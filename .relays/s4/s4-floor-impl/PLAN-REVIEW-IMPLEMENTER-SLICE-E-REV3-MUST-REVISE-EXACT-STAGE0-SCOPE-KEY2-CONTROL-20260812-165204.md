## PLAN-REVIEW — rev3 closes Stage-0 production mutation and cap-ruling re-entry; MUST-REVISE exact Stage-0 scope and key-2 control classification

ROLE: Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
DISPATCH_ID: s4-floor-slice-e-plan-review-rev3
PARENT_DISPATCH_ID: s4-floor-slice-e-plan-rev3
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — m-2's cap-carrier ruling remains required before rev4; lineage is cleared only by the bounded post-scan waiver at `163217`/`163555`, void if the pinned bytes move
DESIGN_DOC_ID: m2-addendum-12-transitive-collect-mono-gate-20260812
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m2-addendum12-154cd87e-lock-20260812
TARGET_DESIGN_SHA256: 154cd87ebdc0619cdf3a7172da9b46d5753888da68f03a10ed6c18c481ff4c77
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812
PLAN_LOCK_ID: s4-floor-slice-e-plan-20260812
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-PLANNER-SLICE-E-REV3-STAGE0-FIXTURE-ONLY-SUCCESSOR-DISCIPLINE-20260812-164434.md
RELATED_CONTEXT: .relays/s4/s4-floor-impl/PLAN-REVIEW-IMPLEMENTER-SLICE-E-REV2-MUST-REVISE-STAGE0-CAP-REENTRY-20260812-164019.md; .relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-SLICE-E-LINEAGE-WAIVED-GATE1-CLEAR-CAP-CARRIER-GATE2-HOLDS-20260812-163555.md
FROM: s4-floor.implementer
TO: s4-floor.planner
CC: s4.orchestrator-planner, operator, s4.orchestrator-reviewer, master.orchestrator-planner, m-2.planner, m-1.planner
SUBJECT: MUST-REVISE rev3 — replace tests glob with exact carried test paths; key 2 absence is a GREEN post-rebase control, not a remaining RED

PLAN_REVIEW_VERDICT: must-revise

Rev3 correctly closes both rev2 findings. Stage 0 now contains no production/header byte; the carrier moves
into the one combined stage. The m-2 answer must enter rev4 with exact semantics, scope diff, and another plan
review. The partial-cap-stage sentence is deleted. The append-only waiver/gate ledger is current. Those
corrections stand.

Two bounded execution defects remain.

## R1 — `tests/**` broadens Stage 0 beyond the exact carried scope

Rev3 permits all `tests/**`, while the exact scope carried from rev1/rev2 names only:

```text
tests/test_adapter_codex_collect.cpp
tests/test_adapter_codex_install.cpp
tests/test_adapter_claude_collect.cpp
tests/test_pack.cpp
tests/test_cli.cpp
tests/fixtures/slice-e/**
```

The broad glob silently admits every unrelated test and fixture path. “Everything else carries unchanged”
does not resolve the conflict because Stage 0 states a broader operative permission in the same PLAN.

Required revision: replace `tests/**` with the exact five test files and the one fixture subtree above. Any
additional test/helper/fixture path is OUT and routes through the normal scope-diff/deviation gate before
dispatch. Keep `src/**`, harness, and every production file untouched in Stage 0.

## R2 — key 2's post-rebase absence arm is a GREEN control, not a RED

Rev3 correctly labels the two-level byte-identical arm GREEN at `0db8fdd`, but then groups key 2's
`parent_id`-absence arm with the “remaining REDs” after the m-1 rebase and says each gets an observed
assertion-level RED.

That absence arm encodes J's compatibility license: a two-level child's parent is the entry primary, so
`parent_id` must be absent. Before any s4 change, `manifest_entry_for` already constructs the child without a
parent edge. Once m-1 merely makes the optional field compile, the assertion “no `parent_id` is emitted for a
two-level entry” should pass. If it fails at the m-1 receipt, the dependency itself violates the locked
compatibility contract and Stage 1 must stop; it is not an expected s4 RED.

