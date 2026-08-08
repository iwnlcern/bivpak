# TARGETED PANEL RECORD — s4-matrix Wave-A fold verification at `c52bcca`

DISPATCH_ID: s4-matrix-wave-a-panel
PARENT_DISPATCH_ID: s4-matrix-wave-a-panel-disposition
CANDIDATE_SHA: c52bcca1f268b9d8ac6e414cd3874a5ba9829601  (replacement head; REVIEW-FOLD of the panel at 66250856)
PRIOR_PANEL: docs/sprints/2026-08-04-s4-step4/reviews/2026-08-07-s4-matrix-wave-a-panel-66250856.md
FOLD_DELTA: `git diff 66250856 c52bcca` = 25 files, +1937 -1084 (reviewed surface; NOT the full branch)
LEAD: s4-matrix.planner (non-lens; no findings of my own, no re-grading)
DATE: 2026-08-08

PANEL_CHOSEN: team-of-4 seats (targeted, delta-scoped)
DEFAULT_ROLES_CHANGED: yes
WHY_THIS_PANEL: post-fold VERIFICATION sized to the fold delta per the cumulative-diff rule (bounded fold => targeted panel, not a full re-run). Same five lens DOMAINS as the prior full panel, but performance and idiomaticity — the two lower-residual-risk domains, whose prior findings were mechanical/optional-tier — were MERGED into one seat for the delta; correctness, security, and test-coverage kept dedicated seats because the fold carried the highest regression surface there (an eligibility ALGORITHM rewrite, new security-critical isolation/validation/containment code, and a new shared git_exec module). Each lens had a dual charter: confirm each assigned M-fix closes its finding AND hunt for defects the fix itself introduced.
ROLES:
- correctness — M5 (algorithm rewrite: verdict-equivalence), M6/M7/M8, M14 conformance, byte-answered items, penumbra single-impl
- security — M1 isolation, M2 validation, M3 containment, ruled removals (fetch/allowlist)
- test-coverage — did the new/changed tests falsify a regression; no new false-greens
- performance+idiomaticity (merged) — M4 budgets, M5 O(refs+tips), M11 dedup, M12/M13, and fold-introduced perf/idiom defects
PANEL_COMPOSITION: four independent cold read-only subagents, each pinned to `c52bcca` and instructed to review ONLY the fold delta `git diff 66250856 c52bcca`, not the whole branch. Both pair seats excluded from lenses (5/5b); this seat non-lens lead. No re-spawn.

## Spawn-count reconciliation

| lens seat | spawns | stalls | finding-sets |
|---|---|---|---|
| correctness | 1 | 0 | 1 |
| security | 1 | 0 | 1 |
| test-coverage | 1 | 0 | 1 |
| performance+idiomaticity | 1 | 0 | 1 |

4 spawns = 4 finding-sets + 0 stalls. No stall (every seat produced a deliverable); the idle-notifications were completion signals. Each report retrieved verbatim (test-coverage/correctness via the mailbox to the lead; security via mailbox; perf+idiom via the subagent transcript) and reproduced below unaltered.

## LEAD PRE-PANEL RECONCILIATION (E1, at c52bcca, before spawning)

- Fold delta 25 files, EVERY path inside the Implementer's FOLD_SCOPE all-in declaration; no scan/pack/open/manifest/report/cli/schemas production source touched.
- Both Step-3 fences LIVE at c52bcca (scan.cpp:138 RepoDiscoveredUnsupported; manifest.cpp:597 require_empty_array).
- Ruled items verified at the bytes: no transport allowlist / protocol.allow added; GIT_PROTOCOL_FROM_USER hygiene pinned; recovery fetch removed from eligibility.cpp; reset gone from restore.cpp; git_exec module + git_budget_expired kind present; test_probe.cpp single-compile.

## LEAD SYNTHESIS

Per-lens verdicts (bare):
correctness approve
test-coverage approve
security must-fix
performance+idiomaticity must-fix

