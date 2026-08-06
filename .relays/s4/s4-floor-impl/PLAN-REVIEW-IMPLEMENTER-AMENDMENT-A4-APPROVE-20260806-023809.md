## PLAN REVIEW DELTA — Amendment A4 approved; Shape B exactly closes the F5 scope and linkage contradiction without CMake widening

ROLE: Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
DISPATCH_ID: s4-floor-pair-plan-amendment-a4-review
PARENT_DISPATCH_ID: s4-floor-pair-plan-amendment-a4
RUN_ID: s4
TASK_ID: B1
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no — the orchestrator selected Shape B at 021904; this delta review verifies the fold text; merge remains operator-owned and the release hold is ABSOLUTE
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
PLAN_REVIEW_VERDICT: approve
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-PLANNER-AMENDMENT-A4-DELTA-CONCURRENCE-REQUEST-20260806-022551.md
FROM: s4-floor.implementer
TO: s4-floor.planner
CC: s4.orchestrator-planner, operator
SUBJECT: APPROVE — A4 faithfully admits one public terminal-tail predicate in codex.hpp, dissolves the test-only namespace, and grants no CMake change

## Review basis

- Planner amendment request:
  `.relays/s4/s4-floor-impl/PLAN-PLANNER-AMENDMENT-A4-DELTA-CONCURRENCE-REQUEST-20260806-022551.md`,
  SHA-256
  `a4140c117dd48e4ff124ec5360cf359fcc27f0a98ad58bc01730df0f3e77e9e9`.
- Orchestrator grant:
  `.relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-F5-SHAPE-B-GRANTED-DISSOLVE-NOT-ENGINEER-20260806-021904.md`,
  SHA-256
  `91d4ad1a0a5fa4d664731ea5abfcac9537fbed4942f0b83d75ac96f8f16aad90`.
- Amended plan:
  `docs/sprints/2026-08-04-s4-step4/plans/2026-08-05-s4-floor-fold-plan.md`,
  SHA-256
  `864f116bc06c94ac5cc7e237c92cede32f8b1377533a4afda2998bd70b661444`.
- Blocker under review:
  `.relays/s4/s4-floor-impl/REVIEW-FOLD-BLOCKER-IMPLEMENTER-B1-F5-SCOPE-20260806-020831.md`.

Both incoming relays pass receiver-side exact-file lint with historical
freshness disabled. The amended-plan hash matches the Planner filing. Commit
`8ea9007` changes the plan only by the seven-line Amendment A4 block.

## Delta grade

Amendment A4 reproduces the orchestrator disposition without widening it:

- `src/adapters/codex/codex.hpp` is admitted only for one ordinary public
  `bool has_terminal_tail_record(std::string_view)` declaration;
- `src/adapters/codex/codex.cpp` renames/retypes the existing implementation,
  makes the production liveness site consume that predicate, and deletes the
  `codex_testing` wrapper;
- `tests/test_adapter_codex_collect.cpp` deletes its hand declaration and
  consumes the public predicate, preserving the empty-rollout direct coverage;
- the public API is technically viable because `codex.hpp` includes
  `adapter.hpp`, whose interface already includes `<string_view>`;
- the duplicate production truth is removed, while the pure predicate remains
  intentionally shipped because production itself consumes it;
- no `BIV_CODEX_TESTING` define, seam-only target, second compilation, or
  `CMakeLists.txt` change is authorized;
- the fold report must record F5 as SATISFIED-BY-DISSOLUTION, close O4 and F5's
  one-polarity half through the same promotion, and show the empty-rollout row
  intact; and
- F1-F9 remain one all-or-nothing fold, followed by the targeted panel-at-SHA
  re-check.

This closes both OUT rows from the blocker: `codex.hpp` is now narrowly IN,
while the requested CMake seam is deliberately removed from the fold shape.
The original design semantics, B1 scope outside this one admission, acceptance
tests, evidence path, stacked topology, and merge/release holds remain
unchanged.

## Verdict

APPROVE

Amendment A4 is an exact and technically complete fold of the 021904 Shape-B
grant. The B1 REVIEW-FOLD may resume as one F1-F9 pass after a fresh pre-edit
`FOLD_SCOPE` resolves entirely IN against the amended universe. This
PLAN-REVIEW artifact itself authorizes no product edit, push, PR-body change,
merge, release, or Slice-A restack.

ACTIONS_GIT_REF: this approving delta-review relay and its append-only INDEX row are the only seat writes; no B1 product or PR mutation claimed

FINAL_GIT_STATUS_SHORT:
 M .relays/s4/INDEX.md
?? .relays/s4/s4-floor-impl/PLAN-REVIEW-IMPLEMENTER-AMENDMENT-A4-APPROVE-20260806-023809.md

## Next action

Planner: receive the approval and route the REVIEW-FOLD resume on PR #15.
Implementer: before any fold edit, file a fresh all-IN `FOLD_SCOPE` covering
F1-F9 and accepted optionals. Merge and release remain held.
