## DISPATCH (fold) — a LIVE M-4 CONTAINMENT LEAK is present at `355aad6` and this fold made it live. An origin `agentId` carried ONLY by the main transcript is never harvested, never paired, and is written VERBATIM into the recipient's store with a clean `origin_id_hits == 0`. Measured twice independently in the operator's own store: 30 main transcripts carry `agentId`; one session carries FOUR values that exist in no subagent file at all. At PRIOR that session was refused outright, so the leak was latent — R-1's minting makes it install, and the leak goes live on the consent-YES path. Your minting work is CORRECT and the A9 boundary held; the failure is that the harvest GATE it inherits is narrower than the union it feeds. Also blocking: R-1 does not hold across sessions, and image-controlled alias keys drive an unbounded substring rewrite.

ROLE: Planner
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: s4-floor-impl-2-cb2-live-leak-fold
PARENT_DISPATCH_ID: s4-floor-pair-plan-review-approve
RUN_ID: s4
TASK_ID: B2
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new gate at this hop — pair-scope fold; but NO hand-up occurs while a live containment leak stands, and the release hold is ABSOLUTE
DESIGN_LOCK_ID: m2-addendum11-422d451b-lock-20260810
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/REVIEW-FOLD-IMPLEMENTER-CB2-RECHECK2-TWO-CRITICALS-COMPLETE-PUBLISHED-20260810-185643.md
RELATED_CONTEXT: docs/sprints/2026-08-04-s4-step4/reviews/2026-08-10-s4-floor-cb2-targeted-recheck-355aad6.md (record; L/X/T/C/M ids and every measurement live there)
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: s4.orchestrator-planner, operator, s4.orchestrator-reviewer
SUBJECT: FOLD — L-1 live leak (blocking), L-2 cross-session refusal, L-3 unbounded rewrite key, X-2/X-3 codex, plus the test-side gaps; X-1 and R-4.15 materialization route UP

DISPATCH IMPL

SCOPE_DIFF:
- src/adapters/claude_code/install.cpp -> in
- src/adapters/codex/install.cpp -> in
- src/adapters/claude_code/claude_code.cpp -> in
- src/adapters/codex/codex.cpp -> in
- src/adapters/rewrite_common.cpp -> in
- src/adapters/rewrite_common.hpp -> in
- tests/test_pack.cpp -> in
- tests/test_adapter_claude_install.cpp -> in
- tests/test_adapter_codex_install.cpp -> in
- tests/test_adapter_claude_collect.cpp -> in
- tests/test_adapter_codex_collect.cpp -> in
- harness/bivharness/e3.py -> in

SCOPE_DIFF_RESULT: all-in

SCOPE_ROW_EVIDENCE:
- src/adapters/claude_code/install.cpp -> L-1 harvest gate (:900-903, :373-381); L-2 union vs per-session ids (:944-947 vs :955-967); L-3 alias shape guard before mint (:468-479, :934); M-1 mint/attribute precedence (:906-936)
- src/adapters/codex/install.cpp -> X-3 writer/reader blast-radius symmetry counterpart
- src/adapters/claude_code/claude_code.cpp -> T-1 never_collect_path falsifier target (:475)
- src/adapters/codex/codex.cpp -> X-2 id-fallback warning (:248-250); X-3 row-scope the staged reader refusals (:746-748, :778-780)
- src/adapters/rewrite_common.cpp -> L-3 boundary handling for id pairs (:328-337 vs :358-368)
- src/adapters/rewrite_common.hpp -> declarations for the same
- tests/test_pack.cpp -> L-1/L-2 round-trip falsifiers; T-2 restored unknown-class case; T-3 attribution collision
- tests/test_adapter_claude_install.cpp -> L-1 main-transcript-only alias falsifier; L-3 hostile short-alias; T-4 replacement shape
- tests/test_adapter_codex_install.cpp -> X-3 row-scoped refusal falsifier
- tests/test_adapter_claude_collect.cpp -> T-1 never_collect fixture (a denied name that IS a valid staged class)
- tests/test_adapter_codex_collect.cpp -> C-1 dangling-parent fixtures re-shaped to root-valued session_id
- harness/bivharness/e3.py -> A3 both-anchor re-fire IF anchored collectors change

## L-1 — the blocking leak (fix this first)
The gate at `:900-903` harvests aliases only from `subagent_jsonl_artifact(...) || child_attributed_artifact(...)`.
`subagent_jsonl_artifact` requires a slash after `agents/claude-code/`, so the MAIN transcript is excluded,
and `agentId` is not a `message_uuid_field`. Result: a main-transcript-only `agentId` is invisible to
`verify_scan` AND unpaired by the rewriter — written through clean.
**Fix: harvest child-identity values from EVERY jsonl destination, so every `agentId` is either paired or
refused — never silently passed.** Falsifier: plant `agentId` in the main transcript ONLY, consent=YES;
assert the origin value is ABSENT from the installed bytes (today it is present with `origin_id_hits == 0`).
Add the consent-NO twin. **The reproduction is in the operator's live store — session `540453ff…` in the
`-Users-jack-Programming-harness--claude-worktrees-prior-art-codewhale` scope, 4 orphan values.**

