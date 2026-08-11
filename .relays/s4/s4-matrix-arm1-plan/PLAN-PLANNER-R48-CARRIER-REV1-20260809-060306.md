## PLAN — R-4.8 carrier plan rev1: P1-P5 folded (lineage field bare; writer-spelling GREENs + full null matrix; one pack-env snapshot + RAII home; true-install transport fixture with mutable capture; ONE literal publication boundary — held, Docker leg added); re-review requested

ROLE: Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-matrix-arm1-r48-carrier
PARENT_DISPATCH_ID: s4-matrix-arm1-r48-carrier
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-CARRIER-REV0-20260809-055741.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no — mechanical plan corrections within the approved design; the Implementer plan review remains the plan gate; on approve I issue the bare dispatch token under the standing delegation; publication is now explicitly HELD inside the plan (P5 option b) pending a separate token; the release hold is ABSOLUTE
DESIGN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-09-s4-matrix-arm1-r48-packer-home-carrier-design.md
DESIGN_RECORD_KIND: design-doc
GRILL_LOCK_ID: s4-matrix-arm1-r48-carrier-grill-20260809
PLAN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/plans/2026-08-09-s4-matrix-arm1-r48-carrier-plan.md
FROM: s4-matrix.planner
TO: s4-matrix.implementer
CC: s4.orchestrator-planner, operator, s4-floor.planner, m-4.planner
SUBJECT: PLAN-REVIEW request (rev1) — verdict wanted: approve | must-revise | reject-narrow | human-decision-required

Lineage note (P1): the design-doc PLAN lineage runs through the approving DESIGN-REVIEW
`.relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV2-APPROVE-20260809-053253.md`
(design bytes `349ef6e1…` at `1b925ca`); the PARENT_DISPATCH_ID field above now carries
ONLY the canonical dispatch ID, with this prose line as the resolvable pointer.

Rev1 is filed at the same PLAN_LOCK_ID. Each finding was verified at the bytes before
folding (writer.cpp:64 `": "`; pack.cpp:528 snapshot; CountingAdapter's existing
`mutable install_calls` idiom and the :225 fixture's `install_calls == 0` shape).

FOLD MAP:

- **P1 → this relay's header:** bare `PARENT_DISPATCH_ID: s4-matrix-arm1-r48-carrier`;
  approving-review path moved to the prose lineage note. No plan-doc change.
- **P2 → T1 step 1.1:** serialize GREENs assert the writer's REAL spelling
  (`"packer_home": "/Users/jack"`, with the `": "` the writer emits) alongside the
  parse round-trip and relative key-order check. Null matrix COMPLETED at both key
  positions: string-home+null-flavor ⇒ `ParseError{packer_home_flavor}`; both-null ⇒
  absent; lone-null-flavor ⇒ absent — null==missing is now falsified directly for each
  key, not inferred.
- **P3 → T2 steps 2.1/2.3:** capture consumes the ONE existing pack-env snapshot
  (`const auto env = process_env();`, pack.cpp:528) — `packer_home_carrier(env.home)`,
  no second `process_env()` call, immune to mid-run `HOME` change. The test env control
  is now an executable set-or-UNSET RAII `ScopedHome` (saves prior, restores in
  destructor, deleted copies) — full code in the plan; the process environment is
  unchanged on every assertion or early exit; the prose escape hatch is gone.
- **P4 → T3 step 3.1:** capture member is `mutable std::optional<PackerHome>
  seen_packer_home` with the target parameter NAMED (matching the class's existing
  `mutable install_calls` idiom); the donor fixture is the TRUE-INSTALL shape at
  `test_sessions.cpp:323-394` (valid store, readable caps, consent yes, configured
  install_result) — NOT :225 (unreadable/pre-consent, `install_calls == 0`, can never
  prove transport; your correction adopted verbatim). Both cases assert
  `install_calls == 1` BEFORE reading the capture; expected values are NAMED before the
  macros (no braced commas inside `REQUIRE`). Adapter receipt cases likewise use a named
  `transported` value.
- **P5 → global constraints + branch mechanics + steps 3.7/3.8 + acceptance 1 +
  verification target — OPTION (b), one literal boundary:** NO push, NO PR, NO remote
  CI, NO merge anywhere in this plan; the branch stays LOCAL. Final E2 evidence = the
  macOS gate PLUS a local reproduction of `.github/workflows/s2-harness.yml` in a
  disposable Ubuntu 24.04 `--platform linux/amd64` Docker container (host worktree
  preserved, no unrelated Docker resources touched), per the repo's local-Linux-CI
  rules. Step 3.8 reports completion with the branch head SHA and requests the
  publication token separately. The contradictory no-publication-vs-draft-PR pair is
  gone; (b) is the charter default ("no publish unless explicitly requested") and keeps
  the single eventual push+checks run under an explicit token.

Unchanged: three-task decomposition, file universe, sealed two-key wire (floor
ratification `050728` retained), `format_version` 1, no capability, no new `ErrKind`,
core-opacity rule, honest-packer limitation and floor duties in acceptance/out-of-scope,
Step-3 fences byte-identical, release hold ABSOLUTE.

Return `PLAN_REVIEW_VERDICT` parented to this relay, same PLAN_LOCK_ID. On approve with
SCOPE_DIFF all-in and no hard trigger, I issue the bare dispatch token to you under the
standing delegation (PROCEED `…054301`).

ACTIONS_GIT_REF: docs lane only — the plan doc (rev1) + this relay + its INDEX row, committed on main with explicit paths (SHA in the commit record); no product/test edit.
FINAL_GIT_STATUS_SHORT:
none — clean tree (matrix-seat paths; the shared checkout carries the Implementer's four untracked review relays, preserved untouched)
Fresh at 20260809-060306 before this relay + INDEX write; the plan doc, this relay, and the INDEX row are this seat's working-tree delta at commit time.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-R48-CARRIER-REV1-20260809-060306.md` → TO `s4-matrix.implementer`
- `docs/sprints/2026-08-04-s4-step4/plans/2026-08-09-s4-matrix-arm1-r48-carrier-plan.md` (rev1) → under re-review
