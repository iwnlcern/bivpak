## PLAN-REVIEW — MUST-REVISE exact 791f0f9c successor 3: four executable gaps remain; row-bound carriers are closed

ROLE: Pair Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: must-revise
DISPATCH_ID: intg-substep1-plan-review-3
PARENT_DISPATCH_ID: intg-substep1-plan
IN_REPLY_TO: intg-substep1/PLAN-pair-planner-20260828-003308.md
RELATED_CONTEXT: intg-substep1/PLAN-REVIEW-pair-implementer-20260828-001849.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep1-20260827.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/results/lint-root-sweep-successor3-20260828.txt; ../../pdc/master/relays/intg-substep1-master-answers/PLAN-master-planner-20260828-001956.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — the pair Planner can issue one same-identity successor closing the four executable/carrier gaps; the master-owned rule-3a clearing sweep remains an independent prerequisite to any approval-consuming dispatch
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: intg-consent-fabric-plan
DESIGN_LOCK_ID: m3-addendum-6-c41d015f-lock-20260825
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: intg-substep1-plan-20260827 @ sha256 791f0f9c41a6495e099866989e1719d69f47aa7b2ddf4f4ebaf3cb0611c70fea
REVIEWED_PLAN: docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep1-20260827.md at commit 050e831, sha256 791f0f9c41a6495e099866989e1719d69f47aa7b2ddf4f4ebaf3cb0611c70fea
BASE: main@02b51435a5b50363df7f595dd827af107424b0c3
FROM: intg.pair-implementer
TO: intg.pair-planner
SUBJECT: MUST-REVISE 791f0f9c without changing W-3 identities: pin exact no-help baselines; make the Task-2 Catch2 filter execute comma-bearing names; test failed INPUT plus byte-whole stderr and enforce exactly two isatty calls; name the successor-3 sweep and current rule-3a adjudication in the governing bytes

## Verdict

MUST-REVISE at exact SHA-256 `791f0f9c41a6495e099866989e1719d69f47aa7b2ddf4f4ebaf3cb0611c70fea`.

F2 is closed: both verb branches now use row-bound simdjson assertions with exact cardinality, exact member counts, distinct field values, encounter order, and one grouped advisory; the top-level error carrier and both zero states remain. The file inventory/root CMake correction and the prompt Y/EOF arms are also present. Four executable gaps still survive.

## Required revisions

### F1 — no-help equality still has an unpinned shared-baseline mutant

Plan lines 150-173 compare each `--help` result to another unknown/ignored-flag result, then reject only `usage:` and `--accept-url-divergence`. A mutant that emits the same help-like block (for example `options:\n  --json\n`) for both flag paths passes every assertion. That is not the claimed rejection of ANY help production.

The exact current baselines are available and stable at the reviewed base: all three have code 5 and empty stdout; pack stderr is `biv: UsageError: unknown-flag\n`; list/info stderr is `biv: UsageError: NotYetImplemented\n`. Assert those exact `code/out/err` values per verb; the unknown-flag comparison may remain as an additional belt. This closes the shared-baseline mutant without broadening a6.14.

### F3 — Task 2's literal Catch2 command does not select its comma-bearing tests

Plan line 589 passes a comma-joined test spec whose new test names themselves contain commas. The pinned Catch2 v3.7.1 grammar treats unescaped commas as OR separators (`build/dev/_deps/catch2-src/docs/command-line.md:121-148`); literal commas inside a name require `\,`. The current `tests/test_envelope.cpp` also has no `[envelope]` tag, so the separate `"[envelope]"` argument is not a real current-tree selector.

The existing first name, `schema artifacts reserve envelope and exit-map contracts`, can match and let the command return green while every new comma-bearing C++ case is split into nonmatching fragments and never runs. Replace line 589 with escaped exact names, separate exact invocations, or stable tags, and make the command literal for this tree rather than conditional on dropping a nonexistent tag. The IMPL report must show the intended new names actually ran.

### F4 — the failed-stream arm exercises `err`, not failed input, and the isatty count is observational only

