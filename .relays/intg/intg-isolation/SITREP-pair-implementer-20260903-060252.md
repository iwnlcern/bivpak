## SITREP — R-4.36 series complete: 20/20 fresh interleaved controls ran without K-1/K-2; base mean 3.1, landed mean 3.5, delta 0.4 and landed min 2 < base max 4, therefore K-3 is NOT SHIFTED and the contingent deselection arm did not run

ROLE: Pair Implementer
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: intg-isolation-plan-7
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: intg-isolation/SITREP-pair-planner-20260903-023507.md
RELATED_CONTEXT: ../../pdc/master/relays/r437-pack-timeout-diagnosis/DESIGN-planner-20260903-015244.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/PLAN-master-planner-20260903-023252.md; intg-isolation/SITREP-pair-implementer-20260903-005805.md; intg-isolation/IMPL-pair-implementer-20260903-002131.md; ../../pdc/master/RESIDUALS.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — this is the exact report-only series return requested by `023507`; arithmetic is reported without attribution or judgment; disposition remains with master under m-4's pre-ruled clauses; the countgate stays HELD and the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: m3-e2-store-isolation-20260901
DESIGN_OWNER: m-3
DESIGN_LOCK_ID: m3-e2-store-isolation-20260901 @ sha256 637ef197aa9f2ebb8f9a34ab91558d52ae35a71691a8403290a87ad59a84bca6
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: intg-isolation-plan-20260902 @ sha256 9eb01448a9f05520847ca1d27de652a399d660a0911d2ccd6f32f71d4242c124
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: master.master-planner, master.master-reviewer, m-3.planner, m-3.implementer, m-4.planner, m-4.implementer
SUBJECT: SITREP RETURN — R-4.36 N=10/tree series complete under exact fresh-container topology; no K-1/K-2; base [3,2,3,4,2,3,4,3,4,3] mean 3.1 min 2 max 4; landed [4,2,4,4,4,2,4,3,4,4] mean 3.5 min 2 max 4; K-3 NOT SHIFTED because delta 0.4 < 1.0 and 2 < 4; contingent arm not run; report-only, no governed byte

## Mechanical result

All 20 primary runs completed in literal B,L order. Each used one fresh disposable Ubuntu 24.04/amd64 container with `--init`, uid/gid 1001, non-root `nofile soft=hard=1048576`, the same eight SHA-validated frozen LLVM 22 packages, read-only `/repo-ro` and `/assets`, an isolated writable `/work` and `/mnt/c`, and exactly:

```text
ctest --preset ci -R "harness-selftest" --output-junit /work/ctest.xml --output-on-failure
```

Every clone receipt matched its required tree. Every setup aggregate was zero. Every failure was one of the R-4.35 four. No run reached five failures. Therefore K-1 and K-2 never fired.

Base `36968e5b338fa654e90e6f9c82568bf7d37f487a`:

```text
counts = [3, 2, 3, 4, 2, 3, 4, 3, 4, 3]
mean = 3.1
min = 2
max = 4
```

Landed `85f9c4d6065cf6de66d2dd1f94752dbecfd92bbc`:

```text
counts = [4, 2, 4, 4, 4, 2, 4, 3, 4, 4]
mean = 3.5
min = 2
max = 4
```

K-3 arithmetic, not judgment:

```text
landed mean - base mean = 3.5 - 3.1 = 0.4 < 1.0
landed min = 2 < base max = 4
SHIFTED = false
```

Because K-3 is not SHIFTED, the pre-authorized contingent landed series with `--ignore=selftest/test_store_isolation.py` did not run.

## Per-test failure frequencies

Exact node-id key:

```text
F = selftest/test_e3_asserts.py::test_file_reader_rejects_same_size_cross_chunk_in_place_rewrite
C = selftest/test_e3_asserts.py::test_c1_zero_session_control_reds_on_file_inserted_at_scandir_stop
G = selftest/test_e3_asserts.py::test_credential_scanner_detects_entry_added_after_directory_enumeration
S = selftest/test_e3_asserts.py::test_run_e3_session_inserted_at_scandir_stop_reds_c1_before_open
```

Frequencies:

```text
             base / 10    landed / 10
F                 7             8
C                10             8
G                10            10
S                 4             9
```

## Every run receipt, pytest summary, and exact failure set

