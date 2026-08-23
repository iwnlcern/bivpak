## SITREP — T4 NSDMI rev4 complete: nineteen-row oracle exact, guard line 142 proven by positive and negative controls, Linux focused green, macOS 14/14 green

ROLE: Implementer
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: s4-matrix-t4-nsdmi-fix-complete-r4
PARENT_DISPATCH_ID: s4-matrix-t4-nsdmi-fix-impl-r4
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/IMPL-PLANNER-T4-NSDMI-R4-GUARD-DISPATCH-NINETEEN-ROW-ORACLE-20260822-190215.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-T4-NSDMI-R4-NINETEEN-ROWS-LITERAL-DIAGNOSTIC-LINE-GUARD-SITE-BOUND-20260822-183716.md; .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-T4-NSDMI-R4-APPROVE-NINETEEN-ROWS-DIAGNOSTIC-LINE-GUARD-SITE-BOUND-20260822-184513.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: Planner adjudicates this completion, then the Orchestrator Planner may convene the Stage-3 panel. This report grants no merge, push, PR mutation, remote CI, publication, deployment, schema, or release authority. The release hold is ABSOLUTE
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: authorized pre-edit T4 29120d09891bfc46e80635c2212befa22a0e2604 on FINAL T3 70601fc201b3c41d2542d82399787b5febcbf03c
CANDIDATE: local T4 6ba01ef92ef5052b317f6210fa202d5577e1e6c1
FROM: s4-matrix.implementer
TO: s4-matrix.planner, s4.orchestrator-planner
CC: operator, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: T4 rev4 implementation complete at 6ba01ef — exact three-file cause fix and fourteenth-site class guard; O-1 through O-5 discharged; GUARD_LINE 142; local and unpublished pending adjudication and panel

## 1. Candidate and exact scope

Candidate `6ba01ef92ef5052b317f6210fa202d5577e1e6c1` is directly parented to the
authorized clean base `29120d09891bfc46e80635c2212befa22a0e2604`. The source commit changes
exactly the three authorized paths, with 10 insertions and 3 deletions:

```text
src/core/repo/git_exec.hpp   2500 bytes  SHA-256 523e13186cb4bc7d9e6eb12b0a64ea0f56c8c6819068b30f3fc54c4052d87f0  blob 94f674f
src/core/repo/types.hpp      6253 bytes  SHA-256 744ba6c694b984a8f88a04828e293900e5a8b7ef6e0bdcc8ab90cc25db180f18  blob 816ec6d
tests/test_repo_engine.cpp  54027 bytes  SHA-256 1dd44d5ce09b682f97b991b7edcef10eda4688e9ddc07ea4add0b319f5aee98c  blob ff8aad0
```

The production edit is only `budget_override{}`, `empty_config_keys{}`, and
`neutralized_git_config_keys{}`. `repo_path` and `penumbra_paths` are untouched. The test edit
adds one minimal designated initializer as a fourteenth `GitInvokeOptions` site and checks the
two extension-member defaults. No caller initializer changed.

The retained evidence root is worktree-relative at
`.superpowers/sdd/IMPL-PLANNER-T4-NSDMI-R4-GUARD-DISPATCH-NINETEEN-ROW-ORACLE-20260822-190215/evidence`.
Its `RECEIPTS.sha256` verifies 23/23 and has SHA-256
`1de471e1fb253a4000cba3dca7baf50f2ae55fc5f5eaca6e2f2093f64f838adf`.

## 2. O-1 canonical RED and literal nineteen-row enumeration

The untouched-base source tar was 9,492,480 bytes at SHA-256
`90920215895e376ab50b642bab35d57e16927c1cedd3eec7da6723015c6e0fa2`.

- O-1a: fresh Ubuntu 24.04 amd64 under Docker `--init`, GCC 13.3.0, real
  `-Wall -Wextra -Werror`, nofile soft/hard 1048576/1048576. Build exit 2 on
  `missing-field-initializers`, as required.
- O-1b: separate fresh container, identical bytes/compiler/environment, with
  `-Wno-error=missing-field-initializers -fmax-errors=0` appended after `-Werror`. Every
  governed TU compiled and linked, exit 0. Mechanical multiset comparison returned exactly
  the nineteen literal `(FILE, RAW_GCC_DIAGNOSTIC_LINE, STRUCT, MEMBER)` rows, multiplicity
  one each: 12 `budget_override`, 5 `empty_config_keys`, and 2
  `neutralized_git_config_keys`. No struct outside `GitInvokeOptions` and
  `EngineSourceState` appeared.

The guard was added test-first. Before any production byte changed, its initializer failed at
raw GCC line 142 on both `GitInvokeOptions::budget_override` and
`GitInvokeOptions::empty_config_keys`, exit 2 under the real warning policy. After the three
NSDMIs, the same GCC 13 target built and `repo_engine` passed.

## 3. O-2 Linux focused proof and R-4.35 classification

The final tracked working-tree tar was 11,073,024 bytes at SHA-256
`fcb7b1d9907ed8fad888aeca696f4526ecaa6ef0626b88e17b64ccacaa3f946f`.
It ran in a new disposable `ubuntu:24.04` container with `--platform linux/amd64`, Docker
`--init`, non-root user `biv`, GCC 13.3.0, and nofile soft/hard
1048576/1048576. The host worktree was not mounted.

