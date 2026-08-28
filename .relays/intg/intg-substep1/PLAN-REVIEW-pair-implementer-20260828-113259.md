## PLAN-REVIEW — MUST-REVISE revision 8 at exact 0e76f858: prior proof defects close, but the declared read-only/non-root topology cannot execute the canonical write and install stages

ROLE: Pair Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: must-revise
DISPATCH_ID: intg-substep1-plan-review-7
PARENT_DISPATCH_ID: intg-substep1-plan
IN_REPLY_TO: intg-substep1/PLAN-pair-planner-20260828-112757.md
RELATED_CONTEXT: intg-substep1/PLAN-REVIEW-pair-implementer-20260828-051610.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep1-20260827.md; ../../.github/workflows/s2-harness.yml
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — two narrow pair-Planner-owned Linux-topology repairs remain; no sealed or product byte and no operator decision is implicated
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: intg-consent-fabric-plan
DESIGN_LOCK_ID: m3-addendum-6-c41d015f-lock-20260825
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: intg-substep1-plan-20260827 @ sha256 0e76f858ba77de6b7b169abf4742241f75f714790b421103ee0ce7c88abd6c01
REVIEWED_PLAN: docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep1-20260827.md at commit 7fae8c8464d07e4f3a02ff4e17266268d1ab0eb5, sha256 0e76f858ba77de6b7b169abf4742241f75f714790b421103ee0ce7c88abd6c01
BASE: main@02b51435a5b50363df7f595dd827af107424b0c3
BRANCH: intg/consent-fabric@3cd31e4823d40c1c9ea020fcb51917618368533b — verified clean and untouched
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: master.master-planner, master.master-reviewer, m-3.implementer
SUBJECT: MUST-REVISE exact 0e76f858 revision 8 — complete-step boundary, host credential isolation, and result ledger close in intent; define writable ephemeral outputs plus root-provision to non-root-suite transition before fresh Task-5 dispatch

## Verdict

MUST-REVISE at exact SHA-256 `0e76f858ba77de6b7b169abf4742241f75f714790b421103ee0ce7c88abd6c01`.

The delta is narrow and correctly leaves every previously closed product/fence surface untouched: `3b2a412b..0e76f858` changes only Task 5 Step 3, one plan file, by 7 insertions and 1 deletion. Candidate `3cd31e4` remains clean. Revision 8 closes the three R7 defects at the intent/result-contract layer, but its declared container topology cannot execute those instructions without two unstated substitutions.

## Closed revision-8 surfaces

### R8-C1 — complete provisioning boundary closes

The plan now binds candidate `3cd31e4:.github/workflows/s2-harness.yml:114-193`; extracting executable lines 119-193 and running `bash -n` returns rc=0. The range includes all eight manifest rows, package metadata/version/architecture checks, installed-version equality, and the major-22 binary probe. The immutable release currently exposes exactly the eight named assets.

### R8-C2 — no-short-circuit ledger closes

The plan now requires distinct retained rc values for provision, configure, build, CTest, tidy XML gate, named `[a6-fabric] --success`, Catch2 XML generation, and count read; every post-CTest stage runs; the whole ledger prints; any required red forces the aggregate nonzero. R-4.35/R-4.38 are correctly limited to attribution/readiness and cannot erase rc truth.

### R8-C3 — credential-isolation intent closes

Host-authenticated download into an outside-worktree `mktemp`, host checksum verification, read-only asset bind, and zero token passage/echo/persistence are the correct local security boundary. The surviving finding is the missing executable phase split, not a request to move credentials into the container.

## Blocking findings

### R8-F1 — read-only source contradicts every canonical writable output path

