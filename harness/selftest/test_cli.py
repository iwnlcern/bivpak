import json
import os
import subprocess
import sys
from pathlib import Path

from bivharness import cli
from bivharness.report import Report, ScenarioResult, Status
from bivharness.report import serialize_report as shared_serialize_report
from test_scenario import use_schema_root


STUB = Path(__file__).with_name("stub_biv.py")


def test_cli_writes_exact_shared_serializer_bytes_and_reuses_results_for_exit(
    monkeypatch, tmp_path
):
    scenarios = tmp_path / "scenarios"
    scenarios.mkdir()
    (scenarios / "one.json").write_text("{}", encoding="utf-8")
    report = tmp_path / "report.json"
    results = [
        ScenarioResult(
            id="owner",
            tier="E2",
            status=Status.PASS,
            classes=["A"],
        )
    ]
    serializer_inputs = []

    monkeypatch.setattr(cli, "run_scenario", lambda *args: results[0])

    def spy_serializer(actual_results):
        serializer_inputs.append(actual_results)
        return shared_serialize_report(actual_results)

    class ExitReport:
        def __init__(self, actual_results):
            assert actual_results is serializer_inputs[0]

        def exit_code(self):
            return 7

    monkeypatch.setattr(cli, "serialize_report", spy_serializer)
    monkeypatch.setattr(cli, "Report", ExitReport)

    assert cli.main([
        "--biv", str(STUB),
        "--scenarios", str(scenarios),
        "--report", str(report),
    ]) == 7
    assert serializer_inputs == [results]
    assert report.read_bytes() == shared_serialize_report(results).encode("utf-8")


def test_cli_writes_report_and_exits_zero_for_stub_ok(monkeypatch, tmp_path):
    use_schema_root(monkeypatch, tmp_path)
    monkeypatch.setenv("STUB_BIV_MODE", "ok")
    scenarios = tmp_path / "scenarios"
    scenarios.mkdir()
    (scenarios / "plain.json").write_text(
        json.dumps(
            {
                "id": "plain",
                "tier": "E2",
                "classes": ["A", "B", "C", "E", "K"],
                "fixture": {"entries": [{"type": "file", "path": "a.txt", "text": "alpha"}]},
                "steps": [{"op": "pack"}, {"op": "open"}],
                "expect": {
                    "tree": True,
                    "members_present": ["manifest.json", "checksums.json", "payload/a.txt"],
                    "members_absent": [],
                    "manifest_variant": "builtin",
                },
            }
        ),
        encoding="utf-8",
    )
    report = tmp_path / "report.json"

    run = subprocess.run(
        [
            sys.executable,
            "-m",
            "bivharness",
            "--biv",
            str(STUB),
            "--scenarios",
            str(scenarios),
            "--report",
            str(report),
        ],
        check=False,
        cwd=Path(__file__).resolve().parents[1],
        text=True,
        capture_output=True,
    )

    assert run.returncode == 0
    data = json.loads(report.read_text(encoding="utf-8"))
    assert data["runnable_passed"] == ["plain"]


def test_cli_resolves_relative_paths_for_scratch_execution(monkeypatch, tmp_path):
    use_schema_root(monkeypatch, tmp_path)
    monkeypatch.setenv("STUB_BIV_MODE", "ok")
    harness = Path(__file__).resolve().parents[1]
    scenarios = tmp_path / "scenarios"
    scenarios.mkdir()
    (scenarios / "plain.json").write_text(
        json.dumps(
            {
                "id": "plain",
                "tier": "E2",
                "classes": ["A", "B", "C", "E", "K"],
                "fixture": {"entries": [{"type": "file", "path": "a.txt", "text": "alpha"}]},
                "steps": [{"op": "pack"}, {"op": "open"}],
                "expect": {
                    "tree": True,
                    "members_present": ["manifest.json", "checksums.json", "payload/a.txt"],
                    "members_absent": [],
                    "manifest_variant": "builtin",
                },
            }
        ),
        encoding="utf-8",
    )
    report = tmp_path / "nested" / "report.json"

    run = subprocess.run(
        [
            sys.executable,
            "-m",
            "bivharness",
            "--biv",
            os.path.relpath(STUB, harness),
            "--scenarios",
            os.path.relpath(scenarios, harness),
            "--report",
            os.path.relpath(report, harness),
        ],
        check=False,
        cwd=harness,
        text=True,
        capture_output=True,
    )

    assert run.returncode == 0
    data = json.loads(report.read_text(encoding="utf-8"))
    assert data["runnable_passed"] == ["plain"]


def test_cli_fails_closed_when_schema_artifacts_are_missing(monkeypatch, tmp_path):
    missing_schema_root = tmp_path / "missing-schemas"
    missing_schema_root.mkdir()
    monkeypatch.setenv("BIVHARNESS_SCHEMA_ROOT", str(missing_schema_root))
    scenarios = tmp_path / "scenarios"
    scenarios.mkdir()
    (scenarios / "plain.json").write_text(
        json.dumps(
            {
                "id": "plain",
                "tier": "E2",
                "classes": ["A", "B", "C", "E", "K"],
                "fixture": {"entries": [{"type": "file", "path": "a.txt", "text": "alpha"}]},
                "steps": [{"op": "pack"}, {"op": "open"}],
                "expect": {"tree": True, "manifest_variant": "builtin"},
            }
        ),
        encoding="utf-8",
    )
    report = tmp_path / "report.json"

    run = subprocess.run(
        [
            sys.executable,
            "-m",
            "bivharness",
            "--biv",
            str(STUB),
            "--scenarios",
            str(scenarios),
            "--report",
            str(report),
        ],
        check=False,
        cwd=Path(__file__).resolve().parents[1],
        text=True,
        capture_output=True,
    )

    assert run.returncode == 1
    data = json.loads(report.read_text(encoding="utf-8"))
    assert data["invalid"] == ["plain"]
