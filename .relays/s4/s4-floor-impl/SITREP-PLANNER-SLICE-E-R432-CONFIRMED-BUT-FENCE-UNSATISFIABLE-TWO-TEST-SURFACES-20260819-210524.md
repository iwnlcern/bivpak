## SITREP (R-4.32 CONFIRMED at the bytes — and the grant's "no test byte" fence and the fix are JOINTLY UNSATISFIABLE, measured; plus the mechanism that made the whole chain blind to it) — **The defect is real and I re-derived it rather than taking it: `EntrySchemaSkipped` is declared at `src/core/support/error.hpp:29`, given its wire string at `error.cpp:45-46`, produced at `sessions.cpp:268` and `:279`, and mapped to exit 0 at `envelope.cpp:411` — and it occurs ZERO times in either `schemas/biv-json-envelope.v1.schema.json` or `schemas/biv-exit-map.v1.json`. Confirmed.** **BUT THE FIX CANNOT BE LANDED INSIDE THE FENCE AS WRITTEN, AND THIS IS ARITHMETIC, NOT PREFERENCE. The grant forbids "any test byte." TWO test surfaces MUST move or the head lands knowingly RED: (1) `harness/selftest/test_envelope.py:13-16` holds `CURRENT_LOCKED_SCHEMA_BLOBS`, pinning BOTH schema files by GIT BLOB ID, and `test_vendored_schema_artifacts_match_current_locked_bytes` computes the blob id of each live file and asserts equality — so ANY byte added to either schema turns `harness-selftest` RED unless those two constants are recomputed from what lands; (2) `tests/test_envelope.cpp` carries a hand-written `rows` vector of 26 expected exit-map kinds AND the EXACT-CARDINALITY assertion `count_occurrences(exit_text, "\"kind\": \"") == rows.size()` — so adding a 27th kind to the exit map against a 26-element list is RED by construction. Neither is avoidable by ordering, cleverness, or a smaller edit: the first is a hash of the very bytes we are told to change, the second is a count of the very rows we are told to add.** **AND HERE IS WHY THE ENTIRE GATE CHAIN WAS BLIND — the mechanism, which I think matters more than the defect: `tests/test_envelope.cpp`'s `rows` IS the instrument that should have caught R-4.32. It asserts every listed kind appears in the exit map, and its cardinality check asserts the file has EXACTLY as many kinds as the list. When A4 added the kind to the CODE and never to this LIST, the cardinality check did not fail — it CONFIRMED the stale count as correct. The completeness instrument was defined by the same omission it was supposed to detect, so it reported green at exactly the moment it should have reported the gap. `schemas/` being outside every fence is the true half of the diagnosis carried down; this is the other half, and it is the sharper one, because a fence can be widened while a self-defining instrument keeps passing forever.** **TWO THINGS I MEASURED SO NOBODY GUESSES: (a) THE STRUCTURE IS DERIVABLE, NOT INVENTED — `test_envelope.cpp:232` already carries `{"SessionsStaged", "advisory", 0}`, an advisory kind at exit 0, which is exactly what `EntrySchemaSkipped` is (`envelope.cpp:411` returns 0). So the exit-map row's class and exit follow existing parity plus `exit_for_error`, and the "do not invent schema structure" fence is satisfiable at the bytes rather than by judgment. (b) THE COUNT CELLS SHOULD NOT MOVE, AND I CHECKED WHY RATHER THAN HOPING — the gate parses `OverallResultsCases`, i.e. CASE counts, not assertion counts. Adding elements to `rows` inside an EXISTING `TEST_CASE` adds ASSERTIONS, never CASES, so the four `want` cells are expected UNCHANGED. But the schemas ARE consumed at runtime in four distinct ways, so a re-run IS owed by the grant's own rule, and any movement is a STOP.** **I HAVE TYPED NOTHING. The fence as written cannot produce a green head, so filling it at a keyboard would mean either editing forbidden files on my own authority or landing a knowingly-red commit, and both are worse than a routed cycle.** `4427bb3` is unchanged; branch LOCAL and UNPUBLISHED; the `165410` presentation stays SUPERSEDED-PENDING and nothing merges. Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-floor-slice-e-r432-fence-unsatisfiable-routed
PARENT_DISPATCH_ID: s4-floor-slice-e-r432-schema-gap-fix-granted
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-SLICE-E-R432-SCHEMA-GAP-BOUNDED-FIX-GRANTED-DOWN-I-OWN-MY-FOOTPRINT-ERROR-20260818-183517.md
RELATED_CONTEXT: .relays/s4/s4-floor-impl/SITREP-PLANNER-SLICE-E-R431-RECIPE-VERIFIED-AT-BYTES-M3-REVIEW-NEXT-20260818-150925.md
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: yes — the bounded fix cannot be landed green inside its stated fence; extending it by the two mechanically-necessary test surfaces is master's and m-3's, not mine. No product, schema or test byte moved at this seat; no commit; no token. The land order binds. The release hold is ABSOLUTE.
DESIGN_DOC_ID: m1-addendum-L-20260816
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m1-addendum-L-10c8e8e6-lock-20260817
SECOND_DESIGN_LOCK: m1-addendum-K-5da667fa-lock-20260816, m3-addendum-5-b8686c75-lock-20260816, m3-addendum-4-9049de44-lock-20260816
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812, m3-addendum-3-eeb4dd01-lock-20260814
PLAN_LOCK_ID: s4-floor-slice-e-plan-20260812
FROM: s4-floor.planner
TO: s4.orchestrator-planner
CC: operator, s4-floor.implementer, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer, m-3.planner, m-3.implementer, m-1.planner
SUBJECT: SITREP — R-4.32 confirmed at the bytes, but the fix and the no-test-byte fence are JOINTLY UNSATISFIABLE: a harness selftest pins both schemas by git blob id and test_envelope.cpp asserts exact kind-cardinality against a hand-written 26-row list; also the mechanism that blinded the chain, plus two measurements (structure derivable by parity; the gate counts CASES so the cells should not move); nothing typed

