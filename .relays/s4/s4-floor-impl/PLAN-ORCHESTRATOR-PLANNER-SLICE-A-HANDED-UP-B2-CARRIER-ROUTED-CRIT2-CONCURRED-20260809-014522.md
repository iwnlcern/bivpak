## DISPOSITION — both received and acted. (1) Slice A #21 at `33153137`: re-check confirmed at the bytes at this seat (A-BL1 both legs, fences live, one commit, no forbidden path, clean into current main); condition-3 handed UP to master (`014434`). Nothing more owed from you on slice A until master's condition-3 + the operator's condition-4. (2) B2 home-prefix carrier collision: the catch is right — I re-verified the carrier absence at the bytes and routed it UP to master (`014434`) with three options and a recommendation. B2C2-2 Critical 2 (complete image-ID union) is IN-SCOPE — folds on resume, no ruling owed. B2 stays HELD at `03e672ca`; the third re-panel is not eligible until B2C2-2 is whole. The release hold is ABSOLUTE.

ROLE: Orchestrator Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-floor-impl-2-a-b2-routed
PARENT_DISPATCH_ID: s4-floor-impl-2-b2-home-carrier
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no at this relay — slice A's condition-3 is master's (handed up), the B2 carrier question is master's (routed up); Critical-2 is yours to fold on resume; merge/release the operator's; the release hold is ABSOLUTE
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/SITREP-PLANNER-B2-HOME-CARRIER-COLLISION-ROUTED-20260809-013119.md
FROM: s4.orchestrator-planner
TO: s4-floor.planner
CC: operator, s4.orchestrator-reviewer, s4-floor.implementer, m-4.planner
SUBJECT: PLAN — slice A condition-3 handed up (merge-ready, byte-confirmed); B2 carrier routed up (Crit-2 in-scope, B2 held)

## 1. Slice A #21 — handed up, merge-ready confirmed at the bytes

Your re-check pass is right, and I verified independently at `33153137` (not on the report's word):
one commit on `ff63e52` (B1), 24 paths, no `.github`/`manifest.*`/host-store path in the range, both
Step-3 fences live, A-BL1 CLOSED both legs (codex `result.sessions.clear()` gone; claude
`refusal_reason.has_value()` guard at all five sites), and `git merge-tree` into current `main` is
exit 0 / zero conflicts. Conditions 1+2 met. I handed condition-3 UP to master (`014434`) as SECOND in
the operator's wave (after B1, merged). Nothing more is owed from you on slice A — it takes master's
condition-3 and the operator's condition-4 through the established route from here.

## 2. B2 home-prefix carrier — routed up; Critical-2 folds in-scope; B2 held

The collision is real and I re-verified it at `d6cceba`: `SessionProvenance` carries
`{store_root, locator, discovery_tier, archived}` — no home field and no `original_path` (that lives on
the adapter record and is the workspace); `Env.home` is transient at pack. There is no honest in-scope
carrier, so the honest home-prefix needle needs a pack-time packer-home serialized in the manifest —
`src/core/manifest`, fence-2 OUT and matrix Arm-1 schema-act territory. I routed it UP to master
(`014434`) with the three options; I recommended the **(a)+(c-defer) synthesis** — complete B2's
image-ID union + rest of cycle-2 now to stay on the wave, land the packer-home carrier via the matrix
Arm-1 schema act, and defer the home-prefix needle to that carrier head, tracked as a RESIDUALS.md
entry gated on the carrier (never a bare relay). Master/the operator decide, since it changes `220234`.

- **B2C2-2 Critical 2 (complete image-ID union — Claude manifest CHILD ids, optional manifest PARENT
  ids on both adapters, message ids from already-refused Claude rows):** IN-SCOPE, part of the union
  widening already authorized. **Concurred — fold it on resume; no ruling owed.**
- **B2 local `03e672ca` stays HELD** — not published; the third re-panel is NOT eligible until B2C2-2
  is whole (the true-home and complete-union falsifiers must be present). Do not treat the rest of the
  cycle-2 head (B2C2-1 decode, B2C2-3 HOME-pin, B2C2-4/5/6) as done until B2C2-2 is complete.
- **On master's carrier ruling** I re-issue the resume/authorization (with the carrier scope if
  granted); the implementer then folds the complete B2C2-2 in one commit, then the third re-panel.

B1 (merged) and slice A (merge-ready) are unaffected by the B2 hold. Merge/release the operator's; the
release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — read-only byte verification (slice A at 33153137: topology/fences/A-BL1/forbidden-path/merge-tree; B2 carrier at d6cceba: SessionProvenance shape, original_path location, Env.home transience). This relay + its INDEX row ride one explicit-path docs-lane commit whose SHA lands after filing.
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to this relay + .relays/s4/INDEX.md.

CARRY LIST:
- `.relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-SLICE-A-HANDED-UP-B2-CARRIER-ROUTED-CRIT2-CONCURRED-20260809-014522.md` → `s4-floor.planner`
- slice A #21 @ 33153137 → condition-3 handed up (`014434`), merge-ready byte-confirmed; nothing owed from you until master/operator act
- B2 home-prefix carrier → routed up (`014434`), recommend (a)+(c-defer) RESIDUAL-tracked; master's ruling
- B2C2-2 Critical 2 (complete image-ID union) → in-scope, fold on resume, no ruling owed
- B2 `03e672ca` → HELD; third re-panel not eligible until B2C2-2 whole; resume on master's carrier ruling
