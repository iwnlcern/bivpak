## PLAN-REVIEW — MUST-REVISE revision 7 at exact 3b2a412b: the two fence-command repairs close, but the Linux proof instrument remains non-executable and can mask red

ROLE: Pair Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: must-revise
DISPATCH_ID: intg-substep1-plan-review-6
PARENT_DISPATCH_ID: intg-substep1-plan
IN_REPLY_TO: intg-substep1/PLAN-pair-planner-20260828-050436.md
RELATED_CONTEXT: intg-substep1/SITREP-pair-implementer-20260828-045956.md; intg-substep1/PLAN-REVIEW-pair-implementer-20260828-011234.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep1-20260827.md; ../../../pdc/master/RESIDUALS.md; ../../.github/workflows/s2-harness.yml
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — all surviving findings are narrow pair-Planner-owned Task-5 proof-instrument repairs; no sealed/product byte or operator decision is implicated
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: intg-consent-fabric-plan
DESIGN_LOCK_ID: m3-addendum-6-c41d015f-lock-20260825
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: intg-substep1-plan-20260827 @ sha256 3b2a412b16bc9a168cc0a6d0d923ed008f5ebdc52798f71c5882d45cfee12823
REVIEWED_PLAN: docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep1-20260827.md at commit 9d29fbecfa7c8752d59338611e94a84de1e52365, sha256 3b2a412b16bc9a168cc0a6d0d923ed008f5ebdc52798f71c5882d45cfee12823
BASE: main@02b51435a5b50363df7f595dd827af107424b0c3
BRANCH: intg/consent-fabric@3cd31e4823d40c1c9ea020fcb51917618368533b — verified clean and untouched
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: master.master-planner, master.master-reviewer, m-3.implementer
SUBJECT: MUST-REVISE exact 3b2a412b revision 7 — include and isatty repairs verified green; repair only the pinned-tidy locator, local provisioning route, and no-short-circuit result ledger before a fresh Task-5 dispatch

## Verdict

MUST-REVISE at exact SHA-256 `3b2a412b16bc9a168cc0a6d0d923ed008f5ebdc52798f71c5882d45cfee12823`.

The revision is correctly limited to the three declared Task-5 surfaces: `d286a0df..3b2a412b` changes one plan file by 8 insertions and 3 deletions, and candidate `intg/consent-fabric@3cd31e4` is clean and unchanged. The two command-defect repairs close. The new Linux paragraph still has three execution-proof defects, all locally repairable without moving any product byte.

## Closed delta surfaces

### R7-C1 — trailing-slash include fence closes

At candidate `3cd31e4`, the revised literal command `git grep -n '#include "core/repo/' -- 'src' ':!src/core/repo'` returns no matches with rc=1, and its following `test $? -eq 1` returns rc=0. It no longer prefix-matches the four legitimate `core/report` includes while retaining the intended product-to-engine include fence.

### R7-C2 — token-level isatty census closes

At candidate `3cd31e4`, `grep -o 'isatty' src/cli/url_consent.cpp | wc -l` yields 2, its numeric gate returns rc=0, and the fixed-string conjunction witness returns rc=0. The revised count and the required one-line expression now agree.

### R7-C3 — residual attribution language is correctly non-waiving

`pdc/master/RESIDUALS.md` R-4.35 names the observed mutation-adversary family and prohibits closing it as environmental; R-4.36 retains the m-4-owned correctness question; R-4.38 prohibits citing the stale count gate as merge-readiness. Revision 7 preserves those distinctions and still withholds Linux-green, verification-complete, and merge-ready claims.

## Blocking findings

### R7-F1 — the pinned-tidy source range ends inside an open shell block

Task 5 cites candidate `.github/workflows/s2-harness.yml:114-184` as the canonical provisioning recipe. At the bound candidate bytes, line 183 opens `test ... || {`, line 184 is only its diagnostic `echo`, lines 185-186 close the block, and lines 187-193 perform and verify the actual `clang-tidy-22 --version` major-22 probe. Extracting the cited executable body through line 184 and running `bash -n` returns rc=2, `syntax error: unexpected end of file`.

Required successor: cite the complete immutable candidate step, at least `3cd31e4823d40c1c9ea020fcb51917618368533b:.github/workflows/s2-harness.yml:114-193`, or name the whole YAML step by commit/blob identity. The executed transcript must include all eight checksum/package/version/architecture checks and the major-22 binary probe.

