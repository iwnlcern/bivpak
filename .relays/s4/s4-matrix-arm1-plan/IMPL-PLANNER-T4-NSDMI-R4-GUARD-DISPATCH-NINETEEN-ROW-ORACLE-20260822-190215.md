## IMPLEMENTATION TOKEN — T4 NSDMI class guard under rev4: three files, the literal nineteen-row raw-diagnostic oracle, and the four-arm guard-site discriminator

ROLE: Planner
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: s4-matrix-t4-nsdmi-fix-impl-r4
PARENT_DISPATCH_ID: s4-matrix-t4-nsdmi-fix-plan-review-r4
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-T4-NSDMI-R4-APPROVE-NINETEEN-ROWS-DIAGNOSTIC-LINE-GUARD-SITE-BOUND-20260822-184513.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-T4-NSDMI-R4-NINETEEN-ROWS-LITERAL-DIAGNOSTIC-LINE-GUARD-SITE-BOUND-20260822-183716.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new operator gate — this token spends the rev4 plan gate approved at `184513` and authorizes product/test edits ONLY inside the three scope rows below. It authorizes NO merge, push, PR mutation, remote CI, schema act, publication, deployment, or release, and no scope widening. Any STOP condition halts before the next obligation and routes to this seat. The release hold is ABSOLUTE
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
DESIGN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: reconstructed T4 `29120d09891bfc46e80635c2212befa22a0e2604` on FINAL T3 `70601fc201b3c41d2542d82399787b5febcbf03c`
AUTHORIZING_PLAN: blob `d2feb3a0bdf7c5a78b8f4defebb8a3a708a57ec0`, SHA-256 `4c816a00c8a9fe2da6bf713f88a0efda9a54c628feba828cc3be3daf2ea49f07`, commit `83cc075d6b292b52e1314b787d32c11ba7a74f61`
AUTHORIZING_REVIEW: `PLAN-REVIEW-IMPLEMENTER-T4-NSDMI-R4-APPROVE-NINETEEN-ROWS-DIAGNOSTIC-LINE-GUARD-SITE-BOUND-20260822-184513.md`, commit `62fcd79`, `VERDICT: approve`
FROM: s4-matrix.planner
TO: s4-matrix.implementer
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: Bare implementation token for T4 NSDMI under rev4 — three IN paths with per-row preimage evidence, the literal nineteen-row raw-GCC-diagnostic-line multiset as the O-1b oracle with its closure STOP, and O-4a through O-4d binding the guard site positively and by removal

I re-derived the approval at my seat before issuing this: `plan_review_approved` returns True on the
review bytes and False on a trailing-period control, so the verdict is canonical and not merely
readable. The rev4 identity the review cites re-derives exactly here — blob
`d2feb3a0bdf7c5a78b8f4defebb8a3a708a57ec0`, SHA-256
`4c816a00c8a9fe2da6bf713f88a0efda9a54c628feba828cc3be3daf2ea49f07`, commit
`83cc075d6b292b52e1314b787d32c11ba7a74f61`. Dispatch IDs `s4-matrix-t4-nsdmi-fix-plan-r4` and
`s4-matrix-t4-nsdmi-fix-plan-review-r4` each have exactly one holder; this token's own ID had zero
before this relay.

SCOPE_DIFF:
- src/core/repo/git_exec.hpp -> in
- src/core/repo/types.hpp -> in
- tests/test_repo_engine.cpp -> in
SCOPE_DIFF_RESULT: all-in

SCOPE_ROW_EVIDENCE:
- src/core/repo/git_exec.hpp -> preimage at 29120d0 is 2496 bytes, SHA-256 ffeacd32f124a5e5ba091be636242a333a0e85d16b3bec5f7542ed7f0194a253, git blob 4224cdabb35cb4c6d65772fa8c7011aaedb5ebef; authorized delta is brace-init on GitInvokeOptions::budget_override at line 24 and GitInvokeOptions::empty_config_keys at line 25, nothing else in the file
- src/core/repo/types.hpp -> preimage at 29120d0 is 6251 bytes, SHA-256 eea2dcce8fb4f2fdc2dc432fdb26917d7c27a7212609da39d4bf428a7c3fe2dd, git blob 88d68409f55b5dab5c61d2d4981c11fdbbf0d145; authorized delta is EXACTLY ONE LINE, brace-init on EngineSourceState::neutralized_git_config_keys at line 192; repo_path and penumbra_paths untouched and every other struct and byte in this shared file byte-identical
- tests/test_repo_engine.cpp -> preimage at 29120d0 is 53795 bytes, SHA-256 72e5e86a0845c8d08caaceeec0fbc2385e24575cf3be27dd3869aa2167a70e74, git blob 991b0c675bd9baceee7ee70b345e406db58c4ea0; authorized delta is the ADDITION of the GitInvokeOptions class guard as a new case, plus the transient O-4 arms which must be fully reverted; the existing initializer at diagnostic line 629 and both EngineSourceState sites at 840 and 865 remain byte-identical

