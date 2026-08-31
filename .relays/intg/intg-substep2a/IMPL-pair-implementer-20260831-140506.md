## IMPL return — baseline environment blocker before the first TDD edit: product suites green, five full-CTest rows red from an absent ignored harness venv and macOS-without-readelf; route the setup treatment

ROLE: Pair Implementer
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: intg-substep2a-impl-return
PARENT_DISPATCH_ID: intg-substep2a-impl
IN_REPLY_TO: intg-substep2a/IMPL-pair-planner-20260831-030859.md
RELATED_CONTEXT: intg-substep2a/PLAN-pair-planner-20260831-022653.md; intg-substep2a/PLAN-REVIEW-pair-implementer-20260831-025316.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep2a-20260830.md; intg-substep1/IMPL-pair-implementer-20260828-152108.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — the pair Planner can route whether ignored environment preparation is admitted setup or requires an instrument revision; no product-semantic or operator-waiver decision is requested
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: intg-format-act-plan
DESIGN_LOCK_ID: m1-addendum-N-82293732-lock-20260827
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: intg-substep2a-plan-20260830 @ sha256 57ab3b9ba15c5674dae5b42dc3a3c48252e844f8e3d863d0cb1f3682c33b4a4b
BASE: main@46df8f3c35981a4ae3f77cf3293a4b7212b4b996
BRANCH: intg/format-act@46df8f3c35981a4ae3f77cf3293a4b7212b4b996 in /Users/jack/Programming/bivpak-intg-format-act; clean; no implementation commit
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: master.master-planner, master.master-reviewer, m-1.planner, m-1.implementer
SUBJECT: BLOCKED before Task 1 RED — clean pinned-base configure/build succeeded and product suites passed, but canonical full macOS CTest is 14 pass / 5 fail / 3 skip because the fresh worktree lacks the ignored `.venv-harness` and macOS lacks `readelf`; route environment setup versus plan revision

## Status

BLOCKED before the first test or production edit. The addressed implementation token was validated, and the exact dispatched worktree was created from the pinned base. The worktree remains clean at `46df8f3c35981a4ae3f77cf3293a4b7212b4b996`.

Per `superpowers:using-git-worktrees`, a red clean-base test run stops implementation pending a routed decision. Per the plan's execution-not-amendment rule, I did not silently create an unmentioned harness environment or reinterpret a red row as green.

## Newly measured baseline receipts

Executed in `/Users/jack/Programming/bivpak-intg-format-act`:

```text
cmake --preset ci-macos                         rc 0
cmake --build --preset ci-macos                 rc 0
ctest --preset ci-macos                         rc 8
CTest summary                                   14 passed / 5 failed / 3 skipped (74%)
```

Product-facing rows at the pinned base are green:

```text
repo_engine                                     418 assertions / 56 cases, pass
biv_tests                                       14,794 assertions; 397 pass / 3 skipped cases, pass
probe                                           296 assertions / 25 cases, pass
safety-build-werror                             pass
```

The five red rows and their direct causes from `build/ci-macos/Testing/Temporary/LastTest.log` are:

```text
probe_envelope_schema                           ModuleNotFoundError: jsonschema
generated_envelope_conforms                     ModuleNotFoundError: jsonschema
harness-selftest                                collection errors: jsonschema / zstandard
harness-e2                                      ModuleNotFoundError: zstandard
safety-hardening                                readelf unavailable
```

## Root-cause classification

The fresh worktree has no `.venv-harness`. `harness/CMakeLists.txt:12-20` silently falls back to the system Python when that directory is absent; the selected Python 3.14 has pytest but lacks the locked `jsonschema` and `zstandard` packages. `harness/requirements.lock` pins exactly `jsonschema==4.25.1`, `pytest==8.4.2`, and `zstandard==0.25.0`. The shared Git exclude already ignores `.venv-harness/`, and the primary worktree has such an environment; this fresh worktree does not.

The hardening row is the known Linux ELF tool row executed on macOS. The prior sub-step-1 report `152108` recorded the same direct result, `readelf unavailable`, as a raw host-environment observation rather than a candidate-attributable product red.

No candidate byte exists, so none of the five rows can be candidate-attributed. This is setup/instrument topology at the pinned base.

## Routed decision requested

Please choose and return one exact path:

1. Admit the following as ignored environment setup, not a repository-byte or plan-scope change: create `.venv-harness` inside the dispatched worktree, install `harness/requirements.lock`, reconfigure so CMake selects that interpreter, rerun the full baseline, retain `readelf unavailable` verbatim as the known macOS host row, then begin Task 1 TDD only if the dependency-backed rows pass.
2. If the macOS instrument must spell that environment preparation explicitly, revise the plan at a new digest and route it through a new exact-hash review before resuming implementation.

I recommend path 1 because it uses the repository's locked dependency set, changes no tracked byte, matches the already-established harness interpreter topology, and leaves the raw hardening observation disclosed. This is a recommendation, not self-authorization; implementation remains stopped until your return.

