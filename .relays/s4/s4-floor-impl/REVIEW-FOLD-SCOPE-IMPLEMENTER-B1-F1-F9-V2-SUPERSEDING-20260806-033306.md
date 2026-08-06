## REVIEW-FOLD SCOPE v2 — superseding complete B1 F1-F9 scope includes the per-head C1 anchor literal; v1's omission remains disclosed; no replay

ROLE: Implementer
PHASE: REVIEW-FOLD
AUTHORITY: fold-in-only
DISPATCH_ID: s4-floor-impl-2-b1-review-fold
PARENT_DISPATCH_ID: s4-floor-impl-2
RUN_ID: s4
TASK_ID: B1
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — the pair Planner disposed the artifact scar under the standing A3 per-head grant; merge remains operator-owned and the release hold is ABSOLUTE
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/IMPL-PLANNER-C1-SCOPE-SCAR-DISPOSED-SUPERSEDE-AND-PROCEED-20260806-032028.md
FROM: s4-floor.implementer
TO: s4-floor.planner
CC: s4.orchestrator-planner, operator
SUBJECT: FOLD_SCOPE v2 ALL-IN — supersedes v1, adds the already-authorized one-literal C1 recapture, preserves the scar, and resumes without replay

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
- harness/bivharness/e3.py -> in
- docs/sprints/2026-08-04-s4-step4/results/receipts/B1-A3-C1-five-owner-receipts.md -> in
- PR #15 body -> in
- .relays/s4/s4-floor-impl/** -> in
- .relays/s4/INDEX.md -> in
FOLD_SCOPE_RESULT: all-in

This artifact supersedes
`REVIEW-FOLD-SCOPE-IMPLEMENTER-B1-F1-F9-20260806-030052.md` without deleting or
rewriting it. V1 incorrectly claimed completeness while omitting
`harness/bivharness/e3.py`; the omission was self-caught and routed before any edit to
that path. The already-held product, test, and fixture edits were each covered by v1,
so the Planner's disposition requires no restore/replay. The scar, blocker, and
supersession remain append-only evidence and will be named in the fold report.

The newly listed harness path is IN only for the standing A3 mechanical operation:
replace exactly the `codex_adapter_file` literal with the SHA-256 of the final folded
`src/adapters/codex/codex.cpp` bytes. No harness behavior, other anchor, schema lock,
exit-map lock, or other `e3.py` content is admitted. The recapture occurs last after
the folded source stabilizes and carries A3's unchanged four checks plus five-owner
mutation receipts.

The v1 F1-F9 map and optional disposition remain unchanged: O1-O5/O7/O8 accepted,
O6 deferred. No `CMakeLists.txt`, manifest, scan contract, schema, merge, release, or
unrelated path is admitted.

ACTIONS_GIT_REF: B1 committed head remains d5642ed9ea19cd6256276681b63199adff21aea4 with held uncommitted edits only in v1-declared paths; harness/bivharness/e3.py has no diff before this v2 artifact; this relay and append-only INDEX row are the only implementer writes made after the blocker
FINAL_GIT_STATUS_SHORT: B1 carries the held declared fold changes; docs lane was clean at 46a7eaf before this v2 relay and INDEX append

CARRY LIST:
- `.relays/s4/s4-floor-impl/REVIEW-FOLD-SCOPE-IMPLEMENTER-B1-F1-F9-V2-SUPERSEDING-20260806-033306.md` → `s4-floor.planner`
