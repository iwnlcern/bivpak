# Sub-step 2b — wiring `biv pack` and `biv open` to the repo engine and the landed consent fabric at product scope — Implementation Plan (rev8)

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** connect both product verbs to the landed repo engine (`src/core/repo`) and the landed consent fabric (`src/cli/url_consent.cpp`), executing SEALED text only — M rev8 / N / O (m-1), A6 rev14 / A7 rev2 / A8 rev8 / A2 D4 (m-3), SR-URL rev5 (m-4), the R-4.47 bar — so that `biv pack` discovers, classifies, gates, captures and records repositories, `biv open` restores them per entry, PROMPT D fires at both encounters through the A6/A7/A8 fabric, `--offline` reaches the engine on both verbs, and every deferred witness (FX-M-1 (a)–(o) incl. (d) + (a)-interactive; FX-A6 a6·1–13 + a6·16's divergence half; FX-A7 a7·1–5; FX-A8 a8·1–a8·6; FX-N (a)/(g); R-4.48 (ii)–(iv)) executes at product scope.

**Architecture:** ONE candidate branch cut from the PUBLISHED PIN `186adf7d67171bd7afe621f39b657a1a113ce299`, commits in the veto-9 MECHANICAL order (the THREE pre-authorized engine commits c1a/c1b/c1c FIRST — m-1 V-2b-1 rev3 — every call-site commit after them; no commit spans both sets), three product tranches A (fabric + CLI plumbing, zero engine reach) → B (open restore path) → C (pack pipeline, the shipped `.git` refusal RETIRED into the narrowed `UnclaimedGitEntry` class), then m-3's harness commit (arm-A shape), then the count-cell companion commit iff a case tuple moved. Every open-side witness first run on a hand-built image is RE-EXECUTED against a `biv pack`-produced image after tranche C, inside the candidate, before the packet (master 041518's condition). The landing rides a PR from the pushed remote branch (R-4.51 (2)); the R-4.49 census instrument is reused at its exact pin with a population written FOR the merge head.

**Tech Stack:** C++23 (`std::expected`), CMake presets `ci-macos` / `ci` (Linux parity container Ubuntu 24.04 `--platform linux/amd64 --init`), Catch2 v3.7.1, the pytest harness under `harness/` (python3.12 venv from `harness/requirements.lock`), bash 3.2-compatible runner blocks, `gh` for the PR.

**Spec (the sealed texts this plan executes; every path under `../pdc/`):** `master/domains/m-1-format-engine/design/2026-08-23-ADDENDUM-M-url-effective-endpoint-consent.md` (M rev8: M-R1..R8 :259-415, FX-M-1 :416-516); `…/2026-08-26-ADDENDUM-N-shallow-payload-only-cell.md` (N; flags-to-wiring-team :320-329; FX-N); `…/2026-09-01-ADDENDUM-O-writer-validity-contract.md` (O; FX-O); `…/2026-07-02-pack-engine.md` (§1.1 Phase D/C, §1.2, §1.3, §2 incl. COND-6, §4); `…/2026-07-02-restore-apply-contract.md` (§1, §2.2); `…/2026-07-04-ADDENDUM-D-offline-and-n3.md` (:78 `offline-pointer`); `…/2026-08-07-ADDENDUM-I-biv-member-refusal.md` (I-R1, I-R2a); `master/domains/m-3-restore-cli/design/2026-08-24-addendum-6-url-consent-consumer-surface.md` (A6 rev14: A6-R1..R9 :380-685, FX-A6 :686-822); `…/2026-08-26-addendum-7-consent-interaction-companion.md` (A7 rev2: A7-R1..R5 :57-138, FX-A7 :139-175); `…/2026-08-29-addendum-8-display-encoding-companion.md` (A8 rev8: A8-R1..R4 :92-256, FX-A8 :257-352); `…/2026-07-04-addendum-2-n24-honest-network-offline.md` (A2 D4 :77-127, D5); `master/domains/m-4-hostile-image/design/2026-08-23-sr-url-effective-endpoint-consent.md` (SR-URL rev5); the R-4.47 bar (`master/relays/m4-reachability-rereview/DESIGN-REVIEW-planner-20260827-204641.md` §1).

**Owner fences this plan is graded against (each read WHOLE by the implementer before Task 0; nothing in them is paraphrased here as authority):** the OWNER WORDS of 2026-09-16 carried by master `master/relays/intg-2b-wiring-act/PLAN-master-planner-20260916-080937.md` — m-1 `master/relays/intg-2b-wiring-act/DESIGN-planner-20260916-074712.md` (Q11 fences = whole-operation typed refusals, `unmerged` permanent, `dirty`/`nested`/`submodule` TRANSITIONAL → R-4.57; Q10 promisor pack-only whole-operation both arms; Q13 apply half — the durable artifact at `<workspace>/.biv/repos/<id>/repo.bundle`; the ten-kind engine semantics table; the ARM-1 fact: the landed engine captures clean single repositories only), m-3 `…/DESIGN-planner-20260916-075225.md` + `080308.md` (Q8 `--network` NOT inert, D3 executes; Q9 `result.repos`; Q13 UX half), m-3's 2b fence origin `master/relays/intg-2b-wiring-act/DESIGN-planner-20260916-134813.md` (rev2 origin under the A6 design-id, approved binding 135230 — the CLI half of record: 130818's §1/§2/§3/§5/§6 carried by reference, its §4 retired clause by clause in favour of A9.4 and A10.6; 130818 is history), m-3 ADDENDUM 10 rev10 — LOCKED `m3-addendum-10-6cba59d3-lock-20260920` (m-3's lock relay `master/relays/intg-2b-wiring-act/DESIGN-planner-20260920-184029.md`; master's seal `master/relays/intg-2b-wiring-act/PLAN-master-planner-20260920-185625.md`) `master/domains/m-3-restore-cli/design/2026-09-16-addendum-10-open-repos-rows-and-network-consent.md` (pre-stamp pin `6cba59d34397f917d4f510d2914e106fb98457ff4d0ae8b4e58f35289c8e1f52` at pdc `5cbb59d7fbb5099ce3acb786941ca752755508d4` — the Domain Reviewer's parented approve 170102 of rev10, the Master Reviewer's APPROVE-FOR-OWNER-LOCK 182105; post-stamp `56abe662b82a189459764d461fd4de024f944a20421930dc86063c558fa0fdda`, both re-hashed at this seat; rev6 `17fda846…` was the revision rev19 transcribed — its rev7..rev10 deltas are transcribed at rev20: ARTIFACT-BEARING keyed on outcome ∧ the engine's artifact-presence fact, never on `capture_mode` (rev7); the detached form's bare `'HEAD'` refspec + the HEAD-only leg (j) fixture (rev8); `capture_mode` OUTCOME-CONDITIONED, null on shallow-pointer / payload-only-unborn rows (rev10, m-1's W-1); A10.2's regained `--json` / PERSISTENCE / ENCODING rows (rev7) — RELEASED to c4b at ITS lock), m-3 ADDENDUM 11 rev11 — LOCKED `m3-addendum-11-fce9cbfa-lock-20260920` (m-3's lock relay `master/relays/intg-2b-wiring-act/DESIGN-planner-20260920-184104.md`; master's seal 185625, the same act) `master/domains/m-3-restore-cli/design/2026-09-16-addendum-11-engine-error-surfacing-rows.md` (pre-stamp pin `fce9cbfaf9eddfee7f3576a235117907fdd499da3f59d1024e7d20dc66db6684` at pdc `2ce699d771ea8a5454e3a0875d6e8134a5f5b09b` — the Domain Reviewer's parented approve 171502 of rev11, the Master Reviewer's 182105; post-stamp `e27763812422f010306a8a3ac1b31f8129d13beb0e724c0de48bfb2eb9c7d895`, both re-hashed at this seat; the lock carries `partial_suffix=.bvpk-open.partial` and `partial_suffix_relay` naming m-1's ruling 162306; rev5 `33c69913…` was the revision rev19 transcribed — its rev6..rev11 deltas are transcribed at rev20: the `.bvpk-open.partial` respelling at the three sites + the SUFFIX paragraph naming 162306 and the lock-file fields (rev6); CR as A8-R1's CLAUSE-2 escape `\r` (rev7); COUNTS by STAGE and MEMBERSHIP — 28/29/4 at the pin, 28/29/3 after A9, 37/38/6 after A9 + A11, the six transitional named (rev8); the INFORMATIVE partial + stage sentence, no policy asked (rev10/rev11, m-1's O-3) — RELEASED to c6b at ITS lock), m-3 ADDENDUM 9 rev2 — LOCKED `m3-addendum-9-40eaea22-lock-20260916` (m-3 `165214`; master 170242): pre-stamp pin `40eaea2273a32922640ade0f65b897ad8d52b40dc8eadef3845264fe1f40fa8c` at pdc `c2f7a6c7eac61fb39c872cb7329734a1cd0c5db0` (the Domain Reviewer's binding approve 134001; the Master Reviewer's approve-for-owner-lock 141334), post-stamp `ae27264763b5ec20057b88f78f87d642ab22a28305a532c66c44063603eb2cf0` (both re-hashed at this seat; the normative region byte-identical), ARCHITECTURE row line 46 — c3h and c6a are RELEASED at this lock under the Master Reviewer's boundaries: A10.6's supersession of A9.4's bundle line takes effect ONLY on A10's OWN lock (A9.4's D4 header/row bytes are the golden until then; NO bundle line is planned from A9); A9 relabels no sealed shallow / payload-only outcome; the 29-row witness is A9's replacement-stage result (A11 moves the count on ITS lock); all eleven A9 legs and mutants are owed at implementation; m-1 `master/relays/intg-2b-wiring-act/DESIGN-planner-20260916-161701.md` (fence rev4 — the fence of record once m-1.implementer's binding approve lands (asked 170247; its must-revise 140251 of rev3 is a hand-carried draft until rendered); supersedes rev3 `131522` and rev2 `171041` IN SUBSTANCE: a THIRD pre-authorized engine commit c1c (`restore_invokes_git` exported and used by `restore_entry`'s single guard at :443-452 — the mechanism unchanged from rev3) re-stated as the engine's GIT-CAPABLE partition (FALSE ⇒ no git UNCONDITIONALLY through success or typed error — N-R4 / H; TRUE ⇒ the restore MAY invoke git once the preceding checks :459/:468/:477/:483 pass and therefore REQUIRES consent — it promises neither a spawn nor a successful apply; first possible spawn :491 or :521+); the walked census of `restore_entry` :425-589 (26 returns; two successful no-git shape returns) quoted beside it; W-G3 narrowed to the single predicate call controlling those two returns; W-G1 bound to PREPARED VALID fixtures; W-G1c the collision counter-control (true, typed failure at :477, zero git — not drift); W-G1n N/H through the error path; W-G2 the drift mutant; the EXACT `--offline`/DECLINED partition on that predicate (FALSE ⇒ CALL `restore_entry`; TRUE ⇒ offline-pointer row) correcting 074712 §2's "never called", ARTIFACT-PRESENT = `entry.bundle` ∧ checksums membership with no engine byte (membership never replacing the integrity/containment checks), and the MUST-2B-17 seam word; 171041 `…/DESIGN-planner-20260915-171041.md` (rev2, approved 044559 at pdc 631aae82 — the M edge's origin until rev3's approve; then the carrier re-pins) stands for everything rev3 carries verbatim: S-2b-1 rev2 (offline COMPOSED with N/G/H — binds only the born non-shallow lane; R-4.1 arm (i) scoped to the git-aware promisor lane; the PACK and OPEN receipts named separately), V-2b-1 rev2 (TWO pre-authorized engine commits c1a/c1b), V-2b-5 rev2 (scan.cpp's `.biv` payload skip stays AS LANDED), witnesses W-O1..3 and W-D1..4; everything else of 042531 stands verbatim: vetoes 1–9 with veto 9 mechanical; V-M-INT-1..5; V-2b-2/4/6/7/8/9; S-2b-2..8; the FX partition; §4 evidence set); m-3 `…/DESIGN-planner-20260915-130818.md` (V-A6-1..6, V-A7-1..4, V-A8-1..5, R-4.48 (ii)–(iv) as vetoes with witnesses; the R4 absence bar in its positive form; TC-1..3; S-1..S-6; §3 the kind; §4 the `--offline`/`--network` cut verbatim; §5 the golden-harness repos bar; §6 the harness-selftest population rule); m-4 `…/DESIGN-planner-20260915-035001.md` (the carry; the E-split; the C-2 pre-warning); m-2 `…/DESIGN-m2-planner-20260915-125200.md` (Q4 NOT a touch on the stated shape — the human open summary moves no session line; a deviation routes back); master `…/PLAN-master-planner-20260915-041518.md` (Q1 both verbs; the re-execution condition; Q5/Q6), `…-043301.md` (`--offline` IN both verbs), `…-131404.md` (all gates IN; the three dispositions; the plan-face list). (rev26) The c6p words, each read WHOLE before the first c6q or c6p byte: master `master/relays/intg-2b-wiring-act/PLAN-master-planner-20260923-011148.md` and the three it carries — m-4 `…/DESIGN-planner-20260922-225418.md`, m-3 `…/DESIGN-planner-20260922-225041.md`, m-1 `…/DESIGN-planner-20260922-225134.md` (T-C6P).

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
                   `m3-addendum-9-40eaea22-lock-20260916` (pre-stamp 40eaea22 @ c2f7a6c7; post-stamp ae272647) → c3h + c6a RELEASED; A10 LOCKED `m3-addendum-10-6cba59d3-lock-20260920` (pre-stamp 6cba59d3 @ 5cbb59d7; post-stamp 56abe662; m-3 184029, seal 185625) → c4b RELEASED; A11 LOCKED `m3-addendum-11-fce9cbfa-lock-20260920` (pre-stamp fce9cbfa @ 2ce699d7; post-stamp e2776381; m-3 184104, seal 185625) → c6b RELEASED; gate files $RUNNERS/m3-addendum-9-lock.txt /
                   m3-addendum-10-lock.txt / m3-addendum-11-lock.txt (WRITTEN 2026-09-20 by the pair Planner into the canonical runners, one field per line: lock_id; doc_sha256 = the post-stamp, the LIVE doc; pin_sha256 + pin_commit = the pre-stamp pin at its pdc commit; relay = the m-3 lock relay; seal_relay = master's 185625 [+ partial_suffix / partial_suffix_relay for A11]; Task 4 Step 0 and Task 6b Step 0 bind each carrier by header, lineage and bytes, and the pin by `git show`)
TOKEN              the pair Planner's bare dispatch token, PARENT = the implementer's exact-hash approve of THIS artifact; under it c1a, c1b, c1c, c2, c3,
                   c4a, c5 proceed (they consume NO A9/A10/A11 row — c3 is the CLI WITHOUT the two help lines and the golden re-pin);
                   c3h (the help lines + golden, A9 lock), c6a, c4b, c6b each HOLD at their contingency; rev22: c6m then c6p (R-4.65's two fixes) after c6b, c6p HOLDING on T-RED1; rev28: c1d then c1e (R-4.72's two engine commits, m-1 `140916` §2 / `150702` §2) after c6p, each HOLDING on the R-4.72 gate (Task 6e Step 0); c7–c9 after c1e; rev33: c8L, c8Tr, c8T (Task 8b) after c8, in that order, and Task 9 after c8T
VEHICLE            ONE push of intg/substep2b-wiring (class a), ONE PR against main; `main` is NEVER pushed by this plan
LANDING            the operator's bare merge token under .relays/intg from the operator's seat; the landing census FOR the merge head is Task 12's
                   (POST-merge, under that token; Task 11 is the PRE-merge rehearsal at H0 + the landing declaration; Task 10 is the vehicle); R-4.52
CLOSURE            the commission-closure SITREP is the LAST task (Task 12): final pin, FOUR worktrees disposed with receipts, evidence homes sealed
                   and named, open residuals handed to owners by row; no further act routes to the pair without a fresh commission
```

## Global constraints (each line binds every task)

- SEALED TEXT ONLY: where M/N/O, A6/A7/A8/A2-D4, SR-URL and the owner cuts DETERMINE, execute byte-exactly; anything they defer or are silent on is a STOP UP the pair line (m-1 S-2b-1..8; m-3 S-1..S-6; M-R7; A6-R7; A7-R5) — never a keyboard call. A STOP is a SITREP to the pair Planner naming the cell; work continues on every task that does not depend on it.
- VETO 9 MECHANICAL (m-1; its mechanical form RE-RULED by its owner for R-4.72, rev28): the sealed M-R8 veto 9 (the consent gate landed before wiring) is satisfied and unaffected. m-1's mechanical form (its `042531` operationalization) binds Task 1: c1a, c1b, c1c are the first three commits above B (V-2b-1 rev3), each its own commit. rev28 admits EXACTLY TWO more engine commits, each engine-only with zero call-site bytes and no spanning commit, which MAY follow c4–c6 because no call site changes (m-1 `140916` §2 `VETO 9 (owner)` for c1d; m-1 `150702` §2 `ORDER` for c1e): c1d (Task 6e) then c1e (Task 6f), both after c6p and before c7. rev33 admits EXACTLY ONE more engine commit (master `224030` Ask A, veto 9 unamended; `003436` heads c8L → c8Tr → c8T; m-1's conditions `224747` §2): c8Tr (Task 8b) — `src/core/repo/restore.cpp` ALONE, zero call-site bytes, after c7, between c8L and c8T. So this plan has exactly SIX engine commits — c1a, c1b, c1c, c1d, c1e, c8Tr; NO commit touches both `src/core/repo/**` and {`src/cli/**`, `src/core/pack/**`, `src/core/scan/**`, `src/core/open/**`}; and no commit other than those six touches `src/core/repo/**`.
- ENGINE BYTES (V-2b-1 rev3, fence 131522 §1; rev28 m-1 `140916` §2 + `150702` §2): zero in `src/core/repo/**` beyond the SIX pre-authorized diffs — Task 1's three: c1a `eligibility.{hpp,cpp}` (the offline mode, placed AFTER the unborn/shallow return at :154-156, binding the born non-shallow lane only), c1b `discover.cpp` (the `.biv` DISCOVERY skip root-scoped; nested `.biv` walked; `.git`-named directories unwalked; symlinked directories unwalked; the marker test :56-70 unchanged) and c1c `restore.{hpp,cpp}` (`bool restore_invokes_git(const RepoEntry&) noexcept` exported — one declaration + one grounds comment; defined as `!entry.shallow && !(entry.head_state == HeadState::unborn && !entry.bundle && !entry.eligibility)`; `restore_entry`'s two no-git early returns at :443-452 become ONE guard on it, shallow arm first, behaviour-preserving; numstat bound restore.hpp +2/-0, restore.cpp one hunk + one function — any other line red); rev28 (R-4.72) Task 6e's c1d `classify.cpp` (both remote-URL sites read `git config --get-all remote.<name>.url` and take the FIRST line; an empty result or a non-zero exit is the existing typed `remote get-url` command error; no new kind; nothing else in classify moves) and Task 6f's c1e `git.{hpp,cpp}`, `git_exec.{hpp,cpp}`, `restore.cpp` (the per-call `GIT_CEILING_DIRECTORIES` = `canonical(partial_root.parent_path())` on every restore invocation; no `GIT_DIR`; no change to M-R2's set, the comparator, `restore_invokes_git` or any row shape), each with `tests/test_repo_engine.cpp`; and rev33's c8Tr `restore.cpp` ALONE (Task 8b; master `215035` R2 + `224030` Ask A: the clang-tidy non-const-global finding at `restore.cpp:13` repaired behaviour-neutrally — the global becomes a function-local static behind `forced_ceiling_error()`, the same single bool and the same two seam accessors; no test path, no header, no NOLINT; m-1's byte review and veto before the landing on the conditions m-1 pre-stated at `master/relays/intg-2b-wiring-act/DESIGN-planner-20260924-224747.md` §2, W-C6 GREEN and its mutant Mc5 RED at the c8Tr head); any other engine need is a STOP (S-2b-5; the third diff's authority is fence rev3 itself, reviewed — never inferred, never in-lane). SCAN PAYLOAD RULE (V-2b-5 rev2): `scan.cpp`'s any-depth `.biv` payload skip (:140-142 at B) stays AS LANDED byte-for-byte — ADDENDUM-I is UNSEALED (R-4.55); a candidate touching it is red. FORMAT BYTES (V-2b-2): zero in `src/core/manifest/**`; the C-2 pack hunk (`pack.cpp` "manifest_json" propagation) byte-identical to a2f6fd1's.
- LINUX TOOLCHAIN AT EVERY NEW HEAD (rev33; master `215035` R3 as corrected by `224030`, final form `003436`): every commit head after c8 (c8L, c8Tr, c8T, and c9 when it exists) passes the canonical container (`linux-container.sh`, rc 0, the four phases and the suite aggregate 0) with the clang-tidy finding set BYTE-EQUAL to that head's pinned list (coverage 37/37; no new finding at an intermediate head) and, at the head that LANDS (c8T, and c9 when it exists), the tidy row GREEN with the list EMPTY — no NOLINT, no `.clang-tidy` change, no suppression anywhere; the macOS build and the five `-r xml` producers rc 0 at each Task 8b head. COUNT GATE REFUSES FAILURES (rev33): a case tuple with `failures` or `expectedFailures` above 0 is a STOP on either platform, never an admitted tuple move (impl-10's H0 carried `biv_tests` 419/0/0/3 → 483/1/0/3 as a move; the Linux producer gate was what refused it).
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
- HARNESS BYTES: `harness/**` bytes belong to TWO owners' commits only — m-3's harness commit (Task 8, arm-A shape; rev22: rev3's twelve paths, nine outside `harness/scenarios/` admitted by m-3's explicit line, population 1014 → 1055 declared, so Task 9 Step 4 measures a moved population and the `015244` series is the expected branch) and the selftest-pin recapture that the same-commit rule forces (which rides INSIDE the kind's product commit, as sub-step 1 did). ANY change to the pytest COLLECTED POPULATION at H (a new scenario's selftest; a new selftest test) fails the rev12 bar's C-2 BY CONSTRUCTION and the `015244` interleaved series (N = 10 per tree) RUNS INSTEAD (m-3 §6, m-4 035001) — Task 9 budgets it; it is not discovered at the gate. `src/adapters/**` bytes: ZERO (adapter-anchor rule; a touch routes UP and re-engages the companion-pin rule). `harness/bivharness/e3.py` pins: untouched.
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
  ENGINE (rev28, R-4.72; after c6p, before c7) c1d: src/core/repo/classify.cpp; tests/test_repo_engine.cpp (W-U1..W-U6)
                                           c1e: src/core/repo/git.{hpp,cpp}, src/core/repo/git_exec.{hpp,cpp}, src/core/repo/restore.cpp;
                                           tests/test_repo_engine.cpp (W-C1..W-C6 + W-C3s at the engine seam)
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
  R-4.65 FIXES (Tasks 6c, 6d; rev22)       c6m: src/core/open/open.cpp (execute_archive only); tests/test_open.cpp; tests/test_cli.cpp
                                           c6p: src/core/pack/pack.cpp; src/core/scan/scan.{hpp,cpp} (stat_node only; the `.biv` skip untouched);
                                           src/core/open/open.cpp; tests/test_scan.cpp; tests/test_pack.cpp; tests/test_open.cpp; tests/test_cli.cpp
  KIND (Task 6, contingent on A9's lock)   src/core/support/error.{hpp,cpp}; src/core/report/envelope.cpp (exit arm); src/core/scan/scan.cpp (the
                                           kind literal); src/cli/url_consent.{hpp,cpp} + src/cli/main.cpp (the rendered detail, one string two
                                           carriers); schemas/biv-exit-map.v1.json; tests/test_envelope.cpp (ExpectedRow + literal + TC-1..3 folds);
                                           tests/test_scan.cpp, tests/test_pack.cpp (the RAW core contract), tests/test_cli.cpp (the rendered CLI
                                           contract); harness/selftest/test_envelope.py pin
  HARNESS (Task 8, m-3's commit)           EXACTLY the twelve paths of m-3's rev3 patch (rev22): harness/scenarios/{d-git-restore.json,
                                           fxd3-open-offline.json,shells/d-git-restore.json}; harness/bivharness/{compare,manifest,scenario}.py;
                                           harness/schemas/manifest-repo-entry-shape-v1.schema.json; harness/selftest/{test_compare,test_manifest,
                                           test_probe_isolation,test_specs}.py; harness/tolerance/tolerance-v1.json — the nine outside scenarios
                                           admitted by m-3's explicit line (222346 / 124555 / 131146); authored at m-3's seat, applied verbatim
                                           as ONE commit; harness/bivharness/e3.py untouched
  LINUX REPAIRS (Task 8b; rev33)           c8L: tests/test_cli.cpp, tests/test_envelope.cpp, tests/test_open.cpp, tests/test_pack.cpp,
                                           tests/test_repo_git.cpp (the 53rd path, master 215035 R1), tests/test_scan.cpp — test-only;
                                           c8Tr: src/core/repo/restore.cpp ALONE (m-1's byte); c8T: src/cli/consent_display_table.hpp
                                           (REGENERATED by the tool, never hand-edited), src/cli/main.cpp, src/cli/url_consent.cpp,
                                           src/cli/url_consent.hpp, src/core/open/open.cpp, src/core/pack/pack.cpp, src/core/report/envelope.cpp,
                                           tests/test_cli.cpp, tests/test_open.cpp, tools/gen_consent_display_table.py — ten paths, inside the 53
  COUNT CELLS (Task 9 Step 5, iff moved)   .github/workflows/s2-harness.yml count cells ONLY
  DOCS LANE (host checkout, pair Planner)  docs/sprints/2026-08-27-intg-consent-fabric/** (this plan, receipts of record, census population)
ZERO BYTES:   src/core/repo/** beyond Task 1's c1a/c1b/c1c, rev28's c1d (Task 6e) / c1e (Task 6f) and rev33's c8Tr (Task 8b) at their fences; src/core/scan/scan.cpp's `.biv` payload skip (:140-142, V-2b-5 rev2); src/core/manifest/**; src/adapters/**; harness/bivharness/** and harness/selftest/** beyond m-3's c8 commit (Task 8: its twelve paths exactly) and the pin
              recapture the same-commit rule forces; src/core/open/render.cpp; every sealed design text; PROMPT A/B/C texts and predicates
              (A6-R6) beyond the V-A7-1 predicate substitution; build_preview / render_prompt_b (R-4.24)
Reads:        the sealed texts and owner fences listed above; the product at B by git object
Target entity: the two product verbs' engine reach (pack: discover → classify → eligibility → capture → repos[] + repos/<id>/… members;
              open: repos/ member class → restore_entry per row) with the consent fabric on every network-class path, both flags, the
              narrowed .git class, and the report carriers
Downstream consumer: m-1's byte review (V-2b-1..9 at H), m-3's byte review (§1 fence at H; the harness commit; c6m / c6p against 164214's V2-1..6 / V1-1..7, m-3.implementer's), m-4's cell-(v) review (E2
              re-derived, E5 re-executed at H), the Master Reviewer's packet, the operator's merge token, the golden harness (m-3 §5)
Contract:     the sealed orderings (pack-engine §1.1/§1.2/§1.3 — each repo unit's penumbra is payload — /§2/§3.2/§4; restore-apply §1/§2.2 incl.
              step 5 after materialization/§2.5/§5; A7-R3); the hook truth table; the two refusal
              grains never crossing (V-A6-5); the A8 policy inside the renderers; the D5.2 outcome vocabulary + offline-pointer; the narrowed
              .git class; every FX leg executed or its deferral REGISTERED with a named owner (S-6)
Proof:        the evidence matrix (§Evidence) — every row a receipt in the evidence home, cited by the merge packet
No-consumer action: an engine need beyond Task 1, Tasks 6e/6f and Task 8b's c8Tr, a RepoEntry ↔ schema mismatch, a network call that cannot flow through invoke_git, a new
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
c6b kinds: the nine A11 wire kinds (ErrKind 28→37 by membership; exit map 29→38; transitional 3→6; sentences; error objects; the      Task 6b  src/core/support/error.*, src/core/report/envelope.cpp, src/core/pack/pack.cpp, src/core/open/open.{hpp,cpp},
         open failed row + failed-mid-apply composition) — CONTINGENT on A11's lock                            src/cli/url_consent.*, src/cli/main.cpp, schemas/biv-exit-map.v1.json, tests/*, harness/selftest/test_envelope.py
c6m open: the directory-mtime pass after the LAST write into the partial (after restore_repos), before     Task 6c  src/core/open/open.cpp, tests/test_open.cpp, tests/test_cli.cpp
         fsync_tree — R-4.65 RED-2 in c4a (restore-apply §5); m-3 164214 RED2_ORCHESTRATION confirm (V2-1..6); T-RED2
c6q pack: each PAYLOAD-ONLY row's whole working tree archived as ordinary payload         Task 6q  src/core/scan/scan.{hpp,cpp} (claimed_markers, scan_subtree),
         (restore_invokes_git == false: N-R3/N-R4 shallow; A §A6 + H zero-ref unborn), its .git        src/core/pack/pack.cpp, tests/test_scan.cpp, tests/test_pack.cpp,
         claimed — R-4.70 in c5; m-1 225134 (C6P_MEMBER_SET: stop), master 011148; rev26             tests/test_cli.cpp
c6p pack+open: each repo row's penumbra written as payload members (pack-engine §1.1/§1.3/§3.2) AND laid     Task 6d  src/core/pack/pack.cpp, src/core/scan/scan.{hpp,cpp} (stat_node),
         after the row's restore_entry, every existing ancestor lstat'd and every absent one created one      src/core/open/open.{hpp,cpp}, tests/test_scan.cpp, tests/test_pack.cpp,
         component at a time (restore-apply §2.2 step 5, §2.5; m-4 arm A); ONE dot-git predicate at both        tests/test_open.cpp, tests/test_cli.cpp
         writers — R-4.65 RED-1 in c5 + R-4.69; m-1 141529 + m-3 164214 (V1-1..7); HOLDS on T-RED1 + T-C6P
c1d engine: classify records each remote's CONFIGURED url — the FIRST line of                    Task 6e  src/core/repo/classify.cpp, tests/test_repo_engine.cpp
         `git config --get-all remote.<name>.url` at both sites (never `remote get-url`, which
         applies insteadOf) — R-4.72 pack half; m-1 140916 §2 (R472_PLACEMENT in-lane,
         R472_MANIFEST_URL configured); engine-only, zero call-site bytes; HOLDS on the R-4.72 gate
c1e engine: every restore invocation bounded by GIT_CEILING_DIRECTORIES =                       Task 6f  src/core/repo/git.{hpp,cpp}, src/core/repo/git_exec.{hpp,cpp}, src/core/repo/restore.cpp,
         canonical(partial_root.parent_path()) — R-4.72 open half; m-4 144917 EC-1                         tests/test_repo_engine.cpp
         (R472_ENCLOSING_REPO ceiling), m-1 150702 §2 (R472_CEILING_PLACEMENT own-commit-in-lane);
         engine-only, zero call-site bytes; HOLDS on the R-4.72 gate
c7  tests: the re-execution of every open-side leg against product-packed images; FX-M-1 (d)
         + (a)-interactive; a6·1–13; a7·1–5; a8·5/a8·6; N (a)/(g); E3 witness — one commit; rev28: the PACK
         grain on REAL config (after c1d), the OPEN grain on the LABELLED shim, the ISO family (after c1e), E3 at pack
c8  harness: m-3's ONE harness commit (arm-A shape; authored at m-3's seat; applied verbatim)     Task 8   rev3's twelve paths exactly (harness/**; e3.py untouched)
c8L tests: every member the 2b structs gained named in the test initializers (GCC     Task 8b  tests/test_{cli,envelope,open,pack,repo_git,scan}.cpp
         -Werror=missing-field-initializers) AND the c3 hook called outside CHECK (the -r xml
         redirecting reporter) — ONE test-only commit (master 003436 cell (A)); the 53rd path (215035 R1)
c8Tr engine: restore's ceiling test seam as a function-local static (tidy non-const global)    Task 8b  src/core/repo/restore.cpp ALONE
         — behaviour-neutral; its own commit because veto 9 refuses a span (master 224030 Ask A)
c8T tidy: EVERY remaining clang-tidy finding of 2b's commits, behaviour-neutral, no          Task 8b  the ten paths in the boundary contract
         suppression — the 22 mechanical repairs, the owners' words B1–B6 (m-3 225029, m-1 224747)
         under m-4's conditions (225018), and the decoder witnesses with their .biv twins —
         ONE commit (master 003436 cell (B)); its head's tidy list EMPTY
c9  ci: count cells (IFF a case tuple moved at H0 on either platform) — committed INSIDE the       Task 9   .github/workflows/s2-harness.yml only
         Task 9 runner by cellpatch.py after both platform observations
c10 open: MUST-H-1 — a failed row's kind and detail rendered, never null (m-3 160359 F1–F5;       Task 8c  src/core/open/open.cpp, src/core/report/envelope.{hpp,cpp}, src/cli/url_consent.{hpp,cpp},
         master 164725's F4 widening): the divergence row carries UrlDivergenceEntryRefused and A6           schemas/biv-json-envelope.v1.schema.json, harness/selftest/test_envelope.py (the pin),
         :537's sentence; the schema admits both iff failed; a failed row lacking either is a typed          tests/test_cli.cpp, tests/test_envelope.cpp, CMakeLists.txt
         InternalError; rev39, after Task 9 completed at c9
c10t test: the two c10 failed-row initializers name every RepoOutcomeRow member (Linux GCC         Task 8d  tests/test_envelope.cpp only
         -Werror=missing-field-initializers; impl-14 231301; repair-13); rev41, after c10's head gate STOPped
c11 ci: count cells re-pinned (IFF a case tuple at the c10t head differs from c9's cells) —           Task 9b  .github/workflows/s2-harness.yml only
         committed INSIDE the re-gate block by cellpatch.py
ORDER RULE: c1a c1b c1c c2 c3 c4a c5 are the token's UNCONDITIONAL prefix (every one of them lands as a COMMIT with no working-tree residue — a
working-tree partial is not a history prefix; MUST-2B-14); c3h, c6a, c4b, c6b land AFTER c5 in the order their locks land (each its own
commit, each citing its lock id + doc sha256; c3h and c6a share A9's lock and land c3h then c6a); rev22: c6m then c6p land after c6b (R-4.65's two fixes,
each its own NEW commit, never a rewrite of c4a / c5; c6p HOLDS on T-RED1); rev26: c6q lands after c6m and BEFORE c6p (R-4.70,
due before c6p lands; its own NEW commit, never a rewrite of c5), and c6p also HOLDS on T-C6P; rev28: c1d then c1e land after c6p and BEFORE c7 (R-4.72; each its own NEW engine-only commit, each
HOLDING on the R-4.72 gate `$RUNNERS/r472-owner-words.txt`, m-1's re-ruled mechanical form); c7 lands after the LAST of them and after
c1e (its A9/A10/A11 legs need their bytes; its R-T and workspace-root legs need c6p's; its pack-grain M legs need c1d's and its ISO legs
c1e's); c8 after c7; rev33: c8L, c8Tr, c8T after c8 in that order (Task 8b; each head passes the per-head gate); c9 last of Task 9; rev39: c10 after c9 (Task 8c); rev41: c10t after c10 (Task 8d; ITS head passes the per-head gate — c10's head gate STOPped under impl-14 and `heads/c10/` stays as that record), then c11 iff moved (Task 9b), last. Veto 9 holds regardless of that order: none of c3h/c6a/c4b/c6b/c6m/c6q/c6p touches src/core/repo, and
c1d/c1e touch nothing outside it but tests/test_repo_engine.cpp; c8Tr touches src/core/repo/restore.cpp and nothing else, and c8L/c8T touch no
src/core/repo path.
H0 = the branch head after c8T (rev33: the last Task 8b commit; the object every suite observation and owner census is taken on); H = the FINAL head after c9 (== H0 iff no cell
moved); the runner proves `git diff H0 H -- . ':!.github/workflows/s2-harness.yml'` EMPTY so every H0 receipt carries to H, and writes H.txt LAST.
rev39: Task 9's H0 (`99136ca`, c8T) and H (`2893bc53`, c9) stand as EXECUTED under impl-12. The re-gate object is the c10 head (`R/H0.txt`), and the FINAL H is the head after c11 (== c10 iff no cell moved since c9), written LAST as `R/H.txt`; Task 9b proves `git diff c10 H -- . ':!.github/workflows/s2-harness.yml'` EMPTY. From rev39 the three owner byte reviews, the GO relay and the vehicle bind THAT H. c10 touches no src/core/repo path; c11 touches the workflow alone. rev41: the re-gate object is the c10t head (Task 8d) — `R/H0.txt` names c10t, the FINAL H is c10t iff no cell moved since c9, and Task 9b proves `git diff c10t H -- . ':!.github/workflows/s2-harness.yml'` EMPTY; c10t touches `tests/test_envelope.cpp` alone.
The three owner byte reviews, the GO relay and the vehicle bind H. NO commit touches both {src/core/repo} and {src/cli, src/core/pack,
src/core/scan, src/core/open}.
```

## Evidence matrix (claim-by-claim; every row = a receipt file in the evidence home; the packet cites rows, never prose)

```text
row    claim / leg                                   where executed                   provenance            tier   verifier of record
E1-M   FX-M-1 (a)–(o): the PACK grain on REAL config  Task 7 (pack: real config after   product-packed; open  E2     lane executes; m-4 verifies grep-derived counts; m-1 re-derives the seam fourteen as floor
       (after c1d); the OPEN grain on the LABELLED    c1d; open: the labelled shim)    grain detection=shim
       shim, never cited as product detection (rev28, R-4.72: m-4 140901 (ii), EC-3; m-3 150622 W-1s)
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
       non-interactive ⇒ url_divergence_refused naming BOTH addresses — AT THE PACK VERB (rev28: m-4 140901 rebinds E3 to pack; the
       open grain is the ISO family + the labelled shim, EC-3)
WIT-U  W-U1..W-U6 (R-4.72 pack half, c1d): the        Task 6e (engine) + Task 7 (pack) unit → product-packed E2     m-1 140916 §2; m-4 (SR-URL-5's property, 140901)
       CONFIGURED url recorded under a local rewrite and a global one; the no-rewrite control; a multi-valued url's FIRST value; the
       unborn-with-refs site; a url-less remote typed; named mutants `config --get` (W-U4) and `remote get-url` (W-U1)
ISO    the open isolation family (R-4.72 open half,  Task 6f (engine seam) + Task 7   unit → product-packed E2     m-4 144917 EC-1..EC-4; m-1 150702 §2; m-3 150622
       c1e): W-1′ = W-C1 the inverted enclosing-repository RED witness (rc 0, the recorded url, no prompt / row / notice; NAMED MUTANT
       the ceiling omitted ⇒ the refusal returns), W-C2 the enclosing .git checksum-equal, W-C3 the symlinked destination, W-C4 the
       control, W-C5 the pack-side negative, W-C6 the typed failure with zero spawns, W-C3s the emitted value at the seam, W-2 a
       temp-HOME global rewrite without effect, W-4 the recorded url unchanged, W-5 the accept flag inert; EC-4's other half is c6p's
       FP1/FP2 (the dot-git refusal at both writers) — named here, cited from R1-P, never re-run
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
R2-M   RED-2 (rev22): a payload directory above a   Task 6c (CLI)                    product-packed        E2     m-3 (V2-1..6; m-3.implementer's byte review at H)
       restored repository keeps its archived mtime (restore-apply §5); RED at the c6b head (the named mutant = the pre-fix order), GREEN at c6m;
       the --offline twin green at both; the source-order oracle names the pass between restore_repos and fsync_tree
R1-P   RED-1 (rev22): each repo row's penumbra is   Task 6d (pack unit + CLI) → Task 7  product-packed; H1–H4 hand-built  E2  m-1 141529 (pack half); m-3 (V1-1..7); m-4 (V1-3)
       payload (member sets EXACT, non-root and root) and is restored after the row's restore_entry with byte/mode/mtime fidelity (network + --offline
       twin + repo under a payload dir + root row under T-RED1 `defer`); V1-3 containment, V1-4 no-overwrite, V1-2 parent-before-child order on
       HAND-BUILT images (labelled; pack cannot produce them at 2b); named mutants: c5's pack (absent), first-pass placement (two forms), the
       ancestor check following links, no existence check; rev26 (T-C6P): below-row creation deleted (m-4 w1), the dot-git fold made exact
       (F-C6P-1), each writer's predicate call, row_relpaths admitting payload-only rows, penumbra re-derived for a payload-only row
R2-Q   R-4.70 (rev26): each payload-only row's    Task 6q (scan unit + pack unit    product-packed        E2     m-1 225134 (owner, due before c6p); master 011148
       WHOLE working tree is payload (member set     + CLI) → Task 7 N (a)
       EXACT with multiplicity, non-root and ROOT — no bare payload/; .gitignore does not prune it; .git claimed) and returns byte/mode/mtime-equal with and without --offline, zero
       git on open; RED at the c6m head (the named mutant = c5's unconditional boundary exclusion)
E1-A10 A10.4 legs (a)–(m): D3 notice/prompt before  Task 4 (interim, c4b) → Task 7   hand-built → product  E2     m-3 (A10 at its lock); m-4 cell (v) (hostile-output surface)
       any git; decline ⇒ offline-pointer rows exit 0; --network; --json parity; --offline never; PROMPT D untouched; the rows; hostile
       URL bytes; the born/unborn/detached reconstruct idioms run into both target states (j); exact argv under the single-quote rule
       (k); the fallback for non-copy-safe operands (l); offline-unborn sha (m); the durable artifact (RCPT-Q)
E1-A11 A11.5 legs (a)–(l): the three fences, unmerged, Task 5 (seam, c5) → Task 6b (kinds) → Task 7  product-packed / shim  E2   m-3 (A11 at its lock); m-1 §1/§3 (grain); m-4
       ref-uncapturable, promisor both arms, git failed pack/open, budget, restore failed, op absent, unknown stays InternalError, counts
RCPT-Q the Q13 durable artifact: after open --offline   Task 7                           product-packed        E2     m-1 074712 §2 (apply half); m-3 A10.6 (UX half)
       <dest>/.biv/repos/<id>/repo.bundle exists for every ARTIFACT-BEARING row (offline-pointer ∧ artifact presence), checksum == checksums.json's, absent for every other row; zero git
CG     count gate: observed case tuples at H0 == the  Task 9                           both platforms        E2     m-3's pin rule
       workflow cells at H (after c9 iff a cell moved); skip sets unchanged (a changed skip set is a STOP, never a re-pin)
CEN    census FOR the merge head (R-4.49 instrument)  Task 12 (POST-merge; Task 11 =    main's post-merge head E2    Master Reviewer; the operator's token
       the pre-merge rehearsal at H0 + declaration)
VETO9  git log --reverse order + no-span check        Task 9 Step 2                    H                     E1     m-1
RPC    RepoEntry production census (V-2b-4): the      Task 9 Step 2                    H0                    E1     m-1
       TYPE-SCOPED census — every RepoEntry-typed binding outside src/core/repo enumerated, zero member writes on any of them; with a
       true-write mutant control (fires) and an unrelated-type write control (does not)
C2H    the C-2 hunk byte-identical to a2f6fd1's       Task 9 Step 2                    H                     E1     m-1 (V-2b-2)
HG     per-head gate (rev33): canonical container rc  Task 8b (c8L, c8Tr, c8T); Task 9 each new head         E2     m-3 (toolchain), m-1 (c8Tr), m-4 (read)
       0; the tidy set byte-equal to the head's pinned list (coverage 37/37); macOS build + five -r xml producers rc 0, failures=0;
       tidy GREEN at H0 and, when c9 exists, at H (`heads/<label>/headgate.txt`, `H/tidy-H0.txt`, `H9/c9-gate.txt`)
MUT    the ruled witnesses and mutants (rev33):       Task 8b (c8Tr and c8T heads)     c8Tr, c8T             E1     m-1 (c8Tr, B5, B6), m-3 (B4), m-4 (C-U1..C-U4)
       W-C6 GREEN with Mc5 and M-SEAM RED at c8Tr; at c8T M-MASK, minimum, M-SEC, B6-swap RED (gating), truncation and B5-bix recorded;
       B1's header reproduced by the tool (`receipts/c8Tr-mutants.txt`, `receipts/c8T-mutants.txt`, `receipts/c8T-b1-regeneration.txt`)
PRV    an earlier Task 9 attempt preserved (rev33;   Task 9 (its first act)          the evidence home     E1     the implementer's exact-hash review
       rev36 adds its B leg): H/, H0.txt, helpers.verify-9.txt and every B/ entry outside Task 0's fifteen renamed through a stage into
       attempts/task9-H0-<H0:7>/ (impl-10's a83657e, impl-11's 99136ca), manifest-verified (`H/preserved-attempt.txt`)
R477   harness-selftest variance (R-4.77): the        Task 9 Step 4                    B and H0              E2     m-3's word at the GO; m-4 CC
       interleaved series ALWAYS runs, N = 10 per tree, per-test frequencies (`H/selftest-series.txt`)
```

## File structure (what each new or modified unit is responsible for)

- `src/core/repo/eligibility.hpp/.cpp` — `run_eligibility(git, entry, EligibilityMode)`; `EligibilityMode::offline` short-circuits every network call (COND-6) on the born non-shallow lane it binds (after the unborn/shallow return), forces full + `offline_declared` there, and refuses a promisor source through the engine's `promisor_objects_unavailable` class (R-4.1 arm (i) HOLD as m-1 recorded it).
- `src/cli/consent_display_table.hpp` (GENERATED) — the sorted table of scalars in `Cf ∪ Zl ∪ Zp ∪ Default_Ignorable_Code_Point` at Unicode 15.0.0 as `constexpr` `[first,last]` ranges + a header comment carrying the Unicode version, the two input files' sha256 and the generator's sha256. `tools/gen_consent_display_table.py` — the generator (inputs: `UnicodeData.txt`, `DerivedCoreProperties.txt`; deterministic output).
- `src/cli/url_consent.cpp` — gains `consent_display(std::string_view) -> std::string` (ONE consent-local encoder reproducing A8-R1 clauses 1–5 — `sanitize_utf8`, the three visible escapes, `\u00xx`, the clause-5 table, pass-through — the shared `display()` untouched) and routes EVERY bound placeholder of the four A8-R2 renderers through it exactly once; templates byte-unchanged. Gains the m-3-cut renderers of A9 (`render_unclaimed_git_entry_detail`, `render_offline_header`, `render_offline_row`; `render_offline_bundle_line` only under T-STAGE's word) so every m-3 template byte in the product lives in ONE file and every bound value passes the encoder ONCE (m-3's (ii) census widens from four renderers to seven or eight; stated, not hidden).
- `src/cli/args.hpp/.cpp` — `Command.offline`, `Command.network`; parse on the verbs m-3 §4 names; `collision`-style conflict rule → `usage("conflicting-flags")`; open help gains the two lines before `  --accept-url-divergence`.
- `src/cli/main.cpp` — `install_url_divergence_hook(...)`: builds the `UrlDivergenceRun`, the hook per the truth table, the stderr notice writer; wraps the verb's engine-reaching call in `ScopedUrlDivergenceRun`; converts run results into the report carriers; emits per-entry refusal lines + the guidance line (open) and the pack refusal detail (pack); the D4 listing (open `--offline`); B's predicate dedup.
- `src/core/open/open.hpp/.cpp` — `OpenOptions.offline`; the `repos/` member class in `read_archive_plan` (V-2b-7) staged under `<dest-parent>/<name>.bvpk-open.stage/`; `restore_entry` per row in §2.2 order after payload apply, inside the partial dir; `OpenReport.repos` (rows) + the refusal rows; offline: no `restore_entry`, `offline-pointer` rows from the manifest alone. (rev22) c6m: the directory-mtime pass after the last write into the partial, before `fsync_tree`. c6p: a `payload/` member OWNED by a repo row (`owning_row`: the DEEPEST row whose relpath is a PROPER whole-segment prefix of the member path — the root row `""` owns every member it contains, under T-RED1's `defer`) is drained and checksum-verified in `apply_archive`'s first pass but NOT written; `apply_owned_members` lays that row's members after the row's outcome in `restore_repos` (restored, offline-pointer, shallow-pointer, payload-only-unborn, url-divergence refusal), lstat-walking every component from the partial root (a symlink or non-directory ⇒ `MemberPathUnsafe`, nothing written), creating a missing component of the row's own relpath one directory at a time (never stamped), refusing an existing final path (`MemberPathUnsafe`), through the SAME member writer as the first pass (modes, symlinks, mtimes, checksum ⇒ `IntegrityFailureMidApply`), each member counted once in `restored_member_count`.
- `src/core/report/envelope.hpp/.cpp` — `machine_text(std::string_view) -> std::string` (= the landed `support::sanitize_utf8`: valid UTF-8 byte-exact, malformed content visibly replaced, NO display escape) applied at EVERY emission of a bound value the A8 census names — `error.path`, every `error.facts` value, the four fields of each `url-divergence-accepted` entry, the five fields of each `url_divergence_refusals` row — the memo/decision bytes in memory untouched (A8-R1 machine-carrier census + the malformed-value arm); `UnclaimedGitEntry` exit arm (Task 6); `result.repos[]` rows ONLY under T-JSON's word; `result.manifest.repos` stays the landed EMPTY array (RECONCILE R4 I2B-09 option (b); registered, not silent).
- `src/core/scan/scan.hpp/.cpp` — `scan(source_root, const ScanExclusions&)`: repo subtrees excluded from the payload walk (V-2b-5) — rev26: the subtrees of GIT-CAPABLE rows only; a PAYLOAD-ONLY row (`restore_invokes_git == false`) has its `.git` marker claimed (`claimed_markers`) and its subtree walked like residue by `scan_subtree` after capture (c6q, R-4.70); a `.git`-named entry that is a discovered boundary's marker is skipped (never a payload node); a `.git`-named entry NOT claimed → the narrowed typed refusal (V-2b-6; kind per Task 6).
- `src/core/pack/pack.hpp/.cpp` — `PackOptions{offline}`; the sealed order (V-2b-3); leaves-first capture; artifacts as members at `archive_path` verbatim; `manifest.repos` = the entries whole; engine `url_divergence_refused` → `ErrKind::UrlDivergenceRefused` (path = repo; facts requested/effective/op); every other engine issue surfaces through today's engine-error path. (rev22, c6p) `penumbra_nodes`: each classified row's penumbra — the engine's `penumbra_paths` minus `.bivignore` matches, minus deeper rows' subtrees, minus `.biv` directories — joins `scan_result->payload` as ordinary members at `payload/<relpath>/<path>`, plus each directory STRICTLY inside the row that is an ancestor of an emitted member and holds no file or symlink outside the row's `penumbra_paths` (T-RED1's `RED1_PENUMBRA_DIRS`; never the repo root); parents before children; the scan's whole-subtree exclusion is unchanged.
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
         planned here AS TERMS from the revision this plan TRANSCRIBES (A9 rev2 40eaea22 — LOCKED; A10 rev10 6cba59d3 — LOCKED; A11 rev11 fce9cbfa — LOCKED; rev20 transcribes the rev6→rev10 / rev5→rev11 deltas) and are re-verified
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
T-JSON   RULED → RELEASED (Q9, m-3 075225; A10 rev10 §A10.1, LOCKED 6cba59d3 → c4b) — `result.repos`: an ARRAY present iff ≥ 1 manifest repos[] row was
         processed, ABSENT at zero state (never []); `result.manifest.repos` UNCHANGED; rows = RepoRestoreRow (restore.hpp:28-37) VERBATIM —
         id, relpath, outcome ∈ restored | shallow-pointer | payload-only-unborn | failed | offline-pointer, sha (40-hex or null),
         capture_mode OUTCOME-CONDITIONED (A10.1 rev10, m-1's W-1): the enum overlay | full on restored / failed / offline-pointer rows, NULL on
         shallow-pointer and payload-only-unborn rows — what the image records (manifest-format π_repo), never the in-memory default `full`;
         local_refs[] {ref, recreated, skipped_at_sha, detail?}, advisories[], shallow {boundary[]} iff
         shallow-pointer; `failed` rows ADD kind (an A11 wire kind) + detail; `offline-pointer` rows ADD branch | "(detached)", remotes[],
         bundle_path? and reconstruct? (ARTIFACT-BEARING ROW := outcome offline-pointer AND the engine's artifact-presence fact — entry.bundle set AND
         the member in checksums.json — NEVER keyed on capture_mode; bundle_path PRESENT on every artifact-bearing row, reconstruct PRESENT on it
         iff copy-safe, BOTH ABSENT on every other row: overlay offline-pointer rows and every engine-returned row whatever its mode; V-A10-8); manifest order; the schema row in the
         SAME commit as the first rendering (V-A6-3; R-4.32) with the selftest pin recomputed; V-A10-5 (no empty array; no field outside the
         set; no failed row without an A11 kind; a non-null capture_mode on a shallow-pointer / payload-only-unborn row or a null one on any other
         row — V-A10-8 rev10). The schema row types capture_mode as string-or-null over the two enum words. Task 4 c4a keeps the rows IN MEMORY
         only; c4b emits them.
T-STAGE  RULED → RELEASED (Q13, m-1 074712 §2 apply half + m-3 A10 rev10 §A10.6 UX half at 6cba59d3 — LOCKED → c4b) — THE INTERIM IS OVER:
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
         bundle_path, <branch>, <sha>, the constant refspecs (the two wildcards on every form; the bare 'HEAD' as well on the detached form) —
         SINGLE-QUOTED on the RAW bytes (an opening ', every ' replaced by
         '\'' , a closing '); nothing unquoted except the fixed words (cd, &&, git, init, --initial-branch=, fetch, --update-head-ok,
         checkout, --detach). COPY-SAFE iff every operand is valid UTF-8 AND A8-R1 is the IDENTITY on it (no C0/C1 control, no DEL, no
         Cf/Zl/Zp/Default_Ignorable code point); the printed line, the JSON reconstruct and what sh hands git are ONE byte sequence.
         FORMS — ONE idiom for EVERY target state (absent, empty, non-empty; `git init '<target>'` creates or re-uses the directory),
         selected ONLY by the row's stored HEAD state (a manifest fact):
           born      git init --initial-branch='bvpk-restore' '<target>' && cd '<target>' && git fetch --update-head-ok '<bundle>' '+refs/heads/*:refs/heads/*' '+refs/tags/*:refs/tags/*' && git checkout '<branch>'
           unborn    git init --initial-branch='<branch>' '<target>' && cd '<target>' && git fetch --update-head-ok '<bundle>' '+refs/heads/*:refs/heads/*' '+refs/tags/*:refs/tags/*'
                     (sha is "(no commits)": NO checkout — HEAD stays the symbolic unborn '<branch>' with no HEAD object; sealed G / W-O2)
           detached  git init --initial-branch='bvpk-restore' '<target>' && cd '<target>' && git fetch --update-head-ok '<bundle>' 'HEAD' '+refs/heads/*:refs/heads/*' '+refs/tags/*:refs/tags/*' && git checkout --detach '<sha>'
                     (rev8, LOCKED: the bare 'HEAD' refspec — the sealed `--all` capture of a repository detached at a commit no branch or tag
                     names advertises HEAD ALONE (`git bundle list-heads` = exactly `<sha> HEAD`); the two wildcards then import nothing (fetch
                     rc 0, `checkout --detach` fatal — the Master Reviewer's 192826); 'HEAD' imports the recorded commit into FETCH_HEAD, a
                     fetch artifact, not a ref; when a branch or tag names the commit the extra refspec changes nothing)
         `git clone` is printed for NO row (it cannot target a non-empty directory and maps carried refs into refs/remotes/origin/).
         LINE — one per ARTIFACT-BEARING row (A10.1: offline-pointer AND the artifact-presence fact; never keyed on capture_mode), AFTER all
         listing rows (A9.4's slot), one of:
           command   <relpath>: <reconstruct>   (partial/manual reconstruction — not a full restore)
           fallback  <relpath>: bundle at <bundle_path> — no copy-paste command: the path or branch carries characters a shell line cannot carry faithfully; reconstruct by hand from the bundle   (partial/manual reconstruction — not a full restore)
                     (values in the fallback are DATA per A8-R1; the JSON row carries bundle_path and NO reconstruct)
         NEVER a stored URL in either form; a display escape in a command; a command for a non-copy-safe operand; a product refusal
         because a path is not copy-safe. OTHER ROWS — no bundle_path, no reconstruct, no bundle line: overlay offline-pointer rows and every
         engine-returned row (a preserved N/H row, a restored row), whatever mode the row bytes carry. SUPERSESSION: A10 IS LOCKED (6cba59d3),
         so these lines NOW replace A9.4's bundle template and its "one line per full-image row" — one command-or-fallback line per
         artifact-bearing row; bundle_path on every artifact-bearing row, reconstruct iff copy-safe (the Master Reviewer's boundary 182105:
         the supersession takes effect at this lock, one golden, never two; before it A9.4's D4 header/row bytes were the golden). V-A10-7/8. rev5's "drain + verify, never materialize" routing stands at c4a (its pre-created-
         file discriminator too); c4b adds the durable placement + the command-or-fallback line + the two row fields.
T-NET    RULED → RELEASED (Q8, m-3 075225; A10 rev10 §A10.2, LOCKED 6cba59d3 → c4b) — `--network` is NOT inert: A2 D3 EXECUTES at 2b (the first act where
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
         promise, per-step inventory) — NO per-entry divergence/2 arm for engine failures; COUNTS by STAGE and MEMBERSHIP (A11 rev11, LOCKED): at the pin 186adf7d ErrKind 28 / exit map 29 / transitional 4;
         after A9 28 / 29 / 3; after A9 + A11 ErrKind 37 (= the pin's 28 − RepoDiscoveredUnsupported + UnclaimedGitEntry + the nine) / exit
         map 38 / transitional EXACTLY the six { SourceUnreadableSubpath, UnsupportedFileTypeSkipped, UsageError, RepoDirtyUnsupported,
         RepoNestedUnsupported, RepoSubmoduleUnsupported }, refusal/3 rows 14 → 20, mid-fail/4 rows 4 → 7, divergence 7, advisory 3,
         usage 1, the InternalError row UNCHANGED — each a SET, the size a consequence (rev7's 36 / seven must FAIL the census); UNKNOWN
         engine kinds STAY InternalError (never mapped by guess); error objects per A11.2 (common: error.kind = the wire kind, errno 0,
         facts.repo_engine_kind kept, error.detail = the A11.3 sentence encoded ONCE at the renderer — one string, both carriers);
         sentences per A11.3 VERBATIM (one line each; `<op>` = the engine's op fact or the word `call`; `[, offline]` iff facts.offline
         is "true"; `<N-3> more` iff N > 3); the open-side failed row (A10.1) carries kind + detail = the same sentence; the enum,
         to_string, the exit-map rows, the envelope arm and the tests land in ONE commit (V-A11-4; R-4.32); the selftest pins recomputed
         in it. url_divergence_refused stays as A6 sealed it (A11.6 (2)).
A10-REV  A10 is LOCKED at rev10 (`m3-addendum-10-6cba59d3-lock-20260920`: pin 6cba59d3 @ pdc 5cbb59d7, post-stamp 56abe662; m-3 184029, seal
         185625; rev6 17fda846 was the revision rev19 transcribed) — the c4b bytes bind at THIS lock and are quoted here from rev10: the D3 TRIGGER = ∃ row with `restore_invokes_git(row) == true` (the ENGINE'S
         predicate, c1c, READ never recomputed; S-A10-1 if the export is absent); DECLINED = the `--offline` partition on that predicate
         (FALSE ⇒ CALL restore_entry — no git UNCONDITIONALLY, through success or a typed error: shallow-pointer per N-R4 identical
         with/without the flag, payload-only-unborn per H, no artifact; TRUE ⇒ offline-pointer row, artifact iff `entry.bundle` ∧ checksums
         membership, sha 40-hex or "(no commits)" iff unborn — never null; fence rev4's git-capable contract); reconstruct = a RENDERED COMMAND for POSIX sh, every operand SINGLE-QUOTED on the raw bytes, emitted ONLY when copy-safe
         (valid UTF-8 and A8-R1 the identity on every operand), else the FALLBACK line and no JSON `reconstruct`; ONE idiom for every
         target state selected by the stored HEAD state: born `git init --initial-branch='bvpk-restore' '<target>' && cd '<target>' &&
         git fetch --update-head-ok '<bundle>' '+refs/heads/*:refs/heads/*' '+refs/tags/*:refs/tags/*' && git checkout '<branch>'`;
         unborn `git init --initial-branch='<branch>' '<target>' && cd '<target>' && git fetch --update-head-ok '<bundle>' '+refs/heads/*:
         refs/heads/*' '+refs/tags/*:refs/tags/*'` (no checkout — the symbolic unborn HEAD with no object; MUST-2B-16 CLOSED with a form);
         detached `git init --initial-branch='bvpk-restore' '<target>' && cd '<target>' && git fetch --update-head-ok '<bundle>' 'HEAD'
         '+refs/heads/*:refs/heads/*' '+refs/tags/*:refs/tags/*' && git checkout --detach '<sha>'` (rev8: the bare 'HEAD' refspec — a HEAD-only
         bundle imports nothing under the wildcards alone); `git clone` is printed for NO row; A9.4's bundle template SUPERSEDED at this lock;
         capture_mode OUTCOME-CONDITIONED (rev10, W-1): the recorded enum on restored / failed / offline-pointer rows, null on shallow-pointer /
         payload-only-unborn rows, never the in-memory default; ARTIFACT-BEARING := offline-pointer ∧ artifact presence (rev7), never keyed on
         capture_mode; A10.2's `--json` / PERSISTENCE / ENCODING rows regained (rev7) — T-NET's `--json` mirror, no persistence, A8-R1 on every value.
ROUTED   the three A10/A11 findings of 085404 are SETTLED by their owners (each binding at its lock): (15) A10 §A10.6 — POSIX sh,
         single-quoted raw operands, copy-safe predicate, fallback line (rev4+, approved at rev5 132531; LOCKED at rev10 with the detached form's bare 'HEAD' refspec, rev8); (16) A10 rev5 §A10.6 — the unborn
         idiom (`git init --initial-branch='<branch>'` + `fetch --update-head-ok`, no checkout) witnessed on git 2.50 (approved at rev5);
         (17) A11 rev11 (LOCKED fce9cbfa) OPEN INVARIANT — master's ruling (b): the landed `result` null iff `error` invariant is KEPT; the orchestrator
         writes `<partial_dir>/inventory.json` (`<partial_dir>` = `<target>.bvpk-open.partial`, the ONE partial-directory path T-PARTIAL authorizes — A11 rev11 spells it at its three sites and derives it from the lock file's `partial_suffix` field, m-1's ruling 162306; completed rows, the failing row with kind + detail, the outcome, §2.2 order);
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
         → POST 9e456b4d…, 9/0, zero lines removed); the rename-map row is master's to annotate; A11 rev6 (LOCKED at rev11 fce9cbfa) spells
         `<target>.bvpk-open.partial` at its three sites and its SUFFIX paragraph names 162306 and the lock-file fields — done. THE WORD ARRIVED
         as TWO fields in $RUNNERS/m3-addendum-11-lock.txt (written 2026-09-20) — `partial_suffix=.bvpk-open.partial` (the only admissible
         value) and `partial_suffix_relay=master/relays/intg-2b-wiring-act/DESIGN-planner-20260918-162306.md` (arm 1, the owner ruling by
         bytes; the lock relay 184104 declares the field too; master's seal spells the path without `master/relays/` — the FILE carries the
         plan's pdc-relative form the block resolves) — and Task 6b Step 0 fails CLOSED without
         both. CONSUMPTION (one spelling, one site): the suffix is spelled at exactly ONE site in the product — the `partial_dir` expression
         at open.cpp:637 at B (:785 at 1065872; whose literal must equal `partial_suffix`; c6b does NOT touch it); the inventory writer receives the `partial_dir`
         VALUE from that expression (`<partial_dir>/inventory.json`); `facts.partial_path` is `partial_dir.generic_string()` (the landed
         `with_partial_dir` pattern, open.cpp:354-356 — the fact renamed per A11.2); the `OpenPartialPresent` detection (open.cpp:638) and
         any clean-up reader test the SAME value; leg (h)'s witness derives its expected path as `<dest-parent>/<dest-name>` + the
         `partial_suffix` READ FROM THE LOCK FILE, never a literal in the test. The lock file carries both fields (Task 6b Step 0 binds them — walked at this seat on the real file: pre + post PASS); every c6b
         open-composition byte names the suffix only through the `partial_dir` value.
T-RED2   SEALED + CONFIRMED (rev22; R-4.65 RED-2 in c4a `ef8e492`; m-1 141529 §3; m-3 164214 with its face line 164238
         `RED2_ORCHESTRATION: confirm`, carried by master 165137 — 164214 is the text of record): restore-apply §5 ("payload members DO
         preserve archived mtimes") determines it; c6m moves the directory-mtime pass after the LAST write into the partial and before
         `fsync_tree` under V2-1..6. No gate file — the word is complete; c6m proceeds after c6b.
T-RED1   SEALED for the pack half and the non-root open half; HOLD on two cells (rev22; R-4.65 RED-1 in c5 `5aeb81c`). pack-engine
         §1.1 / §1.3 / §3.2 and m-1's 141529 §2 determine the file members (the row's `penumbra_paths` minus `.bivignore` matches, minus
         deeper rows' subtrees, minus `.biv` directories, at `payload/<relpath>/<path>`, ordinary metadata); restore-apply §2.2 step 5 and
         m-3's 164214 (`RED1_OPEN_PLACEMENT: confirm`, V1-1..7) determine the open half for NON-root rows. THE TWO CELLS (the pair
         Planner's `intg-substep2b/SITREP-pair-planner-20260921-170128.md`, routed through master): (a) `RED1_ROOT_ROW` — V1-6 keeps the
         root row out of 164214, and under the kept order it reds two ways by reading: a penumbra file inside a TRACKED directory needs
         that directory as an image member for the first pass (`contained_output_path`), and a file ignored only by the source's
         `.git/info/exclude` or the packer's global excludes is laid BEFORE the root checkout and fails its worktree verification
         (`restore.cpp:366-373`). c6p is planned under `defer` — the root row joins the deferred placement (§2.2 step 5 is per
         repository; at a root row every payload member is that row's penumbra). (b) `RED1_PENUMBRA_DIRS` — the directory members:
         each directory STRICTLY inside the row's relpath that is an ancestor of an emitted member and holds no file or symlink outside
         the row's `penumbra_paths`, never the repo root — the filesystem form of "not an ancestor of a tracked path" for an Arm-1
         clean repository (m-1's acceptance test exempts exactly the other directories; V1-4 forbids a member where git made the
         directory). GATE FILE `$RUNNERS/red1-owner-words.txt`, written by the pair Planner ONLY from master's carry, three lines (rev24; rev26 rewrites it to SEVEN — T-C6P),
         pdc-relative: `carry_relay=` (master's relay, TO intg.pair-planner, citing both), `m3_relay=` (FROM m-3.planner, the WHOLE line
         `RED1_ROOT_ROW: defer` exactly once and no other `RED1_ROOT_ROW:` line), `m1_relay=` (FROM m-1.planner, the WHOLE line
         `RED1_PENUMBRA_DIRS: confirm`, likewise). Task 6d Step 0 binds all three by bytes (rev26: with T-C6P's four). Any other word ⇒ a new plan revision; c6p
         writes NO byte before the gate passes; `resume.sh` carries the file. THE WORDS ARRIVED (rev24): m-3 `master/relays/intg-2b-wiring-act/DESIGN-planner-20260921-200917.md` (`RED1_ROOT_ROW: defer`) and m-1 `…/DESIGN-planner-20260921-200936.md` (`RED1_PENUMBRA_DIRS: confirm`, the RECURSIVE reading above, checked by m-1 against `git clone file://` ground truth), carried by master `…/PLAN-master-planner-20260921-211701.md` — the gate file's three fields. They bind c6p beside V1-1..7: m-3's V1-8 (the root row is the shallowest owner; `--offline` or any root outcome running no git lays its members at `.` with no git), V1-9 (the root's `verify_restored`, its `.biv-stage` exclusion and its EMPTY-status requirement byte-identical and still BEFORE the placement — `src/core/repo/**` carries no c6p byte), V1-10 (the deferred writer refuses `MemberPathUnsafe`, nothing written, any member with a `.git` path segment), V1-11 (`.biv/` untouched — the A10.6 artifact, the exclude line, the stage keep their writer and order; a `payload/.biv/…` member is refused by the deferred writer), V1-12 (the joint root witness and its mutants, Task 6d Step 1); m-1's DIRECT-reading mutant on its fixture (Task 6d Step 1 (b) DIRS). Both owners closed the verification-order point (the pre-penumbra empty-status check is the Arm-1 execution of §2.2's 5→6; R-4.57's arms) and registered, as NOT c6p conditions, empty directories inside a repository not carried and `exclude-rules-local` emitted nowhere (m-1, due before the release gate); m-3's first-pass `.git`-segment observation is m-4's, not this plan's (rev26: m-4 answered it and master ruled it rides c6p — T-C6P (d)).
T-C6P    BOUND (rev26; R-4.69 + R-4.70): the three c6p words carried by master `master/relays/intg-2b-wiring-act/PLAN-master-planner-20260923-011148.md` (TO intg.pair-planner,
         citing all three): m-4 `master/relays/intg-2b-wiring-act/DESIGN-planner-20260922-225418.md` — the WHOLE line `C6P_ABSENT_ANCESTOR: arm-a`;
         m-3 `…/DESIGN-planner-20260922-225041.md` — `C6P_V1_READING: confirm`; m-1 `…/DESIGN-planner-20260922-225134.md` — `C6P_MEMBER_SET: stop`.
         WHAT THEY BIND. (a) m-4, ARM A: the deferred writer MAY create a missing ancestor, with (AA-1) exactly the row-component primitive —
         ONE `create_directory` per component, never `create_directories`, only after that component's parent was lstat-verified a real
         directory in the same walk, and a create reporting not-created or an error is a REFUSAL, never a re-check-and-continue; (AA-2) the
         segment refusals run before the walk, every EXISTING ancestor is lstat-checked (symlink or non-directory ⇒ `MemberPathUnsafe`, V1-3)
         before any creation, V1-4's final-path ENOENT unchanged; (AA-3) THE PRECONDITION (F-C6P-1, live at the impl-6 candidate: its `.git`
         refusal is byte-exact, and on macOS's case-insensitive volume `payload/<row>/.GIT/hooks/<name>` walks into the restored `.git`): V1-10's
         refusal becomes ONE shared predicate with git's semantics as prior art, applied UNIFORMLY on every host, never gated by configuration
         or a filesystem probe, and the same fold for V1-11's `.biv` — the exact clauses are Task 6d's Interfaces, transcribed from git
         `3bc0341126508f78f5869cbfc0005e987efdf0c7`; the one accepted cost (m-4's, named): an untracked penumbra directory genuinely named `.GIT`
         on a case-sensitive host now aborts its open loudly; (AA-4) five single-coordinate witnesses — w1..w5, Task 6d Step 1 (d) W2/W3/W5
         with H1 as w4 and Step 4's M9 as w1; w2 and w3 run on the case-insensitive macOS leg AND the Linux leg, asserting refusal on each.
         (b) m-3, CONFIRM: V1-2 licenses no git at a non-materialized row; V1-3's refusals are a symlink and an EXISTING non-directory only —
         the absent-ancestor refusal of rev22..rev25 was the pair Planner's own and is WITHDRAWN; at a non-materialized row the relpath
         ITSELF is absent too, so the creation covers every absent component between the partial root and the member's parent — the row
         relpath's own and those below it alike; a created directory takes no invented mtime (V2-3); V1-1..12 unchanged. (c) m-1, STOP — the
         member set moves by sealed text (ADDENDUM-N N-R3/N-R4 on N3; ADDENDUM-A §A6 :194 with H): a PAYLOAD-ONLY row
         (`repo::restore_invokes_git(entry) == false` — `shallow`, or the zero-ref unborn shape; the engine's own partition) archives its
         WHOLE working tree as ordinary payload and restores it through the first pass with zero git (Task 6q, c6q, R-4.70, owner m-1, due
         BEFORE c6p lands); a GIT-CAPABLE row keeps 200936's recursive rule UNCHANGED, so `RED1_PENUMBRA_DIRS: confirm` now governs
         git-capable rows only and no directory with a tracked descendant is ever archived, including to give an unmaterialized row an
         ancestor; c6p never treats a payload-only row's tree as penumbra (`row_relpaths` returns git-capable rows only; `penumbra_nodes` skips
         payload-only rows — classify records `penumbra_paths` for a shallow row too, `classify.cpp`'s shallow branch, so without that skip
         each of its ignored files would be archived TWICE). After (c) the creation cell governs the git-capable-but-unmaterialized rows:
         the offline-pointer branch (`open.cpp:794` at `e5afe9d`, entered by `--offline` or a declined network consent — `stage` is empty for
         both, `:889-891` with `:1168`) and the url-divergence-refused row (`:850-856`); the two engine-returned pointer rows
         (`restore.cpp:448-457`) are cured by c6q. (d) MASTER'S RULING (011148) on m-4's requirement word for m-3's 200917 observation: the
         open refuses ANY payload member carrying a dot-git component under the AA-3 predicate at BOTH writers — the first pass for the
         members it writes, the deferred writer for the members it writes — one predicate, two call sites, each refusing before any byte of
         that member is written; it RIDES c6p. GATE FILE: `$RUNNERS/red1-owner-words.txt` REWRITTEN by the pair Planner ONLY from 011148, the
         rev24 file preserved beside it as `red1-owner-words.prev-<stamp>.txt`; SEVEN lines, pdc-relative — rev24's three unchanged plus
         `c6p_carry_relay=`, `m4_c6p_relay=`, `m3_c6p_relay=`, `m1_c6p_relay=`; the file NAME is unchanged, so Step 0′'s carried list and
         its pinned block are unchanged. Task 6d Step 0 binds all seven by bytes. REGISTERED, not c6p conditions (Out of scope): m-4's
         TOCTOU observation (master registered it); nesting of payload-only rows; a git-less host.
T-C6B    RECORDED + HOLD for the carry (rev25, MUST-2B-43): c6b `cd51937` (impl-5) committed `src/core/open/open.hpp` (`RepoOutcomeRow` gains
         `kind` / `detail`, the struct side of the failed-row composition) while Task 6b's Files line and commit block listed fourteen
         paths without it and impl-5's per-path ledger assigned `open.hpp` to c4b only; the return did not enumerate it. It is inside
         impl-5's SCOPE_DIFF and additive; rev25 corrects Task 6b's Files line, its commit block and the c6b topology row as the RECORD,
         never a rewrite of c6b. Reported to master (`intg-substep2b/SITREP-pair-planner-20260922-012122.md`). HOLD: the pair Planner
         requests the fresh T-ORACLE carry and issues the next token ONLY after a master relay on record disposes of this deviation
         (naming `cd51937` and `src/core/open/open.hpp`); the token cites that relay.
T-R472   BOUND (rev28; R-4.72 — at product scope neither verb saw a URL divergence: pack recorded `remote get-url`'s insteadOf-expanded
         value as the requested one; open's isolation leaves no user config able to reach a restore site, while an ENCLOSING repository
         reached the gate's `--get-url` by upward discovery). SEVEN owner words carried by master in three relays TO this seat:
         `master/relays/intg-2b-wiring-act/PLAN-master-planner-20260923-142025.md` (m-1 `…/DESIGN-planner-20260923-140916.md`
         `R472_PLACEMENT: in-lane` + `R472_MANIFEST_URL: configured`; m-4 `…-140901.md` `R472_ISOLATION: stands`; m-3 `…-141015.md`
         `R472_OPEN_WITNESS: other`), `…/PLAN-master-planner-20260923-145548.md` (m-4 `…-144917.md` `R472_ENCLOSING_REPO: ceiling`) and
         `…/PLAN-master-planner-20260923-151255.md` (m-1 `…-150702.md` `R472_CEILING_PLACEMENT: own-commit-in-lane`; m-3 `…-150622.md`
         `R472_OPEN_WITNESS_REWORD: shim-fallback`). WHAT THEY BIND: c1d (Task 6e, m-1's fence) and c1e (Task 6f, m-1's fence for m-4's EC-1),
         both engine-only, after c6p, before c7; Task 7's pack grain on REAL config, its open grain on the LABELLED shim, the ISO family
         (EC-2 + W-1′/W-2/W-4/W-5) with EC-4's other half named; E3 at the pack verb; the open gate stays wired (EC-3). GATE FILE
         `$RUNNERS/r472-owner-words.txt`, nine `key=path` lines written by the pair Planner ONLY from those three carries, beside
         `t-oracle.txt` and before the token; `resume.sh` carries it (rev28 adds it to the carried list, so `resume.sh`'s BLOCK moves and
         Step 0′ is re-walked). Task 6e Step 0 binds all nine by bytes for c1d, c1e and c7. Any other word ⇒ a new plan revision.
T-ARM    REGISTERED (S-6; R-4.57, owner m-1) — legs 2b CANNOT execute at product scope because Arms 2/3/4 are unlanded: (i) a
         staged/unstaged-change round trip (no patch artifact exists; capture.cpp:282-403); (ii) a nested-repo image from `biv pack`
         (Fence::nested refuses); (iii) capture leaves-first ordering and the open-side parents-before-children order on a product-packed
         image (needs (ii)); (iv) a submodule image. Each is written in $EVID/legs/registered.txt with its arm; the open-side ordering
         leg keeps its HAND-BUILT (synthetic-manifest) unit witness in Task 4 as the ONLY 2b witness, labelled so.
```

## Per-task runner protocol (measurement tasks) and the code-task discipline

RUNNER RECORDS IN THE EVIDENCE HOME (rev30; the impl-9 STOP `intg-substep2b/IMPL-pair-implementer-20260924-143008.md`): a Task 9 / 10 / 11 runner publishes its four records (`task-N.sh`, `proof-N.txt`, `task-N.sha256`, `task-N.invocation.txt`) as ONE unit, the directory `$EVID/runners/<token-id>/task-N/` (rev32), under `$EVID/runners/<token-id>/` — the token id read from `$RUNNERS/token-id.txt` (written by Step 0′) and form-checked — CONFINED (rev31, MUST-2B-48: `$EVID/runners` a real non-symlink directory whose physical path is the home's own `runners`; the token directory a real non-symlink directory directly beneath it, created by a plain `mkdir` when absent and re-resolved physically; the record name `task-N` LEXICALLY absent — neither a file, a directory nor a symlink, dangling included), every failure an exit before the task body. PUBLICATION IS ATOMIC (rev32, MUST-2B-49 of `intg-substep2b/PLAN-REVIEW-pair-implementer-20260924-153636.md`): the four are copied into a fresh stage directory `stage-task-N.XXXXXX` that `mktemp -d` creates inside the token directory; the stage must then hold exactly four entries, each a regular non-symlink file `cmp`-equal to its source; only then is `task-N` re-checked absent and the stage renamed onto it with one `mv` (a `rename(2)` within one directory); after it `task-N` must be a real directory of exactly those four `cmp`-equal files and the stage name gone. So `task-N/` exists only complete: a fault after any prefix of the copy, a copy that returns 0 with wrong bytes, or a failed rename exits before the body with `task-N` absent. Whatever the fault leaves is inside its own `stage-task-N.*` directory — the durable record of that fault, never removed, never renamed, and never mistakable for the task record, whose one name is `task-N/`. A same-token retry is clean: `task-N` is still absent, so the re-run makes a new stage and publishes, leaving the earlier stage, every earlier task's `task-M/` and the flat records untouched; once `task-N/` exists the same task under the same token is refused, as before. The residual is concurrency, which this lane excludes (one runner at a time under `run-task.sh`): an entry created at `task-N` between the last absence check and the rename could receive the stage, and the post-rename check stops on that. It never writes those four names flat in `$EVID/runners/`, where a runner copied by an earlier token is mode 0500 and cannot be replaced. `finalize.py` walks the home without following symlinks, so a record outside the home or behind a symlink would be absent from the evidence of record — which is why the copy is confined rather than merely redirected. Through rev29 the copy was flat, so the home holds, flat and preserved VERBATIM as the record of those two stopped runs: impl-8's rev28 `runners/task-9.sh` (`d9e96366…`, 0500) and impl-9's `runners/proof-9.txt` (`670aecab…`), `runners/task-9.sha256` and `runners/task-9.invocation.txt` — the impl-9 copy stopped on the first name after writing the other three. Nothing modifies or removes them; `finalize.py` records every regular file of the home, so they enter the evidence of record as they are. `run-task.sh`'s own success receipts (`task-N.done`, `task-N.exit`, `proof-N.tail`, `plan_blocks.sha256-N`) stay flat, written once on a task's rc 0 (Task 11 reads `runners/task-10.done`; `finalize.py` excludes the four Task 11 receipts by name).

Tasks 0, 9, 10 and 11 are MEASUREMENT tasks: each has exactly one `<!-- RUN: task-N -->` block below its steps and is entered ONLY through the runner protocol of `PL-intg-r449-line1-selection-20260913.md` (its BLOCKs `plan_blocks.py` and `run-task.sh` are reproduced in §Instruments below with the named changes and are extracted from THIS plan): `run-task.sh N` re-hashes the plan against `plan-lock.txt`, materializes `task-N.sh` from the plan's own bytes, proves it (`plan_blocks.py check … rc=0` WITH `gates>0` — every mandatory gate of the task is written in its prose as a backtick span carrying `|| STOP`, byte-equal to its runner line, so the checker BINDS the prose to the executable text; a task whose proof reports `gates=0` is unproved), `chmod 0500`s it, records its sha256 and invocation, and runs it exactly once. Every runner's first executable lines after the prologue are `set -o pipefail` and the `PIPEOK` function (the R-4.49 census instrument's form); every pipeline is followed by `PIPEOK <label>`; producers write to files and their status is checked BEFORE the file is read; every retained write is `|| STOP`-guarded and `[ -s ]`-checked; process substitution is not used (a producer writes a file, the consumer reads the file). Task 9 Step 0 runs the runner CONTROLS once: `PIPEOK` fails on `false | cat` (must-be-NO), a write into a read-only directory STOPs, and a producer that exits 1 with partial stdout is caught before its output is read — each in a subshell, each receipt recorded; a control that passes where it must fail STOPs the task.

**Step 0′ — resumption under a LATER token (rev17; rev18 folds MUST-2B-36/37; rev19 folds MUST-2B-38/39/40; the gap disclosed on the token 162507 and in 162750, the fold accepted by master 175324; rev39: Task 9's receipts carried once Task 9 is done; rev46: Task 10's likewise).** rev39: when the previous directory holds `task-9.done`, it must read `rc=0`; `task-9.done`, `task-9.exit`, `proof-9.tail` and `plan_blocks.sha256-9` must equal the controller's copies in `$EVID/runners/`; `task-9.sh` must re-hash to `task-9.sha256`; the runner, its proof, digest and invocation must equal the prologue records of the token that ran it (`$EVID/runners/<that token>/task-9/`); and all eleven Task 9 receipts are carried, so Task 10's controller finds `task-9.done` and Task 9 can never re-run under a later token. rev46: the same, for Task 10, once `task-10.done` is present (and only beside a carried Task 9): it must read `rc=0`; `task-10.done`, `task-10.exit`, `proof-10.tail` and `plan_blocks.sha256-10` must equal the controller's copies in `$EVID/runners/`; `task-10.sh` must re-hash to `task-10.sha256`; the runner, its proof, digest and invocation must equal the prologue records of exactly ONE token (`$EVID/runners/<that token>/task-10/`; impl-15's failed attempt's records differ and do not count); and all eleven Task 10 receipts are carried, so Task 11's controller finds `task-10.done` (its predecessor check, controller line 16) and Task 10 can never re-run under a later token. The runner protocol binds `$RUNNERS/plan-lock.txt` ONCE, before Task 0, to the first token's PLAN_LOCK digest, and `run-task.sh N` STOPs when the live plan's digest differs; every revision after Task 0 has executed therefore orphans the runners. A later token (a new PLAN_LOCK digest, a new DISPATCH_ID, the SAME evidence home — the plan names the home by the token that opened it and a second home would split the evidence) is entered through `resume.sh` (BLOCK in §Instruments, extracted from THIS plan with the fixed reader, run ONCE per token in the implementer's shell BEFORE any task under it: `bash resume.sh <EVID> <the token's PLAN_LOCK sha256, typed ONCE from the token relay> <the token's DISPATCH_ID, typed ONCE>`). PRE-FLIGHT, before any write: the plan on disk re-hashed MUST be the new lock; the new lock MUST differ from the previous directory's (`same-lock` = nothing to resume — the previous directory serves); `task-0.done` MUST read `rc=0`, `task-0.sh` MUST re-hash to `task-0.sha256`, and both MUST equal the copies Task 0 sealed into `$EVID/runners/`; every Task 0 receipt MUST exist; and (MUST-2B-36/38) a carried `t-oracle.txt` MUST hold EXACTLY ONE `plan_sha256=` line and that line MUST name the new lock — BOTH counts measured (total `^plan_sha256=` lines == 1 AND exact current lines == 1; a current line beside the stale one, or two current lines, STOP before any write, where Step 5's `field` parser would otherwise refuse the file only after publication) or STOP `t-oracle-stale` — the T-ORACLE carry binds the LIVE plan digest (Step 5's gate greps `T_ORACLE_PLAN_SHA256: <the live digest>` in master's carry and `plan_sha256=` in the file), so EVERY revision after a carry needs a FRESH carry: after the implementer's exact-hash approve the pair Planner names the new digest to master (042216's rule), master files the five-field carry for it, and the pair Planner REWRITES `$RUNNERS/t-oracle.txt` from it (the previous file preserved as `t-oracle.prev-<stamp>.txt`, never overwritten in place) BEFORE the token that names the new file's digest; a token issued while the file is stale is a token whose Step 5 cannot run. BUILD, unpublished: a NEW runners directory (`mktemp -d` under `$HOME/Programming/bivpak-evidence/` as `s2b-runners-XXXXXX`, `pwd -P`) with `plan-path.txt`, `plan-lock.txt`, `token-id.txt`, `evid.txt`; BOTH instruments re-extracted from the NEW plan bytes (`py_compile` / `bash -n`, `chmod 0500`, digests); `blocks.txt` from `plan_blocks.py list`; Task 0's receipts CARRIED byte-for-byte from the previous directory (`task-0.sh proof-0.txt task-0.sha256 task-0.invocation.txt task-0.exit task-0.done task-0.proof-tail task-0.self.sha256 plan-hash-0.txt plan_blocks.sha256-0`) and every gate file present there (`m3-addendum-9-lock.txt m1-fence-rev4.txt m3-help-order.txt t-oracle.txt m3-r462-patch.txt m1-fence-word.txt m3-addendum-10-lock.txt m3-addendum-11-lock.txt m3-harness-patch.txt red1-owner-words.txt r472-owner-words.txt task-10-go.txt` — rev28 adds `r472-owner-words.txt` and names `red1-owner-words.txt`, which the code has carried since rev22 while this list omitted it; absent ones stay absent and their gates HOLD as before), each copy re-compared; `previous-runners.txt`, `previous-lock.txt`, `carried.sha256`; the SEAL assembled inside the new directory (`seal/`: the binding files and `resume.txt`). SEAL, then PUBLISH LAST (MUST-2B-37): the seal is copied to `$EVID/runners/resume-<token>/` (STOP `seal-exists` if that path exists — no clobber; STOP `seal-copy` if the copy fails; its file count verified and EVERY one of the eight files compared byte-for-byte to the built seal — `seal-<file>-mismatch` (MUST-2B-39: a copier that alters any binding file is caught, not only the note)), THEN the canonical pointer: the old `$EVID/runners-dir.txt` preserved as `runners-dir.prev-<stamp>.txt` (no clobber), the new value written to a temporary name in the SAME directory, verified, and `mv`'d over `runners-dir.txt` (an atomic same-directory replacement) — the pointer moves as the LAST act, and the `mv`'s success IS publication (MUST-2B-40): the run marks itself published the instant the `mv` returns 0, before any later operation, so a failed or mismatching read-back after it STOPs `published-verify` with EVERYTHING retained (the pointer, the seal, the directory — nothing reachable from the canonical pointer is ever removed) and the disposition is a COMPLETED run to verify by hand: `cat $EVID/runners-dir.txt` names the new directory, `RUNNERS` is exported from that value, and a rerun STOPs `same-lock` by design — never a cleanup, never a retry as unpublished. Any STOP before that act leaves the old pointer byte-identical and the previous directory canonical, so the run can be retried once the cause is removed; a STOP after writes began removes ONLY what the run created and has not published — the new directory, the seal copy, the staged pointer (a stamped `runners-dir.prev-<stamp>.txt` is a no-clobber copy and stays) — so a retry starts clean. The script prints the NEW directory's path as its ONLY stdout line — the implementer exports `RUNNERS=` from it. Task 9's controller then finds `task-0.done` in the new directory and the lock equal to the plan. EXECUTED at the pair Planner's seat on a scratch mirror of the real directories: the must-be-YES (a fresh `t-oracle.txt` naming the plan on disk) binds, seals and publishes, and the exact Step 5 T-ORACLE prefix then passes from the new directory against a scratch pdc carry naming the same digest; the stale rev16 `t-oracle.txt` → `t-oracle-stale` before any write, and the same stale file pushed through the T-ORACLE prefix → `plan-sha-mismatch-live-…`; a current `plan_sha256=` line beside the stale one, and two current lines, → `t-oracle-stale` before any write; the six early mutants (a lock that is not the plan on disk; the same lock; `task-0.done` absent; `task-0.sh` altered; a malformed token id; the sealed copy differing) STOP before any write; the five late mutants (the seal path pre-existing → `seal-exists` in pre-flight; `$EVID/runners` unwritable → `seal-copy`; a `cp` shim on PATH that corrupts the copied note → `seal-resume.txt-mismatch`; a `cp` shim that copies faithfully except the sealed `plan-lock.txt` → `seal-plan-lock.txt-mismatch`; `$EVID` unwritable → `preserve-pointer`, a publication failure after the seal was copied) each STOP with the old pointer byte-identical, no seal or staged pointer left behind and no new directory left in the evidence root, and each RETRIES to success once the cause is removed; a `cat` shim that fails the FIRST read after the `mv` → `published-verify` with the pointer at the new directory, the seal and the directory RETAINED, the manual read naming the new directory, and a rerun → `same-lock`.

Tasks 1–8 and 8b (rev33) are CODE tasks executed by the implementer as TDD steps in the WORKTREE: each step's command is run as written, its stdout+stderr+rc appended to `$EVID/code/task-N.log` (one `printf '### step %s rc=%s\n'` line per command), the commit sha of each task recorded in `$EVID/commits.txt` (`cN=<sha>`). A code task ends with `ctest --preset ci-macos -E '^safety-hardening$'` rc 0 and `git status --porcelain` EMPTY in the worktree.

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
- [ ] **Step 8 (c3h): run to verify pass, then commit** — `./build/ci-macos/biv_tests '[cli-flags]'` rc 0 (the c3 flag cases — 6 cases at 1065872; `'[cli]'` matches NO case in this suite and exits 2 "No tests ran", the rev19 defect) and `./build/ci-macos/biv_tests 'Task 4 CLI help documents the strict agent binary pin syntax'` rc 0 (the case c3h's two golden lines landed in at 09563d3); `git diff --stat` names only `src/cli/args.cpp` and `tests/test_cli.cpp`.

```bash
git add src/cli/args.cpp tests/test_cli.cpp
git commit -m "cli: the two help lines at A9's locked position (after --accept-url-divergence, before --agent-bin); a6.18 golden re-pinned -- m-3 addendum 9 <lock id> @ <doc sha256>"
git rev-parse HEAD > "$EVID/commits.c3h.txt"
```

### Task 4 — c4a (sealed) + c4b (A10 lock): the `repos/` member class, `restore_entry` per row in §2.2 order, the in-memory rows, `--offline` D4 listing (c4a); `result.repos` + schema, the D2/D3 network-consent surface, the durable offline artifact + `bundle_path`/`reconstruct` (c4b) (A2 D4; m-3 §4 OPEN; restore-apply §1/§2.2; V-2b-7/V-2b-8; A10 rev10 6cba59d3 LOCKED `m3-addendum-10-6cba59d3-lock-20260920`)

**Files:** Modify `src/core/open/open.hpp`, `src/core/open/open.cpp`, `src/core/report/envelope.hpp`, `src/core/report/envelope.cpp`, `src/cli/main.cpp`, `src/cli/url_consent.hpp`, `src/cli/url_consent.cpp` (the A9.4 offline renderers), `tests/test_cli.cpp`, `tests/test_envelope.cpp`, `tests/test_open.cpp` (the TENTH c4a path — rev13, STOP 021304: ONLY the s3 Task-4 source-hash oracle at `:343` `Task 4 open occupancy and destination contracts stay bounded` is re-oracled, per Step 3b; no other case in that file moves); ONLY under T-JSON's word also `schemas/biv-json-envelope.v1.schema.json` + `harness/selftest/test_envelope.py` (the envelope-schema blob pin recomputed by `git hash-object`, same commit). — PLUS (rev17, R-4.62 arm (a)) `tests/test_probe.cpp` ONLY by m-3's approved mailbox patch applied VERBATIM as ONE commit with m-3's authorship in Step 3c (m-3's bytes, not a c4a path: Step 5's write-set gate still expects exactly the ten paths in `git diff HEAD`, because the patch is COMMITTED before them).
**Interfaces:** Produces `OpenOptions.offline`; `struct RepoOutcomeRow { std::string id; std::string relpath; std::string outcome; /* restored | shallow-pointer | payload-only-unborn | failed | offline-pointer */ std::optional<std::string> sha; std::optional<std::string> branch; std::optional<std::string> capture_mode; /* c4a landed `std::string`; c4b (A10.1 rev10, m-1's W-1): OUTCOME-CONDITIONED — the recorded enum "overlay" | "full" on restored / failed / offline-pointer rows, nullopt (serialized null) on shallow-pointer and payload-only-unborn rows, never the in-memory engine default; keyed on the engine-returned outcome at the two sites (open.cpp:674 offline-pointer, :685 engine-returned, at 1065872) */ std::vector<std::string> remotes; std::optional<std::string> bundle_path; /* c4b: dest-relative posix `.biv/repos/<id>/repo.bundle`, PRESENT iff the row is ARTIFACT-BEARING — outcome offline-pointer AND entry.bundle set AND the member in checksums.json (A10.1 rev10); NEVER keyed on capture_mode */ std::optional<std::string> reconstruct; /* c4b: T-STAGE's ONE single-quoted POSIX-sh idiom for the stored HEAD state (born / unborn / detached), byte-equal to the printed command line; PRESENT iff bundle_path is present AND every operand is copy-safe; ABSENT (the fallback line printed instead) otherwise; every other row (overlay offline-pointer rows, every engine-returned row whatever its mode) carries neither field; emitted under T-JSON's word beside bundle_path in the schema row */ std::vector<biv::repo::LocalRefRestoreRow> local_refs; std::vector<std::string> advisories; std::optional<std::vector<std::string>> shallow_boundary; };` and `std::vector<RepoOutcomeRow> OpenReport::repos` (an IN-MEMORY report field; its JSON emission is T-JSON's); `OpenReport.url_divergence_refusals` FILLED; `biv::report::machine_text`. Consumes `biv::repo::restore_entry`, `biv::repo::Git::resolve`, `biv::repo::engine_error_kind` (types.hpp:92-110 — the TYPED accessor; the wire string is `url-divergence-refused`, never compared by hand).

- [ ] **Step 0: the A10 lock gate — the EXECUTABLE block below, run TWICE: `MODE=pre` before the first c4b test byte (Step 6) and `MODE=post` immediately before the c4b commit (Step 9 refuses without the post receipt)** — c4a (Steps 1–5) is sealed text and LANDED (c4a ef8e492, the R-4.62 patch 3431bb7 before it). c4b (Steps 6–9: the `result.repos` emission + schema row, the D2/D3 surface, the durable offline artifact + bundle line + the two row fields, the `capture_mode` projection) writes NO byte until the block PASSES on `$RUNNERS/m3-addendum-10-lock.txt` (written by the pair Planner 2026-09-20 from master's seal 185625; one field per line: `lock_id=m3-addendum-10-6cba59d3-lock-20260920`, `doc_sha256=56abe662…` (the post-stamp = the LIVE doc), `pin_sha256=6cba59d3…` at `pin_commit=5cbb59d7…` (the reviewed pre-stamp bytes), `relay=master/relays/intg-2b-wiring-act/DESIGN-planner-20260920-184029.md` (m-3's lock relay; 184042 is an accidental verbatim re-render — not cited), `seal_relay=master/relays/intg-2b-wiring-act/PLAN-master-planner-20260920-185625.md`). The block is Task 6b Step 0's shape with the A10 constants and TWO differences: the pin is bound by `git -C ../pdc show <pin_commit>:<doc>` re-hashed against `pin_sha256` (the A9 precedent, Task 6a Step 0), and the seal's LINEAGE is a whole-word citation of the lock relay on the seal's `IN_REPLY_TO` OR `RELATED_CONTEXT` line (the ONE seal 185625 replies to A11's lock relay 184104 and cites A10's 184029 in RELATED_CONTEXT — the same act sealed both). Receipt `$EVID/code/c4b-a10-lock.<pre|post>.txt`. Walked at this seat on the REAL file from the candidate at 1065872 with a scratch `$EVID`: pre + post PASS; must-be-NO controls — a wrong `doc_sha256` (`a10-sha-mismatch`), a wrong `pin_sha256` (`a10-pin-mismatch`), a wrong `pin_commit` (`a10-pin-show`), `seal_relay` = the lock relay (`lock-seal-same-file`), `seal_relay` = master's carry 045732, a PLAN TO the pair that does not cite the lock relay (`seal-lineage`), `relay` = the A11 lock relay 184104 (`lock-id-absent-in-lock-relay`), the planned-shape id `m3-addendum-10-20260916` (`lock-id-absent-in-seal` — the lock relay cites the addendum id as a word, the seal names only the lock id), a duplicated `lock_id` line (`field-lock_id-count-2`), a missing `pin_commit` line (`field-pin_commit-count-0`) — each STOPs before any receipt. The c4b bytes below are planned from A10 rev10 (`6cba59d34397f917d4f510d2914e106fb98457ff4d0ae8b4e58f35289c8e1f52`, the LOCKED pin; rev6 `17fda846…` was rev19's source, its deltas transcribed here at rev20) and are re-verified line-by-line against the locked bytes before they are written — a locked byte differing from rev10's is a new plan revision (RULE).

```bash
# Task 4 Step 0 — the A10 lock gate (rev20). Run with MODE=pre BEFORE the first c4b test byte (Step 6) and again with MODE=post
# IMMEDIATELY BEFORE the c4b commit (Step 9 refuses without the post receipt). Task 6b Step 0's shape with the A10 constants; the pin
# bound by `git show` (the A9 precedent, Task 6a Step 0); the seal's LINEAGE = a whole-word citation of the lock relay on the seal's
# IN_REPLY_TO or RELATED_CONTEXT line (the ONE seal 185625 replies to A11's lock relay and cites A10's — the same act sealed both).
# Every check STOPs before bytes; each producer's rc is checked apart from its predicate's.
set -o pipefail
STOP() { printf 'STOP-c4b-gate %s line=%s\n' "$1" "${BASH_LINENO[0]}" >&2; exit 1; }
MODE=${MODE:-pre}; case "$MODE" in pre|post) :;; *) STOP mode;; esac
[ -n "$RUNNERS" ] && [ -n "$EVID" ] && [ -d "$EVID/code" ] || STOP env
LOCK=$RUNNERS/m3-addendum-10-lock.txt; [ -s "$LOCK" ] || STOP lock-absent
PDC=$(cd ../pdc && pwd -P) || STOP pdc; PDCR=$PDC/master/relays; [ -d "$PDCR" ] || STOP pdc-relays
A10_DOC=master/domains/m-3-restore-cli/design/2026-09-16-addendum-10-open-repos-rows-and-network-consent.md
LOCK_ID_RE='^m3-addendum-10-([0-9a-f]{8}-lock-)?[0-9]{8}$'      # the A9-shaped id (the pin's 8 hex + "-lock-"), or the planned id
field() { # exactly ONE `key=value` line; value nonempty, no whitespace
  g=0; n=$(grep -c -E "^$1=" "$LOCK") || g=$?; [ "$g" -le 1 ] && [ "$n" -eq 1 ] || STOP "field-$1-count-$n"
  v=$(sed -n -E "s/^$1=([^[:space:]]+)$/\1/p" "$LOCK") || STOP "field-$1-read"; [ -n "$v" ] || STOP "field-$1-empty"; printf '%s' "$v"; }
lock_id=$(field lock_id) || exit 1; doc_sha256=$(field doc_sha256) || exit 1; pin_sha256=$(field pin_sha256) || exit 1; pin_commit=$(field pin_commit) || exit 1
relay=$(field relay) || exit 1; seal_relay=$(field seal_relay) || exit 1
printf '%s' "$lock_id" | grep -q -E "$LOCK_ID_RE" || STOP lock-id-shape
for h in "$doc_sha256" "$pin_sha256"; do printf '%s' "$h" | grep -q -E '^[0-9a-f]{64}$' || STOP sha-shape; done
printf '%s' "$pin_commit" | grep -q -E '^[0-9a-f]{40}$' || STOP pin-commit-shape
[ -s "$PDC/$A10_DOC" ] || STOP a10-absent
h=$(shasum -a 256 "$PDC/$A10_DOC" | cut -d' ' -f1) || STOP a10-hash; [ "$h" = "$doc_sha256" ] || STOP a10-sha-mismatch        # the LIVE doc = the post-stamp
p=$(git -C "$PDC" show "${pin_commit}:${A10_DOC}" | shasum -a 256 | cut -d' ' -f1) || STOP a10-pin-show; [ "$p" = "$pin_sha256" ] || STOP a10-pin-mismatch   # the reviewed pre-stamp bytes at their commit
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
# --- the A10 LOCK carrier: m-3.planner's DESIGN relay to master declaring THIS lock id, THIS doc sha and THIS pin, citing the A10 document
line1 "$R1" 'FROM: m-3.planner' lock-from; line1 "$R1" 'TO: master.master-planner' lock-to; line1 "$R1" 'PHASE: DESIGN' lock-phase; line1 "$R1" 'AUTHORITY: design-only' lock-authority
hasw "$R1" "$lock_id" lock-id-absent-in-lock-relay; has "$R1" "$doc_sha256" doc-sha-absent-in-lock-relay; has "$R1" "$pin_sha256" pin-sha-absent-in-lock-relay
g=0; k=$(grep -c -E "^(RELATED_CONTEXT|IN_REPLY_TO): .*$(basename "$A10_DOC")" "$R1") || g=$?; [ "$g" -le 1 ] && [ "$k" -ge 1 ] || STOP lock-relay-not-citing-a10
# --- the SEAL carrier: master's PLAN relay TO the pair, citing the lock relay on its IN_REPLY_TO or RELATED_CONTEXT line, naming the same id + sha + pin, saying SEALED
line1 "$R3" 'FROM: master.master-planner' seal-from; line1 "$R3" 'TO: intg.pair-planner' seal-to; line1 "$R3" 'PHASE: PLAN' seal-phase; line1 "$R3" 'AUTHORITY: plan-only' seal-authority
g=0; k=$(grep -E '^(IN_REPLY_TO|RELATED_CONTEXT): ' "$R3" | grep -c -w -F -- "$relay") || g=$?; [ "$g" -le 1 ] && [ "$k" -ge 1 ] || STOP seal-lineage
hasw "$R3" "$lock_id" lock-id-absent-in-seal; has "$R3" "$doc_sha256" doc-sha-absent-in-seal; has "$R3" "$pin_sha256" pin-sha-absent-in-seal
g=0; k=$(grep -c -i -w 'SEALED' "$R3") || g=$?; [ "$g" -le 1 ] && [ "$k" -ge 1 ] || STOP seal-word
r1sha=$(shasum -a 256 "$R1" | cut -d' ' -f1) || STOP r1-hash; r3sha=$(shasum -a 256 "$R3" | cut -d' ' -f1) || STOP r3-hash
printf 'mode=%s\nlock_id=%s doc_sha256=%s\npin_sha256=%s pin_commit=%s\nrelay=%s sha256=%s\nseal_relay=%s sha256=%s\n' "$MODE" "$lock_id" "$doc_sha256" "$pin_sha256" "$pin_commit" "$relay" "$r1sha" "$seal_relay" "$r3sha" > "$EVID/code/c4b-a10-lock.$MODE.txt" || STOP receipt
if [ "$MODE" = post ]; then
  [ -s "$EVID/code/c4b-a10-lock.pre.txt" ] || STOP pre-receipt-absent
  cmp -s <(sed 1d "$EVID/code/c4b-a10-lock.pre.txt") <(sed 1d "$EVID/code/c4b-a10-lock.post.txt") || STOP pre-post-differ
fi
printf 'c4b-gate %s OK\n' "$MODE"
```
- [ ] **Step 1: the failing tests (hand-built images, `provenance=hand-built, interim`)** — a test helper `build_repo_image(dir) -> image path` that drives the ENGINE directly (`repo::discover` → `classify` → `run_eligibility(…, network)` → `capture` into a scratch dir) then assembles the archive with `manifest::serialize` + the container writer exactly as `pack.cpp` orders members (manifest, checksums, payload, repos, agents) — a fixture builder, replaced by `biv pack` itself once Task 5 lands (Task 7 re-executes every case here against product-packed images). Cases in `tests/test_cli.cpp`:
  - `a real bundle restores` (MUST-2B-02, corrected for ARM-1 REALITY): a CLEAN source repo with one committed file, one IGNORED file (`.gitignore`d — the penumbra; NOT untracked, which is the dirty fence) and one local branch → engine-built image (`repos/<id>/repo.bundle` + `local-refs.bundle` — the ONLY artifacts capture.cpp writes at the pin) → open → `git status --porcelain=v2` of the restored repo is EMPTY like the source's, HEAD/branch equal, the ignored file byte-equal, the local branch recreated; each `repos/<id>/…` member was staged at `<stage>/repos/<id>/…` (the ONLINE arm of Task 4's `stage` routing; the FULL manifest-relative path — `restore.cpp:138-145` resolves `stage_root / <artifact relpath>` and containment-checks it) and its checksum verified; the stage dir is gone after open. The staged/unstaged-patch round trip is T-ARM (i), REGISTERED — no patch artifact exists at 2b.
  - `typed refusal mapping` (MUST-2B-01): a restore-site divergence — NOT a temp-HOME `.gitconfig` insteadOf (impossible at B: restore sets `GIT_CONFIG_GLOBAL=/dev/null`, an engine isolation byte no fence lets 2b touch; rev13 AFFIRMS the implementer's 021304 substitution) but a TEST-LOCAL request-trace git shim on `PATH` that answers ONLY `remote get-url` with the diverged effective URL and forwards every other git invocation to the real git verbatim, recording argv (the trace is the fixture's own receipt; no product byte; the product-scope form is Task 7 M leg (h), F-DIVERGE's default local config — rev28, R-4.72: M (h) is the PACK grain; this OPEN-grain row mapping keeps a labelled shim at product scope too, Task 7 M (b)/(i)/(j) on F-SHIM-OPEN, since the restore isolation and c1e's ceiling leave no configuration able to reach a restore site) → ONE `UrlDivergenceEntryRefused` row + the run CONTINUES to the next entry (exit 2); the mapping goes through `biv::repo::engine_error_kind(error) == EngineErrorKind::url_divergence_refused`; NAMED MUTANT: a string compare of `"url_divergence_refused"` (underscore spelling) takes the whole-operation arm — the test asserts the ROW arm and exit 2, so the mutant reds.
  - `repos/ member class admitted iff named`: an image whose one repos[] row names `repos/<id>/repo.bundle` → open succeeds AND the restored repo is a real git repository at its relpath (`git -C <dest>/<relpath> rev-parse HEAD` == the recorded sha); the SAME image with an extra `repos/<id>/stray.bin` member listed in checksums → exit 3 `UnmanifestedMember` naming it (V-2b-7; ADDENDUM-I discipline); an image whose row names a member ABSENT from the archive → exit 3 `IntegrityFailurePreApply` detail `missing-repo-artifact` (mirrors `missing-agent-member`).
  - `restore_entry once per row, parents before children` (HAND-BUILT ONLY — T-ARM (iii)): a SYNTHETIC manifest with a parent row and a child row (`parent_id` set) whose artifacts are two independently engine-captured clean repos placed at `repos/<id>/…` (the engine's classify would FENCE a real nested tree at 2b, so no product-packed image can carry two rows — registered) → after open, both are git repos at their relpaths under dest; the request-trace shim log (BLOCK `git-shim.sh` on PATH — see §Instruments) shows the parent's clone before the child's; the in-memory rows are two, outcomes `restored`, in that order. Labelled `provenance=hand-built, registered-T-ARM` in its receipt; NOT re-executed in Task 7.
  - `nothing before apply touches disk`: a divergence refusal at the first entry leaves the dest ABSENT? — NO: A6-R4/a6·12 say the clean entries COMPLETE and the refused ones are rows (exit 2); so: two refused entries + one clean → dest exists, the clean repo restored, two `UrlDivergenceEntryRefused` rows in ENCOUNTER ORDER, exit 2, `error` null (a6·12's shape; Task 7 adds the golden text and stream-order assertions at product scope).
  - `--offline` (c4a; with the stage-path DISCRIMINATOR): a regular FILE is pre-created at `<containing_dir(dest)>/<dest.filename()>.bvpk-open.stage` before the run → `biv open --offline` exits 0, the listing renders, and that file is byte-unchanged afterwards (the offline arm never touches the stage path); the CONTROL: the same pre-created file with an ONLINE open of the same image → `OpenPartialPresent` naming that path (proves it is the very path the online arm stages into). NAMED MUTANT: routing `repos/` members into the stage dir regardless of `stage` → the offline run fails on the pre-created file ⇒ RED. At c4a the offline arm DRAINS + verifies every `repos/` member (materializes nothing); at c4b (Step 6) the full-capture row's `repo.bundle` is placed DURABLY per T-STAGE and this case gains: `<dest>/.biv/repos/<id>/repo.bundle` exists with sha256 == checksums.json's entry for `repos/<id>/repo.bundle`, an overlay row's members are absent under `<dest>/.biv/`, the stage path STILL untouched, zero git. Also: the same image → ZERO git spawns in the shim log for the whole open (m-1's guarantee; m-3 V-OFF (1)); payload + sessions laid down as today; the in-memory rows: `offline-pointer` ONLY for rows that would otherwise clone or fetch (born, non-shallow, with a bundle or an eligibility cell); a SHALLOW row stays `shallow-pointer` and an unborn payload-only row stays `payload-only-unborn` — these structural rows are IDENTICAL field-by-field with and without `--offline` (N's parity oracle; the engine returns them without git either way, restore.cpp:444-452) — three branches stated, no two incompatible outcomes claimed; exit 0; the A9.4 listing on stderr after the apply summary for the offline-pointer rows, byte-exact modulo paths (the bundle line + `bundle_path`/`reconstruct` are c4b's — Step 6 witnesses them).
  - `machine carriers valid UTF-8` (MUST-2B-03): a refusal row whose `relpath`/`repo_id` carries a lone `0x9b` → the JSON envelope is VALID UTF-8 with U+FFFD at that coordinate (`machine_text`), the in-memory refusal row still holds the raw byte; the same for `error.path` on a pack refusal and for an accepted advisory entry's `repo`. NAMED MUTANT: a raw `0x9b` reaching the JSON (invalid UTF-8 output) ⇒ RED; a display escape (`\u009b`, `\u{…}`) inside a machine field ⇒ RED.
  - `zero state`: an image with no repos[] → no repos rows in memory; no listing; exit as today.
- [ ] **Step 2: run to verify failure** — `./build/ci-macos/biv_tests '[open-repos]'` FAILS (`UnmanifestedMember` for every `repos/` member today).
- [ ] **Step 3: the implementation** —
  `read_archive_plan` (`open.cpp:283-296`): admit `repos/` members: build `std::set<std::string> named_artifacts` from every `plan.manifest.repos[i]` row's `bundle`, `local_refs_bundle`, `capture.staged_patch`, `capture.worktree_patch` (generic strings; only those four kinds — manifest-format §3 under `repos/<id>/`); a member starting with `repos/` is admitted iff `named_artifacts.contains(path)` (checksums membership is already checked above) → `plan.repo_artifacts.push_back(PlannedMember{…})`; else `UnmanifestedMember`. After the loop: every `named_artifacts` entry not `seen` → `IntegrityFailurePreApply` detail `missing-repo-artifact`.
  `apply_archive(image, plan, partial_dir, dirs, verify, stage)` — a NEW trailing parameter `const std::optional<std::filesystem::path>& stage`: a third branch for `repos/` members (file members only; `MemberPathUnsafe` otherwise), ROUTED by `stage`: (ONLINE — `stage` has a value) extracted into `*stage / <the FULL member path, e.g. repos/<id>/repo.bundle>` — the manifest-relative namespace preserved so `restore_entry(git, entry, partial_dir, *stage)` resolves `stage_root / entry.bundle` exactly (restore.cpp:138-145; MUST-2B-02) — with checksum verification exactly like payload; (OFFLINE at c4a — `stage` is `std::nullopt`) DRAINED and checksum-verified exactly like `agents/` members (`drain_member_midapply` + the extent digest) and NEVER materialized — no stage directory exists in this arm; both arms count `repo_artifact_count` and the member-count check includes them. At c4b (Step 6, A10 lock) the OFFLINE arm gains T-STAGE's durable placement: a member that IS an ARTIFACT-BEARING row's `bundle` (`repos/<id>/repo.bundle` — the row's outcome offline-pointer AND `entry.bundle` set AND the member in checksums.json, A10.1 rev10; NEVER keyed on `capture_mode`, V-A10-8) is written to `partial_dir / ".biv" / "repos" / <id> / "repo.bundle"` with the same checksum verification (integrity-failure(member) on mismatch, §3), carried by the rename; every other `repos/` member (overlay rows' `local-refs.bundle` — R-4.58) stays drained. `git bundle verify` is never run.
  `execute_archive`: `const std::optional<std::filesystem::path> stage = (options.offline || plan.manifest.repos.empty()) ? std::nullopt : std::optional{containing_dir(dest) / (dest.filename() + ".bvpk-open.stage")}`; ONLY when `stage` has a value: present at start → `OpenPartialPresent` naming it (the existing kind; the same repair path as the partial dir), created before apply, removed after the rename and on every error path (the cleanup lambda); under `--offline` the stage path is NEVER stat'ed, created, written or removed. `apply_archive(image, plan, partial_dir, dirs, verify, stage)`; after it and the mtime pass, iff `stage` has a value: `auto git = biv::repo::Git::resolve(getenv)` (`getenv` = the process environment through `support::Getenv`, as the engine tests build it; failure → the engine's typed error surfaces as today); order the rows PARENTS BEFORE CHILDREN (stable topological order by `parent_id`, manifest order within a level); for each row: `restore_entry(git, entry, partial_dir, *stage)`; on a value → `RepoOutcomeRow` from `RepoRestoreRow` (outcome word by the D5.2 enum: `restored`, `shallow-pointer`, `payload-only-unborn`, `failed`); on an error for which `biv::repo::engine_error_kind(err) == biv::repo::EngineErrorKind::url_divergence_refused` (the TYPED accessor, types.hpp:92-110 — MUST-2B-01) → push `UrlDivergenceEntryRefusal{entry.id, entry.relpath, facts.requested, facts.effective, facts.op}` and a `RepoOutcomeRow{outcome = "failed"}` and CONTINUE (V-2b-8(iii): the entry's typed restore failure, never downgraded); any other error → whole-operation failure with the `partial_dir` fact exactly as payload errors today. Offline (`options.offline`) — and a DECLINED D3 run (c4b), the SAME code path — the EXACT partition of m-1's fence rev3 §2 (A10 rev10 §A10.2 carries it verbatim), per row in manifest order on the ENGINE'S predicate, READ never recomputed: `restore_invokes_git(entry) == false` ⇒ CALL `restore_entry(git, entry, partial_dir, <no stage>)` — zero git by construction (the request trace proves it; the sealed rows: `shallow-pointer` per N-R4, IDENTICAL with and without the flag; `payload-only-unborn` per H; `sha` exactly as the engine returns it) — `git` here is `Git::resolve(getenv)`'s handle (a binary lookup that spawns nothing; if it cannot resolve while only predicate-false rows exist, that is an S-2b-5-class STOP to m-1, not a lane workaround); `restore_invokes_git(entry) == true` ⇒ do NOT call `restore_entry`; emit the ADDENDUM-D `offline-pointer` row with `relpath`/`branch`/`sha`/`remotes[]` from the manifest (`sha` = the 40-hex or the sealed literal `(no commits)` iff HEAD is unborn — never null on an offline-pointer row, A10.1); ARTIFACT-PRESENT = `entry.bundle` set ∧ that member in `checksums.json` (a fact the engine wrote at capture.cpp:307; no engine byte) decides the durable placement (c4b) and `bundle_path`; at c4a NO `repos/` member is materialized in this arm; at c4b the artifact-bearing rows' `bundle_path` (dest-relative posix `.biv/repos/<id>/repo.bundle`) and `reconstruct` (T-STAGE's ONE idiom per stored HEAD state — born / unborn / detached — every operand single-quoted on the raw bytes, PRESENT iff every operand is copy-safe, else absent with the fallback line) are set on the in-memory row for every artifact-bearing row; every other row (overlay offline-pointer rows, every engine-returned row whatever its mode) carries neither; and `capture_mode` becomes nullopt on shallow-pointer / payload-only-unborn rows at the engine-returned site (open.cpp:685 at 1065872 — keyed on the engine-returned outcome; the offline-pointer site :674 keeps the manifest enum). Then `fsync_tree` and the rename to `dest`. D3 (c4b, T-NET): in `main.cpp`'s open flow — AFTER the existing collision and PROMPT B handling (A7-R4: B completes before any D) and BEFORE the call that executes the archive (`main.cpp:354` at B; no git subprocess exists before it) — iff `!options.offline` and ∃ a manifest row with `biv::repo::restore_invokes_git(entry) == true` (the engine's GIT-CAPABLE partition, c1c, READ — A10 rev10 §A10.2 TRIGGER; the CLI never recomputes it; TRUE means the row's restore MAY invoke git and therefore REQUIRES consent first — not that it will spawn or succeed): `render_network_consent(rows)` + the decision per T-NET (interactive: prompt; non-interactive: the flag); a DECLINE makes the run `biv open --offline` for its repo half — the partition above, `stage = std::nullopt`, zero git, exit 0, A9.4's listing for the offline-pointer rows (A10 rev10 DECLINED).
  `envelope.cpp`: `machine_text()` (= `support::sanitize_utf8`) applied at EVERY emission of a bound value the A8 census names — `write_error`'s `path` and every `facts` value; the four fields of each `url-divergence-accepted` entry; the five fields of each `url_divergence_refusals` row; every string field of each `result.repos` row (c4b) — valid UTF-8 byte-exact, malformed visibly replaced, never a display escape (MUST-2B-03; A8-R1 machine census + malformed arm); the in-memory values (memo keys, decisions, refusal rows) stay RAW. The `result.repos` emission (T-JSON's row set VERBATIM; present iff ≥ 1 row processed, never `[]`) and `schemas/biv-json-envelope.v1.schema.json`'s `result.properties.repos` (the row shape, `minItems: 1`) land in c4b in the SAME commit with `harness/selftest/test_envelope.py`'s envelope-schema blob pin recomputed by `git hash-object`; `result.manifest.repos` stays the landed EMPTY array (I2B-09 option (b), registered).
  `main.cpp` (open, `--offline`, human mode, iff `!report->repos.empty()`), AFTER the apply summary, on `std::cerr`, the A9.4 bytes VERBATIM (rendered by renderers added to `url_consent.cpp` — `render_offline_header()`, `render_offline_row(relpath, branch, sha, remotes)`; `render_offline_bundle_line(relpath, reconstruct)` at c4b with `<reconstruct>` = T-STAGE's selected form; `render_network_consent(rows)` (c4b; the A10.2 NOTICE bytes + the interactive PROMPT line; the SAME text on the pty and on a redirected stderr) — every bound value through `consent_display`; main.cpp only sequences them):

```text
open --offline: repositories were not restored (no git, no network). Stored remote URLs below are informational — recorded at pack, not vetted or complete. Cloning them is git-clone-grade trust: git may contact those URLs and additional URLs from repo metadata (.gitmodules, nested submodules, host git config) that Bivpak does not see or police. Clone only what you trust.
<relpath> · <branch> · <commit> · <url>[, <url>…]
<relpath>: <reconstruct>   (partial/manual reconstruction — not a full restore)
```

  one repo line per offline-pointer row in manifest order (`<branch>` = `(detached)` when none; `<commit>` = the 40-hex sha, `(no commits)` for an unborn HEAD; no stored URL → `(no stored remote)`); the bundle line for ARTIFACT-BEARING rows is c4b's (Step 6), one per artifact-bearing row AFTER all listing rows, the HEAD-only detached form included; every value through `consent_display` (A8-R1 policy; the machine carrier through `machine_text`); exit 0 (an offline open is a success). `--offline` and `--network` alter NOTHING about PROMPT D (V-OFF (3); V-A10-3); `--network` is consumed ONLY by D3 (c4b, T-NET).
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

- [ ] **Step 6 (c4b, AFTER the A10 gate of Step 0 holds; lands after c5 in lock order): the failing tests** — `tests/test_cli.cpp` (hand-built images, `provenance=hand-built, interim`; Task 7 re-executes on product-packed images), each case naming its A10.4 leg and mutant (thirteen legs (a)–(m) at rev10, LOCKED 6cba59d3 — every one written here, none deferred): **(h) THE ROWS** — two repos (one restored, one shallow-pointer) → `result.repos` with EXACTLY the T-JSON fields and enum words, manifest order — the restored row's `capture_mode` the recorded enum, the shallow-pointer row's `null` (A10.1 rev10); an image with zero repos → NO `repos` member (NAMED MUTANT: `[]` at zero state, an extra/missing field, or `"full"` serialized on the shallow-pointer row ⇒ RED); `result.manifest.repos` unchanged; **(a) NOTICE BEFORE GIT** — `run_cmd_pty_split`, a networked image (one overlay row), no flag: the NOTICE + PROMPT bytes on the pty EXACTLY as T-NET spells them, ONCE, and the shim log shows ZERO git invocations before the answer is read; `y` ⇒ git runs (NAMED MUTANT: a git call before the answer, or a second render ⇒ RED); **(b) DECLINE, MIXED POPULATION (A10.4 (b) rev10)** — an image carrying, in BOTH manifest orders (two fixtures), five rows chosen to overlap the axes: an overlay row with a stored remote (predicate TRUE); a full-capture row with its bundle member (TRUE); a shallow row (FALSE, N); an unborn-HEAD row with no bundle and no eligibility (FALSE, H); an unborn-HEAD full row with a bundle member (TRUE, G). Answer `n` (and separately: empty, EOF): zero git across the whole run (shim tripwire); FIVE rows complete and in manifest order with outcomes offline-pointer / offline-pointer / shallow-pointer / payload-only-unborn / offline-pointer; `bundle_path` (+ `reconstruct`) on exactly the second and fifth rows; `sha` `"(no commits)"` on the fifth, `null` on the fourth, 40-hex on the rest; the shallow row's bytes IDENTICAL to the same image opened with consent (N-R4 parity); two artifacts durable at `.biv/repos/<id>/repo.bundle`; the A9.4 listing for the three offline-pointer rows with two bundle lines; exit 0; the SAME image under `--offline` yields byte-identical rows; and the H row — whose in-memory `capture_mode` is the enum default `full` — passes the schema and V-A10-8 checks with NO `bundle_path`, NO `reconstruct`, NO bundle line and `capture_mode` serialized `null`, as is the shallow row's; the three other rows carry their recorded enum (NAMED MUTANT: `"full"` (or `"overlay"`) serialized on the shallow or H row, `null` on any other row, any git call, a dropped or reordered row, the shallow or H row relabelled offline-pointer, a null sha on an offline-pointer row, a bundle field on a non-artifact-bearing row, a bundle check keyed on `capture_mode`, a refusal exit, or a byte of difference from the `--offline` run ⇒ RED); **(c) NON-INTERACTIVE, NO FLAG** — stdin redirected: no notice, no prompt, zero git, offline-pointer rows, exit 0; **(d) `--network`** — non-interactive with the flag: the NOTICE without the prompt line; git runs (NAMED MUTANT: notice absent, or the prompt line present ⇒ RED); **(e) `--json` PARITY** — (a) and (d) with `--json`: stderr bytes identical, stdout JSON-only, no new envelope member; **(f) `--offline`** — the surface never renders; A9's listing renders instead; **(g) PROMPT D UNTOUCHED** — after `y` (and after `--network`) a divergent triple still renders PROMPT D (NAMED MUTANT: consent-by-network answering a divergence ⇒ RED); **(i) HOSTILE URL BYTES** — a stored URL carrying CR + U+202E renders in the notice as the exact visible escapes (NAMED MUTANT: a raw control byte on the stream ⇒ RED); **(j) THE RECONSTRUCT FORMS + RCPT-Q (A10.4 (j) at 6cba59d3, with rev8's HEAD-only fixture)** — `open --offline` on an image with FOUR artifact-bearing rows — a BORN row (branch + a side branch + a tag, penumbra payload at its relpath), an UNBORN row (sealed G: unborn `main` plus a committed `side`, penumbra at its relpath), a DETACHED row (its commit ALSO named by a branch — the fixture that CONCEALED rev7's failure, kept as a control), and a HEAD-ONLY row (the sealed full-capture recipe `git bundle create --all` run on a repository detached at a commit that NO branch or tag names, so `git bundle list-heads` prints exactly one entry, `<sha> HEAD` — no `refs/heads/*`, no `refs/tags/*`) — prints the born, unborn, detached and (for the HEAD-only row) detached idioms respectively (T-STAGE's forms, byte-exact; the detached form WITH the bare `'HEAD'` refspec), each naming the durable artifact `<dest>/.biv/repos/<id>/repo.bundle` (absolute) on the stream; the JSON rows carry `bundle_path` (dest-relative) and `reconstruct` byte-equal to the printed string; `<dest>/.biv/repos/<id>/repo.bundle` exists with the checksum for all four (RCPT-Q); then, with the HARNESS's own git (the user's step, never the product's), each printed command is run TWICE — into the non-empty (penumbra-populated) target and into an absent scratch target — rc 0 in all eight runs; born: HEAD symbolic to `refs/heads/<branch>`, the worktree populated, `refs/heads/side` and the tag present, the penumbra files untouched; unborn: HEAD symbolic to `refs/heads/main` with NO HEAD object (`rev-parse --verify HEAD` fails), `side` at `refs/heads/side`; detached: HEAD at `<sha>`, no symbolic ref; HEAD-only: HEAD at `<sha>` with no symbolic ref, `git cat-file -e '<sha>^{commit}'` rc 0 (the object IMPORTED), the tracked bytes materialised, the penumbra files untouched, and a colliding untracked file at a tracked path makes this form's checkout REFUSE (rc 1) with the file's bytes intact; nowhere a `refs/remotes/` ref or a remote; two controls: a bundle carrying a branch named `bvpk-restore` still yields rc 0 with that branch restored; a target holding an untracked file at a tracked path makes the born form's checkout REFUSE (rc 1) and leaves the file intact; every control in this leg and in (k) runs against the rev8 forms, never rc alone (NAMED MUTANT: the detached form printed WITHOUT the bare `'HEAD'` refspec — the rev7 wildcard-only form: on the HEAD-only fixture its fetch returns rc 0, imports nothing, and the checkout dies rc 128 "unable to read tree"; a fixture whose detached commit is ALSO named by a branch or tag does NOT discriminate it and is not this mutant's witness — a form selected by target state, a `git clone` printed, a fetch refusal, a missing or remote-namespaced ref, a HEAD object on the unborn row, a clobbered file, or `reconstruct` drifting from the printed line ⇒ RED); **(k) COPY-TEXT SAFETY AND EXACT ARGV** — artifact-present rows whose relpath, branch or dest carries, one per row, a copy-safe hazard: a single quote, a double quote, `$(printf SENTINEL)`, a backtick pair, `$HOME`, an embedded ordinary space (U+0020), a `*`; each printed command fed to `/bin/sh -c` with `git` replaced by an argv-recording stub yields argv operands BYTE-EQUAL to the raw values and NO sentinel expansion (the stub's record shows the literal `$(printf SENTINEL)` text); the refspec operands arrive unglobbed (NAMED MUTANT: a substituted sentinel, a split operand, a globbed refspec, or a serialization other than the single-quote rule ⇒ RED); **(l) THE FALLBACK** — artifact-present rows whose relpath carries, one per row, a NON-copy-safe value: TAB (U+0009), LF, ESC, U+202E, a lone 0xFF byte: NO command is printed; the fallback line renders with the values display-encoded per A8-R1; the JSON row has `bundle_path` and NO `reconstruct`; an ordinary sibling row on the same image still prints its command (NAMED MUTANT: a command printed for any of the five, a display escape inside a printed command or inside JSON `reconstruct`, or the ordinary row losing its command ⇒ RED); **(m) OFFLINE-UNBORN SHA** — an `--offline` image with the G row (unborn HEAD, bundle member — predicate TRUE) and the H row (unborn HEAD, no bundle, no eligibility — predicate FALSE): the G row is offline-pointer with `sha` `"(no commits)"` and `bundle_path`; the H row is payload-only-unborn with `sha` `null`, NO bundle fields, NO bundle line and `capture_mode` `null` whatever the in-memory enum holds, byte-identical to its consented-open bytes (NAMED MUTANT: null on the offline-pointer row, the literal on the engine-returned row, the H row relabelled, or a bundle field on it ⇒ RED); an overlay row → no `bundle_path`, no `reconstruct`, no bundle line, nothing under `<dest>/.biv/` (V-A10-8). `tests/test_envelope.cpp`: the schema gains `result.properties.repos` and the selftest blob pin moves in this commit — asserted by the existing pin test.
- [ ] **Step 7 (c4b): run to verify failure** — the row cases fail (`result.repos` absent), the D3 cases fail (no notice; git runs before any answer), the reconstruct cases fail (no artifact under `<dest>/.biv/`).
- [ ] **Step 8 (c4b): the implementation** — exactly the c4b bytes named in Step 3 (the `result.repos` emission + schema + pin; `render_network_consent` and the D3 decision in `main.cpp`'s open flow; the durable placement in `apply_archive`'s offline arm; `bundle_path` / `reconstruct` on artifact-bearing rows — outcome offline-pointer ∧ artifact presence, never keyed on `capture_mode`; `capture_mode` nullopt/null on shallow-pointer and payload-only-unborn rows; the bundle line with the detached form's bare `'HEAD'` refspec), each re-verified against the LOCKED A10 bytes (post-stamp 56abe662…, live) before writing. `Command.network` is read HERE and nowhere else.
- [ ] **Step 9 (c4b): run to verify pass, then commit (Step 0's gate re-run with `MODE=post` IMMEDIATELY before the block; the block refuses without its receipt)** — `./build/ci-macos/biv_tests` rc 0; `ctest --preset ci-macos -E '^safety-hardening$'` rc 0; `pytest harness/selftest/test_envelope.py` rc 0.

```bash
[ -s "$EVID/code/c4b-a10-lock.post.txt" ] && [ "$EVID/code/c4b-a10-lock.post.txt" -nt "$EVID/code/c4b-a10-lock.pre.txt" ] && [ "$(sed -n 1p "$EVID/code/c4b-a10-lock.post.txt")" = mode=post ] || { echo 'STOP: run the Task 4 Step 0 gate with MODE=post immediately before this commit'; exit 1; }
git add src/core/open/open.hpp src/core/open/open.cpp src/core/report/envelope.hpp src/core/report/envelope.cpp src/cli/main.cpp src/cli/url_consent.hpp src/cli/url_consent.cpp schemas/biv-json-envelope.v1.schema.json harness/selftest/test_envelope.py tests/test_cli.cpp tests/test_envelope.cpp
git commit -m "open: result.repos rows (RepoRestoreRow verbatim; failed kind/detail; offline fields) + schema in the same commit; the D2/D3 network-consent surface (notice before any git; decline => offline-pointer rows, exit 0; --network non-interactive; --json parity; no persistence); the durable offline artifact at <dest>/.biv/repos/<id>/repo.bundle + bundle_path/reconstruct (ONE single-quoted POSIX-sh idiom per stored HEAD state -- born / unborn / detached with the bare HEAD refspec; git clone for no row; copy-safe or the fallback line with no JSON reconstruct; bundle fields on artifact-bearing rows only; capture_mode null on shallow-pointer/payload-only-unborn rows) -- m-3 ADDENDUM 10 m3-addendum-10-6cba59d3-lock-20260920 @ 56abe662b82a189459764d461fd4de024f944a20421930dc86063c558fa0fdda; m-1 074712 s2"
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

### Task 6b — c6b, the NINE engine-error kinds (CONTINGENT on A11's lock — T-A11): the wire kinds, exit-map rows, error objects and sentences; the failure inventory + failed-mid-apply composition (A11 rev11 fce9cbfa LOCKED `m3-addendum-11-fce9cbfa-lock-20260920`; m-1 074712 §3; A9.3's same-commit rule; R-4.32)

**Files:** Modify `src/core/support/error.hpp`, `src/core/support/error.cpp` (nine kinds appended after `UnclaimedGitEntry`, in A11.1's order), `src/core/report/envelope.cpp` (the exit arms; the `failed` row's `kind`/`detail`), `src/core/pack/pack.cpp` (`engine_to_pack_error`'s nine-kind mapping replaces the c5 pass-through), `src/core/open/open.hpp` (rev25, MUST-2B-43: `RepoOutcomeRow` gains `std::optional<std::string> kind` and `std::optional<std::string> detail` — the failed row's kind and detail the composition below writes into the inventory, nothing else; LANDED in c6b `cd51937` before this line existed — the task-scope deviation is recorded under T-C6B), `src/core/open/open.cpp` (the open-side composition per A11 rev11 OPEN INVARIANT — master's MUST-2B-17 ruling (b), m-3 140044: the landed invariant KEPT — `result` null iff `error`; an engine failure at open is the top-level `error` and nothing else — NO `result.repos`, NO row inside `error`, NO rows stringified into facts; the ORCHESTRATOR (m-3's surface, no engine byte) WRITES `<partial_dir>/inventory.json` on failed-mid-apply — `<partial_dir>` = the ONE authorized partial-directory path (T-PARTIAL, RULED (A) by m-1 162306: the suffix is `.bvpk-open.partial`, the landed literal at open.cpp:637, untouched by 2b; c6b writes the inventory, `facts.partial_path`, and any `detect_partial`/`clean_partial` reader byte ONLY from the `partial_dir` value of that one site, and only after Step 0's gate has bound `$RUNNERS/m3-addendum-11-lock.txt`'s `partial_suffix=` / `partial_suffix_relay=` fields to the owner word by bytes): the completed rows, then the failing row with `kind` + `detail`, then the operation outcome `failed-mid-apply(step, repo_id, detail)`, in §2.2 order — one record; `error.detail` equals the failing row's `detail` byte-for-byte; `facts.partial_path` names the partial directory, `facts.repo_id` the failing row's manifest id; the inventory LIVES AND DIES WITH THE PARTIAL (what `detect_partial` reads next run and `clean_partial` removes) and is DISTINCT from §2.3's quarantine inventory of a SUCCEEDED apply — never conflated by name or reader (master 010159 (4); m-3 140045; m-1 171446); `execute_open`'s signature does not move at 2b), `src/cli/url_consent.hpp`, `src/cli/url_consent.cpp` (`render_engine_refusal_detail(kind, facts)` — the eleven A11.3 sentences, each rendered ONCE with every `<…>` value through `consent_display`), `src/cli/main.cpp` (the pack and open error paths fill `error.detail` from the renderer for the nine kinds), `schemas/biv-exit-map.v1.json` (nine rows appended after `UnclaimedGitEntry`), `tests/test_envelope.cpp` (ExpectedRow + literals; counts), `tests/test_pack.cpp`, `tests/test_open.cpp`, `tests/test_cli.cpp`, `harness/selftest/test_envelope.py` (the exit-map blob pin). The envelope schema does NOT move for the kinds (free string); the `failed` row's `kind`/`detail` fields are A10's row shape (c4b) — the `failed` outcome word stays in-memory / inventory vocabulary and is never rendered in an envelope at 2b (A11 rev11). INFORMATIVE at rev11 (m-1's O-3; the Master Reviewer's boundary 182105): the SUFFIX paragraph's partial + stage sentence DESCRIBES `open.cpp:785-805` at 1065872 (the partial checked first; stage detection only on the online non-empty-repos path; `error.path` the directory met and `facts.partial_dir` the partial — distinct from A11's `facts.partial_path`; the owned stage's cleanup a best-effort `remove_all` with its error ignored) — it asks NO deletion, refusal, retry policy or product byte of c6b.

- [ ] **Step 0: the lock gate — the EXECUTABLE block below, run TWICE: `MODE=pre` before the first c6b test byte (Step 1) and `MODE=post` immediately before the c6b commit (Step 5 refuses without the post receipt)** — it binds THREE carriers, none by existence. The lock file `$RUNNERS/m3-addendum-11-lock.txt` (written by the pair Planner at the lock) carries exactly one nonempty line each of `lock_id` (`m3-addendum-11-fce9cbfa-lock-20260920`, the A9-shaped id the ceremony declared), `doc_sha256` (re-hashed against the LIVE A11 document at its fixed pdc path — the post-stamp `e2776381…`), `pin_sha256` + `pin_commit` (rev20: the pre-stamp pin `fce9cbfa…` re-hashed from `git -C ../pdc show <pin_commit>:<doc>` at `2ce699d7…`, and present in both carriers), `relay`, `seal_relay`, `partial_suffix` (== `.bvpk-open.partial`, m-1's ruling 162306, the ONLY admissible value) and `partial_suffix_relay`. Every relay path is pdc-relative, `..`-free, beneath `master/relays` by real directory, TRACKED and UNMODIFIED in pdc (`git ls-files` + empty `status --porcelain`). (1) THE A11 LOCK CARRIER `relay` = m-3.planner's DESIGN relay to master (exact lines `FROM: m-3.planner`, `TO: master.master-planner`, `PHASE: DESIGN`, `AUTHORITY: design-only`) naming `lock_id` as a whole word and `doc_sha256`, and citing the A11 document in its `RELATED_CONTEXT`/`IN_REPLY_TO`. (2) THE SEAL CARRIER `seal_relay` = master's PLAN relay TO the pair (exact lines `FROM: master.master-planner`, `TO: intg.pair-planner`, `PHASE: PLAN`, `AUTHORITY: plan-only`), whose `IN_REPLY_TO` line is EXACTLY `relay` (lineage), naming the same `lock_id` and `doc_sha256`, containing the word SEALED; `seal_relay` ≠ `relay`. (3) THE SUFFIX WORD `partial_suffix_relay` — arm 1 the exact m-1 ruling (sha256 `82e37092a2a5405ef943c194ee313a3a09482432ac599e5a7e64213a74ad7a6f`, its FROM/TO/PHASE/AUTHORITY lines, the RULED (A) sentence) or arm 2 the already-bound lock carrier itself declaring `partial_suffix=.bvpk-open.partial`; any other path STOPs. Then the two one-site counts on `src/core/open/open.cpp` with the producer rc apart, the receipt `$EVID/code/c6b-partial-suffix.<pre|post>.txt` (carrying both carriers' sha256) and the post-vs-pre comparison. The carrier checks are the SHAPE OF THE A9 CEREMONY (m-3 `165214` → master `170242`): EXECUTED by the pair at B as the must-be-YES with the two A11 constants substituted for A9's (doc path, id prefix — the variant is the block plus exactly those two `sed` substitutions): pre + post PASS on the real 165214/170242 pair with `ae272647…`; nine must-be-NO controls each STOP before any receipt — the reviewer's bypass (`relay` = master 010159 with the exact ruling: `lock-from`), `seal_relay` = 010159 (`seal-lineage`), `relay` = another m-3 DESIGN relay 134813 (`lock-to`), the planned-shape id absent from the carriers (`lock-id-absent-in-lock-relay`), arm 2 with a lock relay lacking the field (`lock-relay-spelling`), seal == lock (`lock-seal-same-file`), a master-to-pair PLAN not replying to the lock relay 135421 (`seal-lineage`), a wrong doc sha (`a11-sha-mismatch`), and the unmodified A11 block with `relay` = 010159 (`lock-from`). The bytes below (planned from A11 rev11 `fce9cbfaf9eddfee7f3576a235117907fdd499da3f59d1024e7d20dc66db6684`, the LOCKED pin at pdc `2ce699d7…`; post-stamp `e2776381…` live; rev5 `33c69913…` was rev19's source, its deltas transcribed at rev20) are re-verified line-by-line against the locked bytes — a locked byte differing from rev11's is a new plan revision. The lock file IS WRITTEN (2026-09-20, from master's seal 185625, one field per line, `pin_sha256` / `pin_commit` beside the six fields this block always bound); at rev20 the block ALSO binds the pin (`git -C ../pdc show <pin_commit>:<doc>` re-hashed against `pin_sha256`; `pin_sha256` present in the lock relay and the seal). Walked at this seat on the REAL file from the candidate at 1065872 with a scratch `$EVID`: pre + post PASS (the receipt names the one site at open.cpp:785); must-be-NO controls — a wrong `doc_sha256` (`a11-sha-mismatch`), a wrong `pin_sha256` (`a11-pin-mismatch`), a wrong `pin_commit` (`a11-pin-show`), `seal_relay` = the lock relay (`lock-seal-same-file`), `partial_suffix_relay` spelled without `master/relays/` (master's own shorthand in 185625 — `suffix-relay-unbound`; the file carries the plan's pdc-relative form), `relay` = the A10 lock relay 184029 (`lock-id-absent-in-lock-relay`), a duplicated `lock_id` line (`field-lock_id-count-2`) — each STOPs before any receipt.

```bash
# Task 6b Step 0 — the A11 lock + T-PARTIAL gate (MUST-2B-25 / MUST-2B-26; rev20: the pin bound by git show). Run with MODE=pre BEFORE the first c6b test byte and
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
lock_id=$(field lock_id) || exit 1; doc_sha256=$(field doc_sha256) || exit 1; pin_sha256=$(field pin_sha256) || exit 1; pin_commit=$(field pin_commit) || exit 1; relay=$(field relay) || exit 1; seal_relay=$(field seal_relay) || exit 1
partial_suffix=$(field partial_suffix) || exit 1; partial_suffix_relay=$(field partial_suffix_relay) || exit 1
printf '%s' "$lock_id" | grep -q -E "$LOCK_ID_RE" || STOP lock-id-shape
for h in "$doc_sha256" "$pin_sha256"; do printf '%s' "$h" | grep -q -E '^[0-9a-f]{64}$' || STOP sha-shape; done; printf '%s' "$pin_commit" | grep -q -E '^[0-9a-f]{40}$' || STOP pin-commit-shape
[ "$partial_suffix" = .bvpk-open.partial ] || STOP partial-suffix-value          # m-1's ruling 162306: the ONLY admissible value
[ -s "$PDC/$A11_DOC" ] || STOP a11-absent
h=$(shasum -a 256 "$PDC/$A11_DOC" | cut -d' ' -f1) || STOP a11-hash; [ "$h" = "$doc_sha256" ] || STOP a11-sha-mismatch        # the LIVE doc = the post-stamp
p=$(git -C "$PDC" show "${pin_commit}:${A11_DOC}" | shasum -a 256 | cut -d' ' -f1) || STOP a11-pin-show; [ "$p" = "$pin_sha256" ] || STOP a11-pin-mismatch   # the reviewed pre-stamp bytes at their commit
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
hasw "$R1" "$lock_id" lock-id-absent-in-lock-relay; has "$R1" "$doc_sha256" doc-sha-absent-in-lock-relay; has "$R1" "$pin_sha256" pin-sha-absent-in-lock-relay
g=0; k=$(grep -c -E "^(RELATED_CONTEXT|IN_REPLY_TO): .*$(basename "$A11_DOC")" "$R1") || g=$?; [ "$g" -le 1 ] && [ "$k" -ge 1 ] || STOP lock-relay-not-citing-a11
# --- the SEAL carrier: master's PLAN relay TO the pair, IN_REPLY_TO the lock relay, naming the same id + sha, saying SEALED
line1 "$R3" 'FROM: master.master-planner' seal-from; line1 "$R3" 'TO: intg.pair-planner' seal-to; line1 "$R3" 'PHASE: PLAN' seal-phase; line1 "$R3" 'AUTHORITY: plan-only' seal-authority
line1 "$R3" "IN_REPLY_TO: $relay" seal-lineage; hasw "$R3" "$lock_id" lock-id-absent-in-seal; has "$R3" "$doc_sha256" doc-sha-absent-in-seal; has "$R3" "$pin_sha256" pin-sha-absent-in-seal
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
printf 'mode=%s\nlock_id=%s doc_sha256=%s\npin_sha256=%s pin_commit=%s\nrelay=%s sha256=%s\nseal_relay=%s sha256=%s\npartial_suffix=%s partial_suffix_relay=%s\nsite=%s\ncount_literal=%s count_any_partial=%s\n' "$MODE" "$lock_id" "$doc_sha256" "$pin_sha256" "$pin_commit" "$relay" "$r1sha" "$seal_relay" "$r3sha" "$partial_suffix" "$partial_suffix_relay" "$site" "$c1" "$c2" > "$EVID/code/c6b-partial-suffix.$MODE.txt" || STOP receipt
if [ "$MODE" = post ]; then
  [ -s "$EVID/code/c6b-partial-suffix.pre.txt" ] || STOP pre-receipt-absent
  cmp -s <(sed 1d "$EVID/code/c6b-partial-suffix.pre.txt") <(sed 1d "$EVID/code/c6b-partial-suffix.post.txt") || STOP pre-post-differ
fi
printf 'c6b-gate %s OK\n' "$MODE"
```
- [ ] **Step 1: the failing tests (A11.5, one case per leg, the git shim as the fault injector where a fixture cannot reach the kind)** — `tests/test_pack.cpp` / `tests/test_cli.cpp`: **(a)–(c)** the dirty / nested / submodule fixtures of Task 5 → `biv pack` exit 3, NO image, `error.kind` the wire kind, `error.path` and facts per A11.2 (`RepoNestedUnsupported`'s path = the nested child relpath; `RepoSubmoduleUnsupported`'s = the gitlink path), the sentence per A11.3 byte-golden, the exit-map row `transitional: true` (NAMED MUTANT ×3: exit 4, an image written, `InternalError`, or a byte moved ⇒ RED); **(d) UNMERGED** — three unmerged paths: exit 3, `facts.unmerged_count == "3"`, `facts.unmerged_paths` sorted-unique LF-joined, the sentence listing all three with NO "more" clause; a four-path variant lists three and "and 1 more" (NAMED MUTANT: the clause at N = 3, or an unsorted list ⇒ RED); **(e) REF UNCAPTURABLE** — the shim closes every route for one ref: exit 3, `facts.ref`, the sentence (NAMED MUTANT: the ref absent ⇒ RED); **(f) PROMISOR, BOTH ARMS** — the shim raises a missing-object failure on a promisor-flagged call: under `--offline` the sentence carries ", offline" and `facts.offline == "true"`; online "false" and no clause; exit 3 both (NAMED MUTANT: the arms swapped ⇒ RED); **(g) GIT FAILED, PACK** — the shim fails a pack-side call: exit 4, no image, the pack sentence with the op (NAMED MUTANT: exit 3 or an image ⇒ RED); `tests/test_open.cpp` / `tests/test_cli.cpp`: **(h) GIT FAILED / BUDGET, OPEN (A11 rev11)** — a two-repo fixture (the first restores, the second fails by the shim, then a budget variant) on a fresh target: exit 4, NO workspace at dest, `result` null, `error.kind` the wire kind, `facts.repo_id` / `facts.repo_relpath` / `facts.partial_path` naming the partial directory `<target>.bvpk-open.partial` (T-PARTIAL; the witness derives the expected path as `<dest-parent>/<dest-name>` + the `partial_suffix` READ FROM `$RUNNERS/m3-addendum-11-lock.txt`, never a literal in the test); the witness OPENS `<partial_path>/inventory.json` and finds the completed first row, the failing second row with `kind` + `detail` and the operation outcome, in order; `error.detail` == that row's `detail` byte-for-byte (NAMED MUTANT: a committed workspace, a non-null `result` beside `error`, a `repos` row anywhere in the envelope, `partial_path` absent, the inventory file absent or missing either row, or its `detail` differing from `error.detail` ⇒ RED); **(i) RESTORE FAILED** — the shim breaks a restore step: exit 4, `facts.engine_detail` the engine's `RepoRestoreFailed: <step>[: <detail>]` string, the sentence (NAMED MUTANT: the step absent ⇒ RED); **(j) OP ABSENT** — an engine error without an op fact renders "git call" (NAMED MUTANT: an empty op ⇒ RED); **(m) THE THREE CARRIERS (A11 rev11)** — a hostile engine detail (the shim fails a restore-side clone with stderr `fatal: unable to access 'https://example.invalid/repo.git/': Could not resolve host`) carrying the URL, a literal CR and a literal U+202E, and in a SECOND RUN a lone `0xFF` byte: the HUMAN sentence carries the URL byte-for-byte and A8-R1's escapes — CR as its CLAUSE-2 escape, the TWO bytes `\r` (5c 72), NOT clause 3's six-byte `\u000d` (which A8-R1 reserves for every OTHER C0 scalar, DEL and C1); U+202E as its clause-5 braced escape; the malformed byte as the scalar U+FFFD — on the stream EF BF BD, never the text `\uFFFD`; nothing truncated; JSON `error.detail` = that rendered sentence decoded byte-for-byte (escape text for CR/U+202E; the U+FFFD glyph); JSON `facts.engine_detail` = the SEMANTIC string under A8-R2 decoding to the raw bytes exactly (a literal CR, a literal U+202E; the malformed byte visibly replaced) — three separate assertions (NAMED MUTANT: `error.detail` carrying a raw control, `facts.engine_detail` carrying escape text, CR rendered as the six bytes `\u000d` in the sentence or in `error.detail` instead of the two bytes `\r`, the URL dropped or replaced, the literal text `\uFFFD` in place of EF BF BD, the two decoded JSON fields equal for the valid-hostile run, or the detail truncated ⇒ RED); **(k) UNKNOWN STAYS INTERNAL** — a synthetic `repo_engine_kind` outside the ten → `InternalError`, exit 4 (NAMED MUTANT: a typed row for an unknown kind ⇒ RED); **(l) COUNTS, BY MEMBERSHIP (A11 rev11)** — `tests/test_envelope.cpp`, at the stage AFTER A9 + A11: `ErrKind` is EXACTLY the 37-member set (the pin's 28 − `RepoDiscoveredUnsupported` + `UnclaimedGitEntry` + the nine; `to_string` round-trips every member), the exit map EXACTLY the 38-row set under the same composition, `transitional: true` EXACTLY the six { SourceUnreadableSubpath, UnsupportedFileTypeSkipped, UsageError, RepoDirtyUnsupported, RepoNestedUnsupported, RepoSubmoduleUnsupported }, refusal/3 rows 20, mid-fail/4 rows 7, divergence/2 7, advisory/0 3, usage/5 1, the InternalError row byte-identical — each asserted as the SET with the size a consequence (NAMED MUTANT ×3: a count off by one; the rev7 totals — 36 enumerators, seven transitional — which the composition must FAIL; `RepoDiscoveredUnsupported` or any retired member kept to satisfy a stale size ⇒ RED); `pytest harness/selftest/test_envelope.py` pins recomputed in this commit.
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
- [ ] **Step 4: run to verify pass** — `ctest --preset ci-macos -E '^safety-hardening$'` rc 0; `pytest harness/selftest/test_envelope.py` rc 0; `python3 -c 'import json;print(len(json.load(open("schemas/biv-exit-map.v1.json"))["rows"]))'` == 38; the (l) membership case green (37 enumerators, six transitional by name).
- [ ] **Step 5: commit (Step 0's gate re-run with `MODE=post` IMMEDIATELY before this block; the block refuses without its receipt)** —

```bash
[ -s "$EVID/code/c6b-partial-suffix.post.txt" ] && [ "$EVID/code/c6b-partial-suffix.post.txt" -nt "$EVID/code/c6b-partial-suffix.pre.txt" ] && [ "$(sed -n 1p "$EVID/code/c6b-partial-suffix.post.txt")" = mode=post ] || { echo 'STOP: run the Task 6b Step 0 gate with MODE=post immediately before this commit'; exit 1; }
git add src/core/support/error.hpp src/core/support/error.cpp src/core/report/envelope.cpp src/core/pack/pack.cpp src/core/open/open.hpp src/core/open/open.cpp src/cli/url_consent.hpp src/cli/url_consent.cpp src/cli/main.cpp schemas/biv-exit-map.v1.json tests/test_envelope.cpp tests/test_pack.cpp tests/test_open.cpp tests/test_cli.cpp harness/selftest/test_envelope.py
git commit -m "report: the nine engine-error wire kinds (three transitional fence refusals/3; Unmerged/RefUncapturable/PromisorObjectsUnavailable refusal/3; GitInvocationFailed/GitBudgetExpired/RepoRestoreFailed mid-fail/4), whole-operation grain, A11.2 error objects, A11.3 sentences rendered once; open failed row + failed-mid-apply composition -- m-3 ADDENDUM 11 m3-addendum-11-fce9cbfa-lock-20260920 @ e27763812422f010306a8a3ac1b31f8129d13beb0e724c0de48bfb2eb9c7d895; m-1 074712 s3; ErrKind 28->37 (by membership); exit map 29->38; transitional 3->6"
git rev-parse HEAD > "$EVID/commits.c6b.txt"
```

### Task 6c — c6m, R-4.65 RED-2: the directory-mtime pass after the last write into the partial (restore-apply §5; m-3 164214 V2-1..6 — T-RED2, SEALED + CONFIRMED; rev22)

**Files:** Modify `src/core/open/open.cpp` (`execute_archive` only), `tests/test_open.cpp` (the source-order oracle), `tests/test_cli.cpp` (the CLI witness).
**Interfaces:** none new. `execute_archive`'s order becomes `apply_archive` → `restore_repos` → every other writer into the partial that c4b / c6b placed after `restore_repos` → the directory-mtime pass → `fsync_tree` → the single rename (§2.1's all-inside-the-partial order unchanged in kind).

- [ ] **Step 0: the write census at the c6b head** — `[ "$(git rev-parse HEAD)" = "$(cat "$EVID/commits.c6b.txt")" ] || STOP`; every statement in `execute_archive` between `apply_archive(` and `fsync_tree(partial_dir)` that creates, writes, renames or sets metadata under `partial_dir` (`restore_repos`, and any c4b / c6b writer — the offline durable artifact among them) is listed with file:line to `$EVID/code/c6m-writes.txt`; the pass moves to immediately after the LAST of them (V2-1's record for m-3.implementer).
- [ ] **Step 1: the failing tests** — (a) `tests/test_open.cpp` "Task 4 open occupancy and destination contracts stay bounded": the `calls` array gains `"set_mtime(partial_dir / std::filesystem::path{rel}, it->mtime_s, it->mtime_ns)"` between `"restore_repos(plan, partial_dir, stage, report)"` and `"fsync_tree(partial_dir)"` (seven calls, `std::array<std::string_view, 7>`), so a pass BEFORE `restore_repos` reds (V2-5). (b) `tests/test_cli.cpp` `TEST_CASE("c6m a payload directory above a restored repository keeps its archived mtime", "[cli][c6m]")` on the existing canonical temp-root helper (biv refuses symlinked ancestors): a workspace holding `README.md`, a payload directory `docs` with `docs/notes.txt`, and a CLEAN full-capture repository `docs/inner` (no remote; one tracked `sub/t.txt`); after the commit every source entry's mtime is set to 2020-01-01T00:00:00.123456789Z with `utimensat` (`docs` last); `biv pack` rc 0; `biv open <image> --dest <dest>` non-interactive rc 0 (a bundle row needs no network); `mtime(<dest>/docs)` == `mtime(<ws>/docs)` and `mtime(<dest>/docs/notes.txt)` == the source's, seconds AND nanoseconds, both read by `lstat` (the source is unchanged by pack); `git -C <dest>/docs/inner status --porcelain=v2` EMPTY; the `--offline` twin (the same image, a fresh dest) asserts the same `docs` equality. Receipt lines `leg=c6m-network provenance=product-packed` and `leg=c6m-offline provenance=product-packed` via `BIV_LEG_RECEIPTS`.
- [ ] **Step 2: run at the c6b head = THE NAMED MUTANT (V2-6: `ef8e492`'s order, the pre-fix bytes)** — `./build/ci-macos/biv_tests '[c6m]'` FAILS on the network case (`<dest>/docs` carries restore time) and PASSES on the offline twin; `./build/ci-macos/biv_tests 'Task 4 open occupancy and destination contracts stay bounded'` FAILS (the pass precedes `restore_repos`); both runs with rc and the failing assertion lines to `$EVID/code/c6m-mutant.txt`.
- [ ] **Step 3: the implementation** — move the six-line loop (`for (auto it = dirs.rbegin(); it != dirs.rend(); ++it) { … set_mtime(partial_dir / std::filesystem::path{rel}, it->mtime_s, it->mtime_ns) … }`) BYTE-UNCHANGED to immediately after the last writer Step 0 recorded and before `fsync_tree(partial_dir)`; the `OpenReport report{…}` construction stays where it is (it writes nothing). V2-3: the pass iterates `dirs` only (image directory members), deepest first — nothing stamps a directory the image does not record, and no harness row moves. V2-4: a `set_mtime` failure still returns `with_partial_dir(...)`.
- [ ] **Step 4: run to verify pass** — `./build/ci-macos/biv_tests '[c6m]'` rc 0 and the source-order case rc 0; `ctest --preset ci-macos -E '^safety-hardening$'` rc 0.
- [ ] **Step 5: commit** —

```bash
git add src/core/open/open.cpp tests/test_open.cpp tests/test_cli.cpp
git commit -m "open: the directory-mtime pass after the last write into the partial (after restore_repos), before fsync_tree -- a payload directory above a restored repository keeps its archived mtime (restore-apply section 5); R-4.65 RED-2 in c4a ef8e492; m-3 164214 RED2_ORCHESTRATION confirm (V2-1..6); the source-order oracle names the pass"
git rev-parse HEAD > "$EVID/commits.c6m.txt"
```

### Task 6q — c6q, R-4.70: each PAYLOAD-ONLY repository row's whole working tree archived as ordinary payload (ADDENDUM-N N-R3/N-R4 on N3; ADDENDUM-A §A6 :194 with H; m-1 225134 `C6P_MEMBER_SET: stop`; master 011148 — reproduced at m-1's seat, at master's and at the pair Planner's; due BEFORE c6p lands; rev26)

**Files:** Modify `src/core/scan/scan.hpp`, `src/core/scan/scan.cpp` (`ScanExclusions::claimed_markers` + `claims_marker`, the `.git` test's claim widened to it, `scan_subtree`), `src/core/pack/pack.cpp`, `tests/test_scan.cpp`, `tests/test_pack.cpp`, `tests/test_cli.cpp`. `src/core/repo/**` is NOT touched (`repo::restore_invokes_git` is read, never changed — veto 9). `src/core/open/**` is NOT touched: the tree lands through the first pass ("the payload (working tree) lands via the ordinary payload path", N-R4), and `restore_entry` returns a payload-only row right after `validate_entry`, which validates fields only and acts on no path (`restore.cpp:95-135`, `:448-457` at `e5afe9d`, read at the pair Planner's seat) — so c6q is complete at its own head.
**Interfaces:** `scan.hpp`: `struct ScanExclusions` gains `std::vector<std::string> claimed_markers;` and `bool claims_marker(std::string_view canonical_rel) const;` — a `.git` entry directly under a claimed marker's directory is skipped exactly as a claimed subtree's is, and that directory's other entries are walked; `expected<void> scan_subtree(const std::filesystem::path& source_root, const ignore::Matcher& matcher, const ScanExclusions& exclusions, std::string_view subtree_rel, ScanResult& into)` — for a NON-ROOT `subtree_rel`, emits that directory ITSELF as a directory node first (the walk's own node construction for that path); for the ROOT (`subtree_rel == ""`, the canonical form of `.` — `ScanExclusions::canonical`, `scan.cpp:202-205`) emits NO node for the root itself (rev27, MUST-2B-47: the workspace root is never a payload member — the residue walk never emits it, and a root node would be the bare member `payload/`, which the open-side path refuses as an empty remainder, `open.cpp:520-523`); then walks it exactly as `scan` walks the root (the matcher, `.bivignore` pruning into `into.pruned` with its source, the `.biv` skip, unsupported into `into.skipped_unsupported`, unreadable into `into.unreadable`, a claimed subtree skipped, an UNCLAIMED `.git` → `UnclaimedGitEntry` as today); relpaths workspace-relative; parents before children; nodes appended to `into.payload`. `pack.cpp`: the residue `scan` call and its exclusions stay BYTE-UNCHANGED (every discovered boundary excluded, so a residue scan error keeps today's precedence — before any git runs); AFTER the capture loop, one block: `ScanExclusions q` with `repo_subtrees` = the canonical relpaths of every entry with `repo::restore_invokes_git(entry)` true and `claimed_markers` = those with it false; then, for each entry with it false, in discovery order, `scan_subtree(source, matcher->matcher, q, ScanExclusions::canonical(entry.relpath), *scan_result)` — an error returns through `cleanup_error` as the residue scan's does. The partition is taken on the FINAL entries because `restore_invokes_git` reads `bundle` (set by capture) and `eligibility` (set by `run_eligibility`). A ROOT payload-only row is the whole workspace: the residue `scan` returns EMPTY once the root boundary is claimed (`scan.cpp:278`), so `scan_subtree(…, "", …)` supplies every member — measured at `e5afe9d` from a clean build (rev27): a workspace that is itself a depth-1 clone, and one that is itself a fresh `git init` holding an untracked file, each packed rc 0 with ONLY `manifest.json` and `checksums.json` — R-4.70's worst form, the whole workspace lost silently. Nested payload-only rows are unreachable at 2b (T-ARM (ii)'s nested fence refuses every nested pack): one `scan_subtree` per payload-only row, no nesting logic written (registered, Out of scope).

- [ ] **Step 1: the failing tests** —
  (a) `tests/test_scan.cpp` `[scan][c6q]`: a directory `r` holding a `.git/` directory, `sub/t.txt`, `x.log`, `drop.txt` and a FIFO, with a workspace `.bivignore` = `r/drop.txt` → `scan_subtree(root, matcher, {.claimed_markers = {"r"}}, "r", into)` succeeds; `into.payload` relpaths EXACTLY { `r`, `r/sub`, `r/sub/t.txt`, `r/x.log` } in parents-before-children order, each node field-equal to what `scan()` records for the same path; `r/drop.txt` in `into.pruned` with its `.bivignore` source; the FIFO in `into.skipped_unsupported`; no `.git` relpath. GUARD (holds on both sides, not a mutant): the same call with EMPTY `claimed_markers` → `UnclaimedGitEntry` naming `r/.git`. ROOT (rev27, MUST-2B-47) — a workspace root holding `.git/`, `a.txt` and `d/b.txt` → `scan_subtree(root, matcher, {.claimed_markers = {""}}, "", into)` succeeds and `into.payload` relpaths are EXACTLY { `a.txt`, `d`, `d/b.txt` } — no empty relpath, no `.git`.
  (b) `tests/test_pack.cpp` `TEST_CASE("c6q pack archives each payload-only row's whole working tree", "[pack-repos][c6q]")` — m-1's fixture, reality-shaped: a workspace holding `README.md`; `shal` = `git clone --depth 1 file://…/remote` of a two-commit remote tracking `sub/t.txt`, `b.txt` and `.gitignore` = `*.log`, plus an untracked, IGNORED `x.log` created after the clone; `fresh` = `git init` holding an untracked `sub/f.txt`, no commit, no ref; a clean full repo `lib` (tracked `a.txt`) → rc 0; on the manifest rows `repo::restore_invokes_git` is false for `shal` (`shallow` present) and `fresh` (`unborn`) and true for `lib` — ASSERTED; the `payload/` members, counted WITH MULTIPLICITY, EXACTLY { `payload/README.md`, `payload/fresh`, `payload/fresh/sub`, `payload/fresh/sub/f.txt`, `payload/shal`, `payload/shal/.gitignore`, `payload/shal/b.txt`, `payload/shal/sub`, `payload/shal/sub/t.txt`, `payload/shal/x.log` } — `.gitignore` does NOT prune a payload-only row (it is walked like residue; `.bivignore` only); every `.git` path and every `payload/lib…` path ABSENT (a git-capable row's subtree stays excluded; its penumbra is c6p's); each member's mode and mtime equal the source's `lstat`. PRUNE — the same with `.bivignore` = `shal/sub/` → no `payload/shal/sub…` member and the prune-summary advisory names `shal/sub` with its `.bivignore` source. ROOT (rev27, MUST-2B-47; each workspace is ITSELF the repository, so its manifest row's relpath is `.`) — ROOT-SHALLOW: the workspace is a `git clone --depth 1 file://…/remote` of the same two-commit remote, plus an untracked IGNORED `x.log` and an untracked `extra.txt` → rc 0; the row `shallow` present and `restore_invokes_git` false (ASSERTED); the `payload/` members, counted WITH MULTIPLICITY, EXACTLY { `payload/.gitignore`, `payload/b.txt`, `payload/extra.txt`, `payload/sub`, `payload/sub/t.txt`, `payload/x.log` }; ROOT-UNBORN: the workspace is a fresh `git init` holding an untracked `sub/f.txt`, no commit, no ref → rc 0; the row `unborn`, `restore_invokes_git` false (ASSERTED); the members EXACTLY { `payload/sub`, `payload/sub/f.txt` }. In BOTH: no member named bare `payload/` (and none whose path after `payload/` is empty), every `.git` path ABSENT, each member's mode and mtime equal the source's `lstat`.
  (c) `tests/test_cli.cpp` `[cli][c6q]`, receipts via `BIV_LEG_RECEIPTS`: (b)'s workspace without `lib` → `biv pack` rc 0 → `biv open <image> --dest <dest>` rc 0 and, separately, `biv open <image> --dest <dest2> --offline` rc 0, each through the request-trace shim: every file and directory of `shal` and `fresh` — `.gitignore` and `x.log` included — byte-, mode- and mtime-equal (seconds and nanoseconds) to the source under `<dest>` and `<dest2>` (directories stamped by c6m's pass); `<dest>/shal/.git` and `<dest>/fresh/.git` ABSENT; ZERO git lines in the shim log for each open; `result.repos` rows `shallow-pointer` (shal) and `payload-only-unborn` (fresh) as at the c6m head (the row surface does not move); `result.restored_member_count` == the image's `payload/` member count. ROOT (rev27, MUST-2B-47) — (b)'s ROOT-SHALLOW and ROOT-UNBORN workspaces, each packed and then opened `biv open <image> --dest <dest>` and, separately, `--dest <dest2> --offline`, each through the request-trace shim → rc 0; every file and every NON-ROOT directory of the workspace byte-, mode- and mtime-equal to the source under `<dest>` and `<dest2>` (the destination root itself is never a member and its mtime is not asserted); `<dest>/.git` and `<dest2>/.git` ABSENT; ZERO git lines in the shim log for each open; the single `result.repos` row, relpath `.`, `shallow-pointer` (ROOT-SHALLOW) or `payload-only-unborn` (ROOT-UNBORN), as at the c6m head.
- [ ] **Step 2: run at the c6m head = THE NAMED MUTANT (m-1 225134: c5's unconditional boundary exclusion — every discovered boundary pushed into `ScanExclusions`, no carve-out)** — `./build/ci-macos/biv_tests '[c6q]'`: (a) fails to compile (no `scan_subtree`, no `claimed_markers`); (b) RED (the members are `payload/README.md` alone — the reproduction's shape); (c) RED (neither tree under `<dest>` / `<dest2>`); the ROOT cases RED (the image holds `manifest.json` and `checksums.json` only — the shape measured at the pair Planner's seat, rev27); the ROOT unit case fails to compile with (a). Recorded to `$EVID/code/c6q-mutants.txt`.
- [ ] **Step 3: the implementation** — exactly the Interfaces above. `scan.cpp`: the `.git` test's claim becomes `exclusions.claims(rel_dir) || exclusions.claims_marker(rel_dir)` and nothing else in `walk` moves; `scan_subtree` reuses `walk` (for a non-root start, the start directory's node built as the walk builds any node; for the root, no node — MUST-2B-47). `pack.cpp`: the one post-capture block; the report block, `write_payload_member` and `checksums` untouched (the new nodes travel the ONE payload writer).
- [ ] **Step 4: run to verify pass + the named mutants** — `./build/ci-macos/biv_tests '[c6q]'` rc 0; `./build/ci-macos/biv_tests '[c6m]'` rc 0; `ctest --preset ci-macos -E '^safety-hardening$'` rc 0; the RepoEntry census (Task 5 Step 5's command) rc 0. THE MUTANTS, each on the worktree copy with its file saved to `$EVID/code/<file>.c6q` first and restored after (`cmp` == 0, rebuild, `[c6q]` rc 0 again), each result to `$EVID/code/c6q-mutants.txt`: Mq1 (`scan.cpp`) `claims_marker` dropped from the `.git` test → (b) and (c) RED with `UnclaimedGitEntry` naming `shal/.git` or `fresh/.git`; Mq2 (`pack.cpp`) the partition ignored — `scan_subtree` called for EVERY entry → (b) RED (`payload/lib/a.txt` present: a git-capable row's tracked bytes archived as payload); Mq3 (`scan_subtree`) the row directory's own node not emitted → (b) RED (`payload/shal`, `payload/fresh` absent) and (c) RED (the observed failure recorded) — the ROOT cases stay green under Mq3 (they carry no row-directory node); Mq4 (rev27, MUST-2B-47; `scan_subtree`) the root exception deleted, so the root's own empty-relpath node is emitted → the ROOT cases RED (a bare `payload/` member — the pack or the open refusing it, the observed one recorded) and the ROOT unit case RED (an empty relpath in `into.payload`), while every non-root case stays green. Each removes the only code that can produce or prevent its member.
- [ ] **Step 5: commit** —

```bash
git add src/core/scan/scan.hpp src/core/scan/scan.cpp src/core/pack/pack.cpp tests/test_scan.cpp tests/test_pack.cpp tests/test_cli.cpp
git commit -m "pack: each payload-only row's whole working tree archived as ordinary payload, its .git claimed (restore_invokes_git false: N-R3/N-R4 shallow, A 6 + H zero-ref unborn); the residue scan and its error precedence unchanged; R-4.70 in c5 5aeb81c; m-1 225134 C6P_MEMBER_SET stop, carried by master 011148"
git rev-parse HEAD > "$EVID/commits.c6q.txt"
```

### Task 6d — c6p, R-4.65 RED-1: each repository row's penumbra packed as payload and laid after the row's restore (pack-engine §1.1/§1.3/§3.2; restore-apply §2.2 step 5, §2.5; m-1 141529 §2; m-3 164214 V1-1..7 — HOLD on T-RED1; rev22. rev26: HOLD on T-C6P as well — m-4 arm A with AA-1..4, the shared dot-git predicate at both writers, m-3 225041, m-1 225134; c6q first)

**Files:** Modify `src/core/pack/pack.cpp`, `src/core/scan/scan.hpp`, `src/core/scan/scan.cpp` (`stat_node` only — the walk's `.biv` skip and its `.git` test untouched at c6q's bytes), `src/core/open/open.hpp` (rev26: the `detail` declarations below, nothing else), `src/core/open/open.cpp`, `tests/test_scan.cpp`, `tests/test_pack.cpp`, `tests/test_open.cpp`, `tests/test_cli.cpp`. `src/core/repo/**` is NOT touched (the engine already records the set; veto 9).
**Interfaces:** `scan.hpp`: `expected<std::optional<Node>> stat_node(const std::filesystem::path& source_root, const std::string& relpath)` — the walk's own node construction (kind, size, mode, mtime s/ns, symlink target) for ONE path by `lstat`; `std::nullopt` for a type the walk skips as unsupported; `SourceUnreadableSubpath`-class error for an unreadable or vanished path; the walk calls it for every node, and (rev26) `scan_subtree` builds the row directory's node with it (one construction, DRY). `pack.cpp` (file-local): `expected<std::vector<scan::Node>> penumbra_nodes(const std::filesystem::path& source, const std::vector<repo::RepoEntry>& entries, const ignore::Matcher& matcher, scan::ScanResult& diagnostics)` — members in parents-before-children order; pruned paths appended to `diagnostics.pruned` (the topmost pruned prefix once), unsupported to `diagnostics.skipped_unsupported`, unreadable to `diagnostics.unreadable` (never silent, §3.2). `open.hpp`, `namespace biv::open::detail` (rev26: DECLARED so the tests CALL them — rev25 made them file-local, which left Step 1 (c) able only to search the source text, and a text search passes whatever the function computes; defined in `open.cpp`): `std::optional<std::string> owning_row(std::string_view payload_rel, const std::vector<std::string>& row_rels)`; `std::vector<std::string> row_relpaths(const std::vector<repo::RepoEntry>&)` — GIT-CAPABLE rows only (an entry with `!repo::restore_invokes_git(entry)` is omitted, so a payload-only row's tree never enters the deferred writer and lands through the first pass — T-C6P (c)), `"."` → `""`; `bool is_dotgit_component(std::string_view segment) noexcept` and `bool is_dotbiv_component(std::string_view segment) noexcept` — THE ONE PREDICATE (T-C6P (a) AA-3), TRUE iff ANY clause holds, transcribed from git `3bc0341126508f78f5869cbfc0005e987efdf0c7` (the prior art m-4 names; read at the bytes, not recalled): (i) FOLD — `read-cache.c` `verify_dotfile` matches `.git` "case-insensitively here, even if ignore_case is not set": `segment` equals `.git` under ASCII case-folding; (ii) HFS — `utf8.c` `next_hfs_char` + `is_hfs_dot_generic`: decode UTF-8 and DROP every U+200C U+200D U+200E U+200F U+202A U+202B U+202C U+202D U+202E U+206A U+206B U+206C U+206D U+206E U+206F U+FEFF wherever it occurs (before the dot included); what remains is `.` then `g` `i` `t`, each compared by ASCII `tolower`, then the end — a remaining code point above 127, or malformed UTF-8, is NOT a match; (iii) NTFS — `path.c` `is_ntfs_dotgit`: the segment begins with `.git` or `git~1` (every letter case-insensitive), followed by zero or more `.` or ` ` characters, then the END of the segment or a `:` (git refuses every alternate data stream of `.git`; m-4's word names trailing dots and spaces — the `:` stop is git's own, transcribed with it and FLAGGED for m-4's byte review). `is_dotbiv_component`: the same three clauses with `biv` for `git` and `biv~1` for `git~1` (m-4: "the same fold applies to the `.biv` prefix refusal"; `biv~1` is the pair Planner's transcription of `git~1` onto `.biv`, FLAGGED for m-4's byte review). Neither predicate reads configuration, the host, or the filesystem. `open.cpp` (file-local): `expected<void> write_member(container::TarReader&, const container::MemberMeta&, const std::filesystem::path& out_path, std::vector<container::MemberMeta>& dirs)` (the ONE member writer both passes use — V1-5); `expected<uint64_t> apply_owned_members(const std::filesystem::path& image, const ArchivePlan& plan, const std::filesystem::path& partial_dir, const std::string& row_rel, const std::vector<std::string>& row_rels, std::vector<container::MemberMeta>& dirs, bool verify)`; `apply_archive` gains `const std::vector<std::string>& row_rels`; `restore_repos` gains `image`, `dirs`, `verify` and adds each row's placed count to `report.restored_member_count`.

- [ ] **Step 0: the T-RED1 gate — the EXECUTABLE block below, run TWICE from the worktree: `MODE=pre` before the first c6p test byte (Step 1) and `MODE=post` immediately before the commit (Step 5 refuses without the post receipt).** It binds SEVEN carriers by bytes (rev26): rev24's three (master's carry 211701 TO this seat citing both relays; m-3's whole line `RED1_ROOT_ROW: defer`; m-1's whole line `RED1_PENUMBRA_DIRS: confirm`) and T-C6P's four (master's carry 011148 TO this seat citing all three; m-4's whole line `C6P_ABSENT_ANCESTOR: arm-a`; m-3's `C6P_V1_READING: confirm`; m-1's `C6P_MEMBER_SET: stop`), each resolved under `$PDC/master/relays/`, tracked and unmodified, the seven pairwise distinct, each word exactly once with no contradicting second line, and the post receipt's seven relay lines equal to the pre receipt's. The receipts are `c6p-owner-words.rev26.{pre,post}.txt` — NOT rev25's names, which impl-6's run already holds (`$EVID/code/c6p-owner-words.pre.txt`, evidence, never overwritten).

```bash
# Task 6d Step 0 — T-RED1 + T-C6P: five owner words and two carries bound by bytes, MODE=pre|post (rev22; rev26: seven carriers)
set -o pipefail
STOP() { printf 'STOP-c6p-gate %s line=%s\n' "$1" "${BASH_LINENO[0]}" >&2; exit 1; }
[ -n "$RUNNERS" ] && [ -n "$EVID" ] && [ -d "$EVID/code" ] || STOP env
case "${MODE:-}" in pre|post) ;; *) STOP mode;; esac
F=$RUNNERS/red1-owner-words.txt; [ -s "$F" ] || STOP file-absent
g=0; n=$(grep -c . "$F") || g=$?; [ "$g" -eq 0 ] && [ "$n" -eq 7 ] || STOP "field-count-$n"
field() { g=0; n=$(grep -c -E "^$1=" "$F") || g=$?; [ "$g" -le 1 ] && [ "$n" -eq 1 ] || STOP "field-$1-count-$n"
  v=$(sed -n -E "s/^$1=([^[:space:]]+)$/\1/p" "$F") || STOP "field-$1-read"; [ -n "$v" ] || STOP "field-$1-empty"; printf '%s' "$v"; }
carry=$(field carry_relay) || exit 1; m3=$(field m3_relay) || exit 1; m1=$(field m1_relay) || exit 1
carry2=$(field c6p_carry_relay) || exit 1; m4c=$(field m4_c6p_relay) || exit 1; m3c=$(field m3_c6p_relay) || exit 1; m1c=$(field m1_c6p_relay) || exit 1
PDC=$(cd ../pdc && pwd -P) || STOP pdc; [ -d "$PDC/master/relays" ] || STOP pdc-tree
resolve() { case "$1" in /*|*..*) STOP "path-$2";; esac; [ ! -L "$PDC/$1" ] && [ -f "$PDC/$1" ] || STOP "notfile-$2"
  d=$(cd "$PDC/$(dirname "$1")" && pwd -P) || STOP "dir-$2"; case "$d/" in "$PDC/master/relays/"*) ;; *) STOP "outside-$2";; esac
  git -C "$PDC" ls-files --error-unmatch -- "$1" >/dev/null 2>&1 || STOP "untracked-$2"; git -C "$PDC" diff --quiet HEAD -- "$1" || STOP "modified-$2"; printf '%s' "$PDC/$1"; }
CF=$(resolve "$carry" carry) || exit 1; F3=$(resolve "$m3" m3) || exit 1; F1=$(resolve "$m1" m1) || exit 1
C2=$(resolve "$carry2" carry2) || exit 1; G4=$(resolve "$m4c" m4c) || exit 1; G3=$(resolve "$m3c" m3c) || exit 1; G1=$(resolve "$m1c" m1c) || exit 1
u=0; k=$(printf '%s\n' "$CF" "$F3" "$F1" "$C2" "$G4" "$G3" "$G1" | LC_ALL=C sort -u | grep -c .) || u=$?; [ "$u" -eq 0 ] && [ "$k" -eq 7 ] || STOP "same-relay-$k"
line1() { g=0; k=$(grep -c -x -F -- "$2" "$1") || g=$?; [ "$g" -le 1 ] && [ "$k" -eq 1 ] || STOP "$3"; }
count1() { g=0; k=$(grep -c -E -- "$2" "$1") || g=$?; [ "$g" -le 1 ] && [ "$k" -eq 1 ] || STOP "$3"; }
line1 "$F3" 'FROM: m-3.planner' m3-from; line1 "$F3" 'RED1_ROOT_ROW: defer' m3-word; count1 "$F3" '^RED1_ROOT_ROW:' m3-word-cardinality
line1 "$F1" 'FROM: m-1.planner' m1-from; line1 "$F1" 'RED1_PENUMBRA_DIRS: confirm' m1-word; count1 "$F1" '^RED1_PENUMBRA_DIRS:' m1-word-cardinality
line1 "$G4" 'FROM: m-4.planner' m4c-from; line1 "$G4" 'C6P_ABSENT_ANCESTOR: arm-a' m4c-word; count1 "$G4" '^C6P_ABSENT_ANCESTOR:' m4c-word-cardinality
line1 "$G3" 'FROM: m-3.planner' m3c-from; line1 "$G3" 'C6P_V1_READING: confirm' m3c-word; count1 "$G3" '^C6P_V1_READING:' m3c-word-cardinality
line1 "$G1" 'FROM: m-1.planner' m1c-from; line1 "$G1" 'C6P_MEMBER_SET: stop' m1c-word; count1 "$G1" '^C6P_MEMBER_SET:' m1c-word-cardinality
line1 "$CF" 'FROM: master.master-planner' carry-from; line1 "$CF" 'TO: intg.pair-planner' carry-to
line1 "$C2" 'FROM: master.master-planner' carry2-from; line1 "$C2" 'TO: intg.pair-planner' carry2-to
cite() { g=0; k=$(grep -c -F -- "$1" "$3") || g=$?; [ "$g" -le 1 ] && [ "$k" -ge 1 ] || STOP "$2"; }
cite "$m3" carry-cites-m3 "$CF"; cite "$m1" carry-cites-m1 "$CF"
cite "$m4c" carry2-cites-m4c "$C2"; cite "$m3c" carry2-cites-m3c "$C2"; cite "$m1c" carry2-cites-m1c "$C2"
h=0; sc=$(shasum -a 256 "$CF" | cut -d' ' -f1) || h=$?; [ "$h" -eq 0 ] && [ -n "$sc" ] || STOP sha-carry
h=0; s3=$(shasum -a 256 "$F3" | cut -d' ' -f1) || h=$?; [ "$h" -eq 0 ] && [ -n "$s3" ] || STOP sha-m3
h=0; s1=$(shasum -a 256 "$F1" | cut -d' ' -f1) || h=$?; [ "$h" -eq 0 ] && [ -n "$s1" ] || STOP sha-m1
h=0; sc2=$(shasum -a 256 "$C2" | cut -d' ' -f1) || h=$?; [ "$h" -eq 0 ] && [ -n "$sc2" ] || STOP sha-carry2
h=0; s4c=$(shasum -a 256 "$G4" | cut -d' ' -f1) || h=$?; [ "$h" -eq 0 ] && [ -n "$s4c" ] || STOP sha-m4c
h=0; s3c=$(shasum -a 256 "$G3" | cut -d' ' -f1) || h=$?; [ "$h" -eq 0 ] && [ -n "$s3c" ] || STOP sha-m3c
h=0; s1c=$(shasum -a 256 "$G1" | cut -d' ' -f1) || h=$?; [ "$h" -eq 0 ] && [ -n "$s1c" ] || STOP sha-m1c
hd=$(git rev-parse HEAD) || STOP head
R=$EVID/code/c6p-owner-words.rev26.$MODE.txt
printf 'mode=%s\ncarry=%s sha256=%s\nm3=%s sha256=%s\nm1=%s sha256=%s\ncarry2=%s sha256=%s\nm4c=%s sha256=%s\nm3c=%s sha256=%s\nm1c=%s sha256=%s\nhead=%s\n' "$MODE" "$carry" "$sc" "$m3" "$s3" "$m1" "$s1" "$carry2" "$sc2" "$m4c" "$s4c" "$m3c" "$s3c" "$m1c" "$s1c" "$hd" > "$R" || STOP receipt
[ "$(grep -c . "$R")" -eq 9 ] || STOP receipt-lines
if [ "$MODE" = post ]; then
  P0=$EVID/code/c6p-owner-words.rev26.pre.txt; [ -s "$P0" ] || STOP pre-absent
  a=$(sed -n '2,8p' "$P0") || STOP pre-read; b=$(sed -n '2,8p' "$R") || STOP post-read; [ -n "$a" ] && [ "$a" = "$b" ] || STOP words-moved
fi
printf 'c6p-gate OK mode=%s\n' "$MODE"
```

- [ ] **Step 1: the failing tests** —
  (a) `tests/test_scan.cpp` `[scan][c6p]`: `stat_node` on a regular file, a symlink (target recorded), a FIFO (`std::nullopt`) and a vanished path (the unreadable class) — each node field-equal to what `scan()` records for the same path.
  (b) `tests/test_pack.cpp` `TEST_CASE("c6p pack writes each repository row's penumbra as payload members", "[pack-repos][c6p]")`, the member set read with the file's existing archive-listing helper: NON-ROOT — a workspace holding `README.md` and a clean repo `lib` (tracked `sub/t.txt` and `.gitignore` = `ign/` + `*.log`; ignored `ign/penumbra.txt`, `ign/deep/d.txt`, `sub/x.log`) → the `payload/` members are EXACTLY { `payload/README.md`, `payload/lib/ign`, `payload/lib/ign/deep`, `payload/lib/ign/deep/d.txt`, `payload/lib/ign/penumbra.txt`, `payload/lib/sub/x.log` } — `payload/lib`, `payload/lib/sub` (a tracked ancestor), `payload/lib/sub/t.txt`, `payload/lib/.gitignore` and every `.git` path ABSENT; each member's mode and mtime equal the source's `lstat`; every directory member precedes its descendants. PRUNE — the same with `.bivignore` = `lib/ign/deep/` → no `payload/lib/ign/deep…` member and the prune-summary advisory names `lib/ign/deep` with its `.bivignore` source. ROOT ROW (T-RED1 `defer`; rev24: V1-12's fixture VERBATIM) — the workspace itself a clean repo with tracked `src/a.c`, `.gitignore` = `*.o`, an ignored `src/a.o`, and `local.txt` ignored ONLY by `.git/info/exclude` → the `payload/` members are EXACTLY { `payload/local.txt`, `payload/src/a.o` } — NOT `payload/src` (a tracked ancestor). DIRS (rev24, m-1 200936's fixture VERBATIM, as the workspace-root repo) — tracked `.gitignore` (= `*.o`, `out/`, `build/`), `src/a.c`, `D/x/t.c`, `gk/.gitkeep`; ignored `src/a.o`, `D/y/i.o`, `out/k/z.o`, `gk/g.o`, the symlink `link.o`; exclude-only (`.git/info/exclude` = `local.txt`, `ex/`) `local.txt`, `ex/sub/e.txt`; an EMPTY ignored `build/`; `status --porcelain=v2` empty → the DIRECTORY members are EXACTLY { `payload/D/y`, `payload/ex`, `payload/ex/sub`, `payload/out`, `payload/out/k` } and the file members EXACTLY { `payload/D/y/i.o`, `payload/ex/sub/e.txt`, `payload/gk/g.o`, `payload/link.o` (a symlink member), `payload/local.txt`, `payload/out/k/z.o`, `payload/src/a.o` } — NOT `payload/D`, `payload/src`, `payload/gk`, `payload/build` (m-1's ground truth: the directories a `git clone file://` does not create that hold penumbra). PAYLOAD-ONLY + PENUMBRA (rev26, T-C6P (c)) — Task 6q Step 1 (b)'s fixture at the c6p head → `payload/shal/x.log` (the shallow row's IGNORED file, which classify also records in that row's `penumbra_paths`) appears EXACTLY ONCE in the member listing counted with multiplicity, and the member set is Task 6q's plus `lib`'s penumbra members (none — `lib` has no ignored file) — the payload-only row's tree is never penumbra-derived.
  (c) `tests/test_open.cpp` `[open][c6p]`, CALLING the `detail` functions (rev26 — never a search of the source text): `owning_row` — `lib/x` with {`lib`} → `lib`; `libx/y` with {`lib`} → none (whole segments, V1-1); `a/b/c` with {`a`, `a/b`} → `a/b` (deepest); `x` with {`""`} → `""`; `docs/inner` with {`docs/inner`} → none (a member whose path IS a row's relpath is not owned by it — V1-4's second clause keeps that row's `restore_entry` refusal). `row_relpaths` — a full row `lib`, a shallow row `shal` and a zero-ref unborn row `fresh` → exactly {`lib`}; a full ROOT row → {`""`}. `is_dotgit_component` TRUE for `.git`, `.GIT`, `.gIt`, `.g` U+200C `it`, U+FEFF `.git`, `.git` U+200F, `git~1`, `GIT~1`, `.git.`, `.git ` (trailing space), `.git. .`, `.git:x`, `git~1:y`; FALSE for `.gitx`, `git`, `.gi`, `x.git`, `.git~1`, `git~2`, `.gitignore`, `.g` U+00E9 `t` (a code point above 127 that is not ignorable), and the malformed byte string `.g\xffit`. `is_dotbiv_component` the same table with `biv` / `biv~1` / `.bivignore`. The source-order case: the `calls` array's `apply_archive(…)` and `restore_repos(…)` strings updated to the new signatures, and inside `restore_repos`'s body `apply_owned_members(` follows `restore_entry(` (V1-2's source-order oracle; H4 is its behavioural witness).
  (d) `tests/test_cli.cpp` `[cli][c6p]`, receipts via `BIV_LEG_RECEIPTS`: P1 NON-ROOT (b)'s workspace → `biv pack` → `biv open` (a bundle row, no network) rc 0 → `<dest>/lib/ign/penumbra.txt`, `lib/ign/deep/d.txt`, `lib/sub/x.log` byte-, mode- and mtime-equal (seconds and nanoseconds) to the source; `<dest>/lib/ign` and `lib/ign/deep` mtime-equal to the source (their members, stamped by c6m's pass AFTER the placement — V2-1/V2-2); `git -C <dest>/lib status --porcelain=v2` EMPTY; `result.restored_member_count` == the image's `payload/` member count (each once, V1-5). P2 the `--offline` twin → the same penumbra fidelity under `<dest>/lib/`, ZERO git lines in the request-trace shim log (V1-2, no git); `<dest>/lib` and `<dest>/lib/sub` exist as directories (created by the placement — arm A, T-C6P (b): the row relpath AND the absent component below it, `sub` being a tracked ancestor the archive never carries — never stamped, their mtimes not asserted, V2-3). P3 a repo under a payload directory (`docs` + clean `docs/inner` with ignored `ign/p.txt`) → `<dest>/docs/inner/ign/p.txt` present with fidelity and `<dest>/docs` mtime-equal to the source (c6m, jointly). P4 ROOT ROW = V1-12's JOINT ROOT WITNESS (rev24) — (b)'s ROOT fixture → `biv pack` → `biv open <image> --dest <dest> --network` rc 0 (the root's `verify_restored` ran BEFORE the placement, V1-9) → `<dest>/src/a.o` and `<dest>/local.txt` present, byte-, mode- and mtime-equal to the source; then `git -C <dest> status --porcelain=v2 -z` lists EXACTLY one entry, `? local.txt` (untracked: `.git/info/exclude` does not travel, pack-engine §1.3), and `git -C <dest> status --porcelain=v2 --ignored -z` lists `! src/a.o` (ignored by the tracked `.gitignore`) — both ASSERTED. HAND-BUILT images (labelled `provenance=hand-built, interim` — pack cannot produce these at 2b; the file's existing hand-built image helpers): H1 CONTAINMENT (V1-3; m-4) — one full row `lib` whose bundle tracks a symlink `lib/evil` → `../../outside-<nonce>` plus a member `payload/lib/evil/x` → open fails `MemberPathUnsafe`, nothing exists under `outside-<nonce>`, the partial retained (`facts.partial_path`, c6b's composition). H2 NO OVERWRITE (V1-4) — a member `payload/lib/sub/t.txt` at a TRACKED path → `MemberPathUnsafe`, the tracked bytes in the retained partial equal the bundle's blob. H3 a payload FILE member `payload/docs/inner` where `docs/inner` is a row → the first pass writes it (not owned) and that row's `restore_entry` refuses `materialization target already exists` (fatal, as today). H4 ORDER (V1-2; the nested fence refuses such a pack — T-ARM (ii)) — rows `a` and `a/c` (`parent_id` = `a`) and a FILE member `payload/a/c` (owned by `a`, the deepest PROPER prefix) → `a`'s placement lays it BEFORE `a/c`'s `restore_entry`, which then refuses `materialization target already exists` naming `a/c`; placement after all restores would instead fail `MemberPathUnsafe` on `payload/a/c` — the two outcomes discriminate the order. H5 GIT-OWNED STATE (V1-10; rev25, MUST-2B-44) — each image opened `--network` (the stage partition: the repo artifact is staged OUTSIDE the partial), two arms with SEPARATE predicates and NO baseline file created by the fixture: ROOT ARM — a root-row image with the member `payload/.git/c6p-sentinel` (`.git` itself always exists after the root restore — `git init` makes it, independent of any template directory; git never creates a file of that name) → the open fails `MemberPathUnsafe` from the deferred writer and `<partial>/.git/c6p-sentinel` is ABSENT afterwards (absent before placement by construction); LIB ARM — a `lib`-row image with `payload/lib/.git/config` → `MemberPathUnsafe`, and `<partial>/lib/.git/config` byte-equal to the config a reference `git clone` of the same bundle writes. H6 `.biv/` (V1-11; rev25, MUST-2B-45) — opened `--network` (the stage partition: c4b's offline artifact writer does not run, so nothing of the A10.6 artifact is in the partial), a root-row image carrying the DIRECTORY member `payload/.biv` and the FILE member `payload/.biv/c6p-sentinel` (unique names, not the A10.6 `repos/<id>/repo.bundle` shape) → the open fails `MemberPathUnsafe` at the `payload/.biv` member, and `<partial>/.biv` is ABSENT afterwards (a `<partial>/.biv` present after a landed `--network` open is a STOP to me: the fixture's premise). (rev26, T-C6P — m-4's AA-4 witnesses and the first-pass requirement word; every image HAND-BUILT and labelled as above) W2 (m-4's w2; F-C6P-1's witness, which REDS on the retained impl-6 candidate) — a `lib`-row image opened `--network` (MATERIALIZED) whose only member under `lib` is `payload/lib/.GIT/hooks/post-checkout` → the open fails `MemberPathUnsafe` from the DEFERRED writer, and afterwards `<partial>/lib/.git/hooks/post-checkout` is ABSENT (on macOS's case-insensitive default volume `.GIT` names the restored `.git`); on Linux `<partial>/lib/.GIT` is ABSENT as well; PREMISE, asserted first: a reference `git clone` of the same bundle under the test's isolated HOME writes no `hooks/post-checkout` (else the fixture is void — a STOP to me). W3 (w3) — the same member in an image opened `--offline` (the `lib` row is the offline-pointer row; nothing materialized) → `MemberPathUnsafe`, and `<partial>/lib/.GIT` and `<partial>/lib/.git` ABSENT afterwards (arm A's creation would otherwise make them). W4 (w4) is H1, unchanged. W5 (w5) — opened `--offline`, a `lib`-row image whose members are the SYMLINK `payload/lib/ln` → `../../outside-<nonce>` and then the file `payload/lib/ln/x`, with an EMPTY directory `outside-<nonce>` created beside the destination by the fixture → the open fails `MemberPathUnsafe` at `payload/lib/ln/x`; `outside-<nonce>` still empty afterwards; `<partial>/lib/ln` is the symlink the deferred writer laid (V1-5). FP1 (m-4's requirement word, the FIRST-PASS call site) — an image with NO repository row whose members are the DIRECTORY `payload/.git` and then the FILE `payload/.git/config` → the open fails `MemberPathUnsafe` at `payload/.git` from the first pass; `<partial>/.git` ABSENT afterwards (the directory member supplies the ancestor, so the predicate is the ONLY guard that can refuse — without it the first pass creates `.git` and writes `config`). FP2 — likewise with `payload/docs`, `payload/docs/.Git`, `payload/docs/.Git/config` → refused at `payload/docs/.Git`; `<partial>/docs/.Git` ABSENT (the fold at the first pass). H6b — H6 with `payload/.BIV` and `payload/.BIV/c6p-sentinel` → refused at `payload/.BIV`; `<partial>/.BIV` and `<partial>/.biv` ABSENT (the fold at V1-11). W2 and W3 run in BOTH platform legs (Task 9's macOS and Linux runs execute `biv_tests` whole) and assert refusal on each host — the predicate is uniform.
- [ ] **Step 2: run at the c6q head = THE NAMED MUTANT (c5's pack as c6q left it: no penumbra member)** — `./build/ci-macos/biv_tests '[c6p]'`: (a)–(c) fail to compile or RED (no `stat_node`; no `detail::owning_row`, `row_relpaths`, `is_dotgit_component`, `is_dotbiv_component`); P1–P4 RED (the penumbra absent after open); H4 RED (`MemberPathUnsafe` in the first pass instead of the child's refusal); H1–H3 are guards that hold on both sides (the first pass already refuses H1/H2 — their discriminating mutants are Step 4's M3/M4); the DIRS case REDs (no member); H5 / H6 are recorded as observed at the c6m head (the first pass is m-4's surface, m-3 200917 — not asserted there) and their discriminating mutants are Step 4's M6 / M7; (rev26) W2, W3 and W5 are recorded as observed at the c6q head (the first pass refuses them for want of an apply-created ancestor — not the deferred writer; their discriminating mutants are Step 4's M6, M6′ and M3); FP1 and FP2 RED (the first pass has no dot-git refusal: `<partial>/.git/config` and `<partial>/docs/.Git/config` are CREATED — the finding m-3 raised at 200917); H6b as H6; the PAYLOAD-ONLY + PENUMBRA case green at the c6q head (no penumbra member yet — its discriminator is Step 4's M11). Recorded to `$EVID/code/c6p-mutants.txt`.
- [ ] **Step 3: the implementation** —
  `scan.cpp`: `stat_node` factored out of `walk` (the walk's node block calls it; the `.biv`/`.git`/matcher lines above it byte-unchanged).
  `pack.cpp`: after the capture loop and BEFORE the report block (so the prune-summary and warnings see the new diagnostics): `auto penumbra = penumbra_nodes(source, entries, matcher->matcher, *scan_result); if (!penumbra) return cleanup_error(penumbra.error()); scan_result->payload.insert(scan_result->payload.end(), penumbra->begin(), penumbra->end());` — from there the members travel the ONE payload writer (`emitted_members`, `write_payload_member`, `checksums`). `penumbra_nodes`, per entry in discovery order with `R = ScanExclusions::canonical(entry.relpath)`: skip an entry without `engine_source`, and (rev26, T-C6P (c)) skip every PAYLOAD-ONLY entry (`!repo::restore_invokes_git(entry)`: its tree is c6q's, and classify records `penumbra_paths` for a shallow row too, so without this skip each of its ignored files would be archived TWICE); for each path `p` of `engine_source->penumbra_paths` (sorted) with `full = R.empty() ? p : R + "/" + p`: SKIP (recording) when the matcher ignores `full` or any directory prefix of it (the topmost pruned prefix once into `diagnostics.pruned`); SKIP when `full` lies in a DEEPER entry's subtree; SKIP when any directory segment is `.biv`; else `stat_node(source, full)` (nullopt → `skipped_unsupported`; error → `unreadable`). Directory members: each proper ancestor `a` of an emitted `full` STRICTLY inside `R` (never `R`) is emitted iff every non-directory entry under `source/a` (an `lstat` walk that never follows a symlink) has its `R`-relative path in the entry's `penumbra_paths` (memoized per `a`), and the matcher does not ignore `a`. The result sorted segment-wise so parents precede children.
  `open.cpp`: `execute_archive` computes `const auto row_rels = row_relpaths(plan.manifest.repos);` before `apply_archive(image, plan, partial_dir, dirs, verify, stage, row_rels)`; `apply_archive`'s payload branch: (rev26, T-C6P (d)) a member this pass WRITES — `owning_row(rel, row_rels)` empty — with any path segment for which `detail::is_dotgit_component` is true ⇒ `MemberPathUnsafe` BEFORE any byte of it is written (the first-pass call site of the ONE predicate; an owned member is judged by the deferred writer, its own call site, so each writer refuses before writing what it writes); when `owning_row(rel, row_rels)` has a value → `drain_member_midapply` + the same checksum check, NOT written, NOT counted, NOT in `created`/`dirs` (the `index` still advances; every other member byte-for-byte as today, V1-1); `apply_member`'s kind switch becomes `write_member` (called by both passes). `restore_repos(image, plan, partial_dir, stage, dirs, verify, report)`: after EACH entry's outcome — the restored row, the offline-pointer row (before its `continue`), the no-git rows `restore_entry` returns, the url-divergence refusal row — `apply_owned_members(image, plan, partial_dir, rel, row_rels, dirs, verify)` and `report.restored_member_count += *placed`; an error travels the SAME path c6b gives a `restore_repos` error (`with_partial_dir`, c6b's failed-mid-apply composition). `apply_owned_members`: ONE tar pass; for each `payload/` member with `owning_row(rel) == row_rel`, in this order and with nothing created or written before step (iii) — (i) THE SEGMENT REFUSALS (AA-2: before the walk): any path segment for which `detail::is_dotgit_component` is true (V1-10 under AA-3), or a FIRST segment for which `detail::is_dotbiv_component` is true (V1-11 under AA-3) ⇒ `MemberPathUnsafe`; (ii) THE EXISTING-ANCESTOR PASS (V1-3; AA-2): walk the member's ancestor components from the partial root downward, `symlink_status` each — a symlink or an existing non-directory ⇒ `MemberPathUnsafe` — and stop at the first ABSENT component (absence is monotone in depth in a quiescent partial, m-4); (iii) THE CREATION (arm A, AA-1; T-C6P (b): every absent component between the partial root and the member's parent — the row relpath's own and those below it alike; rev22..rev25's absent-ancestor refusal is WITHDRAWN): for each absent component in order, ONE `std::filesystem::create_directory(component, ec)` whose result must be `true` with no `ec` — `false` or an error ⇒ `MemberPathUnsafe`, never a re-check-and-continue — and then `symlink_status` of that component must report a real directory before the next is created; never `create_directories`; a created directory joins nothing (never stamped, V2-3); (iv) THE FINAL PATH (V1-4, unchanged): `symlink_status` must report not-found, else `MemberPathUnsafe`; then `write_member` and the per-member checksum (`IntegrityFailureMidApply`, V1-5); directory members join `dirs`, so c6m's pass stamps them after the placement (V2-2).
- [ ] **Step 4: run to verify pass + the named mutants** — `./build/ci-macos/biv_tests '[c6p]'` rc 0; `./build/ci-macos/biv_tests '[c6m]'` rc 0; `./build/ci-macos/biv_tests '[c6q]'` rc 0; `ctest --preset ci-macos -E '^safety-hardening$'` rc 0; the RepoEntry census (Task 5 Step 5's command) rc 0; `git diff --unified=0 "$B" HEAD -- src/core/scan/scan.cpp | grep -c -E '^[+-].*"\.biv"'` == 0. THE MUTANTS, each on the worktree copy with `open.cpp` saved to `$EVID/code/open.cpp.c6p` first and restored after (`cmp` == 0, rebuild, `[c6p]` rc 0 again), each result to `$EVID/code/c6p-mutants.txt`: M1a `row_rels` passed EMPTY to `apply_archive` (every member back in the first pass) → P1 RED with `MemberPathUnsafe` (the repo root is never a member, so the first pass cannot create `lib`); M1b M1a plus the first pass creating a missing ancestor (`create_directories`) for such members → P1 RED with `materialization target already exists` (164214 V1-7's named text); M3 (rev26: defined for arm A) the existing-ancestor check made to FOLLOW links (`status` for `symlink_status`) in `apply_owned_members` → H1 RED and W5 RED (a file appears under `outside-<nonce>`); M4 the final-path ENOENT check removed → H2 RED (the tracked bytes replaced or a different kind); (rev24) M1r the ROOT row excluded from `row_rels` (the kept first-pass order for the root, V1-12's named mutant) → P4 RED — on R-a (`MemberPathUnsafe` for `payload/src/a.o`, `src` never a member) or R-b (`worktree verification` on `local.txt`); the observed one recorded; M5 (`pack.cpp`, saved to `$EVID/code/pack.cpp.c6p` and restored the same way) the DIRECT reading — a directory qualifies when its DIRECT non-directory children are all in `penumbra_paths` — → the DIRS case RED with `payload/D` present (m-1 200936's named mutant); M6 ONLY the deferred writer's dot-git call removed → H5's ROOT ARM RED (and W2, W3): `<partial>/.git/c6p-sentinel` is CREATED (its ancestor `.git` is a real directory and the final path is ENOENT, so no other guard fires — the lib arm may still refuse through V1-4's existence rule and is not M6's discriminator); M7 ONLY the deferred writer's `.biv` call removed → H6 RED (and H6b): `<partial>/.biv/` and `<partial>/.biv/c6p-sentinel` are CREATED (the directory member supplies the ancestor, so neither the creation walk nor the final-path rule fires). Each mutant's observed file presence is recorded. (rev26, T-C6P) M9 = m-4's w1: the below-row creation deleted (rev25's absent-ancestor refusal restored) → P2 RED with `MemberPathUnsafe` at `payload/lib/sub/x.log`, on the existing fixture; M6′ the shared predicate's fold replaced by an EXACT compare (`segment == ".git"` / `== ".biv"` — F-C6P-1's form, the retained candidate's) → W2 RED (macOS: `<partial>/lib/.git/hooks/post-checkout` CREATED through `.GIT`; Linux: under `<partial>/lib/.GIT/hooks/`), FP2 RED and H6b RED, while H5 and FP1 stay GREEN (their names are exact) — the predicate's own discriminator; M8 ONLY the first pass's dot-git call removed → FP1 and FP2 RED (`<partial>/.git/config`, `<partial>/docs/.Git/config` CREATED) while every deferred-writer case stays green; M10 `row_relpaths` admitting payload-only rows → the (c) `row_relpaths` case RED; M11 (`pack.cpp`) the payload-only skip removed from `penumbra_nodes` → the PAYLOAD-ONLY + PENUMBRA case RED (`payload/shal/x.log` listed twice, or the pack or the open failing on the duplicate — the observed one recorded). NOT WITNESSED, stated as byte-review conditions for m-4 and NOT claimed as tested (their discriminator is a concurrent writer inside the partial, which no single-threaded fixture supplies): AA-1's `a create_directory reporting not-created is a refusal, never a re-check-and-continue` and `never create_directories`. The MUST-2B-12 fast-path mutant stays Task 7's.
- [ ] **Step 5: commit (Step 0's gate re-run with `MODE=post` IMMEDIATELY before this block; the block refuses without its receipt)** —

```bash
[ -s "$EVID/code/c6p-owner-words.rev26.post.txt" ] && [ "$EVID/code/c6p-owner-words.rev26.post.txt" -nt "$EVID/code/c6p-owner-words.rev26.pre.txt" ] && [ "$(sed -n 1p "$EVID/code/c6p-owner-words.rev26.post.txt")" = mode=post ] || { echo 'STOP: run the Task 6d Step 0 gate with MODE=post immediately before this commit'; exit 1; }
git add src/core/pack/pack.cpp src/core/scan/scan.hpp src/core/scan/scan.cpp src/core/open/open.hpp src/core/open/open.cpp tests/test_scan.cpp tests/test_pack.cpp tests/test_open.cpp tests/test_cli.cpp
git commit -m "pack+open: each repository row's penumbra written as payload members (pack-engine 1.1/1.3/3.2: payload always, never silent) and laid after the row's restore_entry with every ancestor lstat'd (restore-apply 2.2 step 5, 2.5); R-4.65 RED-1 in c5 5aeb81c; m-1 141529 (pack half), m-3 164214 RED1_OPEN_PLACEMENT confirm (V1-1..7); T-RED1 m3=$(sed -n 's/^m3_relay=//p' "$RUNNERS/red1-owner-words.txt") m1=$(sed -n 's/^m1_relay=//p' "$RUNNERS/red1-owner-words.txt"); T-C6P (R-4.69) carry=$(sed -n 's/^c6p_carry_relay=//p' "$RUNNERS/red1-owner-words.txt"): m-4 arm A (AA-1..4), one dot-git predicate at both writers, m-3 C6P_V1_READING confirm, m-1 C6P_MEMBER_SET stop"
git rev-parse HEAD > "$EVID/commits.c6p.txt"
```

### Task 6e — c1d, R-4.72 pack half: classify records each remote's CONFIGURED url — the FIRST line of `git config --get-all remote.<name>.url` at both sites — engine-only (m-1 `140916` §2, pre-authorized engine input c1d: `R472_PLACEMENT: in-lane`, `R472_MANIFEST_URL: configured`; HOLDS on the R-4.72 gate; rev28)

**Files:** Modify `src/core/repo/classify.cpp` (the two remote-URL reads ONLY — the unborn-with-refs branch's loop and the born branch's loop, `:258` and `:319` at `534decb`), Modify `tests/test_repo_engine.cpp` (W-U1..W-U6). ZERO bytes in `src/cli`, `src/core/open`, `src/core/pack`, `src/core/scan`, `src/core/manifest` and every other `src/core/repo` file; no commit spans engine and call site.
**Interfaces:** none new. `classify`'s signature, `RepoEntry`, `Remote`, the remote enumeration (`git remote`), its order and its names are unchanged. Consumes the landed `invoke_classify` lambda (`classify.cpp:107-115` at `534decb`).
**Sealed content (m-1 `140916` §2, the fence, verbatim):**

```text
ENGINE     ONE commit, src/core/repo/classify.cpp + tests/test_repo_engine.cpp only; zero bytes in src/cli,
           src/core/open, src/core/pack, src/core/scan, src/core/manifest; no commit spans engine and call site.
           Both remote-URL sites read `config --get-all remote.<name>.url` and take the FIRST line (trimmed as today);
           an empty result or a non-zero exit is the existing typed "remote get-url" command error (rename the detail
           only if m-3's text requires it; no new kind). Remote enumeration (`git remote`), order and names unchanged.
           Nothing else in classify moves; git_exec's comparator, M-R2's set, and the gate are untouched.
VETO 9     sealed M-R8 veto 9 (consent gate landed before wiring) is satisfied and unaffected. My 042531 mechanical form
(owner)    is re-ruled for this commit: engine-only, zero call-site bytes, no spanning commit. It may follow c4–c6.
WITNESSES  engine seat (test_repo_engine.cpp):
           W-U1 repo-local insteadOf → entry.remotes[0].url == the configured URL; the gate's requested/effective differ;
                with no hook → typed refusal (leg (g)); with the accept arm → proceeds, manifest still configured.
           W-U2 the same rule in GLOBAL scope → identical outcome (scope-independent).
           W-U3 control, no rewrite → configured == effective, no divergence, no prompt.
           W-U4 multi-valued remote.<name>.url → the FIRST value recorded. NAMED MUTANT: `config --get` (records the
                last) → RED here. Second NAMED MUTANT: today's `remote get-url` → RED at W-U1.
           W-U5 the unborn-with-refs branch (:258) under W-U1's rule → configured recorded (both sites covered).
           product scope: Task 7's FX-M-1 legs, (h) included, re-execute over a `biv pack`-produced image as planned.
```

**The cause, re-measured at this seat** (git 2.50.1, isolated HOME, `file://` only): `git remote get-url origin` applies `insteadOf` and returns the REWRITTEN address, so at B the comparator's requested value is already the effective one and no rewrite at any scope is ever a divergence at pack; `biv pack` exits 0 and the image records the rewritten origin (SITREP `134901`). `git config --get remote.origin.url` returns the LAST value of a multi-valued key; `--get-all` lists every value, the FIRST being git's own fetch URL, before rewrite. TWO FURTHER FACTS measured here that m-1's probe did not cover: (1) a config remote with no `url` (only `remote.<n>.fetch` or `remote.<n>.pushurl`) IS listed by `git remote`; at B `remote get-url` returns the remote's NAME with rc 0 and the manifest records that name as its url; under the fence `config --get-all` exits 1 and the typed command error refuses the whole pack. The fence states that arm, so c1d executes it and W-U6 pins it; the behaviour change goes to m-1 on the digest word as a measured observation, not a stop. Legacy `.git/remotes/<n>` and `.git/branches/<n>` remotes are NOT listed by `git remote` at 2.50.1, so neither read reaches them. (2) The landed `F-URL-1 real git a eligibility refuses a repo-local rewrite` case (`test_repo_engine.cpp:425` at `534decb`) configures its rewrite AFTER `classify` has run, so classify never saw it — the order that hid R-4.72 from the suite. Every W-U case configures its rule BEFORE `classify`, as a user's repository has it; the landed case stays byte-for-byte.

- [ ] **Step 0: the R-4.72 gate — the EXECUTABLE block below, run from the worktree with `LABEL=c1d`: `MODE=pre` before the first c1d test byte, `MODE=post` immediately before the c1d commit (Step 5 refuses without the post receipt). Task 6f runs the SAME block with `LABEL=c1e` and Task 7 with `LABEL=c7`, each pre and post.** It binds NINE carriers by bytes: master's three carries TO this seat — `PLAN-master-planner-20260923-142025.md` citing m-1 `140916`, m-4 `140901` and m-3 `141015`; `PLAN-master-planner-20260923-145548.md` citing m-4 `144917`; `PLAN-master-planner-20260923-151255.md` citing m-1 `150702` and m-3 `150622` — and those six owner relays, each resolved under `$PDC/master/relays/`, tracked and unmodified, the nine pairwise distinct, each owner relay's `FROM:` line, each word a whole line exactly once with no second line of its field: `R472_PLACEMENT: in-lane` and `R472_MANIFEST_URL: configured` (m-1 `140916`), `R472_ISOLATION: stands` (m-4 `140901`), `R472_OPEN_WITNESS: other` (m-3 `141015`, whose cell `150622` re-words; both are bound), `R472_ENCLOSING_REPO: ceiling` (m-4 `144917`), `R472_CEILING_PLACEMENT: own-commit-in-lane` (m-1 `150702`), `R472_OPEN_WITNESS_REWORD: shim-fallback` (m-3 `150622`); each carry citing its owner relays by path. Every receipt's nine relay lines must equal those of `r472-owner-words.c1d.pre.txt` (the words cannot move between c1d, c1e and c7, and c1e / c7 cannot pass the gate before c1d's pre receipt exists), and a post receipt's must equal its own pre's. The gate file `$RUNNERS/r472-owner-words.txt` holds nine `key=path` lines (`carry_relay`, `carry2_relay`, `carry3_relay`, `m1_relay`, `m4_relay`, `m3_relay`, `m4_enclosing_relay`, `m1_ceiling_relay`, `m3_reword_relay`), written by the pair Planner beside `t-oracle.txt` BEFORE the token and carried by Step 0′. WALKED at the pair Planner's seat before this revision was filed, on this block's own bytes: six synthetic YES runs (each `LABEL` × `MODE`) and 43 NO runs, each isolating one predicate (the field count, a duplicate field, each of the seven words, a rival line for each, each owner `FROM:`, each carry's `FROM:` / `TO:`, each citation, a reused relay, an untracked / modified / outside / `..` / symlinked path, a post without its pre, words moved inside a commit's window for `c1d` and for `c1e`, `c1e` before `c1d`'s pre, words moved since `c1d`, a bad `LABEL`, a bad `MODE`, the file absent) — 54 PASS, 0 FAIL; then the must-be-YES on the REAL relays at pdc HEAD into a scratch `$EVID` (all six `LABEL` × `MODE` runs rc 0) and a real NO (the superseded `141015` placed in the reword slot ⇒ `same-relay-8`). The walk caught one defect of this block before filing: the post-versus-own-pre comparison sat AFTER the c1d-anchor comparison, which made it dead (a pre always equals the anchor, so the anchor fired first); it now runs first, and both are reachable.

```bash
# Task 6e Step 0 — the R-4.72 gate: seven owner words and three carries bound by bytes, LABEL=c1d|c1e|c7, MODE=pre|post (rev28)
set -o pipefail
STOP() { printf 'STOP-r472-gate %s line=%s\n' "$1" "${BASH_LINENO[0]}" >&2; exit 1; }
[ -n "$RUNNERS" ] && [ -n "$EVID" ] && [ -d "$EVID/code" ] || STOP env
case "${MODE:-}" in pre|post) ;; *) STOP mode;; esac
case "${LABEL:-}" in c1d|c1e|c7) ;; *) STOP label;; esac
F=$RUNNERS/r472-owner-words.txt; [ -s "$F" ] || STOP file-absent
g=0; n=$(grep -c . "$F") || g=$?; [ "$g" -eq 0 ] && [ "$n" -eq 9 ] || STOP "field-count-$n"
field() { g=0; n=$(grep -c -E "^$1=" "$F") || g=$?; [ "$g" -le 1 ] && [ "$n" -eq 1 ] || STOP "field-$1-count-$n"
  v=$(sed -n -E "s/^$1=([^[:space:]]+)$/\1/p" "$F") || STOP "field-$1-read"; [ -n "$v" ] || STOP "field-$1-empty"; printf '%s' "$v"; }
c1=$(field carry_relay) || exit 1; c2=$(field carry2_relay) || exit 1; c3=$(field carry3_relay) || exit 1
m1=$(field m1_relay) || exit 1; m4=$(field m4_relay) || exit 1; m3=$(field m3_relay) || exit 1
m4e=$(field m4_enclosing_relay) || exit 1; m1c=$(field m1_ceiling_relay) || exit 1; m3r=$(field m3_reword_relay) || exit 1
PDC=$(cd ../pdc && pwd -P) || STOP pdc; [ -d "$PDC/master/relays" ] || STOP pdc-tree
resolve() { case "$1" in /*|*..*) STOP "path-$2";; esac; [ ! -L "$PDC/$1" ] && [ -f "$PDC/$1" ] || STOP "notfile-$2"
  d=$(cd "$PDC/$(dirname "$1")" && pwd -P) || STOP "dir-$2"; case "$d/" in "$PDC/master/relays/"*) ;; *) STOP "outside-$2";; esac
  git -C "$PDC" ls-files --error-unmatch -- "$1" >/dev/null 2>&1 || STOP "untracked-$2"; git -C "$PDC" diff --quiet HEAD -- "$1" || STOP "modified-$2"; printf '%s' "$PDC/$1"; }
C1=$(resolve "$c1" carry) || exit 1; C2=$(resolve "$c2" carry2) || exit 1; C3=$(resolve "$c3" carry3) || exit 1
F1=$(resolve "$m1" m1) || exit 1; F4=$(resolve "$m4" m4) || exit 1; F3=$(resolve "$m3" m3) || exit 1
G4=$(resolve "$m4e" m4e) || exit 1; G1=$(resolve "$m1c" m1c) || exit 1; G3=$(resolve "$m3r" m3r) || exit 1
u=0; k=$(printf '%s\n' "$C1" "$C2" "$C3" "$F1" "$F4" "$F3" "$G4" "$G1" "$G3" | LC_ALL=C sort -u | grep -c .) || u=$?; [ "$u" -eq 0 ] && [ "$k" -eq 9 ] || STOP "same-relay-$k"
line1() { g=0; k=$(grep -c -x -F -- "$2" "$1") || g=$?; [ "$g" -le 1 ] && [ "$k" -eq 1 ] || STOP "$3"; }
count1() { g=0; k=$(grep -c -E -- "$2" "$1") || g=$?; [ "$g" -le 1 ] && [ "$k" -eq 1 ] || STOP "$3"; }
line1 "$F1" 'FROM: m-1.planner' m1-from; line1 "$F1" 'R472_PLACEMENT: in-lane' m1-placement; count1 "$F1" '^R472_PLACEMENT:' m1-placement-cardinality
line1 "$F1" 'R472_MANIFEST_URL: configured' m1-manifest-url; count1 "$F1" '^R472_MANIFEST_URL:' m1-manifest-url-cardinality
line1 "$F4" 'FROM: m-4.planner' m4-from; line1 "$F4" 'R472_ISOLATION: stands' m4-isolation; count1 "$F4" '^R472_ISOLATION:' m4-isolation-cardinality
line1 "$F3" 'FROM: m-3.planner' m3-from; line1 "$F3" 'R472_OPEN_WITNESS: other' m3-open-witness; count1 "$F3" '^R472_OPEN_WITNESS:' m3-open-witness-cardinality
line1 "$G4" 'FROM: m-4.planner' m4e-from; line1 "$G4" 'R472_ENCLOSING_REPO: ceiling' m4e-word; count1 "$G4" '^R472_ENCLOSING_REPO:' m4e-word-cardinality
line1 "$G1" 'FROM: m-1.planner' m1c-from; line1 "$G1" 'R472_CEILING_PLACEMENT: own-commit-in-lane' m1c-word; count1 "$G1" '^R472_CEILING_PLACEMENT:' m1c-word-cardinality
line1 "$G3" 'FROM: m-3.planner' m3r-from; line1 "$G3" 'R472_OPEN_WITNESS_REWORD: shim-fallback' m3r-word; count1 "$G3" '^R472_OPEN_WITNESS_REWORD:' m3r-word-cardinality
line1 "$C1" 'FROM: master.master-planner' carry-from; line1 "$C1" 'TO: intg.pair-planner' carry-to
line1 "$C2" 'FROM: master.master-planner' carry2-from; line1 "$C2" 'TO: intg.pair-planner' carry2-to
line1 "$C3" 'FROM: master.master-planner' carry3-from; line1 "$C3" 'TO: intg.pair-planner' carry3-to
cite() { g=0; k=$(grep -c -F -- "$1" "$3") || g=$?; [ "$g" -le 1 ] && [ "$k" -ge 1 ] || STOP "$2"; }
cite "$m1" carry-cites-m1 "$C1"; cite "$m4" carry-cites-m4 "$C1"; cite "$m3" carry-cites-m3 "$C1"
cite "$m4e" carry2-cites-m4e "$C2"; cite "$m1c" carry3-cites-m1c "$C3"; cite "$m3r" carry3-cites-m3r "$C3"
sha() { h=0; s=$(shasum -a 256 "$1" | cut -d' ' -f1) || h=$?; [ "$h" -eq 0 ] && [ -n "$s" ] || STOP "sha-$2"; printf '%s' "$s"; }
s1=$(sha "$C1" carry) || exit 1; s2=$(sha "$C2" carry2) || exit 1; s3=$(sha "$C3" carry3) || exit 1
t1=$(sha "$F1" m1) || exit 1; t4=$(sha "$F4" m4) || exit 1; t3=$(sha "$F3" m3) || exit 1
u4=$(sha "$G4" m4e) || exit 1; u1=$(sha "$G1" m1c) || exit 1; u3=$(sha "$G3" m3r) || exit 1
hd=$(git rev-parse HEAD) || STOP head
R=$EVID/code/r472-owner-words.$LABEL.$MODE.txt
printf 'mode=%s label=%s\ncarry=%s sha256=%s\ncarry2=%s sha256=%s\ncarry3=%s sha256=%s\nm1=%s sha256=%s\nm4=%s sha256=%s\nm3=%s sha256=%s\nm4e=%s sha256=%s\nm1c=%s sha256=%s\nm3r=%s sha256=%s\nhead=%s\n' "$MODE" "$LABEL" "$c1" "$s1" "$c2" "$s2" "$c3" "$s3" "$m1" "$t1" "$m4" "$t4" "$m3" "$t3" "$m4e" "$u4" "$m1c" "$u1" "$m3r" "$u3" "$hd" > "$R" || STOP receipt
[ "$(grep -c . "$R")" -eq 11 ] || STOP receipt-lines
b=$(sed -n '2,10p' "$R") || STOP self-read; [ -n "$b" ] || STOP self-empty
if [ "$MODE" = post ]; then
  P0=$EVID/code/r472-owner-words.$LABEL.pre.txt; [ -s "$P0" ] || STOP pre-absent
  a=$(sed -n '2,10p' "$P0") || STOP pre-read; [ -n "$a" ] && [ "$a" = "$b" ] || STOP words-moved
fi
A0=$EVID/code/r472-owner-words.c1d.pre.txt; [ -s "$A0" ] || STOP anchor-absent
a=$(sed -n '2,10p' "$A0") || STOP anchor-read; [ -n "$a" ] && [ "$a" = "$b" ] || STOP words-moved-since-c1d
printf 'r472-gate OK label=%s mode=%s\n' "$LABEL" "$MODE"
```

- [ ] **Step 1 (c1d): the failing tests** — `tests/test_repo_engine.cpp`, tagged `[repo][c1d]`, with the file's own helpers (`resolved_git`, `init_repo`, `init_bare_remote`, `add_remote_and_push`, `git_run`, `configure_url_rewrite`, `ScopedEnv`, `one_repo`, `request_count_with_argv`). Every address is a local bare repository reached over `file://` (no network egress): `remote.git` holds the commit; `effective.git` is a SECOND bare repository cloned from it. Each rewrite is configured BEFORE `classify`.

```cpp
// W-U1 — R-4.72 (m-1 140916 §2): the requested value is the CONFIGURED url; the gate then sees the rewrite as a divergence.
TEST_CASE("W-U1: a repo-local insteadOf leaves the configured url recorded and the gate refuses it with no hook", "[repo][c1d]") {
  auto git = resolved_git();
  TempDir root{"c1d-w-u1"};
  const auto remote = init_bare_remote(git, root.path());            // file://…/remote.git, holds main
  const auto repo = root.path() / "repo";
  init_repo(git, repo);
  add_remote_and_push(git, repo, remote);
  const auto effective_repo = root.path() / "effective.git";
  git_run(git, root.path(), {"clone", "--bare"}, {remote.string(), effective_repo.string()});
  const auto requested = "file://" + remote.string();
  const auto effective = "file://" + effective_repo.string();
  git_run(git, repo, {"remote", "set-url"}, {"origin", requested});
  configure_url_rewrite(git, repo, requested, effective);            // BEFORE classify, as a user's repository has it
  auto classified = biv::repo::classify(git, repo, one_repo());
  REQUIRE(classified.has_value());
  REQUIRE(classified->entry.remotes.size() == 1U);
  CHECK(classified->entry.remotes[0].url == requested);              // NAMED MUTANT (m-1): `remote get-url` records `effective` ⇒ RED
  auto refused = biv::repo::run_eligibility(git, classified->entry, biv::repo::EligibilityMode::network);  // no hook installed
  REQUIRE_FALSE(refused.has_value());
  CHECK(biv::repo::engine_error_kind(refused.error()) == biv::repo::EngineErrorKind::url_divergence_refused);
  CHECK(refused.error().facts.at("requested") == requested);
  CHECK(refused.error().facts.at("effective") == effective);
  // the accept arm: proceeds; the recorded url stays CONFIGURED (m-1 R472_MANIFEST_URL; m-4 SR-URL-5 (b)'s property)
  biv::repo::UrlDivergenceRun run;
  run.hook = [](const biv::repo::UrlDivergence &) { return biv::repo::UrlDivergenceDecision::proceed; };
  biv::repo::ScopedUrlDivergenceRun scoped{run};
  auto again = biv::repo::classify(git, repo, one_repo());
  REQUIRE(again.has_value());
  auto proceeded = biv::repo::run_eligibility(git, again->entry, biv::repo::EligibilityMode::network);
  REQUIRE(proceeded.has_value());
  CHECK(run.accepted.size() == 1U);
  CHECK(again->entry.remotes[0].url == requested);
}
// W-U2 — the SAME rule in GLOBAL scope: HOME is set BEFORE `resolved_git()` (the handle captures HOME at resolve; the pack-side
// handle does not isolate global config — only restore does) → identical outcome to W-U1 (both arms).
TEST_CASE("W-U2: the same rewrite in global config gives W-U1's outcome", "[repo][c1d]") { /* W-U1's body with the rule in <home>/.gitconfig */ }
// W-U3 — control, no rewrite anywhere → remotes[0].url == requested; run_eligibility with NO hook succeeds; run.refused empty.
TEST_CASE("W-U3: with no rewrite the configured url is the effective one and nothing diverges", "[repo][c1d]") { /* … */ }
// W-U4 — multi-valued remote.origin.url (`git config --add remote.origin.url <second>` after the first) → the FIRST value
// recorded. NAMED MUTANT (m-1): `config --get` records the LAST value ⇒ RED here.
TEST_CASE("W-U4: a multi-valued remote url records the first value, as git fetches it", "[repo][c1d]") { /* … */ }
// W-U5 — the unborn-with-refs branch (the `:258` site): arranged as the landed any-ref unborn case (`:903-925`) plus `origin`
// and W-U1's local rule → remotes[0].url == requested. NAMED MUTANT: that site left on `remote get-url` while `:319` is
// fixed ⇒ RED here ONLY (both sites covered).
TEST_CASE("W-U5: the unborn-with-refs branch records the configured url too", "[repo][c1d]") { /* … */ }
// W-U6 — (pair Planner, pins the fence's stated error arm) a remote with no url: `git config remote.nourl.fetch
// +refs/heads/*:refs/remotes/nourl/*` → classify fails with EngineErrorKind::git_invocation_failed and the detail
// "repo classification git invocation failed: remote get-url" (command_error at classify.cpp:13-18). At B the same repo
// classifies rc 0 with remotes[1].url == "nourl" (the remote's NAME) — the measured behaviour change, flagged to m-1.
TEST_CASE("W-U6: a remote with no url is the existing typed command error", "[repo][c1d]") { /* … */ }
```

- [ ] **Step 2 (c1d): run at the c6p head to verify failure** — `cmake --build --preset ci-macos && ./build/ci-macos/biv_repo_engine_tests '[c1d]'`: W-U1 RED (`remotes[0].url == effective`; `run_eligibility` succeeds — no divergence reaches the gate), W-U2 RED the same way, W-U4 GREEN (measured: with no rule `remote get-url` prints the FIRST value of a multi-valued url, as `--get-all`'s first line does, while `config --get` prints the LAST — so W-U4's only discriminator is Step 4's Mu1), W-U5 RED, W-U6 RED (rc 0 with the name recorded), W-U3 GREEN (the control). Recorded to `$EVID/code/c1d-mutants.txt` with each case's observed line.
- [ ] **Step 3 (c1d): the implementation** — `classify.cpp`, at BOTH sites, the one call and nothing else:

```cpp
          auto url = invoke_classify({"config", "--get-all", "remote." + name + ".url"},
                                     result.entry.promisor);
          if (!url || url->exit_code != 0) {
            return std::unexpected(url ? command_error(repo, "remote get-url")
                                       : url.error());
          }
          const auto values = git_bytes(url->stdout_bytes);
          const auto first = trim_git_newline(values.substr(0, values.find('\n')));
          if (first.empty()) {
            return std::unexpected(command_error(repo, "remote get-url"));
          }
          result.entry.remotes.push_back(Remote{.name = name, .url = first});
```

  The detail string stays `remote get-url` (m-3's text does not require a rename; no new kind). `values.find('\n')` on output without a newline returns `npos` and `substr(0, npos)` is the whole value. No other line of `src/core/repo/**` moves.
- [ ] **Step 4 (c1d): run to verify pass + the named mutants** — `./build/ci-macos/biv_repo_engine_tests '[c1d]'` rc 0; `./build/ci-macos/biv_repo_engine_tests` rc 0 (every landed case green, `F-URL-1 real git a …` byte-for-byte); `ctest --preset ci-macos -E '^safety-hardening$'` rc 0. THE MUTANTS, each on the worktree copy with `classify.cpp` saved to `$EVID/code/classify.cpp.c1d` first and restored after (`cmp` == 0, rebuild, `[c1d]` rc 0 again), each result appended to `$EVID/code/c1d-mutants.txt`: Mu1 (m-1) `config --get` in place of `--get-all` + first line at both sites → W-U4 RED; Mu2 (m-1) `remote get-url` restored at both sites → W-U1, W-U2, W-U5 RED; Mu3 the `:258` site alone restored to `remote get-url` → W-U5 RED and W-U1 GREEN (the second site is covered by its own case).
- [ ] **Step 5 (c1d): the veto-9 shape check, then commit (Step 0's gate re-run with `LABEL=c1d MODE=post` IMMEDIATELY before this block; the block refuses without its receipt)** — `git status --porcelain` names exactly `src/core/repo/classify.cpp`, `tests/test_repo_engine.cpp`; `git diff --stat -- src/cli src/core/pack src/core/scan src/core/open src/core/manifest src/core/repo/eligibility.hpp src/core/repo/eligibility.cpp src/core/repo/discover.cpp src/core/repo/restore.hpp src/core/repo/restore.cpp src/core/repo/git.hpp src/core/repo/git.cpp src/core/repo/git_exec.hpp src/core/repo/git_exec.cpp src/core/repo/capture.cpp` EMPTY.

```bash
[ -s "$EVID/code/r472-owner-words.c1d.post.txt" ] && [ "$EVID/code/r472-owner-words.c1d.post.txt" -nt "$EVID/code/r472-owner-words.c1d.pre.txt" ] && [ "$(sed -n 1p "$EVID/code/r472-owner-words.c1d.post.txt")" = 'mode=post label=c1d' ] || { echo 'STOP: run the Task 6e Step 0 gate with LABEL=c1d MODE=post immediately before this commit'; exit 1; }
git add src/core/repo/classify.cpp tests/test_repo_engine.cpp
git commit -m "repo: classify records each remote's CONFIGURED url -- the first value of git config --get-all remote.<name>.url at both sites (unborn-with-refs, born), never the insteadOf-expanded remote get-url, so the gate's same-context ls-remote --get-url sees a rewrite as a divergence (ADDENDUM-M M-R1/M-R2, FX-M-1 (h)); an absent or failing read is the existing typed command error -- R-4.72 pack half; m-1 140916 section 2 pre-authorized engine input c1d (R472_PLACEMENT in-lane, R472_MANIFEST_URL configured); W-U1..W-U6"
git rev-parse HEAD > "$EVID/commits.c1d.txt"
```

### Task 6f — c1e, R-4.72 open half: every restore invocation bounded by `GIT_CEILING_DIRECTORIES` = `canonical(partial_root.parent_path())` — engine-only (m-4 `144917` EC-1: `R472_ENCLOSING_REPO: ceiling`; m-1 `150702` §2, pre-authorized engine input c1e: `R472_CEILING_PLACEMENT: own-commit-in-lane`; HOLDS on the R-4.72 gate; rev28)

**Files:** Modify `src/core/repo/git.hpp`, `src/core/repo/git.cpp`, `src/core/repo/git_exec.hpp`, `src/core/repo/git_exec.cpp`, `src/core/repo/restore.cpp`, `tests/test_repo_engine.cpp`. ZERO bytes outside `src/core/repo` but that test file; `restore.hpp` untouched (Task 1's `2 0` numstat bound stands); no spanning commit.
**Interfaces:** `git.hpp` `Git::Opts` gains `std::optional<std::filesystem::path> ceiling;` — when set, `build_spawn_request` emits EXACTLY one `GIT_CEILING_DIRECTORIES=<path>` entry (one absolute entry, no separator, no empty entry). The handle's base environment carries no inherited `GIT_*` (`Git::resolve`, `git.cpp:58-95` at `534decb`: PATH, HOME, TMPDIR and the pinned keys only), so the emitted entry IS the value, replacing any the user's environment held. `git_exec.hpp` `GitInvokeOptions` gains `std::optional<std::filesystem::path> ceiling{};` and `invoke_git` copies it into the `Git::Opts` it builds BEFORE the network branch, so the `ls-remote --get-url` resolution and the call it guards run under the SAME ceiling (M-R1's same-context rule by construction). `restore.cpp`: `restore_entry` computes `std::filesystem::canonical(partial_root.parent_path(), ec)` ONCE before its first spawn and every `restore_invoke` / `require_success` passes it; `restore_entry`'s signature is unchanged (it already receives `partial_root`). Pack, classify, eligibility and capture set NO ceiling (the source repository IS the subject). No `GIT_DIR`.
**Sealed content (m-1 `150702` §2, the fence, verbatim; m-4 `144917` EC-1..EC-4 and m-3 `150622` carried on master's `151255`):**

```text
ENGINE     ONE commit: src/core/repo/git.{hpp,cpp}, src/core/repo/git_exec.{hpp,cpp}, src/core/repo/restore.cpp,
           tests/test_repo_engine.cpp only; zero bytes outside src/core/repo except that test file; no spanning commit.
           + Git::Opts: optional ceiling path; build_spawn_request emits EXACTLY `GIT_CEILING_DIRECTORIES=<path>`, one
             absolute entry, no separator, no empty entry, replacing any value (the handle passes no inherited GIT_*).
           + GitInvokeOptions: the ceiling, applied to the network call AND its same-context --get-url resolution.
           ~ restore_entry: ceiling = canonical(partial_root.parent_path()) once, before the first spawn; failure → typed
             restore_error (step "clone"), zero spawns. Every restore_invoke / require_success passes it.
           ✗ pack / classify / eligibility / capture: NO ceiling (the source repo is the subject).
           No GIT_DIR. No change to M-R2's set, the comparator, restore_invokes_git, or any row shape.
WITNESSES  (EC-2's four, at the engine seam here and at product scope in Task 7)
           W-C1 destination inside an enclosing repo whose local config rewrites the recorded remote → restore clones the
                RECORDED url, no divergence, rc 0. NAMED MUTANT: ceiling omitted → divergence prompt/refusal returns.
           W-C2 the enclosing repo's .git tree checksum-equal before and after the open (no host write).
           W-C3 destination reached through a SYMLINK → W-C1 holds (the canonical clause falsified if broken).
           W-C4 control, no enclosing repo → outcomes byte-identical to today.
           NAMED MUTANTS from the probe: emitting ":<path>" (empty-entry prefix) with a symlinked path → W-C3 RED;
                emitting a relative path → W-C1 RED.
           W-C5 pack-side negative: a source repo nested in another repo still classifies from ITS config (no ceiling
                leaks into pack) — the named mutant being the ceiling set in Git::resolve.
           W-C6 an un-canonicalizable parent (injected at the engine seam) → typed failure, zero spawns in the trace.
EC-3/EC-4  M's open-grain gate stays wired as defence in depth (untouched by c1e). EC-4's dot-git refusal at both
           writers is the other half of the property; its bytes are not in c1e, and the H review reads both together.
ORDER      c1d then c1e, both before c7; one plan revision admits both.
```

**Measured at this seat before planning** (git 2.50.1, isolated HOME, `file://` only; the enclosing repository `encl` carries `url.<other>.insteadOf <recorded>`): with no ceiling, `ls-remote --get-url <recorded>` from `encl/p1.partial` (depth 1) and from `encl/sub/p2.partial` (depth 2) returns `other.git`; with `GIT_CEILING_DIRECTORIES` = the canonical parent it returns `rec.git` at both depths. Through a symlinked destination, the canonical, the symlinked-absolute and the trailing-colon spellings bound; `:` + the symlinked spelling and a relative entry do NOT — m-1's table reproduced. And: WITHOUT the ceiling a `git clone` of the recorded url from inside `encl` fetched the RECORDED repository at both depths (clone does not read the enclosing repository's config for its source), so what the enclosing config reaches is the GATE's resolution — the product defect is a false divergence (a prompt, or a refusal row at rc 2), and every W-C1-class assertion reds on the refusal, never on fetched content. Consequences for the witnesses, each carried below: the canonical clause and the no-empty-entry clause are invisible at product scope (a plain symlinked-absolute entry bounds; so does `:` + a canonical one), so W-C3s asserts the EMITTED value at the spawn-request seam and is their only discriminator (Mc6); pack runs git at the repository top, where no ceiling value changes discovery (measured with ceilings at, above and below the nested source), so W-C5's named mutant reds only at the seam leg.

- [ ] **Step 0: the R-4.72 gate — Task 6e Step 0's block, run with `LABEL=c1e MODE=pre` before the first c1e test byte and `LABEL=c1e MODE=post` immediately before the commit** (the block STOPs `anchor-absent` if c1d's pre receipt does not exist and `words-moved-since-c1d` if any relay moved).
- [ ] **Step 1 (c1e): the failing tests** — `tests/test_repo_engine.cpp`, tagged `[repo][c1e]`, every request captured by the handle's `RequestTrace` (`resolved_git([&](const auto &r) { requests.push_back(r); })`), every address a `file://` bare repository. THE FIXTURE `enclosing(root)`: `encl/` = `init_repo` + `configure_url_rewrite(git, encl, requested, other)` where `requested` = `file://…/rec.git` (a bare repository holding the proof sha) and `other` = `file://…/other.git` (a second bare repository); the partial root is `encl/dest.partial`, a PLAIN directory (never a repository). THE ROW: an OVERLAY row (the class whose clone is network-class, `restore.cpp:545`) built as the landed `url-real-clone-population` case builds its `overlay` entry (`:660-690`) with `requested` its remote and proof url and the proof sha `rec.git`'s HEAD.
  - **W-C1** `restore_entry(git, overlay, encl/dest.partial, stage)` → `has_value()`; `UrlDivergenceRun` (scoped, no hook) has `refused` and `accepted` EMPTY; the restored repository's `remote.origin.url` == `requested`; EVERY captured request carries exactly one `GIT_CEILING_DIRECTORIES=` entry equal to `"GIT_CEILING_DIRECTORIES=" + std::filesystem::canonical(root / "encl").string()`, the `ls-remote --get-url` request and the network request it guards included. NAMED MUTANT Mc1 (m-1): the ceiling omitted → `url_divergence_refused` ⇒ RED.
  - **W-C2** the `encl/.git` tree digested before and after W-C1 (every regular file under it, sorted relpath + bytes) → equal (m-4 w2: no host write).
  - **W-C3** the partial root reached through a SYMLINK (`root/link` → `encl`, partial `root/link/dest.partial`) → W-C1's assertions hold, the emitted value being the CANONICAL `encl`. NAMED MUTANT Mc2 (m-1's probe form): `":" + partial_root.parent_path().string()` (empty-entry prefix, the symlinked spelling) → the refusal returns ⇒ RED.
  - **W-C3s** (pair Planner, the seam discriminator of the canonical and no-empty-entry clauses — both invisible at product scope, measured) on W-C3's run: the emitted value == `canonical(parent)`, begins with `/`, and differs from the symlinked spelling `root/link` (so the leg can see a missing `canonical()`). NAMED MUTANT Mc6: `canonical()` dropped (the parent emitted as spelled) → W-C3s RED while W-C3 stays GREEN — recorded as the reason W-C3s exists.
  - **W-C4** control: the same overlay row restored into a partial root under NO repository → the row's fields and the restored repository equal what the same fixture gives at the c1d head (Step 2 records that baseline to `$EVID/code/c1e-w-c4-baseline.txt`; Step 4 compares).
  - **W-C5** pack-side negative: `outer/` a repository with `origin` = `file://…/outer.git`; `outer/src/` a clean repository with `origin` = `file://…/src.git` → `classify(git, outer/src, one_repo())` records `src.git`, and NO request captured during `classify`, `run_eligibility` and `capture` of that entry carries a `GIT_CEILING_DIRECTORIES=` entry. NAMED MUTANT Mc4 (m-1): the ceiling set in `Git::resolve` (any value in the base environment) → the seam assertion RED; the behaviour assertion stays GREEN (pack runs git at the repository top — measured), recorded.
  - **W-C6** an un-canonicalizable parent, INJECTED at the engine seam: a `BIV_REPO_TESTING`-only hook in `restore.cpp` beside the file's existing testing idiom (its shape is m-1's at the byte review) makes the canonicalization fail while every earlier check passes → the typed `restore_error` at step `clone`, and ZERO requests captured. A missing or unwritable parent is NOT an acceptable fixture: `restore_entry`'s own `mkdir` refusal (`restore.cpp:85`, also step `clone`, also zero spawns) would fire first and green the leg under the mutant. NAMED MUTANT Mc5: the failure branch replaced by a call WITHOUT the ceiling → a request appears ⇒ RED.
  - **THE EC-4 COUPLING CONTROL**: the landed `url-real-clone-population` case (`:655-700`, whose partial IS a repository carrying the rewrite) stays GREEN, byte-for-byte: git always examines its working directory itself, so a `.git` INSIDE the partial is outside any ceiling — which is exactly why m-4 made the dot-git refusal at both writers (c6p's predicate) the other half of this property.
- [ ] **Step 2 (c1e): run at the c1d head to verify failure** — the build fails (`Git::Opts::ceiling`, `GitInvokeOptions::ceiling` and the W-C6 hook do not exist); with those three declarations stubbed in the worktree only: W-C1, W-C3, W-C3s RED (`url_divergence_refused`; no `GIT_CEILING_DIRECTORIES=` in any request), W-C2 GREEN (a refused restore writes nothing into `encl`), W-C4 GREEN (the baseline recorded), W-C5 GREEN (its discriminator is Mc4), W-C6 RED. Recorded to `$EVID/code/c1e-mutants.txt`; the stubs discarded before Step 3.
- [ ] **Step 3 (c1e): the implementation, per the fence** — `git.hpp` / `git.cpp`: the `ceiling` member and, in `build_spawn_request` after the `GIT_PROTOCOL_FROM_USER` line, `if (opts.ceiling) { env.emplace_back("GIT_CEILING_DIRECTORIES=" + opts.ceiling->string()); }`. `git_exec.hpp` / `git_exec.cpp`: the `ceiling` member and `git_options.ceiling = options.ceiling;` beside `git_options.isolate_global_config = options.restore;` (BEFORE the network branch). `restore.cpp`: `restore_invoke` and `require_success` gain a trailing `const std::optional<std::filesystem::path>& ceiling` carried into `GitInvokeOptions{…, .ceiling = ceiling}`; `restore_entry` computes the canonical parent ONCE before its first git call — on failure `return std::unexpected(restore_error(entry, "clone", "ceiling: " + ec.message()));` (the landed `"mkdir: " + error.message()` idiom at `:85`; the detail is m-1's at the byte review) — and every helper it calls receives and passes it. Nothing else in `src/core/repo` moves; the network-class census line count stays 6 (`git grep -n 'GitCallClass::network' HEAD -- src | wc -l` recorded to `$EVID/code/c1e-network-class.txt`; its content delta against the c1d head is data for m-1's byte review and Task 9 Step 1).
- [ ] **Step 4 (c1e): run to verify pass + the named mutants** — `./build/ci-macos/biv_repo_engine_tests '[c1e]'` rc 0; `./build/ci-macos/biv_repo_engine_tests` rc 0 (every landed case green, the EC-4 control included); `ctest --preset ci-macos -E '^safety-hardening$'` rc 0. THE MUTANTS, each on the worktree copy with the touched file saved to `$EVID/code/<file>.c1e` first and restored after (`cmp` == 0, rebuild, `[c1e]` rc 0 again), each result appended to `$EVID/code/c1e-mutants.txt`: Mc1 the ceiling never emitted → W-C1, W-C3, W-C3s RED; Mc1b the ceiling applied to the network call but NOT to its `--get-url` resolution → W-C1 RED (the resolution still sees `encl`); Mc2 `":" + <the symlinked parent>` → W-C3 RED, W-C1 GREEN (its parent is already canonical — recorded); Mc3 a RELATIVE entry (`partial_root.parent_path().lexically_relative(partial_root)`, i.e. `..`) → W-C1 RED; Mc4 the ceiling in `Git::resolve`'s base environment → W-C5's seam assertion RED, its behaviour assertion GREEN (recorded); Mc5 the un-canonicalizable branch replaced by a call without the ceiling → W-C6 RED; Mc6 `canonical()` dropped → W-C3s RED, W-C3 GREEN (recorded).
- [ ] **Step 5 (c1e): the veto-9 shape check, then commit (Step 0's gate re-run with `LABEL=c1e MODE=post` IMMEDIATELY before this block)** — `git status --porcelain` names exactly the six Files-line paths; `git diff --stat -- src/cli src/core/pack src/core/scan src/core/open src/core/manifest src/core/repo/classify.cpp src/core/repo/eligibility.hpp src/core/repo/eligibility.cpp src/core/repo/discover.cpp src/core/repo/capture.cpp src/core/repo/restore.hpp` EMPTY.

```bash
[ -s "$EVID/code/r472-owner-words.c1e.post.txt" ] && [ "$EVID/code/r472-owner-words.c1e.post.txt" -nt "$EVID/code/r472-owner-words.c1e.pre.txt" ] && [ "$(sed -n 1p "$EVID/code/r472-owner-words.c1e.post.txt")" = 'mode=post label=c1e' ] || { echo 'STOP: run the Task 6e Step 0 gate with LABEL=c1e MODE=post immediately before this commit'; exit 1; }
git add src/core/repo/git.hpp src/core/repo/git.cpp src/core/repo/git_exec.hpp src/core/repo/git_exec.cpp src/core/repo/restore.cpp tests/test_repo_engine.cpp
git commit -m "repo: every restore invocation bounded by GIT_CEILING_DIRECTORIES = canonical(partial_root.parent_path()) -- one absolute entry computed once per restore_entry before its first spawn, carried to the network call and its same-context --get-url resolution; an un-canonicalizable parent is a typed clone failure with zero spawns; pack, classify, eligibility and capture unbounded; no GIT_DIR -- R-4.72 open half (m-4 144917 EC-1, R472_ENCLOSING_REPO ceiling); m-1 150702 section 2 pre-authorized engine input c1e (R472_CEILING_PLACEMENT own-commit-in-lane); W-C1..W-C6"
git rev-parse HEAD > "$EVID/commits.c1e.txt"
```

### Task 7 — c7, the product-scope witnesses: every deferred leg executed through the REAL CLI against `biv pack`-PRODUCED images (E1; master 041518's re-execution condition; m-1 §2; m-3 §1; FX-A6/A7/A8/M/N; rev28, R-4.72: the PACK grain on REAL config after c1d, the OPEN grain on the LABELLED shim, the ISO family after c1e, E3 at the pack verb — T-R472)

**Files:** Create `tests/test_wiring.cpp` (added to `biv_tests`), Modify `tests/cli_run.hpp` (fixture builders), `CMakeLists.txt` (source list).
**Fixtures (built by the tests in temp dirs; reality-shaped; no network egress — every remote is a local bare repo reached over `file://`):** `F-REMOTE` (bare `remote.git` + a working clone with one commit, one `.gitignore`d penumbra file and `origin` — CLEAN: ARM-1 REALITY, every packed fixture is committed; an untracked file is the dirty fence); `F-DIVERGE` (a second bare `effective.git` cloned from `remote.git`; the working repo's LOCAL config `url.file://…/effective.git.insteadOf file://…/remote.git` — same-context, M leg (h)); `F-DIVERGE-GLOBAL` (rev28: the SAME rule in a temp `HOME/.gitconfig` handed to the child `biv pack` — the pack side reads global config; W-U2's product form); `F-TEMP-HOME-OPEN` (rev28: the recorded url's rewrite in a temp `HOME/.gitconfig` handed to the child `biv open` — the ISOLATION witness W-2, which asserts it has NO effect because restore sets `GIT_CONFIG_GLOBAL=/dev/null`; rev≤27 called this fixture F-RESTORE-DIVERGE and required it to DIVERGE, which the landed isolation makes impossible — Task 4 recorded that impossibility at rev13 while this task kept the fixture: the pair Planner's defect, removed here); `F-ENCL` (rev28, m-3's reproduction as m-4's EC-2 w1: the open's destination inside an enclosing repository `encl/` whose `.git/config` carries `url.<other>.insteadOf <recorded>`, `<other>` a second bare repository; `--dest encl/sub/out`); `F-ENCL-LINK` (rev28: F-ENCL with the destination's containing directory reached through a symlink); `F-SHIM-OPEN` (rev28: the LABELLED test-local shim — the landed `install_trace(root, /*inject_divergence=*/true)` idiom of `tests/test_cli.cpp:1720-1733`, reproduced byte-for-byte in `tests/cli_run.hpp` as `labelled_divergence_shim(root)` because that helper is file-local to `test_cli.cpp`, which is outside this task's Files; it answers every `--get-url` with `https://effective.invalid/repo` and forwards every other call to the real git; installed for an OPEN run only, over a product-packed image; every receipt from it carries `detection=shim` and is never cited as product detection — m-4 140901 (ii), 144917 EC-3; m-3 150622 W-1s); `F-TWO-REPOS` (two working repos with identical requested/effective addresses — a6·6); `F-NESTED` (a repo containing an untracked nested repo — §2.2 order, leaves-first); `F-SHALLOW` (`git clone --depth 1 file://…/remote.git` — N (a)); `F-PROMISOR-SHALLOW` (`git clone --filter=blob:none --depth 1` — N (g)); `F-GITLINK` (a `.git` regular file pointing at a gitdir — discover boundary); `F-UNCLAIMED` (`.git` symlink → `UnclaimedGitEntry`); `F-EQUIV` (rewrites within/without M-R2's equivalence set using `https://Host.invalid/…` ↔ `https://host.invalid/…/`, `http://…:80`, `ssh://…:22`, scp forms — the effective hosts are `.invalid` (RFC 2606, NXDOMAIN by definition) and `GIT_SSH_COMMAND=/usr/bin/false` is set for the child so no transport ever connects; the legs assert PROMPT/REFUSE vs SILENT and `remote_unreachable`/full, never timing). The request-trace instrument: BLOCK `git-shim.sh` installed FIRST on the child's `PATH` — it appends `argv` to `$BIV_GIT_TRACE` and `exec`s the real git; every leg that claims "zero git", "no spawn after DENY", or "no ls-remote" reads that log.

- [ ] **Step 0: the R-4.72 gate — Task 6e Step 0's block with `LABEL=c7 MODE=pre` before the first c7 test byte and `LABEL=c7 MODE=post` immediately before the commit (Step 5 refuses without the post receipt).**
- [ ] **Step 0b: the T-C check** — `grep -c -E 'render_prompt_c|PROMPT C|memory' src/cli/main.cpp src/core/open/render.cpp`; PROMPT C absent at B → a6·10 is REGISTERED (S-6, m-3) in `$EVID/legs/registered.txt`, not written.
- [ ] **Step 1: the legs, one `TEST_CASE` each, tagged `[wiring][<leg>]`, each writing its receipt line `leg=<id> provenance=product-packed verdict=PASS` to `$EVID/legs/<id>.txt` via `BIV_LEG_RECEIPTS`** (the FX text is the oracle; the named mutants are the reason each assertion exists):
  - **M (a)** pack, F-DIVERGE (REAL config, no shim — reachable once c1d records the configured url; NAMED MUTANT: c1d reverted ⇒ rc 0 and the manifest records the effective url ⇒ RED, Step 4b), non-interactive, no flag → exit 3, `error.kind == UrlDivergenceRefused`, `facts.requested`/`facts.effective` VERBATIM, `error.path` = the repo, nothing written (no `.bvpk`, no `.partial`, no `.scratch`); **(a)-interactive**: `run_cmd_pty_split`, answer `n` → refused; the shim log has NO `ls-remote … effective.git` line after the prompt (DENY leaves the network call UN-EXECUTED — by instrument).
  - **M (b)/(i)/(j)** open of a product-packed F-REMOTE image with F-SHIM-OPEN installed for the OPEN run only (LABELLED, `detection=shim`, never product detection: the restore isolation and the ceiling leave no configuration able to reach these sites — m-4 140901, 144917) → each restore site's op label (`ref-recreation` / `clone` / the third `restore.cpp:545` site's label) appears in a `UrlDivergenceEntryRefused` row's `op`; three fixtures (an overlay entry for the clone site; a local_refs remote-proven entry for ref-recreation; the non-full clone arm) — the implementer records which fixture reached which site from the row's `op` and the shim log.
  - **M (c)** F-REMOTE without rewrite: pack + open → zero prompts, zero refusals, zero `url-divergence-accepted`; the envelopes byte-identical modulo `image_id`/`created_at`/paths to a run with the consent fabric's flag absent (they ARE the same run — the assertion is "no fabric surface appears").
  - **M (d)** `--accept-url-divergence` on pack (a6·3; F-DIVERGE, REAL config) and on open (a6·4; F-SHIM-OPEN, labelled): no prompt, proceeds, the notice on stderr byte-golden, ONE `url-divergence-accepted` entries row with the four fields verbatim.
  - **M (e)(f)(l)(m)(n·i)(n·ii)(o)** F-EQUIV forms, each rule in the packed working repository's LOCAL config (REAL, at the PACK verb, after c1d — before c1d every rewrite read SILENT, so each SILENT sub-arm passed for the wrong reason; its DIVERGENCE twin is now its discriminator) → SILENT (no prompt, no refusal, `remote_unreachable` → full) vs DIVERGENCE (refuse/prompt) exactly per the M table; each subarm its own case.
  - **M (g)** = **E3 AT THE PACK VERB** (m-4 140901 rebinds E3 to pack; 144917 EC-3 keeps it there): F-DIVERGE, divergence + NO hook (non-interactive, no flag) → typed `url_divergence_refused` naming BOTH addresses, exit 3, nothing written — receipt `E3-macos.txt`; Task 9 repeats it in the Linux parity container; ONLY this pack case carries the `[E3]` tag. The OPEN grain of (g) (rows + exit 2) runs on F-SHIM-OPEN, labelled — receipt `M-g-open-shim.txt`, untagged, never cited as E3.
  - **M (h)** = F-DIVERGE's default (local config only) → detected at pack (W-U1's product form); its GLOBAL twin F-DIVERGE-GLOBAL (W-U2's product form) → the identical outcome; after an accepted run (`--accept-url-divergence`) each image's manifest records the CONFIGURED url (m-1 `R472_MANIFEST_URL: configured`; SR-URL-5 (b)'s property). NAMED MUTANT: c1d reverted ⇒ both rc 0 with the effective url recorded ⇒ RED (Step 4b).
  - **M (k)** REGISTERED (T-K).
  - **ROUTING (rev28, R-4.72; m-3 150622 W-1s/W-3; m-4 140901 (ii), 144917 EC-3)** — every a6 / a7 / a8 leg below runs at the verb its text names. A PACK-grain leg runs on F-DIVERGE (REAL config, no shim): a6·1, a6·2, a6·3, a6·6 (F-TWO-REPOS: two sibling repositories, each with its local rule), a6·7, a6·13, a7·1, a7·2, a7·3, a7·5, and a6·16's pack envelopes. An OPEN-grain leg runs on F-SHIM-OPEN, LABELLED: a6·4, a6·5, a6·12, a7·4, and a6·16's open envelope; PROMPT D's interactive yes and no answer paths at open (m-3 W-3) ride the shim over the pty. a8·5 / a8·6 carry their hostile bytes in the configured url and its rewrite (REAL config, pack) wherever git config carries them byte-exactly; a coordinate git config cannot carry byte-exactly runs on F-SHIM-OPEN, labelled, and the implementer records each coordinate's route in `$EVID/legs/a8-routes.txt`. Every shim receipt line reads `leg=<id> provenance=product-packed detection=shim verdict=PASS`; the packet cites none of them as product detection. W-4 (m-3) rides EVERY open-grain leg and every ISO leg: the image's recorded url (`repos[].remotes[].url`) read back after the open equals the configured url, unchanged.
  - **a6·1** empty answer → refused (default N); **a6·2** `y` → proceeds, notice golden, entries row, exit 0; **a6·5** memo: open of an overlay entry where the same triple is met at proof-fetch and clone → ONE prompt, ONE notice, ONE entries row; **a6·6** F-TWO-REPOS → two prompts, two rows inside ONE outer `url-divergence-accepted` object, distinguished by `repo`, in encounter order; **a6·7** pack preflight golden refusal (template in `error.detail` AND on the stream, class refusal, exit 3, NOTHING written); **a6·8** flag + PROMPT B image → B still renders; **a6·9** flag + collision → PROMPT A still renders; **a6·11** accept case: NO summary line, NO `warnings` row; **a6·12** two refused entries (distinct `repo_id` AND `relpath`) + one clean, every session row clean → two rows in encounter order, `error` null, exit 2, the clean entry restored, the per-entry template twice on stderr in encounter order (asserted SEPARATELY from the JSON order), the guidance line EXACTLY ONCE with `<n>`=2 after the last per-entry line; **a6·13** run 1 with the flag, run 2 without, non-interactive → refused; no acceptance artifact under the workspace or the temp HOME; **a6·16** (divergence half) the serialized envelopes of a6·2 / a6·7 / a6·12 validate against the LANDED schema through `Draft202012Validator` (a python step over the captured envelopes, run from the venv, receipt `a6-16.txt`).
  - **a7·1** stdin redirected (stderr TTY) → no prompt, typed refusal; **a7·2** stderr redirected (stdin TTY) → no prompt, typed refusal; **a7·3** `run_cmd_pty_split` + `--json`, flag absent, first encounter → PROMPT D renders on the pty (stderr), the answer honored, the envelope on the PIPE (stdout) records the outcome; the split helper's recorded TTY states are asserted (`stdin_tty && stderr_tty && !stdout_tty`); **a7·4** an image triggering PROMPT B AND a restore divergence → B completes before any D; the D prompts in entry encounter order; **a7·5** pack with two divergent remotes (distinct triples) → two prompts at the probe encounter points in order, each atomic (no other stderr byte between a prompt's question and its answer — asserted on the pty transcript).
  - **a8·5** arm A: values carrying the TEN valid rows → `error.facts` / refusal rows / advisories entries round-trip the RAW bytes exactly (C0 via JSON `\u00xx` decoding back byte-exact; multi-byte scalars byte-exact) while the stderr carriers hold the display-encoded form; arm B1: the lone `0x9b` in requested / effective / repo (each in turn) → PROMPT D shows U+FFFD, the decision binds the RAW triple (a second encounter of the SAME raw triple is memo-answered — no second prompt), and on EVERY carrier the source×branch matrix names the serialized value is VALID UTF-8 with the malformed octet visibly REPLACED (U+FFFD) — never the raw `0x9b`, never a display escape (A8-R1's malformed-value arm; `machine_text`); arm B2: `0x9b` in `op`/`relpath`/`repo_id` → no consent claim, the same replacement oracle on the carriers the matrix names for those coordinates. NAMED MUTANT (both arms): invalid-UTF-8 JSON output ⇒ RED; a `\u{…}`/`\u00xx` display spelling inside a machine field ⇒ RED. **a8·6**: a verb-reachable hostile effective address carrying the ten valid rows at the pty → the transcript adds no line, moves no cursor, contains no raw ESC/format scalar; `y` binds the raw triple (memo witness as in B1).
  - **ISO — the open isolation family (rev28, R-4.72 open half, after c1e; m-4 144917 EC-2/EC-4; m-3 150622 W-1′/W-2/W-4/W-5; m-1 150702 W-C1..W-C4 at product scope)** — each leg packs F-REMOTE (NO rewrite; the recorded url `file://…/remote.git`) with `biv pack`, then opens that image non-interactively with `--network`; receipts `ISO-<leg>.txt`:
    - **W-1′ = W-C1** F-ENCL → `biv open <image> --dest encl/sub/out --network` (no flag) → rc 0, the row restored, NO prompt, NO `UrlDivergenceEntryRefused` row, NO `url-divergence-accepted`, NO divergence text on stderr, and `git -C encl/sub/out config --get remote.origin.url` == the recorded url. NAMED MUTANT Mc1 at product scope (c1e reverted, Step 4b): rc 2, the failed row, `UrlDivergenceEntryRefused` — m-3 141015's refusal returns ⇒ RED. The leg asserts the refusal's ABSENCE and the rc, never fetched content: without the ceiling the clone itself still fetches the recorded url (measured, Task 6f), so a content-only assertion would stay green under Mc1.
    - **W-C2** the `encl/.git` tree digested (every regular file, sorted relpath + sha256) before and after W-1′'s open → equal (no host write).
    - **W-C3** F-ENCL-LINK → W-1′'s assertions hold. Mc2 at product scope (`:` + the symlinked parent) ⇒ RED (Task 6f's seam run; the product form is observed in Step 4b with c1e reverted as the no-ceiling bound).
    - **W-C4** the no-enclosing control: the same image opened into a directory under NO repository → the row and the envelope equal (modulo `image_id`/`created_at`/paths) to the same open run by Step 4b's c1e-reverted build — the ceiling changes nothing outside an enclosing repository.
    - **W-C5** pack side, behaviour only: a clean source repository whose containing directory is itself inside ANOTHER repository with a different `origin` → `biv pack` of the inner workspace → the manifest records the INNER repository's configured url. Its named mutant (the ceiling in `Git::resolve`) is caught only by Task 6f's seam leg — pack runs git at the repository top, where no ceiling value changes discovery (measured) — so this leg is a behaviour guard, never cited as Mc4's discriminator.
    - **W-2** (m-3; m-4 140901 (ii)) F-TEMP-HOME-OPEN → rc 0, the recorded url cloned, no prompt, no row, no notice (the landed `GIT_CONFIG_GLOBAL=/dev/null` isolation).
    - **W-5** (m-3 150622, the addition) on F-ENCL: `biv open <image> --dest encl/sub/out2 --network --accept-url-divergence` → rc 0, NO notice, no divergence text; its stderr and envelope equal W-1′'s (modulo `image_id`/`created_at`/paths) — the flag is INERT when nothing reaches the gate. Under Mc1 the flagged run proceeds WITH the notice while W-1′ refuses ⇒ RED.
    - **EC-4, NAMED, not re-run**: the dot-git refusal at both writers (c6p's FP1/FP2 on hand-built images — pack claims `.git` and cannot produce a `payload/.git/…` member) is the other half of this property; the ISO receipts cite R1-P's beside them, and the H review reads c1e and c6p's predicate together (m-1 150702 EC-3/EC-4).
    - **NOT ASSERTED**: m-3's mixed-endpoint observation (closed by construction under the ceiling, m-4 144917 (3)); the networked-open notice's host-config clause (m-3's registered follow-up).
  - **N (a) WHOLE**: F-SHALLOW → `biv pack` → the manifest row carries the full N-R2 cluster (`shallow{boundary}`, no `capture_mode`, no `eligibility`, no `local_refs`, no `bundle`) → `biv open` → `result.repos[0].outcome == "shallow-pointer"`, ZERO git lines in the shim log for that entry (the log is per-run: with only the shallow entry in the image, the whole open shows zero git); **E4 parity**: the same open with `--offline` → the row IDENTICAL (field-by-field) and zero git; receipt `E4-parity.txt`. (rev26, R-4.70 — this leg was ABSENCE-BLIND through rev25: it asserted the row and zero git and would have passed with the whole working tree dropped, which c5 does) BOTH opens also assert F-SHALLOW's working tree at `<dest>/<relpath>` byte-, mode- and mtime-equal to the source's, directories included, and `<dest>/<relpath>/.git` ABSENT; **H at product scope**: an empty `git init` holding an untracked `sub/f.txt` → a `payload-only-unborn` row whose tree lands the same way with and without `--offline`, zero git. **N (g)**: F-PROMISOR-SHALLOW → `biv pack` → `notes[]` carries `{"kind":"promisor-source"}`.
  - **RCPT-P (m-1 rev2 §1, the PACK receipt) + W-O1..3 at product scope**: F-MIXED (one born non-shallow repo with `origin` + F-SHALLOW + an unborn repo with a side ref + an empty unborn repo, all under one workspace) packed TWICE — with and without `--offline` — through the request-trace shim: under `--offline` the shim log has ZERO network-class lines (`ls-remote`/`fetch`) for the whole pack (receipt `RCPT-P-trace.txt`); the two manifests' `repos[]` differ ONLY in the born non-shallow row's `eligibility` + `capture_mode` + the derived `local_refs[].availability` members (receipt `RCPT-P-manifest-diff.txt`, the field-level diff); the shallow row (N-R2), the unborn-with-ref row (G) and the empty-unborn row (H) are byte-identical across the two packs (W-O1/W-O2/W-O3 receipts). A born non-shallow PROMISOR source under `--offline` → the engine's `promisor_objects_unavailable` surfaces as today's engine-error path (T-PROM); a SHALLOW promisor source under `--offline` → a pointer row with the promisor-source note, exit 0 (N's never-refuse).
  - **W-D1..4 at product scope (under ARM-1 REALITY)**: F-NESTED-BIV (`a/.git` + `a/.biv/r/.git`, both clean) → `biv pack` REFUSES with the nested fence naming `a/.biv/r` (at c5 the seam `repo-nested-unsupported`; after c6b `RepoNestedUnsupported`, `error.path == "a/.biv/r"`) and writes NO image — this IS W-D1's product form: the discovery correction makes the nested repository VISIBLE; NAMED MUTANT (the landed any-depth `.biv` skip): the pack SUCCEEDS with one row and the nested repository silently lost ⇒ RED; F-ROOT-BIV (`.biv/r/.git` at the workspace root beside a clean root repo) → ONE row, no refusal (W-D2: the reserved area is not walked); F-NESTED-BIV-IGNORED (the same tree with `.bivignore` = `a/.biv/`) → ONE row, the pack SUCCEEDS, and the pack-end prune summary NAMES `a/.biv` with its `.bivignore` source (W-D3's provenance half — the sealed §1.1 pack-end summary, the scanner's `PruneEntry`; the transitional posture's honest remedy, m-1 074712 §1 FLAG); W-D4: in the F-NESTED-BIV-IGNORED image the parent row's payload census (the archive member listing under `payload/`) holds NO `a/.biv/r/**` node — a negative-membership observation credited together with V-2b-5's single-writer legs and m-1's byte review (044559), never alone. The two-row nested image is T-ARM (ii), REGISTERED.
  - **pack discovery legs**: F-NESTED (a clean parent with a clean child repo) → the NESTED fence refuses (Q11; T-ARM (ii)/(iii) registered — no two-row image, no leaves-first observation at 2b); F-GITLINK → a boundary for discovery, then the SUBMODULE fence refuses at classify (Q11; A11 (c)) — the `.git` REGULAR FILE is never an unclaimed-entry refusal; F-UNCLAIMED → `UnclaimedGitEntry` exit 3, `reason == "symlink"`, detail golden, nothing written; a repo under a `.bivignore`d dir → NOT discovered, the prune-summary advisory names the dir; a workspace-root repo (`git init` at the workspace root + one tracked file + one IGNORED file (`.gitignore`d — an untracked file would be the dirty fence) + a subdirectory with tracked files + one IGNORED file inside that tracked subdirectory) → the archive's `payload/` members are EXACTLY the row's penumbra — the two ignored files and each untracked-only directory holding one (T-RED1) — and NO tracked path; the row's `relpath` is `.`; `biv open` restores the repo at `<dest>` with both ignored files present, laid after the root checkout (c6p, T-RED1 `defer`). rev22 CORRECTS rev≤21's "ZERO `payload/` members … the ignored file present (the engine's penumbra, not payload)": nothing writes the engine's penumbra set, so that leg carried V-2b-5's omission (R-4.65 RED-1). NAMED MUTANT 1: the root-claimed fast path removed → tracked paths appear as `payload/…` members ⇒ RED (the product discriminator for MUST-2B-12; V-2b-5); NAMED MUTANT 2: c5's pack (no penumbra member) → the ignored files absent after open ⇒ RED.
  - **R-T** the round trip: F-REMOTE (CLEAN) with an IGNORED penumbra file + a local branch → `biv pack` → `biv open` → the restored repo's `git status --porcelain=v2` is EMPTY like the source's; HEAD/branch equal; the ignored penumbra file byte-equal; the local branch recreated (`local_refs[0].recreated == true`). (c6p is this leg's precondition — before it the ignored file is absent, R-4.65 RED-1. The dirty-worktree round trip is T-ARM (i), REGISTERED.)
  - **A11 legs at product scope (after c6b)**: A11.5 (a)–(m) re-executed through the REAL CLI — the dirty / nested / submodule / unmerged fixtures of Task 5 → exit 3, no image, the wire kind, path/facts, the byte-golden sentence, `transitional: true` where A11.1 says so; the shim-injected REF-UNCAPTURABLE, PROMISOR (both arms), GIT FAILED (pack), GIT FAILED / BUDGET (open, fresh target: no workspace, partial inventoried, the failed row with kind), RESTORE FAILED, OP ABSENT, UNKNOWN STAYS INTERNAL, COUNTS BY MEMBERSHIP (37 / 38 / the six transitional by name), the three carriers with CR as `\r` — receipts `A11-<leg>.txt`. Before c6b these fixtures assert the c5 seam (`InternalError` + `repo_engine_kind`, no image) and are re-asserted after it.
  - **A10 legs at product scope (after c4b)**: A10.4 (a)–(m) re-executed on product-packed images (a networked image = F-REMOTE packed ONLINE with an overlay-capture row, or a full row with a remote-proven local ref — the network-needing derivation recorded in `$EVID/code/network-needing-rows.txt`): notice before any git (shim tripwire); decline ⇒ offline-pointer rows exit 0, the shallow and H rows serializing `capture_mode` null; non-interactive no flag; `--network`; `--json` parity; `--offline` never; PROMPT D untouched after `y`; the rows; hostile URL bytes; (j) the born / unborn / detached / HEAD-only idioms (T-STAGE, byte-exact; the detached form with the bare `'HEAD'` refspec) each run TWICE with the harness's git — into the non-empty target and into an absent scratch target, rc 0 ×8, the HEAD state per idiom as Task 4 Step 6 (j) states, the HEAD-only row's commit IMPORTED (`cat-file -e`), with its controls (a double-quoted operand, an unquoted one, the rev7 wildcard-only detached form on the HEAD-only fixture ⇒ RED); (k) the exact argv under the seven copy-safe hazards through the argv-recording stub (operands byte-equal to the raw values, no sentinel expansion); (l) the five non-copy-safe fallbacks (no command printed, the fallback line display-encoded, `bundle_path` present and JSON `reconstruct` ABSENT, the ordinary sibling row still printing); (m) the offline-unborn sha cell (`"(no commits)"` on the G row, `null` on the H row; `capture_mode` `null` and no bundle field on the H row) + RCPT-Q (`<dest>/.biv/repos/<id>/repo.bundle` present with the checksum for every artifact-bearing row, absent for every other row, zero git) — receipts `A10-<leg>.txt`, `RCPT-Q.txt`.
- [ ] **Step 2: run to verify failure** — each new case fails before its fixture/assertion wiring exists (the file is new; the first build with the cases stubbed as `FAIL("not yet")` is the red state).
- [ ] **Step 3: implement the fixtures and assertions** — `tests/cli_run.hpp` gains `GitFixture` helpers (`init_bare`, `init_work(remote)`, `set_instead_of(repo, requested, effective)`, `temp_home_with_instead_of(...)`, `shim_path(trace_file)`; rev28: `enclosing_repo_with_instead_of(dir, recorded, other)`, `labelled_divergence_shim(root)`), each a thin wrapper over `git` invocations through `std::system` with quoted paths; every fixture asserts its own preconditions (`git rev-parse HEAD` succeeds; `git remote get-url origin` equals the requested address).
- [ ] **Step 4: run to verify pass** — `./build/ci-macos/biv_tests '[wiring]'` rc 0 (PTY legs run under a real pty allocated by the helper; under ctest they still allocate their own pty); `ctest --preset ci-macos -E '^safety-hardening$'` rc 0; the receipts directory holds one file per leg id listed in the evidence matrix; `ls "$EVID/legs" | wc -l` recorded; `registered.txt` lists exactly the S-6 registrations (T-K, T-C if absent).
- [ ] **Step 4b (rev28): the product-scope mutants, in a DISPOSABLE worktree** — `git worktree add --detach "$EVID/work/c7-mut" HEAD` (never the lane's worktree); the three c7 files copied in and `cmp`-verified; (i) `git -C "$EVID/work/c7-mut" revert --no-commit "$(cat "$EVID/commits.c1d.txt")"`, build, `biv_tests '[wiring]'` → M (a), M (h) and F-DIVERGE-GLOBAL's leg RED (rc 0, the effective url recorded); `git -C "$EVID/work/c7-mut" reset --hard HEAD`, the three files copied in again; (ii) the same with `commits.c1e.txt` → W-1′, W-C3 and W-5 RED, W-C4's run recorded as its baseline; each observed line to `$EVID/legs/c7-product-mutants.txt`; then `git worktree remove --force "$EVID/work/c7-mut"` with the receipt `$EVID/legs/c7-mut-disposed.txt` (the path absent; `git worktree list` no longer names it). A mutant that stays GREEN is a STOP UP (the witness does not discriminate), never a weakened oracle.
- [ ] **Step 5: commit (Step 0's gate re-run with `LABEL=c7 MODE=post` IMMEDIATELY before this block)** —

```bash
[ -s "$EVID/code/r472-owner-words.c7.post.txt" ] && [ "$EVID/code/r472-owner-words.c7.post.txt" -nt "$EVID/code/r472-owner-words.c7.pre.txt" ] && [ "$(sed -n 1p "$EVID/code/r472-owner-words.c7.post.txt")" = 'mode=post label=c7' ] || { echo 'STOP: run the Task 6e Step 0 gate with LABEL=c7 MODE=post immediately before this commit'; exit 1; }
git add tests/test_wiring.cpp tests/cli_run.hpp CMakeLists.txt
git commit -m "tests: product-scope witnesses through the real CLI on biv-pack-produced images -- FX-M-1 (a)-(o) incl. (d) and (a)-interactive, a6.1-13 + a6.16, a7.1-5 (split-stream pty), a8.5/a8.6, FX-N (a) whole + (g), E3 fail-safe, E4 offline parity, the pack->open round trip; R-4.72: the pack grain on real config (c1d), the open grain on the labelled shim, the ISO family (c1e: W-1-prime, W-C2..W-C5, W-2, W-5), E3 at pack"
git rev-parse HEAD > "$EVID/commits.c7.txt"
```

### Task 8 — c8, m-3's harness commit (arm-A shape; m-3 §5): the golden round-trip repos scenario + the A2 FXD-3 offline scenario — AUTHORED AT m-3's SEAT, applied VERBATIM as ONE commit

**Files:** EXACTLY the twelve paths of m-3's rev3 patch (rev22; `$RUNNERS/m3-harness-patch.txt`, written 2026-09-21 from master's 143755: `patch=master/domains/m-3-restore-cli/patches/2026-09-21-c8-harness-scenarios-rev3.patch`, `sha256=8517aaf6ee4fb9e9c48d47d03618ddcda472be23f022176a21108515cf336871`, `relay=master/relays/intg-2b-wiring-act/DESIGN-REVIEW-implementer-20260921-133052.md` — m-3.implementer's exact-sha approve; rev1 `beb5a20e…` and rev2 `9a4da1b3…` are DEAD): `harness/scenarios/d-git-restore.json` (the active E2 scenario), `harness/scenarios/fxd3-open-offline.json` (the `biv open --offline` scenario), `harness/scenarios/shells/d-git-restore.json` (the shell, emptied), and — admitted by m-3's explicit line (222346 / 124555 / 131146) — `harness/bivharness/{compare,manifest,scenario}.py`, `harness/schemas/manifest-repo-entry-shape-v1.schema.json`, `harness/selftest/{test_compare,test_manifest,test_probe_isolation,test_specs}.py`, `harness/tolerance/tolerance-v1.json` (the `git-checkout-dir-mtime: ignore-checkout` row, m-1's `C8_DIR_MTIME_RULING: a`, 141529). `harness/bivharness/e3.py` untouched. Declared `population_change_expected=yes` (1014 → 1055, +41).

- [ ] **Steps 0–1: the patch gate and the ONE commit — the EXECUTABLE block below, run ONCE from the worktree at the c7 head** (rev22; `patch=` is pdc-RELATIVE and resolved under `$PDC/master/domains/`, the approve under `$PDC/master/relays/`, exactly as Task 4 Step 3c resolved the R-4.62 file — rev≤21 said `<abs path>`): the file's three fields; the patch re-hashed; the approve's seven face lines once each; the mailbox author once; the tree clean; `git apply --check`; `--numstat` EQUAL to the twelve expected lines (a thirteenth path, a moved count or a missing path STOPs — a `harness/selftest` path is a population change and these four are budgeted: Task 9 Step 4); `git am` (the mailbox preserves m-3's authorship; no commit-message file); exactly one commit, authored `m-3.planner <m-3.planner@local>`, touching exactly the twelve paths.

```bash
# Task 8 Steps 0-1 — m-3's harness patch bound by bytes and applied VERBATIM as ONE commit with m-3's authorship (rev22; Task 4 Step 3c's shape)
set -o pipefail
STOP() { printf 'STOP-c8 %s line=%s\n' "$1" "${BASH_LINENO[0]}" >&2; exit 1; }
[ -n "$RUNNERS" ] && [ -n "$EVID" ] && [ -d "$EVID/code" ] || STOP env
[ -s "$EVID/commits.c7.txt" ] && [ "$(git rev-parse HEAD)" = "$(cat "$EVID/commits.c7.txt")" ] || STOP not-at-c7
F=$RUNNERS/m3-harness-patch.txt; [ -s "$F" ] || STOP file-absent
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
git diff --cached --quiet || STOP index-dirty
git diff HEAD --quiet || STOP worktree-dirty
u=$(git ls-files --others --exclude-standard); r=$?; [ "$r" -eq 0 ] && [ -z "$u" ] || STOP untracked
git apply --check "$PF" || STOP apply-check
ns=$(git apply --numstat "$PF"); r=$?; [ "$r" -eq 0 ] || STOP numstat-producer
exp=$(printf '37\t1\tharness/bivharness/compare.py\n19\t2\tharness/bivharness/manifest.py\n20\t1\tharness/bivharness/scenario.py\n116\t0\tharness/scenarios/d-git-restore.json\n101\t0\tharness/scenarios/fxd3-open-offline.json\n0\t8\tharness/scenarios/shells/d-git-restore.json\n99\t0\tharness/schemas/manifest-repo-entry-shape-v1.schema.json\n82\t0\tharness/selftest/test_compare.py\n105\t0\tharness/selftest/test_manifest.py\n26\t0\tharness/selftest/test_probe_isolation.py\n3\t2\tharness/selftest/test_specs.py\n1\t0\tharness/tolerance/tolerance-v1.json')
[ "$ns" = "$exp" ] || STOP numstat
files=$(printf '%s\n' "$exp" | cut -f3 | LC_ALL=C sort) || STOP files-producer
PREHEAD=$(git rev-parse HEAD) || STOP head
a=0; git am "$PF" > "$EVID/code/c8-am.log" 2>&1 || a=$?; [ "$a" -eq 0 ] || { git am --abort >/dev/null 2>&1; STOP am; }
POSTHEAD=$(git rev-parse HEAD) || STOP head2; [ "$POSTHEAD" != "$PREHEAD" ] && [ "$(git rev-parse HEAD~1)" = "$PREHEAD" ] || STOP not-one-commit
[ "$(git log -1 --format=%an)" = m-3.planner ] && [ "$(git log -1 --format=%ae)" = m-3.planner@local ] || STOP author
got=$(git show --format= --name-only HEAD | LC_ALL=C sort) || STOP show-producer; [ "$got" = "$files" ] || STOP commit-files
git diff --cached --quiet && git diff HEAD --quiet || STOP dirty-after
printf '%s\n' "$POSTHEAD" > "$EVID/commits.c8.txt" || STOP commits-write; [ -s "$EVID/commits.c8.txt" ] || STOP commits-empty
printf 'patch=%s sha256=%s relay=%s relay_sha256=%s pre_head=%s post_head=%s paths=12 population_change_expected=yes\n' "$patch" "$sha" "$relay" "$rh" "$PREHEAD" "$POSTHEAD" > "$EVID/receipts/harness-patch.txt" || STOP receipt
[ -s "$EVID/receipts/harness-patch.txt" ] || STOP receipt-empty
printf 'c8 OK %s\n' "$POSTHEAD"
```

- [ ] **Step 2: run the harness scenario row on macOS** — the ctest row `harness-e2` (harness/CMakeLists.txt:39-43: `bivharness` over `harness/scenarios`) at the c8 head: `ctest --preset ci-macos -R '^harness-e2$' --output-on-failure --output-junit "$EVID/receipts/harness-e2-macos.junit.xml"` rc 0; the two scenario ids (`d-git-restore`, the offline FXD-3 scenario) green in the runner's output (the implementer records the exact command, rc and the per-scenario lines to `$EVID/receipts/harness-scenarios-macos.txt`); the assertion classes touched enumerated from the scenario files (rev29 record correction: m-3's reviewed rev3 patch declares `A,B,C,D,E,K` for `d-git-restore` and `E,K` for the FXD-3 scenario, as observed at impl-8; the earlier parenthetical `A/B/D/E/H/K` transcribed m-3's §5 word as registered, and whether the patch's set discharges it — C added, H absent — is m-3's, routed through master; the receipt records the declared classes and never relabels them); the tolerance fixture's digest recorded. The LINUX half of the receipt is produced by Task 9's H0 container (`harness-e2` inside its ctest run, `$EVID/H/harness-e2-linux.txt`); BOTH halves at the same H0 are what m-3 §5 requires and what m-1's V-2b-8(iv) reads.
- [ ] **Step 3: record** — `$EVID/commits.c8.txt` and `$EVID/receipts/harness-patch.txt` are written by the block (`population_change_expected=yes`: the four `harness/selftest` files add 41 tests, 1014 → 1055 as m-3 declared); `git status --porcelain` EMPTY. Task 9 Step 4 MEASURES the two populations and runs the `015244` series when they differ — the declaration budgets it, the measurement decides it.

### Task 8b — c8L, c8Tr and c8T, the Linux-toolchain repairs (test-only; engine seam; the tidy class with the owners' words), each head gated by the canonical container and its pinned tidy list (rev33; the impl-10 Task 9 STOP `intg-substep2b/IMPL-pair-implementer-20260924-201131.md`; master `215035` R1/R2/R3, `224030` Asks A/B/C, `…-20260925-003436.md` cells (A)/(B) and the three owner words)

**Why this task exists.** impl-10's Task 9 met the canonical Linux toolchain for the first time and stopped at `cmake --build` on two GCC errors. The whole census (`results/linux-census-20260924/`) found three classes at a83657e = c8, none at B: 24 `-Werror=missing-field-initializers` errors in 6 TEST files; one c3 test that fails under the `-r xml` reporter on both platforms (Catch2's redirecting reporter re-points `std::cerr` at each assertion boundary, and the hook was called inside `CHECK`); and 32 clang-tidy errors in 7 PRODUCT files from seven 2b commits. Master ruled all three repaired INSIDE 2b before Task 9 (215035): R1 admits `tests/test_repo_git.cpp` (the 53rd path); R2 fixes the tidy class as behaviour-neutral product bytes — no NOLINT, no `.clang-tidy` change, neutrality argued per change, owner byte review by file before the landing, interface-level findings STOP up. 224030 Ask A: sealed per-commit veto 9 (Task 9 Step 2) refuses a commit spanning `src/core/repo/` and the surface paths, so `restore.cpp`'s repair is its own commit c8Tr; veto 9 is NOT amended. 003436 cell (A): the two test-only repairs are ONE commit c8L — a head with the initializers but not the c3 fix fails that case under `-r xml` on both platforms, and a head with the c3 fix but not the initializers does not compile under GCC, so no two-commit split has a green first head (walked, and confirmed at master's bytes). 003436 cell (B): ONE c8T carrying the 22 mechanical fixes AND the owners' words — m-1 `DESIGN-planner-20260924-224747.md` (`C8T_B5_SEGMENT: amend`, `C8T_B6_PENUMBRA: amend`), m-3 `DESIGN-planner-20260924-225029.md` (`C8T_B1_TABLE: admit`, `C8T_B2_SIGNATURE: admit`, `C8T_B3_PRIVDIRS: amend`, `C8T_B4_DECODER: amend`), m-4 `DESIGN-planner-20260924-225018.md` (`C8T_SECURITY_READ: conditions`, F-C8T-1, C-U1..C-U4) — so c8T's head is tidy GREEN.

**Files:** c8L — `tests/test_cli.cpp`, `tests/test_envelope.cpp`, `tests/test_open.cpp`, `tests/test_pack.cpp`, `tests/test_repo_git.cpp` (admitted by 215035 R1), `tests/test_scan.cpp`; c8Tr — `src/core/repo/restore.cpp` ALONE; c8T — `src/cli/consent_display_table.hpp` (REGENERATED), `src/cli/main.cpp`, `src/cli/url_consent.cpp`, `src/cli/url_consent.hpp`, `src/core/open/open.cpp`, `src/core/pack/pack.cpp`, `src/core/report/envelope.cpp`, `tests/test_cli.cpp`, `tests/test_open.cpp`, `tools/gen_consent_display_table.py`.

**The bytes are the pair Planner's census patches, applied VERBATIM** (never re-typed), each read from the docs-lane commit `dfffc4912b721717b152d84960abf1df0c19b253` by `git show` and bound by its sha256; each applies to the previous head and yields the scout tree pinned in the block (measured at this seat: the three patches applied in order on a83657e reproduce the scout trees exactly):

```text
label patch (results/linux-census-20260924/)          sha256 (prefix)   numstat                                   tree (prefix)
c8L   repair-12-c8L-tests.patch                        d7bb5097…         +37/-12 over the six test files           1fd0bf64…
c8Tr  repair-3-c8Tr-restore-seam.patch                 f58cc043…         +6/-3 src/core/repo/restore.cpp           17583a96…
c8T   repair-5-c8T-folded.patch                        213f9d54…         +99/-65 over ten files                    22b801f0…
```

**Neutrality, change by change** (the owners' byte reviews re-derive each at the landed bytes, never from this list):
- c8L: each omitted member named in declaration order (`= std::nullopt` / `= {}`), the value the omission already gave; the c3 hook called once, outside `CHECK`, its decision asserted after — the same call and the same oracle.
- c8Tr: the non-const global becomes a function-local static behind `forced_ceiling_error()` — one constant-initialized bool, internal linkage, the two accessors unchanged (m-4 Item 2 clear; m-1's pre-stated conditions: no third accessor, no header, no product writer, no NOLINT, c1e's W-C6 and its mutant re-run at landing — the c8Tr record below).
- c8T, mechanical: `main.cpp` `row.sha.value_or(std::string{})` (unreachable-empty: `manifest.cpp`'s `sha_head_state` clause and `open.cpp:1159`'s unborn render, re-derived at master's bytes); `url_consent.cpp` do-while → `while (true)` with the identical break test, `paths.at(i)` inside the unchanged bound, the empty `catch (...) {}` → `catch (const std::invalid_argument&)` / `catch (const std::out_of_range&)` each setting `total = 0` (the two throw classes `std::stoull` has; m-4 Item 1 clear — the `UnmergedIndexUnrepresentable` pack-refusal detail, not a consent render); `envelope.cpp` and `open.cpp` `value_or` inside the UNCHANGED `has_value()` guards; `open.cpp` `.at()` inside existing bounds (none can throw; in `noexcept` helpers a wrong guard would terminate instead of reading out of bounds — the direction m-4 accepts) and `StageCleanup`'s defaulted constructor with deleted copy/move; `pack.cpp` `std::iota` for the hand loop and `entries.at(i)` inside the bound; the c2 manifest-serialize hunk untouched.
- c8T, the words: B1 — `tools/gen_consent_display_table.py` emits `kConsentDisplayActive.at(mid)` at its two accessor lines, and the header is REGENERATED by the tool from the pinned Unicode inputs (never hand-edited); against c8Tr's header exactly three lines differ — the `generator sha256:` comment and the two accessors — every range row, the version line, the input digests and the member/range counts byte-identical. B2 — `struct OfflineBundleRow { std::string_view relpath; std::string_view absolute_bundle_path; std::optional<std::string> reconstruct; }` and `render_offline_bundle_row(const OfflineBundleRow&)`, both call sites (`main.cpp`, `tests/test_cli.cpp`) built with designated initializers; the rendered bytes and every expected literal unchanged (the `test_cli.cpp` swap witness `find(...) == 0` stands unedited). B3 — `struct PrivateDirectories { std::filesystem::path root; std::filesystem::path relative; }` (value members: `const path&` members trip `avoid-const-or-ref-data-members`), the body byte-identical behind two local references, the one call site designated. B4 — `std::optional<char32_t> next_utf8(std::string_view, size_t& offset)`: only `codepoint = …; return true;` → `return …;` and `return false;` → `return std::nullopt;`; every decode statement — the lead-byte classes, the masks, `minimum`, the truncation guard, the continuation-mask test, the range and surrogate test — literally unmoved (C-U3); the one caller reads the optional. B5 — `path_has_biv_segment(path)`, the literal a function-local `constexpr std::string_view segment = ".biv";` so the loop is byte-for-byte; the one call updated. B6 — `directory_is_all_penumbra(directory, penumbra, repo_root)`, the body byte-for-byte, the one call reordered. WITNESSES (test bytes only, `tests/test_open.cpp`, each `CHECK_FALSE` for `is_dotgit_component` and its `.biv` twin for `is_dotbiv_component`): w1 `".g" + E2 80 0C + "it"` (= m-4's C-U1), w2 `C0 AE + "git"`, w3 `E0 80 AE + "git"`, and w4 `".git" + E2 80` kept as a plain regression input (NOT gating, master 003436). No test case is added or removed (the counts do not move).

**THE MUTANT RECORD at the c8T head (m-4 C-U2, m-3 B4, m-1 B5/B6; ruled by master 003436).** Each mutant is one coordinate, applied to the working tree only, built, run, recorded in `$EVID/receipts/c8T-mutants.txt` and reverted, the tree proved clean after each; its bytes are never committed. GATING (a survivor STOPs): M-MASK (the continuation-mask test removed; w1 and its twin go red — measured 2), `minimum` (the overlong test neutralised as `decoded < (minimum & 0U)`, because removing it leaves `minimum` unused and does not compile under `-Werror`; w2/w3 and their twins go red — measured 4), M-SEC (`continuation_count = 2` → `3` in the three-byte class; the EXISTING ZWNJ, BOM and RLM positives go red — measured 6), B6-swap (the two paths swapped at the call; RED in `c6p pack writes each repository row's penumbra as payload members`, sections "non-root row" and "root row recursive directory ground truth" — measured 2; a green is a STOP to m-1). RECORDED, NOT GATING: truncation (the guard removed; at c8T's bytes the over-read hits `string_view::at` inside a `noexcept` helper, so the run terminates on `std::out_of_range` — rc 134, deterministic, and only with w4 present; without w4 it is green — reported to master for a ruling, gating nothing here) and B5-bix (`.biv` → `.bix`; `failures=0` across all of `biv_tests` in both scout runs — its assertion total is not pinned, since the two runs counted 21 899 and 21 896 — per m-1 a RESIDUALS row under m-1, not a hold).

**THE c8Tr RECORD at the c8Tr head (m-1 224747 §2).** c1e's W-C6 (`W-C6: an un-canonicalizable parent is typed and spawns no git`, `biv_repo_engine_tests`) GREEN at the c8Tr bytes, and two one-coordinate mutants of `restore.cpp` RED, each reverted and the tree proved clean after (`$EVID/receipts/c8Tr-mutants.txt`): Mc5 (the failure branch disabled, `if (ceiling_error && false)`, so the call proceeds without the ceiling — c1e's named mutant) and M-SEAM (the flag write dropped, `forced_ceiling_error() = false && enabled;`, so the seam can no longer force the failure — the mutant for the bytes c8Tr moves). Measured at the scout: W-C6 4/0; Mc5 and M-SEAM each rc 42, 2 failures.

**B1 REPRODUCES.** At the c8T head the generator, run on the pinned Unicode inputs (`$EVID/work/ucd/`, digests in `$EVID/receipts/ucd-inputs.sha256`), reproduces the committed header byte-for-byte, and the diff c8Tr → c8T of the header is exactly the three lines above (`$EVID/receipts/c8T-b1-regeneration.txt`).

**THE PER-HEAD GATE (215035 R3, corrected by 224030, final form 003436).** At EVERY new head the canonical container gives rc 0 AND the tidy finding set is BYTE-EQUAL to that head's pinned list, coverage 37/37: c8L — `clang-tidy-errors-patched.txt` (32 lines, `7c8b1d6c…`, the container's output at the scout head with the same tree); c8Tr — `clang-tidy-held-after-c8Tr.txt` (31 lines, `deef500a…`); c8T — EMPTY, the tidy row PASSED (measured at the c8T scout head). The lists are the container's own output (`grep -E ': error: .*\['` over `ctest-linux-H.log`, `/work/repo/` stripped, `LC_ALL=C sort -u`). The same gate runs the macOS build and the five `-r xml` producers at the head (every rc 0, every tuple `failures=0` — a failure count is never a tuple move), binds the container's head receipt, requires Linux tuples `failures=0`, every other ctest row passed but `harness-selftest` (recorded, R-4.77 data) with exactly the two skip rows not run, scans the container logs for credential shapes, and writes `$EVID/heads/<label>/` (created once, confined; an existing directory is a STOP, never an overwrite).

- [ ] **Step 0: the precondition** — HEAD is the c8 head (`commits.c8.txt` = a83657e…), the tree clean; `$EVID/llvm-manifest.txt` present and pinned (Task 9's produced input, digest `22724f78…`).
- [ ] **Step 1: c8L** — the commit block with `c8L`, then the gate block with `c8L` (rc 0; `heads/c8L/headgate.txt`).
- [ ] **Step 2: c8Tr** — the commit block with `c8Tr`; then the c8Tr record block; then the gate block with `c8Tr`.
- [ ] **Step 3: c8T** — the commit block with `c8T`; then the B1 check block; then the mutant block; then the gate block with `c8T`.
- [ ] **Step 4: record** — `$EVID/commits.c8L.txt`, `commits.c8Tr.txt`, `commits.c8T.txt`, `$EVID/receipts/<label>-commit.txt`, `receipts/c8Tr-mutants.txt`, `receipts/c8T-b1-regeneration.txt`, `receipts/c8T-mutants.txt`, `$EVID/heads/<label>/headgate.txt` for each; `git status --porcelain` EMPTY; the code-task discipline's `ctest --preset ci-macos -E '^safety-hardening$'` rc 0 at the c8T head.

**OWNER BYTE REVIEW SCOPE (224030 Ask C as ratified, with the words of 003436; before the landing, inside each owner's no-red review of H that Task 10's GO binds):** m-1 — `restore.cpp` (c8Tr, against its pre-stated conditions), `pack.cpp` (c8T incl. B5/B6 against its §1 cuts), and co-review of `open.cpp`'s dot-name helpers (`ascii_fold` through `protected_component`) and c6p's ancestor loops (`owned_output_path`) inside the restore-apply contract; m-3 — `open.cpp`, `envelope.cpp`, `main.cpp`, `url_consent.{hpp,cpp}`, the regenerated table with its recorded diff, the generator, and the witnesses; m-4 (security read) — `url_consent.cpp` (the catch and the consent surface; the no-edited-expected-literal rule), `url_consent.hpp`, the regenerated table with its diff, `restore.cpp:10-18`, and `open.cpp`'s fold-and-decode helpers (`ascii_fold` through `protected_component`) with the C-U1 witness and the M-MASK / M-SEC records. Each review reads them at H.

```bash
# Task 8b — ONE repair commit from the pair's census patch, bound by bytes (rev33; master 215035 R1/R2, 224030 Ask A, 003436 cells (A)/(B)): usage  bash <this block> <LABEL>  with LABEL in c8L c8Tr c8T, in that order
set -o pipefail
STOP() { printf 'STOP-c8r %s line=%s\n' "$1" "${BASH_LINENO[0]}" >&2; exit 1; }
LABEL=${1-}; MAIN=/Users/jack/Programming/bivpak; CR=dfffc4912b721717b152d84960abf1df0c19b253; RD=docs/sprints/2026-08-27-intg-consent-fabric/results/linux-census-20260924
[ -n "$EVID" ] && [ -d "$EVID/code" ] || STOP env
case "$LABEL" in
  c8L) PREV=c8; PF=repair-12-c8L-tests.patch; PS=d7bb50972e2917d6f480bde62839df3a5f41ee35d1f1b311d05e8f7c22480bc3; TREE=1fd0bf64e6d55e36cc6dde4962ac91f53d2ecbff
       EXP=$(printf '8\t3\ttests/test_cli.cpp\n6\t1\ttests/test_envelope.cpp\n4\t1\ttests/test_open.cpp\n12\t3\ttests/test_pack.cpp\n2\t0\ttests/test_repo_git.cpp\n5\t4\ttests/test_scan.cpp')
       MSG='test: name every member the 2b structs gained in the test initializers (Linux GCC -Werror=missing-field-initializers), and call the c3 hook outside CHECK so a redirecting reporter (-r xml) cannot bypass the captured stderr -- c8L, test-only';;
  c8Tr) PREV=c8L; PF=repair-3-c8Tr-restore-seam.patch; PS=f58cc04302f7091c1c388b7d27d2d3ab923143f971b426d82bc81d011f626e67; TREE=17583a966f54627f062237b2067a7136328e02cd
       EXP=$(printf '6\t3\tsrc/core/repo/restore.cpp')
       MSG='engine: restore ceiling test seam held in a function-local static (clang-tidy non-const global) -- c8Tr, behaviour-neutral, m-1 byte';;
  c8T) PREV=c8Tr; PF=repair-5-c8T-folded.patch; PS=213f9d543b8228ee250413311d641b795f6280edd4b51128ab07b4bfceca6986; TREE=22b801f0ef1f5dea10f4cc27a84569f0c9ca42e4
       EXP=$(printf '3\t3\tsrc/cli/consent_display_table.hpp\n3\t2\tsrc/cli/main.cpp\n16\t10\tsrc/cli/url_consent.cpp\n7\t3\tsrc/cli/url_consent.hpp\n38\t28\tsrc/core/open/open.cpp\n9\t10\tsrc/core/pack/pack.cpp\n6\t3\tsrc/core/report/envelope.cpp\n3\t2\ttests/test_cli.cpp\n12\t2\ttests/test_open.cpp\n2\t2\ttools/gen_consent_display_table.py')
       MSG='tidy: the clang-tidy findings of the 2b commits repaired behaviour-neutrally with the owners words (m-3 B1-B4, m-1 B5-B6, m-4 conditions) and the decoder witnesses, no suppression -- c8T';;
  *) STOP label;;
esac
[ -s "$EVID/commits.$PREV.txt" ] && [ "$(git rev-parse HEAD)" = "$(cat "$EVID/commits.$PREV.txt")" ] || STOP not-at-prev
[ ! -e "$EVID/commits.$LABEL.txt" ] && [ ! -L "$EVID/commits.$LABEL.txt" ] || STOP already-committed
W=$EVID/code/$LABEL.patch; [ ! -e "$W" ] && [ ! -L "$W" ] || STOP patch-copy-exists
g=0; git -C "$MAIN" cat-file -e "${CR}^{commit}" || g=$?; [ "$g" -eq 0 ] || STOP census-commit
g=0; git -C "$MAIN" show "${CR}:${RD}/${PF}" > "$W" || g=$?; [ "$g" -eq 0 ] && [ -s "$W" ] || STOP patch-read
h=0; ph=$(shasum -a 256 "$W" | cut -d' ' -f1) || h=$?; [ "$h" -eq 0 ] && [ "$ph" = "$PS" ] || STOP patch-sha
git diff --cached --quiet || STOP index-dirty
git diff HEAD --quiet || STOP worktree-dirty
u=$(git ls-files --others --exclude-standard); r=$?; [ "$r" -eq 0 ] && [ -z "$u" ] || STOP untracked
git apply --check "$W" || STOP apply-check
ns=$(git apply --numstat "$W"); r=$?; [ "$r" -eq 0 ] || STOP numstat-producer
[ "$ns" = "$EXP" ] || STOP numstat
PRE=$(git rev-parse HEAD) || STOP head
a=0; git apply --index "$W" || a=$?; [ "$a" -eq 0 ] || STOP apply
g=0; git commit -q -m "$MSG" || g=$?; [ "$g" -eq 0 ] || STOP commit
POST=$(git rev-parse HEAD) || STOP head2; [ "$POST" != "$PRE" ] && [ "$(git rev-parse HEAD~1)" = "$PRE" ] || STOP not-one-commit
[ "$(git rev-parse 'HEAD^{tree}')" = "$TREE" ] || STOP tree
git diff --cached --quiet && git diff HEAD --quiet || STOP dirty-after
printf '%s\n' "$POST" > "$EVID/commits.$LABEL.txt" || STOP commits-write; [ -s "$EVID/commits.$LABEL.txt" ] || STOP commits-empty
printf 'label=%s patch=%s sha256=%s census_commit=%s pre_head=%s post_head=%s tree=%s\n' "$LABEL" "$PF" "$PS" "$CR" "$PRE" "$POST" "$TREE" > "$EVID/receipts/$LABEL-commit.txt" || STOP receipt
[ -s "$EVID/receipts/$LABEL-commit.txt" ] || STOP receipt-empty
printf 'c8r %s OK %s\n' "$LABEL" "$POST"
```

```bash
# Task 8b — m-1's pre-stated c8Tr landing condition (224747 §2): c1e's W-C6 GREEN at the c8Tr bytes and its named mutant Mc5 still RED, plus the seam mutant (the flag write dropped) RED; run ONCE at the c8Tr head, before its head gate
set -o pipefail
STOP() { printf 'STOP-c8tr-mutants %s line=%s\n' "$1" "${BASH_LINENO[0]}" >&2; exit 1; }
[ -n "$EVID" ] && [ -d "$EVID/receipts" ] || STOP env
[ -s "$EVID/commits.c8Tr.txt" ] && [ "$(git rev-parse HEAD)" = "$(cat "$EVID/commits.c8Tr.txt")" ] || STOP not-at-c8Tr
git diff --cached --quiet && git diff HEAD --quiet || STOP dirty
O=$EVID/receipts/c8Tr-mutants.txt; [ ! -e "$O" ] && [ ! -L "$O" ] || STOP record-exists
M=$EVID/code/c8Tr-mutants; [ ! -e "$M" ] && [ ! -L "$M" ] || STOP work-exists; m=0; mkdir "$M" || m=$?; [ "$m" -eq 0 ] || STOP work-mkdir
F=src/core/repo/restore.cpp; WC6='W-C6: an un-canonicalizable parent is typed and spawns no git'
b=0; cmake --build --preset ci-macos > "$M/green.build.log" 2>&1 || b=$?; [ "$b" -eq 0 ] || STOP build-green
x=0; ./build/ci-macos/biv_repo_engine_tests "$WC6" -r xml > "$M/green.xml" 2> "$M/green.stderr" || x=$?
g=0; res=$(grep -o '<OverallResults successes="[0-9]*" failures="0"' "$M/green.xml" | tail -n 1) || g=$?; [ "$x" -eq 0 ] && [ "$g" -eq 0 ] && [ -n "$res" ] || STOP w-c6-not-green
printf 'witness=W-C6 run_rc=%s %s\n' "$x" "$res" >> "$O" || STOP record-write
mut() { local name=$1 old=$2 new=$3
  a=0; python3 -c 'import sys; p,x,y=sys.argv[1:4]; s=open(p).read(); assert s.count(x)==1; open(p,"w").write(s.replace(x,y))' "$F" "$old" "$new" || a=$?; [ "$a" -eq 0 ] || STOP "apply-$name"
  b=0; cmake --build --preset ci-macos > "$M/$name.build.log" 2>&1 || b=$?; [ "$b" -eq 0 ] || { git checkout -q -- "$F"; STOP "build-$name"; }
  x=0; ./build/ci-macos/biv_repo_engine_tests "$WC6" -r xml > "$M/$name.xml" 2> "$M/$name.stderr" || x=$?
  g=0; res=$(grep -o '<OverallResults successes="[0-9]*" failures="[0-9]*"' "$M/$name.xml" | tail -n 1) || g=$?
  c=0; git checkout -q -- "$F" || c=$?; [ "$c" -eq 0 ] || STOP "revert-$name"; git diff HEAD --quiet || STOP "not-clean-after-$name"
  printf 'mutant=%s gating=yes run_rc=%s %s\n' "$name" "$x" "${res:-no-result}" >> "$O" || STOP record-write
  [ "$x" -ne 0 ] || STOP "survived-$name"; }
mut Mc5 '  if (ceiling_error) {
    return std::unexpected(' '  if (ceiling_error && false) {
    return std::unexpected('
mut M-SEAM '  forced_ceiling_error() = enabled;' '  forced_ceiling_error() = false && enabled;'
b=0; cmake --build --preset ci-macos > "$M/rebuild.log" 2>&1 || b=$?; [ "$b" -eq 0 ] || STOP rebuild
git diff --cached --quiet && git diff HEAD --quiet || STOP dirty-after
g=0; k=$(grep -c -E '^(witness|mutant)=' "$O") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 3 ] || STOP record-rows
printf 'c8Tr mutants OK (%s)\n' "$O"
```

```bash
# Task 8b — B1 reproduces (rev33; m-3 225029 B1, m-4 225018 Item 4): at the c8T head the generator, on the pinned Unicode inputs, reproduces the committed header byte-for-byte, and the header's diff from c8Tr is exactly the generator-digest line and the two accessor lines
set -o pipefail
STOP() { printf 'STOP-c8t-b1 %s line=%s\n' "$1" "${BASH_LINENO[0]}" >&2; exit 1; }
[ -n "$EVID" ] && [ -d "$EVID/receipts" ] || STOP env
[ -s "$EVID/commits.c8T.txt" ] && [ "$(git rev-parse HEAD)" = "$(cat "$EVID/commits.c8T.txt")" ] || STOP not-at-c8T
z=0; TR=$(cat "$EVID/commits.c8Tr.txt") || z=$?; [ "$z" -eq 0 ] && [ -n "$TR" ] && [ "$(git rev-parse HEAD~1)" = "$TR" ] || STOP not-after-c8Tr
O=$EVID/receipts/c8T-b1-regeneration.txt; [ ! -e "$O" ] && [ ! -L "$O" ] || STOP record-exists
v=0; (cd "$EVID/work/ucd" && shasum -a 256 -c "$EVID/receipts/ucd-inputs.sha256") > "$EVID/code/c8T-ucd-verify.txt" 2>&1 || v=$?; [ "$v" -eq 0 ] || STOP ucd-inputs
g=0; python3 tools/gen_consent_display_table.py "$EVID/work/ucd/UnicodeData.txt" "$EVID/work/ucd/DerivedCoreProperties.txt" "$EVID/receipts/ucd-inputs.sha256" > "$EVID/code/c8T-regenerated.hpp" || g=$?; [ "$g" -eq 0 ] && [ -s "$EVID/code/c8T-regenerated.hpp" ] || STOP generator
c=0; cmp "$EVID/code/c8T-regenerated.hpp" src/cli/consent_display_table.hpp > "$EVID/code/c8T-regenerated.cmp" 2>&1 || c=$?; [ "$c" -eq 0 ] || STOP header-not-regenerated
d=0; git diff --unified=0 "$TR" HEAD -- src/cli/consent_display_table.hpp > "$EVID/code/c8T-header.diff" || d=$?; [ "$d" -eq 0 ] || STOP diff
g=0; grep -E '^[-+][^-+]' "$EVID/code/c8T-header.diff" > "$EVID/code/c8T-header.changed" || g=$?; [ "$g" -eq 0 ] || STOP changed-lines
a=0; n=$(awk 'END { print NR }' "$EVID/code/c8T-header.changed") || a=$?; [ "$a" -eq 0 ] && [ "$n" -eq 6 ] || STOP changed-count
g=0; k=$(grep -c -E '^[-+]// generator sha256: [0-9a-f]{64}$' "$EVID/code/c8T-header.changed") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 2 ] || STOP generator-line
g=0; k=$(grep -c -E '^-    (if \(scalar < |else if \(scalar > )kConsentDisplayActive\[mid\]\.(first|last)' "$EVID/code/c8T-header.changed") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 2 ] || STOP accessor-old
g=0; k=$(grep -c -E '^\+    (if \(scalar < |else if \(scalar > )kConsentDisplayActive\.at\(mid\)\.(first|last)' "$EVID/code/c8T-header.changed") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 2 ] || STOP accessor-new
c=0; cp "$EVID/code/c8T-header.diff" "$O" || c=$?; [ "$c" -eq 0 ] && [ -s "$O" ] || STOP record-write
printf 'c8T B1 OK: the header regenerates byte-for-byte; 3 lines differ from c8Tr (%s)\n' "$O"
```

```bash
# Task 8b — the c8T mutant record (rev33; m-4 225018 C-U2, m-3 225029 B4, m-1 224747 B5/B6, ruled by master 003436): run ONCE at the c8T head, before its head gate
# each mutant is ONE coordinate, applied to the working tree only, built, its case run, recorded, and reverted; the tree is proved clean after each; a mutant that does not compile is a STOP, never a record
set -o pipefail
STOP() { printf 'STOP-c8t-mutants %s line=%s\n' "$1" "${BASH_LINENO[0]}" >&2; exit 1; }
[ -n "$EVID" ] && [ -d "$EVID/receipts" ] || STOP env
[ -s "$EVID/commits.c8T.txt" ] && [ "$(git rev-parse HEAD)" = "$(cat "$EVID/commits.c8T.txt")" ] || STOP not-at-c8T
git diff --cached --quiet && git diff HEAD --quiet || STOP dirty
O=$EVID/receipts/c8T-mutants.txt; [ ! -e "$O" ] && [ ! -L "$O" ] || STOP record-exists
M=$EVID/code/c8T-mutants; [ ! -e "$M" ] && [ ! -L "$M" ] || STOP work-exists; m=0; mkdir "$M" || m=$?; [ "$m" -eq 0 ] || STOP work-mkdir
CO='c6p ownership rows and protected components are behavioral'; CP="c6p pack writes each repository row's penumbra as payload members"
mut() { local name=$1 gating=$2 file=$3 old=$4 new=$5 tcase=$6
  a=0; python3 -c 'import sys; p,x,y=sys.argv[1:4]; s=open(p).read(); assert s.count(x)==1; open(p,"w").write(s.replace(x,y))' "$file" "$old" "$new" || a=$?; [ "$a" -eq 0 ] || STOP "apply-$name"
  b=0; cmake --build --preset ci-macos > "$M/$name.build.log" 2>&1 || b=$?; [ "$b" -eq 0 ] || { git checkout -q -- "$file"; STOP "build-$name"; }
  x=0; if [ "$tcase" = ALL ]; then ./build/ci-macos/biv_tests -r xml > "$M/$name.xml" 2> "$M/$name.stderr" || x=$?; else ./build/ci-macos/biv_tests "$tcase" -r xml > "$M/$name.xml" 2> "$M/$name.stderr" || x=$?; fi
  g=0; res=$(grep -o '<OverallResults successes="[0-9]*" failures="[0-9]*"' "$M/$name.xml" | tail -n 1) || g=$?
  c=0; git checkout -q -- "$file" || c=$?; [ "$c" -eq 0 ] || STOP "revert-$name"; git diff HEAD --quiet || STOP "not-clean-after-$name"
  printf 'mutant=%s gating=%s run_rc=%s %s\n' "$name" "$gating" "$x" "${res:-no-result}" >> "$O" || STOP record-write
  if [ "$gating" = yes ]; then [ "$x" -ne 0 ] || STOP "survived-$name"; fi; }
mut M-MASK yes src/core/open/open.cpp '    if ((byte & 0xC0U) != 0x80U) return std::nullopt;
' '' "$CO"
mut minimum yes src/core/open/open.cpp 'if (decoded < minimum || decoded > 0x10FFFFU ||' 'if (decoded < (minimum & 0U) || decoded > 0x10FFFFU ||' "$CO"
mut M-SEC yes src/core/open/open.cpp '    continuation_count = 2;' '    continuation_count = 3;' "$CO"
mut B6-swap yes src/core/pack/pack.cpp 'source / std::filesystem::path{ancestor}, penumbra, repo_root);' 'repo_root, penumbra, source / std::filesystem::path{ancestor});' "$CP"
mut truncation no src/core/open/open.cpp '  if (value.size() - offset < continuation_count) return std::nullopt;
' '' "$CO"
mut B5-bix no src/core/pack/pack.cpp 'constexpr std::string_view segment = ".biv";' 'constexpr std::string_view segment = ".bix";' ALL
b=0; cmake --build --preset ci-macos > "$M/rebuild.log" 2>&1 || b=$?; [ "$b" -eq 0 ] || STOP rebuild
git diff --cached --quiet && git diff HEAD --quiet || STOP dirty-after
g=0; k=$(grep -c -E '^mutant=[A-Za-z0-9-]+ gating=(yes|no) run_rc=[0-9]+ ' "$O") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 6 ] || STOP record-rows
printf 'c8T mutants OK (%s)\n' "$O"
```

<!-- BLOCK: headgate.sh -->
```bash
# Task 8b — the per-head gate at ONE new head (rev33; master 215035 R3 as corrected by 224030, final form 003436): usage  bash <this block> <LABEL>  with LABEL in c8L c8Tr c8T (rev39: also c10, Task 8c, and c11, Task 9b; rev41: c10t, Task 8d), run at that commit's head before the next commit
set -o pipefail
STOP() { printf 'STOP-headgate %s line=%s\n' "$1" "${BASH_LINENO[0]}" >&2; exit 1; }
LABEL=${1-}; MAIN=/Users/jack/Programming/bivpak; CR=dfffc4912b721717b152d84960abf1df0c19b253; RD=docs/sprints/2026-08-27-intg-consent-fabric/results/linux-census-20260924
[ -n "$EVID" ] && [ -d "$EVID/code" ] && [ -s "$EVID/llvm-manifest.txt" ] || STOP env
case "$LABEL" in
  c8L) TL=clang-tidy-errors-patched.txt; TS=7c8b1d6cc80679d1fee0a7478b230774fa231c824dfabae137006b0fe461cb06; NT=32;;
  c8Tr) TL=clang-tidy-held-after-c8Tr.txt; TS=deef500a00896d789970d9d9b124844231583c2f66efae5e32f789e288f4d589; NT=31;;
  c8T) TL=none; TS=none; NT=0;;
  c10|c10t|c11) TL=none; TS=none; NT=0;;
  *) STOP label;;
esac
[ -s "$EVID/commits.$LABEL.txt" ] || STOP no-commit
z=0; HX=$(cat "$EVID/commits.$LABEL.txt") || z=$?; [ "$z" -eq 0 ] && [ -n "$HX" ] && [ "$(git rev-parse HEAD)" = "$HX" ] || STOP not-at-head
git diff --cached --quiet && git diff HEAD --quiet || STOP dirty
u=$(git ls-files --others --exclude-standard); r=$?; [ "$r" -eq 0 ] && [ -z "$u" ] || STOP untracked
if [ ! -e "$EVID/heads" ] && [ ! -L "$EVID/heads" ]; then m=0; mkdir "$EVID/heads" || m=$?; [ "$m" -eq 0 ] || STOP heads-mkdir; fi
[ -d "$EVID/heads" ] && [ ! -L "$EVID/heads" ] || STOP heads-kind
p=0; HP=$(cd "$EVID/heads" && pwd -P) || p=$?; [ "$p" -eq 0 ] && [ "$HP" = "$(cd "$EVID" && pwd -P)/heads" ] || STOP heads-confined
G=$EVID/heads/$LABEL; [ ! -e "$G" ] && [ ! -L "$G" ] || STOP gate-exists
m=0; mkdir "$G" || m=$?; [ "$m" -eq 0 ] || STOP gate-mkdir; m=0; mkdir "$G/H" || m=$?; [ "$m" -eq 0 ] || STOP gate-mkdir-H
if [ "$NT" -eq 0 ]; then c=0; : > "$G/tidy-expected.txt" || c=$?; [ "$c" -eq 0 ] || STOP expected-empty; else
g=0; git -C "$MAIN" show "${CR}:${RD}/${TL}" > "$G/tidy-expected.txt" || g=$?; [ "$g" -eq 0 ] && [ -s "$G/tidy-expected.txt" ] || STOP expected-read
h=0; es=$(shasum -a 256 "$G/tidy-expected.txt" | cut -d' ' -f1) || h=$?; [ "$h" -eq 0 ] && [ "$es" = "$TS" ] || STOP expected-sha
fi
a=0; ne=$(awk 'END { print NR }' "$G/tidy-expected.txt") || a=$?; [ "$a" -eq 0 ] && [ "$ne" -eq "$NT" ] || STOP expected-count
# macOS at the head: the build and the five -r xml producers; every rc 0 and every tuple failures=0 (a failure count is never a tuple move)
b=0; cmake --build --preset ci-macos > "$G/build-macos.log" 2>&1 || b=$?; [ "$b" -eq 0 ] || STOP mac-build
for binary in biv_subprocess_tests biv_repo_git_tests biv_repo_engine_tests biv_tests biv_probe_tests; do x=0; "./build/ci-macos/$binary" -r xml > "$G/$binary-macos.xml" 2> "$G/$binary-macos.stderr" || x=$?; printf '%s rc=%s\n' "$binary" "$x" >> "$G/run-rcs-macos.txt" || STOP rcs-write; [ -s "$G/$binary-macos.xml" ] || STOP "mac-xml-$binary"; done
g=0; k=$(grep -c -x -E 'biv_[a-z_]+ rc=0' "$G/run-rcs-macos.txt") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 5 ] || STOP mac-rc
a=0; n=$(awk 'END { print NR }' "$G/run-rcs-macos.txt") || a=$?; [ "$a" -eq 0 ] && [ "$n" -eq 5 ] || STOP mac-rc-rows
u=0; python3 "$EVID/tuples.py" macos "$G"/biv_subprocess_tests-macos.xml "$G"/biv_repo_git_tests-macos.xml "$G"/biv_repo_engine_tests-macos.xml "$G"/biv_tests-macos.xml "$G"/biv_probe_tests-macos.xml > "$G/tuples-macos.txt" || u=$?; [ "$u" -eq 0 ] && [ -s "$G/tuples-macos.txt" ] || STOP mac-tuples
g=0; k=$(grep -c -x -E 'biv_[a-z_]+ macos successes=[0-9]+ failures=0 expectedFailures=0 skips=[0-9]+ xml_sha256=[0-9a-f]{64}' "$G/tuples-macos.txt") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 5 ] || STOP mac-failures
g=0; k=$(grep -c -E '^biv_' "$G/tuples-macos.txt") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 5 ] || STOP mac-rows
# Linux at the head: the pinned clang-tidy-22 mirror, then the plan's own container (Phases R/T/S) with its three inputs byte-copied beside it
LLVM_RAW=$(mktemp -d "$EVID/llvm22-assets-H.XXXXXX") || STOP llvm-mktemp; LLVM_DIR=$(cd "$LLVM_RAW" && pwd -P) || STOP llvm-dir; c=0; cp "$EVID/llvm-manifest.txt" "$LLVM_DIR/MANIFEST" || c=$?; [ "$c" -eq 0 ] || STOP llvm-manifest
h=0; while read -r _ package asset; do gh release download toolchain-mirror-clang-tidy-22-immutable-v1 --repo iwnlcern/bivpak --pattern "$asset" --dir "$LLVM_DIR" || h=$?; done < "$LLVM_DIR/MANIFEST" > "$G/llvm-transport.log" 2>&1
a=0; awk '{ print $1 "  " $3 }' "$LLVM_DIR/MANIFEST" > "$LLVM_DIR/SHA256SUMS" || a=$?; [ "$a" -eq 0 ] && [ -s "$LLVM_DIR/SHA256SUMS" ] || STOP llvm-sums; v=0; (cd "$LLVM_DIR" && shasum -a 256 -c SHA256SUMS) > "$G/llvm-verify.txt" 2>&1 || v=$?; printf 'llvm_transport_rc=%s verify_rc=%s\n' "$h" "$v" > "$G/llvm.rc"; [ "$h" -eq 0 ] && [ "$v" -eq 0 ] || STOP llvm-verify
for f in linux-container.sh linux-suite.sh observer-unset-names.txt; do c=0; cp -p "$EVID/$f" "$G/$f" || c=$?; [ "$c" -eq 0 ] && [ -f "$G/$f" ] && [ ! -L "$G/$f" ] && cmp -s "$EVID/$f" "$G/$f" || STOP "input-$f"; done
o=0; docker run --rm --platform linux/amd64 --init -v "${LLVM_DIR}:/llvm-mirror:ro" -v "${MAIN}:/repo-ro:ro" -v "${G}:/evidence" ubuntu:24.04 bash /evidence/linux-container.sh "$HX" H > "$G/H/linux-container.log" 2>&1 || o=$?; printf '%s\n' "$o" > "$G/linux-container.rc"; [ "$o" -eq 0 ] || STOP container
for f in linux-ledger.txt linux-suite-ledger.txt linux-run-head-receipt.txt container-payload.rc ctest-linux-H.log ctest-linux-H.junit.xml biv_subprocess_tests-linux.xml biv_repo_git_tests-linux.xml biv_repo_engine_tests-linux.xml biv_tests-linux.xml biv_probe_tests-linux.xml; do [ -s "$G/H/$f" ] || STOP "absent-$f"; done
g=0; k=$(grep -c -x -F "expected=$HX observed=$HX" "$G/H/linux-run-head-receipt.txt") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP head-receipt
[ "$(cat "$G/H/container-payload.rc")" = container_payload_rc=0 ] || STOP payload
for x in phase_R_base_provision_rc=0 phase_R_asset_provision_rc=0 phase_T_transition_fixture_rc=0 phase_S_suite_rc=0; do g=0; k=$(grep -c -x -F -- "$x" "$G/H/linux-ledger.txt") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP "ledger-$x"; done
g=0; k=$(grep -c -x -F 'suite_aggregate_rc=0 ledger_write_failed=0' "$G/H/linux-suite-ledger.txt") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP aggregate
g=0; k=$(grep -c -E '^nofile_soft_equals_hard_rc=0$' "$G/H/linux-suite-ledger.txt") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP nofile
u=0; python3 "$EVID/tuples.py" linux "$G"/H/biv_subprocess_tests-linux.xml "$G"/H/biv_repo_git_tests-linux.xml "$G"/H/biv_repo_engine_tests-linux.xml "$G"/H/biv_tests-linux.xml "$G"/H/biv_probe_tests-linux.xml > "$G/tuples-linux.txt" || u=$?; [ "$u" -eq 0 ] && [ -s "$G/tuples-linux.txt" ] || STOP linux-tuples
g=0; k=$(grep -c -x -E 'biv_[a-z_]+ linux successes=[0-9]+ failures=0 expectedFailures=0 skips=[0-9]+ xml_sha256=[0-9a-f]{64}' "$G/tuples-linux.txt") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 5 ] || STOP linux-failures
# the tidy invariant: coverage 37/37, and the finding set BYTE-EQUAL to this head's pinned list (no new finding; the landing head's list is empty)
g=0; k=$(grep -c -F 'clang-tidy coverage: 37 results == 37 sources' "$G/H/ctest-linux-H.junit.xml") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP coverage
g=0; grep -E ': error: .*\[' "$G/H/ctest-linux-H.log" > "$G/tidy-raw.txt" || g=$?; [ "$g" -le 1 ] || STOP tidy-grep
s=0; sed 's|^/work/repo/||' "$G/tidy-raw.txt" > "$G/tidy-stripped.txt" || s=$?; [ "$s" -eq 0 ] || STOP tidy-strip
s=0; LC_ALL=C sort -u "$G/tidy-stripped.txt" > "$G/tidy-observed.txt" || s=$?; [ "$s" -eq 0 ] || STOP tidy-sort
c=0; cmp "$G/tidy-expected.txt" "$G/tidy-observed.txt" > "$G/tidy.cmp" 2>&1 || c=$?; [ "$c" -eq 0 ] || STOP tidy-set
x=0; python3 "$EVID/xmlcases.py" ctest-row safety-tidy-analyzer "$G/H/ctest-linux-H.junit.xml" > "$G/tidy-row.txt" || x=$?
if [ "$NT" -eq 0 ]; then [ "$x" -eq 0 ] || STOP tidy-row-not-green; else [ "$x" -eq 5 ] || STOP tidy-row-not-red; fi
# every other ctest row: failed only harness-selftest (R-4.77 data) beside the tidy row; not-run exactly the two skip rows
g=0; grep -o -E '<testcase name="[^"]+" [^>]*status="[a-z]+"' "$G/H/ctest-linux-H.junit.xml" > "$G/ctest-status.raw" || g=$?; [ "$g" -eq 0 ] || STOP status-grep
s=0; sed -E 's/^<testcase name="([^"]+)".*status="([a-z]+)"$/\2 \1/' "$G/ctest-status.raw" > "$G/ctest-status.txt" || s=$?; [ "$s" -eq 0 ] && [ -s "$G/ctest-status.txt" ] || STOP status-rows
o=0; grep -v -x -E 'run [A-Za-z0-9_-]+|fail safety-tidy-analyzer|fail harness-selftest|notrun safety-asan-ubsan|notrun safety-fuzz-smoke' "$G/ctest-status.txt" > "$G/ctest-status.foreign" || o=$?; [ "$o" -eq 1 ] && [ ! -s "$G/ctest-status.foreign" ] || STOP ctest-foreign
g=0; k=$(grep -c -x -E 'notrun safety-asan-ubsan|notrun safety-fuzz-smoke' "$G/ctest-status.txt") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 2 ] || STOP ctest-skip-shape
g=0; k=$(grep -c -x -F 'fail safety-tidy-analyzer' "$G/ctest-status.txt") || g=$?; [ "$g" -le 1 ] || STOP tidy-status-grep
if [ "$NT" -eq 0 ]; then [ "$k" -eq 0 ] || STOP tidy-failed-at-green-head; else [ "$k" -eq 1 ] || STOP tidy-not-failed; fi
x=0; python3 "$EVID/selftest_summary.py" "$G/H/ctest-linux-H.junit.xml" "$G/selftest-H" > "$G/selftest-H.out" || x=$?; [ "$x" -eq 0 ] && [ -s "$G/selftest-H.kv" ] || STOP selftest-summary
c=0; cat -- "$G/H/linux-container.log" "$G/H/phase-R-base.log" "$G/H/phase-R-assets.log" "$G/H/phase-T-transition.log" "$G/H/phase-S-suite.log" "$G/H/ctest-linux-H.log" "$G"/H/*-linux.stderr > "$G/all-logs-linux.txt" || c=$?; [ "$c" -eq 0 ] || STOP logs
g=0; hits=$(grep -c -E 'sk-[A-Za-z0-9]{8,}|-----BEGIN [A-Z ]*PRIVATE KEY|AKIA[0-9A-Z]{16}|ghp_[A-Za-z0-9]{20,}|xox[abprs]-' "$G/all-logs-linux.txt") || g=$?; [ "$g" -le 1 ] && [ "$hits" -eq 0 ] || STOP secret-scan
printf 'headgate label=%s head=%s tidy_expected=%s tidy_findings=%s coverage=37/37 macos_rc0=5 macos_failures=0 container_rc=0 linux_failures=0\n' "$LABEL" "$HX" "$TL" "$NT" > "$G/headgate.txt" || STOP receipt; [ -s "$G/headgate.txt" ] || STOP receipt-empty
printf 'headgate %s OK %s\n' "$LABEL" "$HX"
```

### Task 8c — c10, MUST-H-1: a failed repository row renders its `kind` and `detail`, never null, and the envelope validates against the product's own schema (rev41: Step 5 EXECUTED under impl-14 — `receipts/c10-mutants.rev40.txt`, `verdict=ok` — and Step 6 STOPPED on the canonical Linux build, repaired by Task 8d as c10t; rev40: Steps 0–4 EXECUTED under impl-13, c10 `2291a46`; Step 5 runs rev40's mutant record; rev39; m-3 `../pdc/master/relays/intg-2b-wiring-act/DESIGN-planner-20260926-160359.md` MUST-H-1 with F1–F5; master `PLAN-master-planner-20260926-164725.md`, F4 widened to both doors; the operator's "lighter regate pls", 2026-09-26)

**Why this task exists.** Task 9 completed at H `2893bc53` (impl-12), and m-3's owner byte review of that H returned MUST-REVISE. A url-divergence-refused row is pushed as `repo_row(*entry)` with `kind` and `detail` unset (`open.cpp:1148` at H). `write_open_result` then writes both keys on every `failed` row, as null when unset (`envelope.cpp:414-420`). The schema's `result.anyOf[1].properties.repos.items` is `additionalProperties: false` over twelve properties, neither of them `kind` nor `detail`. So the envelope fails the product's own schema exactly when the consent fail-safe fires. m-3 reproduced it with the harness validator. Master confirmed it at its own bytes and found a second door: the two-argument `repo_row` maps `RepoRestoreOutcome::failed` to `"failed"` without setting either field (`open.cpp:1069-1088`, pushed at `:1143`), and `restore_entry` initializes its row as `failed` (`restore.cpp:491`). Hence F4, the writer-side invariant, is the load-bearing arm. The fix moves H, so m-1's and m-4's no-reds at `2893bc53` go stale: all three owner reviews are retaken at the FINAL head Task 9b writes.

**Files:** `src/core/open/open.cpp`, `src/core/report/envelope.hpp`, `src/core/report/envelope.cpp`, `src/cli/url_consent.hpp`, `src/cli/url_consent.cpp`, `schemas/biv-json-envelope.v1.schema.json`, `harness/selftest/test_envelope.py` (the schema pin only), `tests/test_cli.cpp`, `tests/test_envelope.cpp`, `CMakeLists.txt`. Each is inside the 53-path allowlist; none is under `src/core/repo`, so veto 9 is untouched. ONE new commit, c10, on top of c9; no landed commit is rewritten.

**The behaviour (each cell has a witness below):**
- F1 — the url-divergence-refused row carries `outcome: "failed"` and `kind: "UrlDivergenceEntryRefused"`, A6's sealed wire kind (`to_string(ErrKind::UrlDivergenceEntryRefused)`; A11.4 item 2 leaves it as A6 sealed it).
- F2 — its `detail` is A6 `:537`'s per-entry sentence with the RAW values, exactly `<relpath>: restore failed — <op> would contact <effective> instead of the requested <requested>; approval was not given.` (no leading spaces, no trailing newline; m-3's owner fill of A10.1's silence, moving no normative byte). It reaches the wire through the writer's existing `machine_text` (A8-R2). ONE sentence function serves both carriers: `render_entry_refusal_line` becomes two spaces, that function over `consent_display(...)` values, then `\n`, and the machine detail is the same function over the raw facts, composed in `open.cpp`. Every `facts.(op|repo|requested|effective)` line in `src/cli/url_consent.cpp` still passes through `consent_display(` (Task 9's A8 census, re-run by Task 9b).
- F3 — the schema's row object gains `kind` (string) and `detail` (string), REQUIRED when `outcome` is `"failed"` and absent otherwise (an `allOf` member: `if {properties: {outcome: {const: "failed"}}}` then `required: [kind, detail]` else `not: {anyOf: [{required: [kind]}, {required: [detail]}]}`); `additionalProperties` stays `false`. Same commit as the rendering (A10.1's schema line; R-4.32). `harness/selftest/test_envelope.py`'s pin for the schema moves to c10's blob (`git hash-object`), nothing else in that file.
- F4 — the writer never emits a null `kind` or `detail`: the two `value_null()` branches go, and the two keys are written only from present values. A public predicate `bool failed_rows_complete(const biv::open::OpenReport&)`, declared in `src/core/report/envelope.hpp`, is true iff every `failed` row carries both. Open's result path evaluates it before a report is returned; when it is false, open returns a top-level typed `ErrKind::InternalError` (the exit map's `mid-fail`, exit 4; result null, A11.2's invariant) instead of a report. That closes both doors — the divergence push and the two-argument overload's `failed` mapping — without a reachability argument. `record_open_engine_failure` (which sets both) is untouched.
- Unchanged: the divergence exit (2), `url_divergence_refusals`, the human carrier's bytes, and every other row shape.

**The witnesses (F5).** (w1) The A10 divergence shim test in `tests/test_cli.cpp` (`url_divergence_refusals` at about `:2027`) additionally asserts each refused row's `kind` and `detail` bytes for the fixture's `op`, `effective` and `requested`, and writes its `--json` stdout to `BIV_DIVERGENCE_ENVELOPE_PATH`. That compile definition is set beside `BIV_GENERATED_ENVELOPE_PATH` in `CMakeLists.txt`, with a reset row `divergence_envelope_reset` and a new ctest row `divergence_envelope_conforms` that validates the file with the same `Draft202012Validator` command as `generated_envelope_conforms` (`FIXTURES_REQUIRED` on `biv_tests`'s setup, `RESOURCE_LOCK` on the artifact). (w2) For display-inert values the human line equals two spaces, the machine `detail`, then `\n`. (w3) `tests/test_envelope.cpp`: `failed_rows_complete` is false for a report with a `failed` row lacking `kind`, false for one lacking `detail`, true for a complete one, and the complete report's envelope carries no `null` for either key.

**THE MUTANT RECORD at the c10 head** (block `c10-mutants.sh`; each mutant applied to the working tree only, built, run, recorded in `$EVID/receipts/c10-mutants.rev40.txt` and reverted, the tree proved clean after each; a mutant that does not compile is a STOP; the record ends in ONE `verdict=ok` line written last, and Task 9b reads that line, never the file's mere presence). rev40 (impl-13's STOP `intg-substep2b/IMPL-pair-implementer-20260926-211822.md`): `divergence_envelope_conforms` REQUIRES the fixture `biv_tests` sets up, so when a mutant reddens `biv_tests` CTest reports the consumer `Not Run`, never `Failed`. rev39 demanded a conforms failure under M-H1-PRE that this topology makes impossible. Each mutant is therefore killed by the NAMED witness it reddens: the per-mutant record carries both CTest rows' statuses and the failed Catch2 cases by name. impl-13's rev39 record (`receipts/c10-mutants.txt`, sha256 `4fe1c976…`) and work directory `code/c10-mutants/` stay where they are as the attempt's record. All three GATE:
- M-H1-PRE: `src/core/open/open.cpp` reverted to c9's bytes (the divergence row back to unset fields, the predicate never evaluated). (w1) goes red in `biv_tests` — exactly ONE failed case, `open repos typed refusal continues in encounter order to a clean entry` — and `divergence_envelope_conforms` is `Not Run` by the fixture (recorded, never counted as a kill; under M-H1-PRE the case aborts on the null `kind` before it writes the envelope, so no conformance run could observe it).
- M-H1-SCHEMA: `schemas/biv-json-envelope.v1.schema.json` reverted to c9's bytes. Every case stays green (`biv_tests` `Passed`, zero failed cases), and `divergence_envelope_conforms` alone goes red (`Failed`), because the fixed row now carries two properties c9's schema forbids — the whole-envelope validation's independent kill.
- M-H1-F4: the predicate made constant `true`, as a one-hunk patch the implementer prepares at `$EVID/code/c10-M-H1-F4.patch` touching `src/core/report/envelope.cpp` only (the block refuses any other path). (w3) goes red in `biv_tests` — exactly its TWO cases, `failed row completeness rejects a missing kind` and `failed row completeness rejects a missing detail and complete rows emit no null carriers` — with `divergence_envelope_conforms` `Not Run` by the fixture.

- [ ] **Step 0: the precondition** — HEAD is c9 (`commits.c9.txt`), which is Task 9's FINAL H (`H.txt`); the tree clean; `commits.c10.txt`, `heads/c10`, `receipts/c10-red.txt`, `receipts/c10-mutants.txt` and `code/c10-mutants` all absent.
- [ ] **Step 1: the failing tests first** — write (w1)–(w3) and the CMake rows; build; run the three named cases and the `divergence_envelope_conforms` row; record each as RED at c9's product bytes in `$EVID/receipts/c10-red.txt` (one `case=<name> rc=<n>` line each, `rc` non-zero for all four).
- [ ] **Step 2: F1–F4** — the minimal product change above; nothing outside the Files line.
- [ ] **Step 3: green** — the three cases, `biv_tests` whole, `generated_envelope_conforms`, `divergence_envelope_conforms` and harness-selftest's `test_envelope.py` all green on macOS.
- [ ] **Step 4: the commit** — `git add` the Files line's paths only; `git commit -m "open: MUST-H-1 -- the failed row's kind and detail rendered, never null; the schema admits both iff failed (m-3 160359 F1-F5; master 164725)"`; `git rev-parse HEAD > "$EVID/commits.c10.txt"`; the tree clean.
- [ ] **Step 5: the mutant record** — prepare `$EVID/code/c10-M-H1-F4.patch`, then `bash` the block `c10-mutants.sh` (extracted from this plan by `plan_blocks.py extract`) from the worktree. rev40 (resumption): Steps 0–4 are EXECUTED under impl-13 — c10 `2291a46e7ff70c4c06055c8d0aab9e6709cb134d` at its ten Files-line paths, `receipts/c10-red.txt` (`801bc78e…`) and the patch `code/c10-M-H1-F4.patch` (one file, one hunk) all in place; under the successor token Task 8c RESUMES HERE, with HEAD at c10 and the tree clean, and nothing of Steps 0–4 is re-run or re-written.
- [ ] **Step 6: the head gate** — `bash` the block `headgate.sh` with `c10` (tidy list EMPTY, coverage 37/37, macOS failures 0, the canonical container rc 0, every ctest row but harness-selftest passed): `heads/c10/headgate.txt`. rev41: EXECUTED under impl-14 and STOPPED (`STOP-headgate container`: GCC 13 `-Werror=missing-field-initializers` at `tests/test_envelope.cpp:75` and `:85`, the retained `heads/c10/H/linux-build.log` `6b0c66e5…`); `heads/c10/` is that STOP's record, never modified, and the head gate is taken at c10t (Task 8d).
- [ ] **Step 7: record** — the IMPL return enumerates c10's paths against the Files line (master 042625 (1)). rev41: EXECUTED under impl-14 (its return 231301).

<!-- BLOCK: c10-mutants.sh -->
```bash
# Task 8c — the c10 mutant record (rev40; impl-13's rev39 attempt preserved; m-3 160359 F5, master 164725): run ONCE at the c10 head, before its head gate; usage  bash <this block>  from the worktree with EVID exported
set -o pipefail
STOP() { printf 'STOP-c10-mutants %s line=%s\n' "$1" "${BASH_LINENO[0]}" >&2; exit 1; }
[ -n "${EVID-}" ] && [ -d "$EVID/receipts" ] && [ -d "$EVID/code" ] || STOP env
z=0; C10=$(cat "$EVID/commits.c10.txt") || z=$?; [ "$z" -eq 0 ] && [ -n "$C10" ] && [ "$(git rev-parse HEAD)" = "$C10" ] || STOP not-at-c10
z=0; C9=$(cat "$EVID/commits.c9.txt") || z=$?; [ "$z" -eq 0 ] && [ -n "$C9" ] && [ "$(git rev-parse HEAD~1)" = "$C9" ] || STOP parent-not-c9
git diff --cached --quiet && git diff HEAD --quiet || STOP dirty
# impl-13's rev39 attempt stays exactly where it is: its record (the M-H1-PRE assertion rev39 could not meet) and its work directory
Q=$EVID/receipts/c10-mutants.txt; [ -f "$Q" ] && [ ! -L "$Q" ] || STOP rev39-record-absent
h=0; s=$(shasum -a 256 "$Q" | cut -d' ' -f1) || h=$?; [ "$h" -eq 0 ] && [ "$s" = 4fe1c9768bc4e6305611cf371c3259ca6d2efcfc16990f2339fee60724145afc ] || STOP rev39-record-moved
[ -d "$EVID/code/c10-mutants" ] && [ ! -L "$EVID/code/c10-mutants" ] || STOP rev39-work-absent
O=$EVID/receipts/c10-mutants.rev40.txt; [ ! -e "$O" ] && [ ! -L "$O" ] || STOP record-exists
P=$EVID/code/c10-M-H1-F4.patch; [ -f "$P" ] && [ -s "$P" ] && [ ! -L "$P" ] || STOP f4-patch-absent
g=0; k=$(grep -c -E '^\+\+\+ ' "$P") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP f4-patch-files; g=0; k=$(grep -c -x -F '+++ b/src/core/report/envelope.cpp' "$P") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP f4-patch-path
g=0; k=$(grep -c -E '^@@ ' "$P") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP f4-patch-hunks
a=0; git apply --check "$P" || a=$?; [ "$a" -eq 0 ] || STOP f4-patch-applies
M=$EVID/code/c10-mutants.rev40; [ ! -e "$M" ] && [ ! -L "$M" ] || STOP work-exists; m=0; mkdir "$M" || m=$?; [ "$m" -eq 0 ] || STOP work-mkdir
# the named witnesses at c10 (w1, w3), by their TEST_CASE names; divergence_envelope_conforms REQUIRES the fixture biv_tests sets up, so CTest runs it only when biv_tests passes
W1='open repos typed refusal continues in encounter order to a clean entry'
W3A='failed row completeness rejects a missing kind'
W3B='failed row completeness rejects a missing detail and complete rows emit no null carriers'
status() { local log=$1 name=$2 n p f r; g=0; p=$(grep -c -E "Test +#[0-9]+: $name \.+ +Passed " "$log") || g=$?; [ "$g" -le 1 ] || STOP "status-grep-$name"
  g=0; f=$(grep -c -E "Test +#[0-9]+: $name \.+\*\*\*Failed " "$log") || g=$?; [ "$g" -le 1 ] || STOP "status-grep-$name"
  g=0; r=$(grep -c -E "Test +#[0-9]+: $name \.+\*\*\*Not Run " "$log") || g=$?; [ "$g" -le 1 ] || STOP "status-grep-$name"
  n=$((p + f + r)); [ "$n" -eq 1 ] || STOP "status-count-$name-$n"
  if [ "$p" -eq 1 ]; then printf passed; elif [ "$f" -eq 1 ]; then printf failed; else printf notrun; fi; }
run() { local name=$1 bs ds
  b=0; cmake --build --preset ci-macos > "$M/$name.build.log" 2>&1 || b=$?; [ "$b" -eq 0 ] || { git checkout -q HEAD -- .; STOP "build-$name"; }
  x=0; ./build/ci-macos/biv_tests -r xml > "$M/$name.xml" 2> "$M/$name.stderr" || x=$?
  f=0; python3 -c 'import sys, xml.etree.ElementTree as E
r = E.parse(sys.argv[1]).getroot()
for t in r.iter("TestCase"):
    o = t.find("OverallResult")
    if o is not None and o.get("success") == "false":
        print(t.get("name"))' "$M/$name.xml" > "$M/$name.failed-cases.txt" || f=$?
  [ "$f" -eq 0 ] || { git checkout -q HEAD -- .; STOP "cases-$name"; }
  y=0; ctest --preset ci-macos -R '^(generated_envelope_reset|divergence_envelope_reset|biv_tests|divergence_envelope_conforms)$' > "$M/$name.ctest.log" 2>&1 || y=$?
  bs=$(status "$M/$name.ctest.log" biv_tests) || { git checkout -q HEAD -- .; exit 1; }
  ds=$(status "$M/$name.ctest.log" divergence_envelope_conforms) || { git checkout -q HEAD -- .; exit 1; }
  g=0; nf=$(grep -c . "$M/$name.failed-cases.txt") || g=$?; [ "$g" -le 1 ] || { git checkout -q HEAD -- .; STOP "cases-count-$name"; }
  c=0; git checkout -q HEAD -- . || c=$?; [ "$c" -eq 0 ] || STOP "revert-$name"; git diff --cached --quiet && git diff HEAD --quiet || STOP "not-clean-after-$name"
  printf 'mutant=%s gating=yes case_rc=%s ctest_rc=%s biv_tests=%s conforms=%s failed_cases=%s\n' "$name" "$x" "$y" "$bs" "$ds" "$nf" >> "$O" || STOP record-write; }
has() { g=0; k=$(grep -c -x -F -- "$2" "$M/$1.failed-cases.txt") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP "$3"; }
g=0; git checkout -q "$C9" -- src/core/open/open.cpp || g=$?; [ "$g" -eq 0 ] || STOP apply-M-H1-PRE
run M-H1-PRE
g=0; git checkout -q "$C9" -- schemas/biv-json-envelope.v1.schema.json || g=$?; [ "$g" -eq 0 ] || STOP apply-M-H1-SCHEMA
run M-H1-SCHEMA
a=0; git apply "$P" || a=$?; [ "$a" -eq 0 ] || STOP apply-M-H1-F4
run M-H1-F4
b=0; cmake --build --preset ci-macos > "$M/rebuild.log" 2>&1 || b=$?; [ "$b" -eq 0 ] || STOP rebuild
git diff --cached --quiet && git diff HEAD --quiet || STOP dirty-after
g=0; k=$(grep -c -E '^mutant=M-H1-(PRE|SCHEMA|F4) gating=yes ' "$O") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 3 ] || STOP record-rows
# M-H1-PRE: killed by (w1) alone inside biv_tests; the conforms consumer is NOT RUN by the fixture, never counted as a kill
g=0; k=$(grep -c -E '^mutant=M-H1-PRE gating=yes case_rc=[1-9][0-9]* ctest_rc=[1-9][0-9]* biv_tests=failed conforms=notrun failed_cases=1$' "$O") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP survived-M-H1-PRE
has M-H1-PRE "$W1" M-H1-PRE-not-w1
# M-H1-SCHEMA: every case green, and the whole-envelope validation (the conforms row) alone red
g=0; k=$(grep -c -E '^mutant=M-H1-SCHEMA gating=yes case_rc=0 ctest_rc=[1-9][0-9]* biv_tests=passed conforms=failed failed_cases=0$' "$O") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP survived-M-H1-SCHEMA
# M-H1-F4: killed by (w3)'s two cases alone inside biv_tests; the conforms consumer NOT RUN
g=0; k=$(grep -c -E '^mutant=M-H1-F4 gating=yes case_rc=[1-9][0-9]* ctest_rc=[1-9][0-9]* biv_tests=failed conforms=notrun failed_cases=2$' "$O") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP survived-M-H1-F4
has M-H1-F4 "$W3A" M-H1-F4-not-w3a; has M-H1-F4 "$W3B" M-H1-F4-not-w3b
printf 'verdict=ok\n' >> "$O" || STOP verdict-write
g=0; k=$(grep -c -x -F 'verdict=ok' "$O") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP verdict-read
printf 'c10 mutants OK (%s)\n' "$O"
```

### Task 8d — c10t: the two c10 failed-row test initializers name every `RepoOutcomeRow` member, so the canonical Linux GCC build compiles (rev41; impl-14's STOP `intg-substep2b/IMPL-pair-implementer-20260926-231301.md`)

**Why this task exists.** impl-14 ran Task 8c Step 5 green (`receipts/c10-mutants.rev40.txt`, `verdict=ok`); Step 6's one head gate at c10 then STOPped in the canonical Linux container. GCC 13 rejects c10's two new `report.repos.push_back({...})` rows in `tests/test_envelope.cpp` (`:75`, `:85`) under `-Wall -Wextra -Werror` as `-Werror=missing-field-initializers`: each names five of `RepoOutcomeRow`'s fourteen members, and Apple clang accepts that. It is the class c8L (`c47eb32`) already repaired for the 2b structs, re-introduced by c10's new rows: Task 8c checked c10 green on macOS only (Step 3) and met the canonical Linux toolchain first at its head gate. The census is complete, not a stopped build's first page: the retained log's error lines are exactly those 18 (the nine trailing members at each row), and a scout at c10 plus the repair built and passed the WHOLE canonical container — tidy clean at 37/37, only harness-selftest red, the selftest population EQUAL to Task 9's — with macOS tuples equal to c10's and the mutant record reproducing impl-14's three rows (`results/c10t-scout-20260926/scout-summary.txt` at `dbea9b75`).

**Files:** `tests/test_envelope.cpp` only (inside c10's Files line and the 53-path allowlist). ONE new commit, c10t, on top of c10; c10 is not amended; no product byte moves; nothing under `src/core/repo`, so veto 9 is untouched.

**The repair (repair-13, pinned).** Each of the two rows names the nine trailing members explicitly, as the rows at `tests/test_envelope.cpp:979` already do: `.sha = std::nullopt, .branch = std::nullopt, .capture_mode = std::nullopt, .remotes = {}, .bundle_path = std::nullopt, .reconstruct = std::nullopt, .local_refs = {}, .advisories = {}, .shallow_boundary = std::nullopt` — the values the omitted members already took, so neither case's meaning moves. The patch is `results/c10t-scout-20260926/repair-13-c10t-initializers.patch` at `dbea9b75` (sha256 `0508c70f…`, +8/−2); the block applies it verbatim and pins the commit's TREE to the scout's (`36331eb0…`).

**Outputs:** `receipts/c10t-red.txt` (the canonical RED, from impl-14's retained build log), `commits.c10t.txt`, `receipts/c10t-mutants.txt` with `code/c10t-mutants/` (the mutant record re-taken at c10t, ending in ONE `verdict=ok`), and `heads/c10t/` (the head gate). `heads/c10/` stays exactly as impl-14 left it: the STOP's record.

- [ ] **Steps 0–4: the block `c10t.sh`** — `bash` it ONCE from the worktree at the c10 head with `EVID` exported. It checks the preconditions: HEAD c10, parent c9, the tree clean, Task 8c's rev40 `verdict=ok`, and `heads/c10/` holding the STOP by content (container rc 1, no `headgate.txt`, the retained build log `6b0c66e5…`). It writes the RED receipt from that log: exactly the 18 lines, nothing foreign. It applies repair-13 (sha-checked; +8/−2 on the one path) and proves it green on macOS: the build, `biv_tests` whole with (w3)'s two cases passed, and the rows `generated_envelope_conforms` and `divergence_envelope_conforms` passed. It then commits with the exact message, pins the commit's tree to the scout's, and writes `commits.c10t.txt`. Any STOP before the commit restores the working tree.
- [ ] **Step 5: the mutant record at c10t** — `bash` the block `c10t-mutants.sh`: Task 8c's three gating mutants with the same named witnesses and verdict lines (M-H1-PRE and M-H1-SCHEMA restore their files from c9; M-H1-F4 applies `code/c10-M-H1-F4.patch`), recorded in `receipts/c10t-mutants.txt` and ending in ONE `verdict=ok`. Task 8c's rev40 record and work directory stay where they are, the record pinned by digest.
- [ ] **Step 6: the head gate** — `bash` the block `headgate.sh` with `c10t` (tidy list EMPTY, coverage 37/37, macOS failures 0, the canonical container rc 0, every ctest row but harness-selftest passed): `heads/c10t/headgate.txt`.
- [ ] **Step 7: record** — the IMPL return enumerates c10t's one path against this Files line (master 042625 (1)).

<!-- BLOCK: c10t.sh -->
```bash
# Task 8d — c10t (rev41; impl-14's STOP 231301): the two c10 failed-row test initializers name every RepoOutcomeRow member (repair-13, pinned); run ONCE at the c10 head; usage  bash <this block>  from the worktree with EVID exported
set -o pipefail
STOP() { printf 'STOP-c10t %s line=%s\n' "$1" "${BASH_LINENO[0]}" >&2; exit 1; }
MAIN=/Users/jack/Programming/bivpak; CR=dbea9b75bcbe0c7ee3f2b9096ef21af1678b5746; RP=docs/sprints/2026-08-27-intg-consent-fabric/results/c10t-scout-20260926/repair-13-c10t-initializers.patch
RS=0508c70fd9ef76a7c91238e135b42512dfc4c669bf77c837610e1cd1b2874472; LS=6b0c66e5f2882bd7eaf20b6a2dbce194b804c190bc573297d5edabd037e74404; TREE=36331eb01cc53efcf8dfafd803948a2cc0f765af
[ -n "${EVID-}" ] && [ -d "$EVID" ] && [ ! -L "$EVID" ] && [ -d "$EVID/receipts" ] && [ -d "$EVID/work" ] || STOP env
z=0; C10=$(cat "$EVID/commits.c10.txt") || z=$?; [ "$z" -eq 0 ] && [ -n "$C10" ] && [ "$(git rev-parse HEAD)" = "$C10" ] || STOP not-at-c10
z=0; C9=$(cat "$EVID/commits.c9.txt") || z=$?; [ "$z" -eq 0 ] && [ -n "$C9" ] && [ "$(git rev-parse HEAD~1)" = "$C9" ] || STOP parent-not-c9
git diff --cached --quiet && git diff HEAD --quiet || STOP dirty
u=$(git ls-files --others --exclude-standard); r=$?; [ "$r" -eq 0 ] && [ -z "$u" ] || STOP untracked
# Task 8c's standing record: the rev40 mutant verdict, and the c10 head gate's STOP kept exactly as impl-14 left it (container rc 1, no headgate.txt, the build log by digest)
g=0; k=$(grep -c -x -F 'verdict=ok' "$EVID/receipts/c10-mutants.rev40.txt") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP c10-mutants-verdict
[ -d "$EVID/heads/c10" ] && [ ! -L "$EVID/heads/c10" ] && [ "$(cat "$EVID/heads/c10/linux-container.rc")" = 1 ] && [ ! -e "$EVID/heads/c10/headgate.txt" ] && [ ! -L "$EVID/heads/c10/headgate.txt" ] || STOP c10-stop-record
L=$EVID/heads/c10/H/linux-build.log; [ -f "$L" ] && [ ! -L "$L" ] || STOP c10-build-log
h=0; s=$(shasum -a 256 "$L" | cut -d' ' -f1) || h=$?; [ "$h" -eq 0 ] && [ "$s" = "$LS" ] || STOP c10-build-log-sha
for x in commits.c10t.txt receipts/c10t-red.txt heads/c10t receipts/c10t-mutants.txt code/c10t-mutants work/c10t-red.errors work/c10t-repair-13.patch; do [ ! -e "$EVID/$x" ] && [ ! -L "$EVID/$x" ] || STOP "exists-$x"; done
# (1) the RED is the canonical build's own: every error line of the retained log is one of the 18 — tests/test_envelope.cpp:75 and :85, the nine trailing RepoOutcomeRow members at each — and none is foreign
g=0; grep -E ': error: ' "$L" > "$EVID/work/c10t-red.errors" || g=$?; [ "$g" -eq 0 ] || STOP red-grep
MEM='sha|branch|capture_mode|remotes|bundle_path|reconstruct|local_refs|advisories|shallow_boundary'
g=0; k=$(grep -c -x -E "/work/repo/tests/test_envelope\.cpp:(75|85):25: error: missing initializer for member 'biv::open::RepoOutcomeRow::($MEM)' \[-Werror=missing-field-initializers\]" "$EVID/work/c10t-red.errors") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 18 ] || STOP red-shape
a=0; n=$(awk 'END { print NR }' "$EVID/work/c10t-red.errors") || a=$?; [ "$a" -eq 0 ] && [ "$n" -eq 18 ] || STOP red-foreign
s=0; d=$(sed -E 's/^[^:]+:([0-9]+):25: .*::([a-z_]+).*$/\1 \2/' "$EVID/work/c10t-red.errors" | LC_ALL=C sort -u | awk 'END { print NR }') || s=$?; [ "$s" -eq 0 ] && [ "$d" -eq 18 ] || STOP red-distinct
w=0; printf 'log=heads/c10/H/linux-build.log sha256=%s\nerrors=18 at=tests/test_envelope.cpp:75,85 members=9-each distinct=18 foreign=0\n' "$LS" > "$EVID/receipts/c10t-red.txt" || w=$?; [ "$w" -eq 0 ] && [ -s "$EVID/receipts/c10t-red.txt" ] || STOP red-receipt
# (2) repair-13, the pinned patch, applied to the working tree: exactly tests/test_envelope.cpp, +8/-2
PT=$EVID/work/c10t-repair-13.patch
g=0; git -C "$MAIN" show "${CR}:${RP}" > "$PT" || g=$?; [ "$g" -eq 0 ] && [ -s "$PT" ] || STOP patch-read
h=0; s=$(shasum -a 256 "$PT" | cut -d' ' -f1) || h=$?; [ "$h" -eq 0 ] && [ "$s" = "$RS" ] || STOP patch-sha
a=0; git apply --check "$PT" || a=$?; [ "$a" -eq 0 ] || STOP patch-check
a=0; git apply "$PT" || a=$?; [ "$a" -eq 0 ] || { git checkout -q HEAD -- .; STOP patch-apply; }
n=0; ns=$(git diff --numstat) || n=$?; [ "$n" -eq 0 ] && [ "$ns" = "$(printf '8\t2\ttests/test_envelope.cpp')" ] || { git checkout -q HEAD -- .; STOP patch-numstat; }
# (3) green on macOS: the build; biv_tests whole, with (w3)'s two cases passed; the envelope rows passed
b=0; cmake --build --preset ci-macos > "$EVID/work/c10t-build-macos.log" 2>&1 || b=$?; [ "$b" -eq 0 ] || { git checkout -q HEAD -- .; STOP build; }
x=0; ./build/ci-macos/biv_tests -r xml > "$EVID/work/c10t-biv_tests.xml" 2> "$EVID/work/c10t-biv_tests.stderr" || x=$?; [ "$x" -eq 0 ] || { git checkout -q HEAD -- .; STOP biv-tests; }
f=0; python3 - "$EVID/work/c10t-biv_tests.xml" > "$EVID/work/c10t-w3.txt" <<'PY' || f=$?
import sys, xml.etree.ElementTree as E
want = {"failed row completeness rejects a missing kind", "failed row completeness rejects a missing detail and complete rows emit no null carriers"}
seen = {}
for t in E.parse(sys.argv[1]).getroot().iter("TestCase"):
    if t.get("name") in want:
        o = t.find("OverallResult")
        seen[t.get("name")] = None if o is None else o.get("success")
for n in sorted(want):
    print("case=%r success=%s" % (n, seen.get(n)))
sys.exit(0 if all(seen.get(n) == "true" for n in want) else 5)
PY
[ "$f" -eq 0 ] || { git checkout -q HEAD -- .; STOP w3-cases; }
y=0; ctest --preset ci-macos -R '^(generated_envelope_reset|divergence_envelope_reset|biv_tests|generated_envelope_conforms|divergence_envelope_conforms)$' > "$EVID/work/c10t-ctest.log" 2>&1 || y=$?; [ "$y" -eq 0 ] || { git checkout -q HEAD -- .; STOP envelope-rows; }
for row in biv_tests generated_envelope_conforms divergence_envelope_conforms; do g=0; k=$(grep -c -E "Test +#[0-9]+: $row \.+ +Passed " "$EVID/work/c10t-ctest.log") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || { git checkout -q HEAD -- .; STOP "row-$row"; }; done
# (4) the commit: the one path staged, its tree the scout's BEFORE the commit (git write-tree), the exact message; its parent c10; the tree clean after
g=0; git add -- tests/test_envelope.cpp || g=$?; [ "$g" -eq 0 ] || { git reset -q; git checkout -q HEAD -- .; STOP stage; }
g=0; IT=$(git write-tree) || g=$?; [ "$g" -eq 0 ] && [ "$IT" = "$TREE" ] || { git reset -q; git checkout -q HEAD -- .; STOP index-tree; }
g=0; git commit -q -m "test: name every RepoOutcomeRow member in c10's two failed-row initializers (Linux GCC -Werror=missing-field-initializers) -- c10t, test-only (impl-14 231301; repair-13)" || g=$?; [ "$g" -eq 0 ] || STOP commit
[ "$(git rev-parse HEAD~1)" = "$C10" ] || STOP commit-parent
[ "$(git rev-parse 'HEAD^{tree}')" = "$TREE" ] || STOP commit-tree
g=0; P1=$(git diff-tree --no-commit-id --name-only -r HEAD) || g=$?; [ "$g" -eq 0 ] && [ "$P1" = tests/test_envelope.cpp ] || STOP commit-paths
git diff --cached --quiet && git diff HEAD --quiet || STOP dirty-after
u=$(git ls-files --others --exclude-standard); r=$?; [ "$r" -eq 0 ] && [ -z "$u" ] || STOP untracked-after
w=0; git rev-parse HEAD > "$EVID/commits.c10t.txt" || w=$?; [ "$w" -eq 0 ] && [ -s "$EVID/commits.c10t.txt" ] || STOP w-commit
printf 'c10t OK %s\n' "$(cat "$EVID/commits.c10t.txt")"
```

<!-- BLOCK: c10t-mutants.sh -->
```bash
# Task 8d — the c10t mutant record (rev41; Task 8c's rev40 record preserved; m-3 160359 F5 and its F5_M_H1_PRE accept 222938, master 164725): run ONCE at the c10t head, before its head gate; usage  bash <this block>  from the worktree with EVID exported
set -o pipefail
STOP() { printf 'STOP-c10t-mutants %s line=%s\n' "$1" "${BASH_LINENO[0]}" >&2; exit 1; }
[ -n "${EVID-}" ] && [ -d "$EVID/receipts" ] && [ -d "$EVID/code" ] || STOP env
z=0; C10T=$(cat "$EVID/commits.c10t.txt") || z=$?; [ "$z" -eq 0 ] && [ -n "$C10T" ] && [ "$(git rev-parse HEAD)" = "$C10T" ] || STOP not-at-c10t
z=0; C10=$(cat "$EVID/commits.c10.txt") || z=$?; [ "$z" -eq 0 ] && [ -n "$C10" ] && [ "$(git rev-parse HEAD~1)" = "$C10" ] || STOP parent-not-c10
z=0; C9=$(cat "$EVID/commits.c9.txt") || z=$?; [ "$z" -eq 0 ] && [ -n "$C9" ] && [ "$(git rev-parse HEAD~2)" = "$C9" ] || STOP grandparent-not-c9
git diff --cached --quiet && git diff HEAD --quiet || STOP dirty
# Task 8c's rev40 record (verdict=ok at c10, impl-14) stays exactly where it is, with its work directory
Q=$EVID/receipts/c10-mutants.rev40.txt; [ -f "$Q" ] && [ ! -L "$Q" ] || STOP rev40-record-absent
h=0; s=$(shasum -a 256 "$Q" | cut -d' ' -f1) || h=$?; [ "$h" -eq 0 ] && [ "$s" = 725ee7fd1bc7ea13a99aa457713a899e5f5cb7df71e83fb7ed5c29d59b2c67bf ] || STOP rev40-record-moved
[ -d "$EVID/code/c10-mutants.rev40" ] && [ ! -L "$EVID/code/c10-mutants.rev40" ] || STOP rev40-work-absent
O=$EVID/receipts/c10t-mutants.txt; [ ! -e "$O" ] && [ ! -L "$O" ] || STOP record-exists
P=$EVID/code/c10-M-H1-F4.patch; [ -f "$P" ] && [ -s "$P" ] && [ ! -L "$P" ] || STOP f4-patch-absent
g=0; k=$(grep -c -E '^\+\+\+ ' "$P") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP f4-patch-files; g=0; k=$(grep -c -x -F '+++ b/src/core/report/envelope.cpp' "$P") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP f4-patch-path
g=0; k=$(grep -c -E '^@@ ' "$P") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP f4-patch-hunks
a=0; git apply --check "$P" || a=$?; [ "$a" -eq 0 ] || STOP f4-patch-applies
M=$EVID/code/c10t-mutants; [ ! -e "$M" ] && [ ! -L "$M" ] || STOP work-exists; m=0; mkdir "$M" || m=$?; [ "$m" -eq 0 ] || STOP work-mkdir
# the named witnesses at c10t (w1, w3), by their TEST_CASE names; divergence_envelope_conforms REQUIRES the fixture biv_tests sets up, so CTest runs it only when biv_tests passes
W1='open repos typed refusal continues in encounter order to a clean entry'
W3A='failed row completeness rejects a missing kind'
W3B='failed row completeness rejects a missing detail and complete rows emit no null carriers'
status() { local log=$1 name=$2 n p f r; g=0; p=$(grep -c -E "Test +#[0-9]+: $name \.+ +Passed " "$log") || g=$?; [ "$g" -le 1 ] || STOP "status-grep-$name"
  g=0; f=$(grep -c -E "Test +#[0-9]+: $name \.+\*\*\*Failed " "$log") || g=$?; [ "$g" -le 1 ] || STOP "status-grep-$name"
  g=0; r=$(grep -c -E "Test +#[0-9]+: $name \.+\*\*\*Not Run " "$log") || g=$?; [ "$g" -le 1 ] || STOP "status-grep-$name"
  n=$((p + f + r)); [ "$n" -eq 1 ] || STOP "status-count-$name-$n"
  if [ "$p" -eq 1 ]; then printf passed; elif [ "$f" -eq 1 ]; then printf failed; else printf notrun; fi; }
run() { local name=$1 bs ds
  b=0; cmake --build --preset ci-macos > "$M/$name.build.log" 2>&1 || b=$?; [ "$b" -eq 0 ] || { git checkout -q HEAD -- .; STOP "build-$name"; }
  x=0; ./build/ci-macos/biv_tests -r xml > "$M/$name.xml" 2> "$M/$name.stderr" || x=$?
  f=0; python3 -c 'import sys, xml.etree.ElementTree as E
r = E.parse(sys.argv[1]).getroot()
for t in r.iter("TestCase"):
    o = t.find("OverallResult")
    if o is not None and o.get("success") == "false":
        print(t.get("name"))' "$M/$name.xml" > "$M/$name.failed-cases.txt" || f=$?
  [ "$f" -eq 0 ] || { git checkout -q HEAD -- .; STOP "cases-$name"; }
  y=0; ctest --preset ci-macos -R '^(generated_envelope_reset|divergence_envelope_reset|biv_tests|divergence_envelope_conforms)$' > "$M/$name.ctest.log" 2>&1 || y=$?
  bs=$(status "$M/$name.ctest.log" biv_tests) || { git checkout -q HEAD -- .; exit 1; }
  ds=$(status "$M/$name.ctest.log" divergence_envelope_conforms) || { git checkout -q HEAD -- .; exit 1; }
  g=0; nf=$(grep -c . "$M/$name.failed-cases.txt") || g=$?; [ "$g" -le 1 ] || { git checkout -q HEAD -- .; STOP "cases-count-$name"; }
  c=0; git checkout -q HEAD -- . || c=$?; [ "$c" -eq 0 ] || STOP "revert-$name"; git diff --cached --quiet && git diff HEAD --quiet || STOP "not-clean-after-$name"
  printf 'mutant=%s gating=yes case_rc=%s ctest_rc=%s biv_tests=%s conforms=%s failed_cases=%s\n' "$name" "$x" "$y" "$bs" "$ds" "$nf" >> "$O" || STOP record-write; }
has() { g=0; k=$(grep -c -x -F -- "$2" "$M/$1.failed-cases.txt") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP "$3"; }
g=0; git checkout -q "$C9" -- src/core/open/open.cpp || g=$?; [ "$g" -eq 0 ] || STOP apply-M-H1-PRE
run M-H1-PRE
g=0; git checkout -q "$C9" -- schemas/biv-json-envelope.v1.schema.json || g=$?; [ "$g" -eq 0 ] || STOP apply-M-H1-SCHEMA
run M-H1-SCHEMA
a=0; git apply "$P" || a=$?; [ "$a" -eq 0 ] || STOP apply-M-H1-F4
run M-H1-F4
b=0; cmake --build --preset ci-macos > "$M/rebuild.log" 2>&1 || b=$?; [ "$b" -eq 0 ] || STOP rebuild
git diff --cached --quiet && git diff HEAD --quiet || STOP dirty-after
g=0; k=$(grep -c -E '^mutant=M-H1-(PRE|SCHEMA|F4) gating=yes ' "$O") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 3 ] || STOP record-rows
# M-H1-PRE: killed by (w1) alone inside biv_tests; the conforms consumer is NOT RUN by the fixture, never counted as a kill
g=0; k=$(grep -c -E '^mutant=M-H1-PRE gating=yes case_rc=[1-9][0-9]* ctest_rc=[1-9][0-9]* biv_tests=failed conforms=notrun failed_cases=1$' "$O") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP survived-M-H1-PRE
has M-H1-PRE "$W1" M-H1-PRE-not-w1
# M-H1-SCHEMA: every case green, and the whole-envelope validation (the conforms row) alone red
g=0; k=$(grep -c -E '^mutant=M-H1-SCHEMA gating=yes case_rc=0 ctest_rc=[1-9][0-9]* biv_tests=passed conforms=failed failed_cases=0$' "$O") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP survived-M-H1-SCHEMA
# M-H1-F4: killed by (w3)'s two cases alone inside biv_tests; the conforms consumer NOT RUN
g=0; k=$(grep -c -E '^mutant=M-H1-F4 gating=yes case_rc=[1-9][0-9]* ctest_rc=[1-9][0-9]* biv_tests=failed conforms=notrun failed_cases=2$' "$O") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP survived-M-H1-F4
has M-H1-F4 "$W3A" M-H1-F4-not-w3a; has M-H1-F4 "$W3B" M-H1-F4-not-w3b
printf 'verdict=ok\n' >> "$O" || STOP verdict-write
g=0; k=$(grep -c -x -F 'verdict=ok' "$O") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP verdict-read
printf 'c10t mutants OK (%s)\n' "$O"
```

### Task 9 — (EXECUTED under impl-12 at H `2893bc53`; rev39 re-gates the c10 head in Task 9b) the gates at H0, both platforms; the companion count-cell commit INSIDE the runner; the FINAL H written last (E2/E5 + closure; veto 9; the type-scoped RepoEntry census; the C-2 hunk; the A8 / predicate / hook censuses; the count gate; the Linux parity leg for H0 and B; the E3 Linux witness; the harness-e2 receipts; the harness-selftest bar and, rev33, the 015244 series ALWAYS; the c8T head first; an earlier attempt preserved first; tidy GREEN at H0)

- [ ] **Step 0 (rev33, FIRST): the c8T head, the Task 8b gates, then the preservation of an earlier attempt** — before any write the runner requires HEAD to be the c8T head and every Task 8b receipt present (`[ -s "$EVID/commits.c8T.txt" ] && [ "$(git rev-parse HEAD)" = "$(cat "$EVID/commits.c8T.txt")" ] || STOP`, then the three head gates and the two mutant records). Then, because this runner writes `$EVID/H/` with `>` and `>>` and `H0.txt` / `helpers.verify-9.txt` at the home's root, an EARLIER attempt's outputs are moved out of the way first (master 215035 R3(iii)): when `H0.txt` exists, it must be one `H0=<40-hex>` line beside a real `H/` directory and a real `helpers.verify-9.txt`; rev36 (impl-11's STOP `intg-substep2b/IMPL-pair-implementer-20260925-130242.md`): the attempt also owns the B Linux leg it wrote into `B/` beside Task 0's fifteen macOS records — `BLEG` lists every `B/` entry outside those fifteen (`biv_{probe,repo_engine,repo_git,subprocess}_tests-macos.{stderr,xml}`, `biv_tests-macos.{stderr,xml}`, `build-B.log`, `configure-B.log`, `run-rcs-macos.txt`, `skipset-macos.txt`, `tuples-macos.txt` — the names Task 0's runner writes; all fifteen must be present as regular files, else a STOP) into the scratch `work/B-leg.names`, the only write before the preservation, and the list travels in the stage as `B-leg.names`; the three and the B leg are recorded by a manifest (type, mode, size and sha256 of every entry, recursively, symlinks by target), renamed one by one into a fresh `mktemp -d` stage inside a confined `$EVID/attempts` (a real directory whose physical path is the home's own, on the home's device, as are `H/` and `B/`) — the B leg into the stage's `B/` — the stage's manifest must equal the recorded one, and ONE rename publishes the stage as `attempts/task9-H0-<first seven of that H0>` (impl-10's → `task9-H0-a83657e`, the name master gave; impl-11's → `task9-H0-99136ca`, with its 36-file B leg), re-verified after; then a fresh empty `H/` is made and `H/preserved-attempt.txt` names the attempt, the manifest's digest and row count, and the B-leg file count. A fault at any rename or verification before the publish renames everything back and proves the originals byte-identical against the recorded manifest before it stops; the stage directory stays as the fault's record. When `H0.txt` is absent, the B leg must be empty, `helpers.verify-9.txt` absent and `H/` absent or empty (anything else is an unrecognized earlier state — a STOP, routed up). An earlier attempt's `series/`, `H9/`, `H.txt` or `commits.c9.txt` is a STOP too (rev38: the two names joined; none exists in this home). rev38 (MUST-2B-52): before the first write the runner proves `work/` and `B/` physically the home's own and finds NO symlink directly under the home, `work/` or `B/`, so no fixed name it writes with `>` can be redirected outside the home. After either branch `B/` holds exactly Task 0's fifteen (`BLEG` empty) or the runner STOPs, so the B leg this run writes starts empty. Nothing is copied or deleted; every runners directory (`s2b-runners-aY2Suc` included) is untouched; the produced inputs (`llvm-manifest*.txt`, `observer-unset-names.txt`) stay pinned where they are.
- [ ] **Step 0: the runner's two inputs, then the runner controls (must-be-NO for every guard this runner relies on)** — THE INPUTS (rev29; the impl-8 STOP `intg-substep2b/IMPL-pair-implementer-20260924-072544.md`: no earlier task ever produced them — rev1 carried the consumer from the R-4.49/R-4.50 runners without their Task 0 producers): after the clean-status receipt and B's macOS tuples, the runner PRODUCES `$EVID/llvm-manifest.txt` (with its source slice `llvm-manifest-source.txt`) from `$EVID/B-workflow.yml` — first proven byte-equal to B's `.github/workflows/s2-harness.yml` blob — by the R-4.50 plan's own producer line (lines 167–174, the ten-space indent stripped, eight lines, the `.deb` row form), and `$EVID/observer-unset-names.txt` from `CREDENTIAL_ENV_NAMES` in `harness/bivharness/e3.py` at the run head by the R-4.50 plan's own derivation (the worktree's `.venv-harness` interpreter, no bytecode written) and its form check. Each file is produced ONLY when absent and is digest-PINNED either way, so a later successor re-run neither overwrites evidence nor re-derives it: the source slice `53bbdd42f32e6685df24d1c11314bfc3b47ceda0a06689458c93dd8a42d8ad5b`, the manifest `22724f783d4dc47ce780841098a3536b29a490dbc3fdb57830087a8f270e7ad7`, the names `e12d5d0af265ea8faf41dadc1e3af02610365ac25c40a228714b0e72f2a612f3` (three names) — each MEASURED at this seat before this revision (the manifest and the names byte-equal to the R-4.50 archive's `token-11-6fNsQJ` copies; `e3.py` untouched on B..a83657e); a half-present manifest pair STOPs; the worktree's status is re-proved clean after the derivation (`$EVID/H/status-inputs.txt`). The macOS observation is NOT run under an observer environment, as at B: Task 0's ambient B observation reproduced every pinned macOS cell (`cellgate.py` UNCHANGED on all five binaries, the three expected skips the same set), and the names file feeds the Linux container's absence proof. THE CONTROLS: in subshells: `PIPEOK` on `false | cat` exits nonzero (`( set -o pipefail; false | cat; PIPEOK ctl ) 2>/dev/null; c1=$?; [ "$c1" -ne 0 ] || STOP`); a write into a read-only directory fails (`( printf x > "$EVID/work/ro/f" ) 2>/dev/null; c2=$?; [ "$c2" -ne 0 ] || STOP`); a producer that exits 1 after partial stdout is caught by the `x=$(cmd) || r=$?` form BEFORE its output is used (`r=0; x=$(printf 'partial\n'; exit 1) || r=$?; [ "$r" -eq 1 ] || STOP`). Each control's receipt to `$EVID/H/runner-controls.txt`.
- [ ] **Step 1: E2, E5 and the closure** — `H0=$(git rev-parse HEAD) || STOP`; the E2 census (`git grep -n -E 'repo::(discover|classify|run_eligibility|capture|restore_entry)\(' HEAD -- src ':!src/core/repo'`, non-empty); the E5 grep (the SAME pattern that was EMPTY at B) → its `file:line` site set equals E2's (`d=0; diff "$EVID/H/E2-sites.txt" "$EVID/H/E5-sites.txt" > "$EVID/H/E5-flip.txt" || d=$?; [ "$d" -eq 0 ] || STOP`); the closure: `invoke_git(` outside `src/core/repo` EMPTY and the spawn primitives EMPTY outside `src/core/repo`/`src/core/support`; the network-class census compared by CONTENT (path + source text, line numbers stripped — Task 1 shifts eligibility.cpp's lines), SPLIT AT c1e (rev28: c1e threads the ceiling through restore.cpp's network-class call lines, so B is compared with c1e's parent and c1e with H0; c1e's own delta is recorded as data for m-1's byte review) — `d=0; diff "$EVID/H/network-class-B.content" "$EVID/H/network-class-C1Ep.content" > "$EVID/H/network-class-pre-c1e.delta" || d=$?; [ "$d" -eq 0 ] || STOP` and `d=0; diff "$EVID/H/network-class-C1E.content" "$EVID/H/network-class-H0.content" > "$EVID/H/network-class-post-c1e.delta" || d=$?; [ "$d" -eq 0 ] || STOP`.
- [ ] **Step 2: veto 9; the type-scoped RepoEntry census; the C-2 hunk; the zero-byte fences; the fabric census; the A8 / predicate / hook censuses** — the commit walk (the first THREE commits engine-only at their exact path sets — c1a eligibility.{hpp,cpp}+test, c1b discover.cpp+test, c1c restore.{hpp,cpp}+test with restore.hpp's numstat `2 0` (fence rev3's bound); V-2b-5 rev2: the scan.cpp diff ADDS OR REMOVES no `".biv"` line — measured under `--unified=0` on changed lines only (`grep -c -E '^[+-].*"\.biv"'` = 0), because the default context carries the file's one UNCHANGED `".biv"` line (1 with context, 0 without, at 1065872; an added-literal mutant hunk = 1 — the rev19 command would have STOPped at H on compliant bytes); rev33: c8Tr is the one further engine commit — `src/core/repo/restore.cpp` alone, identified by `commits.c8Tr.txt`, met exactly once, after c7, with the Task 8b order c8L < c8Tr < c8T measured from the commit files (`H/veto9-order-c8.txt`); rev28: after them and BEFORE c7 the ONLY engine commits are c1d then c1e, identified by `commits.c1d.txt` / `commits.c1e.txt` (never by position), each engine-only at its EXACT path set — c1d {`src/core/repo/classify.cpp`, `tests/test_repo_engine.cpp`}, c1e {`src/core/repo/git.hpp`, `src/core/repo/git.cpp`, `src/core/repo/git_exec.hpp`, `src/core/repo/git_exec.cpp`, `src/core/repo/restore.cpp`, `tests/test_repo_engine.cpp`} — each met exactly once, in walk order c6p < c1d < c1e < c7; no other engine path before c7, and after c7 none but c8Tr's `src/core/repo/restore.cpp`; no commit spans both sets); `c=0; python3 "$EVID/repoentry_census.py" src/cli src/core/pack src/core/scan src/core/open > "$EVID/H/repoentry-census.txt" || c=$?; printf 'repoentry_census_rc=%s\n' "$c" > "$EVID/H/repoentry-census.rc"; [ "$c" -eq 0 ] || STOP` (rc 0 = zero member writes on any RepoEntry-typed binding; its two controls re-run here on scratch copies); the C-2 hunk: the four lines from `auto manifest_json = manifest::serialize(manifest_model);` at H0 `cmp`-equal to a2f6fd1's; the zero-byte fences (rev23, MUST-2B-42: `harness/bivharness` is fenced to `e3.py` plus EXACTLY the three paths m-3's c8 commit admits, and their bytes are c8's — unchanged before c8, unchanged after it): `z=0; git diff --stat "$B" HEAD -- src/core/manifest src/adapters harness/bivharness/e3.py src/core/open/render.cpp > "$EVID/H/zero-byte-fences.txt" || z=$?; [ "$z" -eq 0 ] && [ ! -s "$EVID/H/zero-byte-fences.txt" ] || STOP`; `z=0; git diff --name-only "$B" HEAD -- harness/bivharness > "$EVID/H/bivharness-paths.txt" || z=$?; [ "$z" -eq 0 ] && [ "$(LC_ALL=C sort "$EVID/H/bivharness-paths.txt" | tr '\n' ' ')" = 'harness/bivharness/compare.py harness/bivharness/manifest.py harness/bivharness/scenario.py ' ] || STOP`; `z=0; C8=$(cat "$EVID/commits.c8.txt") || z=$?; [ "$z" -eq 0 ] && [ -n "$C8" ] && git diff --quiet "$C8~1" "$B" -- harness/bivharness && git diff --quiet "$C8" HEAD -- harness/bivharness || STOP`; the eighteen-path fabric census recorded; the A8 census (every `facts.` occurrence inside `url_consent.cpp` on a line that also calls `consent_display(` — the line-level proxy; the per-occurrence census is m-3's review); `g=0; k=$(grep -c 'isatty(' src/cli/main.cpp) || g=$?; [ "$g" -eq 1 ] && [ "$k" -eq 0 ] || STOP` (one predicate); the hook install function's body carries no `json`, `offline` or `network` token.
- [ ] **Step 3: the macOS observation at H0** — build; the five `-r xml` producers → `tuples.py` → `H/tuples-macos.txt`; `cellgate.py "$EVID/B-cells.txt" macos "$EVID/H/tuples-macos.txt"` (rc 0 or 5 — MOVED rows are data); the skip set UNCHANGED (`q=0; python3 "$EVID/skipset.py" "$EVID/B-cells.txt" "$EVID/H/tuples-macos.txt" macos > "$EVID/H/skipset-macos.txt" || q=$?; [ "$q" -eq 0 ] || STOP`); the `harness-e2` row on macOS (`ctest --preset ci-macos -R '^harness-e2$'` rc 0 → `H/harness-e2-macos.rc`). rev33, THE COUNT GATE REFUSES FAILURES: every one of the five producers rc 0 and every macOS tuple `failures=0 expectedFailures=0`, both a STOP otherwise (impl-10's 483/1/0/3 was admitted as a move by rev32; it must not be).
- [ ] **Step 4: the Linux parity leg for H0 and B; E3 Linux; harness-e2 Linux; the population rule** — the pinned clang-tidy-22 mirror assets (manifest from the workflow bytes; `gh release download`; sha256 verified); the container (`linux-container.sh`, Phases R/T/S) at H0 then at B; receipts (payload rc 0; the four phase rcs; the suite aggregate; nofile soft == hard); `tuples.py linux` for both; `cellgate.py … linux` (data) and the Linux skip set UNCHANGED (STOP otherwise) — rev36 (impl-11's STOP): B's workflow pins NO Linux skip-name set (its Linux `checks` block carries only the count `"skips": 1`, which `cellgate.py` gates; `cells.py` records the missing set as `expected_skips linux absent `, a form `skipset.py` does not parse — it raised `IndexError` at impl-11's line 219), so UNCHANGED on Linux is H0's OBSERVED set against B's OBSERVED set: the `absent` row asserted exactly once first (a B-cells file that pins a Linux set STOPs here instead of passing unread), then each tree's one `expected_skips_observed linux n=<k> …` line from `tuples.py` (names sorted, so byte equality is set-and-count equality) compared — `q=0; cmp "$EVID/H/skipset-linux-B.txt" "$EVID/H/skipset-linux-H.txt" > "$EVID/H/skipset-linux.cmp" 2>&1 || q=$?; printf 'skipset_linux_rc=%s\n' "$q" > "$EVID/H/skipset-linux.rc"; [ "$q" -eq 0 ] || STOP`; `skipset.py` stays the macOS gate, verbatim; E3 from the H0 `biv_tests-linux.xml` (`[E3]`-tagged cases all successful) — rev36: read by the runner itself, because `xmlcases.py e3` tests an Element's truth value (`tc.find("OverallResult") or {}`) and a childless `<OverallResult>` is falsy, so it reads a green case as `success=None` (measured on impl-11's `H/biv_tests-linux.xml`: one `[E3]` case, `success="true"`, and `xmlcases.py e3` rc 5); `xmlcases.py ctest-row` is unaffected and stays; the `harness-e2` row status from the H0 ctest junit (`H/harness-e2-linux.txt`, must be passed); `selftest_summary.py` on both junits → the populations; EQUAL → the single-sample bar exactly as the R-4.49 plan computed it (`rcL`; the failed names ⊆ the r435 family; the base draw valid; `bar=pass-green|pass-r435-disclosed-registered-red` required — `case "$bar" in pass-green|pass-r435-disclosed-registered-red) :;; *) STOP;; esac`); rev33 (R-4.77, master 215035: at least five runs each at B and the final head with a per-case frequency table before the GO) — the 015244 interleaved series runs ALWAYS, equal populations or not (with equal populations the single-sample bar must ALSO pass): N = 10 per tree, ALTERNATING B/H0, one fresh container per draw, every draw reduced by `selftest_summary.py`, then `series_verdict.py` (K-1 membership categorical → K-2 count ≥ 5 → K-3 shift = mean delta ≥ 1.0 OR complete separation, strictly `landed min > base max` (rev37, m-4's `K3_TIE: strict`; the corrected block is produced at `$EVID/series_verdict.rev37.py` when absent — rev38: through a fresh `mktemp` stage in the confined `work/`, regular before and after the extract — and pinned by digest either way, and the series calls it); per-draw validity; per-test frequencies) → `VERDICT NOT-SHIFTED` required (`[ "$(cat "$EVID/H/selftest-series.rc")" = series_rc=0 ] || STOP`); the `FREQ` rows are the R-4.77 table m-3 reads at the GO; the deselection arm is NOT pre-authorized for this candidate. rev33, TIDY GREEN AT H0 (the landing condition, 224030): the H0 junit's `safety-tidy-analyzer` row passed, its coverage line `clang-tidy coverage: 37 results == 37 sources` present once, and zero finding lines in the H0 ctest log (`H/tidy-H0.txt`); every Linux H0 tuple `failures=0`.
- [ ] **Step 5: the companion count-cell commit INSIDE the runner, then the FINAL H** — iff any `MOVED` row on either platform: `cellpatch.py "$EVID/B-workflow.yml" "$EVID/H/tuples-macos.txt" "$EVID/H/tuples-linux.txt" > .github/workflows/s2-harness.yml` (rewrites ONLY the moved `successes`/`skips` literals of the named binaries in the named target block — a changed skip set already STOPped above), `cells.py` on the result → `H/H-cells.txt`, `cellgate.py "$EVID/H/H-cells.txt" <target> <tuples>` rc 0 for BOTH targets, the c9 commit (`ci: pin case counts at H (macOS/Linux) -- m-3 count-cell companion`); else no commit and `H-cells.txt` = `B-cells.txt`; either way `[ "$(cat "$EVID/H/count-gate-final-macos.rc")" = count_gate_final_macos_rc=0 ] && [ "$(cat "$EVID/H/count-gate-final-linux.rc")" = count_gate_final_linux_rc=0 ] || STOP`. Then `H=$(git rev-parse HEAD) || STOP`; `d=0; git diff --stat "$H0" "$H" -- . ':!.github/workflows/s2-harness.yml' > "$EVID/H/H0-H.delta" || d=$?; [ "$d" -eq 0 ] && [ ! -s "$EVID/H/H0-H.delta" ] || STOP` (every H0 receipt carries to H); `count-gate-final-<target>.rc` = 0 both; `H.txt` written LAST; `H0.txt` beside it. rev33: when c9 is committed, the canonical container runs once more AT H (`$EVID/H9/`, the three inputs byte-copied beside it): rc 0, the four phases and the aggregate 0, the tidy row GREEN with coverage 37/37 (`H9/c9-gate.txt`) — the per-head gate at the head that lands.
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
# rev33 — Task 9 runs at the c8T head; every Task 8b receipt present (the three head gates, the c8Tr and c8T records)
[ -s "$EVID/commits.c8T.txt" ] && [ "$(git rev-parse HEAD)" = "$(cat "$EVID/commits.c8T.txt")" ] || STOP
for L in c8L c8Tr c8T; do [ -s "$EVID/commits.$L.txt" ] && [ -s "$EVID/heads/$L/headgate.txt" ] || STOP; done
for f in c8Tr-mutants.txt c8T-mutants.txt c8T-b1-regeneration.txt; do [ -s "$EVID/receipts/$f" ] || STOP; done
# rev33 (master 215035 R3(iii), 224030): an EARLIER Task 9 attempt's outputs are PRESERVED before this run writes anything — three renames into a stage, verified, ONE publishing rename, re-verified; never a copy, never a delete; a fault before the publish renames everything back and proves the originals byte-identical
PMANI() { python3 - "$1" "$3" > "$2" <<'PY'
import hashlib, os, stat, sys
root = sys.argv[1]; out = []
def row(rel):
    p = os.path.join(root, rel); st = os.lstat(p); mode = stat.S_IMODE(st.st_mode)
    if stat.S_ISLNK(st.st_mode):
        out.append("l %o - %s %s" % (mode, os.readlink(p), rel))
    elif stat.S_ISDIR(st.st_mode):
        out.append("d %o - - %s" % (mode, rel))
        for n in sorted(os.listdir(p)):
            row(os.path.join(rel, n))
    elif stat.S_ISREG(st.st_mode):
        h = hashlib.sha256()
        with open(p, "rb") as f:
            for chunk in iter(lambda: f.read(1 << 20), b""):
                h.update(chunk)
        out.append("f %o %d %s %s" % (mode, st.st_size, h.hexdigest(), rel))
    else:
        out.append("x %o - - %s" % (mode, rel))
for rel in ["H", "H0.txt", "helpers.verify-9.txt"] + ["B/" + n for n in open(sys.argv[2], encoding="utf-8").read().split("\n") if n]:
    row(rel)
sys.stdout.write("".join(x + "\n" for x in out))
PY
}
# rev36 (impl-11's STOP 130242): an earlier attempt's B Linux leg lives in B/ beside Task 0's fifteen macOS records — BLEG prints every B/ entry
# outside those fifteen (sorted), exit 3 unless all fifteen are present as regular files
BLEG() { python3 - "$EVID/B" > "$1" <<'PY'
import os, sys
T0 = frozenset(("biv_probe_tests-macos.stderr", "biv_probe_tests-macos.xml", "biv_repo_engine_tests-macos.stderr", "biv_repo_engine_tests-macos.xml", "biv_repo_git_tests-macos.stderr", "biv_repo_git_tests-macos.xml", "biv_subprocess_tests-macos.stderr", "biv_subprocess_tests-macos.xml", "biv_tests-macos.stderr", "biv_tests-macos.xml", "build-B.log", "configure-B.log", "run-rcs-macos.txt", "skipset-macos.txt", "tuples-macos.txt"))
d = sys.argv[1]
if any(os.path.islink(os.path.join(d, n)) or not os.path.isfile(os.path.join(d, n)) for n in T0):
    sys.exit(3)
sys.stdout.write("".join(n + "\n" for n in sorted(os.listdir(d)) if n not in T0))
PY
}
for x in series H9 H.txt commits.c9.txt; do [ ! -e "$EVID/$x" ] && [ ! -L "$EVID/$x" ] || STOP; done
[ -d "$EVID/B" ] && [ ! -L "$EVID/B" ] && [ -d "$EVID/work" ] && [ ! -L "$EVID/work" ] || STOP
# rev38 (MUST-2B-52): CONFINEMENT before the first write — work/ and B/ physically the home's own, and no symlink directly under the home, work/ or B/, so no fixed name this runner writes with > can be redirected (H/, H9/ and series/ are made fresh)
p=0; RH=$(cd "$EVID" && pwd -P) || p=$?; [ "$p" -eq 0 ] && [ -n "$RH" ] && [ "$(cd "$EVID/work" && pwd -P)" = "$RH/work" ] && [ "$(cd "$EVID/B" && pwd -P)" = "$RH/B" ] || STOP
f=0; LNK=$(find "$EVID" "$EVID/work" "$EVID/B" -maxdepth 1 -type l) || f=$?; [ "$f" -eq 0 ] && [ -z "$LNK" ] || STOP
b=0; BLEG "$EVID/work/B-leg.names" || b=$?; [ "$b" -eq 0 ] || STOP
if [ -e "$EVID/H0.txt" ] || [ -L "$EVID/H0.txt" ]; then
  [ -f "$EVID/H0.txt" ] && [ ! -L "$EVID/H0.txt" ] && [ -d "$EVID/H" ] && [ ! -L "$EVID/H" ] && [ -f "$EVID/helpers.verify-9.txt" ] && [ ! -L "$EVID/helpers.verify-9.txt" ] || STOP
  a=0; n=$(awk 'END { print NR }' "$EVID/H0.txt") || a=$?; [ "$a" -eq 0 ] && [ "$n" -eq 1 ] || STOP
  g=0; PH0=$(sed -n -E 's/^H0=([0-9a-f]{40})$/\1/p' "$EVID/H0.txt") || g=$?; [ "$g" -eq 0 ] && [ -n "$PH0" ] || STOP
  PN=task9-H0-${PH0:0:7}; PT=$EVID/attempts/$PN
  if [ ! -e "$EVID/attempts" ] && [ ! -L "$EVID/attempts" ]; then m=0; mkdir "$EVID/attempts" || m=$?; [ "$m" -eq 0 ] || STOP; fi
  [ -d "$EVID/attempts" ] && [ ! -L "$EVID/attempts" ] || STOP
  p=0; AP=$(cd "$EVID/attempts" && pwd -P) || p=$?; [ "$p" -eq 0 ] && [ "$AP" = "$(cd "$EVID" && pwd -P)/attempts" ] || STOP
  d=0; DE=$(stat -f %d "$EVID") || d=$?; [ "$d" -eq 0 ] && [ -n "$DE" ] && [ "$(stat -f %d "$EVID/attempts")" = "$DE" ] && [ "$(stat -f %d "$EVID/H")" = "$DE" ] && [ "$(stat -f %d "$EVID/B")" = "$DE" ] || STOP
  [ ! -e "$PT" ] && [ ! -L "$PT" ] || STOP
  PS=$(mktemp -d "$EVID/attempts/stage-$PN.XXXXXX") || STOP; [ -d "$PS" ] && [ ! -L "$PS" ] || STOP
  c=0; cp "$EVID/work/B-leg.names" "$PS/B-leg.names" || c=$?; [ "$c" -eq 0 ] && cmp -s "$EVID/work/B-leg.names" "$PS/B-leg.names" || STOP
  m=0; mkdir "$PS/B" || m=$?; [ "$m" -eq 0 ] || STOP
  q=0; PMANI "$EVID" "$PS/MANIFEST.pre" "$PS/B-leg.names" || q=$?; [ "$q" -eq 0 ] && [ -s "$PS/MANIFEST.pre" ] || STOP
  PBACK() { local y; for y in helpers.verify-9.txt H0.txt H; do if [ -e "$PS/$y" ] || [ -L "$PS/$y" ]; then { [ ! -e "$EVID/$y" ] && [ ! -L "$EVID/$y" ] && mv "$PS/$y" "$EVID/$y"; } || { printf 'STOP-task-9 preserve-rollback %s (%s)\n' "$y" "$1" >&2; exit 1; }; fi; done
    while IFS= read -r y; do [ -n "$y" ] || continue; if [ -e "$PS/B/$y" ] || [ -L "$PS/B/$y" ]; then { [ ! -e "$EVID/B/$y" ] && [ ! -L "$EVID/B/$y" ] && mv "$PS/B/$y" "$EVID/B/$y"; } || { printf 'STOP-task-9 preserve-rollback B/%s (%s)\n' "$y" "$1" >&2; exit 1; }; fi; done < "$PS/B-leg.names"
    local q=0; PMANI "$EVID" "$PS/MANIFEST.back" "$PS/B-leg.names" || q=$?; [ "$q" -eq 0 ] && cmp -s "$PS/MANIFEST.pre" "$PS/MANIFEST.back" || { printf 'STOP-task-9 preserve-rollback-verify (%s)\n' "$1" >&2; exit 1; }
    printf 'STOP-task-9 preserve-fault %s: rolled back, originals byte-identical\n' "$1" >&2; exit 1; }
  for x in H H0.txt helpers.verify-9.txt; do v=0; mv "$EVID/$x" "$PS/$x" || v=$?; [ "$v" -eq 0 ] || PBACK "move-$x"; done
  while IFS= read -r x; do [ -n "$x" ] || continue; v=0; mv "$EVID/B/$x" "$PS/B/$x" || v=$?; [ "$v" -eq 0 ] || PBACK "move-B/$x"; done < "$PS/B-leg.names"
  q=0; PMANI "$PS" "$PS/MANIFEST.stage" "$PS/B-leg.names" || q=$?; [ "$q" -eq 0 ] || PBACK stage-manifest
  c=0; cmp -s "$PS/MANIFEST.pre" "$PS/MANIFEST.stage" || c=$?; [ "$c" -eq 0 ] || PBACK stage-differs
  [ ! -e "$PT" ] && [ ! -L "$PT" ] || PBACK target-appeared
  v=0; mv "$PS" "$PT" || v=$?; [ "$v" -eq 0 ] || PBACK publish
  [ -d "$PT" ] && [ ! -L "$PT" ] && [ ! -e "$PS" ] && [ ! -L "$PS" ] || STOP
  q=0; PMANI "$PT" "$PT/MANIFEST.post" "$PT/B-leg.names" || q=$?; [ "$q" -eq 0 ] || STOP
  c=0; cmp -s "$PT/MANIFEST.pre" "$PT/MANIFEST.post" || c=$?; [ "$c" -eq 0 ] || STOP
  m=0; mkdir "$EVID/H" || m=$?; [ "$m" -eq 0 ] || STOP
  h=0; PMS=$(shasum -a 256 "$PT/MANIFEST.pre" | cut -d' ' -f1) || h=$?; [ "$h" -eq 0 ] && [ -n "$PMS" ] || STOP
  a=0; PMN=$(awk 'END { print NR }' "$PT/MANIFEST.pre") || a=$?; [ "$a" -eq 0 ] || STOP
  a=0; PBN=$(awk 'END { print NR }' "$PT/B-leg.names") || a=$?; [ "$a" -eq 0 ] || STOP
  printf 'preserved=attempts/%s manifest_sha256=%s manifest_rows=%s b_leg_files=%s\n' "$PN" "$PMS" "$PMN" "$PBN" > "$EVID/H/preserved-attempt.txt" || STOP
else
  [ ! -s "$EVID/work/B-leg.names" ] || STOP
  [ ! -e "$EVID/helpers.verify-9.txt" ] && [ ! -L "$EVID/helpers.verify-9.txt" ] || STOP
  if [ ! -e "$EVID/H" ] && [ ! -L "$EVID/H" ]; then m=0; mkdir "$EVID/H" || m=$?; [ "$m" -eq 0 ] || STOP; fi
  [ -d "$EVID/H" ] && [ ! -L "$EVID/H" ] || STOP
  f=0; find "$EVID/H" -mindepth 1 -maxdepth 1 > "$EVID/work/H-prior-entries.txt" || f=$?; [ "$f" -eq 0 ] && [ ! -s "$EVID/work/H-prior-entries.txt" ] || STOP
  printf 'preserved=none\n' > "$EVID/H/preserved-attempt.txt" || STOP
fi
[ -s "$EVID/H/preserved-attempt.txt" ] || STOP
b=0; BLEG "$EVID/work/B-leg.post" || b=$?; [ "$b" -eq 0 ] && [ ! -s "$EVID/work/B-leg.post" ] || STOP
v=0; (cd "$EVID" && shasum -a 256 -c helpers.sha256 > helpers.verify-9.txt 2>&1) || v=$?; [ "$v" -eq 0 ] || STOP
s=0; git status --porcelain > "$EVID/H/status-pre.txt" || s=$?; [ "$s" -eq 0 ] && [ ! -s "$EVID/H/status-pre.txt" ] || STOP
# rev29 (the impl-8 STOP 072544): Task 9 PRODUCES its two inputs here (no earlier task did); each produced only when absent and digest-pinned either way (never overwritten)
[ -s "$EVID/B/tuples-macos.txt" ] || STOP
g=0; git -C "$MAIN" show "${B}:.github/workflows/s2-harness.yml" > "$EVID/work/B-workflow.rev29.yml" || g=$?; [ "$g" -eq 0 ] && [ -s "$EVID/work/B-workflow.rev29.yml" ] || STOP; c=0; cmp -s "$EVID/work/B-workflow.rev29.yml" "$EVID/B-workflow.yml" || c=$?; [ "$c" -eq 0 ] || STOP
if [ ! -e "$EVID/llvm-manifest-source.txt" ] && [ ! -e "$EVID/llvm-manifest.txt" ]; then
s=0; sed -n '167,174p' "$EVID/B-workflow.yml" > "$EVID/llvm-manifest-source.txt" || s=$?; [ "$s" -eq 0 ] && [ -s "$EVID/llvm-manifest-source.txt" ] || STOP; s=0; sed 's/^          //' "$EVID/llvm-manifest-source.txt" > "$EVID/llvm-manifest.txt" || s=$?; [ "$s" -eq 0 ] && [ -s "$EVID/llvm-manifest.txt" ] || STOP; a=0; n=$(awk 'END { print NR }' "$EVID/llvm-manifest.txt") || a=$?; [ "$a" -eq 0 ] && [ "$n" -eq 8 ] || STOP; g=0; k=$(grep -c -E '^[0-9a-f]{64} [a-z0-9-]+ [A-Za-z0-9._+~-]+\.deb$' "$EVID/llvm-manifest.txt") || g=$?; [ "$g" -le 1 ] && [ "$k" -eq 8 ] || STOP
fi
[ -s "$EVID/llvm-manifest-source.txt" ] && [ -s "$EVID/llvm-manifest.txt" ] || STOP
m=0; ms=$(shasum -a 256 "$EVID/llvm-manifest-source.txt" | cut -d' ' -f1) || m=$?; [ "$m" -eq 0 ] && [ "$ms" = 53bbdd42f32e6685df24d1c11314bfc3b47ceda0a06689458c93dd8a42d8ad5b ] || STOP
m=0; mf=$(shasum -a 256 "$EVID/llvm-manifest.txt" | cut -d' ' -f1) || m=$?; [ "$m" -eq 0 ] && [ "$mf" = 22724f783d4dc47ce780841098a3536b29a490dbc3fdb57830087a8f270e7ad7 ] || STOP
if [ ! -e "$EVID/observer-unset-names.txt" ]; then
n=0; (cd harness && PYTHONDONTWRITEBYTECODE=1 ../.venv-harness/bin/python -c 'from bivharness.e3 import CREDENTIAL_ENV_NAMES as n; print("\n".join(n))') > "$EVID/observer-unset-names.txt" || n=$?; [ "$n" -eq 0 ] && [ -s "$EVID/observer-unset-names.txt" ] || STOP
fi
g=0; k=$(grep -c -E '^[A-Z][A-Z0-9_]+$' "$EVID/observer-unset-names.txt") || g=$?; [ "$g" -eq 0 ] && [ "$k" -ge 1 ] || STOP; a=0; n=$(awk 'END { print NR }' "$EVID/observer-unset-names.txt") || a=$?; [ "$a" -eq 0 ] && [ "$n" -eq "$k" ] || STOP
o=0; of=$(shasum -a 256 "$EVID/observer-unset-names.txt" | cut -d' ' -f1) || o=$?; [ "$o" -eq 0 ] && [ "$of" = e12d5d0af265ea8faf41dadc1e3af02610365ac25c40a228714b0e72f2a612f3 ] || STOP
# rev37 (m-4 151817 K3_TIE strict; master 154632): the corrected series reducer, produced beside Task 0's `series_verdict.py` (never overwritten) from THIS plan's block only when absent (rev38: a fresh `mktemp` stage in the confined work/ — never a fixed name, so an earlier failed stage is kept, not truncated — checked regular before and after the extract, digest-checked, then renamed into place), digest-pinned either way
V37=$EVID/series_verdict.rev37.py
if [ ! -e "$V37" ] && [ ! -L "$V37" ]; then
PLANP=$(cat "$RUNNERS/plan-path.txt") || STOP; [ -s "$PLANP" ] || STOP; V37S=$(mktemp "$EVID/work/series_verdict.rev37.XXXXXX") || STOP; [ -f "$V37S" ] && [ ! -L "$V37S" ] && [ ! -s "$V37S" ] || STOP; x=0; python3 "$RUNNERS/plan_blocks.py" extract "$PLANP" series_verdict.py > "$V37S" || x=$?; [ "$x" -eq 0 ] && [ -f "$V37S" ] && [ ! -L "$V37S" ] && [ -s "$V37S" ] || STOP
m=0; vs=$(shasum -a 256 "$V37S" | cut -d' ' -f1) || m=$?; [ "$m" -eq 0 ] && [ "$vs" = 09b6cb7612907972bb9cf340a8ffcbf406a71da1194d034ce45c85de6127d452 ] || STOP
[ ! -e "$V37" ] && [ ! -L "$V37" ] || STOP; v=0; mv "$V37S" "$V37" || v=$?; [ "$v" -eq 0 ] || STOP
fi
[ -f "$V37" ] && [ ! -L "$V37" ] || STOP
m=0; vs=$(shasum -a 256 "$V37" | cut -d' ' -f1) || m=$?; [ "$m" -eq 0 ] && [ "$vs" = 09b6cb7612907972bb9cf340a8ffcbf406a71da1194d034ce45c85de6127d452 ] || STOP
p=0; python3 -m py_compile "$V37" || p=$?; [ "$p" -eq 0 ] || STOP
s=0; git status --porcelain > "$EVID/H/status-inputs.txt" || s=$?; [ "$s" -eq 0 ] && [ ! -s "$EVID/H/status-inputs.txt" ] || STOP
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
z=0; C1E=$(cat "$EVID/commits.c1e.txt") || z=$?; [ "$z" -eq 0 ] && [ -n "$C1E" ] || STOP
r=0; C1EP=$(git rev-parse "$C1E~1") || r=$?; [ "$r" -eq 0 ] && [ -n "$C1EP" ] || STOP
g=0; git grep -n 'GitCallClass::network' "$C1EP" -- src > "$EVID/work/nc-C1Ep.raw" || g=$?; [ "$g" -eq 0 ] || STOP; s=0; sed -E "s/^${C1EP}:([^:]+):[0-9]+:/\1: /" "$EVID/work/nc-C1Ep.raw" > "$EVID/work/nc-C1Ep.unsorted" || s=$?; [ "$s" -eq 0 ] || STOP; s=0; LC_ALL=C sort "$EVID/work/nc-C1Ep.unsorted" > "$EVID/H/network-class-C1Ep.content" || s=$?; [ "$s" -eq 0 ] || STOP
g=0; git grep -n 'GitCallClass::network' "$C1E" -- src > "$EVID/work/nc-C1E.raw" || g=$?; [ "$g" -eq 0 ] || STOP; s=0; sed -E "s/^${C1E}:([^:]+):[0-9]+:/\1: /" "$EVID/work/nc-C1E.raw" > "$EVID/work/nc-C1E.unsorted" || s=$?; [ "$s" -eq 0 ] || STOP; s=0; LC_ALL=C sort "$EVID/work/nc-C1E.unsorted" > "$EVID/H/network-class-C1E.content" || s=$?; [ "$s" -eq 0 ] || STOP
d=0; diff "$EVID/H/network-class-B.content" "$EVID/H/network-class-C1Ep.content" > "$EVID/H/network-class-pre-c1e.delta" || d=$?; [ "$d" -eq 0 ] || STOP
d=0; diff "$EVID/H/network-class-C1E.content" "$EVID/H/network-class-H0.content" > "$EVID/H/network-class-post-c1e.delta" || d=$?; [ "$d" -eq 0 ] || STOP
d=0; diff "$EVID/H/network-class-C1Ep.content" "$EVID/H/network-class-C1E.content" > "$EVID/H/network-class-c1e.delta" || d=$?; [ "$d" -le 1 ] || STOP
a=0; nnc=$(awk 'END { print NR }' "$EVID/H/network-class-H0.content") || a=$?; [ "$a" -eq 0 ] && [ "$nnc" -eq 6 ] || STOP
# Step 2 — veto 9; RepoEntry census (type-scoped) + controls; C-2 hunk; zero-byte fences; fabric census; A8 / predicate / hook censuses
z=0; C1D=$(cat "$EVID/commits.c1d.txt") || z=$?; [ "$z" -eq 0 ] && [ -n "$C1D" ] || STOP
z=0; C1E=$(cat "$EVID/commits.c1e.txt") || z=$?; [ "$z" -eq 0 ] && [ -n "$C1E" ] && [ "$C1E" != "$C1D" ] || STOP
z=0; C6P=$(cat "$EVID/commits.c6p.txt") || z=$?; [ "$z" -eq 0 ] && [ -n "$C6P" ] || STOP
z=0; C7=$(cat "$EVID/commits.c7.txt") || z=$?; [ "$z" -eq 0 ] && [ -n "$C7" ] || STOP
z=0; C8TR=$(cat "$EVID/commits.c8Tr.txt") || z=$?; [ "$z" -eq 0 ] && [ -n "$C8TR" ] || STOP
z=0; C8L=$(cat "$EVID/commits.c8L.txt") || z=$?; [ "$z" -eq 0 ] && [ -n "$C8L" ] || STOP
z=0; C8T=$(cat "$EVID/commits.c8T.txt") || z=$?; [ "$z" -eq 0 ] && [ -n "$C8T" ] || STOP
: > "$EVID/H/veto9.txt"; k=0; kd=0; ke=0; k6p=0; k7=0; k8=0; k8l=0; k8t=0
for c in $(git log --reverse --format=%H "$B..HEAD"); do
  git diff-tree --no-commit-id --name-only -r "$c" > "$EVID/work/paths-$c.txt" || STOP
  e=0; ne=$(grep -c -E '^src/core/repo/' "$EVID/work/paths-$c.txt") || e=$?; [ "$e" -le 1 ] || STOP
  s=0; ns=$(grep -c -E '^(src/cli|src/core/pack|src/core/scan|src/core/open)/' "$EVID/work/paths-$c.txt") || s=$?; [ "$s" -le 1 ] || STOP
  a=0; np=$(awk 'END { print NR }' "$EVID/work/paths-$c.txt") || a=$?; [ "$a" -eq 0 ] || STOP
  k=$((k+1))
  if [ "$k" -eq 1 ]; then [ "$ne" -ge 1 ] && [ "$ns" -eq 0 ] || STOP; o=0; grep -v -E '^(src/core/repo/eligibility\.(hpp|cpp)|tests/test_repo_engine\.cpp)$' "$EVID/work/paths-$c.txt" > "$EVID/work/paths-$c.other" || o=$?; [ "$o" -eq 1 ] && [ ! -s "$EVID/work/paths-$c.other" ] || STOP; elif [ "$k" -eq 2 ]; then [ "$ne" -ge 1 ] && [ "$ns" -eq 0 ] || STOP; o=0; grep -v -E '^(src/core/repo/discover\.cpp|tests/test_repo_engine\.cpp)$' "$EVID/work/paths-$c.txt" > "$EVID/work/paths-$c.other" || o=$?; [ "$o" -eq 1 ] && [ ! -s "$EVID/work/paths-$c.other" ] || STOP; elif [ "$k" -eq 3 ]; then [ "$ne" -ge 1 ] && [ "$ns" -eq 0 ] || STOP; o=0; grep -v -E '^(src/core/repo/restore\.(hpp|cpp)|tests/test_repo_engine\.cpp)$' "$EVID/work/paths-$c.txt" > "$EVID/work/paths-$c.other" || o=$?; [ "$o" -eq 1 ] && [ ! -s "$EVID/work/paths-$c.other" ] || STOP; elif [ "$c" = "$C1D" ]; then [ "$kd" -eq 0 ] && [ "$ne" -eq 1 ] && [ "$ns" -eq 0 ] && [ "$np" -eq 2 ] || STOP; o=0; grep -v -E '^(src/core/repo/classify\.cpp|tests/test_repo_engine\.cpp)$' "$EVID/work/paths-$c.txt" > "$EVID/work/paths-$c.other" || o=$?; [ "$o" -eq 1 ] && [ ! -s "$EVID/work/paths-$c.other" ] || STOP; kd=$k; elif [ "$c" = "$C1E" ]; then [ "$ke" -eq 0 ] && [ "$ne" -eq 5 ] && [ "$ns" -eq 0 ] && [ "$np" -eq 6 ] || STOP; o=0; grep -v -E '^(src/core/repo/git\.(hpp|cpp)|src/core/repo/git_exec\.(hpp|cpp)|src/core/repo/restore\.cpp|tests/test_repo_engine\.cpp)$' "$EVID/work/paths-$c.txt" > "$EVID/work/paths-$c.other" || o=$?; [ "$o" -eq 1 ] && [ ! -s "$EVID/work/paths-$c.other" ] || STOP; ke=$k; elif [ "$c" = "$C8TR" ]; then [ "$k8" -eq 0 ] && [ "$ne" -eq 1 ] && [ "$ns" -eq 0 ] && [ "$np" -eq 1 ] || STOP; o=0; grep -v -x -F 'src/core/repo/restore.cpp' "$EVID/work/paths-$c.txt" > "$EVID/work/paths-$c.other" || o=$?; [ "$o" -eq 1 ] && [ ! -s "$EVID/work/paths-$c.other" ] || STOP; k8=$k; else [ "$ne" -eq 0 ] || STOP; fi
  if [ "$c" = "$C6P" ]; then k6p=$k; fi
  if [ "$c" = "$C7" ]; then k7=$k; fi
  if [ "$c" = "$C8L" ]; then k8l=$k; fi; if [ "$c" = "$C8T" ]; then k8t=$k; fi
  [ "$ne" -eq 0 ] || [ "$ns" -eq 0 ] || STOP
  printf '%s engine=%s callsite=%s\n' "$c" "$ne" "$ns" >> "$EVID/H/veto9.txt"
done
[ -s "$EVID/H/veto9.txt" ] || STOP
[ "$k6p" -gt 3 ] && [ "$kd" -gt "$k6p" ] && [ "$ke" -gt "$kd" ] && [ "$k7" -gt "$ke" ] || STOP
printf 'c6p=%s c1d=%s c1e=%s c7=%s\n' "$k6p" "$kd" "$ke" "$k7" > "$EVID/H/veto9-order.txt" || STOP
[ "$k8l" -gt "$k7" ] && [ "$k8" -gt "$k8l" ] && [ "$k8t" -gt "$k8" ] || STOP
printf 'c7=%s c8L=%s c8Tr=%s c8T=%s\n' "$k7" "$k8l" "$k8" "$k8t" > "$EVID/H/veto9-order-c8.txt" || STOP
a=0; nk=$(awk 'END { print NR }' "$EVID/H/veto9.txt") || a=$?; [ "$a" -eq 0 ] && [ "$nk" -ge 5 ] || STOP
r=0; git diff --numstat "$B" HEAD -- src/core/repo/restore.hpp > "$EVID/H/restore-hpp.numstat" || r=$?; [ "$r" -eq 0 ] || STOP; n=0; nh=$(awk '{ print $1 " " $2 }' "$EVID/H/restore-hpp.numstat") || n=$?; [ "$n" -eq 0 ] && [ "$nh" = "2 0" ] || STOP
b=0; git diff --unified=0 "$B" HEAD -- src/core/scan/scan.cpp > "$EVID/H/scan-diff.txt" || b=$?; [ "$b" -le 1 ] || STOP; n=0; nb=$(grep -c -E '^[+-].*"\.biv"' "$EVID/H/scan-diff.txt") || n=$?; [ "$n" -le 1 ] && [ "$nb" -eq 0 ] || STOP   # rev20: --unified=0 + changed lines only — scan.cpp's one UNCHANGED ".biv" line rides in default context
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
z=0; git diff --stat "$B" HEAD -- src/core/manifest src/adapters harness/bivharness/e3.py src/core/open/render.cpp > "$EVID/H/zero-byte-fences.txt" || z=$?; [ "$z" -eq 0 ] && [ ! -s "$EVID/H/zero-byte-fences.txt" ] || STOP
z=0; git diff --name-only "$B" HEAD -- harness/bivharness > "$EVID/H/bivharness-paths.txt" || z=$?; [ "$z" -eq 0 ] && [ "$(LC_ALL=C sort "$EVID/H/bivharness-paths.txt" | tr '\n' ' ')" = 'harness/bivharness/compare.py harness/bivharness/manifest.py harness/bivharness/scenario.py ' ] || STOP
z=0; C8=$(cat "$EVID/commits.c8.txt") || z=$?; [ "$z" -eq 0 ] && [ -n "$C8" ] && git diff --quiet "$C8~1" "$B" -- harness/bivharness && git diff --quiet "$C8" HEAD -- harness/bivharness || STOP
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
g=0; k=$(grep -c -x -E 'biv_[a-z_]+ rc=0' "$EVID/H/run-rcs-macos.txt") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 5 ] || STOP
g=0; k=$(grep -c -x -E 'biv_[a-z_]+ macos successes=[0-9]+ failures=0 expectedFailures=0 skips=[0-9]+ xml_sha256=[0-9a-f]{64}' "$EVID/H/tuples-macos.txt") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 5 ] || STOP
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
g=0; k=$(grep -c -x -E 'biv_[a-z_]+ linux successes=[0-9]+ failures=0 expectedFailures=0 skips=[0-9]+ xml_sha256=[0-9a-f]{64}' "$EVID/H/tuples-linux.txt") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 5 ] || STOP
x=0; python3 "$EVID/xmlcases.py" ctest-row safety-tidy-analyzer "$EVID/H/ctest-linux-H.junit.xml" > "$EVID/H/tidy-row-H0.txt" || x=$?; [ "$x" -eq 0 ] || STOP
g=0; k=$(grep -c -F 'clang-tidy coverage: 37 results == 37 sources' "$EVID/H/ctest-linux-H.junit.xml") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP
g=0; k=$(grep -c -E ': error: .*\[' "$EVID/H/ctest-linux-H.log") || g=$?; [ "$g" -eq 1 ] && [ "$k" -eq 0 ] || STOP
printf 'tidy_H0=green coverage=37/37 findings=0 row=%s\n' "$(cat "$EVID/H/tidy-row-H0.txt")" > "$EVID/H/tidy-H0.txt" || STOP
c=0; python3 "$EVID/cellgate.py" "$EVID/B-cells.txt" linux "$EVID/H/tuples-linux.txt" > "$EVID/H/count-gate-linux.txt" 2>&1 || c=$?; printf 'count_gate_linux_rc=%s\n' "$c" > "$EVID/H/count-gate-linux.rc"; [ "$c" -eq 0 ] || [ "$c" -eq 5 ] || STOP
g=0; k=$(grep -c -E '^expected_skips linux ' "$EVID/B-cells.txt") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP
g=0; k=$(grep -c -x -F 'expected_skips linux absent ' "$EVID/B-cells.txt") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP
for T in B H; do g=0; grep -E '^expected_skips_observed linux n=[0-9]+ ' "$EVID/$T/tuples-linux.txt" > "$EVID/H/skipset-linux-$T.txt" || g=$?; [ "$g" -eq 0 ] || STOP; a=0; n=$(awk 'END { print NR }' "$EVID/H/skipset-linux-$T.txt") || a=$?; [ "$a" -eq 0 ] && [ "$n" -eq 1 ] || STOP; done
q=0; cmp "$EVID/H/skipset-linux-B.txt" "$EVID/H/skipset-linux-H.txt" > "$EVID/H/skipset-linux.cmp" 2>&1 || q=$?; printf 'skipset_linux_rc=%s\n' "$q" > "$EVID/H/skipset-linux.rc"; [ "$q" -eq 0 ] || STOP
c=0; python3 "$EVID/cellgate.py" "$EVID/B-cells.txt" linux "$EVID/B/tuples-linux.txt" > "$EVID/B/count-gate-linux.txt" 2>&1 || c=$?; [ "$c" -eq 0 ] || STOP
c=0; python3 "$EVID/cellgate.py" "$EVID/B-cells.txt" macos "$EVID/B/tuples-macos.txt" > "$EVID/B/count-gate-macos.txt" 2>&1 || c=$?; [ "$c" -eq 0 ] || STOP
x=0; python3 - "$EVID/H/biv_tests-linux.xml" > "$EVID/H/E3-linux.txt" <<'PY' || x=$?
import sys, xml.etree.ElementTree as ET
rows = []
for tc in ET.fromstring(open(sys.argv[1], "rb").read()).iter("TestCase"):
    if "[E3]" in (tc.get("tags") or ""):
        o = tc.find("OverallResult")
        rows.append((tc.get("name"), None if o is None else o.get("success")))
if not rows:
    print("E3 cases=0"); sys.exit(3)
for name, ok in rows:
    print("E3 case=%r success=%s" % (name, ok))
sys.exit(0 if all(ok == "true" for _, ok in rows) else 5)
PY
printf 'e3_linux_rc=%s\n' "$x" > "$EVID/H/E3-linux.rc"; [ "$x" -eq 0 ] || STOP
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
fi
  m=0; mkdir -p "$EVID/series" || m=$?; [ "$m" -eq 0 ] || STOP
  for i in 1 2 3 4 5 6 7 8 9 10; do
    for T in B H; do
      LABEL="$T-$i"; if [ "$T" = H ]; then EXP=$H0; else EXP=$B; fi
      m=0; mkdir -p "$EVID/series/$LABEL" || m=$?; [ "$m" -eq 0 ] || STOP
      o=0; docker run --rm --platform linux/amd64 --init -v "${LLVM_DIR}:/llvm-mirror:ro" -v "${MAIN}:/repo-ro:ro" -v "${EVID}/series:/evidence" -v "${EVID}/linux-container.sh:/evidence/linux-container.sh:ro" -v "${EVID}/linux-suite.sh:/evidence/linux-suite.sh:ro" -v "${EVID}/observer-unset-names.txt:/evidence/observer-unset-names.txt:ro" ubuntu:24.04 bash /evidence/linux-container.sh "$EXP" "$LABEL" > "$EVID/series/$LABEL/linux-container.log" 2>&1 || o=$?; printf '%s\n' "$o" > "$EVID/series/$LABEL/linux-container.rc"; [ "$o" -eq 0 ] || STOP
      x=0; python3 "$EVID/selftest_summary.py" "$EVID/series/$LABEL/ctest-linux-$LABEL.junit.xml" "$EVID/series/$LABEL/selftest-$LABEL" > "$EVID/series/$LABEL/selftest-$LABEL.out" || x=$?; [ "$x" -eq 0 ] || STOP
    done
  done
  s=0; python3 "$V37" "$EVID/series" "$EVID/H/r435-family.txt" 10 > "$EVID/H/selftest-series.txt" 2>&1 || s=$?; printf 'series_rc=%s\n' "$s" > "$EVID/H/selftest-series.rc"
[ "$(cat "$EVID/H/selftest-series.rc")" = series_rc=0 ] || STOP
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
  H9=$(git rev-parse HEAD) || STOP; m=0; mkdir "$EVID/H9" || m=$?; [ "$m" -eq 0 ] || STOP; m=0; mkdir "$EVID/H9/H" || m=$?; [ "$m" -eq 0 ] || STOP
  for f in linux-container.sh linux-suite.sh observer-unset-names.txt; do c=0; cp -p "$EVID/$f" "$EVID/H9/$f" || c=$?; [ "$c" -eq 0 ] && cmp -s "$EVID/$f" "$EVID/H9/$f" || STOP; done
  o=0; docker run --rm --platform linux/amd64 --init -v "${LLVM_DIR}:/llvm-mirror:ro" -v "${MAIN}:/repo-ro:ro" -v "${EVID}/H9:/evidence" ubuntu:24.04 bash /evidence/linux-container.sh "$H9" H > "$EVID/H9/H/linux-container.log" 2>&1 || o=$?; printf '%s\n' "$o" > "$EVID/H9/linux-container.rc"; [ "$o" -eq 0 ] || STOP
  [ "$(cat "$EVID/H9/H/container-payload.rc")" = container_payload_rc=0 ] || STOP
  g=0; k=$(grep -c -x -F "expected=$H9 observed=$H9" "$EVID/H9/H/linux-run-head-receipt.txt") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP
  for x in phase_R_base_provision_rc=0 phase_R_asset_provision_rc=0 phase_T_transition_fixture_rc=0 phase_S_suite_rc=0; do g=0; k=$(grep -c -x -F -- "$x" "$EVID/H9/H/linux-ledger.txt") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP; done
  g=0; k=$(grep -c -x -F 'suite_aggregate_rc=0 ledger_write_failed=0' "$EVID/H9/H/linux-suite-ledger.txt") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP
  x=0; python3 "$EVID/xmlcases.py" ctest-row safety-tidy-analyzer "$EVID/H9/H/ctest-linux-H.junit.xml" > "$EVID/H9/tidy-row.txt" || x=$?; [ "$x" -eq 0 ] || STOP
  g=0; k=$(grep -c -F 'clang-tidy coverage: 37 results == 37 sources' "$EVID/H9/H/ctest-linux-H.junit.xml") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP
  printf 'c9_head=%s container_rc=0 tidy=green coverage=37/37\n' "$H9" > "$EVID/H9/c9-gate.txt" || STOP
else
  c=0; cp "$EVID/B-cells.txt" "$EVID/H/H-cells.txt" || c=$?; [ "$c" -eq 0 ] || STOP
  printf 'unchanged\n' > "$EVID/H/count-gate.txt"; printf 'count_gate_final_macos_rc=0\n' > "$EVID/H/count-gate-final-macos.rc"; printf 'count_gate_final_linux_rc=0\n' > "$EVID/H/count-gate-final-linux.rc"
fi
[ "$(cat "$EVID/H/count-gate-final-macos.rc")" = count_gate_final_macos_rc=0 ] && [ "$(cat "$EVID/H/count-gate-final-linux.rc")" = count_gate_final_linux_rc=0 ] || STOP
H=$(git rev-parse HEAD) || STOP
d=0; git diff --stat "$H0" "$H" -- . ':!.github/workflows/s2-harness.yml' > "$EVID/H/H0-H.delta" || d=$?; [ "$d" -eq 0 ] && [ ! -s "$EVID/H/H0-H.delta" ] || STOP
s=0; git status --porcelain > "$EVID/H/status-post-9.txt" || s=$?; [ "$s" -eq 0 ] && [ ! -s "$EVID/H/status-post-9.txt" ] || STOP
# Step 6 — the fence-proofs file, then H LAST
{ printf 'check=runner-controls rc=%s expected=0\n' 0; printf 'check=E5-flip rc=%s expected=0\n' 0; printf 'check=closure-invoke-git rc=empty expected=empty\n'; printf 'check=S1-nospawn rc=empty expected=empty\n'; printf 'check=network-class-content rc=0 expected=0 sites=%s\n' "$nnc"; printf 'check=veto9 rc=0 expected=0\n'; cat "$EVID/H/repoentry-census.rc"; cat "$EVID/H/repoentry-census-controls.txt"; printf 'check=c2-hunk rc=0 expected=0\n'; printf 'check=zero-byte-fences rc=empty expected=empty\n'; printf 'check=a8-facts-wrapped unwrapped=0 expected=0\n'; printf 'check=isatty-predicate count=0 expected=0\n'; printf 'check=hook-install-no-json-offline-network count=0 expected=0\n'; cat "$EVID/H/count-gate-final-macos.rc" "$EVID/H/count-gate-final-linux.rc" "$EVID/H/E3-linux.rc" "$EVID/H/skipset-linux.rc" "$EVID/H/harness-e2-macos.rc" "$EVID/H/harness-e2-linux.rc" "$EVID/H/selftest-population.rc"; [ -s "$EVID/H/linux-selftest-bar.txt" ] && cat "$EVID/H/linux-selftest-bar.txt"; [ -s "$EVID/H/selftest-series.rc" ] && cat "$EVID/H/selftest-series.rc"; printf 'check=H0-H-delta rc=0 expected=0\n'; } > "$EVID/H/fence-proofs.txt" || STOP; [ -s "$EVID/H/fence-proofs.txt" ] || STOP
{ cat "$EVID/H/preserved-attempt.txt"; for L in c8L c8Tr c8T; do cat "$EVID/heads/$L/headgate.txt"; done; cat "$EVID/receipts/c8Tr-mutants.txt" "$EVID/receipts/c8T-mutants.txt" "$EVID/receipts/c8T-b1-regeneration.txt"; cat "$EVID/H/tidy-H0.txt"; printf 'check=macos-failures-refused rc=0 expected=0\n'; printf 'check=veto9-c8-order %s\n' "$(cat "$EVID/H/veto9-order-c8.txt")"; if [ -s "$EVID/H9/c9-gate.txt" ]; then cat "$EVID/H9/c9-gate.txt"; fi; } >> "$EVID/H/fence-proofs.txt" || STOP
printf 'H=%s\n' "$H" > "$EVID/H.txt" || STOP; [ -s "$EVID/H.txt" ] || STOP
exit 0
```

### Task 9b — the re-gate at the c10t head (rev41; c10 + Task 8d's c10t): the count cells re-pinned INSIDE the block iff a case tuple moved since c9 (c11), the FINAL H written last into `R/` (rev39; the operator's "lighter regate pls", 2026-09-26; m-3 R-4.83 and master R-4.82 folded for this block)

**Why a lighter re-gate and not Task 9 again.** Task 9 ran once to rc 0 under impl-12 and stands as EXECUTED: its receipts under `H/`, `H9/`, `series/` and `B/` are the record for H0 `99136ca` and its H `2893bc53`, and nothing here moves or rewrites them. c10 changes only the failed-row rendering, its schema and its witnesses. Task 8c's head gate already observes the c10 head on both platforms: the five macOS producers and the canonical Linux container, tidy clean at 37/37, E3 inside `biv_tests`, every ctest row but harness-selftest passed (R-4.83's property, taken from the whole row census rather than inside a population branch), and the selftest summary. This block adds only what the head gate does not carry: c10's path set and the censuses c10 could move; the count gate against c9's cells; both skip sets; the macOS `harness-e2` row; the selftest population, which must EQUAL Task 9's (a moved population needs the series and is a STOP routed up, never a lighter pass); the count-cell companion c11 iff c10 moved a tuple; and the FINAL H.

**rev41 (impl-14's STOP).** The re-gate object is the c10t head — c10 plus Task 8d's test-only c10t — because c10's head gate STOPped on the canonical Linux build. Wherever this task says "the c10 head" or "Task 8c's head gate", read the c10t head and Task 8d's head gate at `heads/c10t/`. The block checks c10's path set against Task 8c's Files line AND c10t's against Task 8d's (exactly `tests/test_envelope.cpp`); it requires both mutant records' `verdict=ok`; it compares the censuses between c9 and c10t; and it proves `git diff c10t H` outside the workflow EMPTY.

**Outputs:** everything under a fresh `$EVID/R/` (created by plain `mkdir`, so an existing directory or a symlink STOPs — R-4.82's form), `$EVID/commits.c11.txt` iff c11 lands, and `heads/c11/` from the head gate iff c11 lands. `R/H.txt` is written LAST and is the object the three owner byte reviews, the GO and Task 10 bind.

- [ ] **Step 1: run the block** — `bash` the block `regate.sh` (extracted from this plan by `plan_blocks.py extract`) ONCE from the worktree, with `EVID` and `RUNNERS` exported as the token names them. A STOP ends the token: report it with its line and receipts, never retry, never weaken a predicate.
- [ ] **Step 2: record** — the IMPL return enumerates c10's and c10t's paths (and c11's, iff it landed) against their Files lines and quotes `R/H.txt`.

<!-- BLOCK: regate.sh -->
```bash
# Task 9b — the re-gate at the c10t head (rev39; rev41: c10 + c10t, impl-14's STOP 231301): usage  bash <this block>  from the worktree with EVID and RUNNERS exported; run ONCE after Task 8d's head gate
set -o pipefail
STOP() { printf 'STOP-regate %s line=%s\n' "$1" "${BASH_LINENO[0]}" >&2; exit 1; }
MAIN=/Users/jack/Programming/bivpak; B=186adf7d67171bd7afe621f39b657a1a113ce299
[ -n "${EVID-}" ] && [ -d "$EVID" ] && [ ! -L "$EVID" ] && [ -n "${RUNNERS-}" ] && [ -d "$RUNNERS" ] || STOP env
[ "$(cat "$RUNNERS/evid.txt")" = "$EVID" ] || STOP evid-pointer
PLAN=$(cat "$RUNNERS/plan-path.txt") || STOP plan-pointer; [ -s "$PLAN" ] || STOP plan-absent
h=0; d=$(shasum -a 256 "$PLAN" | cut -d' ' -f1) || h=$?; [ "$h" -eq 0 ] && [ "$d" = "$(cat "$RUNNERS/plan-lock.txt")" ] || STOP plan-not-the-lock
# the preconditions: HEAD is c10t; its parent is c10; c10's parent is c9, Task 9's FINAL H; Task 9 done; Task 8c's and Task 8d's receipts; the tree clean
z=0; C10T=$(cat "$EVID/commits.c10t.txt") || z=$?; [ "$z" -eq 0 ] && [ -n "$C10T" ] && [ "$(git rev-parse HEAD)" = "$C10T" ] || STOP not-at-c10t
z=0; C10=$(cat "$EVID/commits.c10.txt") || z=$?; [ "$z" -eq 0 ] && [ -n "$C10" ] && [ "$(git rev-parse HEAD~1)" = "$C10" ] || STOP parent-not-c10
z=0; C9=$(cat "$EVID/commits.c9.txt") || z=$?; [ "$z" -eq 0 ] && [ -n "$C9" ] && [ "$(git rev-parse HEAD~2)" = "$C9" ] || STOP grandparent-not-c9
[ "$(cat "$EVID/H.txt")" = "H=$C9" ] || STOP task9-H-not-c9
[ "$(cat "$EVID/runners/task-9.done")" = rc=0 ] || STOP task9-not-done
G=$EVID/heads/c10t
[ -s "$G/headgate.txt" ] && [ -s "$EVID/receipts/c10-red.txt" ] && [ -s "$EVID/receipts/c10t-red.txt" ] || STOP task8c-8d-receipts
g=0; k=$(grep -c -x -F 'verdict=ok' "$EVID/receipts/c10-mutants.rev40.txt") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP task8c-mutants-verdict
g=0; k=$(grep -c -x -F 'verdict=ok' "$EVID/receipts/c10t-mutants.txt") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP task8d-mutants-verdict
g=0; k=$(grep -c -E "^headgate label=c10t head=$C10T tidy_expected=none tidy_findings=0 " "$G/headgate.txt") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP headgate-c10t
git diff --cached --quiet && git diff HEAD --quiet || STOP dirty
u=$(git ls-files --others --exclude-standard); r=$?; [ "$r" -eq 0 ] && [ -z "$u" ] || STOP untracked
# confinement before the first write (rev38's form): R/ and commits.c11.txt absent, no symlink directly under the home, R/ made by a plain mkdir and physically the home's own
for x in R commits.c11.txt; do [ ! -e "$EVID/$x" ] && [ ! -L "$EVID/$x" ] || STOP "exists-$x"; done
f=0; LNK=$(find "$EVID" -maxdepth 1 -type l) || f=$?; [ "$f" -eq 0 ] && [ -z "$LNK" ] || STOP home-symlink
m=0; mkdir "$EVID/R" || m=$?; [ "$m" -eq 0 ] || STOP R-mkdir
p=0; RH=$(cd "$EVID" && pwd -P) || p=$?; [ "$p" -eq 0 ] && [ -d "$EVID/R" ] && [ ! -L "$EVID/R" ] && [ "$(cd "$EVID/R" && pwd -P)" = "$RH/R" ] || STOP R-confined
w=0; printf 'H0=%s\n' "$C10T" > "$EVID/R/H0.txt" || w=$?; [ "$w" -eq 0 ] || STOP w-H0
# (1) c10's path set inside Task 8c's Files line and c10t's EXACTLY tests/test_envelope.cpp, none under src/core/repo; the censuses c10 and c10t could move, compared by CONTENT between c9 and c10t
g=0; git diff-tree --no-commit-id --name-only -r "$C10" > "$EVID/R/c10-paths.txt" || g=$?; [ "$g" -eq 0 ] && [ -s "$EVID/R/c10-paths.txt" ] || STOP c10-paths
o=0; grep -v -x -E 'src/core/open/open\.cpp|src/core/report/envelope\.(hpp|cpp)|src/cli/url_consent\.(hpp|cpp)|schemas/biv-json-envelope\.v1\.schema\.json|harness/selftest/test_envelope\.py|tests/test_cli\.cpp|tests/test_envelope\.cpp|CMakeLists\.txt' "$EVID/R/c10-paths.txt" > "$EVID/R/c10-paths.foreign" || o=$?; [ "$o" -eq 1 ] && [ ! -s "$EVID/R/c10-paths.foreign" ] || STOP c10-foreign-path
g=0; git diff-tree --no-commit-id --name-only -r "$C10T" > "$EVID/R/c10t-paths.txt" || g=$?; [ "$g" -eq 0 ] && [ "$(cat "$EVID/R/c10t-paths.txt")" = tests/test_envelope.cpp ] || STOP c10t-paths
CEN() { local tag=$1 pat=$2 T; for T in "$C9" "$C10T"; do local g=0; git grep -n -E "$pat" "$T" -- src ':!src/core/repo' > "$EVID/work/regate-$tag-$T.raw" || g=$?; [ "$g" -le 1 ] || STOP "census-$tag"; local s=0; sed -E "s/^${T}:([^:]+):[0-9]+:/\1: /" "$EVID/work/regate-$tag-$T.raw" > "$EVID/work/regate-$tag-$T.txt" || s=$?; [ "$s" -eq 0 ] || STOP "census-strip-$tag"; done
  local d=0; diff "$EVID/work/regate-$tag-$C9.txt" "$EVID/work/regate-$tag-$C10T.txt" > "$EVID/R/census-$tag.delta" || d=$?; [ "$d" -eq 0 ] || STOP "census-moved-$tag"; }
CEN E2 'repo::(discover|classify|run_eligibility|capture|restore_entry)\('
CEN closure 'invoke_git\('
CEN network 'GitCallClass::network'
g=0; git grep -n -E 'posix_spawn|execv|popen|std::system|fork\(' HEAD -- src ':!src/core/repo' ':!src/core/support' > "$EVID/R/S1-nospawn.txt" || g=$?; [ "$g" -eq 1 ] && [ ! -s "$EVID/R/S1-nospawn.txt" ] || STOP S1-nospawn
g=0; grep -n -E 'facts\.(op|repo|requested|effective)' src/cli/url_consent.cpp > "$EVID/R/a8-facts-lines.txt" || g=$?; [ "$g" -eq 0 ] && [ -s "$EVID/R/a8-facts-lines.txt" ] || STOP a8-facts
g=0; k=$(grep -c -v 'consent_display(' "$EVID/R/a8-facts-lines.txt") || g=$?; [ "$g" -le 1 ] && [ "$k" -eq 0 ] || STOP a8-raw-fact
z=0; git diff --stat "$B" HEAD -- src/core/manifest src/adapters harness/bivharness/e3.py src/core/open/render.cpp > "$EVID/R/zero-byte-fences.txt" || z=$?; [ "$z" -eq 0 ] && [ ! -s "$EVID/R/zero-byte-fences.txt" ] || STOP zero-byte-fences
# (2) every tuple failures=0 on both platforms (a failure count is never a move), the count gate against c9's cells (MOVED rows are data), and both skip sets UNCHANGED
for T in macos linux; do g=0; k=$(grep -c -x -E "biv_[a-z_]+ $T successes=[0-9]+ failures=0 expectedFailures=0 skips=[0-9]+ xml_sha256=[0-9a-f]{64}" "$G/tuples-$T.txt") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 5 ] || STOP "tuples-failures-$T"; g=0; k=$(grep -c -E '^biv_' "$G/tuples-$T.txt") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 5 ] || STOP "tuples-rows-$T"; done
c=0; python3 "$EVID/cells.py" .github/workflows/s2-harness.yml > "$EVID/R/c9-cells.txt" || c=$?; [ "$c" -eq 0 ] && [ -s "$EVID/R/c9-cells.txt" ] || STOP c9-cells
for T in macos linux; do c=0; python3 "$EVID/cellgate.py" "$EVID/R/c9-cells.txt" "$T" "$G/tuples-$T.txt" > "$EVID/R/count-gate-$T.txt" 2>&1 || c=$?; printf 'count_gate_%s_rc=%s\n' "$T" "$c" > "$EVID/R/count-gate-$T.rc" || STOP "w-count-gate-$T"; [ "$c" -eq 0 ] || [ "$c" -eq 5 ] || STOP "count-gate-$T"; done
q=0; python3 "$EVID/skipset.py" "$EVID/B-cells.txt" "$G/tuples-macos.txt" macos > "$EVID/R/skipset-macos.txt" || q=$?; [ "$q" -eq 0 ] || STOP skipset-macos
for T in B c10t; do if [ "$T" = B ]; then TF=$EVID/B/tuples-linux.txt; else TF=$G/tuples-linux.txt; fi; g=0; grep -E '^expected_skips_observed linux n=[0-9]+ ' "$TF" > "$EVID/R/skipset-linux-$T.txt" || g=$?; [ "$g" -eq 0 ] || STOP "skipset-linux-$T"; a=0; n=$(awk 'END { print NR }' "$EVID/R/skipset-linux-$T.txt") || a=$?; [ "$a" -eq 0 ] && [ "$n" -eq 1 ] || STOP "skipset-linux-rows-$T"; done
q=0; cmp "$EVID/R/skipset-linux-B.txt" "$EVID/R/skipset-linux-c10t.txt" > "$EVID/R/skipset-linux.cmp" 2>&1 || q=$?; printf 'skipset_linux_rc=%s\n' "$q" > "$EVID/R/skipset-linux.rc"; [ "$q" -eq 0 ] || STOP skipset-linux
# (3) E3 Linux, harness-e2 on both platforms, and the ctest row census at c10t (only harness-selftest may fail; the new witness row ran and passed)
x=0; python3 - "$G/H/biv_tests-linux.xml" > "$EVID/R/E3-linux.txt" <<'PY' || x=$?
import sys, xml.etree.ElementTree as ET
rows = []
for tc in ET.fromstring(open(sys.argv[1], "rb").read()).iter("TestCase"):
    if "[E3]" in (tc.get("tags") or ""):
        o = tc.find("OverallResult")
        rows.append((tc.get("name"), None if o is None else o.get("success")))
if not rows:
    print("E3 cases=0"); sys.exit(3)
for name, ok in rows:
    print("E3 case=%r success=%s" % (name, ok))
sys.exit(0 if all(ok == "true" for _, ok in rows) else 5)
PY
printf 'e3_linux_rc=%s\n' "$x" > "$EVID/R/E3-linux.rc"; [ "$x" -eq 0 ] || STOP E3-linux
x=0; python3 "$EVID/xmlcases.py" ctest-row harness-e2 "$G/H/ctest-linux-H.junit.xml" > "$EVID/R/harness-e2-linux.txt" || x=$?; printf 'harness_e2_linux_rc=%s\n' "$x" > "$EVID/R/harness-e2-linux.rc"; [ "$x" -eq 0 ] || STOP harness-e2-linux
e=0; ctest --preset ci-macos -R '^harness-e2$' --output-on-failure > "$EVID/R/harness-e2-macos.log" 2>&1 || e=$?; printf 'harness_e2_macos_rc=%s\n' "$e" > "$EVID/R/harness-e2-macos.rc"; [ "$e" -eq 0 ] || STOP harness-e2-macos
o=0; grep -E '^fail ' "$G/ctest-status.txt" > "$EVID/R/ctest-failed-c10t.txt" || o=$?; [ "$o" -le 1 ] || STOP ctest-failed-grep
o=0; grep -v -x -F 'fail harness-selftest' "$EVID/R/ctest-failed-c10t.txt" > "$EVID/R/ctest-failed-c10t.foreign" || o=$?; [ "$o" -eq 1 ] && [ ! -s "$EVID/R/ctest-failed-c10t.foreign" ] || STOP ctest-foreign-red
g=0; k=$(grep -c -x -F 'run divergence_envelope_conforms' "$G/ctest-status.txt") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP witness-row-linux
# (4) the selftest population EQUAL to Task 9's, and the bar (a moved population needs the series: a STOP routed up, never a lighter pass)
s=0; sed -n 's/^population=//p' "$EVID/H/selftest-H.kv" > "$EVID/R/selftest-population-task9.txt" || s=$?; [ "$s" -eq 0 ] && [ -s "$EVID/R/selftest-population-task9.txt" ] || STOP population-task9
s=0; sed -n 's/^population=//p' "$G/selftest-H.kv" > "$EVID/R/selftest-population-c10t.txt" || s=$?; [ "$s" -eq 0 ] && [ -s "$EVID/R/selftest-population-c10t.txt" ] || STOP population-c10t
p=0; cmp "$EVID/R/selftest-population-task9.txt" "$EVID/R/selftest-population-c10t.txt" > "$EVID/R/selftest-population.cmp" 2>&1 || p=$?; printf 'population_equal_rc=%s\n' "$p" > "$EVID/R/selftest-population.rc"; [ "$p" -eq 0 ] || STOP population-moved
rcL=$(cat "$G/H/ctest-linux-H.rc") || STOP rcL; [ -n "$rcL" ] || STOP rcL-empty
hsum=$(sed -n 's/^summary=//p' "$G/selftest-H.kv"); nfail=$(sed -n 's/^failed=//p' "$G/selftest-H.kv"); nf=$(sed -n 's/^names_count=//p' "$G/selftest-H.kv"); [ -n "$hsum" ] && [ -n "$nfail" ] && [ -n "$nf" ] || STOP selftest-kv
o=0; grep -v -x -F -f "$EVID/H/r435-family.txt" "$G/selftest-H.names" > "$EVID/R/linux-selftest-foreign.names" || o=$?; [ "$o" -le 1 ] || STOP foreign-names
bar=fail; if [ "$rcL" -eq 0 ]; then bar=pass-green; elif [ "$rcL" -ne 8 ]; then bar=fail-not-the-one-row; elif [ "$hsum" != parsed ] || [ "$nf" -lt 1 ] || [ "$nf" -ne "$nfail" ]; then bar=stop-invalid-candidate-result; elif [ -s "$EVID/R/linux-selftest-foreign.names" ]; then bar=fail-foreign-selftest-red; else bar=pass-r435-disclosed-registered-red; fi
printf 'rcL=%s summary=%s failed=%s names=%s bar=%s\n' "$rcL" "$hsum" "$nfail" "$nf" "$bar" > "$EVID/R/linux-selftest-bar.txt" || STOP w-bar
case "$bar" in pass-green|pass-r435-disclosed-registered-red) :;; *) STOP "bar-$bar";; esac
# (5) the companion count-cell commit c11 INSIDE the block iff c10t's tuples differ from c9's cells; its head gated by headgate.sh; then the FINAL gates against HEAD's own cells
p=0; python3 "$EVID/cellpatch.py" "$EVID/B-workflow.yml" "$G/tuples-macos.txt" "$G/tuples-linux.txt" > "$EVID/work/s2-harness.regate.yml" || p=$?; [ "$p" -eq 0 ] && [ -s "$EVID/work/s2-harness.regate.yml" ] || STOP cellpatch
c=0; cmp -s "$EVID/work/s2-harness.regate.yml" .github/workflows/s2-harness.yml || c=$?
if [ "$c" -eq 0 ]; then
  printf 'unchanged-since-c9\n' > "$EVID/R/count-gate.txt" || STOP w-count-gate
elif [ "$c" -eq 1 ]; then
  c=0; cp "$EVID/work/s2-harness.regate.yml" .github/workflows/s2-harness.yml || c=$?; [ "$c" -eq 0 ] || STOP cellpatch-copy
  g=0; git add .github/workflows/s2-harness.yml && git commit -q -m "ci: re-pin case counts at the c10t head (macOS/Linux) -- m-3 count-cell companion" || g=$?; [ "$g" -eq 0 ] || STOP c11-commit
  w=0; git rev-parse HEAD > "$EVID/commits.c11.txt" || w=$?; [ "$w" -eq 0 ] && [ -s "$EVID/commits.c11.txt" ] || STOP w-c11
  g=0; git diff-tree --no-commit-id --name-only -r HEAD > "$EVID/R/c11-paths.txt" || g=$?; [ "$g" -eq 0 ] && [ "$(cat "$EVID/R/c11-paths.txt")" = .github/workflows/s2-harness.yml ] || STOP c11-paths
  HG=$(mktemp "$EVID/work/headgate.regate.XXXXXX") || STOP hg-mktemp; x=0; python3 "$RUNNERS/plan_blocks.py" extract "$PLAN" headgate.sh > "$HG" || x=$?; [ "$x" -eq 0 ] && [ -s "$HG" ] || STOP hg-extract
  x=0; bash "$HG" c11 > "$EVID/R/headgate-c11.out" 2>&1 || x=$?; [ "$x" -eq 0 ] || STOP headgate-c11
  printf 'count-cells-moved: c11 committed\n' > "$EVID/R/count-gate.txt" || STOP w-count-gate
else STOP cellpatch-cmp; fi
c=0; python3 "$EVID/cells.py" .github/workflows/s2-harness.yml > "$EVID/R/H-cells.txt" || c=$?; [ "$c" -eq 0 ] && [ -s "$EVID/R/H-cells.txt" ] || STOP H-cells
for T in macos linux; do c=0; python3 "$EVID/cellgate.py" "$EVID/R/H-cells.txt" "$T" "$G/tuples-$T.txt" > "$EVID/R/count-gate-final-$T.txt" 2>&1 || c=$?; printf 'count_gate_final_%s_rc=%s\n' "$T" "$c" > "$EVID/R/count-gate-final-$T.rc" || STOP "w-final-$T"; [ "$c" -eq 0 ] || STOP "count-gate-final-$T"; done
# (6) the FINAL H: nothing but the workflow's cells between c10t and H, the tree clean, R/H.txt LAST
H=$(git rev-parse HEAD) || STOP head
d=0; git diff --stat "$C10T" "$H" -- . ':!.github/workflows/s2-harness.yml' > "$EVID/R/c10t-H.delta" || d=$?; [ "$d" -eq 0 ] && [ ! -s "$EVID/R/c10t-H.delta" ] || STOP c10t-H-delta
s=0; git status --porcelain > "$EVID/R/status-post.txt" || s=$?; [ "$s" -eq 0 ] && [ ! -s "$EVID/R/status-post.txt" ] || STOP status-post
w=0; printf 'H=%s\n' "$H" > "$EVID/R/H.txt" || w=$?; [ "$w" -eq 0 ] && [ -s "$EVID/R/H.txt" ] || STOP w-H
printf 'regate OK H=%s\n' "$H"
```

### Task 10 — the vehicle (ONLY after the pair Planner's GO relay carrying EXACTLY ONE no-red byte review of H from EACH of m-1, m-3 and m-4 through master): ONE push to ONE pinned destination, ONE draft PR

rev39: H is Task 9b's FINAL H (`R/H.txt`); the final count gates, E3 Linux, both `harness-e2` rows and the population rule are read from `R/` (the population EQUAL, the bar passed), and the container receipts from `heads/c10t/` (rev41) and `B/`. rev41: Step 3's PR body is built by `$EVID/finalize.rev41.py`, produced at the START of the runner — before any gate, push or PR — from THIS plan's `finalize.py` block only when absent (a fresh `mktemp` stage in the confined `work/`, checked regular before and after the extract, digest-checked, then renamed into place) and digest-pinned either way, beside Task 0's sealed `finalize.py`, which is never overwritten. Task 0 sealed its helpers in `helpers.sha256` before rev39 changed the block, so rev39's `finalize.py` edits could never reach the sealed copy; this is the rev37 `series_verdict.rev37.py` pattern.

rev42 (impl-15's Task 10 return `intg-substep2b/IMPL-pair-implementer-20260927-045007.md`: `STOP-task-10 line=73`, the live visibility `PUBLIC` against the required `PRIVATE`, before the hook check, the dry-run, the push and the PR — none of their receipts exists). The operator chose to keep the repository public and publish the branch ("2", 2026-09-27). rev43 folds the implementer's exact-hash MUST-REVISE of rev42 (`intg-substep2b/PLAN-REVIEW-pair-implementer-20260927-151814.md`). MUST-2B-55: every remote read and write now names the one destination, origin's fetch and push URLs must both equal it, and no url.* rewrite may exist. MUST-2B-56: Step 0 also preserves the prior attempt's finalize bytecode, the syntax check writes none, and the Step 0 boundary is stated as the body's first receipt. rev44 folds the implementer's exact-hash MUST-REVISE of rev43 (`intg-substep2b/PLAN-REVIEW-pair-implementer-20260927-162852.md`, MUST-2B-57): the `gh` repository is host-qualified (`github.com/iwnlcern/bivpak`), so `GH_HOST` cannot send the visibility read or the draft PR to a host other than the one the literal git URL pushes to. rev42's three changes, and nothing else in this task moves: Step 0 preserves a prior attempt's `$EVID` files by rename into `attempts/task10-<k>/` with a verified manifest, and STOPs if any push or PR receipt exists; the visibility predicate accepts `PRIVATE` or `PUBLIC`; the EXPOSURE CENSUS runs before the dry-run (Step 1). Measured at the pair Planner's seat before this revision: GitHub's `main` is B, so the push adds exactly the 26 B..H commits; all 26 carry `@local` placeholder identities; the B..H patches have 0 census hits (the H tree's 40 hit files are byte-identical at B, all the `sk-complete`/`sk-structured` false positive, already public on `main`); the real PR body from `finalize.rev41.py` has 0 hits and no local path. The runner re-runs from a NEW runners directory (Step 0′ under the next token, on this revision's lock): the controller's one-shot fence refuses a second run in `s2b-runners-j6w4EX`, whose `task-10.exit` (rc=1) is impl-15's record.

Protocol (e): before `run-task.sh 10` the GO relay's ABSOLUTE path is written into `$RUNNERS/task-10-go.txt` (rev42: by the pair Planner on the operator's word "just cite it, you dont need my typed ack", 2026-09-27; the controller is invoked by its ABSOLUTE path, `"$RUNNERS"/run-task.sh 10` — its line 7 refuses any other `$0`); the runner's FIRST gate binds the GO relay (an engine-filed SITREP in `.relays/intg/intg-substep2b/`, `FROM: intg.pair-planner`, `TO: intg.pair-implementer`, `TASK10_GO: yes`, `TASK10_H: <sha>`, and EXACTLY THREE `OWNER_REVIEW_H: <path> | FROM=<seat> | VERDICT=no-red` lines — one whose seat owner is `m-1`, one `m-3`, one `m-4`, three DISTINCT paths under `../pdc/master/relays/`, each relay carrying `S2B_REVIEW_OBJECT: H=<sha>`, `S2B_REVIEW_SCOPE:` and `S2B_REVIEW_VERDICT: no-red` and no red status line).

- [ ] **Step 0 (rev42; rev43 MUST-2B-56): preserve a prior attempt** — before any receipt the body writes (the generated prologue first publishes the NEW token's own four runner records under `runners/<token>/task-10/`; those are this run's records, never a prior attempt's): every push/PR receipt (`push-dry.txt`, `push-stdout.txt`, `push-stderr.txt`, `push-rc.txt`, `remote-branch-after.txt`, `push-class.txt`, `pr-body.md`, `pr-create.txt`, `pr.rc`) ABSENT or STOP; every earlier-stage file this runner writes that exists (regular, not a link) is renamed into a fresh `attempts/task10-<k>/` with `MANIFEST.pre` and a passing `MANIFEST.verify`, INCLUDING the prior attempt's `__pycache__/finalize.rev41.*.pyc` (rev43). `finalize.rev41.py` itself is NOT renamed: it is the digest-pinned shared helper (`a9eec925…`, verified every run) and stays in place. This runner's syntax check compiles it in memory and writes no bytecode, so no prior byte is rewritten.
- [ ] **Step 1: the owner-set gate, then preconditions** — `[ "$(git rev-parse HEAD)" = "$H" ] || STOP`; the GO relay bound as above with the owner set EXACT (`[ "$n1" -eq 1 ] && [ "$n3" -eq 1 ] && [ "$n4" -eq 1 ] || STOP` on the per-owner line counts; `[ "$nu" -eq 3 ] || STOP` on the distinct-path count); Task 9's final receipts (`count-gate-final-*.rc` both 0; both containers rc 0; E3 Linux rc 0; both `harness-e2` rcs 0; the population rule satisfied by the bar or the series); ONE push destination: `git remote get-url --push --all origin` is EXACTLY one line equal to `https://github.com/iwnlcern/bivpak.git` (`[ "$(cat "$EVID/push-url.txt")" = "$URL" ] || STOP`, rev43); rev43 (MUST-2B-55) ONE destination: `URL=https://github.com/iwnlcern/bivpak.git`, `REPO=github.com/iwnlcern/bivpak` (rev44, MUST-2B-57: host-qualified, so `GH_HOST` cannot re-route `gh repo view` or `gh pr create`); `git remote get-url --all origin` (fetch) is EXACTLY one line equal to `URL`, as is the push URL; `git config --get-regexp '^url\.'` finds nothing in any scope and `git ls-remote --get-url "$URL"` is `URL` (no insteadOf / pushInsteadOf re-routing); every `ls-remote`, the dry-run and the push name `"$URL"`, and `gh repo view` / `gh pr create` name `--repo`/`"$REPO"`; `git ls-remote --heads "$URL" intg/substep2b-wiring` EMPTY; `gh repo view "$REPO" --json visibility` ∈ {PRIVATE, PUBLIC} (rev42: PUBLIC accepted on the operator's word "2", 2026-09-27 — the branch is published to the public repository); rev42's EXPOSURE CENSUS: `git ls-remote "$URL" refs/heads/main` is exactly B (so the push publishes exactly B..H), `git rev-list --count B..H` is 26, every author and committer e-mail in B..H matches `^[a-z0-9.-]+@local$`, and the census alternation over `git log -p B..H` has 0 hits (receipts `exposure-*.txt`); no executable `pre-push` hook.
- [ ] **Step 2: ONE push** — `git push --dry-run --no-tags "$URL" intg/substep2b-wiring` (rev43: the literal destination, and the post-push classifier reads the same `"$URL"`) (the refspec line exactly once) then the one attempt; class a (remote head == H) or STOP; the attempt is SPENT (no retry).
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
# rev42 Step 0: a PRIOR Task 10 attempt's evidence is preserved by rename, never overwritten (impl-15's successor attempt STOPped at the visibility preflight, return 045007); a push or PR receipt from ANY prior attempt is a STOP — a remote act may have happened, and this runner never repeats one
for f in push-dry.txt push-stdout.txt push-stderr.txt push-rc.txt remote-branch-after.txt push-class.txt pr-body.md pr-create.txt pr.rc; do [ ! -e "$EVID/$f" ] && [ ! -L "$EVID/$f" ] || STOP; done
PRE=''; for f in helpers.verify-10.txt task-10-go.txt push-url.txt fetch-url.txt url-rewrite.txt remote-branch-before.txt visibility.txt exposure-remote-main.txt exposure-count.txt exposure-authors.txt exposure-secret.txt work/exposure-patches.txt work/owner-lines.txt work/owner-paths.txt work/owner-paths.uniq; do if [ -e "$EVID/$f" ] || [ -L "$EVID/$f" ]; then [ -f "$EVID/$f" ] && [ ! -L "$EVID/$f" ] || STOP; PRE="$PRE $f"; fi; done
# rev43 (MUST-2B-56): the prior attempt's finalize bytecode (`python3 -m py_compile` under rev41/rev42 wrote it) is part of its byte set and is preserved too; this runner's own syntax check writes no bytecode (below)
for f in "$EVID"/__pycache__/finalize.rev41.*.pyc; do if [ -e "$f" ] || [ -L "$f" ]; then [ -f "$f" ] && [ ! -L "$f" ] || STOP; PRE="$PRE __pycache__/${f##*/}"; fi; done
if [ -n "$PRE" ]; then
  m=0; mkdir -p "$EVID/attempts" || m=$?; [ "$m" -eq 0 ] && [ -d "$EVID/attempts" ] && [ ! -L "$EVID/attempts" ] || STOP
  k=1; while [ -e "$EVID/attempts/task10-$k" ] || [ -L "$EVID/attempts/task10-$k" ]; do k=$((k + 1)); done; AD=$EVID/attempts/task10-$k
  m=0; mkdir "$AD" || m=$?; [ "$m" -eq 0 ] || STOP; m=0; mkdir "$AD/work" || m=$?; [ "$m" -eq 0 ] || STOP; m=0; mkdir "$AD/__pycache__" || m=$?; [ "$m" -eq 0 ] || STOP
  h=0; (cd "$EVID" && shasum -a 256 $PRE) > "$AD/MANIFEST.pre" || h=$?; [ "$h" -eq 0 ] && [ -s "$AD/MANIFEST.pre" ] || STOP
  for f in $PRE; do v=0; mv "$EVID/$f" "$AD/$f" || v=$?; [ "$v" -eq 0 ] && [ ! -e "$EVID/$f" ] && [ -f "$AD/$f" ] || STOP; done
  h=0; (cd "$AD" && shasum -a 256 -c MANIFEST.pre) > "$AD/MANIFEST.verify" 2>&1 || h=$?; [ "$h" -eq 0 ] || STOP
fi
v=0; (cd "$EVID" && shasum -a 256 -c helpers.sha256 > helpers.verify-10.txt 2>&1) || v=$?; [ "$v" -eq 0 ] || STOP
# rev41: the PR-body finalizer, produced beside Task 0's sealed `finalize.py` (never overwritten) from THIS plan's block only when absent (a fresh mktemp stage in the confined work/, checked regular before and after the extract, digest-checked, then renamed into place), digest-pinned either way — before any gate, push or PR
F41=$EVID/finalize.rev41.py
if [ ! -e "$F41" ] && [ ! -L "$F41" ]; then
PLANP=$(cat "$RUNNERS/plan-path.txt") || STOP; [ -s "$PLANP" ] || STOP; F41S=$(mktemp "$EVID/work/finalize.rev41.XXXXXX") || STOP; [ -f "$F41S" ] && [ ! -L "$F41S" ] && [ ! -s "$F41S" ] || STOP; x=0; python3 "$RUNNERS/plan_blocks.py" extract "$PLANP" finalize.py > "$F41S" || x=$?; [ "$x" -eq 0 ] && [ -f "$F41S" ] && [ ! -L "$F41S" ] && [ -s "$F41S" ] || STOP
m=0; fs=$(shasum -a 256 "$F41S" | cut -d' ' -f1) || m=$?; [ "$m" -eq 0 ] && [ "$fs" = a9eec92599b4575b4c7b20a68a25da2ef645873fec75d4d7c8d5a30109f609c0 ] || STOP
[ ! -e "$F41" ] && [ ! -L "$F41" ] || STOP; v=0; mv "$F41S" "$F41" || v=$?; [ "$v" -eq 0 ] || STOP
fi
[ -f "$F41" ] && [ ! -L "$F41" ] || STOP
m=0; fs=$(shasum -a 256 "$F41" | cut -d' ' -f1) || m=$?; [ "$m" -eq 0 ] && [ "$fs" = a9eec92599b4575b4c7b20a68a25da2ef645873fec75d4d7c8d5a30109f609c0 ] || STOP
p=0; python3 -c 'import sys; compile(open(sys.argv[1], encoding="utf-8").read(), sys.argv[1], "exec")' "$F41" || p=$?; [ "$p" -eq 0 ] || STOP   # rev43 (MUST-2B-56): compiled in memory, no `__pycache__` write
H=$(sed 's/^H=//' "$EVID/R/H.txt") || STOP; [ -n "$H" ] || STOP   # rev39: the FINAL H is Task 9b's
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
[ "$(cat "$EVID/R/count-gate-final-macos.rc")" = count_gate_final_macos_rc=0 ] && [ "$(cat "$EVID/R/count-gate-final-linux.rc")" = count_gate_final_linux_rc=0 ] || STOP
[ "$(cat "$EVID/heads/c10t/linux-container.rc")" = 0 ] && [ "$(cat "$EVID/B/linux-container.rc")" = 0 ] && [ "$(cat "$EVID/R/E3-linux.rc")" = e3_linux_rc=0 ] && [ "$(cat "$EVID/R/harness-e2-macos.rc")" = harness_e2_macos_rc=0 ] && [ "$(cat "$EVID/R/harness-e2-linux.rc")" = harness_e2_linux_rc=0 ] || STOP
[ "$(cat "$EVID/R/selftest-population.rc")" = population_equal_rc=0 ] || STOP; g=0; k=$(grep -c -E ' bar=(pass-green|pass-r435-disclosed-registered-red)$' "$EVID/R/linux-selftest-bar.txt") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP   # rev39: the lighter re-gate admits only an EQUAL population
# rev43 (MUST-2B-55): the ONE destination, named literally in every remote read and write; origin's fetch AND push URLs must each be exactly it, and no url.* rewrite may exist in any git config scope (insteadOf / pushInsteadOf would re-route even a literal URL)
URL=https://github.com/iwnlcern/bivpak.git; REPO=github.com/iwnlcern/bivpak   # rev44 (MUST-2B-57): HOST/OWNER/REPO, so GH_HOST cannot send either gh call (the visibility read, the draft PR) to another host
u=0; git remote get-url --all origin > "$EVID/fetch-url.txt" || u=$?; [ "$u" -eq 0 ] && [ -s "$EVID/fetch-url.txt" ] || STOP; a=0; nf=$(awk 'END { print NR }' "$EVID/fetch-url.txt") || a=$?; [ "$a" -eq 0 ] && [ "$nf" -eq 1 ] && [ "$(cat "$EVID/fetch-url.txt")" = "$URL" ] || STOP
r=0; git config --get-regexp '^url\.' > "$EVID/url-rewrite.txt" || r=$?; [ "$r" -eq 1 ] && [ ! -s "$EVID/url-rewrite.txt" ] || STOP; [ "$(git ls-remote --get-url "$URL")" = "$URL" ] || STOP
u=0; git remote get-url --push --all origin > "$EVID/push-url.txt" || u=$?; [ "$u" -eq 0 ] && [ -s "$EVID/push-url.txt" ] || STOP; a=0; nurl=$(awk 'END { print NR }' "$EVID/push-url.txt") || a=$?; [ "$a" -eq 0 ] && [ "$nurl" -eq 1 ] || STOP
[ "$(cat "$EVID/push-url.txt")" = "$URL" ] || STOP
l=0; git ls-remote --heads "$URL" intg/substep2b-wiring > "$EVID/remote-branch-before.txt" || l=$?; [ "$l" -eq 0 ] && [ ! -s "$EVID/remote-branch-before.txt" ] || STOP
v=0; gh repo view "$REPO" --json visibility -q .visibility > "$EVID/visibility.txt" || v=$?; [ "$v" -eq 0 ] || STOP; case "$(cat "$EVID/visibility.txt")" in PRIVATE|PUBLIC) ;; *) STOP;; esac   # rev42: PUBLIC accepted on the operator's word "2" (2026-09-27) — the branch is published to the public repository
# rev42: the exposure census — what the push publishes, measured before it: the remote main IS B (so exactly B..H is new), exactly 26 commits, every author and committer a placeholder @local identity, zero secret-pattern hits in the B..H patches
l=0; git ls-remote "$URL" refs/heads/main > "$EVID/exposure-remote-main.txt" || l=$?; [ "$l" -eq 0 ] && [ "$(cat "$EVID/exposure-remote-main.txt")" = "$(printf '%s\trefs/heads/main' "$B")" ] || STOP
c=0; n=$(git rev-list --count "$B..$H") || c=$?; [ "$c" -eq 0 ] && [ "$n" -eq 26 ] || STOP; w=0; printf 'commits=%s\n' "$n" > "$EVID/exposure-count.txt" || w=$?; [ "$w" -eq 0 ] || STOP
g=0; git log --format='%ae%n%ce' "$B..$H" > "$EVID/exposure-authors.txt" || g=$?; [ "$g" -eq 0 ] && [ -s "$EVID/exposure-authors.txt" ] || STOP; g=0; k=$(grep -c -v -E '^[a-z0-9.-]+@local$' "$EVID/exposure-authors.txt") || g=$?; [ "$g" -eq 1 ] && [ "$k" -eq 0 ] || STOP
g=0; git log -p "$B..$H" > "$EVID/work/exposure-patches.txt" || g=$?; [ "$g" -eq 0 ] && [ -s "$EVID/work/exposure-patches.txt" ] || STOP; g=0; k=$(grep -c -E 'sk-[A-Za-z0-9]{8,}|-----BEGIN [A-Z ]*PRIVATE KEY|AKIA[0-9A-Z]{16}|ghp_[A-Za-z0-9]{20,}|xox[abprs]-' "$EVID/work/exposure-patches.txt") || g=$?; [ "$g" -eq 1 ] && [ "$k" -eq 0 ] || STOP; w=0; printf 'secret_hits=0\n' > "$EVID/exposure-secret.txt" || w=$?; [ "$w" -eq 0 ] || STOP
[ ! -x "$(git rev-parse --git-path hooks/pre-push)" ] || STOP
# Step 2 — ONE push
y=0; git push --dry-run --no-tags "$URL" intg/substep2b-wiring > "$EVID/push-dry.txt" 2>&1 || y=$?; [ "$y" -eq 0 ] || STOP
g=0; k=$(grep -c -F 'intg/substep2b-wiring -> intg/substep2b-wiring' "$EVID/push-dry.txt") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP
p=0; git push --no-tags "$URL" intg/substep2b-wiring > "$EVID/push-stdout.txt" 2> "$EVID/push-stderr.txt" || p=$?; printf 'push_rc=%s\n' "$p" > "$EVID/push-rc.txt"
o=0; git ls-remote --heads "$URL" intg/substep2b-wiring > "$EVID/remote-branch-after.txt" || o=$?; remote_after=$(cut -f1 "$EVID/remote-branch-after.txt")
if [ "$o" -ne 0 ]; then class=d; elif [ "$p" -eq 0 ] && [ "$remote_after" = "$H" ]; then class=a; elif [ "$p" -eq 0 ]; then class=e; elif [ "$remote_after" = "$H" ]; then class=c; elif [ -z "$remote_after" ]; then class=b; else class=f; fi
printf 'class=%s\n' "$class" > "$EVID/push-class.txt"; [ "$class" = a ] || STOP
# Step 3 — the draft PR
w=0; python3 "$F41" prbody "$EVID" "$B" "$H" > "$EVID/pr-body.md" || w=$?; [ "$w" -eq 0 ] && [ -s "$EVID/pr-body.md" ] || STOP
g=0; k=$(grep -c -E 'sk-[A-Za-z0-9]{8,}|-----BEGIN [A-Z ]*PRIVATE KEY|AKIA[0-9A-Z]{16}|ghp_[A-Za-z0-9]{20,}|xox[abprs]-' "$EVID/pr-body.md") || g=$?; [ "$g" -eq 1 ] && [ "$k" -eq 0 ] || STOP
q=0; gh pr create --repo "$REPO" --base main --head intg/substep2b-wiring --title "pack/open: wire the repo engine and the consent fabric at product scope (sub-step 2b)" --body-file "$EVID/pr-body.md" --draft > "$EVID/pr-create.txt" 2>&1 || q=$?; printf 'pr_rc=%s\n' "$q" > "$EVID/pr.rc"; [ "$q" -eq 0 ] || STOP
exit 0
```

### Task 11 — FINALIZE: the census rehearsal at H0 with the population PRODUCED on H0; the landing declaration; the tracked record `results/s2b-<token>/` sealed AFTER every retained write

- [ ] **Step 1: preconditions** — Task 10 done/exit/proof receipts; push class a; PR created; the results dir absent; the instrument's bytes: `[ "$ACT" = 9c9391d5b57fa51793a5cb777537dc6ed572d0522f1138f38df2c5bddd5d99a6 ] || STOP` (the FULL pinned digest of `results/intg-r449-landing-census.sh`, recorded in the R-4.49 packet §8).
- [ ] **Step 2: the population PRODUCED on H0, then the instrument** — `census_population.sh "$H0" "$EVID/census-raw/H0/population-H0.txt" "$H0"` (rev45: run as `census_population.rev45.sh`, produced from this BLOCK beside Task 0's sealed copy only when absent and digest-pinned `0c7124d7…` either way; one tree row per LINE classified by its FIRST match, the pinned instrument's own rule — the sealed copy emitted one row per MATCH; BLOCK; the same alternation and producer lines the instrument uses; every matched value classified by its sha256 against the two ACCEPTED VALUE DIGESTS carried from the R-4.49 record — class A = the fixture digest at a product path, B = the fixture digest elsewhere, C = the English digest; an unclassifiable value is a STOP naming path:line only, never the text; the file's sections in the instrument's exact form); then the ONE instrument invocation with H0 as the tree ref AND as the sole history ref (its reachable history contains B): `c=0; bash "$INST" "$H0" "$EVID/census-raw/H0/population-H0.txt" "$EVID/census-raw/H0" "$H0" > "$EVID/H/census-rehearsal.log" 2>&1 || c=$?; printf 'census_rehearsal_rc=%s\n' "$c" > "$EVID/H/census-rehearsal.rc"; [ "$c" -eq 0 ] || STOP`.
- [ ] **Step 3: the landing declaration** — `$EVID/receipts/landing-census-declaration.txt`: the two command lines the landing act runs at `main`'s post-merge head under the operator's token — `census_population.rev45.sh <merge> <pop-merge> <merge>` (rev45) then `<INST> <merge> <pop-merge> <out> <merge>` — with the instrument digest, the population producer's digest, and the rule that the population is PRODUCED on the merge object and never carried (the R-4.50 lesson); the pair Planner copies it into the merge packet.
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
H0=$(sed 's/^H0=//' "$EVID/R/H0.txt") || STOP; [ -n "$H0" ] || STOP; H=$(sed 's/^H=//' "$EVID/R/H.txt") || STOP; [ -n "$H" ] || STOP
# Step 1 — the instrument's bytes
INST=$MAIN/docs/sprints/2026-08-27-intg-consent-fabric/results/intg-r449-landing-census.sh; [ -s "$INST" ] || STOP
h=0; ACT=$(shasum -a 256 "$INST" | cut -d' ' -f1); PIPEOK inst-digest; [ -n "$ACT" ] || STOP
[ "$ACT" = 9c9391d5b57fa51793a5cb777537dc6ed572d0522f1138f38df2c5bddd5d99a6 ] || STOP
# rev45: the population producer, produced beside Task 0's sealed `census_population.sh` (never overwritten: its tree arm emitted one row per MATCH where the pinned instrument reads one row per LINE, so a line holding two matches drew `STOP-landing-census reason=tree-delta`) from THIS plan's block only when absent (a fresh mktemp stage in the confined work/, checked regular before and after the extract, digest-checked, then renamed into place), digest-pinned either way — before the population is produced
CP45=$EVID/census_population.rev45.sh
if [ ! -e "$CP45" ] && [ ! -L "$CP45" ]; then
PLANP=$(cat "$RUNNERS/plan-path.txt") || STOP; [ -s "$PLANP" ] || STOP; CPS=$(mktemp "$EVID/work/census_population.rev45.XXXXXX") || STOP; [ -f "$CPS" ] && [ ! -L "$CPS" ] && [ ! -s "$CPS" ] || STOP; x=0; python3 "$RUNNERS/plan_blocks.py" extract "$PLANP" census_population.sh > "$CPS" || x=$?; [ "$x" -eq 0 ] && [ -f "$CPS" ] && [ ! -L "$CPS" ] && [ -s "$CPS" ] || STOP
m=0; cs=$(shasum -a 256 "$CPS" | cut -d' ' -f1) || m=$?; [ "$m" -eq 0 ] && [ "$cs" = 0c7124d75aab4fdb34341bb1027e55f2606c7c5ac28bf3868fbf6536c3a23b19 ] || STOP
[ ! -e "$CP45" ] && [ ! -L "$CP45" ] || STOP; v=0; mv "$CPS" "$CP45" || v=$?; [ "$v" -eq 0 ] || STOP
fi
[ -f "$CP45" ] && [ ! -L "$CP45" ] || STOP
m=0; cs=$(shasum -a 256 "$CP45" | cut -d' ' -f1) || m=$?; [ "$m" -eq 0 ] && [ "$cs" = 0c7124d75aab4fdb34341bb1027e55f2606c7c5ac28bf3868fbf6536c3a23b19 ] || STOP
# Step 2 — the population PRODUCED on H0, then the rehearsal
m=0; mkdir -p "$EVID/census-raw/H0" || m=$?; [ "$m" -eq 0 ] || STOP
p=0; bash "$CP45" "$H0" "$EVID/census-raw/H0/population-H0.txt" "$H0" > "$EVID/H/census-population.log" 2>&1 || p=$?; printf 'population_producer_rc=%s\n' "$p" > "$EVID/H/census-population.rc"; [ "$p" -eq 0 ] && [ -s "$EVID/census-raw/H0/population-H0.txt" ] || STOP
c=0; bash "$INST" "$H0" "$EVID/census-raw/H0/population-H0.txt" "$EVID/census-raw/H0" "$H0" > "$EVID/H/census-rehearsal.log" 2>&1 || c=$?; printf 'census_rehearsal_rc=%s\n' "$c" > "$EVID/H/census-rehearsal.rc"; [ "$c" -eq 0 ] || STOP
g=0; k=$(grep -c -E ' result=PASS$' "$EVID/H/census-rehearsal.log") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP
c=0; cp "$EVID/census-raw/H0/population-H0.txt" "$EVID/H/population-H0.txt" || c=$?; [ "$c" -eq 0 ] || STOP
# Step 3 — the landing declaration
PD=$(shasum -a 256 "$CP45" | cut -d' ' -f1); PIPEOK producer-digest; [ -n "$PD" ] || STOP
w=0; printf 'landing census declaration (sub-step 2b) — run at main POST-MERGE head <merge> under the operator token, never carried:\n  bash census_population.rev45.sh <merge> <out>/population-merge.txt <merge>   # producer sha256 %s\n  bash intg-r449-landing-census.sh <merge> <out>/population-merge.txt <out> <merge>   # instrument sha256 %s\nrehearsed at H0=%s: producer rc 0, instrument result=PASS; H=%s\n' "$PD" "$ACT" "$H0" "$H" > "$EVID/receipts/landing-census-declaration.txt" || w=$?; [ "$w" -eq 0 ] && [ -s "$EVID/receipts/landing-census-declaration.txt" ] || STOP
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

- [ ] ORDER: this task begins ONLY after the operator's bare merge token has been consumed and the merge head is on `main` (R-4.52) — nothing here runs before the token. The landing census FOR the merge head: the pinned instrument (`9c9391d5…`, Task 11's `census_population.rev45.sh` (rev45) re-run ON THE MERGE HEAD to produce its population; Task 11's declaration consumed, never carried as an expectation) PASS with the merge head as tree and history ref — receipt in `results/s2b-<token>/landing-census.txt`. Then the final pin (`main`'s post-merge head == `origin/main`); the FOUR worktrees disposed with receipts (Task 0's three + `../bivpak-intg-substep2b-wiring` after landing, one receipt); the evidence homes sealed and named (`results/s2b-<token>/` + the R-4.49 record); the open residuals handed to owners BY ROW (T-K, T-C if registered, T-NET, T-PROM, I2B-09 (b), anything an owner STOP left); no further act routes to the pair without a fresh commission.

## Acceptance criteria (each measured, none inferred)

1. `git log --reverse B..H` reads c1a, c1b, c1c (engine only, each at its exact path set) first; BEFORE c7 the ONLY later commits touching `src/core/repo/` are c1d then c1e (rev28), each engine-only at its exact path set, after c6p and before c7, each met once (`H/veto9.txt`); rev33: c8Tr (`src/core/repo/restore.cpp` alone) is the ONLY engine commit AFTER c7, met once, at that path alone, in the Task 8b order c8L < c8Tr < c8T (`H/veto9-order-c8.txt`) — so exactly SIX commits touch `src/core/repo/` (c1a, c1b, c1c, c1d, c1e, c8Tr) and no others; `git diff --unified=0 "$B" HEAD -- src/core/scan/scan.cpp | grep -c -E '^[+-].*"\.biv"'` prints 0 (V-2b-5 rev2 — `--unified=0` and changed lines only: scan.cpp's one UNCHANGED `".biv"` line rides in the default context, 1 there and 0 here at 1065872; an added or removed `".biv"` line is a hit); no commit spans both sets (`H/veto9.txt`); `git diff H0 H -- . ':!.github/workflows/s2-harness.yml'` EMPTY (every H0 receipt carries to H).
2. E2 census non-empty; E5's grep at H0 equals E2's site set exactly; the network-class census CONTENT-identical to B's at c1e's parent and to c1e's at H0 (six engine sites; line numbers may move; rev28: c1e threads the ceiling through restore.cpp's network-class call lines, so its own delta to those lines is recorded as data for m-1's byte review, never compared to B); `invoke_git(` and every spawn primitive absent outside `src/core/repo`/`src/core/support`.
3. Every FX leg named in the evidence matrix has a `legs/<id>.txt` receipt with `provenance=product-packed verdict=PASS`, or a line in `legs/registered.txt` naming its S-6 owner; the open-side legs' hand-built interim receipts are NOT cited by the packet.
4. a8·1–a8·4 pass on all eleven rows; the A8 census shows every bound value wrapped exactly once; `render.cpp` diff EMPTY; the table header carries `Unicode 15.0.0` + both input digests + the generator digest, and regenerating from `tools/` reproduces it byte-for-byte.
5. The hook install has three rows and no `json`/`offline`/`network` term; `grep -c 'isatty(' src/cli/main.cpp` == 0.
6. `UnclaimedGitEntry` lands only with A9's lock id in its commit message (exit map 29 → 29 at c6a); the nine A11 kinds land only with A11's lock id (exit map 29 → 38, ErrKind 28 → 37, transitional 3 → 6 — asserted BY MEMBERSHIP, A11 rev11 — at c6b); `result.repos` + its schema row land only with A10's lock id in ONE commit (c4b); `RepoDiscoveredUnsupported` absent from `src/`, `schemas/`, `tests/`; no engine failure reaches a verb as `InternalError` at H (V-A11-1) and no unknown kind is mapped; every fence fixture packs NO image; the selftest pins recomputed in the same commits that changed the schema bytes.
7. Count gate: observed case tuples at H0 on both platforms equal the workflow cells at H (after c9 iff owed; `count-gate-final-*.rc` both 0); skip sets unchanged on both platforms (a change is a STOP; macOS against B's pinned names, Linux — where B pins none — H0's observed set against B's, rev36); the Linux single-sample bar `pass-green` or `pass-r435-disclosed-registered-red` when the harness-selftest population is equal at B and H0, OR the 015244 series' `VERDICT NOT-SHIFTED` (K-1/K-2 clean; K-3 not shifted) when it moved.
8. E3 receipts on both platforms; E4 parity receipt; the harness receipt on BOTH targets (`harness-e2` green at H0 on macOS and inside the Linux container; m-3's commit EXACTLY rev3's twelve paths, authored `m-3.planner`, `harness/bivharness/e3.py` untouched — `receipts/harness-patch.txt`).
8b. Every runner proof reports `gates>0`; the Task 9 runner controls (PIPEOK must-be-NO, unwritable write, partial-output producer) all STOPped where they must; the RepoEntry census controls fired / did not fire as declared.
9. Cut-point `origin/main..B` = 0 at Task 0; ONE push destination (`https://github.com/iwnlcern/bivpak.git`, exactly one push URL line); the branch pushed class a; the PR open (draft) against `main` with head H; `main` NOT pushed by this plan; the three worktrees disposed with receipts.
10. EXACTLY one no-red byte review of H from EACH of m-1, m-3 and m-4 (unique relay paths under `../pdc/master/relays/`, each carrying the object, scope and verdict lines) bound by the GO relay BEFORE Task 10 (protocol (e) in the runner).
11. The census rehearsal at H0: the population PRODUCED on H0 by `census_population.rev45.sh` (rev45: from the plan's BLOCK, beside the sealed copy, pinned `0c7124d75aab4fdb34341bb1027e55f2606c7c5ac28bf3868fbf6536c3a23b19`; one tree row per line; every matched value classified A/B/C by digest; an unclassifiable value is a STOP), the pinned instrument (`9c9391d5b57fa51793a5cb777537dc6ed572d0522f1138f38df2c5bddd5d99a6`) PASS with H0 as tree and history ref; the merge-head declaration written for the landing act.

12. (rev22, R-4.65) c6m: `c6m-writes.txt` names every writer into the partial and the pass follows the last; the source-order oracle names the pass between `restore_repos` and `fsync_tree`; `[c6m]`'s network case RED at the c6b head and GREEN at c6m, its offline twin green at both (`c6m-mutant.txt`). c6p: the T-RED1 gate's pre and post receipts present, their relay lines equal; the `[c6p]` member sets EXACT (non-root, prune, root); P1–P4 green with byte/mode/mtime fidelity; H1–H6 as stated; M1a/M1b/M1r/M3/M4/M5/M6/M7 RED as stated (`c6p-mutants.txt`); P4's two status assertions (V1-12); `.biv` scan check 0; the RepoEntry census rc 0; no commit rewrites c4a or c5. (rev26) c6q: `[c6q]` RED at the c6m head (`c6q-mutants.txt`) and GREEN at c6q — the member set EXACT with multiplicity, the round trip byte/mode/mtime-equal with and without `--offline`, zero git on open; Mq1–Mq4 RED as stated; no bare `payload/` member in any image (the ROOT cases, rev27).

13. (rev28, R-4.72) c1d: the R-4.72 gate's `c1d` pre and post receipts present and their nine relay lines equal; `[c1d]` (W-U1..W-U6) RED at the c6p head and GREEN at c1d; the two named mutants RED as stated (`c1d-mutants.txt`). c1e: the gate's `c1e` receipts, their relay lines equal to `c1d`'s pre; `[c1e]` (W-C1..W-C6, W-C3s) green; Mc1, Mc1b, Mc2, Mc3, Mc4, Mc5, Mc6 RED as stated (`c1e-mutants.txt`); the landed `url-real-clone-population` case green (the EC-4 coupling control). c7: every pack-grain M leg on REAL config with no shim; every open-grain consent leg's receipt carrying `detection=shim`; the ISO legs green; `c7-product-mutants.txt` shows c1d reverted ⇒ M (a), M (h) and W-U2's product form RED, and c1e reverted ⇒ W-1′, W-C3 and W-5 RED; E3 at the pack verb on both platforms; the mixed-endpoint observation and the notice clause asserted nowhere. c6p additionally: the rev26 gate's pre and post receipts, their seven relay lines equal; the (c) cases CALL the `detail` functions; W2/W3/W5/FP1/FP2/H6b and the PAYLOAD-ONLY + PENUMBRA multiplicity as stated; M3 (as redefined), M6, M6′, M7, M8, M9, M10, M11 RED as stated; no commit rewrites c6m or c6q.

14. (rev33) Task 8b: each of c8L, c8Tr, c8T applied VERBATIM from its census patch (sha256-bound, `receipts/<label>-commit.txt`) to the tree pinned in the block; at each head `heads/<label>/headgate.txt` — the canonical container rc 0, the tidy set byte-equal to the head's pinned list (32 / 31 / EMPTY with the row passed at c8T) with coverage 37/37, macOS five producers rc 0 with `failures=0`, Linux tuples `failures=0`, every other ctest row passed but `harness-selftest`; at c8Tr W-C6 GREEN with Mc5 and M-SEAM RED (`receipts/c8Tr-mutants.txt`); at c8T B1's header reproduced by the tool with exactly its three lines changed (`receipts/c8T-b1-regeneration.txt`) and M-MASK, minimum, M-SEC and B6-swap RED with truncation and B5-bix recorded (`receipts/c8T-mutants.txt`); at H0 the tidy row GREEN with zero findings (`H/tidy-H0.txt`) and, if c9 exists, at H (`H9/c9-gate.txt`); the count gate refused any failure count on both platforms; the R-4.77 series ran with its `FREQ` table (`H/selftest-series.txt`); impl-10's Task 9 outputs preserved byte-identical in `attempts/task9-H0-a83657e/` and impl-11's — with its 36-file B Linux leg — in `attempts/task9-H0-99136ca/` (`H/preserved-attempt.txt` names the latest, MANIFEST.pre == MANIFEST.post in each; `B/` holds exactly Task 0's fifteen before the B leg is re-measured); no NOLINT and no `.clang-tidy` byte in `git diff B H`.

15. (rev39, MUST-H-1) Task 8c: c10 at its Files line only, on top of c9; `receipts/c10-red.txt` shows the three named cases and `divergence_envelope_conforms` RED at c9's product bytes; the same four green at c10; `receipts/c10-mutants.rev40.txt` ends in ONE `verdict=ok` line: M-H1-PRE killed by (w1)'s one case with the conforms row `Not Run` by the fixture, M-H1-SCHEMA killed by the conforms row alone with every case green, M-H1-F4 killed by (w3)'s two cases (rev40); impl-13's rev39 record preserved unchanged; rev41: `heads/c10/` holds impl-14's head-gate STOP (container rc 1, no `headgate.txt`), unchanged — the head gate passes at c10t (item 17).

16. (rev39) Task 9b: `R/` complete — c10's path set inside its Files line and c10t's exactly `tests/test_envelope.cpp` (rev41), the E2 / closure / network censuses unmoved from c9 at c10t; the A8 facts census, the no-spawn and zero-byte fences; the count gate against c9's cells as data; both skip sets unchanged; E3 Linux and `harness-e2` on both platforms rc 0; the selftest population EQUAL to Task 9's and the bar passed; c11 iff moved, its head gated; both final count gates rc 0; `git diff c10t H` outside the workflow EMPTY; `R/H.txt` written LAST.

17. (rev41) Task 8d: c10t on top of c10, `tests/test_envelope.cpp` only, +8/−2, its tree the scout's; `receipts/c10t-red.txt` records the canonical RED from impl-14's retained build log (the 18 missing-initializer errors, nothing foreign); (w3)'s two cases, `biv_tests`, `generated_envelope_conforms` and `divergence_envelope_conforms` green on macOS at c10t; `receipts/c10t-mutants.txt` ends in ONE `verdict=ok` with item 15's three named kills; `heads/c10t/headgate.txt` (tidy EMPTY, coverage 37/37, macOS failures 0, container rc 0, only harness-selftest red, `divergence_envelope_conforms` run and passed). Task 10's PR body comes from `finalize.rev41.py`, produced from this plan's block beside Task 0's sealed `finalize.py` and digest-pinned, and lists every `commits.<label>.txt` in `B..H` order.

18. (rev42; rev43; rev44) Task 10: a prior attempt's files — its `__pycache__/finalize.rev41.*.pyc` included — preserved under `attempts/task10-<k>/` (manifest verified), `finalize.rev41.py` unchanged in place at `a9eec925…`, no bytecode written by this run; `fetch-url.txt` and `push-url.txt` each exactly `https://github.com/iwnlcern/bivpak.git`, `url-rewrite.txt` empty, every remote read and write naming that URL or the host-qualified `github.com/iwnlcern/bivpak` (rev44); no push or PR receipt from any earlier attempt; visibility `PRIVATE` or `PUBLIC`; the exposure receipts (`exposure-remote-main.txt` == B on `refs/heads/main`, `exposure-count.txt` `commits=26`, `exposure-authors.txt` all `@local`, `exposure-secret.txt` `secret_hits=0`) written before the dry-run; then ONE push (class a) and ONE draft PR.

## Out of scope (an act here is a STOP, not a judgement)

Any `src/core/repo` byte beyond Task 1's c1a/c1b/c1c, rev28's c1d/c1e and rev33's c8Tr at their fences; any clang-tidy suppression (a `NOLINT` comment) or `.clang-tidy` change (rev33, master 215035 R2) (m-1 `140916` §2, `150702` §2); a `GIT_DIR` addition (m-1's registered later hardening); any narrowing of the networked-open notice's host-config clause (m-3's registered follow-up, due after the ceiling lands); any relaxation of the restore isolation (m-4 `140901`: it stands); any change to `execute_open`'s signature or to the result-null-iff-error invariant (A11 rev11; a fourth engine diff no fence authorizes); any pack of a dirty, nested or submodule repository SUCCEEDING (Q11; R-4.57); any per-repo exclusion or full+note lane for a fence; any second consent surface, persistence or envelope member for the D3 decision (V-A10-2/4, S-A10-2); any extraction of an overlay row's `local-refs.bundle` (R-4.58); any byte of scan.cpp's `.biv` payload skip (V-2b-5 rev2; ADDENDUM-I unsealed, R-4.55); any `src/core/manifest` byte; any `src/adapters` byte; any `harness/bivharness` byte beyond m-3's c8 commit (rev23: Task 8's three admitted `harness/bivharness` paths exactly, their bytes c8's, bound by Task 9 Step 2; `harness/bivharness/e3.py` never); any `render.cpp` byte; any summary-line or warnings-row emission for consent (S-4); any persistence of an approval; any address classification or safety wording; any new argv/env/config surface beyond the two flags; any envelope member, kind, exit row or wording the sealed texts and the owner cuts do not determine (T-JSON's member and T-KIND's bytes wait on their words); a pack-level FX-O arm; the PR undraft; the merge; the push of `main`; any release act.

REGISTERED, not acts of this plan (rev26): m-4's TOCTOU observation on the lstat-then-create walk — a same-host process racing inside the partial could swap a verified directory between the two calls; a descriptor-relative walk (`openat` with `O_DIRECTORY|O_NOFOLLOW`, then `mkdirat`) would close it for the whole writer (registered at master, not a c6p condition); NESTED payload-only rows (unreachable at 2b — the nested fence refuses every nested pack; c6q writes no nesting logic); an image whose only rows are payload-only, opened on a host with no `git` on `PATH`, fails at `Git::resolve` (a `PATH` lookup, not a spawn — `git.cpp` at `e5afe9d`) although no git would run, which sits against N3's "always restores offline" (reported to master as an observation, not folded; R-4.71, its own act after 2b lands).

REGISTERED, not acts of this plan (rev28, R-4.72; each gating nothing here): R-4.73 (owner m-1, UX arm m-3) — configured-url recording makes a shorthand remote resolved only by an `insteadOf` rule prompt at pack and fail to clone on a host without the rule; SR-URL-5 (m-4 authors; routed by master as the requirement act, SR-URL rev6); m-3's follow-up on the networked-open notice's host-config clause (due after the ceiling lands, with m-4's review; this plan asserts nothing about that clause); an explicit per-call `GIT_DIR` (m-1, optional later hardening); m-3's mixed-endpoint observation (closed by construction under the ceiling, m-4 `144917` (3) — never asserted). MEASURED at the pair Planner's seat (git 2.50.1, isolated HOME, `file://` only) and flagged to m-1 on the digest word, not stops: (i) a config remote with no `url` (a `remote.<n>.fetch` or `pushurl` only) is listed by `git remote`; at B `remote get-url` returns its NAME (rc 0) and the manifest records the name as its url; under c1d's fence `config --get-all` exits 1 and the typed command error refuses the whole pack — the fence states that arm, so W-U6 pins it; legacy `.git/remotes/` and `.git/branches/` remotes are not listed by `git remote` and are reached by neither read; (ii) a plain absolute NON-canonical ceiling entry bounds (git realpaths it) and so does `:` + a canonical entry, so c1e's canonical clause and its no-empty-entry clause are invisible at product scope — W-C3s at the spawn-request seam is their only discriminator (Mc6); (iii) pack runs git at the repository top, where no ceiling value changes discovery, so W-C5's named mutant (the ceiling in `Git::resolve`) is caught only at the seam — the product leg is a behaviour guard; (iv) without the ceiling the CLONE itself still fetched the recorded url at depth 1 and depth 2 below the enclosing repository — what the enclosing config reaches is the gate's `ls-remote --get-url` — so the defect c1e closes is a false divergence at the gate, and W-1′ reds by the refusal, never by fetched content.

## Anti-half-fix guards

- The hook is installed ONCE per verb around the engine-reaching call; a second install site or a call-site-local prompt is red (V-A6-6's shape).
- A refusal at pack is `UrlDivergenceRefused` with facts, never `no_remote`, never a capture-mode change, never an advisory (M veto 4); a refusal at open is a ROW and the clean entries COMPLETE (a6·12).
- `manifest.repos` entries are the engine's objects, unmodified (the RepoEntry census); artifacts keep their `archive_path` (no renaming).
- `.git` is never a payload node; a GIT-CAPABLE repo subtree is excluded WHOLE from the scan walk (its penumbra enters only through c6p's `penumbra_nodes`, rev22); a PAYLOAD-ONLY row's subtree is walked like residue by `scan_subtree` with its `.git` claimed, and is never penumbra-derived (c6q, rev26); an unclaimed `.git` refuses typed with its reason — never a silent skip (V-2b-5/6).
- Offline means ZERO git and ZERO network on open (shim log), and no `ls-remote`/fetch on pack; the flags never touch PROMPT D (V-OFF).
- Hand-built-image receipts are interim; a packet row citing one is a defect.
- c6p lands the pack half and the open half in ONE commit: a pack-only commit makes every non-root penumbra image fail at open (the first pass cannot create a member beneath an unmaterialized repo root). The deferred writer never follows a symlink and never replaces an existing path (V1-3 / V1-4); the directory-mtime pass never stamps a directory the image does not record (V2-3).
- (rev26) c6q lands ALONE before c6p and is complete at its own head (its members land through the first pass; `restore_entry` returns a payload-only row after field validation only). The dot-git predicate is ONE function with TWO call sites, each refusing before its own writer writes; the deferred writer CREATES an absent ancestor only one parent-verified component at a time and never stamps it; neither predicate is gated by configuration, host or filesystem probe.
- The census population is PRODUCED on the object scanned; never carried (R-4.50).
- No `Co-Authored-By` trailer; no root-mode relay-lint sweeps; no Monitor waiters.

## Instruments (BLOCKs — extracted from THIS plan by `plan_blocks.py extract`; the reused ones are byte-copies of the R-4.49 plan's proven instruments with only the act-specific literals changed, each change named)

- `plan_blocks.py`, `run-task.sh` — the runner protocol's two instruments (R-4.49 plan, verbatim except: `plan_blocks.py`'s task-number regexes accept one or two digits and its `list` enumerates the RUN markers actually present (so `task-10`/`task-11` are listed) because this plan's runner tasks are 0, 9, 10, 11; `run-task.sh` accepts N ∈ {0, 9, 10, 11}; the predecessor map is 9←0, 10←9, 11←10; the continuation gate is Task 10's `task-10-go.txt`).
- `resume.sh` (rev17) — protocol step 0′: binds a NEW runners directory to a later token's lock and id while carrying Task 0's receipts and every gate file; run once per later token, before any task; its gates are the ones §Per-task runner protocol states.
- `cells.py`, `tuples.py`, `skipset.py`, `selftest_summary.py` — verbatim. (rev36: `skipset.py` gates macOS only — B's workflow pins no Linux name set and `cells.py` writes that as `expected_skips linux absent `, which `skipset.py` does not parse; Task 9 compares the two Linux observed sets directly.)
- `cellgate.py` — the 2b form: `cellgate.py <cells.txt> <target> <tuples.txt>` exits 0 iff every literal cell equals the observed tuple on `<target>`; prints one `MOVED <binary> literal=… observed=…` line per differing cell (data, not a STOP — a moved `biv_tests` cell is EXPECTED in this act and drives the companion commit) and `UNCHANGED <binary>` otherwise.
- `finalize.py` — verbatim except the finalizer receipts name Task 11, and the `prbody` subcommand (the PR body from the record files). rev41: Task 0 sealed its copy in `helpers.sha256` before rev39 changed the block, so Task 10 runs `$EVID/finalize.rev41.py`, produced from THIS block beside the sealed copy (never overwritten) and digest-pinned — the rev37 `series_verdict.rev37.py` pattern; `prbody` lists every `commits.<label>.txt` in `B..H` order (the rev1–rev40 form listed only the numeric labels c1–c11, omitting c1a–c1e, c3h, c4a/c4b, c6a/c6b/c6m/c6p/c6q, c8L/c8Tr/c8T, c10t and r462). Task 11's `list` and `check` are byte-identical in both copies and keep the sealed one.
- `linux-container.sh` — the R-4.49 container (Phases R / T / S: base provision, the pinned clang-tidy-22 mirror assets, the non-root `suite` user, the branch clone at the expected head, the suite) with Phase L (the read-trace leg) REMOVED, the branch literal `intg/substep2b-wiring`, and labels `B`, `H`, `B-<n>`, `H-<n>` (the series draws).
- `linux-suite.sh` — verbatim except the label set.
- `git-shim.sh` — the request-trace instrument: first on the child's `PATH`, appends `argv` to `$BIV_GIT_TRACE` (one line per spawn, tab-separated, cwd first) and `exec`s the real git named by `$BIV_GIT_REAL`.
- `gen_consent_display_table.py` — the clause-5 table generator (deterministic; input digests and the generator's own digest in the header).
- `series_verdict.py` — the 015244 interleaved-series reducer, the ruling's three clauses IN ORDER and verbatim in meaning: per-draw validity and equal population within each tree (m-3 §6); K-1 membership — every failing test across all 2N draws in the four-member R-4.35 family, else a FRESH FINDING halts; K-2 — any draw with ≥ 5 failures halts; K-3 — SHIFTED iff (landed mean − base mean) ≥ 1.0 OR landed min > base max (rev37: strict — m-4's `K3_TIE: strict`, `master/relays/intg-2b-wiring-act/DESIGN-planner-20260925-151817.md`, carried by master's `…/PLAN-master-planner-20260925-154632.md`; on integer counts the strict arm implies delta ≥ 1.0; Task 9 runs the corrected block from `$EVID/series_verdict.rev37.py`, produced beside Task 0's copy, which stays byte-unchanged as Task 0's record); NOT-SHIFTED is the ONLY release verdict here (the deselection arm is not pre-authorized for this candidate); per-test frequencies reported. Read against `master/relays/r437-pack-timeout-diagnosis/DESIGN-planner-20260903-015244.md` at this seat before rev3.
- `repoentry_census.py` — the TYPE-SCOPED RepoEntry production census (m-1 V-2b-4): enumerates RepoEntry-typed bindings (declarations, vectors and their range-for variables, `Classification::entry` through a Classification binding) and reports any member WRITE on them; exit 5 on a hit; its two controls are run by Tasks 5 and 9.
- `cellpatch.py` — rewrites ONLY the moved `successes`/`skips` literals of the workflow's count cells to the observed tuples (both platform blocks), preserving every other byte; a red observation exits 5.
- `xmlcases.py` — reads a Catch2 XML for the `[E3]`-tagged cases' results and a CTest JUnit for one named row's status (the E3 Linux witness and the `harness-e2` receipts). rev36: the block is unchanged (Task 0 materialized it and `helpers.sha256` pins it), but Task 9 no longer calls its `e3` mode — `(tc.find("OverallResult") or {})` tests an Element's truth value, a childless `<OverallResult>` is falsy, and a green case reads `success=None`; the runner reads the `[E3]` cases itself with `is None`. The `ctest-row` mode stays in use.
- `census_population.sh` (rev45: run as `census_population.rev45.sh`, produced by Task 11 beside Task 0's sealed copy) — PRODUCES the landing-census population ON THE OBJECT SCANNED in the pinned instrument's exact file form (the R-4.49 accepted value digests carried; every matched value classified A/B/C by digest in memory; an unclassifiable value STOPs; no matched text written); the same lines run at landing on the merge head.

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
#   K-3       SHIFT (only if K-1/K-2 pass): SHIFTED iff (landed mean - base mean) >= 1.0 OR landed min > base max (complete separation);
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
shifted = (hmean - bmean) >= 1.0 or min(hc) > max(bc)
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
r=0; RAW=$(git grep -n -E "$ALT" "$TREE" -- .) || r=$?; [ "$r" -eq 0 ] || STOP tree-producer-rc-"$r"
[ -n "$RAW" ] || STOP tree-zero-rows
TMP=$(mktemp) || STOP tmp; : > "$TMP" || STOP tmp-write
nA=0; nB=0; nC=0
while IFS= read -r line; do
  case "$line" in "$TREE:"*) ;; *) STOP tree-row-prefix;; esac
  rest=${line#"$TREE:"}; pl=${rest%%:*}:; rest2=${rest#*:}; ln=${rest2%%:*}; txt=${rest2#*:}; pl=${pl%:}
  m=0; val=$(printf '%s' "$txt" | grep -o -E "$ALT") || m=$?; [ "$m" -eq 0 ] && [ -n "$val" ] || STOP "tree-row-no-match-at-$pl:$ln"; val=${val%%$'\n'*}   # one row per LINE, classified by its FIRST match: the instrument's own rule (its `git grep -n` + `${v%%$'\n'*}`)
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
RTOK=$(cat "$RUNNERS/token-id.txt") || exit 1; case "$RTOK" in intg-substep2b-impl-[1-9]|intg-substep2b-impl-[1-9][0-9]) ;; *) exit 1;; esac
[ -d "$EVID/runners" ] && [ ! -L "$EVID/runners" ] || exit 1; RHOME=$(cd "$EVID" && pwd -P) || exit 1; RRUN=$(cd "$EVID/runners" && pwd -P) || exit 1; [ "$RRUN" = "$RHOME/runners" ] || exit 1; RREC=$RRUN/$RTOK
if [ -L "$RREC" ]; then exit 1; elif [ -e "$RREC" ]; then [ -d "$RREC" ] || exit 1; else m=0; mkdir "$RREC" || m=$?; [ "$m" -eq 0 ] || exit 1; fi; [ -d "$RREC" ] && [ ! -L "$RREC" ] && [ "$(cd "$RREC" && pwd -P)" = "$RREC" ] || exit 1
RFIN=$RREC/task-@N@; [ ! -e "$RFIN" ] && [ ! -L "$RFIN" ] || exit 1; RSTG=$(mktemp -d "$RREC/stage-task-@N@.XXXXXX") || exit 1; [ -d "$RSTG" ] && [ ! -L "$RSTG" ] || exit 1
c=0; cp -p "$RUNNERS/task-@N@.sh" "$RUNNERS/proof-@N@.txt" "$RUNNERS/task-@N@.sha256" "$RUNNERS/task-@N@.invocation.txt" "$RSTG/" || c=$?; [ "$c" -eq 0 ] || exit 1
for RF in task-@N@.sh proof-@N@.txt task-@N@.sha256 task-@N@.invocation.txt; do [ -f "$RSTG/$RF" ] && [ ! -L "$RSTG/$RF" ] && cmp -s "$RUNNERS/$RF" "$RSTG/$RF" || exit 1; done; [ "$(ls -A "$RSTG" | wc -l | tr -d ' ')" = 4 ] || exit 1
[ ! -e "$RFIN" ] && [ ! -L "$RFIN" ] || exit 1; v=0; mv "$RSTG" "$RFIN" || v=$?; [ "$v" -eq 0 ] || exit 1
[ -d "$RFIN" ] && [ ! -L "$RFIN" ] && [ ! -e "$RSTG" ] && [ "$(ls -A "$RFIN" | wc -l | tr -d ' ')" = 4 ] || exit 1; for RF in task-@N@.sh proof-@N@.txt task-@N@.sha256 task-@N@.invocation.txt; do [ -f "$RFIN/$RF" ] && [ ! -L "$RFIN/$RF" ] && cmp -s "$RUNNERS/$RF" "$RFIN/$RF" || exit 1; done
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
# resume.sh — protocol step 0': bind a NEW runners directory to a LATER token (new PLAN_LOCK digest, new DISPATCH_ID, the SAME evidence home) while carrying Task 0's receipts, Task 9's once Task 9 is done (rev39), Task 10's once Task 10 is done (rev46), and every gate file; pre-flight before any write; build unpublished; seal; publish the pointer LAST
# usage: bash resume.sh <EVID> <new PLAN_LOCK sha256> <new DISPATCH_ID>   — run ONCE per later token, before any task under it; prints the NEW runners path as its only stdout line
set -u
NEW=''; SEAL=''; STAGED=''; PUBLISHED=0
# a STOP before publication removes ONLY what this run created and has not published: the seal copy, the staged pointer, the new directory — so a retry starts clean; the old pointer is never touched before the last act; after the mv (= publication) a STOP removes NOTHING
STOP() { printf 'STOP-resume %s line=%s\n' "$1" "${BASH_LINENO[0]}" >&2; if [ "$PUBLISHED" -eq 1 ]; then printf 'resume PUBLISHED before this STOP: nothing removed; read %s/runners-dir.txt by hand (expected %s) and export RUNNERS from it; a rerun STOPs same-lock by design\n' "$EVID" "$NEW" >&2; fi; if [ "$PUBLISHED" -eq 0 ]; then if [ -n "$SEAL" ] && [ -e "$SEAL" ]; then case "$SEAL" in */runners/resume-intg-substep2b-impl-*) rm -rf "$SEAL";; esac; fi; if [ -n "$STAGED" ] && [ -e "$STAGED" ]; then case "$STAGED" in */runners-dir.txt.new-*) rm -f "$STAGED";; esac; fi; if [ -n "$NEW" ] && [ -d "$NEW" ]; then case "$NEW" in "$HOME"/Programming/bivpak-evidence/s2b-runners-*) rm -rf "$NEW";; esac; fi; fi; exit 1; }
EVID=${1-}; NEWLOCK=${2-}; NEWTOKEN=${3-}
[ -n "$EVID" ] && [ -d "$EVID" ] && [ -d "$EVID/runners" ] && [ -d "$EVID/code" ] || STOP evid
printf '%s' "$NEWLOCK" | grep -q -E '^[0-9a-f]{64}$' || STOP lock-form
printf '%s' "$NEWTOKEN" | grep -q -E '^intg-substep2b-impl-[0-9]+$' || STOP token-form
# pre-flight: every check before any write
OLD=$(cat "$EVID/runners-dir.txt") || STOP old-pointer; [ -n "$OLD" ] && [ -d "$OLD" ] || STOP old-runners-absent
PLAN=$(cat "$OLD/plan-path.txt") || STOP plan-pointer; [ -s "$PLAN" ] || STOP plan-absent
h=0; d=$(shasum -a 256 "$PLAN" | cut -d' ' -f1) || h=$?; [ "$h" -eq 0 ] && [ "$d" = "$NEWLOCK" ] || STOP plan-not-the-new-lock
OLDLOCK=$(cat "$OLD/plan-lock.txt") || STOP old-lock; [ -n "$OLDLOCK" ] && [ "$OLDLOCK" != "$NEWLOCK" ] || STOP same-lock
[ -s "$OLD/task-0.done" ] && [ "$(cat "$OLD/task-0.done")" = rc=0 ] || STOP task-0-not-done
c=0; cmp "$OLD/task-0.done" "$EVID/runners/task-0.done" >&2 || c=$?; [ "$c" -eq 0 ] || STOP task-0-done-mismatch
h=0; s=$(shasum -a 256 "$OLD/task-0.sh" | cut -d' ' -f1) || h=$?; r=$(cut -d' ' -f1 "$OLD/task-0.sha256") || STOP task-0-sha-read; [ "$h" -eq 0 ] && [ -n "$r" ] && [ "$s" = "$r" ] || STOP task-0-sh-altered
c=0; cmp "$OLD/task-0.sh" "$EVID/runners/task-0.sh" >&2 || c=$?; [ "$c" -eq 0 ] || STOP task-0-sh-mismatch
[ "$(cat "$OLD/evid.txt")" = "$EVID" ] || STOP evid-pointer
for f in proof-0.txt task-0.sha256 task-0.invocation.txt task-0.exit task-0.proof-tail task-0.self.sha256 plan-hash-0.txt plan_blocks.sha256-0; do [ -s "$OLD/$f" ] || STOP "receipt-absent-$f"; done
# rev39: once Task 9 is done in the previous directory its receipts are carried (Task 10's controller requires task-9.done in the directory it runs from); each bound to the controller's copies in $EVID/runners/ and to the prologue records of the token that ran it
T9=0; if [ -e "$OLD/task-9.done" ] || [ -L "$OLD/task-9.done" ]; then T9=1; [ -f "$OLD/task-9.done" ] && [ ! -L "$OLD/task-9.done" ] && [ "$(cat "$OLD/task-9.done")" = rc=0 ] || STOP task-9-not-done
  for f in task-9.done task-9.exit proof-9.tail plan_blocks.sha256-9; do c=0; cmp "$OLD/$f" "$EVID/runners/$f" >&2 || c=$?; [ "$c" -eq 0 ] || STOP "task-9-copy-mismatch-$f"; done
  h=0; s=$(shasum -a 256 "$OLD/task-9.sh" | cut -d' ' -f1) || h=$?; r=$(cut -d' ' -f1 "$OLD/task-9.sha256") || STOP task-9-sha-read; [ "$h" -eq 0 ] && [ -n "$r" ] && [ "$s" = "$r" ] || STOP task-9-sh-altered
  # rev40: the records of the ONE token whose Task 9 run these are, found by content (impl-12 ran Task 9; impl-13's directory carried it; impl-14 resumes from impl-13's)
  n=0; for td in "$EVID"/runners/intg-substep2b-impl-*/task-9; do [ -d "$td" ] && [ ! -L "$td" ] || continue; m=1; for f in task-9.sh proof-9.txt task-9.sha256 task-9.invocation.txt; do cmp -s "$OLD/$f" "$td/$f" || m=0; done; [ "$m" -eq 0 ] || n=$((n + 1)); done
  [ "$n" -eq 1 ] || STOP "task-9-record-owner-$n"
  for f in task-9.proof-tail task-9.self.sha256 plan-hash-9.txt; do [ -s "$OLD/$f" ] || STOP "receipt-absent-$f"; done
fi
# rev46: once Task 10 is done in the previous directory its receipts are carried too (Task 11's controller requires task-10.done in the directory it runs from; without them a resumed directory STOPs at the controller's predecessor check); bound exactly as Task 9's: the controller's copies in $EVID/runners/, the runner's own digest, and the prologue records of the ONE token that ran it, found by content
T10=0; if [ -e "$OLD/task-10.done" ] || [ -L "$OLD/task-10.done" ]; then T10=1; [ "$T9" -eq 1 ] || STOP task-10-without-task-9; [ -f "$OLD/task-10.done" ] && [ ! -L "$OLD/task-10.done" ] && [ "$(cat "$OLD/task-10.done")" = rc=0 ] || STOP task-10-not-done
  for f in task-10.done task-10.exit proof-10.tail plan_blocks.sha256-10; do c=0; cmp "$OLD/$f" "$EVID/runners/$f" >&2 || c=$?; [ "$c" -eq 0 ] || STOP "task-10-copy-mismatch-$f"; done
  h=0; s=$(shasum -a 256 "$OLD/task-10.sh" | cut -d' ' -f1) || h=$?; r=$(cut -d' ' -f1 "$OLD/task-10.sha256") || STOP task-10-sha-read; [ "$h" -eq 0 ] && [ -n "$r" ] && [ "$s" = "$r" ] || STOP task-10-sh-altered
  n=0; for td in "$EVID"/runners/intg-substep2b-impl-*/task-10; do [ -d "$td" ] && [ ! -L "$td" ] || continue; m=1; for f in task-10.sh proof-10.txt task-10.sha256 task-10.invocation.txt; do cmp -s "$OLD/$f" "$td/$f" || m=0; done; [ "$m" -eq 0 ] || n=$((n + 1)); done
  [ "$n" -eq 1 ] || STOP "task-10-record-owner-$n"
  for f in task-10.proof-tail task-10.self.sha256 plan-hash-10.txt; do [ -s "$OLD/$f" ] || STOP "receipt-absent-$f"; done
fi
if [ -e "$OLD/t-oracle.txt" ]; then g=0; n=$(grep -c -E '^plan_sha256=' "$OLD/t-oracle.txt") || g=$?; [ "$g" -le 1 ] && [ "$n" -eq 1 ] || STOP t-oracle-stale; g=0; k=$(grep -c -x -F -- "plan_sha256=$NEWLOCK" "$OLD/t-oracle.txt") || g=$?; [ "$g" -le 1 ] && [ "$k" -eq 1 ] || STOP t-oracle-stale; fi
[ ! -e "$EVID/runners/resume-$NEWTOKEN" ] || STOP seal-exists
STAMP=$(date +%Y%m%d-%H%M%S) || STOP stamp
[ ! -e "$EVID/runners-dir.prev-$STAMP.txt" ] && [ ! -e "$EVID/runners-dir.txt.new-$STAMP" ] || STOP stamp-collision
# build, unpublished
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
if [ "$T9" -eq 1 ]; then for f in task-9.sh proof-9.txt task-9.sha256 task-9.invocation.txt task-9.exit task-9.done task-9.proof-tail task-9.self.sha256 plan-hash-9.txt plan_blocks.sha256-9 proof-9.tail; do c=0; cp -p "$OLD/$f" "$NEW/$f" || c=$?; [ "$c" -eq 0 ] && [ -s "$NEW/$f" ] || STOP "carry-$f"; c=0; cmp "$OLD/$f" "$NEW/$f" || c=$?; [ "$c" -eq 0 ] || STOP "carry-cmp-$f"; CARRIED="$CARRIED $f"; done; fi
if [ "$T10" -eq 1 ]; then for f in task-10.sh proof-10.txt task-10.sha256 task-10.invocation.txt task-10.exit task-10.done task-10.proof-tail task-10.self.sha256 plan-hash-10.txt plan_blocks.sha256-10 proof-10.tail; do c=0; cp -p "$OLD/$f" "$NEW/$f" || c=$?; [ "$c" -eq 0 ] && [ -s "$NEW/$f" ] || STOP "carry-$f"; c=0; cmp "$OLD/$f" "$NEW/$f" || c=$?; [ "$c" -eq 0 ] || STOP "carry-cmp-$f"; CARRIED="$CARRIED $f"; done; fi
for f in m3-addendum-9-lock.txt m1-fence-rev4.txt m3-help-order.txt t-oracle.txt m3-r462-patch.txt m1-fence-word.txt m3-addendum-10-lock.txt m3-addendum-11-lock.txt m3-harness-patch.txt red1-owner-words.txt r472-owner-words.txt task-10-go.txt; do [ -e "$OLD/$f" ] || continue; c=0; cp -p "$OLD/$f" "$NEW/$f" || c=$?; [ "$c" -eq 0 ] && [ -s "$NEW/$f" ] || STOP "carry-$f"; c=0; cmp "$OLD/$f" "$NEW/$f" || c=$?; [ "$c" -eq 0 ] || STOP "carry-cmp-$f"; CARRIED="$CARRIED $f"; done
h=0; (cd "$NEW" && shasum -a 256 $CARRIED > carried.sha256) || h=$?; [ "$h" -eq 0 ] && [ -s "$NEW/carried.sha256" ] || STOP carried-sha
w=0; printf '%s\n' "$OLD" > "$NEW/previous-runners.txt" || w=$?; [ "$w" -eq 0 ] && [ -s "$NEW/previous-runners.txt" ] || STOP w-prev
w=0; printf '%s\n' "$OLDLOCK" > "$NEW/previous-lock.txt" || w=$?; [ "$w" -eq 0 ] && [ -s "$NEW/previous-lock.txt" ] || STOP w-prev-lock
m=0; mkdir "$NEW/seal" || m=$?; [ "$m" -eq 0 ] || STOP seal-build-dir
c=0; cp -p "$NEW/plan-lock.txt" "$NEW/token-id.txt" "$NEW/previous-runners.txt" "$NEW/previous-lock.txt" "$NEW/carried.sha256" "$NEW/blocks.txt" "$NEW/run-task.sha256" "$NEW/seal/" || c=$?; [ "$c" -eq 0 ] || STOP seal-build-copy
w=0; printf 'resumed token=%s lock=%s from=%s new=%s at=%s\n' "$NEWTOKEN" "$NEWLOCK" "$OLD" "$NEW" "$STAMP" > "$NEW/seal/resume.txt" || w=$?; [ "$w" -eq 0 ] && [ -s "$NEW/seal/resume.txt" ] || STOP seal-build-note
n=$(ls "$NEW/seal" | wc -l | tr -d ' ') || STOP seal-build-count; [ "$n" -eq 8 ] || STOP "seal-build-count-$n"
# seal into the evidence home (no clobber), then publish the pointer LAST
[ ! -e "$EVID/runners/resume-$NEWTOKEN" ] || STOP seal-exists
SEAL=$EVID/runners/resume-$NEWTOKEN; c=0; cp -R "$NEW/seal" "$SEAL" || c=$?; [ "$c" -eq 0 ] && [ -d "$SEAL" ] || STOP seal-copy
n=$(ls "$EVID/runners/resume-$NEWTOKEN" | wc -l | tr -d ' ') || STOP seal-count; [ "$n" -eq 8 ] || STOP "seal-count-$n"
for f in plan-lock.txt token-id.txt previous-runners.txt previous-lock.txt carried.sha256 blocks.txt run-task.sha256 resume.txt; do c=0; cmp "$NEW/seal/$f" "$SEAL/$f" >&2 || c=$?; [ "$c" -eq 0 ] || STOP "seal-$f-mismatch"; done
[ ! -e "$EVID/runners-dir.prev-$STAMP.txt" ] || STOP prev-exists
c=0; cp -p "$EVID/runners-dir.txt" "$EVID/runners-dir.prev-$STAMP.txt" || c=$?; [ "$c" -eq 0 ] && [ "$(cat "$EVID/runners-dir.prev-$STAMP.txt")" = "$OLD" ] || STOP preserve-pointer
STAGED=$EVID/runners-dir.txt.new-$STAMP; w=0; printf '%s\n' "$NEW" > "$STAGED" || w=$?; [ "$w" -eq 0 ] && [ "$(cat "$STAGED")" = "$NEW" ] || STOP stage-pointer
m=0; mv -f "$STAGED" "$EVID/runners-dir.txt" || m=$?; [ "$m" -eq 0 ] || STOP publish-pointer
PUBLISHED=1; STAGED=''   # the mv IS publication: from here nothing is removed; a failed read-back is a COMPLETED run to verify by hand
v=$(cat "$EVID/runners-dir.txt") || STOP published-verify; [ "$v" = "$NEW" ] || STOP published-verify
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
import hashlib, os, re, subprocess, sys
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
        labels = [f[len("commits."):-len(".txt")] for f in os.listdir(evid) if re.fullmatch(r"commits\.(c[0-9]+[A-Za-z]*|r462)\.txt", f)]
        order = subprocess.run(["git", "rev-list", "--reverse", base + ".." + head], capture_output=True, text=True, check=True).stdout.split()
        pos = {c: i for i, c in enumerate(order)}
        commits = "\n".join("- %s = %s%s" % (l, rd("commits.%s.txt" % l), "" if rd("commits.%s.txt" % l) in pos else " (NOT in B..H)") for _, l in sorted((pos.get(rd("commits.%s.txt" % l), len(order)), l) for l in labels))
        legs = sorted(f for f in os.listdir(os.path.join(evid, "legs")) if f.endswith(".txt")) if os.path.isdir(os.path.join(evid, "legs")) else []
        body = ["Sub-step 2b: wire biv pack and biv open to the repo engine and the landed consent fabric at product scope (sealed M/N/O, A6/A7/A8/A9, SR-URL; the R-4.47 bar).", "",
                "B (published pin) = %s" % base, "H0 (suite object) = %s" % rd("H0.txt"), "H (branch head) = %s" % head, "", "Commits (veto-9 mechanical order):", commits, "",
                "E2 wiring census:", "```", rd("H/E2-census.txt"), "```", "E5 flip: diff EMPTY (%s)" % ("yes" if rd("H/E5-flip.txt") == "" else "NO"),
                "veto 9:", "```", rd("H/veto9.txt"), "```", "Count gate (final): macOS %s / linux %s; %s" % (rd("H/count-gate-final-macos.rc"), rd("H/count-gate-final-linux.rc"), rd("H/count-gate.txt")),
                "E3 (both platforms): macOS receipt legs/E3.txt; linux %s" % rd("H/E3-linux.rc"), "harness-e2: macOS %s; linux %s" % (rd("H/harness-e2-macos.rc"), rd("H/harness-e2-linux.rc")),
                "Selftest population: %s%s" % (rd("H/selftest-population.rc"), (" ; series " + rd("H/selftest-series.rc")) if os.path.isfile(os.path.join(evid, "H/selftest-series.rc")) else (" ; bar " + rd("H/linux-selftest-bar.txt"))),
                "Re-gate at the c10t head (Task 9b, rev39; rev41): object %s; count gate %s; final macOS %s / linux %s; E3 linux %s; harness-e2 macOS %s / linux %s; population %s; bar %s" % (rd("R/H0.txt"), rd("R/count-gate.txt"), rd("R/count-gate-final-macos.rc"), rd("R/count-gate-final-linux.rc"), rd("R/E3-linux.rc"), rd("R/harness-e2-macos.rc"), rd("R/harness-e2-linux.rc"), rd("R/selftest-population.rc"), rd("R/linux-selftest-bar.txt")),
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

- rev46 (2026-09-28): `resume.sh` and the Step 0′ prose only. The pair Planner's walk of the NEXT token's handoff (Step 0′ from a mirror of the real `s2b-runners-V1jS1t` on the rev45 lock, then the sealed controller `run-task.sh 11` from the new directory) STOPped `STOP-controller-task-11 line=16`: the controller requires `task-10.done` rc=0 in the directory it runs from, and `resume.sh` carried Task 0's and Task 9's receipts but never Task 10's, so every resumed directory orphaned Task 11. rev45 walked Step 0′ and the Task 11 body separately and never the controller between them. `resume.sh` now binds and carries Task 10's eleven receipts exactly as rev39 did Task 9's (the controller's copies, the runner's digest, the one owning token's prologue records by content), only beside a carried Task 9.
- rev45 (2026-09-27): Task 11 and the `census_population.sh` BLOCK only. The pair Planner's pre-token walk of Task 11 on a full clone of the real evidence home (after impl-16's Task 10 returned rc 0: branch pushed at H, draft PR #28) STOPped at the census rehearsal: `STOP-landing-census line=38 reason=tree-delta` at H0 `b3039506`. Root cause: the sealed Task 0 producer's tree arm ran `git grep -n -o` (one row per MATCH) while the pinned instrument runs `git grep -n` (one row per LINE) and classifies each line by its first match; the two sets were identical (81 locations) and the expected list carried 4 extra rows for 3 lines holding two matches. The BLOCK now emits one row per line classified by its first match; Task 11 produces `census_population.rev45.sh` from it beside the sealed copy (never overwritten) only when absent, digest-pinned `0c7124d75aab4fdb34341bb1027e55f2606c7c5ac28bf3868fbf6536c3a23b19` either way (the rev41 `finalize.rev41.py` pattern), and uses it for the population and in the landing declaration. With it the pinned instrument PASSes at H0 and at H, and the whole Task 11 body runs rc 0 on the clone (finalize check rc 0).
- rev44 (2026-09-27): folds the implementer's exact-hash MUST-REVISE of rev43 (`intg-substep2b/PLAN-REVIEW-pair-implementer-20260927-162852.md`, MUST-2B-57), Task 10 only. rev43 pinned the git URL but gave `gh` only `OWNER/REPO`, and `GH_HOST` supplies the host when none is given: the implementer's read-only control sent the unqualified visibility read to the injected host. Now `REPO=github.com/iwnlcern/bivpak`, used by both `gh repo view` and `gh pr create --repo`; the git URL and rewrite gates are unchanged. The Task 0 / Task 9 `gh release download --repo iwnlcern/bivpak` lines are in completed tasks' sealed blocks and do not move.
- rev43 (2026-09-27): folds the implementer's exact-hash MUST-REVISE of rev42 (`intg-substep2b/PLAN-REVIEW-pair-implementer-20260927-151814.md`), Task 10 only. MUST-2B-55: rev42's census read origin's FETCH side and an unqualified `gh repo view` while the push used origin's PUSH URL — split remotes (proved by the implementer's control) would let the census certify one repository and the push mutate another, and the post-push classifier read the wrong one. Now `URL`/`REPO` are pinned; origin's fetch and push URLs must each be exactly `URL`; no `url.*` rewrite (insteadOf / pushInsteadOf, which re-route even a literal URL) may exist in any scope; every ls-remote, the dry-run, the push and the classifier name `"$URL"`; `gh repo view` and `gh pr create` name the repo. MUST-2B-56: rev42's Step 0 missed the prior attempt's `__pycache__/finalize.rev41.cpython-312.pyc`, which the rerun's `py_compile` would rewrite, and claimed "before any `$EVID` write" although the generated prologue writes the new token's runner records first. Now the pyc is preserved, the syntax check compiles in memory, `finalize.rev41.py` is stated as the in-place digest-pinned helper, and the boundary reads "before any receipt the body writes".
- rev42 (2026-09-27): folds impl-15's Task 10 STOP (`intg-substep2b/IMPL-pair-implementer-20260927-045007.md`, `STOP-task-10 line=73`: `gh repo view` returned `PUBLIC`, the gate required `PRIVATE`; nothing pushed). The operator chose to keep the repository public and publish the branch ("2", 2026-09-27). Task 10 only: Step 0 preserves a prior attempt's `$EVID` files by rename (manifest verified) and STOPs on any push/PR receipt; the visibility predicate accepts `PRIVATE` or `PUBLIC`; the exposure census (remote `main` == B, 26 commits, `@local` identities, 0 census hits in the B..H patches) runs before the dry-run. Protocol (e)'s prose records the operator's waiver of the typed act and the controller's absolute invocation (impl-15's first attempt STOPped `controller-invoked-off-path` on `./run-task.sh`, return 044136). Every measurement the census encodes was taken at the pair Planner's seat before this revision. Task 10 re-runs from a new runners directory under the next token (`s2b-runners-j6w4EX` keeps impl-15's `task-10.exit`).
- rev41 (2026-09-26): folds impl-14's STOP (`intg-substep2b/IMPL-pair-implementer-20260926-231301.md`, `STOP-headgate container` at c10). Step 0′ and Task 8c Step 5 passed: `receipts/c10-mutants.rev40.txt` ends in `verdict=ok`, each mutant killed by its named witness. Step 6's one head gate then STOPped in the canonical Linux container on GCC 13 `-Werror=missing-field-initializers` at c10's two new failed-row initializers in `tests/test_envelope.cpp` (`:75`, `:85`), each naming five of `RepoOutcomeRow`'s fourteen members — c8L's class, re-introduced; Task 8c had proved c10 green on macOS only. NEW Task 8d: c10t, `tests/test_envelope.cpp` only (repair-13, pinned at `dbea9b75`, the commit's tree pinned to the scout's), its RED taken from impl-14's retained build log (exactly the 18 errors, nothing foreign), green on macOS, the mutant record re-taken at c10t (block `c10t-mutants.sh`, rev40's block with its head, parent, record and work names moved), and the head gate at c10t (`headgate.sh` gains the `c10t` label). The census was measured before this revision, not inferred from a stopped build: a scout at c10 plus repair-13 passed the whole canonical container (tidy 0 at 37/37, only harness-selftest red, the selftest population EQUAL to Task 9's 1055), macOS tuples equal to c10's, and the mutant record reproduced impl-14's three rows (`results/c10t-scout-20260926/`). Task 9b re-gates the c10t head: `regate.sh` binds HEAD c10t → c10 → c9, both mutant verdicts, `heads/c10t/`, c10t's one path, and the censuses and final delta against c10t. Task 10 reads `heads/c10t/`. A latent rev39 defect, found while tracing Task 10's inputs: Task 0 sealed `finalize.py` in `helpers.sha256` (verified by Tasks 9, 10 and 11) before rev39 edited the block, so rev39's re-gate line and its c10/c11 commit list could never run — the class rev37 met with `series_verdict.py`. Task 10 now produces `finalize.rev41.py` beside the sealed copy (the rev37 pattern) before any gate, push or PR, and its `prbody` lists every `commits.<label>.txt` in `B..H` order; the rev1–rev40 form listed only numeric labels, omitting the veto-9 engine commits c1a–c1e among others. `heads/c10/` stays as impl-14's STOP record. Every other block is unchanged.
- rev40 (2026-09-26): folds impl-13's STOP (`intg-substep2b/IMPL-pair-implementer-20260926-211822.md`, `STOP-c10-mutants survived-M-H1-PRE`). c10 `2291a46` LANDED green at its ten paths, and every mutant was killed by a named witness (M-H1-PRE by (w1), M-H1-SCHEMA by the conforms row, M-H1-F4 by (w3)). But rev39's block demanded a `divergence_envelope_conforms` FAILURE under M-H1-PRE, and CTest reports that consumer `Not Run` whenever the `biv_tests` fixture it requires fails — an assertion rev39's own topology made impossible, in the one arm rev39 disclosed as unwalked. `c10-mutants.sh` rev40: each mutant is killed by the witness it NAMES — the per-mutant record carries both CTest rows' statuses and the failed Catch2 cases by name (exactly (w1)'s one case under M-H1-PRE; zero cases with the conforms row alone `Failed` under M-H1-SCHEMA; exactly (w3)'s two under M-H1-F4). The record is `receipts/c10-mutants.rev40.txt`, ending in ONE `verdict=ok` line written last; impl-13's rev39 record and work directory stay in place, the record pinned by digest. The same STOP exposed a second defect: `regate.sh` gated Task 8c on `[ -s receipts/c10-mutants.txt ]`, which impl-13's FAILED record satisfies. Task 9b now reads the rev40 record's `verdict=ok`. A third defect, found by walking Step 0′ for the NEXT token from a mirror of impl-13's runners directory: rev39's `resume.sh` bound Task 9's records to `$EVID/runners/<the previous directory's token>/task-9/`, which holds only for the FIRST successor after Task 9; from impl-13's directory it STOPs `task-9-record-mismatch`. rev40 binds them by CONTENT to exactly one token's `task-9/` record set. Task 8c resumes at Step 5 (Steps 0–4 EXECUTED under impl-13). Every other block is unchanged, `regate.sh` apart from that one line.
- rev39 (2026-09-26): folds m-3's MUST-H-1 (owner byte review of H `2893bc53`, `../pdc/master/relays/intg-2b-wiring-act/DESIGN-planner-20260926-160359.md`, F1–F5) as carried and widened by master (`PLAN-master-planner-20260926-164725.md`, F4 the load-bearing arm across both doors), under the operator's "lighter regate pls" (2026-09-26). NEW Task 8c: c10, the failed row's `kind` and `detail` rendered and never null, the schema admitting both iff failed, a failed row lacking either a typed `InternalError`; tests first; three gating mutants (block `c10-mutants.sh`); the per-head gate, now the named block `headgate.sh`, with the `c10` / `c11` labels. NEW Task 9b: the re-gate at the c10 head (block `regate.sh`) — the censuses c10 could move, the count gate against c9's cells, both skip sets, E3 and `harness-e2`, the selftest population EQUAL to Task 9's (a moved population is a STOP routed up), the companion c11 iff moved, the FINAL H into `R/H.txt` LAST; R-4.83's whole-census form and R-4.82's plain-`mkdir` form carried for this block. Task 9 stands as EXECUTED (impl-12); nothing in its outputs moves. `resume.sh` carries Task 9's eleven receipts once Task 9 is done (Task 10's controller requires `task-9.done`; the gap would have stopped Task 10 under any later token). Task 10, Task 11 and `finalize.py` read the FINAL H and the re-gate receipts from `R/`. The topology gains c10 and c11; acceptance gains 15 and 16.
- rev38 (2026-09-25): folds MUST-2B-52 of the implementer's exact-hash review of rev37 `82d2780a…` (`intg-substep2b/PLAN-REVIEW-pair-implementer-20260925-171756.md`): rev37's producer redirected the extractor into a FIXED stage name, `work/series_verdict.rev37.stage`, with no lexical-absence check and no regular-file check after the extract, so a planted stage symlink carried the write outside the home before any STOP (reproduced by the implementer: an outside sentinel rewritten, then the symlink renamed into the final name), and a regular stage from an earlier failure was silently truncated. My matrix tested symlinks at the final path only. The stage is now a fresh `mktemp` file in `work/` (never a fixed name, so an earlier failed stage is kept byte-identical rather than truncated), checked regular and empty before the extract and regular and non-empty after it, then digest-checked and renamed. The same class — a `>` onto a fixed name that could be a symlink — also reached the rev29 inputs (`[ ! -e ]` is true for a DANGLING symlink) and every other fixed name Task 9 writes at the home root, in `work/` and in `B/`. So before its first write the runner now proves `work/` and `B/` physically the home's own and finds NO symlink directly under the home, `work/` or `B/`; `H/`, `H9/` and `series/` are made fresh. It also STOPs on a pre-existing `H.txt` or `commits.c9.txt`, joining the existing `series/` and `H9/` absences. m-4's strict rule, master's carry, rev36's approved fixes and every other block are unchanged.
- rev37 (2026-09-25): folds m-4's `K3_TIE: strict` (`master/relays/intg-2b-wiring-act/DESIGN-planner-20260925-151817.md`, the clause's author; carried by master's `…/PLAN-master-planner-20260925-154632.md`, R-4.80 discharged). K-3's separation arm becomes `landed min > base max` at the three sites carrying it: the `series_verdict.py` code line, the block's own K-3 comment, and the instruments description; Task 9 Step 4's "complete separation" wording already said the intent and now names the strict form. m-4's reasons: `015244`'s own SUBJECT said "complete separation", and `>=` treats touching ranges as separated, so two identical constant series read SHIFTED at delta 0.00 (the pair's `142508` probe, reproduced at master), and a near-null series (base [2, 3×9] against landed [3×10], delta 0.10) read SHIFTED too; on integer counts the strict arm implies delta ≥ 1.0, so it never fires without the mean arm, while a real one-failure shift ([2×5, 3×5] → [3×5, 4×5]) still fires. The series runs ALWAYS in Task 9, so an unfolded clause would STOP on a null with certainty. Because Task 0 materialized the old block into `$EVID/series_verdict.py` (pinned by `helpers.sha256`, verified at Tasks 9–11, never overwritten), Task 9 now PRODUCES the corrected block at `$EVID/series_verdict.rev37.py` from this plan when absent (extracted into a `work/` stage, digest-checked, then renamed into place, so a failed extract never leaves a bad file under the final name), pins it by digest either way (`09b6cb7612907972bb9cf340a8ffcbf406a71da1194d034ce45c85de6127d452`), compiles it, and the series calls it. Tasks 0, 10 and 11 and every other block are unchanged; rev36's Task 9 fold (the Linux skip set, the E3 read, the B-leg preservation — master's no-objection `145141`, R-4.81) stands byte-unchanged.
- rev36 (2026-09-25): folds impl-11's Task 9 STOP (`intg-substep2b/IMPL-pair-implementer-20260925-130242.md`; Step 0′ and Task 8b complete — c8L `c47eb322`, c8Tr `889d8130`, c8T `99136ca6`, every head gate rc 0; Task 9 passed its controls, macOS, H0 tidy and BOTH Linux containers, then stopped at derived line 219). The defect is the pair Planner's: Task 0's `cells.py` writes a workflow block that pins no skip names as `expected_skips <target> absent ` by design, B's Linux block pins none, and the pinned `skipset.py` parses only the `n=<k>` form — it raised `IndexError` on B's Linux row; the rev33–rev35 walks never ran Task 9's body past its new lines against the real `B-cells.txt`. Walking every consumer after line 219 on a mirror of the real home found a SECOND latent stop: `xmlcases.py e3` reads a childless `<OverallResult>` as falsy, so the one green `[E3]` case at H0 read `success=None` (rc 5). Delta, Task 9 and its terms only: (1) the Linux skip set UNCHANGED is H0's observed set against B's observed set (`tuples.py`'s sorted line, byte-compared; the `absent` row asserted exactly once first; `H/skipset-linux.rc` joins the fence proofs); macOS stays on `skipset.py`, verbatim; (2) the runner reads the `[E3]` cases itself (`is None`); no helper file under `$EVID` changes, so `helpers.sha256` still verifies at Tasks 9–11; (3) Step 0's preservation also moves the attempt's B Linux leg — every `B/` entry outside Task 0's fifteen macOS records, listed in the stage as `B-leg.names` — so impl-11's attempt publishes as `attempts/task9-H0-99136ca/` with its 36 B files, and after either branch `B/` holds exactly the fifteen (the rev33 guard that STOPped on `B/linux-container.*` is replaced by that assertion). The other consumers after line 219 were run on the mirror unchanged and pass: the B cell gates (both platforms UNCHANGED), the `harness-e2` row, the population read (B 1013, H0 1055 — unequal, so the series governs), `series_verdict.py` parsing real draws (on ten copies each of the one B and one H0 draw it returns K-3 SHIFTED, because equal constant counts satisfy `landed min ≥ base max`; a real series varies — r437's ran 2–4 failures at both trees, NOT-SHIFTED — so the tie is disclosed to master and K-3 is unchanged), and `cellpatch.py` → `cells.py` → the final cell gates (both rc 0, four literals moved). Acceptance 7 and 14 and the PRV row say the same. No product, test, workflow, harness or helper-block byte moves; the Task 10 and Task 11 runners are unchanged.
- rev35 (2026-09-25): folds MUST-2B-51 of the implementer's exact-hash review of rev34 `80ea88f4…` (`intg-substep2b/PLAN-REVIEW-pair-implementer-20260925-065407.md`): rev34 widened acceptance 1's first subject to c8Tr, which put c8Tr under that clause's "after c6p and before c7" modifier while the same sentence placed it after c7; Task 9's Step 2 prose had the same shape. Both are now PARTITIONED by c7 — c1d then c1e are the ONLY engine commits after c1c and BEFORE c7; c8Tr is the ONLY engine commit AFTER c7, at `src/core/repo/restore.cpp` alone, between c8L and c8T, met once; exactly SIX engine commits in all, no spanning. No block, runner or gate byte moves.
- rev34 (2026-09-25): folds MUST-2B-50 of the implementer's exact-hash review of rev33 `7bbd6270…` (`intg-substep2b/PLAN-REVIEW-pair-implementer-20260925-063356.md`): the VETO 9 MECHANICAL global constraint still said "exactly FIVE engine commits … no commit other than those five touches `src/core/repo/**`" while Task 8b, the order rule, Task 9's executable veto and acceptance 1 require c8Tr — now EXACTLY SIX (c1a, c1b, c1c, c1d, c1e, c8Tr), c8Tr at `src/core/repo/restore.cpp` alone, after c7 and between c8L and c8T, the no-spanning rule unchanged; the same exclusive "ONLY c1d then c1e" wording repaired in Task 9's Step 2 prose and acceptance 1. No block, runner or gate byte moves.
- rev33 (2026-09-25): folds impl-10's Task 9 STOP (`intg-substep2b/IMPL-pair-implementer-20260924-201131.md`) and master's rulings `master/relays/intg-2b-wiring-act/PLAN-master-planner-20260924-215035.md` (R1 scope 53, R2 the tidy class inside 2b, R3 the process items and the per-head container gate, R-4.77), `…-224030.md` (Ask A: c8Tr then c8T under veto 9, unamended; R3 corrected — tidy set byte-equal to a pinned list at every intermediate head, GREEN at the landing head; Ask B routed to m-3 / m-1 / m-4; Ask C ratified) and `…-20260925-003436.md` (cell (A): the initializer and c3-hook repairs are ONE test-only commit c8L, because neither order of two commits has a green first head; cell (B): ONE c8T carrying the 22 mechanical repairs, the owners' words and the decoder witnesses, tidy GREEN at its head — T-C8B and c8B dissolved; w1–w3 with their `.biv` twins and their mutants GATING, M-SEC gating on the existing positives, w4 NOT gating with R-4.78 registered to m-3) with the three owner words it carries: m-1 `DESIGN-planner-20260924-224747.md` (B5, B6 amend; the c8Tr conditions), m-3 `DESIGN-planner-20260924-225029.md` (B1, B2 admit; B3, B4 amend), m-4 `DESIGN-planner-20260924-225018.md` (C8T_SECURITY_READ conditions, F-C8T-1, C-U1..C-U4). NEW Task 8b: c8L (six test files incl. the admitted `tests/test_repo_git.cpp`), c8Tr (`restore.cpp` alone, with W-C6 green and Mc5 / M-SEAM red at its head), c8T (ten paths; B1 regenerated by the tool and reproduced; the c8T mutant record), each applied verbatim from the census record at `dfffc4912b721717b152d84960abf1df0c19b253` and each head gated by the canonical container with the tidy list pinned per head (32 / 31 / EMPTY) plus macOS `-r xml` rc 0 with `failures=0`. Task 9: the c8T head and the Task 8b receipts first; then impl-10's `H/`, `H0.txt` and `helpers.verify-9.txt` PRESERVED by staged renames into `attempts/task9-H0-a83657e/` with one publishing rename and manifest verification, a fault rolling back to byte-identical originals; veto 9 admits c8Tr at its exact path and orders the Task 8b commits; the macOS and Linux count gates REFUSE failures; tidy GREEN at H0; the 015244 series ALWAYS (R-4.77's frequency table); the container once more at H when c9 exists. Global constraints: SIX engine diffs; the Linux toolchain at every new head; the count gate refuses failures. Registered defects of mine (212307): no Linux contact before Task 9, and a count gate that admitted a failure count; and (232402) a split walked only at its final head, not at each intermediate head.
- rev32 (2026-09-24): folds the implementer's exact-hash MUST-REVISE of rev31 (`intg-substep2b/PLAN-REVIEW-pair-implementer-20260924-153636.md`): MUST-2B-49 — rev31 copied the four records straight into their final names, so a `cp` that failed after a prefix exited (the post-copy check was never reached) with a partial record under the final names, and the same token could never retry past it; rev31's own paragraph had accepted that state, which 145529 had already ruled out. `PROLOGUE_EVID` now stages the four in a fresh `mktemp -d` directory inside the token directory, verifies it exactly (four entries, regular, non-symlink, `cmp`-equal), and publishes it with one rename onto `task-N/`, re-verified after; a fault leaves `task-N` absent and its own `stage-task-N.*` directory as the fault record; a same-token retry publishes cleanly. The record path moves from `runners/<token-id>/task-N.sh` (etc.) to `runners/<token-id>/task-N/task-N.sh` (etc.); nothing in the plan reads those paths. Only `plan_blocks.py` moves among the BLOCKs; task-0, `resume.sh` and `run-task.sh` byte-identical to rev31.
- rev31 (2026-09-24): folds the implementer's exact-hash MUST-REVISE of rev30 (`intg-substep2b/PLAN-REVIEW-pair-implementer-20260924-145529.md`): MUST-2B-48 — rev30's token record path was not confined: a symlinked `$EVID/runners/<token-id>` sent all four records outside the home (runner rc 0, the body ran, `finalize.py` listed none of them), a dangling `task-N.sh` symlink passed the `-e` test, and the other three names were not tested at all. `PROLOGUE_EVID` now proves `$EVID/runners` real and physically the home's, the token directory real, non-symlink and directly beneath it (plain `mkdir` when absent), all four names lexically absent before the copy and each a regular non-symlink byte-equal file after it; every failure exits before the body. Only `plan_blocks.py` moves among the BLOCKs; task-0, `resume.sh` and `run-task.sh` byte-identical to rev30.
- rev30 (2026-09-24): folds the implementer's impl-9 STOP `intg-substep2b/IMPL-pair-implementer-20260924-143008.md`: Step 0′ published `s2b-runners-IvrESr`, and Task 9's prologue stopped at derived line 11 — its flat copy into `$EVID/runners/` could not replace impl-8's rev28 `task-9.sh` (mode 0500); the multi-source copy wrote the other three names, leaving a mixed flat record. The defect is the pair Planner's: the impl-9 token asserted the re-copy without running the prologue against the home's real state. `plan_blocks.py`'s `PROLOGUE_EVID` now copies into `$EVID/runners/<token-id>/` (form-checked id; refuses a pre-existing `task-N.sh` there); the flat remnants are preserved verbatim and recorded in §Per-task runner protocol. Only `plan_blocks.py` moves among the BLOCKs; the derived task-9 / task-10 / task-11 runners move by that one prologue line; task-0, `resume.sh`, `run-task.sh` and every other BLOCK are byte-identical to rev29.
- rev29 (2026-09-24): folds the implementer's impl-8 STOP `intg-substep2b/IMPL-pair-implementer-20260924-072544.md` (c1d 116697f, c1e f57cd35, c7 9081149, c8 a83657e COMMITTED; Task 9 STOPped at its line 21 before any control or H0): Task 9's two inputs `observer-unset-names.txt` and `llvm-manifest.txt` had a consumer since rev1 and NO producer (the R-4.49/R-4.50 runners' Task 0 producers were never carried; the defect is the pair Planner's). Task 9 now produces both at its head by the R-4.50 plan's own producer lines, each only when absent and digest-pinned either way (source slice 53bbdd42…, manifest 22724f78…, names e12d5d0a…, measured), with B's workflow re-proved against the blob and the status re-proved clean; walked on 2 YES (fresh; idempotent re-run byte-equal) and 10 NO cases each STOPping at its own guard (tuples empty, workflow altered, manifest bytes, source bytes, half-present pair, names bytes, names form, no interpreter, dirty status, a shifted producer range). Task 8 Step 2's class parenthetical corrected as a RECORD (the patch declares A,B,C,D,E,K and E,K; the §5-vs-patch difference routed to m-3 through master). Only Task 9's RUN block moves; every BLOCK, `resume.sh` and every other task byte-identical to rev28.
- rev28 (2026-09-23): folds R-4.72 (the implementer's c7 STOP `intg-substep2b/IMPL-pair-implementer-20260923-133444.md`, verified and widened at `intg-substep2b/SITREP-pair-planner-20260923-134901.md`: at product scope neither verb saw a URL divergence) on master's three carries `…/PLAN-master-planner-20260923-142025.md`, `…-145548.md` and `…-151255.md` — seven owner words: m-1 `R472_PLACEMENT: in-lane` + `R472_MANIFEST_URL: configured` (140916), m-4 `R472_ISOLATION: stands` (140901), m-3 `R472_OPEN_WITNESS: other` (141015), m-4 `R472_ENCLOSING_REPO: ceiling` (144917), m-1 `R472_CEILING_PLACEMENT: own-commit-in-lane` (150702), m-3 `R472_OPEN_WITNESS_REWORD: shim-fallback` (150622). Delta: T-R472 and its gate file `r472-owner-words.txt` (Step 0′'s prose list and `resume.sh`'s carried list — `resume.sh`'s BLOCK moves; the prose list also gains `red1-owner-words.txt`, which the code has carried since rev22 while the list omitted it); VETO 9 MECHANICAL and ENGINE BYTES (five engine commits, m-1's re-ruled mechanical form); the Identity TOKEN line, the boundary contract's ENGINE rows and ZERO BYTES line, the topology rows and ORDER RULE; NEW Task 6e (c1d, m-1's fence, W-U1..W-U6 with W-U6 pinning the fence's stated error arm, the executable R-4.72 gate for c1d / c1e / c7) and Task 6f (c1e, m-1's fence for m-4's EC-1, W-C1..W-C6, W-C3s at the seam, Mc1..Mc6, the EC-4 coupling control); Task 7 — the pack grain on REAL config, the open grain on the labelled shim, the ISO family (W-1′/W-C1..W-C5/W-2/W-4/W-5) with EC-4's other half named, E3 at the pack verb, the F-RESTORE-DIVERGE fixture REMOVED (it contradicted Task 4's rev13 record of the landed isolation — the pair Planner's defect since rev13), Step 4b's product mutants in a disposable worktree, the c7 gate; Task 9 — the network-class census split at c1e (B vs c1e's parent, c1e vs H0; c1e's delta recorded as data) and the veto-9 arm admitting exactly c1d and c1e at their exact path sets by recorded sha, in walk order c6p < c1d < c1e < c7; evidence rows E1-M, E3, WIT-U, ISO; acceptance 1, 2 and 13; Out of scope and the REGISTERED paragraph (R-4.73, SR-URL-5, m-3's notice follow-up, the optional `GIT_DIR`, the mixed-endpoint observation — none asserted, none gating) with four measurements of this seat flagged to m-1. Nothing in Tasks 0–6d moves but their cross-references; the T-ORACLE prefix (Task 4 Step 5) is byte-identical.
- rev27 (2026-09-23): folds the implementer's exact-hash MUST-REVISE of rev26 (`intg-substep2b/PLAN-REVIEW-pair-implementer-20260923-023855.md`): MUST-2B-47 — Task 6q applied `scan_subtree` to EVERY payload-only row and required it to emit the row directory itself, but a ROOT payload-only row canonicalizes to `""` (`scan.cpp:202-205`), so the plan mandated the bare member `payload/`, which the open-side path refuses (`open.cpp:520-523`); the root form was reachable and untested (only non-root `shal` / `fresh`), and Mq3 would have pressed an implementation toward the invalid node. Measured at `e5afe9d` from a clean build: a workspace that is itself a depth-1 clone, and one that is itself a fresh `git init`, each packs rc 0 with ONLY `manifest.json` and `checksums.json` — R-4.70's worst form. Delta, Task 6q only: the Interfaces (the root exception; the root row as the whole workspace), Step 1 (a) ROOT unit case, (b) ROOT-SHALLOW and ROOT-UNBORN member multisets, (c) their round trips with and without `--offline`, Step 2 (the ROOT cases' RED shape), Step 3, Step 4 (Mq4; Mq3 kept for the non-root node), evidence row R2-Q, acceptance 12, this bullet. No BLOCK moves (census 22); Task 6d, its gate and Step 0′ are byte-identical to rev26.
- rev26 (2026-09-23): folds the T-C6P carry `master/relays/intg-2b-wiring-act/PLAN-master-planner-20260923-011148.md` — m-4 `C6P_ABSENT_ANCESTOR: arm-a` (AA-1..4 and F-C6P-1's precondition), m-3 `C6P_V1_READING: confirm` (plus the relpath-component fact), m-1 `C6P_MEMBER_SET: stop` (R-4.70) and master's ruling that the shared dot-git predicate rides c6p at both writers — after the implementer's STOP `intg-substep2b/IMPL-pair-implementer-20260922-181342.md` (rev25's Task 6d P2 was unsatisfiable: the pair Planner's own absent-ancestor refusal, rev22..rev25, aborted every open with a non-materialized row whose penumbra sat under a tracked-only directory). Delta: T-C6P (and pointers in T-RED1); the owner-fence line; NEW Task 6q (c6q, R-4.70: payload-only rows' whole working tree as payload, its own commit, BEFORE c6p) with its topology row, ORDER RULE, evidence row R2-Q and acceptance; Task 6d — the header, Files (`open.hpp`: the `detail` declarations), Interfaces (`owning_row` / `row_relpaths` DECLARED for behavioural tests — rev25's file-local placement had left Step 1 (c) testable only by a search of the source text, the pair Planner's defect; `row_relpaths` git-capable only; the one predicate transcribed from git `3bc0341…`), the Step 0 gate (SEVEN carriers, rev26-named receipts so impl-6's rev25 receipts stay intact), Step 1 ((b) the payload-only multiplicity case; (c) behavioural; (d) P2 now satisfiable, P4's CLI spelling, W2/W3/W5/FP1/FP2/H6b), Step 2 (at the c6q head), Step 3 (the four-stage walk; the first-pass call site; `penumbra_nodes` skips payload-only rows — classify records their `penumbra_paths`), Step 4 (M3 redefined for arm A; M6/M7 re-scoped; M6′, M8, M9, M10, M11; AA-1's race conditions stated as NOT witnessed), Step 5 (receipts, `open.hpp`, message); Task 7 N (a) no longer absence-blind (the pair Planner's leg would have passed with the whole tree dropped) plus H at product scope; Task 6c's `biv open <image> <dest>` spelling (the CLI takes `--dest`); the scan file-structure bullet and the "subtree excluded WHOLE" guard (both now contradicted by R-4.70, amended rather than left standing); Out of scope (three registered items); acceptance 12; this bullet. No BLOCK and no RUN block moves (census 22); Step 0′'s carried list is unchanged (the gate file keeps its name).
- rev25 (2026-09-22): folds the implementer's exact-hash MUST-REVISE of rev24 (`intg-substep2b/PLAN-REVIEW-pair-implementer-20260922-015007.md`): MUST-2B-43 — c6b's landed `open.hpp` enters Task 6b's Files line, its commit block and the c6b topology row as the record, and T-C6B holds the carry request and the next token on master's disposition of the task-scope deviation; MUST-2B-44 — H5 split into a root arm on `payload/.git/c6p-sentinel` (no baseline file; absent afterwards) and a lib arm on the existing `lib/.git/config`, opened `--network`, with M6 discriminating on the root arm's created sentinel; MUST-2B-45 — H6 opened `--network` with unique `payload/.biv` + `payload/.biv/c6p-sentinel` members (not the A10.6 artifact shape), asserted absent afterwards, with M7 discriminating on their creation. MUST-2B-46 was the carrier's stale BRIDGE line (impl-5 for impl-6), fixed on the carrier. Delta: those sites and this bullet; every BLOCK byte-identical to rev24.
- rev24 (2026-09-22): folds the T-RED1 owner words carried by master `master/relays/intg-2b-wiring-act/PLAN-master-planner-20260921-211701.md` — m-3 `…/DESIGN-planner-20260921-200917.md` (`RED1_ROOT_ROW: defer`, root-row veto conditions V1-8..12) and m-1 `…/DESIGN-planner-20260921-200936.md` (`RED1_PENUMBRA_DIRS: confirm`, the recursive rule rev23 already wrote, and the DIRECT-reading mutant on m-1's ground-truth fixture). Delta, Task 6d and its terms only: T-RED1 records the words and what they bind; Step 1 (b)'s root fixture becomes V1-12's verbatim and gains m-1's DIRS fixture with exact directory and file member sets; Step 1 (d)'s P4 becomes V1-12's joint root witness (open `--network` rc 0; `? local.txt` and `! src/a.o` ASSERTED) and gains H5 (V1-10, `.git`-segment members) and H6 (V1-11, `payload/.biv/…`); Step 3's deferred writer refuses both before any write; Step 4 gains M1r (the root's kept first-pass order), M5 (the direct reading, `pack.cpp`), M6, M7; acceptance 12; this bullet. No BLOCK moves (the Task 6d Step 0 gate is unchanged: its three carriers are 211701 / 200917 / 200936). RECORDED, not a plan change: impl-5's return (`intg-substep2b/IMPL-pair-implementer-20260921-224404.md`) landed c4b `cd12bb5`, c6b `cd51937`, c6m `e5afe9d`; c6b's commit carries `src/core/open/open.hpp` (`RepoOutcomeRow` gains `kind` / `detail` — the struct side of the failed row Task 6b's text requires) although Task 6b's Files line and its commit block do not list that path; it is inside impl-5's SCOPE_DIFF, was not disclosed in the return, and is reported to master and to the owners' byte reviews at H.
- rev23 (2026-09-21): folds the implementer's exact-hash MUST-REVISE of rev22 (`intg-substep2b/PLAN-REVIEW-pair-implementer-20260921-173212.md`): MUST-2B-42 — rev22 admitted and required three `harness/bivharness` paths in Task 8 (m-3's rev3 patch) but left Task 9 Step 2's zero-byte fence over the whole `harness/bivharness` directory (runner and prose) and the Out-of-scope clause forbidding every `harness/bivharness` byte, so the valid c8 commit would STOP Task 9 deterministically. Task 9 Step 2 now fences `harness/bivharness/e3.py` with the other zero-byte paths, requires the `harness/bivharness` paths changed since B to be EXACTLY c8's three, and binds their bytes to c8 (the tree at c8's parent equals B's there, and HEAD equals c8's) — three runner lines, each a prose gate span; Out-of-scope forbids only bytes beyond the c8 commit. Delta: those two sites and this bullet; the task-9 block's digest moves (gates 13 → 16); every other block byte-identical to rev22.
- rev22 (2026-09-21): folds master's `master/relays/intg-2b-wiring-act/PLAN-master-planner-20260921-143755.md` and `…-165137.md` — R-4.65's two reds in LANDED lane bytes, both reproduced at master and at m-3's seat, both execution of sealed text: RED-1 (c5 `5aeb81c`: `biv pack` drops a clean repository's `.gitignore`d penumbra silently; pack-engine §1.1/§1.3/§3.2; m-1 141529, which owns V-2b-5's omission) and RED-2 (c4a `ef8e492`: the directory-mtime pass precedes `restore_repos`, so a payload directory above a restored repository loses its archived mtime; restore-apply §5; m-3 164214/164238 CONFIRM, V2-1..6 / V1-1..7). Delta: T-RED2 and T-RED1 (the root-row and directory-member cells HOLD on `$RUNNERS/red1-owner-words.txt`, the pair Planner's STOP 170128 under V1-6); Task 6c (c6m) and Task 6d (c6p, its executable Step 0 gate) inserted after c6b as NEW commits (never a rewrite of c4a / c5); the topology rows and ORDER RULE (c7 after c6p); the boundary contract, file structure and evidence rows R2-M / R1-P; Task 7's workspace-root leg CORRECTED (rev≤21 asserted the ignored file returns "through the engine's penumbra, not payload" — the pair Planner's copy of the same omission) and its R-T leg's precondition stated; Task 8 widened to m-3's rev3 patch — twelve paths, nine admitted outside `harness/scenarios/`, population 1014 → 1055 — with an executable Steps 0–1 block (the pdc-relative path resolved as Task 4 Step 3c resolved R-4.62's); `resume.sh` carries `red1-owner-words.txt`; the HARNESS BYTES constraint, acceptance 8 and new 12, two guards; this bullet. Task 4 Steps 0 / 6–9 and Task 6b are byte-identical to rev21 (impl-4 executes them; the hold point is before c7 — the pair Planner's 170127).
- rev21 (2026-09-20): folds the implementer's exact-hash MUST-REVISE of rev20 (`intg-substep2b/PLAN-REVIEW-pair-implementer-20260920-193911.md`): MUST-2B-41 — two operative terms still carried A11 rev7's rejected arithmetic (the c6b topology row's `ErrKind 27→36`; T-A11's `COUNTS ErrKind 27 → 36 (after A9's 27 → 27) … transitional 4 → 7`), contradicting the locked rev11 composition and Task 6b's own leg (l); both now state the stage-and-membership census (28/29/4 at the pin → 28/29/3 after A9 → 37/38/6 after A9 + A11, the six transitional named). Delta: those two sites and this bullet; no BLOCK moves (census 22, every digest identical to rev20). The rev20 sweep grepped `27->36` and `ErrKind 36` but not the arrow spelling `27 → 36` / `27→36` — the lesson: sweep every spelling of a retired number, not the one you wrote last.
- rev20 (2026-09-20): THE LOCK REVISION — folds master's seal `master/relays/intg-2b-wiring-act/PLAN-master-planner-20260920-185625.md` (A10 rev10 `m3-addendum-10-6cba59d3-lock-20260920`, pin 6cba59d3 @ pdc 5cbb59d7, post-stamp 56abe662, m-3's lock relay 184029; A11 rev11 `m3-addendum-11-fce9cbfa-lock-20260920`, pin fce9cbfa @ 2ce699d7, post-stamp e2776381, m-3's lock relay 184104, `partial_suffix=.bvpk-open.partial` + `partial_suffix_relay` = m-1's 162306; the Master Reviewer's APPROVE-FOR-OWNER-LOCK 182105 and its boundaries) under the RULE (a moved byte between the transcribed and the locked revision is a new plan revision): the A10 rev6→rev10 deltas (ARTIFACT-BEARING := offline-pointer ∧ the engine's artifact-presence fact, never `capture_mode`; the detached form's bare `'HEAD'` refspec + leg (j)'s HEAD-only fixture with the rev7 wildcard-only form as the named failing mutant; `capture_mode` OUTCOME-CONDITIONED — null on shallow-pointer / payload-only-unborn rows; leg (b)'s mixed population; A10.2's regained `--json` / PERSISTENCE / ENCODING rows) transcribed into T-JSON, T-STAGE, T-NET, A10-REV, ROUTED, Task 4's header / Interfaces / Step 3 / Steps 6, 8, 9 and Task 7; the A11 rev5→rev11 deltas (the `.bvpk-open.partial` spelling at the three sites with the suffix READ FROM the lock file; CR as A8-R1's CLAUSE-2 `\r` with the `\u000d` mutant; COUNTS by STAGE and MEMBERSHIP 28/29/4 → 28/29/3 → 37/38/6 with the six transitional named, leg (l) ×3; the INFORMATIVE partial + stage sentence, no policy asked) transcribed into T-PARTIAL, ROUTED (17), Task 6b's header / Files / Step 0 / Steps 1, 4, 5, Task 7 and acceptance 6. The two lock gate files WRITTEN into the canonical runners (`s2b-runners-PEazOQ`), one field per line, with `pin_sha256` / `pin_commit` beside the carrier fields. Task 4 Step 0 becomes an EXECUTABLE gate (Task 6b Step 0's shape with the A10 constants; the pin by `git show`; the seal's lineage a whole-word citation on IN_REPLY_TO / RELATED_CONTEXT, since the one seal replies to A11's lock relay and cites A10's); Task 6b Step 0's block gains the pin binding; Step 9 (c4b) refuses without the post receipt, as Step 5 (c6b) already does; both commit messages spell the lock ids and post-stamp digests (the c6a precedent). The two evidence-command repairs master 121637 accepted: Task 3 Step 8 selects `'[cli-flags]'` (6 cases at 1065872) plus the case c3h's golden lines landed in — `'[cli]'` matched nothing and exited 2; the scan.cpp `".biv"` claim (Task 9 Step 2 prose AND its RUN block line, acceptance 1) measures `git diff --unified=0` on changed lines only — the default context carried the file's one unchanged `".biv"` line and the rev19 block would have STOPped at H on compliant bytes (1 with context, 0 without, at 1065872; an added-literal mutant = 1). Walked at this seat from the candidate at 1065872 with a scratch `$EVID`: the A11 block on the real file pre + post PASS, seven must-be-NO controls STOP before any receipt (wrong doc sha, wrong pin sha, wrong pin commit, seal = lock, the suffix relay without `master/relays/`, the A10 lock relay as `relay`, a duplicated `lock_id` line); the A10 block pre + post PASS, nine must-be-NO controls STOP (wrong doc sha, wrong pin sha, wrong pin commit, seal = lock, a non-citing PLAN as seal, the A11 lock relay as `relay`, the planned-shape id, a duplicated field, a missing field); the Task 9 block's scan.cpp line YES at 1065872 and NO on an added-literal mutant hunk; `bash -n` and extract == reader on every touched block; runner proofs 3 / 13 / 4 / 2. Delta: the lines named above and this bullet; `resume.sh`, `run-task.sh`, the T-ORACLE block and every other BLOCK are byte-identical to rev19.
- rev19 (2026-09-19): folds the implementer's exact-hash MUST-REVISE of rev18 (`intg-substep2b/PLAN-REVIEW-pair-implementer-20260919-224817.md`): MUST-2B-38 — the T-ORACLE pre-flight measured the matching line, not the field's cardinality, so a locator holding a current line beside the stale one passed pre-flight and published, to be refused by Step 5's `field` parser only afterwards; `resume.sh` now requires total `^plan_sha256=` lines == 1 AND exact current lines == 1 before any write. MUST-2B-39 — after the recursive seal copy only the note was compared, so a copier altering any of the seven binding files published; every one of the eight sealed files is now compared byte-for-byte (`seal-<file>-mismatch`). MUST-2B-40 — the `mv` was followed by a fallible read-back inside the unpublished window, so a failed read after a successful `mv` cleaned up the seal and the directory the canonical pointer already named (a dangling pointer, the class MUST-2B-37 closed); the `mv`'s success now IS publication — `PUBLISHED=1` the instant it returns 0, the read-back STOPs `published-verify` with everything retained and a by-hand disposition (the pointer names the new directory; export `RUNNERS` from it; a rerun STOPs `same-lock`). Delta: the Step 0′ paragraph, the `resume.sh` BLOCK, this bullet; nothing else moves. Walked at this seat: the positive through the exact Step-5 T-ORACLE prefix again; the two cardinality negatives (current + stale; two current) STOP `t-oracle-stale` with no write; the `cp` shim on `plan-lock.txt` → `seal-plan-lock.txt-mismatch`, cleaned up, retried to success; the `cat` shim failing the first post-`mv` read → `published-verify` with the pointer at the new directory, the seal and the directory retained, a rerun → `same-lock`; every rev18 mutant re-run.
- rev18 (2026-09-19): folds the implementer's exact-hash MUST-REVISE of rev17 (`intg-substep2b/PLAN-REVIEW-pair-implementer-20260919-213206.md`): MUST-2B-36 — the T-ORACLE carry binds the LIVE plan digest, so the `t-oracle.txt` written for rev16 (`plan_sha256=7f538d82…`) is stale for every later revision and Step 5 would STOP `plan-sha-mismatch-live-…` deterministically; `resume.sh` now STOPs `t-oracle-stale` in its pre-flight when a carried file does not name the new lock, and Step 0′ states the process: after each exact-hash approve the pair Planner names the new digest to master, master files a fresh five-field carry, the pair Planner rewrites the file from it (the previous preserved as `t-oracle.prev-<stamp>.txt`) BEFORE the token; MUST-2B-37 — `resume.sh` published the canonical pointer before the seal, so a seal failure exposed an unsealed directory and the retry wedged on `same-lock`; the block is restructured: every check pre-flight before any write; the new directory built unpublished (the seal assembled inside it); the seal copied to `$EVID/runners/resume-<token>/` with no clobber and its count verified; the old pointer preserved with no clobber; the new value staged to a same-directory temporary name and `mv`'d over the pointer as the LAST act; a STOP after the new directory exists removes that unpublished directory. Executed on a scratch mirror: the must-be-YES with a fresh `t-oracle.txt` naming the plan on disk, then the exact Step 5 T-ORACLE prefix from the new directory against a scratch pdc carry naming the same digest — pass; the stale file → `t-oracle-stale` (no write) and, pushed through the T-ORACLE prefix, `plan-sha-mismatch-live-…`; the six early mutants STOP before any write; the three late mutants (the seal path pre-existing; `$EVID/runners` unwritable; `$EVID` unwritable) STOP with the old pointer byte-identical and no seal, and each retries to success once the cause is removed. Step 3c, Step 4 and the Task 4 Files line are unchanged from rev17 (the reviewer's Step 3c positive passed: one m-3.planner-authored commit, the ten paths preserved, the rebuilt binary, the witness). A10 rev7 / A11 rev7 stay untranscribed (Master Reviewer 192826 must-revise; no lock).
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
