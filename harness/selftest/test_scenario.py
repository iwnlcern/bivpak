import json
from pathlib import Path

from bivharness.report import Status
from bivharness.scenario import run_scenario


STUB = Path(__file__).with_name("stub_biv.py")


def write_schema_root(root: Path, *, envelope_version_const=1):
    root.mkdir(parents=True, exist_ok=True)
    (root / "biv-json-envelope.v1.schema.json").write_text(
        json.dumps(
            {
                "$schema": "https://json-schema.org/draft/2020-12/schema",
                "type": "object",
                "required": [
                    "envelope_version",
                    "app_version",
                    "ok",
                    "verb",
                    "exit_code",
                    "warnings",
                    "advisories",
                    "result",
                    "error",
                ],
                "properties": {
                    "envelope_version": {"const": envelope_version_const},
                    "app_version": {"type": "string"},
                    "ok": {"type": "boolean"},
                    "verb": {"type": "string"},
                    "exit_code": {"type": "integer"},
                    "warnings": {"type": "array"},
                    "advisories": {"type": "array"},
                    "result": {"type": ["object", "null"]},
                    "error": {"type": ["object", "null"]},
                },
            }
        ),
        encoding="utf-8",
    )
    (root / "biv-exit-map.v1.json").write_text(
        json.dumps(
            {
                "version": 1,
                "rows": [
                    {"kind": "FormatVersionUnsupported", "class": "refusal", "exit": 3},
                    {"kind": "InternalError", "class": "mid-fail", "exit": 4},
                ],
            }
        ),
        encoding="utf-8",
    )
    return root


def use_schema_root(monkeypatch, tmp_path, *, envelope_version_const=1):
    schema_root = write_schema_root(tmp_path / "schemas", envelope_version_const=envelope_version_const)
    monkeypatch.setenv("BIVHARNESS_SCHEMA_ROOT", str(schema_root))
    return schema_root


def _write_spec(path: Path, data: dict):
    path.write_text(json.dumps(data), encoding="utf-8")
    return path


def _basic_spec(tmp_path, **overrides):
    spec = {
        "id": "basic",
        "tier": "E2",
        "classes": ["A", "B", "C", "E", "K"],
        "fixture": {"entries": [{"type": "file", "path": "a.txt", "text": "alpha", "mode": "0644"}]},
        "steps": [{"op": "pack"}, {"op": "open"}],
        "expect": {
            "tree": True,
            "members_present": ["manifest.json", "checksums.json", "payload/a.txt"],
            "members_absent": [],
            "manifest_variant": "builtin",
        },
        "held": [],
    }
    spec.update(overrides)
    return _write_spec(tmp_path / f"{spec['id']}.json", spec)


def test_stub_ok_scenario_passes_all_bound_classes(monkeypatch, tmp_path):
    use_schema_root(monkeypatch, tmp_path)
    monkeypatch.setenv("STUB_BIV_MODE", "ok")
    result = run_scenario(_basic_spec(tmp_path), STUB, tmp_path / "scratch")

    assert result.status is Status.PASS
    assert result.classes == ["A", "B", "C", "E", "K"]


def test_result_classes_record_exercised_checks_not_spec_echo(monkeypatch, tmp_path):
    use_schema_root(monkeypatch, tmp_path)
    monkeypatch.setenv("STUB_BIV_MODE", "ok")
    spec = _basic_spec(tmp_path, classes=["A", "B", "C", "E", "K", "UNEXERCISED"])

    result = run_scenario(spec, STUB, tmp_path / "scratch")

    assert result.status is Status.PASS
    assert result.classes == ["A", "B", "C", "E", "K"]


def test_stub_badtree_reports_class_c_failure(monkeypatch, tmp_path):
    use_schema_root(monkeypatch, tmp_path)
    monkeypatch.setenv("STUB_BIV_MODE", "badtree")
    result = run_scenario(_basic_spec(tmp_path), STUB, tmp_path / "scratch")

    assert result.status is Status.FAIL
    assert "C:" in result.detail


def test_refusal_scenario_passes_refusal_invariants_with_held_asserts(monkeypatch, tmp_path):
    use_schema_root(monkeypatch, tmp_path)
    monkeypatch.setenv("STUB_BIV_MODE", "refuse")
    spec = _basic_spec(
        tmp_path,
        id="fv99",
        steps=[{"op": "pack"}, {"op": "synthesize-fv99"}, {"op": "open"}],
        expect={"refusal": True},
        held=["exit==3", "json.error.kind"],
    )

    result = run_scenario(spec, STUB, tmp_path / "scratch")

    assert result.status is Status.PASS
    assert result.held_asserts == ["exit==3", "json.error.kind"]


