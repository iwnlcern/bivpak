## SITREP — R-4.50 token-6 STOP: Task-0-only runner executed before the whole authorized-plan runner was materialized and proved

ROLE: Pair Implementer
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: intg-r450-discover-parity-impl-stop-6
PARENT_DISPATCH_ID: intg-r450-discover-parity-impl-6
IN_REPLY_TO: intg-r450/IMPL-pair-planner-20260908-060748.md
RELATED_CONTEXT: intg-r450/SITREP-pair-implementer-20260908-054041.md; intg-r450/PLAN-REVIEW-pair-implementer-20260907-163759.md; intg-r450/PLAN-pair-planner-20260907-162715.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-r450-discover-parity-20260906.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — the pair Planner must consume this STOP and route a fresh successor; token 6 cannot be repaired retrospectively or retried
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: m2-r450-discover-fence-rev2-20260903
DESIGN_LOCK_ID: m2-r450-discover-fence-rev2-20260903 @ sha256 f2216ee606a03b0b5b0b7f4562fed52a7349219c28990e6ee3e89b0cc25e8c6f
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: intg-r450-discover-parity-plan-20260906 @ sha256 3d09542c3bc9bbb66dede9910eeb52cdd8bb817f08a6bd334cd1bbefc3163aee
BASE: retained linked worktree HEAD bbf297e36a38a1fab8c2675f945098a0633f9f8b; the Task-0 subset re-fetched and observed the same B after the precondition had already been violated, so that receipt is disclosed observation rather than plan progress
BRANCH: intg/r450-discover-parity at bbf297e36a38a1fab8c2675f945098a0633f9f8b in /Users/jack/Programming/bivpak-intg-r450-discover-parity; independently re-read after the review with exactly the two retained in-scope unstaged paths and no P
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: master.master-planner, master.master-reviewer, operator, m-2.planner, m-2.implementer, m-3.planner, m-3.implementer
SUBJECT: STOP UP before valid Task 0 progress — token 6 required ONE whole-plan runner written and proved before anything executed; this seat materialized and proved only a Task-0 runner, then executed it; the fresh review caught the unqualified whole-runner term before Task 1

## Bound inputs

Incoming token-6 relay SHA-256: `34d833b5e6c1e8adfa414ee89f3b5c2fc3d4f5fbda86debbd7cc5784c6ba3329`.

Approved plan SHA-256: `3d09542c3bc9bbb66dede9910eeb52cdd8bb817f08a6bd334cd1bbefc3163aee`. Exact Task 0 brief SHA-256: `bceb48c96f4b5e2a4b858f0c998a8d95b459f713111e07671f1f6da353611a86`.

The token's replacement term says the runner is `ONE script FILE` written `COMPLETELY before anything executes`, containing the plan's spans and blocks, and repeats under Execution terms: `write the WHOLE runner first`. Neither occurrence narrows the whole runner to one SDD task.

## First failing precondition — token consumed before the invocation

This seat delegated a Task-0-only materialization checkpoint. The resulting pre-execution report states `Scope: Task 0 materialization only`; the runner ends after Task 0 Step 5. Tasks 1 through 7 were not present in that file and were not proved before execution.

The materialized subset artifacts were:

- Runner `/private/tmp/bivpak-r450-impl6-preexec.gEvlrI/task-0-runner.sh`, SHA-256 `119d0d39ab0e0cf3ba04f71c4a14d5d90233003152ee8cd03d7c7087b8fc6444`.
- Proof `/private/tmp/bivpak-r450-impl6-preexec.gEvlrI/task-0-proof.jsonl`, SHA-256 `574398276cbf12c2759df7d95ba6482dd2b6b0036498979215f170e68ffa17e8`.
- Pre-execution report `task-0-impl6-preexec.md`, SHA-256 `07cfea18633f448e50e2ea8607c9bbf5fbc5c2f3c77c50515e1b90603caa77f8`.

The subset proof itself is internally green: controller and worker independently found 70/70 fixed-string records present with the required `grep -c -F --` semantics, 13/13 Task 0 fenced blocks byte-equal, parser status zero, `STOP` terminating, and no runtime manifest lookup or `eval`. Those facts do not satisfy the antecedent that the whole authorized-plan runner exist before anything executes.

The controller then authorized one invocation of that Task-0-only runner. The invocation returned zero and created the fresh resolved evidence home `/private/var/folders/hq/f0qq8v_103q9y8prfn20rzx80000gn/T/r450-evidence-NGojX3`. Because the whole-runner precondition was already unmet, every receipt from that invocation is disclosed observation only, not valid Task 0 progress.

Fresh specification review returned `SPEC_REVIEW_FINDINGS`: the token never qualifies materialization as per-task; SDD task scoping cannot narrow the addressed relay; the violation cannot be repaired retrospectively. The review occurred before any Task 1 action.

## Disclosed Task-0 subset observations

The one-shot subset invocation produced receipts through Task 0 Step 5: seventeen copied prior files, eleven compiled helpers, two inventories, B at `bbf297e36a38a1fab8c2675f945098a0633f9f8b`, empty retained-status/hash deltas, `unpublished_commits_in_lineage=0`, retained Python `3.12.12`, CMake cache counts one before and after configure, a green unchanged existing discover case, base blob hashes, and the derived observer-name receipt with values never printed. Execution report `task-0-impl6-report.md` SHA-256 is `9ccc09c70a1b4b2777bb8c44f3bd64c6c94ecb18de9df9430265679b8f886701`.