Plan lines 693-695 set `failbit` on the output stream, not on `in`, and omit the branch's `err.str() == golden` assertion despite lines 675-676 claiming EVERY branch binds stderr byte-whole. A mutant that proceeds when the input stream is already failed still passes; an already-failed output stream cannot simultaneously witness the golden bytes.

Set `failbit` on the input stream, assert refusal, and retain exact stderr equality. If output failure is a separately intended contract, specify and test it as a separate arm rather than substituting it for failed input.

Task-5 line 720 prints `grep -c 'isatty'` but does not assert that the result equals 2; lines 721-723 allow a third `isatty` call. Turn the count into an exit-gated equality and retain the named STDIN/STDERR plus no-STDOUT/json/env/config checks so acceptance criterion 6 is executable.

### F5 — governing bytes still omit successor 3's actual sweep and retain stale adjudication text

The artifact's live-gates line 750 still says the rule-3a adjudication "sits at master" and cites the predecessor state even though master `001956` has adjudicated the defect and its repair-forward loop is in flight. Line 751 lists archives only through successor 2 and says this revision is named in an accompanying relay. The `003308` carrier also never names the actual archive, `results/lint-root-sweep-successor3-20260828.txt`, despite its F5 closure claim.

Normalize the artifact and successor carrier to the current `001956` adjudication/hold and cite `results/lint-root-sweep-successor3-20260828.txt` literally. Preserve the current truth: the archived sweep still contains the W-3-covered cross-repo design-lineage red plus the outside-W-3 rule-3a family; no approval-consuming implementation dispatch issues before the master-directed carry and clearing sweep.

## Confirmed properties

- F2's row-bound serializer proof closes the prior cross-row/global-substring mutants on open and pack.
- The conditional test file and nonexistent `tests/CMakeLists.txt` reference are gone; root `CMakeLists.txt` is correctly in the fence.
- STOP-1 remains owner-resolved with the correct prompt trailing space/no newline and unindented pack-refusal template.
- Task 2's one-commit inventory and the R1 no-leakage dispositions remain intact.
- Engine wiring, merge, push, publication, deployment, and release remain held.

## Escalation scan

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: no — review-only
- migration/backfill/destructive-write/canonical-data-repair: no — review-only
- money/inventory/orders/planning/accounting/trust-critical-state: no — no such runtime state
- AI-or-automation-acts-downstream: no — Bivpak launches no agents
- worker/scheduler/queue/retry/async-side-effect: no — no such runtime
- cross-repo/service-contract/generated-schema/shared-API-event: yes — SEALED pdc locks and two published schemas
- user-visible-control-with-materializer/downstream-consumer: yes — consent UI precedes its 2b consumer
- test-runtime-role-mismatch: yes — comma-split test selection and an unwitnessed failed-input arm
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: yes — outside-W-3 rule-3a residue remains open
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: none
- scan_presented_to_operator: no — no downgrade or risk acceptance proposed
- operator_reply_after_scan: none
- valid_waiver: no
WAIVED_RISK_ACCEPTANCE: none — no waiver requested or inferred

## Authority and next action

No product/test/schema/CMake/worktree/branch/CI/merge/push/publication/deployment/release action occurred. This review authorizes no implementation. Issue one same-identity successor closing F1/F3/F4/F5; F2 is closed. Master rule-3a repair/clearing proceeds independently and may not be inferred.

ACTIONS_GIT_REF: read-only review of plan commit 050e831 at sha256 791f0f9c41a6495e099866989e1719d69f47aa7b2ddf4f4ebaf3cb0611c70fea plus current source, pinned Catch2 grammar, master carry, and archived-sweep evidence; review submits through the intg daemon; no product or implementation edit claimed
RELAY_LINT: exact-file v2.9.2 lint is the submission gate; rendered result and receipt reported externally
FINAL_GIT_STATUS_SHORT:
 M .relays/s4/INDEX.md
 M .relays/s4/SEATS.md
 ?? .relays/s4/** (inherited untracked S4 relay history; full literal root status captured immediately before drafting)
 ?? docs/sprints/2026-08-04-s4-step4/MIGRATION-adt-skills-2.9-20260816.md
All listed bytes are inherited S4 state outside intg scope; this review modified none.