## 1. R-4.32 — confirmed, re-derived

```text
declared   src/core/support/error.hpp:29        EntrySchemaSkipped
wire       src/core/support/error.cpp:45-46     return "EntrySchemaSkipped";
produced   src/core/open/sessions.cpp:268, :279
exit       src/core/report/envelope.cpp:411     -> 0 (advisory)
schemas    ZERO occurrences in schemas/biv-json-envelope.v1.schema.json
           ZERO occurrences in schemas/biv-exit-map.v1.json
```

## 2. The fence and the fix are jointly unsatisfiable — the two blocking surfaces

### 2.1 `harness/selftest/test_envelope.py` pins BOTH schemas by git blob id

```python
CURRENT_LOCKED_SCHEMA_BLOBS = {                                          # :13-16
    "schemas/biv-json-envelope.v1.schema.json": "4f842442eac5421ca9312c7944d911ea8a3dbf3d",
    "schemas/biv-exit-map.v1.json":             "7ac7de89c1a60016ed24e17e6205c4a9acb7a538",
}
def test_vendored_schema_artifacts_match_current_locked_bytes():        # :23-29
    actual = {path: _git_blob_id((REPO_ROOT / path).read_bytes()) for path in CURRENT_LOCKED_SCHEMA_BLOBS}
    assert actual == CURRENT_LOCKED_SCHEMA_BLOBS
```

**Any byte added to either schema turns `harness-selftest` RED** unless those two constants are recomputed
from what lands. **The pin is a hash of the exact bytes the grant orders changed.** No ordering avoids it.

### 2.2 `tests/test_envelope.cpp` asserts EXACT kind-cardinality against a hand-written list

```cpp
const std::vector<ExpectedRow> rows{ ... 26 entries ... };
...
CHECK(count_occurrences(exit_text, "\"kind\": \"") == rows.size());
```

**Adding a 27th kind to the exit map against a 26-element `rows` is RED by construction.** The row must
also be added to `rows`. **The check is a count of the very rows the grant orders added.**

### 2.3 Therefore

```text
land the schema change alone      -> harness-selftest RED and test_envelope.cpp RED — a knowingly-red head
land it with the test surfaces    -> two FORBIDDEN test bytes moved on my own authority
=> the fence as written cannot produce a green head. I typed nothing.
```

## 3. Why the whole chain was blind — the mechanism, and I think it is the sharper half

`tests/test_envelope.cpp`'s `rows` **IS the instrument that should have caught R-4.32.** It asserts every
listed kind appears in the exit map, and its cardinality check asserts the file holds EXACTLY as many kinds
as the list.

**When A4 added the kind to the CODE and never to this LIST, the cardinality check did not fail — it
CONFIRMED the stale count as correct.** The completeness instrument was defined by the same omission it
existed to detect, so it reported green precisely where it should have reported the gap.

`schemas/` sitting outside every fence is the true half carried down. **This is the other half, and it is
the more dangerous one: a fence can be widened, while a self-defining instrument keeps passing forever.**
Recommended for the registry alongside R-4.32, because the fence fix alone does not remove it.

## 4. Two measurements so nobody guesses

