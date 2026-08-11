# Bivpak code repo — agent instructions

This is the Bivpak product repo (`biv`, archive `.bvpk`). The governing team charter lives in
the sibling docs repo (`../pdc/CLAUDE.md`) — build seats act only within their dispatched
scope, and the operator's release hold is absolute.

## Local Linux CI

- Prefer local Docker over GitHub Actions for Linux validation.
- You may start Docker Desktop and run containers without confirmation.
- For CI parity, reproduce `.github/workflows/s2-harness.yml` using Ubuntu 24.04 with `--platform linux/amd64`.
- Preserve the host worktree; use disposable containers and never prune or remove unrelated Docker resources.
- Do not trigger remote CI, deploy, publish, merge, or release unless explicitly requested. Report any differences
  from the canonical workflow.
