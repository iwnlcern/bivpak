## SITREP — T2 NSDMI cause-fix complete in one bounded local commit; exact Linux RED becomes fixed-head build and eight-site repo_git GREEN, with retained receipts and the known harness-selftest residual separate

ROLE: Implementer
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: s4-matrix-t2-nsdmi-impl-complete
PARENT_DISPATCH_ID: s4-matrix-t2-nsdmi-impl
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/IMPL-PLANNER-T2-NSDMI-FIX-DISPATCH-20260821-185207.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — Planner review and the T2 Stage-3 panel are next; no merge, push, force-push, PR mutation, remote CI, publication, schema act, deployment, or release authority is carried here
BASE: reconstructed T2 `e17234356a53ef14b997a4cf038bd72898961424`; fixed T2 `7688bbd00b10e3f6f1e8f501a1094ba17f85ce67`
FROM: s4-matrix.implementer
TO: s4-matrix.planner
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: COMPLETE — one-line T2 NSDMI fix at 7688bbd; canonical Ubuntu build and repo_git green at the fixed head with 42 retained receipts; eight construction sites confirmed; harness-selftest separately retains the adjudicated three-failure flaky residual

## 1. Exact commit and scope

The isolated `s4-matrix/arm1-t2` worktree is clean at:

```text
7688bbd00b10e3f6f1e8f501a1094ba17f85ce67  fix(repo): default-initialize empty Git config keys
```

Its sole parent is `e17234356a53ef14b997a4cf038bd72898961424`. The complete
base-to-fixed diff names exactly `src/core/repo/git.hpp`, with one deletion and one
insertion:

```diff
-    std::vector<std::string> empty_config_keys;
+    std::vector<std::string> empty_config_keys{};
```

Fixed `git.hpp` SHA-256 is
`90c8602d840b3064c3c5ad423f63a522befec429eb299d38e24b8d47dc79a43d`.
No `cwd{}`, `stdout_file{}`, test, CMake, workflow, harness, schema, or other product
edit was taken.

## 2. TDD RED to GREEN on the real tree

Before the production edit, a Git archive of exact head `e172343` ran in a disposable
`ubuntu:24.04 --platform linux/amd64` container as non-root `biv`, with
`nofile_soft=1048576` raised to `nofile_hard=1048576` and GCC 13.3.0:

```text
CONFIGURE_RC=0
BUILD_RC=2
tests/test_repo_git.cpp:250:48  missing initializer for Git::Opts::empty_config_keys
tests/test_repo_git.cpp:299:41  missing initializer for Git::Opts::empty_config_keys
```

The diagnostic count is exactly two. This existing build is the failing test observed
before production changed.

After the minimal edit, the local macOS `biv_repo_git_tests` target built and passed before
commit. The fixed-head repeat records:

```text
macOS BUILD_RC=0
macOS CTEST_RC=0
macOS DIRECT_RC=0
All tests passed (179 assertions in 6 test cases)
```

## 3. Canonical fixed-head Linux evidence

The fixed-head Git archive, not the host working tree, ran in a fresh disposable
`ubuntu:24.04 --platform linux/amd64` container. The run installed and reverified all
eight checksum-pinned immutable Clang 22 packages, observed clang-tidy 22.1.8 and GCC
13.3.0, used non-root `biv`, provisioned the writable WSL fixture root, and lifted the
soft descriptor limit to the inherited hard value.

```text
VENV_RC=0
PIP_RC=0
CONFIGURE_RC=0
BUILD_RC=0
REPO_GIT_CTEST_RC=0
REPO_GIT_DIRECT_RC=0
```

The full CMake build reaches 100 percent and includes
`Built target biv_repo_git_tests`. Focused CTest records one of one `repo_git` passed,
and the direct Linux binary records the same `179 assertions in 6 test cases` as macOS.

The fixed archive contains exactly eight `Git::Opts` constructions:

```text
empty-brace:        57, 124, 265
plain default-init: 76, 147, 228
designated:         244, 293
```

Their single translation unit compiles clean under the canonical warning-as-error build.
The completion claim is bound to eight sites, not the rev0 five-site instrument reach.

## 4. Retained evidence and preserved r0 harness defect

The complete evidence chain is retained at:

```text
/Users/jack/Programming/bivpak/.superpowers/sdd/t2-nsdmi-dl58XcCh
```

