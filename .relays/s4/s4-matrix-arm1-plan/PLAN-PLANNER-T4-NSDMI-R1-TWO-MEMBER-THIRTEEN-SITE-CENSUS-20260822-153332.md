## PLAN rev1 — the two-member fix as ruled at `152652`, now with the corrected THIRTEEN-site census throughout and O-1 rewritten so the baseline instrument cannot repeat the defect that produced it. The guard's target is confirmed to carry `-Werror`, so the canary can actually fail

ROLE: Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-matrix-t4-nsdmi-fix-plan-r1
PARENT_DISPATCH_ID: s4-matrix-wave-a-t4-nsdmi-successor-ruled-two-member
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-T4-NSDMI-SUCCESSOR-RULED-TWO-MEMBER-MY-CENSUS-WAS-DEFECTIVE-TOO-20260822-152652.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-T4-NSDMI-B-EXTENDED-MUST-REVISE-AUTHORITY-THIRTEEN-SITE-CENSUS-20260822-150410.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new operator gate — `152652` is the Orchestrator successor ruling MR-1 required and it authorizes the two-member fix expressly. This relay carries NO token; an Implementer PLAN-REVIEW approve is required and the bare token parents to THAT approval. No merge, push, PR mutation, schema act, deployment, or release. The release hold is ABSOLUTE
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: reconstructed T4 `29120d09891bfc46e80635c2212befa22a0e2604` on FINAL T3 `70601fc201b3c41d2542d82399787b5febcbf03c`
SUPERSEDES: PLAN `s4-matrix-t4-nsdmi-fix-plan` at blob `9a05d18e31960e5153c0593efc9c4513b9f356cc`, SHA-256 `8a1db5b0e07ad1172b0de39e9b1e564cd5c8d34b6dcf9dd0c1370abec2181a5a` (MUST REVISE); both re-derived at this seat before superseding
FROM: s4-matrix.planner
TO: s4-matrix.implementer
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: PLAN rev1 — two-member NSDMI fix at git_exec.hpp:24-25 as expressly ruled, thirteen-site census bound throughout, O-1 rewritten to enumerate ALL warning sites so the baseline cannot repeat the build-log-bounded defect, guard at tests/test_repo_engine.cpp with its -Werror target confirmed at CMakeLists.txt:126, five obligations and a two-row fence

## 1. What changed from rev0

`152652` expressly rules the two-member fix, so MR-1's missing authority is supplied and rev1
binds exactly that disposition rather than proposing it. The orchestrator also corrected their
own `144729` census in the same way mine was corrected — they read `:24` and never enumerated
`:25`. Three seats reached the same defect from three instruments; the correction is now
common ground and rev1 carries it throughout rather than in a footnote.

```text
rev0 said        8 sites, all naming empty_config_keys  -> WRONG (the stopped build's subset)
rev1 binds      13 sites, FIVE of which omit empty_config_keys
```

## 2. The edit — as ruled

Two NSDMIs in `src/core/repo/git_exec.hpp`, no other production byte:

```cpp
  std::optional<std::chrono::milliseconds> budget_override{};   // :24
  std::span<const std::string> empty_config_keys{};             // :25
```

Both provable behavioural no-ops at every one of the thirteen sites: `std::optional<T>{}` is
value-initialization, identical to the default `nullopt`; `std::span<const T>{}` is the
default-constructed empty span. A site that NAMES the member is unaffected because its
initializer wins; a site that OMITS it gets the same value it already got by default
construction. Zero caller edits — option C stays rejected and is now moot.

## 3. The census, bound

```text
src/core/repo/capture.cpp       6   name empty_config_keys, omit budget_override   } the 8 that warned
src/core/repo/classify.cpp      2   name empty_config_keys, omit budget_override   }
src/core/repo/eligibility.cpp   3   OMIT empty_config_keys  (:67, :109, :180)      } the 5 the
src/core/repo/restore.cpp       1   OMIT empty_config_keys  (:30)                  } one-line B
tests/test_repo_engine.cpp      1   names budget_override, OMITS empty_config_keys } would leave red
                               --
                               13   12 production + 1 test
```

Verified tree-wide at `29120d0` at this seat, not taken from a build log.

## 4. The guard

```cpp
TEST_CASE("GitInvokeOptions members all carry default member initializers") {
  const biv::repo::GitInvokeOptions opts{.promisor = true};
  CHECK(opts.promisor);
  CHECK_FALSE(opts.restore);
  CHECK_FALSE(opts.allow_user_protocol);
  CHECK(opts.call_class == biv::repo::GitCallClass::local);
  CHECK_FALSE(opts.budget_override.has_value());
  CHECK(opts.empty_config_keys.empty());
}
```

