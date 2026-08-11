# FINAL CHECK RECORD — s4-matrix Wave-A, cumulative window `66250856` -> `d11c49c`

DISPATCH_ID: s4-matrix-wave-a-panel
PARENT_DISPATCH_ID: s4-matrix-wave-a-panel-disposition
FINAL_CANDIDATE_SHA: d11c49c  (second replacement head; S-1 + P-1 folded onto c52bcca)
CUMULATIVE_WINDOW: from the last FULL panel 66250856 through the final head d11c49c
LEAD: s4-matrix.planner (non-lens; no findings of my own, no re-grading)
DATE: 2026-08-08

## Cumulative window and chain-of-records (orchestrator record-shape tightening, 20260807-205729)

This record states the CUMULATIVE WINDOW explicitly and incorporates the prior records BY REFERENCE so the three read as ONE auditable panel history at merge condition 3:

- **66250856..c52bcca** (the 14-must-fix fold): covered by the targeted panel record `docs/sprints/2026-08-04-s4-step4/reviews/2026-08-08-s4-matrix-wave-a-targeted-panel-c52bcca.md` — INCORPORATED BY REFERENCE; 14/14 closed with regression-falsifying tests, M5 rewrite verified verdict-equivalent. That span is already checked and is not re-opened here.
- **66250856..c52bcca (full)**: the originating full panel `docs/sprints/2026-08-04-s4-step4/reviews/2026-08-07-s4-matrix-wave-a-panel-66250856.md` — the last FULL panel; the cumulative-diff baseline.
- **c52bcca..d11c49c** (this check): the second bounded fold, S-1 + P-1 — checked FRESH below.

**Blast-radius / clause-3 predicate:** the c52bcca..d11c49c product delta is exactly `src/core/repo/git.cpp` (+4 injected config lines, COUNT 3->5), `src/core/support/subprocess.cpp` (-1 line), and `tests/test_repo_git.cpp` (S-1 hostile test). It changes NEITHER design NOR blast radius — both Step-3 fences remain live at d11c49c, no scan/pack/open/manifest/report/cli/schemas source is touched, and no allowlist was reintroduced (lead-verified at the bytes, E1).

## Check composition

Per the after-fold-ins rule (bounded ~3-file delta): LEAD byte-verification + the two OWNING lenses (security for S-1, performance for P-1) only — not a full re-panel. Two cold read-only subagents, pinned to d11c49c, scoped to `git diff c52bcca d11c49c`. Both pair seats excluded from lenses; this seat non-lens lead. Spawn reconciliation: 2 spawns / 0 stalls / 2 finding-sets.

## LEAD byte-reconciliation (E1, at d11c49c)

- P-1: the per-write `bytes_.reserve(bytes_.size() + retained)` present at c52bcca:128 is ABSENT at d11c49c; ByteCapture::write goes straight to `std::ranges::transform(..., std::back_inserter(bytes_), ...)`.
- S-1: `GIT_CONFIG_COUNT` 3->5, adding `core.fsmonitor=` and `core.alternateRefsCommand=` (empty); `env.reserve` 18->22. No `protocol.allow`/allowlist anywhere.
- Both fences live; delta scope clean (no consumer/fenced production source).

## LEAD SYNTHESIS

Per-lens verdicts (bare):
performance approve
security must-fix

**FINAL-CHECK VERDICT: NOT panel-clean — one residual must-fix; the config-exec class disposition is ROUTED UP.** P-1 is closed (performance approve: the O(N^2) per-drain reserve is deleted, amortized O(N) restored, caps/raw-bytes/output_incomplete bit-for-bit unchanged, no new issue). S-1 as dispatched is closed and non-vacuous (security: fsmonitor/alternateRefsCommand proven neutralized, RED-without-fix demonstrated) — BUT the security lens, checking the CLASS for completeness, found a NEWLY-identified member the fixed-key strategy structurally cannot cover:

RESIDUAL (security, must-fix, E2 reproduced): a hostile repo-local `filter.<name>.clean` driver (with an in-tree `.gitattributes` assigning it) EXECUTES during `git status --porcelain=v2` in classify (classify.cpp:303) under the exact d11c49c injected env — the identical sink and threat model the panel already accepted for `core.hooksPath`. The fixed-key `GIT_CONFIG` injection cannot enumerate arbitrary filter names, so no number of added fixed keys closes it. The lens scoped it tightly: `filter.*.smudge` on restore is NOT reachable (target repo is fresh-init, config not versioned), and diff/merge drivers are NOT reachable (engine issues no diff/merge) — the one live vector is the clean filter via status.

