## IMPL REPORT — TASK-5 REV12 RERUN EXECUTED AT FROZEN 3cd31e4: `openssh-client` CLOSES THE `repo_engine` BLOCKER; R-4.35 AND R-4.38 REMAIN RETAINED REDS; NOT VERIFICATION-COMPLETE OR MERGE-READY

ROLE: Pair Implementer
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: intg-substep1-impl-3
PARENT_DISPATCH_ID: intg-substep1-impl-3
IN_REPLY_TO: intg-substep1/IMPL-pair-planner-20260828-175521.md
RELATED_CONTEXT: intg-substep1/PLAN-REVIEW-pair-implementer-20260828-173854.md; intg-substep1/PLAN-pair-planner-20260828-153816.md; intg-substep1/IMPL-pair-implementer-20260828-152108.md; intg-substep1/SITREP-pair-planner-20260828-153827.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep1-20260827.md; ../../../pdc/master/relays/intg-stop1-a6-golden-bytes/DESIGN-planner-20260827-235912.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — the approved battery remains nonzero on the registered R-4.35 and R-4.38 rows; their named owners/governing adjudication control any readiness transition, while merge, publication, deployment, and release remain separately held and the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: intg-consent-fabric-plan
DESIGN_LOCK_ID: m3-addendum-6-c41d015f-lock-20260825
DESIGN_RECORD_KIND: design-doc
SECOND_CONSUMED_LOCK: m3-addendum-7-4c40fe37-lock-20260827
PLAN_LOCK_ID: intg-substep1-plan-20260827 @ sha256 403b3c95bdce875be5a0111a82b47d91168b2aa53964364166309c0403e4b9b4
BASE: main@02b51435a5b50363df7f595dd827af107424b0c3
BRANCH: intg/consent-fabric@3cd31e4823d40c1c9ea020fcb51917618368533b — unchanged and clean after verification
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: master.master-planner, master.master-reviewer, m-3.implementer
SUBJECT: RETURN intg-substep1-impl-3 — the rev12 dependency delta works and `repo_engine` is green; retain R-4.35 at 3 failed/996 passed/3 skipped and R-4.38 at 399/0/0/1; candidate A6 evidence and fences are green, but the aggregate remains red and no verification-complete or merge-ready claim exists

## Disposition

**TASK-5 REV12 RERUN EXECUTED; REV12 DELTA GREEN; OVERALL BLOCKED; NOT VERIFICATION-COMPLETE; NOT MERGE-READY.**

The exact approved plan digest and frozen candidate were consumed without amendment. No product, test, schema, harness, CMake, workflow, plan, or sealed byte changed. The candidate worktree remains clean at `3cd31e4823d40c1c9ea020fcb51917618368533b`.

PR: none — no push, PR, merge, publication, deployment, seal, or release authority exists in this dispatch.

Files changed by this execution: none in the product checkout. Writable battery outputs existed only under `/work` in the disposable container; the host asset directory was outside the repository and contained only the eight authenticated assets, manifest/checksum material, and the battery script.

## Newly measured Phase-H-through-S receipts

### Phase H — authenticated host boundary

The manifest was derived from candidate `3cd31e4` workflow lines 130-139. All eight `toolchain-mirror-clang-tidy-22-immutable-v1` assets downloaded into a fresh `mktemp -d` directory outside the worktree. Derived `SHA256SUMS` passed `sha256sum --check --strict`; the `.deb` count was exactly eight. The host GitHub credential never entered a container, output, report, or repository file. No remote CI ran.

### Phase R — root provision in the frozen container topology

The container was `ubuntu:24.04`, `linux/amd64`, with `--init`; `/repo-ro`, `/llvm22-mirror`, and `/run-battery.sh` were read-only mounts. The exact frozen base command, now including `openssh-client`, ran unamended.

All eight package metadata rows matched package name, the exact version `1:22.1.8~++20260613092238+e80beda6e255-1~exp1~20260613092253.78`, and `amd64`; every installed version matched; `clang-tidy-22 --version` reported Ubuntu LLVM 22.1.8.

### Phase T — identity and immutable-source transition

Root created gid/uid 1001 before clone and ownership. The clone came from the read-only main repository bind, not the linked worktree, and produced:

```text
expected_head=3cd31e4823d40c1c9ea020fcb51917618368533b
observed_head=3cd31e4823d40c1c9ea020fcb51917618368533b
runuser -u suite -- test -w /mnt/c/tmp  rc=0
```

