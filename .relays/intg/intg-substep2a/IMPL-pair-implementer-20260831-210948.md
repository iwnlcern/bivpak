## IMPL return — combined R-4.37 evidence set complete at exactly three acts and one new run: seven retained effective environments + metadata-only store census, one 25-second sampled bare pack, and the staged fixture shape; receipts verbatim below, no m-3 conclusion drawn, HOLD

ROLE: Pair Implementer
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: intg-substep2a-impl-return
PARENT_DISPATCH_ID: intg-substep2a-impl
IN_REPLY_TO: intg-substep2a/PLAN-pair-planner-20260831-194932.md
RELATED_CONTEXT: intg-substep2a/IMPL-pair-implementer-20260831-163742.md; intg-substep2a/SITREP-pair-planner-20260831-171137.md; ../../pdc/master/relays/intg-substep2a-format-act/PLAN-master-planner-20260831-194614.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/DESIGN-m2-planner-20260831-192500.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — this is the directed evidence return only; H-A/H-D and any product, gate, timeout, Task 1, merge, publication, deployment, seal, or release decision remain at their routed owners
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: intg-format-act-plan
DESIGN_LOCK_ID: m1-addendum-N-82293732-lock-20260827
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: intg-substep2a-plan-20260830 @ sha256 57ab3b9ba15c5674dae5b42dc3a3c48252e844f8e3d863d0cb1f3682c33b4a4b
BASE: main@46df8f3c35981a4ae3f77cf3293a4b7212b4b996
BRANCH: intg/format-act@46df8f3c35981a4ae3f77cf3293a4b7212b4b996 in /Users/jack/Programming/bivpak-intg-format-act; clean; no implementation commit
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: master.master-planner, master.master-reviewer, m-3.planner, m-3.implementer, m-2.planner
SUBJECT: EVIDENCE RETURN — exact Acts 1-3 complete; seven environments and store counts, one 30.372974-second run with 25-second sample, fixture shape; no retries or other rows; HOLD

## Boundary and run-budget receipt

The exact three acts are consumed. Act 1 read only the five named environment variables and filesystem metadata. Act 2 launched exactly one new bare `open-unknown-agent` pack, with no retry. Act 3 read only staged-profile filesystem metadata. No other scenario row, full `harness-e2`, C3, Task 1, source/test/schema/harness/workflow/gate/timeout edit, merge, push, PR, remote CI, publication, deployment, seal, or release action occurred.

The only process-environment change was the standing value-free `env -u ANTHROPIC_API_KEY`; no credential value was read, recorded, or echoed. The metadata census did not open any session, rollout, configuration, or database content. H-A/H-D is m-3's cut; no conclusion is drawn at this seat. The live-held token, 2a hold, and option (c) refusal remain unchanged.

## ACT 1a — effective environment of the seven retained bare runs

The retained driver constructs `env = os.environ.copy()` and then overlays only the harness-produced `source_env`. For this scenario `_prepare_agent_profiles(..., ["codex"])` supplies only `CODEX_HOME`. Each measurement process was launched under `env -u ANTHROPIC_API_KEY`.

The identically reconstructed sanitized context printed these common effective values for all seven rows:

```text
HOME=/Users/jack                                      inherited
CODEX_SQLITE_HOME=<unset>                            inherited absence
CLAUDE_CONFIG_DIR=<unset>                            inherited absence
TMPDIR=/var/folders/hq/f0qq8v_103q9y8prfn20rzx80000gn/T/  inherited
ANTHROPIC_API_KEY=<unset>                            explicitly removed
```

The one row-specific override was `CODEX_HOME`:

| retained row | effective CODEX_HOME |
|---|---|
| format-m1 1 | `/private/tmp/bivpak-intg-format-m1-1-3kgv46gm/open-unknown-agent/open-unknown-agent/profiles/source-codex` |
| format-m1 2 | `/private/tmp/bivpak-intg-format-m1-2-hkg8z3g1/open-unknown-agent/open-unknown-agent/profiles/source-codex` |
| format-m1 3 | `/private/tmp/bivpak-intg-format-m1-3-a523s41w/open-unknown-agent/open-unknown-agent/profiles/source-codex` |
| primary-m1 1 | `/private/tmp/bivpak-intg-primary-m1-1-xrx9nzvw/open-unknown-agent/open-unknown-agent/profiles/source-codex` |
| primary-m1 2 | `/private/tmp/bivpak-intg-primary-m1-2-0m4iaj_m/open-unknown-agent/open-unknown-agent/profiles/source-codex` |
| primary-m1 3 | `/private/tmp/bivpak-intg-primary-m1-3-a9v9xk51/open-unknown-agent/open-unknown-agent/profiles/source-codex` |
| format-m2 1 | `/private/tmp/bivpak-intg-format-m2-1-ow0xe731/open-unknown-agent/open-unknown-agent/profiles/source-codex` |

Every retained receipt records `sanitized_name_absent: true` and its exact row-specific `codex_home` value.

## ACT 1b — harness sanitized C3/rerun contexts

The C3 full rows and the bounded rerun use the same scenario runner:

- `harness/bivharness/scenario.py:134-151`: `_run_json` copies `os.environ`, overlays only `env_overrides`, and supplies that environment to the command.
- `harness/bivharness/scenario.py:262-319`: `_prepare_agent_profiles` starts with empty `source_env`; it sets `CLAUDE_CONFIG_DIR` only when `claude-code` appears in the scenario agents and sets `CODEX_HOME` only when `codex` appears.
- `harness/scenarios/open-unknown-agent.json:2-8`: this scenario names only `codex` and starts with `pack`.
- `harness/bivharness/scenario.py:471-483,496-499`: the scenario prepares those profiles and passes `source_env` to the exact pack invocation.

Therefore, for the sanitized `open-unknown-agent` C3 and bounded-rerun contexts, `source_env` set only the scratch `CODEX_HOME`; `HOME`, `CODEX_SQLITE_HOME`, `CLAUDE_CONFIG_DIR`, and `TMPDIR` remained inherited. The surrounding launch removed only the value-free name `ANTHROPIC_API_KEY`.

## ACT 1c — store-resolution source and metadata-only census

Resolution source at the pinned format-act bytes:

- `src/core/pack/pack.cpp:610-620`: pack constructs the process environment and iterates every built-in adapter's `discover` and `collect`.
- `src/adapters/registry.cpp:11`: the built-ins are Claude Code and Codex.
- `src/adapters/codex/codex.cpp:1193-1206`: Codex adds an existing env `CODEX_HOME`, then also adds `$HOME/.codex` when it exists and differs from the env root.
- `src/adapters/codex/codex.cpp:1157-1177`: `CODEX_SQLITE_HOME`, if set, is the first SQLite locator source; it was unset in every measured environment. The metadata census did not read the fallback configuration content.
- `src/adapters/claude_code/claude_code.cpp:570-594`: with `CLAUDE_CONFIG_DIR` unset, Claude Code resolves the existing `$HOME/.claude` default.

Counts below were produced by directory enumeration and `stat` only. `immediate` means direct children of the named root; subtree directory/file counts are recursive metadata counts within the named store subtree. No entry name or content from the real stores is carried in this receipt.

| root | immediate entries | immediate dirs/files | named subtree metadata | state_5.sqlite |
|---|---:|---:|---|---|
| `/Users/jack/.codex` | 54 | 20 / 34 | `sessions`: 159 descendant dirs, 1330 regular files, 1326 JSONL, 1326 rollout JSONL; `archived_sessions`: 0 descendant dirs, 4 regular files, 4 JSONL, 4 rollout JSONL | present, 9,228,288 bytes |
| `/Users/jack/.claude` | 41 | 22 / 19 | `projects`: 228 descendant dirs, 2210 regular files, 762 JSONL; `sessions`: 0 descendant dirs, 46 regular files, 0 JSONL | absent |

Each of the seven row-specific scratch `source-codex` roots above had the same census:

```text
root immediate entries: 1 (one directory, zero regular files)
sessions subtree: 3 descendant directories, 1 regular file,
                  1 JSONL, 1 rollout JSONL
rollouts directory: absent
archived_sessions directory: absent
projects directory: absent
state_5.sqlite: absent
```

