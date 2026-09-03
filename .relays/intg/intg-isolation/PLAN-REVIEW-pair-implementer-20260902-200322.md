## PLAN-REVIEW artifact — APPROVE exact isolation plan revision 6 at 9eb01448: literal execution order, adjacent two-sided pre-commit guard, landed-SHA Linux sequencing, and the rev5 warning/pin/fence constraints are executable

ROLE: Pair Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: approve
DISPATCH_ID: intg-isolation-plan-review-8
PARENT_DISPATCH_ID: intg-isolation-plan-7
IN_REPLY_TO: intg-isolation/PLAN-pair-planner-20260902-194515.md
RELATED_CONTEXT: intg-isolation/PLAN-REVIEW-pair-implementer-20260902-193327.md; intg-isolation/SITREP-pair-planner-20260902-195418.md; docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-isolation-20260902.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/DESIGN-REVIEW-implementer-20260902-162639.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/DESIGN-REVIEW-master-reviewer-20260902-164129.md; ../../pdc/master/relays/r437-operator-scope-ruling/PLAN-operator-20260902-173858.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/PLAN-master-planner-20260902-173859.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — rev5 is owner-approved, Master-Reviewer-approved with VP concurrence, and exactly operator-commissioned; this exact plan is approved, but implementation still requires the separate in-lane bare `DISPATCH IMPL` token addressed solely to intg.pair-implementer; m-3's landed-sha byte review and every merge, push, publication, and release gate remain held
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: m3-e2-store-isolation-20260901
DESIGN_OWNER: m-3
DESIGN_LOCK_ID: m3-e2-store-isolation-20260901 @ sha256 637ef197aa9f2ebb8f9a34ab91558d52ae35a71691a8403290a87ad59a84bca6
DESIGN_RECORD_KIND: design-doc
TARGET_DESIGN_COMMIT: a07d84cee5687efb05912567fa58387e61b93317
PLAN_LOCK_ID: intg-isolation-plan-20260902 @ sha256 9eb01448a9f05520847ca1d27de652a399d660a0911d2ccd6f32f71d4242c124
REVIEWED_PLAN: docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-isolation-20260902.md at commit 714732b0c531b92c37ecd551a27acd67067d10ab, sha256 9eb01448a9f05520847ca1d27de652a399d660a0911d2ccd6f32f71d4242c124
TARGET_RELAY_SHA256: 5630c663a7de41cad2a32ddfbff1aea7138ad9a548d2d71f856515c88014be3a
BASE: incoming carrier correctly declares docs-lane filing head main@4f3ef6661885c2731dd47e35938f0017228b1a21, which is commit 714732b's direct parent; review performed at main@714732b0c531b92c37ecd551a27acd67067d10ab; governed harness, adapters, CLI, pack, envelope, and manifest surfaces remain byte-identical to product pin 46df8f3
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: operator, master.master-planner, master.master-reviewer, m-3.planner, m-3.implementer, m-2.planner
SUBJECT: APPROVE exact 9eb01448 — Task 3 now has one executable order; the two-sided status guard catches vanished inherited state and is adjacent to the one commit; $LANDED exists before the landed fence/Linux clone; the recorded stale-instruction predicate, fresh plan-7 lineage, design edge, warning-object witness, four-path fence, budgets, and downstream holds verify

## Verdict

APPROVE exact SHA-256 `9eb01448a9f05520847ca1d27de652a399d660a0911d2ccd6f32f71d4242c124`.

No blocking plan finding remains. Task 0 runs before governed writes. Task 3's numbered order is now literal: working-tree fence, macOS and mutant evidence, the HEAD/index/two-sided-status guard directly adjacent to the one commit, `$LANDED` capture, landed-byte fence, Linux at `$LANDED`, then the IMPL report. Linux-red handling explicitly preserves the one-commit boundary and routes the landed SHA plus red transcript upward without amend, reset, or a second commit.

The two-sided status witness discriminates. Re-running the former counterexample produced one `<` row, so the required zero-removal check fails; the valid case produced zero removals and exactly the four expected porcelain rows with status codes. The updated stale-instruction predicate independently reproduced `L=439`, `rc=1`. The product-pin proof returned rc 0, the carrier's filing base equals its parent, and the archived root measurement records no carrier-local fire with design-edge class zero.

This approval is review-only. It does not itself authorize implementation, harness or product edits, a commit, merge, push, remote CI, publication, deployment, or release. Implementation begins only on the separately filed, correctly parented, addressed bare token.

## Exact-plan checks

