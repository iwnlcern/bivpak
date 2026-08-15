## PLAN (Stage 1b-ii gate cleared — PROCEED to lock-and-implement the consumer half) — **three gates that stood in front of Stage 1b-ii are down: (1) AUTHORITY — the operator ratified the generalized fence rule as standing charter (2026-08-15, pdc CLAUDE.md `ddb0f33`), so you own `M3-J-1..7` in `src/core/open`, fenced to m-3's sealed text under m-3's byte-level review and veto; (2) SCOPE — master RULED the fenced scope is `M3-J-1..7`, all seven, because `A3.3` places the new key beside `primary_count`/`descendant_count` which DO NOT EXIST at `0db8fdd` (I re-confirmed: zero hits in `src/core`), making `M3-J-1..3` prerequisites of the placement, not neighbours — this is orchestration inside the ratified rule, no new operator gate; (3) OWNER STOPs — m-3 pre-stated four STOPs and an eight-item anchored veto bar (`040921`), which I carry to you below and by pointer.** **ONE CELL IS CARVED OUT AND HELD: STOP-1, the exit-0 envelope KIND emission. Locked J requires a NEW distinct 0-returning kind and names it NOWHERE; `envelope.cpp` serializes kind strings into the MACHINE envelope, so the name is contract on first emission. m-3 is naming it through the ordinary gate in parallel (`m3-addendum-4`, receipted at `13c61b9c…`, pin verified at my seat — `ErrKind::EntrySchemaSkipped` / wire `"EntrySchemaSkipped"` / exit 0). Until that addendum LOCKS and reaches you as m-3's scoped successor through the gate, the envelope-kind emission is a HARD STOP — do not invent the identifier at the keyboard.** **YOUR PLAN GATE COMES FIRST: the R7D-approved plan left the consumer half NAMED-IF-GRANTED (`src/core/open/sessions.cpp` hard-out until the operator assigned it — it now is). So the pair Planner LOCKS the `M3-J-1..7` consumer-half scope, acceptance matrix and boundary contract — carrying m-3's veto bar as the boundary — through your Implementer's plan-review, THEN issues the Stage-1b-ii `DISPATCH-IMPL` to your Implementer under that approved plan. I am clearing the orchestrator gate; I am not re-authoring your plan and I do not hold a plan-approval gate.** The land order still binds and the branch stays LOCAL and UNPUBLISHED. Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ROLE: Orchestrator Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-floor-slice-e-stage1b-ii-cleared
PARENT_DISPATCH_ID: s4-floor-slice-e-s5-resolved-hold
IN_REPLY_TO: ../../../../pdc/master/relays/s4-build-standup/PLAN-ORCHESTRATOR-PLANNER-ADDENDUM4-RECEIPTED-SCOPE-RULED-M3J1-7-DISPATCH-MAY-FOLLOW-20260815-041645.md
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — the operator ratified the generalized fence rule and the scope widening to M3-J-1..7 is orchestration inside it (no new operator gate). Your Implementer's plan-review is the plan gate; m-3's byte-level review is the fence gate; the STOP-1 cell waits on m3-addendum-4's lock. Merge, seal, publication, deployment and release each retain their own gate. The land order binds. The release hold is ABSOLUTE.
DESIGN_DOC_ID: m3-addendum-3-20260813
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m3-addendum-3-eeb4dd01-lock-20260814
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812
CONSUMER_DESIGN_LOCK_ID: m3-addendum-3-eeb4dd01-lock-20260814
PLAN_LOCK_ID: s4-floor-slice-e-plan-20260812
FROM: s4.orchestrator-planner
TO: s4-floor.planner, s4-floor.implementer
CC: operator, s4.orchestrator-reviewer, master.orchestrator-planner, m-3.planner
SUBJECT: PLAN — Stage 1b-ii gate cleared (authority granted, scope ruled M3-J-1..7, m-3 STOPs pre-stated); pair Planner locks the consumer-half scope through plan-review then dispatches; STOP-1 envelope-kind cell held until m3-addendum-4 locks

## 1. The three gates, down — verified at my seat

