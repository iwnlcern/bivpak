## PLAN rev4 (the ONE R-4.32 four-file commit — every landed value traced to an owner source, the two ordering choices disclosed rather than buried, and one measurement that rules out a missed site) — **rev3 (`144504`, approved `144652`) and through it rev2/rev1/rev0 carry forward VERBATIM; the landed heads `e8aabc4` and `4427bb3` are not reopened. rev4 adds ONE bind, S-18, and four scope rows.** **I READ THE A4 LOCK'S OWN BYTES, not the paraphrase: the doc at `40bd88a6` hashes `9049de44…` (verified), its REOPENS line pins the shape as *"one enum member, one wire string, one exit-map row, one row-mapping split"*, and A4.1 GOLDEN fixes `wire string "EntrySchemaSkipped"` (PascalCase) and `exit 0`, with A4.2 deriving that 0 from sealed §A1.2b rather than by fiat. So the lock determines the KIND and the EXIT. It does NOT determine the JSON `class` field, and that is exactly where a keyboard would invent — so I measured instead.** **THE `class` IS DERIVED, NOT CHOSEN, AND THE MEASUREMENT IS TOTAL: across ALL 26 existing exit-map rows the class↔exit correspondence is exception-free — exit 0 → `advisory` (only), 2 → `divergence`, 3 → `refusal`, 4 → `mid-fail`, 5 → `usage`. Since A4 fixes exit 0, `class` follows with no residue, and the two existing exit-0 rows (`SessionsConsentSkipped`, `SessionsStaged`) are the byte-shape template. Nothing in the exit-map row is authored.** **AND I RULED OUT A MISSED SITE RATHER THAN ASSUMING ONE — the same class of omission that produced R-4.32 in the first place: I enumerated EVERY `enum` in the envelope schema (ten of them). Exactly ONE constrains session-row kinds, at `/properties/result/anyOf[1]/…/sessions/items/properties/kind`, holding six members; the error envelope's `kind` at `:19` and `:185` is `{"type": "string"}` — free-form, no enum, nothing owed there. **One site, not two, and that is measured, not inferred.** The site itself is determined by where the value lands on the wire: `sessions.cpp:268`/`:279` emit this kind into the session row.** **TWO ORDERING CHOICES EXIST AND I AM NAMING THEM RATHER THAN LETTING THEM PASS AS DERIVED: JSON enum order and `rows` order are not determined by anything — I bind both to IMMEDIATELY AFTER `UnknownAgentSkipped`, derived from A4.3's own framing (*"the split, and what `UnknownAgentSkipped` keeps"*), because the kind is that kind's split. If m-3 wants either elsewhere, it is theirs to redirect and I would rather they see the choice than discover it.** **R-4.34 IS NOT THIS COMMIT'S JOB and rev4 binds that negatively: do NOT derive the expected kind-set from the `ErrKind` enum here. That repair changes what the instrument measures and is m-3's with VP visibility.** No token in this relay — my Implementer's PLAN-REVIEW on rev4 is the next gate, and the W-2 join re-runs fresh at the token. `4427bb3` unchanged; branch LOCAL and UNPUBLISHED; the `165410` presentation stays SUPERSEDED-PENDING and nothing merges. Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ROLE: Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-floor-slice-e-r432-plan-rev4
PARENT_DISPATCH_ID: s4-floor-slice-e-r432-fence-amended-keyboard-released
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-SLICE-E-R432-FENCE-AMENDED-FOUR-FILE-COMMIT-KEYBOARD-RELEASED-DOWN-20260819-222228.md
RELATED_CONTEXT: .relays/s4/s4-floor-impl/SITREP-PLANNER-SLICE-E-R432-CONFIRMED-BUT-FENCE-UNSATISFIABLE-TWO-TEST-SURFACES-20260819-210524.md
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — the landed commit takes m-3's byte review over ALL FOUR files (their surfaces, their veto), and the merge stays held at the superseded presentation. No token here; my Implementer's PLAN-REVIEW is the next gate. The land order binds. The release hold is ABSOLUTE.
DESIGN_DOC_ID: m1-addendum-L-20260816
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m1-addendum-L-10c8e8e6-lock-20260817
SECOND_DESIGN_LOCK: m1-addendum-K-5da667fa-lock-20260816, m3-addendum-5-b8686c75-lock-20260816, m3-addendum-4-9049de44-lock-20260816
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812, m3-addendum-3-eeb4dd01-lock-20260814
CONSUMER_DESIGN_LOCK_ID: m3-addendum-3-eeb4dd01-lock-20260814
PLAN_LOCK_ID: s4-floor-slice-e-plan-20260812
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, m-3.planner, m-3.implementer, m-1.planner
SUBJECT: PLAN rev4 — adds S-18, the ONE R-4.32 four-file commit, with every value traced to an owner source (A4 lock for kind and exit; a TOTAL exit-to-class invariant across all 26 rows for class; recomputed blob ids; parity plus exit_for_error), one measured site not two, and the two ordering choices disclosed; R-4.34 bound negatively; PLAN-REVIEW requested

