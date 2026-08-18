## PLAN rev2 (coupled fold + S-16, now carrying the W-2 LITERAL BINDING LIST that rev0 and rev1 both lacked) — **rev2 adds ONE THING and changes nothing else: the literal binding list W-2's selector requires and my two previous revisions never carried. Everything substantive carries forward verbatim from rev1 (`6057acc081bdf87a385b632eba1784ab135a0f55c4e2eb378a399a4d42b54556`, approved at `233228`), which carried rev0 (`1b9c6930e35ded4bffd5e34002d3101786190fc7b1dde104a2265c163aa11ec5`, approved at `192103`) verbatim: S-1…S-16, the sixteen live legs, the nine scope rows, A1–A15, G1–G9, the structural bar at `probe.cpp:652-656`, the measure-first shape procedure, and fix-commit-FIRST ordering. Not one of them is reopened, and rev2 is not an occasion to reopen them.** **WHY IT EXISTS, stated plainly because a reviewer should not have to reconstruct it: I refused my own token at `234900`. W-2's coverage comes from ONE source — *"the plan's literal binding list CREATES coverage — the ONLY source"* — and its exhaustive field dispositions say `DESIGN_DOC_ID` / `DESIGN_LOCK_ID` / `SECOND_DESIGN_LOCK` create NO coverage unless the identity is RESTATED in that list, with ambiguity resolving to INAPPLICABLE and never to the larger set. rev0 and rev1 carried header fields and a §1 lock table; neither carried a `DESIGN_DOC_ID -> DESIGN_LOCK_ID` pair list. So L never entered coverage, and — because W-2 is a CURRENT-REVISION MODEL, NOT CUMULATIVE — rev1 displacing the registry's K-only revision under the same `PLAN_LOCK_ID` took K out too. rev2 restores a well-formed current list.** **THE LIST IS ONE ITEM AND THAT IS A MEASUREMENT, NOT A CHOICE: W-2 fails a list that restates a NON-firing identity (*"a successor list restating a NON-firing identity fails the selector and is INAPPLICABLE / NO TOKEN"*), so the list must be exactly the fired set. `--relay-root .relays/s4` reports exactly ONE DESIGN-lineage error per plan file, naming `m1-addendum-L-10c8e8e6-lock-20260817` and nothing else; K, A5 and A4 ride `SECOND_DESIGN_LOCK`, which the gate at `relay-lint.py:3252` never reads. **K is therefore NOT restated — deliberately, and it is not an omission to correct.** If a reviewer believes K should be listed, the way to establish that is to make K FIRE and measure it, not to add it because it feels safer; adding it would fail the selector and refuse the token a second time.** **WHAT rev2 DOES NOT DO: it does not issue a token, and it does not perform the W-2 join. The join runs per LISTED identity at the registry and locked bytes AFTER this revision passes local plan-review, with every element reported pass or fail, and NO token issues on any mismatch. That order is W-2's own extension rule and I am not compressing it.** `9729191` untouched, the fold delta held unstaged, branch LOCAL and UNPUBLISHED. Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ROLE: Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-floor-slice-e-coupled-fold-plan-rev2
PARENT_DISPATCH_ID: s4-floor-slice-e-coupled-fold-plan-review-rev1
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-REVIEW-IMPLEMENTER-SLICE-E-COUPLED-FOLD-REV1-APPROVE-W2-TOKEN-JOIN-20260817-233228.md
RELATED_CONTEXT: .relays/s4/s4-floor-impl/SITREP-PLANNER-SLICE-E-TOKEN-REFUSED-W2-NO-LITERAL-BINDING-LIST-REV2-OWED-20260817-234900.md
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no NEW operator gate — rev2 adds only the literal binding list W-2's own selector requires, restoring a well-formed current revision. No token here; the W-2 join and then the token follow this revision's local plan-review. m-1's veto, m-3's combined review and the m-3/m-2 objection path on the fix are unchanged. The land order binds. The release hold is ABSOLUTE.
DESIGN_DOC_ID: m1-addendum-L-20260816
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m1-addendum-L-10c8e8e6-lock-20260817
TARGET_DESIGN_SHA256: 10c8e8e6ed1560d8fc03e9342ed539a1554fdc0a978ba864ce6427226e0daba4
TARGET_DESIGN_COMMIT: 8c7f9281d538704419ea7142a417495eec46e8a5
SECOND_DESIGN_LOCK: m1-addendum-K-5da667fa-lock-20260816, m3-addendum-5-b8686c75-lock-20260816, m3-addendum-4-9049de44-lock-20260816
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812, m3-addendum-3-eeb4dd01-lock-20260814
CONSUMER_DESIGN_LOCK_ID: m3-addendum-3-eeb4dd01-lock-20260814
PLAN_LOCK_ID: s4-floor-slice-e-plan-20260812
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer, m-1.planner, m-3.planner, m-2.planner
SUBJECT: PLAN rev2 — adds the W-2 LITERAL BINDING LIST (one item, L only, the measured fired set); rev1 and rev0 carry forward verbatim with nothing reopened; no token and no join in this relay; PLAN-REVIEW requested

