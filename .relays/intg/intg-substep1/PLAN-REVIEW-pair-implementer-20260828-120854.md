## PLAN-REVIEW — MUST-REVISE revision 10 at exact 3acc283b: prior three mechanisms close, but harness setup is unassigned, the root WSL probe is vacuous, and the locked provision command remains self-amending

ROLE: Pair Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: must-revise
DISPATCH_ID: intg-substep1-plan-review-9
PARENT_DISPATCH_ID: intg-substep1-plan
IN_REPLY_TO: intg-substep1/PLAN-pair-planner-20260828-120027.md
RELATED_CONTEXT: intg-substep1/PLAN-REVIEW-pair-implementer-20260828-115204.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep1-20260827.md; ../../.github/workflows/s2-harness.yml
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — three narrow pair-Planner-owned proof-instrument repairs remain; no sealed or product byte and no operator decision is implicated
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: intg-consent-fabric-plan
DESIGN_LOCK_ID: m3-addendum-6-c41d015f-lock-20260825
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: intg-substep1-plan-20260827 @ sha256 3acc283bd9f346d9a7a11e8ce304fc5035a9329de300de4056d8ddcf3b952000
REVIEWED_PLAN: docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep1-20260827.md at commit 90dcde34b403b4a647d0e26cdd6da22fbf02fb28, sha256 3acc283bd9f346d9a7a11e8ce304fc5035a9329de300de4056d8ddcf3b952000
BASE: main@02b51435a5b50363df7f595dd827af107424b0c3
BRANCH: intg/consent-fabric@3cd31e4823d40c1c9ea020fcb51917618368533b — verified clean and untouched
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: master.master-planner, master.master-reviewer, m-3.implementer
SUBJECT: MUST-REVISE exact 3acc283b revision 10 — host checksum ownership, main-repo clone, and enumerated base install close; explicitly run harness dependency setup as non-root, test WSL writability as that same uid, and fail closed instead of amending the locked package set during execution

## Verdict

MUST-REVISE at exact SHA-256 `3acc283bd9f346d9a7a11e8ce304fc5035a9329de300de4056d8ddcf3b952000`.

Revision 10 closes all three revision-9 mechanisms at their stated boundaries: host ownership now includes the checksum-file write, the container can clone the exact candidate branch from the read-only main repository, and the enumerated bare-Ubuntu package command installs successfully. The executable sequence still omits one canonical workflow stage, performs one proof as the wrong uid, and authorizes an unreviewed instrument amendment after failure.

## Closed revision-10 surfaces

### R10-C1 — asset ownership and read-only handoff close

Phase H now owns workflow lines 141-151 whole, including `SHA256SUMS` generation and strict checking before the asset directory becomes read-only. Phase R begins at line 153, the first read-only-safe operation.

### R10-C2 — exact-tree clone source closes

A disposable `ubuntu:24.04 --platform linux/amd64` probe with the main repository mounted read-only at `/repo-ro` executed `git clone --no-hardlinks --branch intg/consent-fabric /repo-ro /work` successfully and receipted `/work` at exact HEAD `3cd31e4823d40c1c9ea020fcb51917618368533b`. The linked-worktree pointer trap is correctly excluded.

### R10-C3 — enumerated base install closes its prior ambiguity

The exact revision-10 apt command completed with `apt_update_rc=0` and `apt_install_rc=0` in a disposable bare amd64 Ubuntu 24.04 container. It supplied `git`, `g++`, `make`, `cmake`, `python3`, `pip`, `objcopy`, `zstd`, and `runuser`. Preserve this enumeration and its distinct ledger result, subject only to R10-F3's fail-closed correction.

## Blocking findings

### R10-F1 — canonical harness dependency setup is not assigned to any phase

The workflow's lines 194-197 create `.venv-harness` and install `harness/requirements.lock` before configure. Revision 10 assigns 141-151 to Phase H, 153-193 plus 198-202 to Phase R, clone/ownership to Phase T, and configure/build/tests to Phase S; no phase executes 194-197. Merely naming `.venv-harness` as an output and installing system Python packages does not install `pytest`, `jsonschema`, or Python `zstandard` into the interpreter selected by `harness/CMakeLists.txt:12-20`.

The exact base-install probe also reports `python=absent` and `python3=/usr/bin/python3`, so literal workflow line 196 (`python -m venv`) returns command-not-found in this topology.

