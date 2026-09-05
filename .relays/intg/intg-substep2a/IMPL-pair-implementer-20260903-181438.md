## IMPL STOP RETURN — replacement candidate `b09e192` is frozen: macOS product rows and static fences are green, but Ubuntu 24.04 GCC and clang-tidy are candidate-attributable red; the pack initializer repair is outside C-2/C-3's NOTHING-else grant

ROLE: Pair Implementer
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: intg-substep2a-impl-3
PARENT_DISPATCH_ID: intg-substep2a-plan-review-12
IN_REPLY_TO: intg-substep2a/IMPL-pair-planner-20260903-153402.md
RELATED_CONTEXT: intg-substep2a/PLAN-pair-planner-20260902-070149.md; intg-substep2a/PLAN-REVIEW-pair-implementer-20260903-141140.md; intg-substep2a/SITREP-pair-planner-20260903-154413.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep2a-20260830.md; ../../../pdc/master/relays/intg-substep2a-format-act/DESIGN-planner-20260901-231935.md; ../../../pdc/master/relays/intg-substep2a-format-act/DESIGN-planner-20260902-034802.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — Task 4 found candidate-attributable Linux build and tidy reds; the necessary `pack.cpp` aggregate-initializer byte is outside the exact C-2/C-3 propagation hunk, which says NOTHING else, so the execution-not-amendment STOP fires. Obtain an owner ruling, successor exact-hash plan/review, and fresh addressed implementation token before any product edit or rerun. m-1/m-3 byte review, merge packet, landing, count-gate observations, push, publication, deployment, and release remain held; the release hold is ABSOLUTE
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
PLAN_LOCK_ID: intg-substep2a-plan-20260830 @ sha256 e5875e8ee830265743e05c09db2224d2bca956f9dba7ed7372cfc417889dd2bc
BASE: main@46df8f3c35981a4ae3f77cf3293a4b7212b4b996
BRANCH: intg/format-act@b09e1922c16da50b5bef0644d9923a567b98c468 in /Users/jack/Programming/bivpak-intg-format-act; status empty; four commits above base; retained-task3-9e6ebe8 resolves to 9e6ebe8fca2454164051573323dd7adfa2901219; frozen red candidate, NOT merge-ready
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: master.master-planner, master.master-reviewer, m-1.planner, m-1.implementer, m-3.planner, m-3.implementer
SUBJECT: STOP UP — Task 4 Linux parity finds the new `Manifest::repos` carrier missing from pack's aggregate initializer plus four manifest tidy reds; rule the exact correction scope, then issue a successor plan/review/token; no byte moves under this consumed token

## Disposition and exact stop point

The `153402` token was consumed in order: Step 0-bis, Task 3 Steps 4 through 6, one replacement commit, and the clean-Task-3 review loop completed before Task 4 opened. Task 4 ran the static fence battery, macOS suite, and canonical Ubuntu 24.04 amd64 H/R/T/S instrument. Linux build and tidy produced new candidate-attributable reds.

```text
/work/src/core/pack/pack.cpp:764:3: error: missing initializer for member 'biv::manifest::Manifest::repos' [-Werror=missing-field-initializers]
build_rc=2
```

`Manifest` now declares `repos` before `agent_sessions`; the existing pack aggregate proceeds from `.packer_home` directly to `.agent_sessions`. The apparent minimal correction is `.repos = {}`. It is not authorized: plan and dispatch bind `pack.cpp` to the fallible-serialize propagation hunk alone and say NOTHING else; the out-of-scope section repeats that any byte beyond C-2 is hard-out. No repair, stage, or amend followed.

```text
HEAD=b09e1922c16da50b5bef0644d9923a567b98c468
HEAD^=363d812fba2610f7e5c71fdb9daee5c7f740027a
rev-list --count 46df8f3..HEAD=4
retained-task3-9e6ebe8=9e6ebe8fca2454164051573323dd7adfa2901219
git status --short --untracked-files=all=EMPTY
git diff --name-only=EMPTY
```

## Task 3 and static receipts

- Step 0-bis verified the frozen checkpoint and deleted only the two struck remotes clauses and arms. Corrected checkpoint tables read A=40, B=8, FX-O-INV=48.
- Final reviewed inventory after helper/coordinate expansion reads A=64, B=8, FX-O-INV=72, parser-local P=122; FX-O-FIELD=7, FX-O-LEG=6, O-MUTANT=8 plus census, inherited NAMED MUTANT=9.
- A fresh Task-3 reviewer returned Specification compliance CLEAN and Code quality CLEAN at `b09e192` before Task 4. This does not waive the later Linux red.
- base-to-HEAD membership/cardinality equals the TEN-path allowlist; `9e6ebe8..HEAD` equals the six Task-3 paths; production caller grep empty rc 1; format-version literal unchanged.
- C-1: exactly three ruled `serialize` callers consuming `expected<>` at pack `:765`, test_cli `:192`, test_open `:131`.
- C-3: pack `+5/-2`, test_cli `+3/-1`, test_open `+3/-1`; zero non-bound changed lines.
- C-4: serialize `765` precedes partial-open `772`; only image-path write is rename `804`. NO FX-O leg exercises this pack-level path; refusal is writer-unit-only; no pack-level test was added or required.
- C-5 CLI/schema rc 0; no promisor/engine_source emission; M surface quiet; (i)/(j) and E4 request-trace green.
- Local report `.superpowers/sdd/PL-intg-substep2a-20260830/task-4-report.md` hashes to `0aabaa95138b1b29cd93aa71e598056bc1e74a5d57e73293b3d32ca6436b704f`. A fresh post-correction reviewer returned Specification compliance CLEAN and Evidence quality CLEAN. This relay carries material results because the local report is not a governed merge artifact.

