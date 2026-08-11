# TARGETED CHECK #5 RECORD — s4-matrix Wave-A, cumulative window `66250856` -> `cb1f6254`

DISPATCH_ID: s4-matrix-wave-a-panel
PARENT_DISPATCH_ID: s4-matrix-wave-a-panel-disposition
CANDIDATE_SHA: cb1f6254e1a275fd5e56ba91547d762145b32fa7  (fifth/final replacement head; PR #20 head; enumeration-completion folded onto a3c5454)
CUMULATIVE_WINDOW: from the last FULL panel 66250856 through cb1f6254
LEAD: s4-matrix.planner (non-lens; no findings of my own, no re-grading)
DATE: 2026-08-08

## Cumulative window and chain-of-records (orchestrator record-shape discipline)

- 66250856..c52bcca (full panel + 14-fix targeted): records `2026-08-07-s4-matrix-wave-a-panel-66250856.md` and `2026-08-08-s4-matrix-wave-a-targeted-panel-c52bcca.md` — INCORPORATED BY REFERENCE.
- c52bcca..d11c49c (S-1/P-1 fold): record `2026-08-08-s4-matrix-wave-a-final-check-d11c49c.md` — INCORPORATED BY REFERENCE (P-1 approved; S-1's two keys closed).
- d11c49c..a3c5454 (neutralize-found fold, check #4): record `2026-08-08-s4-matrix-wave-a-check4-a3c5454.md` — INCORPORATED BY REFERENCE (BLOCK — enumeration under-collected include/worktree scopes; completion directed under standing disposition, plus the orchestrator's added negative-control criterion).
- a3c5454..cb1f6254 (this check): the enumeration-completion fold — checked FRESH below.

**Blast-radius / clause-3 predicate:** the a3c5454..cb1f6254 product delta is exactly two files — `src/core/repo/git_exec.cpp` (`repo_local_command_config_keys`) and `tests/test_repo_engine.cpp` (three added TEST_CASEs). It changes NEITHER design NOR blast radius — both Step-3 fences live at cb1f6254 (`src/core/scan/scan.cpp:138` RepoDiscoveredUnsupported on `.git`; `src/core/manifest/manifest.cpp:597` `require_empty_array(object,"repos")`), no scan/pack/open/report/cli/schemas source touched, no allowlist, no fail-closed refusal (lead-verified, E1). Clean fast-forward over the fourth head; fold-3 commit a3c5454 preserved as ancestor.

## Check composition

Bounded per the directed shape and the orchestrator's added criterion: LEAD byte-verification + the SECURITY owning lens over the delta, grading BOTH directions (coverage AND the ordinary-repo negative control). One cold read-only subagent pinned to cb1f6254, scoped to `git diff 5be90ed6 cb1f6254 -- src/core/repo/git_exec.cpp tests/test_repo_engine.cpp` (the fourth published head through the fifth). Both pair seats excluded. Spawn reconciliation: 1 spawn / 0 stalls / 1 finding-set.

## LEAD byte-reconciliation (E1, at cb1f6254)

- Union enumeration: `repo_local_command_config_keys` now runs a `collect` lambda over TWO scopes into one shared key vector — `git config --local --includes --null --name-only --get-regexp <pattern>` and `git config --worktree --includes --null --name-only --get-regexp <pattern>` — pattern UNCHANGED (`^(filter\..*\.(clean|smudge|process)|diff\..*\.(command|textconv)|merge\..*\.driver)$`; no new family). Results appended, then `std::ranges::sort` + `erase(unique)`.
- Exit handling: exit-1 => empty set (ordinary no-match); for the `--worktree` scope, exit-128 gated on BOTH stderr anchors (`--worktree cannot be used with multiple working trees unless` AND `worktreeConfig is enabled`) => empty set for that scope only, preserving keys already collected from `--local`; every other nonzero => typed git_invocation_failure (propagates).
- Negative-control safety: `LC_ALL=C` pinned in the wrapper base env (git.cpp:77), so the English C-locale stderr anchors are deterministic — the exit-128 match cannot silently miss in another locale.
- Static base + carry unchanged: the five static injected keys and the empty-override composer are OUTSIDE this delta; the enlarged union set carries into capture via the existing engine-source state (no carry-site edit needed).
- `--local`/`--worktree` scope only; global untouched. Fences live; scope clean.

## LEAD SYNTHESIS

Per-lens verdict (bare):
security approve

**CHECK #5 VERDICT: GREEN — the neutralize-found command-exec class is CLOSED at the final head; condition 1 (adversarial panel) is met at cb1f6254.** The security owning lens returns approve on BOTH required directions:

- **(A) COVERAGE — PASS.** `--local --includes` follows `include.path`/`includeIf`/nested includes; `--worktree --includes` reads `.git/config.worktree` (main and linked). The union enumerates the entire repo-local surface git honors during classify's plumbing — system config is off (`GIT_CONFIG_NOSYSTEM=1`), global is trusted, and local/worktree precedence is irrelevant because every matched key is emptied regardless of value (a key-set union, not a value merge, is the correct superset). The lens's escape attempt found NO still-open repo-local exec path; the regex covers every exec-driver family and git lowercases names before `--get-regexp`, so the anchors hold. The two hostile TEST_CASEs (include-delivered and worktree-delivered `filter.evil.clean`) genuinely trap — RED without the completed enumeration (asserted `neutralized_git_config_keys == {"filter.evil.clean"}` AND absent marker both depend on the fix).
- **(B) NEGATIVE CONTROL — PASS.** The exit-128 special-case is not too broad (only git's worktree-config fatal emits that exact two-part phrase; other 128s and all `--local` failures still propagate) and not too narrow (single-worktree/extension-off repos treat `--worktree` as `--local` and do not error; only genuine multi-worktree+extension-off hits 128 — and git ignores `config.worktree` there anyway, so nothing executable is left unneutralized). The added TEST_CASE "classification treats disabled worktree config as empty in linked worktrees" creates a REAL linked worktree with worktreeConfig disabled and drives `git config --worktree` to exit 128 in the linked worktree; without the special-case, `REQUIRE(result.has_value())` goes RED. Ordinary-repo classify stays GREEN, exit 0, empty neutralization set — the orchestrator's added criterion satisfied at the bytes.

Union/dedup verified: when `--worktree` degrades to `--local` (single-worktree, extension off) a common-config key is emitted by both scopes but is byte-identical, so `unique` collapses it — no double injection, no dropped key.

## Disposition

- Candidate cb1f6254 IS panel-clean. Condition 1 (panel) MET at the final head. The full cumulative window 66250856..cb1f6254 is now verified: 14 M-fixes + P-1 + S-1's two keys (by reference) + the neutralize-found command-exec class closed across all three repo-local delivery paths {direct, include, worktree} with the ordinary-repo negative control green.
- **One LOW-severity, non-blocking note (Implementer-discretion, not a fold requirement):** an attacker-controlled repo-local `include.path` pointing at the absolute path of the user's global gitconfig would make `--local --includes` resolve and enumerate the user's trusted global filter keys (e.g. `filter.lfs.clean`), adding them to `neutralized_git_config_keys`. Consequence is exec-SAFE and read-only — the effect is only an EMPTY override (never execution), and the user's on-disk global config is untouched. The wrinkle is that this widens the neutralization/report set slightly beyond attacker-defined keys and could suppress the user's git-lfs clean during that one hostile-repo pack and surface a surprising `filter.lfs.clean` in the neutralized-keys report. Rated low by the lens; it does not reopen the exec boundary and is not a blocker to condition 1. Carried to the Implementer as discretion; if the operator wants it addressed it becomes a directed item.
- Carried unchanged: the Wave-C exit-mapping flag; the zero-ref `capture_mode` cell (still awaiting m-1).

---

## VERBATIM LENS REPORT (unaltered)

### === security (enumeration-completion check #5) ===

VERDICT: approve

Judged at commit cb1f6254 against the source shown by `git show`/`git diff`. Both scopes feed one shared `keys` vector that is sorted/deduped and returned to `classify.cpp:102-106`, then injected as empty overrides via the already-accepted composer in `git.cpp:112-129`. Injection path is uniform for both scopes.

(A) COVERAGE — PASS
- `--local --includes` (git_exec.cpp:104-105): prior head omitted `--includes`; git defaults `--includes` OFF under an explicit scope, so include-/includeIf-delivered driver keys were invisible. Adding `--includes` makes git follow `include.path`, `includeIf gitdir/onbranch`, and nested includes recursively. Enumeration runs with `cwd = repo` (git_exec.cpp:63) — the same cwd/HEAD as the classify plumbing (`git.run` adds `-C repo`), so gitdir/onbranch conditionals evaluate identically; no consistency gap.
- `--worktree --includes` (same lambda, called at :148): reads `.git/config.worktree` (main worktree) and `.git/worktrees/<id>/config.worktree` (linked) plus their includes.
- Escape attempt closed: the attacker-controlled repo-local config surface git honors during status/ls-files is exactly {local, worktree} plus their include chains (system is off via `GIT_CONFIG_NOSYSTEM=1`; global is trusted). The union `--local --includes` ∪ `--worktree --includes` enumerates that entire set. Precedence between local/worktree is irrelevant because every matched key is emptied regardless of value, so a key-set union (not a precedence merge) is the correct and sufficient superset. The regex `^(filter\..*\.(clean|smudge|process)|diff\..*\.(command|textconv)|merge\..*\.driver)$` covers every exec driver family; git canonicalizes section/variable names to lowercase before `--get-regexp` matches, so anchoring on lowercase `filter`/`diff`/`merge`/`clean`/… is sound, and `.*` absorbs dotted subsection (filter) names. I found no still-open repo-local exec path. No BLOCK finding.

(B) NEGATIVE CONTROL — PASS
- Special-case at git_exec.cpp:112-121 gates on scope=="--worktree" AND exit 128 AND both stderr anchors ("...cannot be used with multiple working trees unless" + "worktreeConfig is enabled") → returns empty for that scope only, preserving keys already collected from `--local`.
- Not too broad: only git's worktree-config fatal emits that exact two-part phrase; any other exit-128 (not-a-repo, malformed config) fails one anchor and still propagates via git_invocation_failure (:123-126). `--local` failures are never swallowed.
- Not too narrow: single-worktree repos with the extension off do not error (git treats `--worktree` as `--local` there — e.g. hostile test 1 succeeds), so only genuine multi-worktree+extension-off hits 128, which is exactly the swallowed case. Swallowing is safe because git also ignores `config.worktree` during plumbing when the extension is off, so nothing executable is left unneutralized.
- LC_ALL=C is pinned in the base env (git.cpp:78) and flows through `git_options`/`base_env_`, so the English stderr anchors are reliable.
- Test "classification treats disabled worktree config as empty in linked worktrees" (test_repo_engine.cpp): `worktree add` then `classify(git, linked, …)` drives `git config --worktree` to exit 128 in the linked worktree; without the special-case, `collect("--worktree")` returns git_invocation_failure and `REQUIRE(result.has_value())` goes RED. Genuinely exercises the path.
- Hostile tests genuinely trap: "…from local includes" is RED pre-fix because `--get-regexp` without `--includes` never enumerates `filter.evil.clean` (driver would run → marker exists, and neutralized list ≠ {filter.evil.clean}); "…from worktree config" is RED pre-fix because prior code never read `--worktree`. Both assertions (marker absent AND exact neutralized-keys vector) depend on the completed enumeration.

Union/dedup: `std::ranges::sort` + `erase(unique)` at git_exec.cpp:150-151. When `--worktree` degrades to `--local` (single-worktree, extension off), a key defined in common config is emitted by both scopes but is byte-identical, so unique collapses it — no double injection, no dropped key.

Lower-severity note (not blocking): an attacker-controlled repo-local `include.path` pointing at the absolute path of the user's global gitconfig (e.g. `include.path = /Users/<user>/.gitconfig`) makes `--local --includes` resolve and enumerate the user's trusted global filters (git-lfs). Consequence is exec-SAFE — the effect is only to add e.g. `filter.lfs.clean` to `neutralized_git_config_keys`, i.e. an empty override, never execution. The user's on-disk global config is untouched. The correctness wrinkle: that neutralized-keys list persists into capture (capture.cpp:256), so a hostile repo could suppress the user's git-lfs smudge/clean during pack and also surface a surprising `filter.lfs.clean` in the neutralized-keys report. Read-only and non-exec, so I rate it low, but worth a comment since it slightly widens neutralization beyond attacker-defined keys.
