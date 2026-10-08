#!/usr/bin/env python3
"""Capture revision-bound validation evidence without touching existing logs.

Examples (outputs and shared lock must be outside the checkout):
  python tools/decomp_build.py baseline --mode full --output /tmp/baseline --lock /tmp/team.lock
  python tools/decomp_build.py run --mode objects --target build/RSBE01_02/src/example.o
      --baseline /tmp/baseline --expected-baseline-revision COMMIT
      --expected-baseline-fingerprint FINGERPRINT --output /tmp/check --lock /tmp/team.lock
  python tools/decomp_build.py compare /tmp/baseline /tmp/check

Only a full run can establish the 127-file gate. Full runs refresh existing
comparison bases; absent unrelated draft bases remain explicitly unavailable.
Requested object-scoped bases must compile successfully. Baselines are freshly generated,
not imported reports. Evidence directories must not already exist. Cooperation
requires every runner to use the same explicit lock path; no stale-lock bypass.
Unchanged complete report inputs may reuse finalized baseline report bytes;
--fresh-report disables reuse. Incompatible tools/runtime still require a new baseline.
Warm outputs rely on Ninja dependency correctness; observed hashes are provenance,
not an independent proof that a cached object was compiled from current inputs.
"""
from __future__ import annotations

import argparse
import hashlib
import json
import math
import os
from pathlib import Path
import re
import shutil
import subprocess
import sys
import time
from typing import Any

SCHEMA = 1


class ValidationError(Exception):
    pass


def digest(path: Path, algorithm: str = "sha256") -> str:
    h = hashlib.new(algorithm)
    with path.open("rb") as stream:
        for block in iter(lambda: stream.read(1024 * 1024), b""):
            h.update(block)
    return h.hexdigest()


def json_digest(value: Any) -> str:
    return hashlib.sha256(json.dumps(value, sort_keys=True, separators=(",", ":")).encode()).hexdigest()


def write_json(path: Path, value: Any) -> None:
    temporary = path.with_name(path.name + ".tmp")
    temporary.write_text(json.dumps(value, indent=2, sort_keys=True) + "\n", encoding="utf-8")
    temporary.replace(path)


def load_json(path: Path) -> Any:
    try:
        return json.loads(path.read_text(encoding="utf-8"))
    except (OSError, ValueError) as exc:
        raise ValidationError(f"Cannot read JSON {path}: {exc}") from exc


def outside(path: Path, root: Path, label: str) -> Path:
    path = path.resolve()
    if path == root or root in path.parents:
        raise ValidationError(f"{label} must be outside the checkout: {path}")
    return path


class SharedLock:
    def __init__(self, path: Path):
        self.path = path
        self.held = False

    def __enter__(self):
        self.path.parent.mkdir(parents=True, exist_ok=True)
        try:
            fd = os.open(self.path, os.O_WRONLY | os.O_CREAT | os.O_EXCL, 0o600)
        except FileExistsError as exc:
            raise ValidationError(f"Validation lock busy: {self.path}; no automatic stale-lock removal") from exc
        self.held = True
        try:
            with os.fdopen(fd, "w") as stream:
                json.dump({"pid": os.getpid(), "started": time.time()}, stream)
        except BaseException:
            self.path.unlink()
            self.held = False
            raise
        return self

    def __exit__(self, *_):
        if self.held:
            self.path.unlink()
            self.held = False


def git(root: Path, *args: str) -> str:
    result = subprocess.run(["git", "-C", str(root), *args], capture_output=True, check=False)
    if result.returncode:
        raise ValidationError(f"Git provenance command failed: git {' '.join(args)}")
    return result.stdout.decode("utf-8", errors="surrogateescape").strip()


