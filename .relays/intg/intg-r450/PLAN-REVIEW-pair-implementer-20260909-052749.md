## PLAN-REVIEW — MUST-REVISE exact rev10 1a07c564: the pathspec closes the token-9 concurrency race, but the exact artifact overclaims its proof and contradicts its archived validation census

ROLE: Pair Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: must-revise
DISPATCH_ID: intg-r450-discover-parity-plan-review-10
PARENT_DISPATCH_ID: intg-r450-discover-parity-plan-10
IN_REPLY_TO: intg-r450/PLAN-pair-planner-20260909-051237.md
RELATED_CONTEXT: intg-r450/SITREP-pair-implementer-20260909-042759.md; intg-r450/IMPL-pair-planner-20260909-031538.md; intg-r450/PLAN-REVIEW-pair-implementer-20260909-014848.md; intg-r450/PLAN-pair-planner-20260909-013355.md; ../../../pdc/master/relays/intg-r450-discover-parity-act/PLAN-master-planner-20260908-140952.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-r450-discover-parity-20260906.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/results/rehearsal-r450-rev10-main-status-pathspec-20260909.txt
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new human gate — this is a plan-owned exact-claim correction; it grants no implementation. The m-2 fenced review of C, m-3 reviews of C and H, merge bar, operator condition-4 token, landing-push rule, and absolute release hold remain
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
PLAN_LOCK_ID: intg-r450-discover-parity-plan-20260906 @ sha256 1a07c5648201bd0e1fb013fa22b684b7c511a0311ee5313dd05a697e3980c802
TARGET_RELAY_SHA256: 289bdd7b9ae5409e71e233eab615db67caf6146fe3259b6f4c3359bee6b46b8a
TARGET_PLAN_SHA256: 1a07c5648201bd0e1fb013fa22b684b7c511a0311ee5313dd05a697e3980c802
TARGET_PLAN_COMMIT: dac93e80f90948c7ea3117c2ef51d2a70cfff285
REVIEWED_PLAN: docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-r450-discover-parity-20260906.md at commit dac93e80f90948c7ea3117c2ef51d2a70cfff285, sha256 1a07c5648201bd0e1fb013fa22b684b7c511a0311ee5313dd05a697e3980c802
BASE: review checkout main@913ff8871fd913cd4f2bc8d7005bee4c8b0d9fa6; published product base B=bbf297e36a38a1fab8c2675f945098a0633f9f8b
BRANCH: retained intg/r450-discover-parity worktree verified read-only, clean, at P=54954281b30cae113f399055fff106963a37a443; no C or H authored in this review
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: master.master-planner, master.master-reviewer, operator, m-2.planner, m-2.implementer, m-3.planner, m-3.implementer
SUBJECT: MUST-REVISE exact rev10 1a07c564 — executable pathspec repair works for Git-visible state, but the exact plan says any outside-path write fires although ignored writes do not, and its residual/mutation counts contradict the archived run

## Verdict

VERDICT: must-revise

The token-9 STOP is correctly folded at the executable seam. Task 0 Step 0 and Task 2 Step 4 use the same `-- . ':(exclude).relays' ':(exclude)docs/sprints'` pathspec, and Task 4 Step 3 plus Task 5 Step 5 inherit the Task 2 form by explicit reference. Fresh bash and zsh probes in disposable shared clones reproduced the intended result: new state under `.relays/` and `docs/sprints/` left the comparison equal, while an untracked `harness/` path made it differ. The governed candidate remained exact P and clean.

The exact artifact nevertheless cannot be approved because the revised prose makes a stronger claim than the instrument proves and does not agree with its own archived validation record. This is a plan-record correction, not a request to change the working pathspec or any product, fence, owner, vehicle, merge, landing, or release term.

## F1 — blocking exact-claim mismatch: Git status does not prove that every outside-path write fires

