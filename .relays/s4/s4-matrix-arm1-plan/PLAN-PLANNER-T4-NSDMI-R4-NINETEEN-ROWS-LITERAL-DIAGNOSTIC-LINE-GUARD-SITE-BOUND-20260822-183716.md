## PLAN rev4 — the nineteen rows are now IN this plan, literal and complete; LINE is defined as the RAW GCC DIAGNOSTIC LINE and I took the values from the retained manifest rather than hand-mapping, which is what MR-2 forbade; and O-4 is rebuilt so it cannot pass unless the new guard site itself fires

ROLE: Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-matrix-t4-nsdmi-fix-plan-r4
PARENT_DISPATCH_ID: s4-matrix-t4-nsdmi-fix-plan-review-r3
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-T4-NSDMI-R3-MUST-REVISE-ORACLE-LITERALS-LINE-ANCHOR-GUARD-DISCRIMINATOR-20260822-181116.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-T4-FENCE-EXTENDED-THIRD-FILE-ENGINESOURCESTATE-TU-SCOPED-ORACLE-20260822-174122.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new operator gate — the three-file fence, the minimal cause-fix and the TU-scoped population are all ruled at `174122` and closed at review r3; rev4 repairs only the proof contract. This relay carries NO token; an Implementer PLAN-REVIEW approve is required and the bare token parents to THAT approval. No merge, push, PR mutation, schema act, deployment, or release. The release hold is ABSOLUTE
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: reconstructed T4 `29120d09891bfc46e80635c2212befa22a0e2604` on FINAL T3 `70601fc201b3c41d2542d82399787b5febcbf03c`
SUPERSEDES: PLAN `s4-matrix-t4-nsdmi-fix-plan-r3` at blob `2c974824fdeceb2a122ff1ec7ac7c03e761e79e2`, SHA-256 `f7c6372b1dde600f21bf49912100dd25e3b696f73a11cfa8e39ace970e1804bf` (MUST REVISE)
FROM: s4-matrix.planner
TO: s4-matrix.implementer
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: PLAN rev4 — all nineteen expected pairs literalized in the operative plan with multiplicity; LINE canonically defined as the raw GCC diagnostic line with values taken from the retained manifest 1d96e795 rather than derived; O-4 rebuilt into four arms binding the temporary-member RED to the new guard site and adding a guard-removal negative control

## 1. MR-1 and MR-2 accepted, and they are the same defect wearing two coats

MR-1: rev3 said each pair is bound by FILE, LINE, MEMBER and STRUCT and then supplied
`GitInvokeOptions 17` — a count — leaving the seventeen bindings in a superseded document. **I
wrote that the total must never be the oracle, and then made the total the oracle for
seventeen-nineteenths of the set.** A missing site plus a differently-bound same-struct site
preserves `17` and is exactly what the closure rule exists to catch.

MR-2: rev3 said LINE is exact without saying *which* line. GCC reports at the aggregate's
closing line; rev2's inherited census used the opening line. A literal comparison against
opening lines would have **rejected a correct run** — the oracle would have failed the truth.

Both are the same defect: I specified a predicate without specifying its terms. rev4 fixes it
by taking the values from the instrument's own output instead of from my reasoning.

## 2. The oracle — nineteen literal rows, LINE = raw GCC diagnostic line

**Canonical coordinate: the raw GCC 13 diagnostic line.** That is what the compiler emits and
what a mechanical comparison can consume without a hand-map. Initializer opening lines are NOT
the oracle and are not carried here, precisely so the two cannot be mixed silently.

**Provenance: these values are transcribed from the retained O-1b manifest**
`04-o1b-warning-manifest.txt`, SHA-256 `1d96e7957e870b711c8cb31d2cf622e082745b3b4b95b42441b0ae4b46546ea8`,
1462 bytes, verified at my seat. They are measured output, not derived by me from source.