def snapshot(root: Path, tools: dict[str, Path], manifest: Path, generated: bool = False) -> dict[str, Any]:
    """Hash source/config/tool content, including submodules and relevant untracked files."""
    files: dict[str, str] = {}
    # Walking source roots includes submodule working contents, even dirty or
    # untracked headers. Generated build outputs and build.log are never inputs.
    roots = [root / name for name in ("src", "include", "asm", "config", "tools", "tests")]
    candidates = [p for p in root.iterdir() if p.is_file() and p.suffix in (".py", ".toml", ".yml", ".yaml")]
    for directory in roots:
        if directory.exists():
            for base, directories, names in os.walk(directory):
                directories[:] = sorted(d for d in directories if d not in (".git", "__pycache__"))
                candidates.extend(Path(base) / n for n in sorted(names) if not n.endswith((".pyc", ".log")))
    for path in sorted(set(candidates)):
        if path.is_file():
            files[str(path.relative_to(root))] = digest(path)
    tree = git(root, "rev-parse", "HEAD^{tree}")
    head = git(root, "rev-parse", "HEAD")
    status = git(root, "status", "--porcelain", "--untracked-files=all")
    # Git status is descriptive; content digest is the actual source identity.
    # A dirty/untracked tool checkout must never be advertised as HEAD contents.
    tool_hashes = {name: {"path": str(path), "sha256": digest(path)} for name, path in tools.items()}
    state = {"files": files, "tools": tool_hashes, "manifest_sha256": digest(manifest)}
    if generated:
        state["generated"] = {str(p.relative_to(root)): digest(p) for p in
            [root / "build.ninja", root / "objdiff.json", *sorted((root / "build").glob("*/config.json"))] if p.is_file()}
        runtime = [*sorted((root / "build/compilers").rglob("*")),
                   *sorted((root / "build/binutils").rglob("*"))]
        runtime.extend(root / "build/tools" / n for n in ("wibo", "sjiswrap.exe"))
        state["runtime"] = {str(p.relative_to(root)): digest(p) for p in runtime if p.is_file()}
        state["original_binaries"] = {str(p.relative_to(root)): digest(p) for p in
            sorted((root / "orig").rglob("*")) if p.is_file() and p.suffix in (".dol", ".rel")}
    return {"head": head, "head_tree": tree, "matches_head": False, "identity_kind": "working_snapshot",
            "source_fingerprint": json_digest(state), "inputs": state, "git_status": status}


def assert_stable(before: dict, after: dict) -> None:
    if before["source_fingerprint"] != after["source_fingerprint"] or before["head"] != after["head"]:
        raise ValidationError("Source, configuration, tool, or revision drift during validation")


def positive_integer(value: Any, field: str, allow_zero: bool = False) -> int:
    try:
        if isinstance(value, bool) or value is None:
            raise ValueError()
        number = int(str(value), 0) if isinstance(value, str) and value.startswith("0x") else int(value)
        if str(number) != str(value) and not (isinstance(value, str) and value.startswith("0x")):
            raise ValueError()
        if number < 0 or (not allow_zero and number == 0):
            raise ValueError()
        return number
    except (ValueError, TypeError):
        raise ValidationError(f"Missing or invalid original {field}: {value!r}") from None


def report_index(report: dict, version: str) -> dict[tuple, dict]:
    if not isinstance(report.get("units"), list) or not report["units"]:
        raise ValidationError("Report has no units")
    result = {}
    unit_names = set()
    for unit in report["units"]:
        name = unit.get("name")
        if not isinstance(name, str) or not name or name in unit_names:
            raise ValidationError(f"Missing/duplicate report unit name: {name!r}")
        unit_names.add(name)
        metadata = unit.get("metadata", {})
        module = metadata.get("module_name")
        module_id = positive_integer(metadata.get("module_id"), "module id", True)
        if not isinstance(module, str) or not module:
            raise ValidationError(f"Missing original module name in {name}")
        functions = unit.get("functions", [])
        if not isinstance(functions, list):
            raise ValidationError(f"Invalid function list in {name}")
        for function in functions:
            address = positive_integer(function.get("metadata", {}).get("virtual_address"), "address", True)
            size = positive_integer(function.get("size"), "size")
            key = (version, module_id, module, address, size)
            if key in result:
                raise ValidationError(f"Ambiguous duplicate original function key: {key}")
            percent = function.get("fuzzy_match_percent", 0)
            if not isinstance(percent, (float, int)) or isinstance(percent, bool) or not math.isfinite(percent) or not 0 <= percent <= 100:
                raise ValidationError(f"Invalid matching percentage for {key}")
            result[key] = {"unit": name, "name": function.get("name"), "exact": percent == 100, "size": size}
    if not result:
        raise ValidationError("Report has no original functions")
    return result


