## PROCEED-TO-PLAN — s4-matrix: the design-completion report is reconciled at the bytes (design `802b8499…` at `934fca3`; governing G pin `ef96d2d0…` at `12a1c82`); author the gated PLAN parented to the approving review. Conditional dispatch authority is delegated under the standing conditions — with the schema-act fence carved OUT of it explicitly.

ROLE: Orchestrator Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-matrix-plan
PARENT_DISPATCH_ID: s4-matrix-design
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no new gate — plan authorization only; implementation follows solely from your delegated issuance of the literal implementation-dispatch token under the conditions below; the schema act additionally waits on F's landing signal regardless of any approve; merge is the operator's; the release hold is ABSOLUTE
DELEGATED_DISPATCH_AUTHORITY: yes
FROM: s4.orchestrator-planner
TO: s4-matrix.planner
CC: operator, s4.orchestrator-reviewer, s4-matrix.implementer
IN_REPLY_TO: .relays/s4/s4-matrix-design/SITREP-PLANNER-DESIGN-COMPLETE-20260805-220320.md
RELATED_CONTEXT: docs/sprints/2026-08-04-s4-step4/designs/2026-08-05-s4-matrix-arm1-design.md (rev4 — the approved design this sequencing references); .relays/s4/s4-matrix-design/DESIGN-REVIEW-IMPLEMENTER-REV4-20260805-213906.md (the approving review); ../pdc/master/domains/m-1-format-engine/design/2026-08-05-ADDENDUM-G-unborn-head-eligibility.md at `12a1c82` (the governing pin)
SUBJECT: PROCEED-TO-PLAN — Arm 1; plan against rev4 SHA 802b8499…; delegated dispatch on plan-review approve; the schema act stays fenced regardless

Reconciled at this seat before issuing (all E1): the rev4 design blob at `934fca3`
hashes to exactly the claimed `802b8499…` and the working copy matches; the approving
review carries `DESIGN_REVIEW_VERDICT: approve`, `DESIGN_RECORD_KIND: design-doc`, the
matching `DESIGN_DOC_ID`, correct intra-pair addressing, and BASE `934fca3`; the
governing G pin was verified at this seat at the landing signal (`211923`) and is
restated void-on-drift. The five-round review chain (B1–B4 → R1–R4 → the option-1 cell →
the G-staleness hold → approve at the pin) is consistent with this seat's record of
every ruling.

This relay is SEQUENCING ONLY. The gated design-doc lock is yours to emit: your
`PHASE: PLAN` relay carries `DESIGN_LOCK_ID` = the DESIGN_DOC_ID above,
`DESIGN_RECORD_KIND: design-doc`, and `PARENT_DISPATCH_ID` pointing at the approving
DESIGN-REVIEW (`…-213906`), per the lineage gate. A UNIQUE pair-PLAN `DISPATCH_ID` —
the floor pair's lineage scar (this seat's sequencing id reused in a plan thread) is a
class your thread avoids from the start.

**Plan obligations, carried from the reviewed design as written (no new content):** the
DR-3 fixture ledger MATERIALIZED AND FROZEN inside the PLAN per the design's D7 (both
audits' flip/retain/add lists merged); the four-surface schema act as designed; the
golden harness day one (fixture builder, repo-boundary comparison, tolerance-table
extension — one tolerance surface, never a second harness); FX-G-1's fifteen-leg
surface as the fixture target; the blob-lock recapture discipline (ruling `200505`)
in the same reviewed head as any locked-schema change; the act-window ownership from
the reconcile (the three shared clusters matrix-owned for the Arm-1 window; the floor's
additive `value_uint` writer addition rebased over, never touched); the frozen-oracle
recapture as ONE recorded decision in the window; partial-lifecycle and representability
rows in their ruled homes.

**Delegated conditional dispatch authority (the standing conditions, all required):**
your implementation-dispatch token issues only after your Implementer's plan review
returns approve (bare verdict line, R-3.40 item 7); `TO` exactly
`s4-matrix.implementer`; `PARENT_DISPATCH_ID` pointing at the approving PLAN-REVIEW,
which itself parents to your PLAN; a mechanical SCOPE_DIFF over the locked plan's
touched files vs the dispatched scope with `SCOPE_DIFF_RESULT: all-in`; no hard trigger.
**CARVED OUT OF THE DELEGATION, explicitly: the SCHEMA ACT.** Tasks that touch
`manifest.cpp`'s fenced reopening (or consume addendum F) may appear in the locked plan
but are NOT dispatchable under this delegation until F's landing signal arrives in the
pin format ACROSS THE BRIDGE and this seat relays it — an F-fenced task in a SCOPE_DIFF
is an OUT row until then, whatever the plan says. Deviations of any kind re-engage this
seat. Merge authority is NOT delegated and never will be from here — the operator's
token alone; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product edits; this relay + its INDEX row, committed on the docs lane
FINAL_GIT_STATUS_SHORT: not claimed here — see the lane commit carrying this relay for the path-scoped set
