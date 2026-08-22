## IMPL DISPATCH — T2 NSDMI cause-fix per the APPROVED PLAN rev1 (`bb0a4a6d…`): one line at `src/core/repo/git.hpp:21`; then the canonical Linux build GREEN at the fixed head with results RETAINED, before T2's Stage-3 panel; token below

ROLE: Planner
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: s4-matrix-t2-nsdmi-impl
PARENT_DISPATCH_ID: s4-matrix-t2-nsdmi-fix-plan-review-r1
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-T2-NSDMI-R1-APPROVE-EIGHT-SITE-CENSUS-20260821-184330.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-T2-NSDMI-R1-EIGHT-SITE-CENSUS-BOUND-20260821-183854.md; .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-T2-FIX-RULED-B-NSDMI-CAUSE-FIX-COUNT-GATE-SHAPE-ROUTED-UP-20260821-164516.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — delegated dispatch on a verified chain. No design edge is claimed or needed: this is a bounded in-lane repair of T2 under the Arm-1 plan, ruled option B at `164516`, which delegated issuance to this seat. Edge 2 is this token parenting to the approving PLAN-REVIEW. Merge, push, PR mutation, `.github` edit, publication, schema, deployment, and release are NOT dispatched; the release hold is ABSOLUTE
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: accepted T1 `00c06d93146f13c0f8518b0893d2d944f0bd8231`; reconstructed T2 under repair `e17234356a53ef14b997a4cf038bd72898961424` (= `s4-matrix/arm1-t2`)
FROM: s4-matrix.planner
TO: s4-matrix.implementer
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: IMPL — execute the approved T2 NSDMI cause-fix: one line in git.hpp; then retained fixed-head Linux evidence; completion report requests the fixed head, the retained build and repo_git results, and the eight-site confirmation

Delegated-condition verification, run at this seat at issue time (`185207`):

1. **Plan gate (Edge 2):** `PLAN-REVIEW-IMPLEMENTER-T2-NSDMI-R1-APPROVE-EIGHT-SITE-CENSUS-20260821-184330`
   — `VERDICT: approve`, `AUTHORITY: review-only`, FROM `s4-matrix.implementer` TO
   `s4-matrix.planner`, and the **sole** holder of `s4-matrix-t2-nsdmi-fix-plan-review-r1`.
2. **Plan bytes re-hashed at issue time**, not carried from the approval on report:
   `bb0a4a6d6be0f0e8ff496bf024bf33259faba7df64088329b86bd17e280095d1`, blob
   `e568dc45b1bd951827db527c9bec3cfbeed7332a` — **both match** what the approval bound, so
   the artifact has not drifted between approve and issue.
3. **Chain, each link a sole ID holder:** this token → `…plan-review-r1` (`184330`, approve)
   → `…plan-r1` (`183854`, my PLAN, TO the Implementer) → the Orchestrator's `164516` ruling
   of option B, which authorized the bounded in-lane repair and delegated issuance here.
4. **No design edge is claimed.** `164516` scoped this to `git.hpp` with no sealed, schema,
   charter, `.github`, or cross-lane surface. I assert no `DESIGN_LOCK_ID` I do not hold.
5. **Token ID free:** no existing relay holds `s4-matrix-t2-nsdmi-impl`.
6. **Target unmoved:** `e172343` is `fix(review): compose dynamic empty Git config overrides`.

SCOPE_DIFF:
- src/core/repo/git.hpp -> in
SCOPE_DIFF_RESULT: all-in

SCOPE_ROW_EVIDENCE (per IN path — approved PLAN rev1 mapping):
- src/core/repo/git.hpp: exactly ONE line, at `:21` inside `struct Opts`, changing `std::vector<std::string> empty_config_keys;` to `std::vector<std::string> empty_config_keys{};`. Nothing else in the file and nothing else in the tree. Do NOT add `cwd{}` or `stdout_file{}` — the `164516` latitude was DECLINED in the approved plan and their future-omission risk is registered as a separate follow-up, so taking it here would exceed the approved scope

BINDING EXECUTION CONDITIONS — carried from the approving review and PLAN rev1:

1. **The pre-token scratch measurements are PLAN evidence and do NOT substitute for the fixed-head run.** You must produce and RETAIN the canonical Linux build and `repo_git` results at the actual fixed head — a fresh evidence root, receipts absent-before and non-empty-after, hashed — before T2's Stage-3 panel.
2. **Exit is the run, not the diff.** The canonical Ubuntu 24.04 `--platform linux/amd64` build must reach GREEN at the fixed head, under the pinned toolchain, non-root, with `nofile` soft raised to the inherited hard limit inside the drop. Capture every exit status explicitly and never through a pipe.
3. **The eight-site census is the acceptance frame, not five.** All eight `Git::Opts` constructions live in the single TU of `biv_repo_git_tests` — empty-brace `:57 :124 :265`, plain default-init `:76 :147 :228`, designated `:244 :293`. A clean compile of that TU is what proves no site is perturbed; report it as an eight-site result.
4. **`harness-selftest` is separately adjudicated under `201613`** — expected red on Linux, candidate-neutral, nondeterministic membership. Report it separately and do NOT label the full Linux suite GREEN.
5. **The count-gate SHAPE finding rides T2's stage-4 cells** as a coverage-**visibility** gap, not a red: T2's fourth binary (`biv_repo_git_tests`) means `biv_tests` staying at 385 is neutral precisely because T2's new tests are not in it. Do not read the count gate as covering them.
6. **Nothing beyond the one SCOPE_DIFF path.** No test file, no `CMakeLists.txt`, no `.github`, no harness, no sealed or schema surface. If the repair appears to require any of those, STOP and route rather than widening.
7. **Charter conditions hold:** disposable containers only, host worktree preserved, no unrelated Docker resource pruned or removed.

NOT DISPATCHED, and none of it implied by this token: merge, push, force-push, PR mutation or comment, remote CI, `.github` edit, publication, the Arm-1 schema act (F+G-fenced), deployment, release. T3/T4 remain at their old heads and `compare.py` remains owed at T3 under its test obligation. Linux `nonzero_exit` remains OWED in T1's stage-4.

Completion report should carry: the fixed T2 head SHA, the resulting `git.hpp` SHA-256, the retained evidence root with its receipts, the canonical Linux build and `repo_git` results with every captured exit status, the eight-site confirmation, and `harness-selftest` reported separately.

DISPATCH IMPL

ACTIONS_GIT_REF: docs lane only — this dispatch relay + its INDEX row ride one explicit-path commit (SHA lands after filing). Verification at this seat was read-only: re-hashing the approved PLAN, `git hash-object` for blob identity, greps for sole-ID-holder checks, and `git log -1 e172343`. No product or test path was touched by any action at this seat; no ref moved; no container started; the candidate worktree and the published surface are untouched by this relay.
FINAL_GIT_STATUS_SHORT: this relay and its INDEX row are this seat's only working-tree delta at commit time; the shared checkout carries sibling-authored untracked paths, preserved and unclaimed

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/IMPL-PLANNER-T2-NSDMI-FIX-DISPATCH-20260821-185207.md` → TO `s4-matrix.implementer`; carries the bare `DISPATCH IMPL` token
- CHAIN VERIFIED AT ISSUE TIME, not accepted on report: the approving PLAN-REVIEW `184330` is `VERDICT: approve`, review-only, and the SOLE holder of `s4-matrix-t2-nsdmi-fix-plan-review-r1`; the approved PLAN re-hashes at issue time to `bb0a4a6d…` with blob `e568dc45…`, BOTH matching what the approval bound; the token ID was free; `e172343` unmoved
- PARENT is the APPROVING REVIEW, not the PLAN and not the Orchestrator's `164516`; no design edge claimed because none exists for a bounded in-lane repair
- SCOPE exactly ONE path, `SCOPE_DIFF_RESULT: all-in`, with a `SCOPE_ROW_EVIDENCE` row naming the single line at `git.hpp:21` and EXPLICITLY forbidding `cwd{}`/`stdout_file{}` — that latitude was declined in the approved plan, so taking it would exceed scope
- BINDING: pre-token scratch measurements are PLAN evidence ONLY and do not substitute for the retained fixed-head run; exit is the RUN not the diff, canonical Ubuntu 24.04 amd64 GREEN at the fixed head under the pinned toolchain, non-root, with the descriptor lift, every exit status captured explicitly and never through a pipe
- THE EIGHT-SITE CENSUS is the acceptance frame: empty-brace `:57 :124 :265`, plain default-init `:76 :147 :228`, designated `:244 :293`, all in the one `biv_repo_git_tests` TU whose clean compile is the proof — report it as an eight-site result, not five
- `harness-selftest` separately adjudicated under `201613` and the full Linux suite never labelled GREEN; the count-gate SHAPE finding rides T2's stage-4 cells as a coverage-VISIBILITY gap since T2's fourth binary means 385 is neutral precisely BECAUSE the new tests are not in `biv_tests`
- NOT DISPATCHED: merge, push, force-push, PR mutation or comment, remote CI, `.github` edit, publication, schema act, deployment, release. T3/T4 at old heads; `compare.py` owed at T3; Linux `nonzero_exit` owed in T1 stage-4; schema F+G-fenced; merge != push != release; release hold ABSOLUTE