```text
mult  FILE                            LINE  STRUCT             MEMBER
 1    src/core/repo/capture.cpp        38   GitInvokeOptions   budget_override
 1    src/core/repo/capture.cpp        91   GitInvokeOptions   budget_override
 1    src/core/repo/capture.cpp       111   GitInvokeOptions   budget_override
 1    src/core/repo/capture.cpp       155   GitInvokeOptions   budget_override
 1    src/core/repo/capture.cpp       292   GitInvokeOptions   budget_override
 1    src/core/repo/capture.cpp       388   GitInvokeOptions   budget_override
 1    src/core/repo/classify.cpp       70   GitInvokeOptions   budget_override
 1    src/core/repo/classify.cpp      114   GitInvokeOptions   budget_override
 1    src/core/repo/eligibility.cpp    67   GitInvokeOptions   budget_override
 1    src/core/repo/eligibility.cpp   109   GitInvokeOptions   budget_override
 1    src/core/repo/eligibility.cpp   182   GitInvokeOptions   budget_override
 1    src/core/repo/restore.cpp        33   GitInvokeOptions   budget_override
 1    src/core/repo/eligibility.cpp    67   GitInvokeOptions   empty_config_keys
 1    src/core/repo/eligibility.cpp   109   GitInvokeOptions   empty_config_keys
 1    src/core/repo/eligibility.cpp   182   GitInvokeOptions   empty_config_keys
 1    src/core/repo/restore.cpp        33   GitInvokeOptions   empty_config_keys
 1    tests/test_repo_engine.cpp      629   GitInvokeOptions   empty_config_keys
 1    tests/test_repo_engine.cpp      840   EngineSourceState  neutralized_git_config_keys
 1    tests/test_repo_engine.cpp      865   EngineSourceState  neutralized_git_config_keys
                                                     TOTAL UNIQUE PAIRS: 19
                        12 budget_override + 5 empty_config_keys + 2 neutralized_git_config_keys
```

Every row multiplicity 1. Note `eligibility` `:67`/`:109`/`:182` and `restore:33` each appear
twice — once per omitted member — which is precisely the overlap that made 17 wrong as a site
count and 19 right as a pair count.

## 3. O-1, restated

```text
O-1a  CANONICAL RED
      untouched 29120d0, real -Wall -Wextra -Werror
      EXPECT nonzero exit and the missing-field-initializers diagnostic class

O-1b  TU-SCOPED ENUMERATE-ALL
      identical bytes/compiler/environment; -Wno-error=missing-field-initializers appended
      AFTER -Werror; every governed TU of the O-2 focused build compiled to completion
      EXPECT exit zero absent any other error
      ORACLE the nineteen rows in section 2, compared as a MULTISET on
        (FILE, RAW_GCC_DIAGNOSTIC_LINE, STRUCT, MEMBER)
      Any missing, extra, duplicate or differently-bound row STOPS and routes.
      CLOSURE STOP: any row naming a struct outside {GitInvokeOptions, EngineSourceState}
        STOPS -- do not fix it, do not widen the oracle.
LIMIT -fmax-errors=0 proves within-TU continuation only, never whole-population reach.
```

## 4. MR-3 accepted — O-4 rebuilt so the guard must fire

The reviewer is right that rev3's `NONZERO + member name` can pass without the guard: the
existing thirteen `GitInvokeOptions` sites omit any newly appended member too, and the canonical
RED already stops in `classify.cpp`/`capture.cpp` before the build reaches the test target. That
predicate proves the mutation and the warning policy, not the guard. **A discriminator that
cannot distinguish its own subject from the background is the exact defect I have been applying
to everyone else's instruments all cycle.**

The guard's initializer line does not exist yet, so it cannot be pinned here. It is RECORDED at
implementation time and becomes the coordinate the arms below bind to.

```text
PRECONDITION  record GUARD_LINE = the raw GCC diagnostic line for the guard's own
              GitInvokeOptions initializer in tests/test_repo_engine.cpp at the fixed head.

O-4a  POLICY FIRES.  fixed head + a TEMPORARY NSDMI-less member on GitInvokeOptions, real
      -Wall -Wextra -Werror -> NONZERO exit.  (proves the policy, nothing more)

O-4b  THE GUARD SITE FIRES.  same tree, warning DEMOTED after -Werror so every TU compiles ->
      the enumerated pair set MUST CONTAIN
        (tests/test_repo_engine.cpp, GUARD_LINE, GitInvokeOptions, <temporary member>)
      Binding to the TU or to the member name alone is NOT sufficient and does not satisfy O-4b.

O-4c  NEGATIVE CONTROL.  temporary member RETAINED, the new guard TEST_CASE REMOVED, same
      demoted policy -> that exact pair MUST BE ABSENT.  Other diagnostics from pre-existing
      callers may remain and are expected; only the guard-site pair must vanish.
      This is what proves the guard produced it.

O-4d  RESTORE.  temporary member removed and the guard restored -> focused build AND test GREEN,
      and all three fence files at their fixed digests.
```

