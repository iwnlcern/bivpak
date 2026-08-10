# Targeted re-panel — C `b8083be` / B2 `20e56bc` (four folds + ADDENDUM-11)

Convened by `s4-floor.planner` per master's four-folds ruling (`234510`: M-4 AND round-trip lenses at the new exact SHAs).
Four read-only lenses over committed bytes (`git show "<sha>:<path>"`), never the working tree.
Heads: C `b8083be8529a97d1d3d5931a2c7b308335bbd09c` (writer), B2 `20e56bc4053d4a27c4b47b6dbff0fc02af1dcc13` (readers/adapters).
Governing design: ADDENDUM-11 at certified pdc rev11 blob `858d1ca` = SHA-256 `422d451b0c61…4fcb` (re-derived independently by two lenses and this seat).

## Verdicts

| Lens | Verdict | Findings |
|---|---|---|
| M-4 containment | **FAIL** | 2 fold-scope Major, 1 pre-existing Major, 3 Minor |
| Claude round-trip (B1) | **FAIL** | 1 Critical, 4 Major (one provenance-corrected, one design-level), 3 Minor |
| Codex round-trip + A11 conformance | PASS | 3 Minor (23-clause conformance table, one form-only deviation) |
| Tests / falsifier power | PASS | 5 Minor (all 11 FX-A11 keys have falsifying power) |

**Panel verdict: FAIL — the pair is NOT bar-ready; findings fold before any hand-up.**

## What HOLDS (verified, carries)

- A1 truncation closure holds: refusal branch `continue`s, later artifacts still harvested (both branches enumerated; regression test `test_adapter_claude_install.cpp:2543` has falsifying power).
- A2 PRIMARY-identity half correct in BOTH adapters, derived from all records before version-floor decisions, with powered falsifiers on both.
- B1 same-set invariant over PATHS proven as equality (one shared predicate `claude_staged_subtree_artifact`, single symbol, both directions, all four probe cases; `<id>/notes.txt` round-trips end-to-end).
- ADDENDUM-11 conformance: 23 clauses conform (writer join/duplicate/missing-join failure; canonical representative by kind; two closed states; membership/duplicate/type/empty/mixed-presence fail-closed; absent-state resolver BYTE-IDENTICAL to `0653fea`; per-row recovery with no fallback; consumers exactly the two re-collectors). The LLVM-22 portability delta preserves both closed states.
- 1+N scrub surface clean BY CONSTRUCTION: the sidecar never ships in an image (`.biv` pack-scanner-excluded, `scan.cpp:140-142`), no `verify_*` call takes sidecar bytes, and writer membership holds by construction (windows canonicalization matches `origin_spellings`).
- No containment reliance on the integrity cross-check (grep-verified; store_root pair independent of the sidecar).
- All 11 FX-A11 fixture keys exist and have falsifying power; production call-path binding holds (`stage_then_pack` drives real adapters; the one injected parser seam is bound through `pack` on both consumers).
- Mechanical (this seat): topology exact, single-commit heads, FOLD_SCOPE ⊇ actual deltas, A3 anchors match at `20e56bc`, stack merges conflict-free onto LOCAL main (`693ff5f`, `7addb73c`).

## GATING findings → FOLD (pair scope)

