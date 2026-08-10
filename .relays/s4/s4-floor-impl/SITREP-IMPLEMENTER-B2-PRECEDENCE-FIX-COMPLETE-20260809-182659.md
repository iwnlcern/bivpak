## SITREP — B2 precedence fix complete at exact one-commit head f9675ea; both-adapter descendant-staging falsifiers green; scoped re-review clean; host and local Linux bars complete; PR #23 republished

ROLE: Implementer
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-floor-impl-2-b2-precedence-complete
PARENT_DISPATCH_ID: s4-floor-impl-2-b2-precedence-fold
RUN_ID: s4
TASK_ID: B2
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — implementation and authorized draft publication are complete; the third targeted re-panel, merge, release, and deployment remain outside this seat
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/IMPL-PLANNER-B2-PRECEDENCE-FIX-DISPATCH-IMPL-TOKEN-20260809-161206.md
FROM: s4-floor.implementer
TO: s4-floor.planner
CC: s4.orchestrator-planner, operator
SUBJECT: DONE_WITH_CONCERNS — B2 precedence Important addressed at f9675ea; strict TDD, scoped re-review, fresh host suite, and ruled Docker bar complete; PR #23 republished; merge/release held

DONE_WITH_CONCERNS

## Exact result and publication state

The final-review staged-path precedence Important is addressed and B2 is republished as
draft PR #23:

- PR: https://github.com/iwnlcern/bivpak/pull/23
- branch: `s4-floor/b2-torn-tail`
- exact head: `f9675ea0303209af0a6b12f08bf05625f141c826`
- exact parent: `ec9a2db2cfe55191f99efbcf12902a79d99e159e`
- topology: exactly one commit over the dispatched parent
- subject: `feat(pack): collect torn tails and staged sidecars`
- implementation worktree: clean after amend, verification, and publication

The remote branch and open draft PR were verified at the exact head after a
force-with-lease update from the previously observed remote head `d6cceba`. GitHub
Actions was not manually invoked, rerun, or managed. Implementation was complete and
both local verification environments had run before publication. No merge, release, or
deployment action was performed.

## Root cause and implemented behavior

`derive_install_pair_set` emits original-path pairs before staged-root pairs. When a
staged root is a descendant of the original path, insertion-order JSON rewriting applied
the shorter original prefix first. The longer exact staged-root pair then missed, leaving
a semantically wrong descendant path while both raw origin needles were absent.

`apply_replacements` now creates a non-owning view of the supplied path pairs, stably
orders that view by descending source length, and applies JSON path replacements in
longest-source-first order. Equal-length order remains stable. This matches the existing
verification-needle precedence. ID replacement order is unchanged.

No pair construction, needle set, verification domain, rewrite radius, public signature,
or header changed.

## Strict RED to GREEN

Before the production edit, two real-adapter falsifiers were added:

- `B2 composed Claude descendant staging path uses the exact final workspace`
- `B2 composed Codex descendant staging path uses the exact final workspace`

Each drives the real installer with an authoritative staged root below the original
path, requires the exact final workspace in rewritten JSON, rejects the wrongly rewritten
descendant, and still requires zero surviving origin-path hits.

RED under insertion-order application:

```text
exit 42
test cases: 2 | 0 passed | 2 failed
assertions: 22 | 18 passed | 4 failed
```

For each adapter, the exact-final assertion and wrong-descendant-absent assertion failed;
installation and zero-origin-hit assertions passed. This proves the falsifiers exercised
the precedence defect rather than an invalid fixture or refusal path.

Immediate GREEN after the minimal production change:

```text
All tests passed (22 assertions in 2 test cases)
```

The focused composed/re-pack/transcript cohort then passed 429 assertions in eight cases.

## Scope, amend, and A3 ceremony

The fix wave from held head `3f2dd3ead60f50a06d3951d69bf46b8afa2becf1`
to final head `f9675ea0303209af0a6b12f08bf05625f141c826` changes exactly:

- `src/adapters/rewrite_common.cpp`: 11 lines, 10 insertions and one deletion;
- `tests/test_adapter_claude_install.cpp`: 50 insertions;
- `tests/test_adapter_codex_install.cpp`: 54 insertions.

`git diff --check 3f2dd3e..f9675ea` passes. `src/adapters/rewrite_common.hpp`,
manifest files, `.github/**`, R-4.8/home-prefix work, and all other product/test paths
were unchanged by this fix wave.

The three paths were staged explicitly and amended into the existing B2 commit with the
subject preserved. The complete one-commit B2 head contains the previously authorized
16-path union and remains exactly one commit over `ec9a2db`.

The mechanical A3 check passes: neither anchored collector source changed in this fix
wave, so anchor recapture did not re-fire. No anchored hash was asserted without running
that check.

## Scoped independent re-review

The independent re-review inspected only `3f2dd3e..f9675ea` and returned:

- the precedence Important is ADDRESSED;
- the shared implementation supplies a stable longest-source-first path-pair view;
- both Claude and Codex falsifiers exercise the real composed descendant-staging path;
- exact three-file scope and code quality pass;
- no new Critical or Important issue was found.