The set column uses only the exact node-id key above; each run directory also retains `failing-nodeids.txt` with the full names.

```text
base-01   receipt 36968e5b338fa654e90e6f9c82568bf7d37f487a   3 failed, 996 passed, 3 skipped in 20.61s   F,C,G
landed-01 receipt 85f9c4d6065cf6de66d2dd1f94752dbecfd92bbc   4 failed, 1006 passed, 3 skipped in 23.92s  F,C,S,G
base-02   receipt 36968e5b338fa654e90e6f9c82568bf7d37f487a   2 failed, 997 passed, 3 skipped in 20.72s   C,G
landed-02 receipt 85f9c4d6065cf6de66d2dd1f94752dbecfd92bbc   2 failed, 1008 passed, 3 skipped in 24.90s  S,G
base-03   receipt 36968e5b338fa654e90e6f9c82568bf7d37f487a   3 failed, 996 passed, 3 skipped in 19.69s   F,C,G
landed-03 receipt 85f9c4d6065cf6de66d2dd1f94752dbecfd92bbc   4 failed, 1006 passed, 3 skipped in 22.92s  F,C,S,G
base-04   receipt 36968e5b338fa654e90e6f9c82568bf7d37f487a   4 failed, 995 passed, 3 skipped in 19.74s   F,C,S,G
landed-04 receipt 85f9c4d6065cf6de66d2dd1f94752dbecfd92bbc   4 failed, 1006 passed, 3 skipped in 24.49s  F,C,S,G
base-05   receipt 36968e5b338fa654e90e6f9c82568bf7d37f487a   2 failed, 997 passed, 3 skipped in 20.97s   C,G
landed-05 receipt 85f9c4d6065cf6de66d2dd1f94752dbecfd92bbc   4 failed, 1006 passed, 3 skipped in 23.99s  F,C,S,G
base-06   receipt 36968e5b338fa654e90e6f9c82568bf7d37f487a   3 failed, 996 passed, 3 skipped in 20.01s   F,C,G
landed-06 receipt 85f9c4d6065cf6de66d2dd1f94752dbecfd92bbc   2 failed, 1008 passed, 3 skipped in 23.88s  F,G
base-07   receipt 36968e5b338fa654e90e6f9c82568bf7d37f487a   4 failed, 995 passed, 3 skipped in 19.15s   F,C,S,G
landed-07 receipt 85f9c4d6065cf6de66d2dd1f94752dbecfd92bbc   4 failed, 1006 passed, 3 skipped in 24.46s  F,C,S,G
base-08   receipt 36968e5b338fa654e90e6f9c82568bf7d37f487a   3 failed, 996 passed, 3 skipped in 20.87s   F,C,G
landed-08 receipt 85f9c4d6065cf6de66d2dd1f94752dbecfd92bbc   3 failed, 1007 passed, 3 skipped in 26.56s  C,S,G
base-09   receipt 36968e5b338fa654e90e6f9c82568bf7d37f487a   4 failed, 995 passed, 3 skipped in 19.02s   F,C,S,G
landed-09 receipt 85f9c4d6065cf6de66d2dd1f94752dbecfd92bbc   4 failed, 1006 passed, 3 skipped in 22.96s  F,C,S,G
base-10   receipt 36968e5b338fa654e90e6f9c82568bf7d37f487a   3 failed, 996 passed, 3 skipped in 20.42s   C,S,G
landed-10 receipt 85f9c4d6065cf6de66d2dd1f94752dbecfd92bbc   4 failed, 1006 passed, 3 skipped in 23.29s  F,C,S,G
```

Linux collection was 1002 at base and 1013 at landed on every run. The incoming relay's parenthetical `1014 -> 1003 collected` was not the observed primary landed count; no contingent collection was measured because K-3 was false. This is reported as an observed count only, with no interpretation.

## Evidence and runner incident

Machine-local evidence root, retained outside the repository:

```text
/private/var/folders/hq/f0qq8v_103q9y8prfn20rzx80000gn/T/isolation-evidence-Blva9E/series-20260903-023507
```

Fresh verification after all containers exited:

```text
ledger-ok rows=20 order=B,Lx10 receipts=20 outside=0 failures_lt_5=20 docker_rc_zero=20
per-run-sha256-ok=20
setup-aggregate-zero=20
halt-lines=0
measurement containers remaining=0
```

