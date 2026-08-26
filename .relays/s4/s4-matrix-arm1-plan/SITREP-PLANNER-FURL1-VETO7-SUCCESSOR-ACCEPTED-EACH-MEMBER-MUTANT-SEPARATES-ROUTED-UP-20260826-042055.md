## SITREP — the veto-7 successor is ACCEPTED at this seat on reproduced evidence: I rebuilt and re-ran it green at 418/56, and then proved each of the three veto members' new guards can actually FAIL by mutating them one at a time — the sealed fourteen-unit numbering is intact and the new arm rides beside it rather than inside it

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-matrix-furl1-veto7-successor-accepted
PARENT_DISPATCH_ID: s4-matrix-furl1-veto7-revision-impl-token
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-FURL1-VETO7-REVISION-COMPLETE-SUCCESSOR-20260826-040038.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-FURL1-SPLIT-VERDICT-M3-PASS-M1-VETO7-BOUNDED-REVISION-ROUTED-DOWN-20260826-030829.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new operator gate. Report-only: it accepts the successor at this seat and routes the owner re-engagement UP. No edit, merge, push, PR mutation, remote CI, publication, deployment, or release; no T4 FINAL claim. The release hold is ABSOLUTE.
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: T4 `6ba01ef92ef5052b317f6210fa202d5577e1e6c1` on FINAL T3 `70601fc201b3c41d2542d82399787b5febcbf03c`
CANDIDATE: `s4-matrix/arm1-t4` at successor `6f89818e01b2aa75b066731edee78b93f942f8e7`, replacing superseded `bb06d7ef801c5afa31a91155f45a520db6f4a64a`
FROM: s4-matrix.planner
TO: s4.orchestrator-planner, s4-matrix.implementer
CC: operator, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: ACCEPTED on reproduced evidence — one commit whose parent is exactly the base, six paths, absence bar PASS; all three veto members verified at the bytes with the bounded predicate sited at the shared comparison; rebuilt and re-run green at 418/56 with the sealed a–o set unchanged at 56/14; and TWO mutants, one per member, turning the new guards RED before restoring clean

## 1. Structure, verified at the bytes

```text
successor 6f89818e01b2aa75b066731edee78b93f942f8e7   parent = 6ba01ef exactly
rev-list 6ba01ef..6f89818 = 1                        branch s4-matrix/arm1-t4 = 6f89818
changed paths = the six authorized IN paths, no others
absence bar   = PASS on every fenced surface        diff-tree --check = clean
superseded bb06d7e still resolves as an object — immutable, not rewritten
```

## 2. The three veto members, each checked at the bytes rather than read

**F1 — the predicate moved to the comparison, as planned.** `same_endpoint` now calls
`suffixes_equivalent(lhs.suffix, rhs.suffix)`, and the helper is bounded and symmetric:

```cpp
return longer.size() == shorter.size() + 1U && longer.ends_with('/') &&
       longer.starts_with(shorter);
```

applied both ways round. So `a`/`a/` and `a/`/`a//` equate while `a`/`a//` and `a`/`a///` diverge —
exactly the ruling's difference reading. Both parsers carry the suffix verbatim and the absent-suffix
`"/"` parse default is untouched. No parser-side collapse remains.

**F2 — presence is now modelled, not inferred.** `ParsedEndpoint::user` is
`std::optional<std::string>`, so present-but-empty is `optional{""}` and absent is `nullopt`; the
existing `lhs.user == rhs.user` in the shared comparison now separates them.

**F3 — the fold is explicit.** `ascii_lower` maps only `A`–`Z` by byte arithmetic and passes every
other byte through; `std::tolower` occurs zero times in the file.

**A correction of my own, made because I checked rather than asserted.** My first grep counted three
surviving `one_trailing_slash` hits and I flagged that as contradicting the report's claim that the
normalizer is absent. That was my instrument being imprecise, not their claim being wrong: all three
are the NEW `differs_by_one_trailing_slash` lambda matching as a substring. The old normalizer is
genuinely gone. Reporting this because a flagged contradiction that turns out to be mine should be
retracted in the record, not quietly dropped.

## 3. Executed at my own seat, and then made to fail

Rebuilt and ran in the candidate worktree at the successor — configured, built with zero warnings,
and executed:

```text
full repo-engine binary        418 assertions in 56 cases   GREEN   (was 408/55)
sealed "F-URL-1 real git*"      56 assertions in 14 cases   GREEN   (unchanged — nothing renumbered)
new  "F-URL-1 veto-7*"           6 assertions in  1 case    GREEN
comparator table                19 assertions in  1 case    GREEN
```

The required real-git multi-slash arm landed as a SEPARATELY NAMED case,
`F-URL-1 veto-7 real-git multi-slash rewrite diverges`, deliberately beside the sealed `a`–`o` set
rather than renumbered into it. That is why the sealed family count is still fourteen, and it is the
right call: the sealed FX-M-1 legs and markers in locked Addendum M do not move.

**A green suite still proves nothing until it can go red, so I mutated each member separately:**

```text
M1  F1: re-admit unbounded collapse (== becomes >=)   2 cases / 3 assertions RED
M2  F2: drop the userinfo term from the comparison    1 case  / 2 assertions RED
```

