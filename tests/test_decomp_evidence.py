"""Synthetic evidence fixtures only; no game bytes or extracted assembly."""
import copy
import json
import tempfile
import unittest
from unittest.mock import patch
from pathlib import Path

from tools.decomp_evidence import EvidenceStore, integer, main


class EvidenceTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.base = Path(self.temp.name)
        self.root = self.base / "repo"
        self.root.mkdir()
        (self.root / "src").mkdir()
        (self.root / "include").mkdir()
        (self.root / "src/unit.cpp").write_text('#include <unit.h>\nvoid source() {}\n', encoding="utf-8")
        (self.root / "include/unit.h").write_text('class Example { virtual void method(); };\n// HYPOTHESIS: interpretation only\n', encoding="utf-8")
        (self.root / "configure.py").write_text("configuration = True\n", encoding="utf-8")
        config = self.root / "config/V1/rels/demo"
        config.mkdir(parents=True)
        (config / "symbols.txt").write_text('label = .text:0x00000100; // type:function size:0x8\n', encoding="utf-8")
        (config / "splits.txt").write_text('unit.cpp:\n\t.text start:0x00000100 end:0x00000108\nother.cpp:\n\t.text start:0x108 end:0x110\n', encoding="utf-8")
        self.binary = self.base / "synthetic.bin"
        self.binary.write_bytes(b"synthetic original, not game data")
        self.report_path = self.base / "report.json"
        self.report = {"units": [{"name": "demo/unit", "metadata": {"module_name": "demo", "complete": False,
                        "source_path": "src/unit.cpp"}, "functions": [{"name": "label", "size": "8",
                        "metadata": {"virtual_address": "256"}, "fuzzy_match_percent": 100}]}]}
        self.write_report()
        self.store = EvidenceStore(self.base / "index.sqlite", self.root)

    def tearDown(self):
        self.store.close()
        self.temp.cleanup()

    def write_report(self):
        self.report_path.write_text(json.dumps(self.report), encoding="utf-8")

    def load(self, **kwargs):
        return self.store.import_report(self.report_path, "V1", {"demo": self.binary}, **kwargs)

    def function(self, packet=None):
        packet = packet or self.store.packet("demo/unit")
        return next(o["value"] for o in packet["observations"] if o["kind"] == "function_report")

    def evidence(self, packet=None, kind="report"):
        packet = packet or self.store.packet("demo/unit")
        return [a["id"] for a in packet["artifacts"] if a["kind"] == kind]

    def test_identity_survives_renaming_and_isolated_by_all_original_fields(self):
        self.load()
        original = self.function()["id"]
        self.report["units"][0]["functions"][0]["name"] = "renamed"
        self.write_report()
        self.load()
        self.assertEqual(original, self.function()["id"])
        function = self.function()
        self.assertTrue(function["reported_object_exact"])
        # Exact object instructions must not silently imply Matching/linked.
        unit = next(o["value"] for o in self.store.packet("demo/unit")["observations"] if o["kind"] == "unit_report")
        self.assertFalse(unit["metadata"]["complete"])
        changed_ids = set()
        for field, value in [("size", "12"), ("address", "264")]:
            altered = copy.deepcopy(self.report)
            target = altered["units"][0]["functions"][0]
            if field == "address":
                target["metadata"]["virtual_address"] = value
            else:
                target[field] = value
            self.report_path.write_text(json.dumps(altered))
            self.load()
            changed_ids.add(self.function()["id"])
        self.write_report()
        self.store.import_report(self.report_path, "V2", {"demo": self.binary})
        changed_ids.add(self.function()["id"])
        self.binary.write_bytes(b"different original")
        self.load()
        changed_ids.add(self.function()["id"])
        self.assertEqual(4, len(changed_ids))
        self.assertNotIn(original, changed_ids)

    def test_conflicts_and_review_history_are_append_only(self):
        self.load()
        subject = self.function()["id"]
        evidence = self.evidence(kind="header")
        first = self.store.claim(subject, "slot", "unresolved", "hypothesis", "first", evidence)
        second = self.store.claim(subject, "slot", "different interpretation", "interpretation", "second", evidence)
        self.store.review(first, "accepted", "reviewer", evidence)
        self.store.review(first, "needs-review", "reviewer", evidence)
        packet = self.store.packet("demo/unit")
        claims = packet["claims"]
        self.assertEqual([second], claims[0]["conflicts_with"])
        self.assertEqual([first], claims[1]["conflicts_with"])
        self.assertEqual("needs-review", claims[0]["review_status"])
        self.assertEqual(2, len(claims[0]["reviews"]))
        self.assertEqual("hypothesis", claims[0]["category"])
        self.assertFalse(any(o["kind"] == "proved_slot" for o in packet["observations"]))
        with self.assertRaises(ValueError):
            self.store.claim(subject, "slot", 1, "observed", "author", evidence)
        with self.assertRaises(ValueError):
            self.store.claim(subject, "slot", 1, "hypothesis", "author", [])
        with self.assertRaises(ValueError):
            self.store.review(first, "accepted", "reviewer", ["missing"])

    def test_source_header_and_report_staleness_preserves_original_hashes(self):
        imported = self.load()
        packet = self.store.packet("demo/unit")
        subject = self.function(packet)["id"]
        self.store.claim(subject, "meaning", "unknown", "hypothesis", "author", self.evidence(packet, "header"))
        self.assertFalse(packet["stale"])
        self.assertEqual("unverified", packet["report_source_alignment"]["status"])
        (self.root / "include/unit.h").write_text("class Changed {};\n")
        (self.root / "src/unit.cpp").write_text("void changed() {}\n")
        self.report_path.write_text(json.dumps({"units": []}))
        packet = self.store.packet("demo/unit", imported)
        self.assertTrue(packet["stale"])
        self.assertTrue(packet["claims"][0]["stale"])
        self.assertEqual({"header", "source", "report"}, {a["kind"] for a in packet["artifacts"] if a["stale"]})
        for artifact in packet["artifacts"]:
            if artifact["stale"]:
                self.assertNotEqual(artifact["sha256"], artifact["current_sha256"])
        (self.root / "include/unit.h").unlink()
        packet = self.store.packet("demo/unit", imported)
        self.assertEqual("missing or unreadable", next(a for a in packet["artifacts"] if a["kind"] == "header")["stale_reason"])

    def test_context_and_assembly_operands_never_infer_virtual_slots(self):
        assembly = self.base / "synthetic.s"
        assembly.write_text('.fn label, global\n/* synthetic */ bl possible_name\n/* synthetic */ bctrl\n/* synthetic */ b .L_local\n.endfn label\n')
        map_file = self.base / "synthetic.map"
        map_file.write_text('.section 1\n00000100 PossiblyWrongClass__method\n00000200 Unrelated\n')
        self.load(assembly={"demo/unit": assembly}, maps={"demo": map_file})
        packet = self.store.packet("demo/unit")
        calls = next(o["value"] for o in packet["observations"] if o["kind"] == "assembly_calls")
        self.assertEqual(1, len(calls))
        self.assertEqual("possible_name", calls[0]["callee_operand"])
        self.assertIn("unresolved", calls[0]["proof_scope"])
        labels = next(o["value"] for o in packet["observations"] if o["kind"] == "map_labels")
        self.assertEqual(1, len(labels))
        self.assertEqual("PossiblyWrongClass__method", labels[0]["label_operand"])
        self.assertIn("unverified", labels[0]["proof_scope"])
        symbols = next(o["value"] for o in packet["observations"] if o["kind"] == "symbols_context")
        self.assertEqual("label", symbols[0]["label"])
        splits = next(o["value"] for o in packet["observations"] if o["kind"] == "splits_context")
        self.assertEqual(2, len(splits))
        self.assertFalse(packet["claims"])

    def test_malformed_import_is_atomic(self):
        self.load()
        count = self.store.connection.execute("SELECT count(*) FROM observations").fetchone()[0]
        malformed = [[], {"units": [{}]}, {"units": [self.report["units"][0], self.report["units"][0]]}]
        for case in malformed:
            self.report_path.write_text(json.dumps(case))
            with self.assertRaises(ValueError):
                self.load()
            self.assertEqual(count, self.store.connection.execute("SELECT count(*) FROM observations").fetchone()[0])
        for change in [{"size": 0}, {"size": -1}, {"metadata": {}}, {"metadata": []}, {"fuzzy_match_percent": 101}, {"fuzzy_match_percent": True}]:
            case = copy.deepcopy(self.report)
            case["units"][0]["functions"][0].update(change)
            self.report_path.write_text(json.dumps(case))
            with self.assertRaises(ValueError):
                self.load()
        self.write_report()
        with self.assertRaises(ValueError):
            self.store.import_report(self.report_path, "V1", {})
        with self.assertRaises(ValueError):
            self.load(units=["missing"])
        self.report_path.write_text('{"units": [NaN]}')
        with self.assertRaises(ValueError):
            self.load()

    def test_outputs_must_be_outside_repository_and_snapshot_imports_are_idempotent(self):
        imported = self.load()
        self.assertEqual(imported, self.load())
        self.assertEqual(1, self.store.connection.execute("SELECT count(*) FROM imports").fetchone()[0])
        with self.assertRaises(ValueError):
            EvidenceStore(self.root / "forbidden.sqlite", self.root)
        with self.assertRaises(ValueError):
            self.store.write_packet("demo/unit", self.root / "packet")
        json_path, markdown = self.store.write_packet("demo/unit", self.base / "packets")
        self.assertEqual(imported, json.loads(json_path.read_text())["import_id"])
        self.assertIn("no inferred virtual-slot", markdown.read_text())
        self.assertIn("Original address", markdown.read_text())
        self.assertIn("sha256", json_path.read_text())

    def test_review_evidence_and_original_binary_invalidate_effective_acceptance(self):
        self.load()
        subject = self.function()["id"]
        claim = self.store.claim(subject, "meaning", "candidate", "hypothesis", "author", self.evidence(kind="header"))
        self.store.review(claim, "accepted", "reviewer", self.evidence(kind="report"))
        original_report = self.report_path.read_bytes()
        self.report_path.write_text(json.dumps({"units": []}))
        item = self.store.packet("demo/unit")["claims"][0]
        self.assertFalse(item["stale"])
        self.assertTrue(item["reviews"][0]["stale"])
        self.assertEqual("accepted", item["review_status"])
        self.assertEqual("needs-review", item["effective_review_status"])
        self.report_path.write_bytes(original_report)
        self.binary.write_bytes(b"changed binary")
        item = self.store.packet("demo/unit")["claims"][0]
        self.assertTrue(item["stale"])
        self.assertTrue(item["reviews"][0]["stale"])
        self.assertEqual("needs-review", item["effective_review_status"])

    def test_new_local_shadow_and_unresolved_include_changes_are_detected(self):
        (self.root / "include/unit.h").unlink()
        library = self.root / "include/lib/BrawlHeaders/Brawl/Include"
        library.mkdir(parents=True)
        (library / "unit.h").write_text("class Library {};\n")
        self.load()
        self.assertFalse(self.store.packet("demo/unit")["stale"])
        claim = self.store.claim(self.function()["id"], "meaning", "library candidate", "hypothesis", "author", self.evidence(kind="header"))
        self.store.review(claim, "accepted", "reviewer", self.evidence(kind="header"))
        (self.root / "include/unit.h").write_text("class Local {};\n")
        packet = self.store.packet("demo/unit")
        self.assertTrue(packet["stale"])
        self.assertTrue(packet["include_resolution_changes"])
        self.assertEqual("needs-review", packet["claims"][0]["effective_review_status"])
        self.assertTrue(all(o["stale"] for o in packet["observations"] if o["kind"] == "function_report"))
        (self.root / "src/unit.cpp").write_text('#include <missing.h>\n')
        self.load()
        self.assertFalse(self.store.packet("demo/unit")["include_resolution_changes"])
        (self.root / "include/missing.h").write_text("class Found {};\n")
        self.assertTrue(self.store.packet("demo/unit")["include_resolution_changes"])

    def test_import_collisions_and_file_changes_during_import_are_rejected_atomically(self):
        duplicate = copy.deepcopy(self.report["units"][0])
        duplicate["name"] = "demo/other-unit"
        self.report["units"].append(duplicate)
        self.write_report()
        with self.assertRaises(ValueError):
            self.load()
        self.report["units"].pop()
        self.write_report()
        config = self.base / "objdiff.json"
        config.write_text(json.dumps({"units": [{"name": "demo/unit"}, {"name": "demo/unit"}]}))
        with self.assertRaises(ValueError):
            self.load(objdiff=config)
        original_artifact = self.store._artifact
        changed = False
        def change_after_read(path, kind):
            nonlocal changed
            result = original_artifact(path, kind)
            if kind == "source" and not changed:
                changed = True
                Path(path).write_text("changed during import\n")
            return result
        with patch.object(self.store, "_artifact", side_effect=change_after_read):
            with self.assertRaisesRegex(ValueError, "changed during import"):
                self.load()
        self.assertEqual(0, self.store.connection.execute("SELECT count(*) FROM imports").fetchone()[0])

    def test_packet_snapshots_use_distinct_import_names_and_atomic_files(self):
        original = self.load()
        first, _ = self.store.write_packet("demo/unit", self.base / "packets", original)
        self.report["units"][0]["functions"][0]["name"] = "renamed"
        self.write_report()
        latest = self.load()
        second, _ = self.store.write_packet("demo/unit", self.base / "packets", latest)
        self.assertNotEqual(first, second)
        self.assertEqual(original, json.loads(first.read_text())["import_id"])
        self.assertEqual(latest, json.loads(second.read_text())["import_id"])
        self.assertFalse(list((self.base / "packets").glob(".evidence-*")))

    def test_cli_errors_are_nonzero_and_decimal_hex_identity_is_unambiguous(self):
        self.assertEqual(256, integer("256", "address"))
        self.assertEqual(256, integer("0x100", "address"))
        self.assertEqual(256, integer(256, "address"))
        with self.assertRaises(ValueError):
            integer(True, "address")
        with self.assertRaises(SystemExit) as exit_status:
            main(["--db", str(self.base / "cli.sqlite"), "--root", str(self.root), "import",
                  "--report", str(self.report_path), "--version", "V1", "--binary", "wrong=" + str(self.binary)])
        self.assertEqual(2, exit_status.exception.code)


if __name__ == "__main__":
    unittest.main()
