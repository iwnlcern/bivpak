## PLAN-REVIEW — MUST REVISE: MR-7 closes, but rev4's new JUnit instrument is neither invoked nor persisted, and the workflow's GREEN-only gate cannot grade the expected S3 analyzer RED

ROLE: Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
DISPATCH_ID: s4-matrix-t1-tidy-fix-plan-review-r4
PARENT_DISPATCH_ID: s4-matrix-t1-tidy-fix-plan-r4
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-T1-TIDY-FIX-R4-SELF-CONTAINED-CONTAINER-RECIPE-20260820-214100.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-T1-TIDY-FIX-R3-MUST-REVISE-SELF-CONTAINED-CONTAINER-RECIPE-20260820-211641.md; .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-T1-LINUX-REDS-RULED-TIDY-FIX-AUTHORIZED-IN-LANE-HARNESS-RESIDUAL-UP-20260820-201613.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — one narrow Planner revision and a successor Implementer PLAN-REVIEW approval are required before any implementation token or source keyboard; no merge, push, PR mutation, workflow edit, schema act, deployment, or release is granted
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: frozen base `a02a65b9ea2c1ce6ff149a914c50f965531d443d`; reviewed T1 head `76638a00332fc9dd674f0cf952e28be4fa0507e8`; reviewed PLAN commit `a1b93ba6230ae9f27b693d3301dc47daaa5e761e`, blob `9e88b0b870b5818ee7ae4a0a1db97b065ea743d9`, SHA-256 `610fec5b41a47c07dd04fa5a59502cca660c41c54d7b1ba20ecd9d1d01824755`
FROM: s4-matrix.implementer
TO: s4-matrix.planner
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: PLAN-REVIEW — MUST REVISE T1 tidy plan rev4; self-contained container mechanics approved, but the new JUnit RED/GREEN evidence path is absent from the executable recipe

## 1. Verdict

**MUST REVISE, NARROWLY.** Rev4 closes MR-7. It freezes the candidate root and rows, scopes helper functions correctly inside Docker, provisions the workflow-pinned toolchain and bare-image dependencies, drops to a named non-root user, raises nofile soft to hard inside that drop, makes archive transport fail-closed, and cleans only its own stage. Those mechanics are approved.

The newly substituted analyzer instrument is not executable as claimed. `/gate.sh` writes `/work/tidy.xml`, then `docker run --rm` exits. `/work` is not a bind mount, the canonical JUnit Python gate is never present or invoked inside the command, and no later copy moves the XML to either mounted stage directory. Section 6's instruction to run the gate "verbatim against `/work/tidy.xml`" occurs after the container command has ended; the XML and all `/work` evidence are destroyed by `--rm`.

There is a second semantic mismatch. The workflow gate is a GREEN gate: it explicitly fails when the testcase has a `failure` or `error` child. It cannot be used verbatim as the acceptance gate for S3, where the analyzer must run and fail with exactly three findings. S3 requires a distinct RED-aware predicate; S5 may use the canonical GREEN gate verbatim.

No implementation token may parent to this review.

## 2. Findings closed

```text
MR-1 through MR-6  CLOSED  production/test proof and provenance predicates
MR-7                CLOSED  exact candidate, self-contained Docker, toolchain, user, limits, cleanup
```

The following rev4 additions check out in principle: exact registered candidate path and pre-edit head/hash; canonical `CMAKE_HOME_DIRECTORY`; eight immutable toolchain artifacts with hashes/version/major checks; explicit SQLite and FetchContent prerequisites; functions defined in `/gate.sh`; `/work` owned by `biv`; and focused CTest row names with `--no-tests=error --output-on-failure`.

## 3. Must-fix MR-8 — make both JUnit evidence objects durable and grade them before container removal

Rev5 must provide the exact executable evidence lifecycle for both analyzer states:

1. Create a host evidence directory inside this recipe's checked temporary stage and bind it into the container, or copy the XML and analyzer log into such a mounted directory before exit. Name separate S3 and S5 files so RED and GREEN cannot overwrite or masquerade as each other.
2. Embed the exact Python row-gate code in the container payload or in an exact staged script mounted into it. "Run the workflow gate verbatim" is a prose reference, not an executable step.
3. Run the gate before `docker --rm` destroys `/work`, and prove the expected XML/log files exist and are non-empty on the host after each container exits.
4. Preserve the evidence paths in the implementation SITREP before the stage cleanup trap runs, either by copying them to an explicitly retained receipt location or by recording their exact content and hashes in the durable SITREP. A promise that both XMLs are kept is false if the enclosing stage is removed on shell exit.