## Why this routes UP rather than a third fixed-key fold

This is the THIRD round on the hostile-repo-local-config code-execution class (M1: 3 keys; S-1: 2 keys; now filter drivers). The security lens's own finding proves the FIXED-KEY STRATEGY is structurally insufficient — filter names are unbounded. The real fix is one of two shapes, and choosing between them is above the pair:

1. **Keep the neutralization posture (structural fold):** enumerate the DEFINED filter/diff drivers from the repo's config at classify time (`git config --get-regexp '^filter\..*\.(clean|smudge|process)$'` — you cannot predict names but you CAN read which are defined), inject empty overrides for exactly those, OR fail-closed (typed refusal) when a repo-local filter is assigned to tracked content. Consistent with the already-endorsed M1/S-1 folds; a real but bounded implementation with a design choice (neutralize-found vs fail-closed).
2. **Trust-posture ruling (no fold):** rule that pack-side plumbing over a repo the user CHOSE to pack is git-status-grade trust — the same code that already runs in the user's normal `git status`/shell-prompt on that repo — parallel to addendum-D's "networked open is git-clone-grade trust." Under this ruling the whole config-exec class is ANSWERED-BY-TRUST-POSTURE and the M1/S-1 folds were belt-and-suspenders, not a security boundary.

Lead observation (not a re-grade — the lens's must-fix stands): option 2 is in tension with the ALREADY-ENDORSED folds — the orchestrator endorsed neutralizing command-executing config keys as in-scope, so consistency points toward option 1 (finish the class with the structural fix). But option 2 is a legitimate posture the operator/m-1 could rule, exactly as the allowlist was ruled ANSWERED-BY-SEALED-RECORD. The fix PATH genuinely depends on that ruling, so it routes to the orchestrator before any third fold — a third fixed-key fold would be provably futile.

## Disposition

- Candidate d11c49c is NOT declared panel-clean. Condition 1 is unmet by exactly this one residual.
- Everything else in the cumulative window is verified: the 14 M-fixes (by reference), P-1 (this check), and S-1's two enumerated keys (this check).
- Carried unchanged: the Wave-C integration-window exit-mapping flag; the zero-ref capture_mode cell (awaiting m-1).
- Optionals/nits from the c52bcca panel remain Implementer discretion.

---

## VERBATIM LENS REPORTS (separated, unaltered)

### === LENS 1/2: performance (final P-1 check) ===

Lens: performance (final P-1 check)
Verdict: approve
Evidence: per-write reserve deleted -> E1 (source) -> git diff c52bcca d11c49c src/core/support/subprocess.cpp; remaining path is back_inserter geometric growth -> E1 -> git show d11c49c:src/core/support/subprocess.cpp:124-133
P-1 verification:
- per-write reserve removed: yes — the `bytes_.reserve(bytes_.size() + retained)` line present at c52bcca:128 is absent at d11c49c; `write` at d11c49c:124-133 goes straight from the retained/output_incomplete computation to `std::ranges::transform(input, std::back_inserter(bytes_), ...)`.
- capture restored to amortized O(N): yes — `std::back_inserter(bytes_)` with no per-call reserve lets std::vector use its geometric (capacity-doubling) growth, so total capture is amortized O(N) with O(log N) reallocations instead of the ~2048 exact-size reallocs the reserve forced. Drain loop at d11c49c:220-230 does one fixed 8 KiB stack `std::array` (no per-chunk heap alloc) and a single `capture.write` per read; no other per-chunk allocation/copy remains, so the path is not super-linear.
- observable behavior unchanged (caps/raw bytes/output_incomplete): yes — `retained = min(size, cap_ - min(cap_, bytes_.size()))` (d11c49c:125-126) and `output_incomplete_ = output_incomplete_ || retained != size` (127) are byte-identical to c52bcca; the cap clamp and truncation signal are untouched. transform still casts each `unsigned char` -> `std::byte` 1:1, so raw-byte fidelity is preserved. Deletion is cost-only.
- new issue in the delta: none — `retained` is still live (drives the cap clamp, the output_incomplete signal, and the transform span), so no dead variable; removing the reserve leaves no orphaned code.
Findings:
none
Verdict-one-line: approve — the O(N^2) per-drain reserve is deleted and the back_inserter path restores amortized-O(N) capture with caps, raw-byte fidelity, and output_incomplete all bit-for-bit unchanged.

### === LENS 2/2: security (final S-1 check) ===

Lens: security (final S-1 check)
Verdict: must-fix
Evidence: fsmonitor executes pre-fix and is defanged post-fix; filter.*.clean still executes during `git status` under the exact d11c49c injected env -> E2 -> local repro with a hostile repo-local config repo, engine env reproduced verbatim from `git show d11c49c:src/core/repo/git.cpp` lines 78-88.
S-1 verification:
- both keys neutralized: yes — `git show d11c49c:src/core/repo/git.cpp:85-88` (GIT_CONFIG_KEY_3=core.fsmonitor / VALUE_3=empty, KEY_4=core.alternateRefsCommand / VALUE_4=empty), COUNT bumped to 5 at :78, reserve to 22 at :71. Injected GIT_CONFIG_COUNT values are read last and outrank repo-local config; empty value defangs the program form. Proven E2: with COUNT=3 a repo-local core.fsmonitor ran (marker RAN_fsmon created); with the COUNT=5 set it did not.
- class complete for the engine's command set: INCOMPLETE: residual key filter.<name>.clean (and .smudge) — reasoning: content filter drivers are command-executing repo-local config in the same class, and they are NOT enumerable/neutralizable by the fixed-key injection strategy (filter names are arbitrary). Reproduced E2: a hostile repo-local `filter.evil.clean` + in-tree `.gitattributes: * filter=evil` executed the clean program during `git status --porcelain=v2` under the FULL d11c49c injected env (marker RAN_clean created in both pre- and post-fix runs). The sink is real and attacker-config-controlled: classify.cpp:303 runs `git status --porcelain=v2 -z` against the live/hostile repo whose repo-local config is on disk — the identical threat model the panel accepted for core.hooksPath. Scope note (not residuals): diff.<name>.command/.textconv and merge drivers are NOT reachable (engine issues no `git diff`/merge); filter.*.smudge is NOT reachable on the restore checkout path because restore does `git init` + `bundle unbundle` + checkout in a target repo whose config is default-init (config is not versioned, so the attacker's filter.*.smudge is never present) — verified by reading restore.cpp. The one proven live vector is the clean filter via status in classify/capture.
- test proves prevention (RED without fix): yes — `git show d11c49c:tests/test_repo_git.cpp:192-194`: after run_ok spawns real `git status` with the engine env, CHECK_FALSE(fs::exists(fsmonitor_marker)). Non-vacuous: I proved the marker IS created when the fsmonitor override is absent (COUNT=3). Caveat: the test covers only fsmonitor execution; core.alternateRefsCommand has only an env-presence CHECK (:186-188), no execution test; nothing covers the clean-filter residual.
- new issue / regression in the delta: none — subprocess.cpp only removes a `bytes_.reserve()` (geometric-growth perf; cap/output_incomplete logic unchanged, no security effect). git.cpp change is additive isolation; M1/M2/M3 untouched, no regression.
Findings:
1. must-fix src/core/repo/git.cpp:78-88 (sink: src/core/repo/classify.cpp:303) — hostile repo-local `filter.<name>.clean` executes during `git status` in the classify/capture path; the S-1 class is not closed because the fixed-key GIT_CONFIG injection cannot enumerate arbitrary filter/diff driver names — required change: neutralize content-filter execution for the read-only plumbing calls run over untrusted repos (e.g. run status/ls-files in a mode that does not apply content filters, or fail-closed when `.gitattributes` assigns a filter whose driver is defined in repo-local config) rather than adding more fixed keys — E2.
Verdict-one-line: must-fix — the fold correctly and non-vacuously closes core.fsmonitor/core.alternateRefsCommand, but the hostile-repo-local-config code-execution class is still open: `filter.*.clean` runs during `git status` on untrusted repos under the exact d11c49c env (proven E2).