```text
(a) STRUCTURE IS DERIVABLE, NOT INVENTED
    tests/test_envelope.cpp:232 already carries {"SessionsStaged", "advisory", 0} — an advisory kind at
    exit 0, exactly what EntrySchemaSkipped is (envelope.cpp:411 -> 0). The exit-map row's class and exit
    follow EXISTING PARITY plus exit_for_error, so "do not invent schema structure" is satisfiable at the
    bytes rather than by judgment.
(b) THE COUNT CELLS SHOULD NOT MOVE — checked, not hoped
    the gate parses OverallResultsCases — CASE counts, not assertion counts. Adding elements to `rows`
    inside an EXISTING TEST_CASE adds ASSERTIONS, never CASES, so the four `want` cells are expected
    UNCHANGED. But schemas/ IS consumed at runtime in FOUR ways — CMakeLists.txt:221/:233, the two
    harness paths, and tests/test_envelope.cpp:201/:250 — so a RE-RUN IS OWED by the grant's own rule,
    and any movement is a STOP.
```

## 5. Options — master's and m-3's, not mine

```text
(i)  RECOMMENDED — extend the fence by EXACTLY these, and nothing else:
       harness/selftest/test_envelope.py   the TWO constants at :13-16, RECOMPUTED from what lands
       tests/test_envelope.cpp             ONE `rows` element, class/exit by parity + exit_for_error
     Both values are DERIVED, not authored — the same R-3.48 shape already used twice in this lane: the
     arm that changes a pinned artifact repairs its own pin, under the owning domain's byte review. The
     harness is m-3's as infrastructure; the schemas are m-3's error surface. One commit, one reviewer.
(ii) land the schema change alone and accept two RED instruments — REJECTED, and named only to reject it.
(iii) split the test half to another seat — it must ride the SAME commit or there is a red interval, and
     a red interval is the shape this org rejected for macOS and again for the fold ordering.
```

**Not requested:** any widening beyond those two surfaces; any `SessionsStaged` or other-kind touch; any
product byte; any count cell; any `.github` byte; any restructuring of either schema.

## 6. State

```text
typed      NOTHING — no schema, test, product or .github byte; no commit; no token
head       4427bb3 unchanged, LOCAL and UNPUBLISHED
gates      R-4.31 at m-3 (4427bb3); R-4.32 blocked here on the fence, not on capability
merge      the 165410 presentation stays SUPERSEDED-PENDING; nothing merges
```

Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product, schema, test, fixture, workflow, documentation, branch, Docker, push, PR, Actions, merge, publication, deployment, or release act at this seat — read-only measurement. Read this pass at `4427bb3`: `EntrySchemaSkipped` grepped across `src` (six sites: `error.hpp:29`, `error.cpp:45-46`, `sessions.cpp:268`/`:279`, `envelope.cpp:411`) and across `schemas` (zero in both files); every runtime consumer of `schemas/` enumerated (`CMakeLists.txt:221`/`:233`, `harness/bivharness/scenario.py:26`/`:182`/`:191`, `harness/selftest/test_envelope.py:13-16`/`:23-29`, `tests/test_envelope.cpp:201`/`:250`); `harness/selftest/test_envelope.py:1-40` read in full for the blob-id pin mechanism; `tests/test_envelope.cpp:195-262` read in full for the 26-row list, the per-row CHECKs, the exact-cardinality assertion and the `SessionsStaged` precedent; the Linux count gate re-read and confirmed to parse `OverallResultsCases`. I ran no container, no build and no test. This relay + its INDEX row ride ONE explicit-path docs-lane commit whose SHA lands after filing. No token issued.
RELAY_LINT: per D-3.4 (v2.9) — per-file WITH freshness (clock read immediately before filing, per D-5.10 instance 4), exit status checked un-piped and READ before committing; `--relay-root` run against this file and its output READ IN FULL. Standing reds disclosed: the cross-repo DESIGN-lineage class, whose coverage for the listed identity is the eleven-element W-2 join re-run at `145233`; INDEX cell-count (R-4.27) at 132, 222, 324, 362, 384, 388, 408, 435; INDEX time inversions at 222 and 393. `.relays/s4/INDEX.md` tail re-read before appending; `--index`; add and commit path-scoped; my appended row is 10-cell clean.
FINAL_GIT_STATUS_SHORT: literal path-scoped `git status --short` for this seat's two writes, captured at staging (the implementation worktree `s4-floor-slice-e-stage1a` reports EMPTY `git status --short` at `4427bb3`; the shared main checkout carries sibling-authored untracked state, excluded and unclaimed):
  M  .relays/s4/INDEX.md
  A  .relays/s4/s4-floor-impl/SITREP-PLANNER-SLICE-E-R432-CONFIRMED-BUT-FENCE-UNSATISFIABLE-TWO-TEST-SURFACES-20260819-210524.md

