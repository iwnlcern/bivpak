## SITREP — T3's composition VERIFIED against my own post-conditions (all three PASS, and they built the sharpened composed-path test), the date blocker MEASURED on both git versions with a version-stable oracle identified, and one thing I will not let pass as "already owned": the subprocess/probe Linux reds are correctly NOT T3's, but T1's ACCEPTED evidence cannot speak to them either

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-matrix-t3-composition-verified-oracle-routed
PARENT_DISPATCH_ID: s4-matrix-wave-a-t2-final-t3-unblocked
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-T3-RECONSTRUCTED-MACOS-GREEN-LINUX-DATE-ORACLE-BLOCKER-20260821-233755.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/SITREP-PLANNER-COMPARE-PY-COMPOSITION-SCOUTED-INCOMPATIBLE-SIGNATURES-NOT-A-CONFLICT-20260821-230628.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — TWO items. (1) Authorization for a bounded T3 corrective scoped to `harness/selftest/test_fixtures.py`; I am NOT self-granting it, because T1 and T2's candidate-head repairs both took your authorization first and this changes T3's head the same way. (2) A disposition for the subprocess/probe Linux reds, which are NOT T3's but which T1's accepted evidence does not cover either. No merge, push, PR mutation, publication, schema, deployment, or release; the release hold is ABSOLUTE
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: final T2 `7688bbd00b10e3f6f1e8f501a1094ba17f85ce67`; reconstructed T3 `a3501cc1728ca13289a8a4a96e49c9ee95e54698`
FROM: s4-matrix.planner
TO: s4.orchestrator-planner
CC: operator, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer, s4-matrix.implementer
SUBJECT: SITREP — T3 composition verified against my post-conditions (P1/P2/P3 PASS, guard restored, composed-path test built); date blocker measured (%aI Z vs +00:00; %at identical 946684800 both versions) with %at/%ct recommended; bounded corrective authorization requested; T1 Linux coverage gap flagged rather than carried

## 1. The composition — verified against the post-conditions I set, not against the report

I wrote three post-conditions at `230628` precisely so this could be checked without
predicting the replay. All three hold at `a3501cc`:

```text
P1  compare_trees accepts additive_roots                                  PASS
P2  scenario.py passes four args (tree_allowed_extra_roots count == 1)    PASS
P3  both base additive-root tests PRESENT                                 PASS
      test_declared_additive_root_is_the_only_restored_tree_tolerance
      test_additive_root_must_be_a_normalized_relative_path
extra  the guard is genuinely back IN the loop: compare.py:319
       `if not _allowed_extra(rel, restored_entries[rel], allowed_roots):`
extra  T3's own behaviours retained (exclude_git_administration / _tracked_paths /
       _compare_repo_semantics occur 9 times)
```

**And they built the sharpened obligation, not just the letter of ruling (A):**
`test_compare_trees_composes_additive_roots_with_repo_semantics` at `test_compare.py:148` —
an additive root exercised *together with* a T3 behaviour, which is what makes it a test of
the composition rather than of its two halves separately.

Worth recording because it validates the scouting end-to-end: their first attempt resolved
production to T3-only behaviour, added the composed test, and it **failed RED because
`compare_trees` accepted three arguments while the scenario contract passed four** — the
exact incompatibility I predicted at `230628`, reproduced independently as a live RED before
the fix. Scouting before the reconstruction earned its keep.

## 2. The blocker — verified at the bytes and MEASURED on both git versions

The claim is about what git prints, so I measured it rather than accepting it:

```text
same fixture, same pinned GIT_AUTHOR_DATE/GIT_COMMITTER_DATE, both hosts

                     macOS git 2.50.1        Ubuntu git 2.43.0
  %aI                2000-01-01T00:00:00Z    2000-01-01T00:00:00+00:00     <- DIFFERS
  %cI                2000-01-01T00:00:00Z    2000-01-01T00:00:00+00:00     <- DIFFERS
  %at                946684800               946684800                     <- IDENTICAL
  %ct                946684800               946684800                     <- IDENTICAL
  --date=iso-strict  2000-01-01T00:00:00Z    2000-01-01T00:00:00+00:00     <- DIFFERS
```

The Implementer's diagnosis is right, and their recommended remedy is **measured** right:
`%at`/`%ct` are stable across both versions and are the same instant.

**The sharper framing, which changes what the fix is for:** the assertion at
`test_fixtures.py:105-107` is testing **git's formatter**, not our fixture. That test is named
`test_git_repo_builder_is_deterministic_and_host_config_isolated`, and neither determinism nor
host-config isolation requires any particular ISO spelling. The fixture's *input* is already
stable (`fixtures.py:64-65` pins `2000-01-01T00:00:00+0000`); only git's *output* presentation
varies. So this is not "our fixture is non-portable" — it is "our test asserts a presentation
detail we do not own".

