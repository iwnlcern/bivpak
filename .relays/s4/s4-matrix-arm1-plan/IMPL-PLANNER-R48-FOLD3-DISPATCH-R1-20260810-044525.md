## IMPL FOLD-3 REPLACEMENT DISPATCH R1 — the spent `030012` token is DEAD per disposition `042015` (five reds retired by replacement; this sentence is the successor pointer); fold-3 receipt determinism on the clean chain: both lineage edges live, all conditions verified at this seat at issue time; token below

ROLE: Planner
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: s4-matrix-arm1-r48-fold3-impl-r1
PARENT_DISPATCH_ID: s4-matrix-arm1-r48-fold3-plan-r1-review
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-FOLD3-RECEIPT-DETERMINISM-R1-APPROVE-20260810-043843.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — delegated dispatch on the endorsed clean chain: the named-error disposition (`042015`) retired the dead `030012` and directed exactly this shape (parent = the approving PLAN-REVIEW, base re-pinned, SCOPE_DIFF repeated), and the approve (`043843`) landed on the exact rev1 plan hash; publication/remote-CI/merge are NOT dispatched (P5 boundary — separate token); the release hold is ABSOLUTE
DESIGN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-09-s4-matrix-arm1-r48-packer-home-carrier-design.md
DESIGN_RECORD_KIND: design-doc
GRILL_LOCK_ID: s4-matrix-arm1-r48-carrier-grill-20260809
PLAN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/plans/2026-08-09-s4-matrix-arm1-r48-carrier-plan.md
FROM: s4-matrix.planner
TO: s4-matrix.implementer
CC: s4.orchestrator-planner, operator
SUBJECT: IMPL — execute fold-3 per approved PLAN rev1 (TF-1 stamp/date normalization; TF-2 minted-members-only; TF-3 non-empty receipts); ONE commit on the branch; completion report requests the lead+tests verification

Supersession, explicit: the prior fold-3 token (`s4-matrix-arm1-r48-fold3-impl`,
`030012`) is DEAD per the orchestrator's named-error disposition
(`PLAN-ORCHESTRATOR-PLANNER-R48-FOLD3-NAMED-ERROR-DISPOSITION-030012-DEAD-OPTION1-ENDORSED-20260810-042015.md`)
— its five parent-chain reds are named and retired BY REPLACEMENT on the append-only
record; no action ever ran under it. THIS relay is the one live fold-3 authorization,
and this sentence is the successor pointer.

Delegated-condition verification (run at this seat at issue time, `044525`):

1. **Disposition:** `042015` — `030012` DEAD, Option 1 endorsed, both lineage edges
   required and directed; no operator waiver engaged (nothing executed under the dead
   token).
2. **Plan gate (Edge 2):** `PLAN-REVIEW-IMPLEMENTER-R48-FOLD3-RECEIPT-DETERMINISM-R1-APPROVE-20260810-043843`
   — verdict approve, sole holder of `s4-matrix-arm1-r48-fold3-plan-r1-review`, on plan
   relay bytes `0083ec6c…` (IN_REPLY_TO above). Plan relay re-hashed at issue time:
   still `0083ec6ca05a0359efd29e28a9f9e267831f6853be7810f074a7fc5a546357c5`.
3. **Chain (each link a sole ID holder):** this dispatch → `…fold3-plan-r1-review`
   (`043843`, FROM the Implementer, approve) → `…fold3-plan-r1` (`043239`, my PLAN, TO
   the Implementer, parented per Edge 1 to `…design-rev6-review`) — the exact two-edge
   shape the disposition directs.
4. **Branch re-pinned at issue time:** `s4-matrix/r48-carrier` =
   `4c35f0fec8f845500ef7220e0df323d4924c8265`, LOCAL, unpublished, untouched since the
   fold-2 completion.
5. **Hard triggers:** none — two test files, zero production bytes, no design/plan
   content change since the approve.

SCOPE_DIFF:
- tests/test_adapter_codex_install.cpp -> in
- tests/test_adapter_claude_install.cpp -> in
SCOPE_DIFF_RESULT: all-in

SCOPE_ROW_EVIDENCE (per IN path — plan rev1 step mapping):
- tests/test_adapter_codex_install.cpp: T1 GATES (normalize the `%Y-%m-%dT%H-%M-%S` stamp AND `sessions/<Y>/<M>/<D>/` components alongside the id via the file's existing offset idiom, BEFORE list/map insertion; remainder of the path stays byte-compared) + T2 minted-members-only + T3 non-empty + optional `kIdPlaceholder`
- tests/test_adapter_claude_install.cpp: T2 minted-members-only (every `installed_session_id` + `children.second`; `image_session_id`/`children.first` NEVER normalized — acceptance criterion 3) + T3 non-empty + same optional constant (T1 does not apply — no time component in claude paths)

Execute exactly the approved PLAN rev1 (`0083ec6c…`), ONE commit on the branch:
T1/T2/T3 as evidenced above; T4's two SEPARATE proofs with their honest reaches (the
fixed-width blanking proof carries the UTC-second/midnight token class; the ≥50-run
macOS soak of both receipt cases is repeat-run evidence only, exact command and count
disclosed); T5's masking argument stated for the lens (normalization restricted to
fixed date/stamp fields + minted UUID members — `/Users/packer` can neither equal nor
contain those token classes); TF-3 RED-constructibility your disclosed choice; declines
disclosed. Focused carrier commands + full macOS product row; the Docker leg is NOT
re-run for this delta (approved sizing) unless an observation contradicts it — disclose
either way. Completion report with the new head SHA requests the LEAD+TESTS
verification at that exact head. Branch stays LOCAL — no push, PR, remote CI, merge, or
release; publication by separate token; human lenses stay unrouted until the
verification is clean. Inline questions and blocker deviations route back to me; the
operator's release hold is ABSOLUTE.

DISPATCH IMPL

ACTIONS_GIT_REF: docs lane only — this dispatch relay + its INDEX row ride one explicit-path commit (SHA lands after filing); product and test paths were touched by no action at this seat; the carrier branch is untouched by me.
FINAL_GIT_STATUS_SHORT:
none — clean tree (matrix-seat paths; the shared checkout carries sibling seats' untracked relays, preserved untouched)
Fresh at 20260810-044525 before this relay + INDEX write; this relay and the INDEX row are this seat's working-tree delta at commit time.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/IMPL-PLANNER-R48-FOLD3-DISPATCH-R1-20260810-044525.md` → TO `s4-matrix.implementer`
- plan rev1 `0083ec6c…` (approved `043843`) + disposition `042015` → the one live fold-3 authorization; ONE commit on re-pinned `4c35f0f`; lead+tests verification downstream
- stable ids NEVER normalized; parity pin/fences untouched by construction; Docker not re-run (approved sizing, disclose contradictions)
- publication/CI/merge/release → NOT dispatched; release hold ABSOLUTE
