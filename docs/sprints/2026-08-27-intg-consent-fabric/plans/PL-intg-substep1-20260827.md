# intg sub-step 1 — A6 consent-UX fabric (engine unwired) Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:executing-plans (the executor is the addressed `intg.pair-implementer`; implementation starts ONLY on the pair Planner's bare dispatch token after PLAN-REVIEW approve). Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Land the SEALED Addendum-6 rev14 consumer fabric — the `--accept-url-divergence` flag, help closure, the two url-divergence ErrKinds with their exit rows, the three envelope-contract sites, the carrier structs/serialization, the widened open-exit aggregator, and the PROMPT D renderer module — on branch `intg/consent-fabric`, with the engine fully unwired and only the spine-assigned landing legs claimed.

**Architecture:** All bytes are CLI/report/contract-layer; ZERO engine bytes and ZERO product references into `src/core/repo/`. The renderer + A7-R1 predicate land as a self-contained `src/cli/url_consent` module whose only consumer today is its unit tests — its declared production consumer is sub-step 2b's wiring act (V-A6-6 makes that consumer mandatory-at-wiring). Carriers ride `OpenReport`/`PackReport` as plain-string structs in `src/core/support/` so no layering or engine include is introduced.

**Tech Stack:** C++23, Catch2 (`tests/`), pytest selftest (`harness/selftest/`), JSON Schema Draft 2020-12.

**Spec:** SEALED m-3 Addendum-6 rev14 — pdc `master/domains/m-3-restore-cli/design/2026-08-24-addendum-6-url-consent-consumer-surface.md`, lock `m3-addendum-6-c41d015f-lock-20260825` (locked pin `c41d015f…`, post-stamp `7ce2251d…`); SEALED m-3 Addendum-7 rev2 — `.../2026-08-26-addendum-7-consent-interaction-companion.md`, lock `m3-addendum-7-4c40fe37-lock-20260827` (locked pin `4c40fe37…`, post-stamp `e4a6b982…`). Read-only context: LOCKED M rev8 (M-R3 hook contract). Bars: R-4.47 (S1–S4/V1–V5/E1–E5, OBLIGATIONS §B2); RECONCILE §R1 constraints I2–I6.

## Global Constraints

