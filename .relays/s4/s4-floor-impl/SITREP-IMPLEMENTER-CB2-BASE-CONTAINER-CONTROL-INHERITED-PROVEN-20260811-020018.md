## SITREP — plain post-R-4.8 base reproduces the exact five Linux probe failures; C/B2 delta exonerated

ROLE: Implementer
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-floor-impl-2-cb2-base-control-complete
PARENT_DISPATCH_ID: s4-floor-impl-2-cb2-base-control
RUN_ID: s4
TASK_ID: B2
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — fresh paired hand-up, master's condition-3, operator's paired condition-4, merge, seal, and release remain separately gated; release hold ABSOLUTE
DESIGN_LOCK_ID: m2-addendum11-422d451b-lock-20260810
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-PLANNER-CB2-BASE-CONTAINER-CONTROL-OWED-BEFORE-HANDUP-20260811-013353.md
RELATED_CONTEXT: .relays/s4/s4-floor-impl/REVIEW-FOLD-IMPLEMENTER-CB2-RESTACK-POST-R48-SEVEN-FRESH-COMPLETE-PUBLISHED-20260811-012231.md; .relays/s4/s4-floor-impl/IMPL-PLANNER-CB2-RESTACK-CARRY-RULE-CORRECTED-SEVEN-FRESH-DISPATCH-IMPL-TOKEN-20260811-003533.md
FROM: s4-floor.implementer
TO: s4-floor.planner
CC: s4.orchestrator-planner, operator, s4.orchestrator-reviewer, m-2.planner
SUBJECT: BASE CONTROL PASS — plain origin/main 38a4702 reproduces the exact five probe failures and eight failed assertions seen at fd857f1; failures are inherited and environmental, not introduced by C/B2

BASE CONTROL COMPLETE / E2 EVIDENCE FILED

Plain post-R-4.8 `origin/main` at exact
`38a4702bdc6c0fe82a102ebf58977ca7ad67623a` reproduces the **same five unique
probe cases and the same eight failed assertions** observed at re-stacked B2
`fd857f124b8e60d982fc341a563bab99317b0850`.

The owed comparison therefore resolves **INHERITED + environmental**. The C/B2 delta
did not introduce the four failures that appeared in addition to the single invalid-
executable failure seen in an earlier paneled run. The prior report's class label is
forward-corrected by this measured statement; immutable prior history is not rewritten.

No product, test, branch, PR, or remote-ref byte changed. No GitHub Actions run or
check was invoked, rerun, cancelled, or inspected. No PR metadata, merge, tag,
deployment, seal, or release action occurred. C never lands without B2; the release
hold is ABSOLUTE.

## Static exclusion reproduced before the control

`tests/test_probe.cpp` is byte-identical across all three relevant states:

| state | exact SHA | `tests/test_probe.cpp` SHA-256 | TEST_CASE count |
|---|---|---|---:|
| paneled B2 | `3762f3722a1fcebfbaa25921c31ca2f10df4ddf4` | `587d0197d8ca83f3d1de53c4e4138bb6962743363376783f6cb2e87498b6d6da` | 25 |
| post-R-4.8 base | `38a4702bdc6c0fe82a102ebf58977ca7ad67623a` | `587d0197d8ca83f3d1de53c4e4138bb6962743363376783f6cb2e87498b6d6da` | 25 |
| re-stacked B2 | `fd857f124b8e60d982fc341a563bab99317b0850` | `587d0197d8ca83f3d1de53c4e4138bb6962743363376783f6cb2e87498b6d6da` | 25 |

Additional static checks:

- R-4.8 paneled-B2-to-base delta: zero probe/process/spawn source paths;
- base-to-re-stacked-B2 delta: zero probe/process/spawn source paths;
- `src/core/support/error.cpp`: zero `spawn`, `nonzero_exit`, or `probe` matches.

That source chain made environment variance the only explanation consistent with the
bytes. The container run below converts the inference to E2 evidence.

## Controlled environment

The valid control ran in a fresh, non-`--init` container so PID 1 behavior matched the
canonical re-stacked parity run and no earlier probe execution could leave descendants:

- image: `ubuntu:24.04`;
- platform: `linux/amd64` (`uname -m` = `x86_64`);
- source: exact `git archive` of `38a4702` only;
- Python 3.12.3;
- CMake 3.28.3;
- GCC 13.3.0;
- exact eight pinned LLVM mirror packages, all SHA-256 values verified;
- every installed LLVM package version exact
  `1:22.1.8~++20260613092238+e80beda6e255-1~exp1~20260613092253.78`;
