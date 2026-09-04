## PLAN revision 15 — artifact `plans/PL-intg-substep2a-20260830.md` @ sha256 beba597c (dead priors: 84061879 and the twelve before it; same identity via engine supersession): the rev14 must-revise `225905` folded, all three findings — **F1** the tidy coverage receipt was UNOBSERVABLE as commanded (ordinary CTest hides a passing test's stdout; the rev13 log had no `clang-tidy coverage:` line for exactly that reason): Step 4b now runs the row VERBOSE — `ctest --preset ci -R '^safety-tidy-analyzer$' -V 2>&1 | tee <tidy log>`, `tidy_rc` = ctest's exit through the pipe — retains that stdout and requires EXACTLY ONE `clang-tidy coverage: <N> results == <N> sources` line with equal N ≥ 1, rejecting `COVERAGE FAILURE:`; the verbose form carried in the headline, Step 4b, Task 4 T-3, and acceptance 12; **F2** the rev14 fold rule had weakened exact-hunk authority to path-only authority — RESTORED at Step 4b and Step 0-quater (iv): the ONLY bytes that may exist vs `retained-task3b-b09e192` are the SIX AUTHORIZED HUNKS (T-1's header line `manifest.hpp:78`; the four T-4 sites `manifest.cpp` `:836` `:905` `:2176` `:2179`; the `dot{}` line `tests/test_manifest.cpp:1356`); an enumerated red whose correction is one of those hunks done differently folds THERE and the whole gate re-runs to zero; an enumerated red needing ANY OTHER byte is a STOP through me even inside the three checkpoint files — a fourth path a subset of that rule; the keep-going census is an OBSERVATION mechanism, not repair authority; **F3** Task 4's T-5 bullet now names the CANDIDATE head, not the dead rev13 head; also folded: the diagnostic count is judged on the PRINTED integer, never `grep -c`'s exit status (1 on zero matches by design). Nothing else moves (Step 0-quater's `dot{}` NSDMI, the accepted `find_field_unordered` spelling, the keep-going build, the three-path Step 5 proofs all as at rev14); identity UNCHANGED (W-5's frozen selector) and this revision's replacement root-mode measurement is filed with its relay — on your exact-hash approve at THIS digest the fresh token `intg-substep2a-impl-5` issues; `b09e192` stays FROZEN with the held two-file repair on it; no byte moves before the token

ROLE: Pair Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: intg-substep2a-plan
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: intg-substep2a/PLAN-REVIEW-pair-implementer-20260903-225905.md
RELATED_CONTEXT: intg-substep2a/PLAN-pair-planner-20260903-223053.md; intg-substep2a/IMPL-pair-implementer-20260903-222330.md; ../../pdc/master/relays/intg-substep2a-format-act/DESIGN-planner-20260903-183510.md; ../../pdc/master/relays/intg-substep2a-format-act/PLAN-master-planner-20260903-183926.md; ../../pdc/master/relays/intg-substep2a-format-act/DESIGN-planner-20260901-231935.md; ../../pdc/master/relays/intg-substep2a-format-act/DESIGN-planner-20260902-034802.md; ../../pdc/master/relays/intg-substep2a-format-act/PLAN-master-planner-20260902-035616.md; ../../pdc/master/domains/m-1-format-engine/design/2026-09-01-ADDENDUM-O-writer-validity-contract.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — a plan revision folding the pair Implementer's three review findings on the pair's own census instrument and STOP boundary; no sealed byte, no product byte, no parser byte, no ref move; no owner fence touched; W-5 neither reopened nor widened (frozen selector, frozen eligible row); a fresh implementation token issues only on your exact-hash approve of THIS digest; m-1's V-FA and m-3's C-6 byte reviews, the merge packet, push, publication, deployment, and release keep their gates; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
COMMISSION_SCOPE: the operator-authorized integration phase (2026-08-26) executed by ONE commissioned pair — sub-step 1 first, the A6 rev14 consent-UX fabric with the engine unwired per the sealed spine; subsequent sub-steps (format act consuming LOCKED M rev8 + LOCKED N; then wiring at product scope) each behind their standing gates incl. m-4's reachability re-review before any wiring; sealed design only; STOPs route UP; no merge/push/publication/release authority
COMMISSION_TO: intg.pair-planner
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: intg-format-act-plan
DESIGN_LOCK_ID: m1-addendum-O-63c46631-lock-20260901
DESIGN_RECORD_KIND: design-doc
LOCKED_DESIGN_SHA256: 63c46631c84ce27ebedbf71c4965e6b0b149919a83118835d78ce29e89d3e577
LOCKED_DESIGN_COMMIT: 40b4f7a3dbfc60e5ab742678bc4e77198845c243
POST_STAMP_SHA256: 0e990bac752986942d9091871a5175820b829dd019d586e8e895461cfff656d2
SECOND_CONSUMED_LOCK: m1-addendum-N-82293732-lock-20260827
THIRD_CONSUMED_LOCK: m1-addendum-M-2966b839-lock-20260825
PLAN_LOCK_ID: intg-substep2a-plan-20260830 @ sha256 beba597c20d43441f6901f4930e4e4141bd866ecdc27c3f8cec3f403dcb0f265
BASE: main@46df8f3c35981a4ae3f77cf3293a4b7212b4b996
BRANCH: intg/format-act at the FROZEN RED candidate b09e1922c16da50b5bef0644d9923a567b98c468 in ../bivpak-intg-format-act with the HELD two-file Step 0-ter repair uncommitted on it (exactly src/core/manifest/manifest.cpp f7a89c8c… + src/core/manifest/manifest.hpp fd12d52b… modified; both retention tags present; index empty — re-verified at this revision); NOT a merge-packet input; NO byte moves before the fresh token
FROM: intg.pair-planner
TO: intg.pair-implementer
CC: master.master-planner, master.master-reviewer, m-1.planner, m-1.implementer, m-3.planner, m-3.implementer
SUBJECT: PLAN revision 15 — artifact @ sha256 beba597c (dead prior 84061879): the 225905 must-revise folded — F1 the tidy row runs VERBOSE (ctest -R '^safety-tidy-analyzer$' -V, stdout retained; exactly one coverage line, equal N ≥ 1; COVERAGE FAILURE rejected) everywhere the receipt is promised; F2 the STOP boundary restored to the SIX authorized hunks (any other byte = STOP, path-inside notwithstanding; the keep-going census observes, never authorizes); F3 T-5 at the candidate head; the printed-integer count rule; identity unchanged; W-5 replacement measurement filed with this relay; your exact-hash review at beba597c → token intg-substep2a-impl-5

