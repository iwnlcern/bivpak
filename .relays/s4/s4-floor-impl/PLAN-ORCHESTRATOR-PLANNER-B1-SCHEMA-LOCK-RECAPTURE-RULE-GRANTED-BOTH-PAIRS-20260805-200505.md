## DISPOSITION — the STANDING PER-SLICE RECAPTURE RULE IS GRANTED (path 1), and it is the ruling of record for BOTH pairs: a locked-schema blob lock recaptures MECHANICALLY in the SAME reviewed head that changes the schema, literal-for-literal, nothing else in the file. B1 folds the envelope entry to its reviewed blob and proceeds to PR; Tasks 4-11 unblock.

ROLE: Orchestrator Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-floor-impl-2-b1-schema-lock-blocker
PARENT_DISPATCH_ID: s4-floor-pair-plan
RUN_ID: s4
TASK_ID: B1
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no — a within-gate lock-discipline disposition at the seat the standing conditions name; no sealed artifact moves; merge is the operator's; the release hold is ABSOLUTE
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/SITREP-PLANNER-B1-SCHEMA-LOCK-DEVIATION-ROUTED-20260805-195419.md
FROM: s4.orchestrator-planner
TO: s4-floor.planner
CC: operator, s4.orchestrator-reviewer, s4-floor.implementer
SUBJECT: PLAN — the blob-lock recapture discipline ruled; the exact bound; B1 unblocked to PR

Verified at this seat before ruling (E1): `harness/selftest/test_envelope.py:11-14` pins
`CURRENT_LOCKED_SCHEMA_BLOBS`; `git hash-object` on `main` returns exactly the pinned
`ac127cab…` (envelope schema) and `bc86a434…` (exit map). The lock therefore goes red on
EVERY slice head that legitimately edits a locked schema — B1 now (Task 1's required
envelope edit), Task 5 (slice A, envelope again), Task 7 (slice C, exit map) by plan.
The pair is right that a one-off edit is no discipline at all.

**THE RULING — the standing rule, bounded exactly:**

1. **What the lock IS, stated so the rule preserves it:** a staleness tripwire that makes
   locked-schema changes DECIDED, never accidental. Per-slice recapture in the SAME
   reviewed head preserves that entirely — the recapture rides the review that approved
   the schema change, so the lock's green is always a reviewed decision, never a drive-by.
2. **The rule:** `harness/selftest/test_envelope.py` is admitted to the dispatched
   universe for MECHANICAL LOCK RECAPTURE ONLY — at each slice head that changes a
   locked schema artifact, update ONLY the corresponding `CURRENT_LOCKED_SCHEMA_BLOBS`
   literal to that slice's reviewed git blob id, in the SAME head (composing with the
   slices' one-commit laws). No harness behavior, scenario logic, or other selftest
   surface changes. Any other edit to the file — or a recapture of a literal whose
   schema the head did NOT change — is a NEW deviation, back here before an edit.
3. **Both pairs, one discipline (recorded in RECONCILE as the ruling of record):** the
   matrix pair's Arm-1 schema act will edit the SAME two locked artifacts (envelope
   repos rows; exit-map row retirement). The identical rule binds there: recapture
   literal-for-literal in the same reviewed head, inside the act window that owns the
   schema file. This does NOT touch the frozen open-envelope ORACLE's separate
   once-per-window recapture ruling — different instrument, different discipline, as
   your relay correctly distinguished; the oracle rule stands unchanged.
4. **B1 immediate fold, authorized:** recapture the envelope entry to the reviewed
   `561dccf0…` on the B1 head, prove the focused lock test + the relevant harness
   selection green, scoped review per your stated shape, then the B1 PR. Tasks 4-11
   unblock behind it. The three non-gating reviewer items ride to the B1 panel as
   carried, no edit authorized.

ACTIONS_GIT_REF: no product edits at this seat; this relay + its INDEX row + the RECONCILE ruling-of-record note, committed on the docs lane
FINAL_GIT_STATUS_SHORT: not claimed here — see the lane commit carrying this relay for the path-scoped set
