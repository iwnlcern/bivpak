## PLAN-REVIEW artifact — APPROVE revision 15 at beba597c: verbose CTest makes the green coverage receipt observable, and the census is again bounded by the exact authorized repair cells

ROLE: Pair Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: approve
DISPATCH_ID: intg-substep2a-plan-review-15
PARENT_DISPATCH_ID: intg-substep2a-plan
IN_REPLY_TO: intg-substep2a/PLAN-pair-planner-20260903-230341.md
RELATED_CONTEXT: intg-substep2a/PLAN-REVIEW-pair-implementer-20260903-225905.md; intg-substep2a/PLAN-pair-planner-20260903-223053.md; intg-substep2a/IMPL-pair-implementer-20260903-222330.md; ../../../pdc/master/relays/intg-substep2a-format-act/DESIGN-planner-20260903-183510.md; ../../../pdc/master/relays/intg-substep2a-format-act/PLAN-master-planner-20260903-183926.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new gate — this approval closes only the exact-hash plan review at beba597c; W-5 remains effective at its frozen selector and eligible row. Implementation remains prohibited until a fresh addressed bare token `intg-substep2a-impl-5` stands; m-1/m-3 byte review, merge, count-gate, push, PR, publication, deployment, and release retain separate gates; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: intg-format-act-plan
DESIGN_LOCK_ID: m1-addendum-O-63c46631-lock-20260901
DESIGN_RECORD_KIND: design-doc
LOCKED_DESIGN_SHA256: 63c46631c84ce27ebedbf71c4965e6b0b149919a83118835d78ce29e89d3e577
LOCKED_DESIGN_COMMIT: 40b4f7a3dbfc60e5ab742678bc4e77198845c243
POST_STAMP_SHA256: 0e990bac752986942d9091871a5175820b829dd019d586e8e895461cfff656d2
SECOND_CONSUMED_LOCK: m1-addendum-N-82293732-lock-20260827
THIRD_CONSUMED_LOCK: m1-addendum-M-2966b839-lock-20260825
PLAN_LOCK_ID: intg-substep2a-plan-20260830 @ sha256 beba597c20d43441f6901f4930e4e4141bd866ecdc27c3f8cec3f403dcb0f265
TARGET_RELAY_SHA256: a8218ef24826b100bee96dd4b70629531d4f346b92d67fa19606fd5dd4242762
TARGET_PLAN_SHA256: beba597c20d43441f6901f4930e4e4141bd866ecdc27c3f8cec3f403dcb0f265
TARGET_PLAN_COMMIT: 77f2253c3531b1748014902aedfeec418cf33105
BASE: main@46df8f3c35981a4ae3f77cf3293a4b7212b4b996; exact review filed from docs lane commit 77f2253c
BRANCH: intg/format-act@b09e1922c16da50b5bef0644d9923a567b98c468 with exactly the two held unstaged manifest-path repairs; index empty; both retention tags present; no product/test byte or ref changed by this review
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: master.master-planner, master.master-reviewer, m-1.planner, m-1.implementer, m-3.planner, m-3.implementer
SUBJECT: APPROVE exact beba597c — revision 15 makes tidy coverage observable through ctest -V, restores byte-level STOP outside the six authorized repair cells, fixes T-5 to the candidate head, and preserves every downstream hold; issue no product instruction except through fresh addressed token intg-substep2a-impl-5

## Verdict

APPROVE exact SHA-256 `beba597c20d43441f6901f4930e4e4141bd866ecdc27c3f8cec3f403dcb0f265`.

Revision 15 folds all three findings from `225905` and is mechanically executable. It preserves the rev14 `dot{}` repair, held ondemand lookup spelling, keep-going build, staged-tree proofs, sealed design boundaries, and ten-path ceiling without authorizing any new byte.

This approval is review-only. It authorizes no product/test/plan edit, tag or ref movement, container execution against changed bytes, reset, staging, commit, byte-review request, merge, count-gate act, push, PR, remote CI, publication, deployment, seal, or release.

## Review findings

### F1 — the tidy coverage receipt is now observable and fail-closed

Step 4b now invokes only the anchored safety-tidy row with verbose CTest, merges stderr into stdout, and tees the evidence log. It explicitly takes CTest's pipeline element status via `${PIPESTATUS[0]}`, not `tee`'s status, and requires `tidy_rc == 0`.

The gate requires exactly one `clang-tidy coverage: <N> results == <N> sources` line, equal populations, N >= 1, and no `COVERAGE FAILURE:`. This matches the harness: `run_clang_tidy.py` prints that line only after deriving a nonempty project-source population and verifying result/source cardinality, then returns nonzero for any tidy failure. Verbose CTest closes the rev14 invisibility defect; `--output-on-failure` is not substituted.

The diagnostic count is one printed integer over concatenated build and tidy logs. Treating the printed zero as the receipt while ignoring grep's expected zero-match status 1 is explicit, so the rev13 arithmetic and shell-status defects cannot recur.

### F2 — keep-going observes broadly but repairs remain exact

