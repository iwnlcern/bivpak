import hashlib
import io
import json
import os
import re
import shutil
import stat
import tarfile
from pathlib import Path
from types import SimpleNamespace

import pytest
import zstandard

from bivharness import cli, e3
from bivharness.e3 import (
    CLAUDE_RESUME_MUTATION,
    CODEX_RESUME_SHAPE,
    CREDENTIAL_ENV_NAMES,
    assert_exact_install_delta,
    assert_resume_containment,
    assert_one_checkpoint,
    capture_inventory,
    class_j_failures,
    classify_capture,
    format_cleanup_report,
    ordered_turns_present,
    perform_oauth_checkpoint,
    plant_credential_decoys,
    rejected_credential_names,
    scan_secret_values,
    scan_image_secret_values,
    select_owned_rollout,
    snapshot_store,
    verify_credential_decoys,
    version_in_validated_range,
)
from bivharness.precheck import profile_root_failures
from bivharness.report import Status


@pytest.fixture
def repo_root() -> Path:
    root = Path(__file__).resolve().parents[2]
    assert (root / "src/adapters/codex/install.cpp").is_file(), (
        f"repo_root mis-resolved: {root}"
    )
    assert (root / "harness/scenarios-e3/e3-dual-resume.json").is_file(), (
        f"repo_root mis-resolved: {root}"
    )
    return root


@pytest.fixture
def stable_test_root(tmp_path):
    root = (
        Path.home()
        / ".cache"
        / "bivharness-selftest"
        / f"{os.getpid()}-{tmp_path.name}"
    )
    shutil.rmtree(root, ignore_errors=True)
    root.mkdir(parents=True)
    assert root.is_absolute()
    assert root.resolve() == root
    for live_store in (Path.home() / ".claude", Path.home() / ".codex"):
        assert root != live_store
        assert live_store not in root.parents
    try:
        yield root
    finally:
        shutil.rmtree(root, ignore_errors=True)


PRODUCT_PREDICATES = {
    "codex": ("src/adapters/codex/install.cpp", "validated_codex_version"),
    "claude-code": (
        "src/adapters/claude_code/install.cpp",
        "validated_claude_version",
    ),
}


def _product_prefixes(repo_root: Path, agent_id: str) -> list[str]:
    rel, function = PRODUCT_PREDICATES[agent_id]
    source = (repo_root / rel).read_text(encoding="utf-8")
    match = re.search(
        rf"bool\s+{function}\s*\([^)]*\)\s*\{{(.*?)\n\}}",
        source,
        re.S,
    )
    assert match, f"predicate {function} not found in {rel}"
    prefixes = re.findall(r'starts_with\("([^"]*)"\)', match.group(1))
    assert prefixes, f"{function} is no longer a starts_with prefix set"
    return prefixes


def test_scenario_version_sets_mirror_the_product_exactly(repo_root):
    spec = json.loads(
        (repo_root / "harness/scenarios-e3/e3-dual-resume.json").read_text(
            encoding="utf-8"
        )
    )
    for agent in spec["agents"]:
        product = _product_prefixes(repo_root, agent["id"])
        assert agent["validated_version_prefixes"] == product, (
            f"{agent['id']}: scenario {agent['validated_version_prefixes']} != product "
            f"{product}. Mirror the product exactly."
        )


def _valid_two_agent_spec():
    """Return a two-agent E3 spec that passes validation once lists are supported."""
    codex = {
        "id": "codex",
        "live_profile": "~/.codex",
        "env": {},
        "auth_status": ["codex", "login", "status"],
        "version_command": ["codex", "--version"],
        "validated_version_prefixes": ["0.142.", "0.144."],
        "cheapest_model": "cheap",
        "seed_start_command": ["codex", "seed", "{run_token}", "--model", "cheap"],
        "seed_retry_resume_command": ["codex", "retry", "{run_token}", "--model", "cheap"],
        "seed_continue_command": ["codex", "continue", "{run_token}", "--model", "cheap"],
        "ownership_glob": "*.jsonl",
        "run_token_prefix": "token",
        "resume_command": ["codex", "resume", "--model", "cheap"],
        "resume_shape": CODEX_RESUME_SHAPE,
    }
    claude = {
        **codex,
        "id": "claude-code",
        "live_profile": "~/.claude",
        "auth_status": ["claude", "auth", "status"],
        "version_command": ["claude", "--version"],
        "validated_version_prefixes": ["2.1."],
        "seed_start_command": ["claude", "seed", "{run_token}", "--model", "cheap"],
        "seed_retry_resume_command": ["claude", "retry", "{run_token}", "--model", "cheap"],
        "seed_continue_command": ["claude", "continue", "{run_token}", "--model", "cheap"],
        "resume_command": ["claude", "resume", "--model", "cheap"],
        "liveness_command": ["claude", "--model", "cheap", "-p", "Reply with one token: OK"],
        "resume_mutation": CLAUDE_RESUME_MUTATION,
    }
    claude.pop("resume_shape", None)
    return {
        "id": "cx-range",
        "tier": "E3",
        "checkpoint_count": 1,
        "seed_turns": ["one", "two"],
        "resume_probe": "probe",
        "credential_scan_sentinels": ["synthetic-secret"],
        "agents": [codex, claude],
    }


def test_shared_fixture_is_valid_as_authored():
    assert e3._validate_spec(_valid_two_agent_spec()) == []


def test_ordered_turns_require_all_sentinels_and_probe_in_order():
    turns = ["seed-one", "seed-two", "resume-probe"]

    assert ordered_turns_present("prefix seed-one middle seed-two tail resume-probe", turns)
    assert not ordered_turns_present("seed-two seed-one resume-probe", turns)
    assert not ordered_turns_present("seed-one seed-two", turns)


def test_owned_rollout_rejects_foreign_and_ambiguous_candidates(tmp_path):
    owned = tmp_path / "rollout-2026-07-11-owned-id.jsonl"
    owned.write_text('{"run_token":"mine"}\n', encoding="utf-8")

    assert select_owned_rollout(tmp_path, "owned-id", "mine") == owned

    duplicate = tmp_path / "nested" / owned.name
    duplicate.parent.mkdir()
    duplicate.write_text('{"run_token":"mine"}\n', encoding="utf-8")
    with pytest.raises(ValueError, match="exactly one"):
        select_owned_rollout(tmp_path, "owned-id", "mine")


def _checkpoint_agents():
    return [
        {
            "id": "claude-code",
            "host2_profile": "claude",
            "env": {"CLAUDE_CONFIG_DIR": "{profile}"},
            "auth_status": ["claude", "auth", "status"],
            "version_command": ["claude", "--version"],
            "validated_version_prefixes": ["2.1."],
            "liveness_command": ["claude", "--model", "haiku", "-p", "Reply with one token: OK"],
        },
        {
            "id": "codex",
            "host2_profile": "codex",
            "env": {"CODEX_HOME": "{profile}"},
            "auth_status": ["codex", "login", "status"],
            "version_command": ["codex", "--version"],
            "validated_version_prefixes": ["0.142.", "0.144."],
        },
    ]


def test_oauth_checkpoint_constructs_profiles_and_prints_real_login_commands(tmp_path):
    host2 = tmp_path / "host two"
    profile_root = host2 / "profiles"
    calls = []
    pauses = []

    def fake_spawn(command, cwd, env):
        calls.append(command)
        version = "2.1.202" if command[0] == "claude" else "0.142.5"
        return SimpleNamespace(returncode=0, stdout=version, stderr="")

    def pause(prompt):
        pauses.append(prompt)
        assert (host2 / "home").is_dir()
        assert (profile_root / "claude").is_dir()
        assert (profile_root / "codex").is_dir()
        assert f"CLAUDE_CONFIG_DIR='{profile_root / 'claude'}' claude auth login" in prompt
        assert f"CODEX_HOME='{profile_root / 'codex'}' codex login" in prompt
        return ""

    envs = perform_oauth_checkpoint(
        {"agents": _checkpoint_agents()}, host2, profile_root, pause, fake_spawn
    )

    assert len(pauses) == 1
    assert set(envs) == {"claude-code", "codex"}
    assert calls[-1][0] == "claude"
    assert "-p" in calls[-1]


@pytest.mark.parametrize("failed", [{"claude-code", "codex"}, {"claude-code"}, {"codex"}])
def test_oauth_checkpoint_rejects_neither_or_one_authenticated_agent(tmp_path, failed):
    auth_seen = []

    def fake_spawn(command, cwd, env):
        agent = "claude-code" if command[0] == "claude" else "codex"
        if command[-1] == "status":
            auth_seen.append(agent)
            return SimpleNamespace(returncode=1 if agent in failed else 0, stdout="", stderr="")
        return SimpleNamespace(returncode=0, stdout="2.1.202 0.142.5", stderr="")

    with pytest.raises(ValueError, match="host2 authentication missing"):
        perform_oauth_checkpoint(
            {"agents": _checkpoint_agents()}, tmp_path / "host2", tmp_path / "profiles",
            lambda prompt: "", fake_spawn,
        )
    assert auth_seen == ["claude-code", "codex"]


def test_oauth_checkpoint_rejects_failed_claude_liveness(tmp_path):
    def fake_spawn(command, cwd, env):
        if command[0] == "claude" and "-p" in command:
            return SimpleNamespace(returncode=1, stdout="", stderr="offline")
        return SimpleNamespace(returncode=0, stdout="2.1.202 0.142.5", stderr="")

    with pytest.raises(ValueError, match="liveness"):
        perform_oauth_checkpoint(
            {"agents": _checkpoint_agents()}, tmp_path / "host2", tmp_path / "profiles",
            lambda prompt: "", fake_spawn,
        )


def test_oauth_checkpoint_rejects_multi_token_claude_liveness(tmp_path):
    def fake_spawn(command, cwd, env):
        output = "too many tokens" if command[0] == "claude" and "-p" in command else "2.1.202 0.142.5"
        return SimpleNamespace(returncode=0, stdout=output, stderr="")

    with pytest.raises(ValueError, match="one token"):
        perform_oauth_checkpoint(
            {"agents": _checkpoint_agents()}, tmp_path / "host2", tmp_path / "profiles",
            lambda prompt: "", fake_spawn,
        )


def test_oauth_checkpoint_retries_claude_liveness_once(tmp_path):
    liveness_calls = 0

    def fake_spawn(command, cwd, env):
        nonlocal liveness_calls
        if command[0] == "claude" and "-p" in command:
            liveness_calls += 1
            return SimpleNamespace(
                returncode=1 if liveness_calls == 1 else 0,
                stdout="" if liveness_calls == 1 else "OK",
                stderr="transient" if liveness_calls == 1 else "",
            )
        return SimpleNamespace(returncode=0, stdout="2.1.202 0.142.5", stderr="")

    perform_oauth_checkpoint(
        {"agents": _checkpoint_agents()}, tmp_path / "host2", tmp_path / "profiles",
        lambda prompt: "", fake_spawn,
    )
    assert liveness_calls == 2


@pytest.mark.parametrize("first_failure", ["multi-token", "timeout", "oserror"])
def test_oauth_checkpoint_retries_invalid_or_exceptional_liveness_once(tmp_path, first_failure):
    liveness_calls = 0

    def fake_spawn(command, cwd, env):
        nonlocal liveness_calls
        if command[0] == "claude" and "-p" in command:
            liveness_calls += 1
            if liveness_calls == 1 and first_failure == "timeout":
                raise e3.subprocess.TimeoutExpired(command, 120)
            if liveness_calls == 1 and first_failure == "oserror":
                raise OSError("spawn failed")
            output = "too many tokens" if liveness_calls == 1 else "OK"
            return SimpleNamespace(returncode=0, stdout=output, stderr="")
        return SimpleNamespace(returncode=0, stdout="2.1.202 0.142.5", stderr="")

    perform_oauth_checkpoint(
        {"agents": _checkpoint_agents()}, tmp_path / "host2", tmp_path / "profiles",
        lambda prompt: "", fake_spawn,
    )
    assert liveness_calls == 2


@pytest.mark.parametrize("first_failure", ["empty", "timeout", "oserror"])
def test_model_reply_retry_covers_semantic_and_exceptional_failure(tmp_path, first_failure):
    calls = 0

    def fake_spawn(command, cwd, env):
        nonlocal calls
        calls += 1
        if calls == 1 and first_failure == "timeout":
            raise e3.subprocess.TimeoutExpired(command, 120)
        if calls == 1 and first_failure == "oserror":
            raise OSError("spawn failed")
        return SimpleNamespace(returncode=0, stdout="" if calls == 1 else "reply", stderr="")

    result = e3._spawn_retry_with(
        ["agent", "resume"], tmp_path, {}, fake_spawn,
        lambda value: value.returncode == 0 and bool(value.stdout.strip()),
    )
    assert result.stdout == "reply"
    assert calls == 2


