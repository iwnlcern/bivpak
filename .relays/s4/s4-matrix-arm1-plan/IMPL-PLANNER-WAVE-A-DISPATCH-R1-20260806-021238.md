## IMPL DISPATCH (corrected, supersedes 005530) — Wave A of the rev3 plan (T1–T4): the admitted probe-test path is IN, all delegated conditions re-verified, token below

ROLE: Planner
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: s4-matrix-arm1-impl-wave-a-r1
PARENT_DISPATCH_ID: s4-matrix-arm1-plan-review-rev3-amendment
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-REV3-AMENDMENT-APPROVE-20260806-020547.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — delegated conditional dispatch per the PROCEED-TO-PLAN (20260805-220522) on the amended plan; all standing conditions re-verified below; Waves B/C/D remain F-FENCED and are NOT dispatched here; merge is the operator's; the release hold is ABSOLUTE
DESIGN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-05-s4-matrix-arm1-design.md
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/plans/2026-08-06-s4-matrix-arm1-plan.md
FROM: s4-matrix.planner
TO: s4-matrix.implementer
CC: s4.orchestrator-planner, operator
SUBJECT: IMPL — Wave A resumed on plan rev3 (T1 incl. the granted T1.5a relocation); the 005530 dispatch is SUPERSEDED by this one; linear stack t1←main…t4←t3

Supersession, explicit: the prior Wave-A dispatch (`s4-matrix-arm1-impl-wave-a`,
20260806-005530) is SUPERSEDED by this relay — its authorization is spent; this is the
one live Wave-A dispatch, and this sentence is its successor pointer.

Delegated-condition verification (re-run at this seat for the amended plan):
- Plan approve chain: rev2 approve (`…-005302`) stands un-reopened; the rev3 delta
  concurrence is `PLAN-REVIEW-IMPLEMENTER-REV3-AMENDMENT-APPROVE-20260806-020547`
  (`PLAN_REVIEW_VERDICT: approve` on the bare line, BASE `f2846f2`, plan blob
  `e1e6fd43…`) — this relay's PARENT_DISPATCH_ID; that review parents to
  `s4-matrix-arm1-plan`; the required chain holds with unique ids.
- Scope authority for the added path: the orchestrator grant
  (`…T1-RELOCATION-GRANTED-…-20260806-014725`) admits `tests/test_probe.cpp` for T1.5a's
  mechanical relocation only.
- Lint disposition: the thirteen root reds remain class-scoped on named authority; no new
  root-lint class has appeared.
- Hard triggers: none — unchanged from the 005530 analysis; the added path is a test-file
  anchor relocation under an explicit grant.

SCOPE_DIFF:
- src/core/support/subprocess.hpp -> in
- src/core/support/subprocess.cpp -> in
- src/core/support/probe.hpp -> in
- src/core/support/probe.cpp -> in
- tests/test_subprocess.cpp -> in
- tests/test_probe.cpp -> in
- src/core/repo/types.hpp -> in
- src/core/repo/git.hpp -> in
- src/core/repo/git.cpp -> in
- tests/test_repo_git.cpp -> in
- src/core/repo/discover.hpp -> in
- src/core/repo/discover.cpp -> in
- src/core/repo/classify.hpp -> in
- src/core/repo/classify.cpp -> in
- src/core/repo/eligibility.hpp -> in
- src/core/repo/eligibility.cpp -> in
- src/core/repo/capture.hpp -> in
- src/core/repo/capture.cpp -> in
- src/core/repo/restore.hpp -> in
- src/core/repo/restore.cpp -> in
- tests/test_repo_engine.cpp -> in
- CMakeLists.txt -> in
- harness/bivharness/fixtures.py -> in
- harness/bivharness/compare.py -> in
- harness/bivharness/scenario.py -> in
- harness/tolerance/tolerance-v1.json -> in
- harness/selftest/test_fixtures.py -> in
- harness/selftest/test_compare.py -> in
- harness/selftest/test_scenario.py -> in
- docs/sprints/2026-08-04-s4-step4/results/dr3-fixture-ledger.md -> in
- .relays/s4/s4-matrix-arm1-impl/IMPL-IMPLEMENTER-*.md -> in
- .relays/s4/INDEX.md -> in
SCOPE_DIFF_RESULT: all-in

Bounded semantics riding four of those rows (locked plan rev3): `tests/test_probe.cpp` is
T1.5a ONLY — the one test case's location anchors + the successor-instrument sentence,
zero behavioral assertion changes, anything wider is a NEW deviation routed before an
edit; the ledger row is STATUS-ONLY in Wave-A-keyed rows (T3's L-G2/L-G3); the report row
is one new file per task under `.relays/s4/s4-matrix-arm1-impl/`; the INDEX row is
append-at-EOF only.

Dispatched scope: the rev3 plan's WAVE A — T1 (incl. T1.5a), T2, T3, T4 exactly as
written, under Superpowers executing-plans on the ONE LINEAR STACK
(`s4-matrix/arm1-t1` ← `main`, t2←t1, t3←t2, t4←t3); PRs target the base branch;
per-task file-first report + INDEX row; author-side exact-file lint WITH freshness on
every filing; the STOP RULE on every edge.
NOT dispatched: Waves B/C/D (T5–T8) — F-fenced until the pinned landing signal crosses
the bridge; any need to touch a file outside the SCOPE_DIFF rows above STOPS work and
relays to this seat.
Both Step-3 fences and all landed behavior remain UNCHANGED through Wave A; the Wave-A
acceptance bars in the rev3 plan are dispatch conditions.

DISPATCH IMPL

ACTIONS_GIT_REF: docs lane only — this dispatch + its INDEX row, committed on main with explicit paths (SHA in the commit record); no product edit by this relay.
FINAL_GIT_STATUS_SHORT:
none — clean tree
Fresh at 20260806-021238 before this relay + INDEX write; the two files this filing creates/modifies are the only working-tree delta at commit time and are named above.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/IMPL-PLANNER-WAVE-A-DISPATCH-R1-20260806-021238.md` → TO `s4-matrix.implementer`
