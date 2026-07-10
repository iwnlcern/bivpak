from copy import deepcopy

from bivharness.manifest import validate_manifest


def _golden_manifest(variant="builtin"):
    builtin_id = "builtin-v1" if variant == "builtin" else None
    source = "builtin" if variant == "builtin" else "file"
    return {
        "format_version": 1,
        "required_capabilities": [],
        "image_id": "00000000-0000-4000-8000-000000000000",
        "app_version": "0.1.0",
        "created_at": "2026-07-05T00:00:00Z",
        "source_path": "/tmp/plain",
        "source_path_flavor": "posix",
        "bivignore": {
            "source": source,
            "builtin_id": builtin_id,
            "sha256": "abc123",
        },
        "repos": [],
        "agent_sessions": [],
    }


def _agent_session_entry():
    return {
        "agent": "codex",
        "agent_version_at_pack": "0.142.5",
        "relpath_key": ".",
        "original_path": "/mnt/c/Users/x/proj",
        "normalized_path_key": "/mnt/c/users/x/proj",
        "normalization_scheme": "codex-cwd/v1",
        "path_flavor": "wsl",
        "provenance": {
            "store_root": "/home/u/.codex",
            "locator": "sessions_root",
            "discovery_tier": "default",
            "archived": False,
        },
        "original_session_ids": {"primary": "019f-aaaa"},
        "children": [
            {"original_id": "019f-bbbb", "artifacts": ["agents/codex/019f-bbbb.jsonl"]}
        ],
        "artifacts": ["agents/codex/019f-aaaa.jsonl"],
        "live_at_pack": False,
        "imported_at": "2026-07-07T00:00:00Z",
        "entry_schema": 1,
    }


def test_golden_plain_dir_manifests_validate_for_both_variants():
    assert validate_manifest(_golden_manifest("file"), "file") == []
    assert validate_manifest(_golden_manifest("builtin"), "builtin") == []


def test_unknown_top_level_field_is_ignored():
    manifest = _golden_manifest()
    manifest["future_field"] = {"ok": True}

    assert validate_manifest(manifest, "builtin") == []


def test_future_format_version_fails():
    manifest = _golden_manifest()
    manifest["format_version"] = 2

    assert any("format_version" in item for item in validate_manifest(manifest, "builtin"))


def test_manifest_with_agent_sessions_entry_validates():
    manifest = _golden_manifest()
    manifest["agent_sessions"] = [_agent_session_entry()]

    assert validate_manifest(manifest, "builtin") == []


def test_agent_sessions_entry_missing_required_field_fails():
    manifest = _golden_manifest()
    entry = _agent_session_entry()
    del entry["normalization_scheme"]
    manifest["agent_sessions"] = [entry]

    assert any(
        "normalization_scheme" in item for item in validate_manifest(manifest, "builtin")
    )


def test_agent_session_locked_mechanical_rules_are_enforced():
    cases = []

    invalid_agent = _agent_session_entry()
    invalid_agent["agent"] = "../evil"
    cases.append(invalid_agent)

    escaped_artifact = _agent_session_entry()
    escaped_artifact["artifacts"] = ["agents/codex/../../auth.json"]
    cases.append(escaped_artifact)

    empty_parent = _agent_session_entry()
    empty_parent["artifacts"] = []
    cases.append(empty_parent)

    dangling_without_parent = _agent_session_entry()
    dangling_without_parent["original_session_ids"]["parent_in_image"] = False
    cases.append(dangling_without_parent)

    dangling_without_marker = _agent_session_entry()
    dangling_without_marker["original_session_ids"]["parent"] = "missing"
    cases.append(dangling_without_marker)

    for entry in cases:
        manifest = _golden_manifest()
        manifest["agent_sessions"] = [entry]
        assert validate_manifest(manifest, "builtin")


def test_agent_session_uniqueness_and_nullable_parent():
    manifest = _golden_manifest()
    first = _agent_session_entry()
    second = deepcopy(first)
    second["artifacts"] = ["agents/codex/other.jsonl"]
    manifest["agent_sessions"] = [first, second]
    assert any("unique" in item for item in validate_manifest(manifest, "builtin"))

    nullable = _golden_manifest()
    entry = _agent_session_entry()
    entry["original_session_ids"]["parent"] = None
    nullable["agent_sessions"] = [entry]
    assert validate_manifest(nullable, "builtin") == []


def test_future_entry_schema_reaches_per_entry_skip_with_only_dispatch_fields():
    manifest = _golden_manifest()
    manifest["agent_sessions"] = [{"agent": "future-tool", "entry_schema": 99}]

    assert validate_manifest(manifest, "builtin") == []


def test_agent_memory_top_level_is_ignored_not_rejected():
    # seam lock s3-seam-lock-20260707 Part 1 rule 5: unknown top-level field, ignored
    for field in ("agent_memory", "memory"):
        manifest = _golden_manifest()
        manifest[field] = []
        assert validate_manifest(manifest, "builtin") == []


def test_wrong_builtin_id_fails_variant_check():
    manifest = deepcopy(_golden_manifest("builtin"))
    manifest["bivignore"]["builtin_id"] = "other"

    assert any("builtin_id" in item for item in validate_manifest(manifest, "builtin"))
