## IMPL REPORT — TASK 5 EXECUTED AT FROZEN 3cd31e4; BLOCKED, NOT VERIFICATION-COMPLETE — MACOS RAW CTEST RETAINS TWO HOST-ENVIRONMENT REDS; LINUX RETAINS R-4.35, R-4.38, AND A FROZEN-BASE `openssh-client` OMISSION; A6 FABRIC ITSELF PASSES 127/12 ON BOTH HOSTS

ROLE: Pair Implementer
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: intg-substep1-impl-2
PARENT_DISPATCH_ID: intg-substep1-impl-2
IN_REPLY_TO: intg-substep1/IMPL-pair-planner-20260828-144303.md
RELATED_CONTEXT: intg-substep1/PLAN-pair-planner-20260828-135056.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep1-20260827.md; ../../../pdc/master/relays/intg-substep1-master-answers/PLAN-master-planner-20260828-022017.md; ../../../pdc/master/relays/intg-stop1-a6-golden-bytes/DESIGN-planner-20260827-235912.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — the approved battery is nonzero; the frozen base package list needs a fresh exact-hash plan review before adding `openssh-client`; R-4.35 and R-4.38 remain owner/adjudication gates; merge and release remain separately held and the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: intg-consent-fabric-plan
DESIGN_LOCK_ID: m3-addendum-6-c41d015f-lock-20260825
DESIGN_RECORD_KIND: design-doc
SECOND_CONSUMED_LOCK: m3-addendum-7-4c40fe37-lock-20260827
PLAN_LOCK_ID: intg-substep1-plan-20260827 @ sha256 6e179f2b99faf86770d97f865e7e2e9de4b8446b2e7fa62cdaabc3eb3a55f91e
BASE: main@02b51435a5b50363df7f595dd827af107424b0c3
BRANCH: intg/consent-fabric@3cd31e4823d40c1c9ea020fcb51917618368533b — unchanged and clean after verification
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: master.master-planner, master.master-reviewer, m-3.implementer
SUBJECT: BLOCKER return for intg-substep1-impl-2 — Task 5 Steps 1-4 executed without candidate mutation; retain every red and route the `openssh-client` delta through a fresh locked-plan cycle; no verification-complete or merge-ready claim

## Disposition

**BLOCKED; NOT VERIFICATION-COMPLETE; NOT LINUX-GREEN; NOT MERGE-READY.**

The verification-only token was consumed at the exact locked-plan digest and frozen candidate. No product, test, schema, harness, CMake, workflow, or plan byte changed. The candidate remains clean at `3cd31e4823d40c1c9ea020fcb51917618368533b`.

PR: none — no PR, push, merge, publication, deployment, or release authority exists in this dispatch.

## Task 5 Step 1 — fence transcript

```text
rc=1 expected/no matches  run_eligibility|restore_entry|repo::capture outside src/core/repo
rc=1 expected/no matches  #include "core/repo/ outside src/core/repo
rc=0 lines 117,971       require_empty_array remains in src/core/manifest/manifest.cpp
rc=1 expected/no matches  getenv|setenv|ofstream|fopen|config in src/cli/url_consent.cpp
rc=0 count=2             exactly two isatty tokens
rc=0                      byte-exact ::isatty(STDIN_FILENO) != 0 && ::isatty(STDERR_FILENO) != 0 conjunction
rc=1 expected/no matches  STDOUT_FILENO|json in src/cli/url_consent.cpp
rc=0 empty diff           BASE..HEAD src/core/repo engine path
rc=0 count=18            exact planned changed-path census
fence aggregate rc=0
```

The eighteen paths match the dispatch SCOPE_DIFF exactly. No engine reference/include or engine byte escaped the fence.

## Task 5 Step 2 — macOS receipt

```text
cmake --preset ci-macos                                      rc=0
cmake --build --preset ci-macos                              rc=0
ctest --preset ci-macos --output-on-failure                  rc=8
biv_tests                                                     PASS, 448.68 s
harness-e2                                                    PASS, 286.64 s
harness-selftest                                              RED, 119 failed / 884 passed
safety-hardening                                              RED, readelf unavailable
raw CTest total                                               17 accounted pass/skip, 2 failed of 19
```

The two reds are retained. Root-cause evidence, not replacement evidence:

