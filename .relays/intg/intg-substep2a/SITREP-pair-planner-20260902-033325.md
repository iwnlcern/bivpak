## SITREP — 2a plan revision 4 returned MUST-REVISE (`025301`), and ONE of its four findings is a counterexample to the fence owner's own C-4 text that this pair may not correct in-lane — ROUTED UP: at retained `9e6ebe8`, `image_path`, `partial_path`, and `spool_path` are three distinct paths (`pack.cpp:549-551`), `cleanup_error` removes ONLY the latter two (`:569-573`), and the destination is touched ONLY by the final rename (`:801`) — so an O-R1 refusal leaves a PRE-EXISTING `<name>.bvpk` at the destination untouched, and C-4's unconditional "no `.bvpk` at the destination" is FALSE on that host state (verified at my bytes before routing); the provable statement is narrower ("serialization refuses before the partial archive is opened; cleanup removes partial + spool; NO NEW OR REPLACEMENT image is emitted; a pre-existing destination image is unchanged") — m-1's exact correction requested; the other three findings (F1 the writer domain must span every typed-expressible parser invariant, incl. the pre-build O-R2 helper path; F2 C-2's literal no-brace form and pack numstat `+3/-2`; F4 an empty `git status --short` postcondition) are verified and fold in-lane at revision 5, which files ONLY after the ruled C-4 text is truthfully executable; the token still waits on that approve + the operator's W-5 disposition + concurrence; tranche 1 stands

ROLE: Pair Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: intg-substep2a-audit
PARENT_DISPATCH_ID: intg-substep2a-format-act
IN_REPLY_TO: intg-substep2a/PLAN-REVIEW-pair-implementer-20260902-025301.md
RELATED_CONTEXT: ../../pdc/master/relays/intg-substep2a-format-act/DESIGN-planner-20260901-231935.md; ../../pdc/master/relays/intg-substep2a-format-act/PLAN-master-planner-20260901-232655.md; intg-substep2a/PLAN-pair-planner-20260902-023115.md; docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep2a-20260830.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no NEW gate — a fence-term counterexample routed to its owner on the fence's own path; the operator's W-5 disposition (vi) and the Master Reviewer's concurrence stand as the standing gates; no product byte, no ref move, no merge/push/publication/release; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: intg-format-act-plan
DESIGN_LOCK_ID: m1-addendum-O-63c46631-lock-20260901
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: intg-substep2a-plan-20260830 @ sha256 e0d5585b77b52e464be97e4e03685c0509ee170660bdfccc3a7f6ee12f42baa4
FROM: intg.pair-planner
TO: master.master-planner
CC: operator, master.master-reviewer, intg.pair-implementer, m-1.planner, m-1.implementer, m-3.planner, m-3.implementer
SUBJECT: SITREP — rev4 MUST-REVISE (025301): F3 is a C-4 counterexample verified at 9e6ebe8 (three distinct paths :549-551; cleanup removes partial+spool only :569-573; destination touched only by the rename :801 → a pre-existing image survives refusal) — m-1's exact C-4 correction requested via you; F1/F2/F4 verified, fold in-lane at rev5 AFTER the correction; the W-5 replacement measurement of rev4 stands (023115 = the one O red); tranche 1 unstaged at 9e6ebe8; nothing else moves

## F3 — the counterexample, at the bytes

```text
pack.cpp @ 9e6ebe8 (identical at the tranche-1 tree — pack.cpp is untouched there):
  :549  image_path   = source.parent / (name + ".bvpk")
  :550  partial_path = source.parent / (name + ".bvpk.partial")
  :551  spool_path   = source.parent / (name + ".bvpk.spool")
  :569-573  cleanup_error: remove(partial_path); remove(spool_path); return unexpected(...)
  :801  rename(partial_path, image_path)   — the ONLY write to image_path
host state: an EARLIER <name>.bvpk exists at image_path (no precondition or guard checks this)
O-R1 refusal at :765 → cleanup_error → the earlier image is still there.
C-4 (231935): "on refusal, pack fails closed — no .bvpk at the destination" — UNCONDITIONAL: false on that state.
provable instead: "serialize refuses BEFORE the partial archive is opened; cleanup removes partial
  + spool; no NEW or REPLACEMENT .bvpk is emitted; a pre-existing destination image is unchanged."
```

**Ask of m-1 (via you):** an exact C-4 correction — either the narrower provable statement above as the evidence text, or an explicitly bound absence precondition (a destination check the ruling would then have to place somewhere, which is a product byte outside the propagation and so NOT this pair's to add). The pair will not file evidence stating the current unconditional claim as fact, and will not widen its own write set to add a guard.

## The other three findings — verified, fold in-lane at rev5

```text
F1 (Critical)  RepoEntry::sha is optional<string> (types.hpp:204) and the parser rejects a present
               non-40-hex value (:1561); the retained path helpers (:1077-1111) reject BEFORE row
               construction. rev4's "SHAPE errors have no typed twin" was wrong for string/content
               invariants (sha, eligibility.method, proof tip_sha, local-ref sha + proof relation,
               shallow boundary hex, structured-note constraints). rev5: a CENSUS of all 60 ParseError
               sites in the repo parsers (:1077-1700, grep-derived) classified typed-expressible →
               the ONE inventory (with a writer-refusal witness each) vs unrepresentable (JSON type,
               enum discriminant text) → parser-local; and the O-R2 helpers restructured to parse
               paths as raw typed values with the predicate applied ONLY by the shared call. The
               boundary is DETERMINED by the census, not chosen: O-R1 names "§2.3+G+H+N+O-R2/O-R3"
               and the parser's acceptance predicates ARE those invariants as executed.
F2 (Important) C-2 literal: `if (!manifest_json) return cleanup_error(manifest_json.error());` (no
               braces) — rev5 carries the owner's bytes; pack numstat +3/-2.
F4 (Important) `git status --short` reports no ignored paths — rev5 binds it to EMPTY.
```

## Standing state

- Rev5 files ONLY after m-1's C-4 correction reaches me (the reviewer's own sequencing: "reissue … only after the ruled C-4 text is truthfully executable"); then exact-hash re-review and the W-5 root-mode re-measurement.
- W-5's measured entry for the 2a lineage stands at rev4 (`023115` / `e0d5585b`) until rev5 replaces it.
- The isolation act (`031728`) opens in parallel under its own NEW plan identity — reported separately.
- Tranche 1: unstaged and uncommitted over `9e6ebe8`, diff `72fd3dc6…`. No merge, push, PR, remote CI, publication, seal, or release. The release hold is ABSOLUTE.

ACTIONS_GIT_REF: docs-lane writes only — this SITREP via the engine; no plan byte (rev5 held), no product byte, no ref move
RELAY_LINT: engine-rendered submission; per-file v2.9.2 lint rides the daemon gate
FINAL_GIT_STATUS_SHORT:
 ?? .relays/intg/.engine/drafts/intg.pair-planner/SITREP-2A-REV4-C4-COUNTEREXAMPLE-UP.md
Literal path-scoped status for this seat's own writes at authoring time; the shared bivpak tree additionally carries sibling-authored state not claimed clean here.
