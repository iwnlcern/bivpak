## PLAN-REVIEW — MUST-REVISE exact rev2 9b889d04: helper scripts are consumed before materialization, F4 still masks producer failures and retains two pipelines, and acceptance promises three unscheduled green witness parses

ROLE: Pair Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: must-revise
DISPATCH_ID: intg-r450-discover-parity-plan-review-2
PARENT_DISPATCH_ID: intg-r450-discover-parity-plan-2
IN_REPLY_TO: intg-r450/PLAN-pair-planner-20260906-154309.md
RELATED_CONTEXT: intg-r450/PLAN-REVIEW-pair-implementer-20260906-065859.md; intg-r450/PLAN-pair-planner-20260906-010428.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-r450-discover-parity-20260906.md; ../../../pdc/master/relays/intg-r450-discover-parity-act/PLAN-master-planner-20260906-004023.md; ../../../pdc/master/relays/intg-r450-discover-parity-act/PLAN-master-planner-20260906-015102.md; ../../../pdc/master/relays/intg-r450-discover-parity-act/DESIGN-REVIEW-master-reviewer-20260906-053521.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new human gate — the locked m-2 fence, owner-ruled N=1/two-cell shape, CG-R7 rev5 B/P/C carrier, and R-4.52 landing rule remain valid; the pair Planner can repair these executable-plan defects as revision 3. No implementation token may mint from this must-revise review. All owner-review, merge, landing-push, publication, deployment, release, and closure gates remain
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: m2-r450-discover-fence-rev2-20260903
DESIGN_LOCK_ID: m2-r450-discover-fence-rev2-20260903 @ sha256 f2216ee606a03b0b5b0b7f4562fed52a7349219c28990e6ee3e89b0cc25e8c6f
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: intg-r450-discover-parity-plan-20260906 @ sha256 9b889d045f46054c59fbe4502ede80e5d450fd4c83aee76fa8d2de7c65bd006f
TARGET_RELAY_SHA256: cae86d900aaa98a7f37c2ebd4bdb33014a78bf40690c615d6afb9d24c8d2a683
TARGET_PLAN_SHA256: 9b889d045f46054c59fbe4502ede80e5d450fd4c83aee76fa8d2de7c65bd006f
TARGET_PLAN_COMMIT: ac3391a274db5c50203e66405867122129a9c224
REVIEWED_PLAN: docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-r450-discover-parity-20260906.md at commit ac3391a274db5c50203e66405867122129a9c224, sha256 9b889d045f46054c59fbe4502ede80e5d450fd4c83aee76fa8d2de7c65bd006f
BASE: review checkout main@94db573c366741ea7e682388e8367efea8d5df10; published product base origin/main@bbf297e36a38a1fab8c2675f945098a0633f9f8b; product-path diff between published base and main is empty
BRANCH: none — PLAN-REVIEW only; no R-4.50 worktree, branch, product/test/workflow edit, commit, tag, push, or PR
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: master.master-planner, master.master-reviewer, operator, m-2.planner, m-2.implementer, m-3.planner, m-3.implementer
SUBJECT: MUST-REVISE exact rev2 9b889d04 — F2/F3 and B/P/C are repaired, but five helpers are invoked before creation, cells.py and gate.py failures remain maskable, wc-to-tr pipelines contradict F4, and three required green witness parses are absent

## Verdict

VERDICT: must-revise

The plan artifact hashes exactly to `9b889d045f46054c59fbe4502ede80e5d450fd4c83aee76fa8d2de7c65bd006f`; the addressed carrier hashes to `cae86d900aaa98a7f37c2ebd4bdb33014a78bf40690c615d6afb9d24c8d2a683`, has one unique INDEX row, and passes both v2.9.2 and v2.9.3 exact-file lint with freshness disabled. Its declared structure reproduces: 31 checkbox steps and six syntactically valid Python blocks.

The accepted authority did not regress. At pdc commit `79fa1754ca576193accb15b813163c376ab7e2b6`, the exact m-2 fence blob re-hashes to `f2216ee606a03b0b5b0b7f4562fed52a7349219c28990e6ee3e89b0cc25e8c6f` and the matching m-2 origin plus peer approval remain present. CG-R7 rev5 re-hashes to `9a0320b60e87819495ae1b11a9c4469455267af0275b9479dbf81376d1940f7d` and the Master Reviewer approved that exact pin. The plan's B/P/C roles, binding order, observed entry trigger, two-cell transcription, same-commit candidate, two-owner reviews, and R-4.52 landing hold agree with those carriers.

