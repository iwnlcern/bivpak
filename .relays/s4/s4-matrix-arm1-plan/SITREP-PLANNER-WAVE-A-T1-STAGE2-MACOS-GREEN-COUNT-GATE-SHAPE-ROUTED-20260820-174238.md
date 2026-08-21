## SITREP (STAGE 2/4, macOS half — #16) — the scouted probe question is ANSWERED (consistent), the macOS chartered gate is GREEN at the integration head, and stage-4 cells are transcribed per target; but a STRUCTURAL finding routes UP before I spend the Linux leg measuring against a gate whose SHAPE is in question: **#16 splits the suite into THREE binaries while the count gate reads ONE**, so the gate would report a spurious FAILURE for a candidate that in fact increases coverage — and "fixing" it by rewriting the single number to 385 would permanently blind it to 34 cases. Two false alarms of my own were refuted before leaving my seat and are recorded

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-matrix-wave-a-t1-stage2-macos
PARENT_DISPATCH_ID: s4-matrix-wave-a-three-cells-ruled
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-WAVE-A-THREE-CELLS-RULED-CANDIDATE-LOCAL-INDEX-UNION-COMPARE-TEST-OBLIGATION-20260820-163957.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new operator gate — local suite runs as dispatched; but the count-gate SHAPE question needs your word before the Linux leg, since the Linux `want` is single-binary too and would reproduce the same defect at greater cost; no merge, push, PR mutation, or `.github` edit occurred; the release hold is ABSOLUTE
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
FROM: s4-matrix.planner
TO: s4.orchestrator-planner
CC: operator, s4.orchestrator-reviewer, master.orchestrator-planner, s4-matrix.implementer
SUBJECT: SITREP — #16 macOS stage-2 GREEN and probe question answered; per-target stage-4 cells transcribed; count-gate shape routed before the Linux leg

## 1. The integration head, built under the ruled mechanic

```text
candidate       s4-matrix/arm1-t1  d691f9b  (the LOCAL corrected head, per your (C) ruling)
integration     s4-matrix/arm1-t1-reverify  acfdf7b  = candidate + merge of local main
INDEX union     applied per your (B) ruling and PROVEN, not asserted:
                ours 105 rows + theirs 512 rows -> resolved 513
                rows from OURS missing in resolved:   0
                rows from THEIRS missing in resolved: 0
                nothing rewritten, reordered, or dropped; NO non-INDEX conflict appeared
```

The reviewed candidate branch and the shared checkout were never touched — all work is on a
separate integration branch in a scratch worktree.

## 2. The scouted probe overlap — ANSWERED on macOS: consistent

Auto-merge preserved both sides (slice E's platform split and binary invalid-ELF fixture;
#16's shared `TempDir` and re-pointed seal), and the composed state RUNS clean:
`biv_probe_tests` 25 cases, 0 failures. **#16's rewrite of the `spawn_error`/`nonzero_exit`
classification and slice E's platform-split assertion over its changed fixture are
consistent at the new base.** That is the macOS half of the question you scouted; the
Linux half is still owed and I am not recording it as answered.

## 3. macOS chartered gate — GREEN

```text
ctest --preset ci-macos -R '^(biv_tests|harness-selftest|harness-e2|errno_table_gate|generated_envelope_conforms)$'
CTEST_EXIT = 0        all five rows pass        harness-e2 227.52s (durable-600 in effect; the stale 180 ceiling is gone)
```

## 4. Stage-4 cells — transcribed per target from each target's OWN catch.xml (M-a, no arithmetic, no borrowing)

```text
#16 integration head acfdf7b, preset ci-macos, `-r xml` per binary
  biv_tests             successes 385  failures 0  expectedFailures 0  skips 3     exit 0
  biv_probe_tests       successes  25  failures 0  expectedFailures 0  skips 0     exit 0
  biv_subprocess_tests  successes   9  failures 0  expectedFailures 0  skips 0     exit 0

CONTROL, current local main, same preset, same instrument, FULLY built
  biv_tests             successes 410  failures 0  expectedFailures 0  skips 3     exit 0
  s2-harness.yml macOS want                    410 /        0 /                0 /        3   → MATCH: main satisfies its own gate
```

## 5. THE STRUCTURAL FINDING — routed before the Linux leg

At main, `CMakeLists.txt:122` reads `target_sources(biv_tests PRIVATE tests/test_probe.cpp)`
— one binary holds everything, and the gate's one `want` cell measures it correctly.
**#16 deliberately splits the suite**: `add_executable(biv_probe_tests tests/test_probe.cpp)`
and `add_executable(biv_subprocess_tests tests/test_subprocess.cpp)`. So under #16 the
suite spans THREE binaries while the gate still runs `./build/ci-macos/biv_tests -r xml`
against a single cell. Consequences, both bad and in opposite directions:

- **As written the gate FAILS #16 spuriously** — it observes 385 against `want` 410, while
  the candidate actually *increases* coverage (385 + 25 + 9 = 419 successes vs main's 410;
  the 25 probe cases moved binary, they did not disappear, and 9 are genuinely new).
- **The obvious "fix" is worse than the failure** — rewriting the cell to 385 makes the
  gate green while permanently blinding it to 34 cases in the other two binaries. That is
  a gate that cannot fail for the thing it exists to catch, in the shape this lane has
  paid for repeatedly.

So this is not a cell to re-derive; it is a gate whose SHAPE stops matching the suite. The
honest repair is per-target cells (three cells, each transcribed from its own catch.xml,
which §4 above already provides). I have NOT edited `.github/workflows/s2-harness.yml` —
`.github` is outside the granted scope and this is a CI-contract change, not a local
suite run. **Routing it, and holding the Linux leg**: the Linux `want` (412/0/0/1) is
single-binary too, so running that leg now would reproduce the identical finding at the
cost of a full Docker parity build, and would produce a "count cell" whose meaning is
already in question. One word from you and I run it — either as-is with the mismatch
recorded as expected, or after the shape is settled.

## 6. Two false alarms of mine, refuted before leaving my seat — recorded

Both would have been reported as candidate defects had I stopped at the first reading:

- **"Three harness rows fail at the integration head."** `harness-selftest`, `harness-e2`,
  and `generated_envelope_conforms` failed — but `harness-e2` "ran" in 0.04s against its
  normal ~180s. All nine harness modules were dying at pytest COLLECTION because my fresh
  scratch worktree had no `.venv-harness`, so CMake silently fell back to system Python.
  Provisioned from `harness/requirements.lock`; the diagnosis was then confirmed BY THE
  FIX (selftest row 0.34s → 6.10s, passing). An environment gap of mine, not a candidate
  regression.
- **"main is red — 19 failures."** The first control showed main failing 19 cases. Reading
  the failure NAMES showed they were nearly all CLI tests that shell out to the `biv`
  binary — and I had built the control with `--target biv_tests` only, so `biv` never
  existed. A cause assertion cannot see a run that never built its dependency. Rebuilt
  fully: **main is 410/0/0/3, exit 0, an exact match to its own gate.**

And one instrument note worth carrying: my first gate run reported "exit code 0" while
ctest had actually FAILED, because I piped ctest into `tail` and inherited the pipe's
status. Every run since captures the exit code explicitly. An instrument's verdict is its
exit status — and only if that status is actually the instrument's.

## 7. State

Nothing merged, pushed, re-based onto a published ref, or PR-mutated; no `.github` edit;
the schema act remains F+G-fenced and untouched; #17/#19/#20 not started (#19/#20 still
held on the `compare.py` composition, which I own per your (A) ruling and which carries
the test obligation). `origin` untouched; merge ≠ push ≠ release; the release hold is
ABSOLUTE.

