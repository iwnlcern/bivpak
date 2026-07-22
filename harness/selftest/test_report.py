from bivharness.report import Report, ScenarioResult, Status


def _r(status, id="s", tier="E2", warnings=None):
    return ScenarioResult(
        id=id,
        tier=tier,
        status=status,
        classes=["A"],
        held_asserts=[],
        detail="",
        warnings=warnings or [],
    )


def test_all_pass_exits_zero():
    assert Report([_r(Status.PASS)]).exit_code() == 0


def test_xfail_pending_never_green_but_not_red():
    rep = Report([_r(Status.PASS), _r(Status.XFAIL_PENDING, id="shell")])
    assert rep.exit_code() == 0
    assert rep.to_json()["pending"] == ["shell"]
    assert "shell" not in rep.to_json()["runnable_passed"]


def test_fail_and_invalid_exit_nonzero():
    assert Report([_r(Status.FAIL)]).exit_code() == 1
    assert Report([_r(Status.INVALID)]).exit_code() == 1


def test_pending_only_run_is_not_green():
    assert Report([_r(Status.XFAIL_PENDING)]).exit_code() == 1


def test_report_serializes_warned_and_clean_rows_distinctly():
    warned = _r(
        Status.PASS,
        id="warned",
        warnings=["CodexDbEnrichmentSkipped"],
    )
    clean = _r(Status.PASS, id="clean")

    rows = Report([warned, clean]).to_json()["rows"]

    assert rows[0]["warnings"] == ["CodexDbEnrichmentSkipped"]
    assert rows[1]["warnings"] == []
