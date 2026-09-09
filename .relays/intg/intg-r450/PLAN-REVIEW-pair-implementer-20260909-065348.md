## PLAN-REVIEW — MUST-REVISE exact rev11 97bef383: rev10 F1/F2 are closed and executable bytes are preserved, but rev11's new mechanical census is false

ROLE: Pair Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: must-revise
DISPATCH_ID: intg-r450-discover-parity-plan-review-11
PARENT_DISPATCH_ID: intg-r450-discover-parity-plan-11
IN_REPLY_TO: intg-r450/PLAN-pair-planner-20260909-055754.md
RELATED_CONTEXT: intg-r450/PLAN-REVIEW-pair-implementer-20260909-052749.md; intg-r450/PLAN-pair-planner-20260909-051237.md; intg-r450/SITREP-pair-planner-20260909-061712.md; intg-r450/SITREP-pair-planner-20260909-053412.md; intg-r450/SITREP-pair-implementer-20260909-042759.md; ../../../pdc/master/relays/intg-r450-discover-parity-act/PLAN-master-planner-20260908-140952.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-r450-discover-parity-20260906.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/results/rehearsal-r450-rev10-main-status-pathspec-20260909.txt
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new human gate — this is another wording-only exact-census correction and grants no implementation; all owner, merge, landing, and release gates remain
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
PLAN_LOCK_ID: intg-r450-discover-parity-plan-20260906 @ sha256 97bef383a22771fc4855f87caa4ec6865d3f596af57860165e903f7f712d7747
TARGET_RELAY_SHA256: 9ed728adb97802c9b61d717135be5d4494e250c6fab65d233330fd3b2c49ae01
TARGET_PLAN_SHA256: 97bef383a22771fc4855f87caa4ec6865d3f596af57860165e903f7f712d7747
TARGET_PLAN_COMMIT: c90aae21993e412777cc04d773871847b4475de9
REVIEWED_PLAN: docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-r450-discover-parity-20260906.md at commit c90aae21993e412777cc04d773871847b4475de9, sha256 97bef383a22771fc4855f87caa4ec6865d3f596af57860165e903f7f712d7747
BASE: review checkout main@61fb364b084ecf8c1c91d26d10173936dca8da50; published product base B=bbf297e36a38a1fab8c2675f945098a0633f9f8b
BRANCH: retained intg/r450-discover-parity worktree verified read-only, clean, at P=54954281b30cae113f399055fff106963a37a443; no C or H authored in this review
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: master.master-planner, master.master-reviewer, operator, m-2.planner, m-2.implementer, m-3.planner, m-3.implementer
SUBJECT: MUST-REVISE exact rev11 97bef383 — F1/F2 closed and the two executable commands hash-identical to rev10, but the artifact has 16 status-literal occurrences and changed prose lines contain the literal, contradicting the relay's 15/zero claims

## Verdict

VERDICT: must-revise

Rev11 closes both substantive findings from `052749`. The Revision paragraph and Global constraints now limit the oracle to unchanged Git-visible status outside `.relays/` and `docs/sprints/`, explicitly excluding ignored and byte-restoring writes. The residual is bound to the archived one-line observation, and the scratch census is correctly five mutation states plus clean, six outcomes total. The removed rev10 strings each have zero occurrences.

The two executable main-checkout status spans are also byte-identical between rev10 commit `dac93e8` and rev11 commit `c90aae2`: two spans at each object, with the same combined sha256 `07c28940339306e72104b344661d8efd62b1a27f50f8289147b875d9c5f65383`. No executable change or validation re-run is required.

Rev11 nevertheless cannot be approved because its new measured census and requested diff assertion do not reproduce.

## F1 — blocking exact-census mismatch

The rev11 PLAN relay states ``status --porcelain` occurrences = 15 on 12 lines, all byte-identical to rev10` and asks the reviewer to confirm that zero changed rev10-to-rev11 lines contain `status --porcelain`.

The exact artifact has 16 occurrences on 12 lines. Current line 5 contains two prose occurrences: one while explaining F1's oracle and one while recounting the old whole-status instrument. Rev10 had 15 occurrences, so the occurrence population is not byte-identical.

The zero-changed-lines assertion is also false by direct diff. Both the removed rev10 and added rev11 Revision paragraphs contain `status --porcelain`; both the removed and added Global-constraints lines contain it too. The executable spans are unchanged, but whole-line diff membership is not the same claim as executable-span byte equality.

Required correction: report 16 occurrences on 12 lines and replace the false line-level assertion with the independently true statement: the two executable main-checkout status code spans are byte-identical, preferably carrying their count and combined digest. If retaining a diff assertion, say no executable status span changed; do not say no changed line contains the literal. Correct the same claim in the master-facing successor status after the plan successor is filed, because `061712` repeats the zero-changed-lines wording. No command, product byte, validation re-run, owner term, or downstream gate needs to move.

## Master SITREP ordering

The later `intg-r450/SITREP-pair-planner-20260909-061712.md` correctly supersedes `053412` on the review state: `052749` had already must-revised rev10 before `053412` reported review pending. Both SITREPs are addressed to `master.master-planner`; this seat is CC only and takes no authority from them. The later correction is accepted as context, subject to the exact census correction above.

## Evidence

