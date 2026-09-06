## PLAN-REVIEW — MUST REVISE exact rev5 7804d89b: the literal refspec is shell-safe, but the command-binding gate passes without the executable line and the new dry-run evidence is absent from the durable return

ROLE: Pair Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: must-revise
DISPATCH_ID: intg-firstpush-plan-review-5
PARENT_DISPATCH_ID: intg-firstpush-plan-5
IN_REPLY_TO: intg-firstpush/PLAN-pair-planner-20260905-174634.md
RELATED_CONTEXT: intg-firstpush/IMPL-pair-implementer-20260905-163348.md; intg-firstpush/SITREP-pair-planner-20260905-164106.md; intg-firstpush/PLAN-pair-planner-20260905-151513.md; intg-firstpush/PLAN-REVIEW-pair-implementer-20260905-153200.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-firstpush-20260905.md; ../../../pdc/master/relays/r438-transcription-at-merged-bytes/PLAN-master-planner-20260905-164704.md; ../../../pdc/master/relays/r438-transcription-at-merged-bytes/PLAN-master-planner-20260905-082012.md; ../../../pdc/master/relays/publication-path-ruling/PLAN-operator-20260902-141706.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new human gate — master's `164704` ruling authorizes a fresh pair revision and token for the still-unperformed publication, but `intg-firstpush-impl-2` must not issue until rev6 closes F1-F2 and receives a new exact-hash approval; publication, PR, remote CI, tag, deployment, and release remain held
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
PLAN_LOCK_ID: intg-firstpush-plan-20260905 @ sha256 7804d89b17677d18f603bc60ab96417a555952636a5dd880197b5489675cdecf
TARGET_RELAY_SHA256: e78bc18d685d463ca910d70b39093760dc6831ba2f3f09d880e0a2437370928d
TARGET_PLAN_SHA256: 7804d89b17677d18f603bc60ab96417a555952636a5dd880197b5489675cdecf
TARGET_PLAN_COMMIT: 65ed837199f35e88d94fe7b6a48f7564fab6ec8f
REVIEWED_PLAN: docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-firstpush-20260905.md at commit 65ed837199f35e88d94fe7b6a48f7564fab6ec8f, sha256 7804d89b17677d18f603bc60ab96417a555952636a5dd880197b5489675cdecf
BASE: main@65ed837199f35e88d94fe7b6a48f7564fab6ec8f; publication PIN bbf297e36a38a1fab8c2675f945098a0633f9f8b; origin refs/heads/main observed read-only at OLD 0db8fdd8424d27aad2c547614e9ebb95621a2794
BRANCH: main@65ed837199f35e88d94fe7b6a48f7564fab6ec8f — review-only; no actual push, state-changing fetch, local or remote ref movement, branch, tag, worktree byte, staging, commit, PR, remote CI, deployment, release, or remote write
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: master.master-planner, master.master-reviewer, operator, m-3.planner, m-3.implementer, m-4.planner
SUBJECT: MUST REVISE exact rev5 7804d89b — retain the literal PIN refspec and successful zsh/bash dry-run behavior, but make the plan-byte command check uniquely bind the executable act as master required, fail closed on the new evidence writes, and carry the command/shell/dry-run records verbatim in the IMPL return

## Verdict

MUST REVISE exact SHA-256 `7804d89b17677d18f603bc60ab96417a555952636a5dd880197b5489675cdecf`.

The literal refspec correction itself is sound. Independent zsh 5.9 and bash 3.2 dry runs of `git push --dry-run origin bbf297e36a38a1fab8c2675f945098a0633f9f8b:refs/heads/main` each returned 0 and named `0db8fdd..bbf297e ... -> main`; read-only probes before, between, and after the dry runs all observed origin `refs/heads/main` unchanged at OLD. The new exact literal has no parameter expansion for zsh to reinterpret, and the old executable form occurs zero times.

Two defects remain in the new gate and evidence contract. They are on the load-bearing correction added because rev4's untested command form consumed a token, so exact-hash approval is withheld.

## F1 — the command-binding gate does not bind the executable push line and departs from master's exact predicate

Master `164704` names the plan check as:

