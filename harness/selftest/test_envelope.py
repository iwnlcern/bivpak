import hashlib
import json
from pathlib import Path

from bivharness.report import Status
from bivharness.scenario import run_scenario

from test_scenario import use_schema_root
from test_specs import SCENARIOS, STUB


REPO_ROOT = Path(__file__).resolve().parents[2]
CURRENT_LOCKED_SCHEMA_BLOBS = {
    "schemas/biv-json-envelope.v1.schema.json": "fe42d6fb696850d7bbb8d73385e2b1b604b6bd59",
    "schemas/biv-exit-map.v1.json": "31fb8ef8966f2de44b9de268265a5c7e013e6c5d",
}


def _git_blob_id(data: bytes) -> str:
    return hashlib.sha1(b"blob " + str(len(data)).encode("ascii") + b"\0" + data).hexdigest()


def test_vendored_schema_artifacts_match_current_locked_bytes():
    actual = {
        path: _git_blob_id((REPO_ROOT / path).read_bytes())
        for path in CURRENT_LOCKED_SCHEMA_BLOBS
    }

    assert actual == CURRENT_LOCKED_SCHEMA_BLOBS


def _schema():
    return json.loads((REPO_ROOT / "schemas/biv-json-envelope.v1.schema.json").read_text())


def test_a6_17_i_open_result_declares_url_divergence_refusals():
    result_obj = next(b for b in _schema()["properties"]["result"]["anyOf"]
                      if isinstance(b, dict) and b.get("type") == "object")
    prop = result_obj["properties"]["url_divergence_refusals"]
    assert prop["minItems"] == 1
    items = prop["items"]
    assert sorted(items["required"]) == ["effective", "kind", "op", "relpath", "repo_id", "requested"]
    assert items["properties"]["kind"] == {"const": "UrlDivergenceEntryRefused"}
    for field in ("repo_id", "relpath", "requested", "effective", "op"):
        assert items["properties"][field] == {"type": "string"}


def test_a6_17_ii_error_facts_declare_the_three_hook_facts():
    error_obj = next(b for b in _schema()["properties"]["error"]["anyOf"]
                     if isinstance(b, dict) and b.get("type") == "object")
    facts = error_obj["properties"]["facts"]["properties"]
    for field in ("requested", "effective", "op"):
        assert facts[field] == {"type": "string"}


def test_a6_17_iii_accepted_advisory_branch_declares_complete_structure():
    branches = _schema()["properties"]["advisories"]["items"]["oneOf"]
    branch = next(b for b in branches
                  if b.get("properties", {}).get("kind") == {"const": "url-divergence-accepted"})
    assert sorted(branch["required"]) == ["entries", "kind"]
    entries = branch["properties"]["entries"]
    assert entries["minItems"] == 1
    assert sorted(entries["items"]["required"]) == ["effective", "op", "repo", "requested"]
    for field in ("requested", "effective", "op", "repo"):
        assert entries["items"]["properties"][field] == {"type": "string"}


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