## 1. W-2 LITERAL BINDING LIST

Carried forward from rev3 unchanged — rev4 becomes the current approved revision on its approval, and the
current revision's list IS the coverage.

W2_BINDING_LIST:
- m1-addendum-L-20260816 -> m1-addendum-L-10c8e8e6-lock-20260817
W2_BINDING_LIST_COUNT: 1

Still the measured fired set. **Restating a non-firing identity would fail the selector**, so it stays at one.

## 2. What rev4 changes

```text
ADDS       S-18 (§4) and four scope rows (§5)
CARRIES    rev3 (144504, approved 144652) and through it rev2/rev1/rev0, VERBATIM: S-1..S-17, the sixteen
FORWARD    live legs, A1..A21 (A20 as replaced at the 145233 token), G1..G9, every fence
NOT        the landed heads e8aabc4 (owner-passed) and 4427bb3 (at m-3 for R-4.31) are NOT reopened
REOPENED
```

## 3. What the A4 lock determines — read at its own bytes

```text
doc        pdc master/domains/m-3-restore-cli/design/2026-08-15-addendum-4-entry-schema-skipped-kind.md
lock       m3-addendum-4-9049de44-lock-20260816 @ 40bd88a6 — the blob hashes 9049de44…   VERIFIED
shape      REOPENS line: "one enum member, one wire string, one exit-map row, one row-mapping split"
A4.1       wire string "EntrySchemaSkipped" (PascalCase, per support/error.cpp convention) · exit 0   GOLDEN
A4.2       exit 0 DERIVED from sealed §A1.2b (chosen outcome), not by fiat
NOT        the lock does NOT determine the JSON `class` field, nor enum member ORDER. §4.2 and §4.5 handle
DETERMINED those explicitly rather than letting a keyboard fill them.
```

## 4. S-18 — the ONE R-4.32 commit

### 4.1 `schemas/biv-exit-map.v1.json` — the row, fully derived

```text
LAND      {"kind": "EntrySchemaSkipped", "class": "advisory", "exit": 0}
kind      A4.1 GOLDEN
exit      A4.1 GOLDEN (and A4.2's derivation); envelope.cpp:411 returns 0
class     DERIVED FROM A TOTAL INVARIANT, measured across ALL 26 existing rows:
            exit 0 -> advisory (ONLY)   2 -> divergence   3 -> refusal   4 -> mid-fail   5 -> usage
          exception-free, so exit 0 fixes class with NO residue
shape     the two existing exit-0 rows are the byte template:
            {"kind": "SessionsConsentSkipped", "class": "advisory", "exit": 0}
            {"kind": "SessionsStaged", "class": "advisory", "exit": 0}
```

### 4.2 `schemas/biv-json-envelope.v1.schema.json` — ONE site, measured not assumed

```text
SITE      /properties/result/anyOf[1]/properties/sessions/properties/agents/items/properties/sessions/
          items/properties/kind — the enum with six members
WHY       this is where the value lands on the wire: sessions.cpp:268/:279 emit the kind into the SESSION ROW
ONE SITE  I enumerated EVERY enum in the file (ten). Exactly ONE constrains session-row kinds. The error
          envelope's `kind` at :19 and :185 is {"type": "string"} — FREE-FORM, no enum, nothing owed.
          Measured, not inferred — a missed second site is the very shape that produced R-4.32.
LAND      add "EntrySchemaSkipped" to that enum. NOTHING else in the file.
```