Any other compiler or test error is not the discriminator and STOPS.

## 5. Unchanged from rev3 and its ruling

The three-file fence; the two `GitInvokeOptions` NSDMIs at `git_exec.hpp:24`/`:25`; the minimal
`neutralized_git_config_keys{}` at `types.hpp:192` with `repo_path`/`penumbra_paths` untouched
and belonging to m-1's enlarged R-4.41; zero caller edits; O-2 (Linux focused build and tests
GREEN under Docker `--init` and the `nofile` lift, residuals classified against the registered
R-4.35 four-member family, anything outside STOPPING, no whole-suite-green claim); O-3 (macOS
T2/T3/T4 interaction GREEN with counts and exit); and O-5 — exactly three changed files, the
`types.hpp` diff EXACTLY ONE LINE with every other byte of that shared file identical, the four
repo callers byte-identical, and the two `EngineSourceState` call sites `:840`/`:865` unchanged.

## 6. Fence

Exactly three: `src/core/repo/git_exec.hpp`, `src/core/repo/types.hpp`,
`tests/test_repo_engine.cpp`. Not the four repo callers, not `git.hpp`/`Git::Opts`, not
`repo_path`/`penumbra_paths`, not any other struct in `types.hpp`, no other production byte, no
`.github/`, no schema, no harness, not T4's other files, not the stage-5 report's contents.

No token here. Ceremony: rev4 → Implementer PLAN-REVIEW → my bare token parented to that
approval, with three SCOPE_DIFF rows and a SCOPE_ROW_EVIDENCE row per IN path.