- `clang-tidy-22` reported Ubuntu LLVM 22.1.8;
- writable `/mnt/c/tmp` fixture provisioned before configure;
- locked harness Python requirements installed;
- core-adapter-purity check passed;
- configure selected `/usr/bin/clang-tidy-22` with LLVM major 22;
- default `biv` executable and complete `biv_tests` binary both built successfully;
- initial zombie count before the valid run: zero.

An earlier attempt built only the `biv_tests` target and therefore omitted the `biv`
executable required by CLI subprocess cases. Its 14 exit-127 CLI failures are a setup
artifact and are discarded. The prepared filesystem was completed with the missing
default target, snapshotted, and the evidence run was performed once in a new container
with zero initial zombies. Only that fresh result is the control of record.

## Raw base/head comparison

| measurement | plain base `38a4702` | re-stacked B2 `fd857f1` |
|---|---:|---:|
| total test cases | 269 | 385 |
| passed test cases | 264 | 380 |
| failed test cases | 5 | 5 |
| total assertions | 7,248 | 11,203 |
| passed assertions | 7,240 | 11,195 |
| failed assertions | 8 | 8 |
| Catch2 exit | 42 | 42 |

The five unique failing cases are identical on both sides:

1. `version probe does not fall back to PATH when a pinned executable cannot spawn`;
2. `version probe times out, reaps its direct child, and kills the process group`;
3. `version probe acknowledges a successfully detached descendant`;
4. `version probe preserves clean exit while disposing a pipe-holding grandchild`;
5. `post-KILL ownership falls back to blocking reap when handoff fails`.

The fifth case has two generated sections on both sides. That accounts for the same
eight failed assertions in each run. The re-stacked head adds 116 passing cases and
3,955 passing assertions while preserving the base's exact failure set; it adds no
product failure.

## Corrected record statement

The hand-up may now state:

> Plain post-R-4.8 `origin/main` in the same Ubuntu 24.04 `linux/amd64`, non-`--init`,
> pinned-LLVM environment reproduced the exact five unique probe failures and eight
> failed assertions observed at re-stacked B2. `tests/test_probe.cpp` is byte-identical
> across paneled B2, base, and new B2; neither delta touches probe/process/spawn source.
> The failures are inherited and environmental, not introduced by C/B2.

This measured statement supersedes the unproven membership wording in the `012231`
report without altering that immutable relay.

## Resource and scope closeout

Both task-scoped containers, the temporary prepared image, and the exact LLVM package
staging directory were removed after evidence capture. No unrelated Docker resource
was pruned or removed.

Boundary contract: not applicable — E2 evidence-only control; no product writer or
downstream materializer changed.

Done: static exclusion, same-environment plain-base build, full base product suite,
raw failure-set comparison, and forward correction.

Not done: no new product/test edit, review fold, PR mutation, Actions operation, merge,
tag, deployment, seal, release, or live verification.

Remaining dependency: the planner's already-convened seven-FRESH combined re-check.
On its PASS, this base control no longer blocks fresh paired hand-up.

ACTIONS_GIT_REF: no product/test/ref/PR mutation — exact read-only control at base 38a4702bdc6c0fe82a102ebf58977ca7ad67623a compared with published B2 fd857f124b8e60d982fc341a563bab99317b0850; only this SITREP and its append-only INDEX row are written and ride one explicit-path docs-lane commit whose SHA lands after filing
FINAL_GIT_STATUS_SHORT: C and B2 product worktrees remain clean; shared docs checkout retains unrelated pre-existing untracked relay files, preserved; this seat writes only this SITREP and its one INDEX row

CARRY LIST:
- `.relays/s4/s4-floor-impl/SITREP-IMPLEMENTER-CB2-BASE-CONTAINER-CONTROL-INHERITED-PROVEN-20260811-020018.md` -> `s4-floor.planner`
- BASE CONTROL E2: 38a4702 = 264/269 cases, 7240/7248 assertions; fd857f1 = 380/385 cases, 11195/11203 assertions; exact same five unique cases and eight failed assertions
- static exclusion confirmed: test_probe.cpp exact same hash and 25 cases across paneled/base/new; neither delta touches probe/process/spawn source
- corrected record: failures are INHERITED + environmental, not introduced by C/B2; the earlier class label is forward-corrected, not silently retained
- no Actions, product/ref/PR mutation, merge, seal, or release; A10.3 and release hold ABSOLUTE
