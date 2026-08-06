## IMPL REPORT — Arm-1 Wave A T3 complete: deterministic Git fixtures and repo-aware golden harness, PR #19 open

ROLE: Implementer
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: s4-matrix-arm1-impl-wave-a-r1-t3
PARENT_DISPATCH_ID: s4-matrix-arm1-impl-wave-a-r1
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/IMPL-PLANNER-WAVE-A-DISPATCH-R1-20260806-021238.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — this is the durable T3 completion report under the live corrected Wave-A dispatch; merge remains operator-owned and the release hold is ABSOLUTE
DESIGN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-05-s4-matrix-arm1-design.md
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/plans/2026-08-06-s4-matrix-arm1-plan.md
FROM: s4-matrix.implementer
TO: s4-matrix.planner
CC: s4.orchestrator-planner, operator
SUBJECT: T3 COMPLETE — deterministic Git fixtures + repo-aware semantic oracle + live tolerance rows reviewed and fresh-green at E2; stacked PR #19 targets T2; merge/release held

### Result

T3 is complete on `s4-matrix/arm1-t3`, exactly one implementation commit above
the published T2 head `616bc4f2058c6a8bd8eeb2a3d0f5303b2d47552d`:

- `3dc03376020dd0513813855ba469192d1fb84576` — `feat(harness): git fixture builders, repo-aware compare, tolerance git rows`

The ready-for-review stacked PR is
https://github.com/iwnlcern/bivpak/pull/19, targeting
`s4-matrix/arm1-t2`. GitHub stack #18 records the required linear
`main ← t1 ← t2 ← t3` topology. No merge or release action was taken.

### Implemented surface

- Extended `fixtures.py` with `git-bare` and `git-repo` entries, deterministic
  commit/branch/tag construction, declared local remotes and pushes, one
  resolved Git binary, and a controlled environment with isolated HOME/global
  config, fixed identity/dates, disabled signing, and no ambient `GIT_*`
  injection channels.
- Hardened mixed fixtures so lexical, case-folded, canonical-symlink, pre-init,
  and later generic-entry paths cannot write through a declared repo's `.git`
  administration area or redirect `git init` outside the fixture root.
- Made `compare_trees` prune `.git/**` from byte comparison and replace it with
  semantic HEAD/current-branch, clean porcelain-v2, carried heads/tags, and
  recorded-remote checks. Non-carried refs remain tolerated by tree comparison
  while explicit `repo_state` assertions retain all-ref visibility.
- Limited checkout-mtime tolerance to source-index tracked files. Ignored and
  untracked repo penumbra remains payload and retains the existing exact mtime
  contract; bytes, modes, and symlink targets remain checked throughout the
  worktree.
- Wired `expect.repo_state` into scenarios for `head_sha` or `head_unborn`,
  branch, porcelain cleanliness, and exact ref assertions.
- Flipped the single tolerance surface to reachable `head-and-refs`,
  `semantic-only`, and `recorded-remote` policies, with the consuming policy set
  changed in lockstep. The authorized status-only L-G2/L-G3 ledger cells moved
  exactly from `FROZEN` to `DONE`.

### Verification and review

- TDD RED witnessed before implementation: the new repo-state oracle import was
  absent. Subsequent REDs covered hostile config parameters and template hooks,
  ambient Git directory redirection, case-folded/canonical/pre-init/generic
  `.git` writes, unborn state, all three live tolerance policies, tracked versus
  ignored-payload mtimes, and carried versus non-carried refs.
- `PYTHONPATH=harness .../python3.12 -m pytest harness/selftest -q` — PASS,
  974/974 in 11.27s on the exact reviewed head.
- Focused fixture/comparator selftests — PASS, 31/31.
- `ctest --preset dev -E '^safety-hardening$' --output-on-failure` — PASS,
  16/16 supported tests in 404.01s; `biv_tests` 229.36s, `probe` 10.28s,
  `harness-selftest` 13.10s, `harness-e2` 147.58s, and
  `safety-build-werror` green. The existing platform-gated
  `safety-asan-ubsan`, `safety-tidy-analyzer`, and `safety-fuzz-smoke` cases
  reported SKIPPED.
- One superseded full-suite attempt recorded a timeout in an inherited probe
  case under concurrent review load. It did not recur in 30 isolated
  repetitions, a dedicated full probe target, or the final complete E2 run; no
  product or inherited-test change was made.
- Structural guards — PASS: the exact T2→T3 diff contains eight authorized
  harness/ledger paths and zero `src/`, `tests/`, or `CMakeLists.txt` paths;
  `git diff --check` is clean.
- Independent scoped review — READY, no remaining Critical or Important
  findings at `3dc0337`. Every adversarial finding was reproduced as a focused
  RED, fixed, regression-tested, and closed on re-review.

### Boundary and continuation

Only T3's seven harness paths and the status-only L-G2/L-G3 ledger cells were
changed. No product, product-test, CMake, manifest, scan, pack, open, schema,
Wave-B/C/D, merge, or release surface was changed. T4 remains next on the
required linear stack, based on this published T3 head; all F-fenced work
remains held.

ACTIONS_GIT_REF: `s4-matrix/arm1-t3@3dc03376020dd0513813855ba469192d1fb84576`; PR https://github.com/iwnlcern/bivpak/pull/19 targeting `s4-matrix/arm1-t2`; this report and its append-only INDEX row are the only post-code filing delta, with carrying commit recorded in branch history after filing; no merge or release.

FINAL_GIT_STATUS_SHORT:
none — clean at the code head before this report + INDEX write; those two governed filing paths are the only intended delta and are committed together after fresh exact-file and INDEX lint.

Fresh at 20260806-041636 before this report + INDEX write.
Post-T2-correction restack refreshed exact pins at 20260806-054635; the original
filing timestamp and append-only INDEX row remain unchanged.
Post-tidy correction restack refreshed exact pins at 20260806-064700; the
original filing timestamp and append-only INDEX row remain unchanged.
