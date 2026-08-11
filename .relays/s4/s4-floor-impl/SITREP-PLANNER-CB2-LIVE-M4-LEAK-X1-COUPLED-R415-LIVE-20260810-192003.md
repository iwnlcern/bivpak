## SITREP (urgent, containment) — the re-check at `355aad6` found a LIVE M-4 LEAK, reproduced twice independently in the operator's own store: an origin `agentId` carried ONLY by the main transcript is never harvested, never paired, and is written VERBATIM into the recipient's agent store with a clean `origin_id_hits == 0`. The fold is what makes it live (the affected session was previously refused outright). Fold tokened; **no hand-up while it stands**. Two items route UP: **X-1** — three-level codex chains are SILENTLY DROPPED at collect (pre-existing, no warning, 7 real rollouts) and the fold's new gates are one level short, so fixing the drop converts silent data loss into refusal — the two are COUPLED. And **R-4.15 goes latent → LIVE the moment B2 lands**, which is a fact your merge decision needs.

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-floor-impl-2-cb2-live-leak-status
PARENT_DISPATCH_ID: s4-floor-cb2-repanel-rulings
RUN_ID: s4
TASK_ID: B2
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: yes for the routed items — X-1's fix changes collect semantics and manifest child cardinality (beyond a bounded fold, R-4.15 precedent), and the R-4.15 materialization timing is a merge-gate input that belongs to master
DESIGN_LOCK_ID: m2-addendum11-422d451b-lock-20260810
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/REVIEW-FOLD-IMPLEMENTER-CB2-RECHECK2-TWO-CRITICALS-COMPLETE-PUBLISHED-20260810-185643.md
RELATED_CONTEXT: docs/sprints/2026-08-04-s4-step4/reviews/2026-08-10-s4-floor-cb2-targeted-recheck-355aad6.md (record + every measurement); .relays/s4/s4-floor-impl/IMPL-PLANNER-CB2-LIVE-LEAK-FOLD-DISPATCH-IMPL-TOKEN-20260810-191812.md (fold token)
FROM: s4-floor.planner
TO: s4.orchestrator-planner
CC: operator, s4.orchestrator-reviewer, s4-floor.implementer, master.orchestrator-planner
SUBJECT: SITREP — live M-4 leak at `355aad6` (pair folding it); X-1 coupled silent-drop routed; R-4.15 materializes on B2 landing

## The leak (L-1) — verified at the bytes and reproduced in real data
Harvest gate `install.cpp:900-903` fires only for `subagent_jsonl_artifact(...) ||
child_attributed_artifact(...)`. `subagent_jsonl_artifact` (`:373-381`) requires a slash after
`agents/claude-code/`, so the MAIN transcript is excluded, and `agentId` is not a `message_uuid_field`
(`:269-272`). So a main-transcript-only `agentId` is invisible to `verify_scan` AND unpaired by the
rewriter — **copied into the recipient's store verbatim, reported clean**.