Merge is not push is not release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: none — no edits made at this seat; no branch, ref or worktree moved and no candidate exists. Read-only: located and verified the retained O-1b warning manifest at the T4 worktree evidence root (SHA-256 `1d96e7957e870b711c8cb31d2cf622e082745b3b4b95b42441b0ae4b46546ea8`, 1462 bytes, matching the Implementer's citation) and transcribed its nineteen measured pairs verbatim; plus `git rev-parse`/`git show` to re-derive rev3's blob and SHA-256 before superseding. No merge, push, PR mutation, or remote CI. Docs lane: this relay + its INDEX row ride ONE explicit-path commit.
FINAL_GIT_STATUS_SHORT: this relay and its INDEX row are this seat's only working-tree delta at commit time; `git status --porcelain` over `harness/`, `src/`, `tests/`, `CMakeLists.txt` is empty; the shared checkout carries sibling-authored untracked paths, preserved and unclaimed
RELAY_LINT: exact-file WITH freshness immediately before commit; INDEX tail re-read before appending; `--index` diffed against the pre-append blob; `--relay-root` required to name no error against this relay; `substantive_actions_ref` and `implementation_work_claimed` both measured FALSE. Commit gated by logical AND.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-T4-NSDMI-R4-NINETEEN-ROWS-LITERAL-DIAGNOSTIC-LINE-GUARD-SITE-BOUND-20260822-183716.md` → TO `s4-matrix.implementer`
- MR-1 AND MR-2 ACCEPTED, AND THEY ARE THE SAME DEFECT WEARING TWO COATS: rev3 said each pair is bound by FILE, LINE, MEMBER and STRUCT and then supplied `GitInvokeOptions 17`, a COUNT, leaving the seventeen bindings in a superseded document — I wrote that the total must never be the oracle and then made the total the oracle for seventeen-nineteenths of the set, where a missing site plus a differently-bound same-struct site preserves 17. And rev3 said LINE is exact without saying WHICH line: GCC reports at the aggregate's CLOSING line while rev2's census used the OPENING line, so a literal comparison against opening lines would have REJECTED A CORRECT RUN. Both are one defect — specifying a predicate without specifying its terms
- FIXED BY TAKING THE VALUES FROM THE INSTRUMENT, NOT FROM MY REASONING: LINE is canonically the RAW GCC 13 DIAGNOSTIC LINE, and all nineteen rows are transcribed verbatim from the retained O-1b manifest `04-o1b-warning-manifest.txt`, SHA-256 `1d96e7957e870b711c8cb31d2cf622e082745b3b4b95b42441b0ae4b46546ea8`, 1462 bytes, located and verified at my seat. Opening lines are NOT carried, precisely so the two coordinates cannot be mixed silently
- THE NINETEEN ROWS ARE NOW IN THE OPERATIVE PLAN with multiplicity 1 each: capture `:38 :91 :111 :155 :292 :388`, classify `:70 :114`, eligibility `:67 :109 :182`, restore `:33` for `GitInvokeOptions::budget_override` (12); eligibility `:67 :109 :182`, restore `:33`, test `:629` for `GitInvokeOptions::empty_config_keys` (5); test `:840 :865` for `EngineSourceState::neutralized_git_config_keys` (2). Eligibility and restore each appear TWICE, once per omitted member — the overlap that made 17 wrong as a SITE count and 19 right as a PAIR count. Compared as a MULTISET on (FILE, RAW_GCC_DIAGNOSTIC_LINE, STRUCT, MEMBER), with the closure STOP on any struct outside the two
- MR-3 ACCEPTED: rev3's `NONZERO + member name` can pass WITHOUT the guard, because the existing thirteen `GitInvokeOptions` sites omit any newly appended member too and the canonical RED already stops in `classify.cpp`/`capture.cpp` before the build reaches the test target — it proves the mutation and the policy, not the guard. A discriminator that cannot distinguish its own subject from the background is the exact defect I have been applying to everyone else's instruments all cycle
- O-4 REBUILT INTO FOUR ARMS around a recorded `GUARD_LINE` (the guard's initializer does not exist yet so it cannot be pinned here): O-4a policy fires (temp member + real `-Werror` -> NONZERO, proving the policy and nothing more); O-4b THE GUARD SITE FIRES (same tree, demoted so every TU compiles -> the enumerated set MUST CONTAIN `(tests/test_repo_engine.cpp, GUARD_LINE, GitInvokeOptions, <temporary member>)`, with binding to the TU or the member name alone explicitly NOT sufficient); O-4c NEGATIVE CONTROL (temp member RETAINED, the new guard TEST_CASE REMOVED -> that exact pair MUST BE ABSENT while other pre-existing-caller diagnostics may remain — this is what proves the guard produced it); O-4d RESTORE (temp removed, guard restored -> build AND test GREEN with all three fence files at their fixed digests)
- UNCHANGED: three-file fence; the two `GitInvokeOptions` NSDMIs at `git_exec.hpp:24`/`:25`; minimal `neutralized_git_config_keys{}` at `types.hpp:192` with `repo_path`/`penumbra_paths` untouched and belonging to m-1's enlarged R-4.41; zero caller edits; O-2 Linux under `--init` + `nofile` with R-4.35 classification and no suite-green claim; O-3 macOS interaction with counts and exit; O-5 exactly three changed files with the `types.hpp` diff EXACTLY ONE LINE, the four repo callers byte-identical, and `:840`/`:865` unchanged
- SUPERSEDES rev3 at blob `2c974824fdeceb2a122ff1ec7ac7c03e761e79e2` / SHA-256 `f7c6372b1dde600f21bf49912100dd25e3b696f73a11cfa8e39ace970e1804bf`. NO TOKEN: rev4 → Implementer PLAN-REVIEW → my bare token parented to THAT approval with three scope rows and per-row evidence. T1 `00c06d9` / T2 `7688bbd` / T3 `70601fc` FINAL; T4 `29120d0` clean, local, unpublished, no candidate; R-4.38 binary inventory my stage-5 obligation; schema F+G-fenced; no remote CI, push, PR mutation, merge, publication, deployment or release; release hold ABSOLUTE
