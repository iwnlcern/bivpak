## PLAN-REVIEW artifact — MUST-REVISE exact revision 4 at e0d5585b: the writer domain is still wider than the shared inventory; C-4's destination claim is false; C-2/C-3 and the status proof contradict their own commands

ROLE: Pair Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: must-revise
DISPATCH_ID: intg-substep2a-plan-review-4
PARENT_DISPATCH_ID: intg-substep2a-plan
IN_REPLY_TO: intg-substep2a/PLAN-pair-planner-20260902-023115.md
RELATED_CONTEXT: docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep2a-20260830.md; intg-substep2a/PLAN-REVIEW-pair-implementer-20260901-233102.md; intg-substep2a/IMPL-pair-implementer-20260901-063948.md; sealed Addendum O at locked commit 40b4f7a3dbfc60e5ab742678bc4e77198845c243; m-1 ASK-6 ruling 231935; master carry 232655
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no NEW human gate — F3 is a contradiction in the fence owner's C-4 condition and must route UP for owner clarification/correction; the standing operator W-5 disposition and the remaining exact-hash plan corrections/re-review still follow; implementation, byte reviews, merge, push, publication, deployment, and release remain separately gated
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
PLAN_LOCK_ID: intg-substep2a-plan-20260830 @ sha256 e0d5585b77b52e464be97e4e03685c0509ee170660bdfccc3a7f6ee12f42baa4
REVIEWED_PLAN: docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep2a-20260830.md at commit 430ece9a606f22512fe0ffa6ea06860d8fddf264, sha256 e0d5585b77b52e464be97e4e03685c0509ee170660bdfccc3a7f6ee12f42baa4
BASE: main@46df8f3c35981a4ae3f77cf3293a4b7212b4b996; review filed from main@430ece9a606f22512fe0ffa6ea06860d8fddf264
BRANCH: intg/format-act at retained HEAD 9e6ebe8fca2454164051573323dd7adfa2901219; index clean; uncommitted tranche-1 diff remains exactly 72fd3dc604957e14e944b9f7418a64f723125d8b138909e8e0bd5b045e4b22cf over src/core/manifest/manifest.cpp and tests/test_manifest.cpp; no product byte or ref changed by this review
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: master.master-planner, master.master-reviewer, m-1.planner, m-1.implementer, m-3.planner, m-3.implementer
SUBJECT: MUST-REVISE exact e0d5585b — F1 expand the one validator to every typed-expressible parser invariant and make repo path validation actually pass through it; F2 restore ASK-6 C-2's literal no-brace shape and correct C-3's pack numstat; F3 route C-4 UP because cleanup_error cannot prove no destination archive exists; F4 correct the impossible ignored-only status postcondition; prior staging, presence-fact, and tag findings otherwise folded

## Verdict

MUST-REVISE at exact SHA-256 `e0d5585b77b52e464be97e4e03685c0509ee170660bdfccc3a7f6ee12f42baa4`.

Revision 4 folds the three findings from `233102`, but four blockers remain. F1 permits writer-emitted typed states the parser rejects and cannot realize the claimed post-build path enforcement. F2 does not adopt ASK-6 C-2 verbatim and gives an impossible pack numstat. F3 requires a false C-4 evidence statement and therefore must route to the fence owner. F4 binds `git status --short` to output that command cannot produce. No implementation token may parent to this review.

This is review-only. It authorizes no product edit, plan edit, branch/ref movement, implementation, merge, push, publication, deployment, or release.

## Findings

### F1 — Critical — `RepoRowFacts` still does not span O-R1's validated domain or O-R4's parser language

Plan lines 100-116 enumerate O-R2/O-R3/G/H/N/COND-3, then classify `non-40-hex sha` with wrong JSON types and bad enum text as a parser-only SHAPE error because “the typed carrier cannot express” it. That statement is false. At retained `9e6ebe8`, `RepoEntry::sha` is `std::optional<std::string>` (`types.hpp:204`), while `parse_repo_entry` rejects a present non-40-hex value (`manifest.cpp:1532-1535`). The planned writer facts and inventory do not check its syntax. A born row with `sha = "x"` therefore reaches the planned writer, emits, and is rejected by `parse`: a direct counterexample to locked O-R1's validation of every typed entry against section 2.3 and O-R4's equality between the O-R1-accepted projection and the parser acceptance language.

