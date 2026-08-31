## PLAN-REVIEW artifact — APPROVE revision 2 at exact 57ab3b9b: both returned mechanical defects are closed and W-4 covers only the measured M/N lineage partition

ROLE: Pair Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: approve
DISPATCH_ID: intg-substep2a-plan-review-2
PARENT_DISPATCH_ID: intg-substep2a-plan
IN_REPLY_TO: intg-substep2a/PLAN-pair-planner-20260831-022653.md
RELATED_CONTEXT: intg-substep2a/PLAN-REVIEW-pair-implementer-20260830-234421.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep2a-20260830.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/results/lint-root-sweep-2a-rev2-w4-20260831.txt; ../../../pdc/master/relays/intg-substep2a-format-act/PLAN-master-planner-20260831-022201.md; ../../../pdc/master/RESIDUALS.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — exact-digest plan approval only; a separate correctly parented pair-Planner implementation token remains required, while m-1 byte review, merge, push, publication, deployment, and release retain their named gates
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: intg-format-act-plan
DESIGN_LOCK_ID: m1-addendum-N-82293732-lock-20260827
DESIGN_RECORD_KIND: design-doc
SECOND_CONSUMED_LOCK: m1-addendum-M-2966b839-lock-20260825
PLAN_LOCK_ID: intg-substep2a-plan-20260830 @ sha256 57ab3b9ba15c5674dae5b42dc3a3c48252e844f8e3d863d0cb1f3682c33b4a4b
REVIEWED_PLAN: docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep2a-20260830.md at commit 6f822bf427487e552a837f74687b0ae67862166e, sha256 57ab3b9ba15c5674dae5b42dc3a3c48252e844f8e3d863d0cb1f3682c33b4a4b
BASE: main@46df8f3c35981a4ae3f77cf3293a4b7212b4b996; review filed from main@6f822bf427487e552a837f74687b0ae67862166e
BRANCH: intg/format-act not created; target worktree ../bivpak-intg-format-act absent; no product byte changed
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: master.master-planner, master.master-reviewer, m-1.planner, m-1.implementer
SUBJECT: APPROVE exact 57ab3b9b revision 2 — F1 and F2 are mechanically closed; all sealed M/N, W-4 partition, coverage, byte-review, implementation-token, merge, push, and release boundaries remain controlling

## Verdict

APPROVE at exact SHA-256 `57ab3b9ba15c5674dae5b42dc3a3c48252e844f8e3d863d0cb1f3682c33b4a4b`.

Revision 2 closes both findings from review `234421` without changing the plan's substantive engineering contract. The prior-to-current artifact diff is limited to four replacements: the zero-caller census is production-scoped in both occurrences, the Task-4 scope census names a sorted seven-path allowlist, and acceptance criterion 8 now states seven paths plus the scoped caller proof. `git diff --check` is clean.

This approval is PLAN-REVIEW authority only. It is not implementation authority and does not authorize product edits, branch/worktree creation, merging, pushing, publication, deployment, or release.

## Finding closure

### F1 — closed

The plan still authorizes exactly seven paths: three under `src/core/repo`, two under `src/core/manifest`, and two tests. Task 4 now compares the sorted candidate path census to the explicit sorted seven-path allowlist, proving both membership and cardinality. Acceptance criterion 8 consistently says seven. No stale “six planned paths” text remains.

### F2 — closed

Global constraint 5 and Task 4 now use the same production-scoped command:

```text
git grep -n 'run_eligibility\|restore_entry\|repo::capture' -- src ':!src/core/repo'
```

Executed against the pinned base `46df8f3c35981a4ae3f77cf3293a4b7212b4b996`, it returns no output and rc 1. The positive `src` pathspec excludes relays and documentation that legitimately name the symbols, so the command now measures zero production callers as intended.

## Preserved substantive contract

- `Manifest.repos : std::vector<repo::RepoEntry>` remains the single carrier, with the same cycle-free include justification and STOP on a discovered schema mismatch.
- The N-R3 ordering, boundary-only `Shallow`, mirror retirement, shallow bundle suppression, and shallow-pointer-before-payload-only-unborn restore order remain unchanged.
- Task 3 remains one symmetric commit containing carrier, writer, parser, round-trip proof, and `require_empty_array("repos")` retirement.
- The never-serialized, no-format-version-bump, no-product-call-site, E4 request-trace, TDD, two-platform, and seven-path fences remain explicit.
- The hard out-of-scope set still excludes M consent-seam bytes, m-2/m-3 surfaces, schemas, harness, workflows, 2b wiring, the `--offline` CLI surface, merge, push, publication, and release.
- The pinned product roots at base `46df8f3` remain byte-equal to landed `81066ef`; the target branch and worktree remain absent at review time.

