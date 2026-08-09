## MERGE-GATE (condition-4 executor token) — Slice A #21 is OPERATOR-AUTHORIZED; all four conditions met; master carried the authorization down the bridge (`022707`). Per the token grammar (B1 precedent), the bare condition-4 token is valid only FROM an orchestrator-planner TO one implementer, so I issue it to you now. Re-verified at THIS seat: A's tip `33153137` is unmoved and merges CLEAN into the current `main` tip `e8acb6a` (merge-tree exit 0, zero conflict markers; A is one commit on B1, already in main). Merge SLICE A ALONE into current `main`. Merge ≠ release; the release hold is ABSOLUTE.

ROLE: Orchestrator Planner
PHASE: MERGE-GATE
AUTHORITY: merge-gated
DISPATCH_ID: s4-floor-a-merge-exec
PARENT_DISPATCH_ID: s4-floor-a-merge-gate
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: DISCHARGED for slice A — the operator granted condition 4 (2026-08-09); master carried it down the bridge (`022707`); this relay is the sanctioned in-team hop that hands you the token. The release hold remains a SEPARATE, still-closed gate — merge is not release.
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: ../../../pdc/master/relays/s4-build-standup/MERGE-GATE-ORCHESTRATOR-PLANNER-SLICE-A-AUTHORIZED-OPERATOR-GRANT-CARRIED-20260809-022707.md
FROM: s4.orchestrator-planner
TO: s4-floor.implementer
CC: operator, s4.orchestrator-reviewer, master.orchestrator-planner
SUBJECT: condition-4 token — merge slice A #21 (33153137) into current main; slice A alone; re-verify clean at the execution tip

## The token and its exact scope

Slice A (`33153137`, PR #21, `s4-floor/a-floor-core`) has all four merge-bar conditions met:
1+2 by s4 (team-of-5 panel + targeted re-check at the bytes, byte-confirmed at this seat), 3 by master
(condition-3 merge-ready verify, `020923`), 4 by the operator (authorization carried in master's
`022707`). CI-leg (a) governs. Second in the operator's wave (after B1, merged).

You are the slice-A executor. The bare condition-4 token on its own line below authorizes you — and
only you — to merge slice A into `main`:

DISPATCH MERGE

## Execution conditions (yours at merge time)

- **Re-verify clean at the ACTUAL merge tip.** `main` advances on the docs lane; I re-verified clean at
  `e8acb6a` moments ago, but re-run the clean-check against `main` as it stands when you merge — never a
  remembered tip.
- **One commit stacked on B1** (already in `main`) — the merge brings exactly slice A's single commit,
  over paths disjoint from the docs-lane advance. No conflict expected (merge-tree exit 0, zero markers).
- **STOP and route up on any surprise conflict** — do not resolve one silently; a conflict would
  contradict the disjoint-path property.
- **Route the resulting merge commit SHA UP to me** after the merge, to close condition-3-of-record.

## What is NOT authorized

Scope is SLICE A ALONE. NOT authorized by this token: slice C (waits on B2 readiness per the
C→B2-immediate election), B2's merge (resumes build under the ratified defer — separate relay this
turn), matrix Wave-A (owes its docs-lane INDEX refresh). Do not fold, batch, or ride any other
candidate on this merge.

## Release

Merge ≠ release. Landing slice A on `main` releases nothing. The operator's release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — read-only re-verify at this seat (rev-parse main/A tip; merge-base --is-ancestor B1 ⊂ main; git merge-tree --write-tree main 33153137 = exit 0, zero conflict markers). This relay + its INDEX row ride one explicit-path docs-lane commit; the MERGE itself is your act under this token, not mine.
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to this relay + .relays/s4/INDEX.md.

CARRY LIST:
- `.relays/s4/s4-floor-impl/MERGE-GATE-ORCHESTRATOR-PLANNER-SLICE-A-CONDITION-4-TOKEN-ISSUED-EXECUTOR-20260809-023857.md` → `s4-floor.implementer`
- slice A #21 merge commit SHA (after the merge) → `s4.orchestrator-planner` → master, to close condition-3-of-record
- scope reminder: SLICE A ALONE; C waits on B2, B2 resumes build, matrix separate — none ride this token
