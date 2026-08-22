## PLAN-REVIEW — APPROVE: rev2 closes the seventeen-pair census and dual-baseline findings on the operative real-Orchestrator lineage; exact two-file fence and all downstream holds remain

ROLE: Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: approve
DISPATCH_ID: s4-matrix-t4-nsdmi-fix-plan-review-r2
PARENT_DISPATCH_ID: s4-matrix-t4-nsdmi-fix-plan-r2
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-T4-NSDMI-R2-SEVENTEEN-PAIRS-DUAL-BASELINE-20260822-161333.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-T4-O1-MULTISET-CORRECTED-REAL-ORCHESTRATOR-SEVENTEEN-20260822-160705.md; .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-T4-NSDMI-R1-MUST-REVISE-SEVENTEEN-DIAGNOSTICS-DUAL-BASELINE-20260822-153511.md; .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-OUT-OF-ROLE-ORCHESTRATOR-RELAY-AD13EF8-NONOPERATIVE-CORRECTION-20260822-160045.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new operator gate. This approval closes the rev2 plan gate only and permits s4-matrix.planner to issue the later bare implementation token parented to this review, addressed to exactly one Implementer and fenced by exactly two IN scope rows with per-row evidence. This review itself grants no product edit, branch/ref move, remote CI, push, PR mutation, merge, schema, publication, deployment, or release authority. The release hold is ABSOLUTE
REVIEWED_PLAN_ARTIFACT: PLAN-PLANNER-T4-NSDMI-R2-SEVENTEEN-PAIRS-DUAL-BASELINE-20260822-161333
REVIEWED_PLAN_SHA256: 8c91caed7d2f06caf8316275011bdd9be161af370d1fc8dccb24a95d803c87c4
REVIEWED_PLAN_GIT_BLOB: a1af036fc654bd2be7038e438398fcf38c879688
BASE: reconstructed T4 `29120d09891bfc46e80635c2212befa22a0e2604` descending from FINAL T3 `70601fc201b3c41d2542d82399787b5febcbf03c`
FROM: s4-matrix.implementer
TO: s4-matrix.planner
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: APPROVE rev2 at SHA-256 8c91caed — operative lineage holder counts are unique; MR-1 closes on exact 17 file-line-member pairs across 13 sites and an independent actual-header GCC 13.4.0 overlap probe; MR-2 closes on separate canonical-RED and warning-demoted enumerate-all arms; O-4 is C++-specific; all other obligations, exact two-file fence, and holds carry unchanged

APPROVE. I reviewed the committed rev2 bytes independently. Its lineage, census, oracle,
verdict split, guard discriminator, scope fence, and downstream ceremony match the operative
Orchestrator correction. The two MUST-REVISE findings in review r1 are closed.

## 1. Exact artifact and operative lineage

The reviewed rev2 is SHA-256
`8c91caed7d2f06caf8316275011bdd9be161af370d1fc8dccb24a95d803c87c4`, Git blob
`a1af036fc654bd2be7038e438398fcf38c879688`, committed at
`20fdcc74b7ae9411fe289296ad0028bf5c8d00e2`. Exact-file relay lint passes.

The rev2 dispatch ID and its parent dispatch ID each have holder count one. The parent is the
real-Orchestrator `160705` correction, not the out-of-role `154807` artifact. The latter remains
NON-OPERATIVE historical evidence and grants no routing, review, token, or scope authority.
Rev2 does not launder or parent through it.

## 2. MR-1 closed — exact seventeen member-site pairs

Direct reads at clean T4 `29120d0` reproduce the complete initializer population:

```text
file                          site lines                      budget_override   empty_config_keys
src/core/repo/classify.cpp    69,112                                2                  0
src/core/repo/capture.cpp     36,89,109,153,290,386                 6                  0
src/core/repo/eligibility.cpp 67,109,180                            3                  3
src/core/repo/restore.cpp     30                                    1                  1
tests/test_repo_engine.cpp    628                                   0                  1
13 initializer sites                                              12                  5
```

That is exactly seventeen file-line-member pairs. The three eligibility sites and the restore
site each omit both members and therefore each contribute two member-specific diagnostics.
Rev2 binds O-1b to the exact membership, not merely the total, and stops on a missing, extra,
duplicate, or differently-bound pair.

I also compiled three representative initializers against the actual `29120d0` header in a
disposable Docker-init `gcc:13` Linux/amd64 container, GCC 13.4.0, with only
`missing-field-initializers` demoted after `-Werror`. The omits-both shape emitted both
`budget_override` and `empty_config_keys`; the two one-member shapes emitted the corresponding
single warning. The probe exited zero, exactly as the enumerate-all arm predicts absent another
error. MR-1 is discharged.

## 3. MR-2 closed — two arms, two verdicts

Rev2 no longer asks one compiler arm to be both fatal and warning-demoted:

```text
O-1a canonical RED   untouched 29120d0, real -Wall -Wextra -Werror,
                     nonzero exit plus missing-field-initializers class
O-1b enumerate all   identical bytes/compiler/environment, only the named warning demoted
                     after -Werror, every relevant TU compiled, zero absent another error,
                     exact seventeen file-line-member pairs
```

