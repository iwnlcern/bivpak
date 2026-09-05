## PLAN-REVIEW — MUST REVISE exact rev1 3cb78373: bind the effective push endpoint, measure ambiguous outcomes, prove the no-byte boundary, and narrow the receipt fetch

ROLE: Pair Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: must-revise
DISPATCH_ID: intg-firstpush-plan-review-1
PARENT_DISPATCH_ID: intg-firstpush-plan
IN_REPLY_TO: intg-firstpush/PLAN-pair-planner-20260905-084607.md
RELATED_CONTEXT: ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-firstpush-20260905.md; ../../../pdc/master/relays/r438-transcription-at-merged-bytes/PLAN-master-planner-20260905-082012.md; ../../../pdc/master/relays/publication-path-ruling/PLAN-operator-20260902-141706.md; ../../../pdc/master/relays/r438-transcription-at-merged-bytes/DESIGN-planner-20260905-074107.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new human gate — the operator ruling and master's repaired route stand, but no `intg-firstpush-impl` token may issue until a successor plan folds F1-F4, receives a new exact digest, and is approved at those exact bytes; every publication and release hold remains
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
PLAN_LOCK_ID: intg-firstpush-plan-20260905 @ sha256 3cb78373f44bdc22488c0ff2ff6ec8ce7b06c01fc5631b573d5487ab5c379de9
TARGET_RELAY_SHA256: 1cb53e69a0db4d3db8211ade2fb05d3ad58081fa59fcf70520f2e1cd6a35521a
TARGET_PLAN_SHA256: 3cb78373f44bdc22488c0ff2ff6ec8ce7b06c01fc5631b573d5487ab5c379de9
TARGET_PLAN_COMMIT: b7cf25e4b24ebf787d8c0093cc6c64d296fc8f33
REVIEWED_PLAN: docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-firstpush-20260905.md at commit b7cf25e4b24ebf787d8c0093cc6c64d296fc8f33, sha256 3cb78373f44bdc22488c0ff2ff6ec8ce7b06c01fc5631b573d5487ab5c379de9
BASE: main@b7cf25e4b24ebf787d8c0093cc6c64d296fc8f33; publication pin bbf297e36a38a1fab8c2675f945098a0633f9f8b; origin refs/heads/main observed read-only at 0db8fdd8424d27aad2c547614e9ebb95621a2794
BRANCH: main@b7cf25e4b24ebf787d8c0093cc6c64d296fc8f33 — review-only; no push, fetch, ref, branch, tag, worktree byte, staging, commit, PR, remote-CI, deployment, release, or remote write
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: master.master-planner, master.master-reviewer, operator, m-3.planner, m-3.implementer, m-4.planner
SUBJECT: MUST REVISE exact rev1 3cb78373 — authority, pin, STOP-1/STOP-2, and the exact 3/2 census reproduce; bind every effective push URL, measure outcome after any push rc, prove the no-byte boundary and external evidence home, and narrow the receipt fetch to origin/main with no tags

## Verdict

MUST REVISE exact SHA-256 `3cb78373f44bdc22488c0ff2ff6ec8ce7b06c01fc5631b573d5487ab5c379de9`.

The governing authority and central act are sound. The operator carrier re-hashes to `b30cff98372867bd67a96eec6fadf7b73add0854b1fc118a9f6eb85663297e30`; master's repaired route re-hashes to `0fbd4fe64314040de498f8b56f091e82873515f9abd1f78f1bbddfe83967c320`; their literal routing reaches this pair. The plan correctly uses the pinned SHA refspec, fast-forward-only and one-attempt bounds, pin-is-ancestor-of-`main`, the census of record, and all downstream holds.

Four local execution/evidence gaps remain. They do not reopen the ruling, route, accepted count-gate repair, or census definition.

## F1 — the preflight checks the fetch URL, not every effective push URL

Plan line 31 records `git remote get-url origin`, but line 39 runs `git push origin ...`. Git may resolve those to different endpoints through `remote.origin.pushurl` or `url.*.pushInsteadOf`; multiple push URLs are possible. The exact plan therefore does not bind the irreversible act to only the authorized endpoint.

Current contrast is green but not a durable guard: fetch and effective push URLs both return `https://github.com/iwnlcern/bivpak.git`, with zero configured push URLs and zero URL rewrites.

Required fold: record the status and complete output of `git remote get-url --push --all origin`; require exactly one line equal to the authorized URL; include it in the fresh gate and IMPL return. Keep the fetch URL check separate.

## F2 — a nonzero push skips outcome measurement

Line 39 makes nonzero `git push` an immediate STOP before Task 3. A transport may fail after the server accepts the ref update, so rc alone cannot prove whether the remote moved. The token remains consumed and retry remains prohibited, but the current flow can omit receipt (i).

Required fold: after the sole push attempt, always record `push_rc`, always run and record the read-only `ls-remote` outcome probe, and always run the post-act worktree boundary measurement. Never retry. Nonzero remains a STOP, but report whether the remote stayed old, reached the pin despite client failure, or could not be observed. Continue the success receipt only when rc is zero and receipt (i) reads the pin.

## F3 — status labels do not prove byte-identical worktree state

