## DISPOSITION — master RECEIPTED B2's fourth-re-panel PASS on its merits (I-3 closed, content right) but REFUSED condition-3 on MERGE MECHANICS: the C→B2 pair is stacked on the SUPERSEDED old-slice-A (`798526c`), which never merged — the rebuilt one-commit A (`33153137`) is what landed in `main`, so C and B2 conflict with `main` (11 content conflicts incl. add/add `version_floor.{cpp,hpp}`). I re-verified all of it at the bytes. THE RETURN (mechanical, yours): re-stack C's own delta onto current `main`, re-stack B2's delta onto the new C, suites honestly green, targeted re-verification at the NEW exact SHAs, then fresh condition-3 hand-ups. AND the orphan definition is RULED: refuse-by-default ACCEPTED (fail-closed correct; R-4.9 registers the electable scrub, NOT release-gating). The release hold is ABSOLUTE.

ROLE: Orchestrator Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-floor-impl-2-b2-restack
PARENT_DISPATCH_ID: s4-floor-impl-2-b2-fourth-repanel-disp
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new gate — the orphan cell is CLOSED by master's family ruling (refuse-by-default accepted; R-4.9 the electable fix); the re-stack is the floor's mechanical return; fresh condition-3s + per-candidate operator authorizations follow; the release hold is ABSOLUTE
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: ../../../pdc/master/relays/s4-build-standup/MERGE-GATE-ORCHESTRATOR-PLANNER-B2-CONDITION-3-REFUSED-STALE-BASE-RESTACK-ORPHAN-RULED-R49-20260809-202301.md
RELATED_CONTEXT: docs/sprints/2026-08-04-s4-step4/reviews/2026-08-09-s4-floor-b2-fourth-repanel-6a8ea75.md (the PASS that stands on content)
FROM: s4.orchestrator-planner
TO: s4-floor.planner
CC: operator, s4.orchestrator-reviewer, s4-floor.implementer
SUBJECT: PLAN — B2 condition-3 refused on stale base (C stacked on superseded old-A); re-stack C→B2; orphan RULED refuse-by-default (R-4.9)

## The refusal is on MECHANICS, not content — I re-verified at the bytes

Master's fourth-re-panel receipt stands: B2's content is right (I-3 closed on all three arms; the PASS
holds). Condition-3 refused because the C→B2 base is stale. Confirmed at this seat:
- old-A `798526c` ⊂ C `ec9a2db`: **YES**;
- old-A `798526c` ⊂ `main`: **NO** — old-A never merged;
- rebuilt new-A `33153137` (the post-panel one-commit head with the six A-BL fixes) ⊂ `main`: **YES**;
- new-A `33153137` ⊂ C: **NO** — the C stack never absorbed the rebuild;
- `git merge-tree main ec9a2db` (C) → **11 content conflicts**, incl. add/add `version_floor.cpp`
  (stages 2+3), and B2 inherits the same base.
Merging as-is would force conflict resolution inside an untested, unpaneled merge commit — exactly what
the bar prevents. This is master's condition-3 doing its job; my hand-up deferred the ancestry check to
it correctly, but note for next time: a stacked candidate's base can be superseded by a REBUILT
predecessor — verify the whole stack merges clean, not just the immediate parent.

## The return (mechanical, yours)

1. **Re-stack C:** replay C's OWN logical delta onto current `main`. Old-A's content is already in `main`
   via `33153137`, so C's rebase drops the old-A content naturally (keep C's own changes only).
2. **Re-stack B2:** replay `6a8ea75`'s one-commit delta onto the new C head.
3. **Suites honestly green** on both heads — host + the local Ubuntu 24.04 amd64 Docker parity suite.
4. **Targeted re-verification at the NEW exact SHAs.** The four B2 panels' + C's review findings carry
   logically, but panel-at-exact-SHA is the bar — the record must bind to the bytes that merge. Structure
   a TARGETED recheck (not from-scratch) under your local gates: re-confirm at the new SHAs that the fold
   set (C's delta; B2's I-3/F2/F3 + TIMEOUT-600) is intact, fences live, scope clean, and the merge-tree
   into current `main` is conflict-free. On any surprise, route up.
5. **Fresh condition-3 hand-ups** for the re-stacked C→B2 pair, in the elected order (C first, B2
   immediately after).

## The orphan definition — RULED (closes the routed cell)

Master ruled: **not-in-image Codex parent → refuse-by-default ACCEPTED.** A not-in-image
`parent_thread_id` in a session's own installed bytes IS origin identity; fail-open would re-leak it
(pre-B2 it silently did), so B2's fail-closed refusal is the correct end state — **the id is NEVER
dropped from the union.** The usability cost (orphan Codex sessions refuse) is registered as **R-4.9**:
prepare-time scrubbing of the dangling reference at pack is the electable fix, operator-electable as
SEPARATE work, NOT release-gating (fail-closed is safe). Keep the refusal detail honest so users can act.
This cell does NOT gate the re-stacked B2 — do not fold a scrub into the re-stack.

## Scope note
The re-stack replays EXISTING deltas onto a fresh base — no new logical change, no scope expansion. If a
rebase surfaces a genuine semantic conflict (not just old-A content dropping), stop and route it up.
R-4.8 (matrix carrier) and the disclosed Minors remain separate. Merge/release the operator's; the
release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — read-only re-verification (merge-base --is-ancestor ×4: old-A⊂C, old-A⊄main, new-A⊂main, new-A⊄C; merge-tree main C = 11 conflicts incl. version_floor add/add). This relay + its INDEX row ride one explicit-path docs-lane commit whose SHA lands after filing; the re-stack is your act.
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to this relay + .relays/s4/INDEX.md.

CARRY LIST:
- `.relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-B2-CONDITION-3-REFUSED-RESTACK-C-B2-ORPHAN-RULED-20260809-204023.md` → `s4-floor.planner`
- B2 condition-3 REFUSED on stale base (C stacked on superseded old-A 798526c; new-A 33153137 in main; 11 conflicts) — re-verified at bytes → re-stack C onto current main, B2 onto new C, suites green, targeted re-verification at NEW SHAs, fresh condition-3s
- B2 fourth-re-panel PASS stands on CONTENT (I-3 closed) — not reopened by the re-stack
- orphan RULED: refuse-by-default ACCEPTED (fail-closed; id never dropped from union); scrub = R-4.9 electable/NOT release-gating; do NOT fold it into the re-stack
- release hold ABSOLUTE
