## SITREP — B2 amend is host-green and its scoped re-review passes, but final whole-branch review finds a staged-path precedence Important outside the live three-file token; Docker and PR republication held

ROLE: Implementer
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-floor-impl-2-b2-final-review-precedence-blocker
PARENT_DISPATCH_ID: s4-floor-impl-2-b2-amend-fold
RUN_ID: s4
TASK_ID: B2
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — authorize or disposition the final-review staged-path precedence fix because its required common-rewrite and Codex-test paths are outside the live three-file amend token; Docker, PR republication, Actions, merge, and release remain held
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/IMPL-PLANNER-B2-AMEND-E2-600-DISPATCH-IMPL-TOKEN-20260809-063737.md
FROM: s4-floor.implementer
TO: s4-floor.planner
CC: s4.orchestrator-planner, operator
SUBJECT: BLOCKED — exact 600-second amend and host suite pass at 3f2dd3e, but broad final review requests longest-source-first staged-path rewriting outside the live scope

BLOCKED / SCOPE DISPOSITION REQUIRED

## Summary

The live amend was executed exactly: the independently approved round-2 Claude delta and
the single `harness-e2` `TIMEOUT 180` to `TIMEOUT 600` line were amended into B2's one
commit. Focused tests and the full host suite are green. The scoped three-path re-review
passes with the earlier pre-refused-alias Important addressed and no new Critical or
Important breakage.

The mandatory final whole-branch review then found one new Important in the earlier staged
path fix. `derive_install_pair_set` appends original-path pairs before staging-root pairs,
and JSON rewriting applies them in that order. When a staging root is a descendant of the
original path, the shorter original prefix rewrites first, the exact staging-root pair then
misses, and verification sees neither original needle. The install can therefore publish
JSONL containing the wrong workspace path while reporting zero origin-path hits.

## PR and exact branch state

PR: draft #23, `https://github.com/iwnlcern/bivpak/pull/23`, remains at remote head
`d6cceba9321d693d8e302e89b796ca159a0f8f66`. It was not republished.

Local candidate:

- head: `3f2dd3ead60f50a06d3951d69bf46b8afa2becf1`
- parent: `ec9a2db2cfe55191f99efbcf12902a79d99e159e`
- commit count above parent: `1`
- subject: `feat(pack): collect torn tails and staged sidecars`
- tracked worktree: clean

Plan lock: `s4-floor-fold-plan-20260805`; operative amend dispatch
`s4-floor-impl-2-b2-amend-fold`.

## Files changed by the authorized amend

Relative to held head `9977a15f7d9957acb8d643a7919b24196293b0a9`, the amended commit changes
exactly:

- `src/adapters/claude_code/install.cpp`
- `tests/test_adapter_claude_install.cpp`
- `harness/CMakeLists.txt`

The CMake delta is exactly one deletion and one insertion: `TIMEOUT 180` to
`TIMEOUT 600`. Neither A3 anchored collector changed, so the mechanical A3 check passed
and recapture did not re-fire.

## Acceptance criteria and verification

- pre-edit `FOLD_SCOPE`: rewritten to the exact three authorized paths, `all-in`;
- focused Claude union/refusal/composed cohort: 192 assertions in 6 cases passed before
  and after amend;
- harness selftest: 975 passed before and after amend;
- full host suite: 14 of 14 selected rows passed, including `biv_tests` in 319.15s,
  `harness-selftest` in 5.11s, and `harness-e2` in 179.16s under the durable 600-second
  budget; three configured safety rows skipped; total 505.62s;
- `git diff --check` on the whole one-commit range: pass;
- scoped review of `9977a15..3f2dd3e`: PASS; earlier pre-refused staged Claude child-alias
  finding ADDRESSED; no new Critical/Important amendment breakage;
- final review of `ec9a2db..3f2dd3e`: CHANGES REQUESTED on the staged-path precedence
  Important described below.

This is E2 host proof, not Docker, hosted-Linux, deployment, or live proof. GitHub Actions
was not invoked or managed.

## Final-review Important and scope diff

Static proof:

- `src/adapters/rewrite_common.cpp:796-809` appends original-path pairs before staged-root
  pairs;
- `src/adapters/rewrite_common.cpp:391-399` applies JSON path replacements in pair order;
- raw verification needles already use longest-source-first ordering at
  `src/adapters/rewrite_common.cpp:104-124`, so JSON rewriting and verification do not share
  the same precedence rule.

Required correction from review: apply JSON path pairs longest-source-first and add
composed Claude and Codex descendant-staging tests. This is exact staged-path behavior, not
the separately assigned R-4.8 home-prefix carrier.

ROW_TRUTH_CHECK: required
SCOPE_DIFF:
- src/adapters/rewrite_common.cpp -> OUT
- tests/test_adapter_claude_install.cpp -> in
- tests/test_adapter_codex_install.cpp -> OUT
SCOPE_DIFF_RESULT: deviation-present
SCOPE_ROW_EVIDENCE:
- src/adapters/rewrite_common.cpp -> required central precedence fix; absent from the live dispatch SCOPE_DIFF at lines 12-16 and named OUT by the pre-edit fold-scope fence
- tests/test_adapter_claude_install.cpp -> present in the live dispatch SCOPE_DIFF at line 14
- tests/test_adapter_codex_install.cpp -> required Codex parity falsifier; absent from the live dispatch SCOPE_DIFF at lines 12-16 and named OUT by the pre-edit fold-scope fence

No deviation edit was made. A Claude-only workaround within the current token would leave
the shared Codex defect and violate the required parity proof, so it was not attempted.

## Boundary contract proof and preserved exclusions

The affected contract is stage to pack to install: both the original source path and the
authoritative intermediate `provenance.store_root` must rewrite to the final workspace, and
verification must refuse any surviving origin. The descendant-root ordering counterexample
shows this contract is not yet proven for all admitted path relationships.

Preserved out of scope: R-4.8 home-prefix carrier and falsifier; global agent-qualified
sidecar-ID uniqueness Minor; staged/host cross-source dedupe Minor; `manifest.*` and
`src/core/manifest/**`; `.github/**`; merge; release; deployment.

## Remaining risk and next requested action

Remaining risk: a descendant staging root can be transformed to a target-relative suffix
instead of the exact final workspace while verification reports no origin hits. The broad
review classifies this as Important correctness breakage.

Next requested action: grant or disposition a narrow final-review fix covering
`src/adapters/rewrite_common.cpp`, `tests/test_adapter_claude_install.cpp`, and
`tests/test_adapter_codex_install.cpp`. On a valid live token, run TDD, amend the single
commit, scoped re-review, full host suite, the standing Ubuntu 24.04 `linux/amd64` Docker
suite, and only then republish PR #23. The orchestrator's third targeted re-panel remains
downstream of the implementation report and republication.

ACTIONS_GIT_REF: local B2 candidate `s4-floor/b2-torn-tail@3f2dd3ead60f50a06d3951d69bf46b8afa2becf1`, parent `ec9a2db2cfe55191f99efbcf12902a79d99e159e`, one commit, preserved subject; draft PR #23 remains at remote `d6cceba9321d693d8e302e89b796ca159a0f8f66`; this report rides one explicit-path docs-lane commit after filing, while its INDEX row remains append-only in the concurrent shared-index worktree; no Docker, push, Actions management, merge, release, or deployment followed the changes-requested final review
FINAL_GIT_STATUS_SHORT: B2 implementation worktree tracked status is clean at `3f2dd3e`; before the explicit report commit, main docs lane contains this untracked report, the modified `.relays/s4/INDEX.md`, and pre-existing or concurrent untracked sibling R-4.8 relays not authored or modified by this seat

CARRY LIST:
- staged-path replacement precedence Important and three-path deviation request -> `s4-floor.planner`
- local amended candidate `3f2dd3e` -> HELD, host-green, final-review changes requested
- Ubuntu 24.04 amd64 Docker + PR #23 republication + third panel -> not yet eligible
- R-4.8 true-home carrier/falsifier -> separate, unchanged
- two broad-review Minors -> disclosed, unchanged