def compare_reports(baseline: dict, candidate: dict, version: str, scope: list[str] | None = None) -> dict:
    old = report_index(baseline, version)
    new = report_index(candidate, version)
    if scope is not None:
        names = {u["name"] for u in candidate["units"]}
        if names != set(scope):
            raise ValidationError("Scoped report omitted or added units")
        old = {k: v for k, v in old.items() if v["unit"] in scope}
        if {v["unit"] for v in old.values()} != set(scope):
            raise ValidationError("Scoped baseline lacks requested units")
    # Renames/split movement do not change binary identity. Original key set
    # changes mean incomparable/stale target metadata, not reported progress.
    if old.keys() != new.keys():
        raise ValidationError(f"Original function universe changed: missing={len(old.keys()-new.keys())}, added={len(new.keys()-old.keys())}")
    lost = [k for k in old if old[k]["exact"] and not new[k]["exact"]]
    gained = [k for k in new if new[k]["exact"] and not old[k]["exact"]]
    return {"baseline_exact": sum(v["exact"] for v in old.values()),
            "final_exact": sum(v["exact"] for v in new.values()),
            "gained": [list(k) for k in gained], "lost": [list(k) for k in lost],
            "newly_matched_bytes": sum(new[k]["size"] for k in gained),
            "lost_matched_bytes": sum(old[k]["size"] for k in lost)}


def hash_entries(path: Path, root: Path) -> list[tuple[str, Path]]:
    result = []
    seen = set()
    for line in path.read_text(encoding="utf-8").splitlines():
        if not line.strip():
            continue
        match = re.fullmatch(r"([0-9a-fA-F]{40})\s+\*?(.+)", line)
        if not match:
            raise ValidationError(f"Invalid hash manifest line: {line!r}")
        target = (root / match[2]).resolve()
        if root not in target.parents or target in seen:
            raise ValidationError("Hash manifest contains escaping/duplicate output path")
        seen.add(target)
        result.append((match[1].lower(), target))
    if len(result) != 127:
        raise ValidationError(f"Full gate requires exactly127 unique hash entries; found {len(result)}")
    return result


def verify_hashes(entries: list[tuple[str, Path]]) -> dict:
    bad = [str(path) for expected, path in entries if not path.is_file() or digest(path, "sha1") != expected]
    if bad:
        raise ValidationError(f"Output hash failures: {bad}")
    return {"ok": len(entries), "bad": 0}


def resolve_tool(value: str, root: Path) -> Path:
    candidate = root / value
    path = candidate.resolve() if candidate.is_file() else Path(shutil.which(value) or "")
    if not path.is_file() or not os.access(path, os.X_OK):
        raise ValidationError(f"Missing executable tool: {value}")
    return path.resolve()


def command(argv: list[str], root: Path, output: Path, records: list, label: str) -> None:
    start = time.time()
    log = output / f"{len(records):02d}-{label}.log"
    record = {"role": label, "argv": argv, "cwd": str(root), "log": log.name, "started": start}
    records.append(record)
    try:
        with log.open("wb") as stream:
            result = subprocess.run(argv, cwd=root, stdout=stream, stderr=subprocess.STDOUT, check=False)
        record["returncode"] = result.returncode
        if result.returncode:
            raise ValidationError(f"{label} failed with exit{result.returncode}; see {log}")
    finally:
        record["seconds"] = time.time() - start
        if log.exists():
            record["log_sha256"] = digest(log)


