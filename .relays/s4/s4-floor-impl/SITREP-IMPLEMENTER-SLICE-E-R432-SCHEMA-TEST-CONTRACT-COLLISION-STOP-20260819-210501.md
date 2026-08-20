## SITREP — R-4.32 schemas are test-consumed and the schema-only fence deterministically breaks two selected contract checks

ROLE: Implementer
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-floor-slice-e-r432-schema-test-contract-collision-stop
PARENT_DISPATCH_ID: s4-floor-slice-e-r432-schema-gap-fix-granted
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-SLICE-E-R432-SCHEMA-GAP-BOUNDED-FIX-GRANTED-DOWN-I-OWN-MY-FOOTPRINT-ERROR-20260818-183517.md
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — the current grant forbids the test bytes that must move for either selected platform suite to remain green after the required schema additions; the floor must route this contradiction upward before plan approval or implementation dispatch
DESIGN_DOC_ID: m3-addendum-4-20260815
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m3-addendum-4-9049de44-lock-20260816
PLAN_LOCK_ID: s4-floor-slice-e-plan-20260812
FROM: s4-floor.implementer
TO: s4-floor.planner
CC: s4.orchestrator-planner, operator, s4.orchestrator-reviewer, master.orchestrator-planner, m-3.planner, m-3.implementer, m-1.planner
SUBJECT: STOP — both schemas are consumed by both platform suites, but the schema-only R-4.32 fence guarantees failures in the exact-row and locked-blob tests while forbidding both necessary test updates

## Determination

The R-4.32 defect and the A4 contract are confirmed at exact candidate
`4427bb30e23309af92432a06dc66d89463480d0c`. The locked A4 document at pdc object `40bd88a6`
hashes `9049de443e8ecc91ff72c291e85fd1c0c3c8876ac6deed28265fb10154600746` and specifies the
additive `EntrySchemaSkipped` wire kind at exit 0. Both target schema files currently contain zero occurrences
of that string.

The required runtime-consumption measurement returns **consumed** for both files and both platform suites:

- `biv_tests` opens `schemas/biv-exit-map.v1.json` and `schemas/biv-json-envelope.v1.schema.json` in the
  `schema artifacts reserve envelope and exit-map contracts` case.
- `harness-selftest` reads and hashes both repository schema files in
  `test_vendored_schema_artifacts_match_current_locked_bytes`.
- the macOS selected row explicitly includes both `biv_tests` and `harness-selftest`;
- the Linux workflow runs the full CTest suite, which includes both rows.

Both platform suites are therefore owed after implementation. No no-rerun ground exists.

## Scope collision at the candidate bytes

The currently authorized two-schema-only edit cannot satisfy that owed validation:

1. `tests/test_envelope.cpp` has 26 expected exit-map rows and asserts that the literal number of schema
   `"kind"` rows equals that vector size. The current exit map also has exactly 26 rows. Adding the required
   `EntrySchemaSkipped` row makes the schema count 27 while the expected vector remains 26, so `biv_tests`
   fails unless this test file gains the corresponding advisory row.
2. `harness/selftest/test_envelope.py` pins the Git blob IDs of both schema files at candidate head:
   `4f842442eac5421ca9312c7944d911ea8a3dbf3d` for the envelope schema and
   `7ac7de89c1a60016ed24e17e6205c4a9acb7a538` for the exit map. The required addition changes both blobs,
   so `harness-selftest` fails unless both expected IDs are refreshed.

These are existing test cases, so the necessary expectation updates should leave Catch2 case counts and skip
counts unchanged. They are nevertheless test-byte changes, and the incoming grant explicitly forbids **any test
byte**. The same grant requires both suites green with unchanged count cells and says any count movement or
undetermined need is a STOP routed upward. The contradiction is structural and exists before implementation;
running the known-red post-edit suites is not needed to establish it.

## Required disposition

No floor plan can honestly reach PLAN-REVIEW under the current fence. Before a plan or token issues, the floor
Planner must route upward for an amended bounded grant that either:

- admits the two exact existing test-contract updates needed to track the authorized schema bytes, while keeping
  all test-case and workflow count cells unchanged; or
- supplies another explicit owner-ratified disposition that makes both selected suites pass without violating the
  A4 schema contract.

The first shape is the smallest observed repair: add the new advisory row to the existing C++ expected-row vector
and refresh the two existing schema blob IDs after the schema bytes are final. This relay does not authorize that
widening and does not prescribe the final plan.

## Seat boundary

No schema, product, test, fixture, workflow, count, branch or implementation byte changed. No test suite was run,
because no implementation token exists and the contradiction is established directly by the selected test code.
The implementation worktree remains clean at `4427bb3`. No GitHub Actions, remote CI, push, PR, merge,
publication, deployment or release occurred. The old merge-gate presentation remains superseded-pending and the
release hold remains absolute.

ACTIONS_GIT_REF: E2 read-only verification at clean implementation head 4427bb30e23309af92432a06dc66d89463480d0c and docs head 6f7f45962ea6180b3dcad295453d7f3819871906; incoming relay sha256 2bb5c2ec1eaf78b9a27a67c507531ad7bca5e29e1af865f22e8a64027a850403; target test blobs 1bb9b83f76f14126b9518e97b068f39e57cf531b and de408f12922cf6ffc74833908b45081e4d1650bc; workflow blob f52c65fa980f30be4f78c0522953e41b26100648; this SITREP and one live-EOF INDEX row are the only intended coordination writes
RELAY_LINT: incoming exact-file no-freshness PASS and outgoing exact-file freshness PASS; live INDEX lint reports only inherited malformed-cell rows 132, 222, 324, 362, 384, 388, 408 and 435 plus inherited time inversions 222 and 393; this relay's 10-cell row was appended at live EOF and the later Planner row now occupies EOF without rewriting either row
FINAL_GIT_STATUS_SHORT: path-scoped pre-commit status is `?? .relays/s4/s4-floor-impl/SITREP-IMPLEMENTER-SLICE-E-R432-SCHEMA-TEST-CONTRACT-COLLISION-STOP-20260819-210501.md`; all other untracked paths are pre-existing foreign artifacts, preserved and excluded

CARRY LIST:
- `.relays/s4/s4-floor-impl/SITREP-IMPLEMENTER-SLICE-E-R432-SCHEMA-TEST-CONTRACT-COLLISION-STOP-20260819-210501.md` -> `s4-floor.planner`
- R-4.32 defect and A4 lock -> independently confirmed at exact candidate `4427bb3`
- schema consumption -> both target files are read by `biv_tests` and `harness-selftest`, both selected on macOS and Linux
- current schema-only fence -> deterministically breaks the 26-row equality assertion and both locked schema blob IDs
- necessary test updates -> currently forbidden, so route upward for amended bounded authority before plan-review or token
- implementation head -> clean and unchanged; no suite, Actions, publication, merge or release action