### 4.3 `harness/selftest/test_envelope.py` — the two constants, recomputed

```text
LAND      the TWO values in CURRENT_LOCKED_SCHEMA_BLOBS, RECOMPUTED from the schema bytes that ACTUALLY LAND
HOW       `git hash-object <file>` on the FINAL files — the same algorithm the test uses
          (`sha1(b"blob " + len + b"\0" + data)`, :19-20)
NEVER     hand-author a hash; never copy one from this plan, the review or the token
NOTHING   else in this file — no other constant, no test body
```

### 4.4 `tests/test_envelope.cpp` — one `rows` element

```text
LAND      ONE element: {"EntrySchemaSkipped", "advisory", biv::report::exit_for_error(biv::ErrKind::EntrySchemaSkipped)}
class     "advisory" — the same total invariant as §4.1
exit      use the FUNCTION form exit_for_error(...), as the majority of rows do, NOT a literal 0 — the
          function is the product's own answer and a literal would restate it by hand
effect    rows.size() becomes 27, so the exact-cardinality CHECK matches the 27-kind exit map
NOTHING   else — no other row edited, no assertion added or removed, no restructuring
```

### 4.5 The two ORDERING choices — named, not buried

```text
JSON enum order and `rows` order are determined by NOTHING. I bind both to IMMEDIATELY AFTER
`UnknownAgentSkipped`, derived from A4.3's own framing — "the split, and what UnknownAgentSkipped keeps" —
because this kind is that kind's split. THESE ARE THE ONLY TWO NON-DERIVED DECISIONS IN THE COMMIT, and
they are stated here so m-3 sees them rather than discovers them. If m-3 wants either elsewhere, theirs to
redirect.
```

### 4.6 What S-18 must NOT do

```text
no other kind touched — SessionsStaged and every other row stay BYTE-EXACT
no invented schema structure · no authored value · no fifth file · no count cell · no .github byte
no product byte · no other test byte
R-4.34 BOUND NEGATIVELY: do NOT derive the expected kind-set from the ErrKind enum here. That repair
changes what the instrument measures and is m-3's to design with VP visibility.
```

## 5. Scope

SCOPE_DIFF:
- schemas/biv-exit-map.v1.json -> in
- schemas/biv-json-envelope.v1.schema.json -> in
- harness/selftest/test_envelope.py -> in
- tests/test_envelope.cpp -> in
SCOPE_DIFF_RESULT: all-in

SCOPE_ROW_EVIDENCE:
- `schemas/biv-exit-map.v1.json` — §4.1 ONLY: one row, every field owner-sourced.
- `schemas/biv-json-envelope.v1.schema.json` — §4.2 ONLY: one enum member at the single measured session-row `kind` site.
- `harness/selftest/test_envelope.py` — §4.3 ONLY: the two `CURRENT_LOCKED_SCHEMA_BLOBS` values, recomputed from the landed bytes. Mechanically necessary — the test hashes the very files the fix changes.
- `tests/test_envelope.cpp` — §4.4 ONLY: one `rows` element. Mechanically necessary — the exact-cardinality check counts the very rows the fix adds.

**OUT — a discovered need is a STOP to me:** every other byte of all four files; any fifth path; every product path; `.github/**` including all count cells; `pdc/**`; the R-4.34 derive-from-enum repair.

## 6. Re-run and counts

```text
RE-RUN   OWED. schemas/ is consumed at runtime in FOUR ways — CMakeLists.txt:221/:233,
         harness/bivharness/scenario.py, harness/selftest/test_envelope.py, tests/test_envelope.cpp:201/:250.
         BOTH platform suites re-observe on the fixed tree.
COUNTS   :68/:71/:268/:271 expected UNCHANGED, and here is the GROUND rather than the hope: the gate parses
         `OverallResultsCases` — CASE counts. A `rows` element inside an EXISTING TEST_CASE adds
         ASSERTIONS, never CASES. So the cells should not move.
STOP     ANY count movement is a STOP routed to me — never transcribed, never reconciled at the keyboard.
```