`CODEX_SQLITE_HOME` resolved to no environment path because it was unset. `TMPDIR` is not an adapter store root. The resolved pack store roots on these bytes were the row-specific scratch `CODEX_HOME`, the distinct existing default `/Users/jack/.codex`, and the existing Claude default `/Users/jack/.claude`.

## ACT 2 — exactly one sampled bare run

Invocation:

```text
/Users/jack/Programming/bivpak-intg-format-act/build/ci-macos/biv \
  pack \
  /private/tmp/bivpak-intg-format-act2-1-k2_5gtbb/open-unknown-agent/open-unknown-agent/source \
  --json
```

Receipt:

```text
binary sha256: 92ced84dcd616741a4db92c366045274822edaf3dbec9c3e40c3dec20a235128
hard cap: 600 seconds
wall: 30.372974 seconds
exit: 2
cap_hit: false
stderr: empty
sanitized_name_absent: true
stdout JSON: ok=true, verb=pack, exit_code=2,
  warning=SessionLiveAtPack(019faaaa-bbbb-7ccc-8ddd-eeeeeeee0001),
  member_count=2, payload_bytes=10, codex session_count=1, error=null
fixture work.txt sha256: d2e9f563419699d12f7be092973f94a255e4ffd5567722fa3875a0e91501c010
transcript sha256: 0794b1c8ec6ce4777febafc853dccaa8c60b5c584597c0f351302e3591b86e0a
raw structured receipt: /tmp/bivpak-intg-act2-format.json
raw receipt sha256: 315270f98a20c53aca0663d7ccbea71f47b86a5325bf305118fe10f96a5745fb
```

Effective environment was the same inherited set from Act 1a, with row-specific `CODEX_HOME=/private/tmp/bivpak-intg-format-act2-1-k2_5gtbb/open-unknown-agent/open-unknown-agent/profiles/source-codex`.

The sampler started after the 3-second delay and ran for 25 seconds:

```text
Sampling process 92571 for 25 seconds with 1 millisecond of run time between samples
Sampling completed, processing symbols...
Sample analysis of process 92571 written to file /private/tmp/bivpak-intg-format-act2-1-k2_5gtbb/sample.txt
sample exit: 0
sample lines: 291
sample bytes: 39216
sample sha256: c8b118c1ab2763d068bedf7e79f5750f991cc83bb970998ca267f250ef3a5c6c
```

The complete sampler output is retained verbatim at that exact path. These exact top call-graph lines are copied without interpretation:

```text
21502 biv::pack::(anonymous namespace)::pack_impl(std::__fs::filesystem::path const&)  (in biv) + 6000  [0x1041983cc]  pack.cpp:620
18852 biv::adapters::(anonymous namespace)::CodexAdapter::collect(std::__fs::filesystem::path const&, std::span<biv::adapters::Store const, 18446744073709551615ul>) const  (in biv) + 12932  [0x1041e3940]  codex.cpp:1273
+ 18851 biv::adapters::(anonymous namespace)::source_text(biv::adapters::SessionRecord::ArtifactSource const&)  (in biv) + 156  [0x1041e7d4c]  codex.cpp:172
2291 biv::adapters::(anonymous namespace)::ClaudeCodeAdapter::collect(std::__fs::filesystem::path const&, std::span<biv::adapters::Store const, 18446744073709551615ul>) const  (in biv) + 5040  [0x1041c0f14]  claude_code.cpp:655
+ 2291 biv::adapters::(anonymous namespace)::source_text(biv::adapters::SessionRecord::ArtifactSource const&)  (in biv) + 156  [0x1041ca7c4]  claude_code.cpp:113
```

No conclusion is attached at this seat.

## ACT 3 — staged fixture agent-store shape

The one new run's `profiles` root had two immediate entries, both directories, and recursively 6 descendant directories, 2 regular files, 1 JSONL, and 1 rollout JSONL.

```text
profiles/source-codex/
  sessions/2026/07/11/
    rollout-2026-07-11T01-00-00-019faaaa-bbbb-7ccc-8ddd-eeeeeeee0001.jsonl

source-codex metadata:
  immediate entries: 1
  descendant directories: 4
  regular files: 1
  JSONL: 1
  rollout JSONL: 1
  config.toml: absent
  state_5.sqlite: absent

profiles/target-codex/
  config.toml

target-codex metadata:
  immediate entries: 1
  descendant directories: 0
  regular files: 1
  config.toml: present, 0 bytes
  state_5.sqlite: absent

profiles/source-claude: absent
profiles/target-claude: absent
```

