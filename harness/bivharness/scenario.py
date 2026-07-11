import hashlib
import json
import os
import shutil
import subprocess
import sys
from pathlib import Path
from typing import Any, NamedTuple

from jsonschema import Draft202012Validator

from bivharness.artifact import extract_member, list_members, mutate_in_stream, payload_extent_digests
from bivharness.compare import assert_members, compare_trees, load_tolerance
from bivharness.fixtures import materialize
from bivharness.manifest import validate_manifest
from bivharness.precheck import pin_env, probe
from bivharness.report import ScenarioResult, Status


COMMAND_TIMEOUT_S = 30
BUILTIN_BIVIGNORE_SHA256 = "e271561320eecb76b6736a4b85bfc98069e1259b8fc9609ebea926e8aa5bb1d3"
SCHEMA_FILES = ("biv-json-envelope.v1.schema.json", "biv-exit-map.v1.json")


class CommandResult(NamedTuple):
    exit_code: int
    envelope: dict[str, Any]
    detail: str
    invalid: list[str]


def _command(biv: Path, args: list[str]) -> list[str]:
    if biv.suffix == ".py":
        return [sys.executable, str(biv), *args]
    return [str(biv), *args]


def _parse_stdout(stdout: str) -> tuple[dict[str, Any], list[str]]:
    stripped = stdout.strip()
    if not stripped:
        return {}, ["stdout JSON missing"]
    decoder = json.JSONDecoder()
    try:
        payload, end = decoder.raw_decode(stripped)
    except json.JSONDecodeError as exc:
        return {}, [f"stdout JSON invalid: {exc.msg}"]
    if stripped[end:].strip():
        return {}, ["stdout must contain exactly one JSON document"]
    if not isinstance(payload, dict):
        return {}, ["stdout JSON root must be an object"]
    return payload, []


def _run_json(
    biv: Path,
    args: list[str],
    cwd: Path,
    env_overrides: dict[str, str] | None = None,
) -> CommandResult:
    env = os.environ.copy()
    if env_overrides:
        env.update(env_overrides)
    try:
        run = subprocess.run(
            _command(biv, [*args, "--json"]),
            cwd=cwd,
            check=False,
            text=True,
            capture_output=True,
            env=env,
            timeout=COMMAND_TIMEOUT_S,
        )
    except subprocess.TimeoutExpired as exc:
        detail = "\n".join(part for part in ((exc.stdout or "").strip(), (exc.stderr or "").strip()) if part)
        return CommandResult(
            -1,
            {},
            detail,
            [f"command timeout after {COMMAND_TIMEOUT_S}s: {' '.join(args)}"],
        )

    payload, invalid = _parse_stdout(run.stdout)
    detail = "\n".join(part for part in (run.stdout.strip(), run.stderr.strip()) if part)
    return CommandResult(run.returncode, payload, detail, invalid)


def _schema_root() -> Path:
    if "BIVHARNESS_SCHEMA_ROOT" in os.environ:
        return Path(os.environ["BIVHARNESS_SCHEMA_ROOT"])
    return Path(__file__).resolve().parents[2] / "schemas"


def _schema_artifact_failures() -> list[str]:
    root = _schema_root()
    return [f"missing schema artifact: {root / name}" for name in SCHEMA_FILES if not (root / name).exists()]


def _validate_envelope(envelope: dict[str, Any]) -> list[str]:
    missing = _schema_artifact_failures()
    if missing:
        return missing
    schema = _schema_root() / "biv-json-envelope.v1.schema.json"
    loaded = json.loads(schema.read_text(encoding="utf-8"))
    return [
        f"envelope schema: {'.'.join(str(p) for p in error.path) or '<root>'}: {error.message}"
        for error in Draft202012Validator(loaded).iter_errors(envelope)
    ]


