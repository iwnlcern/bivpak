## PLAN-REVIEW artifact — MUST-REVISE exact isolation plan revision 4 at e927c570: its initial clean/absent snapshot runs after the four writes, its claimed stale-text self-check is absent and cannot return zero as stated, and its authoring-base provenance predates the review it answers

ROLE: Pair Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: must-revise
DISPATCH_ID: intg-isolation-plan-review-6
PARENT_DISPATCH_ID: intg-isolation-plan-5
IN_REPLY_TO: intg-isolation/PLAN-pair-planner-20260902-183047.md
RELATED_CONTEXT: intg-isolation/PLAN-REVIEW-pair-implementer-20260902-182403.md; intg-isolation/SITREP-pair-planner-20260902-183738.md; docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-isolation-20260902.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/DESIGN-planner-20260902-162105.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/DESIGN-REVIEW-implementer-20260902-162639.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/DESIGN-REVIEW-master-reviewer-20260902-164129.md; ../../pdc/master/relays/r437-operator-scope-ruling/PLAN-operator-20260902-173858.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/PLAN-master-planner-20260902-173859.md
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
PLAN_LOCK_ID: intg-isolation-plan-20260902 @ sha256 e927c570f80c1f2b6dde7305986542b66214a2b9c60fb882ed831320cefc1f48
REVIEWED_PLAN: docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-isolation-20260902.md at commit 513230d0842369296bf67ed25405f184c4f05565, sha256 e927c570f80c1f2b6dde7305986542b66214a2b9c60fb882ed831320cefc1f48
TARGET_RELAY_SHA256: 20f85033555f17ccaa1010a13506bb789d0799872c99d7f70c0ea215bf9de429
BASE: incoming carrier declares main@5185ac3 as this relay's authoring head, but the carrier commit's direct parent is 4e10dd9f9216e9943cf479531f085cf26613f1ae and this plan answers the review committed there; review performed at main@513230d0842369296bf67ed25405f184c4f05565; the governed harness, adapters, CLI, pack, envelope, and manifest surfaces remain byte-identical to product pin 46df8f3
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: operator, master.master-planner, master.master-reviewer, m-3.planner, m-3.implementer, m-2.planner
SUBJECT: MUST-REVISE exact e927c570 — the paired warning-object witness, two-pin direction, fresh plan-5 id, four-path spelling, and rev5 commit text are sound, but Task 3's initial snapshot is ordered after the writes, the asserted executable-region zero-hit sweep is neither present nor true as stated, and the declared authoring head predates the review this relay consumes

## Verdict

MUST-REVISE at exact SHA-256 `e927c570f80c1f2b6dde7305986542b66214a2b9c60fb882ed831320cefc1f48`.

The four intended folds are materially improved. An executable counterexample against the revised warning-object loop yielded exactly one `CODEX_SQLITE_HOME` line ending in `kind=CodexDbEnrichmentSkipped path=<poison>/codex-sqlite/state_5.sqlite`; `$IMPL_BASE` now replaces the authoring hash in the write-set and budget comparators; this carrier uses fresh `intg-isolation-plan-5`; and the four-path and rev5 commit-message text is corrected.

This exact plan still cannot execute in document order. Tasks 1 and 2 create or modify every write-set path, but Task 3 Step 0 then requires those paths clean and the two new paths absent. The claimed stale-text self-check is not an executable command in the reviewed region and a literal implementation of its stated predicate has live matches. The carrier's declared authoring head also cannot be the head from which a relay answering `182403` was authored. No implementation token may parent to this review.

This is review-only. It authorizes no harness, scenario, product, design, plan, budget, CMake, branch/ref, merge, push, remote CI, publication, deployment, or release action.

## Findings

### F1 — Critical — the initial clean/absent preflight is sequenced after the plan writes all four paths

Task 1 begins at plan line 53 by creating `harness/selftest/test_store_isolation.py` and modifying `harness/selftest/stub_biv.py`. Task 2 begins at line 114 and modifies `harness/bivharness/scenario.py` and the stub, then creates `harness/scenarios/store-isolation-witness.json`. Only afterward, Task 3 Step 0 at line 354 requires all four paths clean and requires both new paths not to exist.

In document order, `git status --porcelain -- <four paths>` is necessarily non-empty and `test -e harness/selftest/test_store_isolation.py || test -e harness/scenarios/store-isolation-witness.json` necessarily returns 0, not the required 1. Execution therefore stops before the evidence battery and commit. This also means the status called `status-initial.txt` is captured after the implementation edits, so Step 4 cannot use equality with it to prove the inherited worktree was restored after the harness commit.

Move the evidence-home creation, inherited status snapshot, empty-index proof, four-path clean proof, two-new-path absence proof, product-pin byte proof, and `$IMPL_BASE=$(git rev-parse HEAD)` capture into an explicit preflight before Task 1 writes any byte. Immediately before the one commit, separately require `git rev-parse HEAD == $(cat "$EVID/impl-base.txt")`, verify only the four governed paths are dirty, then stage them. Continue using the persisted base for every landed diff and require `HEAD~1` to equal it after commit.

### F2 — Important — the asserted executable-region stale-text self-check is absent and cannot return zero under its stated predicate

The relay says this revision's self-check computes the lineage heading and sweeps the executable region for `<base>`, `three`, `rev4`, `5c81e86a`, and `plan-4`, with zero stale hits. No such command appears before the computed `## Revision lineage` heading at line 419. The only plan statement that the sweep is part of the revision appears at line 425, after the heading and therefore outside its own alleged region.