## macOS evidence

```text
configure=0; build=0
ctest=8: 16/19 accounted; 3 configured skips
FX-O*=803 assertions/11 cases rc 0
FX-N*=135 assertions/5 cases rc 0
E4 direct=13 assertions/1 case rc 0
classifier/E4 slice=47 assertions/5 cases rc 0
```

Candidate product rows passed. Full-CTest rows are partitioned: ambient `ANTHROPIC_API_KEY` scan without value exposure; registered closed R-4.37 timeout/bytes-string path; `readelf unavailable`; configured sanitizer/tidy/fuzz skips.

## Ubuntu 24.04 amd64 evidence — blocking

Docker used `--platform linux/amd64 --init`, read-only host inputs, suite-user `nofile` 1024→1048576. Eight pinned LLVM 22 debs passed strict SHA256 verification. No credential was copied or printed.

```text
expected_head=b09e1922c16da50b5bef0644d9923a567b98c468
observed_head=b09e1922c16da50b5bef0644d9923a567b98c468
base-provision=0; deb-provision=0; transition=0; fixture=0
nofile=0; harness-venv=0; configure=0; build=2; ctest=8
tidy-row-gate=1; a6-fabric-success=127; catch2-xml=127; count-read=1
linux_battery_aggregate_rc=1; container_suite_rc=1
```

Safety-build repeats the missing-`repos` GCC failure. Tidy ran and reports:

```text
manifest.cpp:836:33  bugprone-easily-swappable-parameters
manifest.cpp:905:20  cppcoreguidelines-avoid-const-or-ref-data-members
manifest.cpp:2176:34 cppcoreguidelines-pro-bounds-avoid-unchecked-container-access
manifest.cpp:2179:39 cppcoreguidelines-pro-bounds-avoid-unchecked-container-access
pack.cpp:764:3       clang-diagnostic-missing-designated-field-initializers
```

Four manifest locations blame to `b09e192`. The pack brace is inherited from `26deee05`, but its diagnostic is candidate-attributable because `b09e192` inserted intervening `repos` without initializing it. Later missing executables, E2 missing `biv`, hardening missing binary, and A6/Catch/count failures are build consequences. R-4.35 is retained-not-cited (Linux selftest 3 failed/996 passed/3 skipped); R-4.38 could not be remeasured because no Catch binary built.

## Required ruling and resume conditions

Return an exact successor that:

1. authorizes the `pack.cpp` aggregate correction beyond C-2/C-3, or specifies another correction;
2. re-censuses every `Manifest{...}` aggregate under GNU `-Wmissing-field-initializers`, naming any additional paths/hunks;
3. specifies corrections for the four `manifest.cpp` tidy rows, or adjudicates their gate status without claiming tidy green;
4. preserves O/N/M locks, serializer/parser semantics, no format bump, no new caller, and path ceiling unless deliberately re-ruled;
5. requires a new SHA and fresh Task-4 evidence before m-1/m-3 review.

Resume only through a successor exact-hash plan, fresh Pair Implementer review, and fresh addressed token. `153402` is consumed. m-1 V-FA/O/(c)/(i)/(j) and m-3 C-6 reviews at `b09e192` are NOT requested because it is red.

## Explicit NOT-DONE

- No Linux-red correction or further product/test byte.
- No 2b wiring, `--offline` parity, m-3 rendering, pack-level FX-O arm, or count-gate observation.
- No merge-ready claim, merge packet, landing, push, PR, remote CI, publication, deployment, seal, or release.
- Count-gate approval stays held behind a successful tranche-2 landing per `154413`.

SCOPE_DIFF (candidate base-to-HEAD equals this authorized TEN-path set):
- src/core/repo/classify.cpp -> in
- src/core/repo/types.hpp -> in
- src/core/repo/restore.cpp -> in
- src/core/manifest/manifest.hpp -> in
- src/core/manifest/manifest.cpp -> in
- tests/test_repo_engine.cpp -> in
- tests/test_manifest.cpp -> in
- src/core/pack/pack.cpp -> in
- tests/test_cli.cpp -> in
- tests/test_open.cpp -> in
SCOPE_DIFF_RESULT: all-in

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: no — no credential value read or recorded
- migration/backfill/destructive-write/canonical-data-repair: no
- money/inventory/orders/planning/accounting/trust-critical-state: no
- AI-or-automation-acts-downstream: no — parse/serialize reach only
- worker/scheduler/queue/retry/async-side-effect: no
- cross-repo/service-contract/generated-schema/shared-API-event: yes — PDC-locked surface and exact ruled hunk
- user-visible-control-with-materializer/downstream-consumer: yes — archive emission and later restore; 2b absent
- test-runtime-role-mismatch: yes — canonical Linux is red
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: yes — pack/tidy repairs exceed current exact-hunk grant
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: none
- valid_waiver: no

ACTIONS_GIT_REF: no product ref move after b09e192; candidate clean/frozen; this engine-filed STOP relay is the only new governed docs-lane action; no merge, push, PR, remote CI, publication, deployment, seal, or release
RELAY_LINT: engine-rendered submission; per-file lint rides daemon gate; exact-file lint and root verify follow filing
FINAL_GIT_STATUS_SHORT:
Candidate worktree `/Users/jack/Programming/bivpak-intg-format-act`: EMPTY at b09e1922c16da50b5bef0644d9923a567b98c468. Primary docs checkout contains inherited concurrent relay/docs state not authored or claimed clean by this seat.
