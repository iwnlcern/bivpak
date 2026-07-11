import hashlib
import json
import os
import re
import shutil
import subprocess
import time
from pathlib import Path
from typing import Any

from bivharness.precheck import pin_env, probe, profile_root_failures
from bivharness.report import ScenarioResult, Status


CREDENTIAL_ENV_NAMES = (
    "ANTHROPIC_API_KEY",
    "OPENAI_API_KEY",
    "CODEX_ACCESS_TOKEN",
)
CLAUDE_RESUME_MUTATION = "appends-same-file"
CODEX_RESUME_SHAPE = "appends-same-rollout"
E3_CLASS = "E3 (real CLI resume in isolated profile)"
COMMAND_TIMEOUT_S = 120


def rejected_credential_names(env: dict[str, str]) -> list[str]:
    return sorted(name for name in CREDENTIAL_ENV_NAMES if name in env)


def ordered_turns_present(transcript: str, turns: list[str]) -> bool:
    cursor = 0
    for turn in turns:
        found = transcript.find(turn, cursor)
        if found < 0:
            return False
        cursor = found + len(turn)
    return True


def _project_key(path: Path) -> str:
    return "".join(ch if ch.isascii() and ch.isalnum() else "-" for ch in path.as_posix())


def scan_secret_values(blob: bytes, secret_values: list[str]) -> list[str]:
    return [f"secret[{index}]" for index, value in enumerate(secret_values) if value and value.encode() in blob]


def version_in_validated_range(version_output: str, validated_prefix: str) -> bool:
    versions = re.findall(r"(?<![0-9])([0-9]+\.[0-9]+\.[0-9]+)(?![0-9])", version_output)
    return any(version.startswith(validated_prefix) for version in versions)


def class_j_failures(seed_workspace: Path, restored_workspace: Path, app_state_paths: list[Path]) -> list[str]:
    failures: list[str] = []
    if seed_workspace.resolve(strict=False) == restored_workspace.resolve(strict=False):
        failures.append("workspace-paths-not-distinct")
    if any(path.exists() for path in app_state_paths):
        failures.append("bivpak-state-present")
    return failures


def assert_resume_containment(
    agent_id: str,
    profile: Path,
    restored_workspace: Path,
    session_id: str,
    turns: list[str],
    probe: str,
    pinned_shape: str,
) -> Path:
    if agent_id == "claude-code":
        if pinned_shape != CLAUDE_RESUME_MUTATION:
            raise ValueError("Claude resume mutation does not match pinned shape")
        transcript = profile / "projects" / _project_key(restored_workspace) / f"{session_id}.jsonl"
        probe_hits = []
        for candidate in profile.rglob("*.jsonl"):
            try:
                if probe in candidate.read_text(encoding="utf-8"):
                    probe_hits.append(candidate)
            except (OSError, UnicodeError):
                continue
        if probe_hits != [transcript]:
            raise ValueError("Claude resume containment requires the exact installed transcript")
    elif agent_id == "codex":
        if pinned_shape != CODEX_RESUME_SHAPE:
            raise ValueError("Codex resume shape does not match pinned shape")
        transcript = select_owned_rollout(profile, session_id, probe)
    else:
        raise ValueError(f"unsupported E3 agent: {agent_id}")
    if not transcript.is_file() or not ordered_turns_present(transcript.read_text(encoding="utf-8"), turns):
        raise ValueError(f"{agent_id} transcript containment failed")
    return transcript


def select_owned_rollout(root: Path, session_id: str, run_token: str) -> Path:
    matches: list[Path] = []
    for path in root.rglob("rollout-*.jsonl"):
        if session_id not in path.name:
            continue
        try:
            content = path.read_text(encoding="utf-8")
        except (OSError, UnicodeError):
            continue
        if run_token in content:
            matches.append(path)
    if len(matches) != 1:
        raise ValueError(f"expected exactly one owned rollout, got {len(matches)}")
    return matches[0]


