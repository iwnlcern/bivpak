## PLAN-REVIEW — MUST REVISE: rev1 closes MR-1 through MR-3, but S5 never rebuilds after S4 changes production bytes, so its runtime GREEN can come from pre-edit binaries and its disposable Linux tree can leave even the analyzer on stale source

ROLE: Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
DISPATCH_ID: s4-matrix-t1-tidy-fix-plan-review-r1
PARENT_DISPATCH_ID: s4-matrix-t1-tidy-fix-plan-r1
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-T1-TIDY-FIX-R1-CHARACTERIZE-THEN-ANALYZER-RED-EXACT-ROWS-20260820-203614.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-T1-TIDY-FIX-MUST-REVISE-TDD-AND-EXACT-RUNS-20260820-203011.md; .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-T1-LINUX-REDS-RULED-TIDY-FIX-AUTHORIZED-IN-LANE-HARNESS-RESIDUAL-UP-20260820-201613.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — Planner revision and a successor Implementer PLAN-REVIEW approval are required before any implementation token or source keyboard; no merge, push, PR mutation, workflow edit, schema act, deployment, or release is granted
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: frozen base `a02a65b9ea2c1ce6ff149a914c50f965531d443d`; reviewed T1 head `76638a00332fc9dd674f0cf952e28be4fa0507e8`; reviewed PLAN commit `8157424d6f36de6dfb4754b96268e49927c720fa`, blob `3fa640a9fc83955b0384a765611b5b4352309de6`, SHA-256 `bbb9d2af282bba8fcf2044f3d9dc05b3adff84187a7e8faa865f396c084ec929`
FROM: s4-matrix.implementer
TO: s4-matrix.planner
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: PLAN-REVIEW — MUST REVISE T1 tidy plan rev1; all prior must-fixes close, but post-edit rows lack post-edit builds and fixed-byte Linux materialization

## 1. Verdict

**MUST REVISE.** Rev1 correctly closes MR-1 through MR-3. The characterization cases are now honestly pre-edit GREEN, the pinned analyzer is the executable RED, the three exact case vectors are frozen, and the separately registered `subprocess` row plus `--no-tests=error` and `BIVHARNESS_REQUIRE_CLANG_TIDY=ON` guards make row presence and analyzer execution falsifiable.

One new load-bearing sequence defect remains. S2 builds the macOS subprocess target before S4. S3 configures and builds the Linux tree before S4. S4 then changes `src/core/support/subprocess.cpp`, but every S5 command is `ctest`; there is no post-edit build on either host. CTest executes registered test commands. It does not compile changed sources first. Therefore the S5 `subprocess` rows can execute the pre-edit binaries built in S2/S3 and report GREEN without exercising either pointer conversion or `buffer{}`. The later macOS named selection has the same stale-binary problem.

No implementation token may parent to this review.

## 2. Prior findings closed and production shape approved in principle

Rev1's three corrections are accepted:

```text
MR-1  CLOSED  three behavior cases run pre-edit as characterization GREEN; analyzer is RED
MR-2  CLOSED  exact scripts, caps, retained bytes, flag, exit, and IO expectations frozen
MR-3  CLOSED  subprocess row named on both hosts and analyzer row named on Linux
```

The rev1 additions are also sound: `--no-tests=error` separates a real focused row from a zero-match success, and `-DBIVHARNESS_REQUIRE_CLANG_TIDY=ON` prevents an unavailable analyzer from becoming a non-failing SKIP. Requiring the analyzer to report execution over 29 of 29 sources is the correct positive observation.

The two-path change and chosen source shape remain approved in principle: pointer-held non-null sinks initialized from the constructor references, monotonic OR into the one shared flag, per-instance caps unchanged, no pointer arithmetic, no return-path transfer, no `reserve`, and restoration of `std::array<char, 8192> buffer{}`.

## 3. Must-fix MR-4 — rebuild after the production edit

The locked sequence currently says:

```text
S2  build macOS target at old production bytes
S3  configure and build Linux tree at old production bytes
S4  edit src/core/support/subprocess.cpp
S5  run CTest rows only
```

That ordering proves neither post-edit runtime behavior nor post-edit linkage. Revise S5 so compilation is explicit after S4 and before any GREEN claim:

```text
macOS, after S4
  cmake --build --preset ci-macos --target biv_subprocess_tests
  ctest --preset ci-macos -R '^subprocess$' --no-tests=error --output-on-failure
  cmake --build --preset ci-macos
  ctest --preset ci-macos \
    -R '^(biv_tests|harness-selftest|harness-e2|errno_table_gate|generated_envelope_conforms)$' \
    --no-tests=error --output-on-failure

Linux, after fixed bytes are materialized as required by MR-5
  cmake --preset ci -DBIVHARNESS_REQUIRE_CLANG_TIDY=ON
  cmake --build --preset ci
  ctest --preset ci -R '^subprocess$' --no-tests=error --output-on-failure
  ctest --preset ci -R '^safety-tidy-analyzer$' --no-tests=error --output-on-failure
```

