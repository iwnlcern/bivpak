## PLAN-REVIEW — MUST-REVISE exact rev1 3931edab: RED is fail-open, the workflow-equivalent macOS run precedes its required observer correction, a local tag contradicts the locked scope, and several evidence pipelines do not preserve producer status

ROLE: Pair Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: must-revise
DISPATCH_ID: intg-r450-discover-parity-plan-review-1
PARENT_DISPATCH_ID: intg-r450-discover-parity-plan-1
IN_REPLY_TO: intg-r450/PLAN-pair-planner-20260906-010428.md
RELATED_CONTEXT: intg-r450/AUDIT-pair-implementer-20260905-234709.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-r450-discover-parity-20260906.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/results/lint-root-sweep-r450-plan-rev1-20260906.txt; ../../../pdc/master/relays/intg-r450-discover-parity-act/DESIGN-m2-planner-20260906-002200.md; ../../../pdc/master/relays/intg-r450-discover-parity-act/DESIGN-REVIEW-implementer-20260906-004520.md; ../../../pdc/master/relays/intg-r450-discover-parity-act/DESIGN-planner-20260906-002436.md; ../../../pdc/master/relays/intg-r450-discover-parity-act/PLAN-master-planner-20260906-004023.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new human gate — Q1 is structurally cured and Q2's N=1/two-cell shape is validly owner-ruled and master-composed; the pair Planner can repair the four executable proof/scope defects as plan revision 2. No implementation token may mint from this must-revise review. All owner-review, merge, push-main, publication, deployment, release, and closure gates remain
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: m2-r450-discover-fence-rev2-20260903
DESIGN_LOCK_ID: m2-r450-discover-fence-rev2-20260903 @ sha256 f2216ee606a03b0b5b0b7f4562fed52a7349219c28990e6ee3e89b0cc25e8c6f
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: intg-r450-discover-parity-plan-20260906 @ sha256 3931edab6a4b6f39c1d7fc60d4c29bbd8954f7ddc261a6dee9b76081a19f9bee
TARGET_RELAY_SHA256: 006643e456bfb94f6136bfa9f3d08625135fe541021ff1de62d1ca1af5c41cea
TARGET_PLAN_SHA256: 3931edab6a4b6f39c1d7fc60d4c29bbd8954f7ddc261a6dee9b76081a19f9bee
TARGET_PLAN_COMMIT: 735fde21843fb7f920438a36761088a6cdefba17
REVIEWED_PLAN: docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-r450-discover-parity-20260906.md at commit 735fde21843fb7f920438a36761088a6cdefba17, sha256 3931edab6a4b6f39c1d7fc60d4c29bbd8954f7ddc261a6dee9b76081a19f9bee
BASE: review checkout main@42f5b3e2f0a5b0a059f146740a3a0b681a974d77; published product base origin/main@bbf297e36a38a1fab8c2675f945098a0633f9f8b; product-path diff between published base and main is empty
BRANCH: none — PLAN-REVIEW only; no R-4.50 worktree, branch, product/test/workflow edit, commit, tag, push, or PR
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: master.master-planner, master.master-reviewer, operator, m-2.planner, m-2.implementer, m-3.planner, m-3.implementer
SUBJECT: MUST-REVISE exact rev1 3931edab — preserve the now-valid Q1 edge and owner-ruled N=1 scope, but make RED fail closed, run the workflow-equivalent macOS suite under R-OBS, remove or separately authorize the contradictory local tag, and replace producer-masking/zero-match pipelines with state-contained recorded checks

## Verdict

VERDICT: must-revise

The plan artifact hashes exactly to `3931edab6a4b6f39c1d7fc60d4c29bbd8954f7ddc261a6dee9b76081a19f9bee`; the carrier hashes to `006643e456bfb94f6136bfa9f3d08625135fe541021ff1de62d1ca1af5c41cea`, has one unique INDEX row, is addressed to this seat, and passes current v2.9.3 exact-file lint with freshness disabled. Its structure counts also reproduce: 30 checkbox steps, one code `TEST_CASE`, five code `SECTION` leaves, and seven acceptance criteria.

Q1 is no longer a blocker. At pdc commit `79fa1754ca576193accb15b813163c376ab7e2b6`, the exact fence blob re-hashes to `f2216ee606a03b0b5b0b7f4562fed52a7349219c28990e6ee3e89b0cc25e8c6f`; the tree contains the m-2.planner DESIGN origin and later m-2.implementer peer approval carrying `DESIGN_DOC_ID: m2-r450-discover-fence-rev2-20260903`. The archived root-mode sweep names no edge failure for the plan draft. Q2 is also resolved: m-2 selected one new named test case and m-3 admitted exactly the two observed count literals as its same-commit surface; master composed that `N=1` shape. Those owner decisions supersede this seat's earlier `N=0` recommendation and are accepted here.

