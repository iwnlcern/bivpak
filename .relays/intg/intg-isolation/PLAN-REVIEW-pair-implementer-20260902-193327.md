## PLAN-REVIEW artifact — MUST-REVISE exact isolation plan revision 5 at e834972b: the immediate pre-commit check is followed by the evidence battery, Linux requires the not-yet-created landed SHA, and the status-delta proof ignores removed inherited entries

ROLE: Pair Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: must-revise
DISPATCH_ID: intg-isolation-plan-review-7
PARENT_DISPATCH_ID: intg-isolation-plan-6
IN_REPLY_TO: intg-isolation/PLAN-pair-planner-20260902-185828.md
RELATED_CONTEXT: intg-isolation/PLAN-REVIEW-pair-implementer-20260902-184706.md; intg-isolation/SITREP-pair-planner-20260902-190629.md; docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-isolation-20260902.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/DESIGN-REVIEW-implementer-20260902-162639.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/DESIGN-REVIEW-master-reviewer-20260902-164129.md; ../../pdc/master/relays/r437-operator-scope-ruling/PLAN-operator-20260902-173858.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/PLAN-master-planner-20260902-173859.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — rev5 remains owner-approved, Master-Reviewer-approved with VP concurrence, and exactly operator-commissioned; the required next act is a pair-planner correction under a fresh PLAN handoff id, followed by a new exact-hash review; all implementation, merge, push, publication, and release gates remain held
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: m3-e2-store-isolation-20260901
DESIGN_OWNER: m-3
DESIGN_LOCK_ID: m3-e2-store-isolation-20260901 @ sha256 637ef197aa9f2ebb8f9a34ab91558d52ae35a71691a8403290a87ad59a84bca6
DESIGN_RECORD_KIND: design-doc
TARGET_DESIGN_COMMIT: a07d84cee5687efb05912567fa58387e61b93317
PLAN_LOCK_ID: intg-isolation-plan-20260902 @ sha256 e834972b69c1eb6d5d6b77cd4b68d3b778bbd8c2e93b7bc5f39065e96eb6bb07
REVIEWED_PLAN: docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-isolation-20260902.md at commit b30b1f7769cff16225729f490124f6534cf2e2a7, sha256 e834972b69c1eb6d5d6b77cd4b68d3b778bbd8c2e93b7bc5f39065e96eb6bb07
TARGET_RELAY_SHA256: ce951cf761aefb201a1986b9124992c25097a61a79667718062c06b1649b53fe
BASE: incoming carrier correctly declares the docs-lane filing head main@3e0fc302df1d4029dec426596e4c39779d022870, which is the carrier commit's direct parent; review performed at main@b30b1f7769cff16225729f490124f6534cf2e2a7; the governed harness, adapters, CLI, pack, envelope, and manifest surfaces remain byte-identical to product pin 46df8f3
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: operator, master.master-planner, master.master-reviewer, m-3.planner, m-3.implementer, m-2.planner
SUBJECT: MUST-REVISE exact e834972b — Task 0, the narrowed stale-instruction predicate, and filing-base provenance are corrected, but Task 3's allegedly immediate pre-commit check precedes four evidence steps, Linux targets a landed SHA that Step 4 has not created, and the status-delta pipeline ignores inherited entries that disappear

## Verdict

MUST-REVISE at exact SHA-256 `e834972b69c1eb6d5d6b77cd4b68d3b778bbd8c2e93b7bc5f39065e96eb6bb07`.

The three requested folds are present. Task 0 now captures the snapshot and `$IMPL_BASE` before any governed write; the stale-instruction predicate is recorded and independently reproduces `L=426`, `rc=1`; and the carrier's `main@3e0fc30` filing base equals commit `b30b1f7`'s direct parent. The product-pin proof remains rc 0, the PLAN handoff id is fresh, and the earlier paired-warning, four-path, and rev5-text regions are unchanged by this revision.

The exact plan is still not executable in document order. Task 3 Step 0 calls itself the immediate pre-commit check with nothing between it and Step 4, yet Steps 1, 2, 2b, and 3 intervene. Step 3 additionally requires a clone of local main at the landed SHA, which does not exist until Step 4 creates the commit. The new status-delta pipeline can also return exactly the four expected paths while an inherited status entry has disappeared. No implementation token may parent to this review.

This is review-only. It authorizes no harness, scenario, product, design, plan, budget, CMake, branch/ref, merge, push, remote CI, publication, deployment, or release action.

## Findings

### F1 — Critical — Task 3 has no executable order satisfying both the immediate pre-commit check and the landed-SHA Linux target

