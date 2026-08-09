## IMPL DISPATCH R1 (replacement — the spent `063357` token is DEAD per the orchestrator disposition) — R-4.8 carrier on the unique chain: all delegated conditions re-verified, SCOPE_DIFF repeated all-in, BASE re-pinned; token below

ROLE: Planner
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: s4-matrix-arm1-r48-impl-r1
PARENT_DISPATCH_ID: s4-matrix-arm1-r48-plan-review
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-CARRIER-REV2B-UNIQUE-APPROVE-20260809-141439.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — delegated conditional dispatch on the endorsed unique chain; the orchestrator's named-error disposition (`…141650`) retired the three `063357` reds by replacement and directed exactly this dispatch (parent `141439`, BASE re-pinned, SCOPE_DIFF repeated); publication/remote-CI/merge are NOT dispatched (P5 boundary — separate token); the release hold is ABSOLUTE
DESIGN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-09-s4-matrix-arm1-r48-packer-home-carrier-design.md
DESIGN_RECORD_KIND: design-doc
GRILL_LOCK_ID: s4-matrix-arm1-r48-carrier-grill-20260809
PLAN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/plans/2026-08-09-s4-matrix-arm1-r48-carrier-plan.md
FROM: s4-matrix.planner
TO: s4-matrix.implementer
CC: s4.orchestrator-planner, operator
SUBJECT: IMPL — execute the rev2 carrier plan on the unique chain (Task 0 worktree bootstrap → T1 schema → T2 capture → T3 transport → gates); branch stays LOCAL; completion report requests the publication token

Supersession, explicit: the prior dispatch (`s4-matrix-arm1-r48-impl`, `063357`) is DEAD
per the orchestrator's named-error disposition
(`PLAN-ORCHESTRATOR-PLANNER-R48-LINEAGE-NAMED-ERROR-DISPOSITION-THREE-REDS-UNIQUE-CHAIN-ENDORSED-20260809-141650.md`)
— its three lineage reds are named and retired BY REPLACEMENT on the append-only record;
no action ever ran under it. THIS relay is the one live R-4.8 implementation
authorization, and this sentence is the successor pointer.

Delegated-condition verification (re-run at this seat on the unique chain):

1. **Delegation:** PROCEED-TO-PLAN `…054301` (standing); the disposition `…141650`
   additionally endorses option 1 and directs this exact dispatch (option 2 declined —
   dispatch authority stays at the pair).
2. **Plan gate:** `PLAN-REVIEW-IMPLEMENTER-R48-CARRIER-REV2B-UNIQUE-APPROVE-20260809-141439.md`
   — verdict approve, sole holder of `s4-matrix-arm1-r48-plan-review`, on plan bytes
   `438365bdea220b2c9313c54a7b1174ba872094ab95083d5223c1a59091bcc8ca` (IN_REPLY_TO above).
3. **Chain (each link a sole ID holder):** this dispatch → `s4-matrix-arm1-r48-plan-review`
   (`141439`, FROM the Implementer, approve) → `s4-matrix-arm1-r48-plan` (`140846`, my
   pair-Planner PLAN over the unchanged bytes) → design lock `349ef6e1…@1b925ca` via the
   corrected approving DESIGN-REVIEW edge. The orchestrator byte-verified this chain
   passes all three lineage checks.
4. **Bytes re-verified at issue time:** plan file SHA-256 still `438365bd…`; src/ and
   tests/ byte-unchanged `a921b1f..6047ab0` (empty diff at this seat).
5. **Hard triggers:** none — wire floor-ratified (`050728`), publication held inside the
   plan, fences outside the universe, no new authority.

SCOPE_DIFF:
- src/core/manifest/manifest.hpp -> in
- src/core/manifest/manifest.cpp -> in
- src/core/pack/pack.cpp -> in
- src/adapters/adapter.hpp -> in
- src/core/open/sessions.cpp -> in
- tests/test_manifest.cpp -> in
- tests/test_pack.cpp -> in
- tests/test_sessions.cpp -> in
- tests/test_adapter_claude_install.cpp -> in
- tests/test_adapter_codex_install.cpp -> in
SCOPE_DIFF_RESULT: all-in

**BASE (Task 0 pin, re-pinned at issue time): `6047ab0311491da5567c99f32b22ff14433fb1d2`**
(current `main`; docs-lane-only ahead of `a921b1f`). Create the isolated worktree from
exactly this SHA (Task 0 via superpowers:using-git-worktrees), branch
`s4-matrix/r48-carrier`, and execute the rev2 plan under superpowers:executing-plans:
Task 0 bootstrap/baseline (STOP-AND-ROUTE on a red baseline) → T1 schema → T2 capture →
T3 transport → step 3.5 full macOS gate → step 3.7 Docker leg (R-3.48 verdict shape:
substantive rows green, count row an expected disclosed cosmetic red with exact observed
totals) → step 3.8 completion report with the branch head SHA, BOTH evidence legs, and
the publication-token request. The branch is NOT pushed; no PR, no remote CI, no merge,
no release. Carried unchanged: the Wave-C exit-mapping flag; the zero-ref `capture_mode`
cell (awaiting m-1); Waves B/C/D stay F-fenced — this dispatch is the R-4.8 carrier ONLY.
Inline questions and blocker deviations route back to me; the operator's release hold is
ABSOLUTE.

DISPATCH IMPL

ACTIONS_GIT_REF: docs lane only — this dispatch relay + its INDEX row ride one explicit-path commit (SHA lands after filing); product and test paths were touched by no action at this seat.
FINAL_GIT_STATUS_SHORT:
none — clean tree (matrix-seat paths; the shared checkout carries the Implementer's untracked review/blocker relays, preserved untouched — please land them with your next lane commit)
Fresh at 20260809-142630 before this relay + INDEX write; this relay and the INDEX row are this seat's working-tree delta at commit time.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/IMPL-PLANNER-R48-CARRIER-DISPATCH-R1-20260809-142630.md` → TO `s4-matrix.implementer`
- BASE `6047ab0311491da5567c99f32b22ff14433fb1d2` + plan `438365bd…` (rev2, unique chain) → the one live R-4.8 implementation authorization; publication by separate token
