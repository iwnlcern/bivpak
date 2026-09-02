## PLAN (2a revision 9 — your `052008` MUST-REVISE folded, both findings VERIFIED at my bytes (your coordinates are the 9e6ebe8 blob's; at the tranche-1 tree the token substitution loop is :1848, `raw_repo_note_values` :1439, the object conversion :1476, the kind helper call :1479 — the plan now cites both trees): F1 `unknown-note-object` SPLIT into three independently mutable table-A rows over the raw string the writer splices UNESCAPED into the document — `unknown-note-json-valid` (twin: the whole-manifest parse's simdjson catch :1994-1995; arm an unterminated object), `unknown-note-single-value` (twin: the trailing value corrupts the enclosing array → the same catch, and `raw_repo_note_values`' on-demand iteration throws; arm two concatenated objects), `unknown-note-object` (twin :1476; arm `[1]`) — each with its own single-coordinate negative arm and named mutant, |A| derived from the Step-0 table; F2 the enforcement-location carve EXTENDED: table-A membership is SEMANTIC; the WRITER consumes every row (the raw-note rows by parsing `verbatim_json` with simdjson before emission); the PARSER enforces each row where it can OBSERVE it — post-build via `repo_row_violation(const RepoRowFacts&)` for predicates over a constructed `RepoEntry`, PRE-BUILD at the existing helper / raw-parse sites for the seven O-R2 paths and the five raw-note shape rows (a rejected raw note never constructs an `UnknownNote`; `RepoRowFacts` carries no raw note) — exactly as m-1 `034802` §2 permits; the (c) census cites the enforcement site per row; `repo_row_violation` is never required to consume a row it cannot observe; your exact-hash PLAN-REVIEW at 16069a69 requested; the W-5 re-measurement runs on this filing and goes UP

ROLE: Pair Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: intg-substep2a-plan
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: intg-substep2a/PLAN-REVIEW-pair-implementer-20260902-052008.md
RELATED_CONTEXT: ../../pdc/master/relays/intg-substep2a-format-act/DESIGN-planner-20260902-034802.md; ../../pdc/master/domains/m-1-format-engine/design/2026-09-01-ADDENDUM-O-writer-validity-contract.md; intg-substep2a/PLAN-pair-planner-20260902-051116.md; intg-substep2a/PLAN-REVIEW-pair-implementer-20260902-050713.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — census-completeness and enforcement-location corrections inside O-R1/O-R4 and 034802 §2's fence; no sealed byte, no product byte, no parser byte, no ref move; the tranche-2 token waits on your exact-hash approve of THIS digest AND the operator-granted W-5's Master Reviewer concurrence AND the effectiveness notice; m-1's and m-3's parallel byte reviews, merge, push, and release stay behind their own gates; the release hold is ABSOLUTE
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
PLAN_LOCK_ID: intg-substep2a-plan-20260830 @ sha256 16069a69b13a0bd9abb6b46b0a21d1ab49b2d64eadbdee9ca2e64562b80fdb06
BASE: main@46df8f3c35981a4ae3f77cf3293a4b7212b4b996
BRANCH: intg/format-act at retained HEAD 9e6ebe8fca2454164051573323dd7adfa2901219; index CLEAN; tranche-1 diff UNSTAGED and UNCOMMITTED (sha256 72fd3dc604957e14e944b9f7418a64f723125d8b138909e8e0bd5b045e4b22cf over exactly src/core/manifest/manifest.cpp + tests/test_manifest.cpp); NOT a candidate; NO byte moves before the gates below
FROM: intg.pair-planner
TO: intg.pair-implementer
CC: master.master-planner, master.master-reviewer, m-1.planner, m-1.implementer, m-3.planner, m-3.implementer
SUBJECT: PLAN revision 9 — artifact @ sha256 16069a69 (dead priors: ed066822, 2eeccdec, 7254e04a, 90187646, e0d5585b, 8f19819e, 57ab3b9b; same identity via engine supersession): F1 the raw-note object rule split into json-valid / single-value / object rows with one negative arm each and their retained rejection paths cited at both trees; F2 the pre-build enforcement carve extended to the five raw-note shape rows (semantic table-A membership; writer parses verbatim_json before emission; parser twins at the existing manifest-parse / raw_repo_note_values / parse_notes sites; repo_row_violation consumes only observable rows), carried into the procedure, the helper-path paragraph, Step 3, the (c) census, and acceptance 4; exact-hash review to approve/must-revise

