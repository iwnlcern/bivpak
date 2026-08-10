## SITREP — the complete B2 amend VERIFIED at the bytes at 6a8ea75 (I-3 key symmetry real at all three call sites; lock-in test genuinely inverted incl. an ESCAPED-key fixture; F2 parent map keyed on a prepared parent; F3 present). Requesting the FOURTH targeted re-panel — with ONE cell flagged for explicit grading: the admitted-session/NOT-in-image-parent path now mechanically refuses, and that election is untested by design.

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-floor-impl-2-b2-fourth-repanel-request
PARENT_DISPATCH_ID: s4-floor-impl-2-b2-i3-amend-fold
RUN_ID: s4
TASK_ID: B2
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: yes — the fourth targeted re-panel is the bar-readiness gate (M-4 must hold FULLY); merge and release remain the operator's alone and the release hold is ABSOLUTE
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/SITREP-IMPLEMENTER-B2-I3-F2-F3-AMEND-COMPLETE-20260809-195459.md
FROM: s4-floor.planner
TO: s4.orchestrator-planner
CC: operator, s4.orchestrator-reviewer, s4-floor.implementer
SUBJECT: REQUEST — convene the fourth targeted re-panel at exact PR #23 head 6a8ea75a2d7ae072839940e69b16f6393c80ac32; my byte verification below, plus one flagged cell the panel must grade explicitly

## Verified at the bytes at this seat (not on the report's word)
- remote `origin/s4-floor/b2-torn-tail` and draft PR #23 = exact `6a8ea75`; exactly ONE
  commit over `ec9a2db`; subject preserved; amend wave `f9675ea..6a8ea75` = exactly the
  four authorized paths; `rewrite_common.hpp` UNCHANGED (the conditional row unused).
- **I-3 closed symmetrically:** all THREE `JsonValueRewriter` call sites now pass
  `decode_keys=true` — the jsonl rewrite arm (`rewrite_common.cpp:841`), the
  whole-document arm (`:923`), and the verify/values arm (`:1051`). Keys decode, rewrite
  under the pair-set (longest-source-first applies), and are scanned.
- **The lock-in test is genuinely inverted:** `key-must-not-change` survives only as the
  VALUE; the assertions now require the origin-path KEY rewritten to the workspace at both
  the unit level (`test_adapter_claude_install.cpp:484-487`) and the real-install level
  (`:538-542`), and the fixture includes an ESCAPED key (`\/ws\/proj`) — the
  encoded-forms falsification this family demanded. The matching Codex lock-in was
  inverted as the necessary consequence of the shared rule.
- **F2:** the parent id-map entry is added exactly when a PREPARED parent with the matching
  primary exists (`codex/install.cpp:463-471`) → in-image parents rewrite instead of
  self-refusing; the de-masked fixture carries a real `parent_thread_id`.
- **F3:** the cross-session child-id falsifier exists, sourced from a version-refused
  NONPREPARED manifest row — kill-power against the direct union insert (the implementer's
  mutation run confirms RED on its removal).
- Evidence chain: strict RED→GREEN per finding; scoped independent re-review clean (after
  catching and correcting an intermediate `parent_in_image` misreading against the real
  manifest invariant); fresh post-review host 14/14 (`harness-e2` 178.12s under the 600s
  budget); Docker parity green modulo the standing ruled exceptions; A3 checked-not-asserted
  (no anchored file in the wave).

## ONE cell the fourth panel must grade explicitly (flagged, not folded)
The union inserts EVERY manifest record's parent id (`codex/install.cpp:485-486`), but the
rewrite map covers only PREPARED parents. So an ADMITTED codex session whose own
`parent_thread_id` references a NOT-in-image parent now mechanically REFUSES (id in the
union, never rewritten). Pre-B2 that id silently survived; the ruled fold neither elected
nor tested this outcome — the implementer correctly avoided answering the pre-flagged
definition cell, but the CODE now has a default answer (refusal) for a reachable case
(a collected session whose parent was not collected). The panel should grade: is
refuse-by-default here correct under the family invariant (fail-closed on an origin id),
or an F2-shaped false refusal of legitimate data that needs the definition routed up?
I flag it so M-4's "holds FULLY" verdict covers the cell rather than sliding past it.

## The request
Convene the FOURTH targeted re-panel at exact `6a8ea75a2d7ae072839940e69b16f6393c80ac32`
— security + correctness + tests, cold lenses, cumulative `ec9a2db..6a8ea75`, M-4 must
hold FULLY (I-3 closed with no key-arm leak; F2 self-refusal gone; F3 covered; the flagged
cell graded). On its pass B2 is bar-ready and the C→B2-immediate pair proceeds to
condition-3s + per-candidate operator authorizations. R-4.8 and the disclosed Minors
remain separately carried. Merge/release the operator's; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — read-only git verification at 6a8ea75 (rev-parse/log/diff/show); this relay + its INDEX row ride one explicit-path docs-lane commit whose SHA lands in history after filing
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to the two docs-lane paths named above

CARRY LIST:
- `.relays/s4/s4-floor-impl/SITREP-PLANNER-B2-AMEND-VERIFIED-FOURTH-REPANEL-REQUESTED-20260809-195959.md` → `s4.orchestrator-planner`
- PR #23 at exact `6a8ea75a2d7ae072839940e69b16f6393c80ac32` → fourth targeted re-panel (M-4 must hold FULLY; flagged not-in-image-parent cell graded)
- on the panel's pass → B2 bar-ready; C→B2-immediate condition-3s + operator authorizations; merge/release the operator's, hold ABSOLUTE
