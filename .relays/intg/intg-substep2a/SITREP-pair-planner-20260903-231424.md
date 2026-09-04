## SITREP — 2a plan REVISION 15 FILED as `intg-substep2a/PLAN-pair-planner-20260903-230341.md` (artifact @ beba597c20d43441f6901f4930e4e4141bd866ecdc27c3f8cec3f403dcb0f265; dead prior 84061879; identity PRESERVED; commission surface byte-equal to the grant) folding the implementer's rev14 MUST-REVISE `225905` — three findings, all correct at the text and all mine: **F1** the tidy coverage receipt rev14 required was UNOBSERVABLE as commanded — ordinary CTest hides a passing test's stdout, and the rev13 log (tidy row PASSED 1/1, `tidy_rc=0`, NO `clang-tidy coverage:` line) is the counterexample the reviewer produced — Step 4b now runs `ctest --preset ci -R '^safety-tidy-analyzer$' -V 2>&1 | tee <tidy log>`, `tidy_rc` through the pipe, and requires EXACTLY ONE `clang-tidy coverage: <N> results == <N> sources` line with equal N ≥ 1, rejecting `COVERAGE FAILURE:`, the verbose form carried everywhere the receipt is promised (headline, Step 4b, T-3, acceptance 12); **F2** rev14's fold rule ("fold every enumerated red within the three paths; a fourth path = STOP") had WEAKENED the exact-hunk authority to a path-only one — RESTORED at Step 4b and Step 0-quater (iv): the ONLY bytes that may exist vs `retained-task3b-b09e192` are the SIX AUTHORIZED HUNKS (T-1's header line; the four T-4 sites; the `dot{}` line); an enumerated red needing ANY OTHER byte is a STOP through me even inside the three checkpoint files, a fourth path a subset of that rule; the keep-going census is an OBSERVATION mechanism, not repair authority; **F3** Task 4's T-5 bullet named the dead rev13 head — now the CANDIDATE head; also folded: the diagnostic count is judged on the PRINTED integer, never `grep -c`'s exit status (1 on zero matches by design). The W-5 CURRENT-REVISION REPLACEMENT MEASUREMENT is filed with it: EXACTLY ONE fired line on the carrier, the O design-lineage red, verbatim below (archive `results/lint-root-sweep-2a-rev15-verbose-tidy-20260903.txt` @ 2a10cad6; zero lineage-walk errors root-wide). Two lessons owned at this seat, both instrument-shaped: a plan that requires a receipt from a tool's stdout must command the INVOCATION MODE that surfaces it (I required a line that ctest's default mode swallows), and an observation mechanism must never be phrased as repair authority. Nothing else moves: Step 0-quater's `dot{}` NSDMI, the accepted `find_field_unordered` spelling (m-1 objects at V-FA if at all), the keep-going build, the three-path Step 5 proofs stand as at rev14. NEXT: the implementer's exact-hash review at beba597c → token `intg-substep2a-impl-5`. `b09e192` FROZEN with the held two-file repair on it (fd12d52b… / f7a89c8c…, re-verified); the count-gate token stays HELD; no product byte at this seat; no merge, push, PR, publication, release; the release hold is ABSOLUTE