## Prior findings disposition

- Prior F1 logic is substantially repaired: build status is required zero, the named RED run uses `-w UnmatchedTestSpec`, its status must be nonzero, and retained XML is parsed for exactly ROW 1 and ROW 5 red. The executable ordering defect below nevertheless prevents that proof from running as written.
- Prior F2 is repaired. The exact product-derived observer tuple has three names on this seat, with one present; a fresh discriminator returned ambient rc 8 and exact-name-unset rc 0, and the full workflow-equivalent macOS command under the same observer environment returned rc 0. The plan schedules that command at P and C and does not treat ambient arm 1 as acceptance.
- Prior F3 is repaired. No local or remote tag operation or tag-dependent retention remains; P is recorded by object id and re-proved with `git cat-file -e` before later use. No R-4.50 branch or tag currently exists locally, and the remote branch probe is empty.
- Prior F4 is not fully repaired. The materialized diff/grep/xargs/sed/sort forms are materially better, but the whole-artifact sweep claim is false for the exact defects below.

## Blocking findings

### F1 — five helpers are invoked before the document creates them

The artifact requires execution in document order, but the first operational use precedes the `Write this block` instruction for five helpers: `cells.py` use at line 70 before creation at line 97; `witness.py` use at line 299 before creation at line 334; `hunks.py` use at line 368 before creation at line 390; `tuples.py` use at line 397 before creation at line 422; and `gate.py` use at line 466 before creation at line 492. Only `transcribe.py` is materialized before its run.

Fresh execution of Task 0 Step 1's ordering in an external temporary directory returned `missing_before_write_rc=2` with zero output bytes. Revision 3 must materialize and validate each helper before its first use, without changing the helper bytes or owner-ruled semantics.

### F2 — F4 still contains maskable producer failures and two prohibited pipelines

Task 0 Step 1 runs `cells.py` without capturing or requiring its exit status; it checks only that `B-cells.txt` is non-empty. A fresh mutant of the real B workflow with one Linux binary removed made the exact helper emit six lines and then exit 3. The plan's non-empty check therefore passes a rejected partial parse, allowing an incomplete baseline into every later B/P/C comparison.

Task 4 Step 2 similarly invokes `gate.py` without an executable status capture/check. A fresh ten-cell input with one altered C observation made the exact helper emit ten lines including one `equal=no`, then exit 5; its output remained non-empty. Prose saying `rc REQUIRED 0` and `[ -s ]` does not implement the artifact's own state-contained command rule.

The whole-artifact assertion that no evidence-producing pipeline remains is also false. Task 3 Step 2 line 459 still computes the workflow-hunk count with `wc -l ... | tr -d ' '`, and Task 6 Step 1 line 503 repeats that pipeline for the push-URL count. Revision 3 must give every helper invocation an explicit captured status and checked output, replace both pipelines with state-contained producer/consumer stages, and re-sweep the exact executable spans rather than counting prose/regex alternations.

### F3 — acceptance criterion 2 promises four green parser proofs but schedules only one

Acceptance criterion 2 requires `witness.py green` at P and C on both targets. The executable plan invokes `witness.py green` only once: the targeted macOS run at P in Task 1 Step 5. Task 2 parses P's macOS and Linux XML only with `tuples.py`; Task 4 repeats tuple extraction at C and never invokes `witness.py` on either C XML. Aggregate tuple equality does not satisfy the plan's stronger per-SECTION parser claim.

Revision 3 must either schedule status-captured, non-empty `witness.py green` proofs against the `biv_tests` XML at P/macOS, P/Linux, C/macOS, and C/Linux, or narrow acceptance criterion 2 to the proof actually required by the locked owners. Do not leave an acceptance claim with no producing step.

## Checks that pass and must remain unchanged

- The proposed C++ discover body keeps the accepted Codex append/default/normalized-distinct reference shape and Claude locator shape. The one named Catch2 case retains five ROW sections, ROW 5's one-store discriminator, and the explicit S-CP-5 hold.
- B is resolved before implementation/observation; P is bound before P observation; C is bound before C observation. P supplies the two literals, P to C is workflow-only, and the local gate requires literal C equal observed P equal observed C.
- The observer environment is limited to the product-derived credential names and lives only in run evidence. Both workflow-equivalent macOS runs are under that environment; Linux retains the ruled container topology and name-free proof.
- No tag, merge, landing push, publication, deployment, release, or closure authority was added. Task 6 ends at the remote branch and open PR after both owner reviews; the landing push remains the merge packet's later step.

