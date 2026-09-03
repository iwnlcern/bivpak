## IMPL RETURN — store isolation landed at `85f9c4d6065cf6de66d2dd1f94752dbecfd92bbc`; macOS and both E2 witnesses are GREEN, but Ubuntu 24.04/amd64 is RED on three existing E3 selftests, so sha plus red return UP as a FINDING with no repair, reset, or acceptance claim

ROLE: Pair Implementer
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: intg-isolation-impl-return
PARENT_DISPATCH_ID: intg-isolation-impl
IN_REPLY_TO: intg-isolation/IMPL-pair-planner-20260902-205130.md
RELATED_CONTEXT: intg-isolation/PLAN-pair-planner-20260902-194515.md; intg-isolation/PLAN-REVIEW-pair-implementer-20260902-200322.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-isolation-20260902.md; ../../pdc/master/domains/m-3-restore-cli/design/2026-09-01-e2-store-isolation-r437.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/DESIGN-REVIEW-implementer-20260902-162639.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/DESIGN-REVIEW-master-reviewer-20260902-164129.md; ../../pdc/master/relays/r437-operator-scope-ruling/PLAN-operator-20260902-173858.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/PLAN-master-planner-20260902-173859.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — Task 3 Step 7 is RED at the landed sha; m-3/master must adjudicate the three Linux failures in the existing E3 selftest surface and return any repair through a new plan/review/token; this report neither un-lands the authorized harness commit nor claims acceptance; no second implementation commit, reset, amend, countgate act, merge, push, PR, remote CI, publication, deployment, seal, or release is authorized; release hold ABSOLUTE
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: m3-e2-store-isolation-20260901
DESIGN_OWNER: m-3
DESIGN_LOCK_ID: m3-e2-store-isolation-20260901 @ sha256 637ef197aa9f2ebb8f9a34ab91558d52ae35a71691a8403290a87ad59a84bca6
DESIGN_RECORD_KIND: design-doc
TARGET_DESIGN_COMMIT: a07d84cee5687efb05912567fa58387e61b93317
PLAN_LOCK_ID: intg-isolation-plan-20260902 @ sha256 9eb01448a9f05520847ca1d27de652a399d660a0911d2ccd6f32f71d4242c124
BASE: local main implementation base `36968e5b338fa654e90e6f9c82568bf7d37f487a`, captured before any write
BRANCH: none — the one harness commit landed directly on local unpublished main at `85f9c4d6065cf6de66d2dd1f94752dbecfd92bbc`; no merge, push, or PR
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: master.master-planner, master.master-reviewer, operator, m-3.planner, m-3.implementer, m-2.planner
SUBJECT: IMPL RETURN / STOP FINDING — route landed sha `85f9c4d6065cf6de66d2dd1f94752dbecfd92bbc` and retained Ubuntu red to master/m-3; exact four-path isolation change has targeted/macOS/E2/mutant evidence below, but Linux harness-selftest has 3 existing E3 failures while harness-e2 and store-isolation-witness pass; no repair or acceptance inferred

## Outcome and stop point

Rev6 ran in literal order. Task 0 preceded every byte; Tasks 1-2 were test-first; Task 3 Steps 1-6 completed, including THE GUARD adjacent to THE ONE COMMIT. Step 7 used disposable Ubuntu 24.04 under `--platform linux/amd64` and `--init`, a read-only clone receipt at the exact landed sha, and non-root `nofile` soft raised to hard.

Linux aggregate returned 1 solely because CTest returned 8: `harness-selftest` had three failures in pre-existing `harness/selftest/test_e3_asserts.py`; `harness-e2` and the new witness passed. The sealed red rule therefore stopped execution: no implementation byte, second commit, amendment, reset, rerun, or repair followed. The landing stays frozen; this is Step 8 UP, not acceptance.

## Landed sha and fences

```text
IMPL_BASE=36968e5b338fa654e90e6f9c82568bf7d37f487a
LANDED=85f9c4d6065cf6de66d2dd1f94752dbecfd92bbc
HEAD at final audit=85f9c4d6065cf6de66d2dd1f94752dbecfd92bbc
LANDED parent=36968e5b338fa654e90e6f9c82568bf7d37f487a

M  harness/bivharness/scenario.py
A  harness/scenarios/store-isolation-witness.json
M  harness/selftest/stub_biv.py
A  harness/selftest/test_store_isolation.py
```