def evidence(path: Path) -> tuple[dict, dict]:
    manifest = load_json(path / "validation.json")
    if manifest.get("schema") != SCHEMA or manifest.get("status") != "passed":
        raise ValidationError("Baseline/candidate evidence is not a finalized successful run")
    mode = manifest.get("mode")
    if mode not in ("full", "objects") or manifest.get("full_gate") != (mode == "full"):
        raise ValidationError("Evidence has invalid scoped/full gate identity")
    expected_roles = ["configure", "prepare-original", "dependency-provenance", "build"]
    if mode == "full":
        expected_roles.append("all127-hashes")
    generation = manifest.get("report_generation", {"kind": "generated"})
    if generation.get("kind") == "generated":
        expected_roles.append("fresh-report")
    elif generation.get("kind") != "reused":
        raise ValidationError("Invalid report generation provenance")
    if [c.get("role") for c in manifest.get("commands", [])] != expected_roles:
        raise ValidationError("Evidence lacks required validation commands")
    report_path = path / "report.json"
    if json_digest(manifest.get("source", {}).get("inputs")) != manifest.get("source", {}).get("source_fingerprint"):
        raise ValidationError("Source provenance fingerprint is inconsistent")
    if digest(path / "objdiff.json") != manifest.get("report_config_sha256"):
        raise ValidationError("Report configuration evidence was modified")
    if digest(report_path) != manifest.get("report_sha256"):
        raise ValidationError("Baseline/candidate report was modified after validation")
    for record in manifest.get("commands", []):
        if record.get("returncode") != 0 or digest(path / record["log"]) != record.get("log_sha256"):
            raise ValidationError("Baseline/candidate command evidence is missing or modified")
    if not manifest.get("commands") or not manifest.get("source", {}).get("source_fingerprint"):
        raise ValidationError("Baseline/candidate lacks correlated command/source provenance")
    if manifest.get("mode") == "full" and manifest.get("hashes") != {"ok": 127, "bad": 0}:
        raise ValidationError("Full evidence lacks all127 hash checks")
    signature = manifest.get("report_reuse")
    if signature is not None:
        try:
            expected = report_signature(manifest)
        except (KeyError, TypeError) as exc:
            raise ValidationError("Incomplete report reuse provenance") from exc
        if signature != expected:
            raise ValidationError("Report reuse fingerprint is inconsistent")
    if generation.get("kind") == "reused":
        if signature is None:
            raise ValidationError("Reused report lacks verified input closure")
        origin = generation.get("origin", {})
        if origin.get("report_sha256") != manifest.get("report_sha256") or origin.get("reuse_sha256") != signature["sha256"] or origin.get("validation_sha256") != manifest.get("baseline", {}).get("validation_sha256"):
            raise ValidationError("Reused report origin does not match current evidence")
        ancestry = generation.get("ancestry")
        if not isinstance(ancestry, list) or not ancestry or ancestry[0] != origin:
            raise ValidationError("Reused report lacks explicit ancestry")
        for ancestor in ancestry:
            if any(not re.fullmatch(r"[0-9a-f]{64}", str(ancestor.get(k, ""))) for k in ("validation_sha256", "report_sha256", "reuse_sha256")):
                raise ValidationError("Invalid reused-report ancestry digest")
        if generation.get("log") != "report-reuse.json" or digest(path / generation["log"]) != generation.get("log_sha256"):
            raise ValidationError("Report reuse operation evidence is missing or modified")
        operation = load_json(path / generation["log"])
        if operation != {k: generation[k] for k in ("kind", "origin", "ancestry")}:
            raise ValidationError("Report reuse operation metadata differs")
    report = load_json(report_path)
    report_index(report, manifest["version"])
    if {u["name"] for u in report["units"]} != set(manifest.get("units", [])):
        raise ValidationError("Evidence report does not cover recorded scope")
    return manifest, report


