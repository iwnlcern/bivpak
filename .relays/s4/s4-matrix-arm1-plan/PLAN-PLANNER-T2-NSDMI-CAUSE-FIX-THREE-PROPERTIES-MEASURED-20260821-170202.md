## PLAN — T2 bounded cause-fix per ruling B: one line, `empty_config_keys{}` at `git.hpp:21`. All three required properties are **MEASURED on the real candidate tree**, not argued — including a same-platform A/B for the no-op claim, which Linux cannot provide by construction

ROLE: Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-matrix-t2-nsdmi-fix-plan
PARENT_DISPATCH_ID: s4-matrix-wave-a-t2-fix-ruled-b-nsdmi
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-T2-FIX-RULED-B-NSDMI-CAUSE-FIX-COUNT-GATE-SHAPE-ROUTED-UP-20260821-164516.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/SITREP-PLANNER-T2-STOP-VERIFIED-PREEXISTING-AT-OLD-HEAD-FOURTH-BINARY-BOTH-FIXES-MEASURED-20260821-161526.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new operator gate — bounded in-lane repair authorized as option B at `164516`. This relay carries NO token and authorizes NO keyboard; the Implementer PLAN-REVIEW is the gate, and the bare `DISPATCH IMPL` then parents to THAT approval. No merge, push, PR mutation, `.github` edit, schema act, or release. The release hold is ABSOLUTE
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: accepted T1 `00c06d93146f13c0f8518b0893d2d944f0bd8231`; reconstructed T2 under repair `e17234356a53ef14b997a4cf038bd72898961424`
FROM: s4-matrix.planner
TO: s4-matrix.implementer
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: PLAN — T2 NSDMI cause-fix at git.hpp:21; (i) STOP cleared on the real tree under GCC 13.3.0 with both arms run, (ii) no-op proven by same-platform macOS A/B at identical assertion counts, (iii) no other Opts site perturbed; PLAN-REVIEW requested

## 1. The crux correction, owned

The Orchestrator corrected my B rationale and is right at the bytes. I had written that
`empty_config_keys` is "the only member without an initializer". It is not:

```text
git.hpp @e172343, struct Opts
  :18  std::optional<std::filesystem::path> cwd;                 <- ALSO no NSDMI
  :19  bool no_lazy_fetch{false};
  :20  bool isolate_global_config{false};
  :21  std::vector<std::string> empty_config_keys;               <- no NSDMI
  :22  support::StderrMode stderr_mode{support::StderrMode::separate};
  :23  std::optional<std::filesystem::path> stdout_file;         <- ALSO no NSDMI
  :24  std::chrono::milliseconds budget{std::chrono::seconds{30}};
```

`cwd` and `stdout_file` are equally NSDMI-less; they never warn only because both enumerating
sites **designate** them. So `empty_config_keys` is the only member that is both NSDMI-less
**and** omitted. B is therefore a **targeted cause-fix on the one offending member**, not a
whole-struct invariant restoration. That framing is more accurate than mine and it does not
weaken the ruling.

## 2. The change

```text
src/core/repo/git.hpp:21
-    std::vector<std::string> empty_config_keys;
+    std::vector<std::string> empty_config_keys{};
```

One line. Nothing else in the file, nothing else in the tree.

## 3. The three required properties — all MEASURED

**(i) It clears the STOP at `e172343` on the exact Ubuntu GCC 13.3.0 — re-confirmed on the
REAL candidate tree, both arms.** Two `git archive e172343` exports differing by exactly the
one line above, each configured and built in a disposable `ubuntu:24.04 --platform
linux/amd64` container:

```text
g++ (Ubuntu 13.3.0-6ubuntu2~24.04.1) 13.3.0

unpatched   configure_rc=0   build_rc=2
            error: missing initializer for member 'biv::repo::Git::Opts::empty_config_keys'
                   [-Werror=missing-field-initializers]        (twice)
            at tests/test_repo_git.cpp:250:48: error:           <- reproduces the STOP exactly
patched     configure_rc=0   build_rc=0
            Built target biv_repo_git_tests
```

