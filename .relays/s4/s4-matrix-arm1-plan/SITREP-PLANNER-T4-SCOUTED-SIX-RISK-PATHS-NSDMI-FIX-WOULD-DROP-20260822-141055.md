## SITREP — T4 scouted at the bytes BEFORE any reconstruction, and the instrument earned itself again: SIX risk paths against T3's three, and one of them would silently drop T2's landed NSDMI product fix. Post-conditions set now, while they can still be checked independently of the replay

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-matrix-t4-scouted-six-risk-paths
PARENT_DISPATCH_ID: s4-matrix-wave-a-t3-relens-pass-head-final-reconstruct-t4
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-T3-RELENS-PASS-HEAD-FINAL-70601FC-ACCEPTED-RECONSTRUCT-T4-20260822-140530.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/SITREP-PLANNER-COMPARE-PY-COMPOSITION-SCOUTED-INCOMPATIBLE-SIGNATURES-NOT-A-CONFLICT-20260821-230628.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new operator gate — `140530` authorizes the T4 reconstruction in-lane and this is the pre-reconstruction scout it names. This relay carries NO token and no keyboard authority; the reconstruction is the Implementer's under the standing Wave-A dispatch. No merge, push, PR mutation, schema act, deployment, or release. The release hold is ABSOLUTE
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: FINAL T3 `70601fc201b3c41d2542d82399787b5febcbf03c` (the reconstruction target); T4's old head `cb1f6254e1a275fd5e56ba91547d762145b32fa7`; Wave-A fork `285cfc4758fab77f70832555eb8461ac0ed86251`
FROM: s4-matrix.planner
TO: s4-matrix.implementer
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: T4 SCOUTED before any keyboard — base-added-since-fork intersected with T4's own rewrites gives SIX risk paths of nineteen, and src/core/repo/git.hpp would DROP T2's landed NSDMI fix (present at 70601fc, absent at cb1f625, T4 rewrites it with 10 deletions); six post-conditions set now, plus the paths proven safe so effort goes where the risk is

## 1. Why this is filed before the reconstruction, not after

`230628` established the rule for T3 and `140530` asks for it again: a replay that silently
drops base content answers the question before anyone can ask it, and a build cannot see a
deleted feature — a test suite cannot see one whose tests were deleted in the same range. So
the determination is made now, at the bytes, and stated as post-conditions that hold whichever
way the replay behaves.

**The T4 pre-check I filed at `230628` is stale and I am not reusing it.** It was measured
against `7688bbd` (final T2). The stack has moved twice since — through T3's reconstruction and
its ref-SHA guard — so I re-ran the instrument at the current head. A verdict decays as the
tree moves; that is the lane's own lesson and it applies to my own prior work.

## 2. The instrument, re-run at `70601fc`

T4's OWN slice is `d7d32f9..cb1f625` — everything after T3's last commit on the old branch:
the repo engine (`discover`, `classify`, `eligibility`, `capture`, `restore`) plus three
Wave-A-wide review-fold commits. Its earlier commits are T1/T2/T3 predecessors and are not
T4's to replay.

```text
base-added-since-fork  =  git diff --numstat 285cfc4 70601fc  -- src tests harness CMakeLists.txt schemas
T4-own-rewrites        =  git diff --numstat d7d32f9 cb1f625  -- (same paths)

T4 rewrites 19 paths; the base changed 113 since the fork; INTERSECTION = 6

  CMakeLists.txt              T4 +12/-0    base since fork +40/-3
  src/core/repo/git.cpp       T4 +17/-13   base since fork +165/-0
  src/core/repo/git.hpp       T4 +21/-10   base since fork  +87/-0
  src/core/repo/types.hpp     T4 +92/-1    base since fork +130/-0
  tests/support/temp_dir.hpp  T4 +11/-2    base since fork  +43/-0
  tests/test_repo_git.cpp     T4 +35/-29   base since fork +312/-0
```

Six risk paths against T3's three. **This is a materially larger surface than T3's, and the
count is not the point — the content is.**

## 3. The finding that earns the scout

```text
T2's NSDMI cause-fix, `empty_config_keys{}` in src/core/repo/git.hpp
  at base 70601fc   1 occurrence   <- the landed fix
  at T4 old cb1f625 0 occurrences  <- predates it
and T4 rewrites git.hpp with 10 DELETIONS
```

A replay that resolves `git.hpp` to T4's side **silently drops a landed product fix** — the
same shape as `compare.py` on T3, on a product header this time rather than a harness module.
Nothing about the build or the suite would announce it: the file still compiles, and the NSDMI
fix's absence is exactly the kind of defect that shows up as a tidy warning or a latent
init-order question, not a failing test.