Step 4 found zero `<` status-delta rows and exactly those four `>` porcelain rows; no command intervened before stage/commit. Post-commit status equals the Task-0 snapshot. Final audit: 35 inherited S4-only rows, direct-stream SHA-256 `aee3eac8aa0a74221c8a386b27ef04a081284e89fafbb8e1d57f2a26632925f5`; not staged or altered. `git diff-tree --check LANDED^ LANDED` is clean.

The landed fence re-proved: no `src/`, `schemas/`, CMake, `.github/`, `e3.py`, or existing-scenario byte; `scenario.py` remains `24:COMMAND_TIMEOUT_S = 30`; e3 remains 120 and byte-equal to base; production changed-line timeout count 0; no isolation/mutant knob; adapter locator census exactly `CLAUDE_CONFIG_DIR`, `CODEX_HOME`, `CODEX_SQLITE_HOME`; complete five-name `HERMETIC_LOCATORS`; exactly seven `NAMED MUTANT:` markers.

Machine-local evidence root outside the repository:

```text
/private/var/folders/hq/f0qq8v_103q9y8prfn20rzx80000gn/T/isolation-evidence-Blva9E

09df89ae60ca9ab85afe288290ab9cb14056aca7c038168c21a3f9e03edf469a  precommit-fence.log
ff22a387249625ec27eecc9a260821b2e36b26a974d216764eabcde52997e5b6  precommit-guard-and-commit.log
e75732ea0e2811de9034a09f5d64dae7d022309a622abfde830feb16d8d869b5  landed-fence.log
d0b539d3125d4f7eeabeeedf3dae4717ed0f54a7b6835f7ca44d1854e2390f66  rp-mutants.log
cd83cb9ca7bf66f76e22b8a3132ef2d5f594bb008067c8286f9267368574f1cb  linux-container.log
7a3d2e73b7a2e5d27aa67ae878ab73cfb6cb8e48c1dc91080daba93641a5d646  linux-ctest.log
```

## Evidence partition — newly measured

- Test-first RED: 11 collected, failing on absent isolation interfaces; `pytest-red.log` retained. Targeted final: 11 passed in 1.18s.
- Whole macOS selftest under standing value-free `env -u ANTHROPIC_API_KEY`: 1014 passed in 11.91s. No value was read, printed, or retained. Raw ambient run retained honestly RED (119 failed, 895 passed) because E3 rejected the ambient name; it is not substituted for controlled evidence.
- macOS CTest under the same value-free environment: harness-selftest 12.00s, harness-e2 1.44s, 2/2 passed, 13.44s total. Witness is `runnable_passed`, status pass.
- macOS timings, all pass: open-deny-default 0.237220s; open-store-locked 0.162150s; open-unknown-agent 0.013029s; witness 0.221795s.
- Linux transport validated eight frozen LLVM 22 assets. Container: Ubuntu 24.04 amd64, `--init`, read-only `/repo-ro`, isolated writable `/work` and `/mnt/c`, uid/gid 1001, `nofile soft=hard=1048576`; clone exact LANDED; clang-tidy LLVM major 22; configure/build zero.

Linux ledger and result:

```text
base_provision=0
deb_provision=0
transition=0
fixture=0
venv=0
configure=0
build=0
ctest=8
report=0
timing=0
aggregate=1

harness-selftest: FAILED, 3 failed / 1007 passed / 3 skipped in 23.20s
harness-e2: PASSED in 1.21s
CTest aggregate: 1 of 2 passed; rc 8
```

Exact existing E3 failures:

```text
test_file_reader_rejects_same_size_cross_chunk_in_place_rewrite
  expected CredentialStatus.SOURCE_UNREADABLE; received CredentialStatus.OK
test_run_e3_session_inserted_at_scandir_stop_reds_c1_before_open
  expected seen == ["pack"]; received ["pack", "open"]
test_credential_scanner_detects_entry_added_after_directory_enumeration
  expected scanner.scan_tree(tmp_path, set()) truthy; received False
```

No root-cause, baseline, or waiver claim: commit edits none of `e3.py`, `host2_credentials.py`, `test_e3_asserts.py`; diagnosis/repair is a fresh act. Linux E2 still lists all 12 runnable rows passed, including witness classes A/B/C/E/K, empty detail/warnings. Linux timings, all pass: open-deny-default 0.105325s; open-store-locked 0.083236s; open-unknown-agent 0.073737s; witness 0.110485s.

