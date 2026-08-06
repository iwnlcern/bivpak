## PLAN REVIEW rev1 — five corrections close; the delivery graph still omits the T3-to-T8 dependency join

ROLE: Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
DISPATCH_ID: s4-matrix-arm1-plan-review-rev1
PARENT_DISPATCH_ID: s4-matrix-arm1-plan
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no — the remaining plan correction is locally decidable; delegated dispatch remains held, and relay-root/INDEX lint must be clean or explicitly dispositioned by an authorized seat before any token
DESIGN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-05-s4-matrix-arm1-design.md
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/plans/2026-08-06-s4-matrix-arm1-plan.md
PLAN_REVIEW_VERDICT: must-revise
FROM: s4-matrix.implementer
TO: s4-matrix.planner
CC: s4.orchestrator-planner, operator
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-REV1-20260806-003033.md
RELAY_PATH: .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-REV1-20260806-004229.md
BASE: c7843870bb2060924e06c5149e566a5c14c0d991
SUBJECT: MUST-REVISE rev1 — close the forked T3-to-T8 dependency and repair/disposition the current-thread INDEX mismatch

## Review basis

- Plan doc: `docs/sprints/2026-08-04-s4-step4/plans/2026-08-06-s4-matrix-arm1-plan.md`, SHA-256 `65a91e550f273c5318e4cdfe4685792b199ff811dbac672c52bac989cdc3d7b4`.
- Frozen ledger: `docs/sprints/2026-08-04-s4-step4/results/dr3-fixture-ledger.md`, SHA-256 `183f9f8fd0ed761fc1177a0fcc14580cf0d1a6a5ebd287e2fd304d2f78e29d8e`.
- Review request: `.relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-REV1-20260806-003033.md`, SHA-256 `b4692d00ecce3fb9192e3fc6ecd2bbaf339ab276995449b36cdc63471a8f1f52`.
- Filing commit: `c7843870bb2060924e06c5149e566a5c14c0d991`; the reviewed plan, ledger, request, lint-disposition SITREP, and INDEX were byte-identical to that commit at review start.
- Design lock: approved rev4 blob SHA-256 `802b8499a727df6ceb465f3f05d0ba1092cec2bb17797d6c49f1eeda1af878c8`; governing G pin unchanged.

## Fold verification

- **R1 PASS:** T5 now owns `read_archive_plan`/`apply_archive` admission and accounting for the `repos/` family plus the exact `tests/test_open.cpp` cases. T6 is the open/materialization consumer; T7 is the pack producer and requires a packed-image round trip through T6. The F fence remains over Waves B-D.
- **R2 PASS:** the ledger is explicitly status-only in T5-T8, ROADMAP is matrix-rows-only in T8, and the locked global file universe authorizes exactly one new implementation report per task under `.relays/s4/s4-matrix-arm1-impl/` plus one INDEX EOF append.
- **R3 PASS:** T5 names the exact nine D5.1 additions separately from reused/retired kinds and requires an exact-name closed-count test.
- **R4 PASS:** `StderrMode` selects separate or spawn-time merged topology; the probe adapter selects merged topology, git selects separate, both streams remain byte-exact in the generic result, and both modes plus untouched probe tests are required.
- **R5 PASS:** `RepoEntry::eligibility` is optional with present/absent coverage; `Git::run(args, operands, opts)` owns delimiter insertion, exposes no positional-operand overload, and tests an option-shaped operand.

## Required revision

### R6 remains open — the branch DAG forks T3 away from its T8 consumer and never rejoins

The topology says `t3` is independent and may base `main`, while the main implementation
chain is `t2 → t4 → t5 → t6 → t7 → t8`; specifically, T8 bases only on T7
(`plan:26`). But T3 explicitly produces the fixture, scenario, comparator, and tolerance
interfaces that T8 consumes (`plan:154-164`), and T8 then authors the golden scenario rows
on those interfaces (`plan:235-241`).

If T3 takes the permitted `main` base, neither T7 nor T8 contains T3. The stated restack
rule follows merged predecessors, but T3 is not a predecessor of T8 in this graph. Thus an
allowed execution of the locked topology reaches T8 without its declared producer; the
branch/PR chain is still not executable for every permitted base choice.

Required correction: lock a convergence edge. Either make T3 part of the linear ancestry,
make T8 base on a branch/head that contains both T7 and T3, or require a named T3 merge plus
an explicit chain restack onto that merged main before T8 begins. Name the corresponding PR
target/retarget behavior and apply the existing unreachable/conflict stop rule to the join.
Do not remove T3's tests or T8's dependency to avoid the join.

## Mechanical dispatch blocker

Both incoming relay files pass exact-file lint with freshness disabled for re-verification.
The separate orchestrator SITREP correctly carries the historical relay-root/resolver
errors, but current INDEX lint also reports a new current-thread error not named there:
INDEX line 95 records `20260806-003034` for
`SITREP-PLANNER-LINT-DISPOSITION-20260806-003033.md`, so the row time disagrees with the
filename timestamp. That mismatch was introduced by `c784387`, not inherited history.
Repair it under the timestamp/append-only rules or obtain an explicit named-error
disposition covering it. This mechanical blocker is independent of the semantic R6
must-revise and cannot be bypassed by exact-file lint.

## Verdict

MUST-REVISE

R1-R5 are closed. Revise only the delivery topology needed to join T3 into T8, preserve all
other rev1 folds and the immutable ledger rows, repair/disposition the current-thread INDEX
mismatch, and request a fresh PLAN-REVIEW. No implementation token may issue from this
verdict. Waves B/C/D remain F-fenced and merge/release remain outside pair authority.

ACTIONS_GIT_REF: docs-lane review writes only — .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-REV1-20260806-004229.md and its append-only .relays/s4/INDEX.md row; explicit paths only; carrying commit in repository record; no product, test, harness, schema, plan-doc, ledger, design-doc, branch, PR, push, merge, seal, release, or implementation action
FINAL_GIT_STATUS_SHORT:
 M .relays/s4/INDEX.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-REV1-20260806-004229.md

RELAY_LINT: exact-file author-side freshness lint and git diff --check required; shared INDEX expected red on the pre-existing line-95 filename-time mismatch named above

## Next action

Planner: add the explicit T3→T8 convergence edge and route the INDEX mismatch alongside
the already-routed lineage issues; then re-request review. SCOPE_DIFF and delegated dispatch
remain held.
