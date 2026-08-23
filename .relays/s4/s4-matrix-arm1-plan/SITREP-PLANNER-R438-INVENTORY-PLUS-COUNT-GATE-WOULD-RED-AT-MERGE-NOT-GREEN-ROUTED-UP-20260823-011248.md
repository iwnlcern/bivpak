## SITREP — R-4.38 inventory delivered, and it surfaced something the row has backwards: the macOS count gate does not green over the invisible coverage, it REDS. Measured 385 against a `want` of 410, and the 25-case gap is exactly the binary split T1 performed

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-matrix-r438-inventory-count-gate-reds
PARENT_DISPATCH_ID: s4-matrix-wave-a-t4-panel-adjudicated
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-T4-PANEL-ADJUDICATED-FIX-CLEARED-SECURITY-FINDING-UP-NITS-DISCLOSED-20260822-233156.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/SITREP-PLANNER-T4-A1-CONCURRED-AND-LOCKED-PANEL-MAY-CONVENE-ON-6BA01EF-20260822-231328.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: routing only. `.github/` is m-3's surface by the standing R-4.38 ownership ruling and I propose no edit and touch no workflow byte. This is a merge-readiness measurement that belongs in front of the operator before any Wave-A merge, and a correction to R-4.38's registered characterization that RESIDUALS is master's pen to make. No merge, push, PR mutation, remote CI, schema act, publication, deployment, or release. The release hold is ABSOLUTE
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: authorized pre-edit T4 `29120d09891bfc46e80635c2212befa22a0e2604` on FINAL T3 `70601fc201b3c41d2542d82399787b5febcbf03c`
CANDIDATE: local T4 `6ba01ef92ef5052b317f6210fa202d5577e1e6c1` — unchanged by this relay
FROM: s4-matrix.planner
TO: s4.orchestrator-planner
CC: operator, s4-matrix.implementer, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: R-4.38 per-candidate inventory complete (1 to 5 Catch2 binaries across the four pinned heads, 80 of 468 cases invisible at T4); and a polarity correction — at the candidate the macOS gate measures successes 385 against want 410, the 25-case delta is exactly test_probe.cpp which T1 split out of biv_tests while the want cell stayed pre-split, so the gate REDS at merge rather than greening; main-side status and the Linux gate are explicitly UNMEASURED

## 1. The inventory you asked me to continue

Measured at each pinned head. My extractor is self-validated: per head, the count of
`add_test(NAME …)` rows it parsed equals the raw count of `add_test(` occurrences, so no row
shape escaped it. My first extractor did not pass that check — it saw 1/3/4/4/5 rows against
totals of 6/8/9/9/10 because it only matched the single-line form — and I discarded it.

```text
head                      ctest rows   Catch2 binaries   unseen by the count gate
main @ 0d48944 (older)         8             1           none
T1 FINAL  00c06d9             10             3           probe, subprocess
T2 FINAL  7688bbd             11             4           + repo_git
T3 FINAL  70601fc             11             4           (unchanged)
T4 cand   6ba01ef             12             5           + repo_engine
```

Case counts at the T4 candidate, which is where the disclosure has to be concrete:

```text
biv_tests               388 cases   <- the ONLY binary either count gate runs
biv_probe_tests          25         unseen
biv_subprocess_tests     12         unseen
biv_repo_git_tests        6         unseen
biv_repo_engine_tests    37         unseen
total                   468
invisible to the gate    80  (17% of the suite; all still EXECUTE under ctest)
```

Correction to my own framing: I initially labelled `0d48944` "pre-Wave-A". It is not — it is an
older main commit from earlier this month, and the true Wave-A base is `6047ab0`, the parent of
T1's first commit `21c6d8c`. The row above is relabelled accordingly.

## 2. The polarity correction

R-4.38 records the gap as benign: "`biv_tests` staying flat is candidate-neutral precisely
BECAUSE the new coverage lives elsewhere — the gate greens over RISING INVISIBLE coverage."

**`biv_tests` did not stay flat. It fell by 25, and the `want` cell did not follow.**

```text
gate instrument, run at the candidate    ./build/ci-macos/biv_tests -r xml
  got   successes 385, failures 0, expectedFailures 0, skips 3
  want  successes 410, failures 0, expectedFailures 0, skips 3
  VERDICT  COUNT GATE FAILED: expected 410, got 385
```

The mechanism, closed exactly:

```text
main   CMakeLists.txt:122  target_sources(biv_tests PRIVATE tests/test_probe.cpp)
T4     CMakeLists.txt:170  add_executable(biv_probe_tests tests/test_probe.cpp)
tests/test_probe.cpp holds 25 TEST_CASEs; biv_probe_tests lists 25 cases
want total  410 + 3 skips = 413  == the PRE-split composition
measured    385 + 3 skips = 388  == the POST-split composition
delta       413 - 388 = 25       == test_probe.cpp exactly
```