The same class is wider than the minimal witness: the typed carrier can express invalid `eligibility.method`, proof `tip_sha`, local-ref `sha` and proof-presence relation, shallow boundary values, and structured-note constraints that the retained parser rejects. Wrong JSON type and invalid enum discriminants genuinely are parser-only because no typed value represents them; string/content invariants are not.

A second execution gap exists inside the same claim. The retained repo path helpers call `valid_manifest_path` and return before `RepoEntry` construction (`manifest.cpp:1077-1111`, consumed by the repo parser from `:1260` onward). Under the prescribed “post-build” shared call, an invalid O-R2 path never reaches `repo_row_violation`, contradicting lines 100 and 155 and acceptance criterion 4, which call it the ONLY validator with every field reached from both call lines.

Required correction: census the parser's repo-row acceptance predicates against the fields the typed carrier can express; put every such invariant in the one writer/parser inventory, with typed writer-refusal witnesses sufficient to kill an omitted writer clause. Keep only genuinely unrepresentable JSON syntax/type/discriminant errors parser-local. For O-R2, prescribe how repo path parsing obtains a typed row without independently enforcing the semantic predicate before the shared call, or revise the architecture through the design owner; do not claim a post-build ONLY validator while the helper rejects first. If section 2.3 does not determine the boundary of this census, STOP UP rather than selecting it in-lane.

### F2 — Important — C-2's exact shape and C-3's pack proof are internally inconsistent

The fence owner's `231935` C-2 bytes are literal: `if (!manifest_json) return cleanup_error(manifest_json.error());` with no braces. Plan lines 35 and 133 instead prescribe `if (!manifest_json) { return cleanup_error(...); }`. A conventional multi-line braced implementation adds a structural-only `}` which makes line 150's own changed-line grep return nonzero; even a one-line braced form is not the owner's exact shape.

The expected pack numstat is also wrong. Against `9e6ebe8`, the literal owner shape changes the declaration (`+1/-1`), inserts the one-line refusal (`+1/-0`), and dereferences at the existing use (`+1/-1`): exactly `+3/-2`, not approximately `+4/-1`. The two test-TU expectations `+3/-1` are consistent.

Required correction: carry C-2's literal no-brace pack form, keep the C-3 grep mechanically satisfiable, and bind the pack numstat to `+3/-2`. If formatting policy prevents the owner-prescribed one-line form, route that conflict UP; do not silently change the ruled shape.

### F3 — Critical — C-4's unconditional destination statement is false at the ruled bytes

Plan line 151 requires the IMPL report to state that `cleanup_error` removes `partial_path` and `spool_path`, therefore “no `.bvpk` exists at the destination.” The premise does not imply the conclusion. At retained `9e6ebe8`, `image_path`, `partial_path`, and `spool_path` are distinct (`pack.cpp:548-551`); `cleanup_error` removes only the latter two (`:569-573`); `image_path` is touched only by the later rename (`:801`). There is no precondition or guard that the destination archive is absent. If an earlier `<name>.bvpk` already exists, an O-R1 refusal leaves it there.

The code does prove a narrower and useful statement: serialization refuses before the partial archive is opened, cleanup removes the spool, and no NEW destination image is emitted. It does not prove literal destination nonexistence. Because “no `.bvpk` at the destination” is m-1's C-4 fence term, not plan-local wording, this seat cannot correct it in-lane.

Required correction: route the counterexample UP to the fence owner for an exact C-4 clarification/correction (for example, “no new/replacement `.bvpk` is emitted; a pre-existing destination is unchanged”) or an explicitly bound absence precondition. Do not file evidence that states the current unconditional claim as fact.

### F4 — Important — the Task-3 clean-status postcondition expects ignored output from a command that suppresses it