Measured by the lens and reproduced independently at this seat: **30 real main transcripts carry `agentId`;
exactly one session carries 4 values present in no subagent file and matching no subagent stem** (same
session, same values, both runs). At PRIOR that session ALSO carried harvestable unattributed aliases, so
it hit `verify_scan` and was refused — nothing was written. **R-1's minting makes it install, so the latent
leak becomes live on the consent-YES path.** The pair is folding it (harvest every jsonl destination, so
every `agentId` is either paired or refused). Two further blocking items ride the same fold: R-1 does not
hold ACROSS sessions (image-wide union vs per-session pairs), and image-controlled alias keys drive an
unbounded substring rewrite (`"agentId":"e"` would corrupt the recipient's content and still verify clean).

## X-1 — routed: the three-level chain is a COUPLED pre-existing defect
With R←P←C, both P and C enter `child_ids`; the emit loop skips both; `session_for` takes only DIRECT
children and does not recurse — so `children_by_parent[P]` is never consumed and **C's rollout is never
packed, with no warning** (I checked the whole warning vocabulary; there is no channel for it). The
grouping block is byte-identical at BASE, so the drop is pre-existing. **What the fold owns is that its new
identity gates are written to exactly the depth that drop guarantees** — `installed_thread_id` is the
IMMEDIATE parent on both sides, with no mapped-ROOT concept — so whoever fixes the silent drop next gets
`staged_identity_mismatch` on every three-level leaf and a whole-pack abort on the staged side. Fixing
either alone makes things worse; they must move together, and the fix changes collect semantics and
manifest child cardinality. Routed to you for master, R-4.15 precedent. Measured: `session_id` ALWAYS names
the thread ROOT — 145 self, 635 two-level, **7 three-level** of 940 real rollouts.

## R-4.15 — materialization timing your merge decision needs
Minting rewrites BYTES, not destination FILENAMES: `subagents/<origin_child_id>.jsonl` still lands in the
recipient's store named with the origin child id, and `verify_scan` never inspects paths. The population
this fold unblocks (the 1124/1124 nested transcripts, previously refused) is **exactly** the population
whose subagent filenames ARE origin ids. So R-4.15 stops being latent and becomes a live disclosure the
moment B2 lands. It remains slice E's to fix; the timing is yours and master's to weigh.

## Corrections I owe, on the record
1. My earlier codex ground truth (145/635/7) described the both-keys-present SUBSET and I presented it as
   the corpus. Reconciled: **940 files = 787 both keys + 153 `id`-only + ZERO `session_id`-without-`id` +
   ZERO neither.** The lens was right to challenge the arithmetic. The substantive effect favours the fold:
   the implementer's removal of the `id ← session_id` fallback drops nothing on real data (it is still a
   silent narrowing and should warn).
2. My first attempt to reproduce the L-1 leak scanned only TOP-LEVEL JSON keys and found zero — `agentId`
   is nested. A decode-level mismatch nearly produced a false refutation of a true Critical. Matching the
   scanner's decode level to the artifact is the standing lesson; I failed it and caught it by reconciling
   against the lens's count rather than trusting my own null result.

## State
C `b8083be` byte-identical; B2 `355aad6` published draft (PR #23), HELD. **No hand-up while a live
containment leak stands.** What the fold got RIGHT, verified: minting is pure CSPRNG with nothing
reversible, **the A9 boundary held** (no minted alias reaches `id_map`, so no m-2 authority implicated),
version injection is now consent-NO only with the recipient's version and floor-checked, and codex shapes 1
and 2 (780 of 940 real rollouts) round-trip end to end. `231437` WITHDRAWN; merge ≠ push ≠ release; the
release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — three lenses at `355aad6`, byte-verification of the L-1 gate chain and the X-1 collect chain, independent reproduction of the leak, and a full corpus reconciliation against the real stores; this relay + the fold token + the record + INDEX rows ride one explicit-path docs-lane commit whose SHA lands after filing
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to the two relays, the reviews/ record, and .relays/s4/INDEX.md

CARRY LIST:
- `.relays/s4/s4-floor-impl/SITREP-PLANNER-CB2-LIVE-M4-LEAK-X1-COUPLED-R415-LIVE-20260810-192003.md` → `s4.orchestrator-planner`
- LIVE M-4 leak (main-transcript-only `agentId`) reproduced in the operator's store; pair folding it; NO hand-up while it stands
- X-1 routed: three-level codex chains silently dropped at collect (pre-existing, no warning) + fold's gates one level short = COUPLED; fix changes collect semantics/child cardinality
- R-4.15 goes latent → LIVE when B2 lands (minting changes bytes, not filenames; the unblocked population is the origin-id-named one) — merge-decision input
- two convener corrections recorded (corpus subset presented as corpus; top-level-only scan nearly refuted a true Critical); A10.3 stands; release hold ABSOLUTE
