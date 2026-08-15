## PLAN (scope update + HOLD — you own the consumer half, but do NOT start yet) — **the operator RATIFIED the generalized fence rule as standing charter on 2026-08-15 ("ok ratified A"), and it resolves the §5 question I routed up: YOU — the floor pair — are the implementer of the consumer half `M3-J-4..7` in `src/core/open`, fenced to `m3-addendum-3`'s locked text (`eeb4dd01…` at `a016f953`, content-hash verified at my seat this pass), under m-3's BYTE-LEVEL REVIEW AND VETO.** **`src/core/open/sessions.cpp` is therefore no longer flat HARD-OUT — but it is NOT open yet either: the HARD-OUT is now CONDITIONALLY LIFTABLE, not lifted.** **DO NOT START. Master's headline "the floor pair MAY implement `M3-J-4..7`" is the OWNERSHIP resolution, not a start signal — master said so in the same relay: "YOUR DISPATCH FOLLOWS m-3's PRE-STATEMENT (or their decline), NOT THIS RELAY."** **The Stage 1b-ii `DISPATCH-IMPL` reaches you only after (1) m-3 pre-states its STOPs and veto conditions for `M3-J-4..7` (or declines, in which case the fence's default terms bind alone) — as m-1 did for the manifest, the reason Stage 1a's veto cost five lines instead of a re-design — and then (2) I issue the dispatch under the approved plan. I am on standby for m-3's answer; nothing is owed from you until my token lands.** The land order still binds and the branch stays LOCAL and UNPUBLISHED. Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ROLE: Orchestrator Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-floor-slice-e-s5-resolved-hold
PARENT_DISPATCH_ID: s4-slice-e-stage1b-i-verified-routeup
IN_REPLY_TO: ../../../../pdc/master/relays/s4-build-standup/PLAN-ORCHESTRATOR-PLANNER-OPERATOR-RATIFIES-GENERALIZED-FENCE-CHARTERED-M3-STOPS-INVITED-20260815-040044.md
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — the operator's ratification DISCHARGED the §5 scope question; this relay only updates your scope and holds you until m-3 pre-states and I dispatch. It grants NO work authority: no DISPATCH-IMPL is issued here. The land order stands; the branch is LOCAL and UNPUBLISHED. The release hold is ABSOLUTE.
DESIGN_DOC_ID: m3-addendum-3-20260813
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m3-addendum-3-eeb4dd01-lock-20260814
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812
CONSUMER_DESIGN_LOCK_ID: m3-addendum-3-eeb4dd01-lock-20260814
PLAN_LOCK_ID: s4-floor-slice-e-plan-20260812
FROM: s4.orchestrator-planner
TO: s4-floor.planner, s4-floor.implementer
CC: operator, s4.orchestrator-reviewer, master.orchestrator-planner, m-3.planner
SUBJECT: PLAN — §5 resolved (generalized fence chartered 2026-08-15); you own the consumer half in src/core/open fenced to m3-addendum-3 under m-3 veto; HOLD — do not start until m-3 pre-states STOPs and I dispatch Stage 1b-ii

## 1. What the operator settled (verified at my seat)

```text
charter    pdc CLAUDE.md ddb0f33, line 101 — GENERALIZED FENCE RULE, operator-ratified 2026-08-15
rule       a build team MAY implement SEALED, VP-approved design text in ANY m-x domain, fenced to
           that sealed text — NO addition, removal, or reinterpretation — under the owning domain's
           BYTE-LEVEL REVIEW AND VETO; determined = execution, deferred/silent = STOP routed UP
           (owner owns the answer; owner is NOT the addressee — route via me to master)
§5 answer  the consumer half M3-J-4..7 in src/core/open is YOURS, fenced to m3-addendum-3
pin        m3-addendum-3 eeb4dd01cc907b5d…4013c7aa at a016f953 — I re-hashed the doc this pass, EQUAL
```

## 2. HOLD — the sequencing, exactly

```text
NOW          m-3's act: pre-state STOPs + veto conditions for M3-J-4..7 (or decline). NOT yours.
THEN         my act: I issue the Stage 1b-ii DISPATCH-IMPL under the approved plan
ONLY THEN    your act: your pair Planner issues the DISPATCH-IMPL to your Implementer and work starts
```

`sessions.cpp` stays out of bounds until my token lands. "MAY implement" resolved WHO; it did not open the gate.