**F-1 [Critical, B1 lens #1] Staged-reader CONTENT gate not established by the writer — subagent `.jsonl`.**
`claude_code.cpp:481-499` requires the staged subagent transcript to parse to `sessionId == row.minted`; the installer never establishes it. A `{}` subagent body — the product's own collect-fixture shape (`test_adapter_claude_collect.cpp:176`) — stages under consent-NO, then re-pack hard-aborts `staged_identity_mismatch` (whole pack, exit 4). The B1 failure mode relocated from path class to content class. Spot-verified at bytes by the convener.

**F-2 [Major, B1 lens #2] Main staged transcript without `sessionId` aborts the pack.** `claude_code.cpp:435-438`; live collect deliberately supports id-less transcripts via filename-stem fallback (`claude_code.cpp:670`); install derives identity from names, stages happily, re-pack dies.

**F-3 [Major, B1 lens #3] Main staged transcript without body `version` aborts the pack.** `claude_code.cpp:439-443`; a live-status-supplied version passes the floor at install while the body lacks it; staged re-pack dies `missing_staged_version`.

**F-4 [Major, M-4 lens #1] Claude refused-row child-alias harvest gated on staged provenance.** `install.cpp:750-752`: a NON-staged version-refused row's subagent `agentId` alias never seeds the union; admitted branch (`:786-804`) has no such gate; an admitted sibling carrying the alias installs with the packer's agent id intact. The fold's regression test exercises only the staged branch. Spot-verified at bytes by the convener.

**F-5 [Major, M-4 lens #2] Codex child ARTIFACT-DERIVED identity of version-refused records never reaches the union.** `codex/install.cpp:454-476` inserts the record-level artifact-derived identity but never `identity_for_artifacts(child.artifacts, child.original_id)`; version-refused records exit at `:361-371` before `prepared_sessions`. Exact mirror of the claude class the fold closed; no codex test covers it. Spot-verified at bytes by the convener.

**F-6 [Major, B1 lens #5] Blast radius: every staged-reader refusal still aborts the ENTIRE pack** (`pack.cpp:544-547`) — unrelated sessions and the other adapter lost. Master's original B1 grant already offered per-session skip-and-warn as an alternative; with F-1..F-3 live, the whole-pack abort is load-bearing harm.

Fold invariant (governing all of F-1..F-3/F-6): **the staged reader must accept every workspace the writer can legally produce** — same-set over CONTENT, not only paths; refusals confined to genuine integrity violations (a PRESENT-and-mismatched id stays a refusal); blast-radius choice per master's original grant. The codex staged reader carries the same gate class (`codex.cpp:716-721`) — the fold must prove the codex mirror unreachable or align it symmetrically, with falsifiers.

## ROUTED UP (beyond pair scope)

**R-a [Major class, provenance CORRECTED by convener] WSL/windows-origin sidecar corridor.**
B1 lens #4 reported the reader rejecting the writer's own WSL-workspace sidecar (windows-spelled pair targets vs `target_path != source_root.generic_string()`, `rewrite_common.cpp:982`) as introduced-by-fold. Convener verification: **the check is byte-identical at `0653fea`** — the class is PRE-EXISTING for codex (sole sidecar consumer then); B2 widens the consumer set to claude. Deeper: for a windows-drive origin in a wsl-flavor workspace, `derive_pair_set` emits windows-spelled targets, so the ALL-pairs target check — and ADDENDUM-11's own PRESENT membership formula `(row.original_path, source_root.generic_string()) ∈ pair_set_applied` — appear unsatisfiable together: the certified contract may be unimplementable on that corridor. Target semantics are certified-contract territory (A11 clause "target mismatch fails") → **routes to m-2 via the orchestrator**, not a pair-local fold. Not on the operator's three exit legs (mac→mac, mac→linux, linux→mac); realism bounded, but round-trip hard-abort class members gate on master's word, not the pair's.

**R-b [Major, pre-existing, M-4 lens #4] Origin CHILD session ids reach the recipient's store as FILENAMES.** `install.cpp:198-206` keeps the image-relative subtree tail verbatim (`…/<installed>/subagents/<child.original_id>.jsonl`); all verify surfaces scan bytes, none scan destination paths. Pre-existing at C's parent, outside every fold delta; enshrined by tests. Candidate fix (rename subagent members to minted child ids — id_map already carries them) is a coherent writer+reader change beyond this fold's grant → **routes to master for register/gating disposition** (the standing rule: an origin-ID vector gates even when pre-existing — master's call).

**R-c [caveat, M-4 lens item 3c] Restore side has no `.biv` rejection** (`open.cpp:446-476`); a crafted image can plant a staging carrier into the workspace. Fails closed today on `foreign_staging_carrier` + parser gates + minted-id checks (all verified) — net effect denial of the recipient's own staging, no identity escape. Register as residual context.

## Non-gating (implementer discretion in the fold + disclosure)

- Tests lens #1: FX-A11-4 `target mismatch` SECTION is dead (pre-existing `:982` fires first) — replace with a target-valid, origin-absent value.
- Tests lens #2: FX-A11-8a/8b assert one field, not the key's byte identity — compare full second manifest/members.
- Tests lens #3: writer-side guards (`sessions.cpp:44-60`, `:78-89`) have no falsifier.
- Tests lens #4: pack-level refusals assert `detail` only — add `ErrKind`.
- A11 lens #1: writer re-derives the representative instead of calling `origin_spellings` (`sessions.cpp:35-51`) — outcome proven identical; fold to the call to restore by-construction structure.
- A11 lens #3: writer-side sidecar failure indistinguishable from filesystem error in the report (reason "error", empty detail).
- M-4 #3 residual (undecodable artifact's own ids unharvested + codex `break` shape at `:494-499`), #5 (`.meta.json` alias in orphan meta neither rewritten nor unioned; common case fails closed), #6 (rename `audited` local); B1 #6 (`never_collect` not enforced on staged path), #7 (`.meta.json` verify-hit drops session from round-trip), #8 (safe-but-unsupported-suffix asymmetry — register a residual line).
- A11 lens observation, binding on merge order: **C alone is not ADDENDUM-10-clean** (claude staged project key becomes destination-keyed only at B2) — C must never land without B2. Carried into the hand-up conditions.

## Disposition

FAIL → one bounded fold cycle on the pair under a fresh delegated token (F-1..F-6 + chosen non-gating items + falsifiers), R-a/R-b/R-c routed up in the companion SITREP, then a fresh targeted re-check of the fold delta (M-4 + round-trip lenses scoped to changed files; byte-identical files carry), then the paired hand-up.
