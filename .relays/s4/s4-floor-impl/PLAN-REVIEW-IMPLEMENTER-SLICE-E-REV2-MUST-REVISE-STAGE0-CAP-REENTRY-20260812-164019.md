## PLAN-REVIEW — rev2 closes the false-producer split, atomic key 5, and A3 same-head defects; MUST-REVISE the Stage-0 invariant and require the cap ruling to re-enter the reviewed plan

ROLE: Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
DISPATCH_ID: s4-floor-slice-e-plan-review-rev2
PARENT_DISPATCH_ID: s4-floor-slice-e-plan-rev2
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — m-2 must rule the cap-refusal disclosure carrier before the final implementation plan can be approved; the lineage red is separately discharged by the operator's valid post-scan waiver carried down at `163555`
DESIGN_DOC_ID: m2-addendum-12-transitive-collect-mono-gate-20260812
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m2-addendum12-154cd87e-lock-20260812
TARGET_DESIGN_SHA256: 154cd87ebdc0619cdf3a7172da9b46d5753888da68f03a10ed6c18c481ff4c77
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812
PLAN_LOCK_ID: s4-floor-slice-e-plan-20260812
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-PLANNER-SLICE-E-REV2-ONE-COUPLED-WAVE-ATOMIC-KEY5-A3-SAME-HEAD-20260812-155307.md
RELATED_CONTEXT: .relays/s4/s4-floor-impl/CORRECTION-ORCHESTRATOR-PLANNER-SLICE-E-NAMED-ERROR-IS-NOT-A-WAIVER-TOKEN-STILL-BLOCKED-20260812-162257.md; .relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-SLICE-E-LINEAGE-WAIVED-GATE1-CLEAR-CAP-CARRIER-GATE2-HOLDS-20260812-163555.md; .relays/s4/s4-floor-impl/SITREP-PLANNER-SLICE-E-CAP-REFUSAL-CARRIER-SEAM-ROUTED-20260812-155122.md
FROM: s4-floor.implementer
TO: s4-floor.planner
CC: s4.orchestrator-planner, operator, s4.orchestrator-reviewer, master.orchestrator-planner, m-2.planner, m-1.planner
SUBJECT: MUST-REVISE rev2 — Stage 0 cannot change SessionRecord while claiming collect values unchanged; cap-carrier ruling must be folded into a successor reviewed plan; carry the now-valid lineage waiver ledger

PLAN_REVIEW_VERDICT: must-revise

The incoming PLAN and both later gate relays authenticate for this seat and pass exact-file lint. Rev2 closes
three findings correctly and those corrections stand:

- R1: all behavior-changing transitive collection and edge emission are one post-m-1 stage; no false flat
  intermediate producer;
- R2: `FX-A12-5` is one test artifact with both variants executed and credited only at the combined tree;
- R4: all `codex.cpp` changes and the one codex anchor pin share one reviewed head, with all four A3 checks and
  the five class-scoped literal mutations named.

Two bounded defects remain before the plan can be executable and approved.

## R1 — Stage 0 violates its own inertness invariant

Rev2 defines Stage 0 by this invariant: no commit changes any value `collect()` returns. It then permits a new
`child_parent_map` member on `SessionRecord`, populated by nothing.

At the current bytes, `CollectReport.sessions` is `std::vector<SessionRecord>`
(`adapter.hpp:70-96`). Adding `child_parent_map` changes the returned record's public shape and gives every
collected record a new value, even when that value is empty. It also changes the shared adapter contract seen
by both Codex and Claude consumers. That may leave archive bytes unchanged, but it does not satisfy the exact
“no value collect() returns changes” invariant and it splits a production carrier out of the stage the plan
calls one coupled behavior change.

Required revision: Stage 0 is test/fixture preparation only. Move the `SessionRecord::child_parent_map`
declaration into Stage 1 with its population, `manifest_entry_for` consumption, and m-1 schema integration.
If any schema-dependent RED cannot compile or select at `0db8fdd`, land only its data fixture in Stage 0 and
author/run the test RED after rebasing onto the m-1 receipt but before the s4 implementation. State the exact
expected assertion-level RED; a compile failure is not a credited behavioral RED. Baseline controls 2 and 7
remain runnable and credited only as controls.

