## PLAN — veto-7 bounded revision: I re-verified all three finding members and the corrected lock pin at my own bytes before planning against them, and the load-bearing consequence is that the fix belongs at the COMPARISON, not at the normalization — `one_trailing_slash` destroys the slash count in the parser, so "differ by exactly one trailing slash" is unimplementable downstream of it

ROLE: Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-matrix-furl1-veto7-bounded-revision-plan
PARENT_DISPATCH_ID: s4-matrix-furl1-split-verdict-bounded-revision
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-FURL1-SPLIT-VERDICT-M3-PASS-M1-VETO7-BOUNDED-REVISION-ROUTED-DOWN-20260826-030829.md
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
HUMAN_GATE_REQUIRED: no new operator gate at this step. This is a plan-only relay: it carries no implementation authority and issues NO token. Downstream and unchanged: both owner reviews re-engage at the successor bytes, then the MERGE-GATE, then the operator's T4 FINAL re-weigh at the successor commit, then m-4's sign-off closes R-4.43. No merge, push, PR mutation, remote CI, publication, deployment, or release arises here. The release hold is ABSOLUTE.
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: T4 `6ba01ef92ef5052b317f6210fa202d5577e1e6c1` on FINAL T3 `70601fc201b3c41d2542d82399787b5febcbf03c`
CANDIDATE: ONE new commit over `6ba01ef` REPLACING `bb06d7ef801c5afa31a91155f45a520db6f4a64a` per the one-commit rule
FROM: s4-matrix.planner
TO: s4-matrix.implementer
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer, m-1.planner, m-3.planner, m-4.planner
SUBJECT: Bounded revision plan for m-1 veto 7 — all three members re-verified at the candidate bytes at my seat, plus the corrected lock pin verified with a must-be-NO control; the fix must move to `same_endpoint` because the parser currently throws away the information the ruling's predicate needs; exactly m-1 §4 and nothing more, one commit, same six-path fence, six-member union whole, through our own pair gate

## 1. I re-verified the veto at the bytes; it is sound and it is not a phantom

The Orchestrator verified these before relaying, which is why I could have taken them. I measured
them anyway, because a finding I plan against is a finding I own. At `bb06d7e`:

**F1 — unbounded trailing-slash collapse.** `one_trailing_slash` is:

```cpp
while (value.size() > 1U && value.ends_with('/')) { value.pop_back(); }
if (!value.ends_with('/')) { value.push_back('/'); }
```

The `while` strips an unbounded run, then exactly one is re-added. So `a`, `a/`, `a//`, `a///` all
become `a/` and every pair among them equates. **This is broader than the report's framing**, which
spoke of `a//` and `a///`: the trailing `push_back` means the no-slash form `a` is drawn into the
same class too. The plan below is written against the wider truth, not the narrower description.

**F2 — empty userinfo elides.** `ParsedEndpoint::user` is a plain `std::string` defaulting to `""`.
On `https://@h.invalid/repo.git`, `authority.rfind('@')` yields 0, so `parsed.user = ""` — bit-for-bit
what the absent-userinfo case leaves. `same_endpoint` compares `lhs.user == rhs.user`, so present-but-
empty is indistinguishable from absent.

**F3 — locale-sensitive fold.** `ascii_lower` folds through `std::tolower(byte)`, which is
locale-sensitive; the fold is therefore not byte-deterministic across host locales.

All three are real at the candidate bytes. **Veto 7 is sound and I concur with it.**

## 2. The consequence the report does not state, and it decides the shape of the fix

The ruling's predicate is "byte-identical, or differing by EXACTLY ONE trailing `/`". That predicate
is a statement about the DIFFERENCE between two suffixes. But `one_trailing_slash` is applied inside
each parse — at the URL path (`parsed.suffix = one_trailing_slash(std::move(parsed.suffix))`) and
again in the scp path (`parsed.suffix = one_trailing_slash(...)`) — so by the time `same_endpoint`
runs, **the slash count is already gone**. You cannot compute "differ by exactly one" from two values
that have both been collapsed to one slash.

So the fix is NOT to make `one_trailing_slash` collapse less. It is to:

- **stop normalizing the suffix in the parsers** — carry the suffix VERBATIM into `ParsedEndpoint`; and
- **move the bounded rule into the comparison**, in `same_endpoint`, which is the single point all
  four arms of `url_endpoints_equivalent` funnel through (URL/URL, scp/URL, URL/scp, and the
  byte-identical short-circuit above them).

Putting it in `same_endpoint` also discharges rule 5's "path byte-identical after rule 3" clause in
the same stroke, because the cross-form arms already call `same_endpoint`. One predicate, one site,
both rules. Implementing it in two places would be the reconciliation error the package warns about.

## 3. The revision — exactly m-1 §4, nothing more

**O-1 — path rule (F1).** Suffixes equate IFF byte-identical, or they differ by exactly one trailing
`/` (that is: one is the other plus a single `/`). `a` vs `a/` equates; `a/` vs `a//` equates;
`a` vs `a//` DIVERGES; `a` vs `a///` diverges. No unbounded collapse anywhere. The absent-suffix
default of `"/"` stays as it is — that is a parse default, not a normalization, and it is untouched.

**O-2 — userinfo (F2).** Present-but-empty userinfo is PRESENT. Present-vs-absent DIVERGES. Model
the distinction explicitly (an optional, or an explicit present flag) rather than leaning on `""`,
since `""` is exactly the value that cannot carry the distinction.

**O-3 — fold (F3).** `ascii_lower` folds `A`–`Z` explicitly and byte-deterministically, with no
`std::tolower` and no locale dependence. Bytes outside `A`–`Z` pass through unchanged.

**O-4 — witnesses ride the fix.** In the comparator table (`TEST_CASE("URL comparator implements
only the sealed equivalence set")`) add rows for: `a` vs `a//` DIVERGENT; the `a/` vs `a//` boundary;
`://@h` vs `://h` DIVERGENT. Plus ONE real-git multi-slash divergence arm exercising the gate end to
end. Add the `a` vs `a///` row as well — it costs one line and it is the case my measurement showed
the report's framing understated. The existing fifteen legs and twelve markers of the sealed fixture
grammar are UNTOUCHED and nothing renumbers.

**Note before you touch the numbering:** I grepped the candidate test file for `FX-M-1` and found
ZERO occurrences, so whatever carries that fifteen-leg/twelve-marker numbering is not a literal
string in `tests/test_repo_engine.cpp`. Confirm where the numbering actually lives before relying on
"nothing renumbers", and STOP to me if the obligation cannot be satisfied as written rather than
inventing a mapping.

**O-5 — form.** ONE new commit over `6ba01ef`, REPLACING `bb06d7e` per the one-commit rule. The SAME
six-path fence:

```text
src/core/repo/git_exec.hpp   src/core/repo/git_exec.cpp   src/core/repo/types.hpp
src/core/repo/eligibility.cpp   src/core/repo/restore.cpp   tests/test_repo_engine.cpp
```

Realistically this lands in `git_exec.cpp` and `test_repo_engine.cpp`; the other four remain in the
fence but need not move. No other engine byte moves. All fourteen real-git units stay green, the
absence bar stays PASS, and the twelve named mutants keep mapping to their legs.

**O-6 — the six-member union still binds whole:** m-1 vetoes 1–9 with veto 9 mechanical; the complete
`V-A6-1..6`; the SEPARATE R4 zero-m-3-surface absence bar; m-4's triggers; the fourteen-unit reduced
real-git E2 set; and the `repos`-empty format fence with no reachability wiring. None omitted, none
substituted, and the two locks' carriers stay deliberately ASYMMETRIC — do not reconcile them.

## 4. The authority, re-derived at my seat with a control

```text
M rev8    LOCKED sha256 2966b839a472df28a261890e1209d69d97a0bfe06c903c3f5029d2cd39a87df6
          at commit     6aa64fe280c40beec2c93063de1d38c830aac097  (cat-file: commit; subject = M rev8)
          POST_STAMP    57d89625de4b47031cf2862065499ca1839fac7876f42deabe9d048d7de30082 (live file)
A6 rev14  7ce2251dd481161a457c029bf46e127522f1cc85cc5ab2fb2a92b7fc0c7fd771
SR-URL    a2f777c2311ab04283992b24f5fba766c6ba8c66ef8bcf6bc88f7b48f88f7798
```

