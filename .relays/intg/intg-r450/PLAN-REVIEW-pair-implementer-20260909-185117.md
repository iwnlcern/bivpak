## PLAN-REVIEW — MUST-REVISE rev12 5a2ddf5d: state iii stops in Task 1, the admitted Linux red cannot escape the retained container gate, and the runner proof does not prove whole-task completeness

ROLE: Pair Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: must-revise
DISPATCH_ID: intg-r450-discover-parity-plan-review-13
PARENT_DISPATCH_ID: intg-r450-discover-parity-plan-13
IN_REPLY_TO: intg-r450/PLAN-pair-planner-20260909-183047.md
RELATED_CONTEXT: ../../../pdc/master/relays/intg-r450-discover-parity-act/PLAN-master-planner-20260909-173401.md; ../../../pdc/master/relays/intg-r450-discover-parity-act/PLAN-master-planner-20260909-164408.md; ../../../pdc/master/relays/intg-r450-discover-parity-act/DESIGN-planner-20260909-165351.md; ../../../pdc/master/relays/intg-r450-discover-parity-act/DESIGN-planner-20260909-165801.md; ../../../pdc/master/relays/intg-r450-discover-parity-act/DESIGN-planner-20260909-165802.md; intg-r450/SITREP-pair-implementer-20260909-154922.md; intg-r450/PLAN-REVIEW-pair-implementer-20260909-073544.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-r450-discover-parity-20260906.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/results/r450-r435-discriminator-at-B-20260909.txt
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new human gate — revise the exact plan and return it for a new exact-hash review; token 12 remains held, and iso rev9's separate Master-Reviewer gate remains separate
COMMISSION_ID: intg-consent-fabric
COMMISSION_SCOPE: the operator-authorized integration phase (2026-08-26) executed by ONE commissioned pair — sub-step 1 first, the A6 rev14 consent-UX fabric with the engine unwired per the sealed spine; subsequent sub-steps (format act consuming LOCKED M rev8 + LOCKED N; then wiring at product scope) each behind their standing gates incl. m-4's reachability re-review before any wiring; sealed design only; STOPs route UP; no merge/push/publication/release authority
COMMISSION_TO: intg.pair-planner
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: m2-r450-discover-fence-rev2-20260903
DESIGN_OWNER: m-2
DESIGN_SOURCE_REPO: ../pdc
DESIGN_SOURCE_COMMIT: 79fa1754ca576193accb15b813163c376ab7e2b6
DESIGN_SOURCE_ROOT: master/relays
DESIGN_SOURCE_PATH: master/relays/r437-pack-timeout-diagnosis/DESIGN-m2-planner-20260903-144700.md
DESIGN_LOCK_ID: m2-r450-discover-fence-rev2-20260903 @ sha256 f2216ee606a03b0b5b0b7f4562fed52a7349219c28990e6ee3e89b0cc25e8c6f
DESIGN_RECORD_KIND: design-doc
TARGET_DESIGN_COMMIT: dfb5b409935212696e030a80d3e9afdd6abe912e
PLAN_LOCK_ID: intg-r450-discover-parity-plan-20260906 @ sha256 5a2ddf5d31f8d4b0676a23bd4f548dd2fa016895bd8444abb7d9fbdc27283c29
TARGET_RELAY_SHA256: 97c6b585285dd9be067433e57c855266d96b48952dcbb2d1514a8f915ade842d
TARGET_PLAN_SHA256: 5a2ddf5d31f8d4b0676a23bd4f548dd2fa016895bd8444abb7d9fbdc27283c29
TARGET_PLAN_COMMIT: 7b2b487
REVIEWED_PLAN: docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-r450-discover-parity-20260906.md at commit 7b2b487, sha256 5a2ddf5d31f8d4b0676a23bd4f548dd2fa016895bd8444abb7d9fbdc27283c29
BASE: review checkout main@26d96b79925e076a3f686eed4431b85e3bd492d3; published product base B=bbf297e36a38a1fab8c2675f945098a0633f9f8b
BRANCH: retained intg/r450-discover-parity worktree verified read-only and clean at H=8509157c41c5ef66595d655f39eee5107081bd32; H^=C=961b1ccd0ba488f909357d4cac1abab8c77d2fa8; H^^=B=bbf297e36a38a1fab8c2675f945098a0633f9f8b
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: master.master-planner, master.master-reviewer, operator, m-2.planner, m-2.implementer, m-3.planner, m-3.implementer
SUBJECT: MUST-REVISE exact rev12 5a2ddf5d — the state-iii route executes a P-only red disclosure at H and STOPs; the reused Linux container rejects the registered red before its new bar; stale green-only requirements conflict; two evidence producers mask status; runner proof is not whole-task proof

## Verdict

VERDICT: must-revise

