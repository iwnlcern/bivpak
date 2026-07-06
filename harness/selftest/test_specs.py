import json
from pathlib import Path

from bivharness.report import Status
from bivharness.scenario import run_scenario

from test_scenario import use_schema_root


HARNESS = Path(__file__).resolve().parents[1]
SCENARIOS = HARNESS / "scenarios"
STUB = Path(__file__).with_name("stub_biv.py")


def _load(name):
    return json.loads((SCENARIOS / name).read_text(encoding="utf-8"))


def test_all_required_scenario_specs_exist_and_have_minimum_grammar():
    expected = {
        "plain-dir-v1.json",
        "plain-dir-v2.json",
        "format-version-99.json",
        "shells/d-git-restore.json",
        "shells/f-adapters-identity.json",
        "shells/g-consent-dna.json",
        "shells/h-error-matrix.json",
    }
    actual = {path.relative_to(SCENARIOS).as_posix() for path in SCENARIOS.rglob("*.json")}
    assert expected <= actual

    for rel in expected:
        spec = _load(rel)
        assert spec["id"]
        assert spec["tier"]
        assert isinstance(spec["classes"], list)
        assert isinstance(spec.get("dor_pointers", []), list)
        if spec.get("status") == "xfail-pending":
            assert spec["steps"] == []
        else:
            assert spec["fixture"]["entries"]
            assert spec["steps"]
            assert "expect" in spec


def test_shell_specs_report_xfail_pending_without_execution(tmp_path):
    for rel in (
        "shells/d-git-restore.json",
        "shells/f-adapters-identity.json",
        "shells/g-consent-dna.json",
        "shells/h-error-matrix.json",
    ):
        result = run_scenario(SCENARIOS / rel, tmp_path / "missing", tmp_path / rel)
        assert result.status is Status.XFAIL_PENDING


def test_v1_and_v2_specs_run_green_against_stub_ok(monkeypatch, tmp_path):
    use_schema_root(monkeypatch, tmp_path)
    monkeypatch.setenv("STUB_BIV_MODE", "ok")
    for rel in ("plain-dir-v1.json", "plain-dir-v2.json"):
        result = run_scenario(SCENARIOS / rel, STUB, tmp_path / rel)
        assert result.status is Status.PASS, result.detail
