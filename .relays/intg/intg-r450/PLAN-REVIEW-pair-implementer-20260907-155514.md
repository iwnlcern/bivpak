## PLAN-REVIEW — MUST-REVISE exact rev6 3a17a74f: Task 7 asserts the census is at H but both executable arms still scan C

ROLE: Pair Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: must-revise
DISPATCH_ID: intg-r450-discover-parity-plan-review-6
PARENT_DISPATCH_ID: intg-r450-discover-parity-plan-6
IN_REPLY_TO: intg-r450/PLAN-pair-planner-20260907-145505.md
RELATED_CONTEXT: intg-r450/SITREP-pair-implementer-20260906-201740.md; intg-r450/PLAN-REVIEW-pair-implementer-20260906-192951.md; ../../../pdc/master/relays/intg-r450-discover-parity-act/PLAN-master-planner-20260907-134909.md; ../../../pdc/master/relays/intg-r450-discover-parity-act/DESIGN-REVIEW-master-reviewer-20260907-134011.md; ../../../pdc/master/domains/m-3-restore-cli/design/2026-09-01-e2-store-isolation-r437.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-r450-discover-parity-20260906.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new human gate — this exact-hash review returns one executable target correction to the pair Planner. It does not grant implementation. The m-2 fenced review of C, m-3 reviews of C and H, merge bar, operator condition-4 token, landing-push rule, and absolute release hold remain
COMMISSION_ID: intg-consent-fabric
COMMISSION_SCOPE: the operator-authorized integration phase (2026-08-26) executed by ONE commissioned pair — sub-step 1 first, the A6 rev14 consent-UX fabric with the engine unwired per the sealed spine; subsequent sub-steps (format act consuming LOCKED M rev8 + LOCKED N; then wiring at product scope) each behind their standing gates incl. m-4's reachability re-review before any wiring; sealed design only; STOPs route UP; no merge/push/publication/release authority
COMMISSION_TO: intg.pair-planner
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: m2-r450-discover-fence-rev2-20260903; m3-e2-store-isolation-20260901
DESIGN_LOCK_ID: m2-r450-discover-fence-rev2-20260903 @ sha256 f2216ee606a03b0b5b0b7f4562fed52a7349219c28990e6ee3e89b0cc25e8c6f; m3-e2-store-isolation-20260901 @ sha256 00046a657abd6c5792e3c6222c8690b39f1a773ecbc2473ca9af2845a95813af
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: intg-r450-discover-parity-plan-20260906 @ sha256 3a17a74f0279b688df6dd4dbf68896b6945d8c9893993f5af59b3fe696c62432
TARGET_RELAY_SHA256: 8ae1abcdf1d411a4f45dabf2d7187942a4971db40a562fc823b87b57f4679c96
TARGET_PLAN_SHA256: 3a17a74f0279b688df6dd4dbf68896b6945d8c9893993f5af59b3fe696c62432
TARGET_PLAN_COMMIT: ca61ef83ee7dbc2bdf1d65890be2564f70108aca
REVIEWED_PLAN: docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-r450-discover-parity-20260906.md at commit ca61ef83ee7dbc2bdf1d65890be2564f70108aca, sha256 3a17a74f0279b688df6dd4dbf68896b6945d8c9893993f5af59b3fe696c62432
BASE: review checkout main@860577167c82da9f910c0581295dc4e6a32dadec; published product base and retained candidate HEAD bbf297e36a38a1fab8c2675f945098a0633f9f8b
BRANCH: retained intg/r450-discover-parity worktree verified read-only at bbf297e36a38a1fab8c2675f945098a0633f9f8b with exactly the two prior unstaged in-scope files, sha256 4e105052a17b7e0d99bfeca28ac45cac1f6ed3c5ba0e9ba9ec62a34e530a3a51 and 90615eeb414c1cdcabeff124f95aafa6f729764860c9782f023f401a35d7a8e9; no P, C, or H authored this review
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: master.master-planner, master.master-reviewer, operator, m-2.planner, m-2.implementer, m-3.planner, m-3.implementer
SUBJECT: MUST-REVISE exact rev6 3a17a74f — replace both Task 7 Step 2 census producers' C arguments with H; the current executable bytes cannot prove the required branch-head census

## Verdict

VERDICT: must-revise

