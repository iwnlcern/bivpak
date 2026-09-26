# rev37 walks — the records behind plan rev37 (m-4's `K3_TIE: strict` folded)

Filed with rev37 for the implementer's exact-hash review; m-4's word `master/relays/intg-2b-wiring-act/DESIGN-planner-20260925-151817.md`, carried by master's `…/PLAN-master-planner-20260925-154632.md`.
Every walk ran in the pair Planner's scratchpad; the real evidence home and `s2b-runners-aY2Suc` were read, never written. The scripts carry their scratch paths as they ran.

## generator/

`gen37.py` writes rev37 from the committed rev36 blob: the block's code line and K-3 comment (`>=` → `>`), the instruments description, the Task 9 producer and series call, Task 9 Step 4's prose, and `hist37.md` (the history entry, with the corrected block's digest substituted).

## producer/ — Task 9's new lines producing `$EVID/series_verdict.rev37.py`

`snip.sh` is rev37's runner from the rev37 comment through the `py_compile` line, sourced by `walk.sh <case>` on a scratch home holding Task 0's `series_verdict.py`, with a scratch RUNNERS (`plan_blocks.py`, `plan-path.txt`) and `shim/` first on `PATH`.
`results.txt`: absent → produced and pinned; present and correct → accepted; present with Task 0's old bytes, a symlink, a dangling symlink, `plan-path.txt` naming rev36 (the old block), a missing plan, a failed `mv`, a failed extract, a failed compile → each STOPs at its own line, and Task 0's copy stays intact in every case.
The mutant without the stage digest check (`mut-nostagecheck.sh`) lets the old block land under the final name, where every later run would refuse it — so the stage check is load-bearing.

## reducer/results.txt

Task 0's copy (the old block) against the corrected block on: ten copies each of the real B and H0 draws (the pair's `142508` probe), a constant 3-vs-3 series, m-4's sixth series ([2, 3×9] → [3×10], delta 0.10) and m-4's seventh ([2×5, 3×5] → [3×5, 4×5], delta 1.00).
The old block returns SHIFTED on all four; the corrected block returns NOT-SHIFTED on the three nulls and SHIFTED on the real one-failure shift.

## step0prime/

`w37tok.sh` runs `resume.sh` (unchanged, `192369f3…`) from a mirror of `s2b-runners-aY2Suc` on rev37's lock, the carry's `t-oracle.txt` rewrite simulated in the YES case only; `w37tok.out` is its output.