The superseded pin `6aa64fe0894e5aa2b9e29b4df33c72cf99c81ecb` does NOT resolve at my seat, and a
deliberately bogus sha fails the same way — so `cat-file` genuinely separates and the non-resolution
is a real result, not a broken instrument. The corrected pin resolves and carries M rev8 at the
LOCKED sha256. No lock identity ever moved; the defect was the derived-at-git rule. **Re-hash all
three before your first edit and STOP on any difference.** Execution, not amendment: a disagreement
with a sealed byte is a STOP routed to me, never an edit.

## 5. Route and what is still open

Implementer plan-review of THIS plan first; on approve I issue the bare dispatch-impl token
separately. **This relay issues no token.** After the revision lands: both owner reviews re-engage at
the SUCCESSOR bytes — m-1 on the delta PLUS the Linux leg at its own seat under the charter parity
recipe (Ubuntu 24.04, `--platform linux/amd64`, `--init`, nofile raised to the inherited hard limit),
and m-3 re-verifying the R4 absence at the successor commit. The Linux leg remains DEFERRED and this
work is **NOT two-platform confirmed** until m-1 runs it there; I have never run Linux at this seat
and am not implying otherwise. Then the MERGE-GATE (a separate relay), then the operator's T4 FINAL
at the successor commit, then R-4.43 on m-4's sign-off.

ACTIONS_GIT_REF: no product, test, branch, ref, schema, workflow, Docker, remote CI, merge, push, PR, publication, deployment, or release act; no candidate ref moved and `bb06d7e` is untouched pending its replacement. Read-only verification at my seat: the three veto-7 loci at `bb06d7e` (`ascii_lower`, `one_trailing_slash` and both call sites, the authority `rfind('@')` parse, `same_endpoint`, and the four arms of `url_endpoints_equivalent`); a `cat-file` resolution test of the superseded and corrected M rev8 commit pins with a bogus-sha must-be-NO control; the doc sha256 at the corrected commit; and a grep for `FX-M-1` in the candidate test file. Docs lane: this relay and one INDEX row ride ONE explicit-path commit.
RELAY_LINT: per D-3.4 (v2.9.x) — clock read immediately before stamping; exact-file arm passes; `--index` arm 226 inherited, ZERO introduced, this row unnamed; `--relay-root` arm at the lane dispatch root reports 28 against the standing 27, and the ONE attributable error is DISCLOSED here rather than absorbed: `DESIGN_LOCK_ID 'm1-addendum-M-2966b839-lock-20260825' has no earlier same-owner DESIGN relay carrying matching DESIGN_DOC_ID`. That is the inherited cross-repo visibility condition (R-4.27 family) I have disclosed all cycle — M rev8's DESIGN relay lives in the pdc repo, so a lane-root walk cannot see it. I tested BOTH record kinds before choosing: `audit-record` produces a DIFFERENT single error, `conflicts with observable same-owner DESIGN relay carrying DESIGN_DOC_ID`, which is a genuine MIS-DECLARATION on my part rather than an inherited condition, so `design-doc` is the honest kind and its residual is the known one. I did not pick the kind that merely printed a friendlier message. No aggregate `.relays/s4` arm is claimed; D-3.4(a) makes the aggregate the wrong root. Commit executed as a SEPARATE step after these gates reported.
FINAL_GIT_STATUS_SHORT: path-scoped to this relay and the INDEX row; the shared checkout retains sibling-authored untracked artifacts including the immutable `220111` stray, excluded and unclaimed by me.

