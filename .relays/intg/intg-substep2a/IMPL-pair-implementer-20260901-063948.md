## IMPL RETURN — tranche 1 is reviewed clean and retained uncommitted over `9e6ebe8`; tranche 2 and Task 4 remain closed

ROLE: Pair Implementer
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: intg-substep2a-impl-tranche1-return-2
PARENT_DISPATCH_ID: intg-substep2a-audit
IN_REPLY_TO: intg-substep2a/PLAN-pair-planner-20260901-051824.md
RELATED_CONTEXT: intg-substep2a/IMPL-pair-planner-20260831-030859.md; intg-substep2a/IMPL-pair-implementer-20260901-025845.md; docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep2a-20260830.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — tranche 1 consumed only the determined carry; tranche 2 waits on Addendum O's seal, and Task 4, candidate submission, merge, push, publication, deployment, seal, and release remain gated; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: intg-format-act-plan
DESIGN_LOCK_ID: m1-addendum-N-82293732-lock-20260827
DESIGN_RECORD_KIND: design-doc
SECOND_CONSUMED_LOCK: m1-addendum-M-2966b839-lock-20260825
PLAN_LOCK_ID: intg-substep2a-plan-20260830 @ sha256 57ab3b9ba15c5674dae5b42dc3a3c48252e844f8e3d863d0cb1f3682c33b4a4b
BASE: main@46df8f3c35981a4ae3f77cf3293a4b7212b4b996
BRANCH: intg/format-act at retained HEAD 9e6ebe8fca2454164051573323dd7adfa2901219 with tranche-1 diff deliberately UNCOMMITTED; diff sha256 72fd3dc604957e14e944b9f7418a64f723125d8b138909e8e0bd5b045e4b22cf; NOT a candidate
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: master.master-planner, master.master-reviewer, m-1.planner, m-1.implementer
SUBJECT: RETURN — tranche 1 clean: collision-safe UnknownNote substitution, exhaustive ruled DOM witness, H/N-aware local_refs presence, seven parser member paths under the sealed predicate with URLs retained as data, and corrected evidence text; tree remains uncommitted for tranche-2 one-replacement-commit assembly

## Boundary

Consumed `PLAN-pair-planner-20260901-051824.md` at SHA-256 `df0fbc645bd4352bc3b57f799d8659ab214f369cc6b9a099e1a58a87b13c8db9` under standing token `IMPL-pair-planner-20260831-030859.md` at SHA-256 `796005f3babeee9a201a2c4e7b4798d329a836a31a81d867ef1c006571792a99`.

The live Addendum O file had advanced to rev2 and explicitly said `NOT SEALED`; it was NOT consumed. No serializer-signature change, writer-side invalid-carrier refusal, O-R3 biconditional, shared writer/parser inventory, or FX-O witness exists. H's four-field discriminator is unchanged. Task 4 remains closed.

## Implemented, TDD, and review

Tracked changes are exactly `src/core/manifest/manifest.cpp` and `tests/test_manifest.cpp`. The ignored prior Task-3 report now uses sealed spellings `remote`, `url`, `ref`, `tip_sha`, and forced-payload `path`.

1. UnknownNote placeholders capture offsets before raw-note insertion and replace highest-offset first; the two-note collision preserves both raw notes and reparses.
2. The populated DOM witness asserts exact cardinality, member sets, and literals for both rows' `remotes[]`, every `local_refs[]` row including `proof:null`, `capture.forced_payload[]`, `shallow`, structured notes, and the UnknownNote nested array.
3. Missing `local_refs` is rejected for ordinary rows while sealed H payload-only-unborn and N shallow rows retain absent-or-empty licensing.
4. Parser-side `valid_manifest_path` covers exactly `relpath`, `local_refs_bundle`, `bundle`, both patch fields, `payload_prefix`, and forced-payload `path`. Each has absolute, traversal, and dot discrimination; only `relpath` permits `.`. URL data such as `file:///home/user/repo` remains accepted and round-trips.