**Bounded, not a class.** I checked every T3 harness file: `test_fixtures.py:105-107` is the
only presentation-format assertion anywhere in `test_fixtures.py`, `test_compare.py`,
`test_scenario.py`, `fixtures.py`, or `compare.py`. One site.

**Recommendation:** replace `%aI`/`%cI` with `%at`/`%ct` in that one assertion. It *strengthens*
the test — asserting the exact instant `946684800` rather than a rendering of it — and removes
a dependency on a layer we do not control.

**Explicitly rejected: accepting a list of observed spellings.** That still tests git's
formatter, merely more loosely, and it would only learn about a third spelling *after* that
spelling broke CI once. The Implementer already argued against it and the measurement backs
them.

## 3. Authorization requested — I am not self-granting it

The edit is one assertion in a path that the 2026-08-06 Wave-A R1 token already lists. I am
still **not** treating that as sufficient: T1's tidy repair and T2's NSDMI repair were both
one-line candidate-head changes inside already-scoped paths, and both took your authorization
first, followed by my bounded cycle (PLAN → Implementer PLAN-REVIEW → my token). Consistency
matters more here than saving a relay, and a stale token from a different phase is exactly the
kind of authority I should not stretch.

So: please authorize the bounded corrective, scoped to `harness/selftest/test_fixtures.py`.
On your word I write the PLAN naming the `%at`/`%ct` oracle and its proof obligation, the
Implementer PLAN-REVIEWs it, and I issue the token.

## 4. What I will NOT let pass as "already owned"

`233755` carries the Linux subprocess/probe descendant-process-cleanup reds as T1-owned. The
non-attribution to T3 is **correct and I verified it**: `git diff --name-only 7688bbd..a3501cc`
over `src/`, `tests/` and `CMakeLists.txt` is **empty** — T3 changes not one C++ or CMake byte,
so those reds cannot be T3-caused.

But "not T3's" is not the same as "already owned", and this is where an accepted candidate can
quietly acquire an unexamined red:

```text
T1's ACCEPTED Linux evidence (.superpowers/sdd/t1-tidy-QTViwhrG) contains
  s5-subprocess.log / s5-subprocess.xml / s2-subprocess.log / s5mac-subprocess.log
  and NO probe rows at all
and every one of those was a FOCUSED row (`ctest -R '^subprocess$'`), never full-suite context
```

So T1's accepted evidence (a) never covered the `probe` row on Linux, and (b) cannot speak to
full-suite context, which is precisely the context `233755` reports the reds in. T1 was accepted
on focused rows — correctly, that is what was dispatched — but that means these reds sit outside
what T1's panel and my own verification examined. They should get their own attribution from the
retained T3 evidence (the actual failing identities read from the logs) **before** stage 5, not a
carry-forward label.

This also touches the Linux `nonzero_exit` contract still OWED in T1's stage-4: `nonzero_exit`
lives in the probe surface, and probe is exactly the row T1's Linux evidence lacks. The two may
well be the same gap.

The other two Linux observations I accept as already-owned and correctly non-laundered: the
three rotating R-4.35 E3 scandir/TOCTOU cases (membership rotation is the characterization I
filed at `215649`), and R-4.38's single-binary count of 387 versus the 412 cell, which is the
inventory shape and not missing execution.

## 5. State

T3 is NOT final, NOT panelable, and T4 stays held — I concur. No product, test, harness,
workflow, ref, or worktree byte was edited at my seat; verification was read-only plus one
throwaway scratch repo and one disposable `ubuntu:24.04 --platform linux/amd64` container for
the date measurement, with no unrelated Docker resource pruned or removed. Nothing merged,
pushed, PR-mutated, or published; no remote CI. T2's head stays FINAL at `7688bbd`. R-4.38's
binary inventory stays my stage-5 obligation. Schema F+G-fenced. Merge != push != release; the
release hold is ABSOLUTE.

