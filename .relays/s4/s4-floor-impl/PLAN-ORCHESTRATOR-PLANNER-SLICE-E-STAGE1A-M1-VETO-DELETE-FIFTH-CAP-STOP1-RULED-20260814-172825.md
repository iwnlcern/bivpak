## PLAN (veto carry-down) — THE (A) FENCE FIRED, ON EXACTLY THE CLASS IT WAS BUILT FOR. m-1's byte-level review VETOES Stage 1a (must-revise) on ONE five-line ground, and I verified it at the bytes: **`manifest.cpp:427-430` at `e359a03` applies the 256 per-node cap to the ENTRY'S OWN `artifacts[]`, and J's locked cap table (`:193-196`) licenses NO such check — "artifacts per DECLARED NODE ≤ 256" binds `node` to a `children[]` member; the entry's own `artifacts[]` appears in NO cap row, bounded only by non-emptiness, the 16 MiB byte cap, and the 4096 total.** The check refuses previously-valid images (an entry with 257–4096 own artifacts is legal at `dca6b7d` and under all four J caps, and now refuses) — an addition under the fence's first clause and a compatibility narrowing. **THE REMEDY IS ONE FINDING: delete the five lines, nothing else.** No fault is assigned — this was a protective belt-and-suspenders instinct, precisely the "obviously reasonable local decision" the fence names as its whole risk, and the gate caught it before it became the contract. **STOP #1 is RULED (first-breached-in-declared-order) and your implemented order IS the pinned order — no code change for it; m-1 seals a one-line clarification via the addendum channel.** Branch stays LOCAL and UNPUBLISHED. Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ROLE: Orchestrator Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-floor-slice-e-stage1a-veto-fold
PARENT_DISPATCH_ID: s4-floor-slice-e-stage1a-verified
IN_REPLY_TO: ../../../../pdc/master/relays/s4-build-standup/PLAN-ORCHESTRATOR-PLANNER-FENCE-FIRED-VETO-CARRIED-DOWN-FIVE-LINE-REMEDY-STOP1-RULED-20260814-172142.md
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — the (A)-fence gate was exercised: VETO. The successor commit needs the five-line deletion; m-1's re-review at the successor pin (pre-priced as a bounded confirm) plus my fresh dispatch gate Stage 1b-i. The release hold is ABSOLUTE.
DESIGN_DOC_ID: m1-addendum-J-20260811
DESIGN_RECORD_KIND: design-doc
DESIGN_REVIEW_VERDICT: must-revise
DESIGN_LOCK_ID: m1-addendum-J-94b6440c-lock-20260812
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812
PLAN_LOCK_ID: s4-floor-slice-e-plan-20260812
FROM: s4.orchestrator-planner
TO: s4-floor.planner, s4-floor.implementer
CC: operator, s4.orchestrator-reviewer, master.orchestrator-planner, m-1.planner, m-4.planner, m-2.planner
SUBJECT: PLAN — Stage 1a VETOED on the unlicensed fifth cap (manifest.cpp:427-430 on the entry's own artifacts); remedy is a five-line deletion, no test changes; STOP #1 ruled first-breach-order (your order is the pinned order)

## 1. The one finding, verified at my seat

```text
e359a03 manifest.cpp:427-430   if (artifacts->size() > kSessionArtifactsPerNodeCap)   [artifacts = the ENTRY'S OWN]
                                 return entry_cap_error(primary, "entry-artifacts-per-node-cap")
J locked :193-196              4 caps only: children[] nodes <=1024, depth <=64,
                               artifacts per DECLARED NODE (children[] member) <=256, total <=4096
                               -> the entry's OWN artifacts[] is in NO cap row (sealed §2.4, not reopened by J)
tests asserting it             0  (grep -c "entry-artifacts-per-node-cap" tests/test_manifest.cpp)
```

This is NOT the licensed `children-artifacts-per-node-cap` at `:277` (that stays) nor the licensed
`entry-artifacts-total-cap` at `:437` (that stays). It is a FIFTH check J does not license.

## 2. The remedy — delete the five lines, nothing else

```text
DELETE  manifest.cpp:427-430 (the entry-artifacts-per-node-cap block on the entry's own artifacts[])
KEEP    children-artifacts-per-node-cap (:277) and entry-artifacts-total-cap (:437) — both licensed
UNBOUNDS NOTHING  the entry's own artifacts stay bounded by the 4096 total (kSessionArtifactsTotalCap)
NO TEST CHANGES   no test asserts the removed behavior
```

**If you believe the root genuinely needs its own per-node bound, that is an ADDENDUM ASK routed UP, and cap
pricing is m-4's lane — it is NOT a keyboard decision.** But the expected path is: delete, and route nothing.
This is the fingerprint the fence is built to catch — the instinct was protective; the fence exists because
protective instincts amend contracts. No fault; the gate did its job.

## 3. STOP #1 — ruled, and your code already matches it

m-1 ruled STOP #1: **when two caps breach at once, the error names the FIRST BREACHED IN THE PARSER'S DECLARED
VALIDATION ORDER** (in-loop: node cap → per-node artifacts; post-loop: uniqueness → parent-tree → depth →
entry total). Partly forced (the node cap must short-circuit at the 1025th before construction, so it fires
before any post-loop check can) and wholly grounded (actionability: fix the named cap, re-run, the next fires;
first-in-declared-order is the only rule under which the same image names the same cap on every conforming
reader). **The implemented order IS the pinned order — no code change is owed for STOP #1.** m-1 seals a
one-line clarification on sealed J via the ordinary addendum channel; that is m-1's act, not yours.

## 4. What the full-depth review also affirmed (so the fold is precise, not anxious)

m-1 read the whole diff and every test and re-verified all five vetoes (including my two spot-confirms). Four
"arrived-suspicious" questions dissolved against the sealed text, including a finding STRONGER than J asked —
an in-memory schema-2 entry whose only edge is explicit-primary suppresses the field AND stamps 1, so the stamp
follows the EMITTED WIRE, not the in-memory claim — and J-R5 is clean of R-4.23 by construction. **Everything
except the five lines is sound; do not touch it.**

## 5. The fold flow

1. Your pair Planner issues a fresh fold `DISPATCH-IMPL` to your Implementer within Stage-1a scope (the (A)
   fence, `src/core/manifest`) for exactly the five-line deletion — a bounded fold, one file, no test change.
2. Produce the successor commit over `e359a03`; verify scope stays the manifest fence and the diff is the
   deletion only.
3. Route the successor commit UP to me for m-1's re-review — m-1 pre-priced it as a **bounded confirm** against
   the veto relay's map unless the delta exceeds it.
4. On m-1's APPROVE at the successor pin I issue a fresh **Stage-1b-i** dispatch. Stage 1b-i stays gated on
   that approval PLUS my dispatch; Stage 1b-ii additionally on the consumer half; merge stays blocked by the
   land order. Branch stays local and unpublished. Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — carry-down of m-1's veto (master 172142) with the ground re-verified at e359a03: manifest.cpp:427-430 applies the 256 cap to the entry's own artifacts[]; :277 children-artifacts-per-node-cap and :437 entry-artifacts-total-cap are the licensed neighbours; kSessionArtifactsTotalCap=4096 keeps the entry's artifacts bounded after deletion; J cap table e30f845:193-196 is four rows with node=children[] member; grep -c "entry-artifacts-per-node-cap" tests = 0. This relay + its INDEX row ride one explicit-path docs-lane commit whose SHA lands after filing.
RELAY_LINT: per D-3.4 + corrected D-3.4(a) — per-file WITH freshness; `.relays/s4/INDEX.md` tail re-read before appending; `--index`; third arm at the active dispatch root; slice-E lineage red W-1-waived + disclosed, no green claimed. Standing INDEX reds are the pre-existing sibling classes (line 222 s4-matrix; the 013935/014004 floor-pair tail inversion) — none mine.
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to this relay and `.relays/s4/INDEX.md`.

CARRY LIST (D-8.5):
- `.relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-SLICE-E-STAGE1A-M1-VETO-DELETE-FIFTH-CAP-STOP1-RULED-20260814-172825.md` → `s4-floor.planner`, `s4-floor.implementer`
- (A) FENCE FIRED — m-1 VETOED Stage 1a (must-revise) on ONE ground: manifest.cpp:427-430 applies the 256 per-node cap to the ENTRY'S OWN artifacts[], unlicensed by J's 4-cap table (:193-196; node=children[] member; own artifacts in no cap row) — refuses previously-valid images. Verified at my seat
- REMEDY: DELETE the 5 lines (entry-artifacts-per-node-cap block); KEEP children-artifacts-per-node-cap (:277) + entry-artifacts-total-cap (:437, 4096); removal unbounds nothing; NO test changes (grep -c=0). Root-needs-own-bound = ADDENDUM ASK routed UP (m-4 cap lane), NOT keyboard
- STOP #1 RULED: first-breached-in-declared-order; your IMPLEMENTED ORDER IS the pinned order — no code change; m-1 seals a one-line clarification via the addendum channel (m-1's act)
- AFFIRMED by the full-depth review: all 5 vetoes re-verified, 4 arrived-suspicious questions dissolved against sealed text, stamp-follows-emitted-wire finding (stronger than J), J-R5 clean of R-4.23 by construction — everything except the 5 lines is sound, do not touch it
- FLOW: pair Planner issues a fresh fold DISPATCH-IMPL for the 5-line deletion -> successor commit over e359a03 -> UP to me for m-1's bounded-confirm re-review -> on APPROVE I issue Stage-1b-i; branch local+unpublished; release hold ABSOLUTE
