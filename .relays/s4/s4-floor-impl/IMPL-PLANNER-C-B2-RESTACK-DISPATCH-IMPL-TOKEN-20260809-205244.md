## IMPL DISPATCH — re-stack C→B2 onto current main: the LIVE token. Master refused B2's condition-3 on MECHANICS (the stack sits on the SUPERSEDED old-A `798526c`; the rebuilt A `33153137` is what merged), content PASSES stand. Replay C's own delta onto current main, B2's delta onto the new C; suites green on BOTH heads; republish both PRs; my targeted re-verification at the NEW SHAs follows, then fresh condition-3s. The orphan cell is RULED closed (refuse-by-default; R-4.9 electable; NO scrub here).

ROLE: Planner
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: s4-floor-impl-2-cb2-restack
PARENT_DISPATCH_ID: s4-floor-pair-plan-review-approve
RUN_ID: s4
TASK_ID: B2
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
SCOPE_DIFF:
- harness/bivharness/compare.py -> in
- harness/bivharness/e3.py -> in
- harness/bivharness/scenario.py -> in
- harness/CMakeLists.txt -> in
- harness/scenarios/open-consent-no.json -> in
- harness/scenarios/open-consent-per-agent.json -> in
- harness/scenarios/open-deny-default.json -> in
- harness/selftest/test_compare.py -> in
- harness/selftest/test_e3_asserts.py -> in
- harness/selftest/test_envelope.py -> in
- schemas/biv-exit-map.v1.json -> in
- schemas/biv-json-envelope.v1.schema.json -> in
- src/adapters/adapter.hpp -> in
- src/adapters/claude_code/claude_code.cpp -> in
- src/adapters/claude_code/install.cpp -> in
- src/adapters/codex/codex.cpp -> in
- src/adapters/codex/install.cpp -> in
- src/adapters/rewrite_common.cpp -> in
- src/adapters/rewrite_common.hpp -> in
- src/core/open/render.cpp -> in
- src/core/open/sessions.cpp -> in
- src/core/open/sessions.hpp -> in
- src/core/pack/pack.cpp -> in
- src/core/report/envelope.cpp -> in
- src/core/support/error.cpp -> in
- src/core/support/error.hpp -> in
- tests/test_adapter_claude_collect.cpp -> in
- tests/test_adapter_claude_install.cpp -> in
- tests/test_adapter_codex_collect.cpp -> in
- tests/test_adapter_codex_install.cpp -> in
- tests/test_cli.cpp -> in
- tests/test_envelope.cpp -> in
- tests/test_pack.cpp -> in
- tests/test_sessions.cpp -> in
SCOPE_DIFF_RESULT: all-in
SCOPE_ROW_EVIDENCE:
- harness/bivharness/compare.py -> member of slice C's paneled 24-path range (git diff --name-only 798526c..ec9a2db, verified at this seat 20260809-205244)
- harness/bivharness/e3.py -> member of B2's paneled 16-path range (git diff --name-only ec9a2db..6a8ea75, same verification)
- harness/bivharness/scenario.py -> slice C paneled range (same verification)
- harness/CMakeLists.txt -> B2 paneled range (the operator-ruled TIMEOUT 600 line)
- harness/scenarios/open-consent-no.json -> slice C paneled range
- harness/scenarios/open-consent-per-agent.json -> slice C paneled range
- harness/scenarios/open-deny-default.json -> slice C paneled range
- harness/selftest/test_compare.py -> slice C paneled range
- harness/selftest/test_e3_asserts.py -> slice C paneled range
- harness/selftest/test_envelope.py -> slice C paneled range
- schemas/biv-exit-map.v1.json -> slice C paneled range
- schemas/biv-json-envelope.v1.schema.json -> slice C paneled range
- src/adapters/adapter.hpp -> both paneled ranges (C fold + B2)
- src/adapters/claude_code/claude_code.cpp -> B2 paneled range
- src/adapters/claude_code/install.cpp -> both paneled ranges
- src/adapters/codex/codex.cpp -> B2 paneled range
- src/adapters/codex/install.cpp -> both paneled ranges
- src/adapters/rewrite_common.cpp -> B2 paneled range (150142 grant lineage)
- src/adapters/rewrite_common.hpp -> B2 paneled range (150142 grant lineage)
- src/core/open/render.cpp -> slice C paneled range
- src/core/open/sessions.cpp -> slice C paneled range
- src/core/open/sessions.hpp -> slice C paneled range
- src/core/pack/pack.cpp -> B2 paneled range
- src/core/report/envelope.cpp -> slice C paneled range
- src/core/support/error.cpp -> slice C paneled range
- src/core/support/error.hpp -> slice C paneled range
- tests/test_adapter_claude_collect.cpp -> B2 paneled range
- tests/test_adapter_claude_install.cpp -> both paneled ranges
- tests/test_adapter_codex_collect.cpp -> B2 paneled range
- tests/test_adapter_codex_install.cpp -> both paneled ranges
- tests/test_cli.cpp -> both paneled ranges
- tests/test_envelope.cpp -> slice C paneled range
- tests/test_pack.cpp -> B2 paneled range
- tests/test_sessions.cpp -> slice C paneled range
HUMAN_GATE_REQUIRED: no — pair-Planner conditional dispatch: orchestrator-delegated conditional dispatch at the initial PLAN dispatch; Implementer plan review = approve (`s4-floor-pair-plan-review-approve`); mechanical SCOPE_DIFF all-in (rows above = the exact union of the two PANELED ranges; verified at this seat 20260809-205244); no hard trigger — the re-stack replays EXISTING paneled deltas onto a fresh base per master's refusal + the orchestrator's return (`204023`), no new logical change; the orphan cell is CLOSED by master's ruling (refuse-by-default; R-4.9 electable, NOT folded here). Merge and release remain the operator's alone; the release hold is ABSOLUTE.
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-B2-CONDITION-3-REFUSED-RESTACK-C-B2-ORPHAN-RULED-20260809-204023.md
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: s4.orchestrator-planner, operator
SUBJECT: the live token for the C→B2 re-stack onto current main — replay-only, delta-equality is the acceptance bar, semantic conflicts are stop-and-route