@pytest.mark.parametrize("pattern", ["*.jsonl", "rollout-*.jsonl"])
@pytest.mark.parametrize("case", ["clean", "foreign-new", "foreign-modified", "duplicate-owned"])
def test_capture_window_requires_one_owned_and_zero_foreign_candidates(tmp_path, pattern, case):
    root = tmp_path / "store"
    root.mkdir()
    foreign = root / ("rollout-foreign.jsonl" if pattern.startswith("rollout") else "foreign.jsonl")
    if case == "foreign-modified":
        foreign.write_text("old", encoding="utf-8")
    before = capture_inventory(root, pattern)
    owned = root / ("rollout-owned.jsonl" if pattern.startswith("rollout") else "owned.jsonl")
    owned.write_text("TOKEN", encoding="utf-8")
    if case == "foreign-new":
        foreign.write_text("foreign", encoding="utf-8")
    elif case == "foreign-modified":
        foreign.write_text("changed", encoding="utf-8")
    elif case == "duplicate-owned":
        duplicate = root / "nested" / owned.name
        duplicate.parent.mkdir()
        duplicate.write_text("TOKEN", encoding="utf-8")
    after = capture_inventory(root, pattern)

    if case == "clean":
        selected, candidates = classify_capture(before, after, "TOKEN")
        assert selected == owned
        assert candidates == [owned]
    else:
        with pytest.raises(ValueError, match="capture ambiguity"):
            classify_capture(before, after, "TOKEN")


def test_cleanup_report_discloses_foreign_but_never_suggests_it_for_cleanup(tmp_path):
    owned = tmp_path / "owned.jsonl"
    foreign = tmp_path / "foreign.jsonl"
    report = format_cleanup_report([owned, foreign], [owned])
    disclosure, cleanup = report.split("Ownership-proven cleanup candidates (not deleted):\n")
    assert str(foreign) in disclosure
    assert str(foreign) not in cleanup
    assert str(owned) in cleanup


def test_failed_seed_leg_still_classifies_every_changed_candidate(tmp_path):
    root = tmp_path / "store"
    root.mkdir()
    owned = root / "owned.jsonl"
    foreign = root / "foreign.jsonl"

    def failed_command():
        owned.write_text("TOKEN", encoding="utf-8")
        foreign.write_text("other", encoding="utf-8")
        return SimpleNamespace(returncode=1, stdout="", stderr="failed")

    with pytest.raises(e3.CaptureAmbiguity) as caught:
        e3._capture_seed_leg(root, "*.jsonl", "TOKEN", failed_command)
    assert caught.value.candidates == [foreign, owned]


@pytest.mark.parametrize("foreign_write", [False, True])
def test_exceptional_seed_leg_still_classifies_every_changed_candidate(tmp_path, foreign_write):
    root = tmp_path / "store"
    root.mkdir()
    owned = root / "owned.jsonl"
    foreign = root / "foreign.jsonl"

    def timed_out_command():
        owned.write_text("TOKEN", encoding="utf-8")
        if foreign_write:
            foreign.write_text("other", encoding="utf-8")
        raise e3.subprocess.TimeoutExpired(["agent", "seed"], 120)

    expected = e3.CaptureAmbiguity if foreign_write else e3.CaptureCommandError
    with pytest.raises(expected) as caught:
        e3._capture_seed_leg(root, "*.jsonl", "TOKEN", timed_out_command)
    assert caught.value.candidates == ([foreign, owned] if foreign_write else [owned])


@pytest.mark.parametrize("failure", ["nonzero", "timeout", "oserror", "foreign"])
def test_first_leg_owned_path_survives_every_continuation_failure(tmp_path, failure):
    root = tmp_path / "store"
    root.mkdir()
    workspace = tmp_path / "workspace"
    workspace.mkdir()
    session_id = "aaaaaaaa-1111-4111-8111-111111111111"
    transcript = _scoped_claude_transcript(root, workspace, session_id)
    foreign = root / "foreign.jsonl"
    calls = 0

    def fake_spawn(command, cwd, env):
        nonlocal calls
        calls += 1
        if calls == 1:
            transcript.write_text("TOKEN\nseed-one\n", encoding="utf-8")
            return SimpleNamespace(returncode=0, stdout="", stderr="")
        transcript.write_text("TOKEN\nseed-one\nseed-two\n", encoding="utf-8")
        if failure == "nonzero":
            return SimpleNamespace(returncode=1, stdout="", stderr="failed")
        if failure == "timeout":
            raise e3.subprocess.TimeoutExpired(command, 120)
        if failure == "oserror":
            raise OSError("spawn failed")
        foreign.write_text("other", encoding="utf-8")
        return SimpleNamespace(returncode=0, stdout="", stderr="")

    agent = {
        "id": "claude-code",
        "ownership_glob": "*.jsonl",
        "run_token": "TOKEN",
        "seed_start_command": ["agent", "start"],
        "seed_retry_resume_command": ["agent", "retry-resume", "{id}"],
        "seed_continue_command": ["agent", "continue", "{id}"],
    }
    spec = {"seed_turns": ["seed-one", "seed-two"]}
    candidates = []
    owned = []

    with pytest.raises(ValueError):
        e3._seed_agent(agent, root, workspace, spec, {}, fake_spawn, candidates, owned)

    report = format_cleanup_report(candidates, owned)
    disclosure, cleanup = report.split("Ownership-proven cleanup candidates (not deleted):\n")
    assert str(transcript) in cleanup
    if failure == "foreign":
        assert str(foreign) in disclosure
        assert str(foreign) not in cleanup


def _retry_seed_agent():
    return {
        "id": "claude-code",
        "ownership_glob": "*.jsonl",
        "run_token": "TOKEN",
        "seed_start_command": ["agent", "start"],
        "seed_retry_resume_command": ["agent", "retry-resume", "{id}"],
        "seed_continue_command": ["agent", "continue", "{id}"],
    }


def _scoped_claude_transcript(root, workspace, session_id):
    project = root / "projects" / e3._project_key(workspace)
    project.mkdir(parents=True, exist_ok=True)
    return project / f"{session_id}.jsonl"


def test_runtime_tokens_are_distinct_between_invocations():
    spec = {
        "agents": [
            {"id": "claude-code", "run_token_prefix": "BIV_E3_CLAUDE_RUN_TOKEN"},
            {"id": "codex", "run_token_prefix": "BIV_E3_CODEX_RUN_TOKEN"},
        ]
    }

    first = e3.materialize_run_tokens(spec)
    second = e3.materialize_run_tokens(spec)

    assert [agent["run_token"] for agent in first["agents"]] != [
        agent["run_token"] for agent in second["agents"]
    ]
    assert all("run_token" not in agent for agent in spec["agents"])


@pytest.mark.parametrize(
    "foreign_token",
    [
        "BIV_E3_CLAUDE_RUN_TOKEN",
        "THIS_INVOCATION_TOKEN"[:-1],
        "THIS_INVOCATION_TOKEN_SUFFIX",
        "OTHER_INVOCATION_TOKEN",
    ],
)
def test_failed_empty_start_never_adopts_non_exact_invocation_token(tmp_path, foreign_token):
    root = tmp_path / "store"
    root.mkdir()
    workspace = tmp_path / "workspace"
    workspace.mkdir()
    session_id = "aaaaaaaa-1111-4111-8111-111111111111"
    transcript = _scoped_claude_transcript(root, workspace, session_id)
    commands = []

    def fake_spawn(command, cwd, env):
        commands.append(command)
        transcript.write_text(f"{foreign_token}\nseed-one\n", encoding="utf-8")
        return SimpleNamespace(returncode=1, stdout="", stderr="transient")

    agent = {
        **_retry_seed_agent(),
        "run_token_prefix": "BIV_E3_CLAUDE_RUN_TOKEN",
        "run_token": "THIS_INVOCATION_TOKEN",
    }
    candidates = []
    owned = []
    with pytest.raises(ValueError, match="capture ambiguity"):
        e3._seed_agent(
            agent, root, workspace, {"seed_turns": ["seed-one", "seed-two"]},
            {}, fake_spawn, candidates, owned,
        )

    assert len(commands) == 1
    assert candidates == [transcript]
    assert owned == []


def test_failed_start_resumes_candidate_with_this_invocations_exact_token(tmp_path):
    root = tmp_path / "store"
    root.mkdir()
    workspace = tmp_path / "workspace"
    workspace.mkdir()
    session_id = "aaaaaaaa-1111-4111-8111-111111111111"
    transcript = _scoped_claude_transcript(root, workspace, session_id)
    commands = []

    def fake_spawn(command, cwd, env):
        commands.append(command)
        if len(commands) == 1:
            transcript.write_text("THIS_INVOCATION_TOKEN\nseed-one\n", encoding="utf-8")
            return SimpleNamespace(returncode=1, stdout="", stderr="transient")
        if len(commands) == 2:
            transcript.write_text("THIS_INVOCATION_TOKEN\nseed-one\nretry-reply\n", encoding="utf-8")
            return SimpleNamespace(returncode=0, stdout="reply", stderr="")
        transcript.write_text("THIS_INVOCATION_TOKEN\nseed-one\nseed-two\n", encoding="utf-8")
        return SimpleNamespace(returncode=0, stdout="reply", stderr="")

    agent = {
        **_retry_seed_agent(),
        "run_token_prefix": "BIV_E3_CLAUDE_RUN_TOKEN",
        "run_token": "THIS_INVOCATION_TOKEN",
        "seed_start_command": ["agent", "start", "{run_token}"],
        "seed_retry_resume_command": ["agent", "retry-resume", "{id}", "{run_token}"],
        "seed_continue_command": ["agent", "continue", "{id}", "{run_token}"],
    }
    selected = e3._seed_agent(
        agent, root, workspace,
        {"id": "scenario-id", "seed_turns": ["seed-one", "seed-two"]},
        {}, fake_spawn, [], [],
    )

    assert selected == transcript
    assert commands[1] == ["agent", "retry-resume", session_id, "THIS_INVOCATION_TOKEN"]
    assert commands[2] == ["agent", "continue", session_id, "THIS_INVOCATION_TOKEN"]


def test_claude_token_outside_seed_workspace_project_is_foreign(tmp_path):
    root = tmp_path / "store"
    root.mkdir()
    workspace = tmp_path / "workspace"
    workspace.mkdir()
    foreign_project = root / "projects" / "foreign-workspace"
    foreign_project.mkdir(parents=True)
    transcript = foreign_project / "aaaaaaaa-1111-4111-8111-111111111111.jsonl"
    calls = 0

    def fake_spawn(command, cwd, env):
        nonlocal calls
        calls += 1
        transcript.write_text("THIS_INVOCATION_TOKEN\nseed-one\n", encoding="utf-8")
        return SimpleNamespace(returncode=1, stdout="", stderr="transient")

    agent = {
        **_retry_seed_agent(),
        "run_token": "THIS_INVOCATION_TOKEN",
    }
    candidates = []
    owned = []
    with pytest.raises(ValueError, match="capture ambiguity"):
        e3._seed_agent(
            agent, root, workspace, {"seed_turns": ["seed-one", "seed-two"]},
            {}, fake_spawn, candidates, owned,
        )

    assert calls == 1
    assert candidates == [transcript]
    assert owned == []


@pytest.mark.parametrize("agent_id", ["claude-code", "codex"])
def test_capture_path_proof_rejects_malformed_session_uuid(tmp_path, agent_id):
    root = tmp_path / "store"
    workspace = tmp_path / "workspace"
    malformed = "xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx"
    if agent_id == "claude-code":
        path = root / "projects" / e3._project_key(workspace) / f"{malformed}.jsonl"
    else:
        path = root / "sessions" / f"rollout-2026-07-11-{malformed}.jsonl"

    assert not e3._capture_path_proof(agent_id, path, root, workspace)


