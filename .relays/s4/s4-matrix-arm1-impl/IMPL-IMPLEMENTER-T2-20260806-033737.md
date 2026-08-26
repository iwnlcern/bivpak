## IMPL REPORT — Arm-1 Wave A T2 complete: sealed repo types and env-pinned git wrapper, PR #17 open

ROLE: Implementer
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: s4-matrix-arm1-impl-wave-a-r1-t2
PARENT_DISPATCH_ID: s4-matrix-arm1-impl-wave-a-r1
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/IMPL-PLANNER-WAVE-A-DISPATCH-R1-20260806-021238.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — this is the durable T2 completion report under the live corrected Wave-A dispatch; merge remains operator-owned and the release hold is ABSOLUTE
DESIGN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-05-s4-matrix-arm1-design.md
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/plans/2026-08-06-s4-matrix-arm1-plan.md
FROM: s4-matrix.implementer
TO: s4-matrix.planner
CC: s4.orchestrator-planner, operator
SUBJECT: T2 COMPLETE — sealed repo types + one env-pinned git wrapper reviewed and fresh-green at E2; stacked PR #17 targets T1; merge/release held

### Result

T2 is complete on `s4-matrix/arm1-t2`, exactly one product commit above the
published T1 head `18c68f26d9e27ac9dffd2c6e8330fc15b65724e2`:

- `d1a336adefc30a40df7c5c017645f5112e3aab5f` — `feat(repo): repo types + env-pinned git wrapper`

The ready-for-review stacked PR is
https://github.com/iwnlcern/bivpak/pull/17, targeting
`s4-matrix/arm1-t1`. GitHub stack #18 records the required linear
`main ← t1 ← t2` topology. No merge or release action was taken.

### Implemented surface

- Added `src/core/repo/types.hpp`, mirroring the sealed §2.3 + addendum-G
  vocabulary: repo/head/capture/eligibility/ref-availability enums; proof,
  remote, local-ref, eligibility, shallow, capture, and note shapes; and a
  `RepoEntry` whose eligibility is optional for the zero-ref unborn case.
- Preserved unknown addendum-G note members as an exact `verbatim_json` byte
  string alongside their kind so the later `--json` consumer can carry them
  without reinterpretation.
- Added `src/core/repo/git.{hpp,cpp}` as the sole repo-layer adapter to
  `support::run_argv`: it resolves one canonical absolute git binary; pins the
  non-interactive, locale, config, askpass, and conditional lazy-fetch
  environment; expresses cwd through `-C`; mechanically inserts `--` before
  every non-empty operand list; keeps exit status as data; and supports direct
  stdout-file streaming.
- Added the `BIV_REPO_TESTING` request-construction seam, a dedicated `repo_git`
  CTest target, and the full T2 real-git plus request-shape test matrix in
  `tests/test_repo_git.cpp`.

### Verification and review

- TDD RED witnessed before implementation: the new header/source and CMake
  target were absent. Subsequent focused REDs proved missing askpass pins and
  the missing verbatim payload on `UnknownNote`; each became a regression test
  before the implementation fix.
- `cmake --build --preset dev -j2` — PASS.
- `ctest --preset dev -R '^(repo_git|subprocess|probe.*)$' --output-on-failure`
  — PASS, 4/4 in 13.32s after the final T1 restack and review fix.
- `ctest --preset dev -E '^safety-hardening$' --output-on-failure` — PASS,
  16/16 supported tests in 397.78s on the exact product head; `biv_tests`
  228.66s, `probe` 10.37s, `harness-selftest` 8.39s, `harness-e2` 146.88s,
  and `safety-build-werror` green. The existing platform-gated
  `safety-asan-ubsan`, `safety-tidy-analyzer`, and `safety-fuzz-smoke` cases
  reported SKIPPED.
- Structural guards — PASS: `src/core/repo/git.cpp` is the only repo-layer file
  containing `run_argv`; `src/core/repo/types.hpp` has no manifest include;
  `git diff --check 18c68f2..d1a336a` is clean.
- Post-stack GNU CI compatibility correction: T2's three partial aggregate
  initializers in `tests/test_repo_git.cpp` now use default construction plus
  explicit assignment. Runtime values and assertions are unchanged; the focused
  `repo_git` case remains green.
- Post-stack clang-tidy compatibility correction: the capture cap arithmetic in
  `src/core/repo/git.cpp` now begins with `std::size_t`, avoiding an implicit
  widening conversion. Direct clang-tidy 22.1.8 and the focused test are green.
- Independent scoped review — APPROVE, no remaining Critical or Important
  findings. Review initially found that unknown note kinds lacked their exact
  JSON payload; the finding was reproduced as a compile RED, fixed with
  `verbatim_json`, regression-tested, and approved on re-review.

### Boundary and continuation

Only T2's four new files and its CMake wiring were changed. No discovery,
classification, eligibility, capture, restore, harness, manifest, scan, pack,
open, schema, ledger-status, Wave-B/C/D, merge, or release surface was changed.
T3 remains next on the required linear stack, based on this published T2 head;
all F-fenced work remains held.

ACTIONS_GIT_REF: `s4-matrix/arm1-t2@d1a336adefc30a40df7c5c017645f5112e3aab5f`; PR https://github.com/iwnlcern/bivpak/pull/17 targeting `s4-matrix/arm1-t1`; this report and its append-only INDEX row are the only post-code filing delta, with carrying commit recorded in branch history after filing; no merge or release.

FINAL_GIT_STATUS_SHORT:
none — clean at the code head before this report + INDEX write; those two governed filing paths are the only intended delta and are committed together after fresh exact-file and INDEX lint.

Fresh at 20260806-033737 before this report + INDEX write.
Post-CI evidence refreshed at 20260806-054550; the original filing timestamp and
append-only INDEX row remain unchanged.
Post-tidy restack evidence refreshed at 20260806-064500; the original filing
timestamp and append-only INDEX row remain unchanged.
