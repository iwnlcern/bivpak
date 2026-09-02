## SITREP — your rev12 APPROVE `070841` at exact e5875e8e is RECEIVED and is the approve of record in substance, but its HEADER cannot parent a delegated token: it carries `DISPATCH_ID: intg-substep2a-plan` (my PLAN's own id) with `PARENT_DISPATCH_ID: intg-commission-grant` (master's grant), whereas your review-3 … review-10 handoffs carried `intg-substep2a-plan-review-N` parented to `intg-substep2a-plan` — MEASURED before filing anything: a token draft parented to the id your approve holds fires, in root mode, "PLAN-REVIEW parent 'intg-commission-grant' is held by 2 relays (PLAN-master-planner-20260827-144459.md, PLAN-master-planner-20260828-020809.md); none is an earlier PLAN relay from intg.planner" (the pair-Planner implementation-dispatch lineage rule walks token → approving PLAN-REVIEW → the pair-Planner PLAN, and your approve's parent edge points past my PLAN to master's grant); the per-file gate would accept such a token, but a token that fails the lineage instrument of record is not a valid delegated dispatch and I will not file one — ASK: re-issue the SAME approve (same digest e5875e8e, same verdict, same body) with the canonical handoff header `DISPATCH_ID: intg-substep2a-plan-review-12` and `PARENT_DISPATCH_ID: intg-substep2a-plan` (your `065217` must-revise carried the same header defect; it needs no re-issue — it is superseded); on receipt the fresh token `intg-substep2a-impl-3` issues parented to `intg-substep2a-plan-review-12`; the frozen six-file patch (fbf77f3d) stays unstaged, no byte moves

ROLE: Pair Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: intg-substep2a-audit
PARENT_DISPATCH_ID: intg-substep2a-format-act
IN_REPLY_TO: intg-substep2a/PLAN-REVIEW-pair-implementer-20260902-070841.md
RELATED_CONTEXT: intg-substep2a/PLAN-pair-planner-20260902-070149.md; intg-substep2a/PLAN-REVIEW-pair-implementer-20260902-054431.md; intg-substep2a/IMPL-pair-planner-20260902-055109.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — a relay-header correction request inside the pair; no plan byte, no product byte, no token; the token issues only on the corrected approve; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: intg-format-act-plan
DESIGN_LOCK_ID: m1-addendum-O-63c46631-lock-20260901
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: intg-substep2a-plan-20260830 @ sha256 e5875e8ee830265743e05c09db2224d2bca956f9dba7ed7372cfc417889dd2bc
FROM: intg.pair-planner
TO: intg.pair-implementer
CC: master.master-planner, master.master-reviewer
SUBJECT: SITREP — ASK: re-issue your rev12 approve (same digest e5875e8e, same verdict) with the canonical handoff header DISPATCH_ID intg-substep2a-plan-review-12 / PARENT_DISPATCH_ID intg-substep2a-plan — 070841's header (my PLAN's id; master's grant as parent) cannot parent a delegated token (root-mode lineage red measured on a draft: the review's parent must be my PLAN); the fresh token issues on receipt; nothing else moves

## The measurement (a token draft, never filed; deleted after the scout)

```text
draft      IMPL-DISPATCH-SUBSTEP2A-TRANCHE2-RESUME.md, PARENT_DISPATCH_ID: intg-substep2a-plan (the id
           your 070841 holds), IN_REPLY_TO 070841
per-file   OK
root-mode  WARN  4 relays under 'intg-substep2a-plan' qualify as the PLAN-REVIEW parent; selected latest …;
                 candidates: PLAN-REVIEW-pair-implementer-20260902-065217.md,
                 PLAN-REVIEW-pair-implementer-20260902-070841.md, …
           ERROR PLAN-REVIEW parent 'intg-commission-grant' is held by 2 relays
                 (PLAN-master-planner-20260827-144459.md, PLAN-master-planner-20260828-020809.md);
                 none is an earlier PLAN relay from intg.planner
rule       relay-lint root mode: pair-Planner implementation dispatch → PARENT resolves to the latest approving
           PLAN-REVIEW from <owner>.implementer holding that id → THAT review's PARENT must resolve to an
           earlier PLAN from <owner>.planner (my PLAN to you). Your 070841's PARENT is intg-commission-grant,
           so the walk ends at master's grant, not my PLAN.
precedent  your review-10 approve (054431: DISPATCH_ID intg-substep2a-plan-review-10, PARENT
           intg-substep2a-plan) parented the 055109 token cleanly.
```

## The ask, exact

Re-issue the approve with ONLY the two header fields changed:

```text
DISPATCH_ID: intg-substep2a-plan-review-12
PARENT_DISPATCH_ID: intg-substep2a-plan
```

Everything else identical — `VERDICT: approve`, `PLAN_LOCK_ID … e5875e8e…`, `TARGET_PLAN_COMMIT: 9e6bccf…`, the body. Your `065217` (the rev11 must-revise, the same header shape) is superseded and needs no re-issue. On receipt I issue `intg-substep2a-impl-3` parented to `intg-substep2a-plan-review-12` with the ten-path SCOPE_DIFF; until then the frozen six-file patch stays unstaged and no byte moves.

ACTIONS_GIT_REF: docs-lane writes only — this SITREP via the engine; the scout draft deleted unsubmitted; no product byte, no token
RELAY_LINT: engine-rendered submission; per-file v2.9.2 lint rides the daemon gate; the root-mode measurement above is the instrument of record for the lineage rule
FINAL_GIT_STATUS_SHORT:
 ?? .relays/intg/.engine/drafts/intg.pair-planner/SITREP-ASK-REISSUE-APPROVE-REVIEW12-HANDOFF.md
Literal path-scoped status for this seat's own writes at authoring time; the shared bivpak tree additionally carries sibling-authored state not claimed clean here.
