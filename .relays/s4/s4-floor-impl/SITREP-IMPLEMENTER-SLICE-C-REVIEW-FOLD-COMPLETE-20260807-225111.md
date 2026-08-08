## SITREP — Slice C review fold complete and republished at exact one-commit head ec9a2db; BL-1..BL-7 closed; host suite green; local Linux substitute completed with disclosed environment deltas

ROLE: Implementer
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-floor-impl-2-c-review-fold-complete
PARENT_DISPATCH_ID: s4-floor-impl-2-c-review-fold
RUN_ID: s4
TASK_ID: C
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — the requested fold and authorized draft re-publication are complete; targeted planner re-check, merge, release, and deployment remain outside this seat
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/REVIEW-FOLD-PLANNER-SLICE-C-PANEL-DISPATCH-20260807-212042.md
FROM: s4-floor.implementer
TO: s4-floor.planner
CC: s4.orchestrator-planner, operator
SUBJECT: DONE_WITH_CONCERNS — all seven in-universe panel blockers are closed at ec9a2db; exact-head host suite is green; local Ubuntu amd64 workflow substitute and controls completed; draft PR #22 republished; Actions, merge, and release remain held

DONE_WITH_CONCERNS

## Summary and exact publication state

The complete BL-1..BL-7 review fold is published on draft PR #22:

- PR: https://github.com/iwnlcern/bivpak/pull/22
- branch: `s4-floor/c-consent-no-carrier`
- exact amended head: `ec9a2db2cfe55191f99efbcf12902a79d99e159e`
- exact parent: `798526c5c68c4251cc088bcf922fbee798ed8b79`
- topology: exactly one commit over the parent
- required subject: `feat(open): stage consent-no sessions with provenance sidecar`
- final range: 24 paths, 1,661 insertions, 61 deletions
- fold delta from reviewed head `eadc88f`: 13 paths, 420 insertions, 156 deletions
- implementation worktree: clean before and after immutable publication

The remote update used an exact lease on reviewed head
`eadc88f89cd0eeeea0b9e5e0eb8a1577bed0d67e`; the remote and draft PR now resolve to
`ec9a2db2cfe55191f99efbcf12902a79d99e159e`.

GitHub Actions was not invoked, queried, rerun, or managed. The standing Ubuntu 24.04
`linux/amd64` Docker substitute ran only after implementation, review folding, the
sole commit, and the host suite were complete. No merge, release, or deployment action
was performed.

## FOLD_SCOPE discipline

Before any fold edit, the required scope was written to:

`.superpowers/sdd/2026-08-05-s4-floor-fold-plan/slice-c-review-fold-scope.md`

Its SHA-256 is
`7a17ad14e1f6027552dcca3c1c181beada7eac62eee8e8f22d59eb398276d151`.
It maps every BL-1..BL-7 edit to the 13 fold paths and explicitly excludes the routed
`open.cpp` defense, the held Claude layout contract, rejected performance work, and
optional minors. The final fold path set matches that scope exactly.

## BL-1..BL-7 disposition

### BL-1 — pre-planted staging carrier: CLOSED

`run_session_installs` now performs one preflight containment check before either
adapter can write. Any pre-existing `.biv/agents` carrier — including a pre-planted
manifest or any other foreign member — produces `ContainmentRefused` rows with reason
`foreign_staging_carrier`, no errno detail, zero adapter calls, zero new staged bytes,
and byte-for-byte preservation of the foreign carrier.

The routed defense-in-depth extract filter in `open.cpp` remains untouched and held at
the orchestrator/operator boundary, as directed.

### BL-2 — disabled tree proof: CLOSED

All three consent-no scenarios again declare `"tree": true`. The harness now accepts
an additive `tree_allowed_extra_roots` list and validates each entry as a normalized
relative root. The three scenarios admit exactly `.biv/agents`; comparison ignores
that root, its descendants, and only the directory ancestors needed to reach it.
Sibling drift such as `.biv/foreign.txt`, source-tree drift, a missing staged carrier,
or a wider undeclared root remains red. Coverage classes A/B/C are active again.

### BL-3 — publish containment classification: CLOSED

The sidecar publication-failure path now uses the same `install_failure_reason`
classification as sibling install failures. A containment failure produces
`ContainmentRefused` / `containment_refused` and carries no ambient errno symbol.
Tests now seal the corrected classification instead of the former `error`/`EEXIST`
shape.

### BL-4 — applied rewrite-pair provenance: CLOSED

`InstallResult` now carries `pair_set_applied`. Each adapter returns its actual
`rewrite::derive_pair_set` result; orchestration aggregates those exact pairs into the
sidecar. Cross-flavor WSL coverage proves the four derived origin spellings and a
second record's pair are all present, rather than the prior synthetic single pair.

