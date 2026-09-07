## PLAN-REVIEW — MUST-REVISE exact rev4 6ebbfa42: the happy path repairs the Python 3.14 stop, but cleanup/version producers remain fail-open, freshness is unproved, and the new ignore-proof ordering is false

ROLE: Pair Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: must-revise
DISPATCH_ID: intg-r450-discover-parity-plan-review-4
PARENT_DISPATCH_ID: intg-r450-discover-parity-plan-4
IN_REPLY_TO: intg-r450/PLAN-pair-planner-20260906-181613.md
RELATED_CONTEXT: intg-r450/SITREP-pair-implementer-20260906-175211.md; intg-r450/IMPL-pair-planner-20260906-173252.md; intg-r450/PLAN-REVIEW-pair-implementer-20260906-165625.md; intg-r450/PLAN-pair-planner-20260906-163706.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-r450-discover-parity-20260906.md; ../../../pdc/master/relays/intg-r450-discover-parity-act/PLAN-master-planner-20260906-004023.md; ../../../pdc/master/relays/intg-r450-discover-parity-act/PLAN-master-planner-20260906-015102.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new human gate — the pair Planner can repair these executable-plan defects as revision 5 without changing the locked product surface or owner rulings. No implementation token may mint from this must-revise review. The m-2 fenced review, m-3 hunk review, merge bar, operator condition-4 token, landing rule, and absolute release hold remain
COMMISSION_ID: intg-consent-fabric
COMMISSION_SCOPE: the operator-authorized integration phase (2026-08-26) executed by ONE commissioned pair — sub-step 1 first, the A6 rev14 consent-UX fabric with the engine unwired per the sealed spine; subsequent sub-steps (format act consuming LOCKED M rev8 + LOCKED N; then wiring at product scope) each behind their standing gates incl. m-4's reachability re-review before any wiring; sealed design only; STOPs route UP; no merge/push/publication/release authority
COMMISSION_TO: intg.pair-planner
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: m2-r450-discover-fence-rev2-20260903
DESIGN_LOCK_ID: m2-r450-discover-fence-rev2-20260903 @ sha256 f2216ee606a03b0b5b0b7f4562fed52a7349219c28990e6ee3e89b0cc25e8c6f
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: intg-r450-discover-parity-plan-20260906 @ sha256 6ebbfa421398e2901e01cf9e5343517ffce214ebe7048ee007ff814a4be75d8e
TARGET_RELAY_SHA256: 76630f5a21f11abca212d850ebbd87fee16384881201d368cb2348f16a15cd8e
TARGET_PLAN_SHA256: 6ebbfa421398e2901e01cf9e5343517ffce214ebe7048ee007ff814a4be75d8e
TARGET_PLAN_COMMIT: fdda379a59f783373fa4a0eaefeceecf429d8d8b
REVIEWED_PLAN: docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-r450-discover-parity-20260906.md at commit fdda379a59f783373fa4a0eaefeceecf429d8d8b, sha256 6ebbfa421398e2901e01cf9e5343517ffce214ebe7048ee007ff814a4be75d8e
BASE: review checkout main@5563755c89ad8091009e907ecccce606b1c5fd12; published product base origin/main@bbf297e36a38a1fab8c2675f945098a0633f9f8b; revision-4 product paths remain untouched
BRANCH: retained intg/r450-discover-parity worktree verified read-only at bbf297e36a38a1fab8c2675f945098a0633f9f8b with empty status; no P; no branch action in this review
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: master.master-planner, master.master-reviewer, operator, m-2.planner, m-2.implementer, m-3.planner, m-3.implementer
SUBJECT: MUST-REVISE exact rev4 6ebbfa42 — the venv and fresh configure work on the happy path, but the written bytes do not fail closed on either deletion or the Python-version producer, do not prove the build directory fresh, and contradict their own check-ignore-before-status rule

## Verdict

VERDICT: must-revise

The artifact hashes exactly to `6ebbfa421398e2901e01cf9e5343517ffce214ebe7048ee007ff814a4be75d8e`; the addressed carrier hashes to `76630f5a21f11abca212d850ebbd87fee16384881201d368cb2348f16a15cd8e`, has one unique INDEX row, and passes v2.9.3 exact-file lint with freshness disabled. The daemon-matched v2.9.2 root verification returned `ok:true`. Commit `fdda379a59f783373fa4a0eaefeceecf429d8d8b` contains those exact plan bytes.

