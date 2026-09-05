## PLAN-REVIEW — MUST REVISE exact rev2 69447b2a: the four concepts are present, but the fresh gate, inventory, outcome record, and external-home flow remain non-executable or incomplete

ROLE: Pair Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: must-revise
DISPATCH_ID: intg-firstpush-plan-review-2
PARENT_DISPATCH_ID: intg-firstpush-plan-2
IN_REPLY_TO: intg-firstpush/PLAN-pair-planner-20260905-092654.md
RELATED_CONTEXT: intg-firstpush/PLAN-REVIEW-pair-implementer-20260905-091850.md; intg-firstpush/PLAN-pair-planner-20260905-084607.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-firstpush-20260905.md; ../../../pdc/master/relays/r438-transcription-at-merged-bytes/PLAN-master-planner-20260905-082012.md; ../../../pdc/master/relays/publication-path-ruling/PLAN-operator-20260902-141706.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new human gate — the operator ruling and master's repaired route remain sufficient, but no `intg-firstpush-impl` token may issue until a rev3 folds F1-F4, receives a new exact digest, and is approved at those exact bytes; publication and release remain held
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
PLAN_LOCK_ID: intg-firstpush-plan-20260905 @ sha256 69447b2a4e18eeacce492c085686ae2d5378f5988e041d23ebcb7d3a31eefc41
TARGET_RELAY_SHA256: 931ead60d13818fa0fb5afb0fda6807125e98966c7437b4bb0b6e5304bc0e10a
TARGET_PLAN_SHA256: 69447b2a4e18eeacce492c085686ae2d5378f5988e041d23ebcb7d3a31eefc41
TARGET_PLAN_COMMIT: e842e193004cc29ccbb93aad6e788f59086b09a7
REVIEWED_PLAN: docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-firstpush-20260905.md at commit e842e193004cc29ccbb93aad6e788f59086b09a7, sha256 69447b2a4e18eeacce492c085686ae2d5378f5988e041d23ebcb7d3a31eefc41
BASE: main@e842e193004cc29ccbb93aad6e788f59086b09a7; publication pin bbf297e36a38a1fab8c2675f945098a0633f9f8b; origin refs/heads/main observed read-only at 0db8fdd8424d27aad2c547614e9ebb95621a2794
BRANCH: main@e842e193004cc29ccbb93aad6e788f59086b09a7 — review-only; no push, state-changing fetch, ref, branch, tag, worktree byte, staging, commit, PR, remote-CI, deployment, release, or remote write
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: master.master-planner, master.master-reviewer, operator, m-3.planner, m-3.implementer, m-4.planner
SUBJECT: MUST REVISE exact rev2 69447b2a — retain the effective URL, outcome probe, content inventory, and narrow-fetch direction, but put endpoint/hook checks in the fresh gate, make every inventory producer fail closed and hash symlink targets, materialize class/receipt evidence after every push rc, and prove the evidence base external before mkdir

## Verdict

MUST REVISE exact SHA-256 `69447b2a4e18eeacce492c085686ae2d5378f5988e041d23ebcb7d3a31eefc41`.

Revision 2 adopts all four review directions in substance. The exact push URL list is measured, a post-attempt remote probe is specified, regular-file hashing replaces status-label inference, and receipt fetch is narrowed to one ref with `--no-tags`. The authority, pinned refspec, one-attempt rule, STOP-1/STOP-2, census, three-line receipt, and downstream holds remain correct.

The exact commands still do not prove the strengthened claims. Four bounded folds are required.

## F1 — endpoint and hook checks are still absent from the fresh gate

Step 0 at plan line 31 measures the effective push URL and hook path. Step 4 at line 35 still concatenates only STOP-1, STOP-2, and the census summary, and only Steps 1-2 are rerun after five minutes. The slow history census and other commands intervene before the line-39 push. A changed `pushurl`, URL rewrite, or executable hook after Step 0 would therefore escape the final gate even though the prior review explicitly required the effective URL in that fresh record.

Required fold: immediately before the push, re-measure and compare the complete effective push URL set, fetch URL, resolved hook path/executable state, visibility, STOP-1, and STOP-2, then write their recorded values and statuses into `prepush-gate.txt`. Perform no command between that complete fresh gate and the one push attempt.

## F2 — the byte inventory masks producer failures and does not bind symlink targets

The regular-file commands at lines 31 and 41 are pipelines without `pipefail`: `find ... | sort -z | xargs ... || i=$?`. Both bash and zsh returned rc 0 in the independent discriminator `false | sort -z | xargs -0 shasum -a 256`; an upstream `find` or `sort` failure can therefore yield an incomplete inventory accepted as successful. The symlink commands capture no producer status at all.

The symlink inventory records names only. In an external scratch probe, retargeting one link from `target-one` to `target-two` left the before/after name files byte-equal and `diff` returned 0. Acceptance 5's byte-identical claim is therefore false for symlinks. The newline-delimited `-print` form is also not names-safe.

Required fold: split discovery, ordering, and hashing into recorded intermediate files with each command's status checked independently, in a form portable to the required bash and zsh hosts. Use NUL-safe path transport. Record a digest of each symlink's `readlink` bytes together with its path, not merely the symlink name, and compare the complete regular-file and symlink-target inventories on every outcome.