## The oracle you are bound to

O-1b's expected set is the nineteen rows below, compared as a MULTISET on
(FILE, RAW_GCC_DIAGNOSTIC_LINE, STRUCT, MEMBER). LINE means the raw GCC 13 diagnostic line and
nothing else. Initializer opening lines are NOT the oracle and must not be substituted.

```text
mult  FILE                            LINE  STRUCT             MEMBER
 1    src/core/repo/capture.cpp        38   GitInvokeOptions   budget_override
 1    src/core/repo/capture.cpp        91   GitInvokeOptions   budget_override
 1    src/core/repo/capture.cpp       111   GitInvokeOptions   budget_override
 1    src/core/repo/capture.cpp       155   GitInvokeOptions   budget_override
 1    src/core/repo/capture.cpp       292   GitInvokeOptions   budget_override
 1    src/core/repo/capture.cpp       388   GitInvokeOptions   budget_override
 1    src/core/repo/classify.cpp       70   GitInvokeOptions   budget_override
 1    src/core/repo/classify.cpp      114   GitInvokeOptions   budget_override
 1    src/core/repo/eligibility.cpp    67   GitInvokeOptions   budget_override
 1    src/core/repo/eligibility.cpp   109   GitInvokeOptions   budget_override
 1    src/core/repo/eligibility.cpp   182   GitInvokeOptions   budget_override
 1    src/core/repo/restore.cpp        33   GitInvokeOptions   budget_override
 1    src/core/repo/eligibility.cpp    67   GitInvokeOptions   empty_config_keys
 1    src/core/repo/eligibility.cpp   109   GitInvokeOptions   empty_config_keys
 1    src/core/repo/eligibility.cpp   182   GitInvokeOptions   empty_config_keys
 1    src/core/repo/restore.cpp        33   GitInvokeOptions   empty_config_keys
 1    tests/test_repo_engine.cpp      629   GitInvokeOptions   empty_config_keys
 1    tests/test_repo_engine.cpp      840   EngineSourceState  neutralized_git_config_keys
 1    tests/test_repo_engine.cpp      865   EngineSourceState  neutralized_git_config_keys
                                                     TOTAL UNIQUE PAIRS: 19
```

CLOSURE STOP: any reported pair naming a struct outside `{GitInvokeOptions, EngineSourceState}`
STOPS. Do not fix it and do not widen the oracle. Any missing, extra, duplicate or
differently-bound pair likewise STOPS and routes here.

## Obligations

```text
O-1a  untouched 29120d0, real -Wall -Wextra -Werror -> NONZERO plus the
      missing-field-initializers class.
O-1b  identical bytes/compiler/environment, -Wno-error=missing-field-initializers appended
      AFTER -Werror, every governed TU compiled to completion -> exit zero absent any other
      error, and the nineteen-row multiset above matched exactly.
      -fmax-errors=0 proves within-TU continuation only, never whole-population reach.
O-2   Linux focused build and tests, Ubuntu 24.04 linux/amd64, Docker --init, nofile soft
      raised to the inherited hard limit -> GREEN, residuals classified against the
      registered R-4.35 four-member family, anything outside it STOPS. No whole-suite-green
      claim.
O-3   macOS T2/T3/T4 interaction set GREEN with counts and exit status reported.
O-4   PRECONDITION record GUARD_LINE = the raw GCC diagnostic line of the guard's own
      GitInvokeOptions initializer at the fixed head.
      O-4a  fixed head + a TEMPORARY NSDMI-less member on GitInvokeOptions, real -Werror
            -> NONZERO. Proves the policy and nothing more.
      O-4b  same tree, warning demoted so every TU compiles -> the enumerated pair set MUST
            CONTAIN (tests/test_repo_engine.cpp, GUARD_LINE, GitInvokeOptions, <temp member>).
            TU-level or member-name-level binding is NOT sufficient.
      O-4c  temp member RETAINED, the new guard case REMOVED, same demoted policy -> that
            exact tuple MUST BE ABSENT. Other pre-existing-caller diagnostics may remain.
      O-4d  temp member removed and guard restored -> focused build AND test GREEN, and all
            three files at their fixed post-fix digests.
      Any other compiler or test error is not the discriminator and STOPS.
O-5   exactly three changed files versus 29120d0; the types.hpp diff EXACTLY ONE LINE;
      classify.cpp, capture.cpp, eligibility.cpp and restore.cpp byte-identical; the two
      EngineSourceState sites 840 and 865 unchanged; all thirteen existing GitInvokeOptions
      initializers unchanged with the guard a fourteenth site rather than an edit.
```

Report GUARD_LINE explicitly in your SITREP — the O-4b and O-4c verdicts are unreadable without it.

## Fence

Exactly the three IN paths. Not the four repo callers, not `git.hpp` or `Git::Opts`, not
`repo_path`/`penumbra_paths`, not any other struct in `types.hpp`, no other production byte, no
`.github/`, no schema, no harness, not T4's other files, not the stage-5 report's contents.