def _exit_for_kind(kind: str) -> tuple[int | None, str | None]:
    exit_map = _schema_root() / "biv-exit-map.v1.json"
    if not exit_map.exists():
        return None, f"missing schema artifact: {exit_map}"
    rows = json.loads(exit_map.read_text(encoding="utf-8")).get("rows", [])
    for row in rows:
        if row.get("kind") == kind:
            return int(row["exit"]), None
    return None, f"exit-map missing kind: {kind}"


def _check_prune_summary(envelope: dict[str, Any], expected: list[dict[str, str]]) -> list[str]:
    if not expected:
        return []
    advisories = envelope.get("advisories", [])
    entries: list[dict[str, str]] = []
    for advisory in advisories:
        if advisory.get("kind") == "prune-summary":
            entries.extend({"path": item.get("path", ""), "source": item.get("source", "")}
                           for item in advisory.get("entries", []))
    if sorted(entries, key=lambda item: (item["path"], item["source"])) != sorted(
        expected, key=lambda item: (item["path"], item["source"])
    ):
        return [f"prune-summary mismatch: expected {expected}, got {entries}"]
    return []


def _copy_expected_tree(source: Path, expected: Path) -> None:
    if expected.exists():
        shutil.rmtree(expected)
    shutil.copytree(source, expected, symlinks=True, copy_function=shutil.copy2)


def _remove_expected_absences(expected: Path, absent_members: list[str]) -> None:
    for member in absent_members:
        if not member.startswith("payload/"):
            continue
        rel = member.removeprefix("payload/").rstrip("/")
        target = expected / rel
        if target.is_symlink() or target.is_file():
            target.unlink()
        elif target.is_dir():
            shutil.rmtree(target)


def _fingerprint(root: Path) -> list[tuple[str, str, Any]]:
    facts: list[tuple[str, str, Any]] = []
    if not root.exists():
        return facts
    for path in sorted(root.rglob("*"), key=lambda item: item.relative_to(root).as_posix()):
        rel = path.relative_to(root).as_posix()
        if path.is_symlink():
            facts.append((rel, "symlink", os.readlink(path)))
        elif path.is_dir():
            facts.append((rel, "dir", None))
        elif path.is_file():
            facts.append((rel, "file", path.read_bytes()))
        else:
            facts.append((rel, "other", None))
    return facts


def _work_entries(path: Path) -> set[str]:
    if not path.exists():
        return set()
    return {item.name for item in path.iterdir()}


def _project_key(path: Path) -> str:
    return "".join(ch if ch.isascii() and ch.isalnum() else "-" for ch in path.as_posix())


def _prepare_agent_profiles(work: Path, source: Path, agents: list[str]) -> tuple[dict[str, str], dict[str, str], dict[str, Path]]:
    source_env: dict[str, str] = {}
    target_env: dict[str, str] = {}
    targets: dict[str, Path] = {}
    if "claude-code" in agents:
        session_id = "aaaaaaaa-1111-4000-8000-000000000001"
        source_store = work / "profiles" / "source-claude"
        target_store = work / "profiles" / "target-claude"
        transcript = source_store / "projects" / _project_key(source) / f"{session_id}.jsonl"
        transcript.parent.mkdir(parents=True)
        transcript.write_text(
            "\n".join(
                (
                    json.dumps({"type": "user", "cwd": source.as_posix(),
                                "uuid": "11111111-1111-4111-8111-111111111111",
                                "parentUuid": None, "sessionId": session_id,
                                "version": "2.1.202", "message": "seed one"}),
                    json.dumps({"type": "assistant", "cwd": source.as_posix(),
                                "uuid": "22222222-2222-4222-8222-222222222222",
                                "parentUuid": "11111111-1111-4111-8111-111111111111",
                                "sessionId": session_id,
                                "message": "seed two"}),
                )
            ) + "\n",
            encoding="utf-8",
        )
        target_store.mkdir(parents=True)
        (target_store / "settings.json").write_text("{}\n", encoding="utf-8")
        source_env["CLAUDE_CONFIG_DIR"] = str(source_store)
        target_env["CLAUDE_CONFIG_DIR"] = str(target_store)
        targets["claude-code"] = target_store
    if "codex" in agents:
        session_id = "019faaaa-bbbb-7ccc-8ddd-eeeeeeee0001"
        source_store = work / "profiles" / "source-codex"
        target_store = work / "profiles" / "target-codex"
        transcript = source_store / "sessions" / "2026" / "07" / "11" / (
            f"rollout-2026-07-11T01-00-00-{session_id}.jsonl"
        )
        transcript.parent.mkdir(parents=True)
        transcript.write_text(
            "\n".join(
                (
                    json.dumps({"timestamp": "2026-07-11T01:00:00Z", "type": "session_meta",
                                "payload": {"id": session_id, "session_id": session_id,
                                            "cwd": source.as_posix(), "cli_version": "0.142.5"}}),
                    json.dumps({"timestamp": "2026-07-11T01:01:00Z", "type": "turn_context",
                                "payload": {"cwd": source.as_posix(),
                                            "workspace_roots": [source.as_posix()]}}),
                )
            ) + "\n",
            encoding="utf-8",
        )
        target_store.mkdir(parents=True)
        (target_store / "config.toml").write_text("", encoding="utf-8")
        source_env["CODEX_HOME"] = str(source_store)
        target_env["CODEX_HOME"] = str(target_store)
        targets["codex"] = target_store
    return source_env, target_env, targets


