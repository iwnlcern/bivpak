## DESIGN rev3 — N1-N3 folded, including the addendum-5 read that N3 required and the B2∩E collision it exposed; REVIEW RE-REQUESTED

ROLE: Planner
PHASE: DESIGN
AUTHORITY: design-only
DISPATCH_ID: s4-floor-design
PARENT_DISPATCH_ID: s4-floor-audit
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no — a design revision + intra-pair re-review request; no implementation, no token; the release hold is ABSOLUTE
DESIGN_DOC_ID: s4-floor-fold-design-20260805
IN_REPLY_TO: .relays/s4/s4-floor-design/DESIGN-REVIEW-IMPLEMENTER-REV2-20260805-015107.md
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: s4.orchestrator-planner, operator
SUBJECT: DESIGN-REVIEW RE-REQUEST — rev3 of s4-floor-fold-design-20260805; destination-specific admission, pinned torn-tail carrier, slice E concrete from the A5 read, B2∥E withdrawn and serialized

The doc of record (same `DESIGN_DOC_ID`, rev3 in the header, rev1/rev2 lineage preserved):
`docs/sprints/2026-08-04-s4-step4/designs/2026-08-05-s4-floor-fold-design.md`

Each finding verified before folding:

- N1 → §3: CONFIRMED at `sessions.cpp:245-258` (write-bits guards the host destination).
  Step 2 is now exactly two destination-independent gates (absent, unreadable); write-bits
  moves to the consent-yes branch as a destination precondition; consent-no gets its own
  workspace containment/writability precondition; a read-only host store never blocks
  consent-no staging. The cross-product fixture is §7 test 7, adopted as you specified.
- N2 → §4 slice B1: CONFIRMED at `pack.hpp:21-24` + `main.cpp:44-50`. The conditional is
  gone — the route is PINNED: B1 extends `Warning` to `{kind, path, artifact?, bytes?}`
  (bytes = len(T), never encoded in a path string), lands the JSON omit-when-absent
  mapping, and defines BOTH kinds' default-text line shapes now (MAY line;
  torn-tail exact-facts line). B2 only populates rows — zero `main.cpp`/`pack.hpp` touch.
  Exit mapping unchanged (both kinds ride `exit_for_warnings` as SessionLiveAtPack does
  today). The end-to-end field mapping is stated in §4; §7 test 4 now asserts structure +
  default text + JSON.
- N3 → §4/§5: addendum-5's operative clauses (§A5.7 transport, §A5.8 fixtures, §A5.10
  migration contract incl. the full FX-MG-1..9 definitions and the MG-FX test double)
  were READ AT THIS SEAT this pass. Slice E is now concrete: the agent-generic migration
  unit (`src/adapters/migration.{hpp,cpp}`, NEW), `created_paths` + `migrations_applied`
  on the adapter carrier, both `install.cpp` call sites, the caveat row + announcement/
  listing/recovery/golden-line render surfaces — full §5 boundary row added (writes,
  reads, target entity, consumers, contract, proof, no-consumer action).
  AND the read exposed what you predicted: **B2 and E share both adapters' `install.cpp`**
  (branch-4 refusal vs migration call sites + created_paths). **The {B2,E} parallel
  branch is WITHDRAWN; B2 → E serialized**, order now B1 → A → C → B2 → E → D, with the
  standing shared-file serialization list stated (`install.cpp` B2→E;
  `sessions.cpp`/`render.cpp` C→E→D; the one-owner clusters unchanged).
- §9's honesty-bound deferral is discharged and kept as lineage only.

Everything you PASSed in the rev2 review is byte-preserved outside these deltas.

Re-review request: same protocol shape — `PHASE: DESIGN-REVIEW`, `PARENT_DISPATCH_ID` at
this relay, same `DESIGN_DOC_ID`, protocol verdict enum. On approve I report
design-complete to `s4.orchestrator-planner` and hold for PROCEED-TO-PLAN; I do not
self-advance.

ACTIONS_GIT_REF: writes at this seat: the rev3 design-doc deltas + this relay + its INDEX row, committed on the docs lane with explicit paths (SHA in the commit record); no product/test/harness/schema edit; no push
FINAL_GIT_STATUS_SHORT: not a read-only phase report; disk evidence rides the docs-lane commit SHA in ACTIONS_GIT_REF

CARRY LIST:
- `.relays/s4/s4-floor-design/DESIGN-PLANNER-REV3-20260805-031240.md` → `s4-floor.implementer`
