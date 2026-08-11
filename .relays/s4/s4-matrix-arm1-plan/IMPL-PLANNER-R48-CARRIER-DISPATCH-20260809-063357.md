## IMPL DISPATCH — R-4.8 carrier on plan rev2: all delegated conditions verified, SCOPE_DIFF all-in, BASE pinned; token below

ROLE: Planner
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: s4-matrix-arm1-r48-impl
PARENT_DISPATCH_ID: s4-matrix-arm1-r48-carrier
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-CARRIER-REV2-APPROVE-20260809-062921.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — delegated conditional dispatch per the PROCEED-TO-PLAN (`…054301` §"What you emit next") on the approved rev2 plan; all standing conditions verified below; publication/remote-CI/merge are NOT dispatched (P5 boundary — separate token); the release hold is ABSOLUTE
DESIGN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-09-s4-matrix-arm1-r48-packer-home-carrier-design.md
DESIGN_RECORD_KIND: design-doc
GRILL_LOCK_ID: s4-matrix-arm1-r48-carrier-grill-20260809
PLAN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/plans/2026-08-09-s4-matrix-arm1-r48-carrier-plan.md
FROM: s4-matrix.planner
TO: s4-matrix.implementer
CC: s4.orchestrator-planner, operator
SUBJECT: IMPL — execute the rev2 carrier plan (Task 0 worktree bootstrap → T1 schema → T2 capture → T3 transport + gates); branch stays LOCAL; completion report requests the publication token

Delegated-condition verification (re-run at this seat):

1. **Delegation exists:** PROCEED-TO-PLAN `…054301` explicitly delegates conditional
   dispatch ("on its approve, you issue the bare dispatch token to your one Implementer
   within the locked scope").
2. **Plan review approve:** `PLAN-REVIEW-IMPLEMENTER-R48-CARRIER-REV2-APPROVE-20260809-062921.md`,
   verdict approve on plan bytes `438365bd…` at `a921b1f` (IN_REPLY_TO above).
3. **Chain:** that approve parents to my rev2 PLAN (`…062131`), which is my pair-Planner
   PLAN addressed to you under DESIGN_LOCK `349ef6e1…@1b925ca` via the corrected
   approving DESIGN-REVIEW (`…-LINEAGE-CORRECTION-20260809-061515`).
4. **SCOPE_DIFF:** the mechanical block below — plan file universe vs the locked design
   scope; no row outside it. `.github/**`, `rewrite_common.*`,
   `pack.cpp::path_flavor()`, and both Step-3 fence sites are NOT in the universe.
5. **Hard triggers:** none — no sealed-behavior change (wire ratified by the floor at
   `050728`), no new authority, publication held inside the plan, fences untouched.

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

**BASE (Task 0 pin): `a921b1fc50b7bdbca2e197ac2517e0405b8a06be`** (current `main`;
your approve verified src/tests byte-unchanged from the design commit through this head).
Create the isolated worktree from exactly this SHA (Task 0 via
superpowers:using-git-worktrees), branch `s4-matrix/r48-carrier`, and execute the plan
under superpowers:executing-plans: Task 0 bootstrap/baseline (STOP-AND-ROUTE on a red
baseline) → T1 schema → T2 capture → T3 transport → step 3.5 full macOS gate → step 3.7
Docker leg (R-3.48 verdict shape: substantive rows green, count row an expected disclosed
cosmetic red with exact observed totals) → step 3.8 completion report with the branch
head SHA, BOTH evidence legs, and the publication-token request. The branch is NOT
pushed; no PR, no remote CI, no merge, no release. Carried unchanged: the Wave-C
exit-mapping flag; the zero-ref `capture_mode` cell (awaiting m-1); Waves B/C/D stay
F-fenced — this dispatch is the R-4.8 carrier ONLY. Inline questions and blocker
deviations route back to me; the operator's release hold is ABSOLUTE.

DISPATCH IMPL

ACTIONS_GIT_REF: docs lane only — this dispatch relay + its INDEX row, committed on main with explicit paths (SHA in the commit record); no product/test edit at this seat.
FINAL_GIT_STATUS_SHORT:
none — clean tree (matrix-seat paths; the shared checkout carries your seven untracked review relays, preserved untouched — please land them with your next lane commit)
Fresh at 20260809-063357 before this relay + INDEX write; this relay and the INDEX row are this seat's working-tree delta at commit time.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/IMPL-PLANNER-R48-CARRIER-DISPATCH-20260809-063357.md` → TO `s4-matrix.implementer`
- BASE `a921b1fc50b7bdbca2e197ac2517e0405b8a06be` + plan `438365bd…` (rev2) → the one live R-4.8 implementation authorization; publication by separate token
