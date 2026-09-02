## PLAN-REVIEW artifact — MUST-REVISE revision 9 at 16069a69: two normative test paragraphs retain rev8's impossible post-build call claim and stale five-row UnknownNote population

ROLE: Pair Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: must-revise
DISPATCH_ID: intg-substep2a-plan-review-9
PARENT_DISPATCH_ID: intg-substep2a-plan
IN_REPLY_TO: intg-substep2a/PLAN-pair-planner-20260902-052432.md
RELATED_CONTEXT: docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep2a-20260830.md; intg-substep2a/PLAN-REVIEW-pair-implementer-20260902-052008.md; ../../pdc/master/relays/intg-substep2a-format-act/DESIGN-planner-20260902-034802.md; ../../pdc/master/domains/m-1-format-engine/design/2026-09-01-ADDENDUM-O-writer-validity-contract.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new operator gate — the semantic correction is present; this finding removes two stale contradictory execution sentences inside the same locked O-R1/O-R4 behavior; exact-hash re-review, W-5 concurrence/effectiveness, implementation, byte reviews, merge, push, publication, deployment, and release remain separately gated
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: intg-format-act-plan
DESIGN_LOCK_ID: m1-addendum-O-63c46631-lock-20260901
DESIGN_RECORD_KIND: design-doc
LOCKED_DESIGN_SHA256: 63c46631c84ce27ebedbf71c4965e6b0b149919a83118835d78ce29e89d3e577
LOCKED_DESIGN_COMMIT: 40b4f7a3dbfc60e5ab742678bc4e77198845c243
POST_STAMP_SHA256: 0e990bac752986942d9091871a5175820b829dd019d586e8e895461cfff656d2
SECOND_CONSUMED_LOCK: m1-addendum-N-82293732-lock-20260827
THIRD_CONSUMED_LOCK: m1-addendum-M-2966b839-lock-20260825
PLAN_LOCK_ID: intg-substep2a-plan-20260830 @ sha256 16069a69b13a0bd9abb6b46b0a21d1ab49b2d64eadbdee9ca2e64562b80fdb06
REVIEWED_PLAN: docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep2a-20260830.md at commit 9ee2252, sha256 16069a69b13a0bd9abb6b46b0a21d1ab49b2d64eadbdee9ca2e64562b80fdb06
BASE: main@46df8f3c35981a4ae3f77cf3293a4b7212b4b996; review filed from main@9ee2252
BRANCH: intg/format-act at retained HEAD 9e6ebe8fca2454164051573323dd7adfa2901219; index clean; uncommitted tranche-1 diff remains exactly 72fd3dc604957e14e944b9f7418a64f723125d8b138909e8e0bd5b045e4b22cf over src/core/manifest/manifest.cpp and tests/test_manifest.cpp; no product byte or ref changed by this review
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: master.master-planner, master.master-reviewer, m-1.planner, m-1.implementer, m-3.planner, m-3.implementer
SUBJECT: MUST-REVISE exact 16069a69 — align the leg-(e) asymmetry explanation and raw-byte control sentence with rev9's pre-build enforcement carve and seven-row UnknownNote inventory

## Verdict

MUST-REVISE at exact SHA-256 `16069a69b13a0bd9abb6b46b0a21d1ab49b2d64eadbdee9ca2e64562b80fdb06`.

Revision 9 folds both `052008` findings in its contract, procedure, helper-path paragraph, implementation step, coverage census, and acceptance criterion: JSON validity, single-value consumption, and object type are separate table-A rows with discriminating arms; the five raw-note shape rows are parser-enforced pre-build while `repo_row_violation(RepoRowFacts)` consumes only predicates observable on a constructed row. Two mandatory-test paragraphs were not updated and now contradict that correction. This is a narrow consistency finding, not a new semantic or structural design request.

This is review-only. It authorizes no product, test, plan, branch, tag, index, ref, merge, push, publication, deployment, or release action.

## Finding

### F1 — Major — stale leg-(e) and control prose contradict the corrected enforcement location and inventory population

At exact plan line 250, the asymmetry-mutant explanation still says every table-A writer clause has a parser rejection twin “because both points call `repo_row_violation` on the same table.” Rev9 elsewhere correctly establishes that the seven O-R2 paths and five raw-note shape rows are parser-enforced pre-build and cannot be observed by that post-build function. The rejection twin remains true; the stated reason is false and reinstates the impossible structure F2 was meant to remove.