@pytest.mark.parametrize("first_shape", ["wrote-owned", "wrote-nothing"])
def test_first_seed_retry_resumes_owned_or_restarts_empty_window(tmp_path, first_shape):
    root = tmp_path / "store"
    root.mkdir()
    workspace = tmp_path / "workspace"
    workspace.mkdir()
    session_id = "aaaaaaaa-1111-4111-8111-111111111111"
    transcript = _scoped_claude_transcript(root, workspace, session_id)
    commands = []

    def fake_spawn(command, cwd, env):
        commands.append(command)
        if len(commands) == 1:
            if first_shape == "wrote-owned":
                transcript.write_text("TOKEN\nseed-one\n", encoding="utf-8")
            return SimpleNamespace(returncode=1, stdout="", stderr="transient")
        if len(commands) == 2:
            transcript.write_text("TOKEN\nseed-one\nretry-reply\n", encoding="utf-8")
            return SimpleNamespace(returncode=0, stdout="reply", stderr="")
        transcript.write_text("TOKEN\nseed-one\nseed-two\n", encoding="utf-8")
        return SimpleNamespace(returncode=0, stdout="reply", stderr="")

    candidates = []
    owned = []
    selected = e3._seed_agent(
        _retry_seed_agent(), root, workspace, {"seed_turns": ["seed-one", "seed-two"]},
        {}, fake_spawn, candidates, owned,
    )

    assert selected == transcript
    assert owned == [transcript]
    expected_retry = ["agent", "retry-resume", session_id] if first_shape == "wrote-owned" else ["agent", "start"]
    assert commands[1] == expected_retry


@pytest.mark.parametrize("first_shape", ["two-owned", "foreign"])
def test_first_seed_retry_rejects_ambiguous_or_foreign_window(tmp_path, first_shape):
    root = tmp_path / "store"
    root.mkdir()
    workspace = tmp_path / "workspace"
    workspace.mkdir()
    first = _scoped_claude_transcript(root, workspace, "aaaaaaaa-1111-4111-8111-111111111111")
    second = first.parent / "bbbbbbbb-1111-4111-8111-111111111111.jsonl"
    foreign = root / "foreign.jsonl"
    calls = 0

    def fake_spawn(command, cwd, env):
        nonlocal calls
        calls += 1
        first.write_text("TOKEN\nseed-one\n", encoding="utf-8")
        if first_shape == "two-owned":
            second.write_text("TOKEN\nseed-one\n", encoding="utf-8")
        else:
            foreign.write_text("other", encoding="utf-8")
        return SimpleNamespace(returncode=1, stdout="", stderr="transient")

    candidates = []
    owned = []
    with pytest.raises(ValueError, match="capture ambiguity"):
        e3._seed_agent(
            _retry_seed_agent(), root, workspace, {"seed_turns": ["seed-one", "seed-two"]},
            {}, fake_spawn, candidates, owned,
        )
    assert calls == 1
    assert owned == []


def test_first_seed_retry_rejects_resume_after_midfail_rejection(tmp_path):
    root = tmp_path / "store"
    root.mkdir()
    workspace = tmp_path / "workspace"
    workspace.mkdir()
    session_id = "aaaaaaaa-1111-4111-8111-111111111111"
    transcript = _scoped_claude_transcript(root, workspace, session_id)
    commands = []

    def fake_spawn(command, cwd, env):
        commands.append(command)
        transcript.write_text(f"TOKEN\nseed-one\nattempt-{len(commands)}\n", encoding="utf-8")
        return SimpleNamespace(returncode=1, stdout="", stderr="resume rejected")

    candidates = []
    owned = []
    with pytest.raises(ValueError, match="retry failed"):
        e3._seed_agent(
            _retry_seed_agent(), root, workspace, {"seed_turns": ["seed-one", "seed-two"]},
            {}, fake_spawn, candidates, owned,
        )
    assert commands == [["agent", "start"], ["agent", "retry-resume", session_id]]
    assert owned == [transcript]


def test_second_seed_turn_retries_same_resume_command_once(tmp_path):
    root = tmp_path / "store"
    root.mkdir()
    workspace = tmp_path / "workspace"
    workspace.mkdir()
    session_id = "aaaaaaaa-1111-4111-8111-111111111111"
    transcript = _scoped_claude_transcript(root, workspace, session_id)
    commands = []

    def fake_spawn(command, cwd, env):
        commands.append(command)
        if len(commands) == 1:
            transcript.write_text("TOKEN\nseed-one\n", encoding="utf-8")
            return SimpleNamespace(returncode=0, stdout="reply", stderr="")
        transcript.write_text(f"TOKEN\nseed-one\nseed-two\nattempt-{len(commands)}\n", encoding="utf-8")
        return SimpleNamespace(returncode=1 if len(commands) == 2 else 0, stdout="reply", stderr="")

    e3._seed_agent(
        _retry_seed_agent(), root, workspace, {"seed_turns": ["seed-one", "seed-two"]},
        {}, fake_spawn, [], [],
    )
    assert commands[1] == commands[2] == ["agent", "continue", session_id]


def test_e3_scenario_pins_cheapest_model_on_every_model_call_leg():
    scenario = Path(__file__).parents[1] / "scenarios-e3" / "e3-dual-resume.json"
    spec = json.loads(scenario.read_text(encoding="utf-8"))
    expected = {"claude-code": "haiku", "codex": "gpt-5.4-mini"}
    assert spec["model_call_baseline"] == {"claude-code": 4, "codex": 3}

    for agent in spec["agents"]:
        model = expected[agent["id"]]
        assert agent["cheapest_model"] == model
        fields = ["seed_start_command", "seed_retry_resume_command", "seed_continue_command", "resume_command"]
        if agent["id"] == "claude-code":
            fields.append("liveness_command")
        for field in fields:
            command = agent[field]
            index = command.index("--model")
            assert command[index + 1] == model


def test_e3_scenario_keeps_only_token_prefix_and_injects_runtime_token_into_seed_commands():
    scenario = Path(__file__).parents[1] / "scenarios-e3" / "e3-dual-resume.json"
    spec = json.loads(scenario.read_text(encoding="utf-8"))

    for agent in spec["agents"]:
        assert agent["run_token_prefix"]
        assert "run_token" not in agent
        for field in ("seed_start_command", "seed_retry_resume_command", "seed_continue_command"):
            assert any("{run_token}" in part for part in agent[field])


def test_workspace_credential_decoys_are_exact_and_format_valid(tmp_path):
    sentinels = ["synthetic-secret-one", "synthetic-secret-two"]
    paths = plant_credential_decoys(tmp_path, sentinels)
    assert {path.name for path in paths} == {".credentials.json", "auth.json", ".env"}
    verify_credential_decoys(tmp_path, paths, sentinels)


@pytest.mark.parametrize("removed_count", [1, 2])
def test_workspace_credential_decoys_reject_missing_required_paths(tmp_path, removed_count):
    sentinels = ["synthetic-secret"]
    paths = plant_credential_decoys(tmp_path, sentinels)
    for path in paths[-removed_count:]:
        path.unlink()
    with pytest.raises(ValueError, match="exact controlled credential-shaped decoy set"):
        verify_credential_decoys(tmp_path, paths, sentinels)


@pytest.mark.parametrize(
    ("name", "content"),
    [
        (".credentials.json", "synthetic-secret"),
        ("auth.json", '{"apiKey":"synthetic-secret"}'),
        (".env", "OPENAI_API_KEY=synthetic-secret\n"),
    ],
)
def test_workspace_credential_decoys_reject_wrong_format_or_content(tmp_path, name, content):
    sentinels = ["synthetic-secret"]
    paths = plant_credential_decoys(tmp_path, sentinels)
    next(path for path in paths if path.name == name).write_text(content, encoding="utf-8")
    with pytest.raises(ValueError, match="format invalid"):
        verify_credential_decoys(tmp_path, paths, sentinels)


@pytest.mark.parametrize("kind", ["directory", "symlink"])
def test_workspace_credential_decoys_require_regular_files(tmp_path, kind):
    sentinels = ["synthetic-secret"]
    paths = plant_credential_decoys(tmp_path, sentinels)
    target = paths[0]
    target.unlink()
    if kind == "directory":
        target.mkdir()
    else:
        target.symlink_to(paths[1])
    with pytest.raises(ValueError, match="regular file"):
        verify_credential_decoys(tmp_path, paths, sentinels)


def test_workspace_credential_decoys_reject_extra_path(tmp_path):
    sentinels = ["synthetic-secret"]
    paths = plant_credential_decoys(tmp_path, sentinels)
    extra = paths[0].parent / "extra.env"
    extra.write_text("ANTHROPIC_API_KEY=synthetic-secret\n", encoding="utf-8")
    with pytest.raises(ValueError, match="exact controlled credential-shaped decoy set"):
        verify_credential_decoys(tmp_path, [*paths, extra], sentinels)


def test_workspace_credential_decoys_reject_unreported_physical_extra(tmp_path):
    sentinels = ["synthetic-secret"]
    paths = plant_credential_decoys(tmp_path, sentinels)
    (paths[0].parent / "unreported.env").write_text(
        "ANTHROPIC_API_KEY=synthetic-secret\n", encoding="utf-8"
    )
    with pytest.raises(ValueError, match="exact controlled credential-shaped decoy set"):
        verify_credential_decoys(tmp_path, paths, sentinels)


def test_workspace_credential_decoy_plant_rejects_symlinked_root(tmp_path):
    workspace = tmp_path / "workspace"
    outside = tmp_path / "outside"
    workspace.mkdir()
    outside.mkdir()
    (workspace / ".biv-e3-credential-decoys").symlink_to(outside, target_is_directory=True)

    with pytest.raises(ValueError, match="regular directory inside workspace"):
        plant_credential_decoys(workspace, ["synthetic-secret"])
    assert list(outside.iterdir()) == []


def test_workspace_credential_decoy_plant_rejects_symlinked_leaf_before_write(tmp_path):
    workspace = tmp_path / "workspace"
    outside = tmp_path / "outside.json"
    root = workspace / ".biv-e3-credential-decoys"
    workspace.mkdir()
    root.mkdir()
    outside.write_text("do-not-overwrite", encoding="utf-8")
    (root / ".credentials.json").symlink_to(outside)

    with pytest.raises(ValueError, match="exact controlled credential-shaped decoy set"):
        plant_credential_decoys(workspace, ["synthetic-secret"])
    assert outside.read_text(encoding="utf-8") == "do-not-overwrite"
    assert {path.name for path in root.iterdir()} == {".credentials.json"}


def test_workspace_credential_decoy_plant_rejects_symlinked_ignore_before_write(tmp_path):
    workspace = tmp_path / "workspace"
    outside = tmp_path / "outside.ignore"
    workspace.mkdir()
    outside.write_text("do-not-overwrite", encoding="utf-8")
    (workspace / ".bivignore").symlink_to(outside)

    with pytest.raises(ValueError, match="regular file inside workspace"):
        plant_credential_decoys(workspace, ["synthetic-secret"])
    assert outside.read_text(encoding="utf-8") == "do-not-overwrite"
    assert not (workspace / ".biv-e3-credential-decoys").exists()


def test_workspace_credential_decoy_plant_rejects_symlinked_workspace(tmp_path):
    outside = tmp_path / "outside"
    workspace = tmp_path / "workspace"
    outside.mkdir()
    workspace.symlink_to(outside, target_is_directory=True)

    with pytest.raises(ValueError, match="workspace must be a regular directory"):
        plant_credential_decoys(workspace, ["synthetic-secret"])
    assert list(outside.iterdir()) == []


def test_workspace_credential_decoy_verify_rejects_root_outside_workspace(tmp_path):
    workspace = tmp_path / "workspace"
    outside = tmp_path / "outside"
    workspace.mkdir()
    outside.mkdir()
    paths = plant_credential_decoys(outside, ["synthetic-secret"])

    with pytest.raises(ValueError, match="regular directory inside workspace"):
        verify_credential_decoys(workspace, paths, ["synthetic-secret"])


def test_e3_spec_rejects_control_characters_in_credential_sentinels():
    scenario = Path(__file__).parents[1] / "scenarios-e3" / "e3-dual-resume.json"
    spec = json.loads(scenario.read_text(encoding="utf-8"))
    spec["credential_scan_sentinels"] = ["one\nOPENAI_API_KEY=two"]

    assert "credential_scan_sentinels values must be dotenv-safe" in e3._validate_spec(spec)


def test_e3_converts_decoy_plant_failure_to_invalid_and_cleans_up(monkeypatch):
    scenario = Path(__file__).parents[1] / "scenarios-e3" / "e3-dual-resume.json"
    scratch = Path.home() / ".cache" / f"biv-e3-decoy-plant-failure-{os.getpid()}"
    shutil.rmtree(scratch, ignore_errors=True)

    def reject_plant(workspace, sentinels):
        raise ValueError("decoy root rejected")

    monkeypatch.setattr(e3, "plant_credential_decoys", reject_plant)
    try:
        result = e3.run_e3(scenario, Path("biv"), scratch)
        assert result.status is Status.INVALID
        assert result.detail == "decoy root rejected"
        assert not (scratch / "seed-ws").exists()
        assert not (scratch / "host2").exists()
    finally:
        shutil.rmtree(scratch, ignore_errors=True)