**And what is NOT at risk, stated so effort goes where the risk is:**

```text
src/core/support/subprocess.cpp   NOT in T4's rewrite set  -> T1's tidy repair cannot be dropped
tests/test_probe.cpp              NOT in T4's rewrite set  -> R-3.40(13)'s platform split is safe
13 of T4's 19 paths are T4-ONLY (capture/classify/discover/eligibility/restore/git_exec .cpp+.hpp,
  test_repo_engine.cpp) -> purely additive, nothing of the base's to drop
```

## 4. A count that would have reassured me and proves nothing

```text
tests/test_repo_git.cpp   TEST_CASE count at base 70601fc  = 6
                          TEST_CASE count at T4  cb1f625   = 6
                          base added +312 lines since the fork
```

Equal counts across a 312-line addition. If I had checked the case count and stopped, I would
have reported the file safe. **The post-condition for this path must therefore be content-level,
never count-level** — the lane already paid for this in the other direction (a leg is not
redundant because its count matches another's).

## 5. Post-conditions for the reconstructed head

Stated now so they can be checked without predicting how the replay behaves:

```text
P1  src/core/repo/git.hpp CONTAINS `empty_config_keys{}` -- T2's NSDMI fix, the highest-value
    drop risk.  A reconstructed head without it is WRONG regardless of what builds or passes.
P2  src/core/repo/git.cpp retains the base's static GIT_CONFIG_KEY_0..4 isolation block AND
    T4's own git.cpp changes; neither side may be taken wholesale.
P3  tests/test_repo_git.cpp -- CONTENT-level: every test present at 70601fc is present at the
    reconstructed head.  Do NOT use the TEST_CASE count; it is 6 on both sides and blind.
P4  CMakeLists.txt retains the base's additions AND gains T4's repo-engine sources; verify both
    directions, not just that the file changed.
P5  src/core/repo/types.hpp and tests/support/temp_dir.hpp retain their base-added content
    alongside T4's additions.
P6  the 13 T4-only paths are purely additive; if any shows a DELETION against the base, the
    scope is wrong and it stops.
```

**Beyond the post-conditions**, `140530` also asks for the interaction verification. T4's own
slice contains three Wave-A-WIDE review folds (`fix(review): fold Wave A engine findings`,
`neutralize repo-local Git command drivers`, `complete Git driver enumeration`) whose targets
are T1/T2/T3 surfaces, not T4's. Whether those folds are already present in the reconstructed
stack or must be re-applied is a real question I have NOT answered here and am not guessing at:
it needs measuring per fold against `70601fc`, and I will scout it as a second pass rather than
let a "probably already there" ride into a replay. Flagging it now so it is not discovered
mid-reconstruction.

## 6. State

No reconstruction has begun and none is authorized by this relay. T3 head FINAL at `70601fc`;
T2 FINAL at `7688bbd`; T1 FINAL at `00c06d9`; T4 HELD at its old `cb1f625` pending
reconstruction. All heads LOCAL and UNPUBLISHED. Findings (1), (2) and (4) plus R-4.35 /
R-4.38 / R-4.40 and the three permanent root-mode lineage record-defects all ride the stage-5
merge-readiness report, which is my obligation. Schema F+G-fenced. Merge is not push is not
release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: none — no edits made at this seat; no branch, ref or worktree moved and no reconstruction begun. Read-only: `git log`/`git rev-parse`/`git merge-base` over `s4-matrix/arm1-t4`, `70601fc` and the fork `285cfc4`; two `git diff --numstat` ranges intersected locally; and `git show` of `src/core/repo/git.hpp`, `src/core/support/subprocess.cpp`, `tests/test_probe.cpp` and `tests/test_repo_git.cpp` at the base and at T4's old head. No merge, push, PR mutation, or remote CI. Docs lane: this relay + its INDEX row ride ONE explicit-path commit.
FINAL_GIT_STATUS_SHORT: this relay and its INDEX row are this seat's only working-tree delta at commit time; `git status --porcelain` over `harness/`, `src/`, `tests/`, `CMakeLists.txt` is empty; the shared checkout carries sibling-authored untracked paths, preserved and unclaimed
RELAY_LINT: exact-file WITH freshness immediately before commit; INDEX tail re-read before appending; `--index` diffed against the same lint on the pre-append blob; `--relay-root` run before commit required to name no error against this relay; `substantive_actions_ref` and `implementation_work_claimed` both measured FALSE on the finished bytes. Commit gated by logical AND.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/SITREP-PLANNER-T4-SCOUTED-SIX-RISK-PATHS-NSDMI-FIX-WOULD-DROP-20260822-141055.md` → TO `s4-matrix.implementer`
- SCOUTED BEFORE ANY KEYBOARD per `230628` and as `140530` asks: a replay that silently drops base content answers the question before anyone can ask it, and a build cannot see a deleted feature while a suite cannot see one whose tests were deleted in the same range
- MY OWN `230628` T4 PRE-CHECK IS STALE AND I AM NOT REUSING IT: it was measured against `7688bbd`, and the stack has moved twice since through T3's reconstruction and its ref-SHA guard. A verdict decays as the tree moves — the lane's own lesson, applied to my own prior work
- INSTRUMENT RE-RUN AT `70601fc`: T4's OWN slice is `d7d32f9..cb1f625` (the repo engine plus three Wave-A-wide review folds; its earlier commits are T1/T2/T3 predecessors and not T4's to replay). T4 rewrites 19 paths, the base changed 113 since the fork, INTERSECTION = SIX: `CMakeLists.txt` (T4 +12/-0 vs base +40/-3), `src/core/repo/git.cpp` (+17/-13 vs +165/-0), `src/core/repo/git.hpp` (+21/-10 vs +87/-0), `src/core/repo/types.hpp` (+92/-1 vs +130/-0), `tests/support/temp_dir.hpp` (+11/-2 vs +43/-0), `tests/test_repo_git.cpp` (+35/-29 vs +312/-0). SIX risk paths against T3's THREE
- THE FINDING THAT EARNS THE SCOUT: T2's NSDMI cause-fix `empty_config_keys{}` in `src/core/repo/git.hpp` is present ONCE at base `70601fc` and ZERO times at T4's old `cb1f625`, and T4 rewrites that file with 10 DELETIONS — so a replay resolving `git.hpp` to T4's side SILENTLY DROPS A LANDED PRODUCT FIX. Same shape as `compare.py` on T3, on a product header this time, and nothing would announce it: the file still compiles and the fix's absence surfaces as a tidy warning or a latent init-order question, not a failing test
- WHAT IS NOT AT RISK, so effort goes where the risk is: `src/core/support/subprocess.cpp` is NOT in T4's rewrite set so T1's tidy repair cannot be dropped; `tests/test_probe.cpp` is NOT either so R-3.40(13)'s platform split is safe; and 13 of T4's 19 paths are T4-ONLY (capture/classify/discover/eligibility/restore/git_exec sources and headers, `test_repo_engine.cpp`) hence purely additive with nothing of the base's to drop
- A COUNT THAT WOULD HAVE REASSURED ME AND PROVES NOTHING: `tests/test_repo_git.cpp` has TEST_CASE count 6 at BOTH heads while the base added +312 lines. Had I checked the case count and stopped I would have reported the file safe, so P3's post-condition is CONTENT-level and explicitly forbids the count
- SIX POST-CONDITIONS SET NOW so they can be checked without predicting the replay: P1 `git.hpp` CONTAINS `empty_config_keys{}` and a head without it is WRONG regardless of what builds or passes; P2 `git.cpp` retains the base's static `GIT_CONFIG_KEY_0..4` isolation block AND T4's own changes with neither side taken wholesale; P3 `test_repo_git.cpp` content-level with the count explicitly forbidden; P4 `CMakeLists.txt` retains base additions AND gains T4's repo-engine sources, verified in BOTH directions; P5 `types.hpp` and `temp_dir.hpp` retain base-added content alongside T4's; P6 the 13 T4-only paths are purely additive and any DELETION against the base means the scope is wrong and it stops
- AN OPEN QUESTION I AM NOT GUESSING AT: T4's own slice contains three Wave-A-WIDE review folds (`fold Wave A engine findings`, `neutralize repo-local Git command drivers`, `complete Git driver enumeration`) whose targets are T1/T2/T3 surfaces rather than T4's. Whether each is already present in the reconstructed stack or must be re-applied needs MEASURING per fold against `70601fc`; I will scout it as a second pass rather than let a "probably already there" ride into a replay, and I flag it now so it is not discovered mid-reconstruction
- STATE: no reconstruction begun and none authorized by this relay; T3 head FINAL at `70601fc`, T2 FINAL at `7688bbd`, T1 FINAL at `00c06d9`, T4 HELD at its old `cb1f625`; all heads LOCAL and UNPUBLISHED; findings (1)/(2)/(4) plus R-4.35, R-4.38, R-4.40 and the three permanent root-mode lineage record-defects all ride the stage-5 merge-readiness report which is my obligation; schema F+G-fenced; no remote CI, push, PR mutation, merge, publication, deployment or release; release hold ABSOLUTE
