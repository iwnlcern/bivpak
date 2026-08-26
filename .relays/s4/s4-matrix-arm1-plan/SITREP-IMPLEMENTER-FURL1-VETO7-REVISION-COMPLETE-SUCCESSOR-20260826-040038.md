## SITREP — F-URL-1 veto-7 bounded revision complete at successor `6f89818`: comparison-site predicate, explicit userinfo presence, and deterministic ASCII fold

ROLE: Implementer
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-matrix-furl1-veto7-revision-complete
PARENT_DISPATCH_ID: s4-matrix-furl1-veto7-revision-impl-token
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/IMPL-PLANNER-FURL1-VETO7-REVISION-TOKEN-SIX-PATHS-COMPARISON-SITE-BOUNDED-20260826-033431.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-FURL1-VETO7-BOUNDED-REVISION-FIX-AT-THE-COMPARISON-NOT-THE-NORMALIZATION-20260826-031648.md; .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-FURL1-VETO7-BOUNDED-REVISION-APPROVE-20260826-032415.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
DESIGN_DOC_ID: m1-addendum-M-20260823
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m1-addendum-M-2966b839-lock-20260825
LOCKED_DESIGN_SHA256: 2966b839a472df28a261890e1209d69d97a0bfe06c903c3f5029d2cd39a87df6
LOCKED_DESIGN_COMMIT: 6aa64fe280c40beec2c93063de1d38c830aac097
POST_STAMP_SHA256: 57d89625de4b47031cf2862065499ca1839fac7876f42deabe9d048d7de30082
CONSUMED_CONTRACT: m3-addendum-6-c41d015f-lock-20260825 (7ce2251dd481161a457c029bf46e127522f1cc85cc5ab2fb2a92b7fc0c7fd771)
SECOND_CONSUMED_CONTRACT: m4-sr-url-family-20260823 (a2f777c2311ab04283992b24f5fba766c6ba8c66ef8bcf6bc88f7b48f88f7798)
HUMAN_GATE_REQUIRED: no new operator gate at this report-only handoff. Both owner reviews re-engage on the successor bytes; m-1 owns the deferred Linux leg. Merge still requires a separate MERGE-GATE, T4 FINAL returns to the operator alone, and the release hold is ABSOLUTE. No push, PR mutation, remote CI, merge, publication, deployment, or release is authorized or performed here.
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: T4 `6ba01ef92ef5052b317f6210fa202d5577e1e6c1` on FINAL T3 `70601fc201b3c41d2542d82399787b5febcbf03c`
FROM: s4-matrix.implementer
TO: s4-matrix.planner
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer, m-1.planner, m-3.planner, m-4.planner
SUBJECT: Veto-7 bounded revision implemented at successor 6f89818e01b2aa75b066731edee78b93f942f8e7 as exactly one commit over 6ba01ef replacing bb06d7e; suffixes remain verbatim through both parsers and one symmetric exact-or-one-slash predicate lives at same_endpoint, userinfo presence is explicit, ASCII folding is locale-independent, additive witnesses RED then GREEN, fourteen sealed real-Git units stay green, the six-path and absence bars pass, macOS canonical rows pass, and Linux remains deferred to m-1

The token, its approving review, all three sealed authorities, and all six base preimages were
re-derived before the first edit and matched exactly. The revision is landed in the preserved
isolated candidate worktree on branch `s4-matrix/arm1-t4` as:

```text
6f89818e01b2aa75b066731edee78b93f942f8e7
fix(repo): gate rewritten network endpoints
parent 6ba01ef92ef5052b317f6210fa202d5577e1e6c1
```

`git rev-list --count 6ba01ef..HEAD` returns `1`. The successor therefore replaces the superseded
`bb06d7e` candidate without stacking a second implementation commit.

## Bounded implementation

The veto revision itself moves only `src/core/repo/git_exec.cpp` and
`tests/test_repo_engine.cpp`. The whole successor commit remains exactly the authorized six-path
set:

```text
src/core/repo/git_exec.hpp
src/core/repo/git_exec.cpp
src/core/repo/types.hpp
src/core/repo/eligibility.cpp
src/core/repo/restore.cpp
tests/test_repo_engine.cpp
```

Both endpoint parsers now carry suffix bytes verbatim. The absent URL suffix retains its specified
`"/"` parse default. `same_endpoint` is the one shared site for a symmetric predicate that accepts
byte identity or a difference of exactly one trailing slash. Thus `a` and `a/`, and `a/` and
`a//`, equate; `a` and `a//`, and `a` and `a///`, diverge. No parser-side slash collapse remains.

`ParsedEndpoint::user` is now an optional string. URL userinfo introduced by `@` is present even
when empty; absent userinfo remains absent. Absolute scp parsing retains its existing rejection of
an empty user while carrying a valid user explicitly. Optional equality at the shared comparison
therefore separates `https://@example.invalid/repo.git` from
`https://example.invalid/repo.git`.

`ascii_lower` now maps only ASCII `A` through `Z` by explicit byte arithmetic and passes every
other byte unchanged. There is no `std::tolower`. The prior `one_trailing_slash` parser normalizer
is absent.

## Red-green and local verification receipts

Baseline before the additive witnesses was green at 408 assertions in 55 repo-engine cases. The
test-first RED phase separated the defect exactly:

- the comparator case failed three required divergent rows: no slash against two slashes, no
  slash against three slashes, and present-empty userinfo against absent userinfo;
- the new real-Git multi-slash rewrite arm reached the gate and failed because the old comparator
  returned success instead of `url_divergence_refused`;
- the required one-slash against two-slash boundary remained green, showing that the witness did
  not merely demand strict byte identity.

After the production change, both focused cases passed: 19 assertions in the comparator case and
6 assertions in the real-Git multi-slash case. Post-commit verification on the exact successor
then produced:

- full repo-engine: 418 assertions in 56 cases, all green;
- unchanged sealed selection `F-URL-1 real git*`: 56 assertions in exactly 14 cases, all green;
- full macOS build: pass;
- canonical macOS product and harness selection: 6 of 6 rows passed in 675.09 seconds, including
  `biv_tests` in 396.37 seconds and `harness-e2` in 264.33 seconds;
- `clang-format --dry-run --Werror` and `git diff --check`: pass.

A supplemental direct macOS `clang-tidy -p build/ci-macos` call is not claimed as a project gate:
that ad-hoc shape traversed generated Catch2 headers under warnings-as-errors and exited nonzero on
third-party macro diagnostics. The canonical `safety-tidy-analyzer` row on this macOS configure is
a declared skip because an executable named `clang-tidy-22` is absent. The token assigns the
canonical Linux clang-tidy and parity leg to m-1 at its own seat, so no Linux run and no
two-platform-green claim is made here. No remote CI was triggered.

## Scope, absence, and next actors

The committed path-set comparison against `6ba01ef` returns `scope_exact=True`, an empty
outside-scope set, and `ABSENCE_BAR=PASS`. There are zero successor bytes under `src/cli/**`,
`src/core/report/**`, `schemas/**`, `harness/**`, `src/core/manifest/**`, `src/core/pack/**`,
`src/core/open/**`, `.github/**`, `tests/test_cli.cpp`, or `tests/test_envelope.cpp`. The revision
adds tests only; it renumbers or deletes none of the sealed FX-M-1 legs or markers, and all twelve
previously mapped mutants retain their unchanged test legs. The candidate worktree is clean.

Route successor `6f89818e01b2aa75b066731edee78b93f942f8e7` to both owner reviews: m-1 reviews the engine delta
against locked M rev8 and runs the Linux parity leg at its seat; m-3 independently re-verifies the
separate R4 zero-m-3-surface absence bar at the successor. Each retains veto. Only after both pass
may the orchestrator consider the separate MERGE-GATE. This report grants no integration or release
authority.

ACTIONS_GIT_REF: candidate branch `s4-matrix/arm1-t4` replaced superseded candidate `bb06d7ef801c5afa31a91155f45a520db6f4a64a` with sole successor commit `6f89818e01b2aa75b066731edee78b93f942f8e7`, whose parent is exactly base `6ba01ef92ef5052b317f6210fa202d5577e1e6c1` and whose diff is exactly the six authorized paths. Local macOS validation only. No Linux run, remote CI, push, PR mutation, merge, publication, deployment, release, or T4 FINAL act. Docs lane: this report and one EOF INDEX row ride one explicit-path commit; daemon reconciliation/rendering may refresh its owned projections afterward.
FINAL_GIT_STATUS_SHORT: isolated candidate clean at `6f89818e01b2aa75b066731edee78b93f942f8e7`, exactly one commit over `6ba01ef`, six landed paths and no untracked candidate bytes. Shared main retains its pre-existing sibling-authored modified SEATS projection and untracked historical artifacts; they are excluded and unclaimed by this seat.
RELAY_LINT: exact-file freshness, INDEX, and lane-root arms are run on final bytes before the explicit-path docs commit. Because relay-engine cannot natively route this `s4-matrix-*` dispatch into the ruled `s4-matrix-arm1-plan` root, the established in-lane hand-origin reconcile pattern is used and disclosed. Inherited root or INDEX findings are attributed by delta and no whole-root-green claim is made.

CARRY LIST (D-8.5):
- this completion relay -> TO `s4-matrix.planner`
- successor `6f89818e01b2aa75b066731edee78b93f942f8e7`, exactly one commit over `6ba01ef`, replaces `bb06d7e`; exact six-path commit; clean preserved candidate worktree; no remote or integration act
- bounded suffix predicate implemented once at `same_endpoint` after both parsers preserve suffix bytes verbatim; explicit optional userinfo presence; explicit deterministic ASCII `A` through `Z` fold; absent URL suffix default preserved
- TDD receipts: baseline 408 assertions in 55 cases; comparator and real-Git multi-slash witnesses RED on the old bytes for the intended defects; final 418 assertions in 56 cases; unchanged sealed selection 56 assertions in exactly 14 real-Git cases
- macOS full build and canonical six-row selection green in 675.09 seconds; direct ad-hoc tidy shape invalid on generated Catch2 diagnostics and not claimed; canonical Linux parity and tidy leg deferred to m-1; not two-platform confirmed; remote CI not triggered
- exact six-path scope and separate zero-m-3-surface absence bar PASS; additive tests preserve the existing fourteen sealed identities and twelve mutant mappings
- next: m-1 engine-byte review plus Linux leg and m-3 independent successor absence review, each retaining veto; separate MERGE-GATE later; T4 FINAL to operator alone; release hold ABSOLUTE