At exact plan line 251, the positive `unknown-note-roundtrip` control is still described as covering “the five UnknownNote refusal rows above (three table-A shape rows, two table-B image exclusions).” The same line now enumerates seven refusal rows: five table-A shapes (`json-valid`, `single-value`, `object`, `kind-present`, `kind-string`) plus two table-B image exclusions (`kind`, `aliases-structured`). The stale sentence conflicts with the explicit arms, the Step-0-derived equality, the coverage census, and acceptance criterion 4.

Required correction: in leg (e), retain the one-inventory/asymmetry claim but ground each table-A parser twin at its actual enforcement site — post-build `repo_row_violation` where observable, otherwise the existing pre-build helper/raw-parse site. In the raw-byte control sentence, replace the stale five/three population with the rev9 population (seven total: five A + two B), or avoid a fixed total and enumerate the same rows unambiguously. Re-scan the normative test/acceptance prose for the dead rev8 population and post-build-consumption wording. No code, parser byte, design ruling, test surface, or new arm is requested.

## Verified folds and unaffected surfaces

- Incoming carrier hashes to `fffd9cdf2d920148927bcf7d32fe5a1b59af88c21fc092f06cb1eac8a0544266`; the reviewed plan hashes to `16069a69b13a0bd9abb6b46b0a21d1ab49b2d64eadbdee9ca2e64562b80fdb06` at `9ee2252`.
- Sealed O re-verifies: live post-stamp `0e990bac752986942d9091871a5175820b829dd019d586e8e895461cfff656d2`; blob at `40b4f7a3dbfc60e5ab742678bc4e77198845c243` = locked `63c46631c84ce27ebedbf71c4965e6b0b149919a83118835d78ce29e89d3e577`.
- Retained tranche 1 is unchanged: HEAD `9e6ebe8fca2454164051573323dd7adfa2901219`, index empty, exactly two tracked modified files, diff `72fd3dc604957e14e944b9f7418a64f723125d8b138909e8e0bd5b045e4b22cf`.
- Rev9 F1 is substantively folded: the three raw JSON/object predicates and their distinct negative arms are present; A/B populations derive from Step 0.
- Rev9 F2 is substantively folded: the helper-path paragraph, Step 3, census, and acceptance criterion correctly distinguish post-build and pre-build parser enforcement.
- Repo-id uniqueness remains absent; parser acceptance/detail strings, C-2/C-3/C-4, the ten-path allowlist, staged-tree proofs, both-platform battery, W-5 gates, and the release hold otherwise carry without a finding.
- Exact-file lint for the incoming relay is clean; the daemon ledger verifies; the rev9 W-5 report hashes to `b25ef320515f3b2cd245a5ed24cffdefc93b504fd2b8bfd172c79f1e531718ad` and records the one expected O design-lineage fired entry without implementation authority.

## Escalation scan

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: no — review-only
- migration/backfill/destructive-write/canonical-data-repair: no — no product or canonical-data write
- money/inventory/orders/planning/accounting/trust-critical-state: no
- AI-or-automation-acts-downstream: no
- worker/scheduler/queue/retry/async-side-effect: no
- cross-repo/service-contract/generated-schema/shared-API-event: yes — locked PDC O and m-1's unchanged-parser-acceptance ruling govern
- user-visible-control-with-materializer/downstream-consumer: yes — archive bytes and parser/writer symmetry are user-visible
- test-runtime-role-mismatch: yes — two mandatory-test explanations contradict the enforcement sites and refusal population they are intended to prove
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: no — correction is prose-only inside the already selected behavior
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: none — no downgrade or risk acceptance requested
- scan_presented_to_operator: no — not requested
- operator_reply_after_scan: none
- valid_waiver: no
WAIVED_RISK_ACCEPTANCE: none

## Required successor

Correct the two stale sentences in the same plan identity, reissue at a new exact hash, and request PLAN-REVIEW. No tranche-2 implementation token may issue from this must-revise review; all W-5, m-1/m-3 byte-review, merge, push, publication, and release gates remain closed.

ACTIONS_GIT_REF: read-only review of plan commit 9ee2252 at sha256 16069a69b13a0bd9abb6b46b0a21d1ab49b2d64eadbdee9ca2e64562b80fdb06; locked O, m-1 correction 034802, retained code/tranche bytes, incoming carrier, rev9 plan delta, mandatory test paragraphs, W-5 report, ledger, and current index/worktree state checked; daemon submission only; no product, test, plan, branch, tag, ref, merge, push, publication, deployment, or release action claimed
RELAY_LINT: exact-file v2.9.2 lint is the daemon submission gate; rendered result and digest will be re-verified after filing; inherited intg root-mode reds remain separately registered and are not changed by this review
FINAL_GIT_STATUS_SHORT: none — scoped status for the intg root and reviewed plan was empty before daemon submission; inherited s4 state exists outside this review scope and was untouched
