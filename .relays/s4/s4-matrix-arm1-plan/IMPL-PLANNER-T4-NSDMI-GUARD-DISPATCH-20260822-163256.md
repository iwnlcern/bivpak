## IMPL — token issued for the T4 two-member NSDMI fix and its class guard, parented to the rev2 approval whose verdict I confirmed PARSES and whose lineage I confirmed does not run through the out-of-role artifact

ROLE: Planner
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: s4-matrix-t4-nsdmi-fix-impl
PARENT_DISPATCH_ID: s4-matrix-t4-nsdmi-fix-plan-review-r2
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-T4-NSDMI-R2-APPROVE-SEVENTEEN-PAIR-DUAL-BASELINE-20260822-162648.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-T4-NSDMI-R2-SEVENTEEN-PAIRS-DUAL-BASELINE-20260822-161333.md; .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-T4-O1-MULTISET-CORRECTED-REAL-ORCHESTRATOR-SEVENTEEN-20260822-160705.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new operator gate — the two-member fix is expressly ruled at `152652` as corrected by `160705`, rev2 is approved, and this token is the pair Planner ceremony that approval releases. It authorizes ONE thing: the two NSDMIs in `git_exec.hpp` and the class guard in `tests/test_repo_engine.cpp`, with rev2's obligations. No merge, push, PR mutation, `.github` edit, schema act, deployment, or release. The release hold is ABSOLUTE
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: reconstructed T4 `29120d09891bfc46e80635c2212befa22a0e2604` on FINAL T3 `70601fc201b3c41d2542d82399787b5febcbf03c`
FROM: s4-matrix.planner
TO: s4-matrix.implementer
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: IMPL token for the two-member NSDMI fix and class guard, parented to the confirmed-parsing rev2 approval on operative real-Orchestrator lineage; two scope rows with per-row evidence; rev2's O-1a/O-1b/O-2/O-3/O-4/O-5 bind in full including the exact 17-pair oracle

DISPATCH IMPL

## 1. Scope

SCOPE_DIFF:
- src/core/repo/git_exec.hpp -> in
- tests/test_repo_engine.cpp -> in

SCOPE_DIFF_RESULT: all-in

SCOPE_ROW_EVIDENCE:
- `src/core/repo/git_exec.hpp` — the production path. At the authorized pre-edit head `29120d0` it is 2496 bytes, SHA-256 `ffeacd32f124a5e5ba091be636242a333a0e85d16b3bec5f7542ed7f0194a253`, re-derived at this seat. It carries `GitInvokeOptions` whose `:24 budget_override` and `:25 empty_config_keys` are the two NSDMI-less members; the authorized edit adds `{}` to each and nothing else.
- `tests/test_repo_engine.cpp` — the guard path. At `29120d0` it is 53795 bytes, SHA-256 `72e5e86a0845c8d08caaceeec0fbc2385e24575cf3be27dd3869aa2167a70e74`, re-derived at this seat. It is built by `biv_repo_engine_tests` (`CMakeLists.txt:123-127`) with `-Wall -Wextra -Werror` at `:126`, which is what lets the canary fail; its existing initializer at `:628` is one of the five omitting `empty_config_keys`, so this translation unit is reddened by the unfixed struct and greened by the fix.

Nothing else is in scope. Explicitly out: `classify.cpp`, `capture.cpp`, `eligibility.cpp`,
`restore.cpp` and every other caller; `git.hpp` and `Git::Opts` (R-4.41 at m-1); any other
production byte; `.github/`; the schema; the harness; T4's other files; and the stage-5 report's
contents.

## 2. Lineage, checked at the bytes

```text
parent approval  s4-matrix-t4-nsdmi-fix-plan-review-r2
  plan_review_approved       True     matcher re-validated on a must-be-YES and must-be-NO first
  DISPATCH_ID holders        1        the walk cannot guess
this token's id  s4-matrix-t4-nsdmi-fix-impl        holders 0    fresh
rev2 seal cited by the review, re-derived here:
  blob a1af036fc654bd2be7038e438398fcf38c879688
  SHA-256 8c91caed7d2f06caf8316275011bdd9be161af370d1fc8dccb24a95d803c87c4
```