## Evidence partition — carried

- Design rev5 pin `637ef197aa9f2ebb8f9a34ab91558d52ae35a71691a8403290a87ad59a84bca6` at `a07d84cee5687efb05912567fa58387e61b93317`, operator amendment, and master carry.
- Plan rev6 pin `9eb01448a9f05520847ca1d27de652a399d660a0911d2ccd6f32f71d4242c124`, exact-hash approval, and addressed IMPL grant.
- Product/harness pin proof against `46df8f3` rc 0 before implementation; no product byte.
- Task-0 35-row snapshot, empty index, four paths clean, two new paths absent, and implementation base.

## Evidence partition — registered, not cited as green

- R-4.35-family registered rows remain retained and do not waive/replace the direct Linux measurement.
- First Docker stdin transport produced no measurement or receipt; canonical script run above is the sole cited Linux measurement.
- First macOS timing exposed `/var` vs `/private/var` aliasing; evidence root normalized before credited timings; no shipped-byte change.
- First evidence-only mutant driver resolved the relative binary against scenario cwd; driver alone changed to absolute paths before the single credited four-arm campaign; no shipped driver/knob.

## Evidence partition — green gates inside stopped aggregate

- Preflight, RED, targeted GREEN, pre-commit fence, adjacent guard, one-commit fence, landed fence complete.
- Seven markers: four iso·1 locator, one TMPDIR iso·2, one adapter census iso·3(a), one budget iso·4.
- Controlled whole macOS selftest and both macOS CTest targets passed.
- Real-product witness passed macOS and Linux; `_rp_positive` credited exact staged codex/Claude identities and provenance before no-poison oracle.
- Four restore-to-poison demonstrations returned status fail with leak-tags exactly their restored locator. SQLite arm emitted exactly one `CodexDbEnrichmentSkipped` at poisoned `state_5.sqlite`, no positive-missing line.
- Linux provisioning/transition/fixture/venv/configure/build/report/timing zero and harness-e2 passed. None overrides aggregate red.

## Real-binary mutant transcript

Full verbatim transcript: `rp-mutants.log`, SHA-256 above. Exact result-bearing lines reproduced verbatim:

```text
MUTANT HOME: status=fail leak_tags=['HOME']
isolation-leak HOME: warnings[1] kind=SessionLiveAtPack path=0d15ea5e-0001-4000-8000-00000000c0de
isolation-leak HOME: agents[codex].image_session_id=0d15ea5e-0001-4000-8000-00000000c0de
MUTANT CODEX_HOME: status=fail leak_tags=['CODEX_HOME']
isolation-positive missing: codex staged session 019faaaa-bbbb-7ccc-8ddd-eeeeeeee0001 appears 0 times in agent_sessions (expected 1)
isolation-leak CODEX_HOME: warnings[0] kind=SessionLiveAtPack path=0d15ea5e-0003-4000-8000-000000c0de40
isolation-leak CODEX_HOME: agents[codex].store_root=/private/var/folders/hq/f0qq8v_103q9y8prfn20rzx80000gn/T/isolation-evidence-Blva9E/rp-mutants/mutant-CODEX_HOME/store-isolation-witness.poison/codex-home
isolation-leak CODEX_HOME: agents[codex].image_session_id=0d15ea5e-0003-4000-8000-000000c0de40
MUTANT CODEX_SQLITE_HOME: status=fail leak_tags=['CODEX_SQLITE_HOME']
isolation-leak CODEX_SQLITE_HOME: warnings[0] kind=CodexDbEnrichmentSkipped path=/private/var/folders/hq/f0qq8v_103q9y8prfn20rzx80000gn/T/isolation-evidence-Blva9E/rp-mutants/mutant-CODEX_SQLITE_HOME/store-isolation-witness.poison/codex-sqlite/state_5.sqlite
MUTANT CLAUDE_CONFIG_DIR: status=fail leak_tags=['CLAUDE_CONFIG_DIR']
isolation-positive missing: claude-code staged session aaaaaaaa-1111-4000-8000-000000000001 appears 0 times in agent_sessions (expected 1)
isolation-leak CLAUDE_CONFIG_DIR: agents[claude-code].store_root=/private/var/folders/hq/f0qq8v_103q9y8prfn20rzx80000gn/T/isolation-evidence-Blva9E/rp-mutants/mutant-CLAUDE_CONFIG_DIR/store-isolation-witness.poison/claude-config
isolation-leak CLAUDE_CONFIG_DIR: agents[claude-code].image_session_id=0d15ea5e-0004-4000-8000-0000c1a0dec0
ALL FOUR MUTANTS RED ON EXACTLY THEIR OWN LOCATOR
```

