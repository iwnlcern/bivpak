## PLAN (carry-down) — BOTH token gates I was tracking are now CLEAR, and the Addendum-12 pin MOVED. **(1) W-1 (the lineage-red waiver) is CONCURRED and EFFECTIVE, re-scoped to the PROPERTY so it survives a pin change. (2) Your cap-carrier cell is RESOLVED in the Addendum-12 rev8 lock — and the ruling is stronger than the option you recommended: m-2 ruled the cap refusal NEVER fell under §A12.4.1 ("a refusal is not a drop"), narrowed §A12.4.1 to material omitted/altered within an EMITTED entry, and added §A12.4.2 — so J's typed loud fatal carries the cap refusal and no `CollectReport.warnings` line was ever owed. Your (B) OUTCOME holds; its RECOMMENDED REASONING ("a typed error discharges the warnings clause") was REJECTED — do not encode that basis.** **(3) THE PIN MOVED: Addendum-12 is now `29a5b3a3` (commit `6eeeb157`, VP-re-approved `191415`, superseding the void `145249`); the old `154cd87e` is SUPERSEDED. Your `163555` binding to `154cd87e` is retired.** **YOUR NEXT ACT: a SUCCESSOR slice-E PLAN under `s4-floor-slice-e-plan-20260812` carrying the CURRENT pin `29a5b3a3` and the resolved §A12.4.1/§A12.4.2 cap-carrier reading.** The token still is NOT issued — the remaining gates are all independent and yours to clear. Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ROLE: Orchestrator Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-floor-slice-e-successor-plan-directed
PARENT_DISPATCH_ID: s4-floor-slice-e-plan-rev1
IN_REPLY_TO: ../../../../pdc/master/relays/s4-build-standup/RECONCILE-ORCHESTRATOR-PLANNER-W1-CONCURRED-EFFECTIVE-FOLD-FILED-CHAIN-CLOSED-20260812-211308.md
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new operator gate — W-1 is the operator-granted waiver (effective) and the Addendum-12 rev8 is VP-re-approved. Remaining gates are yours: the successor PLAN, its local PLAN-REVIEW approve, token-time tuple re-verification, and merge/seal/publication/deployment/release. The release hold is ABSOLUTE.
DESIGN_DOC_ID: m2-addendum-12-transitive-collect-mono-gate-20260812
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m2-addendum12-29a5b3a3-lock-20260812
TARGET_DESIGN_SHA256: 29a5b3a3abb6777af70a1c959728f4f61731489a1735773e81713b5aa3ea3adb
TARGET_DESIGN_COMMIT: 6eeeb157be249792d61774016485d97c303e2c8f
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812
FROM: s4.orchestrator-planner
TO: s4-floor.planner
CC: operator, s4.orchestrator-reviewer, s4-floor.implementer, master.orchestrator-planner, m-2.planner
SUBJECT: PLAN — both gates clear (W-1 effective + cap-carrier resolved in Addendum-12 rev8); pin moved to 29a5b3a3; file a successor slice-E PLAN under s4-floor-slice-e-plan-20260812 at the new pin

## 1. Gate 1 — W-1 effective, property-scoped

The operator's waiver is now the concurred/effective residual **W-1**, re-scoped to the cross-repo
foreign-lock-target lineage PROPERTY on the slice-E plan lineage — so it survives the pin move (a pin-bound
waiver would have died when Addendum-12 re-locked). It clears ONLY that structural lint red; it does NOT
approve your PLAN, supply local PLAN-REVIEW approval, issue a token, or confer merge/seal/publication/release.

## 2. Gate 2 — the cap-carrier cell is RESOLVED (verified at my seat)

The Addendum-12 rev8 lock `29a5b3a3` contains m-2's ruling on the seam you routed:

```text
§A12.4.1 predicate NARROWED (rev5): "Any material OMITTED FROM, OR ALTERED WITHIN, AN ENTRY OR REPORT THAT
  IS NEVERTHELESS EMITTED MUST produce a line on CollectReport.warnings."
  => a whole-entry cap REFUSAL is NOT a drop/alteration-within-an-emitted-entry, so it NEVER fell under §A12.4.1.
§A12.4.2 ADDED (rev3): holds the cap case — J's LOCKED TYPED WHOLE-ENTRY REFUSAL naming cap + entry.
RULING: the cap refusal is J's typed loud fatal; NO CollectReport.warnings line is owed for it.
```

**This is your (B) outcome — pack-side typed error, no warnings line — but the JUSTIFICATION is m-2's, not
the one you recommended.** m-2 explicitly rejected "a typed error discharges the warnings requirement" (it
would license discharging the OTHER §A12.4.1 items the same way). **Encode the correct basis in the successor
PLAN: the cap refusal is outside §A12.4.1 by predicate; §A12.4.2 + J carry it.** Both killing arms you named
still bind (a fatal with NO disclosure fails; and a genuine drop/alter with NO §A12.4.1 warnings line fails).

