## PLAN — rev3 narrow amendment folded per the orchestrator's T1 grant; delta concurrence requested (scoped to the amendment)

ROLE: Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-matrix-arm1-plan
PARENT_DISPATCH_ID: s4-matrix-arm1-plan-t1-probe-disposition
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-T1-RELOCATION-GRANTED-SEAL-MOVES-WITH-ITS-MACHINERY-20260806-014725.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no — the scope admission is granted at the authorized seat; this is the prescribed amendment + concurrence step; T1–T4 stay held until the corrected dispatch; the release hold is ABSOLUTE
DESIGN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-05-s4-matrix-arm1-design.md
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/plans/2026-08-06-s4-matrix-arm1-plan.md
FROM: s4-matrix.planner
TO: s4-matrix.implementer
CC: s4.orchestrator-planner, operator
SUBJECT: PLAN rev3 — your blocker's recommended disposition granted and folded exactly; concur on the delta and the corrected Wave-A dispatch follows

Your T1 blocker's recommended disposition was GRANTED at the orchestrator seat
(disposition `…T1-RELOCATION-GRANTED-…-20260806-014725`, provenance-checked: the seal is
a pair-era instrument, no master ruling) with the bounds you proposed plus one
bookkeeping obligation.
The plan is amended to rev3, narrowly:

1. **T1 Files** gains `tests/test_probe.cpp` — T1.5a's mechanical relocation ONLY; any
   other edit in that file is a NEW deviation, routed before an edit.
2. **New step T1.5a:** within the one test case "version probe has one traced readiness
   primitive": retarget the source-location anchors from `probe.cpp` to `subprocess.cpp`;
   STRENGTHEN the probe.cpp side to assert ZERO `::poll(`/`::select(`/`::ppoll(` anywhere
   in `probe.cpp`; add the successor-instrument sentence in the test comment (the
   orchestrator's bookkeeping obligation, verbatim in the plan): "the
   one-traced-readiness-primitive seal moved with its machinery from probe.cpp to
   subprocess.cpp; probe.cpp's half strengthened to zero-primitives."
3. **T1.6 bar reworded, both halves carried:** "ZERO BEHAVIORAL probe-contract edits"
   AND "probe.cpp asserts zero polling primitives"; the only permitted delta in
   `tests/test_probe.cpp` is T1.5a's anchors + successor note.
4. **T1 Acceptance** updated to match (successor-instrument sentence included).
Every other rev2 byte stands — no other task, wave, ledger row, or gate moved; the
Wave-A dispatch's SCOPE_DIFF row set will gain the one path on re-issue.

Concurrence request (per the disposition's prescribed process): a DELTA concurrence
scoped to this amendment — bare verdict line, `PHASE: PLAN-REVIEW`, parented to THIS
relay; the standing rev2 approve is not re-opened.
Grading surface: does rev3 implement the grant's bounds exactly (one test case, anchors
only, both bar halves, successor sentence), and does it change nothing else?

On your concurrence: I re-issue the corrected Wave-A dispatch parented per the standing
chain (fresh exact-file lint, SCOPE_DIFF all-in including the admitted path), and T1–T4
resume on the linear stack.

ACTIONS_GIT_REF: docs lane only — rev3 edits to the plan doc (changelog + T1 block), this relay, and its INDEX row, committed on main with explicit paths (SHA in the commit record); no product, test, harness, schema, or ledger edit.
FINAL_GIT_STATUS_SHORT: recorded in the lane-commit record for this filing — the shared tree carries sibling in-flight files; this seat claims only the three paths in ACTIONS_GIT_REF.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-REV3-AMENDMENT-20260806-015400.md` → TO `s4-matrix.implementer`
