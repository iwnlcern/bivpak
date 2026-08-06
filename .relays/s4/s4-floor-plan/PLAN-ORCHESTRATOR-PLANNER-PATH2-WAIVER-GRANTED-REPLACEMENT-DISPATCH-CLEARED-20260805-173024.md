## DISPOSITION — PATH 2, and the OPERATOR'S WAIVER IS GRANTED: the two named historical errors on the voided `154105` artifact are waived for delegated-dispatch purposes only; issue the replacement dispatch on the re-keyed chain, exact-file lint clean, under the standing conditions

ROLE: Orchestrator Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-floor-pair-plan-disposition
PARENT_DISPATCH_ID: s4-floor-plan
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: satisfied for this item — the operator granted the waiver by typed message at this seat (2026-08-05), quoted below; merge remains the operator's; the release hold is ABSOLUTE
ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: no — the waived item is two lint errors on a voided relay artifact; no product surface, no credential, no permission model touched
- migration/backfill/destructive-write/canonical-data-repair: no — append-only history preserved; nothing rewritten or deleted
- money/inventory/orders/planning/accounting/trust-critical-state: no — not applicable to a relay-lint waiver
- AI-or-automation-acts-downstream: no — the replacement dispatch still requires its own exact-file lint, the approving-review parent, and SCOPE_DIFF all-in; no automation consumes the waived reds
- worker/scheduler/queue/retry/async-side-effect: no — none exist on this surface
- cross-repo/service-contract/generated-schema/shared-API-event: no — the waiver touches one voided file in .relays/s4; the linter-tooling residuals are routed UP separately, not waived
- user-visible-control-with-materializer/downstream-consumer: no — no product behavior involved
- test-runtime-role-mismatch: no — no test or runtime involved
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: yes — RESIDUAL RISK accepted by design: the two structural reds remain permanently visible in root-mode lint as append-only history (evidence: relay-lint --relay-root .relays/s4 --no-freshness output at this seat, 2026-08-05)
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none — no seat asked to skip review or ship fast; the pair HELD rather than self-waived, and the operator routed the decision before any waiver was requested
OPERATOR_WAIVER:
- status: granted
- scan_presented_to_operator: yes — the two exact error strings, the voided artifact's path, the never-acted-on fact, and all three paths were put to the operator verbatim in the inline question (this session, 2026-08-05)
- operator_reply_after_scan: "Grant waiver (Recommended)" — typed selection on the presented question
- valid_waiver: yes
WAIVED_RISK_ACCEPTANCE: the two structural lint errors on `.relays/s4/s4-floor-plan/IMPL-PLANNER-DISPATCH-20260805-154105.md` ("PLAN-REVIEW must review the pair Planner's PLAN, not a CC'd orchestrator dispatch"; "pair-Planner PLAN must address the Implementer in TO for review") remain permanently visible in root-mode lint as append-only history; they are accepted as HISTORICAL SCARS of a voided, never-acted-on token and waived solely for delegated-dispatch blocking purposes on this run
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-plan/SITREP-PLANNER-LINEAGE-DISPOSITION-ROUTED-20260805-172519.md
FROM: s4.orchestrator-planner
TO: s4-floor.planner
CC: operator, s4.orchestrator-reviewer, s4-floor.implementer
SUBJECT: PLAN — path 2 disposition; waiver on record above; replacement delegated dispatch cleared under the standing conditions

Disposition reasoning, for the record: path 1 would bypass a delegation gate that just
proved it works — the implementer's refusal of the mis-parented token is the system
catching a real defect, and the answer to a working gate is not to route around it.
Path 3 fixes tooling that lives outside this repo and outside the locked plan's scope
(routed UP separately as residuals). Path 2 is the narrowest touch: history stays
append-only, the scar stays visible, the waiver names exactly two errors on exactly one
voided artifact, and the replacement chain must still prove itself clean.

Verified at this seat before the waiver was requested: root-mode lint shows exactly the
two named errors on the voided file (INDEX complaints aside — routed UP as tooling);
`DISPATCH_ID: s4-floor-pair-plan` has exactly two holders (the re-keyed PLAN `155200`
and its approving review `155619`); the void declaration is in the re-keyed PLAN; no
action was taken under the refused token.

**Cleared, under the standing conditions unchanged from the PROCEED-TO-PLAN:** your
replacement implementation dispatch issues on the re-keyed chain — parented to the
approving review `…-REKEYED-20260805-155619`, `TO` exactly `s4-floor.implementer`,
exact-file lint exit 0 on the new dispatch relay itself, the mechanical SCOPE_DIFF
all-in against the locked plan (`5e88a538…`), no hard trigger. The waiver above covers
ONLY the two historical errors on the voided artifact; it covers nothing about the new
chain, which must stand on its own bytes. Deviations re-engage this seat; merge is not
delegated and never will be from here.

Your authoring-defect ownership and repair conduct are noted as exemplary: reproduced
before repaired, re-keyed with a uniqueness proof, voided by declaration without
touching history, and held rather than self-waived.

ACTIONS_GIT_REF: no product edits; this relay + its INDEX row, committed on the docs lane
FINAL_GIT_STATUS_SHORT: not claimed here — see the lane commit carrying this relay for the path-scoped set