**PANEL VERDICT: REVIEW-FOLD required — a SECOND, bounded fold of exactly two must-fixes.** The fold closed all fourteen prior must-fixes: correctness verified the M5 rewrite verdict-equivalent to the sealed method and M6/M7/M8/M14 closed with tests; test-coverage confirmed every fix has a regression-falsifying test (incl. the previously-untested promisor no-lazy-fetch property, now traced at the production Git::run chokepoint); security confirmed M2/M3 closed and both ruled removals absent; perf+idiom confirmed M4/M5/M11/M12/M13 closed. Two findings survive, both NARROW and CHEAP, one an incomplete class and one a fold-introduced regression:

S-1 (security, must-fix, E1) — **incomplete config-exec class.** M1 neutralized core.hooksPath/credential.helper/core.sshCommand but the same hostile-repo-local-config code-execution class also includes **core.fsmonitor** (runs on index refresh, reached by pack-side `git status --porcelain=v2`) and **core.alternateRefsCommand** (runs during bundle-create/clone object negotiation). Add both to the injected GIT_CONFIG deny-list (bump GIT_CONFIG_COUNT). NO sealed tension — this is neutralizing command-EXECUTING config keys (the same class already folded), NOT URL/transport policing, so it folds cleanly. No live path at c52bcca (engine unwired) but MUST close before Wave-C wires it into pack/restore.

P-1 (performance, must-fix, E2) — **fold-introduced O(N^2) capture regression.** A cheap fold-in added `bytes_.reserve(size + retained)` per 8 KiB drain chunk (subprocess.cpp:129); on libc++/libstdc++ that defeats vector geometric growth, making capture O(N^2) where the reviewed head was O(N) — ~2048 reallocations / ~17 GiB copied near the 16 MiB cap, on the realistic large-output paths (ls-remote many-ref, ls-files penumbra). Delete the per-write reserve (rely on back_inserter growth) or reserve once to a bounded target. Pure regression fix, no design tension.

Both fixes are localized (the git.cpp env-injection set; one line in subprocess.cpp) — a bounded second fold whose replacement head gets a TARGETED CHECK sized to its ~2-file delta (lead verify + the two owning lenses), not a full re-panel, per the after-fold-ins rule.

Optional / nit (Implementer discretion; verbatim in the reports): output_incomplete single shared bool + single-stream-only truncation not directly covered, non-atomic TempDir next_id_, test_subprocess env-mutation without a scope guard (test-coverage 1/2/3); the classify remote-name option-confusion that fails closed (security 2); the types.hpp <initializer_list> IWYU (perf+idiom 2).

Carried forward to the Wave-C INTEGRATION window (not a fold defect — correctness Q1): the RepoRestoreRow does not structurally separate WARNING-class (exit 2: repo-verify-divergence, local-ref-failed) from ADVISORY-class (exit 0) entries, so open.cpp's future exit-mapping must map an Ok-row-with-outcome=failed+divergence to exit 2 (D5.3) not exit 4 (D5.2) without string-matching. Recorded for the integration window.

Also carried (routed separately, unchanged by this panel): the zero-ref capture_mode inexpressible cell (SITREP-PLANNER-CAPTUREMODE-CELL-ROUTED-20260807-162054), awaiting the orchestrator's ruling; the fold left the current value unblessed as directed.

Rejected / weak: none — every finding cites file:line at c52bcca.

Live-verification impact (panel-level): none NEW at this SHA (units unwired); the prior panel's Wave-C entry conditions stand (run eligibility+capture against a realistic many-ref/minutes-class repo; the excludesFile dirt-gate fixture) and S-1 joins them as a pre-wiring must-close.

---

## VERBATIM LENS REPORTS (separated, unaltered, no lead re-grading)

### === LENS 1/4: correctness (fold-verify) ===

Lens: correctness (targeted fold-verify)
Verdict: approve
Evidence: fold delta 66250856->c52bcca closes all assigned correctness findings with no new defect -> E1 (source pinned at c52bcca) + E1 test-read; the relay's claimed E2 run was not independently re-executed here (workspace at a1df932, read-only, peers active) -> git show c52bcca:<path>, tests/test_repo_engine.cpp

