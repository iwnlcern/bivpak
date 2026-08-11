# Targeted re-check — C `b8083be` / B2 `355aad6` (two-Critical fold)

Three read-only lenses over committed bytes, scoped to the fold delta `8b12b25 → 355aad6` (10 paths).
Convener re-ran every load-bearing measurement against the operator's real stores.

| Lens | Verdict |
|---|---|
| Containment (alias minting) | **FAIL** — 2 CRITICAL, 2 MAJOR, 2 MINOR |
| Codex identity semantics | **FAIL** — 1 CRITICAL, 2 HIGH, 2 MEDIUM |
| Tests / falsifier power | **FAIL** — 1 HIGH blocking, 3 MEDIUM, 3 LOW |

**Panel verdict: FAIL. A LIVE containment leak is present — the pair must not hand up.**

## L-1 [CRITICAL — LIVE M-4 LEAK, convener-reproduced in the operator's own data]

An origin `agentId` carried **only by the main transcript** is never harvested, never paired, and is written
verbatim into the recipient's store with a clean `origin_id_hits == 0`.

Every link verified at `355aad6`:
- harvest gate `install.cpp:900-903` fires only for `subagent_jsonl_artifact(...) || child_attributed_artifact(...)`;
- `subagent_jsonl_artifact` (`:373-381`) requires a slash after `agents/claude-code/`, so the main artifact
  `agents/claude-code/<sid>.jsonl` is excluded; `child_attributed_artifact` never matches the main transcript;
- `agentId` is NOT in `message_uuid_field` (`:269-272`), so the message-uuid harvest cannot see it either.
⇒ not in `image_origin_id_set` (verify blind) **and** no rewrite pair (bytes untouched).

**Measured, twice, independently.** Lens: 30 main transcripts carry `agentId`; session `540453ff…` carries 4
values appearing in no subagent file and matching no subagent stem. Convener reproduction: **30 main
transcripts carry `agentId` (recursive walk), exactly 1 session orphan-carrying 4 values — same session,
same values.** (The convener's first scan read only TOP-LEVEL keys and found zero — a decode-level mismatch
against a nested field. Recorded because it nearly produced a false refutation of a true Critical.)

**This fold owns it.** The gate code is unchanged, but that session ALSO carries harvestable unattributed
aliases, so at PRIOR it hit `verify_scan` and was refused — nothing was written. R-1's minting makes the
session install, converting a latent leak into a live one on the consent-YES path.

Fix: widen the harvest to every jsonl destination (the main transcript included), so that every `agentId`
is either paired or refused. The R-1 test cannot catch this — its alias is planted inside the gate.

## L-2 [CRITICAL] R-1's refusal survives cross-session: global union, per-session pairs
`image_origin_id_set` is image-wide (`install.cpp:944-947`, including refused sessions) but `ids` is
per-session (`:955-967`). An alias owned by session A appearing in session B's bytes is in the union with no
pair for B ⇒ B refused `verify-hits`/`origin_id` — the original Critical relocated from same-session to
cross-session. Encoded as expected in the new test (session 1 asserted refused). Measured: 3 alias/session
pairs in one real project scope. **R-1 is therefore narrowed, not closed, for any image with >1 session.**

## L-3 [MAJOR] Image-controlled alias keys drive an unbounded substring rewrite
Id pairs use `replace_all` (`rewrite_common.cpp:328-337`) with NO boundary check, unlike the path variant's
`path_replacement_boundary_ok` (`:358-368`), and `collect_child_identity_object` (`install.cpp:468-479`)
accepts ANY non-empty string under `agentId`. An image carrying `"agentId":"e"` rewrites every `e` in the
recipient's transcript to a 36-char UUID — mass corruption that still passes `verify_scan`. Benign only by
luck of shape (every real `agentId` is ≥17 chars; 60029 at exactly 17). PRIOR paired only child-attributed
aliases; this fold extends the exposure to every harvested alias. Needs a shape guard before minting.

## X-1 [CRITICAL, PRE-EXISTING + branch-coupled] Three-level codex chains: silent drop, one-level gates
Convener-verified: with R←P←C, both P and C enter `child_ids`; the emit loop (`codex.cpp:1293-1298`) skips
both; `session_for` (`:452-460`) takes only DIRECT children and does not recurse, so `children_by_parent[P]`
is never consumed. **C's rollout is never packed, with no warning** — the warning vocabulary
(`CompressedRolloutSkipped`, `SessionDuplicateStore`, `StagedSessionVersionMissing`, db warnings) has no
entry for it. The grouping block is byte-identical at BASE, so the DROP is pre-existing.

**What the fold owns:** its new identity gates are written to exactly the depth that drop guarantees —
`installed_thread_id` is the IMMEDIATE parent (`install.cpp:565-568`, reader `codex.cpp:775-777`); there is
no mapped-ROOT concept in the file. So whoever fixes the silent drop immediately gets
`staged_identity_mismatch` on every three-level leaf, and a WHOLE-PACK abort on the staged side. **The two
defects are coupled and must move together.**