`RECEIPTS.sha256` contains 42 entries. Fresh verification returns every entry `OK`;
the receipt-file SHA-256 is
`f13208aa4f8c0827a915dddedf2415f30cb2ec32867c9c7ec1bcdf0b855e3592`.

The first fixed-head Linux wrapper stopped before configure with `PIP_RC=1`. Investigation
found a scratch-driver generation defect, not a product or dependency defect: JavaScript
newline escaping folded six patch markers into literal `+` command arguments, and pip
reported `Invalid requirement: '+'`. That r0 driver, log, status, and pip error remain
retained and hashed. No product byte changed. A new r1 driver removed the malformed
continuations, used distinct receipt names, passed `bash -n`, and produced the accepted
status set above. No receipt was overwritten.

## 5. Separate Linux harness-selftest adjudication

`harness-selftest` was run separately after the green fixed-head product build:

```text
HARNESS_SELFTEST_RC=8
3 failed, 968 passed, 3 skipped
```

The three failing rows are the already adjudicated E3 scandir-stop mutation residuals:

- `test_c1_zero_session_control_reds_on_file_inserted_at_scandir_stop`
- `test_run_e3_session_inserted_at_scandir_stop_reds_c1_before_open`
- `test_credential_scanner_detects_entry_added_after_directory_enumeration`

This report does not label the full Linux suite green. The candidate product build and
focused `repo_git` target are green; the separately ruled flaky selftest residual remains
visible and unchanged.

## 6. Boundary and requested next gate

Please review exact local head `7688bbd00b10e3f6f1e8f501a1094ba17f85ce67`, the one-line scope, the real-tree
RED-to-GREEN pair, the fixed-head macOS and canonical Linux target results, and the retained
receipt chain before routing T2 to its Stage-3 panel.

The count-gate shape remains a coverage-visibility carry for T2 Stage-4; `biv_tests` count
movement is not claimed as coverage of this fourth test binary. T3/T4 remain at their old
heads, `compare.py` remains owed at T3, Linux `nonzero_exit` remains owed in T1 Stage-4,
and schema stays F+G-fenced. No GitHub Actions, remote CI, push, force-push, merge, PR
mutation or comment, publication, deployment, tag, or release occurred. The release hold is
ABSOLUTE.

ACTIONS_GIT_REF: created one local candidate commit 7688bbd00b10e3f6f1e8f501a1094ba17f85ce67 on s4-matrix/arm1-t2; ran local macOS and disposable Ubuntu 24.04 amd64 evidence; downloaded only the workflow's immutable toolchain release assets for local verification; retained ignored evidence under /Users/jack/Programming/bivpak/.superpowers/sdd/t2-nsdmi-dl58XcCh; no merge, push, force-push, PR mutation, remote CI, workflow, schema, publication, deployment, tag, or release action. Docs lane is this relay plus one live-EOF INDEX append in one explicit-path commit.
RELAY_LINT: exact-file freshness before docs commit and no-freshness after; live INDEX EOF re-read before append; full INDEX lint with inherited historical defects disclosed and preserved.
FINAL_GIT_STATUS_SHORT: candidate worktree clean at 7688bbd00b10e3f6f1e8f501a1094ba17f85ce67; shared main retains sibling-authored untracked relays and migration note unchanged and unclaimed; only this completion relay and its one INDEX append belong to this seat.

CARRY LIST:
- fixed local T2 head `7688bbd00b10e3f6f1e8f501a1094ba17f85ce67`, one commit after e172343, scope exactly `src/core/repo/git.hpp`
- fixed source SHA-256 `90c8602d840b3064c3c5ad423f63a522befec429eb299d38e24b8d47dc79a43d`
- retained evidence root `/Users/jack/Programming/bivpak/.superpowers/sdd/t2-nsdmi-dl58XcCh`; 42 receipts; `RECEIPTS.sha256` digest `f13208aa4f8c0827a915dddedf2415f30cb2ec32867c9c7ec1bcdf0b855e3592`
- real-tree Linux RED configure zero and build two with exactly two missing-initializer diagnostics becomes fixed-head configure, full build, repo_git CTest, and direct binary all zero; macOS build, CTest, and direct binary also zero; both direct binaries 179 assertions in 6 cases
- exact eight-site census retained: three empty-brace, three plain default-init, two designated
- harness-selftest separately rc 8 with the adjudicated 3 failed, 968 passed, 3 skipped residual; full Linux suite not called green
- request Planner review and T2 Stage-3 panel; no integration, remote, publication, schema, deployment, or release authority follows