- Base and branch: `git worktree add ../bivpak-intg-consent-fabric -b intg/consent-fabric 02b51435` — product work happens ONLY in that worktree (the primary worktree hosts the relay daemon and other seats; never switch its branch). No rebase without a routed STOP.
- SEALED TEXT ONLY: where A6/A7 determine, execute byte-exactly; anything they defer or are silent on is a STOP up the pair line — never a keyboard call (A6-R7, A7-R5).
- Golden-byte fence (V-A6-2): every user-facing template byte comes verbatim from A6-R2/R4. Two byte cells are UNDETERMINED and are routed as STOP-1 (see Task 4's gate); Task 4 is blocked until the answer relay is cited.
- One-commit rule (V-A6-3, R-3.43, R-4.34-lesson): the commit that lands either ErrKind lands, in the SAME commit, both exit-map rows, all three envelope-schema sites, both derived parity rows in `tests/test_envelope.cpp`, and BOTH recomputed selftest blob pins. Task 2 is that commit.
- Zero-engine fence (V-A6-6 / R-4.47 V1, RECONCILE I6): no engine byte changes; no product call site to `run_eligibility`, `restore_entry`, `repo::capture`, or any network-class engine path; no `#include` of any `src/core/repo/` header from product code. Task 5 proves it by grep.
- No PROCEED-default anywhere; `--json` is never a consent suppressor or enabler (A7-R2, R-4.47 V3 shadow); PROMPT D's predicate has NO json term and NO env/config override (A7-R1; proposing one is a STOP to MASTER).
- No new argv/env/config surface beyond exactly `--accept-url-divergence` (A7-V4, S8 scope fence: no unlanded design-table flags — `--offline`/`--network`/`--merge`/`--with-memory*`/`--rename-path`/`--session-store` are OUT).
- No persistence of any approval in any form (V-A6-1).
- No explicit `list`/`info` flag parsing (RECONCILE I2; R-6.2 owns their closed grammar); the a6·14 regression pins the inert observable only.
- No consent-surface text that classifies/annotates an address, ranks a target, or proposes persistence (R-4.47 S3).
- Sub-step 1 claims ONLY the spine-assigned landing legs: a6·14, a6·15, a6·17, a6·18, and the zero-state half of a6·16. All behavioral legs (a6·1–13, divergence half of a6·16, all five FX-A7 legs) are DUE AT 2b and no E2 coverage is claimed for them here (RECONCILE I5).
- Do not touch `build_preview`/`render_prompt_b` (R-4.24 fires on any touch), PROMPT A/B/C texts or predicates (A6-R6), or the R-3.29 rewrite/verify surface.
- Tests land inside the existing `biv_tests` / selftest targets (no new ctest target, so no macOS allowlist row is owed; R-3.37 disclosed).
- Every commit in the worktree is authored as `intg.pair-implementer`; commits stay green (TDD red states live only in the working tree).

## File structure

```text
Modify: src/cli/args.hpp            (Command gains accept_url_divergence)
Modify: src/cli/args.cpp            (pack + open parse branches; help line)
Create: src/cli/url_consent.hpp     (facts struct, renderers, A7-R1 predicate, prompt)
Create: src/cli/url_consent.cpp
Modify: src/cli/main.cpp:363        (exit_for_open aggregator call)
Modify: src/core/support/error.hpp  (two ErrKinds appended)
Modify: src/core/support/error.cpp  (to_string cases)
Create: src/core/support/url_divergence.hpp (two carrier structs)
Modify: src/core/open/open.hpp      (OpenReport carrier fields)
Modify: src/core/pack/pack.hpp      (PackReport accepted-advisory field)
Modify: src/core/report/envelope.hpp (exit_for_open declaration)
Modify: src/core/report/envelope.cpp (exit rows; writer: refusals array + third advisory member on both verbs; exit_for_open)
Modify: schemas/biv-exit-map.v1.json (two rows appended)
Modify: schemas/biv-json-envelope.v1.schema.json (three A6-R1 sites)
Modify: tests/test_cli.cpp          (help golden; a6·14 regression; parser tests)
Modify: tests/test_envelope.cpp     (two derived parity rows; writer/aggregator unit tests)
Modify: harness/selftest/test_envelope.py (both blob pins recomputed; a6·17 structural tests; zero-state validation)
Create: tests/test_url_consent.cpp only if CMake needs it — otherwise the unit tests join tests/test_cli.cpp (follow the existing single-binary layout; do NOT add a ctest target)
```

CMake note: if `tests/CMakeLists.txt` enumerates source files, add the new `src/cli/url_consent.cpp` to the existing `biv` / `biv_tests` source lists — no new target.

---

### Task 1: flag parsing + help closure (a6·18 home, a6·14 regression)

**Files:** Modify `src/cli/args.hpp:17-25`, `src/cli/args.cpp` (pack loop `:168-176`, open loop `:193-255`, `help_text` `:130-147`), `tests/test_cli.cpp` (help golden `:1425-1440` + new cases).

**Interfaces — Produces:** `biv::cli::Command::accept_url_divergence` (`bool`, default `false`), set by `--accept-url-divergence` on `pack` and `open`. Task 3's aggregator and 2b's wiring consume it.

- [ ] **Step 1: failing tests.** Update the byte-whole help golden and add parser cases:

```cpp
// tests/test_cli.cpp — REPLACE the expected string in
// "Task 4 CLI help documents the strict agent binary pin syntax":
CHECK(help.out ==
      "usage: biv open <image> [options]\n"
      "  --dest <path>\n"
      "  --consent <yes|no|agent=yes,...>\n"
      "  --accept-url-divergence\n"
      "  --agent-bin <claude-code|codex>=<absolute-or-relative-path>\n"
      "  --rename\n"
      "  --abort-on-collision\n"
      "  --verify\n"
      "  --json\n");

TEST_CASE("a6-R3 pack and open accept --accept-url-divergence") {
  // open: flag parses alongside an image; no usage error
  {
    char prog[] = "biv", verb[] = "open", flag[] = "--accept-url-divergence", img[] = "x.bvpk";
    char* argv[] = {prog, verb, flag, img};
    const auto parsed = biv::cli::parse_args(std::span<char* const>{argv, 4});
    REQUIRE(parsed.has_value());
    CHECK(parsed->accept_url_divergence);
    CHECK(parsed->verb == biv::cli::Verb::open);
  }
  // pack: the ONE accepted flag; other flags still rejected
  {
    char prog[] = "biv", verb[] = "pack", flag[] = "--accept-url-divergence", dir[] = "srcdir";
    char* argv[] = {prog, verb, flag, dir};
    const auto parsed = biv::cli::parse_args(std::span<char* const>{argv, 4});
    REQUIRE(parsed.has_value());
    CHECK(parsed->accept_url_divergence);
  }
  {
    char prog[] = "biv", verb[] = "pack", flag[] = "--not-a-flag", dir[] = "srcdir";
    char* argv[] = {prog, verb, flag, dir};
    CHECK_FALSE(biv::cli::parse_args(std::span<char* const>{argv, 4}).has_value());
  }
}

TEST_CASE("a6.14 list/info accept the flag inert with zero A6 surfaces") {
  const auto root = make_tmp("a6-14-inert");
  const auto with_flag = run_cmd("list --accept-url-divergence missing.bvpk", root);
  const auto without   = run_cmd("list missing.bvpk", root);
  CHECK(with_flag.code == without.code);            // exit unchanged from flagless
  CHECK(with_flag.out.find("UrlDivergence") == std::string::npos);
  CHECK(with_flag.err.find("url-divergence") == std::string::npos);
  const auto info_flag = run_cmd("info --accept-url-divergence missing.bvpk", root);
  const auto info_none = run_cmd("info missing.bvpk", root);
  CHECK(info_flag.code == info_none.code);
  std::filesystem::remove_all(root);
}
```

(The a6·14 case pins the FLAG spelling's inert observable only — it must not assert acceptance of arbitrary trailing tokens; the stub path is not this feature's contract. RECONCILE I2.)

- [ ] **Step 2: run, verify FAIL** — `ctest --test-dir build -R cli` (or the repo's equivalent target): the help golden fails on the missing line; the parser cases fail on `unknown-flag`.
- [ ] **Step 3: implement.**

```cpp
// src/cli/args.hpp — inside struct Command, after `bool help{false};`:
  bool accept_url_divergence{false};
```

```cpp
// src/cli/args.cpp help_text — insert ONE line directly after the --consent line
// (consent-family adjacency, A6-R9; two-space indent, flag only, newline):
        "  --consent <yes|no|agent=yes,...>\n"
        "  --accept-url-divergence\n"
        "  --agent-bin <";
```

```cpp
// src/cli/args.cpp pack loop — replace the unconditional flag rejection:
    for (size_t i = 1; i < tokens.size(); ++i) {
      if (tokens.at(i) == "--accept-url-divergence") {
        command.accept_url_divergence = true;
        continue;
      }
      if (is_flag(tokens.at(i))) {
        return std::unexpected(usage("unknown-flag"));
      }
      ...unchanged...
    }
```

```cpp
// src/cli/args.cpp open loop — one new branch beside the existing flag branches
// (same idiom as --verify: set and continue; repeats behave like every other flag):
      } else if (arg == "--accept-url-divergence") {
        command.accept_url_divergence = true;
      } else if (arg == "--verify") {
```

- [ ] **Step 4: run, verify PASS** (help golden byte-whole; parser cases; a6·14 pair).
- [ ] **Step 5: commit** — `git add src/cli/args.hpp src/cli/args.cpp tests/test_cli.cpp && git commit -m "feat(cli): --accept-url-divergence parses on pack/open; open help gains its line after --consent (sealed A6-R3/R9; a6.18 golden updated; a6.14 inert regression)"`

### Task 2: the CONTRACT + CARRIER commit (one commit, V-A6-3)

**Files:** Modify `src/core/support/error.hpp`, `src/core/support/error.cpp`, `src/core/report/envelope.hpp`, `src/core/report/envelope.cpp`, `src/core/open/open.hpp:28-35`, `src/core/pack/pack.hpp:44-55`, `src/cli/main.cpp:363`, `schemas/biv-exit-map.v1.json`, `schemas/biv-json-envelope.v1.schema.json`, `tests/test_envelope.cpp`, `harness/selftest/test_envelope.py`. Create `src/core/support/url_divergence.hpp`.

**Interfaces — Produces:**
- `biv::ErrKind::UrlDivergenceRefused` (exit 3, class refusal), `biv::ErrKind::UrlDivergenceEntryRefused` (exit 2, class divergence) — appended after `ParseError`.
- `biv::UrlDivergenceEntryRefusal { std::string repo_id, relpath, requested, effective, op; }` and `biv::UrlDivergenceAcceptedEntry { std::string requested, effective, op, repo; }` in `src/core/support/url_divergence.hpp`.
- `open::OpenReport` gains `std::vector<UrlDivergenceEntryRefusal> url_divergence_refusals{}` and `std::vector<UrlDivergenceAcceptedEntry> url_divergence_accepted{}`; `pack::PackReport` gains `std::vector<UrlDivergenceAcceptedEntry> url_divergence_accepted{}`. (Empty in all of sub-step 1; 2b populates.)
- `biv::report::exit_for_open(const core_sessions::SessionsOutcome&, const std::vector<UrlDivergenceEntryRefusal>&) -> int` — the A6-R1 typed aggregator.

- [ ] **Step 1: failing tests.**

```cpp
// tests/test_envelope.cpp — APPEND to the ExpectedRow vector (declaration-derived
// positions: the two members are appended to ErrKind, so the rows append here):
      {"UrlDivergenceRefused", "refusal", biv::report::exit_for_error(biv::ErrKind::UrlDivergenceRefused)},
      {"UrlDivergenceEntryRefused", "divergence", biv::report::exit_for_error(biv::ErrKind::UrlDivergenceEntryRefused)}};

TEST_CASE("a6-R1 carriers: refusal rows, grouped advisory, zero-state absence") {
  biv::open::OpenReport report{.image_path = "img.bvpk", .output_dir = "out"};
  // zero state (a6.15 unit half): both carriers ABSENT
  const auto zero = biv::report::envelope("open", std::nullopt, report, std::nullopt, 0);
  CHECK(zero.find("url_divergence_refusals") == std::string::npos);
  CHECK(zero.find("url-divergence-accepted") == std::string::npos);
  // populated: rows in vector (encounter) order; advisory grouped, one outer object
  report.url_divergence_refusals = {
      {"r1", "a/b", "https://req", "https://eff", "fetch"},
      {"r2", "c/d", "https://req2", "https://eff2", "fetch"}};
  report.url_divergence_accepted = {{"https://q", "https://e", "fetch", "/repo"}};
  const auto populated = biv::report::envelope("open", std::nullopt, report, std::nullopt, 2);
  const auto first = populated.find("\"repo_id\": \"r1\"");
  const auto second = populated.find("\"repo_id\": \"r2\"");
  REQUIRE(first != std::string::npos);
  REQUIRE(second != std::string::npos);
  CHECK(first < second);
  CHECK(populated.find("\"kind\": \"UrlDivergenceEntryRefused\"") != std::string::npos);
  CHECK(count_occurrences(populated, "url-divergence-accepted") == 1);
  CHECK(populated.find("\"repo\": \"/repo\"") != std::string::npos);
}

TEST_CASE("a6-R1 exit composition: one typed aggregator over both sources") {
  core_sessions::SessionsOutcome clean{};  // no rows -> exit_for_sessions == 0
  const std::vector<biv::UrlDivergenceEntryRefusal> rows{
      {"r1", "a/b", "https://req", "https://eff", "fetch"}};
  CHECK(biv::report::exit_for_open(clean, {}) == 0);
  CHECK(biv::report::exit_for_open(clean, rows) == 2);  // repository population alone
}
```

```python
# harness/selftest/test_envelope.py — a6.17 structural declarations (i)/(ii)/(iii)
def _schema():
    return json.loads((REPO_ROOT / "schemas/biv-json-envelope.v1.schema.json").read_text())

def test_a6_17_i_open_result_declares_url_divergence_refusals():
    result_obj = next(b for b in _schema()["properties"]["result"]["anyOf"]
                      if isinstance(b, dict) and b.get("type") == "object")
    prop = result_obj["properties"]["url_divergence_refusals"]
    assert prop["minItems"] == 1
    items = prop["items"]
    assert sorted(items["required"]) == ["effective", "kind", "op", "relpath", "repo_id", "requested"]
    assert items["properties"]["kind"] == {"const": "UrlDivergenceEntryRefused"}
    for field in ("repo_id", "relpath", "requested", "effective", "op"):
        assert items["properties"][field] == {"type": "string"}

def test_a6_17_ii_error_facts_declare_the_three_hook_facts():
    error_obj = next(b for b in _schema()["properties"]["error"]["anyOf"]
                     if isinstance(b, dict) and b.get("type") == "object")
    facts = error_obj["properties"]["facts"]["properties"]
    for field in ("requested", "effective", "op"):
        assert facts[field] == {"type": "string"}

def test_a6_17_iii_accepted_advisory_branch_declares_complete_structure():
    branches = _schema()["properties"]["advisories"]["items"]["oneOf"]
    branch = next(b for b in branches
                  if b.get("properties", {}).get("kind") == {"const": "url-divergence-accepted"})
    assert sorted(branch["required"]) == ["entries", "kind"]
    entries = branch["properties"]["entries"]
    assert entries["minItems"] == 1
    assert sorted(entries["items"]["required"]) == ["effective", "op", "repo", "requested"]
    for field in ("requested", "effective", "op", "repo"):
        assert entries["items"]["properties"][field] == {"type": "string"}
```

- [ ] **Step 2: run, verify FAIL** — parity rows fail (`exit_for_error` case missing → compile error first: add enum members before running; run after Step 3's enum edit to see the JSON-side failures), a6·17 tests fail on missing declarations, the carrier unit tests fail to compile.
- [ ] **Step 3: implement.**

```cpp
// src/core/support/error.hpp — append inside enum class ErrKind after ParseError:
  ParseError,
  UrlDivergenceRefused,
  UrlDivergenceEntryRefused
```

```cpp
// src/core/support/error.cpp — two cases before the closing brace of the switch:
    case ErrKind::UrlDivergenceRefused:
      return "UrlDivergenceRefused";
    case ErrKind::UrlDivergenceEntryRefused:
      return "UrlDivergenceEntryRefused";
```

```cpp
// src/core/report/envelope.cpp exit_for_error — UrlDivergenceRefused joins the
// `return 3` refusal group; UrlDivergenceEntryRefused joins the `return 2` group:
    case ErrKind::ContainmentRefused:
    ...
    case ErrKind::AgentNotValidatedFailed:
    case ErrKind::UrlDivergenceEntryRefused:
      return 2;
    ...
    case ErrKind::OpenPartialPresent:
    case ErrKind::UrlDivergenceRefused:
      return 3;
```

```cpp
// src/core/support/url_divergence.hpp (new):
#pragma once
#include <string>
namespace biv {
struct UrlDivergenceEntryRefusal {
  std::string repo_id;
  std::string relpath;
  std::string requested;
  std::string effective;
  std::string op;
};
struct UrlDivergenceAcceptedEntry {
  std::string requested;
  std::string effective;
  std::string op;
  std::string repo;
};
}  // namespace biv
```

```cpp
// src/core/open/open.hpp — OpenReport gains (after checksums_verified/manifest_format_version):
  std::vector<biv::UrlDivergenceEntryRefusal> url_divergence_refusals{};
  std::vector<biv::UrlDivergenceAcceptedEntry> url_divergence_accepted{};
// src/core/pack/pack.hpp — PackReport gains (after advisories):
  std::vector<biv::UrlDivergenceAcceptedEntry> url_divergence_accepted{};
// (include core/support/url_divergence.hpp in both headers)
```

```cpp
// src/core/report/envelope.cpp — writer changes:
// (1) a helper writing the grouped third advisory member, present <=> non-empty,
//     ONE outer object, entries rows in vector (encounter) order:
void write_url_divergence_accepted(json::Writer& writer,
                                   const std::vector<UrlDivergenceAcceptedEntry>& entries) {
  if (entries.empty()) {
    return;
  }
  writer.begin_object();
  writer.key("kind");
  writer.value_string("url-divergence-accepted");
  writer.key("entries");
  writer.begin_array();
  for (const auto& entry : entries) {
    writer.begin_object();
    writer.key("requested");
    writer.value_string(entry.requested);
    writer.key("effective");
    writer.value_string(entry.effective);
    writer.key("op");
    writer.value_string(entry.op);
    writer.key("repo");
    writer.value_string(entry.repo);
    writer.end_object();
  }
  writer.end_array();
  writer.end_object();
}
// (2) write_advisories emits it after the existing pack advisories loop (new
//     signature takes the accepted entries); the else-branch (non-pack verbs)
//     replaces its bare empty advisories array with:
    writer.key("advisories");
    writer.begin_array();
    if (open_report.has_value()) {
      write_url_divergence_accepted(writer, open_report->url_divergence_accepted);
    }
    writer.end_array();
// (3) write_open_result appends, present <=> non-empty, rows in vector order:
  if (!report.url_divergence_refusals.empty()) {
    writer.key("url_divergence_refusals");
    writer.begin_array();
    for (const auto& row : report.url_divergence_refusals) {
      writer.begin_object();
      writer.key("kind");
      writer.value_string("UrlDivergenceEntryRefused");
      writer.key("repo_id");
      writer.value_string(row.repo_id);
      writer.key("relpath");
      writer.value_string(row.relpath);
      writer.key("requested");
      writer.value_string(row.requested);
      writer.key("effective");
      writer.value_string(row.effective);
      writer.key("op");
      writer.value_string(row.op);
      writer.end_object();
    }
    writer.end_array();
  }
// (4) the typed aggregator (envelope.hpp declares; envelope.cpp defines):
int exit_for_open(const core_sessions::SessionsOutcome& outcome,
                  const std::vector<UrlDivergenceEntryRefusal>& refusals) noexcept {
  int exit_code = exit_for_sessions(outcome);
  for (const auto& row : refusals) {
    (void)row;
    exit_code = std::max(exit_code, exit_for_error(ErrKind::UrlDivergenceEntryRefused));
  }
  return exit_code;
}
```

```cpp
// src/cli/main.cpp:363 — the ONE exit source widens (A6-R1's formula verbatim):
        const int exit_code =
            biv::report::exit_for_open(*sessions, report->url_divergence_refusals);
```

```json
// schemas/biv-exit-map.v1.json — append after the UsageError row (A6-R1 rows verbatim):
    {"kind": "UrlDivergenceRefused",      "class": "refusal",    "exit": 3},
    {"kind": "UrlDivergenceEntryRefused", "class": "divergence", "exit": 2}
```

Match the file's existing row formatting exactly (the parity test string-matches `"kind": "..."` / `"class": "..."` / `"exit": N`).

```json
// schemas/biv-json-envelope.v1.schema.json — three sites:
// (i) advisories items.oneOf gains the third branch:
   {
    "type": "object",
    "required": ["kind", "entries"],
    "properties": {
     "kind": {"const": "url-divergence-accepted"},
     "entries": {
      "type": "array",
      "minItems": 1,
      "items": {
       "type": "object",
       "required": ["requested", "effective", "op", "repo"],
       "properties": {
        "requested": {"type": "string"},
        "effective": {"type": "string"},
        "op": {"type": "string"},
        "repo": {"type": "string"}
       }
      }
     }
    }
   }
// (ii) error.facts.properties gains:
      "requested": {"type": "string"},
      "effective": {"type": "string"},
      "op": {"type": "string"}
// (iii) the result object branch's properties gain:
      "url_divergence_refusals": {
       "type": "array",
       "minItems": 1,
       "items": {
        "type": "object",
        "required": ["kind", "repo_id", "relpath", "requested", "effective", "op"],
        "properties": {
         "kind": {"const": "UrlDivergenceEntryRefused"},
         "repo_id": {"type": "string"},
         "relpath": {"type": "string"},
         "requested": {"type": "string"},
         "effective": {"type": "string"},
         "op": {"type": "string"}
        }
       }
      }
```

```python
# harness/selftest/test_envelope.py — recompute BOTH pins FROM THE LANDED BYTES
# (run _git_blob_id over the edited files; paste the two hex values):
CURRENT_LOCKED_SCHEMA_BLOBS = {
    "schemas/biv-json-envelope.v1.schema.json": "<recomputed sha1>",
    "schemas/biv-exit-map.v1.json": "<recomputed sha1>",
}
```

- [ ] **Step 4: run, verify PASS** — `biv_tests` envelope suite (parity + carriers + aggregator) and `pytest harness/selftest/test_envelope.py` (pins + a6·17 + the existing scenario validations, which are the zero-state half of a6·16 now running against the widened schema).
- [ ] **Step 5: commit (the one-commit contract landing)** — `git add src/core/support/error.hpp src/core/support/error.cpp src/core/support/url_divergence.hpp src/core/open/open.hpp src/core/pack/pack.hpp src/core/report/envelope.hpp src/core/report/envelope.cpp src/cli/main.cpp schemas/biv-exit-map.v1.json schemas/biv-json-envelope.v1.schema.json tests/test_envelope.cpp harness/selftest/test_envelope.py && git commit -m "feat(contract): the two url-divergence ErrKinds land WITH both exit-map rows, all three envelope-schema sites, carrier structs/serialization, the widened open-exit aggregator, derived parity rows, and both recomputed selftest pins (sealed A6-R1; V-A6-3 one-commit rule)"`

### Task 3: E2 zero-state legs at verb scope (a6·15)

**Files:** Modify `tests/test_cli.cpp`.

- [ ] **Step 1: failing test** (fails only if Task 2 mis-emits; expected to pass immediately — it is the a6·15 landing instrument, keep it even when green on first run):

```cpp
TEST_CASE("a6.15 zero state: no divergence -> both carriers absent") {
  const auto root = make_tmp("a6-15-zero");
  // any existing green pack fixture dir helper; --json envelope on pack:
  write_min_packable_tree(root / "src");  // use the suite's existing minimal-tree helper
  const auto pack = run_cmd("pack src --json", root);
  CHECK(pack.out.find("url-divergence-accepted") == std::string::npos);
  CHECK(pack.out.find("url_divergence_refusals") == std::string::npos);
  // open the produced image with consent no; assert the open envelope's zero state:
  const auto open = run_cmd("open <produced-image> --consent no --json --dest out", root);
  CHECK(open.out.find("url-divergence-accepted") == std::string::npos);
  CHECK(open.out.find("url_divergence_refusals") == std::string::npos);
  std::filesystem::remove_all(root);
}
```

(Adapt the two helper calls to the suite's existing pack/open fixture helpers — reuse, don't invent; the assertion set is the leg.)

- [ ] **Step 2: run, verify PASS both assertions on real verb envelopes.**
- [ ] **Step 3: commit** — `git add tests/test_cli.cpp && git commit -m "test: a6.15 zero-state landing leg — both url-divergence carriers absent on divergence-free pack/open envelopes"`

### Task 4: the PROMPT D renderer module (BLOCKED on STOP-1)

**GATE:** do not start until the pair Planner cites m-3's answer relay for STOP-1 (the two golden-byte cells: (a) PROMPT D's terminal bytes after `[y/N]` — trailing space per PROMPT B's convention vs the fenced block's bare line; (b) whether the fenced templates' two-space leading indent is part of the golden bytes on BOTH carriers of the pack-refusal template (`error.detail` + stream) or is stream-rendering only). The template literals below carry `<STOP-1>` markers at the two undetermined cells; everything else is sealed-verbatim.

**Files:** Create `src/cli/url_consent.hpp`, `src/cli/url_consent.cpp`; modify `tests/test_cli.cpp` (unit tests); add `url_consent.cpp` to the existing source lists in CMake.

**Interfaces — Produces (2b's wiring consumes all of these):**
- `biv::cli::UrlDivergenceFacts { std::string op, repo, requested, effective; }` (M-R3's four hook inputs, plain strings — NO engine header).
- `bool interactive_url_hook_installable()` — A7-R1: `::isatty(STDIN_FILENO) != 0 && ::isatty(STDERR_FILENO) != 0`; no json term, no env/config term.
- `std::string render_prompt_d(const UrlDivergenceFacts&)`
- `std::string render_accepted_notice(const UrlDivergenceFacts&)`
- `std::string render_pack_refusal_detail(const UrlDivergenceFacts&)`
- `std::string render_entry_refusal_line(std::string_view relpath, const UrlDivergenceFacts&)`
- `std::string render_run_guidance_line(std::size_t refused_count)`
- `bool prompt_url_divergence(const UrlDivergenceFacts&, std::istream& in, std::ostream& err)` — renders PROMPT D on `err`, reads one answer from `in`, returns true iff `y`/`Y`; EMPTY ANSWER REFUSES (default N, a6·1); stream failure refuses.

- [ ] **Step 1: failing byte-equality tests** — each template asserted BYTE-WHOLE against the sealed text (with STOP-1 cells resolved), e.g.:

```cpp
TEST_CASE("A6-R2 PROMPT D bytes are golden") {
  const biv::cli::UrlDivergenceFacts facts{"fetch", "/w/repo", "https://req", "https://eff"};
  CHECK(biv::cli::render_prompt_d(facts) ==
        "  fetch: the address git will contact for /w/repo differs from the requested address:\n"
        "    requested: https://req\n"
        "    effective: https://eff\n"
        "  Contact the effective address? [y/N]<STOP-1a>");
}
TEST_CASE("A6-R4 accepted notice bytes are golden") {
  const biv::cli::UrlDivergenceFacts facts{"fetch", "/w/repo", "https://req", "https://eff"};
  CHECK(biv::cli::render_accepted_notice(facts) ==
        "  fetch: contacting https://eff for /w/repo (requested: https://req — accepted for this run)\n");
}
TEST_CASE("A6-R4 refusal + guidance bytes are golden") {
  const biv::cli::UrlDivergenceFacts facts{"fetch", "/w/repo", "https://req", "https://eff"};
  CHECK(biv::cli::render_pack_refusal_detail(facts) ==
        "<STOP-1b>pack refused: fetch for /w/repo would contact https://eff instead of the requested https://req; approval was not given. Re-run interactively to review, or pass --accept-url-divergence to proceed.");
  CHECK(biv::cli::render_entry_refusal_line("a/b.txt", facts) ==
        "  a/b.txt: restore failed — fetch would contact https://eff instead of the requested https://req; approval was not given.\n");
  CHECK(biv::cli::render_run_guidance_line(2) ==
        "  open: 2 restore entry(ies) refused — the effective address was not approved. Re-run interactively to review, or pass --accept-url-divergence to proceed.\n");
}
TEST_CASE("A6-R2 default N: empty answer refuses; y proceeds") {
  const biv::cli::UrlDivergenceFacts facts{"fetch", "/r", "https://q", "https://e"};
  { std::istringstream in{"\n"}; std::ostringstream err;
    CHECK_FALSE(biv::cli::prompt_url_divergence(facts, in, err)); }
  { std::istringstream in{"y\n"}; std::ostringstream err;
    CHECK(biv::cli::prompt_url_divergence(facts, in, err)); }
  { std::istringstream in{"n\n"}; std::ostringstream err;
    CHECK_FALSE(biv::cli::prompt_url_divergence(facts, in, err)); }
}
```

Addresses render VERBATIM — no elision, truncation, or normalization anywhere in the module (A6-R2). These are unit tests of the module's bytes; they claim NO FX-A6 behavioral leg (those need verb-reachable divergence, due 2b).

- [ ] **Step 2: run, verify FAIL (module absent).**
- [ ] **Step 3: implement the module** — template literals exactly as the tests assert (STOP-1 cells per m-3's answer); the predicate; the prompt function reading one line, `y`/`Y` → true, anything else (including empty/EOF/stream-fail) → false. No file, env, or config read/write anywhere in the module (V-A6-1, A7-R1).
- [ ] **Step 4: run, verify PASS.**
- [ ] **Step 5: commit** — `git add src/cli/url_consent.hpp src/cli/url_consent.cpp tests/test_cli.cpp <cmake file if touched> && git commit -m "feat(cli): PROMPT D renderer module — sealed A6-R2/R4 golden bytes (STOP-1 cells per m-3 <answer relay id>), A7-R1 stdin+stderr predicate, default-N prompt; consumer is sub-step 2b's wiring (V-A6-6)"`

### Task 5: fence proofs + verification battery + IMPL report

- [ ] **Step 1: fence greps (all must hold; paste outputs into the IMPL report):**

```bash
# zero engine references from product code (definitions + tests excepted):
git grep -n 'run_eligibility\|restore_entry\|repo::capture' -- 'src' ':!src/core/repo' ; test $? -eq 1
git grep -n '#include "core/repo' -- 'src' ':!src/core/repo' ; test $? -eq 1
# repos fence intact:
grep -n 'require_empty_array' src/core/manifest/manifest.cpp
# no persistence tokens in the new module (env/config/file APIs absent):
grep -nE 'getenv|setenv|ofstream|fopen|config' src/cli/url_consent.cpp ; test $? -eq 1
# engine bytes untouched:
git diff --stat 02b51435..HEAD -- src/core/repo | wc -l   # must be 0
```

- [ ] **Step 2: full local suite** — configure + build + `ctest` on macOS (both test binaries; note R-3.37: the macOS allowlist is deny-by-default — these tests live in EXISTING binaries; verify the new cases actually RAN by name in the ctest/Catch2 output, not just that the suite is green).
- [ ] **Step 3: Linux parity leg** — Docker `ubuntu-24.04 --platform linux/amd64 --init` (R-4.40), raise `nofile` soft→hard inside the runuser context before the suite (R-4.31(a)), reproduce the s2-harness recipe; count-gate posture: R-4.38's pre-existing red stands disclosed and is NOT citable as merge-readiness (its repair is m-3's parallel gate).
- [ ] **Step 4: IMPL report** (file-first relay): claims with evidence levels; `ACTIONS_GIT_REF` branch@sha; the leg census (a6·14/15/17/18 + zero-half 16 — where each ran and its counts); the fence-grep outputs; the STOP-1 answer relay cited; explicit NOT-DONE list (all behavioral legs due 2b; no wiring; no merge claim).

## Acceptance criteria (the plan is met when ALL hold)

1. Branch `intg/consent-fabric` over base `02b51435`, commits exactly as tasked, every commit green.
2. The resulting `biv open --help` byte-equals the a6·18 golden (new line directly after `--consent`; `--agent-bin` line preserved); `pack`/`list`/`info` still print no help.
3. `--accept-url-divergence` parses on `pack` and `open` (state on `Command`); `list`/`info` inert observable pinned; no other new argv surface exists.
4. Both ErrKinds + exit rows + all three schema sites + parity rows + BOTH recomputed pins landed in ONE commit; `pytest harness/selftest/test_envelope.py` green including the three a6·17 structural tests.
5. Zero-state absence proven at unit AND verb scope (a6·15; zero-half of a6·16 via the selftest validation over real envelopes).
6. The renderer module's bytes are sealed-verbatim (STOP-1 answer cited); default-N proven; predicate is exactly stdin+stderr TTY.
7. Every fence grep in Task 5 holds; engine diff from base is empty; the R-4.47 S3/V3-shadow constraints hold on every new text/predicate byte.
8. No claim of any 2b-due leg anywhere in the report.

## Out of scope (hard)

Engine wiring or any product→engine call/include; hook installation into engine runs; the format act (repos cell, N); `list`/`info` implementation (R-6.2); any unlanded design-table flag; PROMPT A/B/C or `build_preview`/`render_prompt_b` (R-4.24); summary-line or warning-row emission for this feature (SUPPRESS is the cut, A6-R7(2)); persistence of anything; FX-A6 behavioral legs a6·1–13 + divergence half of a6·16; all FX-A7 legs; any PTY-helper change (RECONCILE I5); merge/push/publication/release.

## Operator/upstream questions

STOP-1 (filed by the pair Planner to master → m-3): the two golden-byte cells named in Task 4's gate. Nothing else is open; every other byte is determined by the sealed texts.
