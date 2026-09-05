## SITREP — count-gate plan REVISION 5 FILED as `intg-countgate/PLAN-pair-planner-20260905-022403.md` (handoff `intg-countgate-plan-5`; artifact @ b2c9295647188ff97fd0a4846562031c9c9a8ddfe84a9d67e10ff112143efc2e; dead prior 91852771; identities PRESERVED; commission surface byte-equal to the grant) folding the implementer's rev4 MUST-REVISE `020651` — three findings, all correct at the text and all mine: **F1** the identity section still carried two rev3 handoff references beside my appended plan-4 sentence (I appended instead of editing the sentence) — both now name `intg-countgate-plan-5`, the appended sentence removed, `grep -c 'intg-countgate-plan-3\b'` over the artifact = 0; **F2** Step 3(c)'s `echo rc` printed a word and recorded nothing — each discriminator arm now runs with fail-fast OFF for exactly those two commands, captures `$?` immediately into `discriminator-as-is.rc` / `discriminator-unset.rc`, and the plan ASSERTS from the files `rc2 == 0` and `rc1 != 0` iff the by-name host census holds a `present` name (either mismatch = FINDING, STOP UP); the two codes and the presence count flow to Step 5's table, the commit message, and acceptance 6; no value read or printed; **F3** Step 3(a)'s blanket "EVERY macOS observation command" sentence contradicted the as-is control arm — scoped to R-OBS-2's actual set (the five `-r xml` runs, the unfiltered scout, discriminator arm 2) with arm 1 named the ambient-host CONTROL; nothing else unset, no workflow/harness/product byte. Nothing else moves: m-3's ruling `012332` as encoded at rev4 (R-OBS-1..6), the sealed pin `0099d1cf`, W-4, your release `135906` and direction (a), the ten observed cells, the workflow-only scope, the run-head fence, ONE local-main commit, m-3's seven-point review. The W-4 CURRENT-REVISION REPLACEMENT MEASUREMENT is filed with it: EXACTLY ONE fired line on the carrier, the `0099d1cf` design-lineage red, verbatim below (archive `results/lint-root-sweep-countgate-plan-rev5-20260905.txt` @ b5fe79ca; per-file OK; zero lineage-walk errors root-wide). Two lessons owned at this seat: when a plan names a discriminator, write the CAPTURE and the ASSERTION, not a print; and grep the artifact for the OLD handoff id before filing. NEXT: the implementer's exact-hash review at b2c92956 (parented to `intg-countgate-plan-5`) → token `intg-countgate-impl-2` (the three-clause predicate already met) → Task 1 Step 1 at the then-current head; at that token's commit this seat's docs-lane freeze re-imposes until the landed sha returns. No workflow byte, no product byte, no observation at this seat; no merge, push, PR, publication, release; the release hold is ABSOLUTE

ROLE: Pair Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: intg-countgate-plan-5
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: intg-countgate/PLAN-REVIEW-pair-implementer-20260905-020651.md
RELATED_CONTEXT: intg-countgate/PLAN-pair-planner-20260905-022403.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-countgate-20260830.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/results/lint-root-sweep-countgate-plan-rev5-20260905.txt; intg-countgate/PLAN-pair-planner-20260905-014631.md; intg-countgate/SITREP-pair-planner-20260905-015625.md; ../../pdc/master/relays/r438-transcription-at-merged-bytes/DESIGN-planner-20260905-012332.md; ../../pdc/master/relays/r438-transcription-at-merged-bytes/PLAN-master-planner-20260905-013755.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/ROADMAP.md; ../../pdc/master/RESIDUALS.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — a pair-owned plan revision folding the pair Implementer's review findings, filed with its replacement measurement; no design byte, no ruling byte; W-4 neither reopened nor widened; the token waits on the implementer's exact-hash approve; m-3's seven-point review at the landed sha, the first push (master's routed act, R-4.51), publication, and release keep their gates; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: intg-countgate-plan
DESIGN_LOCK_ID: m3-countgate-repair-20260830 @ sha256 0099d1cf4aeb39f3732e823657ec0b78434f6a638db70b69a3fd6bd4dd717875
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: intg-countgate-plan-20260830 @ sha256 b2c9295647188ff97fd0a4846562031c9c9a8ddfe84a9d67e10ff112143efc2e
FROM: intg.pair-planner
TO: master.master-planner
CC: operator, master.master-reviewer, intg.pair-implementer, m-3.planner, m-3.implementer, m-4.planner
SUBJECT: SITREP — count-gate plan rev5 FILED (022403; intg-countgate-plan-5; artifact b2c92956; identities preserved) folding the rev4 must-revise 020651 (F1 stale handoff refs → plan-5; F2 discriminator arms capture $? into .rc files and assert rc2 == 0 and rc1 != 0 iff a present name; F3 the one environment scoped to the five XML runs + scout + arm 2, arm 1 the control) — W-4 replacement measurement: exactly ONE fired line, the 0099d1cf red (archive b5fe79ca; zero lineage errors); next = implementer's exact-hash review → token intg-countgate-impl-2; the freeze re-imposes at that commit

