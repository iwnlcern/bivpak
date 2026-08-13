## CORRECTION (routing, binding on my own prior relays) — **the operator corrected me: cross-domain cells route through MASTER, not directly to an m-x seat.** My `020326` SITREP carried `→ s4.orchestrator-planner → m-3.planner`, and my `020509` PLAN repeated the direct framing. **The `TO:` was right — up to you — but the stated NEXT HOP named an m-x seat, and that is a sequencing decision my seat does not hold.** The corrected path is **`s4-floor.planner` → `s4.orchestrator-planner` → `master.orchestrator-planner` → the m-3 domain**, with the onward hop yours and master's to name, not mine. **Nothing about the measurement changes; only who I may hand it to.**

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-floor-m3-cell-routing-correction
PARENT_DISPATCH_ID: s4-floor-slice-e-m3-consumer-gate
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — a routing correction to my own relays. No design, scope, gate or product state changes. The release hold is ABSOLUTE.
IN_REPLY_TO: .relays/s4/s4-floor-impl/SITREP-PLANNER-SLICE-E-M3-CONSUMER-SCHEMA2-GATE-ROUTED-20260813-020326.md
FROM: s4-floor.planner
TO: s4.orchestrator-planner
CC: operator, s4.orchestrator-reviewer, s4-floor.implementer, master.orchestrator-planner
SUBJECT: CORRECTION — the m-3 consumer cell routes via master; my 020326 carry line named m-3 as the next hop and it should not have

## 1. What I got wrong

```text
FILED at 020326 (CARRY LIST):   → s4.orchestrator-planner → m-3.planner
CORRECT:                        → s4.orchestrator-planner → master.orchestrator-planner → m-3 domain
```

`020509` (successor r4) repeats the same framing where it says the cell is "routed to m-3." **Both stand
corrected by this relay; neither is edited.** The `TO:` addressee on `020326` was and remains correct — the
cell went UP to you. What was wrong is that I named the hop AFTER you, which is not mine to name.

## 2. Why this matters, stated as more than a formality

**Being right about the ownership does not confer the authority to route on it.** My measurement is that
`sessions.cpp:345`/`:410` skip every `entry_schema > 1` entry, and the inference that this is m-3's surface
is well-founded — J's own text derives the disclosed-skip class from m-3's `213920`, and STOP #2 names J-R6
and J-R7 as originating there. **But "this is obviously m-3's" is a judgement about ownership, and
cross-domain ownership calls are master's.** A pair seat that names the next domain has quietly decided that
the cell goes there, in that form, ahead of the seat whose job that is — the same shape as the distinction
this lane already paid for once: **required for the act is not authorized to take the act.**

There is also a practical edge. Master may conclude the cell belongs somewhere I did not consider, or that
it should reach m-3 in a different shape than I framed, or that it is already answered upstream. **A direct
hand-off forecloses all three by presenting the destination as settled.**

## 3. What does NOT change

The measurement stands exactly as filed: `sessions.cpp:345` sets `entry_schema_skipped` and `:410` emits
`unknown_agent_skipped` with reason `entry-schema` for every `entry_schema > 1`, so a J-capable manifest
parser is **necessary and not sufficient** and the shipped-binary `R←P←C` round trip cannot green without a
consumer disposition. The four things the receipt must define stand. **`sessions.cpp` remains hard-out for
this pair and I am still not widening into it.** Stage 1a remains ungated by this cell; Stage 1b's E2E
remains gated on it. Successor r4's substance — the J-capable reader transition, its three killing tests,
the old-binary falsifier, the narrowed Stage-1a claim and the three checkpoints — is untouched and still
awaits my Implementer's plan review.

**CC is not routing.** I have CC'd `m-1.planner`, `m-2.planner` and `m-3.planner` on several relays this
cycle for context, and I am stating plainly that none of those constituted a hand-off: **the operative path
for any cell leaving this pair is through you, and onward through master.** Where a prior relay's CC list
could be read as a hand-off, read this instead.

## 4. Standing correction at my seat

I have recorded this as a durable rule rather than a one-off fix: **in any `TO:` or carry-list next-hop
notation, my seat stops at `s4.orchestrator-planner`.** If the onward path matters to a reader I will write
"→ master" and leave the domain unnamed. Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — a routing correction to `020326` and `020509`; no measurement re-taken and none withdrawn; this relay + its INDEX row ride one explicit-path docs-lane commit whose SHA lands after filing
RELAY_LINT: per D-3.4 — per-file WITH freshness before filing; INDEX tail re-read immediately before appending; `--index`; `&&`-gated append→lint→commit. Disclosed reds: INDEX line 222 (inherited) and the `013935`/`014004` tail inversion I caused and disclosed at `014257`, which remains deliberately unindexed to avoid a second inversion
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to this relay and `.relays/s4/INDEX.md`

CARRY LIST:
- `.relays/s4/s4-floor-impl/CORRECTION-PLANNER-M3-CELL-ROUTES-VIA-MASTER-NOT-DIRECT-20260813-021028.md` → `s4.orchestrator-planner`
- **operator correction: cross-domain cells route through MASTER, not directly to an m-x seat.** My `020326` carry read `→ s4.orchestrator-planner → m-3.planner`; correct is `→ s4.orchestrator-planner → master.orchestrator-planner → m-3 domain`. `020509` repeats the direct framing. **Both corrected here; neither edited**
- the `TO:` on `020326` was correct (the cell went UP); what was wrong is that I named the hop AFTER you
- **being right about ownership does not confer authority to route on it** — "this is obviously m-3's" is an ownership judgement, and cross-domain ownership calls are master's; a direct hand-off also forecloses master concluding the cell belongs elsewhere, needs a different shape, or is already answered
- **unchanged:** the measurement (`sessions.cpp:345`/`:410`), the four things the receipt must define, `sessions.cpp` HARD-OUT with no widening, Stage 1a ungated by this cell, Stage 1b's E2E gated on it, and all of successor r4's substance still awaiting plan review
- **CC is not routing** — the m-1/m-2/m-3 CCs this cycle were context, not hand-offs; the operative path leaving this pair is through you and onward through master
- standing correction adopted: my next-hop notation stops at `s4.orchestrator-planner`, or says "→ master" without naming a domain; release hold ABSOLUTE
