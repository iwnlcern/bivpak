## REVIEW-FOLD — Slice A Tasks 4–6 filed at one-commit head 26e6eb1; nine final-head receipts durable; PR #21 requests panel with GitHub CI billing-blocked before test execution

ROLE: Implementer
PHASE: REVIEW-FOLD
AUTHORITY: fold-in-only
DISPATCH_ID: s4-floor-impl-2-a-review-fold
PARENT_DISPATCH_ID: s4-floor-impl-2
RUN_ID: s4
TASK_ID: A
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no for this filing — the pair Planner's panel-at-SHA is next; final-head GitHub jobs were triggered only after implementation but the first completed job was blocked before execution by account billing/spend status; merge is operator-owned and the release hold is ABSOLUTE
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/IMPL-PLANNER-RESTACK-SLICE-A-GO-20260806-051129.md
FROM: s4-floor.implementer
TO: s4-floor.planner
CC: s4.orchestrator-planner, operator
SUBJECT: DONE_WITH_CONCERNS — Slice A Tasks 4–6 are one reviewed commit at PR #21 head 26e6eb1; local gates and nine exact-head mutation cycles are green; final-head GitHub CI is billing-blocked before tests run; panel requested, merge/release held

FOLD_SCOPE:
- CMakeLists.txt -> in
- harness/bivharness/e3.py -> in
- harness/ci/check_version_floor_mirror.py -> in
- harness/scenarios-e3/e3-dual-resume.json -> in
- harness/selftest/test_e3_asserts.py -> in
- harness/selftest/test_envelope.py -> in
- schemas/biv-json-envelope.v1.schema.json -> in
- src/adapters/adapter.hpp -> in
- src/adapters/claude_code/install.cpp -> in
- src/adapters/codex/install.cpp -> in
- src/adapters/version_floor.cpp -> in
- src/adapters/version_floor.hpp -> in
- src/core/open/render.cpp -> in
- src/core/open/sessions.cpp -> in
- src/core/pack/pack.cpp -> in
- src/core/report/envelope.cpp -> in
- tests/fixtures/probe-envelope-v1.json -> in
- tests/test_adapter_claude_install.cpp -> in
- tests/test_adapter_codex_install.cpp -> in
- tests/test_cli.cpp -> in
- tests/test_envelope.cpp -> in
- tests/test_pack.cpp -> in
- tests/test_render.cpp -> in
- tests/test_sessions.cpp -> in
- docs/sprints/2026-08-04-s4-step4/results/receipts/Slice-A-nine-mutation-receipts.md -> in
- PR #21 body -> in
- .relays/s4/s4-floor-impl/REVIEW-FOLD-IMPLEMENTER-SLICE-A-TASKS-4-6-FILED-20260806-091452.md -> in
- .relays/s4/INDEX.md -> in
FOLD_SCOPE_RESULT: all-in

DONE_WITH_CONCERNS

Slice A is filed as exactly one commit,
`26e6eb1fbe57401e9ed3c931a57f0d8863d96fd6`, whose exact parent is the frozen B1
head `ff63e521d8ae5229a831aab8718a3fa58205f40f`. The commit subject is the plan's
prescribed subject:

`feat(adapters): version floor + C1 conjunction, one head — allowlist retired, mirror + pin check same-commit`

Draft PR #21 (`s4-floor/a-floor-core` → `main`) points to that exact head. The diff is
24 authorized paths. It touches no manifest, scan, `.github`, host-store, release, or
collect-anchor/A3 source path; therefore the A3 per-head collect-source ceremony was not
triggered. The A2 envelope-schema blob lock was mechanically recaptured in the same
commit at `4775167b2c28eab13863911196707234c4211c6f`.

## Folded Tasks 4–6

- Task 4: the shared bounded version grammar, MIN/survey rows, direction gate, both
  allowlist deletions, product/harness/scenario mirror, and same-commit drift checker.
- Task 5: factory-only invariant capabilities, four closed wire spellings,
  absent/unreadable pre-consent zero-call refusals, and detail-preserving mapper rows.
- Task 6: below-MIN omission before spool/manifest reservation and default-visible
  readable-newer disclosure driven only by derived capability state.
- The E3 carrier retains trusted forward-host evidence through later setup/open
  failures while ordinary and exact-string-spoof Biv warnings remain untrusted.
- The PR body carries the decided-not-deleted flip ledger for every replaced assertion
  family and the explicit OUT set.

## Reviews and local evidence at the exact head

- Independent task review, whole-slice review, amendment re-review, and final CI-fix
  delta review all returned Ready YES with no Critical, Important, or Minor findings.
