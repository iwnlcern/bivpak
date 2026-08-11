## IMPL BLOCKER — Amendment A2's schema lock recapture is exact, but B1's intended Codex source change leaves the C1 whole-file drift anchor deterministically red

ROLE: Implementer
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: s4-floor-impl-2-b1-c1-tripwire-blocker
PARENT_DISPATCH_ID: s4-floor-impl-2
RUN_ID: s4
TASK_ID: B1
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — the locked plan requires full harness selftests green at every slice head, but B1's dispatched `codex.cpp` change invalidates the C1 whole-file source anchor; no B1 act or authorized Amendment A2 change admits recapturing that different harness literal
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/IMPL-PLANNER-RESUME-B1-RECAPTURE-TO-PR-20260805-210447.md
FROM: s4-floor.implementer
TO: s4-floor.planner
CC: s4.orchestrator-planner, operator
SUBJECT: BLOCKED before B1 recapture commit/PR — the envelope blob lock can be recaptured exactly, but the independent C1 adapter-source anchor makes the required harness selection red; exact anchor disposition is needed

## Amendment A2 was exercised exactly, then restored on stop

- Worktree/branch: `/Users/jack/.config/superpowers/worktrees/bivpak/s4-floor-b1-codex-liveness`, `s4-floor/b1-codex-liveness@49448016b4104d2e75e32eada4686036246485f1`.
- Before editing, the focused schema-lock test reproduced RED: exit `1`, actual envelope blob `561dccf0dbd8e374b975ba19e2dbd8ddad553e81` versus old literal `ac127cab3ecb8bb39b82ecd20c04bb41ba0d6717`; the exit-map value matched.
- The authorized transient edit changed only that envelope literal. The focused test then passed: exit `0`, `1 passed`; `git hash-object` returned exactly `561dccf0dbd8e374b975ba19e2dbd8ddad553e81`; the diff was one deletion plus one insertion and `git diff --check` was clean.
- The required harness selection was not green, so the stop rule fired before commit/review/PR. The temporary literal was restored. The implementation worktree is clean at `4944801`; no commit, push, PR, successor branch, merge, seal, or release occurred.

## Independent deterministic failure

Configured run:

`ctest --test-dir build/dev -R '^(harness-selftest|harness-e2)$' --output-on-failure`

`harness-selftest` completed with ctest exit `8`: `903 passed, 52 failed`. The envelope lock test itself passed under the authorized transient literal. Representative failures returned `Status.INVALID` / `e3-post-materialization-invalid`; the discriminating direct test failed with:

`C1 drift tripwire RED: adapter session-location source changed (codex_adapter_file)`

Fresh direct reproduction after restoring the clean head:

`PYTHONPATH=harness /Library/Frameworks/Python.framework/Versions/3.12/bin/python3.12 -c 'from bivharness import e3; print(e3._c1_drift_tripwire_failures())'`

Result: exit `0`, list containing exactly that one Codex-anchor failure.

Root cause is exact and independent of Amendment A2. `harness/bivharness/e3.py:68-76` pins the SHA-256 of the entire `src/adapters/codex/codex.cpp` file at `4fb3b38ca8df11dfc92e735c69ac8717a4920d54724d85cde49a93c24ace56cb`. B1's reviewed, required tail-liveness implementation changes the file SHA-256 to `f00fbde5061fddb961f09148d51061490aacdf57b6eedd8b49ff9abd016d7e12`, although it does not change the session-location surface the C1 tripwire protects. Every E3 path that calls the tripwire then fails closed before its expected outcome.

The plan's verification ledger requires `full ctest + harness selftests green at the head` for every slice. `harness/bivharness/e3.py` is in the overall dispatch universe for named Slice-A version-floor changes, but no B1 task or Amendment A2 admits changing `_ADAPTER_SOURCE_ANCHORS`; a drive-by pin update would be a new act/change-shape and must be ruled before edit. `harness-e2` was stopped once the mandatory selection was irretrievably red and is not claimed green.

## Deviation and requested disposition

SCOPE_DIFF:
- `src/adapters/codex/codex.cpp` -> in (Task 3; reviewed B1 behavior)
- `harness/selftest/test_envelope.py` -> in for Amendment A2's exact envelope-literal recapture only
- `harness/bivharness/e3.py::_ADAPTER_SOURCE_ANCHORS[codex_adapter_file]` -> OUT of the B1 act and every granted amendment/change-shape
SCOPE_DIFF_RESULT: deviation-present

Recommended narrow path: admit a B1 mechanical C1 anchor recapture in the same reviewed head — update only the Codex anchor literal from `4fb3b38c…` to the reviewed B1 whole-file SHA-256 `f00fbde5…`; leave the Claude anchor and all C1 behavior unchanged; prove the focused drift-tripwire tests, full harness selftests, and E2 selection green; then scoped review, B1 PR, and Slice-A seed. State whether the same literal-only discipline applies when later reviewed slices intentionally change an anchored adapter file.

Alternatives requiring an explicit ruling are: waive the per-slice harness-green gate for B1, or redesign C1 to anchor the protected session-location surface rather than the whole adapter file. Neither is inferred here.

The three prior non-gating reviewer items remain carried unchanged: the `codex_testing` linkage seam lacks a shared declaration; the intentional two-LF fixture needs a scoped `git diff --check` exception or approved representation; and direct TornTail/unknown renderer coverage remains for B2. None authorizes an edit and none is this blocker.

ACTIONS_GIT_REF: implementation branch remains `s4-floor/b1-codex-liveness@49448016b4104d2e75e32eada4686036246485f1`; this blocker relay plus its append-only INDEX row are the only docs-lane writes, with commit named in repository history after filing
FINAL_GIT_STATUS_SHORT: implementation worktree clean at `49448016b4104d2e75e32eada4686036246485f1`; docs-lane precommit set is `.relays/s4/INDEX.md` plus this relay

## Next action

Planner: route the exact C1-anchor disposition to `s4.orchestrator-planner`. Keep the B1 schema-lock commit, scoped review, PR/push, Slice A, and Tasks 4-11 held until the green-at-head contradiction is resolved by an exact ruling and, if needed, folded plan scope.