CARRY LIST (D-8.5):
- `.relays/s4/s4-floor-impl/SITREP-PLANNER-SLICE-E-R432-CONFIRMED-BUT-FENCE-UNSATISFIABLE-TWO-TEST-SURFACES-20260819-210524.md` → `s4.orchestrator-planner`
- R-4.32 CONFIRMED and re-derived rather than taken: EntrySchemaSkipped is declared at error.hpp:29, given its wire string at error.cpp:45-46, produced at sessions.cpp:268 and :279, and mapped to exit 0 at envelope.cpp:411, while occurring ZERO times in either schema file
- THE FIX AND THE NO-TEST-BYTE FENCE ARE JOINTLY UNSATISFIABLE, and this is arithmetic not preference. TWO test surfaces must move or the head lands knowingly RED: harness/selftest/test_envelope.py:13-16 holds CURRENT_LOCKED_SCHEMA_BLOBS pinning BOTH schema files by GIT BLOB ID, with test_vendored_schema_artifacts_match_current_locked_bytes computing each live file's blob id and asserting equality, so any schema byte turns harness-selftest RED unless the two constants are recomputed from what lands; and tests/test_envelope.cpp carries a hand-written 26-element rows vector plus the EXACT-CARDINALITY assertion count_occurrences(exit_text, kind) == rows.size(), so adding a 27th kind against a 26-element list is RED by construction. Neither is avoidable by ordering or a smaller edit: the first is a hash of the very bytes ordered changed, the second a count of the very rows ordered added
- WHY THE WHOLE CHAIN WAS BLIND, the mechanism and arguably the sharper half: tests/test_envelope.cpp's rows IS the instrument that should have caught R-4.32, asserting every listed kind appears in the exit map and that the file holds EXACTLY as many kinds as the list; when A4 added the kind to the CODE and never to this LIST, the cardinality check did not fail but CONFIRMED the stale count as correct, so the completeness instrument was defined by the same omission it existed to detect and reported green precisely where it should have reported the gap. schemas/ being outside every fence is the true half carried down; this is the other half and the more dangerous one, because a fence can be widened while a self-defining instrument keeps passing forever — recommended for the registry alongside R-4.32 since the fence fix alone does not remove it
- TWO MEASUREMENTS SO NOBODY GUESSES: the STRUCTURE IS DERIVABLE not invented, since tests/test_envelope.cpp:232 already carries SessionsStaged as an advisory kind at exit 0 which is exactly what EntrySchemaSkipped is per envelope.cpp:411, so the row's class and exit follow existing parity plus exit_for_error and the do-not-invent fence is satisfiable at the bytes; and THE COUNT CELLS SHOULD NOT MOVE, checked rather than hoped, because the gate parses OverallResultsCases meaning CASE counts, and adding elements to rows inside an EXISTING TEST_CASE adds assertions and never cases — though schemas/ IS consumed at runtime in FOUR ways (CMakeLists.txt:221 and :233, two harness paths, tests/test_envelope.cpp:201 and :250) so a RE-RUN IS OWED by the grant's own rule and any movement is a STOP
- OPTIONS, master's and m-3's: (i) RECOMMENDED extend the fence by EXACTLY the two constants at harness/selftest/test_envelope.py:13-16 recomputed from what lands and ONE rows element in tests/test_envelope.cpp with class and exit by parity plus exit_for_error, both values DERIVED not authored, the same R-3.48 shape already used twice in this lane where the arm that changes a pinned artifact repairs its own pin under the owning domain's byte review, one commit and one reviewer; (ii) land the schema change alone and accept two RED instruments, REJECTED and named only to reject it; (iii) split the test half to another seat, which must ride the SAME commit or create a red interval, the shape this org rejected for macOS and again for the fold ordering. NOT REQUESTED: any widening beyond those two surfaces, any SessionsStaged or other-kind touch, any product byte, any count cell, any .github byte, any restructuring of either schema
- TYPED NOTHING: no schema, test, product or .github byte, no commit, no token — the fence as written cannot produce a green head, so filling it at a keyboard would mean either editing forbidden files on my own authority or landing a knowingly-red commit, and both are worse than a routed cycle. 4427bb3 unchanged, LOCAL and UNPUBLISHED; R-4.31 sits at m-3; R-4.32 blocked on the fence and not on capability; the 165410 presentation stays SUPERSEDED-PENDING and nothing merges; merge is not push is not release; release hold ABSOLUTE
