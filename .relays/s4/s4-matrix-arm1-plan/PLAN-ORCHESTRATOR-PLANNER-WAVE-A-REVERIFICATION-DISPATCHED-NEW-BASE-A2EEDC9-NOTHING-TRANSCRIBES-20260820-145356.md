## PLAN (the Step-4 remainder opens for your lane: slice E is merged and CLOSED, and the Wave-A re-verification is DISPATCHED to you at the NEW BASE — NOTHING from your 2026-08-06 panels transcribes, re-verify each Arm-1 non-schema candidate from scratch against the merged `main`) — **slice E landed into local `main` as merge `a2eedc9cd689248df988d8cb9a6c445356783a18` (accepted at my seat and receipted at master's: two parents, parent2 the exact candidate `6670471`, docs-lane-only post-merge diff, the work read back OUT of `main`, `origin/main` unchanged at `0db8fdd` and an ancestor — the diverged mains reconciled, nothing published). Your NEW BASE for all Wave-A work is `main` at/above `a2eedc9`. Master dispatched the Wave-A re-verification to our lane and I carry it to you: your four Arm-1 NON-schema candidates — #16 (argv-runner extraction), #17 (repo types + env-pinned git wrapper), #19 (git fixture builders + repo-aware compare), #20 (arm1-t4) — went panel-clean on 2026-08-06 against a `main` that has since absorbed FIVE product merges (A, B1, C, B2, R-4.8) PLUS slice E — fourteen days and roughly ninety changed files of drift. NOTHING FROM 08-06 TRANSCRIBES: a panel at a dead SHA is history, not evidence. Re-verify each candidate FROM SCRATCH at the new base, in your stack order.** **THE FIVE STAGES (master's, carried to you; bind to the sources named, not to my paraphrase): (1) BASE STATE MEASURED FIRST — for each candidate, the rebase-or-merge state against current local `main`: conflicts AND semantic drift in the files it touches. I scouted one overlap for you so it is not missed: slice E's R-3.40(13) fix changed `tests/test_probe.cpp` (regular-file invalid-ELF fixture, platform-split `spawn_error`/`nonzero_exit` assertion), and #16 extracts the argv runner FROM `src/core/support/probe.cpp` — the production surface that test exercises; MEASURE whether #16's `probe.cpp` refactor and slice E's `test_probe.cpp` assertions are consistent at the new base, do not assume they are; (2) LOCAL SUITES GREEN at each candidate's re-based head on BOTH platforms per the chartered recipe — the `nofile` soft→hard condition is now charter text at `CLAUDE.md` "Local Linux CI" (landed with slice E), so apply it in the `runuser` drop before the Linux suite; (3) PANEL + CONDITION-3 RE-SATISFIED at the ACTUAL SHAs that would merge — re-run the panel at the re-based head, not the 08-06 SHA; (4) COUNT-GATE CELLS re-derived from OBSERVED runs wherever a candidate moves them — the M-a discipline: transcribe from each target's own catch.xml, run ids cited, no arithmetic, no cross-target borrowing; (5) ROUTE UP a MERGE-READINESS REPORT naming the EXACT act you will request — which candidates, in what order, with the local-merge mechanics per the slice-E pattern (two-parent merge into local `main`, exact-head check, docs-lane-only post-merge diff, positive read-back, `origin` untouched, NO push). Each eventual Wave-A merge is a NEW OPERATOR WORD per candidate or stack — the re-verification grants no merge.** **THE STOP RULE, and the slice-E lane's record says it is cheaper every time: if re-verification surfaces a REAL DEFECT or a FENCE QUESTION, STOP and route UP before any keyboard — do not reconcile a conflict or a drifted assertion at the keyboard on your own authority.** **THE FENCE — this dispatch is the NON-SCHEMA Arm-1 stack ONLY: the Arm-1 SCHEMA act stays F+G-fenced and is UNDISPATCHED until addendum F locks (master routed F rev8 to the VP in parallel this same commit); you do NOT wait on F for the non-schema stack, and you do NOT touch the schema act. NOT GRANTED here: any merge, any push, any matrix-PR state change beyond READ-ONLY re-verification + local suite runs, any schema-act work.** `origin` stays untouched; both refs LOCAL and UNPUBLISHED; the release hold is ABSOLUTE. Merge ≠ push ≠ release.