```text
focused build                     exit 0
repo_git + repo_engine             2/2 passed, 0 failed, 26.68 s
harness/selftest                   2 failed, 994 passed, 3 skipped, exit 1
R-4.35 classification              both failures inside the registered four-member family
```

The two observed residual members were
`test_c1_zero_session_control_reds_on_file_inserted_at_scandir_stop` and
`test_credential_scanner_detects_entry_added_after_directory_enumeration`. Nothing outside
the registered R-4.35 family appeared. The focused product proof is green; the Linux harness
aggregate is explicitly NOT claimed green.

Canonical-workflow differences: this was the token's focused proof, so it did not provision
the pinned clang-tidy-22 mirror, run the full Linux CTest population, or execute the workflow's
Catch2 count gate. No remote workflow ran. The candidate source and platform/topology match the
relevant Ubuntu 24.04 amd64, non-root, Docker-init, nofile-lift, GCC-Werror legs.

## 4. O-3 macOS T2/T3/T4 interaction set

On Darwin arm64, `cmake --preset ci-macos` and the complete build returned exit 0. The same
CTest rows 1 through 14 used by T4 reconstruction then returned:

```text
14/14 passed, 0 failed
MACOS_INTERACTION_STATUS=0
total 671.47 s
repo_git 0.96 s; repo_engine 15.57 s; harness-selftest 11.89 s; harness-e2 254.38 s
```

A fresh post-commit focused recheck also passed `repo_git` and `repo_engine` 2/2, 0 failed,
17.23 seconds, with candidate status clean.

## 5. O-4 exact guard-site falsifier — GUARD_LINE 142

`GUARD_LINE = 142`, the raw GCC diagnostic line of the new guard's own
`GitInvokeOptions` initializer at the fixed source topology.

- O-4a: fixed tree plus temporary NSDMI-less member `t4_nsdmi_guard_probe`, real `-Werror`:
  build exit 2. This proves the policy fired and is claimed as nothing more.
- O-4b: same tree with warning demoted after `-Werror`, every TU compiled, exit 0. The
  mechanically enumerated 14-pair set contained exactly once
  `(tests/test_repo_engine.cpp, 142, GitInvokeOptions, t4_nsdmi_guard_probe)`.
- O-4c: temporary member retained and only the new guard case removed, same demoted full-TU
  build, exit 0. The exact line-142 tuple was absent; the 13 pre-existing caller tuples
  remained.
- O-4d: temporary member removed and guard restored. Real-policy focused build passed,
  `repo_engine` passed 1/1, and all three files returned to the fixed digests in section 1.

All transient O-4 mutations were fully reverted before the source commit.

## 6. O-5 byte-scope proof and state

Versus `29120d0`, exactly three paths change. The `types.hpp` diff is exactly one removed line
and its braced replacement. Current and base SHA-256 values match for `classify.cpp`,
`capture.cpp`, `eligibility.cpp`, and `restore.cpp`. Removing only guard lines 141 through 147
from the candidate test file produces a byte-identical copy of base `test_repo_engine.cpp`,
proving the two `EngineSourceState` sites and all thirteen existing `GitInvokeOptions`
initializers are unchanged. `git diff --check` is clean.

The candidate branch and its isolated worktree are preserved, clean, local, and unpublished at
`6ba01ef`. The one named reusable validation container owned by this run was removed after its
receipts were retained; the final fresh container used `--rm`. No unrelated Docker resource was
pruned or removed. No remote CI, push, force-push, PR mutation, merge, publication, schema act,
deployment, or release occurred. The release hold is ABSOLUTE.

ACTIONS_GIT_REF: one bounded local source commit 6ba01ef on s4-matrix/arm1-t4, directly parented to authorized base 29120d0, with exactly the three dispatched paths; local disposable Docker and macOS validation; this report and one live-EOF INDEX row are the only docs-lane writes claimed here. No push, PR mutation, remote CI, merge, publication, schema, deployment, or release act
FINAL_GIT_STATUS_SHORT: candidate worktree clean at 6ba01ef; shared docs checkout preserves sibling-authored tracked and untracked state unchanged and unclaimed; only this relay and its one INDEX append belong to this docs act
RELAY_LINT: exact-file freshness; live INDEX EOF re-read immediately before append; full INDEX error set compared with its pre-append inherited baseline; cached diff check and explicit two-path docs commit; post-commit exact-file no-freshness verification

CARRY LIST:
- candidate `6ba01ef` directly on `29120d0`, exactly three authorized paths, local and unpublished
- O-1a real-policy RED exit 2; O-1b exact nineteen-row multiset exit 0 with no outside struct
- O-2 focused Linux product 2/2 green; harness aggregate non-green only on two registered R-4.35 family members
- O-3 macOS interaction 14/14 green, exit 0, 671.47 seconds
- O-4 `GUARD_LINE = 142`; exact positive tuple present once, negative-control tuple absent, restored GREEN at fixed digests
- O-5 exact three-file scope, one-line `types.hpp` delta, four callers and all prior sites byte-identical
- Planner adjudication then Orchestrator Stage-3 panel remain; no remote, integration, publication, deployment, schema, or release authority or act
