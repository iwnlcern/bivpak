# Slice B2 team-of-5 adversarial panel — record of record

**Target:** PR #23, branch `s4-floor/b2-torn-tail`, exact head
`54a6c54f9d12874123bb520b2598f1086931f70f`, parent `ec9a2db2cfe55191f99efbcf12902a79d99e159e`
(one commit, 13 authorized paths). Subject: `feat(pack): collect torn tails and staged sidecars`.
**Method:** five read-only lenses over committed blobs at the exact SHA (never the working
tree); planner re-verified load-bearing claims at the SHA (both Criticals read directly;
A3 anchors recomputed; topology/scope/fences).
**Aggregate verdict:** MUST-FIX (two confirmed Criticals).

## Per-lens verdicts
- security: must-fix (1 Critical — I-1 upgraded on cross-lens verification, 2 Important)
- correctness: must-fix (2 Critical, both reproduced by COMPILING+RUNNING the functions; 1 Important; refuted X-1/X-4 to Minor)
- tests: must-fix (2 Critical, 5 Important)
- idiom: must-fix (6 Important, 7 Minor; + out-of-lens X-1..X-4)
- performance: approve (3 Important efficiency, 2 Minor; probed the real 1.8 GB store)

## Confirmed blockers (folded to implementer)

| ID | Sev | Lens consensus | Site @ SHA | One-line |
|---|---|---|---|---|
| BL2-1 | Critical | tests C2 + security C-1 + correctness C1 | claude_code/install.cpp:178-182, :684-703 | `never_rewrite` (DEFAULT arm, any non-.jsonl/.txt member) written to host store un-rewritten AND un-scanned → origin path + session id leak; new test seals it |
| BL2-2 | Critical | security I-2 + correctness C2 (ran it) | adapter.hpp:216-237, :315-338 | `.txt` verifier reuses rewriter's `boundary_ok` → tautological; 4 concrete leaks incl. ripgrep output |
| BL2-3 | Important | security I-3 + correctness I3 | adapter.hpp:377; branch-3 resize | zero-byte `.jsonl` → session un-installable; A3.3 can manufacture one |
| BL2-4 | Important (AUTHORITY, held) | correctness I4 | codex/install.cpp:494-504; claude:705-720 | origin-leak refusal radius narrowed whole-set → per-session without authority |
| BL2-6 | Important (tests) | tests C1/I3/I4/I5/I6/I7 | collect + install tests | vacuous interior-segment controls (live==false); missing falsifiers |
| BL2-7 | Important (idiom) | idiom I-1/I-2/X-2 | claude_code.cpp:335-430 ≡ codex.cpp:481-576; adapter.hpp:180-388 | 96-line byte-identical sidecar parser for a core-owned doc (rename a writer key → silent staged-session loss); 208-line rewrite API in root header past the swap guard |

BL2-5 (idiom X-1 assert-stripped deref + X-4 unchecked find) — REGRADED to non-blocking
hardening: correctness traced the establishing invariant at the bytes and refuted both as
live defects; security concurred (M-4/M-5 Minor). Recommended `.value()`/`.at()` or
carry-forward as the claude leg does.

## Routed above the pair (companion SITREP to orchestrator)
- BL2-4 authority: per-session vs whole-set refusal radius for the origin-leak class (dispatch authorized per-session only for `undecodable_line`).
- fence-2 caveat: `staged` rekey privilege derives from image-controlled `locator`/`discovery_tier` read without enum validation in `manifest.cpp` (fence-2 OUT) — crafted `.bvpk` declares its own rekey privilege.
- linkage: BL2-1/BL2-2 are the same origin-disclosure family as slice C's master-held ROUTED-3 (keep resolutions consistent).

## Fix-shape note (correctness, load-bearing)
"Restore the old `verify_scan` call" is NOT the BL2-1 fix — base was over-strict (a
pretty-printed multi-line `.meta.json` hit the `decoded=false` auto-refuse arm). Correct
fix: a whole-document raw origin scan (`count_hits_bytes`, no line-structure) for
`never_rewrite`, and make the `.txt` verifier count bare `matches_at` without `boundary_ok`.
BL2-1 and BL2-2 are one defect class — re-establish a single fail-closed origin-scan floor
across all three handling arms, not two separate patches.

## Cross-lens conflicts resolved at the bytes
- perf's prior-slice unreachable-Critical error NOT repeated (real-store probe; approve).
- X-1 (assert-stripped deref) and X-4 (unchecked find): idiom raised, correctness REFUTED as live defects by tracing the invariant; regraded Minor/hardening.
- Both Criticals independently reproduced by execution (correctness compiled+ran the verifiers) and re-read by the planner at the bytes.

## Checked-clean (strong, evidenced across lenses)
Torn-tail four-branch structure exhaustive/mutually-exclusive; T = segment after last LF,
byte-exact retained prefix, `bytes==len(T)` exact; branch-3 liveness rides B1's real
derivation (not hardcoded); no TOCTOU (fstat-once + pread); re-pack identity handling
GENUINELY closed (the Critical + 2 Important the implementer's own review closed reproduce
as closed); rekey-restricted-to-staged covers every site; `missing_staged_version` fails
closed before any schema-1 byte on both legs; CANON-2.6 reader symlink/TOCTOU fail-closed;
`.txt` excluded from JSONL rule; CRLF safe; A3 both anchors recaptured and matching the
committed blobs (recomputed independently by planner and tests lens).

## Fold discipline / re-review owed
FOLD_SCOPE before any edit; one-commit law; A3 re-fires if either anchored collect file is
touched again; because BL2-1/BL2-2 change install-time verify semantics (security-bearing),
the replacement head owes a TARGETED re-panel on the rewrite/verify surface (security +
correctness + tests on the fold delta), not merely the planner's targeted re-check.
Merge/release the operator's; release hold ABSOLUTE.
