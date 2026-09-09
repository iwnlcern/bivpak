## SITREP — R-4.50 token-8 STOP before Task 2 runner entry: the fully proved scratch runner lacked execute permission; the sole invocation returned rc 126; no Task-2 plan command ran

ROLE: Pair Implementer
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: intg-r450-discover-parity-impl-stop-8
PARENT_DISPATCH_ID: intg-r450-discover-parity-impl-8
IN_REPLY_TO: intg-r450/IMPL-pair-planner-20260909-021109.md
RELATED_CONTEXT: intg-r450/PLAN-REVIEW-pair-implementer-20260909-014848.md; intg-r450/PLAN-pair-planner-20260909-013355.md; intg-r450/SITREP-pair-implementer-20260908-231512.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-r450-discover-parity-20260906.md; ../../pdc/master/relays/intg-r450-discover-parity-act/PLAN-master-planner-20260908-140952.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — the pair Planner must consume this process STOP and issue an addressed fresh successor before any retry; token 8 cannot be reused
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: m2-r450-discover-fence-rev2-20260903
DESIGN_LOCK_ID: m2-r450-discover-fence-rev2-20260903 @ sha256 f2216ee606a03b0b5b0b7f4562fed52a7349219c28990e6ee3e89b0cc25e8c6f
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: intg-r450-discover-parity-plan-20260906 @ sha256 4d304232b322e4005518aa00bb688d725996ccecb36906e76ed34d06888f5e90
BASE: B = bbf297e36a38a1fab8c2675f945098a0633f9f8b; provisional P = 54954281b30cae113f399055fff106963a37a443, parent B, tree f1eb8aec36601a02312a5d34a18ea0a6238833a1
BRANCH: intg/r450-discover-parity at provisional P 54954281b30cae113f399055fff106963a37a443 in /Users/jack/Programming/bivpak-intg-r450-discover-parity; clean after the STOP; no remote branch or tag
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: master.master-planner, master.master-reviewer, operator, m-2.planner, m-2.implementer, m-3.planner, m-3.implementer
SUBJECT: STOP UP before Task 2 runner entry under token 8 — complete runner/proof were materialized, but the scratch runner mode was non-executable; sole invocation rc 126 permission denied; no observation, retry, chmod, Task 3, or repository mutation

## Bound authority and completed predecessor tasks

Incoming token-8 relay SHA-256: `b479fafc5dcc011ff83c3ee0687522e12df2bc75f1945c0ab60a1aaf9cd34ce7`. Approved plan revision 9 SHA-256: `4d304232b322e4005518aa00bb688d725996ccecb36906e76ed34d06888f5e90`.

Task 0 completed from a fresh resolved evidence home. Its runner SHA-256 is `2157eda5cb36c61633d1f2b1f13b06f0e105e509a067ce2c5b0edeb76ffaffb6`; proof SHA-256 `c625d7e5749c9877f5f03e80c66f3590be0ecfaef4c3f08670a182100fe59911`; state `ii` selected and exact P, parent, tree, blobs, numstat, venv, build, and observer gates passed.

Task 1 completed at the existing P without commit or amend. Its runner SHA-256 is `0510d48d6b77fe8d19ee59f81ef363426932b4394cc5251983ca8839d528b79b`; proof SHA-256 `6e13797241e420dc2a1031bbdb933d548dabbea65f9f37be20e288b7deb0e7a6`. The fresh GREEN witness and existing case passed. The P-state disclosure suite returned rc 8 with failing set exactly `harness-selftest` and `claude_adapter_file` present in the log 33 times. P rebound as `54954281b30cae113f399055fff106963a37a443`, tree `f1eb8aec36601a02312a5d34a18ea0a6238833a1`, clean.

The token-8 evidence home is the resolved path `/private/var/folders/hq/f0qq8v_103q9y8prfn20rzx80000gn/T/r450-evidence-8oqZqb`. The token-7 home remains sealed and was not reused.

## Task 2 pre-execution packet

Before Task 2's first intended plan command, the complete macOS/Linux runner and supporting artifacts were materialized:

- Runner `/private/tmp/bivpak-r450-impl8-task2-preexec.ecUkh0/task-2-runner.sh`, SHA-256 `384ab644ecbe5f621a2718a17aa526364acf1853db91c6a7fff35df402370b5a`.
- Static proof `task-2-proof.jsonl`, SHA-256 `73b948f749d707a4e22776fc83461464dfb00ada43ba0e8561b6bbdb5105844f`: 216/216 records passed — 162 literal, 32 operational, 11 structural, nine artifact, one binding, and one summary record.
- Linux container wrapper SHA-256 `03580dc393dffe9e7e90db101947b76804b90c5e5205faa8c59991560fbd17d8`; Linux suite SHA-256 `707246fcc2f4f88c20050fa94ac8108365d374ee37de9590b46c28e2edce0677`; entry checker SHA-256 `c3d19cc8821663afc6f1f7f30047fc8d5391d125e330503ffb73e725529ae9f3`.
- All three shell artifacts passed `bash -n`; the Python entry helper compiled.
- EVID preexec binding manifest SHA-256 `db42fbef369a3b03361b89000a085a9557435c03c22235ea8b342875f5314123`; every entry verified.
- The repaired `skipset.py` membership-and-count comparison is the active macOS skip gate. The token-7 byte-order comparison is absent from executable runner bytes.
- Local Docker was available; the frozen runner carries Ubuntu 24.04, `--platform linux/amd64`, `--init`, and the in-runuser `nofile` raise.
- `$EVID/P` was absent and the governed worktree was clean at exact P.

The PREEXEC report incorrectly concluded the packet was runnable after syntax and content proof. It did not gate the scratch runner's executable mode.

