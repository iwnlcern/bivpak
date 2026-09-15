# Sub-step 2b — wiring `biv pack` and `biv open` to the repo engine and the landed consent fabric at product scope — Implementation Plan (rev1)

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** connect both product verbs to the landed repo engine (`src/core/repo`) and the landed consent fabric (`src/cli/url_consent.cpp`), executing SEALED text only — M rev8 / N / O (m-1), A6 rev14 / A7 rev2 / A8 rev8 / A2 D4 (m-3), SR-URL rev5 (m-4), the R-4.47 bar — so that `biv pack` discovers, classifies, gates, captures and records repositories, `biv open` restores them per entry, PROMPT D fires at both encounters through the A6/A7/A8 fabric, `--offline` reaches the engine on both verbs, and every deferred witness (FX-M-1 (a)–(o) incl. (d) + (a)-interactive; FX-A6 a6·1–13 + a6·16's divergence half; FX-A7 a7·1–5; FX-A8 a8·1–a8·6; FX-N (a)/(g); R-4.48 (ii)–(iv)) executes at product scope.

**Architecture:** ONE candidate branch cut from the PUBLISHED PIN `186adf7d67171bd7afe621f39b657a1a113ce299`, commits in the veto-9 MECHANICAL order (the one pre-authorized engine commit FIRST; every call-site commit after it; no commit spans both sets), three product tranches A (fabric + CLI plumbing, zero engine reach) → B (open restore path) → C (pack pipeline, the shipped `.git` refusal RETIRED into the narrowed `UnclaimedGitEntry` class), then m-3's harness commit (arm-A shape), then the count-cell companion commit iff a case tuple moved. Every open-side witness first run on a hand-built image is RE-EXECUTED against a `biv pack`-produced image after tranche C, inside the candidate, before the packet (master 041518's condition). The landing rides a PR from the pushed remote branch (R-4.51 (2)); the R-4.49 census instrument is reused at its exact pin with a population written FOR the merge head.

**Tech Stack:** C++23 (`std::expected`), CMake presets `ci-macos` / `ci` (Linux parity container Ubuntu 24.04 `--platform linux/amd64 --init`), Catch2 v3.7.1, the pytest harness under `harness/` (python3.12 venv from `harness/requirements.lock`), bash 3.2-compatible runner blocks, `gh` for the PR.

**Spec (the sealed texts this plan executes; every path under `../pdc/`):** `master/domains/m-1-format-engine/design/2026-08-23-ADDENDUM-M-url-effective-endpoint-consent.md` (M rev8: M-R1..R8 :259-415, FX-M-1 :416-516); `…/2026-08-26-ADDENDUM-N-shallow-payload-only-cell.md` (N; flags-to-wiring-team :320-329; FX-N); `…/2026-09-01-ADDENDUM-O-writer-validity-contract.md` (O; FX-O); `…/2026-07-02-pack-engine.md` (§1.1 Phase D/C, §1.2, §1.3, §2 incl. COND-6, §4); `…/2026-07-02-restore-apply-contract.md` (§1, §2.2); `…/2026-07-04-ADDENDUM-D-offline-and-n3.md` (:78 `offline-pointer`); `…/2026-08-07-ADDENDUM-I-biv-member-refusal.md` (I-R1, I-R2a); `master/domains/m-3-restore-cli/design/2026-08-24-addendum-6-url-consent-consumer-surface.md` (A6 rev14: A6-R1..R9 :380-685, FX-A6 :686-822); `…/2026-08-26-addendum-7-consent-interaction-companion.md` (A7 rev2: A7-R1..R5 :57-138, FX-A7 :139-175); `…/2026-08-29-addendum-8-display-encoding-companion.md` (A8 rev8: A8-R1..R4 :92-256, FX-A8 :257-352); `…/2026-07-04-addendum-2-n24-honest-network-offline.md` (A2 D4 :77-127, D5); `master/domains/m-4-hostile-image/design/2026-08-23-sr-url-effective-endpoint-consent.md` (SR-URL rev5); the R-4.47 bar (`master/relays/m4-reachability-rereview/DESIGN-REVIEW-planner-20260827-204641.md` §1).

**Owner fences this plan is graded against (each read WHOLE by the implementer before Task 0; nothing in them is paraphrased here as authority):** m-1 `master/relays/intg-2b-wiring-act/DESIGN-planner-20260915-042531.md` (vetoes 1–9 with veto 9 mechanical; V-M-INT-1..5; V-2b-1..9; S-2b-1..8; the FX partition; §4 evidence set); m-3 `…/DESIGN-planner-20260915-130818.md` (V-A6-1..6, V-A7-1..4, V-A8-1..5, R-4.48 (ii)–(iv) as vetoes with witnesses; the R4 absence bar in its positive form; TC-1..3; S-1..S-6; §3 the kind; §4 the `--offline`/`--network` cut verbatim; §5 the golden-harness repos bar; §6 the harness-selftest population rule); m-4 `…/DESIGN-planner-20260915-035001.md` (the carry; the E-split; the C-2 pre-warning); m-2 `…/DESIGN-m2-planner-20260915-125200.md` (Q4 NOT a touch on the stated shape — the human open summary moves no session line; a deviation routes back); master `…/PLAN-master-planner-20260915-041518.md` (Q1 both verbs; the re-execution condition; Q5/Q6), `…-043301.md` (`--offline` IN both verbs), `…-131404.md` (all gates IN; the three dispositions; the plan-face list).

---

## Identity

```text
PLAN artifact      docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep2b-20260915.md  (this file; rev1)
PLAN_LOCK_ID       intg-substep2b-plan-20260915 @ sha256 <the artifact's own sha256, carried on the PLAN relay>
DESIGN record      design-doc — the sealed set above; primary lock m1-addendum-M-2966b839-lock-20260825 (post-stamp 57d89625…),
                   consumed locks m3-addendum-6-c41d015f-lock-20260825 (post-stamp 7ce2251d…), m3-addendum-7-4c40fe37-lock-20260827
                   (e4a6b982…), m3-addendum-8 lock d686e39a (b4ed44ce…), m1-addendum-N-82293732-lock-20260827, m1-addendum-O-63c46631-lock-20260901
BASE (B)           origin/main = 186adf7d67171bd7afe621f39b657a1a113ce299 — the R-4.49 landing merge, the PUBLISHED PIN; re-read at Task 0
BRANCH             intg/substep2b-wiring — does not exist yet (no local ref, no remote head); Task 0 cuts it with a FRESH worktree
WORKTREE           /Users/jack/Programming/bivpak-intg-substep2b-wiring
EVIDENCE HOME      $HOME/Programming/bivpak-evidence/s2b-<token>-XXXXXX (durable root; never the OS temp root; never inside a repository)
TOKEN              the pair Planner's bare dispatch token, PARENT = the implementer's exact-hash approve of THIS artifact
VEHICLE            ONE push of intg/substep2b-wiring (class a), ONE PR against main; `main` is NEVER pushed by this plan
LANDING            the operator's bare merge token under .relays/intg from the operator's seat; the census (Task 10) FOR the merge head; R-4.52
CLOSURE            the commission-closure SITREP is the LAST task (Task 11): final pin, FOUR worktrees disposed with receipts, evidence homes sealed
                   and named, open residuals handed to owners by row; no further act routes to the pair without a fresh commission
```

## Global constraints (each line binds every task)

