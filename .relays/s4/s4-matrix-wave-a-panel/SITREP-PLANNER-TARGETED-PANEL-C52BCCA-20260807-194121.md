## SITREP — targeted fold-verification panel COMPLETE at `c52bcca`: 2 approve / 2 must-fix; all 14 prior fixes closed; verdict REVIEW-FOLD required (a SECOND bounded fold of exactly two narrow items); record durable

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-matrix-wave-a-panel
PARENT_DISPATCH_ID: s4-matrix-wave-a-panel-disposition
IN_REPLY_TO: .relays/s4/s4-matrix-wave-a-panel/REVIEW-FOLD-IMPLEMENTER-WAVE-A-M1-M14-FILED-20260807-192253.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no at this relay — the second fold is the pair's under the standing REVIEW-FOLD discipline; both items are clean folds (no sealed tension); merge conditions 3/4 stay master/operator; the release hold is ABSOLUTE
DESIGN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-05-s4-matrix-arm1-design.md
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/plans/2026-08-06-s4-matrix-arm1-plan.md
FROM: s4-matrix.planner
TO: s4.orchestrator-planner
CC: operator, s4.orchestrator-reviewer, s4-matrix.implementer
SUBJECT: SITREP — the c52bcca fold verified; 14/14 prior must-fixes closed; 2 narrow items survive => one more bounded fold + a targeted check, then the candidate is panel-clean

Record of record (durable):
`docs/sprints/2026-08-04-s4-step4/reviews/2026-08-08-s4-matrix-wave-a-targeted-panel-c52bcca.md`
— a TARGETED panel sized to the fold delta `66250856..c52bcca` (25 files) per your cumulative-diff
rule, NOT a full re-run. Four cold SHA-bound lenses, delta-scoped (perf+idiom merged — the
down-size and rationale recorded in PANEL_CHOSEN/DEFAULT_ROLES_CHANGED/WHY_THIS_PANEL);
both pair seats excluded; I ran non-lens lead, no findings of my own, no re-grading.
Spawn reconciliation clean: 4 spawns / 0 stalls / 4 finding-sets.

Lead pre-panel reconciliation (E1 at c52bcca, before spawning): the 25-file delta is entirely
inside the Implementer's FOLD_SCOPE all-in; both Step-3 fences LIVE; no scan/pack/open/manifest
source touched; every ruled item verified at the bytes (no allowlist added; hygiene
GIT_PROTOCOL_FROM_USER pinned; recovery fetch removed; reset gone; git_exec + git_budget_expired
present; test_probe single-compile).

Per-lens verdicts (bare):
correctness approve
test-coverage approve
security must-fix
performance+idiomaticity must-fix

Result: **14/14 prior must-fixes CLOSED with tests** — correctness verified the M5 eligibility
ALGORITHM rewrite is VERDICT-EQUIVALENT to the sealed method (the real regression risk of a
rewrite), M6/M7/M8/M14 closed; test-coverage confirmed every fix has a regression-falsifying
test incl. the previously-untested promisor no-lazy-fetch property (now traced at the
production Git::run chokepoint); security confirmed M2/M3 closed + both ruled removals absent;
perf+idiom confirmed M4/M5/M11/M12/M13 closed (single penumbra snapshot confirmed).

TWO findings survive — both NARROW, CHEAP, and CLEAN FOLDS (no sealed tension, unlike the
first cycle's allowlist):
- **S-1 (security, must-fix, E1):** M1 neutralized 3 command-exec config keys but the same
  hostile-repo-local-config code-execution CLASS also has `core.fsmonitor` (runs on index
  refresh via pack-side `git status`) and `core.alternateRefsCommand` (runs during
  bundle/clone negotiation). Add both to the injected GIT_CONFIG deny-list. This is neutralizing
  command-EXECUTING keys — the SAME class already folded — NOT URL policing, so it folds cleanly.
  No live path at c52bcca (engine unwired) but MUST close before Wave-C wiring.
- **P-1 (performance, must-fix, E2):** a cheap fold-in introduced an O(N^2) capture regression —
  a per-8KiB-chunk `reserve()` (subprocess.cpp:129) defeats vector geometric growth on
  libc++/libstdc++ (~17 GiB copied near the 16 MiB cap) where the reviewed head was O(N). Delete
  the per-write reserve. Pure regression fix.

Both are localized (git.cpp env-injection set; one line in subprocess.cpp). I am opening a
SECOND bounded fold at the pair for exactly these two (routing relay to the Implementer alongside
this); its replacement head gets a TARGETED CHECK sized to its ~2-file delta (lead verify + the
two owning lenses), not a full re-panel, per the after-fold-ins rule. On that check green, the
candidate is panel-clean (condition 1) at its final head.

Carried, not fold defects:
- Wave-C INTEGRATION-window flag (correctness Q1): RepoRestoreRow does not structurally separate
  WARNING-class (exit 2) from ADVISORY-class (exit 0) rows; open.cpp's future exit-mapping must
  map an Ok-row-with-outcome=failed+divergence to exit 2 (D5.3), not exit 4 (D5.2), without
  string-matching. Recorded for the integration window.
- The zero-ref `capture_mode` inexpressible cell (my SITREP …-162054) still awaits your ruling;
  the fold left the value unblessed as directed — unchanged by this panel.

Optionals/nits are Implementer discretion (verbatim in the record). Merge stays the operator's;
B/C/D stay F-fenced; the stack (#16/#17/#19/#20) stays open at the replacement head.

ACTIONS_GIT_REF: docs lane only — the targeted-panel record + this relay + its INDEX row, committed on main with explicit paths (SHA in the commit record); no product edit; the stack is untouched by this filing.
FINAL_GIT_STATUS_SHORT:
none — clean tree
Fresh at 20260807-194121 before this relay + INDEX write; the record, this relay, and the INDEX row are the working-tree delta at commit time and are named above.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-wave-a-panel/SITREP-PLANNER-TARGETED-PANEL-C52BCCA-20260807-194121.md` → TO `s4.orchestrator-planner`
