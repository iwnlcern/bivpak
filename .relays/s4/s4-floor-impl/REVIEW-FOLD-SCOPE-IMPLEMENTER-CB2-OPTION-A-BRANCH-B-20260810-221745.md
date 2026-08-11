## REVIEW-FOLD SCOPE — corrected CB2 Option A Branch B is all-IN; five product/test paths declared before the first edit

ROLE: Implementer
PHASE: REVIEW-FOLD
AUTHORITY: fold-in-only
DISPATCH_ID: s4-floor-impl-2-cb2-option-a-branch-b-scope
PARENT_DISPATCH_ID: s4-floor-impl-2-cb2-option-a-branch-b
RUN_ID: s4
TASK_ID: B2
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — the combined re-check, fresh paired hand-up, condition-3, and operator paired condition-4 remain downstream; the release hold remains ABSOLUTE
DESIGN_LOCK_ID: m2-addendum11-422d451b-lock-20260810
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/IMPL-PLANNER-CB2-OPTION-A-BRANCH-B-CORRECTED-DISPATCH-IMPL-TOKEN-20260810-220856.md
RELATED_CONTEXT: .relays/s4/s4-floor-impl/SITREP-IMPLEMENTER-CB2-OPTION-A-CONTRACT-CONTRADICTION-BLOCKER-20260810-220519.md
FROM: s4-floor.implementer
TO: s4-floor.planner
CC: s4.orchestrator-planner, operator, s4.orchestrator-reviewer, m-2.planner
SUBJECT: FOLD_SCOPE ALL-IN — Branch B is bounded to Claude identity semantics and five test/consumer surfaces; Codex, shared rewrite, collector source, and harness remain untouched

FOLD_SCOPE:
- src/adapters/claude_code/install.cpp -> in
- tests/test_adapter_claude_install.cpp -> in
- tests/test_adapter_claude_collect.cpp -> in
- tests/test_pack.cpp -> in
- tests/test_sessions.cpp -> in
FOLD_SCOPE_RESULT: all-in

The corrected token's six authorized paths were resolved before the first product or
test edit. The five paths above are the actual fold: Claude stops minting child IDs
that name no artifact, emits identity-valued `IdMapEntry.children`, removes the
Claude-only `agentId` alias-harvest/needling arm and its now-dead shape guard, and
retargets the old-contract tests plus the standing pack/open and caveat consumers.

`harness/bivharness/e3.py` is conditionally authorized only if an anchored collector
changes. Neither collector production source is part of this fold, so that condition is
not triggered and the harness path will not be edited. `src/adapters/rewrite_common.cpp`
stays byte-identical: its shared boundary-aware rewrite and strict substring verification
continue to govern session IDs, message UUIDs, and declared child-ID pairs. Codex stays
byte-identical because its minted child ID names the written rollout artifact.

The test fixture basis covers flat bare-hex, flat slug-hex, and nested bare-hex under
`subagents/<wf>/`. Surviving L-1/L-2 tests will be unhidden and inverted to the ruled
identity contract; no `.pending-r415` marker will remain. The standing pack/open proof
will require restored parent references to equal the actual on-disk subagent stems, and
the sessions consumer proof will require identity-valued children to make the staged
path caveat findable.

Hard OUT remains X-1/the three-level slice E, R-4.18 widening, WSL/A11, R-4.16, sealed
A9 member shape, `.github/**`, merge, tag, deployment, seal, and release. Remote CI is
not invoked or inspected; local Ubuntu 24.04 linux/amd64 Docker remains the Linux proof.

ACTIONS_GIT_REF: no product/test edit, build, test, PR mutation, push, GitHub Actions action, merge, tag, deploy, seal, or release preceded this artifact; only this scope relay and its append-only INDEX row are written at this hop
FINAL_GIT_STATUS_SHORT: product worktree clean at e0d6c1994e286291cc7ab3439228edbb65f048a4 before filing; shared docs checkout carries unrelated pre-existing untracked relay files, which remain untouched

CARRY LIST:
- `.relays/s4/s4-floor-impl/REVIEW-FOLD-SCOPE-IMPLEMENTER-CB2-OPTION-A-BRANCH-B-20260810-221745.md` -> `s4-floor.planner`
