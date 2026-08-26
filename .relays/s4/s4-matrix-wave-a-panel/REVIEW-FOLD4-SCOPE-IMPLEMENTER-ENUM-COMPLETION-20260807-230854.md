## REVIEW-FOLD4 SCOPE — include/worktree enumeration completion resolves all-IN before the first product or test edit

ROLE: Implementer
PHASE: REVIEW-FOLD
AUTHORITY: fold-in-only
DISPATCH_ID: s4-matrix-wave-a-panel
PARENT_DISPATCH_ID: s4-matrix-wave-a-panel-disposition
IN_REPLY_TO: .relays/s4/s4-matrix-wave-a-panel/REVIEW-FOLD4-PLANNER-DISPATCH-ENUM-COMPLETION-20260807-230021.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — this completes the already-directed neutralize-found enumeration; merge remains operator-owned and the release hold is ABSOLUTE
DESIGN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-05-s4-matrix-arm1-design.md
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/plans/2026-08-06-s4-matrix-arm1-plan.md
FROM: s4-matrix.implementer
TO: s4-matrix.planner
CC: s4.orchestrator-planner, operator
SUBJECT: FOLD_SCOPE ALL-IN — exactly the include-following local pass, worktree-scope pass, disabled-worktree empty-set handling, three direct regressions, and governed filing surfaces

FOLD_SCOPE:
- src/core/repo/git_exec.cpp -> in
- tests/test_repo_engine.cpp -> in
- .relays/s4/s4-matrix-wave-a-panel/** -> in
- .relays/s4/INDEX.md -> in
FOLD_SCOPE_RESULT: all-in

### Finding map

The T4 enumeration helper will union two config reads over the unchanged driver-family
pattern: `--local --includes` and `--worktree --includes`. The worktree pass will map
only the ordinary disabled-extension result to an empty set: exit 1 on a single-worktree
repository, or exit 128 carrying Git's stable C-locale `--worktree cannot be used with
multiple working trees unless ... worktreeConfig is enabled` diagnostic on a linked
worktree. Other nonzero results remain typed failures. Sorting, deduplication, empty
override composition, classification/capture carry, and the five static keys are
unchanged.

`tests/test_repo_engine.cpp` will add real RED/GREEN cases for an included
`filter.evil.clean`, a `.git/config.worktree` `filter.evil.clean`, and an ordinary linked
worktree with `extensions.worktreeConfig` disabled. The first two must create their
markers before the fold and leave them absent after it; the negative control must fail
classification before the special case and classify green after it. The direct
`.git/config` case remains unchanged.

No Git wrapper override API, driver family, global config scope, fail-closed refusal,
eligibility/restore/schema/CLI/harness surface, Wave-C exit mapping, zero-ref
`capture_mode` decision, new PR, merge, or release is in this fold.

ACTIONS_GIT_REF: no product/test edit or branch publication preceded this artifact; cumulative T4 is clean at `5be90ed60d5649060417c79909be277fddc1955d`; the existing engine baseline passed 292 assertions in 33 cases; this scope relay and its append-only INDEX row are the only pre-fold writes
FINAL_GIT_STATUS_SHORT: none — clean cumulative T4 tree at `5be90ed60d5649060417c79909be277fddc1955d` before this scope relay and INDEX append

Fresh at 20260807-230854 before the first REVIEW-FOLD4 product or test edit.
