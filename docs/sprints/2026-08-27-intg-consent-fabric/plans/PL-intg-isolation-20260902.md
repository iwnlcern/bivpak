# E2 store-isolation repair (R-4.37 harness hermeticity) — implementation plan

> **For agentic workers:** REQUIRED SUB-SKILL: superpowers:executing-plans, task-by-task, steps as checkboxes.

**Goal:** Execute `m3-e2-store-isolation-20260901` rev2 at exact pin `290db9a4…` verbatim — every E2 scenario command (source `pack`, target `open`) runs under a hermetic five-locator overlay (`HOME`, `CODEX_HOME`, `CODEX_SQLITE_HOME`, `CLAUDE_CONFIG_DIR`, `TMPDIR`) that OVERWRITES the inherited values with scenario-owned scratch paths, witnessed by four legs / seven markers, with NO budget byte moved, harness files only, ONE commit on local main, m-3's landed-sha byte review as the acceptance gate.

**Architecture:** Environment, not fixtures. The scenario runner gains one overlay builder and one fail-closed runtime guard; staged fixture stores keep their exact semantics and simply become the values the overlay points at for a named agent. The witness legs live in the harness selftest against deterministic synthetic ambient POISON (four disjoint roots with unique canaries), with the selftest stub modelling the product's five discovery ingress paths so a leak names its locator. The real E2 suite green at unchanged budget bytes is the mandatory end-to-end green (iso·4).

**Tech stack:** Python 3 (`harness/bivharness/scenario.py`, `harness/selftest/*.py`, pytest), the harness venv (`.venv-harness`, `harness/requirements.lock`), the `harness-selftest` and `harness-e2` ctest targets (`harness/CMakeLists.txt:30-52`, untouched), the proven four-phase Linux parity instrument for the second platform.

**Sealed input (execution-not-amendment; where the text defers or is silent → STOP UP through master; m-3 owns the answer):** `pdc:master/domains/m-3-restore-cli/design/2026-09-01-e2-store-isolation-r437.md` @ sha256 `290db9a47b8624170a996cb30f2ac73493280db3baef631708131a8be0b0c8dc` at commit `62a261819ca66ed93be174ecef3c0ce10441f085` — re-verified at plan authoring: the pinned blob, the live file, and the pdc HEAD blob all hash EQUAL. ISO-R1..R4, V-ISO-1..4, the four legs / seven markers. Its authority chain: m-3.implementer approve `142647` at the exact pin; the Master Reviewer's approve with VP concurrence `155517`; the operator's scope ruling of record `r437-operator-scope-ruling/PLAN-operator-20260902-031727.md` ("approved both", 2026-09-02); master's fenced execution route `r437-pack-timeout-diagnosis/PLAN-master-planner-20260902-031728.md`.