## 7. Acceptance criteria

```text
A22  the commit touches EXACTLY the four §5 paths and no other byte in any of them
A23  the exit-map row is byte-shaped like the two exit-0 precedents; SessionsStaged and every other row
     are BYTE-EXACT unchanged
A24  the envelope enum gains exactly one member at the single §4.2 site; no other enum in the file moves
A25  both blob-id constants RECOMPUTED via `git hash-object` on the LANDED schema files — report both
     computed values and the command you ran; `harness-selftest` GREEN
A26  `rows.size()` == the exit map's `"kind": "` count == 27, with the cardinality CHECK passing; the
     exit column uses `exit_for_error(...)`, not a literal
A27  both platform suites re-observed on the fixed tree; the four count cells UNCHANGED, evidenced BY JOB
     AND MAPPING KEY (never by line position, per the A20 replacement); any movement reported as a STOP
```

## 8. Questions for my Implementer

1. Do you agree the exit→class correspondence is TOTAL across all 26 rows? **Re-derive it yourself** — if
   you find a single exception, `class` becomes an authored choice and that is a STOP, not a judgment call.
2. Do you find any SECOND enumerated kind site in the envelope schema? I found one and measured the error
   envelope's `kind` as free-form; a missed site is exactly how R-4.32 happened.
3. Do you accept the two ordering choices in §4.5, or would you place either differently?
4. Anything in S-18 or A22–A27 you can refute. rev0–rev3 are approved and are not reopened.

Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product, schema, test, fixture, workflow, documentation, branch, Docker, push, PR, Actions, merge, publication, deployment, or release act at this seat — plan-only. Read-only this pass: the A4 addendum read at pdc object `40bd88a6` with its blob re-hashed to `9049de44…` and its REOPENS / A4.1 / A4.2 / A4.3 clauses read; at `4427bb3`, `schemas/biv-exit-map.v1.json` parsed and ALL 26 rows tabulated for the exit→class correspondence (exception-free) with the two exit-0 precedents read; `schemas/biv-json-envelope.v1.schema.json` parsed and ALL TEN enums enumerated to establish that exactly one constrains session-row kinds, plus its free-form `kind` sites at `:19`/`:185`; `harness/selftest/test_envelope.py:1-40` re-read for the pin algorithm; `tests/test_envelope.cpp:195-262` re-read for the `rows` list, the cardinality check and the `SessionsStaged` template; the Linux gate re-confirmed to parse `OverallResultsCases`. I ran no container and no build. This relay + its INDEX row ride ONE explicit-path docs-lane commit whose SHA lands after filing. No token issued — it follows the PLAN-REVIEW on rev4, and the W-2 join re-runs fresh there.
RELAY_LINT: per D-3.4 (v2.9) — per-file WITH freshness (clock read immediately before filing, per D-5.10 instance 4), exit status checked un-piped and READ before committing; `--relay-root` run against this file and its output READ IN FULL. Standing reds disclosed: the cross-repo DESIGN-lineage class, of which this thread's plan revisions are members and whose coverage for the listed identity is the W-2 join re-run at each token; INDEX cell-count (R-4.27) at 132, 222, 324, 362, 384, 388, 408, 435; INDEX time inversions at 222 and 393. `.relays/s4/INDEX.md` tail re-read before appending; `--index`; add and commit path-scoped; my appended row is 10-cell clean.
FINAL_GIT_STATUS_SHORT: literal path-scoped `git status --short` for this seat's two writes, captured at staging (the implementation worktree `s4-floor-slice-e-stage1a` reports EMPTY `git status --short` at `4427bb3`; the shared main checkout carries sibling-authored untracked state, excluded and unclaimed):
  M  .relays/s4/INDEX.md
  A  .relays/s4/s4-floor-impl/PLAN-PLANNER-SLICE-E-REV4-S18-R432-FOUR-FILE-COMMIT-DERIVATIONS-PINNED-20260819-223918.md

CARRY LIST (D-8.5):
- `.relays/s4/s4-floor-impl/PLAN-PLANNER-SLICE-E-REV4-S18-R432-FOUR-FILE-COMMIT-DERIVATIONS-PINNED-20260819-223918.md` → `s4-floor.implementer`
- rev4 ADDS S-18, the ONE R-4.32 four-file commit, plus four scope rows; rev3 at 144504 approved at 144652 and through it rev2, rev1 and rev0 carry forward VERBATIM with S-1 through S-17, the sixteen live legs, A1 through A21 with A20 as replaced at the 145233 token, and G1 through G9; the landed heads e8aabc4 and 4427bb3 are NOT reopened. W-2's literal binding list carries forward unchanged at one item
- THE A4 LOCK WAS READ AT ITS OWN BYTES, not the paraphrase: the doc at 40bd88a6 hashes 9049de44, its REOPENS line pins the shape as one enum member, one wire string, one exit-map row and one row-mapping split, and A4.1 GOLDEN fixes the wire string EntrySchemaSkipped in PascalCase and exit 0, with A4.2 deriving that 0 from sealed A1.2b rather than by fiat. The lock determines the KIND and the EXIT; it does NOT determine the JSON class field or enum member order, which is precisely where a keyboard would invent
- THE class IS DERIVED AND THE MEASUREMENT IS TOTAL: across ALL 26 existing exit-map rows the class-to-exit correspondence is exception-free, with exit 0 mapping to advisory only, 2 to divergence, 3 to refusal, 4 to mid-fail and 5 to usage, so A4's exit 0 fixes class with NO residue, and the two existing exit-0 rows SessionsConsentSkipped and SessionsStaged are the byte template. Nothing in the exit-map row is authored
- A MISSED SITE WAS RULED OUT BY MEASUREMENT rather than assumed, that being the same class of omission that produced R-4.32: every enum in the envelope schema was enumerated, ten in total, and exactly ONE constrains session-row kinds at the sessions items kind path holding six members, while the error envelope's kind at :19 and :185 is free-form string with no enum so nothing is owed there. One site, not two, measured. The site is determined by where the value lands on the wire, since sessions.cpp:268 and :279 emit the kind into the session row
- TWO ORDERING CHOICES EXIST AND ARE NAMED RATHER THAN BURIED: JSON enum order and rows order are determined by nothing, and both are bound to IMMEDIATELY AFTER UnknownAgentSkipped, derived from A4.3's own framing of the split and what UnknownAgentSkipped keeps, because this kind is that kind's split. These are the ONLY two non-derived decisions in the commit and are stated so m-3 sees rather than discovers them; if m-3 wants either elsewhere it is theirs to redirect
- THE FOUR LANDED CHANGES: the exit-map row with every field owner-sourced; one enum member at the single measured envelope site; the TWO blob-id constants RECOMPUTED via git hash-object on the LANDED files using the same algorithm the test uses, never hand-authored and never copied from a relay; and ONE rows element using the FUNCTION form exit_for_error rather than a literal 0, since the function is the product's own answer, taking rows.size() to 27 so the exact-cardinality check matches the 27-kind exit map
- FORBIDDEN: any other kind touched with SessionsStaged and every other row byte-exact, any invented structure, any authored value, any fifth file, any count cell, any .github byte, any product byte, any other test byte; and R-4.34 IS BOUND NEGATIVELY, so the derive-from-enum repair must NOT be attempted here since it changes what the instrument measures and is m-3's with VP visibility
- RE-RUN OWED since schemas are consumed at runtime in FOUR ways, so both platform suites re-observe on the fixed tree; the four count cells are expected UNCHANGED with the GROUND stated rather than hoped, the gate parsing OverallResultsCases so a rows element inside an EXISTING TEST_CASE adds assertions and never cases; ANY count movement is a STOP routed to this seat, never transcribed
- SIX ACCEPTANCE CRITERIA A22 through A27 and four questions for the review, including a REQUIRED independent re-derivation of the exit-to-class totality (a single exception makes class an authored choice and therefore a STOP) and an independent search for a SECOND enumerated kind site; NO token in this relay, the PLAN-REVIEW on rev4 being the next gate with the W-2 join re-running fresh at the token; 4427bb3 unchanged; branch LOCAL and UNPUBLISHED; the 165410 presentation stays SUPERSEDED-PENDING and nothing merges; merge is not push is not release; release hold ABSOLUTE
