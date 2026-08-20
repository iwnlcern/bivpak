## SITREP (STAGE-1 SUPPLEMENT) — the Implementer's `161626` corroboration caught a THIRD blocking item my `161137` missed, and it is correct: the PUBLISHED PR heads for #16/#17/#19 are NOT the locally measured candidate bytes (and #20's identical tip sits on stale published ancestry), so "the ACTUAL SHAs that would merge" is currently ambiguous and stage 3 cannot be satisfied honestly until it is ruled. I verified it independently, I own the omission, and I record one alarming hypothesis I formed and then REFUTED so nobody re-derives it: the published heads do NOT carry the P-1 O(N²) regression

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-matrix-wave-a-reverify-stage1-supplement
PARENT_DISPATCH_ID: s4-matrix-wave-a-reverify-stage1-impl-corroboration
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-WAVE-A-REVERIFY-STAGE1-INDEPENDENT-STOP-CORROBORATION-20260820-161626.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no new operator gate — measurement only; this consolidates the pair's THREE blocking cells into one ask so you rule once rather than thrice; no merge, push, re-base, conflict resolution, or PR mutation occurred; the release hold is ABSOLUTE
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
FROM: s4-matrix.planner
TO: s4.orchestrator-planner
CC: operator, s4.orchestrator-reviewer, master.orchestrator-planner, s4-matrix.implementer
SUBJECT: SITREP — identity item corroborated and owned; a refuted alarm recorded; the pair's three blocking cells consolidated into one ask

## 1. The Implementer is right, and this is my omission

`161626` reports that the published PR heads differ from the local candidate heads. I
verified it at my seat rather than accepting it on report:

```text
#16  s4-matrix/arm1-t1   published 18c68f26d   local d691f9be8   DIFFER
#17  s4-matrix/arm1-t2   published 616bc4f20   local 92a70c9cd   DIFFER
#19  s4-matrix/arm1-t3   published 80a5fc82c   local d7d32f94c   DIFFER
#20  s4-matrix/arm1-t4   published cb1f6254e   local cb1f6254e   SAME tip, stale ancestry beneath
```

My `161137` measured the four LOCAL branches against local `main` and never compared
them to what the PRs actually publish. That is the same class of gap I caught during
R-4.8 — where the published PR sat two commits behind the reviewed head and merging it
would have landed bytes the review window failed — and I did not apply the lesson to my
own Stage-1 sweep. The Implementer's independent pass caught it. Recording it plainly
because a lesson that only fires when someone else is the subject has not actually been
learned.

**Why it blocks:** stage 3 requires "panel + condition-3 re-satisfied at the ACTUAL SHAs
that would merge." With two live topologies, that phrase has no unique referent. Any
panel, suite receipt, or count-gate cell produced now would have to name which topology
it proves, and the two are not interchangeable.

## 2. An alarming hypothesis I formed and REFUTED — recorded so it is not re-derived

Local T1 carries two commits absent from published #16: `bbe824a fix(review): harden
subprocess capture and test fixtures` and `d691f9b fix(review): restore geometric
subprocess capture growth`. `d691f9b` deletes exactly
`bytes_.reserve(bytes_.size() + retained);` — which is **P-1**, the O(N²) capture
regression the 2026-08-08 Wave-A panel ruled must-fix. The obvious inference is that the
published head still carries a closed must-fix defect. **That inference is WRONG, and I
checked before reporting it:**

```text
reserve(bytes_.size() + retained)  at published 18c68f26d : ABSENT
                                    at local     arm1-t1   : ABSENT
bbe824a ADDS the line; d691f9b REMOVES it — introduced and fixed inside the local pair
```

So P-1 is closed on **both** topologies; the published heads are older, not defective.
Stating the refutation explicitly because the hypothesis is one any careful reader would
form from the commit messages alone, and it would have started a fire drill.

**What the difference actually is** (net, published #16 → local T1, `src/`+`tests/`):
`ByteCapture` gains a per-instance `bool& output_incomplete_` — replacing the single
shared truncation flag the Wave-A test-coverage lens flagged as not directly covered —
plus `reference_wrapper` reduced to a plain reference, a new shared
`tests/support/temp_dir.hpp`, and the corresponding test updates. In other words the
local stack carries **later review-fold work** that the published PRs never received.
That is a real difference in reviewed substance, not a bookkeeping mismatch — which is
precisely why it needs a ruling rather than a quiet pick.

## 3. The pair's THREE blocking cells, consolidated — please rule once

Both seats independently reproduced (A) and (B); (C) is the Implementer's find, verified
by me. The re-verification cannot resume until all three are worded, because each one
gates a different stage.

```text
(A) compare.py composition   #19/#20   main's _validated_additive_roots / additive-root
                                       compare_trees  ×  #19's _row_reachable + rewritten
                                       compare_trees. A semantic contract question with a
                                       test obligation — not a mechanical pick. Assign an
                                       owner and bound the act.            → gates stages 2-5 for #19/#20
