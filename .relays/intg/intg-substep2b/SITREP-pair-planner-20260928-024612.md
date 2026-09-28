## SITREP — ACCEPTANCE RECEIVED (023917). Before the operator chooses an option in R-4.88: under the plan as it stands (rev46, 86f0f7d3), option (a)'s "rides the landing push" cannot happen as described. There are two reasons, both in the plan's own bytes. First, Task 12 runs only AFTER the merge head is on `main`, which is after the landing push. Second, Task 12 writes `landing-census.txt` INTO the sealed record, which makes the whole-set manifest check fail. Whichever option the operator picks needs its sequencing stated before the landing, so that no one has to decide it afterwards.

ROLE: Pair Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: intg-substep2b
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260928-023917.md
RELATED_CONTEXT: ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260928-023918.md; intg-substep2b/SITREP-pair-planner-20260928-021758.md; intg-substep2b/IMPL-pair-implementer-20260928-021324.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — the R-4.88 option word, PR #28's undraft and the bare merge token under .relays/intg are the operator's; if the chosen option needs a plan byte (see below), a rev47 needs the implementer's exact-hash review before Task 12; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
COMMISSION_TO: intg.pair-planner
CHARTER_DOC_ID: CH-intg-consent-fabric
PLAN_LOCK_ID: intg-substep2b-plan-20260915 @ sha256 86f0f7d305567828eb156f918464360c825476b75b8252e3c1054a5770e070aa
FROM: intg.pair-planner
TO: master.master-planner
CC: operator, master.master-reviewer, intg.pair-implementer
SUBJECT: SITREP — 023917 received and the explicit-path condition accepted. For R-4.88: under rev46, option (a)'s "rides the landing push" is unreachable for two reasons. (1) Task 12 starts only after the merge head is on main, which is after the push; the plan has no `git add` of the record, and main is never pushed by this plan. (2) Task 12 puts landing-census.txt inside the sealed record, and finalize.py check (SET == TREE minus SHA256SUMS == MANIFEST) then fails. Two sequencing forms are laid out below; each needs a plan byte and a stated order.
REPO: `../bivpak` docs lane — this relay (a path-scoped commit follows, no trailer); the plan at 885e754 untouched; the record still untracked; product bytes untouched; `../pdc` read-only
BRIDGE: intg.pair-planner → master.master-planner (the sequencing gap under R-4.88); operator CC (it bears on the option word); implementer CC (the landing act's inputs may change)

## Receipt

023917 is received. Task 11 is accepted, and you have confirmed that the record is untracked (021758 is the correct wording, not 012153's). I accept the Task 12 condition as binding under any option: the record is committed only BY EXPLICIT PATH, and the receipt states the committed file count and the `SHA256SUMS` digest.

## The gap, at the plan's bytes (rev46, 86f0f7d3)

1. **Order.** The plan's LANDING row and Task 12's ORDER line say Task 12 "begins ONLY after the operator's bare merge token has been consumed and the merge head is on `main` (R-4.52)". Under R-4.52 the landing merges locally and pushes local `main` in the same act, and your 023918 says so too. The VEHICLE row says "`main` is NEVER pushed by this plan", and no line of the plan runs `git add` on `RESDIR`. So a record committed during Task 12 sits on local `main` AFTER the only authorized push. Publishing it would take a second push of `main`, which nothing authorizes. As written, option (a) does not ride the landing push; the record would be committed and left local.
2. **The seal.** Task 12 writes its receipt into `results/s2b-<token>/landing-census.txt`. The plan's `finalize.py check` (the usage comment at plan line 3873) passes only if SET == TRACKED TREE (every regular file under RESDIR except SHA256SUMS) == MANIFEST PATHS. One more file in RESDIR makes that check fail against the sealed 2,342-line manifest (187a1a10). So committing "the record" after Task 12 would publish a tree that its own manifest does not describe. Otherwise the record must be re-sealed, which moves the digest your condition wants stated.

## Two forms that satisfy option (a) and your condition (both need a rev47 plan byte)

- **(a1) Commit before the landing, census kept outside the record.** Before the operator's token is consumed, the pair Planner commits exactly the 2,343 paths to local `main` by explicit path, in a docs-lane commit. The receipt states `files=2343` (2,342 plus SHA256SUMS) and `SHA256SUMS=187a1a10…`. The landing push then carries the record. Task 12's merge-head census is written BESIDE the record (for example `results/s2b-intg-substep2b-impl-1.landing-census.txt`), not inside it, so the sealed manifest stays true. That census receipt, and the closure SITREP's other records, stay local until a later authorized push. The landing census itself cannot ride the landing push, because it measures the merge head.
- **(a2) Everything after the landing, second push authorized.** Task 12 runs as written. The census goes inside RESDIR, and the record is re-sealed with a new SHA256SUMS whose count and digest are stated. Everything is committed by explicit path, and a SECOND push of `main` publishes it. That push needs the operator's explicit authorization, because the plan never pushes `main`.

My recommendation is (a1). It keeps the sealed manifest at 187a1a10 as it was measured, adds no push, and leaves only the census receipt local. Under option (b) there is no gap: nothing is committed, and the census still has to sit outside RESDIR or the manifest check fails. Option (c) needs its own selection act either way. The census-outside-RESDIR change is needed under ANY option, and it is a Task 12 plan byte.

Asked of you: carry the operator's option word together with a sequencing form (a1, a2, or your own). I then write rev47 (Task 12's receipt path, plus the pre-landing explicit-path commit step under a1) for the implementer's exact-hash review, before the token.

ACTIONS_GIT_REF: docs-lane writes only: this relay (a path-scoped commit follows), no trailer; the plan artifact at 885e754 untouched; every measurement read-only; product bytes untouched at this seat.
RELAY_LINT: engine-rendered submission; per-file 2.9.5 `relay-lint.py --no-freshness` on the draft; python-written; the filed bytes compared to the draft by digest; every newer upstream file opened before this submit (the listing run as its own command).
FINAL_GIT_STATUS_SHORT:
?? docs/sprints/2026-08-27-intg-consent-fabric/results/s2b-intg-substep2b-impl-1/
Literal path-scoped status for this seat's own writes at write time; the untracked results record is impl-17's; the shared bivpak tree carries other seats' untracked relays, not claimed clean here.
