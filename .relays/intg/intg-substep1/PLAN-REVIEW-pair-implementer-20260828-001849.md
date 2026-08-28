## PLAN-REVIEW — MUST-REVISE exact 53037fa5 successor 2: executable mutants survive; build instructions contradict the tree; carrier identity/evidence text is stale

ROLE: Pair Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: must-revise
DISPATCH_ID: intg-substep1-plan-review
PARENT_DISPATCH_ID: intg-substep1-plan
IN_REPLY_TO: intg-substep1/PLAN-pair-planner-20260828-001327.md
RELATED_CONTEXT: intg-substep1/PLAN-REVIEW-pair-implementer-20260827-235343.md; intg-substep1/SITREP-pair-planner-20260828-001427.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep1-20260827.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/results/lint-root-sweep-successor2-20260828.txt
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — the pair Planner can issue one same-identity successor closing the executable-plan findings; STOP-1 is owner-resolved; the master-owned rule-3a residue remains an independent prerequisite to approval/dispatch
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: intg-consent-fabric-plan
DESIGN_LOCK_ID: m3-addendum-6-c41d015f-lock-20260825
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: intg-substep1-plan-20260827 @ sha256 53037fa5f29ca8481de4288fbaad93ba0533e1028fa42b2ab25caad96a4d04b9
REVIEWED_PLAN: docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep1-20260827.md at commit ff7dfd3c, sha256 53037fa5f29ca8481de4288fbaad93ba0533e1028fa42b2ab25caad96a4d04b9
BASE: main@02b51435a5b50363df7f595dd827af107424b0c3
FROM: intg.pair-implementer
TO: intg.pair-planner
SUBJECT: MUST-REVISE 53037fa5 without changing W-3 identities: close the remaining no-help, carrier, build-command, prompt-wrapper, and successor-identity/evidence gaps; master rule-3a remains held

## Verdict

MUST-REVISE at exact SHA-256 `53037fa5f29ca8481de4288fbaad93ba0533e1028fa42b2ab25caad96a4d04b9`.

The boundary contract, full list/info equality, concrete Task-3 fixture, literal Task-4 CMake edits, owner-resolved STOP-1 bytes, and honest rule-3a row are materially improved. The artifact still lacks executable proof for all acceptance claims and carries stale predecessor identity text.

## Required revisions

### F1 — a6.18 no-help witness still admits help surfaces

Plan lines 150-160 check `usage: biv open` only on stdout and the new flag spelling on stdout/stderr. A mutant emitting `usage: biv pack ...` or another help block on stderr passes. SEALED A6 lines 641-646, 681-684, and 801-805 require pack/list/info to carry NO help surface, witnessed rather than assumed.

Assert the existing non-help behavior on BOTH streams for each verb, preferably exact `code/out/err` baselines (`pack --help` is UsageError/unknown-flag; list/info are ordinary NotYetImplemented), or an equivalently complete assertion rejecting any help production. Keep this distinct from a6.14's flagged-versus-flagless equality.

### F2 — A6-R1 carrier tests do not prove the acceptance claim

Plan lines 227-280 use global substring searches. On open, accepted-entry `op` may be omitted and the refusal row's identical value still satisfies the check. On pack, the second entry's requested/effective/op are never asserted. Refusal rows share `op`, are not parsed as rows, and neither array's exact cardinality/entry shape is checked. These mutants survive while acceptance line 677 claims all fields, encounter order, one outer object, and a complete refusal-row field set.

Parse the JSON and compare exact arrays/objects (or use equally row-bound assertions) with distinct values for every field in every row. Prove exact cardinality, order, all fields per entry, and the single grouped advisory independently on BOTH verb branches. Retain the top-level error-carrier and both zero-state tests.

### F3 — build and TDD commands remain contradictory/non-executable

Plan lines 79-82 still offer `tests/test_url_consent.cpp` conditionally and refer to nonexistent `tests/CMakeLists.txt`, despite line 594 correctly naming unconditional root `CMakeLists.txt` edits. Root `CMakeLists.txt:97,137-158` enumerates both source lists. Remove the conditional path and list root `CMakeLists.txt` in the file inventory.

Plan line 168's `ctest --test-dir build -R cli` selects zero tests here (`ctest --test-dir build/dev -N -R cli` reports `Total Tests: 0`). Name executable commands against the real `biv_tests` target and/or Catch2 specifications for each task; replace “or equivalent” and bare PASS instructions with literal invocations.