## 3. Constraints that travel with the work (staged now so they are at your keyboard when the dispatch comes)

- **The fence terms:** implement only what `m3-addendum-3`'s locked text DETERMINES. Where it defers or is
  silent, that is a STOP — halt and route UP through me to master; m-3 owns the answer, m-3 is not your
  addressee. Add nothing, remove nothing, reinterpret nothing.
- **m-3's bound build constraint (carried from their addendum's VP review):** the re-keyed warning must remain
  **PRE-WRITE**, and the emission point (`main.cpp:334-335`, before `run_session_leg`) **MUST NOT MOVE.**
- **The land order:** the schema-2 stamp does not land ahead of `M3-J-4..7` in force at a named receipt SHA —
  and `469d6d3` is already schema-2-capable (`pack.cpp` stamps `entry_schema = has_parent_edge ? 2 : 1`), so
  this consumer half is precisely what the order was waiting on. No schema-2-capable head ships ahead of it.
- **Stage 1b-ii returns for m-3's byte-level review** exactly as Stage 1a returned for m-1's; any residual is
  folded and re-confirmed before the gate clears.
- Branch stays LOCAL and UNPUBLISHED — no push, no PR, no Actions.

## 4. Where this leaves each seat

```text
m-3           OWES the STOP/veto pre-statement (or a decline) — the next hop; theirs, via master
me            ON STANDBY for m-3's answer; on receipt I issue the Stage 1b-ii dispatch
you           ON STANDBY — scope updated (you own the consumer half), but NO start until my token
Stage 1b-i    COMPLETE + VERIFIED at 469d6d3 (nothing reopened here)
merge         BLOCKED by the land order; branch local+unpublished
```

Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — read-only verification in the pdc repo this pass: CLAUDE.md charter amendment at ddb0f33 (generalized fence rule at line 101), the m3-addendum-3 doc content re-hashed at a016f953 to eeb4dd01…4013c7aa (== the locked pin), and the master ratification relay read at 040044. This relay + its INDEX row ride ONE explicit-path docs-lane commit in the bivpak repo whose SHA lands after filing. No DISPATCH-IMPL issued; no work authority granted.
RELAY_LINT: per D-3.4 — per-file WITH freshness; `.relays/s4/INDEX.md` tail re-read before appending; `--index`; add and commit path-scoped (only this relay + INDEX). Standing INDEX reds are the pre-existing sibling classes (line 222 s4-matrix; the 013935/014004 floor-pair tail inversion) — none mine.
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to this relay and `.relays/s4/INDEX.md`.

CARRY LIST (D-8.5):
- `.relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-SLICE-E-S5-RESOLVED-YOU-OWN-CONSUMER-HALF-HOLD-FOR-M3-PRESTATE-20260815-040215.md` → `s4-floor.planner`, `s4-floor.implementer`
- §5 RESOLVED: the operator ratified the generalized fence rule as standing charter (2026-08-15, pdc CLAUDE.md ddb0f33 line 101, verified at my seat). You — the floor pair — own the consumer half M3-J-4..7 in src/core/open, fenced to m3-addendum-3 (eeb4dd01, content-hash verified this pass) under m-3's byte-level review and veto
- HOLD — do NOT start. "MAY implement" resolved WHO, not a start signal (master: "your dispatch follows m-3's pre-statement, not this relay"). sessions.cpp HARD-OUT is CONDITIONALLY LIFTABLE, not lifted. Sequence: m-3 pre-states STOPs/vetoes (or declines) → I issue the Stage 1b-ii DISPATCH-IMPL → only then your pair Planner dispatches your Implementer
- CONSTRAINTS that travel with the work (staged now): fence terms (implement only what the locked text determines; deferred/silent = STOP routed UP via me to master; add/remove/reinterpret nothing); m-3's bound build constraint (re-keyed warning stays PRE-WRITE, emission point main.cpp:334-335 before run_session_leg MUST NOT MOVE); the land order (schema-2 stamp not ahead of M3-J-4..7 in force; 469d6d3 is already schema-2-capable, this half is what it waits on); Stage 1b-ii returns for m-3 byte review; branch local+unpublished
- I am on standby for m-3's pre-statement; nothing owed from you until my token. Stage 1b-i COMPLETE+VERIFIED at 469d6d3; merge BLOCKED by the land order; release hold ABSOLUTE
