## PLAN-REVIEW artifact — APPROVE revision 13 at f59b9017: route (A) is exact, the pre-commit Linux census closes the stopped-build gap, and the four tidy folds remain behavior-bounded

ROLE: Pair Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: approve
DISPATCH_ID: intg-substep2a-plan-review-13
PARENT_DISPATCH_ID: intg-substep2a-plan
IN_REPLY_TO: intg-substep2a/PLAN-pair-planner-20260903-184850.md
RELATED_CONTEXT: intg-substep2a/IMPL-pair-implementer-20260903-181612.md; intg-substep2a/SITREP-pair-planner-20260903-185751.md; intg-substep2a/PLAN-REVIEW-pair-implementer-20260903-141140.md; ../../../pdc/master/relays/intg-substep2a-format-act/DESIGN-planner-20260903-183510.md; ../../../pdc/master/relays/intg-substep2a-format-act/PLAN-master-planner-20260903-183926.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new gate — this approval closes only the exact-hash plan review at f59b9017; W-5 remains effective at its frozen selector and eligible row; implementation remains prohibited until a fresh addressed bare token `intg-substep2a-impl-4` stands, and byte review, merge, push, publication, deployment, and release retain their separate gates; the release hold is ABSOLUTE
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
PLAN_LOCK_ID: intg-substep2a-plan-20260830 @ sha256 f59b90172806416f4dbc5c13afae4ee00c72a3babd16d9717054f0c026d8af0b
TARGET_RELAY_SHA256: 3ef70944fb796dbd96e8fe6c0230c8814c206d580a6334f68462d5dfd4470b4c
TARGET_PLAN_SHA256: f59b90172806416f4dbc5c13afae4ee00c72a3babd16d9717054f0c026d8af0b
TARGET_PLAN_COMMIT: aca5b514c4258bc55a6c2f24487a5dd10df72529
BASE: main@46df8f3c35981a4ae3f77cf3293a4b7212b4b996; exact review filed from the docs lane at aca5b514
BRANCH: intg/format-act@b09e1922c16da50b5bef0644d9923a567b98c468; parent 363d812fba2610f7e5c71fdb9daee5c7f740027a; four commits above base; status empty; FROZEN RED and not a merge-packet input; no product byte moves under this review
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: master.master-planner, master.master-reviewer, m-1.planner, m-1.implementer, m-3.planner, m-3.implementer
SUBJECT: APPROVE exact f59b9017 — revision 13 folds the 181612 STOP under m-1 route (A), adds the missing pre-commit Linux all-target and tidy census, and bounds the two-file repair without changing C-1..C-7; issue no product instruction except through fresh addressed token intg-substep2a-impl-4

## Verdict

APPROVE exact SHA-256 `f59b90172806416f4dbc5c13afae4ee00c72a3babd16d9717054f0c026d8af0b`.

Revision 13 is internally consistent, mechanically executable, and sufficient to close the plan defect exposed by the `181612` STOP. It carries m-1's route (A) without widening the sealed design, fenced propagation sites, or ten-path allowlist.

This approval is review-only. It authorizes no edit, tag, reset, staging, commit, container execution against changed bytes, Task 4, candidate submission, branch/ref move, merge, push, PR, remote CI, publication, deployment, seal, or release.

## Review findings

### F1 — the stopped GCC aggregate defect is closed at the correct ownership surface

Step 0-ter binds the only header repair to `Manifest::repos` itself: `repos;` becomes `repos{};`, exactly +1/-1 in `manifest.hpp`. The three ruled propagation files and their aggregates remain byte-frozen; per-site `.repos = {}` is expressly forbidden, including the manifest-test aggregate. This is route (A) from owner ruling `183510`, stays within the existing manifest header write set, and changes neither emitted wire bytes nor the logical empty-vector value of omitted aggregate members.

The plan also retains the red `b09e192` candidate by a local tag before branch movement and makes any frozen-state mismatch a STOP. That preserves the failed specimen and prevents an unreceipted repair base.

### F2 — the Linux compile/tidy gap is closed before replacement-commit construction

New Step 4b runs against the two-file working diff before the soft reset and replacement commit. It receipts the host/container manifest bytes, configures the canonical Ubuntu 24.04 amd64 `--init` topology with required clang-tidy, builds the default all-target graph, then runs the safety tidy row over every compile-command source. Configure, build, missing-initializer diagnostic count, coverage, and tidy return code are independent pass terms; a stopped build is explicitly red and cannot be treated as an environmental residual.

The runner is adequate without Task 4's later suite phase: `harness/ci/run_clang_tidy.py` imports only the Python standard library, derives every project `src` translation unit from `compile_commands.json`, and rejects an empty or dropped source population. Full product CTest remains in Task 4 and may begin only after Step 4b, the replacement commit, and the scoped review loop are green.

### F3 — the four tidy folds are behavior-bounded and implementable

The plan confines the checkpoint write set to `manifest.hpp` and `manifest.cpp`, names the four candidate-owned findings, requires every diff hunk to map to one of them, and preserves the inventory populations 64/8/3 plus both enforcement classes. The `raw_repo_note_values` folds must use the existing checked `at_key(...).get(...)` idiom and preserve the same thrown simdjson error path. The `RepoRowFacts` and enum-helper folds are structural; their concrete shapes remain implementation choices only inside those constraints.

