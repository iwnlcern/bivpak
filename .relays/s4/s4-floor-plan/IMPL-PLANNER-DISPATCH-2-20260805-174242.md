## IMPL DISPATCH (REPLACEMENT) — issued on the complete re-keyed chain: approving review in place, waiver boundary honored, scope gate all-in

ROLE: Planner
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: s4-floor-impl-2
PARENT_DISPATCH_ID: s4-floor-pair-plan-review-approve
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new gate — the human decision is satisfied on record (operator path-2 waiver in the orchestrator's `173024`); this token authorizes implementation of the locked plan only; merge remains the operator's alone; the release hold is ABSOLUTE
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-plan/PLAN-REVIEW-IMPLEMENTER-REKEYED-APPROVE-20260805-173930.md
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: s4.orchestrator-planner, operator
SUBJECT: DISPATCH — implement s4-floor-fold-plan-20260805 (plan SHA 5e88a538…) under the approving review s4-floor-pair-plan-review-approve; five stacked heads B1→A→C→B2→E

The locked plan: `docs/sprints/2026-08-04-s4-step4/plans/2026-08-05-s4-floor-fold-plan.md`
— disk SHA-256 re-verified at issuance: `5e88a538b26d8318d3a6260dc4f988e644bcf3ed153a7c0a970cbd25918cfecb`,
byte-identical to the substance approved at `s4-floor-plan-review-rev2` and re-approved
on the re-keyed lineage at `s4-floor-pair-plan-review-approve` (verdict approve, bare).

Condition record at issuance:
- Lineage: this relay parents to `s4-floor-pair-plan-review-approve`, which parents to
  the unique pair PLAN `s4-floor-pair-plan` (`…-REKEYED-20260805-155200`), which parents
  to the approving DESIGN-REVIEW lineage. `DISPATCH_ID: s4-floor-impl-2` verified unique
  in the relay root before filing.
- Waiver boundary honored (the operator's path-2 grant, scan of record in `173024`): it
  covers ONLY the two named historical errors on the voided `154105` artifact; this
  relay's exact-file lint is exit 0, and the pre-file root check is recorded in the
  hand-off — the review's condition is that ONLY the two waived scars and the
  separately-routed INDEX tooling complaints remain, and any new replacement-chain
  error is a stop, not a proceed.
- No hard trigger fired beyond what this production-risk ceremony already carries.

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

Every row is a path the locked plan names; the universe is the plan's own enumerated
dispatch-scope set (unchanged since the rev2 approve), so the diff is identity by
construction — recorded mechanically, not judged. Anything OUTSIDE these rows (slice D,
`src/core/manifest/*`, `.github/`, host stores, sibling relay trees, the pdc RUNCARD,
any new test translation unit) stays OUT: touching one is a deviation that re-engages
`s4.orchestrator-planner` BEFORE the edit.

Execution terms (restating the locked plan, adding nothing): Superpowers
`executing-plans`; the five stacked heads B1→A→C→B2→E per the plan's topology section;
TDD RED-first; the one-commit laws for slices A and C; receipts at their GREEN-abling
slice with the discriminating-input-class precheck; evidence to
`docs/sprints/2026-08-04-s4-step4/results/receipts/**`; reports to
`.relays/s4/s4-floor-impl/**` + EOF INDEX rows, docs-lane explicit-path commits.
IMPL exits at branch + PR + report per head; no merge — the operator's token alone, per
PR, in stack order. Blockers and scope pressure route to me; above-pair goes to
`s4.orchestrator-planner` via my seat.

DISPATCH IMPL

ACTIONS_GIT_REF: writes at this seat: this relay + its INDEX row, committed on the docs lane with explicit paths (SHA in the commit record); no product/test/harness/schema edit; no push
FINAL_GIT_STATUS_SHORT: not a read-only phase report; disk evidence rides the docs-lane commit SHA in ACTIONS_GIT_REF

CARRY LIST:
- `.relays/s4/s4-floor-plan/IMPL-PLANNER-DISPATCH-2-20260805-174242.md` → `s4-floor.implementer`