The addressed carrier hashes exactly to `8ae1abcdf1d411a4f45dabf2d7187942a4971db40a562fc823b87b57f4679c96`, has one unique INDEX row, and passes both v2.9.2 and v2.9.3 exact-file lint with freshness disabled. Daemon-matched v2.9.2 root verification returned `verify_ok=True`. The locked artifact hashes exactly to `3a17a74f0279b688df6dd4dbf68896b6945d8c9893993f5af59b3fe696c62432`, and commit `ca61ef83ee7dbc2bdf1d65890be2564f70108aca` contains those bytes.

Revision 6 correctly folds master's arm-A release: C remains the three-path candidate, H is its three-file harness child, P/C suite reds are disclosures bounded to `harness-selftest`, and acceptance moves to H on both platforms. The requested helper, fidelity, and retained-log probes reproduce successfully. One executable census defect prevents approval.

## F1 — MUST-REVISE: the claimed H census executes at C in both arms

Task 7 Step 2 binds `H`, proves `HEAD == H`, and says every `"$C"` in the two arms is executed as `"$H"`. The commands that actually produce the evidence do the opposite:

- Tree arm: `git grep ... "$C" -- . > "$EVID/census-tree-raw.txt"`.
- History arm: `git rev-list "$C" > "$EVID/rl.txt"`.

Those literal commands scan C and C's reachable history. They do not inspect H's tree or include H in the history walk. Consequently, a forbidden alternation introduced by any of H's three harness files would be absent from both evidence arms while both deltas could still be empty. This contradicts master's required sequence `census of record at the branch head`, the plan's Acceptance criterion 6, Task 8's pre-push re-assertion at H, and the IMPL return's claim that both H census deltas are empty.

Required correction: in Task 7 Step 2, change the tree producer's revision argument from `"$C"` to `"$H"` and the history producer from `git rev-list "$C"` to `git rev-list "$H"`; then re-run the written two-arm form at an actual scratch H and preserve the unchanged expectations only if the resulting H evidence proves them. Update any mechanical rehearsal claim that currently treats the prose substitution as execution. No surface, fence, test, owner, vehicle, or release term needs to broaden.

## Independent evidence

- Incoming relay: exact sha256 `8ae1abcdf1d411a4f45dabf2d7187942a4971db40a562fc823b87b57f4679c96`; unique INDEX row; v2.9.2 and v2.9.3 exact-file lint clean; daemon-matched v2.9.2 verification `verify_ok=True`.
- Plan: exact sha256 `3a17a74f0279b688df6dd4dbf68896b6945d8c9893993f5af59b3fe696c62432` at `ca61ef83ee7dbc2bdf1d65890be2564f70108aca`; upstream master release and iso-rev8 pins match.
- Retained candidate: branch `intg/r450-discover-parity`, HEAD `bbf297e36a38a1fab8c2675f945098a0633f9f8b`, exactly two unstaged paths; hashes match the plan's resume checkpoint.
- The four extracted helper files were byte-compared to their exact fenced plan blocks before execution. `h_fidelity.py` returned 5 on the retained stale stub with only ROW 1 and ROW 5 mismatching; after `h_stub.py` on a scratch harness copy it returned 0 with all five rows `ok`.
- On the same scratch copy, `h_stub.py`, `h_test.py`, and `h_e3pin.py` each returned 0 once; `h_e3pin.py` computed `new=4e105052a17b7e0d99bfeca28ac45cac1f6ed3c5ba0e9ba9ec62a34e530a3a51`. Each helper's second application returned 3 and left its target hash unchanged.
- The written failing-set extraction against the retained real `ctest-macos-P.log` returned grep 0, sed 0, diff 0, exactly `harness-selftest`; the cause scan returned 33 `claude_adapter_file` hits.
- External resolved scratch evidence: `/private/var/folders/hq/f0qq8v_103q9y8prfn20rzx80000gn/T/r450-planreview6-2Axuc5`. It did not modify a governed worktree.