## What the reviewer is asked to grade at beba597c

```text
F1  Step 4b: ctest --preset ci -R '^safety-tidy-analyzer$' -V 2>&1 | tee <tidy log>; tidy_rc = ctest's exit via the pipe; the verbose stdout carries EXACTLY ONE
    'clang-tidy coverage: <N> results == <N> sources' line, N equal, N ≥ 1; 'COVERAGE FAILURE:' / no line / unequal N = red; carried in the headline, Step 4b, T-3, acceptance 12
F2  Step 4b + Step 0-quater (iv): the six authorized hunks — manifest.hpp:78 (T-1) · manifest.cpp :836 :905 :2176 :2179 (T-4) · tests/test_manifest.cpp:1356 (dot{}) —
    are the ONLY bytes that may exist vs retained-task3b-b09e192; a red whose fix is one of them done differently folds there and the WHOLE gate re-runs to zero;
    a red needing any other byte = STOP through the Planner, even inside the three files (a fourth path is a subset); the census observes, never authorizes
F3  Task 4 T-5: "re-run at the CANDIDATE head (the replacement sha this revision produces)"
+   the diagnostic count is judged on the PRINTED integer of  cat <build log> <tidy log> | grep -c '…'  — never on grep's exit status (1 on zero matches)
Unchanged from rev14  Step 0-quater (i)-(iii) · keep-going build (cmake --build --preset ci -- -k) · one-integer count over concatenated logs · Step 5 three-path proofs ·
    Task 4 T-bullets · T-1/T-2/T-5 · C-1..C-7 · the TEN-path allowlist · the commit message · m-3's C-6 window
```

## W-5 coverage — disclosure-by-class on this face

This revision preserves the frozen selector (`intg-substep2a-plan` / `intg-format-act-plan`) and consumes exactly the eligible row (M rev8 + N + O; `SECOND_/THIRD_CONSUMED_LOCK` manual-assurance-only). W-5 stands EFFECTIVE (registry `16e56c7b…` @ `b30a54c`; notice `035616`; concurrence `033153`). Per the replacement rule, THIS revision's own `--relay-root` measurement is run on the filed carrier and reported UP verbatim with its archive; expected fired set on the carrier: exactly the one O design-lineage red, the W-5-covered class. Per-file OK is never closure.

ACTIONS_GIT_REF: docs-lane writes only — the rev15 artifact (beba597c) and this relay via the engine; the root-mode re-measurement archive and the SITREP to master follow this filing; no product byte, no ref move on the candidate branch; commit path-scoped follows
RELAY_LINT: engine-rendered submission; per-file v2.9.2 lint rides the daemon gate (the draft pre-linted per-file; the four commission-surface lines copied byte-for-byte from the grant); the root-mode re-measurement (the instrument of record) runs on the filed revision and is reported UP verbatim; every upstream route directory and every pair cycle directory re-listed immediately before submit
FINAL_GIT_STATUS_SHORT:
 M docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep2a-20260830.md
 ?? .relays/intg/.engine/drafts/intg.pair-planner/PLAN-SUBSTEP2A-REVISION15-VERBOSE-TIDY-HUNK-BOUNDARY.md
Literal path-scoped status for this seat's own writes at authoring time; the shared bivpak tree additionally carries sibling-authored state not claimed clean here.
