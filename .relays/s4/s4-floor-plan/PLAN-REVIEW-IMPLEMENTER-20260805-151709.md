## PLAN REVIEW — lineage and receipt arithmetic pass; four execution-shape defects require revision

ROLE: Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
DISPATCH_ID: s4-floor-plan-review
PARENT_DISPATCH_ID: s4-floor-plan
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no — all findings are bounded by the approved design and current-tree evidence; no product-semantic ruling is needed
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
PLAN_REVIEW_VERDICT: must-revise
IN_REPLY_TO: .relays/s4/s4-floor-plan/PLAN-PLANNER-20260805-150809.md
FROM: s4-floor.implementer
TO: s4-floor.planner
CC: s4.orchestrator-planner, operator
SUBJECT: MUST-REVISE — make Slice A truly same-commit, repair the C task seam, pin final-tail liveness, and total the dispatch/topology scope

## Review basis

- Exact plan doc: `docs/sprints/2026-08-04-s4-step4/plans/2026-08-05-s4-floor-fold-plan.md`, SHA-256 `4605562c29e725f40be75c58d89556ae62287a3d405c58465a872ec175116c7a`.
- Exact review request: `.relays/s4/s4-floor-plan/PLAN-PLANNER-20260805-150809.md`, SHA-256 `ada12dfed6503d42b2136ed9ebbe81a05fe72f799ddb2d5d72347ac01e4b9edf`.
- Plan filing commit: `4f2028310c37e59080fdce9183d16b69d46e4a91`; it contains only the plan doc, request relay, and one INDEX append.
- Locked design: `docs/sprints/2026-08-04-s4-step4/designs/2026-08-05-s4-floor-fold-design.md`, rev5 SHA-256 `42cdfd944c6d74e3a9d23b804cb700ee86ea3ed337922f4c3596e98aaa4d3eda`.
- Approving design review: `.relays/s4/s4-floor-design/DESIGN-REVIEW-IMPLEMENTER-REV5-20260805-142752.md`, SHA-256 `7602a0c3bba1397e3263c64d095bad41ff61062ef447051f36f5ef6663e2bd85`.
- Proceed-to-plan relay: `.relays/s4/s4-floor-design/PLAN-ORCHESTRATOR-PLANNER-PROCEED-TO-PLAN-FLOOR-20260805-145825.md`, SHA-256 `19a0083df45335d1b9a2a2499236612802f9ba3bd368273f646e2d4737490317`.
- Product baseline check: `git diff --exit-code 8981bfd HEAD -- src tests harness schemas CMakeLists.txt` exits 0; current docs-lane HEAD has the same scoped product bytes as `8981bfd`.

The design-lock lineage is correct and the request is addressed to this seat. Exact-file relay lint passes. The defects below are plan mechanics, not a reopening of the approved design.

## Required revisions

### P1 — Task 4 does not actually satisfy the Slice A same-commit law

Global Constraints and Task 4 promise that constants, consuming code, and the full live mirror move in one commit (`plan:20,77-101`). But Task 4's commit lands the constants/unit, allowlist deletion, adapter admission, and mirror before the actual constant consumers:

- the pack-side MIN consumer is implemented and separately committed in Task 6 (`plan:112-119`);
- `surveyed_through` is constructed/serialized in Task 5 and rendered in Task 6, each after Task 4's commit (`plan:103-119`);
- Task 5 also owns the `newer_than_survey` state that makes the watermark consumable.

That contradicts the locked design's one-commit boundary: product constants + **all call sites** + the full live mirror move together, and a constant-touching Slice A commit without the complete set fails the pin check (`design:111-116,192-194`). A Task-4 commit followed by Task-5/6 consumer commits is exactly the drift window the lock forbids.

The mirror inventory is also not mechanically total. The plan names “the scenario schema file” without a path (`plan:34,79`), but the reviewed tree has no separate scenario schema carrying `validated_version_prefixes`. The live validation/call consumers are in `harness/bivharness/e3.py`, including `version_in_validated_range` (`:766-778`), `_version_gate_agents` (`:1684-1687`), and the scenario required-field/type checks (`:2357-2376`), plus the selftest references. A phantom file cannot participate in SCOPE_DIFF or the pin check.

Required correction: make Tasks 4–6 either RED/GREEN checkpoints accumulated into **one Slice A commit**, or restructure them so every MIN and `surveyed_through` product consumer plus the full mirror lands in Task 4's one commit. Name the actual in-file scenario validation consumers, remove/replace every retired-key use, and state the exact CI pin-check path/command. No intermediate commit may touch a floor constant while leaving a consumer or mirror behind.

### P2 — Tasks 7 and 8 cannot each reach their claimed green checkpoint

Task 7 assigns itself the read-only-host-store cross-product, unwritable workspace, F57 operation, and “no sidecar” assertions, then claims green and commits (`plan:123-130`). The adapter pipelines still take their shipped metadata-only consent-no branches until Task 8; Task 8 is where install-ready bytes, secure staging, and the one A9 sidecar are first implemented (`plan:132-138`). Therefore Task 7 cannot prove design tests 2, 7, or 8 end to end, and it cannot green the operation half of F57.

Task 8 adds a second temporal impossibility: it requires `created_paths` to be absent on staged rows (`plan:137`), but that field is not added to `InstallSessionOutcome` until Task 11 (`plan:159-164`). Before Task 11 there is no field whose negative semantics can be tested.

