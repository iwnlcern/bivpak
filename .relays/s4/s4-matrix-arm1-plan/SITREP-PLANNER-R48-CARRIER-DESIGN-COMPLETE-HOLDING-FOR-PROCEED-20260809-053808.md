## SITREP — R-4.8 carrier DESIGN COMPLETE: rev2 APPROVED by the pair Implementer (doc bytes hash-pinned) + floor consumer contract RATIFIED affirmatively; both lock conditions on record; seams re-verified at the moved main tip; HOLDING for PROCEED-TO-PLAN

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-matrix-arm1-r48-carrier
PARENT_DISPATCH_ID: s4-build-standup-step4-opening-dispatch
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV2-APPROVE-20260809-053253.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no — an anticipated lifecycle event (design completion report); PROCEED-TO-PLAN is the orchestrator's sequencing call; implementation remains unauthorized; the release hold is ABSOLUTE
DESIGN_DOC_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-09-s4-matrix-arm1-r48-packer-home-carrier-design.md
DESIGN_RECORD_KIND: design-doc
GRILL_REQUIRED: yes
GRILL_LOCK_ID: s4-matrix-arm1-r48-carrier-grill-20260809
FROM: s4-matrix.planner
TO: s4.orchestrator-planner
CC: operator, s4.orchestrator-reviewer, s4-matrix.implementer, s4-floor.planner, m-4.planner
SUBJECT: SITREP — design complete for the master-directed R-4.8 scope addition; holding per lifecycle for your PROCEED-TO-PLAN

The R-4.8 pack-time packer-home carrier design (your dispatch `…024150`) is COMPLETE with
both lock conditions on record:

- **DESIGN_DOC_ID (rev2, APPROVED):**
  `docs/sprints/2026-08-04-s4-step4/designs/2026-08-09-s4-matrix-arm1-r48-packer-home-carrier-design.md`
  — bytes SHA-256 `349ef6e1f503be8a05660053111d5a4de634f0c0eba7512cccabfc38cc75841a`,
  committed at `1b925ca6dbcc46871afadde3e90f50870d634004`.
- **Approving DESIGN-REVIEW:**
  `DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV2-APPROVE-20260809-053253.md`
  (`DESIGN_REVIEW_VERDICT: approve`; R1-R3 reconciled PASS at the pinned bytes).
- **Floor consumer-contract ratification (affirmative):**
  `DESIGN-REVIEW-FLOOR-PLANNER-R48-CONSUMER-CONTRACT-RATIFIED-20260809-050728.md`
  (approve, no extra field; commit `996dd1c`; retained through rev2 — the two-key wire
  shape, own-flavor meaning, opaque transport, and absence-to-skip semantics are
  unchanged since ratification, per the rev1 re-review's own criterion).
- **Durable grill lock:** `…r48-carrier-grill-lock.md` (D1-D5 + rev2 appendix D6-D8).

Lifecycle summary (three review cycles, converged): rev0 must-revise B1-B4 → rev1 folded
(transport seam, independent flavor, honest empty mechanism, grill + explicit floor
routing) → rev1 must-revise R1-R3 → rev2 folded (single optional `PackerHome` struct;
core-local total `classify_absolute` with a rewrite-parity pin — direct reuse rejected as
circular from the parser; one lexical validator at both wire boundaries; JSON null ≡
missing rule; local error-detail remap) → APPROVE. Every finding was byte-verified at the
source seams before folding. Operator rulings on record: top-level-once placement; Q1
(relative `$HOME` ⇒ absent — subsumed under the classifier in rev2).

Design invariants for your reconcile: wire = two optional co-occurring top-level keys
(`"packer_home"`, `"packer_home_flavor"`), present ⇒ non-empty absolute in its
declared-and-verified flavor, absent ⇒ needle skips; `format_version` stays 1, no
capability entry, no new `ErrKind` (D5 freeze intact); transport = one
`optional<manifest::PackerHome>` field on `InstallTarget`, populated once by
`run_session_leg`, core strictly opaque; both Step-3 fences untouched; 23-case acceptance
matrix across `tests/test_manifest.cpp` / `test_pack.cpp` / `test_sessions.cpp` / both
adapter-install files. On record from the floor: the honest-packer limitation (a hostile
image can omit the pair; the origin-path/id union scan remains the adversarial floor) and
two consumer-side duties owed at the needle head.

Freshness note: I re-verified the design's cited seams at the CURRENT main tip after
master's condition-3 closures landed (B1 `e3f8f39`, slice A `77daa87c` — both merged
BENEATH my design commits; `main` tip = `1b925ca`): `InstallTarget` unchanged
(adapter.hpp:156-161), single construction site (sessions.cpp:267), fences live. No
seam drift; the approve's pinned bytes are the tip's bytes.

HOLDING per lifecycle step 6: the gated design-doc PLAN is mine to emit AFTER your
PROCEED-TO-PLAN (sequencing only, per the lineage gate). Non-blocking context unchanged:
Wave-A panel-clean and with master; B/C/D F-fenced; zero-ref `capture_mode` cell awaiting
m-1; the carrier + floor needle land together under R-4.8, hard-gated before ANY release;
the release hold is ABSOLUTE.

ACTIONS_GIT_REF: docs lane only — this relay + its INDEX row, committed on main with explicit paths (SHA in the commit record); no product/test edit.
FINAL_GIT_STATUS_SHORT:
none — clean tree (matrix-seat paths; the shared checkout carries the Implementer's three untracked review relays, preserved untouched)
Fresh at 20260809-053808 before this relay + INDEX write; this relay and the INDEX row are this seat's working-tree delta at commit time.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/SITREP-PLANNER-R48-CARRIER-DESIGN-COMPLETE-HOLDING-FOR-PROCEED-20260809-053808.md` → TO `s4.orchestrator-planner`
