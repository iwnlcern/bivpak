## SITREP — the one requested Ubuntu 24.04/amd64 implementation-base control is complete: base `36968e5b` is RED at 2 failed / 997 passed / 3 skipped, not the landed 3 / 1007 / 3, and the exact failure set differs (one common, one base-only, two landed-only); therefore the executed discriminator is a FINDING, not candidate-neutral attribution; no retry, repair, reset, or governed byte

ROLE: Pair Implementer
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: intg-isolation-plan-7
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: intg-isolation/SITREP-pair-planner-20260903-004437.md
RELATED_CONTEXT: intg-isolation/IMPL-pair-implementer-20260903-002131.md; intg-isolation/IMPL-pair-planner-20260902-205130.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-isolation-20260902.md; ../../pdc/master/RESIDUALS.md; intg-substep1/IMPL-pair-implementer-20260828-184407.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — this is the exact report-only discriminator return requested by `004437`; acceptance/attribution remains with master and m-3/m-4, and any repair requires fresh governed authority; release hold ABSOLUTE
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: m3-e2-store-isolation-20260901
DESIGN_OWNER: m-3
DESIGN_LOCK_ID: m3-e2-store-isolation-20260901 @ sha256 637ef197aa9f2ebb8f9a34ab91558d52ae35a71691a8403290a87ad59a84bca6
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: intg-isolation-plan-20260902 @ sha256 9eb01448a9f05520847ca1d27de652a399d660a0911d2ccd6f32f71d4242c124
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: master.master-planner, master.master-reviewer, m-3.planner, m-3.implementer, m-4.planner
SUBJECT: SITREP RETURN — one base control at 36968e5 completed under the same Linux topology; base 2/997/3 and landed 3/1007/3 have different exact failing sets, so `004437`'s discriminator result is FINDING; no interpretation beyond differs, no repeat, no repair, landed 85f9c4d6 frozen

## Executed control and receipt

Exactly one control run was executed. A disposable external clone's local `main` was set to the exact implementation base without moving the primary repository's ref. It was mounted read-only as `/repo-ro`; Phase T cloned its `main` into `/work` and produced the required receipt:

```text
clone receipt: 36968e5b338fa654e90e6f9c82568bf7d37f487a expected: 36968e5b338fa654e90e6f9c82568bf7d37f487a
```

The instrument otherwise matched the landed run: disposable Ubuntu 24.04, `--platform linux/amd64`, `--init`, uid/gid 1001, read-only `/repo-ro` and `/assets`, isolated writable `/work` and `/mnt/c`, the same eight SHA-validated frozen LLVM 22 packages, clang-tidy major 22, and non-root `nofile soft=hard=1048576` at venv/configure/build/CTest. The measurement was exactly:

```text
ctest --preset ci -R "harness-selftest" --output-junit /work/ctest-base-control.xml --output-on-failure
```

No `harness-e2` was added; it was optional. No repeat sampling or retry occurred.

Ledger:

```text
base_provision=0
deb_provision=0
transition=0
fixture=0
venv=0
configure=0
build=0
ctest=8
aggregate=1
```

## Exact base versus landed result

Base at `36968e5b338fa654e90e6f9c82568bf7d37f487a`:

```text
================== 2 failed, 997 passed, 3 skipped in 20.05s ===================
FAILED selftest/test_e3_asserts.py::test_c1_zero_session_control_reds_on_file_inserted_at_scandir_stop
FAILED selftest/test_e3_asserts.py::test_credential_scanner_detects_entry_added_after_directory_enumeration
```

Landed at `85f9c4d6065cf6de66d2dd1f94752dbecfd92bbc`, carried verbatim from `002131`'s retained one-run transcript:

```text
================== 3 failed, 1007 passed, 3 skipped in 23.20s ==================
FAILED selftest/test_e3_asserts.py::test_file_reader_rejects_same_size_cross_chunk_in_place_rewrite
FAILED selftest/test_e3_asserts.py::test_run_e3_session_inserted_at_scandir_stop_reds_c1_before_open
FAILED selftest/test_e3_asserts.py::test_credential_scanner_detects_entry_added_after_directory_enumeration
```

Mechanical set comparison:

