## PLAN — count-gate repair plan REVISION 6 as `intg-countgate-plan-6` (artifact @ 61922feb; dead prior b2c92956, must-revised `023907`): the rev5 review's two findings folded, both the pair's own instrument bytes — **F1** the permitted `set +e` … `set -e` form followed by `grep -c` ABORTED on the VALID zero state (zero present names; zero secret matches — `grep -c` prints 0 and exits 1; under the restored `-e` the shell exits before the comparison; the reviewer reproduced it at E2 in zsh): replaced by ONE exact, state-contained capture form used everywhere — `rc=0; <command> || rc=$?` for the two ctest arms, and `g=0; n=$(grep -c …) || g=$?` with `g ≤ 1` = a count (valid data) and `g ≥ 2` = a real grep/input error (STOP) for the presence count and the token scan (over the CONCATENATED logs, one integer) — the caller's fail-fast state is never changed, zero presence and zero secret matches are SUCCESSFUL data, real errors are still distinguished; VALIDATED at this seat in bash AND zsh on the must-pass and must-fail cases (zero-match → n=0 g=1 reached; one-match → n=1 g=0; missing file → g=2; the `||` arm form captures the status and continues); **F2** the new predicate was asserted only inside Step 3 — the presence count and the RECORDED predicate results (`discriminator-predicate.txt` = `rc1 rc2 present_count iff=PASS|FAIL hygiene=PASS|FAIL`) now flow into Step 5's environment block, Task 2 Step 4's commit message, and acceptance criterion 6, which binds BOTH arms and the iff (`rc2 == 0` AND `rc1 != 0` iff `present_count > 0`). Nothing else moves: m-3's ruling `012332` as encoded (R-OBS-1..6), the sealed pin `0099d1cf`, W-4, master's release `135906` and direction (a), the ten observed cells, the workflow-only scope, the run-head fence, ONE local-main commit, m-3's seven-point review. IDENTITY PRESERVED (W-4 EFFECTIVE for this lineage; this revision's replacement root-mode measurement is filed with its relay); on your exact-hash approve at THIS digest (parented to `intg-countgate-plan-6` under a unique review id) the token `intg-countgate-impl-2` issues; no observation, no byte before it

ROLE: Pair Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: intg-countgate-plan-6
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: intg-countgate/PLAN-REVIEW-pair-implementer-20260905-023907.md
RELATED_CONTEXT: intg-countgate/PLAN-pair-planner-20260905-022403.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-countgate-20260830.md; intg-countgate/PLAN-REVIEW-pair-implementer-20260905-020651.md; ../../pdc/master/relays/r438-transcription-at-merged-bytes/DESIGN-planner-20260905-012332.md; ../../pdc/master/relays/r438-transcription-at-merged-bytes/PLAN-master-planner-20260905-013755.md; ../../pdc/master/domains/m-3-restore-cli/design/2026-08-30-count-gate-repair-r438-rev1.md; ../../pdc/master/RESIDUALS.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — a plan revision folding the pair Implementer's two findings on the pair's own instrument bytes; no design byte, no ruling byte, no workflow byte, no product byte; W-4 neither reopened nor widened (identities preserved; the replacement measurement filed); a fresh implementation token issues only on your exact-hash approve of THIS digest; m-3's seven-point review at the landed sha, the first push (master's routed act, R-4.51), publication, and release keep their gates; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
COMMISSION_SCOPE: the operator-authorized integration phase (2026-08-26) executed by ONE commissioned pair — sub-step 1 first, the A6 rev14 consent-UX fabric with the engine unwired per the sealed spine; subsequent sub-steps (format act consuming LOCKED M rev8 + LOCKED N; then wiring at product scope) each behind their standing gates incl. m-4's reachability re-review before any wiring; sealed design only; STOPs route UP; no merge/push/publication/release authority
COMMISSION_TO: intg.pair-planner
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: intg-countgate-plan
DESIGN_LOCK_ID: m3-countgate-repair-20260830 @ sha256 0099d1cf4aeb39f3732e823657ec0b78434f6a638db70b69a3fd6bd4dd717875
DESIGN_RECORD_KIND: design-doc
TARGET_DESIGN_COMMIT: 9763658e
PLAN_LOCK_ID: intg-countgate-plan-20260830 @ sha256 61922feb603838294d5fb7680c8553105eb37227eaf1f37b56e98f317d3044cf
BASE: docs-lane head at filing = main@3bea52f — NOT the run head: the run head is stated at execution (Task 1 Step 1, `run-head.txt`) with 81066ef AND 29acc6c ancestors, and the ONE workflow-only commit lands ON it (Task 2 Step 3b proves HEAD == run head immediately before the commit)
BRANCH: none — ONE commit directly on local main under the token (global constraints 1–2); no branch, no merge commit; NO observation, NO byte before the token
FROM: intg.pair-planner
TO: intg.pair-implementer
CC: master.master-planner, master.master-reviewer, m-3.planner, m-3.implementer, m-4.planner
SUBJECT: PLAN revision 6 (intg-countgate-plan-6; artifact 61922feb; dead prior b2c92956) — the 023907 must-revise folded: F1 one state-contained capture form everywhere (rc=0; cmd || rc=$?; grep counts with g ≤ 1 as data, g ≥ 2 as STOP; fail-fast never toggled; zero matches = success; validated in bash + zsh); F2 the presence count and recorded iff/hygiene predicate results carried into Step 5, the commit message, and acceptance 6 (both arms + the iff bound); ruling/pin/W-4/gate contents unchanged; W-4 replacement measurement filed with this relay; your exact-hash review at 61922feb → token intg-countgate-impl-2

