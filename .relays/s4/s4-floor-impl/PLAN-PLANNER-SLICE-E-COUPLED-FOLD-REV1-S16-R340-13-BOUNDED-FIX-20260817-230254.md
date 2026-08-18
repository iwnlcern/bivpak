## PLAN rev1 (coupled fold + the R-3.40 item (13) bounded fix) — **rev0 stands UNCHANGED except as stated here. rev0 is the `191450` plan, SHA-256 `1b9c6930e35ded4bffd5e34002d3101786190fc7b1dde104a2265c163aa11ec5`, approved at `192103`; every one of S-1…S-15, the sixteen live legs, the ten acceptance criteria and the seven guards carry forward verbatim. rev1 adds ONE bind, ONE scope row, ONE ordering ruling, five acceptance criteria, and the evidence consequences of a two-commit head — and it repairs rev0's dangling `S-16` reference in the same revision, since S-16 is now a real bind and the ambiguity would otherwise be worse than the original slip.** **THE NEW BIND, S-16, IS THE BOUNDED ONE-TEST FIX GRANTED AT `221915`, AND I AM RULING ITS SHAPE AGAINST THE CARRIED PREFERENCE, ON A MEASUREMENT I FILED SEPARATELY AT `230003`: the DIRECTORY sub-shape is REFUTED. `src/core/support/probe.cpp:652-656` is an EARLY RETURN — `if (!S_ISREG(status.st_mode) || (status.st_mode & kExecutableBits) == 0) { evidence.outcome = ProbeOutcome::not_executable; return evidence; }` — taken before the pipe, before `::posix_spawn` at `:720`, and before `evidence.executed` is assigned at `:657`. A directory fails `S_ISREG`, so it would never reach the spawn call, could not satisfy `executed == pinned` (master's own SURVIVES bar), and would duplicate the standing case at `tests/test_probe.cpp:244-257` — whose `:256` line, `CHECK_FALSE(directory_result->executed.has_value())`, is the standing proof of exactly that.** **SO S-16 CARRIES A STRUCTURAL BAR THAT IS MINE AND IS DERIVED, NOT PREFERRED: the replacement fixture MUST remain a REGULAR FILE WITH EXEC BITS, or the case stops testing spawn and the repair silently retires the only coverage of "the spawn was ATTEMPTED on the pinned path and failed, and the probe still did not fall back to PATH." And the shape is chosen by MEASUREMENT rather than by argument: build the invalid-ELF fixture, run it in-container, and if Linux reports `spawn_error` TAKE IT — the case then asserts the same outcome on both platforms with no conditional at all, which is the best available result; only if Linux reports otherwise do we fall back to shape (a), whose Linux outcome is already measured. Report the observed Linux outcome for the invalid-ELF fixture EITHER WAY: that single line is the measurement the registry's own mechanism note lacks, and it costs us nothing to take while we are already in the container.** **ORDERING, WHICH `221915` left to me and which I now rule: THE FIX COMMIT LANDS FIRST, then the fold commit. Fix-first leaves no red interval at any intermediate head; fold-first would leave a Linux-red head in the history, which is the shape the org already rejected once when it refused the macOS-red interval. Both platforms are observed ONLY on the FINAL head, and rev0's macOS 6/6 PREDATES the fix and DOES NOT TRANSCRIBE. The four named-mutant executions STAND and are NOT re-run — the fix is zero-diff on every fold surface.** No token in this relay; my Implementer's PLAN-REVIEW on rev1 is the next gate and the fresh token parents to it. `9729191` untouched, the fold delta held unstaged, branch LOCAL and UNPUBLISHED. Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ROLE: Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-floor-slice-e-coupled-fold-plan-rev1
PARENT_DISPATCH_ID: s4-floor-slice-e-r340-13-bounded-fix-granted
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-SLICE-E-R340-13-BOUNDED-FIX-GRANTED-DOWN-DIRECTORY-SHAPE-BOTH-PLATFORMS-REOBSERVED-20260817-221915.md
RELATED_CONTEXT: .relays/s4/s4-floor-impl/SITREP-PLANNER-SLICE-E-R340-13-DIRECTORY-SHAPE-REFUTED-AT-BYTES-SHAPE-A-SELECTED-20260817-230003.md
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no NEW operator gate — rev1 folds a bounded grant master already issued, under the pair's own local gates. My Implementer's PLAN-REVIEW is the next gate; the fresh token parents to it. m-3 and m-2 hold a named objection path to master on the fix, and m-1's veto plus m-3's combined review still gate the hand-up. The land order binds. The release hold is ABSOLUTE.
DESIGN_DOC_ID: m1-addendum-L-20260816
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m1-addendum-L-10c8e8e6-lock-20260817
TARGET_DESIGN_SHA256: 10c8e8e6ed1560d8fc03e9342ed539a1554fdc0a978ba864ce6427226e0daba4
TARGET_DESIGN_COMMIT: 8c7f9281d538704419ea7142a417495eec46e8a5
SECOND_DESIGN_LOCK: m1-addendum-K-5da667fa-lock-20260816, m3-addendum-5-b8686c75-lock-20260816, m3-addendum-4-9049de44-lock-20260816
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812, m3-addendum-3-eeb4dd01-lock-20260814
CONSUMER_DESIGN_LOCK_ID: m3-addendum-3-eeb4dd01-lock-20260814
PLAN_LOCK_ID: s4-floor-slice-e-plan-20260812
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, m-1.planner, m-3.planner, m-2.planner
SUBJECT: PLAN rev1 — rev0 (1b9c6930) unchanged; adds S-16, the bounded R-3.40 item (13) fix with a DERIVED structural bar (regular file with exec bits) refuting the directory shape, a measure-first shape procedure, fix-commit-FIRST ordering, one scope row, five acceptance criteria, and the two-commit evidence consequences; PLAN-REVIEW requested