(B) INDEX reconciliation     ALL FOUR  every candidate conflicts on the append-only
                                       .relays/s4/INDEX.md; no re-based head can exist
                                       without reconciling it, and the STOP rule reserves
                                       that act. State the allowed mechanic (retain both
                                       append-only tails, nothing rewritten or reordered)
                                       or choose an alternate.             → gates stages 2-4 for ALL
(C) candidate identity       #16/#17/  published ≠ local for three; #20's tip sits on
                             #19/#20   stale published ancestry. Name which topology is
                                       THE candidate, and who holds re-publication /
                                       re-stack authority if it is the local one.
                                                                            → gates stage 3 for ALL
```

My recommendations, offered as recommendations: **(B1)** rule the mechanical INDEX
resolution in-scope with the rule stated in your reply; **(C)** name the LOCAL corrected
heads as the candidates — they carry the review-fold work the published PRs lack, so
paneling the published topology would prove the wrong bytes — and route the
re-publication as its own operator word, since it is a P5 act and the R-4.8 precedent is
that reviewed head and published head must agree before anything merges; **(A)** is not
mine to recommend an answer to, only to flag that it needs a test obligation attached,
not just a resolution.

## 4. Standing state

Nothing ran. No re-base, no conflict resolution, no merge, no push, no PR mutation, no
suite or Docker run, no count-gate derivation, no schema-act contact (F+G-fenced and
untouched). Stage 2 remains ready to start with #16 the moment (B) and (C) are worded —
it is the stack root, has no product conflict, and carries the probe-classification
question that only a both-platform run can answer. `origin` untouched; merge ≠ push ≠
release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: read-only verification only — `gh pr view` head OIDs for #16/#17/#19/#20, `git fetch` of the published #16 head, `git log`/`git show`/`git diff` across published and local heads. NO re-base, NO conflict resolution, NO merge, NO push, NO branch or PR mutation, NO product/test edit. Docs lane: this relay + its INDEX row ride one explicit-path commit (SHA lands after filing).
FINAL_GIT_STATUS_SHORT:
none — clean tree (matrix-seat paths; the shared checkout carries sibling-authored state, excluded/unclaimed)
Fresh at 20260820-162333 before this relay + INDEX write; this relay and the INDEX row are this seat's working-tree delta at commit time.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/SITREP-PLANNER-WAVE-A-STAGE1-SUPPLEMENT-IDENTITY-THIRD-ITEM-20260820-162333.md` → TO `s4.orchestrator-planner`
- Implementer `161626`'s identity finding CORROBORATED at my seat and OWNED as my `161137` omission (same class as the R-4.8 published-vs-reviewed gap I caught for someone else and missed for myself)
- REFUTED ALARM recorded: published heads do NOT carry the P-1 O(N²) regression — `bbe824a` adds the reserve line and `d691f9b` removes it, both inside the local pair; P-1 closed on BOTH topologies. The real difference is later review-fold work in local (per-stream `output_incomplete`, shared `temp_dir.hpp`) absent from the published PRs
- THREE cells consolidated for ONE ruling: (A) `compare.py` composition + test obligation → #19/#20; (B) INDEX reconciliation mechanic → ALL, gates stages 2-4; (C) candidate identity + re-publication authority → ALL, gates stage 3
- recommendations: (B1) mechanical resolution in-scope with the rule stated; (C) local corrected heads as THE candidates with re-publication as its own operator word per the R-4.8 precedent; (A) needs an owner AND a test obligation
- stage 2 ready to start at #16 on (B)+(C); nothing re-based/merged/pushed/resolved; schema F+G-fenced; release hold ABSOLUTE
