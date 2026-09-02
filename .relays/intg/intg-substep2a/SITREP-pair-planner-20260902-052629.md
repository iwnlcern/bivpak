## SITREP — 2a plan revision 9 FILED (`intg-substep2a/PLAN-pair-planner-20260902-052432.md`, artifact @ 16069a69; identities UNCHANGED — W-5's frozen selector holds): the implementer's `052008` MUST-REVISE of rev8 folded in-lane after verification at the retained bytes — the writer splices `UnknownNote.verbatim_json` UNESCAPED into the document (the substitution loop; tranche-1 :1848, 9e6ebe8 :1806), so the rev8 "one JSON object" rule hid two more independently mutable typed states (malformed JSON; a trailing second value) that the whole-manifest parse rejects; rev9 splits the row into json-valid / single-value / object with one negative arm each and their retained rejection paths, and EXTENDS the pre-build enforcement carve (034802 §2) to the five raw-note shape rows — semantic table-A membership, the writer parsing `verbatim_json` before emission, the parser twins at the existing raw-parse sites, `repo_row_violation(RepoRowFacts)` consuming only rows it can observe; the W-5 replacement re-measurement fires EXACTLY ONE entry on the citing carrier (the O design-lineage red, verbatim below; per-file OK) — archive `results/lint-root-sweep-2a-rev9-rawnote-split-20260902.txt` @ b25ef320; the isolation carrier stays silent; next gate = the implementer's exact-hash approve at 16069a69; token still behind that + W-5 concurrence + the effectiveness notice; tranche 1 stands unstaged at 9e6ebe8

ROLE: Pair Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: intg-substep2a-audit
PARENT_DISPATCH_ID: intg-substep2a-format-act
IN_REPLY_TO: intg-substep2a/PLAN-REVIEW-pair-implementer-20260902-052008.md
RELATED_CONTEXT: ../../docs/sprints/2026-08-27-intg-consent-fabric/results/lint-root-sweep-2a-rev9-rawnote-split-20260902.txt; intg-substep2a/PLAN-pair-planner-20260902-052432.md; ../../pdc/master/relays/intg-substep2a-format-act/DESIGN-planner-20260902-034802.md; ../../pdc/master/RESIDUALS.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no NEW gate — the standing ones: the operator-granted W-5's Master Reviewer concurrence and the effectiveness notice (master's), then the tranche-2 token after the implementer's exact-hash approve; no product byte, no ref move, no merge/push/publication/release; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: intg-format-act-plan
DESIGN_LOCK_ID: m1-addendum-O-63c46631-lock-20260901
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: intg-substep2a-plan-20260830 @ sha256 16069a69b13a0bd9abb6b46b0a21d1ab49b2d64eadbdee9ca2e64562b80fdb06
FROM: intg.pair-planner
TO: master.master-planner
CC: operator, master.master-reviewer, intg.pair-implementer, m-1.planner, m-1.implementer, m-3.planner, m-3.implementer
SUBJECT: SITREP — rev9 filed (052432; artifact 16069a69; identities frozen as W-5 selects): the rev8 must-revise (052008) folded in-lane — the raw-note object rule split into json-valid / single-value / object rows with arms, the pre-build enforcement carve extended to the raw-note shape rows (repo_row_violation consumes only observable rows); the W-5 replacement re-measurement = ONE fired entry on the citing carrier (the O design-lineage red, verbatim; per-file OK) archived @ b25ef320; token waits on the exact-hash approve at 16069a69 + concurrence + notice

## The W-5 replacement re-measurement, VERBATIM (the instrument of record)

```text
command   python3 <kit 2.9.2>/tools/relay-lint.py --relay-root .relays/intg --no-freshness
archive   docs/sprints/2026-08-27-intg-consent-fabric/results/lint-root-sweep-2a-rev9-rawnote-split-20260902.txt
          sha256 b25ef320515f3b2cd245a5ed24cffdefc93b504fd2b8bfd172c79f1e531718ad ; 279 lines ; rc 1
          (256 ERROR / 23 WARN root-wide — the standing historical population; design-lineage class 48
          = 46 prior + the rev9 carrier + its draft echo; design-edge class 0; the isolation carrier
          033604 silent)

FIRED SET ON THE CITING CARRIER (exactly one line):
ERROR .relays/intg: intg-substep2a/PLAN-pair-planner-20260902-052432.md: DESIGN_LOCK_ID 'm1-addendum-O-63c46631-lock-20260901' has no earlier same-owner DESIGN relay carrying matching DESIGN_DOC_ID

per-file contrast (NOT closure): relay-lint.py --no-freshness intg-substep2a/PLAN-pair-planner-20260902-052432.md → OK, rc 0
```

The fired identity is unchanged (O); both frozen identities preserved — the entry replaces to rev9 under the replacement rule.

## What rev9 folds (verified at the tranche-1 tree before folding)

```text
F1  unknown-note-object → three rows: json-valid (twin: the manifest parse's simdjson catch :1994-1995 /
    9e6ebe8 :1952-1953; arm an unterminated object), single-value (twin: the same catch and
    raw_repo_note_values' throw :1439-1460 / :1415-1436; arm two concatenated objects), object (twin
    :1476 / :1452; arm `[1]`) — each a single-coordinate negative arm with a named mutant
F2  the pre-build carve (034802 §2) extended to the five raw-note shape rows: table-A membership
    semantic; the writer parses verbatim_json before emission; the parser twins execute at the
    existing manifest-parse / raw_repo_note_values / parse_notes sites; repo_row_violation(RepoRowFacts)
    consumes only rows over a constructed RepoEntry; the (c) census cites the enforcement site per row
kept  everything else from rev8; coordinates now given at the tranche-1 tree with 9e6ebe8's in parentheses
```

## Standing state (both lanes)

- 2a: awaiting the implementer's exact-hash review at `16069a69…`; then the token behind the operator-granted W-5's concurrence + the effectiveness notice. Tranche 1 unstaged at `9e6ebe8` (`72fd3dc6…`).
- Isolation: plan `033604` @ `46e47a0a` awaiting the implementer's exact-hash review; the cross-repo edge structurally green (`033843`).
- No merge, no push (R-4.38 due point + R-4.46), no PR, no remote CI, no publication, no seal, no release. The release hold is ABSOLUTE.

ACTIONS_GIT_REF: docs-lane writes only — the rev9 artifact, the archived re-measurement, the filed 052432, and this SITREP via the engine; commit path-scoped follows; no product byte, no ref move
RELAY_LINT: engine-rendered submission; per-file v2.9.2 lint rides the daemon gate; the root-mode sweep above is the instrument of record
FINAL_GIT_STATUS_SHORT:
 M docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep2a-20260830.md
 ?? .relays/intg/.engine/drafts/intg.pair-planner/PLAN-SUBSTEP2A-REVISION9-RAWNOTE-SPLIT.md
 ?? .relays/intg/.engine/drafts/intg.pair-planner/SITREP-REV9-FILED-REMEASURED.md
 ?? .relays/intg/intg-substep2a/PLAN-pair-planner-20260902-052432.md
 ?? docs/sprints/2026-08-27-intg-consent-fabric/results/lint-root-sweep-2a-rev9-rawnote-split-20260902.txt
Literal path-scoped status for this seat's own writes at authoring time; the shared bivpak tree additionally carries sibling-authored state not claimed clean here.
