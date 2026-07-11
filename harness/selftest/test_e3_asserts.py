import json
import os
import shutil
from pathlib import Path
from types import SimpleNamespace

import pytest

from bivharness import e3
from bivharness.e3 import (
    CLAUDE_RESUME_MUTATION,
    CODEX_RESUME_SHAPE,
    CREDENTIAL_ENV_NAMES,
    assert_resume_containment,
    assert_one_checkpoint,
    class_j_failures,
    ordered_turns_present,
    rejected_credential_names,
    scan_secret_values,
    select_owned_rollout,
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
    foreign = tmp_path / "rollout-2026-07-11-foreign-id.jsonl"
    owned.write_text('{"run_token":"mine"}\n', encoding="utf-8")
    foreign.write_text('{"run_token":"other"}\n', encoding="utf-8")

    assert select_owned_rollout(tmp_path, "owned-id", "mine") == owned

    duplicate = tmp_path / "nested" / owned.name
    duplicate.parent.mkdir()
    duplicate.write_text('{"run_token":"mine"}\n', encoding="utf-8")
    with pytest.raises(ValueError, match="exactly one"):
        select_owned_rollout(tmp_path, "owned-id", "mine")


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
                "seed_start_command": [command, "seed"],
                "seed_continue_command": [command, "continue"],
                "ownership_glob": "*.jsonl",
                "run_token": "token",
                "resume_command": [command, "resume"],
            })
    spec = {
        "id": "auth-order",
        "tier": "E3",
        "checkpoint_count": 1,
        "seed_turns": ["one", "two"],
        "resume_probe": "probe",
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
