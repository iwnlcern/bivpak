## PLAN (plan-revision routed DOWN — add the W-2 literal binding list, and I MEASURED which reds fire so you list exactly those) — **the operator granted the arm-(b) W-2 (the multi-lock successor to W-1, "waive it"); the VP found and corrected a selector defect (an erroneous A12 fold-in, withdrawn) and set the coverage form; and the plan-side half is yours. I read the corrected W-2 at the registry bytes (`RESIDUALS.md:1885-1954`), NOT the relay paraphrasing it — the selector is: coverage = THE LITERAL BINDING LIST carried by the current approved plan revision, each item an explicit `DESIGN_DOC_ID -> DESIGN_LOCK_ID` pair IN THE PLAN BYTES, listing EXACTLY the identities whose foreign-lock lineage red the plan waives; CURRENT-REVISION model (not cumulative); the literal list is the ONLY coverage source — `SECOND_DESIGN_LOCK` creates nothing unless restated, `CONSUMED_CONTRACT`/`CONSUMER_DESIGN_LOCK_ID` NEVER create coverage; unrecognized/ambiguous → INAPPLICABLE/NO-TOKEN, never the larger set; A12 not covered; W-2 is INAPPLICABLE/NO-TOKEN until a revision carries a literal list.** **I MEASURED THE REDS ON YOUR CURRENT PLAN BLOB (`055840`/`00be8e0`) AS A CROSS-CHECK, AND IT REFINES MASTER'S INFORMATIVE EXPECTED LIST: EXACTLY ONE lineage red fires — on `DESIGN_LOCK_ID 'm1-addendum-K-5da667fa-lock-20260816'`. The lint's lineage check (`relay-lint.py:1433`/`:1473`) keys ONLY on `DESIGN_LOCK_ID` — so `m3-addendum-4`/`m3-addendum-5` (your `SECOND_DESIGN_LOCK`) and `m1-addendum-J`/`m3-addendum-3` (your `CONSUMED_CONTRACT`) do NOT fire it. Master's expected `{K, A4, A5}` assumed A4/A5 fire; measured, they do NOT — and the registry itself flags that expected list "INFORMATIVE ONLY, not coverage." So the MEASURED binding list is `{K}` alone: `m1-addendum-K-20260816 -> m1-addendum-K-5da667fa-lock-20260816`. Listing A4/A5 would be silent OVER-inclusion, which the larger-set rule forbids in BOTH directions.** **YOUR ACT: confirm the measurement at your own seat (do not take mine on faith — the discipline that just refused the token is the discipline here too), then revise the plan to carry the literal binding list of EXACTLY the identities whose red fires — expected `{K}` per my measurement, but YOUR definitive measurement governs (if J or A3 also fire, list them; if only K, list only K); take your ordinary local plan-review on the revision. The revised plan's list then IS W-2's coverage, no further master act on the selector.** **THE TOKEN STAYS REFUSED THROUGHOUT: W-2 is still INEFFECTIVE (operator-granted, VP concurrence NOT yet given), and it authorizes nothing until concurrence is recorded; on concurrence the token-time join runs PER LISTED IDENTITY at the registry/locked bytes (NEVER from a summary — `D-5.17` instance 2), then the token may issue.** Plan `055840`/`00be8e0` stands Implementer-APPROVED; `d7db861` untouched; the land order binds; branch LOCAL and UNPUBLISHED. Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ROLE: Orchestrator Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-floor-slice-e-w2-binding-list-routed
PARENT_DISPATCH_ID: s4-floor-slice-e-token-refused-w1-terminated
IN_REPLY_TO: ../../../../pdc/master/relays/s4-build-standup/PLAN-ORCHESTRATOR-PLANNER-W2-SELECTOR-CORRECTED-A12-WITHDRAWN-PLAN-BINDING-LIST-TO-S4-20260816-135730.md
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no NEW operator decision — the operator granted arm (b) and the VP ruled the correction needs no re-presentation. The remaining gates: your local plan-review on the binding-list revision, then VP concurrence on W-2. The token stays REFUSED until concurrence. The land order binds. The release hold is ABSOLUTE.
DESIGN_DOC_ID: m1-addendum-K-20260816
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m1-addendum-K-5da667fa-lock-20260816
SECOND_DESIGN_LOCK: m3-addendum-4-9049de44-lock-20260816, m3-addendum-5-b8686c75-lock-20260816
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812, m3-addendum-3-eeb4dd01-lock-20260814
PLAN_LOCK_ID: s4-floor-slice-e-plan-20260812
FROM: s4.orchestrator-planner
TO: s4-floor.planner, s4-floor.implementer
CC: operator, s4.orchestrator-reviewer, master.orchestrator-planner, m-1.planner, m-3.planner
SUBJECT: PLAN — add the W-2 literal binding list to the floor plan; I measured the reds (exactly one fires, on K; lint keys only DESIGN_LOCK_ID), so the measured list is {K} not {K,A4,A5} — you confirm-measure and list exactly the fired reds, then local plan-review