Plan line 361 declares Step 0 to run “immediately before Step 4's commit; nothing else between.” In document order, Step 1's fence transcript, Step 2's macOS build/tests, Step 2b's four real-binary demonstrations, and Step 3's Linux battery all run between Step 0 and Step 4 at line 401. A docs-lane commit can therefore land during that evidence battery without being caught immediately before `git add`/`git commit`; the postcondition detects the wrong parent only after the harness commit has already landed.

The same sequence is impossible for Linux independently: Step 3 requires the parity container to clone local main “at the landed sha with the rev-parse receipt,” but Step 4 is the operation that creates and records that landed SHA. Before Step 4 there is no landed harness commit for Phase T to clone.

State one literal execution order. Put the HEAD/index/full-status equality check directly beside and immediately before staging/commit. Any command requiring the landed SHA, including the Linux clone and post-commit write-set checks, must occur after that SHA exists; alternatively, define a different pre-commit Linux transport whose receipt targets the exact dirty four-path bytes rather than claiming a landed SHA. Do not leave a numbered-order exception implicit.

### F2 — Critical — the status-delta command proves additions only and silently ignores removed inherited state

Task 3 Step 0 claims that the only difference from `status-initial.txt` is the four governed paths, using:

```text
diff <(sort "$EVID/status-initial.txt") <(git status --porcelain | sort) | grep '^>' | sed 's/^> ...//' | sort
```

Filtering only `>` rows discards every `<` row. An inherited entry that was deleted, cleaned, renamed, or otherwise removed from the current status is invisible. An executable counterexample with initial ` M inherited.txt` and current `?? harness/{a,b,c,d}.py` printed exactly the four harness paths and returned rc 0 while the inherited deletion was omitted.

Replace the one-sided projection with full equality: current porcelain status must equal the initial snapshot plus the four exact expected porcelain rows, or prove both directions separately and require the removed-initial set empty. Preserve status codes as well as paths. Run this full check immediately before staging, then retain the exact post-commit equality with the initial snapshot.

## Verified surfaces that carry forward

- Incoming carrier SHA-256 is `ce951cf761aefb201a1986b9124992c25097a61a79667718062c06b1649b53fe`; exact-file v2.9.2 lint is green with historical freshness disabled.
- Plan SHA-256 is `e834972b69c1eb6d5d6b77cd4b68d3b778bbd8c2e93b7bc5f39065e96eb6bb07` at commit `b30b1f7769cff16225729f490124f6534cf2e2a7`. Its parent is the declared filing base `3e0fc302df1d4029dec426596e4c39779d022870`.
- The stale-instruction command reproduced the pasted `L=426`, `rc=1` result on the exact artifact. Its narrowed predicate no longer mistakes historical or current “three” prose for a stale execution instruction.
- The archived root sweep is `57df35acd382f57d33baee583daca3726145e86fe834ce1e8cc2847fa24e48b1`; its report names the `185828` carrier as filed, with no carrier-local fired entry and design-edge class zero, while inherited root-wide findings remain.
- The product-pin command over `harness`, adapters, CLI, envelope, pack, and manifest returned rc 0 at the reviewed head. The rev5 diff hunks touch only constraint 10, new Task 0, Task 3 Step 0, identity/token parentage, lineage, and the self-check section; the paired warning-object and real-product oracle text is unchanged.
- Fresh `intg-isolation-plan-6`, pre-write Task 0, the product/implementation pin separation, four governed paths, rev5 `637ef197` commit text, exact warning-object witness, two grains, seven markers, unchanged budgets, no production mutant knob, one local harness commit maximum, m-3 landed-byte review, and every downstream hold may carry after F1-F2 are corrected.

## Escalation scan

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: yes — the harness must prove ambient agent-store locators are cut without reading real host stores
- migration/backfill/destructive-write/canonical-data-repair: no — review-only
- money/inventory/orders/planning/accounting/trust-critical-state: yes — E2 hermeticity becomes governed merge and publication evidence
- AI-or-automation-acts-downstream: yes — a later token and countgate observations consume this plan
- worker/scheduler/queue/retry/async-side-effect: yes — spawned E2 command environments and real-binary demonstrations are governed
- cross-repo/service-contract/generated-schema/shared-API-event: yes — PDC design governs the commissioned Bivpak harness lane
- user-visible-control-with-materializer/downstream-consumer: no — harness-only design
- test-runtime-role-mismatch: yes — Linux requires a landed SHA before the commit that creates it, and the pre-commit guard is not immediately pre-commit
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: yes — the one-sided status proof can conceal loss of inherited shared-worktree state
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: none — no downgrade or risk acceptance requested
- scan_presented_to_operator: no — the required forward path is a corrected pair plan at the existing exact commissioned design pin
- operator_reply_after_scan: none
- valid_waiver: no
WAIVED_RISK_ACCEPTANCE: none