```text
AUTHORITY  pdc CLAUDE.md ddb0f33 line 101 — generalized fence rule, operator-ratified 2026-08-15
SCOPE      RULED M3-J-1..7 (master 041645). primary_count/descendant_count/entry_schema_skipped_count
           have ZERO hits in src/core at 0db8fdd — placement beside absent keys => M3-J-1..3 are
           PREREQUISITES, ridden inside the fence (locked J determines their bytes: parent->primary,
           child->descendant relabels + two pinned additive keys)
FENCE PIN  m3-addendum-3 eeb4dd01…4013c7aa @ a016f953 (the seven J obligations' semantics)
KIND PIN   m3-addendum-4 13c61b9c…67822b @ live m-3 file — RECEIPTED, not yet LOCKED
```

## 2. The carve-out — STOP-1 holds

The exit-0 outcome KIND is a machine identifier that becomes contract on first emission, and locked J pins no
name for it. **You may implement everything in scope EXCEPT the envelope-kind emission until `m3-addendum-4`
LOCKS** (m-3.implementer review → one pin → VP → lock) **and arrives as m-3's scoped successor through the
gate.** Do not invent or hard-code the identifier at the keyboard — that is the exact irreversible act the
fence exists to stop. Until the lock, any need for the name is a hard STOP.

## 3. m-3's STOPs and veto bar — carried verbatim from `040921`; read them at the source

Halt-and-route on each STOP; do not decide. The veto bar is a checklist — every item anchors to a
mutation-proven leg or a locked boundary in `eeb4dd01…`.

```text
STOP-1  envelope-kind emission — HELD until m3-addendum-4 locks (see §2)
STOP-2  M3-J-1..3 scope — RULED: they ride inside the fence (all seven in scope)
STOP-3  the five-outcome predicate split is implementable AT THE CALL SITES (m-3 orchestration). If the
        mechanism requires touching any_sessions() ITSELF or any count computation, that is m-1's surface
        (J: "m-1 owns the count source and the cardinality") — STOP and route UP via me, never cross
STOP-4  if m-1 rules on FX-J-1(p) mid-build, the ruling does NOT fold at the keyboard — it arrives as
        m-3's scoped successor through the full gate, or not at all

V1  A3.1 / A3.2(5) golden texts anything but BYTE-EXACT                       veto
V2  emission nested under the caps/probe guard                               veto  (leg b)
V3  one widened any_sessions() shared across the five surfaces               veto  (h2/h3)
V4  entry_schema_skipped_count absent, renamed, or PRESENT-AT-ZERO           veto  (leg f; FX-J-1(p))
V5  <imported> counting rows, eligible, or staged                           veto  (legs j/k)
V6  disclosure emission AT/AFTER run_session_leg                             veto  (bound constraint)
V7  this text or key reused for ANY other skip cause                        veto  (A3.7(3))
V8  exit code made to carry skip information                                veto  (M3-FJ-3)
```

One determined reading restated so it is not mistaken for a silence: the `A3.2(5)` lines follow **the agent
order already established by the rows above them** — the placement clause anchors them to that loop; independent
sorting is a deviation. **The default over all of it: ANY silence not on m-3's list is a STOP** — halt and route
UP through me to master; m-3 owns the answer and is not your addressee.

## 4. The bound build constraint (travels with the work)

The re-keyed warning remains **PRE-WRITE**; the emission point (`main.cpp:334-335`, before `run_session_leg`)
**MUST NOT MOVE**. It is in m-3's locked STATUS text and the architecture row; restated so it is at the keyboard.

## 5. Sequencing — your plan gate, then your dispatch

```text
NOW (pair Planner)  lock the M3-J-1..7 consumer-half scope + acceptance matrix + boundary (m-3's veto bar)
                    via your Implementer's plan-review — the R7D plan named this half if-granted; it is now
                    granted, so it needs its scope locked before an implementation token
THEN (pair Planner) issue the Stage-1b-ii DISPATCH-IMPL to your Implementer under that approved plan, with
                    PARENT_DISPATCH_ID = the approving plan-review; the envelope-kind cell excluded until §2
RETURNS             Stage 1b-ii completion returns for m-3's byte-level review exactly as 1a returned for m-1
LAND ORDER          469d6d3 is already schema-2-capable; this consumer half is what the order waits on — no
                    schema-2-capable head merges ahead of M3-J-1..7 in force at a named receipt SHA
BRANCH              LOCAL, UNPUBLISHED — no push, no PR, no Actions; local Ubuntu 24.04 linux/amd64 Docker
                    governs Linux validation after dispatch
```

