## PLAN-REVIEW — MUST-REVISE rev16 58345125: F1a/F1b close, but the tracked evidence set omits cited receipts and final controller records

ROLE: Pair Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: must-revise
DISPATCH_ID: intg-r450-discover-parity-plan-review-16
PARENT_DISPATCH_ID: intg-r450-discover-parity-plan-16
IN_REPLY_TO: intg-r450/PLAN-pair-planner-20260910-204615.md
RELATED_CONTEXT: intg-r450/PLAN-REVIEW-pair-implementer-20260910-040614.md; intg-r450/SITREP-pair-planner-20260910-210914.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-r450-discover-parity-20260906.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/results/rehearsal-r450-rev16-controls-20260910.txt; ../../docs/sprints/2026-08-27-intg-consent-fabric/results/rehearsal-r450-rev16-flow-20260910.txt; ../../../pdc/master/relays/intg-r450-discover-parity-act/PLAN-master-planner-20260910-042340.md; ../../../pdc/master/domains/m-3-restore-cli/design/2026-09-01-e2-store-isolation-r437.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new human gate — revise the exact plan and return it for a new exact-hash review; token 12 remains held and iso rev9's separate Master-Reviewer gate remains separate
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
PLAN_LOCK_ID: intg-r450-discover-parity-plan-20260906 @ sha256 58345125e6cec95ee688a0faeebe8fadab92f55f0bec91762c715cab6baca022
TARGET_RELAY_SHA256: 345a46f05393f1ca7c932e179dc495e7cde6bc11791cc7123d88577a83d4e1c7
TARGET_PLAN_SHA256: 58345125e6cec95ee688a0faeebe8fadab92f55f0bec91762c715cab6baca022
TARGET_PLAN_COMMIT: bcc656b583bc1a9e7185bf6a27091079bc32af91
REVIEWED_PLAN: docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-r450-discover-parity-20260906.md at commit bcc656b583bc1a9e7185bf6a27091079bc32af91, sha256 58345125e6cec95ee688a0faeebe8fadab92f55f0bec91762c715cab6baca022
BASE: review checkout main@11894134a753c8096e580957ec0b559d1c3bf2d9; published product base B=bbf297e36a38a1fab8c2675f945098a0633f9f8b
BRANCH: retained intg/r450-discover-parity worktree verified read-only and clean at H=8509157c41c5ef66595d655f39eee5107081bd32; H^=C=961b1ccd0ba488f909357d4cac1abab8c77d2fa8; H^^=B=bbf297e36a38a1fab8c2675f945098a0633f9f8b; remote branch absent
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: master.master-planner, master.master-reviewer, operator, m-2.planner, m-2.implementer, m-3.planner, m-3.implementer
SUBJECT: MUST-REVISE exact rev16 58345125 — F1a/F1b now close and F2/F3/F4 remain closed, but master 042340's tracked-record ruling is not met: cited evidence files are omitted, post-task-8 controller receipts arrive after the last manifest, and shasum -c proves only the copied subset

## Verdict

VERDICT: must-revise

The carrier hashes to `345a46f05393f1ca7c932e179dc495e7cde6bc11791cc7123d88577a83d4e1c7`. The live artifact and its blob at `bcc656b583bc1a9e7185bf6a27091079bc32af91` both hash to `58345125e6cec95ee688a0faeebe8fadab92f55f0bec91762c715cab6baca022`; the stated rev14-to-rev16 delta reproduces as 476 insertions and 331 deletions. The retained candidate is clean at H with the declared H to C to B lineage and no remote branch. The design source blob hashes to `f2216ee606a03b0b5b0b7f4562fed52a7349219c28990e6ee3e89b0cc25e8c6f`. The live iso rev9 source artifact independently hashes to `59f9c0d1d71f4604801758880865fdcc21fe61db8ad2841c488eabc65118dc23`; that is recorded as the bar source pin, not as an approval.

## F1a — closed: controller and extractor authenticate against the lock-verified plan

The exact controller re-hashes the plan before use, reads fresh `run-task.sh` and `plan_blocks.py` bytes from that plan with its fixed reader, and compares both before extraction. Independent controls from the exact artifact produced:

```text
extractor-only edit: rc=1; STOP-controller-task-0-extractor-not-the-plan-bytes; task-0.sh absent; task-0.done absent
controller-only edit: rc=1; STOP-controller-task-0-not-the-plan-bytes; task-0.sh absent; task-0.done absent
plan-only edit: rc=1 at the plan-lock comparison; task-0.sh absent; task-0.done absent
off-resolved-path controller invocation: rc=1 before materialization
```

