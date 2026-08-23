## SITREP — T4 stops at binding O-1b: GCC 13 enumerates the authorized seventeen GitInvokeOptions pairs plus two extra EngineSourceState pairs; all product/test edits reverted and no candidate exists

ROLE: Implementer
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-matrix-t4-o1b-exact17-fail-two-extra-engine-source-state
PARENT_DISPATCH_ID: s4-matrix-t4-nsdmi-fix-impl
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/IMPL-PLANNER-T4-NSDMI-GUARD-DISPATCH-20260822-163256.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-T4-NSDMI-R2-SEVENTEEN-PAIRS-DUAL-BASELINE-20260822-161333.md; .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-T4-O1-MULTISET-CORRECTED-REAL-ORCHESTRATOR-SEVENTEEN-20260822-160705.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — the pair Planner must rule the two extra EngineSourceState warning pairs and issue any successor plan/review/token before another product or test edit; no scope expansion, caller edit, remote CI, push, PR mutation, merge, publication, deployment, schema act, or release is authorized
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: reconstructed T4 `29120d09891bfc46e80635c2212befa22a0e2604` on FINAL T3 `70601fc201b3c41d2542d82399787b5febcbf03c`
CANDIDATE: none — no product/test commit was made and T4 remains at `29120d09891bfc46e80635c2212befa22a0e2604`
FROM: s4-matrix.implementer
TO: s4-matrix.planner
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: T4 O-1b exact-17 oracle FAILS on binding Ubuntu GCC 13 with 19 unique pairs — the authorized 17 are present exactly once plus two extra EngineSourceState::neutralized_git_config_keys pairs at test lines 840 and 865; STOP honored, edits reverted, no commit, successor ruling required

The implementation token binds rev2 literally: O-1b must compile every relevant translation unit
at untouched `29120d0` in the same Ubuntu 24.04/GCC 13 environment as O-1a, with
`-Wno-error=missing-field-initializers` appended after the real `-Werror`; the result must contain
the exact seventeen file-line-member pairs, and any missing, extra, duplicate or differently-bound
pair stops and routes. That stop fired before any candidate could be committed.

## Binding evidence

O-1a is valid canonical RED. A fresh disposable `ubuntu:24.04` container ran with
`--platform linux/amd64`, `--init`, GCC 13.3.0, and `nofile` soft/hard
`1048576/1048576`. The real `-Wall -Wextra -Werror` build exited nonzero on
`-Werror=missing-field-initializers` in the expected `GitInvokeOptions` class. Its retained log is
`01-o1a-linux-red-gxx-make.log`, 192624 bytes, SHA-256
`484c08ca22027ce47c918da4f21bba9c270858eec2b17972ea80c7f3b5ed8c21`.

O-1b used a host-created immutable archive of exact base `29120d0`, 9492480 bytes, SHA-256
`90920215895e376ab50b642bab35d57e16927c1cedd3eec7da6723015c6e0fa2`. A fresh disposable
Ubuntu 24.04 linux/amd64 `--init` container again used GCC 13.3.0 and the same nofile state.
Its compiler launcher ends with exactly:

```text
exec "$@" -Wno-error=missing-field-initializers -fmax-errors=0
```

The retained verbose compile commands show project `-Werror` before that launcher suffix. The
`biv_repo_engine_tests` dependency build compiled `classify.cpp`, `capture.cpp`,
`eligibility.cpp`, `restore.cpp`, and `tests/test_repo_engine.cpp`, linked successfully, and the
container exited zero absent another compiler error. The authoritative log is
`04-o1b-linux-gcc13-enumerate-valid.log`, 207300 bytes, SHA-256
`41639b79eb141525a4aeb966bdd0a545b6c4970e9a3b2824c5efe439cc096b41`.

The mechanical warning projection reports nineteen unique pairs, every one at multiplicity one.
All seventeen bound `GitInvokeOptions` pairs are present: twelve `budget_override` omissions and
five `empty_config_keys` omissions over the thirteen governed initializer sites. The test-site
diagnostic is reported by GCC at closing line 629 for the initializer beginning at bound line 628.
Two additional pairs are also present:

```text
1 tests/test_repo_engine.cpp:840:EngineSourceState::neutralized_git_config_keys
1 tests/test_repo_engine.cpp:865:EngineSourceState::neutralized_git_config_keys
```

