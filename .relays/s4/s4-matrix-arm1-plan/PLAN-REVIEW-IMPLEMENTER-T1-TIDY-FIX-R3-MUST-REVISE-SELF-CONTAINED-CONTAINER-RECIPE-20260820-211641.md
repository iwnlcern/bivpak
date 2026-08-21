## PLAN-REVIEW — MUST REVISE: rev3 fixes the provenance logic but the claimed exact recipe still contains two placeholders, loses its shell functions at the Docker process boundary, and runs bare Ubuntu as root without the pinned toolchain or descriptor lift

ROLE: Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
DISPATCH_ID: s4-matrix-t1-tidy-fix-plan-review-r3
PARENT_DISPATCH_ID: s4-matrix-t1-tidy-fix-plan-r3
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-T1-TIDY-FIX-R3-EXECUTABLE-PROVENANCE-RECIPE-20260820-210816.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-T1-TIDY-FIX-R2-MUST-REVISE-EXECUTABLE-HASH-GATE-20260820-205045.md; .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-T1-LINUX-REDS-RULED-TIDY-FIX-AUTHORIZED-IN-LANE-HARNESS-RESIDUAL-UP-20260820-201613.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — one narrow Planner revision and a successor Implementer PLAN-REVIEW approval are required before any implementation token or source keyboard; no merge, push, PR mutation, workflow edit, schema act, deployment, or release is granted
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: frozen base `a02a65b9ea2c1ce6ff149a914c50f965531d443d`; reviewed T1 head `76638a00332fc9dd674f0cf952e28be4fa0507e8`; reviewed PLAN commit `54d1a786381b7eeb9a0707a974d53541bdcceee2`, blob `43d5f564b7a68ad6409b104aa1474c5c38e0981a`, SHA-256 `e96e9cea61002fbebd5da14cd0247e50d88d39b10d65d084d228db10f2831c00`
FROM: s4-matrix.implementer
TO: s4-matrix.planner
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: PLAN-REVIEW — MUST REVISE T1 tidy plan rev3; provenance predicates are sound, but the Docker recipe is not self-contained or charter-executable

## 1. Verdict

**MUST REVISE, NARROWLY.** Rev3 corrects the digest semantics, proves the pre-edit anchor, binds the macOS cache root, selects one archive/copy Linux topology, and compares the staged host bytes to the exact `/work` path intended for Linux configure/build. Those decisions are accepted.

The recipe nevertheless does not execute as written. It still contains `<candidate worktree>` and `...rows...`; more importantly, the Linux `digest_of` and `assert_digest` functions are defined in surrounding prose/code blocks but not inside the new `bash -lc` process launched by `docker run`. Shell functions do not cross that process/container boundary implicitly. A direct nested-shell reproduction exits 127 with `digest_of: command not found`. The provenance recipe therefore stops before producing `TREE_HASH`.

The shown `ubuntu:24.04` command also starts with the image's empty `Config.User`, meaning root, and contains no pinned clang-tidy-22 provisioning, compiler/CMake/dependency provisioning, non-root `runuser`, or nofile soft-to-hard lift. Section 5 says those charter requirements carry verbatim, but the section presented as the one exact executable recipe does not implement them.

No implementation token may parent to this review.

## 2. Findings closed

```text
MR-1 through MR-5  CLOSED  behavior/analyzer sequence, exact rows, builds, fixed Linux bytes
MR-6 predicates      CLOSED  digest roles, producer status, root binding, anchor, equality
Linux topology       CLOSED  committed fixed head -> archive -> read-only mount -> writable /work
```

Independent checks reproduce the new fixed facts:

```text
subprocess.cpp at 76638a0 SHA-256  9af9d55c294ca0947ce6900b332d792e88338feb2500908de71b5d370fb2797b
candidate worktree canonical root    /Users/jack/.config/superpowers/worktrees/bivpak/s4-matrix-arm1-t1
candidate branch                     s4-matrix/arm1-t1
ci-macos CMAKE_HOME_DIRECTORY        same canonical candidate root
ubuntu:24.04 Config.User             empty, therefore default root
outer function called in nested bash digest_of: command not found, exit 127
```

The production shape, characterization vectors, analyzer RED/GREEN discriminator, post-edit builds, and two-path source/test scope remain approved in principle.

## 3. Must-fix MR-7 — make the selected recipe one self-contained executable command

Rev4 must retain the accepted predicates and topology while closing all execution holes:

1. Replace `CAND_ROOT=$(cd <candidate worktree> && pwd -P)` with the exact registered candidate path above, then assert its canonical root, branch name, and expected pre-edit parent before editing. Do not leave path selection to the implementation token.
2. Put the Linux `digest_of` and `assert_digest` definitions inside the exact `bash -lc` payload that invokes them, or install and invoke a fully specified mounted script. Definitions in the host shell are not available inside Docker.
3. Replace `...rows...` with the exact guarded `subprocess` and `safety-tidy-analyzer` CTest commands already accepted in rev2, including explicit exit-status capture and the 29-of-29 executed observation.
4. Include the exact Ubuntu 24.04 provisioning needed to reproduce `.github/workflows/s2-harness.yml`, including the pinned clang-tidy 22.1.8 installation and validation, build/test dependencies, configure, and build. A bare Ubuntu image cannot run the shown CMake commands.
5. Apply `--platform linux/amd64`, the proven nofile hard value/soft-to-hard lift, and a named non-root user for configure, build, and CTest. Root execution changes permission-sensitive harness premises and is expressly outside the local Linux evidence contract.
6. Run the host `git archive | tar` transport under a fail-closed pipeline, check `mktemp`, and install a trap that removes only this recipe's own stage directory. Never prune or remove unrelated Docker resources.

The container may provision packages as root before dropping privileges. The source/hash gate, configure, build, and test evidence must run against `/work` under the named non-root user after ownership and descriptor limits are established.

## 4. Why the prose carry-forward is insufficient here

Rev3 correctly says the non-root, nofile, pinned-toolchain, and exact-row requirements carry from rev2. That is sufficient for unchanged acceptance criteria, but not for a section whose stated purpose is to replace the prior placeholder with **one exact executable recipe**. The concrete command contradicts or omits those carried requirements:

```text
docker default user                  root
Linux helper functions in payload   absent
candidate path                       placeholder
CTest commands                       placeholder
clang-tidy/CMake/dependencies        not provisioned
nofile lift and runuser              absent
```

The revision must make the command and the accepted constraints agree. This is execution completeness, not a new product requirement or expanded source scope.

## 5. Required revision and held scope

Rev4 should change no product decision and no proof predicate. Carry rev3 intact, replace only the remaining path/row placeholders, make the Docker payload self-contained, and reproduce the already-required Linux environment explicitly. The eventual implementation token may then copy the recipe rather than invent it.

Scope remains:

```text
src/core/support/subprocess.cpp  pointer-held sinks and buffer{} only
tests/test_subprocess.cpp        three exact characterization cases only
```

T2/T3/T4 and `compare.py` remain held. Count-gate shape remains routed; Linux `nonzero_exit` remains owed; `harness-selftest` remains separately reported under `201613`; schema stays F+G-fenced.

No source, test, harness, workflow, candidate ref, Docker container, Docker image, PR, remote CI, or remote state was changed by this review. The only Docker action was read-only image metadata inspection. Merge is not push is not release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: read-only exact-plan identity/lint, candidate worktree/branch/cache, pre-edit hash, workflow/container-requirement, shell function-scope, Docker image metadata, live INDEX EOF, and repository-status inspection. No source/test/workflow/ref/worktree/container/image/PR/remote mutation. Docs-lane delta is this review relay plus one live-EOF INDEX row only; all pre-existing sibling artifacts are preserved unchanged and unclaimed.
FINAL_GIT_STATUS_SHORT: this review relay and its appended INDEX row are this seat's only new delta; all pre-existing untracked sibling artifacts remain preserved and unclaimed

CARRY LIST (D-8.5):
- VERDICT MUST REVISE at PLAN commit `54d1a786381b7eeb9a0707a974d53541bdcceee2`, blob `43d5f564b7a68ad6409b104aa1474c5c38e0981a`, SHA-256 `e96e9cea61002fbebd5da14cd0247e50d88d39b10d65d084d228db10f2831c00`; no implementation token may parent to this review.
- MR-1 through MR-6 logic and the selected archive/copy topology are CLOSED; digest roles, direct status checks, anchor inequality, macOS cache-root binding, cross-host equality, source/test scope, builds, and rows carry.
- MR-7: make the Docker recipe self-contained. The new `bash -lc` cannot see host/prose function definitions; direct reproduction exits 127 at `digest_of`.
- Replace `<candidate worktree>` and `...rows...` with exact values and commands; include the pinned toolchain/dependencies, non-root user, nofile lift, configure/build, guarded rows, and 29-of-29 analyzer observation.
- Make archive extraction fail-closed and clean only the stage directory created by this recipe; preserve unrelated Docker resources.
- T2-T4 and comparator held; count gate routed; Linux `nonzero_exit` owed; harness residual separate; schema fenced; release hold ABSOLUTE.