BOUNDARY_CONTRACT:
- Writes: later implementation may write only the Claude discover body, the one Claude test file, and the two m-3-owned workflow integer literals
- Reads: sealed c1 section 7, exact m-2 fence bytes and peer lineage, Codex discover reference shape, m-3 T-1 through T-5 and CG-R7 rev5, and observed P/C XML tuples
- Target entity: Claude store discovery set and the corresponding two platform count-gate cells
- Downstream consumer: open retains env-first front selection; pack enumerates all stores and supplies ROW 5's interim refusal; local CI consumes the transcribed cells
- Contract: both differing existing stores returned env-first; normalized-equal store emitted once as env; default-only and neither rows; one new passing case changes each successes cell from its own observed run
- Proof: E2 fail-closed RED, green section evidence matching the acceptance text, full macOS and Linux-parity runs under the ruled observers, B/P/C bounds, C tuple equality, and m-2/m-3 candidate reviews
- No-consumer action: reject and STOP UP; no dedupe, collect, Codex, harness, extra-workflow, tag, merge, or landing-push expansion

## Scope and holds

Read-only PLAN-REVIEW. No R-4.50 product, test, workflow, harness, plan, design, branch, worktree, commit, tag, push, PR, merge, publication, deployment, release, or closure action occurred. Review commands ran existing ignored macOS build outputs and wrote external temporary evidence only; no repository product path changed. The outgoing daemon-filed review and INDEX append are the only own-seat repository writes.

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: yes — the ruled observer handles credential names; review derived names and presence only and never read or printed values
- migration/backfill/destructive-write/canonical-data-repair: no
- money/inventory/orders/planning/accounting/trust-critical-state: yes — exact run provenance and CI count cells are trust-critical evidence
- AI-or-automation-acts-downstream: yes — later implementation changes a workflow-enforced count gate
- worker/scheduler/queue/retry/async-side-effect: yes — later Docker/test execution and one-attempt remote branch push are gated side effects
- cross-repo/service-contract/generated-schema/shared-API-event: yes — pdc design authority and two owner surfaces govern this Bivpak act
- user-visible-control-with-materializer/downstream-consumer: no
- test-runtime-role-mismatch: yes — host credential-name state changes harness runtime results and is corrected only in the observer
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: yes — accepting unexecutable or maskable evidence steps would accept residual proof risk; revision is required instead
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: none
- scan_presented_to_operator: no — no downgrade or residual-risk acceptance is requested
- operator_reply_after_scan: none
- valid_waiver: no
WAIVED_RISK_ACCEPTANCE: none

ACTIONS_GIT_REF: read-only review at main 94db573c366741ea7e682388e8367efea8d5df10; review ran existing ignored macOS test artifacts and external scratch probes only. No R-4.50 product/test/workflow/harness/plan/design edit, branch, worktree, commit, tag, push, PR, merge, publication, deployment, release, or closure. This daemon-filed PLAN-REVIEW and its INDEX row are the sole own-seat repository writes.
RELAY_LINT: incoming carrier exact-file clean under both v2.9.2 and v2.9.3 with freshness disabled; outgoing draft and render require both exact-file linters clean, daemon v2.9.2 admission/render through its matching installed client, draft/render byte equality, unique INDEX row, and engine verification. Full-root lint carries inherited historical noise and is not represented as exact-file truth.
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

The literal status above was captured after all review probes and before this relay's own filing. Every listed path is inherited S4/root state. After daemon render, `.relays/intg/INDEX.md` and the rendered PLAN-REVIEW are the expected additional own-seat paths.

Done: exact-hash rev2 plan review; authority, F2, F3, and B/P/C preserved; three executable-plan blockers independently reproduced and mapped to revision-3 repairs.
Not done: no plan edit, token, R-4.50 implementation, worktree, branch, commit, tag, owner candidate review, push, PR, merge, landing push, publication, deployment, release, or closure.
Next requested action: intg.pair-planner — issue `intg-r450-discover-parity-plan-3` only after helpers precede use, every helper and evidence producer is status-proved without pipelines, and green witness acceptance matches its producing steps; then request a new exact-hash PLAN-REVIEW. Do not issue the implementation token from this must-revise review.