```text
COMMON (1)
selftest/test_e3_asserts.py::test_credential_scanner_detects_entry_added_after_directory_enumeration

BASE-ONLY (1)
selftest/test_e3_asserts.py::test_c1_zero_session_control_reds_on_file_inserted_at_scandir_stop

LANDED-ONLY (2)
selftest/test_e3_asserts.py::test_file_reader_rejects_same_size_cross_chunk_in_place_rewrite
selftest/test_e3_asserts.py::test_run_e3_session_inserted_at_scandir_stop_reds_c1_before_open
```

RESULT: different count and different exact set. Under `004437`'s own rule this is a FINDING. No further interpretation, attribution, diagnosis, flake claim, repair proposal, or acceptance claim is made at this seat.

## Evidence

Machine-local evidence remains outside the repository:

```text
/private/var/folders/hq/f0qq8v_103q9y8prfn20rzx80000gn/T/isolation-evidence-Blva9E
```

Hashes:

```text
2cf99d70cc9b681debf1d55a627c5d1b556b9a887f91f1277f9d3e59baf9fce2  base-control-container.log
15560462585bfd20cdac8822b8c735c0d3226617aa3ea9aab4e7182d3e8ba460  base-control-ctest.log
533d155f733bb5aef40204d3086c7ecb3d3fe38c94b5062141658764de9e8474  ctest-base-control.xml
7a3d2e73b7a2e5d27aa67ae878ab73cfb6cb8e48c1dc91080daba93641a5d646  linux-ctest.log (landed comparator)
```

The evidence-side `linux-base-control.sh` and disposable source clone are untracked, outside the primary repository, and retained for audit. The Docker container was removed by its own `--rm` lifecycle. Primary `main` remained at `21705f74221c52d994cbb7657518bedf54af085a` throughout the measurement; the landed implementation commit `85f9c4d6` remains frozen beneath it.

## Explicit NOT DONE

- No second run, repeat sampling, harness-e2 control, or retry.
- No product, harness, test, schema, CMake, workflow, relay-engine, or inherited S4 byte changed by the measurement.
- No repair, second implementation commit, amend, reset, ref move in the primary repository, or alteration of landed `85f9c4d6`.
- No candidate-neutral attribution, root-cause determination, m-3/m-4 disposition, countgate action, merge, push, PR, remote CI, publication, deployment, seal, or release.

Please route the differing set/count finding to master and m-3/m-4 exactly as requested. Any next product/harness action needs fresh addressed authority.

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: no — no credential value or credential-bearing store was read
- migration/backfill/destructive-write/canonical-data-repair: no — disposable external build only
- money/inventory/orders/planning/accounting/trust-critical-state: no
- AI-or-automation-acts-downstream: no
- worker/scheduler/queue/retry/async-side-effect: no — one run, no retry
- cross-repo/service-contract/generated-schema/shared-API-event: yes — R-4.35 attribution and m-3/m-4 acceptance are cross-owner governance inputs
- user-visible-control-with-materializer/downstream-consumer: no — report-only measurement, no product action
- test-runtime-role-mismatch: yes — the base and landed Linux runtime failure sets/counts differ
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: yes — attribution and any acceptance of the differing runtime evidence remain owner-routed
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: none
- scan_presented_to_operator: no
- operator_reply_after_scan: none
- valid_waiver: no
WAIVED_RISK_ACCEPTANCE: none

ACTIONS_GIT_REF: one read-only Linux measurement against disposable external clone `main@36968e5b338fa654e90e6f9c82568bf7d37f487a`; evidence hashes above; primary repository remained `main@21705f74221c52d994cbb7657518bedf54af085a` with no measurement-induced byte or ref change; this report is the only docs-lane action through the intg daemon; no repair/reset/second implementation commit/merge/push/PR/remote CI/publication/deployment/seal/release
RELAY_LINT: exact-file pre-lint, then engine-rendered submission; rendered exact-file lint, SHA-256, INDEX/daemon state, `relay verify`, and post-filing status are checked before handoff
FINAL_GIT_STATUS_SHORT:
35 inherited S4-only rows, direct-stream SHA-256 `aee3eac8aa0a74221c8a386b27ef04a081284e89fafbb8e1d57f2a26632925f5`; no intg, harness, product, schema, CMake, or workflow dirt before this daemon submission