### R7-F2 — `WITHOUT set -e` neither bypasses the canonical explicit exit nor preserves final failure truth

The canonical full-suite step captures `ctest_rc` at line 211 and `tidy_gate_rc` at line 214, then explicitly executes `exit 1` at line 255 if either is red. Removing or omitting `set -e` does not bypass that explicit exit, so the later Catch2 XML/count step at lines 256-280 still cannot execute after the known-family CTest red. Conversely, merely deleting the explicit exit lets a later green command become the shell's final rc and can falsely green the battery despite earlier red.

Required successor: specify an explicit no-short-circuit result ledger. Capture and retain separate rc values for provision, configure, build, CTest, the tidy XML row gate, `[a6-fabric] --success`, Catch2 XML generation, and the count gate; run every post-CTest evidence command; print every rc/result; then return/report a final aggregate that remains nonzero if any required gate is red. R-4.35 and R-4.38 control attribution and readiness claims only — they must not erase the observed nonzero results.

### R7-F3 — the Actions provisioning step has no executable local-Docker credential/tool route

The required parity target is a bare `ubuntu:24.04 --platform linux/amd64 --init` container. A fresh read-only probe shows `gh=absent` there. On the host, `GITHUB_SERVER_URL`, `GITHUB_REPOSITORY`, and `GH_TOKEN` are all unset; the workflow obtains its `GH_TOKEN` from `${{ github.token }}`, which exists only on a GitHub-hosted Actions run. The authenticated host `gh release view` does confirm that the immutable tag exists with all eight named assets, but the plan does not say how those assets safely reach the disposable container.

Required successor: choose and state a credential-safe local route. Preferred: use authenticated host `gh release download` into a `mktemp -d` directory outside the worktree, verify the manifest there, bind-mount that directory read-only into the container, then repeat the dpkg metadata/install/version and binary-major checks inside it. An alternative may install `gh` in-container and inject a scoped token, but must explicitly prevent token echo, persistence, or inclusion in evidence. Do not trigger remote CI.

## Preserved scope and gates

- No finding reopens Tasks 1-4, their exact four-commit series, the 18-path product fence, the STOP-1 bytes, or the accepted implementation-complete product status.
- The successor is Task-5 proof-instrument text only. Candidate product bytes remain at `3cd31e4`; no source/test/CMake edit is authorized.
- No implementation token is present or consumed. No merge, push, PR, remote CI, publication, deployment, or release authority exists; the release hold remains absolute.

## Escalation scan

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: yes — the currently unstated local mirror-download route would touch host GitHub credentials; the successor must make that route non-leaking
- migration/backfill/destructive-write/canonical-data-repair: no — review-only
- money/inventory/orders/planning/accounting/trust-critical-state: no — no such runtime state
- AI-or-automation-acts-downstream: no — no downstream automation action
- worker/scheduler/queue/retry/async-side-effect: no — no product runtime action
- cross-repo/service-contract/generated-schema/shared-API-event: yes — pdc residual rows remain governing cross-repo context
- user-visible-control-with-materializer/downstream-consumer: yes — accepted consent fabric remains unwired pending later sub-step 2b
- test-runtime-role-mismatch: yes — GitHub-hosted runner provisioning assumptions do not hold in the required bare local Docker topology
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: yes — Linux verification remains incomplete and no risk is accepted by this review
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: none
- scan_presented_to_operator: no — no downgrade or risk acceptance proposed
- operator_reply_after_scan: none
- valid_waiver: no
WAIVED_RISK_ACCEPTANCE: none — no waiver requested or inferred

## Authority and next action

Pair Planner: issue one exact-hash successor changing only Task 5 Step 3 to close R7-F1..F3. Preserve the already-closed include and isatty commands byte-for-byte. A fresh delta PLAN-REVIEW remains required before any new Task-5 implementation dispatch.

ACTIONS_GIT_REF: read-only review of plan commit 9d29fbecfa7c8752d59338611e94a84de1e52365 at sha256 3b2a412b16bc9a168cc0a6d0d923ed008f5ebdc52798f71c5882d45cfee12823; E2 command checks at clean candidate intg/consent-fabric@3cd31e4823d40c1c9ea020fcb51917618368533b; one disposable read-only ubuntu:24.04 gh-presence probe; this review submits through the intg daemon; no product/plan/workflow implementation edit claimed
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
