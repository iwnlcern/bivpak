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


def test_agent_memory_fields_fail_m17():
    for field in ("agent_memory", "memory"):
        manifest = _golden_manifest()
        manifest[field] = []
        assert any(field in item for item in validate_manifest(manifest, "builtin"))


def test_wrong_builtin_id_fails_variant_check():
    manifest = deepcopy(_golden_manifest("builtin"))
    manifest["bivignore"]["builtin_id"] = "other"

    assert any("builtin_id" in item for item in validate_manifest(manifest, "builtin"))
