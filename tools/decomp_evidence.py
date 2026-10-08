#!/usr/bin/env python3
"""Index observed decompilation evidence and append reviewed interpretations.

Only the Python tool and synthetic tests belong in Git. Databases and packets
must live outside the checkout. Report percentages describe object comparisons;
they are not proof of behavior, virtual slots, source identities, or REL hashes.
Uses the standard library only; no compiler, DTK, or external service is run.
"""
import argparse
import datetime
import hashlib
import json
import math
import re
import sqlite3
import tempfile
from pathlib import Path


def digest_file(path):
    digest = hashlib.sha256()
    with Path(path).open("rb") as stream:
        for chunk in iter(lambda: stream.read(1024 * 1024), b""):
            digest.update(chunk)
    return digest.hexdigest()


def stable_id(value):
    return hashlib.sha256(json.dumps(value, sort_keys=True, separators=(",", ":")).encode()).hexdigest()


def integer(value, label):
    if isinstance(value, bool):
        raise ValueError(label + " must be a nonnegative integer")
    try:
        result = value if isinstance(value, int) else int(value, 16 if str(value).lower().startswith("0x") else 10)
    except (TypeError, ValueError):
        raise ValueError(label + " must be a nonnegative integer") from None
    if result < 0:
        raise ValueError(label + " must be a nonnegative integer")
    return result


def outside_repo(path, root):
    path, root = Path(path).resolve(), Path(root).resolve()
    if path == root or root in path.parents:
        raise ValueError("database and generated packets must be outside the repository: " + str(path))
    return path


def parse_json(raw, path):
    def reject_constant(value):
        raise ValueError("non-finite JSON number: " + value)
    try:
        return json.loads(raw.decode("utf-8"), parse_constant=reject_constant)
    except (json.JSONDecodeError, UnicodeDecodeError) as error:
        raise ValueError("malformed JSON: " + str(path)) from error


def atomic_write(path, text):
    temporary = None
    try:
        with tempfile.NamedTemporaryFile(mode="w", encoding="utf-8", dir=path.parent,
                                         prefix=".evidence-", delete=False) as stream:
            temporary = Path(stream.name)
            stream.write(text)
        temporary.replace(path)
    finally:
        if temporary and temporary.exists():
            temporary.unlink()


def pairs(values):
    result = {}
    for value in values or []:
        name, separator, path = value.partition("=")
        if not separator or not name or not path or name in result:
            raise ValueError("expected unique NAME=FILE mapping: " + value)
        result[name] = Path(path).resolve()
    return result


def declaration_lines(text):
    """Lexical declaration candidates only, never inferred ABI facts."""
    result = []
    for number, line in enumerate(text.splitlines(), 1):
        if re.search(r"\b(class|struct|virtual|typedef|using)\b", line) or "HYPOTHESIS:" in line or "MATCH-ONLY:" in line:
            result.append({"line": number, "text": line.strip()})
    return result


def symbol_context(text, functions):
    identities = {(f["identity"]["address"], f["identity"]["size"]) for f in functions}
    result = []
    for number, line in enumerate(text.splitlines(), 1):
        match = re.match(r"(.+?)\s*=\s*(\.[\w.]+):0x([\da-fA-F]+);.*\bsize:0x([\da-fA-F]+)", line)
        if match and (int(match[3], 16), int(match[4], 16)) in identities:
            result.append({"line": number, "label": match[1].strip(), "section": match[2],
                           "address": int(match[3], 16), "size": int(match[4], 16), "text": line})
    return result


def split_context(text, source):
    current, result = None, []
    normalized = source.removeprefix("src/") if source else None
    for number, line in enumerate(text.splitlines(), 1):
        if line and not line[0].isspace() and line.endswith(":"):
            current = line[:-1]
        if current and normalized and (current == normalized or normalized.endswith("/" + current)):
            if line.strip():
                result.append({"line": number, "text": line})
    return result


def direct_calls(text):
    result, current = [], None
    for number, line in enumerate(text.splitlines(), 1):
        match = re.match(r"\.fn\s+([^,]+)", line.strip())
        if match:
            current = match[1]
        instruction = line.split("*/", 1)[-1].strip()
        match = re.match(r"(bl|b)\s+([^\s]+)\s*$", instruction)
        if match and not match[2].startswith(".L"):
            result.append({"line": number, "caller_operand": current, "opcode": match[1],
                           "callee_operand": match[2], "proof_scope": "literal assembly operand; identity unresolved"})
    return result


