"""Synthetic validation cases; no game image, compiler, or network required."""
import argparse
import copy
import hashlib
import importlib.util
import json
import os
from pathlib import Path
import subprocess
import tempfile
import unittest
from unittest.mock import patch

spec = importlib.util.spec_from_file_location("decomp_build", Path(__file__).resolve().parents[1] / "tools/decomp_build.py")
build = importlib.util.module_from_spec(spec)
spec.loader.exec_module(build)


def report(name="old", percent=100, address="4096", size="4", unit="main/example"):
    return {"units": [{"name": unit, "metadata": {"module_name": "main", "module_id": 0},
                       "functions": [{"name": name, "size": size, "fuzzy_match_percent": percent,
                                      "metadata": {"virtual_address": address}}]}]}


class ReportTests(unittest.TestCase):
    def test_rename_cannot_hide_loss(self):
        result = build.compare_reports(report(), report("renamed", 99), "V")
        self.assertEqual(len(result["lost"]), 1)

    def test_rename_retains_exact(self):
        self.assertEqual(build.compare_reports(report(), report("renamed"), "V")["lost"], [])

    def test_relocated_unit_retains_identity(self):
        self.assertEqual(build.compare_reports(report(), report(unit="main/other"), "V")["lost"], [])

    def test_missing_original_metadata(self):
        r = report(); del r["units"][0]["functions"][0]["metadata"]
        with self.assertRaises(build.ValidationError): build.report_index(r, "V")

    def test_missing_module_metadata(self):
        r = report(); del r["units"][0]["metadata"]["module_id"]
        with self.assertRaises(build.ValidationError): build.report_index(r, "V")

    def test_duplicate_original_keys(self):
        r = report(); r["units"].append(copy.deepcopy(r["units"][0])); r["units"][1]["name"] = "main/other"
        with self.assertRaises(build.ValidationError): build.report_index(r, "V")

    def test_changed_size_is_incomparable(self):
        with self.assertRaises(build.ValidationError): build.compare_reports(report(), report(size="8"), "V")

    def test_scoped_omission_rejected(self):
        with self.assertRaises(build.ValidationError): build.compare_reports(report(), report(), "V", ["main/example", "main/missing"])

    def test_invalid_percentage(self):
        with self.assertRaises(build.ValidationError): build.report_index(report(percent=float("nan")), "V")

    def test_empty_report_rejected(self):
        with self.assertRaises(build.ValidationError): build.report_index({"units": []}, "V")

    def test_zero_address_valid(self):
        self.assertEqual(len(build.report_index(report(address="0"), "V")), 1)


class FixtureTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.base = Path(self.temp.name)
        self.root = self.base / "project"; self.root.mkdir()
        self.lock = self.base / "team.lock"
        for d in ("src", "include/submodule", "tools", "config/V", "build/V"):
            (self.root / d).mkdir(parents=True)
        (self.root / "src/a.cpp").write_text("source")
        (self.root / "include/submodule/header.h").write_text("header")
        (self.root / "configure.py").write_text("# Synthetic configure: existing fixture graph is already generated.\n")
        (self.root / "build.ninja").write_text("# synthetic graph\n")
        (self.root / "build/V/config.json").write_text("{}")
        (self.root / ".gitignore").write_text("build/\nobjdiff.json\nbuild.ninja\n")
        entries = []
        for i in range(127):
            content = str(i).encode(); p = self.root / f"build/V/{i}.rel"; p.write_bytes(content)
            entries.append(f"{hashlib.sha1(content).hexdigest()}  build/V/{i}.rel")
        (self.root / "config/V/build.sha1").write_text("\n".join(entries) + "\n")
        objdiff = {"units": [{"name": "main/example", "base_path": "build/V/a.o", "target_path": "build/V/orig.o"}]}
        (self.root / "objdiff.json").write_text(json.dumps(objdiff))
        (self.root / "build/V/a.o").write_text("compiled object")
        (self.root / "build/V/orig.o").write_text("original object")
        program = '''#!/usr/bin/env python3
import json,sys
from pathlib import Path
if 'report' in sys.argv:
    config=json.loads((Path(sys.argv[sys.argv.index('-p')+1])/'objdiff.json').read_text())
    units=[]
    for unit in config['units']:
        units.append({'name':unit['name'],'metadata':{'module_name':'main','module_id':0},'functions':[{'name':'symbol','size':'4','fuzzy_match_percent':100,'metadata':{'virtual_address':'4096'}}]})
    Path(sys.argv[sys.argv.index('-o')+1]).write_text(json.dumps({'units':units}))
'''
        for name in ("ninja", "dtk", "objdiff"):
            p = self.root / "tools" / name; p.write_text(program); p.chmod(0o755)
        subprocess.run(["git", "init", "-q", str(self.root)], check=True)
        subprocess.run(["git", "-C", str(self.root), "add", "."], check=True)
        subprocess.run(["git", "-C", str(self.root), "-c", "user.name=Test", "-c", "user.email=test@example.invalid", "commit", "-qm", "fixture"], check=True)

    def args(self, action="baseline", mode="full", output="baseline"):
        return argparse.Namespace(action=action, project=str(self.root), version="V", mode=mode,
            target=[] if mode == "full" else ["build/V/a.o"], jobs=1, output=str(self.base/output), lock=str(self.lock),
            ninja="tools/ninja", dtk="tools/dtk", objdiff="tools/objdiff", baseline=str(self.base/"baseline"),
            expected_baseline_revision=build.git(self.root, "rev-parse", "HEAD"), expected_baseline_fingerprint=None, configure_arg=[], fresh_report=False)

    def test_full_gate_runs_three_explicit_commands(self):
        state = build.run(self.args())
        self.assertTrue(state["full_gate"])
        self.assertEqual(state["hashes"], {"ok": 127, "bad": 0})
        self.assertEqual(len(state["commands"]), 6)
        self.assertIn("shasum", state["commands"][4]["argv"])
        self.assertFalse(self.lock.exists())

    def test_scoped_is_not_full(self):
        state = build.run(self.args(mode="objects"))
        self.assertFalse(state["full_gate"])
        self.assertNotIn("hashes", state)

    def test_false_dtk_success_cannot_hide_bad_hash(self):
        (self.root / "build/V/5.rel").write_text("bad")
        with self.assertRaises(build.ValidationError): build.run(self.args())
        self.assertEqual(build.load_json(self.base/"baseline/validation.json")["status"], "failed")

    def test_lock_busy_not_removed(self):
        self.lock.write_text("owner")
        with self.assertRaises(build.ValidationError): build.run(self.args())
        self.assertEqual(self.lock.read_text(), "owner")

    def test_output_inside_repo_rejected(self):
        a = self.args(); a.output = str(self.root / "evidence")
        with self.assertRaises(build.ValidationError): build.run(a)

    def test_existing_output_never_overwritten(self):
        (self.base/"baseline").mkdir()
        with self.assertRaises(build.ValidationError): build.run(self.args())

    def test_tampered_report_rejected(self):
        build.run(self.args()); (self.base/"baseline/report.json").write_text("{}")
        with self.assertRaises(build.ValidationError): build.evidence(self.base/"baseline")

    def test_tampered_command_log_rejected(self):
        build.run(self.args()); (self.base/"baseline/03-build.log").write_text("altered")
        with self.assertRaises(build.ValidationError): build.evidence(self.base/"baseline")

    def test_wrong_expected_revision_rejected(self):
        build.run(self.args()); a = self.args("run", output="candidate"); a.expected_baseline_revision="0"*40
        with self.assertRaises(build.ValidationError): build.run(a)

    def test_scoped_baseline_cannot_claim_full_gate(self):
        build.run(self.args(mode="objects")); a=self.args("run", output="candidate")
        with self.assertRaises(build.ValidationError): build.run(a)

    def test_source_drift_rejected_with_failure_evidence(self):
        original = build.command
        def drift(*args, **kwargs):
            original(*args, **kwargs)
            (self.root/"src/a.cpp").write_text("drift")
        with patch.object(build, "command", side_effect=drift):
            with self.assertRaises(build.ValidationError): build.run(self.args())
        self.assertFalse(self.lock.exists())
        self.assertEqual(build.load_json(self.base/"baseline/validation.json")["status"], "failed")

    def test_submodule_working_content_changes_fingerprint(self):
        tools={"ninja":self.root/"tools/ninja"}; m=self.root/"config/V/build.sha1"
        before=build.snapshot(self.root, tools, m)
        (self.root/"include/submodule/header.h").write_text("dirty header")
        after=build.snapshot(self.root, tools, m)
        self.assertNotEqual(before["source_fingerprint"], after["source_fingerprint"])

    def test_untracked_source_is_hashed(self):
        tools={"ninja":self.root/"tools/ninja"}; m=self.root/"config/V/build.sha1"
        before=build.snapshot(self.root, tools, m)
        (self.root/"src/new.cpp").write_text("new source")
        after=build.snapshot(self.root, tools, m)
        self.assertFalse(after["matches_head"])
        self.assertNotEqual(before["source_fingerprint"], after["source_fingerprint"])

    def test_build_log_is_preserved_and_not_an_input(self):
        p=self.root/"build.log"; p.write_text("human log")
        build.run(self.args())
        self.assertEqual(p.read_text(), "human log")

    def test_dirty_baseline_needs_explicit_fingerprint(self):
        (self.root/"src/a.cpp").write_text("dirty")
        state=build.run(self.args()); self.assertFalse(state["source"]["matches_head"])
        a=self.args("run",output="candidate")
        with self.assertRaises(build.ValidationError): build.run(a)
        a.expected_baseline_fingerprint=state["source"]["source_fingerprint"]
        self.assertEqual(build.run(a)["status"], "passed")

    def test_hash_manifest_must_have127_unique_outputs(self):
        p=self.root/"config/V/build.sha1"; p.write_text(p.read_text().splitlines()[0]+"\n")
        with self.assertRaises(build.ValidationError): build.hash_entries(p,self.root)

    def test_missing_requested_object_rejected(self):
        a=self.args(mode="objects"); a.target=["missing.o"]
        with self.assertRaises(build.ValidationError): build.run(a)

    def test_full_does_not_build_absent_unrelated_draft(self):
        p=self.root/"objdiff.json";data=json.loads(p.read_text())
        data["units"].append({"name":"main/unavailable", "base_path":"build/V/absent.o", "target_path":"build/V/orig2.o"})
        p.write_text(json.dumps(data));(self.root/"build/V/orig2.o").write_text("original")
        program=self.root/"tools/objdiff";text=program.read_text()
        text=text.replace("'fuzzy_match_percent':100", "'fuzzy_match_percent':100 if Path(unit['base_path']).is_file() else 0")
        text=text.replace("'virtual_address':'4096'", "'virtual_address':'4100' if unit['name']=='main/unavailable' else '4096'")
        program.write_text(text)
        state=build.run(self.args());argv=state["commands"][3]["argv"]
        self.assertNotIn("build/V/absent.o",argv)
        self.assertIn("build/V/a.o",argv)
        self.assertFalse(any(str(self.root) in token for token in argv[4:]))
        self.assertNotIn("all_source",argv)
        self.assertEqual(state["unavailable_base_units"],["main/unavailable"])
        self.assertIsNone(state["report_inputs"][str(self.root/"build/V/absent.o")])

    def test_supplied_fingerprint_always_checked_even_if_marked_clean(self):
        build.run(self.args())
        p=self.base/"baseline/validation.json";state=build.load_json(p)
        state["source"]["matches_head"]=True;build.write_json(p,state)
        a=self.args("run",output="candidate");a.expected_baseline_fingerprint="wrong"
        with self.assertRaises(build.ValidationError):build.run(a)
        self.assertFalse((self.base/"candidate").exists())

    def test_configure_preserves_interpreter_symlink_spelling(self):
        import sys
        alias=self.base/"python-alias"
        alias.symlink_to(sys.executable)
        with patch.object(build.sys,"executable",str(alias)):
            state=build.run(self.args())
        self.assertEqual(state["commands"][0]["argv"][3],str(alias))
        self.assertEqual(state["source"]["inputs"]["tools"]["python"]["sha256"],build.digest(alias.resolve()))

    def test_original_side_effect_is_not_scheduled_as_ninja_target(self):
        ninja=self.root/"tools/ninja"
        ninja.write_text("#!/usr/bin/env python3\nimport sys\nif any('orig.o' in x for x in sys.argv):sys.exit(7)\n")
        state=build.run(self.args())
        self.assertNotIn("build/V/orig.o",state["commands"][3]["argv"])
        self.assertEqual(state["commands"][1]["role"],"prepare-original")
        self.assertIn("build/V/config.json",state["commands"][1]["argv"])

    def test_scoped_missing_base_must_not_pass(self):
        (self.root/"build/V/a.o").unlink()
        with self.assertRaises(build.ValidationError):build.run(self.args(mode="objects"))

    def test_wrong_configured_version_rejected_before_build(self):
        p=self.root/"objdiff.json"; data=json.loads(p.read_text())
        data["units"][0]["target_path"]="build/OTHER/orig.o";p.write_text(json.dumps(data))
        with self.assertRaises(build.ValidationError): build.run(self.args())

    def test_report_object_drift_rejected(self):
        original=build.command
        def drift(argv, root, output, records, label):
            original(argv, root, output, records, label)
            if label=="fresh-report":(self.root/"build/V/a.o").write_text("foreign object")
        with patch.object(build,"command",side_effect=drift):
            with self.assertRaises(build.ValidationError):build.run(self.args())

    def test_generated_graph_drift_rejected(self):
        original=build.command
        def drift(argv, root, output, records, label):
            original(argv,root,output,records,label)
            if label=="build":(self.root/"build.ninja").write_text("changed graph")
        with patch.object(build,"command",side_effect=drift):
            with self.assertRaises(build.ValidationError):build.run(self.args())

    def test_ignored_header_still_requires_working_fingerprint(self):
        p=self.root/"include/ignored.h";p.write_text("ignored input")
        with (self.root/".git/info/exclude").open("a") as stream:stream.write("\ninclude/ignored.h\n")
        state=build.run(self.args())
        self.assertFalse(state["source"]["matches_head"])
        self.assertIn("include/ignored.h",state["source"]["inputs"]["files"])

    def test_foreign_dependency_cache_rejected(self):
        p=self.root/"tools/ninja"
        p.write_text("#!/usr/bin/env python3\nimport sys\nif '-t' in sys.argv:print('    /foreign/checkout/source.cpp')\n")
        with self.assertRaises(build.ValidationError):build.run(self.args())

    def test_baseline_config_evidence_tampering_rejected(self):
        build.run(self.args());(self.base/"baseline/objdiff.json").write_text("{}")
        with self.assertRaises(build.ValidationError):build.evidence(self.base/"baseline")

    def test_source_provenance_tampering_rejected(self):
        build.run(self.args());p=self.base/"baseline/validation.json";state=build.load_json(p)
        state["source"]["inputs"]["files"]["src/a.cpp"]="fake";build.write_json(p,state)
        with self.assertRaises(build.ValidationError):build.evidence(self.base/"baseline")

    def baseline_and_candidate_args(self, mode="full"):
        state=build.run(self.args())
        a=self.args("run",mode=mode,output="candidate")
        a.expected_baseline_fingerprint=state["source"]["source_fingerprint"]
        return state,a

    def test_identical_closure_reuses_entire_report_and_fresh_hash_gate(self):
        baseline,a=self.baseline_and_candidate_args()
        state=build.run(a)
        self.assertEqual(state["report_generation"]["kind"],"reused")
        self.assertEqual((self.base/"baseline/report.json").read_bytes(),(self.base/"candidate/report.json").read_bytes())
        self.assertEqual([c["role"] for c in state["commands"]],
                         ["configure","prepare-original","dependency-provenance","build","all127-hashes"])
        self.assertEqual(state["hashes"],{"ok":127,"bad":0})
        self.assertTrue(state["full_gate"])
        build.evidence(self.base/"candidate")

    def test_fresh_report_option_bypasses_reuse(self):
        _,a=self.baseline_and_candidate_args();a.fresh_report=True
        state=build.run(a)
        self.assertEqual(state["report_generation"]["kind"],"generated")
        self.assertEqual(state["commands"][-1]["role"],"fresh-report")

    def test_v1_fresh_evidence_without_reuse_key_regenerates(self):
        _,a=self.baseline_and_candidate_args();p=self.base/"baseline/validation.json"
        state=build.load_json(p);del state["report_reuse"];del state["report_generation"];build.write_json(p,state)
        self.assertEqual(build.run(a)["report_generation"]["kind"],"generated")

    def test_modified_base_bytes_regenerate(self):
        _,a=self.baseline_and_candidate_args();(self.root/"build/V/a.o").write_text("changed compiled object")
        self.assertEqual(build.run(a)["report_generation"]["kind"],"generated")

    def test_modified_target_bytes_regenerate(self):
        _,a=self.baseline_and_candidate_args();(self.root/"build/V/orig.o").write_text("changed original object")
        self.assertEqual(build.run(a)["report_generation"]["kind"],"generated")

    def test_config_metadata_completeness_change_regenerates(self):
        _,a=self.baseline_and_candidate_args();p=self.root/"objdiff.json";cfg=build.load_json(p)
        cfg["units"][0]["metadata"]={"complete":True,"progress_categories":["different"]}
        build.write_json(p,cfg)
        self.assertEqual(build.run(a)["report_generation"]["kind"],"generated")

    def prepare_second_unit(self, unavailable=False):
        p=self.root/"objdiff.json";cfg=build.load_json(p)
        cfg["units"].append({"name":"main/second","base_path":"build/V/b.o","target_path":"build/V/orig2.o"})
        build.write_json(p,cfg);(self.root/"build/V/orig2.o").write_text("original2")
        if not unavailable:(self.root/"build/V/b.o").write_text("compiled2")
        p=self.root/"tools/objdiff";text=p.read_text()
        text=text.replace("'virtual_address':'4096'","'virtual_address':'4096' if unit['name']=='main/example' else '4100'")
        text=text.replace("'fuzzy_match_percent':100","'fuzzy_match_percent':100 if Path(unit['base_path']).is_file() else 0")
        p.write_text(text)

    def test_ordered_config_change_regenerates(self):
        self.prepare_second_unit();_,a=self.baseline_and_candidate_args()
        p=self.root/"objdiff.json";cfg=build.load_json(p);cfg["units"].reverse();build.write_json(p,cfg)
        self.assertEqual(build.run(a)["report_generation"]["kind"],"generated")

    def test_missing_base_becoming_available_regenerates(self):
        self.prepare_second_unit(unavailable=True);_,a=self.baseline_and_candidate_args()
        (self.root/"build/V/b.o").write_text("new compiled draft")
        state=build.run(a)
        self.assertEqual(state["report_generation"]["kind"],"generated")
        self.assertEqual(state["unavailable_base_units"],[])
        self.assertEqual(len(state["comparison"]["gained"]),1)

    def test_available_base_disappearing_regenerates_and_detects_loss(self):
        self.prepare_second_unit();_,a=self.baseline_and_candidate_args()
        (self.root/"build/V/b.o").unlink()
        with self.assertRaises(build.ValidationError):build.run(a)
        state=build.load_json(self.base/"candidate/validation.json")
        self.assertEqual(state["report_generation"]["kind"],"generated")
        self.assertEqual(state["commands"][-1]["role"],"fresh-report")
        self.assertEqual(len(state["comparison"]["lost"]),1)

    def test_changed_tool_still_requires_new_baseline(self):
        _,a=self.baseline_and_candidate_args();p=self.root/"tools/objdiff"
        p.write_text(p.read_text()+"\n# new binary content\n")
        with self.assertRaises(build.ValidationError):build.run(a)
        self.assertFalse((self.base/"candidate").exists())

    def test_changed_runtime_still_requires_new_baseline(self):
        _,a=self.baseline_and_candidate_args();p=self.root/"build/compilers/version"
        p.parent.mkdir();p.write_text("different runtime")
        with self.assertRaises(build.ValidationError):build.run(a)
        state=build.load_json(self.base/"candidate/validation.json")
        self.assertEqual(state["status"],"failed")

    def test_scope_change_regenerates_not_splices(self):
        self.prepare_second_unit();_,a=self.baseline_and_candidate_args(mode="objects")
        state=build.run(a)
        self.assertEqual(state["report_generation"]["kind"],"generated")
        self.assertEqual(state["units"],["main/example"])
        self.assertFalse(state["full_gate"])

    def test_scoped_reuse_stays_scoped(self):
        baseline=build.run(self.args(mode="objects"));a=self.args("run",mode="objects",output="candidate")
        a.expected_baseline_fingerprint=baseline["source"]["source_fingerprint"]
        state=build.run(a)
        self.assertEqual(state["report_generation"]["kind"],"reused")
        self.assertFalse(state["full_gate"]);self.assertNotIn("hashes",state)
        build.evidence(self.base/"candidate")

    def test_report_closure_key_includes_split_tool_runtime_and_configuration(self):
        baseline,_=self.baseline_and_candidate_args()
        old=baseline["report_reuse"]
        for field in ["split_config","generated","runtime","original_binaries","objdiff_tool","options","config_sha256","object_inputs","unavailable_base_units"]:
            with self.subTest(field=field):
                current=copy.deepcopy(old);current["inputs"][field]="different"
                current["sha256"]=build.json_digest(current["inputs"])
                self.assertFalse(build.may_reuse_report(baseline,current,False))

    def test_split_metadata_change_regenerates(self):
        _,a=self.baseline_and_candidate_args();(self.root/"build/V/config.json").write_text('{"changed":true}')
        self.assertEqual(build.run(a)["report_generation"]["kind"],"generated")

    def test_bad_fresh_hash_gate_blocks_reuse(self):
        _,a=self.baseline_and_candidate_args();(self.root/"build/V/5.rel").write_text("bad")
        with patch.object(build,"reuse_report") as reuse:
            with self.assertRaises(build.ValidationError):build.run(a)
            reuse.assert_not_called()
        self.assertEqual(build.load_json(self.base/"candidate/validation.json")["status"],"failed")

    def test_baseline_tampering_at_copy_rejected(self):
        _,a=self.baseline_and_candidate_args();original=build.reuse_report
        def tamper(path,output,state):
            (path/"report.json").write_text("{}")
            original(path,output,state)
        with patch.object(build,"reuse_report",side_effect=tamper):
            with self.assertRaises(build.ValidationError):build.run(a)
        self.assertFalse(build.load_json(self.base/"candidate/validation.json")["full_gate"])

    def test_object_drift_after_copy_rejected(self):
        _,a=self.baseline_and_candidate_args();original=build.shutil.copyfile
        def drift(source,destination):
            result=original(source,destination)
            (self.root/"build/V/a.o").write_text("drift")
            return result
        with patch.object(build.shutil,"copyfile",side_effect=drift):
            with self.assertRaises(build.ValidationError):build.run(a)

    def test_reused_evidence_does_not_depend_on_ancestor_path(self):
        _,a=self.baseline_and_candidate_args();build.run(a)
        build.shutil.rmtree(self.base/"baseline")
        build.evidence(self.base/"candidate")

    def test_nested_reuse_records_explicit_ancestry(self):
        _,a=self.baseline_and_candidate_args();state=build.run(a)
        a=self.args("run",output="third");a.baseline=str(self.base/"candidate")
        a.expected_baseline_fingerprint=state["source"]["source_fingerprint"]
        final=build.run(a)
        self.assertEqual(len(final["report_generation"]["ancestry"]),2)
        build.evidence(self.base/"third")

    def test_reused_origin_tampering_rejected(self):
        _,a=self.baseline_and_candidate_args();build.run(a)
        p=self.base/"candidate/validation.json";state=build.load_json(p)
        state["report_generation"]["origin"]["report_sha256"]="0"*64;build.write_json(p,state)
        with self.assertRaises(build.ValidationError):build.evidence(self.base/"candidate")

    def test_inconsistent_reuse_key_rejected(self):
        build.run(self.args());p=self.base/"baseline/validation.json";state=build.load_json(p)
        state["report_reuse"]["inputs"]["options"]=["unverified option"];build.write_json(p,state)
        with self.assertRaises(build.ValidationError):build.evidence(self.base/"baseline")

    def test_command_failure_is_recorded(self):
        (self.root/"tools/ninja").write_text("#!/bin/sh\nexit 3\n")
        with self.assertRaises(build.ValidationError): build.run(self.args())
        state=build.load_json(self.base/"baseline/validation.json")
        self.assertEqual(state["commands"][1]["returncode"],3)
        self.assertEqual(state["status"],"failed")




