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

rev33 baseline (2026-09-25, for impl-11): `baseline-substep2b-rev33.txt` b09f297da9962b1c559cd82d313d444e2cd1b261338d4c4550413dd3ef44d0c3 adds 13 classified rows for Task 8b (the three `commits.c8*.txt` written through `$LABEL`, the three `receipts/c8*` written through `$O`) and Task 9 (the preserved attempt's `H0.txt` and `helpers.verify-9.txt`, five `H9/H` container copy-outs), and drops none of the 25.
Discriminator run on rev35 (`6781eae1…`) with rev35's extractor `8331c944…`, each isolating its predicate:
- the rev33 baseline: rc 0 — 0 orphans, 38 classified, 0 stale;
- the committed 25-row baseline: rc 1 — exactly those 13 rows as ORPHAN;
- rev35 plus one read of an unwritten `$EVID/receipts/c8X-unwritten.txt`: rc 1 — that one ORPHAN.

rev36 baseline (2026-09-25, for the successor of impl-11): `baseline-substep2b-rev36.txt` 06ff5dfffcd467be3322aafe14c2a3f1c437cef042f3543e941f85ca5181c215 adds 2 classified rows to the rev33 baseline: Task 9's `BLEG` writes its argument (`> "$1"` inside the function), which the gate cannot see — `work/B-leg.names` before the preservation and `work/B-leg.post` after it.
Discriminator run on rev36 (`e87c999a…`) with its extractor `8331c944…`, each isolating its predicate:
- the rev36 baseline: rc 0 — 0 orphans, 40 classified, 0 stale;
- the rev33 baseline: rc 1 — exactly those 2 rows as ORPHAN;
- rev36 plus one read of an unwritten `$EVID/H/skipset-linux-unwritten.txt`: rc 1 — that one ORPHAN.
