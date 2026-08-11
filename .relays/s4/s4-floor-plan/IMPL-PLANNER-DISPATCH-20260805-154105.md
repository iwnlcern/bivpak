## IMPL DISPATCH — the floor-fold plan is approved and the mechanical scope gate returns all-in; implementation authority issues below under the orchestrator's delegated conditions

ROLE: Planner
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: s4-floor-impl
PARENT_DISPATCH_ID: s4-floor-plan-review-rev2
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new gate — this token authorizes implementation of the locked plan only; merge remains the operator's alone; the release hold is ABSOLUTE
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-plan/PLAN-REVIEW-IMPLEMENTER-REV2-20260805-153838.md
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: s4.orchestrator-planner, operator
SUBJECT: DISPATCH — implement s4-floor-fold-plan-20260805 (plan SHA 5e88a538…, approved s4-floor-plan-review-rev2) under Superpowers executing-plans; five stacked heads B1→A→C→B2→E

The locked plan: `docs/sprints/2026-08-04-s4-step4/plans/2026-08-05-s4-floor-fold-plan.md`
— disk SHA-256 re-verified at issuance: `5e88a538b26d8318d3a6260dc4f988e644bcf3ed153a7c0a970cbd25918cfecb`,
identical to the approving review's pinned SHA.

Delegated-condition record (the orchestrator's standing conditions, `145825`, all met):
the Implementer plan review is APPROVE on its own bare line
(`s4-floor-plan-review-rev2`); this relay's parent chain is that review → my PLAN
(`s4-floor-plan`) → the approving DESIGN-REVIEW lineage; the mechanical scope gate is
below and returns all-in; no hard trigger fired beyond what this production-risk
ceremony already carries (no new authz/secret/migration-of-canonical-data/cross-repo
surface entered the plan after the reviews; the A5.10 session-migration mechanism is
sealed-design content, not a data migration; host stores are written only via the
existing consent-bound install path).

SCOPE_DIFF:
- src/adapters/version_floor.hpp -> in
- src/adapters/version_floor.cpp -> in
- src/adapters/migration.hpp -> in
- src/adapters/migration.cpp -> in
- src/adapters/adapter.hpp -> in
- src/adapters/codex/codex.cpp -> in
- src/adapters/codex/install.cpp -> in
- src/adapters/claude_code/claude_code.cpp -> in
- src/adapters/claude_code/install.cpp -> in
- src/core/open/sessions.hpp -> in
- src/core/open/sessions.cpp -> in
- src/core/open/render.hpp -> in
- src/core/open/render.cpp -> in
- src/core/pack/pack.hpp -> in
- src/core/pack/pack.cpp -> in
- src/core/report/envelope.cpp -> in
- src/core/support/error.hpp -> in
- src/core/support/error.cpp -> in
- src/cli/main.cpp -> in
- schemas/biv-json-envelope.v1.schema.json -> in
- schemas/biv-exit-map.v1.json -> in
- CMakeLists.txt -> in
- tests/test_adapter_codex_collect.cpp -> in
- tests/test_adapter_claude_collect.cpp -> in
- tests/test_adapter_codex_install.cpp -> in
- tests/test_adapter_claude_install.cpp -> in
- tests/test_pack.cpp -> in
- tests/test_manifest.cpp -> in
- tests/test_open.cpp -> in
- tests/test_sessions.cpp -> in
- tests/test_render.cpp -> in
- tests/test_envelope.cpp -> in
- tests/test_cli.cpp -> in
- tests/fixtures/** -> in
- harness/scenarios-e3/e3-dual-resume.json -> in
- harness/bivharness/e3.py -> in
- harness/selftest/test_e3_asserts.py -> in
- harness/scenarios/open-consent-no.json -> in
- harness/scenarios/open-deny-default.json -> in
- harness/ci/check_version_floor_mirror.py -> in
- docs/sprints/2026-08-04-s4-step4/results/receipts/** -> in
- .relays/s4/s4-floor-impl/** -> in
- .relays/s4/INDEX.md -> in
SCOPE_DIFF_RESULT: all-in

Every row above is a path the locked plan names; the universe is the plan's own
enumerated dispatch-scope set, so the diff is identity by construction — recorded
mechanically, not judged. Anything OUTSIDE these rows (slice D, `src/core/manifest/*`,
`.github/`, host stores, sibling relay trees, the pdc RUNCARD, any new test translation
unit) stays OUT: touching one is a deviation that re-engages `s4.orchestrator-planner`
BEFORE the edit.

Execution terms (restating the locked plan, adding nothing):
- Superpowers `executing-plans` governs; the five stacked heads and their base/target/
  restack rules are the plan's §Five-head topology; TDD RED-first per task; the
  one-commit laws for slices A and C; receipts executed at their GREEN-abling slice with
  the discriminating-input-class precheck note; evidence to
  `docs/sprints/2026-08-04-s4-step4/results/receipts/**`; implementation reports to
  `.relays/s4/s4-floor-impl/**` + EOF INDEX rows, docs-lane commits explicit-path.
- IMPL exits at branch + PR + report per head. No merge: the operator's token alone
  authorizes any merge, per PR, in stack order.
- Blockers, seam questions, and any scope pressure route to me inline or by relay;
  anything above the pair goes to `s4.orchestrator-planner` via my seat.

DISPATCH IMPL

ACTIONS_GIT_REF: writes at this seat: this relay + its INDEX row, committed on the docs lane with explicit paths (SHA in the commit record); no product/test/harness/schema edit; no push
FINAL_GIT_STATUS_SHORT: not a read-only phase report; disk evidence rides the docs-lane commit SHA in ACTIONS_GIT_REF

CARRY LIST:
- `.relays/s4/s4-floor-plan/IMPL-PLANNER-DISPATCH-20260805-154105.md` → `s4-floor.implementer`