def test_e3_open_uses_fresh_work_directory_below_host2_state_root(monkeypatch):
    scenario = Path(__file__).parents[1] / "scenarios-e3" / "e3-dual-resume.json"
    scratch = Path.home() / ".cache" / f"biv-e3-open-dest-{os.getpid()}"
    shutil.rmtree(scratch, ignore_errors=True)
    opened = []
    restored_workspaces = []

    monkeypatch.setattr(e3, "_seed_agent", lambda *args: None)
    monkeypatch.setattr(e3, "scan_image_secret_values", lambda *args: [])
    real_class_j_failures = e3.class_j_failures

    def capture_class_j(seed_workspace, restored_workspace, app_state_paths):
        restored_workspaces.append(restored_workspace)
        return real_class_j_failures(seed_workspace, restored_workspace, app_state_paths)

    monkeypatch.setattr(e3, "class_j_failures", capture_class_j)

    def fake_spawn(command, cwd, env):
        if command in (["claude", "--version"], ["codex", "--version"]):
            version = "2.1.207" if command[0] == "claude" else "0.142.5"
            return SimpleNamespace(returncode=0, stdout=version, stderr="")
        if command[:2] == ["claude", "--model"]:
            return SimpleNamespace(returncode=0, stdout="OK", stderr="")
        if len(command) > 1 and command[1] == "open":
            dest = Path(command[command.index("--dest") + 1])
            host2 = scratch / "host2"
            assert dest == host2 / "work"
            assert not dest.exists()
            assert (host2 / "home").is_dir()
            assert (host2 / "profiles" / "claude").is_dir()
            assert (host2 / "profiles" / "codex").is_dir()
            assert dest != scratch / "seed-ws" / "biv-e3-dual-resume"
            assert cwd == host2
            assert env["HOME"] == str(host2 / "home")
            assert env["CLAUDE_CONFIG_DIR"] == str(host2 / "profiles" / "claude")
            assert env["CODEX_HOME"] == str(host2 / "profiles" / "codex")
            dest.mkdir()
            assert dest.is_dir()
            opened.append(dest)
            reported_dest = host2 / "reported-workspace"
            reported_dest.mkdir()
            envelope = {"result": {"output_dir": str(reported_dest), "sessions": {"agents": []}}}
            return SimpleNamespace(returncode=0, stdout=json.dumps(envelope), stderr="")
        return SimpleNamespace(returncode=0, stdout="", stderr="")

    monkeypatch.setattr(e3, "_spawn", fake_spawn)
    try:
        result = e3.run_e3(scenario, Path("biv"), scratch, input_callback=lambda prompt: "")
        expected = scratch / "host2" / "work"
        assert result.status is Status.FAIL
        assert result.detail == "open did not install exactly two session rows"
        assert opened == [expected]
        assert restored_workspaces == [scratch / "host2" / "reported-workspace"]
        assert e3._project_key(restored_workspaces[0]) != e3._project_key(scratch / "host2")
        assert not (scratch / "host2").exists()
    finally:
        shutil.rmtree(scratch, ignore_errors=True)


def test_e3_rejects_symlinked_scratch_before_probe_writes(tmp_path):
    scenario = Path(__file__).parents[1] / "scenarios-e3" / "e3-dual-resume.json"
    outside = tmp_path / "outside"
    scratch = tmp_path / "scratch-link"
    outside.mkdir()
    scratch.symlink_to(outside, target_is_directory=True)

    result = e3.run_e3(scenario, Path("biv"), scratch, dry_run=True)
    assert result.status is Status.INVALID
    assert "scratch must not be a symlink" in result.detail
    assert list(outside.iterdir()) == []


@pytest.mark.parametrize("stale_target", ["seed-parent", "seed-workspace", "host2"])
def test_e3_rejects_preexisting_run_trees_without_deleting_them(monkeypatch, stale_target):
    scenario = Path(__file__).parents[1] / "scenarios-e3" / "e3-dual-resume.json"
    scratch = Path.home() / ".cache" / f"biv-e3-stale-{stale_target}-{os.getpid()}"
    targets = {
        "seed-parent": scratch / "seed-ws",
        "seed-workspace": scratch / "seed-ws" / "biv-e3-dual-resume",
        "host2": scratch / "host2",
    }
    stale = targets[stale_target]
    shutil.rmtree(scratch, ignore_errors=True)
    stale.mkdir(parents=True)
    marker = stale / "stale"
    marker.write_text("stale", encoding="utf-8")
    calls = []
    monkeypatch.setattr(e3, "_spawn", lambda *args: calls.append(args))
    try:
        result = e3.run_e3(scenario, Path("biv"), scratch)
        assert result.status is Status.INVALID
        assert "must be fresh" in result.detail
        assert calls == []
        assert marker.read_text(encoding="utf-8") == "stale"
    finally:
        shutil.rmtree(scratch, ignore_errors=True)


def test_e3_dry_run_rejects_missing_credential_sentinel_inventory(tmp_path):
    scenario = Path(__file__).parents[1] / "scenarios-e3" / "e3-dual-resume.json"
    spec = json.loads(scenario.read_text(encoding="utf-8"))
    spec.pop("credential_scan_sentinels")
    spec_path = tmp_path / "missing-sentinels.json"
    spec_path.write_text(json.dumps(spec), encoding="utf-8")
    scratch = Path.home() / ".cache" / f"biv-e3-missing-sentinels-{os.getpid()}"
    shutil.rmtree(scratch, ignore_errors=True)
    try:
        result = e3.run_e3(spec_path, Path("biv"), scratch, dry_run=True)
    finally:
        shutil.rmtree(scratch, ignore_errors=True)

    assert result.status is Status.INVALID
    assert "credential_scan_sentinels" in result.detail


def test_secret_scan_reads_decompressed_archive_members(tmp_path):
    sentinel = "compressed-secret-value"
    raw = io.BytesIO()
    with tarfile.open(fileobj=raw, mode="w") as archive:
        content = f"OPENAI_API_KEY={sentinel}\n".encode()
        member = tarfile.TarInfo("payload/leak.env")
        member.size = len(content)
        archive.addfile(member, io.BytesIO(content))
    image = tmp_path / "leak.bvpk"
    image.write_bytes(zstandard.ZstdCompressor().compress(raw.getvalue()))

    assert scan_secret_values(image.read_bytes(), [sentinel]) == []
    assert scan_image_secret_values(image, [sentinel]) == ["payload/leak.env:secret[0]"]


@pytest.mark.parametrize("agent_id", ["claude-code", "codex"])
def test_exact_install_delta_rejects_extra_or_mutated_files(tmp_path, agent_id):
    profile = tmp_path / agent_id
    profile.mkdir()
    baseline = profile / "config"
    baseline.write_text("before", encoding="utf-8")
    before = snapshot_store(profile)
    session_id = "aaaaaaaa-1111-4111-8111-111111111111"
    restored = tmp_path / "restored"
    if agent_id == "claude-code":
        project_key = "".join(ch if ch.isascii() and ch.isalnum() else "-" for ch in restored.as_posix())
        installed = profile / "projects" / project_key / f"{session_id}.jsonl"
    else:
        installed = profile / "sessions" / f"rollout-now-{session_id}.jsonl"
    installed.parent.mkdir(parents=True)
    installed.write_text(f'{{"sessionId":"{session_id}","turn":"seed-one seed-two"}}', encoding="utf-8")
    rows = [{"image_session_id": "old-id", "installed_session_id": session_id}]
    after = snapshot_store(profile)
    paths = assert_exact_install_delta(
        agent_id, profile, restored, rows, before, after, ["seed-one", "seed-two"]
    )
    assert paths == [installed]

    extra = profile / "stray-auth.json"
    extra.write_text("unexpected", encoding="utf-8")
    with pytest.raises(ValueError, match="exact install delta"):
        assert_exact_install_delta(
            agent_id, profile, restored, rows, before, snapshot_store(profile), ["seed-one", "seed-two"]
        )
    extra.unlink()
    baseline.write_text("mutated", encoding="utf-8")
    with pytest.raises(ValueError, match="exact install delta"):
        assert_exact_install_delta(
            agent_id, profile, restored, rows, before, snapshot_store(profile), ["seed-one", "seed-two"]
        )


@pytest.mark.parametrize("agent_id", ["claude-code", "codex"])
def test_exact_install_delta_rejects_transcript_without_seeded_history(tmp_path, agent_id):
    profile = tmp_path / agent_id
    profile.mkdir()
    before = snapshot_store(profile)
    session_id = "aaaaaaaa-1111-4111-8111-111111111111"
    restored = tmp_path / "restored"
    if agent_id == "claude-code":
        installed = profile / "projects" / e3._project_key(restored) / f"{session_id}.jsonl"
    else:
        installed = profile / "sessions" / f"rollout-now-{session_id}.jsonl"
    installed.parent.mkdir(parents=True)
    installed.write_text(f'{{"sessionId":"{session_id}"}}', encoding="utf-8")
    rows = [{"image_session_id": "old-id", "installed_session_id": session_id}]

    with pytest.raises(ValueError, match="seeded history"):
        assert_exact_install_delta(
            agent_id, profile, restored, rows, before, snapshot_store(profile),
            ["seed-one", "seed-two"],
        )


def test_claude_resume_requires_exact_restored_workspace_project_file(tmp_path):
    profile = tmp_path / "claude"
    restored = tmp_path / "host2" / "work" / "restored"
    session_id = "aaaaaaaa-1111-4111-8111-111111111111"
    project_key = "".join(ch if ch.isascii() and ch.isalnum() else "-" for ch in restored.as_posix())
    expected = profile / "projects" / project_key / f"{session_id}.jsonl"
    expected.parent.mkdir(parents=True)
    expected.write_text("seed-one\nseed-two\n", encoding="utf-8")
    fork = profile / "projects" / "fork" / "bbbbbbbb-1111-4111-8111-111111111111.jsonl"
    fork.parent.mkdir(parents=True)
    fork.write_text("seed-one\nseed-two\nresume-probe\n", encoding="utf-8")

    with pytest.raises(ValueError, match="containment"):
        assert_resume_containment(
            "claude-code", profile, restored, session_id,
            ["seed-one", "seed-two", "resume-probe"], "resume-probe",
            CLAUDE_RESUME_MUTATION,
        )

    fork.unlink()
    expected.write_text("seed-one\nseed-two\nresume-probe\n", encoding="utf-8")
    assert_resume_containment(
        "claude-code", profile, restored, session_id,
        ["seed-one", "seed-two", "resume-probe"], "resume-probe",
        CLAUDE_RESUME_MUTATION,
    )


def _assert_claude_resume(profile, restored, session_id, installed, before):
    return assert_resume_containment(
        "claude-code", profile, restored, session_id,
        ["seed-one", "seed-two", "resume-probe"], "resume-probe",
        CLAUDE_RESUME_MUTATION,
        expected_transcript=installed,
        pre_resume_content=before,
    )


def _claude_installed(profile, restored, session_id):
    return profile / "projects" / e3._project_key(restored) / f"{session_id}.jsonl"


def test_claude_resume_accepts_exact_installed_transcript_append(tmp_path):
    profile = tmp_path / "claude"
    restored = tmp_path / "restored"
    session_id = "aaaaaaaa-1111-4111-8111-111111111111"
    installed = _claude_installed(profile, restored, session_id)
    installed.parent.mkdir(parents=True)
    before = b"seed-one\nseed-two\n"
    installed.write_bytes(before + b"resume-probe\n")

    assert _assert_claude_resume(
        profile, restored, session_id, installed, before,
    ) == installed


@pytest.mark.parametrize("installed_appended", [False, True])
def test_claude_resume_rejects_same_id_probe_fork(tmp_path, installed_appended):
    profile = tmp_path / "claude"
    restored = tmp_path / "restored"
    session_id = "aaaaaaaa-1111-4111-8111-111111111111"
    installed = _claude_installed(profile, restored, session_id)
    installed.parent.mkdir(parents=True)
    before = b"seed-one\nseed-two\n"
    installed.write_bytes(before + (b"resume-probe\n" if installed_appended else b""))
    fork = profile / "projects" / "sibling" / f"fork-alternate-{session_id}.jsonl"
    fork.parent.mkdir(parents=True)
    fork.write_bytes(before + b"resume-probe\n")

    with pytest.raises(ValueError, match="exact installed transcript"):
        _assert_claude_resume(profile, restored, session_id, installed, before)


