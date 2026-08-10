# Targeted re-check — C `b8083be` / B2 `2b5675a` (re-panel-failure fold)

Convened by `s4-floor.planner` on the implementer's REVIEW-FOLD (`152847`), per the orchestrator's rulings (`153853`).
Three read-only lenses over committed bytes at the LOCAL head (objects reachable from this seat), scoped to the fold delta
`20e56bc → 2b5675a` = 8 paths. Files unchanged since `20e56bc` carry their prior verdicts.

## Verdicts

| Lens | Verdict | Live after adjudication |
|---|---|---|
| M-4 containment (child/alias) | FAIL | F-A Major; F-B **REFUTED by E1 scout**; F-C/D/F Minor |
| Content same-set / round-trip | FAIL | #1 Major (codex mirror), #3 Major (version drop); #2 **REFUTED**; #4/#5 Minor |
| Tests / falsifier power | FAIL | #1 HIGH blocking (tests-only); #2/#3/#4 Minor |

**Panel verdict: FAIL — one more bounded fold. No hand-up on a failed panel.**

## E1 SCOUT — the decisive instrument this round (convener-run, real store)

Two lenses independently raised, as a Major, that the fold's NEW writer-establishment guard rests on an
unvalidated format assumption ("a subagent transcript's `sessionId` is the PARENT's"), with the failure
mode "if real Claude Code writes its own id, EVERY session with subagents is refused on install." Both
recommended real-data evidence before shipping. Rather than fold on the argument, the convener measured
the real store (`~/.claude/projects`, read-only, identity fields only — no conversation content read):

```
TOTAL real subagent transcripts .................. 1695
  sessionId == PARENT session .................... 1657   (97.8%)
  sessionId ABSENT ...............................   38   ( 2.2%)
  sessionId == OWN id ............................    0
  sessionId == anything else .....................    0
layout: subagents/<deeper>/*.jsonl ............... 1124   (66%)
        subagents/*.jsonl (flat) .................  571
```

**Adjudication: the guard's assumption is CORRECT on real data.** Both observed classes pass it —
`== parent` maps through rewrite to the installed parent id, and `absent` no-ops the guard
(`install.cpp:295-298`). M-4 **F-B** and round-trip **#2** are REFUTED on their reachability half and do
NOT gate. Had the pair "fixed" the guard on the lenses' word, it would have broken a correct control.
(First measurement of this attempted a flat `<sess>/subagents/` layout, mis-bucketed 1099 nested files, and
produced a false alarm; reconciled by depth before any claim was made. A scout figure that cannot be
reconciled is not evidence.)

**Second scout result, verified at the bytes:** 66% of real subagent transcripts are NESTED
(`subagents/workflows/<wf>/agent-*.jsonl`). Both the writer guard (`install.cpp:305-312`) and the reader
gate (`claude_code.cpp:481-482`) use PREFIX semantics on `subagents/`, so both cover the nested layout
identically — the dominant real-world shape is symmetric. M-4 F-C is therefore narrowed to non-`subagents/`
subtree directories only (see below).

## GATING findings → FOLD

**G-1 [HIGH, tests-only — convener-confirmed at bytes] The F-3/F-6 sibling falsifier is absent; `continue`→`break` survives the suite.**
The skip is a `continue` in the per-row loop (`claude_code.cpp:441`, `codex.cpp:724`), but the fixture
(`test_pack.cpp:1734`) gives the FAILING adapter exactly one staged row and puts the survivor in the OTHER
adapter, asserting `agent_sessions.size() == 1U`. The other adapter is a separate `collect()` call
(`pack.cpp:545`), so mutating the `continue` to `break`/early-return keeps the suite GREEN. This is the
A1 break-vs-continue shape this run has already paid for once, and it is exactly master's stated bar
("the test must assert the SIBLING survives"). Fix: a second version-complete staged row on the SAME
adapter, asserting two survivors. No production change.

**G-2 [Major] The codex staged-reader mirror was neither aligned nor proven unreachable — the fold's explicit mandate.**
`codex.cpp:716-721`/`:743-749` still hard-refuse a PRESENT mismatched identity, and the only codex
install-side change in the delta is the union enrichment at `:467-468` (a needle feed, not a gate).
`inspect_rollout_head` reads both `payload.id` and `payload.session_id` while collect keys on `id` only
(`codex.cpp:1200-1216`), so a head carrying `id: A` + `session_id: B` (B≠A) stages with B untouched and
then aborts the ENTIRE pack on re-pack (`pack.cpp:544-547`) — the very blast radius this fold was convened
to remove. The `090631` token required "prove the codex mirror unreachable for legal writer output OR
align it symmetrically"; neither was done. Do one or the other, with evidence.