- `ctest --preset dev --output-on-failure -E '^safety-hardening$'` completed all 14
  locally applicable rows: product, purity, mirror, errno, both schema gates, harness
  selftests, E2, Werror, and the locally available safety rows passed.
- Product result: 247 cases; 245 passed and 2 expected WSL skips; 6,592 assertions
  passed. Harness selftests: 969 passed. E2: passed in 148.12 seconds.
- A separate GCC 15 adapter target with `-Werror=missing-field-initializers` passed.
- `safety-hardening` is not waived: it is excluded locally only because Darwin lacks
  the Linux `readelf` prerequisite; the final-head Linux workflow owns that row.
- Final implementation worktree proof: status empty; `git diff --exit-code` zero; exact
  parent `ff63e52`; `git rev-list --count ff63e52..HEAD` = 1; 24 diff paths.

## Nine exact-head mutation receipts

All nine plan-required arms were replayed after the final amendment at exact head
`26e6eb1`: correct-code GREEN → one isolated mutation → intended RED with required
sibling controls → exact inverse → same-command GREEN. Every temporary instrument was
removed and the tree returned clean between arms:

- `FX-VF-O3/{codex,claude}/disclosure-default-visible`;
- `FX-VF-O6/{codex,claude}/no-image-field-in-derivation`;
- `FX-VF-O4/{codex,claude}/basis-nul-bearing/refuses-before-comparison`;
- `FX-MG-7/{codex,claude}/full-grammar-red`;
- `A5.8/silent-promotion` with the real 0.145.0/2.2.0 inputs and both MINs frozen.

The run-traceable evidence is durable at
`docs/sprints/2026-08-04-s4-step4/results/receipts/Slice-A-nine-mutation-receipts.md`,
refreshed at docs-lane commit `15fbcb0` (initial filing `5362a03`). A final focused
control run after receipt cleanup passed 162 assertions across 5 committed cases.

## GitHub CI disposition and concern

Per operator instruction, no GitHub CI/CD test was run until implementation was
complete. The guarded exact-head force-with-lease update then triggered the push and PR
workflow runs `31118381998` and `31118387236`. GitHub queued all eight jobs. The first
job to settle, push-run macOS job `92673449370`, completed red without executing code.
Its sole check annotation says the job was not started because recent account payments
failed or the spending limit needs to be increased, and directs the account owner to
Billing & plans. At filing time the other seven jobs remain pending.

The final-head remote matrix is therefore **billing-blocked before test execution**:
zero final-head CI tests have run, and no remote test verdict is claimed. This external
condition is disclosed and routed; it is not treated as a product failure and is not
repairable inside the pair's implementation or `.github` scope. The draft PR remains
the durable place to observe jobs after the account condition is restored.

The earlier `e11731a` runs exposed two in-scope CI deltas before the final amendment:
GCC missing-field-initializer warnings and three stale CLI exit expectations. The final
three-file amendment initialized both admitted details explicitly and changed only
those three exit expectations from 0 to the designed pre-consent refusal code 2. That
delta was independently reviewed and reproduced locally before `26e6eb1` was pushed.

## Requested next action and holds

Planner panel-at-SHA is requested against PR #21 head `26e6eb1`. The GitHub billing or
spending-limit condition requires account-owner disposition before final-head CI can
execute; after restoration, the same PR jobs must be observed. Any `.github/**`
count-gate correction remains hard OUT for this pair. No merge or release authority is
claimed or exercised.

ACTIONS_GIT_REF: Slice A exact head `26e6eb1fbe57401e9ed3c931a57f0d8863d96fd6` pushed by immutable force-with-lease to draft PR #21; final-head receipt evidence refreshed at docs-lane commit `15fbcb0`; this relay and its append-only INDEX row ride a later docs-lane commit whose SHA lands in repository history after filing
FINAL_GIT_STATUS_SHORT: Slice A implementation worktree clean at 26e6eb1 and equal to origin/s4-floor/a-floor-core; docs lane clean at 15fbcb0 before this relay, apart from the unrelated pre-existing untracked s4-matrix relay which remains untouched

CARRY LIST:
- `.relays/s4/s4-floor-impl/REVIEW-FOLD-IMPLEMENTER-SLICE-A-TASKS-4-6-FILED-20260806-091452.md` → `s4-floor.planner`
- `https://github.com/iwnlcern/bivpak/pull/21` at `26e6eb1fbe57401e9ed3c931a57f0d8863d96fd6` → panel-at-SHA and CI observation only; merge/release held
- `docs/sprints/2026-08-04-s4-step4/results/receipts/Slice-A-nine-mutation-receipts.md` at docs commit `15fbcb0` → receipt evidence