### Phase S — non-root measurement and retained ledger

The one `runuser` suite context raised its soft `nofile` from 1024 to the inherited hard 1048576 before the harness venv, configure, build, or tests. The locked harness requirements installed before configure. The required no-short-circuit ledger is:

```text
base-provision=0
deb-provision=0
transition=0
fixture=0
nofile=0
harness-venv=0
configure=0
build=0
ctest=8
tidy-row-gate=0
a6-fabric-success=0
catch2-xml=0
count-read=1
linux_battery_aggregate_rc=1
container_suite_rc=1
```

CTest accounted all 19 rows: 16 passed, two expected topology skips, and one failed row. `repo_engine` passed in 26.36 seconds, proving the rev12 `openssh-client` delta closed the prior real-Git `/usr/bin/ssh -G` blocker. `harness-e2`, `safety-build-werror`, `safety-tidy-analyzer`, and `safety-hardening` passed; the tidy XML row gate independently observed exactly one executed, passing row with `status='run'`.

The named `[a6-fabric] --success` execution passed all 127 assertions in all 12 cases. Catch2 XML generation passed.

## Re-measured fence transcript

```text
engine_refs_rc=1                 expected/no matches outside src/core/repo
engine_include_rc=1              expected/no product include of core/repo/
repos_fence_rc=0                 require_empty_array at manifest.cpp:117,971
persistence_tokens_rc=1          expected/no getenv|setenv|ofstream|fopen|config
isatty_count=2                   exact token count
predicate_conjunction_rc=0       exact stdin-TTY AND stderr-TTY expression
stdout_json_rc=1                 expected/no STDOUT_FILENO or json term
engine_diff_command_rc=0         BASE..HEAD src/core/repo output empty
changed_path_count=18            exact plan/dispatch fence
fence_aggregate_rc=0
```

The four candidate commits retain author `intg.pair-implementer`; the second commit remains the same-commit contract landing. The exact eighteen changed paths equal the dispatch SCOPE_DIFF and contain no engine path.

## Carried-forward accepted evidence

Per the dispatch, the accepted macOS receipt from `intg-substep1/IMPL-pair-implementer-20260828-152108.md` carries without rerun because the candidate head and product bytes are unchanged. It retains the raw full-CTest environment/tool observations (`credential-env:ANTHROPIC_API_KEY` and `readelf unavailable`) while its candidate-specific gates remain: `biv_tests` pass, `harness-e2` pass, `[a6-fabric]` 127 assertions / 12 cases pass, and `harness/selftest/test_envelope.py` 6 pass. Those carried observations are not relabeled as newly measured or erased.

The STOP-1 byte ownership remains m-3 ruling `intg-stop1-a6-golden-bytes/DESIGN-planner-20260827-235912.md`: PROMPT D ends with one trailing space and no newline; pack refusal detail begins `pack refused:` with no leading indent. The Linux named run freshly re-proved those golden tests.

## Registered residuals — retained, not converted to green

### R-4.35 mutation-adversary family

`harness-selftest` returned rc nonzero with `3 failed, 996 passed, 3 skipped`. All three failures are the registered mutation-during-read/enumeration adversary family and are attributed to no candidate byte:

```text
test_file_reader_rejects_same_size_cross_chunk_in_place_rewrite
test_c1_zero_session_control_reds_on_file_inserted_at_scandir_stop
test_credential_scanner_detects_entry_added_after_directory_enumeration
```

The changed member/count relative to the prior `4 failed, 995 passed, 3 skipped` observation is consistent with the registered flaky family; it is not a waiver and does not turn the rc green. Correctness ownership remains R-4.36/m-4 as routed.

### R-4.38 Catch2 count gate

The count gate retained rc 1:

```text
expected successes/failures/expectedFailures/skips = 412/0/0/1
observed successes/failures/expectedFailures/skips = 399/0/0/1
```

The observed tuple is unchanged from impl-2 and matches the already reconciled registered probe-split arithmetic `412 - 25 + 12 = 399` in Planner SITREP `153827`. That arithmetic explains the observation; it does not satisfy the frozen workflow gate and is never merge-readiness evidence.

## Actual green gates and leg census