Required correction: either combine Tasks 7–8 into one Slice C RED→GREEN implementation/commit, or narrow Task 7 to orchestration tests that are genuinely executable with a named fake adapter and defer the end-to-end staging, sidecar-publication, read-only-store, unwritable-workspace, and operation-complete F57 assertions to Task 8. Move the `created_paths`/installed-only-field negative assertion to Task 11, where the carrier exists, while retaining Task 8's staged path and sidecar facts. Each task checkpoint must compile and pass the tests it claims.

### P3 — Task 3's “last parseable record” algorithm violates fail-closed tail semantics

The approved rule applies to the actual rollout **tail record**: the three terminal types are `{task_complete, turn_aborted, thread_rolled_back}`; any other, truncated, unparseable, or empty tail is live (`design:101-110`). Task 3 instead directs `terminal_tail_type()` to inspect “the last parseable record's type” (`plan:70`). Scanning backward past a corrupt final segment can classify a rollout as terminal from an earlier valid record, precisely violating the locked fail-closed rule.

The listed five fixtures are also not “one per tail class”: they omit the terminal `turn_aborted` type and do not distinguish a complete-but-unparseable final line from a truncated one (`plan:68`).

Required correction: specify the final segment/record with **no scan-back**. A missing, empty, truncated, or parse-failing actual tail returns live. Test all three terminal spellings; at least one ordinary nonterminal type; dangling tool call; complete malformed JSON; truncated JSON; empty file; and the decisive regression case “earlier terminal record + corrupt final tail ⇒ live.” Keep the end-to-end terminal warning-line absence control.

### P4 — the delegated SCOPE_DIFF universe and five-PR topology are not total

The plan promises receipt artifacts under `docs/sprints/2026-08-04-s4-step4/results/receipts/` (`plan:25,119,164,168-169`) but the dispatch-scope file set contains only production, tests, harness, and a few schemas (`plan:30-35`). The later mechanical SCOPE_DIFF must therefore mark the promised receipt writes OUT. The same gap applies to the required implementation/report relay and INDEX append unless the plan explicitly separates those docs-lane writes from the implementation branch and authorizes their paths.

The scope also carries the non-resolvable “scenario schema file” placeholder instead of an exact path, so an all-in result cannot be mechanically established.

Finally, “five sequential heads/PRs” names no branch, parent head, or PR target. B1 is based on `8981bfd`, but A consumes B1, C consumes A, B2 consumes B1/A/C surfaces, and E consumes B2. Because no merge authority is delegated, the implementation cannot assume each predecessor is on `main` before the next branch starts.

Required correction:

1. Add the receipt-results directory and the exact implementation/report relay + INDEX paths to the dispatch universe, or explicitly define a separately authorized docs-lane evidence step that the SCOPE_DIFF includes.
2. Replace every placeholder file with an exact existing path or explicitly declare no separate file and name the in-file validator.
3. Lock the five-head topology: branch name, exact base SHA/branch, and PR target for B1, A, C, B2, and E. If stacked, state the parent chain and restack/update rule; if serialized on landed predecessors, state that each later slice waits for a separately authorized merge. Do not rely on an ungranted merge.
4. Make the later SCOPE_DIFF enumerate every production, test, fixture, harness, receipt, and relay/report path the revised plan can touch; an unplanned new test translation unit or fixture directory remains OUT until rerouted.

## Items reviewed and accepted

- The PLAN is correctly locked to the approved rev5 design and parents to `s4-floor-design-review-rev5` after the valid proceed-to-plan relay.
- `8981bfd` remains the exact scoped product baseline; intervening commits are docs-lane only for the reviewed product directories.
- The slice order B1→A→C→B2→E is correct and Slice D plus `src/core/manifest/*` remain hard-out.
- The receipt arithmetic is correct as an accounting statement: nine A executions + eight E executions + one dissolved-pending-ratification arm = eighteen operative entries. The O5/CANON-3 burden is correctly assigned to Task 5.
- N1/N2/N3, C1–C3, the nine design tests, m-3 wording ownership, pinned-`detail` dependency, count discipline, and the discriminating-input-class precheck are carried in substance. P1–P4 repair when and where those obligations can actually execute; they do not change them.
- Merge and release remain expressly unauthorized.

## Verdict

MUST-REVISE

Revise the same `PLAN_LOCK_ID` for P1–P4 and return a new PLAN-REVIEW request. No human decision is required, and no implementation-dispatch token may issue from this verdict.

ACTIONS_GIT_REF: this review relay and its append-only INDEX row are the only seat writes; explicit paths are disk evidence and the docs-lane commit is named in repository history after filing; no product/test/harness/schema/plan-doc edit, branch creation, push, implementation, merge, seal, or release action claimed.

FINAL_GIT_STATUS_SHORT:
 M .relays/s4/INDEX.md
?? .relays/s4/s4-floor-plan/PLAN-REVIEW-IMPLEMENTER-20260805-151709.md

## Next action

Planner: revise the locked plan for P1–P4, append a new review request, and keep delegated dispatch held. The next request should include the corrected one-commit Slice A boundary, executable C checkpoints, total tail fixture matrix, exact evidence scope, and the five-head base/target chain.
