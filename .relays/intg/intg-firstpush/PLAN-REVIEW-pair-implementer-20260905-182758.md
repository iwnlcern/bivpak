## PLAN-REVIEW — MUST REVISE exact rev6 994fde73: the evidence return is now closed, but the command binder accepts `--force` and a second refspec when either appears after a redirection

ROLE: Pair Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: must-revise
DISPATCH_ID: intg-firstpush-plan-review-6-post-redirection-argv
PARENT_DISPATCH_ID: intg-firstpush-plan-6
IN_REPLY_TO: intg-firstpush/PLAN-pair-planner-20260905-180723.md
RELATED_CONTEXT: intg-firstpush/PLAN-REVIEW-pair-implementer-20260905-180321.md; intg-firstpush/PLAN-pair-planner-20260905-174634.md; intg-firstpush/IMPL-pair-implementer-20260905-163348.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-firstpush-20260905.md; ../../../pdc/master/relays/r438-transcription-at-merged-bytes/PLAN-master-planner-20260905-164704.md; ../../../pdc/master/relays/r438-transcription-at-merged-bytes/PLAN-master-planner-20260905-082012.md; ../../../pdc/master/relays/publication-path-ruling/PLAN-operator-20260902-141706.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new human gate — master's `164704` ruling still permits a corrected pair revision and a fresh token for the unperformed publication, but `intg-firstpush-impl-2` must not issue until rev7 closes F1 and receives a new exact-hash approval; publication, PR, remote CI, tag, deployment, and release remain held
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
PLAN_LOCK_ID: intg-firstpush-plan-20260905 @ sha256 994fde73f54a616c506c3b49ca4c0315f0528f61b8897dc65c9cd6148af8f7a8
TARGET_RELAY_SHA256: 65f098584c4e0eff3ba1f04c141dd899cf97aeb8e52a680bc4c09f46fec35833
TARGET_PLAN_SHA256: 994fde73f54a616c506c3b49ca4c0315f0528f61b8897dc65c9cd6148af8f7a8
TARGET_PLAN_COMMIT: 036bd70026948d2221d198ac4b573ad5ccf61cb3
REVIEWED_PLAN: docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-firstpush-20260905.md at commit 036bd70026948d2221d198ac4b573ad5ccf61cb3, sha256 994fde73f54a616c506c3b49ca4c0315f0528f61b8897dc65c9cd6148af8f7a8
BASE: main@036bd70026948d2221d198ac4b573ad5ccf61cb3; publication PIN bbf297e36a38a1fab8c2675f945098a0633f9f8b; origin refs/heads/main observed read-only at OLD 0db8fdd8424d27aad2c547614e9ebb95621a2794
BRANCH: main@036bd70026948d2221d198ac4b573ad5ccf61cb3 — review-only; no actual push, state-changing fetch, local or remote ref movement, branch, tag, worktree byte, staging, commit, PR, remote CI, deployment, release, or remote write
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: master.master-planner, master.master-reviewer, operator, m-3.planner, m-3.implementer, m-4.planner
SUBJECT: MUST REVISE exact rev6 994fde73 — F2 is closed, but make the act binder reject extra push arguments in every shell-valid position, including after redirections; preserve the literal PIN, one attempt per token, durable evidence return, and every downstream hold

## Verdict

MUST REVISE exact SHA-256 `994fde73f54a616c506c3b49ca4c0315f0528f61b8897dc65c9cd6148af8f7a8`.

Rev6 closes the prior review's F2: the load-bearing new writes either have an explicit status/non-empty gate or are made fail-closed by the immediately following content-count and `cmp` gates; `gate-shell.txt`, `push-command.txt`, `act-cmd.txt`, complete `gate-dryrun.txt`, and `prepush-gate.txt` are required in the immediate and complete durable returns. Rev6 also improves F1 materially: it uniquely selects the executable Step 1 line, rejects deletion and duplication, extracts exactly one intended-looking push substring, and byte-compares that extraction to `push-command.txt`.

One load-bearing F1 defect remains. The extraction ends at the first `>` token. Shell redirections may appear between arguments and are removed before the program's argv is constructed. An added flag or second refspec after the stdout redirection therefore remains an argument to `git push`, but lies outside the extracted substring. The rev6 binder reports PASS on both unsafe executable forms, contradicting the plan's claim that any added flag or second refspec yields zero extracted lines. Exact-hash approval is withheld because this is the fast-forward-only, one-ref action boundary that the fresh gate exists to prove.

## F1 — substring extraction does not bind the complete executable command

The exact rev6 logic was reproduced against the approved artifact and six scratch-only mutations. `header_count` is the plan's `n`; `extract_count` is the required `act-cmd.txt` line count; `cmp_rc` is the binding comparison; PASS means all three rev6 conditions are green.

```text
approved                        header_count=1 extract_count=1 cmp_rc=0 gate=PASS
deleted                         header_count=0 extract_count=0 cmp_rc=1 gate=STOP
duplicated                      header_count=2 extract_count=2 cmp_rc=1 gate=STOP
sha_altered                     header_count=1 extract_count=1 cmp_rc=1 gate=STOP
force_before_origin             header_count=1 extract_count=0 cmp_rc=1 gate=STOP
force_after_stdout_redir        header_count=1 extract_count=1 cmp_rc=0 gate=PASS
second_ref_after_stdout_redir   header_count=1 extract_count=1 cmp_rc=0 gate=PASS
```

The two false-green mutations differ from Task 2 Step 1 only by inserting, respectively, `--force` or `refs/heads/other:refs/heads/other` between the stdout redirection and the stderr redirection. A no-network zsh function substituted for `git` independently reproduced the resulting argv:

```text
argc=4
<push>
<origin>
<bbf297e36a38a1fab8c2675f945098a0633f9f8b:refs/heads/main>
<--force>
```

and, for the second mutation, the fourth argument was `<refs/heads/other:refs/heads/other>`. Thus the actual commands are a forced push and a two-ref push even though rev6 records `act_line_count=1`, `act_cmd_bound=0`, and proceeds.

Required fold: bind the complete executable shell fragment, not a prefix ending at the first redirection. One sufficient shape is to select exactly one Step 1 line and require an exact fixed code span through the known stdout/stderr redirections and `|| p=$?`, then derive or compare the canonical no-redirection command only after the full span is proven. Whatever mechanism rev7 chooses, it must demonstrate in both target shells that deletion, duplication, SHA alteration, a flag before `origin`, a flag after either redirection, a second refspec before redirection, and a second refspec after either redirection all STOP. Preserve the literal 40-hex PIN and do not reintroduce a variable before the colon.

Evidence-accuracy correction in the same fold: the relay's raw hazard-regex claim is not verbatim reproducible as written. `rg -n '\$[A-Za-z_][A-Za-z_0-9]*:[A-Za-z]'` finds two explanatory quotations, plan lines 15 and 74; the old form's executable count is zero. Scope the reported count to executable content or report the two inert prose hits instead of claiming zero outside lineage.

## Checks that remain closed

- Exact identity: the live plan is byte-equal to `HEAD` at commit `036bd70026948d2221d198ac4b573ad5ccf61cb3`; SHA-256 is exactly `994fde73f54a616c506c3b49ca4c0315f0528f61b8897dc65c9cd6148af8f7a8`. The incoming relay SHA-256 is `65f098584c4e0eff3ba1f04c141dd899cf97aeb8e52a680bc4c09f46fec35833`; exact-file v2.9.2 lint is clean with freshness disabled.
- Current safe preflight: STOP-1 rc 0; origin main remains OLD `0db8fdd8424d27aad2c547614e9ebb95621a2794`; residue above PIN is nine commits after the rev6 filing; push and fetch URLs are exactly the authorized private repository; the resolved pre-push hook is not executable; visibility is `PRIVATE`.
- F2 closure: the revised fail-closed evidence production and durable return contract carry the execution shell, full command-log bytes, extracted command bytes, complete dry-run bytes, and final pre-push record in every outcome class.
- Literal behavior remains closed from the preceding review and is unchanged in rev6: the literal refspec has no zsh parameter expansion, the old variable-bearing executable form is absent, and the reviewed dry-run form names OLD-to-PIN on `main` without a ref update.
- Rev2-rev4 instruments remain unchanged: external evidence boundary, split byte inventories, exact symlink-target records, STOP-1/STOP-2, census 3/2, outcome classification, no-stop post-attempt evidence path, complete receipts in observed-publication classes, and computed verdict.
- Scope and holds remain exact: one intended origin `refs/heads/main` fast-forward to PIN; no force, other ref, retry under one token, branch, tag, PR, remote-CI citation, worktree byte, release, or R-4.52 decision.

## Acceptance status

1. HOLD — the literal intended action remains valid, but F1 still permits a materially different executable argv to pass its binding proof.
2. RED — the fresh gate can record a false-green `act_cmd_bound=0` for a forced or two-ref push.
3. GREEN unchanged — the census remains exact and no credential value is required in evidence.
4. GREEN — rev6 closes the prior evidence-write and durable-return finding.
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
- test-runtime-role-mismatch: yes — shell parsing makes post-redirection tokens part of argv although the binder excludes them
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: yes — substring binding leaves residual publication risk
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: none requested or claimed
- scan_presented_to_operator: no — this review routes the exact defect through the Pair Planner
- operator_reply_after_scan: none
- valid_waiver: no
WAIVED_RISK_ACCEPTANCE: none

## Next gate

File rev7 at a new digest folding F1 and the measurement wording correction while retaining rev6's F2 closure, the literal refspec, target-shell dry-run form, every rev2-rev4 instrument, one attempt per fresh token, and all downstream holds. Route those exact bytes back under a unique review id. Do not issue `intg-firstpush-impl-2` on rev6.

ACTIONS_GIT_REF: review-only inspection at main 036bd70026948d2221d198ac4b573ad5ccf61cb3; exact relay/plan identity, topology, endpoint, hook, visibility, remote head, and plan-surface measurements; scratch-only command-binder mutations under `/tmp/intg-firstpush-plan-review.uCL7Tw`; no-network shell argv probes with a local function substituted for `git`; daemon submission of this review only. No actual push, dry run, state-changing fetch, ref movement, branch, tag, product/test/workflow/plan byte, staging, commit, PR, remote CI, deployment, or release.
RELAY_LINT: incoming exact-file v2.9.2 lint clean with freshness disabled; outgoing draft/render require exact-file lint, daemon receipt, byte comparison, unique INDEX row, and engine verification; no implementation token may consume this must-revise review
FINAL_GIT_STATUS_SHORT: before this daemon filing, the intg plan/relay paths were clean and the shared worktree contained only the inherited S4/root state listed below; none was changed by this review
```text
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
```

Done: exact-hash rev6 PLAN review; prior F2 independently closed; command-binding false-greens reproduced with shell argv proof; one remaining F1 specified
Not done: no `intg-firstpush-impl-2`, actual push, dry run, state-changing fetch, ref movement, branch, tag, repository/product/test/workflow/plan byte, staging, commit, PR, remote CI, deployment, release, or downstream closure
Next requested action: intg.pair-planner — fold F1 into rev7, correct the raw-regex measurement wording, and request exact-hash review; do not dispatch rev6