## Sole invocation and STOP

The Task-2 runner path was invoked exactly once with the exact three arguments recorded in `$EVID/task-2-exact-invocation.txt`. The controller returned:

```text
TASK2_OUTER_RC=126
zsh:2: permission denied: /private/tmp/bivpak-r450-impl8-task2-preexec.ecUkh0/task-2-runner.sh
```

The scratch runner stat is:

```text
-rw-r--r-- 43276 /private/tmp/bivpak-r450-impl8-task2-preexec.ecUkh0/task-2-runner.sh
```

Cause, owned by this seat: the adapted materializer wrote the runner bytes but did not apply executable permission. Content proof and `bash -n` both succeeded, and the PREEXEC review checked neither the execute bit nor an explicit `test -x`. The earlier token-7 packet had repaired the mode before invocation; this token's rebuild did not preserve that repair.

This failure happened in the invoking shell before the runner shebang, plan-hash gate, binding verification, `STOP` function, or any Task-2 plan command could execute. The absence of `$EVID/P` proves none of the five macOS XML runs, `skipset.py`, scout, token scan, Phase H download, Docker/Linux stages, ENTRY, predictor, B/P table, or Task-2 no-mutation command ran.

No chmod, retry, alternate `bash runner`, re-observation, or substitute command was attempted after rc 126. Under the token's one-invocation/no-retry discipline, the token is consumed.

## Preservation and evidence

Post-STOP read-only state:

```text
HEAD 54954281b30cae113f399055fff106963a37a443
worktree status: empty
$EVID/P: absent
```

Task-2 report SHA-256: `d6bcbdcb609569b6b719c765afbb4b4d5aac58f128132f3d7e8d63ac001279f8`. Thirteen-record STOP evidence manifest SHA-256: `aa165b744437d2021c56dfa76f0ea0b5d4486e688941655f1acda78cc81c1531`; verification rc 0.

No product byte, index, commit, reflog entry, ref, remote, prior evidence record, Docker resource, or main-worktree byte changed during Task 2. Tasks 3 through 8 did not start. No C or H exists. No push, PR, merge, landing push, tag, publication, deployment, release, or closure occurred.

ROW_TRUTH_CHECK: required
SCOPE_DIFF:
- src/adapters/claude_code/claude_code.cpp -> in, existing provisional P commit only
- tests/test_adapter_claude_collect.cpp -> in, existing provisional P commit only
SCOPE_DIFF_RESULT: all-in; token-8 Task 2 introduced zero repository-byte or ref changes
SCOPE_ROW_EVIDENCE:
- src/adapters/claude_code/claude_code.cpp: existing P path, re-fenced in Task 1; unchanged through the Task-2 pre-entry STOP
- tests/test_adapter_claude_collect.cpp: existing P path, re-fenced in Task 1; unchanged through the Task-2 pre-entry STOP

BOUNDARY_CONTRACT:
- Writes: fresh Task-0/1 evidence, Task-2 preexec/STOP evidence, ignored SDD reports, and this relay plus INDEX projection only
- Reads: exact token/plan/review bytes, retained P, prior evidence, Task-0 helpers, Task-1 receipts, and Task-2 preexec artifacts
- Target entity: provisional P remains the only candidate commit; no C or H exists
- Downstream consumer: pair Planner must consume this process STOP and decide whether to issue a fresh addressed successor
- Contract: token 8 is consumed at its sole Task-2 invocation; no in-token permission repair or retry is permitted
- Proof: runner/proof/binding hashes, rc-126 log, non-executable stat, absent observation directory, and clean P
- No-consumer action: STOP UP; no Task 3 through Task 8 action

ACTIONS_GIT_REF: `intg/r450-discover-parity@54954281b30cae113f399055fff106963a37a443`; no remote branch, tag, push, PR, merge, landing push, or release act. Main checkout writes are limited to this daemon-rendered report and INDEX projection; inherited concurrent state is preserved.

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: no
- migration/backfill/destructive-write/canonical-data-repair: no
- money/inventory/orders/planning/accounting/trust-critical-state: yes — one-shot measurement provenance and STOP handling are trust-critical
- AI-or-automation-acts-downstream: yes — the runner invocation consumed token 8 before entry
- worker/scheduler/queue/retry/async-side-effect: yes — retry is expressly prohibited without a successor
- cross-repo/service-contract/generated-schema/shared-API-event: yes — master and owner gates remain downstream
- user-visible-control-with-materializer/downstream-consumer: no
- test-runtime-role-mismatch: yes — the materialized script was syntactically valid but not executable by the controller
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: no
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
retained R-4.50 worktree at P: clean

Main checkout scoped to `.relays/intg` before render: no own-seat rendered path yet. After daemon render, `.relays/intg/INDEX.md` and this SITREP are the expected own-seat paths; inherited concurrent state is preserved.

Done: token-8 Tasks 0 and 1 completed and were review-clean; P rebound unchanged; Task-2 runner/support/proof fully materialized and content-audited; the sole rc-126 invocation and exact pre-entry boundary sealed; P preserved clean.

Not done: any Task-2 observation, skip-set execution, Linux action, ENTRY/predictor/B-P table, Task 3 through Task 8, C, H, push, PR, merge, landing push, tag, publication, deployment, release, or closure.

Blocked: token 8 was consumed by the non-executable scratch runner at its sole Task-2 invocation. This is an Implementer process defect, not a product or plan finding.

Next requested action: `intg.pair-planner` — consume `intg-r450-discover-parity-impl-8` and, if the act remains authorized, issue a fresh addressed successor that restarts from the plan-prescribed fresh Task 0. Preserve provisional P and the sealed token-8 EVID record.
