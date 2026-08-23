## SITREP — the STOP was correct and I concur: the two-member fix ALONE cannot green O-2, which I measured rather than inferred. `EngineSourceState` is production, all three of its members lack NSDMIs, and under the real `-Werror` policy the guard's own translation unit still fails. And the census I should have run four revisions ago says this is not a second instance — TWENTY-SIX structs carry NSDMI-less members

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-matrix-t4-stop-concurred-twentysix-struct-census-routed
PARENT_DISPATCH_ID: s4-matrix-t4-o1b-exact17-fail-two-extra-engine-source-state
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-T4-O1B-EXACT17-FAIL-TWO-EXTRA-ENGINE-SOURCE-STATE-ROUTED-20260822-171058.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-T4-O1-MULTISET-CORRECTED-REAL-ORCHESTRATOR-SEVENTEEN-20260822-160705.md; .relays/s4/s4-matrix-arm1-plan/IMPL-PLANNER-T4-NSDMI-GUARD-DISPATCH-20260822-163256.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — a scope decision that is NOT mine. Greening O-2 requires touching either `src/core/repo/types.hpp` (a THIRD file, outside the two-file fence) or the two caller sites inside the guard file. I frame both and recommend one; I do not take it. Separately, the 26-struct census materially enlarges R-4.41's scope and should reach m-1. No merge, push, PR mutation, schema act, deployment, or release. The release hold is ABSOLUTE
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: reconstructed T4 `29120d09891bfc46e80635c2212befa22a0e2604` on FINAL T3 `70601fc201b3c41d2542d82399787b5febcbf03c`; no candidate exists
FROM: s4-matrix.planner
TO: s4.orchestrator-planner
CC: operator, s4-matrix.implementer, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: STOP concurred and the oracle earned itself; measured that the two-member fix leaves the guard TU RED because EngineSourceState omits a third NSDMI-less member under the real -Werror; the reach defect is mine a fourth time (struct-scoped population vs TU-scoped warning set); 26 structs carry NSDMI-less members; three options framed, decision routed

## 1. The STOP was correct, and the oracle earned its cost

The Implementer stopped before any candidate existed, reverted both authorized hunks, and left
T4 clean at `29120d0` with `git diff --exit-code` 0 and both in-fence files at their pre-edit
digests. That is the binding behaviour rev2 asked for and it was honoured exactly.

**And the membership-bound oracle is why this is a two-line report instead of a mystery.** A
total-only oracle would have said "19 ≠ 17, stop" and left everyone guessing. Binding by file,
line and member named the two extras immediately —
`tests/test_repo_engine.cpp:840` and `:865`, member
`EngineSourceState::neutralized_git_config_keys`. The insistence that the total is not the
oracle paid for itself on its first run.

## 2. What I measured, because the consequence decides the ruling

`EngineSourceState` is **production**, not test — `src/core/repo/types.hpp:189` — and **all
three** of its members lack NSDMIs:

```text
struct EngineSourceState {            src/core/repo/types.hpp:189
  std::filesystem::path repo_path;                        NO NSDMI
  std::vector<std::filesystem::path> penumbra_paths;      NO NSDMI
  std::vector<std::string> neutralized_git_config_keys;   NO NSDMI
};
the two sites name TWO of three:
  tests/test_repo_engine.cpp:840  EngineSourceState{.repo_path = repo, .penumbra_paths = {}}
  tests/test_repo_engine.cpp:865  same shape
```

Measured on GCC 13.4.0 under the **real** target policy, not the demoted one:

```text
that exact shape, -Wall -Wextra -Werror
  error: missing initializer for member 'EngineSourceState::neutralized_git_config_keys'
  exit 2
with neutralized_git_config_keys{} added
  exit 0
```

**Therefore the authorized two-member fix alone cannot green O-2.** Both sites live in
`tests/test_repo_engine.cpp`, which `biv_repo_engine_tests` builds with `-Wall -Wextra -Werror`
at `CMakeLists.txt:126` — the very flag that makes the guard able to fail. The guard's own
translation unit stays red, so O-2 and O-4 cannot pass under the current two-file fence no
matter how correct the `GitInvokeOptions` edit is.

I measured this rather than reasoning from the demoted run's warnings, because "the warning
would obviously become an error" is the shape of assumption this cycle has punished four times.

## 3. The reach defect is mine, a fourth time

I scoped the oracle to `GitInvokeOptions` initializers. **The compiler's warning set is scoped
to the translation units it compiles**, not to the struct I happened to be reasoning about.
Those are different populations, and I bounded the oracle by the wrong one.

```text
T2       grep reach          'Opts{' could not match a plain declaration      5 of 8
rev0     stopped-build log   8 sites reported as the population               8 of 13
rev1     derived count       carried the stale 8 into the warning expectation 13 vs 17
rev2     struct-scoped       oracle bounded by ONE struct, not by the TUs     17 vs 19
```

Each correction fixed the instance and left the generator. The generator is: **I keep defining
the population by the thing I am thinking about instead of by the thing the instrument
measures.**

## 4. The census I should have run four revisions ago

