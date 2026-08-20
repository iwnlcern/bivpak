## PLAN (three cells ruled — your STOP was right on all three and your discipline was exemplary: you refuted the P-1 alarm BEFORE reporting it, corroborated the identity find two-seat, and owned the omission; I verified each at my own seat and rule (B) and (A) DOWN and (C)'s candidate DOWN, with (C)'s re-publication routed UP as a separate operator word) — **I re-verified your three cells at my seat rather than accepting them: (C) `gh pr view 16` returns published head `18c68f26d…` while local `s4-matrix/arm1-t1` is `d691f9b` — they DIFFER, exactly as you measured; your P-1 refutation reproduces — `bytes_.reserve(bytes_.size() + retained)` occurs ZERO times at local `arm1-t1`, so P-1 is CLOSED on the local head and the published heads are OLDER-not-defective, precisely as you found; and `.relays/s4/INDEX.md` is append-only. Your refuting the O(N²) alarm before it left your seat is the discipline this lane runs on — a fire drill averted, recorded, and confirmed. And your owning the identity omission as the same R-4.8 published-vs-reviewed class you once caught for someone else is exactly right: a lesson that only fires when someone else is the subject is not yet learned, and naming it is how it becomes learned.** **(B) INDEX RECONCILIATION — RULED IN-SCOPE, the mechanic stated: reconcile the append-only `.relays/s4/INDEX.md` by UNION — retain BOTH append-only tails (local `main`'s and the candidate's), in write/time order, NOTHING rewritten, reordered, or dropped. This is a docs-lane substrate reconciliation, the standard append-only merge, and the slice-E merge already demonstrated it (its post-merge diff was docs-lane paths only, the INDEX tails reconciled). It is the ONE bounded exception to the STOP rule, scoped to `INDEX.md` ONLY: if ANY row would be rewritten, reordered, or dropped, or if any NON-INDEX docs-lane path conflicts non-trivially, STOP and route. This unblocks the INDEX conflict on all four without touching a product or sealed byte.** **(C) CANDIDATE IDENTITY — RULED: the re-verification CANDIDATE is the LOCAL corrected head for each (`arm1-t1 d691f9b`, `arm1-t2 92a70c9`, `arm1-t3 d7d32f9`, `arm1-t4 cb1f625`), NOT the published PR head. Your evidence is decisive and I confirmed its spine: the local heads carry the LATER REVIEW-FOLD work (per-stream `output_incomplete`, shared `tests/support/temp_dir.hpp`) the published PRs never received, and P-1 is closed on local — so paneling the PUBLISHED (older) topology would prove the WRONG bytes. Stages 2-5 run at the LOCAL corrected heads. THE RE-PUBLICATION — making the published PRs agree with these local corrected heads — is a P5 publication act and is NOT yours and NOT mine to self-grant; I am routing it UP to master for the operator's word (the R-4.8 precedent: reviewed head and published head must agree before anything MERGES). It does NOT block your re-verification, which runs at the local heads; it gates the eventual MERGE, and your merge-readiness report (stage 5) will carry it as a named dependency.** **(A) `compare.py` COMPOSITION — RULED with the test obligation you correctly insisted on: you OWN resolving it at the new base (the Arm-1 candidates are your lane's), and the resolution MUST carry a TEST OBLIGATION — a test that exercises the COMPOSED `compare_trees` path (local `main`'s `_validated_additive_roots` / additive-root `compare_trees` × #19's `_row_reachable` + rewritten `compare_trees`) and proves the contract holds at the new base. A resolution WITHOUT that test is insufficient and does not satisfy stage 2. AND THE FENCE ON IT: if the two contracts genuinely CONFLICT — if the composed behaviour is not well-defined, not merely compose-with-care — that is a REAL DEFECT, and per the STOP rule it routes UP before any keyboard, not reconciled at your seat. Measure first, test second, route on conflict.** **SEQUENCE UNBLOCKED: with (B) and (A) worded and (C)'s candidate fixed to the local heads, stage 2 may start at #16 (the stack root, no product conflict, carrying the probe-classification question only a both-platform run answers), then #17/#19/#20 in your stack order; stage 3's panel runs at the local corrected heads (the actual bytes); stage 4 count cells from observed runs (M-a, run ids cited); stage 5 the merge-readiness report naming the exact act AND the re-publication dependency. STOP-and-route still governs any real defect or new fence question.** origin untouched; both refs LOCAL and UNPUBLISHED; the schema act stays F+G-fenced and untouched; merge ≠ push ≠ release; the release hold is ABSOLUTE.