T1 moved `test_probe.cpp` out of `biv_tests` into its own binary. The gate's `want` still expects
those 25 cases inside `biv_tests`. The gate is not blind to the split — it is calibrated against
the world before it.

Both `want` blocks are pre-split: macOS 410+3 and Linux 412+1 both total 413, and both gates run
only `biv_tests` (`:56` and `:258`). There is no second binary cell anywhere in the workflow.

## 3. Run validity, established before I read any of it

The 385 is not a stale-build artifact. Three independent confirmations agree:

```text
binary --list-tests                                     388
static TEST_CASE count over biv_tests' TRUE source set  388
gate XML run  385 successes + 3 skips                   388
worktree at 6ba01ef, zero dirty paths, binaries newer than sources, rc=0, empty stderr
```

I discarded three instruments before trusting any number: a `sed` expecting `matching test
cases` when the unfiltered form prints `N test cases`; an `awk` range for `biv_tests`' source
block that ran past its terminator and swallowed `test_probe.cpp`, inflating the static count to
413 — which coincidentally equalled the `want` total and would have made the gate look
consistent; and a regex source-set extractor that found 14 files where the block has more.

**That second one is worth naming.** A contaminated extractor produced a number that agreed with
the `want` cell and would have closed this investigation with "gate is fine." It agreed for the
same reason the `want` is wrong — both included the probe cases. A wrong instrument that
reproduces the wrong reference value is the most expensive kind of green.

## 4. What I have NOT measured, stated as such

- **Whether main is currently consistent.** Main's build is stale — binary dated 2026-08-09
  against sources dated 2026-08-20 — so its `--list-tests` reading of 254 is meaningless and I
  discarded it rather than report it. I did not rebuild main. **Open question:** if main is
  consistent at 413, this failure is introduced AT MERGE; if main is already inconsistent, the
  gate is red today and Wave-A merely inherits it. That distinction changes who owns it and I
  will not guess it.
- **The Linux gate.** Unmeasured. Its `want` total is also 413 and it runs the same source set,
  so the same mechanism is expected — but expected is not measured, and a Linux number must come
  from a Linux run.
- **T1, T2, T3 exact counts.** Only T4's binary was measured. All four carry the split, so all
  four have `biv_tests` without the 25 probe cases while `want` expects them; the direction is
  certain, the exact per-head values are not.

## 5. Ask

Two, both routing:

1. Carry this to master as a correction to R-4.38's characterization — the row's own text cites
   ``want`` 385, which is the post-split value the binary actually produces, while the workflow
   carries 410. Registry and workflow disagree, and the workflow is what runs.
2. Put it in front of the operator before any Wave-A merge decision. A merge that reds a required
   count gate is the operator's call to make knowingly, not a surprise to discover afterward.

I propose no fix. `.github/` is m-3's by the standing ruling, the repair is a gate-design act, and
this lane's refusal to touch it in-lane was correct and stays correct.

T1 `00c06d9`, T2 `7688bbd`, T3 `70601fc` FINAL; T4 IMPLEMENTED at `6ba01ef`, panel-adjudicated,
FINAL held pending master's F-URL-1 disposition. Merge is not push and neither is release; the
release hold is ABSOLUTE.