def map_context(text, functions):
    addresses = {function["identity"]["address"] for function in functions}
    result, section = [], None
    for number, line in enumerate(text.splitlines(), 1):
        marker = re.match(r"\.section\s+(\S+)", line)
        if marker:
            section = marker[1]
        match = re.match(r"([\da-fA-F]{8})\s+(.+)$", line)
        if match and int(match[1], 16) in addresses:
            result.append({"line": number, "section_operand": section, "address_operand": int(match[1], 16),
                           "label_operand": match[2], "proof_scope": "map label observation; source identity unverified"})
    return result


class EvidenceStore:
    def __init__(self, database, root):
        self.root = Path(root).resolve()
        self.database = outside_repo(database, self.root)
        self.database.parent.mkdir(parents=True, exist_ok=True)
        self.connection = sqlite3.connect(self.database)
        self.connection.row_factory = sqlite3.Row
        self.connection.execute("PRAGMA foreign_keys=ON")
        self.connection.executescript("""
            CREATE TABLE IF NOT EXISTS artifacts (
                id TEXT PRIMARY KEY, path TEXT NOT NULL, relative_path TEXT,
                kind TEXT NOT NULL, sha256 TEXT NOT NULL, size INTEGER NOT NULL);
            CREATE TABLE IF NOT EXISTS imports (
                id TEXT PRIMARY KEY, created_at TEXT NOT NULL, manifest TEXT NOT NULL);
            CREATE TABLE IF NOT EXISTS units (
                id TEXT PRIMARY KEY, version TEXT NOT NULL, module TEXT NOT NULL,
                binary_sha256 TEXT NOT NULL, name TEXT NOT NULL);
            CREATE TABLE IF NOT EXISTS functions (
                id TEXT PRIMARY KEY, identity TEXT NOT NULL);
            CREATE TABLE IF NOT EXISTS observations (
                id INTEGER PRIMARY KEY, import_id TEXT NOT NULL REFERENCES imports(id),
                unit_id TEXT NOT NULL REFERENCES units(id), function_id TEXT REFERENCES functions(id),
                kind TEXT NOT NULL, value TEXT NOT NULL, evidence TEXT NOT NULL);
            CREATE TABLE IF NOT EXISTS claims (
                id INTEGER PRIMARY KEY, subject TEXT NOT NULL, key TEXT NOT NULL,
                value TEXT NOT NULL, category TEXT NOT NULL, author TEXT NOT NULL,
                created_at TEXT NOT NULL, evidence TEXT NOT NULL);
            CREATE TABLE IF NOT EXISTS reviews (
                id INTEGER PRIMARY KEY, claim_id INTEGER NOT NULL REFERENCES claims(id),
                status TEXT NOT NULL, reviewer TEXT NOT NULL, created_at TEXT NOT NULL,
                evidence TEXT NOT NULL);
        """)

    def close(self):
        self.connection.close()

    def _artifact(self, path, kind):
        path = Path(path).resolve()
        raw = path.read_bytes()
        sha = hashlib.sha256(raw).hexdigest()
        relative = path.relative_to(self.root).as_posix() if self.root in path.parents else None
        artifact = {"id": stable_id([str(path), kind, sha]), "path": str(path),
                    "relative_path": relative, "kind": kind, "sha256": sha, "size": len(raw)}
        return artifact, raw

    def _include_directories(self):
        return [self.root / item for item in (
            "include", "include/lib/PowerPC_EABI_Support/Runtime/Inc",
            "include/lib/BrawlHeaders/Brawl/Include", "include/lib/BrawlHeaders/nw4r/include",
            "include/lib/BrawlHeaders/OpenRVL/include", "include/lib/BrawlHeaders/OpenRVL/include/MetroTRK",
            "include/lib/BrawlHeaders/OpenRVL/include/revolution", "include/lib/BrawlHeaders/OpenRVL/include/RVLFaceLib",
            "include/lib/BrawlHeaders/OpenRVL/include/stl", "include/lib/BrawlHeaders/utils/include")]

    def _resolve_include(self, parent, operand, quoted):
        candidates = ([parent / operand] if quoted else []) + [d / operand for d in self._include_directories()]
        return next((p.resolve() for p in candidates if p.is_file()), None)

    def _source_files(self, source):
        """Resolve lexical includes using the project's local-shadow order.

        Unresolved system includes are listed explicitly. Dependencies are an
        observed include graph, not a claim to reproduce compiler preprocessing.
        """
        queue, seen, results = [self.root / source], set(), []
        while queue:
            path = queue.pop(0).resolve()
            if path in seen:
                continue
            seen.add(path)
            if self.root not in path.parents:
                raise ValueError("source/include escapes repository: " + str(path))
            artifact, raw = self._artifact(path, "source" if path == (self.root / source).resolve() else "header")
            text = raw.decode("utf-8", errors="replace")
            includes = []
            for number, line in enumerate(text.splitlines(), 1):
                match = re.match(r'\s*#\s*include\s*([<"])([^>"]+)[>"]', line)
                if not match:
                    continue
                quoted = match[1] == '"'
                resolved = self._resolve_include(path.parent, match[2], quoted)
                includes.append({"line": number, "operand": match[2], "quoted": quoted,
                                 "resolved": str(resolved) if resolved else None})
                if resolved:
                    queue.append(resolved)
            results.append((artifact, {"declaration_candidates": declaration_lines(text), "includes": includes}))
        return results

    def import_report(self, report, version, binaries, units=None, objdiff=None, assembly=None, maps=None):
        if not version:
            raise ValueError("explicit binary version is required")
        report_art, report_raw = self._artifact(report, "report")
        document = parse_json(report_raw, report)
        if not isinstance(document, dict) or not isinstance(document.get("units"), list):
            raise ValueError("report must contain a units array")
        config_units = {}
        artifacts = {}
        artifacts[report_art["id"]] = report_art
        if objdiff:
            config_art, config_raw = self._artifact(objdiff, "objdiff_config")
            config = parse_json(config_raw, objdiff)
            if not isinstance(config, dict) or not isinstance(config.get("units"), list):
                raise ValueError("objdiff configuration must contain a units array")
            artifacts[config_art["id"]] = config_art
            for item in config["units"]:
                if not isinstance(item, dict) or not isinstance(item.get("name"), str):
                    raise ValueError("malformed objdiff unit")
                if item["name"] in config_units:
                    raise ValueError("duplicate objdiff unit: " + item["name"])
                config_units[item["name"]] = item
        selected, names, function_ids = [], set(), set()
        wanted = set(units or [])
        binary_artifacts = {}
        for raw in document["units"]:
            if not isinstance(raw, dict) or not isinstance(raw.get("name"), str) or not raw["name"]:
                raise ValueError("malformed report unit")
            name = raw["name"]
            if name in names:
                raise ValueError("duplicate report unit: " + name)
            names.add(name)
            if wanted and name not in wanted:
                continue
            metadata = raw.get("metadata", {})
            if not isinstance(metadata, dict):
                raise ValueError("unit metadata must be an object")
            module = metadata.get("module_name") or name.split("/", 1)[0]
            if not isinstance(module, str) or not module or module not in binaries:
                raise ValueError("explicit original binary mapping missing for " + str(module))
            if module not in binary_artifacts:
                path = Path(binaries[module]).resolve()
                sha = digest_file(path)
                binary_artifacts[module] = {"id": stable_id([str(path), "original_binary", sha]),
                                          "path": str(path), "relative_path": None, "kind": "original_binary",
                                          "sha256": sha, "size": path.stat().st_size}
            binary = binary_artifacts[module]
            artifacts[binary["id"]] = binary
            key = {"version": version, "module": module, "binary_sha256": binary["sha256"], "name": name}
            unit_id = stable_id(key)
            functions = []
            raw_functions = raw.get("functions", [])
            if not isinstance(raw_functions, list):
                raise ValueError("functions must be an array")
            for function in raw_functions:
                if not isinstance(function, dict) or not isinstance(function.get("name"), str):
                    raise ValueError("malformed report function")
                if not isinstance(function.get("metadata", {}), dict):
                    raise ValueError("function metadata must be an object")
                address = integer(function.get("metadata", {}).get("virtual_address"), "original address")
                size = integer(function.get("size"), "original size")
                if not size:
                    raise ValueError("function size must be positive")
                identity = {"binary_sha256": binary["sha256"], "version": version, "module": module,
                            "address": address, "size": size}
                function_id = stable_id(identity)
                if function_id in function_ids:
                    raise ValueError("duplicate original function identity across selected units")
                function_ids.add(function_id)
                percent = function.get("fuzzy_match_percent")
                if percent is not None and (isinstance(percent, bool) or not isinstance(percent, (int, float))
                                            or not math.isfinite(percent) or not 0 <= percent <= 100):
                    raise ValueError("function match percentage must be between 0 and 100")
                functions.append({"id": function_id, "identity": identity, "report": function,
                                  "reported_object_exact": percent == 100})
            context = []
            references = [report_art["id"], binary["id"]]
            if objdiff:
                references.append(config_art["id"])
            source = metadata.get("source_path") or config_units.get(name, {}).get("metadata", {}).get("source_path")
            if source:
                if not isinstance(source, str):
                    raise ValueError("source path must be a string")
                for artifact, value in self._source_files(source):
                    artifacts[artifact["id"]] = artifact
                    context.append({"kind": "source_context", "value": value, "evidence": [artifact["id"]]})
                    references.append(artifact["id"])
            for filename, kind in [(self.root / "configure.py", "configure"),
                                   (self.root / "config" / version / ("symbols.txt" if module == "main" else "rels/" + module + "/symbols.txt"), "symbols"),
                                   (self.root / "config" / version / ("splits.txt" if module == "main" else "rels/" + module + "/splits.txt"), "splits")]:
                if filename.is_file():
                    artifact, contents = self._artifact(filename, kind)
                    artifacts[artifact["id"]] = artifact
                    references.append(artifact["id"])
                    text = contents.decode("utf-8", errors="replace")
                    value = symbol_context(text, functions) if kind == "symbols" else split_context(text, source) if kind == "splits" else {"configuration_file": str(filename)}
                    context.append({"kind": kind + "_context", "value": value, "evidence": [artifact["id"]]})
            for mapping, mapping_key, kind, parser in [(assembly or {}, name, "assembly_calls", direct_calls),
                                                      (maps or {}, module, "map_labels", lambda text: map_context(text, functions))]:
                if mapping_key in mapping:
                    artifact, contents = self._artifact(mapping[mapping_key], kind)
                    artifacts[artifact["id"]] = artifact
                    references.append(artifact["id"])
                    context.append({"kind": kind, "value": parser(contents.decode("utf-8", errors="replace")), "evidence": [artifact["id"]]})
            selected.append({"id": unit_id, "key": key, "metadata": metadata, "functions": functions,
                             "context": context, "references": references, "sections": raw.get("sections", [])})
        if wanted - names:
            raise ValueError("requested units absent from report: " + ", ".join(sorted(wanted - names)))
        if not selected:
            raise ValueError("no units selected")
        manifest = {"format": 1, "report": report_art["id"], "version": version, "units": [u["id"] for u in selected],
                    "artifacts": sorted(artifacts)}
        import_id = stable_id(manifest)
        for artifact in artifacts.values():
            if digest_file(artifact["path"]) != artifact["sha256"]:
                raise ValueError("evidence changed during import: " + artifact["path"])
        # All input validation and hashing happens before this atomic write.
        with self.connection:
            if self.connection.execute("SELECT 1 FROM imports WHERE id=?", (import_id,)).fetchone():
                return import_id
            for artifact in artifacts.values():
                self.connection.execute("INSERT OR IGNORE INTO artifacts VALUES (:id,:path,:relative_path,:kind,:sha256,:size)", artifact)
            self.connection.execute("INSERT INTO imports VALUES (?,?,?)", (import_id, self._now(), json.dumps(manifest)))
            for unit in selected:
                key = unit["key"]
                self.connection.execute("INSERT OR IGNORE INTO units VALUES (?,?,?,?,?)", (unit["id"], version, key["module"], key["binary_sha256"], key["name"]))
                self._observe(import_id, unit["id"], None, "unit_report", {"metadata": unit["metadata"], "sections": unit["sections"]}, unit["references"])
                for function in unit["functions"]:
                    self.connection.execute("INSERT OR IGNORE INTO functions VALUES (?,?)", (function["id"], json.dumps(function["identity"])))
                    self._observe(import_id, unit["id"], function["id"], "function_report", function, unit["references"])
                for observation in unit["context"]:
                    self._observe(import_id, unit["id"], None, observation["kind"], observation["value"], observation["evidence"])
        return import_id

    @staticmethod
    def _now():
        return datetime.datetime.now(datetime.timezone.utc).isoformat()

    def _observe(self, import_id, unit, function, kind, value, evidence):
        self.connection.execute("INSERT INTO observations(import_id,unit_id,function_id,kind,value,evidence) VALUES (?,?,?,?,?,?)",
                                (import_id, unit, function, kind, json.dumps(value), json.dumps(evidence)))

    def _validate_evidence(self, evidence):
        if not evidence:
            raise ValueError("at least one explicit evidence reference is required")
        for identifier in evidence:
            if not self.connection.execute("SELECT 1 FROM artifacts WHERE id=?", (identifier,)).fetchone():
                raise ValueError("unknown evidence artifact: " + identifier)

    def claim(self, subject, key, value, category, author, evidence):
        if category not in ("interpretation", "hypothesis"):
            raise ValueError("claims are interpretations or hypotheses, never imported facts")
        if not key or not author:
            raise ValueError("claim key and author are required")
        if not any(self.connection.execute("SELECT 1 FROM " + table + " WHERE id=?", (subject,)).fetchone() for table in ("units", "functions")):
            raise ValueError("unknown claim subject")
        self._validate_evidence(evidence)
        with self.connection:
            cursor = self.connection.execute("INSERT INTO claims(subject,key,value,category,author,created_at,evidence) VALUES (?,?,?,?,?,?,?)",
                                             (subject, key, json.dumps(value, sort_keys=True, allow_nan=False), category, author, self._now(), json.dumps(evidence)))
        return cursor.lastrowid

    def review(self, claim, status, reviewer, evidence):
        if status not in ("accepted", "rejected", "needs-review") or not reviewer:
            raise ValueError("explicit review status and reviewer are required")
        if not self.connection.execute("SELECT 1 FROM claims WHERE id=?", (claim,)).fetchone():
            raise ValueError("unknown claim")
        self._validate_evidence(evidence)
        with self.connection:
            cursor = self.connection.execute("INSERT INTO reviews(claim_id,status,reviewer,created_at,evidence) VALUES (?,?,?,?,?)",
                                             (claim, status, reviewer, self._now(), json.dumps(evidence)))
        return cursor.lastrowid

    def packet(self, unit_name, import_id=None):
        query = "SELECT o.import_id,o.unit_id FROM observations o JOIN units u ON u.id=o.unit_id WHERE u.name=?"
        parameters = [unit_name]
        if import_id:
            query += " AND o.import_id=?"
            parameters.append(import_id)
        row = self.connection.execute(query + " ORDER BY o.id DESC LIMIT 1", parameters).fetchone()
        if not row:
            raise ValueError("unit not imported: " + unit_name)
        import_id, unit_id = row
        observations = []
        for record in self.connection.execute("SELECT * FROM observations WHERE import_id=? AND unit_id=? ORDER BY id", (import_id, unit_id)):
            item = dict(record)
            item["value"], item["evidence"] = json.loads(item["value"]), json.loads(item["evidence"])
            observations.append(item)
        subjects = {unit_id} | {o["function_id"] for o in observations if o["function_id"]}
        claims = []
        for record in self.connection.execute("SELECT * FROM claims ORDER BY id"):
            if record["subject"] not in subjects:
                continue
            item = dict(record)
            item["value"], item["evidence"] = json.loads(item["value"]), json.loads(item["evidence"])
            item["reviews"] = [{**dict(review), "evidence": json.loads(review["evidence"])} for review in self.connection.execute("SELECT * FROM reviews WHERE claim_id=? ORDER BY id", (item["id"],))]
            item["review_status"] = item["reviews"][-1]["status"] if item["reviews"] else "unreviewed"
            claims.append(item)
        for claim in claims:
            claim["conflicts_with"] = [other["id"] for other in claims if other["subject"] == claim["subject"] and other["key"] == claim["key"] and other["value"] != claim["value"]]
        references = {identifier for o in observations for identifier in o["evidence"]}
        references.update(identifier for c in claims for identifier in c["evidence"])
        references.update(identifier for c in claims for r in c["reviews"] for identifier in r["evidence"])
        artifacts = []
        for identifier in sorted(references):
            item = dict(self.connection.execute("SELECT * FROM artifacts WHERE id=?", (identifier,)).fetchone())
            path = self.root / item["relative_path"] if item["relative_path"] else Path(item["path"])
            try:
                actual = digest_file(path)
                reason = None if actual == item["sha256"] else "hash changed"
            except OSError:
                actual, reason = None, "missing or unreadable"
            item.update(current_path=str(path), current_sha256=actual, stale=reason is not None, stale_reason=reason)
            artifacts.append(item)
        by_id = {a["id"]: a for a in artifacts}
        stale = {a["id"] for a in artifacts if a["stale"]}
        resolution_changes = []
        for observation in observations:
            observation["stale"] = bool(stale.intersection(observation["evidence"]))
            if observation["kind"] == "source_context":
                source_artifact = by_id[observation["evidence"][0]]
                parent = Path(source_artifact["current_path"]).parent
                for include in observation["value"]["includes"]:
                    current = self._resolve_include(parent, include["operand"], include.get("quoted", False))
                    expected = Path(include["resolved"]) if include["resolved"] else None
                    if expected and self.root not in expected.parents:
                        # External paths stay external; checkout-local paths are
                        # rebased by their artifact's recorded relative path.
                        matching = next((a for a in artifacts if a["path"] == str(expected)), None)
                        if matching and matching["relative_path"]:
                            expected = self.root / matching["relative_path"]
                    change = {"source": source_artifact["current_path"], "line": include["line"],
                              "operand": include["operand"], "previous": str(expected) if expected else None,
                              "current": str(current) if current else None}
                    if current != expected or "quoted" not in include:
                        resolution_changes.append(change)
                        source_artifact["stale"] = True
                        source_artifact["stale_reason"] = "include resolution changed"
                        stale.add(source_artifact["id"])
        for observation in observations:
            observation["stale"] = bool(stale.intersection(observation["evidence"]))
        binary_stale = any(a["kind"] == "original_binary" and a["stale"] for a in artifacts)
        for claim in claims:
            claim["stale"] = binary_stale or bool(resolution_changes) or bool(stale.intersection(claim["evidence"]))
            for review in claim["reviews"]:
                review["stale"] = binary_stale or bool(stale.intersection(review["evidence"]))
            latest = claim["reviews"][-1] if claim["reviews"] else None
            claim["effective_review_status"] = "needs-review" if claim["stale"] or (latest and latest["stale"]) else claim["review_status"]
        unit = dict(self.connection.execute("SELECT * FROM units WHERE id=?", (unit_id,)).fetchone())
        return {"schema_version": 1, "unit": unit, "import_id": import_id,
                "report_source_alignment": {"status": "unverified",
                    "reason": "Context hashes were observed at import; an objdiff report does not prove it was built from those files."},
                "scope": "Observed report/config/source context only; no inferred virtual-slot or field semantics; no automatic proof promotion.",
                "stale": bool(stale), "include_resolution_changes": resolution_changes,
                "artifacts": artifacts, "observations": observations, "claims": claims}

    def write_packet(self, unit, output, import_id=None):
        output = outside_repo(output, self.root)
        packet = self.packet(unit, import_id)
        output.mkdir(parents=True, exist_ok=True)
        basename = (re.sub(r"[^\w.-]+", "-", unit).strip("-")[:100] + "-" + packet["unit"]["id"][:12]
                    + "-" + packet["import_id"][:12])
        json_path, markdown_path = output / (basename + ".json"), output / (basename + ".md")
        lines = ["# " + unit, "", packet["scope"], "", "Import: `" + packet["import_id"] + "`", "",
                 "Binary SHA-256: `" + packet["unit"]["binary_sha256"] + "`", "",
                 "Stale since import: **" + str(packet["stale"]) + "**", "",
                 "Report/source alignment: **unverified**. Unchanged hashes do not establish an exact build binding.", "",
                 "## Functions", "",
                 "| Original address | Size | Report label | Object match | Identity |", "|---|---:|---|---|---|"]
        for observation in packet["observations"]:
            if observation["kind"] == "function_report":
                value = observation["value"]
                label = value["report"]["name"].replace("|", "\\|")
                lines.append(f"| 0x{value['identity']['address']:X} | {value['identity']['size']} | {label} | {value['report'].get('fuzzy_match_percent', 'unknown')} | `{value['id']}` |")
        lines += ["", "## Evidence files", ""]
        selected = [a for a in packet["artifacts"] if a["kind"] != "header" or a["stale"]]
        for artifact in selected[:20]:
            lines.append(f"- `{artifact['id']}` {artifact['kind']}: `{artifact['current_path']}`; SHA-256 `{artifact['sha256']}`; stale={artifact['stale']}")
        lines += [f"", f"{len(packet['artifacts'])} evidence artifacts total; full hashes and transitive header context are in `{json_path.name}`.",
                  "", "## Context overview", "", "These are lexical observations, not ABI proof.", ""]
        for observation in packet["observations"]:
            if observation["kind"] == "source_context" and any(a["kind"] == "source" and a["id"] in observation["evidence"] for a in packet["artifacts"]):
                for declaration in observation["value"]["declaration_candidates"][:12]:
                    lines.append(f"- Source line {declaration['line']}: `{declaration['text'][:180]}`")
            if observation["kind"] not in ("function_report", "unit_report", "source_context"):
                value = observation["value"]
                count = len(value) if isinstance(value, (list, dict)) else 1
                lines.append(f"- Observation {observation['id']}: {observation['kind']}; {count} entries; evidence={observation['evidence']}; details in JSON.")
        lines += ["## Interpretations and hypotheses", ""]
        for claim in packet["claims"]:
            lines.append(f"- Claim {claim['id']} ({claim['category']}, historical={claim['review_status']}, effective={claim['effective_review_status']}, stale={claim['stale']}): {claim['key']} = {json.dumps(claim['value'])}; conflicts={claim['conflicts_with']}; evidence={claim['evidence']}")
        changes = packet["include_resolution_changes"]
        lines += ["", "## Include resolution changes", "", f"{len(changes)} changes; full details in JSON."]
        atomic_write(json_path, json.dumps(packet, indent=2, ensure_ascii=False, allow_nan=False) + "\n")
        atomic_write(markdown_path, "\n".join(lines) + "\n")
        return json_path, markdown_path


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--db", required=True, help="SQLite database outside repository")
    parser.add_argument("--root", required=True, help="repository root for context and stale checks")
    commands = parser.add_subparsers(dest="command", required=True)
    load = commands.add_parser("import", help="append report/context observations with explicit original binary mapping")
    load.add_argument("--report", required=True)
    load.add_argument("--version", required=True)
    load.add_argument("--binary", action="append", required=True, metavar="MODULE=FILE")
    load.add_argument("--unit", action="append", help="exact report unit name; repeated selectors supported")
    load.add_argument("--objdiff")
    load.add_argument("--assembly", action="append", metavar="UNIT=FILE")
    load.add_argument("--map", action="append", metavar="MODULE=FILE")
    packet = commands.add_parser("packet", help="emit JSON/Markdown outside repo; show conflicts and live stale hashes")
    packet.add_argument("--unit", required=True)
    packet.add_argument("--out", required=True)
    packet.add_argument("--import-id")
    claim = commands.add_parser("claim", help="append an interpretation or HYPOTHESIS; never erase conflicting claims")
    claim.add_argument("--subject", required=True, help="unit or stable function ID from packet")
    claim.add_argument("--key", required=True)
    claim.add_argument("--value", required=True, help="JSON claim value")
    claim.add_argument("--category", choices=["interpretation", "hypothesis"], default="hypothesis")
    claim.add_argument("--author", required=True)
    claim.add_argument("--evidence", action="append", required=True, help="artifact ID from packet")
    review = commands.add_parser("review", help="append human/agent review status without promoting an observation to proof")
    review.add_argument("--claim", required=True, type=int)
    review.add_argument("--status", required=True, choices=["accepted", "rejected", "needs-review"])
    review.add_argument("--reviewer", required=True)
    review.add_argument("--evidence", action="append", required=True)
    args = parser.parse_args(argv)
    store = None
    try:
        store = EvidenceStore(args.db, args.root)
        if args.command == "import":
            print(store.import_report(args.report, args.version, pairs(args.binary), args.unit, args.objdiff, pairs(args.assembly), pairs(args.map)))
        elif args.command == "packet":
            print("\n".join(str(p) for p in store.write_packet(args.unit, args.out, args.import_id)))
        elif args.command == "claim":
            print(store.claim(args.subject, args.key, json.loads(args.value), args.category, args.author, args.evidence))
        else:
            print(store.review(args.claim, args.status, args.reviewer, args.evidence))
    except (ValueError, OSError, sqlite3.Error) as error:
        parser.exit(2, "error: " + str(error) + "\n")
    finally:
        if store:
            store.close()


if __name__ == "__main__":
    main()
