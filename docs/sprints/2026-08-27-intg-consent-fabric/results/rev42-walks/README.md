# rev42 walks (sub-step 2b, Task 10 only)

rev42 folds impl-15's Task 10 STOP (`STOP-task-10 line=73`: the repository is PUBLIC, the gate required PRIVATE; nothing pushed) under the operator's choice "2" (2026-09-27): keep the repository public and publish the branch.

- `gen42.py` produces rev42 from the rev41 blob at df0b928 (`0140f69e…`). Only the `task-10` block moves, as `plan_blocks.py list` shows, and `plan_blocks.py check` passes for tasks 0, 9, 10 and 11.
- `walk42.sh` → `walk42.out` runs the three new pieces verbatim from the rev42 block:
  - Step 0, preservation: runs on copies of the real failed-attempt files. YES moves them with a verified manifest, byte-equal to the originals; a second run is a no-op; with `task10-1` taken it uses `task10-2`. NO: a push receipt, a PR receipt, a symlinked file, and a symlinked `attempts/`.
  - Visibility: `gh` is faked. `PUBLIC` and `PRIVATE` pass; `INTERNAL`, lowercase `public` and empty STOP.
  - Exposure census: runs on the real candidate with a real `git ls-remote` (a read). YES passes. NO: a wrong B, a 25-commit range, a foreign author and a secret line in the patches — the last two hooked on `git log --format` and `git log -p` separately, so each reaches only its own line — plus a no-op hook control that passes.
- `producer-gate-rev42.out`: `orphans=0 classified=54 stale=0` against the unchanged rev41 baseline (`baseline-substep2b-rev41.txt`); rev42 adds no cross-task read.

Invalid run, recorded: the first exposure walk hooked every `git log`, so the secret-line NO case STOPped at the author check (the injected line also reached the author list). It was not an isolated control; the hook was narrowed to `git log -p` and the case re-run (`walk42.sh` as committed).
