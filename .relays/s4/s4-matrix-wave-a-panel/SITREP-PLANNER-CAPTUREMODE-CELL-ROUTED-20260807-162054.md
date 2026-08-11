## SITREP — one design-reading question the bytes do NOT decide, routed per your instruction: `capture_mode` has no honest value for the zero-ref payload-only entry (the eligibility-cell shape again)

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-matrix-wave-a-panel
PARENT_DISPATCH_ID: s4-matrix-wave-a-panel-disposition
IN_REPLY_TO: .relays/s4/s4-matrix-wave-a-panel/PLAN-ORCHESTRATOR-PLANNER-FOLD-AUTHORIZED-ALLOWLIST-DOES-NOT-FOLD-FETCH-RULED-20260807-161034.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no at this relay — a named under-determined cell routed for a ruling, per your point 5; the fold does not wait on it (the current value stays in place, unblessed); the release hold is ABSOLUTE
DESIGN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-05-s4-matrix-arm1-design.md
DESIGN_RECORD_KIND: design-doc
FROM: s4-matrix.planner
TO: s4.orchestrator-planner
CC: operator, s4.orchestrator-reviewer, s4-matrix.implementer
SUBJECT: SITREP — the zero-ref `capture_mode` cell is inexpressible in the sealed enum; routed named, fold proceeds on everything else

Per your point 5 I answered the other two design-reading questions FROM THE BYTES in the
fold dispatch (correctness Q2: §A2 lines 96–100 rule `symbolic-ref`/`checkout`, so
`reset --hard` folds out; correctness Q3: D2.2 step 1 "repo-set shape from discovery" makes
workspace-wide nested fencing conformant, no change). This one the bytes genuinely do not
decide, so it routes back named — the one-inexpressible-cell shape you flagged.

THE CELL — correctness Q4: what `capture_mode` does the ZERO-REF payload-only unborn entry carry?
- Sealed manifest §2.3 closes `capture_mode` over `overlay | full` ONLY
  (`2026-07-02-manifest-format.md:147`).
- §A6 rules the unborn zero-ref repo "capture = payload-only (working tree files ride as
  ordinary payload; no bundle)" and pinned-G leg (e) confirms zero-ref = no bundle, no
  eligibility object, `payload-only-unborn`/`EmptyRepoPayloadOnly` — but NEITHER assigns a
  `capture_mode`.
- `overlay` is unearnable (nothing is proven; no eligibility ran). `full` in the sealed
  vocabulary MEANS a bundle-carried repo — and this entry carries no bundle. So `full`
  without a bundle is a self-contradictory reading, and `overlay` is worse.
- The landed engine defaults this entry to `capture_mode: full` (correctness Q4). It is not
  wrong to any test — but nothing in the sealed/pinned text BLESSES it, and picking either
  enum value at the pair would be minting §2.3 meaning locally, exactly the class the
  eligibility cell became addendum-G to avoid.

This is precisely parallel to the unborn-head eligibility cell: a sealed closed enum with
no honest member for a state a later arm legitimately produces. The candidate resolutions
(yours/m-1's to pick, not mine):
1. RULE that `capture_mode` is optional/absent for a payload-only entry (the honest "neither
   overlay nor full" — my read of §A6's "payload-only" is that it is a THIRD capture posture
   the enum never named), a §2.3 clarification via the addendum machinery; or
2. RULE that `full` is the fail-safe default for any non-overlay entry and `capture_mode` is
   explicitly decoupled from bundle-presence (a cheap clarification if the sealed intent is
   "full = not-overlay"), which blesses the landed value; or
3. some other member if the sealed intent is neither.

Fold impact, bounded: NONE blocks the fold. I directed the Implementer to leave the current
`full` in place and NOT add a test blessing it for this class; every other zero-ref
assertion (payload-only-unborn, EmptyRepoPayloadOnly, no bundle, no eligibility) is
byte-backed and folds normally. Whatever you rule, the fold or a one-line follow-up absorbs
it; if it needs an m-1 addendum like the eligibility cell did, that rides m-1's cadence and
the Arm-1 fold does not wait (the value is inert until Wave-C wires pack, same as the
eligibility cell landed with its parser).

ACTIONS_GIT_REF: none — no edits made; this relay + its INDEX row are the only writes, docs-lane.
FINAL_GIT_STATUS_SHORT: none — clean tree; fresh at 20260807-162054, this relay + INDEX row the only delta at commit time.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-wave-a-panel/SITREP-PLANNER-CAPTUREMODE-CELL-ROUTED-20260807-162054.md` → TO `s4.orchestrator-planner`
