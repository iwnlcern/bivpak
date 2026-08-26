## IMPLEMENTATION TOKEN — veto-7 bounded revision: one commit over `6ba01ef` replacing `bb06d7e`, six IN paths with preimages re-measured at filing, and the bounded predicate sited at `same_endpoint` because the parser cannot carry what the ruling needs

ROLE: Planner
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: s4-matrix-furl1-veto7-revision-impl-token
PARENT_DISPATCH_ID: s4-matrix-furl1-veto7-bounded-revision-plan-review
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-FURL1-VETO7-BOUNDED-REVISION-APPROVE-20260826-032415.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-FURL1-VETO7-BOUNDED-REVISION-FIX-AT-THE-COMPARISON-NOT-THE-NORMALIZATION-20260826-031648.md
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
HUMAN_GATE_REQUIRED: no NEW operator gate — this token spends the plan gate approved at `032415`. It authorizes product/test edits ONLY inside the six scope rows below. It authorizes NO merge claim (a MERGE-GATE relay is required), no push, PR mutation, remote CI, publication, deployment, release, and NO scope widening. Both owner reviews re-engage at the successor bytes, and the T4 FINAL re-weigh at the successor commit returns to the OPERATOR and is never claimed here. Any STOP halts before the next obligation and routes to this seat. The release hold is ABSOLUTE.
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: T4 `6ba01ef92ef5052b317f6210fa202d5577e1e6c1` on FINAL T3 `70601fc201b3c41d2542d82399787b5febcbf03c`
AUTHORIZING_PLAN: `s4-matrix-furl1-veto7-bounded-revision-plan`, commit `06c0258bd60194258c952390555ff8e277fc4a83`, blob `69609cc3cda1d59b7f05ec439df7899d2acc30b8`, SHA-256 `13c2d0679002ac5de16c15ac4675b5273632203df88deab936ff3c126bf43f18`
AUTHORIZING_REVIEW: `.relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-FURL1-VETO7-BOUNDED-REVISION-APPROVE-20260826-032415.md`, commit `f187cfe`, `VERDICT: approve`
FROM: s4-matrix.planner
TO: s4-matrix.implementer
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer, m-1.planner, m-3.planner, m-4.planner
SUBJECT: Bare veto-7 revision token — ONE new commit over `6ba01ef` REPLACING `bb06d7e`, the same six IN paths each with a preimage re-measured at filing, the bounded path predicate sited at the single shared comparison, explicit userinfo presence, an explicit ASCII fold, the additive witnesses, the six-member union whole, and the sealed FX-M-1 legs untouched

I re-derived the gate at my seat before issuing. `plan_review_approved` is True on the approval bytes
and False on a trailing-period control, so the verdict SEPARATES. The plan identity the review cites
re-derives EXACTLY: commit `06c0258bd60194258c952390555ff8e277fc4a83`, blob
`69609cc3cda1d59b7f05ec439df7899d2acc30b8`, SHA-256
`13c2d0679002ac5de16c15ac4675b5273632203df88deab936ff3c126bf43f18`. The approval is in THIS lane's
dispatch root with exactly one holder, and its stamp `032415` is strictly EARLIER than this token's —
both preconditions I measured earlier this cycle are satisfied by construction.

SCOPE_DIFF:
- src/core/repo/git_exec.hpp -> in
- src/core/repo/git_exec.cpp -> in
- src/core/repo/types.hpp -> in
- src/core/repo/eligibility.cpp -> in
- src/core/repo/restore.cpp -> in
- tests/test_repo_engine.cpp -> in
SCOPE_DIFF_RESULT: all-in

SCOPE_ROW_EVIDENCE:
- src/core/repo/git_exec.hpp -> preimage at 6ba01ef 2500 bytes SHA-256 523e13186cb4bc7d9e6eb12b0a64ea0f56c8c6819068b30f3fc54c4052d87f0a
- src/core/repo/git_exec.cpp -> preimage at 6ba01ef 10844 bytes SHA-256 cfd9c69e2396ef7486156f645ad8f5c859181f29b0b0351c767fefa4e96f7cbf; the parsers, `ascii_lower`, `one_trailing_slash`, `same_endpoint`, and the four arms of `url_endpoints_equivalent`
- src/core/repo/types.hpp -> preimage at 6ba01ef 6253 bytes SHA-256 744ba6c694b984a8f88a04828e293900e5a8b7ef6e0bdcc8ab90cc25db180f18
- src/core/repo/eligibility.cpp -> preimage at 6ba01ef 8085 bytes SHA-256 d06af9cb04fea8eeade594481712c99ad24939661009010e0ded015f882a622d
- src/core/repo/restore.cpp -> preimage at 6ba01ef 19919 bytes SHA-256 a3fb265816822427d30795807665574a6341dc934740e9d3d7d4002dcbb6258b
- tests/test_repo_engine.cpp -> preimage at 6ba01ef 54027 bytes SHA-256 1dd44d5ce09b682f97b991b7edcef10eda4688e9ddc07ea4add0b319f5aee98c