## W-4 boundary confirmation

The addressed Master-Planner notice `022201` is context for this review and grants coverage consumption to the Pair Planner, not implementation authority to this seat. Its binding registry blob at commit `dfc58e50f146a13b1a8aac90ff3d54b519d7376c` independently re-hashes to `5aa05c140ae5cfed968dc0d97d8e4480ef7d0b5070ede329ccf190d0a7b1ea04`.

The revision-2 replacement measurement is filed at SHA-256 `b32e0c4fe11f5ea4f7b6ed181ff28b773e5e33aff4e610cfa8b998e34b936241`. It records the new `022653` carrier's N primary-lock design-lineage red. W-4 covers only this plan lineage's named M rev8 and N locks; M remains manual-assurance-only rather than a fired primary-lock entry. Historical/root noise remains red and is neither erased nor cited as green. Per-file lint is structural proof only and is not substituted for the root-mode measurement.

No third plan, changed plan identity, or out-of-row sealed identity was observed. This exact approval satisfies only the exact-hash review prerequisite. The Pair Planner must still issue a fresh, correctly parented bare implementation token before any implementation act.

## Escalation scan

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: no — review-only; no credential or permission surface changed
- migration/backfill/destructive-write/canonical-data-repair: no — no product or canonical data write
- money/inventory/orders/planning/accounting/trust-critical-state: no — no such runtime state
- AI-or-automation-acts-downstream: no — no downstream automation action
- worker/scheduler/queue/retry/async-side-effect: no — no product runtime action
- cross-repo/service-contract/generated-schema/shared-API-event: yes — sealed PDC M/N locks and the pinned W-4 registry govern this approval
- user-visible-control-with-materializer/downstream-consumer: yes — the future manifest/restore behavior is user-visible but remains unwired and unimplemented
- test-runtime-role-mismatch: yes — the chartered two-platform execution instrument remains mandatory
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: yes — root historical noise and all later byte-review/merge/release gates remain retained
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: granted — W-4 only, at the pinned registry bytes and exact two-lineage partition; no other risk or gate waived
- scan_presented_to_operator: yes — W-4 registry record at commit dfc58e50f146a13b1a8aac90ff3d54b519d7376c and Master Reviewer concurrence 015509, carried by addressed notice 022201
- operator_reply_after_scan: waiver approved, as recorded by W-4 and the addressed effectiveness notice
- valid_waiver: yes — only for the two named structural lineage-red partitions and their replacement-measurement rule
WAIVED_RISK_ACCEPTANCE: W-4 accepts only the structural cross-repo design-lineage reds for this plan's named M rev8 and N locks under manual bytes-and-approval assurance; it does not accept any product, test, byte-review, merge, push, publication, deployment, or release risk

## Authority and next action

Pair Planner: record this exact-digest approval. If every delegated-dispatch condition still stands, issue the fresh `intg-substep2a-impl` handoff parented to `intg-substep2a-plan-review-2`. Any plan-byte change requires another exact-hash review. The future implementation must stop on any S-FA trigger or scope deviation and must preserve the separate m-1 candidate byte review and all merge/push/release gates.

ACTIONS_GIT_REF: read-only review of plan commit 6f822bf427487e552a837f74687b0ae67862166e at sha256 57ab3b9ba15c5674dae5b42dc3a3c48252e844f8e3d863d0cb1f3682c33b4a4b; prior-to-current four-line plan diff, corrected pinned-base caller census, explicit seven-path allowlist, W-4 notice and registry pin, replacement root-mode measurement, pinned product-root equality, target branch/worktree absence, incoming relay lint, and inherited worktree state checked; this review submits through the intg daemon; no product, plan, workflow, branch, worktree, merge, push, publication, deployment, or release action claimed
RELAY_LINT: exact-file v2.9.2 lint is the daemon submission gate; rendered result and digest reported externally
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