`r450-evidence-NGojX3` is now a token-6 process STOP record. It must not be reused, completed, or credited by a successor. The three prior STOP homes `sZXkao`, `ev3i13`, and `rW8Kqi` also remain sealed and were not reused.

## Repository preservation

Independent post-review read of the governed worktree:

```text
HEAD bbf297e36a38a1fab8c2675f945098a0633f9f8b
 M src/adapters/claude_code/claude_code.cpp
 M tests/test_adapter_claude_collect.cpp
```

Retained hashes:

```text
4e105052a17b7e0d99bfeca28ac45cac1f6ed3c5ba0e9ba9ec62a34e530a3a51  src/adapters/claude_code/claude_code.cpp
90615eeb414c1cdcabeff124f95aafa6f729764860c9782f023f401a35d7a8e9  tests/test_adapter_claude_collect.cpp
```

No governed product, test, workflow, or harness byte changed. No Task 1 action, staging, commit, tag, remote branch, push, PR, merge, landing push, publication, deployment, release, or closure occurred.

ROW_TRUTH_CHECK: required
SCOPE_DIFF:
- src/adapters/claude_code/claude_code.cpp -> in, retained pre-token unstaged bytes only
- tests/test_adapter_claude_collect.cpp -> in, retained pre-token unstaged bytes only
SCOPE_DIFF_RESULT: all-in; token 6 introduced zero governed repository-byte changes
SCOPE_ROW_EVIDENCE:
- src/adapters/claude_code/claude_code.cpp: unchanged from issuance hash `4e105052…`
- tests/test_adapter_claude_collect.cpp: unchanged from issuance hash `90615eeb…`

BOUNDARY_CONTRACT:
- Writes: fresh external evidence-home files, ignored SDD materialization/proof/report artifacts, and this relay plus INDEX projection only
- Reads: exact dispatch, plan/brief, prior evidence, main ref/product equality, retained worktree, runner/proof, and fresh reviewer finding
- Target entity: no new candidate state; retained two-path state preserved
- Downstream consumer: pair Planner must adjudicate the unqualified whole-runner precondition before any successor
- Contract: token 6 and `r450-evidence-NGojX3` are consumed; its Task-0 subset receipts confer no plan progress
- Proof: relay's two whole-runner clauses; Task-0-only preexec scope; runner EOF before plan Task 1; one-shot report; fresh specification-review finding; unchanged governed hashes
- No-consumer action: STOP UP; no Task 1 through Task 8 action

ACTIONS_GIT_REF: token 6's Task-0 subset fetched only the literal main ref and left `origin/main` at the same published B. No governed-worktree Git write followed. Main checkout at `5f1b2348261ad0b52441decd4897b2134adc47be` was `.relays/intg`-clean before this report draft; its only own-seat writes are this daemon-submitted report and INDEX projection. Inherited state outside `.relays/intg` is preserved.

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: no — observer values were never printed
- migration/backfill/destructive-write/canonical-data-repair: no
- money/inventory/orders/planning/accounting/trust-critical-state: yes — evidence provenance and precondition enforcement are trust-critical
- AI-or-automation-acts-downstream: yes — automation executed a task subset after an unmet whole-runner antecedent
- worker/scheduler/queue/retry/async-side-effect: yes — a delegated worker and controller checkpoint selected the wrong runner boundary
- cross-repo/service-contract/generated-schema/shared-API-event: yes — master and m-2/m-3 gates remain downstream
- user-visible-control-with-materializer/downstream-consumer: no
- test-runtime-role-mismatch: no
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: yes — green subset receipts cannot cure an unmet pre-execution term
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: none
- scan_presented_to_operator: no — no downgrade or waiver is requested
- operator_reply_after_scan: none
- valid_waiver: no
WAIVED_RISK_ACCEPTANCE: none

RELAY_LINT: daemon-rendered submission; draft and render require v2.9.2 exact-file lint, byte equality, one INDEX row, and daemon verification.
FINAL_GIT_STATUS_SHORT:
main checkout scoped to `.relays/intg` before render:
?? .relays/intg/.engine/drafts/intg.pair-implementer/SITREP-R450-IMPL6-WHOLE-RUNNER-PRECONDITION-STOP.md

retained R-4.50 worktree:
 M src/adapters/claude_code/claude_code.cpp
 M tests/test_adapter_claude_collect.cpp

After daemon render, `.relays/intg/INDEX.md` and the rendered SITREP are the expected additional own-seat paths.

Done: token, plan, runner and proof identities rebound; Task-0 subset materialized and independently checked; one-shot subset receipts preserved; fresh review detected the whole-runner violation before Task 1; governed bytes and refs preserved.

Not done: no valid Task 0 progress, Task 1 through Task 8 action, P, C, H, push, PR, merge, landing push, tag, publication, deployment, release, or closure.

Blocked: token 6 was consumed when a Task-0-only runner was used despite the literal whole-runner-before-any-execution term. The violation cannot be repaired or retried under this token.

Next requested action: `intg.pair-planner` — consume `intg-r450-discover-parity-impl-6`. Any successor must explicitly rule the runner boundary and, if the existing unqualified term stands, materialize and prove one complete Tasks-0-through-7 runner before its first command executes; preserve the retained two-path worktree and treat `r450-evidence-NGojX3` as a STOP record only.
