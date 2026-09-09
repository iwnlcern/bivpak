## PLAN-REVIEW — MUST-REVISE exact rev8 8e45acd3: skip-set membership repair is sound, but the P-bound resume cannot pass the inherited Task 0/1 gates

ROLE: Pair Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: must-revise
DISPATCH_ID: intg-r450-discover-parity-plan-review-8
PARENT_DISPATCH_ID: intg-r450-discover-parity-plan-8
IN_REPLY_TO: intg-r450/PLAN-pair-planner-20260908-234427.md
RELATED_CONTEXT: intg-r450/SITREP-pair-implementer-20260908-231512.md; intg-r450/IMPL-pair-planner-20260908-143301.md; intg-r450/PLAN-REVIEW-pair-implementer-20260907-163759.md; intg-r450/PLAN-pair-planner-20260907-162715.md; ../../../pdc/master/relays/intg-r450-discover-parity-act/PLAN-master-planner-20260908-140952.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-r450-discover-parity-20260906.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new human gate — this is a plan-owned executable resume correction and does not grant implementation; the m-2 fenced review of C, m-3 reviews of C and H, merge bar, operator condition-4 token, landing-push rule, and absolute release hold remain
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
PLAN_LOCK_ID: intg-r450-discover-parity-plan-20260906 @ sha256 8e45acd3a2609f5c44dc507e621ea88bd8a399f55c66c25388d7079944149e72
TARGET_RELAY_SHA256: a802d0a267c2041ef26a20ff55381a96f699fadf33b3df7d63c6fcb316211588
TARGET_PLAN_SHA256: 8e45acd3a2609f5c44dc507e621ea88bd8a399f55c66c25388d7079944149e72
TARGET_PLAN_COMMIT: 09aa89530759101267250ec04232265ef473dfb0
REVIEWED_PLAN: docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-r450-discover-parity-20260906.md at commit 09aa89530759101267250ec04232265ef473dfb0, sha256 8e45acd3a2609f5c44dc507e621ea88bd8a399f55c66c25388d7079944149e72
BASE: review checkout main@806c09cab7452bab72d3a09be71183944bea3cf5; published product base B=bbf297e36a38a1fab8c2675f945098a0633f9f8b
BRANCH: retained intg/r450-discover-parity worktree verified read-only, clean, at P=54954281b30cae113f399055fff106963a37a443; no C or H authored in this review
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: master.master-planner, master.master-reviewer, operator, m-2.planner, m-2.implementer, m-3.planner, m-3.implementer
SUBJECT: MUST-REVISE exact rev8 8e45acd3 — skipset.py passes the real and mutant membership cases, but state (ii) is unreachable through the unconditional B gate, contradicts the zero cut-point, lacks a materialized selector/receipt, and cannot pass the post-venv status delta

## Verdict

VERDICT: must-revise

The new skip-set comparison form is correct. Extracted from the locked artifact, `skipset.py` returned 0 with `same_set=yes` for the real B `expected_skips` names and the real token-7 P observed tuple despite their different ordering; it returned 5 for a changed name, 5 for a dropped name with observed count 2, and 2 when the observed line was absent. Bash and zsh reproduced the same four outcomes. The global membership constraint and the Task 2 / Task 4 invocations close the `231512` order-only plan defect.

The new P-bound resume does not form an executable path through the unchanged surrounding steps. The isolated state-(ii) span passes at P, but the full affected Task 0 / Task 1 flow is blocked by the findings below. Rev8 therefore cannot mint an implementation token.

## F1 — fatal: the unconditional B gate precedes and excludes state (ii)

Task 0 Step 2 first requires `HEAD == bbf297e36a38a1fab8c2675f945098a0633f9f8b`, then later describes state (ii) as `HEAD == 54954281b30cae113f399055fff106963a37a443`. At the retained P worktree, the earlier required B predicate returns 1. No runner can reach state (ii) while obeying Step 2 in document order.

Required correction: move HEAD identity into one materialized, mutually exclusive state selector. Require the exact branch and then select state (i) only at B or state (ii) only at P; every other head must STOP UP.

## F2 — fatal: the promised resume-state receipt has no producer or executable selector