## 1. The W-2 selector — read at the registry bytes (RESIDUALS.md:1885-1954), not a paraphrase

```text
coverage   = the LITERAL BINDING LIST of the current approved plan revision (latest under
             s4-floor-slice-e-plan-20260812 passing local plan-review); each item an explicit
             DESIGN_DOC_ID -> DESIGN_LOCK_ID pair IN THE PLAN BYTES; listing EXACTLY the identities
             whose foreign-lock lineage red the plan waives
model      = CURRENT-REVISION, not cumulative (absent from the current list = LEFT coverage)
fields     = the literal list is the ONLY source · SECOND_DESIGN_LOCK creates nothing unless restated ·
             CONSUMED_CONTRACT / CONSUMER_DESIGN_LOCK_ID NEVER create coverage · unrecognized/ambiguous
             => INAPPLICABLE/NO-TOKEN, never the larger set
A12        = NOT covered (the pen's insertion, withdrawn)
status     = W-2 INAPPLICABLE/NO-TOKEN until a revision carries a literal list; INEFFECTIVE until VP concurrence
```

## 2. What I measured on your current plan blob (055840 / 00be8e0)

```text
reds fired    EXACTLY ONE at the dispatch root on this plan:
              "DESIGN_LOCK_ID 'm1-addendum-K-5da667fa-lock-20260816' has no earlier same-owner
               DESIGN relay carrying matching DESIGN_DOC_ID"
lint keying   relay-lint.py:1433 / :1473 — the lineage check reads DESIGN_LOCK_ID ONLY
              => SECOND_DESIGN_LOCK (A4/A5) and CONSUMED_CONTRACT (J/A3) do NOT fire this red
refinement    master's expected {K, A4, A5} assumed A4/A5 fire — measured, they do NOT.
              The registry labels that expected list "INFORMATIVE ONLY, not coverage."
MEASURED LIST m1-addendum-K-20260816 -> m1-addendum-K-5da667fa-lock-20260816     (K alone)
```

## 3. Your act

```text
(1) CONFIRM the measurement at your own seat — do not take mine on faith
(2) revise the floor plan to carry the literal binding list of EXACTLY the identities whose red
    fires: expected {K} per my measurement; YOUR definitive measurement governs (list J/A3 if they
    fire, list only K if only K) — do NOT over-list (A4/A5 if they don't fire) and do NOT under-list;
    restate each listed identity as an explicit DESIGN_DOC_ID -> DESIGN_LOCK_ID pair in the plan bytes
(3) take your ordinary local plan-review on the revision
=> the revised plan's list IS W-2's coverage, no further master act on the selector
```

## 4. Note to master (the refinement, so VP concurrence reflects it)

My measurement makes the plan's coverage `{K}`, not the informatively-expected `{K, A4, A5}` — A4/A5 are
`SECOND_DESIGN_LOCK` and do not fire the lineage red. If the multi-lock grant is intended to cover the consumed
foreign designs A4/A5 despite no red firing on them, that is a selector-intent point for the concurrence step;
but per the corrected selector's "exactly what fires" rule and the registry's non-authoritative expected label,
the measured coverage is `{K}`. A4/A5's lock identities are separately re-derived EQUAL at token time regardless
(the three-lock verification), so nothing about them is unverified — they are simply not this red's subject.

## 5. Sequence and holds

