## DESIGN rev5 — the FX-MG-9 dissolution folded; the last blocker is gone; REVIEW RE-REQUESTED

ROLE: Planner
PHASE: DESIGN
AUTHORITY: design-only
DISPATCH_ID: s4-floor-design
PARENT_DISPATCH_ID: s4-floor-audit
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no — the upstream ruling is folded as received; the count moves only at the VP's master-side pass; the release hold is ABSOLUTE
DESIGN_DOC_ID: s4-floor-fold-design-20260805
IN_REPLY_TO: .relays/s4/s4-floor-design/DESIGN-ORCHESTRATOR-PLANNER-FXMG9-DISSOLVED-FOLD-AND-RE-REQUEST-20260805-141338.md
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: s4.orchestrator-planner, operator
SUBJECT: DESIGN-REVIEW RE-REQUEST — rev5 of s4-floor-fold-design-20260805; FX-MG-9 dissolved with burden pointer to FX-VF-O5/CANON-3; EIGHTEEN operative; C1-C3 and 044329 already folded at rev4

The doc of record (same `DESIGN_DOC_ID`, rev5 in the header, full lineage preserved):
`docs/sprints/2026-08-04-s4-step4/designs/2026-08-05-s4-floor-fold-design.md`

What rev5 folds (the 141338 ruling, as received):

- `FX-MG-9/evaluability-red` is DISSOLVED — m-2's sharpened diagnosis: §A7.5's allowlist
  deletion made the verdict a pure function of the parsed line, so the discriminating
  input class is EXTINCT (unconstructible, not merely unreachable). Your rev3 blocker is
  resolved by dissolution, which was our recommended shape 1 taken as dissolution rather
  than re-specification.
- The M4-C1 burden pointer: `FX-VF-O5`'s 12 keys + `CANON-3` with its own CIM — slice A
  GREEN-ables it (the §A7.4 unreadable gate). §6's map row reads
  `DISSOLVED-PENDING-RATIFICATION` with that pointer — never deleted, never blank.
- Count discipline, verbatim: EIGHTEEN is the operative figure in this design, the plan,
  and the receipt map until the VP's master-side re-ratification pass lands its signal;
  SEVENTEEN appears nowhere except explicitly marked candidate.
- The pattern-library rule is now binding on our receipt work: before building any
  receipt whose fixture predates A7, test whether the DISCRIMINATING INPUT CLASS still
  exists — not whether one case died.
- Consistency sweep: slice E's two stale FX-MG-9 references corrected (§A5.10's
  abstain-by-construction invariant is retained as sealed text but marked product-
  unreachable post-A7; slice E's proof row drops key 9 and points at the slice-A burden).
- No new holds: the possible master-side collapse of FX-MG-9's three sibling BOUND rows
  into `FX-VF-M1` removes obligations if it lands, never adds.

Everything you graded PASS at rev3 (N1/N2/N3 mechanics) and everything folded at rev4
(the 044329 H1/H2 correction; your C1-C3 with §7 tests 8-9) is byte-preserved outside
these deltas.

Review request: the full protocol shape — `PHASE: DESIGN-REVIEW`, `PARENT_DISPATCH_ID`
at this relay, same `DESIGN_DOC_ID`, protocol verdict enum. This is the closed-approve
candidate: no open findings remain at this seat, no hold is outstanding, and the one
external signal (the VP count pass) is non-blocking by the orchestrator's ruling.

On approve I report design-complete to `s4.orchestrator-planner` and hold for
PROCEED-TO-PLAN; I do not self-advance.

ACTIONS_GIT_REF: writes at this seat: the rev5 design-doc deltas + this relay + its INDEX row, committed on the docs lane with explicit paths (SHA in the commit record); no product/test/harness/schema edit; no push
FINAL_GIT_STATUS_SHORT: not a read-only phase report; disk evidence rides the docs-lane commit SHA in ACTIONS_GIT_REF

CARRY LIST:
- `.relays/s4/s4-floor-design/DESIGN-PLANNER-REV5-20260805-141610.md` → `s4-floor.implementer`
