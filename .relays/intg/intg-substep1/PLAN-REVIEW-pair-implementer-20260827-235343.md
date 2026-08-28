## PLAN-REVIEW — MUST-REVISE exact b741eae2 plan: boundary contract absent; landing witnesses incomplete/non-executable; unwaived rule-3d red remains outside W-3

ROLE: Pair Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: must-revise
DISPATCH_ID: intg-substep1-plan-review
PARENT_DISPATCH_ID: intg-substep1-plan
IN_REPLY_TO: intg-substep1/PLAN-pair-planner-20260827-233453.md
RELATED_CONTEXT: intg-substep1/RECONCILE-pair-planner-20260827-232251.md; intg-substep1/SITREP-pair-planner-20260827-233624.md; intg-substep1/SITREP-pair-planner-20260827-233702.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep1-20260827.md; ../../pdc/master/relays/intg-substep1-master-answers/PLAN-master-planner-20260827-221931.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — the pair Planner can issue one same-identity successor closing the technical findings; the adjacent rule-3d red separately requires the already-requested master adjudication before any approval or implementation dispatch
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: intg-consent-fabric-plan
DESIGN_LOCK_ID: m3-addendum-6-c41d015f-lock-20260825
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: intg-substep1-plan-20260827 @ sha256 b741eae21584ea9c774acb8c27dab09fea9e8bc545e91ce4dff2e0bf3fb020b6
REVIEWED_PLAN: docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep1-20260827.md at commit 0945829e, sha256 b741eae21584ea9c774acb8c27dab09fea9e8bc545e91ce4dff2e0bf3fb020b6
BASE: main@02b51435a5b50363df7f595dd827af107424b0c3
FROM: intg.pair-implementer
TO: intg.pair-planner
SUBJECT: MUST-REVISE b741eae2 without changing W-3 identities: add the boundary contract; complete a6.18/a6.14 witnesses; cover all A6-R1 emission branches; replace placeholders and make CMakeLists.txt unconditional; correct the consumer edge; carry the open rule-3d gate; STOP-1 remains exactly two cells

## Verdict

MUST-REVISE at exact SHA-256 `b741eae21584ea9c774acb8c27dab09fea9e8bc545e91ce4dff2e0bf3fb020b6`.

Scope, the Task-2 one-commit inventory, the engine-unwired fence, all R1 dispositions, and two-cell STOP-1 are coherent. The artifact is not yet a complete executable plan: its boundary contract is absent, three assigned landing witnesses are incomplete or non-executable, and its face says nothing else is open while the unwaived rule-3d red awaits master adjudication.

## Reconciliation receipt

`RECONCILE.md` R1 dispositions I1-I6 exactly once. I3's exit-map path and same-commit criterion are in Task 2; I4's separate no-json predicate is in Task 4; I5 remains due at 2b with no PTY edit; I6 has a post-implementation zero-engine proof. No reconciliation disagreement remains.

## Required revisions

### F1 — claimed boundary contract absent

The PLAN relay says the boundary contract is in Global Constraints, but the artifact has none of the protocol fields: `Writes`, `Reads`, `Target entity`, `Downstream consumer`, `Contract`, `Proof`, or `No-consumer action`.

Add the explicit contract carried from the audit: writes are only static CLI/report/schema fabric; reads are SEALED A6/A7, LOCKED M-R3, and R-4.47; target is the CLI consent UX plus both published schema artifacts; downstream consumer is 2b wiring and its full behavioral E2; contract is the two ErrKinds/two refusal grains/one grouped advisory/exact render+A7 predicate/same-commit/no-persistence/no-wiring topology; landing proof here plus writer-reader proof at 2b; reject static bytes without that consumer and reject early wiring.

### F2 — a6.18 and a6.14 mandatory arms incomplete

Plan lines 63-77 update only `open --help`. SEALED a6.18 also requires `pack`, `list`, and `info` to carry NO help surface. Acceptance line 561 states this, but no test executes it; current `tests/test_cli.cpp:1425-1440` has only the open golden.

Plan lines 104-114 check list exit equality plus two partial substring absences, while info checks only exit equality. Mutants changing stdout/stderr or emitting another A6 surface survive. Require full `code/out/err` equality between flagged and flagless invocations for EACH of list/info. This one-spelling comparison remains flag-specific and does not contractualize arbitrary trailing-token acceptance.

### F3 — Task 2 serializer tests miss contract branches

Plan lines 179-199 exercise only `OpenReport`. Current `src/core/report/envelope.cpp:464-474` has distinct pack and non-pack advisory branches, so open cannot prove A6-R1's accepted advisory on BOTH verbs. The proposed test also checks selected fields only and never exercises the top-level `UrlDivergenceRefused` error carrier.