**The chain does not run through the out-of-role artifact.** rev2 parents to the real
Orchestrator correction `160705`; `154807`/`ad13ef8` remains NON-OPERATIVE, preserved, and is
not a routing edge. I verified its SHA-256 `38cdbe7c43bcb2858ae3c142d075a91748dc7f1b49e8354d61e450d7fbfe974f`
at my seat when rev2 was written. I check this rather than assume it because relay-lint does not
enforce `FROM`/`ROLE` provenance and the single git identity here defeats `git log --author`.

## 3. What is bound

rev2 is the contract and is not restated loosely. The obligations that carry the most weight:

```text
O-1a  CANONICAL RED at untouched 29120d0 under the real -Wall -Wextra -Werror: NONZERO exit and
      the missing-field-initializers diagnostic class.
O-1b  ENUMERATE ALL at identical bytes/compiler/environment with the warning demoted AFTER
      -Werror and every relevant TU compiled to completion: exit ZERO absent another error, and
      the ORACLE is the EXACT 17 file-line-member pairs -- classify :69 :112; capture :36 :89
      :109 :153 :290 :386; eligibility :67 :109 :180; restore :30 (12 budget_override) and
      eligibility :67 :109 :180; restore :30; test :628 (5 empty_config_keys).
      THE TOTAL ALONE IS NOT THE ORACLE: a count can match while the membership is wrong.
      Any missing, extra, duplicate or differently-bound pair STOPS and routes.
      -fmax-errors=0 proves within-TU continuation only, never whole-population build reach.
O-2   Linux focused build AND tests GREEN at the fixed head under Docker --init with the
      chartered nofile lift; residuals classified against the registered R-4.35 four-member
      family; anything outside it STOPS; no whole-suite-green claim.
O-3   macOS T2/T3/T4 interaction set GREEN with counts and exit status.
O-4   guard a real discriminator in C++ predicates: temp NSDMI-less member -> NONZERO build whose
      diagnostic NAMES that member; removal -> build AND test GREEN with git_exec.hpp restored to
      its fixed digest; any other error is not the discriminator and STOPS; confirm at RUN TIME
      that biv_repo_engine_tests carries -Wall -Wextra -Werror.
O-5   no-op across ALL THIRTEEN initializers; exactly TWO changed files vs 29120d0; classify.cpp,
      capture.cpp, eligibility.cpp and restore.cpp byte-identical.
```

Any obligation that fails STOPS the cycle and routes; none may be reconciled into a pass. The
scratch probes run at three seats during planning de-risk this; they discharge nothing.

## 4. State

T4's head changes when this lands, after which it is green on both platforms and Stage-3
panelable on the orchestrator's convening. T1 `00c06d9`, T2 `7688bbd`, T3 `70601fc` FINAL; T4
`29120d0` clean, local, unpublished. R-4.38's binary inventory stays my stage-5 obligation, and
the stage-5 report must also carry the T3 findings (1)/(2)/(4), the R-4.35/R-4.40/R-4.41
disclosures, and the permanent root-mode lineage record-defects including this lane's
out-of-role artifact. Schema F+G-fenced. Merge is not push is not release; the release hold is
ABSOLUTE.

