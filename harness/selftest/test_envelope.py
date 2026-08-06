import hashlib
import json
from pathlib import Path

from bivharness.report import Status
from bivharness.scenario import run_scenario

from test_scenario import use_schema_root
from test_specs import SCENARIOS, STUB


REPO_ROOT = Path(__file__).resolve().parents[2]
CURRENT_LOCKED_SCHEMA_BLOBS = {
    "schemas/biv-json-envelope.v1.schema.json": "561dccf0dbd8e374b975ba19e2dbd8ddad553e81",
    "schemas/biv-exit-map.v1.json": "bc86a434eaf848b96d1273326a77b8adf49830ce",
}


def _git_blob_id(data: bytes) -> str:
    return hashlib.sha1(b"blob " + str(len(data)).encode("ascii") + b"\0" + data).hexdigest()


def test_vendored_schema_artifacts_match_current_locked_bytes():
    actual = {
        path: _git_blob_id((REPO_ROOT / path).read_bytes())
        for path in CURRENT_LOCKED_SCHEMA_BLOBS
    }

    assert actual == CURRENT_LOCKED_SCHEMA_BLOBS


def test_fv99_spec_asserts_reconciled_exit_and_error_kind(monkeypatch, tmp_path):
    use_schema_root(monkeypatch, tmp_path)
    monkeypatch.setenv("STUB_BIV_MODE", "ok")

    result = run_scenario(SCENARIOS / "format-version-99.json", STUB, tmp_path / "scratch")

    assert result.status is Status.PASS, result.detail
    assert result.held_asserts == []


def test_envelope_schema_validation_uses_configured_schema_root(monkeypatch, tmp_path):
    use_schema_root(monkeypatch, tmp_path, envelope_version_const=2)
    monkeypatch.setenv("STUB_BIV_MODE", "ok")

    result = run_scenario(SCENARIOS / "plain-dir-v2.json", STUB, tmp_path / "scratch")

    assert result.status is Status.INVALID
    assert "envelope schema" in result.detail
