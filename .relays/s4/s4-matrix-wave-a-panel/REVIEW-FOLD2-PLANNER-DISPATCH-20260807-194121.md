## SITREP — second bounded fold routed: two must-fixes from the c52bcca targeted panel (S-1 config-exec class, P-1 O(N^2) capture regression); both clean folds; FOLD_SCOPE is yours

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-matrix-wave-a-panel
PARENT_DISPATCH_ID: s4-matrix-wave-a-panel-disposition
IN_REPLY_TO: .relays/s4/s4-matrix-wave-a-panel/REVIEW-FOLD-IMPLEMENTER-WAVE-A-M1-M14-FILED-20260807-192253.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — second REVIEW-FOLD under the standing discipline authorized by the orchestrator disposition (…-161034); you write FOLD_SCOPE before any edit; merge stays the operator's; the release hold is ABSOLUTE
DESIGN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-05-s4-matrix-arm1-design.md
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/plans/2026-08-06-s4-matrix-arm1-plan.md
FROM: s4-matrix.planner
TO: s4-matrix.implementer
CC: s4.orchestrator-planner, operator
SUBJECT: REVIEW-FOLD #2 — exactly two must-fixes, both clean; fold produces a second replacement head for a targeted check

Your M1–M14 fold VERIFIED at the targeted panel (record:
`docs/sprints/2026-08-04-s4-step4/reviews/2026-08-08-s4-matrix-wave-a-targeted-panel-c52bcca.md`):
14/14 prior must-fixes closed with tests, the M5 rewrite verdict-equivalent, both ruled removals
absent. Clean work. Two findings survived the fold-verify — routed here for a SECOND bounded fold.
Both are clean folds: NO sealed tension, NO design question.

FOLD (exactly two):
- **S-1 (security must-fix, E1) — complete the command-exec config-key class.** Your M1 fix
  neutralized `core.hooksPath`/`credential.helper`/`core.sshCommand`, but the SAME
  hostile-repo-local-config code-execution class also includes `core.fsmonitor` (hook-program
  form runs on index refresh — reached by the pack-side `git status --porcelain=v2` in classify)
  and `core.alternateRefsCommand` (runs during bundle-create/clone object negotiation with an
  alternates file present). Add `core.fsmonitor=` and `core.alternateRefsCommand=` (empty) to the
  injected GIT_CONFIG set and bump `GIT_CONFIG_COUNT` — the same mechanism, two more keys. This is
  neutralizing command-EXECUTING keys (identical class to what you already folded), NOT URL/host
  policing, so it is unambiguously in-scope and folds cleanly. Add a repo-local-hostile-config
  test that a repo carrying `core.fsmonitor=<program>` does not execute it during classify.
- **P-1 (performance must-fix, E2) — remove the O(N^2) capture regression YOUR fold introduced.**
  `subprocess.cpp:129` `bytes_.reserve(bytes_.size() + retained)` runs on every 8 KiB drain chunk;
  on libc++/libstdc++ `reserve(n)` allocates EXACTLY n, defeating vector geometric growth, so
  capture is now O(N^2) (~2048 reallocations / ~17 GiB copied near the 16 MiB cap) where the
  reviewed head at 66250856 was O(N) with a plain `back_inserter`. Delete the per-write reserve
  (rely on `back_inserter` geometric growth) OR reserve ONCE up front to a bounded target. No test
  change strictly required (behavior identical, cost different); a large-output capture case is a
  cheap optional guard.

DO NOT expand beyond these two. The optionals/nits (test-coverage 1/2/3 single-stream truncation /
non-atomic TempDir id / test env-mutation scope guard; security 2 remote-name option-confusion;
perf+idiom 2 the `<initializer_list>` IWYU) are Implementer discretion — fold the cheap ones if you
are already in the file, but they do NOT gate. A row outside the S-1/P-1 surface is a deviation to
the orchestrator BEFORE the edit.

NOT FOLDED here (carried, unchanged):
- The Wave-C integration-window flag (RepoRestoreRow WARNING-vs-ADVISORY exit-class separation) is
  NOT a fold defect — it lands when open.cpp maps exits at the integration window; leave it.
- The zero-ref `capture_mode` cell stays HELD pending the orchestrator ruling — do not bless a
  value.

Branch mechanics: fold on the stacked topology (S-1 lands on the T2 git-wrapper branch, P-1 on the
T1 subprocess branch; restack T2→T3→T4). Result is a second replacement head. File your
`PHASE: REVIEW-FOLD` report with the FOLD_SCOPE block, `FOLD_SCOPE_RESULT: all-in`, and the new
head; I run a TARGETED CHECK sized to the ~2-file delta (lead verify + the security and
performance lenses only — not a full re-panel, per the after-fold-ins rule), and on green the
candidate is panel-clean at its final head.

ACTIONS_GIT_REF: none — no product/test edit by this seat; this routing relay + its INDEX row are the only writes, docs-lane.
FINAL_GIT_STATUS_SHORT: none — clean tree; fresh at 20260807-194121, this relay + INDEX row the only delta at commit time.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-wave-a-panel/REVIEW-FOLD2-PLANNER-DISPATCH-20260807-194121.md` → TO `s4-matrix.implementer`