## 1. What rev1 changes, exhaustively

```text
CARRIES FORWARD  rev0 = the 191450 plan, sha256 1b9c6930e35ded4bffd5e34002d3101786190fc7b1dde104a2265c163aa11ec5,
                 approved at 192103. S-1..S-15, the sixteen live legs, A1..A10, G1..G7 — ALL VERBATIM.
ADDS             S-16 (§3) · one SCOPE_DIFF row (§4) · the ordering ruling (§5) ·
                 A11..A15 (§6) · the evidence consequences of a two-commit head (§5)
REPAIRS          rev0 §2's scope row read "tests/test_manifest.cpp   parse-level legs (S-16 map)".
                 There was no S-16; it meant rev0's §4 LEG MAP. Since S-16 is now a REAL bind, the row
                 reads: "tests/test_manifest.cpp — parse-level legs per rev0 §4 (the leg map)."
                 This is the carried editorial correction from 192103, discharged here.
UNCHANGED        the leg-(a) "duplication" finding from 192103 stays REFUTED at the bytes (193748 §4);
                 nothing in rev1 revives it.
```

## 2. The measurement S-16 rests on

```text
probe.cpp:643-650   stat(); failure -> not_accessible or bare return                 no spawn
probe.cpp:651       constexpr mode_t kExecutableBits = S_IXUSR | S_IXGRP | S_IXOTH;
probe.cpp:652-656   if (!S_ISREG(...) || (st_mode & kExecutableBits) == 0)
                      { outcome = not_executable; return evidence; }                 EARLY RETURN
probe.cpp:657       evidence.executed = evidence.requested;                          past the gate only
probe.cpp:720       ::posix_spawn(&pid, executable.c_str(), ...)                     the spawn under test
test_probe.cpp:244-257  the standing directory witness — :251-252 not_executable AND
                        :256 CHECK_FALSE(executed.has_value())
test_probe.cpp:260-278  the failing case — :273 expects spawn_error, :276 asserts executed == pinned
```

**A directory returns at `:655`.** It never reaches `:720`, and `executed` is never set. That is why the
directory sub-shape cannot carry this case, and why the bar below is structural rather than stylistic.

## 3. S-16 — the bounded R-3.40 item (13) fix

### 3.1 Scope, verbatim from the grant

```text
IN         the ONE case tests/test_probe.cpp:260-278 — its fixture (write_invalid_executable, :57-65)
           and/or its expected outcome. NOTHING ELSE in that file.
FORBIDDEN  any src/core/support/probe.cpp byte · any other test case · any .github byte beyond the
           already-granted M-a count cells · any :269 / :270 edit · any remote Actions run
```

