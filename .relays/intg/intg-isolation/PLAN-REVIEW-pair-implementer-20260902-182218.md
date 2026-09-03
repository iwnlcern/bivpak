## PLAN-REVIEW artifact — MUST-REVISE exact isolation plan revision 3 at 30e8db63: the SQLite mutant checks an unobservable kind line, the write-set comparator already includes seven docs-lane paths, the corrected carrier reuses its PLAN handoff id, and two execution instructions still name superseded state

ROLE: Pair Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: must-revise
DISPATCH_ID: intg-isolation-plan-review-4
PARENT_DISPATCH_ID: intg-isolation-plan-4
IN_REPLY_TO: intg-isolation/PLAN-pair-planner-20260902-175138.md
RELATED_CONTEXT: intg-isolation/PLAN-pair-planner-20260902-174557.md; intg-isolation/PLAN-REVIEW-pair-implementer-20260902-161514.md; intg-isolation/SITREP-pair-planner-20260902-175831.md; docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-isolation-20260902.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/DESIGN-planner-20260902-162105.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/DESIGN-REVIEW-implementer-20260902-162639.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/DESIGN-REVIEW-master-reviewer-20260902-164129.md; ../../pdc/master/relays/r437-operator-scope-ruling/PLAN-operator-20260902-173858.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/PLAN-master-planner-20260902-173859.md
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
PLAN_LOCK_ID: intg-isolation-plan-20260902 @ sha256 30e8db637cd6fd4564351f4b390f9df61d5a01c2a60eb7ecf642e1ccdab08e1e
REVIEWED_PLAN: docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-isolation-20260902.md at commit 5185ac37418654f0a1256bb754058d731801a3e3, sha256 30e8db637cd6fd4564351f4b390f9df61d5a01c2a60eb7ecf642e1ccdab08e1e
TARGET_RELAY_SHA256: 733dcb477bca1f112fadab225c1bc7bfb4f46fddea8238fd91397bb60c143d29
BASE: incoming carrier declares main@31fb0fe; review performed at main@5185ac37418654f0a1256bb754058d731801a3e3; governed harness, adapters, CLI, pack, envelope, and manifest bytes remain byte-identical to product pin 46df8f3
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: operator, master.master-planner, master.master-reviewer, m-3.planner, m-3.implementer, m-2.planner
SUBJECT: MUST-REVISE exact 30e8db63 — the rev5 authority chain is now valid and the manifest-provenance positive is sound, but the SQLite exact-kind demonstration cannot pass, the base-relative four-path fence already contains seven docs-lane paths, the 175138 PLAN reuses plan-4, and stale three-path/rev4 instructions remain

## Verdict

MUST-REVISE at exact SHA-256 `30e8db637cd6fd4564351f4b390f9df61d5a01c2a60eb7ecf642e1ccdab08e1e`.

The governing correction is real: design rev5 hashes to `637ef197…` at its live bytes, its design commit `a07d84c…`, and source-edge commit `1738583e…`; m-3 approved it at `162639`, the Master Reviewer approved it with VP concurrence at `164129`, the operator re-pinned the commission exactly at `173858`, and master carried it at `173859`. The plan's `_rp_positive` reads the image manifest, binds both staged identities to their source-store provenance, and runs before the poison oracle. The two budget command strings are byte-equal and name all three production-side files.

This exact plan is nevertheless not executable as written. Its exact-kind mutant check searches a filtered list that never contains a non-poison kind value; its base-relative write-set command already returns seven docs-lane paths before any harness commit; its header-only correction reissues PLAN under the same handoff id; and two implementation instructions still describe the former three-path/rev4 plan. No implementation token may parent to this review.

This is review-only. It authorizes no harness, scenario, product, design, plan, budget, CMake, branch/ref, merge, push, remote CI, publication, deployment, or release action.

## Findings

### F1 — Critical — the required SQLite exact-kind demonstration cannot pass

Plan lines 214-233 make `_isolation_leaks` append a finding only when `_poison_tag(value, poison_root)` returns a locator. The exact warning kind `CodexDbEnrichmentSkipped` contains neither a poison session id nor a path under the poison root, so checking `warnings[index].kind` produces no finding. Only the warning path produces `isolation-leak CODEX_SQLITE_HOME: ...path=...`.

Task 3 Step 2b then derives `kinds` exclusively from those `isolation-leak` lines and requires exactly one line ending in `].kind=CodexDbEnrichmentSkipped` (plan lines 375-384). An executable counterexample using the plan's filter against `{"kind":"CodexDbEnrichmentSkipped","path":"/tmp/p/codex-sqlite/state_5.sqlite"}` yielded one path finding, zero kind matches, and one path match. Thus the prescribed driver rejects the correct product envelope and cannot produce the required four-mutant success transcript.

The successor must inspect the actual warning objects or otherwise retain paired kind/path evidence before poison filtering, and must assert exactly one warning object whose kind equals `CodexDbEnrichmentSkipped` and whose path equals the poisoned database. Do not weaken the rev5 exact-object requirement to two unrelated lines.

### F2 — Critical — the post-commit four-path fence uses a base that already contains seven non-harness paths

The incoming relay declares `BASE: main@31fb0fe`. The plan was later committed at `5185ac3`. At the reviewed head, `git diff --name-only 31fb0fe..5185ac3` already returns seven paths: the intg INDEX, both PLAN carriers, the arm-(c) SITREP, the plan artifact, and both root-sweep archives. Task 3 Step 1 nevertheless requires `git diff --name-only <base>..HEAD | sort` after implementation to equal exactly the four harness paths.