### BL-5 — disclosure detail preservation: CLOSED

Publication failure now merges the failure classification with any existing staged-row
detail. A staged row retaining `non_utf8_skipped=1` keeps that disclosure through the
failure flip; containment classification remains errno-free.

### BL-6 — Claude long-key cohort failure: CLOSED

The consent-no Claude project-key cap is evaluated per record. An over-cap origin
fails only its own record while a benign sibling stages successfully with its ID map
and artifacts intact.

### BL-7 — test-strength gaps: CLOSED

The fold adds all three requested falsifiers:

- whole host-store `regular_files` sweeps replace sampled sentinel comparisons;
- a staged result carrying an Activation proves core orchestration does not activate
  consent-no bytes;
- a real multi-artifact Claude publication failure proves every staged artifact is
  disclosed, not merely one path per session.

## Fold paths

The fold from `eadc88f..ec9a2db` changes exactly:

- `harness/bivharness/compare.py`
- `harness/bivharness/scenario.py`
- `harness/scenarios/open-consent-no.json`
- `harness/scenarios/open-consent-per-agent.json`
- `harness/scenarios/open-deny-default.json`
- `harness/selftest/test_compare.py`
- `src/adapters/adapter.hpp`
- `src/adapters/claude_code/install.cpp`
- `src/adapters/codex/install.cpp`
- `src/core/open/sessions.cpp`
- `tests/test_adapter_claude_install.cpp`
- `tests/test_adapter_codex_install.cpp`
- `tests/test_sessions.cpp`

No `.github/**`, `src/core/open/open.cpp`, routed Claude origin-layout, CANON-2.6
reader/repack, merge, release, or deployment byte is present. `git diff --check
HEAD^..HEAD` passes.

## RED to GREEN and mutation receipts

The fold was driven by focused failures before implementation:

- BL-2 RED: `test_compare.py` produced 6 failures because `compare_trees` accepted
  only its original three arguments; GREEN: 15/15.
- BL-4 RED: the C++ focused target did not compile because
  `InstallResult::pair_set_applied` did not exist.

Final focused proof at the committed bytes:

- adapter/session fold filters: 343 assertions in 12 cases, PASS;
- compare-tree selftests: 15/15, PASS;
- full harness selftest on the host: 975 passed;
- scoped exact-head re-review: PASS, with no Critical, Important, or Minor finding.

Falsifying mutations were applied only transiently and exactly inverted:

| Finding | Mutant RED | Inverse GREEN |
|---|---|---|
| BL-1 preflight | disabled preflight: 8 failures, including one adapter call and carrier mutation | 24 assertions / 1 case |
| BL-3 + BL-5 handler | restored old publish handler: 7 failures for wrong row/reason and lost detail | 41 assertions |
| BL-4 pair propagation | dropped propagated pairs: sidecar empty instead of 5 exact pairs | 52 assertions |
| BL-6 long-key scope | restored cohort-wide cap: benign sibling failed and lost ID map | 12 assertions |
| BL-7 activation | forwarded staged Activation: `activation.empty()` became false | 33 assertions |
| BL-7 disclosure | truncated staged caveats: 3 disclosed instead of 5 | 41 assertions |

No mutant byte remains in the commit.

## Host suite at exact amended head

Fresh command:

`ctest --preset dev -E '^safety-hardening$' --output-on-failure`

Result at exact `ec9a2db`:

- exit 0;
- 100% selected tests passed;
- 0 failed out of 14;
- `biv_tests`: 248.55 seconds;
- `harness-selftest`: 9.10 seconds;
- `harness-e2`: 164.70 seconds;
- `safety-build-werror`: PASS;
- total: 424.96 seconds;
- three configured skips: ASan/UBSan, tidy/analyzer, and fuzz smoke.

## Local Ubuntu 24.04 amd64 workflow substitute

The disposable proof environment reproduced the Linux job on:

- `ubuntu:24.04`, `--platform linux/amd64`;
- observed kernel architecture `x86_64`;
- exact detached head `ec9a2db2cfe55191f99efbcf12902a79d99e159e`;
- Python 3.12.3, CMake 3.28.3, GCC 13.3.0;
- writable `/mnt/c/tmp`;
- all eight workflow-pinned LLVM packages checked by SHA-256, package name, exact
  version, and amd64 architecture before install;
- installed clang-tidy exact Debian version
  `1:22.1.8~++20260613092238+e80beda6e255-1~exp1~20260613092253.78`, reporting
  LLVM 22.1.8.

Configure and build completed successfully with
`BIVHARNESS_REQUIRE_CLANG_TIDY=ON`.

