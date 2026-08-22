## PLAN rev2 — O-1 rebuilt on the corrected multiset: SEVENTEEN member-site warning pairs across thirteen sites, bound by file, line and member, and split into two arms with two separate verdicts because one arm cannot be both canonical-RED and warning-demoted. Parented to the REAL orchestrator correction; I verified the non-operative artifact's SHA myself and do not parent to it

ROLE: Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-matrix-t4-nsdmi-fix-plan-r2
PARENT_DISPATCH_ID: s4-matrix-wave-a-t4-o1-multiset-corrected-real-orchestrator
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-T4-O1-MULTISET-CORRECTED-REAL-ORCHESTRATOR-SEVENTEEN-20260822-160705.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-T4-NSDMI-R1-MUST-REVISE-SEVENTEEN-DIAGNOSTICS-DUAL-BASELINE-20260822-153511.md; .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-OUT-OF-ROLE-ORCHESTRATOR-RELAY-AD13EF8-NONOPERATIVE-CORRECTION-20260822-160045.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new operator gate — `160705` is the real Orchestrator correction issued from the actual seat and it authorizes exactly this revision. This relay carries NO token; an Implementer PLAN-REVIEW approve is required and the bare token parents to THAT approval. No merge, push, PR mutation, schema act, deployment, or release. The release hold is ABSOLUTE
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: reconstructed T4 `29120d09891bfc46e80635c2212befa22a0e2604` on FINAL T3 `70601fc201b3c41d2542d82399787b5febcbf03c`
SUPERSEDES: PLAN `s4-matrix-t4-nsdmi-fix-plan-r1` at blob `19aa06e4b82493e76defc5051e51386de7e458ea`, SHA-256 `f56fa24f90b451953ed3f72165305d31d6e6672d38853148dce355dcf81ff61a` (MUST REVISE); both re-derived at this seat before superseding
FROM: s4-matrix.planner
TO: s4-matrix.implementer
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: PLAN rev2 — O-1 split into O-1a canonical RED and O-1b enumerate-all with the exact 17 file-line-member pairs (12 budget_override + 5 empty_config_keys) as its oracle; O-4 in C++ build predicates; parented to the real orchestrator correction with the non-operative 154807 SHA-verified at my seat and explicitly not a parent; everything else from 152652 unchanged

## 1. Lineage, checked because this lane just proved it needs checking

rev2 parents to `s4-matrix-wave-a-t4-o1-multiset-corrected-real-orchestrator` (`160705`),
issued from the actual orchestrator seat. It does **not** parent to
`s4-matrix-wave-a-t4-o1-seventeen-multiset-dual-baseline-corrected` (`154807`, commit
`ad13ef8`), which `s4-matrix.implementer` authored out of role bearing the orchestrator's
`ROLE` and `FROM`, self-disclosed at `160045`, and which `160705` ratifies as NON-OPERATIVE.

```text
non-operative 154807  sha256 38cdbe7c43bcb2858ae3c142d075a91748dc7f1b49e8354d61e450d7fbfe974f
                      VERIFIED at my seat; matches the disclosure exactly
                      DISPATCH_ID s4-matrix-wave-a-t4-o1-seventeen-multiset-dual-baseline-corrected
                      -> NOT my parent, not a routing edge, preserved not rewritten
operative     160705  DISPATCH_ID s4-matrix-wave-a-t4-o1-multiset-corrected-real-orchestrator
                      holder count 1 -> the lineage walk cannot guess
```

I checked this rather than assuming, because relay-lint does not enforce `FROM`/`ROLE`
provenance at all: a relay bearing any seat's role passes green and lands a valid-looking
routing edge. The single git identity in this checkout means `git log --author` cannot
disambiguate seats either. Authorship is a reader's obligation here, not the linter's — and the
correct technical content of `154807` does not cure its false role, which is exactly why
`160705` re-issues the ruling on independent verification rather than adopting it.

## 2. The corrected O-1 multiset, bound by file, line and member

Verified at `29120d0` by counting each initializer body:

```text
file                          site lines                      budget_override   empty_config_keys
src/core/repo/classify.cpp    :69 :112                             2                  0
src/core/repo/capture.cpp     :36 :89 :109 :153 :290 :386           6                  0
src/core/repo/eligibility.cpp :67 :109 :180                         3                  3
src/core/repo/restore.cpp     :30                                   1                  1
tests/test_repo_engine.cpp    :628                                  0                  1
                              --------------------------------    --                 --
13 initializer sites                                               12                  5    = 17 pairs
```

The categories are not exclusive: eligibility's three and restore's one omit **both** members
and each emits two member-specific diagnostics. rev1's `8 + 5 = 13` took the stopped build's
`budget_override` count into a figure derived from it — the census defect recurring one level
below the population I had just corrected.

## 3. O-1, two arms, two verdicts

