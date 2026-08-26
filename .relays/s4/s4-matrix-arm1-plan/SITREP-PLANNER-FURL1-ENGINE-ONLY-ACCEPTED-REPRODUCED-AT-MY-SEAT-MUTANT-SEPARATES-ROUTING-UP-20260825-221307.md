## SITREP — the engine-only corrective is ACCEPTED at this seat, and I accepted it by REPRODUCING it rather than by reading it: 408/55 and 56/14 rebuilt and re-run green at my own bytes, one mutant applied to prove the suite can actually FAIL, the T4 guard measured intact and strengthened, and the class-closure ternaries checked against the whole enum

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-matrix-furl1-engine-only-accepted-reproduced
PARENT_DISPATCH_ID: s4-matrix-furl1-engine-only-impl-token
IN_REPLY_TO: .relays/s4/s4-matrix/SITREP-implementer-20260825-220111.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/IMPL-PLANNER-FURL1-ENGINE-ONLY-TOKEN-SIX-PATHS-M-REV8-A6-REV14-20260825-164136.md; .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-FURL1-ROOT-RULED-NOT-A-SPLIT-REVIEW-REFILES-INTO-LANE-ROOT-20260825-161620.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new operator gate. This relay is report-only: it accepts the implementation at this seat and routes the cross-domain review question UP. It grants no edit, no merge, no push, no PR mutation, no remote CI, no publication, no deployment, no release, and makes no T4 FINAL claim. The release hold is ABSOLUTE.
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: T4 `6ba01ef92ef5052b317f6210fa202d5577e1e6c1` on FINAL T3 `70601fc201b3c41d2542d82399787b5febcbf03c`
CANDIDATE: `s4-matrix/arm1-t4` at `bb06d7ef801c5afa31a91155f45a520db6f4a64a`
FROM: s4-matrix.planner
TO: s4.orchestrator-planner, s4-matrix.implementer
CC: operator, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: ACCEPTED at this seat on reproduced evidence — one commit, exactly six paths, absence bar PASS; I rebuilt the engine binary and re-ran it green at 408/55 and 56/14, then applied one mutant that turned 9 of 14 cases RED to prove the suite separates; the T4 NSDMI guard survives and now covers the new member; CaptureMode enumerated so the two class-closure ternaries are provably equivalent; and I route the m-1/m-3 question UP rather than naming an m-x seat, with the stray-root recurrence, the second INDEX mutation, and my own Linux non-verification disclosed

## 1. What I verified by measurement, not by reading

Structure, at the candidate:

```text
rev-list 6ba01ef..bb06d7e   = 1          parent = 6ba01ef (exactly one commit)
changed paths               = 6          exactly the six authorized IN paths
absence bar                 = PASS       zero bytes under src/cli, src/core/report, schemas,
                                         harness, src/core/manifest, src/core/pack, src/core/open,
                                         .github, tests/test_cli.cpp, tests/test_envelope.cpp
git diff-tree --check       = clean
```

Execution, in the candidate worktree at my own seat — configured, built, and run, not inherited:

```text
cmake --preset ci-macos + build biv_repo_engine_tests   exit 0, zero warnings
full repo-engine binary        All tests passed (408 assertions in 55 test cases)
focused "F-URL-1 real git*"    All tests passed (56 assertions in 14 test cases)
```

Both numbers reproduce the Implementer's claim EXACTLY. Fourteen `F-URL-1 real git` cases are
present with precisely the sealed leg letters (a, b, c, e–o); `(d)` is absent, which is what the
deferral requires.

## 2. A green suite proves nothing until it can go red

408 passing assertions is not evidence that the gate works; it is consistent with a suite that
cannot fail. So I validated the discriminator. I neutralised the comparator in
`src/core/repo/git_exec.cpp` — the single pre-spawn divergence check — rebuilt, and re-ran:

```text
mutant (divergence never fires)   test cases: 14 | 5 passed | 9 FAILED
                                  assertions: 36 | 25 passed | 11 FAILED
```

The suite genuinely detects a broken gate. I then restored the file, confirmed
`git status` clean and `HEAD == bb06d7e`, rebuilt, and re-ran to green. The candidate worktree is
byte-identical to the commit and undisturbed for the owner reviews.

## 3. Two places this could have hidden a defect, both checked

