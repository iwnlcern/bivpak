## IMPL LENS-FOLD DISPATCH — R-4.8 six lens must-fixes per the approved plan (`e1837e21…`) with the reviewer's three proof pins carried verbatim; G1 CLOSED by the operator's option-(b) ruling (`074043` — no product or design path in this fold); ONE test-only commit on the published head, then the lead+tests targeted re-check; all conditions verified at this seat at issue time; token below

ROLE: Planner
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: s4-matrix-arm1-r48-lensfold-impl
PARENT_DISPATCH_ID: s4-matrix-arm1-r48-lensfold-plan-review
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-LENSFOLD-SIX-MUSTFIX-APPROVE-20260810-074840.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-R48-CAPTURE-SCOPE-RULED-B-NO-CELL-TO-WIRE-20260810-074043.md (the option-(b) closure this dispatch carries)
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — delegated dispatch on the clean two-edge chain (Edge 1: the approved PLAN parents to the rev6 DESIGN-REVIEW; Edge 2: this token parents to the approving PLAN-REVIEW); the §4 operator cell is CLOSED (b) and carried herein — any contrary re-ruling is a HARD TRIGGER requiring a fresh product-change cycle, never a silent activation of the closed conditional; publication/PR-update/remote-CI/merge/release NOT dispatched; the release hold is ABSOLUTE
DESIGN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-09-s4-matrix-arm1-r48-packer-home-carrier-design.md
DESIGN_RECORD_KIND: design-doc
GRILL_LOCK_ID: s4-matrix-arm1-r48-carrier-grill-20260809
PLAN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/plans/2026-08-09-s4-matrix-arm1-r48-carrier-plan.md
FROM: s4-matrix.planner
TO: s4-matrix.implementer
CC: s4.orchestrator-planner, operator
SUBJECT: IMPL — execute the approved lens-fold (H1/H2/V1/V2/V3/O1/BR1; G1 closed-(b)); ONE commit on `2341667`; branch/PR NOT republished by this fold; completion report requests the lead+tests re-check

Delegated-condition verification (run at this seat at issue time, `075116`):

1. **Plan gate (Edge 2):** `PLAN-REVIEW-IMPLEMENTER-R48-LENSFOLD-SIX-MUSTFIX-APPROVE-20260810-074840`
   — verdict approve, sole holder of `s4-matrix-arm1-r48-lensfold-plan-review`, on plan
   relay bytes `e1837e21…` (IN_REPLY_TO above). Plan relay re-hashed at issue time:
   still `e1837e21650b1c84795c2a518cafea6040092b517f2f83c5cfaafae84aa1aee2`.
2. **Chain (each link a sole ID holder):** this token → `…lensfold-plan-review`
   (`074840`, FROM the Implementer, approve) → `…lensfold-plan` (`072513`, my PLAN, TO
   the Implementer, parented per Edge 1 to `…design-rev6-review`) — the `071834` §5
   two-edge shape exactly.
3. **§4 closure carried:** the operator ruled option (b) — UNCONDITIONAL capture
   (`074043`; verified by the orchestrator in the R-4.8 register at `cca4b48`).
   G1 is CLOSED with nothing to wire: `pack.cpp` and the design doc are ABSENT from
   this fold's scope; the zero-session disclosure is a DECIDED cell — the re-check is
   instructed NOT to re-raise it.
