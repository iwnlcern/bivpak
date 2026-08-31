## IMPL return — master's directed evidence-only measurement is complete at exactly 3+3+1 runs: all seven bare `open-unknown-agent` packs completed in about 30 seconds, exit 2, without hitting either cap; receipts below, no interpretation at this seat, Task 1 remains CLOSED/HOLD

ROLE: Pair Implementer
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: intg-substep2a-impl-return
PARENT_DISPATCH_ID: intg-substep2a-impl
IN_REPLY_TO: intg-substep2a/PLAN-pair-planner-20260831-162101.md
RELATED_CONTEXT: intg-substep2a/IMPL-pair-implementer-20260831-151147.md; intg-substep2a/SITREP-pair-planner-20260831-160838.md; ../../pdc/master/relays/intg-substep2a-format-act/PLAN-master-planner-20260831-161423.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — this is the directed bounded evidence return only; it grants no product-semantic decision, timeout/gate change, Task 1 restart, merge, publication, deployment, seal, or release
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
SUBJECT: EVIDENCE RETURN — exact M1 3+3 and M2 1 bare-pack measurements complete; all seven complete at about 30 seconds with exit 2 and no cap hit; M3 facts and one interpretation-free sample receipted; no retries or other rows; HOLD

## Verdict and boundary

The exact authorized run set is consumed: three format-act M1 runs, three primary M1 runs, and one format-act M2 run. Every invocation completed; no invocation hit its cap. I performed no retry and no additional scenario row. The receipts below are evidence only feeding the routed R-4.37 diagnosis; I draw no product conclusion and change no gate or timeout. Task 1 remains CLOSED/HOLD until the owner's ruling returns through the master edge.

No full `harness-e2`, no C3, no Task 1, and no source, test, schema, harness, workflow, gate, timeout, or product edit occurred. The only environment change was the directed value-free `env -u ANTHROPIC_API_KEY`; no credential value was read, recorded, or echoed.

## Fixture and argv derivation

The external measurement driver imported and called the harness's own fixture/profile helpers. The exact source was derived as follows from the pinned format-act tree:

- `harness/scenarios/open-unknown-agent.json:2-8`: scenario id `open-unknown-agent`, agent `codex`, the sole fixture entry `work.txt` with exact text `workspace\n`, and first operation `pack`.
- `harness/bivharness/scenario.py:471-483`: `work = scratch / spec["id"]`, `source = work / "source"`, then the harness materializes the fixture and prepares the agent profiles.
- `harness/bivharness/scenario.py:293-318`: the synthetic Codex transcript and `CODEX_HOME` source profile are constructed.
- `harness/bivharness/scenario.py:496-499`: the harness constructs `_run_json(biv, ["pack", str(source), ...], work, source_env)`; `_run_json` appends `--json`.
- `harness/bivharness/fixtures.py:260-264`: the file entry is written byte-for-byte.

Each fresh scratch root was created under `/private/tmp`, outside both repositories, with the requested double layout:

```text
<scratch>/open-unknown-agent/open-unknown-agent/source
```

The exact bare argv shape was:

```text
<selected-build>/biv pack <fresh-absolute-scratch>/open-unknown-agent/open-unknown-agent/source --json
```

The current working directory was `<scratch>/open-unknown-agent/open-unknown-agent`; `CODEX_HOME` named that run's harness-fabricated `profiles/source-codex`; `ANTHROPIC_API_KEY` was absent. All seven driver receipts record `sanitized_name_absent: true`. The fixture `work.txt` SHA-256 was identical in every run: `d2e9f563419699d12f7be092973f94a255e4ffd5567722fa3875a0e91501c010`.

## M1 — format-act binary, exactly three runs, 60-second cap each

Binary:

```text
/Users/jack/Programming/bivpak-intg-format-act/build/ci-macos/biv
sha256 92ced84dcd616741a4db92c366045274822edaf3dbec9c3e40c3dec20a235128
```

The binary target was verified with `cmake --build --preset ci-macos --target biv` at the pinned format-act head; build rc 0.

| run | fresh scratch root | wall seconds | exit | cap hit | stderr |
|---:|---|---:|---:|---|---|
| 1 | `/private/tmp/bivpak-intg-format-m1-1-3kgv46gm` | 30.477250 | 2 | false | empty |
| 2 | `/private/tmp/bivpak-intg-format-m1-2-hkg8z3g1` | 29.908222 | 2 | false | empty |
| 3 | `/private/tmp/bivpak-intg-format-m1-3-a523s41w` | 29.966114 | 2 | false | empty |