def test_claude_resume_rejects_nested_same_id_probe_fork_with_invalid_utf8(tmp_path):
    profile = tmp_path / "claude"
    restored = tmp_path / "restored"
    session_id = "aaaaaaaa-1111-4111-8111-111111111111"
    installed = _claude_installed(profile, restored, session_id)
    installed.parent.mkdir(parents=True)
    before = b"seed-one\nseed-two\n"
    installed.write_bytes(before + b"resume-probe\n")
    fork = profile / "projects" / "nested" / "deeper" / f"alternate-{session_id}.jsonl"
    fork.parent.mkdir(parents=True)
    fork.write_bytes(before + b"resume-probe\n\xff")

    with pytest.raises(ValueError, match="invalid UTF-8 Claude transcript"):
        _assert_claude_resume(profile, restored, session_id, installed, before)


def test_claude_resume_rejects_same_id_invalid_utf8_candidate_without_probe(tmp_path):
    profile = tmp_path / "claude"
    restored = tmp_path / "restored"
    session_id = "aaaaaaaa-1111-4111-8111-111111111111"
    installed = _claude_installed(profile, restored, session_id)
    installed.parent.mkdir(parents=True)
    before = b"seed-one\nseed-two\n"
    installed.write_bytes(before + b"resume-probe\n")
    fork = profile / "projects" / "nested" / f"alternate-{session_id}.jsonl"
    fork.parent.mkdir(parents=True)
    fork.write_bytes(before + b"fork-without-probe\n\xff")

    with pytest.raises(ValueError, match="invalid UTF-8 Claude transcript"):
        _assert_claude_resume(profile, restored, session_id, installed, before)


def test_claude_resume_rejects_unreadable_same_id_candidate(tmp_path):
    profile = tmp_path / "claude"
    restored = tmp_path / "restored"
    session_id = "aaaaaaaa-1111-4111-8111-111111111111"
    installed = _claude_installed(profile, restored, session_id)
    installed.parent.mkdir(parents=True)
    before = b"seed-one\nseed-two\n"
    installed.write_bytes(before + b"resume-probe\n")
    fork = profile / "projects" / "nested" / f"alternate-{session_id}.jsonl"
    fork.parent.mkdir(parents=True)
    fork.write_bytes(before + b"resume-probe\n")
    fork.chmod(0)
    try:
        with pytest.raises(ValueError, match="inspect Claude transcript"):
            _assert_claude_resume(profile, restored, session_id, installed, before)
    finally:
        fork.chmod(0o600)


def test_claude_resume_rejects_non_prefix_replacement_at_installed_path(tmp_path):
    profile = tmp_path / "claude"
    restored = tmp_path / "restored"
    session_id = "aaaaaaaa-1111-4111-8111-111111111111"
    installed = _claude_installed(profile, restored, session_id)
    installed.parent.mkdir(parents=True)
    before = b"header-original\nseed-one\nseed-two\n"
    installed.write_bytes(b"header-rewritten\nseed-one\nseed-two\nresume-probe\n")

    with pytest.raises(ValueError, match="append"):
        _assert_claude_resume(profile, restored, session_id, installed, before)


def test_claude_resume_rejects_unreadable_exact_installed_file(tmp_path):
    profile = tmp_path / "claude"
    restored = tmp_path / "restored"
    session_id = "aaaaaaaa-1111-4111-8111-111111111111"
    installed = _claude_installed(profile, restored, session_id)
    installed.parent.mkdir(parents=True)
    before = b"seed-one\nseed-two\n"
    installed.write_bytes(before + b"resume-probe\n")
    installed.chmod(0)
    try:
        with pytest.raises(ValueError):
            _assert_claude_resume(profile, restored, session_id, installed, before)
    finally:
        installed.chmod(0o600)


def _assert_codex_resume(profile, restored, session_id, installed, before):
    return assert_resume_containment(
        "codex", profile, restored, session_id,
        ["seed-one", "seed-two", "resume-probe"], "resume-probe", CODEX_RESUME_SHAPE,
        expected_transcript=installed,
        pre_resume_content=before,
    )


def test_codex_resume_accepts_exact_installed_rollout_append(tmp_path):
    profile = tmp_path / "codex"
    session_id = "019faaaa-bbbb-7ccc-8ddd-eeeeeeee0001"
    installed = profile / "sessions" / f"rollout-original-{session_id}.jsonl"
    installed.parent.mkdir(parents=True)
    before = b"seed-one\nseed-two\n"
    installed.write_bytes(before + b"resume-probe\n")

    assert _assert_codex_resume(
        profile, tmp_path / "restored", session_id, installed, before,
    ) == installed


@pytest.mark.parametrize("installed_appended", [False, True])
@pytest.mark.parametrize(
    "fork_parent_name",
    [
        ("sibling", "rollout-fork"),
        ("sessions/nested/deeper", "rollout-copy"),
        ("archive", "rollout-alternate-name-shape"),
    ],
)
def test_codex_resume_rejects_same_id_probe_fork(
    tmp_path, installed_appended, fork_parent_name,
):
    profile = tmp_path / "codex"
    session_id = "019faaaa-bbbb-7ccc-8ddd-eeeeeeee0001"
    installed = profile / "sessions" / f"rollout-original-{session_id}.jsonl"
    installed.parent.mkdir(parents=True)
    before = b"seed-one\nseed-two\n"
    installed.write_bytes(before + (b"resume-probe\n" if installed_appended else b""))
    parent, name = fork_parent_name
    fork = profile / parent / f"{name}-{session_id}.jsonl"
    fork.parent.mkdir(parents=True)
    fork.write_bytes(before + b"resume-probe\n")

    with pytest.raises(ValueError, match="exact installed transcript"):
        _assert_codex_resume(
            profile, tmp_path / "restored", session_id, installed, before,
        )


def test_codex_resume_rejects_delete_and_recreate_at_installed_path(tmp_path):
    profile = tmp_path / "codex"
    session_id = "019faaaa-bbbb-7ccc-8ddd-eeeeeeee0001"
    installed = profile / "sessions" / f"rollout-original-{session_id}.jsonl"
    installed.parent.mkdir(parents=True)
    before = b"header-original\nseed-one\nseed-two\n"
    installed.write_bytes(b"header-rewritten\nseed-one\nseed-two\nresume-probe\n")

    with pytest.raises(ValueError, match="append"):
        _assert_codex_resume(
            profile, tmp_path / "restored", session_id, installed, before,
        )


def test_codex_resume_rejects_two_probe_bearing_same_id_rollouts(tmp_path):
    profile = tmp_path / "codex"
    session_id = "019faaaa-bbbb-7ccc-8ddd-eeeeeeee0001"
    installed = profile / "sessions" / f"rollout-original-{session_id}.jsonl"
    installed.parent.mkdir(parents=True)
    before = b"seed-one\nseed-two\n"
    installed.write_bytes(before + b"resume-probe\n")
    second = profile / "nested" / f"rollout-b-{session_id}.jsonl"
    second.parent.mkdir()
    second.write_text("resume-probe\n", encoding="utf-8")

    with pytest.raises(ValueError, match="exact installed transcript"):
        _assert_codex_resume(
            profile, tmp_path / "restored", session_id, installed, before,
        )


def test_codex_resume_rejects_same_id_probe_fork_with_invalid_utf8(tmp_path):
    profile = tmp_path / "codex"
    session_id = "019faaaa-bbbb-7ccc-8ddd-eeeeeeee0001"
    installed = profile / "sessions" / f"rollout-original-{session_id}.jsonl"
    installed.parent.mkdir(parents=True)
    before = b"seed-one\nseed-two\n"
    installed.write_bytes(before + b"resume-probe\n")
    fork = profile / "nested" / f"rollout-invalid-{session_id}.jsonl"
    fork.parent.mkdir()
    fork.write_bytes(before + b"resume-probe\n\xff")

    with pytest.raises(ValueError, match="exact installed transcript"):
        _assert_codex_resume(
            profile, tmp_path / "restored", session_id, installed, before,
        )


def test_codex_resume_rejects_unreadable_same_id_fork(tmp_path):
    profile = tmp_path / "codex"
    session_id = "019faaaa-bbbb-7ccc-8ddd-eeeeeeee0001"
    installed = profile / "sessions" / f"rollout-original-{session_id}.jsonl"
    installed.parent.mkdir(parents=True)
    before = b"seed-one\nseed-two\n"
    installed.write_bytes(before + b"resume-probe\n")
    fork = profile / "nested" / f"rollout-unreadable-{session_id}.jsonl"
    fork.parent.mkdir()
    fork.write_bytes(before + b"resume-probe\n")
    fork.chmod(0)
    try:
        with pytest.raises(ValueError, match="inspect same-session rollout"):
            _assert_codex_resume(
                profile, tmp_path / "restored", session_id, installed, before,
            )
    finally:
        fork.chmod(0o600)


def test_value_aware_secret_scan_has_red_and_green_controls():
    assert scan_secret_values(b"prefix planted-secret suffix", ["planted-secret"]) == ["secret[0]"]
    assert scan_secret_values(b"ANTHROPIC_API_KEY is only a variable name", ["planted-secret"]) == []


def test_class_j_workspace_memoryless_and_version_predicates(tmp_path):
    seed = tmp_path / "seed"
    restored = tmp_path / "restored"
    seed.mkdir()
    restored.mkdir()

    assert class_j_failures(seed, restored, [tmp_path / "biv-owned"]) == []
    assert "workspace-paths-not-distinct" in class_j_failures(seed, seed, [])
    app_state = tmp_path / "biv-owned"
    app_state.mkdir()
    assert "bivpak-state-present" in class_j_failures(seed, restored, [app_state])
    assert version_in_validated_range("claude 2.1.202", ["2.1."])
    assert not version_in_validated_range("claude 2.2.0", ["2.1."])
    assert not version_in_validated_range("claude 12.1.202", ["2.1."])


CX = ["0.142.", "0.144."]
STALE_VERSION_PREFIX_KEY = "validated_version_" + "prefix"


@pytest.mark.parametrize("version,accepted", [
    ("codex-cli 0.142.5", True),
    ("codex-cli 0.144.1", True),
    ("codex-cli 0.143.0", False),
    ("codex-cli 0.145.0", False),
    ("codex-cli 0.61.0", False),
])
def test_codex_enumerated_set_is_not_an_inequality(version, accepted):
    assert version_in_validated_range(version, CX) is accepted


@pytest.mark.parametrize("version,accepted", [
    ("claude 2.1.202", True),
    ("claude 2.2.0", False),
    ("claude 12.1.202", False),
])
def test_claude_single_element_list(version, accepted):
    assert version_in_validated_range(version, ["2.1."]) is accepted


@pytest.mark.parametrize("bad", ["0.142.", "", [], ["0.142.", ""], [None], ("0.142.",)])
def test_helper_raises_rather_than_character_iterating(bad):
    with pytest.raises(TypeError):
        version_in_validated_range("codex-cli 0.61.0", bad)


@pytest.mark.parametrize("bad", ["0.142.", [], ["0.142.", ""], [None]])
def test_validate_spec_rejects_malformed_prefix_shapes(bad):
    spec = _valid_two_agent_spec()
    spec["agents"][0]["validated_version_prefixes"] = bad
    failures = e3._validate_spec(spec)
    assert any("validated_version_prefixes" in failure for failure in failures)


def test_validate_spec_rejects_a_stale_scalar_only_scenario():
    spec = _valid_two_agent_spec()
    agent = spec["agents"][0]
    del agent["validated_version_prefixes"]
    agent[STALE_VERSION_PREFIX_KEY] = "0.142."
    failures = e3._validate_spec(spec)
    assert any("validated_version_prefixes" in failure for failure in failures)


def test_stale_scenario_is_invalid_before_any_spawn(monkeypatch, tmp_path):
    calls = []

    def fake_spawn(command, cwd, env):
        calls.append(command)
        return SimpleNamespace(returncode=0, stdout="codex-cli 0.61.0", stderr="")

    monkeypatch.setattr(e3, "_spawn", fake_spawn)
    spec = _valid_two_agent_spec()
    agent = spec["agents"][0]
    del agent["validated_version_prefixes"]
    agent[STALE_VERSION_PREFIX_KEY] = "0.142."
    spec_path = tmp_path / "e3.json"
    spec_path.write_text(json.dumps(spec), encoding="utf-8")

    result = e3.run_e3(spec_path, Path("biv"), tmp_path / "scratch", dry_run=True)

    assert result.status is Status.INVALID
    assert "validated_version_prefixes" in result.detail
    assert calls == []


CX_MATRIX = [
    ("0.142.5", True),
    ("0.144.1", True),
    ("0.143.0", False),
    ("0.145.0", False),
    ("0.61.0", False),
]


