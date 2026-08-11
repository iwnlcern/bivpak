## REVIEW-FOLD BLOCKER — F5 crosses the locked file universe and its proposed test-only macro wiring cannot close the shipping-symbol finding as written; no B1 fold edit made

ROLE: Implementer
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-floor-impl-2-b1-review-fold-f5-blocker
PARENT_DISPATCH_ID: s4-floor-impl-2-b1-review-fold
RUN_ID: s4
TASK_ID: B1
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: yes — orchestrator scope disposition and a technically complete F5 seam shape are required before the fold can begin
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/REVIEW-FOLD-PLANNER-B1-PANEL-CONSOLIDATED-20260806-015651.md
FROM: s4-floor.implementer
TO: s4-floor.planner
CC: s4.orchestrator-planner, operator
SUBJECT: REVIEW-FOLD BLOCKED BEFORE EDIT — F5 needs OUT codex.hpp and non-authorized CMake seam wiring; requested macro placement does not compile a guarded definition

FOLD_SCOPE:
- src/adapters/codex/codex.cpp -> in
- src/adapters/codex/codex.hpp -> out
- src/cli/main.cpp -> in
- tests/test_adapter_codex_collect.cpp -> in
- tests/test_cli.cpp -> in
- tests/test_envelope.cpp -> in
- tests/fixtures/codex_store/** -> in
- CMakeLists.txt (BIV_CODEX_TESTING seam wiring) -> out
- docs/sprints/2026-08-04-s4-step4/results/receipts/** -> in
- PR #15 body -> in
FOLD_SCOPE_RESULT: deviation-present

## Verified scope contradiction

The locked plan's dispatch universe at
`docs/sprints/2026-08-04-s4-step4/plans/2026-08-05-s4-floor-fold-plan.md:32-36`
enumerates `src/adapters/codex/codex.cpp`, but not
`src/adapters/codex/codex.hpp`. Its `CMakeLists.txt` admission is explicitly
limited to “build wiring for the two new units” in Slice A. Amendment A1 adds
only the JSON writer paths; A2/A3 add only their mechanical lock literals.

F5 requests both excluded surfaces:

- declare the seam in `src/adapters/codex/codex.hpp`; and
- add `BIV_CODEX_TESTING` wiring in `CMakeLists.txt`.

The panel package's assertion that all fixes are already inside the granted
universe therefore conflicts with the mechanical file set. Under the standing
scope rule, no finding severity or acceptance need converts either OUT row to
IN.

## Verified implementation-shape gap

The proposed “declare behind `BIV_CODEX_TESTING`, add the define to
`biv_tests` only” does not by itself close F5:

- `src/adapters/codex/codex.cpp` is compiled into `biv_adapters`, not into
  `biv_tests`;
- a macro private to `biv_tests` makes a guarded declaration visible to the
  test translation unit, but it does not compile a guarded definition into
  `biv_adapters`;
- if the definition remains unguarded, the complained-of shipping symbol
  remains;
- if the definition is guarded, the test declaration has no linked definition.

The cited probe idiom solves this with a separately compiled
`biv_probe_test_seam` target plus `BIV_PROBE_TEST_SEAM_ONLY`. An equivalent
Codex shape would require additional CMake authority and either a seam-only
compilation boundary or another explicitly admitted production unit. A
different valid disposition is to narrow F5 to a shared declaration while
accepting the shipping helper, but that does not satisfy the panel's stated
boundary finding. The owner must choose and authorize the exact contract.

## Fold status

F1-F4 and F6-F9 were technically checked against `d5642ed` and remain queued,
not rejected. They were not partially folded because the REVIEW-FOLD protocol
requires all findings to be understood and every touched file to be in-scope
before the first edit. O1-O8 remain deferred; no optional has been accepted
while the must-fix scope is unresolved.

ACTIONS_GIT_REF: no PR-branch edit, commit, push, PR-body change, merge, release, or Slice-A restack performed; B1 remains s4-floor/b1-codex-liveness@d5642ed9ea19cd6256276681b63199adff21aea4; this blocker relay and its append-only INDEX row are the only seat writes on the docs lane
FINAL_GIT_STATUS_SHORT: B1 product worktree clean at d5642ed before filing; docs-lane write limited to this blocker relay and its INDEX row

NEXT REQUESTED ACTION:
The Planner should route the two OUT rows and the seam-compilation choice to
`s4.orchestrator-planner`. Resume only with a narrow amendment that admits the
selected paths and states whether F5 requires removal of the shipping symbol or
only a shared declaration/polarity consolidation. No new implementation token
is requested; this is REVIEW-FOLD scope disposition on PR #15.

CARRY LIST:
- `.relays/s4/s4-floor-impl/REVIEW-FOLD-BLOCKER-IMPLEMENTER-B1-F5-SCOPE-20260806-020831.md` → `s4-floor.planner`
- F5 OUT rows + seam-compilation choice → `s4.orchestrator-planner`
