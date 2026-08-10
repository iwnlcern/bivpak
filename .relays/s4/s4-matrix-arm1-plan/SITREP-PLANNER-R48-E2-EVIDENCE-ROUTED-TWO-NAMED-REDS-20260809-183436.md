## SITREP — R-4.8 carrier IMPLEMENTED (three commits at `29796bb`, delta exactly the ten paths, carrier evidence green on both platforms); criterion-1 aggregate blocked by TWO named environment reds, both lead-verified at the bytes; evidence disposition ROUTED UP — red 1 is the operator's ALREADY-RULED harness-e2 600 class (fix in flight via B2), red 2 recommended for acceptance conditional on a BASE-container negative control (requested in parallel, grants nothing)

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-matrix-arm1-r48-evidence-routing
PARENT_DISPATCH_ID: s4-matrix-arm1-r48-impl-r1-evidence-blocker
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-CARRIER-IMPLEMENTED-E2-BLOCKED-20260809-182853.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — accepting deviated E2 evidence for a production-risk candidate is above the pair; red 1 applies an EXISTING operator ruling (your affirmation suffices), red 2 needs your acceptance (the operator's native-Linux alternative stated); the pair self-waives nothing; publication remains a separate token; the release hold is ABSOLUTE
DESIGN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-09-s4-matrix-arm1-r48-packer-home-carrier-design.md
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/plans/2026-08-09-s4-matrix-arm1-r48-carrier-plan.md
FROM: s4-matrix.planner
TO: s4.orchestrator-planner
CC: operator, s4.orchestrator-reviewer, s4-matrix.implementer
SUBJECT: SITREP — carrier implemented and carrier-green; two named aggregate reds routed with lead byte-verification and a recommended disposition per red; one parallel negative control requested from the Implementer

## Implementation state (Implementer report `…182853`, key rows lead-verified)

- Branch `s4-matrix/r48-carrier@29796bbe3929429d2d959278053089c5f852e5e2`, exactly three
  task commits over BASE `6047ab03…`, clean, LOCAL (no push/PR/remote-CI/merge).
- **Lead-verified at my seat:** the branch delta is EXACTLY the ten dispatched paths
  (diff listed them, nothing else); the fence statement and excluded files are
  base-identical per the report; acceptance criteria 2-7 pass.
- Carrier evidence green everywhere: schema/capture/transport TDD (RED first, then
  GREEN), 15-case/310-assertion carrier filter on macOS, 13-case/279-assertion carrier
  focus on Ubuntu amd64, full macOS product row green (300.42s), tidy/purity/errno/
  hardening green in Docker.

## The two aggregate reds — lead-verified, both OUTSIDE the ten-path universe

**Red 1 — macOS `harness-e2` TIMEOUT at 180.06s.** Verified at my seat: `TIMEOUT 180` at
`harness/CMakeLists.txt:47` at BASE `6047ab03` AND on current `main` — the constant is
outside the dispatch universe, and this is the class the operator ALREADY RULED
(RECONCILE.md:578: harness-e2 TIMEOUT = 600, DURABLE) with the one-line fix riding B2's
single commit (`IMPL-PLANNER-B2-AMEND-E2-600-DISPATCH-IMPL-TOKEN-20260809-063737`), not
yet merged. The Implementer's direct diagnostic (~194s full run, the one internal-timing
scenario passing alone in 12.3s) matches B2's own evidence for that ruling (181.3s
all-pass vs the 180 budget). **Recommendation: ANSWERED-BY-EXISTING-RULING** — accept the
carrier's macOS aggregate with this row red-by-stale-constant, DISCLOSED; the row re-runs
green mechanically at any post-B2 head (publication/panel time). No carrier action; no
universe expansion; the constant stays B2's to change.

**Red 2 — Docker Desktop amd64-emulation: 5 product failures (`tests/test_probe.cpp`
spawn/reap/process-group) + 3 harness selftest failures (`test_e3_asserts.py`
rewrite/scandir races).** Verified at my seat by object ID: `tests/test_probe.cpp`,
`src/core/support/probe.cpp`, `src/core/support/probe.hpp`, and
`harness/selftest/test_e3_asserts.py` are ALL git-object-IDENTICAL between BASE and the
branch head. The floor's slice C set the precedent (disclosed Docker/Rosetta emulation
deltas with green narrow controls, accepted at condition 3). **Recommendation: accept
under that precedent CONDITIONAL on one negative control** — because object-ID equality
proves the CODE is unchanged but not that the FAILURES are emulation-caused (the five
probe cases run in the same `biv_tests` binary as the new carrier tests; a same-binary
timing interaction is the falsifiable alternative). The control: rerun the same container
recipe at BASE `6047ab03` WITHOUT the carrier commits and observe the SAME 5+3 failures.
Same-failures ⇒ the emulation class is measured, not inferred, and red 2 is acceptable
exactly like slice C's; different-failures ⇒ the carrier interacts and comes back to me
as a real finding.

**Parallel request to the Implementer (CC; grants nothing — verification-only, no
product edit, no publication, no acceptance implied):** run the BASE-container negative
control above and report the failure sets verbatim. This sharpens your disposition
whichever way it goes and costs one container run.

## The asks

1. **Red 1:** affirm ANSWERED-BY-EXISTING-RULING (operator's durable 600; fix rides B2;
   disclosed red at the pre-B2 BASE; mechanical re-run later).
2. **Red 2:** accept under the slice-C precedent conditional on the green negative
   control — or take the operator's alternative (an approved native Linux runtime run,
   the Implementer's option 2) if you or the operator prefer hardware truth over the
   controlled-emulation measurement.
3. On both dispositions + the control result, the Implementer files the Step-3.8
   completion report and the publication-token question comes to the operator; my
   rigorous-review duty at the head follows the normal path.

Carried unchanged: publication held (P5); Waves B/C/D F-fenced; zero-ref `capture_mode`
awaiting m-1; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: docs lane only — this routing relay + its INDEX row ride one explicit-path commit (SHA lands after filing); product and test paths were touched by no action at this seat; the carrier branch is untouched by me.
FINAL_GIT_STATUS_SHORT:
none — clean tree (matrix-seat paths; the shared checkout carries the Implementer's untracked review/blocker relays, preserved untouched)
Fresh at 20260809-183436 before this relay + INDEX write; this relay and the INDEX row are this seat's working-tree delta at commit time.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/SITREP-PLANNER-R48-E2-EVIDENCE-ROUTED-TWO-NAMED-REDS-20260809-183436.md` → TO `s4.orchestrator-planner`
- red 1 → ANSWERED-BY-EXISTING-RULING recommended (operator 600 durable, fix in flight via B2)
- red 2 → accept-conditional-on-negative-control recommended (slice-C precedent); control requested from the Implementer in parallel
- carrier branch `29796bb` → clean, local, carrier-green; completion report + publication token downstream of the disposition
