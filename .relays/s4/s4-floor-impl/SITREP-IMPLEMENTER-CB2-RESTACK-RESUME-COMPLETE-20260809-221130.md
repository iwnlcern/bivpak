## SITREP — C→B2 restack resume complete: ruled per-session tests re-expressed, both exact heads host/Docker verified, merge trees clean, and draft PRs republished

ROLE: Implementer
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-floor-impl-2-cb2-restack-resume-complete
PARENT_DISPATCH_ID: s4-floor-impl-2-cb2-restack-resume
RUN_ID: s4
TASK_ID: B2
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — master's standing per-session ruling was carried exactly, the objection window closed with explicit orchestrator concurrence at 214526, and no new semantic choice or hard escalation trigger arose
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/IMPL-PLANNER-CB2-RESTACK-RESUME-PER-SESSION-RULED-DISPATCH-IMPL-TOKEN-20260809-213224.md
FROM: s4-floor.implementer
TO: s4-floor.planner
CC: s4.orchestrator-planner, operator
SUBJECT: DONE_WITH_CONCERNS — C d6e44d9 and final B2 0653fea are clean one-commit stacked heads; the three inherited tests now preserve A-BL1 while pinning ruled per-session verify-hits; host and classified Docker bars complete; PR #22/#23 republished exact; targeted re-verification requested

DONE_WITH_CONCERNS / RESTACK RESUME COMPLETE

The concern is evidence classification, not a new implementation defect: the repository's
Linux Catch2 workflow gate still expects the historical `223/0` count, while both exact
heads contain larger suites and the Ubuntu `linux/amd64` container reproduces the standing
Rosetta-only spawn-classification exception. Every substantive and narrowed Linux gate is
green. The exact measured counts and classified exits are disclosed below.

## Final topology and scope

Slice C is unchanged from the clean candidate authorized by the resume token:

- branch `s4-floor/c-consent-no-carrier`;
- head `d6e44d9e5ec4ff48e5121a9674ef7788eca9e881`;
- parent `721eeaefd168c917e4ee4cadf7cd0366baa43514`;
- exactly one commit with preserved subject
  `feat(open): stage consent-no sessions with provenance sidecar`;
- exactly the previously verified 24-path paneled range.

Final B2 is:

- branch `s4-floor/b2-torn-tail`;
- head `0653fea400e83a59f4c3a9d7983510222e9159ec`;
- parent `d6e44d9e5ec4ff48e5121a9674ef7788eca9e881`;
- exactly one commit with preserved subject
  `feat(pack): collect torn tails and staged sidecars`;
- exactly 17 paths: the standing 16-path paneled B2 range plus the newly granted
  `tests/test_sessions.cpp`; no eighteenth path.

Both isolated worktrees were clean immediately before publication and remained clean
after publication. C's 24-path delta did not change. Within B2, the only new logical
change beyond the previously paneled 16-path content is the authorized re-expression in:

- `tests/test_adapter_claude_install.cpp`;
- `tests/test_adapter_codex_install.cpp`;
- `tests/test_sessions.cpp`.

No production byte changed for the resume amendment. The Claude collector SHA-256 is
`203c28e9cddc39ec51d16ad0c7eb1111dfffdb2bf31003cc7b94cd3aa86ee42c` and the Codex
collector SHA-256 is
`32588435f94e42536d77a8b48a7112bc635b7bd86c64781900789e79d44b6f9d`.
Both collectors and `harness/bivharness/e3.py` are byte-identical to paneled B2 head
`6a8ea75a2d7ae072839940e69b16f6393c80ac32`; anchor recapture did not fire.

## Ruled three-test amendment

The pre-edit reproduction selected the exact three inherited cases and failed all three:
41 assertions, ten failed. The fixtures had been pinning the superseded cohort result and,
for the install cases, entered the undecodable-line arm before exercising origin hits.

The bounded amendment uses valid JSON fixtures and preserves each test's A-BL1 purpose:

- the version/capability-refusal row remains present as `not-validated` with its typed
  basis detail;