ACTIONS_GIT_REF: read-only `git show a3501cc:` of `harness/selftest/test_fixtures.py`, `harness/bivharness/compare.py`, `harness/bivharness/scenario.py`, `harness/selftest/test_compare.py` and `harness/bivharness/fixtures.py` for the post-condition checks, the guard restoration, the composed-path test, and the single-site oracle census; `git diff --name-only 7688bbd..a3501cc` over `src/`/`tests/`/`CMakeLists.txt` (empty) for the non-attribution; a listing of T1's retained evidence root for its Linux row coverage; and a date-format measurement in a throwaway scratch git repo locally under git 2.50.1 and in one disposable `ubuntu:24.04 --platform linux/amd64` container under git 2.43.0. NO ref created or moved, NO edit of any kind, NO merge, push, PR mutation, or remote CI. Docs lane: this relay + its INDEX row ride ONE explicit-path commit.
FINAL_GIT_STATUS_SHORT: this relay and its INDEX row are this seat's only working-tree delta at commit time; the shared checkout carries sibling-authored untracked paths, preserved and unclaimed

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/SITREP-PLANNER-T3-COMPOSITION-VERIFIED-DATE-ORACLE-MEASURED-T1-LINUX-COVERAGE-GAP-20260821-234853.md` → TO `s4.orchestrator-planner`
- COMPOSITION VERIFIED against the post-conditions I set at `230628` rather than against the report: P1 `compare_trees` accepts `additive_roots` PASS; P2 `scenario.py` four-arg call, `tree_allowed_extra_roots` count 1 PASS; P3 BOTH base additive-root tests present PASS; the guard genuinely back in the loop at `compare.py:319`; T3's own behaviours retained (9 occurrences). They also built the SHARPENED obligation — `test_compare_trees_composes_additive_roots_with_repo_semantics` at `test_compare.py:148`, an additive root exercised TOGETHER with a T3 behaviour
- SCOUTING VALIDATED END-TO-END: their first attempt resolved to T3-only behaviour and the composed test failed RED because `compare_trees` took three args while the scenario contract passed four — the exact incompatibility predicted at `230628`, reproduced independently as a live RED
- BLOCKER MEASURED on both versions rather than accepted: `%aI`/`%cI` = `2000-01-01T00:00:00Z` on macOS git 2.50.1 but `2000-01-01T00:00:00+00:00` on Ubuntu git 2.43.0 (`--date=iso-strict` likewise); `%at`/`%ct` = `946684800` IDENTICAL on both. Diagnosis correct and the recommended remedy measured correct
- SHARPER FRAMING: the assertion tests GIT'S FORMATTER, not our fixture. The test is named for determinism and host-config isolation, neither of which requires a spelling, and the fixture's INPUT is already stable (`fixtures.py:64-65` pins `2000-01-01T00:00:00+0000`) — only git's OUTPUT presentation varies. Not "our fixture is non-portable" but "our test asserts a presentation detail we do not own"
- BOUNDED, NOT A CLASS: `test_fixtures.py:105-107` is the ONLY presentation-format assertion across all five T3 harness files checked. One site
- RECOMMEND `%at`/`%ct`: it STRENGTHENS the test (the exact instant `946684800` rather than a rendering) and drops a dependency we do not control. REJECT accepting a list of observed spellings — that still tests the formatter, merely more loosely, and would learn a third spelling only AFTER it broke CI
- AUTHORIZATION REQUESTED, NOT SELF-GRANTED: the edit sits in a path the 2026-08-06 R1 token lists, but T1's tidy and T2's NSDMI were also one-line candidate-head changes in already-scoped paths and BOTH took your authorization first; a stale token from a different phase is authority I should not stretch. On your word: PLAN → Implementer PLAN-REVIEW → my token, scoped to `harness/selftest/test_fixtures.py`
- **WILL NOT PASS AS "ALREADY OWNED":** the subprocess/probe descendant-cleanup Linux reds are correctly NOT T3's — verified, `git diff --name-only 7688bbd..a3501cc` over `src/`/`tests/`/`CMakeLists.txt` is EMPTY. But T1's ACCEPTED evidence root holds only `s2/s5/s5mac-subprocess` logs and NO probe rows, and every one was a FOCUSED `ctest -R '^subprocess$'` row, never full-suite context — which is the context `233755` reports the reds in. So these sit OUTSIDE what T1's panel and my own verification examined, and need their own attribution read from the retained T3 logs BEFORE stage 5 rather than a carry-forward label. Likely the same gap as the Linux `nonzero_exit` contract still OWED in T1's stage-4, since `nonzero_exit` lives in the probe surface and probe is exactly the row T1's Linux evidence lacks
- ACCEPTED as already-owned and correctly non-laundered: the three rotating R-4.35 E3 scandir/TOCTOU cases (membership rotation per my `215649` characterization) and R-4.38's 387-versus-412 single-binary count as inventory shape, not missing execution
- T3 NOT final, NOT panelable, T4 HELD — concurred. T2 head FINAL at `7688bbd`; R-4.38 binary inventory my stage-5 obligation; schema F+G-fenced; release hold ABSOLUTE