Step 2 says exactly one admissible state is recorded as `resume_state=i|ii` in `$EVID/resume-state.txt`, but no command selects a branch, writes that file, status-checks the write, or verifies its exact content. The receipt is absent after executing the written state-(ii) span. A per-task runner would otherwise encounter both mutually exclusive state bodies in sequence.

Required correction: materialize one exact `if` / `elif` / `else` selection, capture command statuses, write and gate `$EVID/resume-state.txt`, and make every later state-dependent command consume that receipt rather than prose.

## F3 — fatal: Task 0 Step 3 still requires zero unpublished commits at P

Step 3 unconditionally requires `git rev-list --count origin/main..HEAD` to equal 0. At retained P the command succeeds but reports `n=1`, so the required-zero predicate returns 1.

Required correction: gate the cut-point expectation by the selected state: exactly 0 for state (i), exactly 1 for state (ii), with the selected expectation and observed value recorded.

## F4 — fatal: state (ii) cannot pass Task 0 Step 3b's post-venv status delta

State (i) creates `$EVID/status-worktree-0.expected`; state (ii) creates only an empty `$EVID/status-worktree-0.txt`. Step 3b unconditionally diffs the absent expected file against `status-post-venv.txt`. From state (ii), the required diff returns 2.

Required correction: create and status-check `status-worktree-0.expected` in both branches, with an empty expected file for state (ii), then retain the single post-venv comparison.

## F5 — fatal: Task 1's state-(ii) alternative is prose beside executable state-(i) Steps 6–7

The Task 1 checkpoint describes alternate state-(ii) Step 6 checks and a no-commit Step 7, but the actual checklist still runs state (i)'s dirty-worktree Step 6 and commit-producing Step 7. No executable condition suppresses those commands at P. The alternative P-binding span also writes `P.tree` without status-capturing the `rev-parse` producer or proving the receipt non-empty.

Required correction: route the actual Step 6 and Step 7 commands through the same exact `resume-state.txt` selector. Under state (i), run the dirty-worktree fence and one P commit. Under state (ii), run only the P commit-diff fence and bind the existing P without commit or amend. Status-capture and gate every identity/tree receipt producer.

## Required rev9 validation

After correcting F1–F5, execute the complete affected flow from the revised artifact bytes at the actual clean P worktree in both bash and zsh: Task 0 Step 2 through Step 3b, followed by Task 1's checkpoint and actual Step 6 / Step 7 route. Isolated execution of only the newly inserted spans is insufficient because each defect is an interaction with retained surrounding commands. Prove the selected state is `ii`, HEAD remains P, the worktree remains clean, the cut-point is 1, both status comparisons are equal, no second commit or amend occurs, and all identity/tree receipts are non-empty and exact.

No correction is requested to `skipset.py`, the membership semantics, C/H fences, owner terms, evidence target, two-commit vehicle, downstream reviews, merge gate, landing rule, or release hold.

## Independent evidence

- Incoming relay sha256: `a802d0a267c2041ef26a20ff55381a96f699fadf33b3df7d63c6fcb316211588`; exact-file lint passes with freshness disabled.
- Locked plan sha256: `8e45acd3a2609f5c44dc507e621ea88bd8a399f55c66c25388d7079944149e72`, equal in the review checkout and at commit `09aa89530759101267250ec04232265ef473dfb0`.
- Rev7 predecessor reproduced at commit `07708bb7034e2c8748944ed79863150e75ad89fc` with sha256 `3d09542c3bc9bbb66dede9910eeb52cdd8bb817f08a6bd334cd1bbefc3163aee`.
- Mechanical rev7-to-rev8 delta: 36 insertions, 8 deletions, one plan artifact. The prior eleven Python helper blocks are byte-identical; `skipset.py` is the sole added helper.
- Measured artifact counts: 45 checklist steps, 12 Python blocks, 3 text blocks, zero bare `DISPATCH IMPL` lines, zero spaced-pipe backtick hazards.
- Retained candidate: clean `intg/r450-discover-parity` at P `54954281b30cae113f399055fff106963a37a443`.
- Both shell probes used external scratch only: `/private/tmp/r450-rev8-review.zinfDz` and `/private/tmp/r450-rev8-review.Dp1Cqw`. In each, state-(ii)-only rc 0; unconditional B gate rc 1; cut-point command rc 0 with `n=1` and required-zero gate rc 1; `resume-state.txt` existence test rc 1; state-(ii) expected-status existence test rc 1; post-venv diff rc 2.

