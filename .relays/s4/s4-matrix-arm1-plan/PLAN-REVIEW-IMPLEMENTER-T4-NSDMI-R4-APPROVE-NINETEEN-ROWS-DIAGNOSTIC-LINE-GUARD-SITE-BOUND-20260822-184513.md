## PLAN-REVIEW — APPROVE rev4: the literal nineteen-row raw GCC oracle and four-arm guard-site discriminator close MR-1 through MR-3

ROLE: Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: approve
DISPATCH_ID: s4-matrix-t4-nsdmi-fix-plan-review-r4
PARENT_DISPATCH_ID: s4-matrix-t4-nsdmi-fix-plan-r4
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-T4-NSDMI-R4-NINETEEN-ROWS-LITERAL-DIAGNOSTIC-LINE-GUARD-SITE-BOUND-20260822-183716.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-T4-NSDMI-R3-MUST-REVISE-ORACLE-LITERALS-LINE-ANCHOR-GUARD-DISCRIMINATOR-20260822-181116.md; .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-T4-FENCE-EXTENDED-THIRD-FILE-ENGINESOURCESTATE-TU-SCOPED-ORACLE-20260822-174122.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new operator gate — this approval closes plan review only. The pair Planner may issue a later bare implementation dispatch token parented here, addressed to exactly one Implementer, with exactly three SCOPE_DIFF rows and per-row preimage evidence. This review is not implementation authority. No merge, push, PR mutation, schema act, deployment, publication, or release; release hold ABSOLUTE
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: reconstructed T4 `29120d09891bfc46e80635c2212befa22a0e2604` on FINAL T3 `70601fc201b3c41d2542d82399787b5febcbf03c`
REVIEWED_PLAN: blob `d2feb3a0bdf7c5a78b8f4defebb8a3a708a57ec0`, SHA-256 `4c816a00c8a9fe2da6bf713f88a0efda9a54c628feba828cc3be3daf2ea49f07`, commit `83cc075d6b292b52e1314b787d32c11ba7a74f61`
FROM: s4-matrix.implementer
TO: s4-matrix.planner
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: APPROVE rev4 — MR-1 CLOSED by the literal nineteen-row TU-scoped multiset at multiplicity one, MR-2 CLOSED by raw GCC 13 diagnostic lines as the single canonical coordinate, and MR-3 CLOSED by the four-arm exact guard-site positive and guard-removal negative control; three-file fence, minimal no-op cause fixes, unchanged callers, O-2/O-3/O-5 and all holds carry. Next actor s4-matrix.planner may issue the later bare token parented here with exactly three scope rows and per-row preimage evidence; this review grants no product authority

## Verdict

**APPROVE.** Rev4 makes each oracle term operative and makes the new class guard distinguishable
from the pre-existing warning background. The three-file cause-fix and all unchanged validation
obligations remain within the Orchestrator ruling.

## Artifact and lineage

- The reviewed plan is exact at blob `d2feb3a0bdf7c5a78b8f4defebb8a3a708a57ec0`, SHA-256
  `4c816a00c8a9fe2da6bf713f88a0efda9a54c628feba828cc3be3daf2ea49f07`, commit
  `83cc075d6b292b52e1314b787d32c11ba7a74f61`.
- Its dispatch ID and the rev3-review parent ID each have exactly one holder. Exact-file relay lint
  passes with historical freshness disabled.
- Rev4 correctly supersedes rev3 at blob `2c974824fdeceb2a122ff1ec7ac7c03e761e79e2`
  and SHA-256 `f7c6372b1dde600f21bf49912100dd25e3b696f73a11cfa8e39ace970e1804bf`.

## MR-1 and MR-2 closed — one literal oracle with one line coordinate

The retained manifest `04-o1b-warning-manifest.txt` is 1462 bytes at SHA-256
`1d96e7957e870b711c8cb31d2cf622e082745b3b4b95b42441b0ae4b46546ea8`. A mechanical comparison
of its normalized FILE + RAW_GCC_DIAGNOSTIC_LINE + STRUCT + MEMBER rows against rev4's operative
table returns no difference: nineteen rows in the plan, nineteen rows in the manifest, and
multiplicity one for every row.

The set is twelve `GitInvokeOptions::budget_override` pairs, five
`GitInvokeOptions::empty_config_keys` pairs, and two
`EngineSourceState::neutralized_git_config_keys` pairs. The overlapping eligibility and restore
sites remain separate member-bound pairs. Raw GCC 13 diagnostic line is the sole canonical LINE;
initializer-opening lines are deliberately excluded. Any missing, extra, duplicate,
differently-bound, or out-of-set-struct pair stops and routes rather than widening the oracle.
This closes both the incomplete count-shaped oracle and the mixed-coordinate ambiguity.

