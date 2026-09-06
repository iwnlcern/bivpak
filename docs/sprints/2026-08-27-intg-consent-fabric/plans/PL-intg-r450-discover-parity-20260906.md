# R-4.50 claude-discover parity — Implementation Plan (revision 1, DRAFT until the m-2 peer approve lands)

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:executing-plans to implement this plan task-by-task, IN DOCUMENT ORDER. Steps use checkbox (`- [ ]`) syntax for tracking. Nothing in this document is authority: implementation starts only on the pair Planner's addressed token after the exact-hash PLAN-REVIEW approve.

**Goal:** execute sealed c1 §7 in the claude adapter's `discover` body so an existing `CLAUDE_CONFIG_DIR` store no longer suppresses an existing `$HOME/.claude` default store (both are searched, env first), with codex's `discover` as the reference shape; witness it with rows 1–5 + the codex parity row; land as ONE commit on a branch cut at the PUBLISHED base, carried to `origin` as a PR (the vehicle, never the evidence).

**Architecture:** the discover body becomes the codex shape (optional `env_root`; append the env store iff its value exists; append the default iff it exists AND `lexically_normal()` differs) — no other product byte. One NEW named Catch2 `TEST_CASE` in `tests/test_adapter_claude_collect.cpp` carries rows 1–5 + parity as `SECTION`s (the fence owner's shape, N = 1 exactly). The census change (+1 `biv_tests` case on both targets) is transcribed into the two `successes` literals of `.github/workflows/s2-harness.yml` (`:85` macOS, `:326` Linux) in the SAME commit from the candidate's OWN observed `-r xml` runs under CG-R7 / T-1..T-5 — observed, never derived. Two owners review one commit: m-2's fenced byte review (V-CP-1..6) over the product + test bytes; m-3's hunk review (CG-R7.5) over the two workflow lines.

**Tech stack:** C++20 (`std::filesystem`), Catch2 v3 (`TEST_CASE`/`SECTION`, `-r xml`), CMake presets `ci-macos` (host) and `ci` (Linux parity container: ubuntu-24.04 `linux/amd64` `--init`, `nofile` soft == hard), git worktrees, `gh` 2.97.

**Spec (the law of this act, cited never retyped):** m-2 fence rev2 `pdc:master/relays/r437-pack-timeout-diagnosis/DESIGN-m2-planner-20260903-144700.md` @ sha256 `f2216ee606a03b0b5b0b7f4562fed52a7349219c28990e6ee3e89b0cc25e8c6f` (pdc `dfb5b409`; Master Reviewer approve `151001`; design origin `intg-r450-discover-parity-act/DESIGN-m2-planner-20260906-002200.md` for `DESIGN_DOC_ID m2-r450-discover-fence-rev2-20260903`; peer approve PENDING — this plan files for review only after it lands and the edge re-measures GREEN root-mode). Operator grant `r437-operator-scope-ruling/PLAN-operator-20260903-152117.md`. Master's route `intg-r450-discover-parity-act/PLAN-master-planner-20260905-212735.md` and composed ruling `PLAN-master-planner-20260906-004023.md`. m-3's Q2 ruling `DESIGN-planner-20260906-002436.md` (T-1..T-5) and the count-gate design `master/domains/m-3-restore-cli/design/2026-08-30-count-gate-repair-r438-rev1.md` (rev2 LIVE @ `70600364…`, CG-R7.1–7.6 + V-CG-6; rev1 `0099d1cf` stays the landed repair's pin). Sealed c1 §7 in `master/domains/m-2-agent-adapters/design/2026-07-02-adapter-contract-and-session-semantics.md` @ `e4c19914…`.

## Global constraints (each line binds every task)

- DETERMINING TEXT (c1 §7): "Discovery returns ALL stores found (a set): env-set does not suppress the default if both exist and differ — both are searched."
- REFERENCE SHAPE: `src/adapters/codex/codex.cpp:1193-1206` for DISCOVER ONLY — append; `lexically_normal()` guard; env then defaults. Its trailing-slash property (`"/x/.claude/"` ≠ `"/x/.claude"` under `lexically_normal()`, probed 2026-09-05) is INHERITED by parity; any "tightening" is a V-CP-2 divergence (m-2, `004023`).
- TOUCHABLE: `src/adapters/claude_code/claude_code.cpp` discover body (:570-596 at the base) + `tests/test_adapter_claude_collect.cpp` + EXACTLY the two integer literals at `.github/workflows/s2-harness.yml:85` and `:326` (m-3's surface, CG-R7.2/7.4; V-CP-1 read on the record to exclude them). NOTHING ELSE — no codex byte (V-CP-3), no collect byte (V-CP-4), no harness/stub/witness byte (V-CP-5), no other workflow byte (CG-R7.4 → STOP to m-3.planner), no CMake, no fixture file, no docs byte on the branch.
- VETOES V-CP-1..6 (`144700` lines 64-71) and S-CP-1..5 (`142000` :55-71; S-CP-5 HELD, dedupe OUT) bind as written; sealed-text silence = STOP UP through the pair Planner → master; never a local reading.
- COUNT-GATE TERMS T-1..T-5 (`002436`) and CG-R7.3/7.4: cells transcribed from the candidate's OWN `-r xml` `OverallResultsCases` tuples on BOTH targets under CG-R2's topology and the R-OBS observer environment (`CREDENTIAL_ENV_NAMES` derived from `harness/bivharness/e3.py` at the head, unset by NAME, values never read); NO arithmetic anywhere in the evidence (a "+1" is a consistency CHECK only); a census delta other than what the product diff's `TEST_CASE` delta predicts = FINDING routed UP (a skip change touches `expected_skips` → V-CG-5 routed finding FIRST); the ten per-binary tuples + XML sha256 + run identity in the commit message AND the tracked report.
- ONE commit on branch `intg/r450-discover-parity` cut at `origin/main` = `bbf297e36a38a1fab8c2675f945098a0633f9f8b` (the PUBLISHED base; product bytes equal to local `main`; the lineage exported by the PR is zero unpublished commits — MEASURED at Task 0). Commit messages end with `Co-Authored-By: Claude Fable 5.1 <noreply@anthropic.com>`.
- Shell discipline (standing corrective `164704`): every status captured as `rc=0; <cmd> || rc=$?`; never `set +e`; `grep -c` exit 1 = valid zero; every evidence file `[ -s file ] || STOP`; refspecs and paths never spelled `"$VAR:…"` (zsh modifiers) — the push line names the branch LITERALLY and is validated by `git push --dry-run` immediately before; no variable named `path`.
- The GitHub token never enters a container or any evidence; credential VALUES never read/printed; the host worktree byte-clean at product paths; inherited S4 state preserved, never cleaned.
- Merge ≠ push ≠ release. The branch push and the PR are authorized by R-4.51 clause (2) via the route; the local merge waits on the four-condition bar + the operator's condition-4 token; the post-merge push of `main` WAITS on the operator's R-4.52 ruling (stated, not chosen); no tag/release/deploy/seal; red remote CI blocks nothing and is cited nowhere. The release hold is ABSOLUTE.

---

## File structure

- Modify: `src/adapters/claude_code/claude_code.cpp:570-596` — the `discover` body only.
- Modify: `tests/test_adapter_claude_collect.cpp` — one test-local `ScopedEnvVar` helper + two small helpers + ONE new `TEST_CASE` (rows 1–5 + parity as `SECTION`s), appended after the existing discover case at :97-116 (which is unchanged).
- Modify: `.github/workflows/s2-harness.yml:85` and `:326` — the two `biv_tests` `successes` integer literals, transcribed (Task 3), nothing else.
- Evidence (outside the repository): `$EVID` under `mktemp -d`; the tracked report `docs/sprints/2026-08-27-intg-consent-fabric/results/intg-r450-discover-parity-<C>.md` lands on lane-local `main` by the pair Planner (docs lane), never on the branch.

## The circularity, stated and resolved (CG-R7.3 "observed at the candidate head")

A literal cannot be observed at the commit that contains it. Resolution, both halves recorded: (1) a PROVISIONAL commit `P` (product + test, workflow untouched) is observed on BOTH targets — the P run is the SOURCE of the two literals (copied from the XML by a script, Task 3); (2) `P` is amended into the candidate `C` (the two literals + the full message carrying the P tuples and `observed_head=P`); the tree delta `P → C` is PROVEN to be exactly the two workflow lines; `P` stays reachable under the retained local tag `r450-observed-<P>`; (3) `C` is RE-OBSERVED on both targets — the C runs are the runs OF RECORD (ten tuples + XML sha256 + run identity in the tracked report and the IMPL return), and every C cell MUST equal the literal in `C`'s workflow (the gate's own semantics, evaluated locally); any inequality = FINDING, STOP UP. The two-commit alternative (product commit, then a workflow-only child as `b065de1` did) was rejected: the route and CG-R7.2 say ONE commit.

---

### Task 0 — worktree, branch at the published base, evidence home (no product byte)

**Files:** none modified.

- [ ] **Step 0: evidence home + initial snapshot** (the inside-repo `case` guard VALIDATED 2026-09-06 in bash AND zsh: /tmp → ok, ./build → STOP) — `EVID=$(mktemp -d "${TMPDIR:-/tmp}/r450-evidence-XXXXXX")`; `case "$(cd "$EVID" && pwd -P)/" in "$(git rev-parse --show-toplevel)/"*) echo STOP-evid-inside-repo; exit 1;; esac`; `s0=0; git -C /Users/jack/Programming/bivpak status --porcelain > "$EVID/status-initial.txt" || s0=$?; [ "$s0" -eq 0 ] || STOP` (inherited S4 modifications are PRESERVED and DISCLOSED, never staged or cleaned).
- [ ] **Step 1: the base is the published pin** — `git -C /Users/jack/Programming/bivpak fetch --no-tags origin refs/heads/main:refs/remotes/origin/main` (one ref); `BASE=$(git rev-parse origin/main)`; REQUIRE `[ "$BASE" = bbf297e36a38a1fab8c2675f945098a0633f9f8b ] || STOP` (the remote moved — STOP UP, never re-base silently); `d=0; git diff --quiet bbf297e36a38a1fab8c2675f945098a0633f9f8b main -- src tests CMakeLists.txt CMakePresets.json harness .github || d=$?; [ "$d" -eq 0 ] || STOP` (product bytes at the published pin == local main; measured 2026-09-05: 0 lines).
- [ ] **Step 2: worktree + branch** — `git -C /Users/jack/Programming/bivpak worktree add -b intg/r450-discover-parity /Users/jack/Programming/bivpak-intg-r450-discover-parity bbf297e36a38a1fab8c2675f945098a0633f9f8b`; `cd /Users/jack/Programming/bivpak-intg-r450-discover-parity`; REQUIRE `git rev-parse HEAD` == the pin; `git status --porcelain` empty. Record `$EVID/base.txt` = the pin.
- [ ] **Step 3: the cut-point measurement (R-4.8 lesson)** — `n=$(git rev-list --count origin/main..HEAD)`; REQUIRE `0` → `$EVID/cutpoint.txt` = `unpublished_commits_in_lineage=0`. (After the ONE commit, Task 5 re-measures `origin/main..HEAD^` = 0: the PR's lineage exports nothing unpublished.)
- [ ] **Step 4: baseline build + baseline discover census** — `cmake --preset ci-macos && cmake --build --preset ci-macos`; `./build/ci-macos/biv_tests "Claude adapter discovers CLAUDE_CONFIG_DIR as an env-tier store"` → PASS (the existing case, "env exists / default absent", unchanged by this act). Record the three fenced files' sha256 at the base into `$EVID/base-hashes.txt` (`claude_code.cpp`, `codex.cpp`, `test_adapter_claude_collect.cpp`; codex's must be IDENTICAL at `C`, Task 5).

### Task 1 — the witness first (RED), then the discover body (GREEN)

**Files:** Modify `tests/test_adapter_claude_collect.cpp` (append after :116); Modify `src/adapters/claude_code/claude_code.cpp:570-596`.

**Interfaces:** consumes `biv::adapters::Env{getenv, home}`, `Store{root, locators, tier, archived}`, `DiscoveryTier{env, defaults, …}` (`src/adapters/adapter.hpp:23-49`); `biv::adapters::claude_code_adapter()` / `biv::adapters::codex_adapter()`; `biv::pack::pack(const fs::path&) -> expected<PackReport>` (`src/core/pack/pack.hpp:59`), `BivError{kind, path, detail}` (`src/core/support/error.hpp:40-46`), `ErrKind::ArchiveWriteFailed`.

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

Add `#include "adapters/codex/codex.hpp"`, `#include "core/pack/pack.hpp"`, `#include "core/support/error.hpp"` (if `pack.hpp` does not already expose `ErrKind`) beside the existing includes.

- [ ] **Step 2: write the ONE new TEST_CASE** (rows 1–5 + parity as SECTIONs; appended after the existing discover case):

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

  SECTION("ROW 5 (pinned interim, NOT c1 §7 dedupe/provenance compliance): one session id in both stores -> pack refuses") {
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

- [ ] **Step 3: run it RED at the base bytes** — `cmake --build --preset ci-macos && ./build/ci-macos/biv_tests "Claude adapter discovery returns every store found: env and default both searched with codex parity (c1 §7)" -r console > "$EVID/witness-red.log" 2>&1 || true`. EXPECTED: ROW 1 FAILS (`stores->size() == 2` sees 1 — today's early return) and ROW 5 FAILS (`REQUIRE_FALSE(refused.has_value())` — today only the env store is collected, so pack succeeds); ROWS 2/3/4 pass already. Any OTHER failure (e.g. a ROW 5 refusal for a reason other than `adapter-session-invalid`, or ROW 2/3/4 red) = a fixture or model defect → fix the TEST, re-run, and record; if it points at product behaviour outside the discover body → STOP UP (S-CP-4).
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

- [ ] **Step 5: GREEN** — rebuild; run the new case → PASS (all five SECTION leaves); run the existing discover case → PASS; then the FULL macOS suite exactly as the workflow does: `ctest --preset ci-macos -E '^safety-hardening$' --output-on-failure > "$EVID/ctest-macos-pre.log" 2>&1` → rc 0 (host-environment-only reds — the E3 by-name credential tripwire on `harness-selftest` when a credential NAME is exported in the operator's shell — are classified by the R-OBS discriminator in Task 2, never waved through).
- [ ] **Step 6: fence self-check before the provisional commit** — `git status --porcelain` names EXACTLY `src/adapters/claude_code/claude_code.cpp` and `tests/test_adapter_claude_collect.cpp` (and the ignored `build/`); `git diff -U0 -- src/adapters/claude_code/claude_code.cpp | grep -E '^@@'` → every hunk header's old-range lies within `570,596`; `git diff --numstat -- src/adapters/codex/` → empty; no harness path in the status. Anything else = STOP (V-CP-1/3/5), no commit.
- [ ] **Step 7: the PROVISIONAL commit P** — `git add src/adapters/claude_code/claude_code.cpp tests/test_adapter_claude_collect.cpp && git commit -q -F "$EVID/message-P.txt"` where `message-P.txt` = `adapters(claude): discover returns every store found (env + default), codex parity — PROVISIONAL, cells not yet transcribed` + a body naming the design pin and plan pin + the trailer line. `P=$(git rev-parse HEAD)`; `printf '%s\n' "$P" > "$EVID/observed-head-P.txt"`; `git tag "r450-observed-$P"` (retained; never pushed — `--no-tags` everywhere).

### Task 2 — observation at P on BOTH targets (the SOURCE of the literals; CG-R7.3, T-1)

**Files:** none modified. Execute `PL-intg-countgate-20260830.md` Task 1 Steps 3 and 4 (the PROVEN instrument — R-OBS-1..6 macOS observation under the derived unset-name environment, the R-OBS-3 discriminator EXECUTED, the five `-r xml` runs per target, the four-phase Linux container: Phase H / R / T / S at `git show 990ba3b:docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep1-20260827.md` Task 5 Step 3 :757-763) VERBATIM with these retargets ONLY: (a) the run head is `P` (`$EVID/observed-head-P.txt`), the working tree is the r450 worktree, and Phase T clones the BRANCH `intg/r450-discover-parity` from `/repo-ro` with the receipt `rev-parse HEAD == P`; (b) XMLs land in `$EVID/P/<binary>-<target>.xml` and tuples in `$EVID/P/tuples-<target>.txt`; (c) the ancestry proofs are `git merge-base --is-ancestor bbf297e36a38a1fab8c2675f945098a0633f9f8b P` (rc 0) and `… b065de1107161bb5df9543c09b50091365338c1c P` (rc 0 — the count-gate repair is in the lineage).

- [ ] **Step 1: macOS observation at P** — as Steps 3(a)–(g) of the countgate plan (derive `CREDENTIAL_ENV_NAMES` at P; host presence by name; discriminator arms 1/2 with the `iff`/`hygiene` predicate; the five `-r xml` runs under `"${OBS_ENV[@]}"`; the inverted scout; the token scan over the concatenated logs `hits=0`; run identity). Extract per binary: `python3 - "$EVID/P/<binary>-macos.xml"` reading `OverallResultsCases` → `successes failures expectedFailures skips` and the biv_tests skipped-name set (must be byte-identical to the workflow's `expected_skips` at P — a difference = V-CG-5 FINDING, STOP UP).
- [ ] **Step 2: Linux observation at P** — the four-phase container (ubuntu:24.04 `--platform linux/amd64` `--init`; `nofile` soft raised to hard inside the runuser drop; R-OBS-6 name-free proof by name inside the container before the measurement stage; `cmake --preset ci` + build + the five `-r xml` runs), XMLs + per-stage rc ledger copied out to `$EVID/P/`, sha256 of each XML recorded.
- [ ] **Step 3: the consistency CHECK (T-4, CG-R7.3) — a check, never the source** — for each target: `biv_tests.successes(P) − <the literal currently at :85 / :326>` MUST equal the product diff's `TEST_CASE` delta (`git diff bbf297e36a38a1fab8c2675f945098a0633f9f8b P -- tests | grep -c '^+TEST_CASE('` = 1 and `grep -c '^-TEST_CASE('` = 0 → predicted +1); `failures == 0`, `expectedFailures == 0`, `skips` unchanged (3 macOS / 1 Linux), the other four binaries' tuples unchanged. ANY other delta = FINDING routed UP through the pair Planner (never a quiet re-observation, never an exclusion).
- [ ] **Step 4: no-mutation proof** — `git status --porcelain` in the worktree is EMPTY after observation (the evidence lives under `$EVID`; build dirs are ignored); `diff` of the main-repo status against `status-initial.txt` empty.

### Task 3 — transcribe the two literals FROM THE XML and amend P → C (one commit)

**Files:** Modify `.github/workflows/s2-harness.yml:85` and `:326` (integer literals only).

- [ ] **Step 1: the transcription script — reads the XML, writes the literal, refuses anything else** (VALIDATED 2026-09-06 at the pair Planner's seat on a scratch copy of the workflow with two synthetic XMLs: correct block lines → the two literals replaced, all other bytes identical; a wrong anchor line → exit 3 with no write; a missing `OverallResultsCases` → exit 2 with no write):

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

Run: `python3 "$EVID/transcribe.py" .github/workflows/s2-harness.yml "$EVID/P/biv_tests-macos.xml" "$EVID/P/biv_tests-linux.xml"`; REQUIRE rc 0.
- [ ] **Step 2: prove the workflow hunk is EXACTLY the two literals (CG-R7.4)** — `git diff --numstat -- .github/workflows/s2-harness.yml` → `2 2 .github/workflows/s2-harness.yml`; `git diff -U0 -- .github/workflows/s2-harness.yml | grep -E '^[-+][^-+]' > "$EVID/workflow-hunk.txt"` → exactly 4 lines, each matching `^[-+]\s+"successes": [0-9]+,$`; `git status --porcelain` names ONLY the workflow. Anything else = STOP to m-3.planner (through the pair Planner).
- [ ] **Step 3: the ONE commit C = amend P** — `git add .github/workflows/s2-harness.yml && git commit -q --amend -F "$EVID/message-C.txt"`. `message-C.txt`: subject `adapters(claude): discover returns every store found (env + default), codex parity; count-gate cells transcribed`; body: `Design pin: m2-r450-discover-fence-rev2-20260903 sha256 f2216ee606a03b0b5b0b7f4562fed52a7349219c28990e6ee3e89b0cc25e8c6f`; `Plan pin: intg-r450-discover-parity-plan-20260906 sha256 <this artifact's approved hash>`; `observed_head=P=<sha> (retained tag r450-observed-<sha>; tree delta P->C = the two workflow literals only, proven)`; `Observed cells (no arithmetic):` then the TEN `binary=… target=… run_id=… successes=… failures=… expectedFailures=… skips=… xml_sha256=…` lines from the P runs exactly in `b065de1`'s form; the macOS and Linux run-identity + observer blocks (names only); the trailer `Co-Authored-By: Claude Fable 5.1 <noreply@anthropic.com>`. `C=$(git rev-parse HEAD)`; `printf '%s\n' "$C" > "$EVID/candidate-C.txt"`.
- [ ] **Step 4: prove P → C** (the `:(exclude)` pathspec form VALIDATED 2026-09-06 in bash AND zsh on real commits: a workflow-only commit → rc 0; a product merge → rc 1) — `git diff --numstat "$(cat "$EVID/observed-head-P.txt")" "$C"` → exactly `2 2 .github/workflows/s2-harness.yml`; `git diff --quiet "$(cat "$EVID/observed-head-P.txt")" "$C" -- . ':(exclude).github/workflows/s2-harness.yml'` → rc 0; `git rev-parse "$C^"` == the base pin; `git rev-list --count origin/main..$C^` = 0 (the cut-point measure). Record all four in `$EVID/p-to-c-proof.txt`.

### Task 4 — RE-OBSERVATION OF RECORD at C, both targets (the runs the tracked report and IMPL return carry)

- [ ] **Step 1:** repeat Task 2 Steps 1–2 with the run head `C` → `$EVID/C/…` (ten tuples, XML sha256, run identities, R-OBS discriminator + token scan, in-container name-free proof).
- [ ] **Step 2: the gate's own semantics, locally** — for each of the ten cells: the C tuple MUST equal the workflow's literal at `C` (`biv_tests` `:85` / `:326`; the other eight cells unchanged literals) AND equal the P tuple. Write `$EVID/C/gate-equality.txt` with one `binary target literal observed equal=yes|no` line each; ANY `no` = FINDING, STOP UP (no re-transcription, no amend — the plan returns to the pair Planner). The biv_tests skipped-name sets == `expected_skips` on both targets.
- [ ] **Step 3: no-mutation proof** as Task 2 Step 4.

### Task 5 — fence proofs at C, census of record at the branch head, IMPL return (no push yet)

- [ ] **Step 1: the touched set** — `git diff --numstat bbf297e36a38a1fab8c2675f945098a0633f9f8b "$C"` → EXACTLY three paths: `src/adapters/claude_code/claude_code.cpp`, `tests/test_adapter_claude_collect.cpp`, `.github/workflows/s2-harness.yml` (2/2). `sha256` of `src/adapters/codex/codex.cpp` at `C` == `$EVID/base-hashes.txt` (V-CP-3). No `harness/` path (V-CP-5). `claude_code.cpp` hunk headers within `570,596` (V-CP-1); `git diff bbf297e… "$C" -- src/adapters/claude_code/claude_code.cpp | grep -c 'collect('` = 0 (V-CP-4 — no collect byte).
- [ ] **Step 2: the census of record at the branch head, BOTH arms (082012 Answer (1) regex; expectations WRITTEN FIRST)** — write `$EVID/census-expected-tree.txt` = the three lines of the first-push receipt (`tests/test_adapter_codex_collect.cpp:383`, `:385`, `tests/test_cli.cpp:1188`, the `sk-complete` fixture-filename false positive) and `$EVID/census-expected-history.txt` = the two paths `tests/test_adapter_codex_collect.cpp`, `tests/test_cli.cpp`; then tree arm `git grep -n -E 'sk-[A-Za-z0-9]{8,}|-----BEGIN [A-Z ]*PRIVATE KEY|AKIA[0-9A-Z]{16}|ghp_[A-Za-z0-9]{20,}|xox[abprs]-' "$C" -- . > "$EVID/census-tree.txt"` (paths + line numbers; NO values printed beyond the fixture filenames the receipt already names) and history arm `git rev-list "$C" > "$EVID/rl.txt"` then `xargs git grep -l -E '<same alternation>' < "$EVID/rl.txt" | sed 's/^[0-9a-f]*://' | sort -u > "$EVID/census-history.txt"`; REQUIRE `diff` against each expectation EMPTY (the sort/xargs producers status-checked as separate stages, files not process substitution). ANY new line or path = STOP UP, never a judgement call.
- [ ] **Step 3: the IMPL return relay** (PHASE IMPL, report-only body, TO intg.pair-planner) carries: `C`, `P`, the base, the cut-point measure, the three-path numstat, the hunk-range proof, codex sha equality, the ten C tuples + ten P tuples (+ XML sha256 + run ids), the two run-identity/observer blocks (names only), the discriminator predicate, token-scan hits=0, gate-equality all yes, the witness RED log summary (which SECTIONs failed at the base) and GREEN, the census result, `git status --porcelain` empty in the worktree, the retained tag name. NO push, NO PR yet — those are Task 6 after both owner reviews return through master.

### Task 6 — the vehicle (after the pair Planner's verification + m-2's fenced review + m-3's hunk review return through master with no red): push the branch, open the PR

- [ ] **Step 1: pre-push gate (the first-push discipline, retargeted to ONE remote BRANCH ref)** — `git remote get-url --push --all origin` → exactly one line, recorded; `git ls-remote --heads origin intg/r450-discover-parity` → EMPTY (the ref must not pre-exist; non-empty = STOP UP); `gh repo view --json visibility -q .visibility` → `PRIVATE`; `[ -x "$(git rev-parse --git-path hooks/pre-push)" ]` → not executable; `git rev-parse HEAD` == `C`; the census (Task 5 Step 2) re-asserted at `C` (same files, `diff` empty); shell recorded (`echo "$0" / $ZSH_VERSION`).
- [ ] **Step 2: dry-run, then the push — LITERAL names, no refspec variable** — `git push --dry-run --no-tags origin intg/r450-discover-parity > "$EVID/push-dry.txt" 2>&1` → rc 0, output naming `[new branch] intg/r450-discover-parity -> intg/r450-discover-parity`; then THE VERY NEXT COMMAND: `p=0; git push --no-tags origin intg/r450-discover-parity > "$EVID/push-stdout.txt" 2> "$EVID/push-stderr.txt" || p=$?; printf 'push_rc=%s\n' "$p" > "$EVID/push-rc.txt"`; outcome probe ALWAYS: `git ls-remote --heads origin intg/r450-discover-parity` == `C` → class a (rc 0 + remote at C); rc 0 with remote ≠ C = class e (STOP UP); rc ≠ 0 = class b/c per the first-push plan's classifier; ONE attempt per token, nothing retried in-lane.
- [ ] **Step 3: the PR** — `gh pr create --base main --head intg/r450-discover-parity --title "adapters(claude): discover returns every store found (env + default), codex parity; count-gate cells transcribed" --body-file "$EVID/pr-body.md"` where `pr-body.md` names: the design pin, the plan pin, `C`, the three-path numstat, the ten C tuples, the two owner-review relays, and the sentence "This PR is the vehicle under R-4.51 clause (2); the evidence of record is the local suites, the Docker parity leg, the owner byte reviews, and the operator's condition-4 token — a red remote CI is cited nowhere. Merge is local under the operator's token; the post-merge push of main waits on R-4.52." Record the PR URL/number in `$EVID/pr.txt`. No label, no reviewer request, no auto-merge, no `gh pr ready`/draft toggling, no comment. (The route authorizes the PR as the vehicle; if `gh pr create` asks anything interactive → abort, STOP UP.)
- [ ] **Step 4: SITREP UP** with the push class, the PR URL, and the receipt files; the MERGE-GATE packet (`results/intg-r450-discover-parity-merge-gate.md`, four conditions) follows from the pair Planner; the local merge (`git merge --no-ff` of `C` into lane-local `main`, §8-style receipt) happens ONLY under the operator's condition-4 token; the post-merge push of `main` WAITS on R-4.52.

---

## Acceptance criteria (each measured, none inferred)

1. At `C`: `git diff --numstat bbf297e… C` = exactly the three paths; workflow 2/2 with the four changed lines all `"successes": <int>,`; `claude_code.cpp` hunks within :570-596; codex.cpp sha unchanged; no harness/CMake/fixture/docs byte on the branch.
2. The new TEST_CASE was RED at the base (ROW 1 + ROW 5 failing, log retained) and is GREEN at `C` on both targets; the existing discover case unchanged and green.
3. Ten C tuples observed under CG-R2 + R-OBS on both targets; each biv_tests cell EQUALS the literal at `C`; the other eight tuples unchanged; skips 3/1 with `expected_skips` byte-identical; P tuples == C tuples; the P→C tree delta = the two literals; no arithmetic in any evidence.
4. Full macOS ctest (the workflow's exclusion only) rc 0 under the R-OBS environment; the Linux parity leg reaches ctest and the count check passes with the transcribed cells.
5. Census of record at `C` both arms == the written expectations.
6. Cut-point `origin/main..C^` = 0; `C^` = `bbf297e…`; the branch pushed with class a; the PR open against `main`; `main` NOT pushed; no tag pushed; no release act.
7. m-2's fenced review (V-CP-1..6) and m-3's hunk review (CG-R7.5 a–e) both return through master with no red before the merge bar.

## Out of scope (an act here is a STOP, not a judgement)

Dedupe/provenance semantics (S-CP-5 HELD); any collect byte; any codex byte; any harness/stub/witness byte (S-CP-2 is m-3's at landing); any user-facing wording/warning/exit change (S-CP-3); any pack/open interaction beyond enumeration (S-CP-4); any workflow byte beyond the two literals; `expected_skips`; CMake; fixtures under `tests/fixtures/`; the R-4.49 act; pushing `main`; tags; release.

## Anti-half-fix guards

- The witness must have been RED first (Task 1 Step 3 log) — a green-only witness is not a witness.
- ROW 5's discriminator (one store → pack succeeds with one session) must PASS in the same SECTION; a refusal without the passing control is not evidence of both-store discovery.
- The literals are written by the script from the XML; a hand-typed literal, or a literal equal to "old + 1" without an XML, is V-CG-2 red.
- P and C both observed; equality proven; the retained tag keeps P reachable for both owner reviews.

## Revision history

- **rev1** — DRAFTED 2026-09-06 after master `004023` (hold lifted to drafting); FILES for review only after m-2.implementer's peer approve lands and the edge re-measures GREEN root-mode at its pdc commit.
