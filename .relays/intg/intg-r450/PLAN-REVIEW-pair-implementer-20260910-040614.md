## PLAN-REVIEW — MUST-REVISE rev14 e9d51695: the controller trusts a mutable extractor/checker, and the checker still admits a plan-side dropped non-gate executable Step

ROLE: Pair Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: must-revise
DISPATCH_ID: intg-r450-discover-parity-plan-review-15
PARENT_DISPATCH_ID: intg-r450-discover-parity-plan-15
IN_REPLY_TO: intg-r450/PLAN-pair-planner-20260910-033841.md
RELATED_CONTEXT: intg-r450/PLAN-REVIEW-pair-implementer-20260910-010557.md; intg-r450/PLAN-pair-planner-20260909-194001.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-r450-discover-parity-20260906.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/results/rehearsal-r450-rev14-controls-20260910.txt; ../../docs/sprints/2026-08-27-intg-consent-fabric/results/rehearsal-r450-rev14-flow-20260910.txt; ../../docs/sprints/2026-08-27-intg-consent-fabric/results/rehearsal-r450-rev14-phase-s-fault-matrix-20260910.txt; ../../../pdc/master/relays/intg-r450-discover-parity-act/DESIGN-planner-20260909-165802.md
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
PLAN_LOCK_ID: intg-r450-discover-parity-plan-20260906 @ sha256 e9d51695395aa8bde2ebdd6c11253724d00f62b46d7a1a7dc2d823fab7936299
TARGET_RELAY_SHA256: 8f8f27d4e44a47f0882d2dc3e7e1d52bc76eddfaf02d3e1659199f90cadc2592
TARGET_PLAN_SHA256: e9d51695395aa8bde2ebdd6c11253724d00f62b46d7a1a7dc2d823fab7936299
TARGET_PLAN_COMMIT: 8183e0f
REVIEWED_PLAN: docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-r450-discover-parity-20260906.md at commit 8183e0f, sha256 e9d51695395aa8bde2ebdd6c11253724d00f62b46d7a1a7dc2d823fab7936299
BASE: review checkout main@8b154318e9736f54432cede2676b1a4637f7ed04; published product base B=bbf297e36a38a1fab8c2675f945098a0633f9f8b
BRANCH: retained intg/r450-discover-parity worktree verified read-only and clean at H=8509157c41c5ef66595d655f39eee5107081bd32; H^=C=961b1ccd0ba488f909357d4cac1abab8c77d2fa8; H^^=B=bbf297e36a38a1fab8c2675f945098a0633f9f8b; remote branch absent
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: master.master-planner, master.master-reviewer, operator, m-2.planner, m-2.implementer, m-3.planner, m-3.implementer
SUBJECT: MUST-REVISE exact rev14 e9d51695 — preserve F2/F3/F4, but authenticate plan_blocks.py before every controller use and make plan-side completeness cover every executable Step record, not only GATE spans

## Verdict

VERDICT: must-revise

The carrier hashes to `8f8f27d4e44a47f0882d2dc3e7e1d52bc76eddfaf02d3e1659199f90cadc2592`. The live artifact and its blob at `8183e0f` both hash to `e9d51695395aa8bde2ebdd6c11253724d00f62b46d7a1a7dc2d823fab7936299`; the stated rev13→rev14 artifact delta reproduces as 1026 insertions and 105 deletions. The retained candidate is clean at H with the declared H → C → B lineage and no remote branch. The iso rev9 source artifact independently hashes to `59f9c0d1d71f4604801758880865fdcc21fe61db8ad2841c488eabc65118dc23`; that is recorded as the bar source pin, not as an approval.

All nine current task blocks extract and return `bytes=equal prologue=ok`, zero foreign/omitted/out-of-order counts, and `rc=0`. Those results do not close F1 because the trust root and reverse-completeness predicates below are absent from the checker/controller contract.

## F1a — `plan_blocks.py` is mutable after bootstrap and is trusted for both extraction and proof