Every struct in `src/core/repo/` and `src/core/support/` headers at `29120d0`, with at least
one NSDMI-less member:

```text
26 structs.
Among them: GitInvokeOptions (2 members), EngineSourceState (3), RepoEntry (15), Capture (4),
RepoRestoreRow (6), SpawnRequest (5), ProbeEvidence (5), Proof (4), Shallow (3), LocalRef (3),
Eligibility (3), ProbePhaseEvent (4), CaptureResult (2), ArtifactFile (2), Classification (2),
Discovery (2), RepoBoundary (2), NonCarriedRefsNote (2), CaptureEnvironment (2), EngineIssue (2),
Remote (2), UnknownNote (2), LocalRefRestoreRow (2), SpawnResult (2), ForcedPayload (1),
BivError (1).
```

**Instrument bounded honestly:** this is a regex over struct bodies in headers, validated on a
must-be-YES (`GitInvokeOptions` returns exactly its two known NSDMI-less members, not its four
NSDMI'd ones) and a must-be-NO (structs whose members all carry NSDMIs are absent). It is
indicative for routing, not an authoritative per-member census, and it does not tell you which
of the 26 actually **warn** — a warning fires only where an aggregate initializer OMITS an
NSDMI-less member in a compiled TU. Today we know of exactly two such structs in the
`biv_repo_engine_tests` dependency set: `GitInvokeOptions` (17 pairs) and `EngineSourceState`
(2 pairs).

**Why it matters anyway:** R-4.41 is registered as a repo-wide NSDMI-hygiene question arising
from *two option structs*. The real surface is 26 structs, and the warning population is a
function of struct definitions **times** initializer call sites. A per-instance fix strategy
will keep producing exactly this STOP, each costing a full plan → review → token cycle. That is
a fact m-1 should have when it disposes R-4.41, and I am routing it up rather than letting the
next seat rediscover it.

## 5. The decision, framed and not taken

```text
(a) MINIMAL CAUSE-FIX, fence +1 file
    add neutralized_git_config_keys{} in src/core/repo/types.hpp
    greens the TU; consistent with the cause-fix principle ruled twice (T2, T4);
    one line; provable no-op; but types.hpp is a THIRD file, outside the two-file fence
(b) IN-FENCE CALLER FIX
    name the member at tests/test_repo_engine.cpp:840 and :865
    needs NO fence change -- both sites are already in scope
    but it is option-C-shaped, which this lane rejected twice on cause-fix grounds,
    and it leaves EngineSourceState fragile for the next call site
(c) FULL CAUSE-FIX of EngineSourceState
    NSDMIs on all three members; strictly more than needed to green O-2
```

**I recommend (a)**: smallest change that greens the build, consistent with the principle
already ruled twice, and it fixes the cause rather than the symptom. The asymmetry with (b) is
real and worth naming — for `GitInvokeOptions` the cause file was inside the fence, here it is
not — which is precisely why this is a scope decision and not mine.

**Either way the oracle must be re-derived**, and this time from the TU population rather than
from a struct: the successor's O-1b expectation should be computed by enumerating every
missing-field-initializer pair the demoted build reports across the governed TUs, with the
struct identity as a *property* of each pair rather than as the filter that defines the set.

## 6. State

No candidate exists; T4 is clean at `29120d0` and unmoved. O-2, O-3, O-4 and O-5 were correctly
not run after the stop. T1 `00c06d9`, T2 `7688bbd`, T3 `70601fc` FINAL. All heads LOCAL and
UNPUBLISHED. R-4.38's binary inventory stays my stage-5 obligation. Schema F+G-fenced. Merge is
not push is not release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: none — no edits made at this seat; no branch, ref or worktree moved and no candidate exists. Read-only: `git grep`/`git show` of `src/core/repo/types.hpp` and `tests/test_repo_engine.cpp` at `29120d0`, a validated regex census over every header in `src/core/repo/` and `src/core/support/` at `29120d0`, and one disposable `gcc:13 --platform linux/amd64` `--init` container compiling a two-arm standalone reproduction of the `EngineSourceState` shape under the real `-Wall -Wextra -Werror` policy. No unrelated Docker resource pruned or removed. No merge, push, PR mutation, or remote CI. Docs lane: this relay + its INDEX row ride ONE explicit-path commit.
FINAL_GIT_STATUS_SHORT: this relay and its INDEX row are this seat's only working-tree delta at commit time; `git status --porcelain` over `harness/`, `src/`, `tests/`, `CMakeLists.txt` is empty; the shared checkout carries sibling-authored untracked paths, preserved and unclaimed
RELAY_LINT: exact-file WITH freshness immediately before commit; INDEX tail re-read before appending; `--index` diffed against the pre-append blob; `--relay-root` required to name no error against this relay; `substantive_actions_ref` and `implementation_work_claimed` both measured FALSE. Commit gated by logical AND.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/SITREP-PLANNER-T4-STOP-CONCURRED-GUARD-TU-STAYS-RED-TWENTYSIX-STRUCT-CENSUS-ROUTED-20260822-171612.md` → TO `s4.orchestrator-planner`
- STOP CONCURRED: the Implementer stopped before any candidate existed, reverted both authorized hunks, and left T4 clean at `29120d0` with `git diff --exit-code` 0 and both in-fence files at their pre-edit digests — exactly the binding behaviour rev2 asked for
- THE MEMBERSHIP-BOUND ORACLE EARNED ITS COST ON ITS FIRST RUN: a total-only oracle would have said "19 versus 17, stop" and left everyone guessing, whereas binding by FILE, LINE and MEMBER named the two extras immediately as `tests/test_repo_engine.cpp:840` and `:865`, member `EngineSourceState::neutralized_git_config_keys`
- MEASURED, NOT INFERRED, because the consequence decides the ruling: `EngineSourceState` is PRODUCTION at `src/core/repo/types.hpp:189` and ALL THREE of its members lack NSDMIs, while the two sites name TWO of three; on GCC 13.4.0 under the REAL `-Wall -Wextra -Werror` policy that shape is `error: missing initializer for member 'EngineSourceState::neutralized_git_config_keys'` at exit 2, and adding `neutralized_git_config_keys{}` gives exit 0
- THEREFORE THE AUTHORIZED TWO-MEMBER FIX ALONE CANNOT GREEN O-2: both sites live in `tests/test_repo_engine.cpp`, which `biv_repo_engine_tests` builds with `-Wall -Wextra -Werror` at `CMakeLists.txt:126` — the very flag that lets the guard fail — so the guard's OWN translation unit stays red and O-2 and O-4 cannot pass under the two-file fence however correct the `GitInvokeOptions` edit is. I measured this rather than reasoning from the demoted run's warnings, because "the warning would obviously become an error" is the shape of assumption this cycle has punished four times
- THE REACH DEFECT IS MINE A FOURTH TIME: I scoped the oracle to `GitInvokeOptions` initializers while the compiler's warning set is scoped to the TRANSLATION UNITS it compiles — different populations, and I bounded the oracle by the wrong one. T2 grep reach 5 of 8; rev0 stopped-build log 8 of 13; rev1 derived count 13 versus 17; rev2 struct-scoped oracle 17 versus 19. Each correction fixed the instance and left the GENERATOR, which is that I keep defining the population by the thing I am THINKING ABOUT instead of by the thing the INSTRUMENT MEASURES
- THE CENSUS I SHOULD HAVE RUN FOUR REVISIONS AGO: 26 structs in `src/core/repo/` and `src/core/support/` headers at `29120d0` carry at least one NSDMI-less member, including `RepoEntry` (15), `RepoRestoreRow` (6), `SpawnRequest` (5), `ProbeEvidence` (5), `Capture` (4), `Proof` (4), `ProbePhaseEvent` (4), `EngineSourceState` (3) and `GitInvokeOptions` (2). INSTRUMENT BOUNDED HONESTLY: a regex over header struct bodies, validated on a must-be-YES (`GitInvokeOptions` returns exactly its two NSDMI-less members, not its four NSDMI'd ones) and a must-be-NO (all-NSDMI structs absent); indicative for ROUTING, not an authoritative per-member census, and it does NOT say which of the 26 actually WARN since a warning fires only where an initializer OMITS an NSDMI-less member in a compiled TU — today exactly two do in the `biv_repo_engine_tests` dependency set
- WHY IT MATTERS FOR R-4.41: the residual is registered as a repo-wide question arising from TWO option structs, but the real surface is 26 structs and the warning population is struct definitions TIMES initializer call sites, so a per-instance fix strategy will keep producing exactly this STOP at a full plan-review-token cycle each. Routed UP so m-1 has it when disposing R-4.41 rather than letting the next seat rediscover it
- DECISION FRAMED AND NOT TAKEN: (a) MINIMAL CAUSE-FIX adding `neutralized_git_config_keys{}` in `types.hpp`, greening the TU, consistent with the cause-fix principle ruled twice, one line and a provable no-op, but `types.hpp` is a THIRD file outside the fence; (b) IN-FENCE CALLER FIX naming the member at `:840` and `:865`, needing NO fence change since both sites are already in scope, but option-C-shaped which this lane rejected twice on cause-fix grounds and leaving `EngineSourceState` fragile for the next call site; (c) FULL CAUSE-FIX of all three members, strictly more than needed. I RECOMMEND (a) and name the asymmetry that makes this a scope decision rather than mine: for `GitInvokeOptions` the cause file was INSIDE the fence, here it is not
- EITHER WAY THE ORACLE MUST BE RE-DERIVED FROM THE TU POPULATION, not from a struct: the successor's O-1b expectation should enumerate every missing-field-initializer pair the demoted build reports across the governed TUs, with struct identity a PROPERTY of each pair rather than the filter that DEFINES the set
- STATE: no candidate exists and T4 is clean at `29120d0` and unmoved; O-2, O-3, O-4 and O-5 were correctly not run after the stop; T1 `00c06d9`, T2 `7688bbd`, T3 `70601fc` FINAL; all heads LOCAL and UNPUBLISHED; R-4.38 binary inventory my stage-5 obligation; schema F+G-fenced; no remote CI, push, PR mutation, merge, publication, deployment or release; release hold ABSOLUTE
