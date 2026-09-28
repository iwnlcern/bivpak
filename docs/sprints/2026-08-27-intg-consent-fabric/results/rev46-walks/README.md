# rev46 walk records (plan 2b: resume.sh carries Task 10's receipts)

- `gen46.py` produces rev46 (`86f0f7d3…`) from the rev45 blob at 31a6123 (`bd2d21f5…`).
Only the `resume.sh` block moves (`c325718c…` → `e0b5eed5…`), as `plan_blocks.py list` shows, and `plan_blocks.py check` passes for tasks 0, 9, 10 and 11.
- `rev45-to-rev46.diff`: the plan file diff.
- `producer-gate-rev46.out`: `orphans=0 classified=56 stale=0` against `baseline-substep2b-rev45.txt` (resume.sh is not a task runner, so no row moves).

## The finding (walking the NEXT token's handoff, after master's rev45 carry 231805)

- `w45resume-control.sh` / `.out`: rev45's Step 0′ (`resume.sh` `c325718c…`) from a mirror of the real `s2b-runners-V1jS1t` on the rev45 lock publishes a new directory with 32 carried lines and NO `task-10.done`; the sealed controller `run-task.sh 11` from it then STOPs `STOP-controller-task-11 line=16` (its predecessor check: `task-10.done` rc=0 in the directory it runs from) before extracting Task 11.
rev45's walks ran Step 0′ and the Task 11 body separately and never the controller between them.

## rev46 walked (`w46.sh` / `w46.out`)

- YES: rev46 Step 0′ from a mirror of the real `s2b-runners-V1jS1t` (evidence home a full APFS clone) publishes a new directory with 43 carried lines, byte-equal, including all eleven Task 10 receipts (`task-10.done` rc=0).
The sealed controller `run-task.sh 11` from it passes the predecessor check, extracts and proves Task 11 (`proof-11.tail` rc=0), and the runner's prologue writes its record; the body then STOPs at its helpers line (runner line 26) because the walk tampered `cells.py` in the clone on purpose, so no results directory is written into the real MAIN.
The Task 11 body itself (unchanged since rev45) was walked end to end in `results/rev45-walks/`.
- NO, each in pre-flight with nothing published and the pointer unchanged: `task-10.done` rc=1 → `task-10-not-done`; the controller's `task-10.exit` copy differing → `task-10-copy-mismatch-task-10.exit`; `task-10.sh` altered → `task-10-sh-altered`; a second token directory holding the same Task 10 records → `task-10-record-owner-2`.
- Regression: a previous directory with no Task 10 records resumes as before (32 carried lines, no `task-10.done`).
- No walk directory is left in the evidence root; the real pointer still names `s2b-runners-V1jS1t`.