```text
grep -c -F 'git push origin bbf297e36a38a1fab8c2675f945098a0633f9f8b:refs/heads/main' <plan> == 1
```

Rev5 instead accepts `n >= 1`. The measured fixed-string line count is 4: Global Constraints line 15, the gate/logging line 35, executable Step 1 line 39, and lineage line 75. More decisively, deleting executable line 39 only in a read-only stream leaves three matching lines and the exact rev5 predicate still returns green:

```text
grep_rc=0 remaining_literal_lines=3 plan_gate_rc=0
```

Therefore the gate can pass when the executable act is missing or different. It proves only that prose or an independently authored logging command contains the string, not that Task 2 Step 1 is byte-equal to it. `push-command.txt` is also written from a second hard-coded literal; there is no `cmp`, `diff`, digest, or unique extraction tying that file to the Task 2 executable bytes. Its write status is not captured, so a failed command-log write does not STOP the push.

Required fold: obey master's exact-one predicate or obtain an explicit successor ruling; make the checked predicate select the one executable Task 2 act rather than any prose occurrence; create `push-command.txt` with a checked status and verify it byte-for-byte against the uniquely selected executable command before the dry run and act. The check must go red if Task 2's executable line is absent, duplicated, or different. Preserve the literal 40-hex refspec and do not reintroduce a variable before the colon.

## F2 — the new gate evidence is neither fully fail-closed nor required in the durable IMPL return

The gate adds `gate-shell.txt`, `push-command.txt`, `gate-dryrun-stdout.txt`, `gate-dryrun-stderr.txt`, and `gate-dryrun.txt`, but the shell and command-log writes are unchecked. The concatenation into `gate-dryrun.txt` and the final `prepush-gate.txt` write are also not status-captured. With the plan's deliberate no-`set -e` execution model, a failed `push-command.txt` or `prepush-gate.txt` write can continue into the irreversible act. This contradicts the gate's claim that the command is logged before execution and every expected value is recorded or the push does not happen.

Task 3 Step 4 then requires only `prepush-gate.txt`, whose new fields preserve the shell string and `dryrun_rc`, not the dry-run output or logged command bytes. It does not require any of `gate-shell.txt`, `push-command.txt`, `gate-dryrun-stdout.txt`, `gate-dryrun-stderr.txt`, or `gate-dryrun.txt` in the file-first return. A final relay can therefore claim the new acceptance condition while omitting the only bytes that show the required `0db8fdd..bbf297e ... -> main` result and the command that was logged.

Required fold: status-check every new load-bearing evidence write before the act and verify the resulting files' expected content. Add `gate-shell.txt`, `push-command.txt`, and the complete dry-run stdout/stderr or combined record verbatim to Task 3 Step 4's required IMPL return. The return must make both the shell/command binding and the required OLD-to-PIN `main` dry-run line independently reviewable after the external evidence home disappears.

## Checks that remain closed

- Exact identity: the live artifact is byte-equal to `HEAD` at commit `65ed837199f35e88d94fe7b6a48f7564fab6ec8f`; SHA-256 is exactly `7804d89b17677d18f603bc60ab96417a555952636a5dd880197b5489675cdecf`. The incoming relay SHA-256 is `e78bc18d685d463ca910d70b39093760dc6831ba2f3f09d880e0a2437370928d` and exact-file lint is clean. Run-root engine verification reported `ok=true`, 480 dispositions.
- Authority: operator carrier `b30cff98372867bd67a96eec6fadf7b73add0854b1fc118a9f6eb85663297e30`, repaired master route `0fbd4fe64314040de498f8b56f091e82873515f9abd1f78f1bbddfe83967c320`, and master successor ruling `ce0fb56c3e86894433ec041600f1d1338f5e8de95b65392a69f90c24e8d3d7e4` re-hash exactly. The master ruling exact-file lint is clean; no newer substantive master relay than `164704` was present.
- Current safe preflight: STOP-1 rc 0; origin main is OLD; residue above PIN is eight commits at review time; effective push and fetch URLs each read the authorized private URL; the resolved pre-push hook is not executable; visibility is `PRIVATE`.
- Literal behavior: both target shells preserved the literal refspec exactly; both independent dry runs returned 0 with the required fast-forward line; all three remote probes stayed at OLD. No actual push or state-changing fetch ran during this review.
- Rev2-rev4 instruments remain unchanged: external evidence boundary, split byte inventories, exact symlink-target records, STOP-1/STOP-2, census 3/2, outcome classification, no-stop post-attempt evidence path, complete receipts in observed-publication classes, and computed verdict.
- Scope and holds remain exact: one intended origin `refs/heads/main` fast-forward to PIN; no force, other ref, retry under one token, branch, tag, PR, remote-CI citation, worktree byte, release, or R-4.52 decision.

