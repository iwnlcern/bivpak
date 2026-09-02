## PLAN-REVIEW artifact — MUST-REVISE exact revision 3 at 8f19819e: replacement assembly drops both uncommitted tranches; typed-only validation loses parser presence facts; FX-O tag counts contradict their grep

ROLE: Pair Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: must-revise
DISPATCH_ID: intg-substep2a-plan-review-3
PARENT_DISPATCH_ID: intg-substep2a-plan
IN_REPLY_TO: intg-substep2a/PLAN-pair-planner-20260901-230031.md
RELATED_CONTEXT: docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep2a-20260830.md; intg-substep2a/IMPL-pair-implementer-20260901-063948.md; intg-substep2a/SITREP-pair-planner-20260901-230224.md; sealed Addendum O at locked commit 40b4f7a3dbfc60e5ab742678bc4e77198845c243; master carry 224814
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — exact-hash plan correction and re-review are next; W-4 disposition, ASK-6 ruling, implementation, m-1 byte review, merge, push, publication, deployment, and release remain separately gated
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
PLAN_LOCK_ID: intg-substep2a-plan-20260830 @ sha256 8f19819edd1ea097e7b9ebd065d2f2f3260059dfb95438d8cf3a16b604deed04
REVIEWED_PLAN: docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep2a-20260830.md at commit 3dbbb54bb216d79e59b7b4a85ab7fad1943e710b, sha256 8f19819edd1ea097e7b9ebd065d2f2f3260059dfb95438d8cf3a16b604deed04
BASE: main@46df8f3c35981a4ae3f77cf3293a4b7212b4b996; review filed from main@3dbbb54bb216d79e59b7b4a85ab7fad1943e710b
BRANCH: intg/format-act at retained HEAD 9e6ebe8fca2454164051573323dd7adfa2901219; uncommitted tranche-1 diff remains exactly 72fd3dc604957e14e944b9f7418a64f723125d8b138909e8e0bd5b045e4b22cf over src/core/manifest/manifest.cpp and tests/test_manifest.cpp; no product byte or ref changed by this review
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: master.master-planner, master.master-reviewer, m-1.planner, m-1.implementer
SUBJECT: MUST-REVISE exact 8f19819e — F1 add exact staging and staged-tree proof after the soft reset; F2 preserve parser presence facts in the one inventory; F3 choose a non-contradictory FX-O tag grammar; sealed O, ASK-6 escalation, W-4 termination, and retained tranche-1 binding otherwise verified

## Verdict

MUST-REVISE at exact SHA-256 `8f19819edd1ea097e7b9ebd065d2f2f3260059dfb95438d8cf3a16b604deed04`.

Three mechanical blockers remain. F1 would produce the wrong replacement commit under the current retained index/worktree state. F2 makes the promised one-inventory/two-enforcement-points construction unable to express presence-sensitive parser clauses. F3 prescribes mutually impossible grep counts. No implementation token may parent to this review.

This is review-only. It authorizes no product edit, branch/ref movement, ASK-6 propagation, implementation, merge, push, publication, deployment, or release.

## Findings

### F1 — Critical — Task 3 Step 5 omits staging, so the prescribed replacement commit excludes tranche 1 and tranche 2

Plan line 113 says that after `git reset --soft 363d812`, `9e6ebe8`'s tree content stays in the index "together with both tranches," then prescribes one commit without any `git add`. That index claim is false for the retained state the plan binds.

Fresh evidence at `/Users/jack/Programming/bivpak-intg-format-act`:

```text
HEAD = 9e6ebe8fca2454164051573323dd7adfa2901219
git diff --cached --name-only = empty
git diff --name-only =
src/core/manifest/manifest.cpp
tests/test_manifest.cpp
git diff --name-only 363d812..9e6ebe8 =
src/core/manifest/manifest.cpp
src/core/manifest/manifest.hpp
tests/test_manifest.cpp
```

`reset --soft` moves HEAD while preserving index and worktree. The index after that reset would therefore contain only old `9e6ebe8` relative to `363d812`; retained uncommitted tranche 1 and future uncommitted tranche 2 remain unstaged. The prescribed commit recreates old Task 3 rather than the corrected replacement.

Required correction: make staging explicit and scope-safe after the reset, or prescribe an equivalent exact assembly. Before commit prove (a) `git diff --name-only` empty, (b) `git diff --cached --name-only` equals the exact Task-3 allowlist with ASK-6 paths only if ruled, and (c) the cached diff/tree contains both hash-bound tranche 1 and tranche 2. Keep the retention ref and four-commit postcondition.

### F2 — Important — the typed-only shared predicate loses required parser presence facts

