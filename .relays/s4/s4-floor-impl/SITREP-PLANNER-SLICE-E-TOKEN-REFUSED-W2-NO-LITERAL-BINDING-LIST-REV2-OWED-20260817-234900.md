## SITREP (TOKEN REFUSED — I read W-2's own bytes instead of the carried paraphrase, and my plan does not qualify for its coverage) — **rev1 is APPROVED and its substance is sound; the refusal is not about S-16. It is about W-2. The carried term said "the new L lock id is now part of that binding list, so re-verify the join input" — and when I opened `pdc/master/RESIDUALS.md:1931-2035` rather than trusting that sentence, W-2's coverage selector reads: `DESIGN_BINDINGS` = "THE LITERAL BINDING LIST CARRIED BY THE CURRENT APPROVED PLAN REVISION … where each item is an EXPLICIT `DESIGN_DOC_ID -> DESIGN_LOCK_ID` pair IN THE PLAN BYTES." Its FIELD DISPOSITIONS are exhaustive and decide this outright: "the plan's literal binding list CREATES coverage — the ONLY source" and "`DESIGN_DOC_ID` / `DESIGN_LOCK_ID` / `SECOND_DESIGN_LOCK` create NO coverage unless the identity is restated in the literal list," with "unrecognized design-bearing field, or ambiguous binding ⇒ INAPPLICABLE / NO TOKEN — never resolved by choosing the larger set."** **MEASURED AT MY OWN BYTES: NEITHER rev0 NOR rev1 CARRIES A LITERAL BINDING LIST. A grep for any `-> ` pairing an addendum identity returns NOTHING in either file. My §1 "Locks bound" table lists lock ids and hashes under single-letter labels; it is not a `DESIGN_DOC_ID -> DESIGN_LOCK_ID` pair list, it never says it is the W-2 binding list, and under the exhaustive dispositions an ambiguous binding is INAPPLICABLE rather than generously resolved. So the L identity NEVER ENTERED COVERAGE, and the header `DESIGN_LOCK_ID` I did carry creates none by rule. W-2 does not clear the red that fires on rev0 and rev1. NO TOKEN ISSUES.** **AND THERE IS A SECOND CONSEQUENCE I CAUSED AND WILL NOT LEAVE UNSAID: W-2 is a CURRENT-REVISION MODEL, NOT CUMULATIVE — "the current revision's list IS the set; an item absent from the current revision's list has LEFT coverage." The registry names the current approved revision as `PLAN-…-SUCCESSOR-REV1-W2-BINDING-LIST-K-ONLY-20260816-141427`, whose one-item list is `m1-addendum-K-20260816 -> m1-addendum-K-5da667fa-lock-20260816`. My rev1 carries the SAME `PLAN_LOCK_ID: s4-floor-slice-e-plan-20260812` and has now passed local plan-review at `233228`, so it IS the latest locally-approved revision under that selector — and it displaced the K-only revision while carrying no list at all. **By the selector's own words, K has LEFT coverage too, and the registry's "CURRENT APPROVED REVISION" text is now stale.** That is master's row to correct; I am reporting it, not editing it.** **THE FAILURE MODE IS THE RECOVERABLE ONE: `INAPPLICABLE / NO TOKEN` — "W-2 survives, dormant, until a newly complete CURRENT join exists for every identity in the current literal binding list." Not TERMINATED: the repo, relay root, plan lock and slice are unchanged and the red is the same character. The remedy is W-2's own EXTENSION RULE — "a NEW design identity enters coverage ONLY by appearing in the literal binding list of a successor plan revision that passes the sub-team's local plan-review, at a VP-approved current lock." So I owe rev2 carrying the literal list, my Implementer's review of it, then the per-identity join, then the token — in that order, and I will not shortcut it.** **THE LIST MUST BE EXACTLY THE MEASURED FIRED SET, WHICH IS L ALONE. W-2: "a successor list restating a NON-firing identity fails the selector and is INAPPLICABLE / NO TOKEN." I measured rather than reasoned: `--relay-root .relays/s4` reports exactly ONE DESIGN-lineage error per plan file, and on rev1 it names `m1-addendum-L-10c8e8e6-lock-20260817` and nothing else; K, A5 and A4 ride `SECOND_DESIGN_LOCK`, which the gate never reads. I also VALIDATED THE DISCRIMINATOR at the linter source rather than accepting W-2's citation of it: the gate is at `relay-lint.py:3252`, and it filters `same_owner_designs` on `DESIGN_DOC_ID == lock_id` — reading only `DESIGN_LOCK_ID` from the consuming relay, as W-2 says. **W-2's own line citation `relay-lint.py:1432-1442` is STALE** (that range is now `split_index_cells`); the behaviour it describes is correct, the pointer is not — disclosed so the next seat greps rather than jumps.** No token. `9729191` untouched, the fold delta held unstaged, branch LOCAL and UNPUBLISHED. Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-floor-slice-e-token-refused-w2-no-binding-list
PARENT_DISPATCH_ID: s4-floor-slice-e-coupled-fold-plan-review-rev1
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-REVIEW-IMPLEMENTER-SLICE-E-COUPLED-FOLD-REV1-APPROVE-W2-TOKEN-JOIN-20260817-233228.md
RELATED_CONTEXT: .relays/s4/s4-floor-impl/SITREP-PLANNER-SLICE-E-REV1-LINT-DISCLOSURE-CORRECTED-W2-JOIN-DUE-20260817-230604.md
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: yes — a waiver's coverage selector is not met, so no implementation token issues at this seat. The registry's "current approved revision" text is stale as a consequence of my own revision and is master's to correct. No product byte, no commit to the implementation branch, no token. The land order binds. The release hold is ABSOLUTE.
DESIGN_DOC_ID: m1-addendum-L-20260816
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m1-addendum-L-10c8e8e6-lock-20260817
SECOND_DESIGN_LOCK: m1-addendum-K-5da667fa-lock-20260816, m3-addendum-5-b8686c75-lock-20260816, m3-addendum-4-9049de44-lock-20260816
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812, m3-addendum-3-eeb4dd01-lock-20260814
PLAN_LOCK_ID: s4-floor-slice-e-plan-20260812
FROM: s4-floor.planner
TO: s4.orchestrator-planner
CC: operator, s4-floor.implementer, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer, m-1.planner
SUBJECT: SITREP — TOKEN REFUSED: W-2 is INAPPLICABLE because neither rev0 nor rev1 carries a LITERAL BINDING LIST, and the header DESIGN_LOCK_ID creates no coverage by rule; my rev1 also displaced the K-only revision under the current-revision model, so K has left coverage and the registry's current-revision text is stale; rev2 with an L-only list is owed, then the join, then the token

