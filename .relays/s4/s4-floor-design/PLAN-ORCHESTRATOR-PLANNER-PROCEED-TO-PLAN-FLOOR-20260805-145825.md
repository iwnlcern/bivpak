## PROCEED-TO-PLAN — s4-floor: the design-completion report is reconciled at the bytes; author the gated PLAN parented to the approving review. Conditional dispatch authority is delegated under the standing conditions.

ROLE: Orchestrator Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-floor-plan
PARENT_DISPATCH_ID: s4-floor-design
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no new gate — plan authorization only; implementation follows solely from your delegated issuance of the literal implementation-dispatch token under the conditions below; merge is the operator's; the release hold is ABSOLUTE
DELEGATED_DISPATCH_AUTHORITY: yes
FROM: s4.orchestrator-planner
TO: s4-floor.planner
CC: operator, s4.orchestrator-reviewer, s4-floor.implementer
IN_REPLY_TO: .relays/s4/s4-floor-design/SITREP-PLANNER-DESIGN-COMPLETE-20260805-143723.md
RELATED_CONTEXT: docs/sprints/2026-08-04-s4-step4/designs/2026-08-05-s4-floor-fold-design.md (rev5 — the approved design this sequencing references); .relays/s4/s4-floor-design/DESIGN-REVIEW-IMPLEMENTER-REV5-20260805-142752.md (the approving review)
SUBJECT: PROCEED-TO-PLAN — floor fold; plan against rev5 SHA 42cdfd94…; delegated dispatch on plan-review approve

Reconciled at this seat before issuing (all E1): the rev5 approve exists with
`DESIGN_REVIEW_VERDICT: approve`, `DESIGN_RECORD_KIND: design-doc`, the matching
`DESIGN_DOC_ID`, and correct intra-pair addressing; the design SHA-256 at lane commit
`fc9aa60` equals the disk bytes and the review's pinned `42cdfd94…`. The review chain
(rev1 R1-R5 → rev2 hold releases → rev3 N1-N3 → rev4 044329+C1-C3 → rev5 dissolution
fold) is consistent with this seat's record of every upstream ruling.

This relay is SEQUENCING ONLY. The gated design-doc lock is yours to emit: your
`PHASE: PLAN` relay carries `DESIGN_LOCK_ID: s4-floor-fold-design-20260805`,
`DESIGN_RECORD_KIND: design-doc`, and `PARENT_DISPATCH_ID` pointing at the approving
DESIGN-REVIEW (`…-142752`), per the lineage gate.

**Plan obligations, carried from the reviewed design as written (no new content added
here):** the EIGHTEEN discipline (seventeen only as marked candidate until the VP pass
lands); the discriminating-input-class precheck on every pre-A7 receipt fixture; fence 2
(slice D's `manifest.cpp` work behind Addendum F → Arm-1 schema act); the pinned-`detail`
input for exact-row receipts (m-2's scoped addendum, pre-seal); the m-3 consumer-review
leg for the m-3-owned spellings; the act-window serializations from the reconcile
(single owner per window: `src/cli/main.cpp`, the error-enum/exit-map/envelope cluster,
the frozen-oracle recapture — floor AFTER the matrix Arm-1 window); the nine adopted
acceptance tests; receipts produced as arms land.

**Delegated conditional dispatch authority (the standing conditions, all required):**
your implementation-dispatch token issues only after your Implementer's plan review returns approve
(bare verdict line, R-3.40 item 7); `TO` exactly `s4-floor.implementer`;
`PARENT_DISPATCH_ID` pointing at the approving PLAN-REVIEW, which itself parents to your
PLAN; a mechanical SCOPE_DIFF over the locked plan's touched files vs the dispatched
scope with `SCOPE_DIFF_RESULT: all-in` — any OUT row (fence-2 surfaces before the F+G/
Arm-1 signal included) comes to this seat instead of dispatching; no hard trigger.
Deviations of any kind re-engage this seat. Merge authority is NOT delegated and never
will be at this seat — the operator's `DISPATCH MERGE` alone.

ACTIONS_GIT_REF: no product edits; this relay + its INDEX row, committed on the docs lane
FINAL_GIT_STATUS_SHORT: not claimed here — see the lane commit carrying this relay for the path-scoped set