**Baseline pre-verified at plan authoring (bivpak `main@42cc085`; harness, adapters, and `src/cli/main.cpp` byte-identical to `46df8f3`, the design's product pin — `git diff --quiet 46df8f3..HEAD -- harness src/adapters src/cli/main.cpp` rc 0):** the distinct adapter `getenv` literal census is exactly `{CLAUDE_CONFIG_DIR, CODEX_HOME, CODEX_SQLITE_HOME}` (`grep -rhoE 'getenv\("[A-Z_]+"\)' src/adapters | sort -u`); `HOME` enters once at `src/cli/main.cpp:93`; `TMPDIR` via `fs::temp_directory_path()` at `codex.cpp:1084`; codex appends `env.home / ".codex"` at `codex.cpp:1202` even with `CODEX_HOME` set; claude defaults `env.home / ".claude"` at `claude_code.cpp:585`; `scenario.py:140-142` builds every command env from `os.environ.copy()` + overrides; `_prepare_agent_profiles` (`:262-319`) sets `CLAUDE_CONFIG_DIR`/`CODEX_HOME` ONLY for its named agent; the two command sites are `:499` (pack, `source_env`) and `:544` (open, `_probe_open_env(target_env, standins)`); the budget bytes are `scenario.py:24 COMMAND_TIMEOUT_S = 30` and `e3.py:45 = 120`.

## Global constraints (every task implicitly includes these)

1. **Write set — harness files ONLY, exactly THREE paths** (ISO-R4): `harness/bivharness/scenario.py` (the overlay builder + the runtime guard + the merge into source/target env), `harness/selftest/stub_biv.py` (the discovery-echo instrument, selftest-only), `harness/selftest/test_store_isolation.py` (NEW — the four legs). NOTHING else: no `harness/CMakeLists.txt`, no `harness/scenarios/*.json` (fixture semantics untouched — V-ISO-4), no `harness/bivharness/e3.py` (E3 is outside ISO-R1's "every E2 scenario command"), no `src/` byte (V-ISO-3), no `.github/`, no `schemas/`.
2. **No budget or timeout byte** (ISO-R3 / V-ISO-1): `scenario.py:24 COMMAND_TIMEOUT_S = 30` and `e3.py:45` `120` byte-identical; the landing commit's diff contains no `TIMEOUT`/`timeout` token (`git diff <base>..HEAD -- harness | grep -ci 'timeout'` → 0). The knife-edge is removed by isolation, never by calibration — any E2 red that survives isolation is a FINDING routed UP, never a budget edit.
3. **Overwrite, not overlay-if-absent** (ISO-R1): every command env carries ALL FIVE names with scenario-scratch values regardless of the inherited environment; a host where a name is unset gets the same overwrite as a host where it is set.
4. **Hermeticity is a runtime invariant, fail-closed** (V-ISO-2 made mechanical): before every `_run_json` call the runner asserts the five names are present and each value lies under the scenario's `work`; a violation marks the scenario INVALID (never a silent pass, never a repair).
5. **ONE commit on local main**, no branch, no merge commit; the index/path-scoped chain with status-snapshot equality (the countgate rev2 precedent — the shared tree carries inherited S4 state that is PRESERVED and DISCLOSED, never staged, cleaned, or discarded).
6. **Evidence grep-derived at the landed sha**; the seven `NAMED MUTANT:` markers counted by grep; the real E2 suite green on BOTH platforms at unchanged budgets.
7. **No push, no PR, no remote CI (unfunded, never cited), no publication, no release** — R-4.46 stays operator-gated; R-4.38's due point stands; the release hold is ABSOLUTE.
8. **STOP routing:** pair-implementer → pair-planner → master → m-3. The design's silences (below) are STOPs unless they are implementation latitude the design explicitly leaves; the two latitude choices this plan makes are stated as such for m-3's byte review and veto.

**Sequencing:** this act is independent of 2a (tranche 2 waits on W-5's concurrence + the exact-hash approve) and PRECEDES the countgate observations (the owner's ruling: they run only after this repair lands green with fresh E2 evidence).

---

### The two latitude choices (stated, not hidden — m-3 vetoes at the landed sha)

- **L1 — the discovery-echo instrument in the selftest stub.** The selftests run the harness against `harness/selftest/stub_biv.py`, not the real `biv`; the design's iso·1 oracle is "the exact discovered/session result contains ONLY staged content — no canary identity". To make that oracle executable with the stub, `stub_biv.py` gains a discovery echo: when `STUB_BIV_DISCOVERY_LOG` is set in its environment, `pack` and `open` enumerate the FIVE product ingress paths as the product resolves them (`$HOME/.codex`, `$HOME/.claude`, `$CODEX_HOME`, `$CODEX_SQLITE_HOME/state_5.sqlite`, `$CLAUDE_CONFIG_DIR`) plus the temp root (`tempfile.gettempdir()`, which honours `TMPDIR`), and append every discovered file's basename and the temp root to that log file. When the variable is unset (every existing selftest, the E2 suite — which never runs the stub), the stub is byte-for-byte unchanged in behaviour: no envelope member, no new output. The real product's discovery is witnessed by iso·3 (the static census equality) and iso·4 (the real suite green), so a drift between the stub's model and the product is caught at the census, not laundered by the stub.
- **L2 — where the overlay lives.** The overlay is built ONCE per scenario in `run_scenario` (after `work` is created, before `_prepare_agent_profiles`) as `_hermetic_overlay(work)` → the five names → `<work>/hermetic/{home,codex-home,codex-sqlite,claude-config,tmp}` (each directory created empty); the profile env for a NAMED agent then overrides the corresponding empty scratch with the staged store (`{**overlay, **profile_env}` for source and for target separately), so the staged store IS the locator value and every unnamed locator points at an empty scratch directory. `_run_json`'s signature and `os.environ.copy()` base stay as they are (the overlay is complete, so the base cannot leak).

### Task 1 — the four failing witness legs (`harness/selftest/test_store_isolation.py`, NEW)

**Files:** Create `harness/selftest/test_store_isolation.py`. Modify `harness/selftest/stub_biv.py` (L1 only). Reuse `test_scenario.use_schema_root`, `test_specs.STUB`, and the `_basic_spec` idiom.

**Interfaces:** Consumes from Task 2: `scenario.HERMETIC_LOCATORS: tuple[str, ...]` = `("HOME", "CODEX_HOME", "CODEX_SQLITE_HOME", "CLAUDE_CONFIG_DIR", "TMPDIR")`, `scenario.MANDATORY_PROCESS_LOCATORS: frozenset` = `{"HOME", "TMPDIR"}`, `scenario._hermetic_overlay(work: Path) -> dict[str, str]`, `scenario._assert_hermetic(env: dict[str, str], work: Path) -> list[str]` (returns the invalid reasons, empty when hermetic).

- [ ] **Step 1: the poison fixture** — a pytest fixture `poison(tmp_path, monkeypatch)` that creates FOUR DISJOINT roots and sets the INHERITED environment to them via `monkeypatch.setenv` (all five names):
  ```text
  <tmp>/poison/home/.codex/sessions/2026/01/01/rollout-2026-01-01T00-00-00-POISON-HOME-CODEX.jsonl
  <tmp>/poison/home/.claude/projects/-poison/POISON-HOME-CLAUDE.jsonl
  <tmp>/poison/codex-home/sessions/2026/01/01/rollout-2026-01-01T00-00-00-POISON-CODEX-HOME.jsonl
  <tmp>/poison/codex-sqlite/state_5.sqlite            (content: b"POISON-CODEX-SQLITE")
  <tmp>/poison/claude-config/projects/-poison/POISON-CLAUDE-CONFIG.jsonl
  <tmp>/poison/tmp/                                    (TMPDIR poison root)
  HOME=<…>/poison/home  CODEX_HOME=<…>/poison/codex-home  CODEX_SQLITE_HOME=<…>/poison/codex-sqlite
  CLAUDE_CONFIG_DIR=<…>/poison/claude-config  TMPDIR=<…>/poison/tmp
  ```
  Each canary identity is unique per root, so a leak names its locator. Poison is deterministic and host-independent.
- [ ] **Step 2: (iso·1) the per-locator replacement witness** — with `poison` active and `STUB_BIV_DISCOVERY_LOG=<tmp>/discovery.log`, run `run_scenario(spec_with_agents(["claude-code", "codex"]), STUB, tmp_path / "scratch")` (STUB_BIV_MODE `ok`, schema root via `use_schema_root`); REQUIRE the scenario result is not invalid; read the log; REQUIRE it contains the two STAGED session ids (`aaaaaaaa-1111-…0001` and `019faaaa-…0001`, the ones `_prepare_agent_profiles` seeds) and contains NO substring `POISON-`. Then the FOUR independent restore-to-poison mutants, each a separate test that monkeypatches `scenario._hermetic_overlay` to return the overlay WITHOUT one name (so `os.environ.copy()`'s poison value survives for exactly that locator) and REQUIRES the matching canary surfaces in the log:
  - drop `HOME` → `POISON-HOME-CODEX` and `POISON-HOME-CLAUDE` present. `# NAMED MUTANT: HOME restored to the poison root ⇒ RED here (the HOME-default canaries surface).`
  - drop `CODEX_HOME` → `POISON-CODEX-HOME` present. `# NAMED MUTANT: CODEX_HOME restored to poison ⇒ RED here.`
  - drop `CODEX_SQLITE_HOME` → `POISON-CODEX-SQLITE` present. `# NAMED MUTANT: CODEX_SQLITE_HOME restored to poison ⇒ RED here (the sqlite canary is scanned).`
  - drop `CLAUDE_CONFIG_DIR` → `POISON-CLAUDE-CONFIG` present. `# NAMED MUTANT: CLAUDE_CONFIG_DIR restored to poison ⇒ RED here.`
  Positive discovery of a staged id through an override is NEVER credited as proof of `HOME` redirection — the HOME arm asserts the ABSENCE of the HOME-default canaries under a poisoned inherited HOME, and the mutant proves the oracle sees them when the cut is missing. (The runtime guard of constraint 4 would ALSO mark the mutated scenario invalid; the mutant tests therefore monkeypatch `scenario._assert_hermetic` to a no-op so the DISCOVERY oracle, not the guard, is what discriminates — one coordinate per arm.)
- [ ] **Step 3: (iso·2) the TMPDIR witness** — under `poison`, the discovery log's recorded temp root (the stub's `tempfile.gettempdir()` at the time of the codex pack, the model of `codex.cpp:1084`'s `fs::temp_directory_path()`) lies under `<work>/hermetic/tmp`; mutant: drop `TMPDIR` from the overlay (guard no-op'd as above) → the recorded temp root lies under `<…>/poison/tmp`. `# NAMED MUTANT: TMPDIR inherited (poisoned) instead of overlaid ⇒ RED here.`
- [ ] **Step 4: (iso·3) the source-aware static locator-census witness** — (a) `adapter_getenv_locators` = the set of `getenv("NAME")` literals over `Path(__file__).resolve().parents[2] / "src" / "adapters"` (`**/*.cpp`, regex `getenv\("([A-Z_]+)"\)`); REQUIRE `adapter_getenv_locators == set(scenario.HERMETIC_LOCATORS) - scenario.MANDATORY_PROCESS_LOCATORS` (GREEN at the pin: three = three); `# NAMED MUTANT: a store-locator getenv added to the adapters and absent from the harness set ⇒ RED at (a).` (b) for EVERY runnable spec in `harness/scenarios/*.json` (the `test_probe_isolation.test_every_scenario_open_injects_all_pins_and_sandboxes_path` capture idiom — monkeypatch `scenario._run_json` to record `env_overrides`), REQUIRE every recorded overlay (pack AND open) carries all five names and every value is under that scenario's `work`. The mandatory pair is never dropped from the overwrites to make the census balance.
- [ ] **Step 5: (iso·4) the no-calibration witness as a selftest guard** — REQUIRE `scenario.COMMAND_TIMEOUT_S == 30` and `e3.COMMAND_TIMEOUT_S`-equivalent (the `120` at `e3.py:45`, read by the name it carries there) unchanged — a selftest that reds if a budget byte moves; `# NAMED MUTANT: a budget byte moved in this act's commit ⇒ RED here (V-ISO-1 vetoes it regardless).` The full real E2 suite green is Task 3's evidence.
- [ ] **Step 6: the runtime-guard witness (constraint 4)** — `scenario._assert_hermetic({...four of five...}, work)` returns a non-empty reason list; with all five under `work` returns `[]`; with all five present but one value OUTSIDE `work` returns a reason naming that locator; and a `run_scenario` whose overlay is monkeypatched to omit a name (guard ACTIVE this time) yields an INVALID result naming the locator (fail closed at the runner, independent of the stub).
- [ ] **Step 7: marker count** — `grep -c 'NAMED MUTANT:' harness/selftest/test_store_isolation.py` = **7** (iso·1 four, iso·2 one, iso·3 one, iso·4 one) — the design's SEVEN, counted, not asserted.
- [ ] **Step 8: run, verify FAIL** — `python3 -m pytest selftest/test_store_isolation.py` from `harness/`: import failures on the missing `HERMETIC_LOCATORS`/`_hermetic_overlay`/`_assert_hermetic`; after Task 2's stub change but before the overlay, iso·1's positive arm fails (poison canaries surface).

### Task 2 — the overlay, the guard, and the discovery echo

**Files:** Modify `harness/bivharness/scenario.py`; modify `harness/selftest/stub_biv.py`.

- [ ] **Step 1: `scenario.py` — the constants and the builder** (module level, beside `COMMAND_TIMEOUT_S`, which is NOT touched):
  ```python
  HERMETIC_LOCATORS: tuple[str, ...] = ("HOME", "CODEX_HOME", "CODEX_SQLITE_HOME", "CLAUDE_CONFIG_DIR", "TMPDIR")
  MANDATORY_PROCESS_LOCATORS: frozenset[str] = frozenset({"HOME", "TMPDIR"})

  def _hermetic_overlay(work: Path) -> dict[str, str]:
      root = work / "hermetic"
      names = {"HOME": "home", "CODEX_HOME": "codex-home", "CODEX_SQLITE_HOME": "codex-sqlite",
               "CLAUDE_CONFIG_DIR": "claude-config", "TMPDIR": "tmp"}
      overlay: dict[str, str] = {}
      for locator in HERMETIC_LOCATORS:
          path = root / names[locator]
          path.mkdir(parents=True, exist_ok=True)
          overlay[locator] = str(path)
      return overlay

  def _assert_hermetic(env: dict[str, str], work: Path) -> list[str]:
      reasons: list[str] = []
      for locator in HERMETIC_LOCATORS:
          value = env.get(locator)
          if value is None:
              reasons.append(f"hermetic-env: {locator} absent from command environment")
              continue
          if not Path(value).resolve().is_relative_to(work.resolve()):
              reasons.append(f"hermetic-env: {locator} points outside scenario scratch: {value}")
      return reasons
  ```
- [ ] **Step 2: `run_scenario` — the merge (L2)** — after `work.mkdir(parents=True)` and before `_prepare_agent_profiles`: `overlay = _hermetic_overlay(work)`; after the profiles return: `source_env = {**overlay, **source_env}`; `target_env = {**overlay, **target_env}` (the staged store for a named agent overrides its empty scratch; every other locator stays scratch). Immediately before EACH `_run_json` call (`:499` pack with `source_env`; `:544` open with `_probe_open_env(target_env, standins)` — assert on the env actually passed): `reasons = _assert_hermetic(<env>, work); if reasons: invalids.extend(reasons); break`. No other line of `run_scenario` moves; `_run_json`, `_probe_open_env`, `_prepare_agent_profiles`, and every fixture path are untouched.
- [ ] **Step 3: `stub_biv.py` — the discovery echo (L1)** — a helper `_echo_discovery(verb)` called at the top of `pack` and `open_image`: if `STUB_BIV_DISCOVERY_LOG` is unset → return immediately (behaviour byte-identical to today); else enumerate, in this exact order, `Path(os.environ["HOME"]) / ".codex"`, `Path(os.environ["HOME"]) / ".claude"`, `Path(os.environ["CODEX_HOME"])`, `Path(os.environ["CODEX_SQLITE_HOME"]) / "state_5.sqlite"`, `Path(os.environ["CLAUDE_CONFIG_DIR"])` (each `KeyError` → the name recorded as `MISSING:<locator>`), appending one line per discovered regular file (`<verb> <locator> <basename>`) and one line `<verb> TMP <tempfile.gettempdir()>`; sqlite content is echoed as the file's first 32 bytes so the `POISON-CODEX-SQLITE` marker is visible. The stub's envelope, exit codes, and archive bytes do not change.
- [ ] **Step 4: run green** — `python3 -m pytest selftest` whole (the new file + every existing selftest; `test_scenario_env.py`'s two tests still pass unchanged — `_run_json` is untouched); marker grep = 7.

### Task 3 — evidence battery, THE ONE COMMIT on local main, the IMPL report

- [ ] **Step 0: the evidence home and the initial snapshot** — `EVID=$(mktemp -d "${TMPDIR:-/tmp}/isolation-evidence-XXXXXX")` OUTSIDE the repository; `git status --porcelain > "$EVID/status-initial.txt"` (inherited S4 state preserved and disclosed); REQUIRE an empty index (`git diff --cached --quiet` rc 0) and the three write-set paths initially unchanged.
- [ ] **Step 1: the fence transcript at the working tree (pre-commit) and again at the landed sha** (each command + rc retained):
  - write set: `git diff --name-only <base>..HEAD | sort` (post-commit) → exactly `harness/bivharness/scenario.py`, `harness/selftest/stub_biv.py`, `harness/selftest/test_store_isolation.py` (V-ISO-3/V-ISO-4: no `src/`, no `harness/scenarios/`, no CMake, no `e3.py`);
  - budgets: `git diff <base>..HEAD -- harness | grep -ci 'timeout'` → 0; `sed -n 24p harness/bivharness/scenario.py` = `COMMAND_TIMEOUT_S = 30`; `sed -n 45p harness/bivharness/e3.py` byte-equal to base (V-ISO-1);
  - overwrite completeness: `grep -c 'HERMETIC_LOCATORS' harness/bivharness/scenario.py` ≥ 3 and the iso·3(b) selftest green over every runnable spec (ISO-R1 "every source and target command");
  - markers: `grep -c 'NAMED MUTANT:' harness/selftest/test_store_isolation.py` → 7;
  - the adapter census at the landed sha: `grep -rhoE 'getenv\("[A-Z_]+"\)' src/adapters | sort -u` → exactly the three names (ISO-R1's future-adapter rule, green at this pin).
- [ ] **Step 2: macOS** — `cmake --preset ci-macos && cmake --build --preset ci-macos`; `ctest --preset ci-macos -R 'harness-selftest|harness-e2' --output-on-failure > "$EVID/ctest-macos.log"` → BOTH green; the E2 report (`build/ci-macos/harness-e2-report.json`, gitignored) copied to `$EVID` with per-scenario durations recorded — the R-4.37 knife-edge scenarios (`open-unknown-agent`, the three pack timeouts) now complete within the UNCHANGED 30 s budget on THIS host (the host whose real stores produced the diagnosis: 1,330 codex files + 9.2 MB sqlite, 2,210 claude files); if any E2 row still times out, that is a FINDING → STOP UP (no budget byte, ever).
- [ ] **Step 3: Linux** — the proven four-phase container instrument (the rev12 text at `git show 990ba3b:docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep1-20260827.md`, Task 5 Step 3 — Phase H host transport, Phase R frozen base incl. `openssh-client`, Phase T pinned uid 1001 + `/repo-ro` clone of local main at the landed sha with the rev-parse receipt, Phase S nofile raise + venv + configure/build + `--init`), measurement stage = `ctest -R 'harness-selftest|harness-e2'`; artifacts to `$EVID`; the rc ledger retained; registered rows (R-4.35 family) retained-not-cited.
- [ ] **Step 4: THE ONE COMMIT on local main** — `git add -- harness/bivharness/scenario.py harness/selftest/stub_biv.py harness/selftest/test_store_isolation.py`; proofs: `git diff --cached --name-only | sort` == the three paths; `git diff --name-only -- harness` empty after add; commit message: `fix(harness): E2 store isolation — five-locator hermetic overlay (HOME, CODEX_HOME, CODEX_SQLITE_HOME, CLAUDE_CONFIG_DIR, TMPDIR) overwritten on every scenario command, fail-closed runtime guard, four witness legs / seven markers against synthetic ambient poison; no budget byte (m3-e2-store-isolation-20260901 rev2 @ 290db9a4; R-4.37 instrument repair)`; postconditions: `git status --porcelain` == `status-initial.txt` (byte-equal — the inherited state untouched); `git log -1 --format=%H` recorded as the LANDED SHA; `git diff --name-only HEAD~1..HEAD | sort` == the three paths.
- [ ] **Step 5: the IMPL report** (file-first, to the pair-planner; the landed sha UP with the evidence → master → m-3's byte review): partitioned per the sub-step-1 discipline (newly measured / carried / registered / green gates); the fence transcript; the seven markers by grep; both platforms' ctest logs and E2 reports with durations; the two latitude choices (L1, L2) named for m-3's veto; explicit NOT-DONE (no calibration; no E3 change; no product byte; no push; no countgate observation — that act sequences after m-3's acceptance).

## Acceptance criteria (ALL must hold)

1. ONE commit on local main touching exactly the three harness paths; inherited state byte-preserved (status-snapshot equality).
2. Every E2 scenario command env carries all five locators overwritten to scenario scratch (iso·3(b) green over every runnable spec; the runtime guard live and fail-closed).
3. iso·1 green with all four restore-to-poison mutants discriminating (each live mutant test REDs the positive oracle on exactly its own canary); iso·2 green with its mutant; iso·3(a) census equality green at the pin; iso·4's selftest guard green; seven `NAMED MUTANT:` markers by grep.
4. `harness-selftest` and `harness-e2` green on macOS AND in the Linux container at UNCHANGED budget bytes (`COMMAND_TIMEOUT_S = 30`; e3 `120`); the formerly timing-out E2 rows complete on the diagnosis host.
5. No product byte, no fixture-spec byte, no CMake byte, no E3 byte, no `.github` byte.
6. The IMPL report carries the landed sha; m-3's byte review at that sha is the acceptance gate; no push.

## Out of scope (hard)

Budget calibration (30 vs 120 — its own routed act on fresh observations, ISO-R3); E3 (`e3.py`, `scenarios-e3`) environment handling; any product byte (the append-not-replace question at `codex.cpp:1202` is m-2's design-of-record row; R-4.49 is m-1's); fixture content or scenario specs; the countgate observations (sequenced AFTER this landing + m-3's acceptance); `harness/CMakeLists.txt`; push/PR/remote CI/publication/release.

## Identity, lineage, and gates

- Plan identity: dispatch `intg-isolation-plan` (NEW — no grafting onto `intg-substep2a-plan` or `intg-countgate-plan`, per the Master Reviewer's lineage rule (1)); `DESIGN_DOC_ID: m3-e2-store-isolation-20260901`; `DESIGN_LOCK_ID: m3-e2-store-isolation-20260901 @ sha256 290db9a47b8624170a996cb30f2ac73493280db3baef631708131a8be0b0c8dc`; `DESIGN_RECORD_KIND: design-doc`; this artifact `plans/PL-intg-isolation-20260902.md`.
- **The canonical v2.9 exact cross-repo design edge is ATTEMPTED FIRST (lineage rule (2)):** the plan relay declares `DESIGN_SOURCE_REPO: ../pdc`, `DESIGN_SOURCE_COMMIT: b706e745c1890ce43c117a756103c415b4d0c29a` (the pdc commit that filed m-3.implementer's approving DESIGN-REVIEW `142647` at the exact pin; the design blob at that commit hashes `290db9a4…`), `DESIGN_SOURCE_ROOT: master/relays`, `DESIGN_SOURCE_PATH: master/domains/m-3-restore-cli/design/2026-09-01-e2-store-isolation-r437.md`, `DESIGN_OWNER: m-3`, `DESIGN_SHA256: 290db9a4…`. The lint's edge verifies the blob bytes and the OWNER-PEER authority population (origin = the latest m-3.planner DESIGN carrying the doc id, `142445`; review = the latest peer DESIGN-REVIEW parented to it, `142647`, verdict approve). The Master Reviewer's later approval `155517` is a MASTER-tier gate outside the owner-peer model the lint encodes (its owner is `master`, not `m-3`) and is cited by path above rather than declared as the edge's population; the declared commit is stated on the relay's face for that reason. A `--relay-root` measurement on the filed revision decides: structural GREEN ⇒ no waiver needed, proceed to review; FIRED ⇒ the completed scan and exact fired set return UP for the operator's fresh decision (W-4 and W-5 cover neither this design nor this plan and are NOT widened).
- Review and token: the implementer's exact-hash PLAN-REVIEW at this artifact's digest → (structural green standing) → the bare `DISPATCH IMPL` token in-lane with a structured `SCOPE_DIFF` (the three paths `-> in`, this plan's Global-1 as the row evidence) — lineage rule (3).
- Landing: the sha UP with the evidence; m-3's byte review is the acceptance gate — lineage rule (4). Merge is not a step (the commit lands on local main directly under the token, as countgate); push/publication/release behind their own gates; the release hold is ABSOLUTE.
