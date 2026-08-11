## PLAN — R-4.8 carrier implementation plan rev0 (gated, design-doc-locked): three TDD tasks — schema, capture, transport — on one branch off main; plan review requested from the pair Implementer (the plan gate)

ROLE: Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-matrix-arm1-r48-carrier
PARENT_DISPATCH_ID: s4-matrix-arm1-r48-carrier (approving DESIGN-REVIEW: .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV2-APPROVE-20260809-053253.md, per the lineage gate)
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-R48-CARRIER-PROCEED-TO-PLAN-20260809-054301.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no — the gated design-doc PLAN after PROCEED-TO-PLAN; the Implementer plan review is the plan gate; on its approve I issue the bare dispatch token under the standing delegation (PROCEED `…054301` §"What you emit next"); merge/publication/release remain outside — the release hold is ABSOLUTE
DESIGN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-09-s4-matrix-arm1-r48-packer-home-carrier-design.md
DESIGN_RECORD_KIND: design-doc
GRILL_LOCK_ID: s4-matrix-arm1-r48-carrier-grill-20260809
PLAN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/plans/2026-08-09-s4-matrix-arm1-r48-carrier-plan.md
FROM: s4-matrix.planner
TO: s4-matrix.implementer
CC: s4.orchestrator-planner, operator, s4-floor.planner, m-4.planner
SUBJECT: PLAN-REVIEW request (rev0) — verdict wanted: approve | must-revise | reject-narrow | human-decision-required

The gated plan against the approved rev2 design (doc SHA-256 `349ef6e1…` at `1b925ca`,
your approve `…053253`, floor ratification `…050728` retained) is filed:
`docs/sprints/2026-08-04-s4-step4/plans/2026-08-09-s4-matrix-arm1-r48-carrier-plan.md`.

Shape: THREE bite-sized TDD tasks on ONE branch `s4-matrix/r48-carrier` off current
`main`, one commit each, one draft PR at the end, no merge:

- **T1 schema** (`manifest.hpp/.cpp` + `test_manifest.cpp`): `PackerHome` struct
  (defaulted `==` per your rev2 note), `classify_absolute` (exact D7 grammar, WSL before
  POSIX), `packer_home_valid`, valid-gated serialize after `source_path_flavor`, parse
  with presence-XOR / local flavor-detail remap / validator — full hostile-JSON matrix
  incl. the `carrier_json` helper, lone-null/lone-key/mismatch/unknown-flavor rows with
  EXACT `.error().detail` assertions, `classify_absolute` unit branches, and the
  rewrite-parity spelling table (biv_tests links bivcore→biv_adapters PUBLIC, verified).
- **T2 capture** (`pack.cpp` + `test_pack.cpp`): `packer_home_carrier(env.home)` helper
  beside `path_flavor` (which stays UNTOUCHED), one designated-init field at the
  `manifest_model` site (:663), six-row env-controlled table (absolute/unset/empty/
  relative-Q1/wsl-mount-independence/windows-drive) via the file's `ScopedEnv` idiom.
- **T3 transport** (`adapter.hpp` + `sessions.cpp` + three test files):
  `InstallTarget::packer_home` after `capabilities`, populated at the single
  construction site (:267) with `, .packer_home = manifest.packer_home` — NO other core
  read; `CountingAdapter` extended to record receipt (present + absent), one inert-
  receipt case per adapter leg (copy each file's smallest green install case, add only
  the field, keep every assertion — receipt, never needle semantics).

Acceptance criteria (7), out-of-scope guards (needle, interpretation, honest-packer
countermeasures, merge/release), global constraints (format_version 1, no ErrKind, wire
sealed by floor ratification, fences byte-identical), and the full local gate command are
in the plan doc. The honest-packer limitation and the floor's two duties are folded into
out-of-scope/acceptance per the PROCEED's instruction.

REVIEW ASKS:
1. T3 step 3.1 reuses your existing fixtures by exact line anchor (CountingAdapter :225
   setup; each adapter file's smallest green install case) rather than inlining ~50-line
   copies — confirm those anchors are the right fixtures or name better ones.
2. T2 step 2.4's note: existing pack cases set HOME via ScopedEnv, so their manifests now
   carry the field — confirm no existing assertion does full-manifest equality that
   would need widening (I found none by inspection).
3. The plan's parse insertion point (after source_path_flavor assignment, before
   agent_sessions) and designated-init ordering — confirm against your working knowledge
   of the parse function body.
4. Anything that would push a task over its bite-size or needs a fourth task.

Return `PLAN_REVIEW_VERDICT: approve | must-revise | reject-narrow |
human-decision-required` parented to this relay, carrying the same PLAN_LOCK_ID. On
approve with SCOPE_DIFF all-in and no hard trigger, I issue `DISPATCH IMPL` to you under
the standing delegation. Non-blocking context unchanged; carrier + floor needle land
together under R-4.8; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: docs lane only — the plan doc (rev0) + this relay + its INDEX row, committed on main with explicit paths (SHA in the commit record); no product/test edit.
FINAL_GIT_STATUS_SHORT:
none — clean tree (matrix-seat paths; the shared checkout carries the Implementer's three untracked review relays, preserved untouched)
Fresh at 20260809-055146 before this relay + INDEX write; the plan doc, this relay, and the INDEX row are this seat's working-tree delta at commit time.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-R48-CARRIER-REV0-20260809-055146.md` → TO `s4-matrix.implementer`
- `docs/sprints/2026-08-04-s4-step4/plans/2026-08-09-s4-matrix-arm1-r48-carrier-plan.md` → PLAN_LOCK_ID under review
