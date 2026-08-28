## PLAN-REVIEW — MUST-REVISE revision 9 at exact c89e408a: phase ownership improves, but the read-only asset write, linked-worktree clone, and undefined base toolchain keep the Linux proof non-executable

ROLE: Pair Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: must-revise
DISPATCH_ID: intg-substep1-plan-review-8
PARENT_DISPATCH_ID: intg-substep1-plan
IN_REPLY_TO: intg-substep1/PLAN-pair-planner-20260828-114310.md
RELATED_CONTEXT: intg-substep1/PLAN-REVIEW-pair-implementer-20260828-113259.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep1-20260827.md; ../../.github/workflows/s2-harness.yml
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — three narrow pair-Planner-owned Linux-topology repairs remain; no sealed or product byte and no operator decision is implicated
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: intg-consent-fabric-plan
DESIGN_LOCK_ID: m3-addendum-6-c41d015f-lock-20260825
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: intg-substep1-plan-20260827 @ sha256 c89e408adf21cc0b939b8ce9b984f99b217f5d51cf106dbda46fb08d87d7c721
REVIEWED_PLAN: docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep1-20260827.md at commit ceb1ae6c7e885ada26ed135fc929c368dd7b1b3e, sha256 c89e408adf21cc0b939b8ce9b984f99b217f5d51cf106dbda46fb08d87d7c721
BASE: main@02b51435a5b50363df7f595dd827af107424b0c3
BRANCH: intg/consent-fabric@3cd31e4823d40c1c9ea020fcb51917618368533b — verified clean and untouched
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: master.master-planner, master.master-reviewer, m-3.implementer
SUBJECT: MUST-REVISE exact c89e408a revision 9 — writable transition, privilege split, and retained result ledger close; move checksum-file creation wholly host-side, provide a container-visible exact Git source, and enumerate the bare-Ubuntu dependency install before fresh Task-5 dispatch

## Verdict

MUST-REVISE at exact SHA-256 `c89e408adf21cc0b939b8ce9b984f99b217f5d51cf106dbda46fb08d87d7c721`.

Revision 9 correctly narrows Task 5 Step 3 into host transport, root provision, writable transition, and non-root suite phases while preserving the complete pin, host-only credential boundary, no-short-circuit result ledger, and clean candidate `3cd31e4`. Three literal execution defects remain. Each is local to Step 3; no product, workflow, sealed-design, or earlier closed plan surface needs to change.

## Closed revision-9 surfaces

### R9-C1 — writable-output ownership closes

Phase T now makes `/work` the writable ephemeral tree, receipts its candidate HEAD as `3cd31e4823d40c1c9ea020fcb51917618368533b`, places `build/ci`, `.venv-harness`, and both XML outputs below `/work`, and leaves the host candidate byte-clean.

### R9-C2 — privilege and measurement ownership closes in intent

Phase R is explicitly root without `sudo`; Phase S explicitly drops to non-root, raises that runuser context's `nofile` soft limit to its inherited hard limit before measurement, and preserves every required per-stage result plus the aggregate failure rule.

### R9-C3 — credential boundary and earlier proof contracts remain closed

Authenticated `gh` transport remains host-only, with zero token passage, echo, persistence, or evidence inclusion. The complete eight-asset pin, package/version/architecture transcript, include/isatty command bytes, Tasks 1-4, 18-path fence, STOP-1 bytes, and accepted implementation-complete status are unchanged.

## Blocking findings

### R9-F1 — the declared read-only asset phase still executes a canonical write

Phase H says it replaces **exactly** canonical lines 141-147 and nothing else. Phase R says it executes lines 148-193 semantics against the read-only asset bind. But workflow lines 149-150 derive and write `"$LLVM_MIRROR_DIR/SHA256SUMS"`, and line 151 consumes that file. Line 150 cannot succeed on the declared read-only bind. Phase H's separate statement that the host verifies every SHA is semantically replacing lines 149-151 too, contradicting the exact replacement boundary.

Required successor: make Phase H explicitly own canonical lines 141-151, including generation of `SHA256SUMS` and the strict all-eight check before the directory is mounted read-only, and begin Phase R at the first read-only-safe operation (line 153); or copy the bound assets/manifest into named writable container scratch and state the exact line mapping. Preserve the host-only credential boundary.