It also correctly rejects `-fmax-errors=0` as proof of whole-build reach by itself and requires
any keep-going alternative to retain evidence that every relevant translation unit was actually
scheduled and compiled. MR-2 is discharged.

## 4. O-4, retained obligations, and fence

O-4 now uses C++ build predicates: the temporary NSDMI-less-member arm requires a nonzero focused
build whose diagnostic names that exact member; the removal arm requires the focused build and
test green plus restoration of `git_exec.hpp` to its fixed digest. Any other compiler or test
error stops. Rev2 additionally requires run-time confirmation that `biv_repo_engine_tests`
carries `-Wall -Wextra -Werror`; the pinned CMake bytes at lines 123-127 confirm that configured
target policy.

The following remain binding and unchanged: the two no-op NSDMIs, minimal guard in
`tests/test_repo_engine.cpp`, thirteen-site population, O-2 Linux Docker-init/nofile proof with
R-4.35 residual classification and no whole-suite-green claim, O-3 macOS T2/T3/T4 interaction,
O-5 exact two-file/no-caller/no-op proof, and the R-4.41/m-1 disposition for `Git::Opts`.

The implementation fence is exactly:

- `src/core/repo/git_exec.hpp`
- `tests/test_repo_engine.cpp`

No caller source, `git.hpp`, workflow, harness, schema, other T4 byte, or stage-5 report content
is in scope.

## 5. Gate disposition

The rev2 PLAN gate is APPROVED. The next valid actor is `s4-matrix.planner`, which may issue the
bare implementation token parented to this approval, TO exactly one Implementer, with exactly
the two scope rows above, `SCOPE_DIFF_RESULT: all-in`, and one `SCOPE_ROW_EVIDENCE` row per path.
Until that token exists, this Implementer has no product-edit authority.

T1 `00c06d9`, T2 `7688bbd`, and T3 `70601fc` remain FINAL. T4 remains clean, local,
unpublished, not final, and not panelable at `29120d0`. Merge is not push and neither is release;
the release hold is ABSOLUTE.

ACTIONS_GIT_REF: read-only review only — exact-file lint/hash/blob/commit of rev2; unique-holder lineage checks; direct `git show` and `git grep` census of all thirteen initializer bodies at `29120d0`; `git merge-base --is-ancestor` confirming FINAL T3 ancestry; direct CMake target-options read; one disposable Docker-init `gcc:13 --platform linux/amd64` GCC 13.4.0 syntax-only actual-header probe from a read-only T4 mount. No product/test/workflow edit, branch/ref move, remote CI, push, PR mutation, merge, schema, publication, deployment, or release. Docs lane: this review plus one live-EOF INDEX row ride one explicit-path commit.
RELAY_LINT: exact-file with freshness; live INDEX EOF re-read before append; `--index` compared with the parent blob; `--relay-root` checked for no new error attributable to this review; explicit-path add and commit only.
FINAL_GIT_STATUS_SHORT: T4 clean at `29120d0`; the shared checkout retains unrelated pre-existing untracked relays and migration notes unchanged and unclaimed; only this review and its INDEX append are this seat's docs-lane delta.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-T4-NSDMI-R2-APPROVE-SEVENTEEN-PAIR-DUAL-BASELINE-20260822-162648.md` -> `s4-matrix.planner`
- VERDICT APPROVE on rev2 SHA-256 `8c91caed7d2f06caf8316275011bdd9be161af370d1fc8dccb24a95d803c87c4`, blob `a1af036fc654bd2be7038e438398fcf38c879688`, commit `20fdcc74b7ae9411fe289296ad0028bf5c8d00e2`; exact-file lint passes; rev2 and operative-parent holder counts each equal one; parent is real-Orchestrator `160705`, while out-of-role `154807` remains NON-OPERATIVE and is not a routing edge
- MR-1 CLOSED: exact 13-site population yields 12 `budget_override` plus 5 `empty_config_keys` member-site pairs equals 17; eligibility lines 67, 109, 180 and restore line 30 omit BOTH; rev2 binds exact file-line-member membership and stops on any delta; independent actual-header GCC 13.4.0 Linux/amd64 Docker-init probe reproduced both warnings on the overlap shape and one warning on each one-member shape
- MR-2 CLOSED: O-1a is untouched canonical `-Werror` NONZERO RED; O-1b is same-byte/compiler/environment enumerate-all with only the warning demoted after `-Werror`, zero absent another error, every relevant TU compiled, exact 17-pair oracle; `-fmax-errors=0` alone is not whole-population reach proof
- O-4 CLOSED: temporary-member arm requires NONZERO build naming that member; removal requires focused build and test GREEN plus restored fixed-header digest; any other error stops; run-time target flags required
- RETAINED: two-member no-caller no-op fix, minimal guard, O-2/O-3/O-5, exact fence `git_exec.hpp` plus `tests/test_repo_engine.cpp`, `Git::Opts` outside at R-4.41/m-1, and all integration/release holds
- NEXT ACTOR `s4-matrix.planner`: bare implementation token parented to this approval, TO one Implementer, exactly two IN scope rows with all-in result and per-row evidence. This review grants no product authority. T4 remains clean/local/unpublished/not-final/not-panelable at `29120d0`; no remote CI, push, PR mutation, merge, schema, publication, deployment, or release; release hold ABSOLUTE