In `tests/test_repo_engine.cpp`. Its power is the OMISSION, not the assertions: any future
member added without an NSDMI makes this translation unit fail on Linux CI immediately.

**The flag is confirmed, not assumed.** `CMakeLists.txt:123-127` defines
`biv_repo_engine_tests` from `tests/test_repo_engine.cpp`, and `:126` sets
`target_compile_options(biv_repo_engine_tests PRIVATE -Wall -Wextra -Werror)`.
`-Wextra` implies `-Wmissing-field-initializers` and `-Werror` promotes it, so the canary
can genuinely fail. O-4 still re-confirms it at run time rather than resting on this read.

Note `test_repo_engine.cpp:628` is itself one of the five omitting sites, so the guard's own
translation unit is reddened by the unfixed struct and greened by the fix.

Per `152652`, NO `Git::Opts` canary this cycle: it lives in `git.hpp` outside the fence, and
the class-wide question is R-4.41 at m-1. My rev0 raised it; the orchestrator disposed it; rev1
does not reopen it.

## 5. Proof obligations

```text
O-1  GCC MUST-BE-RED BASELINE at the UNFIXED 29120d0, and the instrument is itself the fix for
     the defect that produced this revision: compile TO COMPLETION so every site is surfaced --
     -Wno-error=missing-field-initializers (or -fmax-errors=0) so the build does not stop at the
     first batch -- then ENUMERATE the warning set and require it to equal the measured omitting
     subset: 8 warnings on budget_override (capture 6 + classify 2) and 5 on empty_config_keys
     (eligibility 3 + restore 1 + test 1).  Record the exact diagnostics and exit status.
     A baseline that stops early is the same instrument that produced the 8-of-13 census.

O-2  LINUX GREEN at the fixed head: focused build AND its tests, disposable ubuntu:24.04
     --platform linux/amd64, non-root, Docker --init (035347/R-4.40), nofile SOFT raised to the
     inherited HARD (R-4.31 arm (a)).  Classify every residual against the registered R-4.35
     four-member family; anything OUTSIDE it STOPS and routes.  No whole-suite-green claim.

O-3  MACOS INTERACTION SET (T2/T3/T4) GREEN at the fixed head, with counts and exit status.

O-4  THE GUARD IS A REAL DISCRIMINATOR, proven BOTH directions in a scratch copy:
       (a) confirm at RUN TIME that biv_repo_engine_tests compiles with
           -Wall -Wextra -Werror -- print it from the build command or compile database;
       (b) add a TEMPORARY NSDMI-less member to GitInvokeOptions -> build RED, naming it;
       (c) remove it -> GREEN.
     Restore-gate git_exec.hpp to its fixed digest after (b) and after (c).
     Assert the module imports/compiles before reading any mutation verdict: an ERROR is not a
     FAILURE and proves nothing.

O-5  NO-OP AND SCOPE bound to ALL THIRTEEN initializers.  Exactly TWO changed files vs 29120d0:
     src/core/repo/git_exec.hpp and tests/test_repo_engine.cpp.  classify.cpp, capture.cpp,
     eligibility.cpp and restore.cpp byte-identical to 29120d0.  All 13 existing initializers
     unchanged (the guard's new case is a 14th, not an edit to :628).
```

Any obligation that fails STOPS the cycle and routes; none may be reconciled into a pass.

## 6. Fence

In scope: `src/core/repo/git_exec.hpp` (two NSDMIs) and `tests/test_repo_engine.cpp` (the
guard). **Not** in scope: `classify.cpp`, `capture.cpp`, `eligibility.cpp`, `restore.cpp`,
`git.hpp`/`Git::Opts`, any other production byte, `.github/`, the schema, the harness, T4's
other files, and the stage-5 report's contents.

