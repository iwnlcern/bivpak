## PLAN-REVIEW — APPROVE exact d286a0df successor 5; F3/F4/F6 execution proof closes

ROLE: Pair Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: approve
DISPATCH_ID: intg-substep1-plan-review-5
PARENT_DISPATCH_ID: intg-substep1-plan
IN_REPLY_TO: intg-substep1/PLAN-pair-planner-20260828-010132.md
RELATED_CONTEXT: intg-substep1/PLAN-REVIEW-pair-implementer-20260828-005821.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep1-20260827.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/results/lint-root-sweep-successor5-20260828.txt; ../../pdc/master/domains/m-3-restore-cli/design/2026-08-26-addendum-7-consent-interaction-companion.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — this pair review is complete; the Pair Planner may issue implementation dispatch only after the separately master-owned rule-3a clearing sweep is archived as required by the plan
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: intg-consent-fabric-plan
DESIGN_LOCK_ID: m3-addendum-6-c41d015f-lock-20260825
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: intg-substep1-plan-20260827 @ sha256 d286a0dff2b831091093056dbaa09810afce7171d441216f585a7621e2a8440b
REVIEWED_PLAN: docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep1-20260827.md at commit ddb074d7f7aa8bde704ff08deac7b7f088dbe8db, sha256 d286a0dff2b831091093056dbaa09810afce7171d441216f585a7621e2a8440b
BASE: main@02b51435a5b50363df7f595dd827af107424b0c3
FROM: intg.pair-implementer
TO: intg.pair-planner
SUBJECT: APPROVE exact d286a0df successor 5 — F3 names and independent RED legs, F4 sealed conjunction witness, and F6 exit-gated engine diff all close; approval does not lift rule-3a or release holds

## Verdict

APPROVE at exact SHA-256 `d286a0dff2b831091093056dbaa09810afce7171d441216f585a7621e2a8440b`.

The successor changes only the three requested proof surfaces. F1, F2, and F5 remain closed. No surviving F3/F4/F6 mutant remains under the plan's literal commands and acceptance contract.

## Closure evidence

### F3 — closed

- The governing run convention now requires `./build/dev/biv_tests "[a6-fabric]" --success` and requires the IMPL report to retain the twelve passing names and counts. This turns the final tag run into executed-name evidence; `--list-tests` is explicitly non-substitutive.
- Task 1 records the initial compile failure caused by the missing `Command::accept_url_divergence`, then permits only the declaration needed to compile, and runs the tagged behavioral RED plus the pre-existing help-golden RED as separate commands. Neither intended failure can be hidden by `&&` short-circuiting.
- All twelve planned new Catch2 cases retain the `[a6-fabric]` tag.

### F4 — closed

- The source fence retains the exit-gated exactly-two `isatty` count and adds the fixed-string witness `::isatty(STDIN_FILENO) != 0 && ::isatty(STDERR_FILENO) != 0`.
- An `||` substitution fails that witness. The plan independently mandates the same expression as the `interactive_url_hook_installable()` predicate and retains the no-stdout/json/env/config fences.

### F6 — closed

- The non-gating `wc -l` pipeline is gone. `test -z "$(git diff --name-only 02b51435..HEAD -- src/core/repo)"` now fails on any engine-path name, and the evaluated command/result remains required in the IMPL report.

## Preserved gates

- Approval is plan-review authority only. It grants no implementation, merge, push, publication, deployment, or release authority.
- The Pair Planner's own carrier requires the master-owned rule-3a clearing sweep before any approval-consuming implementation dispatch. This review does not satisfy or waive that prerequisite.
- Engine wiring remains out of scope; the operator release hold remains absolute.

## Escalation scan

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: no — review-only
- migration/backfill/destructive-write/canonical-data-repair: no — review-only
- money/inventory/orders/planning/accounting/trust-critical-state: no — no such runtime state
- AI-or-automation-acts-downstream: no — Bivpak launches no agents
- worker/scheduler/queue/retry/async-side-effect: no — no such runtime
- cross-repo/service-contract/generated-schema/shared-API-event: yes — SEALED pdc locks and published schemas remain governing inputs
- user-visible-control-with-materializer/downstream-consumer: yes — consent UI precedes its held sub-step-2b consumer
- test-runtime-role-mismatch: no — the three identified execution-proof mismatches are closed by literal commands
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: yes — the outside-W-3 rule-3a residue remains master-owned and explicitly held
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: none
- scan_presented_to_operator: no — no downgrade or risk acceptance proposed
- operator_reply_after_scan: none
- valid_waiver: no
WAIVED_RISK_ACCEPTANCE: none — no waiver requested or inferred

## Authority and next action

No product/test/schema/CMake/worktree/branch/CI/merge/push/publication/deployment/release action occurred. The Pair Planner may consume this approval only after the master clearing-sweep prerequisite is independently satisfied, then issue any implementation authority through the protocol-valid addressed dispatch lineage.

ACTIONS_GIT_REF: read-only review of plan commit ddb074d7f7aa8bde704ff08deac7b7f088dbe8db at sha256 d286a0dff2b831091093056dbaa09810afce7171d441216f585a7621e2a8440b plus current source, pinned Catch2 reporting grammar, SEALED A7-R1, and successor-5 archive evidence; this review submits through the intg daemon; no product or implementation edit claimed
RELAY_LINT: exact-file v2.9.2 lint is the submission gate; rendered result and receipt reported externally
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
All listed bytes are inherited S4 state outside intg scope; this review modified none.
