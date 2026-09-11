## PLAN-REVIEW — MUST-REVISE rev17 carrier census; artifact 704bd59a closes F5

ROLE: Pair Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: must-revise
DISPATCH_ID: intg-r450-discover-parity-plan-review-17
PARENT_DISPATCH_ID: intg-r450-discover-parity-plan-17
IN_REPLY_TO: intg-r450/PLAN-pair-planner-20260911-003836.md
RELATED_CONTEXT: intg-r450/PLAN-REVIEW-pair-implementer-20260910-212145.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-r450-discover-parity-20260906.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/results/rehearsal-r450-rev17-controls-20260910.txt; ../../docs/sprints/2026-08-27-intg-consent-fabric/results/rehearsal-r450-rev17-flow-20260910.txt; ../../../pdc/master/relays/intg-r450-discover-parity-act/PLAN-master-planner-20260910-042340.md; ../../../pdc/master/domains/m-3-restore-cli/design/2026-09-01-e2-store-isolation-r437.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new human gate — correct and re-file the carrier census against the unchanged artifact; token 12 and iso rev9's separate Master-Reviewer gate remain separate
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
PLAN_LOCK_ID: intg-r450-discover-parity-plan-20260906 @ sha256 704bd59af21f1fe59e86fd372d7660e7e4180b15fe672a483500dc30387dcd29
TARGET_RELAY_SHA256: 71253224220594458fb5ac655fa8c0987cb0d330e295bb3b17a1e00560c55a2a
TARGET_PLAN_SHA256: 704bd59af21f1fe59e86fd372d7660e7e4180b15fe672a483500dc30387dcd29
TARGET_PLAN_COMMIT: ead87ebd2f394083587eb66b43477bc8db6ba85a
REVIEWED_PLAN: docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-r450-discover-parity-20260906.md at commit ead87ebd2f394083587eb66b43477bc8db6ba85a, sha256 704bd59af21f1fe59e86fd372d7660e7e4180b15fe672a483500dc30387dcd29
BASE: review checkout main@a86bb7a490afad00a26ff8a58f825845974cf1bd; published product base B=bbf297e36a38a1fab8c2675f945098a0633f9f8b
BRANCH: retained intg/r450-discover-parity worktree verified read-only and clean at H=8509157c41c5ef66595d655f39eee5107081bd32; H^=C=961b1ccd0ba488f909357d4cac1abab8c77d2fa8; H^^=B=bbf297e36a38a1fab8c2675f945098a0633f9f8b; remote branch absent
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: master.master-planner, master.master-reviewer, operator, m-2.planner, m-2.implementer, m-3.planner, m-3.implementer
SUBJECT: MUST-REVISE rev17 carrier only — exact artifact 704bd59a closes tracked-record F5 and preserves F1a/F1b/F2/F3/F4, but the carrier's claimed rev16-to-rev17 numstat is 171/36, not 614/334; the larger count begins at rev16's parent

## Verdict

VERDICT: must-revise

The carrier hashes to `71253224220594458fb5ac655fa8c0987cb0d330e295bb3b17a1e00560c55a2a`. The live artifact and its blob at `ead87ebd2f394083587eb66b43477bc8db6ba85a` both hash to `704bd59af21f1fe59e86fd372d7660e7e4180b15fe672a483500dc30387dcd29`. The retained candidate is clean at H with H^ = C, H^^ = B, and no remote branch. The design source blob independently hashes to `f2216ee606a03b0b5b0b7f4562fed52a7349219c28990e6ee3e89b0cc25e8c6f`. The live iso rev9 source artifact independently hashes to `59f9c0d1d71f4604801758880865fdcc21fe61db8ad2841c488eabc65118dc23`; that is the bar text's source pin, not an approval.

## F5 — closed in exact artifact 704bd59a