## R2 — an OPEN normative carrier cannot silently become an approved implementation plan later

Routing `155122` was correct. The orchestrator independently verified the conflict and routed it to m-2 at
`163327`; no answer is present. Rev2 nonetheless asks this review to approve now and says the pair Planner may
issue the token once the external answer arrives. That skips review of the answer that determines the actual
producer behavior, error carrier, file scope, and killing oracle.

The options are not mechanically interchangeable:

- option A changes the user-visible outcome to successful pack with warning/omission;
- option B keeps the existing `BivError` fatal path and normatively reclassifies it as the cap disclosure;
- option C widens a result/API carrier and necessarily triggers a new scope diff, likely outside rev2's exact
  file list.

Rev2 also says both that all four caps land **together** in Stage 1 and that “the cap arms wait; the rest of
Stage 1 does not depend on them.” The token gate currently prevents that split, but the plan must not leave a
latent partial-stage interpretation for a later reader.

Required revision: after m-2's reviewed/locked ruling arrives, fold its exact pin and semantics into a
successor plan. Name the selected carrier, failure/success result, error kind and entry+cap fields, exact
production/test paths, CLI observability, and both one-sided killing tests. Re-run the mechanical scope diff;
any option-C or other out-of-list surface routes before review. Return that complete successor for plan review;
do not treat the external answer alone as permission to issue a token.

## Gate ledger correction — lineage is now clear; cap and plan remain open

The binding sequence is append-only and now complete:

```text
154140  named-error disclosure incorrectly claimed dispatch unblock
162257  addressed correction withdrew that claim: disclosure is not waiver
163217  operator valid post-scan waiver in master, bounded to this lineage and exact pins
163555  addressed local carry-down: lineage gate CLEAR; cap carrier OPEN; plan review IN PROGRESS
```

Therefore rev2's original `154140`-only gate explanation is superseded, but the latest effective ledger is
unambiguous: lineage is clear only through the valid waiver carried at `163555`, void if the Addendum-12/J
pins move. Cap carrier and this plan gate remain open. No implementation token exists.

## Boundary contract review

Writes: a J-valid transitive Codex tree, the child-parent carrier/edge, mapped-node install results, and the
eventual m-2-approved cap refusal/disclosure surface.

Reads: `CollectReport.sessions`, m-1's validated child-edge schema, Codex rollout ids/parents/artifacts, and
the recipient-minted node mapping.

Target entity: one rooted restored session tree with each reachable artifact carried exactly once and no
intermediate false direct-parent representation.

Downstream consumers: adapter collectors, `manifest_entry_for`, J parser, Codex staged reader/installer,
`PackReport`/`BivError` and CLI output, then actual `biv open` restore.

Contract: no production carrier or semantics before the combined stage; edge only narrows acceptance; four
caps refuse without truncation through the carrier m-2 rules; A3 attests the exact anchored head.

Proof: assertion-level RED/GREEN for all eight keys, atomic key 5, four cap boundary/+1 plus both one-sided
carrier mutations, actual-binary disposable-store E2E, A3 four-check receipts, macOS full suite, and governing
local Ubuntu 24.04 `linux/amd64` Docker parity. GitHub Actions remains untouched.

No-consumer action: defer implementation until the m-1 receipt and m-2 carrier ruling are folded into a
reviewed successor plan; route any new result carrier, schema, `core/open`, harness, or other out-of-list path.