- SEALED TEXT ONLY: where M/N/O, A6/A7/A8/A2-D4, SR-URL and the owner cuts DETERMINE, execute byte-exactly; anything they defer or are silent on is a STOP UP the pair line (m-1 S-2b-1..8; m-3 S-1..S-6; M-R7; A6-R7; A7-R5) — never a keyboard call. A STOP is a SITREP to the pair Planner naming the cell; work continues on every task that does not depend on it.
- VETO 9 MECHANICAL (m-1): in `git log --reverse B..H`, every commit touching `src/core/repo/**` precedes every commit touching `src/cli/**`, `src/core/pack/**`, `src/core/scan/**`, `src/core/open/**`; NO commit touches both sets. This plan has exactly ONE engine commit (Task 1) and it is the first commit above B.
- ENGINE BYTES (V-2b-1): zero in `src/core/repo/**` beyond Task 1's one offline input to `run_eligibility`; any other engine need is a STOP (S-2b-5). FORMAT BYTES (V-2b-2): zero in `src/core/manifest/**`; the C-2 pack hunk (`pack.cpp` "manifest_json" propagation) byte-identical to a2f6fd1's.
- RepoEntry PRODUCTION CENSUS (V-2b-4): zero writes to any RepoEntry field outside `src/core/repo` — pack copies the entries `classify`/`capture` return WHOLE into `manifest.repos`; `CaptureResult.artifacts` are written as members at their `archive_path` VERBATIM (no renaming, no path synthesis). The grep is Task 9's census; a hit is a STOP.
- NON-BYPASS (m-4; S1): no direct git spawn in product code outside `src/core/repo`; every product network path flows through `invoke_git` with exactly ONE carrier endpoint; the hook is installed ONLY through the A6/A7/A8 fabric; consent binds the RAW in-memory value.
- HOOK TRUTH TABLE (A7-R1/R2; R-4.47 V3; RECONCILE R4 I2B-02): `--accept-url-divergence` → the always-proceed hook regardless of TTY state; no flag AND `isatty(stdin) && isatty(stderr)` → the interactive PROMPT D hook; otherwise NO hook (the engine's absent-hook posture refuses, typed). `--json` appears in NO row. `--offline`/`--network` appear in NO row (V-OFF (3)). No environment or config override exists (A7-R1; proposing one is a STOP to master).
- ONE PREDICATE (V-A7-1): `main.cpp:277`'s inline `isatty(STDIN) && isatty(STDERR)` conjunction for PROMPT B is replaced by `biv::cli::interactive_url_hook_installable()`; B's OTHER conditions (`any_sessions`, `!consent_specified`, `!json`) stay exactly as landed; nothing of B's `!json` is copied into D.
- CONSENT SURFACES ARE STDERR-ONLY (A6-R4; m-3 S-4; RECONCILE R4 I2B-03): the accepted notice at FIRST proceed per triple; per-entry refusal lines in ENCOUNTER ORDER; EXACTLY ONE run-level guidance line after the last per-entry line; the human open SUMMARY is SUPPRESSED for all of them; `src/core/open/render.cpp` is NOT in the write set; the writers emit whether or not sessions exist.
- GOLDEN BYTES (V-A6-2, V-A8-4): every A6 template is the landed byte sequence in `url_consent.cpp`; every A2-D4 listing byte and the `UnclaimedGitEntry` detail template come from m-3 130818 §3/§4 VERBATIM (reproduced in Tasks 3/5/6 below); no other user-facing text is authored in this act (R4 positive form: every m-3 surface byte the candidate carries is one the sealed texts or the cut determines).
- A8 INSIDE THE RENDERERS (A8-R1/R2; R-4.48 (ii)): every bound placeholder of the four A8-R2 renderers passes through the consent-render encoder EXACTLY ONCE inside the renderer; callers pass RAW facts; the shared `display()` is byte-unchanged; machine carriers stay RAW (byte-exact for valid UTF-8); `render_run_guidance_line` stays outside the census.
- CONTINGENT TERMS (master 131404 (1)): the `UnclaimedGitEntry` kind's NAME / exit-map ROW / schema enum value / detail TEMPLATE / the two test flips land ONLY after m-3's addendum lock id is on the record (Task 6 Step 0 gate); the narrowed class itself EXISTS and fails closed regardless (Task 6 builds the class behind a typed refusal whose kind literal is the ONE place the lock id unblocks). The offline JSON outcome word is SEALED `offline-pointer` (ADDENDUM-D :78; A2 :110) — build it; m-1 confirms at review, nothing waits.
- SAME-COMMIT RULE (V-A6-3; V-M-INT-3): a commit that lands the new kind lands, in the SAME commit, the `ErrKind` member, `to_string`, the exit-map row (`schemas/biv-exit-map.v1.json`), the `exit_for_error` arm, the `ExpectedRow` list + the literal in `tests/test_envelope.cpp`, the envelope schema enum sites, and the recomputed selftest blob pins (`harness/selftest/test_envelope.py` — NOTE: that file is a `harness/**` byte; see the population rule below).
- HARNESS BYTES: `harness/**` bytes belong to TWO owners' commits only — m-3's harness commit (Task 8, arm-A shape) and the selftest-pin recapture that the same-commit rule forces (which rides INSIDE the kind's product commit, as sub-step 1 did). ANY change to the pytest COLLECTED POPULATION at H (a new scenario's selftest; a new selftest test) fails the rev12 bar's C-2 BY CONSTRUCTION and the `015244` interleaved series (N = 10 per tree) RUNS INSTEAD (m-3 §6, m-4 035001) — Task 9 budgets it; it is not discovered at the gate. `src/adapters/**` bytes: ZERO (adapter-anchor rule; a touch routes UP and re-engages the companion-pin rule). `harness/bivharness/e3.py` pins: untouched.
- COUNT CELLS (I2B-08): the workflow cells count Catch2 CASES (`OverallResultsCases`); Task 9 measures the observed case tuples at H on BOTH platforms against B's literal cells; the companion count-cell commit (Task 9 Step 5) exists ONLY if a tuple moved; an unchanged result is reported as such. No remote CI is triggered by this plan.
- EVIDENCE TIERS (I2B-07): a product-command test against a HAND-BUILT image is E2 evidence of the open verb's bounded behavior, labelled `provenance=hand-built, interim`; the same leg against a `biv pack`-PRODUCED image is the record's leg (`provenance=product-packed`); the packet cites ONLY product-packed receipts for the open side (master 041518's condition). The round trip itself is its own row (R-T in the matrix).
- NO PERSISTENCE (V-A6-1; M veto 5): no approval is written anywhere; a6·13 witnesses it across runs.
- NO NEW ARGV/ENV/CONFIG SURFACE beyond exactly `--offline` (pack + open) and `--network` (open) per m-3 §4 (V-A7-4; V-OFF (5)); `list`/`info` reject them as `unknown-flag` UsageError exactly as today.
- Every commit in the worktree is authored as `intg.pair-implementer`; NO `Co-Authored-By` trailer on any commit; commits stay green on macOS (`ctest --preset ci-macos -E '^safety-hardening$'`); TDD red states live only in the working tree.
- Host worktree `/Users/jack/Programming/bivpak` product paths stay byte-clean; all product work happens in the WORKTREE; the relay daemon is served from the host checkout.
- The GitHub token never enters any container, receipt, or relay; credential VALUES are never read, recorded or echoed (names only); no matched census token is ever printed into a relay or a tracked file (digests only).
- Release hold ABSOLUTE; merge ≠ push ≠ publication ≠ release.

## Boundary contract (protocol form)

```text
Writes (WORKTREE only, branch intg/substep2b-wiring, cut from B):
  ENGINE (Task 1 only, the FIRST commit)   src/core/repo/eligibility.{hpp,cpp}; tests/test_repo_engine.cpp (the 19 call sites gain the mode)
  FABRIC (Task 2)                          src/cli/url_consent.{hpp,cpp}; src/cli/consent_display_table.hpp (GENERATED, checked in);
                                           tools/gen_consent_display_table.py (the generator); tests/test_url_consent.cpp (NEW; biv_tests source list
                                           in CMakeLists.txt gains it)
  CLI (Tasks 3, 4, 5, 6)                   src/cli/args.{hpp,cpp}; src/cli/main.cpp; tests/test_cli.cpp
  OPEN (Task 4)                            src/core/open/open.{hpp,cpp}; src/core/report/envelope.{hpp,cpp} (the open result's repos[] rows +
                                           the offline-pointer rows — contingent term T-JSON); schemas/biv-json-envelope.v1.schema.json (same
                                           commit as the emitting bytes; V-A6-3) + harness/selftest/test_envelope.py pin recapture
  PACK (Tasks 5, 6)                        src/core/pack/pack.{hpp,cpp}; src/core/scan/scan.{hpp,cpp}; tests/test_pack.cpp; tests/test_scan.cpp
  KIND (Task 6, contingent on m-3's lock)  src/core/support/error.{hpp,cpp}; src/core/report/envelope.cpp (exit arm); schemas/biv-exit-map.v1.json;
                                           tests/test_envelope.cpp (ExpectedRow + literal + TC-1..3 folds); harness/selftest/test_envelope.py pins
  HARNESS (Task 8, m-3's commit)           harness/scenarios/** ONLY, authored at m-3's seat, applied verbatim as ONE commit
  COUNT CELLS (Task 9 Step 5, iff moved)   .github/workflows/s2-harness.yml count cells ONLY
  DOCS LANE (host checkout, pair Planner)  docs/sprints/2026-08-27-intg-consent-fabric/** (this plan, receipts of record, census population)
ZERO BYTES:   src/core/repo/** beyond Task 1; src/core/manifest/**; src/adapters/**; harness/bivharness/**; harness/selftest/** beyond the pin
              recapture the same-commit rule forces; src/core/open/render.cpp; every sealed design text; PROMPT A/B/C texts and predicates
              (A6-R6) beyond the V-A7-1 predicate substitution; build_preview / render_prompt_b (R-4.24)
Reads:        the sealed texts and owner fences listed above; the product at B by git object
Target entity: the two product verbs' engine reach (pack: discover → classify → eligibility → capture → repos[] + repos/<id>/… members;
              open: repos/ member class → restore_entry per row) with the consent fabric on every network-class path, both flags, the
              narrowed .git class, and the report carriers
Downstream consumer: m-1's byte review (V-2b-1..9 at H), m-3's byte review (§1 fence at H; the harness commit), m-4's cell-(v) review (E2
              re-derived, E5 re-executed at H), the Master Reviewer's packet, the operator's merge token, the golden harness (m-3 §5)
Contract:     the sealed orderings (pack-engine §1.1/§1.2/§1.3/§2/§4; restore-apply §1/§2.2; A7-R3); the hook truth table; the two refusal
              grains never crossing (V-A6-5); the A8 policy inside the renderers; the D5.2 outcome vocabulary + offline-pointer; the narrowed
              .git class; every FX leg executed or its deferral REGISTERED with a named owner (S-6)
Proof:        the evidence matrix (§Evidence) — every row a receipt in the evidence home, cited by the merge packet
No-consumer action: an engine need beyond Task 1, a RepoEntry ↔ schema mismatch, a network call that cannot flow through invoke_git, a new
              kind/row/wording, a Fence disposition, a persistence or classification proposal → STOP UP (the S-tables); never a local mapping
```

## Commit topology (predeclared; `git log --reverse B..H` MUST read in this order)

```text
c1  engine: run_eligibility gains the offline mode (m-1 S-2b-1 pre-authorized; V-2b-1)          Task 1   src/core/repo/eligibility.*, tests/test_repo_engine.cpp
c2  fabric: A8 consent-render policy inside the four renderers + the generated clause-5 table    Task 2   src/cli/url_consent.*, src/cli/consent_display_table.hpp, tools/, tests/test_url_consent.cpp, CMakeLists.txt
c3  cli: flags (--offline pack/open, --network open, conflict), help lines, hook install,        Task 3   src/cli/args.*, src/cli/main.cpp, tests/test_cli.cpp
         flag read, B-predicate dedup, stderr writers (notice / per-entry lines / guidance)
c4  open: repos/ member class + stage; restore_entry per row (§2.2 order); OpenReport.repos[];  Task 4   src/core/open/*, src/core/report/envelope.*, schemas/biv-json-envelope.v1.schema.json,
         offline-pointer rows; the D4 listing; refusal rows; tests (hand-built images)                    harness/selftest/test_envelope.py (pin), tests/test_cli.cpp, tests/test_envelope.cpp
c5  pack: discover → classify → eligibility (mode) → capture leaves-first → repos[] + members;   Task 5   src/core/pack/*, src/core/scan/*, src/cli/main.cpp (pack refusal detail), tests/test_pack.cpp,
         single-writer exclusion; the narrowed .git class behind a typed refusal                          tests/test_scan.cpp, tests/test_cli.cpp
c6  kind: UnclaimedGitEntry (retire RepoDiscoveredUnsupported) — CONTINGENT on m-3's lock id;    Task 6   src/core/support/error.*, src/core/report/envelope.cpp, schemas/biv-exit-map.v1.json,
         TC-1..3 folds ride the same test_envelope.cpp re-cut                                             tests/test_envelope.cpp, tests/test_pack.cpp, tests/test_scan.cpp, harness/selftest/test_envelope.py (pin)
c7  tests: the re-execution of every open-side leg against product-packed images; FX-M-1 (d)     Task 7   tests/test_cli.cpp (+ fixtures under tests/)
         + (a)-interactive; a6·1–13; a7·1–5; a8·5/a8·6; N (a)/(g); E3 witness — one commit
c8  harness: m-3's ONE harness commit (arm-A shape; authored at m-3's seat; applied verbatim)     Task 8   harness/scenarios/** only
c9  ci: count cells (IFF a case tuple moved at H on either platform)                             Task 9   .github/workflows/s2-harness.yml only
H = the branch head after c9 (or c8 if c9 is not owed). NO commit touches both {src/core/repo} and {src/cli, src/core/pack, src/core/scan, src/core/open}.
```

## Evidence matrix (claim-by-claim; every row = a receipt file in the evidence home; the packet cites rows, never prose)

```text
row    claim / leg                                   where executed                   provenance            tier   verifier of record
E1-M   FX-M-1 (a)–(o) at product scope, both verbs   Task 7 (pack arms) + Task 4/7    product-packed        E2     lane executes; m-4 verifies grep-derived counts; m-1 re-derives the seam fourteen as floor
E1-M-d leg (d) pre-approval + (a)-interactive        Task 7                           product-packed        E2     as above
E1-A6  a6·1–13, a6·16 divergence half               Task 4 (interim) → Task 7        hand-built → product  E2     m-3 §1 (V-A6-*), m-4 counts
E1-A7  a7·1–5 (a7·3 via the split-stream helper)     Task 3 helper; Task 7 legs       product-packed        E2     m-3 (V-A7-*), m-4
E1-A8  a8·1–a8·4 (renderer grain, eleven rows)       Task 2                           unit                  E2     m-3 R-4.48 (iii)
       a8·5 arms A/B1/B2, a8·6 PTY                   Task 7                           product-packed        E2     m-3 R-4.48 (iii)/(iv); m-4 cell (v)
E1-N   FX-N (a) WHOLE + (g) at product scope         Task 7 (request-trace shim)      product-packed        E2     m-1 §2; E4-parity arm = the same receipt
E2     the wiring census: every new product→engine   Task 9 Step 1                    grep at H             E1     lane produces; m-4 RE-DERIVES
       call path per-site file:line through invoke_git, one carrier each
E3     fail-safe witness: divergence + no hook +      Task 7 (macOS) + Task 9 (Linux)  product-packed        E2     lane executes both platforms; m-4 reads receipts, may re-run macOS
       non-interactive ⇒ url_divergence_refused naming BOTH addresses
E4     --offline parity (N (a) row identical with/    Task 7                           product-packed        E2     lands WITH E5 (m-4 rider)
       without the flag; zero git for the entry by request trace)
E5     the unreachability grep FLIPS to exactly E2's  Task 9 Step 1                    grep at H             E1     lane produces; m-4 RE-EXECUTES
R-T    the pack → open round trip (payload byte-      Task 7 (product-packed legs);    product-packed        E2/E3  m-3 §5 (the harness receipt, E3 through the real CLI); m-1 V-2b-8(iv) reads it
       compare; repos restored; manifest rows)        Task 8 (m-3's scenario)
CG     count gate: observed case tuples at H vs B     Task 9                           both platforms        E2     m-3's pin rule
CEN    census FOR the merge head (R-4.49 instrument)  Task 10                          main's post-merge head E2    Master Reviewer; the operator's token
VETO9  git log --reverse order + no-span check        Task 9 Step 2                    H                     E1     m-1
RPC    RepoEntry production census (V-2b-4 grep)      Task 9 Step 2                    H                     E1     m-1
C2H    the C-2 hunk byte-identical to a2f6fd1's       Task 9 Step 2                    H                     E1     m-1 (V-2b-2)
```

## File structure (what each new or modified unit is responsible for)

- `src/core/repo/eligibility.hpp/.cpp` — `run_eligibility(git, entry, EligibilityMode)`; `EligibilityMode::offline` short-circuits every network call (COND-6), forces full + `offline_declared`, and refuses a promisor source through the engine's `promisor_objects_unavailable` class (R-4.1 arm (i) HOLD as m-1 recorded it).
- `src/cli/consent_display_table.hpp` (GENERATED) — the sorted table of scalars in `Cf ∪ Zl ∪ Zp ∪ Default_Ignorable_Code_Point` at Unicode 15.0.0 as `constexpr` `[first,last]` ranges + a header comment carrying the Unicode version, the two input files' sha256 and the generator's sha256. `tools/gen_consent_display_table.py` — the generator (inputs: `UnicodeData.txt`, `DerivedCoreProperties.txt`; deterministic output).
- `src/cli/url_consent.cpp` — gains `consent_display(std::string_view) -> std::string` (clauses 1–4 by calling the landed `biv::open_render::display()` — declared in `core/open/render.hpp` — then the clause-5 pass over the result's scalars) and routes EVERY bound placeholder of the four A8-R2 renderers through it exactly once; templates byte-unchanged.
- `src/cli/args.hpp/.cpp` — `Command.offline`, `Command.network`; parse on the verbs m-3 §4 names; `collision`-style conflict rule → `usage("conflicting-flags")`; open help gains the two lines before `  --accept-url-divergence`.
- `src/cli/main.cpp` — `install_url_divergence_hook(...)`: builds the `UrlDivergenceRun`, the hook per the truth table, the stderr notice writer; wraps the verb's engine-reaching call in `ScopedUrlDivergenceRun`; converts run results into the report carriers; emits per-entry refusal lines + the guidance line (open) and the pack refusal detail (pack); the D4 listing (open `--offline`); B's predicate dedup.
- `src/core/open/open.hpp/.cpp` — `OpenOptions.offline`; the `repos/` member class in `read_archive_plan` (V-2b-7) staged under `<dest-parent>/<name>.bvpk-open.stage/`; `restore_entry` per row in §2.2 order after payload apply, inside the partial dir; `OpenReport.repos` (rows) + the refusal rows; offline: no `restore_entry`, `offline-pointer` rows from the manifest alone.
- `src/core/report/envelope.hpp/.cpp` — `result.repos[]` rows for open (T-JSON) + the D5.2/offline-pointer vocabulary; `UnclaimedGitEntry` exit arm (Task 6); `result.manifest.repos` stays the landed EMPTY array (R4-positive: no sealed text determines a summary row shape there — RECONCILE R4 I2B-09 option (b); registered, not silent).
- `src/core/scan/scan.hpp/.cpp` — `scan(source_root, const ScanExclusions&)`: repo subtrees excluded from the payload walk (V-2b-5); a `.git`-named entry that is a discovered boundary's marker is skipped (never a payload node); a `.git`-named entry NOT claimed → the narrowed typed refusal (V-2b-6; kind per Task 6).
- `src/core/pack/pack.hpp/.cpp` — `PackOptions{offline}`; the sealed order (V-2b-3); leaves-first capture; artifacts as members at `archive_path` verbatim; `manifest.repos` = the entries whole; engine `url_divergence_refused` → `ErrKind::UrlDivergenceRefused` (path = repo; facts requested/effective/op); every other engine issue surfaces through today's engine-error path.
- `tests/test_url_consent.cpp` (NEW, in `biv_tests`) — a8·1–a8·4 on the eleven-row matrix; the table's membership witnesses.
- `tests/test_cli.cpp` — `run_cmd_pty_split` (stdin + stderr on the pty slave; stdout a pipe; all three child descriptor TTY states recorded); the fixture builders (bare "remote" repos + `url.<eff>.insteadOf <req>` rewrites in the repo-local config; born shallow source; promisor source; `.git` symlink); the product-scope legs.
- `tests/fixtures/` — none new on disk; every fixture is built in a temp dir by the test (reality-shaped: real `git init`, real `file://` remotes).

## Contingent terms and open cells (each is a plan TERM with a gate; none is a lane choice)

```text
T-KIND   the UnclaimedGitEntry kind NAME / exit-map ROW / detail TEMPLATE / schema value / the two test flips — WAIT on m-3's addendum
         lock id (master 131404 (1); the A4 precedent). Task 6 Step 0 gate: $RUNNERS/m3-addendum-lock.txt (lock id + doc sha256, carried
         by the pair Planner from m-3's relay). If the lock is not on the record when Task 6 is reached, the candidate HOLDS at c5 — it
         does NOT narrow, and the packet is NOT assembled with the shipped kind carrying the narrowed meaning (m-3 §3 WHY NOT).
T-JSON   the open result's repos[] row shape (D5.2 vocabulary restored | shallow-pointer | payload-only-unborn | failed + the SEALED
         offline-pointer; fields = RepoRestoreRow's members verbatim + the offline-pointer fields relpath/branch/sha/remotes[]/bundle_path)
         is built as m-3 §4 JSON states ("the same rows under the OpenReport repos[]") with the outcome word master sealed; its envelope
         SCHEMA declaration is an m-3 surface byte — Q9 asks m-3 to confirm the member name `repos` and the field set BEFORE c4 is
         committed (Task 4 Step 0 gate: $RUNNERS/m3-json-shape.txt, or the pair Planner's SITREP naming m-3's word). Until then Task 4's
         code steps proceed on the shape below; the commit waits.
T-HELP   m-3 §4 HELP places "  --offline" and "  --network" immediately BEFORE "  --accept-url-divergence"; A6-R9 (a6·18) pins the accept
         line DIRECTLY AFTER "  --consent". Both are m-3's; they conflict at one byte position. Q12 asks m-3 which order the golden help
         carries; Task 3 Step 0 gate: $RUNNERS/m3-help-order.txt. Task 3's other steps proceed; the help golden re-pin waits.
T-STAGE  the on-disk location of the extracted bundle artifacts under `biv open --offline` (A2 D4: "extracts the bundle artifacts and
         PRINTS the git clone <bundle-path>") is not determined by sealed text; ADDENDUM-I reserves exactly <workspace>/.biv/. Q13 asks
         m-1 + m-3; the plan's default is <dest>/.biv/repos/<id>/<artifact-name> and the printed <bundle-path> is that absolute path;
         Task 4 Step 0 gate: $RUNNERS/offline-stage.txt.
T-FENCE  a Classification whose fence != none at pack: the engine sets Fence + a typed EngineIssue and produces NO cell (N). Its
         PRODUCT-SCOPE disposition (whole-operation typed refusal vs per-repo note vs forced full) is m-1's word — Q11. Task 5 Step 0
         records each of the four fence sites' trigger conditions (classify.cpp:134/146/179/354) and STOPs to m-1 if any fence fires on
         an ordinary born, non-shallow dirty repo; default until the word: a fenced classification surfaces the EngineIssue as today's
         engine error (whole-operation, typed by its repo_engine_kind fact).
T-PROM   `biv pack --offline` on a promisor source: the engine's promisor_objects_unavailable class refuses (m-1 S-2b-1). R-4.1 names
         `PromisorSourceOffline(repo)` as a kind; no such ErrKind exists. Q10 asks m-3 (S-2b-6 class) whether a typed kind is owed at 2b;
         default: the engine class surfaces through today's engine-error path (kind literal unchanged), registered — never silent.
T-NET    `--network` on open: m-3 §4 cuts parse + conflict + help; A2 D3's network-consent semantics name a prompt no sealed text in this
         act's set defines. Default: parse-only (inert beyond the conflict rule), registered as a residual row with m-3 as owner unless
         m-3's answer to Q8 says otherwise.
T-K      FX-M-1 leg (k) (carrier fail-closed) has no product input that constructs an invocation; it stays at the engine seam as the
         floor and E2's census (every product path carries exactly one endpoint) is its product-scope form — REGISTERED under S-6 with
         m-1 as owner, never silent.
T-C      a6·10 (flag ≠ PROMPT C) executes only if PROMPT C (memory merge) exists at B; Task 7 Step 0 greps for it; absent → REGISTERED
         under S-6 (m-3), never silent.
```

## Per-task runner protocol (measurement tasks) and the code-task discipline

Tasks 0, 9, 10 and 11 are MEASUREMENT tasks: each has exactly one `<!-- RUN: task-N -->` block below its steps and is entered ONLY through the runner protocol of `PL-intg-r449-line1-selection-20260913.md` (its BLOCKs `plan_blocks.py` and `run-task.sh` are reproduced VERBATIM in §Instruments below and are extracted from THIS plan): `run-task.sh N` re-hashes the plan against `plan-lock.txt`, materializes `task-N.sh` from the plan's own bytes, proves it (`plan_blocks.py check … rc=0`), `chmod 0500`s it, records its sha256 and invocation, and runs it exactly once; every gate span in the prose is a runner line; every count comes from a file; no evidence-producing pipeline anywhere (`set -o pipefail` + per-stage `PIPESTATUS` where a pipe is unavoidable); a `STOP` prints its line number and exits 1.

Tasks 1–8 are CODE tasks executed by the implementer as TDD steps in the WORKTREE: each step's command is run as written, its stdout+stderr+rc appended to `$EVID/code/task-N.log` (one `printf '### step %s rc=%s\n'` line per command), the commit sha of each task recorded in `$EVID/commits.txt` (`cN=<sha>`). A code task ends with `ctest --preset ci-macos -E '^safety-hardening$'` rc 0 and `git status --porcelain` EMPTY in the worktree.

## Tasks

### Task 0 — bootstrap: evidence home; helpers; B resolved; the THREE retained pair worktrees DISPOSED with receipts; the FRESH branch + worktree from B; venv + build; B observed on macOS

**Files:** none in the product tree (worktree operations, the evidence home, the build).

- [ ] **Step 0: the evidence home** — token id from `$RUNNERS/token-id.txt`; `mktemp -d "$HOME/Programming/bivpak-evidence/s2b-${TOKEN}-XXXXXX"` resolved with `pwd -P`; not the OS temp root; not inside a repository; subdirs `runners B H work census-raw code legs receipts`; `evid.txt` / `runners-dir.txt` cross-pointers; the runner artifacts copied in; `status-initial.txt` of the host checkout (product paths).
- [ ] **Step 0b: helpers materialized** — every python BLOCK extracted and `py_compile`d; every shell BLOCK extracted and `bash -n`'d; `helpers.sha256` written; `blocks.txt` == `$RUNNERS/blocks.txt`.
- [ ] **Step 1: B resolved and recorded** — `git fetch --no-tags origin refs/heads/main:refs/remotes/origin/main`; `origin/main` MUST equal `186adf7d67171bd7afe621f39b657a1a113ce299` or STOP; the workflow bytes at B → `cells.py` → `B-cells.txt`; `B.txt`.
- [ ] **Step 2: the three retained pair worktrees DISPOSED (master 041518 Q5/Q6)** — for each of `../bivpak-intg-consent-fabric` @ `3cd31e4823d40c1c9ea020fcb51917618368533b` on `intg/consent-fabric`, `../bivpak-intg-format-act` @ `a2f6fd1adf67fd86c8d0c692db34f113a9691135` on `intg/format-act`, `../bivpak-intg-r449-line1-selection` @ `b74ec570e22646bfee6a0c554bcb766fffa6da19` on `intg/r449-line1-selection`: preconditions (path exists; HEAD == the pin; branch == the name; `status --porcelain` EMPTY) → the branch ref recorded BEFORE → `git worktree remove <path>` → the path absent → the branch ref UNCHANGED after → `git worktree list` no longer names the path → one receipt line per worktree in `$EVID/receipts/worktree-disposed-<n>.txt` (`disposed=<path> head_was=<sha> branch_was=<name> remove_rc=0 refs_unchanged=yes`). Branches stay; no other worktree is touched; no remote ref is touched.
- [ ] **Step 3: the FRESH branch and worktree from B** — no local ref `intg/substep2b-wiring`; no remote head of that name (`git ls-remote --heads origin intg/substep2b-wiring` EMPTY); the worktree path absent; `git worktree add -b intg/substep2b-wiring /Users/jack/Programming/bivpak-intg-substep2b-wiring 186adf7d…`; HEAD == B; status EMPTY; `git rev-list --count origin/main..HEAD` == 0 (`cutpoint.txt`); `.venv-harness/` and `build/` git-ignored (proof recorded).
- [ ] **Step 4: venv + build at B** — python3.12 venv from `harness/requirements.lock`; import proof (`pytest jsonschema zstandard`); `cmake --preset ci-macos` (the `BIVHARNESS_PYTHON` cache line exactly once); `cmake --build --preset ci-macos`; `build/ci-macos/biv` executable; status EMPTY.
- [ ] **Step 5: B observed on macOS** — the five test binaries `-r xml` → `B/*-macos.xml` → `tuples.py` → `B/tuples-macos.txt`; `skipset.py` against `B-cells.txt`; status EMPTY after.
- [ ] **Step 6: the Unicode inputs** — `curl -fsSL` `https://www.unicode.org/Public/15.0.0/ucd/UnicodeData.txt` and `https://www.unicode.org/Public/15.0.0/ucd/DerivedCoreProperties.txt` into `$EVID/work/ucd/`; `DerivedCoreProperties.txt` line 1 MUST match `^# DerivedCoreProperties-15\.0\.0\.txt$` or STOP (m-3 S-2 — a version drift is a design act at m-3's seat); `UnicodeData.txt` MUST carry exactly 15 `;`-separated fields on its first line (`awk -F';' 'NR==1{print NF}'` == 15) or STOP; both files' sha256 → `$EVID/receipts/ucd-inputs.sha256` (these digests are copied into the generated header by Task 2).

<!-- RUN: task-0 -->
```bash
# Runner plumbing (Task 0)
WORKTREE=/Users/jack/Programming/bivpak-intg-substep2b-wiring
MAIN=/Users/jack/Programming/bivpak
B=186adf7d67171bd7afe621f39b657a1a113ce299
PLAN=$(cat "$RUNNERS/plan-path.txt") || STOP; [ -s "$PLAN" ] || STOP
cd "$MAIN" || STOP
# Step 0
TOKEN=$(cat "$RUNNERS/token-id.txt") || STOP; [ -n "$TOKEN" ] || STOP
m=0; mkdir -p "$HOME/Programming/bivpak-evidence" || m=$?; [ "$m" -eq 0 ] && [ -d "$HOME/Programming/bivpak-evidence" ] || STOP
EVID_RAW=$(mktemp -d "$HOME/Programming/bivpak-evidence/s2b-${TOKEN}-XXXXXX") || STOP
EVID=$(cd "$EVID_RAW" && pwd -P) || STOP
[ -d "$EVID" ] && [ "$EVID" = "$EVID_RAW" ] || STOP
case "$EVID/" in /var/folders/*|/private/var/folders/*|/tmp/*|/private/tmp/*) echo STOP-evid-in-temp-root; exit 1;; esac
case "$EVID/" in "$(git rev-parse --show-toplevel)/"*) echo STOP-evid-inside-repo; exit 1;; esac
m=0; mkdir "$EVID/runners" "$EVID/B" "$EVID/H" "$EVID/work" "$EVID/census-raw" "$EVID/code" "$EVID/legs" "$EVID/receipts" "$EVID/work/ucd" || m=$?; [ "$m" -eq 0 ] && [ -d "$EVID/runners" ] && [ -d "$EVID/receipts" ] || STOP
w=0; printf '%s\n' "$EVID" > "$RUNNERS/evid.txt" || w=$?; [ "$w" -eq 0 ] && [ -s "$RUNNERS/evid.txt" ] || STOP; w=0; printf '%s\n' "$RUNNERS" > "$EVID/runners-dir.txt" || w=$?; [ "$w" -eq 0 ] && [ -s "$EVID/runners-dir.txt" ] || STOP
c=0; cp -p "$RUNNERS/task-0.sh" "$RUNNERS/proof-0.txt" "$RUNNERS/task-0.sha256" "$RUNNERS/task-0.invocation.txt" "$RUNNERS/plan_blocks.py" "$RUNNERS/run-task.sh" "$RUNNERS/run-task.sha256" "$RUNNERS/blocks.txt" "$RUNNERS/plan-lock.txt" "$RUNNERS/plan-path.txt" "$RUNNERS/token-id.txt" "$EVID/runners/" || c=$?; [ "$c" -eq 0 ] || STOP
w=0; printf 'token=%s\nevid=%s\n' "$TOKEN" "$EVID" > "$EVID/token.txt" || w=$?; [ "$w" -eq 0 ] && [ -s "$EVID/token.txt" ] || STOP
s0=0; git -C "$MAIN" status --porcelain -- src tests harness schemas .github CMakeLists.txt > "$EVID/status-initial.txt" || s0=$?; [ "$s0" -eq 0 ] && [ ! -s "$EVID/status-initial.txt" ] || STOP
# Step 0b
for name in cells tuples cellgate skipset selftest_summary finalize gen_consent_display_table series_verdict; do x=0; python3 "$RUNNERS/plan_blocks.py" extract "$PLAN" "$name.py" > "$EVID/$name.py" || x=$?; [ "$x" -eq 0 ] && [ -s "$EVID/$name.py" ] || STOP; p=0; python3 -m py_compile "$EVID/$name.py" || p=$?; [ "$p" -eq 0 ] || STOP; done
for name in linux-container.sh linux-suite.sh git-shim.sh; do x=0; python3 "$RUNNERS/plan_blocks.py" extract "$PLAN" "$name" > "$EVID/$name" || x=$?; [ "$x" -eq 0 ] && [ -s "$EVID/$name" ] || STOP; s=0; bash -n "$EVID/$name" || s=$?; [ "$s" -eq 0 ] || STOP; done
h=0; (cd "$EVID" && shasum -a 256 cells.py tuples.py cellgate.py skipset.py selftest_summary.py finalize.py gen_consent_display_table.py series_verdict.py linux-container.sh linux-suite.sh git-shim.sh > helpers.sha256) || h=$?; [ "$h" -eq 0 ] && [ -s "$EVID/helpers.sha256" ] || STOP
x=0; python3 "$RUNNERS/plan_blocks.py" list "$PLAN" > "$EVID/blocks.txt" || x=$?; [ "$x" -eq 0 ] && [ -s "$EVID/blocks.txt" ] || STOP; c=0; cmp "$EVID/blocks.txt" "$RUNNERS/blocks.txt" || c=$?; [ "$c" -eq 0 ] || STOP
# Step 1
f=0; git -C "$MAIN" fetch --no-tags origin refs/heads/main:refs/remotes/origin/main || f=$?; [ "$f" -eq 0 ] || STOP
BASE=$(git -C "$MAIN" rev-parse origin/main) || STOP; [ "$BASE" = "$B" ] || STOP
w=0; git -C "$MAIN" show "${B}:.github/workflows/s2-harness.yml" > "$EVID/B-workflow.yml" || w=$?; [ "$w" -eq 0 ] && [ -s "$EVID/B-workflow.yml" ] || STOP
c=0; python3 "$EVID/cells.py" "$EVID/B-workflow.yml" > "$EVID/B-cells.txt" || c=$?; printf 'cells_B_rc=%s\n' "$c" > "$EVID/B-cells.rc"; [ "$c" -eq 0 ] && [ -s "$EVID/B-cells.txt" ] || STOP
printf 'B=%s\n' "$BASE" > "$EVID/B.txt"
# Step 2 — three disposals, one receipt each
n=0
for spec in "/Users/jack/Programming/bivpak-intg-consent-fabric|3cd31e4823d40c1c9ea020fcb51917618368533b|intg/consent-fabric" "/Users/jack/Programming/bivpak-intg-format-act|a2f6fd1adf67fd86c8d0c692db34f113a9691135|intg/format-act" "/Users/jack/Programming/bivpak-intg-r449-line1-selection|b74ec570e22646bfee6a0c554bcb766fffa6da19|intg/r449-line1-selection"; do
  n=$((n+1)); WT=${spec%%|*}; rest=${spec#*|}; SHA=${rest%%|*}; BR=${rest#*|}
  [ -d "$WT" ] || STOP; [ "$(git -C "$WT" rev-parse HEAD)" = "$SHA" ] || STOP; [ "$(git -C "$WT" rev-parse --abbrev-ref HEAD)" = "$BR" ] || STOP
  s=0; git -C "$WT" status --porcelain > "$EVID/receipts/wt-$n-status.txt" || s=$?; [ "$s" -eq 0 ] && [ ! -s "$EVID/receipts/wt-$n-status.txt" ] || STOP
  REF_BEFORE=$(git -C "$MAIN" rev-parse "refs/heads/$BR") || STOP; [ "$REF_BEFORE" = "$SHA" ] || STOP
  w=0; git -C "$MAIN" worktree remove "$WT" > "$EVID/receipts/wt-$n-remove.log" 2>&1 || w=$?; [ "$w" -eq 0 ] && [ ! -e "$WT" ] || STOP
  REF_AFTER=$(git -C "$MAIN" rev-parse "refs/heads/$BR") || STOP; [ "$REF_AFTER" = "$SHA" ] || STOP
  l=0; git -C "$MAIN" worktree list > "$EVID/receipts/wt-$n-list-after.txt" || l=$?; [ "$l" -eq 0 ] || STOP; g=0; k=$(grep -c -F -- "$WT" "$EVID/receipts/wt-$n-list-after.txt") || g=$?; [ "$g" -eq 1 ] && [ "$k" -eq 0 ] || STOP
  w=0; printf 'disposed=%s head_was=%s branch_was=%s remove_rc=0 refs_unchanged=yes\n' "$WT" "$SHA" "$BR" > "$EVID/receipts/worktree-disposed-$n.txt" || w=$?; [ "$w" -eq 0 ] && [ -s "$EVID/receipts/worktree-disposed-$n.txt" ] || STOP
done
[ "$n" -eq 3 ] || STOP
# Step 3
e=0; git -C "$MAIN" show-ref --verify -q refs/heads/intg/substep2b-wiring || e=$?; [ "$e" -ne 0 ] || STOP
l=0; git -C "$MAIN" ls-remote --heads origin intg/substep2b-wiring > "$EVID/remote-branch-initial.txt" || l=$?; [ "$l" -eq 0 ] && [ ! -s "$EVID/remote-branch-initial.txt" ] || STOP
[ ! -e "$WORKTREE" ] || STOP
a=0; git -C "$MAIN" worktree add -b intg/substep2b-wiring "$WORKTREE" "$B" > "$EVID/worktree-add.log" 2>&1 || a=$?; [ "$a" -eq 0 ] && [ -d "$WORKTREE" ] || STOP
cd "$WORKTREE" || STOP
[ "$(git rev-parse HEAD)" = "$B" ] && [ "$(git rev-parse --abbrev-ref HEAD)" = intg/substep2b-wiring ] || STOP
s=0; git status --porcelain > "$EVID/status-worktree-0.txt" || s=$?; [ "$s" -eq 0 ] && [ ! -s "$EVID/status-worktree-0.txt" ] || STOP
c=0; n=$(git rev-list --count origin/main..HEAD) || c=$?; [ "$c" -eq 0 ] && [ "$n" -eq 0 ] || STOP; w=0; printf 'unpublished_commits_in_lineage=%s expected=0 cut_point=%s\n' "$n" "$B" > "$EVID/cutpoint.txt" || w=$?; [ "$w" -eq 0 ] || STOP
g=0; git check-ignore -q .venv-harness/ || g=$?; g2=0; git check-ignore -q build/ || g2=$?; printf 'venv_ignored_rc=%s build_ignored_rc=%s\n' "$g" "$g2" > "$EVID/ignore-proof.txt"; [ "$g" -eq 0 ] && [ "$g2" -eq 0 ] || STOP
# Step 4
v=0; /opt/homebrew/bin/python3.12 -m venv .venv-harness || v=$?; [ "$v" -eq 0 ] && [ -x .venv-harness/bin/python ] || STOP; i=0; .venv-harness/bin/python -m pip install -q -r harness/requirements.lock || i=$?; [ "$i" -eq 0 ] || STOP
m=0; .venv-harness/bin/python -c 'import pytest, jsonschema, zstandard; print("imported", pytest.__name__, jsonschema.__name__, zstandard.__name__)' > "$EVID/venv-imports.txt" 2>&1 || m=$?; [ "$m" -eq 0 ] || STOP
s=0; git status --porcelain > "$EVID/status-post-venv.txt" || s=$?; [ "$s" -eq 0 ] && [ ! -s "$EVID/status-post-venv.txt" ] || STOP
b=0; cmake --preset ci-macos > "$EVID/B/configure-B.log" 2>&1 || b=$?; [ "$b" -eq 0 ] || STOP
g=0; k=$(grep -c -E '^BIVHARNESS_PYTHON:FILEPATH=.*/\.venv-harness/bin/python3$' build/ci-macos/CMakeCache.txt) || g=$?; [ "$g" -le 1 ] && [ "$k" -eq 1 ] || STOP
b=0; cmake --build --preset ci-macos > "$EVID/B/build-B.log" 2>&1 || b=$?; [ "$b" -eq 0 ] && [ -x build/ci-macos/biv ] || STOP
# Step 5
for binary in biv_subprocess_tests biv_repo_git_tests biv_repo_engine_tests biv_tests biv_probe_tests; do x=0; "./build/ci-macos/$binary" -r xml > "$EVID/B/$binary-macos.xml" 2> "$EVID/B/$binary-macos.stderr" || x=$?; printf '%s rc=%s\n' "$binary" "$x" >> "$EVID/B/run-rcs-macos.txt"; [ -s "$EVID/B/$binary-macos.xml" ] || STOP; done
u=0; python3 "$EVID/tuples.py" macos "$EVID"/B/biv_subprocess_tests-macos.xml "$EVID"/B/biv_repo_git_tests-macos.xml "$EVID"/B/biv_repo_engine_tests-macos.xml "$EVID"/B/biv_tests-macos.xml "$EVID"/B/biv_probe_tests-macos.xml > "$EVID/B/tuples-macos.txt" || u=$?; [ "$u" -eq 0 ] && [ -s "$EVID/B/tuples-macos.txt" ] || STOP
q=0; python3 "$EVID/skipset.py" "$EVID/B-cells.txt" "$EVID/B/tuples-macos.txt" macos > "$EVID/B/skipset-macos.txt" || q=$?; [ "$q" -eq 0 ] && [ -s "$EVID/B/skipset-macos.txt" ] || STOP
s=0; git status --porcelain > "$EVID/status-post-B.txt" || s=$?; [ "$s" -eq 0 ] && [ ! -s "$EVID/status-post-B.txt" ] || STOP
# Step 5b — the observer names (the harness credential env NAMES, values never read) and the pinned clang-tidy mirror manifest (workflow bytes at B)
n=0; (cd harness && ../.venv-harness/bin/python -c 'from bivharness.e3 import CREDENTIAL_ENV_NAMES as n; print("\n".join(n))') > "$EVID/observer-unset-names.txt" || n=$?; [ "$n" -eq 0 ] && [ -s "$EVID/observer-unset-names.txt" ] || STOP
g=0; k=$(grep -c -E '^[A-Z][A-Z0-9_]+$' "$EVID/observer-unset-names.txt") || g=$?; [ "$g" -eq 0 ] && [ "$k" -ge 1 ] || STOP
s=0; sed -n '167,174p' "$EVID/B-workflow.yml" > "$EVID/llvm-manifest-source.txt" || s=$?; [ "$s" -eq 0 ] && [ -s "$EVID/llvm-manifest-source.txt" ] || STOP; s=0; sed 's/^          //' "$EVID/llvm-manifest-source.txt" > "$EVID/llvm-manifest.txt" || s=$?; [ "$s" -eq 0 ] || STOP; a=0; nl=$(awk 'END { print NR }' "$EVID/llvm-manifest.txt") || a=$?; [ "$a" -eq 0 ] && [ "$nl" -eq 8 ] || STOP; g=0; k=$(grep -c -E '^[0-9a-f]{64} [a-z0-9-]+ [A-Za-z0-9._+-]+\.deb$' "$EVID/llvm-manifest.txt") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 8 ] || STOP
# Step 6 — the Unicode 15.0.0 inputs (m-3 §2; S-2)
for f in UnicodeData.txt DerivedCoreProperties.txt; do c=0; curl -fsSL "https://www.unicode.org/Public/15.0.0/ucd/$f" -o "$EVID/work/ucd/$f" || c=$?; [ "$c" -eq 0 ] && [ -s "$EVID/work/ucd/$f" ] || { echo STOP-S-2-ucd-unobtainable; exit 1; }; done
g=0; k=$(sed -n '1p' "$EVID/work/ucd/DerivedCoreProperties.txt" | grep -c -E '^# DerivedCoreProperties-15\.0\.0\.txt$') || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || { echo STOP-S-2-ucd-version; exit 1; }
nf=$(awk -F';' 'NR==1{print NF}' "$EVID/work/ucd/UnicodeData.txt") || STOP; [ "$nf" -eq 15 ] || { echo STOP-S-2-ucd-shape; exit 1; }
h=0; (cd "$EVID/work/ucd" && shasum -a 256 UnicodeData.txt DerivedCoreProperties.txt > "$EVID/receipts/ucd-inputs.sha256") || h=$?; [ "$h" -eq 0 ] && [ -s "$EVID/receipts/ucd-inputs.sha256" ] || STOP
exit 0
```

### Task 1 — c1, the ONE engine commit: `run_eligibility` gains the offline mode (m-1 S-2b-1, pre-authorized execution; V-2b-1)

**Files:** Modify `src/core/repo/eligibility.hpp`, `src/core/repo/eligibility.cpp`; Modify `tests/test_repo_engine.cpp` (the 19 existing `run_eligibility(` call sites gain `EligibilityMode::network`; two new cases).
**Interfaces:** Produces `enum class EligibilityMode { network, offline };` and `expected<void> run_eligibility(const Git& git, RepoEntry& entry, EligibilityMode mode);` — no default argument (every caller states its mode; Task 5 passes the pack flag). Consumes nothing new.
**Sealed content (pack-engine §2 COND-6; m-1 S-2b-1):** offline ⇒ no `ls-remote`, no refresh fetch; every repo `capture_mode: full`, `eligibility.result: offline_declared` (wire string already at `manifest.cpp:804`); a promisor source that cannot complete its objects REFUSES through `EngineErrorKind::promisor_objects_unavailable` (R-4.1 arm (i) HOLD). The unborn/shallow early return at the top of `run_eligibility` stays FIRST (N: the structural returns precede the probe; a shallow entry carries no eligibility cell).

- [ ] **Step 1: the failing tests** — in `tests/test_repo_engine.cpp`, two cases using the existing `fake_network_git(...)` helper with a request trace:

```cpp
TEST_CASE("run_eligibility offline: zero network calls, offline_declared, full") {
  // arrange: a born entry with one remote, exactly as the existing proven-remote case builds it
  std::vector<biv::support::SpawnRequest> spawned;
  auto git = fake_network_git(root.path(), /*…as the sibling case…*/, [&](const biv::support::SpawnRequest& r) { spawned.push_back(r); });
  auto result = biv::repo::run_eligibility(git, entry, biv::repo::EligibilityMode::offline);
  REQUIRE(result.has_value());
  CHECK(entry.capture_mode == biv::repo::CaptureMode::full);
  REQUIRE(entry.eligibility.has_value());
  CHECK(entry.eligibility->result == biv::repo::EligibilityResult::offline_declared);
  CHECK_FALSE(entry.eligibility->proof.has_value());
  CHECK(spawned.empty());  // NAMED MUTANT: an offline path that still advertises ⇒ RED here
}
TEST_CASE("run_eligibility offline on a promisor source refuses typed") {
  entry.promisor = true;
  auto result = biv::repo::run_eligibility(git, entry, biv::repo::EligibilityMode::offline);
  REQUIRE_FALSE(result.has_value());
  CHECK(biv::repo::engine_error_kind(result.error()) == biv::repo::EngineErrorKind::promisor_objects_unavailable);  // use the existing facts accessor at types.hpp:93
  CHECK(spawned.empty());
}
```

  Every existing call `run_eligibility(git, entry)` in the file becomes `run_eligibility(git, entry, biv::repo::EligibilityMode::network)` (19 sites; `grep -c 'run_eligibility(' tests/test_repo_engine.cpp` must read 21 after the edit).
- [ ] **Step 2: run to verify failure** — `cmake --build --preset ci-macos` FAILS to compile (the enum and the third parameter do not exist). Expected: compile error naming `EligibilityMode`.
- [ ] **Step 3: the implementation** — `eligibility.hpp`:

```cpp
enum class EligibilityMode { network, offline };
expected<void> run_eligibility(const Git& git, RepoEntry& entry, EligibilityMode mode);
```

  `eligibility.cpp`, inside `run_eligibility` AFTER the unborn/shallow early return and the HEAD-object check, BEFORE the remotes loop:

```cpp
  if (mode == EligibilityMode::offline) {
    if (entry.promisor) {
      return std::unexpected(make_engine_error(
          EngineErrorKind::promisor_objects_unavailable, entry.relpath,
          "offline pack of a promisor source cannot complete its objects"));
    }
    eligibility.result = EligibilityResult::offline_declared;
    force_full(entry, std::move(eligibility));
    return {};
  }
```

  (`eligibility` is the local `Eligibility{.method = "ls-remote-ancestry", …}` already constructed above the remotes check; the `method` literal is NOT changed by this act — if m-1's review wants a distinct offline method string that is m-1's word, S-2b-3 class.) No other line of `src/core/repo/**` moves.
- [ ] **Step 4: run to verify pass** — `cmake --build --preset ci-macos && ./build/ci-macos/biv_repo_engine_tests` rc 0; `ctest --preset ci-macos -E '^safety-hardening$'` rc 0.
- [ ] **Step 5: the veto-9 shape check, then commit** — `git status --porcelain` names exactly `src/core/repo/eligibility.hpp`, `src/core/repo/eligibility.cpp`, `tests/test_repo_engine.cpp`; `git diff --stat -- src/cli src/core/pack src/core/scan src/core/open src/core/manifest` EMPTY.

```bash
git add src/core/repo/eligibility.hpp src/core/repo/eligibility.cpp tests/test_repo_engine.cpp
git commit -m "repo: run_eligibility gains EligibilityMode (offline: no network, offline_declared + full; promisor source refuses typed) -- m-1 S-2b-1 pre-authorized engine input, first in history"
git rev-parse HEAD > "$EVID/commits.c1.txt"
```

### Task 2 — c2, the fabric: the A8 consent-render policy INSIDE the four renderers + the generated clause-5 table (A8-R1/R2; R-4.48 (ii)/(iii); m-3 §2)

**Files:** Create `tools/gen_consent_display_table.py` (BLOCK `gen_consent_display_table.py`, copied verbatim from §Instruments), Create `src/cli/consent_display_table.hpp` (GENERATED), Modify `src/cli/url_consent.hpp`, `src/cli/url_consent.cpp`, Create `tests/test_url_consent.cpp`, Modify `CMakeLists.txt` (the `biv_tests` source list gains `tests/test_url_consent.cpp`; the `biv` and `biv_tests` targets already compile `src/cli/url_consent.cpp` — verify `biv_tests` links it, else add it to the list).
**Interfaces:** Produces `std::string consent_display(std::string_view raw);` (public in `url_consent.hpp`) and `bool consent_display_active(char32_t scalar);` (table membership); the four renderers' signatures UNCHANGED; `render_run_guidance_line` UNCHANGED and outside the census. Consumes `biv::support::sanitize_utf8` (landed).
**Sealed content:** A8-R1 clauses 1–5 composed at the renderer boundary; clause 5 = `General_Category ∈ {Cf, Zl, Zp} ∪ Default_Ignorable_Code_Point` at Unicode 15.0.0 rendered as lowercase braced minimal-hex `\u{…}`; clause 4 = residual pass-through; the shared `display()` in `render.cpp` is NOT edited; the eleven-row matrix with exact renders (A8 FX table; m-3 §1 R-4.48 (iii)).

- [ ] **Step 0: generate the table** — `python3 "$EVID/gen_consent_display_table.py" "$EVID/work/ucd/UnicodeData.txt" "$EVID/work/ucd/DerivedCoreProperties.txt" "$EVID/receipts/ucd-inputs.sha256" > src/cli/consent_display_table.hpp`; the header's comment block MUST carry `Unicode 15.0.0`, both input sha256 lines and the generator's own sha256 (the script computes it over its own bytes); `cp "$EVID/gen_consent_display_table.py" tools/gen_consent_display_table.py`; re-run the generator from `tools/` and `cmp` the two outputs (determinism proof). Membership spot checks recorded to `$EVID/code/table-spot.txt`: U+202E, U+200B, U+2028, U+2029, U+FE0F, U+034F, U+00AD, U+200D IN; U+0041, U+00E9, U+4E2D, U+1F600 OUT.
- [ ] **Step 1: the failing tests (a8·1–a8·4 on all ELEVEN rows)** — `tests/test_url_consent.cpp`:

```cpp
struct MatrixRow { std::string input; std::string expected; };
const std::vector<MatrixRow> kMatrix{
  {std::string{"\x0d"}, "\\r"}, {std::string{"\x0a"}, "\\n"}, {std::string{"\x1b"}, "\\u001b"}, {std::string{"\x7f"}, "\\u007f"},
  {std::string{"\xc2\x9b"}, "\\u009b"}, {std::string{"\x9b"}, "\xef\xbf\xbd"} /* one U+FFFD */,
  {std::string{"\xe2\x80\xae"}, "\\u{202e}"}, {std::string{"\xe2\x80\x8b"}, "\\u{200b}"}, {std::string{"\xe2\x80\xa8"}, "\\u{2028}"},
  {std::string{"\xef\xb8\x8f"}, "\\u{fe0f}"}, {std::string{"\xcd\x8f"}, "\\u{34f}"}};
TEST_CASE("a8-1 prompt-d hostile bytes: exact escapes, zero raw control bytes, template literals intact") {
  for (const auto& row : kMatrix) for (int slot = 0; slot < 4; ++slot) {
    biv::cli::UrlDivergenceFacts f{.op = "clone", .repo = "r", .requested = "https://req.invalid/x.git", .effective = "https://eff.invalid/x.git"};
    (slot == 0 ? f.requested : slot == 1 ? f.effective : slot == 2 ? f.repo : f.op) += row.input;
    const auto out = biv::cli::render_prompt_d(f);
    INFO(slot); CHECK(out.find(row.expected) != std::string::npos);
    CHECK(no_raw_control_or_format_scalar(out));          // helper: decodes UTF-8; fails on C0/DEL/C1 raw or any table member raw
    CHECK(out.find(": the address git will contact for ") != std::string::npos);  // literal intact
    CHECK(out.find("  Contact the effective address? [y/N] ") != std::string::npos);
  }
}
// a8-2 the same over render_accepted_notice; a8-3 render_pack_refusal_detail (the single returned string IS both carriers — identity by
// construction here; Task 7 asserts error.detail == the stream segment at product scope); a8-4 render_entry_refusal_line with the matrix in
// relpath AND effective. Each case asserts the exact expected render, zero raw control/format scalars, and the template literal around it.
TEST_CASE("consent_display clauses 1-4 agree with the landed policy on control rows") { /* \r \n \t; C0/DEL/C1 -> \u00xx lowercase; invalid -> U+FFFD */ }
TEST_CASE("consent_display clause 5 membership: display-active in, ordinary scalars out") { /* the spot list of Step 0, from the table */ }
```

  Named mutants each case kills: raw pass-through of any row (a8·1); U+202E reaching output raw (clause-5 witness); U+FE0F (Mn, Default_Ignorable) passing a Cf-only class (class-boundary witness); an encoded prompt but raw notice (a8·2); the two carriers diverging (a8·3, at Task 7); relpath exempted (a8·4).
- [ ] **Step 2: run to verify failure** — `cmake --build --preset ci-macos && ./build/ci-macos/biv_tests '[a8]'` — FAILS: `consent_display` undeclared / the renderers return raw bytes.
- [ ] **Step 3: the implementation** — `url_consent.cpp`:

```cpp
#include "cli/consent_display_table.hpp"   // generated: constexpr std::array<Range, N> kConsentDisplayActive; bool consent_display_active(char32_t)
#include "core/support/probe.hpp"          // sanitize_utf8 (the landed sanitizer used by display())
namespace {
struct Scalar { char32_t value; std::size_t width; };
Scalar decode_scalar(std::string_view s, std::size_t at);           // valid UTF-8 only (post-sanitize); width 1..4
void append_u00(std::string& out, char32_t v);                      // "\\u00" + two lowercase hex digits
void append_braced(std::string& out, char32_t v);                   // "\\u{" + minimal lowercase hex + "}"
}  // namespace
std::string consent_display(std::string_view value) {
  const auto sanitized = support::sanitize_utf8(value);            // clause 1
  std::string out;
  for (std::size_t off = 0; off < sanitized.size();) {
    const auto sc = decode_scalar(sanitized, off);
    if (sc.value == U'\n') out += "\\n"; else if (sc.value == U'\r') out += "\\r"; else if (sc.value == U'\t') out += "\\t";   // clause 2
    else if (sc.value <= 0x1fU || sc.value == 0x7fU || (sc.value >= 0x80U && sc.value <= 0x9fU)) append_u00(out, sc.value);   // clause 3
    else if (consent_display_active(sc.value)) append_braced(out, sc.value);                                                 // clause 5
    else out.append(sanitized, off, sc.width);                                                                                // clause 4
    off += sc.width;
  }
  return out;
}
```

  and the four renderers wrap EVERY bound value exactly once: `consent_display(facts.op)`, `consent_display(facts.repo)`, `consent_display(facts.requested)`, `consent_display(facts.effective)`, `consent_display(relpath)` — template literals byte-unchanged. `render_run_guidance_line` unchanged. The precedence order in the loop is EXACTLY clauses 1 → 2 → 3 → 5 → 4 (A8-R1 rev5 precedence: one result per scalar).
- [ ] **Step 4: run to verify pass** — `./build/ci-macos/biv_tests '[a8]'` rc 0; the whole suite `ctest --preset ci-macos -E '^safety-hardening$'` rc 0; the A6 golden tests in `test_cli.cpp`/`test_envelope.cpp` still pass (ordinary ASCII addresses are clause-4 pass-through — byte-identical renders).
- [ ] **Step 5: the R-4.48 (ii) census, then commit** — `grep -c -E 'facts\.(op|repo|requested|effective)|std::string\{relpath\}|relpath' src/cli/url_consent.cpp` and `grep -c 'consent_display(' src/cli/url_consent.cpp` recorded to `$EVID/code/a8-census.txt`: every bound-value occurrence inside the four renderer bodies is wrapped (the implementer lists each occurrence line with its wrapper; zero unwrapped). `git diff --stat -- src/core/open/render.cpp` EMPTY.

```bash
git add tools/gen_consent_display_table.py src/cli/consent_display_table.hpp src/cli/url_consent.hpp src/cli/url_consent.cpp tests/test_url_consent.cpp CMakeLists.txt
git commit -m "cli: A8 consent-render policy inside the four url_consent renderers (clauses 1-5; generated Cf|Zl|Zp|Default_Ignorable table @ Unicode 15.0.0 with pinned input digests); a8.1-a8.4 on the eleven-row matrix"
git rev-parse HEAD > "$EVID/commits.c2.txt"
```

### Task 3 — c3, the CLI: `--offline` / `--network` (m-3 §4 verbatim), the hook truth table, the stderr writers, the flag read, the B-predicate dedup

**Files:** Modify `src/cli/args.hpp`, `src/cli/args.cpp`, `src/cli/main.cpp`, `tests/test_cli.cpp`; Create `tests/cli_run.hpp` (the run helpers moved from `test_cli.cpp` + `run_cmd_pty_split`).
**Interfaces:** Produces `Command.offline`, `Command.network` (bool); `biv::pack::PackOptions{bool offline}` and `biv::open::OpenOptions.offline` are DECLARED here (Tasks 4/5 consume them; until then pack/open ignore the field — the flag reaches nothing, honestly); `install_url_divergence_hook(const Command&) -> ConsentRun` in `main.cpp` (a `biv::repo::UrlDivergenceRun` + the notice writer); `emit_entry_refusals(const std::vector<UrlDivergenceEntryRefusal>&, std::ostream& err)` (per-entry lines in row order + ONE guidance line); `run_cmd_pty_split(args, cwd, input) -> RunResult{code, out, err, tty{stdin,stdout,stderr}}` in `tests/cli_run.hpp`.

- [ ] **Step 0: the T-HELP gate** — `[ -s "$RUNNERS/m3-help-order.txt" ]` (the pair Planner writes m-3's Q12 word: `before-accept` or `after-consent`); absent → Steps 1–4 proceed for everything EXCEPT the help-line insertion and the golden re-pin, and the task's commit WAITS on the word (the working tree holds the rest, green).
- [ ] **Step 1: the failing tests** — `tests/test_cli.cpp`: (i) `biv pack --offline <dir>` parses (`Command.offline == true`); `biv open --offline <image>`; `biv open --network <image>`; `biv open --offline --network <image>` → exit 5 UsageError with detail `conflicting-flags`; `biv list --offline` / `biv info --network` → exit 5 `unknown-flag` exactly as any unknown flag today; `biv pack --network <dir>` → `unknown-flag` (open only). (ii) the help golden: `biv open --help` byte-whole with the two new lines at m-3's position (T-HELP). (iii) `run_cmd_pty_split` discriminator: a child `sh -c 'test -t 0; echo $?; test -t 1; echo $?; test -t 2; echo $?'` → stdout `0\n1\n0\n` (stdin TTY, stdout NOT, stderr TTY), captured stdout via the pipe and stderr via the pty master SEPARATELY (must-be-YES); the existing `run_cmd_pty` on the same child → `0\n0\n0\n` (must-be-NO: the one-pty topology is DIFFERENT). (iv) the hook truth table is NOT yet reachable (no engine path) — its legs are Task 7's; here a unit case over `install_url_divergence_hook` asserts: flag set → `run.hook` non-empty and returns `proceed` on a synthetic `UrlDivergence`; flag absent + `interactive_url_hook_installable()` false (the test process has no TTY under ctest) → `run.hook` EMPTY.
- [ ] **Step 2: run to verify failure** — `./build/ci-macos/biv_tests '[cli-flags]'` FAILS (`--offline` → unknown-flag).
- [ ] **Step 3: the implementation** —

  `args.hpp`: `bool offline{false}; bool network{false};` on `Command`.
  `args.cpp` pack loop: `if (tokens.at(i) == "--offline") { command.offline = true; continue; }` before the `is_flag` check; open loop: `else if (arg == "--offline") { command.offline = true; } else if (arg == "--network") { command.network = true; }`; after the loop: `if (command.offline && command.network) return std::unexpected(usage("conflicting-flags"));`. `help_text(Verb::open)`: the two lines `"  --offline\n" "  --network\n"` inserted at m-3's position (T-HELP; default = immediately BEFORE `"  --accept-url-divergence\n"`). `pack` has no help_text and gains none.

  `main.cpp`:

```cpp
struct ConsentRun {
  biv::repo::UrlDivergenceRun run;          // hook + memo + accepted/refused (engine-owned semantics)
};
ConsentRun install_url_divergence_hook(const biv::cli::Command& parsed) {
  ConsentRun consent;
  auto facts_of = [](const biv::repo::UrlDivergence& d) {
    return biv::cli::UrlDivergenceFacts{.op = d.operation, .repo = d.repo.generic_string(), .requested = d.requested, .effective = d.effective};
  };
  auto notice = [facts_of](const biv::repo::UrlDivergence& d) { std::cerr << biv::cli::render_accepted_notice(facts_of(d)) << std::flush; };
  if (parsed.accept_url_divergence) {                                  // row 1: pre-approval, ANY tty state
    consent.run.hook = [notice](const biv::repo::UrlDivergence& d) { notice(d); return biv::repo::UrlDivergenceDecision::proceed; };
  } else if (biv::cli::interactive_url_hook_installable()) {            // row 2: stdin AND stderr TTYs
    consent.run.hook = [facts_of, notice](const biv::repo::UrlDivergence& d) {
      const bool yes = biv::cli::prompt_url_divergence(facts_of(d), std::cin, std::cerr);
      if (yes) notice(d);
      return yes ? biv::repo::UrlDivergenceDecision::proceed : biv::repo::UrlDivergenceDecision::refuse;
    };
  }                                                                     // row 3: NO hook — the engine refuses, typed (M veto 2)
  return consent;                                                       // `--json`, `--offline`, `--network` appear in NO row
}
```

  Installed around the verb's engine-reaching call: `biv::repo::ScopedUrlDivergenceRun scoped{consent.run};` immediately before `biv::pack::pack(...)` / `biv::open::execute_open(...)` and alive until the call returns; afterwards `report->url_divergence_accepted` is filled from `consent.run.accepted` (one entry per accepted triple: requested, effective, op = operation, repo = the hook's repo path as a generic string). The memo (once per triple) is the ENGINE's; the CLI adds no batching (A6-R5).

  Open refusals (`report->url_divergence_refusals`, filled by Task 4): after `execute_open` returns and BEFORE the session leg's output, `for (row : refusals) std::cerr << render_entry_refusal_line(row.relpath, {row.op, row.repo_id? — NO: repo = the entry's relpath per A6-R4's template, requested, effective})`, then iff `!refusals.empty()` ONE `render_run_guidance_line(refusals.size())`. Both to `std::cerr`, flushed; failure of `std::cerr` → the existing `consent-surface-write-failed` InternalError path.

  Pack refusal (filled by Task 5): on `pack` error with `kind == UrlDivergenceRefused`, set `error.detail = render_pack_refusal_detail({facts["op"], error.path, facts["requested"], facts["effective"]})` BEFORE `emit_error` (the stream carries the template after `biv: UrlDivergenceRefused: `; `error.detail` carries it exactly — a6·7's two carriers).

  Predicate dedup: `main.cpp:277`'s `::isatty(STDIN_FILENO) != 0 && ::isatty(STDERR_FILENO) != 0` → `biv::cli::interactive_url_hook_installable()`; `main.cpp:68`'s negated pair (`== 0 || == 0`) → `!biv::cli::interactive_url_hook_installable()` (the same predicate, one definition); PROMPT B's other conjuncts untouched; `#include "cli/url_consent.hpp"` added.

  `tests/cli_run.hpp`: `run_cmd`, `run_cmd_pty`, `run_cmd_closed_stderr` moved verbatim (static inline), plus:

```cpp
struct SplitRunResult { int code; std::string out; std::string err; bool stdin_tty; bool stdout_tty; bool stderr_tty; };
// stdin + stderr = the pty slave (the master is read for `err`); stdout = a pipe (read for `out`); the child records its own
// descriptor TTY states into a temp file the parent reads back (the a7·3 topology; RECONCILE R4 I2B-04).
SplitRunResult run_cmd_pty_split(const std::string& args, const std::filesystem::path& cwd, std::string_view input);
```

- [ ] **Step 4: run to verify pass** — `./build/ci-macos/biv_tests` rc 0; `ctest --preset ci-macos -E '^safety-hardening$'` rc 0; `grep -c 'isatty(STDIN_FILENO)' src/cli/main.cpp` == 0 (recorded; V-A7-1 one predicate).
- [ ] **Step 5: commit (after the T-HELP word)** —

```bash
git add src/cli/args.hpp src/cli/args.cpp src/cli/main.cpp tests/test_cli.cpp tests/cli_run.hpp src/core/pack/pack.hpp src/core/open/open.hpp
git commit -m "cli: --offline (pack, open) and --network (open) per m-3 130818 s4; conflicting-flags; help lines; url-divergence hook truth table (flag | stdin&&stderr TTY | none); stderr writers for notice, per-entry refusals and the one guidance line; PROMPT B/A TTY predicate deduped onto interactive_url_hook_installable; split-stream PTY helper"
git rev-parse HEAD > "$EVID/commits.c3.txt"
```

### Task 4 — c4, the open verb: the `repos/` member class, `restore_entry` per row in §2.2 order, the report rows, `--offline` D4 (A2 D4; m-3 §4 OPEN; restore-apply §1/§2.2; V-2b-7/V-2b-8)

**Files:** Modify `src/core/open/open.hpp`, `src/core/open/open.cpp`, `src/core/report/envelope.hpp`, `src/core/report/envelope.cpp`, `src/cli/main.cpp`, `schemas/biv-json-envelope.v1.schema.json`, `harness/selftest/test_envelope.py` (the `CURRENT_LOCKED_SCHEMA_BLOBS` entry for the envelope schema — recomputed `git hash-object`), `tests/test_cli.cpp`, `tests/test_envelope.cpp`.
**Interfaces:** Produces `OpenOptions.offline`; `struct RepoOutcomeRow { std::string id; std::string relpath; std::string outcome; /* restored | shallow-pointer | payload-only-unborn | failed | offline-pointer */ std::optional<std::string> sha; std::optional<std::string> branch; std::string capture_mode; std::vector<std::string> remotes; std::optional<std::string> bundle_path; std::vector<biv::repo::LocalRefRestoreRow> local_refs; std::vector<std::string> advisories; std::optional<std::vector<std::string>> shallow_boundary; };` and `std::vector<RepoOutcomeRow> OpenReport::repos`; `OpenReport.url_divergence_refusals` FILLED. Consumes `biv::repo::restore_entry`, `biv::repo::Git::resolve`.

- [ ] **Step 0: the T-JSON and T-STAGE gates** — `[ -s "$RUNNERS/m3-json-shape.txt" ]` and `[ -s "$RUNNERS/offline-stage.txt" ]` (the pair Planner writes the owners' words on Q9 / Q13); absent → the code steps proceed on the defaults stated in the contingent-terms table; the commit WAITS.
- [ ] **Step 1: the failing tests (hand-built images, `provenance=hand-built, interim`)** — a test helper `build_repo_image(dir) -> image path` that drives the ENGINE directly (`repo::discover` → `classify` → `run_eligibility(…, network)` → `capture` into a scratch dir) then assembles the archive with `manifest::serialize` + the container writer exactly as `pack.cpp` orders members (manifest, checksums, payload, repos, agents) — a fixture builder, replaced by `biv pack` itself once Task 5 lands (Task 7 re-executes every case here against product-packed images). Cases in `tests/test_cli.cpp`:
  - `repos/ member class admitted iff named`: an image whose one repos[] row names `repos/<id>/repo.bundle` → open succeeds; the SAME image with an extra `repos/<id>/stray.bin` member listed in checksums → exit 3 `UnmanifestedMember` naming it (V-2b-7; ADDENDUM-I discipline); an image whose row names a member ABSENT from the archive → exit 3 `IntegrityFailurePreApply` detail `missing-repo-artifact` (mirrors `missing-agent-member`).
  - `restore_entry once per row, parents before children`: a parent repo with a nested child repo → after open, both are git repos at their relpaths under dest; the request-trace shim log (BLOCK `git-shim.sh` on PATH — see §Instruments) shows the parent's clone before the child's; `result.repos[]` has two rows, outcomes `restored`, in that order.
  - `nothing before apply touches disk`: a divergence refusal at the first entry leaves the dest ABSENT? — NO: A6-R4/a6·12 say the clean entries COMPLETE and the refused ones are rows (exit 2); so: two refused entries + one clean → dest exists, the clean repo restored, two `UrlDivergenceEntryRefused` rows in ENCOUNTER ORDER, exit 2, `error` null (a6·12's shape; Task 7 adds the golden text and stream-order assertions at product scope).
  - `--offline`: the same image → ZERO git spawns in the shim log for the whole open (m-1's guarantee; m-3 V-OFF (1)); payload + sessions laid down as today; `result.repos[]` rows `outcome: offline-pointer` with `relpath`, `branch`, `sha`, `remotes[]`, `bundle_path` (full-image rows only) (T-JSON); exit 0; the D4 listing on stderr (Task 4 Step 3 text) after the apply summary, byte-exact modulo paths.
  - `zero state`: an image with no repos[] → no `repos` member in the result object (a6·15's shape for this member); no listing; exit as today.
- [ ] **Step 2: run to verify failure** — `./build/ci-macos/biv_tests '[open-repos]'` FAILS (`UnmanifestedMember` for every `repos/` member today).
- [ ] **Step 3: the implementation** —
  `read_archive_plan` (`open.cpp:283-296`): admit `repos/` members: build `std::set<std::string> named_artifacts` from every `plan.manifest.repos[i]` row's `bundle`, `local_refs_bundle`, `capture.staged_patch`, `capture.worktree_patch` (generic strings; only those four kinds — manifest-format §3 under `repos/<id>/`); a member starting with `repos/` is admitted iff `named_artifacts.contains(path)` (checksums membership is already checked above) → `plan.repo_artifacts.push_back(PlannedMember{…})`; else `UnmanifestedMember`. After the loop: every `named_artifacts` entry not `seen` → `IntegrityFailurePreApply` detail `missing-repo-artifact`.
  `apply_archive`: a third branch for `repos/` members: extracted (file members only; `MemberPathUnsafe` otherwise) into `stage_dir / <path minus "repos/">` with checksum verification exactly like payload; counted separately (`repo_artifact_count`); the member-count check includes them.
  `execute_archive`: `stage_dir = containing_dir(dest) / (dest.filename() + ".bvpk-open.stage")` — present at start → `OpenPartialPresent` naming it (the existing kind; the same repair path as the partial dir); created before apply; after `apply_archive` and the mtime pass, iff `!plan.manifest.repos.empty() && !options.offline`: `auto git = biv::repo::Git::resolve(getenv)` (`getenv` = the process environment through `support::Getenv`, as the engine tests build it; failure → the engine's typed error surfaces as today); order the rows PARENTS BEFORE CHILDREN (stable topological order by `parent_id`, manifest order within a level); for each row: `restore_entry(git, entry, partial_dir, stage_dir)`; on a value → `RepoOutcomeRow` from `RepoRestoreRow` (outcome word by the D5.2 enum: `restored`, `shallow-pointer`, `payload-only-unborn`, `failed`); on an error whose `repo_engine_kind` fact is `url_divergence_refused` → push `UrlDivergenceEntryRefusal{entry.id, entry.relpath, facts.requested, facts.effective, facts.op}` and a `RepoOutcomeRow{outcome = "failed"}` and CONTINUE (V-2b-8(iii): the entry's typed restore failure, never downgraded); any other error → whole-operation failure with the `partial_dir` fact exactly as payload errors today. Offline: rows synthesized from the manifest alone (`offline-pointer`; `bundle_path` = the staged bundle copied to `<dest>/.biv/repos/<id>/<name>` per T-STAGE's default; unborn HEAD → `sha` absent). Then `fsync_tree`, the rename to `dest`, and `stage_dir` removed (also on every error path via the cleanup lambda).
  `envelope.cpp` `write_open_result`: iff `!report.repos.empty()`: `"repos": [ {id, relpath, outcome, sha|null, branch|null, capture_mode, remotes[], bundle_path?, local_refs[{ref, recreated, skipped_at_sha, detail?}], advisories[], shallow_boundary?} … ]` (T-JSON); `result.manifest.repos` stays the landed EMPTY array (I2B-09 option (b), registered). Schema: the open result branch gains an optional `repos` array property with that row shape (`outcome` enum of the five words); the exit-map schema untouched here; the selftest blob pin for the envelope schema recomputed in THIS commit (V-A6-3 same-commit rule).
  `main.cpp` (open, `--offline`, human mode, iff `!report->repos.empty()`), AFTER the apply summary, on `std::cerr`, VERBATIM from m-3 §4:

```text
open --offline: repositories were not restored (no git, no network). Stored remote URLs below are informational — recorded at pack, not vetted or complete. Cloning them is git-clone-grade trust: git may contact those URLs and additional URLs from repo metadata (.gitmodules, nested submodules, host git config) that Bivpak does not see or police. Clone only what you trust.
<relpath> · <branch> · <commit> · <url>[, <url>…]
<relpath>: git clone <bundle-path>   (partial/manual reconstruction — not a full restore)
```

  one repo line per row in manifest order (`<branch>` = `(detached)` when none; `<commit>` = the 40-hex sha, `(no commits)` for an unborn HEAD; no stored URL → `(no stored remote)`), then the clone line for each full-image row; every value through `consent_display` (A8-R1 policy; the machine carrier raw); exit 0 (an offline open is a success). `--offline` and `--network` alter NOTHING about PROMPT D (V-OFF (3)); `--network` beyond parse/conflict is T-NET (inert).
- [ ] **Step 4: run to verify pass** — `./build/ci-macos/biv_tests` rc 0; `ctest --preset ci-macos -E '^safety-hardening$'` rc 0; the selftest `pytest harness/selftest/test_envelope.py` under the venv rc 0 (the recomputed pin).
- [ ] **Step 5: commit (after the T-JSON / T-STAGE words)** —

```bash
git add src/core/open/open.hpp src/core/open/open.cpp src/core/report/envelope.hpp src/core/report/envelope.cpp src/cli/main.cpp schemas/biv-json-envelope.v1.schema.json harness/selftest/test_envelope.py tests/test_cli.cpp tests/test_envelope.cpp
git commit -m "open: repos/ member class (named by a repos[] row + checksummed; else UnmanifestedMember); restore_entry once per row, parents before children, after plan+consent inside the partial dir; result.repos[] rows (D5.2 + offline-pointer); per-entry url-divergence refusal rows; --offline: zero git, D4 listing per m-3 130818 s4, exit 0"
git rev-parse HEAD > "$EVID/commits.c4.txt"
```

### Task 5 — c5, the pack verb: matcher → discover → classify → eligibility (mode) → capture leaves-first → repos[] + `repos/<id>/…` members; single-writer exclusion; the narrowed `.git` class behind a typed refusal (pack-engine §1.1/§1.2/§1.3/§2/§4; V-2b-3..6; A7-R3(2))

**Files:** Modify `src/core/scan/scan.hpp`, `src/core/scan/scan.cpp`, `src/core/pack/pack.hpp`, `src/core/pack/pack.cpp`, `src/cli/main.cpp`, `tests/test_scan.cpp`, `tests/test_pack.cpp`, `tests/test_cli.cpp`.
**Interfaces:** Produces `struct ScanExclusions { std::vector<std::filesystem::path> repo_subtrees; }` and `expected<ScanResult> scan(const std::filesystem::path& root, const ignore::Matcher& matcher, const ScanExclusions& excl)` (the old one-arg `scan(root)` is kept as a thin overload building the matcher with no exclusions, so existing callers/tests compile); `expected<MatcherBundle> prepare_matcher(root)` (the matcher + the `BivignoreProvenance` scan already records); `struct PackOptions { bool offline{false}; }` and `expected<PackReport> pack(const std::filesystem::path& source_dir, const PackOptions& options)` (the one-arg overload forwards `{}`); `PackReport.repos` (the `manifest.repos` entries, whole). Consumes Task 1's `EligibilityMode`, the engine API verbatim.

- [ ] **Step 0: the T-FENCE record** — read `src/core/repo/classify.cpp:120-190` and `:340-360`; for each `Fence::submodule` (:134), `Fence::nested` (:146), `Fence::unmerged` (:179), `Fence::dirty` (:354) record the exact trigger condition to `$EVID/code/fences.txt`; if `Fence::dirty` fires on an ordinary born, non-shallow repo with uncommitted changes → STOP to m-1 (Q11) BEFORE writing Step 3's fence branch; otherwise proceed with the default disposition (a fenced classification surfaces its `EngineIssue` through the engine-error path as a whole-operation typed failure). Record the outcome either way.
- [ ] **Step 1: the failing tests** — `tests/test_scan.cpp`: the existing "scan refuses repo-bearing roots" case becomes TWO cases: (a) `scan(root, matcher, {.repo_subtrees = {""}})` on a root whose `.git` IS a discovered boundary → succeeds, `payload` contains NO `.git` node and NO node under the repo subtree (workspace-root repo ⇒ EMPTY residue, V-2b-5); (b) a `.git`-named SYMLINK at the root with `repo_subtrees` empty → `RepoDiscoveredUnsupported` (the kind literal until Task 6 renames it) with `facts["reason"] == "symlink"`; a `.git`-named FIFO (`mkfifo`) → `reason == "special-file"`; a `.git` directory whose parent is NOT a boundary (discover did not claim it — synthesized by passing `repo_subtrees` that omit it) → `reason == "unreadable-marker"`? — NO: the reason vocabulary is m-1's three member classes exactly (`symlink | special-file | unreadable-marker`); an unclaimed `.git` DIRECTORY cannot occur when discover ran on the same tree (discover claims every dir-or-regular-file `.git`), so the test for that shape asserts the boundary path instead. A `.git` REGULAR FILE (gitlink/worktree pointer) IS a boundary (discover) → no refusal. `tests/test_pack.cpp`: "pack refuses repo-bearing source" becomes "pack records a repo-bearing source": `git init` + one commit under `source/`; `pack(source, {})` → `report.repos.size() == 1`; the archive lists `repos/<id>/…` members exactly as `CaptureResult.artifacts[].archive_path` names them; `manifest.json` parsed back → `repos[0].relpath == "."`? (the workspace-root repo's relpath as discover reports it); `--offline` variant → `capture_mode == full`, `eligibility.result == offline_declared`, and ZERO `ls-remote` in the request-trace shim log. `tests/test_cli.cpp`: `biv pack --json` on a repo-bearing source → `result.manifest.repos` is `[]` (unchanged carrier, I2B-09 (b)) while the archive's manifest.json carries the row (the two are different objects — asserted separately).
- [ ] **Step 2: run to verify failure** — `./build/ci-macos/biv_tests '[pack-repos]'` FAILS (`RepoDiscoveredUnsupported` on the directory).
- [ ] **Step 3: the implementation** —
  `scan.cpp` `walk`: the `.git` name test becomes: `if (name == ".git") { if (excl.claims(rel_dir)) continue; /* the boundary's marker: never a payload node */ return std::unexpected(unclaimed_git_entry(child.path(), status)); }` where `unclaimed_git_entry` builds `BivError{ErrKind::RepoDiscoveredUnsupported /* Task 6: UnclaimedGitEntry */, path, /*detail*/ {}, 0, {{"reason", is_symlink(status) ? "symlink" : !is_regular_file(status) && !is_directory(status) ? "special-file" : "unreadable-marker"}}}`; a directory entry whose relpath is in `excl.repo_subtrees` is NOT descended and NOT added (V-2b-5; the gitlink entry excepted — a `.git` REGULAR FILE inside a claimed subtree never reaches here because the subtree is skipped whole). The matcher (`.bivignore`) runs FIRST exactly as today (I-R2a; the `continue` at :131 precedes the name test).
  `pack.cpp`, replacing the single `scan::scan(source)` call:

```cpp
  auto matcher = scan::prepare_matcher(source);                    if (!matcher) return cleanup_error(matcher.error());
  auto discovery = repo::discover(source, matcher->matcher);       if (!discovery) return cleanup_error(engine_to_pack_error(discovery.error()));
  scan::ScanExclusions exclusions; for (const auto& b : discovery->repos) exclusions.repo_subtrees.push_back(b.relpath);
  auto scan_result = scan::scan(source, matcher->matcher, exclusions); if (!scan_result) return cleanup_error(scan_result.error());
  std::vector<repo::RepoEntry> entries; std::vector<repo::CaptureResult> captures;
  if (!discovery->repos.empty()) {
    auto git = repo::Git::resolve(getenv_of(env));                  if (!git) return cleanup_error(git.error());
    for (const auto& b : discovery->repos) {                        // §1.3 classify, discovery (DFS) order
      auto c = repo::classify(*git, source / b.relpath, *discovery); if (!c) return cleanup_error(engine_to_pack_error(c.error()));
      if (c->fence != repo::Classification::Fence::none) return cleanup_error(engine_to_pack_error(issue_error(*c)));   // T-FENCE default
      entries.push_back(std::move(c->entry));
    }
    const auto mode = options.offline ? repo::EligibilityMode::offline : repo::EligibilityMode::network;
    for (auto& e : entries) {                                       // §2 eligibility, encounter order — PROMPT D fires here (A7-R3(2))
      if (auto ok = repo::run_eligibility(*git, e, mode); !ok) return cleanup_error(engine_to_pack_error(ok.error()));
    }
    for (auto idx : leaves_first(entries)) {                        // Phase C capture: children before parents
      auto cap = repo::capture(*git, entries[idx], scratch_path);    if (!cap) return cleanup_error(engine_to_pack_error(cap.error()));
      captures.push_back(std::move(*cap));
    }
  }
```

  `engine_to_pack_error(BivError e)`: iff `e.facts["repo_engine_kind"] == "url_divergence_refused"` → `BivError{ErrKind::UrlDivergenceRefused, e.path /* the hook's repo */, {}, 0, {requested, effective, op copied from e.facts}}` (A6-R1's pack grain; M veto 4: never laundered); every other engine error returned UNCHANGED (today's typed engine-error path). `leaves_first`: indices ordered so every entry precedes its `parent_id` (children first), stable by discovery order. `scratch_path = image_path.parent_path() / (image_path.filename() + ".scratch")` created before capture, removed by the cleanup lambda and at the end. Members: after the payload loop and BEFORE the agents loop (§4 "payload/repos/agents"): for each capture, for each artifact: `write_file_member(spool_writer, artifact.disk_path, artifact.archive_path.generic_string(), created.seconds)`; `emitted_members.insert(archive_path)` must succeed (else `ArchiveWriteFailed` `repo-member-duplicate`); `checksums.entries[archive_path] = extent; ++report.member_count`. The manifest: `.repos = entries` (WHOLE — V-2b-4; `PackReport.repos = entries` for the report). The C-2 propagation hunk (`if (!manifest_json) return cleanup_error(...)`) byte-unchanged.
  `main.cpp` pack: `biv::pack::pack(parsed->pack_dir, biv::pack::PackOptions{.offline = parsed->offline})` inside the `ScopedUrlDivergenceRun` from Task 3; the `UrlDivergenceRefused` detail fill from Task 3 now has a producer.
- [ ] **Step 4: run to verify pass** — `./build/ci-macos/biv_tests` rc 0; `ctest --preset ci-macos -E '^safety-hardening$'` rc 0; `grep -n 'manifest_json' src/core/pack/pack.cpp` shows the C-2 hunk unchanged vs `git show a2f6fd1:src/core/pack/pack.cpp` (recorded diff of those lines EMPTY).
- [ ] **Step 5: the RepoEntry production census, then commit** — `grep -n -E '\.(id|relpath|kind|sha|branch|head_state|capture_mode|eligibility|local_refs|local_refs_bundle|bundle|capture|shallow|notes|remotes|remote|parent_id|dirty|promisor|engine_source) *= ' src/cli src/core/pack src/core/scan src/core/open` → EMPTY (V-2b-4; recorded to `$EVID/code/repoentry-census.txt`; a hit is a STOP, not a rewrite).

```bash
git add src/core/scan/scan.hpp src/core/scan/scan.cpp src/core/pack/pack.hpp src/core/pack/pack.cpp src/cli/main.cpp tests/test_scan.cpp tests/test_pack.cpp tests/test_cli.cpp
git commit -m "pack: sealed order (matcher -> discover -> classify -> eligibility(mode) -> capture leaves-first -> assembly); repo subtrees excluded from payload; entries copied whole into manifest.repos; artifacts as members at archive_path verbatim; url_divergence_refused -> UrlDivergenceRefused; the .git refusal narrows to the unclaimed class (kind literal renamed in the next commit)"
git rev-parse HEAD > "$EVID/commits.c5.txt"
```

### Task 6 — c6, the kind (CONTINGENT on m-3's addendum lock — T-KIND): retire `RepoDiscoveredUnsupported`, cut `UnclaimedGitEntry` refusal/3 appended; TC-1..3 fold (m-3 §3; V-A6-3 same-commit; master 131404 (1))

**Files:** Modify `src/core/support/error.hpp`, `src/core/support/error.cpp`, `src/core/report/envelope.cpp`, `src/core/scan/scan.cpp` (the kind literal only), `schemas/biv-exit-map.v1.json`, `tests/test_envelope.cpp`, `tests/test_scan.cpp`, `tests/test_pack.cpp`, `harness/selftest/test_envelope.py` (the exit-map blob pin).

- [ ] **Step 0: the lock gate** — `[ -s "$RUNNERS/m3-addendum-lock.txt" ]` holding `lock_id=<id> doc_sha256=<hex> relay=<path>`; the implementer re-hashes the addendum at the named pdc path and it MUST equal `doc_sha256` or STOP. Absent → HOLD here (the working tree carries nothing of Task 6; Task 7 may proceed on the c5 literal for everything except the kind-name assertions, which are written against a `kUnclaimedGitKind` test constant switched by this task).
- [ ] **Step 1: the failing tests** — `tests/test_envelope.cpp`: the `ExpectedRow` list loses `{"RepoDiscoveredUnsupported", …}` and gains `{"UnclaimedGitEntry", "refusal", biv::report::exit_for_error(biv::ErrKind::UnclaimedGitEntry)}` as the LAST row; the `:249` literal becomes `"\"UnclaimedGitEntry\", \"class\": \"refusal\", \"exit\": 3"` (no `transitional`); `CHECK(exit_text.find("RepoDiscoveredUnsupported") == std::string::npos)`; the `rows.size()` pin self-adjusts (29 → 29). TC-1: two literal exit pins at the parity find-after-position idiom (`:237,245` → `CHECK(exit == 3)` / `CHECK(exit == 2)` literals beside the derived ones). TC-2: a second accepted entry on the open arm of the one-grouped-object claim (`:830,838`). TC-3: one nonzero-sessions arm for `exit_for_open`'s max composition (`:879-885`: a sessions outcome carrying an exit-2 row + one refusal row → 2; an exit-0 sessions outcome + one refusal row → 2; an exit-2 sessions outcome + zero refusals → 2). `tests/test_scan.cpp` / `tests/test_pack.cpp`: the unclaimed cases assert `ErrKind::UnclaimedGitEntry`, `facts["reason"]`, `error.path` = the member path, and `error.detail` == the template below with `<path>` and `<reason>` substituted.
- [ ] **Step 2: run to verify failure** — compile error (`UnclaimedGitEntry` undeclared).
- [ ] **Step 3: the implementation, ONE commit** — `error.hpp`: remove `RepoDiscoveredUnsupported`; append `UnclaimedGitEntry` LAST (after `UrlDivergenceEntryRefused`); `error.cpp` `to_string` likewise; `envelope.cpp` `exit_for_error`: the `RepoDiscoveredUnsupported` case removed from the exit-3 group, `case ErrKind::UnclaimedGitEntry:` added to it; `scan.cpp`: the kind literal → `UnclaimedGitEntry`, `detail` = the byte-golden template (m-3 §3, VERBATIM):

```text
pack refused: <path> is a .git-named entry that is not a repository boundary (<reason>); remove or repair it and re-run.
```

  (one template, two carriers: `error.detail` and the stream through `emit_error`); `schemas/biv-exit-map.v1.json`: the `RepoDiscoveredUnsupported` row removed, `{"kind": "UnclaimedGitEntry", "class": "refusal", "exit": 3}` appended as the LAST row (29 rows before and after); `harness/selftest/test_envelope.py` `CURRENT_LOCKED_SCHEMA_BLOBS["schemas/biv-exit-map.v1.json"]` = `git hash-object schemas/biv-exit-map.v1.json` at the new bytes (the same commit). `error.facts["reason"]` ∈ `symlink | special-file | unreadable-marker` (m-1's three classes; one fixture per class in Step 1). The addendum's lock id and sha are cited in the commit message.
- [ ] **Step 4: run to verify pass** — `ctest --preset ci-macos -E '^safety-hardening$'` rc 0; `pytest harness/selftest/test_envelope.py` rc 0; `python3 -c 'import json;print(len(json.load(open("schemas/biv-exit-map.v1.json"))["rows"]))'` == 29.
- [ ] **Step 5: commit** —

```bash
git add src/core/support/error.hpp src/core/support/error.cpp src/core/report/envelope.cpp src/core/scan/scan.cpp schemas/biv-exit-map.v1.json tests/test_envelope.cpp tests/test_scan.cpp tests/test_pack.cpp harness/selftest/test_envelope.py
git commit -m "report: retire RepoDiscoveredUnsupported (transitional placeholder honored); cut UnclaimedGitEntry refusal/3 appended for the unclaimed .git class (reason: symlink|special-file|unreadable-marker; byte-golden detail) -- m-3 addendum <lock id> @ <doc sha256>; exit map 29->29; TC-1..3 folded"
git rev-parse HEAD > "$EVID/commits.c6.txt"
```

### Task 7 — c7, the product-scope witnesses: every deferred leg executed through the REAL CLI against `biv pack`-PRODUCED images (E1; master 041518's re-execution condition; m-1 §2; m-3 §1; FX-A6/A7/A8/M/N)

**Files:** Create `tests/test_wiring.cpp` (added to `biv_tests`), Modify `tests/cli_run.hpp` (fixture builders), `CMakeLists.txt` (source list).
**Fixtures (built by the tests in temp dirs; reality-shaped; no network egress — every remote is a local bare repo reached over `file://`):** `F-REMOTE` (bare `remote.git` + a working clone with one commit and `origin`); `F-DIVERGE` (a second bare `effective.git` cloned from `remote.git`; the working repo's LOCAL config `url.file://…/effective.git.insteadOf file://…/remote.git` — same-context, M leg (h)); `F-RESTORE-DIVERGE` (the SAME rewrite in a temp `HOME/.gitconfig` handed to the child `biv open` process — the restore context has no repo yet); `F-TWO-REPOS` (two working repos with identical requested/effective addresses — a6·6); `F-NESTED` (a repo containing an untracked nested repo — §2.2 order, leaves-first); `F-SHALLOW` (`git clone --depth 1 file://…/remote.git` — N (a)); `F-PROMISOR-SHALLOW` (`git clone --filter=blob:none --depth 1` — N (g)); `F-GITLINK` (a `.git` regular file pointing at a gitdir — discover boundary); `F-UNCLAIMED` (`.git` symlink → `UnclaimedGitEntry`); `F-EQUIV` (rewrites within/without M-R2's equivalence set using `https://Host.invalid/…` ↔ `https://host.invalid/…/`, `http://…:80`, `ssh://…:22`, scp forms — the effective hosts are `.invalid` (RFC 2606, NXDOMAIN by definition) and `GIT_SSH_COMMAND=/usr/bin/false` is set for the child so no transport ever connects; the legs assert PROMPT/REFUSE vs SILENT and `remote_unreachable`/full, never timing). The request-trace instrument: BLOCK `git-shim.sh` installed FIRST on the child's `PATH` — it appends `argv` to `$BIV_GIT_TRACE` and `exec`s the real git; every leg that claims "zero git", "no spawn after DENY", or "no ls-remote" reads that log.

- [ ] **Step 0: the T-C check** — `grep -c -E 'render_prompt_c|PROMPT C|memory' src/cli/main.cpp src/core/open/render.cpp`; PROMPT C absent at B → a6·10 is REGISTERED (S-6, m-3) in `$EVID/legs/registered.txt`, not written.
- [ ] **Step 1: the legs, one `TEST_CASE` each, tagged `[wiring][<leg>]`, each writing its receipt line `leg=<id> provenance=product-packed verdict=PASS` to `$EVID/legs/<id>.txt` via `BIV_LEG_RECEIPTS`** (the FX text is the oracle; the named mutants are the reason each assertion exists):
  - **M (a)** pack, F-DIVERGE, non-interactive, no flag → exit 3, `error.kind == UrlDivergenceRefused`, `facts.requested`/`facts.effective` VERBATIM, `error.path` = the repo, nothing written (no `.bvpk`, no `.partial`, no `.scratch`); **(a)-interactive**: `run_cmd_pty_split`, answer `n` → refused; the shim log has NO `ls-remote … effective.git` line after the prompt (DENY leaves the network call UN-EXECUTED — by instrument).
  - **M (b)/(i)/(j)** open of a product-packed F-REMOTE image under F-RESTORE-DIVERGE → each restore site's op label (`ref-recreation` / `clone` / the third `restore.cpp:545` site's label) appears in a `UrlDivergenceEntryRefused` row's `op`; three fixtures (an overlay entry for the clone site; a local_refs remote-proven entry for ref-recreation; the non-full clone arm) — the implementer records which fixture reached which site from the row's `op` and the shim log.
  - **M (c)** F-REMOTE without rewrite: pack + open → zero prompts, zero refusals, zero `url-divergence-accepted`; the envelopes byte-identical modulo `image_id`/`created_at`/paths to a run with the consent fabric's flag absent (they ARE the same run — the assertion is "no fabric surface appears").
  - **M (d)** `--accept-url-divergence` on pack (a6·3) and on open (a6·4): no prompt, proceeds, the notice on stderr byte-golden, ONE `url-divergence-accepted` entries row with the four fields verbatim.
  - **M (e)(f)(l)(m)(n·i)(n·ii)(o)** F-EQUIV forms → SILENT (no prompt, no refusal, `remote_unreachable` → full) vs DIVERGENCE (refuse/prompt) exactly per the M table; each subarm its own case.
  - **M (g)** = **E3**: divergence + NO hook (non-interactive, no flag) → typed `url_divergence_refused` naming BOTH addresses (pack grain exit 3; open grain rows + exit 2) — receipt `E3-macos.txt`; Task 9 repeats it in the Linux parity container.
  - **M (h)** = F-DIVERGE's default (local config only) → detected.
  - **M (k)** REGISTERED (T-K).
  - **a6·1** empty answer → refused (default N); **a6·2** `y` → proceeds, notice golden, entries row, exit 0; **a6·5** memo: open of an overlay entry where the same triple is met at proof-fetch and clone → ONE prompt, ONE notice, ONE entries row; **a6·6** F-TWO-REPOS → two prompts, two rows inside ONE outer `url-divergence-accepted` object, distinguished by `repo`, in encounter order; **a6·7** pack preflight golden refusal (template in `error.detail` AND on the stream, class refusal, exit 3, NOTHING written); **a6·8** flag + PROMPT B image → B still renders; **a6·9** flag + collision → PROMPT A still renders; **a6·11** accept case: NO summary line, NO `warnings` row; **a6·12** two refused entries (distinct `repo_id` AND `relpath`) + one clean, every session row clean → two rows in encounter order, `error` null, exit 2, the clean entry restored, the per-entry template twice on stderr in encounter order (asserted SEPARATELY from the JSON order), the guidance line EXACTLY ONCE with `<n>`=2 after the last per-entry line; **a6·13** run 1 with the flag, run 2 without, non-interactive → refused; no acceptance artifact under the workspace or the temp HOME; **a6·16** (divergence half) the serialized envelopes of a6·2 / a6·7 / a6·12 validate against the LANDED schema through `Draft202012Validator` (a python step over the captured envelopes, run from the venv, receipt `a6-16.txt`).
  - **a7·1** stdin redirected (stderr TTY) → no prompt, typed refusal; **a7·2** stderr redirected (stdin TTY) → no prompt, typed refusal; **a7·3** `run_cmd_pty_split` + `--json`, flag absent, first encounter → PROMPT D renders on the pty (stderr), the answer honored, the envelope on the PIPE (stdout) records the outcome; the split helper's recorded TTY states are asserted (`stdin_tty && stderr_tty && !stdout_tty`); **a7·4** an image triggering PROMPT B AND a restore divergence → B completes before any D; the D prompts in entry encounter order; **a7·5** pack with two divergent remotes (distinct triples) → two prompts at the probe encounter points in order, each atomic (no other stderr byte between a prompt's question and its answer — asserted on the pty transcript).
  - **a8·5** arm A: values carrying the TEN valid rows → `error.facts` / refusal rows / advisories entries round-trip the RAW bytes exactly (C0 via JSON `\u00xx` decoding back byte-exact; multi-byte scalars byte-exact) while the stderr carriers hold the display-encoded form; arm B1: the lone `0x9b` in requested / effective / repo (each in turn) → PROMPT D shows U+FFFD, the decision binds the RAW triple (a second encounter of the SAME raw triple is memo-answered — no second prompt), the serialized carriers per the source×branch matrix (invalid-UTF-8 output on the branch that emits the coordinate); arm B2: `0x9b` in `op`/`relpath`/`repo_id` → no consent claim, the JSON carrier's emission per the matrix. **a8·6**: a verb-reachable hostile effective address carrying the ten valid rows at the pty → the transcript adds no line, moves no cursor, contains no raw ESC/format scalar; `y` binds the raw triple (memo witness as in B1).
  - **N (a) WHOLE**: F-SHALLOW → `biv pack` → the manifest row carries the full N-R2 cluster (`shallow{boundary}`, no `capture_mode`, no `eligibility`, no `local_refs`, no `bundle`) → `biv open` → `result.repos[0].outcome == "shallow-pointer"`, ZERO git lines in the shim log for that entry (the log is per-run: with only the shallow entry in the image, the whole open shows zero git); **E4 parity**: the same open with `--offline` → the row IDENTICAL (field-by-field) and zero git; receipt `E4-parity.txt`. **N (g)**: F-PROMISOR-SHALLOW → `biv pack` → `notes[]` carries `{"kind":"promisor-source"}`.
  - **pack discovery legs**: F-NESTED → two rows, `parent_id` set on the child, capture leaves-first (the shim log shows the child's bundle creation before the parent's), members at `repos/<id>/…`; F-GITLINK → a boundary, no refusal; F-UNCLAIMED → `UnclaimedGitEntry` exit 3, `reason == "symlink"`, detail golden, nothing written; a repo under a `.bivignore`d dir → NOT discovered, the prune-summary advisory names the dir; a workspace-root repo → `payload/` EMPTY (V-2b-5).
  - **R-T** the round trip: F-REMOTE with a dirty worktree + an untracked file + a local branch → `biv pack` → `biv open` → the restored repo's `git status --porcelain=v2` equals the source's; HEAD/branch equal; the untracked penumbra file byte-equal; the local branch recreated (`local_refs[0].recreated == true`).
- [ ] **Step 2: run to verify failure** — each new case fails before its fixture/assertion wiring exists (the file is new; the first build with the cases stubbed as `FAIL("not yet")` is the red state).
- [ ] **Step 3: implement the fixtures and assertions** — `tests/cli_run.hpp` gains `GitFixture` helpers (`init_bare`, `init_work(remote)`, `set_instead_of(repo, requested, effective)`, `temp_home_with_instead_of(...)`, `shim_path(trace_file)`), each a thin wrapper over `git` invocations through `std::system` with quoted paths; every fixture asserts its own preconditions (`git rev-parse HEAD` succeeds; `git remote get-url origin` equals the requested address).
- [ ] **Step 4: run to verify pass** — `./build/ci-macos/biv_tests '[wiring]'` rc 0 (PTY legs run under a real pty allocated by the helper; under ctest they still allocate their own pty); `ctest --preset ci-macos -E '^safety-hardening$'` rc 0; the receipts directory holds one file per leg id listed in the evidence matrix; `ls "$EVID/legs" | wc -l` recorded; `registered.txt` lists exactly the S-6 registrations (T-K, T-C if absent).
- [ ] **Step 5: commit** —

```bash
git add tests/test_wiring.cpp tests/cli_run.hpp CMakeLists.txt
git commit -m "tests: product-scope witnesses through the real CLI on biv-pack-produced images -- FX-M-1 (a)-(o) incl. (d) and (a)-interactive, a6.1-13 + a6.16, a7.1-5 (split-stream pty), a8.5/a8.6, FX-N (a) whole + (g), E3 fail-safe, E4 offline parity, the pack->open round trip"
git rev-parse HEAD > "$EVID/commits.c7.txt"
```

### Task 8 — c8, m-3's harness commit (arm-A shape; m-3 §5): the golden round-trip repos scenario + the A2 FXD-3 offline scenario — AUTHORED AT m-3's SEAT, applied VERBATIM as ONE commit

**Files:** `harness/scenarios/**` only (the patch's own file list; `shells/d-git-restore.json` replaced by the active `d-git-restore` E2 scenario; a second scenario for `biv open --offline`).

- [ ] **Step 0: the patch gate** — `[ -s "$RUNNERS/m3-harness-patch.txt" ]` holding `patch=<abs path> sha256=<hex> relay=<pdc path>` (the pair Planner carries m-3's patch from its relay); re-hash the patch file → MUST equal; `git apply --check <patch>` rc 0; `git apply --numstat <patch>` names ONLY paths under `harness/scenarios/` or STOP (a `harness/selftest` or `harness/bivharness` path in m-3's patch is a population change — see Task 9 Step 4; it is admitted only with m-3's explicit line in the relay and budgeted, never silent).
- [ ] **Step 1: apply as ONE commit with m-3's authorship** — `git am <patch>` if it is a mailbox patch (author preserved), else `git apply --index <patch> && git commit --author="<name from the relay> <address from the relay>" -F "$RUNNERS/m3-harness-commit-message.txt"`; `git show --stat HEAD` → only `harness/scenarios/**`.
- [ ] **Step 2: run both scenarios locally on macOS through the harness runner** — the venv's pytest over the harness with the built `biv` (`BIV_BINARY_PATH=build/ci-macos/biv`, the runner's documented invocation in `harness/README.md`; the implementer records the exact command and its rc to `$EVID/receipts/harness-scenarios-macos.txt`); both scenario ids green; the assertion classes touched (A/B/D/E/H/K; FXD-3) enumerated from the scenario files; the tolerance fixture's digest recorded. This receipt is what m-1's V-2b-8(iv) reads.
- [ ] **Step 3: record** — `git rev-parse HEAD > "$EVID/commits.c8.txt"`; `git status --porcelain` EMPTY.

### Task 9 — the gates at H: E2 + E5 + veto-9 + the RepoEntry census + the C-2 hunk; the count gate on BOTH platforms; the Linux E3 witness; the harness-selftest population rule (the 015244 series if it moved); the companion count-cell commit iff owed; the fence proofs

- [ ] **Step 1: E2 and E5 (m-4 035001)** — E2: `git grep -n -E 'repo::(discover|classify|run_eligibility|capture|restore_entry)\(' HEAD -- src ':!src/core/repo'` → the wiring census, one line per call site (`file:line:call`), written to `$EVID/H/E2-census.txt`; each named site is inside the `ScopedUrlDivergenceRun` scope (the implementer cites the enclosing scope line for each); E5: the SAME grep pattern that returned EMPTY at B (`run_eligibility|restore_entry|repo::discover|repo::classify|repo::capture`) now returns EXACTLY the E2 census lines and nothing else (`diff` of the two normalized lists EMPTY) → `$EVID/H/E5-flip.txt`; the network-class census at H: `git grep -n 'GitCallClass::network' HEAD -- src` → the SAME six engine lines as at B (`diff` EMPTY) → `E2-network-class.txt`; `git grep -n -E 'posix_spawn|execv|popen|std::system|fork\(' HEAD -- src ':!src/core/repo' ':!src/core/support'` → EMPTY (S1 no direct spawn) → `S1-nospawn.txt`.
- [ ] **Step 2: veto 9 mechanical; the RepoEntry census; the C-2 hunk; the fabric census** — `git log --reverse --format=%H B..HEAD` → for each commit `git diff-tree --no-commit-id --name-only -r <sha>`; the FIRST commit's paths ⊆ {`src/core/repo/eligibility.hpp`, `src/core/repo/eligibility.cpp`, `tests/test_repo_engine.cpp`}; NO later commit names a `src/core/repo/` path; NO commit names both a `src/core/repo/` path and a path under `src/cli|src/core/pack|src/core/scan|src/core/open` → `$EVID/H/veto9.txt`; the RepoEntry production grep of Task 5 Step 5 re-run at H → EMPTY; `git diff a2f6fd1 HEAD -- src/core/pack/pack.cpp | grep -c 'manifest_json'` → the C-2 hunk lines unchanged (the implementer records the exact hunk at both shas and `cmp`s them); `git diff --stat B HEAD -- src/core/manifest src/adapters harness/bivharness src/core/open/render.cpp` → EMPTY (V-2b-2; adapter-anchor; render.cpp) → `zero-byte-fences.txt`; `git diff --numstat 3cd31e4 HEAD -- <the 18 fabric paths>` recorded (the plan-face census: the ONE `tests/test_cli.cpp` 3/1 row from a2f6fd1 PLUS this act's own fabric commits — stated, not "empty").
- [ ] **Step 3: the count gate, macOS** — the five binaries `-r xml` at H → `tuples.py` → `H/tuples-macos.txt`; `cellgate.py` H-tuples vs `B-cells.txt` → rc 0 iff every `OverallResultsCases` cell for macOS is UNCHANGED; if a cell moved (this act adds `TEST_CASE`s to `biv_tests` — expected), `cellgate.py` prints the new tuples; `skipset.py` unchanged skips.
- [ ] **Step 4: the Linux parity leg (both B and H), the E3 Linux witness, the population rule** — the parity container per CLAUDE.md (`--platform linux/amd64`, Ubuntu 24.04, `--init`, the non-root drop with `nofile` soft raised to hard) via BLOCKs `linux-container.sh` / `linux-suite.sh` (branch `intg/substep2b-wiring`); the suite at H → `H/tuples-linux.txt`; the E3 witness (M (g)) at H inside the container → `H/E3-linux.txt`; the harness-selftest collected population at B and at H under the identical instrument (`pytest --collect-only -q harness/selftest` counts) → `H/selftest-population-{B,H}.txt`; EQUAL → the single-sample rev12 reading is admissible (`selftest_summary.py`); NOT EQUAL (expected iff Task 8's scenario adds a selftest, or the `test_envelope.py` pin edits changed the collected set — a pin VALUE change does not change the population; a new test does) → the `015244` interleaved series RUNS: N = 10 per tree, alternating B/H, one fresh container per draw, every draw's capture bound to its own parsed N (an invalid draw is a STOP), K-1/K-2 every run, at least one non-empty in-family BASE observation, the verdict per the bar — receipt `H/selftest-series.txt`. Budget: ~10–15 min per draw → up to ~5 h wall; the implementer runs it in the foreground with bounded waits (process rule 221230) and files a SITREP naming the done-artifact if it spans a turn.
- [ ] **Step 5: the companion count-cell commit — IFF a cell moved** — `cellgate.py` at H (both platforms) prints the observed tuples; iff any `OverallResultsCases` or skip cell differs from B's literal cells: edit ONLY those literals in `.github/workflows/s2-harness.yml` (the `want` cells for the moved binaries/platforms), re-run `cells.py` on the edited file and `cellgate.py` against H's tuples → rc 0; commit `ci: pin biv_tests case counts at H (macOS <n>/<s>, Linux <n>/<s>) -- m-3 count-cell companion` → `commits.c9.txt`. If NOTHING moved: `H/count-gate.txt` says `unchanged`, no commit (I2B-08).
- [ ] **Step 6: the fence proofs file** — `$EVID/H/fence-proofs.txt`: the S1 grep, the E2/E5 lists, veto-9, the RepoEntry census, the zero-byte fences, the A8 census (Task 2 Step 5 re-run at H), the predicate census (`grep -c 'isatty(' src/cli/main.cpp` == 0), the hook truth table's three rows (`grep -n 'accept_url_divergence\|interactive_url_hook_installable' src/cli/main.cpp`), the `--json` absence from the hook install (`grep -c 'json' <the install function's line range>` == 0), the `render.cpp` zero diff, the `harness/**` diff limited to c8's paths + the two pin lines, the `src/adapters/**` zero diff; each line `check=<name> rc=<n> expected=<n>`; `H.txt` = `git rev-parse HEAD`.

<!-- RUN: task-9 -->
```bash
# Runner plumbing (Task 9) — the grep-derived gates; the macOS count observation; the Linux parity leg for H and B (the R-4.49 container, Phases R/T/S);
# the E3 Linux witness read from the biv_tests XML; the harness-selftest population rule and, if the population moved, the 015244 interleaved series.
WORKTREE=/Users/jack/Programming/bivpak-intg-substep2b-wiring
MAIN=/Users/jack/Programming/bivpak
B=186adf7d67171bd7afe621f39b657a1a113ce299
cd "$WORKTREE" || STOP
v=0; (cd "$EVID" && shasum -a 256 -c helpers.sha256 > helpers.verify-9.txt 2>&1) || v=$?; [ "$v" -eq 0 ] || STOP
s=0; git status --porcelain > "$EVID/H/status-pre.txt" || s=$?; [ "$s" -eq 0 ] && [ ! -s "$EVID/H/status-pre.txt" ] || STOP
H=$(git rev-parse HEAD) || STOP; printf 'H=%s\n' "$H" > "$EVID/H.txt"
[ -s "$EVID/observer-unset-names.txt" ] && [ -s "$EVID/llvm-manifest.txt" ] || STOP
# Step 1 — E2 / E5 / network class / S1
g=0; git grep -n -E 'repo::(discover|classify|run_eligibility|capture|restore_entry)\(' HEAD -- src ':!src/core/repo' > "$EVID/H/E2-census.raw" || g=$?; [ "$g" -eq 0 ] && [ -s "$EVID/H/E2-census.raw" ] || STOP
s=0; sed 's/^HEAD://' "$EVID/H/E2-census.raw" > "$EVID/H/E2-census.txt" || s=$?; [ "$s" -eq 0 ] && [ -s "$EVID/H/E2-census.txt" ] || STOP
g=0; git grep -n -E 'run_eligibility|restore_entry|repo::discover|repo::classify|repo::capture' HEAD -- src ':!src/core/repo' > "$EVID/H/E5-grep.raw" || g=$?; [ "$g" -eq 0 ] || STOP
s=0; sed 's/^HEAD://' "$EVID/H/E5-grep.raw" > "$EVID/H/E5-grep.txt" || s=$?; [ "$s" -eq 0 ] || STOP
s=0; cut -d: -f1,2 "$EVID/H/E5-grep.txt" | LC_ALL=C sort -u > "$EVID/H/E5-sites.txt" || s=$?; [ "$s" -eq 0 ] || STOP
s=0; cut -d: -f1,2 "$EVID/H/E2-census.txt" | LC_ALL=C sort -u > "$EVID/H/E2-sites.txt" || s=$?; [ "$s" -eq 0 ] || STOP
d=0; diff "$EVID/H/E2-sites.txt" "$EVID/H/E5-sites.txt" > "$EVID/H/E5-flip.txt" || d=$?; [ "$d" -eq 0 ] || STOP
g=0; git grep -n 'GitCallClass::network' HEAD -- src > "$EVID/H/network-class-H.raw" || g=$?; [ "$g" -eq 0 ] || STOP; s=0; sed 's/^HEAD://' "$EVID/H/network-class-H.raw" > "$EVID/H/network-class-H.txt" || s=$?; [ "$s" -eq 0 ] || STOP
g=0; git grep -n 'GitCallClass::network' "$B" -- src > "$EVID/H/network-class-B.raw" || g=$?; [ "$g" -eq 0 ] || STOP; s=0; sed "s/^${B}://" "$EVID/H/network-class-B.raw" > "$EVID/H/network-class-B.txt" || s=$?; [ "$s" -eq 0 ] || STOP
d=0; diff "$EVID/H/network-class-B.txt" "$EVID/H/network-class-H.txt" > "$EVID/H/network-class.delta" || d=$?; [ "$d" -eq 0 ] || STOP
g=0; git grep -n -E 'posix_spawn|execv|popen|std::system|fork\(' HEAD -- src ':!src/core/repo' ':!src/core/support' > "$EVID/H/S1-nospawn.txt" || g=$?; [ "$g" -eq 1 ] && [ ! -s "$EVID/H/S1-nospawn.txt" ] || STOP
# Step 2 — veto 9 mechanical; the RepoEntry census; the zero-byte fences; the fabric census
: > "$EVID/H/veto9.txt"; first=1
for c in $(git log --reverse --format=%H "$B..HEAD"); do
  git diff-tree --no-commit-id --name-only -r "$c" > "$EVID/work/paths-$c.txt" || STOP
  e=0; ne=$(grep -c -E '^src/core/repo/' "$EVID/work/paths-$c.txt") || e=$?; [ "$e" -le 1 ] || STOP
  s=0; ns=$(grep -c -E '^(src/cli|src/core/pack|src/core/scan|src/core/open)/' "$EVID/work/paths-$c.txt") || s=$?; [ "$s" -le 1 ] || STOP
  if [ "$first" -eq 1 ]; then [ "$ne" -ge 1 ] && [ "$ns" -eq 0 ] || STOP; o=0; grep -v -E '^(src/core/repo/eligibility\.(hpp|cpp)|tests/test_repo_engine\.cpp)$' "$EVID/work/paths-$c.txt" > "$EVID/work/paths-$c.other" || o=$?; [ "$o" -eq 1 ] && [ ! -s "$EVID/work/paths-$c.other" ] || STOP; first=0; else [ "$ne" -eq 0 ] || STOP; fi
  [ "$ne" -eq 0 ] || [ "$ns" -eq 0 ] || STOP
  printf '%s engine=%s callsite=%s\n' "$c" "$ne" "$ns" >> "$EVID/H/veto9.txt"
done
[ -s "$EVID/H/veto9.txt" ] || STOP
g=0; git grep -n -E '\.(id|relpath|kind|sha|branch|head_state|capture_mode|eligibility|local_refs|local_refs_bundle|bundle|capture|shallow|notes|remotes|remote|parent_id|dirty|promisor|engine_source) *= ' HEAD -- src/cli src/core/pack src/core/scan src/core/open > "$EVID/H/repoentry-census.txt" || g=$?; [ "$g" -eq 1 ] && [ ! -s "$EVID/H/repoentry-census.txt" ] || STOP
z=0; git diff --stat "$B" HEAD -- src/core/manifest src/adapters harness/bivharness src/core/open/render.cpp > "$EVID/H/zero-byte-fences.txt" || z=$?; [ "$z" -eq 0 ] && [ ! -s "$EVID/H/zero-byte-fences.txt" ] || STOP
n=0; git diff --numstat 3cd31e4 HEAD -- CMakeLists.txt harness/selftest/test_envelope.py schemas/biv-exit-map.v1.json schemas/biv-json-envelope.v1.schema.json src/cli/args.cpp src/cli/args.hpp src/cli/main.cpp src/cli/url_consent.cpp src/cli/url_consent.hpp src/core/open/open.hpp src/core/pack/pack.hpp src/core/report/envelope.cpp src/core/report/envelope.hpp src/core/support/error.cpp src/core/support/error.hpp src/core/support/url_divergence.hpp tests/test_cli.cpp tests/test_envelope.cpp > "$EVID/H/fabric-census-3cd31e4-H.txt" || n=$?; [ "$n" -eq 0 ] || STOP
# Step 3 — macOS observation at H (a MOVED biv_tests cell is data here)
b=0; cmake --build --preset ci-macos > "$EVID/H/build-H.log" 2>&1 || b=$?; [ "$b" -eq 0 ] || STOP
for binary in biv_subprocess_tests biv_repo_git_tests biv_repo_engine_tests biv_tests biv_probe_tests; do x=0; "./build/ci-macos/$binary" -r xml > "$EVID/H/$binary-macos.xml" 2> "$EVID/H/$binary-macos.stderr" || x=$?; printf '%s rc=%s\n' "$binary" "$x" >> "$EVID/H/run-rcs-macos.txt"; [ -s "$EVID/H/$binary-macos.xml" ] || STOP; done
u=0; python3 "$EVID/tuples.py" macos "$EVID"/H/biv_subprocess_tests-macos.xml "$EVID"/H/biv_repo_git_tests-macos.xml "$EVID"/H/biv_repo_engine_tests-macos.xml "$EVID"/H/biv_tests-macos.xml "$EVID"/H/biv_probe_tests-macos.xml > "$EVID/H/tuples-macos.txt" || u=$?; [ "$u" -eq 0 ] && [ -s "$EVID/H/tuples-macos.txt" ] || STOP
c=0; python3 "$EVID/cellgate.py" "$EVID/B-cells.txt" macos "$EVID/H/tuples-macos.txt" > "$EVID/H/count-gate-macos.txt" 2>&1 || c=$?; printf 'count_gate_macos_rc=%s\n' "$c" > "$EVID/H/count-gate-macos.rc"; [ "$c" -eq 0 ] || [ "$c" -eq 5 ] || STOP
q=0; python3 "$EVID/skipset.py" "$EVID/B-cells.txt" "$EVID/H/tuples-macos.txt" macos > "$EVID/H/skipset-macos.txt" || q=$?; printf 'skipset_macos_rc=%s\n' "$q" > "$EVID/H/skipset-macos.rc"
# Step 4 — the Linux parity leg: the pinned clang-tidy mirror assets, then the container at H and at B
LLVM_RAW=$(mktemp -d "$EVID/llvm22-assets-H.XXXXXX") || STOP; LLVM_DIR=$(cd "$LLVM_RAW" && pwd -P) || STOP; c=0; cp "$EVID/llvm-manifest.txt" "$LLVM_DIR/MANIFEST" || c=$?; [ "$c" -eq 0 ] || STOP
h=0; while read -r _ package asset; do gh release download toolchain-mirror-clang-tidy-22-immutable-v1 --repo iwnlcern/bivpak --pattern "$asset" --dir "$LLVM_DIR" || h=$?; done < "$LLVM_DIR/MANIFEST" > "$EVID/H/llvm-transport.log" 2>&1
a=0; awk '{ print $1 "  " $3 }' "$LLVM_DIR/MANIFEST" > "$LLVM_DIR/SHA256SUMS" || a=$?; [ "$a" -eq 0 ] && [ -s "$LLVM_DIR/SHA256SUMS" ] || STOP; v=0; (cd "$LLVM_DIR" && shasum -a 256 -c SHA256SUMS) > "$EVID/H/llvm-verify.txt" 2>&1 || v=$?; printf 'llvm_transport_rc=%s verify_rc=%s\n' "$h" "$v" > "$EVID/H/llvm.rc"; [ "$h" -eq 0 ] && [ "$v" -eq 0 ] || STOP
for LABEL in H B; do
  if [ "$LABEL" = H ]; then EXP=$H; else EXP=$B; fi
  o=0; docker run --rm --platform linux/amd64 --init -v "${LLVM_DIR}:/llvm-mirror:ro" -v "${MAIN}:/repo-ro:ro" -v "${EVID}:/evidence" ubuntu:24.04 bash /evidence/linux-container.sh "$EXP" "$LABEL" > "$EVID/$LABEL/linux-container.log" 2>&1 || o=$?; printf '%s\n' "$o" > "$EVID/$LABEL/linux-container.rc"; [ "$o" -eq 0 ] || STOP
  for f in linux-ledger.txt linux-suite-ledger.txt linux-nofile.txt linux-run-head-receipt.txt container-payload.rc "ctest-linux-$LABEL.log" "ctest-linux-$LABEL.rc" "ctest-linux-$LABEL.junit.xml" biv_subprocess_tests-linux.xml biv_repo_git_tests-linux.xml biv_repo_engine_tests-linux.xml biv_tests-linux.xml biv_probe_tests-linux.xml; do [ -s "$EVID/$LABEL/$f" ] || STOP; done
  [ "$(cat "$EVID/$LABEL/container-payload.rc")" = container_payload_rc=0 ] || STOP
  for x in phase_R_base_provision_rc=0 phase_R_asset_provision_rc=0 phase_T_transition_fixture_rc=0 phase_S_suite_rc=0; do g=0; k=$(grep -c -x -F -- "$x" "$EVID/$LABEL/linux-ledger.txt") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP; done
  g=0; k=$(grep -c -x -F 'suite_aggregate_rc=0 ledger_write_failed=0' "$EVID/$LABEL/linux-suite-ledger.txt") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP
  g=0; k=$(grep -c -E '^nofile_soft_equals_hard_rc=0$' "$EVID/$LABEL/linux-suite-ledger.txt") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP
  u=0; python3 "$EVID/tuples.py" linux "$EVID"/$LABEL/biv_subprocess_tests-linux.xml "$EVID"/$LABEL/biv_repo_git_tests-linux.xml "$EVID"/$LABEL/biv_repo_engine_tests-linux.xml "$EVID"/$LABEL/biv_tests-linux.xml "$EVID"/$LABEL/biv_probe_tests-linux.xml > "$EVID/$LABEL/tuples-linux.txt" || u=$?; [ "$u" -eq 0 ] && [ -s "$EVID/$LABEL/tuples-linux.txt" ] || STOP
  x=0; python3 "$EVID/selftest_summary.py" "$EVID/$LABEL/ctest-linux-$LABEL.junit.xml" "$EVID/$LABEL/selftest-$LABEL" > "$EVID/$LABEL/selftest-$LABEL.out" || x=$?; [ "$x" -eq 0 ] && [ -s "$EVID/$LABEL/selftest-$LABEL.kv" ] || STOP
  s=0; sed -n 's/^population=//p' "$EVID/$LABEL/selftest-$LABEL.kv" > "$EVID/H/selftest-population-$LABEL.txt" || s=$?; [ "$s" -eq 0 ] && [ -s "$EVID/H/selftest-population-$LABEL.txt" ] || STOP
  c=0; cat -- "$EVID/$LABEL/linux-container.log" "$EVID/$LABEL/phase-R-base.log" "$EVID/$LABEL/phase-R-assets.log" "$EVID/$LABEL/phase-T-transition.log" "$EVID/$LABEL/phase-S-suite.log" "$EVID/$LABEL/ctest-linux-$LABEL.log" "$EVID"/$LABEL/*-linux.stderr > "$EVID/$LABEL/all-logs-linux.txt" || c=$?; [ "$c" -eq 0 ] || STOP
  g=0; hits=$(grep -c -E 'sk-[A-Za-z0-9]{8,}|-----BEGIN [A-Z ]*PRIVATE KEY|AKIA[0-9A-Z]{16}|ghp_[A-Za-z0-9]{20,}|xox[abprs]-' "$EVID/$LABEL/all-logs-linux.txt") || g=$?; [ "$g" -le 1 ] && [ "$hits" -eq 0 ] || STOP
done
c=0; python3 "$EVID/cellgate.py" "$EVID/B-cells.txt" linux "$EVID/H/tuples-linux.txt" > "$EVID/H/count-gate-linux.txt" 2>&1 || c=$?; printf 'count_gate_linux_rc=%s\n' "$c" > "$EVID/H/count-gate-linux.rc"; [ "$c" -eq 0 ] || [ "$c" -eq 5 ] || STOP
c=0; python3 "$EVID/cellgate.py" "$EVID/B-cells.txt" linux "$EVID/B/tuples-linux.txt" > "$EVID/B/count-gate-linux.txt" 2>&1 || c=$?; [ "$c" -eq 0 ] || STOP
c=0; python3 "$EVID/cellgate.py" "$EVID/B-cells.txt" macos "$EVID/B/tuples-macos.txt" > "$EVID/B/count-gate-macos.txt" 2>&1 || c=$?; [ "$c" -eq 0 ] || STOP
x=0; python3 - "$EVID/H/biv_tests-linux.xml" > "$EVID/H/E3-linux.txt" <<'PY' || x=$?
import sys, xml.etree.ElementTree as ET
root = ET.fromstring(open(sys.argv[1], "rb").read())
rows = [(tc.get("name"), tc.find("OverallResult").get("success")) for tc in root.iter("TestCase") if "[E3]" in (tc.get("tags") or "")]
if not rows: sys.exit(3)
for name, ok in rows: print("E3 linux case=%r success=%s" % (name, ok))
sys.exit(0 if all(ok == "true" for _, ok in rows) else 5)
PY
printf 'e3_linux_rc=%s\n' "$x" > "$EVID/H/E3-linux.rc"; [ "$x" -eq 0 ] || STOP
p=0; cmp "$EVID/H/selftest-population-B.txt" "$EVID/H/selftest-population-H.txt" > "$EVID/H/selftest-population.cmp" 2>&1 || p=$?; printf 'population_equal_rc=%s\n' "$p" > "$EVID/H/selftest-population.rc"
printf 'selftest/test_e3_asserts.py::test_file_reader_rejects_same_size_cross_chunk_in_place_rewrite\nselftest/test_e3_asserts.py::test_c1_zero_session_control_reds_on_file_inserted_at_scandir_stop\nselftest/test_e3_asserts.py::test_credential_scanner_detects_entry_added_after_directory_enumeration\nselftest/test_e3_asserts.py::test_run_e3_session_inserted_at_scandir_stop_reds_c1_before_open\n' > "$EVID/H/r435-family.txt"
if [ "$p" -ne 0 ]; then
  m=0; mkdir -p "$EVID/series" || m=$?; [ "$m" -eq 0 ] || STOP
  for i in 1 2 3 4 5 6 7 8 9 10; do
    for T in B H; do
      LABEL="$T-$i"; if [ "$T" = H ]; then EXP=$H; else EXP=$B; fi
      m=0; mkdir -p "$EVID/series/$LABEL" || m=$?; [ "$m" -eq 0 ] || STOP
      o=0; docker run --rm --platform linux/amd64 --init -v "${LLVM_DIR}:/llvm-mirror:ro" -v "${MAIN}:/repo-ro:ro" -v "${EVID}/series:/evidence" -v "${EVID}/linux-container.sh:/evidence/linux-container.sh:ro" -v "${EVID}/linux-suite.sh:/evidence/linux-suite.sh:ro" -v "${EVID}/observer-unset-names.txt:/evidence/observer-unset-names.txt:ro" ubuntu:24.04 bash /evidence/linux-container.sh "$EXP" "$LABEL" > "$EVID/series/$LABEL/linux-container.log" 2>&1 || o=$?; printf '%s\n' "$o" > "$EVID/series/$LABEL/linux-container.rc"; [ "$o" -eq 0 ] || STOP
      x=0; python3 "$EVID/selftest_summary.py" "$EVID/series/$LABEL/ctest-linux-$LABEL.junit.xml" "$EVID/series/$LABEL/selftest-$LABEL" > "$EVID/series/$LABEL/selftest-$LABEL.out" || x=$?; [ "$x" -eq 0 ] || STOP
    done
  done
  s=0; python3 "$EVID/series_verdict.py" "$EVID/series" "$EVID/H/r435-family.txt" 10 > "$EVID/H/selftest-series.txt" 2>&1 || s=$?; printf 'series_rc=%s\n' "$s" > "$EVID/H/selftest-series.rc"; [ "$s" -eq 0 ] || STOP
fi
# Step 5 — count cells: data for the companion commit (the edit + c9 + the FINAL gate re-run are the implementer's code-discipline step 5b)
if grep -q -E '^MOVED' "$EVID/H/count-gate-macos.txt" "$EVID/H/count-gate-linux.txt"; then
  printf 'count-cells-moved: edit ONLY the moved literals in .github/workflows/s2-harness.yml, commit as c9, then run cells.py on the edited file and cellgate.py <H-cells> <target> <H tuples> for BOTH targets; write count_gate_final_<target>_rc=0 into H/count-gate-final-<target>.rc; record c9 in commits.c9.txt\n' > "$EVID/H/count-gate.txt"
else
  printf 'unchanged\n' > "$EVID/H/count-gate.txt"; printf 'count_gate_final_macos_rc=0\n' > "$EVID/H/count-gate-final-macos.rc"; printf 'count_gate_final_linux_rc=0\n' > "$EVID/H/count-gate-final-linux.rc"
fi
s=0; git status --porcelain > "$EVID/H/status-post-9.txt" || s=$?; [ "$s" -eq 0 ] && [ ! -s "$EVID/H/status-post-9.txt" ] || STOP
exit 0
```

### Task 10 — the vehicle (ONLY after the pair Planner's GO relay carrying m-1's, m-3's and m-4's byte-review words through master with no red): ONE push, ONE PR

Protocol (e): before `run-task.sh 10` the operator's ONE typed act is the GO relay's path into `$RUNNERS/task-10-go.txt`; the runner's FIRST gate binds the GO relay (an engine-filed SITREP in `.relays/intg/intg-substep2b/`, `FROM: intg.pair-planner`, `TO: intg.pair-implementer`, `TASK10_GO: yes`, `TASK10_H: <sha>`, and three `OWNER_REVIEW_H: <path> | FROM=<m-1|m-3|m-4 seat> | VERDICT=no-red` lines whose relays exist under `../pdc/master/relays/`, each carrying `S2B_REVIEW_OBJECT: H=<sha>` and `S2B_REVIEW_VERDICT: no-red`).

- [ ] **Step 1: the gate, then preconditions** — HEAD == H; the GO relay bound as above; `census-tree.delta`-class receipts of Task 9 present with rc 0 (`count-gate-*.rc` both `0` AFTER any c9; `linux-leg.rc` 0; `selftest-population.rc` 0 OR `selftest-series.txt` with a PASS verdict); `git remote get-url --push origin` recorded; `git ls-remote --heads origin intg/substep2b-wiring` EMPTY; `gh repo view --json visibility` == PRIVATE; no executable `pre-push` hook.
- [ ] **Step 2: ONE push** — `git push --dry-run --no-tags origin intg/substep2b-wiring` (the refspec line exactly once) then the one attempt; class a (remote head == H) or STOP.
- [ ] **Step 3: the PR** — `pr-body.md` from the record files (B, H, the commit list c1..c9 with owners, the E2 census, the E5 flip, veto-9, the count-gate rows, the E3 receipts both platforms, the E4 parity receipt, the harness receipt, the registered S-6 rows, the contingent terms' lock ids); the census alternation over the body → 0 hits; `gh pr create --base main --head intg/substep2b-wiring --title "pack/open: wire the repo engine and the consent fabric at product scope (sub-step 2b)" --body-file pr-body.md --draft`; `pr.rc`; the PR number and URL recorded. The PR stays a DRAFT until the operator's merge token (the undraft is a P5 publication-lifecycle act that returns to the operator — never self-granted).

<!-- RUN: task-10 -->
```bash
# Runner plumbing (Task 10)
WORKTREE=/Users/jack/Programming/bivpak-intg-substep2b-wiring
MAIN=/Users/jack/Programming/bivpak
B=186adf7d67171bd7afe621f39b657a1a113ce299
cd "$WORKTREE" || STOP
v=0; (cd "$EVID" && shasum -a 256 -c helpers.sha256 > helpers.verify-10.txt 2>&1) || v=$?; [ "$v" -eq 0 ] || STOP
H=$(cat "$EVID/H.txt" | sed 's/^H=//') || STOP; [ "$(git rev-parse HEAD)" = "$H" ] || STOP
[ -s "$RUNNERS/task-10-go.txt" ] || STOP; a=0; ng=$(awk 'END { print NR }' "$RUNNERS/task-10-go.txt") || a=$?; [ "$a" -eq 0 ] && [ "$ng" -eq 1 ] || STOP; GO=$(sed -n '1p' "$RUNNERS/task-10-go.txt") || STOP; [ -s "$GO" ] || STOP
GOD=$(cd "$(dirname "$GO")" && pwd -P) || STOP; RR=$(cd "$MAIN/.relays/intg/intg-substep2b" && pwd -P) || STOP; [ "$GOD" = "$RR" ] || STOP
GOB=$(basename "$GO") || STOP; case "$GOB" in SITREP-pair-planner-[0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9]-[0-9][0-9][0-9][0-9][0-9][0-9].md) :;; *) STOP;; esac
g=0; k=$(grep -c -F -- "intg-substep2b/$GOB" "$MAIN/.relays/intg/INDEX.md") || g=$?; [ "$g" -eq 0 ] && [ "$k" -ge 1 ] || STOP
for pat in '^FROM: intg\.pair-planner$' '^TO: intg\.pair-implementer$' '^PHASE: SITREP$' '^TASK10_GO: yes$'; do g=0; k=$(grep -c -E "$pat" "$GO") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP; done
g=0; k=$(grep -c -x -F -- "TASK10_H: $H" "$GO") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP
PDC=$(cd "$MAIN/../pdc/master/relays" && pwd -P) || STOP
g=0; k=$(grep -c -E '^OWNER_REVIEW_H: [^ |]+ \| FROM=m-(1|3|4)\.(planner|implementer) \| VERDICT=no-red$' "$GO") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 3 ] || STOP
: > "$EVID/task-10-go.txt"
while IFS= read -r line; do
  RP=$(printf '%s\n' "$line" | sed -n -E 's/^OWNER_REVIEW_H: ([^ |]+) \| FROM=([^ |]+) \| VERDICT=no-red$/\1/p'); RF=$(printf '%s\n' "$line" | sed -n -E 's/^OWNER_REVIEW_H: [^ |]+ \| FROM=([^ |]+) \| VERDICT=no-red$/\1/p'); [ -n "$RP" ] && [ -n "$RF" ] || STOP
  case "$RP" in /*) R=$RP;; *) R=$MAIN/$RP;; esac; [ -s "$R" ] || STOP; RD=$(cd "$(dirname "$R")" && pwd -P) || STOP; case "$RD" in "$PDC"/*) :;; *) STOP;; esac
  g=0; k=$(grep -c -x -F -- "FROM: $RF" "$R") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP
  g=0; k=$(grep -c -x -F -- "S2B_REVIEW_OBJECT: H=$H" "$R") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP
  g=0; k=$(grep -c -x -F -- 'S2B_REVIEW_VERDICT: no-red' "$R") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP
  g=0; k=$(grep -c -i -E '^([A-Z0-9_]*VERDICT|STATUS): *(must-revise|reject|reject-narrow|red|blocked|pending|hold|human-decision-required)' "$R") || g=$?; [ "$g" -eq 1 ] && [ "$k" -eq 0 ] || STOP
  printf 'owner_review=%s FROM=%s\n' "$R" "$RF" >> "$EVID/task-10-go.txt"
done < <(grep -E '^OWNER_REVIEW_H: ' "$GO")
[ "$(cat "$EVID/H/count-gate-final-macos.rc")" = count_gate_final_macos_rc=0 ] && [ "$(cat "$EVID/H/count-gate-final-linux.rc")" = count_gate_final_linux_rc=0 ] && [ "$(cat "$EVID/H/linux-container.rc")" = 0 ] && [ "$(cat "$EVID/B/linux-container.rc")" = 0 ] && [ "$(cat "$EVID/H/E3-linux.rc")" = e3_linux_rc=0 ] || STOP
if [ "$(cat "$EVID/H/selftest-population.rc")" != population_equal_rc=0 ]; then [ -s "$EVID/H/selftest-series.txt" ] || STOP; g=0; k=$(grep -c -E '^VERDICT PASS' "$EVID/H/selftest-series.txt") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP; fi
u=0; git remote get-url --push --all origin > "$EVID/push-url.txt" || u=$?; [ "$u" -eq 0 ] && [ -s "$EVID/push-url.txt" ] || STOP
l=0; git ls-remote --heads origin intg/substep2b-wiring > "$EVID/remote-branch-before.txt" || l=$?; [ "$l" -eq 0 ] && [ ! -s "$EVID/remote-branch-before.txt" ] || STOP
v=0; gh repo view --json visibility -q .visibility > "$EVID/visibility.txt" || v=$?; [ "$v" -eq 0 ] && [ "$(cat "$EVID/visibility.txt")" = PRIVATE ] || STOP
[ ! -x "$(git rev-parse --git-path hooks/pre-push)" ] || STOP
# Step 2 — ONE push
y=0; git push --dry-run --no-tags origin intg/substep2b-wiring > "$EVID/push-dry.txt" 2>&1 || y=$?; [ "$y" -eq 0 ] || STOP
g=0; k=$(grep -c -F 'intg/substep2b-wiring -> intg/substep2b-wiring' "$EVID/push-dry.txt") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP
p=0; git push --no-tags origin intg/substep2b-wiring > "$EVID/push-stdout.txt" 2> "$EVID/push-stderr.txt" || p=$?; printf 'push_rc=%s\n' "$p" > "$EVID/push-rc.txt"
o=0; git ls-remote --heads origin intg/substep2b-wiring > "$EVID/remote-branch-after.txt" || o=$?; remote_after=$(cut -f1 "$EVID/remote-branch-after.txt")
if [ "$o" -ne 0 ]; then class=d; elif [ "$p" -eq 0 ] && [ "$remote_after" = "$H" ]; then class=a; elif [ "$p" -eq 0 ]; then class=e; elif [ "$remote_after" = "$H" ]; then class=c; elif [ -z "$remote_after" ]; then class=b; else class=f; fi
printf 'class=%s\n' "$class" > "$EVID/push-class.txt"; [ "$class" = a ] || STOP
# Step 3 — the PR (draft)
w=0; python3 "$EVID/finalize.py" prbody "$EVID" "$B" "$H" > "$EVID/pr-body.md" || w=$?; [ "$w" -eq 0 ] && [ -s "$EVID/pr-body.md" ] || STOP
g=0; k=$(grep -c -E 'sk-[A-Za-z0-9]{8,}|-----BEGIN [A-Z ]*PRIVATE KEY|AKIA[0-9A-Z]{16}|ghp_[A-Za-z0-9]{20,}|xox[abprs]-' "$EVID/pr-body.md") || g=$?; [ "$g" -eq 1 ] && [ "$k" -eq 0 ] || STOP
q=0; gh pr create --base main --head intg/substep2b-wiring --title "pack/open: wire the repo engine and the consent fabric at product scope (sub-step 2b)" --body-file "$EVID/pr-body.md" --draft > "$EVID/pr-create.txt" 2>&1 || q=$?; printf 'pr_rc=%s\n' "$q" > "$EVID/pr.rc"; [ "$q" -eq 0 ] || STOP
exit 0
```

### Task 11 — FINALIZE the tracked record `results/s2b-<token>/` and the merge-packet inputs; the census rehearsal at H; the population template FOR the merge head

- [ ] **Step 1: preconditions** — Task 10 done/exit/proof receipts; push class a; PR created; the results dir absent.
- [ ] **Step 2: the census rehearsal at H (the R-4.49 instrument at its exact pin)** — `results/intg-r449-landing-census.sh` re-hashed == `9c9391d5…` (the pinned sha256 recorded in `results/intg-r449-merge-gate.md` §8) or STOP; run `<instrument> H <population-for-H> "$EVID/census-raw/H" B` where `<population-for-H>` is PRODUCED on H by the instrument's own producer lines (the census contract: population written for the object scanned, never carried); PASS; the merge head's population is produced AT LANDING on `main`'s post-merge head by the same instrument under the operator's token (the R-4.50 lesson) — this plan writes the TEMPLATE file `results/intg-substep2b-main-head-census-<date>.txt` with the header only; the body is the landing act's.
- [ ] **Step 3: the set, then its classification INTO the record** — `finalize.py list` (no `work/` or `census-raw/` path); the census alternation over every set file → 0 foreign hits (fixture-token copies classified as in the R-4.49 record); the copy under `results/s2b-<token>/`; `SHA256SUMS` (`LC_ALL=C sort -k2`); `finalize.py check` rc 0; `shasum -c` rc 0.
- [ ] **Step 4: the merge-packet inputs** — `results/intg-substep2b-merge-gate.md` (rev1 DRAFT by the pair Planner, in the docs lane): B, H, c1..c9 with owners, the evidence matrix rows → receipt paths, the three owner byte-review relays, m-4's cell-(v) inputs, the count-gate rows, the registered S-6 rows, the contingent terms' lock ids, the census rehearsal, the four-condition bar.

<!-- RUN: task-11 -->
```bash
# Runner plumbing (Task 11)
WORKTREE=/Users/jack/Programming/bivpak-intg-substep2b-wiring
MAIN=/Users/jack/Programming/bivpak
B=186adf7d67171bd7afe621f39b657a1a113ce299
cd "$WORKTREE" || STOP
v=0; (cd "$EVID" && shasum -a 256 -c helpers.sha256 > helpers.verify-11.txt 2>&1) || v=$?; [ "$v" -eq 0 ] || STOP
[ -s "$EVID/runners/task-10.done" ] && [ "$(cat "$EVID/runners/task-10.done")" = rc=0 ] || STOP; [ -s "$EVID/push-class.txt" ] && [ "$(cat "$EVID/push-class.txt")" = class=a ] || STOP; [ -s "$EVID/pr.rc" ] && [ "$(cat "$EVID/pr.rc")" = pr_rc=0 ] || STOP
TOKEN=$(sed -n 's/^token=//p' "$EVID/token.txt"); [ -n "$TOKEN" ] || STOP; RESDIR=$MAIN/docs/sprints/2026-08-27-intg-consent-fabric/results/s2b-${TOKEN}; [ ! -e "$RESDIR" ] || STOP
H=$(sed 's/^H=//' "$EVID/H.txt") || STOP
# Step 2 — the census rehearsal at H with the pinned instrument
INST=$MAIN/docs/sprints/2026-08-27-intg-consent-fabric/results/intg-r449-landing-census.sh; [ -s "$INST" ] || STOP
PIN=$(sed -n -E 's/^.*instrument sha256[^0-9a-f]*([0-9a-f]{64}).*$/\1/p' "$MAIN/docs/sprints/2026-08-27-intg-consent-fabric/results/intg-r449-merge-gate.md" | head -1); [ -n "$PIN" ] || STOP
h=0; ACT=$(shasum -a 256 "$INST" | cut -d' ' -f1) || h=$?; [ "$h" -eq 0 ] && [ "$ACT" = "$PIN" ] || STOP
m=0; mkdir -p "$EVID/census-raw/H" || m=$?; [ "$m" -eq 0 ] || STOP
c=0; bash "$INST" "$H" "$EVID/census-raw/H/population-H.txt" "$EVID/census-raw/H" "$B" > "$EVID/H/census-rehearsal.log" 2>&1 || c=$?; printf 'census_rehearsal_rc=%s\n' "$c" > "$EVID/H/census-rehearsal.rc"; [ "$c" -eq 0 ] || STOP
# Step 3 — the record
x=0; python3 "$EVID/finalize.py" list "$EVID" > "$RUNNERS/final-set.txt" || x=$?; [ "$x" -eq 0 ] && [ -s "$RUNNERS/final-set.txt" ] || STOP
g=0; k=$(grep -c -E '^(work/|census-raw/)' "$RUNNERS/final-set.txt") || g=$?; [ "$g" -eq 1 ] && [ "$k" -eq 0 ] || STOP
ALT='sk-[A-Za-z0-9]{8,}|-----BEGIN [A-Z ]*PRIVATE KEY|AKIA[0-9A-Z]{16}|ghp_[A-Za-z0-9]{20,}|xox[abprs]-'
: > "$EVID/census-raw/record-hits.raw"; while IFS= read -r f; do g=0; grep -o -E "$ALT" "$EVID/$f" >> "$EVID/census-raw/record-hits.raw" || g=$?; [ "$g" -le 1 ] || STOP; done < "$RUNNERS/final-set.txt"
r=0; git grep -h -o -E "$ALT" "$B" -- tests/test_adapter_codex_collect.cpp tests/test_cli.cpp > "$EVID/census-raw/fixture-tokens.raw" || r=$?; [ "$r" -eq 0 ] || STOP
o=0; LC_ALL=C sort -u "$EVID/census-raw/record-hits.raw" > "$EVID/census-raw/record-hits.set" || o=$?; [ "$o" -eq 0 ] || STOP; o=0; LC_ALL=C sort -u "$EVID/census-raw/fixture-tokens.raw" > "$EVID/census-raw/fixture-tokens.set" || o=$?; [ "$o" -eq 0 ] || STOP
c=0; LC_ALL=C comm -23 "$EVID/census-raw/record-hits.set" "$EVID/census-raw/fixture-tokens.set" > "$EVID/census-raw/foreign.set" || c=$?; [ "$c" -eq 0 ] && [ ! -s "$EVID/census-raw/foreign.set" ] || STOP
nd=$(awk 'END { print NR }' "$EVID/census-raw/record-hits.set") || STOP; printf 'distinct_matched_strings=%s foreign_matched_strings=0 class=B-fixture-copies-only\n' "$nd" > "$EVID/record-token-classes.txt"
m=0; mkdir -p "$RESDIR" || m=$?; [ "$m" -eq 0 ] && [ -d "$RESDIR" ] || STOP
c=0; while IFS= read -r f; do d=$(dirname "$f") && mkdir -p "$RESDIR/$d" && cp -p "$EVID/$f" "$RESDIR/$f" || { c=1; break; }; done < "$RUNNERS/final-set.txt"; [ "$c" -eq 0 ] || STOP
h=0; (cd "$RESDIR" && find . -type f ! -name SHA256SUMS -exec shasum -a 256 {} + > "$RUNNERS/final-manifest.unsorted") || h=$?; [ "$h" -eq 0 ] && [ -s "$RUNNERS/final-manifest.unsorted" ] || STOP; o=0; LC_ALL=C sort -k2 "$RUNNERS/final-manifest.unsorted" > "$RESDIR/SHA256SUMS" || o=$?; [ "$o" -eq 0 ] || STOP
k=0; python3 "$EVID/finalize.py" check "$EVID" "$RESDIR" "$RESDIR/SHA256SUMS" > "$RUNNERS/final-verdict.txt" 2>&1 || k=$?; printf 'finalize_check_rc=%s\n' "$k" > "$RUNNERS/final-verdict.rc"; [ "$k" -eq 0 ] || STOP
v=0; (cd "$RESDIR" && shasum -a 256 -c --quiet SHA256SUMS) > "$RUNNERS/final-shasum-c.txt" 2>&1 || v=$?; [ "$v" -eq 0 ] || STOP
exit 0
```

### Task 12 — the commission-closure SITREP (the pair Planner's; AFTER the verified landing under the operator's token and R-4.52)

- [ ] The final pin (`main`'s post-merge head == `origin/main`); the FOUR worktrees disposed with receipts (Task 0's three + `../bivpak-intg-substep2b-wiring` after landing, one receipt); the evidence homes sealed and named (`results/s2b-<token>/` + the R-4.49 record); the census FOR the merge head PASS; the open residuals handed to owners BY ROW (T-K, T-C if registered, T-NET, T-PROM, I2B-09 (b), anything an owner STOP left); no further act routes to the pair without a fresh commission.

## Acceptance criteria (each measured, none inferred)

1. `git log --reverse B..H` reads c1 (engine only) first; no later commit touches `src/core/repo/`; no commit spans both sets (`H/veto9.txt`).
2. E2 census non-empty; E5's grep at H equals E2's site set exactly; the network-class census unchanged (six engine lines); S1 spawn grep EMPTY outside `src/core/repo`/`src/core/support`.
3. Every FX leg named in the evidence matrix has a `legs/<id>.txt` receipt with `provenance=product-packed verdict=PASS`, or a line in `legs/registered.txt` naming its S-6 owner; the open-side legs' hand-built interim receipts are NOT cited by the packet.
4. a8·1–a8·4 pass on all eleven rows; the A8 census shows every bound value wrapped exactly once; `render.cpp` diff EMPTY; the table header carries `Unicode 15.0.0` + both input digests + the generator digest, and regenerating from `tools/` reproduces it byte-for-byte.
5. The hook install has three rows and no `json`/`offline`/`network` term; `grep -c 'isatty(' src/cli/main.cpp` == 0.
6. `UnclaimedGitEntry` lands only with m-3's lock id in its commit message; the exit map is 29 rows; `RepoDiscoveredUnsupported` absent from `src/`, `schemas/`, `tests/`; the selftest pins recomputed in the same commits that changed the schema bytes.
7. Count gate: observed case tuples at H on both platforms equal the workflow cells (after c9 iff owed); skip sets unchanged; the harness-selftest population equal at B and H OR the 015244 series' `VERDICT PASS`.
8. E3 receipts on both platforms; E4 parity receipt; the harness receipt (both scenarios green on macOS; m-3's commit limited to `harness/scenarios/**`).
9. Cut-point `origin/main..B` = 0 at Task 0; the branch pushed class a; the PR open (draft) against `main` with head H; `main` NOT pushed by this plan; the three worktrees disposed with receipts.
10. The three owners' byte reviews of H return through master with no red BEFORE Task 10 (protocol (e) in the runner).

## Out of scope (an act here is a STOP, not a judgement)

Any `src/core/repo` byte beyond Task 1; any `src/core/manifest` byte; any `src/adapters` or `harness/bivharness` byte; any `render.cpp` byte; any summary-line or warnings-row emission for consent (S-4); any persistence of an approval; any address classification or safety wording; any new argv/env/config surface beyond the two flags; any envelope member, kind, exit row or wording the sealed texts and the owner cuts do not determine (T-JSON's member and T-KIND's bytes wait on their words); a pack-level FX-O arm; the PR undraft; the merge; the push of `main`; any release act.

## Anti-half-fix guards

- The hook is installed ONCE per verb around the engine-reaching call; a second install site or a call-site-local prompt is red (V-A6-6's shape).
- A refusal at pack is `UrlDivergenceRefused` with facts, never `no_remote`, never a capture-mode change, never an advisory (M veto 4); a refusal at open is a ROW and the clean entries COMPLETE (a6·12).
- `manifest.repos` entries are the engine's objects, unmodified (the RepoEntry census); artifacts keep their `archive_path` (no renaming).
- `.git` is never a payload node; a repo subtree is excluded WHOLE; an unclaimed `.git` refuses typed with its reason — never a silent skip (V-2b-5/6).
- Offline means ZERO git and ZERO network on open (shim log), and no `ls-remote`/fetch on pack; the flags never touch PROMPT D (V-OFF).
- Hand-built-image receipts are interim; a packet row citing one is a defect.
- The census population is PRODUCED on the object scanned; never carried (R-4.50).
- No `Co-Authored-By` trailer; no root-mode relay-lint sweeps; no Monitor waiters.

## Instruments (BLOCKs — extracted from THIS plan by `plan_blocks.py extract`; the reused ones are byte-copies of the R-4.49 plan's proven instruments with only the act-specific literals changed, each change named)

- `plan_blocks.py`, `run-task.sh` — the runner protocol's two instruments (R-4.49 plan, verbatim except: `plan_blocks.py`'s three task-number regexes accept one or two digits (`[0-9]{1,2}`) because this plan's runner tasks are 0, 9, 10, 11; `run-task.sh` accepts N ∈ {0, 9, 10, 11}; the predecessor map is 9←0, 10←9, 11←10; the continuation gate is Task 10's `task-10-go.txt`).
- `cells.py`, `tuples.py`, `skipset.py`, `selftest_summary.py` — verbatim.
- `cellgate.py` — the 2b form: `cellgate.py <cells.txt> <target> <tuples.txt>` exits 0 iff every literal cell equals the observed tuple on `<target>`; prints one `MOVED <binary> literal=… observed=…` line per differing cell (data, not a STOP — a moved `biv_tests` cell is EXPECTED in this act and drives the companion commit) and `UNCHANGED <binary>` otherwise.
- `finalize.py` — verbatim except the finalizer receipts name Task 11, and the `prbody` subcommand (the PR body from the record files).
- `linux-container.sh` — the R-4.49 container (Phases R / T / S: base provision, the pinned clang-tidy-22 mirror assets, the non-root `suite` user, the branch clone at the expected head, the suite) with Phase L (the read-trace leg) REMOVED, the branch literal `intg/substep2b-wiring`, and labels `B`, `H`, `B-<n>`, `H-<n>` (the series draws).
- `linux-suite.sh` — verbatim except the label set.
- `git-shim.sh` — the request-trace instrument: first on the child's `PATH`, appends `argv` to `$BIV_GIT_TRACE` (one line per spawn, tab-separated, cwd first) and `exec`s the real git named by `$BIV_GIT_REAL`.
- `gen_consent_display_table.py` — the clause-5 table generator (deterministic; input digests and the generator's own digest in the header).
- `series_verdict.py` — the 015244 interleaved-series reducer over the 20 draws' `selftest-*.kv/.names` files (every draw valid; population equal within each tree; the candidate's failing names ⊆ the r435 family ∪ the base's observed names; at least one non-empty base observation; verdict PASS or STOP naming the fresh names). The pair Planner verifies this reducer against the `015244` bar text before Task 9 runs (Q14 in the plan's SITREP).

<!-- BLOCK: cellgate.py -->
```python
#!/usr/bin/env python3
# usage: cellgate.py <cells.txt> <target> <tuples.txt> — exit 0 iff for each of the five binaries the literal cell (successes, failures,
# expectedFailures, skips) equals the tuple OBSERVED on <target>; prints MOVED/UNCHANGED per binary (a moved cell is DATA in this act — it
# names the companion count-cell commit); exit 5 = at least one MOVED; exit 2 = malformed input.
import sys
def rows(path, target):
    out = {}
    for line in open(path, encoding="utf-8"):
        p = line.split()
        if len(p) >= 6 and p[0].startswith("biv_") and p[1] == target and p[2].startswith("successes="):
            out[p[0]] = tuple(x.split("=", 1)[1] for x in p[2:6])
    return out
target = sys.argv[2]
lit, ob = rows(sys.argv[1], target), rows(sys.argv[3], target)
if len(lit) != 5 or set(lit) != set(ob):
    print("MALFORMED literal=%d observed=%d" % (len(lit), len(ob))); sys.exit(2)
moved = 0
for b in sorted(lit):
    if lit[b] == ob[b]:
        print("UNCHANGED %s %s cell=%s" % (b, target, ",".join(lit[b])))
    else:
        moved += 1
        print("MOVED %s %s literal=%s observed=%s" % (b, target, ",".join(lit[b]), ",".join(ob[b])))
sys.exit(0 if moved == 0 else 5)
```

<!-- BLOCK: git-shim.sh -->
```bash
#!/usr/bin/env bash
# git-shim.sh — the request-trace instrument. Installed as `git` FIRST on the child's PATH by a test or a leg; appends one line per spawn
# (cwd, then argv, tab-separated) to $BIV_GIT_TRACE and execs the real git at $BIV_GIT_REAL. A missing variable is a hard failure (exit 97),
# never a silent pass-through: a leg that reads an empty trace must know the shim was live.
[ -n "${BIV_GIT_TRACE-}" ] && [ -n "${BIV_GIT_REAL-}" ] && [ -x "${BIV_GIT_REAL}" ] || exit 97
{ printf '%s' "$PWD"; for a in "$@"; do printf '\t%s' "$a"; done; printf '\n'; } >> "$BIV_GIT_TRACE" || exit 98
exec "$BIV_GIT_REAL" "$@"
```

<!-- BLOCK: gen_consent_display_table.py -->
```python
#!/usr/bin/env python3
# usage: gen_consent_display_table.py <UnicodeData.txt> <DerivedCoreProperties.txt> <inputs.sha256> > consent_display_table.hpp
# The A8-R1 clause-5 class at Unicode 15.0.0: General_Category in {Cf, Zl, Zp} UNION Default_Ignorable_Code_Point, emitted as sorted,
# merged [first, last] ranges of char32_t. Deterministic: same inputs -> same bytes. The header records the Unicode version, both input
# digests (read from <inputs.sha256>, which the caller produced with shasum -a 256) and this generator's own sha256.
import hashlib, re, sys
ud, dcp, digests = sys.argv[1], sys.argv[2], sys.argv[3]
first = open(dcp, encoding="utf-8").readline().rstrip("\n")
if first != "# DerivedCoreProperties-15.0.0.txt":
    sys.exit("STOP: DerivedCoreProperties header is not 15.0.0: %r" % first)
members = set()
# UnicodeData: field 2 = General_Category; ranges are given as "<..., First>" / "<..., Last>" pairs
pending_first = None
for line in open(ud, encoding="utf-8"):
    f = line.rstrip("\n").split(";")
    if len(f) < 3:
        continue
    cp, name, gc = int(f[0], 16), f[1], f[2]
    if name.endswith(", First>"):
        pending_first = (cp, gc); continue
    if name.endswith(", Last>"):
        lo, gc0 = pending_first; pending_first = None
        if gc0 in ("Cf", "Zl", "Zp"):
            members.update(range(lo, cp + 1))
        continue
    if gc in ("Cf", "Zl", "Zp"):
        members.add(cp)
for line in open(dcp, encoding="utf-8"):
    m = re.match(r"^([0-9A-F]{4,6})(?:\.\.([0-9A-F]{4,6}))?\s*;\s*Default_Ignorable_Code_Point\b", line)
    if m:
        lo = int(m.group(1), 16); hi = int(m.group(2), 16) if m.group(2) else lo
        members.update(range(lo, hi + 1))
if not members:
    sys.exit("STOP: empty class")
ranges = []
for cp in sorted(members):
    if ranges and cp == ranges[-1][1] + 1:
        ranges[-1][1] = cp
    else:
        ranges.append([cp, cp])
self_digest = hashlib.sha256(open(sys.argv[0], "rb").read()).hexdigest()
digest_lines = [ln.strip() for ln in open(digests, encoding="utf-8") if ln.strip()]
out = []
out.append("// GENERATED by tools/gen_consent_display_table.py -- DO NOT EDIT (A8-R1 clause 5; m-3 addendum 8 rev8).")
out.append("// Unicode version: 15.0.0 (pinned; a version bump is a design act at m-3's seat, never a regeneration).")
out.append("// class = General_Category in {Cf, Zl, Zp} UNION Default_Ignorable_Code_Point, as sorted merged ranges.")
for ln in digest_lines:
    out.append("// input sha256: " + ln)
out.append("// generator sha256: " + self_digest)
out.append("// members: %d  ranges: %d" % (len(members), len(ranges)))
out.append("#pragma once")
out.append("#include <array>")
out.append("#include <cstddef>")
out.append("namespace biv::cli {")
out.append("struct ConsentDisplayRange { char32_t first; char32_t last; };")
out.append("inline constexpr std::array<ConsentDisplayRange, %d> kConsentDisplayActive{{" % len(ranges))
for lo, hi in ranges:
    out.append("    {0x%04X, 0x%04X}," % (lo, hi))
out.append("}};")
out.append("inline constexpr bool consent_display_active(char32_t scalar) noexcept {")
out.append("  std::size_t lo = 0, hi = kConsentDisplayActive.size();")
out.append("  while (lo < hi) {")
out.append("    const std::size_t mid = lo + (hi - lo) / 2;")
out.append("    if (scalar < kConsentDisplayActive[mid].first) hi = mid;")
out.append("    else if (scalar > kConsentDisplayActive[mid].last) lo = mid + 1;")
out.append("    else return true;")
out.append("  }")
out.append("  return false;")
out.append("}")
out.append("}  // namespace biv::cli")
sys.stdout.write("\n".join(out) + "\n")
```

<!-- BLOCK: series_verdict.py -->
```python
#!/usr/bin/env python3
# usage: series_verdict.py <series-dir> <r435-family.txt> <N>  — the 015244 interleaved-series reducer. Reads <series-dir>/{B,H}-<i>/selftest-<label>.kv
# and .names for i in 1..N (written by selftest_summary.py per draw). Rules: every draw VALID (summary=parsed; failed == names_count;
# population > 0); population EQUAL within each tree across its N draws (an unequal draw is a STOP, never a witness); the candidate tree's
# failing-name UNION must be a subset of (family UNION the base tree's failing-name union) — K-1/K-2 no fresh finding; at least one base draw
# with a non-empty failing set (the in-family base observation); prints VERDICT PASS or VERDICT STOP <reason> [names]; exit 0 iff PASS.
import os, sys
sd, fam_path, n = sys.argv[1], sys.argv[2], int(sys.argv[3])
family = {ln.strip() for ln in open(fam_path, encoding="utf-8") if ln.strip()}
def draw(label):
    kv = dict(ln.rstrip("\n").split("=", 1) for ln in open(os.path.join(sd, label, "selftest-%s.kv" % label), encoding="utf-8") if "=" in ln)
    names = {ln.strip() for ln in open(os.path.join(sd, label, "selftest-%s.names" % label), encoding="utf-8") if ln.strip()}
    return kv, names
trees = {"B": [], "H": []}
for i in range(1, n + 1):
    for t in ("B", "H"):
        kv, names = draw("%s-%d" % (t, i))
        if kv.get("summary") != "parsed" or int(kv.get("failed", "0")) != len(names) or int(kv.get("population", "0")) <= 0:
            print("VERDICT STOP invalid-draw %s-%d %s" % (t, i, kv)); sys.exit(1)
        trees[t].append((int(kv["population"]), names))
for t, rows in trees.items():
    if len({p for p, _ in rows}) != 1:
        print("VERDICT STOP population-unequal-within-tree %s %s" % (t, sorted({p for p, _ in rows}))); sys.exit(1)
base_union = set().union(*[nm for _, nm in trees["B"]])
cand_union = set().union(*[nm for _, nm in trees["H"]])
fresh = sorted(cand_union - family - base_union)
if fresh:
    print("VERDICT STOP fresh-finding K-1/K-2 " + " ".join(fresh)); sys.exit(1)
if not any(nm for _, nm in trees["B"]):
    print("VERDICT STOP inconclusive-base-green (no non-empty in-family base observation)"); sys.exit(1)
print("VERDICT PASS draws=%d population_B=%d population_H=%d base_names=%d candidate_names=%d" % (
    n, trees["B"][0][0], trees["H"][0][0], len(base_union), len(cand_union)))
sys.exit(0)
```

<!-- BLOCK: plan_blocks.py -->
```python
#!/usr/bin/env python3
# usage: plan_blocks.py extract <plan.md> <name>        — a single BLOCK (the fenced block after `<!-- BLOCK: <name> -->`) byte-for-byte; for <name> = task-N
#                                                          the DERIVED RUNNER: PROLOGUE(N) + the concatenation, in document order, of every fenced block that
#                                                          follows a `<!-- RUN: task-N -->` marker (exit 2: marker absent/duplicated/unterminated, or no RUN block)
#        plan_blocks.py list <plan.md>                  — every BLOCK and every derived task runner, in document order: <name> <sha256> <line-count> [run-blocks=<k>]
#        plan_blocks.py check <plan.md> <N> <runner.sh> — exit 0 iff (i) the runner file == the derived task-N runner BYTE-FOR-BYTE; (ii) every `RUN: task-N`
#                                                          marker lies inside Task N's section and that section holds no RUN marker of another task; (iii) the
#                                                          derived runner opens with PROLOGUE(N); (iv) every GATE span of Task N's prose (a backtick span carrying
#                                                          `|| STOP`, `|| exit`, `; exit 1;` or `exit 0; fi`) is a runner line and the gate spans occur in the runner
#                                                          in the prose's order — the narrative stays bound to the executable text; 5 = a violation (each
#                                                          printed); 2 = a missing input. The last line printed is always rc=<n>.
import hashlib, re, sys
GATE = ("|| STOP", "|| exit", "; exit 1;", "exit 0; fi")
PROLOGUE = """#!/usr/bin/env bash
# task-@N@.sh — materialized VERBATIM from the plan's BLOCK task-@N@ by plan_blocks.py extract; proved by plan_blocks.py check; invoked by run-task.sh @N@
set -u
STOP() { printf 'STOP-task-@N@ line=%s\\n' "${BASH_LINENO[0]}" >&2; exit 1; }
RUNNERS=${1-}; [ -n "$RUNNERS" ] && [ -d "$RUNNERS" ] || exit 1
[ "$0" = "$RUNNERS/task-@N@.sh" ] || { printf 'STOP-task-@N@-invoked-off-path %s\\n' "$0" >&2; exit 1; }
t=0; tail -n 1 "$RUNNERS/proof-@N@.txt" > "$RUNNERS/task-@N@.proof-tail" 2>/dev/null || t=$?; [ "$t" -eq 0 ] && [ "$(cat "$RUNNERS/task-@N@.proof-tail")" = rc=0 ] || { printf 'STOP-task-@N@-unproved\\n' >&2; exit 1; }
h=0; shasum -a 256 "$0" > "$RUNNERS/task-@N@.self.sha256" || h=$?; [ "$h" -eq 0 ] && [ -s "$RUNNERS/task-@N@.self.sha256" ] || exit 1
a=$(cut -d' ' -f1 "$RUNNERS/task-@N@.self.sha256") || exit 1; b=$(cut -d' ' -f1 "$RUNNERS/task-@N@.sha256") || exit 1; [ -n "$a" ] && [ "$a" = "$b" ] || { printf 'STOP-task-@N@-bytes-differ\\n' >&2; exit 1; }
"""
PROLOGUE_EVID = """EVID=${2-}; [ -n "$EVID" ] && [ -d "$EVID" ] || exit 1; [ "$EVID" = "$(cat "$RUNNERS/evid.txt")" ] || exit 1
c=0; cp -p "$RUNNERS/task-@N@.sh" "$RUNNERS/proof-@N@.txt" "$RUNNERS/task-@N@.sha256" "$RUNNERS/task-@N@.invocation.txt" "$EVID/runners/" || c=$?; [ "$c" -eq 0 ] || exit 1
"""
def prologue(n):
    p = PROLOGUE + ("" if n == "0" else PROLOGUE_EVID)
    return p.replace("@N@", n)
def read(plan):
    return open(plan, encoding="utf-8").read()
def fenced(lines, i):
    # lines[i] is a marker line; the fence opens on the next line and closes on a line that is exactly ```
    if i + 1 >= len(lines) or not lines[i + 1].startswith("```"):
        sys.exit(2)
    j = i + 2
    body = []
    while j < len(lines) and lines[j] != "```":
        body.append(lines[j])
        j += 1
    if j >= len(lines):
        sys.exit(2)
    return "\n".join(body) + "\n", j
def scan(text):
    """returns (blocks: name -> body, runs: list of (task, line_index, body)) in document order"""
    lines = text.split("\n")
    blocks, runs = {}, []
    i = 0
    while i < len(lines):
        m = re.match(r"^<!-- BLOCK: ([A-Za-z0-9_.-]+) -->$", lines[i])
        r = re.match(r"^<!-- RUN: task-([0-9]{1,2}) -->$", lines[i])
        if m:
            name = m.group(1)
            if name in blocks or re.match(r"^task-[0-9]{1,2}$", name):
                sys.exit(2)
            body, j = fenced(lines, i)
            blocks[name] = body
            i = j
        elif r:
            body, j = fenced(lines, i)
            runs.append((r.group(1), i, body))
            i = j
        i += 1
    return blocks, runs
def section_bounds(text, n):
    """(start_line, end_line) of Task N's section as line indexes, or None"""
    lines = text.split("\n")
    start = None
    for i, ln in enumerate(lines):
        if start is None and re.match(r"^### Task %s —" % re.escape(n), ln):
            start = i
        elif start is not None and (ln.startswith("### Task ") or ln.startswith("## ")):
            return start, i
    return (start, len(lines)) if start is not None else None
def derived(text, n, runs=None):
    if runs is None:
        runs = scan(text)[1]
    mine = [body for task, _, body in runs if task == n]
    if not mine:
        sys.exit(2)
    return prologue(n) + "".join(mine)
def spans(sec):
    return re.findall(r"`([^`\n]+)`", sec)
def extract(plan, name):
    text = read(plan)
    m = re.match(r"^task-([0-9]{1,2})$", name)
    if m:
        sys.stdout.write(derived(text, m.group(1)))
        return 0
    blocks, _ = scan(text)
    if name not in blocks:
        sys.exit(2)
    sys.stdout.write(blocks[name])
    return 0
def listing(plan):
    text = read(plan)
    blocks, runs = scan(text)
    for name, body in blocks.items():
        print("%s %s %d" % (name, hashlib.sha256(body.encode("utf-8")).hexdigest(), body.count("\n")))
    for n in "0123456789":
        k = sum(1 for task, _, _ in runs if task == n)
        if k:
            body = derived(text, n, runs)
            print("task-%s %s %d run-blocks=%d" % (n, hashlib.sha256(body.encode("utf-8")).hexdigest(), body.count("\n"), k))
    return 0
def check(plan, n, runner):
    text = read(plan)
    blocks, runs = scan(text)
    b = section_bounds(text, n)
    if b is None or not any(task == n for task, _, _ in runs):
        sys.exit(2)
    try:
        run = open(runner, encoding="utf-8").read()
    except OSError:
        sys.exit(2)
    rc = 0
    blk = derived(text, n, runs)
    if run != blk:
        rl, bl = run.split("\n"), blk.split("\n")
        k = next((i for i in range(min(len(rl), len(bl))) if rl[i] != bl[i]), min(len(rl), len(bl)))
        print("BYTES-DIFFER at runner line %d (runner %d lines, derived %d lines)" % (k + 1, len(rl), len(bl)))
        rc = 5
    placed = 0
    for task, li, _ in runs:
        inside = b[0] <= li < b[1]
        if task == n and not inside:
            print("RUN-BLOCK-OUTSIDE-SECTION: RUN task-%s at line %d is outside Task %s's section" % (task, li + 1, n))
            rc = 5
        if task != n and inside:
            print("FOREIGN-RUN-BLOCK: RUN task-%s at line %d inside Task %s's section" % (task, li + 1, n))
            rc = 5
        if task == n and inside:
            placed += 1
    pro = prologue(n)
    if not blk.startswith(pro):
        print("PROLOGUE-MISMATCH")
        rc = 5
    sec_lines = text.split("\n")[b[0]:b[1]]
    sec = "\n".join(sec_lines)
    sp = spans(sec)
    gates = [s for s in sp if any(g in s for g in GATE)]
    lines = blk.split("\n")
    pos = {}
    for i, ln in enumerate(lines):
        pos.setdefault(ln, []).append(i)
    last = -1
    omitted = 0
    order = 0
    for s in gates:
        idx = [i for i in pos.get(s, []) if i >= last]
        if s not in pos:
            print("OMITTED gate span: %s" % s)
            omitted += 1
            rc = 5
        elif not idx:
            print("OUT-OF-ORDER gate span (runner lines %s, after %d): %s" % (",".join(str(i + 1) for i in pos[s]), last + 1, s))
            order += 1
            rc = 5
        else:
            last = idx[0]
    print("bytes=%s run_blocks=%d prologue=%s lines=%d spans=%d gates=%d omitted=%d out_of_order=%d" % (
        "equal" if run == blk else "differ", placed, "ok" if blk.startswith(pro) else "mismatch", len(lines) - 1, len(sp), len(gates), omitted, order))
    print("rc=%d" % rc)
    return rc
if __name__ == "__main__":
    if len(sys.argv) == 4 and sys.argv[1] == "extract":
        sys.exit(extract(sys.argv[2], sys.argv[3]))
    if len(sys.argv) == 3 and sys.argv[1] == "list":
        sys.exit(listing(sys.argv[2]))
    if len(sys.argv) == 5 and sys.argv[1] == "check":
        sys.exit(check(sys.argv[2], sys.argv[3], sys.argv[4]))
    sys.exit(2)
```

<!-- BLOCK: run-task.sh -->
```bash
#!/usr/bin/env bash
# run-task.sh N — the CONTROLLER (protocol (a)–(c)): authenticate itself and the extractor against the lock-verified plan, materialize task-N.sh from the plan's RUN blocks, prove it, fix its mode and digest, invoke it BY PATH, record the exit.
set -u
N=${1-}
case "$N" in 0|9|10|11) ;; *) printf 'usage: run-task.sh N (0|9|10|11)\n' >&2; exit 2;; esac
RUNNERS=$(cd "$(dirname "$0")" && pwd -P) || exit 1
[ "$0" = "$RUNNERS/run-task.sh" ] || { printf 'STOP-controller-invoked-off-path %s\n' "$0" >&2; exit 1; }
STOP() { printf 'STOP-controller-task-%s line=%s\n' "$N" "${BASH_LINENO[0]}" >&2; exit 1; }
PLAN=$(cat "$RUNNERS/plan-path.txt") || STOP; [ -s "$PLAN" ] || STOP
h=0; shasum -a 256 "$PLAN" > "$RUNNERS/plan-hash-$N.txt" || h=$?; [ "$h" -eq 0 ] && [ -s "$RUNNERS/plan-hash-$N.txt" ] || STOP
d=$(cut -d' ' -f1 "$RUNNERS/plan-hash-$N.txt") || STOP; e=$(cat "$RUNNERS/plan-lock.txt") || STOP; [ -n "$d" ] && [ "$d" = "$e" ] || STOP
bx() { python3 -c 'import sys; t = open(sys.argv[1], encoding="utf-8").read(); m = "<!-- BLOCK: " + sys.argv[2] + " -->\n"; i = t.index(m) + len(m); j = t.index("\n", i) + 1; k = t.index("\n" + chr(96) * 3 + "\n", j); sys.stdout.write(t[j:k + 1])' "$PLAN" "$1"; }
x=0; bx run-task.sh > "$RUNNERS/run-task.fresh-$N.sh" || x=$?; [ "$x" -eq 0 ] && [ -s "$RUNNERS/run-task.fresh-$N.sh" ] || STOP; c=0; cmp "$0" "$RUNNERS/run-task.fresh-$N.sh" || c=$?; [ "$c" -eq 0 ] || { printf 'STOP-controller-task-%s-not-the-plan-bytes\n' "$N" >&2; exit 1; }
x=0; bx plan_blocks.py > "$RUNNERS/plan_blocks.fresh-$N.py" || x=$?; [ "$x" -eq 0 ] && [ -s "$RUNNERS/plan_blocks.fresh-$N.py" ] || STOP; c=0; cmp "$RUNNERS/plan_blocks.py" "$RUNNERS/plan_blocks.fresh-$N.py" || c=$?; [ "$c" -eq 0 ] || { printf 'STOP-controller-task-%s-extractor-not-the-plan-bytes\n' "$N" >&2; exit 1; }
h=0; shasum -a 256 "$RUNNERS/plan_blocks.py" > "$RUNNERS/plan_blocks.sha256-$N" || h=$?; [ "$h" -eq 0 ] && [ -s "$RUNNERS/plan_blocks.sha256-$N" ] || STOP
if [ "$N" -gt 0 ]; then case "$N" in 9) M=0;; 10) M=9;; 11) M=10;; esac; [ -s "$RUNNERS/task-$M.done" ] && [ "$(cat "$RUNNERS/task-$M.done")" = rc=0 ] || STOP; fi
[ ! -e "$RUNNERS/task-$N.done" ] && [ ! -e "$RUNNERS/task-$N.sh" ] && [ ! -e "$RUNNERS/task-$N.exit" ] || STOP
if [ "$N" -eq 10 ]; then [ -s "$RUNNERS/task-10-go.txt" ] || { printf 'STOP-controller-task-10-no-continuation\n' >&2; exit 1; }; a=0; ng=$(awk 'END { print NR }' "$RUNNERS/task-10-go.txt") || a=$?; [ "$a" -eq 0 ] && [ "$ng" -eq 1 ] || { printf 'STOP-controller-task-10-continuation-not-one-line\n' >&2; exit 1; }; GOP=$(sed -n '1p' "$RUNNERS/task-10-go.txt") || STOP; case "$GOP" in /*) GOF=$GOP;; *) GOF=$(cd "$(dirname "$PLAN")/../../../.." && pwd -P)/$GOP;; esac; [ -s "$GOF" ] || { printf 'STOP-controller-task-10-continuation-target-missing\n' >&2; exit 1; }; fi
m=0; python3 "$RUNNERS/plan_blocks.py" extract "$PLAN" "task-$N" > "$RUNNERS/task-$N.sh" || m=$?; [ "$m" -eq 0 ] && [ -s "$RUNNERS/task-$N.sh" ] || STOP
c=0; python3 "$RUNNERS/plan_blocks.py" check "$PLAN" "$N" "$RUNNERS/task-$N.sh" > "$RUNNERS/proof-$N.txt" || c=$?; [ "$c" -eq 0 ] && [ -s "$RUNNERS/proof-$N.txt" ] || STOP
t=0; tail -n 1 "$RUNNERS/proof-$N.txt" > "$RUNNERS/proof-$N.tail" || t=$?; [ "$t" -eq 0 ] && [ "$(cat "$RUNNERS/proof-$N.tail")" = rc=0 ] || STOP
s=0; bash -n "$RUNNERS/task-$N.sh" || s=$?; [ "$s" -eq 0 ] || STOP
chmod 0500 "$RUNNERS/task-$N.sh" || STOP; [ -x "$RUNNERS/task-$N.sh" ] || STOP
h=0; shasum -a 256 "$RUNNERS/task-$N.sh" > "$RUNNERS/task-$N.sha256" || h=$?; [ "$h" -eq 0 ] && [ -s "$RUNNERS/task-$N.sha256" ] || STOP
if [ "$N" -eq 0 ]; then EVID=; printf '"%s/task-0.sh" "%s"\n' "$RUNNERS" "$RUNNERS" > "$RUNNERS/task-0.invocation.txt" || STOP; else EVID=$(cat "$RUNNERS/evid.txt") || STOP; [ -d "$EVID" ] || STOP; printf '"%s/task-%s.sh" "%s" "%s"\n' "$RUNNERS" "$N" "$RUNNERS" "$EVID" > "$RUNNERS/task-$N.invocation.txt" || STOP; fi
r=0; if [ "$N" -eq 0 ]; then "$RUNNERS/task-0.sh" "$RUNNERS" || r=$?; else "$RUNNERS/task-$N.sh" "$RUNNERS" "$EVID" || r=$?; fi
printf 'rc=%s\n' "$r" > "$RUNNERS/task-$N.exit" || exit 1
[ "$r" -eq 0 ] || { printf 'task-%s exited %s — STOP; the token ends here\n' "$N" "$r" >&2; exit 1; }
printf 'rc=0\n' > "$RUNNERS/task-$N.done" || exit 1
EVID=$(cat "$RUNNERS/evid.txt") || exit 1; c=0; cp -p "$RUNNERS/task-$N.done" "$RUNNERS/task-$N.exit" "$RUNNERS/proof-$N.tail" "$RUNNERS/plan_blocks.sha256-$N" "$EVID/runners/" || c=$?; [ "$c" -eq 0 ] || exit 1
printf 'task-%s done rc=0\n' "$N"
```

<!-- BLOCK: cells.py -->
```python
#!/usr/bin/env python3
# usage: cells.py <s2-harness.yml>   — prints the ten count-gate cells (+ the macOS expected_skips names), read from the bytes
import re, sys
text = open(sys.argv[1], encoding="utf-8").read()
starts = [m.start() for m in re.finditer(r"checks = \{", text)]
if len(starts) != 2:
    sys.exit(2)  # exactly one macOS block and one Linux block
bounds = starts + [len(text)]
for target, (lo, hi) in zip(("macos", "linux"), zip(starts, bounds[1:])):
    region = text[lo:hi]
    end = re.search(r"\n {10}\}\n", region)  # the block closer at the workflow's indentation
    if end is None:
        sys.exit(2)
    checks = region[:end.start()]
    cells = re.findall(r'"(biv_[a-z_]+)": \{\s*"successes": (\d+),\s*"failures": (\d+),\s*"expectedFailures": (\d+),\s*"skips": (\d+),', checks)
    if len(cells) != 5:
        sys.exit(3)
    for binary, s, f, e, k in cells:
        print(f"{binary} {target} successes={s} failures={f} expectedFailures={e} skips={k}")
    skips = re.search(r"expected_skips = \{(.*?)\}", region[end.end():], re.S)
    names = re.findall(r'"([^"]+)"', skips.group(1)) if skips else []
    print(f"expected_skips {target} {'n=' + str(len(names)) if skips else 'absent'} " + " | ".join(names))
```

<!-- BLOCK: tuples.py -->
```python
#!/usr/bin/env python3
# usage: tuples.py <target> <xml>...  — one line per XML: binary target successes failures expectedFailures skips xml_sha256; then the biv_tests skip set
import hashlib, os, sys, xml.etree.ElementTree as ET
target = sys.argv[1]
skips = None
for xml_path in sys.argv[2:]:
    binary = os.path.basename(xml_path).split("-")[0]
    data = open(xml_path, "rb").read()
    if not data:
        sys.exit(2)
    cases = ET.fromstring(data).find("OverallResultsCases")
    if cases is None:
        sys.exit(3)
    tuple_ = " ".join(f"{k}={cases.get(k, '0')}" for k in ("successes", "failures", "expectedFailures", "skips"))
    print(f"{binary} {target} {tuple_} xml_sha256={hashlib.sha256(data).hexdigest()}")
    if binary == "biv_tests":
        skips = sorted(tc.get("name") for tc in ET.fromstring(data).iter("TestCase") if tc.find("Skip") is not None)
if skips is None:
    sys.exit(4)
print(f"expected_skips_observed {target} n={len(skips)} " + " | ".join(skips))
```

<!-- BLOCK: skipset.py -->
```python
#!/usr/bin/env python3
# usage: skipset.py <B-cells.txt> <tuples-<target>.txt> <target>  — exit 0 iff the biv_tests skipped-name SET (and count)
# observed on <target> equals B's expected_skips names for <target>; membership only — the two producers order names differently
# by construction (cells.py: the workflow's listing order; tuples.py: sorted). exit 5 = a set/count difference; exit 2 = a line missing.
import sys
def names(path, prefix):
    for line in open(path, encoding="utf-8"):
        parts = line.rstrip("\n").split(" ", 3)
        if len(parts) >= 3 and parts[0] == prefix and parts[1] == sys.argv[3]:
            n = int(parts[2].split("=", 1)[1])
            rest = parts[3] if len(parts) == 4 else ""
            return n, frozenset(x.strip() for x in rest.split("|") if x.strip())
    return None
expected = names(sys.argv[1], "expected_skips")
observed = names(sys.argv[2], "expected_skips_observed")
if expected is None or observed is None:
    sys.exit(2)
(n_e, s_e), (n_o, s_o) = expected, observed
print(f"expected n={n_e} observed n={n_o} same_set={'yes' if s_e == s_o else 'no'} only_in_B={sorted(s_e - s_o)} only_in_observed={sorted(s_o - s_e)}")
sys.exit(0 if (n_e == n_o == len(s_e) and s_e == s_o) else 5)
```

<!-- BLOCK: selftest_summary.py -->
```python
#!/usr/bin/env python3
# selftest_summary.py — the pytest facts of the `harness-selftest` ctest row, read from CTest's JUnit output (rev18; iso rev13 bar).
#   usage: selftest_summary.py <ctest junit xml> <out prefix>
#   writes <prefix>.kv    one `key=value` per line: status=<run|fail|notrun|absent> summary=<parsed|absent> failed=<n> passed=<m>
#                         skipped=<k> population=<n+m+k> names_count=<c>
#          <prefix>.names one failing test per line as `<path>::<name>` (pytest's `FAILED <path>::<name>` short-summary lines, every file), sorted, unique
#   The summary line is pytest's final `==== N failed, M passed, K skipped in T s ====` line (the LAST such line in the testcase's
#   system-out); `summary=parsed` iff that line exists and carries a `passed` count; `failed`/`skipped` default to 0 when absent from it.
#   exit 0 when the XML parsed and the testcase exists (the bar decides on the fields); 2 on a missing/unparseable file or an absent testcase.
import re, sys, xml.etree.ElementTree as ET
def main(argv):
    if len(argv) != 3:
        print("usage: selftest_summary.py <junit.xml> <out-prefix>")
        return 2
    try:
        root = ET.parse(argv[1]).getroot()
    except Exception as e:
        print("BAD-JUNIT: %s" % e)
        return 2
    tc = next((t for t in root.iter("testcase") if t.get("name") == "harness-selftest"), None)
    if tc is None:
        print("TESTCASE-ABSENT: harness-selftest")
        return 2
    so = tc.find("system-out")
    txt = (so.text or "") if so is not None else ""
    status = tc.get("status") or "absent"
    if tc.find("failure") is not None:
        status = "fail"
    lines = [ln for ln in txt.split("\n") if re.match(r"^=+ .* in [0-9.]+s( \([0-9:]+\))? =+\s*$", ln)]
    summary = lines[-1] if lines else ""
    def count(word):
        m = re.search(r"(\d+) " + word + r"\b", summary)
        return int(m.group(1)) if m else 0
    parsed = bool(summary) and re.search(r"\d+ passed\b", summary) is not None
    failed, passed, skipped = (count("failed"), count("passed"), count("skipped")) if parsed else (0, 0, 0)
    names = sorted(set(re.findall(r"^FAILED (\S+::[A-Za-z0-9_\[\]\-]+)", txt, re.M)))  # QUALIFIED path::name, every file — a failure outside test_e3_asserts.py is a name the bar must see
    kv = "status=%s\nsummary=%s\nfailed=%d\npassed=%d\nskipped=%d\npopulation=%d\nnames_count=%d\n" % (
        status, "parsed" if parsed else "absent", failed, passed, skipped, failed + passed + skipped, len(names))
    with open(argv[2] + ".kv", "w", encoding="utf-8") as f:
        f.write(kv)
    with open(argv[2] + ".names", "w", encoding="utf-8") as f:
        f.write("".join(n + "\n" for n in names))
    sys.stdout.write(kv.replace("\n", " ").strip() + "\n")
    return 0
if __name__ == "__main__":
    sys.exit(main(sys.argv))
```

<!-- BLOCK: finalize.py -->
```python
#!/usr/bin/env python3
# finalize.py — THE EVIDENCE-OF-RECORD SET and its proof (rev17; master 042340 ruling (2); F5 of 212145)
#   list  <evid>                      print the SET: every regular file under the evidence home, path relative to the home,
#                                     sorted bytewise, EXCLUDING any path whose components include one of the four declared
#                                     scratch classes (rederive-*, llvm22-assets-{P,C,H}.*, __pycache__, stale-ci-macos) and the
#                                     four finalizer controller receipts (runners/task-7.done|.exit, proof-7.tail, plan_blocks.sha256-7 — Task 11 is this plan's finalizer)
#   check <evid> <resdir> <manifest>  exit 0 iff SET == TRACKED TREE (every regular file under <resdir> except SHA256SUMS)
#                                     == MANIFEST PATHS, in order and multiplicity; every manifest digest equals the tracked
#                                     file's sha256 recomputed here (hashlib); every tracked file's digest equals its home
#                                     twin's. 5 = a difference (the first ones printed); 2 = usage or an unreadable input.
import hashlib, os, re, sys
SCRATCH = (re.compile(r"^work$"), re.compile(r"^census-raw$"), re.compile(r"^strace-[HB]\.log$"), re.compile(r"^llvm22-assets-[HB]\.[A-Za-z0-9]+$"),
           re.compile(r"^__pycache__$"), re.compile(r"^stale-ci-macos$"))
# the FINALIZER's own controller receipts: written by run-task.sh into the home AFTER the Task 11 runner exits, so they can never
# be in the tree the finalizer proves; excluded here (declared), so a re-check after the run reproduces the same set (the
# pair Planner runs that post-controller re-check on the completed home before committing the record — Task 11 prose)
FINALIZER_RECEIPTS = frozenset(("runners/task-11.done", "runners/task-11.exit", "runners/proof-11.tail", "runners/plan_blocks.sha256-11"))
def excluded(rel):
    return rel in FINALIZER_RECEIPTS or any(p.match(c) for c in rel.split("/") for p in SCRATCH)
def files(root, skip=()):
    out = []
    for d, _dirs, names in os.walk(root):
        for n in names:
            full = os.path.join(d, n)
            if os.path.islink(full) or not os.path.isfile(full):
                continue
            rel = os.path.relpath(full, root)
            if rel in skip:
                continue
            out.append(rel)
    return sorted(out)
def evidence_set(evid):
    return [r for r in files(evid) if not excluded(r)]
def sha(path):
    h = hashlib.sha256()
    with open(path, "rb") as f:
        for chunk in iter(lambda: f.read(1 << 20), b""):
            h.update(chunk)
    return h.hexdigest()
def main(argv):
    if len(argv) == 3 and argv[1] == "list":
        s = evidence_set(argv[2])
        sys.stdout.write("".join(x + "\n" for x in s))
        return 0 if s else 5
    if len(argv) == 5 and argv[1] == "check":
        evid, res, man = argv[2], argv[3], argv[4]
        s = evidence_set(evid)
        tree = files(res, skip=("SHA256SUMS",))
        rows = []
        for ln in open(man, encoding="utf-8").read().split("\n"):
            if not ln:
                continue
            m = re.match(r"^([0-9a-f]{64})  (?:\./)?(.+)$", ln)
            if not m:
                print("BAD-MANIFEST-ROW: " + ln)
                return 5
            rows.append((m.group(2), m.group(1)))
        mpaths = [p for p, _ in rows]
        bad = 0
        def diff(name, first, second):
            nonlocal bad
            if first != second:
                bad = 1
                sa, sb = set(first), set(second)
                for x in sorted(sa - sb)[:5]:
                    print("%s: only in first: %s" % (name, x))
                for x in sorted(sb - sa)[:5]:
                    print("%s: only in second: %s" % (name, x))
                if sa == sb:
                    print("%s: same members, order or multiplicity differs" % name)
        diff("set-vs-tree", s, tree)
        diff("set-vs-manifest", s, mpaths)
        digests_bad = 0
        for p, dgst in rows:
            full = os.path.join(res, p)
            if not os.path.isfile(full):
                digests_bad += 1
                print("digest: missing in tree " + p)
                continue
            if sha(full) != dgst:
                digests_bad += 1
                print("digest: MISMATCH manifest-vs-tree " + p)
        copies_bad = 0
        for p in s:
            home, tracked = os.path.join(evid, p), os.path.join(res, p)
            if not os.path.isfile(tracked) or sha(home) != sha(tracked):
                copies_bad += 1
                print("copy: home-vs-tree differs or missing " + p)
        print("set=%d tree=%d manifest=%d equal=%s digests=%s copies=%s" % (
            len(s), len(tree), len(rows), "no" if bad else "yes", "ok" if digests_bad == 0 else "bad", "ok" if copies_bad == 0 else "bad"))
        return 0 if (bad == 0 and digests_bad == 0 and copies_bad == 0) else 5
    if len(argv) == 5 and argv[1] == "prbody":
        evid, base, head = argv[2], argv[3], argv[4]
        def rd(rel):
            p = os.path.join(evid, rel)
            return open(p, encoding="utf-8").read().strip() if os.path.isfile(p) else "(absent)"
        commits = "\n".join("- c%s = %s" % (k, rd("commits.c%s.txt" % k)) for k in range(1, 10) if os.path.isfile(os.path.join(evid, "commits.c%s.txt" % k)))
        legs = sorted(f for f in os.listdir(os.path.join(evid, "legs")) if f.endswith(".txt")) if os.path.isdir(os.path.join(evid, "legs")) else []
        body = ["Sub-step 2b: wire biv pack and biv open to the repo engine and the landed consent fabric at product scope (sealed M/N/O, A6/A7/A8/A2-D4, SR-URL; the R-4.47 bar).", "",
                "B (published pin) = %s" % base, "H (branch head) = %s" % head, "", "Commits (veto-9 mechanical order):", commits, "",
                "E2 wiring census:", "```", rd("H/E2-census.txt"), "```", "E5 flip: diff EMPTY (%s)" % ("yes" if rd("H/E5-flip.txt") == "" else "NO"),
                "veto 9:", "```", rd("H/veto9.txt"), "```", "Count gate: macOS %s / linux %s; %s" % (rd("H/count-gate-final-macos.rc"), rd("H/count-gate-final-linux.rc"), rd("H/count-gate.txt")),
                "E3 (both platforms): macOS receipt legs/E3.txt; linux %s" % rd("H/E3-linux.rc"), "Selftest population: %s%s" % (rd("H/selftest-population.rc"), (" ; series " + rd("H/selftest-series.rc")) if os.path.isfile(os.path.join(evid, "H/selftest-series.rc")) else ""),
                "Leg receipts (%d): %s" % (len(legs), ", ".join(legs)), "Registered (S-6): %s" % rd("legs/registered.txt"),
                "", "Merge != push != release; the release hold is ABSOLUTE. Draft until the operator's merge token."]
        sys.stdout.write("\n".join(body) + "\n")
        return 0
    print("usage: finalize.py list <evid> | check <evid> <resdir> <manifest> | prbody <evid> <B> <H>")
    return 2
if __name__ == "__main__":
    sys.exit(main(sys.argv))
```

<!-- BLOCK: linux-container.sh -->
```bash
#!/usr/bin/env bash
# linux-container.sh <expected-head> <label B|H|B-n|H-n> — Phases R / T / S (2b: Phase L removed) inside ubuntu:24.04 (linux/amd64, --init); /llvm-mirror and /repo-ro read-only, /evidence writable AND the evidence home mounted a second time at its HOST path (S carries host-path cwd values and project keys, so Phase L packs it IN PLACE at that path under the readtrace shim after a must-be-YES control).
# The container exits 0 ONLY IF Phase R, T and S all exited 0 AND the payload/copy-out receipts wrote and copied; the ctest rc is carried as DATA by Phase S.
set -u
WORK_ROOT=/work
REPO_ROOT=/work/repo
OUT=/work/out
LEDGER="$OUT/linux-ledger.txt"
EXPECTED=${1-}
LABEL=${2-}
STOP() { printf 'STOP-linux-container-%s line=%s\n' "$LABEL" "${BASH_LINENO[0]}" >&2; exit 1; }
finalize_container() {
  payload_rc=$?
  trap - EXIT
  payload_receipt_rc=0
  printf 'container_payload_rc=%s\n' "$payload_rc" > "$OUT/container-payload.rc" || payload_receipt_rc=$?
  copy_out_rc=0
  cp -p "$OUT"/* "/evidence/$LABEL/" || copy_out_rc=$?
  copy_receipt_rc=0
  printf 'copy_out_rc=%s payload_receipt_rc=%s\n' "$copy_out_rc" "$payload_receipt_rc" > "$OUT/container-copy-out.rc" || copy_receipt_rc=$?
  final_receipt_copy_rc=0
  cp -p "$OUT/container-copy-out.rc" "/evidence/$LABEL/container-copy-out.rc" || final_receipt_copy_rc=$?
  if [ "$payload_rc" -ne 0 ] || [ "$payload_receipt_rc" -ne 0 ] || [ "$copy_out_rc" -ne 0 ] || [ "$copy_receipt_rc" -ne 0 ] || [ "$final_receipt_copy_rc" -ne 0 ]; then
    exit 1
  fi
  exit 0
}
[ -n "$EXPECTED" ] || STOP
case "$LABEL" in B|H|B-[0-9]|B-[0-9][0-9]|H-[0-9]|H-[0-9][0-9]) ;; *) STOP;; esac
[ -d "/evidence/$LABEL" ] && [ -w "/evidence/$LABEL" ] || STOP
work_root_rc=0
mkdir -p "$OUT" || work_root_rc=$?
[ "$work_root_rc" -eq 0 ] && [ -d "$OUT" ] || STOP
ledger_create_rc=0
: > "$LEDGER" || ledger_create_rc=$?
[ "$ledger_create_rc" -eq 0 ] && [ -f "$LEDGER" ] || STOP
trap finalize_container EXIT
phase_r_base=0
apt-get update > "$OUT/phase-R-base.log" 2>&1 && apt-get install -y --no-install-recommends ca-certificates git g++ make cmake strace python3 python3-venv python3-pip libsqlite3-dev binutils zstd openssh-client >> "$OUT/phase-R-base.log" 2>&1 || phase_r_base=$?
phase_r_base_record_rc=0
printf 'phase_R_base_provision_rc=%s\n' "$phase_r_base" >> "$LEDGER" || phase_r_base_record_rc=$?
[ "$phase_r_base_record_rc" -eq 0 ] || STOP
[ "$phase_r_base" -eq 0 ] || STOP
phase_r_assets_fn() {
  LLVM_TIDY_VERSION='1:22.1.8~++20260613092238+e80beda6e255-1~exp1~20260613092253.78'
  while read -r _ expected_package asset; do
    packaged_name=$(dpkg-deb --field "/llvm-mirror/$asset" Package) || return 11
    packaged_version=$(dpkg-deb --field "/llvm-mirror/$asset" Version) || return 12
    packaged_arch=$(dpkg-deb --field "/llvm-mirror/$asset" Architecture) || return 13
    [ "$packaged_name" = "$expected_package" ] || return 14
    [ "$packaged_version" = "$LLVM_TIDY_VERSION" ] || return 15
    [ "$packaged_arch" = amd64 ] || return 16
  done < /llvm-mirror/MANIFEST
  set -- /llvm-mirror/*.deb
  [ "$#" -eq 8 ] || return 18
  apt-get install -y --no-install-recommends /llvm-mirror/*.deb || return 19
  while read -r _ package _; do
    installed_package_version=$(dpkg-query --show --showformat='${Version}' "$package") || return 20
    [ "$installed_package_version" = "$LLVM_TIDY_VERSION" ] || return 21
  done < /llvm-mirror/MANIFEST
  installed_version=$(dpkg-query --show --showformat='${Version}' clang-tidy-22) || return 22
  [ "$installed_version" = "$LLVM_TIDY_VERSION" ] || return 23
  clang-tidy-22 --version > "$OUT/clang-tidy-version.txt" || return 24
  [ -s "$OUT/clang-tidy-version.txt" ] || return 25
  observed_major=$(sed -nE 's/.*LLVM version ([0-9]+).*/\1/p' "$OUT/clang-tidy-version.txt") || return 26
  [ "$observed_major" = 22 ] || return 27
}
phase_r_assets=0
phase_r_assets_fn > "$OUT/phase-R-assets.log" 2>&1 || phase_r_assets=$?
phase_r_assets_record_rc=0
printf 'phase_R_asset_provision_rc=%s\n' "$phase_r_assets" >> "$LEDGER" || phase_r_assets_record_rc=$?
[ "$phase_r_assets_record_rc" -eq 0 ] || STOP
[ "$phase_r_assets" -eq 0 ] || STOP
phase_t_transition_fn() {
  groupadd -g 1001 suite || return 31
  useradd -m -u 1001 -g 1001 suite || return 32
  git config --global --add safe.directory /repo-ro || return 33
  git clone --no-hardlinks --branch intg/substep2b-wiring /repo-ro "$REPO_ROOT" || return 34
  git -C "$REPO_ROOT" checkout -q --detach "$EXPECTED" || return 35
  observed_head=$(git -C "$REPO_ROOT" rev-parse HEAD) || return 36
  printf 'expected=%s observed=%s\n' "$EXPECTED" "$observed_head" > "$OUT/linux-run-head-receipt.txt" || return 37
  [ -s "$OUT/linux-run-head-receipt.txt" ] || return 38
  [ "$observed_head" = "$EXPECTED" ] || return 39
  cp /evidence/linux-suite.sh "$REPO_ROOT/linux-suite.sh" || return 40
  cp /evidence/observer-unset-names.txt "$REPO_ROOT/observer-unset-names.txt" || return 41
  chown -R 1001:1001 "$REPO_ROOT" "$OUT" || return 42
  mkdir -p /mnt/c/tmp || return 43
  chown -R 1001:1001 /mnt/c || return 44
  runuser -u suite -- test -w /mnt/c/tmp || return 45
}
phase_t_transition=0
phase_t_transition_fn > "$OUT/phase-T-transition.log" 2>&1 || phase_t_transition=$?
phase_t_record_rc=0
printf 'phase_T_transition_fixture_rc=%s\n' "$phase_t_transition" >> "$LEDGER" || phase_t_record_rc=$?
[ "$phase_t_record_rc" -eq 0 ] || STOP
[ "$phase_t_transition" -eq 0 ] || STOP
phase_s_suite=0
runuser -u suite -- bash "$REPO_ROOT/linux-suite.sh" "$REPO_ROOT" "$OUT" "$LABEL" > "$OUT/phase-S-suite.log" 2>&1 || phase_s_suite=$?
phase_s_record_rc=0
printf 'phase_S_suite_rc=%s\n' "$phase_s_suite" >> "$LEDGER" || phase_s_record_rc=$?
[ "$phase_s_record_rc" -eq 0 ] || STOP
[ "$phase_s_suite" -eq 0 ] || STOP
printf 'LINUX_THREE_PHASE_COMPLETE %s=%s\n' "$LABEL" "$EXPECTED"
exit 0
```

<!-- BLOCK: linux-suite.sh -->
```bash
#!/usr/bin/env bash
# linux-suite.sh <repo-root> <out> <label P|C|H> — Phase S as the suite user: nofile raise, venv, configure, build, the name-free proof, the five -r xml
# producers, the workflow-equivalent ctest run. EVERY status is recorded in <out>/linux-suite-ledger.txt as <name>=<rc>; the 26 REQUIRED statuses
# decide suite_aggregate_rc (0 iff all 0); the ctest rc (ctest_<label>_producer_rc) is DATA — recorded, written bare to ctest-linux-<label>.rc, EXCLUDED
# from the aggregate. The script exits with the aggregate (a required red exits nonzero; a ctest red alone exits 0 and reaches the caller's bar).
set -u
REPO_ROOT=${1-}
OUT=${2-}
LABEL=${3-}
STOP() { printf 'STOP-linux-suite-%s line=%s\n' "$LABEL" "${BASH_LINENO[0]}" >&2; exit 1; }
[ "$REPO_ROOT" = /work/repo ] || STOP
[ "$OUT" = /work/out ] || STOP
case "$LABEL" in B|H|B-[0-9]|B-[0-9][0-9]|H-[0-9]|H-[0-9][0-9]) ;; *) STOP;; esac
cd "$REPO_ROOT" || STOP
[ -d "$OUT" ] && [ -w "$OUT" ] || STOP
SUITE_LEDGER="$OUT/linux-suite-ledger.txt"
ledger_create_rc=0
: > "$SUITE_LEDGER" || ledger_create_rc=$?
[ "$ledger_create_rc" -eq 0 ] && [ -f "$SUITE_LEDGER" ] || STOP
ledger_write_failed=0
record_status() {
  printf '%s=%s\n' "$1" "$2" >> "$SUITE_LEDGER" || ledger_write_failed=1
}
producers_red=0
run_binary() {
  binary=$1
  binary_rc=0
  "./build/ci/$binary" -r xml > "$OUT/$binary-linux.xml" 2> "$OUT/$binary-linux.stderr" || binary_rc=$?
  record_status "${binary}_producer_rc" "$binary_rc"
  binary_xml_nonempty_rc=1
  [ -s "$OUT/$binary-linux.xml" ] && binary_xml_nonempty_rc=0
  record_status "${binary}_xml_nonempty_rc" "$binary_xml_nonempty_rc"
  [ "$binary_rc" -eq 0 ] && [ "$binary_xml_nonempty_rc" -eq 0 ] || producers_red=1
}
hard_limit_rc=0
HARD_LIMIT=$(ulimit -Hn) || hard_limit_rc=$?
record_status nofile_hard_read_rc "$hard_limit_rc"
nofile_raise_rc=125
if [ "$hard_limit_rc" -eq 0 ] && [ -n "$HARD_LIMIT" ]; then
  nofile_raise_rc=0
  ulimit -Sn "$HARD_LIMIT" || nofile_raise_rc=$?
fi
record_status nofile_raise_rc "$nofile_raise_rc"
soft_limit_rc=0
SOFT_LIMIT=$(ulimit -Sn) || soft_limit_rc=$?
record_status nofile_soft_read_rc "$soft_limit_rc"
nofile_equal_rc=1
if [ "$hard_limit_rc" -eq 0 ] && [ "$soft_limit_rc" -eq 0 ] && [ -n "$HARD_LIMIT" ] && [ "$SOFT_LIMIT" = "$HARD_LIMIT" ]; then
  nofile_equal_rc=0
fi
record_status nofile_soft_equals_hard_rc "$nofile_equal_rc"
nofile_receipt_rc=0
printf 'soft=%s hard=%s\n' "${SOFT_LIMIT-UNREADABLE}" "${HARD_LIMIT-UNREADABLE}" > "$OUT/linux-nofile.txt" || nofile_receipt_rc=$?
record_status nofile_receipt_write_rc "$nofile_receipt_rc"
venv_rc=0
python3 -m venv .venv-harness > "$OUT/linux-venv.log" 2>&1 || venv_rc=$?
record_status venv_rc "$venv_rc"
requirements_rc=0
.venv-harness/bin/python -m pip install -r harness/requirements.lock > "$OUT/linux-requirements.log" 2>&1 || requirements_rc=$?
record_status requirements_rc "$requirements_rc"
configure_rc=0
cmake --preset ci -DBIVHARNESS_REQUIRE_CLANG_TIDY=ON > "$OUT/linux-configure.log" 2>&1 || configure_rc=$?
record_status configure_rc "$configure_rc"
build_rc=0
cmake --build --preset ci > "$OUT/linux-build.log" 2>&1 || build_rc=$?
record_status build_rc "$build_rc"
name_proof_create_rc=0
: > "$OUT/linux-observer-name-proof.txt" || name_proof_create_rc=$?
record_status observer_name_proof_create_rc "$name_proof_create_rc"
observer_input_rc=0
[ -s "$REPO_ROOT/observer-unset-names.txt" ] || observer_input_rc=1
record_status observer_name_input_nonempty_rc "$observer_input_rc"
observer_name_present_rc=0
observer_name_proof_write_rc=0
if [ "$name_proof_create_rc" -eq 0 ] && [ "$observer_input_rc" -eq 0 ]; then
  while read -r observer_name; do
    if [ -z "$observer_name" ]; then
      observer_name_present_rc=1
      continue
    fi
    if printenv "$observer_name" > /dev/null; then
      printf '%s present\n' "$observer_name" >> "$OUT/linux-observer-name-proof.txt" || observer_name_proof_write_rc=$?
      observer_name_present_rc=1
    else
      printf '%s absent\n' "$observer_name" >> "$OUT/linux-observer-name-proof.txt" || observer_name_proof_write_rc=$?
    fi
  done < "$REPO_ROOT/observer-unset-names.txt"
fi
record_status observer_name_present_rc "$observer_name_present_rc"
record_status observer_name_proof_write_rc "$observer_name_proof_write_rc"
observer_name_proof_nonempty_rc=1
[ -s "$OUT/linux-observer-name-proof.txt" ] && observer_name_proof_nonempty_rc=0
record_status observer_name_proof_nonempty_rc "$observer_name_proof_nonempty_rc"
measurement_missing=0
ctest_rc=125
ctest_log_nonempty_rc=1
ctest_receipt_rc=125
if [ "$name_proof_create_rc" -eq 0 ] && [ "$observer_input_rc" -eq 0 ] && [ "$observer_name_present_rc" -eq 0 ] && [ "$observer_name_proof_write_rc" -eq 0 ] && [ "$observer_name_proof_nonempty_rc" -eq 0 ] && [ "$configure_rc" -eq 0 ] && [ "$build_rc" -eq 0 ]; then
  run_binary biv_subprocess_tests
  run_binary biv_repo_git_tests
  run_binary biv_repo_engine_tests
  run_binary biv_tests
  run_binary biv_probe_tests
  ctest_rc=0
  ctest --preset ci --output-junit "$OUT/ctest-linux-$LABEL.junit.xml" --output-on-failure --test-output-size-passed 50000000 --test-output-size-failed 50000000 > "$OUT/ctest-linux-$LABEL.log" 2>&1 || ctest_rc=$?
  record_status "ctest_${LABEL}_producer_rc" "$ctest_rc"
  ctest_log_nonempty_rc=1
  [ -s "$OUT/ctest-linux-$LABEL.log" ] && ctest_log_nonempty_rc=0
  record_status "ctest_${LABEL}_log_nonempty_rc" "$ctest_log_nonempty_rc"
  ctest_receipt_rc=0
  printf '%s\n' "$ctest_rc" > "$OUT/ctest-linux-$LABEL.rc" || ctest_receipt_rc=$?
  record_status "ctest_${LABEL}_receipt_write_rc" "$ctest_receipt_rc"
else
  for binary in biv_subprocess_tests biv_repo_git_tests biv_repo_engine_tests biv_tests biv_probe_tests; do
    record_status "${binary}_producer_rc" 125
    record_status "${binary}_xml_nonempty_rc" 1
  done
  record_status "ctest_${LABEL}_producer_rc" 125
  record_status "ctest_${LABEL}_log_nonempty_rc" 1
  record_status "ctest_${LABEL}_receipt_write_rc" 125
  measurement_missing=1
fi
suite_aggregate_rc=0
for required_rc in "$hard_limit_rc" "$nofile_raise_rc" "$soft_limit_rc" "$nofile_equal_rc" "$nofile_receipt_rc" "$venv_rc" "$requirements_rc" "$configure_rc" "$build_rc" "$name_proof_create_rc" "$observer_input_rc" "$observer_name_present_rc" "$observer_name_proof_write_rc" "$observer_name_proof_nonempty_rc" "$measurement_missing" "$producers_red" "$ctest_log_nonempty_rc" "$ctest_receipt_rc"; do
  [ "$required_rc" -eq 0 ] || suite_aggregate_rc=1
done
[ "$producers_red" -eq 0 ] || suite_aggregate_rc=1
[ "$ledger_write_failed" -eq 0 ] || suite_aggregate_rc=1
aggregate_record_rc=0
printf 'suite_aggregate_rc=%s ledger_write_failed=%s\n' "$suite_aggregate_rc" "$ledger_write_failed" >> "$SUITE_LEDGER" || aggregate_record_rc=$?
[ "$aggregate_record_rc" -eq 0 ] || exit 1
exit "$suite_aggregate_rc"
```

## Revision history

- rev1 (2026-09-15): the opening plan for sub-step 2b under the three pre-token gates (m-4 035001; m-1 042531 + master 043301; m-3 130818 + master 131404), master's Q1/Q5/Q6 ruling (041518) and the RECONCILE R4 corrections; contingent terms T-KIND / T-JSON / T-HELP / T-STAGE / T-FENCE / T-PROM / T-NET / T-K / T-C carried as gated plan terms; filed for the implementer's exact-hash review.
