## PLAN-REVIEW — MUST REVISE exact rev3 aa21f0f9: the fresh gate and external-parent flow close, but symlink evidence is not byte-complete and publication can bypass the three-line receipt

ROLE: Pair Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: must-revise
DISPATCH_ID: intg-firstpush-plan-review-3
PARENT_DISPATCH_ID: intg-firstpush-plan-3
IN_REPLY_TO: intg-firstpush/PLAN-pair-planner-20260905-144350.md
RELATED_CONTEXT: intg-firstpush/PLAN-REVIEW-pair-implementer-20260905-143628.md; intg-firstpush/PLAN-pair-planner-20260905-092654.md; intg-firstpush/PLAN-REVIEW-pair-implementer-20260905-091850.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-firstpush-20260905.md; ../../../pdc/master/relays/r438-transcription-at-merged-bytes/PLAN-master-planner-20260905-082012.md; ../../../pdc/master/relays/publication-path-ruling/PLAN-operator-20260902-141706.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new human gate — the operator ruling and master's repaired route remain sufficient, but no `intg-firstpush-impl` token may issue until a rev4 folds F1-F2, receives a new exact digest, and is approved at those exact bytes; publication and release remain held
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
PLAN_LOCK_ID: intg-firstpush-plan-20260905 @ sha256 aa21f0f9a0929887a26de87e471185723e2427ba5dd17714064e83a09fc578a6
TARGET_RELAY_SHA256: 65e266843bc89776780cdc6c428b839b5f4f8a77a581987ce434030a991dc8e9
TARGET_PLAN_SHA256: aa21f0f9a0929887a26de87e471185723e2427ba5dd17714064e83a09fc578a6
TARGET_PLAN_COMMIT: 33565f0dc667522d0ce46fbe163f0bd463030835
REVIEWED_PLAN: docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-firstpush-20260905.md at commit 33565f0dc667522d0ce46fbe163f0bd463030835, sha256 aa21f0f9a0929887a26de87e471185723e2427ba5dd17714064e83a09fc578a6
BASE: main@33565f0dc667522d0ce46fbe163f0bd463030835; publication pin bbf297e36a38a1fab8c2675f945098a0633f9f8b; origin refs/heads/main observed read-only at 0db8fdd8424d27aad2c547614e9ebb95621a2794
BRANCH: main@33565f0dc667522d0ce46fbe163f0bd463030835 — review-only; no push, state-changing fetch, ref, branch, tag, worktree byte, staging, commit, PR, remote-CI, deployment, release, or remote write
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: master.master-planner, master.master-reviewer, operator, m-3.planner, m-3.implementer, m-4.planner
SUBJECT: MUST REVISE exact rev3 aa21f0f9 — retain the now-complete fresh gate, pre-creation external-parent check, split regular-file inventory, explicit class, and narrow fetch; hash exact symlink-target bytes with checked stages and guarantee the complete three-line receipt after every observed publication

## Verdict

MUST REVISE exact SHA-256 `aa21f0f9a0929887a26de87e471185723e2427ba5dd17714064e83a09fc578a6`.

Revision 3 closes prior F1 and F4: the effective endpoints, resolved hook, visibility, STOP-1, and STOP-2 are in the fresh gate immediately before the push; the temporary parent is rejected before `mktemp`. Its separated regular-file discovery, ordering, hashing, and count check also close that part of prior F2, and the outcome class is now assigned and written.

Two exact command/control-flow defects remain on the irreversible path.

## F1 — the symlink inventory is neither byte-complete nor fail-closed

Task 1 Step 0 and Task 2 Step 3 use `t=$(readlink -- "$1")`. POSIX shell command substitution removes trailing newline bytes. In an external scratch discriminator, links targeting the distinct legal byte strings `target` and `target\n` both yielded `shell_length=6` and the identical digest `34a04005bcaf206eec990bd9637d9fdb6725e0a0c0d4aebf003f17f4c956eb5c`. The claimed hash of the link's `readlink` bytes is therefore not a hash of those exact bytes.

The nested `printf | shasum | cut` pipeline also has no checked component status. The independent discriminator `digest=$(printf x | false | cut -c1-64)` returned rc 0 with an empty digest. In the plan's child shell, an analogous hashing-stage failure can still print a line and return success, so the outer checked `xargs` status is insufficient. The final `sha<TAB>path<NL>` form is also ambiguous for legal newline-bearing pathnames, and there is no symlink discovered-count versus successfully encoded-count assertion.

Required fold: preserve the raw `readlink` output without command substitution's trailing-newline deletion; check discovery, ordering, target extraction, hashing, and serialization failures independently; use a NUL-safe or otherwise length-delimited unambiguous record for both target bytes and link path; and compare the discovered symlink count to the successfully hashed/encoded count before accepting either inventory.

## F2 — an observed publication can bypass the required receipt, and receipt (i) copying is unchecked

