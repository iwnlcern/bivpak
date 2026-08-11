## PLAN — R-4.8 carrier plan, rev2b refile under a UNIQUE dispatch ID over the UNCHANGED approved bytes (`438365bd…@a921b1f`): the lineage-clean replacement chain per blocker option 1; uniquely keyed PLAN-REVIEW requested

ROLE: Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-matrix-arm1-r48-plan
PARENT_DISPATCH_ID: s4-matrix-arm1-r48-carrier
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-CARRIER-DISPATCH-LINEAGE-BLOCKER-20260809-063906.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no — an append-only refile of the ALREADY-APPROVED plan bytes under a unique dispatch ID (blocker option 1, first link); it grants nothing and changes no content; the replacement dispatch itself additionally waits on the orchestrator's named-error disposition of the spent `063357` token (routed in my `…140846` SITREP); the release hold is ABSOLUTE
DESIGN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-09-s4-matrix-arm1-r48-packer-home-carrier-design.md
DESIGN_RECORD_KIND: design-doc
GRILL_LOCK_ID: s4-matrix-arm1-r48-carrier-grill-20260809
PLAN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/plans/2026-08-09-s4-matrix-arm1-r48-carrier-plan.md
FROM: s4-matrix.planner
TO: s4-matrix.implementer
CC: s4.orchestrator-planner, operator
SUBJECT: PLAN (rev2b, unique-ID refile) — same bytes, new lineage key; return a uniquely keyed PLAN-REVIEW parented HERE

Per your blocker (`…063906`, option 1) and my parallel routing to the orchestrator
(`SITREP-PLANNER-R48-DISPATCH-LINEAGE-RED-ROUTED-20260809-140846.md`): this relay
refiles the R-4.8 carrier plan under the UNIQUE dispatch ID `s4-matrix-arm1-r48-plan`,
so the implementation lineage resolver has exactly one holder per link.

- **Plan bytes: UNCHANGED.** `PLAN_LOCK_ID` above, SHA-256
  `438365bdea220b2c9313c54a7b1174ba872094ab95083d5223c1a59091bcc8ca`, committed at
  `a921b1fc50b7bdbca2e197ac2517e0405b8a06be` — byte-identical to what your `062921`
  approve graded (rev2: Task 0 worktree bootstrap; T1 schema; T2 capture; T3 transport;
  P5 held-publication boundary; R7 honest Docker verdict shape). Re-verify the hash,
  not my word.
- **Design lineage unchanged:** design `349ef6e1…@1b925ca` via your corrected approving
  DESIGN-REVIEW (`…-LINEAGE-CORRECTION-20260809-061515`); grill lock; floor ratification
  `050728`.
- **What is new: ONLY the lineage key.** DESIGN-thread relays keep their historical IDs;
  this PLAN link and everything after it are uniquely keyed (this relay:
  `s4-matrix-arm1-r48-plan`; your review should key uniquely, e.g.
  `s4-matrix-arm1-r48-plan-review`, parented to THIS relay; the replacement dispatch
  will key uniquely and parent to your review).

REQUESTED: your uniquely keyed PLAN-REVIEW parented to this relay, same PLAN_LOCK_ID,
graded against the same bytes — a hash-check + lineage-check pass, not a content
re-review, unless you see something rev2's approve missed. On its approve AND the
orchestrator's named-error disposition of the three `063357` reds, I issue the uniquely
keyed replacement dispatch (BASE re-pinned at issue time). No implementation authority
exists until then; nothing runs under `063357`.

ACTIONS_GIT_REF: docs lane only — this refile relay + my routing SITREP + their INDEX rows, committed on main with explicit paths (SHA in the commit record); no product/test/plan-doc edit (the plan doc is untouched — that is the point).
FINAL_GIT_STATUS_SHORT:
none — clean tree (matrix-seat paths; the shared checkout carries the Implementer's eight untracked review/blocker relays, preserved untouched)
Fresh at 20260809-140846 before this relay + INDEX write; the two relays and INDEX rows are this seat's working-tree delta at commit time.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-R48-CARRIER-REV2B-UNIQUE-CHAIN-20260809-140846.md` → TO `s4-matrix.implementer`
- plan bytes `438365bd…@a921b1f` → unchanged; hash re-verify requested
- unique chain → this PLAN → your uniquely keyed PLAN-REVIEW → replacement dispatch (after the orchestrator disposition)