### F4 — prompt wrapper contract has no witness

Lines 596-604 declare that `prompt_url_divergence` renders PROMPT D to stderr, accepts lowercase or uppercase Y, and refuses empty/EOF/stream failure. Lines 634-641 assert only return values for empty/lowercase-y/lowercase-n and never inspect stderr. A wrapper emitting nothing or drifted bytes, rejecting uppercase Y, or proceeding on EOF passes.

Bind `err.str()` byte-whole to `render_prompt_d(facts)` and cover uppercase Y plus EOF/failed input. This is a static module landing proof, not a 2b behavioral-leg claim. Add an explicit source/fence proof that A7-R1 contains exactly stdin+stderr `isatty` and no json/env/config term, because acceptance line 679 claims that predicate.

### F5 — successor-2 carrier and artifact retain stale predecessor text

The relay header pins `53037fa5`, but its bound-plan paragraph still says the annotation digest is `fa197652`; its SUBJECT still calls Task 4 BLOCKED although STOP-1 is folded. In the artifact, boundary-contract line 50 still says STOP-1 is pending even though lines 17 and 590-650 resolve it. Normalize every carrier/contract occurrence to successor-2 state.

Open-gates line 691 says each successor re-measures but does not cite this revision's actual archive, `results/lint-root-sweep-successor2-20260828.txt`, which the accompanying SITREP names. Cite it in the governing artifact and fix review ask 5's reference to nonexistent `PLAN_SHA256` (integrity is carried in the annotated `PLAN_LOCK_ID`). The archive shows the W-3-covered design-lineage entry plus the outside-W-3 rule-3a residue. Preserve both W-3 identities; no approval or implementation dispatch issues until master disposes rule 3a.

## Confirmed properties

- The boundary contract now carries Writes/Reads/target/consumer/contract/proof/no-consumer action.
- a6.14 compares full code/out/err for list and info without generalizing arbitrary tokens.
- Both serializer branches, the top-level refusal carrier, and both zero states are present; the remaining defect is assertion completeness.
- Task 3 uses a real round trip; Task 4 names both exact CMake edits and the unwired consumer boundary.
- STOP-1's two cells match m-3 ruling `235912`: prompt terminal space/no newline; refusal template unindented and embedded by standard typed-error rendering. No third cell exists.
- Rule-3a is disclosed outside W-3; engine wiring, merge, push, publication, deployment, and release remain held.

## Escalation scan

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: no — review-only
- migration/backfill/destructive-write/canonical-data-repair: no — review-only
- money/inventory/orders/planning/accounting/trust-critical-state: no — no such runtime state
- AI-or-automation-acts-downstream: no — Bivpak launches no agents
- worker/scheduler/queue/retry/async-side-effect: no — no such runtime
- cross-repo/service-contract/generated-schema/shared-API-event: yes — SEALED pdc locks and two published schemas
- user-visible-control-with-materializer/downstream-consumer: yes — consent UI precedes its 2b consumer
- test-runtime-role-mismatch: yes — surviving mutants and a zero-test command
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

No product/test/schema/CMake/worktree/branch/CI/merge/push/publication/deployment/release action occurred. This review authorizes no implementation. Issue one same-identity successor closing F1-F5; STOP-1 is closed, while master rule-3a adjudication proceeds independently and may not be inferred.

ACTIONS_GIT_REF: read-only review of plan commit ff7dfd3c at sha256 53037fa5f29ca8481de4288fbaad93ba0533e1028fa42b2ab25caad96a4d04b9 plus current source/spec/relay evidence; review submits through the intg daemon; no product or implementation edit claimed
RELAY_LINT: exact-file v2.9.2 lint is the submission gate; rendered result and receipt reported externally
FINAL_GIT_STATUS_SHORT:
 M .relays/s4/INDEX.md
 M .relays/s4/SEATS.md
 ?? .relays/s4/** (inherited untracked S4 relay history; exact full list in contemporaneous root status)
 ?? docs/sprints/2026-08-04-s4-step4/MIGRATION-adt-skills-2.9-20260816.md
Literal status classification before this draft entered the ignored engine lane. All listed bytes are inherited S4 state outside intg scope; this review modified none.
