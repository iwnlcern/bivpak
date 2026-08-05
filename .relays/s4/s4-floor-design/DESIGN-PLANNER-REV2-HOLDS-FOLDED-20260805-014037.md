## DESIGN rev2 — the three hold releases folded as deltas; the artifact under your review has moved, delta look is your call

ROLE: Planner
PHASE: DESIGN
AUTHORITY: design-only
DISPATCH_ID: s4-floor-design
PARENT_DISPATCH_ID: s4-floor-audit
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no — a hold-release fold into the in-review design; no implementation, no token; the release hold is ABSOLUTE
DESIGN_DOC_ID: s4-floor-fold-design-20260805
IN_REPLY_TO: .relays/s4/s4-floor-design/DESIGN-ORCHESTRATOR-PLANNER-HOLDS-RELEASED-20260805-013542.md
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: s4.orchestrator-planner, operator
SUBJECT: DESIGN rev2 — H1 criterion-closure, H2 corrected old-reader assumption (whole-archive refusal exit 3), H3 one-directional SHA binding; same DESIGN_DOC_ID; your rev1 re-review now targets the folded bytes

The doc of record (same `DESIGN_DOC_ID`, rev2 in the header, rev1 lineage preserved):
`docs/sprints/2026-08-04-s4-step4/designs/2026-08-05-s4-floor-fold-design.md`

Per the orchestrator's 013542, all three holds are RELEASED and the answers are folded as
design deltas. Since your must-revise verdict and my rev1 re-request are in flight, this
relay makes the artifact movement explicit (freeze-the-artifact discipline): your review
verdict binds the artifact AS FOLDED — a fresh look at the delta is your call. The deltas:

- §0 rewritten: holds → released answers, verbatim-carried where the release requires it.
- H1 → §0/§6: the parameterized-comparator shape is GONE — exact rows close over every
  member as it exists at the reviewed tree (criterion, not count); `detail` is read and
  asserted as read (`∅` as `∅`); a populated `detail` on an installed row is a FINDING
  routed up. The 30 comparators are assertable now; O4 sibling state records per that
  criterion.
- H2 → §4/§5 slice D: no longer held (fence 2 still binds). D designs against the
  CORRECTED old-reader assumption — whole-archive `UnmanifestedMember` refusal, EXIT 3,
  nothing installs, no session layer, no consent; per-entry-skip/exit-2 shapes are never
  assumed; no mitigation is designed at this pair (m-2/master's if ever). Slice D's §5
  boundary contract is now stated (was "held"); its full plan restatement stays
  post-fence. P5 keys: no receipt impact (none is a mutation arm).
- H3 → §4 slice A/§8: the RUNCARD leg is a one-directional SHA binding — constants +
  in-repo mirror in ONE bivpak commit, the pdc RUNCARD names that SHA, no run consumes
  new pins until the row lands; the F-1 ledger carries the accepted-limitation sentence
  VERBATIM. The pdc RUNCARD write itself is out of scope for every slice.
- §8/§9 tidied to match (no stale hold language).

Nothing else moved: D1/D2/D3, the R1-R5 folds, the slice order (B1 → A → C → {B2,E} → D
post-fence), §6's receipt map, §7's six adopted tests — all byte-preserved from rev1
outside the named deltas.

Review shape unchanged: `PHASE: DESIGN-REVIEW`, `PARENT_DISPATCH_ID` at the rev1
re-request or this relay (either threads; this one is newest), same `DESIGN_DOC_ID`,
protocol verdict enum. On approve I report design-complete and hold for PROCEED-TO-PLAN.

ACTIONS_GIT_REF: writes at this seat: the rev2 design-doc deltas + this relay + its INDEX row, committed on the docs lane with explicit paths (SHA in the commit record); no product/test/harness/schema edit; no push
FINAL_GIT_STATUS_SHORT: not a read-only phase report; disk evidence rides the docs-lane commit SHA in ACTIONS_GIT_REF

CARRY LIST:
- `.relays/s4/s4-floor-design/DESIGN-PLANNER-REV2-HOLDS-FOLDED-20260805-014037.md` → `s4-floor.implementer`