def project_config(root: Path, targets: list[str], output: Path) -> tuple[Path, list[str]]:
    config = load_json(root / "objdiff.json")
    units = config.get("units", [])
    if targets:
        selected = []
        remaining = {(root / target).resolve() for target in targets}
        for unit in units:
            if unit.get("base_path") and (root / unit["base_path"]).resolve() in remaining:
                selected.append(unit)
                remaining.remove((root / unit["base_path"]).resolve())
        if remaining:
            raise ValidationError(f"Targets absent from objdiff config: {sorted(map(str, remaining))}")
        units = selected
    if not units:
        raise ValidationError("Objdiff configuration has no selected units")
    # Fresh report runs outside checkout; absolute paths preserve target ownership.
    for unit in units:
        for key in ("base_path", "target_path"):
            if unit.get(key):
                unit[key] = str((root / unit[key]).resolve())
    config["units"] = units
    config.pop("custom_make", None)
    config.pop("build_target", None)
    write_json(output / "objdiff.json", config)
    return output, [unit["name"] for unit in units]


def report_inputs(config: dict, allow_unavailable: bool = False) -> dict[str, str | None]:
    files = {}
    for unit in config["units"]:
        for field in ("target_path", "base_path"):
            if unit.get(field):
                path = Path(unit[field])
                if not path.is_file():
                    if field == "base_path" and allow_unavailable:
                        files[str(path)] = None
                        continue
                    raise ValidationError(f"Missing report input: {path}")
                files[str(path)] = digest(path)
    return files


REPORT_REUSE_SCHEMA = 1


def report_signature(state: dict) -> dict:
    """Complete report closure. Source fingerprints alone cannot prove reuse."""
    inputs = state["source"]["inputs"]
    closure = {"version": state["version"], "config_sha256": state["report_config_sha256"],
               "object_inputs": state["report_inputs"], "units": state["units"],
               "unavailable_base_units": state["unavailable_base_units"],
               "split_config": state["split_config"], "generated": inputs["generated"],
               "runtime": inputs["runtime"], "original_binaries": inputs["original_binaries"],
               "objdiff_tool": inputs["tools"]["objdiff"], "options": ["report", "generate"]}
    return {"schema": REPORT_REUSE_SCHEMA, "inputs": closure, "sha256": json_digest(closure)}


def may_reuse_report(baseline: dict | None, current: dict, force_fresh: bool) -> bool:
    if baseline is None or force_fresh:
        return False
    prior = baseline.get("report_reuse")
    # Old successful fresh evidence remains valid, but it is not cache evidence.
    return isinstance(prior, dict) and prior.get("schema") == REPORT_REUSE_SCHEMA and prior == current


def reuse_report(baseline_path: Path, output: Path, state: dict) -> None:
    """Recheck the finalized baseline immediately before copying whole bytes."""
    started = time.time()
    manifest, _ = evidence(baseline_path)
    manifest_digest = digest(baseline_path / "validation.json")
    if manifest_digest != state["baseline"]["validation_sha256"] or manifest.get("report_reuse") != state["report_reuse"]:
        raise ValidationError("Baseline report evidence changed before reuse")
    origin = {"path": str(baseline_path), "validation_sha256": manifest_digest,
              "report_sha256": manifest["report_sha256"],
              "reuse_sha256": state["report_reuse"]["sha256"]}
    shutil.copyfile(baseline_path / "report.json", output / "report.json")
    if digest(output / "report.json") != origin["report_sha256"] or digest(baseline_path / "validation.json") != manifest_digest:
        raise ValidationError("Baseline report evidence changed during reuse")
    generation = {"kind": "reused", "origin": origin,
                  "ancestry": [origin, *manifest.get("report_generation", {}).get("ancestry", [])]}
    write_json(output / "report-reuse.json", generation)
    generation.update({"seconds": time.time() - started, "log": "report-reuse.json",
                       "log_sha256": digest(output / "report-reuse.json")})
    state["report_generation"] = generation


