## REVIEW-FOLD2 SCOPE — S-1 and P-1 resolve all-IN before the first product or test edit

ROLE: Implementer
PHASE: REVIEW-FOLD
AUTHORITY: fold-in-only
DISPATCH_ID: s4-matrix-wave-a-panel
PARENT_DISPATCH_ID: s4-matrix-wave-a-panel-disposition
IN_REPLY_TO: .relays/s4/s4-matrix-wave-a-panel/REVIEW-FOLD2-PLANNER-DISPATCH-20260807-194121.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — this is the standing second bounded fold; the replacement head still owes the Planner's targeted check; merge remains operator-owned and the release hold is ABSOLUTE
DESIGN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-05-s4-matrix-arm1-design.md
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/plans/2026-08-06-s4-matrix-arm1-plan.md
FROM: s4-matrix.implementer
TO: s4-matrix.planner
CC: s4.orchestrator-planner, operator
SUBJECT: FOLD_SCOPE ALL-IN — exactly the S-1 Git config-exec closure, P-1 subprocess growth correction, their direct tests, and governed filing surfaces

FOLD_SCOPE:
- src/core/support/subprocess.cpp -> in
- tests/test_subprocess.cpp -> in
- src/core/repo/git.cpp -> in
- tests/test_repo_git.cpp -> in
- .relays/s4/s4-matrix-wave-a-panel/** -> in
- .relays/s4/INDEX.md -> in
FOLD_SCOPE_RESULT: all-in

### Finding map

- **P-1:** remove the per-drain exact-size reserve from `ByteCapture::write` so
  `std::vector` retains geometric growth. `tests/test_subprocess.cpp` is admitted for
  the dispatch's optional large-output regression guard if a stable behavioral guard
  can be demonstrated RED without timing-only assertions.
- **S-1:** extend the existing injected Git config set with empty
  `core.fsmonitor` and `core.alternateRefsCommand` values, and increment
  `GIT_CONFIG_COUNT`. `tests/test_repo_git.cpp` owns the required real hostile
  repo-local fsmonitor execution test.

The non-atomic TempDir optional, test environment-mutation guard, remote-name option
confusion, `<initializer_list>` IWYU nit, Wave-C exit-class integration flag, and held
zero-ref `capture_mode` cell are not accepted into this fold. No source beyond these two
production files, no other test/harness/schema surface, no new PR, no merge, and no
release is in scope.

ACTIONS_GIT_REF: no product/test edit, lower-branch restack, push, merge, or release action preceded this artifact; cumulative T4 was clean at `92bd09f9f8c8898d9a5121dc4f4466cd3b8109c0`; this scope relay and its append-only INDEX row are the only pre-fold writes
FINAL_GIT_STATUS_SHORT: none — clean cumulative T4 tree at `92bd09f9f8c8898d9a5121dc4f4466cd3b8109c0` before this scope relay and INDEX append

Fresh at 20260807-205837 before the first REVIEW-FOLD2 product or test edit.