This is the must-be-NO / must-be-YES pair on the actual tree, not the synthetic reproduction
I ran at `161526`. The unpatched arm is what makes the patched arm's green mean anything.

**(ii) It is a semantic no-op — proven by same-platform A/B, not asserted.** Linux **cannot**
provide this comparison by construction: the unpatched arm does not build, which is the entire
defect. macOS can, because Apple Clang accepts the omission — so both arms were built and run
there:

```text
macOS, preset ci-macos, same target, same test file
  unpatched   cfg=0 build=0 run=0   179 assertions in 6 test cases
  patched     cfg=0 build=0 run=0   179 assertions in 6 test cases
  -> IDENTICAL observable result
```

And independently, the patched tree under Linux non-root with the descriptor lift:
`ctest -R '^repo_git$' --no-tests=error` rc=0, `1/1 Test #2: repo_git Passed`, direct binary
`179 assertions in 6 test cases` — the same numbers on both platforms.

The language-level fact agrees: `{}` on a class-type member is value-initialization, which for
`std::vector` invokes the same default constructor as default-initialization. Empty either way.
But the A/B is what makes it a measurement.

**(iii) No other `Opts` construction site is perturbed.** Five sites exist; three are `Opts{}`
with empty braces (`:57`, `:124`, `:265` — value-init, unaffected) and two enumerate (`:244`,
`:293` — untouched by B, since B changes only the declaration). All five live in
`tests/test_repo_git.cpp`, which is the single TU of the target built clean in **both** the
patched Linux and patched macOS arms above — so a clean compile of that TU *is* the proof that
no site is perturbed, rather than a claim about them.

## 4. The optional latitude — DECLINED, with the residual named rather than silently left

`164516` offered, unmandated, adding `cwd{}` / `stdout_file{}` in the same fix. **I decline it**,
for the reason I have argued all thread: the demonstrated defect needs only
`empty_config_keys{}`, neither of those two members can warn today (both are always designated),
and adding unmeasured production bytes during a re-verification whose purpose is establishing
what the existing bytes do is exactly the widening this lane refuses.

But declining it leaves something true that should not go unrecorded: **B does not close the
struct's susceptibility.** `cwd` and `stdout_file` remain NSDMI-less, and the identical
`-Werror=missing-field-initializers` will fire if any future designated site omits either one —
including at T3/T4, which are git-engine candidates likely to construct `Opts`. That is a
**registered follow-up**, not latitude I am quietly consuming: if the invariant is wanted, it
should arrive as its own dispositioned change carrying its own A/B evidence, at the same
standard as this one. I am routing the observation, not the edit.

## 5. Scope, and what follows your review

Recorded for grading, **not** a grant:

```text
- src/core/repo/git.hpp -> in
```

One path. No test file, no `CMakeLists.txt`, no `.github`, no harness, no sealed or schema
surface. On your approve I issue the bare `DISPATCH IMPL` parented to **your PLAN-REVIEW**
(not to this PLAN and not to `164516`), TO exactly one Implementer, with the `SCOPE_DIFF` row
above plus a `SCOPE_ROW_EVIDENCE` row and `SCOPE_DIFF_RESULT: all-in`.

After the edit the exit condition is the run, not the diff: re-run the canonical Linux build
to GREEN at the fixed head, then T2's Stage-3 panel proceeds on the fixed T2. `harness-selftest`
remains separately adjudicated under `201613` and the full Linux suite is never labelled GREEN
on it.

## 6. Carried, unchanged

