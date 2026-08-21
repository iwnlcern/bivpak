## PLAN-REVIEW — MUST REVISE: MR-4 and MR-5 close, but rev2's only claimed fixed-byte provenance gate still contains an unresolved command placeholder and does not bind the hashed source root to the macOS CMake tree

ROLE: Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
DISPATCH_ID: s4-matrix-t1-tidy-fix-plan-review-r2
PARENT_DISPATCH_ID: s4-matrix-t1-tidy-fix-plan-r2
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-T1-TIDY-FIX-R2-POSTEDIT-BUILDS-AND-FIXED-BYTE-BINDING-20260820-204713.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-T1-TIDY-FIX-R1-MUST-REVISE-REBUILD-FIXED-BYTES-20260820-204036.md; .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-T1-LINUX-REDS-RULED-TIDY-FIX-AUTHORIZED-IN-LANE-HARNESS-RESIDUAL-UP-20260820-201613.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — one narrow Planner revision and a successor Implementer PLAN-REVIEW approval are required before any implementation token or source keyboard; no merge, push, PR mutation, workflow edit, schema act, deployment, or release is granted
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: frozen base `a02a65b9ea2c1ce6ff149a914c50f965531d443d`; reviewed T1 head `76638a00332fc9dd674f0cf952e28be4fa0507e8`; reviewed PLAN commit `78ffedf2317c6ba08644fd75adf0ea13e4254c58`, blob `a51ff99f6d8f48e915d62aa2ff6e3449c11b3491`, SHA-256 `19b0b46c41fca7f9c34f65ee71d22ad84d5feed8b0594e1bc25faa03e1e9e545`
FROM: s4-matrix.implementer
TO: s4-matrix.planner
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: PLAN-REVIEW — MUST REVISE T1 tidy plan rev2; post-edit builds and fresh Linux materialization close, but the sole source-provenance gate is not yet executable or source-root bound

## 1. Verdict

**MUST REVISE, NARROWLY.** Rev2 closes MR-4 and MR-5. It now requires post-S4 builds on both hosts, a distinct fixed-byte Linux evidence tree, exact focused rows, the named-selection absence guard, host/container hash equality, and recorded transport/build/row/analyzer evidence. Everything carried from rev1 remains approved in principle.

The remaining defect is in rev2's load-bearing addition itself. Section 5 says this is "the only step in the plan that actually binds the fixed bytes", but its command is not executable:

```text
TREE_HASH=$(<same command inside the tree about to be built>)
```

The Linux transport remains a choice among a fresh copy, refresh, or read-only bind, with no selected command or exact in-container source path. On macOS, `HOST_HASH` hashes a cwd-relative path while `TREE_HASH` is unresolved; the plan never proves that `build/ci-macos/CMakeCache.txt` names the same canonical source root that was hashed. A comparison cannot bind an evidence object until both producers and both exact objects are named.

No implementation token may parent to this review.

## 2. Findings closed

```text
MR-1 through MR-3  CLOSED  characterization/analyzer ordering, vectors, and exact rows
MR-4             CLOSED  explicit post-edit builds precede post-edit CTest rows
MR-5             CLOSED  post-edit Linux evidence uses fixed bytes distinct from the RED tree
named-row guard  CLOSED  no-tests-error and output-on-failure applied uniformly
```

The production shape and two-path scope remain approved: pointer-held sinks initialized from valid references, unchanged per-stream cap arithmetic and monotonic shared OR, no pointer arithmetic or return-path transfer, no `reserve`, and exact `buffer{}` restoration; three exact characterization cases in `tests/test_subprocess.cpp` only.

## 3. Must-fix MR-6 — replace the placeholder with one exact fail-closed provenance recipe

Rev3 must select one Linux materialization mechanism and spell the commands completely. It must name:

1. The canonical fixed candidate source root on the host.
2. The exact fresh post-edit container/source-tree destination and transport command.
3. The exact host hash producer and exact tree hash producer, each with its own checked exit status and regular-file check before output parsing.
4. The explicit non-empty, non-empty-file-digest, and equality assertions already intended by rev2.
5. The exact source root consumed by each build.

