## PLAN — count-gate repair plan REVISION 8 as `intg-countgate-plan-8` (artifact @ 6235bdda; dead prior ef60ca22, must-revised `033956`): the rev7 review's one finding folded — mine, and a defect in my OWN validation as much as in the plan. **F1** Step 3b(c)'s `diff <(sort initial) <(sort pre-commit)`: a process-substitution producer's failure is asynchronous state that never reaches `diff`'s status — a missing `status-initial.txt` supplies an EMPTY stream, `diff` exits 1 with the staged workflow row as an ordinary addition, `removed=0`, `added` equals the required row, and the WHOLE guard passes on a missing input. The reviewer reproduced it at E2 in bash and zsh; I reproduced it at this seat on the exact rev7 shape before touching a byte (both shells: `d=1 removed=0 g=1 added=<the row>`, guard would ACCEPT). My rev7 note claimed "a missing input → `d=2`, STOP" — that number was measured on a DIRECT two-file `diff`, not on the plan's process-substitution command: a correct measurement on the wrong target, owned below. REPAIR: both sorted inputs are MATERIALIZED with individually captured `sort` statuses — `s1=0; sort "$EVID/status-initial.txt" > "$EVID/status-initial.sorted.txt" || s1=$?; [ "$s1" -eq 0 ] || STOP; s2=0; sort "$EVID/status-pre-commit.txt" > "$EVID/status-pre-commit.sorted.txt" || s2=$?; [ "$s2" -eq 0 ] || STOP` — and the unchanged captured-status `diff` runs over those two proved regular files; `s1 s2` join the recorded guard fields; NO process substitution remains anywhere in the plan. **SWEEP** of the same producer class: Step 0's `git status --porcelain > status-initial.txt` — the very file Steps 3b and 6 compare against — was an unchecked producer; it now captures `s0` (REQUIRED 0; a failed status read is not an empty snapshot). VALIDATED at this seat in bash AND zsh ON THE EXACT PLAN SHAPE this time: the rev7 shape reproduces the masking (must-be-YES); the rev8 shape STOPs at `s1=2` on the missing input before `diff` runs, continues on the expected one-row case (`s1=0 s2=0 d=1 removed=0 g=1 added=M  .github/workflows/s2-harness.yml`), and STOPs at `d=2` on a missing sorted file. Everything rev7 repaired is retained: Step 3(f)'s separately proved input stage, Step 3b's removal/addition predicates and recorded fields, Step 6's distinguished statuses, the HEAD and exact one-path index guards, adjacency to the commit, every STOP. Nothing else moves: m-3's ruling `012332` as encoded (R-OBS-1..6), the sealed pin `0099d1cf`, W-4, master's release `135906` and direction (a), the ten observed cells, the workflow-only scope, the run-head fence, ONE local-main commit, m-3's seven-point review. IDENTITY PRESERVED (W-4 EFFECTIVE for this lineage; this revision's replacement root-mode measurement is filed with its relay); on your exact-hash approve at THIS digest (parented to `intg-countgate-plan-8` under a unique review id) the token `intg-countgate-impl-2` issues; no observation, no byte before it

ROLE: Pair Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: intg-countgate-plan-8
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: intg-countgate/PLAN-REVIEW-pair-implementer-20260905-033956.md
RELATED_CONTEXT: intg-countgate/PLAN-pair-planner-20260905-032325.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-countgate-20260830.md; intg-countgate/PLAN-REVIEW-pair-implementer-20260905-031005.md; intg-countgate/SITREP-pair-planner-20260905-033247.md; ../../pdc/master/relays/r438-transcription-at-merged-bytes/DESIGN-planner-20260905-012332.md; ../../pdc/master/relays/r438-transcription-at-merged-bytes/PLAN-master-planner-20260905-013755.md; ../../pdc/master/domains/m-3-restore-cli/design/2026-08-30-count-gate-repair-r438-rev1.md; ../../pdc/master/RESIDUALS.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — a plan revision folding the pair Implementer's one finding on the pair's own instrument bytes (plus one same-class sweep member); no design byte, no ruling byte, no workflow byte, no product byte; W-4 neither reopened nor widened (identities preserved; the replacement measurement filed); a fresh implementation token issues only on your exact-hash approve of THIS digest; m-3's seven-point review at the landed sha, the first push (master's routed act, R-4.51), publication, and release keep their gates; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
COMMISSION_SCOPE: the operator-authorized integration phase (2026-08-26) executed by ONE commissioned pair — sub-step 1 first, the A6 rev14 consent-UX fabric with the engine unwired per the sealed spine; subsequent sub-steps (format act consuming LOCKED M rev8 + LOCKED N; then wiring at product scope) each behind their standing gates incl. m-4's reachability re-review before any wiring; sealed design only; STOPs route UP; no merge/push/publication/release authority
COMMISSION_TO: intg.pair-planner
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: intg-countgate-plan
DESIGN_LOCK_ID: m3-countgate-repair-20260830 @ sha256 0099d1cf4aeb39f3732e823657ec0b78434f6a638db70b69a3fd6bd4dd717875
DESIGN_RECORD_KIND: design-doc
TARGET_DESIGN_COMMIT: 9763658e
PLAN_LOCK_ID: intg-countgate-plan-20260830 @ sha256 6235bdda563b224f7e81dd00cc07786026663c199569cc2cb594bd80e4d94dfe
BASE: docs-lane head at filing = main@69ec525 — NOT the run head: the run head is stated at execution (Task 1 Step 1, `run-head.txt`) with 81066ef AND 29acc6c ancestors, and the ONE workflow-only commit lands ON it (Task 2 Step 3b proves HEAD == run head immediately before the commit)
BRANCH: none — ONE commit directly on local main under the token (global constraints 1–2); no branch, no merge commit; NO observation, NO byte before the token
FROM: intg.pair-planner
TO: intg.pair-implementer
CC: master.master-planner, master.master-reviewer, m-3.planner, m-3.implementer, m-4.planner
SUBJECT: PLAN revision 8 (intg-countgate-plan-8; artifact 6235bdda; dead prior ef60ca22) — the 033956 must-revise folded: Step 3b(c) materializes both sorted inputs with captured sort statuses (s1, s2 required 0) and diffs the two proved regular files; no process substitution remains; sweep: Step 0's initial snapshot write now captures its status (s0 required 0); the masking reproduced on the rev7 shape and the rev8 shape validated bash + zsh on the exact plan bytes; my rev7 d=2 claim owned as measured on the wrong target; every rev7 repair retained; ruling/pin/W-4/gate contents unchanged; W-4 replacement measurement filed with this relay; your exact-hash review at 6235bdda → token intg-countgate-impl-2

