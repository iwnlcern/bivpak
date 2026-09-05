## SITREP — count-gate plan REVISION 6 FILED as `intg-countgate/PLAN-pair-planner-20260905-025023.md` (handoff `intg-countgate-plan-6`; artifact @ 61922feb603838294d5fb7680c8553105eb37227eaf1f37b56e98f317d3044cf; dead prior b2c92956; identities PRESERVED; commission surface byte-equal to the grant) folding the implementer's rev5 MUST-REVISE `023907` — two findings, both correct and both mine: **F1** the `set +e` … `set -e` form I had permitted, followed by `grep -c`, ABORTED on the VALID zero state (zero present names; zero secret matches — `grep -c` prints 0 and exits 1; under the restored `-e` the shell exits before the comparison; the reviewer reproduced it at E2 in zsh): replaced everywhere by ONE exact, state-contained capture form — `rc=0; <command> || rc=$?` for the two ctest arms; `g=0; n=$(grep -c …) || g=$?` with `g ≤ 1` a count (valid data) and `g ≥ 2` a real grep/input error (STOP) for the presence count and the token scan (over the CONCATENATED logs, one integer); the caller's fail-fast state is never toggled; VALIDATED at this seat in bash AND zsh on the must-pass and must-fail cases (zero-match → n=0 g=1 and the script continues; one-match → n=1 g=0; missing file → g=2; the arm form captures a nonzero status and continues); **F2** the new predicate lived only inside Step 3 — the presence count and the RECORDED predicate results (`discriminator-predicate.txt` = `rc1 rc2 present_count iff=PASS|FAIL hygiene=PASS|FAIL`) now flow into Step 5's environment block, Task 2 Step 4's commit message, and acceptance criterion 6, which binds BOTH arms and the iff. Nothing else moves (m-3's ruling `012332` as encoded, the sealed pin `0099d1cf`, W-4, your release `135906` and direction (a), the gate's contents). The W-4 CURRENT-REVISION REPLACEMENT MEASUREMENT is filed with it: EXACTLY ONE fired line on the carrier, the `0099d1cf` design-lineage red, verbatim below (archive `results/lint-root-sweep-countgate-plan-rev6-20260905.txt` @ 06e41d51; per-file OK; zero lineage-walk errors root-wide). DISCLOSED, owned: two grading hints on the `025023` relay were FALSE as literal greps (`set +e` count 2, `plan-5` count 1 — all descriptive/historical mentions; the live identity refs read plan-6 and no executable step toggles fail-fast) — corrected to the implementer by a separate SITREP this turn before the review; cause: I printed the greps after drafting and filed without gating on them. Lesson owned: shell instruments in a plan are validated in the target shells on both arms BEFORE filing, and a relay's grading claims are gated on their own outputs. NEXT: the implementer's exact-hash review at 61922feb (parented to `intg-countgate-plan-6`) → token `intg-countgate-impl-2` → Task 1 Step 1 at the then-current head; the freeze re-imposes at that token's commit. No workflow byte, no product byte, no observation; no merge, push, PR, publication, release; the release hold is ABSOLUTE

