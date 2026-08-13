## RECONCILE — land order bound at Implementer seat; R5 is superseded before review and a successor pair plan is required

ROLE: Implementer
PHASE: RECONCILE
AUTHORITY: report-only
DISPATCH_ID: s4-floor-slice-e-land-order-bound-implementer
PARENT_DISPATCH_ID: s4-floor-slice-e-land-order-bound
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-SLICE-E-LAND-ORDER-BOUND-SCHEMA2-NOT-AHEAD-OF-M3J47-20260813-025756.md
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — the operator's scope-generalization decision and the separately routed m-3 notice-design/lock remain above this pair; the pair Planner owes a successor plan before local plan review
DESIGN_DOC_ID: m2-addendum-12-transitive-collect-mono-gate-20260812
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m2-addendum12-29a5b3a3-lock-20260812
TARGET_DESIGN_SHA256: 29a5b3a3abb6777af70a1c959728f4f61731489a1735773e81713b5aa3ea3adb
TARGET_DESIGN_COMMIT: 6eeeb157be249792d61774016485d97c303e2c8f
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812
PLAN_LOCK_ID: s4-floor-slice-e-plan-20260812
FROM: s4-floor.implementer
TO: s4-floor.planner, s4.orchestrator-planner
CC: operator, s4.orchestrator-reviewer, master.orchestrator-planner, m-1.planner, m-2.planner
SUBJECT: RECONCILE — schema-2 stamp cannot land ahead of M3-J-4..7; R5 predates the binding and is not reviewable as the operative plan

## Binding accepted at this seat

The orchestrator carry-down is addressed to this Implementer and binds execution order without granting
implementation authority. I independently re-read Addendum J at exact locked commit `e30f845`; its SHA-256
is `94b6440c6ea5342a266ac16eb07b9eb4f1f52524f334e180483d2648d2049d18`. The sealed text states that the
consumer obligation lands before any J-capable writer ships and that the conditional schema bump is strictly
worse than no bump without M3-J-4..7 in force. Exact `origin/main` remains
`0db8fdd8424d27aad2c547614e9ebb95621a2794`; `sessions.cpp:345` still records only a boolean skip and
`:410-414` silently emits `unknown_agent_skipped` for `entry_schema > 1`.

Therefore the operative order at this seat is:

```text
BUILD/RED-TEST     Stage 1a writer bytes may be built and exercised only after an approved successor plan
                   and a valid implementation dispatch.
LAND/SHIP          the schema-2 stamp may not land or ship before M3-J-4..7 is in force.
CONSUMER SURFACE   src/core/open/sessions.cpp remains HARD-OUT until the upper scope/ownership decisions land.
```

The writer and consumer obligations must land together, or the consumer may land first. Writer-first is
forbidden. A local build or test result is not publication, merge, or authority to land the stamp.

## Effect on R5 and this review lane

`PLAN-PLANNER-SLICE-E-SUCCESSOR-R5-STAGE1B-SPLIT-ON-MEASURED-BOUNDARY-20260813-023240.md` predates this
binding. It says Stage 1a is dispatchable on its plan review, calls Stage 1b-i consumer-independent, and
allows the slice to reach seven keys with the shipped acceptance instrument merely owed. Those statements
do not bind the newly required atomic land order across the writer and consumer half. R5 is therefore
superseded before verdict; I do not issue a `PLAN_REVIEW_VERDICT` against a plan that the later orchestrator
binding has made non-operative.

The pair Planner's successor must distinguish the locally buildable/testable Stage-1a commit from its
forbidden writer-first landing, bind the M3-J-4..7 prerequisite to every publication/merge/hand-up path, keep
`sessions.cpp` out until authority lands, and preserve everything already passed at the R4 review: the
J-capable schema-2 reader, schema-3/schema-99 skip controls, base-binary compatibility falsifier, producer-
versus-reader behavior distinction, manifest-only fence, m-1 byte veto, three STOPs and five VETOES.

## Items still above this pair

- m-3 owns the exact notice string/surface design and its reviewed lock; this pair does not answer it or
  address that seat directly.
- the operator owns whether the prior scope ruling generalizes to `src/core/open` under m-3 byte-level veto;
  absent that ruling, this pair does not edit the consumer surface.
- ownership outcome does not weaken the land order: whoever implements the consumer half, M3-J-4..7 must be
  in force before or atomically with the schema-2 stamp.

No bare implementation token appears in the carry-down. No implementation, Docker, GitHub Actions, push,
PR, merge, seal, publication, deployment or release act is authorized. Stage 0 remains accepted and
unpublished at `dca6b7d`; the release hold remains ABSOLUTE.

ACTIONS_GIT_REF: read-only reconciliation against Addendum J at `e30f845`, exact `origin/main` `0db8fdd` and the addressed orchestrator relay; no product/test/fixture/branch edits; this reconciliation and its INDEX row are the only seat writes
FINAL_GIT_STATUS_SHORT: not claimed clean — the coordination checkout retains unrelated untracked sibling relay state; this seat's writes are confined to this reconciliation and `.relays/s4/INDEX.md`
RELAY_LINT: exact-file OK at filing; `--index` reports only inherited line-222 and disclosed `013935`/`014004` inversions at line 393; both remain append-only history and are not rewritten

## Requested next act

Pair Planner: file the successor plan binding the build/test versus land/ship distinction and the atomic
M3-J-4..7 publication order. This Implementer then performs the local plan review; no Stage 1 dispatch or
work precedes that gate.
