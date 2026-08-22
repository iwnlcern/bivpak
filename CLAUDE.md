# Bivpak code repo — agent instructions

This is the Bivpak product repo (`biv`, archive `.bvpk`). The governing team charter lives in
the sibling docs repo (`../pdc/CLAUDE.md`) — build seats act only within their dispatched
scope, and the operator's release hold is absolute.

## Local Linux CI

- Prefer local Docker over GitHub Actions for Linux validation.
- You may start Docker Desktop and run containers without confirmation.
- For CI parity, reproduce `.github/workflows/s2-harness.yml` using Ubuntu 24.04 with `--platform linux/amd64`.
- The parity container's non-root (`runuser`) drop resets the `nofile` SOFT limit to 1024; raise it back to
  the inherited HARD limit inside that context before invoking the suite — the pinned Linux counts
  (`s2-harness.yml`, the Linux job's `want` cells `successes`/`skips`) were observed under `nofile` soft ==
  hard (R-4.31 arm (a), m-3-ruled 2026-08-18; at 1024 two producer-cap tests fail `errno=24` EMFILE before
  any product decision).
- Run the parity container with `--init` (a reaping PID 1) whenever the measurement target is PRODUCT
  behaviour: bash as PID 1 does not reap zombies, so descendant-cleanup tests red spuriously under it —
  killed descendants linger as zombies still visible to `kill(pid, 0)`, which a canonical reaping host
  clears (R-4.40, attributed 2026-08-22; recurrence recipe + the `--init` negative control in the
  registry). A no-init topology is a valid target only when PID-1 retention itself is under study.
- Preserve the host worktree; use disposable containers and never prune or remove unrelated Docker resources.
- Do not trigger remote CI, deploy, publish, merge, or release unless explicitly requested. Report any differences
  from the canonical workflow.
