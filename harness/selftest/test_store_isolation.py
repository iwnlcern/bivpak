import json
import re
from pathlib import Path

import pytest

from bivharness import e3, scenario
from bivharness.report import Status

from test_scenario import _basic_spec, use_schema_root
from test_specs import SCENARIOS, STUB


LOG = "STUB_BIV_DISCOVERY_LOG"


@pytest.fixture
def poison(tmp_path, monkeypatch):
    poison_root = tmp_path / "poison"
    env = scenario._poison_roots(
        poison_root,
        tmp_path / "scratch" / "iso" / "source",
    )
    for locator, value in env.items():
        monkeypatch.setenv(locator, value)
    return poison_root


def _run_poisoned(tmp_path, monkeypatch, log):
    monkeypatch.setenv(LOG, str(log))
    spec = _basic_spec(tmp_path, id="iso", agents=["claude-code", "codex"])
    return scenario.run_scenario(spec, STUB, tmp_path / "scratch"), (
        tmp_path / "scratch" / "iso"
    )


def _entries(log):
    return [
        tuple(line.split(" ", 2))
        for line in log.read_text(encoding="utf-8").splitlines()
    ]


def _leak_tags(entries, poison_root):
    return {
        tag
        for _, tag, path in entries
        if Path(path).is_relative_to(poison_root)
    }


def _assert_hermetic_discovery(entries, poison_root, work):
    leaks = _leak_tags(entries, poison_root)
    assert not leaks, f"poison reachable through {sorted(leaks)}"
    tmp = [Path(path) for _, tag, path in entries if tag == "TMPDIR"]
    assert tmp and all(
        path.is_relative_to(work / "hermetic" / "tmp") for path in tmp
    ), f"temp root outside scratch: {tmp}"


def _restore_poison(monkeypatch, locator):
    original = scenario._run_json

    def mutated(biv, args, cwd, env_overrides=None):
        overrides = dict(env_overrides or {})
        overrides.pop(locator, None)
        return original(biv, args, cwd, overrides)

    monkeypatch.setattr(scenario, "_run_json", mutated)


def _run_mutant(tmp_path, monkeypatch, poison, locator):
    use_schema_root(monkeypatch, tmp_path)
    log = tmp_path / "discovery.log"
    _restore_poison(monkeypatch, locator)
    result, work = _run_poisoned(tmp_path, monkeypatch, log)
    entries = _entries(log)
    with pytest.raises(AssertionError):
        _assert_hermetic_discovery(entries, poison, work)
    assert _leak_tags(entries, poison) == {locator}
    return result, entries


def test_poisoned_inherited_stores_are_replaced_by_scenario_stores(
    monkeypatch, tmp_path, poison
):
    use_schema_root(monkeypatch, tmp_path)
    log = tmp_path / "discovery.log"

    result, work = _run_poisoned(tmp_path, monkeypatch, log)
    entries = _entries(log)

    assert result.status is Status.PASS, result.detail
    paths = [Path(path) for _, _, path in entries]
    assert any(
        Path(path).name == "aaaaaaaa-1111-4000-8000-000000000001.jsonl"
        and tag == "CLAUDE_CONFIG_DIR"
        for _, tag, path in entries
    )
    assert any(
        Path(path).name
        == "rollout-2026-07-11T01-00-00-019faaaa-bbbb-7ccc-8ddd-eeeeeeee0001.jsonl"
        and tag == "CODEX_HOME"
        for _, tag, path in entries
    )
    assert paths
    _assert_hermetic_discovery(entries, poison, work)


def test_home_restore_exposes_both_home_default_canaries(
    monkeypatch, tmp_path, poison
):
    # NAMED MUTANT: HOME restored to the poison root ⇒ RED here (the HOME-default canaries surface).
    result, entries = _run_mutant(tmp_path, monkeypatch, poison, "HOME")

    assert result.status is Status.PASS, result.detail
    assert scenario.POISON_SESSION_IDS["HOME:codex"] in "\n".join(
        path for _, _, path in entries
    )
    assert scenario.POISON_SESSION_IDS["HOME:claude"] in "\n".join(
        path for _, _, path in entries
    )


def test_codex_home_restore_exposes_its_canary(monkeypatch, tmp_path, poison):
    # NAMED MUTANT: CODEX_HOME restored to poison ⇒ RED here.
    result, entries = _run_mutant(tmp_path, monkeypatch, poison, "CODEX_HOME")

    assert result.status is Status.PASS, result.detail
    assert scenario.POISON_SESSION_IDS["CODEX_HOME"] in "\n".join(
        path for _, _, path in entries
    )


