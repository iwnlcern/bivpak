## PLAN-REVIEW — APPROVE the F-URL-1 veto-7 bounded revision plan

ROLE: Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: approve
DISPATCH_ID: s4-matrix-furl1-veto7-bounded-revision-plan-review
PARENT_DISPATCH_ID: s4-matrix-furl1-veto7-bounded-revision-plan
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-FURL1-VETO7-BOUNDED-REVISION-FIX-AT-THE-COMPARISON-NOT-THE-NORMALIZATION-20260826-031648.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-FURL1-SPLIT-VERDICT-M3-PASS-M1-VETO7-BOUNDED-REVISION-ROUTED-DOWN-20260826-030829.md; ../../../../pdc/master/relays/s4-wave-a-furl1-engine-only-accepted-route-owner-reviews-up/DESIGN-REVIEW-planner-20260826-024819.md
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
HUMAN_GATE_REQUIRED: no new operator gate at PLAN-REVIEW. Approval closes this pair review only; implementation still requires the Planner's later fresh bare implementation token addressed to this Implementer. Both owner reviews, the MERGE-GATE, the operator's T4 FINAL re-weigh, and m-4's R-4.43 sign-off remain later gates. No merge, push, PR mutation, remote CI, publication, deployment, or release is authorized. The release hold is ABSOLUTE.
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: T4 `6ba01ef92ef5052b317f6210fa202d5577e1e6c1` on FINAL T3 `70601fc201b3c41d2542d82399787b5febcbf03c`
REVIEWED_PLAN: commit `06c0258bd60194258c952390555ff8e277fc4a83`, blob `69609cc3cda1d59b7f05ec439df7899d2acc30b8`, SHA-256 `13c2d0679002ac5de16c15ac4675b5273632203df88deab936ff3c126bf43f18`
FROM: s4-matrix.implementer
TO: s4-matrix.planner
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer, m-1.planner, m-3.planner, m-4.planner
SUBJECT: APPROVE the exact veto-7 bounded revision plan — the F1 difference predicate must live at the shared comparison after verbatim suffix parsing, F2 needs explicit userinfo presence, F3 needs explicit ASCII folding, the additive comparator and real-Git witnesses are executable above the unchanged FX-M-1 floor, and the one-commit/six-path/owner-review/authority fences remain whole

## Verdict

**APPROVE.** The exact plan at commit `06c0258bd60194258c952390555ff8e277fc4a83`,
blob `69609cc3cda1d59b7f05ec439df7899d2acc30b8`, SHA-256
`13c2d0679002ac5de16c15ac4675b5273632203df88deab936ff3c126bf43f18`
is technically coherent, correctly bounded to m-1 section 4, and implementable within the
existing six-path fence. This approval grants no implementation authority.

## Independent technical review

- **F1 belongs at comparison.** At `bb06d7e`, both parsers call `one_trailing_slash`
  before `same_endpoint`; the unbounded strip-and-readd destroys the exact suffix difference.
  Preserving each parsed suffix verbatim and applying one symmetric predicate in
  `same_endpoint` is necessary to distinguish `a` versus `a//` while retaining
  `a` versus `a/` and `a/` versus `a//`. The same shared predicate naturally covers
  URL/URL and both absolute-scp/URL directions, satisfying rules 3 and 5 without duplicated logic.
  The parser's absent-suffix default `"/"` remains a default and need not be changed.
- **F2 requires presence, not a sentinel string.** The current plain `std::string user`
  maps both absent userinfo and present-empty `@host` to `""`. An optional value or explicit
  presence bit retains that distinction. Existing absolute-scp parsing already rejects an empty
  user before `@`; its valid non-empty and absent cases map cleanly into the same model.
- **F3 is deterministic as planned.** Folding only bytes `'A'` through `'Z'` and passing
  every other byte unchanged exactly implements ASCII case folding without locale state.
- **The witnesses are executable.** The comparator table already separates equivalent and divergent
  pairs. The real-Git harness already configures a repo-local `url.<effective>.insteadOf` and
  drives `invoke_git` through `real_network_probe`; m-1 used that same seam to demonstrate the
  multi-slash false silence. The four proposed boundary rows plus one real-Git divergence arm are
  additive and do not alter the fourteen retained top-level leg identities.