For each row stdout was valid JSON with these exact common result fields:

```text
ok: true
verb: pack
exit_code: 2
warnings: [{kind: SessionLiveAtPack, path: 019faaaa-bbbb-7ccc-8ddd-eeeeeeee0001}]
advisories: []
member_count: 2
payload_bytes: 10
manifest.format_version: 1
manifest.repos: []
manifest.agent_sessions: [{agent: codex, session_count: 1}]
error: null
```

Per-run transcript SHA-256 values, whose transcript bytes include that run's fresh absolute source path:

```text
run 1  0056ebb14f1ca845ebe55e35f5766bec2a4d3911149f3f6cc80ca12d602df031
run 2  0c2a19ebd42aac63f5e1e060a8b829ded9a81072087c52c40d61137ffc3ec067
run 3  701ebe69811d0cee699c51324a8f43eecba9e4ae6cff8dee77086981a30601f6
```

Raw structured receipt retained at `/tmp/bivpak-intg-m1-format.json`, SHA-256 `15f50f0f9b5b24a50a390d10f0d775b0ccb7662eb135b980492e6a06391de3a2`.

## M1 — primary binary, exactly three runs, 60-second cap each

Binary:

```text
/Users/jack/Programming/bivpak/build/ci-macos/biv
sha256 6508deafa397e6b38453bf63a70b04d16efd015d5201bd72a88bc7a22de16f52
```

The primary product paths were mechanically equal to the pinned base, and `cmake --build --preset ci-macos --target biv` rebuilt the ignored primary artifact in place from those bytes; build rc 0. No tracked product byte moved.

| run | fresh scratch root | wall seconds | exit | cap hit | stderr |
|---:|---|---:|---:|---|---|
| 1 | `/private/tmp/bivpak-intg-primary-m1-1-xrx9nzvw` | 29.824480 | 2 | false | empty |
| 2 | `/private/tmp/bivpak-intg-primary-m1-2-0m4iaj_m` | 29.635115 | 2 | false | empty |
| 3 | `/private/tmp/bivpak-intg-primary-m1-3-a9v9xk51` | 29.506021 | 2 | false | empty |

Each row returned the same common JSON result fields listed in the format-act section. Per-run transcript SHA-256 values:

```text
run 1  09d97157daa4c4a6fc5cebbfffce4749115edc29936ccb3fe02311c4c64b57f7
run 2  9c3f2c63fbedaaff17c3524d1f008caa37775f2a7b405f0e43764a80732c4e60
run 3  84978721cd21da1d475e4c611a9e7941bfd0fa0c79c21ee2e3e6d86d8cff754b
```

Raw structured receipt retained at `/tmp/bivpak-intg-m1-primary.json`, SHA-256 `ba76e7e1897bcaee618a8747bccc8acf56b47e22489a050b557e69f6c18fb55b`.

## M2 — one format-act long-cap completion probe

Exactly one further bare format-act invocation used a stated hard cap of 600 seconds:

| run | fresh scratch root | wall seconds | exit | cap hit | stderr |
|---:|---|---:|---:|---|---|
| 1 | `/private/tmp/bivpak-intg-format-m2-1-ow0xe731` | 30.371123 | 2 | false | empty |

It completed and returned the same common JSON result fields listed above. Transcript SHA-256: `9db198e55c6e64943b829421f389777e0183780645c2e438fc97ef4f7844063a`.

One optional interpretation-free `sample` was taken after the process remained live at the 10-second sample delay:

```text
pid: 53358
sample duration: 5 seconds
sample exit: 0
sample path: /private/tmp/bivpak-intg-format-m2-1-ow0xe731/sample.txt
sample sha256: 9c1559b9b8af15d91dd3b0707e8722c2f7d4e9e38874eeb1f2a6afc3b33fa30e
```

No interpretation is attached. Raw structured M2 receipt retained at `/tmp/bivpak-intg-m2-format.json`, SHA-256 `a5275a93618d3489867b4e9f9e40ee94370a5f5c6530230499c218a91652bafa`.

## M3 — cheap object-database and source facts only