- Harness `CREDENTIAL_ENV_NAMES` is exactly `ANTHROPIC_API_KEY`, `OPENAI_API_KEY`, and `CODEX_ACCESS_TOKEN`; the raw child environment contained the first name only. The failure detail was `credential-env:ANTHROPIC_API_KEY`. A minimal controlled rerun removing only those three names produced `1003 passed in 10.60s` (rc 0). No credential value was printed, copied, or persisted.
- `harness/ci/check_hardening.py` requires `shutil.which("readelf")`; the macOS host has no `readelf`, and the row returned `readelf unavailable`. This is the Linux ELF row, but the raw full-CTest red remains in the result.

Required candidate evidence is independently green at the same built bytes:

```text
./build/ci-macos/biv_tests "[a6-fabric]" --success            rc=0
Catch2 result                                                  127 assertions / 12 test cases
Python harness/selftest/test_envelope.py                       6 passed / rc=0
```

## Task 5 Step 3 — four-phase Linux parity receipt

Phase H ran on the host with the authenticated `gh` boundary. All eight assets for `toolchain-mirror-clang-tidy-22-immutable-v1` downloaded outside the worktree; derived `SHA256SUMS` passed `sha256sum --check --strict`; asset count was exactly eight. No host token entered the container or evidence.

Phase R used disposable `ubuntu:24.04 --platform linux/amd64 --init`, with the main repository read-only at `/repo-ro` and the verified asset directory read-only at `/llvm22-mirror`. The frozen enumerated base command ran unamended. Every `.deb` name/version/architecture row passed; all installed versions equal `1:22.1.8~++20260613092238+e80beda6e255-1~exp1~20260613092253.78`; `clang-tidy-22 --version` reported LLVM 22.1.8.

Phase T created gid/uid 1001 before ownership, cloned `intg/consent-fabric` from `/repo-ro` into writable `/work`, and produced this exact receipt:

```text
expected=3cd31e4823d40c1c9ea020fcb51917618368533b
observed=3cd31e4823d40c1c9ea020fcb51917618368533b
runuser -u suite -- test -w /mnt/c/tmp                     rc=0
```

Phase S ran as `suite`; the runuser soft `nofile` value rose from 1024 to the inherited hard 1048576 before measurement. The harness venv was created before configure and carried the locked requirements. The required no-short-circuit ledger is verbatim:

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

Linux CTest retained two failed rows of 19:

1. `repo_engine` — one case / two assertions red because `tests/test_repo_engine.cpp` invokes `/usr/bin/ssh -G`, while the frozen base set installs Git with `--no-install-recommends` and does not install `openssh-client`. The exact exception was `ssh transport expansion failed`. No package was installed in-run. **Proposed delta for fresh exact-hash review:** append `openssh-client` to the enumerated base `apt-get install --no-install-recommends` command.
2. `harness-selftest` — `4 failed, 995 passed, 3 skipped`, all in the registered mutation-during-read/enumeration adversary family in `test_e3_asserts.py`. This is R-4.35 attribution only; the rc stays red.

The tidy row executed and passed (`status='run'`). `safety-hardening` passed. E2 passed. The named A6 execution passed 127 assertions in 12 cases. Catch2 XML generation passed, then the disclosed R-4.38 count gate retained its red:

```text
expected successes/failures/expectedFailures/skips = 412/0/0/1
observed successes/failures/expectedFailures/skips = 399/0/0/1
count-read rc=1
```

No exploratory amended Linux rerun was performed.

## Named A6 evidence and leg census

Both macOS and Linux executed and passed these twelve names under `[a6-fabric] --success`:

1. `a6-R1 open carriers: exact rows, order, cardinality, grouped advisory, zero state`
2. `a6-R1 pack carries the grouped advisory too: exact entries, order, zero state`
3. `a6-R1 site 1: the preflight grain rides the top-level error carrier`
4. `a6-R1 exit composition: one typed aggregator over both sources`
5. `a6.15 zero state: no divergence -> both carriers absent on real verb envelopes`
6. `A6-R2 PROMPT D bytes are golden`
7. `A6-R4 accepted notice bytes are golden`
8. `A6-R4 refusal + guidance bytes are golden`
9. `A6-R2 default N: empty answer refuses; y proceeds; wrapper renders byte-whole to err`
10. `a6-R3 pack and open accept --accept-url-divergence`
11. `a6.14 list/info accept the flag inert: full-stream equality with flagless`
12. `a6.18 inherited no-help boundary witnessed on pack/list/info`