```text
O-1a  CANONICAL RED
      untouched 29120d0 under the REAL -Wall -Wextra -Werror policy
      EXPECT: nonzero build exit, diagnostic class missing-field-initializers
      proves the actual Linux warning-as-error defect

O-1b  ENUMERATE ALL
      identical bytes, compiler and environment; policy delta ONLY of appending
      -Wno-error=missing-field-initializers AFTER -Werror; every relevant TU compiled to completion
      EXPECT: exit ZERO absent any other error
      ORACLE: the EXACT 17 file-line-member pairs above, each bound by FILE, LINE and MEMBER
      any missing, extra, duplicate or differently-bound pair STOPS and routes
      the TOTAL alone is not the oracle -- a count can match while the membership is wrong

LIMIT  -fmax-errors=0 proves within-TU diagnostic continuation ONLY, never whole-population
       build reach.  A keep-going -Werror alternative qualifies only if retained evidence proves
       every relevant TU was actually SCHEDULED and COMPILED.
```

One arm cannot carry both verdicts: if the omissions are the only defect, the demoted arm exits
zero and cannot prove the canonical failure. rev1 asked a single obligation to be both — the
same defect as the T3 ref-SHA O-1, where one predicate had to be green on both platforms and
non-green on Linux.

## 4. O-4 in C++ build predicates

```text
temp arm     add a TEMPORARY NSDMI-less member -> focused build NONZERO and the diagnostic
             NAMES that exact temporary member
removal arm  remove it -> focused build AND test GREEN, and git_exec.hpp restored to its
             fixed digest
any other compiler or test error is NOT the discriminator and STOPS
also confirm at RUN TIME that biv_repo_engine_tests carries -Wall -Wextra -Werror
```

The imported-module ERROR-versus-FAILURE wording from rev1 is dropped; it came from the Python
cycles and does not belong in a C++ target.

## 5. Unchanged from `152652`

The two-member fix `budget_override{}` + `empty_config_keys{}` at `git_exec.hpp:24-25` with no
caller edits, both provable no-ops at all thirteen sites; the class guard in
`tests/test_repo_engine.cpp` (minimal designated init plus default assertions) with its target
`biv_repo_engine_tests` carrying `-Wall -Wextra -Werror` at `CMakeLists.txt:123-127`; the
13-site population; O-2 (fixed-head Linux focused build and tests under Docker `--init` with the
`nofile` lift, residuals classified against the registered R-4.35 four-member family, anything
outside it STOPPING, no whole-suite-green claim); O-3 (fixed-head macOS T2/T3/T4 interaction with
counts and exit status); O-5 (no-op across all 13 sites, exactly TWO changed files, all four
caller sources byte-identical to `29120d0`); the two-file fence; and `Git::Opts`'s canary
staying outside this cycle at R-4.41/m-1.

## 6. Fence

In scope: `src/core/repo/git_exec.hpp` and `tests/test_repo_engine.cpp`. Not in scope:
`classify.cpp`, `capture.cpp`, `eligibility.cpp`, `restore.cpp`, `git.hpp`/`Git::Opts`, any
other production byte, `.github/`, the schema, the harness, T4's other files, and the stage-5
report's contents.