Lines 20, 40, and acceptance 5 equate equal `git status --porcelain` text with byte equality. This shared checkout already has modified and untracked paths. A dirty tracked file can change and remain `M`; an untracked file can change and remain `??`; collapsed untracked directories can conceal descendants. Equal status labels therefore do not prove the asserted byte boundary.

Line 31 also uses `${TMPDIR:-/tmp}` without proving canonical `$EVID` is outside the canonical repository root. A caller-supplied in-repo or ignored `TMPDIR` would violate the plan's own boundary without necessarily changing status output.

Required fold: fail closed unless the canonical evidence path is outside the canonical checkout root. Retain status snapshots, but add a content-complete, names-safe pre/post digest inventory for worktree files outside `.git`, containing hashes rather than values, and compare it on every push outcome. Alternatively narrow the acceptance claim if upstream authorizes weaker evidence; the current no-byte promise calls for the byte-complete proof.

## F4 — the receipt fetch is broader than its one-ref account

Line 45 runs `git fetch origin`, while line 20 says fetch moves only `refs/remotes/origin/main`. The live fetch refspec is `+refs/heads/*:refs/remotes/origin/*`, and the remote exposes 25 heads; a broad fetch may update other remote-tracking refs and auto-follow tags.

Required fold: fetch only `refs/heads/main` into `refs/remotes/origin/main` with `--no-tags`, capturing status and stderr, before measuring `main..origin/main`; or fetch only that source into `FETCH_HEAD` with `--no-tags` and measure the recorded object. Do not use the wildcard-configured fetch.

## Independent evidence

- Incoming carrier SHA-256 `1cb53e69a0db4d3db8211ade2fb05d3ad58081fa59fcf70520f2e1cd6a35521a`; exact-file v2.9.2 lint clean with freshness disabled.
- Live and `HEAD` plan bytes both SHA-256 `3cb78373f44bdc22488c0ff2ff6ec8ce7b06c01fc5631b573d5487ab5c379de9` at `b7cf25e4b24ebf787d8c0093cc6c64d296fc8f33`.
- Current read-only preflight: intended fetch/effective-push URL, visibility `PRIVATE`, remote `0db8fdd8424d27aad2c547614e9ebb95621a2794`, pin exists, pin-to-main ancestry rc 0, remote-to-pin ancestry rc 0, 814 remote-to-pin commits, and two unpublished commits above the pin.
- Independent census at the pin: tree 3 lines/diff rc 0; history 2 paths/diff rc 0; history stderr 0 bytes. Exact expectations reproduced.
- No active pre-push hook, custom push URL, or URL rewrite exists now; those live facts do not replace fresh plan guards.
- No push or fetch ran. No remote or local ref, branch, tag, worktree byte, index entry, PR, remote-CI run, deployment, or release changed.

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: yes — publication and credential-shape census cross a trust boundary
- migration/backfill/destructive-write/canonical-data-repair: no
- money/inventory/orders/planning/accounting/trust-critical-state: yes — the one-shot remote ref and receipt are trust-critical
- AI-or-automation-acts-downstream: yes — approval would permit a publication token
- worker/scheduler/queue/retry/async-side-effect: yes — the network write can succeed with ambiguous client rc and must never be retried
- cross-repo/service-contract/generated-schema/shared-API-event: yes — PDC authority governs the Bivpak act
- user-visible-control-with-materializer/downstream-consumer: no
- test-runtime-role-mismatch: no
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: yes — endpoint, byte-boundary, and outcome proof are incomplete
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER: none
WAIVED_RISK_ACCEPTANCE: none

## Next gate

File a successor at a new digest folding F1-F4 without widening the act: the same pinned fast-forward refspec, one attempt, exact census, and receipt; one effective destination; outcome measurement after any rc; verified external evidence; byte-complete boundary; and single-ref no-tags fetch. Route those exact bytes back for review. Nothing is pushed before exact-hash approval and a fresh addressed `intg-firstpush-impl` token.

ACTIONS_GIT_REF: review-only inspection of exact plan/carrier, sibling PDC authority, current remote configuration/visibility/head/ancestry, and the census in external scratch; daemon submission of this review only; no push, fetch, ref, branch, tag, product/test/workflow/plan byte, staging, commit, PR, remote-CI, deployment, or release
RELAY_LINT: incoming exact-file v2.9.2 clean with freshness disabled; outgoing draft/render require exact-file lint, daemon receipt, unique INDEX row, and engine verification; no root-wide green claim
FINAL_GIT_STATUS_SHORT: inherited shared-root state only before submission — modified `.relays/s4/INDEX.md` and `.relays/s4/SEATS.md`; untracked S4 files, the S4 migration doc, and `relay-draft-intg-task4-stop.md`; preserved outside this review

Done: exact-hash rev1 PLAN review; authority, pins, remote state, ancestry, and census independently reproduced; four gaps specified
Not done: no implementation token, push, fetch, ref move, branch, tag, worktree byte, staging, commit, PR, remote CI, deployment, release, or downstream closure
Next requested action: intg.pair-planner — fold F1-F4, file the successor at a new digest, and request exact-hash review; do not issue `intg-firstpush-impl` on rev1
