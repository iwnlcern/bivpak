## SITREP — T4 reconstructed onto FINAL T3, all six scout post-conditions hold and macOS is green, but Ubuntu GCC exposes a new NSDMI-class build defect; STOP before product edit and route the bounded corrective

ROLE: Implementer
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-matrix-t4-reconstructed-linux-nsdmi-blocker
PARENT_DISPATCH_ID: s4-matrix-wave-a-t3-relens-pass-head-final-reconstruct-t4
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-T3-RELENS-PASS-HEAD-FINAL-70601FC-ACCEPTED-RECONSTRUCT-T4-20260822-140530.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/SITREP-PLANNER-T4-SCOUTED-SIX-RISK-PATHS-NSDMI-FIX-WOULD-DROP-20260822-141055.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — the reconstructed T4 candidate has a real Ubuntu GCC build defect, so the Wave-A STOP rule fired before any corrective product edit. A bounded corrective needs the normal authorization and review cycle. No merge, push, PR mutation, schema act, publication, deployment, or release; the release hold is ABSOLUTE
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: FINAL T3 `70601fc201b3c41d2542d82399787b5febcbf03c`; old T4 `cb1f6254e1a275fd5e56ba91547d762145b32fa7`; reconstructed local T4 `29120d09891bfc46e80635c2212befa22a0e2604`
FROM: s4-matrix.implementer
TO: s4-matrix.planner, s4.orchestrator-planner
CC: operator, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: SITREP — T4 reconstructed locally at 29120d0 with P1-P6 satisfied and macOS 14 of 14 green; Ubuntu 24.04 amd64 under Docker init fails the focused build on eight omitted budget_override initializers; STOP and route bounded corrective

## 1. Reconstruction result and exact identity

The existing eighteen-commit T4-own chain was replayed from old T3 `d7d32f9` onto FINAL T3
`70601fc`. The local branch moved from `cb1f625` to `29120d0`; the old published remote ref
remains exactly `cb1f625`, so the prior chain is retained and nothing was published.

```text
old range       d7d32f9..cb1f625     18 commits
new range       70601fc..29120d0     18 commits
local ref       s4-matrix/arm1-t4    29120d09891bfc46e80635c2212befa22a0e2604
remote ref      origin/s4-matrix/arm1-t4
remote value    cb1f6254e1a275fd5e56ba91547d762145b32fa7    UNCHANGED
```

Ten append-only `.relays/s4/INDEX.md` conflicts were resolved by union: both tails retained,
each T4 row inserted in timestamp order, no existing row rewritten, reordered, or dropped.
The one product conflict was `src/core/repo/git.hpp`; its resolution composes T4's
`allow_user_protocol{false}` and trace API with T2's landed
`empty_config_keys{}` NSDMI fix.

`git range-diff` maps all eighteen old commits to eighteen reconstructed commits. The five
initial repo-engine commits and the two later driver-fold product commits are patch-equivalent.
The broad engine-fold product commit differs only at the deliberately carried
`empty_config_keys{}` brace. The product path set is identical. Seventeen of nineteen final
product files are byte-identical to old T4; the only two composed differences are the expected
`CMakeLists.txt` base additions and `git.hpp` NSDMI brace.

## 2. Planner scout post-conditions P1-P6 — all verified at the reconstructed bytes

```text
P1 PASS  git.hpp contains exactly the carried `empty_config_keys{}` fix
P2 PASS  git.cpp contains static GIT_CONFIG_KEY_0 through 4 isolation and T4's
         RequestTrace, per-call protocol pin, and dynamic empty-key transport
P3 PASS  content-level, not count-level: all six base repo_git tests remain with
         their base assertions; T4 adds protocol assertions and transport opt-in coverage
P4 PASS  CMake retains base version_floor source and mirror gate and adds all T4
         repo-engine sources plus repo_engine test registration
P5 PASS  types.hpp and temp_dir.hpp retain base content while adding T4 engine state,
         issue types, promisor note/state, and byte-vector helper
P6 PASS  all thirteen T4-only paths are additions against 70601fc with zero deletions
```

The three Wave-A-wide folds were measured rather than assumed. `fold Wave A engine findings`
is replayed with the one NSDMI carry above; `neutralize repo-local Git command drivers` and
`complete Git driver enumeration` are patch-equivalent in `range-diff`. Their code and tests
were not already supplied by base `70601fc`, which lacks the T4 repo-engine and `git_exec`
paths; they therefore had to ride the reconstructed chain.

## 3. macOS interaction verification — green

The old T4 focused baseline passed before replay. At reconstructed `29120d0`, the focused
T2/T3/T4 interaction set passed first, followed by the complete non-safety product and harness
set:

```text
old focused baseline        repo_engine                         PASS  16.78 s
reconstructed focused       repo_git, repo_engine, selftest     3 of 3 PASS  29.03 s
reconstructed product set   CTest rows 1 through 14             14 of 14 PASS
  biv_tests                                                      PASS 404.13 s
  harness-selftest                                               PASS  16.39 s
  harness-e2                                                     PASS 261.91 s
total reconstructed product-set time                            712.11 s
```

## 4. Ubuntu interaction verification — real build defect, STOP

The Linux run used an exact `git archive` of `29120d0` in a disposable
`ubuntu:24.04` container with `--platform linux/amd64` and Docker `--init`. The logged topology
is `pid1=docker-init`, `arch=x86_64`, non-root user `biv`, and soft and hard `nofile` both
`1048576`. `/mnt/c/tmp` was provisioned writable. The unrelated pre-existing
`bivpak-slice-a-d885530-ci` container remained running and untouched.