The typed-error literal multiset is a necessary source-byte discriminator, not by itself a complete control-flow proof. Revision 13 does not rely on it alone: it conjunctively requires the full FX-N, FX-O, and parser rows, the explicit missing/malformed `repos` ErrKind-plus-detail check, unchanged raw throw path, unchanged wire controls, unchanged inventory/enforcement census, and later m-1 byte review. Read as that complete gate, T-4 adequately fixes parser acceptance and detail behavior. An implementation report that presented only the multiset equality would not satisfy this plan.

The apparent NOLINT alternatives are not a contradiction: term gamma permits a suppression only if a code fix would change behavior, while term delta merely lists possible shapes subject to that stricter condition. A structural fix remains available at each named site; any need for a suppression or third path outside the stated terms remains a STOP.

### F4 — replacement mechanics and downstream gates remain coherent

Step 5 starts from the frozen `b09e192` tree, soft-resets only after macOS and Linux pre-commit gates, explicitly stages exactly the six Task-3 paths, proves both historical tranches plus the two new manifest files in the cached tree, and creates one replacement commit above `363d812`. Postconditions retain both superseded commits, require four commits above base, require a clean worktree, and prove the new candidate differs from `b09e192` in exactly the two manifest paths.

Task 4 then re-runs confinement, C-1..C-7, T-1..T-5, both-platform evidence, FX-N/FX-O, and the inventory censuses at the replacement candidate. m-1 and m-3 review that exact candidate through master. Countgate, merge, push, publication, deployment, and release remain held.

## Exact review evidence

- Incoming relay SHA-256: `3ef70944fb796dbd96e8fe6c0230c8814c206d580a6334f68462d5dfd4470b4c`.
- Reviewed plan: commit `aca5b514c4258bc55a6c2f24487a5dd10df72529`, SHA-256 `f59b90172806416f4dbc5c13afae4ee00c72a3babd16d9717054f0c026d8af0b`.
- Immutable rev12 comparison: SHA-256 `e5875e8ee830265743e05c09db2224d2bca956f9dba7ed7372cfc417889dd2bc`; rev12 to rev13 changes one plan file, 20 insertions and 9 deletions; `git diff --check` is clean.
- Revision-13 measurement relay `185751` hashes to `c7650f161a3dd6f8fb0acbce6cd9624bdfd6958b41facc39d1a51801d7e7d242`; its archived root sweep hashes to `0c2a533025b3d821001200313e070605aa42e28b8ca72b9a849017bc5746cf36` and records the one W-5-covered O design-lineage carrier red with no lineage-walk error.
- Frozen product state was freshly reverified: HEAD `b09e1922c16da50b5bef0644d9923a567b98c468`, parent `363d812fba2610f7e5c71fdb9daee5c7f740027a`, four commits above `46df8f3`, and empty status.
- Candidate source inspection confirms the four cited tidy sites exist at the recorded lines and the tidy harness uses only standard-library Python while enforcing nonempty, complete source coverage.
- No product, test, plan, candidate branch, tag, ref, merge, push, PR, remote-CI, publication, deployment, seal, or release action was taken by this review.

## Escalation scan

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: yes — exact approval may permit the planner to issue the separately gated fresh implementation token
- migration/backfill/destructive-write/canonical-data-repair: no
- money/inventory/orders/planning/accounting/trust-critical-state: yes — the plan controls downstream archive-format implementation
- AI-or-automation-acts-downstream: yes — a later fresh token may resume product edits
- worker/scheduler/queue/retry/async-side-effect: no
- cross-repo/service-contract/generated-schema/shared-API-event: yes — locked PDC O/N/M and effective W-5 govern
- user-visible-control-with-materializer/downstream-consumer: yes — writer/parser behavior controls archive bytes
- test-runtime-role-mismatch: no — the pre-commit compile/tidy census and later full parity suite are deliberately partitioned
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: no — the stopped-build defect and four candidate-owned tidy findings have exact bounded gates
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: W-5 already granted and effective at the exact frozen row; no new waiver requested
- valid_waiver: yes — only within the unchanged selector and eligible row
WAIVED_RISK_ACCEPTANCE: unchanged from W-5; this review neither expands nor reopens it

## Next gate

The pair Planner may issue the promised fresh addressed bare implementation token `intg-substep2a-impl-4`, parented to this exact-hash approval and carrying the ten-path structured `SCOPE_DIFF` with the three propagation rows still grounded in `231935`. Until that relay stands literally addressed to this seat, `b09e192` remains frozen and Step 0-ter does not begin.

ACTIONS_GIT_REF: review-only inspection of plan commit aca5b514/f59b9017, the immutable rev12 plan, the m-1/master C-3 route, revision-13 W-5 measurement receipts, the frozen b09e192 product bytes, and the tidy harness; daemon submission only; no product/test/plan/candidate-ref/merge/push/PR/remote-CI/publication/deployment/seal/release action
RELAY_LINT: to be engine-rendered; exact-file lint and root verification follow submission
FINAL_GIT_STATUS_SHORT: non-empty shared docs tree — inherited modified s4 INDEX/SEATS plus inherited untracked s4 history and migration artifact; intg carries the valid untracked 181612 STOP, two inert untracked failed-draft artifacts 181132/181438, and one root draft duplicate; all preserved and disclosed; the isolated product worktree is exactly clean at b09e192; this review adds only its engine-rendered relay and engine-owned intg projections
