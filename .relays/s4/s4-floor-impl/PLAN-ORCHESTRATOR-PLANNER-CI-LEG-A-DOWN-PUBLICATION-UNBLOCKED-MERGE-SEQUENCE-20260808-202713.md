## DISPOSITION — the operator RULED CI-leg (a): merge on LOCAL-GREEN, the count gate is off the critical path (unhurried hygiene). Slice A's publication question is RESOLVED by this ruling — remote Actions is non-required, publish/update freely. Floor stack merges B1→A→C on the operator's per-candidate token; B1 is UNBLOCKED (its only blocker was the count gate) and I am handing it UP for condition-3 as the first stack merge. Merge ≠ release; the hold is ABSOLUTE.

ROLE: Orchestrator Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-floor-impl-2-ci-leg-a
PARENT_DISPATCH_ID: s4-floor-pair-plan
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no at this relay — the operator ruled (a); the per-candidate `DISPATCH MERGE` token is still owed downstream and is the operator's; the release hold is ABSOLUTE
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/SITREP-PLANNER-SLICE-A-PUBLICATION-QUESTION-20260807-152458.md
FROM: s4.orchestrator-planner
TO: s4-floor.planner
CC: operator, s4.orchestrator-reviewer, s4-floor.implementer
SUBJECT: PLAN — CI-leg (a) carried down; slice-A publication unblocked; the B1→A→C merge sequence and what each owes

The operator ruled CI-leg (a) (`202307`): **merge on local-green.** `main` is unprotected
(zero required checks), a red remote GitHub Actions run blocks no merge, local Docker CI
(charter `9d933a9`) is the governing Linux signal, and the count-gate repair is unhurried
hygiene — off the merge critical path.

**Slice A's publication question is RESOLVED by (a).** Your `152458` open item was: updating
PR #21 triggers Actions, which the local-CI charter restricts. Under (a), remote Actions is
non-required — publish/update PR #21 freely; a cosmetic remote red is not a blocker, and the
local-Docker green is the signal that counts. No further hold on slice-A publication.

**The floor stack merges B1→A→C, on the operator's per-candidate token, per stack order**
(verified ancestry at this seat: `ff63e52` ⊂ `798526c` ⊂ `ec9a2db`, all targeting main):
- **B1 #15 (`ff63e52`) — UNBLOCKED, handed UP now.** Its only blocker was the count gate
  (my `052818`), removed by (a). Re-verified at the bytes: both Step-3 fences live, no
  `.github` in its product diff, its panel + targeted recheck clean (conditions 1+2 met). I
  am routing it UP for master's condition-3 as the FIRST stack merge (`…202714`).
- **Slice A #21 (`798526c`) — second.** Amended head verified at your seat; publication now
  unblocked. Confirm its panel + recheck are complete and it is local-green at its head; on
  your confirmation I route its condition-3 UP next.
- **Slice C #22 (`ec9a2db`) — third, condition-3 already banked** (master `010500`).
- **B2 #23** continues its in-universe fold (rewrite_common admitted, per-session BL2-4,
  the rewrite/verify re-panel gating its head) — not part of this merge wave.

Merge-mechanics note for your awareness (master's condition-3 confirms it): the docs-lane
commits to `main` have diverged the branches, so each merge is clean-but-not-fast-forward
over disjoint paths (product vs `docs/`+`.relays/`) — no conflict expected, but a real
merge, which is master's ancestry/ff check to make, not a blocker.

No token here. Merge is the operator's per candidate; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product edits at this seat; this relay + its INDEX row, committed on the docs lane
FINAL_GIT_STATUS_SHORT: not claimed here — see the lane commit carrying this relay for the path-scoped set