The incoming carrier hashes to `97c6b585285dd9be067433e57c855266d96b48952dcbb2d1514a8f915ade842d`; the live plan and its blob at `7b2b487` both hash to `5a2ddf5d31f8d4b0676a23bd4f548dd2fa016895bd8444abb7d9fbdc27283c29`. The retained candidate is clean at H with the declared H → C → B lineage. The iso rev9 source artifact independently hashes to `59f9c0d1d71f4604801758880865fdcc21fe61db8ad2841c488eabc65118dc23`; that pin is recorded here as the bar text's source, not as an approval of either artifact.

Rev12 is not executable to its promised acceptance state and does not yet make the token-11 process class impossible.

## F1 — state iii necessarily STOPs in Task 1 Step 5 before the promised Tasks 4–6 rerun

Task 0 Step 2 selects state `iii` while the retained worktree remains at H. Task 1 Step 5 nevertheless runs unconditionally in that H worktree and names its full-suite result `ctest-macos-P.log`; substep (iv) requires the failing set to be exactly `harness-selftest` and requires at least one `claude_adapter_file` tripwire line. The actual H acceptance run already recorded `ctest_macos_H_rc=0` and `1014 passed` in the token-11 STOP relay. Therefore the state-iii Task-1 run is green, its failed-name file is empty, and the diff against the one-line `harness-selftest` expectation returns 1 and STOPs. Rev12 adds state-iii routes only to Task 1 Steps 6–7, after this unconditional blocker.

Required correction: under state `iii`, route Task 1 Step 5 to a receipt-only verification of the sealed P-state disclosure (including its hashes and failing-set/cause receipts), or execute it at an explicitly verified P tree without moving the candidate worktree. Do not execute the P-only disclosure oracle at H. Then mechanically validate the complete Task 0 → Task 1 → Tasks 2/3 receipt → Tasks 4–6 state-iii route.

## F2 — the registered Linux red cannot reach the new bar

Task 6 Step 2 says to use exactly Task 2 Step 2's four-phase container and makes `ctest` rc data only in prose before applying the new bar after copy-out. The retained token-11 runner shows the inherited outer contract: it requires Docker rc 0, `container_payload_rc=0`, `ctest_H_producer_rc=0`, and `suite_aggregate_rc=0 ledger_write_failed=0` before the later evidence parsing. The admitted observation has `ctest_H_producer_rc=8` and `suite_aggregate_rc=1 ledger_write_failed=0`. Reusing that container therefore returns nonzero and STOPs at the outer/container ledger gates before the rev12 bar can classify the registered red.

Required correction: spell the changed Phase-S/container/outer contract in the plan. It must preserve failures for provisioning, configuration, build, XML producers, receipt production and copy-out, but carry the single ctest rc 8 and complete logs out as bounded data for the bar. Prove both paths from the written bytes: green rc 0 reaches `pass-green`; the exact token-11 rc 8 reaches `pass-r435-disclosed-registered-red`; infrastructure or non-bar failures still STOP before acceptance.

## F3 — retained green-only requirements contradict the rev12 Linux bar

The Global constraints still require workflow-equivalent suites on both targets to return rc 0 at H; Task 6's heading still says the suites are required green; and Task 7's IMPL-return checklist still requires “the Linux ctest stage rc 0 at H.” Those terms conflict with Acceptance criterion 4 and the rev12 anti-half-fix guard, which expressly admit a Linux rc 8 satisfying clauses (a)–(g).

Required correction: replace every live green-only Linux requirement and receipt with the exact two-outcome contract: rc 0 plus `pass-green`, or bounded nonzero plus `pass-r435-disclosed-registered-red`. Keep macOS rc 0 mandatory and keep every outside-bar Linux result a STOP.

## F4 — the new state-iii re-derivation masks the generator status

Task 0 Step 2 computes both `MAC` and `LIN` through `python3 tuples.py | sed`. The shell status tested by each command substitution is the final `sed` status, not `tuples.py`'s status. `tuples.py` can print the targeted `biv_tests ... successes=` line and later exit nonzero; a non-empty extracted value then passes. This violates the plan's own requirements that every helper invocation capture its status and that no evidence-producing pipeline exist.

Required correction: write each `tuples.py` output to a file, capture and require the helper status, prove the output non-empty, then extract the one exact target line with separately captured producer/consumer statuses and exact multiplicity. Apply the same discipline to all newly added evidence pipelines.

## F5 — runner proof is one-directional and does not prove a whole Task-N runner

The protocol checks only that every non-glue runner line occurs somewhere in the entire plan. It does not prove that every required Task-N span/block is present in the runner, that the lines came from Task N rather than another task, or that document order and multiplicity are preserved. A controller may omit an entire Task-N command: every remaining line still has `n >= 1`, the proof ends `rc=0`, the runner hash and path checks pass, and the incomplete task executes. The token-11 class was incomplete per-task materialization; runner-to-plan membership alone does not make that class impossible.

Required correction: add a bidirectional, Task-N-scoped manifest or deterministic extraction comparison that binds the complete ordered Task-N plan-origin sequence, including multiplicity, to the materialized runner before `rc=0`. Retain the path, mode and post-proof byte-hash checks; they close different defects.

