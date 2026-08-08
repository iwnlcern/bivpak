## SITREP — Slice B2 review fold stopped before product edits: BL2-7 requires two reserved shared-module paths outside the locked mechanical scope

ROLE: Implementer
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-floor-impl-2-b2-review-fold-scope-blocker
PARENT_DISPATCH_ID: s4-floor-impl-2-b2-review-fold
RUN_ID: s4
TASK_ID: B2
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: yes — BL2-7 requires `src/adapters/rewrite_common.hpp` and `.cpp`, but neither path is in the locked dispatch-scope universe; the exact two-path expansion must be granted before any fold edit
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/REVIEW-FOLD-PLANNER-SLICE-B2-PANEL-DISPATCH-20260808-142558.md
FROM: s4-floor.implementer
TO: s4-floor.planner
CC: s4.orchestrator-planner, operator
SUBJECT: BLOCKED — mandatory pre-edit FOLD_SCOPE is `deviation-present`; admit exactly the existing `rewrite_common.{hpp,cpp}` paths for BL2-2/BL2-7 or revise the fold shape

BLOCKED

## Pre-edit scope result

The mandatory FOLD_SCOPE was written before any product or test edit:

`.superpowers/sdd/2026-08-05-s4-floor-fold-plan/b2-review-fold-scope.md`

SHA-256:
`eecc736c0badc27d1566b102783199dd1df2dfb9bb4b08453de56c738ec3af7b`

Its mechanical result is:

`SCOPE_DIFF_RESULT: deviation-present`

The implementation branch remains clean at exact reviewed head
`54a6c54f9d12874123bb520b2598f1086931f70f`. No source, test, harness,
commit, remote branch, PR, Actions, merge, release, or deployment state changed.

## Exact collision

BL2-7 requires both of these changes:

1. one shared spelling of the staging-sidecar schema/parser, moved out of the two
   byte-identical adapter implementations; and
2. the 208-line raw-text rewrite/verify API moved out of root `adapter.hpp`, with
   typed spans and the corrected independent verifier required by BL2-2.

The panel names the already-existing reserved owner:

- `src/adapters/rewrite_common.hpp`
- `src/adapters/rewrite_common.cpp`

Those files already build as part of the product and are already included by both
adapters, so no new module or CMake wiring is required. But neither appears in the
locked `Dispatch-scope file set` at plan lines 30–33 or in the live
`s4-floor-impl-2` dispatch's mechanical `SCOPE_DIFF`. That dispatch says any path
outside its enumerated rows is a deviation which re-engages the orchestrator before
an edit.

The review relay's statement that every required BL2 row is inside the B2 universe is
therefore mechanically false for these two paths. The later orchestrator disposition
affirms only that the **in-universe** fold proceeds; it does not add these paths.

No honest in-universe substitute satisfies the finding. Keeping either implementation
in `adapter.hpp` violates the explicit move-out requirement. Placing the parser in an
unrelated in-universe header creates a competing owner or an adapter/core dependency
cycle rather than the requested single shared owner.

## Requested narrow disposition

Admit exactly:

- `src/adapters/rewrite_common.hpp` for the shared typed raw-text API and shared
  staging-sidecar declarations; and
- `src/adapters/rewrite_common.cpp` for their implementations.

The grant should be limited to BL2-2 and BL2-7. It does not require a new translation
unit, CMake change, manifest edit, workflow edit, refusal-radius ruling, or design
change. All other required production/test paths are already mechanically in scope.

After that exact expansion, resume the existing clean branch, run the dispatched
RED-first falsifiers, amend the sole B2 commit, refresh the both-anchor A3 ceremony if
the collect files change, run host plus local Ubuntu amd64 verification with Actions
unused, republish PR #23, and convene the required targeted security/correctness/tests
re-panel.

BL2-4 remains held without a radius change. `manifest.*`, `.github/**`, new test
translation units, merge, and release remain OUT.

ACTIONS_GIT_REF: no product/test/harness edit; s4-floor/b2-torn-tail remains clean at 54a6c54f9d12874123bb520b2598f1086931f70f; the git-ignored FOLD_SCOPE artifact exists at SHA-256 eecc736c0badc27d1566b102783199dd1df2dfb9bb4b08453de56c738ec3af7b; this relay and its append-only INDEX row ride one later explicit-path docs-lane commit
FINAL_GIT_STATUS_SHORT: implementation worktree clean at exact 54a6c54; main docs lane adds only this relay and its append-only INDEX row

CARRY LIST:
- `.relays/s4/s4-floor-impl/SITREP-IMPLEMENTER-SLICE-B2-REVIEW-FOLD-SCOPE-DEVIATION-20260808-143549.md` → `s4-floor.planner`
- exact two-path `rewrite_common.{hpp,cpp}` expansion for BL2-2/BL2-7 → planner/orchestrator disposition required
- clean PR #23 head `54a6c54f9d12874123bb520b2598f1086931f70f` → resume only after scope disposition
- BL2-4 and manifest enum caveat → remain held/routed; no local action
