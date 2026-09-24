# Producer gate — every runner read has an earlier writer

The seat's standing pre-token check, added 2026-09-24 after the impl-8 Task 9 STOP (`observer-unset-names.txt` and `llvm-manifest.txt` were read from rev1 and never written).
Master's 080734 proposed the check; the pair Planner cut it.

Usage: `python3 producer_gate.py <plan.md> <plan_blocks.py> baseline-substep2b.txt` — exit 0 means every literal `$EVID/…` / `$RUNNERS/…` read in the RUN tasks (0, 9, 10, 11, in execution order) has an earlier write; exit 1 prints each ORPHAN (and each STALE baseline row).
Writers it models: redirects, `tee`, `mkdir`, `mktemp -d`, `--output-junit`, `git worktree add`, `clone`, the last operand of `cp`/`mv`, same-line `for` loops, `$LABEL`/`$N`/`$T` expansion, the container's `$OUT` copied out to `$EVID/{H,B}`, the controller `run-task.sh`, and the code tasks' steps (Tasks 1–8) for reads in Task 9 and later.
Writers it cannot see are CLASSIFIED in `baseline-substep2b.txt`, one row each with its real writer, or named in the script's `ALLOW` table; both are printed and never pass silently.
Templated reads (a name that continues with a variable) are skipped.

Discriminator run (2026-09-24), each isolating its predicate:
- rev28 (`ccb63bcf…`): rc 1 — ORPHAN `observer-unset-names.txt`, ORPHAN `llvm-manifest.txt` (the real defect), nothing else;
- rev29 (`6ef818b3…`): rc 0 — 0 orphans, 25 classified, 0 stale;
- rev29 with only the names producer removed: rc 1 — that one file;
- rev29 with only the manifest producer removed: rc 1 — the source slice and the manifest.

Digests: `producer_gate.py` 93c30a90235067cf63575b4dcea322222a8862952395040bb44d1f3430122c4c; `baseline-substep2b.txt` 8153bcf8ebd247143746435f6244b0113424fd733b3d1fc7d68d66cd3dfc79e7.
