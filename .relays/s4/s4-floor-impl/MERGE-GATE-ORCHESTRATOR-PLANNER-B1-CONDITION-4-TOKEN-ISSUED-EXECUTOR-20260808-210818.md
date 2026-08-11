## MERGE-GATE (condition-4 executor token) — B1 #15 is OPERATOR-AUTHORIZED and all four conditions are met; master carried the authorization down the bridge (`205500`). Per the token grammar the bare condition-4 token is valid only FROM an orchestrator-planner TO one implementer, so I issue it to you now. Re-verified at THIS seat: B1 tip `ff63e521` is unmoved and merges CLEAN into the current `main` tip `ab463d0` (merge-tree exit 0, zero conflict markers, disjoint paths). Merge B1 ALONE into current `main`. Merge ≠ release; the release hold is ABSOLUTE.

ROLE: Orchestrator Planner
PHASE: MERGE-GATE
AUTHORITY: merge-gated
DISPATCH_ID: s4-floor-b1-merge-exec
PARENT_DISPATCH_ID: s4-floor-b1-merge-gate
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: DISCHARGED for B1 — the operator granted condition 4 (typed the go 2026-08-08); master carried it down the bridge (`205500`); this relay is the sanctioned in-team hop that hands the executor its token. The release hold remains a SEPARATE, still-closed gate — merge is not release.
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: ../../../pdc/master/relays/s4-build-standup/MERGE-GATE-ORCHESTRATOR-PLANNER-B1-DISPATCH-MERGE-OPERATOR-TOKEN-CARRIED-20260808-205500.md
FROM: s4.orchestrator-planner
TO: s4-floor.implementer
CC: operator, s4.orchestrator-reviewer, master.orchestrator-planner
SUBJECT: condition-4 token — merge B1 #15 (ff63e52) into current main; B1 alone; re-verify clean at the execution tip

## The token and its exact scope

B1 (`ff63e52`, PR #15, `s4-floor/b1-codex-liveness`) has all four merge-bar conditions met:
1+2 by s4 (full team-of-5 panel + targeted recheck at `ff63e52`, local Docker green `052818`,
reviewers CC'd); 3 by master (condition-3 merge-ready verify at the bytes, `203731`); and 4 by
the operator (authorization carried down the bridge in master's `205500`). CI-leg (a) governs:
local Docker green is the Linux signal, a cosmetic remote-Actions red blocks nothing.

You are the B1 executor. The bare condition-4 token on its own line below authorizes you — and
only you — to merge B1 into `main`:

DISPATCH MERGE

## Execution conditions (yours at merge time)

- **Re-verify clean at the ACTUAL merge tip.** `main` is advancing on the docs lane
  (`cc0a7f0`→`ab463d0` since master's check; I re-verified clean at `ab463d0` moments ago). Do
  NOT trust a remembered tip — re-run the clean-check against `main` as it stands when you merge.
- **Real, non-ff merge over DISJOINT paths.** B1's product diff and main's docs-lane advance do
  not intersect (I checked: merge-tree exit 0, zero conflict markers). No conflict is expected.
- **STOP and route up on any surprise conflict** — do not resolve one silently. A conflict here
  would contradict the disjoint-path property and must be surfaced, not papered over.
- **Route the resulting merge commit SHA UP to me** after the merge, so master's
  condition-3-of-record closes against the landed bytes. I carry it up the bridge.

## What is NOT authorized

Scope is B1 ALONE — one authorization, one candidate. NOT authorized by this token: slice A #21
(condition-3 HELD, team-of-5 paneling at `798526c`), slice C #22 (I-3 sequencing gated — master's
`204800` land-C-and-B2-as-a-unit ruling awaits operator ratification), matrix Wave-A `cb1f6254`
(separate stack; owes a `.relays/s4/INDEX.md` docs-lane refresh before it is token-eligible). Do
not fold, batch, or ride any other candidate on this merge.

## Release

Merge ≠ release. Landing B1 on `main` releases nothing. The operator's release hold is ABSOLUTE
and untouched by this token.

ACTIONS_GIT_REF: no product/test edits at this seat — read-only re-verify at this seat (rev-parse main/B1 tip; merge-base --is-ancestor B1 ⊂ 798526c; git merge-tree --write-tree main s4-floor/b1-codex-liveness = exit 0, tree be6a4a06, zero conflict markers). This relay + its INDEX row ride one explicit-path docs-lane commit; the MERGE itself is your act under this token, not mine.
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to the two docs-lane paths (this relay + .relays/s4/INDEX.md).

CARRY LIST:
- `.relays/s4/s4-floor-impl/MERGE-GATE-ORCHESTRATOR-PLANNER-B1-CONDITION-4-TOKEN-ISSUED-EXECUTOR-20260808-210818.md` → `s4-floor.implementer`
- B1 #15 merge commit SHA (after the merge) → `s4.orchestrator-planner` → master, to close condition-3-of-record
- scope reminder: B1 ALONE; slice A held, slice C I-3-gated, matrix separate — none ride this token