`finalize.py list` mechanically defines the evidence set as every regular file under the durable evidence home except the four declared scratch-component classes and the four post-exit Task-9 controller receipts. The component rules exclude scratch directories such as `rederive-C` while preserving cited files such as `rederive-C.txt` and `rederive-H.txt`. Task 9 starts only after the controller has written Task 8's `.done`, `.exit`, proof tail, and extractor digest into the home; it enumerates once, copies once into a fresh tracked directory, builds the manifest, and requires both the second-implementation equality/digest/copy check and `shasum -c`. The final verification outputs and post-exit receipts are no longer named as tracked artifacts; they are carried as E2 in the Task-9 SITREP, which is the explicit non-circular route allowed by finding 3 of `212145`.

Independent extraction from the exact artifact produced ten derived runners whose `plan_blocks.py check` result ended `rc=0`. The Task 1 through Task 6 runners and `linux-container.sh` / `linux-suite.sh` are byte-equal to rev16. Deleting or duplicating Task 0's ordinary non-gate `WORKTREE=` line returned `BYTES-DIFFER`, rc 5. The only controller/extractor changes from rev16 are the bounded extension from tasks 0..8 to tasks 0..9.

An independent synthetic home exercised the exact `finalize.py` bytes. The positive set included `rederive-C.txt` and Task 9's prologue runner while excluding all four scratch classes and all four post-exit Task-9 receipts. Results:

```text
positive:       rc=0 set=4 tree=4 manifest=4 equal=yes digests=ok copies=ok
missing file:   rc=5 set=4 tree=3 manifest=4 equal=no digests=bad copies=bad
extra file:     rc=5 set=4 tree=5 manifest=4 equal=no digests=ok copies=ok; stale shasum-c rc=0
altered byte:   rc=5 set=4 tree=4 manifest=4 equal=yes digests=bad copies=bad
deleted row:    rc=5 set=4 tree=4 manifest=3 equal=no digests=ok copies=ok; stale shasum-c rc=0
late home file: rc=5 set=5 tree=4 manifest=4 equal=no digests=ok copies=bad; stale shasum-c rc=0
swapped rows:   rc=5 set=4 tree=4 manifest=4 equal=no digests=ok copies=ok
duplicate row:  rc=5 set=4 tree=4 manifest=5 equal=no digests=ok copies=ok
```

This closes the authoritative-set, post-Task-8 finalization, receipt-cycle, missing-file, extra-file, order, and multiplicity requirements of `212145`. F1a/F1b remain closed; F2/F3/F4 and their exact executable controls remain preserved.

## F6 — blocking carrier census mismatch

Carrier line 65 says:

```text
rev16 -> rev17 diff (git diff bcc656b ead87eb): 614 insertions, 334 deletions
```

That command does not reproduce the claim:

```text
git diff --numstat bcc656b ead87eb -- PL-intg-r450-discover-parity-20260906.md
171  36  PL-intg-r450-discover-parity-20260906.md

git diff --numstat bcc656b^ ead87eb -- PL-intg-r450-discover-parity-20260906.md
614  334 PL-intg-r450-discover-parity-20260906.md
```

`bcc656b` is the rev16 artifact commit. Its parent `bd258b3` is the separate sealed-evidence archive commit, before rev16. Therefore 614/334 is not the rev16-to-rev17 delta the carrier labels and commands. This exact-census mismatch blocks approval of the filed carrier even though the artifact itself is review-clean on the assessed findings.

Required correction: preserve exact artifact `704bd59af21f1fe59e86fd372d7660e7e4180b15fe672a483500dc30387dcd29` unchanged; issue a successor carrier that reports rev16 `bcc656b` to rev17 `ead87eb` as 171 insertions / 36 deletions, or relabels and commands any intentionally wider comparison truthfully. No product or candidate rerun is required for this carrier-only correction.

## Preserved authority

Token 12 remains held. This review grants no reset, candidate mutation, implementation, push, PR, merge, landing push, publication, deployment, release, or closure. The separate iso rev9 Master-Reviewer gate is not adjudicated here.

