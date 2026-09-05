## PLAN-REVIEW artifact — MUST-REVISE revision 14 at 84061879: the green tidy coverage receipt is unreachable through non-verbose CTest, and the red-fold rule weakens the exact-hunk boundary to a path-only boundary

ROLE: Pair Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: must-revise
DISPATCH_ID: intg-substep2a-plan-review-14
PARENT_DISPATCH_ID: intg-substep2a-plan
IN_REPLY_TO: intg-substep2a/PLAN-pair-planner-20260903-223053.md
RELATED_CONTEXT: intg-substep2a/IMPL-pair-implementer-20260903-222330.md; intg-substep2a/IMPL-pair-planner-20260903-211946.md; intg-substep2a/PLAN-REVIEW-pair-implementer-20260903-210020.md; ../../../pdc/master/relays/intg-substep2a-format-act/DESIGN-planner-20260903-183510.md; ../../../pdc/master/relays/intg-substep2a-format-act/PLAN-master-planner-20260903-183926.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new operator gate — the PathMutation repair, held ondemand spelling, and keep-going direction are in-lane; this review requires only executable evidence plumbing, restoration of the exact-hunk STOP boundary, and one stale revision label. A successor exact-hash review and fresh addressed implementation token remain mandatory; m-1/m-3 byte review, merge, count-gate, push, PR, publication, deployment, and release retain their separate gates; the release hold is ABSOLUTE
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
PLAN_LOCK_ID: intg-substep2a-plan-20260830 @ sha256 840618791e2b4eef4bb3b8bd01048604a1b2e8ce059779bf22226f042f60876a
TARGET_RELAY_SHA256: 5a22060d9dc3402b3263291851cb5d22b839881334f3e37e33be261582245300
TARGET_PLAN_SHA256: 840618791e2b4eef4bb3b8bd01048604a1b2e8ce059779bf22226f042f60876a
TARGET_PLAN_COMMIT: 0078ac9a1275465aa9377acea1bc030f333859b6
BASE: main@46df8f3c35981a4ae3f77cf3293a4b7212b4b996; exact review filed from docs lane commit 0078ac9a
BRANCH: intg/format-act@b09e1922c16da50b5bef0644d9923a567b98c468 with exactly the two held unstaged manifest-path repairs; index empty; both retention tags present; no product/test byte or ref changed by this review
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: master.master-planner, master.master-reviewer, m-1.planner, m-1.implementer, m-3.planner, m-3.implementer
SUBJECT: MUST-REVISE exact 84061879 — add verbose CTest output for the mandatory green coverage line, make every non-authorized hunk a STOP even inside the three named paths, and replace the stale rev13-head label

## Verdict

MUST-REVISE at exact SHA-256 `840618791e2b4eef4bb3b8bd01048604a1b2e8ce059779bf22226f042f60876a`.

Revision 14 correctly identifies the pair-owned checkpoint mistake, carries the exact behavior-neutral `PathMutation::dot{}` NSDMI, accepts the compiling ondemand named-lookup spelling on evidence, and upgrades the Linux build to keep-going. Its intended green gate is not executable as written: ordinary CTest hides a passing test's stdout, while the plan requires a line from that hidden stdout and treats absence as red. A second wording conflict permits folds by path even though the plan otherwise permits only five exact repair sites. Both defects must be removed before a fresh implementation token.

This is review-only. It authorizes no product/test/plan edit, container execution against changed bytes, tag/ref movement, reset, staging, commit, byte-review request, merge, count-gate action, push, PR, remote CI, publication, deployment, seal, or release.

## Findings

### F1 — Major — the required successful tidy coverage line is suppressed by the commanded CTest mode

Plan line 274 commands `ctest --preset ci -R 'safety-tidy-analyzer'` and simultaneously requires its stdout to contain exactly one `clang-tidy coverage: <N> results == <N> sources` line, with absence defined as red. CTest's ordinary successful-test mode reports only start/result/summary; `-V` is the option that enables test stdout. `--output-on-failure` would not close this because the needed receipt is from a passing test.

The just-completed rev13 instrument is the direct counterexample. Its safety-tidy row passed 1/1 in 47.24 seconds with `tidy_rc=0`, while the retained combined log contains no `clang-tidy coverage:` line at all. The underlying `harness/ci/run_clang_tidy.py` does print that line before returning 0; CTest suppressed it. Thus revision 14's required success state cannot be observed through its own command and would force another STOP after otherwise-green work.

Required correction: run the exact tidy row in verbose mode, for example `ctest --preset ci -R '^safety-tidy-analyzer$' -V`, retain that stdout, require exactly one coverage line with equal numeric populations and N >= 1, reject `COVERAGE FAILURE:`, and require `tidy_rc == 0`. Carry the verbose form consistently in the revision headline/carrier, Step 4b, Task-4 T-3 evidence, and acceptance 12 wherever the observable receipt is promised.

### F2 — Major — the enumerated-red fold language turns exact-hunk authority into path-only authority

Step 0-quater line 257 remains exact: `tests/test_manifest.cpp` may change only `std::string dot;` to `std::string dot{};`, while Step 0-ter binds `manifest.hpp` to T-1 and every `manifest.cpp` hunk to the four named T-4 sites. But Step 4b line 274 says to fold every enumerated diagnostic within the three named files and STOP only when a fold needs a path outside those files. The PLAN carrier repeats the weaker rule at lines 42 and 46: “a fourth path = STOP.”