Fold verification:
- M5: closed — eligibility.cpp rewrite is verdict-equivalent to the sealed method. Presence pass hoisted to mark_present_tips (git_exec cat-file -e, sha-cached) = O(tips); ancestry is one rev-list --ancestry-path per ref (eligibility.cpp:99-118) replacing per-tip merge-base --is-ancestor. `rev-list --ancestry-path sha..tip0 tip1...` yields exactly the tips of which sha is a proper ancestor (== branch handled separately at :88-92), so proven/sha_unpushed/unknown_tip verdicts match. Non-present tips skip the equality check safely (a tip == HEAD sha is always locally present). 4096-tip ceiling (:180-186) -> unknown_tip -> full = fail-safe, never data-loss. Union over ALL remotes, structured proof, proven=>overlay all intact. Tests: proven/overlay+proof (test:315), sha_unpushed->full (:844), unknown_tip honest+unmodified (:391), no_remote/unreachable (:364).
- M6: closed — one predicate at classify.cpp:107-110 sets RepoEntry.promisor (types.hpp:198, "never serialized"); carried to every later invoke as entry.promisor. invoke_git sets no_lazy_fetch=options.promisor (git_exec.cpp:63) and git.cpp:113 emits GIT_NO_LAZY_FETCH=1; missing-object on any promisor call -> promisor_objects_unavailable (git_exec.cpp:83-88). Trace test (:424-458): detection call has NO flag, every subsequent classify/eligibility/capture call DOES. Never re-derived.
- M7: closed — verify mismatch now returns an Ok row with "repo-verify-divergence" advisory (restore.cpp:526-529, :719-722) instead of std::unexpected(RepoRestoreFailed) exit-4 (the pre-fold bug at 66250856:restore.cpp:455). Per-ref failures carry detail -> local-ref-failed advisories. Test (:1005-1032) asserts outcome=failed + repo-verify-divergence, matching the finding text verbatim.
- M8: closed — capture.cpp maps bundle create --all / thin / verify PROCESS failures to git_invocation_failure{repo,op,exit_code} (:290, :410, :107); verify_bundle calls invoke_git with .promisor so missing-object mapping is gated there too (:100-108 via git_exec:83). Genuine neither-route RefUncapturable precheck: require_bundle_source_ref (:78-96) + remote_proven-without-proof (:377). Tests: ref_uncapturable (:705), promisor_objects_unavailable (:729).
- M14: closed — root repo (relpath ".") materializes directly into partial_root (restore.cpp:496, initialize_root_base uses init+unbundle/fetch, not clone). The pre-fold second mechanism (repo-materialize-<id> staging slot + finalize_root_repo per-child rename) is GONE. Slot-collision handled: non-root collision refused (:499-503); root skips that check (partial_root legitimately exists) and verify excludes .biv-stage from the porcelain check (:365-368). Test (:1097) plants a decoy repo-materialize-source + live stage/keep, asserts partial/.git materializes and both decoys survive untouched. Criterion 4 (one staging boundary) met.
- byte-answered (reset, fetch, nested): confirmed — establish_head replaced `reset --hard sha` with checkout --detach (detached) / checkout --force -B branch sha (branch) / symbolic-ref (unborn) per head_state (restore.cpp:410-430). Pack-side eligibility recovery fetch removed (unprovable=>unknown_tip=>full), test:391 proves the source repo is unmutated. Restore-side A1 fetches (ensure_object, initialize_root_base) are legitimate and retained. Nested workspace-wide fence unchanged (discover.cpp not in fold delta; classify.cpp:126-133 unchanged).
- penumbra single-impl: confirmed — one snapshot_penumbra in git_exec.cpp:168 (unions --others and --others --ignored), called from classify record_penumbra (:74) and capture run_penumbra_oracle (:138). The prior "two copies set-differenced" is gone; the remaining set_difference compares the classification-time snapshot vs a fresh capture-time snapshot from the SAME impl — that two-point-in-time oracle is the intended D2.3 loss/contamination check, not a duplicate. No second ls-files --others enumeration exists in the tree.

Findings (NEW defects the fold introduced, or unclosed items):
none