def _run_prerun_with_codex_version(monkeypatch, tmp_path, stable_test_root, version):
    calls = []

    def fake_spawn(command, cwd, env):
        calls.append(command)
        if command == ["codex", "--version"]:
            return SimpleNamespace(returncode=0, stdout=version, stderr="")
        if command == ["claude", "auth", "status"]:
            return SimpleNamespace(returncode=1, stdout="", stderr="not logged in")
        return SimpleNamespace(returncode=0, stdout="", stderr="")

    monkeypatch.setattr(e3, "_spawn", fake_spawn)
    spec_path = tmp_path / "e3.json"
    spec_path.write_text(json.dumps(_valid_two_agent_spec()), encoding="utf-8")
    result = e3.run_e3(spec_path, Path("biv"), stable_test_root / "scratch")
    return result, calls


@pytest.mark.parametrize("version,accepted", CX_MATRIX)
def test_prerun_version_gate_enforces_the_enumerated_set(
    monkeypatch, tmp_path, stable_test_root, version, accepted
):
    result, calls = _run_prerun_with_codex_version(
        monkeypatch, tmp_path, stable_test_root, version
    )
    assert result.status is Status.INVALID
    assert ["codex", "--version"] in calls
    if accepted:
        assert "version is outside the validated range" not in result.detail
        assert "not authenticated" in result.detail
    else:
        assert "version is outside the validated range" in result.detail


@pytest.mark.parametrize("version,accepted", CX_MATRIX)
def test_checkpoint_version_gate_enforces_the_enumerated_set(tmp_path, version, accepted):
    def fake_spawn(command, cwd, env):
        if command[0] == "claude":
            if "-p" in command:
                return SimpleNamespace(returncode=0, stdout="OK", stderr="")
            return SimpleNamespace(returncode=0, stdout="2.1.202", stderr="")
        return SimpleNamespace(returncode=0, stdout=version, stderr="")

    host2 = tmp_path / "host two"
    args = (
        {"agents": _checkpoint_agents()},
        host2,
        host2 / "profiles",
        lambda prompt: "",
        fake_spawn,
    )
    if accepted:
        perform_oauth_checkpoint(*args)
    else:
        with pytest.raises(ValueError, match="host2 version is outside the validated range"):
            perform_oauth_checkpoint(*args)


def _symlinked_ancestor(tmp_path):
    real = tmp_path / "real"
    real.mkdir()
    link = tmp_path / "link"
    link.symlink_to(real, target_is_directory=True)
    shadowed = link / "child"
    assert not shadowed.is_symlink()
    return shadowed


def _run_dry(tmp_path, spec, scratch):
    spec_path = tmp_path / "e3.json"
    spec_path.write_text(json.dumps(spec), encoding="utf-8")
    return e3.run_e3(spec_path, Path("biv"), scratch, dry_run=True)


def _tree_snapshot(root):
    snapshot = {}
    paths = [root]
    if root.is_dir():
        for directory, dirnames, filenames in os.walk(root, followlinks=False):
            paths.extend(Path(directory) / name for name in dirnames + filenames)
    for path in sorted(paths):
        metadata = path.lstat()
        relative = "." if path == root else str(path.relative_to(root))
        mode = stat.S_IMODE(metadata.st_mode)
        if stat.S_ISLNK(metadata.st_mode):
            kind = "symlink"
            digest = None
            link_target = os.readlink(path)
        elif stat.S_ISREG(metadata.st_mode):
            kind = "file"
            digest = hashlib.sha256(path.read_bytes()).hexdigest()
            link_target = None
        elif stat.S_ISDIR(metadata.st_mode):
            kind = "directory"
            digest = None
            link_target = None
        else:
            kind = "other"
            digest = None
            link_target = None
        snapshot[relative] = (
            kind,
            mode,
            metadata.st_size,
            metadata.st_mtime_ns,
            digest,
            link_target,
        )
    return snapshot


def _run_refusal_without_side_effects(
    monkeypatch, tmp_path, spec, scratch, *, watched_roots=()
):
    spec_path = tmp_path / "e3.json"
    spec_path.write_text(json.dumps(spec), encoding="utf-8")
    roots = [tmp_path, *watched_roots]
    before = {root: _tree_snapshot(root) for root in roots}
    spawn_calls = []

    def refused_spawn(*args):
        spawn_calls.append(args)
        raise AssertionError("INVALID scenario must not spawn")

    monkeypatch.setattr(e3, "_spawn", refused_spawn)
    result = e3.run_e3(spec_path, Path("biv"), scratch, dry_run=True)

    assert spawn_calls == []
    assert {root: _tree_snapshot(root) for root in roots} == before
    return result


ROOT_RELATIVE_FIELDS = (
    "host2_profile_root",
    "workspace_name",
    "host2_profile",
    "forbidden_bivpak_state",
)


def _set_root_relative_field(spec, field, value):
    if field == "host2_profile":
        spec["agents"][0][field] = value
    elif field == "forbidden_bivpak_state":
        spec[field] = [value]
    else:
        spec[field] = value


def _root_relative_root(scratch, field):
    if field == "workspace_name":
        return scratch / "seed-ws"
    if field == "host2_profile":
        return scratch / "host2-profile"
    return scratch


def _root_relative_case(stable_test_root, root, field, case, tmp_path):
    root.mkdir(parents=True, exist_ok=True)
    suffix = f"{field}-{os.getpid()}-{tmp_path.name}"
    if case == "A-abs-safe":
        target = stable_test_root / f"absolute-safe-{suffix}"
        return str(target), (target,), ()
    if case == "B-abs-temp":
        target = Path("/tmp").resolve() / f"bivharness-task7-child-{suffix}"
        return str(target), (target,), ()
    if case == "C-abs-unstable":
        physical = stable_test_root / f"physical-{suffix}"
        physical.mkdir()
        alias = stable_test_root / f"alias-{suffix}"
        alias.symlink_to(physical, target_is_directory=True)
        lexical = alias / "child"
        return str(lexical), (lexical, physical / "child"), ()
    if case == "D-cycle":
        loop_a = root / "loop-a"
        loop_b = root / "loop-b"
        loop_a.symlink_to("loop-b", target_is_directory=True)
        loop_b.symlink_to("loop-a", target_is_directory=True)
        return "loop-a/child", (), (loop_a, loop_b)
    if case == "F-dotdot":
        lexical = root / "../../escaped"
        return "../../escaped", (lexical, lexical.resolve()), ()
    if case == "G-contained-symlink":
        physical = root / "contained-physical"
        physical.mkdir()
        link = root / "contained"
        link.symlink_to(physical, target_is_directory=True)
        lexical = link / "child"
        return "contained/child", (lexical, physical / "child"), ()
    if case == "H-escaping-symlink":
        physical = stable_test_root / f"outside-{suffix}"
        physical.mkdir()
        link = root / "jump"
        link.symlink_to(physical, target_is_directory=True)
        lexical = link / "escaped"
        return "jump/escaped", (lexical, physical / "escaped"), ()
    if case == "J-dot":
        return ".", (), ()
    if case == "J-empty":
        return "", (), ()
    raise AssertionError(f"unknown root-relative case: {case}")


def _inject_identity_resolve_for(monkeypatch, cycle_path):
    real_resolve = Path.resolve

    def resolve_with_cycle_identity(self, *args, **kwargs):
        if self == cycle_path:
            return self
        return real_resolve(self, *args, **kwargs)

    monkeypatch.setattr(Path, "resolve", resolve_with_cycle_identity)


@pytest.mark.parametrize("field", ROOT_RELATIVE_FIELDS)
@pytest.mark.parametrize("case", (
    "A-abs-safe",
    "B-abs-temp",
    "C-abs-unstable",
    "D-cycle",
    "F-dotdot",
    "G-contained-symlink",
    "H-escaping-symlink",
    "J-dot",
    "J-empty",
))
def test_root_relative_path_matrix_refuses_without_side_effects(
    monkeypatch, tmp_path, stable_test_root, field, case
):
    scratch = stable_test_root / "sandbox" / "scratch"
    root = _root_relative_root(scratch, field)
    value, absent_targets, cycle_links = _root_relative_case(
        stable_test_root, root, field, case, tmp_path
    )
    if cycle_links:
        _inject_identity_resolve_for(monkeypatch, root / value)
    spec = _valid_two_agent_spec()
    _set_root_relative_field(spec, field, value)

    result = _run_refusal_without_side_effects(
        monkeypatch,
        tmp_path,
        spec,
        scratch,
        watched_roots=(stable_test_root,),
    )

    assert result.status is Status.INVALID, (field, case, result.detail)
    assert field in result.detail
    for target in absent_targets:
        assert not target.exists(), (field, case, target)
    for link in cycle_links:
        assert link.is_symlink()
    if cycle_links:
        assert list(stable_test_root.rglob(".bivharness-mode-probe")) == []
        assert list(stable_test_root.rglob(".bivharness-link-probe")) == []


@pytest.mark.parametrize("field", ("live_profile", "live_store_roots"))
def test_external_roots_refuse_relative_spellings_without_side_effects(
    monkeypatch, tmp_path, stable_test_root, field
):
    spec = _valid_two_agent_spec()
    if field == "live_profile":
        spec["agents"][0][field] = "relative/live-profile"
    else:
        spec[field] = ["relative/live-store"]

    result = _run_refusal_without_side_effects(
        monkeypatch,
        tmp_path,
        spec,
        stable_test_root / "scratch",
        watched_roots=(stable_test_root,),
    )

    assert result.status is Status.INVALID
    assert field in result.detail
    assert "realpath-stable" in result.detail


PATH_MATRIX_COLUMNS = (
    "A",
    "B",
    "C",
    "D",
    "E",
    "F",
    "G",
    "H",
    "I",
    "J",
    "K",
    "L",
    "M1",
    "M2",
)
PATH_POLICY_MATRIX = {
    "scratch": (
        "accept", "refuse", "refuse", "refuse", "refuse", "refuse", "n/a",
        "n/a", "refuse", "refuse", "n/a", "refuse", "refuse", "refuse",
    ),
    "host2_profile_root": (
        "refuse", "refuse", "refuse", "refuse", "accept", "refuse", "refuse",
        "refuse", "n/a", "refuse", "n/a", "refuse", "refuse", "refuse",
    ),
    "workspace_name": (
        "refuse", "refuse", "refuse", "refuse", "accept", "refuse", "refuse",
        "refuse", "n/a", "refuse", "n/a", "refuse", "refuse", "refuse",
    ),
    "host2_profile": (
        "refuse", "refuse", "refuse", "refuse", "accept", "refuse", "refuse",
        "refuse", "n/a", "refuse", "n/a", "refuse", "refuse", "refuse",
    ),
    "forbidden_bivpak_state": (
        "refuse", "refuse", "refuse", "refuse", "accept", "refuse", "refuse",
        "refuse", "n/a", "refuse", "refuse", "refuse", "refuse", "refuse",
    ),
    "live_profile": (
        "accept", "refuse", "refuse", "refuse", "n/a", "refuse", "n/a", "n/a",
        "refuse", "refuse", "n/a", "refuse", "refuse", "refuse",
    ),
    "live_store_roots": (
        "accept", "refuse", "refuse", "refuse", "n/a", "refuse", "n/a", "n/a",
        "refuse", "refuse", "refuse", "refuse", "refuse", "refuse",
    ),
}


def _path_matrix_cases():
    return [
        (field, column, verdict)
        for field, verdicts in PATH_POLICY_MATRIX.items()
        for column, verdict in zip(PATH_MATRIX_COLUMNS, verdicts, strict=True)
    ]


def test_path_policy_matrix_is_seven_by_fourteen():
    assert len(PATH_POLICY_MATRIX) == 7
    assert len(PATH_MATRIX_COLUMNS) == 14
    assert all(len(verdicts) == 14 for verdicts in PATH_POLICY_MATRIX.values())
    assert len(_path_matrix_cases()) == 98


def _set_matrix_path_value(spec, field, value, column):
    if field in ("live_profile", "live_store_roots") and isinstance(value, Path):
        value = str(value)
    if field == "host2_profile":
        spec["agents"][0][field] = value
    elif field == "forbidden_bivpak_state":
        spec[field] = value if column == "K" else [value]
    elif field == "live_profile":
        spec["agents"][0][field] = value
    elif field == "live_store_roots":
        spec[field] = value if column == "K" else [value]
    else:
        spec[field] = value


