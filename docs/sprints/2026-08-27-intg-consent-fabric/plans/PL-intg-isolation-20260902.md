# E2 store-isolation repair (R-4.37 harness hermeticity) — implementation plan

> **For agentic workers:** REQUIRED SUB-SKILL: superpowers:executing-plans, task-by-task, steps as checkboxes.

**Goal:** Execute `m3-e2-store-isolation-20260901` rev5 at exact pin `637ef197…` verbatim — every E2 scenario command (source `pack`, target `open`) runs under a hermetic five-locator overlay (`HOME`, `CODEX_HOME`, `CODEX_SQLITE_HOME`, `CLAUDE_CONFIG_DIR`, `TMPDIR`) that OVERWRITES the inherited values with scenario-owned scratch paths, witnessed by four legs / seven markers at TWO grains for iso·1 (the selftest grain against a product-faithful stub model; the real-product grain: one E2 scenario against the BUILT `biv` under a poisoned inherited environment, its positive run made NON-VACUOUS by asserting the staged codex identity AND provenance from the image's manifest before the no-poison oracle is credited), with NO budget byte moved, harness files only, ONE commit on local main, m-3's landed-sha byte review as the acceptance gate.

**Architecture:** Environment, not fixtures. The scenario runner gains one overlay builder and one fail-closed runtime guard; staged fixture stores keep their exact semantics and simply become the values the overlay points at for a named agent. The witness legs live in the harness selftest against deterministic synthetic ambient POISON (four disjoint roots with unique canaries), with the selftest stub carrying a product-FAITHFUL discovery model (the pinned adapters' precedence transcribed line-for-line and ruled by m-3 before any token) so a leak names its locator. The real-product grain lives in the E2 suite itself: ONE new isolation-witness scenario spec (isolation STAGING under the design's V-ISO-4 reading) poisons the runner's INHERITED environment with the same deterministic roots and asserts no poison marker in the product-owned result evidence (identities and `warnings[]`); the four restore-to-poison mutants are DEMONSTRATED against the real binary at verification and recorded, never shipped. The real E2 suite green at unchanged budget bytes is the mandatory end-to-end green (iso·4).

**Tech stack:** Python 3 (`harness/bivharness/scenario.py`, `harness/selftest/*.py`, pytest), the harness venv (`.venv-harness`, `harness/requirements.lock`), the `harness-selftest` and `harness-e2` ctest targets (`harness/CMakeLists.txt:30-52`, untouched), the proven four-phase Linux parity instrument for the second platform.

**Sealed input (execution-not-amendment; where the text defers or is silent → STOP UP through master; m-3 owns the answer):** `pdc:master/domains/m-3-restore-cli/design/2026-09-01-e2-store-isolation-r437.md` **rev5** @ sha256 `637ef197aa9f2ebb8f9a34ab91558d52ae35a71691a8403290a87ad59a84bca6` at commit `a07d84cee5687efb05912567fa58387e61b93317` — re-verified at plan authoring: the pinned blob, the live file, and the blob at `1738583e` (the pdc commit filing the owner's approving review) all hash EQUAL; rev2 `290db9a4…`, rev3 `59d5ec91…`, and rev4 `5c81e86a…` are DEAD PINS in its lineage. ISO-R1..R4 with the rev3 V-ISO-4 reading, the four legs / seven markers, THE TWO GRAINS OF iso·1 (L1 selftest grain; RP real-product grain), the HOME-arm reading, and **the rev5 NON-VACUITY BINDING** (design lines 124-167; the binding (1)-(3) at :146-153): the RP scenario MUST (1) stage at least one COLLECTABLE codex rollout whose cwd is inside the packed source and whose emitted session provenance binds to the store root that receives the SQLite warning; (2) assert that exact staged codex identity AND its provenance (`store_root` = the staged codex store) BEFORE crediting the no-poison oracle; (3) on the one-coordinate `CODEX_SQLITE_HOME` mutant require the EXACT warning kind `CodexDbEnrichmentSkipped` with path EQUAL to the poisoned `state_5.sqlite`, then the SAME oracle red with ONLY that tag. Its authority chain: m-3.planner's pre-token ruling `151302`; Master Reviewer `155339` MUST-REVISE of rev4 (publication vacuity; exact rev2 commission) → m-3's rev5 `162105`; owner approve m-3.implementer `162639` at the exact pin; Master Reviewer APPROVE WITH VP CONCURRENCE `164129` at the exact pin; **the operator's commission amendment `r437-operator-scope-ruling/PLAN-operator-20260902-173858.md` (typed "amend") re-pinning the act in `CH-intg-consent-fabric` from exact rev2 to EXACT rev5 — the grant is exact; any further design revision returns to the operator before it reaches this lane**; master's carry `r437-pack-timeout-diagnosis/PLAN-master-planner-20260902-173859.md` (arms (a)+(b) of the corrected predicate `161810` MET; arm (c) — this revision, its measurement, the exact-hash approve — is this lane's); the operator's original scope ruling `PLAN-operator-20260902-031727.md` and master's route `031728`.

**Baseline pre-verified at plan authoring (bivpak `main@31fb0fe`; harness, adapters, `src/cli/main.cpp`, `src/core/report/envelope.cpp`, and `src/core/pack/pack.cpp` byte-identical to `46df8f3`, the design's product pin — `git diff --quiet 46df8f3..HEAD -- harness src/adapters src/cli/main.cpp src/core/report/envelope.cpp src/core/pack/pack.cpp` rc 0):** the RP oracle's product surfaces: `envelope.cpp:16-35` serializes each warning's `kind` and `path`; `pack.cpp:628-629` carries every adapter warning into the report through `adapter_warning` (`:334-341`, splitting `kind:path` at the first colon); `codex.cpp:1240-1246` emits `CodexDbEnrichmentSkipped:<database path>` when `thread_updates` (`:1077`) cannot read the copied database, and `:1394-1400` publishes that warning only when a session exists for the same store root (the staged codex transcript provides one); the open envelope's `result.sessions.agents[]` carries `store_root` and each row's `image_session_id`/`installed_session_id` (`envelope.cpp:321-333`); the pack envelope reports COUNTS only (`agent_sessions[].session_count`), no identities; codex packs only rollouts whose `cwd` lies in the source root (`codex.cpp:1278-1285`), claude likewise (`claude_code.cpp:666-669`) over `projects/*/*.jsonl`; every session id must satisfy `manifest::grammar::session_id_ok` (`agent_member.hpp:17`) or pack REFUSES (`pack.cpp:631-639`). Also: the distinct adapter `getenv` literal census is exactly `{CLAUDE_CONFIG_DIR, CODEX_HOME, CODEX_SQLITE_HOME}` (`grep -rhoE 'getenv\("[A-Z_]+"\)' src/adapters | sort -u`); `HOME` enters once at `src/cli/main.cpp:93`; `TMPDIR` via `fs::temp_directory_path()` at `codex.cpp:1084`; codex appends `env.home / ".codex"` at `codex.cpp:1202` even with `CODEX_HOME` set; claude defaults `env.home / ".claude"` at `claude_code.cpp:585`; `scenario.py:140-142` builds every command env from `os.environ.copy()` + overrides; `_prepare_agent_profiles` (`:262-319`) sets `CLAUDE_CONFIG_DIR`/`CODEX_HOME` ONLY for its named agent; the two command sites are `:499` (pack, `source_env`) and `:544` (open, `_probe_open_env(target_env, standins)`); the budget bytes are `scenario.py:24 COMMAND_TIMEOUT_S = 30` and `e3.py:45 = 120`.

## Global constraints (every task implicitly includes these)

1. **Write set — harness files ONLY, exactly FOUR paths** (ISO-R4 with the rev3 V-ISO-4 reading): `harness/bivharness/scenario.py` (the overlay builder + the runtime guard + the merge into source/target env + the shared poison builder + the inherited-env poisoning + the RP oracle), `harness/selftest/stub_biv.py` (the discovery-echo instrument, selftest-only), `harness/selftest/test_store_isolation.py` (NEW — the four legs at the selftest grain), `harness/scenarios/store-isolation-witness.json` (NEW — the ONE RP isolation-witness scenario; isolation STAGING: no EXISTING fixture's semantics change). NOTHING else: no `harness/CMakeLists.txt`, no edit to any existing `harness/scenarios/*.json`, no `harness/bivharness/e3.py` (E3 is outside ISO-R1's "every E2 scenario command"), no `src/` byte (V-ISO-3), no `.github/`, no `schemas/`. If executing this plan turns out to need ANY byte outside these four paths, that is a STOP back UP NAMING THE BYTE — never an inference either way (master `154650`).
2. **No budget or timeout byte** (ISO-R3 / V-ISO-1): `scenario.py:24 COMMAND_TIMEOUT_S = 30` and `e3.py:45 COMMAND_TIMEOUT_S = 120` byte-identical to base. Proof form (F3 of `035526` — a TEST may name the constants; a production budget edit may not hide): (i) `git diff --quiet <base>..HEAD -- harness/bivharness/e3.py` rc 0 (e3.py is outside the write set — the whole file byte-equal); (ii) `git show <base>:harness/bivharness/scenario.py | grep -n '^COMMAND_TIMEOUT_S = '` byte-equal to `grep -n '^COMMAND_TIMEOUT_S = ' harness/bivharness/scenario.py` (same line 24, same value — the new constants are placed BELOW it); (iii) `git diff <base>..HEAD -- harness/bivharness/scenario.py harness/selftest/stub_biv.py harness/scenarios/store-isolation-witness.json | grep -E '^[-+]' | grep -Ev '^(\+\+\+|---)' | grep -ci 'timeout'` → 0 (no changed line of the three PRODUCTION-side harness files carries the token; `test_store_isolation.py` is exempt from (iii) because iso·4's guard names the constants). The knife-edge is removed by isolation, never by calibration — any E2 red that survives isolation is a FINDING routed UP, never a budget edit.
3. **Overwrite, not overlay-if-absent** (ISO-R1): every command env carries ALL FIVE names with scenario-scratch values regardless of the inherited environment; a host where a name is unset gets the same overwrite as a host where it is set.
4. **Hermeticity is a runtime invariant, fail-closed** (V-ISO-2 made mechanical): before every `_run_json` call the runner asserts the five names are present and each value lies under the scenario's `work`; a violation marks the scenario INVALID (never a silent pass, never a repair).
5. **ONE commit on local main**, no branch, no merge commit; the index/path-scoped chain with status-snapshot equality (the countgate rev2 precedent — the shared tree carries inherited S4 state that is PRESERVED and DISCLOSED, never staged, cleaned, or discarded).
6. **Evidence grep-derived at the landed sha**; the seven `NAMED MUTANT:` markers counted by grep; the real E2 suite (now 18 specs — 17 at base + the RP witness) green on BOTH platforms at unchanged budgets; the four real-binary mutant DEMONSTRATIONS (Task 3 Step 2b) recorded in the IMPL report with their RED transcripts — never committed as tests, never left in the tree.
7. **No push, no PR, no remote CI (unfunded, never cited), no publication, no release** — R-4.46 stays operator-gated; R-4.38's due point stands; the release hold is ABSOLUTE.
8. **STOP routing:** pair-implementer → pair-planner → master → m-3. The design's silences are STOPs unless they are implementation latitude the design explicitly leaves; L1 is now RULED (the selftest grain), L2 stays a stated latitude for m-3's byte review and veto, and the RP grain's mechanics (L3 below) are stated as such.
9. **The RP grain is a runtime witness of the real product, never of the runner's environment** (rev5): the RP oracle reads ONLY product-owned evidence — the image's `manifest.json` (`agent_sessions[].provenance.store_root`, `.original_session_ids.primary`; written at `manifest.cpp:658-720`), the open envelope's `store_root`, `image_session_id`, `installed_session_id`, and BOTH envelopes' `warnings[]` `kind`/`path`; a stub echo or an env assertion is NOT the RP oracle. **Non-vacuity (rev5 binding):** the positive run is credited ONLY after `_rp_positive` finds the staged codex session (`019faaaa-…0001`) and the staged claude session (`aaaaaaaa-…0001`) each EXACTLY ONCE in `agent_sessions` with `provenance.store_root` equal to its staged SOURCE store (`<work>/profiles/source-codex`, `<work>/profiles/source-claude`) and `discovery_tier` `env` (`codex.cpp:405-406`, `claude_code.cpp:71-72`) — the codex one is the session whose provenance binds to the store root that receives the SQLite warning (`codex.cpp:1394-1400` publishes only for a matching root). The `CODEX_SQLITE_HOME` poison is a deterministic INVALID `state_5.sqlite`; on its mutant the demonstration REQUIRES exactly one `warnings[]` entry with kind EQUAL `CodexDbEnrichmentSkipped` and path EQUAL `<poison>/codex-sqlite/state_5.sqlite`, then leak tags == {`CODEX_SQLITE_HOME`}.

**Sequencing:** this act is independent of 2a (tranche 2 waits on the corrected rev12 approve header and the fresh token) and PRECEDES the countgate observations (the owner's ruling: they run only after this repair lands green with fresh E2 evidence). Under the operator's publication-path ruling (R-4.51) this landing stays lane-local on unpublished `main`; the first trunk push is master's later routed act after the count-gate repair.

---

### The latitude choices (stated, not hidden — m-3 vetoes at the landed sha); L1 is RULED, L3 is the RP grain's mechanics

- **L1 — the discovery-echo instrument in the selftest stub (RULED by m-3 `151302`, normative since rev3 and carried at rev5: the SELFTEST GRAIN — a product-FAITHFUL model; fidelity re-checked at m-3's landed-sha byte review).** The selftests run the harness against `harness/selftest/stub_biv.py`, not the real `biv`; the design's iso·1 oracle is "the exact discovered/session result contains ONLY staged content — no canary identity". To make that oracle executable in the selftest, `stub_biv.py` gains a discovery echo: when `STUB_BIV_DISCOVERY_LOG` is set in its environment, `pack` and `open` run `_discover_model(os.environ)` — a transcription of the pinned adapters' discovery PRECEDENCE at `46df8f3` — and append one line `<verb> <LOCATOR> <absolute path>` per discovered file plus one line `<verb> TMPDIR <tempfile.gettempdir()>`. When the variable is unset (every existing selftest; the E2 suite, which never runs the stub) the stub's behaviour is byte-identical to today. The model, cell by cell, with the product line it transcribes:
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
  **Ruled (`151302`, normative since rev3, carried at rev5):** the model is FAITHFUL at the pinned precedence (every cite re-read at the owner's seat; the adapter files zero-drift to head), the unmodelled config.toml fallback is correctly out of model, the HOME-arm reading is CONFIRMED as a reading of the design's text, and L1 is ACCEPTED as the selftest grain — the witness of the RUNNER's mechanics. A model cannot be the hermeticity ORACLE (this plan's rev1 withdrawal of the iso·3-catches-drift claim is what surfaced the second grain): iso·1 therefore runs at TWO grains, both required — L1 here, and the real-product grain below. My rev1 option B was framed as inexpressible because it conflated the real PRODUCT with the real AMBIENT STORES; over a POISONED inherited env the real-product witness is deterministic on every host and needs no gate byte, because `harness-e2` already consumes the built binary. Answered, and consumed below as L3.
- **L2 — where the overlay lives.** The overlay is built ONCE per scenario in `run_scenario` (after `work` is created, before `_prepare_agent_profiles`) as `_hermetic_overlay(work)` → the five names → `<work>/hermetic/{home,codex-home,codex-sqlite,claude-config,tmp}` (each directory created empty); the profile env for a NAMED agent then overrides the corresponding empty scratch with the staged store (`{**overlay, **profile_env}` for source and for target separately), so the staged store IS the locator value and every unnamed locator points at an empty scratch directory. `_run_json`'s signature and `os.environ.copy()` base stay as they are (the overlay is complete, so the base cannot leak). The mutants of Task 1 act on the FINAL per-command environment — a `scenario._run_json` wrapper that removes exactly one locator from `env_overrides` AFTER the profile merge and `_probe_open_env` — so the inherited (poisoned) value survives for that one locator on pack AND open, the runtime guard (which runs on the un-mutated env) stays ACTIVE, and one coordinate moves per arm (F1 of `035526`: dropping a key from the overlay alone is re-covered by `scenario.py:290-291` / `:316-317` for a named agent).
- **L3 — the RP grain's mechanics (the design says WHAT — one E2 scenario, the built `biv`, the poisoned inherited env, the product-owned oracle, the invalid sqlite, four recorded demonstrations; this plan says HOW).** (a) **One shared poison builder** `scenario._poison_roots(root, source)` creates the four disjoint poison roots (+ the tmp root) with VALID, workspace-scoped canary transcripts — the product packs only sessions whose `cwd` lies in the source root and whose id passes the grammar, so a canary that the product would silently skip could never leak; canary identities are deterministic hex UUIDs unique per root (`POISON_SESSION_IDS`, below). The selftest fixture and the RP scenario both call it — "the same deterministic synthetic poison roots". (b) **Spec flag** `"isolation_witness": true` on the ONE new spec: `run_scenario` builds the poison roots at `<scratch>/<id>.poison` (a sibling of `work`, so `work`'s rmtree/mkdir never touches them) and runs the scenario body inside `_inherited_environment(poison_env)` — a context manager that sets the five names in `os.environ` and restores them in `finally` — so `_run_json`'s untouched `os.environ.copy()` base IS the poisoned inherited environment and the overlay's completeness is the only thing protecting the product. The body is extracted verbatim into `_execute_scenario(spec, biv, scratch, result, poison_root)` so the `with` needs no re-indentation of 150 lines. (c) **The RP oracle** `_isolation_leaks(envelopes, poison_root)` runs after the step loop when the flag is set and appends FINDINGS (`isolation-leak <TAG>: <field>=<value>`) for every product-owned string that carries a poison identity or a path under the poison root: BOTH envelopes' `warnings[].kind`/`.path`; the open envelope's `agents[].store_root`, `sessions[].image_session_id`, `sessions[].installed_session_id`. A finding FAILs the scenario (never INVALID — the product ran; it leaked). TAG = the poison sub-root reached (`home`→HOME, `codex-home`→CODEX_HOME, `codex-sqlite`→CODEX_SQLITE_HOME, `claude-config`→CLAUDE_CONFIG_DIR) or the id's owner root. (d) **The four demonstrations** are executed at verification by a one-file driver run from `harness/` that imports the runner, wraps `scenario._run_json` exactly as the selftest's `_restore_poison` does (pop ONE locator from the FINAL overrides after the guard), runs the RP spec against the BUILT `biv`, and prints the result — one run per locator, each expected `FAIL` with exactly its own `isolation-leak <TAG>` finding; the driver lives in `$EVID`, its four transcripts go into the IMPL report, and nothing of it is committed. No knob in production harness code can weaken isolation (R-CLASS.3): the only way to restore poison is an in-process monkeypatch.

### Task 1 — the four failing witness legs (`harness/selftest/test_store_isolation.py`, NEW)

**Files:** Create `harness/selftest/test_store_isolation.py`. Modify `harness/selftest/stub_biv.py` (L1 only). Reuse `test_scenario.use_schema_root`, `test_specs.STUB`, and the `_basic_spec` idiom.

**Interfaces:** Consumes from Task 2: `scenario.HERMETIC_LOCATORS: tuple[str, ...]` = `("HOME", "CODEX_HOME", "CODEX_SQLITE_HOME", "CLAUDE_CONFIG_DIR", "TMPDIR")`, `scenario.MANDATORY_PROCESS_LOCATORS: frozenset` = `{"HOME", "TMPDIR"}`, `scenario._hermetic_overlay(work: Path) -> dict[str, str]`, `scenario._assert_hermetic(env: dict[str, str], work: Path) -> list[str]` (returns the invalid reasons, empty when hermetic).

- [ ] **Step 1: the poison fixture** — a pytest fixture `poison(tmp_path, monkeypatch)` that calls the SHARED builder and sets the INHERITED environment to its five values (`monkeypatch.setenv` each): `env = scenario._poison_roots(tmp_path / "poison", tmp_path / "scratch" / "iso" / "source")`; it yields `tmp_path / "poison"`. The builder (Task 2 Step 1b) lays down:
  ```text
  <poison>/home/.codex/sessions/2026/01/01/rollout-2026-01-01T00-00-00-0d15ea5e-0001-4000-8000-00000000c0de.jsonl   (HOME, codex)
  <poison>/home/.claude/projects/<_project_key(source)>/0d15ea5e-0002-4000-8000-0000000c1a0d.jsonl                   (HOME, claude)
  <poison>/codex-home/sessions/2026/01/01/rollout-2026-01-01T00-00-00-0d15ea5e-0003-4000-8000-000000c0de40.jsonl     (CODEX_HOME)
  <poison>/codex-sqlite/state_5.sqlite      content b"POISON-CODEX-SQLITE: not a database\n"  (deterministic INVALID sqlite)
  <poison>/claude-config/projects/<_project_key(source)>/0d15ea5e-0004-4000-8000-0000c1a0dec0.jsonl                  (CLAUDE_CONFIG_DIR)
  <poison>/tmp/                                                                                                      (TMPDIR poison root)
  HOME=<poison>/home  CODEX_HOME=<poison>/codex-home  CODEX_SQLITE_HOME=<poison>/codex-sqlite  CLAUDE_CONFIG_DIR=<poison>/claude-config  TMPDIR=<poison>/tmp
  ```
  Each transcript is a VALID product-shaped session (the same two-line shapes `_prepare_agent_profiles` seeds, with `cwd` = `source`) whose id is unique per root, so a leak names its locator and the real product would PACK it, not skip it. Poison is deterministic and host-independent.
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
  - `HOME` → leak tags `== {"HOME"}`: the `$HOME/.codex` canary `0d15ea5e-0001-…` surfaces (the product appends `$HOME/.codex` regardless of `CODEX_HOME`); additionally REQUIRE the claude HOME canary id `0d15ea5e-0002-…` is NOT in the log (faithful: claude returned from the staged `CLAUDE_CONFIG_DIR`, L1). `# NAMED MUTANT: HOME restored to the poison root ⇒ RED here (the HOME-default canaries surface).`
  - `CODEX_HOME` → `== {"CODEX_HOME"}` (the canary `0d15ea5e-0003-…`). `# NAMED MUTANT: CODEX_HOME restored to poison ⇒ RED here.`
  - `CODEX_SQLITE_HOME` → `== {"CODEX_SQLITE_HOME"}` (the path `<poison>/codex-sqlite/state_5.sqlite` is recorded — identity by PATH, no content echoed). `# NAMED MUTANT: CODEX_SQLITE_HOME restored to poison ⇒ RED here (the sqlite canary is scanned).`
  - `CLAUDE_CONFIG_DIR` → `== {"CLAUDE_CONFIG_DIR"}` (the canary `0d15ea5e-0004-…`). `# NAMED MUTANT: CLAUDE_CONFIG_DIR restored to poison ⇒ RED here.`
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
- [ ] **Step 1b: `scenario.py` — the shared poison builder, the identities, the inherited-env context manager, the RP oracle** (module level, below Step 1's definitions):
  ```python
  POISON_SESSION_IDS: dict[str, str] = {
      "HOME:codex": "0d15ea5e-0001-4000-8000-00000000c0de",
      "HOME:claude": "0d15ea5e-0002-4000-8000-0000000c1a0d",
      "CODEX_HOME": "0d15ea5e-0003-4000-8000-000000c0de40",
      "CLAUDE_CONFIG_DIR": "0d15ea5e-0004-4000-8000-0000c1a0dec0",
  }
  POISON_SUBROOTS: dict[str, str] = {"home": "HOME", "codex-home": "CODEX_HOME", "codex-sqlite": "CODEX_SQLITE_HOME",
                                     "claude-config": "CLAUDE_CONFIG_DIR", "tmp": "TMPDIR"}

  def _codex_rollout(sessions_root: Path, session_id: str, source: Path) -> None:
      path = sessions_root / "2026" / "01" / "01" / f"rollout-2026-01-01T00-00-00-{session_id}.jsonl"
      path.parent.mkdir(parents=True, exist_ok=True)
      path.write_text("\n".join((
          json.dumps({"timestamp": "2026-01-01T00:00:00Z", "type": "session_meta",
                      "payload": {"id": session_id, "session_id": session_id, "cwd": source.as_posix(), "cli_version": "0.142.5"}}),
          json.dumps({"timestamp": "2026-01-01T00:01:00Z", "type": "turn_context",
                      "payload": {"cwd": source.as_posix(), "workspace_roots": [source.as_posix()]}}),
      )) + "\n", encoding="utf-8")

  def _claude_transcript(projects_root: Path, session_id: str, source: Path) -> None:
      path = projects_root / _project_key(source) / f"{session_id}.jsonl"
      path.parent.mkdir(parents=True, exist_ok=True)
      path.write_text("\n".join((
          json.dumps({"type": "user", "cwd": source.as_posix(), "uuid": "0d15ea5e-aaaa-4111-8111-111111111111",
                      "parentUuid": None, "sessionId": session_id, "version": "2.1.202", "message": "poison one"}),
          json.dumps({"type": "assistant", "cwd": source.as_posix(), "uuid": "0d15ea5e-bbbb-4222-8222-222222222222",
                      "parentUuid": "0d15ea5e-aaaa-4111-8111-111111111111", "sessionId": session_id, "message": "poison two"}),
      )) + "\n", encoding="utf-8")

  def _poison_roots(root: Path, source: Path) -> dict[str, str]:
      """The deterministic synthetic ambient poison (ISO-R2): four disjoint roots + a tmp root; returns the five inherited values."""
      if root.exists():
          shutil.rmtree(root)
      home, codex_home, codex_sqlite, claude_config, tmp = (root / name for name in ("home", "codex-home", "codex-sqlite", "claude-config", "tmp"))
      _codex_rollout(home / ".codex" / "sessions", POISON_SESSION_IDS["HOME:codex"], source)
      _claude_transcript(home / ".claude" / "projects", POISON_SESSION_IDS["HOME:claude"], source)
      _codex_rollout(codex_home / "sessions", POISON_SESSION_IDS["CODEX_HOME"], source)
      codex_sqlite.mkdir(parents=True)
      (codex_sqlite / "state_5.sqlite").write_bytes(b"POISON-CODEX-SQLITE: not a database\n")
      _claude_transcript(claude_config / "projects", POISON_SESSION_IDS["CLAUDE_CONFIG_DIR"], source)
      tmp.mkdir(parents=True)
      return {"HOME": str(home), "CODEX_HOME": str(codex_home), "CODEX_SQLITE_HOME": str(codex_sqlite),
              "CLAUDE_CONFIG_DIR": str(claude_config), "TMPDIR": str(tmp)}

  @contextlib.contextmanager
  def _inherited_environment(values: dict[str, str]):
      """Poison the INHERITED environment for one scenario; _run_json's os.environ.copy() base sees it; restored on exit."""
      saved = {name: os.environ.get(name) for name in values}
      os.environ.update(values)
      try:
          yield
      finally:
          for name, previous in saved.items():
              if previous is None:
                  os.environ.pop(name, None)
              else:
                  os.environ[name] = previous

  def _poison_tag(value: str, poison_root: Path) -> str | None:
      for key, session_id in POISON_SESSION_IDS.items():
          if session_id in value:
              return key.split(":")[0]
      try:
          relative = Path(value).resolve().relative_to(poison_root.resolve())
      except (ValueError, OSError):
          return None
      return POISON_SUBROOTS.get(relative.parts[0]) if relative.parts else None

  def _isolation_leaks(envelopes: list[dict[str, Any]], poison_root: Path) -> list[str]:
      """The RP oracle (rev5): product-owned result evidence only — warnings[] kind/path on every envelope; store_root and session ids on open."""
      findings: list[str] = []
      def check(field: str, value: Any) -> None:
          if isinstance(value, str):
              tag = _poison_tag(value, poison_root)
              if tag:
                  findings.append(f"isolation-leak {tag}: {field}={value}")
      for envelope in envelopes:
          for index, warning in enumerate(envelope.get("warnings", []) or []):
              check(f"warnings[{index}].kind", warning.get("kind"))
              check(f"warnings[{index}].path", warning.get("path"))
          result_obj = envelope.get("result")
          agents = result_obj.get("sessions", {}).get("agents", []) if isinstance(result_obj, dict) else []
          for agent in agents:
              check(f"agents[{agent.get('agent')}].store_root", agent.get("store_root"))
              for row in agent.get("sessions", []):
                  check(f"agents[{agent.get('agent')}].image_session_id", row.get("image_session_id"))
                  check(f"agents[{agent.get('agent')}].installed_session_id", row.get("installed_session_id"))
      return findings

  RP_STAGED: dict[str, tuple[str, str]] = {   # agent -> (staged primary session id, staged SOURCE store dir under <work>/profiles)
      "codex": ("019faaaa-bbbb-7ccc-8ddd-eeeeeeee0001", "source-codex"),
      "claude-code": ("aaaaaaaa-1111-4000-8000-000000000001", "source-claude"),
  }

  def _rp_positive(manifest: dict[str, Any], work: Path) -> list[str]:
      """The rev5 non-vacuity binding: the staged identities AND their provenance, from the image's own manifest, before the no-poison oracle is credited."""
      findings: list[str] = []
      entries = manifest.get("agent_sessions", []) or []
      for agent, (primary, store_dir) in RP_STAGED.items():
          expected_root = (work / "profiles" / store_dir).resolve()
          matches = [entry for entry in entries
                     if entry.get("agent") == agent and entry.get("original_session_ids", {}).get("primary") == primary]
          if len(matches) != 1:
              findings.append(f"isolation-positive missing: {agent} staged session {primary} appears {len(matches)} times in agent_sessions (expected 1)")
              continue
          provenance = matches[0].get("provenance", {}) or {}
          root = provenance.get("store_root", "")
          try:
              same_root = Path(root).resolve() == expected_root
          except OSError:
              same_root = False
          if not same_root or provenance.get("discovery_tier") != "env":
              findings.append(f"isolation-positive missing: {agent} provenance store_root={root!r} discovery_tier={provenance.get('discovery_tier')!r}; expected {expected_root} tier 'env'")
      return findings
  ```
  `import contextlib` joins the module imports (`json`, `os`, `shutil`, `Path`, `Any` are already imported). `_project_key` (`:258`) is reused, not duplicated.
- [ ] **Step 1c: `run_scenario` — the extraction and the poisoned run** — the body from `work = scratch / spec["id"]` (`:470`) to the final `return result` moves VERBATIM into `def _execute_scenario(spec: dict[str, Any], biv: Path, scratch: Path, result: ScenarioResult, poison_root: Path | None) -> ScenarioResult:` (same indentation, no line edited except the two insertions below); `run_scenario` keeps its signature, the spec load, the xfail/probe/schema early returns and `pin_env()`, and ends:
  ```python
      if not spec.get("isolation_witness"):
          return _execute_scenario(spec, biv, scratch, result, None)
      poison_root = scratch / f"{spec['id']}.poison"
      poison_env = _poison_roots(poison_root, scratch / spec["id"] / "source")
      with _inherited_environment(poison_env):
          return _execute_scenario(spec, biv, scratch, result, poison_root)
  ```
  Inside `_execute_scenario`, immediately after the step loop and before `expect = spec.get("expect", {})`:
  ```python
      if poison_root is not None and not invalids:
          try:
              rp_manifest = json.loads(extract_member(image, "manifest.json"))
          except (FileNotFoundError, KeyError, json.JSONDecodeError, OSError, ValueError) as exc:
              findings.append(f"isolation-positive missing: manifest unreadable: {exc}")
          else:
              findings.extend(_rp_positive(rp_manifest, work))          # (2) identity + provenance FIRST
          findings.extend(_isolation_leaks([pack_envelope, run.envelope], poison_root))   # then the no-poison oracle
          exercised.add("K")
  ```
  (`run` is the last executed step's result — the open envelope for the witness spec; `pack_envelope` the pack's; `image` the packed archive; `extract_member` is already imported.) A PASS requires BOTH lists empty — the no-poison oracle is never credited on a vacuous run. The overlay/guard lines of Step 2 apply inside `_execute_scenario`.
- [ ] **Step 2: `run_scenario` — the merge (L2)** — after `work.mkdir(parents=True)` and before `_prepare_agent_profiles`: `overlay = _hermetic_overlay(work)`; after the profiles return: `source_env = {**overlay, **source_env}`; `target_env = {**overlay, **target_env}` (the staged store for a named agent overrides its empty scratch; every other locator stays scratch). Immediately before EACH `_run_json` call (`:499` pack with `source_env`; `:544` open with `_probe_open_env(target_env, standins)` — assert on the env actually passed): `reasons = _assert_hermetic(<env>, work); if reasons: invalids.extend(reasons); break`. No other line of the body moves (beyond Step 1c's verbatim extraction); `_run_json`, `_probe_open_env`, `_prepare_agent_profiles`, and every fixture path are untouched.
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
- [ ] **Step 3b: `harness/scenarios/store-isolation-witness.json` — the ONE RP scenario (NEW file; V-ISO-4 reading: isolation staging)**:
  ```json
  {
    "id": "store-isolation-witness",
    "tier": "E2",
    "classes": ["A", "B", "C", "E", "K"],
    "agents": ["claude-code", "codex"],
    "isolation_witness": true,
    "fixture": {"entries": [{"type": "file", "path": "work.txt", "text": "workspace\n"}]},
    "steps": [{"op": "pack"}, {"op": "open", "args": ["--consent", "yes"]}],
    "expect": {
      "tree": true,
      "manifest_variant": "builtin",
      "session_rows": [
        {"agent": "claude-code", "outcome": "installed", "image_session_id": "aaaaaaaa-1111-4000-8000-000000000001"},
        {"agent": "codex", "outcome": "installed", "image_session_id": "019faaaa-bbbb-7ccc-8ddd-eeeeeeee0001"}
      ]
    },
    "held": []
  }
  ```
  The `session_rows` pin the STAGED ids as the discovered ones (the positive is real, not vacuous); the RP oracle adds its findings on top. Under the stub (iso·3(b)'s capture over every spec) this spec runs to a FAIL on `session_rows` (the stub reports no sessions) — iso·3(b) reads only the captured env, so that is inert; `test_specs.py` names its specs explicitly and is not extended.
- [ ] **Step 4: run green** — `python3 -m pytest selftest` whole (the new file + every existing selftest; `test_scenario_env.py`'s two tests still pass unchanged — `_run_json` is untouched; `test_specs.py` unchanged); marker grep = 7. The RP spec's positive run needs the BUILT `biv` and is Task 3's evidence.

### Task 3 — evidence battery, THE ONE COMMIT on local main, the IMPL report

- [ ] **Step 0: the evidence home and the initial snapshot** — `EVID=$(mktemp -d "${TMPDIR:-/tmp}/isolation-evidence-XXXXXX")` OUTSIDE the repository; `git status --porcelain > "$EVID/status-initial.txt"` (inherited S4 state preserved and disclosed); REQUIRE an empty index (`git diff --cached --quiet` rc 0) and the three write-set paths initially unchanged.
- [ ] **Step 1: the fence transcript at the working tree (pre-commit) and again at the landed sha** (each command + rc retained):
  - write set: `git diff --name-only <base>..HEAD | sort` (post-commit) → exactly `harness/bivharness/scenario.py`, `harness/scenarios/store-isolation-witness.json`, `harness/selftest/stub_biv.py`, `harness/selftest/test_store_isolation.py` (V-ISO-3/V-ISO-4: no `src/`, no EXISTING scenario edited — `git diff --name-only <base>..HEAD -- harness/scenarios | grep -v store-isolation-witness.json` empty, no CMake, no `e3.py`); spec count `python3 -c 'from pathlib import Path; print(len(list(Path("harness/scenarios").rglob("*.json"))))'` → 18 (17 at base);
  - budgets (constraint 2's three proofs, ONE identical command string here and there): (i) `git diff --quiet <base>..HEAD -- harness/bivharness/e3.py` rc 0; (ii) `git show <base>:harness/bivharness/scenario.py | grep -n '^COMMAND_TIMEOUT_S = '` byte-equal to `grep -n '^COMMAND_TIMEOUT_S = ' harness/bivharness/scenario.py` (`24:COMMAND_TIMEOUT_S = 30`); (iii) `git diff <base>..HEAD -- harness/bivharness/scenario.py harness/selftest/stub_biv.py harness/scenarios/store-isolation-witness.json | grep -E '^[-+]' | grep -Ev '^(\+\+\+|---)' | grep -ci 'timeout'` → 0 (V-ISO-1; the selftest file exempt);
  - overwrite completeness: `grep -c 'HERMETIC_LOCATORS' harness/bivharness/scenario.py` ≥ 3 and the iso·3(b) selftest green over every runnable spec (ISO-R1 "every source and target command"); no isolation knob: `grep -c 'BIVHARNESS_ISOLATION\|MUTANT' harness/bivharness/scenario.py` → 0 (R-CLASS.3 — nothing in production harness code can restore poison);
  - markers: `grep -c 'NAMED MUTANT:' harness/selftest/test_store_isolation.py` → 7;
  - the adapter census at the landed sha: `grep -rhoE 'getenv\("[A-Z_]+"\)' src/adapters | sort -u` → exactly the three names (ISO-R1's future-adapter rule, green at this pin).
- [ ] **Step 2: macOS** — `cmake --preset ci-macos && cmake --build --preset ci-macos`; `ctest --preset ci-macos -R 'harness-selftest|harness-e2' --output-on-failure > "$EVID/ctest-macos.log"` → BOTH green, `store-isolation-witness` listed under `runnable_passed` (the RP positive against the real binary on this host); the E2 report (`build/ci-macos/harness-e2-report.json`, gitignored) copied to `$EVID` with per-scenario durations recorded — the R-4.37 knife-edge scenarios (`open-unknown-agent`, the three pack timeouts) now complete within the UNCHANGED 30 s budget on THIS host (the host whose real stores produced the diagnosis: 1,330 codex files + 9.2 MB sqlite, 2,210 claude files); if any E2 row still times out, that is a FINDING → STOP UP (no budget byte, ever).
- [ ] **Step 2b: the four real-binary mutant DEMONSTRATIONS (recorded, never shipped)** — write `$EVID/rp_mutants.py` (outside the repository) and run it from `harness/` with the venv python and the built binary; it wraps `scenario._run_json` exactly as the selftest's `_restore_poison` does and runs the RP spec once per locator:
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
      if locator == "CODEX_SQLITE_HOME":   # rev5 binding (3): the EXACT kind and the EXACT poisoned path, exactly once
          poison_db = out / f"mutant-{locator}" / "store-isolation-witness.poison" / "codex-sqlite" / "state_5.sqlite"
          kinds = [l for l in leaks if l.endswith("].kind=CodexDbEnrichmentSkipped")]
          paths = [l for l in leaks if l.endswith(f"].path={poison_db}")]
          assert len(kinds) == 1 and len(paths) == 1, (kinds, paths, result.detail)
          positive_missing = [l for l in result.detail.splitlines() if l.startswith("isolation-positive missing")]
          assert not positive_missing, positive_missing   # the staged codex session at its store root is what PUBLISHES the warning
  print("ALL FOUR MUTANTS RED ON EXACTLY THEIR OWN LOCATOR")
  ```
  Run: `BIVHARNESS_SCHEMA_ROOT=$PWD/../schemas ../.venv-harness/bin/python3 "$EVID/rp_mutants.py" ../build/ci-macos/biv "$EVID/rp-mutants" | tee "$EVID/rp-mutants.log"`. Expected per locator: `HOME` → the codex canary `0d15ea5e-0001-…` as an `image_session_id` (claude's HOME canary ABSENT — the faithful reading; the positive assertion still holds — both staged stores are discovered); `CODEX_HOME` → `0d15ea5e-0003-…` (the staged codex store is NOT discovered under this mutant, so an `isolation-positive missing` line accompanies the leak — expected); `CODEX_SQLITE_HOME` → EXACTLY ONE `warnings[].kind=CodexDbEnrichmentSkipped` and EXACTLY ONE `warnings[].path=<poison>/codex-sqlite/state_5.sqlite` (equality on the whole path), with NO `isolation-positive missing` line — the staged codex session collected from `source-codex` is what makes `codex.cpp:1394-1400` publish the warning (identities alone cannot see this coordinate — MUST-RP-1; publication is conditional — rev5); `CLAUDE_CONFIG_DIR` → `0d15ea5e-0004-…` (the staged claude store not discovered — a positive-missing line accompanies; and, on open, the target `store_root` under the poison root). Any mutant that stays PASS, or REDs on another tag, is a STOP UP (the product's discovery or the oracle disagrees with the design). The driver and its output are IMPL-report evidence; `git status --porcelain` must not show them (they live in `$EVID`).
- [ ] **Step 3: Linux** — the proven four-phase container instrument (the rev12 text at `git show 990ba3b:docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep1-20260827.md`, Task 5 Step 3 — Phase H host transport, Phase R frozen base incl. `openssh-client`, Phase T pinned uid 1001 + `/repo-ro` clone of local main at the landed sha with the rev-parse receipt, Phase S nofile raise + venv + configure/build + `--init`), measurement stage = `ctest -R 'harness-selftest|harness-e2'`; artifacts to `$EVID`; the rc ledger retained; registered rows (R-4.35 family) retained-not-cited.
- [ ] **Step 4: THE ONE COMMIT on local main** — `git add -- harness/bivharness/scenario.py harness/scenarios/store-isolation-witness.json harness/selftest/stub_biv.py harness/selftest/test_store_isolation.py`; proofs: `git diff --cached --name-only | sort` == the four paths; `git diff --name-only -- harness` empty after add; commit message: `fix(harness): E2 store isolation — five-locator hermetic overlay (HOME, CODEX_HOME, CODEX_SQLITE_HOME, CLAUDE_CONFIG_DIR, TMPDIR) overwritten on every scenario command, fail-closed runtime guard, four witness legs / seven markers at two grains (selftest stub model + one real-product isolation-witness E2 scenario under a poisoned inherited env); no budget byte (m3-e2-store-isolation-20260901 rev4 @ 5c81e86a; R-4.37 instrument repair)`; postconditions: `git status --porcelain` == `status-initial.txt` (byte-equal — the inherited state untouched); `git log -1 --format=%H` recorded as the LANDED SHA; `git diff --name-only HEAD~1..HEAD | sort` == the four paths.
- [ ] **Step 5: the IMPL report** (file-first, to the pair-planner; the landed sha UP with the evidence → master → m-3's byte review): partitioned per the sub-step-1 discipline (newly measured / carried / registered / green gates); the fence transcript; the seven markers by grep; both platforms' ctest logs and E2 reports with durations (the RP witness PASS on both); the four real-binary mutant demonstrations VERBATIM (`rp-mutants.log`); L2 and L3 named for m-3's veto (L1 ruled); explicit NOT-DONE (no calibration; no E3 change; no product byte; no push; no countgate observation — that act sequences after m-3's acceptance).

## Acceptance criteria (ALL must hold)

1. ONE commit on local main touching exactly the four harness paths (no existing scenario edited); inherited state byte-preserved (status-snapshot equality).
2. Every E2 scenario command env carries all five locators overwritten to scenario scratch (iso·3(b) green over every runnable spec; the runtime guard live and fail-closed).
3. iso·1 green with all four restore-to-poison mutants discriminating — each mutant acts on the FINAL per-command env and turns the SAME factored positive oracle RED (`pytest.raises`) with a leak-tag set equal to exactly its own locator; iso·2 green with its mutant likewise; iso·3(a) census equality green at the pin; iso·4's selftest guard green; seven `NAMED MUTANT:` markers by grep.
3b. The RP grain (rev5 binding): `store-isolation-witness` PASSes in the real E2 suite on BOTH platforms — `_rp_positive` finds the staged codex and claude sessions exactly once each with `provenance.store_root` = their staged source stores and tier `env` (the positive is non-vacuous), its `session_rows` pin the staged ids on open, and zero `isolation-leak` findings; the four real-binary demonstrations each FAIL it with exactly their own leak tag, the `CODEX_SQLITE_HOME` one with EXACTLY ONE `CodexDbEnrichmentSkipped` warning whose path EQUALS the poisoned `state_5.sqlite` and no positive-missing line — recorded verbatim in the IMPL report; no knob in production harness code.
4. `harness-selftest` and `harness-e2` (18 specs) green on macOS AND in the Linux container at UNCHANGED budget bytes (`COMMAND_TIMEOUT_S = 30`; e3 `120`); the formerly timing-out E2 rows complete on the diagnosis host.
5. No product byte, no EXISTING fixture-spec byte, no CMake byte, no E3 byte, no `.github` byte.
6. The IMPL report carries the landed sha; m-3's byte review at that sha is the acceptance gate; no push.

## Out of scope (hard)

Budget calibration (30 vs 120 — its own routed act on fresh observations, ISO-R3); E3 (`e3.py`, `scenarios-e3`) environment handling; any product byte (the append-not-replace question at `codex.cpp:1202` is m-2's design-of-record row; R-4.49 is m-1's); existing fixture content or existing scenario specs; the countgate observations (sequenced AFTER this landing + m-3's acceptance); `harness/CMakeLists.txt`; push/PR/remote CI/publication/release.

## Identity, lineage, and gates

- Plan identity: cycle directory `intg-isolation` (stable); this revision's PLAN handoff id is `intg-isolation-plan-4` — the FOURTH PLAN of the cycle; the three prior PLANs (`033604`, `144620`, `155917`) carried the bare `intg-isolation-plan`, which the kit's reissue rule says should have incremented (implementer `161514` F5) — corrected here, and the exact-hash review parents to `intg-isolation-plan-4` under its own unique id so the token → review → PLAN walk is unambiguous. No grafting onto `intg-substep2a-plan` or `intg-countgate-plan` (the Master Reviewer's lineage rule (1)); `DESIGN_DOC_ID: m3-e2-store-isolation-20260901`; `DESIGN_LOCK_ID: m3-e2-store-isolation-20260901 @ sha256 637ef197aa9f2ebb8f9a34ab91558d52ae35a71691a8403290a87ad59a84bca6` (rev5); `DESIGN_RECORD_KIND: design-doc`; this artifact `plans/PL-intg-isolation-20260902.md`.
- **The canonical v2.9 exact cross-repo design edge is ATTEMPTED FIRST (lineage rule (2)):** the plan relay declares `DESIGN_SOURCE_REPO: ../pdc`, `DESIGN_SOURCE_COMMIT: 1738583e8f6080b67da975e2e88c675abdbb72c7` (the pdc commit that filed m-3.implementer's approving DESIGN-REVIEW `162639` at the rev5 pin — derived at git (`git log -1 --format=%H -- master/relays/r437-pack-timeout-diagnosis/DESIGN-REVIEW-implementer-20260902-162639.md`), never hand-expanded; the design blob at that commit hashes `637ef197…`), `DESIGN_SOURCE_ROOT: master/relays`, `DESIGN_SOURCE_PATH: master/domains/m-3-restore-cli/design/2026-09-01-e2-store-isolation-r437.md`, `DESIGN_OWNER: m-3`, `DESIGN_SHA256: 637ef197…`. The lint's edge verifies the blob bytes and the OWNER-PEER authority population (origin = the latest m-3.planner DESIGN carrying the doc id, `162105` (rev5); review = the latest peer DESIGN-REVIEW parented to it, `162639`, verdict approve). The Master Reviewer's approval is a MASTER-tier gate outside the owner-peer model the lint encodes (its owner is `master`, not `m-3`): `164129` APPROVED rev5 at `637ef197` with VP concurrence (rev2's `155517` and rev4's `155339` must-revise are lineage). A `--relay-root` measurement on the filed revision decides, MEASURED BEFORE any waiver word (the edge was structurally green at rev0, rev1, and rev2; only the pin/commit fields change): structural GREEN ⇒ no waiver needed, proceed to review; FIRED ⇒ the completed scan and exact fired set return UP for the operator's fresh decision (W-4 and W-5 cover neither this design nor this plan and are NOT widened).
- Review and token — the corrected predicate (`161810`): (a) the successor pin owner-approved (`162639`) AND Master-Reviewer-approved with VP (`164129`) — MET; (b) the operator's commission amendment naming EXACT rev5 (`173858`) — MET, carried by `173859`; (c) THIS revision consuming the pin, root-mode measured BEFORE any waiver word, and the implementer's exact-hash PLAN-REVIEW at this artifact's digest parented to `intg-isolation-plan-4` under its own unique id → (structural green standing) → the bare `DISPATCH IMPL` token in-lane with a structured `SCOPE_DIFF` (the FOUR paths `-> in`, this plan's Global-1 as the row evidence) — lineage rule (3). Any further design revision returns to the OPERATOR before it reaches this lane (the grant is exact); a fired measurement returns UP to the operator with its scan — never a waiver asked in-lane.
- Landing: the sha UP with the evidence; m-3's byte review is the acceptance gate — lineage rule (4). Merge is not a step (the commit lands on local main directly under the token, as countgate); push/publication/release behind their own gates; the release hold is ABSOLUTE.


## Revision lineage

- **rev0** `46e47a0a0d47cac0d712c44bab65e91b54168256c2806fff4acf99d7d5d54e9a` (commit `e1b3e77`) — DEAD, superseded. Implementer `intg-isolation/PLAN-REVIEW-pair-implementer-20260902-035526.md` MUST-REVISE, four findings, each verified at this seat's own read before folding: **F1 (Critical)** the overlay-drop mutants for `CODEX_HOME`/`CLAUDE_CONFIG_DIR` were masked by the named-profile merge (`scenario.py:290-291`, `:316-317` re-cover them) → the mutants act on the FINAL per-command env via a `_run_json` wrapper (L2; Task 1 Step 2); **F2 (Critical)** L1's unconditional `$HOME/.claude` scan contradicted `claude_code.cpp:573-582` and the sqlite echo published bytes the product never reports → a precedence-faithful model with the product lines cited, path-not-content identity, the unmodelled cell stated, the HOME-arm reading stated, routed UP for m-3's pre-token ruling with option B framed (L1); **F3 (Important)** the `timeout` token grep was impossible beside iso·4's constant-naming guard → three byte-level proofs over the two production-side files (constraint 2; Task 3 Step 1); **F4 (Important)** the mutant tests asserted the leak instead of the oracle's failure → one factored positive oracle executed under each mutation with `pytest.raises` and an exact leak-tag set (Task 1 Steps 2-3; acceptance 3). Also: the sequencing line updated for 2a's actual state and R-4.51.
- **rev1** `c8bd21f05c59de5285618367872399220bbc9d0ed4343578db3ff7cb912c05ed` (commit `292a448`) — DEAD, superseded. Consumed design rev2; its L1 model went UP (`144956`) and came back RULED (m-3 `151302`): (A) faithful, accepted as the SELFTEST grain, HOME-arm reading confirmed — AND a required REAL-PRODUCT grain; the design moved to rev3 (`59d5ec91`, dead) then rev4 (`5c81e86a`, owner-approved `153855`) folding MUST-RP-1 (`152021`: an identity-only RP oracle cannot see `CODEX_SQLITE_HOME`; the poison becomes an INVALID `state_5.sqlite` surfacing as `CodexDbEnrichmentSkipped` in `warnings[]`). Master's carry `154650`. My rev1 option B ("inexpressible") was ANSWERED, not overruled: it conflated the real product with the real ambient stores — over a poisoned inherited env the real-product witness is deterministic and needs no gate byte because `harness-e2` already consumes the built binary.
- **rev2** `6133d6b2042300397dd9c5a81d344898057813b2a68bf1e178a6f2a0c2617d94` (commit `790e07e`) — DEAD, superseded. Consumed design rev4 (`5c81e86a` @ `e19e61fb`; edge commit `2e52fadf`); filed at 15:59 six minutes AFTER the Master Reviewer's `155339` MUST-REVISE of rev4 (VP withheld) had landed — my route-directory listing was nine minutes stale (owned; the filing gate now re-lists every upstream route directory immediately before submit). Implementer `161514` MUST-REVISE: F1/F2 the governance facts (rev4 rejected at the master tier; the operator's `031727` EXACT to dead rev2 — master `161810` corrected its own `154650` predicate to (a) successor pin owner+VP approved AND (b) an operator amendment to that exact pin AND (c) the plan revised/measured/approved under a fresh handoff id); F3 the oracle never asserted the staged identity's PROVENANCE; F4 the budget command named two files at one site and three at the other; F5 three PLANs reused the bare handoff id. rev2 introduced the RP grain added as L3 (one shared poison builder with VALID workspace-scoped canaries — the product packs only `cwd`-in-source sessions with grammar-valid ids; the `isolation_witness` spec flag; the inherited-env context manager with the body extracted verbatim into `_execute_scenario`; the RP oracle over warnings/store_root/session ids; the four real-binary demonstrations by an out-of-tree driver, recorded not shipped; no knob in production harness code); the write set grows to FOUR paths (the ONE new scenario spec — the design's V-ISO-4 reading); the selftest grain (L1) as filed at rev1, its poison fixture calling the shared builder.
- **rev3** — this artifact: consumes design rev5 (`637ef197` @ `a07d84c`; owner `162639`, Master Reviewer w/ VP `164129`; the operator's amendment `173858` re-pinning the commission to EXACT rev5; master's carry `173859`); the canonical edge re-pointed to `1738583e` (the commit filing `162639`, derived at git); F3 folded — `_rp_positive` asserts the staged codex and claude identities exactly once each with `provenance.store_root` = their staged source stores and tier `env` from the image's `manifest.json` BEFORE the no-poison oracle is credited (rev5 binding (1)-(2)), and the `CODEX_SQLITE_HOME` demonstration requires EXACTLY ONE `CodexDbEnrichmentSkipped` warning whose path EQUALS the poisoned `state_5.sqlite` with no positive-missing line (binding (3)); F4 folded — one identical three-file budget command string at both sites; F5 folded — filed as `intg-isolation-plan-4`; constraint 9 restated for rev5; nothing else moved.