## 1. W-2 LITERAL BINDING LIST

**This section is the literal binding list W-2's `DESIGN_BINDINGS` selector reads. It lists exactly the
design identities whose foreign-lock lineage red this plan waives under W-2, as explicit
`DESIGN_DOC_ID -> DESIGN_LOCK_ID` pairs in the plan bytes.**

W2_BINDING_LIST:
- m1-addendum-L-20260816 -> m1-addendum-L-10c8e8e6-lock-20260817
W2_BINDING_LIST_COUNT: 1

```text
WHY EXACTLY ONE, MEASURED
  instrument   python3 ~/.claude/skills/tools/relay-lint.py --relay-root .relays/s4
  observed     exactly ONE DESIGN-lineage error per plan file; on rev1 it names
               DESIGN_LOCK_ID 'm1-addendum-L-10c8e8e6-lock-20260817' and no other identity
  why          the gate (relay-lint.py:3252) filters same-owner DESIGN relays on
               DESIGN_DOC_ID == lock_id, reading ONLY the consuming relay's DESIGN_LOCK_ID.
               K, A5 and A4 ride SECOND_DESIGN_LOCK and never reach it.
  K OMITTED DELIBERATELY — W-2: "a successor list restating a NON-firing identity fails the selector
  and is INAPPLICABLE / NO TOKEN." Listing K would refuse the token a second time. Its absence is a
  measurement, not an oversight, and it is not to be "corrected" in review.
```

**Not coverage-bearing, stated so the record is unambiguous:** this plan's `DESIGN_DOC_ID`,
`DESIGN_LOCK_ID`, `SECOND_DESIGN_LOCK`, `CONSUMED_CONTRACT` and `CONSUMER_DESIGN_LOCK_ID` header fields, and
rev0 §1's "Locks bound" table, create **no** W-2 coverage. Only the list above does.

## 2. What rev2 changes

```text
ADDS       §1, the literal binding list — the ONLY substantive addition
CARRIES    rev1 (6057acc0…, approved 233228) and through it rev0 (1b9c6930…, approved 192103), VERBATIM:
FORWARD      S-1..S-15 (rev0) · S-16 and its one-case fence (rev1) · the structural bar derived at
             probe.cpp:652-656 · the measure-first shape procedure · fix-commit-FIRST ordering ·
             the sixteen live legs · the nine SCOPE_DIFF rows · A1..A15 · G1..G9 · every OUT row
REOPENS    NOTHING. rev2 is not an occasion to revisit approved binds.
```

## 3. Scope — unchanged from rev1, restated for the review's mechanical check