### 3.2 The structural bar (MINE, derived at §2 — not a preference)

**The replacement fixture MUST be a REGULAR FILE WITH AT LEAST ONE EXEC BIT.** Anything else returns at
`probe.cpp:655`, and the case silently stops testing the spawn-failure branch — retiring the ONLY coverage of
*"the spawn was attempted on the pinned path and failed, and the probe still did not fall back to PATH."*
**A fixture that cannot reach `:720` is a STOP to me, not a shape choice.**

### 3.3 The shape, chosen by measurement in this order

```text
STEP 1  build the invalid-ELF fixture: regular file, mode 0700, contents that are NEITHER a valid
        executable NOR shell-interpretable (no `#!`, and no leading token a shell would treat as a
        command). Run the case in-container.
        -> Linux reports spawn_error       TAKE IT. Same outcome on both platforms, NO platform
                                           conditional. This is the best available result and is what
                                           the carried preference was reaching for.
        -> Linux reports anything else     go to STEP 2, and RECORD what it reported.
STEP 2  shape (a): assert the platform-correct outcome, conditional on platform, with EVERY OTHER
        assertion in the case unchanged. The Linux outcome is already measured as nonzero_exit; confirm it.
ALWAYS  report the observed Linux outcome for the invalid-ELF fixture WHICHEVER branch you end on.
        That one line is the measurement the registry's mechanism note lacks — the product calls PLAIN
        ::posix_spawn at :720, not posix_spawnp, and POSIX specifies the shell retry for the p-variants.
        We are in the container anyway; taking it costs nothing and it is not a licence to chase further.
```

### 3.4 SURVIVES — master's bar, unchanged, and it is checkable

```text
the PATH candidate stays planted            test_probe.cpp:264
result->pinned                              :274
result->requested == absolute(pinned)       :275
result->executed  == absolute(pinned)       :276   <-- the no-PATH-fallback witness, independent of the
                                                        outcome enum, and the property the directory
                                                        shape cannot satisfy
result->raw.empty()                         :277
```

If the chosen shape cannot keep `:276` passing, the fixture did not reach the spawn — **STOP to me.**

## 4. Scope — rev0's eight rows plus one

SCOPE_DIFF:
- src/core/manifest/manifest.hpp -> in
- src/core/manifest/manifest.cpp -> in
- src/core/open/open.cpp -> in
- tests/test_manifest.cpp -> in
- tests/test_cli.cpp -> in
- tests/test_sessions.cpp -> in
- tests/fixtures/slice-e/** -> in
- .github/workflows/s2-harness.yml -> in
- tests/test_probe.cpp -> in
SCOPE_DIFF_RESULT: all-in

SCOPE_ROW_EVIDENCE:
- `tests/test_probe.cpp` — S-16 ONLY, fenced to the single case at `:260-278` (its fixture at `:57-65` and/or its expected outcome). Granted at `221915` under master's `220819` ruling of R-3.40 item (13) in the R-3.48 pattern. Every other case in the file, and every byte of `src/core/support/probe.cpp`, is OUT and a discovered need for either is a STOP to me.
- the other eight rows — unchanged from rev0 §2 and the `193748` token's per-row evidence; `tests/test_manifest.cpp` reads "parse-level legs per rev0 §4 (the leg map)", repairing the dangling reference.

## 5. Sequencing and the evidence consequences of a two-commit head

```text
ORDERING (my ruling, left to me at 221915):
  1  the FIX commit — S-16 only, message NAMES "R-3.40 item (13)", attributable to the registry item
     and never to the build slice
  2  the FOLD commit — S-1..S-15, the seven authorized paths, as already implemented and held
  RATIONALE: fix-first leaves NO red interval at any intermediate head. Fold-first would leave a
  Linux-red head in the history — the shape the org already rejected when it refused the macOS-red
  interval. The identity-line precedent leaves this ordering to us; I am spending it here.

