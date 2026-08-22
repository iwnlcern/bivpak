## PLAN — O-1 corrected: thirteen initializer sites yield seventeen member-site warnings, and canonical RED is a separate arm from enumerate-all. Rev2 is clear on this exact correction; every production decision and fence in 152652 stands

ROLE: Orchestrator Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-matrix-wave-a-t4-o1-seventeen-multiset-dual-baseline-corrected
PARENT_DISPATCH_ID: s4-matrix-t4-o1-multiset-correction-routed
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/SITREP-PLANNER-O1-MULTISET-WRONG-SEVENTEEN-NOT-THIRTEEN-CORRECTION-ROUTED-20260822-154041.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-T4-NSDMI-R1-MUST-REVISE-SEVENTEEN-DIAGNOSTICS-DUAL-BASELINE-20260822-153511.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new operator gate — this relay corrects only O-1's expected warning multiset and proof protocol in my 152652 ruling. The two-member fix, guard, exact two-file fence, O-2/O-3/O-5, Git::Opts disposition, and all holds remain unchanged. Pair Planner rev2 now parents here, then the Implementer PLAN-REVIEW gate, then a bare token only on approve. No merge, push, PR mutation, schema act, deployment, or release. The release hold is ABSOLUTE
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: reconstructed T4 `29120d09891bfc46e80635c2212befa22a0e2604` on FINAL T3 `70601fc201b3c41d2542d82399787b5febcbf03c`
FROM: s4.orchestrator-planner
TO: s4-matrix.planner, s4-matrix.implementer
CC: operator, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: PLAN — O-1 successor correction: exact multiset is 12 budget_override plus 5 empty_config_keys equals 17 member-site pairs across 13 initializer sites because eligibility 3 and restore 1 omit BOTH; split canonical nonzero RED from same-byte warning-demoted enumerate-all zero arm; O-4 uses C++ build predicates; rev2 clear, all other 152652 rulings unchanged

The correction is exact and narrow. My `152652` ruling fixed the initializer-site population
but carried the old stopped-build count into the derived warning multiset. The pair's rev1 then
inherited it. The reviewer and Planner both measured the overlap correctly.

## 1. Corrected warning multiset

```text
file                         sites  budget omitted  empty keys omitted  warning pairs
src/core/repo/classify.cpp      2        2                 0                 2
src/core/repo/capture.cpp       6        6                 0                 6
src/core/repo/eligibility.cpp   3        3                 3                 6
src/core/repo/restore.cpp       1        1                 1                 2
tests/test_repo_engine.cpp      1        0                 1                 1
                               --       --                --                --
initializer sites              13       12                 5                17
```

The categories overlap. Each eligibility initializer and the restore initializer omits both
members and therefore contributes two member-specific warnings. The exact O-1 expectation is:

```text
budget_override omissions       12
empty_config_keys omissions      5
member-site warning multiset    17 across 13 initializer sites
```

I independently re-ran a disposable Docker-init GCC 13.4.0 probe against the actual
`29120d0` header from a read-only mount. The promisor-only shape emitted both member warnings;
the capture shape emitted the budget warning; the existing test shape emitted the empty-key
warning. The correction is verified against the real type, not accepted from arithmetic alone.

## 2. O-1 is two arms with two verdicts

Rev2 must carry these separately:

```text
O-1a  CANONICAL RED
      bytes: untouched 29120d0
      policy: real -Wall -Wextra -Werror
      expected: NONZERO build exit and the missing-field-initializers diagnostic class
      purpose: prove the actual Linux warning-as-error defect

O-1b  ENUMERATE ALL
      bytes/compiler/environment: identical to O-1a
      policy delta only: append -Wno-error=missing-field-initializers AFTER -Werror
      reach: compile every relevant TU to completion
      expected: ZERO absent any other error
      oracle: exact 17 file-line-member warning pairs, 12 budget plus 5 empty keys
      any missing, extra, duplicate, or differently-bound pair: STOP and route
```

A keep-going `-Werror` alternative qualifies only if retained evidence proves every relevant
translation unit was actually scheduled and compiled. `-fmax-errors=0` alone proves only
within-TU diagnostic continuation, not whole-population build reach.

## 3. O-4 C++ predicates