The revision is narrow: the rev3-to-rev4 artifact diff is 11 insertions and 8 deletions, limited to the stop explanation, ignored-environment permission, Task 0 Steps 2/3b/4/5, and revision history. The six helpers, product/test body, B/P/C shape, owner reviews, PR vehicle, merge bar, landing rule, and release hold are unchanged from approved revision 3.

The intended repair works on the happy path. In a disposable external clone at B, the written trailing-slash ignore query, Python 3.12 venv creation, locked install, availability probe, clean-status gate, fresh configure, cache grep, build, existing discovery case, and final status all returned zero; the cache match count was exactly one, `missing: []`, and Python was 3.12.12. The retained governed worktree independently matches the resume checkpoint: correct branch, HEAD B, empty status, absent venv, ignored `.venv-harness/` and `build/ci-macos/`, and its consumed-run cache names Homebrew Python 3.14.6.

## Blocking findings

### F1 — the new cleanup/version sequence violates the plan's own fail-closed shell discipline

At artifact line 249, `rm -rf .venv-harness` has no captured status or postcondition, and `.venv-harness/bin/python --version > "$EVID/venv-python.txt"` likewise has no captured status and does not require a non-empty evidence file. This directly contradicts the carrier's F2 claim at line 44 that the sequence through version has each status captured, as well as the artifact's global rule that every producer status is captured and recorded.

At artifact line 250, `rm -rf build/ci-macos` also has no captured status and no `[ ! -e build/ci-macos ]` postcondition. If deletion fails or is partial, the shell continues into configure. A surviving cache that already names `.venv-harness/bin/python3` satisfies the subsequent grep even though the directory was not fresh, so the new cache gate does not close the freshness claim by itself.

Revision 5 must status-capture and require zero for both deletions, prove each target absent before recreation/configure, and status-capture plus non-empty-check the Python-version receipt. The repair must remain limited to the ignored, untracked worktree environment paths.

### F2 — the newly stated check-ignore-before-status invariant is not implemented

Artifact line 19 says the trailing-slash `git check-ignore` query proves each of `.venv-harness/` and `build/` before any worktree status gate reads the worktree. The first worktree status gate is at line 247. The only executable ignore query is the `.venv-harness/` query at line 249, after that status gate; there is no executable `git check-ignore` query for `build/` anywhere in the plan.

Revision 5 must place status-captured trailing-slash ignore proofs for both destructive targets before the first worktree status gate that relies on their invisibility, or narrow the global invariant to the ordering actually required and then prove both targets before their destructive use. Do not rely on this review's read-only queries as future implementation evidence.

### F3 — `find_spec` does not prove the three packages import

The revision explanation at artifact line 5 says Step 3b proves `pytest`, `jsonschema`, and `zstandard` import. The executable command at line 249 only calls `importlib.util.find_spec`; it establishes discoverability, not successful import or extension loading. The happy path passed, but the command cannot support its stronger stated claim.

Revision 5 should execute actual imports of all three named packages with captured status, or narrow every carrier/artifact claim to module discoverability. Because the consumed stop was ten collection-time import errors, the actual-import form is the direct proof.

## Checks that pass and must remain unchanged

- The exact digest and commit bind; the relay is addressed for PLAN-REVIEW only and contains no implementation token.
- The create-or-verify resume checkpoint matches the retained worktree without reset, checkout, or re-creation.
- Python 3.12 plus `harness/requirements.lock` repairs the observed missing-dependency cause on the reproduced happy path.
- A fresh configure selects exactly one `.venv-harness/bin/python3` cache entry, the build completes, and the existing Claude discovery case passes.
- All approved revision-3 helper, observer, product/test, B/P/C, two-owner-review, PR-only, merge, landing, and release boundaries remain unchanged.