Both are real initializers at exact base `29120d0`. They are outside rev2's exact seventeen-member
oracle. The manifest is `04-o1b-warning-manifest.txt`, 1462 bytes, SHA-256
`1d96e7957e870b711c8cb31d2cf622e082745b3b4b95b42441b0ae4b46546ea8`.

The first O-1b archive attempt is retained but NON-EVIDENTIARY: it tried to create the archive
inside a container that could not see the linked-worktree gitdir, so archive extraction failed and
`/work/CMakePresets.json` was absent. The corrected host-created archive and fresh container above
are the binding run. Earlier Homebrew GCC 15 observations likewise remain diagnostic context only;
the two extras reproduced under the specified GCC 13 oracle, so this is not a compiler-version
escape.

## Stop disposition

The two authorized-path edits were transient and uncommitted: `{}` on the two
`GitInvokeOptions` members and the minimal direct Catch2 class guard. Once O-1b showed the two
extra pairs, I reverted only those hunks. I did not broaden into `EngineSourceState`, callers, or
the oracle; I did not run O-2, O-3, O-4, or O-5 after the stop; and I made no product/test commit.

Fresh clean-revert evidence records:

```text
HEAD 29120d09891bfc46e80635c2212befa22a0e2604
git status --short          empty
git diff --exit-code        0
git diff --check            0
git_exec.hpp SHA-256        ffeacd32f124a5e5ba091be636242a333a0e85d16b3bec5f7542ed7f0194a253
test_repo_engine.cpp SHA-256 72e5e86a0845c8d08caaceeec0fbc2385e24575cf3be27dd3869aa2167a70e74
```

That receipt is `05-blocked-clean-revert.log`, 397 bytes, SHA-256
`af35279c4922df490072b439f84c555387934ad61c989d8f4f43695821ab3eaa`. The full implementation
report is `task-1-report.md`, 7488 bytes, SHA-256
`0a9f8735dcc8a187ac0c1dc3ddfafc8de461bda00e1fe79ebc28c4eb5a218fb4`.

The evidence root is retained in the isolated T4 worktree at:

```text
/Users/jack/.config/superpowers/worktrees/bivpak/s4-matrix-arm1-t4/.superpowers/sdd/IMPL-PLANNER-T4-NSDMI-GUARD-DISPATCH-20260822-163256
```

Required word downward: classify and bound the two `EngineSourceState` pairs, then provide a
successor plan/review/token if another implementation attempt is wanted. This report does not
choose whether the successor adds an `EngineSourceState` cause-fix, changes caller bytes, or
redefines the oracle. T4 is not implemented, not final, and not panelable. T1 `00c06d9`, T2
`7688bbd`, and T3 `70601fc` remain FINAL; T4 stays clean, local, and unpublished at `29120d0`.
The release hold remains ABSOLUTE.

ACTIONS_GIT_REF: transient edits only in the isolated T4 worktree under the direct token, then exact apply-patch reversion after the binding O-1b STOP; no candidate commit and no T4 ref movement. Read-only verification and disposable local Docker validation only. This report and one live-EOF INDEX row ride one explicit-path docs-lane commit on main. No remote CI, push, PR mutation, merge, publication, deployment, schema act, or release.
RELAY_LINT: exact-file with freshness immediately before commit; live INDEX EOF re-read before append; INDEX lint compared against its inherited baseline; post-commit exact-file verification without freshness.
FINAL_GIT_STATUS_SHORT: isolated T4 worktree clean at `29120d0`; shared main preserves all sibling-authored tracked and untracked state unchanged and unclaimed; only this relay and its one INDEX append belong to this docs act.

CARRY LIST:
- O-1a canonical Ubuntu 24.04/GCC 13 RED is valid.
- O-1b compiled every relevant governed TU and linked at exit zero with the warning demoted after `-Werror`, but the exact-membership oracle FAILS: seventeen authorized pairs plus two extra `EngineSourceState::neutralized_git_config_keys` pairs at test lines 840 and 865, all unique and multiplicity one.
- The failed in-container archive attempt and non-binding Homebrew GCC 15 observation are retained and explicitly excluded from the verdict.
- STOP honored before O-2/O-3/O-4/O-5; only the two authorized transient hunks existed, both reverted; T4 clean at `29120d0`; no product/test commit or candidate.
- Next actor is `s4-matrix.planner` for a bounded successor ruling; no implementation, remote CI, publication, integration, schema, deployment, or release authority follows from this report.
