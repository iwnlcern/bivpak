## PLAN-REVIEW — APPROVE exact rev4 e8e4b32b: exact symlink-target records and post-publication receipt continuity close the rev3 findings

ROLE: Pair Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: approve
DISPATCH_ID: intg-firstpush-plan-review-4
PARENT_DISPATCH_ID: intg-firstpush-plan-4
IN_REPLY_TO: intg-firstpush/PLAN-pair-planner-20260905-151513.md
RELATED_CONTEXT: intg-firstpush/PLAN-REVIEW-pair-implementer-20260905-150242.md; intg-firstpush/PLAN-pair-planner-20260905-144350.md; intg-firstpush/PLAN-REVIEW-pair-implementer-20260905-143628.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-firstpush-20260905.md; ../../../pdc/master/relays/r438-transcription-at-merged-bytes/PLAN-master-planner-20260905-082012.md; ../../../pdc/master/relays/publication-path-ruling/PLAN-operator-20260902-141706.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — this exact-hash approval closes the pair PLAN-REVIEW gate; the pair Planner may separately issue the already-named `intg-firstpush-impl` token under the commissioned delegation and standing operator/master route, while merge, later publication, deployment, and release remain separately gated and the release hold remains absolute
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
PLAN_LOCK_ID: intg-firstpush-plan-20260905 @ sha256 e8e4b32bbcb1ad32f0045871fbf6d55473688bcc9d4731b75c46f286b68f1bc4
TARGET_RELAY_SHA256: 0785e1003558f473e178a71f722f8ba6c8d83cef97a6c0abee351c46ad55d2e3
TARGET_PLAN_SHA256: e8e4b32bbcb1ad32f0045871fbf6d55473688bcc9d4731b75c46f286b68f1bc4
TARGET_PLAN_COMMIT: 4c2b4b70d0d5cb8597a3a1d0495efcd097e94adf
REVIEWED_PLAN: docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-firstpush-20260905.md at commit 4c2b4b70d0d5cb8597a3a1d0495efcd097e94adf, sha256 e8e4b32bbcb1ad32f0045871fbf6d55473688bcc9d4731b75c46f286b68f1bc4
BASE: main@4c2b4b70d0d5cb8597a3a1d0495efcd097e94adf; publication pin bbf297e36a38a1fab8c2675f945098a0633f9f8b; origin refs/heads/main observed read-only at 0db8fdd8424d27aad2c547614e9ebb95621a2794
BRANCH: main@4c2b4b70d0d5cb8597a3a1d0495efcd097e94adf — review-only; no push, state-changing fetch, ref, branch, tag, worktree byte, staging, commit, PR, remote-CI, deployment, release, or remote write
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: master.master-planner, master.master-reviewer, operator, m-3.planner, m-3.implementer, m-4.planner
SUBJECT: APPROVE exact rev4 e8e4b32b at 4c2b4b7 — rev3 F1 closes with exact target-byte files, checked fail-fast hashing, NUL-delimited records, count completeness, and cmp; F2 closes with checked receipt-i copying, accumulated findings, no post-attempt STOP, and complete receipts for both observed-publication classes; the pinned one-attempt act and every downstream hold remain exact

## Verdict

VERDICT: approve

The live plan, committed plan, and incoming carrier match their declared exact bytes: plan SHA-256 `e8e4b32bbcb1ad32f0045871fbf6d55473688bcc9d4731b75c46f286b68f1bc4`, carrier SHA-256 `0785e1003558f473e178a71f722f8ba6c8d83cef97a6c0abee351c46ad55d2e3`, at commit `4c2b4b70d0d5cb8597a3a1d0495efcd097e94adf`. The incoming carrier passes exact-file v2.9.2 lint with freshness disabled. The commit contains only docs/relay surfaces, including the preceding review and the archived root sweep; it contains no product, test, harness, workflow, remote, or ref mutation.

## Rev3 finding closure

F1 closes. The `SYMCHILD` command writes `readlink -n` output directly to a target file, hashes that file under `set -e`, requires a 64-character digest, and appends one digest/path pair as two NUL-delimited fields. No target byte passes through command substitution. Both the checked `xargs` status and discovered-times-two versus recorded-NUL count gate completeness, and pre/post records are compared with `cmp`.

Independent execution of the exact child form in bash and zsh produced identical record bytes, rc 0, and four NULs for two links. The distinct targets `target` and `target<LF>` produced the distinct digests `34a04005bcaf206eec990bd9637d9fdb6725e0a0c0d4aebf003f17f4c956eb5c` and `c97ecfda4d205190b9f1fdcf0f19411358178988023530742d75b97c91551cf3`. A list containing one link and one regular file returned `xargs_rc=1` and failed the completeness comparison. On the live checkout the exact form returned find/sort/xargs rcs `0/0/0`, 17 discovered links, 34 record NULs, and completeness rc 0.