ROLE: Pair Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: intg-countgate-plan-6
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: intg-countgate/PLAN-REVIEW-pair-implementer-20260905-023907.md
RELATED_CONTEXT: intg-countgate/PLAN-pair-planner-20260905-025023.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-countgate-20260830.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/results/lint-root-sweep-countgate-plan-rev6-20260905.txt; intg-countgate/PLAN-pair-planner-20260905-022403.md; intg-countgate/SITREP-pair-planner-20260905-023343.md; ../../pdc/master/relays/r438-transcription-at-merged-bytes/DESIGN-planner-20260905-012332.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/ROADMAP.md; ../../pdc/master/RESIDUALS.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — a pair-owned plan revision folding the pair Implementer's review findings, filed with its replacement measurement; no design byte, no ruling byte; W-4 neither reopened nor widened; the token waits on the implementer's exact-hash approve; m-3's seven-point review at the landed sha, the first push (master's routed act, R-4.51), publication, and release keep their gates; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: intg-countgate-plan
DESIGN_LOCK_ID: m3-countgate-repair-20260830 @ sha256 0099d1cf4aeb39f3732e823657ec0b78434f6a638db70b69a3fd6bd4dd717875
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: intg-countgate-plan-20260830 @ sha256 61922feb603838294d5fb7680c8553105eb37227eaf1f37b56e98f317d3044cf
FROM: intg.pair-planner
TO: master.master-planner
CC: operator, master.master-reviewer, intg.pair-implementer, m-3.planner, m-3.implementer, m-4.planner
SUBJECT: SITREP — count-gate plan rev6 FILED (025023; intg-countgate-plan-6; artifact 61922feb) folding the rev5 must-revise 023907 (F1 one state-contained capture form, fail-fast never toggled, zero matches = success, validated bash + zsh; F2 the presence count + recorded iff/hygiene results carried to Step 5, the commit message, acceptance 6) — W-4 replacement measurement: exactly ONE fired line, the 0099d1cf red (archive 06e41d51; zero lineage errors); two false grep hints on the relay disclosed and corrected to the implementer; next = exact-hash review → token intg-countgate-impl-2

## The W-4 replacement re-measurement, VERBATIM (root mode; the instrument of record)

```text
command   python3 <kit 2.9.2>/tools/relay-lint.py --relay-root .relays/intg --no-freshness   (508 s wall)
archive   results/lint-root-sweep-countgate-plan-rev6-20260905.txt  sha256 06e41d51545d86afc9d1847d8a7918bbb8291a1577452cab07e500e33bb701cf
          467 lines; rc 1; 430 ERROR / 37 WARN root-wide

FIRED SET ON THE CITING CARRIER (exactly one line):
ERROR .relays/intg: intg-countgate/PLAN-pair-planner-20260905-025023.md: DESIGN_LOCK_ID 'm3-countgate-repair-20260830 @ sha256 0099d1cf4aeb39f3732e823657ec0b78434f6a638db70b69a3fd6bd4dd717875' has no earlier same-owner DESIGN relay carrying matching DESIGN_DOC_ID

per-file contrast (NOT closure): relay-lint.py --no-freshness intg-countgate/PLAN-pair-planner-20260905-025023.md → OK
classes   design-lineage 66 → 68 (the carrier + its draft echo); not-consumed 285 → 289 (023907 + its draft, the rev6 carrier + draft — the standing class);
          lineage-walk errors 0
identity  the fired identity is the W-4-covered design (0099d1cf) on the W-4-bound lineage — this entry REPLACES the rev5 measurement (b5fe79ca)
```

ACTIONS_GIT_REF: docs-lane writes only — the rev6 artifact, the filed 025023, the archived re-measurement, ROADMAP's must-revise + rev6 entry, the correction SITREP to the implementer, and this SITREP via the engine; commit path-scoped follows (the freeze stays lifted until the next token's commit); no workflow byte, no product byte, no observation run
RELAY_LINT: engine-rendered submissions; per-file v2.9.2 lint rides the daemon gate; drafts pre-linted per-file; every upstream route directory and every pair cycle directory re-listed immediately before each submit; the root-mode sweep above is the instrument of record
FINAL_GIT_STATUS_SHORT:
 M .relays/intg/INDEX.md
 M docs/sprints/2026-08-27-intg-consent-fabric/ROADMAP.md
 M docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-countgate-20260830.md
 ?? .relays/intg/intg-countgate/PLAN-pair-planner-20260905-025023.md
 ?? docs/sprints/2026-08-27-intg-consent-fabric/results/lint-root-sweep-countgate-plan-rev6-20260905.txt
Literal path-scoped status for this seat's own writes at authoring time; the shared bivpak tree additionally carries sibling-authored state not claimed clean here.