- `/Users/jack/Programming/bivpak-intg-format-act/.git` is a file containing `gitdir: /Users/jack/Programming/bivpak/.git/worktrees/bivpak-intg-format-act`.
- `/Users/jack/Programming/bivpak/.git` is a directory.
- The linked worktree resolves its common directory to `/Users/jack/Programming/bivpak/.git` and its objects to `/Users/jack/Programming/bivpak/.git/objects`; the primary objects directory is the same primary `.git/objects` store.
- Every pack target above was a fresh harness-fabricated scratch source under `/private/tmp`, outside both repository roots and outside that object store.

These are observations only; no interpretation is owed or supplied at this seat.

## C4 before/after equality and product-byte receipts

Format-act remained at `46df8f3c35981a4ae3f77cf3293a4b7212b4b996`. Its complete `git status --porcelain=v1 --untracked-files=all` stream was empty both before and after; direct-stream SHA-256 both times was `e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855`.

Primary remained at `ecf2b4de6c254952d71e04fd06e1d723a1161f1c` through measurement. Its complete 35-row status stream contained only inherited S4 state both before and after; direct-stream SHA-256 both times was `aee3eac8aa0a74221c8a386b27ef04a081284e89fafbb8e1d57f2a26632925f5`.

For each worktree, `git diff --quiet 46df8f3c35981a4ae3f77cf3293a4b7212b4b996 -- src schemas tests harness CMakeLists.txt` returned rc 0 after the measurement. The format-act worktree has no tracked or untracked byte. The primary's inherited S4 rows were preserved and unclaimed.

## Fence receipt and required hold

- M1 format-act: exactly 3 runs, no retry.
- M1 primary: exactly 3 runs, no retry.
- M2 format-act: exactly 1 run and exactly 1 optional sample, no retry.
- Other scenario rows: 0.
- Full `harness-e2`: NOT RUN.
- C3: NOT RUN.
- Task 1: NOT STARTED; remains CLOSED/HOLD.
- Environment mutation other than directed value-free sanitation: NONE.
- Product, source, test, schema, harness, plan, workflow, gate, or timeout edit: NONE.
- Merge, push, PR, remote CI, publication, deployment, seal, or release: NONE.

Please route these receipts upward with m-3 copied as directed. I now HOLD regardless of outcome; the token remains live-held until m-3's routed ruling returns down the master edge.

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: yes — value-free sanitation of one ambient credential variable name; value never read or recorded
- migration/backfill/destructive-write/canonical-data-repair: no
- money/inventory/orders/planning/accounting/trust-critical-state: no
- AI-or-automation-acts-downstream: no
- worker/scheduler/queue/retry/async-side-effect: no
- cross-repo/service-contract/generated-schema/shared-API-event: yes — locked M/N remains the governing contract; evidence routes to the m-3 owner
- user-visible-control-with-materializer/downstream-consumer: yes — planned feature only; no implementation byte exists
- test-runtime-role-mismatch: yes — this relay reports the directed bare-pack timing evidence without interpretation
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: yes — diagnosis, any gate/timeout change, and any Task 1 restart remain owner-routed
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: none
- scan_presented_to_operator: no
- operator_reply_after_scan: none
- valid_waiver: no
WAIVED_RISK_ACCEPTANCE: none

ACTIONS_GIT_REF: evidence-only execution at pinned `intg/format-act@46df8f3c35981a4ae3f77cf3293a4b7212b4b996` and product-equal primary `main@ecf2b4de6c254952d71e04fd06e1d723a1161f1c`; built/verified ignored `build/ci-macos/biv` artifacts; executed exactly seven external bare-pack invocations and one sample in fresh `/private/tmp` roots; no tracked product/workflow/harness/gate/timeout edit; this receipt submits through the intg daemon from the primary docs lane
RELAY_LINT: exact-file v2.9.2 lint is the daemon submission gate; rendered result, digest, live INDEX tail, daemon status, and `relay verify` are checked after filing
FINAL_GIT_STATUS_SHORT:
worktree `/Users/jack/Programming/bivpak-intg-format-act`: none — clean at `intg/format-act@46df8f3c35981a4ae3f77cf3293a4b7212b4b996`
primary `/Users/jack/Programming/bivpak`: 35 inherited S4-only rows before daemon submission, direct-stream sha256 `aee3eac8aa0a74221c8a386b27ef04a081284e89fafbb8e1d57f2a26632925f5`; no intg tracked dirt before this daemon submission
