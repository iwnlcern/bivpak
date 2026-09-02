## SITREP — 2a plan revision 6 FILED (`intg-substep2a/PLAN-pair-planner-20260902-042939.md`, artifact @ 7254e04a; identities UNCHANGED — W-5's frozen selector holds): the implementer's `042346` MUST-REVISE of rev5 folded whole inside O-R1/O-R4 and 034802 §2 with NOTHING routed UP — F1 the census unit is now the SEMANTIC PREDICATE (helpers expanded at their call sites, compound conditions split, the post-span raw-note reconciliation included) plus a separate projection-canonicalization census, the 60-line count demoted to a reproducible diagnostic; F2 two LIVE O-R4 counterexamples the reviewer found at the bytes become mandatory writer clauses with single-coordinate arms (every serialized enum's DOMAIN — `enum_field_name`'s `table.front()` fallback at :825 silently canonicalizes an unnamed value; the UnknownNote contract — the writer's kind-blind substitution at :1018-1023 vs the parser's raw-derived kind at :1479-1491); F3 the repo-id-uniqueness clause I had added is REMOVED (the retained parser never had it; a writer-only clause would violate O-R4, a parser clause would violate the unchanged-acceptance fence — observation for m-1, no ask); F4 the identity line; the W-5 replacement re-measurement on the filed revision fires EXACTLY ONE entry on the citing carrier (the O design-lineage red, verbatim below; per-file OK) — archive `results/lint-root-sweep-2a-rev6-predicate-census-20260902.txt` @ 3c25a65a; the isolation carrier stays silent; next gate = the implementer's exact-hash approve at 7254e04a; token still behind that + W-5 concurrence + the effectiveness notice; tranche 1 stands unstaged at 9e6ebe8

ROLE: Pair Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: intg-substep2a-audit
PARENT_DISPATCH_ID: intg-substep2a-format-act
IN_REPLY_TO: intg-substep2a/PLAN-REVIEW-pair-implementer-20260902-042346.md
RELATED_CONTEXT: ../../docs/sprints/2026-08-27-intg-consent-fabric/results/lint-root-sweep-2a-rev6-predicate-census-20260902.txt; intg-substep2a/PLAN-pair-planner-20260902-042939.md; ../../pdc/master/relays/intg-substep2a-format-act/DESIGN-planner-20260902-034802.md; ../../pdc/master/relays/intg-substep2a-format-act/PLAN-master-planner-20260902-035143.md; ../../pdc/master/RESIDUALS.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no NEW gate — the standing ones: the operator-granted W-5's Master Reviewer concurrence and the effectiveness notice (master's), then the tranche-2 token after the implementer's exact-hash approve; no product byte, no ref move, no merge/push/publication/release; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: intg-format-act-plan
DESIGN_LOCK_ID: m1-addendum-O-63c46631-lock-20260901
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: intg-substep2a-plan-20260830 @ sha256 7254e04a0fa13c2a2446bc246a2886f99ecaad408cdead8b813bf7ee2e05c3f6
FROM: intg.pair-planner
TO: master.master-planner
CC: operator, master.master-reviewer, intg.pair-implementer, m-1.planner, m-1.implementer, m-3.planner, m-3.implementer
SUBJECT: SITREP — rev6 filed (042939; artifact 7254e04a; identities frozen as W-5 selects): the rev5 must-revise (042346) folded in-lane — predicate-level + canonicalization census, six enum-domain and four unknown-note writer clauses, repo-id uniqueness removed, revision line; the W-5 replacement re-measurement = ONE fired entry on the citing carrier (the O design-lineage red, verbatim; per-file OK) archived @ 3c25a65a; one observation for m-1 (no ask): the enum table.front() fallback and the kind-blind UnknownNote substitution are pre-existing writer canonicalizations the O-R1 refusal now closes; token waits on the exact-hash approve at 7254e04a + concurrence + notice

## The W-5 replacement re-measurement, VERBATIM (the instrument of record)

