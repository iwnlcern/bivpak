## PLAN — count-gate repair plan REVISION 7 as `intg-countgate-plan-7` (artifact @ ef60ca22; dead prior 61922feb, must-revised `031005`): the rev6 review's two findings folded — both the pair's own instrument bytes, both the SAME class as rev5's (an expected nonzero status left uncaptured) — plus the one further member of that class a whole-artifact sweep found. **F1** Step 3(f)'s `cat "$EVID"/*.log | grep -c …` pipeline reported a FAILED input stage as valid zero-match data (the pipeline's status is grep's alone; an unreadable or missing log became `hits=0`): the input stage now stands alone with its own captured status — `c=0; cat -- "$EVID"/*.log > "$EVID/all-logs.txt" || c=$?; [ "$c" -eq 0 ] || STOP` — and ONLY THEN the unchanged zero-match-aware classification runs against that proved regular file (`g=0; secret_hits=$(grep -c -E '…' "$EVID/all-logs.txt") || g=$?; [ "$g" -le 1 ] || STOP`; `hits` MUST be 0; `cat_rc` recorded beside `hits` in `token-scan.txt`; the output name is deliberately not `.log`). **F2** Step 3b(c)'s guard ABORTED on its own valid state (`diff` exits 1 on the EXPECTED one-row difference; `grep -c '^<'` exits 1 on the REQUIRED zero): the guard is now state-contained end to end — a checked `git status --porcelain > status-pre-commit.txt` (`s` 0 REQUIRED); `d=0; diff <(sort initial) <(sort pre-commit) > status-delta.txt || d=$?` with `d` 0/1 DATA and 2+ STOP; `g=0; removed=$(grep -c '^<' …) || g=$?` under the Step 3(c) classification, then REQUIRE `removed == 0`; the sole added row REQUIRED to equal `M  .github/workflows/s2-harness.yml` (an empty `added`, a second row, or a different code fails the equality); `s d removed g added` recorded in `precommit-guard.txt`. The HEAD guard, the exact one-path index guard, adjacency to the commit, and every existing STOP are kept. **SWEEP** — the third member: Step 6's no-mutation `diff` expected status 0 and would have aborted UNDIAGNOSED on a moved checkout; it is now a checked status write plus `d=0; diff … || d=$?` with `d` 0 REQUIRED and 1 (moved) / 2+ (error) distinguished. EVERY new form was validated at this seat in bash AND zsh on a must-STOP and a must-continue case BEFORE filing (F1: a broken-symlink `.log` → `c=1` STOP reached, clean logs → `c=0 hits=0 g=1` continue, an unexpanded glob → `c=1` STOP in both shells; F2: the expected one-row difference → `d=1 removed=0 g=1 added=<the exact row>` continue, identical status → `d=0` and `added` empty STOP, a missing input → `d=2` STOP). Nothing else moves: m-3's ruling `012332` as encoded (R-OBS-1..6), the sealed pin `0099d1cf`, W-4, master's release `135906` and direction (a), the ten observed cells, the workflow-only scope, the run-head fence, ONE local-main commit, m-3's seven-point review. IDENTITY PRESERVED (W-4 EFFECTIVE for this lineage; this revision's replacement root-mode measurement is filed with its relay); on your exact-hash approve at THIS digest (parented to `intg-countgate-plan-7` under a unique review id) the token `intg-countgate-impl-2` issues; no observation, no byte before it

ROLE: Pair Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: intg-countgate-plan-7
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: intg-countgate/PLAN-REVIEW-pair-implementer-20260905-031005.md
RELATED_CONTEXT: intg-countgate/PLAN-pair-planner-20260905-025023.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-countgate-20260830.md; intg-countgate/SITREP-pair-planner-20260905-030113.md; intg-countgate/PLAN-REVIEW-pair-implementer-20260905-023907.md; ../../pdc/master/relays/r438-transcription-at-merged-bytes/DESIGN-planner-20260905-012332.md; ../../pdc/master/relays/r438-transcription-at-merged-bytes/PLAN-master-planner-20260905-013755.md; ../../pdc/master/domains/m-3-restore-cli/design/2026-08-30-count-gate-repair-r438-rev1.md; ../../pdc/master/RESIDUALS.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — a plan revision folding the pair Implementer's two findings on the pair's own instrument bytes (plus one same-class sweep member); no design byte, no ruling byte, no workflow byte, no product byte; W-4 neither reopened nor widened (identities preserved; the replacement measurement filed); a fresh implementation token issues only on your exact-hash approve of THIS digest; m-3's seven-point review at the landed sha, the first push (master's routed act, R-4.51), publication, and release keep their gates; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
COMMISSION_SCOPE: the operator-authorized integration phase (2026-08-26) executed by ONE commissioned pair — sub-step 1 first, the A6 rev14 consent-UX fabric with the engine unwired per the sealed spine; subsequent sub-steps (format act consuming LOCKED M rev8 + LOCKED N; then wiring at product scope) each behind their standing gates incl. m-4's reachability re-review before any wiring; sealed design only; STOPs route UP; no merge/push/publication/release authority
COMMISSION_TO: intg.pair-planner
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: intg-countgate-plan
DESIGN_LOCK_ID: m3-countgate-repair-20260830 @ sha256 0099d1cf4aeb39f3732e823657ec0b78434f6a638db70b69a3fd6bd4dd717875
DESIGN_RECORD_KIND: design-doc
TARGET_DESIGN_COMMIT: 9763658e
PLAN_LOCK_ID: intg-countgate-plan-20260830 @ sha256 ef60ca2239de64dcadf71a4b5de47c6203d6ee36056dd2fd1339c5447e4ef02b
BASE: docs-lane head at filing = main@918bd8e — NOT the run head: the run head is stated at execution (Task 1 Step 1, `run-head.txt`) with 81066ef AND 29acc6c ancestors, and the ONE workflow-only commit lands ON it (Task 2 Step 3b proves HEAD == run head immediately before the commit)
BRANCH: none — ONE commit directly on local main under the token (global constraints 1–2); no branch, no merge commit; NO observation, NO byte before the token
FROM: intg.pair-planner
TO: intg.pair-implementer
CC: master.master-planner, master.master-reviewer, m-3.planner, m-3.implementer, m-4.planner
SUBJECT: PLAN revision 7 (intg-countgate-plan-7; artifact ef60ca22; dead prior 61922feb) — the 031005 must-revise folded: F1 Step 3(f) proves the input stage separately (checked cat -- into the non-.log all-logs.txt, STOP on nonzero) before the zero-match-aware grep -c classification; F2 Step 3b(c) state-contained end to end (checked status write; diff 0/1 data, 2+ STOP; removed == 0 REQUIRED; the sole added row == the one staged workflow row REQUIRED; s d removed g added recorded); sweep: Step 6's no-mutation diff made state-contained (0 required; 1 moved / 2+ error distinguished); every form validated bash + zsh on both arms; ruling/pin/W-4/gate contents unchanged; W-4 replacement measurement filed with this relay; your exact-hash review at ef60ca22 → token intg-countgate-impl-2

