## PLAN AMENDMENT A1 — the granted three-path additive widening is folded into the plan text; SCOPE_DIFF over the widened universe returns all-in; DELTA REVIEW requested on the amendment

ROLE: Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-floor-pair-plan-amendment-a1
PARENT_DISPATCH_ID: s4-floor-design-review-rev5
RUN_ID: s4
TASK_ID: 1
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no — the disposition is the orchestrator's `182217` grant; what remains is your delta approve on the amendment's text, which is pair-internal; the standing dispatch stays live; merge is the operator's; the release hold is ABSOLUTE
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-TASK1-EXPANSION-GRANTED-ADDITIVE-ONLY-DELTA-REVIEW-20260805-182217.md
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: s4.orchestrator-planner, operator
SUBJECT: PLAN — Amendment A1 folded (three writer paths, additive-only bound verbatim); amended plan SHA b6b3907c…; delta plan-review approve requested; on it Task 1 resumes and Tasks 2-11 unblock

The amended plan of record (same `PLAN_LOCK_ID`; the only delta is the named
AMENDMENT A1 block in the dispatch-scope section):
`docs/sprints/2026-08-04-s4-step4/plans/2026-08-05-s4-floor-fold-plan.md`
— SHA-256 at this filing: `b6b3907c7f0bafc33710529da7d66f1b8c1d96473238ac2336dcd03ceb182275`.

What A1 says (the grant's bound, carried verbatim in substance): the three paths
`src/core/json/writer.hpp` / `src/core/json/writer.cpp` / `tests/test_json_writer.cpp`
enter the universe for exactly ONE addition — a public unsigned JSON integer emitter
beside the existing four, its unit boundary test incl. `UINT64_MAX`, and the Task-1
envelope/schema regression; no existing emitter/signature/serialization behavior
changes; any existing-surface change or fourth file is a NEW deviation routed up before
an edit; Task 1's serializer switches `bytes` to the new emitter; the shared-infra
single-owner note is carried.

SCOPE_DIFF over the WIDENED universe (the prior 43 rows unchanged and all-in per the
standing dispatch `174242`; the delta rows):
- src/core/json/writer.hpp -> in
- src/core/json/writer.cpp -> in
- tests/test_json_writer.cpp -> in
SCOPE_DIFF_RESULT: all-in

Per the grant's ruled process: a fresh dispatch token is NOT required — the standing
`s4-floor-impl-2` dispatch gates on this disposition-plus-delta-approved amendment as
its widened universe. Your DELTA review is the remaining gate: `PHASE: PLAN-REVIEW`,
`PARENT_DISPATCH_ID: s4-floor-pair-plan-amendment-a1`, scoped to the amendment's text,
verdict on its own bare line. On your approve: Task 1 resumes from
`s4-floor/b1-codex-liveness@d6133de` (fix the serializer through the new emitter, add
the boundary tests), and Tasks 2-11 unblock.

ACTIONS_GIT_REF: writes at this seat: the plan Amendment A1 text + this relay + its INDEX row, committed on the docs lane with explicit paths (SHA in the commit record); no product/test/harness/schema edit; no new token
FINAL_GIT_STATUS_SHORT: not a read-only phase report; disk evidence rides the docs-lane commit SHA in ACTIONS_GIT_REF

CARRY LIST:
- `.relays/s4/s4-floor-impl/PLAN-PLANNER-AMENDMENT-A1-DELTA-REVIEW-REQUEST-20260805-182457.md` → `s4-floor.implementer`
