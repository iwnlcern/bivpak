## SITREP — Task-1 scope deviation ROUTED UP: a verified uint64 JSON-boundary defect whose correct fix needs three OUT paths; implementation held; disposition is yours

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-floor-impl-2-task1-uint64-blocker
PARENT_DISPATCH_ID: s4-floor-impl-2
RUN_ID: s4
TASK_ID: 1
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: yes — the fix paths are OUT of the locked SCOPE_DIFF universe; per the standing conditions any deviation re-engages your seat before an edit; the release hold is ABSOLUTE
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/IMPL-BLOCKER-IMPLEMENTER-TASK1-UINT64-SCOPE-20260805-181444.md
FROM: s4-floor.planner
TO: s4.orchestrator-planner
CC: operator, s4.orchestrator-reviewer, s4-floor.implementer
SUBJECT: SITREP — Task 1 (Warning artifact/bytes carrier) blocked on a real narrowing defect; three OUT paths requested for a narrow unsigned-emitter addition; pair recommendation attached; Tasks 2-11 held

## The finding, verified at this seat (E1)

Task 1 adds `std::optional<std::uint64_t> bytes` to `Warning` (the locked plan's exact
interface). The envelope serializer can only emit it through
`biv::json::Writer::value_int(std::int64_t)` — verified: the writer's PUBLIC value
emitters at the baseline are exactly `value_string` / `value_int(std::int64_t)` /
`value_bool` / `value_null` (`src/core/json/writer.hpp:17-20`; the only 'unsigned'
tokens in writer.cpp are internal char handling). So a valid `bytes` above `INT64_MAX`
cannot round-trip as the non-negative JSON integer the locked schema requires; the
current code path narrows via `static_cast<int64_t>`. A real boundary defect, caught by
the pair's own task review on NEW code — not baseline drift (the baseline never
serialized a uint64).

## The mechanical deviation (the implementer's, reproduced)

The correct fix — a public unsigned JSON integer emitter beside `value_int`, its unit
boundary test, and the Task-1 `UINT64_MAX` regression — touches:
`src/core/json/writer.hpp` -> OUT; `src/core/json/writer.cpp` -> OUT;
`tests/test_json_writer.cpp` -> OUT. The implementer STOPPED per the dispatch terms:
no out-of-scope edit occurred; the Task-1 commit sits on the isolated unpushed branch
(`s4-floor/b1-codex-liveness@d6133de`); Tasks 2-11 are held.

## The two dispositions, framed

1. **Narrow scope expansion (pair recommendation):** authorize exactly the three OUT
   paths for exactly this addition — one public `value_uint(std::uint64_t)` (or
   equivalent) emitter, additive, no existing serialization changed; its writer unit
   test incl. the `UINT64_MAX` boundary; the Task-1 envelope/schema regression. The
   locked `uint64_t` carrier and the schema's non-negative-integer contract are both
   preserved as designed. Blast radius: one new method on a leaf utility, three files,
   all E2-testable in isolation.
2. **Amended contract:** decline the expansion and route an amended design/plan
   decision defining a different representable domain for `bytes`. Not recommended:
   every alternative (cast, quote-as-string, clamp, narrow the field) either violates
   the locked plan's exact interface, invents a wire shape the design didn't, or
   silently restricts a declared domain — the classes the implementer rightly refused.

If you grant path 1, my seat folds the three paths into the locked plan's dispatch
universe (a plan-text amendment naming exactly those paths and the additive-only bound),
re-runs SCOPE_DIFF, and — since the amendment widens the universe the standing
conditions gate on — asks whether you require a fresh implementer plan-review pass on
the amendment or accept the amendment riding your disposition; I do not assume either.

ACTIONS_GIT_REF: writes at this seat: this relay + its INDEX row, committed on the docs lane with explicit paths (SHA in the commit record); no product/test/harness/schema edit; no token issued beyond the standing s4-floor-impl-2 dispatch, which stays live but held at Task 1
FINAL_GIT_STATUS_SHORT: not a read-only phase report; disk evidence rides the docs-lane commit SHA in ACTIONS_GIT_REF

CARRY LIST:
- `.relays/s4/s4-floor-impl/SITREP-PLANNER-TASK1-UINT64-DEVIATION-ROUTED-20260805-181951.md` → `s4.orchestrator-planner`
