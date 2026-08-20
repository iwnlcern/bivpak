## IMPL — the W-2 join re-run FRESH and passing; the ONE R-4.32 four-file commit is DISPATCHED, with the three-site ordering bind adopted and my own collapsed count owned

ROLE: Planner
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: s4-floor-slice-e-r432-impl
PARENT_DISPATCH_ID: s4-floor-slice-e-r432-plan-review-rev4
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-REVIEW-IMPLEMENTER-SLICE-E-REV4-S18-R432-APPROVE-THREE-PHYSICAL-SITES-20260819-233449.md
RELATED_CONTEXT: .relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-SLICE-E-R432-FENCE-AMENDED-FOUR-FILE-COMMIT-KEYBOARD-RELEASED-DOWN-20260819-222228.md
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — the landed commit returns to m-3 for byte review over ALL FOUR files (their surfaces, their veto), and the merge stays held at the superseded presentation. Both platform suites are owed after implementation. The land order binds. The release hold is ABSOLUTE.
DESIGN_DOC_ID: m1-addendum-L-20260816
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m1-addendum-L-10c8e8e6-lock-20260817
TARGET_DESIGN_SHA256: 10c8e8e6ed1560d8fc03e9342ed539a1554fdc0a978ba864ce6427226e0daba4
TARGET_DESIGN_COMMIT: 8c7f9281d538704419ea7142a417495eec46e8a5
SECOND_DESIGN_LOCK: m1-addendum-K-5da667fa-lock-20260816, m3-addendum-5-b8686c75-lock-20260816, m3-addendum-4-9049de44-lock-20260816
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812, m3-addendum-3-eeb4dd01-lock-20260814
CONSUMER_DESIGN_LOCK_ID: m3-addendum-3-eeb4dd01-lock-20260814
PLAN_LOCK_ID: s4-floor-slice-e-plan-20260812
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer, m-3.planner, m-3.implementer, m-1.planner
SUBJECT: IMPL — R-4.32 four-file commit dispatched on the 233449 approve; W-2 join RE-RUN fresh at token time and passing on all eleven elements; the THREE-site ordering bind adopted after my §4.5 collapsed three insertion sites into two; both suites owed, counts by job and key, then m-3

DISPATCH IMPL

## 1. The W-2 join — RE-RUN at token time

**Not carried from `145233`.** Elements 5 and 6 decay; I re-measured them at this hour.

```text
SELECTOR   REPO ../bivpak · RELAY_ROOT .relays/s4/s4-floor-impl · PLAN_LOCK_ID
           s4-floor-slice-e-plan-20260812 · DESIGN_BINDINGS = rev4 §1's one-item list, rev4 having
           passed local plan-review at 233449 · ERROR_CLASS the cross-repo lineage red, measured
           firing on rev4 and naming this lock alone                                          PASS
1  OWNER LOCK DECLARATION  184619 · m-1.planner · LOCKED_DESIGN_SHA256 10c8e8e6ed…             PASS
2  VP EXACT-PIN APPROVAL   154000 · master.orchestrator-reviewer · TARGET_DESIGN_SHA256 10c8e8e6ed…  PASS
3  GATE DISPOSITION        144843 · m-1.implementer · TARGET_DESIGN_SHA256 10c8e8e6ed…         PASS
4  PRECEDENCE              144843 < 154000 < 154351 < 184619 < 223918 (rev4) < 233449 (approve)
                           < this token                                                       PASS
5  NO LATER SUPERSESSION   RE-MEASURED: ARCHITECTURE.md's L row still LOCKED
                           `m1-addendum-L-10c8e8e6-lock-20260817`                             PASS
6  NO LATER UNLOCKED EDIT  RE-MEASURED: live L doc still b3599511…; diff still ONE hunk
                           `14,18c14,47`; last commit still 437520e                           PASS
```

**Eleven elements, zero mismatches.** Also verified: rev4 hashes `8be6217e10bfb020467e15498d875655093a3830fa84f1e41aefa1f3721b9574` at BOTH the worktree and the `276099f` blob — equal to the review's declared value, so the approve is on the filed bytes.

## 2. The three-site ordering bind — ADOPTED, and my §4.5 undercounted

rev4 §4.5 named **"JSON enum order and `rows` order"** — two lists. **There are THREE physical insertion
sites**, because the exit-map's JSON *row* order is a third I collapsed into "JSON enum order." A token
applying the rule to only some of them would leave the rest to a keyboard, which is the whole thing §4.5
exists to prevent. Owned; the bind is:

```text
1  schemas/biv-exit-map.v1.json        the ROW immediately after the UnknownAgentSkipped row
2  schemas/biv-json-envelope.v1.schema.json  the ENUM MEMBER immediately after "UnknownAgentSkipped"
3  tests/test_envelope.cpp             the ExpectedRow ELEMENT immediately after the UnknownAgentSkipped element
```

Same derivation at all three: A4.3's *"the split, and what `UnknownAgentSkipped` keeps."* **These remain the
only non-derived decisions in the commit, and they are now deterministic at every site.**

## 3. What implements — rev4 governs; this relay is not the spec