## Preserved source terms and scope

The m-3 bar sentence source pin is iso rev9 sha256 `59f9c0d1d71f4604801758880865fdcc21fe61db8ad2841c488eabc65118dc23`. K-2 remains “5 or more is a fresh finding”; m-4's C-1 disjoint-touch and C-2 equal-population conditions remain mandatory; failure of either requires the named bounded interleaved series and a STOP UP. These terms are not the reason for the verdict and must not be weakened while closing F1–F5.

Token 12 remains held. This review grants no reset, candidate mutation, implementation, push, PR, merge, landing push, publication, deployment, release, or closure.

BOUNDARY_CONTRACT:
- Writes: none under this PLAN-REVIEW beyond the daemon-filed review relay and append-only INDEX projection
- Reads: exact plan-13 carrier, rev12 artifact and object, governing master and owner relays, the token-11 STOP relay and sealed runner/ledger receipts, retained candidate lineage, and iso rev9 source bytes
- Target entity: rev12's state-iii reachability, Linux bar reachability, acceptance consistency, producer-status discipline, and whole-task runner proof
- Downstream consumer: a successor exact-hash review, any separately addressed token, owner reviews, and the merge packet
- Contract: every promised route must be mechanically reachable; registered-red classification must occur after infrastructure success without requiring ctest rc 0; runner proof must bind the whole ordered Task-N content
- Proof: exact hashes and object equality; source-line audit; actual H macOS receipt; actual token-11 Linux ledger and runner outer gates; counterexample against the runner proof relation
- No-consumer action: reject and revise; no implementation, branch mutation, push, PR, merge, landing push, publication, deployment, release, or closure

Read-only PLAN-REVIEW. No R-4.50 product, test, workflow, harness, plan, design, governed worktree, branch, commit, tag, push, PR, merge, publication, deployment, release, or closure action occurred. The outgoing daemon-filed PLAN-REVIEW and append-only INDEX projection are the sole own-seat repository writes.

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: no
- migration/backfill/destructive-write/canonical-data-repair: yes — state iii carries a pre-authorized reset branch whose reachability must be exact
- money/inventory/orders/planning/accounting/trust-critical-state: yes — one-shot evidence, candidate retention and acceptance classification are trust-critical execution state
- AI-or-automation-acts-downstream: yes — a later runner consumes the exact plan
- worker/scheduler/queue/retry/async-side-effect: yes — macOS and Linux observations are one-shot and STOP-gated
- cross-repo/service-contract/generated-schema/shared-API-event: yes — pdc master, m-3 and m-4 terms govern this execution
- user-visible-control-with-materializer/downstream-consumer: no
- test-runtime-role-mismatch: yes — the H-state resume executes a P-state disclosure oracle, and the Linux bar sits after a green-only container gate
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: no — no risk is accepted and no scope is widened
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: none
- scan_presented_to_operator: no — no downgrade, residual-risk acceptance, or scope expansion is requested
- operator_reply_after_scan: none
- valid_waiver: no
WAIVED_RISK_ACCEPTANCE: none

ACTIONS_GIT_REF: read-only exact-hash review at main `26d96b79925e076a3f686eed4431b85e3bd492d3`; retained R-4.50 worktree read-only and clean at `intg/r450-discover-parity@8509157c41c5ef66595d655f39eee5107081bd32`. No product/test/workflow/harness/plan/design edit, governed worktree or branch mutation, governed commit, tag, push, PR, merge, publication, deployment, release, or closure. This daemon-filed PLAN-REVIEW and its INDEX append are the sole own-seat repository writes.
RELAY_LINT: incoming PLAN exact-file clean under daemon-matched v2.9.2 with freshness disabled; outgoing draft/render require fresh exact-file lint, daemon admission/render, draft/render byte equality, one unique INDEX row, and engine verification. Full-root inherited noise is not represented as exact-file truth.
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
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-CARRIER-COMPLETE-PUBLISHED-20260809-192358.md
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
?? relay-draft-intg-task4-stop.md
Literal full status captured after review work and immediately before authoring this draft. Every listed path is inherited. After daemon render, `.relays/intg/INDEX.md` and the rendered PLAN-REVIEW are the expected additional own-seat paths.

Done: exact-hash rev12 PLAN-REVIEW must-revise; iso rev9 source pin independently verified and recorded; five executable blockers/counterexamples filed without touching candidate or product bytes.

Not done: no implementation token, reset, R-4.50 continuation, product/test/workflow/harness/plan/design edit, governed worktree or branch mutation, C/H commit, tag, owner candidate review, push, PR, merge, landing push, publication, deployment, release, or closure.

Next requested action: intg.pair-planner — issue a successor plan that closes F1–F5, validate the complete state-iii route and both Linux bar outcomes from its written bytes, and return the new exact hash for PLAN-REVIEW; do not mint token 12 on this must-revised artifact.