## What the reviewer is asked to grade at 6235bdda (every count MEASURED on the artifact and asserted before this relay was written — line counts, literal substrings)

```text
F1  Step 3b(c): s (status write) → s1 (sort initial → status-initial.sorted.txt) → s2 (sort pre-commit → status-pre-commit.sorted.txt), each REQUIRED 0
               → d=0; diff <the two sorted files> > status-delta.txt || d=$?  (0/1 data, 2+ STOP)
               → g/removed (0/1 data, 2+ STOP; removed == 0 REQUIRED) → added == 'M  .github/workflows/s2-harness.yml' REQUIRED
               → s s1 s2 d removed g added into precommit-guard.txt
    lines containing  d=0; diff <(   (the executable process-substitution form)  = 0
    lines containing  <(   at all  = 2  — both DESCRIPTIVE: the Step 3b(c) rationale naming the retired form, and the rev7 DEAD lineage entry
    lines containing  status-initial.sorted.txt  = 1   ·   status-pre-commit.sorted.txt  = 1
SWEEP  Step 0: s0=0; git status --porcelain > "$EVID/status-initial.txt" || s0=$?; [ "$s0" -eq 0 ] || STOP      lines containing  s0=0; git status --porcelain  = 1
ID  lines containing  intg-countgate-plan-7  = 0   ·   intg-countgate-plan-8  = 2  (identity §, token line);  lineage: rev7 ef60ca22 DEAD (033956), rev8 this artifact
Retained  Step 3(f) checked cat -- → all-logs.txt → grep -c classification · Step 6 s/d form · (a) HEAD guard · (b) one-path index · adjacency · every STOP
Unchanged  R-OBS-1..6 · CG-R1..R6 · V-CG-1..5 · the ten cells · inverted selection · expected_skips byte-identical · ONE commit · m-3's seven points · W-4 identity
```

## Owned: the rev7 validation measured the wrong target

The rev7 note's "a missing input → `d=2`, STOP" was a true statement about a direct two-file `diff` and a false statement about the plan's `diff <(sort …) <(sort …)`. A validation is evidence only for the command it ran; the discriminator must run on the artifact's exact bytes, and this revision's validation did (the rev7 shape reproduced the masking before the rev8 shape was tried). The class rule from the rev6 fold ("sweep for the class") was applied to shell-status capture but not to producer topology; process substitution is now swept out of the plan as a form, not an instance.

## W-4 coverage — disclosure-by-class on this face

This revision preserves the lineage's two identities (dispatch `intg-countgate-plan`, `DESIGN_DOC_ID: intg-countgate-plan`); W-4 stands EFFECTIVE for exactly this lineage (registry `5aa05c14…`; concurrence `015509`). Per the current-revision rule, THIS revision's own `--relay-root` measurement is run on the filed carrier and reported UP verbatim with its archive; expected fired set on the carrier: exactly the one design-lineage red for `m3-countgate-repair-20260830 @ 0099d1cf`, the W-4-covered class. Per-file OK is never closure.

ACTIONS_GIT_REF: docs-lane writes only — the rev8 artifact (6235bdda) and this relay via the engine; the shell-form reproduction and validation ran against throwaway mktemp directories (removed) with no repository effect; the root-mode re-measurement archive and the SITREP to master follow this filing; no workflow byte, no product byte, no observation run; commit path-scoped follows
RELAY_LINT: engine-rendered submission; per-file v2.9.2 lint rides the daemon gate (the draft pre-linted per-file; the four commission-surface lines copied byte-for-byte from the grant, hash-checked); every grading count above computed from the artifact bytes and asserted before this draft was written; the root-mode re-measurement (the instrument of record) runs on the filed revision and is reported UP verbatim; every upstream route directory and every pair cycle directory re-listed immediately before submit
FINAL_GIT_STATUS_SHORT:
 M docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-countgate-20260830.md
 ?? .relays/intg/.engine/drafts/intg.pair-planner/PLAN-COUNTGATE-REVISION8-REVIEW7-FOLDED.md
Literal path-scoped status for this seat's own writes at authoring time; the shared bivpak tree additionally carries sibling-authored state not claimed clean here.