Revision 10 and the Global constraints say that "a write at ANY other path in the main checkout still fires." The written command is `git status --porcelain` without `--ignored`; it detects a changed Git-visible status set, not every filesystem write. In a fresh shared clone, `build/rev10-review-probe` was confirmed ignored by `.gitignore:1`; creating it outside both excluded pathspecs left the before and after receipts byte-equal (`cmp` rc 0, both zero bytes). A write that restores the original bytes is likewise not an observable final status change.

Required correction: either narrow every revised claim and the review question to the property actually measured — unchanged Git-visible tracked/untracked status outside `.relays/` and `docs/sprints/` — or materially strengthen the instrument if literal every-path/no-write detection is intended. The first option matches the artifact's existing rule that ignored environment paths are not repository bytes and needs no executable change or re-run. Do not retain the unqualified "any path" / "every write" assertion beside this Git-status oracle.

## F2 — blocking record contradiction: the artifact's counts do not match the cited run

The Revision 10 paragraph says the real-checkout residual is "two inherited untracked files." The archived written-span run at sha256 `8541211edc7f90187a4a4edace9ade75b90005c478f522c3aac31bca30f96bee` records `A ok lines=1` and names only `?? relay-draft-intg-task4-stop.md` in both bash and zsh; the incoming carrier also correctly reports one residual line. A dynamic checkout count should be bound to the archived observation rather than stated as an unqualified current fact.

The rev10 history row says the scratch validation used "the four mutations," but the same log records five mutation states after clean: ROADMAP modified, relay untracked, sibling-sprint doc untracked, product modified, and product untracked. That is three excluded mutations plus two detecting product mutations, not four.

Required correction: bind the residual sentence to the one-line archived snapshot, and change the history census to five mutation states (or describe the three excluded and two detected cases without an aggregate count). Preserve the six total outcomes: clean plus five mutations.

## Exact-byte and mechanical evidence

- Incoming carrier sha256: `289bdd7b9ae5409e71e233eab615db67caf6146fe3259b6f4c3359bee6b46b8a`; exact-file lint passes with freshness disabled; one unique INDEX row; daemon verification reports `ok: true`.
- Locked artifact sha256: `1a07c5648201bd0e1fb013fa22b684b7c511a0311ee5313dd05a697e3980c802`, equal in the live path and at commit `dac93e80f90948c7ea3117c2ef51d2a70cfff285`.
- Rev9-to-rev10 delta: one plan artifact, 7 insertions and 6 deletions, confined to six hunks at current lines 1, 5, 29, 79, 777, and 875–876. The executable changes are only the Task 0 and Task 2 main-checkout status commands; the rest is revision prose/history. All other approved rev9 bytes remain unchanged.
- Measured artifact census agrees with the carrier: 45 checklist steps, 12 Python blocks, 3 text blocks, exact pathspec 4 occurrences, `status --porcelain` 15 occurrences on 12 lines, and zero bare implementation-dispatch lines.
- Fresh functional probes: bash and zsh each returned `excluded_equal=yes product_untracked_fires=yes`, with a clean zero-line baseline and one `?? harness/rev10-review-probe` line after the detecting mutation. External scratch: `/private/tmp/r450-rev10-review.lauvvO`.
- Fresh counterexample to the unqualified claim: `.gitignore:1:build/` matched `build/rev10-review-probe`; the exact narrowed status command remained zero bytes before and after. External scratch: `/private/tmp/r450-rev10-ignored.QDz2Y5`.
- Current main checkout under the same scoped status has one line, `?? relay-draft-intg-task4-stop.md`. This current observation is supporting context only; the required artifact correction binds its historical claim to the archived run.

## Required rev11 scope

Correct only F1 and F2 in the Revision 10 paragraph, Global constraints sentence, review question/carrier as applicable, and rev10 history row. Keep the two executable pathspec commands byte-identical unless the Planner instead chooses the materially stronger-instrument branch, which would require fresh executable validation. With the wording-only branch, the existing bash/zsh run remains valid; the successor still requires a new exact hash and addressed PLAN-REVIEW before any implementation token.

No correction is requested to the sealed design, product/harness fences, retained P, Task 0 restart, P/C/H sequence, count-gate terms, owner review windows, two-commit vehicle, merge gate, landing rule, or absolute release hold.

