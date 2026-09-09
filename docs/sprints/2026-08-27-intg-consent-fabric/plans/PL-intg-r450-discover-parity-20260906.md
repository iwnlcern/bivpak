# R-4.50 claude-discover parity — Implementation Plan (revision 10)

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:executing-plans to implement this plan task-by-task, IN DOCUMENT ORDER. Steps use checkbox (`- [ ]`) syntax for tracking. Nothing in this document is authority: implementation starts only on the pair Planner's addressed token after the exact-hash PLAN-REVIEW approve.

**Revision 10 (2026-09-09) — the implementer's token-9 STOP `042759` (Task 2 Step 4) folded: the main-checkout no-mutation proof measured the WRONG TARGET. Its instrument diffed the WHOLE `git status --porcelain` of the shared main checkout against Task 0's snapshot, so a concurrent, authorized write by ANOTHER seat — my own issuance commit `f394f2d` carrying the ROADMAP ledger while Task 2 observed P — fired it (the delta was exactly one docs-lane line; the observations of P on both targets were complete and correct: macOS `biv_tests` 419, Linux 421, skip sets equal, ENTRY and predictor PASS). The gate's purpose is "the observation run wrote nothing into the main checkout"; the shared main checkout carries two surfaces other seats are AUTHORIZED to write during a token — the engine-owned relay root `.relays/` (every seat's daemon renders there) and the sprint ledgers `docs/sprints/` (this seat's ROADMAP/results at every issuance and receipt; sibling sprints' ledgers likewise) — and a status that includes them measures the pair's concurrency, not the implementer's act (the `shared-index-sweep` lesson in a second form: a shared surface has no per-seat isolation). rev10 narrows the instrument to its target with git's own pathspec: Task 0 Step 0's `status-initial.txt` and Task 2 Step 4's `status-main-post-P.txt` (and by reference Task 4 Step 3's and Task 5 Step 5's twins) are taken with `-- . ':(exclude).relays' ':(exclude)docs/sprints'`; inherited S4 modifications outside those two surfaces (none today: the residual is two inherited untracked files) are still PRESERVED and DISCLOSED by the snapshot; a product-path write in the main checkout still fires (VALIDATED 2026-09-09 in bash AND zsh, from the artifact's WRITTEN bytes, on the real main checkout and on a scratch clone: a ROADMAP modification → 0 lines; an untracked relay → 0; an untracked sibling-sprint doc → 0; a modified `src/adapters/claude_code/claude_code.cpp` → 1 line, the discriminator; an untracked `harness/` file → +1). The `:(exclude)` form is the one this plan already validated for the C → H proof (Task 5 Step 6). Nothing else changes: no fence surface, no owner term, no ruling, no product byte; the standing rule holds — this safeguard lives in the plan through the exact-hash review. The evidence homes of tokens 7, 8 and 9 are sealed records; Task 0 re-runs; state `ii` at P is the expected route.**