class DependencyPathTests(unittest.TestCase):
    def audit(self, text, root):
        with patch.object(build.Path, "read_text", return_value=text):
            build.validate_dependency_paths(Path("/synthetic/deps.log"), root)
    def test_duplicate_absolute_paths_resolved_once(self):
        root = Path("/synthetic/project")
        with patch.object(build.Path, "resolve", return_value=root / "include/header.h") as resolve:
            self.audit("    /synthetic/project/include/header.h\n" * 100, root)
        self.assertEqual(resolve.call_count, 1)

    def test_foreign_absolute_path_rejected_even_when_repeated(self):
        root = Path("/synthetic/project")
        with self.assertRaises(build.ValidationError):
            self.audit("    /synthetic/foreign.h\n" * 3, root)

    def test_symlink_escape_rejected(self):
        with tempfile.TemporaryDirectory() as folder:
            base = Path(folder); root = base / "project"; root.mkdir()
            outside = base / "outside.h"; outside.write_text("synthetic")
            link = root / "escaped.h"; link.symlink_to(outside)
            with self.assertRaises(build.ValidationError):
                self.audit("    " + str(link) + "\n", root)

    def test_relative_paths_keep_existing_policy(self):
        with patch.object(build.Path, "resolve") as resolve:
            self.audit("    ../relative/header.h\n    include/local.h\noutput.o: #deps 2\n", Path("/synthetic/project"))
        resolve.assert_not_called()


if __name__ == "__main__":
    unittest.main()