That wording can authorize a sixth hunk elsewhere in `manifest.cpp`, `manifest.hpp`, or `tests/test_manifest.cpp`, contradicting the exact-hunk and NOTHING-else terms. The keep-going census is an observation mechanism, not authority to repair every same-file diagnostic.

Required correction: state that only the already authorized T-1 hunk, four T-4 sites, and one `dot{}` hunk may exist. Any enumerated red whose correction needs any other byte is a STOP through the Planner, even if that byte is inside one of the three checkpoint files; a fourth path remains a STOP as a subset of that stronger rule. Re-run the whole gate only after an in-scope authorized fold.

### F3 — Minor but binding — Task-4 T-5 names the dead revision head

Plan line 302 requires the zero-caller and no-bump checks to be “re-run at the rev13 head.” Revision 14's eventual replacement candidate is the evidence target. Replace this with “candidate head” or the equivalent revision-14 replacement SHA wording so Task 4 cannot cite the retained pre-replacement state.

## Verified revision-14 folds

- The incoming PLAN relay is addressed to this seat, is plan-only, hashes to `5a22060d9dc3402b3263291851cb5d22b839881334f3e37e33be261582245300`, and passes exact-file relay lint.
- The plan at commit `0078ac9a1275465aa9377acea1bc030f333859b6` hashes to the declared `840618791e2b4eef4bb3b8bd01048604a1b2e8ce059779bf22226f042f60876a`. The rev13-to-rev14 delta is one plan file, 14 insertions / 11 deletions, with `git diff --check` clean.
- The W-5 replacement archive hashes to `62b995b4266ddad0ab310ac78e2f102e998a6159097dab61a67bb2aa6e52b72c` and records exactly the disclosed O design-lineage red on the revision-14 carrier; no new lock or selector is introduced.
- The held product state matches Step 0-quater: HEAD `b09e192`, parent `363d812`, both retention tags correct, index empty, exactly `manifest.cpp` and `manifest.hpp` modified, and their hashes are `f7a89c8c...` / `fd12d52b...` as declared.
- The proposed `std::string dot{};` is confined to a test-local aggregate and is behavior-neutral relative to the omitted member's empty `std::string`; the consumer already branches on `dot.empty()`. The +1/-1 and no-per-aggregate bounds are coherent.
- simdjson 3.10.1 confirms the ondemand reading: public ondemand document/object APIs expose `find_field_unordered`; ondemand object `operator[]` delegates to it, while the cited public `at_key` idiom is DOM. The held checked lookup preserves the previous thrown simdjson error path and remains subject to Step 6 and m-1 V-FA review.
- `CMakePresets.json` names no generator for `ci`, so the Ubuntu configure's observed Unix Makefiles generator accepts the planned `-k` native option. The one-integer concatenated-log count corrects the rev13 filename-qualified-count defect, subject to ordinary shell handling of grep's zero-match status.
- Step 5's three-path comparisons and explicit six-path staging are coherent; both superseded commits remain retained, and no downstream gate is opened by this review.

## Escalation scan

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: no — review-only
- migration/backfill/destructive-write/canonical-data-repair: no
- money/inventory/orders/planning/accounting/trust-critical-state: no
- AI-or-automation-acts-downstream: no — no token may issue from this verdict
- worker/scheduler/queue/retry/async-side-effect: no
- cross-repo/service-contract/generated-schema/shared-API-event: yes — locked PDC O/N/M and W-5 govern the eventual candidate
- user-visible-control-with-materializer/downstream-consumer: yes — the held writer/parser implementation controls archive bytes
- test-runtime-role-mismatch: yes — the mandatory green coverage receipt is hidden by the selected CTest mode
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: yes — same-file fold language is broader than the exact five-site repair authority
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: none — no downgrade or risk acceptance requested
- valid_waiver: no
WAIVED_RISK_ACCEPTANCE: none

## Required successor

Revise the same plan identity to make the tidy coverage receipt observable with verbose CTest, restore the STOP rule at the byte/hunk boundary rather than only the path boundary, and replace the stale rev13-head label. Reissue at a new exact hash and request PLAN-REVIEW. No `intg-substep2a-impl-5` token may issue from this must-revise verdict.

ACTIONS_GIT_REF: read-only review of plan commit 0078ac9a/84061879, incoming carrier 223053, W-5 replacement archive, frozen b09e192 held bytes, simdjson 3.10.1 headers, CMake/CTest surface, retained rev13 Linux log, staged-tree mechanics, and current scoped statuses; daemon submission only; no product, test, plan, branch, tag, ref, reset, staging, commit, merge, push, PR, remote CI, publication, deployment, seal, or release action claimed
RELAY_LINT: to be engine-rendered; exact-file lint and root verification follow submission
FINAL_GIT_STATUS_SHORT: shared docs tree contains inherited untracked intg relay artifacts, including the prior STOP and exact-hash review; all preserved. Isolated product worktree remains at b09e192 with exactly the two held unstaged manifest modifications and no index entry. This review adds only its engine-rendered relay and engine-owned intg projections.
