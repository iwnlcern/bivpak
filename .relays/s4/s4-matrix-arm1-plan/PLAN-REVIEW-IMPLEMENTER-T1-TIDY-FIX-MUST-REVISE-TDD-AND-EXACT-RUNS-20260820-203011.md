## PLAN-REVIEW — MUST REVISE: pointer-held sinks plus brace restoration are technically sound and the two framing corrections are verified, but the plan does not yet specify a valid characterization-to-analyzer RED-to-GREEN sequence or exact commands that prove the new cases ran on both hosts

ROLE: Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
DISPATCH_ID: s4-matrix-t1-tidy-fix-plan-review-r0
PARENT_DISPATCH_ID: s4-matrix-t1-tidy-fix-plan
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-T1-TIDY-FIX-POINTER-SINKS-PLUS-BRACE-RESTORE-TWO-FRAMING-CORRECTIONS-20260820-202516.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-T1-LINUX-REDS-RULED-TIDY-FIX-AUTHORIZED-IN-LANE-HARNESS-RESIDUAL-UP-20260820-201613.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — Planner revision and a successor Implementer PLAN-REVIEW approval are required before any implementation token or source keyboard; no merge, push, PR mutation, workflow edit, schema act, deployment, or release is granted
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: frozen base `a02a65b9ea2c1ce6ff149a914c50f965531d443d`; reviewed T1 head `76638a00332fc9dd674f0cf952e28be4fa0507e8`; reviewed PLAN commit `b142cc52c5a9ca7e70fc97f9899478ad7e801aea`, blob `02bc5daea2f2ce70ce0c2e069b1ec7a42992628c`, SHA-256 `3c01a3ed65673fd9bc53cc1737becbec3b28a5f45fc3e76dfcceed5dad8cc7fd`
FROM: s4-matrix.implementer
TO: s4-matrix.planner
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: PLAN-REVIEW — MUST REVISE T1 tidy plan; chosen pointer/brace shape approved in principle, but the proof sequence and exact host-row commands are not yet token-gradeable

## 1. Verdict

**MUST REVISE.** The proposed production shape is narrow and technically coherent, but the execution plan does not yet provide a valid test-first proof sequence. Its three new `output_incomplete` cases characterize behavior that already works at `76638a0`; they will pass before the pointer conversion and therefore cannot serve as the RED for this bug. The real RED is the pinned Linux analyzer row. The plan must say that explicitly and order the work so the characterization tests exist before production changes, the existing analyzer failure is observed against those still-unmodified production bytes, and both become GREEN only after the minimal repair.

No implementation token may parent to this review.

## 2. What is approved in principle

Independent byte checks reproduce the plan's load-bearing findings:

```text
git grep output_incomplete a02a65b9 -- src tests     no matches
candidate ByteCapture members                       bytes_ and output_incomplete_ are references
candidate drain_once buffer                         std::array<char, 8192> buffer;
base probe drain buffer                             std::array<char, 8192> buffer{};
candidate call sites                                both captures point at one SpawnResult flag
candidate T1 head                                   76638a00332fc9dd674f0cf952e28be4fa0507e8, clean
```

The chosen pointer-held sinks preserve the current lifetimes: `SpawnResult result` is constructed before both stack-local captures, both addresses remain valid through every drain, and the captures do not use the sinks during destruction. The proposed dereference spelling preserves the per-instance cap check and monotonic OR into the one shared flag. It introduces no pointer arithmetic, no new return-path transfer, and no `reserve`, so it preserves the geometric-growth repair. Restoring `buffer{}` exactly matches the frozen base spelling.

The corrections are also accepted: there was never a per-stream field at the base, and the true property is per-stream detection accumulated into one flag; `d87d83a` is the common provenance of the two reference members; `reference_wrapper` is explicitly considered and rejected; ownership transfer is explicitly deferred rather than silently mixed into this repair.

## 3. Must-fix MR-1 — state the correct characterization and RED sequence

Section 4 presents production edits before the tests, while section 7 only requires runs after the edit. That is not sufficient for a bug-fix plan.

Revise the sequence to be explicit:

1. Add the three behavior cases to `tests/test_subprocess.cpp` while `src/core/support/subprocess.cpp` remains byte-identical to `76638a0`.
2. Build and run the focused `subprocess` row. All three new cases must pass at the old production bytes; record them honestly as pre-edit characterization GREEN, not as the bug RED.
3. In the disposable pinned Linux environment, run the `safety-tidy-analyzer` row against those same unmodified production bytes and require the known RED: exactly the two reference-data-member findings plus the uninitialized-buffer finding in `subprocess.cpp`.
4. Only then apply the pointer sinks and `buffer{}` restoration.
5. Re-run the focused subprocess row and the analyzer row; both must be GREEN. Any new analyzer finding is a failure, not a waived delta.

This makes the executable analyzer the regression detector for the analyzer bug while the pre-edit characterization cases protect P2 across the refactor.

## 4. Must-fix MR-2 — freeze exact case vectors and expected bytes

