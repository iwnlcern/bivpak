## PLAN — count-gate repair plan REVISION 9 as `intg-countgate-plan-9` (artifact @ 652f0d73; dead prior 6235bdda, must-revised `042414`): the rev8 review's one finding folded — a proof-flow gap outside the shell bytes the last three rounds repaired, and mine. **F1** The plan REQUIRED two run-head ancestors: `81066ef` (the isolation landing, the gate's design base) and `29acc6c` (the 2a landing — master's direction (a), transcription AFTER 2a, `013755`; the consumed `221146` token made it mechanical). The run identity (Step 3(g)), the commit message (Task 2 Step 4), and acceptance criterion 1 all CLAIMED both facts, but Task 1 Step 1 executed only the `81066ef` check and acceptance 1 bound only `81066ef` — the `29acc6c` fact could have ridden into the landed commit message unmeasured; the live checkout satisfying it today is not a proof for the head captured after the next token. Verified at the bytes before editing: exactly one `is-ancestor` site in the whole artifact, and Step 1's own "record both" wording recorded only the head. REPAIR: Task 1 Step 1 measures BOTH facts with individually captured statuses — `a1=0; git merge-base --is-ancestor 81066ef "$RUN_HEAD" || a1=$?` and `a2=0; git merge-base --is-ancestor 29acc6c "$RUN_HEAD" || a2=$?`, each REQUIRED 0 (`is-ancestor` exits 1 for a non-ancestor and 128 for an unknown revision; neither is data here, any nonzero is a STOP) — and records the head with both results in `run-head-ancestry.txt`; Step 3(g)'s run identity and Task 2 Step 4's commit message now CITE that recorded file instead of restating the facts; acceptance criterion 1 binds BOTH ancestors to their recorded proofs. The re-observe-on-head-move rule and the Task 2 Step 4 carry are preserved unchanged. VALIDATED at this seat in bash AND zsh on the live repository: both required ancestors → `a1=0 a2=0`; a non-ancestor → 1; an unknown revision → 128; the captured form reaches the comparison in every case. Every rev6–rev8 repair retained (Step 3(f)'s proved input stage; Step 3b's materialized sorts, predicates, and recorded fields; Step 6; Step 0's checked snapshot; HEAD/index guards; adjacency; every STOP). Nothing else moves: m-3's ruling `012332` as encoded (R-OBS-1..6), the sealed pin `0099d1cf`, W-4, master's release `135906` and direction (a), the ten observed cells, the workflow-only scope, the run-head fence, ONE local-main commit, m-3's seven-point review. IDENTITY PRESERVED (W-4 EFFECTIVE for this lineage; this revision's replacement root-mode measurement is filed with its relay); on your exact-hash approve at THIS digest (parented to `intg-countgate-plan-9` under a unique review id) the token `intg-countgate-impl-2` issues; no observation, no byte before it

ROLE: Pair Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: intg-countgate-plan-9
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: intg-countgate/PLAN-REVIEW-pair-implementer-20260905-042414.md
RELATED_CONTEXT: intg-countgate/PLAN-pair-planner-20260905-035228.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-countgate-20260830.md; intg-countgate/PLAN-REVIEW-pair-implementer-20260905-033956.md; intg-countgate/IMPL-pair-planner-20260904-221146.md; intg-countgate/SITREP-pair-planner-20260905-040133.md; ../../pdc/master/relays/r438-transcription-at-merged-bytes/PLAN-master-planner-20260905-013755.md; ../../pdc/master/relays/r438-transcription-at-merged-bytes/DESIGN-planner-20260905-012332.md; ../../pdc/master/domains/m-3-restore-cli/design/2026-08-30-count-gate-repair-r438-rev1.md; ../../pdc/master/RESIDUALS.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — a plan revision folding the pair Implementer's one proof-flow finding on the pair's own plan bytes; no design byte, no ruling byte, no workflow byte, no product byte; W-4 neither reopened nor widened (identities preserved; the replacement measurement filed); a fresh implementation token issues only on your exact-hash approve of THIS digest; m-3's seven-point review at the landed sha, the first push (master's routed act, R-4.51), publication, and release keep their gates; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
COMMISSION_SCOPE: the operator-authorized integration phase (2026-08-26) executed by ONE commissioned pair — sub-step 1 first, the A6 rev14 consent-UX fabric with the engine unwired per the sealed spine; subsequent sub-steps (format act consuming LOCKED M rev8 + LOCKED N; then wiring at product scope) each behind their standing gates incl. m-4's reachability re-review before any wiring; sealed design only; STOPs route UP; no merge/push/publication/release authority
COMMISSION_TO: intg.pair-planner
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: intg-countgate-plan
DESIGN_LOCK_ID: m3-countgate-repair-20260830 @ sha256 0099d1cf4aeb39f3732e823657ec0b78434f6a638db70b69a3fd6bd4dd717875
DESIGN_RECORD_KIND: design-doc
TARGET_DESIGN_COMMIT: 9763658e
PLAN_LOCK_ID: intg-countgate-plan-20260830 @ sha256 652f0d73f6784ddf38757371bc1c1755454a8402b4f64c9f8a6276002f0a1e55
BASE: docs-lane head at filing = main@9ad1a5d — NOT the run head: the run head is stated at execution (Task 1 Step 1, `run-head.txt`) with 81066ef AND 29acc6c ancestors BOTH MEASURED there (`run-head-ancestry.txt`), and the ONE workflow-only commit lands ON it (Task 2 Step 3b proves HEAD == run head immediately before the commit)
BRANCH: none — ONE commit directly on local main under the token (global constraints 1–2); no branch, no merge commit; NO observation, NO byte before the token
FROM: intg.pair-planner
TO: intg.pair-implementer
CC: master.master-planner, master.master-reviewer, m-3.planner, m-3.implementer, m-4.planner
SUBJECT: PLAN revision 9 (intg-countgate-plan-9; artifact 652f0d73; dead prior 6235bdda) — the 042414 must-revise folded: Task 1 Step 1 measures BOTH required ancestors (81066ef and 29acc6c) with captured is-ancestor statuses each required 0 and records head + both results in run-head-ancestry.txt; the run identity and the commit message cite the recorded file; acceptance 1 binds both ancestors; validated bash + zsh on the live repo (0/0, non-ancestor 1, unknown rev 128); every rev6–rev8 repair retained; ruling/pin/W-4/gate contents unchanged; W-4 replacement measurement filed with this relay; your exact-hash review at 652f0d73 → token intg-countgate-impl-2