That command is already red before implementation and would return at least eleven paths after the four-path harness commit. The successor must name two distinct pins: the immutable product/design evidence pin and the actual implementation-base commit immediately preceding the one harness commit. Bind the write-set proof to the implementation commit itself (for example its single-parent diff) or to that explicit implementation base; keep product-surface byte-identity as a separate proof.

### F3 — Important governance — the header-only PLAN correction reuses `intg-isolation-plan-4`

Both `PLAN-pair-planner-20260902-174557.md` and `PLAN-pair-planner-20260902-175138.md` carry `DISPATCH_ID: intg-isolation-plan-4`. Their diff changes operative header bytes, including `COMMISSION_SCOPE`, and the newer relay explicitly calls itself a re-file under the same handoff id. The v2.9.2 authority-chain rule is mechanical: a reissued PLAN increments its numeric suffix; the cycle directory remains stable. Reuse also leaves two qualifying PLAN parents for a future review/token walk, contrary to the stated unique lineage goal.

Reissue the corrected successor as the next unused PLAN handoff id, `intg-isolation-plan-5`, in the same `intg-isolation` directory. The new exact-hash review must use its own next unique review id and parent to `intg-isolation-plan-5`.

### F4 — Important — two execution instructions still name superseded state

Task 3 Step 0 (plan line 350) requires “the three write-set paths initially unchanged,” while Global constraint 1 and the acceptance criteria define exactly four paths. This does not prove the new scenario path was clean at implementation start. Task 3 Step 4 (line 391) mandates a commit message naming `m3-e2-store-isolation-20260901 rev4 @ 5c81e86a`, even though the face correctly marks rev4 dead and the commissioned lock is rev5 `637ef197…`.

The successor must require all four paths clean at the implementation base and must bind the implementation commit message to rev5 `637ef197…`. Search the executable tasks, not only the face/revision summary, for stale three-path, rev4, and dead-pin instructions.

## Verified surfaces that carry forward

- Incoming carrier SHA-256 is `733dcb477bca1f112fadab225c1bc7bfb4f46fddea8238fd91397bb60c143d29`; exact-file v2.9.2 lint is green. The archived root sweep is `25a3bd74e1e255491782dbc901fabcb1ef9a3ff2dc72fefb726e2d181cdfa6e5`: root-wide rc 1 is inherited, while the refiled carrier has no local rule-3d fire and its cross-repo design-edge class is zero.
- Plan SHA-256 is `30e8db637cd6fd4564351f4b390f9df61d5a01c2a60eb7ecf642e1ccdab08e1e` at commit `5185ac37418654f0a1256bb754058d731801a3e3`.
- Design rev5 exact bytes and the complete owner/Master/operator/master chain are valid. No new operator amendment is required unless the design pin changes.
- Manifest fields at `manifest.cpp:658-720`, `env` tier spellings, warning queue/publication at `codex.cpp:1240-1246` and `:1394-1400`, warning serialization at `envelope.cpp:16-35`, and the staged source-store paths in `scenario.py:262-319` independently match the plan's positive-provenance direction.
- F4 from `161514` is folded: the changed-line timeout command occurs exactly twice and includes `scenario.py`, `stub_biv.py`, and `store-isolation-witness.json` at both sites.
- The four-path harness fence, two-grain witness, source-aware five-locator overlay, seven markers, unchanged budgets, both-platform battery, no production mutant knob, one local implementation commit maximum, landed-byte m-3 review, and downstream holds may carry after F1-F4 are corrected.

## Escalation scan

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: yes — the harness must prove ambient agent-store locators are cut without reading real host stores
- migration/backfill/destructive-write/canonical-data-repair: no — review-only
- money/inventory/orders/planning/accounting/trust-critical-state: yes — E2 hermeticity becomes governed merge and publication evidence
- AI-or-automation-acts-downstream: yes — a later token and countgate observations consume this plan
- worker/scheduler/queue/retry/async-side-effect: yes — spawned E2 command environments and real-binary demonstrations are governed
- cross-repo/service-contract/generated-schema/shared-API-event: yes — PDC design governs the commissioned Bivpak harness lane
- user-visible-control-with-materializer/downstream-consumer: no — harness-only design
- test-runtime-role-mismatch: yes — the prescribed demonstration rejects the correct warning envelope and the write-set comparator targets the wrong base
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: yes — an authority-chain PLAN id is reused and executable instructions retain dead-plan state
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: none — no downgrade or risk acceptance requested
- scan_presented_to_operator: no — the required forward path is a corrected pair plan at the existing exact commissioned design pin
- operator_reply_after_scan: none
- valid_waiver: no
WAIVED_RISK_ACCEPTANCE: none

## Required successor

Do not mint a token from plan `30e8db63…`, either `plan-4` carrier, or this review. Correct the exact-kind witness to inspect paired warning objects, separate the implementation base from the product evidence pin, require all four initial paths, update the mandated commit message to rev5, and reissue the corrected PLAN under `intg-isolation-plan-5`. Run exact-file and root-mode measurements on that successor, then request a new exact-hash review with a unique review id parented to `intg-isolation-plan-5`.

ACTIONS_GIT_REF: read-only review of plan commit 5185ac37418654f0a1256bb754058d731801a3e3 at sha256 30e8db637cd6fd4564351f4b390f9df61d5a01c2a60eb7ecf642e1ccdab08e1e; incoming carrier, exact rev5 authority chain, product warning/manifest surfaces, executable warning-filter counterexample, base-relative path census, budget-command identity, handoff-id census, exact-file lint, archived root measurement, and current worktree checked; daemon submission and path-scoped review commit only; no harness, scenario, product, design, plan, budget, CMake, branch, merge, push, remote CI, publication, deployment, or release action claimed
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