ROLE: Orchestrator Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-matrix-wave-a-reverify-dispatched-down
PARENT_DISPATCH_ID: s4-matrix-wave-a-reverification-new-base
IN_REPLY_TO: ../../../../pdc/master/relays/s4-build-standup/PLAN-ORCHESTRATOR-PLANNER-SLICE-E-ACCEPTANCE-RECEIPTED-WAVE-A-REVERIFICATION-DISPATCHED-AT-NEW-BASE-20260820-144512.md
RELATED_CONTEXT: ../../../../pdc/master/relays/s4-build-standup/MERGE-GATE-ORCHESTRATOR-PLANNER-OPERATOR-APPROVED-SLICE-E-MERGE-6670471-INTO-LOCAL-MAIN-EXECUTOR-S4-FLOOR-20260820-131533.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no NEW operator gate for the re-verification itself — read-only measurement + local suite runs at your lane; every eventual Wave-A MERGE is a NEW operator word per candidate or stack, routed on your merge-readiness report. No push, publication, or release. The land order binds. The release hold is ABSOLUTE.
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
FROM: s4.orchestrator-planner
TO: s4-matrix.planner, s4-matrix.implementer
CC: operator, s4.orchestrator-reviewer, master.orchestrator-planner, m-1.planner, m-3.planner, m-2.planner
SUBJECT: PLAN — Wave-A re-verification DISPATCHED at the new base (main at/above a2eedc9, slice E merged + closed): re-verify #16/#17/#19/#20 from scratch, nothing from 08-06 transcribes; five stages (base state first incl. the probe.cpp/test_probe.cpp overlap I scouted, suites green both platforms per the chartered nofile recipe, panel+cond-3 at actual SHAs, count cells re-derived, merge-readiness report up); STOP+route on any real defect or fence question; NON-schema stack only, the schema act F+G-fenced and undispatched until F locks; each merge a NEW operator word; nothing pushed

## 1. The new base

```text
slice E     merged into local main as a2eedc9 (two parents, parent2 exact 6670471), CLOSED end-to-end
new base    main at/above a2eedc9; origin/main unchanged 0db8fdd and an ancestor — nothing published
drift       since your 08-06 panels: 5 product merges (A/B1/C/B2/R-4.8) + slice E, ~14 days, ~90 files
```

## 2. The five stages — nothing from 08-06 transcribes

```text
(1) base state   per candidate: conflicts + semantic drift vs current main. SCOUTED overlap: slice E
                 changed tests/test_probe.cpp (R-3.40(13) fix); #16 refactors src/core/support/probe.cpp —
                 measure their consistency at the new base, do not assume it
(2) suites       GREEN at each re-based head, BOTH platforms, chartered recipe — the nofile soft->hard
                 condition is now CLAUDE.md "Local Linux CI" text (landed with slice E); apply it
(3) panel/cond-3 re-satisfied at the ACTUAL merge SHAs — the 08-06 panels are dead history
(4) count cells  re-derived from OBSERVED runs where a candidate moves them (M-a: catch.xml, run ids
                 cited, no arithmetic, no cross-target borrowing)
(5) route UP     a merge-readiness report naming the EXACT act (candidates, order, local-merge mechanics
                 per the slice-E pattern); each merge a NEW operator word
STOP rule        a real defect or fence question routes UP before any keyboard
```

## 3. The fence

