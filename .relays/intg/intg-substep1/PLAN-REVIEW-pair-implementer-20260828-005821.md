## PLAN-REVIEW — MUST-REVISE exact ac4d4322 successor 4: content folds close; three execution-proof gaps remain

ROLE: Pair Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: must-revise
DISPATCH_ID: intg-substep1-plan-review-4
PARENT_DISPATCH_ID: intg-substep1-plan
IN_REPLY_TO: intg-substep1/PLAN-pair-planner-20260828-005011.md
RELATED_CONTEXT: intg-substep1/PLAN-REVIEW-pair-implementer-20260828-004524.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep1-20260827.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/results/lint-root-sweep-successor4-20260828.txt; ../../pdc/master/domains/m-3-restore-cli/design/2026-08-26-addendum-7-consent-interaction-companion.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — the pair Planner can issue one same-identity successor closing three command/proof gaps; the master-owned rule-3a clearing sweep remains an independent prerequisite to any approval-consuming dispatch
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: intg-consent-fabric-plan
DESIGN_LOCK_ID: m3-addendum-6-c41d015f-lock-20260825
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: intg-substep1-plan-20260827 @ sha256 ac4d432271ed91514e3989d99eccbcb3f05d1f8416cb80f25623e3ce92079e73
REVIEWED_PLAN: docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep1-20260827.md at commit 35d1219, sha256 ac4d432271ed91514e3989d99eccbcb3f05d1f8416cb80f25623e3ce92079e73
BASE: main@02b51435a5b50363df7f595dd827af107424b0c3
FROM: intg.pair-implementer
TO: intg.pair-planner
SUBJECT: MUST-REVISE ac4d4322 without changing W-3 identities: make the tagged run print the promised passing names and make Task-1 RED legs independently observable; witness the sealed BOTH-stream conjunction rather than only its calls; make the zero-engine diff an exit gate

## Verdict

MUST-REVISE at exact SHA-256 `ac4d432271ed91514e3989d99eccbcb3f05d1f8416cb80f25623e3ce92079e73`.

The prior content defects are closed: F1 pins exact no-help baselines; all twelve new Catch2 cases carry `[a6-fabric]`; failed input and byte-whole stderr are covered; the isatty count is exit-gated; successor-3 and successor-4 sweeps are named; the `001956` adjudication/hold is current. F2 remains closed. Three execution-proof gaps remain.

## Required revisions

### F3 — the literal tag run cannot supply its promised name-by-name proof, and Task 1 short-circuits its RED witnesses

Every PASS command invokes `./build/dev/biv_tests "[a6-fabric]"` with default Catch2 reporting, while the plan requires the IMPL report to list the executed new names from that output. Pinned Catch2 v3.7.1 documents `-s/--success` as the switch that reports successful results (`build/dev/_deps/catch2-src/docs/command-line.md:240-245`); reporters usually omit successful assertions without it (`docs/reporters.md:163-167`). The literal passing command therefore proves the tag aggregate/count, not the promised twelve names.

Add an evidence-producing invocation such as the tag run with `--success` (or an equivalent machine reporter) and require the report to retain its name/count output. A separate `--list-tests` can prove selection but does not alone prove execution.

Task-1 line 190 also chains build, the expected-failing tag run, and the expected-failing pre-existing help golden with `&&`. Step-1 tests reference the not-yet-existing `Command::accept_url_divergence`, so the build can fail first; even after a minimal declaration lets it compile, the expected tag failure prevents the help-golden command from running. Sequence the RED checks independently and record both intended failures before the behavior edit. Do not use a short-circuit chain to claim both ran.

### F4 — the source fence does not prove A7-R1's required AND semantics

Plan lines 731-734 prove two `isatty` occurrences and the two descriptor spellings, but a mutant changing the implementation from `stdin && stderr` to `stdin || stderr` passes every grep. SEALED A7-R1 lines 59-62 require BOTH streams to be TTYs and make EITHER redirected stream non-interactive.

Add an exact source witness for the required conjunction (for example a fixed-string grep of `::isatty(STDIN_FILENO) != 0 && ::isatty(STDERR_FILENO) != 0`) or a unit seam that exercises both one-stream-false states. Retain the count and no-stdout/json/env/config checks.

### F6 — the zero-engine fence prints a count but cannot fail

Task-5 line 736 pipes the engine diff to `wc -l` and comments "must be 0". `wc` exits zero for a nonzero count, so an engine edit does not fail this command. Make the predicate exit-gated, for example by testing that `git diff --name-only 02b51435..HEAD -- src/core/repo` is empty. Paste the evaluated command and result into the IMPL report as already required.

## Confirmed properties

- Exact no-help baselines now kill the shared-baseline help mutant.
- The twelve new Catch2 cases are tagged correctly; comma-splitting is removed.
- Failed input, EOF, uppercase Y, and stderr byte equality are present.
- F2 row-bound serializers, Task-2 one-commit inventory, and R1 dispositions remain intact.
- Current carrier/artifact/sweep names and the master rule-3a hold are accurate.
- Engine wiring, merge, push, publication, deployment, and release remain held.

## Escalation scan

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: no — review-only
- migration/backfill/destructive-write/canonical-data-repair: no — review-only
- money/inventory/orders/planning/accounting/trust-critical-state: no — no such runtime state
- AI-or-automation-acts-downstream: no — Bivpak launches no agents
- worker/scheduler/queue/retry/async-side-effect: no — no such runtime
- cross-repo/service-contract/generated-schema/shared-API-event: yes — SEALED pdc locks and published schemas
- user-visible-control-with-materializer/downstream-consumer: yes — consent UI precedes its 2b consumer
- test-runtime-role-mismatch: yes — short-circuited RED evidence and non-observable passing names
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: yes — outside-W-3 rule-3a residue remains open
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: none
- scan_presented_to_operator: no — no downgrade or risk acceptance proposed
- operator_reply_after_scan: none
- valid_waiver: no
WAIVED_RISK_ACCEPTANCE: none — no waiver requested or inferred

## Authority and next action

No product/test/schema/CMake/worktree/branch/CI/merge/push/publication/deployment/release action occurred. This review authorizes no implementation. Issue one same-identity successor closing F3/F4/F6; F1/F2/F5 are closed. Master rule-3a repair/clearing proceeds independently and may not be inferred.

ACTIONS_GIT_REF: read-only review of plan commit 35d1219 at sha256 ac4d432271ed91514e3989d99eccbcb3f05d1f8416cb80f25623e3ce92079e73 plus current source, pinned Catch2 reporting grammar, SEALED A7-R1, and successor-4 archived-sweep evidence; review submits through the intg daemon; no product or implementation edit claimed
RELAY_LINT: exact-file v2.9.2 lint is the submission gate; rendered result and receipt reported externally
FINAL_GIT_STATUS_SHORT:
 M .relays/s4/INDEX.md
 M .relays/s4/SEATS.md
 ?? .relays/s4/** (inherited untracked S4 relay history; full literal root status captured immediately before drafting)
 ?? docs/sprints/2026-08-04-s4-step4/MIGRATION-adt-skills-2.9-20260816.md
All listed bytes are inherited S4 state outside intg scope; this review modified none.
