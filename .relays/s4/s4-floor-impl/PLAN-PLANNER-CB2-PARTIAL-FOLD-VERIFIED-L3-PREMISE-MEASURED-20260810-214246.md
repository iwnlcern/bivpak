## PLAN — your partial fold at `e0d6c19` is VERIFIED at my seat and your hold compliance is exact. Three things you could not have had when you filed: (1) **I measured L-3's premise for you** — your boundary predicate treats `-`/`_` as identifier bytes, so an origin id adjacent to one is NOT rewritten while verification stays strict, which would REFUSE the session; in the operator's real store **244/244 `agentId` occurrences are cleanly bounded, zero blocked**, so the change refuses nothing real. Carry that measurement in your next report — it discharges the standing guard-premise rule for this guard. (2) **The corpus dispute is CLOSED**: I disclosed provenance 3 seconds after you filed and the figures reconcile EXACTLY — same store, different search depth. (3) **The fixture guidance changes**: not just shapes but LAYOUTS.

ROLE: Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-floor-impl-2-cb2-partial-verified
PARENT_DISPATCH_ID: s4-floor-impl-2-cb2-live-leak-fold
RUN_ID: s4
TASK_ID: B2
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no at this hop — acknowledgement plus corrections under the existing hold; option (a) implementation still waits on the operator's ratification of the content-scope widening (`205325`) and my carry-down. The release hold is ABSOLUTE.
DESIGN_LOCK_ID: m2-addendum11-422d451b-lock-20260810
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/REVIEW-FOLD-IMPLEMENTER-CB2-LIVE-FOLD-PARTIAL-HOLD-COMPLETE-PUBLISHED-20260810-212701.md
RELATED_CONTEXT: .relays/s4/s4-floor-impl/SITREP-PLANNER-CORPUS-PROVENANCE-DISCLOSED-RECONCILED-EXACTLY-20260810-212704.md (the provenance you were owed, filed 3s after your report)
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: s4.orchestrator-planner, operator, s4.orchestrator-reviewer, m-2.planner
SUBJECT: PLAN — partial fold verified; L-3 premise measured clean (244/244); corpus reconciled; fixtures must cover BOTH layouts

## 1. Verified at my seat (not taken on your word)
One commit atop byte-identical C `b8083be`; subject preserved; delta is exactly your eight declared paths;
codex anchor `2fd24c84…` matches the new bytes and the claude anchor `cd1f8bc8…` is correctly unchanged
(you only touched the codex collector). **Hold compliance exact:** the alias harvest gate at
`install.cpp:907` is NOT widened, no new minting arm exists, and the R-4.18 one-level constraint is honored
(no recursion, no root-mapped comparison, no leaf warning). Keeping the L-1/L-2 falsifiers compiled, hidden
under `[.pending-r415]`, and RED — rather than deleting them or letting them read as closed — is exactly
right and I want it repeated on the next cycle.

## 2. L-3's premise — measured, so you do not have to
Your boundary predicate `id_token_byte` includes `-` and `_`. That means an origin id occurring adjacent to
one of those (canonically the `agent-<id>.jsonl` form) is skipped by the boundary-aware rewrite while strict
substring verification still sees it — i.e. **refuse rather than leak**. Correct choice; but it is a new
guard resting on an assumption about real data, so the standing rule applies. Measured on the operator's
live store: **of 244 real `agentId` occurrences in main transcripts, 244 are cleanly bounded and ZERO are
boundary-blocked.** The `agent-<id>` spelling exists as a FILENAME on disk but does not appear inside
transcript content, so the asymmetry you built refuses nothing real. **Put this measurement in your next
REVIEW-FOLD** — the guard is sound and now it is evidenced.

## 3. The corpus item is CLOSED — you may cite either figure
Your report says the 1702-stem population's provenance "remains owed by the planning pair". I filed it at
`212704`, three seconds after you filed, so you could not have seen it. Reconciled EXACTLY, same host, same
live store, different search depth:
```
FLAT   <sess>/subagents/*.jsonl      578  = 309 bare-hex + 269 slug-hex   <- the 212119 figures, to the unit
NESTED <sess>/subagents/<wf>/*.jsonl 1124 = 1099 bare-hex +  25 other
TOTAL                                1702
```
Both figures are correct measurements of the same store; the earlier one simply included the nested layer.
Nothing came from a fixture tree or another host.

## 4. Fixture guidance — corrected, and it gained an axis
Your carried note ("fixtures must model 309 bare-hex / 269 slug-hex") is right for the FLAT layer and
incomplete for the population:
- **bare-hex majority strengthens** — 53% of the flat layer, **83% of the whole population** (1408/1702);
- **slug-hex is FLAT-ONLY** (269); **`other` is NESTED-ONLY** (25);
- therefore the standing round-trip acceptance fixtures must cover **BOTH LAYOUTS, not just both shapes**:
  a flat bare-hex child, a flat slug-hex child, AND a nested bare-hex child under `subagents/<wf>/`.
A flat-only fixture set models 34% of the population and omits the exact layout R-4.15 is about.

## 5. What happens next
The panel re-check on this partial delta is **DEFERRED, deliberately**: option (a) will change
`install.cpp` again, and paneling bytes that are about to move spends a panel on a decaying artifact. One
re-check will cover the combined candidate — L-3/X-2/X-3/T-1..T-4/C-1/M-1 **plus** (a) — and it will be
scoped to the union of both deltas, not just the last one. I have told the orchestrator so they can
overrule if they want the interim bytes paneled now. **Nothing in this relay authorizes (a)**; on the
operator's ratification I amend the token with (a), the dissolution of L-1/L-2/R-4.15, and the fixture
basis above. Until then the hold stands unchanged. C never lands without B2 (A10.3); publication stays on
the `154400` terms; `231437` WITHDRAWN; merge ≠ push ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — byte verification at `e0d6c19` (topology, eight-path delta, both A3 anchors, harvest-gate non-widening, R-4.18 compliance) plus the real-store boundary-adjacency measurement reported in §2; this relay + the companion SITREP + INDEX rows ride one explicit-path docs-lane commit whose SHA lands after filing
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to the two relays and `.relays/s4/INDEX.md`

CARRY LIST:
- `.relays/s4/s4-floor-impl/PLAN-PLANNER-CB2-PARTIAL-FOLD-VERIFIED-L3-PREMISE-MEASURED-20260810-214246.md` → `s4-floor.implementer`
- partial fold VERIFIED at my seat (topology, anchors, harvest gate not widened, R-4.18 honored); the hidden-but-RED pending falsifiers are the right pattern — repeat it
- L-3 premise MEASURED for you: 244/244 real `agentId` occurrences cleanly bounded, ZERO boundary-blocked → the refuse-rather-than-leak asymmetry refuses nothing real; carry it in your next report
- corpus CLOSED: 578 flat + 1124 nested = 1702, same store, different depth; fixtures must cover BOTH LAYOUTS (flat bare-hex, flat slug-hex, nested bare-hex), bare-hex 83% of population
- re-check DEFERRED to the combined post-(a) candidate (orchestrator may overrule); (a) NOT authorized here; hold unchanged; release hold ABSOLUTE
