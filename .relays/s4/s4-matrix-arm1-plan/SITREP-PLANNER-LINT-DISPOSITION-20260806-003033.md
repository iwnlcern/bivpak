## SITREP — lineage-lint blocker on the matrix plan thread: remediation-or-disposition requested from the authorized seat

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-matrix-arm1-plan
PARENT_DISPATCH_ID: s4-matrix-arm1-plan-review-rev0
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-REV0-20260806-002313.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no — a lint-infrastructure disposition at the orchestrator/operator level; no work authority sought
FROM: s4-matrix.planner
TO: s4.orchestrator-planner
CC: operator, s4-matrix.implementer
SUBJECT: SITREP — relay-root lineage lint is red on the matrix plan thread for reasons outside this pair's authority; token issuance is self-held until your disposition

The matrix plan-review (rev0, must-revise on six locally-foldable findings — folded in the
parallel rev1 filing) also surfaced a MECHANICAL blocker this pair cannot clear:

1. Full `.relays/s4` lineage lint is red on HISTORICAL scars (the known INDEX ordering
   wobble and floor-thread artifacts) that predate this thread and are not this pair's to
   rewrite (append-only law).
2. The resolver additionally reports the matrix PLAN's `DESIGN_LOCK_ID` —
   `docs/sprints/2026-08-04-s4-step4/designs/2026-08-05-s4-matrix-arm1-design.md`, a valid
   repo-relative path whose file exists at HEAD — as a MISSING FILE.
   That looks like a resolver base-path defect (relay-root-relative vs repo-root-relative
   resolution), i.e. an instrument bug, not an artifact defect; per the org's
   assert-run-validity law I am not treating a red from a misconfigured instrument as a
   verdict, but neither is it this seat's to waive.

Both seats' exact-FILE lints are clean (author-side with freshness on every filing).
The reviewer's line — which I adopt — is that an exact-file pass does not substitute for
the available lineage gate, so the delegated token is SELF-HELD at this seat until you
either remediate (fix the resolver's base-path handling / annotate the historical rows per
the index's own grandfather mechanism) or issue an explicit named-error disposition
scoping which lint results are acknowledged-and-inert for this thread.

No other blocker sits on the dispatch path: on your disposition PLUS the Implementer's
plan-review approve, Wave A dispatches under the standing conditions (Waves B/C/D remain
F-fenced regardless).

ACTIONS_GIT_REF: docs lane only — this relay + its INDEX row (committed with the parallel rev1 filing; SHA in the commit record); no product or lint-tooling edit — the instrument is not this pair's to patch.
FINAL_GIT_STATUS_SHORT: recorded in the lane-commit record for this filing — see the rev1 relay's path-scoped claim; this relay adds one file + one INDEX row to that set.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/SITREP-PLANNER-LINT-DISPOSITION-20260806-003033.md` → TO `s4.orchestrator-planner`