## Acceptance status

1. HOLD — the literal action is technically valid, but F1 prevents proof that the reviewed executable act is the command the gate binds.
2. RED — the new command-binding and evidence-record portion of the fresh gate is non-unique and not fail-closed.
3. GREEN unchanged — the census remains exact and no credential value is required in evidence.
4. RED for the new evidence surface — the existing outcome/receipt flow remains closed, but F2 omits the new shell/command/dry-run records from the durable return.
5. GREEN unchanged — the pre/post byte and exact symlink-target boundary remains specified.
6. GREEN as a hold — no PR, remote CI citation, tag, release, or `gh` write is admitted.

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: yes — the publication and credential-shape census cross a trust boundary
- migration/backfill/destructive-write/canonical-data-repair: no
- money/inventory/orders/planning/accounting/trust-critical-state: yes — the one-shot remote ref and its evidence are trust-critical
- AI-or-automation-acts-downstream: yes — approval would permit the Pair Planner to issue a fresh publication token
- worker/scheduler/queue/retry/async-side-effect: yes — the irreversible remote side effect and one-attempt-per-token rule are explicit
- cross-repo/service-contract/generated-schema/shared-API-event: yes — PDC authority governs the Bivpak publication
- user-visible-control-with-materializer/downstream-consumer: no
- test-runtime-role-mismatch: yes — the prior failure was caused by zsh expansion and the replacement gate must bind the actual target-shell command
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: yes — the non-binding predicate and missing durable dry-run evidence leave residual publication risk
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: none requested or claimed
- scan_presented_to_operator: no — this review routes the exact defects through the Pair Planner
- operator_reply_after_scan: none
- valid_waiver: no
WAIVED_RISK_ACCEPTANCE: none

## Next gate

File rev6 at a new digest folding F1-F2 while retaining the literal refspec, successful target-shell dry-run form, every rev2-rev4 instrument, one attempt per fresh token, and all downstream holds. Route those exact bytes back under a unique review id. Do not issue `intg-firstpush-impl-2` on rev5.

ACTIONS_GIT_REF: review-only inspection at main 65ed837199f35e88d94fe7b6a48f7564fab6ec8f; exact relay/plan/authority hashes, root-engine state, topology, endpoint, hook, visibility, and remote head; two explicitly disclosed read-only `git push --dry-run` executions of the literal PIN refspec, one in zsh and one in bash, with remote probes before/between/after unchanged at OLD; streamed anti-vacuity discriminator only; daemon submission of this review only. No actual push, state-changing fetch, ref movement, branch, tag, product/test/workflow/plan byte, staging, commit, PR, remote CI, deployment, or release.
RELAY_LINT: incoming and master-ruling exact-file v2.9.2 lint clean with freshness disabled; outgoing draft/render require exact-file lint, daemon receipt, byte comparison, unique INDEX row, and engine verification; no implementation token may consume this must-revise review
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
 ?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-CARRIER-COMPLETE-20260809-192358.md
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

Done: exact-hash rev5 PLAN review; literal refspec and dry-run behavior independently reproduced; two remaining command/evidence defects specified
Not done: no `intg-firstpush-impl-2`, actual push, state-changing fetch, ref movement, branch, tag, repository/product/test/workflow/plan byte, staging, commit, PR, remote CI, deployment, release, or downstream closure
Next requested action: intg.pair-planner — fold F1-F2 into rev6 and request exact-hash review; do not dispatch rev5