BOUNDARY_CONTRACT:
- Writes: a later separately authorized implementation may write C's three ruled files and H's exact three harness files, in separate commits and under their separate owner fences
- Reads: sealed c1 section 7, exact m-2 fence, iso rev8 follow-through, m-3 CG-R7, and observed P/C/H evidence
- Target entity: Claude store discovery parity, corresponding two count-gate literals, and the H harness model/re-pin follow-through
- Downstream consumer: open, pack, E3 tripwire, harness selftest, count gate, branch-head census, PR vehicle, and owner review gates
- Contract: P then C then H; acceptance and both census arms at H; two commits, two owners, one PR
- Proof: exact candidate hashes; fail-closed witness; P/C disclosures; H green suites; P/C/H tuple equality; exact C and H file fences; both census arms against written expectations
- No-consumer action: reject and STOP UP; no out-of-fence byte, tag, push, PR, merge, landing push, publication, or release expansion

Read-only PLAN-REVIEW. No R-4.50 product, test, workflow, harness, plan, design, governed worktree, branch, commit, tag, push, PR, merge, publication, deployment, release, or closure action occurred. Review probes wrote external temporary evidence only. The outgoing daemon-filed PLAN-REVIEW and append-only INDEX projection are the sole own-seat repository writes.

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: yes — the defective step is the secrets-pattern census, but no matched values were printed or retained in this review
- migration/backfill/destructive-write/canonical-data-repair: no
- money/inventory/orders/planning/accounting/trust-critical-state: yes — exact run provenance and branch-head census evidence are trust-critical
- AI-or-automation-acts-downstream: yes — later separately authorized work changes workflow count gates and opens a PR vehicle
- worker/scheduler/queue/retry/async-side-effect: yes — later Docker/test and one-attempt remote push steps remain gated
- cross-repo/service-contract/generated-schema/shared-API-event: yes — pdc design and two owner surfaces govern this act
- user-visible-control-with-materializer/downstream-consumer: no
- test-runtime-role-mismatch: yes — the revision selector determines which commit the census actually observes
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: no — an exact two-token target correction closes the defect without broadening scope
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: none
- scan_presented_to_operator: no — no downgrade, residual-risk acceptance, or scope expansion is requested
- operator_reply_after_scan: none
- valid_waiver: no
WAIVED_RISK_ACCEPTANCE: none

ACTIONS_GIT_REF: read-only exact-hash review at main 860577167c82da9f910c0581295dc4e6a32dadec; retained R-4.50 worktree read-only at intg/r450-discover-parity@bbf297e36a38a1fab8c2675f945098a0633f9f8b with its exact two prior unstaged files; external scratch evidence only. No product/test/workflow/harness/plan/design edit, governed worktree or branch mutation, commit, tag, push, PR, merge, publication, deployment, release, or closure. This daemon-filed PLAN-REVIEW and its INDEX append are the sole own-seat repository writes.
RELAY_LINT: incoming carrier exact-file clean under v2.9.2 and v2.9.3 with freshness disabled; daemon-matched v2.9.2 root verification ok. Outgoing draft/render require both exact-file linters clean, daemon v2.9.2 admission/render through its matching client, draft/render byte equality, one unique INDEX row, and engine verification. Full-root historical noise is not represented as exact-file truth.
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
 ?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-LENSFOLD-COMPLETE-20260810-092751.md
 ?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-MICROFOLD-DONE-WITH-CONCERNS-20260810-160710.md
 ?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-PR24-MERGED-STEP4-20260810-184033.md
 ?? .relays/s4/s4-matrix/SITREP-implementer-20260825-220111.md
 ?? docs/sprints/2026-08-04-s4-step4/MIGRATION-adt-skills-2.9-20260816.md
 ?? relay-draft-intg-task4-stop.md
 ?? .relays/intg/.engine/drafts/intg.pair-implementer/PLAN-REVIEW-R450-REV6-MUST-REVISE.md
Literal status captured before daemon submission. Every listed path except this draft is inherited root state. After daemon render, `.relays/intg/INDEX.md` and the rendered PLAN-REVIEW are the expected additional own-seat paths.

Done: exact-hash revision-6 PLAN-REVIEW must-revise; helper/fidelity/disclosure folds independently reproduced; one branch-head census target defect isolated.
Not done: no implementation token, R-4.50 implementation continuation, product/test/workflow/harness edit, governed worktree or branch mutation, P/C/H commit, tag, owner candidate review, push, PR, merge, landing push, publication, deployment, release, or closure.
Next requested action: intg.pair-planner — issue rev7 under `intg-r450-discover-parity-plan-7`, replacing both Task 7 Step 2 `C` revision arguments with `H` and re-running the written two-arm H census; do not mint `intg-r450-discover-parity-impl-3` from this must-revise review.
