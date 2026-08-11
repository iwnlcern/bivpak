## PLAN (URGENT amendment to the live `191812` token) — **HOLD the L-1 ALIAS ARM. Do not extend alias minting.** My token told you to close L-1 by harvesting child-identity values from EVERY jsonl destination and pairing them. Master has since closed R-4.15 at the bytes to a LIVE FUNCTIONAL RESTORE DEFECT whose CAUSE is that very minting: rewriting the parent's `senderTaskId`/`agentId` to `uuid4()` while the child file keeps its `agent-<origin-id>.jsonl` name breaks the ONLY reference→file index, so restored sessions cannot find their subagents. **Under that ruling my instruction would make things worse — more harvesting means more dangling references.** I measured it in the operator's real store and the defect is confirmed. Everything else in the fold proceeds; the alias arm waits for the reconciled L-1 + R-4.15 design I am building with m-2.

ROLE: Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-floor-impl-2-cb2-hold-alias-arm
PARENT_DISPATCH_ID: s4-floor-impl-2-cb2-live-leak-fold
RUN_ID: s4
TASK_ID: B2
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — an amendment narrowing work under a live token; implementation authority remains the bare dispatch token in `191812`. The release hold is ABSOLUTE.
DESIGN_LOCK_ID: m2-addendum11-422d451b-lock-20260810
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-CB2-R415-FUNCTIONAL-DEFECT-REPAIR-INVERTED-GATES-FOLD-20260810-202645.md
RELATED_CONTEXT: .relays/s4/s4-floor-impl/IMPL-PLANNER-CB2-LIVE-LEAK-FOLD-DISPATCH-IMPL-TOKEN-20260810-191812.md (the live token this narrows); .relays/s4/s4-floor-impl/PLAN-PLANNER-CB2-FOLD-ONE-LEVEL-CONSISTENT-CONSTRAINT-20260810-193623.md (R-4.18 constraint, still binds)
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: s4.orchestrator-planner, operator, s4.orchestrator-reviewer, m-2.planner
SUBJECT: PLAN — HOLD the L-1 alias arm (my instruction is now harmful under master's R-4.15 ruling); the rest of the fold proceeds; reconciled design coming with m-2

## 1. What is held, precisely
**HELD — do not implement, and revert it if you have already written it:**
- widening the alias harvest to the main transcript / every jsonl destination (L-1's pairing arm);
- any new `child_alias_ids` minting, and any change that increases the set of values rewritten in a
  PARENT transcript.
If you have already made the alias arm change locally, keep it on a scratch branch or drop it — do NOT
publish it. Nothing about the hold implies your work was wrong; **the instruction was mine and it is now
superseded by a ruling that inverts its direction.**

**PROCEEDS as written in `191812` (unaffected by R-4.15):**
- L-3 shape-guard on the alias before it can become a rewrite key (still correct — an unbounded substring
  key is a hazard regardless of whether we mint);
- X-2 (warn the `id`-fallback narrowing), X-3 (row-scope the staged-reader identity refusals),
  T-1..T-4, C-1, M-1;
- the R-4.18 one-level-consistency constraint is UNCHANGED and still binds.
**L-2** (cross-session refusal) is entangled with the reconciled design — hold its implementation too, but
keep any falsifier you have written for it; the falsifier survives either fork.

## 2. Why — measured, not argued
`.meta.json` carries NO id field (its keys are `agentType`, `description`, `toolUseId`, `spawnDepth`,
`parentAgentId`, …), so **the filename is the only reference→file index**. In the operator's real store:
**`senderTaskId` resolves to an on-disk stem 107/107; `agentId` 240/244** (the 4 exceptions are the L-1
orphan session, whose subagent files genuinely do not exist — i.e. that class is a pre-existing dangle, not
a new one). So a rewrite of the parent's reference without a matching rename is a guaranteed dangle. That
is the operator's named "sessions re-seeking" failure, and it gates the merge.

## 3. What comes next (mine, not yours)
I am reconciling L-1 and R-4.15 as ONE design with m-2 — they are the same mechanism, and with the
confidentiality motive for opaque child ids dissolved, "stop minting child aliases" is on the table, which
would dissolve L-1's leak rather than pair around it. You will get one amended instruction covering both.
Acceptance will include a STANDING round-trip check: pack a session with subagents → open → the restored
parent's `senderTaskId`/`agentId` must equal the on-disk `subagents/` stems. **You may build that check now
if it helps you** — it is wanted either way and is the first instrument in this band that measures whether a
restored session WORKS rather than merely that we did not corrupt it.

C never lands without B2 (A10.3). Publication timing is CLOSED (no hold for it). `231437` WITHDRAWN;
merge ≠ push ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — byte re-verification of the alias trace at `355aad6` (`child_alias_ids.push_back({alias, uuid4()})` :934 → `ids` :965-966 → applied to every jsonl destination) plus real-store measurement of `.meta.json` keys, stem shapes, and reference resolution; this relay + the companion design SITREP + INDEX rows ride one explicit-path docs-lane commit whose SHA lands after filing
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to the two relays and `.relays/s4/INDEX.md`

CARRY LIST:
- `.relays/s4/s4-floor-impl/PLAN-PLANNER-CB2-HOLD-L1-ALIAS-ARM-PENDING-R415-DESIGN-20260810-203310.md` → `s4-floor.implementer`
- HELD: the L-1 alias-harvest arm and any new alias minting (my instruction is harmful under master's R-4.15 ruling); L-2 implementation held, its falsifier kept
- PROCEEDS: L-3 shape guard, X-2, X-3, T-1..T-4, C-1, M-1; R-4.18 one-level-consistency still binds
- measured: `.meta.json` has no id member (filename is the ONLY index); senderTaskId 107/107 and agentId 240/244 resolve to stems in the real store
- reconciled L-1 + R-4.15 design coming from me with m-2; the standing round-trip resolution check may be built now; release hold ABSOLUTE