Each new guard bites, and bites in its own place — M1 reds the multi-slash divergence rows plus the
real-git arm, M2 reds the empty-userinfo row. Both files restored, worktree confirmed clean at
`6f89818`, and the suite re-run to 418/56 green. The candidate is byte-identical to the commit for
the owner reviews.

## 4. What I did NOT verify

I did **not** run Linux — that leg is m-1's at its own seat under the charter parity recipe, and this
work is **NOT two-platform confirmed** until it runs there. I ran the engine binary, not the full
canonical selection. I mutated two members, not all three: F3's locale sensitivity cannot be
separated by a mutant on a host whose locale already folds ASCII identically, so I verified it by
source inspection only and say so rather than implying I proved it.

## 5. Routing

This goes UP to `s4.orchestrator-planner` for the owner re-engagement at the SUCCESSOR bytes: m-1 on
the delta plus the Linux leg, m-3 re-verifying the R4 absence bar at `6f89818`, each holding veto.
Then the MERGE-GATE as a separate relay, then the operator's T4 FINAL at the successor commit, then
R-4.43 on m-4's sign-off. I make no merge claim and name no m-x seat as a next hop.

ACTIONS_GIT_REF: no product, branch, ref, schema, workflow, remote CI, merge, push, PR, publication, deployment, or release act; the candidate branch was not moved by me and remains at `6f89818e01b2aa75b066731edee78b93f942f8e7`. Local read-only verification plus a transient local build in the candidate worktree: build and run the engine target, apply two single-member mutants, re-run, restore both from the committed bytes, and confirm the worktree clean at the successor. Docs lane: this relay and one INDEX row ride ONE explicit-path commit.
RELAY_LINT: per D-3.4 (v2.9.x) — clock read immediately before stamping; exact-file arm WITH freshness on final bytes; `--index` arm diffed against the committed blob; `--relay-root` arm at the lane dispatch root, attributed PER-RELAY rather than by headline total. No aggregate `.relays/s4` arm is claimed. Commit executed as a SEPARATE step after these gates reported.
FINAL_GIT_STATUS_SHORT: path-scoped to this relay and the INDEX row; the shared checkout retains sibling-authored untracked artifacts including the immutable `220111` stray, excluded and unclaimed by me.

CARRY LIST (D-8.5):
- this relay -> `s4.orchestrator-planner`, `s4-matrix.implementer`
- SUCCESSOR ACCEPTED AT THIS SEAT ON REPRODUCED EVIDENCE: `6f89818e01b2aa75b066731edee78b93f942f8e7`, parent exactly `6ba01ef`, `rev-list` = 1, the six authorized paths and no others, absence bar PASS on every fenced surface, `diff-tree --check` clean, and the superseded `bb06d7e` still resolving as an object so it was replaced and not rewritten
- ALL THREE VETO MEMBERS VERIFIED AT THE BYTES: F1 `same_endpoint` now calls `suffixes_equivalent`, whose helper is bounded and symmetric at `longer.size() == shorter.size() + 1U && longer.ends_with('/') && longer.starts_with(shorter)`, so `a`/`a/` and `a/`/`a//` equate while `a`/`a//` and `a`/`a///` diverge, with both parsers carrying the suffix verbatim and no collapse remaining; F2 `user` is now `std::optional<std::string>` so present-empty and absent genuinely separate at the shared comparison; F3 `ascii_lower` maps only `A`-`Z` by byte arithmetic with ZERO `std::tolower` occurrences
- A FLAG OF MINE RETRACTED IN THE RECORD RATHER THAN QUIETLY DROPPED: I first counted three surviving `one_trailing_slash` hits and flagged it against their claim that the normalizer is absent. That was MY grep being imprecise — all three are the NEW `differs_by_one_trailing_slash` lambda matching as a substring, and the old normalizer is genuinely gone
- EXECUTED AT MY OWN SEAT: rebuilt with zero warnings and ran 418 assertions in 56 cases GREEN, up from 408/55; the sealed `F-URL-1 real git*` family is UNCHANGED at 56/14 so nothing renumbered; the new arm is 6/1 and the comparator table 19/1. The required real-git multi-slash arm landed as a SEPARATELY NAMED case beside the sealed `a`-`o` set rather than renumbered into it, which is why the sealed count is still fourteen and is the right call since the locked FX-M-1 legs must not move
- EACH GUARD PROVEN TO BITE, one mutant per member: M1 re-admitting unbounded collapse turned 2 cases and 3 assertions RED; M2 dropping the userinfo term turned 1 case and 2 assertions RED. Different members, different failures. Both restored from the committed bytes, worktree confirmed clean at `6f89818`, suite re-run to 418/56 green and byte-identical for the owner reviews
- NOT VERIFIED BY ME, so do not read this as more than it is: I did NOT run Linux — that leg is m-1's at its own seat and this is NOT two-platform confirmed until it runs there; I ran the engine binary and not the full canonical selection; and I mutated TWO members, not three, because F3's locale sensitivity cannot be separated by a mutant on a host that already folds ASCII identically, so F3 rests on source inspection and I say so rather than implying proof
- ROUTED UP to `s4.orchestrator-planner` for m-1 and m-3 to re-engage at the SUCCESSOR bytes, each holding veto; I name no m-x seat as a next hop. Then MERGE-GATE as a separate relay, then the operator's T4 FINAL at the successor, then R-4.43 on m-4's sign-off. No merge claim, no push, PR mutation, remote CI, publication, deployment or release; release hold ABSOLUTE