HOME also had two 2000ms probe timeouts and consequent session-row-missing detail after independent HOME leaks; retained verbatim, not hidden or counted as another locator tag. Campaign was not retried after credited four arms; m-3 may veto L2/L3 or require successor measurement.

## Latitude for m-3 veto

- L1 ruled: conditional selftest-stub discovery echo is faithful at pinned precedence and inert when unset.
- L2 stated: overlay once in `run_scenario`; named profiles override; final command env has five names; fail-closed guard before every command.
- L3 stated: shared poison builder; real-product scenario poisons inherited environment around body; positive binds staged identity/provenance; oracle reads product evidence; four demonstrations evidence-only.

No m-3 acceptance inferred. Linux aggregate red and HOME supplementary timeouts are presented for review/veto.

SCOPE_DIFF (dispatched allowlist versus landed commit):
- harness/bivharness/scenario.py -> in
- harness/selftest/stub_biv.py -> in
- harness/selftest/test_store_isolation.py -> in
- harness/scenarios/store-isolation-witness.json -> in
SCOPE_DIFF_RESULT: all-in
ROW_TRUTH_CHECK: required
SCOPE_ROW_EVIDENCE:
- harness/bivharness/scenario.py: overlay, guard, poison/context, positive/oracle and execution integration; budget unchanged
- harness/selftest/stub_biv.py: faithful conditional discovery model/echo
- harness/selftest/test_store_isolation.py: four legs, seven markers, positive/mutants
- harness/scenarios/store-isolation-witness.json: one new real-product isolation-staging spec

## Explicit NOT DONE / held

- No calibration, timeout, E3, product, CMake, existing scenario, schema, workflow, or generated byte.
- No claim Linux E3 is fixed, baseline, or waived; no post-red repair, second harness commit, amend, reset.
- No m-3 acceptance, countgate, E4, merge, push, PR, remote CI, publication, deployment, seal, release.
- No deletion/staging/ownership claim over inherited S4 state.

Route sha plus Linux finding through master to m-3. Any repair requires successor sealed plan, fresh exact-byte review, fresh addressed IMPL token. This seat stops.

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: yes — value-free removal of ambient `ANTHROPIC_API_KEY` name for controlled local test only; value never read/printed/retained
- migration/backfill/destructive-write/canonical-data-repair: no
- money/inventory/orders/planning/accounting/trust-critical-state: no
- AI-or-automation-acts-downstream: no
- worker/scheduler/queue/retry/async-side-effect: no — credited mutants not retried; no-measurement transport separately disclosed
- cross-repo/service-contract/generated-schema/shared-API-event: yes — design/acceptance m-3/PDC-owned; Linux red routes via master
- user-visible-control-with-materializer/downstream-consumer: yes — harness executes real pack/open; product/release held
- test-runtime-role-mismatch: yes — macOS green; Linux E2 green; Linux aggregate red on three existing E3 selftests
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: yes — Linux E3 adjudication and HOME supplementary probe timeouts owner-routed
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: none
- scan_presented_to_operator: no
- operator_reply_after_scan: none
- valid_waiver: no
WAIVED_RISK_ACCEPTANCE: none

ACTIONS_GIT_REF: implementation commit `85f9c4d6065cf6de66d2dd1f94752dbecfd92bbc` directly on local unpublished main, sole parent `36968e5b338fa654e90e6f9c82568bf7d37f487a`, exactly four SCOPE_DIFF paths; this STOP/FINDING report only subsequent intg docs action via daemon; no second harness commit/reset/merge/push/PR/remote CI/publication/deployment/seal/release
RELAY_LINT: exact-file pre-lint then engine-rendered submission; rendered exact-file lint, SHA-256, INDEX/daemon state and `relay verify` checked after filing; no structural-green claim substitutes for Linux red
FINAL_GIT_STATUS_SHORT:
35 inherited S4-only rows, direct-stream SHA-256 `aee3eac8aa0a74221c8a386b27ef04a081284e89fafbb8e1d57f2a26632925f5`; byte-equal Task-0 snapshot; no intg dirt before daemon submission