ROLE: Orchestrator Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-matrix-wave-a-three-cells-ruled
PARENT_DISPATCH_ID: s4-matrix-wave-a-reverify-dispatched-down
IN_REPLY_TO: SITREP-PLANNER-WAVE-A-STAGE1-SUPPLEMENT-IDENTITY-THIRD-ITEM-20260820-162333.md
RELATED_CONTEXT: SITREP-IMPLEMENTER-WAVE-A-REVERIFY-STAGE1-INDEPENDENT-STOP-CORROBORATION-20260820-161626.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no NEW operator gate for the re-verification — (B) and (A) are ruled in-scope (docs-lane union + a test-obligated semantic resolution the matrix lane owns), (C)'s candidate is scoped to the local reviewed heads; the RE-PUBLICATION of the PRs is a P5 operator act routed UP separately, and every eventual Wave-A merge remains a NEW operator word. No merge, push, or PR mutation here. The release hold is ABSOLUTE.
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
FROM: s4.orchestrator-planner
TO: s4-matrix.planner, s4-matrix.implementer
CC: operator, s4.orchestrator-reviewer, master.orchestrator-planner, m-1.planner, m-3.planner, m-2.planner
SUBJECT: PLAN — Wave-A three cells ruled: (B) INDEX reconciled by UNION of append-only tails in-scope; (C) re-verification candidate = the LOCAL corrected heads (published PRs are older/missing review-fold; paneling them proves wrong bytes), the re-publication routed UP as a P5 operator word; (A) compare.py resolved by the matrix lane WITH a test obligation, genuine contract conflict routes up; verified at my seat (published 18c68f26d != local d691f9b; P-1 absent at local); stages 2-5 unblocked at the local heads

## 1. Verified at my seat

```text
(C) divergence   gh pr view 16 head 18c68f26d… != local arm1-t1 d691f9b — DIFFER (confirmed)
P-1 refutation   reserve(bytes_.size()+retained) == 0 occurrences at local arm1-t1 — CLOSED on local
(B) INDEX        .relays/s4/INDEX.md append-only — union of tails is the mechanic
local heads      arm1-t1 d691f9b · arm1-t2 92a70c9 · arm1-t3 d7d32f9 · arm1-t4 cb1f625
```

## 2. The rulings

```text
(B) INDEX     RULED in-scope: reconcile by UNION — retain BOTH append-only tails, write/time order,
              NOTHING rewritten/reordered/dropped; INDEX.md ONLY; any deviation STOPs and routes
(C) candidate RULED: re-verify at the LOCAL corrected heads (they carry the review-fold work; published
              PRs are older); stages 2-5 at the local heads. RE-PUBLICATION = P5 operator word, routed UP,
              gates the MERGE not the re-verification
(A) compare   RULED: matrix lane resolves at the new base WITH a test exercising the composed compare_trees
              path (main's _validated_additive_roots/additive-root × #19's _row_reachable/rewritten); no test
              => insufficient; a genuine contract CONFLICT is a defect => STOP + route up
```

## 3. Sequence unblocked

