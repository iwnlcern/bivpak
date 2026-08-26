## REVIEW-FOLD2 — S-1 and P-1 folded; second replacement head requests the bounded three-lens check

ROLE: Implementer
PHASE: REVIEW-FOLD
AUTHORITY: fold-in-only
DISPATCH_ID: s4-matrix-wave-a-panel
PARENT_DISPATCH_ID: s4-matrix-wave-a-panel-disposition
IN_REPLY_TO: .relays/s4/s4-matrix-wave-a-panel/REVIEW-FOLD2-PLANNER-DISPATCH-20260807-194121.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no for this filing — the pair Planner's bounded lead/security/performance check at the second replacement head is next; merge remains operator-owned and the release hold is ABSOLUTE
DESIGN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-05-s4-matrix-arm1-design.md
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/plans/2026-08-06-s4-matrix-arm1-plan.md
FROM: s4-matrix.implementer
TO: s4-matrix.planner
CC: s4.orchestrator-planner, operator
SUBJECT: DONE_WITH_CONCERNS — S-1 and P-1 are folded on the linear stack with focused RED/GREEN and full local E2; one cumulative PR #20 publication follows; targeted three-lens check requested; merge/release held

FOLD_SCOPE:
- src/core/support/subprocess.cpp -> in
- tests/test_subprocess.cpp -> in
- src/core/repo/git.cpp -> in
- tests/test_repo_git.cpp -> in
- .relays/s4/s4-matrix-wave-a-panel/** -> in
- .relays/s4/INDEX.md -> in
FOLD_SCOPE_RESULT: all-in

DONE_WITH_CONCERNS

The second bounded fold is complete on the required linear topology:

- T1 P-1 commit `d691f9be89093c27f9b518cfd7dbbdccceacba2e`;
- T2 S-1 commit `792c110486ef2f66e475bbdaf1c0be47a0dbeb89`;
- restacked T3 head `a61f883`;
- restacked prior M1-M14 T4 product commit `97a21fb`;
- pre-edit REVIEW-FOLD2 scope commit `d11c49c` after restack; this final relay and
  INDEX row ride the next cumulative filing commit.

The scope artifact
`.relays/s4/s4-matrix-wave-a-panel/REVIEW-FOLD2-SCOPE-IMPLEMENTER-20260807-205837.md`
was written, exact-file linted, INDEX-appended, and committed at `0627567` before any
second-fold product or test edit. After the mandated lower-branch edits and restack it is
preserved at `d11c49c`. The exact `92bd09f..d11c49c` product/test delta is three files:
`src/core/support/subprocess.cpp`, `src/core/repo/git.cpp`, and
`tests/test_repo_git.cpp`; all are IN. The remaining two changed paths are this governed
scope artifact and its append-only INDEX row.

## P-1 — geometric subprocess growth restored

`ByteCapture::write` no longer calls
`bytes_.reserve(bytes_.size() + retained)` for every drain. The existing
`std::back_inserter` path therefore uses `std::vector`'s geometric growth again instead
of forcing an exact allocation and full-prefix copy for each 8 KiB chunk. This is the
one-line root-cause correction; capture caps, raw bytes, incomplete-output signaling,
and probe/Git policy are unchanged.

The dispatch explicitly made a new P-1 test optional because the observable behavior is
identical. I did not add a flaky wall-clock assertion or a source-text change detector.
The existing real 1 MiB dual-pipe drain case was run before and after the deletion, and
the complete nine-case subprocess target is green after it. `tests/test_subprocess.cpp`
was declared IN but required no edit.

## S-1 — command-executing repo-local config class closed

The injected Git config now carries five entries:

- `core.hooksPath=/dev/null`;
- `credential.helper=`;
- `core.sshCommand=/usr/bin/false`;
- `core.fsmonitor=`;
- `core.alternateRefsCommand=`.

`GIT_CONFIG_COUNT` is five and the preallocated environment capacity was adjusted for
the four added key/value strings. This remains process-command neutralization, not
URL/host policing; the sealed allowlist ruling is untouched.

The real hostile-config test creates an executable fsmonitor program that writes a
marker, installs it in the repo-local config, and runs the same
`status --porcelain=v2` request classification uses. Before the production fix it was
RED with six intended failures: count/key/value assertions for both missing entries and
the fsmonitor marker proving execution. After the fix the focused case passed 55
assertions and the marker remained absent. Removing the `core.fsmonitor` injected entry
re-enables the real program; removing the alternate-refs entry fails the explicit
request-boundary assertion.

## Verification at the cumulative head

- `biv_subprocess_tests`: 51 assertions in 9 cases passed;
- `biv_repo_git_tests`: 178 assertions in 6 cases passed;
- `biv_repo_engine_tests`: 286 assertions in 32 cases passed;
- fresh full command:
  `git diff --check && cmake --build --preset dev -j8 && ctest --preset dev -E '^safety-hardening$' --output-on-failure`;
- full result: 17/17 locally applicable CTest rows passed, zero failed, in 460.02
  seconds; `biv_tests` passed in 243.99 seconds, harness selftest in 9.64 seconds,
  harness E2 in 177.76 seconds, and Werror passed;
- the macOS preset configured ASan/UBSan, pinned clang-tidy, and fuzz smoke as skips.
  Linux ELF hardening remains excluded locally because Darwin has no applicable
  `readelf`; no unsupported platform verdict is claimed.

No GitHub workflow was triggered during editing, restacking, or local validation. Per
the operator's current direction, the cumulative T4 replacement will be published once
after this filing and the resulting final-head checks observed without reruns.

## Preserved boundaries and requested action

The optional TempDir atomic-id and environment-mutation guards, remote-name option
confusion, `<initializer_list>` IWYU nit, Wave-C warning/advisory integration flag, and
held zero-ref `capture_mode` cell were not folded. No harness/schema/CLI consumer,
Wave-B/C/D, new PR, merge, or release action was taken.

Planner TARGETED CHECK is requested against the final published PR #20 head, sized to
the `92bd09f` replacement baseline plus exactly S-1/P-1: lead verification and the
security and performance lenses only. On a green recorded check, the candidate can be
called panel-clean at that final head; this Implementer report grants no merge or
release authority.

ACTIONS_GIT_REF: P-1 `d691f9be89093c27f9b518cfd7dbbdccceacba2e`; S-1 `792c110486ef2f66e475bbdaf1c0be47a0dbeb89`; restacked T3 `a61f883`; restacked prior-fold T4 product `97a21fb`; pre-edit scope at restacked commit `d11c49c`; this relay and append-only INDEX row ride the final cumulative filing commit whose SHA lands in repository history after filing; one guarded force-with-lease publication to existing PR #20 follows; no merge/release
FINAL_GIT_STATUS_SHORT: cumulative T4 clean at `d11c49c` before this relay and INDEX append; origin/s4-matrix/arm1-t4 remains at `92bd09f9f8c8898d9a5121dc4f4466cd3b8109c0` until the single final publication

CARRY LIST:
- `.relays/s4/s4-matrix-wave-a-panel/REVIEW-FOLD2-IMPLEMENTER-S1-P1-FILED-20260807-211112.md` -> `s4-matrix.planner`
- `https://github.com/iwnlcern/bivpak/pull/20` at its final published replacement head -> bounded lead/security/performance check and CI observation only; merge/release held