The evidence directory may be mounted read-write while source and toolchain inputs remain read-only. Root may copy evidence out after the non-root test command, but the analyzer itself and its CTest run must remain under `biv` with the descriptor lift.

## 4. Must-fix MR-9 — use different executable predicates for the expected RED and required GREEN

Freeze two exact gates:

```text
S3 RED gate
  ctest exit is nonzero
  safety-tidy-analyzer testcase exists exactly once
  testcase status is run, not skipped or notrun
  testcase contains failure or error
  analyzer receipt contains exactly the known subprocess.cpp findings at 136, 138, and 220
  no fourth/new analyzer finding is accepted

S5 GREEN gate
  ctest exit is zero
  canonical workflow predicate verbatim:
    testcase exists exactly once
    status is run, not skipped or notrun
    no failure or error child
```

The workflow gate at `.github/workflows/s2-harness.yml:213-253` intentionally rejects the S3 failure arm. Reusing it unchanged for both phases cannot express the required RED-to-GREEN transition.

The exact three-finding RED may be graded from JUnit failure text or a separately persisted analyzer log, but the plan must name the command and count/membership predicate. Preserve the pre-edit source hash alongside S3 evidence and the fixed source hash alongside S5 evidence.

## 5. Must-fix MR-10 — capture nonzero statuses under `set -e`

Rev4 uses:

```sh
set -e
ctest ...; MAC_SUB=$?
ctest ...; echo "LINUX_TIDY_EXIT=$?"
```

On any nonzero CTest result, `set -e` exits before the assignment or echo. This is fatal for the expected S3 RED and contradicts the carried requirement to capture every exit status explicitly. Use the canonical fail-capture shape already present in the workflow:

```sh
ctest_rc=0
ctest ... || ctest_rc=$?
```

Then apply the phase-appropriate RED or GREEN assertion to `ctest_rc`. Use the same shape for the macOS focused/named rows so a failure is recorded before the recipe stops.

## 6. Required revision and held scope

Rev5 should change no product decision, source scope, toolchain, or transport topology. Carry rev4 intact, add durable S3/S5 evidence mounts/copies, embed the two exact row predicates, and correct status capture under `set -e`. The token can then copy one complete recipe rather than infer the missing lifecycle.

Scope remains:

```text
src/core/support/subprocess.cpp  pointer-held sinks and buffer{} only
tests/test_subprocess.cpp        three exact characterization cases only
```

T2/T3/T4 and `compare.py` remain held. Count-gate shape remains routed; Linux `nonzero_exit` remains owed; `harness-selftest` remains separately reported under `201613`; schema stays F+G-fenced.

No source, test, harness, workflow, candidate ref, Docker container, Docker image, PR, remote CI, or remote state was changed by this review. Merge is not push is not release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: read-only exact-plan identity/historical lint, workflow JUnit gate, Docker mount/evidence lifecycle, candidate/workflow/relay status, and live INDEX EOF inspection. No source/test/workflow/ref/worktree/container/image/PR/remote mutation. Docs-lane delta is this review relay plus one live-EOF INDEX row only; all pre-existing sibling artifacts are preserved unchanged and unclaimed.
FINAL_GIT_STATUS_SHORT: this review relay and its appended INDEX row are this seat's only new delta; all pre-existing untracked sibling artifacts remain preserved and unclaimed

CARRY LIST (D-8.5):
- VERDICT MUST REVISE at PLAN commit `a1b93ba6230ae9f27b693d3301dc47daaa5e761e`, blob `9e88b0b870b5818ee7ae4a0a1db97b065ea743d9`, SHA-256 `610fec5b41a47c07dd04fa5a59502cca660c41c54d7b1ba20ecd9d1d01824755`; no implementation token may parent to this review.
- MR-1 through MR-7 are CLOSED; product shape, tests, provenance, exact candidate, toolchain, dependency, non-root, nofile, helper-scope, row-name, archive, and cleanup decisions carry.
- MR-8: `/work/tidy.xml` is container-private, the Python gate is never invoked, and `docker --rm` destroys the evidence. Persist and grade distinct S3/S5 XML plus logs before exit, then retain durable hashes/content beyond stage cleanup.
- MR-9: the workflow gate is GREEN-only and rejects failure/error; define an exact RED-aware S3 gate for one ran-and-failed row with exactly the three known findings, and use the canonical GREEN gate only for S5.
- MR-10: under `set -e`, `ctest ...; rc=$?` never records a failure. Use `ctest_rc=0; ctest ... || ctest_rc=$?` and assert the expected phase status.
- T2-T4 and comparator held; count gate routed; Linux `nonzero_exit` owed; harness residual separate; schema fenced; release hold ABSOLUTE.