T1 `00c06d9`, T2 `7688bbd`, T3 `70601fc` remain FINAL. T4 is clean, local, unpublished and not
panelable at `29120d0`. Merge is not push and neither is release; the release hold is ABSOLUTE.

DISPATCH IMPL

ACTIONS_GIT_REF: none — no edits made at this seat; no product, test, branch, ref or worktree moved and no candidate exists. Read-only at this seat: `plan_review_approved` measured True on the approval bytes with a trailing-period must-be-NO control returning False; unique dispatch-holder counts; re-derivation of the rev4 blob, SHA-256 and commit; and `git cat-file -s` plus `git show | shasum -a 256` preimages for the three IN paths at `29120d0`. No merge, push, PR mutation, or remote CI. Docs lane: this relay and its INDEX row ride ONE explicit-path commit.
FINAL_GIT_STATUS_SHORT: this relay and its INDEX row are this seat's only working-tree delta at commit time; `git status --porcelain` over `harness/`, `src/`, `tests/`, `CMakeLists.txt` is empty; the shared checkout carries sibling-authored untracked paths, preserved and unclaimed
RELAY_LINT: all three arms before commit — exact-file WITH freshness; `--index` error set diffed against the pre-append blob; `--relay-root` run with this relay present AND moved aside, requiring identical error sets. `substantive_actions_ref` and `implementation_work_claimed` both measured False on the finished bytes with a positive control, and `operational_token_text` showing exactly ONE live bare token.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/IMPL-PLANNER-T4-NSDMI-R4-GUARD-DISPATCH-NINETEEN-ROW-ORACLE-20260822-190215.md` → TO `s4-matrix.implementer`
- BARE `DISPATCH IMPL` ISSUED to `s4-matrix.implementer`, parented to the approving PLAN-REVIEW `s4-matrix-t4-nsdmi-fix-plan-review-r4` at commit `62fcd79` — never to the plan and never to the orchestrator relay that prompted it. Verdict canonicality was MEASURED, not read: `plan_review_approved` True on the bytes, False on a trailing-period control
- THREE IN PATHS with per-row preimage evidence at `29120d0`: `git_exec.hpp` 2496 bytes / `ffeacd32f124a5e5ba091be636242a333a0e85d16b3bec5f7542ed7f0194a253`; `types.hpp` 6251 bytes / `eea2dcce8fb4f2fdc2dc432fdb26917d7c27a7212609da39d4bf428a7c3fe2dd`; `test_repo_engine.cpp` 53795 bytes / `72e5e86a0845c8d08caaceeec0fbc2385e24575cf3be27dd3869aa2167a70e74`. `SCOPE_DIFF_RESULT: all-in`
- THE ORACLE TRAVELS WITH THE TOKEN, LITERAL: nineteen rows at multiplicity 1 on (FILE, RAW_GCC_DIAGNOSTIC_LINE, STRUCT, MEMBER) — capture `38 91 111 155 292 388`, classify `70 114`, eligibility `67 109 182`, restore `33` for `budget_override` (12); eligibility `67 109 182`, restore `33`, test `629` for `empty_config_keys` (5); test `840 865` for `EngineSourceState::neutralized_git_config_keys` (2). LINE means the RAW GCC 13 DIAGNOSTIC LINE and opening lines must not be substituted. CLOSURE STOP on any struct outside the two, plus STOP on any missing, extra, duplicate or differently-bound pair
- O-4 IS FOUR ARMS AROUND A RECORDED `GUARD_LINE`: O-4a policy fires (temp member + real `-Werror` -> NONZERO, nothing more); O-4b the enumerated set MUST CONTAIN the exact `(tests/test_repo_engine.cpp, GUARD_LINE, GitInvokeOptions, <temp member>)` tuple, with TU-level or member-name-level binding explicitly INSUFFICIENT; O-4c negative control — temp member RETAINED and only the guard REMOVED, that exact tuple MUST BE ABSENT while pre-existing-caller diagnostics may remain; O-4d restore to build AND test GREEN at fixed digests. **GUARD_LINE must be reported in the SITREP or O-4b/O-4c are unreadable**
- AUTHORIZED DELTAS: `git_exec.hpp:24`/`:25` braced; `types.hpp:192` braced as EXACTLY ONE LINE with `repo_path`/`penumbra_paths` untouched (they belong to m-1's enlarged R-4.41); the guard ADDED as a fourteenth site in `test_repo_engine.cpp`. Zero caller edits. O-2 Linux under `--init` + the `nofile` lift with R-4.35 classification and NO whole-suite-green claim; O-3 macOS counts and exit; O-5 three changed files, four callers byte-identical, `840`/`865` unchanged
- NO merge, push, PR mutation, remote CI, schema act, publication, deployment or release rides this token; no scope widening; STOP and route here rather than repairing outside the fence. T1 `00c06d9` / T2 `7688bbd` / T3 `70601fc` FINAL; T4 `29120d0` clean, local, unpublished, not panelable; R-4.38 binary inventory remains my stage-5 obligation; release hold ABSOLUTE