BOUNDARY_CONTRACT:
- Writes: a later separately authorized implementation may write only the Claude discover body, the one Claude test file, and the two m-3-owned workflow integer literals; ignored worktree venv/build paths are environment only
- Reads: sealed c1 section 7, exact m-2 fence bytes and peer lineage, Codex discover reference shape, m-3 T-1 through T-5 and CG-R7 rev5, and observed P/C XML tuples
- Target entity: Claude store discovery set and the corresponding two platform count-gate cells
- Downstream consumer: open retains env-first front selection; pack enumerates all stores and supplies ROW 5's interim refusal; local CI consumes the transcribed cells
- Contract: both differing existing stores returned env-first; normalized-equal store emitted once as env; default-only and neither rows; one new passing case changes each successes cell from its own observed run
- Proof: E2 fail-closed RED, five green section parses, full macOS and Linux-parity runs under ruled observers, B/P/C bounds, C tuple equality, and m-2/m-3 candidate reviews
- No-consumer action: reject and STOP UP; no dedupe, collect, Codex, harness, extra-workflow, tag, merge, or landing-push expansion

Read-only PLAN-REVIEW. No R-4.50 product, test, workflow, harness, plan, design, worktree, branch, commit, tag, push, PR, merge, publication, deployment, release, or closure action occurred. Review probes wrote only to an external disposable clone/evidence directory. The outgoing daemon-filed PLAN-REVIEW and append-only INDEX projection are the sole own-seat repository writes.

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: yes — later observer execution handles credential names only; this review did not read or print credential values
- migration/backfill/destructive-write/canonical-data-repair: no — the reviewed deletions target only ignored disposable venv/build paths, while their fail-closed proof is still required
- money/inventory/orders/planning/accounting/trust-critical-state: yes — exact run provenance and workflow count cells are trust-critical evidence
- AI-or-automation-acts-downstream: yes — later separately authorized implementation changes a workflow count gate
- worker/scheduler/queue/retry/async-side-effect: yes — later Docker/test and one-attempt remote push steps remain gated
- cross-repo/service-contract/generated-schema/shared-API-event: yes — pdc design and two owner surfaces govern this act
- user-visible-control-with-materializer/downstream-consumer: no
- test-runtime-role-mismatch: yes — host interpreter/dependency and credential-name state change harness outcomes
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: yes — approving fail-open environment preparation would accept residual proof risk; revision is required instead
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: none
- scan_presented_to_operator: no — no downgrade, scope expansion, or residual-risk acceptance is requested
- operator_reply_after_scan: none
- valid_waiver: no
WAIVED_RISK_ACCEPTANCE: none

ACTIONS_GIT_REF: read-only exact-hash review at main 5563755c89ad8091009e907ecccce606b1c5fd12; retained R-4.50 worktree read-only at intg/r450-discover-parity@bbf297e36a38a1fab8c2675f945098a0633f9f8b with empty status; external scratch clone/evidence only. No product/test/workflow/harness/plan/design edit, worktree or branch mutation, commit, tag, push, PR, merge, publication, deployment, release, or closure. This daemon-filed PLAN-REVIEW and its INDEX projection are the sole own-seat repository writes.
RELAY_LINT: incoming carrier exact-file clean under v2.9.3 with freshness disabled; daemon-matched v2.9.2 root verification ok. Outgoing draft/render require both exact-file linters clean, daemon v2.9.2 admission/render through its matching installed client, draft/render byte equality, one unique INDEX row, and engine verification. Full-root historical noise is not represented as exact-file truth.
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

The literal status above was captured after all review probes and before this relay draft. Every listed path is inherited S4/root state. After daemon render, `.relays/intg/INDEX.md` and the rendered PLAN-REVIEW are the expected additional own-seat paths.

Done: exact-hash revision-4 PLAN-REVIEW; happy-path repair reproduced; retained worktree checkpoint verified; three executable-plan defects mapped to revision-5 repairs.
Not done: no implementation token, R-4.50 implementation, product/test/workflow edit, governed worktree or branch mutation, commit, tag, owner candidate review, push, PR, merge, landing push, publication, deployment, release, or closure.
Next requested action: intg.pair-planner — issue `intg-r450-discover-parity-plan-5` only after both destructive cleanups and the version/import proofs are status-gated, build freshness is proven, and the ignore-proof ordering matches the global invariant; then request a new exact-hash PLAN-REVIEW. Do not issue `intg-r450-discover-parity-impl-2` from this must-revise review.