## F3 — the outcome class and failure receipt promised by Step 4 are never created

Line 40 appends `push_rc`, `outcome_probe_rc`, and `remote_after`, then describes classes (a)-(e) only in prose. No assignment or command appends the promised class letter to `push-rc.txt`, although line 48 requires it verbatim. In class (c), prose says the outcome is recorded as receipt (i), but Task 3 is not entered and no command creates `receipt-i.txt`; only `push-outcome-ls-remote.txt` exists.

The same passage writes STOP branches before saying Step 3 must run in every class, leaving immediate-return versus deferred-return control flow implicit on the irreversible path.

Required fold: assign exactly one recorded class after the outcome probe, write it explicitly, materialize receipt (i) from the successful probe whenever observable, run the post-act boundary proof unconditionally, and only then branch to the class-specific return or success receipt. Preserve one attempt and no retry in all classes.

## F4 — the external-home check happens after an in-repo directory may be created

Line 31 first runs `mktemp -d "${TMPDIR:-/tmp}/..."` and only afterward canonicalizes and rejects an in-checkout result. With an in-repo `TMPDIR`, the prohibited directory has already been created before the STOP and no plan command removes it. This contradicts `Files: none in the checkout`, the no-worktree-edit boundary, and the claimed fail-closed external-home fold.

Required fold: canonicalize and reject the candidate temporary parent before `mktemp`, or select a fixed external parent and verify that parent before creation; then canonicalize the created directory as a second guard. The STOP path must not create anything inside the checkout.

## Independent evidence

- Incoming carrier SHA-256 `931ead60d13818fa0fb5afb0fda6807125e98966c7437b4bb0b6e5304bc0e10a`; exact-file v2.9.2 lint clean with freshness disabled.
- Live and `HEAD` plan bytes both SHA-256 `69447b2a4e18eeacce492c085686ae2d5378f5988e041d23ebcb7d3a31eefc41` at `e842e193004cc29ccbb93aad6e788f59086b09a7`.
- Current read-only preflight: exactly one intended effective push URL; visibility `PRIVATE`; remote head `0db8fdd8424d27aad2c547614e9ebb95621a2794`; pin-to-main and remote-to-pin ancestry rcs 0; 814 remote-to-pin commits; three docs-lane commits above the pin.
- Independent census at the pin: tree arm 3 lines, history arm 2 paths, history stderr 0 bytes; both exact expected sets reproduced.
- `git rev-parse --git-path hooks/pre-push` honors absolute and relative `core.hooksPath` overrides; no executable hook exists at the current resolved path.
- The narrowed `--no-tags` one-ref fetch refspec passed `git fetch --dry-run --no-write-fetch-head`; no state-changing fetch ran.
- No push ran. No remote/local ref, branch, tag, repository byte, index entry, PR, remote-CI run, deployment, or release changed.

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: yes — publication and credential-shape census cross a trust boundary
- migration/backfill/destructive-write/canonical-data-repair: no
- money/inventory/orders/planning/accounting/trust-critical-state: yes — the one-shot remote ref and receipt are trust-critical
- AI-or-automation-acts-downstream: yes — exact-hash approval would permit a publication token
- worker/scheduler/queue/retry/async-side-effect: yes — outcome ambiguity and no-retry flow must be executable
- cross-repo/service-contract/generated-schema/shared-API-event: yes — PDC authority governs the Bivpak act
- user-visible-control-with-materializer/downstream-consumer: no
- test-runtime-role-mismatch: no
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: yes — fresh-target and byte-boundary proof remain incomplete
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER: none
WAIVED_RISK_ACCEPTANCE: none

## Next gate

File rev3 at a new digest folding F1-F4 while retaining the same authorization, pin, single fast-forward refspec, one attempt, census, and receipt. Route those exact bytes back for review. Nothing is pushed before exact-hash approval and a fresh addressed `intg-firstpush-impl` token.

ACTIONS_GIT_REF: review-only inspection at main e842e19; exact relay/plan and authority pins; current remote URL/visibility/head/ancestry; full census; shell failure and symlink-target discriminators in external scratch; one-ref fetch dry-run with no FETCH_HEAD write; daemon submission of this review only; no push, state-changing fetch, ref, branch, tag, repository/product/test/workflow/plan byte, staging, commit, PR, remote CI, deployment, or release
RELAY_LINT: incoming exact-file v2.9.2 clean with freshness disabled; outgoing draft/render require exact-file lint, daemon receipt, unique INDEX row, and engine verification; no root-wide green claim
FINAL_GIT_STATUS_SHORT: inherited shared-root state only before submission — modified `.relays/s4/INDEX.md` and `.relays/s4/SEATS.md`; untracked S4 files, the S4 migration doc, and `relay-draft-intg-task4-stop.md`; preserved outside this review

Done: exact-hash rev2 PLAN review; substantive folds and unchanged route independently checked; four remaining execution gaps specified
Not done: no implementation token, push, state-changing fetch, ref move, branch, tag, repository byte, staging, commit, PR, remote CI, deployment, release, or downstream closure
Next requested action: intg.pair-planner — fold F1-F4 into rev3 at a new digest and request exact-hash review; do not issue `intg-firstpush-impl` on rev2
