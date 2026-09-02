# E2 store-isolation repair (R-4.37 harness hermeticity) — implementation plan

> **For agentic workers:** REQUIRED SUB-SKILL: superpowers:executing-plans, task-by-task, steps as checkboxes.

**Goal:** Execute `m3-e2-store-isolation-20260901` rev2 at exact pin `290db9a4…` verbatim — every E2 scenario command (source `pack`, target `open`) runs under a hermetic five-locator overlay (`HOME`, `CODEX_HOME`, `CODEX_SQLITE_HOME`, `CLAUDE_CONFIG_DIR`, `TMPDIR`) that OVERWRITES the inherited values with scenario-owned scratch paths, witnessed by four legs / seven markers, with NO budget byte moved, harness files only, ONE commit on local main, m-3's landed-sha byte review as the acceptance gate.

**Architecture:** Environment, not fixtures. The scenario runner gains one overlay builder and one fail-closed runtime guard; staged fixture stores keep their exact semantics and simply become the values the overlay points at for a named agent. The witness legs live in the harness selftest against deterministic synthetic ambient POISON (four disjoint roots with unique canaries), with the selftest stub carrying a product-FAITHFUL discovery model (the pinned adapters' precedence transcribed line-for-line and ruled by m-3 before any token) so a leak names its locator. The real E2 suite green at unchanged budget bytes is the mandatory end-to-end green (iso·4).

**Tech stack:** Python 3 (`harness/bivharness/scenario.py`, `harness/selftest/*.py`, pytest), the harness venv (`.venv-harness`, `harness/requirements.lock`), the `harness-selftest` and `harness-e2` ctest targets (`harness/CMakeLists.txt:30-52`, untouched), the proven four-phase Linux parity instrument for the second platform.

**Sealed input (execution-not-amendment; where the text defers or is silent → STOP UP through master; m-3 owns the answer):** `pdc:master/domains/m-3-restore-cli/design/2026-09-01-e2-store-isolation-r437.md` @ sha256 `290db9a47b8624170a996cb30f2ac73493280db3baef631708131a8be0b0c8dc` at commit `62a261819ca66ed93be174ecef3c0ce10441f085` — re-verified at plan authoring: the pinned blob, the live file, and the pdc HEAD blob all hash EQUAL. ISO-R1..R4, V-ISO-1..4, the four legs / seven markers. Its authority chain: m-3.implementer approve `142647` at the exact pin; the Master Reviewer's approve with VP concurrence `155517`; the operator's scope ruling of record `r437-operator-scope-ruling/PLAN-operator-20260902-031727.md` ("approved both", 2026-09-02); master's fenced execution route `r437-pack-timeout-diagnosis/PLAN-master-planner-20260902-031728.md`.

**Baseline pre-verified at plan authoring (bivpak `main@42cc085`; harness, adapters, and `src/cli/main.cpp` byte-identical to `46df8f3`, the design's product pin — `git diff --quiet 46df8f3..HEAD -- harness src/adapters src/cli/main.cpp` rc 0):** the distinct adapter `getenv` literal census is exactly `{CLAUDE_CONFIG_DIR, CODEX_HOME, CODEX_SQLITE_HOME}` (`grep -rhoE 'getenv\("[A-Z_]+"\)' src/adapters | sort -u`); `HOME` enters once at `src/cli/main.cpp:93`; `TMPDIR` via `fs::temp_directory_path()` at `codex.cpp:1084`; codex appends `env.home / ".codex"` at `codex.cpp:1202` even with `CODEX_HOME` set; claude defaults `env.home / ".claude"` at `claude_code.cpp:585`; `scenario.py:140-142` builds every command env from `os.environ.copy()` + overrides; `_prepare_agent_profiles` (`:262-319`) sets `CLAUDE_CONFIG_DIR`/`CODEX_HOME` ONLY for its named agent; the two command sites are `:499` (pack, `source_env`) and `:544` (open, `_probe_open_env(target_env, standins)`); the budget bytes are `scenario.py:24 COMMAND_TIMEOUT_S = 30` and `e3.py:45 = 120`.

## Global constraints (every task implicitly includes these)

1. **Write set — harness files ONLY, exactly THREE paths** (ISO-R4): `harness/bivharness/scenario.py` (the overlay builder + the runtime guard + the merge into source/target env), `harness/selftest/stub_biv.py` (the discovery-echo instrument, selftest-only), `harness/selftest/test_store_isolation.py` (NEW — the four legs). NOTHING else: no `harness/CMakeLists.txt`, no `harness/scenarios/*.json` (fixture semantics untouched — V-ISO-4), no `harness/bivharness/e3.py` (E3 is outside ISO-R1's "every E2 scenario command"), no `src/` byte (V-ISO-3), no `.github/`, no `schemas/`.
2. **No budget or timeout byte** (ISO-R3 / V-ISO-1): `scenario.py:24 COMMAND_TIMEOUT_S = 30` and `e3.py:45 COMMAND_TIMEOUT_S = 120` byte-identical to base. Proof form (F3 of `035526` — a TEST may name the constants; a production budget edit may not hide): (i) `git diff --quiet <base>..HEAD -- harness/bivharness/e3.py` rc 0 (e3.py is outside the write set — the whole file byte-equal); (ii) `git show <base>:harness/bivharness/scenario.py | grep -n '^COMMAND_TIMEOUT_S = '` byte-equal to `grep -n '^COMMAND_TIMEOUT_S = ' harness/bivharness/scenario.py` (same line 24, same value — the new constants are placed BELOW it); (iii) `git diff <base>..HEAD -- harness/bivharness/scenario.py harness/selftest/stub_biv.py | grep -E '^[-+]' | grep -Ev '^(\+\+\+|---)' | grep -ci 'timeout'` → 0 (no changed line of the two PRODUCTION-side harness files carries the token; `test_store_isolation.py` is exempt from (iii) because iso·4's guard names the constants). The knife-edge is removed by isolation, never by calibration — any E2 red that survives isolation is a FINDING routed UP, never a budget edit.
3. **Overwrite, not overlay-if-absent** (ISO-R1): every command env carries ALL FIVE names with scenario-scratch values regardless of the inherited environment; a host where a name is unset gets the same overwrite as a host where it is set.
4. **Hermeticity is a runtime invariant, fail-closed** (V-ISO-2 made mechanical): before every `_run_json` call the runner asserts the five names are present and each value lies under the scenario's `work`; a violation marks the scenario INVALID (never a silent pass, never a repair).
5. **ONE commit on local main**, no branch, no merge commit; the index/path-scoped chain with status-snapshot equality (the countgate rev2 precedent — the shared tree carries inherited S4 state that is PRESERVED and DISCLOSED, never staged, cleaned, or discarded).
6. **Evidence grep-derived at the landed sha**; the seven `NAMED MUTANT:` markers counted by grep; the real E2 suite green on BOTH platforms at unchanged budgets.
7. **No push, no PR, no remote CI (unfunded, never cited), no publication, no release** — R-4.46 stays operator-gated; R-4.38's due point stands; the release hold is ABSOLUTE.
8. **STOP routing:** pair-implementer → pair-planner → master → m-3. The design's silences (below) are STOPs unless they are implementation latitude the design explicitly leaves; the two latitude choices this plan makes are stated as such for m-3's byte review and veto.

**Sequencing:** this act is independent of 2a (tranche 2 waits on the corrected rev12 approve header and the fresh token) and PRECEDES the countgate observations (the owner's ruling: they run only after this repair lands green with fresh E2 evidence). Under the operator's publication-path ruling (R-4.51) this landing stays lane-local on unpublished `main`; the first trunk push is master's later routed act after the count-gate repair.

---

### The two latitude choices (stated, not hidden — m-3 vetoes at the landed sha)

- **L1 — the discovery-echo instrument in the selftest stub (rev1: a product-FAITHFUL model, m-3-ruled before any token).** The selftests run the harness against `harness/selftest/stub_biv.py`, not the real `biv`; the design's iso·1 oracle is "the exact discovered/session result contains ONLY staged content — no canary identity". To make that oracle executable in the selftest, `stub_biv.py` gains a discovery echo: when `STUB_BIV_DISCOVERY_LOG` is set in its environment, `pack` and `open` run `_discover_model(os.environ)` — a transcription of the pinned adapters' discovery PRECEDENCE at `46df8f3` — and append one line `<verb> <LOCATOR> <absolute path>` per discovered file plus one line `<verb> TMPDIR <tempfile.gettempdir()>`. When the variable is unset (every existing selftest; the E2 suite, which never runs the stub) the stub's behaviour is byte-identical to today. The model, cell by cell, with the product line it transcribes:
  ```text
  claude  claude_code.cpp:573-582   CLAUDE_CONFIG_DIR set AND exists ⇒ the ONLY claude root is $CLAUDE_CONFIG_DIR/projects; HOME is NOT consulted
          claude_code.cpp:585-594   otherwise $HOME/.claude/projects, when $HOME/.claude exists
  codex   codex.cpp:1195-1199       CODEX_HOME set AND exists ⇒ a store set at $CODEX_HOME                       (tag CODEX_HOME)
          codex.cpp:1202-1206       $HOME/.codex APPENDED when it exists and is not lexically the CODEX_HOME root  (tag HOME)
          codex.cpp:1177-1190       each store set: <root>/sessions (+ <root>/archived_sessions when present); the files under them are the session identities
          codex.cpp:1158-1170       sqlite: CODEX_SQLITE_HOME set ⇒ that DIRECTORY (when it exists) is the sqlite_home locator of every codex store set
          codex.cpp:1226-1236       collect reads <locator>/state_5.sqlite when present, else <root>/state_5.sqlite ⇒ the model records that FILE's PATH
                                    (tag CODEX_SQLITE_HOME when reached through the variable, else the root's tag); NO content is echoed — the product publishes no database bytes
  tmp     codex.cpp:1084            fs::temp_directory_path() ⇒ tempfile.gettempdir(), which honours TMPDIR
  NOT modelled: codex.cpp:1160-1162, the config.toml `sqlite_home` fallback taken only when CODEX_SQLITE_HOME is UNSET — unreachable under the overlay
  (scratch) and under every mutant (poison): the variable is always SET. Stated for m-3, not silently omitted.
  ```
  Consequence stated for the design's HOME arm: with a claude agent named, `CLAUDE_CONFIG_DIR` always names an EXISTING directory (the staged store; for an unnamed agent the overlay's scratch, which `_hermetic_overlay` creates), so the `$HOME/.claude` canary is unreachable under ANY one-coordinate mutant — it needs `HOME` AND `CLAUDE_CONFIG_DIR` compromised together. The HOME mutant therefore REDs on the codex HOME-default canary (`$HOME/.codex`, appended by the product regardless of `CODEX_HOME`), and the faithful test asserts the claude HOME canary's ABSENCE under that mutant. The design's "the HOME-default canaries surface" is read as "those reachable at the pinned precedence".
  **Routing (F2 of `035526`):** the model above, its unmodelled cell, and the HOME-arm reading go UP to master for m-3's EXACT pre-token ruling that this synthetic model faithfully witnesses ISO-R2 (the SITREP filed with this revision carries them verbatim). The token waits on that ruling AND the implementer's exact-hash approve. NOT claimed: that iso·3's static getter census catches behavioural drift in the model — it does not (it checks getter NAMES); the model's fidelity rests on m-3's ruling now and m-3's byte review at the landed sha later. **Option B, framed for m-3 and NOT chosen here because it is not expressible inside the fences:** a real-product witness needs the built `biv` inside the selftest process (`harness-selftest` runs `python -m pytest selftest` with no binary; supplying one is a `harness/CMakeLists.txt` byte — a gate byte under ISO-R4), or a runner-side runtime invariant on the real E2 suite ("every discovered session id ∈ the staged ids, else INVALID"), which can witness only against REAL ambient stores — host-dependent, exactly what ISO-R2 excludes as the oracle. If m-3 prefers B, that is a design-level answer this plan STOPs on.
- **L2 — where the overlay lives.** The overlay is built ONCE per scenario in `run_scenario` (after `work` is created, before `_prepare_agent_profiles`) as `_hermetic_overlay(work)` → the five names → `<work>/hermetic/{home,codex-home,codex-sqlite,claude-config,tmp}` (each directory created empty); the profile env for a NAMED agent then overrides the corresponding empty scratch with the staged store (`{**overlay, **profile_env}` for source and for target separately), so the staged store IS the locator value and every unnamed locator points at an empty scratch directory. `_run_json`'s signature and `os.environ.copy()` base stay as they are (the overlay is complete, so the base cannot leak). The mutants of Task 1 act on the FINAL per-command environment — a `scenario._run_json` wrapper that removes exactly one locator from `env_overrides` AFTER the profile merge and `_probe_open_env` — so the inherited (poisoned) value survives for that one locator on pack AND open, the runtime guard (which runs on the un-mutated env) stays ACTIVE, and one coordinate moves per arm (F1 of `035526`: dropping a key from the overlay alone is re-covered by `scenario.py:290-291` / `:316-317` for a named agent).

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
- [ ] **Step 2: (iso·1) the positive oracle and the per-locator replacement witness** — ONE positive oracle, factored, and the SAME oracle executed under each one-coordinate mutation (F4 of `035526`):
  ```python
  LOG = "STUB_BIV_DISCOVERY_LOG"

  def _run_poisoned(tmp_path, monkeypatch, log):
      monkeypatch.setenv(LOG, str(log))
      spec = _basic_spec(tmp_path, id="iso", agents=["claude-code", "codex"])
      return run_scenario(spec, STUB, tmp_path / "scratch"), tmp_path / "scratch" / "iso"

  def _entries(log):  # one (verb, locator, path) per line
      return [tuple(line.split(" ", 2)) for line in log.read_text(encoding="utf-8").splitlines()]

  def _leak_tags(entries, poison_root):
      return {tag for _, tag, path in entries if Path(path).is_relative_to(poison_root)}

  def _assert_hermetic_discovery(entries, poison_root, work):
      """The positive oracle: no logged path lies under the poison root; every temp root lies under <work>/hermetic/tmp."""
      leaks = _leak_tags(entries, poison_root)
      assert not leaks, f"poison reachable through {sorted(leaks)}"
      tmp = [Path(p) for _, tag, p in entries if tag == "TMPDIR"]
      assert tmp and all(t.is_relative_to(work / "hermetic" / "tmp") for t in tmp), f"temp root outside scratch: {tmp}"

  def _restore_poison(monkeypatch, locator):
      """The mutant: exactly ONE locator is removed from the FINAL per-command overrides, so os.environ's poison survives for it."""
      original = scenario._run_json
      def mutated(biv, args, cwd, env_overrides=None):
          overrides = dict(env_overrides or {})
          overrides.pop(locator, None)
          return original(biv, args, cwd, overrides)
      monkeypatch.setattr(scenario, "_run_json", mutated)
  ```
  Positive test: under `poison` (Step 1) and `use_schema_root`, `_run_poisoned`; REQUIRE `result.status == Status.PASS` (the `bivharness.report.Status` member the existing `test_scenario.py` positive asserts); REQUIRE the log's paths include the staged claude transcript basename `aaaaaaaa-1111-4000-8000-000000000001.jsonl` under tag `CLAUDE_CONFIG_DIR` and the staged codex transcript `rollout-2026-07-11T01-00-00-019faaaa-bbbb-7ccc-8ddd-eeeeeeee0001.jsonl` under tag `CODEX_HOME` (the discovery is real, not vacuous); then `_assert_hermetic_discovery(entries, poison_root, work)` PASSES. Then FOUR mutant tests, each: `_restore_poison(monkeypatch, <LOCATOR>)`, `_run_poisoned`, `with pytest.raises(AssertionError): _assert_hermetic_discovery(...)` — the SAME oracle turns RED — and `_leak_tags(entries, poison_root) == {<LOCATOR>}` — RED on exactly its own canary:
  - `HOME` → leak tags `== {"HOME"}`: the `POISON-HOME-CODEX` transcript surfaces (the product appends `$HOME/.codex` regardless of `CODEX_HOME`); additionally REQUIRE `"POISON-HOME-CLAUDE"` is NOT in the log (faithful: claude returned from the staged `CLAUDE_CONFIG_DIR`, L1). `# NAMED MUTANT: HOME restored to the poison root ⇒ RED here (the HOME-default canaries surface).`
  - `CODEX_HOME` → `== {"CODEX_HOME"}` (`POISON-CODEX-HOME`). `# NAMED MUTANT: CODEX_HOME restored to poison ⇒ RED here.`
  - `CODEX_SQLITE_HOME` → `== {"CODEX_SQLITE_HOME"}` (the path `<poison>/codex-sqlite/state_5.sqlite` is recorded — identity by PATH, no content echoed). `# NAMED MUTANT: CODEX_SQLITE_HOME restored to poison ⇒ RED here (the sqlite canary is scanned).`
  - `CLAUDE_CONFIG_DIR` → `== {"CLAUDE_CONFIG_DIR"}` (`POISON-CLAUDE-CONFIG`). `# NAMED MUTANT: CLAUDE_CONFIG_DIR restored to poison ⇒ RED here.`
  Positive discovery of a staged id through an override is NEVER credited as proof of `HOME` redirection — the positive oracle asserts the ABSENCE of every poison path, and the HOME mutant proves the oracle sees the HOME-default canary when the cut is missing. The runtime guard is NOT no-op'd: it runs on the un-mutated env before `_run_json` and stays green, so the discovery oracle alone discriminates (one coordinate per arm).
- [ ] **Step 3: (iso·2) the TMPDIR witness** — the positive oracle's second clause (every `TMPDIR` line — the stub's `tempfile.gettempdir()` at each command, the model of `codex.cpp:1084`'s `fs::temp_directory_path()` — lies under `<work>/hermetic/tmp`) is asserted by the Step 2 positive test; the mutant: `_restore_poison(monkeypatch, "TMPDIR")` → the SAME oracle RED with `_leak_tags == {"TMPDIR"}` (the recorded temp root lies under `<poison>/tmp`). `# NAMED MUTANT: TMPDIR inherited (poisoned) instead of overlaid ⇒ RED here.`
- [ ] **Step 4: (iso·3) the source-aware static locator-census witness** — (a) `adapter_getenv_locators` = the set of `getenv("NAME")` literals over `Path(__file__).resolve().parents[2] / "src" / "adapters"` (`**/*.cpp`, regex `getenv\("([A-Z_]+)"\)`); REQUIRE `adapter_getenv_locators == set(scenario.HERMETIC_LOCATORS) - scenario.MANDATORY_PROCESS_LOCATORS` (GREEN at the pin: three = three); `# NAMED MUTANT: a store-locator getenv added to the adapters and absent from the harness set ⇒ RED at (a).` (b) for EVERY runnable spec in `harness/scenarios/*.json` (the `test_probe_isolation.test_every_scenario_open_injects_all_pins_and_sandboxes_path` capture idiom — monkeypatch `scenario._run_json` to record `env_overrides`), REQUIRE every recorded overlay (pack AND open) carries all five names and every value is under that scenario's `work`. The mandatory pair is never dropped from the overwrites to make the census balance.
- [ ] **Step 5: (iso·4) the no-calibration witness as a selftest guard** — REQUIRE `scenario.COMMAND_TIMEOUT_S == 30` and `e3.COMMAND_TIMEOUT_S == 120` (`from bivharness import e3`, the import precedent of `test_e3_asserts.py`) — a selftest that reds if a budget byte moves; the constants are named HERE by design, which is why constraint 2's fence is a byte-level proof over the two production-side files and not a token grep over the diff; `# NAMED MUTANT: a budget byte moved in this act's commit ⇒ RED here (V-ISO-1 vetoes it regardless).` The full real E2 suite green is Task 3's evidence.
- [ ] **Step 6: the runtime-guard witness (constraint 4)** — `scenario._assert_hermetic({...four of five...}, work)` returns a non-empty reason list; with all five under `work` returns `[]`; with all five present but one value OUTSIDE `work` returns a reason naming that locator; and a `run_scenario` whose `_hermetic_overlay` is monkeypatched to omit a name (the guard active, as it always is — no test disables it) yields an INVALID result naming the locator (fail closed at the runner, independent of the stub). This arm is the guard's witness, not one of the seven markers.
- [ ] **Step 7: marker count** — `grep -c 'NAMED MUTANT:' harness/selftest/test_store_isolation.py` = **7** (iso·1 four, iso·2 one, iso·3 one, iso·4 one) — the design's SEVEN, counted, not asserted.
- [ ] **Step 8: run, verify FAIL** — `python3 -m pytest selftest/test_store_isolation.py` from `harness/`: import failures on the missing `HERMETIC_LOCATORS`/`_hermetic_overlay`/`_assert_hermetic`; after Task 2's stub change but before the overlay, iso·1's positive arm fails (poison canaries surface).

### Task 2 — the overlay, the guard, and the discovery echo

**Files:** Modify `harness/bivharness/scenario.py`; modify `harness/selftest/stub_biv.py`.

- [ ] **Step 1: `scenario.py` — the constants and the builder** (module level, immediately BELOW `COMMAND_TIMEOUT_S`, which keeps its line number 24 and its bytes):
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
- [ ] **Step 3: `stub_biv.py` — the discovery echo (L1, the faithful model)** — `_echo_discovery(verb)` called at the top of `pack` and `open_image`: if `STUB_BIV_DISCOVERY_LOG` is unset → return immediately (behaviour byte-identical to today: no envelope member, no new output); else append, to that file, one line `f"{verb} {tag} {path}"` per row of `_discover_model(os.environ)` and one line `f"{verb} TMPDIR {tempfile.gettempdir()}"`:
  ```python
  def _discover_model(env):
      """Transcribes the pinned adapters' discovery precedence (bivpak 46df8f3; the L1 table). Returns (locator, path) rows."""
      rows = []
      home = Path(env["HOME"]) if env.get("HOME") else None
      # claude_code.cpp:573-594
      ccd = env.get("CLAUDE_CONFIG_DIR")
      if ccd and Path(ccd).exists():
          claude_roots = [("CLAUDE_CONFIG_DIR", Path(ccd))]
      elif home and (home / ".claude").exists():
          claude_roots = [("HOME", home / ".claude")]
      else:
          claude_roots = []
      for tag, root in claude_roots:
          rows += [(tag, p) for p in sorted((root / "projects").rglob("*.jsonl"))]
      # codex.cpp:1156-1207, plus collect :1226-1236 for the database file
      codex_roots = []
      env_root = None
      ch = env.get("CODEX_HOME")
      if ch and Path(ch).exists():
          env_root = Path(ch)
          codex_roots.append(("CODEX_HOME", env_root))
      if home and (home / ".codex").exists() and (
          env_root is None or os.path.normpath(home / ".codex") != os.path.normpath(env_root)
      ):
          codex_roots.append(("HOME", home / ".codex"))
      csh = env.get("CODEX_SQLITE_HOME")
      for tag, root in codex_roots:
          for sub in ("sessions", "archived_sessions"):
              if (root / sub).exists():
                  rows += [(tag, p) for p in sorted((root / sub).rglob("*.jsonl"))]
          if csh and Path(csh).exists() and (Path(csh) / "state_5.sqlite").exists():
              rows.append(("CODEX_SQLITE_HOME", Path(csh) / "state_5.sqlite"))
          elif (root / "state_5.sqlite").exists():
              rows.append((tag, root / "state_5.sqlite"))
      return rows
  ```
  NO file content is echoed (identity is the path; the product publishes no database bytes). The stub's envelope, exit codes, and archive bytes do not change. The one unmodelled cell (the config.toml `sqlite_home` fallback) is stated in L1 for m-3.
- [ ] **Step 4: run green** — `python3 -m pytest selftest` whole (the new file + every existing selftest; `test_scenario_env.py`'s two tests still pass unchanged — `_run_json` is untouched); marker grep = 7.

### Task 3 — evidence battery, THE ONE COMMIT on local main, the IMPL report

- [ ] **Step 0: the evidence home and the initial snapshot** — `EVID=$(mktemp -d "${TMPDIR:-/tmp}/isolation-evidence-XXXXXX")` OUTSIDE the repository; `git status --porcelain > "$EVID/status-initial.txt"` (inherited S4 state preserved and disclosed); REQUIRE an empty index (`git diff --cached --quiet` rc 0) and the three write-set paths initially unchanged.
- [ ] **Step 1: the fence transcript at the working tree (pre-commit) and again at the landed sha** (each command + rc retained):
  - write set: `git diff --name-only <base>..HEAD | sort` (post-commit) → exactly `harness/bivharness/scenario.py`, `harness/selftest/stub_biv.py`, `harness/selftest/test_store_isolation.py` (V-ISO-3/V-ISO-4: no `src/`, no `harness/scenarios/`, no CMake, no `e3.py`);
  - budgets (constraint 2's three proofs, F3): `git diff --quiet <base>..HEAD -- harness/bivharness/e3.py` rc 0; `git show <base>:harness/bivharness/scenario.py | grep -n '^COMMAND_TIMEOUT_S = '` byte-equal to the same grep at HEAD (`24:COMMAND_TIMEOUT_S = 30`); `git diff <base>..HEAD -- harness/bivharness/scenario.py harness/selftest/stub_biv.py | grep -E '^[-+]' | grep -Ev '^(\+\+\+|---)' | grep -ci 'timeout'` → 0 (V-ISO-1);
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
3. iso·1 green with all four restore-to-poison mutants discriminating — each mutant acts on the FINAL per-command env and turns the SAME factored positive oracle RED (`pytest.raises`) with a leak-tag set equal to exactly its own locator; iso·2 green with its mutant likewise; iso·3(a) census equality green at the pin; iso·4's selftest guard green; seven `NAMED MUTANT:` markers by grep.
4. `harness-selftest` and `harness-e2` green on macOS AND in the Linux container at UNCHANGED budget bytes (`COMMAND_TIMEOUT_S = 30`; e3 `120`); the formerly timing-out E2 rows complete on the diagnosis host.
5. No product byte, no fixture-spec byte, no CMake byte, no E3 byte, no `.github` byte.
6. The IMPL report carries the landed sha; m-3's byte review at that sha is the acceptance gate; no push.

## Out of scope (hard)

Budget calibration (30 vs 120 — its own routed act on fresh observations, ISO-R3); E3 (`e3.py`, `scenarios-e3`) environment handling; any product byte (the append-not-replace question at `codex.cpp:1202` is m-2's design-of-record row; R-4.49 is m-1's); fixture content or scenario specs; the countgate observations (sequenced AFTER this landing + m-3's acceptance); `harness/CMakeLists.txt`; push/PR/remote CI/publication/release.

## Identity, lineage, and gates

- Plan identity: dispatch `intg-isolation-plan` (NEW — no grafting onto `intg-substep2a-plan` or `intg-countgate-plan`, per the Master Reviewer's lineage rule (1)); `DESIGN_DOC_ID: m3-e2-store-isolation-20260901`; `DESIGN_LOCK_ID: m3-e2-store-isolation-20260901 @ sha256 290db9a47b8624170a996cb30f2ac73493280db3baef631708131a8be0b0c8dc`; `DESIGN_RECORD_KIND: design-doc`; this artifact `plans/PL-intg-isolation-20260902.md`.
- **The canonical v2.9 exact cross-repo design edge is ATTEMPTED FIRST (lineage rule (2)):** the plan relay declares `DESIGN_SOURCE_REPO: ../pdc`, `DESIGN_SOURCE_COMMIT: b706e745c1890ce43c117a756103c415b4d0c29a` (the pdc commit that filed m-3.implementer's approving DESIGN-REVIEW `142647` at the exact pin; the design blob at that commit hashes `290db9a4…`), `DESIGN_SOURCE_ROOT: master/relays`, `DESIGN_SOURCE_PATH: master/domains/m-3-restore-cli/design/2026-09-01-e2-store-isolation-r437.md`, `DESIGN_OWNER: m-3`, `DESIGN_SHA256: 290db9a4…`. The lint's edge verifies the blob bytes and the OWNER-PEER authority population (origin = the latest m-3.planner DESIGN carrying the doc id, `142445`; review = the latest peer DESIGN-REVIEW parented to it, `142647`, verdict approve). The Master Reviewer's later approval `155517` is a MASTER-tier gate outside the owner-peer model the lint encodes (its owner is `master`, not `m-3`) and is cited by path above rather than declared as the edge's population; the declared commit is stated on the relay's face for that reason. A `--relay-root` measurement on the filed revision decides: structural GREEN ⇒ no waiver needed, proceed to review; FIRED ⇒ the completed scan and exact fired set return UP for the operator's fresh decision (W-4 and W-5 cover neither this design nor this plan and are NOT widened).
- Review and token: the implementer's exact-hash PLAN-REVIEW at this artifact's digest AND m-3's pre-token ruling on the L1 model (routed UP via master with this revision's SITREP; carried back as an addressed relay — silence is a STOP, never a default) → (structural green standing) → the bare `DISPATCH IMPL` token in-lane with a structured `SCOPE_DIFF` (the three paths `-> in`, this plan's Global-1 as the row evidence) — lineage rule (3). If m-3 rules for option B, this plan STOPs and a revision consumes the answer.
- Landing: the sha UP with the evidence; m-3's byte review is the acceptance gate — lineage rule (4). Merge is not a step (the commit lands on local main directly under the token, as countgate); push/publication/release behind their own gates; the release hold is ABSOLUTE.


## Revision lineage

- **rev0** `46e47a0a0d47cac0d712c44bab65e91b54168256c2806fff4acf99d7d5d54e9a` (commit `e1b3e77`) — DEAD, superseded. Implementer `intg-isolation/PLAN-REVIEW-pair-implementer-20260902-035526.md` MUST-REVISE, four findings, each verified at this seat's own read before folding: **F1 (Critical)** the overlay-drop mutants for `CODEX_HOME`/`CLAUDE_CONFIG_DIR` were masked by the named-profile merge (`scenario.py:290-291`, `:316-317` re-cover them) → the mutants act on the FINAL per-command env via a `_run_json` wrapper (L2; Task 1 Step 2); **F2 (Critical)** L1's unconditional `$HOME/.claude` scan contradicted `claude_code.cpp:573-582` and the sqlite echo published bytes the product never reports → a precedence-faithful model with the product lines cited, path-not-content identity, the unmodelled cell stated, the HOME-arm reading stated, routed UP for m-3's pre-token ruling with option B framed (L1); **F3 (Important)** the `timeout` token grep was impossible beside iso·4's constant-naming guard → three byte-level proofs over the two production-side files (constraint 2; Task 3 Step 1); **F4 (Important)** the mutant tests asserted the leak instead of the oracle's failure → one factored positive oracle executed under each mutation with `pytest.raises` and an exact leak-tag set (Task 1 Steps 2-3; acceptance 3). Also: the sequencing line updated for 2a's actual state and R-4.51.
- **rev1** — this artifact.
