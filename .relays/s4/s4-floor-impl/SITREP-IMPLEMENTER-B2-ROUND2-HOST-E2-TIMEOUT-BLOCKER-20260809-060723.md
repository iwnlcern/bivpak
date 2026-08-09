## SITREP — B2 fix round 2 code-approved but host gate blocked: every E2 scenario passes semantically, while the unchanged canonical 180-second row repeatedly times out at 180.05-180.06 seconds; no amend or publication

ROLE: Implementer
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-floor-impl-2-b2-resume-host-timeout-blocker
PARENT_DISPATCH_ID: s4-floor-impl-2-b2-resume-fold
RUN_ID: s4
TASK_ID: B2
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — disposition the repeated fixed-budget host timeout before the approved round-2 fix may be amended, Docker-verified, or published; no timeout relaxation or failed-gate acceptance is inferred
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/IMPL-PLANNER-B2-RESUME-UNION-SCOPE-DISPATCH-IMPL-TOKEN-20260809-025646.md
FROM: s4-floor.implementer
TO: s4-floor.planner
CC: s4.orchestrator-planner, operator
SUBJECT: BLOCKED — B2 round-2 fix independently approved, but canonical host harness-e2 repeatedly times out at its unchanged 180-second budget; branch remains unamended and unpublished

BLOCKED / HUMAN DISPOSITION REQUIRED

## Implementation and review state

The operative B2 resume completed the exact image-ID union, removed the dishonest
workspace-derived home-prefix surrogate assigned to R-4.8, and folded two additional
whole-branch review blockers:

- staged stage→pack→install records now rewrite and verify both the original source path
  and authoritative intermediate `provenance.store_root` path;
- Claude staged re-pack preserves child ownership and maps both original and staged child
  aliases to one fresh install identity.

Fix round 1 was amended at local head
`9977a15f7d9957acb8d643a7919b24196293b0a9`, exactly one commit over
`ec9a2db2cfe55191f99efbcf12902a79d99e159e`, with subject
`feat(pack): collect torn tails and staged sidecars` preserved. Its composed tests, focused
cohort, 14/14 host suite, and Claude A3 11-control ceremony passed.

Round-1 re-review found one new Important: readable staged Claude child aliases owned only
by a pre-refused row were not entering the frozen image-wide union. Round 2 corrected that
with a scan-only refused-row prepass and a cross-row falsifier. The same independent
reviewer returned **ADDRESSED**, with no new Critical or Important breakage.

Round-2 TDD and focused evidence are green:

- new cross-row falsifier RED: exit 42, 7 of 11 assertions failed for the expected missing
  alias-union behavior;
- GREEN: 11/11 assertions;
- refused-row/message/child union cohort: 192 assertions across 6 cases passed;
- full rebuild passed;
- `git diff --check` passed;
- exact uncommitted delta: `src/adapters/claude_code/install.cpp` and
  `tests/test_adapter_claude_install.cpp` only.

## Canonical host gate blocker

The product and non-E2 host rows pass. The unchanged CTest `harness-e2` row has a fixed
180-second timeout and repeatedly exits red at the boundary:

- worktree full suite: `biv_tests` passed in 318.96s; `harness-e2` timed out at 180.06s;
  aggregate CTest exit 8;
- two exact isolated worktree E2 retries: timed out at the same boundary;
- fresh short-path build created with `mktemp -d /tmp/bivpak-b2-r2-host.XXXXXX`, configured
  from the current source, and fully rebuilt both `biv` and `biv_tests` successfully;
- fresh `/tmp` full suite: `biv_tests` passed in 325.71s, `harness-selftest` passed in
  5.16s, `harness-e2` timed out at 180.05s; 1 of 14 selected rows failed, three configured
  safety rows skipped, aggregate CTest exit 8;
- final one-shot exact E2 replay from that fresh build after the code re-review cooling
  interval: timed out at 180.06s, CTest exit 8.

An instrumented run of the exact scenario runner completed every row:

- 11 runnable E2 scenarios: PASS;
- 6 configured rows: expected `XFAIL_PENDING`;
- no failed or invalid scenario;
- total 181.312s, which is 1.312s over the canonical fixed budget.

This is strong E2 semantic evidence but it is not a green canonical CTest row. The timeout
was not changed, waived, or relabeled. No Docker run followed because the candidate remains
unamended and the host gate is red. GitHub Actions remained unused.

## Requested disposition

Choose one explicitly:

1. grant a narrow evidence exception for this implementation amend, accepting the repeated
   fixed-budget timeout alongside the all-scenarios-pass diagnostic; then resume with the
   final focused check, one-commit amend, local Ubuntu 24.04 `linux/amd64` Docker parity,
   PR #23 republication, and the third panel; or
2. provide a different canonical host/runtime or an explicitly authorized verification
   budget disposition. Any test-timeout source change or workflow edit requires separately
   named scope; none is inferred here.

Do not treat this report as permission to amend, publish, run remote CI, merge, or release.
R-4.8 and the two disclosed broad-review Minors remain separately carried.

ACTIONS_GIT_REF: B2 implementation worktree HEAD remains `s4-floor/b2-torn-tail@9977a15f7d9957acb8d643a7919b24196293b0a9`, parent `ec9a2db2cfe55191f99efbcf12902a79d99e159e`, one commit, preserved subject; round-2 approved fix remains unstaged and uncommitted in exactly `src/adapters/claude_code/install.cpp` and `tests/test_adapter_claude_install.cpp`; origin branch and draft PR #23 remain at prior `d6cceba9321d693d8e302e89b796ca159a0f8f66`; this report and INDEX append are docs-lane-only; no push, Actions, Docker, merge, or release
FINAL_GIT_STATUS_SHORT: B2 worktree has exactly two tracked unstaged files (`src/adapters/claude_code/install.cpp`, `tests/test_adapter_claude_install.cpp`) at unchanged HEAD `9977a15`; main docs lane also contains four pre-existing untracked sibling R-4.8 relays not authored or modified by this seat

CARRY LIST:
- host-timeout disposition → `s4-floor.planner` + `s4.orchestrator-planner` + operator
- independently approved round-2 two-file delta → HELD unstaged/uncommitted at B2 worktree
- local Ubuntu 24.04 amd64 Docker + PR #23 republication + third panel → not yet eligible
- R-4.8 true home carrier/falsifier → remains separate and hard-gated before release
- broad-review Minors (agent-qualified sidecar uniqueness; staged/host cross-source dedupe) → disclosed, unchanged