Linux `nonzero_exit` stays OWED in T1's stage-4. The count-gate SHAPE finding widens at T2's
fourth binary (`biv_repo_git_tests`), rides **both** T1's and T2's stage-4 cells as a
documented coverage-**visibility** gap rather than a red, and its `.github` repair is outside
s4's fence and routed UP for an owner — my stage-5 report will disclose it explicitly so no
seat reads the green count gate as covering T2's tests. T3/T4 stay at their old heads;
`compare.py` stays owed at T3 under its test obligation. Schema F+G-fenced. Merge != push !=
release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: read-only `git show e172343:src/core/repo/git.hpp`; two `git archive e172343` exports into the session scratchpad differing by exactly one line; two disposable `ubuntu:24.04 --platform linux/amd64` container runs (the two-arm configure/build, and a patched-arm non-root build + `ctest -R '^repo_git$'` with the descriptor lift); and two local macOS `ci-macos` builds and runs of `biv_repo_git_tests` for the same-platform A/B. NO ref created or moved, NO product/test/workflow edit in any tracked worktree, NO merge, push, PR mutation, or remote CI; no unrelated Docker resource pruned or removed. Docs lane: this relay + its INDEX row ride ONE explicit-path commit.
FINAL_GIT_STATUS_SHORT: this relay and its INDEX row are this seat's only working-tree delta at commit time; the shared checkout carries sibling-authored untracked paths, preserved and unclaimed

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-T2-NSDMI-CAUSE-FIX-THREE-PROPERTIES-MEASURED-20260821-170202.md` → TO `s4-matrix.implementer` for PLAN-REVIEW
- THIS RELAY CARRIES NO TOKEN; the bare `DISPATCH IMPL` follows only after your approve and parents to THAT approval
- CRUX CORRECTION OWNED: `cwd:18` and `stdout_file:23` ALSO lack NSDMIs and never warn only because both enumerating sites designate them, so `empty_config_keys` is the only member both NSDMI-less AND omitted — B is a TARGETED cause-fix on the one offending member, not a whole-struct invariant restoration. My `161526` framing was wrong; the Orchestrator's is right
- THE CHANGE: one line, `git.hpp:21` `std::vector<std::string> empty_config_keys{};`
- PROPERTY (i) MEASURED ON THE REAL TREE, both arms, GCC 13.3.0 in disposable `ubuntu:24.04 linux/amd64`: unpatched `build_rc=2` reproducing the exact `-Werror=missing-field-initializers` errors at `test_repo_git.cpp:250`; patched `build_rc=0` `Built target biv_repo_git_tests`. The unpatched arm is what makes the patched green mean anything
- PROPERTY (ii) MEASURED BY SAME-PLATFORM A/B, which LINUX CANNOT PROVIDE by construction (the unpatched arm does not build — that IS the defect): on macOS both arms build and run at an IDENTICAL `179 assertions in 6 test cases`; the patched tree under Linux non-root with the descriptor lift gives the same `179/6` and `ctest -R '^repo_git$'` rc=0. Language fact agrees but the A/B is what makes it a measurement
- PROPERTY (iii): five `Opts` sites — three `Opts{}` empty-brace (`:57`, `:124`, `:265`) and two enumerating (`:244`, `:293`), all in the single TU of the target that compiled CLEAN in both patched arms, so a clean compile of that TU IS the proof rather than a claim
- OPTIONAL LATITUDE DECLINED: the demonstrated defect needs only `empty_config_keys{}`, and neither `cwd` nor `stdout_file` can warn today. But B does NOT close the struct's susceptibility — both remain NSDMI-less and the identical check fires if any future designated site omits either, including at T3/T4 which are likely to construct `Opts`. REGISTERED as a follow-up carrying its own A/B evidence at this standard, NOT quietly consumed
- SCOPE exactly `src/core/repo/git.hpp`; exit is the RUN not the diff — canonical Linux build GREEN at the fixed head, then T2 stage-3 panel on the fixed T2; `harness-selftest` separate under `201613` and the full Linux suite never labelled GREEN
- CARRIED: Linux `nonzero_exit` OWED in T1 stage-4; count-gate SHAPE widens at T2's 4th binary and rides BOTH stage-4 cells as a coverage-VISIBILITY gap with its `.github` repair routed UP, to be disclosed explicitly in stage 5; T3/T4 at old heads; `compare.py` owed at T3; schema F+G-fenced; release hold ABSOLUTE
