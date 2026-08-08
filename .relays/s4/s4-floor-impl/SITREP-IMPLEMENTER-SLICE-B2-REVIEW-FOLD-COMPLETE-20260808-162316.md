## SITREP — Slice B2 review fold complete at exact one-commit head d6cceba; both Critical verifier gaps closed, host suite green, Linux tidy/hardening green, PR #23 republished

ROLE: Implementer
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-floor-impl-2-b2-review-fold-complete
PARENT_DISPATCH_ID: s4-floor-impl-2-b2-review-fold
RUN_ID: s4
TASK_ID: B2
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — implementation and authorized draft republication are complete; the planner's targeted security/correctness/tests re-panel with m-4 still gates the replacement head; merge, release, and deployment remain outside this seat and held absolutely
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/IMPL-PLANNER-B2-FOLD-RESUME-EXPANSION-GRANTED-MASTER-RULED-20260808-150932.md
FROM: s4-floor.implementer
TO: s4-floor.planner
CC: s4.orchestrator-planner, operator
SUBJECT: DONE_WITH_CONCERNS — BL2-1..BL2-3 and BL2-5..BL2-7 folded at d6cceba; BL2-4 kept per-session as ruled; PR #23 republished; re-panel, merge, and release held

DONE_WITH_CONCERNS

## Exact head and publication state

- PR: https://github.com/iwnlcern/bivpak/pull/23
- branch: `s4-floor/b2-torn-tail`
- exact remote/local head: `d6cceba9321d693d8e302e89b796ca159a0f8f66`
- exact parent: `ec9a2db2cfe55191f99efbcf12902a79d99e159e`
- topology: exactly one commit over the dispatched parent
- subject preserved: `feat(pack): collect torn tails and staged sidecars`
- cumulative range: exactly 15 authorized paths, 2,936 insertions, 123 deletions
- PR #23 remains open and draft; its head and branch ref both resolve to `d6cceba`
- tracked implementation worktree is clean

The remote update used one exact `--force-with-lease` against reviewed old head
`54a6c54f9d12874123bb520b2598f1086931f70f`. GitHub Actions was not invoked,
rerun, or managed. No merge, release, or deployment action was performed.

## Fold disposition

### BL2-1 Critical — closed

Claude `never_rewrite` artifacts remain byte-identical but now receive a whole-document,
line-structure-independent bare origin scan before publication. Every destination counts
in `artifacts_checked`, and a path or id hit refuses that session before any write. The
exemption is selected from the adapter's declared `never_rewrite` inventory; unknown
subtree formats no longer enter a default unverified arm and instead fail containment.

### BL2-2 Critical — closed

The raw-text rewrite/verify API moved out of root `adapter.hpp` into the granted
`rewrite_common.{hpp,cpp}` paths behind typed byte/pair/origin views. Raw rewriting keeps
its token-boundary rule, while verification independently counts bare occurrences with
no reuse of the rewrite boundary predicate. The JSONL, raw-text, and never-rewrite arms
all have a sound pre-publication scan floor. LLVM 22's bounds-safety finding on the moved
helper was reproduced, fixed with checked-shaped span access, and rerun green.

### BL2-3 Important — closed

`strict_jsonl_decodable` now treats a zero-byte JSONL artifact as zero records, matching
the trailing-newline empty segment. Empty parent/child artifacts install successfully.
The locked whole-file invalid-live branch remains a zero-byte member plus an exact
`TornTailDropped` fact and is now pinned explicitly.

### BL2-4 authority — kept as ruled

No refusal-radius change was made. Origin verification remains per-session, conditioned
on the sound BL2-1/BL2-2 scan floor. The planner's targeted re-panel with m-4 on that
containment invariant remains required.

### BL2-5 Minor hardening — folded

The Codex invariant no longer depends on release-stripped identity assertions or an
unchecked `find` dereference. Established identities use `.value()` and rollout lookup
uses `.at()` after the existing whole-set validation pre-pass.

### BL2-6 test strength — closed

New/changed falsifiers cover:

- live Claude and Codex interior invalid segments, streamed-byte identity, and no facts;
- whole-file invalid live tails;
- two-artifact fact/source pairing and a terminal child under a live parent;
- empty JSONL install for both adapters;
- well-formed escaped ambiguous origins through decoded JSON verification;
- never-rewrite path/id leakage and unknown-format inventory enforcement;
- raw-text origins outside rewrite boundaries;
- non-staged identity mismatch refusal for both adapters.

The corrected never-rewrite and raw-text tests now kill the old leaking behavior by
asserting refusal, zero publication, and the expected hit/artifact counters.

### BL2-7 Important — closed

`StagedMapRow`, `StagedSidecar`, and the strict staging-sidecar parser now have one shared
spelling in `rewrite_common.{hpp,cpp}`. Both adapter collectors call the shared parser;
no new translation unit or CMake edit was introduced.

## Scope and fences

The mandatory fold scope was rekeyed after the exact two-path grant and recorded
`SCOPE_DIFF_RESULT: all-in` before product edits. The final cumulative 15 paths are the
original 13 B2 paths plus exactly:

- `src/adapters/rewrite_common.hpp`
- `src/adapters/rewrite_common.cpp`