Plan lines 69, 90-95, and 111 require landed G/H/N clauses, including `capture_mode` absence and `local_refs` presence behavior, in one predicate over typed `RepoEntry`, called after the parser builds the row. The retained parser proves those facts are not in `RepoEntry`:

- `capture_mode` is optional while parsing, then collapses via `value_or(CaptureMode::full)` at `manifest.cpp:1687`.
- `local_refs_present` is a separate raw-member bit at `manifest.cpp:1590-1592`; `RepoEntry.local_refs` cannot distinguish absent from present-empty.
- raw `sparse` is checked before construction, while `RepoEntry.sparse` is always `nullptr`.

A post-build `repo_row_violation(const RepoEntry&)` cannot enforce those parser-side presence clauses, while leaving them outside contradicts the claimed one inventory.

Required correction: define a shared validator input carrying normalized row plus required wire-presence facts, writer-derived and parser-observed, or explicitly narrow and justify the shared inventory against O-R4 without claiming clauses it cannot represent. Bind parser and writer twins to that exact input contract.

### F3 — Important — the FX-O tag grammar requires incompatible counts

Plan line 99 says each FX-O leg is tagged; lines 107 and 125 require `grep -c 'FX-O (b)' tests/test_manifest.cpp` = 7; line 109 says tests contain six FX-O tags total, and line 126 greps broader `FX-O (` as the six-leg census. Seven `(b)` tags alone make six total tags impossible.

Required correction: choose one unambiguous tag grammar and exact commands/results. For example, use one leg tag per logical leg plus seven differently named field-arm tags, or accept repeated `(b)` tags and derive six logical legs by a unique/sorted census. Preserve sealed O's six legs and nine named-mutant markers; do not alter O.

## Verified unaffected surfaces

- Incoming carrier exact-file lint is clean; root verification reports `ok:true`.
- Plan hashes to `8f19819e...` at commit `3dbbb54...`.
- Sealed O re-verifies: live post-stamp `0e990bac...`; blob at `40b4f7a3...` = locked `63c46631...`; O-R1 through O-R6 and FX-O were read whole.
- ASK-6 is real: external callers are exactly `src/core/pack/pack.cpp:765`, `tests/test_cli.cpp:192`, and `tests/test_open.cpp:131`; the plan correctly self-grants nothing.
- W-4 step (iii) matches master's order and step-(iv) SITREP is filed. This review does not adjudicate steps (v)-(vi).
- Retained tranche 1 is unchanged: HEAD `9e6ebe8...`, two tracked modified files, diff `72fd3dc6...`, file hashes `db50039e...` and `de98adc4...`.

## Escalation scan

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: no — review-only
- migration/backfill/destructive-write/canonical-data-repair: no — no product or canonical-data write
- money/inventory/orders/planning/accounting/trust-critical-state: no — no such runtime state
- AI-or-automation-acts-downstream: no — no downstream automation act
- worker/scheduler/queue/retry/async-side-effect: no — no runtime action
- cross-repo/service-contract/generated-schema/shared-API-event: yes — sealed PDC M/N/O govern the plan and ASK-6 crosses m-1's fence
- user-visible-control-with-materializer/downstream-consumer: yes — future archive bytes and pack error propagation are user-visible
- test-runtime-role-mismatch: yes — Task 4 two-platform verification remains closed
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: yes — ASK-6 and W-4 disposition remain open and the plan is must-revise
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: none — no downgrade or risk acceptance requested
- scan_presented_to_operator: no — not requested
- operator_reply_after_scan: none
- valid_waiver: no
WAIVED_RISK_ACCEPTANCE: none

## Required successor

Reissue the same plan identity with F1-F3 corrected, preserve sealed O citation and ASK-6/W-4 gates, and request a new exact-hash PLAN-REVIEW. No implementation token may issue from this must-revise review.

ACTIONS_GIT_REF: read-only review of plan commit 3dbbb54bb216d79e59b7b4a85ab7fad1943e710b at sha256 8f19819edd1ea097e7b9ebd065d2f2f3260059dfb95438d8cf3a16b604deed04; sealed O hashes, incoming carrier lint/root verification, retained product hashes, caller census, index/worktree state, and plan grep contradictions checked; daemon submission only; no product, plan, branch, worktree, ref, merge, push, publication, deployment, or release action claimed
RELAY_LINT: exact-file v2.9.2 lint is the daemon submission gate; rendered result and digest will be re-verified after filing
FINAL_GIT_STATUS_SHORT: none — scoped status for the intg root and plan path was empty before daemon submission; inherited s4 state exists outside this review scope and was untouched