**Goal:** execute sealed c1 §7 in the claude adapter's `discover` body so an existing `CLAUDE_CONFIG_DIR` store no longer suppresses an existing `$HOME/.claude` default store (both are searched, env first), with codex's `discover` as the reference shape; witness it with rows 1–5 + the codex parity row; land as ONE PR carrying TWO commits on a branch cut at the PUBLISHED base — C (product + test + the two count-gate literals) and its child H (m-3's harness follow-through, three files, iso rev8) — carried to `origin` as a PR (the vehicle, never the evidence), with the acceptance of record at the PR head C+H.

**Architecture:** the discover body becomes the codex shape (optional `env_root`; append the env store iff its value exists; append the default iff it exists AND `lexically_normal()` differs) — no other product byte. One NEW named Catch2 `TEST_CASE` in `tests/test_adapter_claude_collect.cpp` carries rows 1–5 + parity as `SECTION`s (the fence owner's shape, N = 1 exactly). The census change is transcribed into the two `successes` literals of `.github/workflows/s2-harness.yml` (`:85` macOS, `:326` Linux) in the SAME commit from the candidate's OWN observed `-r xml` runs under CG-R7 (rev5) and T-1..T-5 — observed, never derived. H (child of C, three files, iso rev8 :196-240): `harness/selftest/stub_biv.py` — the claude branch of `_discover_model` takes the codex-shaped append (L1 fidelity to C's `discover`, proven by `h_fidelity.py`'s five rows); `harness/selftest/test_store_isolation.py` — the HOME mutant test renamed and asserting BOTH HOME-default canaries (tag set exactly `{HOME}`; seven `NAMED MUTANT` markers / eleven tests unchanged); `harness/bivharness/e3.py` — ONLY the `claude_adapter_file` sha256 literal (`:75`) re-pinned to sha256(`claude_code.cpp` at C). Owners: m-2 reviews C (V-CP-1..6 over the product + test bytes); m-3 reviews C's two workflow lines (CG-R7.5) AND H at the PR head (V-FT-1..8, byte review and veto). The acceptance gate of record is the workflow-equivalent suite on BOTH targets at the PR head C+H.

**Tech stack:** C++20 (`std::filesystem`), Catch2 v3.7.1 (`TEST_CASE`/`SECTION`, `-r xml`, `-w UnmatchedTestSpec`), CMake presets `ci-macos` (host) and `ci` (Linux parity container: ubuntu-24.04 `linux/amd64` `--init`, `nofile` soft == hard), git worktrees, `gh` 2.97, python3 (XML parsing only).

**Spec (the law of this act, cited never retyped):** m-2 fence rev2 `pdc:master/relays/r437-pack-timeout-diagnosis/DESIGN-m2-planner-20260903-144700.md` @ sha256 `f2216ee606a03b0b5b0b7f4562fed52a7349219c28990e6ee3e89b0cc25e8c6f` (pdc `dfb5b409`; Master Reviewer approve `151001`; design origin `intg-r450-discover-parity-act/DESIGN-m2-planner-20260906-002200.md` for `DESIGN_DOC_ID m2-r450-discover-fence-rev2-20260903`; peer approve `DESIGN-REVIEW-implementer-20260906-004520.md` at pdc `79fa1754`). Operator grant `r437-operator-scope-ruling/PLAN-operator-20260903-152117.md`. Master's route `intg-r450-discover-parity-act/PLAN-master-planner-20260905-212735.md`, composed ruling `PLAN-master-planner-20260906-004023.md`, and the R-4.52 landing carry `PLAN-master-planner-20260906-015102.md` (operator carrier `publication-path-ruling/PLAN-operator-20260906-015101.md`). m-3's Q2 ruling `DESIGN-planner-20260906-002436.md` (T-1..T-5) and the count-gate design `master/domains/m-3-restore-cli/design/2026-08-30-count-gate-repair-r438-rev1.md` at rev5 @ `9a0320b60e87819495ae1b11a9c4469455267af0275b9479dbf81376d1940f7d` (CG-R7.1–7.7 + V-CG-6; Master Reviewer approve `053521`; rev1 `0099d1cf` stays the landed repair's pin). Sealed c1 §7 in `master/domains/m-2-agent-adapters/design/2026-07-02-adapter-contract-and-session-semantics.md` @ `e4c19914…`. H's law: iso rev8 `master/domains/m-3-restore-cli/design/2026-09-01-e2-store-isolation-r437.md` @ `00046a657abd6c5792e3c6222c8690b39f1a773ecbc2473ca9af2845a95813af` (pdc `407719b`; Master Reviewer approve `intg-r450-discover-parity-act/DESIGN-REVIEW-master-reviewer-20260907-134011.md`; the follow-through paragraph and V-FT-1..8 / S-FT-1..4 at :196-240), master's vehicle ruling `PLAN-master-planner-20260907-041131.md` (arm A) and release `PLAN-master-planner-20260907-134909.md`; m-3's `DESIGN-planner-20260907-043621.md`, `-130523.md`, `-132308.md`; m-2's fence reading `DESIGN-m2-planner-20260907-062000.md`. The isolation act's landed HOME-mutant evidence (the pre-parity control) `.relays/intg/intg-isolation/IMPL-pair-implementer-20260903-002131.md:135-137`.

## Global constraints (each line binds every task)

- DETERMINING TEXT (c1 §7): "Discovery returns ALL stores found (a set): env-set does not suppress the default if both exist and differ — both are searched."
- REFERENCE SHAPE: `src/adapters/codex/codex.cpp:1193-1206` for DISCOVER ONLY — append; `lexically_normal()` guard; env then defaults. Its trailing-slash property (`"/x/.claude/"` ≠ `"/x/.claude"` under `lexically_normal()`, probed 2026-09-05) is INHERITED by parity; any "tightening" is a V-CP-2 divergence (m-2, `004023`).
- TOUCHABLE: `src/adapters/claude_code/claude_code.cpp` discover body (:570-596 at the base) + `tests/test_adapter_claude_collect.cpp` + EXACTLY the two integer literals at `.github/workflows/s2-harness.yml:85` and `:326` (m-3's surface, CG-R7.2/7.4 (α); V-CP-1 read on the record to exclude them). NOTHING ELSE — no codex byte (V-CP-3), no collect byte (V-CP-4), no harness/stub/witness byte IN C (V-CP-5 — harness bytes exist ONLY in H, Task 5, three files), no other workflow byte (CG-R7.4 → STOP to m-3.planner), no CMake, no fixture file, no docs byte on the branch, NO TAG (local or remote), no ref other than the one branch. IGNORED, UNTRACKED environment paths in the worktree (`.venv-harness/` — ignored by `.git/info/exclude:8`, shared by all worktrees; `build/` — `.gitignore:1`) may be created, deleted and re-created: they are not repository bytes, and `git check-ignore -q <name>/` (trailing slash — the patterns are directory-only) proves BOTH at Task 0 Step 2, immediately after entering the worktree and BEFORE the first worktree status gate.
- H — THE HARNESS FOLLOW-THROUGH (iso rev8 :196-240; owner m-3; executor this pair under the generalized fence rule — m-2's "the pair never fixes the stub or harness in-lane" reads "never inside commit C"): ONE commit, child of C, on the candidate branch, write set EXACTLY (1) `harness/selftest/stub_biv.py` — the claude branch of `_discover_model` (:140-146 at B) takes the codex-shaped append (env root first; `$HOME/.claude` appended when it exists and its `os.path.normpath` differs — the codex branch's OWN idiom at :150-160; the C++ `lexically_normal()` trailing-slash cell is UNMODELLED by both stub branches, pre-existing for codex, recorded here, NOT tightened); (2) `harness/selftest/test_store_isolation.py` — the HOME mutant test (:110-123 at B) renamed `test_home_restore_exposes_both_home_default_canaries` and its claude-canary assertion inverted from ABSENCE (`not in`) to PRESENCE (`in`); the tag-set-exactly-`{HOME}` assertion already lives in `_run_mutant` (unchanged); the seven `NAMED MUTANT` markers and eleven `def test_` stay 7/11 (measured at B 2026-09-07); (3) `harness/bivharness/e3.py` — ONLY the `_ADAPTER_SOURCE_ANCHORS["claude_adapter_file"]` sha256 literal at `:75`, re-pinned by the helper to sha256 of `src/adapters/claude_code/claude_code.cpp` AT C (expected `4e105052a17b7e0d99bfeca28ac45cac1f6ed3c5ba0e9ba9ec62a34e530a3a51`, three seats; computed, never typed). VETOES V-FT-1..8 and STOPs S-FT-1..4 (iso rev8 :227-240) bind as written: no byte outside the three files; no `e3.py` byte other than the one literal (no other anchor, no tripwire logic, no `SESSION_LOCATIONS`/`LIVE_STORE_SELECTORS` byte); the literal == sha256 at C; the stub's claude branch == the codex shape AND == C's `discover` (`h_fidelity.py`, five rows); the HOME mutant asserts both canaries with tag set `{HOME}` and the 7/11 inventory unchanged; no `scenario.py`/spec/oracle/product byte; `harness-selftest` GREEN on both targets at C+H with the HOME real-binary demonstration and the fidelity check IN H's evidence; H lands on the candidate branch BEFORE the PR head's acceptance run. STOPs: S-FT-1 C's `discover` shape deviates from the codex reference → STOP UP (to m-3 through the pair Planner) before any harness byte; S-FT-2 any further harness reference to the claude adapter's bytes or behaviour found while executing H (the WALK below re-run at C shows a new hit) → STOP UP; S-FT-3 the tripwire's re-validation needs more than the re-pin (an E3 model byte) → STOP UP; S-FT-4 the codex anchor or any other pinned surface differs at C → STOP UP.
- THE HARNESS WALK (master `134909`; the lesson of `201740`) — recorded HERE, RE-RUN at C by Task 5 Step 0 against the two inventories written verbatim to `$EVID/walk-A.expected` / `$EVID/walk-B.expected` (Task 0 Step 0b); a new `file:line` = S-FT-2 STOP UP. Class A, bytes-of-the-file pins — `grep -rn -E 'claude_code\.cpp|claude_adapter_file' harness/ --include='*.py'` (11 hits at B, measured 2026-09-07): `bivharness/e3.py:73,74` (the anchor tuple whose `:75` literal H re-pins); `selftest/test_e3_asserts.py:1891,1894,1905,1908,1926,1937,2015,2017` (mutant fixtures that COPY the file and edit string anchors) and `:2184` (the source-copying drift test). Their anchors — `.globs = {"projects/*/*.jsonl"}`, `.path = root / "projects"`, `    std::vector<Store> stores;`, `const Inventory& claude_inventory()` — are each present EXACTLY ONCE in `claude_code.cpp` at C (measured 2026-09-07; re-measured at Task 5 Step 0): they survive C. Class B, behaviour/env references — `grep -rn -E 'CLAUDE_CONFIG_DIR|/\.claude|"\.claude"|SESSION_LOCATIONS|LIVE_STORE_SELECTORS' harness/ --include='*.py' --include='*.json'` (47 hits at B): `bivharness/e3.py:55,56,59,69,2367,2794` (the E3 model — `"claude-code": ("CLAUDE_CONFIG_DIR",)` and `"claude-code": ("projects",)`, UNCHANGED by H: both discovered stores locate `projects`); `bivharness/scenario.py:29,41,70,76,170,181,189,567,568` (poison topology + RP oracle: the `home/.claude/projects` canary maps to HOME — no byte); `scenarios-e3/e3-dual-resume.json:7,19,21` (E3's host2 leg runs agents under a scratch HOME — unaffected, iso rev8); `selftest/stub_biv.py:140,142,143,144` (H file 1); `selftest/test_store_isolation.py:97,148,150,154` (the CLAUDE_CONFIG_DIR mutant and the hermetic positive — unchanged; the HOME test at :110-123 is H file 2 and carries no class-B token); `selftest/test_e3_asserts.py:189,299,639,1931,2054,2084,2153,2253,2269,2276,2297,2356,2391,2437,2496,4452,7652,8455,8473,8492,8516` (E3 env plumbing that sets/unsets the selector for hosts, plus the mutant fixture text — no discovery-precedence model). The wide agent-name pattern `claude-code` (hundreds of hits in `test_e3_asserts.py`, `scenario.py`, `e3.py`, `test_probe_isolation.py`, `test_compare.py`, `ci/check_version_floor_mirror.py` and the E2 specs) names the agent id and its stand-ins, never discovery — walked 2026-09-07, none touched. Only `test_store_isolation.py` reads `STUB_BIV_DISCOVERY_LOG` (measured).
- ACCEPTANCE GATE OF RECORD = the PR head C+H (iso rev8; master `134909`): the workflow-equivalent suites on BOTH targets REQUIRED rc 0 at H (Task 6); the R-OBS discriminator re-EXECUTED at H — the only later head where `harness-selftest` is expected green (at the resume head and at P/C the C1 tripwire reds it under ANY environment, so the predicate cannot separate there; the B-head execution of record is the implementer's `discriminator-predicate.txt`, `rc1=8 rc2=0 present_count=1 iff=pass hygiene=pass`). The P-state and C-state full-suite runs (Task 1 Step 5 (iv), Task 2 Step 2's Linux ctest stage, Task 4 Step 1 both targets) are DISCLOSURE runs: rc recorded as DATA, the failing-row set extracted from the ctest log (`grep -E '^[[:space:]]+[0-9]+ - .*\(Failed\)'` then `sed -E 's/^[[:space:]]*[0-9]+ - ([^ ]+) .*/\1/'`, each status-captured; VALIDATED 2026-09-07 in bash AND zsh on the implementer's REAL `ctest-macos-P.log` → `harness-selftest`; on a log without a FAILED block the grep exits 1 with an empty file and the diff against the expectation then STOPs) and REQUIRED EXACTLY `harness-selftest`; any other row = FINDING, STOP UP. The census cells: observed at P and C; UNMOVED at H (`gate.py`: literal(C) == observed(C) == observed(H)).
- SKIP-SET EQUALITY IS MEMBERSHIP (rev8): the macOS `biv_tests` skipped-name set is compared to B's `expected_skips` names by `skipset.py` (count and membership), NEVER by bytes — `cells.py` emits the workflow's listing order and `tuples.py` emits the names sorted, by construction; a `skipset.py` exit 5 is the V-CG-5 routed FINDING (STOP UP, never an edit); exit 2 is a producer defect (STOP).
- EVIDENCE HOME = a RESOLVED real path (`pwd -P` of the `mktemp -d` result): the product's no-follow containment check refuses a symlinked ancestor (`/tmp` → `/private/tmp`, `/var/folders` → `/private/var/folders` on macOS) with `ArchiveWriteFailed containment_refused errno 20` — measured 2026-09-07 in BOTH the base and the candidate binaries (pre-existing, not this act's); the real-binary demonstration (Task 6 Step 4) and any scratch a `biv` invocation reads MUST live under `$EVID` so resolved.
- VETOES V-CP-1..6 (`144700` lines 64-71) and S-CP-1..5 (`142000` :55-71; S-CP-5 HELD, dedupe OUT) bind as written; sealed-text silence = STOP UP through the pair Planner → master; never a local reading.
- COUNT-GATE TERMS T-1..T-5 (`002436`) and CG-R7.1–7.7 (rev5): B/P/C predeclared below with binding points; the trigger is P's OBSERVATION against B's workflow values (a `TEST_CASE` diff is a PREDICTOR and consistency check only); cells transcribed from P's `-r xml` `OverallResultsCases` tuples on BOTH targets under CG-R2's topology and the R-OBS observer environment (`CREDENTIAL_ENV_NAMES` derived from `harness/bivharness/e3.py` at the head, unset by NAME, values never read); NO arithmetic anywhere in the evidence; an observed delta the predictor does not predict, or a predicted delta not observed, is a FINDING routed UP (a skip-set move touches `expected_skips` → V-CG-5 routed finding FIRST, never an edit); the ten per-binary tuples + XML sha256 + run identity + the old(B)/observed(P)/new(C) table in the commit message AND the tracked report.
- TWO commits on branch `intg/r450-discover-parity` cut at `origin/main` = `bbf297e36a38a1fab8c2675f945098a0633f9f8b` (the PUBLISHED base; product bytes equal to local `main`; the PR's lineage exports zero unpublished commits — MEASURED at Task 0 Step 3, Task 3 Step 4 and Task 5 Step 6): `C` (this act's ONE commit — product + test + the two literals; `C^` = the pin) and its child `H` (the harness follow-through; `H^` = `C`). Commit messages end with `Co-Authored-By: Claude Fable 5.1 <noreply@anthropic.com>`.
- SHELL DISCIPLINE (standing corrective `164704`; the F4 class): every status captured as `rc=0; <cmd> || rc=$?` and RECORDED; never `set +e`; NO pipelines in any evidence-producing span — every producer writes a FILE and its status is checked before the consumer reads the file; `grep -c`/`grep`/`git grep`/`diff` exit 1 is VALID DATA (zero matches / a difference) classified separately from 2+ (an error → STOP); every evidence file `[ -s file ] || STOP` before it is read (except files whose EXPECTED content is empty, which are checked with `[ ! -s file ]` after their producer's status is proven); refspecs and paths never spelled `"$VAR:…"` (zsh modifiers) — `"${VAR}"` braces everywhere a variable touches punctuation; the push line names the branch LITERALLY and is validated by `git push --dry-run` immediately before; no variable named `path`. `STOP` = stop the task, record the failing status and file, return to the pair Planner (never a retry, never a re-observation).
- The GitHub token never enters a container or any evidence; credential VALUES never read/printed; the host worktree byte-clean at product paths; inherited S4 state preserved, never cleaned. THE MAIN-CHECKOUT NO-MUTATION PROOF (rev10): every `git -C /Users/jack/Programming/bivpak status --porcelain` this plan takes carries the pathspec `-- . ':(exclude).relays' ':(exclude)docs/sprints'` — the engine-owned relay root and the sprint ledgers are surfaces OTHER seats are authorized to write while a token executes, so a status that includes them measures concurrency, not the implementer's act (the token-9 STOP `042759`); a write at any other path in the main checkout still fires the diff.
- Merge ≠ push ≠ release. The branch push and the PR are authorized by R-4.51 clause (2) via the route; the local merge waits on the four-condition bar + both owner reviews + the operator's condition-4 token; under the R-4.52 LANDING RULE (operator option A, `015101`/`015102`) the landing = that merge PLUS ONE fast-forward push of local `main` to `origin/main` by this lane — that push is the MERGE PACKET's own step in the first-push shape, NOT this plan's token (this plan ends at the open PR); no docs-lane-only push; no tag/release/deploy/seal; red remote CI blocks nothing and is cited nowhere. The release hold is ABSOLUTE.

---

## B / P / C — roles, resolution, binding points (CG-R7.7, predeclared BEFORE any observation)

```text
B  the pre-act BASELINE = the declared base = origin/main = bbf297e36a38a1fab8c2675f945098a0633f9f8b (the published pin;
   the commit whose workflow bytes the candidate inherits). RESOLVED at Task 0 Step 1 (the remote re-read must equal it)
   and RECORDED with B's workflow values: the ten cells read from `git show bbf297e…:.github/workflows/s2-harness.yml`
   (biv_tests :85 = 418 / :326 = 420; the other eight cells; the macOS expected_skips names — the Linux job has
   no identity block, only its skips count cell) → $EVID/B-cells.txt.
P  the PROVISIONAL tree = product + test bytes over B's workflow bytes, workflow UNTOUCHED. P's identity is RECORDED at
   Task 1 Step 7 (after the provisional commit exists, BEFORE Task 2 observes it) → $EVID/P.txt. P is observed on both
   targets (Task 2) and is the SOURCE of every transcribed literal and of the skip identity set.
C  the CANDIDATE = P amended with EXACTLY the admitted (α) lines whose values P's observation supplied. C's identity is
   RECORDED at Task 3 Step 3 (after the amendment exists, BEFORE Task 4 observes it) → $EVID/C.txt. The diff P→C is
   exactly those lines (Task 3 Step 4). C is observed as the evidence of record (Task 4); C's observations == P's
   observations == C's literals (Task 4 Step 2).
H  the HARNESS FOLLOW-THROUGH = C's CHILD, EXACTLY the three harness files (iso rev8), no product/test/workflow byte. H's identity
   is RECORDED at Task 5 Step 5 (after the commit exists, BEFORE Task 6 observes it) → $EVID/H.txt; H^ == C proven there. H is
   the PR HEAD: the acceptance suites of record run at H on both targets (Task 6); H moves no Catch2 cell (harness-selftest is a
   pytest ctest row) — proven by gate.py over C's literals, C's tuples and H's tuples (Task 6 Step 3).
ENTRY (CG-R7.1)  P's biv_tests tuple vs B's cells: a difference = census-changing act → transcription (Task 3);
   EQUAL = zero-delta — which CONTRADICTS the predictor (+1 TEST_CASE) → FINDING routed UP, no transcription, no commit.
TABLE  $EVID/bpc-table.txt: per binary per target one line `binary target old_B observed_P new_C` (values copied from the
   files that hold them, never typed); the identities B/P/C with their binding steps on top. Goes into the commit message
   (B, P; C's own sha cannot be in C's message — stated) and the tracked report (all three).
ANTI-RETROSPECTION  P.txt, C.txt and H.txt are written at their binding steps (Task 1 Step 7, Task 3 Step 3, Task 5 Step 5) and never rewritten; every later use re-reads them. Order P → C → H is the record; no step reads a later identity.
```

## File structure

- Modify: `src/adapters/claude_code/claude_code.cpp:570-596` — the `discover` body only.
- Modify: `tests/test_adapter_claude_collect.cpp` — one test-local `ScopedEnvVar` helper + two small helpers + ONE new `TEST_CASE` (rows 1–5 + parity as `SECTION`s), appended after the existing discover case at :97-116 (which is unchanged).
- Modify: `.github/workflows/s2-harness.yml:85` and `:326` — the two `biv_tests` `successes` integer literals, transcribed (Task 3), nothing else.
- Modify (H, commit 2 — iso rev8 write set): `harness/selftest/stub_biv.py:140-146` — the claude branch of `_discover_model` (7 lines → 11, the codex shape); `harness/selftest/test_store_isolation.py:110-123` — the HOME mutant test's name and its claude-canary assertion (2 lines); `harness/bivharness/e3.py:75` — the one sha256 literal (1 line). Nothing else.
- Evidence (outside the repository): `$EVID` under `mktemp -d`; the tracked report `docs/sprints/2026-08-27-intg-consent-fabric/results/intg-r450-discover-parity-<C>-<H>.md` lands on lane-local `main` by the pair Planner (docs lane), never on the branch.

## The circularity, stated and resolved (CG-R7.7 is this shape, ruled)

A literal cannot be observed at the commit that contains it. Resolution, all three halves recorded: (1) P (product + test, workflow untouched) is observed on BOTH targets — the P run is the SOURCE of the two literals (copied from the XML by a script, Task 3); (2) P is amended into C (the two literals + the full message carrying the P tuples and `observed_head=P`); the tree delta P→C is PROVEN to be exactly the two workflow lines; P stays reachable by its recorded object id (the branch reflog holds it — `git reflog show intg/r450-discover-parity` lists it; `git cat-file -e` proves it before every use; no tag is created); (3) C is RE-OBSERVED on both targets — the C runs are the runs OF RECORD (ten tuples + XML sha256 + run identity in the tracked report and the IMPL return), and every C cell MUST equal the literal in C's workflow AND the P tuple; any inequality = FINDING, STOP UP. The two-commit alternative (product commit, then a workflow-only child as `b065de1` did) was rejected: the route and CG-R7.2 say ONE commit.

---

### Task 0 — RESUME at the retained candidate: evidence home (resolved), the prior evidence copied, helpers materialized, B recorded, the worktree/venv/build VERIFIED (never re-derived), the observer environment derived (no product byte)

**Files:** none modified.

- [ ] **Step 0: evidence home (RESOLVED) + the prior evidence of record + initial snapshot** — `EVID_RAW=$(mktemp -d "${TMPDIR:-/tmp}/r450-evidence-XXXXXX")`; `EVID=$(cd "$EVID_RAW" && pwd -P)`; `[ -d "$EVID" ] || STOP` (VALIDATED 2026-09-07 in bash AND zsh: `/var/folders/…/T//r450-…` → `/private/var/folders/…/T/r450-…`; the resolved path is the one every later `$EVID` use carries — see the EVIDENCE HOME constraint); the inside-repo `case` guard (VALIDATED 2026-09-06 in bash AND zsh: /tmp → ok, ./build → STOP): `case "$(cd "$EVID" && pwd -P)/" in "$(git rev-parse --show-toplevel)/"*) echo STOP-evid-inside-repo; exit 1;; esac`. THE PRIOR EVIDENCE OF RECORD (the `intg-r450-discover-parity-impl-2` execution's home; READ-ONLY here; master `134909`: not re-derived): `PRIOR=/var/folders/hq/f0qq8v_103q9y8prfn20rzx80000gn/T/r450-evidence-16Y21z; [ -d "$PRIOR" ] || STOP` (absent = STOP UP — the resume premise failed); `mkdir "$EVID/prior"; c=0; cp -p "$PRIOR/witness-red.xml" "$PRIOR/witness-red.rc" "$PRIOR/witness-red.verdict" "$PRIOR/witness-red.stderr" "$PRIOR/witness-red-parse.rc" "$PRIOR/red-build.rc" "$PRIOR/witness-green.xml" "$PRIOR/witness-green.rc" "$PRIOR/witness-green.verdict" "$PRIOR/witness-green-parse.rc" "$PRIOR/discriminator-predicate.txt" "$PRIOR/discriminator-as-is.log" "$PRIOR/discriminator-unset.log" "$PRIOR/observer-unset-names.txt" "$PRIOR/ctest-macos-P.log" "$PRIOR/ctest-macos-P.rc" "$PRIOR/B-cells.txt" "$EVID/prior/" || c=$?; [ "$c" -eq 0 ] || STOP; h=0; shasum -a 256 "$EVID"/prior/* > "$EVID/prior-hashes.txt" || h=$?; [ "$h" -eq 0 ] && [ -s "$EVID/prior-hashes.txt" ] || STOP` (the seventeen files exist at the implementer's home — listed 2026-09-07; a missing file makes `cp` fail → STOP UP). `s0=0; git -C /Users/jack/Programming/bivpak status --porcelain -- . ':(exclude).relays' ':(exclude)docs/sprints' > "$EVID/status-initial.txt" || s0=$?; [ "$s0" -eq 0 ] || STOP` (rev10: the two shared write surfaces excluded — see the MAIN-CHECKOUT NO-MUTATION PROOF constraint; inherited modifications elsewhere are PRESERVED and DISCLOSED, never staged or cleaned; this file may legitimately be non-empty).

- [ ] **Step 0b: MATERIALIZE THE TWELVE HELPERS AND THE TWO WALK INVENTORIES — before ANY use (F1 of `161925`; rev6 adds `h_stub h_test h_e3pin h_fidelity rp_mutants` and `walk-A.expected` / `walk-B.expected`; rev8 adds `skipset`)** — each block below is written to `$EVID/<name>.py` (the inventories to `$EVID/walk-A.expected` and `$EVID/walk-B.expected`, `[ -s ]`-checked) VERBATIM from this plan (copy the fenced bytes exactly; no edits), then proven present and syntactically valid with a CAPTURED status before the next helper is written: for each name in `cells witness hunks tuples transcribe gate h_stub h_test h_e3pin h_fidelity rp_mutants skipset`: `[ -s "$EVID/<name>.py" ] || STOP; k=0; python3 -m py_compile "$EVID/<name>.py" || k=$?; [ "$k" -eq 0 ] || STOP` (VALIDATED 2026-09-06 in bash AND zsh: the six extracted helpers compile with k=0; a helper with one byte corrupted → k=1 → STOP; the five rev6 helpers extracted from THIS plan's bytes compile with k=0, 2026-09-07; `skipset.py` likewise 2026-09-08). `h_fidelity.py` and `rp_mutants.py` RUN under the worktree's venv interpreter (`.venv-harness/bin/python`, proven at Step 3b — they import `stub_biv`/`bivharness`, which need `zstandard`); the others under `python3`. Every later step INVOKES a helper only; no step writes one. Helper semantics are unchanged from rev2 (each carries its VALIDATED note, re-run at the pair Planner's seat on the rev3 bytes).

**`cells.py`**

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

Write this block to `$EVID/cells.py` VERBATIM from the plan (the pair Planner extracted and RAN it on the workflow at `bbf297e` 2026-09-06: ten cells with `biv_tests macos successes=418 … skips=3` and `biv_tests linux successes=420 … skips=1`; `expected_skips macos n=3` and `expected_skips linux absent` — the Linux job carries NO `expected_skips` identity block, only its count cell (`grep -c expected_skips` = 3 at `bbf297e`, all in the macOS job: the definition `:97` and its two uses `:119`/`:127`; none in the Linux job); on a copy with the Linux block removed → rc 2; with one binary removed → rc 3).

**`witness.py`**

```python
#!/usr/bin/env python3
# usage: witness.py <catch2-xml> red|green   — exit 0 iff the five ROW leaves have exactly the expected outcome
import sys, xml.etree.ElementTree as ET
xml_path, mode = sys.argv[1], sys.argv[2]
NAME = "Claude adapter discovery returns every store found: env and default both searched with codex parity (c1 §7)"
RED_ROWS = {"ROW 1", "ROW 5"} if mode == "red" else set()
root = ET.parse(xml_path).getroot()
cases = [tc for tc in root.iter("TestCase") if tc.get("name") == NAME]
if len(cases) != 1:
    sys.exit(2)  # the named case must appear exactly once
seen = {}
for section in cases[0].findall("Section"):
    label = section.get("name", "").split(":")[0].strip()  # "ROW n"
    if not label.startswith("ROW "):
        continue
    results = section.find("OverallResults")
    if results is None or label in seen:
        sys.exit(3)  # every leaf carries one OverallResults; a leaf appears once
    seen[label] = int(results.get("failures", "-1"))
if set(seen) != {"ROW 1", "ROW 2", "ROW 3", "ROW 4", "ROW 5"}:
    sys.exit(4)  # all five leaves present
for label, failures in sorted(seen.items()):
    expected_red = label in RED_ROWS
    if failures < 0 or (failures > 0) != expected_red:
        sys.exit(5)  # a leaf's outcome differs from the mode's expectation
    print(f"{label} failures={failures} expected={'red' if expected_red else 'green'} ok")
overall = cases[0].find("OverallResult")
if overall is None or (overall.get("success") == "true") != (mode == "green"):
    sys.exit(6)  # the case verdict must agree with the mode
print(f"{mode} verdict ok")
```

Write this block to `$EVID/witness.py` VERBATIM from the plan (the pair Planner extracted and RAN it 2026-09-06 against synthetic Catch2 XML in the shape the binary emits: red-mode YES case ROW 1 + ROW 5 failing → 0; all-green in red mode → 5; ROW 2 failing in red mode → 5; a missing ROW 4 → 4; a duplicated leaf → 3; the wrong case name → 2; green-mode with the all-green XML → 0).

**`hunks.py`**

```python
#!/usr/bin/env python3
# usage: hunks.py <hunk-headers-file> <lo> <hi>  — exit 0 iff every @@ -a,b +c,d @@ old-range lies within [lo, hi]
import re, sys
lo, hi = int(sys.argv[2]), int(sys.argv[3])
headers = [line for line in open(sys.argv[1], encoding="utf-8").read().split("\n") if line.startswith("@@")]
if not headers:
    sys.exit(2)
for header in headers:
    m = re.match(r'@@ -(\d+)(?:,(\d+))? \+(\d+)(?:,(\d+))? @@', header)
    if m is None:
        sys.exit(3)
    start = int(m.group(1)); count = int(m.group(2)) if m.group(2) is not None else 1
    end = start + count - 1 if count > 0 else start
    if start < lo or end > hi:
        print(f"OUTSIDE {header}")
        sys.exit(4)
    print(f"inside {header}")
```

Write this block to `$EVID/hunks.py` VERBATIM (the pair Planner RAN it 2026-09-06: a header `@@ -570,27 +570,29 @@` with bounds 570 596 → 0; `@@ -569,2 +569,2 @@` → 4; `@@ -590,10 +590,10 @@` → 4; an empty file → 2; a malformed header → 3).

**`tuples.py`**

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

Write this block to `$EVID/tuples.py` VERBATIM (the pair Planner RAN it 2026-09-06 on a synthetic five-XML set in the binary's shape: five tuple lines + the skip line with n=3; an empty XML → 2; an XML without `OverallResultsCases` → 3; a set without a `biv_tests` XML → 4).

**`transcribe.py`**

```python
#!/usr/bin/env python3
# usage: transcribe.py <workflow> <macos-biv_tests.xml> <linux-biv_tests.xml>
# Writes the observed biv_tests "successes" cells into lines 85 and 326 of the workflow.
# No arithmetic: the value written IS the XML's OverallResultsCases successes attribute.
import sys, re, xml.etree.ElementTree as ET
workflow, macos_xml, linux_xml = sys.argv[1], sys.argv[2], sys.argv[3]
def observed(path):
    cases = ET.parse(path).getroot().find("OverallResultsCases")
    if cases is None or cases.get("successes") is None:
        sys.exit(2)
    return cases.get("successes")
targets = {85: observed(macos_xml), 326: observed(linux_xml)}
lines = open(workflow, encoding="utf-8").read().split("\n")
for lineno in targets:
    if lines[lineno - 2].strip() != '"biv_tests": {':
        sys.exit(3)  # the anchor line above each cell must be the biv_tests block opener
    m = re.fullmatch(r'(\s+"successes": )(\d+)(,)', lines[lineno - 1])
    if m is None:
        sys.exit(3)
    lines[lineno - 1] = f"{m.group(1)}{targets[lineno]}{m.group(3)}"
open(workflow, "w", encoding="utf-8").write("\n".join(lines))
print("transcribed", targets)
```

**`gate.py`**

```python
#!/usr/bin/env python3
# usage: gate.py <C-cells.txt> <P-macos> <P-linux> <C-macos> <C-linux>  — exit 0 iff every cell agrees across literal(C), observed(P), observed(C)
import sys
def read(path):
    rows = {}
    for line in open(path, encoding="utf-8"):
        parts = line.split()
        if len(parts) >= 6 and parts[0].startswith("biv_") and parts[2].startswith("successes="):
            rows[(parts[0], parts[1])] = tuple(p.split("=", 1)[1] for p in parts[2:6])
    return rows
literals = read(sys.argv[1])
observed_p = {**read(sys.argv[2]), **read(sys.argv[3])}
observed_c = {**read(sys.argv[4]), **read(sys.argv[5])}
if len(literals) != 10 or set(literals) != set(observed_p) or set(literals) != set(observed_c):
    sys.exit(2)
bad = 0
for key in sorted(literals):
    ok = literals[key] == observed_p[key] == observed_c[key]
    bad += 0 if ok else 1
    print(f"{key[0]} {key[1]} literal_C={literals[key]} observed_P={observed_p[key]} observed_C={observed_c[key]} equal={'yes' if ok else 'no'}")
sys.exit(0 if bad == 0 else 5)
```

**`skipset.py`** (rev8 — the skip-set comparison FORM; VALIDATED 2026-09-08 in bash AND zsh on the implementer's real `B-cells.txt` and the real observed line of `231512`: exit 0 `same_set=yes`; a changed name → 5; a dropped name (n=2) → 5; a tuples file without the observed line → 2)

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

**`h_stub.py`** (rev6, H file 1 — VALIDATED 2026-09-07 in bash AND zsh on a scratch copy of the candidate: applied once → `old_lines=7 new_lines=11`, the file diff `9 5`; a second application → exit 3 `REFUSED … found 0 times`, no write)

```python
# usage: h_stub.py <harness/selftest/stub_biv.py>  — replaces the claude branch of _discover_model
# with the codex-shaped append (exactly ONE occurrence of the old block, else no write; exit 3).
import sys
from pathlib import Path
target = Path(sys.argv[1])
OLD = (
    '    ccd = env.get("CLAUDE_CONFIG_DIR")\n'
    '    if ccd and Path(ccd).exists():\n'
    '        claude_roots = [("CLAUDE_CONFIG_DIR", Path(ccd))]\n'
    '    elif home and (home / ".claude").exists():\n'
    '        claude_roots = [("HOME", home / ".claude")]\n'
    '    else:\n'
    '        claude_roots = []\n'
)
NEW = (
    '    claude_roots = []\n'
    '    claude_env_root = None\n'
    '    ccd = env.get("CLAUDE_CONFIG_DIR")\n'
    '    if ccd and Path(ccd).exists():\n'
    '        claude_env_root = Path(ccd)\n'
    '        claude_roots.append(("CLAUDE_CONFIG_DIR", claude_env_root))\n'
    '    if home and (home / ".claude").exists() and (\n'
    '        claude_env_root is None\n'
    '        or os.path.normpath(home / ".claude") != os.path.normpath(claude_env_root)\n'
    '    ):\n'
    '        claude_roots.append(("HOME", home / ".claude"))\n'
)
text = target.read_text(encoding="utf-8")
n = text.count(OLD)
if n != 1:
    print(f"REFUSED: old claude branch found {n} times (expected 1); no write", file=sys.stderr)
    sys.exit(3)
target.write_text(text.replace(OLD, NEW, 1), encoding="utf-8")
print(f"stub claude branch replaced: old_lines={OLD.count(chr(10))} new_lines={NEW.count(chr(10))}")
```

**`h_test.py`** (rev6, H file 2 — VALIDATED 2026-09-07 in bash AND zsh: applied once → the file diff `2 2`, the `NAMED MUTANT` count stays 7 and `^def test_` stays 11; a second application → exit 3, no write)

```python
# usage: h_test.py <harness/selftest/test_store_isolation.py>  — the HOME mutant test renamed and
# its claude-canary assertion inverted from ABSENCE to PRESENCE (each edit exactly once, else exit 3, no write).
import sys
from pathlib import Path
target = Path(sys.argv[1])
EDITS = [
    (
        "def test_home_restore_exposes_only_the_reachable_codex_canary(\n",
        "def test_home_restore_exposes_both_home_default_canaries(\n",
    ),
    (
        '    assert scenario.POISON_SESSION_IDS["HOME:claude"] not in "\\n".join(\n'
        "        path for _, _, path in entries\n"
        "    )\n",
        '    assert scenario.POISON_SESSION_IDS["HOME:claude"] in "\\n".join(\n'
        "        path for _, _, path in entries\n"
        "    )\n",
    ),
]
text = target.read_text(encoding="utf-8")
for old, new in EDITS:
    n = text.count(old)
    if n != 1:
        print(f"REFUSED: edit anchor found {n} times (expected 1); no write: {old.splitlines()[0]!r}", file=sys.stderr)
        sys.exit(3)
for old, new in EDITS:
    text = text.replace(old, new, 1)
target.write_text(text, encoding="utf-8")
print("test_store_isolation.py: HOME mutant renamed; claude HOME canary asserted PRESENT")
```

**`h_e3pin.py`** (rev6, H file 3 — VALIDATED 2026-09-07 in bash AND zsh against the candidate's `claude_code.cpp`: prints `old=cd1f8bc8f7ab87cf15251d84ad7e59c618a22f3c19b9633ff193350782800851 new=4e105052a17b7e0d99bfeca28ac45cac1f6ed3c5ba0e9ba9ec62a34e530a3a51`, the file diff `1 1`, the `-U0` hunk `@@ -75 +75 @@` with exactly the two literal lines changed; a second application → exit 3, no write)

```python
# usage: h_e3pin.py <harness/bivharness/e3.py> <src/adapters/claude_code/claude_code.cpp>
# Re-pins ONLY the _ADAPTER_SOURCE_ANCHORS["claude_adapter_file"] sha256 literal to the sha256 of the
# given claude_code.cpp bytes. The old literal line must occur exactly once (else exit 3, no write);
# an unchanged digest is refused (exit 4, no write). Prints old= new= for the evidence.
import hashlib
import sys
from pathlib import Path
e3 = Path(sys.argv[1])
cpp = Path(sys.argv[2])
OLD_LINE = '        "cd1f8bc8f7ab87cf15251d84ad7e59c618a22f3c19b9633ff193350782800851",\n'
new_digest = hashlib.sha256(cpp.read_bytes()).hexdigest()
NEW_LINE = f'        "{new_digest}",\n'
text = e3.read_text(encoding="utf-8")
n = text.count(OLD_LINE)
if n != 1:
    print(f"REFUSED: old anchor literal line found {n} times (expected 1); no write", file=sys.stderr)
    sys.exit(3)
if NEW_LINE == OLD_LINE:
    print("REFUSED: digest unchanged — nothing to re-pin; no write", file=sys.stderr)
    sys.exit(4)
e3.write_text(text.replace(OLD_LINE, NEW_LINE, 1), encoding="utf-8")
print(f"old={OLD_LINE.strip().strip(',').strip(chr(34))} new={new_digest}")
```

**`h_fidelity.py`** (rev6, the L1 fidelity check — RUN WITH THE VENV INTERPRETER; VALIDATED 2026-09-07: on the B-state stub → rc 5 with ROW 1 and ROW 5 `MISMATCH` (observed `[CLAUDE_CONFIG_DIR]`, expected `[CLAUDE_CONFIG_DIR, HOME]`), ROWS 2–4 ok — the must-be-NO; on the H stub → rc 0, five rows ok — the must-be-YES; the rows mirror the TEST_CASE's ROWs 1–5 at the store-TAG level, env first)

```python
# usage: <venv python> h_fidelity.py <harness/selftest dir>  — L1 fidelity: the stub's _discover_model
# claude branch reproduces C's discover on the five witness rows (store TAG sets, env first).
# exit 0 iff every row matches; each row printed as `ROW n: observed=[...] expected=[...] ok|MISMATCH`.
import os
import sys
import tempfile
from pathlib import Path
sys.path.insert(0, sys.argv[1])
import stub_biv  # noqa: E402

def plant(root):
    (root / "projects" / "p").mkdir(parents=True)
    (root / "projects" / "p" / "s.jsonl").write_text("{}\n", encoding="utf-8")

def tags(env):
    seen = []
    for tag, _ in stub_biv._discover_model(env):
        if tag not in seen:
            seen.append(tag)
    return seen

rows = []
with tempfile.TemporaryDirectory() as tmp:
    t = Path(tmp)
    home = t / "home"; env_store = t / "env-store"
    plant(home / ".claude"); plant(env_store)
    rows.append(("ROW 1 env set, exists, differs; default exists", {"HOME": str(home), "CLAUDE_CONFIG_DIR": str(env_store)}, ["CLAUDE_CONFIG_DIR", "HOME"]))
    rows.append(("ROW 2 env set and equal to the default", {"HOME": str(home), "CLAUDE_CONFIG_DIR": str(home / ".claude")}, ["CLAUDE_CONFIG_DIR"]))
    rows.append(("ROW 3 env unset, default exists", {"HOME": str(home)}, ["HOME"]))
    home2 = t / "home2"; home2.mkdir()
    rows.append(("ROW 4 neither", {"HOME": str(home2)}, []))
    rows.append(("ROW 5 env set, default exists, both hold sessions (enumeration only)", {"HOME": str(home), "CLAUDE_CONFIG_DIR": str(env_store)}, ["CLAUDE_CONFIG_DIR", "HOME"]))
    bad = 0
    for name, env, expected in rows:
        observed = tags(env)
        ok = observed == expected
        bad += 0 if ok else 1
        print(f"{name}: observed={observed} expected={expected} {'ok' if ok else 'MISMATCH'}")
sys.exit(0 if bad == 0 else 5)
```

**`rp_mutants.py`** (rev6 — the isolation act's real-binary demonstration, VERBATIM from `PL-intg-isolation-20260902.md` Task 3 Step 3 (the landed act's instrument; not this plan's to edit); RUN WITH THE VENV INTERPRETER from `harness/`, the scratch under the RESOLVED `$EVID`; VALIDATED 2026-09-07 at the candidate's built `biv` under `/private/var/…`: rc 0, `ALL FOUR MUTANTS RED ON EXACTLY THEIR OWN LOCATOR`, the HOME mutant with BOTH identities; under `/tmp/…` (a symlink) → the containment refusal and the `_session_rows` crash — the reason for the resolved-path constraint)

```python
import sys
from pathlib import Path
sys.path.insert(0, str(Path.cwd()))          # harness/
from bivharness import scenario
from bivharness.report import Status
biv, out = Path(sys.argv[1]), Path(sys.argv[2])
spec = Path("scenarios/store-isolation-witness.json")
original = scenario._run_json
for locator in ("HOME", "CODEX_HOME", "CODEX_SQLITE_HOME", "CLAUDE_CONFIG_DIR"):
    def mutated(biv_, args, cwd, env_overrides=None, _locator=locator):
        overrides = dict(env_overrides or {}); overrides.pop(_locator, None)   # the FINAL env loses exactly one locator
        return original(biv_, args, cwd, overrides)
    scenario._run_json = mutated
    result = scenario.run_scenario(spec, biv, out / f"mutant-{locator}")
    scenario._run_json = original
    leaks = [line for line in result.detail.splitlines() if line.startswith("isolation-leak ")]
    tags = {line.split()[1].rstrip(":") for line in leaks}
    print(f"MUTANT {locator}: status={result.status.value} leak_tags={sorted(tags)}")
    print(result.detail)
    assert result.status is Status.FAIL and tags == {locator}, (locator, result.status, tags, result.detail)
    if locator == "CODEX_SQLITE_HOME":   # rev5 binding (3): ONE warning OBJECT whose kind AND path are both exact
        poison_db = out / f"mutant-{locator}" / "store-isolation-witness.poison" / "codex-sqlite" / "state_5.sqlite"
        warning_lines = [l for l in leaks if " warnings[" in l]
        assert len(warning_lines) == 1 and warning_lines[0].endswith(f" kind=CodexDbEnrichmentSkipped path={poison_db}"), (warning_lines, result.detail)
        positive_missing = [l for l in result.detail.splitlines() if l.startswith("isolation-positive missing")]
        assert not positive_missing, positive_missing   # the staged codex session at its store root is what PUBLISHES the warning
print("ALL FOUR MUTANTS RED ON EXACTLY THEIR OWN LOCATOR")
```

**`walk-A.expected`** (rev6 — the class-A inventory at B's harness bytes, `file:line` sorted; written verbatim; compared by `diff` at Task 5 Step 0)

```text
harness/bivharness/e3.py:73
harness/bivharness/e3.py:74
harness/selftest/test_e3_asserts.py:1891
harness/selftest/test_e3_asserts.py:1894
harness/selftest/test_e3_asserts.py:1905
harness/selftest/test_e3_asserts.py:1908
harness/selftest/test_e3_asserts.py:1926
harness/selftest/test_e3_asserts.py:1937
harness/selftest/test_e3_asserts.py:2015
harness/selftest/test_e3_asserts.py:2017
harness/selftest/test_e3_asserts.py:2184
```

**`walk-B.expected`** (rev6 — the class-B inventory at B's harness bytes, `file:line` sorted, 47 lines; written verbatim; compared by `diff` at Task 5 Step 0)

```text
harness/bivharness/e3.py:2367
harness/bivharness/e3.py:2794
harness/bivharness/e3.py:55
harness/bivharness/e3.py:56
harness/bivharness/e3.py:59
harness/bivharness/e3.py:69
harness/bivharness/scenario.py:170
harness/bivharness/scenario.py:181
harness/bivharness/scenario.py:189
harness/bivharness/scenario.py:29
harness/bivharness/scenario.py:41
harness/bivharness/scenario.py:567
harness/bivharness/scenario.py:568
harness/bivharness/scenario.py:70
harness/bivharness/scenario.py:76
harness/scenarios-e3/e3-dual-resume.json:19
harness/scenarios-e3/e3-dual-resume.json:21
harness/scenarios-e3/e3-dual-resume.json:7
harness/selftest/stub_biv.py:140
harness/selftest/stub_biv.py:142
harness/selftest/stub_biv.py:143
harness/selftest/stub_biv.py:144
harness/selftest/test_e3_asserts.py:189
harness/selftest/test_e3_asserts.py:1931
harness/selftest/test_e3_asserts.py:2054
harness/selftest/test_e3_asserts.py:2084
harness/selftest/test_e3_asserts.py:2153
harness/selftest/test_e3_asserts.py:2253
harness/selftest/test_e3_asserts.py:2269
harness/selftest/test_e3_asserts.py:2276
harness/selftest/test_e3_asserts.py:2297
harness/selftest/test_e3_asserts.py:2356
harness/selftest/test_e3_asserts.py:2391
harness/selftest/test_e3_asserts.py:2437
harness/selftest/test_e3_asserts.py:2496
harness/selftest/test_e3_asserts.py:299
harness/selftest/test_e3_asserts.py:4452
harness/selftest/test_e3_asserts.py:639
harness/selftest/test_e3_asserts.py:7652
harness/selftest/test_e3_asserts.py:8455
harness/selftest/test_e3_asserts.py:8473
harness/selftest/test_e3_asserts.py:8492
harness/selftest/test_e3_asserts.py:8516
harness/selftest/test_store_isolation.py:148
harness/selftest/test_store_isolation.py:150
harness/selftest/test_store_isolation.py:154
harness/selftest/test_store_isolation.py:97
```

Write this block to `$EVID/gate.py` VERBATIM (the pair Planner RAN it 2026-09-06 on synthetic inputs: all ten agreeing → 0 with ten `equal=yes` lines; one C tuple altered → 5 with one `equal=no`; a missing cell → 2).

- [ ] **Step 1: the base is the published pin — B RESOLVED and RECORDED** — `f=0; git -C /Users/jack/Programming/bivpak fetch --no-tags origin refs/heads/main:refs/remotes/origin/main || f=$?; [ "$f" -eq 0 ] || STOP` (one ref, literal refspec); `BASE=$(git -C /Users/jack/Programming/bivpak rev-parse origin/main)`; REQUIRE `[ "$BASE" = bbf297e36a38a1fab8c2675f945098a0633f9f8b ] || STOP` (the remote moved — STOP UP, never re-base silently); `d=0; git -C /Users/jack/Programming/bivpak diff --quiet bbf297e36a38a1fab8c2675f945098a0633f9f8b main -- src tests CMakeLists.txt CMakePresets.json harness .github || d=$?; [ "$d" -eq 0 ] || STOP` (product bytes at the published pin == local main; measured 2026-09-05: 0 lines; `d` 1 = a real difference, 2+ = an error — both STOP, distinguished by the recorded value). B's workflow values: `w=0; git -C /Users/jack/Programming/bivpak show bbf297e36a38a1fab8c2675f945098a0633f9f8b:.github/workflows/s2-harness.yml > "$EVID/B-workflow.yml" || w=$?; [ "$w" -eq 0 ] && [ -s "$EVID/B-workflow.yml" ] || STOP`; `c=0; python3 "$EVID/cells.py" "$EVID/B-workflow.yml" > "$EVID/B-cells.txt" || c=$?; printf 'cells_B_rc=%s\n' "$c" > "$EVID/B-cells.rc"; [ "$c" -eq 0 ] && [ -s "$EVID/B-cells.txt" ] || STOP` (the helper materialized at Step 0b; a rejected PARTIAL parse exits 3 with six lines already printed — the STATUS is the gate, non-emptiness alone is not: VALIDATED 2026-09-06 in bash AND zsh: a mutant with one LINUX binary removed → the six macOS lines printed, then c=3 — output NON-EMPTY yet STOP reached on the status; a mutant with a macOS binary removed → c=3 with empty output) — the ten `binary target successes failures expectedFailures skips` lines + the macOS `expected_skips` name list (the Linux job carries no identity block; its skip identity is compared by COUNT only, the observed names recorded for the report), READ from B's bytes, never typed. Record `printf 'B=%s\n' "$BASE" > "$EVID/B.txt"`.

- [ ] **Step 2: the retained worktree — VERIFY, never re-create; ONE state SELECTED and RECEIPTED (rev6 resume; rev9: the selector is executable and every later consumer reads its receipt)** — `[ -d /Users/jack/Programming/bivpak-intg-r450-discover-parity ] || STOP` (absent = STOP UP: the resume premise failed; never re-create silently — the bytes are not this plan's to re-derive); `cd /Users/jack/Programming/bivpak-intg-r450-discover-parity`; THE IGNORE PROOFS, before the first status gate (F2 of `183249`): `g=0; git check-ignore -q .venv-harness/ || g=$?; g2=0; git check-ignore -q build/ || g2=$?; g3=0; git check-ignore -q harness/selftest/__pycache__/ || g3=$?; printf 'venv_ignored_rc=%s build_ignored_rc=%s pycache_ignored_rc=%s\n' "$g" "$g2" "$g3" > "$EVID/ignore-proof.txt"; [ "$g" -eq 0 ] && [ "$g2" -eq 0 ] && [ "$g3" -eq 0 ] || STOP` (trailing slash — the patterns `.venv-harness/` at `.git/info/exclude:8`, `__pycache__/` at `:10` and `build/` at `.gitignore:1` are directory-only; MEASURED 2026-09-06/07 at the retained worktree in bash AND zsh: all 0); the branch: `[ "$(git rev-parse --abbrev-ref HEAD)" = intg/r450-discover-parity ] || STOP`. THE SELECTOR (rev9; F1/F2 of `001126`) — HEAD is read ONCE and exactly one state is chosen and RECEIPTED: `HEAD0=$(git rev-parse HEAD); if [ "$HEAD0" = bbf297e36a38a1fab8c2675f945098a0633f9f8b ]; then resume_state=i; elif [ "$HEAD0" = 54954281b30cae113f399055fff106963a37a443 ]; then resume_state=ii; else resume_state=none; fi; w=0; printf 'resume_state=%s\nhead=%s\n' "$resume_state" "$HEAD0" > "$EVID/resume-state.txt" || w=$?; [ "$w" -eq 0 ] && [ -s "$EVID/resume-state.txt" ] || STOP; [ "$resume_state" = i ] || [ "$resume_state" = ii ] || STOP` (state `i` = the pin with the two unstaged paths, the rev6 resume; state `ii` = P BOUND under token 7, `231512`; any other head = STOP UP — never a reset, never a checkout, never an amend). Every later state-dependent command re-reads the receipt as `resume_state=$(sed -n 's/^resume_state=//p' "$EVID/resume-state.txt")` — the receipt, never prose. STATE (i) BODY: `resume_state=$(sed -n 's/^resume_state=//p' "$EVID/resume-state.txt"); if [ "$resume_state" = i ]; then s=0; git status --porcelain > "$EVID/status-worktree-0.txt" || s=$?; [ "$s" -eq 0 ] && [ -s "$EVID/status-worktree-0.txt" ] || STOP; w=0; printf ' M src/adapters/claude_code/claude_code.cpp\n M tests/test_adapter_claude_collect.cpp\n' > "$EVID/status-worktree-0.expected" || w=$?; [ "$w" -eq 0 ] && [ -s "$EVID/status-worktree-0.expected" ] || STOP; d=0; diff "$EVID/status-worktree-0.expected" "$EVID/status-worktree-0.txt" > "$EVID/status-worktree-0.delta" || d=$?; [ "$d" -eq 0 ] || STOP; h=0; shasum -a 256 src/adapters/claude_code/claude_code.cpp tests/test_adapter_claude_collect.cpp > "$EVID/resume-hashes.txt" || h=$?; [ "$h" -eq 0 ] || STOP; printf '4e105052a17b7e0d99bfeca28ac45cac1f6ed3c5ba0e9ba9ec62a34e530a3a51  src/adapters/claude_code/claude_code.cpp\n90615eeb414c1cdcabeff124f95aafa6f729764860c9782f023f401a35d7a8e9  tests/test_adapter_claude_collect.cpp\n' > "$EVID/resume-hashes.expected"; d=0; diff "$EVID/resume-hashes.expected" "$EVID/resume-hashes.txt" > "$EVID/resume-hashes.delta" || d=$?; [ "$d" -eq 0 ] || STOP; fi` (the status names EXACTLY the two in-scope paths; the two files at the three-seat hashes — MEASURED 2026-09-07 at the then-retained worktree, and 2026-09-09 at a scratch shared clone holding the pin with the two paths). STATE (ii) BODY: `resume_state=$(sed -n 's/^resume_state=//p' "$EVID/resume-state.txt"); if [ "$resume_state" = ii ]; then [ "$(git rev-parse "HEAD^")" = bbf297e36a38a1fab8c2675f945098a0633f9f8b ] || STOP; [ "$(git rev-parse "HEAD^{tree}")" = f1eb8aec36601a02312a5d34a18ea0a6238833a1 ] || STOP; s=0; git status --porcelain > "$EVID/status-worktree-0.txt" || s=$?; [ "$s" -eq 0 ] && [ ! -s "$EVID/status-worktree-0.txt" ] || STOP; w=0; : > "$EVID/status-worktree-0.expected" || w=$?; [ "$w" -eq 0 ] && [ -f "$EVID/status-worktree-0.expected" ] && [ ! -s "$EVID/status-worktree-0.expected" ] || STOP; d=0; diff "$EVID/status-worktree-0.expected" "$EVID/status-worktree-0.txt" > "$EVID/status-worktree-0.delta" || d=$?; [ "$d" -eq 0 ] || STOP; for q in src/adapters/claude_code/claude_code.cpp tests/test_adapter_claude_collect.cpp; do w=0; git show "HEAD:${q}" > "$EVID/P-$(basename "$q")" || w=$?; [ "$w" -eq 0 ] && [ -s "$EVID/P-$(basename "$q")" ] || STOP; done; h=0; shasum -a 256 "$EVID/P-claude_code.cpp" "$EVID/P-test_adapter_claude_collect.cpp" > "$EVID/resume-hashes.txt" || h=$?; [ "$h" -eq 0 ] || STOP; printf '4e105052a17b7e0d99bfeca28ac45cac1f6ed3c5ba0e9ba9ec62a34e530a3a51  %s/P-claude_code.cpp\n90615eeb414c1cdcabeff124f95aafa6f729764860c9782f023f401a35d7a8e9  %s/P-test_adapter_claude_collect.cpp\n' "$EVID" "$EVID" > "$EVID/resume-hashes.expected"; d=0; diff "$EVID/resume-hashes.expected" "$EVID/resume-hashes.txt" > "$EVID/resume-hashes.delta" || d=$?; [ "$d" -eq 0 ] || STOP; r=0; git diff --numstat bbf297e36a38a1fab8c2675f945098a0633f9f8b HEAD > "$EVID/P-touched.numstat" || r=$?; [ "$r" -eq 0 ] && [ -s "$EVID/P-touched.numstat" ] || STOP; printf '12\t13\tsrc/adapters/claude_code/claude_code.cpp\n183\t0\ttests/test_adapter_claude_collect.cpp\n' > "$EVID/P-touched.expected"; d=0; diff "$EVID/P-touched.expected" "$EVID/P-touched.numstat" > "$EVID/P-touched.delta" || d=$?; [ "$d" -eq 0 ] || STOP; fi` (an EMPTY status is the expected content, checked as empty after the producer's status is proven, and an EMPTY `status-worktree-0.expected` is written so Step 3b's single post-venv comparison holds; P's parent, tree, the two blob hashes and the two-path numstat are verified against the values MEASURED 2026-09-08 at the retained worktree; the whole state-(ii) body executed as part of the Task 0 → Task 1 FLOW 2026-09-09 at that worktree in bash AND zsh). Exactly one body runs; the other is a no-op by the receipt.
- [ ] **Step 3: the cut-point measurement (R-4.8 lesson; rev9: the expectation selected by the receipt — F3 of `001126`)** — `resume_state=$(sed -n 's/^resume_state=//p' "$EVID/resume-state.txt"); if [ "$resume_state" = i ]; then want=0; elif [ "$resume_state" = ii ]; then want=1; else STOP; fi; c=0; n=$(git rev-list --count origin/main..HEAD) || c=$?; [ "$c" -eq 0 ] || STOP; [ "$n" -eq "$want" ] || STOP; w=0; printf 'unpublished_commits_in_lineage=%s expected=%s resume_state=%s\n' "$n" "$want" "$resume_state" > "$EVID/cutpoint.txt" || w=$?; [ "$w" -eq 0 ] && [ -s "$EVID/cutpoint.txt" ] || STOP` (under `i` the branch carries no commit above the published pin; under `ii` it carries exactly P — MEASURED 2026-09-09: n=1 at the retained worktree, n=0 at the scratch pin clone; any other value = STOP UP).
- [ ] **Step 3b: the harness venv — VERIFY the retained one; recreate ONLY if its proofs fail (rev6)** — the path's ignore status was PROVEN at Step 2. `if [ -x .venv-harness/bin/python ]; then venv_branch=verify; else venv_branch=create; fi; printf 'venv_branch=%s\n' "$venv_branch" > "$EVID/venv-branch.txt"`. Under `create` (or if a `verify` proof below fails — then record `venv_branch=recreate` and run this once): `r=0; rm -rf .venv-harness || r=$?; [ "$r" -eq 0 ] && [ ! -e .venv-harness ] || STOP` (an ignored, untracked directory, never a repository byte; VALIDATED 2026-09-06 in bash AND zsh on an existing and on an absent directory); `v=0; /opt/homebrew/bin/python3.12 -m venv .venv-harness || v=$?; [ "$v" -eq 0 ] && [ -x .venv-harness/bin/python ] || STOP` (Python 3.12, the version CI pins at `s2-harness.yml:14`); `i=0; .venv-harness/bin/python -m pip install -q -r harness/requirements.lock > "$EVID/venv-pip.log" 2>&1 || i=$?; [ "$i" -eq 0 ] || STOP` (`jsonschema==4.25.1`, `pytest==8.4.2`, `zstandard==0.25.0`). THE PROOFS (both branches): `m=0; .venv-harness/bin/python -c 'import pytest, jsonschema, zstandard; print("imported", pytest.__name__, jsonschema.__name__, zstandard.__name__)' > "$EVID/venv-imports.txt" 2>&1 || m=$?; [ "$m" -eq 0 ] && [ -s "$EVID/venv-imports.txt" ] || STOP` (VALIDATED 2026-09-06 in bash AND zsh: the 3.12 venv → m=0; Homebrew `python3.14` → m=1); `p=0; .venv-harness/bin/python --version > "$EVID/venv-python.txt" 2>&1 || p=$?; [ "$p" -eq 0 ] && [ -s "$EVID/venv-python.txt" ] || STOP` (expected `Python 3.12.x`; the retained venv measured `Python 3.12.12` 2026-09-07). The status gate — the resume state, NOT empty: `s=0; git status --porcelain > "$EVID/status-post-venv.txt" || s=$?; [ "$s" -eq 0 ] || STOP; d=0; diff "$EVID/status-worktree-0.expected" "$EVID/status-post-venv.txt" > "$EVID/status-post-venv.delta" || d=$?; [ "$d" -eq 0 ] || STOP`.
- [ ] **Step 4: the build directory — VERIFY its interpreter, replace it ONLY if stale (the `mv` form, rev6); build at the resume bytes; base hashes from B's blobs** — `BIVHARNESS_PYTHON` is a CMake CACHE entry (`harness/CMakeLists.txt:12-20`; a re-configure KEEPS the first interpreter — MEASURED 2026-09-06). `if [ -e build/ci-macos ]; then g=0; k=$(grep -c -E '^BIVHARNESS_PYTHON:FILEPATH=.*/\.venv-harness/bin/python3$' build/ci-macos/CMakeCache.txt) || g=$?; [ "$g" -le 1 ] || STOP; else k=0; fi; printf 'cache_before_k=%s\n' "$k" > "$EVID/cache-proof-before.txt"`; if `[ -e build/ci-macos ] && [ "$k" -ne 1 ]` (a stale cache): `v=0; mv build/ci-macos "$EVID/stale-ci-macos" || v=$?; [ "$v" -eq 0 ] && [ ! -e build/ci-macos ] || STOP` (the status-captured MOVE into the evidence home is the deletion form's equivalent — the executing wrapper refused `rm -rf` at `201740`; an ignored directory, never a repository byte; VALIDATED 2026-09-07 in bash AND zsh: v=0 and the source path absent) — the retained worktree's `build/ci-macos` was measured venv-selected 2026-09-07 (k=1), so the expected branch is KEEP; then `b=0; cmake --preset ci-macos > "$EVID/configure-0.log" 2>&1 || b=$?; [ "$b" -eq 0 ] || STOP`; THE INTERPRETER PROOF (REQUIRED after configure, both branches): `g=0; k=$(grep -c -E '^BIVHARNESS_PYTHON:FILEPATH=.*/\.venv-harness/bin/python3$' build/ci-macos/CMakeCache.txt) || g=$?; [ "$g" -le 1 ] || STOP; [ "$k" -eq 1 ] || STOP; printf 'cache_after_k=%s\n' "$k" > "$EVID/cache-proof.txt"` (VALIDATED 2026-09-06 on the two scratch caches: venv-selected → k=1; 3.14 → k=0, g=1 → STOP); then `b=0; cmake --build --preset ci-macos > "$EVID/build-0.log" 2>&1 || b=$?; [ "$b" -eq 0 ] || STOP` (this build is AT THE RESUME BYTES — C's product + test — not a baseline; the baseline census was the `impl-2` execution's `existing-discover-0.log`, retained at `$PRIOR`); `t=0; ./build/ci-macos/biv_tests -w UnmatchedTestSpec "Claude adapter discovers CLAUDE_CONFIG_DIR as an env-tier store" > "$EVID/existing-discover-0.log" 2>&1 || t=$?; [ "$t" -eq 0 ] || STOP` (the existing case, unchanged by this act). BASE HASHES FROM B'S BLOBS (the working tree is modified, so `shasum` on it is not the base): `for p in src/adapters/claude_code/claude_code.cpp src/adapters/codex/codex.cpp tests/test_adapter_claude_collect.cpp; do w=0; git show "bbf297e36a38a1fab8c2675f945098a0633f9f8b:${p}" > "$EVID/base-$(basename "$p")" || w=$?; [ "$w" -eq 0 ] && [ -s "$EVID/base-$(basename "$p")" ] || STOP; done; h=0; shasum -a 256 "$EVID"/base-*.cpp > "$EVID/base-hashes.txt" || h=$?; [ "$h" -eq 0 ] && [ -s "$EVID/base-hashes.txt" ] || STOP` (VALIDATED 2026-09-07 in bash AND zsh: three blobs written, three hash lines; the `"${sha}:${p}"` braces keep zsh's `:` modifiers inert) — the codex line must be IDENTICAL at C (Task 7 Step 1; S-FT-4 at Task 5 Step 0).
- [ ] **Step 5: the R-OBS observer environment — DERIVED NOW with the venv interpreter (F2); the discriminator is NOT executable at this head (rev6)** — exactly the count-gate plan's Task 1 Step 3(a) (R-OBS-1..3, RULED `012332`) with the interpreter that can import `e3.py` (the ambient `python3` lacks `zstandard` — `ModuleNotFoundError`, measured 2026-09-07): (a) `n=0; (cd harness && ../.venv-harness/bin/python -c 'from bivharness.e3 import CREDENTIAL_ENV_NAMES as n; print("\n".join(n))') > "$EVID/observer-unset-names.txt" || n=$?; [ "$n" -eq 0 ] && [ -s "$EVID/observer-unset-names.txt" ] || STOP` (derived from `e3.py` at this head, never typed; cross-check `e3.py:33-37` by eye and record the line range; VALIDATED 2026-09-07 in bash AND zsh: three names, `cmp`-equal to the implementer's `prior/observer-unset-names.txt`); `c=0; cmp "$EVID/observer-unset-names.txt" "$EVID/prior/observer-unset-names.txt" || c=$?; [ "$c" -eq 0 ] || STOP`; host presence BY NAME ONLY: `while read -r n; do if printenv "$n" > /dev/null; then echo "$n present"; else echo "$n absent"; fi; done < "$EVID/observer-unset-names.txt" > "$EVID/observer-host-presence.txt"; [ -s "$EVID/observer-host-presence.txt" ] || STOP` (values never printed); the ONE environment: `OBS_ENV=(env); while read -r n; do OBS_ENV+=(-u "$n"); done < "$EVID/observer-unset-names.txt"` — every ctest, pytest, `-r xml` run and the real-binary demonstration in Tasks 1, 2, 4, 5, 6 executes as `"${OBS_ENV[@]}" <command>`; `g=0; present_count=$(grep -c present "$EVID/observer-host-presence.txt") || g=$?; [ "$g" -le 1 ] || STOP; printf 'present_count=%s\n' "$present_count" > "$EVID/observer-present-count.txt"`. (c) THE DISCRIMINATOR (R-OBS-3) is NOT run here: this head carries C's product bytes over the B pin, so `harness-selftest` is RED under ANY environment (the C1 tripwire) and the predicate cannot separate; the B-head execution of record is `$EVID/prior/discriminator-predicate.txt` (`rc1=8 rc2=0 present_count=1 iff=pass hygiene=pass`, the `impl-2` execution); the discriminator EXECUTES ONCE at H (Task 6 Step 1), the only later head where `harness-selftest` is expected green.

### Task 1 — the witness first (RED, fail-closed), then the discover body (GREEN under the observer environment)

**Files:** Modify `tests/test_adapter_claude_collect.cpp` (append after :116); Modify `src/adapters/claude_code/claude_code.cpp:570-596`.

**Interfaces:** consumes `biv::adapters::Env{getenv, home}`, `Store{root, locators, tier, archived}`, `DiscoveryTier{env, defaults, …}` (`src/adapters/adapter.hpp:23-49`); `biv::adapters::claude_code_adapter()` / `biv::adapters::codex_adapter()`; `biv::pack::pack(const fs::path&) -> expected<PackReport>` (`src/core/pack/pack.hpp:59`), `BivError{kind, path, detail}` (`src/core/support/error.hpp:40-46`, namespace `biv`), `ErrKind::ArchiveWriteFailed`.

**RESUME CHECKPOINT (rev6; rev9: routed by the receipt `$EVID/resume-state.txt`, never by prose):** under state `i` — Steps 1, 2 and 4 are DONE in the working tree, verified by hash at Task 0 Step 2 (the ROW 5 label already carries the `ROW 5: (…)` spelling below); Step 3's RED evidence of record is `$EVID/prior/` (copied at Task 0 Step 0: `witness-red.rc` = `red_test_rc=` nonzero, `witness-red.verdict` = `red verdict ok`, `witness-red-parse.rc` = 0, `red-build.rc` = 0, the XML retained) — NOT re-run: the base bytes are no longer in the working tree and master `134909` forbids re-derivation; Step 5 re-runs (i)–(iii) as FRESH proofs under this token and executes (iv) as the DISCLOSURE run; Step 6 runs its state-`i` route (the dirty-worktree fence) and Step 7 its state-`i` route (the ONE commit). Under state `ii`, P BOUND (`231512`) — Steps 1, 2, 4 AND 7 are DONE inside the commit P verified at Task 0 Step 2 (parent, tree, both blob hashes, the two-path numstat); Step 3 as under `i`; Step 5 RE-RUNS (i)–(iv) at P as FRESH proofs under this token (the build is a no-op that proves the binaries current); Step 6 runs its state-`ii` route (the commit-diff fence) and Step 7 its state-`ii` route (bind the EXISTING P — no commit, no amend). The token-7 macOS XMLs (successes=419, skips=3) are a sealed record, not progress: Task 2 observes P from scratch under either state.

- [ ] **Step 1: add the test-local helpers** (inside the existing anonymous namespace, after `write_file`):

```cpp
// Test-local environment scope for ROW 5's in-process pack call (mirrors tests/test_pack.cpp's ScopedEnv).
class ScopedEnvVar {
 public:
  ScopedEnvVar(std::string name, std::optional<std::string> value) : name_{std::move(name)} {
    if (const char* old = std::getenv(name_.c_str()); old != nullptr) {
      old_value_ = std::string{old};
    }
    if (value.has_value()) {
      setenv(name_.c_str(), value->c_str(), 1);
    } else {
      unsetenv(name_.c_str());
    }
  }
  ~ScopedEnvVar() {
    if (old_value_.has_value()) {
      setenv(name_.c_str(), old_value_->c_str(), 1);
    } else {
      unsetenv(name_.c_str());
    }
  }
  ScopedEnvVar(const ScopedEnvVar&) = delete;
  ScopedEnvVar& operator=(const ScopedEnvVar&) = delete;
  ScopedEnvVar(ScopedEnvVar&&) = delete;
  ScopedEnvVar& operator=(ScopedEnvVar&&) = delete;

 private:
  std::string name_;
  std::optional<std::string> old_value_;
};

biv::adapters::Env discovery_env(const fs::path& home,
                                 std::optional<std::string> claude_value,
                                 std::optional<std::string> codex_value) {
  return biv::adapters::Env{
      .getenv = [claude_value, codex_value](const std::string_view name) -> std::optional<std::string> {
        if (name == "CLAUDE_CONFIG_DIR") {
          return claude_value;
        }
        if (name == "CODEX_HOME") {
          return codex_value;
        }
        return std::nullopt;
      },
      .home = home};
}

std::vector<biv::adapters::DiscoveryTier> tiers(const std::vector<biv::adapters::Store>& stores) {
  std::vector<biv::adapters::DiscoveryTier> out;
  for (const auto& store : stores) {
    out.push_back(store.tier);
  }
  return out;
}
```

Add `#include "adapters/codex/codex.hpp"`, `#include "core/pack/pack.hpp"`, `#include "core/support/error.hpp"` beside the existing includes.

- [ ] **Step 2: write the ONE new TEST_CASE** (rows 1–5 + parity as SECTIONs; appended after the existing discover case; the name carries NO comma — a comma is a Catch2 spec separator):

```cpp
TEST_CASE("Claude adapter discovery returns every store found: env and default both searched with codex parity (c1 §7)") {
  const auto& claude = biv::adapters::claude_code_adapter();
  const auto& codex = biv::adapters::codex_adapter();
  const auto root = make_tmp("discover-parity");
  const auto home = root / "home";
  fs::create_directories(home);
  const auto claude_default = home / ".claude";
  const auto codex_default = home / ".codex";
  const auto claude_env = root / "claude-env";
  const auto codex_env = root / "codex-env";

  SECTION("ROW 1: env set, exists, differs; default exists -> TWO stores, env first") {
    fs::create_directories(claude_env / "projects");
    fs::create_directories(claude_default / "projects");
    fs::create_directories(codex_env);
    fs::create_directories(codex_default);
    const auto env = discovery_env(home, claude_env.string(), codex_env.string());

    const auto stores = claude.discover(env);

    REQUIRE(stores.has_value());
    REQUIRE(stores->size() == 2);
    CHECK(stores->at(0).root == claude_env);
    CHECK(stores->at(0).tier == biv::adapters::DiscoveryTier::env);
    CHECK(stores->at(1).root == claude_default);
    CHECK(stores->at(1).tier == biv::adapters::DiscoveryTier::defaults);
    for (const auto& store : *stores) {
      REQUIRE(store.locators.size() == 1);
      CHECK(store.locators.front().kind == "sessions_root");
      CHECK(store.locators.front().path == store.root / "projects");
      CHECK_FALSE(store.archived);
    }
    // PARITY: the same matrix against codex yields the same set shape (env first, then defaults).
    const auto codex_stores = codex.discover(env);
    REQUIRE(codex_stores.has_value());
    CHECK(tiers(*codex_stores) == tiers(*stores));
    REQUIRE(codex_stores->size() == 2);
    CHECK(codex_stores->at(0).root == codex_env);
    CHECK(codex_stores->at(1).root == codex_default);
  }

  SECTION("ROW 2: env set and lexically equal to the default -> ONE store (env)") {
    fs::create_directories(claude_default / "projects");
    fs::create_directories(codex_default);
    // A collapsing spelling: "<home>/./.claude" normalizes to the default (the reference shape's
    // lexically_normal() guard); a trailing-slash spelling would NOT collapse — inherited, not tested here.
    const auto claude_spelling = (home / "." / ".claude").string();
    const auto codex_spelling = (home / "." / ".codex").string();
    const auto env = discovery_env(home, claude_spelling, codex_spelling);

    const auto stores = claude.discover(env);

    REQUIRE(stores.has_value());
    REQUIRE(stores->size() == 1);
    CHECK(stores->front().tier == biv::adapters::DiscoveryTier::env);
    CHECK(stores->front().root == fs::path{claude_spelling});
    const auto codex_stores = codex.discover(env);
    REQUIRE(codex_stores.has_value());
    CHECK(tiers(*codex_stores) == tiers(*stores));
    REQUIRE(codex_stores->size() == 1);
    CHECK(codex_stores->front().root == fs::path{codex_spelling});
  }

  SECTION("ROW 3: env unset, default exists -> ONE store (defaults)") {
    fs::create_directories(claude_default / "projects");
    fs::create_directories(codex_default);
    const auto env = discovery_env(home, std::nullopt, std::nullopt);

    const auto stores = claude.discover(env);

    REQUIRE(stores.has_value());
    REQUIRE(stores->size() == 1);
    CHECK(stores->front().root == claude_default);
    CHECK(stores->front().tier == biv::adapters::DiscoveryTier::defaults);
    const auto codex_stores = codex.discover(env);
    REQUIRE(codex_stores.has_value());
    CHECK(tiers(*codex_stores) == tiers(*stores));
  }

  SECTION("ROW 4: neither -> ZERO stores") {
    const auto env = discovery_env(home, std::nullopt, std::nullopt);

    const auto stores = claude.discover(env);

    REQUIRE(stores.has_value());
    CHECK(stores->empty());
    const auto codex_stores = codex.discover(env);
    REQUIRE(codex_stores.has_value());
    CHECK(codex_stores->empty());
  }

  SECTION("ROW 5: (pinned interim, NOT c1 §7 dedupe/provenance compliance) one session id in both stores -> pack refuses") {
    const auto source = root / "proj";
    fs::create_directories(source);
    write_file(source / "work.txt", "workspace");
    const std::string session_id = "aaaaaaaa-1111-4000-8000-000000000055";
    const std::string transcript = "{\"type\":\"user\",\"cwd\":\"" + source.generic_string() +
                                   "\",\"sessionId\":\"" + session_id + "\",\"version\":\"2.1.202\"}\n";
    write_file(claude_env / "projects" / "project" / (session_id + ".jsonl"), transcript);
    write_file(claude_default / "projects" / "project" / (session_id + ".jsonl"), transcript);
    // version 2.1.202 is at/above the claude minimum: a BELOW-minimum copy is OMITTED with a
    // SessionBelowMinimumOmitted warning (tests/test_pack.cpp:684-720) and would never reach the
    // duplicate-id gate — the fixture must be collectable for ROW 5 to prove anything.
    const ScopedEnvVar scoped_home{"HOME", home.string()};
    const ScopedEnvVar scoped_claude{"CLAUDE_CONFIG_DIR", claude_env.string()};
    const ScopedEnvVar scoped_codex{"CODEX_HOME", (root / "absent-codex").string()};
    const ScopedEnvVar scoped_sqlite{"CODEX_SQLITE_HOME", (root / "absent-sqlite").string()};

    const auto refused = biv::pack::pack(source);

    REQUIRE_FALSE(refused.has_value());
    CHECK(refused.error().kind == biv::ErrKind::ArchiveWriteFailed);
    CHECK(refused.error().detail == "adapter-session-invalid");

    // The discriminator: the SAME id in ONE store only packs, with exactly one claude session —
    // so the refusal above is driven by BOTH stores being discovered, not by a broken fixture.
    fs::remove(claude_default / "projects" / "project" / (session_id + ".jsonl"));
    const auto packed = biv::pack::pack(source);
    REQUIRE(packed.has_value());
    CHECK(std::ranges::count_if(packed->agent_sessions,
                                [](const auto& entry) { return entry.agent == "claude-code"; }) == 1);
  }

  fs::remove_all(root);
}
```

- [ ] **Step 3: run it RED at the base bytes — FAIL-CLOSED (F1)** — **(EXECUTED under `impl-2` 2026-09-06; evidence of record = `$EVID/prior/`; NOT re-run in rev6 — see the RESUME CHECKPOINT)** — three separately proven stages, none masked: (i) the build: `b=0; cmake --build --preset ci-macos > "$EVID/red-build.log" 2>&1 || b=$?; printf 'red_build_rc=%s\n' "$b" > "$EVID/red-build.rc"; [ "$b" -eq 0 ] || STOP`; (ii) the run, status CAPTURED and REQUIRED NONZERO, `-w UnmatchedTestSpec` so an unmatched name is an explicit nonzero exit (VALIDATED 2026-09-06 on the built Catch2 v3.7.1 binary: a non-matching name → rc 3 with the flag, rc 2 without it, both printing "No test cases matched"; the existing discover case with the flag → rc 0; `NoTests` is NOT a recognised warning in this Catch2 — rc 1 "Unrecognised warning option" — caught by executing the written form): `t=0; "${OBS_ENV[@]}" ./build/ci-macos/biv_tests -w UnmatchedTestSpec "Claude adapter discovery returns every store found: env and default both searched with codex parity (c1 §7)" -r xml > "$EVID/witness-red.xml" 2> "$EVID/witness-red.stderr" || t=$?; printf 'red_test_rc=%s\n' "$t" > "$EVID/witness-red.rc"; [ "$t" -ne 0 ] || STOP; [ -s "$EVID/witness-red.xml" ] || STOP`; (iii) the PARSE of the retained XML — ROW 1 and ROW 5 the ONLY red leaves, ROWS 2–4 green, all five present exactly once, the TestCase name exact: `p=0; python3 "$EVID/witness.py" "$EVID/witness-red.xml" red > "$EVID/witness-red.verdict" || p=$?; [ "$p" -eq 0 ] && [ -s "$EVID/witness-red.verdict" ] || STOP`. EXPECTED CAUSES: ROW 1 fails at `stores->size() == 2` (today's early return yields 1); ROW 5 fails at `REQUIRE_FALSE(refused.has_value())` (today only the env store is collected, so pack succeeds). Any OTHER red leaf, a green ROW 1 or ROW 5, a missing leaf, or a parser exit ≠ 0 = STOP: a fixture/model defect is fixed in the TEST and Step 3 re-runs from (i); a product-behaviour cause outside the discover body → STOP UP (S-CP-4).

- [ ] **Step 4: the discover body — the reference shape** (replace `claude_code.cpp:570-596` exactly; everything before :570 and after :596 byte-identical):

```cpp
  expected<std::vector<Store>> discover(const Env& env) const override {
    std::vector<Store> stores;
    auto append_store = [&](const fs::path& root, DiscoveryTier tier) {
      stores.push_back(Store{.root = root,
                             .locators = {StoreLocator{.kind = "sessions_root", .path = root / "projects"}},
                             .tier = tier,
                             .archived = false});
    };
    std::error_code ec;
    std::optional<fs::path> env_root;
    if (env.getenv) {
      auto configured = env.getenv("CLAUDE_CONFIG_DIR");
      if (configured.has_value() && fs::exists(*configured, ec)) {
        env_root = fs::path{*configured};
        append_store(*env_root, DiscoveryTier::env);
      }
    }

    const auto root = env.home / ".claude";
    if (fs::exists(root, ec) &&
        (!env_root.has_value() || root.lexically_normal() != env_root->lexically_normal())) {
      append_store(root, DiscoveryTier::defaults);
    }
    return stores;
  }
```

(`<optional>` is already included at :7. The shape is `codex.cpp:1193-1206` minus codex's sqlite/archived locators — the ONLY differences a side-by-side read may show are the locator kind/path (`projects`) and the absence of the archived twin; anything else is V-CP-2.)

- [ ] **Step 5: GREEN — under the observer environment (F2)** — (i) `b=0; cmake --build --preset ci-macos > "$EVID/green-build.log" 2>&1 || b=$?; [ "$b" -eq 0 ] || STOP`; (ii) the new case, status captured and REQUIRED ZERO, XML parsed in green mode: `t=0; "${OBS_ENV[@]}" ./build/ci-macos/biv_tests -w UnmatchedTestSpec "Claude adapter discovery returns every store found: env and default both searched with codex parity (c1 §7)" -r xml > "$EVID/witness-green.xml" 2> "$EVID/witness-green.stderr" || t=$?; printf 'green_test_rc=%s\n' "$t" > "$EVID/witness-green.rc"; [ "$t" -eq 0 ] && [ -s "$EVID/witness-green.xml" ] || STOP; p=0; python3 "$EVID/witness.py" "$EVID/witness-green.xml" green > "$EVID/witness-green.verdict" || p=$?; [ "$p" -eq 0 ] || STOP`; (iii) the existing discover case: `t=0; "${OBS_ENV[@]}" ./build/ci-macos/biv_tests -w UnmatchedTestSpec "Claude adapter discovers CLAUDE_CONFIG_DIR as an env-tier store" > "$EVID/existing-discover-1.log" 2>&1 || t=$?; [ "$t" -eq 0 ] || STOP`; (iv) the FULL macOS suite exactly as the workflow does, UNDER THE ENVIRONMENT — the P-state DISCLOSURE run (rev6; iso rev8: the C1 tripwire reds `harness-selftest` at P/C by design, the acceptance of record is Task 6 at H): `r=0; "${OBS_ENV[@]}" ctest --preset ci-macos -E '^safety-hardening$' --output-on-failure > "$EVID/ctest-macos-P.log" 2>&1 || r=$?; printf 'ctest_macos_P_rc=%s\n' "$r" > "$EVID/ctest-macos-P.rc"` (rc is DATA: nonzero EXPECTED); THE FAILING SET, REQUIRED EXACTLY `harness-selftest`: `f=0; grep -E '^[[:space:]]+[0-9]+ - .*\(Failed\)' "$EVID/ctest-macos-P.log" > "$EVID/ctest-macos-P.failed" || f=$?; [ "$f" -le 1 ] || STOP; s=0; sed -E 's/^[[:space:]]*[0-9]+ - ([^ ]+) .*/\1/' "$EVID/ctest-macos-P.failed" > "$EVID/ctest-macos-P.failed-names" || s=$?; [ "$s" -eq 0 ] || STOP; printf 'harness-selftest\n' > "$EVID/ctest-failed.expected"; d=0; diff "$EVID/ctest-failed.expected" "$EVID/ctest-macos-P.failed-names" > "$EVID/ctest-macos-P.failed.delta" || d=$?; [ "$d" -eq 0 ] || STOP` (VALIDATED 2026-09-07 in bash AND zsh on the implementer's REAL `ctest-macos-P.log`: f=0 s=0 → `harness-selftest`; a log with NO FAILED block → f=1, empty names, d=1 → STOP — correct: a GREEN P-state suite means the tripwire did not fire, itself a FINDING); the CAUSE must be the tripwire: `g=0; k=$(grep -c -F 'claude_adapter_file' "$EVID/ctest-macos-P.log") || g=$?; [ "$g" -le 1 ] || STOP; [ "$k" -ge 1 ] || STOP` (the implementer's log carries 33 such lines; a `harness-selftest` red WITHOUT the anchor name = a different cause → FINDING, STOP UP). Any other failing row, or `d` ≠ 0, is a FINDING routed UP with the log — never a further `env -u`, never an exclusion.
- [ ] **Step 6: fence self-check — ROUTED by the receipt (materialized, statuses kept — F4; rev9: F5 of `001126`)** — `resume_state=$(sed -n 's/^resume_state=//p' "$EVID/resume-state.txt"); [ "$resume_state" = i ] || [ "$resume_state" = ii ] || STOP`. STATE `i` ROUTE (the dirty worktree before the commit): `if [ "$resume_state" = i ]; then s=0; git status --porcelain > "$EVID/status-pre-P.txt" || s=$?; [ "$s" -eq 0 ] && [ -s "$EVID/status-pre-P.txt" ] || STOP; printf ' M src/adapters/claude_code/claude_code.cpp\n M tests/test_adapter_claude_collect.cpp\n' > "$EVID/status-pre-P.expected"; d=0; diff "$EVID/status-pre-P.expected" "$EVID/status-pre-P.txt" > "$EVID/status-pre-P.delta" || d=$?; [ "$d" -eq 0 ] || STOP; r=0; git diff -U0 -- src/adapters/claude_code/claude_code.cpp > "$EVID/claude-P.diff" || r=$?; [ "$r" -eq 0 ] && [ -s "$EVID/claude-P.diff" ] || STOP; g=0; grep -E '^@@' "$EVID/claude-P.diff" > "$EVID/claude-P.hunks" || g=$?; [ "$g" -eq 0 ] && [ -s "$EVID/claude-P.hunks" ] || STOP; h=0; python3 "$EVID/hunks.py" "$EVID/claude-P.hunks" 570 596 > "$EVID/claude-P.hunks.verdict" || h=$?; [ "$h" -eq 0 ] || STOP; r=0; git diff --numstat -- src/adapters/codex/ > "$EVID/codex-P.numstat" || r=$?; [ "$r" -eq 0 ] && [ ! -s "$EVID/codex-P.numstat" ] || STOP; fi` (the status names EXACTLY the two paths — 1 = an unexpected path → V-CP-1/3/5 STOP, 2+ = diff error STOP; at least one claude hunk MUST exist; every hunk within :570-596; codex untouched — empty is the expected content, checked after the status). STATE `ii` ROUTE (the fence on the EXISTING commit P): `if [ "$resume_state" = ii ]; then s=0; git status --porcelain > "$EVID/status-pre-P.txt" || s=$?; [ "$s" -eq 0 ] && [ ! -s "$EVID/status-pre-P.txt" ] || STOP; r=0; git diff -U0 bbf297e36a38a1fab8c2675f945098a0633f9f8b HEAD -- src/adapters/claude_code/claude_code.cpp > "$EVID/claude-P.diff" || r=$?; [ "$r" -eq 0 ] && [ -s "$EVID/claude-P.diff" ] || STOP; g=0; grep -E '^@@' "$EVID/claude-P.diff" > "$EVID/claude-P.hunks" || g=$?; [ "$g" -eq 0 ] && [ -s "$EVID/claude-P.hunks" ] || STOP; h=0; python3 "$EVID/hunks.py" "$EVID/claude-P.hunks" 570 596 > "$EVID/claude-P.hunks.verdict" || h=$?; [ "$h" -eq 0 ] || STOP; r=0; git diff --numstat bbf297e36a38a1fab8c2675f945098a0633f9f8b HEAD -- src/adapters/codex/ > "$EVID/codex-P.numstat" || r=$?; [ "$r" -eq 0 ] && [ ! -s "$EVID/codex-P.numstat" ] || STOP; fi` (the worktree is CLEAN; the four hunks of P within :570-596 — MEASURED 2026-09-08/09 at the retained worktree: verdict rc 0; codex numstat empty). Exactly one route runs.

- [ ] **Step 7: the PROVISIONAL commit P — BOUND here (CG-R7.7), no tag (F3); rev9: ROUTED by the receipt — ONE commit under state `i`, the EXISTING P under state `ii`, never a second commit, never an amend (F5 of `001126`)** — `resume_state=$(sed -n 's/^resume_state=//p' "$EVID/resume-state.txt"); [ "$resume_state" = i ] || [ "$resume_state" = ii ] || STOP`. STATE `i` ROUTE: `if [ "$resume_state" = i ]; then git add src/adapters/claude_code/claude_code.cpp tests/test_adapter_claude_collect.cpp && git commit -q -F "$EVID/message-P.txt" || STOP; fi` where `message-P.txt` = `adapters(claude): discover returns every store found (env + default), codex parity — PROVISIONAL, cells not yet transcribed` + a body naming the design pin and plan pin + the trailer line (written BEFORE this step from the plan's words). STATE `ii` ROUTE (no git write): `if [ "$resume_state" = ii ]; then [ "$(git rev-parse HEAD)" = 54954281b30cae113f399055fff106963a37a443 ] || STOP; fi`. THE BINDING (both states): `P=$(git rev-parse HEAD); [ -n "$P" ] || STOP; w=0; printf '%s\n' "$P" > "$EVID/P.txt" || w=$?; [ "$w" -eq 0 ] && [ -s "$EVID/P.txt" ] || STOP; e=0; git cat-file -e "${P}^{commit}" || e=$?; [ "$e" -eq 0 ] || STOP; [ "$(git rev-parse "${P}^")" = bbf297e36a38a1fab8c2675f945098a0633f9f8b ] || STOP; t=0; tree=$(git rev-parse "${P}^{tree}") || t=$?; [ "$t" -eq 0 ] && [ -n "$tree" ] || STOP; w=0; printf '%s\n' "$tree" > "$EVID/P.tree" || w=$?; [ "$w" -eq 0 ] && [ -s "$EVID/P.tree" ] || STOP; s=0; git status --porcelain > "$EVID/status-post-P.txt" || s=$?; [ "$s" -eq 0 ] && [ ! -s "$EVID/status-post-P.txt" ] || STOP` (P's parent is the pin in both states; the tree receipt's producer is status-captured and its receipt proven non-empty; the worktree is clean after binding). P is retained by this recorded object id: the branch reflog holds it after the amend (`git reflog show intg/r450-discover-parity` lists it); every later use re-reads `$EVID/P.txt` and re-proves `git cat-file -e "${P}^{commit}"` first. NO tag, NO extra ref (VALIDATED 2026-09-06 in bash AND zsh: `git cat-file -e "${sha}^{commit}"` → 0 for a real commit, 128 for a bogus sha (any nonzero STOPs); no `:` modifier can fire in `"${P}^{commit}"`). Under state `ii` the binding was MEASURED 2026-09-09 at the retained worktree: P = 54954281, parent the pin, tree f1eb8aec, status empty, reflog unchanged.

### Task 2 — observation at P on BOTH targets (the SOURCE of the literals; CG-R7.3/7.7, T-1)

**Files:** none modified. Execute `PL-intg-countgate-20260830.md` Task 1 Steps 3(d)–(g) and 4 (the PROVEN instrument — the five `-r xml` runs per target under `"${OBS_ENV[@]}"` (derived in Task 0 Step 5; NOT re-derived), the inverted-selection scout (e), the R-OBS-5 token scan (f) over the concatenated logs (`cat` stage status-proved, then the zero-match-aware `grep -c`), the run identity (g); the four-phase Linux container: Phase H / R / T / S at `git show 990ba3b:docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep1-20260827.md` Task 5 Step 3 :757-763 with R-OBS-6's in-container name-free proof) VERBATIM with these retargets ONLY: (a) the run head is `P` (`$(cat "$EVID/P.txt")`, `git cat-file -e "${P}^{commit}"` re-proved first), the working tree is the r450 worktree, and Phase T clones the BRANCH `intg/r450-discover-parity` from `/repo-ro` with the receipt `rev-parse HEAD == P`; (b) XMLs land in `$EVID/P/<binary>-<target>.xml` and tuples in `$EVID/P/tuples-<target>.txt` (each XML `[ -s ]`-checked; each sha256 recorded); (c) the ancestry proofs are `a=0; git merge-base --is-ancestor bbf297e36a38a1fab8c2675f945098a0633f9f8b "$P" || a=$?` (REQUIRE 0) and `a2=0; git merge-base --is-ancestor b065de1107161bb5df9543c09b50091365338c1c "$P" || a2=$?` (REQUIRE 0 — the count-gate repair is in the lineage), both recorded.

- [ ] **Step 1: macOS observation at P** — the five `-r xml` runs under `"${OBS_ENV[@]}"` (each `x=0; "${OBS_ENV[@]}" ./build/ci-macos/<binary> -r xml > "$EVID/P/<binary>-macos.xml" 2> "$EVID/P/<binary>-macos.stderr" || x=$?; printf '%s\n' "$x" > "$EVID/P/<binary>-macos.rc"; [ -s "$EVID/P/<binary>-macos.xml" ] || STOP` — the rc is DATA here: a binary with failures exits nonzero and its tuple still transcribes; a MISSING or empty XML is the STOP), then `u=0; python3 "$EVID/tuples.py" macos "$EVID"/P/biv_subprocess_tests-macos.xml "$EVID"/P/biv_repo_git_tests-macos.xml "$EVID"/P/biv_repo_engine_tests-macos.xml "$EVID"/P/biv_tests-macos.xml "$EVID"/P/biv_probe_tests-macos.xml > "$EVID/P/tuples-macos.txt" || u=$?; [ "$u" -eq 0 ] && [ -s "$EVID/P/tuples-macos.txt" ] || STOP` → `$EVID/P/tuples-macos.txt` (five lines `binary target successes failures expectedFailures skips xml_sha256` + one `expected_skips_observed macos n=… <names>` line); the per-SECTION green proof on the full-suite XML (acceptance criterion 2): `p=0; python3 "$EVID/witness.py" "$EVID/P/biv_tests-macos.xml" green > "$EVID/P/witness-green-macos.verdict" || p=$?; [ "$p" -eq 0 ] && [ -s "$EVID/P/witness-green-macos.verdict" ] || STOP` (the helper selects the named case inside the full run — VALIDATED 2026-09-06 on a synthetic full-suite XML with other cases present → 0); REQUIRE the `biv_tests` skipped-name SET == B's `expected_skips` names for macOS — by MEMBERSHIP, through the helper (rev8; the two producers order the names differently by construction): `k=0; python3 "$EVID/skipset.py" "$EVID/B-cells.txt" "$EVID/P/tuples-macos.txt" macos > "$EVID/P/skipset-macos.txt" || k=$?; printf 'skipset_P_macos_rc=%s\n' "$k" > "$EVID/P/skipset-macos.rc"; [ "$k" -eq 0 ] && [ -s "$EVID/P/skipset-macos.txt" ] || STOP` (5 = a set or count difference = the V-CG-5 routed FINDING, STOP UP — never an edit; 2 = a missing line, a producer defect, STOP). The scout (e) and token scan (f) as in the countgate plan (both under `"${OBS_ENV[@]}"`, statuses captured, `hits=0` REQUIRED).

- [ ] **Step 2: Linux observation at P** — the four-phase container (ubuntu:24.04 `--platform linux/amd64` `--init`; `nofile` soft raised to hard inside the runuser drop; R-OBS-6 name-free proof by name inside the container before the measurement stage; `cmake --preset ci` + build + the five `-r xml` runs + the workflow-equivalent `ctest --preset ci` run — at P the ctest stage's rc is DATA (nonzero EXPECTED, the C1 tripwire) and its log is copied out as `$EVID/P/ctest-linux-P.log`, then the failing set is extracted EXACTLY as Task 1 Step 5 (iv) (files `ctest-linux-P.failed`, `.failed-names`, `.failed.delta`; REQUIRED == `harness-selftest`; the `claude_adapter_file` cause grep ≥ 1) — each stage's rc in the ledger), XMLs + ctest log + per-stage rc ledger copied out to `$EVID/P/`, then the same `tuples.py linux` invocation over the five copied-out XMLs with `u=0; … || u=$?; [ "$u" -eq 0 ] && [ -s "$EVID/P/tuples-linux.txt" ] || STOP` → `$EVID/P/tuples-linux.txt`; the per-SECTION green proof on the copied-out Linux XML: `p=0; python3 "$EVID/witness.py" "$EVID/P/biv_tests-linux.xml" green > "$EVID/P/witness-green-linux.verdict" || p=$?; [ "$p" -eq 0 ] && [ -s "$EVID/P/witness-green-linux.verdict" ] || STOP`; REQUIRE the Linux `biv_tests` observed skip COUNT == B's Linux `skips` cell (1) — the Linux job has no `expected_skips` identity block; the observed skipped NAME(s) are recorded in the tuples file and the report (a count difference = FINDING, STOP UP).
- [ ] **Step 3: ENTRY + the consistency CHECK (CG-R7.1/7.3, T-4) — observed trigger, syntactic predictor** — (i) ENTRY: compare P's `biv_tests` tuples (both targets) with B's cells from `$EVID/B-cells.txt`: a DIFFERENCE in `successes` on both targets = census-changing act → Task 3 transcribes; EQUAL on either target = zero-delta on that target, which contradicts the predictor → FINDING, STOP UP (no transcription, no commit); `failures` and `expectedFailures` MUST be 0 and `skips` MUST equal B's on both targets; the other four binaries' tuples MUST equal B's cells (any difference = FINDING, STOP UP). (ii) the PREDICTOR, materialized: `r=0; git diff bbf297e36a38a1fab8c2675f945098a0633f9f8b "$P" -- tests > "$EVID/tests-P.diff" || r=$?; [ "$r" -eq 0 ] && [ -s "$EVID/tests-P.diff" ] || STOP; g=0; added=$(grep -c '^+TEST_CASE(' "$EVID/tests-P.diff") || g=$?; [ "$g" -le 1 ] || STOP; g2=0; removed=$(grep -c '^-TEST_CASE(' "$EVID/tests-P.diff") || g2=$?; [ "$g2" -le 1 ] || STOP; printf 'added=%s removed=%s\n' "$added" "$removed" > "$EVID/predictor.txt"` (zero matches exit 1 = VALID; 2+ = STOP); REQUIRE `added=1 removed=0`; (iii) the check: `observed_P(successes) − old_B(successes)` per target must equal `added − removed` = 1 — a CHECK on the record, never a source (the literal written in Task 3 is the XML value); any mismatch in either direction = FINDING routed UP (never a quiet re-observation, never an exclusion). Write `$EVID/bpc-table.txt` NOW with the old(B)/observed(P) columns (new(C) filled at Task 3 Step 3), values copied from `B-cells.txt` and `tuples-*.txt`.
- [ ] **Step 4: no-mutation proof** — `s=0; git status --porcelain > "$EVID/status-post-P-obs.txt" || s=$?; [ "$s" -eq 0 ] && [ ! -s "$EVID/status-post-P-obs.txt" ] || STOP` (the worktree is EMPTY after observation; the evidence lives under `$EVID`; build dirs are ignored); main-repo status vs `status-initial.txt` (rev10: the SAME pathspec as the snapshot — the two shared write surfaces excluded, everything else compared): `s=0; git -C /Users/jack/Programming/bivpak status --porcelain -- . ':(exclude).relays' ':(exclude)docs/sprints' > "$EVID/status-main-post-P.txt" || s=$?; [ "$s" -eq 0 ] || STOP; d=0; diff "$EVID/status-initial.txt" "$EVID/status-main-post-P.txt" > "$EVID/status-main-post-P.delta" || d=$?; [ "$d" -eq 0 ] || STOP`.

### Task 3 — transcribe the two literals FROM THE XML and amend P → C (one commit; C BOUND here)

**Files:** Modify `.github/workflows/s2-harness.yml:85` and `:326` (integer literals only).

- [ ] **Step 1: the transcription script — reads the XML, writes the literal, refuses anything else** (VALIDATED 2026-09-06 at the pair Planner's seat on a scratch copy of the workflow with two synthetic XMLs: correct block lines → the two literals replaced, all other bytes identical; a wrong anchor line → exit 3 with no write; a missing `OverallResultsCases` → exit 2 with no write):


Run: `x=0; python3 "$EVID/transcribe.py" .github/workflows/s2-harness.yml "$EVID/P/biv_tests-macos.xml" "$EVID/P/biv_tests-linux.xml" > "$EVID/transcribe.out" || x=$?; [ "$x" -eq 0 ] || STOP`.
- [ ] **Step 2: prove the workflow hunk is EXACTLY the two literals (CG-R7.4 (α); materialized — F4)** — `r=0; git diff --numstat -- .github/workflows/s2-harness.yml > "$EVID/workflow.numstat" || r=$?; [ "$r" -eq 0 ] && [ -s "$EVID/workflow.numstat" ] || STOP; printf '2\t2\t.github/workflows/s2-harness.yml\n' > "$EVID/workflow.numstat.expected"; d=0; diff "$EVID/workflow.numstat.expected" "$EVID/workflow.numstat" > "$EVID/workflow.numstat.delta" || d=$?; [ "$d" -eq 0 ] || STOP`; `r=0; git diff -U0 -- .github/workflows/s2-harness.yml > "$EVID/workflow.diff" || r=$?; [ "$r" -eq 0 ] && [ -s "$EVID/workflow.diff" ] || STOP; g=0; grep -E '^[-+][^-+]' "$EVID/workflow.diff" > "$EVID/workflow-hunk.txt" || g=$?; [ "$g" -eq 0 ] && [ -s "$EVID/workflow-hunk.txt" ] || STOP` (changed lines MUST exist → `g` 0); `a=0; n=$(awk 'END { print NR }' "$EVID/workflow-hunk.txt") || a=$?; [ "$a" -eq 0 ] && [ "$n" -eq 4 ] || STOP` (a single-stage line count with its own status — no pipeline; VALIDATED 2026-09-06 in bash AND zsh: 4-line file → n=4 a=0; missing file → a=2); `g=0; m=$(grep -c -E '^[-+][[:space:]]+"successes": [0-9]+,$' "$EVID/workflow-hunk.txt") || g=$?; [ "$g" -le 1 ] || STOP; [ "$m" -eq 4 ] || STOP` (all four changed lines are `successes` literals); the status names ONLY the workflow: `s=0; git status --porcelain > "$EVID/status-pre-C.txt" || s=$?; [ "$s" -eq 0 ] || STOP; printf ' M .github/workflows/s2-harness.yml\n' > "$EVID/status-pre-C.expected"; d=0; diff "$EVID/status-pre-C.expected" "$EVID/status-pre-C.txt" > "$EVID/status-pre-C.delta" || d=$?; [ "$d" -eq 0 ] || STOP`. Anything else = STOP to m-3.planner (through the pair Planner). (VALIDATED 2026-09-06 in bash AND zsh on the scratch transcription: numstat `2 2`, hunk 4 lines, `m=4`.)
- [ ] **Step 3: the ONE commit C = amend P; C BOUND here** — `git add .github/workflows/s2-harness.yml && git commit -q --amend -F "$EVID/message-C.txt"`. `message-C.txt`: subject `adapters(claude): discover returns every store found (env + default), codex parity; count-gate cells transcribed`; body: `Design pin: m2-r450-discover-fence-rev2-20260903 sha256 f2216ee606a03b0b5b0b7f4562fed52a7349219c28990e6ee3e89b0cc25e8c6f`; `Plan pin: intg-r450-discover-parity-plan-20260906 sha256 <this artifact's approved hash>`; `B=bbf297e36a38a1fab8c2675f945098a0633f9f8b (baseline; workflow values inherited) observed_head=P=<sha from P.txt> (provisional; source of the literals; reachable by object id / branch reflog; no tag) — C is this commit (its own sha cannot appear here; the tracked report binds it)`; `Observed cells at P (no arithmetic):` then the TEN `binary=… target=… run_id=… successes=… failures=… expectedFailures=… skips=… xml_sha256=…` lines from `$EVID/P/tuples-*.txt` exactly in `b065de1`'s form; the old(B)/observed(P) table from `bpc-table.txt`; the macOS and Linux run-identity + observer blocks (names only); the trailer `Co-Authored-By: Claude Fable 5.1 <noreply@anthropic.com>`. Then: `C=$(git rev-parse HEAD)`; `printf '%s\n' "$C" > "$EVID/C.txt"; [ -s "$EVID/C.txt" ] || STOP`; fill the new(C) column of `$EVID/bpc-table.txt` from the literals READ BACK from the committed workflow (`git show "${C}:.github/workflows/s2-harness.yml" > "$EVID/C-workflow.yml"` status-checked, then `c=0; python3 "$EVID/cells.py" "$EVID/C-workflow.yml" > "$EVID/C-cells.txt" || c=$?; [ "$c" -eq 0 ] && [ -s "$EVID/C-cells.txt" ] || STOP`).
- [ ] **Step 4: prove P → C (materialized; the `:(exclude)` pathspec VALIDATED 2026-09-06 in bash AND zsh on real commits: a workflow-only commit → rc 0; a product merge → rc 1)** — `P=$(cat "$EVID/P.txt"); C=$(cat "$EVID/C.txt"); e=0; git cat-file -e "${P}^{commit}" || e=$?; [ "$e" -eq 0 ] || STOP`; `r=0; git diff --numstat "$P" "$C" > "$EVID/p-to-c.numstat" || r=$?; [ "$r" -eq 0 ] && [ -s "$EVID/p-to-c.numstat" ] || STOP; d=0; diff "$EVID/workflow.numstat.expected" "$EVID/p-to-c.numstat" > "$EVID/p-to-c.numstat.delta" || d=$?; [ "$d" -eq 0 ] || STOP`; `q=0; git diff --quiet "$P" "$C" -- . ':(exclude).github/workflows/s2-harness.yml' || q=$?; [ "$q" -eq 0 ] || STOP` (1 = a non-workflow byte moved between P and C; 2+ = error; both STOP); `[ "$(git rev-parse "${C}^")" = bbf297e36a38a1fab8c2675f945098a0633f9f8b ] || STOP`; `c=0; n=$(git rev-list --count "origin/main..${C}^") || c=$?; [ "$c" -eq 0 ] && [ "$n" -eq 0 ] || STOP` (the cut-point measure). Record all in `$EVID/p-to-c-proof.txt`.

### Task 4 — RE-OBSERVATION OF RECORD at C, both targets (the runs the tracked report and IMPL return carry)

- [ ] **Step 1:** repeat Task 2 Steps 1–2 with the run head `C` (`$(cat "$EVID/C.txt")`; `git cat-file -e "${C}^{commit}"` proved) → `$EVID/C/…` (ten tuples via the two status-captured `tuples.py` invocations exactly as Task 2, XML sha256, run identities, token scan, in-container name-free proof, and the two per-SECTION green proofs `p=0; python3 "$EVID/witness.py" "$EVID/C/biv_tests-macos.xml" green > "$EVID/C/witness-green-macos.verdict" || p=$?; [ "$p" -eq 0 ] && [ -s "$EVID/C/witness-green-macos.verdict" ] || STOP` and the same for `$EVID/C/biv_tests-linux.xml` → `$EVID/C/witness-green-linux.verdict`) PLUS the C-state DISCLOSURE runs (rev6 — NOT the acceptance runs; those are Task 6 at H): macOS `r=0; "${OBS_ENV[@]}" ctest --preset ci-macos -E '^safety-hardening$' --output-on-failure > "$EVID/C/ctest-macos-C.log" 2>&1 || r=$?; printf 'ctest_macos_C_rc=%s\n' "$r" > "$EVID/C/ctest-macos-C.rc"` (rc DATA) with the failing set extracted EXACTLY as Task 1 Step 5 (iv) (files `$EVID/C/ctest-macos-C.failed`, `.failed-names`, `.failed.delta` against `$EVID/ctest-failed.expected`; REQUIRED == `harness-selftest`; cause grep ≥ 1), and the Linux ctest stage's log copied out as `$EVID/C/ctest-linux-C.log` with the same extraction (REQUIRED == `harness-selftest`). NO discriminator at C (it cannot separate here — Global constraints, ACCEPTANCE GATE).
- [ ] **Step 2: the gate's own semantics, locally (CG-R7.7: C's observations == P's observations == C's literals)** — `q=0; python3 "$EVID/gate.py" "$EVID/C-cells.txt" "$EVID/P/tuples-macos.txt" "$EVID/P/tuples-linux.txt" "$EVID/C/tuples-macos.txt" "$EVID/C/tuples-linux.txt" > "$EVID/C/gate-equality.txt" || q=$?; printf 'gate_rc=%s\n' "$q" > "$EVID/C/gate.rc"; [ "$q" -eq 0 ] && [ -s "$EVID/C/gate-equality.txt" ] || STOP` (the STATUS is the gate — an `equal=no` run prints ten lines and exits 5: VALIDATED 2026-09-06, the altered-C mutant → q=5, output non-empty, STOP reached): for each of the ten cells one line `binary target literal_C observed_P observed_C equal=yes|no`; ANY `no` = FINDING, STOP UP (no re-transcription, no amend — the plan returns to the pair Planner); the `biv_tests` skipped-name SET at C == B's macOS `expected_skips` names by MEMBERSHIP (rev8): `k=0; python3 "$EVID/skipset.py" "$EVID/B-cells.txt" "$EVID/C/tuples-macos.txt" macos > "$EVID/C/skipset-macos.txt" || k=$?; printf 'skipset_C_macos_rc=%s\n' "$k" > "$EVID/C/skipset-macos.rc"; [ "$k" -eq 0 ] && [ -s "$EVID/C/skipset-macos.txt" ] || STOP`; and the Linux skip count == B's Linux `skips` cell.

- [ ] **Step 3: no-mutation proof** as Task 2 Step 4 (files `status-post-C-obs.txt`, `status-main-post-C.*`).

### Task 5 — H: the harness follow-through commit (iso rev8 write set; child of C; BEFORE the acceptance run; H BOUND here)

**Files:** Modify `harness/selftest/stub_biv.py:140-146`; Modify `harness/selftest/test_store_isolation.py:110-123`; Modify `harness/bivharness/e3.py:75`. Nothing else (V-FT-1).

**Interfaces:** consumes `$EVID/C.txt` (bound at Task 3 Step 3), `$EVID/base-hashes.txt` (Task 0 Step 4), the eleven helpers and the two walk inventories (Task 0 Step 0b), `"${OBS_ENV[@]}"` (Task 0 Step 5). Produces `$EVID/H.txt` (H's identity, bound at Step 5), `$EVID/H.numstat.expected`, the fidelity/fence/pytest evidence Task 6 and Task 7 cite.

- [ ] **Step 0: preconditions, the WALK re-run at C, S-FT-1/S-FT-3/S-FT-4 checks (materialized, statuses kept)** — `C=$(cat "$EVID/C.txt"); e=0; git cat-file -e "${C}^{commit}" || e=$?; [ "$e" -eq 0 ] || STOP; [ "$(git rev-parse HEAD)" = "$C" ] || STOP; s=0; git status --porcelain > "$EVID/status-pre-H.txt" || s=$?; [ "$s" -eq 0 ] && [ ! -s "$EVID/status-pre-H.txt" ] || STOP` (the tree is C exactly; Task 4's no-mutation proof stands); harness untouched by C: `q=0; git diff --quiet bbf297e36a38a1fab8c2675f945098a0633f9f8b "$C" -- harness || q=$?; [ "$q" -eq 0 ] || STOP` (1 = a harness byte in C → V-CP-5 red, STOP UP; 2+ = error). THE WALK (Global constraints; S-FT-2): `w=0; grep -rn -E 'claude_code\.cpp|claude_adapter_file' harness/ --include='*.py' > "$EVID/walk-A.txt" || w=$?; [ "$w" -eq 0 ] && [ -s "$EVID/walk-A.txt" ] || STOP; s=0; sed -E 's/^([^:]+:[0-9]+):.*$/\1/' "$EVID/walk-A.txt" > "$EVID/walk-A.inv" || s=$?; [ "$s" -eq 0 ] || STOP; o=0; sort "$EVID/walk-A.inv" > "$EVID/walk-A.sorted" || o=$?; [ "$o" -eq 0 ] || STOP; d=0; diff "$EVID/walk-A.expected" "$EVID/walk-A.sorted" > "$EVID/walk-A.delta" || d=$?; [ "$d" -eq 0 ] || STOP`; `w=0; grep -rn -E 'CLAUDE_CONFIG_DIR|/\.claude|"\.claude"|SESSION_LOCATIONS|LIVE_STORE_SELECTORS' harness/ --include='*.py' --include='*.json' > "$EVID/walk-B.txt" || w=$?; [ "$w" -eq 0 ] && [ -s "$EVID/walk-B.txt" ] || STOP; s=0; sed -E 's/^([^:]+:[0-9]+):.*$/\1/' "$EVID/walk-B.txt" > "$EVID/walk-B.inv" || s=$?; [ "$s" -eq 0 ] || STOP; o=0; sort "$EVID/walk-B.inv" > "$EVID/walk-B.sorted" || o=$?; [ "$o" -eq 0 ] || STOP; d=0; diff "$EVID/walk-B.expected" "$EVID/walk-B.sorted" > "$EVID/walk-B.delta" || d=$?; [ "$d" -eq 0 ] || STOP` (VALIDATED 2026-09-07 in bash AND zsh at the candidate worktree — whose `harness/` equals B's: 11 and 47 lines, both deltas empty; a `d` of 1 = a reference this plan did not walk → S-FT-2 STOP UP; the `--include` filter keeps `__pycache__` binaries out). THE ANCHORS SURVIVE AT C (the mutant fixtures' string anchors, each EXACTLY ONCE): `for a in '.globs = {"projects/*/*.jsonl"}' '.path = root / "projects"' '    std::vector<Store> stores;' 'const Inventory& claude_inventory()'; do g=0; k=$(grep -c -F -- "$a" src/adapters/claude_code/claude_code.cpp) || g=$?; [ "$g" -le 1 ] && [ "$k" -eq 1 ] || STOP; printf '%s -> %s\n' "$a" "$k"; done > "$EVID/anchors-at-C.txt"; [ -s "$EVID/anchors-at-C.txt" ] || STOP` (measured 2026-09-07 at the candidate bytes: 1/1/1/1). THE E3 MODEL LINES (S-FT-3 — the re-validation needs ONLY the re-pin): `g=0; k=$(grep -c -F '    "claude-code": ("CLAUDE_CONFIG_DIR",),' harness/bivharness/e3.py) || g=$?; [ "$g" -le 1 ] && [ "$k" -eq 1 ] || STOP; g=0; k=$(grep -c -F '    "claude-code": ("projects",),' harness/bivharness/e3.py) || g=$?; [ "$g" -le 1 ] && [ "$k" -eq 1 ] || STOP` (both discovered stores locate `projects`; the selector stays `CLAUDE_CONFIG_DIR`). THE CODEX ANCHOR AND CODEX BYTES (S-FT-4): `g=0; k=$(grep -c -F '08480a19a7194f79078d01091f2f24d7d23abb8483c7a2bff0138d6de52e6d5d' harness/bivharness/e3.py) || g=$?; [ "$g" -le 1 ] && [ "$k" -eq 1 ] || STOP; h=0; shasum -a 256 src/adapters/codex/codex.cpp > "$EVID/codex-at-C.sha" || h=$?; [ "$h" -eq 0 ] || STOP; g=0; k=$(grep -c -F "$(cut -d' ' -f1 "$EVID/codex-at-C.sha")" "$EVID/base-hashes.txt") || g=$?; [ "$g" -le 1 ] && [ "$k" -eq 1 ] || STOP` (the candidate's codex digest appears once in the base-hash file — the codex line; the claude and test lines differ by construction). S-FT-1 — THE STALE MODEL PROVEN STALE (the must-be-NO of the fidelity check): `n=0; .venv-harness/bin/python "$EVID/h_fidelity.py" harness/selftest > "$EVID/fidelity-pre-H.txt" 2>&1 || n=$?; printf 'fidelity_pre_rc=%s\n' "$n" > "$EVID/fidelity-pre-H.rc"; [ "$n" -eq 5 ] || STOP` (VALIDATED 2026-09-07: rc 5, ROW 1 and ROW 5 `MISMATCH`; a 0 here means the stub already models parity — a walk miss — STOP UP; any other value = the helper or the venv failed — STOP).
- [ ] **Step 1: the three edits — by the helpers, never by hand** — `a=0; python3 "$EVID/h_stub.py" harness/selftest/stub_biv.py > "$EVID/h-stub.out" 2>&1 || a=$?; [ "$a" -eq 0 ] && [ -s "$EVID/h-stub.out" ] || STOP`; `b=0; python3 "$EVID/h_test.py" harness/selftest/test_store_isolation.py > "$EVID/h-test.out" 2>&1 || b=$?; [ "$b" -eq 0 ] && [ -s "$EVID/h-test.out" ] || STOP`; `c=0; python3 "$EVID/h_e3pin.py" harness/bivharness/e3.py src/adapters/claude_code/claude_code.cpp > "$EVID/h-e3pin.out" 2>&1 || c=$?; [ "$c" -eq 0 ] && [ -s "$EVID/h-e3pin.out" ] || STOP`; THE LITERAL IS THE THREE-SEAT DIGEST (V-FT-3): `g=0; k=$(grep -c -F 'new=4e105052a17b7e0d99bfeca28ac45cac1f6ed3c5ba0e9ba9ec62a34e530a3a51' "$EVID/h-e3pin.out") || g=$?; [ "$g" -le 1 ] && [ "$k" -eq 1 ] || STOP` (a different digest = C's `claude_code.cpp` ≠ the bytes three seats measured → STOP UP, never a re-pin to whatever is there). (All three VALIDATED 2026-09-07 in bash AND zsh on a scratch copy of the candidate: statuses 0; a second application of each → 3 with no write.)
- [ ] **Step 2: L1 fidelity at the H stub (V-FT-4; the must-be-YES)** — `n=0; .venv-harness/bin/python "$EVID/h_fidelity.py" harness/selftest > "$EVID/fidelity-H.txt" 2>&1 || n=$?; printf 'fidelity_rc=%s\n' "$n" > "$EVID/fidelity-H.rc"; [ "$n" -eq 0 ] && [ -s "$EVID/fidelity-H.txt" ] || STOP` (five rows `ok`: ROW 1 `['CLAUDE_CONFIG_DIR', 'HOME']`, ROW 2 `['CLAUDE_CONFIG_DIR']`, ROW 3 `['HOME']`, ROW 4 `[]`, ROW 5 `['CLAUDE_CONFIG_DIR', 'HOME']` — VALIDATED 2026-09-07 on the H stub). The codex SHAPE is read at m-3's review: the new claude block is the codex block (:150-160) with `codex_home`/`CODEX_HOME`/`.codex` → `ccd`/`CLAUDE_CONFIG_DIR`/`.claude` and the local names `claude_roots`/`claude_env_root`.
- [ ] **Step 3: fence proofs on the working tree (V-FT-1/2/5; materialized)** — `s=0; git status --porcelain > "$EVID/status-pre-H-commit.txt" || s=$?; [ "$s" -eq 0 ] && [ -s "$EVID/status-pre-H-commit.txt" ] || STOP; printf ' M harness/bivharness/e3.py\n M harness/selftest/stub_biv.py\n M harness/selftest/test_store_isolation.py\n' > "$EVID/status-pre-H-commit.expected"; d=0; diff "$EVID/status-pre-H-commit.expected" "$EVID/status-pre-H-commit.txt" > "$EVID/status-pre-H-commit.delta" || d=$?; [ "$d" -eq 0 ] || STOP` (exactly the three files; `__pycache__/` is ignored — proven at Task 0 Step 2). `r=0; git diff --numstat > "$EVID/H.numstat" || r=$?; [ "$r" -eq 0 ] && [ -s "$EVID/H.numstat" ] || STOP; printf '1\t1\tharness/bivharness/e3.py\n9\t5\tharness/selftest/stub_biv.py\n2\t2\tharness/selftest/test_store_isolation.py\n' > "$EVID/H.numstat.expected"; d=0; diff "$EVID/H.numstat.expected" "$EVID/H.numstat" > "$EVID/H.numstat.delta" || d=$?; [ "$d" -eq 0 ] || STOP` (VALIDATED 2026-09-07 in bash AND zsh on the scratch: equal). THE ONE `e3.py` BYTE (V-FT-2): `r=0; git diff -U0 -- harness/bivharness/e3.py > "$EVID/e3-H.diff" || r=$?; [ "$r" -eq 0 ] && [ -s "$EVID/e3-H.diff" ] || STOP; g=0; n=$(grep -c -E '^[-+][^-+]' "$EVID/e3-H.diff") || g=$?; [ "$g" -eq 0 ] && [ "$n" -eq 2 ] || STOP; g=0; m=$(grep -c -E '^[-+]        "[0-9a-f]{64}",$' "$EVID/e3-H.diff") || g=$?; [ "$g" -eq 0 ] && [ "$m" -eq 2 ] || STOP; g=0; k=$(grep -c -F '@@ -75 +75 @@' "$EVID/e3-H.diff") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP` (two changed lines, both 64-hex literal lines, one hunk at :75 — VALIDATED 2026-09-07 in bash AND zsh: n=2 m=2 k=1). THE INVENTORY (V-FT-5): `g=0; k=$(grep -c 'NAMED MUTANT' harness/selftest/test_store_isolation.py) || g=$?; [ "$g" -le 1 ] && [ "$k" -eq 7 ] || STOP; g=0; k=$(grep -c '^def test_' harness/selftest/test_store_isolation.py) || g=$?; [ "$g" -le 1 ] && [ "$k" -eq 11 ] || STOP; printf 'markers=7 tests=11\n' > "$EVID/inventory-H.txt"`; the codex anchor still once: `g=0; k=$(grep -c -F '08480a19a7194f79078d01091f2f24d7d23abb8483c7a2bff0138d6de52e6d5d' harness/bivharness/e3.py) || g=$?; [ "$g" -le 1 ] && [ "$k" -eq 1 ] || STOP`.
- [ ] **Step 4: the targeted selftest at H — under the observer environment, the worktree's venv, from `harness/` (the ctest row's own cwd)** — `t=0; (cd harness && "${OBS_ENV[@]}" ../.venv-harness/bin/python -m pytest selftest/test_store_isolation.py -q -p no:cacheprovider) > "$EVID/pytest-store-isolation-H.log" 2>&1 || t=$?; printf 'pytest_si_rc=%s\n' "$t" > "$EVID/pytest-store-isolation-H.rc"; [ "$t" -eq 0 ] || STOP; g=0; k=$(grep -c -E '^11 passed' "$EVID/pytest-store-isolation-H.log") || g=$?; [ "$g" -le 1 ] && [ "$k" -eq 1 ] || STOP` (VALIDATED 2026-09-07 in bash AND zsh on the scratch H under the unset environment: rc 0, `11 passed in 1.27s`); then the whole harness selftest — the `harness-selftest` row's own command, as a pre-proof of Task 6 (rc REQUIRED 0; the summary line recorded): `t=0; (cd harness && "${OBS_ENV[@]}" ../.venv-harness/bin/python -m pytest selftest -q -p no:cacheprovider) > "$EVID/pytest-selftest-H.log" 2>&1 || t=$?; printf 'pytest_selftest_rc=%s\n' "$t" > "$EVID/pytest-selftest-H.rc"; [ "$t" -eq 0 ] || STOP` (VALIDATED 2026-09-07: `1014 passed`, rc 0 at the scratch H; the same command at the scratch C-state → `53 failed, 961 passed`, rc 1 — the tripwire, every failure in `test_e3_asserts.py`). A red here = FINDING routed UP with the log (S-FT-3 if the cause is an E3 model line).
- [ ] **Step 5: the commit H — child of C; H BOUND here (CG-R7.7 order P → C → H)** — `git add harness/bivharness/e3.py harness/selftest/stub_biv.py harness/selftest/test_store_isolation.py && git commit -q -F "$EVID/message-H.txt"` where `message-H.txt` = subject `harness: claude discovery model follows c1 §7 parity (stub codex-shaped append, HOME mutant asserts both canaries, E3 anchor re-pinned) — m-3 follow-through, iso rev8` + body: `Design pin: iso rev8 master/domains/m-3-restore-cli/design/2026-09-01-e2-store-isolation-r437.md sha256 00046a657abd6c5792e3c6222c8690b39f1a773ecbc2473ca9af2845a95813af (V-FT-1..8 / S-FT-1..4)`; `Plan pin: intg-r450-discover-parity-plan-20260906 sha256 <this artifact's approved hash>`; `Parent C=<sha from C.txt> (the R-4.50 candidate; product bytes fixed)`; `claude_adapter_file anchor: old cd1f8bc8f7ab87cf15251d84ad7e59c618a22f3c19b9633ff193350782800851 -> new <the digest from h-e3pin.out> = sha256(src/adapters/claude_code/claude_code.cpp @ C)`; the five fidelity rows from `fidelity-H.txt`; `NAMED MUTANT markers 7, tests 11 (unchanged)`; the trailer `Co-Authored-By: Claude Fable 5.1 <noreply@anthropic.com>`. Then: `H=$(git rev-parse HEAD); printf '%s\n' "$H" > "$EVID/H.txt"; [ -s "$EVID/H.txt" ] || STOP; e=0; git cat-file -e "${H}^{commit}" || e=$?; [ "$e" -eq 0 ] || STOP; [ "$(git rev-parse "${H}^")" = "$C" ] || STOP` (H^ == C; `H.txt` is never rewritten). NO tag, NO extra ref.
- [ ] **Step 6: prove C → H (materialized; the `:(exclude)` pathspec form VALIDATED 2026-09-07 in bash AND zsh on a scratch repository holding exactly C→H: `:(exclude)harness/` → 0; `:(exclude)harness/bivharness/e3.py` alone → 1, the discriminator)** — `r=0; git diff --numstat "$C" "$H" > "$EVID/c-to-h.numstat" || r=$?; [ "$r" -eq 0 ] && [ -s "$EVID/c-to-h.numstat" ] || STOP; d=0; diff "$EVID/H.numstat.expected" "$EVID/c-to-h.numstat" > "$EVID/c-to-h.numstat.delta" || d=$?; [ "$d" -eq 0 ] || STOP`; `q=0; git diff --quiet "$C" "$H" -- . ':(exclude)harness/' || q=$?; [ "$q" -eq 0 ] || STOP` (1 = a non-harness byte moved between C and H → V-FT-1/6 red; 2+ = error); `[ "$(git rev-parse "${H}^^")" = bbf297e36a38a1fab8c2675f945098a0633f9f8b ] || STOP; c=0; n=$(git rev-list --count "origin/main..${H}") || c=$?; [ "$c" -eq 0 ] && [ "$n" -eq 2 ] || STOP` (exactly C and H above the published base — the cut-point measure at the PR head; the `"${H}^^"` and `"origin/main..${H}"` forms VALIDATED 2026-09-07 in bash AND zsh). Record all in `$EVID/c-to-h-proof.txt`. `s=0; git status --porcelain > "$EVID/status-post-H.txt" || s=$?; [ "$s" -eq 0 ] && [ ! -s "$EVID/status-post-H.txt" ] || STOP`.

### Task 6 — THE ACCEPTANCE OF RECORD at the PR head H, both targets (iso rev8; master `134909`): suites REQUIRED green, the discriminator executed, the cells UNMOVED, the HOME real-binary demonstration

**Files:** none modified. `H=$(cat "$EVID/H.txt"); e=0; git cat-file -e "${H}^{commit}" || e=$?; [ "$e" -eq 0 ] || STOP; [ "$(git rev-parse HEAD)" = "$H" ] || STOP; mkdir -p "$EVID/H"`.

- [ ] **Step 1: macOS at H — the discriminator, then the acceptance run, then the census runs** — (i) `b=0; cmake --build --preset ci-macos > "$EVID/H/build-H.log" 2>&1 || b=$?; [ "$b" -eq 0 ] || STOP` (no product byte changed since C; the build is a no-op that proves the binaries are current). (ii) THE DISCRIMINATOR (R-OBS-3; exactly Task 0 Step 5's (c) form, executed at the only later head where `harness-selftest` is expected green): arm 1 AS-IS: `rc1=0; ctest --preset ci-macos -R '^harness-selftest$' > "$EVID/H/discriminator-as-is.log" 2>&1 || rc1=$?`; arm 2 under the environment: `rc2=0; "${OBS_ENV[@]}" ctest --preset ci-macos -R '^harness-selftest$' > "$EVID/H/discriminator-unset.log" 2>&1 || rc2=$?`; `present_count=$(cut -d= -f2 "$EVID/observer-present-count.txt")`; the PREDICATE as data: `rc2 == 0` (else FINDING, STOP UP — hygiene did not explain the red) AND (`rc1 != 0` iff `present_count > 0`) (else FINDING, STOP UP); `printf 'rc1=%s rc2=%s present_count=%s iff=%s hygiene=%s\n' … > "$EVID/H/discriminator-predicate.txt"`; both PASS is the gate; a red arm 2 = FINDING UP with the logs, never a second run. (iii) THE ACCEPTANCE RUN (REQUIRED rc 0 — criterion 4): `r=0; "${OBS_ENV[@]}" ctest --preset ci-macos -E '^safety-hardening$' --output-on-failure > "$EVID/H/ctest-macos-H.log" 2>&1 || r=$?; printf 'ctest_macos_H_rc=%s\n' "$r" > "$EVID/H/ctest-macos-H.rc"; [ "$r" -eq 0 ] || STOP` (a red here is a FINDING routed UP with the log — never a further `env -u`, never an exclusion). (iv) the five `-r xml` runs at H exactly as Task 2 Step 1 (files `$EVID/H/<binary>-macos.xml`, `.stderr`, `.rc`; each XML `[ -s ]`) and `u=0; python3 "$EVID/tuples.py" macos "$EVID"/H/biv_subprocess_tests-macos.xml "$EVID"/H/biv_repo_git_tests-macos.xml "$EVID"/H/biv_repo_engine_tests-macos.xml "$EVID"/H/biv_tests-macos.xml "$EVID"/H/biv_probe_tests-macos.xml > "$EVID/H/tuples-macos.txt" || u=$?; [ "$u" -eq 0 ] && [ -s "$EVID/H/tuples-macos.txt" ] || STOP`; the per-SECTION green proof: `p=0; python3 "$EVID/witness.py" "$EVID/H/biv_tests-macos.xml" green > "$EVID/H/witness-green-macos.verdict" || p=$?; [ "$p" -eq 0 ] && [ -s "$EVID/H/witness-green-macos.verdict" ] || STOP`; the scout (e) and token scan (f) as in the countgate plan (statuses captured, `hits=0` REQUIRED).
- [ ] **Step 2: Linux at H — the four-phase container with the acceptance run REQUIRED** — exactly Task 2 Step 2's container (Phase H / R / T / S; `--init`; `nofile` raised; R-OBS-6 name-free proof) with the run head `H`: Phase T clones the branch from `/repo-ro` with the receipt `rev-parse HEAD == H`; Phase S: venv, `cmake --preset ci`, build, the five `-r xml` runs, and the workflow-equivalent `ctest --preset ci` run whose rc is REQUIRED 0 at H (its log copied out as `$EVID/H/ctest-linux-H.log`; a nonzero rc = FINDING routed UP with the log); XMLs + ledger copied out to `$EVID/H/`; `u=0; python3 "$EVID/tuples.py" linux <the five copied-out XMLs> > "$EVID/H/tuples-linux.txt" || u=$?; [ "$u" -eq 0 ] && [ -s "$EVID/H/tuples-linux.txt" ] || STOP`; `p=0; python3 "$EVID/witness.py" "$EVID/H/biv_tests-linux.xml" green > "$EVID/H/witness-green-linux.verdict" || p=$?; [ "$p" -eq 0 ] && [ -s "$EVID/H/witness-green-linux.verdict" ] || STOP`; the Linux `biv_tests` skip COUNT == B's Linux `skips` cell.
- [ ] **Step 3: the cells are UNMOVED by H (CG-R7: H is a pytest row, not a Catch2 census binary)** — `q=0; python3 "$EVID/gate.py" "$EVID/C-cells.txt" "$EVID/C/tuples-macos.txt" "$EVID/C/tuples-linux.txt" "$EVID/H/tuples-macos.txt" "$EVID/H/tuples-linux.txt" > "$EVID/H/gate-equality-H.txt" || q=$?; printf 'gate_H_rc=%s\n' "$q" > "$EVID/H/gate-H.rc"; [ "$q" -eq 0 ] && [ -s "$EVID/H/gate-equality-H.txt" ] || STOP` (the helper's positional contract — literal file, two "P" tuple files, two "C" tuple files — here reads literal(C), observed(C), observed(H); every line `equal=yes`; VALIDATED 2026-09-07 in bash AND zsh: B's cells with four identical synthetic tuple files → rc 0, ten lines; one altered `biv_tests linux successes` → rc 5 with one `equal=no`). ANY `no` = FINDING, STOP UP (H moved a cell — impossible by construction; a `no` means the H build or run differs from C's).
- [ ] **Step 4: the HOME real-binary demonstration at C+H (iso rev8; V-FT-7) — the landed instrument, VERBATIM, under the RESOLVED evidence home** — `mkdir -p "$EVID/H/rp"; m=0; (cd harness && BIVHARNESS_SCHEMA_ROOT="$PWD/../schemas" "${OBS_ENV[@]}" ../.venv-harness/bin/python3 "$EVID/rp_mutants.py" /Users/jack/Programming/bivpak-intg-r450-discover-parity/build/ci-macos/biv "$EVID/H/rp/rp-mutants") > "$EVID/H/rp/rp-mutants.log" 2>&1 || m=$?; printf 'rp_rc=%s\n' "$m" > "$EVID/H/rp/rp.rc"; [ "$m" -eq 0 ] && [ -s "$EVID/H/rp/rp-mutants.log" ] || STOP` (the binary path ABSOLUTE — the scenario changes cwd; the scratch under `$EVID`, resolved — the containment check refuses a symlinked ancestor; the script's own assertions hold `status=fail` and `tags == {locator}` for all four mutants and print the closing line once). THE PARITY EFFECT, READ FROM THE LOG: `g=0; k=$(grep -c -F 'ALL FOUR MUTANTS RED ON EXACTLY THEIR OWN LOCATOR' "$EVID/H/rp/rp-mutants.log") || g=$?; [ "$g" -le 1 ] && [ "$k" -eq 1 ] || STOP; g=0; k=$(grep -c -F "MUTANT HOME: status=fail leak_tags=['HOME']" "$EVID/H/rp/rp-mutants.log") || g=$?; [ "$g" -le 1 ] && [ "$k" -eq 1 ] || STOP; g=0; k=$(grep -c -E '^isolation-leak HOME: .*0d15ea5e-0002-4000-8000-0000000c1a0d' "$EVID/H/rp/rp-mutants.log") || g=$?; [ "$g" -le 1 ] && [ "$k" -ge 1 ] || STOP; g=0; k=$(grep -c -E '^isolation-leak HOME: .*0d15ea5e-0001-4000-8000-00000000c0de' "$EVID/H/rp/rp-mutants.log") || g=$?; [ "$g" -le 1 ] && [ "$k" -ge 1 ] || STOP` (the claude HOME canary `…0002…c1a0d` on a HOME line is the parity effect — ABSENT in the landed pre-parity evidence `intg-isolation/IMPL-pair-implementer-20260903-002131.md:135-137`, which shows the codex identity only under the same tag set; the must-be-YES MEASURED 2026-09-07 at the candidate's built `biv` under `/private/var/…`: rc 0, `MUTANT HOME: status=fail leak_tags=['HOME']`, `isolation-leak HOME: agents[claude-code].image_session_id=0d15ea5e-0002-4000-8000-0000000c1a0d`, `isolation-leak HOME: agents[codex].image_session_id=0d15ea5e-0001-4000-8000-00000000c0de`). Record the log's sha256.
- [ ] **Step 5: no-mutation proof** as Task 2 Step 4 (files `status-post-H-obs.txt`, `status-main-post-H.*`); the HEAD is still H: `[ "$(git rev-parse HEAD)" = "$H" ] || STOP`.

### Task 7 — fence proofs at C and at H, census of record at the BRANCH HEAD H, IMPL return (no push yet)

- [ ] **Step 1: the touched set (materialized)** — `C=$(cat "$EVID/C.txt")`; `r=0; git diff --numstat bbf297e36a38a1fab8c2675f945098a0633f9f8b "$C" > "$EVID/touched.numstat" || r=$?; [ "$r" -eq 0 ] && [ -s "$EVID/touched.numstat" ] || STOP`; the path column must be EXACTLY the three paths: `s=0; awk '{print $3}' "$EVID/touched.numstat" > "$EVID/touched.paths" || s=$?; [ "$s" -eq 0 ] || STOP; o=0; sort "$EVID/touched.paths" > "$EVID/touched.paths.sorted" || o=$?; [ "$o" -eq 0 ] || STOP; printf '.github/workflows/s2-harness.yml\nsrc/adapters/claude_code/claude_code.cpp\ntests/test_adapter_claude_collect.cpp\n' > "$EVID/touched.expected"; d=0; diff "$EVID/touched.expected" "$EVID/touched.paths.sorted" > "$EVID/touched.delta" || d=$?; [ "$d" -eq 0 ] || STOP` (the workflow row must read `2 2`). Codex byte-identical (V-CP-3): `h=0; git show "${C}:src/adapters/codex/codex.cpp" > "$EVID/codex-C.cpp" || h=$?; [ "$h" -eq 0 ] && [ -s "$EVID/codex-C.cpp" ] || STOP`; its sha256 == the codex line of `$EVID/base-hashes.txt`. No `harness/` path in `touched.paths` (V-CP-5 — implied by the exact three-path equality). The claude hunk range at C: `r=0; git diff -U0 bbf297e36a38a1fab8c2675f945098a0633f9f8b "$C" -- src/adapters/claude_code/claude_code.cpp > "$EVID/claude-C.diff" || r=$?; [ "$r" -eq 0 ] && [ -s "$EVID/claude-C.diff" ] || STOP; g=0; grep -E '^@@' "$EVID/claude-C.diff" > "$EVID/claude-C.hunks" || g=$?; [ "$g" -eq 0 ] && [ -s "$EVID/claude-C.hunks" ] || STOP; h=0; python3 "$EVID/hunks.py" "$EVID/claude-C.hunks" 570 596 > "$EVID/claude-C.hunks.verdict" || h=$?; [ "$h" -eq 0 ] || STOP` (V-CP-1). No collect byte (V-CP-4): `g=0; k=$(grep -c 'collect(' "$EVID/claude-C.diff") || g=$?; [ "$g" -le 1 ] || STOP; [ "$k" -eq 0 ] || STOP` (zero matches exits 1 = the EXPECTED state; 2+ = STOP). H's fence RE-ASSERTED from the commits (rev6): `H=$(cat "$EVID/H.txt"); r=0; git diff --numstat "$C" "$H" > "$EVID/c-to-h.numstat.final" || r=$?; [ "$r" -eq 0 ] || STOP; d=0; diff "$EVID/H.numstat.expected" "$EVID/c-to-h.numstat.final" > "$EVID/c-to-h.numstat.final.delta" || d=$?; [ "$d" -eq 0 ] || STOP` and the whole-branch touched set at H is EXACTLY the six paths: `r=0; git diff --numstat bbf297e36a38a1fab8c2675f945098a0633f9f8b "$H" > "$EVID/touched-H.numstat" || r=$?; [ "$r" -eq 0 ] || STOP; s=0; awk '{print $3}' "$EVID/touched-H.numstat" > "$EVID/touched-H.paths" || s=$?; [ "$s" -eq 0 ] || STOP; o=0; sort "$EVID/touched-H.paths" > "$EVID/touched-H.paths.sorted" || o=$?; [ "$o" -eq 0 ] || STOP; printf '.github/workflows/s2-harness.yml\nharness/bivharness/e3.py\nharness/selftest/stub_biv.py\nharness/selftest/test_store_isolation.py\nsrc/adapters/claude_code/claude_code.cpp\ntests/test_adapter_claude_collect.cpp\n' > "$EVID/touched-H.expected"; d=0; diff "$EVID/touched-H.expected" "$EVID/touched-H.paths.sorted" > "$EVID/touched-H.delta" || d=$?; [ "$d" -eq 0 ] || STOP`.
- [ ] **Step 2: the census of record at the branch head, BOTH arms (082012 Answer (1) alternation; expectations WRITTEN FIRST; every producer materialized — F4)** — expectations: `printf '%s\n' 'tests/test_adapter_codex_collect.cpp:383' 'tests/test_adapter_codex_collect.cpp:385' 'tests/test_cli.cpp:1188' > "$EVID/census-expected-tree.txt"` (the three `sk-complete` fixture-filename false positives of the first-push receipt — line numbers RE-VERIFIED at `bbf297e` 2026-09-06) and `printf '%s\n' 'tests/test_adapter_codex_collect.cpp' 'tests/test_cli.cpp' > "$EVID/census-expected-history.txt"`. THE BRANCH HEAD IS H (rev6): `H=$(cat "$EVID/H.txt"); e=0; git cat-file -e "${H}^{commit}" || e=$?; [ "$e" -eq 0 ] || STOP; [ "$(git rev-parse HEAD)" = "$H" ] || STOP` — both producers below take `"$H"` — the tree arm scans H's tree and the history arm walks H's reachable history, C included (rev7: rev6 spelled `"$C"` in both producers with a prose substitution — the implementer's F1 `155514`; the WRITTEN two-arm form is now EXECUTED at a scratch H, 2026-09-07, bash AND zsh: tree arm = exactly the three expected lines, history arm = exactly the two expected paths, both deltas empty, the raw tree lines carry H's sha; H's three harness files add no alternation match; the expectations are UNCHANGED). Tree arm: `r=0; git grep -n -E 'sk-[A-Za-z0-9]{8,}|-----BEGIN [A-Z ]*PRIVATE KEY|AKIA[0-9A-Z]{16}|ghp_[A-Za-z0-9]{20,}|xox[abprs]-' "$H" -- . > "$EVID/census-tree-raw.txt" || r=$?; [ "$r" -le 1 ] || STOP` (`git grep` exits 1 on zero matches — data; 2+ = STOP); the two stripping stages (rev7: the superseded one-sed template that stood here is removed — the exact form only): `s=0; sed -E 's/^[0-9a-f]{40}://' "$EVID/census-tree-raw.txt" > "$EVID/census-tree-stripped.txt" || s=$?; [ "$s" -eq 0 ] || STOP` then `s=0; sed -E 's/^([^:]+:[0-9]+):.*$/\1/' "$EVID/census-tree-stripped.txt" > "$EVID/census-tree.txt" || s=$?; [ "$s" -eq 0 ] || STOP` (paths + line numbers ONLY — no matched text is retained; NO value is printed or recorded at any step); `d=0; diff "$EVID/census-expected-tree.txt" "$EVID/census-tree.txt" > "$EVID/census-tree.delta" || d=$?; [ "$d" -eq 0 ] || STOP`. History arm: `r=0; git rev-list "$H" > "$EVID/rl.txt" || r=$?; [ "$r" -eq 0 ] && [ -s "$EVID/rl.txt" ] || STOP`; `x=0; xargs git grep -l -E 'sk-[A-Za-z0-9]{8,}|-----BEGIN [A-Z ]*PRIVATE KEY|AKIA[0-9A-Z]{16}|ghp_[A-Za-z0-9]{20,}|xox[abprs]-' < "$EVID/rl.txt" > "$EVID/census-history-raw.txt" || x=$?; [ "$x" -le 1 ] || STOP` (`/usr/bin/xargs` on macOS exits 0 when every batch matched and 1 when some batch had no match — both DATA, VALIDATED 2026-09-06 in bash AND zsh on a 3-commit range: matching alternation → 0, non-matching → 1; 2+ = STOP; `[ -s "$EVID/census-history-raw.txt" ] || STOP`); `s=0; sed -E 's/^[0-9a-f]{40}://' "$EVID/census-history-raw.txt" > "$EVID/census-history-paths.txt" || s=$?; [ "$s" -eq 0 ] || STOP; o=0; sort -u "$EVID/census-history-paths.txt" > "$EVID/census-history.txt" || o=$?; [ "$o" -eq 0 ] && [ -s "$EVID/census-history.txt" ] || STOP; d=0; diff "$EVID/census-expected-history.txt" "$EVID/census-history.txt" > "$EVID/census-history.delta" || d=$?; [ "$d" -eq 0 ] || STOP`. ANY new line or path (`d` 1) = STOP UP, never a judgement call; `d` 2+ = a diff error, STOP. (The whole two-arm form VALIDATED 2026-09-06 at the pair Planner's seat AT `bbf297e` — the must-be-YES case: tree arm = exactly the three expected lines; history arm = exactly the two expected paths; both deltas empty.)
- [ ] **Step 3: the IMPL return relay** (PHASE IMPL, report-only body, TO intg.pair-planner) carries: B, P (with `git cat-file -e "${P}^{commit}"` rc), C, the three-path numstat, the hunk-range verdicts, codex sha equality, the ten C tuples + ten P tuples (+ XML sha256 + run ids) and the old(B)/observed(P)/new(C) table, the two run-identity/observer blocks (names only), the discriminator predicates (Task 0 and Task 4), token-scan hits=0, gate-equality all `yes`, the RED parse verdict (ROW 1 + ROW 5 red, ROWS 2–4 green) and the GREEN parse verdict, the census deltas at H (both empty), `status-post-C-obs.txt` and `status-post-H-obs.txt` empty, the P/C DISCLOSURE runs' rc values with their failing-set deltas (all empty against `harness-selftest`), the Linux ledgers; AND H's record (rev6): H, `H^` == C, `c-to-h.numstat` == the three rows, the `e3.py` `-U0` hunk (`@@ -75 +75 @@`, two literal lines), `old=cd1f8bc8… new=4e105052…`, `fidelity-pre-H.rc` = 5 and `fidelity-H.txt` (five rows ok, rc 0), the 7/11 inventory, the codex anchor count 1, the walk deltas (both empty), the targeted pytest rc 0 (`11 passed`), the discriminator predicate AT H (PASS/PASS), `ctest-macos-H.rc` = 0 and the Linux ctest stage rc 0 at H, `gate-equality-H.txt` all `yes`, the two H `witness.py green` verdicts, the HOME demonstration (`rp.rc` = 0; the `MUTANT HOME` line; BOTH identity lines). NO push, NO PR yet — those are Task 8 after the owner reviews return through master.

### Task 8 — the vehicle (after the pair Planner's verification + m-2's fenced review of C + m-3's hunk review of C and byte review of H at the PR head return through master with no red): push the branch, open the PR

- [ ] **Step 1: pre-push gate (the first-push discipline, retargeted to ONE remote BRANCH ref)** — `H=$(cat "$EVID/H.txt")`; `[ "$(git rev-parse HEAD)" = "$H" ] || STOP` (the PR head is H; rev6); `[ "$(git rev-parse "${H}^")" = "$(cat "$EVID/C.txt")" ] || STOP`; `u=0; git remote get-url --push --all origin > "$EVID/push-url.txt" || u=$?; [ "$u" -eq 0 ] && [ -s "$EVID/push-url.txt" ] || STOP; a=0; n=$(awk 'END { print NR }' "$EVID/push-url.txt") || a=$?; [ "$a" -eq 0 ] && [ "$n" -eq 1 ] || STOP`; `l=0; git ls-remote --heads origin intg/r450-discover-parity > "$EVID/remote-branch-before.txt" || l=$?; [ "$l" -eq 0 ] && [ ! -s "$EVID/remote-branch-before.txt" ] || STOP` (the ref must not pre-exist; non-empty = STOP UP); `v=0; gh repo view --json visibility -q .visibility > "$EVID/visibility.txt" || v=$?; [ "$v" -eq 0 ] && [ "$(cat "$EVID/visibility.txt")" = PRIVATE ] || STOP`; `[ ! -x "$(git rev-parse --git-path hooks/pre-push)" ] || STOP`; the census (Task 7 Step 2) re-asserted at H (the same files, both deltas empty); shell recorded (`printf '%s %s\n' "$0" "${ZSH_VERSION:-${BASH_VERSION:-unknown}}" > "$EVID/shell.txt"`).
- [ ] **Step 2: dry-run, then the push — LITERAL names, no refspec variable** — `y=0; git push --dry-run --no-tags origin intg/r450-discover-parity > "$EVID/push-dry.txt" 2>&1 || y=$?; [ "$y" -eq 0 ] || STOP`; the output must name `[new branch]      intg/r450-discover-parity -> intg/r450-discover-parity` (`g=0; k=$(grep -c -F 'intg/r450-discover-parity -> intg/r450-discover-parity' "$EVID/push-dry.txt") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP`); then THE VERY NEXT COMMAND: `p=0; git push --no-tags origin intg/r450-discover-parity > "$EVID/push-stdout.txt" 2> "$EVID/push-stderr.txt" || p=$?; printf 'push_rc=%s\n' "$p" > "$EVID/push-rc.txt"`; outcome probe ALWAYS: `o=0; git ls-remote --heads origin intg/r450-discover-parity > "$EVID/remote-branch-after.txt" || o=$?; remote_after=$(cut -f1 "$EVID/remote-branch-after.txt")`; `if [ "$o" -ne 0 ]; then class=d; elif [ "$p" -eq 0 ] && [ "$remote_after" = "$H" ]; then class=a; elif [ "$p" -eq 0 ]; then class=e; elif [ "$remote_after" = "$H" ]; then class=c; elif [ -z "$remote_after" ]; then class=b; else class=e; fi; printf 'class=%s\n' "$class" > "$EVID/push-class.txt"`; ONE attempt per token, nothing retried in-lane; class ≠ a = STOP UP with the files.
- [ ] **Step 3: the PR** — `gh pr create --base main --head intg/r450-discover-parity --title "adapters(claude): discover returns every store found (env + default), codex parity; count-gate cells transcribed" --body-file "$EVID/pr-body.md" > "$EVID/pr.txt" 2>&1` (rc captured; REQUIRED 0; `[ -s "$EVID/pr.txt" ]`) where `pr-body.md` names: the design pins (m-2 fence rev2; iso rev8), the plan pin, B/P/C/H with `H^` = C, the three-path numstat of C and the three-file numstat of H (ONE PR, TWO COMMITS, TWO OWNERS — arm A of `041131`), the ten C tuples and the H equality, the owner-review relays (m-2 on C; m-3 on C's cells hunk and on H), and the sentence "This PR is the vehicle under R-4.51 clause (2); the evidence of record is the local suites, the Docker parity leg, the owner byte reviews, and the operator's condition-4 token — a red remote CI is cited nowhere. Merge is local under the operator's token; the landing push of main follows the merge under the R-4.52 landing rule as the merge packet's own step." No label, no reviewer request, no auto-merge, no `gh pr ready`/draft toggling, no comment. (The route authorizes the PR as the vehicle; if `gh pr create` asks anything interactive → abort, STOP UP.)
- [ ] **Step 4: SITREP UP** with the push class, the PR URL, and the receipt files. This plan ENDS here. The MERGE-GATE packet (`results/intg-r450-discover-parity-merge-gate.md`, four conditions) follows from the pair Planner; the local merge (`git merge --no-ff` of H — C and H together — into lane-local `main`, §8-style receipt) happens ONLY under the operator's condition-4 token; the LANDING PUSH of `main` (R-4.52 rule: ONE fast-forward push, pinned sha, census at `main`'s head both arms against written expectations, dry-run, one attempt, class, receipt) is the merge packet's own step in the first-push shape — not this token's.

---

## Acceptance criteria (each measured, none inferred)

1. At C: `touched.paths.sorted` == the three expected paths; the workflow row `2 2` with the four changed lines all `"successes": <int>,`; `claude_code.cpp` hunks within :570-596 (`hunks.py` rc 0); codex.cpp sha unchanged; no harness/CMake/fixture/docs byte IN C. At H: `c-to-h.numstat` == exactly `1 1 e3.py` / `9 5 stub_biv.py` / `2 2 test_store_isolation.py`; `touched-H.paths.sorted` == the six paths; the `e3.py` `-U0` diff = one hunk `@@ -75 +75 @@` whose two changed lines are 64-hex literal lines; `H^` == C.
2. RED of record CITED from `$EVID/prior/` with sha256s (`red-build.rc` 0; `witness-red.rc` nonzero; `witness-red-parse.rc` 0; verdict `red verdict ok`); GREEN proven by `witness.py green` rc 0 with a non-empty verdict file at SEVEN producing steps: the targeted macOS run at the resume bytes (Task 1 Step 5), the full-suite `biv_tests` XML at P/macOS and P/Linux (Task 2), C/macOS and C/Linux (Task 4), H/macOS and H/Linux (Task 6); the existing discover case unchanged and green.
3. B/P/C/H bound in order with recorded identities (B before implementation; P before its observation; C before its observation; H after C is bound and before the acceptance run); ten P tuples, ten C tuples and ten H tuples observed under CG-R2 + R-OBS; ENTRY fired (P's `biv_tests` successes ≠ B's on both targets; every other cell equal; skips equal; the macOS skip set equal to B's names; the Linux skip count equal to B's cell); `gate.py` rc 0 at C (literal(C) == observed(P) == observed(C)) AND at H (literal(C) == observed(C) == observed(H) — H moves no cell); the P→C tree delta = the two literals; the C→H tree delta = the three harness files and nothing outside `harness/`; no arithmetic in any evidence.
4. DISCLOSURE at P and at C, both targets: the workflow-equivalent ctest rc recorded; the failing-row set EXACTLY `harness-selftest` (four empty deltas: macOS P, Linux P, macOS C, Linux C); the tripwire cause line (`claude_adapter_file`) present in each log. ACCEPTANCE at H: the workflow-equivalent macOS ctest (`-E '^safety-hardening$'`) rc 0 under `"${OBS_ENV[@]}"`; the Linux parity leg's ctest rc 0; the R-OBS discriminator predicate PASS/PASS at B (cited from `prior/`) and at H (executed).
5. H's fence (iso rev8): `fidelity-pre-H.rc` = 5 (the B-state stub mis-models ROW 1 and ROW 5) then `fidelity-H.txt` rc 0 (five rows ok); `h-e3pin.out` = `old=cd1f8bc8… new=4e105052a17b7e0d99bfeca28ac45cac1f6ed3c5ba0e9ba9ec62a34e530a3a51`; the four `test_e3_asserts.py` anchors each count 1 in `claude_code.cpp` at C; the codex anchor literal count 1 in `e3.py` at H and codex.cpp's sha == the base line; `NAMED MUTANT` 7 and `^def test_` 11 at H; both walk deltas empty at C; the targeted `pytest selftest/test_store_isolation.py` rc 0 with `11 passed`; the HOME real-binary demonstration `rp.rc` = 0 with `ALL FOUR MUTANTS RED ON EXACTLY THEIR OWN LOCATOR`, `MUTANT HOME: status=fail leak_tags=['HOME']`, and BOTH identities (`0d15ea5e-0002-4000-8000-0000000c1a0d` claude, `0d15ea5e-0001-4000-8000-00000000c0de` codex) on `isolation-leak HOME:` lines.
6. Census of record at H both arms == the written expectations (both deltas empty).
7. Cut-point `origin/main..C^` = 0; `C^` = `bbf297e…`; `H^` = C; `origin/main..H` counts 2; the branch pushed with class a and the remote ref == H; the PR open against `main` with head H; at this plan's end `main` is NOT yet pushed (the landing push is the merge packet's step); no tag exists (local or remote); no release act.
8. m-2's fenced review of C (V-CP-1..6), m-3's hunk review of C's two workflow lines (CG-R7.5 a–f) and m-3's byte review of H at the PR head (V-FT-1..8) all return through master with no red before the merge bar.

## Out of scope (an act here is a STOP, not a judgement)

Dedupe/provenance semantics (S-CP-5 HELD); any collect byte; any codex byte; any harness/stub/witness byte IN C (S-CP-2 is m-3's, executed as H); in H, any byte outside the three files, any `e3.py` byte other than the one literal, any `scenario.py`/spec/oracle byte, any tightening of the stub's `normpath` idiom toward `lexically_normal()`; the harness `_session_rows` robustness defect (an error envelope from `biv` crashes the RP scenario — observed 2026-09-07 only under a symlinked scratch path; pre-existing; REPORTED to m-3 through the pair Planner, not fixed); any user-facing wording/warning/exit change (S-CP-3); any pack/open interaction beyond enumeration (S-CP-4); any workflow byte beyond the two (α) literals; `expected_skips`; CMake; fixtures under `tests/fixtures/`; the R-4.49 act; the merge, the landing push of `main` (the merge packet's step, not this token's); tags of any kind; release.

## Anti-half-fix guards

- The witness must have been RED first, fail-closed (Task 1 Step 3: build rc 0, test rc ≠ 0, `witness.py red` rc 0) — a green-only or unparsed witness is not a witness.
- ROW 5's discriminator (one store → pack succeeds with one session) must PASS in the same SECTION; a refusal without the passing control is not evidence of both-store discovery.
- The literals are written by the script from the XML; a hand-typed literal, or a literal equal to "old + 1" without an XML, is V-CG-2 red.
- B, P and C are bound at their steps and never rewritten (anti-retrospection); P and C both observed; equality proven by `gate.py`; P reachable by object id (no tag).
- No evidence-producing pipeline anywhere: every producer's status recorded, every input proven non-empty (or proven empty where empty is the claim).
- Every helper is written at Task 0 Step 0b and compiled before use; every helper INVOCATION captures its status — a helper's printed output is never the gate, its exit is.
- H's re-pin is legitimate ONLY with the recorded re-validation (`fidelity-pre-H.rc` = 5 then `fidelity-H.txt` rc 0; the four anchors and the codex anchor counted; the E3 model lines untouched; the walk deltas empty) — a re-pin alone is a tripwire DISARM, V-FT red.
- The HOME demonstration must show BOTH identities on `isolation-leak HOME:` lines with the tag set exactly `{HOME}`; a tag-set-only check cannot see the parity effect (the landed pre-parity evidence has the same tag set with ONE identity).
- The P-state and C-state suite reds are DISCLOSED with their failing set proven EXACTLY `harness-selftest` and the tripwire cause line present; a red disclosed without its failing set, or a green P/C suite, is a FINDING — never a pass.
- The acceptance suites at H are REQUIRED rc 0 on both targets; no run at P or C substitutes for them.

## Revision history

- **rev1** `3931edab6a4b6f39c1d7fc60d4c29bbd8954f7ddc261a6dee9b76081a19f9bee` — FILED 2026-09-06 (`intg-r450-discover-parity-plan-1`, `010428`); MUST-REVISE by the implementer `065859` (F1 RED fail-open via `|| true`; F2 ambient macOS suite before the R-OBS correction; F3 ungranted local tag; F4 producer-masking pipelines). DEAD.
- **rev2** `9b889d045f46054c59fbe4502ede80e5d450fd4c83aee76fa8d2de7c65bd006f` — FILED 2026-09-06 (`intg-r450-discover-parity-plan-2`, `154309`); MUST-REVISE by the implementer `161925` (F1 five helpers invoked before creation; F2 `cells.py`/`gate.py` statuses uncaptured and two wc-to-tr line-count pipelines; F3 acceptance 2 promised green parses no step produced). DEAD.
- **rev3** `f1f95ee31c7b68e06a7acb38cc66b1f194a561164422a08df415dd22467b4054` — FILED 2026-09-06 (`intg-r450-discover-parity-plan-3`, `163706`); APPROVED `165625`; token `intg-r450-discover-parity-impl` `173252` CONSUMED at the implementer's Task 0 Step 5 STOP `175211` (rc2=8: the worktree's harness configured onto Homebrew Python 3.14.6 without jsonschema/zstandard — no `.venv-harness` in the isolated worktree). DEAD as the executing revision; its content stands.
- **rev4** `6ebbfa421398e2901e01cf9e5343517ffce214ebe7048ee007ff814a4be75d8e` — FILED 2026-09-06 (`intg-r450-discover-parity-plan-4`, `181613`); MUST-REVISE by the implementer `183249` (F1 the two `rm -rf` and the version receipt fail-open; F2 the ignore proofs came after the first status gate and `build/` had none; F3 `find_spec` is discoverability, not import). DEAD.
- **rev5** `d9230c6e9383f62e5f946de62634d0f42bc085c7a5cd4095fe2a46819812538e` — FILED 2026-09-06 (`intg-r450-discover-parity-plan-5`, `192052`); APPROVED `192951`; token `intg-r450-discover-parity-impl-2` `194721` CONSUMED at the implementer's Task 1 Step 5 (iv) STOP `201740` (`harness-selftest` RED at the P-state tree on macOS: the E3 C1 whole-file drift tripwire on `claude_code.cpp`; cross-domain, routed UP `040217`; master `134909` released arm A). DEAD as the executing revision; its content stands (both cleanups status-captured with absence postconditions, the version receipt status-captured, both ignore proofs before the first status gate, the import proof an actual import).
- **rev6** `3a17a74f0279b688df6dd4dbf68896b6945d8c9893993f5af59b3fe696c62432` — FILED 2026-09-07 (`intg-r450-discover-parity-plan-6`, `145505`); MUST-REVISE by the implementer `155514` (F1 the Task 7 Step 2 census producers scanned C while the prose claimed H). DEAD.
- **rev7** `3d09542c3bc9bbb66dede9910eeb52cdd8bb817f08a6bd334cd1bbefc3163aee` — FILED 2026-09-07 (`intg-r450-discover-parity-plan-7`, `162715`); APPROVED `163759`; tokens 3–7 issued on it: 3–6 CONSUMED at Task 0 by the process layer (`175319` executor operand; `024328` / `054041` / `071938` pair-Planner token terms — master RULED `140952`: per-task runner, no token-only terms); token 7 completed Tasks 0–1 (P bound `54954281`) and was CONSUMED at Task 2 Step 1 `231512` on the skip-set comparison this revision repairs. DEAD as the executing revision; its content stands.
- **rev8** `8e45acd3a2609f5c44dc507e621ea88bd8a399f55c66c25388d7079944149e72` — FILED 2026-09-08 (`intg-r450-discover-parity-plan-8`, `234427`); MUST-REVISE by the implementer `001126` (F1–F5: the P-bound state written as prose beside the unchanged state-(i) commands — unreachable through the unconditional B gate, no receipt producer, the zero cut-point, the absent expected-status file, Steps 6–7 unrouted). DEAD.
- **rev9** `4d304232b322e4005518aa00bb688d725996ccecb36906e76ed34d06888f5e90` — FILED 2026-09-09 (`intg-r450-discover-parity-plan-9`, `013355`); APPROVED `014848`; tokens 8 and 9 issued on it: 8 CONSUMED at the Task-2 runner entry `025213` (implementer process — the scratch runner lacked +x; rc 126 before any plan command), 9 CONSUMED at Task 2 Step 4 `042759` (THIS plan's instrument on the wrong target — the whole shared main-checkout status; P observed complete and correct on both targets). Content: one materialized resume selector with a receipt every state-dependent command re-reads; state bodies, the cut-point expectation, and Task 1 Steps 6–7 routed by it; every identity/tree producer status-captured; the whole affected FLOW (Task 0 Step 2 → Step 3 → Step 3b → Task 1 Steps 6–7) executed from the artifact's bytes at the retained clean P worktree (state `ii`) and at a scratch pin clone (state `i`) in bash AND zsh.
- **rev10** — this artifact (`intg-r450-discover-parity-plan-10`): the main-checkout no-mutation proof narrowed to its target — the snapshot (Task 0 Step 0) and every comparison (Task 2 Step 4; Task 4 Step 3 and Task 5 Step 5 by reference) exclude the two surfaces other seats are authorized to write during a token (`.relays/`, `docs/sprints/`) via git's `:(exclude)` pathspec; validated from the written bytes in bash AND zsh on the real checkout and a scratch clone with the four mutations (three excluded → 0 lines; a product write → fires). Nothing else changed.
- **rev8 (content)** — `skipset.py` (membership + count) as the skip-set comparison form at Task 2 Step 1 and Task 4 Step 2; the P-bound resume introduced (made executable by rev9).
- **rev7 (content)** — both census producers take `"$H"`; the superseded one-sed template span removed from the same step; the written two-arm form executed at a scratch H in bash and zsh (deltas empty); nothing else moved.
- **rev6 (content)** (`intg-r450-discover-parity-plan-6`): master `134909` folded — H as its own Task 5 (iso rev8 write set, V-FT/S-FT, five new helpers, the harness WALK recorded and re-run), the acceptance gate of record at the PR head C+H (new Task 6: suites REQUIRED both targets, discriminator at H, cells UNMOVED by `gate.py`, the HOME real-binary demonstration with both identities), P/C suites as DISCLOSURE runs with the failing set proven, P → C → H binding recorded, RESUME from the candidate's verified two paths with the RED evidence cited from the `impl-2` home, the ROW 5 label, the `mv` form, the venv-interpreter derivation, the RESOLVED evidence home; every new form executed from the WRITTEN bytes in bash AND zsh (scratch copy of the candidate + the candidate's built binary); Task 5 rehearsed end-to-end from the extracted spans on a scratch shared clone in both shells.
- **rev4 (content)** — Task 0 Step 3b (the worktree's harness venv per CI's recipe into the ignored path, module proof, check-ignore proof), Step 4 into a fresh build dir with the CMakeCache interpreter proof, Step 2 resume checkpoint, Step 5 one-execution note; every new form executed from the WRITTEN bytes before filing.
- **rev3 (content)** — the three `161925` findings folded across the whole document (helpers materialized at Task 0 Step 0b; every helper status-captured; awk single-stage counts; five scheduled `witness.py green` proofs); helper bytes unchanged; every changed span executed from the WRITTEN bytes before filing.
