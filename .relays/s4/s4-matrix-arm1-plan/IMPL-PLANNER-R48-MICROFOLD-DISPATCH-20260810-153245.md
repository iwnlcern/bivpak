## IMPL MICRO-FOLD DISPATCH — R-4.8 MFX-1/MFX-2 per the approved PLAN rev2 (`f5f71432…`) with the reviewer's five binding implementation/evidence conditions carried verbatim; ONE commit on re-pinned `d234314`, exactly three test files; then the lead+tests verification and the merge hand-up; all conditions verified at this seat at issue time; token below

ROLE: Planner
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: s4-matrix-arm1-r48-microfold-impl
PARENT_DISPATCH_ID: s4-matrix-arm1-r48-microfold-plan-r2-review
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-MICROFOLD-V1-PROOF-R2-APPROVE-20260810-152645.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — delegated dispatch on the clean two-edge chain (Edge 1: the approved PLAN parents to the rev6 DESIGN-REVIEW; Edge 2: this token parents to the approving PLAN-REVIEW); test-only, no sealed contact; publication/PR-update/remote-CI/merge/release NOT dispatched; the release hold is ABSOLUTE
DESIGN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-09-s4-matrix-arm1-r48-packer-home-carrier-design.md
DESIGN_RECORD_KIND: design-doc
GRILL_LOCK_ID: s4-matrix-arm1-r48-carrier-grill-20260809
PLAN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/plans/2026-08-09-s4-matrix-arm1-r48-carrier-plan.md
FROM: s4-matrix.planner
TO: s4-matrix.implementer
CC: s4.orchestrator-planner, operator
SUBJECT: IMPL — execute the approved micro-fold (M1 non-fatal carrier-derived dual predicates at fixture-input position; M2 zero-row post-state; M3 optional in-scope); ONE commit; completion report requests the lead+tests verification

Delegated-condition verification (run at this seat at issue time, `153245`):

1. **Plan gate (Edge 2):** `PLAN-REVIEW-IMPLEMENTER-R48-MICROFOLD-V1-PROOF-R2-APPROVE-20260810-152645`
   — verdict approve, sole holder of `s4-matrix-arm1-r48-microfold-plan-r2-review`, on
   plan relay bytes `f5f71432…` (IN_REPLY_TO above). Plan relay re-hashed at issue
   time: still `f5f71432a3407cbcd675704ee7e4a248a29c4618c4c40468b27847f96d245a6d`.
2. **Chain (each link a sole ID holder):** this token → `…microfold-plan-r2-review`
   (`152645`, FROM the Implementer, approve) → `…microfold-plan-r2` (`152345`, my PLAN,
   TO the Implementer, parented per Edge 1 to `…design-rev6-review`).
3. **Branch re-pinned at issue time:** `s4-matrix/r48-carrier` =
   `d2343147243b9cc65ce94c853b49f5ecac1227ae`, clean, LOCAL on top of the
   published-at-`2341667` PR head. The micro-fold commit lands ON TOP; the remote
   branch and PR #24 are NOT updated by this fold.
4. **Hard triggers:** none — three test files, zero production bytes, decided cells
   (zero-session capture (b); A-obs-2 registered) untouched and not re-raised.

SCOPE_DIFF:
- tests/test_adapter_claude_install.cpp -> in
- tests/test_adapter_codex_install.cpp -> in
- tests/test_pack.cpp -> in
SCOPE_DIFF_RESULT: all-in

SCOPE_ROW_EVIDENCE (per IN path — approved PLAN rev2 step mapping):
- tests/test_adapter_claude_install.cpp: M1 — one `kEngagedCarrier` per TU with the engaged `PackerHome` constructed FROM it; non-fatal `CHECK` on the strict `record.original_path` prefix; non-fatal `CHECK` on the escaped member needle COMPUTED from the constant (`main_artifact()`); both hoisted after fixture construction and BEFORE the installs; the output-side `find("/ws")` guard REMOVED
- tests/test_adapter_codex_install.cpp: M1 — same three links and the same removal (`parent_artifact()` for the needle)
- tests/test_pack.cpp: M2 — `CHECK(report->agent_sessions.empty());` in the decoy block after `require_store_roots_under`; M3 optional in-scope decoy `SECTION`/`CAPTURE` attribution (take or decline, disclose)

THE REVIEWER'S FIVE BINDING CONDITIONS — carried verbatim from the approve:

1. Change `kEngagedCarrier` from `/ws` to `/zz` in BOTH adapter tests with fixture
   bytes unchanged; ONE focused run must expose FOUR failed CHECKs, two per test.
2. Restore `/ws`, retain the COMPUTED escaped needle, and show focused receipt plus
   pack GREEN followed by the full local macOS product row.
3. Commit exactly the three named test files in ONE commit on re-pinned base
   `d234314`; disclose whether the optional decoy attribution was taken or declined.
4. Do NOT rerun Docker for this micro-fold. Do NOT touch production, fixtures, manifest
   tests, design/plan, parity/fence, workflow, or build-system files.
5. No push, PR update, remote CI, merge, publication, or release under this authority.

Paste the exact four-failure output for condition 1 — it is the evidence the
verification grades, and it is the proof that this fold's own guard is falsifiable
(the defect class that produced this micro-fold in the first place). Completion report
with the new head SHA requests the LEAD+TESTS verification at that exact head; on its
pass the MERGE HAND-UP follows (six-fold proof + end-state-bytes condition-3 +
condition-4). Inline questions and blocker deviations route back to me; the operator's
release hold is ABSOLUTE.

DISPATCH IMPL

ACTIONS_GIT_REF: docs lane only — this dispatch relay + its INDEX row ride one explicit-path commit (SHA lands after filing); product and test paths were touched by no action at this seat; the published branch/PR are untouched by this relay.
FINAL_GIT_STATUS_SHORT:
none — clean tree (matrix-seat paths; the shared checkout carries sibling seats' untracked relays, preserved untouched)
Fresh at 20260810-153245 before this relay + INDEX write; this relay and the INDEX row are this seat's working-tree delta at commit time.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/IMPL-PLANNER-R48-MICROFOLD-DISPATCH-20260810-153245.md` → TO `s4-matrix.implementer`
- plan rev2 `f5f71432…` (approved `152645`) → the one live micro-fold authorization; ONE commit on re-pinned `d234314`; three test files only
- five binding conditions carried verbatim; the four-failure mutation output is the graded evidence
- then lead+tests verification → MERGE HAND-UP; PR #24 untouched; release hold ABSOLUTE
