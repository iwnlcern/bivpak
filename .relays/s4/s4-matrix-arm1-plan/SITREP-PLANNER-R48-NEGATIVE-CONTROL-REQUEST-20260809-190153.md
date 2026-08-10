## SITREP — directed request: run the BASE-container negative control for red 2 (endorsed by the orchestrator disposition `…183936`); verification-only, no product edit, no publication, no acceptance implied

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-matrix-arm1-r48-neg-control
PARENT_DISPATCH_ID: s4-matrix-arm1-r48-evidence-disp
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-R48-E2-EVIDENCE-RED1-AFFIRMED-RED2-HELD-ON-NEGATIVE-CONTROL-20260809-183936.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — a verification-only measurement the orchestrator disposition explicitly endorsed and holds red 2's acceptance ON; it grants no implementation, publication, remote-CI, merge, or release authority and implies no acceptance; the release hold is ABSOLUTE
DESIGN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-09-s4-matrix-arm1-r48-packer-home-carrier-design.md
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/plans/2026-08-09-s4-matrix-arm1-r48-carrier-plan.md
FROM: s4-matrix.planner
TO: s4-matrix.implementer
CC: s4.orchestrator-planner, operator
SUBJECT: SITREP — run the red-2 BASE-container negative control and report the failure sets verbatim; this relay is the directed TO-line request the CC lines could not be

The orchestrator's disposition (`…183936`) affirmed red 1 (answered by the operator's
durable-600 ruling; the macOS aggregate is accepted with that row red-by-stale-constant,
disclosed) and HELD red 2's acceptance on exactly one measurement — the negative control
my routing relay sketched and the disposition endorsed. My earlier request rode a CC
line; per your own addressing discipline this relay is the directed request TO you.

THE CONTROL (verification-only; nothing else):

- Rebuild the SAME disposable Ubuntu 24.04 `--platform linux/amd64` container recipe you
  used for the branch run (same LLVM assets, same pinned Python lock, same non-root
  runner, host worktree mounted read-only/copied), but at **BASE
  `6047ab0311491da5567c99f32b22ff14433fb1d2` WITHOUT the three carrier commits**.
- Run the same suites that produced the red rows (`biv_tests` product row + harness
  selftests; the rest of the legs need not repeat).
- Report VERBATIM the failing case names and counts, side-by-side with the branch run's
  5 product + 3 selftest failures.

Decision rule (the disposition's, restated): SAME 5+3 failures at BASE ⇒ the emulation
class is MEASURED and red 2 is accepted under the slice-C precedent — you then file the
Step-3.8 completion report (both evidence legs + the publication-token request), and my
rigorous-review duty at the head follows. DIFFERENT failures ⇒ a real carrier
interaction; it comes back to me as a finding, not to the acceptance lane. Dispose of
the container afterward; touch no unrelated Docker resources; the branch stays LOCAL and
untouched either way.

Carried unchanged: red 1 disposed; publication held (P5, separate operator token);
Waves B/C/D F-fenced; zero-ref `capture_mode` awaiting m-1; the release hold is
ABSOLUTE.

ACTIONS_GIT_REF: docs lane only — this relay + its INDEX row ride one explicit-path commit (SHA lands after filing); product and test paths were touched by no action at this seat.
FINAL_GIT_STATUS_SHORT:
none — clean tree (matrix-seat paths; the shared checkout carries sibling-seat untracked relays, preserved untouched)
Fresh at 20260809-190153 before this relay + INDEX write; this relay and the INDEX row are this seat's working-tree delta at commit time.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/SITREP-PLANNER-R48-NEGATIVE-CONTROL-REQUEST-20260809-190153.md` → TO `s4-matrix.implementer`
- the control → BASE-container rerun of the red suites at 6047ab03, failure sets verbatim; same 5+3 ⇒ accepted + Step-3.8 report; different ⇒ finding back to the Planner
