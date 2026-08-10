## IMPL DISPATCH — the restack RESUMES on a DERIVED ruling, option 2: the verify-hit cell is NOT an open semantic choice — per-session `verify-hits` IS master's standing B2-1 ruling (145219, carried 220234, sealed by the fourth re-panel's M-4-holds-FULLY pass at exactly those semantics). Rebuilt-A's three tests pin the SUPERSEDED pre-B2 cohort surface incidentally; their PURPOSE (the version-refusal row survives) is preserved by RE-EXPRESSION, not deletion. Amend exactly those three tests inside B2's replay commit; nothing else changes. Objection window CC'd.

ROLE: Planner
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: s4-floor-impl-2-cb2-restack-resume
PARENT_DISPATCH_ID: s4-floor-pair-plan-review-approve
RUN_ID: s4
TASK_ID: B2
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
SCOPE_DIFF:
- tests/test_adapter_claude_install.cpp -> in
- tests/test_adapter_codex_install.cpp -> in
- tests/test_sessions.cpp -> in
SCOPE_DIFF_RESULT: all-in
SCOPE_ROW_EVIDENCE:
- tests/test_adapter_claude_install.cpp -> plan dispatch-scope file set (tests) L33; member of both paneled ranges in the standing 34-row restack union (205244); hosts "Claude rewrite verification preserves a sibling capability refusal"
- tests/test_adapter_codex_install.cpp -> plan dispatch-scope file set (tests) L33; member of both paneled ranges in the standing union; hosts "Codex rewrite verification preserves a sibling capability refusal"
- tests/test_sessions.cpp -> plan dispatch-scope file set (tests) L33; member of slice C's paneled range in the standing union; hosts "Codex session leg preserves a version refusal beside a verify-hit sibling" (verified at this seat 20260809-213224, tests/test_sessions.cpp:655)
HUMAN_GATE_REQUIRED: no — this is a DERIVED disposition, not a fresh election: the cell the blocker names was RULED by master (B2-1 per-session for the origin-leak class, `145219`, carried `220234`) conditional on the sound scan + re-panel confirmation with m-4 — conditions DISCHARGED at the fourth re-panel's M-4-holds-FULLY pass at `6a8ea75` under exactly the per-session semantics. Retaining rebuilt-A's cohort surface (option 1) would silently UNDO that ruling; the three tests predate B2 in the new stack order and pin the superseded surface incidentally (their target was A-BL1's carrier preservation, which survives). Same class as master's own lock-in-inversion ruling: a test pinning superseded semantics is not a constraint on the ruled change. The orchestrator and operator are CC'd with an explicit objection window until the implementer's report — object and the amendment unwinds. Merge and release remain the operator's alone; the release hold is ABSOLUTE.
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/SITREP-IMPLEMENTER-C-B2-RESTACK-SEMANTIC-CONFLICT-BLOCKER-20260809-212704.md
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: s4.orchestrator-planner, operator
SUBJECT: resume the restack — B2's paneled per-session semantics stand (master's ruling); re-express the three rebuilt-A tests inside B2's replay commit; then the full standing sequence from the two clean candidates

Your stop was exactly correct — the token forbade choosing the cell, and you didn't. The
ruling: the cell was never open. Master ruled the origin-leak refusal radius PER-SESSION
(B2-1), the fourth re-panel sealed M-4 at those semantics, and rebuilt-A's three tests —
written when slice A sat BEFORE B2 in the stack — pin the pre-B2 cohort surface only
incidentally: their PURPOSE was A-BL1's guarantee (a version-refusal row survives the
verify-hit gate), which per-session semantics preserve. So: **option 2, bounded.**

## The amendment (inside B2's replay commit at the b6c3fd7 line; the ONLY new logical change)
Re-express EXACTLY the three tests, preserving each one's A-BL1 purpose:
- the VERSION-REFUSAL row: still asserted PRESERVED with its typed reason/detail
  (`not-validated` + basis detail) — the A-BL1 kill-power stays;
- the VERIFY-HIT sibling: now asserted PER-SESSION — reason `verify-hits`, detail
  `origin_path`/`origin_id`, hit counters intact on that session's row; clean siblings
  unaffected (the ruled B2 surface, exactly what the fourth panel passed);
- no test DELETED, no assertion weakened — re-expressed under the ruled semantics, RED
  against any regression of either guarantee.
B2's production bytes keep the paneled resolution you already carried (per-session
`verify_failure_detail`); C's mechanical resolutions at `d6e44d9` stand as executed.

## Delta-equality bar (amended for this resume)
- new-C head `d6e44d9`: unchanged — the 24 paneled paths, already verified.
- new-B2 head: B2's 16 paneled paths PLUS `tests/test_sessions.cpp` (this grant), and
  within the two install-test files the only NEW deltas beyond the paneled 16-path content
  are the re-expressed assertions above. Anything else is a NEW deviation routed up
  BEFORE the edit.

DISPATCH IMPL

## Then (the standing sequence from the two clean candidates)
Amend into B2's single replay commit (one-commit law per head, subjects preserved); the
three-test reproduction must go GREEN and the full host suite honestly green at the new
B2 head (C `d6e44d9` is already host-green — rerun only if the amendment forces a
restack); A3 mechanical check at the final B2 head (collector bytes were byte-identical
at b6c3fd7 — re-run at the amended head, never assert); both heads' local Ubuntu 24.04
`linux/amd64` Docker suites; `git merge-tree` acceptance (main→new-C conflict-free,
new-C→new-B2 stacked clean); republish PR #22 → new C and PR #23 → final B2 under the
standing disposition; report with both exact SHAs. My targeted re-verification at the new
SHAs follows, then fresh condition-3 hand-ups (C first, B2 immediately after). Orphan
R-4.9, R-4.8, and the Minors stay untouched. Merge/release the operator's; the release
hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — this dispatch relay + its INDEX row ride one explicit-path docs-lane commit whose SHA lands in history after filing; the clean candidates remain at C d6e44d9 / B2 b6c3fd7 (local) and PRs #22/#23 at ec9a2db/6a8ea75 (remote) pending your resume
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to the two docs-lane paths named above

CARRY LIST:
- `.relays/s4/s4-floor-impl/IMPL-PLANNER-CB2-RESTACK-RESUME-PER-SESSION-RULED-DISPATCH-IMPL-TOKEN-20260809-213224.md` → `s4-floor.implementer`
- DERIVED ruling: per-session stands (master B2-1 + fourth-panel seal); re-express the three rebuilt-A tests (purpose preserved, no deletion); objection window open until your report
- then host+Docker green both heads, merge-trees clean, republish #22/#23 → my targeted re-verification → fresh condition-3s (C first, B2 immediate)
- orphan R-4.9 / R-4.8 / Minors untouched; merge/release the operator's, hold ABSOLUTE