ACTIONS_GIT_REF: none — no edits made at this seat; the candidate branch is unmoved at `29120d0` and the working tree is clean. Read-only verification: `git cat-file -s` and `git show` piped to `shasum` on `src/core/repo/git_exec.hpp` and `tests/test_repo_engine.cpp` at `29120d0`; `git rev-parse`/`git show` to re-derive rev2's blob and SHA-256; `DISPATCH_ID` holder counts for the parent approval and this token's id; a re-validated `plan_review_approved` call on the parent; and the earlier `shasum` of the non-operative `154807` artifact. No merge, push, PR mutation, or remote CI. Docs lane: this relay + its INDEX row ride ONE explicit-path commit.
FINAL_GIT_STATUS_SHORT: this relay and its INDEX row are this seat's only working-tree delta at commit time; `git status --porcelain` over `harness/`, `src/`, `tests/`, `CMakeLists.txt` is empty; the shared checkout carries sibling-authored untracked paths including the preserved non-operative `154807`, unchanged and unclaimed
RELAY_LINT: exact-file WITH freshness immediately before commit; INDEX tail re-read before appending; `--index` diffed against the pre-append blob; `--relay-root` run over the lane before commit, required to name no error against this relay, with a one-variable control confirming the lane error set is identical with and without it; the bare token verified present exactly ONCE outside any fence via `operational_token_text` with the detector validated on a must-be-YES and a must-be-NO; `substantive_actions_ref` and `implementation_work_claimed` both measured FALSE. Commit gated on all of it by logical AND.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/IMPL-PLANNER-T4-NSDMI-GUARD-DISPATCH-20260822-163256.md` → TO `s4-matrix.implementer`
- TOKEN ISSUED, parented to `s4-matrix-t4-nsdmi-fix-plan-review-r2` whose approve I confirmed PARSES (`plan_review_approved` True) with the matcher re-validated on a must-be-YES and a must-be-NO FIRST; parent id holder count 1 so the walk cannot guess, and this token's id `s4-matrix-t4-nsdmi-fix-impl` has 0 holders. rev2's seal re-derived here: blob `a1af036fc654bd2be7038e438398fcf38c879688`, SHA-256 `8c91caed7d2f06caf8316275011bdd9be161af370d1fc8dccb24a95d803c87c4`
- THE CHAIN DOES NOT RUN THROUGH THE OUT-OF-ROLE ARTIFACT: rev2 parents to the real Orchestrator correction `160705`, while `154807`/`ad13ef8` (SHA-256 `38cdbe7c43bcb2858ae3c142d075a91748dc7f1b49e8354d61e450d7fbfe974f`, verified at my seat) stays NON-OPERATIVE, preserved, and is not a routing edge. Checked rather than assumed because relay-lint does NOT enforce `FROM`/`ROLE` provenance and the single git identity here defeats `git log --author`
- SCOPE is exactly TWO rows with per-row evidence: `src/core/repo/git_exec.hpp` at 2496 bytes / `ffeacd32f124a5e5ba091be636242a333a0e85d16b3bec5f7542ed7f0194a253`, carrying the two NSDMI-less members at `:24` and `:25`; and `tests/test_repo_engine.cpp` at 53795 bytes / `72e5e86a0845c8d08caaceeec0fbc2385e24575cf3be27dd3869aa2167a70e74`, built by `biv_repo_engine_tests` with `-Wall -Wextra -Werror` at `CMakeLists.txt:126` which is what lets the canary FAIL, and whose existing `:628` initializer is one of the five omitting `empty_config_keys` so the TU is reddened then greened by the fix. All four caller sources, `git.hpp`/`Git::Opts`, `.github/`, schema, harness and T4's other files are OUT
- rev2's OBLIGATIONS BIND IN FULL: O-1a canonical RED (NONZERO + missing-field class at untouched `29120d0` under the real policy); O-1b enumerate-all with the EXACT 17 file-line-member pairs as ORACLE and THE TOTAL EXPLICITLY NOT THE ORACLE since a count can match while membership is wrong, any missing/extra/duplicate/differently-bound pair STOPPING, and `-fmax-errors=0` proving within-TU continuation only; O-2 Linux green under `--init` + `nofile` with R-4.35 classification and no suite-green claim; O-3 macOS interaction green with counts and exit; O-4 the guard a real discriminator in C++ predicates including RUN-TIME flag confirmation, with the temp arm requiring a NONZERO build NAMING the member and the removal arm requiring build+test GREEN with the header restored; O-5 no-op across ALL THIRTEEN initializers, exactly TWO changed files, four caller sources byte-identical. Any failure STOPS and routes; none may be reconciled into a pass, and the three seats' scratch probes DISCHARGE NOTHING
- STATE: T4's head CHANGES when this lands, after which it is green on both platforms and Stage-3 panelable on the orchestrator's convening; T1 `00c06d9` / T2 `7688bbd` / T3 `70601fc` FINAL; T4 `29120d0` clean, local, unpublished; R-4.38 binary inventory my stage-5 obligation, and the stage-5 report must also carry the T3 findings (1)/(2)/(4), the R-4.35/R-4.40/R-4.41 disclosures and the permanent root-mode lineage record-defects including this lane's out-of-role artifact; schema F+G-fenced; no remote CI, push, PR mutation, merge, publication, deployment or release; release hold ABSOLUTE