## L-2 — R-1 does not hold across sessions
The union is image-wide (including refused sessions) while `ids` is per-session, so an alias owned by
session A appearing in B's bytes refuses B. Make the alias pair set image-wide (every alias→minted mapping
available to every session's rewrite) or scope the union per session — your call, but state the reasoning.
The current R-1 test ENCODES the refusal (session 1 asserted `verify-hits`); re-target it.

## L-3 — put a shape guard on the alias before it becomes a rewrite key
Id pairs go through `replace_all` with no boundary check while path pairs are guarded. `"agentId":"e"`
would rewrite every `e` in the recipient's transcript. Reject non-id-shaped aliases (or refuse the session)
BEFORE minting. Falsifier: a hostile 1-char alias must not corrupt unrelated content.

## X-2 / X-3 / T-1..T-4 / C-1 / M-1 — see the record
X-2: your `id ← session_id` fallback removal drops NOTHING on real data (measured: zero rollouts carry
`session_id` without `id`) — but it is a silent narrowing outside stated scope; warn or justify. X-3:
row-scope the staged reader's identity refusals (today they abort the ENTIRE pack while the writer refuses
one row). T-1: `never_collect_path` in the staged branch has no falsifier — the `.DS_Store` fixture is
caught by the sibling arm; use a denied NAME that is a valid staged class. T-2: restore an unknown-class
warn-and-skip case and fix the stale test title. T-3/T-4/C-1/M-1 as recorded.

## Routed UP, NOT yours (do not absorb)
**X-1** — three-level codex chains: the leaf is SILENTLY DROPPED at collect (`codex.cpp:1293-1298`;
`session_for` takes only direct children and does not recurse) and your new gates are one level short
(`installed_thread_id` is the immediate parent), so fixing the drop converts silent loss into refusal. The
two are COUPLED; the fix changes collect semantics and manifest child cardinality. Routed to master.
**R-4.15 materialization** — minting changes BYTES, not destination FILENAMES, so origin child ids still
ride the path; the population you unblock is exactly the one whose subagent filenames are origin ids, so
R-4.15 goes latent → LIVE when B2 lands. Routed for master's merge decision. Do not touch either.

## Credit where due, at the bytes
Your minting is correct: pure `uuid4()` CSPRNG, not derived from any origin value, nothing reversible.
**The A9 boundary held** — `child_alias_ids` never reaches `result.id_map`, so no sealed-carrier change and
no m-2 authority implicated. Version injection is now consent-NO only, uses the recipient's
`caps.agent_version()`, and is floor-checked. R-5's precedence guard is real. Codex shapes 1 and 2 (780 of
940 real rollouts) round-trip end to end — the false-premise refusal IS genuinely fixed for them.

## Hard OUT (unchanged) and the return
WSL/A11 membership (m-2); R-4.15 (slice E); R-4.16; X-1 (master); sealed A9 shape; `.github/**`; merge; tag;
deploy; seal; release. Publication only on the `154400` terms. One bounded fold on B2's head; C stays
byte-identical; A3 re-fire if anchored collectors change; suites honestly green both platforms; REVIEW-FOLD
with FOLD_SCOPE, per-finding falsifier receipts, and the premise measurement for every guard you touch.
C never lands without B2 (A10.3). Release hold ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — three lenses at `355aad6`, convener byte-verification of the L-1 gate chain and the X-1 collect chain, and independent reproduction of the L-1 leak plus a full reconciliation of the codex corpus (940 files) against the real stores; this relay + the companion SITREP + the record + INDEX rows ride one explicit-path docs-lane commit whose SHA lands after filing
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to the two relays, the reviews/ record, and .relays/s4/INDEX.md

CARRY LIST:
- `.relays/s4/s4-floor-impl/IMPL-PLANNER-CB2-LIVE-LEAK-FOLD-DISPATCH-IMPL-TOKEN-20260810-191812.md` → `s4-floor.implementer`
- L-1 LIVE M-4 leak (main-transcript-only `agentId`), reproduced in the operator's store — blocking; harvest every jsonl destination
- L-2 cross-session refusal (global union vs per-session pairs); L-3 shape-guard the alias before it becomes an unbounded rewrite key
- X-2 warn on the id-fallback narrowing (measured zero impact); X-3 row-scope staged-reader refusals; T-1..T-4, C-1, M-1 as recorded
- X-1 (three-level silent drop + one-level gates, COUPLED) and R-4.15 latent→LIVE materialization routed UP — do not absorb; A10.3 stands; release hold ABSOLUTE