**G-3 [Major] Writer-accepts / reader-DROPS: the version gate silently loses a session.**
Claude live collect tolerates an absent body `version` (`claude_code.cpp:708` falls back to live status),
so a row can pass the version floor on `sessions/<id>.json` evidence while its transcript body has none.
That row stages, then vanishes from the re-pack with only a `StagedSessionVersionMissing` warning
(`claude_code.cpp:439-443`). Fatal→silent is an improvement, but the same-set biconditional still fails
and the outcome is SESSION LOSS on a legal round-trip. Close it (writer establishes, or the reader takes
version evidence from the sidecar/manifest rather than the body). Codex is not reachable the same way
(`cli_version.value_or("unknown")` fails admission).

**G-4 [Major] Claude alias harvest is conditioned on manifest child ATTRIBUTION — the F-5 shape surviving in claude.**
`install.cpp:783-787` (refused) and `:815-822` (admitted) both require the artifact to appear in some
`children[].artifacts` before harvesting `agentId`. A subagent transcript listed under `record.artifacts`
but not attributed to a child is rewritten against a union that never received its alias, and `verify_scan`
cannot see it (`agentId` is not a message-uuid field). Not producible by biv's own collector — i.e. exactly
the foreign-image case the invariant exists for. Pair with M-4 F-F (claude constrains only the HEAD identity
while codex enforces `*child_identity == child.original_id`): the claude invariant is held by derivation
rather than by a check, which is what makes G-4 reachable.

## Non-gating (fold cheaply or register; disclose either way)

- M-4 F-C, narrowed by the scout: the guard's domain excludes non-`subagents/` subtree dirs
  (`<id>/history/x.jsonl` is rewritten unguarded). Reader does not gate them either, so the round-trip is
  symmetric — the residual is the same foreign-image leak class as G-4.
- M-4 F-D = round-trip #4 (both lenses, independently): the guard's typed refusal is overwritten by the
  verify-hits relabel at `install.cpp:909-914` — fail-closed, but the row misattributes cause.
- Tests #2: collect-side `staged_identity_mismatch` refusals assert only "pack failed", untyped; the
  loosened reader check has no test that distinguishes its refusal from any other.
- Tests #3: F-3 asserts the warning KIND but not its PATH, so "row-scoped" is unproven.
- Tests #4 / round-trip: the writer guard is claude-only while BOTH readers were loosened — pairs with G-2.
- Round-trip #5: the staged reader accepts an id-less codex rollout that live collect would skip.
- M-4 F-E: the sidecar `provenance_chain` still carries a guard-refused row's origin ids
  (`sessions.cpp:120-125`) — pre-existing and by design (`id_map.image_session_id` IS an origin id), not an
  agent-store leak and not a regression. Recorded so it is not re-opened.

## What HOLDS (verified; carries)

- F-4 closed: the staged-provenance gate is GONE from claude's refusal-branch harvest (only remaining
  `staged` bool at `install.cpp:621` serves the containment pre-check) — convener-verified.
- F-5 closed: codex's all-records loop now inserts the CHILD artifact-derived identity at `:467-468`,
  before admission — convener-verified.
- Both falsifiers exercise the UNGATED classes: F-4's fixture is genuinely non-staged (`sessions_root`/`env`
  defaults; the staging lines were deleted), and F-5's row is version-refused so it cannot be smuggled in
  via the prepared-session path. The fixture blindness that let F-4 survive the last panel is closed.
- The mandated `{}`-body round-trip falsifier PASSES end-to-end on real production code
  (`test_pack.cpp:1640` through `run_session_leg` → install → `publish_staging_manifest` → `pack` →
  `append_staged_session`), not a double.
- The new guard: outputs genuinely cleared with no partial write (batch builder skips refused rows; the only
  write is `write_batch_no_replace`), no union gap (the union is frozen before the guard fires), not a
  fresh-`InstallResult` discard, and R-4.15's destination-path class is NOT widened (destination
  construction byte-identical to PRIOR).
- No previously-passing test was weakened to turn a red green: the three changed assertions are honest
  re-targetings of the deliberate behavior change, and both branches of each loosened comparison stay bound.
- A3: both anchors match `e3.py` and the harness delta is exactly the two literal replacements.
- Mechanical (convener): one commit atop byte-identical C, subject preserved, 17-path cumulative range,
  fold delta == the 8 declared FOLD_SCOPE paths, stack merges clean onto LOCAL main.

## Disposition

FAIL → one bounded fold (G-1..G-4 + elected non-gating items + falsifiers) under a fresh token, then a
re-check scoped to that fold delta, then the fresh paired hand-up carrying A10.3 (C never lands without B2).