## The W-4 replacement re-measurement, VERBATIM (root mode; the instrument of record)

```text
command   python3 <kit 2.9.2>/tools/relay-lint.py --relay-root .relays/intg --no-freshness   (484 s wall)
archive   results/lint-root-sweep-countgate-plan-rev5-20260905.txt  sha256 b5fe79ca2b4e6fb2775eff364028d9e716772ad984a6b071dd8c81e03d444c23
          461 lines; rc 1; 424 ERROR / 37 WARN root-wide

FIRED SET ON THE CITING CARRIER (exactly one line):
ERROR .relays/intg: intg-countgate/PLAN-pair-planner-20260905-022403.md: DESIGN_LOCK_ID 'm3-countgate-repair-20260830 @ sha256 0099d1cf4aeb39f3732e823657ec0b78434f6a638db70b69a3fd6bd4dd717875' has no earlier same-owner DESIGN relay carrying matching DESIGN_DOC_ID

per-file contrast (NOT closure): relay-lint.py --no-freshness intg-countgate/PLAN-pair-planner-20260905-022403.md → OK
classes   design-lineage 64 → 66 (the carrier + its draft echo); not-consumed 280 → 285 (020651 + its drafts, the rev5 carrier + draft — the standing class);
          lineage-walk errors 0
identity  the fired identity is the W-4-covered design (0099d1cf) on the W-4-bound lineage — this entry REPLACES the rev4 measurement (f9b957a3)
```

ACTIONS_GIT_REF: docs-lane writes only — the rev5 artifact, the filed 022403, the archived re-measurement, ROADMAP's must-revise + rev5 entry, and this SITREP via the engine; commit path-scoped follows (the freeze stays lifted until the next token's commit); no workflow byte, no product byte, no observation run
RELAY_LINT: engine-rendered submissions; per-file v2.9.2 lint rides the daemon gate; drafts pre-linted per-file; every upstream route directory and every pair cycle directory re-listed immediately before each submit; the root-mode sweep above is the instrument of record
FINAL_GIT_STATUS_SHORT:
 M .relays/intg/INDEX.md
 M docs/sprints/2026-08-27-intg-consent-fabric/ROADMAP.md
 M docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-countgate-20260830.md
 ?? .relays/intg/.engine/drafts/intg.pair-planner/PLAN-COUNTGATE-REVISION5-REVIEW4-FOLDED.md
 ?? .relays/intg/.engine/drafts/intg.pair-planner/SITREP-COUNTGATE-REV5-FILED-W4-REMEASURED.md
 ?? .relays/intg/intg-countgate/PLAN-pair-planner-20260905-022403.md
 ?? docs/sprints/2026-08-27-intg-consent-fabric/results/lint-root-sweep-countgate-plan-rev5-20260905.txt
Literal path-scoped status for this seat's own writes at authoring time; the shared bivpak tree additionally carries sibling-authored state not claimed clean here.
