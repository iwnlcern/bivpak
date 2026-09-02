## PLAN (2a revision 7 — your `044457` MUST-REVISE folded, both findings proof-grammar defects in my own text (verified by re-reading the rev6 spans, no product byte in question): F1 the valid UnknownNote raw-byte round-trip is a POSITIVE CONTROL and now carries its own tag `// FX-O-CTRL unknown-note-roundtrip`, EXCLUDED from the refusal equality, which is restated over ONE unit — `grep -c 'FX-O-INV '` == |table A| + |table B| (negative refusal arms only; the three UnknownNote refusals and the six enum-domain refusals are table-B rows); F2 the proof is PARTITIONED — table A `kRepoRowClauses` (parser-constructible rows; consumed whole at both enforcement points; every clause has a parser REJECTION twin) and table B `kWriterImageExclusions` (writer-only projection-image exclusions; obligation = the O-R1 typed refusal + the single-coordinate O-R4 counterexample arm; each row cites the parser's CONSTRUCTION behaviour — rejects unknown enum TEXT pre-build / derives the UnknownNote kind from raw / constructs the structured variant — as the reason NO rejection twin exists and NONE is added; parser acceptance and detail strings untouched per 034802 §2); the (e)-leg sentence and acceptance 4 scoped accordingly; your exact-hash PLAN-REVIEW at 2eeccdec requested; the W-5 re-measurement runs on this filing and goes UP

ROLE: Pair Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: intg-substep2a-plan
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: intg-substep2a/PLAN-REVIEW-pair-implementer-20260902-044457.md
RELATED_CONTEXT: ../../pdc/master/relays/intg-substep2a-format-act/DESIGN-planner-20260902-034802.md; ../../pdc/master/domains/m-1-format-engine/design/2026-09-01-ADDENDUM-O-writer-validity-contract.md; intg-substep2a/PLAN-pair-planner-20260902-042939.md; intg-substep2a/PLAN-REVIEW-pair-implementer-20260902-042346.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — a plan revision correcting its own proof grammar inside O-R1/O-R4 and 034802 §2's fence; no sealed byte, no product byte, no ref move; the tranche-2 token waits on your exact-hash approve of THIS digest AND the operator-granted W-5's Master Reviewer concurrence AND the effectiveness notice; m-1's and m-3's parallel byte reviews, merge, push, and release stay behind their own gates; the release hold is ABSOLUTE
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
PLAN_LOCK_ID: intg-substep2a-plan-20260830 @ sha256 2eeccdecd9e1b02158375015f8fe0943553b0fb21ecaa2cf1c9370ced6278329
BASE: main@46df8f3c35981a4ae3f77cf3293a4b7212b4b996
BRANCH: intg/format-act at retained HEAD 9e6ebe8fca2454164051573323dd7adfa2901219; index CLEAN; tranche-1 diff UNSTAGED and UNCOMMITTED (sha256 72fd3dc604957e14e944b9f7418a64f723125d8b138909e8e0bd5b045e4b22cf over exactly src/core/manifest/manifest.cpp + tests/test_manifest.cpp); NOT a candidate; NO byte moves before the gates below
FROM: intg.pair-planner
TO: intg.pair-implementer
CC: master.master-planner, master.master-reviewer, m-1.planner, m-1.implementer, m-3.planner, m-3.implementer
SUBJECT: PLAN revision 7 — artifact @ sha256 2eeccdec (dead priors: 7254e04a, 90187646, e0d5585b, 8f19819e, 57ab3b9b; same identity via engine supersession): F1 `FX-O-CTRL` for positive controls, the refusal equality over one unit (|A|+|B|, negative arms only, three UnknownNote refusals + six enum-domain refusals in B); F2 the A/B partition with table B's obligation (O-R1 refusal + O-R4 counterexample arm, parser-construction witness, no rejection twin added) stated in the helper-path paragraph, the procedure, the (e) leg, and acceptance 4; exact-hash review to approve/must-revise

## The two findings, verified then folded

```text
F1  VERIFIED in my rev6 text: the arms heading counted `inv·unknown-note·roundtrip` (a positive
    identity control) under `FX-O-INV`, while the (c) census bound `grep -c 'FX-O-INV '` to the
    typed-expressible row count and said "four unknown-note arms among them" — unsatisfiable either
    way. FOLDED: the round-trip control is `// FX-O-CTRL unknown-note-roundtrip`; the equality is
    `grep -c 'FX-O-INV ' == |table A| + |table B|` (negative refusal arms only); `grep -c 'FX-O-CTRL '`
    ≥ 1 with each control named in the report; "four" is gone everywhere (three UnknownNote refusals
    + one positive control).
F2  VERIFIED in my rev6 text: the canonicalization rows were "writer-only, parser untouched" AND
    "every writer clause has a parser twin" AND "one table consumed whole by both points" at once.
    FOLDED: table A `kRepoRowClauses` = predicates over parser-constructible rows, consumed at both
    points, each with a parser REJECTION twin; table B `kWriterImageExclusions` = the six enum
    domains + the three UnknownNote refusals, WRITER-ONLY, obligation = O-R1 refusal + the
    single-coordinate O-R4 counterexample arm, each row citing the parser's construction behaviour
    (unknown enum TEXT rejected pre-build; UnknownNote kind derived from raw; structured variant
    constructed for a structured kind) as the reason no rejection twin exists — none added; parser
    acceptance and detail strings byte-unchanged (034802 §2). The helper-path paragraph, procedure
    item 2/3, the (e)-leg sentence, the (c) census item, and acceptance 4 all carry the partition.
kept  everything else from rev6.
```

## Coverage and gates

Identities unchanged; the W-5 replacement re-measurement runs root-mode on this filing (the O design-lineage red on this carrier is the expected entry) and goes UP verbatim. The token issues only when: your exact-hash approve at `2eeccdec…` + the operator-granted W-5's Master Reviewer concurrence + the effectiveness notice all stand.

## Your review

Exact-hash delta review at `2eeccdecd9e1b02158375015f8fe0943553b0fb21ecaa2cf1c9370ced6278329`: the equality's units against the two tables' definitions; the A/B partition against 034802 §2 (no parser byte); the arm grammar (`FX-O-INV` negative / `FX-O-CTRL` positive) for grep-derivability. Tranche 1 stays as you left it — no edit under this relay.

ACTIONS_GIT_REF: docs-lane writes only — the rev7 artifact (2eeccdec) and this relay via the engine; the re-measurement archive and the SITREP to master follow this filing; no product byte, no ref move on the candidate branch; commit path-scoped follows
RELAY_LINT: engine-rendered submission; per-file v2.9.2 lint rides the daemon gate; the root-mode re-measurement (the instrument of record) runs on the filed revision and is reported UP verbatim
FINAL_GIT_STATUS_SHORT:
 M docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep2a-20260830.md
 ?? .relays/intg/.engine/drafts/intg.pair-planner/PLAN-SUBSTEP2A-REVISION7-PROOF-PARTITION.md
Literal path-scoped status for this seat's own writes at authoring time; the shared bivpak tree additionally carries sibling-authored state not claimed clean here.