def _session_rows(envelope: dict[str, Any]) -> list[dict[str, Any]]:
    rows: list[dict[str, Any]] = []
    sessions = envelope.get("result", {}).get("sessions", {})
    for agent in sessions.get("agents", []):
        for session in agent.get("sessions", []):
            rows.append({"agent": agent.get("agent"), **session})
    return rows


def _check_bivignore_sha(img: Path, manifest: dict[str, Any]) -> list[str]:
    bivignore = manifest.get("bivignore", {})
    expected = bivignore.get("sha256")
    if bivignore.get("source") == "file":
        try:
            data = extract_member(img, "payload/.bivignore")
        except KeyError:
            return ["bivignore.sha256 cannot be verified: payload/.bivignore missing"]
        actual = hashlib.sha256(data).hexdigest()
    elif bivignore.get("source") == "builtin":
        actual = BUILTIN_BIVIGNORE_SHA256
    else:
        return [f"bivignore.source unknown: {bivignore.get('source')}"]
    if actual != expected:
        return [f"bivignore.sha256 mismatch: {actual} != {expected}"]
    return []


def _hex_sha256(value: Any) -> bool:
    return isinstance(value, str) and len(value) == 64 and all(ch in "0123456789abcdef" for ch in value)


def _check_payload_checksums(img: Path) -> list[str]:
    try:
        checksums = json.loads(extract_member(img, "checksums.json"))
    except (KeyError, json.JSONDecodeError) as exc:
        return [f"checksum manifest invalid: {exc}"]
    if checksums.get("algo") != "sha256":
        return [f"checksum algo mismatch: {checksums.get('algo')}"]
    entries = checksums.get("entries")
    if not isinstance(entries, dict):
        return ["checksum entries missing or non-object"]

    findings: list[str] = []
    actual = payload_extent_digests(img)
    for path, digest in entries.items():
        if not _hex_sha256(digest):
            findings.append(f"checksum digest invalid for {path}")
            continue
        if not path.startswith("payload/"):
            continue
        if path not in actual:
            findings.append(f"checksum entry without payload: {path}")
            continue
        if actual[path] != digest:
            findings.append(f"checksum mismatch for {path}")
    for path in sorted(set(actual) - set(entries)):
        findings.append(f"checksum missing for {path}")
    return findings


def _classes_for_tree_findings(findings: list[str]) -> set[str]:
    found: set[str] = set()
    for finding in findings:
        if len(finding) >= 2 and finding[1] == ":":
            found.add(finding[0])
    return found