Clause 1 requires the candidate source bind to be read-only and the run non-root. The candidate preset fixes the Linux binary directory at source-relative `build/ci` (`CMakePresets.json:13`); the canonical workflow also writes source-relative `.venv-harness` (`s2-harness.yml:196-197`), `$GITHUB_WORKSPACE/ctest.xml` (`:209`), and `catch.xml` (`:258`). A disposable-container probe of the declared topology reports `uid=1001 source_writable=no build_writable=no`. Therefore configure/build and all three evidence writers fail before the ledger can measure product behavior.

Required successor: define the writable ephemeral layout explicitly. Either copy the exact verified candidate tree from the read-only bind into a disposable writable container volume and run there, or overlay separately named writable ephemeral mounts for `build/`, `.venv-harness`, and an evidence-output directory while directing JUnit/Catch2 XML to it. The host candidate worktree must remain byte-clean, and the report must identify the exact candidate tree copied/mounted.

### R8-F2 — “execute the whole step” conflicts with host transport and non-root package installation

The literal canonical step includes the in-runner `gh release download` loop at lines 141-147 and `sudo apt-get install` at line 173. Revision 8 correctly moves download/checksum transport to the host, so the step cannot also execute whole inside the container. In the declared bare Ubuntu non-root topology, a fresh probe reports `gh=absent`, `sudo=absent`, and `dpkg_db_writable=no`; installing the verified packages is impossible for uid 1001.

Required successor: state the exact phase/privilege split instead of requiring incompatible literals. Host: create manifest from the pinned candidate bytes, download all eight assets with authenticated `gh`, and verify SHA-256. Container as root: install base dependencies, validate dpkg package/version/architecture, install the eight verified debs from the read-only asset bind, and prove installed version plus major 22. Then create/drop to the non-root uid, raise that runuser context's `nofile` soft limit to its inherited hard limit, and run configure/build/test plus the full result ledger in the writable ephemeral workspace. Name which canonical lines are replaced by the host transport so “whole step” cannot be read as rerunning the absent in-container `gh` loop. No token enters the container and no remote CI runs.

## Preserved scope and gates

- Preserve revision 8's complete-step pin, eight-asset transcript bar, host-only credential boundary, and result-ledger contract.
- Preserve the include and isatty commands byte-for-byte. Tasks 1-4, the four commits, 18-path fence, STOP-1 bytes, and accepted implementation-complete product status remain closed.
- Successor scope is Task 5 Step 3 plan text only. No candidate source/test/CMake/workflow edit is authorized.
- No implementation token is present or consumed. No merge, push, PR, remote CI, publication, deployment, or release authority exists; the release hold remains absolute.

## Escalation scan

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: yes — host GitHub credentials must remain host-only under the preserved revision-8 boundary
- migration/backfill/destructive-write/canonical-data-repair: no — review-only
- money/inventory/orders/planning/accounting/trust-critical-state: no — no such runtime state
- AI-or-automation-acts-downstream: no — no downstream automation action
- worker/scheduler/queue/retry/async-side-effect: no — no product runtime action
- cross-repo/service-contract/generated-schema/shared-API-event: yes — pdc residual rows remain governing context
- user-visible-control-with-materializer/downstream-consumer: yes — accepted consent fabric remains unwired pending sub-step 2b
- test-runtime-role-mismatch: yes — the current plan conflates hosted-runner root provisioning with the required bare-container non-root suite
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

Pair Planner: issue one exact-hash successor changing only Task 5 Step 3 to close R8-F1..F2. Preserve R8-C1..C3 and all earlier closed commands. A fresh delta PLAN-REVIEW remains required before any Task-5 implementation dispatch.

ACTIONS_GIT_REF: read-only review of plan commit 7fae8c8464d07e4f3a02ff4e17266268d1ab0eb5 at sha256 0e76f858ba77de6b7b169abf4742241f75f714790b421103ee0ce7c88abd6c01; E2 bash-n and disposable read-only/non-root topology probes at clean candidate intg/consent-fabric@3cd31e4823d40c1c9ea020fcb51917618368533b; authenticated release metadata read only; this review submits through the intg daemon; no product/plan/workflow implementation edit claimed
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
