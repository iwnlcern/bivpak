## PLAN-REVIEW artifact — MUST REVISE revision 11 at 0929edb3: the empty-remotes correction is right, but the exact plan still contains a remotes refusal obligation, a false pre-STOP branch checkpoint, and a W-5 gate sequence contradicted by the effective notice

ROLE: Pair Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: must-revise
DISPATCH_ID: intg-substep2a-plan
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: intg-substep2a/PLAN-pair-planner-20260902-064236.md
RELATED_CONTEXT: intg-substep2a/IMPL-pair-implementer-20260902-063445.md; intg-substep2a/PLAN-REVIEW-pair-implementer-20260902-054431.md; ../../../pdc/master/relays/intg-substep2a-format-act/PLAN-master-planner-20260902-035616.md; ../../../pdc/master/relays/intg-substep2a-format-act/PLAN-REVIEW-master-reviewer-20260902-033153.md; intg-substep2a/SITREP-pair-planner-20260902-064627.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — no fresh implementation token may issue until the three exact-artifact contradictions below are folded into a successor plan, that successor receives a new exact digest, and the Pair Implementer approves those exact bytes; W-5 itself is already effective at its pinned registry row and is not reopened by this review
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
PLAN_LOCK_ID: intg-substep2a-plan-20260830 @ sha256 0929edb3d48afee54c6f95a96ee1a09dca11deabdda7e383edcd8754d97f7a16
TARGET_RELAY_SHA256: ebe776a8efaa1b941f1f4a262c95112202202ecec7c07dec51be0848997eed94
TARGET_PLAN_SHA256: 0929edb3d48afee54c6f95a96ee1a09dca11deabdda7e383edcd8754d97f7a16
TARGET_PLAN_COMMIT: 3eaebfc3d855d4f7a0c07e419c6d4ce5d5addbcf
BASE: main@46df8f3c35981a4ae3f77cf3293a4b7212b4b996; exact review filed from the docs lane after plan commit 3eaebfc3
BRANCH: intg/format-act@9e6ebe8fca2454164051573323dd7adfa2901219; retained-task3-9e6ebe8 resolves to the same sha; index clean; exactly six Task-3 paths unstaged; frozen patch sha256 fbf77f3d52b4a229d2309f45c39a62658351049db36276c6703688bd0dd88db7; NOT a candidate
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: master.master-planner, master.master-reviewer, m-1.planner, m-1.implementer, m-3.planner, m-3.implementer
SUBJECT: MUST REVISE exact 0929edb3 — retain the sound removal of the unsupported non-empty clauses, but remove the surviving remotes refusal-arm instruction, encode the actual six-file resume checkpoint, and update W-5 from proposed/awaiting to effective/replacement-filed before requesting exact-hash re-review

## Verdict

MUST REVISE exact SHA-256 `0929edb3d48afee54c6f95a96ee1a09dca11deabdda7e383edcd8754d97f7a16`.

The central correction is approved in substance: `required_string()` checks presence and string type only, `parse_remotes()` does not reject empty strings, sealed §2.3 adds no non-empty rule, and retaining a writer-only non-empty refusal would violate O-R4. Removing the two clauses and their two negative arms, without changing parser bytes, is the correct resolution.

The exact artifact is not yet executable because three current normative passages contradict that resolution or the governed continuation state.

## F1 — a remotes refusal-arm obligation survives the struck inventory row

At current plan line 260, the mandatory `FX-O-INV` population still ends with:

```text
Plus one arm per remaining typed-expressible predicate ... the eligibility relation;
the remotes and forced_payload row forms; the NonCarriedRefsNote clauses
```

After revision 11, there is no typed remotes row-form predicate left: missing/non-string members and non-object elements are parser-local, while empty `name`/`url` strings are explicitly accepted and excluded from table A at lines 144-153. The remaining phrase therefore still orders an implementer to retain or invent a remotes refusal arm and conflicts with the new corollary.

Required fold: remove `the remotes and` from the current mandatory-arm population, or name a different remotes predicate together with its cited executable parser rejection site. Under the evidence on this face, removal is the supported correction. Re-scan all current normative arm/census prose for the struck population; historical revision prose may remain clearly historical.

## F2 — the plan's branch checkpoint and execution steps still require the pre-STOP two-file state

Current plan line 43 says, as a present fact “re-verified at this revision,” that exactly two paths are unstaged and the diff hashes to `72fd3dc6…`. Task 3 Step 0 at line 249 also requires that same two-path state and says any mismatch is a STOP. Those statements are false at revision 11 and make the requested resume impossible: the actual governed state is HEAD/tag `9e6ebe8`, empty index, six unstaged Task-3 paths, and diff SHA-256 `fbf77f3d…`. The incoming relay and `064627` SITREP acknowledge that actual state, but the executable artifact does not.

Required fold:

1. Replace the “current state” statement with the exact frozen six-path checkpoint and full `fbf77f3d52b4a229d2309f45c39a62658351049db36276c6703688bd0dd88db7` digest, while retaining `72fd3dc6…` only as the already-preserved tranche-1 evidence patch.
2. Add an explicit revision-11 resume checkpoint inside the plan: after a fresh token, verify HEAD/tag, empty index, exact six paths, and `fbf77f3d…`; remove the two clauses plus two arms; re-derive the table counts; then continue Steps 4 through 6. Mark or qualify the original Step-0/RED/implementation instructions as already executed evidence, not instructions to recreate the impossible two-file state.
3. Keep “no byte moves before the fresh token” literal. This review does not authorize the mechanical correction.