## What the reviewer is asked to grade at 61922feb

```text
F1  Step 3(c): rc1=0; ctest … || rc1=$?  → discriminator-as-is.rc ;  rc2=0; "${OBS_ENV[@]}" ctest … || rc2=$?  → discriminator-unset.rc
             g=0; present_count=$(grep -c present observer-host-presence.txt) || g=$?; [ "$g" -le 1 ] || STOP  → observer-present-count.txt
             predicate from the files: rc2 == 0 AND (rc1 != 0 iff present_count > 0) → discriminator-predicate.txt (rc1 rc2 present_count iff= hygiene=); both PASS to continue
    Step 3(f): g=0; secret_hits=$(cat "$EVID"/*.log | grep -c -E '…') || g=$?; [ "$g" -le 1 ] || STOP; hits MUST be 0 → token-scan.txt
    no set +e anywhere (grep -c 'set +e' over the artifact = 0); the caller's -e state untouched
F2  Step 5 block: + presence count + iff=/hygiene= + token-scan count · Task 2 Step 4 message: the same · acceptance 6: rc2 == 0 AND (rc1 != 0 iff present_count > 0), all recorded
ID  handoff intg-countgate-plan-6 in the identity section and the token line (grep -c 'plan-5\b' = 0); lineage rev5 DEAD (023907), rev6 this
Unchanged  R-OBS-1..6 · CG-R1..R6 · V-CG-1..5 · the ten cells · inverted selection · expected_skips byte-identical · ONE commit · Step 3b guard · m-3's seven points · W-4 identity
```

## W-4 coverage — disclosure-by-class on this face

This revision preserves the lineage's two identities (dispatch `intg-countgate-plan`, `DESIGN_DOC_ID: intg-countgate-plan`); W-4 stands EFFECTIVE for exactly this lineage (registry `5aa05c14…`; concurrence `015509`). Per the current-revision rule, THIS revision's own `--relay-root` measurement is run on the filed carrier and reported UP verbatim with its archive; expected fired set on the carrier: exactly the one design-lineage red for `m3-countgate-repair-20260830 @ 0099d1cf`, the W-4-covered class. Per-file OK is never closure.

ACTIONS_GIT_REF: docs-lane writes only — the rev6 artifact (61922feb) and this relay via the engine; the shell-idiom validation ran in /tmp-free one-liners with no repository effect; the root-mode re-measurement archive and the SITREP to master follow this filing; no workflow byte, no product byte, no observation run; commit path-scoped follows
RELAY_LINT: engine-rendered submission; per-file v2.9.2 lint rides the daemon gate (the draft pre-linted per-file; the four commission-surface lines copied byte-for-byte from the grant); the root-mode re-measurement (the instrument of record) runs on the filed revision and is reported UP verbatim; every upstream route directory and every pair cycle directory re-listed immediately before submit
FINAL_GIT_STATUS_SHORT:
 M docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-countgate-20260830.md
 ?? .relays/intg/.engine/drafts/intg.pair-planner/PLAN-COUNTGATE-REVISION6-REVIEW5-FOLDED.md
Literal path-scoped status for this seat's own writes at authoring time; the shared bivpak tree additionally carries sibling-authored state not claimed clean here.
