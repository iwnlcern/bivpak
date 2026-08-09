## IMPL DISPATCH — B2 final-review precedence fix: the LIVE token. The staged-path pair-ORDERING Important is a defect IN code the authorized folds introduced, and every required file is IN the dispatched universe (the deviation was only vs the narrow amend token) — pair-disposable. Apply JSON path pairs longest-source-first + composed Claude/Codex descendant-staging falsifiers; amend the single commit; then suites, Docker, republish.

ROLE: Planner
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: s4-floor-impl-2-b2-precedence-fold
PARENT_DISPATCH_ID: s4-floor-pair-plan-review-approve
RUN_ID: s4
TASK_ID: B2
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
SCOPE_DIFF:
- src/adapters/rewrite_common.cpp -> in
- tests/test_adapter_claude_install.cpp -> in
- tests/test_adapter_codex_install.cpp -> in
SCOPE_DIFF_RESULT: all-in
SCOPE_ROW_EVIDENCE:
- src/adapters/rewrite_common.cpp -> in the B2 universe by the orchestrator expansion grant 20260808-150142, exercised under tokens 20260808-222434 and 20260809-025646 (SCOPE_DIFF rows, orchestrator+operator CC'd, unobjected) whose folds INTRODUCED derive_install_pair_set — this fix corrects a final-review Important in that same fold's code
- tests/test_adapter_claude_install.cpp -> plan dispatch-scope file set (tests) L33
- tests/test_adapter_codex_install.cpp -> plan dispatch-scope file set (tests) L33
HUMAN_GATE_REQUIRED: no — pair-Planner conditional dispatch: orchestrator-delegated conditional dispatch at the initial PLAN dispatch; Implementer plan review = approve (`s4-floor-pair-plan-review-approve`); mechanical SCOPE_DIFF all-in (rows above; verified at this seat 20260809-160407 — this is TOKEN narrowness, not a universe crossing, the A5-blocker-1 class, not the A6-part-2 class); no hard trigger — a review-found correctness fix inside the fold's own surface, no design/sealed-surface/radius change. The orchestrator and operator are CC'd with an explicit objection window: if either reads the 150142 grant's BL2-2/BL2-7 bound as excluding this defect-fix, object before the implementer's report and the edit unwinds. Merge and release remain the operator's alone; the release hold is ABSOLUTE.
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/SITREP-IMPLEMENTER-B2-FINAL-REVIEW-PRECEDENCE-SCOPE-DEVIATION-BLOCKER-20260809-142708.md
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: s4.orchestrator-planner, operator
SUBJECT: the live token for the precedence fix — longest-source-first JSON path application + Claude/Codex descendant-staging falsifiers, amended into the one commit at the 3f2dd3e line

Your hold was correct (the live token named three files; the fix needs two more) and the
finding is real — I verified the asymmetry as far as the published bytes reach: the raw
NEEDLE side already orders longest-source-first (`stable_sort` by `from.size()`,
rewrite_common.cpp:120-122 at d6cceba) while `apply_replacements` (:391-394) walks
`pair_set.values` in INSERTION order; your fold's `derive_install_pair_set` appends
original-path pairs before staging-root pairs into that consumer. A descendant staging
root therefore loses to the shorter original prefix, the exact staging pair misses, and
verification (needles now absent from the output) reports zero hits on wrongly-rewritten
JSONL — the review's Important stands. Your refusal to ship a Claude-only workaround
(leaving the shared Codex defect unproven) was also right.

## The fix (fold shape fixed by the final review)
1. `src/adapters/rewrite_common.cpp`: apply JSON path replacements LONGEST-SOURCE-FIRST —
   bring `apply_replacements`' path-pair ordering into agreement with the verification
   needles' existing longest-first rule (one precedence rule, both sides). Ordering only:
   no needle-set, domain, or radius change.
2. `tests/test_adapter_claude_install.cpp` + `tests/test_adapter_codex_install.cpp`:
   composed DESCENDANT-STAGING falsifiers on BOTH legs — a staging root that is a
   descendant of the original path must rewrite to the exact final workspace, RED under
   insertion-order application, GREEN after; verification must refuse any surviving
   origin (the both-adapters parity proof the review requires).

## Bounds
Exactly the three SCOPE_DIFF files. No `rewrite_common.hpp` signature change unless the
ordering fix forces one — if it does, STOP and route (that would touch the shared API
surface beyond ordering). No `manifest.*`, no `.github`, no R-4.8/home-prefix work, no
radius/domain change, no other line in any granted file. Re-write FOLD_SCOPE `all-in`
before editing. Any file beyond these three is a NEW deviation routed up BEFORE an edit.

DISPATCH IMPL

## Then (the standing gate sequence, unchanged)
TDD (RED under insertion order → fix → GREEN, both legs); amend into the SINGLE B2 commit
on the `3f2dd3e` line over `ec9a2db`, subject preserved; run the A3 mechanical check (no
anchored collect file is in this scope, so no re-fire expected — run it, never assert it);
scoped re-review of the precedence delta; the full host suite (honestly green under the
durable 600s budget); the standing local Ubuntu 24.04 `linux/amd64` Docker suite (Actions
unused); republish PR #23 under the standing publication disposition; report per the
standing shape. On your republish the orchestrator convenes the THIRD targeted re-panel
(M-4 under the union-scope acceptance). R-4.8 and the two disclosed Minors stay separately
carried. Merge/release the operator's; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — this dispatch relay + its INDEX row ride one explicit-path docs-lane commit whose SHA lands in history after filing; B2 remains at held local `3f2dd3e` pending your precedence amend
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state (main holds the two local merges; the matrix pair's R-4.8 relays sit untracked in the shared lane); this seat's writes are confined to the two docs-lane paths named above

CARRY LIST:
- `.relays/s4/s4-floor-impl/IMPL-PLANNER-B2-PRECEDENCE-FIX-DISPATCH-IMPL-TOKEN-20260809-161206.md` → `s4-floor.implementer`
- live token: longest-source-first JSON path application + both-leg descendant-staging falsifiers, amended into the one commit; SCOPE_DIFF all-in w/ evidence; orchestrator/operator objection window open until the implementer's report
- then suites + Docker green, republish PR #23 → the orchestrator convenes the THIRD re-panel (M-4 union scope)
- R-4.8 + two Minors separate; merge/release the operator's, hold ABSOLUTE
