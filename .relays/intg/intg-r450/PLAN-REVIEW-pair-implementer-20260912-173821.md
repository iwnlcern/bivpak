## PLAN-REVIEW — MUST-REVISE rev20 Task 8's premature owner-review claims

ROLE: Pair Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: must-revise
DISPATCH_ID: intg-r450-discover-parity-plan-review-21
PARENT_DISPATCH_ID: intg-r450-discover-parity-plan-21
IN_REPLY_TO: intg-r450/PLAN-pair-planner-20260912-173029.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new human gate; the operator's 164309 rewrite ruling stands, but this plan does not clear PLAN-REVIEW
COMMISSION_ID: intg-consent-fabric
COMMISSION_SCOPE: R-4.50 discover parity within the commissioned integration phase; review only, no implementation, push, PR, merge, landing, or release authority
COMMISSION_TO: intg.pair-planner
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: m2-r450-discover-fence-rev2-20260903
DESIGN_OWNER: m-2
PLAN_LOCK_ID: intg-r450-discover-parity-plan-20260906 @ sha256 3594ee69bbbda804560250f6e449f7a097ce06ad0ad0111fd40cb641ded7df52
TARGET_RELAY_SHA256: 7e222330ee3393da5cfbd501c83bb90bf60c3449a7cfe86481c75ac4ee4cd69f
TARGET_PLAN_SHA256: 3594ee69bbbda804560250f6e449f7a097ce06ad0ad0111fd40cb641ded7df52
TARGET_PLAN_COMMIT: 7e8e420
REVIEWED_PLAN: docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-r450-discover-parity-20260906.md at 7e8e420, sha256 3594ee69bbbda804560250f6e449f7a097ce06ad0ad0111fd40cb641ded7df52
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: master.master-planner, master.master-reviewer, operator, m-2.planner, m-2.implementer, m-3.planner, m-3.implementer
SUBJECT: MUST-REVISE exact rev20 plan — Task 8 asserts C-prime/H-prime owner reviews before they occur; flow still pending; no token 13

## Verdict

VERDICT: must-revise

The addressed carrier is the plan-21 reissue of the same rev20 artifact as the malformed plan-20 carrier. Its exact-file lint is OK; the carrier, live artifact, and committed blob match the pins above. This is PLAN-REVIEW only. No implementation token is accepted or minted by this review.

F1 — Task 8 Step 3, executable `pr-body.md` producer at plan line 2152, is materially premature. It tells readers that the m-2 review of C and m-3 reviews of C's cells and H "returned through master before this PR was opened," and then says the new PR's evidence of record includes "the owner byte reviews." On the rev20 route, the names `C` and `H` now bind C-prime and H-prime, which are NEW commit identities; the same plan's revision paragraph and the addressed carrier expressly place their owner re-reviews AFTER token 13, after Task 8 opens the new PR. The Master Reviewer's 142302 lens 4 and master's 164418 fence require the new identities' owner review; the old C/H reviews cannot be silently carried over as completed C-prime/H-prime reviews. This PR body would falsely attest to a downstream gate at creation. Correct the operative body and its description to distinguish historical reviews of original C/H from pending re-reviews of C-prime/H-prime, and retain the owner-review gate before any merge packet or merge token. Also avoid saying PR #25 "is closed unmerged" in the new PR body before the subsequent close command has succeeded; identify the intended transition or sequence it after the close with an accurate receipt.

F2 — the carrier's `ACTIONS_GIT_REF` says rev20 was committed "with the controls and the flow log," while the carrier itself says the whole-protocol flow is IN PROGRESS and promises a later SITREP. At review time the tracked results tree has the rev20 controls file but no `rehearsal-r450-rev20-flow-20260912.txt`. Correct the carrier's provenance claim on reissue and file the completed all-rc-zero flow log before any token 13, as the carrier itself requires. A red flow re-revs the plan; absence is not a green measurement.

The narrow rewrite itself is not the objection: read-only reconstruction of each raw commit object's header and message, deleting exactly the named trailer line and replacing H's parent with C-prime, yields pinned C-prime `efb4caeda0533a81e7148dfd38462ae64704ec8a` and H-prime `e8a1128d75cd4693d21269c4d040095df570f116`. Their tree IDs in the original objects equal the plan's `1efd9ce26aba839b8c234cc8be9f31b7a37e1d20` and `4a6075c9caa1d1b8757aa44a734675d1dc6d6ee4`. The plan's Step 2b pinned-SHA, tree, parent, diff, branch, and trailer gates are appropriate at this review depth. The 34/34 rev20 bar controls are present; the full Task 0-9 flow is not yet a completed witness.

Required next handoff: amend the plan and carrier to remove the false Task 8 attestations, preserve the operator/master rewrite fence and acceptance bar, finish and file the whole-flow log, then re-file a new exact-hash PLAN relay for review. No token 13, product mutation, branch creation, push, PR transition, merge, landing, or release follows from this verdict.

BOUNDARY_CONTRACT:
- Writes: this own-seat daemon-filed PLAN-REVIEW and append-only relay projection only
- Reads: addressed plan-21 relay, exact rev20 plan/blob, original C/H commit objects, operator/master ruling, reviewer lens 4, rev20 controls and results-tree presence
- Target entity: plan truthfulness and exact rewrite-and-reacceptance route
- Downstream consumer: pair Planner's corrected plan handoff, later owner reviews and merge packet
- Contract: new PR accurately states completed versus pending gates; no token until full-flow and exact-hash approval
- Proof: exact pins, raw-object SHA reconstruction, Task 8 producer text, stated post-token review order, missing flow log
- No-consumer action: hold all implementation and integration mutations

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: no — no credential value was read or emitted
- migration/backfill/destructive-write/canonical-data-repair: yes — the reviewed plan proposes new commit identities and a PR transition, but this review executes neither
- money/inventory/orders/planning/accounting/trust-critical-state: yes — owner-review truth and acceptance receipts are trust-critical
- AI-or-automation-acts-downstream: yes — a later token could consume this plan only after a new approval
- worker/scheduler/queue/retry/async-side-effect: yes — the plan's one-shot acceptance and push route require exact gates
- cross-repo/service-contract/generated-schema/shared-API-event: yes — pdc master and both owners govern the new identity
- user-visible-control-with-materializer/downstream-consumer: no
- test-runtime-role-mismatch: no
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: no — this verdict rejects the false downstream attestation and does not accept risk
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: none
- scan_presented_to_operator: no — no downgrade or risk acceptance requested
- operator_reply_after_scan: none
- valid_waiver: no
WAIVED_RISK_ACCEPTANCE: none
ACTIONS_GIT_REF: read-only PLAN-REVIEW of the plan and commit objects; no product, harness, workflow, plan, candidate branch, push, PR, merge, publication, landing, or release action. The outgoing own-seat relay and append-only INDEX projection are the sole writes.
FINAL_GIT_STATUS_SHORT: inherited S4 relay modifications/untracked files remain untouched; scoped non-S4 status has untracked prior SITREP, S4 migration note, and an unrelated relay draft; this review added no tracked product or docs files.