F2 closes. After the one push attempt, Task 2 Steps 2-3 contain zero `|| STOP` branches. The outcome class is written, receipt (i)'s copy status is captured, and every evidence or boundary defect is appended to `findings.txt`. Both classes `a` and `c` — the two cases where the outcome probe reads the pin — route through Task 3 Steps 1-3 before return, including the one-ref `--no-tags` fetch and the complete three-line receipt. The final verdict is mechanical: success only for class `a` with an empty findings file; every other state returns STOP UP, and no state retries the push.

## Locked-plan checks

- Authority and act: the operator carrier still hashes to `b30cff98372867bd67a96eec6fadf7b73add0854b1fc118a9f6eb85663297e30`; master's repaired route hashes to `0fbd4fe64314040de498f8b56f091e82873515f9abd1f78f1bbddfe83967c320`. They retain the one-time first-publication route, exact pin, STOP-1/STOP-2, census, receipt, R-4.52 follow-up, and absolute release hold.
- Scope: the later token permits exactly one fast-forward push of `bbf297e36a38a1fab8c2675f945098a0633f9f8b:refs/heads/main` to `origin`. It admits no other ref, force flag, retry, tag, PR, remote CI, release, or working-tree edit.
- Fresh gate: STOP-1, STOP-2, the single effective push URL, fetch URL, resolved hook state, visibility, and census record are re-measured together, and the push is the next command.
- Boundary: evidence is created only after its canonical parent is proved outside the checkout. Regular files and exact symlink targets are inventoried before and after. The plan executes in the dispatched primary checkout context; this seat verified current `pwd -P` equals the canonical repository root, and no planned command changes directory before either `find .` inventory.
- Outcome: every client status is followed by a remote probe and one recorded class. An observed publication always receives the safe full receipt before success or STOP is returned; an unobserved or non-publication class never prompts a retry.

## Current independent evidence

- Exactly one effective push URL and the fetch URL both read `https://github.com/iwnlcern/bivpak.git`; repository visibility reads `PRIVATE`; the resolved `.git/hooks/pre-push` is not executable.
- Read-only `origin refs/heads/main` remains `0db8fdd8424d27aad2c547614e9ebb95621a2794`. Pin-to-main and remote-to-pin ancestry both return rc 0; remote-to-pin count is 814 and the current pin-to-main docs residue is five commits.
- The census of record reproduced exactly: tree arm 3 lines, history arm 2 paths, both expected-set diffs rc 0, and history stderr 0 bytes.
- No push or state-changing fetch ran. No remote/local ref, branch, tag, repository byte, index entry, PR, remote-CI run, deployment, or release changed.

This approval is exact-hash and review-only. It is not the implementation token and grants no merge, second publication, deployment, or release authority.

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: yes — the ruled publication and credential-shape census cross a trust boundary
- migration/backfill/destructive-write/canonical-data-repair: no
- money/inventory/orders/planning/accounting/trust-critical-state: yes — the one-shot remote ref and outcome receipt are trust-critical
- AI-or-automation-acts-downstream: yes — this approval permits the pair Planner's separately governed publication dispatch
- worker/scheduler/queue/retry/async-side-effect: yes — the one-attempt remote side effect and ambiguous-outcome handling are explicit
- cross-repo/service-contract/generated-schema/shared-API-event: yes — PDC authority governs the Bivpak act
- user-visible-control-with-materializer/downstream-consumer: no
- test-runtime-role-mismatch: no
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: no — rev4 stays within the exact ruled act and retains the full post-act receipt
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER: none
WAIVED_RISK_ACCEPTANCE: none

ACTIONS_GIT_REF: read-only review at main 4c2b4b7; exact relay/plan and authority pins; current remote URL/visibility/head/ancestry; full census; exact symlink-target and failure discriminators in external scratch; daemon submission of this review only; no push, state-changing fetch, ref, branch, tag, repository/product/test/workflow/plan byte, staging, commit, PR, remote CI, deployment, or release
RELAY_LINT: incoming exact-file v2.9.2 clean with freshness disabled; outgoing draft/render require exact-file lint, daemon receipt, byte comparison, unique INDEX row, and engine verification; no root-wide green claim
FINAL_GIT_STATUS_SHORT: inherited shared-root state only before submission — modified `.relays/s4/INDEX.md` and `.relays/s4/SEATS.md`; untracked S4 files, the S4 migration doc, and `relay-draft-intg-task4-stop.md`; preserved outside this review

Done: exact-hash rev4 PLAN review; both rev3 findings independently reproduced closed; authority, pin, census, endpoint, hook, and current remote state rechecked
Not done: no implementation token, push, state-changing fetch, ref move, branch, tag, repository byte, staging, commit, PR, remote CI, deployment, release, or downstream closure
Next requested action: intg.pair-planner — if proceeding, issue the uniquely parented `intg-firstpush-impl` token through the commissioned delegated lineage against this exact approval; preserve every plan STOP, one-attempt rule, receipt, R-4.52 return, and downstream hold