Protocol (0), artifact line 40, bootstraps and self-compares `plan_blocks.py` once. It records no immutable expected digest for that instrument and the controller never authenticates it. Controller lines 208–209 then invoke the same writable file first to produce `task-N.sh` and again to certify that output.

Independent exact-controller reproduction: bootstrap the exact rev14 `plan_blocks.py` and `run-task.sh`; preserve the controller and its recorded digest; edit only `plan_blocks.py` after bootstrap so `extract task-0` emits a harmless non-plan Task 0 and `check` prints `rc=0`; invoke the exact controller by its required path. The result is:

```text
controller_rc=0
controller_output=task-0 done rc=0
task_done=rc=0
bypass_marker=MUTABLE-EXTRACTOR-BYPASS
```

The pristine rev14 checker rejects that materialized runner with `BYTES-DIFFER` and rc 5. Thus the exact controller has accepted and completed bytes that are not BLOCK task-0. The rehearsal controls edit the controller and runners, but contain no control that edits the extractor/checker alone.

Required correction: before every `extract`, `list`, or `check` use, authenticate `plan_blocks.py` against an expected value anchored independently of the mutable instrument and its outputs. A fixed bootstrap extractor or a literal digest inside the already-authenticated controller can supply that trust root; comparing an extractor-produced digest to another mutable extractor-produced receipt does not. Add the exact negative control: edit only `plan_blocks.py` after bootstrap; `run-task.sh 0` must STOP before materialization/execution and must not write `task-0.done`.

## F1b — reverse completeness still covers only heuristic GATE spans

Checker lines 145–174 build all inline spans but require presence/order only for `gates = [s for s in sp if any(g in s for g in GATE)]`. It never requires every executable Step span or its multiplicity. Byte equality proves only that runner equals the task block; it does not prove that the task block contains every executable record declared by the Steps.

Independent plan-side counterexample from exact rev14: in a scratch copy, leave Task 0 Step 1's declared producer ``printf 'B=%s\n' "$BASE" > "$EVID/B.txt"`` present, delete that one non-gate line from BLOCK task-0, extract the runner from the mutated block, and run the exact rev14 checker. It returns:

```text
extract_rc=0
checker_rc=0
bytes=equal prologue=ok lines=69 spans=249 gates=43 foreign=0 omitted=0 out_of_order=0
rc=0
step_span_count=1
runner_line_count=0
```

This is the same missing reverse direction identified in `010557`, narrowed to a non-gate producer. The current plan-side controls remove/edit the amend command, which is a GATE span, so they do not exercise the open class.

Required correction: define the complete, state-routed set of executable Step records mechanically and require its ordered, multiplicity-exact equality with the task block, while retaining the closed prologue/comment allowlist. Add the exact negative control above, plus at least one repeated executable-record multiplicity control; both must return rc 5 before task execution.

## F2, F3 and F4 — independently closed; preserve unchanged

F2 closes. The exact Task 6 ledger line produced 26 required identities and passed a synthetic valid 28-line ledger. Duplicate-for-missing, a foreign row, receipt/value mismatch and a nonzero required identity each reached STOP. `linux-suite.sh` records ctest separately and excludes `ctest_rc` from the required aggregate loop; its payload/copy-out receipts are executable block bytes.

F3 closes. The operative Global constraints section contains no green-only Linux hit and states macOS rc 0 plus the Linux two-outcome contract.

F4 closes. No executable inline span or fenced-code line contains a `shasum` producer piped to `cut`, `grep`, `sed`, `awk`, `sort`, `wc`, `head`, `tail`, `tr`, `xargs` or `tar`. The two raw prose hits are historical descriptions of the removed `shasum … | cut` class, not executable spans.

Preserve the F2 identity/total/binding gates, the executable Linux scripts, the F3 two-outcome terms, the F4 staged producers, F1's exact task-block equality, the m-3 bar sentence, K-2 threshold, m-4 C-1/C-2 conditions, and named bounded-series fallback unchanged.

## Preserved authority

Token 12 remains held. This review grants no reset, candidate mutation, implementation, push, PR, merge, landing push, publication, deployment, release, or closure.

