# Slice C team-of-5 adversarial panel — record of record

**Target:** PR #22, branch `s4-floor/c-consent-no-carrier`, exact head
`eadc88f89cd0eeeea0b9e5e0eb8a1577bed0d67e`, parent `798526c5c68c4251cc088bcf922fbee798ed8b79`
(one commit, 20 authorized paths).
**Method:** five read-only lenses over committed blobs at the exact SHA (never the working
tree); planner re-ran every load-bearing mechanical claim at the SHA before folding.
**Aggregate verdict:** MUST-FIX.

## Per-lens verdicts
- performance: must-fix (2 Critical — BOTH REJECTED on reachability by the planner)
- security: must-fix (1 Critical, 4 Important)
- tests: must-fix (2 Critical — 1 CONFIRMED+escalated, 1 REJECTED against the design)
- idiom: must-fix (1 Important load-bearing, 4 more Important, 8 Minor)
- correctness: must-fix (0 Critical, 4 Important, 6 Minor)

## Confirmed blockers (folded in-universe to the implementer as BL-1..BL-7)

| ID | Sev | Lens consensus | File:line @ SHA | One-line |
|---|---|---|---|---|
| BL-1 | Critical | security C1 | open.cpp (no `.biv` filter); sessions.cpp:489-492 | crafted image pre-plants sidecar path; staged bytes left beside foreign manifest, no rollback/signal |
| BL-2 | Critical | tests C1 + security I5 + idiom | scenarios *.json (`tree:false`); scenario.py:662 | E2E tree assertion DISABLED not adjusted → no proof consent-no writes only under `.biv/agents`; also exceeds A6 part(2) grant bound |
| BL-3 | Important | idiom I1 + security I2 + correctness #2 | sessions.cpp:495-507 | sidecar-failure handler labels containment refusal as ambient errno; test seals the wrong EEXIST=error expectation |
| BL-4 | Important | correctness #1 + security I4 | sessions.cpp:81-96 | `pair_set_applied` records unapplied pairs / omits applied ones for non-posix flavors |
| BL-5 | Important | correctness #3 | sessions.cpp:503-505 | same flip clobbers `row.detail`, destroying non-UTF-8 disclosure on publish failure |
| BL-6 | Important | correctness #4 + tests I4 | claude_code/install.cpp:460-466 | project-key cap is cohort-wide under consent-no; one over-long image path fails the whole claude leg |
| BL-7 | Important | tests I1/I2/I3 | test_sessions.cpp:1022+, configure_staged, caveats | host-store sampled not swept; no core-side no-activation kill test; multi-artifact disclosure completeness unasserted |

## Routed above the pair (companion SITREP to orchestrator)
- **A6 part (2) grant-bound breach** — BL-2 disabled the assertion vs the granted "adjust only for the additive carrier" bound. Fix lands inside the original bound.
- **Out-of-universe half of BL-1** — extract-side `.biv` refusal in `open.cpp` (defense in depth; also covers the symlink-named `.biv` the dir-only pack guard misses).
- **Contract question** — claude staged tree keyed to the packer ORIGIN path leaks the absolute origin path as a directory name into the recipient's workspace (git-committable) and is arguably not install-ready at destination; sealed layout (`test_adapter_claude_install.cpp:619-676`). Options a/b/c in the SITREP; HELD at the pair.

## Cross-lens conflicts resolved at the bytes (not by vote)
- **perf C1 (repeat-run guaranteed EEXIST) + C2 (cross-run duplicate growth): REJECTED.** `execute_archive` (open.cpp:610-664) refuses or renames on an existing dest and builds in a `.partial` dir renamed into a fresh `dest`; no second `biv open` reuses a populated workspace. Mechanics accurate, reachability false. The crafted-IMAGE route is real (BL-1).
- **tests C2 (partial-success sidecar "before all legs succeed"): REJECTED.** Design §3 (design doc lines 79/86/88): sidecar written once after ALL install calls return, aggregating only succeeded staging; a failed agent contributes nothing. Code + `test_sessions.cpp:1229` match the contract; the SITREP's phrasing was imprecise.
- **perf silent-walk-truncation (as stated): REJECTED; narrow increment-failure variant survives as a Minor** (correctness #7). `increment(error)` runs unconditionally and clears on success, so a single `is_regular_file` failure does not end the walk.
- **stale tripwire needle** (idiom 12 / tests M6): occurrence facts confirmed (needle patches the containment-probe occurrence, not the write side), but NO kill-power lost — the drift tripwire hashes only anchored collect files, never `install.cpp`. Hygiene fix.

## Notable checked-clean (strong, verified)
No host-store mutation on any consent-no branch; no traversal via project key or packed
paths; symlink interposition on the carrier refused (O_NOFOLLOW → containment); sidecar
JSON injection-safe; sidecar multiplicity ("exactly one") genuinely asserted twice;
host-store-unchanged is a whole-store byte sweep at E2E and at adapter level; `live_at_pack`
default flip safe; both schema blob literals verified by `git hash-object` at the SHA
(`4f842442…`, `7ac7de89…`); `-Wswitch` exhaustiveness holds across all updated switches.

## Fold discipline
Any byte change preserves the one-commit law and required subject; refresh exact-head
evidence (focused RED→GREEN for new tests; containment-classification receipt for BL-3);
rerun focused + locally applicable suite + the standing local Ubuntu 24.04 amd64 Docker
suite; re-publish under the standing disposition. Planner runs a targeted re-check sized to
the fold delta, not a full re-panel unless blast radius changes. Merge/release the
operator's alone; release hold ABSOLUTE.
