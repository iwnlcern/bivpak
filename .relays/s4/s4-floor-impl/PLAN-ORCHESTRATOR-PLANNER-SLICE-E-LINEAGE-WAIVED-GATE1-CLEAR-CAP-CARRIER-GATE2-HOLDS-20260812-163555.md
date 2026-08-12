## PLAN (carry-down) — the operator GRANTED a valid post-scan waiver on the cross-repo lineage red: **GATE 1 of your token is CLEAR.** The waiver is bounded to exactly this red on the slice-E PLAN lineage at pins `154cd87e` (Addendum-12, commit `3929c9c`) consuming `94b6440c` (J) — VOID if any of those bytes move — and I re-verified all of it at my seat (reviewed `154cd87e`, live post-stamp `5c180c00`, J `94b6440c`; owning m-2.implementer APPROVE `142252` + VP APPROVE `145249`, both on `154cd87e`, preceding the plan). **BUT YOUR TOKEN STILL HOLDS: GATE 2 — the cap-carrier cell you routed at `155122` — is OPEN.** I carried it UP to m-2 (my `163327`) as a normative call on A12.4.1, and it is not answered. **No `DISPATCH-IMPL` issues until BOTH the plan-review approves AND m-2 rules the cap-refusal carrier.** The waiver clears one gate; it does not touch the other, and disclosure never did. Keep folding rev2; the PLAN review continues on the `145249` approval. Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ROLE: Orchestrator Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-floor-slice-e-lineage-waived-cap-holds
PARENT_DISPATCH_ID: s4-floor-slice-e-plan-rev1
IN_REPLY_TO: ../../../../pdc/master/relays/s4-build-standup/PLAN-ORCHESTRATOR-PLANNER-WAIVER-VALID-GRANTED-SLICE-E-TOKEN-UNBLOCKED-R427-TO-V29-WAIT-20260812-163217.md
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: DISCHARGED for the lineage red by the operator's valid post-scan waiver (master `163217`); the cap-carrier cell awaits m-2's normative ruling (my `163327`). No token issues until both that ruling and the plan-review approve land. The release hold is ABSOLUTE.
DESIGN_DOC_ID: m2-addendum-12-transitive-collect-mono-gate-20260812
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m2-addendum12-154cd87e-lock-20260812
TARGET_DESIGN_SHA256: 154cd87ebdc0619cdf3a7172da9b46d5753888da68f03a10ed6c18c481ff4c77
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812
FROM: s4.orchestrator-planner
TO: s4-floor.planner
CC: operator, s4.orchestrator-reviewer, s4-floor.implementer, master.orchestrator-planner, m-2.planner
SUBJECT: PLAN — lineage red WAIVED (gate 1 clear, bounded to 154cd87e/94b6440c, void if moved); cap-carrier cell (gate 2) still open at m-2; token holds until both + plan-review approve

## 1. Gate 1 — the lineage red is WAIVED (verified at my seat)

The operator replied "just waive it, its getting fixed in 2.9 of the protocol" to a COMPLETE nine-row scan
(three triggers present); master granted a valid post-scan waiver (`163217`) and did not widen it. Bounded to:

```text
the cross-repo foreign-lock-target lineage class, ON THE SLICE-E PLAN LINEAGE, at:
  Addendum-12  154cd87e…  (commit 3929c9c)  consuming  J 94b6440c…    VOID if any byte moves
re-verified at my seat: reviewed 154cd87e (@3929c9c), live post-stamp 5c180c00, J live 94b6440c;
  approval lineage complete/ordered/single-pin/correct-owner:
  m-4.planner concur 141629 -> m-2.implementer APPROVE 142252 (owning) -> VP APPROVE 145249, all @154cd87e, all preceding the plan.
```

It does NOT touch class C or D, any other dispatch/slice/future plan; confers NO merge/seal/publication/
deployment/release; slice E's own PLAN gate stands. Keep `DESIGN_RECORD_KIND: design-doc`. **When your token
eventually issues, re-confirm the pins are unmoved — the waiver is void the moment any of those bytes changes.**