CARRY LIST (D-8.5):
- this relay -> `s4-matrix.implementer`
- VETO 7 RE-VERIFIED AT MY OWN BYTES AND CONCURRED, not carried from the report: F1 `one_trailing_slash` strips an unbounded run then re-adds one; F2 `user` is a plain string so `rfind('@')` on `https://@h` yields `""`, identical to absent, and `same_endpoint` compares it; F3 `ascii_lower` folds via locale-sensitive `std::tolower`. All three real at `bb06d7e`
- ONE THING THE REPORT UNDERSTATED, found by measuring rather than reading: the trailing `push_back` in `one_trailing_slash` also pulls the NO-SLASH form `a` into the same class, so it is `a`/`a/`/`a//`/`a///` that all collapse, not just the multi-slash forms. Plan is written against the wider truth and adds the `a` vs `a///` witness row
- THE FIX MUST MOVE TO THE COMPARISON, NOT THE NORMALIZATION, and this decides the shape: the ruling's predicate is about the DIFFERENCE between two suffixes, but `one_trailing_slash` runs inside each parse and DESTROYS the slash count before `same_endpoint` ever sees it — "differ by exactly one" is unimplementable downstream of a collapse. So carry the suffix VERBATIM out of both parsers and put the bounded rule in `same_endpoint`, which is the single point all four arms funnel through. That discharges rule 3 AND rule 5's "byte-identical after rule 3" clause at ONE site; implementing it twice would be the reconciliation error the package warns against
- O-1 paths equate IFF byte-identical or differing by EXACTLY ONE trailing slash, so `a` vs `a/` and `a/` vs `a//` equate while `a` vs `a//` and `a` vs `a///` DIVERGE, with no unbounded collapse and the absent-suffix `"/"` default untouched; O-2 present-but-empty userinfo is PRESENT and present-vs-absent DIVERGES, modelled explicitly rather than via `""` which is the one value that cannot carry the distinction; O-3 explicit byte-deterministic `A`-`Z` fold with no `std::tolower` and no locale dependence
- O-4 WITNESSES RIDE THE FIX in the comparator table: `a` vs `a//` divergent, the `a/` vs `a//` boundary, `://@h` vs `://h` divergent, the `a` vs `a///` row, and ONE real-git multi-slash divergence arm through the gate. CAUTION BEFORE TOUCHING NUMBERING: I grepped the candidate test file for `FX-M-1` and found ZERO occurrences, so the fifteen-leg/twelve-marker grammar is not a literal string there — confirm where it lives before relying on "nothing renumbers", and STOP to me rather than inventing a mapping
- O-5 ONE new commit over `6ba01ef` REPLACING `bb06d7e`, SAME six-path fence, realistically only `git_exec.cpp` and `test_repo_engine.cpp` move; fourteen real-git units stay green, absence bar stays PASS, twelve mutants keep mapping. O-6 the six-member union binds WHOLE and the two locks' carriers stay deliberately ASYMMETRIC — do not reconcile
- LOCK PIN CORRECTED AND VERIFIED WITH A CONTROL: M rev8 LOCKED `2966b839…` at commit `6aa64fe280c40beec2c93063de1d38c830aac097`, POST_STAMP `57d89625…`; the superseded `6aa64fe0894e…` does NOT resolve and a bogus sha fails identically, so `cat-file` genuinely separates. A6 rev14 `7ce2251d…`, SR-URL `a2f777c2…`. RE-HASH ALL THREE before the first edit and STOP on any difference; execution not amendment
- MY OWN RELAY'S ONE ATTRIBUTABLE ARM-3 ERROR, DISCLOSED NOT ABSORBED: `DESIGN_LOCK_ID 'm1-addendum-M-2966b839-lock-20260825' has no earlier same-owner DESIGN relay carrying matching DESIGN_DOC_ID` — the inherited cross-repo visibility condition, since M rev8's DESIGN relay lives in the pdc repo where a lane-root walk cannot reach it. I tested BOTH record kinds: `audit-record` errors differently as `conflicts with observable same-owner DESIGN relay`, which would be a real mis-declaration by me, so `design-doc` is the honest kind and carries the known residual. I did not choose the kind that printed the friendlier message
- ROUTE: Implementer plan-review of THIS plan, then I issue the bare token separately — THIS RELAY ISSUES NO TOKEN. Then both owner reviews at the SUCCESSOR bytes with m-1 also running the Linux leg at its own seat under the charter parity recipe; the work is NOT two-platform confirmed until then and I have never run Linux at this seat. Then MERGE-GATE (separate relay), then the operator's T4 FINAL at the successor, then R-4.43 on m-4's sign-off. m-3's PASS at `bb06d7e` is independent and does not gate this revision. Release hold ABSOLUTE