Boundary contract: pass — D5 error/outcome membership and criterion-4 single staging boundary hold across the changed engine units; no scan/pack/open/manifest surface touched.
Live verification impact: none — every assigned finding has an asserting test in test_repo_engine.cpp; the M5 equivalence is analytically sound and test-covered, so no NEW live check beyond the relay's already-owed E2 run is required. I did not re-run the suite at c52bcca (read-only, checkout at a1df932).
Questions:
1. M7 non-blocking: verify-divergence yields outcome=failed (RepoRestoreRow) PLUS a repo-verify-divergence advisory, and RepoRestoreRow.advisories does not structurally separate WARNING-class (exit 2: repo-verify-divergence, local-ref-failed) from ADVISORY-class (exit 0: non-carried refs, EmptyRepoPayloadOnly) entries. This is faithful to the finding text and tested, but the future open.cpp exit-mapping must reconcile D5.2 (failed=>failed-mid-apply/exit 4) with D5.3 (repo-verify-divergence=>warning/exit 2) — i.e., an Ok row with outcome=failed+divergence must map to exit 2, not exit 4, and warning-vs-advisory must be told apart without string-matching. Flag for the integration window; not a defect in this engine fold.

### === LENS 2/4: test-coverage (fold-verify) ===

I have everything I need. The trace fires inside `Git::run()` (the single production choke point that `invoke_git` and all classify/eligibility/capture calls route through), so the M6 trace test observes real spawned requests, not a test-only shim. Let me send my verdict.

Lens: test-coverage (targeted fold-verify)
Verdict: approve

Evidence: every fold must-fix now has a test that fails if the fix is reverted -> E2-local (build + 17/17 CTest incl. 32/32 repo-engine per Implementer; I verified the test source at `c52bcca`, no GitHub CI run yet) -> `git diff 66250856 c52bcca` over the 6 changed test files + `git show c52bcca:` on subprocess.cpp/git.cpp/git.hpp/git_exec.cpp/CMakeLists.txt.

Fold verification:
- M10a parent-passthrough: proven — `tests/test_subprocess.cpp:56-77@c52bcca` sets `BIV_PARENT_LEAK` in the parent via `::setenv`, request.env={"MARK=x1"}, child prints `isolated` iff the marker is absent; asserts `stdout=="x1|isolated"`. A passthrough regression flips it to `leak` and fails. Prior version only checked one var was visible.
- M10b eligibility-optional real classify: proven — the vacuous copy-ctor test (`std::optional` copy) was deleted from `tests/test_repo_git.cpp` (removed block, old lines 233-247). The property is covered by a real `classify()` zero-ref result at `tests/test_repo_engine.cpp:170-174@c52bcca` (`CHECK_FALSE(zero->entry.eligibility.has_value())` on an unborn zero-ref repo). Not vacuous; no vacuous replacement introduced.
- M10c cap saturation both streams + output_incomplete: proven — `tests/test_subprocess.cpp:70-84@c52bcca` sets stdout_cap=3 and stderr_cap=3, child writes 6 bytes to each; asserts `output_incomplete` true and exact truncated sizes `stdout=="abc"`, `stderr=="uvw"`. Production field exists (`subprocess.hpp:32`) and is set by `ByteCapture` on both streams (`subprocess.cpp:552-556`).
- M6 promisor no-lazy-fetch trace test: proven — `tests/test_repo_engine.cpp:445-487@c52bcca` installs a `Git::RequestTrace` recording every `SpawnRequest`. Trace fires inside production `Git::run()` (`git.cpp` `trace_(request)` immediately before `run_argv`), and every git call in classify/eligibility/capture routes through `Git::run` (incl. `invoke_git` -> `git.run`). Test asserts the promisor-detection call (`--get-regexp`) does NOT carry `GIT_NO_LAZY_FETCH=1` and `all_of` subsequent classify requests DO; then `all_of` eligibility+capture requests carry it. A single dropped call-site fails `all_of`. Closes the prior panel's "no test" gap; boundary polarity (detection excluded) is pinned by `CHECK_FALSE`.
- M9 tolerance rows RED-proven: proven — `harness/selftest/test_compare.py:135-145@c52bcca` removes the `git-administration` row and asserts an "extra path: repo/.git/untracked-admin-byte" finding appears; `:154-165` removes `git-tracked-file-mtime` and asserts "file-mtime mismatch for repo/a.txt". Both green baselines exist (existing `_are_excluded`/`_is_semantically_ignored` tests assert `== []` with the rows present), so each pair proves the row is LIVE, driven by `compare.py`'s `_row_policy(...)` gates.
- M13 shared temp_dir: proven — `tests/support/temp_dir.hpp@c52bcca` deletes copy AND move (with `static_assert !is_copy_constructible && !is_move_constructible`), id = name+`getpid()`+incrementing `next_id_`; the three duplicate class definitions are removed from test_subprocess/test_repo_git/test_repo_engine (and test_probe) in favor of `using biv::test_support::TempDir`.
- test_probe single-compile: confirmed — `CMakeLists.txt` drops `tests/test_probe.cpp` from `biv_tests` (line 141 delta) and it now compiles only in `biv_probe_tests` (`c52bcca:CMakeLists.txt:169`). Previously double-compiled.

