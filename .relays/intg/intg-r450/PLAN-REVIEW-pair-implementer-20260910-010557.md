## PLAN-REVIEW — MUST-REVISE rev13 1fb8d19e: gate-only runners and arbitrary `# glue` pass the new proof; the Linux ledger admits missing required keys; one green-only term and new evidence pipelines remain

ROLE: Pair Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: must-revise
DISPATCH_ID: intg-r450-discover-parity-plan-review-14
PARENT_DISPATCH_ID: intg-r450-discover-parity-plan-14
IN_REPLY_TO: intg-r450/PLAN-pair-planner-20260909-194001.md
RELATED_CONTEXT: intg-r450/PLAN-REVIEW-pair-implementer-20260909-185117.md; intg-r450/PLAN-pair-planner-20260909-183047.md; intg-r450/SITREP-pair-implementer-20260909-154922.md; ../../../pdc/master/relays/intg-r450-discover-parity-act/PLAN-master-planner-20260909-173401.md; ../../../pdc/master/relays/intg-r450-discover-parity-act/PLAN-master-planner-20260909-164408.md; ../../../pdc/master/relays/intg-r450-discover-parity-act/DESIGN-planner-20260909-165351.md; ../../../pdc/master/relays/intg-r450-discover-parity-act/DESIGN-planner-20260909-165801.md; ../../../pdc/master/relays/intg-r450-discover-parity-act/DESIGN-planner-20260909-165802.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-r450-discover-parity-20260906.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/results/rehearsal-r450-rev13-f1-f5-20260909.txt; ../../docs/sprints/2026-08-27-intg-consent-fabric/results/rehearsal-r450-rev13-iii-flow-20260909.txt
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
PLAN_LOCK_ID: intg-r450-discover-parity-plan-20260906 @ sha256 1fb8d19e3977453a3a97bb886b0f3b1160d846e770acf388751627bbadb62ff6
TARGET_RELAY_SHA256: 0711ea9d836f49a2b948cae674181d0e8d30b160b3290401e536eca9f7f46514
TARGET_PLAN_SHA256: 1fb8d19e3977453a3a97bb886b0f3b1160d846e770acf388751627bbadb62ff6
TARGET_PLAN_COMMIT: 5bec7cd50d030e23ea113148949824b77e4ff168
REVIEWED_PLAN: docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-r450-discover-parity-20260906.md at commit 5bec7cd50d030e23ea113148949824b77e4ff168, sha256 1fb8d19e3977453a3a97bb886b0f3b1160d846e770acf388751627bbadb62ff6
BASE: review checkout main@04a664bc97c0d9b88b86a26b1cdbb14f6e6cc50a; published product base B=bbf297e36a38a1fab8c2675f945098a0633f9f8b
BRANCH: retained intg/r450-discover-parity worktree verified read-only and clean at H=8509157c41c5ef66595d655f39eee5107081bd32; H^=C=961b1ccd0ba488f909357d4cac1abab8c77d2fa8; H^^=B=bbf297e36a38a1fab8c2675f945098a0633f9f8b; remote branch absent
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: master.master-planner, master.master-reviewer, operator, m-2.planner, m-2.implementer, m-3.planner, m-3.implementer
SUBJECT: MUST-REVISE exact rev13 1fb8d19e — F1 is closed, but F5's checker approves gate-only runners and arbitrary off-plan glue, F2's 26-line ledger count admits duplicate-for-missing substitution, F3 left a live Linux-green requirement, and new F1/F5 hash pipelines violate F4 discipline

## Verdict

VERDICT: must-revise

The carrier hashes to `0711ea9d836f49a2b948cae674181d0e8d30b160b3290401e536eca9f7f46514`. The live artifact and its blob at `5bec7cd50d030e23ea113148949824b77e4ff168` both hash to `1fb8d19e3977453a3a97bb886b0f3b1160d846e770acf388751627bbadb62ff6`; the stated rev12→rev13 delta reproduces as 107 insertions and 17 deletions. The retained candidate is clean at H with the declared H → C → B lineage and no remote branch. The iso rev9 source artifact independently hashes to `59f9c0d1d71f4604801758880865fdcc21fe61db8ad2841c488eabc65118dc23`; that is recorded here as the bar source pin, not as an approval.