The reviewer authorized the standing sequence of post-review host suite, Ubuntu amd64
Docker substitute, and publication. Merge and release remained explicitly unauthorized.

## Fresh post-review macOS host suite

Command at exact head:

```sh
ctest --preset ci-macos -E '^safety-hardening$' --output-on-failure
```

Result:

- `biv_tests`: PASS in 329.72 seconds;
- `harness-selftest`: PASS in 4.90 seconds;
- `harness-e2`: PASS in 187.22 seconds;
- `safety-build-werror`: PASS in 0.58 seconds;
- ASan/UBSan, tidy/analyzer, and fuzz smoke: preset-configured skips;
- overall: 100%, 14 of 14 selected rows passed, zero failures;
- total: 523.73 seconds.

An earlier pre-review host run was also green, but it is supplemental only; the numbers
above are the required fresh post-review evidence.

## Local Ubuntu 24.04 amd64 workflow substitute

The disposable Docker proof used Ubuntu 24.04 with `--platform linux/amd64`, a clean
detached clone of exact head `f9675ea`, GCC 13, and eight immutable LLVM 22.1.8 amd64
packages verified by SHA-256, package name, version, and architecture. The host Docker
daemon is Linux/aarch64, so this is Docker Desktop x86_64 emulation, not native hosted
Linux proof.

The canonical integrated result retains only the standing ruled environment exceptions:

- product: 313 of 314 cases and 8,024 of 8,025 assertions passed; the sole failure is
  `version probe does not fall back to PATH when a pinned executable cannot spawn`;
- harness: 968 passed, three failed, three configured skips on the classified rerun;
  the failures were a subset of the four ruled Docker overlay sentinels, whose occurrence
  varies with filesystem timing;
- `harness-e2`: PASS in 1.17 seconds;
- `safety-build-werror`: PASS in 1.66 seconds;
- LLVM 22 tidy row: executed and PASS in 46.63 seconds;
- `safety-hardening`: PASS in 0.15 seconds;
- core/adapter purity: PASS;
- canonical CTest total: 76.18 seconds;
- generated-envelope canonical row: dependency-not-run after the product failure.

The narrow controls are green:

- Catch2 excluding only the Rosetta invalid-executable case: 313 cases and 8,015
  assertions, all PASS;
- harness excluding exactly the four ruled overlay sentinels: 967 passed, three
  configured skips, four deselected;
- direct generated-envelope schema validation: PASS;
- JUnit substantive-row, tidy-row, and known-exception gates: PASS.

The runner exits 21 solely for the separately ruled historical Catch2 count gate. That
gate expects 223 successes and zero failures; the canonical XML now contains 313
successes plus the one Rosetta failure. The implementation, narrow controls, analyzer,
E2, hardening, and schema gates are green. `.github/**` remains out of B2 and no workflow
byte was changed.

## Remaining concerns and requested action

The staged-sidecar identity-keying Minor and staged/host cross-source dedupe Minor remain
separately carried. R-4.8/home-prefix work remains separate. The Docker exception set and
stale hard-coded count are disclosed rather than represented as native hosted-Linux
green.

Planner should request the orchestrator's third targeted re-panel at exact PR head
`f9675ea0303209af0a6b12f08bf05625f141c826` under the union-scope acceptance. Merge,
release, deployment, workflow repair, R-4.8, and the two Minors remain held.

FOLD_SCOPE:
- src/adapters/rewrite_common.cpp -> in
- tests/test_adapter_claude_install.cpp -> in
- tests/test_adapter_codex_install.cpp -> in
FOLD_SCOPE_RESULT: all-in

ACTIONS_GIT_REF: implementation exact head f9675ea0303209af0a6b12f08bf05625f141c826, exact parent ec9a2db2cfe55191f99efbcf12902a79d99e159e, exactly one commit with preserved subject; fix wave 3f2dd3e..f9675ea is exactly three authorized paths; origin/s4-floor/b2-torn-tail and open draft PR #23 are verified at the exact head; this relay and its append-only INDEX row ride one later explicit-path docs-lane commit whose SHA lands in repository history after filing
FINAL_GIT_STATUS_SHORT: implementation worktree clean at the published exact head; shared main carried nine unrelated untracked R-4.8 relay files before this report and INDEX append; none was modified, staged, or committed by this seat

CARRY LIST:
- `.relays/s4/s4-floor-impl/SITREP-IMPLEMENTER-B2-PRECEDENCE-FIX-COMPLETE-20260809-182659.md` -> `s4-floor.planner`
- https://github.com/iwnlcern/bivpak/pull/23 at exact `f9675ea0303209af0a6b12f08bf05625f141c826` -> orchestrator third targeted re-panel; merge/release held
- `.github/workflows/s2-harness.yml` stale 223-case count gate -> hard OUT, remains separately routed
- R-4.8/home-prefix and the two disclosed Minors -> separately carried, not expanded into B2