`src/core/manifest/manifest.*`, `.github/**`, new translation units, CMake, schema,
workflow, refusal-radius, and design changes remain OUT and untouched. `git diff --check`
passes, the one-commit law holds, and the class-scoped A3 owner diff has no read-side
location-owner match.

## RED/GREEN evidence

Before production edits, the five-case Claude verifier/empty-JSONL set produced three
intended failures; the two-case Codex set produced the intended empty-JSONL failure while
its identity containment control stayed green. After the fold, the combined seven-case
critical set passed 59 assertions. The raw/never-rewrite focused post-tidy set passed 22
assertions. The staged-sidecar, live-interior, whole-file, multi-artifact, terminal-child,
empty-JSONL, escaped-origin, and identity cohorts all pass at the final bytes.

## A3 two-anchor ceremony

Both changed collector anchors were recaptured at the final product bytes:

- Claude: `2ccf5db154c87bdaa68c3c5c5b9199cb713b043ebc31b72057792a87da99bbed`
- Codex: `3fc6c8d1621967cb41090fb6e41a520945552729cec05429c852770866f59a6a`

The literals match `harness/bivharness/e3.py`; its delta is exactly two insertions and
two deletions. Nine owner-mutation receipts, the pinned-source control, and the unchanged
write-side exclusion control all pass: 11 checks total. The final tidy-only amendment did
not change either anchored source; the full 11-check ceremony was rerun green at final
head `d6cceba`.

## Final host macOS suite

Fresh final-head command: `ctest --preset ci-macos --output-on-failure`.

- `biv_tests`: PASS, all 296 cases / 7,469 assertions, 425.76 seconds;
- open-no-rewrite, adapter-purity, version-floor mirror, errno, schema, and generated
  envelope gates: PASS;
- `harness-selftest`: PASS, 4.96 seconds;
- `harness-e2`: PASS, 165.57 seconds;
- `safety-build-werror`: PASS, 2.25 seconds;
- ASan/UBSan, tidy/analyzer, and fuzz smoke: preset-configured skips;
- sole selected failure: `safety-hardening`, because `readelf` is unavailable on macOS;
- overall: 14/15 rows, 93%, 599.90 seconds.

The Linux substitute below executes and passes the missing hardening/tidy proof.

## Final Ubuntu 24.04 linux/amd64 Docker substitute

The disposable final-head clone ran under Docker Desktop with
`--platform linux/amd64`. All eight pinned LLVM 22.1.8 amd64 packages passed checksum,
package-name, version, and architecture validation.

Canonical results:

- GCC 13 hardened build and `safety-build-werror`: PASS;
- `biv_tests`: 295/296 cases and 7,468/7,469 assertions pass; sole failure is the
  established Rosetta invalid-executable spawn-semantic case;
- `harness-selftest`: 967 pass, four established overlay/enumeration mutation sentinels
  fail, three configured skips;
- `harness-e2`: PASS;
- LLVM 22 tidy: all 28 project sources executed and passed in 45.58 seconds; the JUnit
  tidy-row gate passed;
- `safety-hardening`: PASS;
- ASan/UBSan and fuzz smoke: workflow-configured skips;
- generated-envelope canonical row: dependency-not-run after the product exception;
- stale workflow count gate: still RED, expecting 223 successes while the current XML
  records 295 successes plus the one environment failure; `.github/**` remained OUT.

Bounded diagnostic controls all pass:

- product excluding only the Rosetta case: 295 cases / 7,459 assertions PASS;
- harness excluding exactly the four Docker filesystem sentinels: 967 pass, three
  configured skips, four deselected;
- generated-envelope direct schema validation: PASS.

The narrow controls diagnose the substitute environment and are not claimed as native
GitHub-hosted x86_64 proof. Canonical aggregate exit remains 20 because the runner
honestly retains the product/harness environment exceptions; `tidy_gate_rc=0`, narrow
product/harness/envelope results are all zero. GitHub Actions remained unused.

## Requested next action and holds

Planner should convene the dispatched cold targeted security/correctness/tests re-panel
on exact head `d6cceba`, including m-4 on the per-session containment invariant. This
implementer seat has no authority to declare that gate satisfied. Merge, release, and
deployment remain held absolutely for the operator.

ACTIONS_GIT_REF: product/test fold amended and published at `d6cceba9321d693d8e302e89b796ca159a0f8f66`; this report and its append-only INDEX row ride one explicit-path docs-lane commit filed after the product proof
FINAL_GIT_STATUS_SHORT: implementation worktree clean; shared relay checkout was clean before filing and this seat's docs writes are confined to this report plus the appended INDEX row

CARRY LIST:
- `.relays/s4/s4-floor-impl/SITREP-IMPLEMENTER-SLICE-B2-REVIEW-FOLD-COMPLETE-20260808-162316.md` → `s4-floor.planner`
- exact draft PR #23 head `d6cceba9321d693d8e302e89b796ca159a0f8f66` → targeted security/correctness/tests re-panel with m-4
- Docker/Rosetta exceptions + stale 223-count workflow gate → disclosed residuals; no `.github/**` authority
- merge, release, deployment, and GitHub Actions management → held; operator/planner authority only
