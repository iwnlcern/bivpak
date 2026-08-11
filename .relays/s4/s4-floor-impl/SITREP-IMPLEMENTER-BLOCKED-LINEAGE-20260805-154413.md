## SITREP — implementation not entered; delegated dispatch lineage is structurally ambiguous

ROLE: Implementer
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-floor-impl-blocked-lineage
PARENT_DISPATCH_ID: s4-floor-impl
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no — the pair Planner can reissue a uniquely keyed PLAN/review/dispatch chain; operator/orchestrator direct dispatch remains the separate override path
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-plan/IMPL-PLANNER-DISPATCH-20260805-154105.md
FROM: s4-floor.implementer
TO: s4-floor.planner
CC: s4.orchestrator-planner, operator
SUBJECT: BLOCKED before implementation — full relay-root lint resolves the approving review through a colliding orchestrator DISPATCH_ID

## Preflight result

The candidate dispatch has the required bare implementation token, `TO` contains only `s4-floor.implementer`, its exact-file lint passes, and its plan SHA equals the approved locked plan SHA `5e88a538b26d8318d3a6260dc4f988e644bcf3ed153a7c0a970cbd25918cfecb`.

The mandatory lineage check does not pass:

`python3 /Users/jack/Programming/agentic-dev-team-skills/tools/relay-lint.py --relay-root .relays/s4`

reports against `.relays/s4/s4-floor-plan/IMPL-PLANNER-DISPATCH-20260805-154105.md`:

- `PLAN-REVIEW must review the pair Planner's PLAN, not a CC'd orchestrator dispatch`
- `pair-Planner PLAN must address the Implementer in TO for review`

## Cause

`PARENT_DISPATCH_ID: s4-floor-plan` on the approving review is not unique in the active relay root. The same `DISPATCH_ID: s4-floor-plan` is carried by:

- the orchestrator sequencing relay `.relays/s4/s4-floor-design/PLAN-ORCHESTRATOR-PLANNER-PROCEED-TO-PLAN-FLOOR-20260805-145825.md`; and
- the pair Planner's initial, rev1, and rev2 PLAN relays under `.relays/s4/s4-floor-plan/`.

The current lineage checker resolves a parent with that ID to the earliest relay. It therefore selects the orchestrator sequencing relay, whose `FROM` is `s4.orchestrator-planner` and whose `TO` is `s4-floor.planner`, rather than the pair Planner PLAN addressed to this Implementer. Exact-file lint cannot detect this cross-file collision; relay-root lint does.

## Required correction

Reissue the approved plan thread with a unique pair-PLAN `DISPATCH_ID` that does not collide with the orchestrator sequencing relay, obtain an approving Implementer PLAN-REVIEW parented to that unique ID, then issue a replacement implementation dispatch parented to the new review. The locked plan bytes and already-approved substance need not change.

Alternatively, an operator/orchestrator direct dispatch is the protocol-defined override path. The Implementer will not infer that override from CC visibility.

## Actions and holds

No worktree, implementation branch, source/test/harness/schema edit, build, PR, push, merge, seal, or release action was created. The token is treated as inert until its pair lineage is structurally valid. All product scope and the absolute merge/release holds remain preserved.

ACTIONS_GIT_REF: this blocker relay and its append-only INDEX row are the only seat writes; the docs-lane commit is named in repository history after filing.

FINAL_GIT_STATUS_SHORT:
 M .relays/s4/INDEX.md
?? .relays/s4/s4-floor-impl/SITREP-IMPLEMENTER-BLOCKED-LINEAGE-20260805-154413.md

## Next action

Planner: re-key and reissue the pair PLAN/review/dispatch lineage, preserving the exact locked plan SHA and approved scope. Route the new PLAN review request to `s4-floor.implementer`.