**Implement to rev4 and to the A4 lock bytes (`9049de44…` @ `40bd88a6`), not to this paraphrase.**

```text
exit-map row     {"kind": "EntrySchemaSkipped", "class": "advisory", "exit": 0}
                 kind + exit from A4.1 GOLDEN; class from the TOTAL exception-free exit->class invariant
                 across all 26 rows (independently re-derived at your seat and at mine)
envelope enum    one member at the SINGLE measured session-row kind site — confirmed by two independent
                 enumerations (ten enums, one kind enum; the other kind properties are two free-form
                 strings and two const discriminators, none a second site for this value)
blob-id pins     BOTH constants RECOMPUTED via `git hash-object` on the FINAL schema bytes, AFTER both
                 schema files reach their landed form. Never hand-authored, never copied from any relay
C++ rows element {"EntrySchemaSkipped", "advisory", exit_for_error(biv::ErrKind::EntrySchemaSkipped)}
                 — the FUNCTION form, not a literal 0; rows.size() becomes 27 against a 27-kind exit map
ORDERING         all three sites per §2
FORBIDDEN        any other kind touched (SessionsStaged and every other row BYTE-EXACT) · any invented
                 structure · any authored value · any fifth file · any count cell · any .github byte ·
                 any product byte · any other test byte
R-4.34           BOUND NEGATIVELY — do NOT derive the kind-set from the ErrKind enum here. That repair
                 changes what the instrument measures and is m-3's with VP visibility.
```

## 4. Scope

SCOPE_DIFF:
- schemas/biv-exit-map.v1.json -> in
- schemas/biv-json-envelope.v1.schema.json -> in
- harness/selftest/test_envelope.py -> in
- tests/test_envelope.cpp -> in
SCOPE_DIFF_RESULT: all-in

SCOPE_ROW_EVIDENCE:
- `schemas/biv-exit-map.v1.json` — rev4 §4.1 only: one row, every field owner-sourced, placed per §2.1.
- `schemas/biv-json-envelope.v1.schema.json` — rev4 §4.2 only: one enum member at the single measured session-row `kind` site, placed per §2.2.
- `harness/selftest/test_envelope.py` — rev4 §4.3 only: the two `CURRENT_LOCKED_SCHEMA_BLOBS` values, recomputed from the landed bytes. Mechanically necessary: the test hashes the very files this fix changes.
- `tests/test_envelope.cpp` — rev4 §4.4 only: one `rows` element, placed per §2.3. Mechanically necessary: the exact-cardinality check counts the very rows this fix adds.

**OUT — a discovered need is a STOP to me, never a licence:** every other byte of all four files; any fifth path; every product path; `.github/**` including all count cells; `pdc/**`; the R-4.34 derive-from-enum repair.

## 5. Evidence

```text
RE-RUN   OWED — schemas/ is runtime-consumed four ways; BOTH platform suites re-observe on the fixed tree
COUNTS   :68/:71/:268/:271 expected UNCHANGED, evidenced BY JOB AND MAPPING KEY, never by living position
         (the A20 replacement). GROUND, not hope: the gate parses `OverallResultsCases` — CASE counts —
         and a `rows` element inside an EXISTING TEST_CASE adds ASSERTIONS, never CASES.
STOPS    ANY of these is a STOP to me and is NEVER repaired by widening at the keyboard:
           a fifth path · an extra changed byte in any of the four · a second enum site you find while
           landing · a test failure · ANY count movement
A22-A27  as stated in rev4, with A25 requiring you to REPORT both computed blob-ids and the command,
         and A27 requiring both suites re-observed with the four values reported by job and key
```

## 6. Return path

```text
land    ONE commit, message NAMING R-4.32, touching exactly the four §4 paths
route   to m-3 for byte review over ALL FOUR files — their surfaces, their veto; the commit is LOCAL
        and unwinds on veto
then    m-3 PASS -> the orchestrator's spine check -> master re-presents the merge gate to the operator
        against the NAMED TARGET. Nothing merges before that; the 165410 presentation stays superseded.
```

