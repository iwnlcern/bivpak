## PLAN-REVIEW artifact — APPROVE revision 10 at 557904be: the raw-note predicate census, enforcement-site partition, mandatory arms, and proof prose are consistent and executable

ROLE: Pair Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: approve
DISPATCH_ID: intg-substep2a-plan-review-10
PARENT_DISPATCH_ID: intg-substep2a-plan
IN_REPLY_TO: intg-substep2a/PLAN-pair-planner-20260902-053636.md
RELATED_CONTEXT: docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep2a-20260830.md; intg-substep2a/PLAN-REVIEW-pair-implementer-20260902-053057.md; intg-substep2a/PLAN-REVIEW-pair-implementer-20260902-052008.md; ../../pdc/master/relays/intg-substep2a-format-act/DESIGN-planner-20260902-034802.md; ../../pdc/master/domains/m-1-format-engine/design/2026-09-01-ADDENDUM-O-writer-validity-contract.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new operator gate — this approval closes only the implementer's exact-hash PLAN-REVIEW; the standing W-5 Master Reviewer concurrence and effectiveness notice remain prerequisites to a later tranche-2 dispatch token, and implementation, byte reviews, merge, push, publication, deployment, and release retain their separate gates
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
PLAN_LOCK_ID: intg-substep2a-plan-20260830 @ sha256 557904bee50dbf94a1f18154f9c174e23d1f475c8ef3f44bd06467ce2c464462
REVIEWED_PLAN: docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep2a-20260830.md at commit 25e4019, sha256 557904bee50dbf94a1f18154f9c174e23d1f475c8ef3f44bd06467ce2c464462
BASE: main@46df8f3c35981a4ae3f77cf3293a4b7212b4b996; review filed from main@25e4019
BRANCH: intg/format-act at retained HEAD 9e6ebe8fca2454164051573323dd7adfa2901219; index clean; uncommitted tranche-1 diff remains exactly 72fd3dc604957e14e944b9f7418a64f723125d8b138909e8e0bd5b045e4b22cf over src/core/manifest/manifest.cpp and tests/test_manifest.cpp; no product byte or ref changed by this review
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: master.master-planner, master.master-reviewer, m-1.planner, m-1.implementer, m-3.planner, m-3.implementer
SUBJECT: APPROVE exact 557904be — rev10 resolves the final proof-prose contradictions; the plan is executable under locked O/N/M, with implementation still gated behind W-5 concurrence/effectiveness and a later bare tranche-2 token

## Verdict

APPROVE exact SHA-256 `557904bee50dbf94a1f18154f9c174e23d1f475c8ef3f44bd06467ce2c464462`.

Revision 10 folds `053057` exactly. The leg-(e) asymmetry explanation now grounds every table-A parser rejection twin at the site that can observe it: post-build `repo_row_violation` for predicates over a constructed `RepoEntry`, the retained pre-build helper for the seven O-R2 paths, and the retained manifest/raw-note parse sites for the five raw-note shapes. The `unknown-note-roundtrip` control now names the current seven-row UnknownNote refusal population — five table-A shapes and two table-B image exclusions. The current procedure, helper-path paragraph, mandatory arms, implementation step, coverage census, and acceptance criterion agree.

The plan is sufficiently specific to execute: it preserves the exact retained tranche and one-replacement-commit boundary; fixes the ten-path allowlist and three propagation hunks; requires red-first arms for each Step-0 inventory row; keeps parser acceptance and detail strings unchanged; defines the `pi_repo` oracle and writer refusal detail; supplies staged-tree, scope, two-platform, E4 request-trace, and downstream byte-review gates; and states hard out-of-scope surfaces and STOP conditions.

This approval is review-only. It is not an implementation dispatch and authorizes no product/test edit, branch/tag/ref move, merge, push, publication, deployment, or release. No tranche-2 work begins until a later valid addressed relay carries the required bare implementation token after W-5 concurrence and the effectiveness notice.

## Exact review evidence

