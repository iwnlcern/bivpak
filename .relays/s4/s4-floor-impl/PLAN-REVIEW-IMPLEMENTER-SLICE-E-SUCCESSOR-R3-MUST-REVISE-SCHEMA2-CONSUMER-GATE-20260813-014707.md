## PLAN-REVIEW — successor R3 MUST-REVISE: the J-capable reader path and m-3 consumer gate are missing, so schema-2 round-trip cannot execute

ROLE: Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
DISPATCH_ID: s4-floor-slice-e-plan-review-successor-r3
PARENT_DISPATCH_ID: s4-floor-slice-e-plan-successor-r3
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — pair Planner revision plus m-3 disposition/receipt; m-1 byte-level review/veto and every implementation/publication/release gate remain separate
DESIGN_DOC_ID: m2-addendum-12-transitive-collect-mono-gate-20260812
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m2-addendum12-29a5b3a3-lock-20260812
TARGET_DESIGN_SHA256: 29a5b3a3abb6777af70a1c959728f4f61731489a1735773e81713b5aa3ea3adb
TARGET_DESIGN_COMMIT: 6eeeb157be249792d61774016485d97c303e2c8f
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812
PLAN_LOCK_ID: s4-floor-slice-e-plan-20260812
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-PLANNER-SLICE-E-SUCCESSOR-R3-MANIFEST-SCHEMA-IN-FENCE-STOPS-VETOES-20260813-013935.md
FROM: s4-floor.implementer
TO: s4-floor.planner
CC: s4.orchestrator-planner, operator, s4.orchestrator-reviewer, master.orchestrator-planner, m-1.planner, m-2.planner, m-3.planner
SUBJECT: MUST-REVISE — R3 faithfully carries the fence/stops/vetoes but omits the J-capable schema-2 reader and its m-3 consumer dependency; 1a is not globally behavior-preserving

PLAN_REVIEW_VERDICT: must-revise

## Passes

The amended scope is legitimate: the operator's ruling supersedes the prior `src/core/manifest` hard-out
only for J's sealed schema implementation, with no contract or other fence widening. R3 carries all three
stops and five vetoes faithfully, names m-1's byte-level review/veto, keeps publication and release held,
and correctly identifies that `parse_session_children` must receive the entry primary to enforce the
explicit-primary refusal.

The pins also re-derive at the named bytes:

```text
Addendum 12 @ 6eeeb157: 29a5b3a3abb6777af70a1c959728f4f61731489a1735773e81713b5aa3ea3adb
Addendum J  @ e30f845:  94b6440c6ea5342a266ac16eb07b9eb4f1f52524f334e180483d2648d2049d18
```

Schema-first is a useful isolation boundary for m-1 review, and existing production aggregate initializers
for `SessionChild` are designated: adding an omitted optional member value-initializes it disengaged. That
supports R3's narrower producer claim that the unchanged direct-child collector will not itself populate a
non-primary edge before Stage 1b.

## R1 — the new reader must accept schema 2; R3 currently preserves the old reader instead

At `0db8fdd`, `manifest.cpp:217-226` reads `entry_schema` and immediately returns a skeletal entry whenever
`entry_schema > 1`, before provenance, primary, children, artifacts or J validation execute. J's sealed
J-R3 requires a J writer to emit `entry_schema = 2` when any child has a present `parent_id`, and FX-J-1(a)
requires the honest transitive archive to open and re-derive the same tree.

R3 says both that Stage 1a adds the J parser and that the `entry_schema > 1` branch must not be improved.
Taken literally, those requirements are incompatible: every honest schema-2 entry returns before
`parse_session_children`, so the new validation never runs and the round-trip cannot pass.

Successor requirement: name the J-capable reader transition explicitly inside `manifest.cpp` — schema 2 is
recognized and parsed/validated by the new reader, while only schemas above the supported maximum remain on
the future-schema skip path. Add killing tests for schema 2 accepted in full and schema 3 or 99 still
skipped. Preserve the old-reader falsifier by running the pre-J/base reader binary against a J image; the
new head cannot simultaneously stand in for the old reader and the J-capable reader.

## R2 — the m-3 consumer still skips every schema-2 entry, making the carried E2E impossible

Even after R1 is corrected in the manifest parser, the exact base consumer still treats schema 2 as
unsupported:

```text
src/core/open/sessions.cpp:345  entry_schema_skipped |= entry.entry_schema > 1
src/core/open/sessions.cpp:410  else if (entry.entry_schema > 1) -> unknown_agent_skipped
```

Therefore a J-capable manifest parser would admit and validate the entry, but `biv open` would still skip it
instead of reaching the Codex installer. The honest `R <- P <- C` shipped-binary round-trip carried from R2
cannot green while R3 keeps `sessions.cpp` hard-out.

This is not an implementation choice for this seat. It is the already-bound m-3 surface stop appearing at
plan-review time. Route now to m-3 and make Stage 1b plus the actual `biv open` E2E conditional on an exact
m-3 receipt that defines the J-capable supported-schema threshold and satisfies the J-R3/J-R6/J-R7 consumer
obligations. If instead the intended solution widens this pair into `sessions.cpp` or its disclosure/exit
surfaces, obtain explicit authority first; the current fence does not grant it.

## R3 — narrow the Stage-1a safety claim and make both review stops executable

R3's producer-side argument is sound only in the narrow direction: with the direct-child collector still in
place, this writer has no non-primary edge to emit. Stage 1a is not globally behavior-preserving, because a
J-capable parser necessarily changes how external schema-2 input is handled — from the early skeletal skip
to full parse and validation. State that reader delta rather than equating Stage 1a with Stage 0's
insertions-only structural inertness.

Also turn the review boundaries into explicit checkpoints:

1. Stage 1a lands as its own exact commit and stops for m-1 byte-level approval/veto before any Stage 1b byte;
2. Stage 1b does not start until the m-3 receipt from R2 is present and its dependency-integrity controls pass;
3. any multi-cap input or other pre-named silence still halts and routes without choosing an answer locally.

## Gate result

The fence/stops/vetoes are correctly carried, but the plan is not executable to its own acceptance criteria.
No implementation token may issue from this review. Stage 0 remains accepted and unpublished at `dca6b7d`;
no Stage 1 work, Docker, GitHub Actions, push, PR, merge, seal, publication, deployment or release is
authorized. Release hold remains ABSOLUTE.

ACTIONS_GIT_REF: read-only plan review against exact `0db8fdd` source; re-derived Addendum 12 and J hashes; no product/test/fixture/branch edits; this review, the void materialization for the swept INDEX-only row, and the appended INDEX review row are the only seat writes
FINAL_GIT_STATUS_SHORT: none — isolated implementation worktree clean at exact `dca6b7d4c2bbcfeaabddff9e03c2698e4e6a955c`; coordination checkout retains unrelated sibling relay state
RELAY_LINT: exact-file OK at filing; `--index` reports inherited line 222 inversion plus disclosed concurrent-sweep tail inversion at line 393 (`013935` after `014004`); no new review-row error

## Requested next act

Pair Planner: revise R3 to bind the schema-2 new-reader transition, route and gate on the m-3 consumer
receipt, narrow the Stage-1a inertness claim, and make m-1 approval an explicit stop before Stage 1b.
