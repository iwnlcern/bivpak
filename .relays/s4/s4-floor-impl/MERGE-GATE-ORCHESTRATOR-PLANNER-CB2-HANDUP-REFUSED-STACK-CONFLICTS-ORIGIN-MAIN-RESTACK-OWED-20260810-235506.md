## MERGE-GATE (condition-3 prep — REFUSED, no hand-up) — I cannot carry C/B2 to master's condition-3: **the stack CONFLICTS with its actual merge target `origin/main` (`38a4702`, post-R-4.8).** Verified at my seat with the authoritative form: `git merge-tree --write-tree --name-only origin/main b8083be` → **exit 1**, CONFLICT (content) in `src/core/open/sessions.cpp`, `tests/test_adapter_codex_install.cpp`, `tests/test_sessions.cpp`; `... origin/main 3762f37` → **exit 1**, CONFLICT in `sessions.cpp` + `test_adapter_claude_install.cpp` + `test_adapter_codex_install.cpp` + `test_pack.cpp` + `test_sessions.cpp`. **Root cause:** LOCAL main (`dc12dcd`) does NOT contain R-4.8 (`git merge-base --is-ancestor 38a4702 main` = NO), so your "clean at every hop including onto LOCAL main" test used a STALE pre-R-4.8 target — but R-4.8 landed on `origin/main` and modified EXACTLY the conflicting files (`sessions.cpp` 61 lines, the four test files 410–527 lines each), which the fold also touched. This is the re-stack-provenance class: the merge-clean check must be onto the CURRENT remote merge target, not the local/immediate parent. PRs #22/#23 base = `main` = `origin/main`. No hand-up on a stack that will not merge. The release hold is ABSOLUTE.

ROLE: Orchestrator Planner
PHASE: MERGE-GATE
AUTHORITY: merge-gated
DISPATCH_ID: s4-floor-cb2-handup-refused-restack
PARENT_DISPATCH_ID: s4-floor-cb2-merge-gate
IN_REPLY_TO: .relays/s4/s4-floor-impl/SITREP-PLANNER-CB2-PAIRED-HANDUP-COMBINED-RECHECK-PASS-20260810-232655.md
RUN_ID: s4
TASK_ID: B2
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — a condition-3-prep refusal at my seat; nothing goes to master or the operator until the stack merges clean into the current `origin/main` and re-verifies. The release hold is ABSOLUTE.
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
FROM: s4.orchestrator-planner
TO: s4-floor.planner
CC: operator, s4.orchestrator-reviewer, s4-floor.implementer, master.orchestrator-planner, m-2.planner
SUBJECT: MERGE-GATE — hand-up REFUSED: C/B2 conflict with origin/main (post-R-4.8) on sessions.cpp + tests; re-stack onto 38a4702, resolve, redo the carry adjudication + re-verify, fresh hand-up

## 1. The block, reproducible at any seat

```text
origin/main = 38a4702  (R-4.8 landed here; it modified sessions.cpp + 4 test files)
local  main = dc12dcd  (does NOT contain R-4.8: git merge-base --is-ancestor 38a4702 main → exit 1)

git merge-tree --write-tree --name-only origin/main b8083be  → exit 1
  CONFLICT (content): src/core/open/sessions.cpp
  CONFLICT (content): tests/test_adapter_codex_install.cpp
  CONFLICT (content): tests/test_sessions.cpp
git merge-tree --write-tree --name-only origin/main 3762f37  → exit 1
  CONFLICT (content): src/core/open/sessions.cpp · tests/test_adapter_claude_install.cpp
                      tests/test_adapter_codex_install.cpp · tests/test_pack.cpp · tests/test_sessions.cpp
```

Your combined re-check is sound on its own terms and I verified much of it (SHAs, B2 one commit atop exact C,
blast radius **27** via the corrected `origin/main..3762f37^`, the acceptance-instrument genuineness). But the
merge-clean leg tested the WRONG target: `origin/main` advanced past your base `6047ab03` when R-4.8 landed
(`38a4702`), and R-4.8's edits to `sessions.cpp` and the four test files collide with the fold's edits to the
same files. You even used `origin/main` for the blast radius but `local main` for the merge check — that
inconsistency is exactly the gap.

## 2. What is owed — re-stack onto the current target, then per-file end-state re-adjudication

