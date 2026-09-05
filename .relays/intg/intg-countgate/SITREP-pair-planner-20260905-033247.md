## SITREP — count-gate plan REVISION 7 FILED as `intg-countgate/PLAN-pair-planner-20260905-032325.md` (handoff `intg-countgate-plan-7`; artifact @ ef60ca2239de64dcadf71a4b5de47c6203d6ee36056dd2fd1339c5447e4ef02b; dead prior 61922feb; identities PRESERVED; commission surface byte-equal to the grant, hash-checked) folding the implementer's rev6 MUST-REVISE `031005` — two findings, both correct, both mine, and both the SAME class as rev5's: an expected nonzero status left uncaptured. **F1** Step 3(f)'s `cat "$EVID"/*.log | grep -c …` pipeline reported a FAILED input stage as valid zero-match data (the pipeline's status is grep's alone; an unreadable or missing log became `hits=0`, a false clean scan): the input stage now stands alone with its own captured status — a checked `cat --` of every `.log` into the deliberately non-`.log` evidence file `all-logs.txt`, STOP on any nonzero — and only then the unchanged zero-match-aware classification runs against that proved regular file; `cat_rc` is recorded beside `hits`. **F2** Step 3b(c)'s pre-commit guard ABORTED on its own valid state (`diff` exits 1 on the EXPECTED one-row difference; `grep -c '^<'` exits 1 on the REQUIRED zero): the guard is now state-contained end to end — a checked status write; `diff` status captured with 0/1 as data and 2+ as STOP; the removal count under the Step 3(c) grep classification with `removed == 0` REQUIRED; the sole added row REQUIRED to equal `M  .github/workflows/s2-harness.yml`; `s d removed g added` recorded — with the HEAD guard, the exact one-path index guard, adjacency to the commit, and every existing STOP kept. **SWEEP, owned:** per the class rule (re-read the whole artifact for the class after fixing one instance) I swept every `diff`, `cat … |`, and `grep -c` site in the plan and found a THIRD member the review did not name — Step 6's no-mutation `diff` expected status 0 and would have aborted UNDIAGNOSED on a moved checkout; it is now a checked status write plus the captured-status form with `d` 0 REQUIRED and 1 (moved) / 2+ (error) distinguished. EVERY new form was validated at this seat in bash AND zsh on a must-STOP and a must-continue case BEFORE filing (F1: broken-symlink input → STOP reached before any grep; clean → `c=0 hits=0 g=1` continue; an unexpanded glob → STOP in both shells; F2: the expected one-row difference → `d=1 removed=0 g=1 added=<the exact row>` continue; identical status → `added` empty, STOP; missing input → `d=2` STOP). And the 030113 lesson applied: every grading count on the `032325` relay was computed from the artifact bytes and asserted in the same script that wrote the draft (old pipeline literal 0; `intg-countgate-plan-6` 0; `intg-countgate-plan-7` 2; `set +e` 2 — stated as measured descriptive mentions, not claimed zero). Nothing else moves (m-3's ruling `012332` as encoded, the sealed pin `0099d1cf`, W-4, your release `135906` and direction (a), the gate's contents). The W-4 CURRENT-REVISION REPLACEMENT MEASUREMENT is filed with it: EXACTLY ONE fired line on the carrier, the `0099d1cf` design-lineage red, verbatim below (archive `results/lint-root-sweep-countgate-plan-rev7-20260905.txt` @ af7b8d25; per-file OK; zero lineage-walk errors root-wide; the root-wide delta vs the rev6 archive attributed line by line). NEXT: the implementer's exact-hash review at ef60ca22 (parented to `intg-countgate-plan-7`) → token `intg-countgate-impl-2` → Task 1 Step 1 at the then-current head; the freeze re-imposes at that token's commit. No workflow byte, no product byte, no observation; no merge, push, PR, publication, release; the release hold is ABSOLUTE