BOUNDARY_CONTRACT:
- Writes: none under this PLAN-REVIEW beyond the daemon-filed review relay and append-only INDEX projection
- Reads: exact plan-17 carrier, artifact/blob and rev16 predecessor, prior `212145` review, master `042340`, rev17 rehearsal logs, retained candidate lineage, design-source blob, and iso rev9 source bytes
- Target entity: exact plan trust/completeness plus the truth of the filed mechanical census
- Downstream consumer: a corrected successor carrier, any separately addressed token, owner reviews, and the merge packet
- Contract: authenticated derived runners execute every RUN record exactly; every cited tracked artifact belongs to one mechanical final set; filed measurements reproduce from their named commands and revisions
- Proof: exact hashes/object equality, all ten exact runner checks, preserved runner/script byte equality, independent finalizer controls, exact candidate lineage, and the two independently run numstats
- No-consumer action: reject and re-file the carrier census only; no artifact edit, implementation, branch mutation, push, PR, merge, landing push, publication, deployment, release, or closure

Read-only PLAN-REVIEW. No R-4.50 product, test, workflow, harness, plan, design, governed worktree, branch, commit, tag, push, PR, merge, publication, deployment, release, or closure action occurred. Disposable adversarial files exist only under `/tmp/r450-rev17-review.chSUEW`; they contain review copies/instruments and no governed repository mutation. The outgoing daemon-filed PLAN-REVIEW and append-only INDEX projection are the sole own-seat repository writes.

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: no — the review read names, hashes and plan-defined evidence paths; no credential value or secret was emitted
- migration/backfill/destructive-write/canonical-data-repair: yes — the plan retains a pre-authorized candidate reset branch whose executing runner must remain exact
- money/inventory/orders/planning/accounting/trust-critical-state: yes — one-shot evidence, candidate retention, tracked preservation and acceptance classification are trust-critical execution state
- AI-or-automation-acts-downstream: yes — a later controller consumes this exact plan and a Pair Planner consumes this review
- worker/scheduler/queue/retry/async-side-effect: yes — macOS and Linux observations are one-shot and STOP-gated
- cross-repo/service-contract/generated-schema/shared-API-event: yes — pdc master, m-3 and m-4 terms govern this execution
- user-visible-control-with-materializer/downstream-consumer: no
- test-runtime-role-mismatch: no — the rev17 finalizer independently rejects incomplete or stale trees; the remaining defect is a false carrier census
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: no — no risk is accepted and no scope is widened
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: none
- scan_presented_to_operator: no — no downgrade, residual-risk acceptance, or scope expansion is requested
- operator_reply_after_scan: none
- valid_waiver: no
WAIVED_RISK_ACCEPTANCE: none

ACTIONS_GIT_REF: read-only exact-hash review at main `a86bb7a490afad00a26ff8a58f825845974cf1bd`; retained R-4.50 worktree read-only and clean at `intg/r450-discover-parity@8509157c41c5ef66595d655f39eee5107081bd32`. No product/test/workflow/harness/plan/design edit, governed worktree or branch mutation, governed commit, tag, push, PR, merge, publication, deployment, release, or closure. This daemon-filed PLAN-REVIEW and its INDEX append are the sole own-seat repository writes.
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

Done: exact-hash revision-17 PLAN-REVIEW must-revise; F5 independently confirmed closed; F1a/F1b/F2/F3/F4 preserved; one carrier-only rev16-to-rev17 numstat mismatch reproduced.

Not done: no implementation token, reset, R-4.50 continuation, product/test/workflow/harness/plan/design edit, governed worktree or branch mutation, C/H commit, tag, owner candidate review, push, PR, merge, landing push, publication, deployment, release, or closure.

Next requested action: intg.pair-planner — preserve artifact `704bd59af21f1fe59e86fd372d7660e7e4180b15fe672a483500dc30387dcd29` unchanged and re-file a corrected successor carrier reporting the actual rev16-to-rev17 delta `171/36`; do not mint token 12 on this must-revised carrier.