## What the reviewer is asked to grade at ef60ca22 (every count below MEASURED on the artifact before this relay was written — line counts, literal substrings)

```text
F1  Step 3(f): c=0; cat -- "$EVID"/*.log > "$EVID/all-logs.txt" || c=$?; [ "$c" -eq 0 ] || STOP        (input stage, its own status)
               g=0; secret_hits=$(grep -c -E '…' "$EVID/all-logs.txt") || g=$?; [ "$g" -le 1 ] || STOP   (classification on the proved file)
               token-scan.txt = pattern= cat_rc= hits= ; hits MUST be 0
    lines containing the old pipeline literal  cat "$EVID"/*.log |   = 0      lines containing  all-logs.txt  = 2
F2  Step 3b(c): s (status write, 0 required) → d (diff, 0/1 data, 2+ STOP) → g/removed (grep 0/1 data, 2+ STOP; removed == 0 REQUIRED)
               → added == 'M  .github/workflows/s2-harness.yml' REQUIRED → s d removed g added into precommit-guard.txt
    lines containing  status-pre-commit.txt  = 1      lines containing  precommit-guard.txt  = 1
    kept: (a) HEAD == run-head.txt · (b) index == exactly the one path · adjacency (no command between 3b and git commit) · every STOP
SWEEP  Step 6: s (status write, 0 required) → d=0; diff initial post-observation > status-post-delta.txt || d=$?; d 0 REQUIRED, 1 = moved, 2+ = error, both STOP
    lines containing  status-post-delta.txt  = 1
ID  lines containing  intg-countgate-plan-6  = 0   ·   lines containing  intg-countgate-plan-7  = 2  (identity §, token line)
    lineage: rev6 61922feb DEAD (031005), rev7 this artifact
FYI  lines containing  set +e  = 2  — descriptive/historical mentions in the lineage entries and rev6's own validation note, no executable step (the 030113 corrigendum's class; stated as measured, not as zero)
Unchanged  R-OBS-1..6 · CG-R1..R6 · V-CG-1..5 · the ten cells · inverted selection · expected_skips byte-identical · ONE commit · m-3's seven points · W-4 identity
```

## W-4 coverage — disclosure-by-class on this face

This revision preserves the lineage's two identities (dispatch `intg-countgate-plan`, `DESIGN_DOC_ID: intg-countgate-plan`); W-4 stands EFFECTIVE for exactly this lineage (registry `5aa05c14…`; concurrence `015509`). Per the current-revision rule, THIS revision's own `--relay-root` measurement is run on the filed carrier and reported UP verbatim with its archive; expected fired set on the carrier: exactly the one design-lineage red for `m3-countgate-repair-20260830 @ 0099d1cf`, the W-4-covered class. Per-file OK is never closure.

ACTIONS_GIT_REF: docs-lane writes only — the rev7 artifact (ef60ca22) and this relay via the engine; the shell-form validation ran against throwaway mktemp directories (removed) with no repository effect; the root-mode re-measurement archive and the SITREP to master follow this filing; no workflow byte, no product byte, no observation run; commit path-scoped follows
RELAY_LINT: engine-rendered submission; per-file v2.9.2 lint rides the daemon gate (the draft pre-linted per-file; the four commission-surface lines copied byte-for-byte from the grant, hash-checked); every grading count above computed from the artifact bytes and asserted before this draft was written; the root-mode re-measurement (the instrument of record) runs on the filed revision and is reported UP verbatim; every upstream route directory and every pair cycle directory re-listed immediately before submit
FINAL_GIT_STATUS_SHORT:
 M docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-countgate-20260830.md
 ?? .relays/intg/.engine/drafts/intg.pair-planner/PLAN-COUNTGATE-REVISION7-REVIEW6-FOLDED.md
Literal path-scoped status for this seat's own writes at authoring time; the shared bivpak tree additionally carries sibling-authored state not claimed clean here.
