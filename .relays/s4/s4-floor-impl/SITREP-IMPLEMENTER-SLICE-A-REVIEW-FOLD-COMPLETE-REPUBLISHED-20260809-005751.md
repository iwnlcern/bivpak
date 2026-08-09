## SITREP — Slice A A-BL1..A-BL6 review fold complete, independently approved, local Ubuntu amd64 verified, and draft PR #21 republished

ROLE: Implementer
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-floor-impl-2-a-fold
PARENT_DISPATCH_ID: s4-floor-pair-plan-review-approve
RUN_ID: s4
TASK_ID: A
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — the amended head still owes the Planner's targeted re-check and merge-ready confirmation; merge and release remain the operator's alone and the release hold is ABSOLUTE
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/IMPL-PLANNER-SLICE-A-FOLD-DISPATCH-IMPL-TOKEN-20260808-222525.md
FROM: s4-floor.implementer
TO: s4-floor.planner
CC: s4.orchestrator-planner, operator
SUBJECT: DONE_WITH_CONCERNS — A-BL1..A-BL6 folded at exact one-commit head 33153137; independent review and pinned local Linux verification complete; draft PR #21 republished; targeted re-check, merge, and release held

DONE_WITH_CONCERNS

## Result

The live `DISPATCH IMPL` token was executed within its exact `SCOPE_DIFF`. The mandatory
pre-edit scope artifact returned `all-in`. A-BL1 through A-BL6 are folded into the
single Slice A commit at exact head
`33153137bbf7640cdcf4576de7f41b17fe57ae99`, with exact parent
`ff63e521d8ae5229a831aab8718a3fa58205f40f`. The prescribed subject is unchanged:

`feat(adapters): version floor + C1 conjunction, one head — allowlist retired, mirror + pin check same-commit`

Draft PR #21 was republished by immutable force-with-lease from its observed remote head
`798526c5c68c4251cc088bcf922fbee798ed8b79` to exact head `33153137...`. The PR remains
OPEN and DRAFT. Its body now names the exact head and refreshed host/Docker/review
evidence. No manual GitHub Actions dispatch or rerun was issued; remote workflow results
are not used as proof here.

## Folded blockers

- A-BL1: both Claude and Codex rewrite-verification legs preserve already-typed version
  refusal rows; cohort and consumer-boundary regressions exercise the behavior.
- A-BL2: the probe fixture contains a schema-validated
  `readable-newer-than-survey` row.
- A-BL3: the session E2E uses a live above-host refusing row and no stale
  `not-validated` fallback.
- A-BL4: pack `unknown` remains fail-open and both real adapters cover an unparseable
  host version.
- A-BL5: readable-newer disclosure is gated by the capability verdict.
- A-BL6: admission is centralized in `version_floor::admit`; below-MIN-at-open remains
  admitted by the locked design.

The first implementation head was `d885530ad431491069c7095c5b687fba0e714af8`.
The first independent review returned Approved with no Critical, Important, or Minor
findings. The subsequent pinned clang-tidy 22 run found one real Important integration
defect not visible to the host compiler: three adjacent `std::string_view` parameters in
the new `admit(agent, host_version, image_version)` API were swap-prone. The review-fix
loop replaced them with a named `AdmissionInput`; both adapters and the policy test use
designated fields. No lint suppression or behavior branch was added.

A fresh independent review of `d885530..3315313`, cross-checked against the complete
`798526c..3315313` fold, returned Approved with no Critical, Important, or Minor
findings. It verified the type-safe repair, all A-BL1..A-BL6 protections, exact scope,
exact parent, one-commit topology, and preserved subject.

## Exact fold paths

The fold changes exactly these twelve authorized paths relative to `798526c`:

- `src/adapters/claude_code/install.cpp`
- `src/adapters/codex/install.cpp`
- `src/adapters/version_floor.cpp`
- `src/adapters/version_floor.hpp`
- `src/core/open/render.cpp`
- `src/core/open/sessions.cpp`
- `tests/fixtures/probe-envelope-v1.json`
- `tests/test_adapter_claude_install.cpp`
- `tests/test_adapter_codex_install.cpp`
- `tests/test_pack.cpp`
- `tests/test_render.cpp`
- `tests/test_sessions.cpp`

The complete Slice A commit remains a 24-path authorized range. No anchored collector,
manifest, scan, host-store, `.github/**`, merge, release, or unrelated minor path moved.

## Host verification

Focused TDD and regression controls for A-BL1..A-BL6 passed. After the type-safe repair,
the six focused rows passed with 24, 8, 8, 13, 13, and 15 assertions. The relevant host
suite passed 4/4, including `biv_tests`, `version_floor_mirror`, and
`safety-build-werror`.

The final full host suite at exact head reported 14/14 locally applicable rows green,
zero failures, with three intentional configured skips. Darwin hardening was excluded
because the host has no `readelf`; it was executed and passed in Ubuntu below. The host
implementation worktree ended clean.

## Local Ubuntu 24.04 amd64 substitution