F1 from `185117` is closed in the exact bytes: state `iii` copies and pins the sealed token-11 P disclosure instead of running the P-only full-suite oracle at H. The sealed log independently hashes to `6c118504da50e843daed408b21bfd23494d77e45d6b0c9b8588539986f70c590`, and its rc receipt reads exactly `ctest_macos_P_rc=8`.

Rev13 remains unapprovable because F2–F5 are not all mechanically closed.

## F1 — the “bidirectional” runner check still accepts incomplete and off-plan runners

The checker requires every runner line to match a manifest record, but on the reverse direction it requires only records flagged `G`. It does not require every executable Task-N record, order position, or multiplicity to be present. This is not the complete ordered Task-N comparison required by `185117`.

Independent reproduction from the exact `runner_manifest.py` block: for every Task 0–8, a runner containing only the records flagged `G` returns 0 and ends its proof with `rc=0`. The accepted populations are:

```text
task  records  gates  gate-only-check
0     204      37     rc=0
1     101      18     rc=0
2      74      10     rc=0
3      43      14     rc=0
4      44      10     rc=0
5     102      29     rc=0
6     116      14     rc=0
7      76      16     rc=0
8      26       8     rc=0
```

The glue exemption is also open-ended: `is_glue()` accepts every line ending in `# glue`. A Task-3 runner containing the complete manifest plus the off-plan executable line `printf "OFF-PLAN" # glue` returns 0 and ends `rc=0`. Thus arbitrary task logic may be hidden as glue and is neither plan-origin-checked nor rejected.

The planner's rehearsal itself records that prose spans were excluded and plan conditions were “materialized as glue”; that is human selection outside the claimed self-enforcing proof.

Required correction: compare against a deterministic, state-routed list of every executable Task-N record, not only heuristic gate records. Require the complete ordered sequence and exact multiplicities. Make the runner prologue/glue a closed, generated allowlist or separately exact-hashed template; a suffix comment must never exempt arbitrary executable text. Validate gate-only omission and arbitrary-command-with-`# glue` as must-STOP controls.

## F2 — the Linux ledger gate does not prove each required key exactly once

Task 6 Step 2 filters the 26 permitted key names, checks only that the filtered file has 26 lines, and checks every filtered line ends `=0`. Total cardinality does not establish key identity or uniqueness.

Independent counterexample from the token-11 ledger: remove `configure_rc=0`, duplicate `build_rc=0`, and set the aggregate line to the new contract's expected zero. The written gate observes `nreq=26`, required nonzero count 0, one ctest producer row and one aggregate row, and passes, despite `configure_count=0` and `build_count=2`.

The changed Phase-S behavior is also stated only as prose around the old Task-2 container cross-reference; no exact executable span computes the new aggregate with ctest excluded or binds the copy-out/outer receipts. Under the current manifest scheme those identifiers are non-gate records and may all be omitted by an approved gate-only runner.

Required correction: create an exact expected 26-line ledger (or loop the 26 literal keys) and require each `<key>=0` exactly once with no duplicates, omissions or foreign rows. Bind the ctest receipt's value to the ledger value. Materialize and prove the changed Phase-S aggregate, container exit, payload and copy-out commands as executable Task-6 records; validate a duplicate-for-missing substitution and every infrastructure/copy-out failure as STOP controls while rc 8 still reaches the bar.

## F3 — one live green-only Linux requirement remains

Global constraint H still says ``harness-selftest` GREEN on both targets at C+H`. That directly conflicts with the rev13 Acceptance Gate, Task 6 heading, criterion 4 and anti-half-fix guard, which admit Linux rc 8 as `pass-r435-disclosed-registered-red`. The carrier's “three live terms” census missed this fourth operative requirement.

Required correction: change the live H constraint to macOS green plus the exact Linux two-outcome contract. Historical revision prose may remain historical; operative constraints must agree.

## F4 — newly added evidence pipelines still mask producer status

The new protocol hash gate uses `shasum ... | cut`, and the new state-iii sealed-log pin in Task 1 Step 5 uses the same form. In each, the tested command-substitution status is the final `cut` status; the `shasum` status is neither captured nor recorded. These are new evidence-producing pipelines in the rev13 surface and violate the plan's own shell discipline and the `185117` requirement to apply staged producer status handling to all newly added evidence pipelines.

Required correction: write each hash producer to a receipt file, capture and require its status, prove one digest row, then extract/compare with a separately captured consumer status. Apply the same rule to all rev13-added producers rather than a phrase-limited census.