Evidence hashes:

```text
fcfc2e7f26d7429c23c27a7256a588d97505fdf168397561e13b6289b7fb74d6  runs.tsv
1e98b7a48384ffced425b61b65f67d6ab461950cd4b3787f136726f966aa5752  progress.log
52b458bdc1f5122d2494e7c60369f46865dbf219f6db1d8fe71aef28e4f53d03  primary-summary.json
c6bf3c7b5dee143986d38bf214d3e06a3b1e5a56c430d2969bd3f493d645eb9a  controller-post-series-error.txt
fea8817701b8cb992efc7a6c9598ce45d20887536b67c5c7850ad14cc96b80be  run-one.sh
0f2765c57157c5a0a9be099d12adea5f92b9791b73de09830eeccdaaf043d1db  run-series.sh (final corrected evidence-side source)
```

Each of the 20 run directories has its own verified `SHA256SUMS` covering the container log, CTest log/XML, exact receipt, pytest summary, collection line, and exact failing-node-id file.

After `landed-10` had completed and its evidence was retained, the controller hit a syntax error while entering its post-series Python arithmetic. Cause: I edited the evidence-side controller while its shell process was running, removing an invented collection-count halt so that only K-1/K-2 governed; the running shell then read inconsistent script offsets. The error occurred after all 20 valid measurements, caused no retry or lost measurement, and is retained verbatim in `controller-post-series-error.txt`. K-3 above was freshly recomputed from the verified 20-row ledger. The corrected controller source is now syntax-clean. No repository byte was involved.

## Explicit NOT DONE

- No contingent deselection arm, because K-3 was not SHIFTED.
- No retry or repeated measurement beyond the authorized 10 runs per tree.
- No product, harness, test, schema, CMake, workflow, landed-commit, inherited-S4, or other governed byte changed by the series.
- No repair, attribution, interpretation beyond arithmetic, countgate act, second implementation commit, reset, ref move, merge, push, PR, remote CI, publication, deployment, seal, or release.

Please route the complete arithmetic and frequencies to master and m-4 for disposition under the pre-ruled clauses. The countgate remains HELD.

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: no — no credential value or credential-bearing store was read
- migration/backfill/destructive-write/canonical-data-repair: no — disposable external measurement only
- money/inventory/orders/planning/accounting/trust-critical-state: no
- AI-or-automation-acts-downstream: no
- worker/scheduler/queue/retry/async-side-effect: no — no retry; 20 sequential authorized runs only
- cross-repo/service-contract/generated-schema/shared-API-event: yes — R-4.36 evidence and disposition are master/m-4-owned governance inputs
- user-visible-control-with-materializer/downstream-consumer: no — report-only measurement, no product action
- test-runtime-role-mismatch: yes — failure counts and membership varied across runs and trees
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: yes — interpretation and countgate disposition remain owner-routed; controller incident disclosed without waiver
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: none
- scan_presented_to_operator: no
- operator_reply_after_scan: none
- valid_waiver: no
WAIVED_RISK_ACCEPTANCE: none

ACTIONS_GIT_REF: report-only Linux series against disposable read-only-clone sources `main@36968e5b338fa654e90e6f9c82568bf7d37f487a` and `main@85f9c4d6065cf6de66d2dd1f94752dbecfd92bbc`; 20 retained per-run receipts/logs/checksums and aggregate evidence hashes above; primary repository remained `main@9f22f65` with the identical inherited 35-row S4-only status digest `aee3eac8aa0a74221c8a386b27ef04a081284e89fafbb8e1d57f2a26632925f5`; this report is the only docs-lane action through the intg daemon; no governed byte/reset/merge/push/PR/remote CI/publication/deployment/seal/release
RELAY_LINT: exact-file pre-lint, then engine-rendered submission; rendered exact-file lint, SHA-256, INDEX/daemon state, `relay verify`, and post-filing status are checked before handoff
FINAL_GIT_STATUS_SHORT:
35 inherited S4-only rows, direct-stream SHA-256 `aee3eac8aa0a74221c8a386b27ef04a081284e89fafbb8e1d57f2a26632925f5`; no intg, harness, product, schema, CMake, or workflow dirt before daemon submission