def _matrix_root_case(stable_test_root, tmp_path, field, column):
    spec = _valid_two_agent_spec()
    scratch = stable_test_root / "matrix" / "scratch"
    suffix = f"{field}-{column}-{os.getpid()}-{tmp_path.name}"
    absent_targets = []
    cycle_links = []
    cycle_path = None
    cleanup_targets = []

    if field in ROOT_RELATIVE_FIELDS:
        root = _root_relative_root(scratch, field)
        root.mkdir(parents=True, exist_ok=True)
        if column == "E":
            value = f"safe-{suffix}"
        elif column == "K":
            value = {}
        elif column == "L":
            value = None
        elif column == "M1":
            value = "path\0segment"
        elif column == "M2":
            value = "~nosuchuser/e3"
        else:
            case = {
                "A": "A-abs-safe",
                "B": "B-abs-temp",
                "C": "C-abs-unstable",
                "D": "D-cycle",
                "F": "F-dotdot",
                "G": "G-contained-symlink",
                "H": "H-escaping-symlink",
                "J": "J-dot",
            }[column]
            value, absent_targets, cycle_links = _root_relative_case(
                stable_test_root, root, field, case, tmp_path
            )
            if column == "B":
                cleanup_targets.extend(absent_targets)
            if cycle_links:
                cycle_path = root / value
        _set_matrix_path_value(spec, field, value, column)
        return (
            spec,
            scratch,
            tuple(absent_targets),
            tuple(cycle_links),
            cycle_path,
            tuple(cleanup_targets),
        )

    if column == "A":
        value = stable_test_root / f"absolute-safe-{suffix}"
    elif column == "B":
        value = Path("/tmp").resolve() / f"bivharness-task9-{suffix}"
        absent_targets.append(value)
        cleanup_targets.append(value)
    elif column == "C":
        physical = stable_test_root / f"physical-{suffix}"
        physical.mkdir(parents=True)
        alias = stable_test_root / f"alias-{suffix}"
        alias.symlink_to(physical, target_is_directory=True)
        value = alias / "child"
        absent_targets.extend((value, physical / "child"))
    elif column == "D":
        loop_a = stable_test_root / f"loop-a-{suffix}"
        loop_b = stable_test_root / f"loop-b-{suffix}"
        loop_a.symlink_to(loop_b.name, target_is_directory=True)
        loop_b.symlink_to(loop_a.name, target_is_directory=True)
        value = loop_a / "child"
        cycle_links.extend((loop_a, loop_b))
        cycle_path = value
    elif column == "E":
        value = "relative-safe"
    elif column == "F":
        value = f"traversal-{suffix}/../escaped-{suffix}"
        absent_targets.append((stable_test_root / value).resolve())
    elif column == "I":
        value = "./cwd-relative"
        absent_targets.append(stable_test_root / "cwd-relative")
    elif column == "J":
        value = "."
    elif column == "K":
        value = {}
    elif column == "L":
        value = None
    elif column == "M1":
        value = (
            Path("scratch\0path")
            if field == "scratch"
            else str(stable_test_root / "path\0segment")
        )
    elif column == "M2":
        value = Path("~nosuchuser/e3") if field == "scratch" else "~nosuchuser/e3"
    else:
        raise AssertionError(f"unsupported matrix cell: {field}/{column}")

    if field == "scratch":
        scratch = value
    else:
        _set_matrix_path_value(spec, field, value, column)
    return (
        spec,
        scratch,
        tuple(absent_targets),
        tuple(cycle_links),
        cycle_path,
        tuple(cleanup_targets),
    )


@pytest.mark.parametrize(
    ("field", "column", "verdict"),
    _path_matrix_cases(),
    ids=lambda value: str(value),
)
def test_path_policy_matrix_at_runner_boundary(
    monkeypatch, tmp_path, stable_test_root, field, column, verdict
):
    if verdict == "n/a":
        return

    monkeypatch.chdir(stable_test_root)
    spec, scratch, absent_targets, cycle_links, cycle_path, cleanup_targets = (
        _matrix_root_case(stable_test_root, tmp_path, field, column)
    )
    for target in absent_targets:
        assert target.is_relative_to(stable_test_root) or target in cleanup_targets, (
            field,
            column,
            target,
        )
    if cycle_path is not None:
        _inject_identity_resolve_for(monkeypatch, cycle_path)

    try:
        if verdict == "accept":
            result = _run_dry(tmp_path, spec, scratch)
            assert result.status is Status.PASS, (field, column, result.detail)
            return

        result = _run_refusal_without_side_effects(
            monkeypatch,
            tmp_path,
            spec,
            scratch,
            watched_roots=(stable_test_root,),
        )

        assert result.status is Status.INVALID, (field, column, result.detail)
        assert field in result.detail, (field, column, result.detail)
        for target in absent_targets:
            assert not target.exists(), (field, column, target)
        for link in cycle_links:
            assert link.is_symlink(), (field, column, link)
        if cycle_links:
            assert list(stable_test_root.rglob(".bivharness-mode-probe")) == []
            assert list(stable_test_root.rglob(".bivharness-link-probe")) == []
    finally:
        for target in cleanup_targets:
            shutil.rmtree(target, ignore_errors=True)


@pytest.mark.parametrize("field", ROOT_RELATIVE_FIELDS)
@pytest.mark.parametrize(
    "case",
    (
        "A-abs-safe",
        "B-abs-temp",
        "C-abs-unstable",
        "D-cycle",
        "E-rel-safe",
        "F-dotdot",
        "G-contained-symlink",
        "H-escaping-symlink",
    ),
)
def test_child_path_policy_subsumes_runtime_containment(
    monkeypatch, tmp_path, stable_test_root, field, case
):
    scratch = stable_test_root / "subsumption" / "scratch"
    root = _root_relative_root(scratch, field)
    root.mkdir(parents=True, exist_ok=True)
    if case == "E-rel-safe":
        value = "safe-child"
    else:
        value, _, cycle_links = _root_relative_case(
            stable_test_root, root, field, case, tmp_path
        )
        if cycle_links:
            _inject_identity_resolve_for(monkeypatch, root / value)

    child = root / value
    containment_refuses = not child.resolve().is_relative_to(root.resolve())
    failure = e3._child_failure(field, root, value)

    if containment_refuses:
        assert failure is not None, (field, case, child)
    if case == "E-rel-safe":
        assert failure is None


@pytest.mark.parametrize("field", ("scratch", "live_profile", "live_store_roots"))
def test_resolved_temp_roots_are_refused_without_side_effects(
    monkeypatch, tmp_path, stable_test_root, field
):
    temp_parent = (
        Path("/tmp").resolve()
        / f"bivharness-task7-root-{field}-{os.getpid()}-{tmp_path.name}"
    )
    shutil.rmtree(temp_parent, ignore_errors=True)
    spec = _valid_two_agent_spec()
    scratch = stable_test_root / "scratch"
    if field == "scratch":
        scratch = temp_parent / "scratch"
        target = scratch
    elif field == "live_profile":
        target = temp_parent / "live-profile"
        spec["agents"][0][field] = str(target)
    else:
        target = temp_parent / "live-store"
        spec[field] = [str(target)]

    try:
        result = _run_refusal_without_side_effects(
            monkeypatch,
            tmp_path,
            spec,
            scratch,
            watched_roots=(stable_test_root,),
        )
        assert result.status is Status.INVALID
        assert field in result.detail
        assert not target.exists()
    finally:
        shutil.rmtree(temp_parent, ignore_errors=True)


def test_scratch_rejects_null_without_raising_or_side_effects(
    monkeypatch, tmp_path, stable_test_root
):
    result = _run_refusal_without_side_effects(
        monkeypatch,
        tmp_path,
        _valid_two_agent_spec(),
        None,
        watched_roots=(stable_test_root,),
    )

    assert result.status is Status.INVALID
    assert "scratch" in result.detail


def test_path_field_failures_does_not_recoerce_normalized_scratch(
    monkeypatch, stable_test_root
):
    coerced_labels = []
    real_root_failure = e3._root_failure

    def record_root_coercion(label, value, **kwargs):
        coerced_labels.append(label)
        return real_root_failure(label, value, **kwargs)

    monkeypatch.setattr(e3, "_root_failure", record_root_coercion)

    failures = e3._path_field_failures(
        _valid_two_agent_spec(), stable_test_root / "scratch"
    )

    assert failures == []
    assert "scratch" not in coerced_labels


def _schema_shape_cases():
    """Malformed values for every JSON shape consumed by the E3 runner."""
    scalar = ("none", None), ("scalar", 42), ("container", []), ("bad-element", [None])
    list_of_strings = ("none", None), ("scalar", "value"), ("container", {}), ("bad-element", [None])
    mapping = ("none", None), ("scalar", "value"), ("container", []), ("bad-element", {"KEY": None})
    cases = []

    def add(label, values, mutate):
        cases.extend((f"{label}-{kind}", value, mutate) for kind, value in values)

    add("id", scalar, lambda spec, value: spec.__setitem__("id", value))
    add("checkpoint_prompt", scalar, lambda spec, value: spec.__setitem__("checkpoint_prompt", value))
    add("workspace_name", scalar, lambda spec, value: spec.__setitem__("workspace_name", value))
    add("host2_profile_root", scalar, lambda spec, value: spec.__setitem__("host2_profile_root", value))
    add("resume_probe", scalar, lambda spec, value: spec.__setitem__("resume_probe", value))
    add("seed_turns", list_of_strings, lambda spec, value: spec.__setitem__("seed_turns", value))
    add("live_store_roots", list_of_strings, lambda spec, value: spec.__setitem__("live_store_roots", value))
    add("forbidden_bivpak_state", list_of_strings, lambda spec, value: spec.__setitem__("forbidden_bivpak_state", value))
    add("credential_scan_sentinels", list_of_strings, lambda spec, value: spec.__setitem__("credential_scan_sentinels", value))
    add("agents", list_of_strings, lambda spec, value: spec.__setitem__("agents", value))

    def mutate_agent(field):
        return lambda spec, value: spec["agents"][0].__setitem__(field, value)

    for field in (
        "id", "live_profile", "host2_profile", "ownership_glob", "run_token_prefix",
        "cheapest_model", "resume_shape",
    ):
        add(f"agent-{field}", scalar, mutate_agent(field))
    add("agent-resume_mutation", scalar, lambda spec, value: spec["agents"][1].__setitem__("resume_mutation", value))
    for field in (
        "auth_status", "version_command", "seed_start_command", "seed_retry_resume_command",
        "seed_continue_command", "resume_command", "validated_version_prefixes",
    ):
        add(f"agent-{field}", list_of_strings, mutate_agent(field))
    add("agent-liveness_command", list_of_strings, lambda spec, value: spec["agents"][1].__setitem__("liveness_command", value))
    add("agent-env", mapping, mutate_agent("env"))
    return cases


@pytest.mark.parametrize(("label", "value", "mutate"), _schema_shape_cases())
def test_e3_consumed_schema_is_total_over_arbitrary_json(monkeypatch, tmp_path, label, value, mutate):
    spec = _valid_two_agent_spec()
    mutate(spec, value)
    scratch = tmp_path.resolve() / "scratch"

    assert isinstance(e3._path_field_failures(spec, scratch), list)
    result = _run_refusal_without_side_effects(monkeypatch, tmp_path, spec, scratch)

    assert result.status is Status.INVALID, label
    assert result.detail, label


@pytest.mark.parametrize("label, mutate", [
    ("scratch", lambda spec, stable_root: None),
    ("host2_profile_root", lambda spec, stable_root: spec.__setitem__("host2_profile_root", "path\0segment")),
    ("live_store_roots", lambda spec, stable_root: spec.__setitem__("live_store_roots", [str(stable_root / "path\0segment")])),
    ("live_profile", lambda spec, stable_root: spec["agents"][0].__setitem__("live_profile", str(stable_root / "path\0segment"))),
    ("host2_profile", lambda spec, stable_root: spec["agents"][0].__setitem__("host2_profile", "path\0segment")),
    ("workspace_name", lambda spec, stable_root: spec.__setitem__("workspace_name", "path\0segment")),
    ("forbidden_bivpak_state", lambda spec, stable_root: spec.__setitem__("forbidden_bivpak_state", ["path\0segment"])),
])
def test_e3_path_fields_reject_nul_without_raising(monkeypatch, tmp_path, label, mutate):
    spec = _valid_two_agent_spec()
    stable_root = tmp_path.resolve()
    mutate(spec, stable_root)
    scratch = Path("scratch\0path") if label == "scratch" else stable_root / "scratch"

    assert isinstance(e3._path_field_failures(spec, scratch), list)
    result = _run_refusal_without_side_effects(monkeypatch, tmp_path, spec, scratch)

    assert result.status is Status.INVALID, label


@pytest.mark.parametrize("label, mutate", [
    ("live_store_roots", lambda spec: spec.__setitem__("live_store_roots", ["~nosuchuser/e3"])),
    ("live_profile", lambda spec: spec["agents"][0].__setitem__("live_profile", "~nosuchuser/e3")),
    ("host2_profile", lambda spec: spec["agents"][0].__setitem__("host2_profile", "~nosuchuser/e3")),
    ("workspace_name", lambda spec: spec.__setitem__("workspace_name", "~nosuchuser/e3")),
    ("forbidden_bivpak_state", lambda spec: spec.__setitem__("forbidden_bivpak_state", ["~nosuchuser/e3"])),
])
def test_e3_path_fields_reject_ambiguous_tilde_spellings(monkeypatch, tmp_path, label, mutate):
    spec = _valid_two_agent_spec()
    mutate(spec)

    result = _run_refusal_without_side_effects(
        monkeypatch, tmp_path, spec, tmp_path.resolve() / "scratch"
    )

    assert result.status is Status.INVALID, label
    assert label in result.detail