ACTIONS_GIT_REF: none — no edits made at this seat; no product, test, workflow, branch, ref or worktree moved, and `6ba01ef` is untouched by this relay. Read-only at my seat: `git show` of `CMakeLists.txt` and `.github/workflows/s2-harness.yml` at five heads; `add_test`/`add_executable`/Catch2-link enumeration with a self-validating row-count assertion; `--list-tests` on all five candidate binaries; one `biv_tests -r xml` execution of the gate's own instrument in the existing read-only T4 worktree build with HEAD, cleanliness, mtime, rc and stderr all asserted first; static `TEST_CASE` counts; and `git log -S` provenance for the `want` cell. Three instruments were discarded as invalid before any number was reported. No build was created or modified, no workflow byte touched, no merge, push, PR mutation, or remote CI. Docs lane: this relay and its INDEX row ride ONE explicit-path commit.
FINAL_GIT_STATUS_SHORT: this relay and its INDEX row are this seat's only working-tree delta at commit time; `git status --porcelain` over `harness/`, `src/`, `tests/`, `CMakeLists.txt`, `.github/` is empty; the shared checkout carries sibling-authored untracked paths, preserved and unclaimed
RELAY_LINT: all three arms before commit — exact-file WITH freshness; `--index` error set path-normalized and diffed against the pre-append blob; `--relay-root` run with this relay present AND moved aside, requiring identical error sets. `substantive_actions_ref` and `implementation_work_claimed` measured False on the finished bytes; `operational_token_text` carries no bare token. INDEX tail re-read for NEW INBOUND addressed to this seat, not only for monotonicity.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/SITREP-PLANNER-R438-INVENTORY-PLUS-COUNT-GATE-WOULD-RED-AT-MERGE-NOT-GREEN-ROUTED-UP-20260823-011248.md` → TO `s4.orchestrator-planner`
- R-4.38 PER-CANDIDATE INVENTORY DELIVERED with a SELF-VALIDATED extractor (per head, parsed `add_test(NAME …)` rows == raw `add_test(` count, so no row shape escaped; my first extractor saw 1/3/4/4/5 against totals 6/8/9/9/10 and was DISCARDED): Catch2 binaries go 1 (older main `0d48944`) → 3 (T1 `00c06d9`) → 4 (T2 `7688bbd`) → 4 (T3 `70601fc`) → 5 (T4 `6ba01ef`); at T4 the counts are biv_tests 388, probe 25, subprocess 12, repo_git 6, repo_engine 37 = 468 total, of which **80 cases (17%) are invisible to the count gate** while all still EXECUTE under ctest. My own label correction: `0d48944` is an OLDER MAIN COMMIT, not pre-Wave-A; the true Wave-A base is `6047ab0`, parent of T1's first commit `21c6d8c`
- POLARITY CORRECTION — R-4.38 HAS THIS BACKWARDS: the row says `biv_tests` staying flat is candidate-neutral and the gate GREENS over rising invisible coverage. **`biv_tests` did not stay flat — it FELL BY 25 and the `want` cell did not follow.** The gate's own instrument at the candidate returns successes 385 / skips 3 against want successes 410 / skips 3 → COUNT GATE FAILED: expected 410, got 385. The gate is not blind to the split; it is CALIBRATED AGAINST THE WORLD BEFORE IT
- MECHANISM CLOSED EXACTLY: main `CMakeLists.txt:122` has `target_sources(biv_tests PRIVATE tests/test_probe.cpp)`; T4 `CMakeLists.txt:170` has `add_executable(biv_probe_tests tests/test_probe.cpp)`; `test_probe.cpp` holds 25 TEST_CASEs and `biv_probe_tests` lists 25; want total 410+3 = 413 = PRE-split composition, measured 385+3 = 388 = POST-split, delta 25 = test_probe.cpp EXACTLY. Both `want` blocks are pre-split (macOS 410+3, Linux 412+1, both totalling 413) and both gates run ONLY `biv_tests` (`:56`, `:258`) — there is no second-binary cell anywhere in the workflow
- RUN VALIDITY ESTABLISHED BEFORE READING: three independent confirmations agree at 388 — binary `--list-tests`, static TEST_CASE count over the TRUE source set, and the XML run's 385+3 — with worktree at `6ba01ef`, zero dirty paths, binaries newer than sources, rc=0 and empty stderr. THREE INSTRUMENTS DISCARDED FIRST: a `sed` expecting `matching test cases` where the unfiltered form prints `N test cases`; an `awk` source-block range that overran its terminator and swallowed `test_probe.cpp`, inflating the static count to 413; and a regex extractor finding 14 files where the block has more
- THE MOST EXPENSIVE KIND OF GREEN, NAMED: that contaminated `awk` produced 413 — EXACTLY the `want` total — and would have closed this investigation with "the gate is fine". It agreed with the reference value FOR THE SAME REASON THE REFERENCE IS WRONG: both included the probe cases. A wrong instrument that reproduces the wrong reference value is the hardest false green to catch, and only the source-set contamination check separated them
- EXPLICITLY NOT MEASURED, NOT GUESSED: (i) whether MAIN is currently consistent — main's build is STALE (binary 2026-08-09 vs sources 2026-08-20) so its `--list-tests` 254 is meaningless and was DISCARDED, and I did not rebuild; the open question is whether this failure is INTRODUCED AT MERGE (main consistent at 413) or ALREADY RED TODAY (main inconsistent, Wave-A merely inherits), which changes OWNERSHIP and I will not guess it; (ii) the LINUX gate — same mechanism expected since its want totals 413 over the same source set, but expected is not measured; (iii) T1/T2/T3 exact counts — all four carry the split so the DIRECTION is certain, the per-head values are not
- ASK, BOTH ROUTING, NO FIX PROPOSED: carry this UP to master as a correction to R-4.38's characterization (the row's own text cites `want` 385 — the POST-split value the binary produces — while the workflow carries 410, so registry and workflow DISAGREE and the workflow is what RUNS); and put it in front of the OPERATOR before any Wave-A merge decision, because a merge that reds a required count gate is the operator's call to make knowingly rather than discover afterward. `.github/` is m-3's by the standing R-4.38 ownership ruling, the repair is a gate-design act, and this lane's refusal to touch it in-lane was and remains correct
- T1 `00c06d9` / T2 `7688bbd` / T3 `70601fc` FINAL; T4 IMPLEMENTED at `6ba01ef`, panel-adjudicated, FINAL HELD pending master's F-URL-1 disposition; no workflow byte touched; no remote CI, push, PR mutation, merge, publication, deployment or release; release hold ABSOLUTE
