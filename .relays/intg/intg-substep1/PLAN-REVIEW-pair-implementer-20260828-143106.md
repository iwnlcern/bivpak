## PLAN-REVIEW — APPROVE revision 11 at exact 6e179f2b: the Task-5 Linux proof sequence is executable and fail-closed; implementation dispatch remains held by the plan's commissioning-chain clearing-sweep gate

ROLE: Pair Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: approve
DISPATCH_ID: intg-substep1-plan-review-10
PARENT_DISPATCH_ID: intg-substep1-plan
IN_REPLY_TO: intg-substep1/PLAN-pair-planner-20260828-135056.md
RELATED_CONTEXT: intg-substep1/PLAN-REVIEW-pair-implementer-20260828-120854.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep1-20260827.md; ../../.github/workflows/s2-harness.yml
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — this is plan approval only; the already-owned master commissioning-chain repair and archived clearing sweep remain mandatory before any implementation dispatch
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: intg-consent-fabric-plan
DESIGN_LOCK_ID: m3-addendum-6-c41d015f-lock-20260825
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: intg-substep1-plan-20260827 @ sha256 6e179f2b99faf86770d97f865e7e2e9de4b8446b2e7fa62cdaabc3eb3a55f91e
REVIEWED_PLAN: docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep1-20260827.md at commit dc63e08c040c57474649bd77953771ec6e3b8926, sha256 6e179f2b99faf86770d97f865e7e2e9de4b8446b2e7fa62cdaabc3eb3a55f91e
BASE: main@02b51435a5b50363df7f595dd827af107424b0c3
BRANCH: intg/consent-fabric@3cd31e4823d40c1c9ea020fcb51917618368533b — verified clean and untouched
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: master.master-planner, master.master-reviewer, m-3.implementer
SUBJECT: APPROVE exact 6e179f2b revision 11 — R10-F1..F3 close under executable amd64 probes; preserve all proof and scope contracts; do not issue or consume the fresh Task-5 token until the plan's archived commissioning-chain clearing-sweep predicate is satisfied

## Verdict

APPROVE at exact SHA-256 `6e179f2b99faf86770d97f865e7e2e9de4b8446b2e7fa62cdaabc3eb3a55f91e`.

Revision 11 closes R10-F1..F3 without changing product bytes, Tasks 1-4, locked design, fences, or accepted implementation-complete status. The four-phase Task-5 Linux plan now gives every privileged, writable, credentialed, and measured operation one explicit owner and retains every required result in a fail-closed aggregate.

This approval is PLAN-REVIEW authority only. It is not an implementation token, verification-complete claim, merge grant, or release grant.

## Revision-11 closures

### R11-C1 — harness dependency stage is explicit and identity-correct

Phase S now runs `python3 -m venv /work/.venv-harness` and installs the locked requirements as the suite user before configure, with a distinct retained rc. The `python3` substitution is correctly justified by the bare image's absence of `python`, and the plan prevents `harness/CMakeLists.txt:12-20` from silently selecting an unprepared system interpreter.

### R11-C2 — suite identity and WSL fixture proof are ordered correctly

Phase T pins uid/gid 1001, creates that identity before ownership changes, clones and chowns `/work`, creates/chowns `/mnt/c`, then executes `runuser -u suite -- test -w /mnt/c/tmp`. Root performs only the privileged creation/chown operations; the actual measurement identity proves writability. The fixture stage has its own retained rc.

### R11-C3 — package provisioning is frozen and fail-closed

The enumerated apt command is now immutable for this plan digest. A later missing-package result remains red, fails the aggregate, and returns a blocker plus proposed exact delta for fresh review. An exploratory amended rerun cannot satisfy the approved battery.

## Executable proof

A disposable `ubuntu:24.04 --platform linux/amd64 --init` probe with the main repository read-only at `/repo-ro` executed the revision-11 transition and dependency sequence. Observed results:

```text
apt_update_rc=0
apt_install_rc=0
groupadd_rc=0
useradd_rc=0
clone_rc=0
head=3cd31e4823d40c1c9ea020fcb51917618368533b
chown_work_rc=0
mkdir_fixture_rc=0
chown_fixture_rc=0
fixture_probe_rc=0
nofile_before=1024
nofile_hard=1048576
lift_rc=0
nofile_after=1048576
venv_rc=0
pip_rc=0
import_rc=0
suite_rc=0
```

The import probe loaded `pytest`, `jsonschema`, and `zstandard` from `/work/.venv-harness`. This proves the repaired topology and dependency stage, not the still-unexecuted full Task-5 product battery.

## Preserved plan contract

- Phase H owns host-authenticated download plus lines 149-151 checksum generation/check before the read-only mount; no credential enters the container.
- Phase R uses the frozen base set and complete pinned eight-deb validation/install/probe semantics.
- Phase T clones the exact local branch from the read-only main repository with `--no-hardlinks` and verifies exact HEAD; the linked candidate worktree is never used as the Git source.
- Phase S lifts non-root `nofile`, retains distinct base/deb/fixture/venv/configure/build/CTest/tidy/a6/Catch2/count results, runs every post-CTest evidence stage, prints the ledger, and returns nonzero for any required red.
- The include/isatty commands, Tasks 1-4, four product commits, 18-path fence, STOP-1 bytes, R-4.35/R-4.38 attribution boundaries, and all out-of-scope lines remain unchanged.

## Remaining gate — approval does not lift it

The plan artifact's Open Gate 2 remains controlling: no approval-consuming implementation dispatch may issue before master files the refreshed commissioning-chain members and an archived clearing sweep demonstrates that the rule-3a/3d family is gone with only the covered W-3 red remaining. The revision-11 archived sweep still shows the commissioning-chain residue; therefore the relay sentence promising a fresh token “on your approve” is constrained by the plan's own stronger explicit hold.

Pair Planner may record this approval now. It must wait for and verify the named clearing-sweep evidence before issuing the fresh `intg-substep1-impl-2` dispatch parented to this approving review. Any change to plan bytes requires another exact-hash PLAN-REVIEW.

No product implementation, Task-5 verification battery, merge, push, PR, remote CI, publication, deployment, or release is authorized or claimed here.

## Escalation scan

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: yes — host GitHub credentials remain host-only under the approved boundary
- migration/backfill/destructive-write/canonical-data-repair: no — review-only
- money/inventory/orders/planning/accounting/trust-critical-state: no — no such runtime state
- AI-or-automation-acts-downstream: no — no downstream automation action
- worker/scheduler/queue/retry/async-side-effect: no — no product runtime action
- cross-repo/service-contract/generated-schema/shared-API-event: yes — pdc residual rows remain governing context
- user-visible-control-with-materializer/downstream-consumer: yes — accepted consent fabric remains unwired pending sub-step 2b
- test-runtime-role-mismatch: no — root provisioning and suite-user measurement are now separated and directly probed
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: yes — Linux battery and commissioning-chain clearance remain future gates, not waived
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: none
- scan_presented_to_operator: no — no downgrade or risk acceptance proposed
- operator_reply_after_scan: none
- valid_waiver: no
WAIVED_RISK_ACCEPTANCE: none — no waiver requested or inferred

## Authority and next action

Pair Planner: record the exact-digest approval, preserve the plan bytes, and keep implementation held until the plan's commissioning-chain clearing-sweep predicate is proven. After that independent gate closes, issue the fresh Task-5 dispatch parented to this review. No additional plan review is required unless plan bytes change.

ACTIONS_GIT_REF: read-only review of plan commit dc63e08c040c57474649bd77953771ec6e3b8926 at sha256 6e179f2b99faf86770d97f865e7e2e9de4b8446b2e7fa62cdaabc3eb3a55f91e; disposable linux/amd64 exact base-install, pinned-identity, exact-clone, WSL suite-user probe, nofile-lift, venv/install/import sequence at clean candidate intg/consent-fabric@3cd31e4823d40c1c9ea020fcb51917618368533b; exact plan relay lint and daemon verification; this review submits through the intg daemon; no product/plan/workflow implementation edit claimed
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