- **Authority and identity:** incoming ROLE/PHASE/AUTHORITY are Pair Planner / PLAN / plan-only; `TO` addresses `intg.pair-implementer`; `DISPATCH_ID: intg-isolation-plan-7` is unique among PLAN carriers; no bare implementation token appears in the carrier. Plan and carrier hashes match their declared values.
- **Locked design:** rev5 remains `637ef197…` at design commit `a07d84c…`, owner-approved at `162639`, Master-Reviewer-approved with VP concurrence at `164129`, exactly operator-commissioned at `173858`, and carried at `173859`. The canonical source-edge pin stays `1738583e…`.
- **Pre-write and base fence:** Task 0 creates the out-of-tree evidence home, captures full inherited porcelain status, requires an empty index, proves all four governed paths clean and both new paths absent, rechecks product-byte identity, then records `$IMPL_BASE` before any write.
- **Pre-commit proof:** Step 4 rechecks `HEAD == $IMPL_BASE`, requires the index empty, rejects every removed/changed inherited porcelain row, and admits exactly two modified plus two untracked governed rows. No command occurs between that guard and Step 5's exact-path staging/commit.
- **Landed proof:** Step 5 records `$LANDED` only after the one commit and proves parent/write-set/status equality. Step 6 performs the landed write-set, budget, marker, census, overwrite, and no-knob proofs. Step 7 alone consumes `$LANDED`, with the Ubuntu 24.04 amd64, `--init`, non-root nofile-raise parity topology and explicit red routing.
- **Witnesses and scope:** the paired warning-object line and exact SQLite kind/path assertion are unchanged; `_rp_positive` still makes the real-product grain non-vacuous; four restore-to-poison demonstrations, seven markers, the five-locator overlay, unchanged 30/120 budget bytes, exactly four harness paths, no existing scenario/product/CMake/E3/GitHub byte, no production mutant knob, and both-platform evidence remain required.
- **Root evidence:** exact carrier lint is green. Root archive `d803d0bf9c50b3ea680541edd9279d7d5ffb78b93a9792d855e6e204b08fa7b0` reports the `194515` carrier silent and design-edge class zero; its root-wide rc 1 is inherited and separately enumerated.

## Non-blocking record note

The self-check section heading at plan line 448 still says `rev5`, and the `rev6` summary bullet follows that section's result rather than sitting with rev0-rev5 under `## Revision lineage`; the bullet also says the predicate is “below” although it is above. The exact carrier, PLAN identity line, lock digest, literal tasks, live predicate output, and approval parent are unambiguous, so this editorial placement does not block execution and must not trigger mutation of this approved artifact. Correct it forward only if another substantive plan revision is independently required.

## Escalation scan

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: yes — addressed by the five-locator overwrite, fail-closed guard, two witness grains, and exact poison demonstrations
- migration/backfill/destructive-write/canonical-data-repair: no — review-only; Linux-red handling explicitly forbids reset or un-landing
- money/inventory/orders/planning/accounting/trust-critical-state: yes — exact evidence and landed-sha review gates remain explicit
- AI-or-automation-acts-downstream: yes — implementation remains behind a separate addressed token and m-3's landed-byte review
- worker/scheduler/queue/retry/async-side-effect: yes — every spawned E2 command receives the five-locator overlay and both-platform proof is required
- cross-repo/service-contract/generated-schema/shared-API-event: yes — exact PDC design pin and canonical design edge remain bound
- user-visible-control-with-materializer/downstream-consumer: no — harness-only plan
- test-runtime-role-mismatch: no — working-tree macOS evidence is sequenced before the adjacent commit guard, landed-byte proofs and Linux consume the recorded commit afterward
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: no — exact four-path scope, unchanged budgets, STOP routing, and downstream holds remain explicit
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: none — no risk downgrade or waiver required for this approval
- scan_presented_to_operator: no — existing exact rev5 operator amendment stands; a fresh decision is not required unless the design pin or scope changes
- operator_reply_after_scan: none
- valid_waiver: no
WAIVED_RISK_ACCEPTANCE: none

## Next gate

This review satisfies the implementer's exact-hash PLAN-REVIEW leg for `intg-isolation-plan-7`. The pair planner may now evaluate the structurally green filed measurement and, if every issuance predicate still holds at issuance time, file the separate in-lane token under its own authority with the four-path `SCOPE_DIFF`. Any artifact-byte, design-pin, scope, base, or route change invalidates this exact-hash approval and requires a fresh review.

ACTIONS_GIT_REF: read-only approval of plan commit 714732b0c531b92c37ecd551a27acd67067d10ab at sha256 9eb01448a9f05520847ca1d27de652a399d660a0911d2ccd6f32f71d4242c124; incoming carrier, root-sweep archive, exact Task 0/Task 3 order, live narrowed-self-check reproduction, two-sided status negative and positive witnesses, one-commit/Linux-red boundary, carrier parent/base, product-pin proof, exact plan diff hunks, dispatch-id census, no-token check, exact-file lint, and current worktree checked; daemon submission and path-scoped review commit only; no harness, scenario, product, design, plan, budget, CMake, branch, merge, push, remote CI, publication, deployment, or release action claimed
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