## Boundary and not-done

- No source or test byte changed; all seven authorized paths remain byte-identical to base.
- No Task 1 test was written, so no TDD RED/GREEN claim exists.
- No dependency was installed and no build cache was altered after the observed baseline.
- No format, M-surface, m-2, m-3, schema, harness, workflow, 2b wiring, merge, push, PR, publication, deployment, or release action occurred.
- The inherited primary-worktree S4 state was not touched.

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: no — no credential or permission surface touched
- migration/backfill/destructive-write/canonical-data-repair: no — no product or canonical data write
- money/inventory/orders/planning/accounting/trust-critical-state: no — no such runtime state
- AI-or-automation-acts-downstream: no — no downstream automation action
- worker/scheduler/queue/retry/async-side-effect: no — no product runtime action
- cross-repo/service-contract/generated-schema/shared-API-event: yes — the locked M/N format act remains the governing cross-repo contract
- user-visible-control-with-materializer/downstream-consumer: yes — the planned feature is user-visible, but no implementation byte exists yet
- test-runtime-role-mismatch: yes — fresh-worktree Python dependency topology and Linux-only `readelf` on macOS are the blocker
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: yes — proceeding past a red base without routed treatment would confound attribution
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: none
- scan_presented_to_operator: no — no ceremony downgrade or risk acceptance requested
- operator_reply_after_scan: none
- valid_waiver: no
WAIVED_RISK_ACCEPTANCE: none — no waiver requested or inferred

ACTIONS_GIT_REF: created branch/worktree `intg/format-act@46df8f3c35981a4ae3f77cf3293a4b7212b4b996` at `/Users/jack/Programming/bivpak-intg-format-act`; configured and built `build/ci-macos`; baseline CTest rc 8 with the receipts above; worktree `git status --short` is empty; no source/test edit or implementation commit; this blocker relay submits through the intg daemon from primary main@a5696feb92b090b2f7fe19a02992c58f359b7374
RELAY_LINT: exact-file v2.9.2 lint is the daemon submission gate; rendered result and digest reported externally
FINAL_GIT_STATUS_SHORT:
worktree `/Users/jack/Programming/bivpak-intg-format-act`: none — clean tree at intg/format-act@46df8f3c35981a4ae3f77cf3293a4b7212b4b996
primary `/Users/jack/Programming/bivpak` inherited state:
 M .relays/s4/INDEX.md
 M .relays/s4/SEATS.md
?? .relays/s4/s4-floor-impl/REVIEW-FOLD-IMPLEMENTER-CB2-RECHECK2-TWO-CRITICALS-COMPLETE-PUBLISHED-20260810-185643.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV0-20260809-033926.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV1-20260809-050934.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV2-APPROVE-20260809-053253.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV2-APPROVE-LINEAGE-CORRECTION-20260809-061515.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV3-MUST-REVISE-20260809-210140.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV4-APPROVE-20260809-211611.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV5-MUST-REVISE-20260809-230557.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV6-APPROVE-20260809-231944.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-CARRIER-REV0-20260809-055741.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-CARRIER-REV1-20260809-061515.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-CARRIER-REV2-APPROVE-20260809-062921.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-CARRIER-REV2B-UNIQUE-APPROVE-20260809-141439.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-FOLD3-RECEIPT-DETERMINISM-MUST-REVISE-20260810-041555.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-FOLD3-RECEIPT-DETERMINISM-R1-APPROVE-20260810-043843.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-LENSFOLD-SIX-MUSTFIX-APPROVE-20260810-074840.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-MICROFOLD-V1-PROOF-MUST-REVISE-20260810-145556.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-MICROFOLD-V1-PROOF-R1-MUST-REVISE-20260810-150633.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-MICROFOLD-V1-PROOF-R2-APPROVE-20260810-152645.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-CARRIER-COMPLETE-20260809-192358.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-CARRIER-DISPATCH-LINEAGE-BLOCKER-20260809-063906.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-CARRIER-IMPLEMENTED-E2-BLOCKED-20260809-182853.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-FOLD-MF1-MF6-COMPLETE-20260809-220327.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-FOLD2-EXTENDED-ROOT-RF1-RF2-COMPLETE-20260810-020857.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-FOLD3-COMPLETE-20260810-052656.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-FOLD3-DISPATCH-LINEAGE-BLOCKER-20260810-030814.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-LENSFOLD-COMPLETE-20260810-092751.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-MERGE-BLOCKED-DRAFT-UNSTABLE-20260810-174554.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-MICROFOLD-DONE-WITH-CONCERNS-20260810-160710.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-PR24-MERGED-STEP4-20260810-184033.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-WAVE-A-REVERIFY-STAGE1-INDEPENDENT-STOP-CORROBORATION-20260820-161626.md
?? .relays/s4/s4-matrix/SITREP-implementer-20260825-220111.md
?? docs/sprints/2026-08-04-s4-step4/MIGRATION-adt-skills-2.9-20260816.md
