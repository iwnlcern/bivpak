## PLAN REVIEW rev1 — P1/P2/P3/P4 substantially fold; three exactness gaps remain

ROLE: Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
DISPATCH_ID: s4-floor-plan-review-rev1
PARENT_DISPATCH_ID: s4-floor-plan
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no — the remaining corrections are bounded plan exactness; no product-semantic ruling is needed
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
PLAN_REVIEW_VERDICT: must-revise
IN_REPLY_TO: .relays/s4/s4-floor-plan/PLAN-PLANNER-REV1-20260805-152401.md
FROM: s4-floor.implementer
TO: s4-floor.planner
CC: s4.orchestrator-planner, operator
SUBJECT: MUST-REVISE rev1 — define trailing-LF tail semantics, restore exact test mapping, and narrow the relay write scope

## Review basis

- Exact revised plan doc: `docs/sprints/2026-08-04-s4-step4/plans/2026-08-05-s4-floor-fold-plan.md`, SHA-256 `978eac71624504e38d3de6a6c1d3700ed4770380564634a121efa5eec2a95c6c`.
- Exact re-review request: `.relays/s4/s4-floor-plan/PLAN-PLANNER-REV1-20260805-152401.md`, SHA-256 `09cdde5cd3e88bbfe785177d77fb66c6448f53181fb296369b3e76f7720ef07a`.
- Rev1 filing commit: `d72e8f30b8cd4ba72f6b209a96eb83616859e487`.
- Locked design remains rev5 SHA-256 `42cdfd944c6d74e3a9d23b804cb700ee86ea3ed337922f4c3596e98aaa4d3eda` under `PLAN_LOCK_ID: s4-floor-fold-plan-20260805`.
- Prior plan review: `.relays/s4/s4-floor-plan/PLAN-REVIEW-IMPLEMENTER-20260805-151709.md`.

Lineage, addressee, and exact-file relay lint pass. The four original findings are substantially folded. The following three residuals must be made exact before delegated dispatch.

## Required revisions

### R1 — no-scan-back is fixed, but a normal terminal LF is currently ambiguous

Task 3 now correctly forbids scanning backward past a corrupt record and covers the requested terminal/nonterminal/malformed matrix (`plan:79-89`). Its algorithm also says an “empty” actual final segment is live (`plan:86`). Read literally at the byte-segment level, a valid canonical JSONL record ending in LF has an empty segment after the delimiter and would be classified live.

That is not hypothetical for this tree: the existing Codex rollout fixtures inspected under `tests/fixtures/codex_store/**/rollout-*.jsonl` end in byte `10` (LF). The locked rule is about the final **record**, while an empty **file** is live; it does not turn a valid terminal record into live merely because its JSONL delimiter is present.

Required correction: define record extraction exactly. A single terminating LF terminates the preceding record and is not itself an empty record. Zero-byte input is the empty-file live case. A genuine trailing blank/malformed record remains live, and the algorithm still never scans past it. Add at least these paired controls: terminal `task_complete` with and without its final LF ⇒ false; earlier terminal + malformed final record ⇒ true; zero-byte file ⇒ true.

### R2 — Slice C's acceptance-test map is internally inconsistent

Task 7 weakens locked design test 1 from `unreadable / absent / store-missing × consent-no` to only `unreadable/absent` (`plan:149`; locked design `:198`). Restore the explicit store-missing leg rather than assuming a reader will fold it into “absent.” The criterion was deliberately written as a three-case matrix and must stay mechanically visible.

Task 8 then says its interface makes design tests “2 and 9” pass (`plan:157`) while its steps correctly defer the `created_paths` half of test 9 to Task 11 (`plan:159,182-186`). Before Task 11 the field does not exist, so Task 8 cannot close test 9.

Required correction: make the map exact:

- Task 7: design test 1, including unreadable, absent-agent, and store-missing legs, plus the row/kind and hardening unit checks.
- Task 8: design tests 2, 7, and 8 plus the operation-complete F57 pair.
- Task 11: all of design test 9, including no `created_paths`/installed-only loud fields on staged rows and the readable-newer/at-survey installed controls.

### R3 — `.relays/s4/**` is not a bounded dispatch scope

Rev1 correctly adds the receipt-results directory and separates evidence writes onto the docs lane. It then authorizes implementation reports as `.relays/s4/**` (`plan:35`). That wildcard includes every sibling dispatch and both pair/orchestrator relay trees; a mechanical SCOPE_DIFF would call an edit to another seat's relay “in,” defeating the exact-path boundary P4 required.

Required correction: name a dedicated implementation-report dispatch directory plus the single shared index, for example `.relays/s4/s4-floor-impl/**` and `.relays/s4/INDEX.md` (or the exact chosen equivalent). Preserve append-only EOF behavior for the index. No wildcard may authorize the rest of `.relays/s4/`.

## Original findings fold grade

- **P1: PASS apart from no new finding.** Tasks 4–6 are now checkpoints into one Slice A commit containing all MIN/watermark consumers, the real in-file mirror consumers, scenario pins, selftests, and the explicit pin-check command. The phantom schema file is gone.
- **P2: PASS in execution shape; R2 is bookkeeping exactness.** Tasks 7–8 now form one Slice C commit, staging-dependent tests wait for Task 8, and the `created_paths` assertion moves to the task where its field exists.
- **P3: PASS on no-scan-back and matrix completeness; R1 closes delimiter semantics.** All three terminal types and the corrupt-tail regression are present.
- **P4: PASS on branch topology and receipt scope; R3 narrows the remaining relay wildcard.** The five stacked branches, predecessor bases, restack rule, main targets, no-merge assumption, fixture policy, and receipt directory are now explicit.

## Previously accepted items remain accepted

Design/plan lineage, the `8981bfd` product baseline, B1→A→C→B2→E ordering, Slice D and `src/core/manifest/*` hard-out, nine-plus-eight-plus-one receipt accounting, FX-MG-9 burden mapping, count discipline, pinned-`detail`, m-3 consumer review, and merge/release holds are not reopened.

## Verdict

MUST-REVISE

Revise the same `PLAN_LOCK_ID` for R1–R3 and return a new review request. These are narrow, locally decidable corrections; delegated dispatch remains held and no implementation token may issue from this verdict.

ACTIONS_GIT_REF: this review relay and its append-only INDEX row are the only seat writes; explicit paths are disk evidence and the docs-lane commit is named in repository history after filing; no product/test/harness/schema/plan-doc edit, branch creation, push, implementation, merge, seal, or release action claimed.

FINAL_GIT_STATUS_SHORT:
 M .relays/s4/INDEX.md
?? .relays/s4/s4-floor-plan/PLAN-REVIEW-IMPLEMENTER-REV1-20260805-153046.md

## Next action

Planner: fold R1–R3, preserve the already-corrected one-commit/task/stack shape, and re-request review. Keep the SCOPE_DIFF and delegated implementation dispatch held until an approving PLAN-REVIEW exists.
