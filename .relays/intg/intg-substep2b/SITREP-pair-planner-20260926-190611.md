## SITREP — the operator waived the 2.9.5 Plan contract's body clauses for the 2b plan through sub-step 2b; a register row is requested; rev39 re-carried unchanged as plan-41

ROLE: Pair Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: intg-substep2b
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: intg-substep2b-plan-review-39 (unadmitted draft, sha256 ddb7cdc0e2e6ff23dd2b89ef0b0b4c34cae74fb37c52caee0bed67320a3a33d2)
RELATED_CONTEXT: intg-substep2b/PLAN-pair-planner-20260926-190529.md; intg-substep2b/PLAN-pair-planner-20260926-182900.md; ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260926-164725.md; ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260926-174349.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new gate — report-only; the operator has already ruled (word `a`); master is asked for a register row only; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
COMMISSION_TO: intg.pair-planner
CHARTER_DOC_ID: CH-intg-consent-fabric
PLAN_LOCK_ID: intg-substep2b-plan-20260915 @ sha256 d5a868d3fc8f020398b3b4ac6422f2d0c971f15c98d51bafdc009a5067ad4a80
FROM: intg.pair-planner
TO: master.master-planner
CC: master.master-reviewer, intg.pair-implementer, operator
SUBJECT: SITREP — rev39 d5a868d3 (MUST-H-1 as Task 8c; the operator's lighter re-gate as Task 9b) drew the implementer's must-revise on the 2.9.5 Plan contract (no bodies in a PLAN), new since 2.9.3 and absent from the migration note; the operator waived it for PL-intg-substep2b-20260915 through sub-step 2b (word `a`); register row requested; plan-41 re-carries the same artifact
BRIDGE: intg.pair-planner → master.master-planner (a register row for the operator's waiver); implementer CC (your review is answered in plan-41; please submit it with your 2.9.5 client); operator CC (your word recorded verbatim with its scope)

## What happened

rev39 `d5a868d3fc8f020398b3b4ac6422f2d0c971f15c98d51bafdc009a5067ad4a80` (4024 lines, commit 12ee0f9e) folds MUST-H-1 as your 164725 ordered it: c10, then the re-gate with c11 only if counts move, then the three owner reviews at the final head, then the GO.
The re-gate is the operator's "lighter regate pls": Task 9 is not re-run, there is no series, and a moved selftest population STOPs and routes up.
The implementer's review (`intg-substep2b-plan-review-39`, still an unadmitted draft, sha256 `ddb7cdc0…`) returned must-revise on two findings.
It also recorded that its independent contract review found no design, scope, boundary, order, acceptance or out-of-scope defect in rev39's declarations.
- MUST-2B-54: plan-40's grading heading named rev38's digest. That was my defect, and it is fixed in plan-41.
- MUST-2B-53: the 2.9.5 pair protocol's §Plan contract (pair-planner `protocol.md` :139-156, and the handoff-completeness line :437) says a PLAN carries no implementation bodies, full test bodies or operational scripts, and that execution does not bind snippet bytes. The section does not exist in the 2.9.3 kits. It arrived with today's migration, and your migration note (164725) listed the engine and linter differences but not this protocol change.
This plan's trust model is the opposite: its measurement tasks run byte-for-byte from blocks in the locked plan, Tasks 0 and 9 already ran from those bytes, and the resume and `t-oracle` chain is bound to them.

## The operator's ruling

I put three options to the operator: (a) keep the byte-bound runners for the rest of sub-step 2b under a waiver with a register row, the contract applying from the next sub-step's plan; (b) conform now; (c) move the blocks into a separate executable artifact, which I advised against as the same scripts relocated.
The operator answered, verbatim: `a` (2026-09-26, in this seat's session).
Scope: `PL-intg-substep2b-20260915` only, through sub-step 2b's close. It covers every executable body the plan carries: the 21 named BLOCKs, including rev39's new `c10-mutants.sh` and `regate.sh`; the RUN blocks task-0 / 9 / 10 / 11; and the inline code of Tasks 1–8c. The rest of the 2.9.5 contract review stands.

## The ask

A register row for this waiver, in the form you choose.
Nothing else moves: rev39 is re-carried unchanged as plan-41 (`intg-substep2b/PLAN-pair-planner-20260926-190529.md`) for the implementer's exact-hash verdict. After an approve comes my digest word to you, your five-field carry, then impl-13 (Step 0′ → Task 8c → Task 9b).
The implementer's impl-12 return (`457b14fa…`) and this review are both still unadmitted; only that seat can submit them.
Merge ≠ push ≠ publication ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: none — report-only; this relay and its INDEX row (path-scoped commit follows), no trailer; plan unchanged at 12ee0f9e; product bytes none
RELAY_LINT: engine-rendered submission; per-file 2.9.5 `relay-lint.py --no-freshness` on the draft; python-written; upstream listed as its own command before submit
FINAL_GIT_STATUS_SHORT:
 M .relays/intg/SEATS.md
Literal path-scoped status (`.relays/intg` and the sprint docs, tracked files) at write time; the shared tree carries other seats' untracked relays, not claimed clean here.
