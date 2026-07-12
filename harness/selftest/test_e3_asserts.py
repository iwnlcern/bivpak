import io
import json
import os
import shutil
import tarfile
from pathlib import Path
from types import SimpleNamespace

import pytest
import zstandard

from bivharness import e3
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
            "validated_version_prefix": "2.1.",
            "liveness_command": ["claude", "--model", "haiku", "-p", "Reply with one token: OK"],
        },
        {
            "id": "codex",
            "host2_profile": "codex",
            "env": {"CODEX_HOME": "{profile}"},
            "auth_status": ["codex", "login", "status"],
            "version_command": ["codex", "--version"],
            "validated_version_prefix": "0.142.",
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
    transcript = root / f"{session_id}.jsonl"
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


@pytest.mark.parametrize("first_shape", ["wrote-owned", "wrote-nothing"])
def test_first_seed_retry_resumes_owned_or_restarts_empty_window(tmp_path, first_shape):
    root = tmp_path / "store"
    root.mkdir()
    workspace = tmp_path / "workspace"
    workspace.mkdir()
    session_id = "aaaaaaaa-1111-4111-8111-111111111111"
    transcript = root / f"{session_id}.jsonl"
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
    first = root / "aaaaaaaa-1111-4111-8111-111111111111.jsonl"
    second = root / "bbbbbbbb-1111-4111-8111-111111111111.jsonl"
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
    transcript = root / f"{session_id}.jsonl"
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
    transcript = root / f"{session_id}.jsonl"
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


def test_codex_resume_requires_one_same_id_rollout(tmp_path):
    profile = tmp_path / "codex"
    session_id = "019faaaa-bbbb-7ccc-8ddd-eeeeeeee0001"
    first = profile / f"rollout-a-{session_id}.jsonl"
    first.parent.mkdir(parents=True)
    first.write_text("seed-one\nseed-two\nresume-probe\n", encoding="utf-8")

    assert_resume_containment(
        "codex", profile, tmp_path / "restored", session_id,
        ["seed-one", "seed-two", "resume-probe"], "resume-probe", CODEX_RESUME_SHAPE,
    )

    second = profile / "nested" / f"rollout-b-{session_id}.jsonl"
    second.parent.mkdir()
    second.write_text("resume-probe\n", encoding="utf-8")
    with pytest.raises(ValueError, match="exactly one"):
        assert_resume_containment(
            "codex", profile, tmp_path / "restored", session_id,
            ["seed-one", "seed-two", "resume-probe"], "resume-probe", CODEX_RESUME_SHAPE,
        )


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
    assert version_in_validated_range("claude 2.1.202", "2.1.")
    assert not version_in_validated_range("claude 2.2.0", "2.1.")
    assert not version_in_validated_range("claude 12.1.202", "2.1.")


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
                "validated_version_prefix": "1.0.",
                "cheapest_model": "cheap",
                "seed_start_command": [command, "seed", "--model", "cheap"],
                "seed_retry_resume_command": [command, "retry", "--model", "cheap"],
                "seed_continue_command": [command, "continue", "--model", "cheap"],
                "ownership_glob": "*.jsonl",
                "run_token": "token",
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
        "validated_version_prefix": "1.0.",
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
