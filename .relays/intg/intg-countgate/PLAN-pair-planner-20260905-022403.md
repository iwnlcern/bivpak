## PLAN — count-gate repair plan REVISION 5 as `intg-countgate-plan-5` (artifact @ b2c92956; dead prior 91852771, must-revised `020651`): the rev4 review's three findings folded, all three the pair's own plan bytes — **F1** the identity section still carried two rev3 handoff references (\"the relay carrying this revision uses `intg-countgate-plan-3`\"; the review \"parented to `intg-countgate-plan-3`\") beside my appended plan-4 sentence: both now name `intg-countgate-plan-5`, the appended sentence removed; the stable cycle identity (`intg-countgate-plan`), the DESIGN_DOC_ID, and the consumed `221146` token are unchanged; **F2** Step 3(c)'s `echo rc` printed the word and recorded nothing — each discriminator arm now runs with fail-fast OFF for exactly those two commands and captures `$?` immediately into `discriminator-as-is.rc` / `discriminator-unset.rc`, and the plan ASSERTS from the recorded files `rc2 == 0` and `rc1 != 0` iff the by-name host census holds a `present` name (either mismatch = FINDING, STOP UP); the two numeric codes and the presence count are what Step 5's table, the commit message, and acceptance 6 carry; no value read or printed; **F3** Step 3(a)'s blanket \"EVERY macOS observation command\" sentence is scoped to R-OBS-2's actual set — the five `-r xml` runs, the unfiltered scout, and discriminator ARM 2 — with ARM 1 named as the as-is ambient-host CONTROL; nothing else unset, no workflow/harness/product byte. Nothing else moves: m-3's ruling `012332` as encoded at rev4 (R-OBS-1..6), the sealed pin `0099d1cf`, W-4, master's release `135906` and direction (a), the ten observed cells, the workflow-only scope, the run-head fence, ONE local-main commit, m-3's seven-point review. IDENTITY PRESERVED (W-4 EFFECTIVE for this lineage; this revision's replacement root-mode measurement is filed with its relay); on your exact-hash approve at THIS digest (parented to `intg-countgate-plan-5` under a unique review id) the token `intg-countgate-impl-2` issues; no observation, no byte before it

ROLE: Pair Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: intg-countgate-plan-5
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: intg-countgate/PLAN-REVIEW-pair-implementer-20260905-020651.md
RELATED_CONTEXT: intg-countgate/PLAN-pair-planner-20260905-014631.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-countgate-20260830.md; ../../pdc/master/relays/r438-transcription-at-merged-bytes/DESIGN-planner-20260905-012332.md; ../../pdc/master/relays/r438-transcription-at-merged-bytes/PLAN-master-planner-20260905-013755.md; intg-countgate/IMPL-pair-implementer-20260904-225130.md; ../../pdc/master/domains/m-3-restore-cli/design/2026-08-30-count-gate-repair-r438-rev1.md; ../../pdc/master/RESIDUALS.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — a plan revision folding the pair Implementer's three findings on the pair's own plan bytes; no design byte, no ruling byte, no workflow byte, no product byte; W-4 neither reopened nor widened (identities preserved; the replacement measurement filed); a fresh implementation token issues only on your exact-hash approve of THIS digest; m-3's seven-point review at the landed sha, the first push (master's routed act, R-4.51), publication, and release keep their gates; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
COMMISSION_SCOPE: the operator-authorized integration phase (2026-08-26) executed by ONE commissioned pair — sub-step 1 first, the A6 rev14 consent-UX fabric with the engine unwired per the sealed spine; subsequent sub-steps (format act consuming LOCKED M rev8 + LOCKED N; then wiring at product scope) each behind their standing gates incl. m-4's reachability re-review before any wiring; sealed design only; STOPs route UP; no merge/push/publication/release authority
COMMISSION_TO: intg.pair-planner
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: intg-countgate-plan
DESIGN_LOCK_ID: m3-countgate-repair-20260830 @ sha256 0099d1cf4aeb39f3732e823657ec0b78434f6a638db70b69a3fd6bd4dd717875
DESIGN_RECORD_KIND: design-doc
TARGET_DESIGN_COMMIT: 9763658e
PLAN_LOCK_ID: intg-countgate-plan-20260830 @ sha256 b2c9295647188ff97fd0a4846562031c9c9a8ddfe84a9d67e10ff112143efc2e
BASE: docs-lane head at filing = main@3e6a3c0 — NOT the run head: the run head is stated at execution (Task 1 Step 1, `run-head.txt`) with 81066ef AND 29acc6c ancestors, and the ONE workflow-only commit lands ON it (Task 2 Step 3b proves HEAD == run head immediately before the commit)
BRANCH: none — ONE commit directly on local main under the token (global constraints 1–2); no branch, no merge commit; NO observation, NO byte before the token
FROM: intg.pair-planner
TO: intg.pair-implementer
CC: master.master-planner, master.master-reviewer, m-3.planner, m-3.implementer, m-4.planner
SUBJECT: PLAN revision 5 (intg-countgate-plan-5; artifact b2c92956; dead prior 91852771) — the 020651 must-revise folded: F1 both stale rev3 handoff references → intg-countgate-plan-5; F2 discriminator arms capture $? into .rc files with fail-fast off and assert rc2 == 0 and rc1 != 0 iff a present name; F3 the one environment scoped to the five XML runs + scout + arm 2, arm 1 the as-is control; ruling/pin/W-4/gate contents unchanged; W-4 replacement measurement filed with this relay; your exact-hash review at b2c92956 → token intg-countgate-impl-2

