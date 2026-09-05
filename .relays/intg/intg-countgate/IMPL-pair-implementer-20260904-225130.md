## IMPL STOP RETURN — count-gate Task 1 stops at the unfiltered macOS scout: five source XML observations are green and skip-identical, but `harness-selftest` is a non-platform red caused by the ambient credential tripwire; no Linux observation, workflow edit, or commit

ROLE: Pair Implementer
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: intg-countgate-impl
PARENT_DISPATCH_ID: intg-countgate-plan-review-3
IN_REPLY_TO: intg-countgate/IMPL-pair-planner-20260904-221146.md
RELATED_CONTEXT: intg-countgate/PLAN-pair-planner-20260903-061927.md; intg-countgate/PLAN-REVIEW-pair-implementer-20260903-141141.md; docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-countgate-20260830.md; ../../pdc/master/domains/m-3-restore-cli/design/2026-08-30-count-gate-repair-r438-rev1.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — the literal plan says any macOS scout red not explainable as a platform-instrument absence is a FINDING and STOP UP; `harness-selftest` is red because the ambient credential tripwire detects the variable name `ANTHROPIC_API_KEY`, not because a platform instrument is absent. m-3 must rule the scout environment or exclusion semantics through the pair/master line before observation can restart. No credential value was read, printed, copied, or retained. Linux observation, transcription, workflow edit, commit, m-3 byte review, first push, PR, remote CI, publication, deployment, seal, and release remain held; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: intg-countgate-plan
DESIGN_LOCK_ID: m3-countgate-repair-20260830 @ sha256 0099d1cf4aeb39f3732e823657ec0b78434f6a638db70b69a3fd6bd4dd717875
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: intg-countgate-plan-20260830 @ sha256 6eee9b30a1d97e567579510ef6dc9de58399ec09f5c7b583e79442e8b437388d
BASE: observation run head 77eea8bdf1d43562f2bd975472256479d60ece46 on local main; unchanged; 29acc6c and 81066ef are ancestors
BRANCH: none — no branch and no commit; local main remains at 77eea8bdf1d43562f2bd975472256479d60ece46
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: master.master-planner, master.master-reviewer, operator, m-3.planner, m-3.implementer, m-4.planner
SUBJECT: STOP UP — CG-R5 inventory and all five macOS source XMLs are green, but the required unfiltered CTest scout has a non-platform `harness-selftest` red from the ambient credential tripwire; execution-not-amendment requires an m-3 ruling before Linux observation or any workflow byte

## Exact stop and completed preflight

The `221146` token was received at sha256 `f26811c1e3389cdc6b993c4fb4f8eb57b2fef443db4855a00fc944330a08b033`, with a bare own-line implementation token, `FROM: intg.pair-planner`, and sole acting addressee `TO: intg.pair-implementer`. The plan and sealed design re-hash equal to `6eee9b30a1d97e567579510ef6dc9de58399ec09f5c7b583e79442e8b437388d` and `0099d1cf4aeb39f3732e823657ec0b78434f6a638db70b69a3fd6bd4dd717875`. Workflow and `CMakeLists.txt` matched the rev3 baseline hashes before observation.

Task 1 Steps 0–2 passed at the one captured run head:

```text
run head       77eea8bdf1d43562f2bd975472256479d60ece46
81066ef        ancestor = yes
29acc6c        ancestor = yes
index          empty
workflow diff  empty
evidence home  /var/folders/hq/f0qq8v_103q9y8prfn20rzx80000gn/T//countgate-evidence-nFlU1b
CG-R5 linked targets, exactly five:
  biv_subprocess_tests
  biv_repo_git_tests
  biv_repo_engine_tests
  biv_tests
  biv_probe_tests
```

An initial BSD `awk` extraction attempt had a character-class syntax error and produced an invalid empty comparison. It caused no observation or repository mutation. The corrected linkage-based extraction returned the exact approved five-target set before any source XML run.

## Five macOS source observations

Run id `macos-20260905T053038Z-77eea8bdf1d4`; configure rc 0, build rc 0, and every binary rc 0. Each tuple below is read from that binary's own completed XML, with no arithmetic:

```text
biv_subprocess_tests  successes=12  failures=0 expectedFailures=0 skips=0  xml_sha256=d4b141e21a4fefc58358d263fa58d8c941c95a8ed78be498654acd828648186c
biv_repo_git_tests    successes=6   failures=0 expectedFailures=0 skips=0  xml_sha256=86076d9b4d48de14cc253a7d2ef1d64ffb1f557b4476513559e59b753e0ef8da
biv_repo_engine_tests successes=60  failures=0 expectedFailures=0 skips=0  xml_sha256=2b5d15ad87423dd17437f7f8960508f7064f859fa743b45d52c56a99f8a93e8a
biv_tests             successes=418 failures=0 expectedFailures=0 skips=3  xml_sha256=cb9941b8d300644e144935db492796a5f6f95d3b01815646adbaf5848430713f
biv_probe_tests       successes=25  failures=0 expectedFailures=0 skips=0  xml_sha256=196705105ab15dd0c7e9df6e957d748b1c7e543f9bb01bff60a06856f57aa4c5
```

The `biv_tests` skipped-name set is byte-identical to the existing workflow `expected_skips` membership. No skip membership was adjusted.

## Blocking scout result

The plan's literal unfiltered command ran once and completed:

```text
ctest --preset ci-macos --output-on-failure
scout rc = 8
89% tests passed; 2 failed of 19
harness-selftest: 119 failed, 895 passed
safety-hardening: readelf unavailable
scout-macos.log sha256 = 979c7a293e4903c274dd84228bc4ec12c108ab283f8bb6a97158405e462cb8b5
```

`safety-hardening` is directly explained by a macOS platform-instrument absence and is a justified `-E` candidate. `harness-selftest` is not: its failures repeatedly report `ScenarioResult(... detail='credential-env:ANTHROPIC_API_KEY' ...)`, because the plan's unfiltered scout inherited the host variable name. That is a host-environment credential tripwire, not an absent instrument. The locked instruction says any such red is a FINDING and STOP; it does not authorize this seat to rerun under `env -u`, exclude the row, amend the scout, or interpret the red away. No secret value entered any command or artifact.

## No-mutation proof and required ruling

Task 1's observation-boundary proof is green:

```text
status-initial.txt sha256         fbf103180652d03846545754546a457eb7fa74d491b68acebc0f27bda83e75d3
status-post-observation.txt sha256 fbf103180652d03846545754546a457eb7fa74d491b68acebc0f27bda83e75d3
status snapshot diff              empty
HEAD                              unchanged at 77eea8bdf1d43562f2bd975472256479d60ece46
index                             empty
workflow diff                     empty
```

Required ruling through m-3: specify whether the macOS scout is to run in a sanitized environment, or otherwise rule the non-platform `harness-selftest` red and the lawful selection semantics. Because filing the ruling chain may move docs-lane `main`, the safe resume is the plan's own rule: restart at Task 1 Step 1 on the then-current head and re-observe; never rebase or cherry-pick.

## Explicit NOT-DONE

- No Linux observation or container act.
- No transcription table; only the five macOS source cells exist.
- No workflow, product, test, CMake, schema, harness, or documentation edit.
- No stage, commit, merge, push, fetch, pull, PR, remote CI, publication, deployment, seal, release, reset, revert, branch deletion, worktree removal, or cleanup.
- No m-3 seven-point landed-byte review requested because there is no landed sha.

SCOPE_DIFF:
- .github/workflows/s2-harness.yml -> in, untouched due STOP
SCOPE_DIFF_RESULT: all-in
ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: yes — ambient credential variable name detected by the scanner; no value read or exposed
- migration/backfill/destructive-write/canonical-data-repair: no
- money/inventory/orders/planning/accounting/trust-critical-state: no
- AI-or-automation-acts-downstream: no
- worker/scheduler/queue/retry/async-side-effect: no
- cross-repo/service-contract/generated-schema/shared-API-event: yes — sealed cross-repo m-3 count-gate design
- user-visible-control-with-materializer/downstream-consumer: no
- test-runtime-role-mismatch: yes — literal local scout inherits an ambient credential variable absent from the intended CI environment
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: yes — exclusion or sanitation is deliberately not inferred
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: none
- valid_waiver: no

ACTIONS_GIT_REF: none — main remains 77eea8bdf1d43562f2bd975472256479d60ece46; no workflow byte or ref moved; this engine-filed STOP report remains uncommitted per the pair-planner's docs-lane freeze until a landed sha returns
RELAY_LINT: engine-rendered submission; per-file lint rides daemon admission; exact-file lint and engine body-hash verification follow filing
FINAL_GIT_STATUS_SHORT: before filing, byte-identical to the inherited 36-row snapshot at sha256 fbf103180652d03846545754546a457eb7fa74d491b68acebc0f27bda83e75d3; after filing, only the engine-updated intg INDEX and this rendered STOP relay are additional own-seat rows, intentionally uncommitted under the dispatch freeze