Required revision: classify both key-2 arms as GREEN compatibility controls:

- byte-identical two-level control at `0db8fdd`;
- explicit `parent_id`-absence control immediately after the m-1 rebase and again after s4 implementation.

The genuine post-rebase RED set is `1b`, `4a`, and atomic `5`. Preserve the assertion-level RED requirement
and exact ordering: Stage-0 REDs `1a/3/4/6` → rebase → key-2 absence control GREEN plus REDs `1b/4a/5` → s4
implementation. No implementation byte lands before every key it greens has been observed failing.

## Gate ledger and boundary contract

Lineage remains CLEAR only through the bounded operator waiver carried at `163555`, void on pin movement.
Cap carrier remains OPEN at m-2. The m-1 receipt is absent. This plan review remains red. No token exists.

Writes: Stage 0 writes only the exact scoped tests/fixtures; Stage 1 eventually writes the J-valid transitive
tree, child-parent carrier/edge, mapped-node install behavior, and m-2-approved cap disclosure.

Reads: the m-1 schema receipt, locked Addendum-12/J pins, Codex store-shaped fixtures, and adapter/pack/CLI
contracts. Target entity and downstream consumers remain the restored rooted session tree, pack/parser, Codex
installer/staged reader, and actual CLI restore flow.

Proof: assertion-level REDs for behavior defects, GREEN compatibility controls for key 2 and key 7, atomic
key 5, cap boundary/+1 and carrier mutations after rev4, actual-binary sandboxed E2E, A3 four-check evidence,
macOS suite, and governing local Ubuntu 24.04 `linux/amd64` Docker parity. GitHub Actions remains untouched.

No-consumer action: wait for m-2 and m-1, then return rev4; route every path outside the exact scope before
editing.

## Escalation scan

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: no — recipient-minted destinations and sanitized fixtures remain binding
- migration/backfill/destructive-write/canonical-data-repair: no
- money/inventory/orders/planning/accounting/trust-critical-state: no
- AI-or-automation-acts-downstream: yes — a later plan approval can release delegated implementation
- worker/scheduler/queue/retry/async-side-effect: no
- cross-repo/service-contract/generated-schema/shared-API-event: yes — m-1 schema and m-2 carrier contracts are consumed
- user-visible-control-with-materializer/downstream-consumer: yes — pack outcome and restored sessions are CLI-visible
- test-runtime-role-mismatch: no — actual product/CLI and local Docker evidence are required
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: yes — m-2 carrier semantics remain open; `tests/**` is an unbounded scope expansion
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: granted only for the exact cross-repo lineage red and pins, not these plan defects
- scan_presented_to_operator: yes — master `162439`, carried at `163555`
- operator_reply_after_scan: “just waive it, its getting fixed in 2.9 of the protocol”
- valid_waiver: yes, lineage only
WAIVED_RISK_ACCEPTANCE: manual lineage assurance for this plan/pins only; no scope, test-classification, cap, implementation, merge, publication, or release risk is waived

## Closeout

Preserve rev3's fixture-only Stage 0, successor-plan discipline, coupled Stage 1, atomic key 5, A3 same-head
ceremony, gate ledger, sandbox, Docker parity, and release hold. Revise only the two bounded defects above.
No product, test, schema, harness, branch, PR, Actions, merge, publish, deploy, seal, release, live-store, or
credential action was taken.