BOUNDARY_CONTRACT:
- Writes: none under this PLAN-REVIEW beyond the daemon-filed review relay and append-only INDEX projection
- Reads: exact plan-15 carrier, rev14 artifact/blob and predecessor, `010557`, governing owner source, planner rehearsals, retained candidate lineage, and iso rev9 source bytes
- Target entity: rev14's F1 runner/extractor trust and complete ordered executable-record proof; confirmation that F2–F4 remain closed
- Downstream consumer: a successor exact-hash review, any separately addressed token, owner reviews, and the merge packet
- Contract: the controller authenticates every proof instrument independently before use; a proved runner contains every executable Step record with exact order and multiplicity and no unproved command
- Proof: exact hashes/object equality, exact-controller mutable-extractor bypass, plan-side dropped non-gate producer counterexample, nine exact block checks, exact ledger mutation controls, operative-text and pipeline scans, and clean retained H
- No-consumer action: reject and revise; no implementation, reset, branch mutation, push, PR, merge, landing push, publication, deployment, release, or closure

Read-only PLAN-REVIEW. No R-4.50 product, test, workflow, harness, plan, design, governed worktree, branch, commit, tag, push, PR, merge, publication, deployment, release, or closure action occurred. Temporary adversarial files existed only in automatically removed system temporary directories. The outgoing daemon-filed PLAN-REVIEW and append-only INDEX projection are the sole own-seat repository writes.

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: no
- migration/backfill/destructive-write/canonical-data-repair: yes — the plan retains a pre-authorized candidate reset branch whose executing runner must be exact
- money/inventory/orders/planning/accounting/trust-critical-state: yes — one-shot evidence, candidate retention and acceptance classification are trust-critical execution state
- AI-or-automation-acts-downstream: yes — a later controller consumes this exact plan and currently trusts a mutable extractor/checker
- worker/scheduler/queue/retry/async-side-effect: yes — macOS and Linux observations are one-shot and STOP-gated
- cross-repo/service-contract/generated-schema/shared-API-event: yes — pdc master, m-3 and m-4 terms govern this execution
- user-visible-control-with-materializer/downstream-consumer: no
- test-runtime-role-mismatch: yes — the proof instrument can certify and execute non-plan bytes, and plan-side non-gate omissions pass
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: no — no risk is accepted and no scope is widened
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: none
- scan_presented_to_operator: no — no downgrade, residual-risk acceptance, or scope expansion is requested
- operator_reply_after_scan: none
- valid_waiver: no
WAIVED_RISK_ACCEPTANCE: none

ACTIONS_GIT_REF: read-only exact-hash review at main `8b154318e9736f54432cede2676b1a4637f7ed04`; retained R-4.50 worktree read-only and clean at `intg/r450-discover-parity@8509157c41c5ef66595d655f39eee5107081bd32`. No product/test/workflow/harness/plan/design edit, governed worktree or branch mutation, governed commit, tag, push, PR, merge, publication, deployment, release, or closure. This daemon-filed PLAN-REVIEW and its INDEX append are the sole own-seat repository writes.
RELAY_LINT: incoming PLAN exact-file clean under daemon-matched v2.9.2 with freshness disabled and one unique INDEX row; outgoing draft/render require fresh exact-file lint, daemon admission/render, draft/render byte equality, one unique INDEX row, and engine verification. Full-root inherited noise is not represented as exact-file truth.
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

Done: exact-hash rev14 PLAN-REVIEW must-revise; F2, F3 and F4 independently confirmed closed; two remaining F1 trust/completeness defects reproduced without touching product or candidate bytes.

Not done: no implementation token, reset, R-4.50 continuation, product/test/workflow/harness/plan/design edit, governed worktree or branch mutation, C/H commit, tag, owner candidate review, push, PR, merge, landing push, publication, deployment, release, or closure.

Next requested action: intg.pair-planner — preserve F2/F3/F4 and the exact-block runner design; issue a successor that independently authenticates `plan_blocks.py` before every use and proves every executable Step record with exact order/multiplicity; validate extractor-only mutation and plan-side non-gate omission as must-STOP controls; do not mint token 12 on this must-revised artifact.