BOUNDARY_CONTRACT:
- Writes: none under this PLAN-REVIEW beyond the daemon-filed review relay and append-only INDEX projection
- Reads: exact rev8 carrier, locked plan at commit `09aa8953`, rev7 predecessor, retained P worktree, token-7 STOP evidence, and governing design/master relays
- Target entity: the plan's skip-set comparator and retained-P resume control flow
- Downstream consumer: the separately addressed implementation runner, count gate, C/H construction, owner reviews, and merge packet
- Contract: one selected resume state; complete state-specific Task 0/1 route; P reused without second commit; any mismatch STOPs UP
- Proof: real/mutant skip-set statuses plus full-flow state-(ii) interaction probes in bash and zsh
- No-consumer action: reject and revise the plan; no implementation, reset, checkout, amend, commit, push, PR, merge, landing push, publication, deployment, release, or closure

Read-only PLAN-REVIEW. No R-4.50 product, test, workflow, harness, plan, design, governed worktree, branch, commit, tag, push, PR, merge, publication, deployment, release, or closure action occurred. Review probes wrote external temporary evidence only. The outgoing daemon-filed PLAN-REVIEW and append-only INDEX projection are the sole own-seat repository writes.

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: no
- migration/backfill/destructive-write/canonical-data-repair: no
- money/inventory/orders/planning/accounting/trust-critical-state: yes — resume receipts and commit identity are trust-critical execution state
- AI-or-automation-acts-downstream: yes — a later separately authorized runner consumes these commands
- worker/scheduler/queue/retry/async-side-effect: yes — later local and container test execution remains gated
- cross-repo/service-contract/generated-schema/shared-API-event: yes — pdc design and m-2/m-3 owner surfaces govern the later act
- user-visible-control-with-materializer/downstream-consumer: no
- test-runtime-role-mismatch: yes — the resume selector determines whether a commit-producing step may execute
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: no — the required correction is confined to executable resume control flow
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: none
- scan_presented_to_operator: no — no downgrade, residual-risk acceptance, or scope expansion is requested
- operator_reply_after_scan: none
- valid_waiver: no
WAIVED_RISK_ACCEPTANCE: none

ACTIONS_GIT_REF: read-only exact-hash review at main `806c09cab7452bab72d3a09be71183944bea3cf5`; retained R-4.50 worktree read-only and clean at `intg/r450-discover-parity@54954281b30cae113f399055fff106963a37a443`; external scratch evidence only. No product/test/workflow/harness/plan/design edit, governed worktree or branch mutation, commit, tag, push, PR, merge, publication, deployment, release, or closure. This daemon-filed PLAN-REVIEW and its INDEX append are the sole own-seat repository writes.
RELAY_LINT: incoming carrier and outgoing draft/render require daemon-matched v2.9.2 exact-file lint; incoming historical freshness is evaluated with `--no-freshness`; outgoing admission/render must be fresh, draft/render byte-equal, uniquely indexed, and engine-verified. Full-root inherited noise is not represented as exact-file truth.
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
Literal status captured before daemon submission. Every listed path except this ignored draft is inherited. After daemon render, `.relays/intg/INDEX.md` and the rendered PLAN-REVIEW are the expected additional own-seat paths.

Done: exact-hash revision-8 PLAN-REVIEW must-revise; the skip-set repair independently reproduced correct in both shells; five blocking resume interactions independently reproduced at the actual P state.
Not done: no implementation token, R-4.50 continuation, product/test/workflow/harness edit, governed worktree or branch mutation, P/C/H commit, tag, owner candidate review, push, PR, merge, landing push, publication, deployment, release, or closure.
Next requested action: intg.pair-planner — issue rev9 correcting F1–F5 and validate the complete affected state-(ii) flow from its written bytes; do not mint implementation from rev8.
