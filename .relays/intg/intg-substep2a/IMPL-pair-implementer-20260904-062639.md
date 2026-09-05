## IMPL COMPLETE RETURN — rev15 Task 3 replacement and Task 4 evidence are complete at `a2f6fd1`; candidate-attributable gates are green and downstream byte review remains held

ROLE: Pair Implementer
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: intg-substep2a-impl-5
PARENT_DISPATCH_ID: intg-substep2a-plan-review-15
IN_REPLY_TO: intg-substep2a/IMPL-pair-planner-20260904-044638.md
RELATED_CONTEXT: intg-substep2a/PLAN-pair-planner-20260903-230341.md; intg-substep2a/PLAN-REVIEW-pair-implementer-20260904-043346.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep2a-20260830.md; ../../../pdc/master/relays/intg-substep2a-format-act/DESIGN-planner-20260903-183510.md; ../../../pdc/master/relays/intg-substep2a-format-act/PLAN-master-planner-20260903-183926.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — this implementation return performs no risk downgrade and grants no downstream authority; m-1's extended V-FA/O review and m-3's C-6 test-hunk review must return through master before this candidate may become a merge-packet input, and merge, landing, count-gate observations, push, PR, publication, deployment, seal, and release remain separately held; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: intg-format-act-plan
DESIGN_LOCK_ID: m1-addendum-O-63c46631-lock-20260901
DESIGN_RECORD_KIND: design-doc
LOCKED_DESIGN_SHA256: 63c46631c84ce27ebedbf71c4965e6b0b149919a83118835d78ce29e89d3e577
LOCKED_DESIGN_COMMIT: 40b4f7a3dbfc60e5ab742678bc4e77198845c243
POST_STAMP_SHA256: 0e990bac752986942d9091871a5175820b829dd019d586e8e895461cfff656d2
SECOND_CONSUMED_LOCK: m1-addendum-N-82293732-lock-20260827
THIRD_CONSUMED_LOCK: m1-addendum-M-2966b839-lock-20260825
PLAN_LOCK_ID: intg-substep2a-plan-20260830 @ sha256 beba597c20d43441f6901f4930e4e4141bd866ecdc27c3f8cec3f403dcb0f265
BASE: main@46df8f3c35981a4ae3f77cf3293a4b7212b4b996
BRANCH: intg/format-act at a2f6fd1adf67fd86c8d0c692db34f113a9691135 in /Users/jack/Programming/bivpak-intg-format-act; parent 363d812fba2610f7e5c71fdb9daee5c7f740027a; worktree and index clean; retained-task3-9e6ebe8 and retained-task3b-b09e192 remain local tag-only evidence commits
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: master.master-planner, master.master-reviewer, operator, m-1.planner, m-1.implementer, m-3.planner, m-3.implementer
SUBJECT: RETURN — rev15 implementation complete at exact candidate a2f6fd1 with the one replacement commit, exact ten-path scope, clean Task-3 review, partitioned Task-4 report, green candidate gates on macOS and Ubuntu 24.04 amd64, and only registered/configured aggregate residuals; route exact bytes to m-1 and m-3 via master, with every merge/release gate still held

## Disposition and byte binding

The fresh `044638` authority was consumed in order: Step 0-quater matched the frozen checkpoint, the single `dot{}` test initializer was applied, macOS Step 4 passed, the Ubuntu Step 4b keep-going census passed, Step 5 produced the one replacement commit, Step 6 returned CLEAN, and Task 4 completed at the replacement SHA.

```text
candidate=a2f6fd1adf67fd86c8d0c692db34f113a9691135
candidate_parent=363d812fba2610f7e5c71fdb9daee5c7f740027a
plan_sha256=beba597c20d43441f6901f4930e4e4141bd866ecdc27c3f8cec3f403dcb0f265
task4_report=/Users/jack/Programming/bivpak-intg-format-act/.superpowers/sdd/PL-intg-substep2a-20260830/task-4-report.md
task4_report_sha256=7a4c9c96bb74f118e286e7ab029937d6f897fd8fd68cf9ad4c093f4cff2426b5
task4_report_lines=841
task4_evidence_home=/tmp/bivpak-format-act-task4-rev15.Z1yIwJ
step4b_evidence_home=/tmp/bivpak-intg-rev15.zu1UX0
```

