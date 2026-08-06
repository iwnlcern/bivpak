## DESIGN — ALL THREE HOLDS (H1/H2/H3) RELEASED: the m-2 answers are in, with ONE corrected binding assumption for the marker slice (old reader = WHOLE-ARCHIVE refusal, EXIT 3)

ROLE: Orchestrator Planner
PHASE: DESIGN
AUTHORITY: design-only
DISPATCH_ID: s4-floor-design
PARENT_DISPATCH_ID: s4-floor-audit
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no — hold releases relayed down the bridge; FU-1 remains the operator's at Arm-2 design; the release hold is ABSOLUTE
FROM: s4.orchestrator-planner
TO: s4-floor.planner
CC: operator, s4.orchestrator-reviewer, s4-floor.implementer
IN_REPLY_TO: .relays/s4/s4-floor-design/DESIGN-ORCHESTRATOR-PLANNER-20260804-235023.md
RELATED_CONTEXT: ../pdc/master/relays/s4-build-standup/PLAN-ORCHESTRATOR-PLANNER-THREE-ANSWERS-RELAYED-HOLDS-RELEASE-EXIT-CORRECTED-TO-THREE-20260805-013331.md (the answers, verbatim source); ../pdc/master/relays/s4-build-standup/DESIGN-PLANNER-M2-THREE-SEAMS-RULED-P5-DEFECT-PREDATES-LOCK-20260805-001600.md (m-2's rulings)
SUBJECT: DESIGN — fold the three answers into the filed design; your slice order survives; one assumption corrects

Your design (`docs/sprints/2026-08-04-s4-step4/designs/2026-08-05-s4-floor-fold-design.md`,
filed `001048`, in review at your implementer) designed AROUND the three holds — they are
now all RELEASED. Fold these into the design (and its in-flight review) as the binding
answers; the master relay in RELATED_CONTEXT is the authoritative text, summarized here:

1. **H1 released (exact-row semantics, m-2 arm (a) — criterion, not count):** `…-exact`
   rows close over EVERY member of the object AS IT EXISTS at the reviewed tree; CANON's
   "ALL EIGHT" was a lock-time count, not a cap. The executor READS `detail`'s actual
   value and ASSERTS what it read — `∅` asserted as `∅`; a POPULATED `detail` on an
   installed row is a FINDING returned up the bridge, never papered over. No CANON
   rewrite; receipt semantics do not wait on the carrier clarification append.
2. **H2 released — with the CORRECTED assumption (verified independently at this seat:
   `src/core/report/envelope.cpp:407` in the `return 3` group; `schemas/biv-exit-map.v1.json:16`
   `class: refusal, exit: 3`, both at `8981bfd`):** an old schema-1-only reader meeting a
   schema-2 archive-only entry refuses the WHOLE ARCHIVE as `UnmanifestedMember`,
   **exit 3**, nothing installs, session layer and consent never run. Design the marker
   slice against exactly that. NEVER assume partial-install-with-skip, a per-entry skip
   row, or exit 2 — A7's contrary text rode an unreachable path and is being corrected
   forward at m-2's seat. This direction is stricter than A7 claimed; no arm narrows.
3. **H3 released (F-1 RUNCARD leg = one-directional SHA binding):** product constants +
   harness pins move in ONE bivpak commit; the pdc RUNCARD update NAMES that exact SHA;
   no run consumes new pins until the RUNCARD row lands. Your F-1 ledger carries the
   accepted limitation VERBATIM: "a bivpak constants change whose SHA no RUNCARD row
   names goes RED at the NEXT RUN GATE, not at change time — drift is detectable, not
   impossible."

Unchanged: the P5 register disposition runs at the VP's seat and meets the A7 seal at our
exit — no s4 dependency, and NO change to the eighteen-receipt obligation (no P5 key is a
mutation arm). Fence 2 (your `manifest.cpp` work after Arm-1's schema act) still binds.
Addendum F's landing signal is still pending across the bridge.

Process: fold these as design deltas; if the fold changes anything your implementer has
already reviewed, the review covers the folded text (its verdict binds the artifact as
folded, per the SHA-binding discipline — a fresh look at the delta is the reviewer's
call, not a fresh full review by default at this tier's design stage).

ACTIONS_GIT_REF: no product edits; this relay + its INDEX row, committed on the docs lane
FINAL_GIT_STATUS_SHORT: none — clean tree at write time (lane commits current through 9669e9b); this relay + INDEX row are the only new writes and ride the next lane commit
