## PLAN-REVIEW — MUST-REVISE rev21 Step 3 descriptive mismatch

ROLE: Pair Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: must-revise
DISPATCH_ID: intg-r450-discover-parity-plan-review-23
PARENT_DISPATCH_ID: intg-r450-discover-parity-plan-23
IN_REPLY_TO: intg-r450/PLAN-pair-planner-20260913-013024.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new human gate; the operator's rewrite ruling stands, but this exact plan does not clear review
COMMISSION_ID: intg-consent-fabric
COMMISSION_SCOPE: R-4.50 discover parity in the commissioned integration phase; this relay is review-only and authorizes no implementation, push, PR, merge, landing, or release
COMMISSION_TO: intg.pair-planner
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: m2-r450-discover-fence-rev2-20260903
DESIGN_OWNER: m-2
PLAN_LOCK_ID: intg-r450-discover-parity-plan-20260906 @ sha256 b5d60dbbf5191597edbe222c136c16bc88985bc807e903b210c1d7cc53f09502
TARGET_RELAY_SHA256: 19280814a51963666ff1a73f6e12b596366d527facf087f3d65a2955d73d220f
TARGET_PLAN_SHA256: b5d60dbbf5191597edbe222c136c16bc88985bc807e903b210c1d7cc53f09502
TARGET_PLAN_COMMIT: f66f4f84be35abc243a348afdb2a7761f897d824
REVIEWED_PLAN: docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-r450-discover-parity-20260906.md at f66f4f84be35abc243a348afdb2a7761f897d824, sha256 b5d60dbbf5191597edbe222c136c16bc88985bc807e903b210c1d7cc53f09502
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: master.master-planner, master.master-reviewer, operator, m-2.planner, m-2.implementer, m-3.planner, m-3.implementer
SUBJECT: MUST-REVISE rev21 at b5d60dbb — Step 3 narrative still describes the superseded PR body sentence and no-comment behavior; executable F1 fix and completed F2 flow verified; no token 13

## Verdict

VERDICT: must-revise

The plan-23 carrier is correctly addressed, exact-file lint OK, and uniquely indexed. Its live plan and committed blob both hash to b5d60dbbf5191597edbe222c136c16bc88985bc807e903b210c1d7cc53f09502. The earlier plan-22 carrier was withdrawn for a REPO-label error and is not reviewed here.

F1 residual — the rev21 Task 8 Step 3 RUN block at plan line 2154 now emits the correct temporal language: original C/H reviews returned before PR #25; new C-prime/H-prime reviews are PENDING; PR #25 is TO BE closed unmerged by the next command. The durable rehearsal's pr-body.md independently contains that wording. However, the live Step 3 description at line 2150 still says the body names the old sentence, without the PENDING qualification: “the evidence of record is the local suites, the Docker parity leg, the owner byte reviews, and the operator's condition-4 token.” The same description ends “No ... comment,” although its executable command immediately calls gh pr close 25 --comment. This is an operative current-Step description, not a revision-history quote. It contradicts the runner and leaves my 173821 requirement to correct both the body AND its description incompletely folded. Make the description quote the actual pending-review sentence or describe the pending status without an obsolete verbatim quote, and distinguish no comment on the NEW PR from the required close comment on #25. Preserve the actual RUN block and the master's post-token owner re-review gate.

F2 closed — the carrier's ACTIONS_GIT_REF accurately says the completed flow log was committed with f66f4f8. The tracked rev21 flow log hashes equally live and at that commit. Its disclosed first rehearsal STOP was a scratch-topology mismatch; the rev21c full-clone plus redirected repo-ro mount rehearsal has Tasks 0 through 9 all exit=0 with proof_tail=rc=0 and task_exit=rc=0. I also read all ten durable proof-N.txt tails (all rc=0), the Task 8 PR body and pr25-close receipt, and the 34 bar-control outcome rows (34 OK). These are rehearsal E2, not token-13 execution or new-identity owner review. The real linked candidate remains clean at original H 8509157c, with Git common dir at MAIN; C-prime is still absent from the real object store. No token or downstream gate is inferred from the rehearsal.

The Step 2b pinned rewrite mechanism was independently reproduced in the prior 173821 review and reconfirmed by master's 175243 relay; this revision changes no Task 0 bytes. The actual Task 8 RUN block is the only changed runner from rev20, and its emitted PR-body wording resolves the executable part of F1. The remaining correction is to the current descriptive claim, not to the rewrite, acceptance classifier, or flow. After a new exact-hash carrier accurately folds that line, re-review can be narrow; until then no token 13 is approved.

BOUNDARY_CONTRACT:
- Writes: this own-seat daemon-filed PLAN-REVIEW and append-only relay projection only
- Reads: addressed plan-23 carrier, exact plan/blob/diff, prior 173821 review, master 175243 fence, completed controls and flow, durable rehearsal receipts, real linked-worktree state
- Target entity: exact plan truthfulness at the Task 8 PR transition
- Downstream consumer: pair Planner's corrected plan, later token 13, owner re-reviews and merge packet
- Contract: Step 3 description must match the pending-versus-complete gate and actual comment action; no approval by implication from E2 rehearsal
- Proof: line 2150 versus line 2154 and rehearsal pr-body.md; tracked flow and ten durable task proofs
- No-consumer action: hold implementation and integration mutations

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: no — no credential value was read or emitted
- migration/backfill/destructive-write/canonical-data-repair: yes — the plan proposes new commit identities and a PR transition, but this review executes neither
- money/inventory/orders/planning/accounting/trust-critical-state: yes — owner-review truth and acceptance receipts are trust-critical
- AI-or-automation-acts-downstream: yes — a later token could consume this plan only after approval
- worker/scheduler/queue/retry/async-side-effect: yes — the plan's one-shot acceptance and push route require exact gates
- cross-repo/service-contract/generated-schema/shared-API-event: yes — pdc master and both owners govern the new identities
- user-visible-control-with-materializer/downstream-consumer: no
- test-runtime-role-mismatch: no
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: no — this review accepts no residual risk or scope change
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: none
- scan_presented_to_operator: no — no downgrade requested
- operator_reply_after_scan: none
- valid_waiver: no
WAIVED_RISK_ACCEPTANCE: none
ACTIONS_GIT_REF: read-only plan review; the outgoing own-seat relay and daemon INDEX append are the sole intended repository writes. No product, harness, workflow, plan, candidate branch, commit, push, PR, merge, landing, publication, deployment, or release action.
FINAL_GIT_STATUS_SHORT:
 M .relays/s4/INDEX.md
 M .relays/s4/SEATS.md
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
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-WAVE-A-REVERIFY-STAGE1-INDEPENDENT-STOP-CORROBORATION-20260820-161626.md
?? .relays/s4/s4-matrix/SITREP-implementer-20260825-220111.md
?? docs/sprints/2026-08-04-s4-step4/MIGRATION-adt-skills-2.9-20260816.md
?? relay-draft-intg-task4-stop.md
