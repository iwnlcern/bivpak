## SITREP — Slice A local Linux suite completed; two in-scope Linux gates fixed at amended one-commit head 798526c; Docker-only deltas and stale count gate remain; no remote publication

ROLE: Implementer
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-floor-impl-2-a-local-linux-ci
PARENT_DISPATCH_ID: s4-floor-impl-2-a-review-fold
RUN_ID: s4
TASK_ID: A
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — local amended head 798526c is not published to PR #21; Planner/operator disposition is required before any remote branch update, remote CI observation, merge, or release
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/REVIEW-FOLD-IMPLEMENTER-SLICE-A-TASKS-4-6-FILED-20260806-091452.md
FROM: s4-floor.implementer
TO: s4-floor.planner
CC: s4.orchestrator-planner, operator
SUBJECT: DONE_WITH_CONCERNS — canonical local Ubuntu 24.04 amd64 suite completed; GCC/tidy gates fixed at local head 798526c; all nine receipts refreshed; PR #21 remains at 26e6eb1; publish/merge/release held

DONE_WITH_CONCERNS

## Summary

Per the operator's current repository instruction, GitHub Actions was not used. The
Linux portions of .github/workflows/s2-harness.yml were reproduced locally in
disposable Ubuntu 24.04 linux/amd64 containers with the workflow's exact pinned
clang-tidy 22 packages.

The run exposed two real Slice A defects at the previously filed head 26e6eb1:

1. GCC 13 -Werror=missing-field-initializers rejected new aggregate fixtures in
   tests/test_sessions.cpp.
2. clang-tidy 22 rejected unchecked optional access in both adapter capability probes
   and the intentionally public, non-invariant observation fields on Capabilities.

The minimal four-file correction was folded into the existing Slice A commit, preserving
the one-commit law. The new local exact head is
798526c5c68c4251cc088bcf922fbee798ed8b79, with exact parent
ff63e521d8ae5229a831aab8718a3fa58205f40f. No remote branch, PR, CI, merge, release,
or deployment action was performed. Draft PR #21 therefore remains at remote head
26e6eb1fbe57401e9ed3c931a57f0d8863d96fd6.

## Files changed by the Linux correction

- src/adapters/adapter.hpp — scope the clang-tidy exception to the three public
  observation fields; private verdict/version/newer invariant state is unchanged.
- src/adapters/claude_code/install.cpp — directly guard parsed/compared optionals.
- src/adapters/codex/install.cpp — directly guard parsed/compared optionals.
- tests/test_sessions.cpp — explicitly initialize admitted aggregate fields; test
  behavior and assertions are unchanged.