Leg census: a6.14 = 1 case / 14 assertions; a6.15 = 1 / 13; a6.17 = 3 exact Python structural nodes; a6.18 = 1 / 30 with pack/list/info witnessed; a6.16 zero half = all 6 current envelope selftests passed. The behaviorally wired halves remain 2b-due and are not claimed.

STOP-1 byte ownership remains the owner ruling `intg-stop1-a6-golden-bytes/DESIGN-planner-20260827-235912.md`: PROMPT D ends with one trailing space and no newline; the pack refusal detail begins `pack refused:` with no indent.

## Acceptance, evidence, and boundary status

- Implementation/product-byte scope: unchanged and previously implementation-complete at E2-local evidence; this verification act adds no product claim.
- Acceptance criterion 7 fences: green at exact candidate bytes.
- macOS required product and named evidence: green; raw CTest aggregate red as recorded.
- Linux canonical parity battery: red; not verification-complete.
- Evidence level: E2 measurements only. No live/deployed E3/E4 claim.
- Boundary contract: engine unwired; no product-to-engine call/include; renderer predicate remains exact stdin-TTY AND stderr-TTY; credential boundary preserved.

## Explicit NOT-DONE

- No product, test, schema, harness, CMake, workflow, plan, or sealed-byte mutation.
- No engine wiring, product-to-engine call/include, or hook installation.
- No FX-A6 a6.1–13, divergence half of a6.16, or any FX-A7 behavioral leg; all remain sub-step-2b-due.
- No format act or `repos`/N change; no list/info implementation; no prompt A/B/C, preview, PTY-helper, summary/warning-row, persistence, or extra argv surface.
- No remote CI, push, PR, merge, deployment, publication, seal, or release.
- No verification-complete, Linux-green, merge-ready, waiver, or release claim.

## Remaining risk and requested next action

Remaining risk is bounded but unresolved: the frozen bare-Linux package list cannot execute the real SSH expansion case; the registered R-4.35 adversary family is red; R-4.38 counts differ by thirteen successes; and the raw macOS aggregate retains its two environment/tooling reds.

Requested action: pair Planner returns a successor plan whose frozen base set includes `openssh-client`, routes R-4.35/R-4.38 to their owners or governing adjudication, and obtains fresh exact-hash PLAN-REVIEW before issuing any new Task-5 token. Do not advance the candidate as verification-complete or merge-ready.

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: no — no credential value was read, emitted, copied, or changed
- migration/backfill/destructive-write/canonical-data-repair: no
- money/inventory/orders/planning/accounting/trust-critical-state: no
- AI-or-automation-acts-downstream: no
- worker/scheduler/queue/retry/async-side-effect: no
- cross-repo/service-contract/generated-schema/shared-API-event: yes — the sealed PDC contract and published Bivpak schemas remain governing surfaces
- user-visible-control-with-materializer/downstream-consumer: yes — this consent renderer precedes held sub-step-2b engine wiring
- test-runtime-role-mismatch: yes — the frozen bare-Linux base lacks the `/usr/bin/ssh` runtime required by a registered real-Git test
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: yes — R-4.35, R-4.38, and both raw macOS reds remain unresolved
ESCALATION_SCAN_RESULT: trigger-present
OPERATOR_WAIVER: none requested, offered, or inferred
WAIVED_RISK_ACCEPTANCE: none

ACTIONS_GIT_REF: verification-only execution against clean `intg/consent-fabric@3cd31e4823d40c1c9ea020fcb51917618368533b` over `main@02b51435a5b50363df7f595dd827af107424b0c3`; report filed through the intg relay daemon; no product commit, push, PR, merge, remote CI, deployment, publication, seal, or release
RELAY_LINT: engine-rendered submission; exact-file v2.9.2 lint, digest, daemon receipt, and relay verification follow filing
FINAL_GIT_STATUS_SHORT:
candidate worktree: none — clean tree at 3cd31e4823d40c1c9ea020fcb51917618368533b
primary root, path-scoped to `.relays/intg` and `docs/sprints/2026-08-27-intg-consent-fabric`: none before this report draft; only the daemon draft/filing and rendered intg INDEX projection are this seat's writes; inherited `.relays/s4` and S4 sprint-doc noise remains outside intg scope and unchanged by this seat