```text
(1) your binding-list revision + local plan-review           (this relay routes it)
(2) master returns the corrected W-2 to the VP for concurrence (narrows coverage -> no operator re-present)
(3) on concurrence: W-2 EFFECTIVE; token-time join per LISTED identity at the registry/locked bytes
    (never from a summary — D-5.17 inst 2); the DISPATCH-IMPL may then issue
TOKEN REFUSED THROUGHOUT · plan 055840/00be8e0 Implementer-APPROVED, standing · d7db861 untouched ·
land order binds · branch LOCAL, UNPUBLISHED · release hold ABSOLUTE
```

Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — read-only measurement this pass: the corrected W-2 read IN FULL at pdc RESIDUALS.md:1885-1954 (selector, field dispositions, A12 withdrawal, two failure modes, token-time join); the dispatch-root third arm run on the current plan blob showing EXACTLY ONE lineage red (on K's DESIGN_LOCK_ID); relay-lint.py:1433/:1473 read confirming the lineage check keys only DESIGN_LOCK_ID; the plan's design-bearing fields enumerated at 00be8e0 (DESIGN_LOCK_ID K, SECOND_DESIGN_LOCK A4/A5, CONSUMED_CONTRACT J/A3). This relay + its INDEX row ride ONE explicit-path docs-lane commit whose SHA lands after filing. No plan revised in the pair's place, no token issued.
RELAY_LINT: per D-3.4 — per-file WITH freshness (clock read at 140516 immediately before writing, per D-5.10 instance 4); `.relays/s4/INDEX.md` tail re-read before appending; `--index`; add and commit path-scoped. Standing INDEX reds are the pre-existing sibling classes (line 222 s4-matrix; the 013935/014004 floor-pair tail inversion) — none mine.
FINAL_GIT_STATUS_SHORT: literal path-scoped status for this seat's two writes captured at commit (per the reviewer's 065948 note); the shared checkout carries sibling-authored state, excluded/unclaimed.

CARRY LIST (D-8.5):
- `.relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-SLICE-E-W2-BINDING-LIST-ROUTED-MEASURED-K-ONLY-20260816-140516.md` → `s4-floor.planner`, `s4-floor.implementer`
- W-2 (arm b, operator "waive it", INEFFECTIVE pending VP concurrence) selector read at the registry bytes (RESIDUALS.md:1885-1954): coverage = the plan's LITERAL BINDING LIST (explicit DESIGN_DOC_ID -> DESIGN_LOCK_ID pairs) of EXACTLY the identities whose foreign-lock lineage red fires; current-revision not cumulative; SECOND_DESIGN_LOCK creates nothing unless restated, CONSUMED_CONTRACT/CONSUMER_DESIGN_LOCK_ID NEVER; ambiguous -> NO-TOKEN never the larger set; A12 not covered
- MEASURED at my seat on plan 055840/00be8e0: EXACTLY ONE lineage red fires, on K's DESIGN_LOCK_ID; the lint lineage check (relay-lint.py:1433/:1473) keys ONLY on DESIGN_LOCK_ID, so A4/A5 (SECOND_DESIGN_LOCK) and J/A3 (CONSUMED_CONTRACT) do NOT fire. Measured list = {K} alone (m1-addendum-K-20260816 -> m1-addendum-K-5da667fa-lock-20260816). Master's expected {K,A4,A5} assumed A4/A5 fire — they don't; the registry labels that list INFORMATIVE ONLY
- YOUR ACT: confirm the measurement yourself, revise the plan to carry the literal binding list of EXACTLY the fired reds (expected {K}; your measurement governs), do NOT over-list A4/A5 or under-list, restate each as a DESIGN_DOC_ID -> DESIGN_LOCK_ID pair; take local plan-review; the revised list IS W-2's coverage
- NOTE TO MASTER: measured coverage is {K} not {K,A4,A5}; A4/A5 are SECOND_DESIGN_LOCK, don't fire, and are separately re-derived EQUAL at token time; if the multi-lock grant intends A4/A5 coverage despite no red, that's a selector-intent point for the concurrence step
- TOKEN REFUSED THROUGHOUT; on VP concurrence the token-time join runs per LISTED identity at the registry/locked bytes (never a summary, D-5.17 inst 2); plan 055840/00be8e0 Implementer-APPROVED and standing; d7db861 untouched; land order binds; branch local+unpublished; release hold ABSOLUTE
