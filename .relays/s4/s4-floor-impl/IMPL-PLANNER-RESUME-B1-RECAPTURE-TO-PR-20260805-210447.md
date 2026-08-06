## IMPL — RESUME B1 to PR: the standing recapture rule is granted and folded as Amendment A2; recapture the envelope lock entry on the B1 head, prove green, scoped review, then the PR; Tasks 4-11 unblocked behind it

ROLE: Planner
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: s4-floor-impl-2
PARENT_DISPATCH_ID: s4-floor-pair-plan-review-approve
RUN_ID: s4
TASK_ID: B1
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — sequencing on the live s4-floor-impl-2 dispatch under the orchestrator's `200505` ruling, which authorized the B1 fold directly; merge remains the operator's; the release hold is ABSOLUTE
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-B1-SCHEMA-LOCK-RECAPTURE-RULE-GRANTED-BOTH-PAIRS-20260805-200505.md
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: s4.orchestrator-planner, operator
SUBJECT: RESUME — Amendment A2 folded (amended plan SHA 9ae81519…); recapture the envelope entry to the reviewed 561dccf0… in the B1 head; then focused-green → scoped review → B1 PR; Tasks 4-11 unblock

The ruling (`200505`) grants exactly what was routed: the STANDING per-slice recapture
rule, both pairs, with the immediate B1 fold AUTHORIZED — no further gate was placed on
it beyond your own scoped review of the recapture commit.

Folded at this seat: **AMENDMENT A2** in the plan's dispatch-scope section
(`docs/sprints/2026-08-04-s4-step4/plans/2026-08-05-s4-floor-fold-plan.md`, SHA at this
filing `9ae81519…`), carrying the ruling's bound verbatim in substance:
`harness/selftest/test_envelope.py` admitted for MECHANICAL LOCK RECAPTURE ONLY —
literal-for-literal, same reviewed head, only for a schema the head actually changed;
anything else in that file is a new deviation routed up before an edit; the frozen-oracle
discipline is untouched. The A/C recurrences (Task 5 envelope, Task 7 exit map) ride
their one-commit laws.

SCOPE_DIFF (delta row over the A1-widened universe; all prior rows unchanged and all-in
per the standing dispatch and Amendment A1):
- harness/selftest/test_envelope.py -> in
SCOPE_DIFF_RESULT: all-in

Your resume sequence, per your own stated shape (now authorized end to end):
1. On the B1 head, update ONLY the envelope entry of `CURRENT_LOCKED_SCHEMA_BLOBS` to
   the reviewed blob `561dccf0dbd8e374b975ba19e2dbd8ddad553e81` (the exit-map entry does
   NOT recapture — B1 did not change that schema; the rule forbids it).
2. Prove the focused lock test + the relevant harness selection green at the head.
3. Scoped review of the recapture commit.
4. Open the B1 PR (target `main`, base per the plan's topology section), carrying the
   three non-gating reviewer items to the panel as recorded.
5. Tasks 4-11 UNBLOCK behind the PR: seed `s4-floor/a-floor-core` off the B1 head and
   proceed — slice A's one-commit law and the same recapture rule apply at Task 5.

No new token is needed or issued here — the standing `s4-floor-impl-2` dispatch remains
the live authority; this relay is sequencing on it.

ACTIONS_GIT_REF: writes at this seat: the plan Amendment A2 text + this relay + its INDEX row, committed on the docs lane with explicit paths (SHA in the commit record); no product/test/harness/schema edit; no new token
FINAL_GIT_STATUS_SHORT: not a read-only phase report; disk evidence rides the docs-lane commit SHA in ACTIONS_GIT_REF

CARRY LIST:
- `.relays/s4/s4-floor-impl/IMPL-PLANNER-RESUME-B1-RECAPTURE-TO-PR-20260805-210447.md` → `s4-floor.implementer`
