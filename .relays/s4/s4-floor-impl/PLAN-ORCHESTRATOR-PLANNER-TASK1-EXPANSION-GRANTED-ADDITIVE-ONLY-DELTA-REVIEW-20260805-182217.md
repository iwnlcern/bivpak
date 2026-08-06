## DISPOSITION — Task-1 scope expansion GRANTED, path 1: exactly the three named paths, ADDITIVE-ONLY, for exactly the unsigned-emitter addition. A delta plan-review approve on the amendment is required; a fresh dispatch token is NOT. Tasks 2-11 unblock with Task 1.

ROLE: Orchestrator Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-floor-impl-2-task1-uint64-blocker
PARENT_DISPATCH_ID: s4-floor-pair-plan
RUN_ID: s4
TASK_ID: 1
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no — a within-gate scope disposition at the seat the standing conditions name for deviations; the Step-4 gate's OUT list (.github/, host probing, ENOTDIR widening, beyond-gate scope) is untouched; merge is the operator's; the release hold is ABSOLUTE
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/SITREP-PLANNER-TASK1-UINT64-DEVIATION-ROUTED-20260805-181951.md
FROM: s4.orchestrator-planner
TO: s4-floor.planner
CC: operator, s4.orchestrator-reviewer, s4-floor.implementer
SUBJECT: PLAN — three OUT paths admitted for one additive emitter; the exact bound; the amendment process ruled

Verified at this seat before granting (E1 at `8981bfd`): the writer's public value
emitters are exactly `value_string` / `value_int(std::int64_t)` / `value_bool` /
`value_null` (`src/core/json/writer.hpp:17-20`); the only `unsigned` tokens in
`src/core/json/writer.cpp` are internal char handling (`:12`, `:138`); `value_uint` has
zero hits under `src/`. The defect is real: a locked-plan `std::optional<std::uint64_t>
bytes` cannot round-trip above `INT64_MAX` through a narrowing cast, and every
alternative the pair refused (cast, clamp, string-quote, domain-narrow) either breaks
the locked interface or invents wire shape. The implementer's stop-without-editing is
the standing conditions working; both seats' conduct is correct again.

**THE GRANT — path 1, bounded exactly:**

1. **Paths admitted to the dispatched universe, this addition only:**
   `src/core/json/writer.hpp`, `src/core/json/writer.cpp`,
   `tests/test_json_writer.cpp`.
2. **The additive-only bound:** ONE new public unsigned JSON integer emitter
   (`value_uint(std::uint64_t)` or equivalent) beside the existing emitters; its unit
   boundary test including `UINT64_MAX`; the Task-1 envelope/schema regression. NO
   existing emitter, signature, or serialization behavior changes. A change to any
   existing writer surface — or any fourth file — is a NEW deviation and comes back
   here before an edit.
3. **Shared-infra note (recorded in RECONCILE):** the JSON writer is repo-shared leaf
   infrastructure; this addition rides the floor's current act window under the
   single-owner rule, and the matrix pair rebases over it. Additive shape keeps that
   cheap.

**The amendment process, ruled (your routed question):** fold the three paths + the
additive-only bound into the plan text as a named amendment, re-run the mechanical
SCOPE_DIFF (must return all-in over the widened universe), and obtain a **delta
plan-review approve from your Implementer on the amendment** — bare verdict line, scoped
to the amendment's text; the thirteen-revision full-pass shape is not owed for a
three-path additive widening, and the reviewer who framed the fix is the right gate on
its wording. A fresh dispatch token is **NOT required**: the standing `s4-floor-impl-2`
dispatch remains live — this disposition plus the delta-approved amendment IS the
widened universe it gates on. On the delta approve: Task 1 resumes (the held
`s4-floor/b1-codex-liveness@d6133de` commit continues), Tasks 2-11 unblock.

ACTIONS_GIT_REF: no product edits at this seat; this relay + its INDEX row + a RECONCILE note, committed on the docs lane
FINAL_GIT_STATUS_SHORT: not claimed here — see the lane commit carrying this relay for the path-scoped set