Required successor: after `/work` is writable and owned by the suite user, explicitly run the harness setup as that user and before CMake configure. Use `python3 -m venv /work/.venv-harness` followed by `/work/.venv-harness/bin/python -m pip install -r /work/harness/requirements.lock`, or add and justify `python-is-python3` if preserving the literal `python` command. Give this stage its own retained rc and include it in the final aggregate.

### R10-F2 — the WSL writability probe runs as root before the measurement user exists

Phase R, still root, owns `mkdir`, chown “to the suite uid,” and the line-202 writability probe; Phase T only afterward creates the non-root uid. The uid/gid is not numerically fixed before the chown, and a root `test -w` cannot prove suite-user access. A disposable negative control with `/mnt/c/tmp` mode 0700 and root ownership reports `root_probe_rc=0` while `runuser -u suite -- test -w /mnt/c/tmp` reports `suite_probe_rc=1`.

Required successor: create/fix the suite uid and gid before fixture ownership, then perform the `/mnt/c/tmp` writability probe under that exact non-root identity (for example with `runuser`) after chown and before configure/test. Retain a separate fixture-provision/probe rc in the aggregate. Root may create/chown the path; root must not be the identity that proves its writability.

### R10-F3 — the missing-package amendment rule changes the approved instrument after a red

Revision 10 says that if a later stage fails for a missing package, the package addition is recorded beside an “amended command.” Recording the mutation is better than silence, but it does not preserve the locked plan or the original result ledger: the approved package set can change during execution, and a rerun can replace rather than retain the first red.

Required successor: freeze the approved package command. If a missing-package failure occurs, retain that stage's nonzero result, let the aggregate fail, and return a blocker with the proposed package delta for a fresh exact-hash plan review. Any exploratory amended rerun must be labeled separate evidence and cannot satisfy the approved Task-5 battery.

## Preserved scope and gates

- Preserve R10-C1..C3, revision 9's writable `/work`, privilege/nofile/result-ledger contracts, host-only credential boundary, and every earlier closed command.
- Successor scope is Task 5 Step 3 plan text only. No candidate source, test, CMake, workflow, sealed-design, or Tasks 1-4 edit is authorized.
- No implementation token is present or consumed. No merge, push, PR, remote CI, publication, deployment, or release authority exists; the release hold remains absolute.
- A fresh exact-hash delta PLAN-REVIEW remains required before any Task-5 implementation dispatch.

## Escalation scan

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: yes — host GitHub credentials remain host-only under the preserved boundary
- migration/backfill/destructive-write/canonical-data-repair: no — review-only
- money/inventory/orders/planning/accounting/trust-critical-state: no — no such runtime state
- AI-or-automation-acts-downstream: no — no downstream automation action
- worker/scheduler/queue/retry/async-side-effect: no — no product runtime action
- cross-repo/service-contract/generated-schema/shared-API-event: yes — pdc residual rows remain governing context
- user-visible-control-with-materializer/downstream-consumer: yes — accepted consent fabric remains unwired pending sub-step 2b
- test-runtime-role-mismatch: yes — harness setup is absent and the root identity currently performs a non-root writability proof
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: yes — a self-amending package instrument would accept unreviewed verification drift
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: none
- scan_presented_to_operator: no — no downgrade or risk acceptance proposed
- operator_reply_after_scan: none
- valid_waiver: no
WAIVED_RISK_ACCEPTANCE: none — no waiver requested or inferred

## Authority and next action

Pair Planner: issue one exact-hash successor changing only Task 5 Step 3 to close R10-F1..F3. Preserve R10-C1..C3 and every earlier closed command. A fresh delta PLAN-REVIEW remains required before any Task-5 implementation dispatch.

ACTIONS_GIT_REF: read-only review of plan commit 90dcde34b403b4a647d0e26cdd6da22fbf02fb28 at sha256 3acc283bd9f346d9a7a11e8ce304fc5035a9329de300de4056d8ddcf3b952000; disposable linux/amd64 base-install, exact-clone, command-availability, and root-vs-suite writability probes at clean candidate intg/consent-fabric@3cd31e4823d40c1c9ea020fcb51917618368533b; this review submits through the intg daemon; no product/plan/workflow implementation edit claimed
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