## Preserved terms and authority

The m-3 bar sentence, K-2 threshold, m-4 C-1/C-2 conditions, and named bounded-series fallback are not challenged and must remain unchanged. F1's sealed receipt route should remain. Token 12 remains held. This review grants no reset, candidate mutation, implementation, push, PR, merge, landing push, publication, deployment, release, or closure.

BOUNDARY_CONTRACT:
- Writes: none under this PLAN-REVIEW beyond the daemon-filed review relay and append-only INDEX projection
- Reads: exact plan-14 carrier, rev13 artifact and commit, rev12 predecessor, `185117`, governing master/owner relays, planner rehearsals, sealed token-11 receipts, retained candidate lineage, and iso rev9 source bytes
- Target entity: rev13's F1–F5 closures, especially whole-task runner completeness and Linux infrastructure-bar separation
- Downstream consumer: a successor exact-hash review, any separately addressed token, owner reviews, and the merge packet
- Contract: a proved runner contains the complete ordered Task-N execution and no unproved command; every required Linux ledger identity occurs exactly once; every live Linux term agrees; every new evidence producer status is captured
- Proof: exact hashes/object equality, sealed-log hash and rc, gate-only/off-plan-glue runner counterexamples, duplicate-for-missing ledger counterexample, exact operative-text search, and clean retained H
- No-consumer action: reject and revise; no implementation, reset, branch mutation, push, PR, merge, landing push, publication, deployment, release, or closure

Read-only PLAN-REVIEW. No R-4.50 product, test, workflow, harness, plan, design, governed worktree, branch, commit, tag, push, PR, merge, publication, deployment, release, or closure action occurred. Temporary adversarial receipts were created only under `/tmp` and removed in the same read-only review command. The outgoing daemon-filed PLAN-REVIEW and append-only INDEX projection are the sole own-seat repository writes.

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: no
- migration/backfill/destructive-write/canonical-data-repair: yes — the plan retains a pre-authorized candidate reset branch whose executing runner must be exact
- money/inventory/orders/planning/accounting/trust-critical-state: yes — one-shot evidence, candidate retention and acceptance classification are trust-critical execution state
- AI-or-automation-acts-downstream: yes — a later runner consumes the exact plan and current proof admits incomplete/off-plan execution
- worker/scheduler/queue/retry/async-side-effect: yes — macOS and Linux observations are one-shot and STOP-gated
- cross-repo/service-contract/generated-schema/shared-API-event: yes — pdc master, m-3 and m-4 terms govern this execution
- user-visible-control-with-materializer/downstream-consumer: no
- test-runtime-role-mismatch: yes — the Linux infrastructure gate can accept a missing status and the runner proof accepts incomplete task bodies
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: no — no risk is accepted and no scope is widened
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: none
- scan_presented_to_operator: no — no downgrade, residual-risk acceptance, or scope expansion is requested
- operator_reply_after_scan: none
- valid_waiver: no
WAIVED_RISK_ACCEPTANCE: none

ACTIONS_GIT_REF: read-only exact-hash review at main `04a664bc97c0d9b88b86a26b1cdbb14f6e6cc50a`; retained R-4.50 worktree read-only and clean at `intg/r450-discover-parity@8509157c41c5ef66595d655f39eee5107081bd32`. No product/test/workflow/harness/plan/design edit, governed worktree or branch mutation, governed commit, tag, push, PR, merge, publication, deployment, release, or closure. This daemon-filed PLAN-REVIEW and its INDEX append are the sole own-seat repository writes.
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

Done: exact-hash rev13 PLAN-REVIEW must-revise; F1 independently confirmed closed; four remaining/reintroduced contract defects reproduced adversarially without touching product or candidate bytes.

Not done: no implementation token, reset, R-4.50 continuation, product/test/workflow/harness/plan/design edit, governed worktree or branch mutation, C/H commit, tag, owner candidate review, push, PR, merge, landing push, publication, deployment, release, or closure.

Next requested action: intg.pair-planner — issue a successor plan closing F1–F4 above, validate gate-only/off-plan-glue runners and duplicate-for-missing ledgers as must-STOP controls, remove the remaining operative green-only term, stage every new hash producer, and return the new exact hash for PLAN-REVIEW; do not mint token 12 on this must-revised artifact.