The report is the file-first partitioned evidence artifact for the requested byte reviews. Its temp paths are provenance, not dependencies: the required receipts, hashes, exact command results, residual classification, C/T fence statements, and NOT-DONE boundary are reproduced in the report.

## Step 0-quater through Step 6

- The pre-edit gate matched exactly: HEAD `b09e1922c16da50b5bef0644d9923a567b98c468`, parent `363d812`, four commits above `46df8f3`, both retention tags exact, empty index, and exactly the held `manifest.hpp` plus `manifest.cpp` working-tree paths at the dispatched SHA-256 values.
- `tests/test_manifest.cpp` changed only `std::string dot;` to `std::string dot{};`: numstat `1/1`, changed-line transcript exactly those two lines, and no per-aggregate `.dot = {}`.
- The checkpoint diff stayed exactly three paths and six authorized hunks: T-1's header initializer, four T-4 structural warning folds, and the test-local `dot{}` initializer. No NOLINT was used.
- Step 4 macOS focused rows passed: FX-O `803 assertions / 11 cases`; FX-N `135 / 5`; repository engine `452 / 60`; full `biv_tests` `16,343 assertions`, `418 passed / 3 configured skips` of 421 cases.
- Step 4b ran Ubuntu 24.04 with `--platform linux/amd64 --init`, read-only source/assets, suite uid/gid 1001, and non-root `nofile` raised from 1024 to hard 1048576. All eight pinned LLVM-22 asset hashes passed strict verification. Configure, every-target keep-going build, and the verbose isolated tidy row all returned 0.

```text
missing_initializer_count=0
coverage_line_count=1
coverage_failure_count=0
17: clang-tidy coverage: 37 results == 37 sources
suite_aggregate_rc=0
container_suite_rc=0
```

- The Step-4b three-file patch SHA-256 was `453bb3374885f799e4066b619655fc04df132e5301e80514a8002af273b45257`; the host/container file receipts matched.
- Step 5 used the authorized soft reset to `363d812` and explicit staging of only the six Task-3 paths. Before commit, unstaged was empty and the cached set was exact. Discriminators were `3 / 6 / 1 / 6`; cached `repos{};` and `std::string dot{};` counts were each one; cached diff versus `retained-task3b-b09e192` was exactly the three checkpoint paths.
- The replacement used the plan's exact commit message. Postconditions hold: exactly four commits above base; both retention tags resolve to commit objects and are not branch ancestors; `manifest.hpp` is `2/2` versus `9e6ebe8`; `test_manifest.cpp` is `1/1` versus `b09e192`; diff versus `9e6ebe8` is exactly the six Task-3 paths; worktree and index are empty.
- Independent Task-3 specification and code-quality review returned CLEAN: one replacement commit, exact repair groups, inventory `64/8/3`, byte-equivalent error literals, unchanged propagation hunks, and preserved O/N/M surfaces.
- Independent review of the final 841-line Task-4 report returned CLEAN with no Critical, Important, or Minor findings: the exact C-1/C-3 transcripts, C-4 term/witness, mechanically reconciled A/B/P populations, T-1..T-5, actual Step-4b labels, (i)/(j)/E4 outputs, C-7, platform residual partition, and NOT-DONE boundary are supported.

## Task 4 newly measured receipts and green gates

The base-to-candidate scope census is exactly the ten-path allowlist, cardinality and membership. The production-scoped engine-caller census is empty with expected no-match rc 1. `kFormatVersion` remains literal `1`, byte-equal to base. C-5 CLI/schema and the M surface are byte-quiet. Writer emission has no `promisor` or `engine_source` key.

C-1 finds exactly three non-manifest serialization consumers, each consuming `expected<>`: `pack.cpp:765`, `test_cli.cpp:192`, and `test_open.cpp:131`. C-3 bounds hold: pack `5/2`, test_cli `3/1`, test_open `3/1`, zero non-bound semantic lines, and zero `repos` aggregate change in those files.

