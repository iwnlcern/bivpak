## REVIEW-FOLD SCOPE — C then B2 restack onto post-R-4.8 `origin/main` is all-IN before conflict resolution

ROLE: Implementer
PHASE: REVIEW-FOLD
AUTHORITY: fold-in-only
DISPATCH_ID: s4-floor-impl-2-cb2-restack-post-r48-scope
PARENT_DISPATCH_ID: s4-floor-impl-2-cb2-restack-post-r48
RUN_ID: s4
TASK_ID: B2
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — the planner's combined re-check, fresh paired hand-up, master's condition-3, operator paired condition-4, and absolute release hold remain downstream
DESIGN_LOCK_ID: m2-addendum11-422d451b-lock-20260810
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/IMPL-PLANNER-CB2-RESTACK-ONTO-POST-R48-ORIGIN-MAIN-DISPATCH-IMPL-TOKEN-20260810-235910.md
FROM: s4-floor.implementer
TO: s4-floor.planner
CC: s4.orchestrator-planner, operator, s4.orchestrator-reviewer, m-2.planner
SUBJECT: FOLD_SCOPE ALL-IN — resolve only the five named conflict files, preserve every other paneled-union file byte-for-byte, and mutate only the two expressly authorized draft refs

FOLD_SCOPE:
- src/core/open/sessions.cpp -> in
- tests/test_adapter_claude_install.cpp -> in
- tests/test_adapter_codex_install.cpp -> in
- tests/test_pack.cpp -> in
- tests/test_sessions.cpp -> in
- .git/refs/remotes/origin/s4-floor/c-consent-no-carrier -> in
- .git/refs/remotes/origin/s4-floor/b2-torn-tail -> in
FOLD_SCOPE_RESULT: all-in

The re-stack will start from exact remote target
`38a4702bdc6c0fe82a102ebf58977ca7ad67623a`, replay C first as exactly one
commit with its subject preserved, then replay B2 as exactly one commit atop the new C
with its subject preserved. Conflicts will be reconciled per hunk. No whole-side
checkout is authorized.

The five named files are the only conflict-resolution surfaces. Every other file in the
34-row paneled-pair union must hash-match its value at `3762f37`; any additional moved
union file or correctness judgment stops and routes before resolution. The final report
will name surviving R-4.8 and C/B2 cases in every conflict file and carry the complete
34-row end-state table.

The two `.git/refs` rows are external publication scope, not working-tree edit scope.
They may move only after exact-head verification and independent review, using the
dispatch's immutable leases. Lease failure stops the operation. PR bodies, titles,
bases, labels, reviewers, draft states, all other refs, GitHub Actions, merge, tag,
deploy, seal, and release remain Hard OUT.

The `.pending-r415` markers and alias-ABSENT assertions must not return;
`IdMapEntry.children` identity assertions and the three-shape stage-pack-open acceptance
instrument must survive. The struck `staged_path_caveats` premise stays struck.
R-4.18 remains one-level-consistent: no recursion, mapped-root comparison, or
three-level-leaf warning may enter through conflict resolution.

ACTIONS_GIT_REF: no product/test/ref mutation, build, test, publication, PR metadata action, GitHub Actions action, merge, tag, deploy, seal, or release preceded this artifact; only this scope relay and its append-only INDEX row are written at this hop
FINAL_GIT_STATUS_SHORT: C worktree clean at b8083be8529a97d1d3d5931a2c7b308335bbd09c and B2 worktree clean at 3762f3722a1fcebfbaa25921c31ca2f10df4ddf4 before filing; shared docs checkout retains unrelated pre-existing untracked relay state, preserved

CARRY LIST:
- `.relays/s4/s4-floor-impl/REVIEW-FOLD-SCOPE-IMPLEMENTER-CB2-RESTACK-POST-R48-20260811-001434.md` -> `s4-floor.planner`
- five conflict files and two explicit draft refs -> in; all other paths and actions -> out
- C first, B2 immediate; per-hunk reconciliation; release hold ABSOLUTE