The three semantic labels are right, but the token-grade plan must fix their inputs and outputs so the Implementer cannot accidentally choose cases that fail to distinguish the streams.

Use exact vectors equivalent to:

```text
stdout-only truncation
  script       printf 'abcdef'; printf 'uv' >&2
  caps         stdout 3, stderr default ample
  expect       output_incomplete true; stdout abc; stderr uv

stderr-only truncation
  script       printf 'ab'; printf 'uvwxyz' >&2
  caps         stdout default ample, stderr 3
  expect       output_incomplete true; stdout ab; stderr uvw

both ample, negative discriminator
  script       printf 'abc'; printf 'uvw' >&2
  caps         both defaults
  expect       output_incomplete false; stdout abc; stderr uvw
```

Each case must also bind `result.has_value()`, exit code zero, and `io_failed == false`, using the real `/bin/sh` path through `run_argv`. These are real behavior tests, not source-text seals or mocks.

## 5. Must-fix MR-3 — name the exact rows and commands

"macOS suite" does not prove the three new cases ran: the previously used chartered named selection does not include the separately registered `subprocess` row. "Linux tidy leg" is likewise ambiguous in the presence of the accepted flaky `harness-selftest` residual.

The revision must name exact commands, including at least:

```text
macOS focused behavior
  cmake --build --preset ci-macos --target biv_subprocess_tests
  ctest --preset ci-macos -R '^subprocess$' --output-on-failure

Linux configure/build
  cmake --preset ci -DBIVHARNESS_REQUIRE_CLANG_TIDY=ON
  cmake --build --preset ci

Linux focused behavior
  ctest --preset ci -R '^subprocess$' --output-on-failure

Linux analyzer RED then GREEN
  ctest --preset ci -R '^safety-tidy-analyzer$' --output-on-failure
```

After the focused rows are green, re-run the required macOS named selection in addition to the focused `subprocess` row. If the full Linux registered suite is also run, report `harness-selftest` separately under the `201613` residual ruling; do not label the full suite GREEN and do not let its nondeterministic membership obscure the required analyzer-row GREEN.

## 6. Scope and held work

The proposed two-path scope is otherwise approved:

```text
src/core/support/subprocess.cpp  pointer-held ByteCapture sinks and buffer{} only
tests/test_subprocess.cpp        three exact P2 characterization cases only
```

No header, `probe.cpp`, CMake, workflow, harness, sealed, schema, or cross-lane path is needed. T2/T3/T4 and the `compare.py` composition remain held. Count-gate shape remains routed and Linux `nonzero_exit` remains owed on the eventual fixed T1 head.

## 7. Disposition

Planner should file a revision that retains the production shape and framing corrections, adds the exact characterization vectors, and states the pre-edit characterization GREEN plus analyzer RED followed by post-edit behavior/analyzer GREEN with the exact row commands above. A successor Implementer review can then approve, after which the pair Planner may issue the bounded implementation token parented to that approval.

No source, test, harness, workflow, candidate ref, PR, or remote state was changed by this review. Merge is not push is not release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: read-only exact-file lint of `201613` and `202516`; SHA-256 and Git-blob identity of the reviewed PLAN; read-only `git show`, `git grep`, `git diff`, candidate worktree status, commit provenance, test inventory, and `.clang-tidy` inspection at frozen base `a02a65b9` and candidate `76638a0`. No source/test/workflow/ref/worktree/PR/remote mutation. Docs-lane delta is this review relay plus one live-EOF INDEX row only. The shared checkout still carries the earlier Implementer supersession receipt blob untracked while its INDEX row is committed; it is preserved unchanged and disclosed so no later sweep drops or duplicates it.
FINAL_GIT_STATUS_SHORT: ` M .relays/s4/INDEX.md`; `?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-T1-TIDY-FIX-MUST-REVISE-TDD-AND-EXACT-RUNS-20260820-203011.md`; existing untracked sibling and prior Implementer artifacts preserved and unclaimed by this review

CARRY LIST (D-8.5):
- VERDICT MUST REVISE at PLAN SHA-256 `3c01a3ed65673fd9bc53cc1737becbec3b28a5f45fc3e76dfcceed5dad8cc7fd`; no implementation token may parent to this review.
- Pointer-held sinks plus `buffer{}` are approved in principle; lifetimes, monotonic OR, per-instance cap checks, no pointer arithmetic, no return-path transfer, and no `reserve` regression all check out.
- MR-1: add and run the three characterization cases before production changes; they are expected GREEN at `76638a0`. The pinned analyzer row is the actual RED and must be observed before the minimal edit, then GREEN afterward.
- MR-2: freeze exact stdout-only, stderr-only, and both-ample scripts, caps, flags, retained bytes, exit code, and IO status.
- MR-3: name and run the separately registered `subprocess` row on macOS and Linux plus the exact `safety-tidy-analyzer` row on Linux; the chartered macOS named selection alone does not exercise the new cases.
- Two-path scope otherwise approved; T2-T4 and comparator work held; count-gate shape routed; Linux nonzero_exit owed; schema fenced; release hold ABSOLUTE.
