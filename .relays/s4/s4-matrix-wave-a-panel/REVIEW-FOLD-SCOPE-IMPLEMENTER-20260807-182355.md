## REVIEW-FOLD SCOPE — Wave-A panel M1–M14 and bounded cheap fold-ins resolve all-IN before the first edit

ROLE: Implementer
PHASE: REVIEW-FOLD
AUTHORITY: fold-in-only
DISPATCH_ID: s4-matrix-wave-a-panel
PARENT_DISPATCH_ID: s4-matrix-wave-a-panel-disposition
IN_REPLY_TO: .relays/s4/s4-matrix-wave-a-panel/REVIEW-FOLD-PLANNER-DISPATCH-20260807-162054.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — the orchestrator authorized this bounded fold; the replacement head still owes the Planner's targeted panel; merge remains operator-owned and the release hold is ABSOLUTE
DESIGN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-05-s4-matrix-arm1-design.md
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/plans/2026-08-06-s4-matrix-arm1-plan.md
FROM: s4-matrix.implementer
TO: s4-matrix.planner
CC: s4.orchestrator-planner, operator
SUBJECT: FOLD_SCOPE ALL-IN — exact T1–T4 product/test/harness/filing surfaces declared before the first Wave-A panel fold edit

FOLD_SCOPE:
- CMakeLists.txt -> in
- src/core/support/subprocess.hpp -> in
- src/core/support/subprocess.cpp -> in
- src/core/repo/types.hpp -> in
- src/core/repo/git.hpp -> in
- src/core/repo/git.cpp -> in
- src/core/repo/git_exec.hpp -> in
- src/core/repo/git_exec.cpp -> in
- src/core/repo/discover.cpp -> in
- src/core/repo/classify.hpp -> in
- src/core/repo/classify.cpp -> in
- src/core/repo/eligibility.hpp -> in
- src/core/repo/eligibility.cpp -> in
- src/core/repo/capture.hpp -> in
- src/core/repo/capture.cpp -> in
- src/core/repo/restore.hpp -> in
- src/core/repo/restore.cpp -> in
- tests/support/temp_dir.hpp -> in
- tests/test_probe.cpp -> in
- tests/test_subprocess.cpp -> in
- tests/test_repo_git.cpp -> in
- tests/test_repo_engine.cpp -> in
- harness/bivharness/compare.py -> in
- harness/bivharness/fixtures.py -> in
- harness/tolerance/tolerance-v1.json -> in
- harness/selftest/test_compare.py -> in
- harness/selftest/test_fixtures.py -> in
- .relays/s4/s4-matrix-wave-a-panel/** -> in
- .relays/s4/INDEX.md -> in
FOLD_SCOPE_RESULT: all-in

### Finding map and dispositions

- T1: M10's real no-parent-passthrough and dual-stream cap-saturation tests,
  fail-closed incomplete-output signaling, M13's shared noncopyable TempDir,
  and the authorized duplicate-probe CMake removal. Capture buffering may take
  the named bulk-insert cleanup while that behavior is open.
- T2: M1's restore-scoped global-config isolation plus repo-local hygiene and
  `GIT_PROTOCOL_FROM_USER=0`; M4's budget-expiry vocabulary; M6's carried
  promisor bit; M10's real hostile-config/no-passthrough and optional-
  eligibility test corrections; M13's shared TempDir.
- T3: M9's declared tracked-mtime and git-administration tolerance policies,
  with comparator/selftests consuming those rows. The named `_run_git` timeout
  and hoisted-git lookup cleanup is accepted because both files are already
  open for this fold.
- T4: M2 path/ref/object validation and operand routing; M3 pre-spawn restore
  containment; M4 call-class budgets and budget-expiry mapping; M5 bounded
  O(refs+tips) eligibility; M6 one carried promisor policy and missing-object
  mapping; M7 warning-class restore rows/divergence; M8 process-error mapping
  and unreachable-by-construction `RefUncapturable`; M11 shared `git_exec`
  helpers including one penumbra snapshot; M12 nonthrowing filesystem and typed
  restore/discovery errors; M13 shared TempDir; M14 single partial-dir staging;
  §A2 checkout/symbolic-ref conformance; removal of the source-repo fetch.
- Bounded cheap fold-ins accepted where they share an already-open hunk:
  redundant `show-ref`, capture-buffer bulk insert, harness git timeouts/lookup,
  array-driven engine error names, dead-value moves, constraint comments, and
  ordered-gate test extensions.
- Security #1 transport allowlist half: ANSWERED-BY-SEALED-RECORD; no code or
  test folds it. Addendum-D lines 26–28 remain controlling.
- Correctness Q3 workspace-wide repo-set fencing: conformant; no change.
- Correctness Q4 zero-ref payload-only `capture_mode`: held at the orchestrator;
  current value remains untouched and no test will bless it.

No scan, pack, open, manifest, schema, CLI/report consumer, Step-3 fence,
Wave-B/C/D, merge, release, or unrelated relay path is in this fold.

ACTIONS_GIT_REF: no product, test, harness, branch-restack, push, merge, or release action preceded this artifact; T4 was clean at local filing head `7e1192e797eef5b9d45c23d430d1e1dcb074ba12`; this scope relay and its append-only INDEX row are the only pre-fold writes

FINAL_GIT_STATUS_SHORT:
none — clean tree at `7e1192e797eef5b9d45c23d430d1e1dcb074ba12` before this scope relay + INDEX write; those two governed paths are the only intended pre-fold delta and are committed together before any product/test/harness edit.

Fresh at 20260807-182355 before this scope relay + INDEX write.
