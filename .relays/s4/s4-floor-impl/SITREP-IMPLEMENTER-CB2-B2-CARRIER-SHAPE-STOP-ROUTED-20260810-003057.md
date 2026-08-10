## SITREP — B2 carrier-shape stop fired before edits: two Codex path classes are not row-recoverable from sealed A9 members; route the row-to-pair addendum while A1/A2/B1 proceed locally

ROLE: Implementer
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-floor-impl-2-cb2-b2-shape-stop
PARENT_DISPATCH_ID: s4-floor-impl-2-cb2-four-folds
RUN_ID: s4
TASK_ID: B2
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — B2 needs a row-to-pair association or equivalent new sealed member; the live token forbids the pair from changing the A9 carrier shape and routes that addendum through the orchestrator to m-2
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/IMPL-PLANNER-CB2-FOUR-FOLDS-DISPATCH-IMPL-TOKEN-20260810-000215.md
FROM: s4-floor.implementer
TO: s4-floor.planner
CC: s4.orchestrator-planner, operator
SUBJECT: B2 STOP-AND-ROUTE — sealed A9 members erase the per-row path association, so a correct multi-path Codex recollector requires a carrier-shape addendum; A1/A2/B1 continue locally, commits/publication wait

B2 CARRIER-SHAPE STOP / ADDENDUM ROUTE REQUIRED

The dispatch's cheap pre-edit analysis proves that B2 cannot be implemented within the
sealed A9 content shape.

## Static proof

The sealed sidecar has exactly three relevant surfaces:

- `id_map` associates agent, image ID, installed ID, and child ID pairs, but contains no
  path or path-class member;
- `provenance_chain` is a set of original IDs only;
- `pair_set_applied` is a global set of `[original_path, workspace_path]` pairs.

The writer in `src/core/open/sessions.cpp` sorts and deduplicates the global pair set
before serialization. That intentionally destroys record order and leaves no positional
association with `id_map`.

The Codex consent-NO installer rewrites each row using its own original-path pair into the
same workspace target before publishing the staged artifact. The recollector therefore
sees the installed/minted row identity and rewritten workspace path, not an unreplaced
row-local original path. The existing ID-map and provenance members cannot reconstruct
which of two distinct original-path equivalence classes belongs to which Codex row.

`resolve_codex_staged_original_path` already encodes the strongest inference available
without a row edge: accept one global class, or accept one unclaimed class when exactly
one Codex row remains after Claude claims. With two Codex rows and two unclaimed classes,
both assignments satisfy every sealed member. Selecting either class would be an
unproved association and would silently attach the wrong `original_path` to one row.

Therefore a correct B2 fold needs a row-to-pair edge, a per-row original-path member, or
an equivalent carrier-shape change. Encoding path data into existing ID/children fields
would itself change their sealed meaning and is not a within-shape solution.

## Stop boundary and continuing work

No product or test file was edited before this determination. Per the dispatch:

- B2 carrier-shape implementation is stopped and routed through the Planner/Orchestrator
  to m-2 for the addendum path;
- no edit will add, repurpose, or reinterpret a sealed A9 member locally;
- A1/A2 union under-seeding and B1 Claude staged-subtree same-set work proceed in the
  existing isolated worktree;
- the required two-path Codex round-trip falsifier may be added as RED evidence, but it
  will remain unfixed until the shape ruling returns;
- one-commit amendments, full-suite completion, Docker, merge-tree acceptance, and
  republication wait for the B2 return so each owning head remains one bounded fold.

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: no — repository-local session carrier analysis only
- migration/backfill/destructive-write/canonical-data-repair: no — no persisted mutation
- money/inventory/orders/planning/accounting/trust-critical-state: no — not in scope
- AI-or-automation-acts-downstream: no — no downstream automated act
- worker/scheduler/queue/retry/async-side-effect: no — not in scope
- cross-repo/service-contract/generated-schema/shared-API-event: yes — the required correction changes the sealed A9 carrier contract
- user-visible-control-with-materializer/downstream-consumer: yes — the sidecar writer and staged recollector need a new row-level association
- test-runtime-role-mismatch: no — the defect is reproducible through the real open-to-pack path
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: yes — choosing a row association from an ambiguous global set would accept semantic risk beyond pair authority
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: none
- scan_presented_to_operator: yes — this addressed SITREP presents the carrier-contract and downstream-consumer triggers
- operator_reply_after_scan: none
- valid_waiver: no
WAIVED_RISK_ACCEPTANCE: none

ACTIONS_GIT_REF: no product/test edits claimed; read-only proof at B2 `0653fea400e83a59f4c3a9d7983510222e9159ec`; this relay and its append-only INDEX row are the only writes by this seat
FINAL_GIT_STATUS_SHORT: shared main retains pre-existing untracked sibling relay artifacts; this seat adds only this SITREP and its INDEX append; C worktree clean at d6e44d9 and B2 worktree clean at 0653fea

CARRY LIST:
- B2 row-to-pair carrier-shape addendum → `s4-floor.planner` → `s4.orchestrator-planner` / m-2 route
- A1/A2/B1 plus four-falsifier work → continues locally under `s4-floor-impl-2-cb2-four-folds`
- commits, Docker, merge trees, PR #22/#23 republication, targeted re-panel, merge, and release → held pending B2 return; release hold ABSOLUTE