An equivalent plan may use one full post-edit macOS build before both macOS rows. The load-bearing predicate is that each post-edit CTest row runs an executable built from the fixed production bytes, not from the pre-edit characterization state. Keep explicit exit-status capture without a pipe.

Adding `--no-tests=error` to the named macOS selection makes its own presence requirement explicit too; its five-name expression should not silently succeed if the wrong build tree or preset contains none of those rows.

## 4. Must-fix MR-5 — materialize and bind the fixed bytes in Linux

The local Linux charter requires a disposable container while preserving the host worktree. Rev1 does not state how the S3 pre-edit source tree receives the S4 host edit. If S3 used a copied or archived source tree, reusing that tree in S5 leaves it at the old bytes. In that case the Linux runtime row is stale and the source-reading analyzer can also repeat the pre-edit RED rather than assess the fix. A post-edit build alone is insufficient if it rebuilds a stale copy.

Revise the sequence to require, after S4:

1. Materialize the exact fixed worktree bytes into a fresh disposable Ubuntu 24.04 `linux/amd64` tree, or explicitly refresh the existing disposable tree from those exact bytes.
2. Record the SHA-256 of `src/core/support/subprocess.cpp` on the host and inside the container and require equality before configure/build.
3. Configure with pinned clang-tidy 22 and `-DBIVHARNESS_REQUIRE_CLANG_TIDY=ON`, build under the non-root user with the chartered nofile soft-to-hard lift, then run the focused runtime and analyzer rows.
4. Record the post-edit build command, source-hash equality, exact row counts, analyzer execution over 29 of 29 sources, and every exit status.

A fresh fixed-byte tree is preferred because it makes the pre-edit RED tree and post-edit GREEN tree distinct evidence objects. A correctly refreshed or read-only-bound tree is acceptable if the plan states the transport and proves exact-byte equality before the build.

## 5. Required revision and held scope

Retain rev1's test vectors, production shape, two-path scope, characterization-first ordering, exact three-finding analyzer RED, absence guards, and accepted residual handling. Add only the missing post-edit build and fixed-byte Linux transport/provenance requirements above.

The bounded paths remain:

```text
src/core/support/subprocess.cpp  pointer-held sinks and buffer{} only
tests/test_subprocess.cpp        three exact characterization cases only
```

No header, `probe.cpp`, CMake, workflow, harness, sealed, schema, or cross-lane path is needed. T2/T3/T4 and the `compare.py` composition remain held. Count-gate shape remains routed and Linux `nonzero_exit` remains owed on the eventual fixed T1 head.

## 6. Disposition

Planner should file a narrow rev2 that preserves every closed rev1 decision and inserts explicit post-S4 builds on both hosts plus exact fixed-byte materialization and source-hash equality in the disposable Linux environment. A successor Implementer review can then approve, after which the pair Planner may issue the bounded implementation token parented to that approval.

No source, test, harness, workflow, candidate ref, PR, remote CI, Docker resource, or remote state was changed by this review. Merge is not push is not release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: read-only SHA-256, Git-blob, commit, exact-file, CMake target-registration, candidate-source, worktree-status, and live INDEX EOF inspection. No source/test/workflow/ref/worktree/PR/remote mutation. Docs-lane delta is this review relay plus one live-EOF INDEX row only; all pre-existing untracked sibling artifacts are preserved unchanged and unclaimed.
FINAL_GIT_STATUS_SHORT: this review relay and its appended INDEX row are this seat's only new delta; all pre-existing untracked sibling and prior Implementer artifacts remain preserved and unclaimed

CARRY LIST (D-8.5):
- VERDICT MUST REVISE at PLAN commit `8157424d6f36de6dfb4754b96268e49927c720fa`, blob `3fa640a9fc83955b0384a765611b5b4352309de6`, SHA-256 `bbb9d2af282bba8fcf2044f3d9dc05b3adff84187a7e8faa865f396c084ec929`; no implementation token may parent to this review.
- MR-1 through MR-3 are CLOSED; the exact vectors, characterization/analyzer ordering, focused rows, `--no-tests=error`, required clang-tidy, 29-of-29 execution observation, production shape, and two-path scope carry forward.
- MR-4: S2/S3 build before S4, while S5 only invokes CTest. Require explicit post-edit builds before all post-edit runtime GREEN claims.
- MR-5: a disposable Linux copy created before S4 can remain stale. Require post-edit fixed-byte materialization, host/container `subprocess.cpp` SHA-256 equality, then configure/build and focused rows.
- Add `--no-tests=error --output-on-failure` to the named macOS selection so the selection itself cannot pass on zero matches.
- Preserve explicit exit statuses with no pipe; report `harness-selftest` separately under `201613`; T2-T4 and comparator work held; count gate routed; Linux `nonzero_exit` owed; schema fenced; release hold ABSOLUTE.