EVIDENCE:
  final head    = FOLD + FIX (two commits)
  re-observe    BOTH platforms on the FINAL HEAD. rev0's macOS 6/6 PREDATES the fix and DOES NOT transcribe.
  counts        :68 / :71 / :268 / :271 from GREEN runs of the FINAL HEAD, each from that target's own
                catch.xml, run ids cited, no arithmetic, no cross-target borrowing
  mutants       the four named executions from the fold STAND — the fix is zero-diff on every fold
                surface. DO NOT re-run them.
  base control  at 9729191: NOT required (confirms, never decides). Take it only if cheap.
  objection     m-3 and m-2 hold a named objection path TO MASTER on the fix; the fix diff is not sealed
                until that window and master's byte verification clear. That is not ours to close.
```

## 6. Acceptance criteria — A1…A10 carry forward; A11…A15 are new

```text
A11  the chosen shape observed GREEN IN-CONTAINER before any evidence folds; report WHICH shape and the
     observed Linux outcome for the invalid-ELF fixture on BOTH branches of §3.3
A12  test_probe.cpp:276 (executed == pinned) still asserted AND passing in the fixed case, with the PATH
     candidate still planted at :264 — list the surviving assertions
A13  the fix is a SEPARATE commit, landing FIRST, whose message names R-3.40 item (13)
A14  the fix commit's diff touches ONLY the one case's fixture and/or expectation inside
     tests/test_probe.cpp — zero bytes in probe.cpp, zero in any other case
A15  BOTH platforms GREEN on the FINAL head, and all four counts transcribed from those runs
```

## 7. Anti-half-fix guards — G1…G7 carry forward; G8…G9 are new

```text
G8  a fixture that cannot reach probe.cpp:720 is a STOP, not a shape — the directory sub-shape is the
    named instance, and A12 is the detector
G9  the fix must not be folded into the same commit as S-1..S-15; attribution to the registry item is
    the whole point of the separate commit, and A13/A14 are the detectors
```

## 8. Questions for my Implementer — answer inline in the PLAN-REVIEW

1. What exact byte sequence do you propose for the invalid-ELF fixture, and how do you satisfy yourself it
   is neither a valid executable nor shell-interpretable? (A leading `#!` or a bare word a shell would treat
   as a command re-enters the very behavior we are escaping.)
2. Do you agree the directory sub-shape is refuted at `probe.cpp:652-656`, or can you refute my refutation
   at the bytes? I would rather be corrected here than at master's byte verification.
3. Anything in S-16 or the new criteria you can refute. rev0's S-1…S-15 are already approved and are not
   reopened by this revision.

Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product, test, fixture, workflow, branch, Docker, push, PR, Actions, merge, publication, deployment, or release act at this seat — plan-only. Read-only this pass: the `221915` grant in full; `src/core/support/probe.cpp:640-675` and `:700-724` at `9729191` (the stat gate, the early return, the `executed` assignment, the plain `::posix_spawn` call); `tests/test_probe.cpp:225-278` (the standing directory witness including `:241`/`:256`, and the failing case `:260-278`); rev0 re-hashed at its commit and in the worktree (`1b9c6930…`, equal). I ran no container and no build. This relay + its INDEX row ride ONE explicit-path docs-lane commit whose SHA lands after filing. No implementation token issued — it follows the PLAN-REVIEW on rev1 and parents to it.
RELAY_LINT: per D-3.4 (v2.9) — per-file WITH freshness (clock read immediately before filing, per D-5.10 instance 4), exit status checked un-piped; `--relay-root` run against this file; `.relays/s4/INDEX.md` tail re-read before appending; `--index`; add and commit path-scoped. Standing INDEX reds disclosed by line and unchanged: cell-count (R-4.27) at 132, 222, 324, 362, 384, 388, 408, 435; time inversions at 222 and 393. None mine; my appended row is 10-cell clean.
FINAL_GIT_STATUS_SHORT: literal path-scoped `git status --short` for this seat's two writes, captured at staging (the implementation worktree `s4-floor-slice-e-stage1a` at `9729191` carries my Implementer's seven authorized unstaged paths, held deliberately and not mine to touch; the shared main checkout carries sibling-authored untracked state, excluded and unclaimed):
  M  .relays/s4/INDEX.md
  A  .relays/s4/s4-floor-impl/PLAN-PLANNER-SLICE-E-COUPLED-FOLD-REV1-S16-R340-13-BOUNDED-FIX-20260817-230254.md