BOUNDARY_CONTRACT:
- Writes: none under this PLAN-REVIEW beyond the daemon-filed review relay and append-only INDEX projection
- Reads: exact rev10 carrier and plan bytes, rev9 predecessor, token-9 STOP, archived rev10 rehearsal, retained P, and governing master rule
- Target entity: the plan's main-checkout Git-visible-state safeguard and its exact evidence narrative
- Downstream consumer: the separately addressed implementation runner, P/C/H observation gates, owner reviews, and merge packet
- Contract: shared relay and sprint-ledger state may move concurrently; all other Git-visible tracked/untracked status must remain equal to the Task 0 snapshot; claims may not exceed the oracle
- Proof: exact artifact diff and census, two-shell pathspec probes, ignored-path counterexample, archived residual and mutation census, and clean retained P
- No-consumer action: reject and revise the exact claims; no implementation, reset, checkout, amend, commit, push, PR, merge, landing push, publication, deployment, release, or closure

Read-only PLAN-REVIEW. No R-4.50 product, test, workflow, harness, plan, design, governed worktree, branch, commit, tag, push, PR, merge, publication, deployment, release, or closure action occurred. Review probes wrote external temporary evidence only. The outgoing daemon-filed PLAN-REVIEW and append-only INDEX projection are the sole own-seat repository writes.

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: no
- migration/backfill/destructive-write/canonical-data-repair: no
- money/inventory/orders/planning/accounting/trust-critical-state: yes — one-shot measurement and STOP provenance are trust-critical execution state
- AI-or-automation-acts-downstream: yes — a later separately authorized runner consumes this safeguard
- worker/scheduler/queue/retry/async-side-effect: yes — later macOS and Linux observations remain one-shot and STOP-gated
- cross-repo/service-contract/generated-schema/shared-API-event: yes — pdc design and m-2/m-3 owner gates remain downstream
- user-visible-control-with-materializer/downstream-consumer: no
- test-runtime-role-mismatch: no
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: no — required revision aligns exact claims to the existing oracle without accepting residual risk or widening scope
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: none
- scan_presented_to_operator: no — no downgrade, residual-risk acceptance, or scope expansion is requested
- operator_reply_after_scan: none
- valid_waiver: no
WAIVED_RISK_ACCEPTANCE: none

ACTIONS_GIT_REF: read-only exact-hash review at main `913ff8871fd913cd4f2bc8d7005bee4c8b0d9fa6`; retained R-4.50 worktree read-only and clean at `intg/r450-discover-parity@54954281b30cae113f399055fff106963a37a443`; external scratch evidence only. No product/test/workflow/harness/plan/design edit, governed worktree or branch mutation, governed commit, tag, push, PR, merge, publication, deployment, release, or closure. This daemon-filed PLAN-REVIEW and its INDEX append are the sole own-seat repository writes.
RELAY_LINT: incoming carrier exact-file and root-context clean under daemon-matched v2.9.2 with freshness disabled; outgoing draft/render require fresh exact-file lint, daemon admission/render, draft/render byte equality, one unique INDEX row, and engine verification. Full-root inherited noise is not represented as exact-file truth.
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
Literal full status captured after review probes and before authoring this draft. Every listed path is inherited. After daemon render, `.relays/intg/INDEX.md` and the rendered PLAN-REVIEW are the expected additional own-seat paths.

Done: exact-hash revision-10 PLAN-REVIEW must-revise; executable pathspec repair reproduced sound for Git-visible status in both shells; two blocking exact-claim/census mismatches independently reproduced.

Not done: no implementation token, R-4.50 continuation, product/test/workflow/harness edit, governed worktree or branch mutation, C/H commit, tag, owner candidate review, push, PR, merge, landing push, publication, deployment, release, or closure.

Next requested action: intg.pair-planner — issue a successor correcting F1/F2 and return its new exact hash for PLAN-REVIEW; do not mint implementation from rev10.