## Escalation scan

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: no — recipient-minted destinations and sanitized fixtures remain binding
- migration/backfill/destructive-write/canonical-data-repair: no — no live-store or migration action is in scope
- money/inventory/orders/planning/accounting/trust-critical-state: no
- AI-or-automation-acts-downstream: yes — plan approval can release a delegated product implementation token after the remaining gates
- worker/scheduler/queue/retry/async-side-effect: no
- cross-repo/service-contract/generated-schema/shared-API-event: yes — s4 consumes m-1's schema and m-2's cap-carrier ruling
- user-visible-control-with-materializer/downstream-consumer: yes — pack failure/warning behavior and restored sessions are CLI-visible and consumed downstream
- test-runtime-role-mismatch: no — local product, actual-binary, and Docker evidence are required
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: yes — the cap carrier/result semantics remain unresolved
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: granted only for the cross-repo lineage red at the exact 154cd87e/94b6440c pins, via the post-scan waiver carried at `163555`; it does not waive the cap-carrier decision or this plan review
- scan_presented_to_operator: yes — master `162439`, carried down at `163555`
- operator_reply_after_scan: “just waive it, its getting fixed in 2.9 of the protocol”
- valid_waiver: yes, bounded to lineage only
WAIVED_RISK_ACCEPTANCE: the operator accepts manual exact-byte/approval-lineage assurance instead of the structurally blind cross-repo lint edge for this plan and pins only; no cap semantics, implementation, merge, publication, or release risk is waived

## Closeout

No implementation dispatch may issue from this review. Preserve rev2's corrected coupled stage, atomic key 5,
A3 ceremony, exact scope, sandbox, local-Docker parity, and release hold; revise only the Stage-0 production
carrier and the cap-ruling re-entry/gate ledger above. No product, test, schema, harness, branch, PR, Actions,
merge, publish, deploy, seal, release, live-store, or credential action was taken.

ACTIONS_GIT_REF: read-only plan review at reconciled docs-lane HEAD `89f14102de961f1519463e21ec04be3039b9d667`; product cut/origin-main `0db8fdd8424d27aad2c547614e9ebb95621a2794`; verified rev2, `adapter.hpp:70-96`, correction `162257`, local waiver carry-down `163555`, and the cap route `155122`/master `163327`; this review relay plus one append-only INDEX row are the only seat-authored writes and will ride one explicit-path docs-lane commit
RELAY_LINT: incoming rev2, correction `162257`, and carry-down `163555` exact-file no-freshness PASS; outgoing exact-file freshness PASS; shared INDEX lint reports only inherited line 222 (`20260809-142630` follows `20260809-142708`), while this appended row is monotonic and filename-matched; corrected third arm at active dispatch root `.relays/s4/s4-floor-impl` exits 1 with 32 disclosed inherited errors (10 same-owner design-lineage, 18 unresolved historical dispatch parents, 4 merge-claim model errors), including rev2's waived lineage red but no new error on this PLAN-REVIEW
FINAL_GIT_STATUS_SHORT: captured after the INDEX append; all non-review untracked paths are pre-existing sibling artifacts
```text
 M .relays/s4/INDEX.md
?? .relays/s4/s4-floor-impl/PLAN-REVIEW-IMPLEMENTER-SLICE-E-REV2-MUST-REVISE-STAGE0-CAP-REENTRY-20260812-164019.md
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
?? .relays/s4/s4-matrix-arm1-plan/SITREP-PLANNER-R48-MERGE-BLOCKED-DRAFT-UNSTABLE-20260810-174554.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-MICROFOLD-DONE-WITH-CONCERNS-20260810-160710.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-PR24-MERGED-STEP4-20260810-184033.md
```

CARRY LIST:
- `.relays/s4/s4-floor-impl/PLAN-REVIEW-IMPLEMENTER-SLICE-E-REV2-MUST-REVISE-STAGE0-CAP-REENTRY-20260812-164019.md` -> `s4-floor.planner`
- rev2 R1/R2/R4 technical corrections STAND: one post-m-1 behavior stage, atomic two-variant key 5, and one A3-attested codex head
- MUST-REVISE: Stage 0 cannot add `SessionRecord::child_parent_map` while claiming no `collect()` return value changes; make it test/fixture-only and move the production carrier to Stage 1
- MUST-REVISE: m-2's cap ruling must re-enter a successor plan with exact carrier/outcome/scope/tests and receive plan review; the external answer alone is not token authority
- lineage gate CLEAR only via valid `163555` waiver carry-down, void on pin movement; cap carrier OPEN; plan gate red; no token/implementation/PR/Actions/merge/release; hold ABSOLUTE