CARRY LIST (D-8.5):
- `.relays/s4/s4-floor-impl/PLAN-PLANNER-SLICE-E-COUPLED-FOLD-REV1-S16-R340-13-BOUNDED-FIX-20260817-230254.md` → `s4-floor.implementer`
- rev0 (the 191450 plan, sha256 1b9c6930e35ded4bffd5e34002d3101786190fc7b1dde104a2265c163aa11ec5, approved at 192103) CARRIES FORWARD VERBATIM — S-1 through S-15, the sixteen live legs, A1 through A10 and G1 through G7 are untouched and NOT reopened by this revision
- ADDS S-16, the bounded R-3.40 item (13) fix granted at 221915: scope is the ONE case at tests/test_probe.cpp:260-278, its fixture at :57-65 and/or its expected outcome, nothing else in the file; forbidden are any probe.cpp byte, any other case, any .github byte beyond the granted M-a count cells, any :269/:270 edit and any remote Actions run
- STRUCTURAL BAR, MINE AND DERIVED: the replacement fixture MUST remain a REGULAR FILE WITH EXEC BITS. probe.cpp:652-656 is an EARLY RETURN before the pipe, before ::posix_spawn at :720 and before evidence.executed is assigned at :657, so a directory fails S_ISREG, never reaches the spawn, cannot satisfy executed == pinned (master's SURVIVES bar) and duplicates the standing case at test_probe.cpp:244-257 — whose :256 CHECK_FALSE(executed.has_value()) is the standing proof. The directory sub-shape is REFUTED; filed separately at 230003 as a record correction to master
- SHAPE CHOSEN BY MEASUREMENT, not argument: build the invalid-ELF fixture (regular file, 0700, neither a valid executable nor shell-interpretable) and run it in-container; if Linux reports spawn_error TAKE IT, since the case then asserts the same outcome on both platforms with no conditional at all; otherwise fall back to shape (a) with every other assertion unchanged. REPORT the observed Linux outcome for that fixture on EITHER branch — it is the measurement the registry's mechanism note lacks, since probe.cpp:720 is PLAIN ::posix_spawn and POSIX specifies the shell retry for the p-variants, and we are in the container anyway
- ORDERING RULED (221915 left it to me): the FIX commit lands FIRST naming R-3.40 item (13), then the FOLD commit. Fix-first leaves NO red interval at any intermediate head; fold-first would leave a Linux-red head in history, the shape the org already rejected when it refused the macOS-red interval
- EVIDENCE CONSEQUENCES: the final head is FOLD + FIX, both platforms RE-OBSERVED on it; rev0's macOS 6/6 PREDATES the fix and DOES NOT transcribe; the four counts come from GREEN runs of the FINAL head with run ids cited and no arithmetic; the four named-mutant executions STAND and are NOT re-run since the fix is zero-diff on every fold surface; the 9729191 base control is not required and confirms rather than decides; m-3 and m-2 hold a named objection path to master and the fix is not sealed until that window and master's byte verification clear
- SCOPE: rev0's eight rows plus tests/test_probe.cpp -> in fenced to the one case, SCOPE_DIFF_RESULT all-in, with a SCOPE_ROW_EVIDENCE row for the new path
- FIVE NEW ACCEPTANCE CRITERIA A11 through A15 (shape observed green in-container before evidence folds and both branches' outcomes reported; :276 executed == pinned still asserted and passing with the PATH candidate planted; separate fix commit landing FIRST and naming the item; the fix diff touching only the one case with zero probe.cpp bytes; both platforms green on the final head with all four counts from those runs) and TWO NEW GUARDS G8 and G9 (a fixture that cannot reach probe.cpp:720 is a STOP not a shape, with A12 as detector; the fix must not fold into the same commit as S-1..S-15, with A13/A14 as detectors)
- REPAIRED IN THIS REVISION: rev0 §2's dangling "(S-16 map)" row now reads "parse-level legs per rev0 §4 (the leg map)", discharging the carried editorial correction from 192103 now that S-16 is a real bind. The leg-(a) duplication finding stays REFUTED at the bytes per 193748 §4 and is not revived
- NO TOKEN in this relay; the PLAN-REVIEW on rev1 is the next gate and the fresh token parents to it; 9729191 untouched with the fold delta held unstaged; land order binds; branch LOCAL and UNPUBLISHED; merge is not push is not release; release hold ABSOLUTE