4. **Branch re-pinned at issue time:** `s4-matrix/r48-carrier` =
   `234166722ef44f51db5740c2ac4e01301b5dc0c1` (the published PR #24 head), worktree
   clean, untouched since publication. The fold commit lands ON TOP; the remote branch
   and PR #24 are NOT updated by this fold (republish is a separate instruction).
5. **Hard triggers:** none — four test files, zero production bytes, no design/plan
   content change since the approve.

SCOPE_DIFF:
- tests/test_pack.cpp -> in
- tests/test_adapter_claude_install.cpp -> in
- tests/test_adapter_codex_install.cpp -> in
- tests/test_manifest.cpp -> in
SCOPE_DIFF_RESULT: all-in

SCOPE_ROW_EVIDENCE (per IN path — approved plan step mapping):
- tests/test_pack.cpp: H1 (one restoring RAII fixture owning ALL FOUR discovery inputs — HOME, CLAUDE_CONFIG_DIR, CODEX_HOME, CODEX_SQLITE_HOME — for EVERY pack() call; a matrix row may explicitly override/unset via fixture knobs, no row inherits from the runner; the :606-607 two-tier intent preserved through the knobs) + H2 (every positive discovered row's provenance store_root asserted beneath the test root; zero-row expectations stay explicit)
- tests/test_adapter_claude_install.cpp: V1 (engaged carrier = `/ws` so carrier-prefixed bytes sit IN compared content) + V2 (REQUIRE(emplace .second)) + V3 (minted-id carve-out stated + id-map stable-shape compare: entry count, agent, image_session_id, ordered children.first; installed_session_id/children.second excluded)
- tests/test_adapter_codex_install.cpp: V1 + V2 + V3 (same three, codex arm)
- tests/test_manifest.cpp: O1 (ORACLE RULE comment on the carrier-engaged exact-bytes golden, wording matched to test_envelope.cpp:566-567) + BR1 (factory accept brackets `/x` posix, `/mnt/c/x` wsl, `C:/x` windows)

THE REVIEWER'S THREE PROOF PINS — binding, carried verbatim from the approve:

1. **Hermeticity falsifier (AC2/AC7, NOT discretionary):** a CONSTRUCTED decoy store
   outside the fixture's pinned root must run RED through an unexpected discovered
   row/store-root BEFORE the RAII fixture is applied (strict TDD — this RED is
   constructible and therefore required); `getenv` evidence alone does not discharge
   it. After GREEN: the store-root-beneath-test-root assertions on every positive row.
2. **Carrier non-vacuity (AC3):** a DIRECT pre-equality assertion that at least one
   compared engaged-receipt content value CONTAINS the `/ws` carrier prefix — the
   comment or the assignment alone would be a second vacuous proof.
3. **V3 shape:** compare id-map entry count + stable members (`agent`,
   `image_session_id`, ordered `children.first`) across arms; exclude
   `installed_session_id` and `children.second`.

Gates, then report: focused adapter/manifest/pack verification + the full local macOS
row; Docker NOT re-run (test-only delta under the closed-(b) scope, per the approve).
Declines disclosed — silence is not a decline. Completion report with the new head SHA
requests the LEAD+TESTS targeted re-check at that exact head; the re-check will grade
the three proof pins as stated and will NOT re-raise the decided zero-session cell.
Branch stays LOCAL-plus-published-at-`2341667` — no push, no PR update, no remote CI,
no merge, no release; the merge hand-up (six-fold proof + end-state-bytes condition-3 +
condition-4) follows the re-check. Inline questions and blocker deviations route back
to me; the operator's release hold is ABSOLUTE.

DISPATCH IMPL

ACTIONS_GIT_REF: docs lane only — this dispatch relay + its INDEX row ride one explicit-path commit (SHA lands after filing); product and test paths were touched by no action at this seat; the published branch/PR are untouched by this relay.
FINAL_GIT_STATUS_SHORT:
none — clean tree (matrix-seat paths; the shared checkout carries sibling seats' untracked relays, preserved untouched)
Fresh at 20260810-075116 before this relay + INDEX write; this relay and the INDEX row are this seat's working-tree delta at commit time.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/IMPL-PLANNER-R48-LENSFOLD-DISPATCH-20260810-075116.md` → TO `s4-matrix.implementer`
- plan `e1837e21…` (approved `074840`) → the one live lens-fold authorization; ONE commit on re-pinned `2341667`; four test files only
- §4 CLOSED option-(b) (`074043`, register `cca4b48`) — carried; contrary re-ruling = HARD TRIGGER; decided cell not re-raisable at the re-check
- three reviewer proof pins binding (decoy RED; direct carrier-prefix assertion; stable-shape id-map compare); then lead+tests re-check → merge hand-up
- publication/PR-update/CI/merge/release → NOT dispatched; release hold ABSOLUTE