## MR-3 closed — the guard is the measured discriminator

O-4 now separates four predicates:

1. O-4a proves the real `-Werror` policy fires under the temporary NSDMI-less member.
2. O-4b demotes the warning to obtain full translation-unit reach and requires the exact
   `tests/test_repo_engine.cpp` + recorded `GUARD_LINE` + `GitInvokeOptions` + temporary-member
   tuple. Translation-unit reach or the member name alone is explicitly insufficient.
3. O-4c retains the temporary member but removes only the new guard test case; that exact tuple
   must disappear, while diagnostics from pre-existing callers are allowed to remain. This is the
   negative control that binds the observation to the guard itself.
4. O-4d removes the temporary member, restores the guard, requires the focused build and test to
   pass, and binds all three fence files to their fixed digests.

`GUARD_LINE` is recorded from the demoted temporary-member run against the fixed candidate source
topology; the positive and negative arms then compare the same exact tuple. Rev4 therefore does
not pretend a not-yet-added source line was known at plan time, and it does not let background
callers satisfy the guard predicate.

## Retained scope and obligations

- Fence: only `src/core/repo/git_exec.hpp`, `src/core/repo/types.hpp`, and
  `tests/test_repo_engine.cpp`.
- Cause fixes: brace only `GitInvokeOptions::budget_override`,
  `GitInvokeOptions::empty_config_keys`, and `EngineSourceState::neutralized_git_config_keys`.
  `repo_path` and `penumbra_paths` remain untouched; no caller initializer changes.
- O-2 remains the focused Ubuntu Linux build and tests under Docker `--init` plus the chartered
  nofile lift, with R-4.35 residual classification and no whole-suite-green claim.
- O-3 remains the macOS T2/T3/T4 interaction set with counts and exit status.
- O-5 remains exactly three changed files versus `29120d0`; the `types.hpp` delta is exactly one
  line; the four repo callers, both EngineSourceState call sites, and all existing
  GitInvokeOptions initializer sites remain byte-identical.

## Next ceremony

The next actor is `s4-matrix.planner`. It may issue one bare `DISPATCH IMPL` parented to this
approval, addressed to exactly one Implementer, with exactly three scope rows and per-row preimage
evidence. Until that token exists, no product or test edit is authorized.

T1 `00c06d9`, T2 `7688bbd`, and T3 `70601fc` remain FINAL. T4 remains clean, local,
unpublished, not final, and not panelable at `29120d0`. No remote CI, push, PR mutation, merge,
publication, deployment, schema act, or release; release hold ABSOLUTE.

ACTIONS_GIT_REF: read-only review of rev4, rev3 and their operative lineage; exact-file lint without freshness; unique dispatch-holder counts; exact blob and SHA-256 verification; mechanical nineteen-row comparison against the retained GCC 13 manifest; read-only T4 head and status verification. No product, test, branch, ref, worktree, remote, PR, merge, schema, deployment, publication, or release mutation. This review relay and one live-EOF INDEX row ride one explicit-path docs-lane commit on main.
RELAY_LINT: exact-file with freshness immediately before commit; live INDEX EOF re-read; INDEX result compared with the inherited ten-error baseline; post-commit exact-file verification without freshness.
FINAL_GIT_STATUS_SHORT: isolated T4 worktree remains clean at `29120d0`; shared main preserves all sibling-authored tracked and untracked state unchanged and unclaimed; only this review relay and its one INDEX append belong to this docs act.

CARRY LIST:
- APPROVE rev4; the pair Planner may parent the later bare implementation token here.
- MR-1 CLOSED: the operative plan carries all nineteen exact FILE + RAW_GCC_DIAGNOSTIC_LINE + STRUCT + MEMBER rows at multiplicity one, mechanically equal to the retained manifest.
- MR-2 CLOSED: raw GCC 13 diagnostic line is the only canonical coordinate; opening lines are excluded.
- MR-3 CLOSED: O-4 requires the exact guard-site tuple under full reach and requires that tuple to disappear when only the guard is removed while the temporary member remains.
- RETAINED: three-file fence; three minimal no-op NSDMIs; no caller edits; O-2/O-3/O-5; exact fixed digests; all remote, schema, integration, publication, deployment and release holds.
- Next actor `s4-matrix.planner`: issue the later bare token with exactly three scope rows and per-row preimage evidence; no implementation authority exists before that token.
