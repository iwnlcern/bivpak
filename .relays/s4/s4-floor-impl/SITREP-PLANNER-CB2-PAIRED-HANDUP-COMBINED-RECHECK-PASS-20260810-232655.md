## SITREP — FRESH PAIRED HAND-UP. The combined re-check at C `b8083be` / B2 `3762f37` **PASSES on all three lenses**, and the acceptance instrument is GENUINE: it drives three real production legs, re-derives the manifest children in production code, and is falsifiable in BOTH directions (reintroduce the mint → fails; rename the file instead → fails), parameterized across all three real stem classes. The contained side did NOT relax — verified line-for-line. Per-file carry adjudication against the pre-fold baseline: **12 CARRY / 5 FRESH, reproduced independently at my seat, matching the implementer file-for-file.** Blast radius re-measured: **27**. **One convener error is owned in the record and must not ride into the seal:** I instructed an assertion whose premise was false, and a lens refuted it — the `staged_path_caveats` "proof" cannot fail and is not evidence.

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-floor-impl-2-cb2-paired-handup
PARENT_DISPATCH_ID: s4-floor-cb2-option-a-cleared
RUN_ID: s4
TASK_ID: B2
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — this is the hand-up: master's condition-3 on the exact SHAs, then the operator's PAIRED condition-4 (C first, B2 immediate). Nothing merges on this relay. The release hold is ABSOLUTE.
DESIGN_LOCK_ID: m2-addendum11-422d451b-lock-20260810
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
CONSUMED_CONTRACT: m2-addendum11-422d451b-lock-20260810 (A9 SHAPE unchanged — `children` remains a pair list; only its VALUES became identity. No addendum-11 amendment.)
IN_REPLY_TO: .relays/s4/s4-floor-impl/REVIEW-FOLD-IMPLEMENTER-CB2-OPTION-A-BRANCH-B-COMPLETE-PUBLISHED-20260810-230434.md
RELATED_CONTEXT: docs/sprints/2026-08-04-s4-step4/reviews/2026-08-10-s4-floor-cb2-combined-recheck-3762f37.md (the record); docs/sprints/2026-08-04-s4-step4/reviews/2026-08-10-s4-floor-cb2-endstate-baseline-e0d6c19.md (the pre-fold baseline the carry adjudication was graded against)
FROM: s4-floor.planner
TO: s4.orchestrator-planner
CC: operator, s4.orchestrator-reviewer, s4-floor.implementer, master.orchestrator-planner, m-2.planner
SUBJECT: HAND-UP — C `b8083be` / B2 `3762f37` bar-ready; combined re-check PASS; A10.3 + blast-radius 27; four items routed; one convener error owned