def run_scenario(spec_path: Path, biv: Path, scratch: Path) -> ScenarioResult:
    spec = json.loads(spec_path.read_text(encoding="utf-8"))
    classes = list(spec.get("classes", []))
    held = list(spec.get("held", []))
    result = ScenarioResult(
        id=spec["id"],
        tier=spec["tier"],
        status=Status.INVALID,
        classes=[],
        held_asserts=held,
        detail="",
    )

    if spec.get("status") == "xfail-pending":
        result.status = Status.XFAIL_PENDING
        result.detail = "pending shell; not executed"
        return result

    failures = probe(scratch)
    if failures:
        result.status = Status.INVALID
        result.detail = ",".join(failures)
        return result
    schema_failures = _schema_artifact_failures()
    if schema_failures:
        result.status = Status.INVALID
        result.detail = "\n".join(schema_failures)
        return result
    pin_env()

    work = scratch / spec["id"]
    if work.exists():
        shutil.rmtree(work)
    work.mkdir(parents=True)
    source = work / "source"
    restored = work / "restored"
    expected = work / "expected"
    materialize(spec["fixture"], source)
    _copy_expected_tree(source, expected)
    source_env, target_env, target_stores = _prepare_agent_profiles(
        work, source, list(spec.get("agents", []))
    )
    target_before = {agent: _fingerprint(path) for agent, path in target_stores.items()}
    for agent, mode in spec.get("target_modes", {}).items():
        os.chmod(target_stores[agent], int(mode, 8))

    findings: list[str] = []
    invalids: list[str] = []
    exercised: set[str] = set()
    image = source.parent / f"{source.name}.bvpk"
    pack_envelope: dict[str, Any] = {}
    artifact_ready = False
    source_before_refusal = _fingerprint(source)

    for step in spec.get("steps", []):
        op = step["op"]
        if op == "pack":
            run = _run_json(biv, ["pack", str(source), *step.get("args", [])], work, source_env)
            if run.invalid:
                invalids.extend(run.invalid)
                break
            envelope_errors = _validate_envelope(run.envelope)
            if envelope_errors:
                invalids.extend(envelope_errors)
                break
            exercised.add("E")
            pack_envelope = run.envelope
            if run.exit_code not in (0, 2):
                findings.append(f"pack exited {run.exit_code}: {run.detail}")
                artifact_ready = False
                break
            result_obj = run.envelope.get("result")
            if not isinstance(result_obj, dict):
                invalids.append("pack result missing or non-object")
                break
            image = Path(result_obj.get("image_path", image))
            artifact_ready = True
        elif op == "synthesize-fv99":
            mutated = work / "source-fv99.bvpk"
            mutate_in_stream(image, mutated, b'"format_version": 1', b'"format_version": 9')
            image = mutated
        elif op == "open":
            open_cwd = work / "open-cwd"
            open_cwd.mkdir(exist_ok=True)
            before = _work_entries(open_cwd)
            restored = open_cwd / image.with_suffix("").name
            if step.get("precreate_default"):
                restored.mkdir(parents=True, exist_ok=True)
                (restored / "collision.txt").write_text("collision\n", encoding="utf-8")
            run = _run_json(
                biv,
                ["open", str(image), *step.get("args", [])],
                open_cwd,
                target_env,
            )
            if run.invalid:
                invalids.extend(run.invalid)
                break
            envelope_errors = _validate_envelope(run.envelope)
            if envelope_errors:
                invalids.extend(envelope_errors)
                break
            exercised.add("E")
            if spec.get("expect", {}).get("refusal"):
                exercised.add("K")
                after = _work_entries(open_cwd)
                if run.exit_code == 0:
                    findings.append("refusal expected nonzero exit")
                if "exit" in spec["expect"] and run.exit_code != int(spec["expect"]["exit"]):
                    findings.append(f"refusal exit mismatch: {run.exit_code} != {spec['expect']['exit']}")
                expected_kind = spec["expect"].get("error_kind")
                actual_kind = run.envelope.get("error", {}).get("kind")
                if expected_kind and actual_kind != expected_kind:
                    findings.append(f"refusal error.kind mismatch: {actual_kind} != {expected_kind}")
                if expected_kind:
                    mapped_exit, map_error = _exit_for_kind(expected_kind)
                    if map_error:
                        invalids.append(map_error)
                        break
                    if mapped_exit is not None and run.exit_code != mapped_exit:
                        findings.append(f"exit-map mismatch for {expected_kind}: {run.exit_code} != {mapped_exit}")
                if after != before:
                    findings.append("refusal created entries in open cwd")
                if _fingerprint(source) != source_before_refusal:
                    findings.append("refusal mutated source")
            elif run.exit_code != int(step.get("expect_exit", 0)):
                findings.append(
                    f"open exited {run.exit_code}, expected {step.get('expect_exit', 0)}: {run.detail}"
                )
                break
            else:
                output_dir = run.envelope.get("result", {}).get("output_dir")
                if output_dir:
                    restored = Path(output_dir)
            if not spec.get("expect", {}).get("refusal") and not restored.exists():
                findings.append(f"open default landing missing: {restored}")
        else:
            invalids.append(f"unknown step op: {op}")
            break

    expect = spec.get("expect", {})
    if not invalids and expect.get("session_rows"):
        actual_rows = _session_rows(run.envelope)
        for wanted in expect["session_rows"]:
            if not any(all(row.get(key) == value for key, value in wanted.items()) for row in actual_rows):
                findings.append(f"session row missing: {wanted}; got {actual_rows}")
        exercised.add("K")
    if not invalids and expect.get("sessions_absent"):
        if "sessions" in run.envelope.get("result", {}):
            findings.append("sessionless open unexpectedly emitted sessions block")
        exercised.add("K")
    if not invalids:
        for agent, delta in expect.get("target_delta", {}).items():
            changed = _fingerprint(target_stores[agent]) != target_before[agent]
            if changed != (delta == "changed"):
                findings.append(f"target-store delta for {agent}: expected {delta}")
            exercised.add("G")
    if not invalids and expect.get("claude_project_key_from_output"):
        project_dir = target_stores["claude-code"] / "projects" / _project_key(restored)
        if not project_dir.is_dir() or not any(project_dir.glob("*.jsonl")):
            findings.append(f"Claude project key not derived from restored output: {project_dir}")
        exercised.add("K")
    if not invalids and not expect.get("refusal") and artifact_ready:
        try:
            members = list_members(image)
            member_findings = assert_members(
                members,
                expect.get("members_present", []),
                expect.get("members_absent", []),
            )
            findings.extend(member_findings)
            exercised.add("K")
            manifest = json.loads(extract_member(image, "manifest.json"))
            manifest_findings = validate_manifest(manifest, expect.get("manifest_variant", "builtin"))
            manifest_findings.extend(_check_bivignore_sha(image, manifest))
            manifest_findings.extend(_check_payload_checksums(image))
            findings.extend(manifest_findings)
            exercised.add("E")
            findings.extend(_check_prune_summary(pack_envelope, expect.get("prune_summary", [])))
            if expect.get("tree"):
                _remove_expected_absences(expected, expect.get("members_absent", []))
                tree_findings = compare_trees(expected, restored, load_tolerance())
                findings.extend(tree_findings)
                exercised.update({"A", "B", "C"})
                exercised.update(_classes_for_tree_findings(tree_findings))
        except (FileNotFoundError, KeyError, json.JSONDecodeError, OSError, ValueError) as exc:
            findings.append(f"artifact inspection failed: {exc}")
    elif not invalids and not expect.get("refusal") and not artifact_ready and not findings:
        findings.append(f"image not available for artifact assertions: {image}")

    result.classes = [cls for cls in classes if cls in exercised]
    if invalids:
        result.status = Status.INVALID
        result.detail = "\n".join([*invalids, *findings])
    else:
        result.status = Status.FAIL if findings else Status.PASS
        result.detail = "\n".join(findings)
    return result