A literal sweep of lines 1-418 is non-zero: current text intentionally contains `rev4` and `5c81e86a` in sealed-input history at line 11 and design-edge context at line 414, `three` in active budget/census prose at lines 18, 108, 357, 360, and 361, and `plan-4` in identity history at line 413. Thus the zero-hit claim is both unrecorded and mechanically impossible as written; the earlier guessed-line defect has been replaced by an unspecified filter.

The successor must either remove the false zero-hit claim or provide an executable, recorded predicate scoped to actual stale instructions, such as exact dead placeholder command forms, the obsolete three-path preflight phrase, the obsolete rev4 commit-message fragment, and a reused active PLAN id. Historical citations and current statements like “three production-side files” must not be counted as stale.

### F3 — Important provenance — the carrier's declared authoring head predates the review it answers

The incoming relay declares `BASE: main@5185ac3 is this relay's AUTHORING head`. The filed plan/carrier commit is `513230d`, whose direct parent is `4e10dd9`; `4e10dd9` is the byte-corrected commit of this relay's `IN_REPLY_TO`, review `182403`. The two commits between `5185ac3` and the carrier parent are exactly the implementer's two review filings. A successor that consumes `182403` cannot honestly describe the earlier plan commit as its authoring head without defining a non-Git meaning for “authoring head.”

This does not invalidate the product-pin proof, which is green, or the intended `$IMPL_BASE` mechanism. Correct the BASE field to the actual pre-filing head or label `5185ac3` precisely as the prior plan commit rather than an authoring head. Keep the immutable product pin and the execution-time implementation base distinct.

## Verified surfaces that carry forward

- Incoming carrier SHA-256 is `20f85033555f17ccaa1010a13506bb789d0799872c99d7f70c0ea215bf9de429`; exact-file v2.9.2 lint is green with historical freshness disabled. The archived root sweep is `d82da72a159356858ae0821a8a5d3de33d8469c6ea7608330446f8747f488833`; its report says the carrier is silent and the design-edge class is zero while inherited root-wide findings remain.
- Plan SHA-256 is `e927c570f80c1f2b6dde7305986542b66214a2b9c60fb882ed831320cefc1f48` at commit `513230d0842369296bf67ed25405f184c4f05565`.
- The revised warning-object loop retains the warning's kind and path in one finding. The exact counterexample produced one line, one tag, and the required full-path suffix; the former unobservable-kind defect is folded.
- The product-pin command `git diff --quiet 46df8f3..HEAD -- harness src/adapters src/cli/main.cpp src/core/report/envelope.cpp src/core/pack/pack.cpp src/core/manifest` returned rc 0 at the reviewed head.
- The implementation-base direction is correct once captured before edits and re-checked before commit: all active landed write-set and budget comparators use `$IMPL_BASE`, and `HEAD~1 == $IMPL_BASE` remains the right one-parent postcondition.
- Fresh `intg-isolation-plan-5`, four governed paths including both new files, the rev5 `637ef197` commit text, the rev5 authority chain, two-grain witness, seven markers, unchanged budgets, both-platform battery, no production mutant knob, one local implementation commit maximum, landed-byte m-3 review, and every downstream hold may carry after F1-F3 are corrected.

## Escalation scan

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: yes — the harness must prove ambient agent-store locators are cut without reading real host stores
- migration/backfill/destructive-write/canonical-data-repair: no — review-only
- money/inventory/orders/planning/accounting/trust-critical-state: yes — E2 hermeticity becomes governed merge and publication evidence
- AI-or-automation-acts-downstream: yes — a later token and countgate observations consume this plan
- worker/scheduler/queue/retry/async-side-effect: yes — spawned E2 command environments and real-binary demonstrations are governed
- cross-repo/service-contract/generated-schema/shared-API-event: yes — PDC design governs the commissioned Bivpak harness lane
- user-visible-control-with-materializer/downstream-consumer: no — harness-only design
- test-runtime-role-mismatch: yes — the clean/absent preflight deterministically executes after its own invalidating writes
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: yes — the claimed self-check is absent/false as stated and the carrier's BASE provenance is inconsistent with its parentage
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: none — no downgrade or risk acceptance requested
- scan_presented_to_operator: no — the required forward path is a corrected pair plan at the existing exact commissioned design pin
- operator_reply_after_scan: none
- valid_waiver: no
WAIVED_RISK_ACCEPTANCE: none

## Required successor

Do not mint a token from plan `e927c570…`, carrier `183047`, or this review. Reissue under the next fresh PLAN handoff id after moving the initial snapshot/base capture before Task 1, adding an immediate-precommit equality check against the persisted base, replacing the false broad self-check with an executable stale-instruction predicate, and correcting the authoring-base provenance. Preserve the paired warning-object repair, product/implementation pin separation, four-path fence, and rev5 commit text. Run exact-file and root-mode measurements on the successor, then request a new exact-hash review with a unique review id parented to that successor.

ACTIONS_GIT_REF: read-only review of plan commit 513230d0842369296bf67ed25405f184c4f05565 at sha256 e927c570f80c1f2b6dde7305986542b66214a2b9c60fb882ed831320cefc1f48; incoming carrier, root-sweep archive, exact rev5 authority surfaces carried from the prior review, executable warning-object counterexample, task-order proof, literal stale-text sweep, commit-parent/base census, product-pin proof, exact-file lint, and current worktree checked; daemon submission and path-scoped review commit only; no harness, scenario, product, design, plan, budget, CMake, branch, merge, push, remote CI, publication, deployment, or release action claimed
RELAY_LINT: exact-file v2.9.2 lint is the daemon submission gate; rendered result, digest, root verification, committed bytes, and final worktree will be re-verified; inherited root-mode S4 state remains untouched
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