## 1. What W-2 actually says — read at `RESIDUALS.md:1931-2035`, not carried

```text
DESIGN_BINDINGS   "THE LITERAL BINDING LIST CARRIED BY THE CURRENT APPROVED PLAN REVISION — the latest
                   revision under the PLAN_LOCK_ID above that has passed the sub-team's local plan-review —
                   where each item is an EXPLICIT `DESIGN_DOC_ID -> DESIGN_LOCK_ID` pair IN THE PLAN BYTES"
                  "CURRENT-REVISION MODEL, NOT CUMULATIVE: the current revision's list IS the set; an item
                   absent from the current revision's list has LEFT coverage."

FIELD DISPOSITIONS (exhaustive):
  the plan's literal binding list                      CREATES coverage — the ONLY source
  DESIGN_DOC_ID / DESIGN_LOCK_ID / SECOND_DESIGN_LOCK  create NO coverage unless RESTATED in the literal list
  CONSUMED_CONTRACT / CONSUMER_DESIGN_LOCK_ID          NEVER create coverage
  unrecognized design-bearing field, or ambiguous      => INAPPLICABLE / NO TOKEN — never resolved by
  binding                                                 choosing the larger set
```

## 2. The measurement at my own bytes

```text
grep for any "-> " pairing an addendum identity:
  rev1 (230254)   NONE
  rev0 (191450)   NONE
```

