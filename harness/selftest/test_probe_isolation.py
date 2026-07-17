import json
import shlex
import subprocess
import sys
from pathlib import Path

from bivharness import scenario
from bivharness.report import Status

from test_scenario import use_schema_root
from test_specs import SCENARIOS, STUB


EXPECTED = {
    "codex": ("codex-standin", "codex-cli 0.144.4\n", "0.144.4"),
    "claude-code": (
        "claude-code-standin",
        "2.1.211 (Claude Code)\n",
        "2.1.211",
    ),
}


def _write_executable(path: Path, body: str) -> Path:
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text("#!/bin/sh\n" + body, encoding="utf-8")
    path.chmod(0o755)
    return path


def test_standins_have_non_registry_names_and_exact_reality_shapes(tmp_path):
    standins = scenario._prepare_probe_standins(tmp_path)

    assert set(standins) == set(EXPECTED)
    for agent, (filename, raw, parsed) in EXPECTED.items():
        standin = standins[agent]
        assert standin.path.name == filename
        assert standin.raw == raw
        assert standin.parsed == parsed
        run = subprocess.run(
            [standin.path, "--version"],
            check=False,
            capture_output=True,
            text=True,
            env={"PATH": str(standin.path.parent)},
        )
        assert run.returncode == 0
        assert run.stdout == raw
        assert run.stderr == ""


def test_every_scenario_open_injects_all_pins_and_sandboxes_path(
    monkeypatch, tmp_path
):
    use_schema_root(monkeypatch, tmp_path)
    monkeypatch.setenv("STUB_BIV_MODE", "ok")
    calls = []
    original = scenario._run_json

    def capture(biv, args, cwd, env_overrides=None):
        calls.append((list(args), dict(env_overrides or {})))
        return original(biv, args, cwd, env_overrides)

    monkeypatch.setattr(scenario, "_run_json", capture)
    result = scenario.run_scenario(
        SCENARIOS / "plain-dir-v1.json", STUB, tmp_path / "scratch"
    )

    assert result.status is Status.PASS, result.detail
    open_calls = [(args, env) for args, env in calls if args[0] == "open"]
    assert len(open_calls) == 1
    args, env = open_calls[0]
    pin_values = [args[index + 1] for index, arg in enumerate(args) if arg == "--agent-bin"]
    assert pin_values == [
        f"codex={tmp_path / 'scratch/plain-dir-v1/probe-standins/codex-standin'}",
        "claude-code="
        f"{tmp_path / 'scratch/plain-dir-v1/probe-standins/claude-code-standin'}",
    ]
    assert env["PATH"] == str(tmp_path / "scratch/plain-dir-v1/probe-standins")


def test_open_path_sandbox_blocks_ambient_registry_canary(monkeypatch, tmp_path):
    marker = tmp_path / "ambient-agent-ran"
    ambient = tmp_path / "ambient"
    for name in ("codex", "claude", "claude-code"):
        _write_executable(
            ambient / name,
            f"printf '%s\\n' {shlex.quote(name)} >> {shlex.quote(str(marker))}\n",
        )
    monkeypatch.setenv("PATH", str(ambient))

    wrapper = _write_executable(
        tmp_path / "biv-wrapper",
        (
            'if [ "${1-}" = "open" ]; then\n'
            "  for agent in codex claude claude-code; do\n"
            '    "$agent" --version >/dev/null 2>&1 || true\n'
            "  done\n"
            "fi\n"
            f"exec {shlex.quote(sys.executable)} {shlex.quote(str(STUB))} \"$@\"\n"
        ),
    )
    use_schema_root(monkeypatch, tmp_path)
    monkeypatch.setenv("STUB_BIV_MODE", "ok")

    result = scenario.run_scenario(
        SCENARIOS / "plain-dir-v1.json",
        wrapper,
        tmp_path / "scratch",
    )

    assert result.status is Status.PASS, result.detail
    assert not marker.exists()


def test_probe_oracle_binds_pinned_paths_and_exact_shapes(tmp_path):
    standins = scenario._prepare_probe_standins(tmp_path)
    agents = []
    for agent, standin in standins.items():
        agents.append(
            {
                "agent": agent,
                "probe": {
                    "agent": agent,
                    "requested": str(standin.path),
                    "executed": str(standin.path),
                    "pinned": True,
                    "outcome": "ok",
                    "exit_code": 0,
                    "raw": standin.raw,
                    "parsed": standin.parsed,
                },
            }
        )
    envelope = {"result": {"sessions": {"agents": agents}}}

    assert scenario._probe_oracle_failures(envelope, standins) == []

    broken = json.loads(json.dumps(envelope))
    broken["result"]["sessions"]["agents"][0]["probe"]["pinned"] = False
    failures = scenario._probe_oracle_failures(broken, standins)
    assert len(failures) == 1
    assert "probe oracle mismatch for codex" in failures[0]


def test_probe_oracle_accepts_refusal_envelope_without_result(tmp_path):
    standins = scenario._prepare_probe_standins(tmp_path)

    assert scenario._probe_oracle_failures({"result": None}, standins) == []
