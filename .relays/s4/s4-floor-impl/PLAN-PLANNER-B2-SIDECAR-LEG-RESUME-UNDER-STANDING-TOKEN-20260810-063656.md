## PLAN — the B2 STOP condition is RESOLVED: ADDENDUM-11 is VP-approved, LOCKED at `422d451b…`, and D5-RATIFIED by this seat (companion relay, same filing). The B2 sidecar leg RESUMES under the STANDING four-folds token `s4-floor-impl-2-cb2-four-folds` (000215) — this relay carries NO new token and re-grants nothing; it resolves the token's own STOP-and-route condition with the locked design of record. Implement the row-to-pair edge per the certified bytes; the two-path RED (= FX-A11-1) turns green; fold coherently with A1/A2 on the 1+N per-row-site lockstep.

ROLE: Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-floor-impl-2-b2-leg-resume
PARENT_DISPATCH_ID: s4-floor-impl-2-cb2-four-folds
RUN_ID: s4
TASK_ID: B2
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new gate — implementation authority is the standing bare token in IMPL-PLANNER-CB2-FOUR-FOLDS-DISPATCH-IMPL-TOKEN-20260810-000215.md, still live and undischarged; downstream gates unchanged (targeted re-panel, fresh paired hand-up, operator's paired condition-4, ABSOLUTE release hold)
DESIGN_LOCK_ID: m2-addendum11-422d451b-lock-20260810
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
CONSUMED_CONTRACT: m2-addendum11-422d451b-lock-20260810 (LOCKED_CONTENT_SHA256 422d451b0c613a44f30bf8a93739a691ee410e178ffea7942ec1c31b728d4fcb; rev11 blob at pdc 858d1ca5f4af66ddb2f186466d2ee1d2b77aa7e7; void if bound bytes move)
IN_REPLY_TO: .relays/s4/s4-floor-impl/SITREP-IMPLEMENTER-CB2-B2-CARRIER-SHAPE-STOP-ROUTED-20260810-003057.md
RELATED_CONTEXT: .relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-B2-A9-ADDENDUM11-D5-RATIFIED-SIDECAR-LEG-PROCEEDS-20260810-063120.md (the unblock); .relays/s4/s4-floor-impl/DESIGN-REVIEW-PLANNER-ADDENDUM11-D5-CONSUMER-RATIFY-APPROVE-20260810-063656.md (the ratification, same filing)
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: s4.orchestrator-planner, operator, s4.orchestrator-reviewer
SUBJECT: PLAN — resume the B2 sidecar leg under the standing four-folds token; implement ADDENDUM-11 at the certified bytes; 1+N lockstep with A1/A2; falsifier set and per-owning-head placement restated

## Read the design at the CERTIFIED bytes, not the working file
`cd ../pdc && git show 858d1ca:master/domains/m-2-agent-adapters/design/2026-08-10-ADDENDUM-11-a9-row-to-pair-edge.md`
— the working file carries the lock stamp on top and does NOT hash to `422d451b…` by
construction. I re-derived the hash at that blob and verified the stamp delta is the four
named lock changes only. Normative sections: §A11.2 (+.1), §A11.5, §A11.6, §A11.8 pins.

## The contract you implement (restated from the certified bytes; the bytes govern)
- **Writer** (`sessions.cpp`, C's owning head): the A9 id_map row gains ONE OPTIONAL
  `original_path`; the forward writer EMITS IT ALWAYS. Join by `(agent,
  image_session_id)` to the unique manifest `AgentSessionEntry` — NEVER by order of
  `records`/`id_map`/sorted pairs; missing or duplicate join = writer failure. Emit the
  canonical representative selected BY KIND from `origin_spellings(matched_record
  .original_path, matched_record.path_flavor)`: windows drive path → the
  `windows_backslash` spelling; otherwise → the `literal` spelling. NOT the raw record
  value (§A11.2.1 — a mixed-separator drive path's raw spelling is absent from the
  derived set and would fail the addendum's own parser). `pair_set_applied` stays
  byte-identical in shape/content/meaning; sort/unique untouched.
- **Reader** (both staged re-collectors, B2's owning head; the member is GENERIC):
  TWO CLOSED STATES across ALL id_map rows, all agents — (1) every row lacks the member
  ⇒ the exact old global inference runs unchanged; (2) every row carries a validated
  member ⇒ no fallback runs at all; anything else refuses `invalid_staged_sidecar` at
  PARSE. PRESENT validation: non-empty AND exact membership
  `(row.original_path, source_root.generic_string()) ∈ pair_set_applied`; wrong type /
  empty / duplicate member / missing pair / target mismatch all fail closed, never a
  fallback. Claude re-collect provenance uses the VALIDATED row value; the ADDENDUM-10
  destination-keyed staged LOCATION is unchanged (6a/6b are independent falsifiers).
- **Not a containment control:** the membership cross-check is integrity-only (both
  values live in one attacker-controlled file) — do not cite it against hostile images.

## Fold coherence — the 1+N lockstep (the orchestrator's §3, do not miss it)
The scrub/needle surface moves from ONE site to **1 + N**: the global `pair_set_applied`
COLLECTION (which can hold MANY occurrences — uniqueness is on the pair, not the origin)
PLUS one `original_path` OCCURRENCE PER STAGED ROW (occurrences, NOT distinct values — no
uniqueness invariant exists; several rows may carry the same string). Your A1/A2 fold's
needle/verify surface must account for EVERY per-row occurrence, not the member as one
category-site. **Required falsifier: a per-row-site RED exercising N>1 occurrences.**
This is the registered R-4.8 constraint (`RESIDUALS.md:983-989`) — the floor owns its
consumer side; the image-manifest carrier side stays matrix Arm-1's.

## Falsifiers for this leg (on top of the token's standing set)
- FX-A11-1: the standing two-path codex round-trip RED → GREEN (each row recovers its own
  path from its own member; no inference consulted for rows carrying it).
- FX-A11-2: compatibility negative — an all-absent (old) sidecar yields EXACTLY today's
  outcome INCLUDING the typed refusal on the ambiguous case; must stay green.
- FX-A11-3 vs FX-A11-4 as DISTINCT tests: malformed-at-parse vs well-formed-but-outside-
  the-audit-set; FX-A11-5 mixed presence refuses; FX-A11-6a/6b per consumer;
  FX-A11-7a/7b producer closure (mixed-separator origin, per consumer); FX-A11-8a/8b
  idempotence (already-canonical value is a fixed point; second re-pack byte-identical).
- The 1+N per-row-site RED (above) folded with A1/A2.

## Placement, ceremony, and the return (unchanged from the token)
Writer change on C's owning head; reader/re-collector changes on B2's; each head stays
ONE bounded fold. `codex.cpp`/`claude_code.cpp` are ANCHORED — the A3 both-anchor
ceremony re-fires per touched head. Then: full falsifier set for all four folds, suites
honestly green (macOS + Docker linux/amd64), republication, and report REVIEW-FOLD with
FOLD_SCOPE per the token — after which I convene the targeted re-panel (M-4 + round-trip
lenses at the new SHAs) and the fresh paired hand-up follows. Disclosed behavior change
to carry in your report verbatim: a Windows drive origin containing any `/` normalizes to
the canonical spelling on round-trip (spelling-confined; pinned by 7a/7b, 8a/8b).
Nothing seals; `231437` stays WITHDRAWN; merge ≠ push ≠ release; the release hold is
ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — design verification in ../pdc at 858d1ca5f4af66ddb2f186466d2ee1d2b77aa7e7 / 1d7419c695a29493d177b66670075fddcb4ec334 (read-only); this relay + the companion ratification + INDEX rows ride one explicit-path docs-lane commit whose SHA lands after filing
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to the two relays and .relays/s4/INDEX.md

CARRY LIST:
- `.relays/s4/s4-floor-impl/PLAN-PLANNER-B2-SIDECAR-LEG-RESUME-UNDER-STANDING-TOKEN-20260810-063656.md` → `s4-floor.implementer`
- B2 sidecar leg RESUMES under standing token 000215 (no new token; STOP condition resolved by ADDENDUM-11 at 422d451b, D5-ratified); read the design at the pdc rev11 blob, not the stamped file
- writer always-emit canonical representative by (agent, image_session_id) join on C's head; reader two-closed-states + membership fail-closed on B2's head, both re-collectors; A3 re-fires
- 1+N lockstep with A1/A2 (occurrences per row + the global collection; N>1 per-row-site RED); FX-A11-1..8b falsifier set; then suites green → REVIEW-FOLD report → targeted re-panel; release hold ABSOLUTE
