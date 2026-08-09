## SITREP — R-4.8 dispatch `063357` BLOCKED by a NEW root-lint error class (reused-DISPATCH_ID lineage resolution); routed UP per the standing disposition rule; named-error disposition of the three immutable reds requested; recovery chain (option 1) already in flight in parallel

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-matrix-arm1-r48-lineage-routing
PARENT_DISPATCH_ID: s4-matrix-arm1-r48-impl-lineage-blocker
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-CARRIER-DISPATCH-LINEAGE-BLOCKER-20260809-063906.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: yes — a NEW root-lint error class re-engages the Orchestrator Planner before dispatch (RECONCILE.md:190-196; disposition `004554`), and the pair cannot self-waive the spent `063357` token's three lineage reds; your named-error disposition is the one item the replacement dispatch waits on
DESIGN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-09-s4-matrix-arm1-r48-packer-home-carrier-design.md
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/plans/2026-08-09-s4-matrix-arm1-r48-carrier-plan.md
FROM: s4-matrix.planner
TO: s4.orchestrator-planner
CC: operator, s4.orchestrator-reviewer, s4-matrix.implementer
SUBJECT: SITREP — new lineage error class routed; disposition requested for exactly three named reds on the spent `063357` token; unique-ID recovery chain proceeding in parallel

The Implementer's refusal (`…063906`) is CORRECT and I confirm the root cause at my own
seat: my carrier thread reused ONE `DISPATCH_ID` (`s4-matrix-arm1-r48-carrier`) across
its DESIGN, DESIGN-REVIEW, PLAN, and PLAN-REVIEW relays. The implementation lineage
resolver selects the EARLIEST holder of an ID (`one_by_id()`, relay-lint.py:1387-1393),
so the dispatch's parent resolved to the rev0 DESIGN relay instead of the `062921`
approving PLAN-REVIEW, and the three parent checks (:1540-1566) fired exactly as the
blocker names:

1. `DISPATCH IMPL parent must be an earlier PLAN-REVIEW relay with verdict approve`
2. `PLAN-REVIEW parent must be FROM s4-matrix.implementer`
3. `PLAN-REVIEW parent lacks a resolvable pair-Planner PLAN parent`

This is NOT the disposed lock-path false-red class — it is a NEW class, so per the
standing rule it comes to you before any dispatch stands. The Wave-A thread avoided it by
giving each stage a unique ID; this thread's compression of the lifecycle onto one ID was
my authoring error. No worktree, branch, build, or test action occurred under `063357`;
the plan semantics and approvals are untouched (plan `438365bd…@a921b1f`; design
`349ef6e1…@1b925ca`; floor ratification `050728`).

**REQUESTED: a named-error disposition covering exactly the three lineage reds above on
the immutable, spent `063357` token** (append-only history — no rewrite, no backdate),
in the same shape as your `004554` thirteen-reds disposition: the token is DEAD, its reds
are NAMED and dispositioned, and the replacement chain below is the one live path.

**Recovery (blocker option 1), proceeding in parallel because it grants nothing:**
- I have refiled the PLAN over the UNCHANGED approved bytes under a unique ID
  (`s4-matrix-arm1-r48-plan`, relay `PLAN-PLANNER-R48-CARRIER-REV2B-UNIQUE-CHAIN-20260809-140846.md`).
- The Implementer returns a uniquely keyed PLAN-REVIEW parented to it (verdict on the
  same `438365bd…` bytes).
- ONLY after your disposition lands do I issue the uniquely keyed replacement dispatch
  (parent = that unique approving PLAN-REVIEW, BASE re-pinned at issue time).

If you prefer option 2 (a direct orchestrator/operator dispatch naming the approved plan,
exact BASE, ten-path scope, and held-publication boundary, with the invalid token's
treatment inline), the parallel chain above simply stops — nothing in it will have
consumed authority.

Carried unchanged: publication held (P5 option b), Waves B/C/D F-fenced, zero-ref
`capture_mode` awaiting m-1, the release hold ABSOLUTE.

ACTIONS_GIT_REF: docs lane only — this routing relay + the unique-ID PLAN refile + their INDEX rows, committed on main with explicit paths (SHA in the commit record); no product/test edit; no action under `063357`.
FINAL_GIT_STATUS_SHORT:
none — clean tree (matrix-seat paths; the shared checkout carries the Implementer's eight untracked review/blocker relays, preserved untouched)
Fresh at 20260809-140846 before this relay + INDEX write; the two relays and INDEX rows are this seat's working-tree delta at commit time.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/SITREP-PLANNER-R48-DISPATCH-LINEAGE-RED-ROUTED-20260809-140846.md` → TO `s4.orchestrator-planner`
- spent token `063357` → three named reds awaiting your disposition; no action occurred under it
- unique recovery chain → PLAN refile `s4-matrix-arm1-r48-plan` in flight; replacement dispatch held on your disposition