Master refused B2's condition-3 on MECHANICS only (the fourth-re-panel content PASS
stands): C `ec9a2db` sits on old-A `798526c`, which never merged — the rebuilt A
`33153137` did, so C/B2 conflict with `main` (master + the orchestrator byte-verified: 11
content conflicts incl. add/add `version_floor.{cpp,hpp}` from old-A's ancestry). The
return is a mechanical re-stack. This token makes it live.

## The re-stack (replay-only; no new logical change)
1. **Re-resolve the ACTUAL `main` tip at execution time** (it advances on the docs lane —
   do not trust a remembered tip) and record it.
2. **Re-stack C:** replay C's OWN one-commit delta (`798526c..ec9a2db`, the paneled 24
   paths) onto current `main`. Old-A's content is already in `main` via `33153137`, so
   old-A ancestry content drops naturally — keep C's own changes only. Preserve C's commit
   subject. Textual conflicts where C's context meets rebuilt-A's changed lines: resolve
   by preserving C's SEMANTICS against new-A's text; **a genuine SEMANTIC conflict (not
   just old-A content dropping or context drift) is a STOP-AND-ROUTE — do not resolve one
   silently.**
3. **Re-stack B2:** replay B2's one-commit delta (`ec9a2db..6a8ea75`, the paneled 16
   paths) onto the new C head. Same subject, same conflict rule.
4. **Delta-equality acceptance (the bar for both heads):** at the new C head, `git diff
   --name-only <new-main-base>..<new-C>` must be a SUBSET of C's 24 paneled paths, and the
   content delta must be C's logical change (nothing new, nothing lost); likewise the new
   B2 head vs new C against B2's 16 paths. Any path outside the SCOPE_DIFF union above is
   a NEW deviation routed up BEFORE proceeding.
5. **Suites honestly green on BOTH heads:** focused sets + the full host suite at each
   head, then the standing local Ubuntu 24.04 `linux/amd64` Docker parity suite (Actions
   unused). The A3 mechanical check runs at each head (B2's replay touches the anchored
   collectors — expect the A3 four-check + both-anchor recapture to RE-FIRE at the new B2
   head if the collector bytes differ from the recaptured hashes; run it, never assert it).
6. **Verify the merge path:** `git merge-tree` of current `main` vs the new C head must be
   conflict-free, and new-C→new-B2 likewise stacked clean.
7. **Republish BOTH PRs** under the standing disposition (force-with-lease: PR #22 → the
   new C head; PR #23 → the new B2 head; PR #23's base stays consistent with the stack).
8. Report per the standing shape with both new exact SHAs. My TARGETED re-verification at
   the new SHAs follows (fold-set intact, fences live, scope clean, merge-tree clean), then
   fresh condition-3 hand-ups for C→B2 in the elected order.

## Bounds
- Replay-only: the union SCOPE_DIFF above is the ceiling; delta-equality is the bar.
- The orphan cell is RULED CLOSED — refuse-by-default stands, the parent id is NEVER
  dropped from the union, and **NO R-4.9 scrub is folded here** (operator-electable
  separate work; keep the refusal detail honest).
- No `manifest.*`, no `.github`, no R-4.8/home-prefix work, no new tests/fixes beyond the
  replayed deltas.

DISPATCH IMPL

ACTIONS_GIT_REF: no product/test edits at this seat — this dispatch relay + its INDEX row ride one explicit-path docs-lane commit whose SHA lands in history after filing; C remains at ec9a2db (PR #22) and B2 at 6a8ea75 (PR #23) pending your re-stack
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state (main holds the two local merges; matrix relays sit untracked); this seat's writes are confined to the two docs-lane paths named above

CARRY LIST:
- `.relays/s4/s4-floor-impl/IMPL-PLANNER-C-B2-RESTACK-DISPATCH-IMPL-TOKEN-20260809-205244.md` → `s4-floor.implementer`
- live token: replay C onto current main, B2 onto new C; delta-equality bar; semantic conflicts stop-and-route; A3 re-fires at the new B2 head if collector bytes move; suites + Docker green; republish #22 + #23
- then my targeted re-verification at the NEW SHAs → fresh condition-3 hand-ups (C first, B2 immediately after)
- orphan cell CLOSED (refuse-by-default; R-4.9 electable, not folded); R-4.8 + Minors separate; merge/release the operator's, hold ABSOLUTE