## 3. Gate 0 — the pin MOVED; carry the new one

```text
OLD (retired):  m2-addendum12-154cd87e-lock  @ 3929c9c   VP approval 145249 is VOID (superseded)
NEW (carry):    m2-addendum12-29a5b3a3-lock  @ 6eeeb157   VP re-approval 191415, consuming J 94b6440c
LIVE now:       d0e2c6eb  (a post-stamp of the 29a5b3a3 lock — confirm at token time it is a DISCLOSED
                           status-only post-stamp, NOT an unlocked normative edit)
```

Your `163555` binding to `154cd87e` is retired; the successor PLAN carries `29a5b3a3`. rev3b stays
`must-revise` (`171210`) and is NOT revived by any of this.

## 4. Your next act and the remaining gates (all yours, all independent)

1. **File a successor slice-E PLAN** under `s4-floor-slice-e-plan-20260812`, `DESIGN_LOCK_ID:
   m2-addendum12-29a5b3a3-lock-20260812`, `TARGET_DESIGN_SHA256: 29a5b3a3…`, `TARGET_DESIGN_COMMIT: 6eeeb157`,
   `CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock`, parenting to the VP re-approval `191415`; carry the
   resolved §A12.4.1/§A12.4.2 cap-carrier reading and the reconciled coupled scope (collector recursion + both
   root-mapped gates + killing tests + disposable-store CLI E2E; manifest schema half is m-1's, `manifest.cpp`
   fence-2 HARD-OUT).
2. **Its local PLAN-REVIEW approve** from your Implementer (the plan gate).
3. **Token-time re-verification of the seven-element evidence tuple** — lock declaration + VP approval naming
   `DESIGN_LOCK_ID` + full SHA-256 + full commit; the pre-lock content dispositions naming `DESIGN_DOC_ID` +
   full target SHA-256 (+ commit); all preceding the successor and the token; **no later supersession and no
   later unlocked normative edit** (this is where the live `d0e2c6eb` vs lock `29a5b3a3` must be shown a
   disclosed status-only post-stamp). A miss makes W-1 INAPPLICABLE / NO TOKEN — recoverable, not terminated.
4. Then the delegated token issues; then merge-gate (four-condition bar). The release hold is ABSOLUTE.

Nothing you built is lost — the coupled slice carries forward onto the new pin. Merge ≠ push ≠ release.

ACTIONS_GIT_REF: no product/test edits at this seat — carry-down of master's W-1/chain-closed reconcile (211308) with independent verification at the bytes: Addendum-12 @ 6eeeb157 == 29a5b3a3 (live d0e2c6eb), VP re-approval 191415 approve on 29a5b3a3, and the §A12.4.1-narrowed / §A12.4.2-added cap-carrier ruling diffed 154cd87e->29a5b3a3. This relay + its INDEX row ride one explicit-path docs-lane commit whose SHA lands after filing.
RELAY_LINT: per D-3.4 + corrected D-3.4(a) — per-file WITH freshness; `.relays/s4/INDEX.md` tail re-read before appending; `--index`; the slice-E lineage red is operator-WAIVED (W-1 effective, property-scoped); third arm at the active dispatch root `.relays/s4/s4-floor-impl` disclosed by class at `162400`. INDEX line 222 is the pre-existing sibling class, not mine.
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to this relay and `.relays/s4/INDEX.md`.

CARRY LIST (D-8.5):
- `.relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-SLICE-E-BOTH-GATES-CLEAR-PIN-MOVED-SUCCESSOR-PLAN-29A5B3A3-20260812-211825.md` → `s4-floor.planner`, `s4-floor.implementer`
- BOTH gates clear: W-1 (lineage waiver) CONCURRED/EFFECTIVE + property-scoped; cap-carrier cell RESOLVED in Addendum-12 rev8 (29a5b3a3): m-2 ruled the cap refusal NEVER fell under §A12.4.1 (a refusal is not a drop), narrowed §A12.4.1 + added §A12.4.2 -> J's typed fatal carries it, no warnings line owed. Your (B) outcome, NOT your recommended reasoning (rejected)
- PIN MOVED: 154cd87e (@3929c9c, VP 145249 VOID) -> 29a5b3a3 (@6eeeb157, VP re-approval 191415), live d0e2c6eb post-stamp; your 163555 154cd87e binding retired; rev3b stays must-revise 171210, NOT revived
- NEXT ACT: successor slice-E PLAN under s4-floor-slice-e-plan-20260812 carrying 29a5b3a3 + §A12.4.1/§A12.4.2 reading + the coupled scope, parenting to VP re-approval 191415
- remaining independent gates: successor PLAN -> local PLAN-REVIEW approve -> token-time 7-element tuple re-verify (incl. live d0e2c6eb shown a disclosed status-only post-stamp, no unlocked normative edit) -> token -> merge-gate; W-1 approves none of these; release hold ABSOLUTE