def validate_dependency_paths(log: Path, root: Path) -> None:
    """Check each distinct logged dependency once; retain absolute-path policy."""
    text = log.read_text(encoding="utf-8", errors="replace")
    dependencies = dict.fromkeys(line.strip() for line in text.splitlines() if line.startswith("    "))
    for spelling in dependencies:
        dependency = Path(spelling)
        if dependency.is_absolute() and root not in dependency.resolve().parents:
            raise ValidationError(f"Foreign cached dependency path: {dependency}")


def run(args) -> dict:
    if not re.fullmatch(r"[A-Za-z0-9_]+", args.version):
        raise ValidationError("Invalid binary version identifier")
    root = Path(args.project).resolve()
    output = outside(Path(args.output), root, "Output directory")
    lock = outside(Path(args.lock), root, "Lock path")
    if output.exists():
        raise ValidationError("Output directory already exists; choose a fresh evidence directory")
    if lock == output or output in lock.parents:
        raise ValidationError("Lock must not be inside the evidence directory")
    if args.mode == "objects" and not args.target:
        raise ValidationError("Object-scoped validation requires --target")
    if args.mode == "full" and args.target:
        raise ValidationError("Full validation cannot specify object targets")
    manifest_path = root / "config" / args.version / "build.sha1"
    entries = hash_entries(manifest_path, root)
    tools = {name: resolve_tool(getattr(args, name), root) for name in ("ninja", "dtk", "objdiff")}
    tools["nice"] = resolve_tool("nice", root)
    # Preserve interpreter invocation spelling: configure embeds it into
    # Ninja command hashes. digest() still hashes the actual symlink target.
    tools["python"] = Path(sys.executable).absolute()
    state = {"schema": SCHEMA, "kind": args.action, "mode": args.mode, "version": args.version,
             "status": "running", "commands": [], "targets": args.target, "started": time.time()}
    baseline_manifest = baseline_report = None
    if args.action == "run":
        baseline_manifest, baseline_report = evidence(Path(args.baseline).resolve())
        if baseline_manifest["version"] != args.version:
            raise ValidationError("Baseline binary version differs")
        if baseline_manifest["source"]["head"] != args.expected_baseline_revision:
            raise ValidationError("Baseline revision does not equal explicitly expected full SHA")
        if args.expected_baseline_fingerprint != baseline_manifest["source"]["source_fingerprint"]:
            raise ValidationError("Working-snapshot baseline requires explicit --expected-baseline-fingerprint")
        if args.mode == "full" and baseline_manifest["mode"] != "full":
            raise ValidationError("Scoped baseline cannot establish a full regression gate")
        if {n: t["sha256"] for n, t in baseline_manifest["source"]["inputs"]["tools"].items()} != {n: digest(t) for n, t in tools.items()}:
            raise ValidationError("Baseline tool binaries differ from this validation")
        if baseline_manifest["source"]["inputs"]["manifest_sha256"] != digest(manifest_path):
            raise ValidationError("Baseline binary/hash manifest differs")
        state["baseline"] = {"path": str(Path(args.baseline).resolve()), "validation_sha256": digest(Path(args.baseline) / "validation.json")}
    with SharedLock(lock):
        output.mkdir(parents=True)
        try:
            initial = snapshot(root, tools, manifest_path)
            command([str(tools["nice"]), "-n", "10", str(tools["python"]), "configure.py", "configure", "--version", args.version, *args.configure_arg], root, output, state["commands"], "configure")
            assert_stable(initial, snapshot(root, tools, manifest_path))
            graph = (root / "build.ninja").read_text(encoding="utf-8")
            if "mwcc" in graph:
                required = [root / "build/tools/wibo", root / "build/tools/sjiswrap.exe"]
                compiler_files = list((root / "build/compilers").rglob("mwcceppc.exe"))
                linker_files = list((root / "build/compilers").rglob("mwldeppc.exe"))
                if not compiler_files or not linker_files or not all(p.is_file() for p in required):
                    raise ValidationError("Toolchain is incomplete; validation will not download tools")
            # Original objdiff targets are SPLIT side-effect files, not
            # individually addressable Ninja outputs. Refresh their producer
            # before freezing generated configuration and comparison ownership.
            original_config = root / "config" / args.version / "config.yml"
            if original_config.is_file():
                original_config.touch()
            command([str(tools["nice"]), "-n", "10", str(tools["ninja"]), f"-j{args.jobs}", f"build/{args.version}/config.json"], root, output, state["commands"], "prepare-original")
            assert_stable(initial, snapshot(root, tools, manifest_path))
            if not (root / "build" / args.version / "config.json").is_file():
                raise ValidationError("Original preparation did not produce split metadata")
            before = snapshot(root, tools, manifest_path, True)
            state["source"] = before
            if baseline_manifest is not None:
                for field in ("runtime", "original_binaries"):
                    if before["inputs"][field] != baseline_manifest["source"]["inputs"].get(field):
                        raise ValidationError(f"Baseline {field} differ from this validation")
            write_json(output / "validation.json", state)
            project, scope = project_config(root, args.target, output)
            selected = load_json(output / "objdiff.json")
            expected_build = (root / "build" / args.version).resolve()
            for unit in selected["units"]:
                for field in ("base_path", "target_path"):
                    if unit.get(field) and expected_build not in Path(unit[field]).parents:
                        raise ValidationError(f"Report {field} is outside configured binary version: {unit[field]}")
            command([str(tools["ninja"]), "-t", "deps"], root, output, state["commands"], "dependency-provenance")
            dependency_log = output / state["commands"][-1]["log"]
            validate_dependency_paths(dependency_log, root)
            for unit in selected["units"]:
                if unit.get("target_path") and not Path(unit["target_path"]).is_file():
                    raise ValidationError(f"Original preparation omitted target: {unit['target_path']}")
            targets = args.target if args.mode == "objects" else [f"build/{args.version}/ok", *[u["base_path"] for u in selected["units"] if u.get("base_path") and Path(u["base_path"]).is_file()]]
            targets = [str(Path(t).relative_to(root)) if Path(t).is_absolute() else t for t in targets]
            command([str(tools["nice"]), "-n", "10", str(tools["ninja"]), f"-j{args.jobs}", *targets], root, output, state["commands"], "build")
            assert_stable(before, snapshot(root, tools, manifest_path, True))
            if args.mode == "full":
                command([str(tools["nice"]), "-n", "10", str(tools["dtk"]), "shasum", "-c", str(manifest_path)], root, output, state["commands"], "all127-hashes")
                state["hashes"] = verify_hashes(entries)
            project, scope = project_config(root, args.target, output)
            state["units"] = scope
            state["report_config_sha256"] = digest(output / "objdiff.json")
            state["split_config"] = {str(p.relative_to(root)): digest(p) for p in sorted((root / "build" / args.version).glob("config.json"))}
            state["unavailable_base_units"] = [u["name"] for u in selected["units"] if u.get("base_path") and not Path(u["base_path"]).is_file()]
            state["report_inputs"] = report_inputs(load_json(output / "objdiff.json"), args.mode == "full")
            generated_config = digest(root / "objdiff.json")
            state["report_reuse"] = report_signature(state)
            if may_reuse_report(baseline_manifest, state["report_reuse"], args.fresh_report):
                reuse_report(Path(args.baseline).resolve(), output, state)
            else:
                started = time.time()
                command([str(tools["nice"]), "-n", "10", str(tools["objdiff"]), "report", "generate", "-p", str(project), "-o", str(output / "report.json")], root, output, state["commands"], "fresh-report")
                state["report_generation"] = {"kind": "generated", "seconds": time.time() - started}
            if state["split_config"] != {str(p.relative_to(root)): digest(p) for p in sorted((root / "build" / args.version).glob("config.json"))}:
                raise ValidationError("Split metadata drift during report generation")
            if generated_config != digest(root / "objdiff.json") or state["report_inputs"] != report_inputs(load_json(output / "objdiff.json"), args.mode == "full"):
                raise ValidationError("Report configuration or object input drift during report generation")
            report = load_json(output / "report.json")
            index = report_index(report, args.version)
            unavailable = set(state["unavailable_base_units"])
            if any(v["exact"] and v["unit"] in unavailable for v in index.values()):
                raise ValidationError("Report claims exact functions for unavailable comparison bases")
            if {u["name"] for u in report["units"]} != set(scope):
                raise ValidationError("Generated report omitted configured units")
            assert_stable(before, snapshot(root, tools, manifest_path, True))
            if baseline_report is not None:
                state["comparison"] = compare_reports(baseline_report, report, args.version, scope if args.mode == "objects" else None)
                if state["comparison"]["lost"]:
                    raise ValidationError("Previously exact original functions were lost")
            state["report_sha256"] = digest(output / "report.json")
            state["status"] = "passed"
            state["full_gate"] = args.mode == "full"
        except BaseException as exc:
            state["status"] = "failed"
            state["error"] = str(exc)
            state["full_gate"] = False
            raise
        finally:
            state["seconds"] = time.time() - state["started"]
            write_json(output / "validation.json", state)
    return state


