## PLAN (2a revision 8 — your `050713` MUST-REVISE folded, the finding VERIFIED at my bytes: `element.get(note_object)` fails for a non-object note at :1475-1477 with the existing `ParseError{"notes"}`, and `required_string(note_object, "kind")` at :1479-1481 rejects an absent or non-string kind through the helper at :41-47 — so `unknown-note-object` is a TABLE-A row with that rejection as its twin, the `kind` helper is EXPANDED into two table-A rows (`unknown-note-kind-present`, `unknown-note-kind-string`) each with a negative writer arm, and table B's UnknownNote population is exactly the two TRUE projection-image exclusions (`unknown-note-kind` carrier/raw mismatch; `unknown-note-aliases-structured`); table B's definition is now stated exactly (a row is B iff the retained parser ACCEPTS the emitted bytes and constructs a DIFFERENT projected state — a parser-rejected shape is never B); no A/B count is hard-coded anywhere — |A| and |B| are READ from the Step-0 tables; the `FX-O-CTRL unknown-note-roundtrip` control stays outside the equality; your exact-hash PLAN-REVIEW at ed066822 requested; the W-5 re-measurement runs on this filing and goes UP

ROLE: Pair Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: intg-substep2a-plan
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: intg-substep2a/PLAN-REVIEW-pair-implementer-20260902-050713.md
RELATED_CONTEXT: ../../pdc/master/relays/intg-substep2a-format-act/DESIGN-planner-20260902-034802.md; ../../pdc/master/domains/m-1-format-engine/design/2026-09-01-ADDENDUM-O-writer-validity-contract.md; intg-substep2a/PLAN-pair-planner-20260902-044936.md; intg-substep2a/PLAN-REVIEW-pair-implementer-20260902-044457.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — a table-membership and completeness correction inside O-R1/O-R4 and 034802 §2's fence; no sealed byte, no product byte, no parser byte, no ref move; the tranche-2 token waits on your exact-hash approve of THIS digest AND the operator-granted W-5's Master Reviewer concurrence AND the effectiveness notice; m-1's and m-3's parallel byte reviews, merge, push, and release stay behind their own gates; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
COMMISSION_SCOPE: the operator-authorized integration phase (2026-08-26) executed by ONE commissioned pair — sub-step 1 first, the A6 rev14 consent-UX fabric with the engine unwired per the sealed spine; subsequent sub-steps (format act consuming LOCKED M rev8 + LOCKED N; then wiring at product scope) each behind their standing gates incl. m-4's reachability re-review before any wiring; sealed design only; STOPs route UP; no merge/push/publication/release authority
COMMISSION_TO: intg.pair-planner
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: intg-format-act-plan
DESIGN_LOCK_ID: m1-addendum-O-63c46631-lock-20260901
DESIGN_RECORD_KIND: design-doc
LOCKED_DESIGN_SHA256: 63c46631c84ce27ebedbf71c4965e6b0b149919a83118835d78ce29e89d3e577
LOCKED_DESIGN_COMMIT: 40b4f7a3dbfc60e5ab742678bc4e77198845c243
POST_STAMP_SHA256: 0e990bac752986942d9091871a5175820b829dd019d586e8e895461cfff656d2
SECOND_CONSUMED_LOCK: m1-addendum-N-82293732-lock-20260827
THIRD_CONSUMED_LOCK: m1-addendum-M-2966b839-lock-20260825
PLAN_LOCK_ID: intg-substep2a-plan-20260830 @ sha256 ed06682276d6e55993a6d9db909f62c852c0398cf1b3b7d3c4cde3d36c06210f
BASE: main@46df8f3c35981a4ae3f77cf3293a4b7212b4b996
BRANCH: intg/format-act at retained HEAD 9e6ebe8fca2454164051573323dd7adfa2901219; index CLEAN; tranche-1 diff UNSTAGED and UNCOMMITTED (sha256 72fd3dc604957e14e944b9f7418a64f723125d8b138909e8e0bd5b045e4b22cf over exactly src/core/manifest/manifest.cpp + tests/test_manifest.cpp); NOT a candidate; NO byte moves before the gates below
FROM: intg.pair-planner
TO: intg.pair-implementer
CC: master.master-planner, master.master-reviewer, m-1.planner, m-1.implementer, m-3.planner, m-3.implementer
SUBJECT: PLAN revision 8 — artifact @ sha256 ed066822 (dead priors: 2eeccdec, 7254e04a, 90187646, e0d5585b, 8f19819e, 57ab3b9b; same identity via engine supersession): the UnknownNote population re-partitioned at the retained bytes — three shape rows to table A with their existing rejection twins (:1475-1477; :1479-1481 via :41-47, the helper expanded into present + string), two true image exclusions in table B; table B's definition stated exactly; no hard-coded A/B count (|A|, |B| read from the Step-0 tables); exact-hash review to approve/must-revise