## The obligations

**O-1 — the path predicate, sited at the comparison.** Suffixes equate IFF byte-identical, or one is
the other plus exactly ONE trailing `/`. `a` vs `a/` equates; `a/` vs `a//` equates; `a` vs `a//`
and `a` vs `a///` DIVERGE. Carry the suffix VERBATIM out of BOTH parsers and put the predicate in
`same_endpoint`. Do not implement it twice: `same_endpoint` is the single point all four arms of
`url_endpoints_equivalent` funnel through, so one site discharges rule 3 and rule 5's
"path byte-identical after rule 3" clause together. The absent-suffix `"/"` default is a parse
default, not a normalization; leave it.

**O-2 — userinfo presence.** Present-but-empty userinfo is PRESENT; present-vs-absent DIVERGES. Model
presence explicitly rather than through `""`, which is precisely the value that cannot carry the
distinction.

**O-3 — the fold.** Explicit `A`–`Z` ASCII fold, byte-deterministic under any host locale. No
`std::tolower`. Bytes outside `A`–`Z` pass through unchanged.

**O-4 — witnesses ride the fix, additively.** In the comparator table add `a` vs `a//` DIVERGENT, the
`a/` vs `a//` boundary, `a` vs `a///` DIVERGENT, and `://@h` vs `://h` DIVERGENT; plus ONE real-git
multi-slash divergence arm through the gate end to end. `FX-M-1` lives in LOCKED Addendum M, not in
the test file: its fifteen legs and twelve markers are sealed and must not be renumbered, deleted, or
substituted. Additions only.

**O-5 — form.** ONE new commit over `6ba01ef` REPLACING `bb06d7e` per the one-commit rule, inside the
six-path fence and nothing else. The fourteen real-git units stay green, the absence bar stays PASS,
and the twelve named mutants keep mapping to their legs.

**O-6 — the six-member union binds whole:** m-1 vetoes 1–9 with veto 9 mechanical; the complete
`V-A6-1..6`; the SEPARATE R4 zero-m-3-surface absence bar; m-4's triggers; the fourteen-unit reduced
real-git E2 set; and the `repos`-empty format fence with no reachability wiring. None omitted, none
substituted; the two locks' carriers are deliberately ASYMMETRIC and must NOT be reconciled.

**The authority is the sealed bytes.** M rev8 LOCKED `2966b839…` at commit `6aa64fe280c4…`,
POST_STAMP `57d89625…`; A6 rev14 `7ce2251d…`; SR-URL `a2f777c2…`. RE-HASH ALL THREE before your first
edit and STOP on any difference. This token reproduces no golden text. Execution, not amendment: a
disagreement with a sealed byte is a STOP routed to me, never an edit.

Not in scope: any CLI, help, prompt, envelope, schema or exit-map byte; any wiring; `src/cli/**`,
`src/core/report/**`, `schemas/**`, `harness/**`, `test_cli.cpp`, `test_envelope.cpp`,
`src/core/manifest/**`, `src/core/pack/**`, `src/core/open/**`, `.github/**`, any sealed text,
T1/T2/T3 bytes, the stage-5 report. The Linux leg is m-1's at its own seat and this work is NOT
two-platform confirmed until it runs there. No merge claim without a MERGE-GATE relay; merge is not
push and neither is release; the release hold is ABSOLUTE.

DISPATCH IMPL

ACTIONS_GIT_REF: none — no edits made at this seat; no product, test, branch, ref or worktree moved, and the superseded candidate `bb06d7e` is untouched pending its replacement. Read-only at my seat: `plan_review_approved` measured True on the approval bytes with a trailing-period must-be-NO control returning False; re-derivation of the authorizing plan's commit, blob and SHA-256; the approval's dispatch-root, holder count, and stamp-ordering preconditions; and `git cat-file -s` plus `git show | shasum -a 256` preimages for all six IN paths at `6ba01ef`, re-measured at filing rather than inherited from the plan. No merge, push, PR mutation, or remote CI. Docs lane: this relay and its INDEX row ride ONE explicit-path commit.
RELAY_LINT: per D-3.4 (v2.9.x) — clock read immediately before stamping; exact-file arm passes WITH freshness on final bytes; `--index` arm 226 inherited and ZERO introduced with this row unnamed; `--relay-root` arm at the lane dispatch root totals 28 and I attributed it per-relay rather than by headline: ZERO errors name THIS token. The 28th belongs to the authorizing PLAN and is the inherited cross-repo `DESIGN_LOCK_ID` visibility condition already disclosed on that relay. The token carries the same lock id and record kind yet adds nothing, because the PLAN is now itself the earlier same-owner design-doc relay the gate looks for — so the condition is discharged in-lane for this token. I checked this rather than reusing the plan's disclosure sentence: a footer that inherits a prior relay's caveat without re-measuring is exactly the stale-copy defect I was reviewed for earlier this engagement. `operational_token_text` confirms exactly ONE live bare token. No aggregate `.relays/s4` arm is claimed. Commit executed as a SEPARATE step after these gates reported.
FINAL_GIT_STATUS_SHORT: this relay and its INDEX row are this seat's only working-tree delta at commit time; the shared checkout retains sibling-authored untracked artifacts including the immutable `220111` stray, excluded and unclaimed by me.

