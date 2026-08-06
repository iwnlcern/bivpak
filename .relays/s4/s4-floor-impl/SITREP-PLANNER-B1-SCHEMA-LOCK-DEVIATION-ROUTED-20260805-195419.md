## SITREP — B1 schema-lock deviation ROUTED UP: the harness blob-lock (OUT path) goes deterministically red on every slice that edits a locked schema; a STANDING per-slice recapture rule is requested, not a one-off

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-floor-impl-2-b1-schema-lock-blocker
PARENT_DISPATCH_ID: s4-floor-impl-2
RUN_ID: s4
TASK_ID: B1
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: yes — `harness/selftest/test_envelope.py` is OUT of the dispatched universe; per the standing conditions the deviation re-engages your seat before any edit; the release hold is ABSOLUTE
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/IMPL-BLOCKER-IMPLEMENTER-B1-SCHEMA-LOCK-SCOPE-20260805-194600.md
FROM: s4-floor.planner
TO: s4.orchestrator-planner
CC: operator, s4.orchestrator-reviewer, s4-floor.implementer
SUBJECT: SITREP — B1 review-clean but held at PR; harness schema-blob lock needs a bounded recapture rule spanning slices B1/A/C; pair recommendation attached; B1 PR + Tasks 4-11 held

## The finding, verified at this seat (E1)

`harness/selftest/test_envelope.py:13-16` pins `CURRENT_LOCKED_SCHEMA_BLOBS` — git blob
ids for the two locked schemas — and I reproduced the ground truth on main:
`git hash-object` returns exactly the pinned `ac127cab…` (envelope schema) and
`bc86a434…` (exit map). Task 1's REQUIRED schema edit gives the B1 head a new envelope
blob (`561dccf0…`, the implementer's reviewed value), so the lock test fails
deterministically on that branch — by the lock's design, not by defect.

This recurs by plan: Task 5 (slice A) edits the envelope schema again and Task 7
(slice C) edits the exit map — both locked entries. So the disposition needs to be a
STANDING per-slice rule, exactly as the implementer argues; a one-off undocumented edit
would break at the next slice and provide no lock discipline.

## B1 state (the implementer's, consistent with the record)

Product behavior review-clean across Tasks 1-3 (whole-slice review verdict "With fixes"
solely on this lock); head `s4-floor/b1-codex-liveness@4944801`; worktree clean; no OUT
edit occurred; no push, no PR, no successor branch; Tasks 4-11 held.

## The dispositions, framed

1. **Bounded standing rule (pair recommendation):** admit exactly
   `harness/selftest/test_envelope.py` for MECHANICAL LOCK RECAPTURE ONLY — at each
   slice head that changes a locked schema artifact, update only the corresponding
   `CURRENT_LOCKED_SCHEMA_BLOBS` literal to that slice's reviewed git blob id, in the
   SAME head (composing with slices A/C's one-commit laws); no harness behavior,
   scenario logic, or other selftest surface changes; any other edit to the file is a
   NEW deviation. Immediate B1 fold: recapture the envelope entry to `561dccf0…`, prove
   the focused lock test + relevant harness selection green, scoped review, then the B1
   PR.
2. **Alternative governance:** if per-slice recapture is not the intended lock
   discipline (e.g. the lock should instead be recaptured once at a designated
   window, like the frozen-oracle rule), direct the exact alternative AND how B1/Task 4
   satisfy their green-harness gates meanwhile — the plan's own gates make the lock
   load-bearing, so "leave it red" is not an option the plan permits.

Note for your seat's cross-pair view: this lock is the same CLASS as the frozen
open-envelope oracle (a deliberate staleness tripwire over shared bytes) but a
DIFFERENT instrument — the oracle has a ruled once-per-window recapture; this blob lock
has no ruled discipline yet, which is the actual gap B1 exposed. Whichever shape you
pick likely belongs in RECONCILE as the ruling of record for both pairs.

Also carried from the whole-slice reviewer, non-gating, for the eventual B1 panel: the
`codex_testing` linkage seam declaration, the two-LF fixture's diff-check exception, and
B2's TornTail renderer coverage — no edit authorized by this relay.

ACTIONS_GIT_REF: writes at this seat: this relay + its INDEX row, committed on the docs lane with explicit paths (SHA in the commit record); no product/test/harness/schema edit; the standing s4-floor-impl-2 dispatch stays live but held at the B1 PR gate
FINAL_GIT_STATUS_SHORT: not a read-only phase report; disk evidence rides the docs-lane commit SHA in ACTIONS_GIT_REF

CARRY LIST:
- `.relays/s4/s4-floor-impl/SITREP-PLANNER-B1-SCHEMA-LOCK-DEVIATION-ROUTED-20260805-195419.md` → `s4.orchestrator-planner`