No token here. Ceremony: rev1 → Implementer PLAN-REVIEW → my bare token parented to that
approval, TO one Implementer, with SCOPE_DIFF rows and a SCOPE_ROW_EVIDENCE row per IN path for
exactly the two rows above.

Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: none — no edits made at this seat; no branch, ref or worktree moved. Read-only `git show` of `git_exec.hpp` and `CMakeLists.txt` at `29120d0`, a tree-wide `git grep -n 'GitInvokeOptions{'` census with per-file counts, reads of the five omitting bodies, and `git rev-parse`/`git show` to re-derive rev0's blob and SHA-256 before superseding. No merge, push, PR mutation, or remote CI. Docs lane: this relay + its INDEX row ride ONE explicit-path commit.
FINAL_GIT_STATUS_SHORT: this relay and its INDEX row are this seat's only working-tree delta at commit time; `git status --porcelain` over `harness/`, `src/`, `tests/`, `CMakeLists.txt` is empty; the shared checkout carries sibling-authored untracked paths, preserved and unclaimed
RELAY_LINT: exact-file WITH freshness immediately before commit; INDEX tail re-read before appending; `--index` diffed against the pre-append blob; `--relay-root` required to name no error against this relay; `substantive_actions_ref` and `implementation_work_claimed` both measured FALSE. Commit gated by logical AND.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-T4-NSDMI-R1-TWO-MEMBER-THIRTEEN-SITE-CENSUS-20260822-153332.md` → TO `s4-matrix.implementer`
- rev1 BINDS the two-member fix EXPRESSLY RULED at `152652` rather than proposing it, so MR-1's missing authority is supplied; SUPERSEDES rev0 at blob `9a05d18e31960e5153c0593efc9c4513b9f356cc` / SHA-256 `8a1db5b0e07ad1172b0de39e9b1e564cd5c8d34b6dcf9dd0c1370abec2181a5a`, both re-derived here first
- THE CENSUS IS NOW COMMON GROUND: the orchestrator corrected their own `144729` the same way mine was corrected — they read `:24` and never enumerated `:25`. THREE seats reached the same defect from three instruments, so rev1 carries the 13-site census THROUGHOUT rather than in a footnote: capture 6 + classify 2 name `empty_config_keys` and omit `budget_override` (the 8 that warned); eligibility 3 (`:67`,`:109`,`:180`) + restore 1 (`:30`) + test 1 (`:628`) OMIT `empty_config_keys` (the 5 one-line B would leave red)
- THE EDIT: `budget_override{}` at `:24` and `empty_config_keys{}` at `:25`, no other production byte. Both provable no-ops at ALL THIRTEEN sites — a site that NAMES the member is unaffected because its initializer wins, and a site that OMITS it gets the same value default construction already gave. ZERO caller edits; option C rejected and now moot
- THE GUARD's power is the OMISSION not the assertions, and THE FLAG IS CONFIRMED NOT ASSUMED: `CMakeLists.txt:123-127` defines `biv_repo_engine_tests` from `tests/test_repo_engine.cpp` and `:126` sets `-Wall -Wextra -Werror`, so `-Wextra` implies `-Wmissing-field-initializers` and `-Werror` promotes it and the canary CAN genuinely fail; O-4 still re-confirms at RUN TIME rather than resting on this read. `test_repo_engine.cpp:628` is itself one of the five omitting sites so the guard's own TU is reddened-then-greened by the fix
- NO `Git::Opts` CANARY this cycle per `152652`: it lives in `git.hpp` outside the fence and the class-wide question is R-4.41 at m-1. My rev0 raised it, the orchestrator disposed it, rev1 does not reopen it
- FIVE OBLIGATIONS with O-1 REWRITTEN AS THE FIX FOR THE INSTRUMENT THAT PRODUCED THIS REVISION: the baseline must compile TO COMPLETION (`-Wno-error=missing-field-initializers` or `-fmax-errors=0`) so every site is surfaced, then ENUMERATE the warning set and require it to EQUAL the measured omitting subset of 8 on `budget_override` and 5 on `empty_config_keys` — a baseline that stops early is the same instrument that produced the 8-of-13 census. O-2 Linux green under `--init` + `nofile` with residuals classified against R-4.35 and anything outside STOPPING, no suite-green claim; O-3 macOS interaction green with counts and exit; O-4 the guard proven both directions INCLUDING run-time flag confirmation, with restore gates and an import/compile assertion before any verdict because an ERROR is not a FAILURE; O-5 no-op bound to all 13 initializers, exactly TWO changed files, and `classify.cpp`/`capture.cpp`/`eligibility.cpp`/`restore.cpp` byte-identical
- FENCE: `git_exec.hpp` + `tests/test_repo_engine.cpp` ONLY; not the four caller files, not `git.hpp`/`Git::Opts`, no other production byte, no `.github/`, no schema, no harness, not T4's other files, not the stage-5 report contents. NO TOKEN here: rev1 → Implementer PLAN-REVIEW → my bare token parented to THAT approval with SCOPE_DIFF rows and SCOPE_ROW_EVIDENCE per IN path for exactly the two rows. T1 `00c06d9` / T2 `7688bbd` / T3 `70601fc` FINAL; T4 `29120d0` NOT final, NOT panelable; all heads LOCAL and UNPUBLISHED; schema F+G-fenced; no remote CI, push, PR mutation, merge, publication, deployment or release; release hold ABSOLUTE
