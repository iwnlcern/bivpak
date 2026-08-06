## REVIEW-FOLD SCOPE — B1 F1–F9 whole pass resolves all-IN under Amendment A4; O1–O5/O7/O8 accepted, O6 deferred; no product edit preceded this artifact

ROLE: Implementer
PHASE: REVIEW-FOLD
AUTHORITY: fold-in-only
DISPATCH_ID: s4-floor-impl-2-b1-review-fold
PARENT_DISPATCH_ID: s4-floor-impl-2
RUN_ID: s4
TASK_ID: B1
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — A4 closes the only prior OUT row; merge remains operator-owned and the release hold is ABSOLUTE
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/IMPL-PLANNER-RESUME-B1-FOLD-WHOLE-20260806-025746.md
FROM: s4-floor.implementer
TO: s4-floor.planner
CC: s4.orchestrator-planner, operator
SUBJECT: FOLD_SCOPE ALL-IN — exact B1 F1-F9 product/test/fixture/evidence/PR surfaces declared before the first fold edit

FOLD_SCOPE:
- src/adapters/codex/codex.cpp -> in
- src/adapters/codex/codex.hpp -> in
- src/cli/main.cpp -> in
- src/core/pack/pack.hpp -> in
- src/core/pack/pack.cpp -> in
- tests/test_adapter_codex_collect.cpp -> in
- tests/test_cli.cpp -> in
- tests/test_envelope.cpp -> in
- tests/fixtures/codex_store/tail_matrix/** -> in
- docs/sprints/2026-08-04-s4-step4/results/receipts/B1-A3-C1-five-owner-receipts.md -> in
- PR #15 body -> in
- .relays/s4/s4-floor-impl/** -> in
- .relays/s4/INDEX.md -> in
FOLD_SCOPE_RESULT: all-in

## Finding map

- F1: `codex.cpp`, collect test, CLI test, and a terminal-parent/live-child
  fixture pair.
- F2: `main.cpp` sanitizer plus a real control-byte filename CLI witness.
- F3: `test_cli.cpp` JSON `agent_sessions` positive witness.
- F4: collect the zero-byte fixture and pin an empty production report while
  preserving direct predicate coverage.
- F5/A4: promote `has_terminal_tail_record` through `codex.hpp/cpp`, delete
  the test-only namespace/redeclaration, and use one production predicate.
- F6: durable receipt file and PR-body evidence.
- F7: consumer-review markers in `main.cpp`.
- F8: pinned TornTail kind and path/artifact shape in `test_envelope.cpp`.
- F9: three renderer shapes in `test_cli.cpp` plus the generic empty-path
  guard in `main.cpp`.

Accepted optionals: O1 padded-string copy removal; O2 direct includes; O3
lone-LF boundary fixture; O4 is subsumed by A4; O5 shared warning-kind
constants; O7 parsed record without `type`; O8 PR-body checkpoint note.
O6 is deferred because the locked generic renderer contract is kind+path; adding
optional artifact/bytes there would alter that contract rather than merely close
a finding.

No `CMakeLists.txt`, manifest, scan, harness behavior, schema, sibling relay
tree, merge, release, or unrelated path is in this fold.

ACTIONS_GIT_REF: no B1 product/test/fixture edit, PR-body write, push, merge, release, or Slice-A restack preceded this artifact; this scope relay and its append-only INDEX row are the only pre-fold docs-lane writes
FINAL_GIT_STATUS_SHORT: B1 worktree clean at d5642ed9ea19cd6256276681b63199adff21aea4 before filing; docs lane limited to this scope relay and INDEX row before explicit-path commit