This closes the mutable-extractor bypass in `040614`.

## F1b — closed: every runner is derived from the RUN blocks with byte equality

All nine exact derived runners return a last line `rc=0`. Deleting Task 0's ordinary non-gate producer `WORKTREE=/Users/jack/Programming/bivpak-intg-r450-discover-parity` returns `BYTES-DIFFER` and rc 5; duplicating the same line also returns `BYTES-DIFFER` and rc 5. The derived Task 4, 5 and 6 runner digests reproduce as `e2708b1d58656a2bf434e5fea2cf3b07b4fa83e19ad7e331e336d71d05945521`, `a113e999a6594609978c9e89188c3522c089208365f4ee6b4685ac909274f9f7`, and `4ed67ea9eadef57d43060414a0e2c55253d231cb27f6da61a76b1b8caebed802`. This closes the dropped non-gate and multiplicity classes in `040614`.

## F5 — open: the tracked copy is not complete for the plan's own cited evidence set

Master `042340` requires every artifact the plan cites as evidence of record to be copied into tracked `results/<token>/` with digests. The plan makes that same universal claim at artifact line 1925, and line 1923 explicitly cites `results-copy.txt`, `runners-dir.txt`, every `helpers.verify-N.txt`, `status-post-C-obs.txt`, `status-post-H-obs.txt`, and for every task the runner's `.exit` and `.done` receipts.

The executable copy allowlist at lines 1929–1935 omits `runners-dir.txt`, all eight `helpers.verify-1.txt` through `helpers.verify-8.txt`, both status receipts, and `results-copy.txt`. The last of these cannot be copied by that step: line 1936 creates it only after the copy and manifest verification. Task 8's copy at line 1992 still does not add any of those files. Line 1993 then builds and verifies the last in-run manifest before creating `results-copy-8.txt`. Finally, line 1988 acknowledges that `task-8.exit`, `task-8.done`, `proof-8.tail`, and `plan_blocks.sha256-8` do not exist until after the Task 8 runner exits; it assigns their later addition to the Pair Planner but specifies no post-addition manifest regeneration, exact-set comparison, or proved finalizer.

The supplied E2 rehearsal demonstrates the false-green shape rather than closing it. Its evidence home contains the omitted files. Its reported tracked directory ends Task 8 with 256 regular files, 255 manifest rows because `SHA256SUMS` itself is excluded, and `shasum -c` clean; its printed top-level listing nevertheless lacks `results-copy.txt`, `results-copy-8.txt`, `runners-dir.txt`, every `helpers.verify-N.txt`, and both status receipts, while the printed `runners/` population necessarily predates the controller's four final Task 8 receipts. A clean manifest therefore proves integrity of the selected subset, not completeness against the plan's cited evidence-of-record set.

Required correction:

1. Define one mechanically enumerable authoritative evidence-of-record set, including every artifact cited by the IMPL-return contract, and require ordered/multiplicity-exact equality between that set, the tracked tree, and the manifest paths. A hand-maintained copy allowlist plus a minimum count is not that proof.
2. Finalize the tracked tree only after all Task 8 controller receipts exist, through plan-proved bytes. No later manual addition may sit outside the final manifest and verification gate.
3. Resolve the verification-receipt cycle explicitly: either stop naming a post-manifest verifier receipt as a tracked evidence artifact and carry its E2 result in the return relay, or specify a non-circular sidecar/finalization scheme that gives every cited file a digest.
4. Add negative controls that remove one cited evidence file and that add one file after manifest creation; each must STOP the finalizer even when `shasum -c` over the stale/subset manifest is green.

## F2, F3 and F4 — remain closed; preserve unchanged

The exact `linux-container.sh` and `linux-suite.sh` blocks are byte-equal to rev14. The plan retains six 28-line gates, 18 `ctest-key.value` bindings, the Linux two-outcome terms, and the staged hash producers. Preserve those controls, the now-closed F1a/F1b machinery, the no-prior-evidence rerun, the durable evidence root, the m-3 bar sentence, K-2 threshold, m-4 C-1/C-2 conditions, and the named bounded-series fallback unchanged.

## Preserved authority

Token 12 remains held. This review grants no reset, candidate mutation, implementation, push, PR, merge, landing push, publication, deployment, release, or closure. The archive at `bd258b3` is historical evidence and is not an execution input.

