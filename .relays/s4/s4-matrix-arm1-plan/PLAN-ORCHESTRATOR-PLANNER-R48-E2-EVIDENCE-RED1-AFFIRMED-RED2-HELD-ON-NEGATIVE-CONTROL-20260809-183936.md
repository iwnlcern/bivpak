## DISPOSITION — R-4.8 carrier E2 evidence, two named reds. RED 1 (macOS harness-e2 TIMEOUT 180.06s): AFFIRMED ANSWERED-BY-EXISTING-RULING — I byte-verified the constant is `TIMEOUT 180` at the carrier BASE `6047ab0` AND on current `main` (B2's durable-600 fix unmerged), so this is exactly the operator's ruled class; accept the macOS aggregate with this row red-by-stale-constant, DISCLOSED; it re-runs green mechanically at any post-B2 head. RED 2 (Docker amd64-emulation 5 probe + 3 selftest failures): the negative-control requirement is CORRECT and ENDORSED — acceptance is HELD until the BASE-container control returns the SAME 5+3 failures (object-ID equality proves the code is unchanged, NOT that the failures are emulation-caused; the same-binary timing interaction is the falsifiable alternative). Option 2 (native-Linux run) remains the operator's alternative. No token; the release hold is ABSOLUTE.

ROLE: Orchestrator Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-matrix-arm1-r48-evidence-disp
PARENT_DISPATCH_ID: s4-matrix-arm1-r48-evidence-routing
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no at this relay — red 1 applies the operator's EXISTING durable-600 ruling (affirmation, not a new gate); red 2's acceptance is HELD on a falsifiable negative control (verification-only, grants nothing); publication remains a separate operator token; the release hold is ABSOLUTE
DESIGN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-09-s4-matrix-arm1-r48-packer-home-carrier-design.md
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/plans/2026-08-09-s4-matrix-arm1-r48-carrier-plan.md
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/SITREP-PLANNER-R48-E2-EVIDENCE-ROUTED-TWO-NAMED-REDS-20260809-183436.md
FROM: s4.orchestrator-planner
TO: s4-matrix.planner
CC: operator, s4.orchestrator-reviewer, s4-matrix.implementer
SUBJECT: DISPOSITION — red 1 answered-by-ruling (affirmed); red 2 acceptance held on the green negative control; carrier otherwise clean

## Red 1 — AFFIRMED: answered by the operator's existing durable-600 ruling

Verified at this seat: `set_tests_properties(harness-e2 PROPERTIES TIMEOUT 180)` holds at the carrier
BASE `6047ab0` AND on current `main` — the constant is stale on both because B2's one-line
`TIMEOUT 180 → 600` (the operator's ruled durable value, RECONCILE decision-of-record) rides B2's PR
#23 and has not yet merged. The macOS `harness-e2` 180.06s timeout is that exact class, outside the
carrier's ten-path universe. **Accept the carrier's macOS aggregate with this row red-by-stale-constant,
DISCLOSED**; it re-runs green mechanically at any post-B2 head (panel/publication time). No carrier
action, no universe expansion; the constant stays B2's to move.

## Red 2 — HELD on the negative control (endorsed), not yet accepted

Your reasoning is right and I am holding acceptance to it: object-ID equality of `tests/test_probe.cpp`,
`src/core/support/probe.{cpp,hpp}`, and `harness/selftest/test_e3_asserts.py` between BASE and the
branch proves the CODE is unchanged, but NOT that the 5 probe + 3 selftest failures are
emulation-caused — the five probe cases share the `biv_tests` binary with the new carrier tests, so a
same-binary timing/ordering interaction is a live, falsifiable alternative. **The BASE-container
negative control is the measurement that decides it.** I endorse the parallel control you requested from
the Implementer (verification-only, grants nothing, no product edit):
- **same 5+3 failures at BASE `6047ab0` without the carrier commits ⇒** the emulation class is MEASURED,
  not inferred, and red 2 is acceptable exactly under the slice-C disclosed-emulation precedent. On that
  result I confirm acceptance.
- **different failures ⇒** the carrier interacts; it is a REAL finding and comes back to the pair.

Until the control returns, red 2 is NOT accepted and the carrier is NOT evidence-complete. The operator's
option 2 (an approved native-Linux runtime run — hardware truth over the controlled-emulation
measurement) remains available if you or the operator prefer it; either path closes red 2.

## Carrier otherwise
The implementation is clean and carrier-green as reported (three commits at `29796bb`, delta exactly the
ten dispatched paths, schema/capture/transport TDD RED→GREEN, macOS + Ubuntu carrier focus green, full
macOS product row green, tidy/purity/errno/hardening green). Acceptance criteria 2-7 pass per your
lead verification. On BOTH reds closed (red 1 affirmed + red 2 control green, or the native-Linux run),
the Implementer files the Step-3.8 completion report, my rigorous-review duty at the head follows, and
the publication-token question goes to the operator.

Carried unchanged: R-4.8 (this carrier + the floor's home-prefix needle land together, hard-gated before
any release); publication held (P5); the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — read-only byte verification (harness/CMakeLists.txt TIMEOUT 180 at 6047ab0 and main). This relay + its INDEX row ride one explicit-path docs-lane commit whose SHA lands after filing.
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to this relay + .relays/s4/INDEX.md.

CARRY LIST:
- `.relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-R48-E2-EVIDENCE-RED1-AFFIRMED-RED2-HELD-ON-NEGATIVE-CONTROL-20260809-183936.md` → `s4-matrix.planner`
- red 1 → AFFIRMED answered-by-existing-ruling (operator's durable 600; stale at BASE+main, verified; disclosed; mechanical re-run post-B2)
- red 2 → acceptance HELD on the BASE-container negative control (same 5+3 ⇒ accept under slice-C precedent; different ⇒ real finding); native-Linux run the operator's alternative
- carrier `29796bb` clean/carrier-green; completion report + rigorous review + publication token downstream of BOTH reds closing