The keep-going build may enumerate diagnostics across independent targets, but the plan now denies it repair authority. The only permitted repair cells relative to `retained-task3b-b09e192` are T-1's header initializer, the four T-4 finding sites, and the test-local `dot{}` initializer. Any other byte is a STOP even inside the three named files; a fourth path is merely a subset of that rule.

“Six authorized hunks” is read consistently with the retained Step 0-ter hunk-to-site rule: it names six logical repair cells. The already-held pointer fold has dependent dereference and initializer edits, all mapped to the one `RepoRowFacts::row` finding; it does not create authorization for a new same-file diagnostic. The final proof must retain the complete diff and mapping.

### F3 — replacement and evidence targets are coherent

Task-4 T-5 now runs at the candidate replacement SHA. Step 0-quater still begins from exact held hashes at `b09e192`, adds only `std::string dot{};`, reruns macOS because the test TU changes, then runs the corrected pre-commit Linux census. Step 5 explicitly stages six Task-3 paths and proves the replacement differs from retained `b09e192` only in the three checkpoint paths. Step 6 and Task 4 remain downstream of the green replacement.

## Exact review evidence

- Incoming relay SHA-256: `a8218ef24826b100bee96dd4b70629531d4f346b92d67fa19606fd5dd4242762`; exact-file relay lint is clean.
- Reviewed plan: commit `77f2253c3531b1748014902aedfeec418cf33105`, SHA-256 `beba597c20d43441f6901f4930e4e4141bd866ecdc27c3f8cec3f403dcb0f265`.
- Rev14-to-rev15 delta: one plan file, 8 insertions / 6 deletions; `git diff --check` clean. The delta is confined to F1/F2/F3 and their headline, Step 0-quater, Step 4b, Task-4 T-3/T-5, acceptance 12, and revision identity/authority prose.
- W-5 replacement archive: `lint-root-sweep-2a-rev15-verbose-tidy-20260903.txt`, SHA-256 `2a10cad6e9e12ed2f0841d961a5a8d3295fd64b2dcc5727b2e08c08597636d28`; it records exactly the one W-5-covered O design-lineage red on the citing carrier and zero lineage-walk errors.
- Frozen product state reverified: HEAD `b09e1922c16da50b5bef0644d9923a567b98c468`, parent `363d812fba2610f7e5c71fdb9daee5c7f740027a`, both retention tags correct, index empty, exactly the two held manifest paths modified, source hashes `fd12d52b...` / `f7a89c8c...`.
- CTest documents `-V` as verbose test output; the harness registers `run_clang_tidy.py` directly as `safety-tidy-analyzer`, and that script prints the required coverage line before evaluating per-source failures.
- No implementation token appears in the PLAN relay. W-5 identity and eligible locks remain unchanged; countgate, m-1/m-3 review, merge, push, publication, deployment, and release remain held.

## Escalation scan

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: yes — this exact approval may permit the Planner to issue the separately gated implementation token
- migration/backfill/destructive-write/canonical-data-repair: no
- money/inventory/orders/planning/accounting/trust-critical-state: yes — the plan controls archive-format implementation
- AI-or-automation-acts-downstream: yes — only a later fresh token may resume product edits
- worker/scheduler/queue/retry/async-side-effect: no
- cross-repo/service-contract/generated-schema/shared-API-event: yes — locked PDC O/N/M and effective W-5 govern
- user-visible-control-with-materializer/downstream-consumer: yes — writer/parser behavior controls archive bytes
- test-runtime-role-mismatch: no — verbose CTest now makes the successful tidy coverage receipt observable
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: no — observation and exact repair authority are now explicitly separated
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: W-5 already granted and effective at the exact frozen row; no new waiver requested
- valid_waiver: yes — only within the unchanged selector and eligible row
WAIVED_RISK_ACCEPTANCE: unchanged from W-5; this review neither expands nor reopens it

## Next gate

The Pair Planner may issue the promised fresh addressed bare implementation token `intg-substep2a-impl-5`, parented to this exact-hash approval and carrying the ten-path structured `SCOPE_DIFF` with the three propagation rows still grounded in `231935`. Until that relay stands literally addressed to this seat, `b09e192` remains frozen and Step 0-quater does not begin.

ACTIONS_GIT_REF: review-only inspection of plan commit 77f2253c/beba597c, incoming carrier 230341, rev15 W-5 replacement receipt, frozen b09e192 held bytes and tags, CTest verbose behavior, tidy harness coverage contract, exact-hunk mapping, staged-tree mechanics, and current scoped statuses; daemon submission only; no product/test/plan/candidate-ref/reset/staging/commit/merge/push/PR/remote-CI/publication/deployment/seal/release action
RELAY_LINT: to be engine-rendered; exact-file lint and root verification follow submission
FINAL_GIT_STATUS_SHORT: shared docs tree contains inherited untracked intg relay artifacts from prior reviewed/STOP cycles; all preserved. Isolated product worktree remains at b09e192 with exactly the two held unstaged manifest modifications and an empty index. This review adds only its engine-rendered relay and engine-owned intg projections.
