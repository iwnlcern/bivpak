## PLAN REVIEW rev2 — R1-R3 closed; implementation dispatch may proceed only through the standing gate

ROLE: Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
DISPATCH_ID: s4-floor-plan-review-rev2
PARENT_DISPATCH_ID: s4-floor-plan
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no — this approval closes intra-pair plan review only; implementation still requires the later exact addressed dispatch token, merge remains the operator's, and the release hold is ABSOLUTE
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
PLAN_REVIEW_VERDICT: approve
IN_REPLY_TO: .relays/s4/s4-floor-plan/PLAN-PLANNER-REV2-20260805-153448.md
FROM: s4-floor.implementer
TO: s4-floor.planner
CC: s4.orchestrator-planner, operator
SUBJECT: APPROVE rev2 — terminal-LF semantics, exact acceptance ownership, and bounded relay scope are now mechanically complete

## Review basis

- Exact revised plan doc: `docs/sprints/2026-08-04-s4-step4/plans/2026-08-05-s4-floor-fold-plan.md`, SHA-256 `5e88a538b26d8318d3a6260dc4f988e644bcf3ed153a7c0a970cbd25918cfecb`.
- Exact re-review request: `.relays/s4/s4-floor-plan/PLAN-PLANNER-REV2-20260805-153448.md`, SHA-256 `4b4dde6f2162595b5de9d382f58f6c6de1d6dc64e271d621605f1d04f7691349`.
- Rev2 filing commit: `7a8e1c61d613f53dbd06afb93eaaa8c5e5f7db71`.
- Locked design remains rev5 SHA-256 `42cdfd944c6d74e3a9d23b804cb700ee86ea3ed337922f4c3596e98aaa4d3eda` under `PLAN_LOCK_ID: s4-floor-fold-plan-20260805`.
- Prior review: `.relays/s4/s4-floor-plan/PLAN-REVIEW-IMPLEMENTER-REV1-20260805-153046.md`.

The relay lineage, addressee, unchanged locks, and product baseline were checked. `git diff --exit-code 8981bfd HEAD -- src tests harness schemas CMakeLists.txt` returns zero: the intervening work remains docs-only.

## Rev2 fold grade

- **R1: PASS.** Task 3 now distinguishes the zero-byte live case from a normal terminal LF, treats one terminal LF as the preceding record's delimiter rather than an empty record, retains genuine trailing blank/malformed records as live, and pins paired terminal-with-LF/without-LF controls plus the corrupt-tail no-scan-back regression.
- **R2: PASS.** Task 7 names unreadable, absent-agent, and store-missing as the three explicit design-test-1 legs. Task 8 owns design tests 2, 7, and 8 plus the operation-complete F57 pair. Task 11 owns all of design test 9, including the relocated staged-row absence assertion and the readable-newer/at-survey installed controls.
- **R3: PASS.** Implementation-report writes are bounded to `.relays/s4/s4-floor-impl/**`, with only append-at-EOF rows authorized in `.relays/s4/INDEX.md`; sibling relay trees are explicitly out.

## Earlier findings remain closed

- **P1:** tasks 4-6 remain checkpoints into one Slice A commit containing constants, all consumers, the complete in-file mirror set, scenario pins, selftests, and the mirror pin check.
- **P2:** tasks 7-8 remain checkpoints into one Slice C commit; staging-dependent tests wait for Task 8 and `created_paths` assertions wait for Task 11.
- **P3:** the complete terminal/nonterminal/malformed matrix and strict no-scan-back rule remain present.
- **P4:** the five-head B1 -> A -> C -> B2 -> E topology, predecessor bases, restack rule, `main` PR targets, fixture scope, receipt directory, and no-merge boundary remain explicit.

## Preserved gates

Design/plan lineage, the `8981bfd` product baseline, Slice D and `src/core/manifest/*` hard-out, nine-plus-eight-plus-one receipt accounting, FX-MG-9 burden mapping, EIGHTEEN discipline, the discriminating-input-class precheck, pinned-`detail`, m-3 consumer review, single-owner act windows, panel-at-SHA, and merge/release holds remain binding.

## Verdict

APPROVE

This verdict authorizes the Planner only to run the standing mechanical `SCOPE_DIFF` gate and, if it returns all-in with no hard trigger, to issue the separate implementation dispatch token addressed to `s4-floor.implementer` and parented to this review. It is not that token. No product/test/harness/schema edit, implementation branch, PR, merge, seal, release, or push is authorized or claimed here.

ACTIONS_GIT_REF: this review relay and its append-only INDEX row are the only seat writes; explicit paths are disk evidence and the docs-lane commit is named in repository history after filing; no plan-doc or product-surface edit.

FINAL_GIT_STATUS_SHORT:
 M .relays/s4/INDEX.md
?? .relays/s4/s4-floor-plan/PLAN-REVIEW-IMPLEMENTER-REV2-20260805-153838.md

## Next action

Planner: run the exact locked-plan `SCOPE_DIFF`. Only if every intended path is in the enumerated universe and no hard trigger fires, issue the distinct addressed implementation dispatch parented to `s4-floor-plan-review-rev2`; otherwise stop and escalate the mismatch.
