## SITREP — Slice E Stage 0 complete at two-commit test-only head `dca6b7d`; four behavioral REDs captured before green compatibility controls; publication held

ROLE: Implementer
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-floor-slice-e-stage0-complete
PARENT_DISPATCH_ID: s4-floor-slice-e-stage0-impl
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — Stage 0 is complete; Stage 1 remains blocked on the m-1 receipt and a fresh Planner dispatch; publication, merge, seal, deployment and release remain held
DESIGN_DOC_ID: m2-addendum-12-transitive-collect-mono-gate-20260812
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m2-addendum12-29a5b3a3-lock-20260812
TARGET_DESIGN_SHA256: 29a5b3a3abb6777af70a1c959728f4f61731489a1735773e81713b5aa3ea3adb
TARGET_DESIGN_COMMIT: 6eeeb157be249792d61774016485d97c303e2c8f
PLAN_LOCK_ID: s4-floor-slice-e-plan-20260812
IN_REPLY_TO: .relays/s4/s4-floor-impl/IMPL-PLANNER-SLICE-E-STAGE0-DISPATCH-IMPL-TOKEN-20260812-232912.md
FROM: s4-floor.implementer
TO: s4-floor.planner
CC: s4.orchestrator-planner, operator, s4.orchestrator-reviewer, master.orchestrator-planner, m-2.planner, m-1.planner
SUBJECT: DONE_WITH_CONCERNS — Slice E Stage 0 complete at unpublished local head dca6b7d with four independently observed behavioral REDs, all compatibility controls green, no production byte and no remote CI; Stage 1 and release remain held

DONE_WITH_CONCERNS

## Exact result and publication state

Stage 0 is complete on the isolated local branch cut from the dispatched base:

- branch: `s4-floor/slice-e-stage0`
- worktree: `/Users/jack/.config/superpowers/worktrees/bivpak/s4-floor-slice-e-stage0`
- dispatched base and merge-base: `0db8fdd8424d27aad2c547614e9ebb95621a2794` (`origin/main`)
- exact RED commit: `2f39277` — `test(slice-e): add stage0 behavioral reds`
- exact control/head commit: `dca6b7d4c2bbcfeaabddff9e03c2698e4e6a955c` — `test(slice-e): add stage0 compatibility controls`
- topology: exactly two ordered commits over the dispatched base; REDs precede controls
- PR: none
- remote branch: none
- implementation worktree: clean at final evidence capture

Publication is held exactly as dispatched. No push, `gh pr create`, `gh pr ready`,
GitHub Actions invocation/inspection/rerun, merge, seal, deployment, release, tag or
artifact publication occurred.

## Stage-0 deliverable

The branch adds only tests and committed sanitized fixture data:

- `FX-A12-1`: three-level `R <- P <- C` collection requires `C`, its artifact and
  its marker bytes to be carried by `R`;
- `FX-A12-3`: a rootless component with an off-cycle descendant sorting first
  requires a cycle-member primary, exact-once artifact carriage, a warning naming
  the omitted cycle edge, and a hand-derived retained graph in which every chain
  reaches the primary;
- `FX-A12-4`: an uncarryable descendant represented by a refused symlink artifact
  requires a warning naming that descendant while the root remains collectable;
- `FX-A12-6`: install of a grandchild whose bytes name immediate parent `P` requires
  validation against `P`, not only mapped root `R`;
- `FX-A12-2` arm 1: the two-level Codex parent/child archive members are byte-identical
  to their disposable source rollouts;
- `FX-A12-7`: Claude's flat `subagents/` enumeration remains unchanged;
- three actual shipped-CLI Claude controls cover flat bare-hex, flat slug-hex, and
  nested `subagents/workflows/<wf>/` paths with realistic unprefixed parent references,
  prefixed filenames, restored marker-byte reads and mapped-session containment;
- fixture data only, with no test compiled against the absent m-1 member, is present
  for `1b`, `4a` and `5`.

Every executable Stage-0 case installs a `ScopedPackDiscoveryEnv` equivalent for
`HOME`, `CLAUDE_CONFIG_DIR`, `CODEX_HOME` and `CODEX_SQLITE_HOME`, and checks its
store/workspace/destination roots under a disposable sandbox. Credential-shaped
`auth.json` decoys are asserted absent from collected streams, archive bytes,
member reads and restored output. No live `~/.claude` or `~/.codex` store was read
or mutated.

## Four independently observed behavioral RED receipts

Each case compiled, selected, ran and failed an assertion on the dispatched base
behavior before the RED commit was filed. Catch2 returned `42` for every individual
selection.

### `FX-A12-1`

```text
Filters: "*FX-A12-1*"
root.child_ids:
  { "019fa120-...-0102" }
  != { "019fa120-...-0102", "019fa120-...-0103" }
sorted_artifacts(root): parent + direct child only; leaf artifact absent
streamed_record_text(root).find("SLICE_E_LEAF_1") == npos
test cases: 1 | 0 passed | 1 failed
assertions: 13 | 10 passed | 3 failed
```

### `FX-A12-3`

```text
Filters: "*FX-A12-3*"
REQUIRE(report->sessions.size() == 1U)
with expansion: 0 == 1
test cases: 1 | 1 failed
assertions: 2 | 1 passed | 1 failed
```

The remaining assertions are compiled behind that cardinality gate and bind the full
post-fix contract: primary `...0310` is a cycle member even though descendant `...0301`
sorts first; all three artifacts occur exactly once; warning order names omitted edge
`...0310 -> ...0320`; each retained fixture chain reaches `...0310`.

### `FX-A12-4`

