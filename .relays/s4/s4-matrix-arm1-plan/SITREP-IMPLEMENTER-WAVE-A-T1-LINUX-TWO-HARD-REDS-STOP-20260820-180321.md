## SITREP — Wave-A T1 reconstructed at local corrected bytes; macOS obligations green; Ubuntu 24.04 amd64 full suite has two hard reds in harness-selftest and safety-tidy-analyzer; STOP before T2-T4

ROLE: Implementer
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-matrix-wave-a-t1-linux-two-hard-reds-stop
PARENT_DISPATCH_ID: s4-matrix-wave-a-three-cells-ruled
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-WAVE-A-THREE-CELLS-RULED-CANDIDATE-LOCAL-INDEX-UNION-COMPARE-TEST-OBLIGATION-20260820-163957.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/SITREP-PLANNER-WAVE-A-T1-STAGE2-MACOS-GREEN-COUNT-GATE-SHAPE-ROUTED-20260820-174238.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — the Planner and Orchestrator must route the two observed Linux non-count reds before this stack advances; no T2, T3, T4, panel, count-readiness, merge, push, PR mutation, publication, schema, deployment, or release act is granted
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: frozen dispatch reconstruction base `a02a65b9ea2c1ce6ff149a914c50f965531d443d`; original corrected T1 `d691f9be89093c27f9b518cfd7dbbdccceacba2e`; reconstructed local head `76638a00332fc9dd674f0cf952e28be4fa0507e8`
FROM: s4-matrix.implementer
TO: s4-matrix.planner, s4.orchestrator-planner
CC: operator, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer, m-1.planner, m-3.planner, m-2.planner
SUBJECT: SITREP — Wave-A T1 Stage-2 STOP; local corrected candidate reconstructed with lossless INDEX union and macOS green, but Ubuntu full CTest fails harness-selftest plus clang-tidy; T2-T4 not started

The `163957` dispatch's STOP rule fires at T1. This filing adds the local Linux evidence to the Planner's primary macOS/count-shape route at `174238`; it does not compete with or rewrite that route. The proof below is bound to reconstructed local head `76638a00332fc9dd674f0cf952e28be4fa0507e8` on frozen base `a02a65b9ea2c1ce6ff149a914c50f965531d443d`.

## 1. Reconstruction and ruled INDEX union

The six commits from corrected local T1 `d691f9be89093c27f9b518cfd7dbbdccceacba2e` were replayed in order onto the frozen dispatch base. The sole conflict was `.relays/s4/INDEX.md`; no product, test, workflow, or other docs path conflicted.

The ruled union retained both complete streams:

```text
main_lines=524
candidate_lines=117
rebuilt_lines=525
main_missing=0
candidate_missing=0
```

The final diff is exactly the original T1 scope plus the one authorized INDEX union. `git diff --check a02a65b9ea2c1ce6ff149a914c50f965531d443d..76638a00332fc9dd674f0cf952e28be4fa0507e8` exits zero and the T1 worktree is clean. No other ref or worktree moved.

## 2. macOS Stage-2 rows are green

The valid isolated HOME was `/Users/jack/Library/Caches/biv-wave-a-t1-home`, with `CODEX_HOME` and `CLAUDE_CONFIG_DIR` unset. The workflow-equivalent named CTest selection passed all six registered rows. The explicit `probe` and `subprocess` CTest selection passed both rows.

Observed Catch2 cells, kept per target rather than borrowed across targets:

```text
biv_tests        successes=385 failures=0 expectedFailures=0 skips=3
biv_probe_tests  successes=25  failures=0 expectedFailures=0 skips=0
```

The 25 probe cases are the exact cases moved from `biv_tests` into the separately registered `biv_probe_tests`; the union has the same 413 unique case identities and per-case assertion counts as the frozen base. Thus the single-binary `410/0/0/3` workflow check remains a routed gate-shape defect, not a missing-test finding.

All six required portability filters were non-empty. Their combined run passed 81 cases with 79 passed, 2 expected WSL skips, and 4,076 passing assertions. The direct invalid-ELF test passed on macOS and observed `ProbeOutcome::spawn_error`.

## 3. Ubuntu 24.04 amd64 full-suite hard stop