My §1 "Locks bound" table lists lock ids and hashes under single-letter labels (`L`, `K`, `A5`, `A4`, `J`,
`A3`). It is **not** a `DESIGN_DOC_ID -> DESIGN_LOCK_ID` pair list and never declares itself the W-2 binding
list. Under the exhaustive dispositions that is at best an ambiguous binding, and W-2 resolves ambiguity to
**INAPPLICABLE / NO TOKEN**, expressly refusing the generous reading.

**So the L identity never entered coverage, and the header `DESIGN_LOCK_ID` I did carry creates none by rule.
W-2 does not clear the red that fires on rev0 and rev1. The token does not issue.**

## 3. The second consequence — mine, and I am not leaving it unsaid

```text
registry names as CURRENT   PLAN-…-SUCCESSOR-REV1-W2-BINDING-LIST-K-ONLY-20260816-141427 @ 73d4b22,
                            plan SHA 3178243a…, list = m1-addendum-K-20260816 -> m1-addendum-K-5da667fa-lock-20260816
my rev1                     SAME PLAN_LOCK_ID s4-floor-slice-e-plan-20260812, locally approved at 233228
                            => it is now "the latest revision under the PLAN_LOCK_ID that has passed the
                               sub-team's local plan-review", i.e. THE CURRENT APPROVED REVISION
its list                    ABSENT
```

By the selector's own current-revision words, **K has LEFT coverage**, and the registry's
"CURRENT APPROVED REVISION (folded 2026-08-16)" text is stale. **That row is master's to write** — I am
reporting the fact, not editing it, and rev2 (§5) is what restores a well-formed current list.

## 4. Which failure mode, and why it matters

```text
INAPPLICABLE / NO TOKEN   RECOVERABLE — "W-2 survives, dormant, until a newly complete CURRENT join exists
                          for every identity in the current literal binding list"                THIS ONE
TERMINATED / OUT OF SCOPE  a different REPO, RELAY_ROOT, PLAN_LOCK_ID or slice; a red of different
                          character; the R-4.27 measured-closure condition                       NOT THIS
```

Repo, relay root, plan lock and slice are unchanged and the red is the same character. **Recoverable.** This
distinction is exactly the one that cost a cycle at `131839`, when W-1 proved TERMINATED rather than merely
inapplicable and the instructed remedy was the one act that could not help — so I state which mode fires and
why, rather than saying "the waiver does not apply."

## 5. The remedy, from W-2's own extension rule

> *"a NEW design identity enters coverage ONLY by appearing in the literal binding list of a successor plan
> revision that passes the sub-team's local plan-review, at a VP-approved current lock."*

```text
1  rev2 carries the LITERAL BINDING LIST                          (mine, filing next)
2  my Implementer's PLAN-REVIEW on rev2                           (theirs)
3  the TOKEN-TIME JOIN per LISTED identity at the registry/locked bytes, every element reported  (mine)
4  the token — ONLY if every element matches                      (mine)
```

**The list is L ALONE, because the list must be the MEASURED FIRED SET.** W-2: *"a successor list restating a
NON-firing identity fails the selector and is INAPPLICABLE / NO TOKEN."*

```text
measured   `--relay-root .relays/s4` reports exactly ONE DESIGN-lineage error per plan file; on rev1 it names
           m1-addendum-L-10c8e8e6-lock-20260817 and nothing else
why        K, A5 and A4 ride SECOND_DESIGN_LOCK, which the gate never reads
rev2 list  m1-addendum-L-20260816 -> m1-addendum-L-10c8e8e6-lock-20260817      (one item, no more, no less)
```

**Join inputs already located for step 3**, so the sequence does not stall: the owner Planner's lock
declaration is `pdc master/relays/s4-build-standup/DESIGN-PLANNER-M1-ADDENDUM-L-NEW-LOCK-DECLARED-REV7-FENCES-RESTAMPED-AT-PIN-20260817-184619.md`;
the gate disposition is `DESIGN-REVIEW-IMPLEMENTER-M1-ADDENDUM-L-REV7-APPROVE-LEG-Q-LOCUS-EXACT-20260817-144843.md`;
the VP exact-pin approval is the `154000` act the lock stamp names, to be opened and read at join time rather
than taken from the stamp's own summary.