def parser() -> argparse.ArgumentParser:
    cli = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    commands = cli.add_subparsers(dest="action", required=True)
    for name in ("baseline", "run"):
        p = commands.add_parser(name)
        p.add_argument("--project", default=".")
        p.add_argument("--version", default="RSBE01_02")
        p.add_argument("--mode", choices=("full", "objects"), required=True)
        p.add_argument("--target", action="append", default=[])
        p.add_argument("--configure-arg", action="append", default=[], help="additional configure argv token (use --configure-arg=--flag)")
        p.add_argument("--fresh-report", action="store_true", help="always regenerate rather than reuse an identical verified baseline report")
        p.add_argument("--jobs", type=int, choices=range(1, 5), default=1)
        p.add_argument("--output", required=True)
        p.add_argument("--lock", required=True)
        p.add_argument("--ninja", default="ninja")
        p.add_argument("--dtk", default="build/tools/dtk")
        p.add_argument("--objdiff", default="build/tools/objdiff-cli")
        if name == "run":
            p.add_argument("--baseline", required=True)
            p.add_argument("--expected-baseline-revision", required=True)
            p.add_argument("--expected-baseline-fingerprint", required=True)
    p = commands.add_parser("compare")
    p.add_argument("baseline", type=Path)
    p.add_argument("candidate", type=Path)
    return cli


