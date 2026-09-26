# rev38 walks — the records behind plan rev38 (MUST-2B-52 folded)

Filed with rev38 for the implementer's exact-hash review, after `intg-substep2b/PLAN-REVIEW-pair-implementer-20260925-171756.md`.
Every walk ran in the pair Planner's scratchpad on mirrors; the real evidence home and `s2b-runners-aY2Suc` were read, never written. The scripts carry their scratch paths as they ran.

## generator/

`gen38.py` writes rev38 from the committed rev37 blob; `hist38.md` is the history entry.

## preservation/ — Task 9 Step 0 with the rev38 CONFINEMENT guard

`snippet.sh` is rev38's runner from the preservation comment to the post-preservation `BLEG` assertion (84 lines), sourced by `walk.sh <case>` on mirrors of the real home with `shim/` first on `PATH`; `run-all.sh` drove all 56 cases plus 4 mutants into `results.txt`.
New in rev38: a dangling symlink at a root input name, a symlink to an outside sentinel / a dangling symlink at rev37's old stage name, a dangling symlink at `work/B-leg.names`, and a pre-existing `H.txt` or `commits.c9.txt` each STOP before any write (home unchanged, sentinel byte-identical); a regular file at the old stage name is kept and the run passes.
`mut-nolinkguard.sh` removes only the symlink guard: with a dangling `work/B-leg.names`, rev36's approved `BLEG` write then CREATES an 802-byte file outside the home and the run passes — the guard is load-bearing, and the class was live before rev37.
One behaviour change from rev36: a symlink inside `B/` (case `bleg-symlink`) now STOPs at the guard instead of moving with the B leg.

## producer/ — the rev38 reducer producer

`snip.sh` is rev38's producer lines; `snip-rev37.sh` is rev37's, run once as the CONTROL that reproduces the implementer's finding (the outside sentinel rewritten, the symlink renamed into the final name). `results.txt` holds both.

## step0prime/

`w38tok.sh` runs `resume.sh` (unchanged) from a mirror of `s2b-runners-aY2Suc` on rev38's lock; `w38tok.out` is its output.