```text
Filters: "*FX-A12-4*"
CHECK(any warning names "019fa120-...-0402")
with expansion: false
test cases: 1 | 1 failed
assertions: 10 | 9 passed | 1 failed
```

### `FX-A12-6`

```text
Filters: "*FX-A12-6*"
CHECK(outcome == staged)       with expansion: 2 == 1
CHECK(reason == nullopt)       failed
CHECK(detail == nullopt)       failed
CHECK(id_map.size() == 1U)     with expansion: 0 == 1
test cases: 1 | 0 passed | 1 failed
assertions: 15 | 11 passed | 4 failed
```

The fresh aggregate RED selection confirms the intended boundary and no extra Stage-0
RED case:

```text
./build/dev/biv_tests '[slice-e-red]' --reporter console
test cases: 4 | 0 passed | 4 failed
assertions: 56 | 47 passed | 9 failed
exit: 42
```

## Green compatibility controls

Fresh exact-head command:

```text
./build/dev/biv_tests '[slice-e-control]' --reporter console
All tests passed (280 assertions in 3 test cases)
```

The three CLI shapes execute as three dynamic sections inside one case. Their fixture
covers the axes flat bare-hex, flat slug-hex and nested workflow bare-hex. It does not
claim to reproduce a corpus distribution. The locked provenance remains `309` bare-hex
+ `269` slug-hex of `578`, with bare-hex the majority; the withdrawn all-slug claim
reaches no fixture. No live-store population was remeasured.

## Fresh macOS verification at exact head

The full runnable Catch2 product suite excluding exactly the four deliberate Stage-0
RED tags is green:

```text
./build/dev/biv_tests '~[slice-e-red]' --reporter console
test cases: 388 | 386 passed | 2 skipped
assertions: 11837 | 11837 passed
exit: 0
```

The CTest ancillary run excluding `biv_tests` passed open-no-rewrite, adapter purity,
version-floor mirror, errno, probe schema, generated-envelope schema, reset,
`harness-selftest`, `harness-e2` (201.07 seconds), and build-with-Werror. The three
preset unavailable rows (ASan/UBSan, pinned tidy/analyzer, fuzz targets) skipped. The
sole selected macOS failure was `safety-hardening: readelf unavailable`, an environment
limitation already known for this preset. After reset, the generated detail envelope
was recreated by its named Catch2 producer and directly validated against the schema:

```text
All tests passed (2 assertions in 1 test case)
GENERATED_ENVELOPE_SCHEMA_PASS
```

The dispatch says local Ubuntu 24.04 `linux/amd64` Docker is not required for this
test-only stage unless a RED behaves differently there. All four REDs behaved as
designed on macOS, so Docker was not run. GitHub Actions was not invoked.

## Scope, invariants and hand-up measurement

`git diff --check 0db8fdd..dca6b7d` passes. The effective range contains 34 files and
697 insertions, all within the six authorized rows:

- `tests/test_adapter_codex_collect.cpp`
- `tests/test_adapter_codex_install.cpp`
- `tests/test_adapter_claude_collect.cpp`
- `tests/test_pack.cpp`
- `tests/test_cli.cpp`
- `tests/fixtures/slice-e/**`

An explicit whitelist check returned no `OUT_OF_SCOPE` path. `src/**`, `harness/**`,
`.github/**` and every other path are untouched; therefore no production output or
`collect()` value changed and no A3 anchor ceremony fired. D-5.5(a) at hand-up is
`git rev-list --count origin/main..0db8fdd` = `0`; `origin/main`, merge-base and the
dispatched branch-cut point all remain exact `0db8fdd`.

## Held boundary and requested action

Planner may review the local exact head `dca6b7d`. Stage 0 does not authorize or claim
Stage 1. The m-1 receipt remains a prerequisite, and any Stage-1 implementation needs
a fresh `DISPATCH IMPL` from the Planner. Publication, remote CI, merge, seal,
deployment and release remain held; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: local implementation head dca6b7d4c2bbcfeaabddff9e03c2698e4e6a955c over exact dispatched base 0db8fdd8424d27aad2c547614e9ebb95621a2794; ordered commits 2f39277 then dca6b7d; implementation worktree clean; no remote branch or PR; this report and its append-only INDEX row ride one later explicit-path docs-lane commit whose SHA lands after filing
RELAY_LINT: exact report passed before INDEX append and again with `--no-freshness`; `--index` reports only inherited line-222 timestamp inversion (`142630` precedes `142708`); `--relay-root --no-freshness` reports 232 inherited historical/root-interpretation errors, including INDEX-as-relay noise, known cross-repo design-lineage rows and the already-filed Stage-0 dispatch-parent interpretation; no error names this report. Append-only history was not rewritten
FINAL_GIT_STATUS_SHORT: implementation worktree clean at dca6b7d; coordination checkout carried unrelated untracked historical relay files before this report; none was modified, staged or committed by this seat

CARRY LIST:
- `.relays/s4/s4-floor-impl/SITREP-IMPLEMENTER-SLICE-E-STAGE0-COMPLETE-PUBLICATION-HELD-20260813-003112.md` -> `s4-floor.planner`
- local branch `s4-floor/slice-e-stage0` at exact `dca6b7d4c2bbcfeaabddff9e03c2698e4e6a955c` -> Planner review; publication held
- four assertion-level RED keys `FX-A12-1/3/4/6` -> Stage 1 only after m-1 receipt plus fresh Planner token
- macOS `readelf unavailable` hardening row -> environment disclosure; no Docker required by this Stage-0 token
- merge/seal/deployment/release -> held; release hold ABSOLUTE
