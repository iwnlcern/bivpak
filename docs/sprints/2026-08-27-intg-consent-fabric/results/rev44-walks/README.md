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