- Incoming carrier SHA-256: `21973face8ff3c65d010873d5ee7626ed220c3e3fc5c992d13339e217d323511`; exact-file v2.9.2 lint clean.
- Reviewed plan: commit `25e4019`, SHA-256 `557904bee50dbf94a1f18154f9c174e23d1f475c8ef3f44bd06467ce2c464462`.
- Rev9-to-rev10 plan delta is one file, four insertions/four deletions: the revision banner, the two requested normative sentence corrections, and the current revision identity; no product byte moved.
- Dead-current-wording scan is clean for the requested phrases. The only relevant old formulation remaining is explicitly historical revision prose describing superseded/dead plan revisions or the dropped rev4 promise; current normative instructions consistently use enforcement-site partitioning.
- Sealed O re-verifies: live post-stamp `0e990bac752986942d9091871a5175820b829dd019d586e8e895461cfff656d2`; blob at `40b4f7a3dbfc60e5ab742678bc4e77198845c243` = locked `63c46631c84ce27ebedbf71c4965e6b0b149919a83118835d78ce29e89d3e577`.
- Retained tranche 1 re-verifies: HEAD `9e6ebe8fca2454164051573323dd7adfa2901219`; index empty; modified paths exactly `src/core/manifest/manifest.cpp` and `tests/test_manifest.cpp`; diff SHA-256 `72fd3dc604957e14e944b9f7418a64f723125d8b138909e8e0bd5b045e4b22cf`.
- The daemon ledger verifies. The rev10 W-5 archive hashes to `14e7e497cbf4d5f888b78e286a2c5edc62b3e42d155811e1a6db6227aa3025c1`, contains 285 lines, and records exactly the expected O design-lineage entry on the citing carrier; per-file lint is clean. This approval does not adjudicate or waive the standing root finding.

## Boundary and acceptance review

- Scope: exact ten-path allowlist; Task 3 remains the six-path replacement tranche over the already landed three engine commits; no 2b wiring or new production engine caller.
- Boundary: writer and parser share one semantic clause inventory; parser enforcement is post-build or pre-build according to observability; table B remains writer-only projection-image exclusion with construction witnesses.
- UnknownNote: five table-A raw-shape clauses (`json-valid`, `single-value`, `object`, `kind-present`, `kind-string`), two table-B image exclusions (`kind`, `aliases-structured`), and a separate exact-byte positive control.
- Tests/proofs: one negative `FX-O-INV` arm per A/B row; table-derived equality; six FX-O leg tags, seven field tags, eight in-test O mutant markers plus the census marker; `pi_repo` equality and controls; macOS and Ubuntu 24.04 amd64 suites; E4 request tracing.
- Commit discipline: tranche 1 remains uncommitted; explicit staged-tree proof assembles one Task-3 replacement commit; `9e6ebe8` remains retained by local ref; no intermediate asymmetric commit.
- Gates: m-1 and m-3 parallel byte reviews follow the candidate; merge/push/publication/release stay separately prohibited absent their own authority.

## Escalation scan

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: no — review-only
- migration/backfill/destructive-write/canonical-data-repair: no — no product or canonical-data write
- money/inventory/orders/planning/accounting/trust-critical-state: no
- AI-or-automation-acts-downstream: no
- worker/scheduler/queue/retry/async-side-effect: no
- cross-repo/service-contract/generated-schema/shared-API-event: yes — locked PDC O/N/M and m-1's format boundary govern
- user-visible-control-with-materializer/downstream-consumer: yes — archive bytes and parser/writer symmetry are user-visible
- test-runtime-role-mismatch: yes — the plan explicitly closes the writer/parser enforcement and proof-role split
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: no — exact plan review only; all downstream gates retained
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: none — no downgrade or risk acceptance requested
- scan_presented_to_operator: no — not requested
- operator_reply_after_scan: none
- valid_waiver: no
WAIVED_RISK_ACCEPTANCE: none

## Next gate

The pair Planner may route this exact-hash approval upward for W-5 Master Reviewer concurrence and the effectiveness notice. Only after those stand may a new addressed implementation relay parent to this review and carry the required bare token with the ten-path `SCOPE_DIFF`. This approval itself carries no implementation or merge authority.

ACTIONS_GIT_REF: read-only review of plan commit 25e4019 at sha256 557904bee50dbf94a1f18154f9c174e23d1f475c8ef3f44bd06467ce2c464462; incoming carrier, exact plan delta, normative consistency, locked O, m-1 correction 034802, retained code/tranche bytes, W-5 archive, daemon ledger, scope, boundary, tests, acceptance, and current index/worktree state checked; daemon submission only; no product, test, plan, branch, tag, ref, merge, push, publication, deployment, or release action claimed
RELAY_LINT: exact-file v2.9.2 lint is the daemon submission gate; rendered result and digest will be re-verified after filing; inherited intg root-mode reds remain separately registered and are not changed or waived by this review
FINAL_GIT_STATUS_SHORT: none — scoped status for the intg root and reviewed plan was empty before daemon submission; inherited s4 state exists outside this review scope and was untouched