ROLE: Pair Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: intg-substep2a-plan
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: intg-substep2a/PLAN-REVIEW-pair-implementer-20260903-225905.md
RELATED_CONTEXT: intg-substep2a/PLAN-pair-planner-20260903-230341.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep2a-20260830.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/results/lint-root-sweep-2a-rev15-verbose-tidy-20260903.txt; intg-substep2a/PLAN-pair-planner-20260903-223053.md; intg-substep2a/SITREP-pair-planner-20260903-224021.md; ../../pdc/master/relays/intg-substep2a-format-act/DESIGN-planner-20260903-183510.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/ROADMAP.md; ../../pdc/master/RESIDUALS.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — a pair-owned plan revision folding the pair Implementer's review findings, filed with its replacement measurement; no owner fence touched; W-5 neither reopened nor widened; the token waits on the implementer's exact-hash approve; m-1's V-FA and m-3's C-6 reviews, the merge packet, the count-gate observations, push, publication, deployment, and release keep their gates; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: intg-format-act-plan
DESIGN_LOCK_ID: m1-addendum-O-63c46631-lock-20260901
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: intg-substep2a-plan-20260830 @ sha256 beba597c20d43441f6901f4930e4e4141bd866ecdc27c3f8cec3f403dcb0f265
FROM: intg.pair-planner
TO: master.master-planner
CC: operator, master.master-reviewer, intg.pair-implementer, m-1.planner, m-1.implementer, m-3.planner, m-3.implementer
SUBJECT: SITREP — 2a plan rev15 FILED (230341; artifact beba597c; identity preserved) folding the rev14 must-revise 225905 (F1 ctest -V so the coverage receipt is observable; F2 the STOP boundary restored to the six authorized hunks, the census observes and never authorizes; F3 T-5 at the candidate head) — W-5 replacement measurement: exactly ONE fired line, the O red (archive 2a10cad6; zero lineage errors); next = implementer's exact-hash review → token intg-substep2a-impl-5; b09e192 frozen with the held repair; count-gate token held

## The W-5 replacement re-measurement, VERBATIM (root mode; the instrument of record)

```text
command   python3 <kit 2.9.2>/tools/relay-lint.py --relay-root .relays/intg --no-freshness   (566 s wall)
archive   results/lint-root-sweep-2a-rev15-verbose-tidy-20260903.txt  sha256 2a10cad6e9e12ed2f0841d961a5a8d3295fd64b2dcc5727b2e08c08597636d28
          421 lines; rc 1; 387 ERROR / 34 WARN root-wide

FIRED SET ON THE CITING CARRIER (exactly one line):
ERROR .relays/intg: intg-substep2a/PLAN-pair-planner-20260903-230341.md: DESIGN_LOCK_ID 'm1-addendum-O-63c46631-lock-20260901' has no earlier same-owner DESIGN relay carrying matching DESIGN_DOC_ID

per-file contrast (NOT closure): relay-lint.py --no-freshness intg-substep2a/PLAN-pair-planner-20260903-230341.md → OK
classes   design-lineage 60 → 62 (the carrier + its draft echo); not-consumed 250 → 254 (225905 + its draft, the rev15 carrier + its draft — the
          standing class); lineage-walk errors 0
identity  the fired identity is the W-5-covered design (O) on the W-5-bound lineage — this entry REPLACES the rev14 measurement (62b995b4)
```

ACTIONS_GIT_REF: docs-lane writes only — the rev15 artifact, the filed 230341, the archived re-measurement, ROADMAP's must-revise + rev15 entry, and this SITREP via the engine; commit path-scoped follows; no product byte, no ref move on the candidate branch, no observation run
RELAY_LINT: engine-rendered submissions; per-file v2.9.2 lint rides the daemon gate; drafts pre-linted per-file; every upstream route directory and every pair cycle directory re-listed immediately before each submit; the root-mode sweep above is the instrument of record
FINAL_GIT_STATUS_SHORT:
 M .relays/intg/INDEX.md
 M docs/sprints/2026-08-27-intg-consent-fabric/ROADMAP.md
 M docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep2a-20260830.md
 ?? .relays/intg/.engine/drafts/intg.pair-planner/PLAN-SUBSTEP2A-REVISION15-VERBOSE-TIDY-HUNK-BOUNDARY.md
 ?? .relays/intg/.engine/drafts/intg.pair-planner/SITREP-2A-REV15-FILED-W5-REMEASURED.md
 ?? .relays/intg/intg-substep2a/PLAN-pair-planner-20260903-230341.md
 ?? docs/sprints/2026-08-27-intg-consent-fabric/results/lint-root-sweep-2a-rev15-verbose-tidy-20260903.txt
Literal path-scoped status for this seat's own writes at authoring time; the shared bivpak tree additionally carries sibling-authored state not claimed clean here.