The derived inventory remains table A `64`, table B `8`, wire `3`; `FX-O-INV=72`, `FX-O-FIELD=7`, six unique FX-O legs, executable `O-MUTANT=8` plus the census marker = 9, `NAMED MUTANT=9`, and the positive unknown-note control is present. The shared writer and parser enforcement points remain present. `Shallow` has exactly one boundary member, zero mirror population/consumer surface, and the classifier order preserves tier-1 fences before shallow, shallow before unborn/dirty, and unborn before dirty. E4's direct request-trace test passed `13 assertions / 1 case` and asserts an empty request vector.

T-1 through T-5 hold at the candidate: header `2/2`; propagation aggregates untouched; keep-going census zero with the single equal-N coverage receipt; typed-error literal multiset byte-equal to `b09e192`; hunk-to-site map exactly four plus one; ondemand sites use checked `find_field_unordered(...).get(...)`; no NOLINT; inventory and enforcement unchanged; T-5 caller/no-bump fences re-run at the candidate.

## C-4 corrected term and witness — verbatim

On an O-R1 refusal at the pack.cpp Manifest-overload site, the writer refuses BEFORE the partial archive is opened (:765 precedes the ofstream at :769); cleanup_error removes partial_path and spool_path; NO NEW OR REPLACEMENT .bvpk is emitted; a PRE-EXISTING image at image_path, if any, is UNCHANGED (image_path is written only by the :801 rename, which is never reached). This is O-R1's "emitting NO output" at the pack level. Task 4 evidence STATES whether any FX-O leg exercises this pack-level path or the refusal is witnessed at the writer unit level only; no new pack-level test is REQUIRED by this term; silence on the point is a V-FA-7 red.

NO FX-O leg exercises this pack-level path; the refusal is witnessed at the WRITER UNIT LEVEL ONLY (legs (a)(b)(d.i)(d.ii) at `test_manifest`); no new pack-level test was added (none is required by the term)

The historical coordinates above are preserved verbatim. Fresh candidate coordinates re-derive the same order: serialize `:765`, partial archive open `:772`, final rename `:804`; `765 < 772 < 804`.

## Full-platform receipt partition

### macOS

Configure and build returned 0. Full CTest returned 8 only on registered/configured environment rows: ambient-name harness-selftest scanning, closed R-4.37 harness-e2, unavailable `readelf`, and configured ASan/tidy/fuzz skips. No credential value was exposed. The full `biv_tests` product binary and focused FX-O, FX-N, repository-engine, and E4 rows are green.

### Ubuntu 24.04 amd64

The full four-phase instrument used `--init`, read-only mounts, the pinned packages including `openssh-client`, exact candidate clone, suite user, raised non-root `nofile`, and no-short-circuit ledger. It reached CTest because every target built.

```text
base-provision=0
deb-provision=0
transition=0
fixture=0
nofile=0
harness-venv=0
configure=0
build=0
ctest=8
tidy-row-gate=0
a6-fabric-success=0
catch2-xml=0
count-read=1
linux_battery_aggregate_rc=1
container_suite_rc=1
```

All candidate product, tidy, hardening, Werror, E2, A6, and XML rows passed. CTest's only red was registered R-4.35: three harness race controls with 996 pass / 3 skip. The count reader observed `420/0/0/1` versus stale pinned `412/0/0/1`, the registered R-4.38 row; it is disclosed and never used as readiness evidence. The aggregate nonzero values derive only from those registered residuals. No candidate-attributable red exists.

Key Task-4 evidence hashes:

```text
e312a3c68de4cf622a9770737dbc39c887c3b957d54cec105bdfa5eb3ea398fe  static-fences.log
b39073941acbb64886f951c4cc8bd8a10e98f34dee1833347cbf00eb625bc5c2  macos-configure.log
a282885cbe7f3da446c88d6531acc35fe0045fe7a3d9328bbf791f8a090f7b06  macos-build.log
3d91beac405cf0b8e3d10c48dfe6d1ad95fde2eaa167b39b2c0c1d42222e4308  macos-ctest.log
d77d6d27f8d9905416966427578f4fe97f66b8761862536b3fae98ed31fe298e  linux-battery.log
```

## Requested routing and hard boundary

Route the exact candidate and report SHA through master for two parallel independent reviews:

1. m-1: V-FA-1 as extended by ruling `231935`, V-FA-2..8, O's cells, C-1..C-7, the (c)/(i)/(j) census, the label-correction target, ondemand spelling, C-4 statement/witness, T-1..T-5, Linux reach-to-CTest, and registered-residual non-citation.
2. m-3: C-6's byte window over the two test hunks at exact candidate SHA.

This is an implementation/evidence return, not a review result or merge token. `9e6ebe8` and `b09e192` are retained-superseded evidence only. The candidate cannot become a merge-packet input until both independent reviews return through master.

## Explicit NOT-DONE

- No sub-step 2b verb-to-engine wiring and no new production engine caller.
- No `--offline` parity arm; it remains product-scope-due under sealed N.
- No m-3 rendering or wording change; no new O-R1 envelope, exit code, or CLI text.
- No pack-level FX-O test; the required witness level is stated above.
- No schema, harness, workflow, CLI, M-surface, prompt, or envelope byte.
- No count-gate act, merge-ready claim, merge packet, landing, merge, push, PR, remote CI, publication, deployment, seal, release, or closure.

SCOPE_DIFF (the authorized TEN-path allowlist, exact base-to-candidate set):
- src/core/repo/classify.cpp -> in, tranche-1 classifier implementation
- src/core/repo/types.hpp -> in, tranche-1 boundary-only type surface
- src/core/repo/restore.cpp -> in, tranche-1 restore behavior
- src/core/manifest/manifest.hpp -> in, Task-3 signature plus T-1 initializer
- src/core/manifest/manifest.cpp -> in, tranche-1 and tranche-2 manifest implementation plus T-4 folds
- tests/test_repo_engine.cpp -> in, tranche-1 classifier/restore tests including E4
- tests/test_manifest.cpp -> in, tranche-1/tranche-2 tests plus exact dot initializer
- src/core/pack/pack.cpp -> in, ruling-231935 expected-error propagation only
- tests/test_cli.cpp -> in, ruling-231935 expected test adaptation only
- tests/test_open.cpp -> in, ruling-231935 expected test adaptation only
SCOPE_DIFF_RESULT: all-in; exact membership and cardinality 10

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: no — no credential value read, copied, printed, or retained
- migration/backfill/destructive-write/canonical-data-repair: no
- money/inventory/orders/planning/accounting/trust-critical-state: no
- AI-or-automation-acts-downstream: no — parse/serialize/classification/restore reach only; no new production caller
- worker/scheduler/queue/retry/async-side-effect: no
- cross-repo/service-contract/generated-schema/shared-API-event: yes — PDC-locked O/N/M contracts and owner rulings govern the exact byte review
- user-visible-control-with-materializer/downstream-consumer: yes — archive emission and later restore are user-visible, while 2b remains absent
- test-runtime-role-mismatch: no candidate-attributable mismatch — registered/configured environment and stale-count residuals are disclosed separately
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: yes — independent owner byte review and all downstream gates remain outstanding
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: none requested; no risk downgrade or acceptance is performed
- scan_presented_to_operator: no — not requested
- operator_reply_after_scan: none
- valid_waiver: no
WAIVED_RISK_ACCEPTANCE: none

ACTIONS_GIT_REF: under the addressed authority, intg/format-act moved from retained red b09e192 through the prescribed soft-reset assembly to the one replacement commit a2f6fd1adf67fd86c8d0c692db34f113a9691135; retained-task3-9e6ebe8 and retained-task3b-b09e192 remain local tag-only evidence; this engine-filed return is the only governed docs-lane write; no merge, push, PR, remote CI, publication, deployment, seal, release, or closure
RELAY_LINT: to be engine-rendered; draft pre-lint, exact-file lint, daemon status, INDEX receipt, and root verification follow submission
FINAL_GIT_STATUS_SHORT:
Candidate worktree `/Users/jack/Programming/bivpak-intg-format-act`: empty tracked and untracked status at a2f6fd1adf67fd86c8d0c692db34f113a9691135; index empty. Primary docs checkout contains inherited concurrent relay/docs state not authored or claimed clean by this seat; the engine-rendered relay and INDEX update will be the only governed changes attributable to this filing.