## 2. Gate 2 — the cap-carrier cell is STILL OPEN, and it is a token gate

Your `155122` cap-refusal carrier seam (J's typed-loud fatal vs A12.4.1's `CollectReport.warnings` line, mutually
destructive at `0db8fdd`) is a normative call on m-2's locked A12.4.1. I verified the conflict at the bytes and
routed it UP to m-2 (my `163327`) with your three options — I did NOT decide it, and neither do you. **Until m-2
rules which surface carries the cap-refusal disclosure, no `DISPATCH-IMPL` issues.** Your rev2 states this cell
OPEN with both killing arms (a fatal with NO disclosure fails; a disclosure with NO fatal fails); that stands.

## 3. The token's gate ledger — for the avoidance of a false unblock

```text
GATE            STATUS
lineage red     CLEAR   (operator waiver, master 163217, bounded to 154cd87e/94b6440c, void if moved)
cap-carrier     OPEN    (m-2 normative ruling on A12.4.1, my 163327)
plan review     IN PROGRESS (your Implementer, on the 145249 approval; rev2 answering R1/R2/R4)
```

The token issues only when all three are green AND the pins are unmoved. The waiver cleared one; do not read
"waiver granted" as "token unblocked." Your instinct to hold the token before any waiver existed was correct;
hold it still, on gate 2.

## 4. Tracking

`R-4.27` is superseded upstream — the operator reports the structural lint fix lands in **protocol v2.9**; it
converts to a TRACKED WAIT (when v2.9 lands, re-measure both lanes at their active dispatch roots and close it
against the new behaviour). Meanwhile the manual bytes-and-approval verification is the assurance of record for
any cross-repo plan, and by-class disclosure at the active dispatch root remains standing practice. C/B2 stays
landed. Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — carry-down of the operator waiver (master 163217) with independent re-verification of its pins (addendum-12 reviewed 154cd87e @ 3929c9c, live 5c180c00, J live 94b6440c; m-2.implementer approve 142252 + VP approve 145249 on 154cd87e) and reconciliation against the open cap-carrier cell (my 163327). This relay + its INDEX row ride one explicit-path docs-lane commit whose SHA lands after filing.
RELAY_LINT: per D-3.4 + corrected D-3.4(a) — per-file WITH freshness; `.relays/s4/INDEX.md` tail re-read before appending; `--index`; the slice-E lineage red is now operator-WAIVED (bounded, disclosed) rather than merely named; the third arm at the active dispatch root `.relays/s4/s4-floor-impl` is exit 1 / 32 (A=0/B=10/C=22/D=0) disclosed at `162400`. INDEX line 222 is the pre-existing sibling class, not mine.
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to this relay and `.relays/s4/INDEX.md`.

CARRY LIST (D-8.5):
- `.relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-SLICE-E-LINEAGE-WAIVED-GATE1-CLEAR-CAP-CARRIER-GATE2-HOLDS-20260812-163555.md` → `s4-floor.planner`, `s4-floor.implementer`
- GATE 1 CLEAR: operator valid post-scan waiver of the slice-E cross-repo lineage red (master 163217), bounded to Addendum-12 154cd87e (commit 3929c9c) consuming J 94b6440c, VOID if any byte moves; re-verified at my seat (reviewed 154cd87e, live 5c180c00, J 94b6440c; m-2.impl 142252 + VP 145249 approve). No merge/seal/publication/release conferred
- GATE 2 OPEN: the cap-carrier cell (155122) is a normative call routed to m-2 (my 163327), unanswered — token HOLDS until m-2 rules the cap-refusal carrier
- TOKEN LEDGER: lineage=CLEAR, cap-carrier=OPEN (m-2), plan-review=IN PROGRESS; token issues only when all green AND pins unmoved. Do not read "waiver granted" as "token unblocked"
- R-4.27 -> v2.9 tracked wait (re-measure both lanes at active dispatch roots when v2.9 lands); by-class disclosure remains standing; C/B2 landed; release hold ABSOLUTE
