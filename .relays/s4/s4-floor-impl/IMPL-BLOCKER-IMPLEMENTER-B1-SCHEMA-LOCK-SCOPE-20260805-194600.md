## IMPL BLOCKER — Slice B1 product behavior is review-clean, but the required schema edit leaves an out-of-scope harness lock deterministically red

ROLE: Implementer
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: s4-floor-impl-2-b1-schema-lock-blocker
PARENT_DISPATCH_ID: s4-floor-impl-2
RUN_ID: s4
TASK_ID: B1
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — `harness/selftest/test_envelope.py` is OUT of the dispatched universe; Planner/orchestrator must grant the exact lock-recapture path or direct a plan-compatible alternative before any edit or Slice-A start
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/IMPL-PLANNER-RESUME-TASK1-20260805-183403.md
FROM: s4-floor.implementer
TO: s4-floor.planner
CC: s4.orchestrator-planner, operator
SUBJECT: BLOCKED after B1 whole-slice review — required envelope-schema change invalidates an OUT harness blob lock; exact lock-maintenance scope is needed before PR or Slice A

## B1 implementation and review evidence

- Isolated worktree: `/Users/jack/.config/superpowers/worktrees/bivpak/s4-floor-b1-codex-liveness`.
- Branch/head: `s4-floor/b1-codex-liveness@49448016b4104d2e75e32eada4686036246485f1`.
- B1 commits: `d6133de` carrier, `2629e9b` unsigned writer boundary, `581a211` text warnings, `2ee2e08` exact Codex tail liveness, `4944801` discriminating trailing-blank control.
- Task 1, Task 2, and Task 3 passed independent task review; Task 3's only Important test finding passed a scoped fix re-review.
- Full relevant product evidence at the reviewed head: `229` cases, `227` passed, `2` platform-only skipped; `5754/5754` assertions passed. Focused Codex, Claude, CLI, schema, and E2 controls were green as recorded in the ignored SDD reports.
- Whole-slice review: product behavior aligns with Tasks 1-3; merge-readiness verdict is `With fixes` solely because the harness schema lock below is deterministically stale.

The implementation worktree is clean at the named head. Nothing is pushed, no PR is open, and no Slice-A successor branch has been created.

## Deterministic failure

Task 1 was required to change `schemas/biv-json-envelope.v1.schema.json`. Its reviewed B1 blob id is `561dccf0dbd8e374b975ba19e2dbd8ddad553e81`, while `harness/selftest/test_envelope.py:12-15` still pins the pre-B1 blob `ac127cab3ecb8bb39b82ecd20c04bb41ba0d6717`.

Fresh focused reproduction at `4944801`:

`/Library/Frameworks/Python.framework/Versions/3.12/bin/python3.12 -m pytest harness/selftest/test_envelope.py::test_vendored_schema_artifacts_match_current_locked_bytes -q`

Result: exit `1`, one failed test. The assertion reports the envelope-schema map entry as actual `561dccf0dbd8e374b975ba19e2dbd8ddad553e81` versus expected `ac127cab3ecb8bb39b82ecd20c04bb41ba0d6717`; the exit-map entry is unchanged and identical.

This is load-bearing for the next slice: Task 4 explicitly requires harness selftests green, and the verification ledger requires every slice head green before it seeds its successor. Task 5 later changes the envelope schema again, and Task 7 later changes the exit map, so a one-off undocumented local edit would not provide a stable per-slice lock discipline.

## Mechanical deviation

SCOPE_DIFF:
- schemas/biv-json-envelope.v1.schema.json -> in
- harness/selftest/test_envelope.py -> OUT
SCOPE_DIFF_RESULT: deviation-present

No OUT edit has occurred.

## Requested disposition

Recommended: admit exactly `harness/selftest/test_envelope.py` for mechanical schema-lock maintenance only. At each slice that changes a locked schema artifact, update only the corresponding `CURRENT_LOCKED_SCHEMA_BLOBS` literal to the reviewed git blob id in that same slice/head; do not change harness behavior, scenario logic, or any other selftest surface.

Immediate B1 fold: recapture only the envelope-schema entry to `561dccf0dbd8e374b975ba19e2dbd8ddad553e81`, prove the focused lock test and relevant harness selection green, run scoped review, then create the B1 PR. Later Slice A/C recaptures use their final reviewed schema/exit-map blobs inside their binding one-commit laws.

If that repeated per-slice lock maintenance is not the intended governance, direct the exact alternative and identify how B1 and Task 4 may satisfy their green harness gates without falsifying the current lock.

The whole-slice reviewer also recorded three non-gating minors for final review: the `codex_testing` linkage seam lacks a shared declaration; the intentional two-LF fixture needs a scoped `git diff --check` exception or approved representation; and direct TornTail/unknown renderer coverage remains for B2. None authorizes an edit here and none is the present blocker.

ACTIONS_GIT_REF: implementation branch `s4-floor/b1-codex-liveness@49448016b4104d2e75e32eada4686036246485f1`; this blocker relay and its append-only INDEX row are the only main/docs-lane writes, with commit named in repository history after filing; no OUT edit, push, PR, successor branch, merge, seal, or release.

FINAL_GIT_STATUS_SHORT: implementation worktree clean at `49448016b4104d2e75e32eada4686036246485f1`; docs-lane precommit set is `.relays/s4/INDEX.md` plus this new relay.

## Next action

Planner: route the exact lock-maintenance scope request to `s4.orchestrator-planner`. Keep B1 PR/push, Slice A, and Tasks 4-11 held until an exact disposition is approved and folded into the plan/dispatch universe.
