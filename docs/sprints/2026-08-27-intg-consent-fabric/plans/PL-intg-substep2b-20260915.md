# Sub-step 2b — wiring `biv pack` and `biv open` to the repo engine and the landed consent fabric at product scope — Implementation Plan (rev8)

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** connect both product verbs to the landed repo engine (`src/core/repo`) and the landed consent fabric (`src/cli/url_consent.cpp`), executing SEALED text only — M rev8 / N / O (m-1), A6 rev14 / A7 rev2 / A8 rev8 / A2 D4 (m-3), SR-URL rev5 (m-4), the R-4.47 bar — so that `biv pack` discovers, classifies, gates, captures and records repositories, `biv open` restores them per entry, PROMPT D fires at both encounters through the A6/A7/A8 fabric, `--offline` reaches the engine on both verbs, and every deferred witness (FX-M-1 (a)–(o) incl. (d) + (a)-interactive; FX-A6 a6·1–13 + a6·16's divergence half; FX-A7 a7·1–5; FX-A8 a8·1–a8·6; FX-N (a)/(g); R-4.48 (ii)–(iv)) executes at product scope.

**Architecture:** ONE candidate branch cut from the PUBLISHED PIN `186adf7d67171bd7afe621f39b657a1a113ce299`, commits in the veto-9 MECHANICAL order (the THREE pre-authorized engine commits c1a/c1b/c1c FIRST — m-1 V-2b-1 rev3 — every call-site commit after them; no commit spans both sets), three product tranches A (fabric + CLI plumbing, zero engine reach) → B (open restore path) → C (pack pipeline, the shipped `.git` refusal RETIRED into the narrowed `UnclaimedGitEntry` class), then m-3's harness commit (arm-A shape), then the count-cell companion commit iff a case tuple moved. Every open-side witness first run on a hand-built image is RE-EXECUTED against a `biv pack`-produced image after tranche C, inside the candidate, before the packet (master 041518's condition). The landing rides a PR from the pushed remote branch (R-4.51 (2)); the R-4.49 census instrument is reused at its exact pin with a population written FOR the merge head.

**Tech Stack:** C++23 (`std::expected`), CMake presets `ci-macos` / `ci` (Linux parity container Ubuntu 24.04 `--platform linux/amd64 --init`), Catch2 v3.7.1, the pytest harness under `harness/` (python3.12 venv from `harness/requirements.lock`), bash 3.2-compatible runner blocks, `gh` for the PR.

**Spec (the sealed texts this plan executes; every path under `../pdc/`):** `master/domains/m-1-format-engine/design/2026-08-23-ADDENDUM-M-url-effective-endpoint-consent.md` (M rev8: M-R1..R8 :259-415, FX-M-1 :416-516); `…/2026-08-26-ADDENDUM-N-shallow-payload-only-cell.md` (N; flags-to-wiring-team :320-329; FX-N); `…/2026-09-01-ADDENDUM-O-writer-validity-contract.md` (O; FX-O); `…/2026-07-02-pack-engine.md` (§1.1 Phase D/C, §1.2, §1.3, §2 incl. COND-6, §4); `…/2026-07-02-restore-apply-contract.md` (§1, §2.2); `…/2026-07-04-ADDENDUM-D-offline-and-n3.md` (:78 `offline-pointer`); `…/2026-08-07-ADDENDUM-I-biv-member-refusal.md` (I-R1, I-R2a); `master/domains/m-3-restore-cli/design/2026-08-24-addendum-6-url-consent-consumer-surface.md` (A6 rev14: A6-R1..R9 :380-685, FX-A6 :686-822); `…/2026-08-26-addendum-7-consent-interaction-companion.md` (A7 rev2: A7-R1..R5 :57-138, FX-A7 :139-175); `…/2026-08-29-addendum-8-display-encoding-companion.md` (A8 rev8: A8-R1..R4 :92-256, FX-A8 :257-352); `…/2026-07-04-addendum-2-n24-honest-network-offline.md` (A2 D4 :77-127, D5); `master/domains/m-4-hostile-image/design/2026-08-23-sr-url-effective-endpoint-consent.md` (SR-URL rev5); the R-4.47 bar (`master/relays/m4-reachability-rereview/DESIGN-REVIEW-planner-20260827-204641.md` §1).

**Owner fences this plan is graded against (each read WHOLE by the implementer before Task 0; nothing in them is paraphrased here as authority):** the OWNER WORDS of 2026-09-16 carried by master `master/relays/intg-2b-wiring-act/PLAN-master-planner-20260916-080937.md` — m-1 `master/relays/intg-2b-wiring-act/DESIGN-planner-20260916-074712.md` (Q11 fences = whole-operation typed refusals, `unmerged` permanent, `dirty`/`nested`/`submodule` TRANSITIONAL → R-4.57; Q10 promisor pack-only whole-operation both arms; Q13 apply half — the durable artifact at `<workspace>/.biv/repos/<id>/repo.bundle`; the ten-kind engine semantics table; the ARM-1 fact: the landed engine captures clean single repositories only), m-3 `…/DESIGN-planner-20260916-075225.md` + `080308.md` (Q8 `--network` NOT inert, D3 executes; Q9 `result.repos`; Q13 UX half), m-3's 2b fence origin `master/relays/intg-2b-wiring-act/DESIGN-planner-20260916-134813.md` (rev2 origin under the A6 design-id, approved binding 135230 — the CLI half of record: 130818's §1/§2/§3/§5/§6 carried by reference, its §4 retired clause by clause in favour of A9.4 and A10.6; 130818 is history), m-3 ADDENDUM 10 rev6 `master/domains/m-3-restore-cli/design/2026-09-16-addendum-10-open-repos-rows-and-network-consent.md` (pin `17fda846d320b09bae57ed088cb722f1d92392583dd66785900fd312f32823fd`; rev5 `db384844…` approved binding 132531 and superseded cleanly by rev6, which folds m-1's rev3 §2 partition verbatim and is UNDER the re-approve — binding at ITS lock), m-3 ADDENDUM 11 rev5 `master/domains/m-3-restore-cli/design/2026-09-16-addendum-11-engine-error-surfacing-rows.md` (pin `33c699138a0bb6a240d7e0a8f50407e83e39c72635ae078964c196fbec97ea3a`; rev4 `cacce399…` closed MUST-A11-2 with the three-carrier assertions, rev5 folds the MUST-2B-17 seam settlement — UNDER REVIEW, binding at ITS lock), m-3 ADDENDUM 9 rev2 — LOCKED `m3-addendum-9-40eaea22-lock-20260916` (m-3 `165214`; master 170242): pre-stamp pin `40eaea2273a32922640ade0f65b897ad8d52b40dc8eadef3845264fe1f40fa8c` at pdc `c2f7a6c7eac61fb39c872cb7329734a1cd0c5db0` (the Domain Reviewer's binding approve 134001; the Master Reviewer's approve-for-owner-lock 141334), post-stamp `ae27264763b5ec20057b88f78f87d642ab22a28305a532c66c44063603eb2cf0` (both re-hashed at this seat; the normative region byte-identical), ARCHITECTURE row line 46 — c3h and c6a are RELEASED at this lock under the Master Reviewer's boundaries: A10.6's supersession of A9.4's bundle line takes effect ONLY on A10's OWN lock (A9.4's D4 header/row bytes are the golden until then; NO bundle line is planned from A9); A9 relabels no sealed shallow / payload-only outcome; the 29-row witness is A9's replacement-stage result (A11 moves the count on ITS lock); all eleven A9 legs and mutants are owed at implementation; m-1 `master/relays/intg-2b-wiring-act/DESIGN-planner-20260916-161701.md` (fence rev4 — the fence of record once m-1.implementer's binding approve lands (asked 170247; its must-revise 140251 of rev3 is a hand-carried draft until rendered); supersedes rev3 `131522` and rev2 `171041` IN SUBSTANCE: a THIRD pre-authorized engine commit c1c (`restore_invokes_git` exported and used by `restore_entry`'s single guard at :443-452 — the mechanism unchanged from rev3) re-stated as the engine's GIT-CAPABLE partition (FALSE ⇒ no git UNCONDITIONALLY through success or typed error — N-R4 / H; TRUE ⇒ the restore MAY invoke git once the preceding checks :459/:468/:477/:483 pass and therefore REQUIRES consent — it promises neither a spawn nor a successful apply; first possible spawn :491 or :521+); the walked census of `restore_entry` :425-589 (26 returns; two successful no-git shape returns) quoted beside it; W-G3 narrowed to the single predicate call controlling those two returns; W-G1 bound to PREPARED VALID fixtures; W-G1c the collision counter-control (true, typed failure at :477, zero git — not drift); W-G1n N/H through the error path; W-G2 the drift mutant; the EXACT `--offline`/DECLINED partition on that predicate (FALSE ⇒ CALL `restore_entry`; TRUE ⇒ offline-pointer row) correcting 074712 §2's "never called", ARTIFACT-PRESENT = `entry.bundle` ∧ checksums membership with no engine byte (membership never replacing the integrity/containment checks), and the MUST-2B-17 seam word; 171041 `…/DESIGN-planner-20260915-171041.md` (rev2, approved 044559 at pdc 631aae82 — the M edge's origin until rev3's approve; then the carrier re-pins) stands for everything rev3 carries verbatim: S-2b-1 rev2 (offline COMPOSED with N/G/H — binds only the born non-shallow lane; R-4.1 arm (i) scoped to the git-aware promisor lane; the PACK and OPEN receipts named separately), V-2b-1 rev2 (TWO pre-authorized engine commits c1a/c1b), V-2b-5 rev2 (scan.cpp's `.biv` payload skip stays AS LANDED), witnesses W-O1..3 and W-D1..4; everything else of 042531 stands verbatim: vetoes 1–9 with veto 9 mechanical; V-M-INT-1..5; V-2b-2/4/6/7/8/9; S-2b-2..8; the FX partition; §4 evidence set); m-3 `…/DESIGN-planner-20260915-130818.md` (V-A6-1..6, V-A7-1..4, V-A8-1..5, R-4.48 (ii)–(iv) as vetoes with witnesses; the R4 absence bar in its positive form; TC-1..3; S-1..S-6; §3 the kind; §4 the `--offline`/`--network` cut verbatim; §5 the golden-harness repos bar; §6 the harness-selftest population rule); m-4 `…/DESIGN-planner-20260915-035001.md` (the carry; the E-split; the C-2 pre-warning); m-2 `…/DESIGN-m2-planner-20260915-125200.md` (Q4 NOT a touch on the stated shape — the human open summary moves no session line; a deviation routes back); master `…/PLAN-master-planner-20260915-041518.md` (Q1 both verbs; the re-execution condition; Q5/Q6), `…-043301.md` (`--offline` IN both verbs), `…-131404.md` (all gates IN; the three dispositions; the plan-face list).

---

## Identity

```text
PLAN artifact      docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep2b-20260915.md  (this file; rev8)
PLAN_LOCK_ID       intg-substep2b-plan-20260915 @ sha256 <the artifact's own sha256, carried on the PLAN relay>
DESIGN record      design-doc — the sealed set above; primary lock m1-addendum-M-2966b839-lock-20260825 (post-stamp 57d89625…),
                   consumed locks m3-addendum-6-c41d015f-lock-20260825 (post-stamp 7ce2251d…), m3-addendum-7-4c40fe37-lock-20260827
                   (e4a6b982…), m3-addendum-8 lock d686e39a (b4ed44ce…), m1-addendum-N-82293732-lock-20260827, m1-addendum-O-63c46631-lock-20260901
BASE (B)           origin/main = 186adf7d67171bd7afe621f39b657a1a113ce299 — the R-4.49 landing merge, the PUBLISHED PIN; re-read at Task 0
BRANCH             intg/substep2b-wiring — does not exist yet (no local ref, no remote head); Task 0 cuts it with a FRESH worktree
WORKTREE           /Users/jack/Programming/bivpak-intg-substep2b-wiring
EVIDENCE HOME      $HOME/Programming/bivpak-evidence/s2b-<token>-XXXXXX (durable root; never the OS temp root; never inside a repository)
ENGINE FENCE       m-1 rev4 `161701` + m-1.implementer's binding approve `intg-2b-wiring-act-m1-fence-review-r4/DESIGN-REVIEW-implementer-
                   20260916-171135.md` — the fence of record; pinned by the plan-7 carrier's DESIGN_SOURCE_COMMIT a1ce40a930b5fd01d905e8295c3a9e581455a1c7
                   (master 010159; relay-lint's own xroot_authority PASS at that tree — executed at this seat as the must-be-YES, with the
                   pre-approve trees 4636fcef / 74810810 FIRING "selected review is not later than selected origin" as the must-be-NO); the
                   root sweep re-runs once with the filed plan-7 in scope
LOCK IDS           THREE contingent lock ids, each binding at ITS lock whichever revision locks (master 080937): A9 — LOCKED
                   `m3-addendum-9-40eaea22-lock-20260916` (pre-stamp 40eaea22 @ c2f7a6c7; post-stamp ae272647) → c3h + c6a RELEASED; A10 (`m3-addendum-10-20260916`) → c4b; A11 (`m3-addendum-11-20260916`) → c6b; gate files $RUNNERS/m3-addendum-9-lock.txt /
                   m3-addendum-10-lock.txt / m3-addendum-11-lock.txt (lock id + doc sha256 + the m-3 lock relay + master's seal relay [+ the two T-PARTIAL fields for A11], carried by the pair Planner; Task 6b Step 0 binds each carrier by header, lineage and bytes)
TOKEN              the pair Planner's bare dispatch token, PARENT = the implementer's exact-hash approve of THIS artifact; under it c1a, c1b, c1c, c2, c3,
                   c4a, c5 proceed (they consume NO A9/A10/A11 row — c3 is the CLI WITHOUT the two help lines and the golden re-pin);
                   c3h (the help lines + golden, A9 lock), c6a, c4b, c6b each HOLD at their contingency; c7–c9 after all four
VEHICLE            ONE push of intg/substep2b-wiring (class a), ONE PR against main; `main` is NEVER pushed by this plan
LANDING            the operator's bare merge token under .relays/intg from the operator's seat; the landing census FOR the merge head is Task 12's
                   (POST-merge, under that token; Task 11 is the PRE-merge rehearsal at H0 + the landing declaration; Task 10 is the vehicle); R-4.52
CLOSURE            the commission-closure SITREP is the LAST task (Task 12): final pin, FOUR worktrees disposed with receipts, evidence homes sealed
                   and named, open residuals handed to owners by row; no further act routes to the pair without a fresh commission
```

## Global constraints (each line binds every task)

- SEALED TEXT ONLY: where M/N/O, A6/A7/A8/A2-D4, SR-URL and the owner cuts DETERMINE, execute byte-exactly; anything they defer or are silent on is a STOP UP the pair line (m-1 S-2b-1..8; m-3 S-1..S-6; M-R7; A6-R7; A7-R5) — never a keyboard call. A STOP is a SITREP to the pair Planner naming the cell; work continues on every task that does not depend on it.
- VETO 9 MECHANICAL (m-1): in `git log --reverse B..H`, every commit touching `src/core/repo/**` precedes every commit touching `src/cli/**`, `src/core/pack/**`, `src/core/scan/**`, `src/core/open/**`; NO commit touches both sets. This plan has exactly THREE engine commits (Task 1: c1a, c1b, c1c, each its own commit) and they are the first three commits above B (V-2b-1 rev3).
- ENGINE BYTES (V-2b-1 rev3, fence 131522 §1): zero in `src/core/repo/**` beyond Task 1's THREE pre-authorized diffs — c1a `eligibility.{hpp,cpp}` (the offline mode, placed AFTER the unborn/shallow return at :154-156, binding the born non-shallow lane only), c1b `discover.cpp` (the `.biv` DISCOVERY skip root-scoped; nested `.biv` walked; `.git`-named directories unwalked; symlinked directories unwalked; the marker test :56-70 unchanged) and c1c `restore.{hpp,cpp}` (`bool restore_invokes_git(const RepoEntry&) noexcept` exported — one declaration + one grounds comment; defined as `!entry.shallow && !(entry.head_state == HeadState::unborn && !entry.bundle && !entry.eligibility)`; `restore_entry`'s two no-git early returns at :443-452 become ONE guard on it, shallow arm first, behaviour-preserving; numstat bound restore.hpp +2/-0, restore.cpp one hunk + one function — any other line red); any other engine need is a STOP (S-2b-5; the third diff's authority is fence rev3 itself, reviewed — never inferred, never in-lane). SCAN PAYLOAD RULE (V-2b-5 rev2): `scan.cpp`'s any-depth `.biv` payload skip (:140-142 at B) stays AS LANDED byte-for-byte — ADDENDUM-I is UNSEALED (R-4.55); a candidate touching it is red. FORMAT BYTES (V-2b-2): zero in `src/core/manifest/**`; the C-2 pack hunk (`pack.cpp` "manifest_json" propagation) byte-identical to a2f6fd1's.
- RepoEntry PRODUCTION CENSUS (V-2b-4): zero writes to any RepoEntry field outside `src/core/repo` — pack copies the entries `classify`/`capture` return WHOLE into `manifest.repos`; `CaptureResult.artifacts` are written as members at their `archive_path` VERBATIM (no renaming, no path synthesis). The grep is Task 9's census; a hit is a STOP.
- NON-BYPASS (m-4; S1): no direct git spawn in product code outside `src/core/repo`; every product network path flows through `invoke_git` with exactly ONE carrier endpoint; the hook is installed ONLY through the A6/A7/A8 fabric; consent binds the RAW in-memory value.
- HOOK TRUTH TABLE (A7-R1/R2; R-4.47 V3; RECONCILE R4 I2B-02): `--accept-url-divergence` → the always-proceed hook regardless of TTY state; no flag AND `isatty(stdin) && isatty(stderr)` → the interactive PROMPT D hook; otherwise NO hook (the engine's absent-hook posture refuses, typed). `--json` appears in NO row. `--offline`/`--network` appear in NO row (V-OFF (3)). No environment or config override exists (A7-R1; proposing one is a STOP to master).
- ONE PREDICATE (V-A7-1): `main.cpp:277`'s inline `isatty(STDIN) && isatty(STDERR)` conjunction for PROMPT B is replaced by `biv::cli::interactive_url_hook_installable()`; B's OTHER conditions (`any_sessions`, `!consent_specified`, `!json`) stay exactly as landed; nothing of B's `!json` is copied into D.
- CONSENT SURFACES ARE STDERR-ONLY (A6-R4; m-3 S-4; RECONCILE R4 I2B-03): the accepted notice at FIRST proceed per triple; per-entry refusal lines in ENCOUNTER ORDER; EXACTLY ONE run-level guidance line after the last per-entry line; the human open SUMMARY is SUPPRESSED for all of them; `src/core/open/render.cpp` is NOT in the write set; the writers emit whether or not sessions exist.
- GOLDEN BYTES (V-A6-2, V-A8-4): every A6 template is the landed byte sequence in `url_consent.cpp`; every A2-D4 listing byte and the `UnclaimedGitEntry` detail template come from m-3 130818 §3/§4 VERBATIM (reproduced in Tasks 3/5/6 below); no other user-facing text is authored in this act (R4 positive form: every m-3 surface byte the candidate carries is one the sealed texts or the cut determines).
- A8 INSIDE THE RENDERERS (A8-R1/R2; R-4.48 (ii)): every bound placeholder of the four A8-R2 renderers passes through the consent-render encoder EXACTLY ONCE inside the renderer; callers pass RAW facts; the shared `display()` is byte-unchanged; machine carriers stay RAW (byte-exact for valid UTF-8); `render_run_guidance_line` stays outside the census.
- ARM-1 REALITY (m-1 074712; STEP4-DESIGN-PACKAGE §2): the landed engine captures CLEAN SINGLE repositories only — `classify.cpp:347-357` runs `git status --porcelain=v2 -z` and ANY output (tracked changes OR untracked files) sets `Fence::dirty`; a nested boundary sets `Fence::nested` (:146); a gitlink `Fence::submodule` (:134); an unmerged index `Fence::unmerged` (:179) — each a WHOLE-OPERATION typed refusal at pack (Q11): NO image, never a per-repo exclusion, never full+note. Therefore EVERY fixture this plan packs is CLEAN (committed), with IGNORED files (`.gitignore`d, absent from porcelain v2) as its penumbra; no leg asserts a dirty, nested or submodule pack succeeds; `capture.cpp` writes `repo.bundle` and `local-refs.bundle` ONLY (:282-306, :371-403) — no patch artifact exists at 2b (Arm 2), and `restore.cpp` applies none.
- CONTINGENT TERMS (master 131404 (1); RECONCILE R5 MUST-2B-04): the ONLY cells that proceed on a default are the ones a sealed text DETERMINES; every genuinely undetermined cell HOLDS BEFORE ITS BYTES ARE WRITTEN — not before its commit — until the owner's exact word (or lock) is carried into the gate file the term names (rev6: the three lock files $RUNNERS/m3-addendum-{9,10,11}-lock.txt, $RUNNERS/m3-help-order.txt, and the RULED words carried in-plan from 074712/075225/080308); an owner word that changes a planned task produces a NEW hash-bound plan revision, never an unreviewed branch inside this pin. The `UnclaimedGitEntry` kind's NAME / exit-map ROW / detail TEMPLATE / the two test flips wait on A9's lock (Task 6 Step 0); the narrowed class itself EXISTS and fails closed under the shipped literal regardless. The offline JSON outcome word is SEALED `offline-pointer` (ADDENDUM-D :78; A2 :110) — build it; m-1 confirms at review, nothing waits.
- SAME-COMMIT RULE (V-A6-3; V-M-INT-3): a commit that lands the new kind lands, in the SAME commit, the `ErrKind` member, `to_string`, the exit-map row (`schemas/biv-exit-map.v1.json` — the PUBLISHED contract that moves; the envelope schema types `error.kind` as a free string and carries NO kind enumeration, A9.3, so no envelope-schema byte moves for the kind), the `exit_for_error` arm, the `ExpectedRow` list + the literal in `tests/test_envelope.cpp`, and the recomputed selftest blob pin (`harness/selftest/test_envelope.py` — a `harness/**` byte; see the population rule below).
- HARNESS BYTES: `harness/**` bytes belong to TWO owners' commits only — m-3's harness commit (Task 8, arm-A shape) and the selftest-pin recapture that the same-commit rule forces (which rides INSIDE the kind's product commit, as sub-step 1 did). ANY change to the pytest COLLECTED POPULATION at H (a new scenario's selftest; a new selftest test) fails the rev12 bar's C-2 BY CONSTRUCTION and the `015244` interleaved series (N = 10 per tree) RUNS INSTEAD (m-3 §6, m-4 035001) — Task 9 budgets it; it is not discovered at the gate. `src/adapters/**` bytes: ZERO (adapter-anchor rule; a touch routes UP and re-engages the companion-pin rule). `harness/bivharness/e3.py` pins: untouched.
- COUNT CELLS (I2B-08): the workflow cells count Catch2 CASES (`OverallResultsCases`); Task 9 measures the observed case tuples at H on BOTH platforms against B's literal cells; the companion count-cell commit (Task 9 Step 5) exists ONLY if a tuple moved; an unchanged result is reported as such. No remote CI is triggered by this plan.
- EVIDENCE TIERS (I2B-07): a product-command test against a HAND-BUILT image is E2 evidence of the open verb's bounded behavior, labelled `provenance=hand-built, interim`; the same leg against a `biv pack`-PRODUCED image is the record's leg (`provenance=product-packed`); the packet cites ONLY product-packed receipts for the open side (master 041518's condition). The round trip itself is its own row (R-T in the matrix).
- NO PERSISTENCE (V-A6-1; M veto 5): no approval is written anywhere; a6·13 witnesses it across runs.
- NO NEW ARGV/ENV/CONFIG SURFACE beyond exactly `--offline` (pack + open) and `--network` (open) per A9.4 (V-A7-4; V-OFF (5)); `list`/`info` parsing is NOT touched — at the pin those branches return without examining trailing tokens (args.cpp:283-290), so the two flags leave the stubs BYTE-UNCHANGED unless A9's lock advances a bounded enforcement (T-LIST).
- Every commit in the worktree is authored as `intg.pair-implementer`; NO `Co-Authored-By` trailer on any commit; commits stay green on macOS (`ctest --preset ci-macos -E '^safety-hardening$'`); TDD red states live only in the working tree.
- Host worktree `/Users/jack/Programming/bivpak` product paths stay byte-clean; all product work happens in the WORKTREE; the relay daemon is served from the host checkout.
- The GitHub token never enters any container, receipt, or relay; credential VALUES are never read, recorded or echoed (names only); no matched census token is ever printed into a relay or a tracked file (digests only).
- Release hold ABSOLUTE; merge ≠ push ≠ publication ≠ release.

## Boundary contract (protocol form)

```text
Writes (WORKTREE only, branch intg/substep2b-wiring, cut from B):
  ENGINE (Task 1 only, the FIRST THREE commits) c1a: src/core/repo/eligibility.{hpp,cpp}; tests/test_repo_engine.cpp (the 19 call sites gain the mode; W-O1..3)
                                           c1b: src/core/repo/discover.cpp; tests/test_repo_engine.cpp (W-D1..3 engine halves; the :815 discover case is the W-D2 control)
                                           c1c: src/core/repo/restore.{hpp,cpp}; tests/test_repo_engine.cpp (W-G1..3)
  FABRIC (Task 2)                          src/cli/url_consent.{hpp,cpp}; src/cli/consent_display_table.hpp (GENERATED, checked in);
                                           tools/gen_consent_display_table.py (the generator); tests/test_url_consent.cpp (NEW; biv_tests source list
                                           in CMakeLists.txt gains it)
  CLI (Tasks 3, 4, 5, 6)                   src/cli/args.{hpp,cpp}; src/cli/main.cpp; src/cli/url_consent.{hpp,cpp} (the A9 renderers, Tasks 4 and 6);
                                           tests/test_cli.cpp; tests/cli_run.hpp (NEW, Task 3); tests/test_wiring.cpp (NEW, Task 7); tests/test_url_consent.cpp (NEW, Task 2)
  OPEN (Task 4)                            src/core/open/open.{hpp,cpp}; src/core/report/envelope.{hpp,cpp} (the machine-carrier valid-UTF-8
                                           invariant at every bound-value emission — A8-R1/R2's census; the open result's repos[] rows ONLY under
                                           T-JSON's word); schemas/biv-json-envelope.v1.schema.json (ONLY with T-JSON's word, same commit as the
                                           emitting bytes; V-A6-3) + harness/selftest/test_envelope.py pin recapture when the schema moves
  PACK (Tasks 5, 6)                        src/core/pack/pack.{hpp,cpp}; src/core/scan/scan.{hpp,cpp}; tests/test_pack.cpp; tests/test_scan.cpp
  KIND (Task 6, contingent on A9's lock)   src/core/support/error.{hpp,cpp}; src/core/report/envelope.cpp (exit arm); src/core/scan/scan.cpp (the
                                           kind literal); src/cli/url_consent.{hpp,cpp} + src/cli/main.cpp (the rendered detail, one string two
                                           carriers); schemas/biv-exit-map.v1.json; tests/test_envelope.cpp (ExpectedRow + literal + TC-1..3 folds);
                                           tests/test_scan.cpp, tests/test_pack.cpp (the RAW core contract), tests/test_cli.cpp (the rendered CLI
                                           contract); harness/selftest/test_envelope.py pin
  HARNESS (Task 8, m-3's commit)           harness/scenarios/** ONLY, authored at m-3's seat, applied verbatim as ONE commit
  COUNT CELLS (Task 9 Step 5, iff moved)   .github/workflows/s2-harness.yml count cells ONLY
  DOCS LANE (host checkout, pair Planner)  docs/sprints/2026-08-27-intg-consent-fabric/** (this plan, receipts of record, census population)
ZERO BYTES:   src/core/repo/** beyond Task 1's c1a/c1b/c1c; src/core/scan/scan.cpp's `.biv` payload skip (:140-142, V-2b-5 rev2); src/core/manifest/**; src/adapters/**; harness/bivharness/**; harness/selftest/** beyond the pin
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
c1a engine: run_eligibility gains the offline mode, COMPOSED with N/G/H (m-1 S-2b-1 rev2; V-2b-1 rev2)   Task 1   src/core/repo/eligibility.*, tests/test_repo_engine.cpp
c1b engine: discover.cpp's `.biv` discovery skip root-scoped (m-1 V-2b-1 rev2 §2; W-D1..3)             Task 1   src/core/repo/discover.cpp, tests/test_repo_engine.cpp
c1c engine: restore_invokes_git exported + used by restore_entry's own no-git returns (fence rev3 §1)  Task 1   src/core/repo/restore.{hpp,cpp}, tests/test_repo_engine.cpp
c2  fabric: A8 consent-render policy inside the four renderers + the generated clause-5 table    Task 2   src/cli/url_consent.*, src/cli/consent_display_table.hpp, tools/, tests/test_url_consent.cpp, CMakeLists.txt
c3  cli: flags (--offline pack/open, --network open, conflict), hook install, flag read,        Task 3   src/cli/args.*, src/cli/main.cpp, src/core/pack/pack.hpp, src/core/open/open.hpp,
         B-predicate dedup, stderr writers, split PTY helper — NO help-line byte, NO golden re-pin              tests/test_cli.cpp, tests/cli_run.hpp
c3h cli: the two help lines at A9's locked position + the a6·18 golden re-pin — A9 SEALED, lands after c5    Task 3   src/cli/args.cpp (help_text only), tests/test_cli.cpp (the golden only)
c4a open: repos/ member class + stage routing; restore_entry per row (§2.2 order); in-memory rows;   Task 4   src/core/open/*, src/core/report/envelope.*, src/cli/main.cpp, src/cli/url_consent.*,
         the machine-carrier invariant; offline-pointer rows; the D4 listing; refusal rows;               tests/test_cli.cpp, tests/test_envelope.cpp (+ schemas/biv-json-envelope.v1.schema.json and
         tests (hand-built images); tests/test_open.cpp:343 re-oracled (rev13)                            harness/selftest/test_envelope.py ONLY under T-JSON's word)
c5  pack: discover → classify → eligibility (mode) → capture leaves-first → repos[] + members;   Task 5   src/core/pack/*, src/core/scan/*, src/cli/main.cpp (pack refusal detail), tests/test_pack.cpp,
         single-writer exclusion; the narrowed .git class behind a typed refusal                          tests/test_scan.cpp, tests/test_cli.cpp
c6a kind: UnclaimedGitEntry (retire RepoDiscoveredUnsupported) — CONTINGENT on A9's lock;        Task 6a  src/core/support/error.*, src/core/report/envelope.cpp, src/core/scan/scan.cpp, src/cli/url_consent.*,
         TC-1..3 folds ride the same test_envelope.cpp re-cut                                             src/cli/main.cpp, schemas/biv-exit-map.v1.json, tests/test_envelope.cpp, tests/test_pack.cpp,
                                                                                                          tests/test_scan.cpp, tests/test_cli.cpp, harness/selftest/test_envelope.py (pin)
c4b open rows + D3 + Q13: result.repos + schema (same commit); the D2/D3 network-consent surface;    Task 4   src/core/open/*, src/core/report/envelope.*, schemas/biv-json-envelope.v1.schema.json,
         the durable offline artifact + bundle_path/reconstruct (one idiom per HEAD state) — CONTINGENT on A10's lock          harness/selftest/test_envelope.py, src/cli/main.cpp, src/cli/url_consent.*, tests/test_cli.cpp
c6b kinds: the nine A11 wire kinds (ErrKind 27→36; exit map 29→38; sentences; error objects; the      Task 6b  src/core/support/error.*, src/core/report/envelope.cpp, src/core/pack/pack.cpp, src/core/open/open.cpp,
         open failed row + failed-mid-apply composition) — CONTINGENT on A11's lock                            src/cli/url_consent.*, src/cli/main.cpp, schemas/biv-exit-map.v1.json, tests/*, harness/selftest/test_envelope.py
c7  tests: the re-execution of every open-side leg against product-packed images; FX-M-1 (d)
         + (a)-interactive; a6·1–13; a7·1–5; a8·5/a8·6; N (a)/(g); E3 witness — one commit
c8  harness: m-3's ONE harness commit (arm-A shape; authored at m-3's seat; applied verbatim)     Task 8   harness/scenarios/** only
c9  ci: count cells (IFF a case tuple moved at H0 on either platform) — committed INSIDE the       Task 9   .github/workflows/s2-harness.yml only
         Task 9 runner by cellpatch.py after both platform observations
ORDER RULE: c1a c1b c1c c2 c3 c4a c5 are the token's UNCONDITIONAL prefix (every one of them lands as a COMMIT with no working-tree residue — a
working-tree partial is not a history prefix; MUST-2B-14); c3h, c6a, c4b, c6b land AFTER c5 in the order their locks land (each its own
commit, each citing its lock id + doc sha256; c3h and c6a share A9's lock and land c3h then c6a); c7 lands after the LAST of them (its
A9/A10/A11 legs need their bytes); c8, c9 after c7. Veto 9
holds regardless of that order (none of them touches src/core/repo).
H0 = the branch head after c8 (the object every suite observation and owner census is taken on); H = the FINAL head after c9 (== H0 iff no cell
moved); the runner proves `git diff H0 H -- . ':!.github/workflows/s2-harness.yml'` EMPTY so every H0 receipt carries to H, and writes H.txt LAST.
The three owner byte reviews, the GO relay and the vehicle bind H. NO commit touches both {src/core/repo} and {src/cli, src/core/pack,
src/core/scan, src/core/open}.
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
E2     the wiring census: every new product→engine   Task 9 Step 1                    grep at H0 (carried to H) E1   lane produces; m-4 RE-DERIVES
       entry point per-site file:line (discover/classify/run_eligibility/capture/restore_entry), PLUS the closure proof: zero `invoke_git(`
       and zero spawn primitives outside src/core/repo (the product never constructs an invocation; the one-carrier rule is the engine's
       — its six network-class sites content-identical to B's)
E3     fail-safe witness: divergence + no hook +      Task 7 (macOS) + Task 9 (Linux)  product-packed        E2     lane executes both platforms; m-4 reads receipts, may re-run macOS
       non-interactive ⇒ url_divergence_refused naming BOTH addresses
RCPT-P the PACK-side COND-6 no-network receipt (m-1 rev2 §1): Task 7                           product-packed        E2     m-1 §1 rev2 (the owner's receipt); m-4 reads
       under --offline the request trace shows ZERO GitCallClass::network spawns for the whole pack; the manifest diff with/without
       the flag touches ONLY born non-shallow rows' eligibility + capture_mode + the derived members (W-O1..3 shapes byte-identical)
E4     the OPEN-side N-R4 parity receipt (m-1 rev2 §1; Task 7                           product-packed        E2     lands WITH E5 (m-4 rider); m-1 §1 rev2; m-3 A9.4 OPEN
RCPT-O m-3's surface): the shallow entry's shallow_pointer row IDENTICAL with/without --offline, zero git for the entry; every
       non-shallow row under --offline is an ADDENDUM-D offline-pointer row, MANIFEST-DERIVED, restore_entry NEVER called (zero
       engine reach on the whole open by request trace — no open-side engine input exists)
WIT-O  W-O1 born shallow / W-O2 unborn with a side ref / Task 1 (engine) + Task 7 (product) unit → product-packed E2     m-1 V-2b-9 rev2
       W-O3 empty unborn: pack --offline leaves the N / G / H shape unchanged (single-coordinate arms beside the COND-6 positive)
WIT-G  W-G1 oracle pairing (born overlay / G unborn-with-refs   Task 1 (engine, c1c) + Task 7 (trace)  unit → product-packed E2     m-1 fence rev3 §1
       full / H payload-only / N shallow → restore_invokes_git == (≥1 git spawn from restore_entry): T/T/F/F); W-G2 drift mutant
       (one conjunct negated ⇒ exactly one class red); W-G3 single-source census (ONE call in restore_entry; no other pre-git return)
WIT-D  W-D1 nested .biv with a repo → discovered with  Task 1 (engine) + Task 7 (product) unit → product-packed E2     m-1 V-2b-9 rev2; m-4 (hostile class)
       parent edge / W-D2 root .biv control → not discovered / W-D3 nested .biv declared in .bivignore → pruned (engine half) + the
       pack-end prune summary names it (product half — discover() returns no printable report) / W-D4 the W-D1 repo's subtree absent
       from the parent's payload census (a negative-membership observation credited WITH V-2b-5 + m-1's byte review, per 044559)
E5     the unreachability grep FLIPS to exactly E2's  Task 9 Step 1                    grep at H             E1     lane produces; m-4 RE-EXECUTES
R-T    the pack → open round trip (payload byte-      Task 7 (product-packed legs);    product-packed        E2/E3  m-3 §5 (the harness receipt, E3 through the real CLI); m-1 V-2b-8(iv) reads it
       compare; a CLEAN repo with an ignored penumbra  Task 8 (m-3's scenario)
       file + a local branch restored; manifest rows)
E1-A10 A10.4 legs (a)–(m): D3 notice/prompt before  Task 4 (interim, c4b) → Task 7   hand-built → product  E2     m-3 (A10 at its lock); m-4 cell (v) (hostile-output surface)
       any git; decline ⇒ offline-pointer rows exit 0; --network; --json parity; --offline never; PROMPT D untouched; the rows; hostile
       URL bytes; the born/unborn/detached reconstruct idioms run into both target states (j); exact argv under the single-quote rule
       (k); the fallback for non-copy-safe operands (l); offline-unborn sha (m); the durable artifact (RCPT-Q)
E1-A11 A11.5 legs (a)–(l): the three fences, unmerged, Task 5 (seam, c5) → Task 6b (kinds) → Task 7  product-packed / shim  E2   m-3 (A11 at its lock); m-1 §1/§3 (grain); m-4
       ref-uncapturable, promisor both arms, git failed pack/open, budget, restore failed, op absent, unknown stays InternalError, counts
RCPT-Q the Q13 durable artifact: after open --offline   Task 7                           product-packed        E2     m-1 074712 §2 (apply half); m-3 A10.6 (UX half)
       <dest>/.biv/repos/<id>/repo.bundle exists for every full-capture row, checksum == checksums.json's, absent for overlay rows; zero git
CG     count gate: observed case tuples at H0 == the  Task 9                           both platforms        E2     m-3's pin rule
       workflow cells at H (after c9 iff a cell moved); skip sets unchanged (a changed skip set is a STOP, never a re-pin)
CEN    census FOR the merge head (R-4.49 instrument)  Task 12 (POST-merge; Task 11 =    main's post-merge head E2    Master Reviewer; the operator's token
       the pre-merge rehearsal at H0 + declaration)
VETO9  git log --reverse order + no-span check        Task 9 Step 2                    H                     E1     m-1
RPC    RepoEntry production census (V-2b-4): the      Task 9 Step 2                    H0                    E1     m-1
       TYPE-SCOPED census — every RepoEntry-typed binding outside src/core/repo enumerated, zero member writes on any of them; with a
       true-write mutant control (fires) and an unrelated-type write control (does not)
C2H    the C-2 hunk byte-identical to a2f6fd1's       Task 9 Step 2                    H                     E1     m-1 (V-2b-2)
```

## File structure (what each new or modified unit is responsible for)

- `src/core/repo/eligibility.hpp/.cpp` — `run_eligibility(git, entry, EligibilityMode)`; `EligibilityMode::offline` short-circuits every network call (COND-6) on the born non-shallow lane it binds (after the unborn/shallow return), forces full + `offline_declared` there, and refuses a promisor source through the engine's `promisor_objects_unavailable` class (R-4.1 arm (i) HOLD as m-1 recorded it).
- `src/cli/consent_display_table.hpp` (GENERATED) — the sorted table of scalars in `Cf ∪ Zl ∪ Zp ∪ Default_Ignorable_Code_Point` at Unicode 15.0.0 as `constexpr` `[first,last]` ranges + a header comment carrying the Unicode version, the two input files' sha256 and the generator's sha256. `tools/gen_consent_display_table.py` — the generator (inputs: `UnicodeData.txt`, `DerivedCoreProperties.txt`; deterministic output).
- `src/cli/url_consent.cpp` — gains `consent_display(std::string_view) -> std::string` (ONE consent-local encoder reproducing A8-R1 clauses 1–5 — `sanitize_utf8`, the three visible escapes, `\u00xx`, the clause-5 table, pass-through — the shared `display()` untouched) and routes EVERY bound placeholder of the four A8-R2 renderers through it exactly once; templates byte-unchanged. Gains the m-3-cut renderers of A9 (`render_unclaimed_git_entry_detail`, `render_offline_header`, `render_offline_row`; `render_offline_bundle_line` only under T-STAGE's word) so every m-3 template byte in the product lives in ONE file and every bound value passes the encoder ONCE (m-3's (ii) census widens from four renderers to seven or eight; stated, not hidden).
- `src/cli/args.hpp/.cpp` — `Command.offline`, `Command.network`; parse on the verbs m-3 §4 names; `collision`-style conflict rule → `usage("conflicting-flags")`; open help gains the two lines before `  --accept-url-divergence`.
- `src/cli/main.cpp` — `install_url_divergence_hook(...)`: builds the `UrlDivergenceRun`, the hook per the truth table, the stderr notice writer; wraps the verb's engine-reaching call in `ScopedUrlDivergenceRun`; converts run results into the report carriers; emits per-entry refusal lines + the guidance line (open) and the pack refusal detail (pack); the D4 listing (open `--offline`); B's predicate dedup.
- `src/core/open/open.hpp/.cpp` — `OpenOptions.offline`; the `repos/` member class in `read_archive_plan` (V-2b-7) staged under `<dest-parent>/<name>.bvpk-open.stage/`; `restore_entry` per row in §2.2 order after payload apply, inside the partial dir; `OpenReport.repos` (rows) + the refusal rows; offline: no `restore_entry`, `offline-pointer` rows from the manifest alone.
- `src/core/report/envelope.hpp/.cpp` — `machine_text(std::string_view) -> std::string` (= the landed `support::sanitize_utf8`: valid UTF-8 byte-exact, malformed content visibly replaced, NO display escape) applied at EVERY emission of a bound value the A8 census names — `error.path`, every `error.facts` value, the four fields of each `url-divergence-accepted` entry, the five fields of each `url_divergence_refusals` row — the memo/decision bytes in memory untouched (A8-R1 machine-carrier census + the malformed-value arm); `UnclaimedGitEntry` exit arm (Task 6); `result.repos[]` rows ONLY under T-JSON's word; `result.manifest.repos` stays the landed EMPTY array (RECONCILE R4 I2B-09 option (b); registered, not silent).
- `src/core/scan/scan.hpp/.cpp` — `scan(source_root, const ScanExclusions&)`: repo subtrees excluded from the payload walk (V-2b-5); a `.git`-named entry that is a discovered boundary's marker is skipped (never a payload node); a `.git`-named entry NOT claimed → the narrowed typed refusal (V-2b-6; kind per Task 6).
- `src/core/pack/pack.hpp/.cpp` — `PackOptions{offline}`; the sealed order (V-2b-3); leaves-first capture; artifacts as members at `archive_path` verbatim; `manifest.repos` = the entries whole; engine `url_divergence_refused` → `ErrKind::UrlDivergenceRefused` (path = repo; facts requested/effective/op); every other engine issue surfaces through today's engine-error path.
- `tests/test_url_consent.cpp` (NEW, in `biv_tests`) — a8·1–a8·4 on the eleven-row matrix; the table's membership witnesses.
- `tests/test_cli.cpp` — `run_cmd_pty_split` (stdin + stderr on the pty slave; stdout a pipe; all three child descriptor TTY states recorded); the fixture builders (bare "remote" repos + `url.<eff>.insteadOf <req>` rewrites in the repo-local config; born shallow source; promisor source; `.git` symlink); the product-scope legs.
- `tests/fixtures/` — none new on disk; every fixture is built in a temp dir by the test (reality-shaped: real `git init`, real `file://` remotes).

## Contingent terms and open cells (each is a plan TERM with a gate; none is a lane choice)

```text
RULE     (MUST-2B-04) a term marked HOLD writes NO product byte for its cell until its gate file holds the owner's exact word or lock;
         a term marked SEALED proceeds because a sealed text determines it and the owner only confirms at review; a term marked RULED
         proceeds on an owner word carried by master (080937) with the ruling relay named. A word that changes a planned task ⇒ a new
         hash-bound plan revision before the bytes move. THREE LOCK IDS bind the contingent commits, each at ITS lock whichever revision
         locks: A9 (LOCKED `m3-addendum-9-40eaea22-lock-20260916`) → c3h + c6a, A10 → c4b, A11 → c6b (gate files $RUNNERS/m3-addendum-{9,10,11}-lock.txt: `lock_id=<id> doc_sha256=<hex>
         relay=<path>`; the implementer re-hashes the addendum at the named pdc path — mismatch ⇒ STOP). The bytes each lock governs are
         planned here AS TERMS from the revision this plan TRANSCRIBES (A9 rev2 40eaea22 — LOCKED; A10 rev6 17fda846; A11 rev5 33c69913) and are re-verified
         against the LOCKED pin before they are written — a moved byte between the reviewed and the locked revision is a new plan revision.
T-KIND   RULED at the LOCK (master 170242; c6a RELEASED) — the UnclaimedGitEntry kind NAME / exit-map ROW / detail TEMPLATE / the two test
         flips are the LOCKED pin's bytes: `m3-addendum-9-40eaea22-lock-20260916`, pre-stamp `40eaea22…` @ pdc `c2f7a6c7`, post-stamp
         `ae272647…` (Domain Reviewer 134001 binding; Master Reviewer 141334). The pair Planner writes $RUNNERS/m3-addendum-9-lock.txt at
         Task 0 as `lock_id=m3-addendum-9-40eaea22-lock-20260916 doc_sha256=ae27264763b5ec20057b88f78f87d642ab22a28305a532c66c44063603eb2cf0
         pin_sha256=40eaea2273a32922640ade0f65b897ad8d52b40dc8eadef3845264fe1f40fa8c relay=master/relays/intg-2b-wiring-act/DESIGN-planner-
         20260916-165214.md`; Task 6a Step 0 re-hashes the live file (post-stamp) AND the c2f7a6c7 blob (pin) — either mismatch ⇒ STOP.
         BOUNDARIES on the stamp (binding): A9.4's D4 header/row bytes are the golden until A10's OWN lock — no bundle line is planned
         from A9; no sealed shallow / payload-only outcome is relabelled; the 29-row witness is A9's replacement-stage result. CARRIERS (MUST-A9-1, A8-R2): the detail is rendered ONCE
         by a renderer in url_consent.cpp with `<path>` and `<reason>` through consent_display, and that ONE string is both `error.detail`
         and the stream line; `error.path` carries the member path through machine_text.
T-HELP   RULED at the LOCK (c3h RELEASED) — the two help lines directly AFTER `  --accept-url-divergence` and BEFORE `  --agent-bin`
         (A9.4 at the locked pin; Q12; MUST-A9-2). c3 (unconditional) touches NO help byte and leaves the golden green; c3h inserts the
         lines and re-pins the golden ONLY from $RUNNERS/m3-help-order.txt (the pair Planner copies the two lines and their neighbours from
         the LOCKED file `master/domains/m-3-restore-cli/design/2026-09-15-addendum-9-unclaimed-git-entry-and-offline-cli.md` §A9.4 HELP
         at Task 0, with the lock id and post-stamp sha), landing after c5 in lock order (MUST-2B-14).
T-LIST   SEALED-as-measured — `--offline` / `--network` on `list` / `info`: the stubs return without examining trailing tokens
         (args.cpp:283-290); A9 rev2 PRESERVES the R-6.2 deferral verbatim. Task 3 touches NO list/info byte; the a6·14-shaped control
         asserts the stubs' outcome is byte-identical with and without the flags.
T-JSON   RULED → HOLD (Q9, m-3 075225; A10 rev2 §A10.1; A10 lock → c4b) — `result.repos`: an ARRAY present iff ≥ 1 manifest repos[] row was
         processed, ABSENT at zero state (never []); `result.manifest.repos` UNCHANGED; rows = RepoRestoreRow (restore.hpp:28-37) VERBATIM —
         id, relpath, outcome ∈ restored | shallow-pointer | payload-only-unborn | failed | offline-pointer, sha (40-hex or null),
         capture_mode ∈ overlay | full, local_refs[] {ref, recreated, skipped_at_sha, detail?}, advisories[], shallow {boundary[]} iff
         shallow-pointer; `failed` rows ADD kind (an A11 wire kind) + detail; `offline-pointer` rows ADD branch | "(detached)", remotes[],
         bundle_path? and reconstruct? (PRESENT on every full-capture row, ABSENT on overlay rows); manifest order; the schema row in the
         SAME commit as the first rendering (V-A6-3; R-4.32) with the selftest pin recomputed; V-A10-5 (no empty array; no field outside the
         set; no failed row without an A11 kind). Task 4 c4a keeps the rows IN MEMORY only; c4b emits them.
T-STAGE  RULED → HOLD (Q13, m-1 074712 §2 apply half + m-3 A10 rev6 §A10.6 UX half at 17fda846; A10 lock → c4b) — THE INTERIM IS OVER:
         under `open --offline` (or DECLINED) a row with `restore_invokes_git == true` whose `entry.bundle` is set AND whose member is in
         checksums.json has its `repos/<id>/repo.bundle` COPIED during apply into the §2.1 staging tree at <partial_dir>/.biv/repos/<id>/
         repo.bundle (checksums-verified file-level; `git bundle verify` NOT run — zero git) and carried by the single rename to
         <dest>/.biv/repos/<id>/repo.bundle — DURABLE, outliving the run; grounded on sealed pack-engine §1.2 (`.biv/` never payload) +
         restore-apply §2.3/§2.6 + ADDENDUM-D :64-70, NOT on unsealed ADDENDUM-I (R-4.55). Overlay rows write NOTHING (their
         local-refs.bundle stays in the image — R-4.58, m-1's question, the pair does NOT add it).
         FIELD CLASSES (A10.6): semantic DATA — bundle_path, branch, sha, relpath, remotes[] (raw on the machine carrier under A8-R2,
         display-encoded on the human carrier under A8-R1); command — `reconstruct`, a RENDERED COMMAND STRING shared by both carriers
         byte-for-byte, existing ONLY when copy-safe. bundle_path PRINTED = the ABSOLUTE <dest>/.biv/repos/<id>/repo.bundle; JSON = the
         dest-relative posix `.biv/repos/<id>/repo.bundle`.
         INTERPRETER POSIX sh (`/bin/sh -c`) only. SERIALIZATION every operand — <target> = <dest>/<relpath>, <bundle> = the absolute
         bundle_path, <branch>, <sha>, the two constant refspecs — SINGLE-QUOTED on the RAW bytes (an opening ', every ' replaced by
         '\'' , a closing '); nothing unquoted except the fixed words (cd, &&, git, init, --initial-branch=, fetch, --update-head-ok,
         checkout, --detach). COPY-SAFE iff every operand is valid UTF-8 AND A8-R1 is the IDENTITY on it (no C0/C1 control, no DEL, no
         Cf/Zl/Zp/Default_Ignorable code point); the printed line, the JSON reconstruct and what sh hands git are ONE byte sequence.
         FORMS — ONE idiom for EVERY target state (absent, empty, non-empty; `git init '<target>'` creates or re-uses the directory),
         selected ONLY by the row's stored HEAD state (a manifest fact):
           born      git init --initial-branch='bvpk-restore' '<target>' && cd '<target>' && git fetch --update-head-ok '<bundle>' '+refs/heads/*:refs/heads/*' '+refs/tags/*:refs/tags/*' && git checkout '<branch>'
           unborn    git init --initial-branch='<branch>' '<target>' && cd '<target>' && git fetch --update-head-ok '<bundle>' '+refs/heads/*:refs/heads/*' '+refs/tags/*:refs/tags/*'
                     (sha is "(no commits)": NO checkout — HEAD stays the symbolic unborn '<branch>' with no HEAD object; sealed G / W-O2)
           detached  git init --initial-branch='bvpk-restore' '<target>' && cd '<target>' && git fetch --update-head-ok '<bundle>' '+refs/heads/*:refs/heads/*' '+refs/tags/*:refs/tags/*' && git checkout --detach '<sha>'
         `git clone` is printed for NO row (it cannot target a non-empty directory and maps carried refs into refs/remotes/origin/).
         LINE — one per artifact-present row, AFTER all listing rows (A9.4's slot), one of:
           command   <relpath>: <reconstruct>   (partial/manual reconstruction — not a full restore)
           fallback  <relpath>: bundle at <bundle_path> — no copy-paste command: the path or branch carries characters a shell line cannot carry faithfully; reconstruct by hand from the bundle   (partial/manual reconstruction — not a full restore)
                     (values in the fallback are DATA per A8-R1; the JSON row carries bundle_path and NO reconstruct)
         NEVER a stored URL in either form; a display escape in a command; a command for a non-copy-safe operand; a product refusal
         because a path is not copy-safe. SUPERSESSION: at A10's OWN lock these lines replace A9.4's bundle template and its "one line
         per full-image row" (the Master Reviewer's boundary on A9's stamp: until then A9.4's D4 header/row bytes are the golden and NO
         bundle line is planned from A9). V-A10-7/8. rev5's "drain + verify, never materialize" routing stands at c4a (its pre-created-
         file discriminator too); c4b adds the durable placement + the command-or-fallback line + the two row fields.
T-NET    RULED → HOLD (Q8, m-3 075225; A10 rev2 §A10.2; A10 lock → c4b) — `--network` is NOT inert: A2 D3 EXECUTES at 2b (the first act where
         open reaches git; sealed VP must 2). TRIGGER: a NETWORKED open — the open plan holds ≥ 1 repos[] row whose restore needs a git
         NETWORK call (derived from the manifest row exactly as restore-apply §2.2 and restore.cpp's three network sites :250/:419/:545
         decide — an overlay row's clone from its remote; a full row's remote-proven local_refs fetch; the implementer records the
         derivation in $EVID/code/network-needing-rows.txt; if it cannot be derived from sealed text ⇒ S-A10-1 STOP to m-1 + m-3); rendered
         ONCE per run, on stderr, BEFORE ANY git subprocess (V-A10-1); `--offline` ⇒ never; zero network-needing rows ⇒ never. PREDICATE:
         A7-R1 (interactive_url_hook_installable() — stdin AND stderr TTYs; no override). INTERACTIVE: the NOTICE + PROMPT rendered
         atomically (A7-R3 shape), one line read: `y`/`Y` ⇒ git may run (PROMPT D still governs every divergent triple — V-A10-3); anything
         else / empty / EOF ⇒ ZERO git this run, every network-needing row becomes an offline-pointer row with A9.4's listing, exit 0.
         NON-INTERACTIVE: `--network` PRESENT ⇒ the NOTICE without the prompt line, git may run; ABSENT ⇒ no notice, no git, offline-pointer
         rows, exit 0. `--json` mirrors A7-R2 (the surface renders the same; stdout JSON-only; NO new envelope member — the record is the
         rows' outcomes). No persistence in any form (A6-R7(3)). Every printed value through consent_display (A8-R1). THE BYTES (A10.2,
         VERBATIM at its lock — the gate file carries them):
           Opening this image will run git to clone/fetch its repositories. This is git clone-grade trust — only open images you trust.
             manifest/stored URLs (informational):
               <relpath> · <url>[, <url>…]
             git may contact ADDITIONAL URLs found in repo metadata (.gitmodules, nested submodules, or host git config) that Bivpak does not see or police.
           Run `biv open --offline` to open with zero network access — files + sessions only, repos listed for manual clone.
           Run git for these repositories? [y/N] 
         (the prompt line interactive-only, terminal space, no newline; a row with no stored URL prints `<relpath> · (no stored remote)`).
         The hook truth table for PROMPT D is UNCHANGED — `--network` and the `y` answer appear in NO row of it (V-OFF (3); V-A10-3).
T-FENCE  RULED (Q11, m-1 074712 §1; carried by master 080937) — a Classification with fence != none at pack is a WHOLE-OPERATION typed
         refusal: pack produces NO image (the .partial discipline leaves nothing under the final name), the refusal names the repo and the
         fence's facts; NEVER a per-repo exclusion, NEVER full+note. `unmerged` (:179) is PERMANENT (ADDENDUM-B §B1; F56); `dirty` (:354),
         `nested` (:146), `submodule` (:134) are TRANSITIONAL Arm-1 boundaries, registered R-4.57 (owner m-1), each retiring with Arm 2/3/4
         by addendum, never in-lane. Task 5 MAY START: c5 surfaces every fence through the engine seam (`make_engine_error(issue.kind, …)`
         → ErrKind::InternalError + fact repo_engine_kind, exit 4 at c5) as a whole-operation failure with no image; the REFUSAL bytes
         (wire kind, class refusal/3, `transitional: true`, sentence, error object) are A11's and land in c6b at A11's lock. A `dirty` fence
         on an ordinary dirty repo is the Arm-1 boundary doing its job — not a STOP. The user's remedy (declare the path in .bivignore —
         I-R2a matcher first; commit/stash; resolve the merge) is stated by A11.3's sentences, never by this plan.
T-PROM   RULED (Q10, m-1 074712 §2; A11 rev1) — `promisor_objects_unavailable` is a WHOLE-OPERATION typed refusal reachable at PACK ONLY:
         (a) `--offline`, a born non-shallow promisor source whose full capture cannot complete; (b) online, any promisor-flagged
         invocation failing for a missing object (git_exec.cpp:345-349 — capture's bundle create is the live site). Open cannot raise it.
         A SHALLOW promisor source is N's cell — pointer row + promisor-source note, never refused (W-O1's promisor arm). At c5 it surfaces
         through the seam (InternalError + fact, no image); at c6b (A11 lock) it is `PromisorObjectsUnavailable` refusal/3 with facts
         repo_relpath, op, exit_code (engine) and offline = "true" | "false" (the CLI's own flag); NO `PromisorSourceOffline` member.
T-A11    HOLD (A11 lock → c6b) — the NINE wire kinds appended to ErrKind and the exit map AFTER UnclaimedGitEntry, in A11.1's order:
         RepoDirtyUnsupported / RepoNestedUnsupported / RepoSubmoduleUnsupported (pack, refusal/3, transitional: true — Arms 2/3/4),
         UnmergedIndexUnrepresentable / RefUncapturable / PromisorObjectsUnavailable (pack, refusal/3), GitInvocationFailed /
         GitBudgetExpired (pack + open, mid-fail/4), RepoRestoreFailed (open, mid-fail/4); GRAIN whole-operation on every row (pack: no
         image; open: failed-mid-apply — fresh target: the partial confined, NO workspace committed; collision-merge target: no atomicity
         promise, per-step inventory) — NO per-entry divergence/2 arm for engine failures; COUNTS ErrKind 27 → 36 (after A9's 27 → 27),
         exit map 29 → 38, refusal/3 rows 14 → 20, mid-fail/4 rows 4 → 7, transitional 4 → 7, the InternalError row UNCHANGED; UNKNOWN
         engine kinds STAY InternalError (never mapped by guess); error objects per A11.2 (common: error.kind = the wire kind, errno 0,
         facts.repo_engine_kind kept, error.detail = the A11.3 sentence encoded ONCE at the renderer — one string, both carriers);
         sentences per A11.3 VERBATIM (one line each; `<op>` = the engine's op fact or the word `call`; `[, offline]` iff facts.offline
         is "true"; `<N-3> more` iff N > 3); the open-side failed row (A10.1) carries kind + detail = the same sentence; the enum,
         to_string, the exit-map rows, the envelope arm and the tests land in ONE commit (V-A11-4; R-4.32); the selftest pins recomputed
         in it. url_divergence_refused stays as A6 sealed it (A11.6 (2)).
A10-REV  A10 is at rev6 (17fda846; rev5 db384844 approved binding 132531, superseded cleanly; rev6 under the re-approve) — the c4b bytes
         bind at the LOCK and are quoted here from rev6: the D3 TRIGGER = ∃ row with `restore_invokes_git(row) == true` (the ENGINE'S
         predicate, c1c, READ never recomputed; S-A10-1 if the export is absent); DECLINED = the `--offline` partition on that predicate
         (FALSE ⇒ CALL restore_entry — no git UNCONDITIONALLY, through success or a typed error: shallow-pointer per N-R4 identical
         with/without the flag, payload-only-unborn per H, no artifact; TRUE ⇒ offline-pointer row, artifact iff `entry.bundle` ∧ checksums
         membership, sha 40-hex or "(no commits)" iff unborn — never null; fence rev4's git-capable contract); reconstruct = a RENDERED COMMAND for POSIX sh, every operand SINGLE-QUOTED on the raw bytes, emitted ONLY when copy-safe
         (valid UTF-8 and A8-R1 the identity on every operand), else the FALLBACK line and no JSON `reconstruct`; ONE idiom for every
         target state selected by the stored HEAD state: born `git init --initial-branch='bvpk-restore' '<target>' && cd '<target>' &&
         git fetch --update-head-ok '<bundle>' '+refs/heads/*:refs/heads/*' '+refs/tags/*:refs/tags/*' && git checkout '<branch>'`;
         unborn `git init --initial-branch='<branch>' '<target>' && cd '<target>' && git fetch --update-head-ok '<bundle>' '+refs/heads/*:
         refs/heads/*' '+refs/tags/*:refs/tags/*'` (no checkout — the symbolic unborn HEAD with no object; MUST-2B-16 CLOSED with a form);
         detached `… && git checkout --detach '<sha>'`; `git clone` is printed for NO row; A9.4's bundle template SUPERSEDED at A10's lock.
ROUTED   the three A10/A11 findings of 085404 are SETTLED by their owners (each binding at its lock): (15) A10 §A10.6 — POSIX sh,
         single-quoted raw operands, copy-safe predicate, fallback line (rev4+, approved at rev5 132531); (16) A10 rev5 §A10.6 — the unborn
         idiom (`git init --initial-branch='<branch>'` + `fetch --update-head-ok`, no checkout) witnessed on git 2.50 (approved at rev5);
         (17) A11 rev5 OPEN INVARIANT — master's ruling (b): the landed `result` null iff `error` invariant is KEPT; the orchestrator
         writes `<partial_dir>/inventory.json` (`<partial_dir>` = the ONE partial-directory path T-PARTIAL authorizes — its suffix is the owner's word, not this plan's; completed rows, the failing row with kind + detail, the outcome, §2.2 order);
         `facts.partial_path` + `facts.repo_id`; no `result.repos` on failure; NO change to `execute_open`'s signature (that would be a
         fourth engine diff no fence authorizes) — c6b's composition is written from this at A11's lock. The D3 engine facts: INVOKES-GIT
         = c1c's exported predicate (fence rev4 `161701`, the third engine diff — its binding approve pending at 170247; T-NET releases on
         it and the carrier re-pins); ARTIFACT-PRESENT = `entry.bundle` ∧ checksums membership, no engine byte (membership never replacing
         the integrity/containment checks).
T-K      FX-M-1 leg (k) (carrier fail-closed) has no product input that constructs an invocation; it stays at the engine seam as the
         floor and E2's census (every product path carries exactly one endpoint) is its product-scope form — REGISTERED under S-6 with
         m-1 as owner, never silent.
T-C      a6·10 (flag ≠ PROMPT C) executes only if PROMPT C (memory merge) exists at B; Task 7 Step 0 greps for it; absent → REGISTERED
         under S-6 (m-3), never silent.
T-PARTIAL HOLD → RULED (A) by the owner (MUST-2B-21; pair 141053 → master 152800 → m-1.planner `intg-2b-wiring-act/DESIGN-planner-20260918-162306.md`,
         TO master, the pair CC — master's carry pending; the term RELEASES on the lock-file field, not on this citation): the open-side
         staging directory is spelled `<target>.bvpk-open.partial/` — the LANDED, verb-scoped form (open.cpp:637 at B); (B) is REJECTED;
         `open.cpp:637` is NOT touched by 2b. m-1's grounds, re-verified here: sealed restore-apply §2.1 (:105/:108/:110) and §3 (:206) and the
         rename map (:33) spelled `.bvpk-partial` and classed the open-side object "archive-file" — the conflation the landed code resolved:
         pack's object is a partial archive FILE (`<name>.bvpk.partial`, pack.cpp:550; R-4.61) and open's is a partial workspace DIRECTORY;
         two objects that can share a stem must not share a suffix. DR-2 executed: restore-apply §2.1 annotated status-only (PRE 2748e851…
         → POST 9e456b4d…, 9/0, zero lines removed); the rename-map row is master's to annotate; A11's next revision or its lock annotation
         spells `<target>.bvpk-open.partial` at its three sites (:82/:85/:167) — m-3's act. THE WORD ARRIVES as TWO fields in
         $RUNNERS/m3-addendum-11-lock.txt — `partial_suffix=.bvpk-open.partial` (the only admissible value) and `partial_suffix_relay=<the
         pdc path of the owner ruling: 162306, or A11's lock relay if it carries the spelling>` — and Task 6b Step 0 fails CLOSED without
         both. CONSUMPTION (one spelling, one site): the suffix is spelled at exactly ONE site in the product — the `partial_dir` expression
         at open.cpp:637 (whose literal must equal `partial_suffix`; c6b does NOT touch it); the inventory writer receives the `partial_dir`
         VALUE from that expression (`<partial_dir>/inventory.json`); `facts.partial_path` is `partial_dir.generic_string()` (the landed
         `with_partial_dir` pattern, open.cpp:354-356 — the fact renamed per A11.2); the `OpenPartialPresent` detection (open.cpp:638) and
         any clean-up reader test the SAME value; leg (h)'s witness derives its expected path as `<dest-parent>/<dest-name>` + the
         `partial_suffix` READ FROM THE LOCK FILE, never a literal in the test. Until the lock file carries the field: NO c6b
         open-composition byte names the suffix.
T-ARM    REGISTERED (S-6; R-4.57, owner m-1) — legs 2b CANNOT execute at product scope because Arms 2/3/4 are unlanded: (i) a
         staged/unstaged-change round trip (no patch artifact exists; capture.cpp:282-403); (ii) a nested-repo image from `biv pack`
         (Fence::nested refuses); (iii) capture leaves-first ordering and the open-side parents-before-children order on a product-packed
         image (needs (ii)); (iv) a submodule image. Each is written in $EVID/legs/registered.txt with its arm; the open-side ordering
         leg keeps its HAND-BUILT (synthetic-manifest) unit witness in Task 4 as the ONLY 2b witness, labelled so.
```

## Per-task runner protocol (measurement tasks) and the code-task discipline

Tasks 0, 9, 10 and 11 are MEASUREMENT tasks: each has exactly one `<!-- RUN: task-N -->` block below its steps and is entered ONLY through the runner protocol of `PL-intg-r449-line1-selection-20260913.md` (its BLOCKs `plan_blocks.py` and `run-task.sh` are reproduced in §Instruments below with the named changes and are extracted from THIS plan): `run-task.sh N` re-hashes the plan against `plan-lock.txt`, materializes `task-N.sh` from the plan's own bytes, proves it (`plan_blocks.py check … rc=0` WITH `gates>0` — every mandatory gate of the task is written in its prose as a backtick span carrying `|| STOP`, byte-equal to its runner line, so the checker BINDS the prose to the executable text; a task whose proof reports `gates=0` is unproved), `chmod 0500`s it, records its sha256 and invocation, and runs it exactly once. Every runner's first executable lines after the prologue are `set -o pipefail` and the `PIPEOK` function (the R-4.49 census instrument's form); every pipeline is followed by `PIPEOK <label>`; producers write to files and their status is checked BEFORE the file is read; every retained write is `|| STOP`-guarded and `[ -s ]`-checked; process substitution is not used (a producer writes a file, the consumer reads the file). Task 9 Step 0 runs the runner CONTROLS once: `PIPEOK` fails on `false | cat` (must-be-NO), a write into a read-only directory STOPs, and a producer that exits 1 with partial stdout is caught before its output is read — each in a subshell, each receipt recorded; a control that passes where it must fail STOPs the task.

**Step 0′ — resumption under a LATER token (rev17; the gap disclosed on the token 162507 and in 162750, the fold accepted by master 175324).** The runner protocol binds `$RUNNERS/plan-lock.txt` ONCE, before Task 0, to the first token's PLAN_LOCK digest, and `run-task.sh N` STOPs when the live plan's digest differs; every revision after Task 0 has executed therefore orphans the runners. A later token (a new PLAN_LOCK digest, a new DISPATCH_ID, the SAME evidence home — the plan names the home by the token that opened it and a second home would split the evidence) is entered through `resume.sh` (BLOCK in §Instruments, extracted from THIS plan with the fixed reader, run ONCE per token in the implementer's shell BEFORE any task under it: `bash resume.sh <EVID> <the token's PLAN_LOCK sha256, typed ONCE from the token relay> <the token's DISPATCH_ID, typed ONCE>`): it re-hashes the plan on disk and STOPs unless it IS the new lock; STOPs if the new lock equals the old one (nothing to resume — the old directory serves); binds a NEW runners directory (`mktemp -d` under `$HOME/Programming/bivpak-evidence/` as `s2b-runners-XXXXXX`, `pwd -P`) with `plan-path.txt`, `plan-lock.txt`, `token-id.txt`, `evid.txt`; re-extracts BOTH instruments from the NEW plan bytes (`py_compile` / `bash -n`, `chmod 0500`, digests), writes `blocks.txt` from `plan_blocks.py list`; CARRIES Task 0's receipts byte-for-byte from the previous directory (`task-0.sh proof-0.txt task-0.sha256 task-0.invocation.txt task-0.exit task-0.done task-0.proof-tail task-0.self.sha256 plan-hash-0.txt plan_blocks.sha256-0`) after proving `task-0.done` is `rc=0`, `task-0.sh` re-hashes to `task-0.sha256`, and both equal the copies Task 0 sealed into `$EVID/runners/`; CARRIES every gate file present in the previous directory (`m3-addendum-9-lock.txt m1-fence-rev4.txt m3-help-order.txt t-oracle.txt m3-r462-patch.txt m1-fence-word.txt m3-addendum-10-lock.txt m3-addendum-11-lock.txt m3-harness-patch.txt task-10-go.txt` — absent ones stay absent and their gates HOLD as before) and re-compares each copy; records `previous-runners.txt`, `previous-lock.txt`, `carried.sha256`; preserves the old `$EVID/runners-dir.txt` as `runners-dir.prev-<stamp>.txt` and writes the new path there; seals a copy of the binding files into `$EVID/runners/resume-<token>/`; prints the NEW directory's path as its ONLY stdout line — the implementer exports `RUNNERS=` from it. Task 9's controller then finds `task-0.done` in the new directory and the lock equal to the plan. Executed at the pair Planner's seat on a scratch mirror of the real directories (the must-be-YES) and against five mutants (a lock that is not the plan on disk; the same lock; `task-0.done` absent; `task-0.sh` altered; a malformed token id) — each STOPs before any write.

Tasks 1–8 are CODE tasks executed by the implementer as TDD steps in the WORKTREE: each step's command is run as written, its stdout+stderr+rc appended to `$EVID/code/task-N.log` (one `printf '### step %s rc=%s\n'` line per command), the commit sha of each task recorded in `$EVID/commits.txt` (`cN=<sha>`). A code task ends with `ctest --preset ci-macos -E '^safety-hardening$'` rc 0 and `git status --porcelain` EMPTY in the worktree.

## Tasks

### Task 0 — bootstrap: evidence home; helpers; B resolved; the THREE retained pair worktrees DISPOSED with receipts; the FRESH branch + worktree from B; venv + build; B observed on macOS

**Files:** none in the product tree (worktree operations, the evidence home, the build).

- [ ] **Step 0: the evidence home** — token id from `$RUNNERS/token-id.txt`; `mktemp -d "$HOME/Programming/bivpak-evidence/s2b-${TOKEN}-XXXXXX"` resolved with `pwd -P`; not the OS temp root; not inside a repository; subdirs `runners B H work census-raw code legs receipts`; `evid.txt` / `runners-dir.txt` cross-pointers; the runner artifacts copied in; `status-initial.txt` of the host checkout (product paths).
- [ ] **Step 0b: helpers materialized** — every python BLOCK extracted and `py_compile`d; every shell BLOCK extracted and `bash -n`'d; `helpers.sha256` written; `blocks.txt` == `$RUNNERS/blocks.txt`.
- [ ] **Step 1: B resolved and recorded** — `git fetch --no-tags origin refs/heads/main:refs/remotes/origin/main`; the gate `BASE=$(git -C "$MAIN" rev-parse origin/main) || STOP; [ "$BASE" = "$B" ] || STOP`; the workflow bytes at B → `cells.py` → `B-cells.txt`; `B.txt`; the observer names and the clang-tidy mirror manifest (Step 5b).
- [ ] **Step 2: the three retained pair worktrees DISPOSED (master 041518 Q5/Q6)** — for each of `../bivpak-intg-consent-fabric` @ `3cd31e4823d40c1c9ea020fcb51917618368533b` on `intg/consent-fabric`, `../bivpak-intg-format-act` @ `a2f6fd1adf67fd86c8d0c692db34f113a9691135` on `intg/format-act`, `../bivpak-intg-r449-line1-selection` @ `b74ec570e22646bfee6a0c554bcb766fffa6da19` on `intg/r449-line1-selection`: preconditions (path exists; HEAD == the pin; branch == the name; `status --porcelain` EMPTY) → the branch ref recorded BEFORE → `git worktree remove <path>` → the path absent → the branch ref UNCHANGED after → `git worktree list` no longer names the path → one receipt line per worktree in `$EVID/receipts/worktree-disposed-<n>.txt` (`disposed=<path> head_was=<sha> branch_was=<name> remove_rc=0 refs_unchanged=yes`). Branches stay; no other worktree is touched; no remote ref is touched.
- [ ] **Step 3: the FRESH branch and worktree from B** — no local ref `intg/substep2b-wiring`; no remote head of that name; the worktree path absent (`[ ! -e "$WORKTREE" ] || STOP`); `git worktree add -b intg/substep2b-wiring /Users/jack/Programming/bivpak-intg-substep2b-wiring 186adf7d…`; the gate `[ "$(git rev-parse HEAD)" = "$B" ] && [ "$(git rev-parse --abbrev-ref HEAD)" = intg/substep2b-wiring ] || STOP`; status EMPTY; `git rev-list --count origin/main..HEAD` == 0 (`cutpoint.txt`); `.venv-harness/` and `build/` git-ignored (proof recorded).
- [ ] **Step 4: venv + build at B** — python3.12 venv from `harness/requirements.lock`; import proof (`pytest jsonschema zstandard`); `cmake --preset ci-macos` (the `BIVHARNESS_PYTHON` cache line exactly once); `cmake --build --preset ci-macos`; `build/ci-macos/biv` executable; status EMPTY.
- [ ] **Step 5: B observed on macOS** — the five test binaries `-r xml` → `B/*-macos.xml` → `tuples.py` → `B/tuples-macos.txt`; `skipset.py` against `B-cells.txt`; status EMPTY after.
- [ ] **Step 6: the Unicode inputs** — `curl -fsSL` `https://www.unicode.org/Public/15.0.0/ucd/UnicodeData.txt` and `https://www.unicode.org/Public/15.0.0/ucd/DerivedCoreProperties.txt` into `$EVID/work/ucd/`; `DerivedCoreProperties.txt` line 1 MUST match `^# DerivedCoreProperties-15\.0\.0\.txt$` or STOP (m-3 S-2 — a version drift is a design act at m-3's seat); `UnicodeData.txt` MUST carry exactly 15 `;`-separated fields on its first line (`awk -F';' 'NR==1{print NF}'` == 15) or STOP; both files' sha256 → `$EVID/receipts/ucd-inputs.sha256` (these digests are copied into the generated header by Task 2).

<!-- RUN: task-0 -->
```bash
# Runner plumbing (Task 0)
set -o pipefail
PIPEOK() { local st=("${PIPESTATUS[@]}"); local k; for k in "${st[@]}"; do [ "$k" -eq 0 ] || { printf 'STOP-task-0 pipe=%s stage-status=%s line=%s\n' "$1" "${st[*]}" "${BASH_LINENO[0]}" >&2; exit 1; }; done; }
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
for name in cells tuples cellgate skipset selftest_summary finalize gen_consent_display_table series_verdict repoentry_census cellpatch xmlcases; do x=0; python3 "$RUNNERS/plan_blocks.py" extract "$PLAN" "$name.py" > "$EVID/$name.py" || x=$?; [ "$x" -eq 0 ] && [ -s "$EVID/$name.py" ] || STOP; p=0; python3 -m py_compile "$EVID/$name.py" || p=$?; [ "$p" -eq 0 ] || STOP; done
for name in linux-container.sh linux-suite.sh git-shim.sh census_population.sh; do x=0; python3 "$RUNNERS/plan_blocks.py" extract "$PLAN" "$name" > "$EVID/$name" || x=$?; [ "$x" -eq 0 ] && [ -s "$EVID/$name" ] || STOP; s=0; bash -n "$EVID/$name" || s=$?; [ "$s" -eq 0 ] || STOP; done
h=0; (cd "$EVID" && shasum -a 256 cells.py tuples.py cellgate.py skipset.py selftest_summary.py finalize.py gen_consent_display_table.py series_verdict.py repoentry_census.py cellpatch.py xmlcases.py linux-container.sh linux-suite.sh git-shim.sh census_population.sh > helpers.sha256) || h=$?; [ "$h" -eq 0 ] && [ -s "$EVID/helpers.sha256" ] || STOP
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
# Step 6 — the Unicode 15.0.0 inputs (m-3 §2; S-2)
for f in UnicodeData.txt DerivedCoreProperties.txt; do c=0; curl -fsSL "https://www.unicode.org/Public/15.0.0/ucd/$f" -o "$EVID/work/ucd/$f" || c=$?; [ "$c" -eq 0 ] && [ -s "$EVID/work/ucd/$f" ] || { echo STOP-S-2-ucd-unobtainable; exit 1; }; done
s=0; sed -n '1p' "$EVID/work/ucd/DerivedCoreProperties.txt" > "$EVID/work/ucd/dcp-line1.txt" || s=$?; [ "$s" -eq 0 ] && [ -s "$EVID/work/ucd/dcp-line1.txt" ] || STOP; g=0; k=$(grep -c -E '^# DerivedCoreProperties-15\.0\.0\.txt$' "$EVID/work/ucd/dcp-line1.txt") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || { echo STOP-S-2-ucd-version; exit 1; }
nf=$(awk -F';' 'NR==1{print NF}' "$EVID/work/ucd/UnicodeData.txt") || STOP; [ "$nf" -eq 15 ] || { echo STOP-S-2-ucd-shape; exit 1; }
h=0; (cd "$EVID/work/ucd" && shasum -a 256 UnicodeData.txt DerivedCoreProperties.txt > "$EVID/receipts/ucd-inputs.sha256") || h=$?; [ "$h" -eq 0 ] && [ -s "$EVID/receipts/ucd-inputs.sha256" ] || STOP
exit 0
```

### Task 1 — c1a, c1b and c1c, the THREE pre-authorized engine commits (m-1 V-2b-1 rev3, fence `131522` §1 over rev2 `171041` §1–§2 approved `044559`): c1a `run_eligibility` gains the offline mode COMPOSED with N/G/H; c1b `discover.cpp`'s `.biv` discovery skip root-scoped; c1c `restore_invokes_git` exported and used by `restore_entry`'s own no-git returns

**Files (c1a):** Modify `src/core/repo/eligibility.hpp`, `src/core/repo/eligibility.cpp`; Modify `tests/test_repo_engine.cpp` (the 19 existing `run_eligibility(` call sites gain `EligibilityMode::network`; the two offline cases; the three W-O cases).
**Files (c1b):** Modify `src/core/repo/discover.cpp`; Modify `tests/test_repo_engine.cpp` (the W-D cases; the existing `:815` discover case is kept byte-for-byte as the W-D2 regression control).
**Interfaces:** Produces `enum class EligibilityMode { network, offline };` and `expected<void> run_eligibility(const Git& git, RepoEntry& entry, EligibilityMode mode);` — no default argument (every caller states its mode; Task 5 passes the pack flag). `discover(root, matcher)`'s signature is UNCHANGED. Consumes nothing new.
**Sealed content (pack-engine §2 COND-6 as COMPOSED by m-1 rev2 §1 with N-R2/N-R3, G-R1/B2 and H):** the offline mode binds ONLY the lane that survives the existing first return (`eligibility.cpp:154-156`: `head_state == unborn || shallow` ⇒ `return {}` before any work) — born, non-shallow. In that lane offline ⇒ no `ls-remote`, no refresh fetch, `eligibility.result: offline_declared` (wire string already at `manifest.cpp:804`), `capture_mode: full`. A shallow row (N-R2: capture_mode ABSENT, eligibility ABSENT, local_refs EMPTY), an unborn row with refs (G: bundle + `unborn-head` + sha null + full) and an empty unborn row (H: no eligibility, no capture_mode) are UNCHANGED by the flag. R-4.1 arm (i) SCOPED: a born non-shallow PROMISOR source under offline REFUSES via `EngineErrorKind::promisor_objects_unavailable`; a SHALLOW promisor source is N's cell — never refused. A candidate whose offline branch PRECEDES the unborn/shallow return, or writes eligibility/capture_mode onto a shallow or payload-only-unborn row, is red.
**Sealed content (pack-engine §1.1; m-1 rev2 §2):** the ONLY discovery prune is `.bivignore` ("DO recurse for nested repo discovery"); `<root>/.biv` (the reserved area, root-anchored) is never a repo container and is not walked; a NESTED directory named `.biv` IS walked like any other directory; directories named `.git` stay unwalked (a marker is not a container); symlinked directories stay unwalked; the matcher precedes the marker test (as landed, I-R2a order); the marker test (`:56-70`) is unchanged. No second discovery traversal in pack, no pack-side workaround — the correction is at the engine or nowhere.

- [ ] **Step 1 (c1a): the failing tests** — in `tests/test_repo_engine.cpp`, using the existing `fake_network_git(...)` helper with a request trace (the sibling proven-remote case's arrangement):

```cpp
TEST_CASE("run_eligibility offline: zero network calls, offline_declared, full (COND-6 positive)") {
  // arrange: a born, non-shallow entry with one remote, exactly as the existing proven-remote case builds it
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
TEST_CASE("run_eligibility offline on a born non-shallow promisor source refuses typed (R-4.1 arm (i), scoped)") {
  entry.promisor = true;
  auto result = biv::repo::run_eligibility(git, entry, biv::repo::EligibilityMode::offline);
  REQUIRE_FALSE(result.has_value());
  CHECK(biv::repo::engine_error_kind(result.error()) == biv::repo::EngineErrorKind::promisor_objects_unavailable);  // the typed accessor at types.hpp:92-110
  CHECK(spawned.empty());
}
// W-O1..3 — the composed shapes: each snapshots the entry BEFORE the call and asserts NOTHING moved and NOTHING spawned.
// NAMED MUTANT for all three: an offline branch placed BEFORE the unborn/shallow return writes full + offline_declared (or, for the
// promisor arm, refuses) onto an entry N/G/H say it must not touch ⇒ RED.
static void check_untouched_offline(biv::repo::Git& git, biv::repo::RepoEntry& entry, std::vector<biv::support::SpawnRequest>& spawned) {
  const auto mode_before = entry.capture_mode; const bool elig_before = entry.eligibility.has_value();
  const auto refs_before = entry.local_refs.size();
  auto result = biv::repo::run_eligibility(git, entry, biv::repo::EligibilityMode::offline);
  REQUIRE(result.has_value());
  CHECK(entry.capture_mode == mode_before); CHECK(entry.eligibility.has_value() == elig_before);
  CHECK(entry.local_refs.size() == refs_before); CHECK(spawned.empty());
}
TEST_CASE("W-O1: a born SHALLOW source under offline keeps the N-R2 shape; a shallow promisor is never refused") {
  // arrange the entry as the existing shallow case does (entry.shallow set; capture_mode / eligibility absent)
  check_untouched_offline(git, entry, spawned);
  entry.promisor = true; check_untouched_offline(git, entry, spawned);  // N's cell: pointer row + promisor-source note, NEVER refused
}
TEST_CASE("W-O2: an UNBORN source with a side ref under offline keeps the G shape") {
  // arrange as the existing any-ref unborn case does (head_state unborn; the side ref present)
  check_untouched_offline(git, entry, spawned);
}
TEST_CASE("W-O3: an EMPTY unborn source under offline keeps the H shape") {
  // arrange as the existing zero-ref unborn case does
  check_untouched_offline(git, entry, spawned);
}
```

  Every existing call `run_eligibility(git, entry)` in the file becomes `run_eligibility(git, entry, biv::repo::EligibilityMode::network)` (19 sites; `grep -c 'run_eligibility(' tests/test_repo_engine.cpp` must read 19 + the new calls after the edit — recorded, not assumed).
- [ ] **Step 2 (c1a): run to verify failure** — `cmake --build --preset ci-macos` FAILS to compile (the enum and the third parameter do not exist). Expected: compile error naming `EligibilityMode`.
- [ ] **Step 3 (c1a): the implementation** — `eligibility.hpp`:

```cpp
enum class EligibilityMode { network, offline };
expected<void> run_eligibility(const Git& git, RepoEntry& entry, EligibilityMode mode);
```

  `eligibility.cpp`, inside `run_eligibility` AFTER the unborn/shallow early return (`:154-156`, UNTOUCHED and FIRST) and the HEAD-object check, BEFORE the remotes loop:

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

  (`eligibility` is the local `Eligibility{.method = "ls-remote-ancestry", …}` already constructed above the remotes check; the `method` literal is NOT changed by this act — if m-1's review wants a distinct offline method string that is m-1's word, S-2b-3 class.) No other line of `src/core/repo/**` moves in c1a.
- [ ] **Step 4 (c1a): run to verify pass** — `cmake --build --preset ci-macos && ./build/ci-macos/biv_repo_engine_tests` rc 0; `ctest --preset ci-macos -E '^safety-hardening$'` rc 0.
- [ ] **Step 5 (c1a): the veto-9 shape check, then commit** — `git status --porcelain` names exactly `src/core/repo/eligibility.hpp`, `src/core/repo/eligibility.cpp`, `tests/test_repo_engine.cpp`; `git diff --stat -- src/cli src/core/pack src/core/scan src/core/open src/core/manifest src/core/repo/discover.cpp` EMPTY.

```bash
git add src/core/repo/eligibility.hpp src/core/repo/eligibility.cpp tests/test_repo_engine.cpp
git commit -m "repo: run_eligibility gains EligibilityMode (offline: no network, offline_declared + full on the born non-shallow lane only; the unborn/shallow return stays first; a born non-shallow promisor source refuses typed) -- m-1 S-2b-1 rev2 pre-authorized engine input c1a, first in history; W-O1..3"
git rev-parse HEAD > "$EVID/commits.c1a.txt"
```

- [ ] **Step 6 (c1b): the failing tests** — in `tests/test_repo_engine.cpp`, beside the existing `repo discovery preserves prune ordering and records nested boundaries` case (`:815`, KEPT byte-for-byte: its root `.biv/private/.git` is the W-D2 control already in the suite):

```cpp
TEST_CASE("W-D1 / W-D2: repo discovery walks a NESTED .biv directory and keeps the ROOT .biv reserved") {
  TempDir root{"discover-nested-biv"};
  std::filesystem::create_directories(root.path() / "a/.git");
  std::filesystem::create_directories(root.path() / "a/.biv/r/.git");   // W-D1: a nested .biv IS a container
  std::filesystem::create_directories(root.path() / ".biv/r/.git");     // W-D2: the root reserved area is NOT walked
  auto matcher = biv::ignore::Matcher::compile("", false);
  REQUIRE(matcher.has_value());
  auto result = biv::repo::discover(root.path(), *matcher);
  REQUIRE(result.has_value());
  REQUIRE(result->repos.size() == 2);
  CHECK(result->repos[0].relpath == "a");
  CHECK(result->repos[0].kind == biv::repo::RepoKind::repo);
  CHECK_FALSE(result->repos[0].parent_index.has_value());
  CHECK(result->repos[1].relpath == "a/.biv/r");
  CHECK(result->repos[1].kind == biv::repo::RepoKind::nested);
  CHECK(result->repos[1].parent_index == 0);                            // W-D1 binds the parent edge
  // NAMED MUTANTS: the landed any-depth skip ⇒ size 1 (W-D1 red); a skip that forgets the root scope ⇒ size 3 (W-D2 red)
}
TEST_CASE("W-D3 (engine half): a nested .biv DECLARED in .bivignore is pruned by the matcher, not discovered") {
  TempDir root{"discover-nested-biv-ignored"};
  std::filesystem::create_directories(root.path() / "a/.git");
  std::filesystem::create_directories(root.path() / "a/.biv/r/.git");
  auto matcher = biv::ignore::Matcher::compile("a/.biv/\n", false);
  REQUIRE(matcher.has_value());
  auto result = biv::repo::discover(root.path(), *matcher);
  REQUIRE(result.has_value());
  REQUIRE(result->repos.size() == 1);
  CHECK(result->repos[0].relpath == "a");
  // the provenance half (the pack-end prune summary NAMES a/.biv) is Task 7's product-scope leg — discover() returns no printable
  // report (044559); W-D1 is the discriminator between "pruned by the matcher" and "skipped by name"
}
TEST_CASE("unchanged rules: a .git-named directory is a marker and is never walked; a symlinked directory is never descended") {
  TempDir root{"discover-marker-not-container"};
  std::filesystem::create_directories(root.path() / "a/.git/modules/m/.git");   // inside a marker: never a boundary
  std::filesystem::create_directories(root.path() / "elsewhere/r/.git");
  std::filesystem::create_directory_symlink(root.path() / "elsewhere", root.path() / "a/link");  // a symlinked directory: not descended
  auto matcher = biv::ignore::Matcher::compile("", false);
  REQUIRE(matcher.has_value());
  auto result = biv::repo::discover(root.path(), *matcher);
  REQUIRE(result.has_value());
  REQUIRE(result->repos.size() == 2);
  CHECK(result->repos[0].relpath == "a");
  CHECK(result->repos[1].relpath == "elsewhere/r");   // reached through its real path only
}
```

- [ ] **Step 7 (c1b): run to verify failure** — `./build/ci-macos/biv_repo_engine_tests '*W-D1*'` FAILS: `repos.size() == 1` (the landed any-depth skip at `discover.cpp:43` never walks `a/.biv`). The `:815` case still PASSES (the control).
- [ ] **Step 8 (c1b): the implementation** — `discover.cpp`: `walk(...)` gains a trailing `std::size_t depth` parameter (`discover()` passes `0`; the recursion passes `depth + 1`); the name test at `:43` becomes:

```cpp
    const auto name = child.path().filename();
    if (name == ".git") {
      continue;  // a marker, never a container (the marker test below reads it from its parent)
    }
    if (name == ".biv" && depth == 0) {
      continue;  // <root>/.biv is the reserved area (I-R1 root-anchored); a NESTED .biv is walked like any directory (sealed §1.1)
    }
```

  Everything else in `walk` — the not-a-directory / symlink `continue` before it, the matcher after it, the marker test and the recursion — stays byte-for-byte. No other line of `src/core/repo/**` moves in c1b.
- [ ] **Step 9 (c1b): run to verify pass** — `cmake --build --preset ci-macos && ./build/ci-macos/biv_repo_engine_tests` rc 0 (W-D1/W-D2/W-D3 green; `:815` green); `ctest --preset ci-macos -E '^safety-hardening$'` rc 0.
- [ ] **Step 10 (c1b): the veto-9 shape check, then commit** — `git status --porcelain` names exactly `src/core/repo/discover.cpp`, `tests/test_repo_engine.cpp`; `git diff --stat -- src/cli src/core/pack src/core/scan src/core/open src/core/manifest src/core/repo/eligibility.hpp src/core/repo/eligibility.cpp` EMPTY.

```bash
git add src/core/repo/discover.cpp tests/test_repo_engine.cpp
git commit -m "repo: discover walks a nested .biv directory (the only discovery prune is .bivignore, sealed 1.1); <root>/.biv stays reserved; .git-named dirs stay markers; symlinks stay unwalked -- m-1 V-2b-1 rev2 pre-authorized engine input c1b, second in history; W-D1..3"
git rev-parse HEAD > "$EVID/commits.c1b.txt"
```

- [ ] **Step 11 (c1c, fence rev4 `161701` §1 — RELEASED: the binding approve `…-m1-fence-review-r4/DESIGN-REVIEW-implementer-20260916-171135.md` is on the record and master named the pin a1ce40a9 (010159); the pair Planner writes `$RUNNERS/m1-fence-rev4.txt` at Task 0 as `approve=master/relays/intg-2b-wiring-act-m1-fence-review-r4/DESIGN-REVIEW-implementer-20260916-171135.md pin=a1ce40a930b5fd01d905e8295c3a9e581455a1c7 fence_sha256=cf3190ab4a2f99dc339c676c981c406f3d4bd5936649653ae6117815c33d00ea` and the implementer re-hashes the fence carrier at pdc 74810810 against `fence_sha256` — mismatch ⇒ STOP): the failing tests** — in `tests/test_repo_engine.cpp` (the CONTRACT: `restore_invokes_git(entry)` is the engine's GIT-CAPABLE partition — FALSE ⇒ no git UNCONDITIONALLY, through success or a typed error; TRUE ⇒ the restore MAY invoke git once the checks at :459/:468/:477/:483 pass and REQUIRES consent before entering that path — it promises neither a spawn nor a successful apply):

```cpp
// W-G1 — oracle pairing over the four sealed classes on PREPARED VALID fixtures (the row's artifacts present in stage_root; a usable,
// non-colliding target under partial_root; parents creatable): the exported predicate == "restore_entry spawns git for this row"
TEST_CASE("W-G1: restore_invokes_git pairs with restore_entry's own git reach over the four sealed classes (valid fixtures)") {
  // four entries built as the existing restore cases build them: a born OVERLAY row (remote-proven refs), the G unborn-with-refs FULL row
  // (bundle set), the H payload-only row (unborn, no bundle, no eligibility), the N SHALLOW row
  for (auto& [entry, expected] : std::vector<std::pair<biv::repo::RepoEntry, bool>>{{overlay, true}, {g_full, true}, {h_row, false}, {n_shallow, false}}) {
    std::vector<biv::support::SpawnRequest> spawned;
    auto git = fake_network_git(root.path(), /*…*/, [&](const biv::support::SpawnRequest& r) { spawned.push_back(r); });
    CHECK(biv::repo::restore_invokes_git(entry) == expected);
    auto row = biv::repo::restore_entry(git, entry, partial.path(), stage.path());
    CHECK((!spawned.empty()) == expected);   // the predicate IS the engine's behaviour (single source)
  }
}
// W-G1c — COLLISION COUNTER-CONTROL (rev4): a valid born overlay row with non-root relpath r and a PRE-EXISTING partial/r ⇒ predicate
// TRUE, restore_entry returns the typed "materialization target already exists" failure (:477), the trace shows ZERO git — CORRECT, not drift
TEST_CASE("W-G1c: a git-capable row that fails a pre-git check spawns nothing — the predicate is capability, not a spawn promise") { /* as above */ }
// W-G1n — N/H UNCONDITIONAL (rev4): the shallow row and the payload-only row with validate_entry FAILING (a hostile field) ⇒ the typed
// error at :430 and ZERO git — the false arm holds through the error path too
TEST_CASE("W-G1n: the false arm spawns nothing even when validation fails") { /* shallow + hostile field; payload-only + hostile field */ }
// W-G2 — drift mutant: negating one conjunct of the predicate reds W-G1 at exactly ONE class (the reviewer's form: inner !bundle → bundle
// flips only H) — asserted by the implementer's mutant run, recorded in $EVID/legs/W-G2.txt
// W-G3 (narrowed, rev4) — single-source census, grep-derived: restore_entry contains EXACTLY ONE call to restore_invokes_git; that call
// controls EXACTLY the two successful shape-based no-git returns (the successors of :446/:452) and nothing else; every typed failure exit
// (:430, :459, :468, :477, :483, and the unborn+bundle / born branches' typed returns) is PRESERVED byte-for-byte; the predicate's body
// references exactly {shallow, head_state, bundle, eligibility}; no consumer outside src/core/repo re-derives it (grep over src/cli
// src/core/open src/core/pack for the four-field expression: EMPTY — Task 9 runs it). THE COUNT RULE (m-1's erratum 171446, adopted by
// master 010159): the W-G3 acceptance count of `return`s in restore_entry is the GREP'S OUTPUT AT THE CANDIDATE HEAD, recorded into
// $EVID/legs/W-G3-returns.txt beside the sites (at 186adf7d: 27 over :425-589 — 21 typed-error returns, 6 row returns — re-run at this
// seat; c1c's guard adds NO return and removes none); never a number carried from a relay
```

- [ ] **Step 12 (c1c): run to verify failure** — compile error (`restore_invokes_git` undeclared).
- [ ] **Step 13 (c1c): the implementation** — `restore.hpp` (+2/-0): `bool restore_invokes_git(const RepoEntry& entry) noexcept;` with ONE comment line naming N-R4 / G-R1 / H as its grounds; `restore.cpp`: the definition `return !entry.shallow && !(entry.head_state == HeadState::unborn && !entry.bundle && !entry.eligibility);` and `restore_entry`'s `:443-452` become ONE guard `if (!restore_invokes_git(entry)) { if (entry.shallow) { …the existing shallow_pointer return… } …the existing payload_only_unborn return… }` — shallow arm FIRST, the same rows returning at the same point with the same row bytes. NOTHING ELSE in `src/core/repo`; numstat bound: `restore.hpp` +2/-0, `restore.cpp` exactly one hunk at :443-452 plus one new function.
- [ ] **Step 14 (c1c): run to verify pass** — `cmake --build --preset ci-macos && ./build/ci-macos/biv_repo_engine_tests` rc 0 (W-G1 green; every existing restore case green — behaviour-preserving); `ctest --preset ci-macos -E '^safety-hardening$'` rc 0.
- [ ] **Step 15 (c1c): the veto-9 shape check, then commit** — `git status --porcelain` names exactly `src/core/repo/restore.hpp`, `src/core/repo/restore.cpp`, `tests/test_repo_engine.cpp`; `git diff --numstat -- src/core/repo/restore.hpp` reads `2 0`; `git diff -- src/core/repo/restore.cpp | grep -c '^@@'` reads 2 (the guard hunk + the new function); `git diff --stat -- src/cli src/core/pack src/core/scan src/core/open src/core/manifest src/core/repo/eligibility.hpp src/core/repo/eligibility.cpp src/core/repo/discover.cpp` EMPTY.

```bash
git add src/core/repo/restore.hpp src/core/repo/restore.cpp tests/test_repo_engine.cpp
git commit -m "repo: restore_invokes_git(const RepoEntry&) exported -- the engine's git-capable row partition -- and used by restore_entry's single guard over its two shape-based no-git returns (shallow first; behaviour-preserving; every typed failure exit preserved) -- m-1 fence rev4 pre-authorized engine input c1c, third in history; W-G1/W-G1c/W-G1n/W-G2/W-G3"
git rev-parse HEAD > "$EVID/commits.c1c.txt"
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
    // the WHOLE render is byte-golden: the sealed template with each slot holding its EXPECTED encoded spelling — the template's own
    // LF/space bytes are trusted literals, so the raw-byte scan runs over the ENCODED SLOT VALUES only, never over the template
    const auto expected = expected_prompt_d(f, /*encoded slot*/ slot, row.expected);   // helper: the A6-R2 template with the slot text replaced by consent_display's expected output
    INFO(slot); CHECK(out == expected);
    CHECK(no_raw_control_or_format_scalar(biv::cli::consent_display(slot_value(f, slot))));  // decodes UTF-8; fails on raw C0/DEL/C1 or a raw table member IN THE SLOT
  }
}
// a8-2 the same over render_accepted_notice; a8-3 render_pack_refusal_detail (the single returned string IS both carriers — identity by
// construction here; Task 7 asserts error.detail == the stream segment at product scope); a8-4 render_entry_refusal_line with the matrix in
// relpath AND effective. Each case asserts the WHOLE byte-golden render (template + expected slot spellings) and the slot-only raw scan.
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

### Task 3 — c3 (unconditional) + c3h (A9 lock): the CLI — `--offline` / `--network` (m-3 §4 verbatim), the hook truth table, the stderr writers, the flag read, the B-predicate dedup (c3); the two help lines + the golden re-pin (c3h)

**Files:** Modify `src/cli/args.hpp`, `src/cli/args.cpp`, `src/cli/main.cpp`, `tests/test_cli.cpp`; Create `tests/cli_run.hpp` (the run helpers moved from `test_cli.cpp` + `run_cmd_pty_split`).
**Interfaces:** Produces `Command.offline`, `Command.network` (bool — parsed here; CONSUMED by Task 4's c4b as the D3 non-interactive consent per T-NET; until c4b lands the flag reaches nothing, honestly); `biv::pack::PackOptions{bool offline}` and `biv::open::OpenOptions.offline` are DECLARED here (Tasks 4/5 consume them; until then pack/open ignore the field — the flag reaches nothing, honestly); `install_url_divergence_hook(const Command&) -> ConsentRun` in `main.cpp` (a `biv::repo::UrlDivergenceRun` + the notice writer); `emit_entry_refusals(const std::vector<UrlDivergenceEntryRefusal>&, std::ostream& err)` (per-entry lines in row order + ONE guidance line); `run_cmd_pty_split(args, cwd, input) -> RunResult{code, out, err, tty{stdin,stdout,stderr}}` in `tests/cli_run.hpp`.

- [ ] **Step 0: the split (MUST-2B-14)** — c3 (Steps 1–5) carries EVERYTHING of this task EXCEPT the two help lines and the a6·18 golden re-pin, and COMMITS unconditionally under the token (the `help_text` byte string and the golden test are UNTOUCHED in c3 — the existing golden stays green because no help byte moved). c3h (Steps 6–8) inserts the two lines and re-pins the golden ONLY when `[ -s "$RUNNERS/m3-help-order.txt" ]` holds A9's LOCKED `help_text` lines VERBATIM (the exact bytes of the two new lines and their neighbours, plus the lock id and doc sha256 — copied from the lock, never chosen here); it lands after c5 in lock order (T-HELP). No working-tree residue exists between the two.
- [ ] **Step 1: the failing tests** — `tests/test_cli.cpp`: (i) `biv pack --offline <dir>` parses (`Command.offline == true`); `biv open --offline <image>`; `biv open --network <image>`; `biv open --offline --network <image>` → exit 5 UsageError with detail `conflicting-flags`; `biv list --offline` / `biv info --network` → EXACTLY the flagless `biv list` / `biv info` outcome (exit, stream bytes, JSON) — the stub ignores trailing tokens at the pin (T-LIST; a6·14's shape); `biv pack --network <dir>` → `unknown-flag` (open only). (ii) the help golden is NOT touched in c3 — `biv open --help` stays byte-identical to B's golden (a control: the existing a6·18 golden test passes unchanged in c3; the two new lines and the re-pin are c3h's Steps 6–8 ONLY). (iii) `run_cmd_pty_split` discriminator: a child `sh -c 'test -t 0; echo $?; test -t 1; echo $?; test -t 2; echo $?'` → stdout `0\n1\n0\n` (stdin TTY, stdout NOT, stderr TTY), captured stdout via the pipe and stderr via the pty master SEPARATELY (must-be-YES); the existing `run_cmd_pty` on the same child → `0\n0\n0\n` (must-be-NO: the one-pty topology is DIFFERENT). (iv) the hook truth table is NOT yet reachable (no engine path) — its legs are Task 7's; here a unit case over `install_url_divergence_hook` asserts: flag set → `run.hook` non-empty and returns `proceed` on a synthetic `UrlDivergence`; flag absent + `interactive_url_hook_installable()` false (the test process has no TTY under ctest) → `run.hook` EMPTY.
- [ ] **Step 2: run to verify failure** — `./build/ci-macos/biv_tests '[cli-flags]'` FAILS (`--offline` → unknown-flag).
- [ ] **Step 3: the implementation** —

  `args.hpp`: `bool offline{false}; bool network{false};` on `Command`.
  `args.cpp` pack loop: `if (tokens.at(i) == "--offline") { command.offline = true; continue; }` before the `is_flag` check; open loop: `else if (arg == "--offline") { command.offline = true; } else if (arg == "--network") { command.network = true; }`; after the loop: `if (command.offline && command.network) return std::unexpected(usage("conflicting-flags"));`. `help_text(Verb::open)`: UNTOUCHED in c3 (no help byte moves in this commit; the two lines land in c3h at A9's locked position — Step 7). `pack` has no help_text and gains none. `list`/`info` parsing UNTOUCHED (T-LIST).

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
- [ ] **Step 5: commit c3 (unconditional; no help byte)** —

```bash
# c3 SPLIT PROOF (MUST-2B-18 / MUST-2B-22) — graded on the STAGED c3 object, never the unstaged diff; three discriminators, each
# validated on a must-be-YES and a must-be-NO synthetic diff BEFORE it grades the real one (D-5.5(a)); the diff PRODUCER's status is
# checked apart from the predicate's (rc 0/1 = a verdict; anything else = STOP). No attribute diff driver at B (checked), so the
# synthetic controls and the staged gate share git's default funcname rule.
set -o pipefail
git add src/cli/args.hpp src/cli/args.cpp src/cli/main.cpp tests/test_cli.cpp tests/cli_run.hpp src/core/pack/pack.hpp src/core/open/open.hpp || { echo 'STOP: git add failed (a c3 file is missing); nothing is staged, so the gate below would pass vacuously'; exit 1; }
for f in src/cli/args.cpp tests/test_cli.cpp; do [ "$(git check-attr diff -- "$f" | awk '{print $NF}')" = unspecified ] || { echo "STOP: a diff driver is set on $f; the funcname discriminator is unvalidated"; exit 1; }; done
T=$(mktemp -d)
git show HEAD:src/cli/args.cpp > "$T/a.cpp" || { echo 'STOP: control producer (args.cpp)'; exit 1; }
git show HEAD:tests/test_cli.cpp > "$T/t.cpp" || { echo 'STOP: control producer (test_cli.cpp)'; exit 1; }
python3 - "$T" <<'PY'
import sys,pathlib; T=pathlib.Path(sys.argv[1])
def ins(src, after, line):
    a=src.split('\n'); i=next(k for k,l in enumerate(a) if after in l); return '\n'.join(a[:i+1]+[line]+a[i+1:])
a=(T/'a.cpp').read_text(); t=(T/'t.cpp').read_text()
(T/'yes.cpp').write_text(ins(a, '"usage: biv open <image> [options]\\n"', '        "  --control\\n"'))     # inside help_text(): must FIRE
(T/'no.cpp').write_text(ins(a, 'command.verb = Verb::open;', '    (void)0;  // control'))                    # inside parse_args(): must NOT fire
(T/'tyes.cpp').write_text(ins(t, '"  --abort-on-collision\\n"', '        "  --control\\n"'))                # inside the open-help golden case: must FIRE
PY
count() { # $1 $2 = the two files of a --no-index diff (or "cached" + path); $3 = the regex; prints the match count; STOPs on a producer/grep fault
  if [ "$1" = cached ]; then git diff --cached -U0 -- "$2" > "$T/d.txt"; else git diff --no-index -U0 -- "$1" "$2" > "$T/d.txt"; fi; r=$?
  [ "$r" -le 1 ] || { echo "STOP: diff producer rc=$r ($1 $2)"; exit 1; }
  c=$(grep -c -E -- "$3" "$T/d.txt"); g=$?; [ "$g" -le 1 ] || { echo "STOP: grep rc=$g"; exit 1; }; echo "$c"; }
H='^@@ .* @@ .*help_text\('                                                              # a staged hunk whose enclosing function is help_text()
G='^@@ .* @@ TEST_CASE\("Task 4 CLI help documents the strict agent binary pin syntax"'  # a staged hunk inside the open-help golden case
R='^[-+][[:space:]]*"(usage: biv |  --[a-z-]+)'                                          # an added/removed usage or help-row string literal
y1=$(count "$T/a.cpp" "$T/yes.cpp" "$H");  [ "$y1" -ge 1 ] || { echo 'STOP: must-be-YES failed: the help_text discriminator cannot see a help_text hunk'; exit 1; }
n1=$(count "$T/a.cpp" "$T/no.cpp"  "$H");  [ "$n1" -eq 0 ] || { echo 'STOP: must-be-NO failed: the help_text discriminator fires inside parse_args'; exit 1; }
y2=$(count "$T/t.cpp" "$T/tyes.cpp" "$G"); [ "$y2" -ge 1 ] || { echo 'STOP: must-be-YES failed: the golden-case discriminator cannot see a golden hunk'; exit 1; }
y3=$(count "$T/t.cpp" "$T/tyes.cpp" "$R"); [ "$y3" -ge 1 ] || { echo 'STOP: must-be-YES failed: the help-row literal discriminator cannot see a help row'; exit 1; }
n3=$(count "$T/a.cpp" "$T/no.cpp"  "$R");  [ "$n3" -eq 0 ] || { echo 'STOP: must-be-NO failed: the help-row literal discriminator fires on parse code'; exit 1; }
a1=$(count cached src/cli/args.cpp   "$H"); [ "$a1" -eq 0 ] || { echo 'STOP: a help_text hunk is STAGED in c3'; exit 1; }
t1=$(count cached tests/test_cli.cpp "$G"); [ "$t1" -eq 0 ] || { echo 'STOP: a hunk inside the open-help golden case is STAGED in c3 (c3 test cases go at END of file, never directly after the golden case: an insertion there inherits its funcname and fires here — by design)'; exit 1; }
a2=$(count cached src/cli/args.cpp   "$R"); t2=$(count cached tests/test_cli.cpp "$R"); [ "$a2" -eq 0 ] && [ "$t2" -eq 0 ] || { echo 'STOP: a usage/help-row literal is STAGED in c3'; exit 1; }
printf 'controls yes_help=%s no_help=%s yes_golden=%s yes_row=%s no_row=%s\nstaged help_text_hunks=%s golden_hunks=%s help_row_lines=%s/%s\n' "$y1" "$n1" "$y2" "$y3" "$n3" "$a1" "$t1" "$a2" "$t2" > "$EVID/code/c3-split-proof.txt"
rm -rf "$T"
git commit -m "cli: --offline (pack, open) and --network (open) per m-3 130818 s4; conflicting-flags; url-divergence hook truth table (flag | stdin&&stderr TTY | none); stderr writers for notice, per-entry refusals and the one guidance line; PROMPT B/A TTY predicate deduped onto interactive_url_hook_installable; split-stream PTY helper (help lines + golden: c3h at A9's lock)"
git rev-parse HEAD > "$EVID/commits.c3.txt"
```

- [ ] **Step 6 (c3h, AFTER the T-HELP gate holds; lands after c5 in lock order): the failing test** — `tests/test_cli.cpp`: the a6·18 golden becomes the eleven-line order A9's lock states (usage, --dest, --consent, --accept-url-divergence, --offline, --network, --agent-bin, --rename, --abort-on-collision, --verify, --json at rev2 — copied from `$RUNNERS/m3-help-order.txt`, never typed here) with a split-adjacency mutant (`--offline` before `--accept-url-divergence` ⇒ RED).
- [ ] **Step 7 (c3h): the implementation** — `args.cpp` `help_text(Verb::open)`: EXACTLY the two lines from the gate file inserted at EXACTLY the position it states; nothing else moves.
- [ ] **Step 8 (c3h): run to verify pass, then commit** — `./build/ci-macos/biv_tests '[cli]'` rc 0; `git diff --stat` names only `src/cli/args.cpp` and `tests/test_cli.cpp`.

```bash
git add src/cli/args.cpp tests/test_cli.cpp
git commit -m "cli: the two help lines at A9's locked position (after --accept-url-divergence, before --agent-bin); a6.18 golden re-pinned -- m-3 addendum 9 <lock id> @ <doc sha256>"
git rev-parse HEAD > "$EVID/commits.c3h.txt"
```

### Task 4 — c4a (sealed) + c4b (A10 lock): the `repos/` member class, `restore_entry` per row in §2.2 order, the in-memory rows, `--offline` D4 listing (c4a); `result.repos` + schema, the D2/D3 network-consent surface, the durable offline artifact + `bundle_path`/`reconstruct` (c4b) (A2 D4; m-3 §4 OPEN; restore-apply §1/§2.2; V-2b-7/V-2b-8; A10 rev6 17fda846 at its lock)

**Files:** Modify `src/core/open/open.hpp`, `src/core/open/open.cpp`, `src/core/report/envelope.hpp`, `src/core/report/envelope.cpp`, `src/cli/main.cpp`, `src/cli/url_consent.hpp`, `src/cli/url_consent.cpp` (the A9.4 offline renderers), `tests/test_cli.cpp`, `tests/test_envelope.cpp`, `tests/test_open.cpp` (the TENTH c4a path — rev13, STOP 021304: ONLY the s3 Task-4 source-hash oracle at `:343` `Task 4 open occupancy and destination contracts stay bounded` is re-oracled, per Step 3b; no other case in that file moves); ONLY under T-JSON's word also `schemas/biv-json-envelope.v1.schema.json` + `harness/selftest/test_envelope.py` (the envelope-schema blob pin recomputed by `git hash-object`, same commit). — PLUS (rev17, R-4.62 arm (a)) `tests/test_probe.cpp` ONLY by m-3's approved mailbox patch applied VERBATIM as ONE commit with m-3's authorship in Step 3c (m-3's bytes, not a c4a path: Step 5's write-set gate still expects exactly the ten paths in `git diff HEAD`, because the patch is COMMITTED before them).
**Interfaces:** Produces `OpenOptions.offline`; `struct RepoOutcomeRow { std::string id; std::string relpath; std::string outcome; /* restored | shallow-pointer | payload-only-unborn | failed | offline-pointer */ std::optional<std::string> sha; std::optional<std::string> branch; std::string capture_mode; std::vector<std::string> remotes; std::optional<std::string> bundle_path; /* c4b: dest-relative posix `.biv/repos/<id>/repo.bundle`, PRESENT iff artifact-present (full-capture row) */ std::optional<std::string> reconstruct; /* c4b: T-STAGE's ONE single-quoted POSIX-sh idiom for the stored HEAD state (born / unborn / detached), byte-equal to the printed command line; PRESENT iff bundle_path is present AND every operand is copy-safe; ABSENT (the fallback line printed instead) otherwise; overlay rows carry neither field; emitted under T-JSON's word beside bundle_path in the schema row */ std::vector<biv::repo::LocalRefRestoreRow> local_refs; std::vector<std::string> advisories; std::optional<std::vector<std::string>> shallow_boundary; };` and `std::vector<RepoOutcomeRow> OpenReport::repos` (an IN-MEMORY report field; its JSON emission is T-JSON's); `OpenReport.url_divergence_refusals` FILLED; `biv::report::machine_text`. Consumes `biv::repo::restore_entry`, `biv::repo::Git::resolve`, `biv::repo::engine_error_kind` (types.hpp:92-110 — the TYPED accessor; the wire string is `url-divergence-refused`, never compared by hand).

- [ ] **Step 0: the A10 gate (HOLD, not defer)** — c4a (Steps 1–5) is sealed text and proceeds under the token. c4b (Steps 6–9: the `result.repos` emission + schema row, the D2/D3 surface, the durable offline artifact + bundle line + the two row fields) writes NO byte until `[ -s "$RUNNERS/m3-addendum-10-lock.txt" ]` holds `lock_id=m3-addendum-10-20260916 doc_sha256=<hex> relay=<path>` and the implementer's re-hash of the addendum at the named pdc path equals `doc_sha256` (mismatch ⇒ STOP); the c4b bytes below are planned from A10 rev6 (`17fda846d320b09bae57ed088cb722f1d92392583dd66785900fd312f32823fd`, the revision this plan transcribes) and are re-verified line-by-line against the LOCKED pin before they are written — a locked byte differing from rev6's is a new plan revision (RULE).
- [ ] **Step 1: the failing tests (hand-built images, `provenance=hand-built, interim`)** — a test helper `build_repo_image(dir) -> image path` that drives the ENGINE directly (`repo::discover` → `classify` → `run_eligibility(…, network)` → `capture` into a scratch dir) then assembles the archive with `manifest::serialize` + the container writer exactly as `pack.cpp` orders members (manifest, checksums, payload, repos, agents) — a fixture builder, replaced by `biv pack` itself once Task 5 lands (Task 7 re-executes every case here against product-packed images). Cases in `tests/test_cli.cpp`:
  - `a real bundle restores` (MUST-2B-02, corrected for ARM-1 REALITY): a CLEAN source repo with one committed file, one IGNORED file (`.gitignore`d — the penumbra; NOT untracked, which is the dirty fence) and one local branch → engine-built image (`repos/<id>/repo.bundle` + `local-refs.bundle` — the ONLY artifacts capture.cpp writes at the pin) → open → `git status --porcelain=v2` of the restored repo is EMPTY like the source's, HEAD/branch equal, the ignored file byte-equal, the local branch recreated; each `repos/<id>/…` member was staged at `<stage>/repos/<id>/…` (the ONLINE arm of Task 4's `stage` routing; the FULL manifest-relative path — `restore.cpp:138-145` resolves `stage_root / <artifact relpath>` and containment-checks it) and its checksum verified; the stage dir is gone after open. The staged/unstaged-patch round trip is T-ARM (i), REGISTERED — no patch artifact exists at 2b.
  - `typed refusal mapping` (MUST-2B-01): a restore-site divergence — NOT a temp-HOME `.gitconfig` insteadOf (impossible at B: restore sets `GIT_CONFIG_GLOBAL=/dev/null`, an engine isolation byte no fence lets 2b touch; rev13 AFFIRMS the implementer's 021304 substitution) but a TEST-LOCAL request-trace git shim on `PATH` that answers ONLY `remote get-url` with the diverged effective URL and forwards every other git invocation to the real git verbatim, recording argv (the trace is the fixture's own receipt; no product byte; the product-scope form is Task 7 M leg (h), F-DIVERGE's default local config) → ONE `UrlDivergenceEntryRefused` row + the run CONTINUES to the next entry (exit 2); the mapping goes through `biv::repo::engine_error_kind(error) == EngineErrorKind::url_divergence_refused`; NAMED MUTANT: a string compare of `"url_divergence_refused"` (underscore spelling) takes the whole-operation arm — the test asserts the ROW arm and exit 2, so the mutant reds.
  - `repos/ member class admitted iff named`: an image whose one repos[] row names `repos/<id>/repo.bundle` → open succeeds AND the restored repo is a real git repository at its relpath (`git -C <dest>/<relpath> rev-parse HEAD` == the recorded sha); the SAME image with an extra `repos/<id>/stray.bin` member listed in checksums → exit 3 `UnmanifestedMember` naming it (V-2b-7; ADDENDUM-I discipline); an image whose row names a member ABSENT from the archive → exit 3 `IntegrityFailurePreApply` detail `missing-repo-artifact` (mirrors `missing-agent-member`).
  - `restore_entry once per row, parents before children` (HAND-BUILT ONLY — T-ARM (iii)): a SYNTHETIC manifest with a parent row and a child row (`parent_id` set) whose artifacts are two independently engine-captured clean repos placed at `repos/<id>/…` (the engine's classify would FENCE a real nested tree at 2b, so no product-packed image can carry two rows — registered) → after open, both are git repos at their relpaths under dest; the request-trace shim log (BLOCK `git-shim.sh` on PATH — see §Instruments) shows the parent's clone before the child's; the in-memory rows are two, outcomes `restored`, in that order. Labelled `provenance=hand-built, registered-T-ARM` in its receipt; NOT re-executed in Task 7.
  - `nothing before apply touches disk`: a divergence refusal at the first entry leaves the dest ABSENT? — NO: A6-R4/a6·12 say the clean entries COMPLETE and the refused ones are rows (exit 2); so: two refused entries + one clean → dest exists, the clean repo restored, two `UrlDivergenceEntryRefused` rows in ENCOUNTER ORDER, exit 2, `error` null (a6·12's shape; Task 7 adds the golden text and stream-order assertions at product scope).
  - `--offline` (c4a; with the stage-path DISCRIMINATOR): a regular FILE is pre-created at `<containing_dir(dest)>/<dest.filename()>.bvpk-open.stage` before the run → `biv open --offline` exits 0, the listing renders, and that file is byte-unchanged afterwards (the offline arm never touches the stage path); the CONTROL: the same pre-created file with an ONLINE open of the same image → `OpenPartialPresent` naming that path (proves it is the very path the online arm stages into). NAMED MUTANT: routing `repos/` members into the stage dir regardless of `stage` → the offline run fails on the pre-created file ⇒ RED. At c4a the offline arm DRAINS + verifies every `repos/` member (materializes nothing); at c4b (Step 6) the full-capture row's `repo.bundle` is placed DURABLY per T-STAGE and this case gains: `<dest>/.biv/repos/<id>/repo.bundle` exists with sha256 == checksums.json's entry for `repos/<id>/repo.bundle`, an overlay row's members are absent under `<dest>/.biv/`, the stage path STILL untouched, zero git. Also: the same image → ZERO git spawns in the shim log for the whole open (m-1's guarantee; m-3 V-OFF (1)); payload + sessions laid down as today; the in-memory rows: `offline-pointer` ONLY for rows that would otherwise clone or fetch (born, non-shallow, with a bundle or an eligibility cell); a SHALLOW row stays `shallow-pointer` and an unborn payload-only row stays `payload-only-unborn` — these structural rows are IDENTICAL field-by-field with and without `--offline` (N's parity oracle; the engine returns them without git either way, restore.cpp:444-452) — three branches stated, no two incompatible outcomes claimed; exit 0; the A9.4 listing on stderr after the apply summary for the offline-pointer rows, byte-exact modulo paths (the bundle line + `bundle_path`/`reconstruct` are c4b's — Step 6 witnesses them).
  - `machine carriers valid UTF-8` (MUST-2B-03): a refusal row whose `relpath`/`repo_id` carries a lone `0x9b` → the JSON envelope is VALID UTF-8 with U+FFFD at that coordinate (`machine_text`), the in-memory refusal row still holds the raw byte; the same for `error.path` on a pack refusal and for an accepted advisory entry's `repo`. NAMED MUTANT: a raw `0x9b` reaching the JSON (invalid UTF-8 output) ⇒ RED; a display escape (`\u009b`, `\u{…}`) inside a machine field ⇒ RED.
  - `zero state`: an image with no repos[] → no repos rows in memory; no listing; exit as today.
- [ ] **Step 2: run to verify failure** — `./build/ci-macos/biv_tests '[open-repos]'` FAILS (`UnmanifestedMember` for every `repos/` member today).
- [ ] **Step 3: the implementation** —
  `read_archive_plan` (`open.cpp:283-296`): admit `repos/` members: build `std::set<std::string> named_artifacts` from every `plan.manifest.repos[i]` row's `bundle`, `local_refs_bundle`, `capture.staged_patch`, `capture.worktree_patch` (generic strings; only those four kinds — manifest-format §3 under `repos/<id>/`); a member starting with `repos/` is admitted iff `named_artifacts.contains(path)` (checksums membership is already checked above) → `plan.repo_artifacts.push_back(PlannedMember{…})`; else `UnmanifestedMember`. After the loop: every `named_artifacts` entry not `seen` → `IntegrityFailurePreApply` detail `missing-repo-artifact`.
  `apply_archive(image, plan, partial_dir, dirs, verify, stage)` — a NEW trailing parameter `const std::optional<std::filesystem::path>& stage`: a third branch for `repos/` members (file members only; `MemberPathUnsafe` otherwise), ROUTED by `stage`: (ONLINE — `stage` has a value) extracted into `*stage / <the FULL member path, e.g. repos/<id>/repo.bundle>` — the manifest-relative namespace preserved so `restore_entry(git, entry, partial_dir, *stage)` resolves `stage_root / entry.bundle` exactly (restore.cpp:138-145; MUST-2B-02) — with checksum verification exactly like payload; (OFFLINE at c4a — `stage` is `std::nullopt`) DRAINED and checksum-verified exactly like `agents/` members (`drain_member_midapply` + the extent digest) and NEVER materialized — no stage directory exists in this arm; both arms count `repo_artifact_count` and the member-count check includes them. At c4b (Step 6, A10 lock) the OFFLINE arm gains T-STAGE's durable placement: a member that IS a full-capture row's `bundle` (`repos/<id>/repo.bundle`, the row's `capture_mode == full`) is written to `partial_dir / ".biv" / "repos" / <id> / "repo.bundle"` with the same checksum verification (integrity-failure(member) on mismatch, §3), carried by the rename; every other `repos/` member (overlay rows' `local-refs.bundle` — R-4.58) stays drained. `git bundle verify` is never run.
  `execute_archive`: `const std::optional<std::filesystem::path> stage = (options.offline || plan.manifest.repos.empty()) ? std::nullopt : std::optional{containing_dir(dest) / (dest.filename() + ".bvpk-open.stage")}`; ONLY when `stage` has a value: present at start → `OpenPartialPresent` naming it (the existing kind; the same repair path as the partial dir), created before apply, removed after the rename and on every error path (the cleanup lambda); under `--offline` the stage path is NEVER stat'ed, created, written or removed. `apply_archive(image, plan, partial_dir, dirs, verify, stage)`; after it and the mtime pass, iff `stage` has a value: `auto git = biv::repo::Git::resolve(getenv)` (`getenv` = the process environment through `support::Getenv`, as the engine tests build it; failure → the engine's typed error surfaces as today); order the rows PARENTS BEFORE CHILDREN (stable topological order by `parent_id`, manifest order within a level); for each row: `restore_entry(git, entry, partial_dir, *stage)`; on a value → `RepoOutcomeRow` from `RepoRestoreRow` (outcome word by the D5.2 enum: `restored`, `shallow-pointer`, `payload-only-unborn`, `failed`); on an error for which `biv::repo::engine_error_kind(err) == biv::repo::EngineErrorKind::url_divergence_refused` (the TYPED accessor, types.hpp:92-110 — MUST-2B-01) → push `UrlDivergenceEntryRefusal{entry.id, entry.relpath, facts.requested, facts.effective, facts.op}` and a `RepoOutcomeRow{outcome = "failed"}` and CONTINUE (V-2b-8(iii): the entry's typed restore failure, never downgraded); any other error → whole-operation failure with the `partial_dir` fact exactly as payload errors today. Offline (`options.offline`) — and a DECLINED D3 run (c4b), the SAME code path — the EXACT partition of m-1's fence rev3 §2 (A10 rev6 §A10.2 carries it verbatim), per row in manifest order on the ENGINE'S predicate, READ never recomputed: `restore_invokes_git(entry) == false` ⇒ CALL `restore_entry(git, entry, partial_dir, <no stage>)` — zero git by construction (the request trace proves it; the sealed rows: `shallow-pointer` per N-R4, IDENTICAL with and without the flag; `payload-only-unborn` per H; `sha` exactly as the engine returns it) — `git` here is `Git::resolve(getenv)`'s handle (a binary lookup that spawns nothing; if it cannot resolve while only predicate-false rows exist, that is an S-2b-5-class STOP to m-1, not a lane workaround); `restore_invokes_git(entry) == true` ⇒ do NOT call `restore_entry`; emit the ADDENDUM-D `offline-pointer` row with `relpath`/`branch`/`sha`/`remotes[]` from the manifest (`sha` = the 40-hex or the sealed literal `(no commits)` iff HEAD is unborn — never null on an offline-pointer row, A10.1); ARTIFACT-PRESENT = `entry.bundle` set ∧ that member in `checksums.json` (a fact the engine wrote at capture.cpp:307; no engine byte) decides the durable placement (c4b) and `bundle_path`; at c4a NO `repos/` member is materialized in this arm; at c4b the full-capture rows' `bundle_path` (dest-relative posix `.biv/repos/<id>/repo.bundle`) and `reconstruct` (T-STAGE's ONE idiom per stored HEAD state — born / unborn / detached — every operand single-quoted on the raw bytes, PRESENT iff every operand is copy-safe, else absent with the fallback line) are set on the in-memory row for every artifact-present row; overlay rows carry neither. Then `fsync_tree` and the rename to `dest`. D3 (c4b, T-NET): in `main.cpp`'s open flow — AFTER the existing collision and PROMPT B handling (A7-R4: B completes before any D) and BEFORE the call that executes the archive (`main.cpp:354` at B; no git subprocess exists before it) — iff `!options.offline` and ∃ a manifest row with `biv::repo::restore_invokes_git(entry) == true` (the engine's GIT-CAPABLE partition, c1c, READ — A10 rev6 §A10.2 TRIGGER; the CLI never recomputes it; TRUE means the row's restore MAY invoke git and therefore REQUIRES consent first — not that it will spawn or succeed): `render_network_consent(rows)` + the decision per T-NET (interactive: prompt; non-interactive: the flag); a DECLINE makes the run `biv open --offline` for its repo half — the partition above, `stage = std::nullopt`, zero git, exit 0, A9.4's listing for the offline-pointer rows (A10 rev6 DECLINED).
  `envelope.cpp`: `machine_text()` (= `support::sanitize_utf8`) applied at EVERY emission of a bound value the A8 census names — `write_error`'s `path` and every `facts` value; the four fields of each `url-divergence-accepted` entry; the five fields of each `url_divergence_refusals` row; every string field of each `result.repos` row (c4b) — valid UTF-8 byte-exact, malformed visibly replaced, never a display escape (MUST-2B-03; A8-R1 machine census + malformed arm); the in-memory values (memo keys, decisions, refusal rows) stay RAW. The `result.repos` emission (T-JSON's row set VERBATIM; present iff ≥ 1 row processed, never `[]`) and `schemas/biv-json-envelope.v1.schema.json`'s `result.properties.repos` (the row shape, `minItems: 1`) land in c4b in the SAME commit with `harness/selftest/test_envelope.py`'s envelope-schema blob pin recomputed by `git hash-object`; `result.manifest.repos` stays the landed EMPTY array (I2B-09 option (b), registered).
  `main.cpp` (open, `--offline`, human mode, iff `!report->repos.empty()`), AFTER the apply summary, on `std::cerr`, the A9.4 bytes VERBATIM (rendered by renderers added to `url_consent.cpp` — `render_offline_header()`, `render_offline_row(relpath, branch, sha, remotes)`; `render_offline_bundle_line(relpath, reconstruct)` at c4b with `<reconstruct>` = T-STAGE's selected form; `render_network_consent(rows)` (c4b; the A10.2 NOTICE bytes + the interactive PROMPT line; the SAME text on the pty and on a redirected stderr) — every bound value through `consent_display`; main.cpp only sequences them):

```text
open --offline: repositories were not restored (no git, no network). Stored remote URLs below are informational — recorded at pack, not vetted or complete. Cloning them is git-clone-grade trust: git may contact those URLs and additional URLs from repo metadata (.gitmodules, nested submodules, host git config) that Bivpak does not see or police. Clone only what you trust.
<relpath> · <branch> · <commit> · <url>[, <url>…]
<relpath>: <reconstruct>   (partial/manual reconstruction — not a full restore)
```

  one repo line per offline-pointer row in manifest order (`<branch>` = `(detached)` when none; `<commit>` = the 40-hex sha, `(no commits)` for an unborn HEAD; no stored URL → `(no stored remote)`); the bundle line for full-capture rows is c4b's (Step 6), one per full row AFTER all listing rows; every value through `consent_display` (A8-R1 policy; the machine carrier through `machine_text`); exit 0 (an offline open is a success). `--offline` and `--network` alter NOTHING about PROMPT D (V-OFF (3); V-A10-3); `--network` is consumed ONLY by D3 (c4b, T-NET).
- [ ] **Step 3b (rev13/rev14, STOP 021304 — the s3 Task-4 source-hash oracle): re-oracle `tests/test_open.cpp:343` `Task 4 open occupancy and destination contracts stay bounded` IN THE SAME COMMIT, TWO hunks in that file and nothing else** — the case (origin `2537eb6`, s3 Step 3 Task 4) hashes two whole source slices of `open.cpp` (`plan_open` … `execute_open`; `const auto partial_dir =` … `return OpenReport{`) and pins them by sha256 (`940128ad…`, `eab078f6…`). A sha over a region the locked plan itself changes is a FREEZE, not a contract: re-pinning it in the commit that moves the bytes proves nothing, and c4b / c6b would re-pin it twice more. The CONTRACT the case names — destination handling bounded, occupancy checked before anything is written, every writer aimed at the partial directory, fsync before the rename that publishes it — is kept and asserted DIRECTLY, WITH ORDER (MUST-2B-28). HUNK 1 (the case): the two sha `CHECK`s are deleted; kept verbatim: the two `symlink_status` existence `find`s and the `plan_open` slice's three controls (`options.dest.value_or(default_dest_for(options.image)).lexically_normal()` present; `absolute` absent; `weakly_canonical` absent) with the slice's begin anchor unchanged (`expected<OpenPlanHandle> plan_open`) and its end anchor unchanged (`expected<OpenReport> execute_open`); the write path becomes a slice whose begin anchor is unchanged (`const auto partial_dir =`) and whose end anchor is the FIRST `"\n}\n"` after it (the enclosing function's column-0 close — stable across c4a / c4b / c6b); inside that slice the SIX exact call forms are located with `find`, each `REQUIRE`d present and `CHECK`ed to occur EXACTLY ONCE, and their positions `CHECK`ed STRICTLY INCREASING in this order: `std::filesystem::exists(partial_dir, ec)` < `std::filesystem::create_directories(partial_dir, ec)` < `apply_archive(image, plan, partial_dir, dirs, verify, stage)` < `restore_repos(plan, partial_dir, stage, report)` < `fsync_tree(partial_dir)` < `std::filesystem::rename(partial_dir, dest, ec)` (the retained candidate's load-bearing sequence, read at 13ec732+9: positions 113 < 1125 < 2072 < 2871 < 3018 < 3273, each once); plus `ErrKind::OpenPartialPresent` present, `absolute` absent, `weakly_canonical` absent, and `".bvpk-open.partial"` present exactly once in the slice (T-PARTIAL's one site). If c4b or c6b later changes one of the six forms, THAT commit updates the exact form in the same commit (`tests/test_open.cpp` joins its staged set) — the order is the contract, the spelling follows the sealed bytes. HUNK 2 (MUST-2B-27): the anonymous-namespace helper `sha256_hex(std::string_view)` at `tests/test_open.cpp:54-58` has no caller once the two `CHECK`s go and the suite compiles `-Wall -Wextra -Werror` (`-Wunused-function` would red the build) — the helper is DELETED (five lines, `std::string sha256_hex(std::string_view text) {` through its `}`), never kept alive by a fake call and never re-pinned; `biv::support::Sha256` is not otherwise used in the file, and an unused include does not warn. Every other test case in the file is byte-identical: `git diff --numstat -- tests/test_open.cpp` reads one row; `git diff -U0 -- tests/test_open.cpp | grep -c '^@@'` == 2 (recorded in `$EVID/code/c4a-test-open-hunks.txt`, producer rc checked). NAMED MUTANTS (each applied to `open.cpp` in a scratch copy of the tree, the case run, then reverted — receipts `$EVID/code/c4a-oracle-mutant-<n>.log`): (i) `std::filesystem::absolute(` inserted inside `plan_open` ⇒ RED; (ii) `.lexically_normal()` removed from the dest expression ⇒ RED; (iii) `weakly_canonical` inserted inside the write slice ⇒ RED; (iv) the `std::filesystem::exists(partial_dir, ec)` occupancy check removed ⇒ RED; (v) the rename replaced by a copy ⇒ RED; (vi) `apply_archive(image, plan, partial_dir, dirs, verify, stage)` retargeted to `dest` ⇒ RED (the exact form is absent); (vii) `restore_repos(plan, partial_dir, stage, report)` retargeted to `dest` ⇒ RED; (viii) the `rename` moved BEFORE `fsync_tree` ⇒ RED (order); (ix) the occupancy check moved AFTER `create_directories` ⇒ RED (order). RED-before: the case is red at the candidate bytes on the OLD oracle (`c4a-full-ambient.log`: `write_end == npos`) — that log is the Step 2 receipt for this step. The pair verified the new oracle READ-ONLY against the retained candidate at 13ec732+9: both slices resolve, every asserted form is present exactly once and in order, `absolute` / `weakly_canonical` are absent from both slices, the suffix literal occurs once, and the old `return OpenReport{` marker is gone. CENSUS (MUST-2B-30 — the named command's FULL output at B, `git grep -n '"src"' 186adf7d -- tests`, rc 0, nine lines): `tests/test_adapter_claude_install.cpp:1787` and `tests/test_adapter_codex_install.cpp:1807` (adapter install sources — untouched by 2b), `tests/test_cli.cpp:1382` (args.cpp) and `:1605` (main.cpp) (order/presence checks, no sha — c3 passed them; c3h and c5 re-run them), `tests/test_envelope.cpp:846` (a `source_path = "src"` value, not a reader), `tests/test_open.cpp:345` (this case), `tests/test_probe.cpp:272`, `:984`, `:991` (probe.hpp/probe.cpp — untouched by 2b). Targeted, producer-rc-checked: `git grep -n 'open.cpp' -- tests` → ONE line, `tests/test_open.cpp:346` (no second reader of `open.cpp`); `git grep -n 'sha256_hex(' -- tests` → `test_open.cpp:54/364/377` (this helper + the two pins) and `test_tar_writer.cpp` (its OWN byte-span helper over tar bytes, not product source) plus `extent_sha256_hex()` reader calls in `test_pack.cpp:105` / `test_tar_reader.cpp:143` — so the two `test_open.cpp` calls are the suite's only sha pins over product source. T-ORACLE (master 032924, the objection window — m-3 ANSWERED in the window's lineage: `intg-2b-wiring-act/DESIGN-planner-20260919-033307.md` NO OBJECTION with conditions (a)–(f), all inside this shape, PINNED here at sha256 `20c9f24d0652285298ca88bd67d66d3cd861d1ebc2093b6606d76a1d4a9554e7`; m-1's `033215` NO OBJECTION was answered from CC and is NOT the governed word — MUST-2B-31: TO acts, CC informs, and a later carry cannot retroactively address m-1): c4a's COMMIT (Step 5) waits on this revision's exact-hash approve AND the EVIDENCE GATE below (rev16, MUST-2B-31/33/34), which reads FIVE pdc carriers and derives every word from the relay bytes, none by existence: (1) the window 032924, pinned by sha256 `a199b971…`; (2) m-3's word, pinned by sha256 (a committed-but-changed file with every textual predicate preserved STOPs on the pin), with its exact `FROM: m-3.planner` / `TO: master.master-planner` / `PHASE: DESIGN` / `AUTHORITY: design-only` lines, `IN_REPLY_TO:` exactly the window, the case path, and a SUBJECT saying NO OBJECTION and not objecting; (3) master's ADDRESSED REQUEST to m-1 — a PLAN relay `FROM: master.master-planner` / `TO: m-1.planner` / `PHASE: PLAN` / `AUTHORITY: plan-only` naming the window path, the case path and `T-ORACLE`; (4) m-1's ADDRESSED REPLY — its DESIGN relay to master whose `IN_REPLY_TO:` is exactly that request (a reply to the window, or the CC-answered 033215, STOPs on lineage), on the case, SUBJECT NO OBJECTION and not objecting; (5) master's CARRY TO the pair — exact `FROM: master.master-planner` / `TO: intg.pair-planner` / `PHASE: PLAN` / `AUTHORITY: plan-only` lines and FIVE exact, unique fields: `T_ORACLE_VERDICT: cleared` (exactly one `T_ORACLE_VERDICT:` line; any other value — NOT CLEARED, blocked, objection, held — STOPs), `T_ORACLE_PLAN_SHA256: <the plan it clears>` (== the live plan re-hashed from the primary checkout), `T_ORACLE_M3: <path> sha256=<the pinned m-3 digest>`, `T_ORACLE_M1: <path> sha256=<the reply's digest>` (the carry affirms m-1's bytes; the gate re-hashes the file and compares), `T_ORACLE_M1_REQUEST: <path> sha256=<the request's digest>`; every path pdc-relative, `..`-free, NOT a symlink, a regular file beneath `master/relays` by real directory, tracked and unmodified in pdc; the five relays distinct; the receipt records six digests. The pair Planner writes `$RUNNERS/t-oracle.txt` with FOUR locators only (`m1_request=`, `m1_relay=`, `carry_relay=`, `plan_sha256=`); the window and m-3's word are constants of this plan; no summary word exists anywhere to trust. EXECUTED by the pair in a scratch clone of pdc with a throwaway bivpak worktree: the REAL pinned m-3 word + a synthetic addressed m-1 request/reply and carry committed in the clone ⇒ pass (six digests); nineteen controls STOP before any receipt, each on its own predicate — carry NOT CLEARED / blocked / an objection without the phrase (`carry-verdict-not-cleared`), verdict absent (`count-0`), duplicate verdict (`count-2`), carry naming another plan (`carry-plan-sha`), carry with a wrong m-1 digest (`carry-m1-object`), m-3 committed-but-changed with every predicate preserved (`m3-bytes`), m-1 replying to the window instead of the request (`m1-lineage`), the real CC-answered 033215 offered as the reply (`m1-lineage`), a request not addressed TO m-1 (`m1req-to`), a reply whose SUBJECT keeps the freeze (`m1-subject-not-no-objection`), a `..` path, a symlink, an untracked copy, a modified reply, a reply committed-but-changed after the carry (`carry-m1-object`), a request not naming the case (`m1req-not-this-case`), `plan_sha256` ≠ the live plan (`plan-sha-mismatch-live`); the block in the plan is byte-equal to the executed one. The approve of THIS revision waits on the addressed m-1 exchange EXISTING in pdc (034009 / 040334): the companion SITREP asks master for the request TO m-1.planner; m-1 replies in that lineage; master's carry then names all four objects by digest. Silence is not consent; a `keep the freeze` word from either owner ⇒ a plan revision that re-pins the sha at c4a / c4b / c6b and says why. Steps 1–4 (tests, implementation, the re-oracle hunks, the floor) proceed under the token meanwhile — bytes in the worktree, no commit.
- [ ] **Step 3c (rev17, R-4.62 arm (a) — the STOP 175439: the untouched probe fixture `tests/test_probe.cpp:580` reds sporadically on this host, 2 in 40 in isolation at the D0-pinned candidate binary; owner-at-open m-3.planner, arm (a) triggered by m-3's own rule 180036; the patch authored at m-3's seat 183855, APPROVED at the exact sha by m-3.implementer 190602, the fields carried by master 191012; the vehicle = the Task 8 arm-A shape ruled by master 182240): m-3's test-only patch applied VERBATIM as ONE commit with m-3's authorship BEFORE Step 4's floor, then the rebuilt binary, then m-3's WITNESS** — the gate file `$RUNNERS/m3-r462-patch.txt` (the pair Planner's bytes, three fields, one per line: `patch=master/domains/m-3-restore-cli/patches/2026-09-19-r462-test-probe-fixture-bounds.patch` · `sha256=69e8db84c2a7be37d52436bde8d98495aef391a4fbdf58e93801f68a1faab81e` · `relay=master/relays/intg-2b-wiring-act/DESIGN-REVIEW-implementer-20260919-190602.md`) is bound by the EXECUTABLE block below: exactly those three fields; both paths pdc-relative, `..`-free, non-symlink, tracked and unmodified in `../pdc` (the patch beneath `master/domains`, the relay beneath `master/relays`); the patch re-hashed MUST equal `sha256=`; the relay is m-3.implementer's DESIGN-REVIEW with `DESIGN_REVIEW_VERDICT: approve` and `TARGET_PATCH_SHA256:` equal to the same digest, naming the same `patch=`/`sha256=` lines; the mailbox's `From:` is m-3.planner; the tree before the commit: HEAD's `tests/test_probe.cpp` at the pre-image `b03b33db…` (the file is byte-identical at B and c3), the index clean, the dirty set EXACTLY the ten c4a paths, no untracked path; `git apply --check` rc 0; `git apply --numstat` EXACTLY `11	5	tests/test_probe.cpp`; `git am` → exactly ONE new commit whose parent is the previous HEAD, author `m-3.planner <m-3.planner@local>`, touching only `tests/test_probe.cpp`, whose post-image is `fbaee3bf…`; the ten-path dirty set and the clean index UNCHANGED across the commit; `commits.r462.txt` and `code/c4a-r462-patch.txt` written. Then `cmake --build --preset ci-macos` rc 0 and the probe binary's digest MUST differ from D0's (`code/c4a-probe-binary.sha256`). Then THE WITNESS m-3 accepts (183855, = the pair's recipe): the exact case ×20 in isolation (D1) and ×20 under 2×-core-count `yes` load (D2) at the rebuilt binary — per run its own `TMPDIR` under `$EVID/work/r462/`, a 5 ms watcher that, on sighting the fixture's `direct-child-exiting` marker, re-reads it at 1 ms until its content appears or the file is gone, THEN takes the clock (`marker_seen_ms`, the read loop precedes it: the marker lives ~10 ms and one clock call costs ~5 ms, so the read must come first — the walk saw empty reads when the clock came first) and copies it before the fixture's `TempDir` removes it (the fixture deletes its directory at scope exit, so a black-box witness cannot read the marker AFTER the run — the assertion's own expansion, `-1` = absent at every read / `0` = empty read / `>0`, stays the primary discriminator; the copy and the sighting time are the secondary), Catch2 `--durations yes`, the wall time bracketed in ms, `uptime` before and after; every run's directory kept. 40/40 CLOSES arm (a) (m-3's criterion); ANY red → STOP to the pair Planner (R-4.62 re-opens with the discriminators; forty greens are the owner's closure criterion, NOT permission to retry until green — 190602). The patch's `6000 × 5 ms` is a requested-sleep cap, not an elapsed cap (190602): a hung fixture takes ~30 s per poll to fail, which is the intended guard, not a budget. m-3's scope ruling leaves the unrelated `:531` bound AS IS; a red there under Step 4's floor is a NEW R-4.62 observation (arm (c)) → STOP, never a retry.

```bash
# Task 4 Step 3c — R-4.62 arm (a): m-3's approved test-only patch applied VERBATIM as ONE commit with m-3's authorship, the rebuild, m-3's witness (rev17)
set -o pipefail
STOP() { printf 'STOP-r462 %s line=%s\n' "$1" "${BASH_LINENO[0]}" >&2; exit 1; }
[ -n "$RUNNERS" ] && [ -n "$EVID" ] && [ -d "$EVID/code" ] || STOP env
F=$RUNNERS/m3-r462-patch.txt; [ -s "$F" ] || STOP file-absent
g=0; n=$(grep -c . "$F") || g=$?; [ "$g" -eq 0 ] && [ "$n" -eq 3 ] || STOP "field-count-$n"
field() { g=0; n=$(grep -c -E "^$1=" "$F") || g=$?; [ "$g" -le 1 ] && [ "$n" -eq 1 ] || STOP "field-$1-count-$n"
  v=$(sed -n -E "s/^$1=([^[:space:]]+)$/\1/p" "$F") || STOP "field-$1-read"; [ -n "$v" ] || STOP "field-$1-empty"; printf '%s' "$v"; }
patch=$(field patch) || exit 1; sha=$(field sha256) || exit 1; relay=$(field relay) || exit 1
printf '%s' "$sha" | grep -q -E '^[0-9a-f]{64}$' || STOP sha-form
PDC=$(cd ../pdc && pwd -P) || STOP pdc; [ -d "$PDC/master/relays" ] && [ -d "$PDC/master/domains" ] || STOP pdc-tree
resolve() { case "$1" in /*|*..*) STOP "path-$2";; esac; [ ! -L "$PDC/$1" ] && [ -f "$PDC/$1" ] || STOP "notfile-$2"
  d=$(cd "$PDC/$(dirname "$1")" && pwd -P) || STOP "dir-$2"; case "$d/" in "$PDC/master/$3/"*) ;; *) STOP "outside-$2";; esac
  git -C "$PDC" ls-files --error-unmatch -- "$1" >/dev/null 2>&1 || STOP "untracked-$2"; git -C "$PDC" diff --quiet HEAD -- "$1" || STOP "modified-$2"; printf '%s' "$PDC/$1"; }
PF=$(resolve "$patch" patch domains) || exit 1; RF=$(resolve "$relay" relay relays) || exit 1
h=0; ph=$(shasum -a 256 "$PF" | cut -d' ' -f1) || h=$?; [ "$h" -eq 0 ] && [ "$ph" = "$sha" ] || STOP patch-sha
h=0; rh=$(shasum -a 256 "$RF" | cut -d' ' -f1) || h=$?; [ "$h" -eq 0 ] && [ -n "$rh" ] || STOP relay-sha
line1() { g=0; k=$(grep -c -x -F -- "$2" "$1") || g=$?; [ "$g" -le 1 ] && [ "$k" -eq 1 ] || STOP "$3"; }
line1 "$RF" 'FROM: m-3.implementer' relay-from; line1 "$RF" 'PHASE: DESIGN-REVIEW' relay-phase; line1 "$RF" 'AUTHORITY: review-only' relay-authority
line1 "$RF" 'DESIGN_REVIEW_VERDICT: approve' relay-verdict; line1 "$RF" "TARGET_PATCH_SHA256: $sha" relay-target-sha
line1 "$RF" "patch=$patch" relay-patch-line; line1 "$RF" "sha256=$sha" relay-sha-line
line1 "$PF" 'From: "m-3.planner" <m-3.planner@local>' patch-author
# the tree before the commit
git diff --cached --quiet || STOP index-dirty
u=$(git ls-files --others --exclude-standard); r=$?; [ "$r" -eq 0 ] && [ -z "$u" ] || STOP untracked
git diff HEAD --name-only > "$EVID/code/c4a-r462-pre-write-set.txt"; r=$?; [ "$r" -eq 0 ] || STOP diff-producer
ws=$(LC_ALL=C sort "$EVID/code/c4a-r462-pre-write-set.txt" | tr '\n' ' '); r=$?; [ "$r" -eq 0 ] || STOP sort-producer
[ "$ws" = 'src/cli/main.cpp src/cli/url_consent.cpp src/cli/url_consent.hpp src/core/open/open.cpp src/core/open/open.hpp src/core/report/envelope.cpp src/core/report/envelope.hpp tests/test_cli.cpp tests/test_envelope.cpp tests/test_open.cpp ' ] || STOP pre-write-set
git diff HEAD --quiet -- tests/test_probe.cpp || STOP probe-file-dirty
h=0; pre=$(git show HEAD:tests/test_probe.cpp | shasum -a 256 | cut -d' ' -f1) || h=$?; [ "$h" -eq 0 ] && [ "$pre" = b03b33dbc78b18d6c574d902e819b1e7adee1d9e9e94abc65146f0cf88132b35 ] || STOP preimage
git apply --check "$PF" || STOP apply-check
ns=$(git apply --numstat "$PF"); r=$?; [ "$r" -eq 0 ] && [ "$ns" = "$(printf '11\t5\ttests/test_probe.cpp')" ] || STOP "numstat"
PREHEAD=$(git rev-parse HEAD) || STOP head
# the commit, m-3's authorship preserved by the mailbox
a=0; git am "$PF" > "$EVID/code/c4a-r462-am.log" 2>&1 || a=$?; [ "$a" -eq 0 ] || { git am --abort >/dev/null 2>&1; STOP am; }
POSTHEAD=$(git rev-parse HEAD) || STOP head2; [ "$POSTHEAD" != "$PREHEAD" ] || STOP no-commit
[ "$(git rev-parse HEAD~1)" = "$PREHEAD" ] || STOP not-one-commit
[ "$(git log -1 --format=%an)" = m-3.planner ] && [ "$(git log -1 --format=%ae)" = m-3.planner@local ] || STOP author
[ "$(git show --format= --name-only HEAD)" = tests/test_probe.cpp ] || STOP commit-files
h=0; post=$(git show HEAD:tests/test_probe.cpp | shasum -a 256 | cut -d' ' -f1) || h=$?; [ "$h" -eq 0 ] && [ "$post" = fbaee3bf1dd00f6764e9fafa3a4e1dd8a80a0eff106c88fd9824273e0adedacd ] || STOP postimage
git diff --cached --quiet || STOP index-dirty-after
git diff HEAD --name-only > "$EVID/code/c4a-r462-post-write-set.txt"; r=$?; [ "$r" -eq 0 ] || STOP diff-producer2
ws=$(LC_ALL=C sort "$EVID/code/c4a-r462-post-write-set.txt" | tr '\n' ' '); r=$?; [ "$r" -eq 0 ] || STOP sort-producer2
[ "$ws" = 'src/cli/main.cpp src/cli/url_consent.cpp src/cli/url_consent.hpp src/core/open/open.cpp src/core/open/open.hpp src/core/report/envelope.cpp src/core/report/envelope.hpp tests/test_cli.cpp tests/test_envelope.cpp tests/test_open.cpp ' ] || STOP post-write-set
printf '%s\n' "$POSTHEAD" > "$EVID/commits.r462.txt" || STOP commits-write; [ -s "$EVID/commits.r462.txt" ] || STOP commits-empty
printf 'patch=%s sha256=%s relay=%s relay_sha256=%s pre_head=%s post_head=%s preimage=%s postimage=%s\n' "$patch" "$sha" "$relay" "$rh" "$PREHEAD" "$POSTHEAD" "$pre" "$post" > "$EVID/code/c4a-r462-patch.txt" || STOP receipt; [ -s "$EVID/code/c4a-r462-patch.txt" ] || STOP receipt-empty
# the rebuild; the probe binary must change
b=0; cmake --build --preset ci-macos > "$EVID/code/c4a-r462-build.log" 2>&1 || b=$?; [ "$b" -eq 0 ] || STOP build
BIN=./build/ci-macos/biv_probe_tests; [ -x "$BIN" ] || STOP binary
[ -s "$EVID/code/c4a-probe-binary.sha256" ] || STOP d0-binary-receipt-absent
h=0; nb=$(shasum -a 256 "$BIN" | cut -d' ' -f1) || h=$?; ob=$(cat "$EVID/code/c4a-probe-binary.sha256") || STOP; [ "$h" -eq 0 ] && [ "$nb" != "$ob" ] || STOP binary-unchanged
printf '%s\n' "$nb" > "$EVID/code/c4a-r462-binary.sha256" || STOP
# THE WITNESS (m-3 183855 = the pair's recipe): D1 x20 isolation, D2 x20 load; per run: own TMPDIR, the marker watcher, --durations, wall ms, uptime before/after
CASE='version probe preserves clean exit while disposing a pipe-holding grandchild'
ms() { perl -MTime::HiRes=time -e 'printf "%d\n", time*1000'; }
run_case() { local dir="$EVID/work/r462/$1-$2"; mkdir -p "$dir/tmp" || STOP mkdir; uptime > "$dir/uptime-before.txt" || STOP uptime
  ( t0=$(ms); while [ ! -e "$dir/run.done" ]; do for m in "$dir"/tmp/biv-test-post-exit-drain-ledger-*/direct-child-exiting; do
      if [ -e "$m" ]; then c=''; k=0; while [ "$k" -lt 40 ]; do c=$(cat "$m" 2>/dev/null); [ -n "$c" ] && break; [ -e "$m" ] || break; sleep 0.001; k=$((k+1)); done; t1=$(ms); cp -p "$m" "$dir/marker.copy" 2>/dev/null; printf 'marker_seen_ms=%s content=%s reads=%s\n' "$((t1-t0))" "$c" "$k" > "$dir/marker.txt"; exit 0; fi; done; sleep 0.005; done ) & local wpid=$!
  local t0 t1 r=0; t0=$(ms); TMPDIR="$dir/tmp" "$BIN" "$CASE" --durations yes > "$dir/run.log" 2>&1 || r=$?; t1=$(ms)
  : > "$dir/run.done"; wait "$wpid" 2>/dev/null; uptime > "$dir/uptime-after.txt" || STOP uptime2
  [ -e "$dir/marker.txt" ] || printf 'marker_first_seen_ms=none\n' > "$dir/marker.txt"
  printf 'rc=%s wall_ms=%s\n' "$r" "$((t1-t0))" > "$dir/result.txt"; return "$r"; }
p1=0; f1=0; for i in $(seq 1 20); do if run_case d1 "$i"; then p1=$((p1+1)); else f1=$((f1+1)); fi; done
N=$(sysctl -n hw.ncpu) || STOP ncpu; pids=''; for i in $(seq 1 $((N*2))); do yes > /dev/null & pids="$pids $!"; done
p2=0; f2=0; for i in $(seq 1 20); do if run_case d2 "$i"; then p2=$((p2+1)); else f2=$((f2+1)); fi; done
kill $pids 2>/dev/null; wait 2>/dev/null; left=$(pgrep -x yes | wc -l | tr -d ' ')
grep -h -E 'test_probe.cpp:[0-9]+: FAILED' -A3 "$EVID"/work/r462/d[12]-*/run.log 2>/dev/null | grep -v '^--$' | sort | uniq -c > "$EVID/code/c4a-r462-failures.txt"; true
printf 'commit=%s binary=%s d1 pass=%s fail=%s\nd2 pass=%s fail=%s ncpu=%s yes_left=%s\n' "$POSTHEAD" "$nb" "$p1" "$f1" "$p2" "$f2" "$N" "$left" > "$EVID/code/c4a-r462-witness.txt" || STOP witness-write; [ -s "$EVID/code/c4a-r462-witness.txt" ] || STOP witness-empty
cat "$EVID/code/c4a-r462-witness.txt"
[ "$f1" -eq 0 ] && [ "$f2" -eq 0 ] || STOP witness-red
printf 'r462 arm (a) witness 40/40 at %s\n' "$nb"
```

- [ ] **Step 4: run to verify pass (the FULL floor, re-run after Step 3b — rev13 — at the binary Step 3c rebuilt after its 40/40 witness — rev17)** — the focused `[open-repos]` cases + the pointer-heads partition + the four c4a mutants of Step 3 re-run at the final bytes (receipts re-cut: `c4a-green4.log`, `c4a-pointer-heads3.log`, `c4a-mutants2.log`, `c4a-display-mutant2.log`); then `./build/ci-macos/biv_tests` rc 0 with `0 failed` on the whole binary (`c4a-full2.log`, run under `env -u ANTHROPIC_API_KEY` if the ambient key trips the harness scanner — the credential VALUE is never read or recorded); `ctest --preset ci-macos -E '^safety-hardening$'` rc 0 (no schema byte and no selftest pin move in c4a); the five oracle mutants of Step 3b red. (rev17) Receipts re-cut after Step 3c carry the suffix `-r462` (`c4a-green4-r462.log`, `c4a-full2-r462.log`, `c4a-ctest-r462.log`, …); every earlier receipt — the red floor's, the D1/D2 logs — STAYS in the home (master 175324 condition (i)); the packet's cell-(v) input discloses the single red with the D1/D2 counts (condition (ii)). A red on `tests/test_probe.cpp`'s `:531` bound (the case m-3's scope ruling left as is) is a NEW R-4.62 observation (arm (c)) → STOP to the pair Planner, never a retry; any other red is the STOP it always was.
- [ ] **Step 5: commit c4a (the sealed bytes + the re-oracled case, ONE commit)** —

```bash
# T-ORACLE (master 032924 → m-3 033307; master's addressed request TO m-1 → m-1's addressed reply; master's CARRY TO the pair): the owner words
# on the re-oracle of tests/test_open.cpp:343, read from the relays themselves and PINNED — never from a summary word. Run IMMEDIATELY before
# c4a's `git add`; every check STOPs before bytes; each producer's rc is checked apart from its predicate's.
set -o pipefail
STOP() { printf 'STOP-t-oracle %s line=%s\n' "$1" "${BASH_LINENO[0]}" >&2; exit 1; }
[ -n "$RUNNERS" ] && [ -n "$EVID" ] && [ -d "$EVID/code" ] || STOP env
F=$RUNNERS/t-oracle.txt; [ -s "$F" ] || STOP file-absent
PDC=$(cd ../pdc && pwd -P) || STOP pdc; PDCR=$PDC/master/relays; [ -d "$PDCR" ] || STOP pdc-relays
MAIN=$(cd "$(git rev-parse --git-common-dir)/.." && pwd -P) || STOP main
PLAN=$MAIN/docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep2b-20260915.md; [ -s "$PLAN" ] || STOP plan-absent
WINDOW=master/relays/intg-2b-wiring-act/PLAN-master-planner-20260919-032924.md; WINDOW_SHA=a199b971903421e7dc5aff49ff3a23a2da63a43cf0739130c3bde11a4166c7a1      # the objection window (TO m-3)
M3_RELAY=master/relays/intg-2b-wiring-act/DESIGN-planner-20260919-033307.md; M3_SHA=20c9f24d0652285298ca88bd67d66d3cd861d1ebc2093b6606d76a1d4a9554e7                 # m-3's word, PINNED by the plan
CASE='tests/test_open.cpp:343'
field() { g=0; n=$(grep -c -E "^$1=" "$F") || g=$?; [ "$g" -le 1 ] && [ "$n" -eq 1 ] || STOP "field-$1-count-$n"
  v=$(sed -n -E "s/^$1=([^[:space:]]+)$/\1/p" "$F") || STOP "field-$1-read"; [ -n "$v" ] || STOP "field-$1-empty"; printf '%s' "$v"; }
m1_request=$(field m1_request) || exit 1; m1_relay=$(field m1_relay) || exit 1; carry_relay=$(field carry_relay) || exit 1; plan_sha256=$(field plan_sha256) || exit 1
for a in "$m1_request" "$m1_relay" "$carry_relay"; do [ "$a" != "$M3_RELAY" ] && [ "$a" != "$WINDOW" ] || STOP relays-not-distinct; done
[ "$m1_request" != "$m1_relay" ] && [ "$m1_request" != "$carry_relay" ] && [ "$m1_relay" != "$carry_relay" ] || STOP relays-not-distinct
printf '%s' "$plan_sha256" | grep -q -E '^[0-9a-f]{64}$' || STOP plan-sha-shape
h=$(shasum -a 256 "$PLAN" | cut -d' ' -f1) || STOP plan-hash; [ "$h" = "$plan_sha256" ] || STOP "plan-sha-mismatch-live-$h"
resolve() { # pdc-relative, no absolute, no `..`, not a symlink, a regular file whose real dir lies beneath master/relays, tracked + unmodified in pdc
  case "$1" in /*|..|../*|*/..|*/../*) STOP "path-shape-$2";; esac
  [ ! -L "$PDC/$1" ] || STOP "symlink-$2"; [ -f "$PDC/$1" ] && [ -s "$PDC/$1" ] || STOP "absent-$2"
  d=$(cd "$(dirname "$PDC/$1")" && pwd -P) || STOP "dir-$2"; case "$d" in "$PDCR"|"$PDCR"/*) :;; *) STOP "outside-root-$2";; esac
  git -C "$PDC" ls-files --error-unmatch -- "$1" >/dev/null 2>&1 || STOP "untracked-$2"
  s=$(git -C "$PDC" status --porcelain -- "$1") || STOP "status-$2"; [ -z "$s" ] || STOP "modified-$2"; printf '%s' "$PDC/$1"; }
sha()   { h=$(shasum -a 256 "$1" | cut -d' ' -f1) || STOP "hash-$2"; printf '%s' "$h"; }
line1() { g=0; k=$(grep -c -x -F -- "$2" "$1") || g=$?; [ "$g" -le 1 ] && [ "$k" -eq 1 ] || STOP "$3"; }
has()   { g=0; k=$(grep -c -F -- "$2" "$1") || g=$?; [ "$g" -le 1 ] && [ "$k" -ge 1 ] || STOP "$3"; }
subject_no_objection() { g=0; k=$(grep -c -E '^SUBJECT: .*NO OBJECTION' "$1") || g=$?; [ "$g" -le 1 ] && [ "$k" -eq 1 ] || STOP "$2-subject-not-no-objection"
  g=0; k=$(grep -c -i -E '^SUBJECT: .*(keep the freeze|OBJECTION:|OBJECTS|NOT CLEARED|blocked)' "$1") || g=$?; [ "$g" -le 1 ] && [ "$k" -eq 0 ] || STOP "$2-subject-objects"; }
# (1) the window, pinned
W=$(resolve "$WINDOW" window) || exit 1; [ "$(sha "$W" window)" = "$WINDOW_SHA" ] || STOP window-bytes
# (2) m-3's word, PINNED: its DESIGN relay to master replying to the window, on this case, SUBJECT NO OBJECTION
R3=$(resolve "$M3_RELAY" m3) || exit 1; r3=$(sha "$R3" m3) || exit 1; [ "$r3" = "$M3_SHA" ] || STOP "m3-bytes-$r3"
line1 "$R3" 'FROM: m-3.planner' m3-from; line1 "$R3" 'TO: master.master-planner' m3-to; line1 "$R3" 'PHASE: DESIGN' m3-phase; line1 "$R3" 'AUTHORITY: design-only' m3-authority
line1 "$R3" "IN_REPLY_TO: $WINDOW" m3-lineage; has "$R3" "$CASE" m3-not-this-case; subject_no_objection "$R3" m3
# (3) master's ADDRESSED request TO m-1 (MUST-2B-31): a PLAN relay FROM master TO m-1.planner naming the window, the case and T-ORACLE
RQ=$(resolve "$m1_request" m1-request) || exit 1; rq=$(sha "$RQ" m1-request) || exit 1
line1 "$RQ" 'FROM: master.master-planner' m1req-from; line1 "$RQ" 'TO: m-1.planner' m1req-to; line1 "$RQ" 'PHASE: PLAN' m1req-phase; line1 "$RQ" 'AUTHORITY: plan-only' m1req-authority
has "$RQ" "$WINDOW" m1req-not-naming-window; has "$RQ" "$CASE" m1req-not-this-case; has "$RQ" 'T-ORACLE' m1req-not-t-oracle
# (4) m-1's ADDRESSED reply: its DESIGN relay to master replying to THAT request, on this case, SUBJECT NO OBJECTION; its digest is carried by master's carry (below)
R1=$(resolve "$m1_relay" m1) || exit 1; r1=$(sha "$R1" m1) || exit 1
line1 "$R1" 'FROM: m-1.planner' m1-from; line1 "$R1" 'TO: master.master-planner' m1-to; line1 "$R1" 'PHASE: DESIGN' m1-phase; line1 "$R1" 'AUTHORITY: design-only' m1-authority
line1 "$R1" "IN_REPLY_TO: $m1_request" m1-lineage; has "$R1" "$CASE" m1-not-this-case; subject_no_objection "$R1" m1
# (5) master's CARRY TO the pair: exact header lines + FIVE exact, unique T-ORACLE fields — the affirmative verdict, the plan it clears, both owner objects BY DIGEST, the m-1 request
RC=$(resolve "$carry_relay" carry) || exit 1; rc=$(sha "$RC" carry) || exit 1
line1 "$RC" 'FROM: master.master-planner' carry-from; line1 "$RC" 'TO: intg.pair-planner' carry-to; line1 "$RC" 'PHASE: PLAN' carry-phase; line1 "$RC" 'AUTHORITY: plan-only' carry-authority
g=0; k=$(grep -c -E '^T_ORACLE_VERDICT:' "$RC") || g=$?; [ "$g" -le 1 ] && [ "$k" -eq 1 ] || STOP "carry-verdict-count-$k"
line1 "$RC" 'T_ORACLE_VERDICT: cleared' carry-verdict-not-cleared
line1 "$RC" "T_ORACLE_PLAN_SHA256: $plan_sha256" carry-plan-sha
line1 "$RC" "T_ORACLE_M3: $M3_RELAY sha256=$M3_SHA" carry-m3-object
line1 "$RC" "T_ORACLE_M1: $m1_relay sha256=$r1" carry-m1-object
line1 "$RC" "T_ORACLE_M1_REQUEST: $m1_request sha256=$rq" carry-m1-request
printf 'window=%s sha256=%s\nm3_relay=%s sha256=%s\nm1_request=%s sha256=%s\nm1_relay=%s sha256=%s\ncarry_relay=%s sha256=%s\nplan_sha256=%s\n' "$WINDOW" "$WINDOW_SHA" "$M3_RELAY" "$r3" "$m1_request" "$rq" "$m1_relay" "$r1" "$carry_relay" "$rc" "$plan_sha256" > "$EVID/code/c4a-t-oracle.txt" || STOP receipt
printf 't-oracle OK\n'
# the c4a WRITE SET (MUST-2B-29): every tracked change vs HEAD (staged OR unstaged) is exactly the ten paths, and NO untracked path exists; producers rc-checked apart
set -o pipefail
u=$(git ls-files --others --exclude-standard); r=$?; [ "$r" -eq 0 ] || { echo 'STOP: ls-files producer'; exit 1; }; [ -z "$u" ] || { printf 'STOP: untracked path(s) in the worktree: %s\n' "$u"; exit 1; }
git diff HEAD --name-only > "$EVID/code/c4a-write-set.txt"; r=$?; [ "$r" -eq 0 ] || { echo 'STOP: diff producer'; exit 1; }
ws=$(LC_ALL=C sort "$EVID/code/c4a-write-set.txt" | tr '\n' ' '); r=$?; [ "$r" -eq 0 ] || { echo 'STOP: sort producer'; exit 1; }
[ "$ws" = 'src/cli/main.cpp src/cli/url_consent.cpp src/cli/url_consent.hpp src/core/open/open.cpp src/core/open/open.hpp src/core/report/envelope.cpp src/core/report/envelope.hpp tests/test_cli.cpp tests/test_envelope.cpp tests/test_open.cpp ' ] || { printf 'STOP: the c4a write set is not exactly the ten paths: %s\n' "$ws"; exit 1; }
git add src/core/open/open.hpp src/core/open/open.cpp src/core/report/envelope.hpp src/core/report/envelope.cpp src/cli/main.cpp src/cli/url_consent.hpp src/cli/url_consent.cpp tests/test_cli.cpp tests/test_envelope.cpp tests/test_open.cpp
git commit -m "open: repos/ member class (named by a repos[] row + checksummed; else UnmanifestedMember); staged at the manifest-relative path; restore_entry once per row, parents before children, after plan+consent inside the partial dir; typed url-divergence refusal rows via engine_error_kind; machine carriers valid UTF-8 (machine_text); --offline: zero git, A9.4 listing rows, exit 0; test_open.cpp:343 re-oracled from two source sha pins to anchored occupancy/destination controls (the s3 Task-4 contract kept, the freeze dropped)"
git rev-parse HEAD > "$EVID/commits.c4a.txt"
```

- [ ] **Step 6 (c4b, AFTER the A10 gate of Step 0 holds; lands after c5 in lock order): the failing tests** — `tests/test_cli.cpp` (hand-built images, `provenance=hand-built, interim`; Task 7 re-executes on product-packed images), each case naming its A10.4 leg and mutant (thirteen legs (a)–(m) at rev6 — every one written here, none deferred): **(h) THE ROWS** — two repos (one restored, one shallow-pointer) → `result.repos` with EXACTLY the T-JSON fields and enum words, manifest order; an image with zero repos → NO `repos` member (NAMED MUTANT: `[]` at zero state, or an extra/missing field ⇒ RED); `result.manifest.repos` unchanged; **(a) NOTICE BEFORE GIT** — `run_cmd_pty_split`, a networked image (one overlay row), no flag: the NOTICE + PROMPT bytes on the pty EXACTLY as T-NET spells them, ONCE, and the shim log shows ZERO git invocations before the answer is read; `y` ⇒ git runs (NAMED MUTANT: a git call before the answer, or a second render ⇒ RED); **(b) DECLINE** — `n`, then separately empty and EOF: zero git, every network-needing row `offline-pointer`, the A9.4 listing for them, exit 0 (NAMED MUTANT: any git call, a refusal exit, or a missing offline-pointer row ⇒ RED); **(c) NON-INTERACTIVE, NO FLAG** — stdin redirected: no notice, no prompt, zero git, offline-pointer rows, exit 0; **(d) `--network`** — non-interactive with the flag: the NOTICE without the prompt line; git runs (NAMED MUTANT: notice absent, or the prompt line present ⇒ RED); **(e) `--json` PARITY** — (a) and (d) with `--json`: stderr bytes identical, stdout JSON-only, no new envelope member; **(f) `--offline`** — the surface never renders; A9's listing renders instead; **(g) PROMPT D UNTOUCHED** — after `y` (and after `--network`) a divergent triple still renders PROMPT D (NAMED MUTANT: consent-by-network answering a divergence ⇒ RED); **(i) HOSTILE URL BYTES** — a stored URL carrying CR + U+202E renders in the notice as the exact visible escapes (NAMED MUTANT: a raw control byte on the stream ⇒ RED); **(j) THE RECONSTRUCT FORMS + RCPT-Q (A10.4 (j) at 17fda846)** — `open --offline` on an image with THREE artifact-present rows — a BORN row (branch + a side branch + a tag, penumbra payload at its relpath), an UNBORN row (sealed G: unborn `main` plus a committed `side`, penumbra at its relpath), a DETACHED row — prints the born, unborn and detached idioms respectively (T-STAGE's forms, byte-exact), each naming the durable artifact `<dest>/.biv/repos/<id>/repo.bundle` (absolute) on the stream; the JSON rows carry `bundle_path` (dest-relative) and `reconstruct` byte-equal to the printed string; `<dest>/.biv/repos/<id>/repo.bundle` exists with the checksum for all three (RCPT-Q); then, with the HARNESS's own git (the user's step, never the product's), each printed command is run TWICE — into the non-empty target and into an absent scratch target — rc 0 in all six runs; born: HEAD symbolic to `refs/heads/<branch>`, the worktree populated, `refs/heads/side` and the tag present, the penumbra files untouched; unborn: HEAD symbolic to `refs/heads/main` with NO HEAD object (`rev-parse --verify HEAD` fails), `side` at `refs/heads/side`; detached: HEAD at `<sha>`, no symbolic ref; nowhere a `refs/remotes/` ref or a remote; two controls: a bundle carrying a branch named `bvpk-restore` still yields rc 0 with that branch restored; a target holding an untracked file at a tracked path makes the born form's checkout REFUSE (rc 1) and leaves the file intact (NAMED MUTANT: a form selected by target state, a `git clone` printed, a fetch refusal, a missing or remote-namespaced ref, a HEAD object on the unborn row, a clobbered file, or `reconstruct` drifting from the printed line ⇒ RED); **(k) COPY-TEXT SAFETY AND EXACT ARGV** — artifact-present rows whose relpath, branch or dest carries, one per row, a copy-safe hazard: a single quote, a double quote, `$(printf SENTINEL)`, a backtick pair, `$HOME`, an embedded ordinary space (U+0020), a `*`; each printed command fed to `/bin/sh -c` with `git` replaced by an argv-recording stub yields argv operands BYTE-EQUAL to the raw values and NO sentinel expansion (the stub's record shows the literal `$(printf SENTINEL)` text); the refspec operands arrive unglobbed (NAMED MUTANT: a substituted sentinel, a split operand, a globbed refspec, or a serialization other than the single-quote rule ⇒ RED); **(l) THE FALLBACK** — artifact-present rows whose relpath carries, one per row, a NON-copy-safe value: TAB (U+0009), LF, ESC, U+202E, a lone 0xFF byte: NO command is printed; the fallback line renders with the values display-encoded per A8-R1; the JSON row has `bundle_path` and NO `reconstruct`; an ordinary sibling row on the same image still prints its command (NAMED MUTANT: a command printed for any of the five, a display escape inside a printed command or inside JSON `reconstruct`, or the ordinary row losing its command ⇒ RED); **(m) OFFLINE-UNBORN SHA** — an `--offline` image with the G row (unborn HEAD, bundle member — predicate TRUE) and the H row (unborn HEAD, no bundle, no eligibility — predicate FALSE): the G row is offline-pointer with `sha` `"(no commits)"`; the H row is payload-only-unborn with `sha` `null`, byte-identical to its consented-open bytes (NAMED MUTANT: null on the offline-pointer row, the literal on the engine-returned row, or the H row relabelled ⇒ RED); an overlay row → no `bundle_path`, no `reconstruct`, no bundle line, nothing under `<dest>/.biv/` (V-A10-8). `tests/test_envelope.cpp`: the schema gains `result.properties.repos` and the selftest blob pin moves in this commit — asserted by the existing pin test.
- [ ] **Step 7 (c4b): run to verify failure** — the row cases fail (`result.repos` absent), the D3 cases fail (no notice; git runs before any answer), the reconstruct cases fail (no artifact under `<dest>/.biv/`).
- [ ] **Step 8 (c4b): the implementation** — exactly the c4b bytes named in Step 3 (the `result.repos` emission + schema + pin; `render_network_consent` and the D3 decision in `main.cpp`'s open flow; the durable placement in `apply_archive`'s offline arm; `bundle_path` / `reconstruct` on full rows; the bundle line), each re-verified against the LOCKED A10 pin before writing. `Command.network` is read HERE and nowhere else.
- [ ] **Step 9 (c4b): run to verify pass, then commit** — `./build/ci-macos/biv_tests` rc 0; `ctest --preset ci-macos -E '^safety-hardening$'` rc 0; `pytest harness/selftest/test_envelope.py` rc 0.

```bash
git add src/core/open/open.hpp src/core/open/open.cpp src/core/report/envelope.hpp src/core/report/envelope.cpp src/cli/main.cpp src/cli/url_consent.hpp src/cli/url_consent.cpp schemas/biv-json-envelope.v1.schema.json harness/selftest/test_envelope.py tests/test_cli.cpp tests/test_envelope.cpp
git commit -m "open: result.repos rows (RepoRestoreRow verbatim; failed kind/detail; offline fields) + schema in the same commit; the D2/D3 network-consent surface (notice before any git; decline => offline-pointer rows, exit 0; --network non-interactive; --json parity; no persistence); the durable offline artifact at <dest>/.biv/repos/<id>/repo.bundle + bundle_path/reconstruct (ONE single-quoted POSIX-sh idiom per stored HEAD state -- born / unborn / detached; git clone for no row; copy-safe or the fallback line with no JSON reconstruct) -- m-3 ADDENDUM 10 <lock id> @ <doc sha256>; m-1 074712 s2"
git rev-parse HEAD > "$EVID/commits.c4b.txt"
```

### Task 5 — c5, the pack verb: matcher → discover → classify → eligibility (mode) → capture leaves-first → repos[] + `repos/<id>/…` members; single-writer exclusion; the narrowed `.git` class behind a typed refusal (pack-engine §1.1/§1.2/§1.3/§2/§4; V-2b-3..6; A7-R3(2))

**Files:** Modify `src/core/scan/scan.hpp`, `src/core/scan/scan.cpp`, `src/core/pack/pack.hpp`, `src/core/pack/pack.cpp`, `src/cli/main.cpp`, `tests/test_scan.cpp`, `tests/test_pack.cpp`, `tests/test_cli.cpp`.
**Interfaces:** Produces `struct ScanExclusions { std::vector<std::string> repo_subtrees; /* CANONICAL relpaths only — see canonical() */ static std::string canonical(const std::filesystem::path& rel); /* lexically_normal().generic_string(); "." and "" both → "" (THE ROOT); no trailing '/' */ bool claims_root() const; /* any entry == "" */ bool claims(std::string_view canonical_rel) const; /* exact match on canonical strings */ }` (`scan.cpp`'s walker relpaths are already canonical: `""` at the root, `a/b` below — `child_relpath` :74-84; `discover()` reports the root boundary as `"."`, which `canonical()` maps to `""` — ONE representation, MUST-2B-12) and `expected<ScanResult> scan(const std::filesystem::path& root, const ignore::Matcher& matcher, const ScanExclusions& excl)` (ROOT-CLAIMED FAST PATH: `if (excl.claims_root()) return ScanResult{};` BEFORE the walk — the workspace-root repository is the single writer of everything beneath it, so the payload and the prune list are EMPTY and no directory is read (V-2b-5); a mutant that removes this line admits every non-`.git` child of the root into the payload) (the old one-arg `scan(root)` is kept as a thin overload building the matcher with no exclusions, so existing callers/tests compile); `expected<MatcherBundle> prepare_matcher(root)` (the matcher + the `BivignoreProvenance` scan already records); `struct PackOptions { bool offline{false}; }` and `expected<PackReport> pack(const std::filesystem::path& source_dir, const PackOptions& options)` (the one-arg overload forwards `{}`); `PackReport.repos` (the `manifest.repos` entries, whole). Consumes Task 1's `EligibilityMode`, the engine API verbatim.

- [ ] **Step 0: the T-FENCE word — RULED (Q11, m-1 074712 §1, carried by master 080937)** — Task 5 STARTS on it: `$RUNNERS/m1-fence-word.txt` is written by the pair Planner from 074712 §1 verbatim (class · site · engine facts · disposition · standing) for the implementer's record, and the `fence != none` branch in Step 3 is the whole-operation typed refusal through the engine seam (no image); the REFUSAL bytes (wire kind, exit 3, sentence, error object) are A11's and land in c6b — at c5 the fence surfaces as the seam's `InternalError` + `repo_engine_kind` (exit 4), which V-A11-1 forbids at H and c6b resolves. Also read `src/core/repo/classify.cpp:120-190` and `:340-360` and record each fence site's trigger condition (`Fence::submodule` :134, `Fence::nested` :146, `Fence::unmerged` :179, `Fence::dirty` :354) to `$EVID/code/fences.txt` — the record the word is graded against (the case is recorded, the task HOLDS at c4 until m-1's disposition per class arrives — Q11); the word, when it lands, is a plan revision's term, not an in-pin branch.
- [ ] **Step 1: the failing tests** — `tests/test_scan.cpp`: the existing "scan refuses repo-bearing roots" case becomes TWO cases: (a) `scan(root, matcher, {.repo_subtrees = {biv::scan::ScanExclusions::canonical(".")}})` — the PRODUCTION value, `discover()`'s root relpath — on a root holding `.git/`, `src/main.cpp` and `README` → succeeds with `payload` EMPTY and `pruned` EMPTY (workspace-root repo ⇒ EMPTY residue, V-2b-5); the same with `{""}` → identical (the two spellings canonicalize to one); NAMED MUTANT: the root-claimed fast path removed → `src/main.cpp` appears in `payload` ⇒ RED. (a′) `{.repo_subtrees = {"lib/vendored"}}` on a tree holding `lib/vendored/.git`, `lib/vendored/x.c`, `lib/other.c` → `payload` holds `lib/other.c` and NO `lib/vendored/**` node and NO `.git` node (the nested single-writer arm); (b) a `.git`-named SYMLINK at the root with `repo_subtrees` empty → `RepoDiscoveredUnsupported` (the kind literal until Task 6 renames it) with `facts["reason"] == "symlink"`; a `.git`-named FIFO (`mkfifo`) → `reason == "special-file"`; a `.git` directory whose parent is NOT a boundary (discover did not claim it — synthesized by passing `repo_subtrees` that omit it) → `reason == "unreadable-marker"`? — NO: the reason vocabulary is m-1's three member classes exactly (`symlink | special-file | unreadable-marker`); an unclaimed `.git` DIRECTORY cannot occur when discover ran on the same tree (discover claims every dir-or-regular-file `.git`), so the test for that shape asserts the boundary path instead. A `.git` REGULAR FILE (gitlink/worktree pointer) IS a boundary (discover) → no refusal. `tests/test_pack.cpp` (ARM-1 REALITY: every packed fixture is CLEAN — committed, with `.gitignore`d files as penumbra; an untracked file IS the dirty fence): "pack refuses repo-bearing source" becomes "pack records a repo-bearing source": `git init` + one commit under `source/`; the FENCE cases (Q11; the seam at c5, re-asserted as A11's wire kinds at c6b): (dirty) the same repo + one untracked file → `pack` FAILS, `error.kind == InternalError`, `facts.repo_engine_kind == "repo-dirty-unsupported"`, NO `.bvpk`, NO `.partial` left under the destination; (nested) a clean repo containing a clean child repo → `"repo-nested-unsupported"` with the child relpath in the engine paths; (submodule) a gitlink → `"repo-submodule-unsupported"`; (unmerged) a conflict fixture → `"unmerged-index-unrepresentable"` with the sorted-unique paths; NAMED MUTANT for all four: an image written, or the fenced repo silently omitted, or captured as `full` ⇒ RED; `pack(source, {})` → `report.repos.size() == 1`; the archive lists `repos/<id>/…` members exactly as `CaptureResult.artifacts[].archive_path` names them; `manifest.json` parsed back → `repos[0].relpath == "."`? (the workspace-root repo's relpath as discover reports it); `--offline` variant on THIS fixture's born, non-shallow repo → `capture_mode == full`, `eligibility.result == offline_declared`, and ZERO `ls-remote` in the request-trace shim log (the composed shapes — shallow, unborn-with-ref, empty-unborn — are UNCHANGED by the flag: Task 1's W-O1..3 unit cases and Task 7's product legs, never asserted here as `full`). `tests/test_cli.cpp`: `biv pack --json` on a repo-bearing source → `result.manifest.repos` is `[]` (unchanged carrier, I2B-09 (b)) while the archive's manifest.json carries the row (the two are different objects — asserted separately).
- [ ] **Step 2: run to verify failure** — `./build/ci-macos/biv_tests '[pack-repos]'` FAILS (`RepoDiscoveredUnsupported` on the directory).
- [ ] **Step 3: the implementation** —
  `scan.cpp` `walk`: the `.git` name test becomes: `if (name == ".git") { if (excl.claims(rel_dir)) continue; /* the boundary's marker: never a payload node */ return std::unexpected(unclaimed_git_entry(child.path(), status)); }` where `unclaimed_git_entry` builds `BivError{ErrKind::RepoDiscoveredUnsupported /* Task 6: UnclaimedGitEntry */, path /* RAW — the machine carrier; machine_text applies at emission */, /*detail*/ {}, 0, {{"reason", is_symlink(status) ? "symlink" : !is_regular_file(status) && !is_directory(status) ? "special-file" : "unreadable-marker"}}}` (the detail is EMPTY in core — the CLI renders the m-3 template once, Task 6); a directory entry whose CANONICAL relpath `excl.claims(...)` is NOT descended and NOT added, and the `.git` test's `excl.claims(rel_dir)` receives the walker's own canonical `rel_dir` (`""` at the root) (V-2b-5; MUST-2B-12; the gitlink entry excepted — a `.git` REGULAR FILE inside a claimed subtree never reaches here because the subtree is skipped whole). The matcher (`.bivignore`) runs FIRST exactly as today (I-R2a; the `continue` at :131 precedes the name test).
  `pack.cpp`, replacing the single `scan::scan(source)` call:

```cpp
  auto matcher = scan::prepare_matcher(source);                    if (!matcher) return cleanup_error(matcher.error());
  auto discovery = repo::discover(source, matcher->matcher);       if (!discovery) return cleanup_error(engine_to_pack_error(discovery.error()));
  scan::ScanExclusions exclusions; for (const auto& b : discovery->repos) exclusions.repo_subtrees.push_back(scan::ScanExclusions::canonical(b.relpath));   // "." → "" (the root); MUST-2B-12
  auto scan_result = scan::scan(source, matcher->matcher, exclusions); if (!scan_result) return cleanup_error(scan_result.error());
  std::vector<repo::RepoEntry> entries; std::vector<repo::CaptureResult> captures;
  if (!discovery->repos.empty()) {
    auto git = repo::Git::resolve(getenv_of(env));                  if (!git) return cleanup_error(git.error());
    for (const auto& b : discovery->repos) {                        // §1.3 classify, discovery (DFS) order
      auto c = repo::classify(*git, source / b.relpath, *discovery); if (!c) return cleanup_error(engine_to_pack_error(c.error()));
      if (c->fence != repo::Classification::Fence::none) return cleanup_error(engine_to_pack_error(repo::make_engine_error(c->issue.kind, b.relpath, c->issue.detail, c->issue.paths)));   // Q11: WHOLE-OPERATION typed refusal through the engine seam — no image (the .partial cleanup); the issue's kind/paths/detail are the facts A11's row renders at c6b (T-FENCE / T-A11); never exclusion, never full+note
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

  `engine_to_pack_error(BivError e)`: (c5) iff `biv::repo::engine_error_kind(e) == biv::repo::EngineErrorKind::url_divergence_refused` (the TYPED accessor at types.hpp:92-110 — the wire fact is `url-divergence-refused`, hyphenated; MUST-2B-01) → `BivError{ErrKind::UrlDivergenceRefused, e.path /* the hook's repo */, {}, 0, {requested, effective, op copied from e.facts}}` (A6-R1's pack grain; M veto 4: never laundered); every other engine error returned UNCHANGED at c5 (the seam: InternalError + fact repo_engine_kind — the fences, promisor_objects_unavailable, git_invocation_failed, git_budget_expired, ref_uncapturable all arrive here); c6b (A11 lock) replaces this arm with the nine-kind mapping (T-A11); unknown kinds STAY InternalError. Control in `tests/test_pack.cpp`: a pack-side divergence → `report.error().kind == ErrKind::UrlDivergenceRefused` with the three facts; NAMED MUTANT: an underscore string compare leaves the error as `InternalError` ⇒ RED. `leaves_first`: indices ordered so every entry precedes its `parent_id` (children first), stable by discovery order. `scratch_path = image_path.parent_path() / (image_path.filename() + ".scratch")` created before capture, removed by the cleanup lambda and at the end. Members: after the payload loop and BEFORE the agents loop (§4 "payload/repos/agents"): for each capture, for each artifact: `write_file_member(spool_writer, artifact.disk_path, artifact.archive_path.generic_string(), created.seconds)`; `emitted_members.insert(archive_path)` must succeed (else `ArchiveWriteFailed` `repo-member-duplicate`); `checksums.entries[archive_path] = extent; ++report.member_count`. The manifest: `.repos = entries` (WHOLE — V-2b-4; `PackReport.repos = entries` for the report). The C-2 propagation hunk (`if (!manifest_json) return cleanup_error(...)`) byte-unchanged.
  `main.cpp` pack: `biv::pack::pack(parsed->pack_dir, biv::pack::PackOptions{.offline = parsed->offline})` inside the `ScopedUrlDivergenceRun` from Task 3; the `UrlDivergenceRefused` detail fill from Task 3 now has a producer.
- [ ] **Step 4: run to verify pass** — `./build/ci-macos/biv_tests` rc 0; `ctest --preset ci-macos -E '^safety-hardening$'` rc 0; `grep -n 'manifest_json' src/core/pack/pack.cpp` shows the C-2 hunk unchanged vs `git show a2f6fd1:src/core/pack/pack.cpp` (recorded diff of those lines EMPTY); V-2b-5 rev2: `git diff "$B" -- src/core/scan/scan.cpp | grep -c -F -- '".biv"'` reads 0 — the any-depth `.biv` payload skip (`:140-142` at B) is untouched (the `.git` name test above it is the ONLY changed test in that block).
- [ ] **Step 5: the RepoEntry production census, then commit** — `python3 "$EVID/repoentry_census.py" src/cli src/core/pack src/core/scan src/core/open > "$EVID/code/repoentry-census.txt"` rc 0 (the TYPE-SCOPED census — §Instruments: every RepoEntry-typed binding enumerated; zero member writes on any of them; MUST-2B-06); its two controls run once here: a scratch copy with `entries[0].sha = "x";` injected → rc 5 (fires); a scratch copy with `warning.path = "x";` injected → rc 0 (does not) — receipts `repoentry-census-controls.txt`.

```bash
git add src/core/scan/scan.hpp src/core/scan/scan.cpp src/core/pack/pack.hpp src/core/pack/pack.cpp src/cli/main.cpp tests/test_scan.cpp tests/test_pack.cpp tests/test_cli.cpp
git commit -m "pack: sealed order (matcher -> discover -> classify -> eligibility(mode) -> capture leaves-first -> assembly); repo subtrees excluded from payload; entries copied whole into manifest.repos; artifacts as members at archive_path verbatim; url_divergence_refused -> UrlDivergenceRefused; the .git refusal narrows to the unclaimed class (kind literal renamed in the next commit)"
git rev-parse HEAD > "$EVID/commits.c5.txt"
```

### Task 6a — c6a, the A9 kind (CONTINGENT on A9's lock — T-KIND): retire `RepoDiscoveredUnsupported`, cut `UnclaimedGitEntry` refusal/3 appended; TC-1..3 fold (m-3 §3; V-A6-3 same-commit; master 131404 (1))

**Files:** Modify `src/core/support/error.hpp`, `src/core/support/error.cpp`, `src/core/report/envelope.cpp`, `src/core/scan/scan.cpp` (the kind literal only), `src/cli/url_consent.hpp`, `src/cli/url_consent.cpp` (`render_unclaimed_git_entry_detail`), `src/cli/main.cpp` (the pack error path fills the detail), `schemas/biv-exit-map.v1.json`, `tests/test_envelope.cpp`, `tests/test_scan.cpp`, `tests/test_pack.cpp` (the RAW core contract), `tests/test_cli.cpp` (the rendered CLI contract), `harness/selftest/test_envelope.py` (the exit-map blob pin). The envelope schema does NOT move (A9.3: `error.kind` is a free string).

- [ ] **Step 0: the lock gate (A9 IS LOCKED — the file is written at Task 0 from T-KIND's values)** — `[ -s "$RUNNERS/m3-addendum-9-lock.txt" ]` holding `lock_id=m3-addendum-9-40eaea22-lock-20260916 doc_sha256=ae27264763b5ec20057b88f78f87d642ab22a28305a532c66c44063603eb2cf0 pin_sha256=40eaea2273a32922640ade0f65b897ad8d52b40dc8eadef3845264fe1f40fa8c relay=master/relays/intg-2b-wiring-act/DESIGN-planner-20260916-165214.md`; the implementer re-hashes the LIVE addendum at the named pdc path (must equal `doc_sha256`, the post-stamp) AND `git -C ../pdc show c2f7a6c7:<path> | shasum -a 256` (must equal `pin_sha256`) — either mismatch ⇒ STOP. The bytes below are the locked pin's; A9.4's D4 header/row bytes are the golden for the offline listing until A10's own lock (no bundle line from A9).
- [ ] **Step 1: the failing tests** — `tests/test_envelope.cpp`: the `ExpectedRow` list loses `{"RepoDiscoveredUnsupported", …}` and gains `{"UnclaimedGitEntry", "refusal", biv::report::exit_for_error(biv::ErrKind::UnclaimedGitEntry)}` as the LAST row; the `:249` literal becomes `"\"UnclaimedGitEntry\", \"class\": \"refusal\", \"exit\": 3"` (no `transitional`); `CHECK(exit_text.find("RepoDiscoveredUnsupported") == std::string::npos)`; the `rows.size()` pin self-adjusts (29 → 29). TC-1: two literal exit pins at the parity find-after-position idiom (`:237,245` → `CHECK(exit == 3)` / `CHECK(exit == 2)` literals beside the derived ones). TC-2: a second accepted entry on the open arm of the one-grouped-object claim (`:830,838`). TC-3: one nonzero-sessions arm for `exit_for_open`'s max composition (`:879-885`). `tests/test_scan.cpp` / `tests/test_pack.cpp` / `tests/test_cli.cpp`: the kind-name assertions flip to `UnclaimedGitEntry`; one fixture per `reason` class.
- [ ] **Step 2: run to verify failure** — compile error (`UnclaimedGitEntry` undeclared).
- [ ] **Step 3: the implementation, ONE commit** — `error.hpp`: remove `RepoDiscoveredUnsupported`; append `UnclaimedGitEntry` LAST (after `UrlDivergenceEntryRefused`); `error.cpp` `to_string` likewise; `envelope.cpp` `exit_for_error`: the `RepoDiscoveredUnsupported` case removed from the exit-3 group, `case ErrKind::UnclaimedGitEntry:` added to it; `scan.cpp`: the kind literal → `UnclaimedGitEntry` (detail stays EMPTY in core); `url_consent.cpp` gains `render_unclaimed_git_entry_detail(std::string_view path, std::string_view reason)` — the byte-golden template (A9.3, VERBATIM) with `<path>` and `<reason>` through `consent_display` — and `main.cpp`'s pack error path fills `error.detail` from it for `kind == UnclaimedGitEntry` exactly as it fills the url-divergence detail (ONE rendered string, TWO carriers; `error.path` RAW through `machine_text` at emission — MUST-A9-1):

```text
pack refused: <path> is a .git-named entry that is not a repository boundary (<reason>); remove or repair it and re-run.
```

  `schemas/biv-exit-map.v1.json`: the `RepoDiscoveredUnsupported` row removed, `{"kind": "UnclaimedGitEntry", "class": "refusal", "exit": 3}` appended as the LAST row (29 rows before and after); `harness/selftest/test_envelope.py` `CURRENT_LOCKED_SCHEMA_BLOBS["schemas/biv-exit-map.v1.json"]` = `git hash-object schemas/biv-exit-map.v1.json` at the new bytes (the same commit). `error.facts["reason"]` ∈ `symlink | special-file | unreadable-marker`. The addendum's lock id and sha are cited in the commit message.
- [ ] **Step 4: run to verify pass** — `ctest --preset ci-macos -E '^safety-hardening$'` rc 0; `pytest harness/selftest/test_envelope.py` rc 0; `python3 -c 'import json;print(len(json.load(open("schemas/biv-exit-map.v1.json"))["rows"]))'` == 29.
- [ ] **Step 5: commit** —

```bash
git add src/core/support/error.hpp src/core/support/error.cpp src/core/report/envelope.cpp src/core/scan/scan.cpp src/cli/url_consent.hpp src/cli/url_consent.cpp src/cli/main.cpp schemas/biv-exit-map.v1.json tests/test_envelope.cpp tests/test_scan.cpp tests/test_pack.cpp tests/test_cli.cpp harness/selftest/test_envelope.py
git commit -m "report: retire RepoDiscoveredUnsupported (transitional placeholder honored); cut UnclaimedGitEntry refusal/3 appended for the unclaimed .git class (reason: symlink|special-file|unreadable-marker; byte-golden detail) -- m-3 addendum 9 <lock id> @ <doc sha256>; exit map 29->29; TC-1..3 folded"
git rev-parse HEAD > "$EVID/commits.c6a.txt"
```

### Task 6b — c6b, the NINE engine-error kinds (CONTINGENT on A11's lock — T-A11): the wire kinds, exit-map rows, error objects and sentences; the failure inventory + failed-mid-apply composition (A11 rev5 33c69913 at its lock; m-1 074712 §3; A9.3's same-commit rule; R-4.32)

**Files:** Modify `src/core/support/error.hpp`, `src/core/support/error.cpp` (nine kinds appended after `UnclaimedGitEntry`, in A11.1's order), `src/core/report/envelope.cpp` (the exit arms; the `failed` row's `kind`/`detail`), `src/core/pack/pack.cpp` (`engine_to_pack_error`'s nine-kind mapping replaces the c5 pass-through), `src/core/open/open.cpp` (the open-side composition per A11 rev5 OPEN INVARIANT — master's MUST-2B-17 ruling (b), m-3 140044: the landed invariant KEPT — `result` null iff `error`; an engine failure at open is the top-level `error` and nothing else — NO `result.repos`, NO row inside `error`, NO rows stringified into facts; the ORCHESTRATOR (m-3's surface, no engine byte) WRITES `<partial_dir>/inventory.json` on failed-mid-apply — `<partial_dir>` = the ONE authorized partial-directory path (T-PARTIAL, RULED (A) by m-1 162306: the suffix is `.bvpk-open.partial`, the landed literal at open.cpp:637, untouched by 2b; c6b writes the inventory, `facts.partial_path`, and any `detect_partial`/`clean_partial` reader byte ONLY from the `partial_dir` value of that one site, and only after Step 0's gate has bound `$RUNNERS/m3-addendum-11-lock.txt`'s `partial_suffix=` / `partial_suffix_relay=` fields to the owner word by bytes): the completed rows, then the failing row with `kind` + `detail`, then the operation outcome `failed-mid-apply(step, repo_id, detail)`, in §2.2 order — one record; `error.detail` equals the failing row's `detail` byte-for-byte; `facts.partial_path` names the partial directory, `facts.repo_id` the failing row's manifest id; the inventory LIVES AND DIES WITH THE PARTIAL (what `detect_partial` reads next run and `clean_partial` removes) and is DISTINCT from §2.3's quarantine inventory of a SUCCEEDED apply — never conflated by name or reader (master 010159 (4); m-3 140045; m-1 171446); `execute_open`'s signature does not move at 2b), `src/cli/url_consent.hpp`, `src/cli/url_consent.cpp` (`render_engine_refusal_detail(kind, facts)` — the eleven A11.3 sentences, each rendered ONCE with every `<…>` value through `consent_display`), `src/cli/main.cpp` (the pack and open error paths fill `error.detail` from the renderer for the nine kinds), `schemas/biv-exit-map.v1.json` (nine rows appended after `UnclaimedGitEntry`), `tests/test_envelope.cpp` (ExpectedRow + literals; counts), `tests/test_pack.cpp`, `tests/test_open.cpp`, `tests/test_cli.cpp`, `harness/selftest/test_envelope.py` (the exit-map blob pin). The envelope schema does NOT move for the kinds (free string); the `failed` row's `kind`/`detail` fields are A10's row shape (c4b) — the `failed` outcome word stays in-memory / inventory vocabulary and is never rendered in an envelope at 2b (A11 rev5).

- [ ] **Step 0: the lock gate — the EXECUTABLE block below, run TWICE: `MODE=pre` before the first c6b test byte (Step 1) and `MODE=post` immediately before the c6b commit (Step 5 refuses without the post receipt)** — it binds THREE carriers, none by existence. The lock file `$RUNNERS/m3-addendum-11-lock.txt` (written by the pair Planner at the lock) carries exactly one nonempty line each of `lock_id` (shape `m3-addendum-11-<8 hex>-lock-<date>` or `m3-addendum-11-<date>`, the A9-shaped or the planned id — whichever the ceremony declares), `doc_sha256` (re-hashed against the A11 document at its fixed pdc path), `relay`, `seal_relay`, `partial_suffix` (== `.bvpk-open.partial`, m-1's ruling 162306, the ONLY admissible value) and `partial_suffix_relay`. Every relay path is pdc-relative, `..`-free, beneath `master/relays` by real directory, TRACKED and UNMODIFIED in pdc (`git ls-files` + empty `status --porcelain`). (1) THE A11 LOCK CARRIER `relay` = m-3.planner's DESIGN relay to master (exact lines `FROM: m-3.planner`, `TO: master.master-planner`, `PHASE: DESIGN`, `AUTHORITY: design-only`) naming `lock_id` as a whole word and `doc_sha256`, and citing the A11 document in its `RELATED_CONTEXT`/`IN_REPLY_TO`. (2) THE SEAL CARRIER `seal_relay` = master's PLAN relay TO the pair (exact lines `FROM: master.master-planner`, `TO: intg.pair-planner`, `PHASE: PLAN`, `AUTHORITY: plan-only`), whose `IN_REPLY_TO` line is EXACTLY `relay` (lineage), naming the same `lock_id` and `doc_sha256`, containing the word SEALED; `seal_relay` ≠ `relay`. (3) THE SUFFIX WORD `partial_suffix_relay` — arm 1 the exact m-1 ruling (sha256 `82e37092a2a5405ef943c194ee313a3a09482432ac599e5a7e64213a74ad7a6f`, its FROM/TO/PHASE/AUTHORITY lines, the RULED (A) sentence) or arm 2 the already-bound lock carrier itself declaring `partial_suffix=.bvpk-open.partial`; any other path STOPs. Then the two one-site counts on `src/core/open/open.cpp` with the producer rc apart, the receipt `$EVID/code/c6b-partial-suffix.<pre|post>.txt` (carrying both carriers' sha256) and the post-vs-pre comparison. The carrier checks are the SHAPE OF THE A9 CEREMONY (m-3 `165214` → master `170242`): EXECUTED by the pair at B as the must-be-YES with the two A11 constants substituted for A9's (doc path, id prefix — the variant is the block plus exactly those two `sed` substitutions): pre + post PASS on the real 165214/170242 pair with `ae272647…`; nine must-be-NO controls each STOP before any receipt — the reviewer's bypass (`relay` = master 010159 with the exact ruling: `lock-from`), `seal_relay` = 010159 (`seal-lineage`), `relay` = another m-3 DESIGN relay 134813 (`lock-to`), the planned-shape id absent from the carriers (`lock-id-absent-in-lock-relay`), arm 2 with a lock relay lacking the field (`lock-relay-spelling`), seal == lock (`lock-seal-same-file`), a master-to-pair PLAN not replying to the lock relay 135421 (`seal-lineage`), a wrong doc sha (`a11-sha-mismatch`), and the unmodified A11 block with `relay` = 010159 (`lock-from`). The bytes below (planned from A11 rev5 `33c699138a0bb6a240d7e0a8f50407e83e39c72635ae078964c196fbec97ea3a`, the revision this plan transcribes) are re-verified line-by-line against the LOCKED pin — a locked byte differing from rev5's (beyond m-3's respelling of :82/:85/:167 to the ruled suffix) is a new plan revision. Absent lock file → HOLD here (Task 7's A11 legs wait; the c5 seam stands meanwhile).

```bash
# Task 6b Step 0 — the A11 lock + T-PARTIAL gate (MUST-2B-25 / MUST-2B-26). Run with MODE=pre BEFORE the first c6b test byte and
# again with MODE=post IMMEDIATELY BEFORE the c6b commit (Step 5 refuses without the post receipt). Every check STOPs before bytes;
# each producer's rc is checked apart from its predicate's. THREE carriers are bound, none by existence: the A11 LOCK relay
# (m-3.planner's DESIGN relay declaring the lock id + the locked doc sha, committed in pdc), master's SEAL relay (PLAN, TO the pair,
# replying to the lock relay, naming the same id + sha, committed in pdc), and the SUFFIX word (m-1's ruling by sha256, or the lock
# relay itself). The carrier checks are the shape of the A9 ceremony (165214 + 170242), on which they were executed as the must-be-YES.
set -o pipefail
STOP() { printf 'STOP-c6b-gate %s line=%s\n' "$1" "${BASH_LINENO[0]}" >&2; exit 1; }
MODE=${MODE:-pre}; case "$MODE" in pre|post) :;; *) STOP mode;; esac
[ -n "$RUNNERS" ] && [ -n "$EVID" ] && [ -d "$EVID/code" ] || STOP env
LOCK=$RUNNERS/m3-addendum-11-lock.txt; [ -s "$LOCK" ] || STOP lock-absent
PDC=$(cd ../pdc && pwd -P) || STOP pdc; PDCR=$PDC/master/relays; [ -d "$PDCR" ] || STOP pdc-relays
A11_DOC=master/domains/m-3-restore-cli/design/2026-09-16-addendum-11-engine-error-surfacing-rows.md
LOCK_ID_RE='^m3-addendum-11-([0-9a-f]{8}-lock-)?[0-9]{8}$'      # the planned id, or the A9-shaped id with the pin's 8 hex + "-lock-"
field() { # exactly ONE `key=value` line; value nonempty, no whitespace
  g=0; n=$(grep -c -E "^$1=" "$LOCK") || g=$?; [ "$g" -le 1 ] && [ "$n" -eq 1 ] || STOP "field-$1-count-$n"
  v=$(sed -n -E "s/^$1=([^[:space:]]+)$/\1/p" "$LOCK") || STOP "field-$1-read"; [ -n "$v" ] || STOP "field-$1-empty"; printf '%s' "$v"; }
lock_id=$(field lock_id) || exit 1; doc_sha256=$(field doc_sha256) || exit 1; relay=$(field relay) || exit 1; seal_relay=$(field seal_relay) || exit 1
partial_suffix=$(field partial_suffix) || exit 1; partial_suffix_relay=$(field partial_suffix_relay) || exit 1
printf '%s' "$lock_id" | grep -q -E "$LOCK_ID_RE" || STOP lock-id-shape
printf '%s' "$doc_sha256" | grep -q -E '^[0-9a-f]{64}$' || STOP doc-sha-shape
[ "$partial_suffix" = .bvpk-open.partial ] || STOP partial-suffix-value          # m-1's ruling 162306: the ONLY admissible value
[ -s "$PDC/$A11_DOC" ] || STOP a11-absent
h=$(shasum -a 256 "$PDC/$A11_DOC" | cut -d' ' -f1) || STOP a11-hash; [ "$h" = "$doc_sha256" ] || STOP a11-sha-mismatch
resolve() { # $1 = a pdc-relative relay path (no absolute, no `..` component); real directory beneath master/relays; COMMITTED in pdc, unmodified
  case "$1" in /*|..|../*|*/..|*/../*) STOP "relay-path-shape-$2";; esac
  [ -s "$PDC/$1" ] || STOP "relay-absent-$2"; d=$(cd "$(dirname "$PDC/$1")" && pwd -P) || STOP "relay-dir-$2"
  case "$d" in "$PDCR"|"$PDCR"/*) :;; *) STOP "relay-outside-root-$2";; esac
  git -C "$PDC" ls-files --error-unmatch -- "$1" >/dev/null 2>&1 || STOP "relay-untracked-$2"
  s=$(git -C "$PDC" status --porcelain -- "$1") || STOP "relay-status-$2"; [ -z "$s" ] || STOP "relay-modified-$2"; printf '%s' "$PDC/$1"; }
line1() { g=0; k=$(grep -c -x -F -- "$2" "$1") || g=$?; [ "$g" -le 1 ] && [ "$k" -eq 1 ] || STOP "$3"; }         # exactly one whole line
has()   { g=0; k=$(grep -c -F -- "$2" "$1") || g=$?; [ "$g" -le 1 ] && [ "$k" -ge 1 ] || STOP "$3"; }            # at least one occurrence
hasw()  { g=0; k=$(grep -c -w -F -- "$2" "$1") || g=$?; [ "$g" -le 1 ] && [ "$k" -ge 1 ] || STOP "$3"; }         # as a whole word
R1=$(resolve "$relay" lock) || exit 1; R3=$(resolve "$seal_relay" seal) || exit 1; [ "$relay" != "$seal_relay" ] || STOP lock-seal-same-file
# --- the A11 LOCK carrier: m-3.planner's DESIGN relay to master declaring THIS lock id and THIS doc sha, citing the A11 document
line1 "$R1" 'FROM: m-3.planner' lock-from; line1 "$R1" 'TO: master.master-planner' lock-to; line1 "$R1" 'PHASE: DESIGN' lock-phase; line1 "$R1" 'AUTHORITY: design-only' lock-authority
hasw "$R1" "$lock_id" lock-id-absent-in-lock-relay; has "$R1" "$doc_sha256" doc-sha-absent-in-lock-relay
g=0; k=$(grep -c -E "^(RELATED_CONTEXT|IN_REPLY_TO): .*$(basename "$A11_DOC")" "$R1") || g=$?; [ "$g" -le 1 ] && [ "$k" -ge 1 ] || STOP lock-relay-not-citing-a11
# --- the SEAL carrier: master's PLAN relay TO the pair, IN_REPLY_TO the lock relay, naming the same id + sha, saying SEALED
line1 "$R3" 'FROM: master.master-planner' seal-from; line1 "$R3" 'TO: intg.pair-planner' seal-to; line1 "$R3" 'PHASE: PLAN' seal-phase; line1 "$R3" 'AUTHORITY: plan-only' seal-authority
line1 "$R3" "IN_REPLY_TO: $relay" seal-lineage; hasw "$R3" "$lock_id" lock-id-absent-in-seal; has "$R3" "$doc_sha256" doc-sha-absent-in-seal
g=0; k=$(grep -c -i -w 'SEALED' "$R3") || g=$?; [ "$g" -le 1 ] && [ "$k" -ge 1 ] || STOP seal-word
# --- the SUFFIX word: arm 1 the exact m-1 ruling by bytes; arm 2 the (already-bound) lock relay declaring the field
RULING=master/relays/intg-2b-wiring-act/DESIGN-planner-20260918-162306.md; RULING_SHA=82e37092a2a5405ef943c194ee313a3a09482432ac599e5a7e64213a74ad7a6f
if [ "$partial_suffix_relay" = "$RULING" ]; then
  R2=$(resolve "$partial_suffix_relay" suffix) || exit 1
  h=$(shasum -a 256 "$R2" | cut -d' ' -f1) || STOP ruling-hash; [ "$h" = "$RULING_SHA" ] || STOP ruling-bytes
  for l in 'FROM: m-1.planner' 'TO: master.master-planner' 'PHASE: DESIGN' 'AUTHORITY: design-only'; do line1 "$R2" "$l" ruling-header; done
  has "$R2" 'MUST-2B-21 RULED — (A): the open-side staging directory is spelled `<target>.bvpk-open.partial/`' ruling-verdict
elif [ "$partial_suffix_relay" = "$relay" ]; then
  has "$R1" 'partial_suffix=.bvpk-open.partial' lock-relay-spelling
else STOP suffix-relay-unbound; fi                                                 # any other path is NOT an owner word
# --- the one product site (open.cpp:637 at B; untouched by 2b)
g=0; c1=$(grep -c -F -- "\"$partial_suffix\"" src/core/open/open.cpp) || g=$?; [ "$g" -le 1 ] && [ "$c1" -eq 1 ] || STOP "one-site-count-$c1"
g=0; c2=$(grep -c -E 'bvpk[-.]partial|bvpk-open\.partial' src/core/open/open.cpp) || g=$?; [ "$g" -le 1 ] && [ "$c2" -eq 1 ] || STOP "second-literal-count-$c2"
site=$(grep -n -F -- "\"$partial_suffix\"" src/core/open/open.cpp) || STOP site-read
r1sha=$(shasum -a 256 "$R1" | cut -d' ' -f1) || STOP r1-hash; r3sha=$(shasum -a 256 "$R3" | cut -d' ' -f1) || STOP r3-hash
printf 'mode=%s\nlock_id=%s doc_sha256=%s\nrelay=%s sha256=%s\nseal_relay=%s sha256=%s\npartial_suffix=%s partial_suffix_relay=%s\nsite=%s\ncount_literal=%s count_any_partial=%s\n' "$MODE" "$lock_id" "$doc_sha256" "$relay" "$r1sha" "$seal_relay" "$r3sha" "$partial_suffix" "$partial_suffix_relay" "$site" "$c1" "$c2" > "$EVID/code/c6b-partial-suffix.$MODE.txt" || STOP receipt
if [ "$MODE" = post ]; then
  [ -s "$EVID/code/c6b-partial-suffix.pre.txt" ] || STOP pre-receipt-absent
  cmp -s <(sed 1d "$EVID/code/c6b-partial-suffix.pre.txt") <(sed 1d "$EVID/code/c6b-partial-suffix.post.txt") || STOP pre-post-differ
fi
printf 'c6b-gate %s OK\n' "$MODE"
```
- [ ] **Step 1: the failing tests (A11.5, one case per leg, the git shim as the fault injector where a fixture cannot reach the kind)** — `tests/test_pack.cpp` / `tests/test_cli.cpp`: **(a)–(c)** the dirty / nested / submodule fixtures of Task 5 → `biv pack` exit 3, NO image, `error.kind` the wire kind, `error.path` and facts per A11.2 (`RepoNestedUnsupported`'s path = the nested child relpath; `RepoSubmoduleUnsupported`'s = the gitlink path), the sentence per A11.3 byte-golden, the exit-map row `transitional: true` (NAMED MUTANT ×3: exit 4, an image written, `InternalError`, or a byte moved ⇒ RED); **(d) UNMERGED** — three unmerged paths: exit 3, `facts.unmerged_count == "3"`, `facts.unmerged_paths` sorted-unique LF-joined, the sentence listing all three with NO "more" clause; a four-path variant lists three and "and 1 more" (NAMED MUTANT: the clause at N = 3, or an unsorted list ⇒ RED); **(e) REF UNCAPTURABLE** — the shim closes every route for one ref: exit 3, `facts.ref`, the sentence (NAMED MUTANT: the ref absent ⇒ RED); **(f) PROMISOR, BOTH ARMS** — the shim raises a missing-object failure on a promisor-flagged call: under `--offline` the sentence carries ", offline" and `facts.offline == "true"`; online "false" and no clause; exit 3 both (NAMED MUTANT: the arms swapped ⇒ RED); **(g) GIT FAILED, PACK** — the shim fails a pack-side call: exit 4, no image, the pack sentence with the op (NAMED MUTANT: exit 3 or an image ⇒ RED); `tests/test_open.cpp` / `tests/test_cli.cpp`: **(h) GIT FAILED / BUDGET, OPEN (A11 rev5)** — a two-repo fixture (the first restores, the second fails by the shim, then a budget variant) on a fresh target: exit 4, NO workspace at dest, `result` null, `error.kind` the wire kind, `facts.repo_id` / `facts.repo_relpath` / `facts.partial_path` naming the partial directory under the AUTHORIZED spelling (T-PARTIAL); the witness OPENS `<partial_path>/inventory.json` and finds the completed first row, the failing second row with `kind` + `detail` and the operation outcome, in order; `error.detail` == that row's `detail` byte-for-byte (NAMED MUTANT: a committed workspace, a non-null `result` beside `error`, a `repos` row anywhere in the envelope, `partial_path` absent, the inventory file absent or missing either row, or its `detail` differing from `error.detail` ⇒ RED); **(i) RESTORE FAILED** — the shim breaks a restore step: exit 4, `facts.engine_detail` the engine's `RepoRestoreFailed: <step>[: <detail>]` string, the sentence (NAMED MUTANT: the step absent ⇒ RED); **(j) OP ABSENT** — an engine error without an op fact renders "git call" (NAMED MUTANT: an empty op ⇒ RED); **(m) THE THREE CARRIERS (A11 rev4)** — a hostile engine detail carrying CR + U+202E and a lone `0x9b`: the HUMAN sentence carries A8-R1's escapes (the malformed byte as the scalar U+FFFD — on the stream EF BF BD, never the text `\uFFFD`); JSON `error.detail` = that rendered sentence decoded byte-for-byte (escape text for CR/U+202E; the U+FFFD glyph); JSON `facts.engine_detail` = the SEMANTIC string under A8-R2 decoding to the raw bytes exactly (a literal CR, a literal U+202E; the malformed byte visibly replaced) — three separate assertions (NAMED MUTANT: `error.detail` carrying a raw control, or `facts.engine_detail` carrying escape text ⇒ RED); **(k) UNKNOWN STAYS INTERNAL** — a synthetic `repo_engine_kind` outside the ten → `InternalError`, exit 4 (NAMED MUTANT: a typed row for an unknown kind ⇒ RED); **(l) COUNTS** — `tests/test_envelope.cpp`: ErrKind 36 (`to_string` round-trips every member), the exit map 38 rows, seven `transitional: true`, refusal/3 rows 20, mid-fail/4 rows 7, the InternalError row byte-identical (NAMED MUTANT: a count off by one ⇒ RED); `pytest harness/selftest/test_envelope.py` pins recomputed in this commit.
- [ ] **Step 2: run to verify failure** — compile error (the nine kinds undeclared); the sentence/exit cases fail on the c5 seam (`InternalError`, exit 4).
- [ ] **Step 3: the implementation, ONE commit (V-A11-4)** — `error.hpp`/`error.cpp`: the nine members appended after `UnclaimedGitEntry` in A11.1's order; `envelope.cpp` `exit_for_error`: the six refusal kinds join the exit-3 group, the three mid-fail kinds the exit-4 group; `pack.cpp` `engine_to_pack_error`: `switch (engine_error_kind(e))` over the nine (+ url_divergence_refused as before) → `BivError{<wire kind>, <path per A11.2>, {} /* detail filled at the CLI */, 0, <facts per A11.2 + repo_engine_kind kept>}`; default (unknown/absent) → UNCHANGED `InternalError`; `open.cpp`: an engine error from `restore_entry` that is NOT url_divergence_refused → the row becomes `failed` (kind = the wire kind, detail = the sentence) and the operation fails as failed-mid-apply (the existing §3 family byte; the partial confined on a fresh target); `url_consent.cpp` `render_engine_refusal_detail(kind, facts)` renders EXACTLY these sentences (A11.3, VERBATIM; `<op>` = `facts.op` or `call`; `[, offline]` iff `facts.offline == "true"`; `<N-3> more` iff N > 3):

```text
RepoDirtyUnsupported          pack refused: <repo> has uncommitted changes; this build captures clean repositories only. Commit or stash the changes, or declare the path in .bivignore, and re-run.
RepoNestedUnsupported         pack refused: <repo> contains a nested repository at <child>; this build captures single repositories only. Declare <child> in .bivignore, and re-run.
RepoSubmoduleUnsupported      pack refused: <repo> has a submodule at <gitlink>; this build captures repositories without submodules only. Declare <gitlink> in .bivignore, and re-run.
UnmergedIndexUnrepresentable  pack refused: <repo> has an unmerged index (<N> paths: <p0>[, <p1>[, <p2>]][ and <N-3> more]); an in-progress merge cannot be represented. Resolve or abort the merge and re-run.
RefUncapturable               pack refused: <repo> ref <ref> has neither a remote nor a bundle route; the image would lose it. Push or remove the ref and re-run.
PromisorObjectsUnavailable    pack refused: <repo> is a partial clone whose objects are unavailable (git <op> exit <exit_code>[, offline]); the image would be incomplete. Fetch the missing objects, or re-run without --offline, and re-run.
GitInvocationFailed   (pack)  pack failed: git <op> for <repo> did not complete (<engine detail>); no image was written.
GitInvocationFailed   (open)  open failed while restoring <repo>: git <op> did not complete (<engine detail>).
GitBudgetExpired      (pack)  pack failed: git <op> for <repo> exceeded the call budget; no image was written.
GitBudgetExpired      (open)  open failed while restoring <repo>: git <op> exceeded the call budget.
RepoRestoreFailed             open failed while restoring <repo>: <step>[: <detail>].
```

  `main.cpp`: the pack and open error paths fill `error.detail` from the renderer for the nine kinds (one string, two carriers — A9.3's binding shape; `error.path` and every facts value RAW through `machine_text` at emission); `PromisorObjectsUnavailable`'s `facts.offline` is set from `Command.offline` at the CLI; `schemas/biv-exit-map.v1.json`: nine rows appended after `UnclaimedGitEntry` in order — `{"kind": "RepoDirtyUnsupported", "class": "refusal", "exit": 3, "transitional": true}`, the same for Nested and Submodule, `{"kind": "UnmergedIndexUnrepresentable", "class": "refusal", "exit": 3}`, RefUncapturable, PromisorObjectsUnavailable likewise, `{"kind": "GitInvocationFailed", "class": "mid-fail", "exit": 4}` (the landed class word for the exit-4 family — copied from the existing rows, never coined), GitBudgetExpired, RepoRestoreFailed likewise (38 rows); `harness/selftest/test_envelope.py`'s exit-map blob pin recomputed in the same commit. The lock id and sha cited in the commit message.
- [ ] **Step 4: run to verify pass** — `ctest --preset ci-macos -E '^safety-hardening$'` rc 0; `pytest harness/selftest/test_envelope.py` rc 0; `python3 -c 'import json;print(len(json.load(open("schemas/biv-exit-map.v1.json"))["rows"]))'` == 38.
- [ ] **Step 5: commit (Step 0's gate re-run with `MODE=post` IMMEDIATELY before this block; the block refuses without its receipt)** —

```bash
[ -s "$EVID/code/c6b-partial-suffix.post.txt" ] && [ "$EVID/code/c6b-partial-suffix.post.txt" -nt "$EVID/code/c6b-partial-suffix.pre.txt" ] && [ "$(sed -n 1p "$EVID/code/c6b-partial-suffix.post.txt")" = mode=post ] || { echo 'STOP: run the Task 6b Step 0 gate with MODE=post immediately before this commit'; exit 1; }
git add src/core/support/error.hpp src/core/support/error.cpp src/core/report/envelope.cpp src/core/pack/pack.cpp src/core/open/open.cpp src/cli/url_consent.hpp src/cli/url_consent.cpp src/cli/main.cpp schemas/biv-exit-map.v1.json tests/test_envelope.cpp tests/test_pack.cpp tests/test_open.cpp tests/test_cli.cpp harness/selftest/test_envelope.py
git commit -m "report: the nine engine-error wire kinds (three transitional fence refusals/3; Unmerged/RefUncapturable/PromisorObjectsUnavailable refusal/3; GitInvocationFailed/GitBudgetExpired/RepoRestoreFailed mid-fail/4), whole-operation grain, A11.2 error objects, A11.3 sentences rendered once; open failed row + failed-mid-apply composition -- m-3 ADDENDUM 11 <lock id> @ <doc sha256>; m-1 074712 s3; ErrKind 27->36; exit map 29->38"
git rev-parse HEAD > "$EVID/commits.c6b.txt"
```

### Task 7 — c7, the product-scope witnesses: every deferred leg executed through the REAL CLI against `biv pack`-PRODUCED images (E1; master 041518's re-execution condition; m-1 §2; m-3 §1; FX-A6/A7/A8/M/N)

**Files:** Create `tests/test_wiring.cpp` (added to `biv_tests`), Modify `tests/cli_run.hpp` (fixture builders), `CMakeLists.txt` (source list).
**Fixtures (built by the tests in temp dirs; reality-shaped; no network egress — every remote is a local bare repo reached over `file://`):** `F-REMOTE` (bare `remote.git` + a working clone with one commit, one `.gitignore`d penumbra file and `origin` — CLEAN: ARM-1 REALITY, every packed fixture is committed; an untracked file is the dirty fence); `F-DIVERGE` (a second bare `effective.git` cloned from `remote.git`; the working repo's LOCAL config `url.file://…/effective.git.insteadOf file://…/remote.git` — same-context, M leg (h)); `F-RESTORE-DIVERGE` (the SAME rewrite in a temp `HOME/.gitconfig` handed to the child `biv open` process — the restore context has no repo yet); `F-TWO-REPOS` (two working repos with identical requested/effective addresses — a6·6); `F-NESTED` (a repo containing an untracked nested repo — §2.2 order, leaves-first); `F-SHALLOW` (`git clone --depth 1 file://…/remote.git` — N (a)); `F-PROMISOR-SHALLOW` (`git clone --filter=blob:none --depth 1` — N (g)); `F-GITLINK` (a `.git` regular file pointing at a gitdir — discover boundary); `F-UNCLAIMED` (`.git` symlink → `UnclaimedGitEntry`); `F-EQUIV` (rewrites within/without M-R2's equivalence set using `https://Host.invalid/…` ↔ `https://host.invalid/…/`, `http://…:80`, `ssh://…:22`, scp forms — the effective hosts are `.invalid` (RFC 2606, NXDOMAIN by definition) and `GIT_SSH_COMMAND=/usr/bin/false` is set for the child so no transport ever connects; the legs assert PROMPT/REFUSE vs SILENT and `remote_unreachable`/full, never timing). The request-trace instrument: BLOCK `git-shim.sh` installed FIRST on the child's `PATH` — it appends `argv` to `$BIV_GIT_TRACE` and `exec`s the real git; every leg that claims "zero git", "no spawn after DENY", or "no ls-remote" reads that log.

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
  - **a8·5** arm A: values carrying the TEN valid rows → `error.facts` / refusal rows / advisories entries round-trip the RAW bytes exactly (C0 via JSON `\u00xx` decoding back byte-exact; multi-byte scalars byte-exact) while the stderr carriers hold the display-encoded form; arm B1: the lone `0x9b` in requested / effective / repo (each in turn) → PROMPT D shows U+FFFD, the decision binds the RAW triple (a second encounter of the SAME raw triple is memo-answered — no second prompt), and on EVERY carrier the source×branch matrix names the serialized value is VALID UTF-8 with the malformed octet visibly REPLACED (U+FFFD) — never the raw `0x9b`, never a display escape (A8-R1's malformed-value arm; `machine_text`); arm B2: `0x9b` in `op`/`relpath`/`repo_id` → no consent claim, the same replacement oracle on the carriers the matrix names for those coordinates. NAMED MUTANT (both arms): invalid-UTF-8 JSON output ⇒ RED; a `\u{…}`/`\u00xx` display spelling inside a machine field ⇒ RED. **a8·6**: a verb-reachable hostile effective address carrying the ten valid rows at the pty → the transcript adds no line, moves no cursor, contains no raw ESC/format scalar; `y` binds the raw triple (memo witness as in B1).
  - **N (a) WHOLE**: F-SHALLOW → `biv pack` → the manifest row carries the full N-R2 cluster (`shallow{boundary}`, no `capture_mode`, no `eligibility`, no `local_refs`, no `bundle`) → `biv open` → `result.repos[0].outcome == "shallow-pointer"`, ZERO git lines in the shim log for that entry (the log is per-run: with only the shallow entry in the image, the whole open shows zero git); **E4 parity**: the same open with `--offline` → the row IDENTICAL (field-by-field) and zero git; receipt `E4-parity.txt`. **N (g)**: F-PROMISOR-SHALLOW → `biv pack` → `notes[]` carries `{"kind":"promisor-source"}`.
  - **RCPT-P (m-1 rev2 §1, the PACK receipt) + W-O1..3 at product scope**: F-MIXED (one born non-shallow repo with `origin` + F-SHALLOW + an unborn repo with a side ref + an empty unborn repo, all under one workspace) packed TWICE — with and without `--offline` — through the request-trace shim: under `--offline` the shim log has ZERO network-class lines (`ls-remote`/`fetch`) for the whole pack (receipt `RCPT-P-trace.txt`); the two manifests' `repos[]` differ ONLY in the born non-shallow row's `eligibility` + `capture_mode` + the derived `local_refs[].availability` members (receipt `RCPT-P-manifest-diff.txt`, the field-level diff); the shallow row (N-R2), the unborn-with-ref row (G) and the empty-unborn row (H) are byte-identical across the two packs (W-O1/W-O2/W-O3 receipts). A born non-shallow PROMISOR source under `--offline` → the engine's `promisor_objects_unavailable` surfaces as today's engine-error path (T-PROM); a SHALLOW promisor source under `--offline` → a pointer row with the promisor-source note, exit 0 (N's never-refuse).
  - **W-D1..4 at product scope (under ARM-1 REALITY)**: F-NESTED-BIV (`a/.git` + `a/.biv/r/.git`, both clean) → `biv pack` REFUSES with the nested fence naming `a/.biv/r` (at c5 the seam `repo-nested-unsupported`; after c6b `RepoNestedUnsupported`, `error.path == "a/.biv/r"`) and writes NO image — this IS W-D1's product form: the discovery correction makes the nested repository VISIBLE; NAMED MUTANT (the landed any-depth `.biv` skip): the pack SUCCEEDS with one row and the nested repository silently lost ⇒ RED; F-ROOT-BIV (`.biv/r/.git` at the workspace root beside a clean root repo) → ONE row, no refusal (W-D2: the reserved area is not walked); F-NESTED-BIV-IGNORED (the same tree with `.bivignore` = `a/.biv/`) → ONE row, the pack SUCCEEDS, and the pack-end prune summary NAMES `a/.biv` with its `.bivignore` source (W-D3's provenance half — the sealed §1.1 pack-end summary, the scanner's `PruneEntry`; the transitional posture's honest remedy, m-1 074712 §1 FLAG); W-D4: in the F-NESTED-BIV-IGNORED image the parent row's payload census (the archive member listing under `payload/`) holds NO `a/.biv/r/**` node — a negative-membership observation credited together with V-2b-5's single-writer legs and m-1's byte review (044559), never alone. The two-row nested image is T-ARM (ii), REGISTERED.
  - **pack discovery legs**: F-NESTED (a clean parent with a clean child repo) → the NESTED fence refuses (Q11; T-ARM (ii)/(iii) registered — no two-row image, no leaves-first observation at 2b); F-GITLINK → a boundary for discovery, then the SUBMODULE fence refuses at classify (Q11; A11 (c)) — the `.git` REGULAR FILE is never an unclaimed-entry refusal; F-UNCLAIMED → `UnclaimedGitEntry` exit 3, `reason == "symlink"`, detail golden, nothing written; a repo under a `.bivignore`d dir → NOT discovered, the prune-summary advisory names the dir; a workspace-root repo (`git init` at the workspace root + one tracked file + one IGNORED file (`.gitignore`d — an untracked file would be the dirty fence) + a subdirectory with tracked files) → the archive lists ZERO `payload/` members, the row's `relpath` is `.`, and `biv open` restores the repo at `<dest>` with the ignored file present (the engine's penumbra, not payload) — NAMED MUTANT: the root-claimed fast path removed → `payload/…` members appear in the archive ⇒ RED (the product discriminator for MUST-2B-12; V-2b-5).
  - **R-T** the round trip: F-REMOTE (CLEAN) with an IGNORED penumbra file + a local branch → `biv pack` → `biv open` → the restored repo's `git status --porcelain=v2` is EMPTY like the source's; HEAD/branch equal; the ignored penumbra file byte-equal; the local branch recreated (`local_refs[0].recreated == true`). (The dirty-worktree round trip is T-ARM (i), REGISTERED.)
  - **A11 legs at product scope (after c6b)**: A11.5 (a)–(l) re-executed through the REAL CLI — the dirty / nested / submodule / unmerged fixtures of Task 5 → exit 3, no image, the wire kind, path/facts, the byte-golden sentence, `transitional: true` where A11.1 says so; the shim-injected REF-UNCAPTURABLE, PROMISOR (both arms), GIT FAILED (pack), GIT FAILED / BUDGET (open, fresh target: no workspace, partial inventoried, the failed row with kind), RESTORE FAILED, OP ABSENT, UNKNOWN STAYS INTERNAL, COUNTS — receipts `A11-<leg>.txt`. Before c6b these fixtures assert the c5 seam (`InternalError` + `repo_engine_kind`, no image) and are re-asserted after it.
  - **A10 legs at product scope (after c4b)**: A10.4 (a)–(m) re-executed on product-packed images (a networked image = F-REMOTE packed ONLINE with an overlay-capture row, or a full row with a remote-proven local ref — the network-needing derivation recorded in `$EVID/code/network-needing-rows.txt`): notice before any git (shim tripwire); decline ⇒ offline-pointer rows exit 0; non-interactive no flag; `--network`; `--json` parity; `--offline` never; PROMPT D untouched after `y`; the rows; hostile URL bytes; (j) the born / unborn / detached idioms (T-STAGE, byte-exact) each run TWICE with the harness's git — into the non-empty target and into an absent scratch target, rc 0 ×6, the HEAD state per idiom as Task 4 Step 6 (j) states, with its two controls (a double-quoted operand, an unquoted one ⇒ RED); (k) the exact argv under the seven copy-safe hazards through the argv-recording stub (operands byte-equal to the raw values, no sentinel expansion); (l) the five non-copy-safe fallbacks (no command printed, the fallback line display-encoded, `bundle_path` present and JSON `reconstruct` ABSENT, the ordinary sibling row still printing); (m) the offline-unborn sha cell (`"(no commits)"` on the G row, `null` on the H row) + RCPT-Q (`<dest>/.biv/repos/<id>/repo.bundle` present with the checksum for every full row, absent for overlay rows, zero git) — receipts `A10-<leg>.txt`, `RCPT-Q.txt`.
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
- [ ] **Step 2: run the harness scenario row on macOS** — the ctest row `harness-e2` (harness/CMakeLists.txt:39-43: `bivharness` over `harness/scenarios`) at the c8 head: `ctest --preset ci-macos -R '^harness-e2$' --output-on-failure --output-junit "$EVID/receipts/harness-e2-macos.junit.xml"` rc 0; the two scenario ids (`d-git-restore`, the offline FXD-3 scenario) green in the runner's output (the implementer records the exact command, rc and the per-scenario lines to `$EVID/receipts/harness-scenarios-macos.txt`); the assertion classes touched (A/B/D/E/H/K; FXD-3) enumerated from the scenario files; the tolerance fixture's digest recorded. The LINUX half of the receipt is produced by Task 9's H0 container (`harness-e2` inside its ctest run, `$EVID/H/harness-e2-linux.txt`); BOTH halves at the same H0 are what m-3 §5 requires and what m-1's V-2b-8(iv) reads.
- [ ] **Step 3: record** — `git rev-parse HEAD > "$EVID/commits.c8.txt"`; `git status --porcelain` EMPTY. If m-3's patch adds or changes a `harness/selftest` test, the pytest COLLECTED POPULATION moves and Task 9's series branch runs — recorded here as `population_change_expected=yes|no` in `$EVID/receipts/harness-patch.txt` from `git apply --numstat`.

### Task 9 — the gates at H0, both platforms; the companion count-cell commit INSIDE the runner; the FINAL H written last (E2/E5 + closure; veto 9; the type-scoped RepoEntry census; the C-2 hunk; the A8 / predicate / hook censuses; the count gate; the Linux parity leg for H0 and B; the E3 Linux witness; the harness-e2 receipts; the harness-selftest bar or the 015244 series)

- [ ] **Step 0: the runner controls (must-be-NO for every guard this runner relies on)** — in subshells: `PIPEOK` on `false | cat` exits nonzero (`( set -o pipefail; false | cat; PIPEOK ctl ) 2>/dev/null; c1=$?; [ "$c1" -ne 0 ] || STOP`); a write into a read-only directory fails (`( printf x > "$EVID/work/ro/f" ) 2>/dev/null; c2=$?; [ "$c2" -ne 0 ] || STOP`); a producer that exits 1 after partial stdout is caught by the `x=$(cmd) || r=$?` form BEFORE its output is used (`r=0; x=$(printf 'partial\n'; exit 1) || r=$?; [ "$r" -eq 1 ] || STOP`). Each control's receipt to `$EVID/H/runner-controls.txt`.
- [ ] **Step 1: E2, E5 and the closure** — `H0=$(git rev-parse HEAD) || STOP`; the E2 census (`git grep -n -E 'repo::(discover|classify|run_eligibility|capture|restore_entry)\(' HEAD -- src ':!src/core/repo'`, non-empty); the E5 grep (the SAME pattern that was EMPTY at B) → its `file:line` site set equals E2's (`d=0; diff "$EVID/H/E2-sites.txt" "$EVID/H/E5-sites.txt" > "$EVID/H/E5-flip.txt" || d=$?; [ "$d" -eq 0 ] || STOP`); the closure: `invoke_git(` outside `src/core/repo` EMPTY and the spawn primitives EMPTY outside `src/core/repo`/`src/core/support`; the network-class census compared by CONTENT (path + source text, line numbers stripped — Task 1 shifts eligibility.cpp's lines) — `d=0; diff "$EVID/H/network-class-B.content" "$EVID/H/network-class-H0.content" > "$EVID/H/network-class.delta" || d=$?; [ "$d" -eq 0 ] || STOP`.
- [ ] **Step 2: veto 9; the type-scoped RepoEntry census; the C-2 hunk; the zero-byte fences; the fabric census; the A8 / predicate / hook censuses** — the commit walk (the first THREE commits engine-only at their exact path sets — c1a eligibility.{hpp,cpp}+test, c1b discover.cpp+test, c1c restore.{hpp,cpp}+test with restore.hpp's numstat `2 0` (fence rev3's bound); V-2b-5 rev2: the scan.cpp diff carries no `".biv"` line; no later engine path; no commit spans both sets); `c=0; python3 "$EVID/repoentry_census.py" src/cli src/core/pack src/core/scan src/core/open > "$EVID/H/repoentry-census.txt" || c=$?; printf 'repoentry_census_rc=%s\n' "$c" > "$EVID/H/repoentry-census.rc"; [ "$c" -eq 0 ] || STOP` (rc 0 = zero member writes on any RepoEntry-typed binding; its two controls re-run here on scratch copies); the C-2 hunk: the four lines from `auto manifest_json = manifest::serialize(manifest_model);` at H0 `cmp`-equal to a2f6fd1's; `git diff --stat "$B" HEAD -- src/core/manifest src/adapters harness/bivharness src/core/open/render.cpp` EMPTY; the eighteen-path fabric census recorded; the A8 census (every `facts.` occurrence inside `url_consent.cpp` on a line that also calls `consent_display(` — the line-level proxy; the per-occurrence census is m-3's review); `g=0; k=$(grep -c 'isatty(' src/cli/main.cpp) || g=$?; [ "$g" -eq 1 ] && [ "$k" -eq 0 ] || STOP` (one predicate); the hook install function's body carries no `json`, `offline` or `network` token.
- [ ] **Step 3: the macOS observation at H0** — build; the five `-r xml` producers → `tuples.py` → `H/tuples-macos.txt`; `cellgate.py "$EVID/B-cells.txt" macos "$EVID/H/tuples-macos.txt"` (rc 0 or 5 — MOVED rows are data); the skip set UNCHANGED (`q=0; python3 "$EVID/skipset.py" "$EVID/B-cells.txt" "$EVID/H/tuples-macos.txt" macos > "$EVID/H/skipset-macos.txt" || q=$?; [ "$q" -eq 0 ] || STOP`); the `harness-e2` row on macOS (`ctest --preset ci-macos -R '^harness-e2$'` rc 0 → `H/harness-e2-macos.rc`).
- [ ] **Step 4: the Linux parity leg for H0 and B; E3 Linux; harness-e2 Linux; the population rule** — the pinned clang-tidy-22 mirror assets (manifest from the workflow bytes; `gh release download`; sha256 verified); the container (`linux-container.sh`, Phases R/T/S) at H0 then at B; receipts (payload rc 0; the four phase rcs; the suite aggregate; nofile soft == hard); `tuples.py linux` for both; `cellgate.py … linux` (data) and the Linux skip set UNCHANGED (STOP otherwise); E3 from the H0 `biv_tests-linux.xml` (`[E3]`-tagged cases all successful); the `harness-e2` row status from the H0 ctest junit (`H/harness-e2-linux.txt`, must be passed); `selftest_summary.py` on both junits → the populations; EQUAL → the single-sample bar exactly as the R-4.49 plan computed it (`rcL`; the failed names ⊆ the r435 family; the base draw valid; `bar=pass-green|pass-r435-disclosed-registered-red` required — `case "$bar" in pass-green|pass-r435-disclosed-registered-red) :;; *) STOP;; esac`); NOT EQUAL → the 015244 interleaved series: N = 10 per tree, ALTERNATING B/H0, one fresh container per draw, every draw reduced by `selftest_summary.py`, then `series_verdict.py` (K-1 membership categorical → K-2 count ≥ 5 → K-3 shift = mean delta ≥ 1.0 OR complete separation; per-draw validity; per-test frequencies) → `VERDICT NOT-SHIFTED` required (`if [ "$p" -ne 0 ]; then [ "$(cat "$EVID/H/selftest-series.rc")" = series_rc=0 ] || STOP; fi`); the deselection arm is NOT pre-authorized for this candidate.
- [ ] **Step 5: the companion count-cell commit INSIDE the runner, then the FINAL H** — iff any `MOVED` row on either platform: `cellpatch.py "$EVID/B-workflow.yml" "$EVID/H/tuples-macos.txt" "$EVID/H/tuples-linux.txt" > .github/workflows/s2-harness.yml` (rewrites ONLY the moved `successes`/`skips` literals of the named binaries in the named target block — a changed skip set already STOPped above), `cells.py` on the result → `H/H-cells.txt`, `cellgate.py "$EVID/H/H-cells.txt" <target> <tuples>` rc 0 for BOTH targets, the c9 commit (`ci: pin case counts at H (macOS/Linux) -- m-3 count-cell companion`); else no commit and `H-cells.txt` = `B-cells.txt`; either way `[ "$(cat "$EVID/H/count-gate-final-macos.rc")" = count_gate_final_macos_rc=0 ] && [ "$(cat "$EVID/H/count-gate-final-linux.rc")" = count_gate_final_linux_rc=0 ] || STOP`. Then `H=$(git rev-parse HEAD) || STOP`; `d=0; git diff --stat "$H0" "$H" -- . ':!.github/workflows/s2-harness.yml' > "$EVID/H/H0-H.delta" || d=$?; [ "$d" -eq 0 ] && [ ! -s "$EVID/H/H0-H.delta" ] || STOP` (every H0 receipt carries to H); `count-gate-final-<target>.rc` = 0 both; `H.txt` written LAST; `H0.txt` beside it.
- [ ] **Step 6: the fence-proofs file** — `$EVID/H/fence-proofs.txt`: one `check=<name> rc=<n> expected=<n>` line per gate above, assembled from the receipts by printf (no inference).

<!-- RUN: task-9 -->
```bash
# Runner plumbing (Task 9)
set -o pipefail
PIPEOK() { local st=("${PIPESTATUS[@]}"); local k; for k in "${st[@]}"; do [ "$k" -eq 0 ] || { printf 'STOP-task-9 pipe=%s stage-status=%s line=%s\n' "$1" "${st[*]}" "${BASH_LINENO[0]}" >&2; exit 1; }; done; }
WORKTREE=/Users/jack/Programming/bivpak-intg-substep2b-wiring
MAIN=/Users/jack/Programming/bivpak
B=186adf7d67171bd7afe621f39b657a1a113ce299
cd "$WORKTREE" || STOP
v=0; (cd "$EVID" && shasum -a 256 -c helpers.sha256 > helpers.verify-9.txt 2>&1) || v=$?; [ "$v" -eq 0 ] || STOP
s=0; git status --porcelain > "$EVID/H/status-pre.txt" || s=$?; [ "$s" -eq 0 ] && [ ! -s "$EVID/H/status-pre.txt" ] || STOP
[ -s "$EVID/observer-unset-names.txt" ] && [ -s "$EVID/llvm-manifest.txt" ] && [ -s "$EVID/B/tuples-macos.txt" ] || STOP
# Step 0 — runner controls (each MUST fail)
( set -o pipefail; false | cat; PIPEOK ctl ) 2>/dev/null; c1=$?; [ "$c1" -ne 0 ] || STOP
m=0; mkdir -p "$EVID/work/ro" || m=$?; [ "$m" -eq 0 ] || STOP; chmod 0500 "$EVID/work/ro" || STOP
( printf x > "$EVID/work/ro/f" ) 2>/dev/null; c2=$?; [ "$c2" -ne 0 ] || STOP
chmod 0700 "$EVID/work/ro" || STOP
r=0; x=$(printf 'partial\n'; exit 1) || r=$?; [ "$r" -eq 1 ] || STOP
w=0; printf 'pipeok_control_rc=%s readonly_write_rc=%s partial_producer_rc=%s\n' "$c1" "$c2" "$r" > "$EVID/H/runner-controls.txt" || w=$?; [ "$w" -eq 0 ] && [ -s "$EVID/H/runner-controls.txt" ] || STOP
H0=$(git rev-parse HEAD) || STOP
printf 'H0=%s\n' "$H0" > "$EVID/H0.txt" || STOP
# Step 1 — E2 / E5 / closure / network class by content
g=0; git grep -n -E 'repo::(discover|classify|run_eligibility|capture|restore_entry)\(' HEAD -- src ':!src/core/repo' > "$EVID/H/E2-census.raw" || g=$?; [ "$g" -eq 0 ] && [ -s "$EVID/H/E2-census.raw" ] || STOP
s=0; sed 's/^HEAD://' "$EVID/H/E2-census.raw" > "$EVID/H/E2-census.txt" || s=$?; [ "$s" -eq 0 ] && [ -s "$EVID/H/E2-census.txt" ] || STOP
g=0; git grep -n -E 'run_eligibility|restore_entry|repo::discover|repo::classify|repo::capture' HEAD -- src ':!src/core/repo' > "$EVID/H/E5-grep.raw" || g=$?; [ "$g" -eq 0 ] || STOP
s=0; sed 's/^HEAD://' "$EVID/H/E5-grep.raw" > "$EVID/H/E5-grep.txt" || s=$?; [ "$s" -eq 0 ] || STOP
s=0; cut -d: -f1,2 "$EVID/H/E5-grep.txt" > "$EVID/work/E5-sites.unsorted" || s=$?; [ "$s" -eq 0 ] || STOP; s=0; LC_ALL=C sort -u "$EVID/work/E5-sites.unsorted" > "$EVID/H/E5-sites.txt" || s=$?; [ "$s" -eq 0 ] || STOP
s=0; cut -d: -f1,2 "$EVID/H/E2-census.txt" > "$EVID/work/E2-sites.unsorted" || s=$?; [ "$s" -eq 0 ] || STOP; s=0; LC_ALL=C sort -u "$EVID/work/E2-sites.unsorted" > "$EVID/H/E2-sites.txt" || s=$?; [ "$s" -eq 0 ] || STOP
d=0; diff "$EVID/H/E2-sites.txt" "$EVID/H/E5-sites.txt" > "$EVID/H/E5-flip.txt" || d=$?; [ "$d" -eq 0 ] || STOP
g=0; git grep -n -E 'invoke_git\(' HEAD -- src ':!src/core/repo' > "$EVID/H/closure-invoke-git.txt" || g=$?; [ "$g" -eq 1 ] && [ ! -s "$EVID/H/closure-invoke-git.txt" ] || STOP
g=0; git grep -n -E 'posix_spawn|execv|popen|std::system|fork\(' HEAD -- src ':!src/core/repo' ':!src/core/support' > "$EVID/H/S1-nospawn.txt" || g=$?; [ "$g" -eq 1 ] && [ ! -s "$EVID/H/S1-nospawn.txt" ] || STOP
g=0; git grep -n 'GitCallClass::network' HEAD -- src > "$EVID/work/nc-H0.raw" || g=$?; [ "$g" -eq 0 ] || STOP; s=0; sed -E 's/^HEAD:([^:]+):[0-9]+:/\1: /' "$EVID/work/nc-H0.raw" > "$EVID/work/nc-H0.unsorted" || s=$?; [ "$s" -eq 0 ] || STOP; s=0; LC_ALL=C sort "$EVID/work/nc-H0.unsorted" > "$EVID/H/network-class-H0.content" || s=$?; [ "$s" -eq 0 ] || STOP
g=0; git grep -n 'GitCallClass::network' "$B" -- src > "$EVID/work/nc-B.raw" || g=$?; [ "$g" -eq 0 ] || STOP; s=0; sed -E "s/^${B}:([^:]+):[0-9]+:/\1: /" "$EVID/work/nc-B.raw" > "$EVID/work/nc-B.unsorted" || s=$?; [ "$s" -eq 0 ] || STOP; s=0; LC_ALL=C sort "$EVID/work/nc-B.unsorted" > "$EVID/H/network-class-B.content" || s=$?; [ "$s" -eq 0 ] || STOP
d=0; diff "$EVID/H/network-class-B.content" "$EVID/H/network-class-H0.content" > "$EVID/H/network-class.delta" || d=$?; [ "$d" -eq 0 ] || STOP
a=0; nnc=$(awk 'END { print NR }' "$EVID/H/network-class-H0.content") || a=$?; [ "$a" -eq 0 ] && [ "$nnc" -eq 6 ] || STOP
# Step 2 — veto 9; RepoEntry census (type-scoped) + controls; C-2 hunk; zero-byte fences; fabric census; A8 / predicate / hook censuses
: > "$EVID/H/veto9.txt"; k=0
for c in $(git log --reverse --format=%H "$B..HEAD"); do
  git diff-tree --no-commit-id --name-only -r "$c" > "$EVID/work/paths-$c.txt" || STOP
  e=0; ne=$(grep -c -E '^src/core/repo/' "$EVID/work/paths-$c.txt") || e=$?; [ "$e" -le 1 ] || STOP
  s=0; ns=$(grep -c -E '^(src/cli|src/core/pack|src/core/scan|src/core/open)/' "$EVID/work/paths-$c.txt") || s=$?; [ "$s" -le 1 ] || STOP
  k=$((k+1))
  if [ "$k" -eq 1 ]; then [ "$ne" -ge 1 ] && [ "$ns" -eq 0 ] || STOP; o=0; grep -v -E '^(src/core/repo/eligibility\.(hpp|cpp)|tests/test_repo_engine\.cpp)$' "$EVID/work/paths-$c.txt" > "$EVID/work/paths-$c.other" || o=$?; [ "$o" -eq 1 ] && [ ! -s "$EVID/work/paths-$c.other" ] || STOP; elif [ "$k" -eq 2 ]; then [ "$ne" -ge 1 ] && [ "$ns" -eq 0 ] || STOP; o=0; grep -v -E '^(src/core/repo/discover\.cpp|tests/test_repo_engine\.cpp)$' "$EVID/work/paths-$c.txt" > "$EVID/work/paths-$c.other" || o=$?; [ "$o" -eq 1 ] && [ ! -s "$EVID/work/paths-$c.other" ] || STOP; elif [ "$k" -eq 3 ]; then [ "$ne" -ge 1 ] && [ "$ns" -eq 0 ] || STOP; o=0; grep -v -E '^(src/core/repo/restore\.(hpp|cpp)|tests/test_repo_engine\.cpp)$' "$EVID/work/paths-$c.txt" > "$EVID/work/paths-$c.other" || o=$?; [ "$o" -eq 1 ] && [ ! -s "$EVID/work/paths-$c.other" ] || STOP; else [ "$ne" -eq 0 ] || STOP; fi
  [ "$ne" -eq 0 ] || [ "$ns" -eq 0 ] || STOP
  printf '%s engine=%s callsite=%s\n' "$c" "$ne" "$ns" >> "$EVID/H/veto9.txt"
done
[ -s "$EVID/H/veto9.txt" ] || STOP
a=0; nk=$(awk 'END { print NR }' "$EVID/H/veto9.txt") || a=$?; [ "$a" -eq 0 ] && [ "$nk" -ge 3 ] || STOP
r=0; git diff --numstat "$B" HEAD -- src/core/repo/restore.hpp > "$EVID/H/restore-hpp.numstat" || r=$?; [ "$r" -eq 0 ] || STOP; n=0; nh=$(awk '{ print $1 " " $2 }' "$EVID/H/restore-hpp.numstat") || n=$?; [ "$n" -eq 0 ] && [ "$nh" = "2 0" ] || STOP
b=0; git diff "$B" HEAD -- src/core/scan/scan.cpp > "$EVID/H/scan-diff.txt" || b=$?; [ "$b" -le 1 ] || STOP; n=0; nb=$(grep -c -F -- '".biv"' "$EVID/H/scan-diff.txt") || n=$?; [ "$n" -le 1 ] && [ "$nb" -eq 0 ] || STOP
c=0; python3 "$EVID/repoentry_census.py" src/cli src/core/pack src/core/scan src/core/open > "$EVID/H/repoentry-census.txt" || c=$?; printf 'repoentry_census_rc=%s\n' "$c" > "$EVID/H/repoentry-census.rc"; [ "$c" -eq 0 ] || STOP
m=0; rm -rf "$EVID/work/rc-mutant" "$EVID/work/rc-control" && mkdir -p "$EVID/work/rc-mutant" "$EVID/work/rc-control" && cp -R src/core/pack "$EVID/work/rc-mutant/" && cp -R src/core/pack "$EVID/work/rc-control/" || m=$?; [ "$m" -eq 0 ] || STOP
printf '\nvoid __census_mutant(std::vector<biv::repo::RepoEntry>& entries) { entries[0].sha = "x"; }\n' >> "$EVID/work/rc-mutant/pack/pack.cpp" || STOP
printf '\nvoid __census_control(biv::pack::Warning& warning) { warning.path = "x"; }\n' >> "$EVID/work/rc-control/pack/pack.cpp" || STOP
c=0; python3 "$EVID/repoentry_census.py" "$EVID/work/rc-mutant/pack" > "$EVID/H/repoentry-census-mutant.txt" || c=$?; [ "$c" -eq 5 ] || STOP
c=0; python3 "$EVID/repoentry_census.py" "$EVID/work/rc-control/pack" > "$EVID/H/repoentry-census-control.txt" || c=$?; [ "$c" -eq 0 ] || STOP
printf 'mutant_rc=5 control_rc=0\n' > "$EVID/H/repoentry-census-controls.txt"
s=0; git show a2f6fd1:src/core/pack/pack.cpp > "$EVID/work/pack-a2f6fd1.cpp" || s=$?; [ "$s" -eq 0 ] || STOP; g=0; grep -n -A3 'auto manifest_json = manifest::serialize(manifest_model);' "$EVID/work/pack-a2f6fd1.cpp" > "$EVID/work/c2-a2f.hunk" || g=$?; [ "$g" -eq 0 ] && [ -s "$EVID/work/c2-a2f.hunk" ] || STOP
g=0; grep -n -A3 'auto manifest_json = manifest::serialize(manifest_model);' src/core/pack/pack.cpp > "$EVID/work/c2-H0.hunk" || g=$?; [ "$g" -eq 0 ] && [ -s "$EVID/work/c2-H0.hunk" ] || STOP
s=0; sed -E 's/^[0-9]+[:-]//' "$EVID/work/c2-a2f.hunk" > "$EVID/H/c2-a2f.text" || s=$?; [ "$s" -eq 0 ] || STOP; s=0; sed -E 's/^[0-9]+[:-]//' "$EVID/work/c2-H0.hunk" > "$EVID/H/c2-H0.text" || s=$?; [ "$s" -eq 0 ] || STOP
c=0; cmp "$EVID/H/c2-a2f.text" "$EVID/H/c2-H0.text" > "$EVID/H/c2-hunk.cmp" 2>&1 || c=$?; [ "$c" -eq 0 ] || STOP
z=0; git diff --stat "$B" HEAD -- src/core/manifest src/adapters harness/bivharness src/core/open/render.cpp > "$EVID/H/zero-byte-fences.txt" || z=$?; [ "$z" -eq 0 ] && [ ! -s "$EVID/H/zero-byte-fences.txt" ] || STOP
n=0; git diff --numstat 3cd31e4 HEAD -- CMakeLists.txt harness/selftest/test_envelope.py schemas/biv-exit-map.v1.json schemas/biv-json-envelope.v1.schema.json src/cli/args.cpp src/cli/args.hpp src/cli/main.cpp src/cli/url_consent.cpp src/cli/url_consent.hpp src/core/open/open.hpp src/core/pack/pack.hpp src/core/report/envelope.cpp src/core/report/envelope.hpp src/core/support/error.cpp src/core/support/error.hpp src/core/support/url_divergence.hpp tests/test_cli.cpp tests/test_envelope.cpp > "$EVID/H/fabric-census-3cd31e4-H0.txt" || n=$?; [ "$n" -eq 0 ] || STOP
g=0; grep -n -E 'facts\.(op|repo|requested|effective)' src/cli/url_consent.cpp > "$EVID/H/a8-facts-lines.txt" || g=$?; [ "$g" -eq 0 ] && [ -s "$EVID/H/a8-facts-lines.txt" ] || STOP
g=0; k=$(grep -c -v 'consent_display(' "$EVID/H/a8-facts-lines.txt") || g=$?; [ "$g" -le 1 ] && [ "$k" -eq 0 ] || STOP
g=0; k=$(grep -c 'isatty(' src/cli/main.cpp) || g=$?; [ "$g" -eq 1 ] && [ "$k" -eq 0 ] || STOP
s=0; sed -n '/install_url_divergence_hook(const biv::cli::Command/,/return consent;/p' src/cli/main.cpp > "$EVID/H/hook-install-body.txt" || s=$?; [ "$s" -eq 0 ] && [ -s "$EVID/H/hook-install-body.txt" ] || STOP
g=0; k=$(grep -c -i -E 'json|offline|network' "$EVID/H/hook-install-body.txt") || g=$?; [ "$g" -eq 1 ] && [ "$k" -eq 0 ] || STOP
# Step 3 — macOS observation at H0
b=0; cmake --build --preset ci-macos > "$EVID/H/build-H0.log" 2>&1 || b=$?; [ "$b" -eq 0 ] || STOP
for binary in biv_subprocess_tests biv_repo_git_tests biv_repo_engine_tests biv_tests biv_probe_tests; do x=0; "./build/ci-macos/$binary" -r xml > "$EVID/H/$binary-macos.xml" 2> "$EVID/H/$binary-macos.stderr" || x=$?; printf '%s rc=%s\n' "$binary" "$x" >> "$EVID/H/run-rcs-macos.txt"; [ -s "$EVID/H/$binary-macos.xml" ] || STOP; done
u=0; python3 "$EVID/tuples.py" macos "$EVID"/H/biv_subprocess_tests-macos.xml "$EVID"/H/biv_repo_git_tests-macos.xml "$EVID"/H/biv_repo_engine_tests-macos.xml "$EVID"/H/biv_tests-macos.xml "$EVID"/H/biv_probe_tests-macos.xml > "$EVID/H/tuples-macos.txt" || u=$?; [ "$u" -eq 0 ] && [ -s "$EVID/H/tuples-macos.txt" ] || STOP
c=0; python3 "$EVID/cellgate.py" "$EVID/B-cells.txt" macos "$EVID/H/tuples-macos.txt" > "$EVID/H/count-gate-macos.txt" 2>&1 || c=$?; printf 'count_gate_macos_rc=%s\n' "$c" > "$EVID/H/count-gate-macos.rc"; [ "$c" -eq 0 ] || [ "$c" -eq 5 ] || STOP
q=0; python3 "$EVID/skipset.py" "$EVID/B-cells.txt" "$EVID/H/tuples-macos.txt" macos > "$EVID/H/skipset-macos.txt" || q=$?; [ "$q" -eq 0 ] || STOP
e=0; ctest --preset ci-macos -R '^harness-e2$' --output-on-failure > "$EVID/H/harness-e2-macos.log" 2>&1 || e=$?; printf 'harness_e2_macos_rc=%s\n' "$e" > "$EVID/H/harness-e2-macos.rc"; [ "$e" -eq 0 ] || STOP
# Step 4 — the Linux parity leg: assets, then the container at H0 and at B
LLVM_RAW=$(mktemp -d "$EVID/llvm22-assets-H.XXXXXX") || STOP; LLVM_DIR=$(cd "$LLVM_RAW" && pwd -P) || STOP; c=0; cp "$EVID/llvm-manifest.txt" "$LLVM_DIR/MANIFEST" || c=$?; [ "$c" -eq 0 ] || STOP
h=0; while read -r _ package asset; do gh release download toolchain-mirror-clang-tidy-22-immutable-v1 --repo iwnlcern/bivpak --pattern "$asset" --dir "$LLVM_DIR" || h=$?; done < "$LLVM_DIR/MANIFEST" > "$EVID/H/llvm-transport.log" 2>&1
a=0; awk '{ print $1 "  " $3 }' "$LLVM_DIR/MANIFEST" > "$LLVM_DIR/SHA256SUMS" || a=$?; [ "$a" -eq 0 ] && [ -s "$LLVM_DIR/SHA256SUMS" ] || STOP; v=0; (cd "$LLVM_DIR" && shasum -a 256 -c SHA256SUMS) > "$EVID/H/llvm-verify.txt" 2>&1 || v=$?; printf 'llvm_transport_rc=%s verify_rc=%s\n' "$h" "$v" > "$EVID/H/llvm.rc"; [ "$h" -eq 0 ] && [ "$v" -eq 0 ] || STOP
for LABEL in H B; do
  if [ "$LABEL" = H ]; then EXP=$H0; else EXP=$B; fi
  o=0; docker run --rm --platform linux/amd64 --init -v "${LLVM_DIR}:/llvm-mirror:ro" -v "${MAIN}:/repo-ro:ro" -v "${EVID}:/evidence" ubuntu:24.04 bash /evidence/linux-container.sh "$EXP" "$LABEL" > "$EVID/$LABEL/linux-container.log" 2>&1 || o=$?; printf '%s\n' "$o" > "$EVID/$LABEL/linux-container.rc"; [ "$o" -eq 0 ] || STOP
  for f in linux-ledger.txt linux-suite-ledger.txt linux-nofile.txt linux-run-head-receipt.txt container-payload.rc "ctest-linux-$LABEL.log" "ctest-linux-$LABEL.rc" "ctest-linux-$LABEL.junit.xml" biv_subprocess_tests-linux.xml biv_repo_git_tests-linux.xml biv_repo_engine_tests-linux.xml biv_tests-linux.xml biv_probe_tests-linux.xml; do [ -s "$EVID/$LABEL/$f" ] || STOP; done
  [ "$(cat "$EVID/$LABEL/container-payload.rc")" = container_payload_rc=0 ] || STOP
  for x in phase_R_base_provision_rc=0 phase_R_asset_provision_rc=0 phase_T_transition_fixture_rc=0 phase_S_suite_rc=0; do g=0; k=$(grep -c -x -F -- "$x" "$EVID/$LABEL/linux-ledger.txt") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP; done
  g=0; k=$(grep -c -x -F 'suite_aggregate_rc=0 ledger_write_failed=0' "$EVID/$LABEL/linux-suite-ledger.txt") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP
  g=0; k=$(grep -c -E '^nofile_soft_equals_hard_rc=0$' "$EVID/$LABEL/linux-suite-ledger.txt") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP
  u=0; python3 "$EVID/tuples.py" linux "$EVID"/$LABEL/biv_subprocess_tests-linux.xml "$EVID"/$LABEL/biv_repo_git_tests-linux.xml "$EVID"/$LABEL/biv_repo_engine_tests-linux.xml "$EVID"/$LABEL/biv_tests-linux.xml "$EVID"/$LABEL/biv_probe_tests-linux.xml > "$EVID/$LABEL/tuples-linux.txt" || u=$?; [ "$u" -eq 0 ] && [ -s "$EVID/$LABEL/tuples-linux.txt" ] || STOP
  x=0; python3 "$EVID/selftest_summary.py" "$EVID/$LABEL/ctest-linux-$LABEL.junit.xml" "$EVID/$LABEL/selftest-$LABEL" > "$EVID/$LABEL/selftest-$LABEL.out" || x=$?; [ "$x" -eq 0 ] && [ -s "$EVID/$LABEL/selftest-$LABEL.kv" ] || STOP
  c=0; cat -- "$EVID/$LABEL/linux-container.log" "$EVID/$LABEL/phase-R-base.log" "$EVID/$LABEL/phase-R-assets.log" "$EVID/$LABEL/phase-T-transition.log" "$EVID/$LABEL/phase-S-suite.log" "$EVID/$LABEL/ctest-linux-$LABEL.log" "$EVID"/$LABEL/*-linux.stderr > "$EVID/$LABEL/all-logs-linux.txt" || c=$?; [ "$c" -eq 0 ] || STOP
  g=0; hits=$(grep -c -E 'sk-[A-Za-z0-9]{8,}|-----BEGIN [A-Z ]*PRIVATE KEY|AKIA[0-9A-Z]{16}|ghp_[A-Za-z0-9]{20,}|xox[abprs]-' "$EVID/$LABEL/all-logs-linux.txt") || g=$?; [ "$g" -le 1 ] && [ "$hits" -eq 0 ] || STOP
done
c=0; python3 "$EVID/cellgate.py" "$EVID/B-cells.txt" linux "$EVID/H/tuples-linux.txt" > "$EVID/H/count-gate-linux.txt" 2>&1 || c=$?; printf 'count_gate_linux_rc=%s\n' "$c" > "$EVID/H/count-gate-linux.rc"; [ "$c" -eq 0 ] || [ "$c" -eq 5 ] || STOP
q=0; python3 "$EVID/skipset.py" "$EVID/B-cells.txt" "$EVID/H/tuples-linux.txt" linux > "$EVID/H/skipset-linux.txt" || q=$?; [ "$q" -eq 0 ] || STOP
c=0; python3 "$EVID/cellgate.py" "$EVID/B-cells.txt" linux "$EVID/B/tuples-linux.txt" > "$EVID/B/count-gate-linux.txt" 2>&1 || c=$?; [ "$c" -eq 0 ] || STOP
c=0; python3 "$EVID/cellgate.py" "$EVID/B-cells.txt" macos "$EVID/B/tuples-macos.txt" > "$EVID/B/count-gate-macos.txt" 2>&1 || c=$?; [ "$c" -eq 0 ] || STOP
x=0; python3 "$EVID/xmlcases.py" e3 "$EVID/H/biv_tests-linux.xml" > "$EVID/H/E3-linux.txt" || x=$?; printf 'e3_linux_rc=%s\n' "$x" > "$EVID/H/E3-linux.rc"; [ "$x" -eq 0 ] || STOP
x=0; python3 "$EVID/xmlcases.py" ctest-row harness-e2 "$EVID/H/ctest-linux-H.junit.xml" > "$EVID/H/harness-e2-linux.txt" || x=$?; printf 'harness_e2_linux_rc=%s\n' "$x" > "$EVID/H/harness-e2-linux.rc"; [ "$x" -eq 0 ] || STOP
s=0; sed -n 's/^population=//p' "$EVID/B/selftest-B.kv" > "$EVID/H/selftest-population-B.txt" || s=$?; [ "$s" -eq 0 ] && [ -s "$EVID/H/selftest-population-B.txt" ] || STOP
s=0; sed -n 's/^population=//p' "$EVID/H/selftest-H.kv" > "$EVID/H/selftest-population-H.txt" || s=$?; [ "$s" -eq 0 ] && [ -s "$EVID/H/selftest-population-H.txt" ] || STOP
p=0; cmp "$EVID/H/selftest-population-B.txt" "$EVID/H/selftest-population-H.txt" > "$EVID/H/selftest-population.cmp" 2>&1 || p=$?; printf 'population_equal_rc=%s\n' "$p" > "$EVID/H/selftest-population.rc"
printf 'selftest/test_e3_asserts.py::test_file_reader_rejects_same_size_cross_chunk_in_place_rewrite\nselftest/test_e3_asserts.py::test_c1_zero_session_control_reds_on_file_inserted_at_scandir_stop\nselftest/test_e3_asserts.py::test_credential_scanner_detects_entry_added_after_directory_enumeration\nselftest/test_e3_asserts.py::test_run_e3_session_inserted_at_scandir_stop_reds_c1_before_open\n' > "$EVID/H/r435-family.txt"
if [ "$p" -eq 0 ]; then
  rcL=$(cat "$EVID/H/ctest-linux-H.rc"); [ -n "$rcL" ] || STOP; rcB=$(cat "$EVID/B/ctest-linux-B.rc"); [ -n "$rcB" ] || STOP
  hsum=$(sed -n 's/^summary=//p' "$EVID/H/selftest-H.kv"); nfail=$(sed -n 's/^failed=//p' "$EVID/H/selftest-H.kv"); nf=$(sed -n 's/^names_count=//p' "$EVID/H/selftest-H.kv"); [ -n "$hsum" ] && [ -n "$nfail" ] && [ -n "$nf" ] || STOP
  bsum=$(sed -n 's/^summary=//p' "$EVID/B/selftest-B.kv"); nbfail=$(sed -n 's/^failed=//p' "$EVID/B/selftest-B.kv"); nb=$(sed -n 's/^names_count=//p' "$EVID/B/selftest-B.kv"); [ -n "$bsum" ] && [ -n "$nbfail" ] && [ -n "$nb" ] || STOP
  o=0; grep -v -x -F -f "$EVID/H/r435-family.txt" "$EVID/H/selftest-H.names" > "$EVID/H/linux-selftest-foreign.names" || o=$?; [ "$o" -le 1 ] || STOP
  o=0; grep -v -x -F -f "$EVID/H/r435-family.txt" "$EVID/B/selftest-B.names" > "$EVID/B/base-foreign.names" || o=$?; [ "$o" -le 1 ] || STOP
  f=0; grep -E '^[[:space:]]+[0-9]+ - .*\(Failed\)' "$EVID/H/ctest-linux-H.log" > "$EVID/H/ctest-linux-H.failed" || f=$?; [ "$f" -le 1 ] || STOP; s=0; sed -E 's/^[[:space:]]*[0-9]+ - ([^ ]+) .*/\1/' "$EVID/H/ctest-linux-H.failed" > "$EVID/H/ctest-linux-H.failed-names" || s=$?; [ "$s" -eq 0 ] || STOP
  printf 'harness-selftest\n' > "$EVID/work/ctest-failed.expected"; d=0; diff "$EVID/work/ctest-failed.expected" "$EVID/H/ctest-linux-H.failed-names" > "$EVID/H/ctest-linux-H.failed.delta" || d=$?; [ "$d" -le 1 ] || STOP
  bar=fail; if [ "$rcL" -eq 0 ]; then bar=pass-green; elif [ "$rcL" -ne 8 ] || [ "$d" -ne 0 ]; then bar=fail-not-the-one-row; elif [ "$hsum" != parsed ] || [ "$nf" -lt 1 ] || [ "$nf" -ne "$nfail" ]; then bar=stop-invalid-candidate-result; elif [ "$nf" -ge 5 ] || [ -s "$EVID/H/linux-selftest-foreign.names" ]; then bar=stop-fresh-finding-K1-K2-up-to-m3-m4; elif { [ "$rcB" -ne 0 ] && [ "$rcB" -ne 8 ]; } || [ "$bsum" != parsed ] || [ "$nb" -ne "$nbfail" ]; then bar=stop-invalid-base-draw; elif [ "$nb" -eq 0 ]; then bar=stop-inconclusive-base-green-arm-ii-required; elif [ "$nb" -ge 5 ] || [ -s "$EVID/B/base-foreign.names" ]; then bar=stop-fresh-finding-base-outside-family; else bar=pass-r435-disclosed-registered-red; fi
  printf 'rcL=%s rcB=%s summary_H=%s failed_H=%s names_H=%s summary_B=%s failed_B=%s names_B=%s bar=%s\n' "$rcL" "$rcB" "$hsum" "$nfail" "$nf" "$bsum" "$nbfail" "$nb" "$bar" > "$EVID/H/linux-selftest-bar.txt"
  case "$bar" in pass-green|pass-r435-disclosed-registered-red) :;; *) STOP;; esac
else
  m=0; mkdir -p "$EVID/series" || m=$?; [ "$m" -eq 0 ] || STOP
  for i in 1 2 3 4 5 6 7 8 9 10; do
    for T in B H; do
      LABEL="$T-$i"; if [ "$T" = H ]; then EXP=$H0; else EXP=$B; fi
      m=0; mkdir -p "$EVID/series/$LABEL" || m=$?; [ "$m" -eq 0 ] || STOP
      o=0; docker run --rm --platform linux/amd64 --init -v "${LLVM_DIR}:/llvm-mirror:ro" -v "${MAIN}:/repo-ro:ro" -v "${EVID}/series:/evidence" -v "${EVID}/linux-container.sh:/evidence/linux-container.sh:ro" -v "${EVID}/linux-suite.sh:/evidence/linux-suite.sh:ro" -v "${EVID}/observer-unset-names.txt:/evidence/observer-unset-names.txt:ro" ubuntu:24.04 bash /evidence/linux-container.sh "$EXP" "$LABEL" > "$EVID/series/$LABEL/linux-container.log" 2>&1 || o=$?; printf '%s\n' "$o" > "$EVID/series/$LABEL/linux-container.rc"; [ "$o" -eq 0 ] || STOP
      x=0; python3 "$EVID/selftest_summary.py" "$EVID/series/$LABEL/ctest-linux-$LABEL.junit.xml" "$EVID/series/$LABEL/selftest-$LABEL" > "$EVID/series/$LABEL/selftest-$LABEL.out" || x=$?; [ "$x" -eq 0 ] || STOP
    done
  done
  s=0; python3 "$EVID/series_verdict.py" "$EVID/series" "$EVID/H/r435-family.txt" 10 > "$EVID/H/selftest-series.txt" 2>&1 || s=$?; printf 'series_rc=%s\n' "$s" > "$EVID/H/selftest-series.rc"
fi
if [ "$p" -ne 0 ]; then [ "$(cat "$EVID/H/selftest-series.rc")" = series_rc=0 ] || STOP; fi
# Step 5 — the companion count-cell commit INSIDE the runner; the FINAL H last
mv=0; grep -q -E '^MOVED' "$EVID/H/count-gate-macos.txt" "$EVID/H/count-gate-linux.txt" || mv=$?
if [ "$mv" -eq 0 ]; then
  p=0; python3 "$EVID/cellpatch.py" "$EVID/B-workflow.yml" "$EVID/H/tuples-macos.txt" "$EVID/H/tuples-linux.txt" > "$EVID/work/s2-harness.patched.yml" || p=$?; [ "$p" -eq 0 ] && [ -s "$EVID/work/s2-harness.patched.yml" ] || STOP
  c=0; cp "$EVID/work/s2-harness.patched.yml" .github/workflows/s2-harness.yml || c=$?; [ "$c" -eq 0 ] || STOP
  c=0; python3 "$EVID/cells.py" .github/workflows/s2-harness.yml > "$EVID/H/H-cells.txt" || c=$?; [ "$c" -eq 0 ] && [ -s "$EVID/H/H-cells.txt" ] || STOP
  c=0; python3 "$EVID/cellgate.py" "$EVID/H/H-cells.txt" macos "$EVID/H/tuples-macos.txt" > "$EVID/H/count-gate-final-macos.txt" 2>&1 || c=$?; printf 'count_gate_final_macos_rc=%s\n' "$c" > "$EVID/H/count-gate-final-macos.rc"; [ "$c" -eq 0 ] || STOP
  c=0; python3 "$EVID/cellgate.py" "$EVID/H/H-cells.txt" linux "$EVID/H/tuples-linux.txt" > "$EVID/H/count-gate-final-linux.txt" 2>&1 || c=$?; printf 'count_gate_final_linux_rc=%s\n' "$c" > "$EVID/H/count-gate-final-linux.rc"; [ "$c" -eq 0 ] || STOP
  g=0; git add .github/workflows/s2-harness.yml && git commit -q -m "ci: pin case counts at H (macOS/Linux) -- m-3 count-cell companion" || g=$?; [ "$g" -eq 0 ] || STOP
  git rev-parse HEAD > "$EVID/commits.c9.txt" || STOP; printf 'count-cells-moved: c9 committed\n' > "$EVID/H/count-gate.txt"
else
  c=0; cp "$EVID/B-cells.txt" "$EVID/H/H-cells.txt" || c=$?; [ "$c" -eq 0 ] || STOP
  printf 'unchanged\n' > "$EVID/H/count-gate.txt"; printf 'count_gate_final_macos_rc=0\n' > "$EVID/H/count-gate-final-macos.rc"; printf 'count_gate_final_linux_rc=0\n' > "$EVID/H/count-gate-final-linux.rc"
fi
[ "$(cat "$EVID/H/count-gate-final-macos.rc")" = count_gate_final_macos_rc=0 ] && [ "$(cat "$EVID/H/count-gate-final-linux.rc")" = count_gate_final_linux_rc=0 ] || STOP
H=$(git rev-parse HEAD) || STOP
d=0; git diff --stat "$H0" "$H" -- . ':!.github/workflows/s2-harness.yml' > "$EVID/H/H0-H.delta" || d=$?; [ "$d" -eq 0 ] && [ ! -s "$EVID/H/H0-H.delta" ] || STOP
s=0; git status --porcelain > "$EVID/H/status-post-9.txt" || s=$?; [ "$s" -eq 0 ] && [ ! -s "$EVID/H/status-post-9.txt" ] || STOP
# Step 6 — the fence-proofs file, then H LAST
{ printf 'check=runner-controls rc=%s expected=0\n' 0; printf 'check=E5-flip rc=%s expected=0\n' 0; printf 'check=closure-invoke-git rc=empty expected=empty\n'; printf 'check=S1-nospawn rc=empty expected=empty\n'; printf 'check=network-class-content rc=0 expected=0 sites=%s\n' "$nnc"; printf 'check=veto9 rc=0 expected=0\n'; cat "$EVID/H/repoentry-census.rc"; cat "$EVID/H/repoentry-census-controls.txt"; printf 'check=c2-hunk rc=0 expected=0\n'; printf 'check=zero-byte-fences rc=empty expected=empty\n'; printf 'check=a8-facts-wrapped unwrapped=0 expected=0\n'; printf 'check=isatty-predicate count=0 expected=0\n'; printf 'check=hook-install-no-json-offline-network count=0 expected=0\n'; cat "$EVID/H/count-gate-final-macos.rc" "$EVID/H/count-gate-final-linux.rc" "$EVID/H/E3-linux.rc" "$EVID/H/harness-e2-macos.rc" "$EVID/H/harness-e2-linux.rc" "$EVID/H/selftest-population.rc"; [ -s "$EVID/H/linux-selftest-bar.txt" ] && cat "$EVID/H/linux-selftest-bar.txt"; [ -s "$EVID/H/selftest-series.rc" ] && cat "$EVID/H/selftest-series.rc"; printf 'check=H0-H-delta rc=0 expected=0\n'; } > "$EVID/H/fence-proofs.txt" || STOP; [ -s "$EVID/H/fence-proofs.txt" ] || STOP
printf 'H=%s\n' "$H" > "$EVID/H.txt" || STOP; [ -s "$EVID/H.txt" ] || STOP
exit 0
```

### Task 10 — the vehicle (ONLY after the pair Planner's GO relay carrying EXACTLY ONE no-red byte review of H from EACH of m-1, m-3 and m-4 through master): ONE push to ONE pinned destination, ONE draft PR

Protocol (e): before `run-task.sh 10` the operator's ONE typed act is the GO relay's path into `$RUNNERS/task-10-go.txt`; the runner's FIRST gate binds the GO relay (an engine-filed SITREP in `.relays/intg/intg-substep2b/`, `FROM: intg.pair-planner`, `TO: intg.pair-implementer`, `TASK10_GO: yes`, `TASK10_H: <sha>`, and EXACTLY THREE `OWNER_REVIEW_H: <path> | FROM=<seat> | VERDICT=no-red` lines — one whose seat owner is `m-1`, one `m-3`, one `m-4`, three DISTINCT paths under `../pdc/master/relays/`, each relay carrying `S2B_REVIEW_OBJECT: H=<sha>`, `S2B_REVIEW_SCOPE:` and `S2B_REVIEW_VERDICT: no-red` and no red status line).

- [ ] **Step 1: the owner-set gate, then preconditions** — `[ "$(git rev-parse HEAD)" = "$H" ] || STOP`; the GO relay bound as above with the owner set EXACT (`[ "$n1" -eq 1 ] && [ "$n3" -eq 1 ] && [ "$n4" -eq 1 ] || STOP` on the per-owner line counts; `[ "$nu" -eq 3 ] || STOP` on the distinct-path count); Task 9's final receipts (`count-gate-final-*.rc` both 0; both containers rc 0; E3 Linux rc 0; both `harness-e2` rcs 0; the population rule satisfied by the bar or the series); ONE push destination: `git remote get-url --push --all origin` is EXACTLY one line equal to `https://github.com/iwnlcern/bivpak.git` (`[ "$(cat "$EVID/push-url.txt")" = https://github.com/iwnlcern/bivpak.git ] || STOP`); `git ls-remote --heads origin intg/substep2b-wiring` EMPTY; `gh repo view --json visibility` == PRIVATE; no executable `pre-push` hook.
- [ ] **Step 2: ONE push** — `git push --dry-run --no-tags origin intg/substep2b-wiring` (the refspec line exactly once) then the one attempt; class a (remote head == H) or STOP; the attempt is SPENT (no retry).
- [ ] **Step 3: the draft PR** — `pr-body.md` from the record files (`finalize.py prbody`); the census alternation over the body → 0 hits; `gh pr create --draft`; the PR stays a DRAFT until the operator's merge token (the undraft is a P5 publication-lifecycle act that returns to the operator — never self-granted).

<!-- RUN: task-10 -->
```bash
# Runner plumbing (Task 10)
set -o pipefail
PIPEOK() { local st=("${PIPESTATUS[@]}"); local k; for k in "${st[@]}"; do [ "$k" -eq 0 ] || { printf 'STOP-task-10 pipe=%s stage-status=%s line=%s\n' "$1" "${st[*]}" "${BASH_LINENO[0]}" >&2; exit 1; }; done; }
WORKTREE=/Users/jack/Programming/bivpak-intg-substep2b-wiring
MAIN=/Users/jack/Programming/bivpak
B=186adf7d67171bd7afe621f39b657a1a113ce299
cd "$WORKTREE" || STOP
v=0; (cd "$EVID" && shasum -a 256 -c helpers.sha256 > helpers.verify-10.txt 2>&1) || v=$?; [ "$v" -eq 0 ] || STOP
H=$(sed 's/^H=//' "$EVID/H.txt") || STOP; [ -n "$H" ] || STOP
[ "$(git rev-parse HEAD)" = "$H" ] || STOP
# Step 1 — the GO relay and the owner set
[ -s "$RUNNERS/task-10-go.txt" ] || STOP; a=0; ng=$(awk 'END { print NR }' "$RUNNERS/task-10-go.txt") || a=$?; [ "$a" -eq 0 ] && [ "$ng" -eq 1 ] || STOP; GO=$(sed -n '1p' "$RUNNERS/task-10-go.txt") || STOP; [ -s "$GO" ] || STOP
GOD=$(cd "$(dirname "$GO")" && pwd -P) || STOP; RR=$(cd "$MAIN/.relays/intg/intg-substep2b" && pwd -P) || STOP; [ "$GOD" = "$RR" ] || STOP
GOB=$(basename "$GO") || STOP; case "$GOB" in SITREP-pair-planner-[0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9]-[0-9][0-9][0-9][0-9][0-9][0-9].md) :;; *) STOP;; esac
g=0; k=$(grep -c -F -- "intg-substep2b/$GOB" "$MAIN/.relays/intg/INDEX.md") || g=$?; [ "$g" -eq 0 ] && [ "$k" -ge 1 ] || STOP
for pat in '^FROM: intg\.pair-planner$' '^TO: intg\.pair-implementer$' '^PHASE: SITREP$' '^TASK10_GO: yes$'; do g=0; k=$(grep -c -E "$pat" "$GO") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP; done
g=0; k=$(grep -c -x -F -- "TASK10_H: $H" "$GO") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP
g=0; grep -E '^OWNER_REVIEW_H: [^ |]+ \| FROM=m-(1|3|4)\.(planner|implementer) \| VERDICT=no-red$' "$GO" > "$EVID/work/owner-lines.txt" || g=$?; [ "$g" -eq 0 ] || STOP
a=0; nl=$(awk 'END { print NR }' "$EVID/work/owner-lines.txt") || a=$?; [ "$a" -eq 0 ] && [ "$nl" -eq 3 ] || STOP
g=0; n1=$(grep -c -F ' | FROM=m-1.' "$EVID/work/owner-lines.txt") || g=$?; [ "$g" -le 1 ] || STOP; g=0; n3=$(grep -c -F ' | FROM=m-3.' "$EVID/work/owner-lines.txt") || g=$?; [ "$g" -le 1 ] || STOP; g=0; n4=$(grep -c -F ' | FROM=m-4.' "$EVID/work/owner-lines.txt") || g=$?; [ "$g" -le 1 ] || STOP
[ "$n1" -eq 1 ] && [ "$n3" -eq 1 ] && [ "$n4" -eq 1 ] || STOP
s=0; sed -E 's/^OWNER_REVIEW_H: ([^ |]+) \| .*$/\1/' "$EVID/work/owner-lines.txt" > "$EVID/work/owner-paths.txt" || s=$?; [ "$s" -eq 0 ] || STOP; s=0; LC_ALL=C sort -u "$EVID/work/owner-paths.txt" > "$EVID/work/owner-paths.uniq" || s=$?; [ "$s" -eq 0 ] || STOP
a=0; nu=$(awk 'END { print NR }' "$EVID/work/owner-paths.uniq") || a=$?; [ "$a" -eq 0 ] || STOP
[ "$nu" -eq 3 ] || STOP
PDC=$(cd "$MAIN/../pdc/master/relays" && pwd -P) || STOP
: > "$EVID/task-10-go.txt"
while IFS= read -r line; do
  RP=$(printf '%s\n' "$line" | sed -n -E 's/^OWNER_REVIEW_H: ([^ |]+) \| FROM=([^ |]+) \| VERDICT=no-red$/\1/p'); PIPEOK owner-path; RF=$(printf '%s\n' "$line" | sed -n -E 's/^OWNER_REVIEW_H: [^ |]+ \| FROM=([^ |]+) \| VERDICT=no-red$/\1/p'); PIPEOK owner-from; [ -n "$RP" ] && [ -n "$RF" ] || STOP
  case "$RP" in /*) R=$RP;; *) R=$MAIN/$RP;; esac; [ -s "$R" ] || STOP; RD=$(cd "$(dirname "$R")" && pwd -P) || STOP; case "$RD" in "$PDC"/*) :;; *) STOP;; esac
  g=0; k=$(grep -c -x -F -- "FROM: $RF" "$R") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP
  g=0; k=$(grep -c -E '^PHASE: [A-Z-]+$' "$R") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP
  g=0; k=$(grep -c -x -F -- "S2B_REVIEW_OBJECT: H=$H" "$R") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP
  g=0; k=$(grep -c -E '^S2B_REVIEW_SCOPE: .+$' "$R") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP
  g=0; k=$(grep -c -x -F -- 'S2B_REVIEW_VERDICT: no-red' "$R") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP
  g=0; k=$(grep -c -i -E '^([A-Z0-9_]*VERDICT|STATUS): *(must-revise|reject|reject-narrow|red|blocked|pending|hold|human-decision-required)' "$R") || g=$?; [ "$g" -eq 1 ] && [ "$k" -eq 0 ] || STOP
  printf 'owner_review=%s FROM=%s\n' "$R" "$RF" >> "$EVID/task-10-go.txt" || STOP
done < "$EVID/work/owner-lines.txt"
[ -s "$EVID/task-10-go.txt" ] || STOP
[ "$(cat "$EVID/H/count-gate-final-macos.rc")" = count_gate_final_macos_rc=0 ] && [ "$(cat "$EVID/H/count-gate-final-linux.rc")" = count_gate_final_linux_rc=0 ] || STOP
[ "$(cat "$EVID/H/linux-container.rc")" = 0 ] && [ "$(cat "$EVID/B/linux-container.rc")" = 0 ] && [ "$(cat "$EVID/H/E3-linux.rc")" = e3_linux_rc=0 ] && [ "$(cat "$EVID/H/harness-e2-macos.rc")" = harness_e2_macos_rc=0 ] && [ "$(cat "$EVID/H/harness-e2-linux.rc")" = harness_e2_linux_rc=0 ] || STOP
if [ "$(cat "$EVID/H/selftest-population.rc")" = population_equal_rc=0 ]; then g=0; k=$(grep -c -E ' bar=(pass-green|pass-r435-disclosed-registered-red)$' "$EVID/H/linux-selftest-bar.txt") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP; else [ "$(cat "$EVID/H/selftest-series.rc")" = series_rc=0 ] || STOP; g=0; k=$(grep -c -E '^VERDICT NOT-SHIFTED' "$EVID/H/selftest-series.txt") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP; fi
u=0; git remote get-url --push --all origin > "$EVID/push-url.txt" || u=$?; [ "$u" -eq 0 ] && [ -s "$EVID/push-url.txt" ] || STOP; a=0; nurl=$(awk 'END { print NR }' "$EVID/push-url.txt") || a=$?; [ "$a" -eq 0 ] && [ "$nurl" -eq 1 ] || STOP
[ "$(cat "$EVID/push-url.txt")" = https://github.com/iwnlcern/bivpak.git ] || STOP
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
# Step 3 — the draft PR
w=0; python3 "$EVID/finalize.py" prbody "$EVID" "$B" "$H" > "$EVID/pr-body.md" || w=$?; [ "$w" -eq 0 ] && [ -s "$EVID/pr-body.md" ] || STOP
g=0; k=$(grep -c -E 'sk-[A-Za-z0-9]{8,}|-----BEGIN [A-Z ]*PRIVATE KEY|AKIA[0-9A-Z]{16}|ghp_[A-Za-z0-9]{20,}|xox[abprs]-' "$EVID/pr-body.md") || g=$?; [ "$g" -eq 1 ] && [ "$k" -eq 0 ] || STOP
q=0; gh pr create --base main --head intg/substep2b-wiring --title "pack/open: wire the repo engine and the consent fabric at product scope (sub-step 2b)" --body-file "$EVID/pr-body.md" --draft > "$EVID/pr-create.txt" 2>&1 || q=$?; printf 'pr_rc=%s\n' "$q" > "$EVID/pr.rc"; [ "$q" -eq 0 ] || STOP
exit 0
```

### Task 11 — FINALIZE: the census rehearsal at H0 with the population PRODUCED on H0; the landing declaration; the tracked record `results/s2b-<token>/` sealed AFTER every retained write

- [ ] **Step 1: preconditions** — Task 10 done/exit/proof receipts; push class a; PR created; the results dir absent; the instrument's bytes: `[ "$ACT" = 9c9391d5b57fa51793a5cb777537dc6ed572d0522f1138f38df2c5bddd5d99a6 ] || STOP` (the FULL pinned digest of `results/intg-r449-landing-census.sh`, recorded in the R-4.49 packet §8).
- [ ] **Step 2: the population PRODUCED on H0, then the instrument** — `census_population.sh "$H0" "$EVID/census-raw/H0/population-H0.txt" "$H0"` (BLOCK; the same alternation and producer lines the instrument uses; every matched value classified by its sha256 against the two ACCEPTED VALUE DIGESTS carried from the R-4.49 record — class A = the fixture digest at a product path, B = the fixture digest elsewhere, C = the English digest; an unclassifiable value is a STOP naming path:line only, never the text; the file's sections in the instrument's exact form); then the ONE instrument invocation with H0 as the tree ref AND as the sole history ref (its reachable history contains B): `c=0; bash "$INST" "$H0" "$EVID/census-raw/H0/population-H0.txt" "$EVID/census-raw/H0" "$H0" > "$EVID/H/census-rehearsal.log" 2>&1 || c=$?; printf 'census_rehearsal_rc=%s\n' "$c" > "$EVID/H/census-rehearsal.rc"; [ "$c" -eq 0 ] || STOP`.
- [ ] **Step 3: the landing declaration** — `$EVID/receipts/landing-census-declaration.txt`: the two command lines the landing act runs at `main`'s post-merge head under the operator's token — `census_population.sh <merge> <pop-merge> <merge>` then `<INST> <merge> <pop-merge> <out> <merge>` — with the instrument digest, the population producer's digest, and the rule that the population is PRODUCED on the merge object and never carried (the R-4.50 lesson); the pair Planner copies it into the merge packet.
- [ ] **Step 4: classify, THEN freeze the set, THEN copy** — the pre-scan list; every set file scanned with the alternation; the classification written (`record-token-classes.txt`); THEN the FINAL set listed (`finalize.py list` — the classification file is now in it); the copy under `results/s2b-<token>/`; `SHA256SUMS` (`LC_ALL=C sort -k2`); `finalize.py check` rc 0; `shasum -c` rc 0. The finalizer's own controller receipts are excluded by declaration (`finalize.py`); nothing else is written into the home after the final list.

<!-- RUN: task-11 -->
```bash
# Runner plumbing (Task 11)
set -o pipefail
PIPEOK() { local st=("${PIPESTATUS[@]}"); local k; for k in "${st[@]}"; do [ "$k" -eq 0 ] || { printf 'STOP-task-11 pipe=%s stage-status=%s line=%s\n' "$1" "${st[*]}" "${BASH_LINENO[0]}" >&2; exit 1; }; done; }
WORKTREE=/Users/jack/Programming/bivpak-intg-substep2b-wiring
MAIN=/Users/jack/Programming/bivpak
B=186adf7d67171bd7afe621f39b657a1a113ce299
cd "$WORKTREE" || STOP
v=0; (cd "$EVID" && shasum -a 256 -c helpers.sha256 > helpers.verify-11.txt 2>&1) || v=$?; [ "$v" -eq 0 ] || STOP
[ -s "$EVID/runners/task-10.done" ] && [ "$(cat "$EVID/runners/task-10.done")" = rc=0 ] || STOP; [ -s "$EVID/push-class.txt" ] && [ "$(cat "$EVID/push-class.txt")" = class=a ] || STOP; [ -s "$EVID/pr.rc" ] && [ "$(cat "$EVID/pr.rc")" = pr_rc=0 ] || STOP
TOKEN=$(sed -n 's/^token=//p' "$EVID/token.txt"); [ -n "$TOKEN" ] || STOP; RESDIR=$MAIN/docs/sprints/2026-08-27-intg-consent-fabric/results/s2b-${TOKEN}; [ ! -e "$RESDIR" ] || STOP
H0=$(sed 's/^H0=//' "$EVID/H0.txt") || STOP; [ -n "$H0" ] || STOP; H=$(sed 's/^H=//' "$EVID/H.txt") || STOP; [ -n "$H" ] || STOP
# Step 1 — the instrument's bytes
INST=$MAIN/docs/sprints/2026-08-27-intg-consent-fabric/results/intg-r449-landing-census.sh; [ -s "$INST" ] || STOP
h=0; ACT=$(shasum -a 256 "$INST" | cut -d' ' -f1); PIPEOK inst-digest; [ -n "$ACT" ] || STOP
[ "$ACT" = 9c9391d5b57fa51793a5cb777537dc6ed572d0522f1138f38df2c5bddd5d99a6 ] || STOP
# Step 2 — the population PRODUCED on H0, then the rehearsal
m=0; mkdir -p "$EVID/census-raw/H0" || m=$?; [ "$m" -eq 0 ] || STOP
p=0; bash "$EVID/census_population.sh" "$H0" "$EVID/census-raw/H0/population-H0.txt" "$H0" > "$EVID/H/census-population.log" 2>&1 || p=$?; printf 'population_producer_rc=%s\n' "$p" > "$EVID/H/census-population.rc"; [ "$p" -eq 0 ] && [ -s "$EVID/census-raw/H0/population-H0.txt" ] || STOP
c=0; bash "$INST" "$H0" "$EVID/census-raw/H0/population-H0.txt" "$EVID/census-raw/H0" "$H0" > "$EVID/H/census-rehearsal.log" 2>&1 || c=$?; printf 'census_rehearsal_rc=%s\n' "$c" > "$EVID/H/census-rehearsal.rc"; [ "$c" -eq 0 ] || STOP
g=0; k=$(grep -c -E ' result=PASS$' "$EVID/H/census-rehearsal.log") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP
c=0; cp "$EVID/census-raw/H0/population-H0.txt" "$EVID/H/population-H0.txt" || c=$?; [ "$c" -eq 0 ] || STOP
# Step 3 — the landing declaration
PD=$(shasum -a 256 "$EVID/census_population.sh" | cut -d' ' -f1); PIPEOK producer-digest; [ -n "$PD" ] || STOP
w=0; printf 'landing census declaration (sub-step 2b) — run at main POST-MERGE head <merge> under the operator token, never carried:\n  bash census_population.sh <merge> <out>/population-merge.txt <merge>   # producer sha256 %s\n  bash intg-r449-landing-census.sh <merge> <out>/population-merge.txt <out> <merge>   # instrument sha256 %s\nrehearsed at H0=%s: producer rc 0, instrument result=PASS; H=%s\n' "$PD" "$ACT" "$H0" "$H" > "$EVID/receipts/landing-census-declaration.txt" || w=$?; [ "$w" -eq 0 ] && [ -s "$EVID/receipts/landing-census-declaration.txt" ] || STOP
# Step 4 — classify, freeze, copy
x=0; python3 "$EVID/finalize.py" list "$EVID" > "$RUNNERS/final-set-pre.txt" || x=$?; [ "$x" -eq 0 ] && [ -s "$RUNNERS/final-set-pre.txt" ] || STOP
g=0; k=$(grep -c -E '^(work/|census-raw/)' "$RUNNERS/final-set-pre.txt") || g=$?; [ "$g" -eq 1 ] && [ "$k" -eq 0 ] || STOP
ALT='sk-[A-Za-z0-9]{8,}|-----BEGIN [A-Z ]*PRIVATE KEY|AKIA[0-9A-Z]{16}|ghp_[A-Za-z0-9]{20,}|xox[abprs]-'
: > "$EVID/census-raw/record-hits.raw" || STOP; while IFS= read -r f; do g=0; grep -o -E "$ALT" "$EVID/$f" >> "$EVID/census-raw/record-hits.raw" || g=$?; [ "$g" -le 1 ] || STOP; done < "$RUNNERS/final-set-pre.txt"
r=0; git grep -h -o -E "$ALT" "$B" -- tests/test_adapter_codex_collect.cpp tests/test_cli.cpp > "$EVID/census-raw/fixture-tokens.raw" || r=$?; [ "$r" -eq 0 ] || STOP
o=0; LC_ALL=C sort -u "$EVID/census-raw/record-hits.raw" > "$EVID/census-raw/record-hits.set" || o=$?; [ "$o" -eq 0 ] || STOP; o=0; LC_ALL=C sort -u "$EVID/census-raw/fixture-tokens.raw" > "$EVID/census-raw/fixture-tokens.set" || o=$?; [ "$o" -eq 0 ] || STOP
c=0; LC_ALL=C comm -23 "$EVID/census-raw/record-hits.set" "$EVID/census-raw/fixture-tokens.set" > "$EVID/census-raw/foreign.set" || c=$?; [ "$c" -eq 0 ] && [ ! -s "$EVID/census-raw/foreign.set" ] || STOP
a=0; nd=$(awk 'END { print NR }' "$EVID/census-raw/record-hits.set") || a=$?; [ "$a" -eq 0 ] || STOP
w=0; printf 'distinct_matched_strings=%s foreign_matched_strings=0 class=B-fixture-copies-only\n' "$nd" > "$EVID/record-token-classes.txt" || w=$?; [ "$w" -eq 0 ] && [ -s "$EVID/record-token-classes.txt" ] || STOP
x=0; python3 "$EVID/finalize.py" list "$EVID" > "$RUNNERS/final-set.txt" || x=$?; [ "$x" -eq 0 ] && [ -s "$RUNNERS/final-set.txt" ] || STOP
g=0; k=$(grep -c -x -F 'record-token-classes.txt' "$RUNNERS/final-set.txt") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP
m=0; mkdir -p "$RESDIR" || m=$?; [ "$m" -eq 0 ] && [ -d "$RESDIR" ] || STOP
c=0; while IFS= read -r f; do d=$(dirname "$f") && mkdir -p "$RESDIR/$d" && cp -p "$EVID/$f" "$RESDIR/$f" || { c=1; break; }; done < "$RUNNERS/final-set.txt"; [ "$c" -eq 0 ] || STOP
h=0; (cd "$RESDIR" && find . -type f ! -name SHA256SUMS -exec shasum -a 256 {} + > "$RUNNERS/final-manifest.unsorted") || h=$?; [ "$h" -eq 0 ] && [ -s "$RUNNERS/final-manifest.unsorted" ] || STOP; o=0; LC_ALL=C sort -k2 "$RUNNERS/final-manifest.unsorted" > "$RESDIR/SHA256SUMS" || o=$?; [ "$o" -eq 0 ] || STOP
k=0; python3 "$EVID/finalize.py" check "$EVID" "$RESDIR" "$RESDIR/SHA256SUMS" > "$RUNNERS/final-verdict.txt" 2>&1 || k=$?; printf 'finalize_check_rc=%s\n' "$k" > "$RUNNERS/final-verdict.rc"; [ "$k" -eq 0 ] || STOP
v=0; (cd "$RESDIR" && shasum -a 256 -c --quiet SHA256SUMS) > "$RUNNERS/final-shasum-c.txt" 2>&1 || v=$?; [ "$v" -eq 0 ] || STOP
exit 0
```

### Task 12 — the commission-closure SITREP (the pair Planner's; AFTER the verified landing under the operator's token and R-4.52)

- [ ] ORDER: this task begins ONLY after the operator's bare merge token has been consumed and the merge head is on `main` (R-4.52) — nothing here runs before the token. The landing census FOR the merge head: the pinned instrument (`9c9391d5…`, Task 11's `census_population.sh` re-run ON THE MERGE HEAD to produce its population; Task 11's declaration consumed, never carried as an expectation) PASS with the merge head as tree and history ref — receipt in `results/s2b-<token>/landing-census.txt`. Then the final pin (`main`'s post-merge head == `origin/main`); the FOUR worktrees disposed with receipts (Task 0's three + `../bivpak-intg-substep2b-wiring` after landing, one receipt); the evidence homes sealed and named (`results/s2b-<token>/` + the R-4.49 record); the open residuals handed to owners BY ROW (T-K, T-C if registered, T-NET, T-PROM, I2B-09 (b), anything an owner STOP left); no further act routes to the pair without a fresh commission.

## Acceptance criteria (each measured, none inferred)

1. `git log --reverse B..H` reads c1a, c1b, c1c (engine only, each at its exact path set) first; no later commit touches `src/core/repo/`; `git diff B HEAD -- src/core/scan/scan.cpp` carries no `".biv"` line (V-2b-5 rev2); no commit spans both sets (`H/veto9.txt`); `git diff H0 H -- . ':!.github/workflows/s2-harness.yml'` EMPTY (every H0 receipt carries to H).
2. E2 census non-empty; E5's grep at H0 equals E2's site set exactly; the network-class census CONTENT-identical to B's (six engine sites; line numbers may move); `invoke_git(` and every spawn primitive absent outside `src/core/repo`/`src/core/support`.
3. Every FX leg named in the evidence matrix has a `legs/<id>.txt` receipt with `provenance=product-packed verdict=PASS`, or a line in `legs/registered.txt` naming its S-6 owner; the open-side legs' hand-built interim receipts are NOT cited by the packet.
4. a8·1–a8·4 pass on all eleven rows; the A8 census shows every bound value wrapped exactly once; `render.cpp` diff EMPTY; the table header carries `Unicode 15.0.0` + both input digests + the generator digest, and regenerating from `tools/` reproduces it byte-for-byte.
5. The hook install has three rows and no `json`/`offline`/`network` term; `grep -c 'isatty(' src/cli/main.cpp` == 0.
6. `UnclaimedGitEntry` lands only with A9's lock id in its commit message (exit map 29 → 29 at c6a); the nine A11 kinds land only with A11's lock id (exit map 29 → 38, ErrKind 36, seven transitional at c6b); `result.repos` + its schema row land only with A10's lock id in ONE commit (c4b); `RepoDiscoveredUnsupported` absent from `src/`, `schemas/`, `tests/`; no engine failure reaches a verb as `InternalError` at H (V-A11-1) and no unknown kind is mapped; every fence fixture packs NO image; the selftest pins recomputed in the same commits that changed the schema bytes.
7. Count gate: observed case tuples at H0 on both platforms equal the workflow cells at H (after c9 iff owed; `count-gate-final-*.rc` both 0); skip sets unchanged on both platforms (a change is a STOP); the Linux single-sample bar `pass-green` or `pass-r435-disclosed-registered-red` when the harness-selftest population is equal at B and H0, OR the 015244 series' `VERDICT NOT-SHIFTED` (K-1/K-2 clean; K-3 not shifted) when it moved.
8. E3 receipts on both platforms; E4 parity receipt; the harness receipt on BOTH targets (`harness-e2` green at H0 on macOS and inside the Linux container; m-3's commit limited to `harness/scenarios/**`).
8b. Every runner proof reports `gates>0`; the Task 9 runner controls (PIPEOK must-be-NO, unwritable write, partial-output producer) all STOPped where they must; the RepoEntry census controls fired / did not fire as declared.
9. Cut-point `origin/main..B` = 0 at Task 0; ONE push destination (`https://github.com/iwnlcern/bivpak.git`, exactly one push URL line); the branch pushed class a; the PR open (draft) against `main` with head H; `main` NOT pushed by this plan; the three worktrees disposed with receipts.
10. EXACTLY one no-red byte review of H from EACH of m-1, m-3 and m-4 (unique relay paths under `../pdc/master/relays/`, each carrying the object, scope and verdict lines) bound by the GO relay BEFORE Task 10 (protocol (e) in the runner).
11. The census rehearsal at H0: the population PRODUCED on H0 by `census_population.sh` (every matched value classified A/B/C by digest; an unclassifiable value is a STOP), the pinned instrument (`9c9391d5b57fa51793a5cb777537dc6ed572d0522f1138f38df2c5bddd5d99a6`) PASS with H0 as tree and history ref; the merge-head declaration written for the landing act.

## Out of scope (an act here is a STOP, not a judgement)

Any `src/core/repo` byte beyond Task 1's c1a/c1b/c1c; any change to `execute_open`'s signature or to the result-null-iff-error invariant (A11 rev5; a fourth engine diff no fence authorizes); any pack of a dirty, nested or submodule repository SUCCEEDING (Q11; R-4.57); any per-repo exclusion or full+note lane for a fence; any second consent surface, persistence or envelope member for the D3 decision (V-A10-2/4, S-A10-2); any extraction of an overlay row's `local-refs.bundle` (R-4.58); any byte of scan.cpp's `.biv` payload skip (V-2b-5 rev2; ADDENDUM-I unsealed, R-4.55); any `src/core/manifest` byte; any `src/adapters` or `harness/bivharness` byte; any `render.cpp` byte; any summary-line or warnings-row emission for consent (S-4); any persistence of an approval; any address classification or safety wording; any new argv/env/config surface beyond the two flags; any envelope member, kind, exit row or wording the sealed texts and the owner cuts do not determine (T-JSON's member and T-KIND's bytes wait on their words); a pack-level FX-O arm; the PR undraft; the merge; the push of `main`; any release act.

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

- `plan_blocks.py`, `run-task.sh` — the runner protocol's two instruments (R-4.49 plan, verbatim except: `plan_blocks.py`'s task-number regexes accept one or two digits and its `list` enumerates the RUN markers actually present (so `task-10`/`task-11` are listed) because this plan's runner tasks are 0, 9, 10, 11; `run-task.sh` accepts N ∈ {0, 9, 10, 11}; the predecessor map is 9←0, 10←9, 11←10; the continuation gate is Task 10's `task-10-go.txt`).
- `resume.sh` (rev17) — protocol step 0′: binds a NEW runners directory to a later token's lock and id while carrying Task 0's receipts and every gate file; run once per later token, before any task; its gates are the ones §Per-task runner protocol states.
- `cells.py`, `tuples.py`, `skipset.py`, `selftest_summary.py` — verbatim.
- `cellgate.py` — the 2b form: `cellgate.py <cells.txt> <target> <tuples.txt>` exits 0 iff every literal cell equals the observed tuple on `<target>`; prints one `MOVED <binary> literal=… observed=…` line per differing cell (data, not a STOP — a moved `biv_tests` cell is EXPECTED in this act and drives the companion commit) and `UNCHANGED <binary>` otherwise.
- `finalize.py` — verbatim except the finalizer receipts name Task 11, and the `prbody` subcommand (the PR body from the record files).
- `linux-container.sh` — the R-4.49 container (Phases R / T / S: base provision, the pinned clang-tidy-22 mirror assets, the non-root `suite` user, the branch clone at the expected head, the suite) with Phase L (the read-trace leg) REMOVED, the branch literal `intg/substep2b-wiring`, and labels `B`, `H`, `B-<n>`, `H-<n>` (the series draws).
- `linux-suite.sh` — verbatim except the label set.
- `git-shim.sh` — the request-trace instrument: first on the child's `PATH`, appends `argv` to `$BIV_GIT_TRACE` (one line per spawn, tab-separated, cwd first) and `exec`s the real git named by `$BIV_GIT_REAL`.
- `gen_consent_display_table.py` — the clause-5 table generator (deterministic; input digests and the generator's own digest in the header).
- `series_verdict.py` — the 015244 interleaved-series reducer, the ruling's three clauses IN ORDER and verbatim in meaning: per-draw validity and equal population within each tree (m-3 §6); K-1 membership — every failing test across all 2N draws in the four-member R-4.35 family, else a FRESH FINDING halts; K-2 — any draw with ≥ 5 failures halts; K-3 — SHIFTED iff (landed mean − base mean) ≥ 1.0 OR landed min ≥ base max; NOT-SHIFTED is the ONLY release verdict here (the deselection arm is not pre-authorized for this candidate); per-test frequencies reported. Read against `master/relays/r437-pack-timeout-diagnosis/DESIGN-planner-20260903-015244.md` at this seat before rev3.
- `repoentry_census.py` — the TYPE-SCOPED RepoEntry production census (m-1 V-2b-4): enumerates RepoEntry-typed bindings (declarations, vectors and their range-for variables, `Classification::entry` through a Classification binding) and reports any member WRITE on them; exit 5 on a hit; its two controls are run by Tasks 5 and 9.
- `cellpatch.py` — rewrites ONLY the moved `successes`/`skips` literals of the workflow's count cells to the observed tuples (both platform blocks), preserving every other byte; a red observation exits 5.
- `xmlcases.py` — reads a Catch2 XML for the `[E3]`-tagged cases' results and a CTest JUnit for one named row's status (the E3 Linux witness and the `harness-e2` receipts).
- `census_population.sh` — PRODUCES the landing-census population ON THE OBJECT SCANNED in the pinned instrument's exact file form (the R-4.49 accepted value digests carried; every matched value classified A/B/C by digest in memory; an unclassifiable value STOPs; no matched text written); the same lines run at landing on the merge head.

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


<!-- BLOCK: repoentry_census.py -->
```python
#!/usr/bin/env python3
# usage: repoentry_census.py <dir>...  — the TYPE-SCOPED RepoEntry production census (m-1 V-2b-4): exit 0 iff NO member write exists on any
# RepoEntry-typed binding in the given trees; exit 5 with one line per hit otherwise; exit 2 on no input files.
# A "RepoEntry-typed binding" is (a) a declaration whose type text names RepoEntry (`repo::RepoEntry`, `biv::repo::RepoEntry`, `RepoEntry&`,
# `std::vector<...RepoEntry>` and its element loops), (b) a range-for variable over such a vector, (c) `Classification::entry` reached through a
# Classification binding (`c->entry`, `c.entry`). A WRITE is `<binding>[.index]?.<member> = <not '='>` or `<binding>.<member> +=` etc.
# Controls (run by the plan): `entries[0].sha = "x";` on a RepoEntry vector ⇒ exit 5; `warning.path = "x";` on an unrelated type ⇒ exit 0.
import os, re, sys
DECL = re.compile(r'\b(?:const\s+)?(?:biv::)?(?:repo::)?RepoEntry\s*&?\s*([A-Za-z_][A-Za-z0-9_]*)\b')
VEC = re.compile(r'std::vector<\s*(?:biv::)?(?:repo::)?RepoEntry\s*>\s*&?\s*([A-Za-z_][A-Za-z0-9_]*)\b')
CLS = re.compile(r'\b(?:biv::)?(?:repo::)?Classification\s*>?\s*&?\s*([A-Za-z_][A-Za-z0-9_]*)\b|expected<\s*(?:biv::)?(?:repo::)?Classification\s*>\s+([A-Za-z_][A-Za-z0-9_]*)\b')
files = []
for d in sys.argv[1:]:
    for root, _dirs, names in os.walk(d):
        for n in names:
            if n.endswith((".cpp", ".hpp")):
                files.append(os.path.join(root, n))
if not files:
    print("NO-INPUT"); sys.exit(2)
hits = 0
for path in sorted(files):
    text = open(path, encoding="utf-8", errors="replace").read()
    names, vecs, cls = set(), set(), set()
    for m in DECL.finditer(text): names.add(m.group(1))
    for m in VEC.finditer(text): vecs.add(m.group(1))
    for m in CLS.finditer(text): cls.add(m.group(1) or m.group(2))
    for v in list(vecs):
        for m in re.finditer(r'for\s*\(\s*(?:const\s+)?auto\s*&?\s*([A-Za-z_][A-Za-z0-9_]*)\s*:\s*' + re.escape(v) + r'\s*\)', text):
            names.add(m.group(1))
    names -= {"RepoEntry"}
    for lineno, line in enumerate(text.split("\n"), 1):
        for n in sorted(names):
            if re.search(r'\b' + re.escape(n) + r'\s*(\[[^\]]*\])?\s*\.\s*[A-Za-z_][A-Za-z0-9_]*\s*(\+|-|\*|/|%|&|\||\^|<<|>>)?=(?!=)', line):
                print("WRITE %s:%d binding=%s :: %s" % (path, lineno, n, line.strip())); hits += 1
        for v in sorted(vecs):
            if re.search(r'\b' + re.escape(v) + r'\s*\[[^\]]*\]\s*\.\s*[A-Za-z_][A-Za-z0-9_]*\s*(\+|-|\*|/|%|&|\||\^|<<|>>)?=(?!=)', line):
                print("WRITE %s:%d vector=%s :: %s" % (path, lineno, v, line.strip())); hits += 1
        for c in sorted(cls):
            if re.search(r'\b' + re.escape(c) + r'\s*(->|\.)\s*entry\s*\.\s*[A-Za-z_][A-Za-z0-9_]*\s*(\+|-|\*|/|%|&|\||\^|<<|>>)?=(?!=)', line):
                print("WRITE %s:%d classification=%s :: %s" % (path, lineno, c, line.strip())); hits += 1
    print("SCANNED %s bindings=%d vectors=%d classifications=%d" % (path, len(names), len(vecs), len(cls)))
print("RESULT writes=%d" % hits)
sys.exit(0 if hits == 0 else 5)
```

<!-- BLOCK: cellpatch.py -->
```python
#!/usr/bin/env python3
# usage: cellpatch.py <workflow.yml> <tuples-macos.txt> <tuples-linux.txt> > patched.yml — rewrites ONLY the `successes` / `skips` literals
# of the five binaries inside the macOS and Linux `checks = {` blocks to the OBSERVED tuples (failures/expectedFailures must be 0 in the
# observation — anything else exits 5); every other byte of the workflow is preserved. exit 2 = malformed input.
import re, sys
text = open(sys.argv[1], encoding="utf-8").read()
def tuples(path, target):
    out = {}
    for line in open(path, encoding="utf-8"):
        p = line.split()
        if len(p) >= 6 and p[0].startswith("biv_") and p[1] == target and p[2].startswith("successes="):
            vals = dict(x.split("=", 1) for x in p[2:6]); out[p[0]] = vals
    return out
obs = {"macos": tuples(sys.argv[2], "macos"), "linux": tuples(sys.argv[3], "linux")}
for t, rows in obs.items():
    if len(rows) != 5: print("MALFORMED tuples for %s: %d" % (t, len(rows))); sys.exit(2)
    for b, v in rows.items():
        if v["failures"] != "0" or v["expectedFailures"] != "0": print("OBSERVED-RED %s %s %s" % (t, b, v)); sys.exit(5)
starts = [m.start() for m in re.finditer(r"checks = \{", text)]
if len(starts) != 2: print("MALFORMED workflow: %d checks blocks" % len(starts)); sys.exit(2)
bounds = starts + [len(text)]
out = text[:starts[0]]
for target, (lo, hi) in zip(("macos", "linux"), zip(starts, bounds[1:])):
    region = text[lo:hi]
    for b, v in obs[target].items():
        pat = re.compile(r'("%s": \{\s*"successes": )(\d+)(,\s*"failures": \d+,\s*"expectedFailures": \d+,\s*"skips": )(\d+)(,)' % re.escape(b))
        region, n = pat.subn(lambda m: m.group(1) + v["successes"] + m.group(3) + v["skips"] + m.group(5), region, count=1)
        if n != 1: print("MALFORMED workflow: cell %s/%s not found once" % (target, b)); sys.exit(2)
    out += region
sys.stdout.write(out)
```

<!-- BLOCK: xmlcases.py -->
```python
#!/usr/bin/env python3
# usage: xmlcases.py e3 <catch2-xml>            — exit 0 iff at least one TestCase carries the tag [E3] and every such case succeeded (rows printed)
#        xmlcases.py ctest-row <name> <ctest-junit> — exit 0 iff the ctest testcase <name> exists and has no <failure>/<error>/<skipped> child
import sys, xml.etree.ElementTree as ET
mode = sys.argv[1]
if mode == "e3":
    root = ET.fromstring(open(sys.argv[2], "rb").read())
    rows = [(tc.get("name"), (tc.find("OverallResult") or {}).get("success")) for tc in root.iter("TestCase") if "[E3]" in (tc.get("tags") or "")]
    if not rows: print("E3 cases=0"); sys.exit(3)
    for name, ok in rows: print("E3 case=%r success=%s" % (name, ok))
    sys.exit(0 if all(ok == "true" for _, ok in rows) else 5)
if mode == "ctest-row":
    name, path = sys.argv[2], sys.argv[3]
    root = ET.parse(path).getroot()
    tc = next((t for t in root.iter("testcase") if t.get("name") == name), None)
    if tc is None: print("ROW-ABSENT %s" % name); sys.exit(3)
    bad = [c.tag for c in tc if c.tag in ("failure", "error", "skipped")]
    print("ROW %s status=%s children=%s" % (name, tc.get("status"), bad or "none"))
    sys.exit(0 if not bad else 5)
print("usage"); sys.exit(2)
```

<!-- BLOCK: series_verdict.py -->
```python
#!/usr/bin/env python3
# usage: series_verdict.py <series-dir> <r435-family.txt> <N>  — the 015244 interleaved-series reducer, the three clauses IN ORDER:
#   validity  every draw <series-dir>/{B,H}-<i>/selftest-<label>.kv has summary=parsed, failed == names_count, population > 0, and the
#             population is EQUAL within each tree (m-3 130818 §6: every sample under the bar's own valid-draw rule; an invalid draw is a STOP)
#   K-1       MEMBERSHIP, categorical: every failing test across ALL 2N draws lies in the four-member R-4.35 family; ANY name outside it is a
#             FRESH FINDING attributed to the landing — HALT (exit 1, VERDICT STOP fresh-finding <names>)
#   K-2       ESCALATION FLOOR: any single draw with failure count >= 5 — HALT (exit 1, VERDICT STOP escalation <label> <count>)
#   K-3       SHIFT (only if K-1/K-2 pass): SHIFTED iff (landed mean - base mean) >= 1.0 OR landed min >= base max (complete separation);
#             SHIFTED => exit 1 (VERDICT SHIFTED ...) — the deselection arm is NOT pre-authorized for this candidate; NOT-SHIFTED => exit 0.
#   report    per-test failure frequencies per tree (informational; R-4.36's evidence base).
import os, sys
sd, fam_path, n = sys.argv[1], sys.argv[2], int(sys.argv[3])
family = {ln.strip() for ln in open(fam_path, encoding="utf-8") if ln.strip()}
if len(family) != 4: print("VERDICT STOP family-not-four"); sys.exit(1)
def draw(label):
    kv = dict(ln.rstrip("\n").split("=", 1) for ln in open(os.path.join(sd, label, "selftest-%s.kv" % label), encoding="utf-8") if "=" in ln)
    names = [ln.strip() for ln in open(os.path.join(sd, label, "selftest-%s.names" % label), encoding="utf-8") if ln.strip()]
    return kv, names
trees = {"B": [], "H": []}
for i in range(1, n + 1):
    for t in ("B", "H"):
        label = "%s-%d" % (t, i)
        kv, names = draw(label)
        failed = int(kv.get("failed", "-1")); pop = int(kv.get("population", "0"))
        if kv.get("summary") != "parsed" or failed != len(names) or failed != int(kv.get("names_count", "-2")) or pop <= 0:
            print("VERDICT STOP invalid-draw %s %s" % (label, kv)); sys.exit(1)
        trees[t].append((label, pop, failed, names))
for t, rows in trees.items():
    if len({p for _, p, _, _ in rows}) != 1:
        print("VERDICT STOP population-unequal-within-tree %s %s" % (t, sorted({p for _, p, _, _ in rows}))); sys.exit(1)
fresh = sorted({nm for rows in trees.values() for _, _, _, names in rows for nm in names} - family)
if fresh:
    print("VERDICT STOP fresh-finding K-1 " + " ".join(fresh)); sys.exit(1)
for t, rows in trees.items():
    for label, _, failed, _ in rows:
        if failed >= 5:
            print("VERDICT STOP escalation K-2 %s count=%d" % (label, failed)); sys.exit(1)
bc = [f for _, _, f, _ in trees["B"]]; hc = [f for _, _, f, _ in trees["H"]]
bmean = sum(bc) / len(bc); hmean = sum(hc) / len(hc)
shifted = (hmean - bmean) >= 1.0 or min(hc) >= max(bc)
freq = {}
for t, rows in trees.items():
    for _, _, _, names in rows:
        for nm in names: freq[(t, nm)] = freq.get((t, nm), 0) + 1
for (t, nm), k in sorted(freq.items()): print("FREQ tree=%s test=%s draws=%d/%d" % (t, nm, k, n))
print("K-3 base_mean=%.2f landed_mean=%.2f base_max=%d landed_min=%d delta=%.2f" % (bmean, hmean, max(bc), min(hc), hmean - bmean))
if shifted:
    print("VERDICT SHIFTED (K-3) — countgate HELD for this candidate; the deselection arm is not pre-authorized here"); sys.exit(1)
print("VERDICT NOT-SHIFTED draws=%d population_B=%d population_H=%d" % (2 * n, trees["B"][0][1], trees["H"][0][1]))
sys.exit(0)
```

<!-- BLOCK: census_population.sh -->
```bash
#!/bin/bash
# census_population.sh <TREE_REF> <OUT_POP> <HISTORY_REF>... — PRODUCES the population file the pinned landing-census instrument consumes, ON THE
# OBJECT SCANNED (never carried). Same alternation; the TREE ARM rows (path:line | class) from ONE `git grep -n` over the whole tree, every matched
# value classified IN MEMORY by its sha256 against the two ACCEPTED VALUE DIGESTS of the R-4.49 record (fixture / english); class A = the fixture
# digest at a product path (src|tests|harness|.github|CMake), B = the fixture digest elsewhere, C = the english digest; ANY other value ⇒
# STOP naming path:line only (a new class is the pair Planner's classification, never automatic). HISTORY ARM: `git rev-list` over the refs, ONE
# `git grep -l`, paths sorted -u under LC_ALL=C. bash 3.2; set -o pipefail; every producer's rc before its output is read; no matched text written.
set -u
set -o pipefail
ALT='sk-[A-Za-z0-9]{8,}|-----BEGIN [A-Z ]*PRIVATE KEY|AKIA[0-9A-Z]{16}|ghp_[A-Za-z0-9]{20,}|xox[abprs]-'
FIX=2b3d813effb1ac2021683332d9bc74477e9d7bf5a9bc47a95a8c725de0562150
ENG=5d64f445c82a86cf123096105cd0d3a763abce9db9d67f366b5694c3b483f380
STOP() { printf 'STOP-census-population line=%s reason=%s\n' "${BASH_LINENO[0]}" "$1" >&2; exit 1; }
PIPEOK() { local st=("${PIPESTATUS[@]}"); local k; for k in "${st[@]}"; do [ "$k" -eq 0 ] || STOP "$1-stage-status-${st[*]// /-}"; done; }
[ $# -ge 3 ] || STOP usage
TREE_REF=$1; OUTP=$2; shift 2
export LC_ALL=C
TREE=$(git rev-parse --verify --quiet "${TREE_REF}^{tree}") || STOP tree-ref-unresolvable
[ "${#TREE}" -eq 40 ] || STOP tree-sha-shape
r=0; RAW=$(git grep -n -o -E "$ALT" "$TREE" -- .) || r=$?; [ "$r" -eq 0 ] || STOP tree-producer-rc-"$r"
[ -n "$RAW" ] || STOP tree-zero-rows
TMP=$(mktemp) || STOP tmp; : > "$TMP" || STOP tmp-write
nA=0; nB=0; nC=0
while IFS= read -r line; do
  case "$line" in "$TREE:"*) ;; *) STOP tree-row-prefix;; esac
  rest=${line#"$TREE:"}; pl=${rest%%:*}:; rest2=${rest#*:}; ln=${rest2%%:*}; val=${rest2#*:}; pl=${pl%:}
  dg=$(printf '%s' "$val" | shasum -a 256 | cut -d' ' -f1); PIPEOK value-digest
  cls=""
  if [ "$dg" = "$FIX" ]; then case "$pl" in src/*|tests/*|harness/*|.github/*|CMake*) cls="A fixture-product";; *) cls="B fixture-copy";; esac
  elif [ "$dg" = "$ENG" ]; then cls="C english-word-false-positive"
  else STOP "unclassified-value-at-$pl:$ln"; fi
  case "$cls" in A*) nA=$((nA+1));; B*) nB=$((nB+1));; C*) nC=$((nC+1));; esac
  printf '%s:%s | %s\n' "$pl" "$ln" "$cls" >> "$TMP" || STOP row-write
done <<EOF_ROWS
$RAW
EOF_ROWS
unset RAW
nt=$(awk 'END { print NR }' "$TMP") || STOP count
HTMP=$(mktemp) || STOP tmp2
git rev-list "$@" > "$HTMP.revs" || STOP rev-list; [ -s "$HTMP.revs" ] || STOP rev-list-empty
REVS=$(cat "$HTMP.revs") || STOP rev-list-read; set -- $REVS; [ $# -ge 1 ] || STOP rev-list-args
x=0; git grep -l -E "$ALT" "$@" -- . > "$HTMP.raw" || x=$?; [ "$x" -eq 0 ] || STOP history-producer-rc-"$x"
sed -E 's/^[0-9a-f]{40}://' "$HTMP.raw" > "$HTMP.paths" || STOP history-strip
LC_ALL=C sort -u "$HTMP.paths" > "$HTMP.p" || STOP history-reduction; [ -s "$HTMP.p" ] || STOP history-empty
nh=$(awk 'END { print NR }' "$HTMP.p") || STOP count2; nr=$(awk 'END { print NR }' "$HTMP.revs") || STOP count3
{
  printf '# sub-step 2b census population PRODUCED on %s (tree %s) by census_population.sh — paths and line numbers ONLY; no matched text.\n' "$TREE_REF" "$TREE"
  printf '# Classes by value digest against the R-4.49 record: A fixture-product (%s) B fixture-copy (%s) C english (%s); history refs: %s (%s commits)\n' "$nA" "$nB" "$nC" "$*" "$nr"
  printf '== ACCEPTED VALUE DIGESTS: fixture=%s english=%s\n' "$FIX" "$ENG"
  printf '\n== TREE ARM (path:line | class) — %s locations\n' "$nt"
  cat "$TMP"
  printf '\n== HISTORY ARM — %s paths\n' "$nh"
  cat "$HTMP.p"
  printf '\n'
} > "$OUTP" || STOP population-write
rm -f "$TMP" "$HTMP" "$HTMP.revs" "$HTMP.raw" "$HTMP.paths" "$HTMP.p"
[ -s "$OUTP" ] || STOP population-empty
printf 'census_population tree=%s rows=%s A=%s B=%s C=%s history_paths=%s commits=%s\n' "$TREE" "$nt" "$nA" "$nB" "$nC" "$nh" "$nr"
exit 0
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
    for n in sorted({task for task, _, _ in runs}, key=int):
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

<!-- BLOCK: resume.sh -->
```bash
#!/usr/bin/env bash
# resume.sh — protocol step 0': bind a NEW runners directory to a LATER token (new PLAN_LOCK digest, new DISPATCH_ID, the SAME evidence home) while carrying Task 0's receipts and every gate file
# usage: bash resume.sh <EVID> <new PLAN_LOCK sha256> <new DISPATCH_ID>   — run ONCE per later token, before any task under it; prints the NEW runners path as its only stdout line
set -u
STOP() { printf 'STOP-resume %s line=%s\n' "$1" "${BASH_LINENO[0]}" >&2; exit 1; }
EVID=${1-}; NEWLOCK=${2-}; NEWTOKEN=${3-}
[ -n "$EVID" ] && [ -d "$EVID" ] && [ -d "$EVID/runners" ] && [ -d "$EVID/code" ] || STOP evid
printf '%s' "$NEWLOCK" | grep -q -E '^[0-9a-f]{64}$' || STOP lock-form
printf '%s' "$NEWTOKEN" | grep -q -E '^intg-substep2b-impl-[0-9]+$' || STOP token-form
OLD=$(cat "$EVID/runners-dir.txt") || STOP old-pointer; [ -n "$OLD" ] && [ -d "$OLD" ] || STOP old-runners-absent
PLAN=$(cat "$OLD/plan-path.txt") || STOP plan-pointer; [ -s "$PLAN" ] || STOP plan-absent
h=0; d=$(shasum -a 256 "$PLAN" | cut -d' ' -f1) || h=$?; [ "$h" -eq 0 ] && [ "$d" = "$NEWLOCK" ] || STOP plan-not-the-new-lock
OLDLOCK=$(cat "$OLD/plan-lock.txt") || STOP old-lock; [ -n "$OLDLOCK" ] && [ "$OLDLOCK" != "$NEWLOCK" ] || STOP same-lock
[ -s "$OLD/task-0.done" ] && [ "$(cat "$OLD/task-0.done")" = rc=0 ] || STOP task-0-not-done
c=0; cmp "$OLD/task-0.done" "$EVID/runners/task-0.done" || c=$?; [ "$c" -eq 0 ] || STOP task-0-done-mismatch
h=0; s=$(shasum -a 256 "$OLD/task-0.sh" | cut -d' ' -f1) || h=$?; r=$(cut -d' ' -f1 "$OLD/task-0.sha256") || STOP task-0-sha-read; [ "$h" -eq 0 ] && [ -n "$r" ] && [ "$s" = "$r" ] || STOP task-0-sh-altered
c=0; cmp "$OLD/task-0.sh" "$EVID/runners/task-0.sh" || c=$?; [ "$c" -eq 0 ] || STOP task-0-sh-mismatch
[ "$(cat "$OLD/evid.txt")" = "$EVID" ] || STOP evid-pointer
for f in proof-0.txt task-0.sha256 task-0.invocation.txt task-0.exit task-0.proof-tail task-0.self.sha256 plan-hash-0.txt plan_blocks.sha256-0; do [ -s "$OLD/$f" ] || STOP "receipt-absent-$f"; done
m=0; mkdir -p "$HOME/Programming/bivpak-evidence" || m=$?; [ "$m" -eq 0 ] || STOP evidence-root
NEW_RAW=$(mktemp -d "$HOME/Programming/bivpak-evidence/s2b-runners-XXXXXX") || STOP mktemp; NEW=$(cd "$NEW_RAW" && pwd -P) || STOP new-real; [ -d "$NEW" ] && [ "$NEW" = "$NEW_RAW" ] || STOP new-path
w=0; printf '%s\n' "$PLAN" > "$NEW/plan-path.txt" || w=$?; [ "$w" -eq 0 ] && [ -s "$NEW/plan-path.txt" ] || STOP w-plan-path
w=0; printf '%s\n' "$NEWLOCK" > "$NEW/plan-lock.txt" || w=$?; [ "$w" -eq 0 ] && [ -s "$NEW/plan-lock.txt" ] || STOP w-plan-lock
w=0; printf '%s\n' "$NEWTOKEN" > "$NEW/token-id.txt" || w=$?; [ "$w" -eq 0 ] && [ -s "$NEW/token-id.txt" ] || STOP w-token
w=0; printf '%s\n' "$EVID" > "$NEW/evid.txt" || w=$?; [ "$w" -eq 0 ] && [ -s "$NEW/evid.txt" ] || STOP w-evid
bx() { python3 -c 'import sys; t = open(sys.argv[1], encoding="utf-8").read(); m = "<!-- BLOCK: " + sys.argv[2] + " -->\n"; i = t.index(m) + len(m); j = t.index("\n", i) + 1; k = t.index("\n" + chr(96) * 3 + "\n", j); sys.stdout.write(t[j:k + 1])' "$PLAN" "$1"; }
x=0; bx plan_blocks.py > "$NEW/plan_blocks.py" || x=$?; [ "$x" -eq 0 ] && [ -s "$NEW/plan_blocks.py" ] || STOP x-plan-blocks; k=0; python3 -m py_compile "$NEW/plan_blocks.py" || k=$?; [ "$k" -eq 0 ] || STOP compile-plan-blocks
x=0; bx run-task.sh > "$NEW/run-task.sh" || x=$?; [ "$x" -eq 0 ] && [ -s "$NEW/run-task.sh" ] || STOP x-run-task; s=0; bash -n "$NEW/run-task.sh" || s=$?; [ "$s" -eq 0 ] || STOP syntax-run-task
chmod 0500 "$NEW/run-task.sh" || STOP chmod; [ -x "$NEW/run-task.sh" ] || STOP exec
h=0; shasum -a 256 "$NEW/run-task.sh" > "$NEW/run-task.sha256" || h=$?; [ "$h" -eq 0 ] && [ -s "$NEW/run-task.sha256" ] || STOP h-run-task
x=0; python3 "$NEW/plan_blocks.py" list "$PLAN" > "$NEW/blocks.txt" || x=$?; [ "$x" -eq 0 ] && [ -s "$NEW/blocks.txt" ] || STOP blocks-list
CARRIED=''
for f in task-0.sh proof-0.txt task-0.sha256 task-0.invocation.txt task-0.exit task-0.done task-0.proof-tail task-0.self.sha256 plan-hash-0.txt plan_blocks.sha256-0; do c=0; cp -p "$OLD/$f" "$NEW/$f" || c=$?; [ "$c" -eq 0 ] && [ -s "$NEW/$f" ] || STOP "carry-$f"; c=0; cmp "$OLD/$f" "$NEW/$f" || c=$?; [ "$c" -eq 0 ] || STOP "carry-cmp-$f"; CARRIED="$CARRIED $f"; done
for f in m3-addendum-9-lock.txt m1-fence-rev4.txt m3-help-order.txt t-oracle.txt m3-r462-patch.txt m1-fence-word.txt m3-addendum-10-lock.txt m3-addendum-11-lock.txt m3-harness-patch.txt task-10-go.txt; do [ -e "$OLD/$f" ] || continue; c=0; cp -p "$OLD/$f" "$NEW/$f" || c=$?; [ "$c" -eq 0 ] && [ -s "$NEW/$f" ] || STOP "carry-$f"; c=0; cmp "$OLD/$f" "$NEW/$f" || c=$?; [ "$c" -eq 0 ] || STOP "carry-cmp-$f"; CARRIED="$CARRIED $f"; done
h=0; (cd "$NEW" && shasum -a 256 $CARRIED > carried.sha256) || h=$?; [ "$h" -eq 0 ] && [ -s "$NEW/carried.sha256" ] || STOP carried-sha
w=0; printf '%s\n' "$OLD" > "$NEW/previous-runners.txt" || w=$?; [ "$w" -eq 0 ] && [ -s "$NEW/previous-runners.txt" ] || STOP w-prev
w=0; printf '%s\n' "$OLDLOCK" > "$NEW/previous-lock.txt" || w=$?; [ "$w" -eq 0 ] && [ -s "$NEW/previous-lock.txt" ] || STOP w-prev-lock
STAMP=$(date +%Y%m%d-%H%M%S) || STOP stamp
c=0; cp -p "$EVID/runners-dir.txt" "$EVID/runners-dir.prev-$STAMP.txt" || c=$?; [ "$c" -eq 0 ] && [ -s "$EVID/runners-dir.prev-$STAMP.txt" ] || STOP preserve-pointer
w=0; printf '%s\n' "$NEW" > "$EVID/runners-dir.txt" || w=$?; [ "$w" -eq 0 ] && [ "$(cat "$EVID/runners-dir.txt")" = "$NEW" ] || STOP w-pointer
m=0; mkdir "$EVID/runners/resume-$NEWTOKEN" || m=$?; [ "$m" -eq 0 ] || STOP seal-dir
c=0; cp -p "$NEW/plan-lock.txt" "$NEW/token-id.txt" "$NEW/previous-runners.txt" "$NEW/previous-lock.txt" "$NEW/carried.sha256" "$NEW/blocks.txt" "$NEW/run-task.sha256" "$EVID/runners/resume-$NEWTOKEN/" || c=$?; [ "$c" -eq 0 ] || STOP seal-copy
w=0; printf 'resumed token=%s lock=%s from=%s new=%s at=%s\n' "$NEWTOKEN" "$NEWLOCK" "$OLD" "$NEW" "$STAMP" > "$EVID/runners/resume-$NEWTOKEN/resume.txt" || w=$?; [ "$w" -eq 0 ] && [ -s "$EVID/runners/resume-$NEWTOKEN/resume.txt" ] || STOP seal-note
printf '%s\n' "$NEW"
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
        body = ["Sub-step 2b: wire biv pack and biv open to the repo engine and the landed consent fabric at product scope (sealed M/N/O, A6/A7/A8/A9, SR-URL; the R-4.47 bar).", "",
                "B (published pin) = %s" % base, "H0 (suite object) = %s" % rd("H0.txt"), "H (branch head) = %s" % head, "", "Commits (veto-9 mechanical order):", commits, "",
                "E2 wiring census:", "```", rd("H/E2-census.txt"), "```", "E5 flip: diff EMPTY (%s)" % ("yes" if rd("H/E5-flip.txt") == "" else "NO"),
                "veto 9:", "```", rd("H/veto9.txt"), "```", "Count gate (final): macOS %s / linux %s; %s" % (rd("H/count-gate-final-macos.rc"), rd("H/count-gate-final-linux.rc"), rd("H/count-gate.txt")),
                "E3 (both platforms): macOS receipt legs/E3.txt; linux %s" % rd("H/E3-linux.rc"), "harness-e2: macOS %s; linux %s" % (rd("H/harness-e2-macos.rc"), rd("H/harness-e2-linux.rc")),
                "Selftest population: %s%s" % (rd("H/selftest-population.rc"), (" ; series " + rd("H/selftest-series.rc")) if os.path.isfile(os.path.join(evid, "H/selftest-series.rc")) else (" ; bar " + rd("H/linux-selftest-bar.txt"))),
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

- rev17 (2026-09-19): folds the implementer's IMPL STOPs `intg-substep2b/IMPL-pair-implementer-20260919-171145.md` (the final credential-clean floor at the ten-path candidate red ONLY on the untouched probe fixture `tests/test_probe.cpp:671`) and `…-175439.md` (the pair Planner's disposition 173140: D1 ×20 isolation at the D0-pinned candidate binary = 18/20 — run 16 `:671` -1, run 17 `:606` 1179 ms; D2 ×20 load = 20/20; the candidate build cleared by an interleaved A/B at the pair Planner's seat) — registered R-4.62 by master 175324, owned at open by m-3.planner (180036: a real-time 200 × 5 ms poll inside a fake-clock test; the -1 says the marker file never existed within the budget), arm (a) triggered by m-3's own rule (≥ 1 in 40): m-3's test-only patch `master/domains/m-3-restore-cli/patches/2026-09-19-r462-test-probe-fixture-bounds.patch` (sha256 `69e8db84c2a7be37d52436bde8d98495aef391a4fbdf58e93801f68a1faab81e`, +11/−5 in `tests/test_probe.cpp` only: both waiter polls 200 → 6000 × 5 ms as a hung-fixture guard, the first half's probe wall 1000 → 10000 ms and its promptness bound 800 → 5000 ms, the sibling `:916-945` poll the same guard, the unrelated `:531` bound left as is) authored at m-3's seat (183855) and APPROVED at the exact sha by m-3.implementer (190602), the fields carried by master 191012, the vehicle ruled by master 182240 = the Task 8 arm-A shape. Task 4 gains Step 3c: an EXECUTABLE gate on `$RUNNERS/m3-r462-patch.txt` (three fields; both paths tracked + unmodified in pdc; the patch re-hashed; the approve relay bound by header, verdict, `TARGET_PATCH_SHA256` and its own `patch=`/`sha256=` lines; the mailbox's author; the pre-image and the ten-path dirty set proved before, the post-image, one commit, m-3's authorship and the unchanged dirty set proved after; `git am`), the rebuild (the probe binary must change), and m-3's WITNESS (D1 ×20 isolation + D2 ×20 load at the rebuilt binary, per run: own TMPDIR, a 5 ms watcher for the exiting-marker's first sighting + copy, `--durations yes`, wall ms, `uptime` before/after; 40/40 closes arm (a); any red STOPs — never a retry) BEFORE Step 4's floor; Step 4 names the `-r462` receipt suffix, master's conditions (i)/(ii), and the `:531` arm-(c) rule. The runner protocol gains Step 0′ + the `resume.sh` BLOCK: a later token (new lock, new id, the same home) binds a NEW runners directory carrying Task 0's receipts and every gate file, with the plan re-hashed against the new lock (the gap disclosed on the token 162507 / 162750; master 175324). A10 rev7 (`46f66f89…`) and A11 rev7 (`9f613760…`) are APPROVED by m-3.implementer (190600/190601) but NOT LOCKED (the Master Reviewer's re-verify, the locks and the seal relays follow at master) — c4b / c6b HOLD at their gate files as before; the lock values are transcribed in the revision that follows the locks, not here. Every new block EXECUTED at the pair Planner's seat before filing: Step 3c on a scratch clone at c3 carrying the candidate's exact ten-path diff (the must-be-YES through the commit, the rebuild and a shortened witness) and against its mutants (a wrong `sha256=`; the authoring relay 183855 in place of the approve; the pre-image altered; a red witness); Step 0′ on a scratch mirror of the real runners and evidence directories and against five mutants.
- rev16 (2026-09-19): folds the implementer's exact-hash MUST-REVISE of rev15 (`intg-substep2b/PLAN-REVIEW-pair-implementer-20260919-040334.md`): MUST-2B-31 — the gate binds master's ADDRESSED request TO m-1.planner and m-1's reply in THAT lineage (the CC-answered 033215 is refused on lineage); the approve waits on the exchange existing; MUST-2B-33 — the window and m-3's word are PINNED by sha256 in the plan; m-1's reply and master's request are pinned by digests the carry affirms and the gate re-hashes; a committed-but-changed owner STOPs on the pin; MUST-2B-34 — the carry must carry exactly one `T_ORACLE_VERDICT: cleared` line plus four exact object/plan fields; NOT CLEARED, blocked, an objection without the phrase, an absent or duplicate verdict each STOP. Executed: the real pinned m-3 word + a synthetic addressed exchange and carry pass; nineteen controls STOP on their own predicates.
- rev15 (2026-09-19): folds the implementer's exact-hash MUST-REVISE of rev14 (`intg-substep2b/PLAN-REVIEW-pair-implementer-20260919-034009.md`): MUST-2B-31 — the owner words are on file in their own voices (m-3 033307, m-1 033215, both TO master replying to the window; m-1 from CC) and master's carry TO the pair is the addressed act the gate binds, with the TO-m-1 form asked of master as well; MUST-2B-32 — T-ORACLE is an EXECUTABLE evidence gate reading four pdc carriers (window by sha256; two owner words by header, lineage, case, window id and SUBJECT disposition; master's carry by header, both owner paths, `T-ORACLE`, the live plan's sha256, no keep-the-freeze), each path `..`-free, non-symlink, beneath `master/relays`, tracked + unmodified; executed on the real owner words + a synthetic carry in a scratch clone (pass) and twelve controls (STOP, no receipt).
- rev14 (2026-09-19): folds the implementer's exact-hash MUST-REVISE of rev13 (`intg-substep2b/PLAN-REVIEW-pair-implementer-20260919-032618.md`): MUST-2B-27 — the dead `sha256_hex` helper (test_open.cpp:54-58) is deleted in a second hunk (the suite is `-Werror`; `-Wunused-function` would red), two hunks proved by `grep -c '^@@'` == 2; MUST-2B-28 — the write-slice oracle asserts the SIX exact call forms (occupancy, create_directories, apply_archive, restore_repos, fsync_tree, rename — each once) in STRICT ORDER, read on the candidate (113 < 1125 < 2072 < 2871 < 3018 < 3273), with four new mutants (writer retargeted to dest ×2, rename before fsync, occupancy after create); MUST-2B-29 — the c4a write-set gate enumerates `git diff HEAD --name-only` (staged + unstaged) and refuses any untracked path, producers rc-checked, executed in a throwaway worktree (ten ⇒ pass incl. a staged subset; an extra staged tracked path ⇒ STOP; an extra untracked path ⇒ STOP; nine ⇒ STOP); MUST-2B-30 — the census is the named command's full nine-line output plus the two targeted producer-checked searches. Plus T-ORACLE (master `intg-2b-wiring-act/PLAN-master-planner-20260919-032924.md`, read before filing): c4a's commit waits on the approve AND m-3's / m-1's words on the re-oracle, carried in `$RUNNERS/t-oracle.txt`; Step 5's block refuses without it.
- rev13 (2026-09-19): folds the implementer's IMPL STOP `intg-substep2b/IMPL-pair-implementer-20260919-021304.md` (c4a's nine-path candidate at 13ec732 reaches focused GREEN; the mandatory full suite fires `tests/test_open.cpp:343`, an s3 Task-4 source-hash FREEZE over the two `open.cpp` regions sealed c4a must change): `tests/test_open.cpp` is c4a's TENTH path (Files; the staged set proved by a ten-path write-set gate before `git add`); Step 3b re-oracles that ONE case in the same commit — the two sha pins deleted, the contract's text controls kept verbatim, the write slice bounded by a stable end anchor and asserted directly (occupancy, OpenPartialPresent, create_directories, fsync_tree, rename, no absolute / weakly_canonical, the one suffix site), five named oracle mutants; Step 4 re-runs the focused receipts, the four c4a mutants and the FULL floor at the final bytes; the typed-refusal fixture is the request-trace shim (the temp-HOME insteadOf is impossible at B: GIT_CONFIG_GLOBAL=/dev/null) — affirmed, product-scope form unchanged (Task 7 M (h)); the source-text census at B recorded (one sha pin in the suite). Tasks 0–3 stand as executed (c1a a73f1da, c1b 9621d4c, c1c 732a39c, c2 e5aa0a3, c3 13ec732); c4b / c6b / c7–c9, Task 10, the landing and the release gates unchanged.
- rev12 (2026-09-18): folds the implementer's exact-hash MUST-REVISE of rev11 (`intg-substep2b/PLAN-REVIEW-pair-implementer-20260918-165800.md`, MUST-2B-26): the Task 6b gate now BINDS the A11 lock carrier and a new `seal_relay` carrier — m-3.planner's DESIGN relay (exact FROM/TO/PHASE/AUTHORITY lines; the lock id as a whole word; the doc sha; the A11 document cited) and master's PLAN relay TO the pair whose `IN_REPLY_TO` is exactly the lock relay (the same id + sha; SEALED); every carrier tracked and unmodified in pdc; arm 2 rides on the bound lock carrier; receipts carry both carriers' sha256. The checks are the shape of the A9 ceremony (165214 → 170242) and were EXECUTED on it as the must-be-YES (the block with two constant substitutions), with nine must-be-NO controls including the reviewer's exact bypass (`relay` = 010159 with the true ruling ⇒ `lock-from`, no receipt).
- rev11 (2026-09-18): folds the implementer's exact-hash MUST-REVISE of rev10 (`intg-substep2b/PLAN-REVIEW-pair-implementer-20260918-164316.md`, MUST-2B-25): Task 6b Step 0 is now an EXECUTABLE block run pre and post — exactly-one-field parsing, the fixed value, the A11 doc re-hashed at its pdc path, both relay paths resolved `..`-free beneath `master/relays`, the owner word bound by BYTES (the 162306 ruling's sha256 + header + verdict sentence, or A11's lock relay from an m-3 seat carrying the spelling and the doc sha), the two one-site counts with producer rc apart, receipts compared pre/post; executed by the pair against a synthetic lock file (pre/post pass; seven controls STOP); Step 5 refuses without the post receipt; the Files prose carries the ruled state.
- rev10 (2026-09-18): T-PARTIAL narrowed to the owner's ruling — m-1.planner `intg-2b-wiring-act/DESIGN-planner-20260918-162306.md` (TO master, the pair CC; landed 16:23, five minutes BEFORE the plan-9 relay was submitted unopened — disclosed in the companion SITREP): (A) `<target>.bvpk-open.partial/` is the spelling, (B) REJECTED, `open.cpp:637` untouched by 2b, DR-2 executed on restore-apply §2.1 (status-only, 9/0, zero removed), A11's three sites respelled by m-3, the rename-map row master's; Task 6b Step 0's admissible `partial_suffix` value is now exactly `.bvpk-open.partial` and its one-site grep gate holds BEFORE and AFTER c6b; the (B) branch text (a c6b open.cpp hunk + rev9+) is removed; the term still RELEASES only on the lock-file fields. No other byte moves.
- rev9 (2026-09-18): folds the implementer's exact-hash MUST-REVISE of rev8 (`intg-substep2b/PLAN-REVIEW-pair-implementer-20260918-153551.md`): MUST-2B-22 — the c3 split proof now grades the STAGED object with three validated discriminators (a hunk whose funcname is `help_text(`; a hunk inside the open-help golden case; an added/removed usage or help-row literal), each run on a must-be-YES and a must-be-NO synthetic diff before the real gate, the diff producer's and `git add`'s rc checked apart from grep's, counts recorded — the block itself executed by the pair in a throwaway worktree at B: missing c3 file ⇒ STOP; clean ⇒ pass; a staged help row ⇒ STOP; a staged golden row ⇒ STOP; a parse-only edit plus an EOF test case ⇒ pass; the orphaned topology continuation under c3h removed (c3h names only `help_text` + the golden); MUST-2B-23 — `RepoOutcomeRow` gains `std::optional<std::string> reconstruct` with its presence rule; the c4b commit text and Task 7's product-scope cell carry A10 rev6 (a)–(m) with the (j)–(m) discriminators; MUST-2B-24 — the ROUTED paragraph names `<partial_dir>/inventory.json` (no suffix); T-PARTIAL carries master 152800's routing state (to m-1, recommendation (A); R-4.61 registered for pack's third form) and the two lock-file fields `partial_suffix=` / `partial_suffix_relay=`; Task 6b Step 0 fails closed on both, and the one-site consumption (open.cpp:637 → writer, `facts.partial_path`, `OpenPartialPresent`, leg (h) reading the suffix from the lock file) is spelled with two grep gates.
- rev8 (2026-09-18): folds the implementer's exact-hash MUST-REVISE of rev7 (`intg-substep2b/PLAN-REVIEW-pair-implementer-20260917-025941.md`): MUST-2B-18 — c3's Step 1(ii) and Step 3 no longer touch the help golden or `help_text` (a control asserts the golden is unchanged in c3; the c3 commit block proves no help/golden hunk is staged); c3h alone carries both. MUST-2B-19 — T-STAGE, Task 4 Step 3 and Step 6 now carry A10 rev6 §A10.6 / §A10.4 VERBATIM: one single-quoted POSIX-sh idiom per stored HEAD state (born / unborn / detached), `git clone` for no row, the copy-safe predicate and the fallback line, legs (j) with both target states and the two controls, (k) exact argv under the seven hazards, (l) the five non-copy-safe fallbacks, (m) the offline-unborn sha; the double-quoted two-form text is GONE. MUST-2B-20 — every lock gate and the RULE compare against the revisions this plan transcribes (A10 rev6 17fda846; A11 rev5 33c69913; A9 rev2 locked). MUST-2B-21 — the partial-directory suffix (`.bvpk-partial` in A11 rev5 vs `.bvpk-open.partial` landed, DR-2) is a routed HOLD term T-PARTIAL keyed on `partial_suffix=` in A11's lock file; no c6b byte names either suffix until the word. No engine byte moves.
- rev7 (2026-09-17, FILED as intg-substep2b-plan-7 on master's 010159 — the M edge bound again at pdc `a1ce40a9` by m-1.implementer's binding approve 171135 of fence rev4; the plan-7 carrier floats DESIGN_SOURCE_COMMIT to that pin; A10 rev6 / A11 rev5 remain contingent on their locks): c1c RELEASED under fence rev4 + its approve (gate file `$RUNNERS/m1-fence-rev4.txt`); the W-G3 count rule (the grep at the candidate head; m-1's erratum: 27 not 26 at 186adf7d, re-run here); the failure inventory distinct from §2.3's quarantine inventory (both owners confirmed the seam — closed without arbitration). ALSO folds master's 170242 — A9 SEALED at `m3-addendum-9-40eaea22-lock-20260916` (pre-stamp 40eaea22 @ c2f7a6c7, post-stamp ae272647 — both re-hashed here): T-KIND / T-HELP RULED at the lock, c3h and c6a RELEASED under the Master Reviewer's boundaries (A9.4's D4 bytes are the golden until A10's own lock; no bundle line from A9; no relabel; the 29-row witness is A9's own); fence rev4 (`161701`, folding the reviewer's 140251): c1c's MECHANISM unchanged, the predicate re-stated as the GIT-CAPABLE partition (FALSE ⇒ no git unconditionally; TRUE ⇒ consent required, no spawn promised), W-G3 narrowed, W-G1 bound to valid fixtures, W-G1c (collision counter-control) and W-G1n (N/H through the error path) added, the D3 trigger and the partition term re-worded. Fence rev3's items: ALSO folds master's 135421 status carry — m-1 fence rev3 `131522`: a THIRD pre-authorized engine commit c1c (`restore_invokes_git` exported and used by `restore_entry`'s own no-git returns; W-G1..3; numstat-bound) so V-2b-1 rev3 = c1a/c1b/c1c and the token's prefix is `c1a c1b c1c c2 c3 c4a c5`; the EXACT `--offline`/DECLINED partition on that predicate (FALSE ⇒ CALL `restore_entry` — 074712 §2's "never called" corrected by m-1; TRUE ⇒ offline-pointer row) in Task 4 and A10 rev6 (17fda846); the D3 trigger READ from the predicate; ARTIFACT-PRESENT = `entry.bundle` ∧ checksums membership; MUST-2B-16 CLOSED by A10 rev5's unborn idiom; MUST-2B-17 CLOSED by A11 rev5's OPEN INVARIANT (invariant kept; the orchestrator's `inventory.json`; `facts.partial_path`/`repo_id`; leg (h) rewritten; leg (m) the three carriers); m-3's fence origin of record is now 134813 (130818 history; §4 retired in favour of A9.4/A10.6); the M edge will re-pin once more after fence rev3's approve. MUST-2B-14 — c3 is split: c3 (unconditional: flags, conflict rule, hook truth table, stderr writers, B-predicate dedup, split PTY helper — no help byte, no golden re-pin) and c3h (A9 lock: the two help lines + the golden), so the token's prefix `c1a c1b c2 c3 c4a c5` is a real commit prefix with no working-tree residue; identity, ORDER, topology, T-HELP and Task 3 say one thing. The A10 revision drift (rev2 → rev4 718fd6ec) recorded as the A10-REV term (D3 trigger = an engine-exposed per-row fact, S-A10-1; DECLINED = the --offline rule; single-quoted POSIX-sh reconstruct with the copy-safe predicate and the fallback line); MUST-2B-15/16/17 recorded as ROUTED owner cells holding the affected c4b/c6b bytes. No engine byte moves.
- rev6 (2026-09-16): folds master `080937` — every open owner cell RULED (m-1 `074712`: Q11 fences = whole-operation typed refusals, `unmerged` permanent, `dirty`/`nested`/`submodule` transitional → R-4.57, Task 5 may start; Q10 promisor pack-only whole-operation both arms; Q13 apply half — the durable artifact at `<dest>/.biv/repos/<id>/repo.bundle` via the §2.1 staging; the ten-kind table; the ARM-1 fact; m-3 `075225`/`080308` + ADDENDUM 10 rev2 `81e2abca`: Q8 `--network` NOT inert — D3 executes; Q9 `result.repos` rows; Q13 UX half — the two reconstruct forms; ADDENDUM 11 rev1 `26161c41`: the nine engine-error wire kinds). THREE contingent lock ids (A9 → c6a, A10 → c4b, A11 → c6b), each binding at ITS lock; c4 splits into c4a (sealed) + c4b (A10), c6 into c6a (A9) + c6b (A11); the token's unconditional prefix is c1a c1b c2 c3 c4a c5; the terms T-JSON / T-STAGE / T-NET / T-FENCE / T-PROM rewritten as RULED/HOLD-at-lock terms with the addenda's bytes quoted; new T-A11 and T-ARM (registered Arm 2/3/4 legs: patch round trip, nested/two-row images, leaves-first + parents-before-children at product scope, submodules). ARM-1 REALITY applied to every fixture: packed repos are CLEAN with `.gitignore`d penumbra (an untracked file is the dirty fence at classify.cpp:347-357); the MUST-2B-02 leg corrected to the real-bundle + local-refs round trip; W-D1's product form is the nested-fence refusal naming the nested repository (the any-depth-skip mutant packs it silently); the open-side parents-before-children witness is hand-built (synthetic manifest) and labelled so; the rev5 offline "drain, never materialize" routing stands at c4a and gains the durable placement at c4b. Runner proofs unchanged (3/13/4/2). No engine byte moves.
- rev5 (2026-09-16): folds the implementer's exact-hash MUST-REVISE of rev4 (`intg-substep2b/PLAN-REVIEW-pair-implementer-20260916-065734.md`): MUST-2B-04 — T-STAGE: `apply_archive` gains an `std::optional<path> stage` parameter that ROUTES `repos/` members (online: extracted into the stage dir; offline: drained + verified, never materialized; the stage path never touched under `--offline`) with a product discriminator (a pre-created FILE at the stage path: offline exits 0 and leaves it unchanged; online reports `OpenPartialPresent`; the extract-regardless mutant reds); T-FENCE: the product STOP branch is REMOVED — Task 5 does not start until `$RUNNERS/m1-fence-word.txt` holds m-1's disposition, the candidate HOLDS at c4, and the fence branch is transcribed from the word in the revision that carries it. MUST-2B-12 — ONE canonical root representation (`ScanExclusions::canonical`: `"."`/`""` → `""`), a root-claimed fast path in `scan()` (payload + prune list EMPTY, nothing read), pack canonicalizes discover's relpaths, the unit test uses the PRODUCTION value with the fast-path mutant named, and Task 7's workspace-root leg is the product discriminator. MUST-2B-13 — the identity block, the CEN row and Task 12 now say the landing census FOR the merge head is Task 12's (POST-merge, after the operator's token); Task 11 is the pre-merge rehearsal + declaration; Task 10 the vehicle; the `--offline` variant in Task 5 Step 1 is scoped to the fixture's born non-shallow repo. No other section changes.
- rev4 (2026-09-16): folds m-1's fence rev2 (`master/relays/intg-2b-wiring-act/DESIGN-planner-20260915-171041.md`, approved by m-1.implementer `044559` at pdc `631aae82` — master 051652): c1 becomes TWO engine commits at the head of history — c1a (the offline mode placed AFTER the unborn/shallow return, binding the born non-shallow lane only; R-4.1 arm (i) scoped to the git-aware promisor lane) and c1b (`discover.cpp`'s `.biv` discovery skip root-scoped; nested `.biv` walked; `.git` dirs and symlinks unwalked; marker test unchanged) — veto 9 mechanical over both; the PACK (COND-6 no-network) and OPEN (N-R4 parity, `restore_entry` never called under `--offline`) receipts as separate evidence rows RCPT-P / E4+RCPT-O; witnesses W-O1..3 and W-D1..4 in `tests/test_repo_engine.cpp` and re-executed at Task 7's product scope (W-D3's provenance half and W-D4's negative-membership status per 044559); V-2b-5 rev2 — `scan.cpp`'s any-depth `.biv` payload skip stays AS LANDED (a runner gate); T-PROM scoped. The plan-4 carrier floats DESIGN_SOURCE_COMMIT to `631aae82…` (the M edge measured PASS by `xroot_authority` at that tree). No other section changes; the A9 terms stay contingent on the LOCK id (rev2 `40eaea22` passed its pair gate on the merits; the binding re-file is pending).
- rev3 (2026-09-15): folds the implementer's exact-hash MUST-REVISE of rev2 (`intg-substep2b/PLAN-REVIEW-pair-implementer-20260915-140509.md`, MUST-2B-01..11 — the dispositions are the R5 table in RECONCILE.md and the PLAN relay): the typed `engine_error_kind` accessor at both consuming boundaries with controls (01); the stage keeps the manifest-relative namespace, a real bundle + both patch classes restore, offline rows stated as three branches (02); `machine_text` on every A8 machine carrier with the malformed-replacement oracle, whole-byte-golden renderer tests (03); HOLD-before-bytes contingent terms, T-LIST added, no vocabulary alternatives (04); file lists, raw-core vs rendered-CLI test boundaries, no invented schema enum (05); `plan_blocks.py` lists two-digit tasks, prose gate spans bind every runner, `set -o pipefail` + `PIPEOK` + runner controls, the type-scoped RepoEntry census with controls, network class compared by content, closure greps, the C-2 hunk `cmp`, the A8/predicate/hook censuses executed (06); c9 inside the Task 9 runner with H written LAST and the H0→H delta proof (07); both-target harness receipts, the single-sample bar on the equal-population branch, the exact 015244 reducer with NOT-SHIFTED required (08); the exact owner set with distinct paths and ONE pinned push URL (09); the pinned instrument digest literal, `census_population.sh` producing the population on H0, H0 as history ref, classify-then-freeze in Task 11 (10); the canonical cross-repo design edge declared on the PLAN carrier and measured root-mode (11 — the measured fired set is reported on the carrier and UP).
- rev2 (2026-09-15, same day, BEFORE any review verdict): folds m-3.implementer's MUST-REVISE of Addendum 9 rev1 (132531) — T-KIND names A9 and its lock; the detail template is rendered ONCE with encoded `<path>`/`<reason>` and RAW `error.path` (MUST-A9-1); T-HELP follows A9's revised, adjacency-preserving placement (MUST-A9-2); NEW T-LIST: list/info ignore trailing tokens at the pin (MUST-A9-3); the A9 renderers live in url_consent.cpp; `consent_display` is one consent-local encoder. rev1 was filed 134403 without reading 132531 — a re-sweep miss, disclosed.
- rev1 (2026-09-15): the opening plan for sub-step 2b under the three pre-token gates (m-4 035001; m-1 042531 + master 043301; m-3 130818 + master 131404), master's Q1/Q5/Q6 ruling (041518) and the RECONCILE R4 corrections; filed for the implementer's exact-hash review.
