## SITREP — completion fold routed: the neutralize-found enumeration under-collects (include + worktree scopes proven-executable, E2); add `--includes` + a `--worktree --includes` pass; this CLOSES the class per the lens's exhaustive sweep

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-matrix-wave-a-panel
PARENT_DISPATCH_ID: s4-matrix-wave-a-panel-disposition
IN_REPLY_TO: .relays/s4/s4-matrix-wave-a-panel/REVIEW-FOLD3-IMPLEMENTER-NEUTRALIZE-FOUND-FILED-20260807-224258.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — this COMPLETES the orchestrator-directed neutralize-found fix (not unbuildable, not a new design decision); you write FOLD_SCOPE before any edit; merge stays the operator's; the release hold is ABSOLUTE
DESIGN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-05-s4-matrix-arm1-design.md
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/plans/2026-08-06-s4-matrix-arm1-plan.md
FROM: s4-matrix.planner
TO: s4-matrix.implementer
CC: s4.orchestrator-planner, operator
SUBJECT: REVIEW-FOLD #4 — complete the neutralize-found enumeration (include + worktree scopes); exactly one item; the class closes with this

Check #4 (security owning lens, E2 live repros; record
`docs/sprints/2026-08-04-s4-step4/reviews/2026-08-08-s4-matrix-wave-a-check4-a3c5454.md`)
returned BLOCK: neutralize-found closes the DIRECT `.git/config` filter driver (your
RED/GREEN is real and non-vacuous, the override mechanism + `--local` global-exclusion +
enumeration-read safety all correct), but the enumeration MISSES two config-delivery
mechanisms for the SAME `filter.*.clean` family, both of which `git status` executes
during classify:

1. **include.path / includeIf:** `git config --local --get-regexp` defaults `--includes`
   OFF for a specific scope, so a driver in a file pulled via `[include] path=…` in
   `.git/config` is NOT surfaced (rc=1) — yet `git status` follows includes and RUNS it.
2. **extensions.worktreeConfig:** a driver in `.git/config.worktree` is NOT surfaced by
   `--local` — yet `git status` reads worktree config and RUNS it.

FOLD (exactly one item — COMPLETE the enumeration; the override mechanism is untouched):
- In `git_exec.cpp repo_local_command_config_keys`, replace the single pass with the UNION
  of two enumerations over the same driver-family pattern:
  - `git config --local --includes --null --name-only --get-regexp <pattern>` (adds
    include-following to the existing local scope);
  - `git config --worktree --includes --null --name-only --get-regexp <pattern>` (adds the
    worktree scope).
  Union + sort + dedup the found keys; inject the same empty `GIT_CONFIG_*` overrides for
  each (the override already outranks every scope — ONLY the enumeration changes).
- **Handle the worktree-not-enabled case as EMPTY-SET, not failure (critical):**
  `git config --worktree` errors when `extensions.worktreeConfig` is disabled — the NORMAL
  case for almost every repo — so that specific nonzero exit MUST map to an empty result,
  exactly like the exit-1 empty-set path, or classify breaks on every ordinary repo. Do not
  fold it into the generic typed-failure branch. Verify the exact exit/stderr git emits when
  worktree config is off and special-case it precisely (an ordinary repo with no worktree
  config must classify GREEN).
- **Global stays excluded:** neither pass adds `--global`; the lens verified
  `--local --includes` does not leak the user's global `filter.lfs.clean` — git-lfs
  preserved. Keep it that way.
- **Tests (RED/GREEN, both newly-proven delivery paths):**
  (a) a hostile repo with `[include] path=evil-include` in `.git/config` and the driver in
  the included file + `.gitattributes: * filter=evil`; assert the marker is ABSENT with the
  fix and CREATED without it;
  (b) a hostile repo with `core.repositoryformatversion=1` + `extensions.worktreeConfig=true`
  and the driver in `.git/config.worktree`; same RED/GREEN.
  Keep your existing direct-`.git/config` case. Add one ordinary-repo (worktree config OFF)
  case asserting classify still GREEN (guards the not-enabled special-case).

DO NOT expand beyond completing the enumeration. The lens's EXHAUSTIVE sweep confirms the
class CLOSES with this: every other command-exec key (`diff.external`, `core.gitProxy`,
`protocol.*.command`, `url.*.insteadOf`, `remote.*.uploadpack`, pager/editor, aliases,
`safe.directory`) is confirmed NOT reachable by the commands classify/capture issue, and the
static-injected keys beat all scopes. No new family to add. A row outside the
classify/git-wrapper enumeration surface is a deviation to the orchestrator BEFORE the edit.
NOT folded, carried unchanged: the Wave-C exit-mapping flag; the zero-ref `capture_mode` cell.

Branch mechanics: lands on the T2/T4 enumeration surface; restack; produces a fifth
replacement head. File your `PHASE: REVIEW-FOLD` report with FOLD_SCOPE,
`FOLD_SCOPE_RESULT: all-in`, and the new head; I run a FIFTH targeted check — lead byte-verify
+ the security owning lens over the delta — its record stating the cumulative window from
`66250856` and incorporating the c52bcca + d11c49c + a3c5454 records by reference. On green,
condition 1 is met at the final head.

ACTIONS_GIT_REF: none — no product/test edit by this seat; this routing relay + its INDEX row are the only writes, docs-lane.
FINAL_GIT_STATUS_SHORT: none — clean tree; fresh at 20260807-230021, this relay + INDEX row the only delta at commit time.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-wave-a-panel/REVIEW-FOLD4-PLANNER-DISPATCH-ENUM-COMPLETION-20260807-230021.md` → TO `s4-matrix.implementer`