Task 2 Step 2 uses `[ "$o" -ne 0 ] || cp ... receipt-i.txt` without capturing or testing `cp`'s status. The plan explicitly uses manual status capture rather than shell fail-fast. An external discriminator with a missing source showed the following command still executed after `cp` failed. Class `c` then branches directly to a return that expressly omits receipts (ii) and (iii), even though its definition says the publication happened. This contradicts the plan Goal, Task 3, and acceptance criteria requiring the complete three-line receipt for a remote at the pin.

The same sequencing can omit the safe receipt after class `a` or `c` if the unconditional post-act boundary proof encounters an evidence-command failure and STOPs before Task 3. Once the remote is observed at the pin, evidence defects must not suppress the non-push receipt measurements. They must be recorded and returned alongside the receipt; the push must never be retried.

Required fold: materialize receipt (i) directly from the successful outcome probe or capture and require the copy status; accumulate rather than erase any evidence/boundary finding; whenever the outcome probe observes `remote_after=$PIN` (classes `a` and `c`), execute the safe receipt sequence (i), the one-ref `--no-tags` fetch and receipt (ii), and receipt (iii) before returning. Class `c` remains a STOP/finding after that receipt, and no class permits a second push.

## Independent evidence

- Incoming carrier SHA-256 `65e266843bc89776780cdc6c428b839b5f4f8a77a581987ce434030a991dc8e9`; exact-file v2.9.2 lint clean with freshness disabled.
- Live and `HEAD` plan bytes both SHA-256 `aa21f0f9a0929887a26de87e471185723e2427ba5dd17714064e83a09fc578a6` at `33565f0dc667522d0ce46fbe163f0bd463030835`; carrier bytes also match `HEAD`.
- Current read-only preflight: exactly one intended effective push URL; visibility `PRIVATE`; remote head `0db8fdd8424d27aad2c547614e9ebb95621a2794`; pin-to-main and remote-to-pin ancestry rcs 0; 814 remote-to-pin commits; four docs-lane commits above the pin.
- Independent full census at the pin reproduced the exact 3-line tree arm and 2-path history arm with 0 history stderr bytes.
- No executable hook exists at the current resolved pre-push path.
- External scratch probes reproduced the trailing-newline target collision, the masked nested-pipeline failure, and continuation after a failed receipt copy. The pre-parent guard, split regular-file stage checks, fresh gate composition, and class assignment were separately inspected and are not reopened here.
- No push or state-changing fetch ran. No remote/local ref, branch, tag, repository byte, index entry, PR, remote-CI run, deployment, or release changed.

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: yes — publication and credential-shape census cross a trust boundary
- migration/backfill/destructive-write/canonical-data-repair: no
- money/inventory/orders/planning/accounting/trust-critical-state: yes — the one-shot remote ref and receipt are trust-critical
- AI-or-automation-acts-downstream: yes — exact-hash approval would permit a publication token
- worker/scheduler/queue/retry/async-side-effect: yes — ambiguous outcome and no-retry handling must preserve post-publication evidence
- cross-repo/service-contract/generated-schema/shared-API-event: yes — PDC authority governs the Bivpak act
- user-visible-control-with-materializer/downstream-consumer: no
- test-runtime-role-mismatch: no
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: yes — exact-byte boundary proof and full post-publication receipt remain incomplete
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER: none
WAIVED_RISK_ACCEPTANCE: none

## Next gate

File rev4 at a new digest folding F1-F2 while retaining the exact authorization, pin, single fast-forward refspec, one attempt, fresh gate, census, and narrow receipt fetch. Route those exact bytes back for review. Nothing is pushed before exact-hash approval and a fresh addressed `intg-firstpush-impl` token.

ACTIONS_GIT_REF: review-only inspection at main 33565f0; exact relay/plan and authority pins; current remote URL/visibility/head/ancestry; full census; symlink-byte, nested-pipeline, and receipt-copy discriminators in external scratch; daemon submission of this review only; no push, state-changing fetch, ref, branch, tag, repository/product/test/workflow/plan byte, staging, commit, PR, remote CI, deployment, or release
RELAY_LINT: incoming exact-file v2.9.2 clean with freshness disabled; outgoing draft/render require exact-file lint, daemon receipt, unique INDEX row, and engine verification; no root-wide green claim
FINAL_GIT_STATUS_SHORT: inherited shared-root state only before submission — modified `.relays/s4/INDEX.md` and `.relays/s4/SEATS.md`; untracked S4 files, the S4 migration doc, and `relay-draft-intg-task4-stop.md`; preserved outside this review

Done: exact-hash rev3 PLAN review; prior folds and current command/control flow independently checked; two remaining defects specified
Not done: no implementation token, push, state-changing fetch, ref move, branch, tag, repository byte, staging, commit, PR, remote CI, deployment, release, or downstream closure
Next requested action: intg.pair-planner — fold F1-F2 into rev4 at a new digest and request exact-hash review; do not issue `intg-firstpush-impl` on rev3
