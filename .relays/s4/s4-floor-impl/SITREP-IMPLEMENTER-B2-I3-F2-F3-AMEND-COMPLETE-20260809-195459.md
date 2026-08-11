## SITREP — complete B2 amend landed at one-commit head 6a8ea75; I-3/F2/F3 addressed, host and local Linux bars complete, PR #23 republished for fourth re-panel

ROLE: Implementer
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-floor-impl-2-b2-i3-amend-complete
PARENT_DISPATCH_ID: s4-floor-impl-2-b2-i3-amend-fold
RUN_ID: s4
TASK_ID: B2
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — implementation and authorized draft publication are complete; the fourth targeted re-panel, merge, release, and deployment remain outside this seat
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/IMPL-PLANNER-B2-I3-F2-F3-AMEND-DISPATCH-IMPL-TOKEN-20260809-191503.md
FROM: s4-floor.implementer
TO: s4-floor.planner
CC: s4.orchestrator-planner, operator
SUBJECT: DONE_WITH_CONCERNS — complete B2 amend at 6a8ea75 closes I-3 key-arm leak and F2 self-refusal, supplies F3 kill-power, passes review/host/local-Docker bars, and republishes PR #23; fourth re-panel requested; merge/release held

DONE_WITH_CONCERNS

## Exact result and publication state

The complete B2 amend is republished as draft PR #23:

- PR: https://github.com/iwnlcern/bivpak/pull/23
- branch: `s4-floor/b2-torn-tail`
- exact head: `6a8ea75a2d7ae072839940e69b16f6393c80ac32`
- exact parent: `ec9a2db2cfe55191f99efbcf12902a79d99e159e`
- topology: exactly one commit over the dispatched parent
- subject: `feat(pack): collect torn tails and staged sidecars`
- implementation worktree: clean after amend, verification, and publication

The remote branch and open draft PR were verified at the exact head after a
force-with-lease update from the observed remote head `f9675ea`. GitHub Actions
was not manually invoked, rerun, or managed. All implementation and both local
verification environments completed before publication. No merge, release, or
deployment action was performed.

## Implemented behavior

**I-3, symmetric JSON key handling.** `JsonValueRewriter` now decodes object
keys, applies the same path and id replacement pipeline used for string values,
and re-encodes the result. `rewrite_jsonl` enables key rewriting and
`verify_scan` decodes and scans both keys and values. The already-ruled
longest-source-first path precedence therefore applies to keys as well. The
Claude lock-in assertion was inverted, and the matching Codex assertion found
by the wider cohort was inverted as the necessary consequence of the shared
rule. Numeric and other non-string JSON values remain byte-shaped as before.

**F2, Codex parent rewrite symmetry.** After all admitted sessions are
prepared, a session carrying a parent id receives an id-map entry only when a
matching parent is actually present in `prepared_sessions`; its
`parent_thread_id` then rewrites to that parent's installed id. This uses the
repository's real manifest invariant: an in-image parent is represented by the
matching session row with no `parent_in_image` marker, while a not-in-image
parent carries `false`. No matching prepared parent means no mapping, so the
pre-flagged not-in-image self-reference/disclosure definition was neither
answered nor changed.

The collect-realistic F2 fixture now includes the real `parent_thread_id`,
requires both parent and child installed, checks zero child origin-id hits, and
checks the child's published rollout contains the parent's installed id rather
than its origin id. A separate version-refused origin row preserves direct
manifest-parent union kill-power without electing an outcome for an admitted
not-in-image child.

**F3, Codex child-id kill-power.** The new cross-session falsifier sources the
child id from a version-refused, nonprepared manifest row and requires a
recipient carrying that id to refuse with `origin_id_hits>0`. It therefore
depends on the direct all-record child-union insertion rather than the admitted
session's prepared-origin fallback.

`rewrite_common.hpp` did not need a declaration change. No public surface,
rewrite radius/domain, manifest byte, collector, Claude installer, R-4.8 work,
or disclosed Minor changed.

## Strict RED to GREEN and mutation proof

Before the production fix:

- the common key-rewrite/decoded-key test failed two of ten assertions;
- the Claude real-install key test failed two of twelve assertions;
- the collect-realistic Codex parent case failed its legitimate child's
  installed and zero-origin-hit assertions;
- the F3 child-union test was baseline-green because production was already
  correct, then turned RED with four failed assertions when the direct Codex
  manifest-child union insertion alone was removed; restoring the insertion
  returned it to GREEN.

After the minimal production edits, all four focused cases passed. The wider
shared-rewrite and both-adapter install cohort then exposed the matching Codex
key lock-in assertion; after its required inversion the final cohort passed 453
assertions across 30 cases.

## Scope, one-commit law, and A3

The amend wave `f9675ea..6a8ea75` changes exactly four authorized paths:

- `src/adapters/codex/install.cpp`: 12 insertions;
- `src/adapters/rewrite_common.cpp`: 17 insertions and 10 deletions;
- `tests/test_adapter_claude_install.cpp`: 15 insertions and five deletions;
- `tests/test_adapter_codex_install.cpp`: 159 insertions and four deletions.

`src/adapters/rewrite_common.hpp` was authorized conditionally but remained
unchanged. `git diff --check f9675ea..6a8ea75` passes. The four paths were
staged explicitly and amended into the existing B2 commit with its subject
preserved. The complete B2 head remains exactly one commit over `ec9a2db`.

The A3 mechanical check was run against the amend wave: neither anchored
collector (`src/adapters/codex/codex.cpp` nor
`src/adapters/claude_code/claude_code.cpp`) changed, so anchor recapture did not
re-fire. No anchored hash is asserted without that check.

