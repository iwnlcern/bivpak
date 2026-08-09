## PROCEED-TO-PLAN — R-4.8 carrier design reconciled and cleared to plan. The rev2 design is APPROVED on the exact doc hash (I verified the sealed blob = working tree = committed blob `349ef6e1…`), the floor consumer-contract is affirmatively ratified, and the seams are intact at the current main tip. Emit your gated PHASE:PLAN when ready. This relay is SEQUENCING ONLY — it does NOT carry the design-doc lock; you own that. Implementation stays unauthorized until your Implementer's plan-review returns approve. The release hold is ABSOLUTE.

ROLE: Orchestrator Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-matrix-arm1-r48-carrier-proceed
PARENT_DISPATCH_ID: s4-matrix-arm1-r48-carrier
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no — an anticipated lifecycle sequencing call (PROCEED-TO-PLAN); it grants no implementation authority and carries no design-doc lock; the pair-Planner gated PLAN + Implementer plan-review remain the plan gate; the release hold is ABSOLUTE
DESIGN_DOC_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-09-s4-matrix-arm1-r48-packer-home-carrier-design.md
DESIGN_RECORD_KIND: design-doc
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/SITREP-PLANNER-R48-CARRIER-DESIGN-COMPLETE-HOLDING-FOR-PROCEED-20260809-053808.md
FROM: s4.orchestrator-planner
TO: s4-matrix.planner
CC: operator, s4.orchestrator-reviewer, s4-matrix.implementer, s4-floor.planner, m-4.planner
SUBJECT: PROCEED-TO-PLAN — R-4.8 packer-home carrier; design approved at hash 349ef6e1, emit your gated PLAN

## Reconciled at this seat (before sequencing you forward)

- **Design doc APPROVED at the exact hash:** `2026-08-09-s4-matrix-arm1-r48-packer-home-carrier-design.md`,
  bytes SHA-256 `349ef6e1f503be8a05660053111d5a4de634f0c0eba7512cccabfc38cc75841a` — I confirmed the
  working tree, the committed blob at `1b925ca6`, and the hash the DESIGN-REVIEW pins are all identical.
- **Approving DESIGN-REVIEW:** `DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV2-APPROVE-20260809-053253.md`
  (`DESIGN_REVIEW_VERDICT: approve`, R1-R3 reconciled at the pinned bytes). The approve is on the exact
  doc hash — the design-doc PLAN lineage gate is satisfied; this PROCEED is sequencing, not an approve.
- **Floor consumer-contract:** affirmatively ratified
  (`DESIGN-REVIEW-FLOOR-PLANNER-R48-CONSUMER-CONTRACT-RATIFIED-20260809-050728.md`) — two-key wire shape,
  own-flavor meaning, opaque transport, absence-to-skip semantics, retained through rev2.
- **Seams intact at current `main` (`f0179e0`):** `InstallTarget` struct present (the single
  `optional<PackerHome>` field lands here on implement), fences live (`RepoDiscoveredUnsupported`;
  `require_empty_array` ×2). Main advanced past your `1b925ca` freshness tip on the docs lane, but the
  sealed design hash is fixed and the seams have not drifted.

## Design invariants I am holding you to (the dispatched scope, unchanged)

Wire = two optional co-occurring top-level keys (`packer_home`, `packer_home_flavor`); present ⇒
non-empty absolute in its declared-and-verified flavor; absent (or JSON null) ⇒ needle skips.
`format_version` stays 1; NO capability entry; NO new `ErrKind` (D5 freeze). Transport = one
`optional<manifest::PackerHome>` on `InstallTarget`, populated once by `run_session_leg`, core strictly
opaque. Both Step-3 fences untouched. 23-case acceptance matrix across `test_manifest.cpp` /
`test_pack.cpp` / `test_sessions.cpp` / both adapter-install files. This matches my `024150` dispatch —
no scope drift observed; capturing pack-time metadata (not editing a restored payload) stays inside the
operator's session-only-rewrite line.

On record, carried forward: the honest-packer limitation (a hostile image can omit the key pair — the
origin-path/id **union** scan remains the adversarial floor, this carrier is not a security boundary on
its own) and the two consumer-side duties owed at the floor's needle head. Fold both into the plan's
acceptance criteria and out-of-scope lines.

## What you emit next

Per lifecycle step 6, emit your gated `PHASE: PLAN` FROM `s4-matrix.planner` with `DESIGN_LOCK_ID` = the
design-doc path, `DESIGN_RECORD_KIND: design-doc`, and `PARENT_DISPATCH_ID` pointing to the approving
DESIGN-REVIEW (`…053253`). Your Implementer's plan-review is the plan gate; on its approve, you issue the
bare `DISPATCH IMPL` to your one Implementer within the locked scope. I do not hold a standing
plan-approval gate and go to standby after this — re-engage me on a hard trigger, scope deviation,
cross-pair collision, or the merge report.

## Coupling reminder
The carrier + the floor's home-prefix needle land TOGETHER under R-4.8, hard-gated before ANY release.
Non-blocking for B2's current union-scope resume. Merge ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — read-only reconcile (sha256 of the design doc working-tree + committed blob at 1b925ca6; verdict/hash grep of the DESIGN-REVIEW; seam + fence check at main). This relay + its INDEX row ride one explicit-path docs-lane commit whose SHA lands after filing.
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to this relay + .relays/s4/INDEX.md.

CARRY LIST:
- `.relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-R48-CARRIER-PROCEED-TO-PLAN-20260809-054301.md` → `s4-matrix.planner`
- design APPROVED at hash 349ef6e1 (sealed blob = working = committed 1b925ca6); DESIGN-REVIEW 053253 approve; floor contract ratified 050728 → lineage gate satisfied
- emit the gated PHASE:PLAN (DESIGN_LOCK_ID = doc path, PARENT = the approving DESIGN-REVIEW); Implementer plan-review is the plan gate; I go to standby
- R-4.8 coupling: carrier + floor needle land together, hard-gated before any release; non-blocking for B2's union-scope resume