def main(argv=None) -> int:
    args = parser().parse_args(argv)
    try:
        if args.action == "compare":
            old, before = evidence(args.baseline)
            new, after = evidence(args.candidate)
            if old["version"] != new["version"] or old["source"]["inputs"]["manifest_sha256"] != new["source"]["inputs"]["manifest_sha256"]:
                raise ValidationError("Incompatible original binary/version evidence")
            for field in ("runtime", "original_binaries"):
                if old["source"]["inputs"].get(field) != new["source"]["inputs"].get(field):
                    raise ValidationError(f"Incompatible {field} evidence")
            if {n: t["sha256"] for n, t in old["source"]["inputs"]["tools"].items()} != {n: t["sha256"] for n, t in new["source"]["inputs"]["tools"].items()}:
                raise ValidationError("Incompatible tool binary evidence")
            if new["mode"] == "full" and old["mode"] != "full":
                raise ValidationError("Scoped baseline cannot establish a full regression gate")
            result = compare_reports(before, after, new["version"], new["units"] if new["mode"] == "objects" else None)
            print(json.dumps(result, indent=2))
            return 1 if result["lost"] else 0
        state = run(args)
        print(f"{state['mode']} validation passed; full gate={state['full_gate']}; evidence: {args.output}")
        return 0
    except (ValidationError, OSError) as exc:
        print(f"Validation failed: {exc}", file=sys.stderr)
        return 1


if __name__ == "__main__":
    raise SystemExit(main())