Measured (convener): of 940 real rollouts, `session_id` ALWAYS names the thread ROOT — 145 self-rooted,
635 two-level (root == parent, which is why they look like "session_id == parent"), **7 three-level** where
root ≠ immediate parent. Shapes 1 and 2 (780) ARE genuinely fixed by this fold and round-trip end to end.

## X-2 [HIGH → downgraded by measurement] the `id ← session_id` fallback was removed
`codex.cpp:248-250` at NEW reads `facts.id` from `payload.id` only; PRIOR and BASE had a `session_id`
fallback. Collect then silently `continue`s on a missing id. The lens flagged this as silent data loss and
noted the convener's ground truth summed to 787 against a 930 corpus.
**Convener reconciliation (the lens was right to challenge it): 940 files = 787 with both keys + 153 with
`id` only + ZERO with `session_id` but no `id` + ZERO with neither.** The "143 gap" was the `id`-only class;
the convener had presented a breakdown of the both-present subset as if it covered the corpus. So the
removal drops NOTHING on real data. What survives is narrower: an unscoped, silent narrowing — make it
warned or justify it.

## X-3 [HIGH] Staged-reader refusals are whole-pack aborts; the writer's are row-scoped
`codex.cpp:746-748`/`:778-780` return `std::unexpected` → `pack.cpp:544-546` fails the entire pack, while
the writer refuses per row (`install.cpp:589-592`). Same predicate class, opposite blast radius. Reachable
inside the fold's own new code (direct + nested `parent_thread_id` disagreeing). Make the reader row-scoped.

## Also fold
- **T-1** `never_collect_path` in the staged branch (`claude_code.cpp:475`) has ZERO falsifying coverage —
  the `.DS_Store` fixture is caught by the sibling arm of the same `||`; delete the clause and everything
  passes. It is load-bearing (`history.jsonl`, `memory/*.jsonl`, `shell-snapshots/*.txt` would pack).
- **T-2** The deleted `reject("unknown-subtree-class")` case leaves "regular file, plausible location,
  unknown class, not in never_collect → warn-and-skip" uncovered; the enclosing test title is now stale.
- **T-3** Nested child attribution rides `ChildArtifactMatcher`'s filename-stem fallback, not the explicit
  map (which only matches flat spellings) — the same-stem-under-two-workflows collision is untested.
- **T-4** R-1's absence assertion does not constrain the REPLACEMENT (an empty string or a duplicate of the
  session id would pass); the file's `uuid_strings`/`disjoint` helpers close it cheaply.
- **C-1** Codex dangling-parent fixtures still use a self-valued `session_id`, which the measured semantics
  say cannot occur; three sibling fixtures were corrected in this fold and these were missed.
- **M-1** Mint-before-attribute precedence: the minted pair wins and a later child-attributed pair is inert,
  so the recipient loses the nested-reference → installed-child link (no leak, but a lost linkage).
- **M-2** A non-string `version` is now tolerated and left in place, so a consent-NO transcript can carry two
  version spellings, one invalid. Deliberate and tested; residual.

## ROUTE UP
- **X-1** (three-level: pre-existing silent drop + one-level gates) — the fix changes collect semantics and
  manifest child cardinality; beyond a bounded fold. R-4.15 precedent.
- **R-4.15 materialization** — minting does not change destination FILENAMES, so `subagents/<origin_child_id>.jsonl`
  still lands in the recipient's store named with the origin child id, and `verify_scan` never inspects
  paths. The population this fold unblocks (1124/1124 nested) is exactly the population whose subagent
  filenames ARE origin ids. **R-4.15 goes latent → LIVE the moment B2 lands** — master needs this for the
  merge decision.

## What HOLDS
Minted values are pure `uuid4()` CSPRNG, not derived from origin ids/paths — nothing to reverse. **The A9
boundary held**: `child_alias_ids` never reaches `result.id_map` (`:1084-1087` uses `child_ids` only), so no
m-2 authority is implicated. Version injection is now consent-NO only, uses the RECIPIENT's
`caps.agent_version()`, and is floor-checked before insert. R-5 typed-cause precedence is real (asserts
`origin_path_hits > 0` alongside the typed reason, proving the suppressed check fired). R-a's symlink and
non-regular refusals are byte-identical and still refuse; the skip is entry-scoped; the warning stays on the
packer's own stdout. Codex shapes 1 and 2 round-trip end to end — the PRIOR false-premise refusal is
genuinely fixed for 780 of 940 rollouts. Both A3 anchors match and the `e3.py` delta is exactly two literals.
Topology: one commit atop byte-identical C, 17-path cumulative, fold delta == the 10 declared paths.

## Disposition
FAIL → fold L-1 (live leak, blocking), L-2, L-3, X-2, X-3, T-1..T-4, C-1, M-1; route X-1 and the R-4.15
materialization. No hand-up while a live containment leak stands.