## F3 — W-5 is regressed from effective to proposed/awaiting

Current plan line 318 says W-5 “is PROPOSED” and awaits the operator disposition, Master Reviewer concurrence, and effectiveness notice. Line 321 repeats those already-completed acts as future prerequisites after this review. That contradicts:

- the addressed W-5 effectiveness notice `035616`, which binds registry `16e56c7b… @ b30a54c…`, freezes this plan identity/selector, and says a preserving successor replaces the prior entry after its new root-mode measurement is filed;
- Master Reviewer concurrence `033153`, which states `W5_EFFECTIVE: yes`; and
- the revision-11 filing/SITREP `064627`, which records the new root-mode measurement for this exact plan carrier.

It also contradicts the incoming revision-11 relay's own `HUMAN_GATE_REQUIRED: no` statement and promise that a fresh token follows only after exact-hash approval.

Required fold: state W-5 as already effective at the exact pinned registry row, record revision 11's filed replacement measurement and preserved selector/eligible row, and describe the remaining token chain accurately: successor exact-hash plan review, then a fresh addressed token. Preserve the rule that any selector/eligible-row change or fourth lock terminates coverage and requires a fresh scan/decision; do not silently request or imply a second operator grant for this identity-preserving replacement.

## Exact review evidence

- Incoming relay SHA-256: `ebe776a8efaa1b941f1f4a262c95112202202ecec7c07dec51be0848997eed94`; exact-file lint clean.
- Reviewed plan: commit `3eaebfc3d855d4f7a0c07e419c6d4ce5d5addbcf`, SHA-256 `0929edb3d48afee54c6f95a96ee1a09dca11deabdda7e383edcd8754d97f7a16`.
- Immutable rev10 comparison: commit `25e4019861f0f9a0fdb511b3c281a88e2ce42b01`, SHA-256 `557904bee50dbf94a1f18154f9c174e23d1f475c8ef3f44bd06467ce2c464462`; rev10 to rev11 changes one plan file, 13 insertions and 4 deletions.
- Sealed manifest-format line 259 and live Addendum O were read; O live re-hashes to post-stamp `0e990bac…`.
- W-5 notice `035616` and concurrence `033153` were re-read at their exact current bytes; both say effective, not proposed.
- Product state reverified: HEAD/tag `9e6ebe8`; index empty; changed paths exactly `manifest.cpp`, `manifest.hpp`, `pack.cpp`, `test_cli.cpp`, `test_manifest.cpp`, and `test_open.cpp`; live diff SHA-256 `fbf77f3d52b4a229d2309f45c39a62658351049db36276c6703688bd0dd88db7`.
- No product, test, plan, branch, tag, ref, merge, push, PR, remote-CI, publication, deployment, seal, or release action was taken by this review.

## Escalation scan

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: yes — W-5 is a narrowly effective structural authority waiver and its exact future gate text must not be regressed
- migration/backfill/destructive-write/canonical-data-repair: no
- money/inventory/orders/planning/accounting/trust-critical-state: yes — the plan controls downstream implementation authority
- AI-or-automation-acts-downstream: yes — an approval would permit a fresh implementation token
- worker/scheduler/queue/retry/async-side-effect: no
- cross-repo/service-contract/generated-schema/shared-API-event: yes — locked PDC O/N/M and W-5 govern the plan
- user-visible-control-with-materializer/downstream-consumer: yes — the manifest writer/parser contract controls archive bytes
- test-runtime-role-mismatch: yes — the plan must distinguish historical RED evidence from the actual continuation checkpoint
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: yes — the exact artifact currently gives mutually inconsistent execution and authority instructions
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: W-5 already granted and effective at the exact pinned row; no new waiver requested
- valid_waiver: yes — only within the existing frozen selector and eligible row
WAIVED_RISK_ACCEPTANCE: unchanged from W-5; this review neither expands nor reopens it

## Next gate

File a successor plan that folds F1 through F3 and carries a new exact SHA-256. Route that exact artifact back for Pair Implementer review. Until an exact-hash approve and a fresh addressed implementation token both stand, the six-file patch remains frozen and no Task-3 correction or Task 4 begins.

ACTIONS_GIT_REF: review-only inspection of plan commit 3eaebfc3 at sha256 0929edb3, immutable rev10 at 25e4019/557904be, sealed format/O bytes, effective W-5 notices, revision-11 measurement SITREP, and frozen product bytes; daemon submission only; no product/test/plan/ref/merge/push/PR/remote-CI/publication/deployment/seal/release action
RELAY_LINT: to be engine-rendered; exact-file lint and root verification follow submission
FINAL_GIT_STATUS_SHORT: none — scoped status for the reviewed plan and intg root was clean before daemon submission; inherited S4 state exists outside this review and was untouched; the isolated product worktree remains intentionally dirty in exactly six unstaged paths as recorded above
