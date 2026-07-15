import json
from pathlib import Path


HARNESS = Path(__file__).resolve().parents[1]


def test_cmake_registers_harness_and_safety_gate_rows():
    text = (HARNESS / "CMakeLists.txt").read_text(encoding="utf-8")
    for name in (
        "harness-selftest",
        "harness-e2",
        "safety-build-werror",
        "safety-asan-ubsan",
        "safety-tidy-analyzer",
        "safety-hardening",
        "safety-fuzz-smoke",
    ):
        assert name in text
    assert "fuzz_manifest_json" in text
    assert "fuzz_tar_member" in text
    assert "-runs=100000" in text
    assert "ASAN_OPTIONS" in text
    assert "UBSAN_OPTIONS" in text
    assert "halt_on_error=1" in text
    assert "safety-fuzz-smoke PROPERTIES TIMEOUT" in text
    assert "harness-e2 PROPERTIES" in text
    assert "LABELS" in text
    assert "run_clang_tidy.py" in text
    assert "set_tests_properties(safety-tidy-analyzer PROPERTIES\n    TIMEOUT 600" in text


def test_fuzz_budget_is_fixed_runs_and_seed():
    budget = json.loads((HARNESS / "fuzz" / "budgets.json").read_text(encoding="utf-8"))
    assert budget == {"runs": 100000, "seed": 1}


def test_safety_gate_doc_marks_future_rows_pending_and_no_local_waiver():
    text = (HARNESS / "ci" / "safety-gates.md").read_text(encoding="utf-8")
    assert "disabled check is a top-level review item" in text
    assert "TSan" in text
    assert "CB4-1" in text
    assert "git/SQLite/host-store" in text


def test_hardening_gate_checks_stack_and_fortify_without_bindnow_fallback():
    text = (HARNESS / "ci" / "check_hardening.py").read_text(encoding="utf-8")
    assert "__stack_chk_fail" in text
    assert "_FORTIFY_SOURCE" in text
    assert "-fstack-clash-protection" in text
    assert "(FLAGS)" not in text


def test_fuzz_smoke_copies_corpora_and_uses_artifact_prefix():
    text = (HARNESS / "ci" / "run_fuzz_smoke.py").read_text(encoding="utf-8")
    assert "copytree" in text
    assert "-artifact_prefix=" in text


def test_cmake_presets_and_ci_workflow_exist():
    assert (HARNESS / "CMakePresets.json").exists()
    workflow = HARNESS.parent / ".github" / "workflows" / "s2-harness.yml"
    assert workflow.exists()
    text = workflow.read_text(encoding="utf-8")
    assert "harness-selftest" in text
    assert "safety-fuzz-smoke" in text
