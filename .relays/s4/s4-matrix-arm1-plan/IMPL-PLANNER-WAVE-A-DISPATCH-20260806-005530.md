## IMPL DISPATCH — Wave A of the approved Arm-1 plan (T1–T4): delegated conditions verified, scope all-in, token below

ROLE: Planner
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: s4-matrix-arm1-impl-wave-a
PARENT_DISPATCH_ID: s4-matrix-arm1-plan-review-rev2
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-REV2-20260806-005302.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — delegated conditional dispatch per the PROCEED-TO-PLAN (20260805-220522), all standing conditions verified below; Waves B/C/D remain F-FENCED and are NOT dispatched here; merge is the operator's; the release hold is ABSOLUTE
DESIGN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-05-s4-matrix-arm1-design.md
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/plans/2026-08-06-s4-matrix-arm1-plan.md
FROM: s4-matrix.planner
TO: s4-matrix.implementer
CC: s4.orchestrator-planner, operator
SUBJECT: IMPL — Wave A only (T1 runner, T2 types+wrapper, T3 harness day one, T4 engine units); linear stack t1←main…t4←t3; per-task reports; fences stay live

Delegated-condition verification (each PROCEED condition, checked at this seat):
- Plan review approve: `PLAN-REVIEW-IMPLEMENTER-REV2-20260806-005302`, `PLAN_REVIEW_VERDICT: approve` on the bare line, BASE `8df4cf8` — this relay's PARENT_DISPATCH_ID.
- Lineage: that review parents to `s4-matrix-arm1-plan` (my PLAN, addressed to you in TO); this dispatch parents to the review — the required chain, unique ids throughout.
- Lint disposition: the thirteen root reds are class-scoped on named authority with the operator's recorded waiver (`…NAMED-ERROR-DISPOSITION-THIRTEEN-REDS-SCOPED-20260806-004554`); no new root-lint class has appeared since.
- Hard triggers: none — Wave A is new files + the probe-adapter refactor + harness-only work; no authz/migration/money/downstream-automation/worker/cross-repo-contract/user-visible-materializer/test-role/scope-expansion touch. The probe law-comment re-scope is design-reviewed content (D1.1), cited to its ruling.
- The scope diff below is mechanical — list, not judgment; NO F-fenced path is named by this dispatch.

SCOPE_DIFF:
- src/core/support/subprocess.hpp -> in
- src/core/support/subprocess.cpp -> in
- src/core/support/probe.hpp -> in
- src/core/support/probe.cpp -> in
- tests/test_subprocess.cpp -> in
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

Bounded semantics riding three of those rows (locked plan, R2 fold): the ledger row is
STATUS-ONLY transitions in Wave-A-keyed rows (T3's L-G2/L-G3); the report row is one new
file per task under `.relays/s4/s4-matrix-arm1-impl/`; the INDEX row is append-at-EOF
only, one row per report.

Dispatched scope: the locked plan's WAVE A — tasks T1, T2, T3, T4 exactly as written
(files, interfaces, TDD cycles, acceptance criteria), executed under Superpowers
executing-plans on the ONE LINEAR STACK: `s4-matrix/arm1-t1` ← `main`, t2←t1, t3←t2,
t4←t3; PRs target the base branch; per-task file-first implementation report + INDEX row;
author-side exact-file lint WITH freshness on every filing; the STOP RULE on every edge.
NOT dispatched: Waves B/C/D (T5–T8) — F-fenced until the pinned landing signal crosses
the bridge; any need to touch a file outside the SCOPE_DIFF rows above STOPS work and
relays to this seat (no minor-edit exception exists).
Both Step-3 fences and all landed behavior remain UNCHANGED through Wave A — the Wave-A
acceptance bars in the plan (probe tests untouched; full suite green unchanged; no
product wiring) are dispatch conditions, not suggestions.

DISPATCH IMPL

ACTIONS_GIT_REF: docs lane only — this dispatch + its INDEX row, committed on main with explicit paths (SHA in the commit record); no product edit by this relay.
FINAL_GIT_STATUS_SHORT:
none — clean tree
Fresh at 20260806-005530 before this relay + INDEX write; the two files this filing creates/modifies are the only working-tree delta at commit time and are named above.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/IMPL-PLANNER-WAVE-A-DISPATCH-20260806-005530.md` → TO `s4-matrix.implementer`
