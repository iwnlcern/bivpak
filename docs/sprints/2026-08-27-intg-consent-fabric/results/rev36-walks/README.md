# rev36 walks — the records behind plan rev36 (`e87c999a…`)

Filed with the rev36 plan for the implementer's exact-hash review (plan-37), after impl-11's Task 9 STOP `intg-substep2b/IMPL-pair-implementer-20260925-130242.md`.
Every walk ran in the pair Planner's scratchpad on MIRRORS of the real evidence home `s2b-intg-substep2b-impl-1-y3iCLB` (copied `cp -Rp`); the real home was read, never written.
The scripts carry their scratch paths as they ran; rerunning them needs those paths re-pointed.

## generator/

`patch9.py` turns rev35's derived task-9 runner into rev36's (each edit an exact replacement asserted to match once); `gen36.py` writes rev36 from the committed rev35 blob, the two runners and `hist36.md` (the history entry).

## preservation/ — Task 9 Step 0 with the B Linux leg

`snippet.sh` is rev36's runner from the preservation comment to the post-preservation `BLEG` assertion, sourced by `walk.sh <case>` with `shim/` first on `PATH` (fault-injecting `mv` and `python3`, counted per call).
`results.txt` holds 49 verdict lines: 27 structural cases, 9 `mv` failures (two with a failing rollback), 1 more rollback failure on a B file, 4 corrupting moves, 5 python failures, and 3 mutants that each remove one guard (`mut-*.sh`).
In the YES case the attempt publishes as `attempts/task9-H0-99136ca/` with MANIFEST.pre == MANIFEST.post, 36 B files byte-identical and Task 0's fifteen intact.

## lines/ — the Linux skip-set gate and the E3 read

`snip.sh` is rev36's runner from the skip-set lines through the E3 receipt (the two B cell-gate lines between them included), run by `walk.sh <case>` on the mirror; `results.txt` holds YES and eight NO cases, each stopping at its own line.

## consumers-after-219.txt

Every consumer after rev35's line 219, run unchanged on the mirror, including rev35's line 219 itself (`IndexError`, rc 1) and `xmlcases.py e3` (rc 5 on a green case).
`series_verdict.py` there runs on ten COPIES each of the one real B draw and the one real H0 draw; its SHIFTED verdict is the K-3 tie reported to master, not a measurement of the series.

## step0prime/

`w36tok.sh` runs rev36's `resume.sh` (unchanged, `192369f3…`) from a mirror of `s2b-runners-aY2Suc` on rev36's lock; the carry's `t-oracle.txt` rewrite is simulated in the YES case only; `w36tok.out` is its output.

## series-draw/

`run.sh` runs ONE series draw (`B-1` at B) exactly as Task 9's loop line does, in one disposable container, then `selftest_summary.py`; `run.out` is its output.
Result (2026-09-25 14:12–14:23): container rc 0; the four phases, the suite aggregate and `container_payload_rc` 0; head receipt `expected=observed=186adf7d…`; `selftest_summary.py` rc 0 with population 1013 (equal to B's single draw) and 4 failures, all four R-4.35 family names (B's single draw had 3).
The three read-only FILE binds into the mounted `series/` leave three EMPTY mountpoint files (`linux-container.sh`, `linux-suite.sh`, `observer-unset-names.txt`) in `series/` on the host; `series_verdict.py` reads only the labelled draw directories, and `finalize.py list` would carry them as empty files.