## What the reviewer is asked to grade at 652f0d73 (every count MEASURED on the artifact and asserted before this relay was written — line counts, literal substrings)

```text
F1  Task 1 Step 1: RUN_HEAD=$(git rev-parse main)
                   a1=0; git merge-base --is-ancestor 81066ef "$RUN_HEAD" || a1=$?      a2=0; git merge-base --is-ancestor 29acc6c "$RUN_HEAD" || a2=$?
                   [ "$a1" -eq 0 ] && [ "$a2" -eq 0 ] || STOP   →   run-head.txt  +  run-head-ancestry.txt (run_head= ancestor_81066ef_rc= ancestor_29acc6c_rc=)
    lines containing  is-ancestor 81066ef  = 1   ·   is-ancestor 29acc6c  = 1   ·   run-head-ancestry.txt  = 5  (Step 1 ×2, Step 3(g), Task 2 Step 4, acceptance 1)
    Step 3(g) run identity + Task 2 Step 4 commit message: both ancestry facts CITED from run-head-ancestry.txt (rc 0 each)
    acceptance 1: "with BOTH `81066ef` AND `29acc6c` ancestors, each proved by its own … status 0 at Task 1 Step 1 and recorded"   lines = 1
    preserved: the re-observe-on-head-move rule (same sentence, unchanged) · Task 2 Step 3b HEAD == run-head.txt · Task 2 Step 4 carry
ID  lines containing  intg-countgate-plan-8  = 0   ·   intg-countgate-plan-9  = 2  (identity §, token line);  lineage: rev8 6235bdda DEAD (042414), rev9 this artifact
Retained  Step 0 s0 · Step 3(f) checked cat -- → all-logs.txt → grep -c · Step 3b s/s1/s2/d/removed/g/added · Step 6 s/d · (a) HEAD guard · (b) one-path index · adjacency · every STOP
          lines containing  d=0; diff <(  = 0   ·   cat "$EVID"/*.log |  = 0
Unchanged  R-OBS-1..6 · CG-R1..R6 · V-CG-1..5 · the ten cells · inverted selection · expected_skips byte-identical · ONE commit · m-3's seven points · W-4 identity
```

## W-4 coverage — disclosure-by-class on this face

This revision preserves the lineage's two identities (dispatch `intg-countgate-plan`, `DESIGN_DOC_ID: intg-countgate-plan`); W-4 stands EFFECTIVE for exactly this lineage (registry `5aa05c14…`; concurrence `015509`). Per the current-revision rule, THIS revision's own `--relay-root` measurement is run on the filed carrier and reported UP verbatim with its archive; expected fired set on the carrier: exactly the one design-lineage red for `m3-countgate-repair-20260830 @ 0099d1cf`, the W-4-covered class. Per-file OK is never closure.

ACTIONS_GIT_REF: docs-lane writes only — the rev9 artifact (652f0d73) and this relay via the engine; the ancestry-form validation ran read-only `git merge-base` queries against the live repository with no repository effect; the root-mode re-measurement archive and the SITREP to master follow this filing; no workflow byte, no product byte, no observation run; commit path-scoped follows
RELAY_LINT: engine-rendered submission; per-file v2.9.2 lint rides the daemon gate (the draft pre-linted per-file; the four commission-surface lines copied byte-for-byte from the grant, hash-checked); every grading count above computed from the artifact bytes and asserted before this draft was written; the root-mode re-measurement (the instrument of record) runs on the filed revision and is reported UP verbatim; every upstream route directory and every pair cycle directory re-listed immediately before submit
FINAL_GIT_STATUS_SHORT:
 M docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-countgate-20260830.md
 ?? .relays/intg/.engine/drafts/intg.pair-planner/PLAN-COUNTGATE-REVISION9-REVIEW8-FOLDED.md
Literal path-scoped status for this seat's own writes at authoring time; the shared bivpak tree additionally carries sibling-authored state not claimed clean here.