This is the re-stack-provenance discipline (a rebuilt/landed predecessor supersedes the base; verify the WHOLE
stack into the CURRENT remote main, per-file end-state hashes):
1. **Re-stack C `b8083be` / B2 `3762f37` onto post-R-4.8 `origin/main` (`38a4702`)** — rebase C then B2, or
   merge origin/main in; resolve the conflicts in `sessions.cpp` and the four test files (R-4.8's changes vs
   the fold's — both are yours to reconcile: R-4.8's session/manifest work AND the fold's option-(a) removal).
2. **Re-verify the WHOLE stack merges CLEAN into the current `origin/main`** (`git merge-tree --write-tree`
   exit 0) before anything else.
3. **REDO the carry adjudication against the re-stacked end-state.** The conflict-resolved files change bytes,
   so the combined re-check's verdict on `sessions.cpp`, `test_adapter_codex_install.cpp`, `test_sessions.cpp`
   (+ B2's `test_adapter_claude_install.cpp`, `test_pack.cpp`) does NOT carry — those need FRESH review at the
   re-stacked head; files whose end-state bytes still match the current combined head carry. The 12/5 count
   will change.
4. **Re-run the combined re-check** (three lenses + the standing round-trip resolution check with the
   both-layouts / bare-hex-majority fixtures) at the re-stacked SHAs.
5. **Re-measure the blast radius** (`origin/main..<re-stacked B2>^`) at the re-stacked head — it will differ.
6. **Fresh paired hand-up** with the new SHAs, A10.3, and the re-measured blast-radius line.

## 3. What survives the re-stack (so it is not re-done for nothing)

The parts of your re-check that are independent of the conflicting files carry once their bytes are confirmed
unchanged at the re-stacked head: the option-(a) implementation logic (`child_ids` identity, alias-arm
removal, A9-safety — `child_alias_ids` never reaches `id_map`), the acceptance instrument's genuineness, the
contained-side intactness on the path channel, and the convener-error strike (the `staged_path_caveats`
"proof" stays struck — do not resurrect it). The routed non-gating items (E-1/E-2/E-3 → slice E, R-a →
residual) stand. Only the conflict-resolved files need fresh grading.

## 4. Note on foreseeability (shared, lightly)

Once R-4.8 landed (`38a4702`, publishing to origin/main), C/B2's eventual merge onto the advanced target was
going to need a re-stack — I could have flagged that at the landing and did not; you tested merge-clean onto
the stale local main rather than the advanced remote target. Both are the same lesson; I caught it at the
hand-up gate, which is where it must not get past. No hand-up on a conflicting stack.

`231437` stays WITHDRAWN; merge ≠ push ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — condition-3-prep verification only: git merge-tree --write-tree origin/main {b8083be,3762f37} (exit 1, conflicts named), git merge-base --is-ancestor 38a4702 main (exit 1), git show --stat 38a4702 (the conflicting files in R-4.8's delta), gh pr view {22,23} base = main, blast radius origin/main..3762f37^ = 27. This relay + its INDEX row on one explicit-path docs-lane commit whose SHA lands after filing. No fold, no merge, no token.
RELAY_LINT: per D-3.4 — per-file WITH freshness at this seat before filing; `.relays/s4/INDEX.md` tail re-read for sibling rows before appending; `--index`; commit GATED on both exits, path-scoped add AND commit. Token-style locks; other reds are the pre-existing sibling classes — none mine.
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to this relay and `.relays/s4/INDEX.md`.

CARRY LIST (D-8.5):
- `.relays/s4/s4-floor-impl/MERGE-GATE-ORCHESTRATOR-PLANNER-CB2-HANDUP-REFUSED-STACK-CONFLICTS-ORIGIN-MAIN-RESTACK-OWED-20260810-235506.md` → `s4-floor.planner`
- HAND-UP REFUSED at condition-3 prep: C b8083be + B2 3762f37 CONFLICT into origin/main 38a4702 (git merge-tree --write-tree exit 1) on sessions.cpp + 4 test files — the files R-4.8 modified and the fold also touched; you tested merge-clean onto STALE local main (dc12dcd, no R-4.8), not the current remote target
- OWED: re-stack C/B2 onto post-R-4.8 origin/main (38a4702), resolve conflicts, verify WHOLE stack merges clean, REDO carry adjudication (conflicting files' verdicts do NOT carry — fresh review), re-run combined re-check, re-measure blast radius, fresh paired hand-up
- survives: option-(a) logic, A9-safety, acceptance-instrument genuineness, contained-side intactness, the struck convener-error line, E-1/E-2/E-3→slice E, R-a→residual — for files whose end-state bytes are unchanged at the re-stacked head
- no hand-up on a conflicting stack; 231437 WITHDRAWN; release hold ABSOLUTE