Findings (NEW false-greens or unclosed test gaps):
1. optional `tests/test_subprocess.cpp:73-84@c52bcca` — `output_incomplete` is one shared bool written by both stream captures, so the flag alone cannot localize which stream saturated; the test disambiguates only via the per-stream length asserts (`=="abc"`/`=="uvw"`). Not a false-green (both saturations are independently proven), but a single-stream-only truncation is not directly covered. Suggest one test that saturates exactly one stream. E2-local.
2. optional `tests/support/temp_dir.hpp:37@c52bcca` — `next_id_` is a non-atomic `static std::size_t`; collision-resistance holds only under serial Catch2 execution (pid still separates processes). Latent if tests are ever parallelized. Consider an atomic counter. E1.
3. optional `tests/test_subprocess.cpp:56-63@c52bcca` — the test mutates the real process environment (`::setenv`/`::unsetenv`) with no scope guard; safe as written (no throw between set and unset) but leaks the marker if an assertion is ever added between them. E1.

Boundary contract: pass — the `RequestTrace` seam is bound to the production forwarding edge; `Git::run()` traces the exact `SpawnRequest` it hands to `run_argv`, and all engine git calls funnel through `Git::run`, so the trace enumeration is complete (no bypass via `invoke_git`).

Live verification impact: none — coverage claims are provable at source + E2-local; no host/CI-runner-specific behavior is asserted (the budget-expiry test's 1s-vs-20ms margin is host-robust).

Questions: none

### === LENS 3/4: security (fold-verify) ===

Lens: security (targeted fold-verify)
Verdict: must-fix
Evidence: fold closes M2/M3 cleanly and confirms both ruled removals; M1's injected-config neutralization is complete only for the 3 named keys but leaves same-class command-exec keys open (core.fsmonitor reachable via pack-side `git status`) -> E1 -> git.cpp@c52bcca:78-84, classify.cpp@c52bcca:303, git docs.
Fold verification:
- M1: closed (for named scope) — GIT_CONFIG_GLOBAL=/dev/null now gated on opts.isolate_global_config (git.cpp@c52bcca:110-112) set only from options.restore (git_exec.cpp:62), so pack-side reads user global excludes again; hooksPath/credential.helper(reset via empty)/sshCommand injected in base_env at command-scope precedence (git.cpp@c52bcca:78-84), overriding repo-local; GIT_PROTOCOL_FROM_USER=0 default, =1 only on opt-in (git.cpp@c52bcca:109). See Finding 1 for residual keys.
- M2: closed — path/url/target values go through operand channel after `--` (git.cpp@c52bcca:102-104); object ids hex-validated (valid_object_id) and ref names check-ref-format-validated (valid_ref_name) at the type boundary in validate_entry (restore.cpp@c52bcca:76-121) and eligibility append/mark before argv. One residual, Finding 2.
- M3: closed — validate_entry rejects absolute/`..`/non-normalized relpath+members (valid_manifest_path), then contained_member weakly_canonical + lexically_relative `..`-check fires BEFORE mkdir/unbundle/clone (restore.cpp@c52bcca:123-141, called at 353-372 before any fs op). Symlink-escape covered by canonicalization. No defect.
- ruled removals (fetch, allowlist): confirmed-absent — mutating `fetch` into engine_source repo is gone from eligibility.cpp (now ls-remote advertisement + local cat-file/rev-list only; the surviving fetches in restore.cpp target the fresh partial repo, not the source); no protocol.allow/allowlist/host-floor string anywhere in the changed engine files; git.hpp comment explicitly disclaims a URL/host allowlist.
Findings:
1. must-fix src/core/repo/git.cpp@c52bcca:78-84 — injected GIT_CONFIG neutralizes only core.hooksPath/credential.helper/core.sshCommand, but the same hostile-repo-local-config code-exec class still includes core.fsmonitor (hook-program form runs on index refresh; reached by pack-side `git status --porcelain=v2` at classify.cpp@c52bcca:303) and core.alternateRefsCommand (runs during bundle-create/clone object negotiation when an alternates file is present). Both are repo-local, unaffected by GIT_CONFIG_NOSYSTEM or the restore-side GIT_CONFIG_GLOBAL. Required change: add core.fsmonitor= (empty/false) and core.alternateRefsCommand= to the injected GIT_CONFIG set (bump GIT_CONFIG_COUNT), or otherwise deny-list command-executing config keys. — E1
2. optional src/core/repo/classify.cpp@c52bcca:227,286 — remote name from `git remote` output is interpolated into `{"remote","get-url",name}` in option position; `git remote get-url` has no `--` end-of-options, so a hand-edited hostile `.git/config` section like [remote "--all"] reaches argv unvalidated. No dangerous option exists on get-url so this is option-confusion (fails closed), not RCE, but it is a value-typed string bypassing the type boundary. Required change: reject names with a leading `-` (or read via `git config --get remote.<name>.url` with validated name). — E1
Boundary contract: pass — Wave A stays unwired into scan/pack/open/manifest; no new spawn site outside subprocess.cpp (all git routes through git.run -> support::run_argv); subprocess fd/CLOEXEC/process-group logic unchanged (diff only adds output_incomplete truncation-detection + uninitialized read buffer, both benign); no host-store write or agent launch in changed lines.
Live verification impact: none — units unreachable from product at c52bcca, so Finding 1 has no live exploit path today; it must close before this engine is wired into pack/restore.
Questions: none

### === LENS 4/4: performance+idiomaticity (fold-verify) ===

I have completed the targeted fold-verification. All fold items verified closed except one new performance defect the fold introduced in the subprocess capture path. Here is my panel data.

---

Lens: performance+idiomaticity (targeted fold-verify)
Verdict: must-fix
Evidence: fold delta `git diff 66250856 c52bcca` reviewed, reads pinned to `git show c52bcca:*` -> E2 (source-dispositive) -> src/core/repo/{git_exec,eligibility,git,capture,classify,restore}.{hpp,cpp}, src/core/support/subprocess.{hpp,cpp}, tests/support/temp_dir.hpp, harness/bivharness/{compare,fixtures}.py

Fold verification (performance):
- M4 budgets: closed — `GitCallClass{local,network,bundle}` map to 30s/2min/5min via `budget_for` (git_exec.cpp:14-25); `budget_override` honored (git_exec.cpp:67); timeout ⇒ `git_budget_expired` distinct from `git_invocation_failed` (git_exec.cpp:74-83); capped output ⇒ `output_incomplete` ⇒ fail-closed `git_invocation_failed` (git_exec.cpp:80-83, subprocess.hpp:32). Three call classes wired at every site (capture.cpp:99/268/361 bundle, eligibility.cpp:182 network, restore.cpp:180/229/393/513 mixed).
- M5 O(refs+tips): confirmed — one `cat-file -e` per unique sha memoized in `mark_present_tips` (eligibility.cpp:56-75), one `rev-list --ancestry-path` per ref passing ALL present tips in a single spawn (eligibility.cpp:100-108); spawns = O(remotes+unique_shas+refs). 4096-tip ceiling present: `kMaxAdvertisedTips` guards `append_advertisement` (eligibility.cpp:30) and forces-full per-remote (eligibility.cpp:194-201).

Fold verification (idiomaticity):
- M11 git_exec dedup + single penumbra: closed — all nine helpers defined only in git_exec.cpp (grep of `src/core/repo/*.cpp` returns git_exec.cpp exclusively); `snapshot_penumbra` is ONE function, called from classify.cpp:74 and capture.cpp:138; no residual copies in classify/capture/eligibility/restore. `expected`-shadowing renamed: the only `expected*` local is `expected_ref` (restore.cpp:322), a ref-name string, not a shadow of the `expected<T>` alias.
- M12 error_code filesystem: closed — all four restore.cpp calls use non-throwing overloads (`create_directories`+ec:63, `exists`+ec:73, `weakly_canonical`+ec:122/125, `is_regular_file`+ec:175); no throwing `std::filesystem::` call remains in the changed body.
- M13 shared TempDir: closed — tests/support/temp_dir.hpp: copy AND move deleted (with `static_assert`s), `inline static next_id_` counter + pid in the path.

Findings (NEW defects the fold introduced, or unclosed items):
1. must-fix [perf] src/core/support/subprocess.cpp:129 @c52bcca — `bytes_.reserve(bytes_.size() + retained)` runs on every 8 KiB drain chunk (drain_once, subprocess.cpp:221-224). `reserve(n)` allocates exactly `n` on libc++/libstdc++, so it defeats `std::vector`'s amortized geometric growth: after each append size==capacity, and the next write reallocates+copies the whole buffer. Capturing near the 16 MiB `kCaptureCap` (git.cpp:14) means ~2048 reallocations copying ~17 GiB cumulatively — O(N²) where the reviewed head (66250856, no reserve, plain `back_inserter`) was O(N). Hits the realistic large-output paths (ls-remote on many-ref remotes, ls-files penumbra on large trees). Required change: delete the per-write `reserve` (rely on `back_inserter` geometric growth), or reserve once up front to a bounded target. — E2
2. optional [idiom] src/core/repo/types.hpp @c52bcca (`engine_error_kind`) — the array-driven range-`for` over a braced-init-list deduces `std::initializer_list<EngineErrorKind>` and thus requires `<initializer_list>`, but types.hpp pulls it in only transitively (via `<vector>`/`<optional>`). The same fold explicitly lists `<initializer_list>` in git_exec.hpp, so this is an IWYU inconsistency, not a compile break. Required change: add `#include <initializer_list>` to types.hpp. — E1

Notes on the other cheap fold-ins (all clean): `drain_once` buffer de-zeroing (subprocess.cpp:221) is safe — only `count` read bytes are consumed. `git.cpp` `env.reserve(18U)` correctly covers the enlarged base env. New budget arithmetic is `std::chrono::milliseconds` throughout, no overflow/UB. git_exec.hpp header hygiene is correct IWYU (includes types.hpp directly; `#pragma once` makes manifest include-order moot). Harness fold-ins confirmed: `@functools.cache` on `_git_binary()` and 30s `timeout=`+`TimeoutExpired` handling in both compare.py and fixtures.py. capture set_difference `back_inserter` (capture.cpp:145/152) is correct idiom (result size unknown); bulk range-insert used where sizeable (capture.cpp:350).

Boundary contract: pass — reviewed only the 25-file fold delta, reads pinned to c52bcca, no whole-branch re-review.
Live verification impact: none — finding 1 is source-dispositive; a microbench would corroborate but the reserve-vs-geometric-growth behavior is determined by the source on the actual libc++/libstdc++ build targets.
Questions: none

---

## APPENDIX — lens charters (targeted, delta-scoped)

All four lenses received: the replacement head c52bcca and the reviewed head 66250856; the instruction to review ONLY `git diff 66250856 c52bcca` (the fold delta, 25 files), pinning reads to `git show c52bcca:<path>`, and NOT to re-review the whole branch; the dual charter (confirm each assigned M-fix closes its finding AND hunt fold-introduced regressions in the changed lines); the fixed return format (Lens / Verdict / Evidence / Fold verification per M-item / Findings / Boundary contract / Live verification impact / Questions). Per-seat M-item assignments are as in ROLES above.
