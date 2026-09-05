## IMPL STOP RETURN — revision-13 Step 4b is RED at the all-target Linux census; the held two-file repair remains uncommitted and `tests/test_manifest.cpp` is outside this checkpoint's write set

ROLE: Pair Implementer
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: intg-substep2a-impl-4
PARENT_DISPATCH_ID: intg-substep2a-plan-review-13
IN_REPLY_TO: intg-substep2a/IMPL-pair-planner-20260903-211946.md
RELATED_CONTEXT: intg-substep2a/PLAN-pair-planner-20260903-184850.md; intg-substep2a/PLAN-REVIEW-pair-implementer-20260903-210020.md; intg-substep2a/IMPL-pair-implementer-20260903-181612.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep2a-20260830.md; ../../../pdc/master/relays/intg-substep2a-format-act/DESIGN-planner-20260903-183510.md; ../../../pdc/master/relays/intg-substep2a-format-act/PLAN-master-planner-20260903-183926.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — Step 4b's every-target build stopped on `tests/test_manifest.cpp:1364`, whose required aggregate-initializer correction is explicitly outside Step 0-ter's exact `manifest.hpp` + `manifest.cpp` checkpoint write set and is bound as NO-edit-under-this-token. Obtain an owner ruling, successor exact-hash plan/review, and fresh addressed implementation token before any additional product or test byte, reset, replacement commit, or rerun. m-1/m-3 byte review, merge, landing, count-gate observations, push, PR, publication, deployment, and release remain held; the release hold is ABSOLUTE
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
PLAN_LOCK_ID: intg-substep2a-plan-20260830 @ sha256 f59b90172806416f4dbc5c13afae4ee00c72a3babd16d9717054f0c026d8af0b
BASE: main@46df8f3c35981a4ae3f77cf3293a4b7212b4b996
BRANCH: intg/format-act at b09e1922c16da50b5bef0644d9923a567b98c468 in /Users/jack/Programming/bivpak-intg-format-act; retained-task3b-b09e192 resolves to that frozen red candidate; working tree intentionally holds exactly two unstaged modified paths, `src/core/manifest/manifest.hpp` and `src/core/manifest/manifest.cpp`; no replacement commit was cut
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: master.master-planner, master.master-reviewer, operator, m-1.planner, m-1.implementer, m-3.planner, m-3.implementer
SUBJECT: STOP UP — Step 0-ter's two-file repair and macOS gate are green, but the pre-commit Ubuntu 24.04 all-target census stops on the inherited first `PathMutation` aggregate omitting `.dot`; rule that exact test byte and the ondemand lookup spelling, then issue a successor plan/review/token

## Disposition and exact stop point

The `211946` token was consumed in order through Step 0-ter, the macOS Step 4 gate, and the Step 4b Linux census. Step 0-ter created the authorized local retention tag and applied only the exact header hunk plus four structural `manifest.cpp` folds. The Linux all-target build then reached `biv_tests` and stopped here:

```text
/work/tests/test_manifest.cpp:1364:65: error: missing initializer for member 'CATCH2_INTERNAL_TEST_48()::PathMutation::dot' [-Werror=missing-field-initializers]
build_rc=2
```

The local `PathMutation` has four members; its first aggregate initializes `detail`, `absolute`, and `traversal` but omits `dot`. The apparent minimal correction is an explicit empty `.dot`, or an owner-approved default member initializer. This token explicitly says NO edit to `tests/test_manifest.cpp` at the Step 0-ter checkpoint. The mandatory STOP therefore fired: this seat made no test-file repair, did not reset, did not stage, did not commit, and did not begin Step 5, Step 6, or Task 4.

```text
HEAD=b09e1922c16da50b5bef0644d9923a567b98c468
HEAD^=363d812fba2610f7e5c71fdb9daee5c7f740027a
retained-task3-9e6ebe8=9e6ebe8fca2454164051573323dd7adfa2901219
retained-task3b-b09e192=b09e1922c16da50b5bef0644d9923a567b98c468
git diff --name-only=src/core/manifest/manifest.cpp + src/core/manifest/manifest.hpp only
manifest.hpp checkpoint numstat=1/1
git diff --check=0
```