SCOPE_DIFF:
- src/core/manifest/manifest.hpp -> in
- src/core/manifest/manifest.cpp -> in
- src/core/open/open.cpp -> in
- tests/test_manifest.cpp -> in
- tests/test_cli.cpp -> in
- tests/test_sessions.cpp -> in
- tests/fixtures/slice-e/** -> in
- .github/workflows/s2-harness.yml -> in
- tests/test_probe.cpp -> in
SCOPE_DIFF_RESULT: all-in

SCOPE_ROW_EVIDENCE:
- unchanged from rev1 §4 and the `193748` token's per-row evidence; rev2 adds no path and removes none. `tests/test_probe.cpp` remains fenced to the single case at `:260-278` (its helper at `:57-65` and/or its expected outcome) under the `221915` grant.

## 4. What happens after this revision passes review — the order I will not compress

```text
1  this revision passes my Implementer's PLAN-REVIEW      => it becomes the CURRENT APPROVED REVISION
                                                              under PLAN_LOCK_ID s4-floor-slice-e-plan-20260812,
                                                              and §1 becomes W-2's current coverage
2  the W-2 TOKEN-TIME JOIN, per LISTED identity (L), at the registry and locked bytes, never from a summary:
     · the owning Planner's lock declaration naming lock ID + full content SHA-256 + full commit
     · the VP's exact-pin approval naming the same three-field identity
     · the design's own gate dispositions as its lock records them
     · every artifact PRECEDES the consuming token; no later supersession; no later unlocked normative edit
   EVERY element reported pass or fail in the token relay. ANY mismatch => NO TOKEN.
3  the token, parented to the PLAN-REVIEW on THIS revision
```

**Join inputs already located** (to be opened and read at join time, not taken from any summary):
`pdc master/relays/s4-build-standup/DESIGN-PLANNER-M1-ADDENDUM-L-NEW-LOCK-DECLARED-REV7-FENCES-RESTAMPED-AT-PIN-20260817-184619.md`
(owner lock declaration) · `DESIGN-REVIEW-IMPLEMENTER-M1-ADDENDUM-L-REV7-APPROVE-LEG-Q-LOCUS-EXACT-20260817-144843.md`
(gate disposition) · the VP exact-pin approval act `154000` the lock stamp names.

## 5. One consequence for master, carried here as well as at `234900`

W-2's current-revision model means rev1 already displaced the registry-named K-only revision
(`PLAN-…-141427` at `73d4b22`, plan SHA `3178243a…`) as "the latest revision under the `PLAN_LOCK_ID` that
has passed the sub-team's local plan-review". Once rev2 is approved, **rev2 is that revision and §1 is the
coverage.** The registry's `DESIGN_BINDINGS` block still names `141427`; that text is stale and is
**master's row to correct** — not mine to edit, and not a blocker on this revision.

## 6. Questions for my Implementer

1. Do you agree the list must be **L alone**, and that adding K would fail the selector? If you read the
   fired set differently, say so with the command you ran.
2. Does §1 satisfy W-2's `DESIGN_BINDINGS` form — an explicit `DESIGN_DOC_ID -> DESIGN_LOCK_ID` pair, in the
   plan bytes, unambiguously identified as the binding list? This is the one thing rev2 exists to get right.
3. Anything else in rev2. rev0's and rev1's approved binds are not reopened.

Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product, test, fixture, workflow, branch, Docker, push, PR, Actions, merge, publication, deployment, or release act at this seat — plan-only. Read-only this pass: `pdc/master/RESIDUALS.md:1931-2035` (W-2 in full); rev0 and rev1 re-hashed (`1b9c6930…`, `6057acc0…`) and grepped for a literal binding list (absent in both); `--relay-root .relays/s4` re-run and the fired identity read; `relay-lint.py:3252` and its candidate filter read; the L join artifacts located in pdc. This relay + its INDEX row ride ONE explicit-path docs-lane commit whose SHA lands after filing. NO TOKEN ISSUED and NO JOIN PERFORMED — both follow this revision's plan-review.
RELAY_LINT: per D-3.4 (v2.9) — per-file WITH freshness (clock read immediately before filing, per D-5.10 instance 4), exit status checked un-piped and READ before committing; `--relay-root` run against this file and its output read in full. Standing reds disclosed: the cross-repo DESIGN-lineage class (rev0, rev1 and now this revision are members — that red is precisely what §1 exists to bring under W-2, and it is disclosed rather than claimed absent); INDEX cell-count (R-4.27) at 132, 222, 324, 362, 384, 388, 408, 435; INDEX time inversions at 222 and 393. `.relays/s4/INDEX.md` tail re-read before appending; `--index`; add and commit path-scoped; my appended row is 10-cell clean.
FINAL_GIT_STATUS_SHORT: literal path-scoped `git status --short` for this seat's two writes, captured at staging (the implementation worktree `s4-floor-slice-e-stage1a` at `9729191` carries my Implementer's seven authorized unstaged paths, held deliberately and not mine to touch; the shared main checkout carries sibling-authored untracked state, excluded and unclaimed):
  M  .relays/s4/INDEX.md
  A  .relays/s4/s4-floor-impl/PLAN-PLANNER-SLICE-E-COUPLED-FOLD-REV2-W2-LITERAL-BINDING-LIST-L-ONLY-20260817-235116.md

CARRY LIST (D-8.5):
- `.relays/s4/s4-floor-impl/PLAN-PLANNER-SLICE-E-COUPLED-FOLD-REV2-W2-LITERAL-BINDING-LIST-L-ONLY-20260817-235116.md` → `s4-floor.implementer`
- rev2 ADDS EXACTLY ONE THING: the W-2 LITERAL BINDING LIST at §1, which rev0 and rev1 both lacked. rev1 (6057acc081bdf87a385b632eba1784ab135a0f55c4e2eb378a399a4d42b54556, approved 233228) and through it rev0 (1b9c6930e35ded4bffd5e34002d3101786190fc7b1dde104a2265c163aa11ec5, approved 192103) carry forward VERBATIM — S-1 through S-16, the sixteen live legs, the nine scope rows, A1 through A15, G1 through G9, the structural bar at probe.cpp:652-656, the measure-first shape procedure and fix-commit-FIRST ordering. NOTHING is reopened
- WHY: this seat refused its own token at 234900. W-2's coverage comes from ONE source, the plan's literal binding list, and its exhaustive field dispositions make DESIGN_DOC_ID, DESIGN_LOCK_ID and SECOND_DESIGN_LOCK create NO coverage unless restated in it, with ambiguity resolving to INAPPLICABLE rather than to the larger set. rev0 and rev1 carried header fields and a lock table but no DESIGN_DOC_ID to DESIGN_LOCK_ID pair list, so L never entered coverage; and because W-2 is a CURRENT-REVISION MODEL and not cumulative, rev1 displacing the registry's K-only revision under the same PLAN_LOCK_ID took K out as well
- THE LIST IS ONE ITEM AND THAT IS A MEASUREMENT: W2_BINDING_LIST is m1-addendum-L-20260816 -> m1-addendum-L-10c8e8e6-lock-20260817, count 1. --relay-root reports exactly one DESIGN-lineage error per plan file naming that lock and no other identity, because the gate at relay-lint.py:3252 filters same-owner DESIGN relays on DESIGN_DOC_ID equal to lock_id and reads only the consuming relay's DESIGN_LOCK_ID, while K, A5 and A4 ride SECOND_DESIGN_LOCK and never reach it. K IS OMITTED DELIBERATELY — W-2 fails a list restating a NON-firing identity, so listing K would refuse the token a second time; its absence is a measurement, not an oversight, and is not to be corrected in review
- rev2 ISSUES NO TOKEN AND PERFORMS NO JOIN. The order, uncompressed: this revision passes local plan-review and becomes the current approved revision so §1 becomes W-2's coverage; then the token-time join per LISTED identity at the registry and locked bytes, never from a summary, covering the owner Planner's lock declaration with lock ID plus full SHA-256 plus full commit, the VP's exact-pin approval naming the same three-field identity, the design's own gate dispositions as its lock records them, and every artifact preceding the token with no later supersession or unlocked normative edit — every element reported pass or fail, and ANY mismatch means NO TOKEN; then the token, parented to the PLAN-REVIEW on this revision
- JOIN INPUTS LOCATED, to be opened at join time rather than taken from a summary: pdc master/relays/s4-build-standup/DESIGN-PLANNER-M1-ADDENDUM-L-NEW-LOCK-DECLARED-REV7-FENCES-RESTAMPED-AT-PIN-20260817-184619.md, DESIGN-REVIEW-IMPLEMENTER-M1-ADDENDUM-L-REV7-APPROVE-LEG-Q-LOCUS-EXACT-20260817-144843.md, and the VP exact-pin approval act 154000 named by the lock stamp
- FOR MASTER, carried here as well as at 234900: once rev2 is approved it is the latest locally-approved revision under PLAN_LOCK_ID s4-floor-slice-e-plan-20260812 and §1 is the coverage, so the registry's DESIGN_BINDINGS block naming the 141427 K-only revision is stale; master's row to correct, not this seat's to edit, and not a blocker on this revision
- 9729191 untouched with the fold delta held unstaged; land order binds every merge; branch LOCAL and UNPUBLISHED; merge is not push is not release; release hold ABSOLUTE
