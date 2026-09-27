# rev39 walks — the records behind plan rev39 (MUST-H-1 folded; the lighter re-gate)

Filed with rev39 (`d5a868d3fc8f020398b3b4ac6422f2d0c971f15c98d51bafdc009a5067ad4a80`) for the implementer's exact-hash review, after m-3 `DESIGN-planner-20260926-160359.md` (MUST-H-1) and master `PLAN-master-planner-20260926-164725.md`, under the operator's direction "lighter regate pls".
Every walk ran in the pair Planner's scratchpad on clones and mirrors; the real evidence home, the candidate worktree and `s2b-runners-UG0MP0` were read, never written.
The scripts carry their scratch paths as they ran.
Every walked block is byte-equal to its BLOCK in the final rev39: `resume.sh` e2d6bde3, `regate.sh` 0f130dc2, `headgate.sh` d83e0c1b, `c10-mutants.sh` c2f35e6c, `finalize.py` 8958e54e, `task-10` fb09e2f0, `task-11` 022a0416; `task-9` is unchanged from rev38 at eb3a4adf and `task-0` at b782ae10.
`plan_blocks.py check` returns rc 0 for tasks 0, 9, 10 and 11 on the final rev39.

## generator/

`gen39.py` writes rev39 from the committed rev38 blob (`a342a9c5…`), inserting `task8c.md` (Task 8c: c10, the MUST-H-1 fix, with the `c10-mutants.sh` BLOCK) and `task9b.md` (Task 9b: the lighter re-gate at c10, with the `regate.sh` BLOCK).

## step0prime/ — resume.sh carrying Task 9's receipts

`wresume.sh` runs rev39's `resume.sh` from a mirror of `s2b-runners-UG0MP0` on the final rev39 lock.
The pass case carries 31 files (Task 0's 10 receipts, Task 9's 11, the 10 gate files), all byte-equal, `task-9.sh` keeping mode 500; with no Task 9 in the old directory it carries 20.
done-red, exit-mismatch, sh-altered, record-mismatch, receipt-absent and done-symlink each STOP with no new directory and the pointer unchanged.
`wconsumer.sh` then runs the CONSUMER, `run-task.sh 10`, from each carried directory: with Task 9 carried it reaches only the absent GO (`no-continuation`); without it, it STOPs at line 16 — the latent rev38 defect (Task 0's receipts alone were carried) that rev39 closes.

## regate/ — Task 9b

`wregate.sh` runs `regate.sh` on a scratch clone at c9 with a synthetic c10 against a mirror of the real home's inputs; ctest is stubbed on `PATH` (the implementer measures the real `harness-e2`), and the head gate is stubbed in a walk-only plan copy for the c11 branch.
Both pass branches: counts unchanged (no c11) and counts moved (c11 committed through the head gate).
21 NO cases each STOP at their own guard (the list is `wregate.out`), including a tuple with `failures=1`, which the first draft caught only in `cellpatch` — rev39 gates `failures=0` in every tuple explicitly.

## task10-11/ — the Task 10 and Task 11 reads of `R/`

`frag10.sh` and `frag11.sh` are the rev39 lines of Task 10 and Task 11 that read `R/`, each line verbatim from the final block (checked by fixed-string grep).
Pass on both branches (`f/yes-unchanged-full`, `f/yes-moved-full`: the regate walk homes plus `heads/c10/linux-container.rc` and `B/linux-container.rc`, which the regate walk's stubs do not write and which `headgate.sh` line 40 and Task 9 write in a real run).
Each NO home STOPs Task 10 at its own line; `no-H` and `oldH-only` (no `R/` at all, only Task 9's `H.txt`) STOP both tasks.
The NO homes were built on the first regate walk's moved home (their H values differ from the re-run's; each mutates only its own file).

## c10-mutants/ — the precondition arm of `c10-mutants.sh`

`walk.sh` runs the block on clones of the regate walk's c10: not-at-c10, dirty, record-exists, patch-absent, patch-path, patch-hunks, patch-stale (does not apply), work-exists and a dangling work link each STOP before creating the work directory, with the tree clean.
The pass direction reaches `build-M-H1-PRE` (a clone has no configured build) with the tree clean.
The mutant arm itself — build, red the named cases, revert — runs only at the real c10 with its real build; it is not walked here and is disclosed as such.
rev39 creates the work directory only after every patch check passes.

## headgate/ — the new `c10|c11` labels

`walk.sh`: c10, c11 and c8T pass the label case; c12, c9 and an empty label STOP at `label`; with `commits.c10.txt` at HEAD, c10 runs on to the macOS build.

## producer-gate/

The discriminator for `baseline-substep2b-rev39.txt`: see `../producer-gate/README.md`.
