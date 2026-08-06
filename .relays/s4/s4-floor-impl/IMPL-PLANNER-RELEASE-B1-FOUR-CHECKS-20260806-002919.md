## IMPL — B1 RELEASES: the master-granted C1 recapture discipline is folded as Amendment A3; execute the recapture under the FOUR CHECKS, prove the greens, scoped review, then the B1 PR; Tasks 4-11 unblock behind the recapture

ROLE: Planner
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: s4-floor-impl-2
PARENT_DISPATCH_ID: s4-floor-pair-plan-review-approve
RUN_ID: s4
TASK_ID: B1
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — sequencing on the live s4-floor-impl-2 dispatch under master's grant relayed at `002730`; the B1 PR then meets the standing Step-4 merge bar whose token is the operator's alone; the release hold is ABSOLUTE
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-C1-RECAPTURE-GRANTED-B1-RELEASES-FOUR-CHECKS-20260806-002730.md
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: s4.orchestrator-planner, operator
SUBJECT: RELEASE B1 — Amendment A3 folded (amended plan SHA f06b7459…); codex anchor recaptures to the reviewed f00fbde5… under the four-check ceremony; envelope blob lock recapture per A2 rides the same head; then greens → scoped review → PR

Master granted the C1 recapture rule WITH the re-verification obligation your provenance
concern earned (the A2 analogue could not carry alone — C1 attests non-perturbation over
a surface F-4 forbids us to perturb, so the attestation needs its mutation evidence).
Folded at this seat as **AMENDMENT A3** (`docs/sprints/2026-08-04-s4-step4/plans/2026-08-05-s4-floor-fold-plan.md`,
SHA at this filing `f06b7459…`), carrying the grant's operational text verbatim in
substance.

SCOPE_DIFF (delta over the A1/A2-widened universe; all prior rows unchanged and all-in):
- harness/bivharness/e3.py -> in for the _ADAPTER_SOURCE_ANCHORS codex literal ONLY, this head, under A3's four checks
SCOPE_DIFF_RESULT: all-in

Your release sequence on the B1 head:

1. ONE recapture commit carrying BOTH granted literals for this head: the A2 envelope
   blob entry → `561dccf0dbd8e374b975ba19e2dbd8ddad553e81` and the A3 codex anchor →
   `f00fbde5061fddb961f09148d51061490aacdf57b6eedd8b49ff9abd016d7e12`; nothing else
   anchor- or lock-side (the claude anchor and exit-map entry do NOT move — B1 changed
   neither).
2. The FOUR CHECKS in the scoped review of that commit: (1) diff = F's change + the one
   anchor literal, nothing else anchor-side; (2) re-derive codex.cpp's whole-file hash
   at the head and match the literal; (3) mutation-check each `153958` §4 read-side
   codex session literal — disposable local mutation, RED under the harness, reverted,
   recorded as mutation diff + failing assertion; (4) state class-scoped that the head's
   own diff touches none of those literals.
3. Prove green at the head: focused tripwire tests, the focused schema-lock test, FULL
   harness selftests, and the E2 selection.
4. Open the B1 PR (target `main`, base per the plan topology) — the FIRST Step-4
   merge-bar candidate; panel-at-SHA and the full bar govern from there; the three
   non-gating reviewer items ride to that panel as carried.
5. Tasks 4-11 UNBLOCK behind the recapture: seed `s4-floor/a-floor-core` off the B1
   head. Slice B2 inherits A3 on BOTH anchors, per-head, never batched.
6. Burden-report duty (A3): if the four-check ceremony proves burdensome, say so in
   your report — that is what re-opens the upstream re-anchoring item; we never absorb
   it silently.

No new token is needed or issued — the standing `s4-floor-impl-2` dispatch remains the
live authority; this relay is sequencing on it.

ACTIONS_GIT_REF: writes at this seat: the plan Amendment A3 text + this relay + its INDEX row, committed on the docs lane with explicit paths (SHA in the commit record); no product/test/harness/schema edit; no new token
FINAL_GIT_STATUS_SHORT: not a read-only phase report; disk evidence rides the docs-lane commit SHA in ACTIONS_GIT_REF

CARRY LIST:
- `.relays/s4/s4-floor-impl/IMPL-PLANNER-RELEASE-B1-FOUR-CHECKS-20260806-002919.md` → `s4-floor.implementer`
