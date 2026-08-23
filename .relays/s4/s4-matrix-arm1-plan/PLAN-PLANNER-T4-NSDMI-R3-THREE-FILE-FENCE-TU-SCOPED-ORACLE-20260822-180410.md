## PLAN rev3 — the three-file fence and the TU-scoped oracle as ruled at `174122`, with one precision the ruling's shorthand elides: `types.hpp` is NOT a T4-owned file. It exists at FINAL T3 and carries base content; only the STRUCT is T4's. So O-5 binds the `types.hpp` diff to exactly one line rather than trusting a whole-file claim

ROLE: Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-matrix-t4-nsdmi-fix-plan-r3
PARENT_DISPATCH_ID: s4-matrix-wave-a-t4-fence-extended-third-file-tu-scoped-oracle
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-T4-FENCE-EXTENDED-THIRD-FILE-ENGINESOURCESTATE-TU-SCOPED-ORACLE-20260822-174122.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-T4-O1B-EXACT17-FAIL-TWO-EXTRA-ENGINE-SOURCE-STATE-ROUTED-20260822-171058.md; .relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-T4-NSDMI-R2-SEVENTEEN-PAIRS-DUAL-BASELINE-20260822-161333.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new operator gate — `174122` is the Orchestrator scope decision I routed and it rules the three-file fence, the minimal cause-fix, and the TU-scoped oracle expressly. This relay carries NO token; an Implementer PLAN-REVIEW approve is required and the bare token parents to THAT approval. No merge, push, PR mutation, schema act, deployment, or release. The release hold is ABSOLUTE
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: reconstructed T4 `29120d09891bfc46e80635c2212befa22a0e2604` on FINAL T3 `70601fc201b3c41d2542d82399787b5febcbf03c`
SUPERSEDES: PLAN `s4-matrix-t4-nsdmi-fix-plan-r2` at blob `a1af036fc654bd2be7038e438398fcf38c879688`, SHA-256 `8c91caed7d2f06caf8316275011bdd9be161af370d1fc8dccb24a95d803c87c4` (superseded by the fence extension, not by a review defect); both re-derived at this seat
FROM: s4-matrix.planner
TO: s4-matrix.implementer
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: PLAN rev3 — three-file fence (git_exec.hpp + types.hpp + tests/test_repo_engine.cpp), minimal EngineSourceState cause-fix at types.hpp:192, TU-scoped O-1b with a 19-pair oracle and a struct-closure STOP; and O-5 tightened because types.hpp exists at FINAL T3 and carries base content — the struct is T4-owned, the file is not

## 1. One precision on the ruling, offered as a correction to its shorthand

`174122` extends the fence to `types.hpp` on the grounds that "`EngineSourceState` is T4's OWN
struct (absent at T3), so fixing it is the candidate greening its own build, not a base edit."
**The struct claim is exactly right. The file claim would not be**, and the ruling does not
quite make it — but a reader could take it that way, so I am pinning it:

```text
src/core/repo/types.hpp at FINAL T3 70601fc      EXISTS
  struct EngineSourceState occurrences            0
src/core/repo/types.hpp at T4 29120d0            EXISTS, 6251 bytes
  struct EngineSourceState occurrences            1   <- T4 added the STRUCT to a SHARED file
```

So the fence now includes a file that carries **base content T4 did not author**. Editing it is
still correct — the edit lands inside T4's own struct — but "T4-owned struct" and "T4-owned
file" are different guarantees, and only the first holds. O-5 therefore binds the `types.hpp`
delta to **exactly one line** rather than resting on a whole-file ownership claim. That is the
same base-added-since-fork discipline that produced the T4 scout, applied to the file the fence
just grew into.

## 2. The edits — three files, three changes

```text
src/core/repo/git_exec.hpp     :24  std::optional<std::chrono::milliseconds> budget_override{};
                               :25  std::span<const std::string> empty_config_keys{};
src/core/repo/types.hpp        :192 std::vector<std::string> neutralized_git_config_keys{};
tests/test_repo_engine.cpp          + the GitInvokeOptions class guard (rev2 §4, unchanged)
```

All three NSDMIs are provable behavioural no-ops: `std::optional<T>{}` is the empty state the
default constructor gives; `std::span<const T>{}` is the empty span; `std::vector<T>{}` is the
empty vector. Every omitting site already receives exactly these values by default
construction, and every naming site is unaffected because its own initializer wins.

**`repo_path` and `penumbra_paths` are deliberately NOT touched.** They are named at both
`:840` and `:865`, they warn nowhere today, and NSDMI'ing them would pre-empt the enlarged
R-4.41 that m-1 owns — the identical logic that kept `Git::Opts` out of this cycle. Zero caller
edits: option (b)'s call-site initializers are rejected on the cause-over-symptom grounds this
lane has now ruled three times.

## 3. O-1b — scoped to the translation units, which is the generator fix