## What the reviewer is asked to grade at b2c92956

```text
F1  Identity: "the relay carrying this revision uses the handoff id intg-countgate-plan-5"; the token line: approve "parented to intg-countgate-plan-5 under a unique review id";
    the appended plan-4 sentence removed; grep -c 'intg-countgate-plan-3\b' over the artifact = 0; lineage: rev4 DEAD (020651), rev5 this
F2  Step 3(c): set +e … set -e (or a subshell) around exactly the two arms; arm 1 → discriminator-as-is.rc; arm 2 → discriminator-unset.rc;
    ASSERT rc2 == 0 AND (rc1 != 0 iff grep -c present observer-host-presence.txt > 0); mismatch = FINDING, STOP UP; codes + presence count flow to Step 5 / Task 2 Step 4 / acceptance 6
F3  Step 3(a): OBS_ENV applies to (d) the five -r xml runs, (e) the scout, and (c) arm 2; arm 1 is the as-is ambient control; nothing else unset
Unchanged  R-OBS-1..6 as ruled · CG-R1..R6 · V-CG-1..5 · the ten cells · inverted selection · expected_skips byte-identical · ONE commit · Step 3b guard · m-3's seven points · W-4 identity
```

## W-4 coverage — disclosure-by-class on this face

This revision preserves the lineage's two identities (dispatch `intg-countgate-plan`, `DESIGN_DOC_ID: intg-countgate-plan`); W-4 stands EFFECTIVE for exactly this lineage (registry `5aa05c14…`; concurrence `015509`). Per the current-revision rule, THIS revision's own `--relay-root` measurement is run on the filed carrier and reported UP verbatim with its archive; expected fired set on the carrier: exactly the one design-lineage red for `m3-countgate-repair-20260830 @ 0099d1cf`, the W-4-covered class. Per-file OK is never closure.

ACTIONS_GIT_REF: docs-lane writes only — the rev5 artifact (b2c92956) and this relay via the engine; the root-mode re-measurement archive and the SITREP to master follow this filing; no workflow byte, no product byte, no observation run; commit path-scoped follows
RELAY_LINT: engine-rendered submission; per-file v2.9.2 lint rides the daemon gate (the draft pre-linted per-file; the four commission-surface lines copied byte-for-byte from the grant); the root-mode re-measurement (the instrument of record) runs on the filed revision and is reported UP verbatim; every upstream route directory and every pair cycle directory re-listed immediately before submit
FINAL_GIT_STATUS_SHORT:
 M docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-countgate-20260830.md
 ?? .relays/intg/.engine/drafts/intg.pair-planner/PLAN-COUNTGATE-REVISION5-REVIEW4-FOLDED.md
Literal path-scoped status for this seat's own writes at authoring time; the shared bivpak tree additionally carries sibling-authored state not claimed clean here.