- the verify-hit sibling is asserted per session as `verify-hits`, with detail
  `origin_path` or `origin_id` and its path/ID hit counters intact;
- the clean sibling remains unaffected and activation remains suppressed where required;
- no test or assertion was deleted, and the tests still fail if either the preserved
  refusal guarantee or the ruled per-session guarantee regresses.

After the edit, the exact three cases passed all 41 assertions. After the amendment was
folded into the single B2 replay commit, the seven-case ruled-plus-I3/F2/F3/key cohort
passed all 84 assertions.

## Host verification

At unchanged C `d6e44d9`, the standing fresh host evidence remains applicable because the
resume amendment did not force a C restack:

- A3 drift-tripwire/control cohort: 12 passed, 844 deselected;
- compare selftests: 15 passed;
- staged/consent focused product cohort: 333 assertions in 12 cases passed;
- `ctest --preset dev -E '^safety-hardening$' --output-on-failure`: 14 of 14 selected
  rows passed, zero failures, 443.69 seconds; three configured safety rows skipped.

At final B2 `0653fea`:

- A3 drift-tripwire/control cohort: 12 passed, 844 deselected;
- ruled three-case cohort: 41 assertions in three cases passed;
- expanded seven-case focused cohort: 84 assertions in seven cases passed;
- `ctest --preset ci-macos -E '^safety-hardening$' --output-on-failure`: 14 of 14
  selected rows passed, zero failures, 501.98 seconds; `biv_tests` passed in 318.69
  seconds, harness E2 passed in 176.45 seconds, and only the three configured safety rows
  skipped.

## Local Ubuntu 24.04 `linux/amd64` Docker parity

No GitHub Actions test was used as a Linux substitute. After all implementation and host
testing were complete, each exact head was cloned clean and detached into a disposable
Ubuntu 24.04 container launched with `--platform linux/amd64`. Each run verified the eight
immutable LLVM mirror package hashes, package names, exact version
`1:22.1.8~++20260613092238+e80beda6e255-1~exp1~20260613092253.78`, and amd64 architecture;
observed clang-tidy was LLVM 22.1.8 and the compiler was GNU 13.3.0.

At C `d6e44d9`:

- configure, build, core-adapter purity, E2, `safety-build-werror`, executed
  `safety-tidy-analyzer`, hardening, and generated-envelope schema gates passed;
- full product: 268 passed and one failed out of 269; the sole failure was the standing
  `version probe does not fall back to PATH when a pinned executable cannot spawn` case;
- canonical harness: 967 passed, four known overlay sentinels failed, three skipped;
- narrowed product excluding the known probe case: 7,059 assertions in 268 cases passed;
- narrowed harness excluding the four known sentinels: 967 passed, three skipped, four
  deselected;
- substantive-row, tidy-row, known-needle, narrowed-product, narrowed-harness, and schema
  classifiers all returned zero;
- classified wrapper exit: 21 only because the historical Catch2 `223/0` count gate saw
  `268/1`; Catch2 execution itself returned only the known probe failure.

At final B2 `0653fea`:

- configure, build, core-adapter purity, E2, `safety-build-werror`, executed
  `safety-tidy-analyzer`, hardening, and generated-envelope schema gates passed;
- full product: 322 passed and one failed out of 323; the sole failure was the same
  standing probe case;
- canonical harness: 969 passed, two known overlay sentinels failed, three skipped;
- narrowed product excluding the known probe case: 8,217 assertions in 322 cases passed;
- narrowed harness excluding the four-class known-sentinel set: 967 passed, three
  skipped, four deselected;
- substantive-row, tidy-row, known-needle, narrowed-product, narrowed-harness, and schema
  classifiers all returned zero;
- classified wrapper exit: 21 only because the historical Catch2 `223/0` count gate saw
  `322/1`; Catch2 execution itself returned only the known probe failure.

The two configured container skips were `safety-asan-ubsan` and `safety-fuzz-smoke`, as in
the repository configuration. No unrelated Docker resource was pruned or removed.

## Merge-tree and publication receipts

Conflict-free merge-tree receipts were produced before publication:

- remote `main` `8981bfd0848039d533d9bb2a96301d4d81b564fa` → C `d6e44d9`:
  tree `e4c0c4f453db4ded4988f29ca5d443ebe6941c8e`;
- current local docs `main` `ea97204a322a57393484dadf6701b37a073bfaf1` → C `d6e44d9`:
  tree `abb2fa04582da8794324b75dd574eedf00902844`;
- C `d6e44d9` → B2 `0653fea`:
  tree `8ecd683ed2ff74affdb2dfb596e8667c2d930d99`.

Remote leases were re-read immediately before publication, then explicit
`--force-with-lease=<ref>:<old-sha>` guards moved only the two authorized branches:

- PR #22 branch from `ec9a2db2cfe55191f99efbcf12902a79d99e159e` to exact C
  `d6e44d9e5ec4ff48e5121a9674ef7788eca9e881`;
- PR #23 branch from `6a8ea75a2d7ae072839940e69b16f6393c80ac32` to exact B2
  `0653fea400e83a59f4c3a9d7983510222e9159ec`.

Post-push remote and PR queries agree on both exact heads. PR #22 and PR #23 remain OPEN,
DRAFT, and based on `main` under the locked repository topology. Implementation and all
local host/Docker validation finished before either push. GitHub Actions was not manually
invoked, rerun, cancelled, or managed; no Actions result is claimed here.

## Boundaries and handoff

Orphan R-4.9, R-4.8, and the Minors were not touched. No merge, release, deployment, or
live-behavior claim was made. The operator's release hold remains ABSOLUTE.

The requested next act is the planner's targeted verification at exact C `d6e44d9` and B2
`0653fea`, followed by fresh condition-3 hand-ups in C-first/B2-immediate order.

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: no — local adapter/session tests and authorized branch publication only
- migration/backfill/destructive-write/canonical-data-repair: no — no persisted data mutation
- money/inventory/orders/planning/accounting/trust-critical-state: no — not in scope
- AI-or-automation-acts-downstream: no — no downstream automated act was added
- worker/scheduler/queue/retry/async-side-effect: no — not in scope
- cross-repo/service-contract/generated-schema/shared-API-event: no — existing repository-local surfaces only; no new schema byte in the resume amendment
- user-visible-control-with-materializer/downstream-consumer: no — the per-session surface was already ruled and paneled
- test-runtime-role-mismatch: no — host and exact detached Linux product/harness rows exercised the amended tests
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: no — the only semantic cell was explicitly ruled and concurred; known Linux exceptions and stale count gate are disclosed, classified, and narrowed
ESCALATION_SCAN_RESULT: all-no
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: none
- scan_presented_to_operator: yes — this addressed completion report includes the scan and exact classified evidence
- operator_reply_after_scan: not required
- valid_waiver: not applicable
WAIVED_RISK_ACCEPTANCE: none

ACTIONS_GIT_REF: local C `d6e44d9e5ec4ff48e5121a9674ef7788eca9e881` and B2 `0653fea400e83a59f4c3a9d7983510222e9159ec` were force-with-lease published to their existing authorized branches and verified as draft PR #22/#23 heads; this report and its append-only INDEX row are the only writes by this seat in the shared docs checkout; no PR metadata edit, manual Actions operation, merge, release, deployment, or unrelated Docker cleanup
FINAL_GIT_STATUS_SHORT: C worktree clean at d6e44d9; B2 worktree clean at 0653fea; shared main retains pre-existing sibling untracked relay artifacts and a sibling INDEX append, all preserved; this seat adds only this report and its own INDEX append

CARRY LIST:
- exact C `d6e44d9` / PR #22 and exact B2 `0653fea` / PR #23 → `s4-floor.planner` for targeted re-verification and fresh C-first/B2-immediate condition-3 hand-ups
- Docker concern → substantive and narrowed gates green; standing Rosetta/overlay exceptions plus stale historical `223/0` count gate disclosed exactly
- GitHub Actions → unmanaged; no result claimed
- orphan R-4.9, R-4.8, Minors, merge, release, and deployment → untouched; release hold ABSOLUTE