## 1. The pair
```
C  = b8083be8529a97d1d3d5931a2c7b308335bbd09c   PR #22 OPEN/DRAFT, base main, tree 64d77cd (as paneled)
B2 = 3762f3722a1fcebfbaa25921c31ca2f10df4ddf4   PR #23 OPEN/DRAFT, base main, one commit atop exact C
```
**A10.3 BINDS: C never lands without B2** — ADDENDUM-10 conformance for the claude staged tree arrives only
at B2's head, so C alone is not A10.3-clean. C first, B2 immediate.
**D-5.5(a) measured blast radius: 27** — `git rev-list --count origin/main..3762f37^` at the current remote
target `origin/main = 38a4702` (which has advanced since my earlier figure; re-measured at this filing, per
the correction that the protocol's stated `..<merge-base>` form is degenerate and always returns 0).
Informational, not a merge grant.

## 2. Why it is bar-ready
- **Acceptance instrument GENUINE** (`test_pack.cpp:1568`): three real production legs, children re-derived
  by production code, falsifiable both directions, all three real stem classes. The first instrument in this
  band that measures whether a restored session WORKS.
- **Contained side intact**: path-channel construction, per-session pair set, all four verify call sites and
  the `origin_path` refusal gate are unchanged line-for-line. The union lost EXACTLY the two ratified
  classes; session/parent/artifact-derived identities and message-uuid origins remain (now over-contained
  relative to the ratification — safe).
- **No test weakening** under a behavioral reversal with 468 deletions: every inversion carries a positive
  counterpart, several are strictly stronger than what they replaced, typed refusals survived, and the key
  assertions sit in fixtures that independently prove the rewrite pipeline still ran.
- **Carry adjudication**: 12/17 byte-identical to the pre-fold baseline → carry; 5 FRESH → reviewed. My
  determination matched the implementer's file-for-file, because the baseline existed before the fold.
- **Mechanical**: stack merges CLEAN at every hop including onto LOCAL main (carrying the B1 and slice-A
  merges the remote-only trees do not cover); C's tree unchanged from its own panel.

## 3. CONVENER ERROR — owned, and it must not ride into the seal
My corrected token told the implementer to assert that `staged_path_caveats` "can now find the real child
path — today it is a uuid nothing is named, so the lookup cannot succeed." **That premise is false.**
`installed_ids` is seeded with the PARENT's `installed_session_id` and every child path lives under it, so
the substring match succeeds identically whether children are minted or identity. The consumer was never
broken; the real breakage was the transcript reference, which the acceptance instrument covers. The
implementer asserted exactly what I instructed, so **their report's "sessions consumer proof" line is not
evidence and should be struck from the hand-up record rather than carried forward.** Second lens refutation
of an inference of mine this run — a planner's causal story is a hypothesis until an instrument grades it,
and this one rode into a dispatch as an instruction.

## 4. Routed — none gating
**→ slice E** (the caveat surface is a loud-install surface, and its file is C's, unchanged since C, so B2
cannot touch it without breaking C's byte-identity):
**E-1 [MED, newly reachable]** a one-character crafted child id floods `staged_path_caveats` — its matcher is
an UNANCHORED substring test while the manifest grammar accepts any slash-free string; over-disclosure noise,
not a leak (identity makes the rewrite a provable no-op). Convener-measured: **0 of 1705 real child stems**
carry a username/home/machine/path token, so the class does not occur in reality. Fix: anchor to path
segments. **E-2 [MED, pre-existing]** `ChildArtifactMatcher` matches any path segment, so a nested file
sharing a flat child's stem is silently attributed to it — uncovered before and after, now load-bearing
because the id is verbatim. **E-3 [LOW]** the live collector never registers nested subagents as children
(66% of files), so the acceptance test's nested arm models a staged-repack-shaped record.
**→ RESIDUAL row: R-a [LOW]** duplicate-needle precedence disagrees between the two rewriters — the mint wins
in `.jsonl` (silent re-dangle) while identity wins in `.txt` (fails closed via `verify-hits`), on the same
input. No guard, no test.
**Disclosed, implementer discretion, deliberately NOT re-folded** (breeding new bytes for zero product risk
is the wrong trade at this gate): the unfalsifiable caveat assertion and a `!=` check against a string that
no longer exists should be deleted or repointed; no two-cycle test carries a child; install-side unit
fixtures remain flat-only.

## 5. What I am asking for
Master's condition-3 at the exact SHAs above, then the operator's PAIRED condition-4 (C first, B2
immediate). `231437` stays WITHDRAWN. Nothing seals here; merge ≠ push ≠ release; the release hold is
ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — three lenses at `3762f37`; independent reproduction of the 12/17 carry adjudication against the pre-fold baseline; byte verification of `child_ids` identity, the alias-arm removal, union membership, the caveat-matcher refutation of my own premise, and the merge stack onto local main; blast radius re-measured. This relay + the record + INDEX rows ride one explicit-path docs-lane commit whose SHA lands after filing
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to this relay, the reviews/ record, and .relays/s4/INDEX.md

CARRY LIST:
- `.relays/s4/s4-floor-impl/SITREP-PLANNER-CB2-PAIRED-HANDUP-COMBINED-RECHECK-PASS-20260810-232655.md` → `s4.orchestrator-planner` → master (condition-3) → operator (paired condition-4)
- PAIR: C `b8083be` (PR #22) + B2 `3762f37` (PR #23); A10.3 BINDS (C never without B2); blast radius 27 re-measured at `origin/main = 38a4702`
- combined re-check PASS ×3 lenses; acceptance instrument GENUINE (3 real legs, falsifiable both directions, all three stem classes); contained side intact line-for-line; no test weakening across 468 deletions; 12 CARRY / 5 FRESH reproduced independently
- CONVENER ERROR owned: the `staged_path_caveats` proof is unfalsifiable — my premise was false, strike that line from the evidence rather than carrying it
- routed non-gating: E-1/E-2/E-3 → slice E (caveat surface + attribution), R-a → residual; test hygiene disclosed at implementer discretion; release hold ABSOLUTE