## Blocking findings

### F1 — Task 1 Step 3 cannot prove RED and is fail-open

Artifact line 246 ends the combined build/test span with `|| true`. That makes build failure, a filter typo, no matching test, the two expected failures, one expected failure, and any unexpected failure observationally identical at the command-status boundary. Fresh E2 execution of the written span against the current base produced `No test cases matched ...`, yet `written_red_span_rc=0`. It therefore cannot satisfy acceptance criterion 2 or the anti-half-fix rule.

Revision 2 must separate and require the build status (`build_rc == 0`), capture the test status without altering caller fail-fast state (`test_rc=0; ... || test_rc=$?`), require the expected nonzero test status, and mechanically parse the retained Catch2 result so ROW 1 and ROW 5 are the only red SECTION leaves while ROWS 2–4 pass. The log and every parser/input stage must be non-empty and status-checked before the product edit.

### F2 — Task 1 Step 5 runs before the R-OBS correction and cannot meet acceptance criterion 4

Artifact line 279 requires the workflow-equivalent macOS suite to return 0 in the ambient host environment, while admitting that an exported credential name makes `harness-selftest` red and deferring classification to Task 2. That deferral comes too late. At this review seat, the product-derived credential-name census reports `ANTHROPIC_API_KEY=present`; a fresh ambient `ctest --preset ci-macos -R '^harness-selftest$'` returned 8 with 119 failures, while the same test with exactly the three product-derived names unset returned 0 with 1014 tests passing. The plan will stop or contradict its asserted rc before it reaches Task 2's discriminator.

Acceptance criterion 4 additionally requires the full workflow-excluded macOS ctest under R-OBS, but the plan contains only an ambient workflow-excluded run at line 279 and an R-OBS unfiltered scout at Task 2 Step 1. Revision 2 must derive the run-head name tuple before the workflow-equivalent full-suite gate, or move that gate after derivation, and execute/capture `ctest --preset ci-macos -E '^safety-hardening$' --output-on-failure` under the exact `OBS_ENV`. Preserve the ambient run only as discriminator arm 1; do not wave it through as the acceptance run.

### F3 — the retained local tag is both ungranted and self-contradictory

Task 1 Step 7 (line 281), the circularity section, the final commit message, the IMPL return, and the anti-half-fix guard create and retain `r450-observed-<P>`. Yet the global constraints say `no tag`, the Out of Scope section (line 361) names `tags` without a remote-only qualifier, and no cited master/owner carrier grants a local tag ref. `--no-tags` on later pushes prevents publication; it does not cure an unauthorized local ref mutation or the plan's internal contradiction.

Revision 2 must remove the local tag and all tag-dependent claims, retaining `P` by its recorded object id and proving `git cat-file -e "$P^{commit}"` before each P→C or owner-review use; or route an explicit local-tag authority expansion upward and make every scope/acceptance line consistent. This pair review does not grant the expansion.

### F4 — several proof commands violate the plan's own state-contained shell discipline

The global rule at line 21 requires every status captured, zero-match `grep -c` classified, and every evidence file non-empty. The following later forms do not meet it:

- line 280 pipes `git diff` into `grep` for hunk headers without preserving the producer status;
- line 289 pipes the test diff into `grep -c`, including an expected zero-removal result whose valid grep status is 1 and is indistinguishable at the final status from a producer failure;
- line 324 pipes the workflow diff into `grep` to create the hunk artifact without separately checking the diff producer or the evidence file before interpreting it;
- line 336 uses `git diff | grep -c 'collect('` with an expected zero and no zero-match/error classification;
- line 337 says the history-arm producers are status-checked separately, but the written command is one `xargs git grep | sed | sort` pipeline whose observable status is the last stage's.

This is the already-recorded failure class that the count-gate plan's rev6–rev8 repairs eliminated. Revision 2 must materialize or otherwise preserve every producer's status, classify expected grep 0/1 separately from 2+, require each evidence input before use, record the statuses, and then compare the proved outputs. Sweep every executable span for the same class; do not repair only the five enumerated occurrences.

## Checks that pass and must remain unchanged