RED: the UnknownNote collision failed reparse; an ordinary row missing `local_refs` parsed; an unsafe `relpath` parsed. Initial focused GREEN counts were `37`, `11`, `124`, and `208` assertions.

Independent review found no production defect, one Important DOM gap, and one confirmed test gap. Fix round 1 changed tests only, adding the shallow remote, two `proof:null` values, the UnknownNote nested literals, and dot-refusal arms for all six non-`relpath` carriers. Focused reruns passed at `228` and `154` assertions. Scoped re-review: `all findings addressed`; no new Critical or Important breakage.

Fresh final verification:

- build — exit 0.
- `biv_tests` — `15,372 / 15,372 assertions`; `410` cases: `407 passed`, `3 declared skips`.
- `biv_repo_engine_tests` — `452 assertions / 60 cases`, all passed.
- `git diff --check` — exit 0.

## Exact byte binding and next action

```text
HEAD 9e6ebe8fca2454164051573323dd7adfa2901219
git-diff sha256 72fd3dc604957e14e944b9f7418a64f723125d8b138909e8e0bd5b045e4b22cf
manifest.cpp sha256 db50039e715aa42a5768364d1a69685b81020ba3541f78d506d54e5731359ec5
test_manifest.cpp sha256 de98adc41527313ab1751141dc496f01af4259ef12350efd3e1ede5a1d85fea5
corrected prior report sha256 2a3e44464685891a6e816c288c40eca3b40a98c32d08e037f9d0c00ea224c143
tranche report sha256 7b5df5e590be1aab213f3f4adb454faf42ccf092744d9bf5dc939d889da4f99c
```

No commit was made because both tranches must assemble into one replacement Task-3 commit superseding immutable `9e6ebe8`. These hashes bind the returned bytes until a sealed tranche-2 carry arrives.

Not done: tranche 2; O seal consumption; fallible typed serializer; writer validity; O-R3/O-R4/FX-O; replacement commit; final Task-3 review; Task 4 or Linux parity; m-1 candidate review; merge, push, PR, remote CI, publication, deployment, seal, or release.

Next requested action: retain this tree and carry the sealed tranche-2 ruling. Re-verify the exact seal and carry before editing. Task 4 opens only after the replacement Task-3 commit is independently clean.

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: no — no permission or credential value touched
- migration/backfill/destructive-write/canonical-data-repair: no — no destructive act
- money/inventory/orders/planning/accounting/trust-critical-state: no
- AI-or-automation-acts-downstream: no — parse-reach only, zero caller added
- worker/scheduler/queue/retry/async-side-effect: no
- cross-repo/service-contract/generated-schema/shared-API-event: yes — sealed PDC contract governs the parser seam and unsealed O remains deferred
- user-visible-control-with-materializer/downstream-consumer: yes — archive bytes are user-visible, though 2b wiring remains absent
- test-runtime-role-mismatch: yes — Task 4 Linux parity remains unopened
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: yes — tranche 2 and final candidate verification remain outstanding by design
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: not applicable — no downgrade or risk acceptance requested
- scan_presented_to_operator: no — not requested
- operator_reply_after_scan: none
- valid_waiver: no
WAIVED_RISK_ACCEPTANCE: none

ACTIONS_GIT_REF: intg/format-act@9e6ebe8fca2454164051573323dd7adfa2901219; uncommitted tracked diff sha256 72fd3dc604957e14e944b9f7418a64f723125d8b138909e8e0bd5b045e4b22cf over exactly src/core/manifest/manifest.cpp and tests/test_manifest.cpp; no commit/ref move; ignored evidence corrected; no push/PR/merge/release
RELAY_LINT: to be engine-rendered; exact-file lint and root verification follow submission
FINAL_GIT_STATUS_SHORT:
 M src/core/manifest/manifest.cpp
 M tests/test_manifest.cpp
!! .superpowers/
Literal status from the isolated product worktree. The primary checkout retains inherited S4 state, untouched and not claimed clean.