def test_codex_sqlite_restore_exposes_the_database_path(
    monkeypatch, tmp_path, poison
):
    # NAMED MUTANT: CODEX_SQLITE_HOME restored to poison ⇒ RED here (the sqlite canary is scanned).
    result, entries = _run_mutant(
        tmp_path, monkeypatch, poison, "CODEX_SQLITE_HOME"
    )

    assert result.status is Status.PASS, result.detail
    assert ("pack", "CODEX_SQLITE_HOME", str(poison / "codex-sqlite/state_5.sqlite")) in entries


def test_claude_config_restore_exposes_its_canary(monkeypatch, tmp_path, poison):
    # NAMED MUTANT: CLAUDE_CONFIG_DIR restored to poison ⇒ RED here.
    result, entries = _run_mutant(
        tmp_path, monkeypatch, poison, "CLAUDE_CONFIG_DIR"
    )

    assert result.status is Status.PASS, result.detail
    assert scenario.POISON_SESSION_IDS["CLAUDE_CONFIG_DIR"] in "\n".join(
        path for _, _, path in entries
    )


def test_tmpdir_restore_exposes_the_poison_temp_root(monkeypatch, tmp_path, poison):
    # NAMED MUTANT: TMPDIR inherited (poisoned) instead of overlaid ⇒ RED here.
    result, _ = _run_mutant(tmp_path, monkeypatch, poison, "TMPDIR")

    assert result.status is Status.PASS, result.detail


def test_adapter_locator_census_matches_the_source_aware_harness_set():
    # NAMED MUTANT: a store-locator getenv added to the adapters and absent from the harness set ⇒ RED at (a).
    adapter_root = Path(__file__).resolve().parents[2] / "src" / "adapters"
    adapter_getenv_locators = {
        match.group(1)
        for path in adapter_root.rglob("*.cpp")
        for match in re.finditer(
            r'getenv\("([A-Z_]+)"\)', path.read_text(encoding="utf-8")
        )
    }

    assert adapter_getenv_locators == (
        set(scenario.HERMETIC_LOCATORS) - scenario.MANDATORY_PROCESS_LOCATORS
    )


def test_every_runnable_scenario_overlays_all_five_locators(
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
    for spec_path in SCENARIOS.rglob("*.json"):
        spec = json.loads(spec_path.read_text(encoding="utf-8"))
        if spec.get("status") == "xfail-pending":
            continue
        before = len(calls)
        scenario.run_scenario(spec_path, STUB, tmp_path / "scratch")
        scenario_calls = calls[before:]
        assert scenario_calls, spec_path
        work = tmp_path / "scratch" / spec["id"]
        for args, env in scenario_calls:
            assert args[0] in {"pack", "open"}
            assert set(scenario.HERMETIC_LOCATORS) <= set(env)
            assert all(
                Path(env[locator]).resolve().is_relative_to(work.resolve())
                for locator in scenario.HERMETIC_LOCATORS
            )


def test_command_budgets_remain_uncalibrated():
    # NAMED MUTANT: a budget byte moved in this act's commit ⇒ RED here (V-ISO-1 vetoes it regardless).
    assert scenario.COMMAND_TIMEOUT_S == 30
    assert e3.COMMAND_TIMEOUT_S == 120


def test_runtime_guard_rejects_missing_and_outside_locators(tmp_path):
    work = tmp_path / "work"
    overlay = scenario._hermetic_overlay(work)

    missing = dict(overlay)
    missing.pop("CODEX_HOME")
    assert scenario._assert_hermetic(missing, work) == [
        "hermetic-env: CODEX_HOME absent from command environment"
    ]
    assert scenario._assert_hermetic(overlay, work) == []
    outside = dict(overlay)
    outside["TMPDIR"] = str(tmp_path / "outside")
    assert scenario._assert_hermetic(outside, work) == [
        f"hermetic-env: TMPDIR points outside scenario scratch: {tmp_path / 'outside'}"
    ]


def test_runner_fails_closed_when_overlay_omits_a_locator(monkeypatch, tmp_path):
    use_schema_root(monkeypatch, tmp_path)
    original = scenario._hermetic_overlay

    def missing_codex_home(work):
        overlay = original(work)
        overlay.pop("CODEX_HOME")
        return overlay

    monkeypatch.setattr(scenario, "_hermetic_overlay", missing_codex_home)
    result = scenario.run_scenario(
        _basic_spec(tmp_path), STUB, tmp_path / "scratch"
    )

    assert result.status is Status.INVALID
    assert "hermetic-env: CODEX_HOME absent" in result.detail