- Phase H asset integrity/count; Phase R base and eight-package provisioning; Phase T exact-head clone and suite-identity fixture; Phase S nofile/venv/configure/build: green.
- `repo_engine`: green; the prior frozen-package blocker is closed.
- Tidy execution row, Linux ELF hardening, harness E2, product test binary, A6 named slice, and Catch2 XML generation: green.
- a6.14: one named case / 14 assertions; a6.15: one / 13; a6.17: three exact Python structural nodes carried and Linux selftest observed them before the unrelated R-4.35 row failure; a6.18: one / 30 with pack/list/info witnessed; a6.16 zero half: all six envelope selftests carried green and the Linux selftest reached them green.
- Fences: green at the exact candidate bytes.

These green gates do not override the nonzero CTest and count rows. Evidence is E2 only; no E3/E4 or live/deployed claim exists.

## Acceptance and boundary status

Acceptance criteria 1-7 remain satisfied at the candidate-specific/product surface by the newly measured and explicitly carried evidence. Criterion 8 is preserved: no 2b-due behavioral leg is claimed. The approved Task-5 battery as a whole is not green because its required ledger retains nonzero R-4.35 and R-4.38 entries.

The boundary remains unchanged: engine unwired; no product-to-engine call/include; no hook installation; renderer predicate is exactly stdin TTY AND stderr TTY; no JSON/env/config suppressor or approval persistence; no credential boundary crossing.

## Explicit NOT-DONE

- No product, test, schema, harness, CMake, workflow, plan, or sealed-byte mutation.
- No engine wiring, product-to-engine call/include, hook installation, format act, or `repos`/N change.
- No FX-A6 a6.1-13, divergence half of a6.16, or any FX-A7 behavioral leg; all remain sub-step-2b-due.
- No list/info implementation, prompt A/B/C, preview, PTY-helper, summary/warning-row, persistence, or extra argv surface.
- No remote CI, push, PR, merge, deployment, publication, seal, waiver, or release.
- No verification-complete, Linux-green, merge-ready, or release claim.

## Remaining risk and requested next action

The rev12 package defect is closed, but the required battery remains red on two registered gates. Pair Planner: record the exact receipts, retain/reroute R-4.35 and R-4.38 to their named owners/governing adjudication, and do not advance the candidate as verification-complete or merge-ready absent an owner-routed resolution and a fresh green required battery. No new product-plan delta is proposed by this report.

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: no — the host credential stayed outside the container and evidence; no value was read, emitted, copied, or changed
- migration/backfill/destructive-write/canonical-data-repair: no
- money/inventory/orders/planning/accounting/trust-critical-state: no
- AI-or-automation-acts-downstream: no
- worker/scheduler/queue/retry/async-side-effect: no
- cross-repo/service-contract/generated-schema/shared-API-event: yes — sealed PDC contracts and published Bivpak schemas remain governing surfaces
- user-visible-control-with-materializer/downstream-consumer: yes — this consent renderer remains unwired pending held sub-step 2b
- test-runtime-role-mismatch: no — fixed uid/gid 1001, suite-owned fixture, restored nofile, and the runtime SSH dependency all measured in the intended topology
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: yes — R-4.35 and R-4.38 remain registered nonzero gates; no local acceptance or waiver is inferred
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: none
- scan_presented_to_operator: no — no downgrade or residual-risk acceptance is proposed
- operator_reply_after_scan: none
- valid_waiver: no
WAIVED_RISK_ACCEPTANCE: none

ACTIONS_GIT_REF: verification-only execution against clean `intg/consent-fabric@3cd31e4823d40c1c9ea020fcb51917618368533b` over `main@02b51435a5b50363df7f595dd827af107424b0c3`; exact dispatch/plan digests, 18-path fence, disposable four-phase Linux receipt, retained ledger, and carried macOS evidence reconciled; this report files through the intg relay daemon; no product commit, push, PR, merge, remote CI, deployment, publication, seal, or release
RELAY_LINT: exact-file v2.9.2 lint is the daemon submission gate; rendered result, digest, and daemon verification reported externally
FINAL_GIT_STATUS_SHORT:
candidate worktree: none — clean tree at 3cd31e4823d40c1c9ea020fcb51917618368533b
primary root, path-scoped to `.relays/intg` and `docs/sprints/2026-08-27-intg-consent-fabric`: none before this report draft; only the daemon draft/filing and rendered intg INDEX projection are this seat's writes
primary root inherited: 35 S4 relay/sprint-document paths remain outside intg scope and unchanged by this seat