The final range remains exactly 24 authorized Slice A paths. It touches no .github/**,
manifest, scan, host-store, release, or collect-anchor/A3 source path. The envelope
schema is unchanged by this correction. The implementation worktree is clean.

## Linux runner and workflow parity

The proof runner used:

- ubuntu:24.04, --platform linux/amd64, observed uname -m = x86_64;
- unprivileged UID/GID 501 and an init/subreaper process model;
- an exec-capable task-owned Docker volume for test temporaries;
- Python 3.12.3, CMake 3.28.3, GCC 13.3.0;
- all eight workflow LLVM assets, each verified by the workflow SHA-256, Debian package
  name, exact version, amd64 architecture, installed version, and LLVM major 22;
- writable /mnt/c/tmp, as required by the cross-flavor fixture.

Differences from GitHub Actions were explicit:

- a detached local clone replaced actions/checkout;
- host-side authenticated release download replaced in-job gh release download, while
  the exact eight assets were reverified inside the container;
- Ubuntu's Python 3.12.3 replaced actions/setup-python;
- Docker Desktop emulated amd64 on an arm64 macOS host via Rosetta instead of running a
  native GitHub x86_64 VM.

The initial root-container attempt is retained as a process scar: root bypassed
permission-mode tests. It was discarded and rerun unprivileged. A tmpfs probe was also
discarded because Docker mounts /dev/shm noexec; it was not used as product evidence.

## Canonical Linux results at tested corrected bytes

The corrected implementation worktree and disposable clone had identical SHA-256 blobs
for all four changed files.

- harness dependency install, harness configure, core-adapter purity, Linux configure,
  and Linux build: PASS;
- BIVHARNESS_REQUIRE_CLANG_TIDY=ON: selected /usr/bin/clang-tidy-22;
- safety-build-werror: PASS;
- safety-tidy-analyzer: PASS in 30.49 seconds;
- exact JUnit tidy-row gate: one safety-tidy-analyzer row, status run, PASS;
- harness-e2: PASS;
- safety-hardening: PASS;
- errno, schema, mirror, purity, and open/no-rewrite rows: PASS;
- safety-asan-ubsan and safety-fuzz-smoke: workflow-configured SKIP rows.

The canonical full CTest result was 80%: 12 effective PASS rows, two configured SKIPs,
and three red/not-run rows:

- biv_tests: 246 of 247 cases passed; the sole failure is the Rosetta-only
  invalid-executable semantic difference. Rosetta starts its amd64 translation shim and
  returns nonzero exit, while the native x86_64 contract expects posix_spawn failure.
- harness-selftest: 962 passed, 4 skipped, 3 failed in that run. Across repeated Docker
  storage probes, four directory/file mutation-detection cases varied with Docker
  filesystem timestamp/enumeration semantics.
- generated_envelope_conforms: not run only because CTest depends on biv_tests.

Narrow environment-exclusion controls then passed:

- product: 246 cases and 6,523 assertions PASS with only the Rosetta invalid-executable
  case excluded;
- harness: 961 passed, 4 skipped, 4 Docker-filesystem mutation cases deselected;
- generated envelope: direct schema validation PASS.

These exclusions diagnose local Docker substitution limits; they are not claimed as a
canonical native-x86_64 green run. The full canonical failure remains disclosed.

Independently of the Rosetta case, the workflow's Linux Catch2 count gate is stale:
the binary enumerates 247 cases while .github/workflows/s2-harness.yml still requires
exactly 223 successes. .github/** remains hard OUT for this pair, so no count-gate
edit was made.

## Review and exact-head mutation receipts

An independent read-only review of 26e6eb1..798526c found no Critical, Important, or
Minor issue and returned Ready to merge: YES. Its focused invariant/probe/session
control passed 389 assertions.

Because the amendment changed the exact head, all nine required mutation receipts were
replayed at 798526c, each as correct-code GREEN → one isolated intended RED with
required sibling controls → exact inverse → same-command GREEN:

| Receipt | GREEN | intended RED | inverse GREEN |
|---|---:|---:|---:|
| O3 Codex default disclosure | 27/27 | 26/27, visibility only | 27/27 |
| O3 Claude default disclosure | 27/27 | 26/27, visibility only | 27/27 |
| O6 Claude derivation purity | 12/12 | 10/12, ten siblings green | 12/12 |
| O6 Codex derivation purity | 12/12 | 10/12, ten siblings green | 12/12 |
| O4 Codex NUL ordering | 65/65 | 62/65, row/exit/read siblings green | 65/65 |
| O4 Claude NUL ordering | 65/65 | 56/65, hostile siblings green | 65/65 |
| MG7 Codex full grammar | 112/112 | 72/112; Claude 56/56 green | 112/112 |
| MG7 Claude full grammar | 112/112 | 72/112; Codex 56/56 green | 112/112 |
| A5.8 silent promotion | 6/6 | 4/6; frozen versions/MINs green | 6/6 |

All temporary receipt tests and mutations were removed. The refreshed run trace is the
git-ignored local artifact
.superpowers/sdd/2026-08-05-s4-floor-fold-plan/slice-a-nine-receipts-report.md;
this relay is the durable routed summary.

An extra host-side ctest --test-dir build/dev --output-on-failure passed rows 1–11,
skipped 12/13/15, and stopped at row 14 only because Darwin lacks readelf. This does
not conflict with the Ubuntu runner, where safety-hardening passed.

## Acceptance, boundary, and remaining risk

- one-commit topology: PASS (ff63e52..798526c count = 1);
- required commit subject: unchanged;
- final implementation status: clean;
- final 24-path scope: unchanged and authorized;
- Linux GCC build gate: PASS after correction;
- clang-tidy execution and exact-row gate: PASS after correction;
- exact-head nine-receipt ceremony: PASS;
- independent delta review: Ready YES;
- remote publication: NOT PERFORMED;
- native GitHub x86_64 proof: NOT CLAIMED;
- hard-OUT Catch2 count gate: still stale at 223 versus 247 enumerated cases;
- merge/release: HELD.

## Requested next action

Planner should review this amended exact head and decide whether/when the remote branch
may be updated under immutable force-with-lease. Any publication would change PR #21's
head and requires panel/receipt reconciliation at 798526c. The hard-OUT .github
count gate still needs upstream ownership. No merge or release authority is claimed.

ACTIONS_GIT_REF: local Slice A head 798526c5c68c4251cc088bcf922fbee798ed8b79, exact parent ff63e521d8ae5229a831aab8718a3fa58205f40f, one commit and 24 authorized paths; origin/s4-floor/a-floor-core and draft PR #21 remain at 26e6eb1fbe57401e9ed3c931a57f0d8863d96fd6; no remote action performed; this relay and its append-only INDEX row ride a later docs-lane commit whose SHA lands in repository history after filing
FINAL_GIT_STATUS_SHORT: implementation worktree clean at local 798526c and intentionally differs from origin/PR head 26e6eb1; docs lane clean apart from the unrelated pre-existing untracked s4-matrix relay, which remains untouched

CARRY LIST:
- .relays/s4/s4-floor-impl/SITREP-IMPLEMENTER-SLICE-A-LOCAL-LINUX-CI-20260806-160811.md → s4-floor.planner
- local head 798526c5c68c4251cc088bcf922fbee798ed8b79 → panel/publication disposition only; no implicit push
- https://github.com/iwnlcern/bivpak/pull/21 at remote head 26e6eb1fbe57401e9ed3c931a57f0d8863d96fd6 → unchanged; merge/release held