## Scoped independent re-review

The cold read-only reviewer first caught an Important error in an intermediate
attempt that treated optional `parent_in_image` engagement as its boolean
value. Repository manifest validation then established the stronger invariant:
`true` is invalid, in-image is a matching row with the marker absent, and
not-in-image is `false`. The intermediate guard and invalid fixture were
corrected to match on an actually prepared parent instead.

The reviewer re-read the stable final delta and returned no Critical or
Important findings. It confirmed I-3 key decode/rewrite/verify symmetry, valid
F2 parent mapping without choosing the missing-parent semantic cell, F3's
nonprepared-row kill-power, exact four-file effective scope, unchanged header,
and clean `git diff --check`. The gate passed for amend and post-review suites.

## Fresh post-review macOS host suite

Command at exact committed head:

```sh
ctest --preset ci-macos -E '^safety-hardening$' --output-on-failure
```

Result:

- `biv_tests`: PASS in 320.76 seconds;
- `harness-selftest`: PASS in 4.84 seconds;
- `harness-e2`: PASS in 178.12 seconds;
- `safety-build-werror`: PASS in 0.59 seconds;
- ASan/UBSan, tidy/analyzer, and fuzz smoke: preset-configured skips;
- overall: 100%, 14 of 14 selected rows passed, zero failures;
- total: 505.71 seconds.

## Local Ubuntu 24.04 amd64 workflow substitute

The disposable Docker proof used Ubuntu 24.04 with `--platform linux/amd64`, a
clean detached clone of exact head `6a8ea75`, GCC 13, and the standing immutable
LLVM 22.1.8 amd64 packages verified by SHA-256, package name, version, and
architecture. The host Docker daemon is Linux/aarch64, so this is Docker
Desktop x86_64 emulation, not native hosted-Linux proof.

The canonical integrated result retained only the standing ruled environment
exceptions:

- product: 315 of 316 cases and 8,053 of 8,054 assertions passed; the sole
  failure was `version probe does not fall back to PATH when a pinned executable cannot spawn`;
- harness: 968 passed, three failed, three configured skips; all three failures
  were members of the four ruled Docker-overlay sentinel set;
- `harness-e2`: PASS in 1.05 seconds;
- `safety-build-werror`: PASS in 1.46 seconds;
- LLVM 22 tidy: executed and PASS in 37.13 seconds;
- `safety-hardening`: PASS in 0.14 seconds;
- core/adapter purity: PASS;
- canonical CTest total: 64.09 seconds;
- generated-envelope canonical row: dependency-not-run after the product
  failure.

The narrow controls were green:

- Catch2 excluding only the classified product case: 315 cases and 8,044
  assertions, all PASS;
- harness excluding exactly the four ruled overlay sentinels: 967 passed,
  three configured skips, four deselected;
- direct generated-envelope schema validation: PASS;
- JUnit substantive-row, tidy-row, and known-exception gates: PASS.

The runner exited 21 solely for the separately ruled historical Catch2 count
gate. That gate expects 223 successes and zero failures; canonical XML now
contains 315 successes plus the one classified product failure. All
substantive locally applicable rows and narrow controls are green. `.github/**`
remained out of B2 and no workflow byte changed.

## Remaining concerns and requested action

R-4.8/home-prefix work and the previously disclosed Minors remain separately
carried. The Docker exceptions and stale hard-coded count are disclosed rather
than represented as native hosted-Linux green.

Planner should request the orchestrator's **fourth targeted re-panel** at exact
PR head `6a8ea75a2d7ae072839940e69b16f6393c80ac32`. M-4 must hold fully: I-3
closed with no key-arm leak, F2 parent self-refusal gone, and F3 covered. B2 is
not bar-ready until that panel passes. Merge, release, deployment, workflow
repair, R-4.8, and the disclosed Minors remain held.

FOLD_SCOPE:
- src/adapters/rewrite_common.cpp -> in
- src/adapters/rewrite_common.hpp -> in
- src/adapters/codex/install.cpp -> in
- tests/test_adapter_claude_install.cpp -> in
- tests/test_adapter_codex_install.cpp -> in
FOLD_SCOPE_RESULT: all-in

ACTIONS_GIT_REF: implementation exact head 6a8ea75a2d7ae072839940e69b16f6393c80ac32, exact parent ec9a2db2cfe55191f99efbcf12902a79d99e159e, exactly one commit with preserved subject; amend wave f9675ea..6a8ea75 is exactly four authorized paths and rewrite_common.hpp is unchanged; origin/s4-floor/b2-torn-tail and open draft PR #23 are verified at the exact head; this relay and its append-only INDEX row ride one later explicit-path docs-lane commit whose SHA lands in repository history after filing
FINAL_GIT_STATUS_SHORT: implementation worktree clean at the published exact head; shared main carried unrelated matrix R-4.8 relay and INDEX state before this report; none was modified, staged, or committed by this seat

CARRY LIST:
- `.relays/s4/s4-floor-impl/SITREP-IMPLEMENTER-B2-I3-F2-F3-AMEND-COMPLETE-20260809-195459.md` -> `s4-floor.planner`
- https://github.com/iwnlcern/bivpak/pull/23 at exact `6a8ea75a2d7ae072839940e69b16f6393c80ac32` -> orchestrator fourth targeted re-panel; B2 not bar-ready until M-4 holds fully
- `.github/workflows/s2-harness.yml` stale 223-case count gate -> hard OUT, separately carried
- R-4.8/home-prefix and disclosed Minors -> separately carried, not expanded into B2
- merge/release/deployment -> operator-owned; release hold ABSOLUTE