def test_shell_spec_is_pending_and_does_not_invoke_stub(tmp_path):
    spec = _basic_spec(tmp_path, status="xfail-pending", id="shell")

    result = run_scenario(spec, tmp_path / "missing-stub", tmp_path / "scratch")

    assert result.status is Status.XFAIL_PENDING


def test_probe_failure_returns_invalid_before_execution(monkeypatch, tmp_path):
    use_schema_root(monkeypatch, tmp_path)
    monkeypatch.setenv("STUB_BIV_MODE", "ok")
    result = run_scenario(_basic_spec(tmp_path), STUB, Path("/mnt/c/bivharness-invalid"))

    assert result.status is Status.INVALID
    assert "drvfs-guard" in result.detail


def test_missing_schema_artifacts_invalidates_runnable_scenario(monkeypatch, tmp_path):
    missing_schema_root = tmp_path / "missing-schemas"
    missing_schema_root.mkdir()
    monkeypatch.setenv("BIVHARNESS_SCHEMA_ROOT", str(missing_schema_root))
    monkeypatch.setenv("STUB_BIV_MODE", "ok")

    result = run_scenario(_basic_spec(tmp_path), STUB, tmp_path / "scratch")

    assert result.status is Status.INVALID
    assert "missing schema artifact" in result.detail


def test_open_step_uses_default_cwd_landing_not_dest(monkeypatch, tmp_path):
    use_schema_root(monkeypatch, tmp_path)
    monkeypatch.setenv("STUB_BIV_MODE", "reject-dest")

    result = run_scenario(_basic_spec(tmp_path), STUB, tmp_path / "scratch")

    assert result.status is Status.PASS, result.detail


def test_malformed_stdout_is_invalid(monkeypatch, tmp_path):
    use_schema_root(monkeypatch, tmp_path)
    monkeypatch.setenv("STUB_BIV_MODE", "malformed-stdout")

    result = run_scenario(_basic_spec(tmp_path), STUB, tmp_path / "scratch")

    assert result.status is Status.INVALID
    assert "stdout JSON" in result.detail


def test_noisy_stdout_is_invalid(monkeypatch, tmp_path):
    use_schema_root(monkeypatch, tmp_path)
    monkeypatch.setenv("STUB_BIV_MODE", "noisy-stdout")

    result = run_scenario(_basic_spec(tmp_path), STUB, tmp_path / "scratch")

    assert result.status is Status.INVALID
    assert "exactly one JSON document" in result.detail


def test_pack_failure_is_deterministic_fail_without_member_assert_crash(monkeypatch, tmp_path):
    use_schema_root(monkeypatch, tmp_path)
    monkeypatch.setenv("STUB_BIV_MODE", "pack-fail")

    result = run_scenario(_basic_spec(tmp_path), STUB, tmp_path / "scratch")

    assert result.status is Status.FAIL
    assert "pack exited 4" in result.detail


def test_manifest_sha_mismatch_fails_class_e(monkeypatch, tmp_path):
    use_schema_root(monkeypatch, tmp_path)
    monkeypatch.setenv("STUB_BIV_MODE", "bad-manifest")

    result = run_scenario(_basic_spec(tmp_path), STUB, tmp_path / "scratch")

    assert result.status is Status.FAIL
    assert "bivignore.sha256" in result.detail


def test_payload_checksum_mismatch_fails_class_e(monkeypatch, tmp_path):
    use_schema_root(monkeypatch, tmp_path)
    monkeypatch.setenv("STUB_BIV_MODE", "bad-checksums")

    result = run_scenario(_basic_spec(tmp_path), STUB, tmp_path / "scratch")

    assert result.status is Status.FAIL
    assert "checksum mismatch" in result.detail


def test_leaked_forbidden_member_fails_class_k(monkeypatch, tmp_path):
    use_schema_root(monkeypatch, tmp_path)
    monkeypatch.setenv("STUB_BIV_MODE", "leak-member")
    spec = _basic_spec(
        tmp_path,
        fixture={
            "entries": [
                {"type": "file", "path": ".bivignore", "text": "secret.log\n"},
                {"type": "file", "path": "keep.txt", "text": "keep"},
                {"type": "file", "path": "secret.log", "text": "secret"},
            ]
        },
        expect={
            "tree": True,
            "members_present": ["manifest.json", "checksums.json", "payload/keep.txt"],
            "members_absent": ["payload/secret.log"],
            "manifest_variant": "file",
        },
    )

    result = run_scenario(spec, STUB, tmp_path / "scratch")

    assert result.status is Status.FAIL
    assert "expected absent" in result.detail