The Linux leg used a disposable `ubuntu:24.04` container with `--platform linux/amd64`, a copied disposable source tree, pinned clang-tidy `22.1.8`, a non-root `runuser`, and the required descriptor lift:

```text
nofile_soft=1048576
nofile_hard=1048576
configure=PASS
build=PASS
full registered CTest: 15 passed, 2 failed, 2 expected skips
```

The first hard red is `harness-selftest`: `4 failed, 967 passed, 3 skipped`. Exact failed tests and observations:

1. `test_file_reader_rejects_same_size_cross_chunk_in_place_rewrite` observed `CredentialStatus.OK`, not `SOURCE_UNREADABLE`.
2. `test_c1_zero_session_control_reds_on_file_inserted_at_scandir_stop` lacked the required C1 evidence.
3. `test_run_e3_session_inserted_at_scandir_stop_reds_c1_before_open` observed `['pack', 'open']`, not `['pack']`.
4. `test_credential_scanner_detects_entry_added_after_directory_enumeration` returned false rather than detecting the inserted entry.

The second hard red is `safety-tidy-analyzer`. It executed and covered 29 of 29 sources, then failed on `src/core/support/subprocess.cpp`:

```text
line 136  reference data member bytes_
line 138  reference data member output_incomplete_
line 220  uninitialized std::array<char, 8192> buffer
JUnit row gate: failed status='fail'
```

These are non-count failures. Per the controlling STOP rule, the already-started full CTest was allowed to finish for its row evidence, but no separate Linux Catch2 XML/count command and no direct Linux invalid-ELF command ran afterward. The Linux `nonzero_exit` contract remains unclaimed.

## 4. Disposition

STOP before T2. T2, T3, and T4 were not reconstructed; the test-obligated `compare.py` composition was not started; no panel, condition-3 review, Stage-4 readiness cell, or Stage-5 merge-readiness claim was produced.

The Planner and Orchestrator must route both Linux reds and the already-routed single-binary count-gate shape before re-verification resumes. The later Arm-II supersession-comment assignment is outside this filing and was not acted on. The Arm-1 schema act remains F+G-fenced and untouched. No GitHub Actions run, remote CI, push, PR mutation, merge, publication, deployment, or release occurred; the release hold is ABSOLUTE.

Evidence is retained under `.superpowers/sdd/PLAN-ORCHESTRATOR-PLANNER-WAVE-A-THREE-CELLS-RULED-CANDIDATE-LOCAL-INDEX-UNION-COMPARE-TEST-OBLIGATION-20260820-163957/`, including `task-1-report.md` and the exact macOS/Linux logs and XML named there.

ACTIONS_GIT_REF: locally replayed the six-commit corrected T1 range onto frozen base `a02a65b9ea2c1ce6ff149a914c50f965531d443d`, producing `76638a00332fc9dd674f0cf952e28be4fa0507e8`; resolved the sole INDEX conflict by the ruled lossless append-only union; configured, built, and tested locally on macOS and in one disposable Ubuntu 24.04 amd64 container; no remote or external mutation. Docs-lane delta is this relay plus one live-EOF INDEX row only; all sibling-authored shared-checkout state is preserved and unclaimed.
FINAL_GIT_STATUS_SHORT: candidate T1 worktree clean; shared main carries this relay and INDEX row plus pre-existing sibling-authored untracked paths, preserved and unclaimed

CARRY LIST (D-8.5):
- T1 local corrected bytes reconstructed as `76638a00332fc9dd674f0cf952e28be4fa0507e8` on frozen base `a02a65b9ea2c1ce6ff149a914c50f965531d443d`; sole conflict INDEX; both tails retained with zero missing lines.
- macOS named suite, probe/subprocess rows, per-target Catch2 executions, portability filters, and invalid-ELF `spawn_error` are green.
- The single-binary count comparison is still structurally stale because the candidate deliberately registers 25 probe cases in `biv_probe_tests`; no case is missing.
- Ubuntu 24.04 amd64 configure/build pass, but `harness-selftest` has four E3 TOCTOU assertion failures and `safety-tidy-analyzer` has three `subprocess.cpp` findings; both are hard reds.
- STOP before T2-T4; no comparator composition, panels, readiness, remote CI, PR mutation, merge, schema, deployment, or release; release hold ABSOLUTE.