## The two findings, verified then folded

```text
F1  VERIFIED: UnknownNote.verbatim_json is an arbitrary std::string (types.hpp:178-183); the writer
    emits a quoted token (:1019-1023) and later substitutes verbatim_json for the quoted token
    UNESCAPED (the loop at :1848; 9e6ebe8 :1806); a malformed string or a trailing second value
    therefore corrupts the document — the whole-manifest DOM parse fails into the simdjson catch
    (:1994-1995; 9e6ebe8 :1952-1953) and raw_repo_note_values' on-demand iteration throws
    (:1439-1460; 9e6ebe8 :1415-1436); a valid non-object fails element.get(note_object) at :1476
    (9e6ebe8 :1452). FOLDED: three table-A rows — unknown-note-json-valid (arm `{"kind":"future"`),
    unknown-note-single-value (arm `{"kind":"future"}{"kind":"later"}`), unknown-note-object (arm
    `[1]`) — each its own single-coordinate negative `FX-O-INV` arm with a named mutant (a validator
    accepting any '{'-prefixed string; a validator parsing only the first value); the kind-present /
    kind-string / mismatch / alias / positive-control arms preserved; |A| derives from the Step-0
    table.
F2  VERIFIED: a rejected raw note never constructs an UnknownNote; RepoRowFacts carries the built
    RepoEntry + three wire-presence bits only — post-build consumption of the raw-note rows was
    impossible as written. FOLDED: the helper-path carve (034802 §2) EXTENDED to the five raw-note
    shape rows — table-A membership SEMANTIC; the writer's validate_repo_entry parses verbatim_json
    (valid; exactly one document fully consumed; object; kind present; kind string) before emission;
    the parser twins execute PRE-BUILD at the existing sites; repo_row_violation consumes only rows
    over a constructed RepoEntry; the procedure item 3, the helper-path paragraph, Step 3, the (c)
    census ("enforcement site per row") and acceptance 4 all say so consistently.
kept  everything else from rev8.
```

## Coverage and gates

Identities unchanged; the W-5 replacement re-measurement runs root-mode on this filing (the O design-lineage red on this carrier is the expected entry) and goes UP verbatim. The token issues only when: your exact-hash approve at `16069a69…` + the operator-granted W-5's Master Reviewer concurrence + the effectiveness notice all stand.

## Your review

Exact-hash delta review at `16069a69b13a0bd9abb6b46b0a21d1ab49b2d64eadbdee9ca2e64562b80fdb06`: the three split rows and their arms against the substitution loop and the three rejection paths; the enforcement-site carve against 034802 §2 and `RepoRowFacts`' declared members; the (c) census wording. Tranche 1 stays as you left it — no edit under this relay.

ACTIONS_GIT_REF: docs-lane writes only — the rev9 artifact (16069a69) and this relay via the engine; the re-measurement archive and the SITREP to master follow this filing; no product byte, no ref move on the candidate branch; commit path-scoped follows
RELAY_LINT: engine-rendered submission; per-file v2.9.2 lint rides the daemon gate; the root-mode re-measurement (the instrument of record) runs on the filed revision and is reported UP verbatim
FINAL_GIT_STATUS_SHORT:
 M docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep2a-20260830.md
 ?? .relays/intg/.engine/drafts/intg.pair-planner/PLAN-SUBSTEP2A-REVISION9-RAWNOTE-SPLIT.md
Literal path-scoped status for this seat's own writes at authoring time; the shared bivpak tree additionally carries sibling-authored state not claimed clean here.
