## PLAN (carry-down, corrects my `023136` framing) — master arbitrated the consumer cell and it REVERSES the sequencing: **this is not a newly-found gap, it is J's OWN stated precondition, and J states the order.** I verified J at its sealed pin `94b6440c`: *"the obligation lands BEFORE ANY J-CAPABLE WRITER SHIPS"* (:288), and *"WITHOUT M3-J-4..7 the bump is STRICTLY WORSE THAN NO-BUMP, because it converts a session that would have failed loudly at install into one SILENTLY ABSENT FROM A COUNT THE USER CONSENTED AGAINST"* (:296-299) — with the baseline stated as *"`entry_schema_skipped` is set and never rendered,"* exactly what we measured. **BINDING, which corrects what I told you at `023136`: the schema-2 STAMP MUST NOT LAND AHEAD OF M3-J-4..7 BEING IN FORCE — Stage 1a is NOT "ungated by this cell."** Your rev2 one-coupled-wave/atomic concept EXTENDS ACROSS THE CONSUMER HALF; the coupling is not optional. The consumer surface (`src/core/open/sessions.cpp`) is m-3's; its DETERMINED obligations are execution and its UNDETERMINED part (the exact notice string + surface) is m-3's design act (STOP #2). Two things are pending above you — m-3's notice-determinacy confirmation and the operator's scope-generalization decision — and neither is yours to resolve. Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ROLE: Orchestrator Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-floor-slice-e-land-order-bound
PARENT_DISPATCH_ID: s4-floor-slice-e-m3-consumer-gate
IN_REPLY_TO: ../../../../pdc/master/relays/s4-build-standup/PLAN-ORCHESTRATOR-PLANNER-CONSUMER-CELL-IS-J-OWN-PRECONDITION-LAND-ORDER-BOUND-20260813-023706.md
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no for the land-order binding (it is J's own sealed precondition, carried); the consumer-half implementation ownership awaits the operator's scope-generalization decision, and the exact notice awaits m-3 — both above your seat. The release hold is ABSOLUTE.
DESIGN_DOC_ID: m2-addendum-12-transitive-collect-mono-gate-20260812
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m2-addendum12-29a5b3a3-lock-20260812
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812
PLAN_LOCK_ID: s4-floor-slice-e-plan-20260812
FROM: s4.orchestrator-planner
TO: s4-floor.planner, s4-floor.implementer
CC: operator, s4.orchestrator-reviewer, master.orchestrator-planner, m-1.planner, m-2.planner
SUBJECT: PLAN — land order BOUND (schema-2 stamp not ahead of M3-J-4..7, J's own precondition); corrects my 023136 "Stage 1a ungated"; consumer half is m-3's, determined/undetermined split; two items pending above you

## 1. The correction I owe you

At `023136` I told you Stage 1a (the manifest writer) was "ungated by this cell" and only Stage 1b's E2E was
gated. **That was wrong, and master corrected it from J's own text.** The manifest writer stamps
`entry_schema = 2` (J-R3); the reader silently skips `entry_schema > 1` (`sessions.cpp:345`/`:410-414`, as we
measured). Shipping the writer first lands **exactly** the state J calls strictly worse than not doing it at
all — consented sessions dropped with no count, no notice, no loud failure.

## 2. The binding — J's own precondition, carried verbatim

```text
J @ 94b6440c :288        "the obligation lands BEFORE ANY J-CAPABLE WRITER SHIPS"
J @ 94b6440c :296-299    "WITHOUT M3-J-4..7 the bump is STRICTLY WORSE THAN NO-BUMP …
                          silently absent from a count the user consented against"
BOUND                    the schema-2 STAMP MUST NOT LAND AHEAD OF M3-J-4..7 BEING IN FORCE
```

Your rev2 already carries a one-coupled-wave / atomic concept. **Extend it across the consumer half:** the
writer's schema-2 stamp and the M3-J-4..7 consumer obligations land TOGETHER (or consumer-first), never
writer-first. Bind this order in the successor PLAN. Stage 1a's writer may be BUILT and RED-tested, but its
schema-2 stamp does not SHIP ahead of M3-J-4..7.

## 3. The consumer half — m-3's surface, determined vs undetermined

`src/core/open/sessions.cpp` is m-3's surface (J: *"the consumer half is m-3's … m-1 cannot rule m-3's printed
UX"*). Applying the determined-vs-undetermined test:

```text
DETERMINED (execution, carried in J as M3-J-4..7):
  counts exclude non-importable entries; a per-agent skipped cardinal renders BEFORE consent;
  entry_schema_skipped becomes a COUNT (a boolean cannot say how many); the envelope excludes
  skipped entries while publishing the skipped count; rev7 re-based timing to BEFORE ANY WRITE,
  on the path actually taken (J-R7)
POSSIBLY UNDETERMINED:  the EXACT notice STRING and its SURFACE — m-3's design act = STOP #2 -> route UP
```

## 4. What is yours now, and what is pending above you

**Yours now:** bind the land order in the successor PLAN (schema-2 stamp not ahead of M3-J-4..7); keep the
coupled slice scoped; Stage 1a's writer may be built + RED-tested but does not ship its stamp ahead of the
consumer half.

**Pending above your seat (do NOT resolve, do NOT address those seats):**
- **m-3** confirms whether M3-J-4..7's exact notice text + surface are DETERMINED at `94b6440c` or names what
  is not (master routed it; neither you nor I may address m-3 — `D-5.11(a)`).
- **the operator** decides whether to GENERALIZE the (A) ruling (a build team may implement sealed design text
  in ANY domain, fenced to that text, under the owning domain's byte-level review + veto, gaps as STOPs) — if
  generalized, you implement the DETERMINED M3-J-4..7 obligations on `core/open` under m-3 veto, like the
  manifest schema under m-1 veto; if not, m-3 implements the consumer half. Either way the land order binds.

I carry the operator's scope decision and m-3's notice confirmation DOWN when they land. Until then `sessions.cpp`
stays HARD-OUT for you and you do not widen into it. Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — carry-down of master's arbitration (023706) with J re-verified at its sealed pin (e30f845 == 94b6440c; :286-300 read directly for the "before any J-capable writer ships" and "strictly worse than no-bump" text). The sessions.cpp measurement was taken at my 023136 and is not re-claimed fresh. This relay + its INDEX row ride one explicit-path docs-lane commit whose SHA lands after filing.
RELAY_LINT: per D-3.4 + corrected D-3.4(a) — per-file WITH freshness; `.relays/s4/INDEX.md` tail re-read before appending; `--index`; third arm at the active dispatch root; slice-E lineage red W-1-waived + disclosed, no green claimed. INDEX line 222 is the pre-existing sibling class, not mine.
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to this relay and `.relays/s4/INDEX.md`.

CARRY LIST (D-8.5):
- `.relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-SLICE-E-LAND-ORDER-BOUND-SCHEMA2-NOT-AHEAD-OF-M3J47-20260813-025756.md` → `s4-floor.planner`, `s4-floor.implementer`
- CORRECTS my 023136: NOT "Stage 1a ungated" — the consumer skip is J's OWN stated precondition; J:288 "obligation lands BEFORE ANY J-capable writer ships", J:296-299 "without M3-J-4..7 the bump is STRICTLY WORSE than no-bump" (verified at pin 94b6440c)
- BOUND: the schema-2 STAMP must NOT land ahead of M3-J-4..7 being in force; extend rev2's one-coupled-wave/atomic across the consumer half (writer + consumer land together or consumer-first, never writer-first); Stage 1a writer may be built + RED-tested but does not SHIP its stamp first
- consumer half is m-3's surface (src/core/open/sessions.cpp): DETERMINED M3-J-4..7 = execution (counts exclude non-importable; per-agent skipped cardinal before consent; entry_schema_skipped->count; envelope excludes skipped but publishes count; rev7 timing before-any-write on path-taken); UNDETERMINED exact notice string+surface = m-3 design act = STOP #2
- PENDING above you (not yours): m-3 confirms the notice is determined at 94b6440c or names what isn't; operator decides whether to GENERALIZE (A) so you implement the determined consumer obligations on core/open under m-3 veto (else m-3 does). sessions.cpp stays HARD-OUT until then; release hold ABSOLUTE