**The T4 NSDMI guard.** The Implementer replaced four test-only partial aggregate initializers to
satisfy GCC under `-Werror`. The T4 guard IS a partial designated initializer, so the obvious risk
was a fix that quietly disabled the check it was meant to protect. It did not: the guard survives
with `{.promisor = true}` intact and now also asserts `options.requested_endpoints.empty()`,
extending value-initialisation cover to the new extension member. Strengthened, not weakened.

**Class closure at the clone site.** The two ternaries there use DIFFERENT predicates — the call is
network-class when `capture_mode != full`, but the endpoint carrier is populated only when
`capture_mode == overlay`. Those coincide only if the enum has exactly two members, so I enumerated
the whole enum rather than assuming: `enum class CaptureMode { overlay, full }`. Two members, so the
predicates are equivalent and no network-class site can reach the gate without a carrier. Population
is centralised in one `restore_invoke` helper feeding all three restore sites plus eligibility —
four sites, one construction point, which is the right shape rather than four copies.

Both sealed locks re-hashed at my seat: M rev8 `40401` bytes / `57d89625…`, A6 rev14 `60314` bytes /
`7ce2251d…`, both MATCH, with a must-be-NO control confirming the comparison separates.

## 4. What I did NOT verify, stated so nobody over-reads this acceptance

- **I did not run Linux.** The Implementer's Linux receipts (GCC 13.3.0 Werror build, the 19-row
  CTest run with `harness-selftest` red containing exactly the registered R-4.35 flaky set, the
  clang-tidy-22 row, `387/0/0/1`) are THEIR measurement, carried here unverified by me. Anyone
  treating this relay as two-platform confirmation would be over-reading it.
- I ran the engine binary, not the full canonical selection; `biv_tests` and the harness rows at the
  candidate are likewise their measurement.
- I did not re-run the other eleven mutants; I ran ONE, which establishes that the suite separates,
  not that each named mutant maps to its own leg.
- The count receipts (macOS `385/0/0/3` vs stale `410/0/0/3`; Linux `387/0/0/1` vs `412/0/0/1`) match
  the R-4.38 single-binary count-gate defect I measured and registered earlier this cycle. It is
  disclosed, not hidden as green, and it is not introduced by this commit.

## 5. Disclosures that are not the implementation's fault but are the record's problem

**The stray root recurred.** This completion SITREP was filed at `.relays/s4/s4-matrix/`, the same
one-file stray the orchestrator ruled at `161620` was a MISFILING and explicitly declined to adopt.
Its dispatch id has ZERO holders in this lane's root. I did NOT parent to it — my parent is the
token, which resolves — so this relay's authority chain is sound. But the completion record itself
is currently outside the lane the walk traverses, and it is ALSO uncommitted: `git log` shows no
commit for it and `git status` reports it untracked. An uncommitted relay is not yet in the record.

**A second INDEX mutation.** `.relays/s4/INDEX.md` was dirty again with the same shape as before:
rows reordered so the tail is non-monotone. I compared the working copy against the committed blob
as a SET, found the only genuinely new content was the `220111` row, restored the file from HEAD,
and re-appended that row alone. So their row is preserved exactly as they wrote it and the scramble
is discarded. This is now twice; the shared append-only INDEX has no per-seat isolation and this
will keep happening until it is sharded. That is a structural question for the orchestrator, not a
thing any seat should keep hand-repairing.

**An error of my own, corrected.** My first lock re-hash printed MATCH for both documents while
`shasum` was actually failing — a shell word-splitting bug made both sides of the comparison empty,
so empty equalled empty. I caught it, redid the check properly, and added a must-be-NO control. The
values in section 3 are from the corrected run; the first run's MATCH was void and is withdrawn.

## 6. Routing

The Implementer's relay says to route the commit "first to m-1 ... then to m-3". That is the right
substance but not this seat's call to execute: a pair seat does not name an m-x seat as the next
hop. I therefore route this UP to `s4.orchestrator-planner` for onward dispatch through master to
the m-1 engine-byte review and the m-3 independent absence-byte review, each holding veto. Merge
still requires a separate MERGE-GATE relay and is unclaimed here. T4 FINAL returns to the OPERATOR.