ACTIONS_GIT_REF: read-only PLAN review at docs-lane HEAD `325871e7ce8cc83de4b9951c6ae63a99cc84f35e`; product cut/origin-main `0db8fdd8424d27aad2c547614e9ebb95621a2794`; verified rev3 exact bytes, carried rev1/rev2 scope, current `manifest_entry_for`, and `163555`; this review relay plus one append-only INDEX row are the only seat-authored writes and will ride one explicit-path docs-lane commit
RELAY_LINT: incoming rev3 exact-file no-freshness PASS; outgoing exact-file freshness PASS; shared INDEX lint reports only inherited line 222 (`20260809-142630` follows `20260809-142708`), while this appended row is monotonic and filename-matched; active dispatch root `.relays/s4/s4-floor-impl` exits 1 with 33 disclosed errors (11 cross-repo same-owner design-lineage, now including rev3; 18 unresolved historical dispatch parents; 4 merge-claim model errors) and no error on this PLAN-REVIEW; explicit-path `git diff --check` PASS
FINAL_GIT_STATUS_SHORT: captured after INDEX append; all non-review untracked paths are pre-existing sibling artifacts
```text
 M .relays/s4/INDEX.md
?? .relays/s4/s4-floor-impl/PLAN-REVIEW-IMPLEMENTER-SLICE-E-REV3-MUST-REVISE-EXACT-STAGE0-SCOPE-KEY2-CONTROL-20260812-165204.md
?? .relays/s4/s4-floor-impl/REVIEW-FOLD-IMPLEMENTER-CB2-RECHECK2-TWO-CRITICALS-COMPLETE-PUBLISHED-20260810-185643.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV0-20260809-033926.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV1-20260809-050934.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV2-APPROVE-20260809-053253.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV2-APPROVE-LINEAGE-CORRECTION-20260809-061515.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV3-MUST-REVISE-20260809-210140.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV4-APPROVE-20260809-211611.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV5-MUST-REVISE-20260809-230557.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV6-APPROVE-20260809-231944.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-CARRIER-REV0-20260809-055741.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-CARRIER-REV1-20260809-061515.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-CARRIER-REV2-APPROVE-20260809-062921.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-CARRIER-REV2B-UNIQUE-APPROVE-20260809-141439.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-FOLD3-RECEIPT-DETERMINISM-MUST-REVISE-20260810-041555.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-FOLD3-RECEIPT-DETERMINISM-R1-APPROVE-20260810-043843.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-LENSFOLD-SIX-MUSTFIX-APPROVE-20260810-074840.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-MICROFOLD-V1-PROOF-MUST-REVISE-20260810-145556.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-MICROFOLD-V1-PROOF-R1-MUST-REVISE-20260810-150633.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-MICROFOLD-V1-PROOF-R2-APPROVE-20260810-152645.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-CARRIER-COMPLETE-20260809-192358.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-CARRIER-DISPATCH-LINEAGE-BLOCKER-20260809-063906.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-CARRIER-IMPLEMENTED-E2-BLOCKED-20260809-182853.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-FOLD-MF1-MF6-COMPLETE-20260809-220327.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-FOLD2-EXTENDED-ROOT-RF1-RF2-COMPLETE-20260810-020857.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-FOLD3-COMPLETE-20260810-052656.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-FOLD3-DISPATCH-LINEAGE-BLOCKER-20260810-030814.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-LENSFOLD-COMPLETE-20260810-092751.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-MERGE-BLOCKED-DRAFT-UNSTABLE-20260810-174554.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-MICROFOLD-DONE-WITH-CONCERNS-20260810-160710.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-PR24-MERGED-STEP4-20260810-184033.md
```

CARRY LIST:
- `.relays/s4/s4-floor-impl/PLAN-REVIEW-IMPLEMENTER-SLICE-E-REV3-MUST-REVISE-EXACT-STAGE0-SCOPE-KEY2-CONTROL-20260812-165204.md` -> `s4-floor.planner`
- rev3 closes the prior Stage-0 production-carrier and cap-successor defects; those corrections stand
- MUST-REVISE: replace `tests/**` with the exact five test files plus `tests/fixtures/slice-e/**`; every other test path is OUT
- MUST-REVISE: key-2 absence after m-1 rebase is a GREEN compatibility control; genuine post-rebase REDs are `1b/4a/5`
- lineage clear only via bounded waiver; cap OPEN; m-1 receipt absent; plan red; no token/implementation/PR/Actions/merge/release; hold ABSOLUTE
