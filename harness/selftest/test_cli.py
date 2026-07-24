import json
import os
import subprocess
import sys
from pathlib import Path

from bivharness import cli
from bivharness import e3
from bivharness.report import Report, ScenarioResult, Status
from bivharness.report import serialize_report as shared_serialize_report
from test_scenario import use_schema_root


STUB = Path(__file__).with_name("stub_biv.py")


def test_cli_atomically_replaces_stale_pass_with_terminal_report_refusal(
    monkeypatch, tmp_path
):
    scenario = tmp_path / "e3.json"
    scenario.write_text("{}", encoding="utf-8")
    report = tmp_path / "report.json"
    report.write_text(
        shared_serialize_report(
            [
                ScenarioResult(
                    "stale-pass",
                    "E3",
                    Status.PASS,
                    ["RAW_CAPTURED_PRIOR"],
                    detail="PASS",
                )
            ]
        ),
        encoding="utf-8",
    )
    monkeypatch.setattr(
        cli,
        "run_e3",
        lambda *_args, **_kwargs: e3._nonwritable_sanitized_report_result(),
    )
    replacements = []
    real_replace = os.replace

    def recording_replace(source, destination):
        replacements.append((Path(source), Path(destination)))
        return real_replace(source, destination)

    monkeypatch.setattr(os, "replace", recording_replace)
    exit_code = cli.main(
        [
            "--biv",
            str(STUB),
            "--e3",
            str(scenario),
            "--report",
            str(report),
        ]
    )

    assert exit_code == 1
    report_text = report.read_text(encoding="utf-8")
    data = json.loads(report_text)
    expected = ScenarioResult(
        id="e3-report-refused",
        tier="E3",
        status=Status.INVALID,
        classes=[],
        held_asserts=[],
        detail="report refused: result could not be sanitized",
        warnings=[],
    )
    assert report.read_bytes() == shared_serialize_report([expected]).encode("utf-8")
    assert data["invalid"] == ["e3-report-refused"]
    assert data["runnable_passed"] == []
    assert data["rows"] == [
        {
            "id": "e3-report-refused",
            "tier": "E3",
            "status": "invalid",
            "classes": [],
            "detail": "report refused: result could not be sanitized",
            "warnings": [],
        }
    ]
    assert "stale-pass" not in report_text
    assert "RAW_CAPTURED_PRIOR" not in report_text
    assert len(replacements) == 1
    temporary, destination = replacements[0]
    assert destination == report.resolve()
    assert temporary.parent == report.parent
    assert temporary != destination
    assert not temporary.exists()


def test_cli_writes_constant_invalid_when_scanner_activation_inspection_fails(
    monkeypatch, tmp_path
):
    class BrokenActiveScanner(e3._CredentialScanner):
        @property
        def active(self):
            raise RuntimeError("active unavailable")

    scenario = tmp_path / "e3.json"
    scenario.write_text("{}", encoding="utf-8")
    report = tmp_path / "report.json"
    secret = "REFRESHED_REAL_CREDENTIAL_VALUE_7f1a"

    def run_with_activation_failure(*_args, **_kwargs):
        scratch = tmp_path / "scratch"
        scanner = BrokenActiveScanner()
        scanner.add_value(b"CONTROLLED_RUNTIME_SENTINEL_activation_failure")
        return e3._scan_and_teardown(
            ScenarioResult(
                "unsafe-primary",
                "E3",
                Status.FAIL,
                [],
                detail="unsafe-primary-detail",
                warnings=[secret],
            ),
            scanner,
            scratch,
            child_outputs=[],
            ambient_snapshots={},
            credential_guards={},
            claude_dest=scratch / "profile" / ".credentials.json",
            codex_dest=scratch / "profile" / "auth.json",
            profile_root=scratch / "profile",
            host2=scratch / "host2",
            seed_parent=scratch / "seed-ws",
            remove_targets=False,
        )

    monkeypatch.setattr(cli, "run_e3", run_with_activation_failure)

    assert (
        cli.main(
            [
                "--biv",
                str(STUB),
                "--e3",
                str(scenario),
                "--report",
                str(report),
            ]
        )
        == 1
    )
    report_text = report.read_text(encoding="utf-8")
    data = json.loads(report_text)
    assert data["invalid"] == ["e3-report-refused"]
    assert data["rows"][0]["warnings"] == []
    assert secret not in report_text
    assert "unsafe-primary" not in report_text
    assert "unsafe-primary-detail" not in report_text


def test_cli_writes_constant_invalid_when_scanner_is_empty(monkeypatch, tmp_path):
    scenario = tmp_path / "e3.json"
    scenario.write_text("{}", encoding="utf-8")
    report = tmp_path / "report.json"
    secret = "REFRESHED_REAL_CREDENTIAL_VALUE_empty_scanner"

    def run_with_empty_scanner(*_args, **_kwargs):
        scratch = tmp_path / "scratch"
        return e3._scan_and_teardown(
            ScenarioResult(
                "unsafe-empty-primary",
                "E3",
                Status.FAIL,
                ["unsafe-class"],
                ["unsafe-assert"],
                detail="unsafe-empty-primary-detail",
                warnings=[secret],
            ),
            e3._CredentialScanner(),
            scratch,
            child_outputs=[],
            ambient_snapshots={},
            credential_guards={},
            claude_dest=scratch / "profile" / ".credentials.json",
            codex_dest=scratch / "profile" / "auth.json",
            profile_root=scratch / "profile",
            host2=scratch / "host2",
            seed_parent=scratch / "seed-ws",
            remove_targets=False,
        )

    monkeypatch.setattr(cli, "run_e3", run_with_empty_scanner)

    assert (
        cli.main(
            [
                "--biv",
                str(STUB),
                "--e3",
                str(scenario),
                "--report",
                str(report),
            ]
        )
        == 1
    )
    report_text = report.read_text(encoding="utf-8")
    assert json.loads(report_text)["rows"] == [
        {
            "id": "e3-report-refused",
            "tier": "E3",
            "status": "invalid",
            "classes": [],
            "detail": "report refused: result could not be sanitized",
            "warnings": [],
        }
    ]
    assert secret not in report_text
    assert "unsafe-empty-primary" not in report_text
    assert "unsafe-empty-primary-detail" not in report_text


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
