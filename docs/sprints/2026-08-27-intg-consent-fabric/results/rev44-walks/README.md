# rev44 walk records (plan 2b, MUST-2B-57)

- `gen44.py` produces rev44 (`7d55f0b8…`) from the rev43 blob at e8b3ab2 (`096e47b4…`).
Only the `task-10` block moves, as `plan_blocks.py list` shows, and `plan_blocks.py check` passes for tasks 0, 9, 10 and 11.
- `rev43-to-rev44.diff`: `git diff` of the plan file, rev43 → rev44.
- `producer-gate-rev44.out`: `orphans=0 classified=54 stale=0` against the unchanged rev41 baseline.
- `walk44.sh` extracts Task 10's `URL=`/`REPO=` line and visibility line from rev44 and, as the control, from rev43, and runs each on the real candidate; `walk44.out` is one recorded run.

## MUST-2B-57 (host-qualified gh repository)

- rev44 with no `GH_HOST`: PUBLIC.
- rev44 with `GH_HOST=gh-host-control.invalid`: PUBLIC; the host-qualified repository reaches github.com.
- Control, rev43's `REPO=iwnlcern/bivpak` under the same `GH_HOST`: `error connecting to gh-host-control.invalid`, STOP at the visibility line; the unqualified form follows the injected host.
- rev44 with both `GH_HOST` and `GH_REPO` injected: PUBLIC.
- Static: one `REPO=` assignment in Task 10, host-qualified; zero `gh repo|pr|api` calls in Task 10 not naming `"$REPO"`.
- `gh pr create` was not run: it is a write, and its `--dry-run` help says it "may still push git changes".
Its `--repo` flag takes `[HOST/]OWNER/REPO` (gh 2.97.0 help), the same resolver form as the walked `repo view`.
- No `GH_DEBUG` was used, so no request header was printed; no token environment variable was set (names checked only).

## Task 10 GO walks (after master's carry 181059)

- `t-oracle-replay.txt`: the plan's T-ORACLE prefix in scratch clones against synthetic carries at `7d55f0b8`: YES, `carry-to` NO and stale-digest NO (run before the digest word).
After the carry, the same prefix ran against the REAL rewritten `s2b-runners-j6w4EX/t-oracle.txt` (predecessor `t-oracle.prev-20260927-202507.txt`): `t-oracle OK`, rc 0, one receipt in a scratch EVID.
- `w44resume.sh` / `w44resume.out`: Step 0′ (`resume.sh`, `c325718c…`) from a mirror of the real `s2b-runners-j6w4EX`, unedited, with the rev44 lock and token impl-16.
It publishes one new directory with 32 carried lines (`t-oracle.txt` and `task-10-go.txt` included), all byte-equal, and no `task-10` records; the predecessor oracle STOPs `t-oracle-stale` without publishing.
- `go-gate.sh`: Task 10's derived lines 52–78 (the GO and owner-set gate) with the prologue's `set -u`, `STOP` and `PIPEOK`, run against the real runners directory after `task-10-go.txt` was re-cited to `SITREP-pair-planner-20260927-202731.md`: `GO-GATE-OK`, rc 0.
NO: pointing `task-10-go.txt` at `SITREP-pair-planner-20260927-043806.md` (INDEX-listed, no GO lines) STOPs at gate line 10 (plan line 57).
A first gate run omitted the prologue's `PIPEOK`, so six calls failed with "command not found"; that run was void and is superseded.
