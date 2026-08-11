# TARGETED CHECK #4 RECORD — s4-matrix Wave-A, cumulative window `66250856` -> `a3c5454`

DISPATCH_ID: s4-matrix-wave-a-panel
PARENT_DISPATCH_ID: s4-matrix-wave-a-panel-disposition
CANDIDATE_SHA: a3c5454539ab4664573a51840855198416630ffd  (third replacement head; neutralize-found folded onto d11c49c)
CUMULATIVE_WINDOW: from the last FULL panel 66250856 through a3c5454
LEAD: s4-matrix.planner (non-lens; no findings of my own, no re-grading)
DATE: 2026-08-08

## Cumulative window and chain-of-records (orchestrator record-shape discipline)

- 66250856..c52bcca (full panel + 14-fix targeted): records `2026-08-07-s4-matrix-wave-a-panel-66250856.md` and `2026-08-08-s4-matrix-wave-a-targeted-panel-c52bcca.md` — INCORPORATED BY REFERENCE.
- c52bcca..d11c49c (S-1/P-1 fold): record `2026-08-08-s4-matrix-wave-a-final-check-d11c49c.md` — INCORPORATED BY REFERENCE (P-1 approved; S-1's two keys closed; the filter.*.clean residual routed and directed).
- d11c49c..a3c5454 (this check): the third bounded fold, neutralize-found — checked FRESH below.

**Blast-radius / clause-3 predicate:** the d11c49c..a3c5454 product delta is the classify/git-wrapper config-enumeration surface (git.cpp/hpp, git_exec.cpp/hpp, types.hpp, classify.cpp, capture.cpp) plus two test files. It changes NEITHER design NOR blast radius — both Step-3 fences live at a3c5454, no scan/pack/open/manifest/report/cli/schemas source touched, no allowlist, no fail-closed refusal (lead-verified, E1).

## Check composition

Bounded per the directed shape: LEAD byte-verification + the SECURITY owning lens over the delta. One cold read-only subagent pinned to a3c5454, scoped to `git diff d11c49c a3c5454`. Both pair seats excluded. Spawn reconciliation: 1 spawn / 0 stalls / 1 finding-set.

## LEAD byte-reconciliation (E1, at a3c5454)

- Enumeration: `git config --local --null --name-only --get-regexp` over `^(filter\..*\.(clean|smudge|process)|diff\..*\.(command|textconv)|merge\..*\.driver)$` (git_exec.cpp `repo_local_command_config_keys`); exit-1 => empty set; other nonzero => typed failure; keys sorted/deduped.
- Dynamic overrides: `Opts::empty_config_keys` appended after the 5 static keys in git.cpp `build_spawn_request`, `GIT_CONFIG_COUNT` recomputed; base static keys unchanged; carried into capture via engine-source state.
- No fail-closed refusal; `--local` only (global untouched). Fences live; scope clean.

## LEAD SYNTHESIS

Per-lens verdict (bare):
security block

**CHECK #4 VERDICT: BLOCK — the directed neutralize-found fix is INCOMPLETE; the identical filter.*.clean exec vector survives via two config-delivery mechanisms the enumeration does not read. NOT panel-clean.** The fix correctly closes the direct `.git/config` form (RED/GREEN test real and non-vacuous), and the override mechanism, `--local` global-exclusion, and enumeration-read safety are all correct. But the security lens proved (E2, live repros) two enumeration MISSES of the SAME `filter.*.clean` family:

1. **include.path / includeIf:** `git config --local --get-regexp` defaults `--includes` OFF for a specific scope, so a driver in a file pulled via `[include] path=...` in `.git/config` is NOT surfaced (rc=1), yet `git status` follows includes and EXECUTES it. Trivial to plant, no prerequisites.
2. **extensions.worktreeConfig:** a driver in `.git/config.worktree` (with `core.repositoryformatversion=1` + `extensions.worktreeConfig=true`) is NOT surfaced by `--local`, yet `git status` reads worktree config and EXECUTES it.

Convergence, not treadmill: the lens's EXHAUSTIVE sweep confirms this is the complete boundary — every other command-exec key (`diff.external`, `core.gitProxy`, `protocol.*.command`, `url.*.insteadOf`, `remote.*.uploadpack`, pager/editor, aliases, `safe.directory`) is confirmed NOT reachable by the commands classify/capture issue, and the static-injected keys beat all scopes. The class closes once the enumeration reads the full repo-local surface.

**Proven corrective form (the completion fold):** add `--includes` to the existing `--local` pass AND add a second `--worktree --includes` enumeration pass, unioning the results — the lens verified this catches both bypasses while NOT leaking the global git-lfs key (global preserved), and the empty `GIT_CONFIG_*` override already outranks every scope, so ONLY the enumeration needs completing. (Implementation note carried to the dispatch: `git config --worktree` errors when `extensions.worktreeConfig` is disabled — the normal case — so that exit must be treated as empty-set, not a typed failure, or classify breaks on every ordinary repo.)

## Disposition

- Candidate a3c5454 is NOT panel-clean. Condition 1 unmet by exactly this enumeration-completeness gap.
- This is a bounded COMPLETION of the already-directed neutralize-found fix (not unbuildable, not a new design decision), dispatched to the Implementer under the standing disposition; a fifth targeted check follows on its head.
- Everything else in the window is verified (14 M-fixes + P-1 + S-1's keys + the direct filter form, all by reference/this check).
- Carried unchanged: the Wave-C exit-mapping flag; the zero-ref capture_mode cell.

---

## VERBATIM LENS REPORT (unaltered)

### === security (neutralize-found check #4) ===

Lens: security (neutralize-found check #4)
Verdict: block
Evidence: enumeration `git config --local … --get-regexp` misses include- and worktree-scoped driver keys that `git status` still executes -> E2 (live git repros) -> `git show a3c5454:src/core/repo/git_exec.cpp` `repo_local_command_config_keys` + scratchpad repros
Neutralize-found verification:
- closes clean-via-status vector: yes (only the narrow form) — the driver defined DIRECTLY in repo-local `.git/config` is surfaced by `--local` and beaten by the empty `GIT_CONFIG_*` override; `tests/test_repo_engine.cpp` "classification neutralizes repo-local clean filter commands" (a3c5454) is real and non-vacuous: it commits `.gitattributes: * filter=evil`, installs a real executable clean program, asserts the enumerated key set AND `CHECK_FALSE(exists(marker))` — removing the override would recreate the marker. But this covers only the `.git/config`-direct delivery, not the class.
- enumeration complete (worktree-config / includes / other command-exec keys): INCOMPLETE: TWO reachable, proven bypasses of the SAME `filter.*.clean` family the fix targets —
  1. include.path / includeIf: `git config --local --get-regexp` defaults `--includes` OFF for a specific scope, so a driver defined in a file pulled via `include.path=evil-include` in `.git/config` is NOT surfaced (rc=1), yet `git status --porcelain=v2` follows includes and EXECUTES it (marker written). Repro: scratchpad `inc2/` — [B] `--local` misses, [C] default-scope catches, [D] status executed. Trivial to plant (no prerequisites).
  2. extensions.worktreeConfig: with `core.repositoryformatversion=1` + `extensions.worktreeConfig=true` in `.git/config`, a driver in `.git/config.worktree` is NOT surfaced by `--local` (empty result), yet `git status` reads worktree config and EXECUTES it. Repro: scratchpad `wt-probe/` — MARKER PRESENT.
  Corrective form (proven in scratchpad): enumerate with `--includes` AND add a `--worktree --includes` pass, unioned. `--local --includes` catches the include key and does NOT leak the global `filter.lfs.clean` (git-lfs preserved); `--worktree --includes` catches the worktree key that plain `--local --includes` still misses (rc=1). The `GIT_CONFIG_*` empty override already outranks every scope, so ONLY the enumeration needs completing.
  Other command-exec keys considered and NOT reachable (correctly out of scope): `diff.external`, `core.gitProxy`, `protocol.*.command`, `url.*.insteadOf`/`remote.*.uploadpack` — all require a `git diff`/network-transport call, and classify/capture issue none (config, ls-files, status, for-each-ref, rev-parse, remote, `remote get-url` [read-only], symbolic-ref, show-ref, bundle create/verify only). `core.pager`/`core.editor`/`sequence.editor` unreachable (piped, non-interactive). `alias.status` etc. are ignored by git because they shadow builtins. `core.hooksPath`, `core.fsmonitor`, `core.sshCommand`, `credential.helper`, `core.alternateRefsCommand` are static-covered via `GIT_CONFIG_*` (beat all scopes). `safe.directory` is not an exec vector.
- --local scope correct (global preserved, repo-local covered): issue — the intent (exclude global git-lfs, cover repo-local) is right, but bare `--local` OVER-narrows: it drops both include-following and worktree scope, opening the two bypasses above. `--local --includes` + `--worktree --includes` preserves global exclusion while covering the full repo-local surface (verified: global lfs key not leaked).
- enumeration step safe + no new delta issue: yes — the enumeration is a pure config read; no driver executes during `git config … --get-regexp` (confirmed across all repros, no marker). Dynamic env composition in `git.cpp build_spawn_request` (a3c5454) is correct (GIT_CONFIG_COUNT string-replaced, KEY_5+/empty VALUE_5+ appended); `git_exec.cpp invoke_git` copies the span into `Git::Opts`; capture carries `entry.engine_source->neutralized_git_config_keys`. The only defect is that the carried set is itself incomplete because enumeration under-collects.
Findings:
1. High `git_exec.cpp` `repo_local_command_config_keys` (a3c5454) — enumeration `{"config","--local","--null","--name-only","--get-regexp",pattern}` misses include.path/includeIf-defined and worktree-config-defined driver keys, both of which `git status` executes during classify — arbitrary command execution on pack of a hostile repo survives the fix — add `--includes` to the enumeration and add a second `--worktree --includes` enumeration pass, union the results (keeps global/git-lfs excluded; the empty `GIT_CONFIG_*` override already covers precedence) — E2
Verdict-one-line: block — the neutralize-found enumeration closes only the `.git/config`-direct driver form; sibling include-path and worktree-config deliveries of the identical `filter.*.clean` key are enumeration-missed and still execute during `git status`, so the proven command-exec class is not closed.