Per the operator's CI rule, the Linux workflow was reproduced locally; GitHub Actions
was not manually invoked. Exact archived bytes of `33153137...` were built in a
disposable `ubuntu:24.04` container forced to `linux/amd64`, observed as `x86_64`, under
unprivileged UID/GID 501. The runner used Python 3.12.3, CMake 3.28.3, GCC 13.3.0, an
exec-capable task-owned Docker volume, and writable `/mnt/c/tmp`.

All eight workflow LLVM assets were downloaded from the immutable release and matched
the workflow's SHA-256 manifest. The installed packages reported the exact pinned
`1:22.1.8~++20260613092238+e80beda6e255-1~exp1~20260613092253.78` version and
clang-tidy LLVM major 22.

At final head:

- configure/build and core-adapter purity: PASS;
- `BIVHARNESS_REQUIRE_CLANG_TIDY=ON`: selected `/usr/bin/clang-tidy-22`;
- `safety-build-werror`: PASS;
- `safety-tidy-analyzer`: PASS in 31.23 seconds, with the exact JUnit row present,
  status `run`, and no skip/failure/error child;
- `harness-e2`: PASS;
- `safety-hardening`: PASS;
- errno, probe-schema, version-floor mirror, core purity, and open/no-rewrite rows: PASS;
- `safety-asan-ubsan` and `safety-fuzz-smoke`: workflow-configured SKIP rows.

The canonical full CTest result was 80%: twelve effective pass rows including the two
configured skips, with three red/not-run rows retained as substitution evidence:

1. `biv_tests`: 253/254 cases and 6,695/6,696 assertions passed. The sole red is the
   already documented Docker Desktop Rosetta invalid-executable semantic difference:
   Rosetta starts its amd64 translation shim and returns a nonzero exit rather than the
   native-x86_64 `posix_spawn` failure.
2. `harness-selftest`: 963 passed, 3 skipped, and two of the four known
   Docker-filesystem mutation-detection cases failed in this run. The failing subset is
   variable across overlay runs and is retained as an environment limitation.
3. `generated_envelope_conforms`: not run only because CTest depends on `biv_tests`.

Narrow environment-exclusion controls then passed:

- product: 253 cases and 6,686 assertions PASS with only the Rosetta case excluded;
- harness: 961 passed, 3 skipped, 4 known Docker-filesystem mutation cases deselected;
- generated envelope: direct Draft 2020-12 schema validation PASS.

These exclusions are diagnostic-substitute proof, not a claim of native GitHub x86_64
green. The workflow's hard-OUT Catch2 count gate is also stale: exact XML reports 253
successes, 1 failure, 0 expected failures, 0 skips across 254 cases, while the workflow
still requires exactly 223 successes. No `.github/**` edit was authorized or made.

## First Docker attempt scar

The first fresh container configuration attempt lacked Ubuntu's `libsqlite3-dev` and
stopped before product tests. Its evidence-path also targeted the root-owned volume
directory. The runner-only script was corrected to install the workflow prerequisite,
write evidence under the unprivileged repository directory, and parse CTest's actual
`build/ci/ctest.xml` location. The final run above used those corrected runner bytes;
no product path was changed for this scar.

## Gates and holds

- A-BL1..A-BL6: CLOSED at exact `33153137...`;
- independent exact-diff review: APPROVED, no findings;
- one-commit law, exact parent, exact subject, and scope: PASS;
- host verification: PASS within named Darwin limitation;
- local Ubuntu pinned clang-tidy/Werror/E2/hardening gates: PASS;
- draft PR #21 publication: COMPLETE at exact head;
- Planner targeted re-check and merge-ready confirmation: OWED;
- merge: NOT AUTHORIZED;
- release: HELD ABSOLUTE.

ACTIONS_GIT_REF: Slice A exact head `33153137bbf7640cdcf4576de7f41b17fe57ae99`, parent `ff63e521d8ae5229a831aab8718a3fa58205f40f`, one commit with preserved subject; origin `s4-floor/a-floor-core` and draft PR #21 verified at the exact head after force-with-lease publication; this report and its append-only INDEX row ride one explicit-path docs-lane commit whose SHA lands in repository history after filing
FINAL_GIT_STATUS_SHORT: Slice A implementation worktree clean at exact published head; docs lane was clean before this report and INDEX append; B2 local `03e672ca` remains separately HELD by the manifest-carrier scope blocker filed at `20260808-235201`

CARRY LIST:
- `.relays/s4/s4-floor-impl/SITREP-IMPLEMENTER-SLICE-A-REVIEW-FOLD-COMPLETE-REPUBLISHED-20260809-005751.md` → `s4-floor.planner`
- `33153137bbf7640cdcf4576de7f41b17fe57ae99` / draft PR #21 → targeted Planner re-check, then merge-ready confirmation only
- `.relays/s4/s4-floor-impl/SITREP-IMPLEMENTER-B2-CYCLE2-MANIFEST-CARRIER-SCOPE-BLOCKER-20260808-235201.md` → independent B2 scope decision; do not publish local `03e672ca`
- merge and release → operator only; release hold ABSOLUTE