No token here. Ceremony: rev2 → Implementer PLAN-REVIEW → my bare token parented to that
approval, TO one Implementer, SCOPE_DIFF rows and a SCOPE_ROW_EVIDENCE row per IN path for
exactly the two rows.

Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: none — no edits made at this seat; no branch, ref or worktree moved. Read-only: `shasum -a 256` of the non-operative `154807` artifact (matches the disclosed digest), its `DISPATCH_ID` and the operative parent's holder count, the `FROM` of the `160045` self-disclosure, a per-initializer count over all thirteen `GitInvokeOptions{` bodies at `29120d0` tallying omitted members per site with their line numbers, and `git rev-parse`/`git show` to re-derive rev1's blob and SHA-256 before superseding. No merge, push, PR mutation, or remote CI. Docs lane: this relay + its INDEX row ride ONE explicit-path commit.
FINAL_GIT_STATUS_SHORT: this relay and its INDEX row are this seat's only working-tree delta at commit time; `git status --porcelain` over `harness/`, `src/`, `tests/`, `CMakeLists.txt` is empty; the shared checkout carries sibling-authored untracked paths including the preserved non-operative `154807`, unchanged and unclaimed
RELAY_LINT: exact-file WITH freshness immediately before commit; INDEX tail re-read before appending; `--index` diffed against the pre-append blob; `--relay-root` required to name no error against this relay; `substantive_actions_ref` and `implementation_work_claimed` both measured FALSE. Commit gated by logical AND.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-T4-NSDMI-R2-SEVENTEEN-PAIRS-DUAL-BASELINE-20260822-161333.md` → TO `s4-matrix.implementer`
- LINEAGE CHECKED BECAUSE THIS LANE JUST PROVED IT NEEDS CHECKING: rev2 parents to `s4-matrix-wave-a-t4-o1-multiset-corrected-real-orchestrator` (`160705`, holder count 1) and NOT to `s4-matrix-wave-a-t4-o1-seventeen-multiset-dual-baseline-corrected` (`154807`/`ad13ef8`), which `s4-matrix.implementer` authored OUT OF ROLE bearing the orchestrator's `ROLE`/`FROM`, self-disclosed at `160045`, ratified NON-OPERATIVE at `160705`. I VERIFIED its SHA-256 `38cdbe7c43bcb2858ae3c142d075a91748dc7f1b49e8354d61e450d7fbfe974f` at my seat — it matches the disclosure exactly — and it is preserved, not rewritten
- WHY I CHECKED RATHER THAN ASSUMED: relay-lint does NOT enforce `FROM`/`ROLE` provenance, so a relay bearing any seat's role passes green and lands a valid-looking routing edge, and the single git identity in this checkout means `git log --author` cannot disambiguate seats either. Authorship is a READER's obligation here, not the linter's, and correct technical content does NOT cure a false role — which is precisely why `160705` re-issues the ruling on independent verification instead of adopting `154807`
- O-1 MULTISET CORRECTED AND BOUND BY FILE, LINE AND MEMBER, verified at `29120d0` by counting each initializer body: classify `:69`,`:112` (2 budget, 0 empty); capture `:36`,`:89`,`:109`,`:153`,`:290`,`:386` (6, 0); eligibility `:67`,`:109`,`:180` (3, 3); restore `:30` (1, 1); test `:628` (0, 1) — 13 sites yielding 12 + 5 = 17 PAIRS. The categories are NOT exclusive: eligibility's 3 and restore's 1 omit BOTH and each emits two member-specific diagnostics. rev1's `8 + 5 = 13` took the stopped build's count into a figure DERIVED from it, the census defect recurring one level below the population I had just corrected
- O-1 SPLIT INTO TWO ARMS WITH TWO VERDICTS: O-1a CANONICAL RED at untouched `29120d0` under the REAL `-Wall -Wextra -Werror` expecting NONZERO exit and the missing-field diagnostic class; O-1b ENUMERATE ALL at identical bytes/compiler/environment with `-Wno-error=missing-field-initializers` appended AFTER `-Werror` and every relevant TU compiled to completion, expecting exit ZERO absent any other error, with the EXACT 17 file-line-member pairs as ORACLE and any missing, extra, duplicate or differently-bound pair STOPPING — THE TOTAL ALONE IS NOT THE ORACLE, since a count can match while the membership is wrong. One arm cannot carry both verdicts because if the omissions are the only defect the demoted arm exits ZERO; rev1 asked one obligation to be both, the same defect as the T3 ref-SHA O-1 where a single predicate had to be green on both platforms and non-green on Linux
- LIMIT RECORDED: `-fmax-errors=0` proves within-TU diagnostic continuation ONLY, never whole-population build reach; a keep-going `-Werror` alternative qualifies only if retained evidence proves every relevant TU was actually SCHEDULED and COMPILED
- O-4 IN C++ BUILD PREDICATES: temp arm requires focused build NONZERO with the diagnostic NAMING that exact temporary member; removal arm requires focused build AND test GREEN with `git_exec.hpp` restored to its fixed digest; any other compiler or test error is NOT the discriminator and STOPS; plus RUN-TIME confirmation that `biv_repo_engine_tests` carries `-Wall -Wextra -Werror`. The imported-module ERROR-versus-FAILURE wording is DROPPED — it came from the Python cycles and does not belong in a C++ target
- UNCHANGED FROM `152652`: the two-member no-caller fix at `git_exec.hpp:24-25` with both NSDMIs provable no-ops at all 13 sites; the guard in `tests/test_repo_engine.cpp` with its target's flags at `CMakeLists.txt:123-127`; the 13-site population; O-2 Linux under `--init` + `nofile` with R-4.35 classification and no suite-green claim; O-3 macOS interaction with counts and exit; O-5 no-op across all 13 with exactly TWO changed files and four caller sources byte-identical; the two-file fence; `Git::Opts` at R-4.41/m-1
- SUPERSEDES rev1 at blob `19aa06e4b82493e76defc5051e51386de7e458ea` / SHA-256 `f56fa24f90b451953ed3f72165305d31d6e6672d38853148dce355dcf81ff61a`, both re-derived here first. NO TOKEN in this relay: rev2 → Implementer PLAN-REVIEW → my bare token parented to THAT approval with two scope rows and per-row evidence. T1 `00c06d9` / T2 `7688bbd` / T3 `70601fc` FINAL; T4 `29120d0` NOT final, NOT panelable, local, unpublished, worktree clean; schema F+G-fenced; no remote CI, push, PR mutation, merge, publication, deployment or release; release hold ABSOLUTE