The canonical integrated CTest result is honestly non-green under Docker Desktop's
amd64 emulation:

- 15 JUnit rows recorded;
- 10 rows ran and passed;
- `biv_tests`: 261 of 262 cases and 6,895 of 6,896 assertions passed; the sole failure
  is the established Rosetta invalid-executable semantic difference in
  `version probe does not fall back to PATH when a pinned executable cannot spawn`;
- `harness-selftest`: 968 passed, 3 failed, 3 skipped in the canonical run; repeated
  runs established the exact four Docker-overlay filesystem mutation sentinels as the
  varying set;
- `generated_envelope_conforms`: dependency-not-run after `biv_tests`;
- ASan/UBSan and fuzz smoke: workflow-configured skips;
- canonical CTest exit: 8.

All non-environment workflow rows passed, including:

- `open_no_rewrite_gate`;
- core adapter purity;
- version-floor mirror;
- errno table and probe-envelope schema;
- `harness-e2`;
- `safety-build-werror`;
- `safety-hardening`;
- `safety-tidy-analyzer` in 34.75 seconds.

The JUnit tidy gate found exactly one `safety-tidy-analyzer` row, status `run`, with
no skip/failure/error child: PASS.

Narrow substitution controls passed:

- Catch2 excluding only the Rosetta case: 261 cases, 6,886 assertions, all PASS;
- harness excluding exactly the four known same-size rewrite/end-of-enumeration
  mutation sentinels: 967 passed, 3 configured skips, 4 deselected;
- generated-envelope document against the Draft 2020-12 schema: direct PASS.

The workflow count gate is independently and honestly red: its XML observed
`261 successes / 1 failure / 0 expected failures / 0 skips`, while the workflow still
requires `223 / 0 / 0 / 0`. `.github/**` ownership remains routed upstream and hard
OUT for Slice C, so no count-gate edit was made.

These controls diagnose the local Docker/Rosetta substitution boundary; they are not
claimed as native GitHub-hosted x86_64 proof.

## Cleanup and preservation

Only task-named resources were disposed after evidence capture: container
`bivpak-s4-ec9a2db-ci`, volume `bivpak-s4-ec9a2db-work`, the exact-head bundle,
pinned-asset copies, and the temporary format-recovery worktree. Temporary filesystem
copies were moved to the macOS Trash and remain recoverable. No unrelated container,
volume, worktree, branch, or working-tree byte was removed.

## Remaining held boundaries and requested action

The in-universe fold is complete. Remaining items are unchanged:

- `open.cpp` extract-side `.biv` defense remains held/routed; BL-1 closes the live
  Slice-C write-before-refusal vector without crossing that boundary;
- the Claude origin-path-keyed layout contract remains held/routed as a sealed A9
  decision;
- the CANON-2.6 sidecar reader and re-pack-exact fixtures remain Slice B2's;
- the stale workflow count gate remains routed upstream;
- merge, release, and deployment remain the operator's alone.

Planner should perform the dispatched targeted re-check at exact amended PR head
`ec9a2db2cfe55191f99efbcf12902a79d99e159e`. No full re-panel is requested unless the
planner determines the blast radius changed.

ACTIONS_GIT_REF: implementation exact head ec9a2db2cfe55191f99efbcf12902a79d99e159e, exact parent 798526c5c68c4251cc088bcf922fbee798ed8b79, one commit and 24 total range paths; fold delta eadc88f89cd0eeeea0b9e5e0eb8a1577bed0d67e..ec9a2db2cfe55191f99efbcf12902a79d99e159e is 13 scoped paths; origin/s4-floor/c-consent-no-carrier and draft PR #22 are at ec9a2db; this relay and its append-only INDEX row ride one later explicit-path docs-lane commit whose SHA lands in repository history after filing
FINAL_GIT_STATUS_SHORT: implementation worktree clean at the published exact head; main docs lane was clean before this relay and INDEX append; disposable Docker and temporary fold-recovery resources were removed or moved to recoverable Trash after evidence capture

CARRY LIST:
- .relays/s4/s4-floor-impl/SITREP-IMPLEMENTER-SLICE-C-REVIEW-FOLD-COMPLETE-20260807-225111.md → s4-floor.planner
- https://github.com/iwnlcern/bivpak/pull/22 at exact ec9a2db2cfe55191f99efbcf12902a79d99e159e → targeted re-check only; merge/release held
- `src/core/open/open.cpp` extract-side `.biv` defense and Claude origin-layout contract → remain held/routed upstream
- CANON-2.6 staging-sidecar reader and re-pack-exact fixtures → Slice B2 remains the named downstream owner
- `.github/workflows/s2-harness.yml` stale Catch2 count gate → hard OUT, routed upstream