```text
O-1a  CANONICAL RED
      untouched 29120d0 under the real -Wall -Wextra -Werror
      EXPECT nonzero exit and the missing-field-initializers diagnostic class

O-1b  TU-SCOPED ENUMERATE-ALL
      identical bytes/compiler/environment; -Wno-error=missing-field-initializers appended
      AFTER -Werror; EVERY governed TU of the O-2 focused build compiled to completion
      EXPECT exit zero absent any other error
      ORACLE: enumerate every missing-field-initializer pair the build reports across ALL
      governed TUs, each bound by FILE, LINE, MEMBER and STRUCT.  Struct identity is a
      PROPERTY of each pair, never the filter that defines the set.
      EXPECTED TODAY: 19 pairs -- GitInvokeOptions 17, EngineSourceState 2 (:840, :865).
      CLOSURE STOP: if ANY reported pair names a struct outside {GitInvokeOptions,
      EngineSourceState}, STOP and route.  Do not fix it, do not widen the oracle.
      Any missing, extra, duplicate or differently-bound pair likewise STOPS.
LIMIT -fmax-errors=0 proves within-TU continuation only, never whole-population build reach.
```

The closure check is what makes this self-validating. rev2's oracle could be wrong about its own
population because it was defined by a struct I chose; this one is defined by what the compiler
compiles, and it announces any struct I failed to anticipate instead of silently excluding it.
That is the structural cure for four turns of the same reach defect, and it is the reason I am
not simply promising to be more careful.

## 4. Remaining obligations

```text
O-2  Linux focused build AND tests GREEN at the fixed head: disposable ubuntu:24.04
     --platform linux/amd64, non-root, Docker --init (035347/R-4.40), nofile SOFT raised to the
     inherited HARD (R-4.31 arm (a)).  Residuals classified against the registered R-4.35
     four-member family; anything outside STOPS.  No whole-suite-green claim.
O-3  macOS T2/T3/T4 interaction set GREEN with counts and exit status.
O-4  the guard a real discriminator in C++ predicates: confirm at RUN TIME that
     biv_repo_engine_tests carries -Wall -Wextra -Werror; a TEMPORARY NSDMI-less member ->
     NONZERO build whose diagnostic NAMES that member; removal -> build AND test GREEN with
     git_exec.hpp restored to its fixed digest.  Any other error is not the discriminator, STOP.
O-5  NO-OP AND SCOPE, three files:
       exactly THREE changed files vs 29120d0
       src/core/repo/types.hpp diff vs 29120d0 is EXACTLY ONE LINE -- the added {} at :192.
         Every other struct and byte in that shared file byte-identical.
       classify.cpp, capture.cpp, eligibility.cpp, restore.cpp byte-identical to 29120d0
       the two EngineSourceState call sites tests/test_repo_engine.cpp:840 and :865 UNCHANGED
       all 13 GitInvokeOptions initializers unchanged (the guard's case is a 14th, not an edit)
```

Any obligation that fails STOPS the cycle and routes; none may be reconciled into a pass.

## 5. Fence

In scope, exactly three: `src/core/repo/git_exec.hpp`, `src/core/repo/types.hpp`,
`tests/test_repo_engine.cpp`. Not in scope: the four repo caller sources, `git.hpp`/`Git::Opts`,
`repo_path`/`penumbra_paths` within `EngineSourceState`, any other struct in `types.hpp`, any
other production byte, `.github/`, the schema, the harness, T4's other files, and the stage-5
report's contents.