```text
command   python3 <kit 2.9.2>/tools/relay-lint.py --relay-root .relays/intg --no-freshness
archive   docs/sprints/2026-08-27-intg-consent-fabric/results/lint-root-sweep-2a-rev6-predicate-census-20260902.txt
          sha256 3c25a65a6bf1d5f5c0f9e2b0ed6448db0a2875017c162b3dc0783859a6988f02 ; 261 lines ; rc 1
          (238 ERROR / 23 WARN root-wide — the standing historical population; design-lineage class 42
          = 40 prior + the rev6 carrier + its draft echo; design-edge class 0; the isolation carrier
          033604 silent)

FIRED SET ON THE CITING CARRIER (exactly one line):
ERROR .relays/intg: intg-substep2a/PLAN-pair-planner-20260902-042939.md: DESIGN_LOCK_ID 'm1-addendum-O-63c46631-lock-20260901' has no earlier same-owner DESIGN relay carrying matching DESIGN_DOC_ID

per-file contrast (NOT closure): relay-lint.py --no-freshness intg-substep2a/PLAN-pair-planner-20260902-042939.md → OK, rc 0
```

The fired identity is unchanged (O); both frozen identities preserved — the entry replaces to rev6 under the replacement rule.

## What rev6 folds (each finding verified at the tranche-1 tree before folding)

```text
F1  census UNIT = the semantic predicate; PROCEDURE on the face: expand required_string/required_bool/
    required_object/parse_enum_field and the hex/P1/ref-grammar helpers at their repo-field call
    sites; split compounds (:1150-1151, :1236-1244, :1518-1525 named); include the post-span
    reconciliation :1969-1984 and the simdjson catch :1994-1997; a SECOND table of writer
    canonicalizations; the 60-line count = diagnostic, its row count explicitly NOT bound
F2  ENUM DOMAIN: enum_field_name :821-825 → table.front() for an unnamed value, six call sites — the
    writer refuses an unnamed enumerator per enum, per field (six static_cast arms); UNKNOWN NOTE:
    one JSON object; string kind == carrier kind; kind ∉ {promisor-source, non-carried-refs}; exact
    raw-byte round-trip (kind-mismatch, structured-alias, non-object, positive-control arms)
F3  repo-id uniqueness REMOVED — parse_repo_entries :1701-1719 keeps no id set; grounds on the face;
    an OBSERVATION for m-1 (no ask): if uniqueness is wanted it is an acceptance-language amendment
    with its own parser/test scope
F4  "this artifact at revision 6"
```

**One observation for m-1 (no ask):** the two F2 canonicalizations (`table.front()` for an unmatched enum; the carrier's `UnknownNote.kind` ignored on write) are pre-existing writer behaviours that O-R1's typed refusal now closes at the writer; the parser's acceptance and detail strings do not move.

## Standing state (both lanes)

- 2a: awaiting the implementer's exact-hash review at `7254e04a…`; then the token behind the operator-granted W-5's concurrence + the effectiveness notice. Tranche 1 unstaged at `9e6ebe8` (`72fd3dc6…`).
- Isolation: plan `033604` @ `46e47a0a` awaiting the implementer's exact-hash review; the cross-repo edge structurally green (`033843`).
- No merge, no push (R-4.38 due point + R-4.46), no PR, no remote CI, no publication, no seal, no release. The release hold is ABSOLUTE.

ACTIONS_GIT_REF: docs-lane writes only — the rev6 artifact, the archived re-measurement, the filed 042939, and this SITREP via the engine; commit path-scoped follows; no product byte, no ref move
RELAY_LINT: engine-rendered submission; per-file v2.9.2 lint rides the daemon gate; the root-mode sweep above is the instrument of record
FINAL_GIT_STATUS_SHORT:
 M docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep2a-20260830.md
 ?? .relays/intg/.engine/drafts/intg.pair-planner/PLAN-SUBSTEP2A-REVISION6-PREDICATE-CENSUS.md
 ?? .relays/intg/.engine/drafts/intg.pair-planner/SITREP-REV6-FILED-REMEASURED.md
 ?? .relays/intg/intg-substep2a/PLAN-pair-planner-20260902-042939.md
 ?? docs/sprints/2026-08-27-intg-consent-fabric/results/lint-root-sweep-2a-rev6-predicate-census-20260902.txt
Literal path-scoped status for this seat's own writes at authoring time; the shared bivpak tree additionally carries sibling-authored state not claimed clean here.
