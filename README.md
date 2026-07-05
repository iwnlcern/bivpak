# Bivpak

Portable development container — a downloadable, offline CLI that packs any directory
(nested git repos, uncommitted state, and coding-agent sessions) into a single portable
`.bvpk` image restorable and resumable on any machine.

- **Command:** `biv` (`biv pack` / `biv open` / `biv list` / `biv info`)
- **Archive extension:** `.bvpk`
- **Ignore file:** `.bivignore`

## This repo

Product **code only**. The governing design-of-record + charter live in the sibling docs
repo (`../pdc`): the spec, the c1 design locks, the c1.5/c2r2 addenda, and `ROADMAP.md`.
Where this code and the sealed design differ, the design governs — changes to the
design-of-record are made only in the docs repo by the high-level design teams.

Built by lower-level orchestrator-team instances against the sealed design-of-record.
**First scope: ROADMAP Step 2** — core library + `manifest.json` read/write + scanner walk
+ the golden round-trip harness.
