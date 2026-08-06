## SITREP — B1's C1-anchor deviation ROUTED UP, with a PROVENANCE FLAG the prior two grants did not have: the drift anchor is s3-era C1 instrumentation, so whose authority rules its recapture is itself part of the question

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-floor-impl-2-b1-c1-tripwire-blocker
PARENT_DISPATCH_ID: s4-floor-impl-2
RUN_ID: s4
TASK_ID: B1
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: yes — the anchor literal is OUT of every granted scope; per the standing conditions the deviation re-engages your seat before an edit; and the instrument's s3 provenance may put the recapture RULE above this run entirely — your call which authority applies; the release hold is ABSOLUTE
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/IMPL-BLOCKER-IMPLEMENTER-B1-C1-TRIPWIRE-SCOPE-20260805-212230.md
FROM: s4-floor.planner
TO: s4.orchestrator-planner
CC: operator, s4.orchestrator-reviewer, s4-floor.implementer
SUBJECT: SITREP — B1 held at the green-at-head gate by the C1 whole-file source anchor; narrow recapture path framed + the B2 recurrence + the sealed-instrument authority question; everything held

## The finding, verified at this seat (E1)

`harness/bivharness/e3.py:68-77` pins `_ADAPTER_SOURCE_ANCHORS` — whole-file SHA-256
anchors for BOTH adapters' collect-side files. Reproduced on main: `shasum -a 256`
returns exactly the pinned `4fb3b38c…` (codex.cpp) and `ba4308ec…` (claude_code.cpp), so
the tripwire is green on main and RED on the B1 head by the anchor's own design — B1's
required, reviewed tail-liveness change alters codex.cpp's file hash while (per the
implementer's review) NOT changing the session-location surface C1 protects.
Blast radius verified from the implementer's run: 52 harness-selftest failures, all
downstream of the one anchor (every E3 path fails closed at the tripwire).
The comment block above the dict shows the anchor set is a CONSIDERED design
(install.cpp deliberately excluded as restore-side) — this is a working tripwire doing
its job on a legitimate change, the same shape as the A2 blob lock, on a different
instrument.

## Implementer conduct (clean again, and note the A2 execution detail)

Amendment A2 was exercised EXACTLY and then rolled back when the stop fired: the
envelope-literal edit was made, focus-tested green, and RESTORED once the wider harness
selection was irretrievably red — no commit, no PR, no successor branch; worktree clean
at `4944801`. The A2 grant was not stretched to cover the anchor; the anchor deviation
was routed instead. Tasks 4-11, the B1 recapture commit, and the PR are all held.

## The recurrence, mapped from the locked plan (why a one-off is again no answer)

- B1 (now): codex.cpp anchor trips.
- B2 (torn-tail): changes BOTH collect files — both anchors trip.
- E: install.cpp only — deliberately excluded, no trip.
- The matrix pair: Arm 1 does not touch adapter collect files; no trip expected there.
So the rule must cover at least B1 and B2 on this pair.

## The dispositions, framed

1. **Narrow mechanical recapture (the implementer's recommendation, pair-concurred as
   the WITHIN-RUN shape):** admit the single anchor literal for same-reviewed-head
   recapture — B1 updates only `codex_adapter_file` from `4fb3b38c…` to the reviewed
   `f00fbde5…`; the claude anchor and all C1 behavior untouched; focused tripwire tests
   + full harness selftests + the E2 selection proven green; then scoped review → B1
   PR → slice-A seed. Extend the same literal-only, changed-file-only, same-head
   discipline to B2's two anchors (mirroring your A2 ruling's shape).
2. **The alternatives named by the implementer, neither recommended nor inferred:**
   waive the per-slice harness-green gate for B1 (weakens a load-bearing plan gate), or
   redesign C1 to anchor the protected session-location SURFACE rather than the whole
   file (attractive long-term — it would end this class — but it is a change to what
   the instrument MEASURES, which is exactly the part that may not be ours).

## THE PROVENANCE FLAG (what makes this one different from A1/A2)

The C1 drift tripwire is s3-era instrumentation: the C1 binding, its anchors, and its
population were ruled in the s3 lane with VP involvement. A recapture RULE for its
anchor literals is a rule about what keeps a SEALED-ERA instrument honest — that may be
this run's to grant (the anchor VALUES are mechanical facts of the tree), or it may
need the bridge to master/the instrument's owner (if the anchor discipline itself is
part of what s3 sealed). The A2 precedent (blob-lock recapture, granted at your seat,
both pairs) is the near analogue and may settle it; distinguishing them — or not — is
above the pair, so I route it named rather than assumed. Option-2b (re-anchoring to the
protected surface) is flagged as DEFINITELY above this run.

ACTIONS_GIT_REF: writes at this seat: this relay + its INDEX row, committed on the docs lane with explicit paths (SHA in the commit record); no product/test/harness/schema edit; the standing s4-floor-impl-2 dispatch stays live but held at the B1 green-at-head gate
FINAL_GIT_STATUS_SHORT: not a read-only phase report; disk evidence rides the docs-lane commit SHA in ACTIONS_GIT_REF

CARRY LIST:
- `.relays/s4/s4-floor-impl/SITREP-PLANNER-B1-C1-ANCHOR-DEVIATION-ROUTED-20260806-001643.md` → `s4.orchestrator-planner`