No token here. Ceremony: rev3 → Implementer PLAN-REVIEW → my bare token parented to that
approval, TO one Implementer, with SCOPE_DIFF rows and a SCOPE_ROW_EVIDENCE row per IN path for
exactly the three rows.

Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: none — no edits made at this seat; no branch, ref or worktree moved and no candidate exists. Read-only: `git cat-file -e` and `git show | grep -c` of `src/core/repo/types.hpp` at `70601fc` (file present, `EngineSourceState` count 0) and at `29120d0` (count 1); `git cat-file -s` and `git show | shasum` of all three fence files at `29120d0`; `git show | grep -n` locating `neutralized_git_config_keys` at `types.hpp:192`; and `git rev-parse`/`git show` to re-derive rev2's blob and SHA-256 before superseding. No merge, push, PR mutation, or remote CI. Docs lane: this relay + its INDEX row ride ONE explicit-path commit.
FINAL_GIT_STATUS_SHORT: this relay and its INDEX row are this seat's only working-tree delta at commit time; `git status --porcelain` over `harness/`, `src/`, `tests/`, `CMakeLists.txt` is empty; the shared checkout carries sibling-authored untracked paths, preserved and unclaimed
RELAY_LINT: exact-file WITH freshness immediately before commit; INDEX tail re-read before appending; `--index` diffed against the pre-append blob; `--relay-root` required to name no error against this relay; `substantive_actions_ref` and `implementation_work_claimed` both measured FALSE. Commit gated by logical AND.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-T4-NSDMI-R3-THREE-FILE-FENCE-TU-SCOPED-ORACLE-20260822-180410.md` → TO `s4-matrix.implementer`
- ONE PRECISION ON THE RULING'S SHORTHAND: `174122` extends the fence to `types.hpp` because "EngineSourceState is T4's OWN struct (absent at T3), so fixing it is the candidate greening its own build, not a base edit." The STRUCT claim is exactly right; a FILE claim would not be. MEASURED: `types.hpp` EXISTS at FINAL T3 `70601fc` with `struct EngineSourceState` count 0, and exists at `29120d0` at 6251 bytes with count 1 — T4 added the STRUCT to a SHARED file. The fence now includes a file carrying BASE content T4 did not author; editing it is still correct because the edit lands inside T4's own struct, but T4-owned-struct and T4-owned-file are different guarantees and only the first holds
- SO O-5 BINDS THE `types.hpp` DELTA TO EXACTLY ONE LINE rather than resting on a whole-file ownership claim — the same base-added-since-fork discipline that produced the T4 scout, applied to the file the fence just grew into
- THE EDITS, three files: `git_exec.hpp:24` `budget_override{}` and `:25` `empty_config_keys{}`; `types.hpp:192` `neutralized_git_config_keys{}`; and the `GitInvokeOptions` class guard in `tests/test_repo_engine.cpp` unchanged from rev2. All three NSDMIs are provable no-ops — `std::optional<T>{}` the empty state, `std::span<const T>{}` the empty span, `std::vector<T>{}` the empty vector — since every omitting site already receives exactly these by default construction and every naming site is unaffected because its own initializer wins
- `repo_path` AND `penumbra_paths` DELIBERATELY NOT TOUCHED: named at both `:840` and `:865`, warning nowhere today, and NSDMI'ing them would pre-empt the enlarged R-4.41 m-1 owns — the identical logic that kept `Git::Opts` out of this cycle. ZERO caller edits; option (b) call-site initializers rejected on the cause-over-symptom grounds this lane has now ruled three times
- O-1b IS SCOPED TO THE TRANSLATION UNITS, which is the GENERATOR fix: enumerate every missing-field-initializer pair the demoted build reports across ALL governed TUs, each bound by FILE, LINE, MEMBER and STRUCT, with struct identity a PROPERTY of each pair and NEVER the filter defining the set; expected today 19 pairs (GitInvokeOptions 17, EngineSourceState 2 at `:840`/`:865`); CLOSURE STOP if ANY reported pair names a struct outside {GitInvokeOptions, EngineSourceState} — do not fix it, do not widen the oracle — and any missing, extra, duplicate or differently-bound pair likewise STOPS. `-fmax-errors=0` proves within-TU continuation only, never whole-population reach
- WHY THE CLOSURE CHECK MATTERS: rev2's oracle could be wrong about its own population because a struct I chose defined it; this one is defined by what the COMPILER COMPILES and announces any struct I failed to anticipate instead of silently excluding it. That is the structural cure for four turns of the same reach defect and the reason I am not simply promising to be more careful
- O-5 NO-OP AND SCOPE across THREE files: exactly three changed files vs `29120d0`; the `types.hpp` diff EXACTLY ONE LINE with every other struct and byte in that shared file byte-identical; `classify.cpp`, `capture.cpp`, `eligibility.cpp`, `restore.cpp` byte-identical; the two `EngineSourceState` call sites at `:840` and `:865` UNCHANGED; all 13 `GitInvokeOptions` initializers unchanged with the guard's case a 14th rather than an edit
- FENCE exactly three: `git_exec.hpp`, `types.hpp`, `tests/test_repo_engine.cpp`. NOT the four repo callers, NOT `git.hpp`/`Git::Opts`, NOT `repo_path`/`penumbra_paths`, NOT any other struct in `types.hpp`, no other production byte, no `.github/`, no schema, no harness, not T4's other files, not the stage-5 report contents. SUPERSEDES rev2 at blob `a1af036fc654bd2be7038e438398fcf38c879688` / SHA-256 `8c91caed7d2f06caf8316275011bdd9be161af370d1fc8dccb24a95d803c87c4` — superseded by the FENCE EXTENSION, not by a review defect — both re-derived here. NO TOKEN: rev3 → Implementer PLAN-REVIEW → my bare token parented to THAT approval with THREE scope rows and per-row evidence. T1 `00c06d9` / T2 `7688bbd` / T3 `70601fc` FINAL; T4 `29120d0` clean, local, unpublished, no candidate; R-4.38 binary inventory my stage-5 obligation; schema F+G-fenced; no remote CI, push, PR mutation, merge, publication, deployment or release; release hold ABSOLUTE
