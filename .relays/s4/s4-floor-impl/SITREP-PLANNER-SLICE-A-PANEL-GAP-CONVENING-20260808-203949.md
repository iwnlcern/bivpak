## SITREP — CI-leg (a) acknowledged; slice-A publication unblocked. But I CANNOT confirm slice A's panel is complete: it was never adversarially paneled (only E1/E2-verified + a single delta review + local-green). Convening the slice-A team-of-5 panel at 798526c now; hold its condition-3 hand-up until it clears.

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-floor-impl-2-a-panel-gap
PARENT_DISPATCH_ID: s4-floor-impl-2-ci-leg-a
RUN_ID: s4
TASK_ID: A
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: yes — slice A's condition-3 hand-up presumes a completed panel that did not happen; the merge-readiness confirmation you asked for cannot be given until the panel clears
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-CI-LEG-A-DOWN-PUBLICATION-UNBLOCKED-MERGE-SEQUENCE-20260808-202713.md
FROM: s4-floor.planner
TO: s4.orchestrator-planner
CC: operator, s4.orchestrator-reviewer, s4-floor.implementer
SUBJECT: CORRECTION — slice A has no adversarial panel; running it now at 798526c before any condition-3 hand-up

## CI-leg (a) received and applied
Operator ruled (a): merge on local-green, remote Actions non-required, count gate off the
critical path. Slice A's `152458` publication question is RESOLVED — PR #21 is already at
798526c and stays published; a cosmetic remote red is not a blocker. No dispute.

## The correction you need before routing slice A
You asked me to "confirm its panel + recheck are complete and it is local-green." I can
confirm TWO of the three, and must NOT confirm the third:
- **local-green: YES** — the implementer's `160811` local Ubuntu 24.04 amd64 run at 798526c
  (two Linux gate defects fixed, nine receipts refreshed, Docker/Rosetta deltas disclosed).
- **one-commit + in-universe scope: YES** — re-verified at the bytes now:
  `ff63e52..798526c` = exactly one commit, 24 paths, all in-universe.
- **adversarial panel: NO — it never ran.** The reviews directory holds
  `2026-08-07-s4-floor-slice-c-panel-eadc88f.md` and
  `2026-08-08-s4-floor-slice-b2-panel-54a6c54.md` but NO slice-A panel. Slice A received
  my E1/E2 verification (`152458`) + ONE independent delta review (Ready-YES, zero
  findings) + local CI. The `091452` relay literally said "panel requested"; that request
  was overtaken by the publication question and the C/B2 work, and never fulfilled.

I will not paper a single delta review over as "panel complete." That would be false, and
the evidence says it would be unsafe: the team-of-5 panel found REAL Criticals on BOTH
slice C and slice B2 that single reviews missed — including an origin-disclosure store-leak
family master ruled as ONE invariant, one vector of which (the JSON-object-key leak, B2
re-panel tests I-3) is INHERITED, pre-existing at base ec9a2db (slice C's head) and
therefore present in the lineage slice A sits under. Slice A's own diff touches
`adapter.hpp`, both `install.cpp`, and `sessions.cpp`, so it is squarely on the
install/admission surface a panel must grade.

## What I am doing now (no permission needed — it is the pair-planner lifecycle)
Convening the slice-A team-of-5 adversarial panel (security, correctness, tests,
performance, idiom) over `ff63e52..798526c` at exact `798526c`, cold read-only lenses on
the committed bytes, focused on slice A's actual surface: the Addendum-7 version-floor
admission (grammar-before-ordering, below-MIN/newer-than-host/unorderable closed reason
spellings, fail-closed on unreadable host version), untrusted version-string parsing, the
allowlist deletion's admission-equivalence, and the §A7.10 mirror check's soundness — plus
whether any origin-disclosure vector is present at this head.

## The ask
Do NOT route slice A's condition-3 up yet. On the panel result I will either (a) confirm
merge-ready with the panel record, or (b) route a fold. B1 (#15) proceeding first as you
staged is unaffected — its panel + recheck ARE complete (conditions 1+2 met), so its
condition-3 hand-up stands. Slice C (#22) condition-3 is banked, BUT note the inherited
JSON-key leak (I-3) is in the origin-disclosure family master ruled as one invariant and
is present at slice C's head — flagging so C's merge and the family's resolution stay
coherent; that is master's/your call, not a floor block. B2 (#23) continues its second
fold cycle (the rewrite/verify re-panel found M-4 does not yet hold — separate relay).

ACTIONS_GIT_REF: no product edits at this seat — read-only git verification (ff63e52..798526c topology/scope) + five read-only panel lenses at 798526c; this relay + its INDEX row ride one explicit-path docs-lane commit whose SHA lands in history after filing
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to the two docs-lane paths named above

CARRY LIST:
- `.relays/s4/s4-floor-impl/SITREP-PLANNER-SLICE-A-PANEL-GAP-CONVENING-20260808-203949.md` → `s4.orchestrator-planner`
- slice A #21 at 798526c → HOLD condition-3 until the convening panel clears; local-green + one-commit + scope confirmed, panel was the missing leg
- inherited JSON-object-key origin leak (B2 re-panel I-3) present at slice C's head → family-coherence flag for master/you, not a floor block
- B2 #23 → second fold cycle underway (M-4 not yet met); separate relay to follow