@pytest.mark.parametrize("spec", [[], "s", 42, None])
def test_e3_consumed_schema_rejects_non_object_top_levels(monkeypatch, tmp_path, spec):
    scratch = tmp_path.resolve() / "scratch"

    assert isinstance(e3._path_field_failures(spec, scratch), list)
    result = _run_refusal_without_side_effects(monkeypatch, tmp_path, spec, scratch)

    assert result.status is Status.INVALID
    assert result.id == "e3-invalid-spec"
    assert result.detail


def test_cli_persists_invalid_e3_report_for_malformed_json(tmp_path):
    scenario = tmp_path / "malformed-e3.json"
    report_path = tmp_path / "report.json"
    scenario.write_text("[]", encoding="utf-8")

    exit_code = cli.main([
        "--biv", str(tmp_path / "biv"),
        "--e3", str(scenario),
        "--dry-run",
        "--report", str(report_path),
    ])

    assert exit_code != 0
    assert report_path.is_file()
    report = json.loads(report_path.read_text(encoding="utf-8"))
    assert report["invalid"] == ["e3-invalid-spec"]
    assert len(report["rows"]) == 1
    row = report["rows"][0]
    assert row["id"] == "e3-invalid-spec"
    assert row["tier"] == "E3"
    assert row["status"] == "invalid"
    assert row["classes"] == []
    assert row["detail"]


def test_scratch_under_a_symlinked_ancestor_is_refused_without_writing(tmp_path):
    shadowed = _symlinked_ancestor(tmp_path)
    real = tmp_path / "real"

    result = _run_dry(tmp_path, _valid_two_agent_spec(), shadowed)

    assert result.status is Status.INVALID
    assert "realpath-stable" in result.detail
    assert "scratch" in result.detail
    assert not shadowed.exists()
    assert list(real.iterdir()) == []


@pytest.mark.parametrize("spelling", ["relative-scratch", ".", "", "~nosuchuser/e3"])
def test_scratch_relative_spellings_are_refused_by_realpath_stability(
    monkeypatch, tmp_path, spelling
):
    stable = tmp_path.resolve()
    monkeypatch.chdir(stable)

    scratch = Path(spelling)
    assert isinstance(e3._path_field_failures(_valid_two_agent_spec(), scratch), list)
    result = _run_refusal_without_side_effects(
        monkeypatch, tmp_path, _valid_two_agent_spec(), scratch
    )

    assert result.status is Status.INVALID
    assert "scratch must be realpath-stable" in result.detail


def test_absolute_realpath_unstable_host2_profile_root_is_refused(tmp_path):
    spec = _valid_two_agent_spec()
    spec["host2_profile_root"] = str(_symlinked_ancestor(tmp_path) / "profiles")
    result = _run_dry(tmp_path, spec, tmp_path.resolve() / "scratch")
    assert result.status is Status.INVALID
    assert "host2_profile_root" in result.detail


def test_realpath_unstable_live_store_root_is_refused(tmp_path):
    spec = _valid_two_agent_spec()
    spec["live_store_roots"] = [str(_symlinked_ancestor(tmp_path) / "store")]
    result = _run_dry(tmp_path, spec, tmp_path.resolve() / "scratch")
    assert result.status is Status.INVALID
    assert "live_store_roots" in result.detail


def test_realpath_unstable_live_profile_is_refused(tmp_path):
    spec = _valid_two_agent_spec()
    spec["agents"][0]["live_profile"] = str(_symlinked_ancestor(tmp_path) / ".codex")
    result = _run_dry(tmp_path, spec, tmp_path.resolve() / "scratch")
    assert result.status is Status.INVALID
    assert "live_profile" in result.detail


@pytest.mark.parametrize("field", ["host2_profile", "workspace_name"])
def test_absolute_value_that_would_escape_its_root_is_refused(tmp_path, field):
    spec = _valid_two_agent_spec()
    if field == "workspace_name":
        spec["workspace_name"] = "/etc"
    else:
        spec["agents"][0]["host2_profile"] = "/etc"
    result = _run_dry(tmp_path, spec, tmp_path.resolve() / "scratch")
    assert result.status is Status.INVALID
    assert field in result.detail


def test_absolute_forbidden_bivpak_state_entry_is_refused(tmp_path):
    spec = _valid_two_agent_spec()
    spec["forbidden_bivpak_state"] = ["/etc"]
    result = _run_dry(tmp_path, spec, tmp_path.resolve() / "scratch")
    assert result.status is Status.INVALID
    assert "forbidden_bivpak_state" in result.detail


def test_realpath_stable_paths_are_accepted(tmp_path, stable_test_root):
    result = _run_dry(
        tmp_path, _valid_two_agent_spec(), stable_test_root / "scratch"
    )
    assert result.status is Status.PASS


def test_temp_rooted_host2_profile_is_refused_before_any_spawn(
    monkeypatch, tmp_path, stable_test_root
):
    calls = []

    def fake_spawn(command, cwd, env):
        calls.append(command)
        return SimpleNamespace(returncode=0, stdout="", stderr="")

    monkeypatch.setattr(e3, "_spawn", fake_spawn)
    spec = _valid_two_agent_spec()
    spec["host2_profile_root"] = "/tmp/bivharness-selftest-host2"

    result = _run_dry(tmp_path, spec, stable_test_root / "scratch")

    assert result.status is Status.INVALID
    assert calls == []


def test_shipped_scenario_has_no_realpath_unstable_or_absolute_paths(repo_root):
    spec = json.loads(
        (repo_root / "harness/scenarios-e3/e3-dual-resume.json").read_text(encoding="utf-8")
    )
    assert e3._path_field_failures(spec, Path.home()) == []


def test_runner_stops_on_an_alias_spelled_seeded_transcript_before_pack(
    monkeypatch, tmp_path, stable_test_root
):
    calls = []

    def fake_spawn(command, cwd, env):
        calls.append(command)
        if "--version" in command:
            version = "claude 2.1.202" if command[0] == "claude" else "codex-cli 0.144.1"
            return SimpleNamespace(returncode=0, stdout=version, stderr="")
        return SimpleNamespace(returncode=0, stdout="", stderr="")

    def fake_seed_agent(
        agent,
        live_profile,
        seed_workspace,
        spec,
        env,
        spawn,
        capture_candidates,
        owned_paths,
    ):
        spelling = (
            b"/var/folders/hq/x/T/ws"
            if agent["id"] == "codex"
            else b"/Users/jack/biv-e3/ws"
        )
        transcript = seed_workspace.parent / f"{agent['id']}-seed.jsonl"
        transcript.write_bytes(b'{"cwd":"' + spelling + b'"}\n')
        owned_paths.append(transcript)
        return transcript

    monkeypatch.setattr(e3, "_spawn", fake_spawn)
    monkeypatch.setattr(e3, "_seed_agent", fake_seed_agent)
    spec_path = tmp_path / "e3.json"
    spec_path.write_text(json.dumps(_valid_two_agent_spec()), encoding="utf-8")

    result = e3.run_e3(spec_path, Path("biv"), stable_test_root / "scratch")

    assert result.status is Status.INVALID
    assert "negative-control" in result.detail
    assert not any(command[:2] == ["biv", "pack"] for command in calls)


def test_negative_control_flags_an_alias_spelled_transcript(tmp_path):
    transcript = tmp_path / "seed.jsonl"
    transcript.write_bytes(b'{"cwd":"/var/folders/hq/x/T/ws"}\n')
    failures = e3._negative_control_failures([transcript])
    assert failures and "negative-control" in failures[0]


def test_negative_control_flags_the_resolved_spelling_too(tmp_path):
    transcript = tmp_path / "seed.jsonl"
    transcript.write_bytes(b'{"cwd":"/private/var/folders/hq/x/T/ws"}\n')
    assert e3._negative_control_failures([transcript])


def test_negative_control_is_silent_on_a_realpath_stable_transcript(tmp_path):
    transcript = tmp_path / "seed.jsonl"
    transcript.write_bytes(b'{"cwd":"/Users/jack/biv-e3/seed-ws"}\n')
    assert e3._negative_control_failures([transcript]) == []


def test_all_host1_auth_and_version_gates_run_before_any_seed(monkeypatch, tmp_path):
    calls = []

    def fake_spawn(command, cwd, env):
        calls.append(command)
        if command == ["second", "auth"]:
            return SimpleNamespace(returncode=1, stdout="", stderr="not logged in")
        return SimpleNamespace(returncode=0, stdout="tool 1.0.0", stderr="")

    agents = []
    for agent_id, command in (("first", "first"), ("second", "second")):
        agents.append({
            "id": agent_id,
            "live_profile": str(Path.home() / f".{agent_id}"),
            "env": {},
            "auth_status": [command, "auth"],
                "version_command": [command, "version"],
                "validated_version_prefixes": ["1.0."],
                "cheapest_model": "cheap",
                "seed_start_command": [command, "seed", "{run_token}", "--model", "cheap"],
                "seed_retry_resume_command": [command, "retry", "{run_token}", "--model", "cheap"],
                "seed_continue_command": [command, "continue", "{run_token}", "--model", "cheap"],
                "ownership_glob": "*.jsonl",
                "run_token_prefix": "token",
                "resume_command": [command, "resume", "--model", "cheap"],
            })
    spec = {
        "id": "auth-order",
        "tier": "E3",
        "checkpoint_count": 1,
        "seed_turns": ["one", "two"],
        "resume_probe": "probe",
        "credential_scan_sentinels": ["synthetic-secret"],
        "agents": agents,
    }
    spec_path = tmp_path / "e3.json"
    spec_path.write_text(json.dumps(spec), encoding="utf-8")
    scratch = Path.home() / ".cache" / f"biv-e3-auth-order-{os.getpid()}"
    shutil.rmtree(scratch, ignore_errors=True)
    monkeypatch.setattr(e3, "_spawn", fake_spawn)
    try:
        result = e3.run_e3(spec_path, Path("biv"), scratch)
    finally:
        shutil.rmtree(scratch, ignore_errors=True)

    assert result.status is Status.INVALID
    assert calls == [["first", "auth"], ["first", "version"], ["second", "auth"]]


def test_e3_spec_validation_rejects_dead_or_wrong_resume_shape():
    base = {
        "id": "agent",
        "live_profile": "~/.agent",
        "auth_status": ["agent", "auth"],
        "version_command": ["agent", "version"],
        "validated_version_prefixes": ["1.0."],
        "seed_start_command": ["agent", "seed"],
        "seed_continue_command": ["agent", "continue"],
        "ownership_glob": "*.jsonl",
        "run_token": "token",
        "resume_command": ["agent", "resume"],
    }
    spec = {
        "tier": "E3",
        "checkpoint_count": 1,
        "seed_turns": ["one", "two"],
        "resume_probe": "probe",
        "agents": [
            {**base, "id": "claude-code", "resume_mutation": "forks-new-file"},
            {**base, "id": "codex", "resume_shape": CODEX_RESUME_SHAPE},
        ],
    }
    assert "Claude resume mutation must match the pinned shape" in e3._validate_spec(spec)


def test_checkpoint_cardinality_is_exactly_one():
    assert_one_checkpoint(["oauth"])
    with pytest.raises(ValueError, match="exactly one"):
        assert_one_checkpoint([])
    with pytest.raises(ValueError, match="exactly one"):
        assert_one_checkpoint(["oauth", "oauth-again"])


@pytest.mark.parametrize("name", CREDENTIAL_ENV_NAMES)
def test_credential_inventory_rejects_each_named_variable(name):
    assert rejected_credential_names({name: "secret"}) == [name]


def test_profile_root_guards_tmp_mnt_and_live_store(tmp_path):
    live = tmp_path / "live-store"
    live.mkdir()

    assert "profile-root-tmp" in profile_root_failures(Path("/tmp/host2"), [])
    assert "profile-root-mnt" in profile_root_failures(Path("/mnt/c/host2"), [])
    assert "profile-root-live-store" in profile_root_failures(live / "nested", [live])


def test_profile_root_accepts_isolated_native_path(tmp_path):
    root = Path.home() / ".cache" / "bivharness-e3-test-profile"
    live = tmp_path / "live-store"

    assert profile_root_failures(root, [live]) == []