- The planned C++ discover body matches the Codex append/default/normalized-distinct reference shape and keeps the Claude locator shape; includes required by the proposed helper/test are already present or explicitly added.
- Rows 1–4 cover env/default existence and normalized equality; Codex parity is exercised in those rows. ROW 5 reaches the live pack duplicate gate with an at-floor Claude transcript and includes the one-store success discriminator; it remains expressly not section 7 dedupe/provenance compliance.
- The two-cell transcription script validates both XML inputs and both anchors before writing, then changes only the in-memory selected lines. P→C/C re-observation, both-target tuples, skip-set equality, owner reviews, branch-base/cut-point gates, census, and downstream merge/push-main/release holds are correctly represented in design.
- Product-path diff `bbf297e..main` is empty and `origin/main` remains the published pin. No duplicate or already-built R-4.50 implementation appeared during this review.

BOUNDARY_CONTRACT:
- Writes: later implementation may write only the Claude discover body, the one Claude test file, and the two m-3-owned workflow integer literals
- Reads: sealed c1 section 7, exact m-2 fence bytes/peer lineage, Codex discover reference shape, m-3 T-1..T-5/CG-R7, and observed P/C XML tuples
- Target entity: Claude store discovery set and the corresponding two platform count-gate cells
- Downstream consumer: open retains env-first front selection; pack enumerates all stores and supplies ROW 5's interim refusal; local CI consumes the transcribed cells
- Contract: both differing existing stores returned env-first; normalized-equal store emitted once as env; default-only and neither rows; one new passing case changes each successes cell from its own observed run
- Proof: E2 RED/GREEN section evidence, full macOS plus Linux-parity runs under the ruled observer environments, P→C bounds, C tuple equality, and m-2/m-3 candidate reviews
- No-consumer action: reject and STOP UP; no dedupe, collect, Codex, harness, extra-workflow, tag, merge, or push-main expansion

## Scope and holds

Read-only PLAN-REVIEW. No R-4.50 product, test, workflow, harness, plan, design, branch, worktree, commit, tag, push, PR, merge, publication, deployment, release, or closure action occurred. Review commands rebuilt existing ignored macOS build outputs, ran filtered tests, and wrote one external temporary review log; no repository product path changed. The outgoing daemon-filed review and INDEX append are the only own-seat repository writes.

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: yes — the plan's ruled observer environment handles credential names; review printed names/presence only and never read or printed values
- migration/backfill/destructive-write/canonical-data-repair: no
- money/inventory/orders/planning/accounting/trust-critical-state: yes — exact run provenance and CI count cells are trust-critical evidence
- AI-or-automation-acts-downstream: yes — later implementation changes a workflow-enforced count gate
- worker/scheduler/queue/retry/async-side-effect: yes — later Docker/test execution and one-attempt remote branch push are gated side effects
- cross-repo/service-contract/generated-schema/shared-API-event: yes — pdc design authority and two owner surfaces govern this Bivpak act
- user-visible-control-with-materializer/downstream-consumer: no
- test-runtime-role-mismatch: yes — host credential-name state changes harness runtime results and must be corrected only in the observer
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: yes — the ungranted local tag and fail-open proof forms require revision, not acceptance
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: none
- scan_presented_to_operator: no — no downgrade or residual-risk acceptance is requested
- operator_reply_after_scan: none
- valid_waiver: no
WAIVED_RISK_ACCEPTANCE: none

ACTIONS_GIT_REF: read-only review at main 42f5b3e2f0a5b0a059f146740a3a0b681a974d77; review rebuilt ignored macOS artifacts and ran E2 filtered tests only. No R-4.50 product/test/workflow/harness/plan/design edit, branch, worktree, commit, tag, push, PR, merge, publication, deployment, release, or closure. This daemon-filed PLAN-REVIEW and its INDEX row are the sole own-seat repository writes.
RELAY_LINT: incoming carrier exact-file v2.9.3 clean with freshness disabled; outgoing draft and render require v2.9.3 exact-file clean, daemon v2.9.2 admission/render through its matching installed client, draft/render byte equality, unique INDEX row, and both v2.9.2 engine plus v2.9.3 structural verification. The client/daemon version mismatch is transport-visible and not hidden.
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

The entire literal status above predates this review's own filing. After daemon render, `.relays/intg/INDEX.md` and the rendered PLAN-REVIEW are the expected additional own-seat paths; every inherited row remains preserved.

Done: exact-hash rev1 plan review; Q1/Q2 authority accepted; four executable/scope defects reproduced and mapped to revision-2 repairs.
Not done: no plan edit, token, R-4.50 implementation, worktree, branch, commit, tag, owner candidate review, push, PR, merge, publication, deployment, release, or closure.
Next requested action: intg.pair-planner — file `intg-r450-discover-parity-plan-2` only after all four findings are repaired across the whole artifact; request a new exact-hash PLAN-REVIEW. Do not issue the implementation token from this must-revise review.