The held patch is recoverable at `/tmp/bivpak-intg-rev13.UzYi28/rev13-two-file.patch`, sha256 `4abbcbffed0a67d23295286c156efd92d9650ccc207c269741f33a70daa4e226`. Current source receipts are:

```text
manifest.hpp fd12d52bf4d87fcc2cbabb7fae1e957fdbb796e5362499e9030e99ed47c46bc7
manifest.cpp f7a89c8cfa12c4312b33aa2ea83be8adff01d21c6f8582a80999e80a383869af
```

## Step 0-ter and macOS receipts

- The frozen-state gate matched exactly before any byte: HEAD `b09e192`, parent `363d812`, four commits above `46df8f3`, empty status, and the original retention tag at `9e6ebe8`.
- `retained-task3b-b09e192` was created locally and was not pushed.
- The checkpoint diff contains exactly the two manifest paths. The header change is exactly `repos;` to `repos{};`, +1/-1. `pack.cpp`, `test_cli.cpp`, `test_open.cpp`, and `test_manifest.cpp` were untouched; no per-site `.repos = {}` was added.
- The typed-error literal multiset remained byte-equal to `retained-task3b-b09e192`; the row/writer-image/wire inventories remained 64/8/3 and both enforcement points remained present.
- The four `manifest.cpp` folds map only to the dispatched sites: string-literal key typing for `parse_enum_field`, pointer storage for `RepoRowFacts::row`, and checked named lookups for the two ondemand arrays. No NOLINT was used.
- The plan named `at_key`, but compilation established that simdjson's ondemand document/object types do not expose that DOM-only method. The held implementation uses checked `find_field_unordered(...).get(array)`, the ondemand named-lookup primitive underlying `operator[]`, and preserves the existing thrown simdjson error route. This exact spelling should be expressly accepted or replaced in the successor ruling; no widening was attempted after STOP.
- macOS configure and final build passed. `FX-O*` passed 803 assertions / 11 cases; `FX-N*` passed 135 / 5; `biv_repo_engine_tests` passed 452 / 60; the full `biv_tests` binary passed 418 of 421 cases with 3 configured skips and all 16,343 executed assertions green.

## Ubuntu 24.04 amd64 Step 4b receipts — blocking

The census used Ubuntu 24.04, `--platform linux/amd64 --init`, a read-only source origin and read-only patch/assets, suite uid/gid 1001, and raised `nofile` soft 1024 to inherited hard 1048576. All eight pinned LLVM-22 assets passed strict SHA256 verification after one disclosed operator invocation defect: the first check ran from the wrong directory and therefore found no relative asset paths; it was immediately rerun from the mirror directory and all eight verified `OK`. No failed invocation was counted as a receipt.

The container cloned exact `b09e192`, applied the two-file patch after `git apply --check`, and reproduced both host source hashes. Base provision, deb provision, transition, fixture generation, nofile raise, and configure all returned 0. The configured compiler was GNU 13.3 with clang-tidy 22. The all-target build advanced through product and most test targets, then stopped at 91% on the out-of-scope test aggregate above.

The required isolated tidy row still ran without short-circuit and passed 1/1 in 47.24 seconds (`tidy_rc=0`). The evidence script then printed the two-file grep counts as two filename-qualified lines and attempted an integer comparison, producing `integer expression expected`; its `tidy_coverage_count=0` parser likewise is not an admissible N-sources coverage receipt. This instrumentation defect is separate from, and cannot mask or cure, the already-decisive compiler red. The retained combined log is `/tmp/bivpak-intg-rev13.UzYi28/step4b-linux.log`; terminal aggregate was 1.

## Required ruling and resume conditions

Return an exact successor that:

1. authorizes the exact `tests/test_manifest.cpp` aggregate correction, or specifies another exact solution, despite the current checkpoint's NO-edit binding;
2. rules whether the checked ondemand `find_field_unordered` spelling satisfies T-4's named-lookup requirement, or specifies a compiling exact alternative;
3. repairs the Step 4b evidence counter so the missing-initializer total is numeric and the tidy N-results/N-sources coverage receipt is non-vacuous;
4. requires the entire Step 4b every-target census to be rerun from configure through build and isolated tidy, because the stopped build may conceal another diagnostic;
5. preserves O/N/M, parser acceptance/detail strings, wire bytes, inventory 64/8/3, the two enforcement points, the ten-path ceiling, and every downstream hold unless deliberately re-ruled.

Resume only through a successor exact-hash plan, fresh Pair Implementer exact-byte review, and fresh addressed implementation token. `211946` is consumed. The uncommitted two-file repair and both retention tags remain frozen for that successor.

## Explicit NOT-DONE

- No edit outside `manifest.hpp` and `manifest.cpp`; specifically no `test_manifest.cpp` repair.
- No reset, staged tree, replacement commit, Task-3 Step 6, Task 4, or new candidate SHA.
- No m-1 V-FA/O/(c)/(i)/(j) request and no m-3 C-6 request because there is no green replacement candidate.
- No merge-ready claim, merge packet, landing, count-gate observation, push, PR, remote CI, publication, deployment, seal, or release.

SCOPE_DIFF (the plan's authorized TEN-path allowlist; this token changed only the two Step 0-ter paths before STOP):
- src/core/repo/classify.cpp -> in, unchanged under this token
- src/core/repo/types.hpp -> in, unchanged under this token
- src/core/repo/restore.cpp -> in, unchanged under this token
- src/core/manifest/manifest.hpp -> in, modified exactly at T-1
- src/core/manifest/manifest.cpp -> in, modified only at the four T-4 sites
- tests/test_repo_engine.cpp -> in, unchanged under this token
- tests/test_manifest.cpp -> in allowlist but explicitly NO edit at this checkpoint; blocking byte not made
- src/core/pack/pack.cpp -> in, unchanged under this token
- tests/test_cli.cpp -> in, unchanged under this token
- tests/test_open.cpp -> in, unchanged under this token
SCOPE_DIFF_RESULT: all-in; checkpoint write set exactly two paths

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: no — no credential value read or recorded
- migration/backfill/destructive-write/canonical-data-repair: no
- money/inventory/orders/planning/accounting/trust-critical-state: no
- AI-or-automation-acts-downstream: no — parse/serialize reach only
- worker/scheduler/queue/retry/async-side-effect: no
- cross-repo/service-contract/generated-schema/shared-API-event: yes — PDC-locked implementation surface and exact owner ruling
- user-visible-control-with-materializer/downstream-consumer: yes — archive emission and later restore are user-visible, though 2b remains absent
- test-runtime-role-mismatch: yes — canonical Linux all-target build is red
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: yes — the required test byte is outside this checkpoint and the ondemand spelling plus evidence counter require explicit disposition
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: none
- valid_waiver: no

ACTIONS_GIT_REF: created only the authorized local retention tag `retained-task3b-b09e192`; branch ref remains b09e192 with exactly two unstaged manifest-path edits; this engine-filed STOP relay is the only governed docs-lane write; no reset, commit, merge, push, PR, remote CI, publication, deployment, seal, or release
RELAY_LINT: engine-rendered submission; draft pre-linted per-file; exact-file lint and root verify follow filing
FINAL_GIT_STATUS_SHORT:
Candidate worktree `/Users/jack/Programming/bivpak-intg-format-act`: exactly two unstaged modifications, `src/core/manifest/manifest.cpp` and `src/core/manifest/manifest.hpp`, at b09e1922c16da50b5bef0644d9923a567b98c468. Primary docs checkout contains inherited concurrent relay/docs state not authored or claimed clean by this seat.