CARRY LIST (D-8.5):
- this relay -> TO `s4-matrix.implementer`
- BARE VETO-7 REVISION TOKEN ISSUED, parented to the approving PLAN-REVIEW at `032415` commit `f187cfe`. Gate re-derived at my seat, not read: `plan_review_approved` True on the bytes and False on a trailing-period control so it SEPARATES; the plan identity re-derives EXACTLY at commit `06c0258b`, blob `69609cc3`, sha256 `13c2d067`; the approval sits in THIS lane's dispatch root with one holder and its `032415` stamp is strictly EARLIER than this token, so both preconditions I measured earlier this cycle hold by construction
- SIX IN PATHS with preimages RE-MEASURED AT FILING against `6ba01ef` rather than inherited from the plan: `git_exec.hpp` 2500B, `git_exec.cpp` 10844B, `types.hpp` 6253B, `eligibility.cpp` 8085B, `restore.cpp` 19919B, `test_repo_engine.cpp` 54027B; `SCOPE_DIFF_RESULT: all-in`
- O-1 THE PREDICATE IS SITED AT `same_endpoint`, NOT IN THE PARSERS, and that is the whole point: the ruling's rule is about the DIFFERENCE between two suffixes, and a parser-side collapse destroys the slash count before the comparison ever sees it. Carry the suffix VERBATIM out of both parsers; implement the predicate ONCE at the shared comparison, which discharges rule 3 and rule 5's byte-identical-after-rule-3 clause together. Equate iff byte-identical or differing by EXACTLY ONE trailing slash, so `a`/`a/` and `a/`/`a//` equate while `a`/`a//` and `a`/`a///` DIVERGE; the absent-suffix default is a parse default and stays
- O-2 present-but-empty userinfo is PRESENT and present-vs-absent DIVERGES, modelled explicitly and not through `""`. O-3 explicit byte-deterministic `A`-`Z` fold with no `std::tolower`. O-4 witnesses ADDITIVE only — `a` vs `a//`, the `a/` vs `a//` boundary, `a` vs `a///`, `://@h` vs `://h`, plus ONE real-git multi-slash arm through the gate; `FX-M-1` lives in LOCKED Addendum M and its fifteen legs and twelve markers must NOT be renumbered, deleted or substituted
- O-5 ONE new commit over `6ba01ef` REPLACING `bb06d7e`, six-path fence and nothing else, fourteen real-git units still green, absence bar still PASS, twelve mutants still mapping. O-6 the six-member union binds WHOLE and the two lock carriers stay deliberately ASYMMETRIC — do not reconcile
- RE-HASH M rev8 `2966b839…` at commit `6aa64fe280c4…` with POST_STAMP `57d89625…`, A6 rev14 `7ce2251d…`, and SR-URL `a2f777c2…` BEFORE the first edit and STOP on any difference. Execution not amendment: a disagreement with a sealed byte is a STOP routed to me, never an edit
- ZERO ARM-3 ERRORS NAME THIS TOKEN, attributed per-relay rather than read off the headline total: the run totals 28, and the 28th belongs to the authorizing PLAN as its already-disclosed cross-repo `DESIGN_LOCK_ID` condition. This token carries the same lock id and record kind but adds nothing, because the PLAN is now the earlier same-owner design-doc relay the gate seeks. I re-measured instead of reusing the plan's caveat sentence — inheriting a prior relay's disclosure without re-checking is the stale-copy defect I was reviewed for earlier
- AFTER: both owner reviews re-engage at the SUCCESSOR bytes, with m-1 also running the Linux leg AT ITS OWN SEAT under the charter parity recipe — this work is NOT two-platform confirmed until then and I have never run Linux at this seat. Then MERGE-GATE (separate relay, unclaimed), then the operator's T4 FINAL at the successor commit, then R-4.43 on m-4's sign-off. No push, PR mutation, remote CI, publication, deployment or release; release hold ABSOLUTE
