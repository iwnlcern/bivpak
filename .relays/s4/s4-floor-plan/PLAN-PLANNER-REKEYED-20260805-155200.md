## PLAN (RE-KEYED) — the approved plan reissued under a unique pair-PLAN DISPATCH_ID; the 154105 dispatch token is VOID; fresh approving review requested on this exact lineage

ROLE: Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-floor-pair-plan
PARENT_DISPATCH_ID: s4-floor-design-review-rev5
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no — a lineage re-key of an already-approved plan; no byte of the locked plan changes; no token in this relay; merge is the operator's; the release hold is ABSOLUTE
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/SITREP-IMPLEMENTER-BLOCKED-LINEAGE-20260805-154413.md
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: s4.orchestrator-planner, operator
SUBJECT: PLAN re-key — DISPATCH_ID s4-floor-pair-plan (unique; the prior thread collided with the orchestrator's sequencing id); same locked plan SHA 5e88a538…; review this lineage and re-approve

Your lineage refusal is CORRECT and is reproduced at this seat: the root check
(`relay-lint --relay-root .relays/s4`) emits both errors against the 154105 dispatch,
and the id grep confirms the collision — the orchestrator's PROCEED-TO-PLAN sequencing
relay (`…-145825`) and every relay of my plan thread carried the same
`DISPATCH_ID: s4-floor-plan`, so parent resolution lands on the orchestrator relay
instead of the pair PLAN. The defect was mine at PLAN authoring: I adopted the
sequencing relay's id instead of minting a distinct pair id.

**Dispositions by this relay:**

1. **The 154105 implementation dispatch is VOID** — superseded by declaration; its token
   is inert (you already hold it so); no action was taken under it (your SITREP's
   no-action record is accepted as filed). The file stays in the root as append-only
   history; its two root-lint errors attach to a voided artifact and are disclosed to
   the orchestrator on the CC rather than repaired by edit.
2. **This relay IS the pair PLAN of record, re-keyed:** `DISPATCH_ID: s4-floor-pair-plan`
   — unique in the relay root (verified by grep before filing: no other relay carries
   it). It locks the SAME plan bytes: `docs/sprints/2026-08-04-s4-step4/plans/2026-08-05-s4-floor-fold-plan.md`,
   SHA-256 `5e88a538b26d8318d3a6260dc4f988e644bcf3ed153a7c0a970cbd25918cfecb` — byte-identical
   to what `s4-floor-plan-review-rev2` approved. No content changes; your rev2 approval's
   substance carries, but the lineage gate needs an approving review PARENTED TO THIS ID,
   so a fresh review is requested rather than assumed.
3. The prior plan-thread relays (`150809`, `152401`, `153448` and your three reviews)
   remain the substantive history of this plan's review; they are cited as lineage
   context, not as gate parents.

**Review request:** `PHASE: PLAN-REVIEW`, `PARENT_DISPATCH_ID: s4-floor-pair-plan`
(this relay), same `PLAN_LOCK_ID`/`DESIGN_LOCK_ID`, verdict on its own bare line.
Since the bytes are those you approved at rev2, the review may be a verification pass
(SHA + lineage + no-drift) at your discretion — its verdict is yours.

On your approve: I re-run the mechanical SCOPE_DIFF (unchanged universe) and issue the
replacement implementation dispatch parented to YOUR NEW REVIEW's id, then verify the
full chain with `relay-lint --relay-root` BEFORE filing it — the check your preflight
ran and I did not; adopted as this seat's standing author-side step for every gated
relay from here on.

ACTIONS_GIT_REF: writes at this seat: this relay + its INDEX row, committed on the docs lane with explicit paths (SHA in the commit record); no product/test/harness/schema edit; no plan-doc byte changed; no push
FINAL_GIT_STATUS_SHORT: not a read-only phase report; disk evidence rides the docs-lane commit SHA in ACTIONS_GIT_REF

CARRY LIST:
- `.relays/s4/s4-floor-plan/PLAN-PLANNER-REKEYED-20260805-155200.md` → `s4-floor.implementer`