## 6. Discriminator validated, and one stale pointer disclosed

W-2 asserts the lineage gate reads only `DESIGN_LOCK_ID` and cites `relay-lint.py:1432-1442`. I checked the
source rather than accepting the citation:

```text
relay-lint.py:3252   result.error(f"... DESIGN_LOCK_ID {lock_id!r} has no earlier same-owner DESIGN relay
                     carrying matching DESIGN_DOC_ID")
  fed by             design_candidates = [item for item in same_owner_designs
                                          if item[3].get("DESIGN_DOC_ID") == lock_id]
```

**The behaviour W-2 describes is correct** — only `DESIGN_LOCK_ID` is read from the consuming relay.
**The line citation is STALE:** `1432-1442` is now `split_index_cells`. Disclosed so the next seat greps for
the message rather than jumping to a range that no longer holds it.

## 7. State

```text
rev1         APPROVED at 233228; its substance is untouched by this refusal — S-16, the structural bar,
             the measure-first shape, fix-commit-FIRST ordering, A11-A15, G8-G9 all stand
token        REFUSED. None issued.
9729191      untouched; the fold delta held unstaged; nothing committed to the implementation branch
next (mine)  rev2 with the literal binding list, filed immediately after this relay
```

Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product, test, fixture, workflow, branch, Docker, push, PR, Actions, merge, publication, deployment, or release act at this seat. Read-only this pass: `pdc/master/RESIDUALS.md:1931-2035` (W-2 in full — status, coverage block, field dispositions, extension rule, token-time join, both failure modes, the risk sentence); rev0 and rev1 grepped for a literal binding list (none in either); the `233228` review read in full and its declared hashes for rev1 (`6057acc0…`) and my correction (`31625d01…`) re-derived by me and EQUAL; `--relay-root .relays/s4` re-run and the fired identity on rev1 read; `relay-lint.py:3252` and its candidate filter read to validate the discriminator; the L lock declaration and gate-disposition relays located in pdc for the join. This relay + its INDEX row ride ONE explicit-path docs-lane commit whose SHA lands after filing. NO TOKEN ISSUED.
RELAY_LINT: per D-3.4 (v2.9) — per-file WITH freshness (clock read immediately before filing, per D-5.10 instance 4), exit status checked un-piped and READ before committing; `--relay-root` run against this file and its output read in full. Standing reds disclosed: the cross-repo DESIGN-lineage class of 27 rows including rev0 and rev1; INDEX cell-count (R-4.27) at 132, 222, 324, 362, 384, 388, 408, 435; INDEX time inversions at 222 and 393. `.relays/s4/INDEX.md` tail re-read before appending; `--index`; add and commit path-scoped; my appended row is 10-cell clean.
FINAL_GIT_STATUS_SHORT: literal path-scoped `git status --short` for this seat's two writes, captured at staging (the implementation worktree `s4-floor-slice-e-stage1a` at `9729191` carries my Implementer's seven authorized unstaged paths, held deliberately and not mine to touch; the shared main checkout carries sibling-authored untracked state, excluded and unclaimed):
  M  .relays/s4/INDEX.md
  A  .relays/s4/s4-floor-impl/SITREP-PLANNER-SLICE-E-TOKEN-REFUSED-W2-NO-LITERAL-BINDING-LIST-REV2-OWED-20260817-234900.md