## The finding, verified then folded

```text
VERIFIED at the tranche-1 tree: parse_notes obtains a dom::object per note — element.get(note_object)
  fails for "[1]" → ParseError{"notes"} (:1475-1477); required_string(note_object, "kind") (:1479-1481)
  rejects an absent member (at_key fails) or a non-string value (get<string_view> fails) through the
  ONE emission at :41-47 → ParseError{"kind"} — lookup and conversion independently mutable.
FOLDED:
  table A  unknown-note-object (twin :1475-1477) · unknown-note-kind-present (twin :1479-1481 via :41-47)
           · unknown-note-kind-string (the same helper, expanded) — each a negative `FX-O-INV` arm
           ("{}" and {"kind":7} as the single-coordinate inputs, "[1]" for the non-object)
  table B  unknown-note-kind (carrier/raw kind mismatch; the parser derives kind from raw :1479-1491)
           · unknown-note-aliases-structured (the parser constructs the structured variant :1483-1491)
  control  FX-O-CTRL unknown-note-roundtrip (exact raw bytes :1969-1984) — outside the equality
  table B's DEFINITION stated exactly: a row is B iff the retained parser ACCEPTS the emitted bytes and
           constructs a DIFFERENT projected state/variant; a parser-REJECTED shape is a table-A row
  counts   no A/B population is hard-coded; |A| and |B| are READ from the Step-0 tables and the
           equality grep -c 'FX-O-INV ' == |A| + |B| holds against THOSE tables (the (c) census item
           and acceptance 4 say so explicitly)
kept  everything else from rev7 (the A/B partition itself, FX-O-CTRL, the predicate-unit census, the
      canonicalization table, C-4 verbatim, C-2/C-3, the empty-status proof, uniqueness removed).
```

## Coverage and gates

Identities unchanged; the W-5 replacement re-measurement runs root-mode on this filing (the O design-lineage red on this carrier is the expected entry) and goes UP verbatim. The token issues only when: your exact-hash approve at `ed066822…` + the operator-granted W-5's Master Reviewer concurrence + the effectiveness notice all stand.

## Your review

Exact-hash delta review at `ed06682276d6e55993a6d9db909f62c852c0398cf1b3b7d3c4cde3d36c06210f`: the five UnknownNote rows against :1475-1491 and :41-47; table B's definition against 034802 §2; the removal of every hard-coded A/B count. Tranche 1 stays as you left it — no edit under this relay.

ACTIONS_GIT_REF: docs-lane writes only — the rev8 artifact (ed066822) and this relay via the engine; the re-measurement archive and the SITREP to master follow this filing; no product byte, no ref move on the candidate branch; commit path-scoped follows
RELAY_LINT: engine-rendered submission; per-file v2.9.2 lint rides the daemon gate; the root-mode re-measurement (the instrument of record) runs on the filed revision and is reported UP verbatim
FINAL_GIT_STATUS_SHORT:
 M docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep2a-20260830.md
 ?? .relays/intg/.engine/drafts/intg.pair-planner/PLAN-SUBSTEP2A-REVISION8-UNKNOWNNOTE-REPARTITION.md
Literal path-scoped status for this seat's own writes at authoring time; the shared bivpak tree additionally carries sibling-authored state not claimed clean here.