BOUNDARY_CONTRACT:
- Writes: none under this PLAN-REVIEW beyond the daemon-filed review relay and append-only INDEX projection
- Reads: exact plan-16 carrier and successor SITREP, rev16 artifact/blob and predecessor, `040614`, master `042340`, planner rehearsals, retained candidate lineage, design-source blob, and iso rev9 source bytes
- Target entity: exact plan trust/completeness plus master `042340`'s complete durable tracked evidence-of-record contract
- Downstream consumer: a successor exact-hash review, any separately addressed token, owner reviews, and the merge packet
- Contract: authenticated derived runners execute every RUN record exactly; every cited evidence artifact reaches the tracked tree exactly once and is covered by the final digest set after all controller receipts exist
- Proof: exact hashes/object equality, exact-controller mutation controls, all nine exact runner checks, non-gate deletion/duplication controls, preserved script digests, and the plan/rehearsal counterexample showing a clean subset manifest with omitted cited receipts
- No-consumer action: reject and revise; no implementation, reset, branch mutation, push, PR, merge, landing push, publication, deployment, release, or closure

Read-only PLAN-REVIEW. No R-4.50 product, test, workflow, harness, plan, design, governed worktree, branch, commit, tag, push, PR, merge, publication, deployment, release, or closure action occurred. Disposable adversarial files exist only under `/tmp/r450-rev16-review.6u8RNR` and `/tmp/r450-rev16-preserved.UYM3n8`; they contain review copies/instruments and no governed repository mutation. The outgoing daemon-filed PLAN-REVIEW and append-only INDEX projection are the sole own-seat repository writes.

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: no — the review read names, hashes and plan-defined token scans; no credential value or secret was emitted
- migration/backfill/destructive-write/canonical-data-repair: yes — the plan retains a pre-authorized candidate reset branch whose executing runner must remain exact
- money/inventory/orders/planning/accounting/trust-critical-state: yes — one-shot evidence, candidate retention, tracked preservation and acceptance classification are trust-critical execution state
- AI-or-automation-acts-downstream: yes — a later controller consumes this exact plan and a Pair Planner would consume the tracked evidence
- worker/scheduler/queue/retry/async-side-effect: yes — macOS and Linux observations are one-shot and STOP-gated
- cross-repo/service-contract/generated-schema/shared-API-event: yes — pdc master, m-3 and m-4 terms govern this execution
- user-visible-control-with-materializer/downstream-consumer: no
- test-runtime-role-mismatch: yes — the current manifest verification can certify a selected subset while cited records remain only in the working evidence home
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: no — no risk is accepted and no scope is widened
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: none
- scan_presented_to_operator: no — no downgrade, residual-risk acceptance, or scope expansion is requested
- operator_reply_after_scan: none
- valid_waiver: no
WAIVED_RISK_ACCEPTANCE: none

ACTIONS_GIT_REF: read-only exact-hash review at main `11894134a753c8096e580957ec0b559d1c3bf2d9`; retained R-4.50 worktree read-only and clean at `intg/r450-discover-parity@8509157c41c5ef66595d655f39eee5107081bd32`. No product/test/workflow/harness/plan/design edit, governed worktree or branch mutation, governed commit, tag, push, PR, merge, publication, deployment, release, or closure. This daemon-filed PLAN-REVIEW and its INDEX append are the sole own-seat repository writes.
RELAY_LINT: incoming PLAN exact-file clean under daemon-matched v2.9.2 with freshness disabled and one unique INDEX row; outgoing draft/render require fresh exact-file lint, daemon admission/render, draft/render byte equality, one unique INDEX row, and engine verification. Full-root inherited six historical index inversions are not represented as exact-file truth.
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
?? relay-draft-intg-task4-stop.md
Literal full status captured after review work and immediately before authoring this draft. Every listed path is inherited. After daemon render, `.relays/intg/INDEX.md` and the rendered PLAN-REVIEW are the expected additional own-seat paths.

Done: exact-hash rev16 PLAN-REVIEW must-revise; F1a and F1b independently confirmed closed; F2, F3 and F4 preserved; one new tracked-evidence completeness defect reproduced from the plan and supplied rehearsal without touching product or candidate bytes.

Not done: no implementation token, reset, R-4.50 continuation, product/test/workflow/harness/plan/design edit, governed worktree or branch mutation, C/H commit, tag, owner candidate review, push, PR, merge, landing push, publication, deployment, release, or closure.

Next requested action: intg.pair-planner — preserve F1a/F1b/F2/F3/F4 and the no-resume/durable-root corrections; issue a successor that makes the cited evidence set mechanically complete, finalizes only after every Task 8 controller receipt exists, and rejects missing or post-manifest files; do not mint token 12 on this must-revised artifact.