Plan line 140 says `git status --short` equals “only the ignored `.superpowers/`.” Default `git status --short` does not report ignored paths. At the retained worktree it reports only the two tracked tranche files; `git status --short --ignored` is the command that reports `!! .superpowers/`, and it also reports other ignored build/cache paths. After the replacement commit, the intended default clean proof is an EMPTY `git status --short`, not an ignored-only row.

Required correction: bind `git status --short` to empty for tracked/untracked cleanliness. If ignored evidence is desired, make it a separate classified census without claiming `.superpowers/` is the only ignored path.

## Verified folds and unaffected surfaces

- Incoming carrier hashes to `f2fcd2a0...`; the plan hashes to `e0d5585b...` at `430ece9...`.
- Prior F1 is substantively folded: the six-path explicit `git add`, empty-unstaged proof, exact cached-path proof, and cached-tree tranche discriminators prevent the soft-reset loss. F4 above is a narrower postcondition correction.
- Prior F2's three missing wire facts are now representable in `RepoRowFacts`; the new F1 concerns the still-uncensused typed domain and the pre-build O-R2 helper path.
- Prior F3 is folded: six `FX-O-LEG`, seven `FX-O-FIELD`, eight test `O-MUTANT` markers plus one census marker, and the nine existing FX-N `NAMED MUTANT` markers are non-colliding.
- C-1's corrected `:docs/` confinement grep was executed at `9e6ebe8` and returns exactly the three ruled callers. C-5 through C-7 are carried without a finding here.
- Sealed O re-verifies: live post-stamp `0e990bac...`; blob at `40b4f7a3...` = locked `63c46631...`.
- Retained tranche 1 is unchanged: HEAD `9e6ebe8...`, index empty, exactly two tracked modified files, diff `72fd3dc6...`.

## Escalation scan

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: no — review-only
- migration/backfill/destructive-write/canonical-data-repair: no — no product or canonical-data write
- money/inventory/orders/planning/accounting/trust-critical-state: no — no such runtime state
- AI-or-automation-acts-downstream: no — no downstream automation act
- worker/scheduler/queue/retry/async-side-effect: no — no runtime action
- cross-repo/service-contract/generated-schema/shared-API-event: yes — sealed PDC O and m-1's ASK-6 fence govern this plan
- user-visible-control-with-materializer/downstream-consumer: yes — future archive bytes and pack refusal semantics are user-visible
- test-runtime-role-mismatch: yes — Task 4 two-platform verification remains closed
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: yes — F1's schema-domain boundary and F3's ruled C-4 contradiction block execution
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: none — no downgrade or risk acceptance requested
- scan_presented_to_operator: no — not requested
- operator_reply_after_scan: none
- valid_waiver: no
WAIVED_RISK_ACCEPTANCE: none

## Required successor

Route F3 UP through master to m-1; reissue the same plan identity only after the ruled C-4 text is truthfully executable, with F1/F2/F4 corrected and all standing W-5, review, merge, push, and release gates preserved. Request a new exact-hash PLAN-REVIEW. No implementation token may issue from this must-revise review.

ACTIONS_GIT_REF: read-only review of plan commit 430ece9a606f22512fe0ffa6ea06860d8fddf264 at sha256 e0d5585b77b52e464be97e4e03685c0509ee170660bdfccc3a7f6ee12f42baa4; sealed O, m-1 ruling 231935, master carry 232655, retained code/object bytes, incoming carrier, C-1 caller census, C-2/C-3 arithmetic, C-4 cleanup paths, and current index/worktree state checked; daemon submission only; no product, plan, branch, worktree, ref, merge, push, publication, deployment, or release action claimed
RELAY_LINT: exact-file v2.9.2 lint is the daemon submission gate; rendered result and digest will be re-verified after filing; inherited root-mode reds remain separately registered and are not changed by this review
FINAL_GIT_STATUS_SHORT: none — scoped status for the intg root and plan path was empty before daemon submission; inherited s4 state exists outside this review scope and was untouched
