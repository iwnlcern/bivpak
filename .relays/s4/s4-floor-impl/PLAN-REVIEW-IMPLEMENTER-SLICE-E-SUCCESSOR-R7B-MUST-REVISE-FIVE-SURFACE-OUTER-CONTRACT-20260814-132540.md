## PLAN-REVIEW — successor R7B MUST-REVISE: the second silent-loss gate is found, but the locked five-surface outcome is not carried

ROLE: Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
DISPATCH_ID: s4-floor-slice-e-plan-review-successor-r7b
PARENT_DISPATCH_ID: s4-floor-slice-e-plan-successor-r7b
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — pair Planner successor; the operator's separate consumer-scope assignment, every domain veto, implementation token, publication gate and release hold remain unchanged
DESIGN_DOC_ID: m2-addendum-12-transitive-collect-mono-gate-20260812
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m2-addendum12-29a5b3a3-lock-20260812
TARGET_DESIGN_SHA256: 29a5b3a3abb6777af70a1c959728f4f61731489a1735773e81713b5aa3ea3adb
TARGET_DESIGN_COMMIT: 6eeeb157be249792d61774016485d97c303e2c8f
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812
CONSUMER_DESIGN_LOCK_ID: m3-addendum-3-eeb4dd01-lock-20260814
CONSUMER_TARGET_DESIGN_SHA256: eeb4dd01cc907b5dc793a7a27892395a8af258f4967a38fd744f2b424013c7aa
CONSUMER_TARGET_DESIGN_COMMIT: a016f9532d6a4abff2d4e642062f8127efa0eae8
CONSUMER_POST_STAMP_SHA256: cefd3f799b571bea511b362583c97e1a856dbf07b97a4a948882d74705a6db67
PLAN_LOCK_ID: s4-floor-slice-e-plan-20260812
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-PLANNER-SLICE-E-SUCCESSOR-R7B-TWO-SUPPRESSION-PATHS-BOUND-20260814-131510.md
RELATED_CONTEXT: .relays/s4/s4-floor-impl/PLAN-PLANNER-SLICE-E-SUCCESSOR-R7-THREE-PINS-CONSUMER-NOTICE-BOUND-20260814-130641.md (amended base); ../pdc/master/domains/m-3-restore-cli/design/2026-08-13-addendum-3-j-consumer-notice-and-envelope-key.md at a016f9532d6a4abff2d4e642062f8127efa0eae8 (sealed consumer bytes)
FROM: s4-floor.implementer
TO: s4-floor.planner
CC: s4.orchestrator-planner, operator, s4.orchestrator-reviewer, master.orchestrator-planner, m-1.planner, m-2.planner, m-3.planner
SUBJECT: MUST-REVISE — R7B correctly binds the inner guard, eligible-only outer gate and pre-write placement, but omits A3.2(4)'s distinct outcomes and shared-widening mutant across all five consumers

PLAN_REVIEW_VERDICT: must-revise

## Passes

R7B correctly finds the defect R7 missed. At sealed m3 Addendum 3 `a016f953`, `A3.2(2)` binds the inner
capability/probe guard while `A3.2(4)` separately shows that M3-J-4 can make every eligible count zero and
therefore close the outer `any_sessions()` gate. The two named mutants are real and non-duplicative:

```text
inner  nest the line under caps/probe; failed probe plus skipped >= 1 loses the line
outer  retain the eligible-only gate; zero eligible plus skipped >= 1 loses the whole carrier
```

The placement amendment also reads the locked design rather than inventing a new carrier. At exact base
`0db8fdd`, `main.cpp` constructs the disclosure at `:269-272`, publishes it at `:295-303`, executes archive
output at `:352-356`, calls the host-writing `run_session_leg` at `:357-358`, and renders the final summary
at `:381-382`. A shared-domain event-trace leg that reds after moving the notice beyond the first write
therefore protects the locked pre-write rule. R7B also preserves the consumer half as named-if-granted and
keeps `src/core/open/sessions.cpp` hard-out until the operator assigns that work.

The three contract pins remain exact at their named commit blobs, including m3 Addendum 3:

```text
Addendum 12 @ 6eeeb157  29a5b3a3abb6777af70a1c959728f4f61731489a1735773e81713b5aa3ea3adb
Addendum J  @ e30f845   94b6440c6ea5342a266ac16eb07b9eb4f1f52524f334e180483d2648d2049d18
m3 Add. 3  @ a016f953   eeb4dd01cc907b5dc793a7a27892395a8af258f4967a38fd744f2b424013c7aa
```

## R1 — the outer-gate repair omits three surfaces and permits the exact mechanism A3.2(4) excludes

R7B binds this outer requirement:

```text
the OUTER carrier predicate MUST COUNT SKIPPED ENTRIES, so an all-skipped image
still admits the preview and still emits
```

Its falsifier is an all-skipped image passed through the unmodified eligible-only predicate. That is
necessary, but it is not the complete locked `A3.2(4)` behavior. At `0db8fdd`, `any_sessions()` has five
consumers, and sealed Addendum 3 rules each one for zero eligible and skipped greater than or equal to one:

```text
disclosure      RENDER
json envelope   PRESENT with entry_schema_skipped_count
text summary    RENDER with the A3.2(5) aggregate
consent prompt  SUPPRESS
trust warning   SUPPRESS
```

R7B names only admission and emission. R7, which R7B amends, did not carry `A3.2(4)` at all, so “everything
else in R7 stands” cannot supply the missing three surfaces or the two explicit suppressions.

This omission leaves a natural-but-wrong implementation green against every R7B mutant: widen the one
shared `any_sessions()` predicate to `eligible > 0 OR skipped > 0`. The disclosure renders, the all-skipped
outer mutant is killed, and the plan's inner and placement tests still pass — but the same widening also
renders an inert consent prompt on the interactive path and a trust warning on non-prompt paths. Sealed
`A3.2(4)` explicitly excludes that observable result. The plan therefore does not yet let an implementer
or reviewer verify the all-skipped contract without reopening the m3 design, which is the criterion R7B
asks this review to judge.

## Required successor

Carry the five outcomes above into the executable plan and bind both classes of outer mutation:

1. Keep the eligible-only outer predicate mutant on an all-skipped image, proving disclosure, machine key
   and text summary do not vanish.
2. Add the distinct shared-widening mutant, proving consent prompt and trust warning do not appear. Preserve
   the sealed named populations: JSON; interactive TTY with no consent flag; non-TTY with no consent flag;
   and interactive TTY with `--consent yes`. The last two are separate control-flow populations and cannot
   be collapsed into one disjunctive leg.
3. State the behavioral split without choosing m-1's mechanism: disclosure/envelope/summary key on eligible
   or skipped, while prompt/warning remain keyed to eligible. Count source and predicate mechanism remain
   m-1's; observable m3 behavior is not open.

Preserve R7B's approved inner-guard and pre-write mutants, three-pin identity, hard-out consumer scope,
stage split, merge-gate predicate, refused early-merge narrowing, local Docker rule and absolute release
hold. The successor may remain a narrow amendment to R7 plus R7B.

## Gate result

The defect is execution-critical because the shared widening is the simplest repair to the outer silence
and would violate two locked user surfaces while satisfying R7B as written. No plan approval or
implementation token issues from this review. Stage 0 remains accepted and unpublished at `dca6b7d`.
There are no product, test or fixture edits; no Docker or GitHub Actions run; and no push, PR, merge, seal,
publication, deployment or release is authorized. Release hold remains ABSOLUTE.

ACTIONS_GIT_REF: read-only review of R7 plus R7B against sealed m3 Addendum 3 at a016f953 and exact base 0db8fdd call order; independently rechecked the m3 blob hash; no product/test/fixture/branch edits; this review and its INDEX row are the only seat writes
FINAL_GIT_STATUS_SHORT: not claimed clean — the shared checkout retains unrelated untracked sibling relay state; this seat's writes are confined to this review and `.relays/s4/INDEX.md`
RELAY_LINT: exact-file and INDEX results recorded at filing; inherited INDEX history is disclosed, not rewritten or treated as green

## Requested next act

Pair Planner: file the narrow successor carrying the complete five-surface all-skipped contract and both
outer mutation classes. A corrected plan can then receive a fresh local PLAN-REVIEW; implementation remains
held until that approval and a separate valid implementation token.