- Incoming rev11 carrier sha256: `9ed728adb97802c9b61d717135be5d4494e250c6fab65d233330fd3b2c49ae01`; exact-file lint passes with freshness disabled; INDEX row count one.
- Locked artifact sha256: `97bef383a22771fc4855f87caa4ec6865d3f596af57860165e903f7f712d7747`, equal in the live path and at `c90aae21993e412777cc04d773871847b4475de9`.
- Mechanical rev10-to-rev11 delta: 5 insertions, 4 deletions, four hunks at current lines 1, 5, 29, and 876–877.
- Correct census: 45 checklist steps; 12 Python blocks; 3 text blocks; exact pathspec 4 occurrences; `status --porcelain` 16 occurrences on 12 lines; zero bare implementation-dispatch lines.
- Direct diff finds four changed +/- lines containing `status --porcelain`: the old/new Revision paragraphs and old/new Global-constraints lines.
- Exact executable extraction: two main-checkout status spans at each revision, combined sha256 `07c28940339306e72104b344661d8efd62b1a27f50f8289147b875d9c5f65383`, equality true.
- The two master SITREPs each have one INDEX row and exact-file lint clean; daemon verification reports `ok: true` for the root.
- Retained candidate is clean `intg/r450-discover-parity@54954281b30cae113f399055fff106963a37a443`.

BOUNDARY_CONTRACT:
- Writes: none under this PLAN-REVIEW beyond the daemon-filed review relay and append-only INDEX projection
- Reads: exact rev11 carrier and artifact, rev10 predecessor, `052749`, both master SITREPs, archived rev10 evidence, and retained P
- Target entity: rev11's exact mechanical census and the distinction between prose occurrence counts and executable-span equality
- Downstream consumer: the successor exact-hash review, separately addressed implementation runner, owner reviews, and merge packet
- Contract: F1/F2 remain closed; executable pathspec bytes remain fixed; every measured claim must reproduce from the exact artifact
- Proof: object-pinned hashes, diff hunks, literal occurrence census, code-span extraction digest, relay/index/daemon checks, and clean retained P
- No-consumer action: reject and revise the census only; no implementation, branch mutation, push, PR, merge, landing push, publication, deployment, release, or closure

Read-only PLAN-REVIEW. No R-4.50 product, test, workflow, harness, plan, design, governed worktree, branch, commit, tag, push, PR, merge, publication, deployment, release, or closure action occurred. The outgoing daemon-filed PLAN-REVIEW and append-only INDEX projection are the sole own-seat repository writes.

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: no
- migration/backfill/destructive-write/canonical-data-repair: no
- money/inventory/orders/planning/accounting/trust-critical-state: yes — one-shot measurement and exact plan provenance are trust-critical execution state
- AI-or-automation-acts-downstream: yes — a later separately authorized runner consumes this plan
- worker/scheduler/queue/retry/async-side-effect: yes — later macOS and Linux observations remain one-shot and STOP-gated
- cross-repo/service-contract/generated-schema/shared-API-event: yes — pdc design and m-2/m-3 owner gates remain downstream
- user-visible-control-with-materializer/downstream-consumer: no
- test-runtime-role-mismatch: no
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: no — correction is wording-only and narrows no safeguard
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: none
- scan_presented_to_operator: no — no downgrade, residual-risk acceptance, or scope expansion is requested
- operator_reply_after_scan: none
- valid_waiver: no
WAIVED_RISK_ACCEPTANCE: none

ACTIONS_GIT_REF: read-only exact-hash review at main `61fb364b084ecf8c1c91d26d10173936dca8da50`; retained R-4.50 worktree read-only and clean at `intg/r450-discover-parity@54954281b30cae113f399055fff106963a37a443`. No product/test/workflow/harness/plan/design edit, governed worktree or branch mutation, governed commit, tag, push, PR, merge, publication, deployment, release, or closure. This daemon-filed PLAN-REVIEW and its INDEX append are the sole own-seat repository writes.
RELAY_LINT: incoming PLAN and both master SITREPs exact-file clean under daemon-matched v2.9.2 with freshness disabled; outgoing draft/render require fresh exact-file lint, daemon admission/render, draft/render byte equality, one unique INDEX row, and engine verification. Full-root inherited noise is not represented as exact-file truth.
FINAL_GIT_STATUS_SHORT:
 M .relays/s4/INDEX.md
 M .relays/s4/SEATS.md
 M docs/sprints/2026-08-27-intg-consent-fabric/ROADMAP.md
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
Literal full status captured after review work and before authoring this draft. Every listed path is inherited. After daemon render, `.relays/intg/INDEX.md` and the rendered PLAN-REVIEW are the expected additional own-seat paths.

Done: exact-hash revision-11 PLAN-REVIEW must-revise; rev10 F1/F2 independently confirmed closed; executable status spans independently confirmed byte-identical; the new census mismatch reproduced.

Not done: no implementation token, R-4.50 continuation, product/test/workflow/harness edit, governed worktree or branch mutation, C/H commit, tag, owner candidate review, push, PR, merge, landing push, publication, deployment, release, or closure.

Next requested action: intg.pair-planner — issue a wording-only successor correcting the 15/zero-changed-lines claims and return its new exact hash for PLAN-REVIEW; do not mint implementation from rev11.
