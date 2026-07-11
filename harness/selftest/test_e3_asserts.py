import os
from pathlib import Path

import pytest

from bivharness.e3 import (
    CREDENTIAL_ENV_NAMES,
    assert_one_checkpoint,
    ordered_turns_present,
    rejected_credential_names,
    select_owned_rollout,
)
from bivharness.precheck import profile_root_failures


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