For macOS, bind `build/ci-macos` to the hashed root by reading `CMAKE_HOME_DIRECTORY:INTERNAL` from its `CMakeCache.txt`, canonicalizing it, and requiring equality with the canonical candidate root before the post-edit build. Then hash `subprocess.cpp` through that cache-bound source root. Comparing the same cwd-relative path to itself would be tautological and is not provenance.

For Linux, choose the fresh-copy path or one explicitly equivalent transport; do not leave the Implementer to choose among three evidence topologies inside the implementation token. The container-side hash must be obtained from the exact path that the subsequent `cmake --preset ci` consumes, before configure/build, and compared to a host hash computed outside the container from the fixed candidate root.

The commands may use `shasum -a 256`, but each `shasum` must succeed directly before its digest is accepted. Do not rely on a pipeline's exit status: without `pipefail`, `shasum ... | cut ...` exits with `cut`'s status even when `shasum` failed. The subsequent non-empty assertion currently fails closed, but a direct producer-status check makes the stated gate and its receipt truthful.

## 4. Factual correction to carry

Rev2 says the empty-file digest is "exactly what `shasum` prints when it hashed a path that does not exist" and that two missing files therefore compare as that digest. Direct checks with the command as written show otherwise:

```text
shasum -a 256 /definitely/not/a/path | cut -d' ' -f1
  stderr  shasum: ... No such file or directory
  stdout  empty
  pipeline exit 0 without pipefail
```

The existing `test -n` rejects that empty stdout, so this incorrect explanation does not turn the gate fail-open. The `e3b0c442...` refusal instead rejects an existing zero-byte file. Preserve both protections, correct their stated roles, and check each hash producer directly as MR-6 requires.

## 5. Required revision and held scope

Rev3 should change no product decision. It should carry rev2 verbatim except for replacing the provenance placeholder and transport alternatives with one exact executable recipe and correcting the missing-path explanation. The analyzer GREEN remains the semantic discriminator that the intended source repair exists; the provenance gate establishes that the source assessed and built is the fixed candidate tree.

Scope remains:

```text
src/core/support/subprocess.cpp  pointer-held sinks and buffer{} only
tests/test_subprocess.cpp        three exact characterization cases only
```

T2/T3/T4 and `compare.py` remain held. Count-gate shape remains routed; Linux `nonzero_exit` remains owed on the eventual fixed head; `harness-selftest` remains separately reported under `201613`; schema stays F+G-fenced.

No source, test, harness, workflow, candidate ref, Docker resource, PR, remote CI, or remote state was changed by this review. Merge is not push is not release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: read-only exact-plan identity/lint, CMake preset/cache, candidate-worktree, shell hash-failure semantics, live INDEX EOF, and repository-status inspection. No source/test/workflow/ref/worktree/PR/remote mutation. Docs-lane delta is this review relay plus one live-EOF INDEX row only; all pre-existing sibling artifacts are preserved unchanged and unclaimed.
FINAL_GIT_STATUS_SHORT: this review relay and its appended INDEX row are this seat's only new delta; all pre-existing untracked sibling artifacts remain preserved and unclaimed

CARRY LIST (D-8.5):
- VERDICT MUST REVISE at PLAN commit `78ffedf2317c6ba08644fd75adf0ea13e4254c58`, blob `a51ff99f6d8f48e915d62aa2ff6e3449c11b3491`, SHA-256 `19b0b46c41fca7f9c34f65ee71d22ad84d5feed8b0594e1bc25faa03e1e9e545`; no implementation token may parent to this review.
- MR-1 through MR-5 and the named-selection guard are CLOSED; production shape, exact vectors, sequence, rows, builds, fresh Linux evidence object, analyzer observations, and two-path scope carry forward.
- MR-6: replace `TREE_HASH=$(<same command inside the tree about to be built>)` and the transport alternatives with one exact executable, fail-closed host-to-build-tree provenance recipe.
- macOS must bind the hashed source root to `build/ci-macos` via canonical `CMAKE_HOME_DIRECTORY`; Linux must hash the exact transported path consumed by configure/build and compare it to an independently produced host hash.
- Correct the factual record: a missing path yields empty stdout through the written pipeline, rejected by `test -n`; `e3b0c442...` identifies an existing zero-byte file. Check each hash producer's status directly.
- T2-T4 and comparator held; count gate routed; Linux `nonzero_exit` owed; harness residual separate; schema fenced; release hold ABSOLUTE.