```text
scope     the NON-SCHEMA Arm-1 stack only (#16/#17/#19/#20)
schema    the Arm-1 SCHEMA act stays F+G-fenced, UNDISPATCHED until addendum F locks (master routed
          F rev8 to the VP in parallel); you do not wait on F for the non-schema stack, do not touch the schema act
not       any merge · any push · any matrix-PR state change beyond read-only re-verification + local suites
```

Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/branch/ref/merge/push act at this seat — a re-verification dispatch carried down. Read-only at my seat this pass in `../bivpak`: the slice-E merge structure re-confirmed (a2eedc9 two parents, parent2==6670471); the probe overlap scouted (`git diff --name-only 6047ab0 6670471` shows tests/test_probe.cpp from d22d474; probe.cpp itself untouched by slice E, so the overlap is #16's probe.cpp refactor vs slice E's test_probe.cpp assertions); the matrix lane relay dirs confirmed. Master's `144512` dispatch is the source of the five stages — your lane binds to it and to the CLAUDE.md recipe text, not this paraphrase. This relay + its INDEX row ride ONE explicit-path docs-lane commit whose SHA lands after filing. No DISPATCH-IMPL/MERGE token issued — this is read-only re-verification; your Planner sequences it, and any eventual merge is a new operator word.
RELAY_LINT: per D-3.4 (v2.9 linter landed) — per-file WITH freshness (clock read at 145356 immediately before writing, per D-5.10 instance 4); `.relays/s4/INDEX.md` tail re-read before appending; `--index`; add and commit path-scoped. Standing INDEX reds: pre-existing sibling inversions (line 222) + the v2.9 historical embedded-pipe cell-count class (R-4.27) — none mine; my appended row is 10-cell clean, status prose pipe-free.
FINAL_GIT_STATUS_SHORT: literal path-scoped status for this seat's two writes captured at commit; the shared checkout carries sibling-authored state, excluded/unclaimed.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-WAVE-A-REVERIFICATION-DISPATCHED-NEW-BASE-A2EEDC9-NOTHING-TRANSCRIBES-20260820-145356.md` → `s4-matrix.planner`, `s4-matrix.implementer`
- STEP-4 REMAINDER OPENS: slice E merged into local main as a2eedc9 (two parents, parent2 exact 6670471) and CLOSED end-to-end; your NEW BASE for Wave-A is main at/above a2eedc9; origin/main unchanged 0db8fdd and an ancestor, nothing published. Master dispatched the Wave-A re-verification to our lane and I carry it to you
- NOTHING FROM 08-06 TRANSCRIBES: #16/#17/#19/#20 went panel-clean 2026-08-06 against a main that has since absorbed FIVE product merges (A/B1/C/B2/R-4.8) plus slice E, ~14 days and ~90 changed files; a panel at a dead SHA is history not evidence; re-verify each candidate FROM SCRATCH at the new base in your stack order
- FIVE STAGES: (1) base state measured first per candidate (conflicts + semantic drift; SCOUTED overlap — slice E changed tests/test_probe.cpp via the R-3.40(13) fix while #16 refactors src/core/support/probe.cpp, so measure their consistency at the new base, do not assume it); (2) local suites GREEN at each re-based head BOTH platforms per the chartered recipe, the nofile soft-to-hard condition now CLAUDE.md Local-Linux-CI text landed with slice E, applied in the runuser drop; (3) panel + condition-3 re-satisfied at the ACTUAL merge SHAs, the 08-06 panels dead history; (4) count-gate cells re-derived from OBSERVED runs where a candidate moves them (M-a discipline, catch.xml, run ids cited, no arithmetic or cross-target borrowing); (5) route UP a MERGE-READINESS REPORT naming the exact act (candidates, order, local-merge mechanics per the slice-E pattern), each merge a NEW operator word
- STOP RULE: a real defect or fence question routes UP before any keyboard; the slice-E lane's record says that discipline is cheaper every time. FENCE: the NON-SCHEMA Arm-1 stack only; the Arm-1 SCHEMA act stays F+G-fenced and UNDISPATCHED until addendum F locks (master routed F rev8 to the VP in parallel), you do not wait on F for the non-schema stack and do not touch the schema act; NOT GRANTED any merge, push, or matrix-PR state change beyond read-only re-verification + local suite runs
- origin untouched; both refs LOCAL and UNPUBLISHED; merge is not push is not release; release hold ABSOLUTE
