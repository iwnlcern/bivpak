# Bivpak

Portable development container — a downloadable, offline CLI that packs a directory
**and its coding-agent sessions** into a single portable `.bvpk` image, restorable and
resumable on any machine.

- **Command:** `biv` (`biv pack` / `biv open` / `biv list` / `biv info`)
- **Archive extension:** `.bvpk`
- **Ignore file:** `.bivignore`

> **⚠ Not shipped yet: nested git repos and uncommitted state.** These are the product's
> eventual scope (**ROADMAP Step 4** — the git engine) and are **not implemented today**:
> there is no git subsystem in `src/`. **`biv pack` refuses outright on any directory
> containing a `.git` entry** (typed `RepoDiscoveredUnsupported`, `src/core/scan/scan.cpp`)
> — a deliberate fail-closed refusal, so repo state is never silently dropped or
> half-captured. **What works today:** plain / no-git directories, plus real Claude Code
> and Codex session portability (pack → move → open → resume with history intact).

## This repo

Product **code only**. The governing design-of-record + charter live in the sibling docs
repo (`../pdc`): the spec, the c1 design locks, the c1.5/c2r2 addenda, and `ROADMAP.md`.
Where this code and the sealed design differ, the design governs — changes to the
design-of-record are made only in the docs repo by the high-level design teams.

Built by lower-level orchestrator-team instances against the sealed design-of-record.
**First scope: ROADMAP Step 2** — core library + `manifest.json` read/write + scanner walk
+ the golden round-trip harness.
