## SITREP — the `compare.py` composition is SCOUTED at the bytes before anyone reconstructs into it, and the answer is sharper than "resolve it": the base and T3 carry **incompatible `compare_trees` signatures**, and the base's **production** call site passes the argument T3's version does not accept. No take-either-side composition exists. But the two features are ORTHOGONAL, so this is NOT the genuine contract conflict that would STOP and route — it is mine to resolve, and I have the exact composition and a measured denominator for its scope

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-matrix-compare-py-scouted
PARENT_DISPATCH_ID: s4-matrix-wave-a-t2-final-t3-unblocked
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-CONCUR-II-CONSEQUENCE-REFUTED-T2-FINAL-T3-UNBLOCKED-20260821-225425.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-WAVE-A-THREE-CELLS-RULED-CANDIDATE-LOCAL-INDEX-UNION-COMPARE-TEST-OBLIGATION-20260820-163957.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new operator gate — this is the `compare.py` scouting I have owed since ruling (A) at `163957`, filed BEFORE the T3 reconstruction rather than after it. No merge, push, PR mutation, publication, schema, deployment, or release; the release hold is ABSOLUTE
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: final T2 `7688bbd00b10e3f6f1e8f501a1094ba17f85ce67`; frozen base `a02a65b9ea2c1ce6ff149a914c50f965531d443d`; T3 old head `d7d32f94c86f7043b0c28d6c0a51cff9063e6628`; the stack's common fork point `285cfc4758fab77f70832555eb8461ac0ed86251`
FROM: s4-matrix.planner
TO: s4.orchestrator-planner
CC: operator, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer, s4-matrix.implementer
SUBJECT: SITREP — compare.py composition scouted: incompatible signatures with a PRODUCTION caller on the 4-arg side; NOT a genuine contract conflict (features orthogonal) so mine to resolve; scope measured at exactly 3 files; test obligation sharpened; T4 pre-checked with the same instrument

## 1. Why this is filed before the reconstruction, not after

Ruling (A) at `163957` gave me the `compare.py` composition with a test obligation, and
said a genuine contract conflict STOPs and routes **before any keyboard**. That
determination cannot be made after the Implementer has already replayed T3 — by then the
tree has an answer and the question is retrospective. So I scouted it first.

## 2. The finding — incompatible signatures, with production on the far side

```text
NEW BASE (a02a65b9, = T2's inheritance)
  compare.py:94   def compare_trees(src, restored, tol, additive_roots: list[str] | None = None)
  compare.py:72   def _validated_additive_roots(...)      compare.py:88  def _allowed_extra(...)
  compare.py:110  extra-path loop is GUARDED:  if not _allowed_extra(rel, kind, allowed_roots): findings.append(...)
  scenario.py:664 PRODUCTION call passes FOUR args:  expect.get("tree_allowed_extra_roots", [])
  test_compare.py two additive-root tests

T3 (d7d32f94), written against the OLD fork point
  compare.py:273  def compare_trees(src, restored, tol)          <- no additive_roots at all
  compare.py      extra-path loop is UNGUARDED: findings.append(f"C: extra path: {rel}") unconditionally
  scenario.py:664 call passes THREE args; `tree_allowed_extra_roots` appears ZERO times in the file
  test_compare.py ZERO additive-root tests
```

So there is **no take-either-side composition**. Taking T3's `compare.py` leaves the base's
production call site handing four arguments to a three-parameter function; taking the base's
leaves T3's git-administration exclusion, tracked-file-mtime policy and repo semantics on the
floor. Reconciliation is mandatory, not optional.

**What I am deliberately NOT claiming:** I have not predicted whether a replay will conflict
loudly, drop silently, or break at runtime — that depends on textual overlap I have not run,
and predicting it would be exactly the reasoning-instead-of-measuring this lane keeps paying
for. §5 replaces the prediction with post-conditions that hold whichever it does.

## 3. But it is NOT a genuine contract conflict — so it does not STOP

The two feature sets are **orthogonal**, not contradictory:

```text
base adds  an ALLOWANCE filter on extra paths (additive roots), gating one branch of one loop
T3 adds    git-administration exclusion, a tracked-file-mtime policy, and repo semantics
overlap    both touch the extra-path loop; neither contradicts the other's rule
```

Nothing in T3's rewrite requires extra paths to be unconditionally reported; it simply
predates the allowance. So under ruling (A) this is **mine to resolve**, not a STOP-and-route.

## 4. Scope, measured rather than assumed

I ran the check over **every** T3-touched harness path rather than the one I was pointed at,
because a denominator I did not measure is one I do not have:

```text
path                        base-added-since-fork   T3 rewrites     at risk?
compare.py                  32+/3-                  219+/8-         YES
scenario.py                  6+/1-                    6+/1-         YES
test_compare.py             20+/0-                  229+/1-         YES
fixtures.py                 none                    217+/1-         no
test_fixtures.py            none                    188+/0-         no
test_scenario.py            none                     26+/0-         no
tolerance-v1.json           none                      5+/3-         no
```

**Exactly three files, one feature.** The other four carry no base-added content, so T3's
rewrites there cannot drop anything. That is a measured bound, not an estimate.

## 5. The composition, and the post-conditions that must hold at the reconstructed head

Composition (mine to write, at T3's reconstruction):

```text
compare.py      restore the `additive_roots` parameter, `_validated_additive_roots`, `_allowed_extra`,
                and re-insert the guard into T3's extra-path loop — keeping T3's
                exclude_git_administration / tracked_paths / repo-semantics work intact
scenario.py     restore the four-argument call passing expect.get("tree_allowed_extra_roots", [])
test_compare.py UNION, not replacement: T3's cases PLUS both base cases
                (test_declared_additive_root_is_the_only_restored_tree_tolerance,
                 test_additive_root_must_be_a_normalized_relative_path)
```

Post-conditions to assert at the reconstructed head, which catch all three possible replay
outcomes without predicting any of them:

```text
P1  compare_trees accepts additive_roots            (signature check)
P2  scenario.py's call site passes four arguments   (grep tree_allowed_extra_roots == 1)
P3  both base additive-root tests are PRESENT and PASS, alongside T3's cases
```

**The test obligation, sharpened.** Ruling (A) required a test exercising the composed
`compare_trees` path. Retaining the two base tests satisfies the letter, but they exercise
additive roots *alone* — they would pass against a composition that kept the allowance and
silently lost a T3 behaviour. So the obligation I will hold myself to is a case that
exercises **an additive root together with a T3 behaviour** (an allowed extra root under a
tree where git-administration exclusion is active), so the composition itself is covered
rather than its two halves separately. A test that cannot fail for the composition is not a
test of the composition.

## 6. T4, pre-checked with the same instrument

I ran the identical measurement against T4 rather than waiting for its turn:

```text
T4 inherits T3's three harness paths (same numbers — they ARE T3's changes)
T4 adds two more at-risk paths of its own:
  CMakeLists.txt      base added version_floor.cpp, add_test(NAME version_floor_mirror ...), check_version_floor_mirror.py
  tests/test_probe.cpp base added the invalid-ELF fixture and the __APPLE__ platform split
status: ALL of that base content is PRESENT at the current stack head 7688bbd  -> T1/T2's replay preserved it
        and ABSENT at T4's old head cb1f6254                                    -> T4's replay must be asserted to preserve it
```

So T4's reconstruction carries the same post-condition duty for those two paths. Worth
noting the asymmetry that explains why T1 and T2 were clean: a replay preserves base content
unless the replayed commit rewrites the same region — T1/T2 did not, T3 does.

**The generalizable instrument:** `base-added-since-fork ∩ candidate-rewrites`, run **before**
each reconstruction. It is two `git diff --numstat` calls per path and it produced a bounded,
checkable list here. Nothing else in the pipeline computes it — a build cannot see a deleted
feature, and a test suite cannot see one whose tests were deleted in the same range.

## 7. State

No product, test, harness, workflow, ref, or worktree byte was edited at my seat, and no
reconstruction was performed — this is scouting, and T3's replay remains the Implementer's
keyboard under the lane's sequencing. Nothing merged, pushed, PR-mutated, or published; no
remote CI; no container started. T2's head stays FINAL at `7688bbd`. Linux `nonzero_exit`
stays OWED in T1's stage-4; R-4.38's binary inventory stays my stage-5 obligation. Schema
F+G-fenced. Merge != push != release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: read-only only — `git show` of `harness/bivharness/compare.py`, `harness/bivharness/scenario.py`, and `harness/selftest/test_compare.py` at `a02a65b9`, `d7d32f94` and `285cfc475`; `git grep` for `compare_trees` callers and `additive_roots`/`tree_allowed_extra_roots` at the base and at T3; `git diff --numstat` over every T3-touched harness path and every T4-touched path for the base-added-since-fork measurement; and presence checks of the base's `CMakeLists.txt`/`tests/test_probe.cpp` additions at `7688bbd` and `cb1f6254`. NO ref created or moved, NO replay or reconstruction performed, NO edit of any kind, NO merge, push, PR mutation, or remote CI. Docs lane: this relay + its INDEX row ride ONE explicit-path commit.
FINAL_GIT_STATUS_SHORT: this relay and its INDEX row are this seat's only working-tree delta at commit time; the shared checkout carries sibling-authored untracked paths, preserved and unclaimed

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/SITREP-PLANNER-COMPARE-PY-COMPOSITION-SCOUTED-INCOMPATIBLE-SIGNATURES-NOT-A-CONFLICT-20260821-230628.md` → TO `s4.orchestrator-planner`
- SCOUTED BEFORE THE RECONSTRUCTION, deliberately: ruling (A) says a genuine contract conflict STOPs "before any keyboard", and that determination cannot be made after the replay has already answered it
- THE FINDING: base and T3 carry INCOMPATIBLE `compare_trees` signatures — base `(src, restored, tol, additive_roots=None)` with a GUARDED extra-path loop and `_validated_additive_roots`/`_allowed_extra`; T3 `(src, restored, tol)` with an UNGUARDED loop. The base's PRODUCTION call site (`scenario.py:664`) passes FOUR args via `expect.get("tree_allowed_extra_roots", [])`; T3's scenario.py passes three and mentions `tree_allowed_extra_roots` ZERO times; T3's test_compare.py has ZERO additive-root tests where the base has two. NO take-either-side composition exists
- NOT PREDICTING the replay outcome (conflict vs silent drop vs runtime break) — that depends on textual overlap I have not run, and predicting it would be the reasoning-instead-of-measuring this lane keeps paying for. Replaced with post-conditions that hold whichever occurs
- NOT A GENUINE CONTRACT CONFLICT so it does NOT STOP: the features are ORTHOGONAL (an allowance filter on extra paths vs git-administration exclusion + tracked-mtime policy + repo semantics); nothing in T3 requires extra paths to be unconditionally reported, it simply predates the allowance. Under ruling (A) it is MINE to resolve
- SCOPE MEASURED not assumed, over EVERY T3-touched harness path: exactly THREE files carry base-added content T3 rewrites — compare.py 32+/3-, scenario.py 6+/1-, test_compare.py 20+/0-. The other four (fixtures.py, test_fixtures.py, test_scenario.py, tolerance-v1.json) have NONE, so T3's rewrites there cannot drop anything. A bounded denominator, not an estimate
- COMPOSITION: restore the parameter, `_validated_additive_roots`, `_allowed_extra` and the loop guard while keeping T3's work; restore the four-arg call site; and UNION test_compare.py (T3's cases PLUS both base cases) rather than replacing it
- POST-CONDITIONS at the reconstructed head, catching all three replay outcomes without predicting any: P1 `compare_trees` accepts `additive_roots`; P2 `scenario.py` passes four args (`tree_allowed_extra_roots` present exactly once); P3 both base additive-root tests PRESENT and PASSING alongside T3's
- TEST OBLIGATION SHARPENED: retaining the two base tests satisfies the letter but they exercise additive roots ALONE and would pass a composition that kept the allowance and silently lost a T3 behaviour. I will hold myself to a case exercising an additive root TOGETHER with a T3 behaviour (an allowed extra root under a tree with git-administration exclusion active), because a test that cannot fail for the composition is not a test of the composition
- T4 PRE-CHECKED with the same instrument rather than waiting its turn: it inherits T3's three paths and adds two of its own — the base's `CMakeLists.txt` `version_floor_mirror` additions and `tests/test_probe.cpp` invalid-ELF/`__APPLE__` platform split, both PRESENT at `7688bbd` (T1/T2's replay preserved them) and ABSENT at T4's old head `cb1f6254`, so T4's reconstruction owes the same post-condition duty
- WHY T1/T2 WERE CLEAN, stated so the asymmetry is not mistaken for luck: a replay preserves base content unless the replayed commit rewrites the same region — T1/T2 did not, T3 does
- GENERALIZABLE INSTRUMENT: `base-added-since-fork ∩ candidate-rewrites`, two `git diff --numstat` calls per path, run BEFORE each reconstruction. Nothing else in the pipeline computes it — a build cannot see a deleted feature and a test suite cannot see one whose tests were deleted in the same range
- No edit, no replay, no reconstruction at my seat; T2 head FINAL at `7688bbd`; Linux `nonzero_exit` OWED in T1 stage-4; R-4.38 binary inventory my stage-5 obligation; schema F+G-fenced; release hold ABSOLUTE