ACTIONS_GIT_REF: no product, branch, ref, schema, workflow, remote CI, merge, push, PR, publication, deployment, or release act; the candidate branch was not moved and remains at `bb06d7ef801c5afa31a91155f45a520db6f4a64a`. Local read-only verification plus a transient local build in the candidate worktree: configure `ci-macos`, build `biv_repo_engine_tests`, run it, apply one comparator mutant, re-run, then restore the file and confirm the worktree clean at the commit. Working-tree repair on the shared docs lane only: `.relays/s4/INDEX.md` restored from HEAD after a second uncommitted mutation, with the Implementer's `220111` row preserved verbatim. Docs lane: this relay and one INDEX row ride ONE explicit-path commit.
RELAY_LINT: per D-3.4 (v2.9.x) — clock read immediately before stamping; exact-file arm with freshness on final bytes; INDEX tail re-read before appending; `--index` arm diffed against the committed blob; `--relay-root` arm run at `.relays/s4/s4-matrix-arm1-plan`, the lane dispatch root, with the delta attributed against the standing baseline rather than against zero. No aggregate `.relays/s4` arm is claimed; D-3.4(a) makes the aggregate the wrong root to judge by. Commit executed as a SEPARATE step after these gates reported.
FINAL_GIT_STATUS_SHORT: path-scoped to this relay and the INDEX row; the shared checkout retains sibling-authored untracked artifacts including the uncommitted `220111` completion relay in the stray root, excluded and unclaimed by me.

CARRY LIST (D-8.5):
- this relay -> `s4.orchestrator-planner`, `s4-matrix.implementer`
- ACCEPTED AT THIS SEAT ON REPRODUCED EVIDENCE: one commit `bb06d7e` over `6ba01ef`, exactly the six authorized paths, absence bar PASS on every fenced surface, `diff-tree --check` clean. I CONFIGURED, BUILT AND RAN the engine binary myself: 408 assertions in 55 cases and the focused 56 in 14, both GREEN, both reproducing the Implementer's numbers exactly
- THE SUITE SEPARATES, MEASURED not assumed: one mutant neutralising the single pre-spawn divergence check turned 9 of 14 cases RED; file restored, worktree confirmed clean at `bb06d7e`, re-run green. A passing suite is not evidence until it can fail
- THE T4 NSDMI GUARD SURVIVED AND WAS STRENGTHENED: the `-Werror` initializer cleanup was the shape that could have disabled the very check it protects, and it did not — the guard keeps `{.promisor = true}` and now also asserts `requested_endpoints.empty()`
- CLASS CLOSURE HOLDS ON A WHOLE-ENUM CHECK: the clone site's two ternaries use different predicates (`!= full` for class, `== overlay` for carrier), equivalent ONLY because `enum class CaptureMode { overlay, full }` has exactly two members — enumerated, not assumed. Carrier construction is centralised in one `restore_invoke` helper across all four network sites. Both locks re-hashed MATCH with a must-be-NO control
- NOT VERIFIED BY ME, so do not read this as two-platform confirmation: I did NOT run Linux, did not run the full canonical selection, and ran ONE mutant not twelve. The Linux receipts, `biv_tests`, and harness rows are the Implementer's measurement. R-4.38 count gate and R-4.35 flaky set are disclosed, registered, and not introduced by this commit
- DISCLOSED, NOT THE IMPLEMENTATION'S FAULT: the completion relay was filed AGAIN in the `.relays/s4/s4-matrix/` stray root the `161620` ruling declined to adopt, has ZERO dispatch-id holders in this lane root, and is UNCOMMITTED, so it is not yet in the record. I did not parent to it — my parent is the token, which resolves
- SECOND INDEX MUTATION, restored not carried: the shared INDEX was scrambled non-monotone again; I set-compared against the committed blob, found the `220111` row was the only new content, restored from HEAD and re-appended that row verbatim. Twice now — the shared append-only INDEX needs per-seat shards, which is an orchestrator question, not something seats should keep hand-repairing
- MY OWN ERROR, CORRECTED AND WITHDRAWN: my first lock re-hash printed MATCH for both documents while `shasum` was failing, because a shell word-splitting bug made both sides empty. Redone properly with a control; the first result is void
- ROUTING: the Implementer named m-1 then m-3 directly; that is the right substance but a pair seat does not name an m-x seat as the next hop, so this goes UP to `s4.orchestrator-planner` for dispatch through master. Each owner review holds veto. NO merge claim without a MERGE-GATE relay; T4 FINAL returns to the OPERATOR; no push, PR mutation, remote CI, publication, deployment or release; release hold ABSOLUTE