- **The sealed floor is located and preserved.** `FX-M-1` lives in locked Addendum M, not as a
  literal in `tests/test_repo_engine.cpp`. At the corrected pin it states fifteen legs and twelve
  named-mutant markers. The plan adds veto-7 regression witnesses above that floor; it does not
  renumber, delete, or substitute any sealed leg or marker.
- **Form and scope remain exact.** The successor is one new commit directly over
  `6ba01ef92ef5052b317f6210fa202d5577e1e6c1`, replacing `bb06d7e`. The existing six-path
  implementation is retained, with the revision expected only in `git_exec.cpp` and
  `test_repo_engine.cpp`; every excluded m-3/product surface stays byte-identical to base.

## Authority and lock evidence

The corrected M rev8 commit `6aa64fe280c40beec2c93063de1d38c830aac097` resolves as a
commit with the rev8 subject. Its Addendum M blob is 38,365 bytes and hashes to locked
`2966b839a472df28a261890e1209d69d97a0bfe06c903c3f5029d2cd39a87df6`.
The live post-stamp M file is 40,401 bytes and hashes to `57d89625de4b47031cf2862065499ca1839fac7876f42deabe9d048d7de30082`.
A6 rev14 is 60,314 bytes / `7ce2251dd481161a457c029bf46e127522f1cc85cc5ab2fb2a92b7fc0c7fd771`;
SR-URL is 10,249 bytes / `a2f777c2311ab04283992b24f5fba766c6ba8c66ef8bcf6bc88f7b48f88f7798`.
The superseded `6aa64fe0894e5aa2b9e29b4df33c72cf99c81ecb` does not resolve, while the
corrected pin does; the control separates.

## Next act and holds

The next actor is `s4-matrix.planner`. It may issue one fresh bare implementation token
parented exactly to `s4-matrix-furl1-veto7-bounded-revision-plan-review`, addressed exactly
to `s4-matrix.implementer`, preserving the bounded F1-F3 revision, additive witnesses,
one-commit replacement, six-path fence, complete six-member union, and every later owner gate.
Until those exact bytes arrive, the candidate remains untouched at `bb06d7e`.

ACTIONS_GIT_REF: review-only evidence and docs-lane filing; no product, test, candidate branch, schema, workflow, Docker, remote CI, merge, push, PR, publication, deployment, release, or T4 FINAL act. Read-only review covered the exact plan commit/blob/SHA-256, candidate comparator and test seams, the corrected and invalid Git pins, locked/live M hashes, A6 and SR-URL hashes, FX-M-1 counts, six-path fence, and authority sequence. Docs lane: this fresh in-lane review and one EOF INDEX row ride one explicit-path commit; the immutable stray completion and foreign INDEX/SEATS effects remain untouched.
RELAY_LINT: exact-file v2.9.2 lint passes on final bytes; lane-root lint is measured against the pre-file 28-error baseline and no whole-root-green claim is made. The active engine cannot natively route an `s4-matrix-*` dispatch into the ruled `s4-matrix-arm1-plan` root, so the established in-lane hand-origin reconcile pattern is used and disclosed.
FINAL_GIT_STATUS_SHORT: path-scoped to this review and its one INDEX row at commit time; the shared checkout retains sibling-authored modified projections and untracked history, excluded and unclaimed. Candidate remains clean at `bb06d7ef801c5afa31a91155f45a520db6f4a64a`.

CARRY LIST (D-8.5):
- this PLAN-REVIEW -> `s4-matrix.planner`
- VERDICT APPROVE exact plan commit `06c0258bd60194258c952390555ff8e277fc4a83`, blob `69609cc3cda1d59b7f05ec439df7899d2acc30b8`, SHA-256 `13c2d0679002ac5de16c15ac4675b5273632203df88deab936ff3c126bf43f18`
- F1 comparison-site shape correct: verbatim parsed suffixes plus one symmetric exactly-one-trailing-slash predicate at `same_endpoint`; F2 explicit present-empty userinfo; F3 byte-deterministic ASCII A-Z fold
- additive comparator boundaries plus one real-Git multi-slash gate arm are executable; locked FX-M-1 remains fifteen legs/twelve markers and nothing renumbers
- successor form remains one new commit directly over `6ba01ef` replacing `bb06d7e`, inside the same six-path fence; complete six-member union and absence bar remain binding
- next: Planner's separate fresh bare token; afterward both owner reviews re-engage at the successor, m-1 also owns the Linux parity leg, then separate MERGE-GATE, operator T4 FINAL, and m-4 R-4.43 sign-off; release hold ABSOLUTE
