## IMPL REPORT — Arm-1 Wave A T4 complete: repo engine units, PR #20 open

ROLE: Implementer
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: s4-matrix-arm1-impl-wave-a-r1-t4
PARENT_DISPATCH_ID: s4-matrix-arm1-impl-wave-a-r1
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/IMPL-PLANNER-WAVE-A-DISPATCH-R1-20260806-021238.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — this is the durable T4 completion report under the live corrected Wave-A dispatch; merge remains operator-owned and the release hold is ABSOLUTE
DESIGN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-05-s4-matrix-arm1-design.md
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/plans/2026-08-06-s4-matrix-arm1-plan.md
FROM: s4-matrix.implementer
TO: s4-matrix.planner
CC: s4.orchestrator-planner, operator
SUBJECT: T4 COMPLETE — repo discovery/classification/eligibility/capture/restore units independently reviewed and fresh-green at E2; stacked PR #20 targets T3; Wave A complete; merge/release held

### Result

T4 is complete on `s4-matrix/arm1-t4`, exactly the required five implementation
commits above the published T3 head
`80a5fc82c9bbc58855855b87b527ddd8f0a931f0`:

- `8597f00afc95a9af5d4cb62ed5965d935f458aef` — `feat(repo): discover`
- `37344dac13471b6a16e51aadaace77d770e5be7e` — `feat(repo): classify`
- `aaa8a4452e35826ed01fb5d17fc58219683ca944` — `feat(repo): eligibility`
- `03786e0405efbb7679877e249b9a1cd381fe31a8` — `feat(repo): capture`
- `43d4b97f63bca3d9f01c25992ead462325f4cc5c` — `feat(repo): restore`

The ready-for-review stacked PR is
https://github.com/iwnlcern/bivpak/pull/20, targeting
`s4-matrix/arm1-t3`. GitHub stack #18 records the required linear
`main ← t1 ← t2 ← t3 ← t4` topology. No merge or release action was taken.

### Implemented surface

- Added boundary discovery with prune-before-discovery ordering, `.biv` pruning,
  nested-repository recording, and actual parent-index gitlink detection. A
  regular `.git` file remains a repository boundary and is not falsely treated
  as a submodule, so linked worktrees classify correctly.
- Added the ordered classification gate for nested/submodule fences, unmerged
  index paths, zero-ref and any-ref unborn repositories, dirt, shallow state,
  promisor policy, remote/ref facts, and real timestamp capture. Transient
  engine source state separates filesystem source paths from manifest relpaths
  and snapshots the penumbra used by capture checks.
- Added eligibility proof across all advertised remotes, records the actual
  proving remote on the entry, and uses an unknown-tip fetch probe without
  admitting foreign remote bases to thin capture.
- Added verified full and thin bundles, clone-remote-only thin bases,
  non-carried-ref note generation for P1 legs o1–o5, hostile-ref at-rest
  encoding, stash disclosure, and penumbra loss/contamination detection.
- Added payload-only, shallow, full, overlay, and unborn restore branches with
  object-closure import but no source-ref installation, stash exclusion,
  skip-at-sha/update-ref behavior, branch/detached HEAD correction, zero-artifact
  overlay, root-repository staging beside the live `.biv-stage`, and typed
  engine-error mapping seams.
- Wired only the new repo-engine units and their focused test executable into
  CMake. Scan, pack, open, manifest, and every Step-3 fence remain untouched.

### Verification and review

- TDD REDs preceded each unit implementation. The final focused suite contains
  25 cases and 233 assertions spanning every mandated discovery,
  classification, eligibility, capture, and restore branch.
- `cmake --build --preset dev -j2` — PASS on the exact reviewed code head.
- `ctest --preset dev -R '^repo_engine$' --output-on-failure` — PASS, 1/1 in
  9.01s; 25 cases and 233 assertions.
- `ctest --preset dev -E '^safety-hardening$' --output-on-failure` — PASS,
  17/17 supported tests in 426.58s; `repo_engine` 9.54s, `biv_tests` 243.06s,
  `probe` 11.01s, `harness-selftest` 12.55s, `harness-e2` 146.60s, envelope
  gates green, and `safety-build-werror` green. The existing platform-gated
  `safety-asan-ubsan`, `safety-tidy-analyzer`, and `safety-fuzz-smoke` cases
  reported SKIPPED.
- Earlier superseded full-suite attempts exposed incomplete focused-build
  artifacts and then one generated-envelope artifact. The fixture chain was
  isolated and re-run, two later complete envelope runs passed, and the final
  exact-head 17/17 run above is clean.
- Structural guards — PASS: the exact T3→T4 code diff contains only
  `CMakeLists.txt`, the eleven authorized `src/core/repo/` files, and
  `tests/test_repo_engine.cpp`; there are zero scan/pack/open/manifest edits,
  and `git diff --check` is clean.
- The first published Linux CI build provided a fresh compiler RED: GNU's
  `-Wmissing-field-initializers` rejected partial designated initializers that
  local Apple Clang accepted. The bounded correction makes every omitted field
  explicit without changing its prior default. Independent GNU 15.2
  reproduction with `-Werror=missing-field-initializers` now compiles every new
  production and test unit, and the focused 25/233 suite passes there.
- The next Linux CI pass exposed one fixture portability gap and active
  clang-tidy findings. The merge-conflict fixture now pins a local Git identity
  so Linux reaches the intended unmerged-index state. All Wave-A findings were
  removed or, for two private restore helpers with deliberately distinct named
  roles, narrowly documented and suppressed. Direct clang-tidy 22.1.8 is clean
  across the eight Wave-A C++ units, and the focused suite remains green.
- Independent adversarial re-review — READY, no remaining Critical or Important
  findings at exact code head `43d4b97f63bca3d9f01c25992ead462325f4cc5c`.
  Reproduced findings closed source-relpath separation, proving-remote and thin
  base selection, the penumbra oracle, root-repo staging, typed error use, and
  linked-worktree versus gitlink classification.

### Boundary and continuation

Wave A T1–T4 is complete and published as stack #18. Only T4's authorized new
repo-engine units, type additions, focused test, and CMake wiring changed before
this filing. No scan, pack, open, manifest, schema, Wave-B/C/D, merge, or release
surface changed. Waves B/C/D remain F-fenced and undispatched; both Step-3
fences and all landed behavior remain unchanged.

ACTIONS_GIT_REF: code-review pin `s4-matrix/arm1-t4@43d4b97f63bca3d9f01c25992ead462325f4cc5c`; PR https://github.com/iwnlcern/bivpak/pull/20 targeting `s4-matrix/arm1-t3`; this report and its append-only INDEX row are the only post-code filing delta, with carrying commit recorded in branch history after filing; no merge or release.

FINAL_GIT_STATUS_SHORT:
none — clean at the code head before this report + INDEX write; those two governed filing paths are the only intended delta and are committed together after fresh exact-file and INDEX lint.

Fresh at 20260806-052028 before this report + INDEX write.
Post-CI evidence refreshed at 20260806-053738; the original filing timestamp and
append-only INDEX row remain unchanged.
Post-T2-correction restack refreshed exact pins at 20260806-054709.
Post-tidy correction restack refreshed exact pins at 20260806-064900; the
original filing timestamp and append-only INDEX row remain unchanged.
