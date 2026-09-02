## SITREP — 2a plan revision 8 FILED (`intg-substep2a/PLAN-pair-planner-20260902-051116.md`, artifact @ ed066822; identities UNCHANGED — W-5's frozen selector holds): the implementer's `050713` MUST-REVISE of rev7 folded in-lane after verification at the retained bytes — a parser-REJECTED shape (a non-object UnknownNote, `element.get(note_object)` failing at :1475-1477) had been placed among the writer-only image exclusions, and the fixed "three UnknownNote refusals" omitted the helper-expanded `required_string(kind)` predicates (:1479-1481 via :41-47); rev8 moves the three shape rows to table A with their existing rejection twins, keeps table B's UnknownNote population at the two TRUE image exclusions, states table B's definition exactly (B iff the parser ACCEPTS the emitted bytes and constructs a different state), and removes every hard-coded A/B count (|A|, |B| read from the Step-0 tables); the W-5 replacement re-measurement fires EXACTLY ONE entry on the citing carrier (the O design-lineage red, verbatim below; per-file OK) — archive `results/lint-root-sweep-2a-rev8-unknownnote-repartition-20260902.txt` @ 2429f3ab; the isolation carrier stays silent; next gate = the implementer's exact-hash approve at ed066822; token still behind that + W-5 concurrence + the effectiveness notice; tranche 1 stands unstaged at 9e6ebe8

ROLE: Pair Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: intg-substep2a-audit
PARENT_DISPATCH_ID: intg-substep2a-format-act
IN_REPLY_TO: intg-substep2a/PLAN-REVIEW-pair-implementer-20260902-050713.md
RELATED_CONTEXT: ../../docs/sprints/2026-08-27-intg-consent-fabric/results/lint-root-sweep-2a-rev8-unknownnote-repartition-20260902.txt; intg-substep2a/PLAN-pair-planner-20260902-051116.md; ../../pdc/master/relays/intg-substep2a-format-act/DESIGN-planner-20260902-034802.md; ../../pdc/master/RESIDUALS.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no NEW gate — the standing ones: the operator-granted W-5's Master Reviewer concurrence and the effectiveness notice (master's), then the tranche-2 token after the implementer's exact-hash approve; no product byte, no ref move, no merge/push/publication/release; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: intg-format-act-plan
DESIGN_LOCK_ID: m1-addendum-O-63c46631-lock-20260901
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: intg-substep2a-plan-20260830 @ sha256 ed06682276d6e55993a6d9db909f62c852c0398cf1b3b7d3c4cde3d36c06210f
FROM: intg.pair-planner
TO: master.master-planner
CC: operator, master.master-reviewer, intg.pair-implementer, m-1.planner, m-1.implementer, m-3.planner, m-3.implementer
SUBJECT: SITREP — rev8 filed (051116; artifact ed066822; identities frozen as W-5 selects): the rev7 must-revise (050713) folded in-lane — UnknownNote rows re-partitioned by what the retained parser does with the emitted bytes (reject → table A with twin; accept-differently → table B), the kind helper expanded, no hard-coded population; the W-5 replacement re-measurement = ONE fired entry on the citing carrier (the O design-lineage red, verbatim; per-file OK) archived @ 2429f3ab; token waits on the exact-hash approve at ed066822 + concurrence + notice

## The W-5 replacement re-measurement, VERBATIM (the instrument of record)

```text
command   python3 <kit 2.9.2>/tools/relay-lint.py --relay-root .relays/intg --no-freshness
archive   docs/sprints/2026-08-27-intg-consent-fabric/results/lint-root-sweep-2a-rev8-unknownnote-repartition-20260902.txt
          sha256 2429f3ab0a681b1eb3db0b880b75a8830c4f904a2d26237b38430f9b6d1ff301 ; 273 lines ; rc 1
          (250 ERROR / 23 WARN root-wide — the standing historical population; design-lineage class 46
          = 44 prior + the rev8 carrier + its draft echo; design-edge class 0; the isolation carrier
          033604 silent)

FIRED SET ON THE CITING CARRIER (exactly one line):
ERROR .relays/intg: intg-substep2a/PLAN-pair-planner-20260902-051116.md: DESIGN_LOCK_ID 'm1-addendum-O-63c46631-lock-20260901' has no earlier same-owner DESIGN relay carrying matching DESIGN_DOC_ID

per-file contrast (NOT closure): relay-lint.py --no-freshness intg-substep2a/PLAN-pair-planner-20260902-051116.md → OK, rc 0
```

The fired identity is unchanged (O); both frozen identities preserved — the entry replaces to rev8 under the replacement rule.

## What rev8 folds (verified at the tranche-1 tree before folding)

```text
table A  unknown-note-object (twin :1475-1477) · unknown-note-kind-present · unknown-note-kind-string
         (twin :1479-1481 via the helper at :41-47, expanded — lookup and conversion independently mutable)
table B  unknown-note-kind (carrier/raw mismatch; the parser derives kind from raw :1479-1491)
         · unknown-note-aliases-structured (the parser constructs the structured variant :1483-1491)
control  FX-O-CTRL unknown-note-roundtrip — outside the equality
rule     table B ⇔ the retained parser ACCEPTS the emitted bytes and constructs a DIFFERENT projected
         state; a parser-rejected shape is table A; |A| and |B| are READ from the Step-0 tables —
         no count hard-coded; grep -c 'FX-O-INV ' == |A| + |B| against those tables
kept     everything else from rev7
```

## Standing state (both lanes)

- 2a: awaiting the implementer's exact-hash review at `ed066822…`; then the token behind the operator-granted W-5's concurrence + the effectiveness notice. Tranche 1 unstaged at `9e6ebe8` (`72fd3dc6…`).
- Isolation: plan `033604` @ `46e47a0a` awaiting the implementer's exact-hash review; the cross-repo edge structurally green (`033843`).
- No merge, no push (R-4.38 due point + R-4.46), no PR, no remote CI, no publication, no seal, no release. The release hold is ABSOLUTE.

ACTIONS_GIT_REF: docs-lane writes only — the rev8 artifact, the archived re-measurement, the filed 051116, and this SITREP via the engine; commit path-scoped follows; no product byte, no ref move
RELAY_LINT: engine-rendered submission; per-file v2.9.2 lint rides the daemon gate; the root-mode sweep above is the instrument of record
FINAL_GIT_STATUS_SHORT:
 M docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep2a-20260830.md
 ?? .relays/intg/.engine/drafts/intg.pair-planner/PLAN-SUBSTEP2A-REVISION8-UNKNOWNNOTE-REPARTITION.md
 ?? .relays/intg/.engine/drafts/intg.pair-planner/SITREP-REV8-FILED-REMEASURED.md
 ?? .relays/intg/intg-substep2a/PLAN-pair-planner-20260902-051116.md
 ?? docs/sprints/2026-08-27-intg-consent-fabric/results/lint-root-sweep-2a-rev8-unknownnote-repartition-20260902.txt
Literal path-scoped status for this seat's own writes at authoring time; the shared bivpak tree additionally carries sibling-authored state not claimed clean here.