ACTIONS_GIT_REF: local re-verification only — created scratch worktrees and the integration branch `s4-matrix/arm1-t1-reverify` (LOCAL, never pushed), applied the ruled INDEX union, configured/built/ran local suites on macOS, and built a control at local `main`. NO merge into any lane branch, NO push, NO PR mutation, NO `.github` edit, NO product or test source edit. Docs lane: this relay + its INDEX row ride one explicit-path commit (SHA lands after filing).
FINAL_GIT_STATUS_SHORT:
none — clean tree (matrix-seat paths; the shared checkout carries sibling-authored state, excluded/unclaimed)
Fresh at 20260820-174238 before this relay + INDEX write; this relay and the INDEX row are this seat's working-tree delta at commit time.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/SITREP-PLANNER-WAVE-A-T1-STAGE2-MACOS-GREEN-COUNT-GATE-SHAPE-ROUTED-20260820-174238.md` → TO `s4.orchestrator-planner`
- #16 integration head `acfdf7b` (candidate `d691f9b` + local main); INDEX union applied per (B) and PROVEN lossless (0 rows missing from either side, 105+512→513, no non-INDEX conflict)
- SCOUTED PROBE QUESTION ANSWERED on macOS: composed state consistent, `biv_probe_tests` 25/0; Linux half still owed, not recorded as answered
- macOS chartered gate GREEN: `CTEST_EXIT=0`, all five rows, `harness-e2` 227.52s (durable-600 in effect)
- STAGE-4 CELLS transcribed per target from each own catch.xml: biv_tests 385/0/0/3 · biv_probe_tests 25/0/0/0 · biv_subprocess_tests 9/0/0/0; CONTROL main fully built 410/0/0/3 = MATCHES its own want
- STRUCTURAL FINDING ROUTED: #16 splits the suite into THREE binaries (`biv_probe_tests`, `biv_subprocess_tests`) while the gate reads ONE — as written it FAILS #16 spuriously (385 vs 410) though coverage RISES to 419; rewriting the cell to 385 would blind the gate to 34 cases permanently. Needs per-target cells, i.e. a gate SHAPE change in `.github` — outside granted scope, NOT edited. Linux leg HELD because its `want` is single-binary too and would reproduce the finding at full Docker cost
- TWO FALSE ALARMS refuted before leaving my seat and recorded: the "three failing harness rows" were my worktree's missing `.venv-harness` (proven by the fix, 0.34s→6.10s); "main is red with 19 failures" was my control built `--target biv_tests` only so the `biv` CLI never existed (rebuilt: main 410/0/0/3 exit 0). Plus: a piped `tail` masked a real ctest failure as "exit 0" — exit status is now captured explicitly
- #17/#19/#20 not started; `compare.py` composition still owed by me with its test obligation; schema F+G-fenced; release hold ABSOLUTE
