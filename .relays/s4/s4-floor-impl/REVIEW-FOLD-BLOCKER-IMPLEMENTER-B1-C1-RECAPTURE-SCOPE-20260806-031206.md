## REVIEW-FOLD BLOCKER — the folded Codex source trips the per-head C1 anchor, but the mandatory mechanical recapture path was omitted from my pre-edit FOLD_SCOPE

ROLE: Implementer
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-floor-impl-2-b1-review-fold-c1-scope-blocker
PARENT_DISPATCH_ID: s4-floor-impl-2-b1-review-fold
RUN_ID: s4
TASK_ID: B1
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: yes — scope/process disposition is required before any C1 anchor edit, folded commit, push, PR-body update, or Slice-A restack
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/IMPL-PLANNER-RESUME-B1-FOLD-WHOLE-20260806-025746.md
FROM: s4-floor.implementer
TO: s4-floor.planner
CC: s4.orchestrator-planner, operator
SUBJECT: B1 FOLD BLOCKED AT C1 GATE — exact anchor recapture is authorized per head, but harness/bivharness/e3.py was absent from the pre-edit FOLD_SCOPE; no silent widening

## Verified trigger

The focused F1-F5/F7-F9 implementation and regressions are uncommitted in the B1
worktree. The focused C++ selection is GREEN (`145 assertions in 7 test cases`).
Because the fold changes `src/adapters/codex/codex.cpp`, the standing master grant
at `PLAN-ORCHESTRATOR-PLANNER-C1-RECAPTURE-GRANTED-B1-RELEASES-FOUR-CHECKS-20260806-002730.md`
applies again: every Step-4 head changing an anchored file must recapture its one
anchor literal at the same head under the four checks.

At the current uncommitted folded bytes:

```text
shasum -a 256 src/adapters/codex/codex.cpp
6f8ec5721e7aed0950d6d2a16bc2463cf5f5085412594fafc338ea8ae1f318cf
```

The required pinned-source command exits `1`:

```text
/Library/Frameworks/Python.framework/Versions/3.12/bin/python3.12 -m pytest \
  harness/selftest/test_e3_asserts.py::test_drift_tripwire_is_green_at_pinned_source -q

C1 drift tripwire RED: adapter session-location source changed (codex_adapter_file)
```

`git diff -- harness/bivharness/e3.py` is empty: no anchor edit has been made.

## Scope/process defect

My `REVIEW-FOLD-SCOPE-IMPLEMENTER-B1-F1-F9-20260806-030052.md` declared the
finding paths, durable receipt, PR body, and relay paths, but omitted
`harness/bivharness/e3.py`. That omission makes its “every file”/all-IN claim
incomplete even though Amendment A3's standing per-head rule narrowly authorizes the
one `codex_adapter_file` literal recapture. I own this scope miss. The required
pre-edit timing cannot be repaired retroactively, so I will not silently amend the
anchor or claim the original FOLD_SCOPE was complete.

The product/test/fixture edits remain confined to the already-declared paths. No
`CMakeLists.txt`, schema lock, Claude anchor, exit-map lock, harness behavior, merge,
release, or Slice-A change has occurred.

ACTIONS_GIT_REF: B1 remains at committed head d5642ed9ea19cd6256276681b63199adff21aea4 with the focused fold held as uncommitted changes; no anchor edit, commit, push, PR-body mutation, merge, release, or restack performed; this blocker relay and append-only INDEX row are the only docs-lane writes
FINAL_GIT_STATUS_SHORT: B1 has only the declared fold product/test/fixture changes; docs lane was clean at 285cfc4758fab77f70832555eb8461ac0ed86251 before this relay and INDEX append

NEXT REQUESTED ACTION:
The Planner should obtain/issue an explicit disposition for the process scar and
corrected scope. If accepted, re-dispatch the whole fold with
`harness/bivharness/e3.py` IN for exactly the `codex_adapter_file` literal matching
the final folded `codex.cpp` bytes, preserving the per-head four-check ceremony and
five-owner durable receipts. If the pre-edit rule instead requires restart, direct
whether the held uncommitted fold must be restored and replayed after a corrected
FOLD_SCOPE. No new implementation authority beyond that narrow choice is requested.

CARRY LIST:
- `.relays/s4/s4-floor-impl/REVIEW-FOLD-BLOCKER-IMPLEMENTER-B1-C1-RECAPTURE-SCOPE-20260806-031206.md` → `s4-floor.planner`
- C1 recapture scope/process disposition → `s4.orchestrator-planner`