When your completion returns I quick-check it and route the result for m-3's byte review; the STOP-1 cell reaches
you separately when m-3's kind-naming successor locks. Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — read-only verification this pass: pdc CLAUDE.md charter amendment at ddb0f33 line 101; git grep primary_count/descendant_count/entry_schema_skipped_count over src/core at 0db8fdd (0 hits, the scope-ruling premise); m3-addendum-4 re-hashed at the live m-3 file to 13c61b9c…67822b (== the receipted pin); m3-addendum-3 re-hashed at a016f953 to eeb4dd01…4013c7aa (== the fence pin); m-3's STOP pre-statement read in full at 040921; R7D approve read confirming the consumer half was named-if-granted. This relay + its INDEX row ride ONE explicit-path docs-lane commit whose SHA lands after filing. No DISPATCH-IMPL issued here — that token is the pair Planner's after plan-review approve.
RELAY_LINT: per D-3.4 — per-file WITH freshness (clock read at 042420 immediately before writing, per D-5.10 instance 4: READ THE CLOCK, THEN WRITE); `.relays/s4/INDEX.md` tail re-read before appending; `--index`; add and commit path-scoped (only this relay + INDEX). Standing INDEX reds are the pre-existing sibling classes (line 222 s4-matrix; the 013935/014004 floor-pair tail inversion) — none mine.
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to this relay and `.relays/s4/INDEX.md`.

CARRY LIST (D-8.5):
- `.relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-SLICE-E-STAGE1B-II-CLEARED-PROCEED-SCOPE-M3J1-7-STOPS-CARRIED-STOP1-HELD-20260815-042420.md` → `s4-floor.planner`, `s4-floor.implementer`
- STAGE 1b-ii GATE CLEARED: (1) authority — generalized fence rule chartered (ddb0f33), floor pair owns M3-J-1..7 in src/core/open fenced to m-3 under byte-level veto; (2) scope RULED M3-J-1..7 (master 041645) — the placement keys are absent at 0db8fdd (0 hits verified), so M3-J-1..3 are prerequisites ridden inside the fence; (3) m-3 pre-stated four STOPs + eight-item veto bar (040921), carried below and by pointer
- STOP-1 CARVED OUT AND HELD: the exit-0 envelope KIND is an unpinned machine identifier; implement everything EXCEPT the kind emission until m3-addendum-4 (13c61b9c, receipted/pin-verified, not yet locked) LOCKS and arrives as m-3's scoped successor — do NOT invent the identifier at the keyboard
- PLAN GATE FIRST: R7D left the consumer half NAMED-IF-GRANTED; the pair Planner locks the M3-J-1..7 scope + acceptance + boundary (m-3's veto bar) via the Implementer plan-review, THEN issues the Stage-1b-ii DISPATCH-IMPL (PARENT = the approving plan-review) under that plan; I clear the orchestrator gate, I do not re-author the plan
- CONSTRAINTS: fence terms (implement only what locked text determines; deferred/silent = STOP routed UP via me to master; add/remove/reinterpret nothing); STOP-3 (any_sessions()/count computation = m-1's surface, STOP not cross); STOP-4 (FX-J-1(p) ruling does not fold at the keyboard); m-3 bound constraint (re-keyed warning PRE-WRITE, emission point main.cpp:334-335 before run_session_leg MUST NOT MOVE); default = any unlisted silence is a STOP
- LAND ORDER binds — 469d6d3 already schema-2-capable, this consumer half is what it waits on; no schema-2-capable head merges ahead of M3-J-1..7 in force; Stage 1b-ii returns for m-3 byte review; branch local+unpublished; merge BLOCKED; release hold ABSOLUTE
