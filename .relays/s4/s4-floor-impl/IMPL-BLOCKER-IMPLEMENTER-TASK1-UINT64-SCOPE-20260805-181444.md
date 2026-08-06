## IMPL BLOCKER — Task 1 review exposes a uint64 JSON boundary defect whose correct fix is outside the dispatched scope

ROLE: Implementer
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: s4-floor-impl-2-task1-uint64-blocker
PARENT_DISPATCH_ID: s4-floor-impl-2
RUN_ID: s4
TASK_ID: 1
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — the required JSON-writer paths are OUT of the locked SCOPE_DIFF; orchestrator must expand scope or direct a design-compatible in-scope alternative before any fix
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-plan/IMPL-PLANNER-DISPATCH-2-20260805-174242.md
FROM: s4-floor.implementer
TO: s4-floor.planner
CC: s4.orchestrator-planner, operator
SUBJECT: BLOCKED at Task 1 review — Warning::bytes narrows uint64_t through int64_t; correct writer fix requires three OUT paths

## Current implementation evidence

- Isolated worktree: `/Users/jack/.config/superpowers/worktrees/bivpak/s4-floor-b1-codex-liveness`.
- Branch: `s4-floor/b1-codex-liveness`.
- Task 1 commit: `d6133de10a30208f5dc462c3368264b00d64f49c` (`feat(pack): extend Warning with optional artifact/bytes`).
- TDD/product evidence: focused carrier and compatibility tests pass; full hermetic `biv_tests` reports 224 cases, 222 passed, 2 WSL-only skipped, 5,638/5,638 assertions passed.
- Implementation worktree is clean at that commit; nothing is pushed and no PR is open.

The task implementation correctly adds `std::optional<std::string> artifact` and `std::optional<std::uint64_t> bytes`, omits unset JSON keys, updates the schema, and covers ordinary populated/unset cases. The independent task review nevertheless returns MUST-REVISE on a load-bearing boundary defect.

## Finding

`src/core/report/envelope.cpp` currently serializes the new `std::uint64_t` value by `static_cast<int64_t>` into `biv::json::Writer::value_int(std::int64_t)`. A valid value greater than `INT64_MAX` therefore cannot retain its non-negative numeric value, while the locked schema requires a non-negative integer. The existing test value `42` does not exercise the boundary.

The available writer API has no unsigned-number emitter. Its JSON framing methods are private, so there is no clean in-scope call from `envelope.cpp` that can emit `UINT64_MAX` as an unquoted JSON integer. Narrowing the model field to signed width would contradict the locked plan's exact `std::uint64_t` interface and is not an Implementer-local option.

## Mechanical deviation

SCOPE_DIFF:
- src/core/pack/pack.hpp -> in
- src/core/report/envelope.cpp -> in
- schemas/biv-json-envelope.v1.schema.json -> in
- tests/test_envelope.cpp -> in
- tests/test_pack.cpp -> in
- src/core/json/writer.hpp -> OUT
- src/core/json/writer.cpp -> OUT
- tests/test_json_writer.cpp -> OUT
SCOPE_DIFF_RESULT: deviation-present

## Requested disposition

Recommended: authorize the three OUT paths for the narrow addition of an unsigned JSON integer emitter, its writer unit boundary test, and the Task 1 `UINT64_MAX` envelope/schema regression. This preserves the locked `uint64_t` carrier and JSON numeric contract without ad hoc envelope serialization.

If scope expansion is declined, route an amended design/plan decision that defines a different representable contract. Do not ask the Implementer to cast, quote, clamp, or silently restrict the declared unsigned domain.

Task 2 and all later tasks are held. The current Task 1 commit is retained only on the isolated unpushed branch for adjudication; no out-of-scope edit has occurred.

ACTIONS_GIT_REF: implementation branch `s4-floor/b1-codex-liveness@d6133de10a30208f5dc462c3368264b00d64f49c`; this blocker relay and its append-only INDEX row are the only main/docs-lane writes, with commit named in repository history after filing; no push, PR, merge, seal, or release.

FINAL_GIT_STATUS_SHORT: implementation worktree clean at `d6133de10a30208f5dc462c3368264b00d64f49c`; docs-lane precommit set is `.relays/s4/INDEX.md` plus this new relay.

## Next action

Planner: route the deviation to `s4.orchestrator-planner`. Resume Task 1 only after an exact scope disposition; Tasks 2-11 remain held.
