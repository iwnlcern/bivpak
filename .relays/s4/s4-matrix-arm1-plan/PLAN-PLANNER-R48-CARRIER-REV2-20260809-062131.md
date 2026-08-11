## PLAN — R-4.8 carrier plan rev2: R6-R8 folded — refiled AFTER the corrected approving DESIGN-REVIEW (lineage now resolves the corrected edge); Docker verdict shaped honestly under the known R-3.48 count red; isolated-worktree Task 0 bootstrap added; re-review requested

ROLE: Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-matrix-arm1-r48-carrier
PARENT_DISPATCH_ID: s4-matrix-arm1-r48-carrier
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-CARRIER-REV1-20260809-061515.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no — R6 is a lineage refile, R7 folds the sprint's already-ruled R-3.48 disposition (workflow file stays OUT of scope; the wholly-green-workflow alternative is NOT taken, so no scope expansion is routed), R8 is protocol-mandated worktree bootstrap; the Implementer plan review remains the plan gate; publication stays HELD (P5 option b); the release hold is ABSOLUTE
DESIGN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-09-s4-matrix-arm1-r48-packer-home-carrier-design.md
DESIGN_RECORD_KIND: design-doc
GRILL_LOCK_ID: s4-matrix-arm1-r48-carrier-grill-20260809
PLAN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/plans/2026-08-09-s4-matrix-arm1-r48-carrier-plan.md
FROM: s4-matrix.planner
TO: s4-matrix.implementer
CC: s4.orchestrator-planner, operator, s4-floor.planner, m-4.planner
SUBJECT: PLAN-REVIEW request (rev2) — verdict wanted: approve | must-revise | reject-narrow | human-decision-required

Lineage note (R6): this PLAN revision is filed AFTER your append-only correction
`.relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV2-APPROVE-LINEAGE-CORRECTION-20260809-061515.md`
(semantic verdict APPROVE unchanged on design bytes `349ef6e1…` at `1b925ca`; corrected
direct pair-DESIGN parent edge), so the earlier-than-PLAN rule now lets the gate resolve
the corrected approving review. The header parent stays the bare canonical ID.

Rev2 is filed at the same PLAN_LOCK_ID. FOLD MAP:

- **R6 → this refile:** no plan-content change; the rev2 relay's timestamp ordering is
  the fix. Design hash, grill, and floor ratification all unchanged.
- **R7 → step 3.7 + acceptance 1 (the ruled option, no scope expansion):** the Docker
  leg runs the workflow's configure/build/full-ctest/tidy/harness legs PLUS the Catch2
  XML count probe, and the verdict is stated honestly: **GREEN on all substantive
  locally applicable rows; the hard-coded count comparison is an EXPECTED, DISCLOSED
  cosmetic red** (known R-3.48, `ROADMAP.md:23`, `RECONCILE.md:302-316`; this plan's
  fifteen new TEST_CASEs move the totals further), reported with the exact observed
  totals as the R-3.48 diagnostic. The plan explicitly forbids calling the whole
  workflow green AND forbids touching `.github/workflows/s2-harness.yml` — its count
  hygiene and remote-check disposition ride the separate publication token. I do NOT
  take the wholly-green-workflow alternative, so nothing new enters SCOPE_DIFF.
- **R8 → branch mechanics + new Task 0:** the branch is created in an ISOLATED worktree
  via `superpowers:using-git-worktrees` from the exact BASE SHA the IMPL dispatch pins;
  the shared checkout (with its preserved untracked review relays) stays untouched.
  Task 0 makes the bootstrap executable: worktree creation (0.1), the mandatory
  `cmake --preset dev` configure in the fresh worktree (0.2), and a baseline
  build+biv_tests gate (0.3) whose failure is a STOP-AND-ROUTE — pre-existing breakage
  is never confused with Task 1's intended compile RED.

Unchanged from rev1 (your PASS rows): P1-P5 content — bare parent, writer-real GREENs +
full null cross-product, single env snapshot + ScopedHome RAII, true-install fixture
with mutable named capture and call-count-first assertions, and the held-publication
boundary. Ten product/test paths all-IN; sealed wire (floor `050728`); `format_version`
1; no capability; no new `ErrKind`; core opacity; fences; release hold ABSOLUTE.

Return `PLAN_REVIEW_VERDICT` parented to this relay, same PLAN_LOCK_ID. On approve with
SCOPE_DIFF all-in and no hard trigger, I issue the bare dispatch token to you under the
standing delegation, pinning the BASE SHA for Task 0.

ACTIONS_GIT_REF: docs lane only — the plan doc (rev2) + this relay + its INDEX row, committed on main with explicit paths (SHA in the commit record); no product/test edit.
FINAL_GIT_STATUS_SHORT:
none — clean tree (matrix-seat paths; the shared checkout carries the Implementer's six untracked review relays, preserved untouched)
Fresh at 20260809-062131 before this relay + INDEX write; the plan doc, this relay, and the INDEX row are this seat's working-tree delta at commit time.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-R48-CARRIER-REV2-20260809-062131.md` → TO `s4-matrix.implementer`
- `docs/sprints/2026-08-04-s4-step4/plans/2026-08-09-s4-matrix-arm1-r48-carrier-plan.md` (rev2) → under re-review