The CI preset configured under GCC 13.3.0, then the focused product build stopped in T4 code:

```text
src/core/repo/git_exec.hpp:24
  std::optional<std::chrono::milliseconds> budget_override;

src/core/repo/classify.cpp    2 GitInvokeOptions designated initializers omit budget_override
src/core/repo/capture.cpp     6 GitInvokeOptions designated initializers omit budget_override

GCC diagnostic at each site:
  error: missing initializer for member
  'biv::repo::GitInvokeOptions::budget_override'
  [-Werror=missing-field-initializers]

focused Linux build exit     2
Linux tests                  NOT RUN because the required targets did not build
```

This is T4-owned: `GitInvokeOptions`, both failing callers, and the omitted member are all in
T4's own slice. It is not a dropped-base symptom: P1-P6 all pass, and the failure occurs in
T4-only `classify.cpp` and `capture.cpp`. macOS Clang did not diagnose the omission; Ubuntu
GCC with the CI warning policy does.

The likely bounded repair is the same NSDMI class just corrected on T2: give
`budget_override` an explicit empty default in `git_exec.hpp`, or explicitly initialize it at
all eight callers. I did not choose between those product shapes and changed no product byte.
The authorization/review cycle should select the shape and require a GCC must-be-red baseline,
the corrected focused Linux build and tests under Docker `--init`, the macOS interaction set,
and a regression guard that prevents another later optional member from reopening the class.

Canonical-workflow differences are explicit: this diagnostic run used the canonical Ubuntu
24.04 amd64 CI preset and warning policy but intentionally set
`BIVHARNESS_REQUIRE_CLANG_TIDY=OFF`, did not provision the pinned clang-tidy-22 mirror, and
selected only `repo_git`, `repo_engine`, and `harness-selftest`. The build failed before those
tests could run. It is evidence of this compiler defect, not a claim that the canonical full
Linux workflow passed.

## 5. State and evidence

T4 is reconstructed but NOT FINAL, NOT Stage-3-panelable, and NOT merge-ready. The local
candidate remains at `29120d0`, clean and unpublished, pending disposition. T1 `00c06d9`, T2
`7688bbd`, and T3 `70601fc` remain FINAL and unchanged. No remote CI, push, PR mutation, merge,
schema act, publication, deployment, or release occurred. The release hold is ABSOLUTE.

Durable local evidence is retained under the ignored root
`.superpowers/sdd/t4-reconstruct-iD45AHvj/`, including the old baseline, `range-diff`, final-file
byte comparison, macOS configure/build/focused/full-product logs, exact candidate archive, and
the Ubuntu `--init` failure log. No unsuffixed stale twin was created.

ACTIONS_GIT_REF: local-only rebase of `s4-matrix/arm1-t4` from old head `cb1f625` onto accepted T3 `70601fc`, yielding `29120d0`; ten INDEX conflicts unioned under the standing append-only rule and one `git.hpp` product conflict composed under P1. Read-only replay verification, macOS builds/tests, and one disposable Ubuntu 24.04 amd64 Docker-init run followed. `origin/s4-matrix/arm1-t4` remains `cb1f625`; no push, PR mutation, merge, remote CI, schema, publication, deployment, or release. Docs lane: this relay and its INDEX row ride one explicit-path commit
FINAL_GIT_STATUS_SHORT: T4 worktree clean at `29120d0`; main docs checkout has this relay and its INDEX row as this seat's only staged paths at commit time, with all sibling-authored untracked paths preserved and unclaimed

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-T4-RECONSTRUCTED-MACOS-GREEN-LINUX-NSDMI-BLOCKER-20260822-143923.md` to `s4-matrix.planner` and `s4.orchestrator-planner`
- T4 reconstructed locally from old `cb1f625` onto FINAL T3 `70601fc` as `29120d0`; eighteen old commits map to eighteen new commits; origin T4 remains exactly old `cb1f625`; local and unpublished
- ten INDEX conflicts resolved by append-only union and one product conflict composed in `git.hpp`; product path set identical, seventeen of nineteen product files byte-identical to old T4, expected differences only CMake base additions and the carried `empty_config_keys{}` brace
- P1-P6 all PASS by content: T2 NSDMI brace retained; five-key isolation plus T4 transport retained; all base repo_git tests and assertions retained with T4 additions; CMake both directions; shared type/helper content composed; thirteen T4-only paths additive with zero deletions
- three Wave-A-wide folds measured: broad fold differs only by the required NSDMI carry; neutralize-found and completed enumeration patch-equivalent; base lacks their T4 engine and git_exec paths, so they were required, not duplicate
- macOS reconstructed interaction evidence GREEN: focused 3 of 3 in 29.03 seconds and full product/harness rows 1 through 14 at 14 of 14 in 712.11 seconds, including biv_tests 404.13 seconds and E2 261.91 seconds
- Linux exact candidate under disposable Ubuntu 24.04 amd64, Docker init, non-root, raised nofile: configure PASS, focused build EXIT 2 before tests because eight T4 designated initializers omit later GitInvokeOptions budget_override and GCC 13 promotes missing-field-initializers to error; two sites classify.cpp and six capture.cpp
- STOP before product edit. Bounded corrective authorization and review required; likely shape choice is one NSDMI default at budget_override versus eight explicit caller initializers, with GCC red baseline, Docker-init Linux green, macOS interaction, and a class regression guard required. T4 reconstructed but NOT FINAL or panelable; release hold ABSOLUTE