## Required successor

Do not mint a token from plan `e834972b…`, carrier `185828`, or this review. Reissue under the next fresh PLAN handoff id with one explicit executable order: pre-write Task 0; governed edits and pre-commit tests; a two-sided exact status/HEAD/index proof immediately adjacent to the commit; then every landed-SHA consumer after the commit (or a precisely specified pre-commit Linux transport that does not claim a landed SHA). Preserve the corrected self-check, filing base, warning-object witness, product/implementation pins, four-path fence, and rev5 text. Run exact-file and root-mode measurements on the successor, then request a new exact-hash review with a unique review id parented to that successor.

ACTIONS_GIT_REF: read-only review of plan commit b30b1f7769cff16225729f490124f6534cf2e2a7 at sha256 e834972b69c1eb6d5d6b77cd4b68d3b778bbd8c2e93b7bc5f39065e96eb6bb07; incoming carrier, root-sweep archive, exact task order, live stale-instruction reproduction, executable one-sided-status counterexample, commit parent/base, product-pin proof, exact plan diff hunks, exact-file lint, and current worktree checked; daemon submission and path-scoped review commit only; no harness, scenario, product, design, plan, budget, CMake, branch, merge, push, remote CI, publication, deployment, or release action claimed
RELAY_LINT: exact-file v2.9.2 lint is the daemon submission gate; rendered result, digest, daemon verification, committed bytes, and final worktree will be re-verified; inherited root-mode S4 state remains untouched
FINAL_GIT_STATUS_SHORT:
 M relays/s4/INDEX.md
 M relays/s4/SEATS.md
?? relays/s4/s4-floor-impl/REVIEW-FOLD-IMPLEMENTER-CB2-RECHECK2-TWO-CRITICALS-COMPLETE-PUBLISHED-20260810-185643.md
?? relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV0-20260809-033926.md
?? relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV1-20260809-050934.md
?? relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV2-APPROVE-20260809-053253.md
?? relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV2-APPROVE-LINEAGE-CORRECTION-20260809-061515.md
?? relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV3-MUST-REVISE-20260809-210140.md
?? relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV4-APPROVE-20260809-211611.md
?? relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV5-MUST-REVISE-20260809-230557.md
?? relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV6-APPROVE-20260809-231944.md
?? relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-CARRIER-REV0-20260809-055741.md
?? relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-CARRIER-REV1-20260809-061515.md
?? relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-CARRIER-REV2-APPROVE-20260809-062921.md
?? relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-CARRIER-REV2B-UNIQUE-APPROVE-20260809-141439.md
?? relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-FOLD3-RECEIPT-DETERMINISM-MUST-REVISE-20260810-041555.md
?? relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-FOLD3-RECEIPT-DETERMINISM-R1-APPROVE-20260810-043843.md
?? relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-LENSFOLD-SIX-MUSTFIX-APPROVE-20260810-074840.md
?? relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-MICROFOLD-V1-PROOF-MUST-REVISE-20260810-145556.md
?? relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-MICROFOLD-V1-PROOF-R1-MUST-REVISE-20260810-150633.md
?? relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-MICROFOLD-V1-PROOF-R2-APPROVE-20260810-152645.md
?? relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-CARRIER-COMPLETE-20260809-192358.md
?? relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-CARRIER-DISPATCH-LINEAGE-BLOCKER-20260809-063906.md
?? relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-CARRIER-IMPLEMENTED-E2-BLOCKED-20260809-182853.md
?? relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-FOLD-MF1-MF6-COMPLETE-20260809-220327.md
?? relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-FOLD2-EXTENDED-ROOT-RF1-RF2-COMPLETE-20260810-020857.md
?? relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-FOLD3-COMPLETE-20260810-052656.md
?? relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-FOLD3-DISPATCH-LINEAGE-BLOCKER-20260810-030814.md
?? relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-LENSFOLD-COMPLETE-20260810-092751.md
?? relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-MERGE-BLOCKED-DRAFT-UNSTABLE-20260810-174554.md
?? relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-MICROFOLD-DONE-WITH-CONCERNS-20260810-160710.md
?? relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-PR24-MERGED-STEP4-20260810-184033.md
?? relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-WAVE-A-REVERIFY-STAGE1-INDEPENDENT-STOP-CORROBORATION-20260820-161626.md
?? relays/s4/s4-matrix/SITREP-implementer-20260825-220111.md
?? docs/sprints/2026-08-04-s4-step4/MIGRATION-adt-skills-2.9-20260816.md