**Standing constraints unchanged:** GitHub Actions NOT invoked; branch stays LOCAL and UNPUBLISHED — no push, no PR, no merge, no seal, no publication; live `~/.claude` / `~/.codex` never read-for-mutation or written; no credential collection. **Any gap rev0–rev4 plus §2 do not decide is a STOP to me**, never a keyboard call.

Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product, schema, test, fixture, workflow, documentation, branch, Docker, push, PR, Actions, merge, publication, deployment, or release act at this seat — this relay delegates. Read-only this pass: the `233449` approve read in full; rev4 re-hashed from BOTH the worktree and the `276099f` blob (`8be6217e…`, equal to each other and to the review's declared value); the W-2 join RE-RUN — elements 1-3 re-read for their identity fields at `184619`/`154000`/`144843`, element 5 re-measured against `master/ARCHITECTURE.md`'s L row, element 6 re-measured by re-hashing the live L doc (`b3599511…`), re-diffing against `8c7f9281` (one Status-block hunk `14,18c14,47`) and re-checking its last commit (`437520e`). I ran no container and no build. This relay + its INDEX row ride ONE explicit-path docs-lane commit whose SHA lands after filing.
RELAY_LINT: per D-3.4 + D-3.4(a) — clock read immediately before filing (D-5.10), per-file WITH freshness and the exit status checked un-piped and READ before committing; `--relay-root` run against this file and its output READ IN FULL. Standing reds disclosed: the cross-repo DESIGN-lineage class, whose coverage for the listed identity is the eleven-element W-2 join re-run in §1; INDEX cell-count (R-4.27) at 132, 222, 324, 362, 384, 388, 408, 435; INDEX time inversions at 222 and 393. `.relays/s4/INDEX.md` tail re-read before appending; `--index`; add and commit path-scoped; my appended row is 10-cell clean.
FINAL_GIT_STATUS_SHORT: literal path-scoped `git status --short` for this seat's two writes, captured at staging (the implementation worktree `s4-floor-slice-e-stage1a` reports EMPTY `git status --short` at `4427bb3`; the shared main checkout carries sibling-authored untracked state, excluded and unclaimed):
  M  .relays/s4/INDEX.md
  A  .relays/s4/s4-floor-impl/IMPL-PLANNER-SLICE-E-S18-R432-DISPATCH-IMPL-TOKEN-20260819-235119.md

CARRY LIST (D-8.5):
- `.relays/s4/s4-floor-impl/IMPL-PLANNER-SLICE-E-S18-R432-DISPATCH-IMPL-TOKEN-20260819-235119.md` → `s4-floor.implementer` — LIVE bare implementation token, parented to the `233449` rev4 plan-review approve
- THE W-2 JOIN WAS RE-RUN AT TOKEN TIME and not carried from 145233, since elements five and six decay: all eleven PASS, with the selector's five carrying rev4's one-item list now current after its 233449 approval, elements one through three re-read at 184619, 154000 and 144843 all naming SHA 10c8e8e6, element four's precedence holding, element five re-measured with ARCHITECTURE.md's L row still LOCKED m1-addendum-L-10c8e8e6-lock-20260817, and element six re-measured with the live L doc still hashing b3599511, the diff still one hunk at 14,18c14,47 and the last commit still 437520e. rev4 also re-hashed to 8be6217e at BOTH the worktree and the 276099f blob, equal to the review's declared value
- THE THREE-SITE ORDERING BIND IS ADOPTED AND MY OWN COUNT WAS WRONG: rev4 section 4.5 named JSON enum order and rows order, which is TWO lists, but there are THREE physical insertion sites because the exit-map's JSON ROW order is a third that I collapsed into JSON enum order; a token applying the rule to only some of them would leave the rest to a keyboard, which is exactly what section 4.5 exists to prevent. The bind is now the exit-map row immediately after the UnknownAgentSkipped row, the envelope enum member immediately after UnknownAgentSkipped, and the C++ ExpectedRow element immediately after the UnknownAgentSkipped element, all three derived from A4.3's split framing, and these remain the only non-derived decisions in the commit
- WHAT IMPLEMENTS, to rev4 and the A4 lock bytes and not this paraphrase: the exit-map row with kind and exit from A4.1 GOLDEN and class from the TOTAL exception-free exit-to-class invariant across all 26 rows, independently re-derived at both seats; one enum member at the SINGLE measured session-row kind site, confirmed by two independent enumerations finding ten enums and one kind enum with the other kind properties being two free-form strings and two const discriminators; BOTH blob-id constants RECOMPUTED via git hash-object on the FINAL schema bytes after both files reach landed form, never hand-authored and never copied from a relay; and one C++ rows element using the FUNCTION form exit_for_error rather than a literal, taking rows.size to 27 against a 27-kind exit map
- FORBIDDEN: any other kind touched with SessionsStaged and every other row BYTE-EXACT, any invented structure, any authored value, any fifth file, any count cell, any .github byte, any product byte, any other test byte; and R-4.34 is BOUND NEGATIVELY so the derive-from-enum repair is not attempted here, belonging to m-3 with VP visibility
- EVIDENCE: the re-run is OWED with both platform suites re-observing on the fixed tree; the four count cells are expected UNCHANGED and evidenced BY JOB AND MAPPING KEY never by living position per the A20 replacement, with the GROUND stated rather than hoped since the gate parses OverallResultsCases meaning CASE counts and a rows element inside an EXISTING TEST_CASE adds assertions and never cases; and ANY of a fifth path, an extra changed byte, a second enum site found while landing, a test failure, or ANY count movement is a STOP to this seat and is NEVER repaired by widening at the keyboard
- RETURN PATH: land ONE commit naming R-4.32 touching exactly the four scope paths, route it to m-3 for byte review over ALL FOUR files with the commit LOCAL and unwindable on veto, then on m-3's PASS the orchestrator's spine check and master's re-presentation of the merge gate against the NAMED TARGET, with nothing merging before that and the 165410 presentation staying superseded. Actions NOT invoked; branch LOCAL and UNPUBLISHED; live home agent stores never read-for-mutation or written; no credential collection; any gap rev0 through rev4 plus the three-site bind do not decide is a STOP to this seat; merge is not push is not release; release hold ABSOLUTE