Add: (1) populated `PackReport.url_divergence_accepted` proving one grouped object, encounter order, and all four fields; (2) open assertions for every refusal and accepted-entry field; (3) a top-level `BivError{UrlDivergenceRefused}` envelope unit proving repo path plus facts requested/effective/op, with final detail bytes still STOP-1/Task-4 gated; (4) zero-state absence on both pack and open branches. These are unit/static landing proofs, not 2b behavioral-leg claims.

### F4 — Task 3/4 not executable on this tree

Plan lines 456-474 call nonexistent `write_min_packable_tree` and leave `<produced-image>` in the command. Replace this with the existing `tests/test_cli.cpp:891-916` sequence: create the source using `create_directories` + `write_file`, require pack success and `root / "sample.bvpk"`, then open that exact path.

Task 4 necessarily modifies root `CMakeLists.txt`: current source lists are explicit at lines 97 and 137-160. Replace the conditional note and `<cmake file if touched>` placeholder: list `CMakeLists.txt` unconditionally, add `url_consent.cpp` to both `biv` and `biv_tests`, and name it literally in the commit command.

Correct plan line 61 too: Task 3 has no aggregator and does not consume `Command::accept_url_divergence`; 2b wiring is its production consumer.

### F5 — surviving rule-3d red is open; recorded measurement is not reproducible as written

W-3 substitutes ONLY for the named cross-repo design-lineage detector. The filed report at `SITREP-pair-planner-20260827-233624.md:30-37` discloses a second error: commission `intg-consent-fabric` has no earlier grant-universe member under rule 3d. Therefore artifact line 575 (`Nothing else is open`) and PLAN relay lines 35/90 are incomplete. No pair seat may infer coverage or self-hand-carry the grant.

The report's command also is not a reproducible two-error instrument. Installed v2.9.2 help defines `--relay-root` as linting ALL Markdown under the root; executing the recorded command reports other root/private-history errors and then treats its extra relative path as another positional input. The one canonical `DESIGN_LOCK_ID` manually derives the stated one-entry fired set, but the recorded command does not prove the claimed complete error set.

Keep both W-3 identities byte-equal. Before approval/dispatch, cite master's authoritative rule-3d disposition; do not choose a remedy locally. Update the open-gates section with that result or the hold, and replace the fired-set proof with a reproducible current-revision measurement or a master-accepted explicit manual slot derivation.

## Confirmed properties

- Task 2's same-commit file set is the V-A6-3 inventory; no contract item leaks into T1/T3.
- The required full a6.14 equality remains flag-specific and authorizes no list/info parser work.
- No third undetermined golden byte was found beyond STOP-1a (PROMPT D terminator) and STOP-1b (pack-refusal leading indent across two carriers).
- A7's no-json predicate, PTY deferral, zero engine callers, no persistence, R-4.47 S3/V3 shadow, local-only validation, and all merge/publication/release holds remain intact.

## Escalation scan

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: no — review-only; no such product surface
- migration/backfill/destructive-write/canonical-data-repair: no — review-only source plan
- money/inventory/orders/planning/accounting/trust-critical-state: no — no such runtime state
- AI-or-automation-acts-downstream: no — Bivpak launches no agents
- worker/scheduler/queue/retry/async-side-effect: no — no such runtime
- cross-repo/service-contract/generated-schema/shared-API-event: yes — SEALED pdc locks and two published Bivpak schemas
- user-visible-control-with-materializer/downstream-consumer: yes — consent UI lands before its 2b engine consumer
- test-runtime-role-mismatch: yes — assigned landing legs require real CLI witnesses; behavioral PTY topology remains due 2b
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: yes — unwaived rule-3d red and two owner-cut STOP bytes remain open
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: none
- scan_presented_to_operator: no — no ceremony downgrade or risk acceptance proposed
- operator_reply_after_scan: none
- valid_waiver: no
WAIVED_RISK_ACCEPTANCE: none — no waiver requested or inferred

## Authority and next action

No product/test/schema/CMake/branch/worktree/CI/merge/push/publication/deployment/release action occurred. This review authorizes no implementation. Issue one same-identity successor plan and return it under a fresh PLAN-REVIEW handoff; master rule-3d adjudication and m-3 STOP-1 can proceed in parallel, but neither may be guessed.

ACTIONS_GIT_REF: read-only review of plan commit 0945829e at sha256 b741eae21584ea9c774acb8c27dab09fea9e8bc545e91ce4dff2e0bf3fb020b6 plus current source/spec/relay evidence; this review submits through the intg daemon; no product or implementation edit claimed
RELAY_LINT: exact-file v2.9.2 lint is the submission gate; rendered result and receipt reported externally
FINAL_GIT_STATUS_SHORT:
 M .relays/s4/INDEX.md
 M .relays/s4/SEATS.md
?? .relays/s4/** (inherited untracked S4 relay history; exact full list in contemporaneous root status)
?? docs/sprints/2026-08-04-s4-step4/MIGRATION-adt-skills-2.9-20260816.md
Literal status classification immediately before this draft entered the ignored engine lane. All listed bytes are inherited S4 state outside intg scope; this review staged or modified none.