def _select_owned_transcript(
    root: Path,
    pattern: str,
    run_token: str,
    started_ns: int,
    ended_ns: int,
) -> Path:
    matches: list[Path] = []
    for path in root.rglob(pattern):
        try:
            modified = path.stat().st_mtime_ns
            content = path.read_text(encoding="utf-8")
        except (OSError, UnicodeError):
            continue
        if started_ns <= modified <= ended_ns and run_token in content:
            matches.append(path)
    if len(matches) != 1:
        raise ValueError(f"expected exactly one ownership-proven transcript, got {len(matches)}")
    return matches[0]


def assert_one_checkpoint(checkpoints: list[str]) -> None:
    if len(checkpoints) != 1:
        raise ValueError(f"expected exactly one OAuth checkpoint, got {len(checkpoints)}")


def _hash(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def _clean_env(overrides: dict[str, str] | None = None) -> dict[str, str]:
    env = os.environ.copy()
    for name in CREDENTIAL_ENV_NAMES:
        env.pop(name, None)
    if overrides:
        env.update(overrides)
    rejected = rejected_credential_names(env)
    if rejected:
        raise ValueError("credential environment names present: " + ", ".join(rejected))
    return env


def _spawn(command: list[str], cwd: Path, env: dict[str, str]) -> subprocess.CompletedProcess[str]:
    clean = _clean_env(env)
    return subprocess.run(
        command,
        cwd=cwd,
        env=clean,
        text=True,
        capture_output=True,
        check=False,
        timeout=COMMAND_TIMEOUT_S,
    )


def _spawn_retry(command: list[str], cwd: Path, env: dict[str, str]) -> subprocess.CompletedProcess[str]:
    first = _spawn(command, cwd, env)
    if first.returncode == 0:
        return first
    return _spawn(command, cwd, env)


def _agent_profile(agent: dict[str, Any], profile_root: Path, *, live: bool) -> Path:
    if live:
        return Path(agent["live_profile"]).expanduser().resolve(strict=False)
    suffix = agent.get("host2_profile", agent["id"])
    return (profile_root / suffix).resolve(strict=False)


def _agent_env(agent: dict[str, Any], profile: Path) -> dict[str, str]:
    return {key: str(value).format(profile=str(profile)) for key, value in agent.get("env", {}).items()}


def _session_id_from_path(agent_id: str, path: Path) -> str:
    if agent_id == "codex":
        candidate = path.stem[-36:]
    else:
        candidate = path.stem
    if len(candidate) != 36 or candidate.count("-") != 4:
        raise ValueError("owned transcript filename did not contain a session UUID")
    return candidate


def _result(spec: dict[str, Any], status: Status, detail: str) -> ScenarioResult:
    return ScenarioResult(
        id=spec.get("id", "e3-invalid-spec"),
        tier="E3",
        status=status,
        classes=[E3_CLASS] if status is Status.PASS else [],
        detail=detail,
    )


def _validate_spec(spec: dict[str, Any]) -> list[str]:
    failures: list[str] = []
    if spec.get("tier") != "E3":
        failures.append("scenario tier must be E3")
    if spec.get("checkpoint_count") != 1:
        failures.append("scenario must declare exactly one checkpoint")
    agents = spec.get("agents")
    if not isinstance(agents, list) or len(agents) != 2:
        failures.append("scenario must declare two agents")
    else:
        required_agent_fields = (
            "id", "live_profile", "auth_status", "version_command",
            "validated_version_prefix", "seed_start_command", "seed_continue_command",
            "ownership_glob", "run_token", "resume_command",
        )
        for agent in agents:
            for field in required_agent_fields:
                if not agent.get(field):
                    failures.append(f"agent missing {field}")
            if agent.get("id") == "claude-code" and agent.get("resume_mutation") != CLAUDE_RESUME_MUTATION:
                failures.append("Claude resume mutation must match the pinned shape")
            if agent.get("id") == "codex" and agent.get("resume_shape") != CODEX_RESUME_SHAPE:
                failures.append("Codex resume shape must match the pinned shape")
    for key in ("seed_turns", "resume_probe"):
        if not spec.get(key):
            failures.append(f"scenario missing {key}")
    return failures


def run_e3(
    spec_path: Path,
    biv: Path,
    scratch: Path,
    *,
    dry_run: bool = False,
) -> ScenarioResult:
    try:
        spec = json.loads(spec_path.read_text(encoding="utf-8"))
    except (OSError, json.JSONDecodeError) as exc:
        return _result({}, Status.INVALID, f"scenario unreadable: {exc}")

    failures = _validate_spec(spec)
    failures.extend(probe(scratch))
    failures.extend(f"credential-env:{name}" for name in rejected_credential_names(os.environ))

    profile_root = Path(spec.get("host2_profile_root", scratch / "host2-profile"))
    if not profile_root.is_absolute():
        profile_root = scratch / profile_root
    live_stores = [Path(value).expanduser() for value in spec.get("live_store_roots", [])]
    failures.extend(profile_root_failures(profile_root, live_stores))
    if failures:
        return _result(spec, Status.INVALID, "\n".join(failures))

    pin_env()
    if dry_run:
        return _result(spec, Status.PASS, "dry-run: structural, isolation, and credential guards passed")

    # Live execution is intentionally explicit: this path owns real API calls and one
    # operator OAuth checkpoint. The scenario supplies commands so CLI surface changes
    # cannot silently alter the safety predicates in this runner.
    scratch.mkdir(parents=True, exist_ok=True)
    seed_ws = scratch / "seed-ws" / spec.get("workspace_name", "resume-e3")
    host2 = scratch / "host2"
    seed_ws.mkdir(parents=True, exist_ok=True)
    host2.mkdir(parents=True, exist_ok=True)
    checkpoints: list[str] = []
    owned_paths: list[Path] = []
    host2_env: dict[str, str] = {}
    host2_agent_envs: dict[str, dict[str, str]] = {}
    try:
        live_contexts: list[tuple[dict[str, Any], Path, dict[str, str]]] = []
        for agent in spec["agents"]:
            live_profile = _agent_profile(agent, profile_root, live=True)
            env = _agent_env(agent, live_profile)
            auth = _spawn(agent["auth_status"], seed_ws, env)
            if auth.returncode != 0:
                return _result(spec, Status.INVALID, f"{agent['id']} is not authenticated")
            version = _spawn(agent["version_command"], seed_ws, env)
            if version.returncode != 0 or not version_in_validated_range(
                version.stdout + version.stderr, agent["validated_version_prefix"]
            ):
                return _result(spec, Status.INVALID, f"{agent['id']} version is outside the validated range")
            live_contexts.append((agent, live_profile, env))

        for agent, live_profile, env in live_contexts:
            started_ns = time.time_ns()
            seeded = _spawn(
                [part.format(workspace=str(seed_ws), **spec) for part in agent["seed_start_command"]],
                seed_ws,
                env,
            )
            if seeded.returncode != 0:
                return _result(spec, Status.INVALID, f"{agent['id']} seed failed: {seeded.stderr.strip()}")
            first = _select_owned_transcript(
                live_profile,
                agent["ownership_glob"],
                agent["run_token"],
                started_ns,
                time.time_ns(),
            )
            seed_id = _session_id_from_path(agent["id"], first)
            seeded = _spawn(
                [part.format(workspace=str(seed_ws), id=seed_id, **spec)
                 for part in agent["seed_continue_command"]],
                seed_ws,
                env,
            )
            ended_ns = time.time_ns()
            if seeded.returncode != 0:
                return _result(spec, Status.INVALID, f"{agent['id']} seed failed: {seeded.stderr.strip()}")
            owned = _select_owned_transcript(
                live_profile,
                agent["ownership_glob"],
                agent["run_token"],
                started_ns,
                ended_ns,
            )
            if owned != first or not ordered_turns_present(
                owned.read_text(encoding="utf-8"), spec["seed_turns"]
            ):
                return _result(spec, Status.INVALID, f"{agent['id']} seed turns were not in one transcript")
            owned_paths.append(owned)

        before = {path: _hash(path) for path in owned_paths}
        packed = _spawn([str(biv), "pack", str(seed_ws), "--json"], scratch, {})
        if packed.returncode != 0:
            return _result(spec, Status.FAIL, f"pack failed: {packed.stderr.strip()}")
        if any(_hash(path) != digest for path, digest in before.items()):
            return _result(spec, Status.INVALID, "pack mutated an owned live-store transcript")
        image = seed_ws.parent / f"{seed_ws.name}.bvpk"
        secret_hits = scan_secret_values(image.read_bytes(), spec.get("credential_scan_sentinels", []))
        if secret_hits:
            return _result(spec, Status.FAIL, "credential sentinel found in image: " + ", ".join(secret_hits))

        checkpoints.append("host2-oauth")
        assert_one_checkpoint(checkpoints)
        input(spec.get("checkpoint_prompt", "Authenticate both CLIs in host2, then press Enter: "))

        for agent in spec["agents"]:
            isolated_profile = _agent_profile(agent, profile_root, live=False)
            isolated_profile.mkdir(parents=True, exist_ok=True)
            env = _agent_env(agent, isolated_profile)
            host2_home = host2 / "home"
            host2_home.mkdir(parents=True, exist_ok=True)
            env["HOME"] = str(host2_home)
            host2_agent_envs[agent["id"]] = env
            host2_env.update(env)
            auth = _spawn(agent["auth_status"], host2, env)
            if auth.returncode != 0:
                return _result(spec, Status.INVALID, f"{agent['id']} host2 authentication missing")
            version = _spawn(agent["version_command"], host2, env)
            if version.returncode != 0 or not version_in_validated_range(
                version.stdout + version.stderr, agent["validated_version_prefix"]
            ):
                return _result(spec, Status.INVALID, f"{agent['id']} host2 version is outside the validated range")

        # The remaining open/resume commands are deliberately data-driven and still
        # pass through _spawn, preserving the no-credential and isolated-profile gates.
        opened = _spawn([str(biv), "open", str(image), "--dest", str(host2),
                         "--consent", "yes", "--json"], host2, host2_env)
        if opened.returncode != 0:
            return _result(spec, Status.FAIL, f"open failed: {opened.stderr.strip()}")
        envelope = json.loads(opened.stdout)
        restored_workspace = Path(envelope.get("result", {}).get("output_dir", ""))
        if not restored_workspace.is_dir():
            return _result(spec, Status.FAIL, "open output workspace missing")
        class_j = class_j_failures(
            seed_ws,
            restored_workspace,
            [restored_workspace / ".biv" / "agents",
             *[scratch / path for path in spec.get("forbidden_bivpak_state", [])]],
        )
        if class_j:
            return _result(spec, Status.INVALID, ",".join(class_j))
        groups = envelope.get("result", {}).get("sessions", {}).get("agents", [])
        installed: dict[str, dict[str, Any]] = {}
        for group in groups:
            sessions = [row for row in group.get("sessions", []) if row.get("outcome") == "installed"]
            if len(sessions) == 1:
                installed[group.get("agent")] = sessions[0]
        if len(installed) != len(spec["agents"]):
            return _result(spec, Status.FAIL, "open did not install exactly two session rows")

        for agent in spec["agents"]:
            row = installed[agent["id"]]
            session_id = row.get("installed_session_id")
            if not session_id:
                return _result(spec, Status.FAIL, f"{agent['id']} installed id missing")
            command = [part.format(id=session_id, probe=spec["resume_probe"])
                       for part in agent["resume_command"]]
            profile = _agent_profile(agent, profile_root, live=False)
            env = host2_agent_envs[agent["id"]]
            resumed = _spawn_retry(command, restored_workspace, env)
            if resumed.returncode != 0 or not resumed.stdout.strip():
                return _result(spec, Status.INVALID, f"{agent['id']} resume did not return a reply")
            turns = [*spec["seed_turns"], spec["resume_probe"]]
            shape = agent["resume_mutation"] if agent["id"] == "claude-code" else agent["resume_shape"]
            assert_resume_containment(
                agent["id"], profile, restored_workspace, session_id,
                turns, spec["resume_probe"], shape,
            )
        return _result(spec, Status.PASS, "dual-agent resume and store containment passed")
    except (KeyError, OSError, ValueError, subprocess.TimeoutExpired, json.JSONDecodeError) as exc:
        return _result(spec, Status.INVALID, str(exc))
    finally:
        print("Ownership-proven cleanup candidates (not deleted):")
        for path in owned_paths:
            print(path)
        shutil.rmtree(seed_ws.parent, ignore_errors=True)
        shutil.rmtree(host2, ignore_errors=True)