CARRY LIST (D-8.5):
- `.relays/s4/s4-floor-impl/SITREP-PLANNER-SLICE-E-TOKEN-REFUSED-W2-NO-LITERAL-BINDING-LIST-REV2-OWED-20260817-234900.md` → `s4.orchestrator-planner`
- TOKEN REFUSED. rev1 is APPROVED and its substance is sound; the refusal is about W-2, not S-16. Reading RESIDUALS.md:1931-2035 rather than the carried sentence "the new L lock id is now part of that binding list": W-2's DESIGN_BINDINGS selector is THE LITERAL BINDING LIST CARRIED BY THE CURRENT APPROVED PLAN REVISION, each item an EXPLICIT DESIGN_DOC_ID -> DESIGN_LOCK_ID pair IN THE PLAN BYTES, and its exhaustive FIELD DISPOSITIONS say the literal list CREATES coverage as the ONLY source while DESIGN_DOC_ID, DESIGN_LOCK_ID and SECOND_DESIGN_LOCK create NO coverage unless restated in it, with ambiguous binding resolving to INAPPLICABLE / NO TOKEN and never to the larger set
- MEASURED AT MY OWN BYTES: NEITHER rev0 NOR rev1 CARRIES A LITERAL BINDING LIST — a grep for any addendum "-> " pairing returns nothing in either file. My §1 Locks-bound table lists lock ids and hashes under single-letter labels, is not a doc-id-to-lock-id pair list, and never declares itself the W-2 binding list. The L identity therefore NEVER ENTERED COVERAGE and the header DESIGN_LOCK_ID creates none by rule, so W-2 does not clear the red firing on rev0 and rev1
- SECOND CONSEQUENCE, MINE AND OWNED: W-2 is a CURRENT-REVISION MODEL, NOT CUMULATIVE, and an item absent from the current revision's list has LEFT coverage. My rev1 carries the same PLAN_LOCK_ID s4-floor-slice-e-plan-20260812 and passed local plan-review at 233228, so it is now the latest locally-approved revision under that selector and it displaced the registry-named K-only revision 141427 while carrying no list at all. K has LEFT coverage and the registry's CURRENT APPROVED REVISION text is stale — master's row to correct, reported not edited
- FAILURE MODE IS THE RECOVERABLE ONE: INAPPLICABLE / NO TOKEN, W-2 surviving dormant until a newly complete CURRENT join exists for every identity in the current literal binding list. NOT TERMINATED — repo, relay root, plan lock and slice are unchanged and the red is the same character. Naming the mode matters: this is the distinction that cost a cycle at 131839 when W-1 proved TERMINATED and the instructed remedy was the one act that could not help
- REMEDY, from W-2's own EXTENSION RULE: (1) rev2 carrying the LITERAL BINDING LIST, filing immediately after this relay; (2) the Implementer's PLAN-REVIEW on rev2; (3) the TOKEN-TIME JOIN per LISTED identity at the registry and locked bytes with every element reported; (4) the token ONLY if every element matches. THE LIST IS L ALONE because it must be the MEASURED FIRED SET and W-2 fails a list restating a NON-firing identity: --relay-root reports exactly one DESIGN-lineage error per plan file and on rev1 it names m1-addendum-L-10c8e8e6-lock-20260817 and nothing else, while K, A5 and A4 ride SECOND_DESIGN_LOCK which the gate never reads. rev2's list is the single pair m1-addendum-L-20260816 -> m1-addendum-L-10c8e8e6-lock-20260817
- JOIN INPUTS LOCATED so step 3 does not stall: the owner Planner lock declaration at pdc master/relays/s4-build-standup/DESIGN-PLANNER-M1-ADDENDUM-L-NEW-LOCK-DECLARED-REV7-FENCES-RESTAMPED-AT-PIN-20260817-184619.md, the gate disposition at DESIGN-REVIEW-IMPLEMENTER-M1-ADDENDUM-L-REV7-APPROVE-LEG-Q-LOCUS-EXACT-20260817-144843.md, and the VP exact-pin approval act 154000 named by the lock stamp, to be opened and read at join time rather than taken from the stamp's own summary
- DISCRIMINATOR VALIDATED AT SOURCE rather than accepted from the waiver: the gate is relay-lint.py:3252, fed by design_candidates filtering same_owner_designs on DESIGN_DOC_ID == lock_id, so only DESIGN_LOCK_ID is read from the consuming relay exactly as W-2 says. W-2's own citation relay-lint.py:1432-1442 is STALE, that range now being split_index_cells — disclosed so the next seat greps for the message rather than jumping to a range that no longer holds it
- NO TOKEN ISSUED; rev1's substance stands untouched; 9729191 untouched with the fold delta held unstaged; land order binds; branch LOCAL and UNPUBLISHED; merge is not push is not release; release hold ABSOLUTE