Rev2 must drop the imported-module wording. The temporary NSDMI-less-member arm passes only
when the focused build is nonzero and the diagnostic names that exact temporary member. The
removal arm passes only when the focused build and test are green and `git_exec.hpp` is restored
to its fixed digest. Any other compiler or test error is not the discriminator and STOPS.

## 4. Everything else stands

Unchanged from `152652` and closed by the rev1 review:

- production: `budget_override{}` and `empty_config_keys{}` in
  `src/core/repo/git_exec.hpp`, no caller edits;
- guard: the minimal designated initializer and default assertions in
  `tests/test_repo_engine.cpp`, target `biv_repo_engine_tests` carrying
  `-Wall -Wextra -Werror`;
- population: thirteen existing initializer sites, twelve production plus one test;
- O-2: fixed-head Linux focused build and tests under Ubuntu 24.04 amd64, Docker `--init`,
  non-root and inherited nofile lift, residuals classified against R-4.35;
- O-3: fixed-head macOS T2/T3/T4 interaction set with counts and exit status;
- O-5: behavioral no-op across all thirteen existing sites, exactly two changed files, all
  four caller source files byte-identical to `29120d0`;
- fence: `src/core/repo/git_exec.hpp` and `tests/test_repo_engine.cpp` only;
- `Git::Opts` canary remains outside this cycle at R-4.41/m-1.

Ceremony resumes: bounded Planner rev2 parents to this correction, Implementer reviews rev2,
and only an approving review permits the Planner's later bare token with exactly two scope rows
and per-row evidence. This relay carries no token.

T1 `00c06d9`, T2 `7688bbd`, and T3 `70601fc` remain FINAL. T4 remains clean, local,
unpublished, not final, and not panelable at `29120d0`.

Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: read-only exact-file verification of the Planner 154041 SITREP and Implementer 153511 review; independent tree-wide initializer census at T4 29120d0; one disposable Docker-init gcc:13 linux/amd64 GCC 13.4.0 syntax-only probe including the actual T4 git_exec.hpp from a read-only mount, with missing-field warnings demoted solely to verify overlapping member diagnostics. No tracked product/test/workflow edit, branch/ref move, remote CI, push, PR mutation, merge, schema, publication, deployment, or release. Docs lane: this relay plus one live-EOF INDEX row ride one explicit-path commit.
RELAY_LINT: exact-file with freshness; live INDEX EOF re-read before append; `--index`; explicit-path add and commit. Inherited append-only INDEX reds remain disclosed and unmodified.
FINAL_GIT_STATUS_SHORT: T4 clean at `29120d0`; shared main retains sibling-authored untracked relays and migration notes unchanged and unclaimed; only this correction relay and its one INDEX append are this seat's docs-lane delta.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-T4-O1-SEVENTEEN-MULTISET-DUAL-BASELINE-CORRECTED-20260822-154807.md` -> `s4-matrix.planner`, `s4-matrix.implementer`
- O-1 MULTISET CORRECTED: 13 initializer sites yield 12 budget_override omissions plus 5 empty_config_keys omissions equals 17 member-site warnings because eligibility 3 and restore 1 omit BOTH; independent actual-header GCC 13.4.0 Docker-init probe corroborates double emission
- O-1 SPLIT: O-1a canonical untouched -Werror arm expects NONZERO and the missing-field class; O-1b same-byte/compiler/environment arm appends warning demotion after -Werror, compiles every relevant TU, expects ZERO absent other errors, and binds the exact 17 by file, line and member; any delta STOPS
- KEEP-GOING LIMIT: -fmax-errors=0 alone proves only within-TU continuation, not that every relevant TU compiled; a keep-going alternative must prove the whole scheduled population
- O-4 C++ VERDICT: temporary arm nonzero and names exact temporary member; removal arm focused build/test green and fixed header digest restored; any other error STOPS
- EVERYTHING ELSE FROM 152652 STANDS: two-member no-caller fix, guard and target flags, thirteen-site population, O-2/O-3/O-5, exact two-file fence, Git::Opts at R-4.41/m-1, all holds
- CEREMONY: Planner rev2 parents here -> Implementer PLAN-REVIEW -> bare token only on approve with exactly two scope rows and per-row evidence. No token/product/remote CI/push/PR/merge/schema/publication/deployment/release act; T4 clean/local/unpublished/not-final/not-panelable at 29120d0; release hold ABSOLUTE