### R9-F2 — `/src-ro` is a linked worktree whose Git metadata is absent in the container

The candidate's `.git` file is `gitdir: /Users/jack/Programming/bivpak/.git/worktrees/bivpak-intg-consent-fabric`. A disposable `ubuntu:24.04 --platform linux/amd64` probe mounting only the candidate read-only at `/src-ro` reports that absolute target is not visible. Consequently `git clone --branch intg/consent-fabric /src-ro /work` cannot recognize `/src-ro` as a repository in the declared topology; the proposed HEAD receipt is unreachable.

Required successor: provide a container-visible exact Git source and state its mount/clone command. One valid topology is a read-only bind of the main repository/common Git metadata at `/repo-ro`, followed by `git clone --no-hardlinks --branch intg/consent-fabric /repo-ro /work` and exact HEAD verification. An independently prepared host clone/archive is also acceptable if the plan specifies an equally strong exact-tree receipt. Do not rely on the linked worktree's host-absolute `.git` pointer.

### R9-F3 — “the canonical apt set minus tidy debs” is undefined for bare Ubuntu 24.04

The selected image is bare `ubuntu:24.04`, not a GitHub-hosted runner. A fresh amd64 probe reports `git=absent`, `cmake=absent`, `c++=absent`, `python3=absent`, and `ninja=absent` (`runuser` alone is present). The repository contains no named canonical base apt set for this topology, while the workflow installs only `ca-certificates` plus the pinned tidy debs because its hosted runner already supplies build tools. Thus Phase R cannot clone, configure, build, create the harness venv, or run the suite as written.

Required successor: enumerate the exact root provisioning command/package list needed in bare Ubuntu 24.04 for clone, CMake configure/build, Python harness setup, and the canonical suite, or bind it to an exact checked-in provisioning script. Capture that base-provision rc distinctly in the retained provision result. “Canonical apt set” without an executable source is insufficient.

## Preserved scope and gates

- Preserve R9-C1..C3 and every earlier closed command/result contract.
- Successor scope is Task 5 Step 3 plan text only. No candidate source, test, CMake, workflow, sealed-design, or Tasks 1-4 edit is authorized.
- No implementation token is present or consumed. No merge, push, PR, remote CI, publication, deployment, or release authority exists; the release hold remains absolute.
- A fresh exact-hash delta PLAN-REVIEW remains required before any Task-5 implementation dispatch.

## Escalation scan

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: yes — host GitHub credentials must remain host-only under the preserved boundary
- migration/backfill/destructive-write/canonical-data-repair: no — review-only
- money/inventory/orders/planning/accounting/trust-critical-state: no — no such runtime state
- AI-or-automation-acts-downstream: no — no downstream automation action
- worker/scheduler/queue/retry/async-side-effect: no — no product runtime action
- cross-repo/service-contract/generated-schema/shared-API-event: yes — pdc residual rows remain governing context
- user-visible-control-with-materializer/downstream-consumer: yes — accepted consent fabric remains unwired pending sub-step 2b
- test-runtime-role-mismatch: yes — the current host/root/non-root split still contains an impossible read-only write, an unavailable Git source, and an unstated hosted-runner dependency inheritance
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: yes — Linux verification remains incomplete and no risk is accepted
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: none
- scan_presented_to_operator: no — no downgrade or risk acceptance proposed
- operator_reply_after_scan: none
- valid_waiver: no
WAIVED_RISK_ACCEPTANCE: none — no waiver requested or inferred

## Authority and next action

Pair Planner: issue one exact-hash successor changing only Task 5 Step 3 to close R9-F1..F3. Preserve R9-C1..C3 and every earlier closed command. A fresh delta PLAN-REVIEW remains required before any Task-5 implementation dispatch.

ACTIONS_GIT_REF: read-only review of plan commit ceb1ae6c7e885ada26ed135fc929c368dd7b1b3e at sha256 c89e408adf21cc0b939b8ce9b984f99b217f5d51cf106dbda46fb08d87d7c721; exact workflow-line inspection and disposable linux/amd64 bare-image/linked-worktree visibility probes at clean candidate intg/consent-fabric@3cd31e4823d40c1c9ea020fcb51917618368533b; this review submits through the intg daemon; no product/plan/workflow implementation edit claimed
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
