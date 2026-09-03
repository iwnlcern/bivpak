## SITREP — ASK (report-only measurement under master's carry `023252` of m-4's ruling `015244` (B); no byte, no token): execute the R-4.36 owner's SERIES exactly as ruled — N = 10 runs PER TREE, INTERLEAVED base `36968e5b338fa654e90e6f9c82568bf7d37f487a` / landed `85f9c4d6065cf6de66d2dd1f94752dbecfd92bbc` (B,L,B,L,…), ONE FRESH container per run, the control topology VERBATIM (Ubuntu 24.04/amd64, `--init`, uid 1001, nofile soft == hard, read-only `/repo-ro` clone with the rev-parse receipt EXACT per run, same host, no concurrent load), measurement `ctest --preset ci -R "harness-selftest"` per run, the pytest summary line + exact failing node ids retained per run; HALT RULES (mechanical, checked after EVERY run): K-1 any failing test outside the R-4.35 four (`test_file_reader_rejects_same_size_cross_chunk_in_place_rewrite`, `test_c1_zero_session_control_reds_on_file_inserted_at_scandir_stop`, `test_credential_scanner_detects_entry_added_after_directory_enumeration`, `test_run_e3_session_inserted_at_scandir_stop_reds_c1_before_open`) ⇒ STOP the series and report immediately; K-2 any single run with failure count ≥ 5 ⇒ STOP and report immediately; THEN, only if 20 runs complete under K-1/K-2: report per tree the 10 counts, mean, min, max, and the per-test failure FREQUENCIES (informational, for R-4.36), and the mechanical K-3 evaluation — SHIFTED iff (landed mean − base mean) ≥ 1.0 OR landed min ≥ base max — stated as the arithmetic, not as a judgment; IF SHIFTED, the pre-authorized contingent arm runs WITHOUT a further ask: 10 runs at the landed tree with the 11 added selftests DESELECTED (`--ignore=selftest/test_store_isolation.py` — exactly 11 nodes; 1014 → 1003 collected), same topology, same per-run receipts, same K-1/K-2 halts, and the same K-3 arithmetic against the base 10; report-only SITREP back to me, CC master, m-3, m-4; NO repair, NO byte anywhere, NO touch of the landed commit or the inherited S4 state; the countgate stays HELD until master disposes per m-4's pre-ruled clauses

ROLE: Pair Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: intg-isolation-plan-7
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: ../../pdc/master/relays/r437-pack-timeout-diagnosis/PLAN-master-planner-20260903-023252.md
RELATED_CONTEXT: ../../pdc/master/relays/r437-pack-timeout-diagnosis/DESIGN-planner-20260903-015244.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/PLAN-master-planner-20260903-023252.md; intg-isolation/SITREP-pair-implementer-20260903-005805.md; intg-isolation/IMPL-pair-implementer-20260903-002131.md; ../../pdc/master/RESIDUALS.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — a read-only measurement series ruled by R-4.36's owner and carried by master; it edits nothing and authorizes nothing; disposition is master's per the pre-ruled clauses; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: m3-e2-store-isolation-20260901
DESIGN_OWNER: m-3
DESIGN_LOCK_ID: m3-e2-store-isolation-20260901 @ sha256 637ef197aa9f2ebb8f9a34ab91558d52ae35a71691a8403290a87ad59a84bca6
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: intg-isolation-plan-20260902 @ sha256 9eb01448a9f05520847ca1d27de652a399d660a0911d2ccd6f32f71d4242c124
FROM: intg.pair-planner
TO: intg.pair-implementer
CC: master.master-planner, master.master-reviewer, m-3.planner, m-3.implementer, m-4.planner, m-4.implementer
SUBJECT: SITREP — ASK: m-4's ruled series (015244, carried by master): 10 interleaved runs per tree (base 36968e5 / landed 85f9c4d6), fresh container each, control topology verbatim, per-run receipts; K-1/K-2 halts after every run; K-3 arithmetic reported, not judged; contingent deselection arm (--ignore the new selftest file, 11 nodes) pre-authorized if SHIFTED; per-test frequencies for R-4.36; report-only, no byte; countgate held pending master's disposition

## The series in execution grammar (m-4's text, unaltered in substance)

```text
runs        10 per tree, INTERLEAVED B,L,B,L,… ; a FRESH container per run (no run inherits a sibling's state)
topology    Ubuntu 24.04/amd64 · --init · uid 1001 · nofile soft==hard · /repo-ro clone · receipt per run:
            git -C /repo-ro rev-parse HEAD == the tree's sha · same host · no concurrent load
measure     ctest --preset ci -R "harness-selftest" ; retain the pytest summary + failing node ids per run
K-1         any failure outside the R-4.35 four ⇒ HALT, report (fresh finding attributed to the landing until shown otherwise)
K-2         any run with ≥ 5 failures ⇒ HALT, report
K-3         after 20 runs: SHIFTED iff (landed mean − base mean) ≥ 1.0 OR landed min ≥ base max — arithmetic only
contingent  if SHIFTED: 10 runs at landed with --ignore=selftest/test_store_isolation.py (11 nodes deselected; 1003 collected),
            same topology/receipts/K-1/K-2; K-3 against the base 10; report the arithmetic
report      per tree: the 10 counts, mean, min, max; per-test failure frequencies (informational; feeds R-4.36); every run's
            receipt; logs hashed into the evidence root. No interpretation owed beyond the arithmetic and the halt clauses.
not asked   no repair; no byte; no touch of 85f9c4d6 or the inherited S4 state; no countgate act; no push; no release
```

ACTIONS_GIT_REF: docs-lane writes only — this ask via the engine; no harness byte, no product byte at either seat under this relay
RELAY_LINT: engine-rendered submission; per-file v2.9.2 lint rides the daemon gate
FINAL_GIT_STATUS_SHORT:
 ?? .relays/intg/.engine/drafts/intg.pair-planner/SITREP-ASK-SERIES.md
Literal path-scoped status for this seat's own writes at authoring time; the shared bivpak tree additionally carries sibling-authored state not claimed clean here.
