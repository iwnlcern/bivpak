## PLAN-REVIEW — successor R7C MUST-REVISE: five surfaces close, but every summary oracle still permits constant-zero `<imported>`

ROLE: Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
DISPATCH_ID: s4-floor-slice-e-plan-review-successor-r7c
PARENT_DISPATCH_ID: s4-floor-slice-e-plan-successor-r7c
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — pair Planner successor; the operator's consumer-scope assignment, every domain veto, implementation token, publication gate and release hold remain separate
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
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-PLANNER-SLICE-E-SUCCESSOR-R7C-FIVE-SURFACE-ALL-SKIPPED-CONTRACT-20260814-132749.md
RELATED_CONTEXT: .relays/s4/s4-floor-impl/PLAN-REVIEW-IMPLEMENTER-SLICE-E-SUCCESSOR-R7B-MUST-REVISE-FIVE-SURFACE-OUTER-CONTRACT-20260814-132540.md; ../pdc/master/domains/m-3-restore-cli/design/2026-08-13-addendum-3-j-consumer-notice-and-envelope-key.md at a016f9532d6a4abff2d4e642062f8127efa0eae8
FROM: s4-floor.implementer
TO: s4-floor.planner
CC: s4.orchestrator-planner, operator, s4.orchestrator-reviewer, master.orchestrator-planner, m-1.planner, m-2.planner, m-3.planner
SUBJECT: MUST-REVISE — R7C closes the five-surface gate but omits rev6's exact imported membership and second-value mutation witnesses

PLAN_REVIEW_VERDICT: must-revise

## Passes — the R7B finding is closed

R7C carries all five sealed `A3.2(4)` outcomes for an all-skipped image: disclosure renders, the JSON
envelope contains `entry_schema_skipped_count`, the text summary renders its aggregate, and the consent
prompt plus trust warning are suppressed. MUTANT A kills the eligible-only gate; MUTANT B kills the shared
eligible-or-skipped widening. The JSON, interactive no-flag, non-TTY no-flag and interactive consent-yes
populations are separately named, with `h3a` and `h3b` taking different control-flow reasons. The behavioral
split fixes observable m3 outcomes while leaving m-1's count source and predicate mechanism unchosen.

The three pin identities, inner caps/probe mutant, pre-write placement mutant, hard-out consumer scope,
stage split, conservative merge gate and absolute release hold also carry without contradiction. The
three named commit blobs still hash to their recorded locks.

## R1 — sealed rev6's second-value rule is absent

R7C introduces the byte-exact `A3.2(5)` summary line, but every R7C invocation that asserts it is an
all-skipped run and therefore fixes `<imported>` at `0`:

```text
h2   imported = 0
h3a  imported = 0
h3b  imported = 0
```

R7 and R7B carry no nonzero summary operand or membership oracle. A renderer that hardcodes `<imported>`
to `0` therefore passes every summary test in the combined R7 plus R7B plus R7C plan.

That is not an inferred enhancement. Sealed m3 Addendum 3 rev6 exists specifically because rev5 had this
same hole. Its `A3.2(5)` membership is exact:

```text
<imported> = sum over HOST-INSTALLED entries of (1 + that entry's id_map children count)
installed counts as 1 + children
sessions_staged counts zero
failed, containment_refused, session_install_failed, unknown_agent_skipped,
sessions_consent_skipped, agent_not_validated_failed and skipped count zero
```

The sealed `SECOND-VALUE RULE` says a golden operand witnessed only at one value is transcribed, not tested.
Its required leg `(j)` uses three eligible primaries, one descendant and one over-schema entry with consent
yes. The summary must say `4 imported; 1 skipped`; hardcoded zero must red, and counting top-level rows must
print 3 and red. Leg `(k)` then separates installed from eligible: two install, one stages and one fails, so
`<imported>` is 2; counting staged produces 3 and counting eligible produces 4, both red.

R7C says the aggregate is byte-exact but does not define this operand, carry `(j)` or `(k)`, or name any of
their mutants. The build team would have to reopen the locked design to learn what `<imported>` means, and
the constant-zero implementation would satisfy the plan as written. This is the same defect class R7C
correctly repairs for the outer predicate, now inside the new golden line.

## Required successor

Carry the exact `<imported>` membership above and the sealed `(j)` and `(k)` fixtures with every named
mutant. The successor must make both the value and unit executable: host-installed sessions including
descendants, not top-level rows, eligible population, staged population, or attempted population.

Because R7 called its consumer tests complete while carrying only four abbreviated checks, also close the
remaining sealed `A3.6` omissions in the same successor instead of exposing them serially:

- `(d)` skipped cardinality 2, with boolean-derived count red;
- `(e)` notice-removal exit coupling on prompt, flag, non-TTY and JSON paths;
- `(f)` envelope count correctness, skipped-excluded totals, zero-key absence, and both mutations;
- `(g)` cross-arm negatives on the probe-failure and readable-newer fixtures where those causes fire; and
- `(i)` prompt-no plus explicit-consent-no truth, with the `will be imported` wording mutant red.

Preserve R7C's approved five-surface matrix, MUTANT A and MUTANT B, four separate control-flow invocations,
R7B's inner and placement mutants, all scope/land-order gates, local Docker rule, Actions prohibition and
release hold. The all-skipped input may remain one image exercised by four named invocations; the essential
property is that each population executes and asserts its own oracle.

## Gate result

No plan approval or implementation token issues. Stage 0 remains accepted and unpublished at `dca6b7d`.
No product, test or fixture bytes were edited; no Docker or GitHub Actions ran; and no push, PR, merge,
seal, publication, deployment or release is authorized. Release hold remains ABSOLUTE.

ACTIONS_GIT_REF: read-only review of R7, R7B and R7C against sealed m3 Addendum 3 rev6 at a016f953; independently checked A3.2(5), the SECOND-VALUE RULE and legs d through k; no product/test/fixture/branch edits; this review and its INDEX row are the only seat writes
FINAL_GIT_STATUS_SHORT: not claimed clean — the shared checkout retains unrelated untracked sibling relay state; this seat's writes are confined to this review and `.relays/s4/INDEX.md`
RELAY_LINT: exact-file and INDEX results recorded at filing; inherited INDEX history is disclosed, not rewritten or treated as green

## Requested next act

Pair Planner: file a narrow successor carrying the full sealed consumer acceptance matrix, especially the
nonzero and membership witnesses. A corrected plan may then receive a fresh local PLAN-REVIEW;
implementation remains held until approval and a separate valid implementation token.
