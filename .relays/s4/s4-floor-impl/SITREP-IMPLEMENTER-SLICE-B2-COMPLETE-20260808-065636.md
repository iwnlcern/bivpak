## SITREP — Slice B2 complete at exact one-commit head 54a6c54; torn-tail and CANON-2.6 reader/re-pack shipped; host suite green; local Linux substitute completed with disclosed environment deltas

ROLE: Implementer
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-floor-impl-2-b2-complete
PARENT_DISPATCH_ID: s4-floor-impl-2
RUN_ID: s4
TASK_ID: B2
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — implementation and authorized draft publication are complete; planner review, merge, release, and deployment remain outside this seat
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/IMPL-PLANNER-SLICE-B2-DISPATCH-20260808-010412.md
FROM: s4-floor.implementer
TO: s4-floor.planner
CC: s4.orchestrator-planner, operator
SUBJECT: DONE_WITH_CONCERNS — B2 is complete and published at 54a6c54; host suite and exact A3 ceremony are green; local Ubuntu amd64 substitute completed with bounded Docker/Rosetta exceptions; Actions, merge, and release remain held

DONE_WITH_CONCERNS

## Summary and exact publication state

Slice B2 is complete and published as draft PR #23:

- PR: https://github.com/iwnlcern/bivpak/pull/23
- branch: `s4-floor/b2-torn-tail`
- exact head: `54a6c54f9d12874123bb520b2598f1086931f70f`
- exact parent: `ec9a2db2cfe55191f99efbcf12902a79d99e159e`
- topology: exactly one commit over the dispatched parent
- subject: `feat(pack): collect torn tails and staged sidecars`
- range: exactly 13 authorized paths, 2,682 insertions, 123 deletions
- implementation worktree: clean at publication and final evidence capture

The remote branch and open draft PR both resolve to the exact head above. PR #23 is
stacked on Slice C draft PR #22; its GitHub base remains `main` for the repository's
current PR topology.

GitHub Actions was not manually invoked, rerun, or managed. The Ubuntu 24.04
`linux/amd64` Docker substitute ran only after implementation was complete. No merge,
release, or deployment action was performed.

## Implemented behavior

### Torn-tail A3.3

Both adapters implement the locked final-segment rule for JSONL artifacts:

- empty tail is retained verbatim;
- valid-JSON tail is retained with exactly one appended LF;
- invalid live tail is dropped exactly and records artifact plus exact byte count;
- invalid non-live tail is retained verbatim;
- interior segments are never inspected by the torn-tail rule.

Codex branch 3 is driven through production liveness derivation; branch 4 retains its
bounded seam. Every dropped fact becomes structured `TornTailDropped` warning data,
and the default-text and JSON CLI forms preserve the exact artifact and byte count.

Retained JSONL remains strict at install: an undecodable retained line refuses only its
own session with `verify-hits/undecodable_line`. The Codex publication-failure path now
preserves an earlier verify refusal reason and detail instead of overwriting it.
Claude raw `.txt` artifacts remain outside the JSONL rule.

### CANON-2.6 staging-sidecar reader and re-pack exactness

The collect side reads strict A9 staging sidecars without following symlinks, validates
sidecar/path containment, and fails closed on the pair-set contract. Staged records emit
the minted staged artifact identity while retaining the original provenance chain and
the `locator: staging` / `discovery_tier: staged` contract.

Canonical re-pack/install now works when staged or minted artifact identities differ
from the original provenance identity, including Codex parent-plus-children and the
Claude subtree. Installers rewrite and verify current artifact IDs and provenance IDs.
Rekeying remains restricted to sealed staged records (`locator=staging`,
`discovery_tier=staged`). Aggregate CANON fixtures cover all five members.

A staged record missing its version now fails immediately as
`ParseError/missing_staged_version`, before either adapter can emit a schema-1 manifest
or archive.

The Claude LLVM-tidy containment finding was closed with an executable runtime guard;
the protection no longer depends on a debug-only assertion.

## Scope and fences

The final commit changes exactly:

- `harness/bivharness/e3.py`
- `src/adapters/adapter.hpp`
- `src/adapters/claude_code/claude_code.cpp`
- `src/adapters/claude_code/install.cpp`
- `src/adapters/codex/codex.cpp`
- `src/adapters/codex/install.cpp`
- `src/core/pack/pack.cpp`
- `tests/test_adapter_claude_collect.cpp`
- `tests/test_adapter_claude_install.cpp`
- `tests/test_adapter_codex_collect.cpp`
- `tests/test_adapter_codex_install.cpp`
- `tests/test_cli.cpp`
- `tests/test_pack.cpp`

`src/core/manifest/manifest.*`, `.github/**`, new test translation units, and all other
harness files remain untouched. `git diff --check HEAD^..HEAD` passes.

## RED/GREEN and independent review

The implementation was driven through the dispatched branch fixtures and exact
retained-prefix controls. The final post-review focused set passes 245 assertions in
eight cases, covering both missing-version adapters, aggregate re-pack, staged installs,
Codex failure radius, containment controls, and CLI torn-tail warning output. The final
Claude targeted set passes 30 assertions.

The first independent final review found one Critical and two Important defects:
canonical re-pack identity handling, Codex refusal-detail preservation, and missing
staged-version emission. All three were reproduced and closed before publication.
The final independent review found no Critical or Important issue and independently
passed 44 relevant containment/staged assertions on a clean worktree.

One Minor remains disclosed: staged-sidecar artifact identity uniqueness is enforced
globally rather than keyed by `(agent, id)`. It does not weaken refusal behavior and was
not expanded into this locked slice.

## A3 four-check ceremony on both anchors

Both final source anchors were recaptured at the exact committed head:

- Claude source SHA-256:
  `046527fd56f815d2ea810c7b914aefee1f39792763f12c1725ed2d2089460f10`
- Codex source SHA-256:
  `da32ace63f48daa22addf78f669a2fb74878f00f71ace1c785ceda9999e36e4a`

The literals match `harness/bivharness/e3.py`. Nine owner mutations/inverses, the
pinned-anchor control, and the write-side exclusion control all pass: 11 checks total.
The `e3.py` recapture delta is exactly two insertions and two deletions; no anchor-set or
harness behavior was changed.

Ceremony burden disclosure: whole-file anchors require recapture even for changes that
do not move the guarded call sites, plus nine falsifying mutations/inverses and two
controls. That cost was paid independently on this final head rather than inferred from
an earlier slice.

## Host macOS suite at exact head

Fresh command:

`ctest --preset ci-macos --output-on-failure`

Result at exact `54a6c54f9d12874123bb520b2598f1086931f70f`:

- `biv_tests`: PASS in 417.55 seconds; 286 cases, with two expected WSL skips;
- open-no-rewrite, adapter purity, version-floor mirror, errno, schema, and generated
  envelope gates: PASS;
- `harness-selftest`: PASS in 4.68 seconds;
- `harness-e2`: PASS in 163.97 seconds;
- `safety-build-werror`: PASS in 2.43 seconds;
- ASan/UBSan, tidy/analyzer, and fuzz smoke: preset-configured skips;
- sole selected failure: `safety-hardening`, because `readelf` is unavailable on the
  macOS host;
- overall: 93%, 14 of 15 rows passed, total 590.07 seconds.

The product and all runnable cross-platform gates are green; the hardening row is
covered by the Linux substitute below.

## Local Ubuntu 24.04 amd64 workflow substitute

The disposable Docker proof used Ubuntu 24.04 under `--platform linux/amd64`, cloned
the exact detached head, built with GCC 13 and Werror, and verified all eight pinned
LLVM 22.1.8 amd64 assets by checksum, package name, version, and architecture.

The canonical integrated outcome is honestly non-green under Docker Desktop's
amd64/Rosetta and overlay-filesystem substitution:

- `biv_tests`: 285 of 286 cases and 7,386 of 7,387 assertions passed; the sole failure
  is `version probe does not fall back to PATH when a pinned executable cannot spawn`,
  whose invalid-executable spawn semantics differ under Rosetta;
- `harness-selftest`: 967 passed, 4 failed, 3 configured skips; the four failures are
  the established same-size in-place rewrite and end-of-directory-enumeration mutation
  sentinels under Docker's mounted/overlay filesystem;
- `harness-e2`: PASS in 1.04 seconds;
- `safety-build-werror`: PASS in 1.51 seconds;
- LLVM 22 tidy: all 28 project sources executed and passed in 38.96 seconds; the JUnit
  tidy row gate passed;
- `safety-hardening`: PASS;
- ASan/UBSan and fuzz smoke: workflow-configured skips;
- generated-envelope canonical row: dependency-not-run after the product failure;
- canonical result: `harness_job_rc=8`, `ctest_rc=8`, `tidy_gate_rc=0`.

The four canonical harness failures are exactly:

1. `test_file_reader_rejects_same_size_cross_chunk_in_place_rewrite`
2. `test_c1_zero_session_control_reds_on_file_inserted_at_scandir_stop`
3. `test_run_e3_session_inserted_at_scandir_stop_reds_c1_before_open`
4. `test_credential_scanner_detects_entry_added_after_directory_enumeration`

Narrow substitution controls diagnose those environment boundaries:

- Catch2 excluding only the Rosetta invalid-executable case: 285 cases and 7,377
  assertions, all PASS;
- harness excluding exactly the four Docker filesystem sentinels: 967 passed, 3
  configured skips, 4 deselected;
- generated-envelope document against its schema: direct PASS.

These controls are not claimed as native GitHub-hosted x86_64 proof.

## Stale workflow count gate

The workflow count gate remains independently red. It expects 223 successful Catch2
cases, while the canonical XML now contains 285 successes plus the one environment
failure. The gate exits 1. `.github/**` is hard OUT for B2, so no workflow byte was
changed; the existing upstream routing remains required.

No GitHub Actions workflow was manually started. This local suite is the instructed
Linux substitute, not authorization for CI management.

## Requested action and held boundaries

Planner should convene the dispatched review panel at exact PR head
`54a6c54f9d12874123bb520b2598f1086931f70f`. The implementation is ready for that
review. Merge, release, deployment, `.github/**` repair, and resolution of the disclosed
Minor remain held.

ACTIONS_GIT_REF: implementation exact head 54a6c54f9d12874123bb520b2598f1086931f70f, exact parent ec9a2db2cfe55191f99efbcf12902a79d99e159e, exactly one commit and 13 authorized paths; origin/s4-floor/b2-torn-tail and draft PR #23 are at the exact head; this relay and its append-only INDEX row ride one later explicit-path docs-lane commit whose SHA lands in repository history after filing
FINAL_GIT_STATUS_SHORT: implementation worktree clean at the published exact head; main docs lane was clean before this relay and INDEX append; no unrelated working-tree byte was modified

CARRY LIST:
- `.relays/s4/s4-floor-impl/SITREP-IMPLEMENTER-SLICE-B2-COMPLETE-20260808-065636.md` → `s4-floor.planner`
- https://github.com/iwnlcern/bivpak/pull/23 at exact `54a6c54f9d12874123bb520b2598f1086931f70f` → dispatched review panel; merge/release held
- `.github/workflows/s2-harness.yml` stale Catch2 count gate → hard OUT, remains routed upstream
- staged-sidecar uniqueness keying Minor → disclosed, not expanded into locked B2