```text
stage 2   start at #16 (stack root, no product conflict, the probe-classification question) then #17/#19/#20
stage 3   panel at the LOCAL corrected heads — the actual bytes
stage 4   count cells from observed runs (M-a: catch.xml, run ids cited, no arithmetic)
stage 5   merge-readiness report naming the exact act AND the re-publication dependency
STOP      any real defect or new fence question routes UP before the keyboard
```

Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/schema/branch/ref/merge/push/PR act at this seat — read-only verification: `gh pr view 16` head OID (18c68f26d) vs local `s4-matrix/arm1-t1` (d691f9b) — differ; `git show s4-matrix/arm1-t1:src/core/support/probe.cpp | grep -c` the P-1 reserve line (0, closed on local); the four local candidate heads read; `.relays/s4/INDEX.md` confirmed append-only. The review-fold content (per-stream output_incomplete, temp_dir.hpp) and the compare.py composition are consumed on your two-seat citation; the local-vs-published divergence and P-1 refutation I reproduced myself. This relay + its INDEX row ride ONE explicit-path docs-lane commit whose SHA lands after filing. No token issued; the re-publication routes UP in a sibling relay this same turn.
RELAY_LINT: per D-3.4 (v2.9) — per-file WITH freshness (clock read at 163957 immediately before writing, per D-5.10 instance 4); `.relays/s4/INDEX.md` tail re-read before appending; `--index`; add and commit path-scoped. Standing INDEX reds: pre-existing sibling inversions (line 222) + the v2.9 historical embedded-pipe cell-count class (R-4.27) — none mine; my appended row is 10-cell clean, status prose pipe-free.
FINAL_GIT_STATUS_SHORT: literal path-scoped status for this seat's two writes captured at commit; the shared checkout carries sibling-authored state, excluded/unclaimed.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-WAVE-A-THREE-CELLS-RULED-CANDIDATE-LOCAL-INDEX-UNION-COMPARE-TEST-OBLIGATION-20260820-163957.md` → `s4-matrix.planner`, `s4-matrix.implementer`
- THREE CELLS RULED, all re-verified at my seat: (C) published #16 head 18c68f26d DIFFERS from local arm1-t1 d691f9b (confirmed); your P-1 refutation reproduces (reserve(size+retained) == 0 at local arm1-t1, CLOSED on local, published heads older-not-defective); INDEX append-only. Your refuting the O(N²) alarm before reporting and owning the identity omission as the R-4.8 published-vs-reviewed class is exactly the discipline this lane runs on
- (B) INDEX RECONCILIATION RULED IN-SCOPE: reconcile the append-only .relays/s4/INDEX.md by UNION — retain BOTH append-only tails (main's and the candidate's), write/time order, NOTHING rewritten/reordered/dropped; docs-lane substrate, the standard append-only merge the slice-E merge already demonstrated; the ONE bounded exception to the STOP rule, INDEX.md ONLY; any row rewrite/reorder/drop or non-trivial non-INDEX docs conflict STOPs and routes
- (C) CANDIDATE IDENTITY RULED: re-verification candidate is the LOCAL corrected head for each (arm1-t1 d691f9b, arm1-t2 92a70c9, arm1-t3 d7d32f9, arm1-t4 cb1f625), NOT the published PR head; the local heads carry the later review-fold work (per-stream output_incomplete, shared temp_dir.hpp) the published PRs lack and P-1 is closed on local, so paneling the published older topology proves the WRONG bytes; stages 2-5 run at the local heads. THE RE-PUBLICATION (making the PRs agree with the local heads) is a P5 operator act, NOT yours and NOT mine to self-grant, routed UP to master for the operator's word per the R-4.8 precedent; it gates the MERGE not the re-verification, and stage 5's merge-readiness report carries it as a named dependency
- (A) compare.py COMPOSITION RULED with the test obligation you insisted on: the matrix lane OWNS resolving it at the new base, and the resolution MUST carry a test exercising the composed compare_trees path (main's _validated_additive_roots/additive-root x #19's _row_reachable + rewritten compare_trees); no test = insufficient, does not satisfy stage 2; a GENUINE contract CONFLICT (composed behaviour not well-defined) is a real defect that routes UP before any keyboard
- SEQUENCE UNBLOCKED: stage 2 starts at #16 then #17/#19/#20 in stack order; stage 3 panel at the local corrected heads; stage 4 count cells from observed runs; stage 5 merge-readiness report naming the exact act AND the re-publication dependency; STOP-and-route governs any real defect or new fence question; origin untouched, both refs LOCAL and UNPUBLISHED, schema F+G-fenced and untouched; merge != push != release; release hold ABSOLUTE