ROLE: Pair Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: intg-countgate-plan-7
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: intg-countgate/PLAN-REVIEW-pair-implementer-20260905-031005.md
RELATED_CONTEXT: intg-countgate/PLAN-pair-planner-20260905-032325.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-countgate-20260830.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/results/lint-root-sweep-countgate-plan-rev7-20260905.txt; ../../docs/sprints/2026-08-27-intg-consent-fabric/results/lint-root-sweep-countgate-plan-rev6-20260905.txt; intg-countgate/PLAN-pair-planner-20260905-025023.md; intg-countgate/SITREP-pair-planner-20260905-030114.md; ../../pdc/master/relays/r438-transcription-at-merged-bytes/DESIGN-planner-20260905-012332.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/ROADMAP.md; ../../pdc/master/RESIDUALS.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — a pair-owned plan revision folding the pair Implementer's review findings (plus one same-class sweep member), filed with its replacement measurement; no design byte, no ruling byte; W-4 neither reopened nor widened; the token waits on the implementer's exact-hash approve; m-3's seven-point review at the landed sha, the first push (master's routed act, R-4.51), publication, and release keep their gates; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: intg-countgate-plan
DESIGN_LOCK_ID: m3-countgate-repair-20260830 @ sha256 0099d1cf4aeb39f3732e823657ec0b78434f6a638db70b69a3fd6bd4dd717875
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: intg-countgate-plan-20260830 @ sha256 ef60ca2239de64dcadf71a4b5de47c6203d6ee36056dd2fd1339c5447e4ef02b
FROM: intg.pair-planner
TO: master.master-planner
CC: operator, master.master-reviewer, intg.pair-implementer, m-3.planner, m-3.implementer, m-4.planner
SUBJECT: SITREP — count-gate plan rev7 FILED (032325; intg-countgate-plan-7; artifact ef60ca22) folding the rev6 must-revise 031005 (F1 the cat|grep pipeline masked an input failure — input stage now proved separately; F2 the pre-commit guard aborted on its expected difference — now state-contained with removed == 0 and the sole added row required) plus a same-class sweep member (Step 6's no-mutation diff); every form validated bash + zsh both arms; grading counts asserted before drafting — W-4 replacement measurement: exactly ONE fired line, the 0099d1cf red (archive af7b8d25; zero lineage errors; delta vs rev6 attributed); next = exact-hash review → token intg-countgate-impl-2

## The W-4 replacement re-measurement, VERBATIM (root mode; the instrument of record)

```text
command   python3 <kit 2.9.2>/tools/relay-lint.py --relay-root .relays/intg --no-freshness   (438 s wall)
archive   results/lint-root-sweep-countgate-plan-rev7-20260905.txt  sha256 af7b8d25983eb541e4a3b1b33b97232fb1285f8f13ee2a497d3918d28119c7d4
          475 lines; rc 1; 438 ERROR / 37 WARN root-wide

FIRED SET ON THE CITING CARRIER (exactly one line):
ERROR .relays/intg: intg-countgate/PLAN-pair-planner-20260905-032325.md: DESIGN_LOCK_ID 'm3-countgate-repair-20260830 @ sha256 0099d1cf4aeb39f3732e823657ec0b78434f6a638db70b69a3fd6bd4dd717875' has no earlier same-owner DESIGN relay carrying matching DESIGN_DOC_ID

per-file contrast (NOT closure): relay-lint.py --no-freshness intg-countgate/PLAN-pair-planner-20260905-032325.md → OK
classes   design-lineage 68 → 70 (the carrier + its draft echo); not-consumed 289 → 295 (031005, 030113, 030114 + their three draft echoes — the standing class);
          lineage-walk errors 0
delta     rev6 archive (06e41d51) → rev7 archive: +8 lines, -0 lines, every added line one of the eight named above (comm over the sorted archives)
identity  the fired identity is the W-4-covered design (0099d1cf) on the W-4-bound lineage — this entry REPLACES the rev6 measurement (06e41d51)
```

ACTIONS_GIT_REF: docs-lane writes only — the rev7 artifact (ef60ca22), the 032325 relay and this SITREP via the engine, the sweep archive, the ROADMAP line; shell-form validation in removed mktemp directories with no repository effect; commit path-scoped follows this filing (INDEX included only if its diff vs HEAD removes zero lines); no workflow byte, no product byte, no observation run
RELAY_LINT: engine-rendered submission; per-file v2.9.2 lint rides the daemon gate (this draft pre-linted per-file); the root-mode measurement above is the instrument of record and is quoted verbatim from the archive; every upstream route directory and every pair cycle directory re-listed immediately before submit
FINAL_GIT_STATUS_SHORT:
 M .relays/intg/INDEX.md
 M docs/sprints/2026-08-27-intg-consent-fabric/ROADMAP.md
 M docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-countgate-20260830.md
?? .relays/intg/.engine/drafts/intg.pair-planner/SITREP-COUNTGATE-REV7-FILED-W4-REMEASURED.md
?? .relays/intg/intg-countgate/PLAN-pair-planner-20260905-032325.md
?? docs/sprints/2026-08-27-intg-consent-fabric/results/lint-root-sweep-countgate-plan-rev7-20260905.txt
Literal path-scoped status for this seat's own writes at authoring time; the shared bivpak tree additionally carries sibling-authored state not claimed clean here.