This shape follows `harness/scenarios/open-unknown-agent.json:5-8` and `harness/bivharness/scenario.py:293-318`: only Codex is named, so only the Codex source/target profiles are staged. No Claude-side profile or store is staged by this fixture. The seven retained run roots had the same one-rollout source-Codex shape.

## C4 before/after equality and exact fences

Format-act remained at `46df8f3c35981a4ae3f77cf3293a4b7212b4b996`. Its complete `git status --porcelain=v1 --untracked-files=all` stream was empty before and after, SHA-256 `e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855` both times.

Primary remained at `95f64fcb4111b81988eefb619e332535256c9f4d` through the three acts. Its complete 35-row inherited S4-only status stream had SHA-256 `aee3eac8aa0a74221c8a386b27ef04a081284e89fafbb8e1d57f2a26632925f5` before and after.

For both worktrees, `git diff --quiet 46df8f3c35981a4ae3f77cf3293a4b7212b4b996 -- src schemas tests harness CMakeLists.txt` returned rc 0 after the acts.

- Act 1 environment reads: exactly the five directed names; metadata census only; no store content read by the census.
- Act 2: exactly one new run and one 25-second sample; no retry.
- Act 3: fixture metadata enumeration only.
- Other scenario rows: 0.
- Full `harness-e2`: NOT RUN.
- C3: NOT RUN.
- Task 1: NOT STARTED; remains CLOSED/HOLD.
- Product, source, test, schema, harness, workflow, gate, or timeout edit: NONE.
- Merge, push, PR, remote CI, publication, deployment, seal, or release: NONE.

Please route these receipts upward with m-3 and m-2 copied as directed. I now HOLD. The H-A/H-D cut, product diagnosis, token transition, and any next act remain outside this seat.

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: yes — only value-free removal of one ambient credential variable name; no value read or recorded
- migration/backfill/destructive-write/canonical-data-repair: no
- money/inventory/orders/planning/accounting/trust-critical-state: no
- AI-or-automation-acts-downstream: no
- worker/scheduler/queue/retry/async-side-effect: no
- cross-repo/service-contract/generated-schema/shared-API-event: yes — the evidence routes into the m-2/m-3-owned R-4.37 diagnosis
- user-visible-control-with-materializer/downstream-consumer: yes — planned format action remains held; no implementation byte exists
- test-runtime-role-mismatch: yes — directed runtime performance evidence is the subject of this return
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: yes — H-A/H-D, diagnosis, gate/timeout changes, and Task 1 restart remain owner-routed
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: none
- scan_presented_to_operator: no
- operator_reply_after_scan: none
- valid_waiver: no
WAIVED_RISK_ACCEPTANCE: none

ACTIONS_GIT_REF: evidence-only execution at pinned `intg/format-act@46df8f3c35981a4ae3f77cf3293a4b7212b4b996` and product-equal primary `main@95f64fcb4111b81988eefb619e332535256c9f4d`; exactly five named environment reads, metadata-only store/profile enumeration, one external bare-pack invocation, and one 25-second sample in `/private/tmp`; no tracked product/workflow/harness/gate/timeout edit; this receipt submits through the intg daemon from the primary docs lane
RELAY_LINT: exact-file v2.9.2 lint is the daemon submission gate; rendered result, digest, live INDEX tail, daemon status, and `relay verify` are checked after filing
FINAL_GIT_STATUS_SHORT:
worktree `/Users/jack/Programming/bivpak-intg-format-act`: none — clean at `intg/format-act@46df8f3c35981a4ae3f77cf3293a4b7212b4b996`
primary `/Users/jack/Programming/bivpak`: 35 inherited S4-only rows before daemon submission, direct-stream sha256 `aee3eac8aa0a74221c8a386b27ef04a081284e89fafbb8e1d57f2a26632925f5`; no intg tracked dirt before this daemon submission
