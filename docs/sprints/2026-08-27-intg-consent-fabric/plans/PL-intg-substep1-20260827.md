# intg sub-step 1 — A6 consent-UX fabric (engine unwired) Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:executing-plans (the executor is the addressed `intg.pair-implementer`; implementation starts ONLY on the pair Planner's bare dispatch token after PLAN-REVIEW approve). Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Land the SEALED Addendum-6 rev14 consumer fabric — the `--accept-url-divergence` flag, help closure, the two url-divergence ErrKinds with their exit rows, the three envelope-contract sites, the carrier structs/serialization, the widened open-exit aggregator, and the PROMPT D renderer module — on branch `intg/consent-fabric`, with the engine fully unwired and only the spine-assigned landing legs claimed.

**Architecture:** All bytes are CLI/report/contract-layer; ZERO engine bytes and ZERO product references into `src/core/repo/`. The renderer + A7-R1 predicate land as a self-contained `src/cli/url_consent` module whose only consumer today is its unit tests — its declared production consumer is sub-step 2b's wiring act (V-A6-6 makes that consumer mandatory-at-wiring). Carriers ride `OpenReport`/`PackReport` as plain-string structs in `src/core/support/` so no layering or engine include is introduced.

**Tech Stack:** C++23, Catch2 (`tests/`), pytest selftest (`harness/selftest/`), JSON Schema Draft 2020-12.

**Spec:** SEALED m-3 Addendum-6 rev14 — pdc `master/domains/m-3-restore-cli/design/2026-08-24-addendum-6-url-consent-consumer-surface.md`, lock `m3-addendum-6-c41d015f-lock-20260825` (locked pin `c41d015f…`, post-stamp `7ce2251d…`); SEALED m-3 Addendum-7 rev2 — `.../2026-08-26-addendum-7-consent-interaction-companion.md`, lock `m3-addendum-7-4c40fe37-lock-20260827` (locked pin `4c40fe37…`, post-stamp `e4a6b982…`). Read-only context: LOCKED M rev8 (M-R3 hook contract). Bars: R-4.47 (S1–S4/V1–V5/E1–E5, OBLIGATIONS §B2); RECONCILE §R1 constraints I2–I6.

## Global Constraints

- Base and branch: `git worktree add ../bivpak-intg-consent-fabric -b intg/consent-fabric 02b51435` — product work happens ONLY in that worktree (the primary worktree hosts the relay daemon and other seats; never switch its branch). No rebase without a routed STOP.
- SEALED TEXT ONLY: where A6/A7 determine, execute byte-exactly; anything they defer or are silent on is a STOP up the pair line — never a keyboard call (A6-R7, A7-R5).
- Golden-byte fence (V-A6-2): every user-facing template byte comes verbatim from A6-R2/R4, with the two once-open STOP-1 cells resolved by the owner's ruling (m-3 `235912`, carried `000750`) and folded into Task 4's literals; no other byte cell is open.
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

## Boundary contract (protocol form; carried from the reconciled audits)

```text
Writes: static CLI/report/schema fabric ONLY — src/cli/ (flag, help, url_consent module),
        src/core/support/ (ErrKinds, carrier structs), src/core/report/ (writer, exit
        rows, aggregator), src/core/open/open.hpp + src/core/pack/pack.hpp (carrier
        fields), schemas/biv-json-envelope.v1.schema.json + schemas/biv-exit-map.v1.json,
        tests/, harness/selftest/, root CMakeLists.txt (source lists only) — on branch
        intg/consent-fabric; engine bytes and product engine call sites are ZERO.
Reads: SEALED A6 rev14 (m3-addendum-6-c41d015f-lock-20260825); SEALED A7 rev2
       (m3-addendum-7-4c40fe37-lock-20260827); LOCKED M rev8 as the READ-ONLY hook
       contract (M-R3); the R-4.47 bar (S1-S4/V1-V5/E1-E5).
Target entity: the biv CLI consent-UX surface plus BOTH published schema artifacts
       (biv-json-envelope.v1, biv-exit-map.v1) with their pinned selftest blobs.
Downstream consumer: sub-step 2b's verb-to-engine wiring (installs the hook, populates
       the carriers) and its full A6/A7 behavioral E2 suite; m-3's byte review at every
       landing.
Contract: two ErrKinds (UrlDivergenceRefused refusal/3; UrlDivergenceEntryRefused
       divergence/2); two refusal grains never crossing (V-A6-5); ONE grouped
       url-divergence-accepted advisory member on BOTH verbs; exact golden render bytes
       (STOP-1 cells RESOLVED per m-3 235912); the A7-R1 stdin+stderr predicate with no json term;
       the same-commit published-contract topology (V-A6-3); no persistence; no wiring.
Proof: the landing legs at THIS act (a6.14, a6.15, a6.17, a6.18, zero-state half of
       a6.16, E2/unit as tasked); the writer-reader round-trip and every behavioral leg
       prove at 2b where the consumer lands.
No-consumer action: reject any static byte with no declared 2b consumer, and reject any
       attempt to create that consumer early (the wiring fence).
```

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
Modify: tests/test_cli.cpp          (help golden; a6·14 regression; a6·18 no-help arms; parser tests; Task-4 unit tests — include ONLY src/cli/url_consent.hpp)
Modify: tests/test_envelope.cpp     (two derived parity rows; row-bound carrier/aggregator unit tests)
Modify: harness/selftest/test_envelope.py (both blob pins recomputed; a6·17 structural tests; zero-state validation)
Modify: CMakeLists.txt              (line 97: add src/cli/url_consent.cpp to the biv executable; one new target_sources(biv_tests PRIVATE src/cli/url_consent.cpp) line in the existing biv_tests block at :137-158 — no new target, no new test binary)
```

Run-command convention for every task (literal, per the reviewed tree): configure/build with `cmake --build build/dev --target biv_tests biv`, then invoke the test binary directly with Catch2 name filters, e.g. `./build/dev/biv_tests "a6.18 inherited no-help boundary witnessed on pack/list/info"`. (`ctest --test-dir build/dev -R cli` selects ZERO tests on this tree — never use `-R cli`.) The selftest runs as `python3 -m pytest harness/selftest/test_envelope.py -q`.

---

### Task 1: flag parsing + help closure (a6·18 home, a6·14 regression)

**Files:** Modify `src/cli/args.hpp:17-25`, `src/cli/args.cpp` (pack loop `:168-176`, open loop `:193-255`, `help_text` `:130-147`), `tests/test_cli.cpp` (help golden `:1425-1440` + new cases).

**Interfaces — Produces:** `biv::cli::Command::accept_url_divergence` (`bool`, default `false`), set by `--accept-url-divergence` on `pack` and `open`. Its ONLY production consumer is sub-step 2b's wiring (which passes it into the hook installation); nothing in this plan reads it after parse.

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

TEST_CASE("a6.14 list/info accept the flag inert: full-stream equality with flagless") {
  const auto root = make_tmp("a6-14-inert");
  // FULL code/out/err equality for EACH verb — a mutant emitting any A6 surface on any
  // stream, or shifting the exit, REDs here (flag-specific: only this spelling compared).
  const auto list_flag = run_cmd("list --accept-url-divergence missing.bvpk", root);
  const auto list_none = run_cmd("list missing.bvpk", root);
  CHECK(list_flag.code == list_none.code);
  CHECK(list_flag.out == list_none.out);
  CHECK(list_flag.err == list_none.err);
  const auto info_flag = run_cmd("info --accept-url-divergence missing.bvpk", root);
  const auto info_none = run_cmd("info missing.bvpk", root);
  CHECK(info_flag.code == info_none.code);
  CHECK(info_flag.out == info_none.out);
  CHECK(info_flag.err == info_none.err);
  std::filesystem::remove_all(root);
}

TEST_CASE("a6.18 inherited no-help boundary witnessed on pack/list/info") {
  const auto root = make_tmp("a6-18-nohelp");
  // The sealed leg requires the OTHER verbs' help ABSENCE witnessed, not assumed.
  // The witness is help-is-not-special FULL-STREAM equality: for each verb, `--help`
  // must produce EXACTLY what any other unknown/ignored flag produces (code, stdout,
  // stderr) — a mutant emitting ANY help production on ANY stream for that verb
  // diverges from its own unknown-flag baseline and REDs here. Belt: no usage/help
  // text on either stream.
  const std::vector<std::pair<std::string, std::string>> probes{
      {"pack --help", "pack --no-such-flag"},          // pack rejects every flag alike
      {"list --help x.bvpk", "list --no-such-flag x.bvpk"},  // stubs ignore trailing tokens alike
      {"info --help x.bvpk", "info --no-such-flag x.bvpk"}};
  for (const auto& [help_form, baseline_form] : probes) {
    const auto help = run_cmd(help_form, root);
    const auto baseline = run_cmd(baseline_form, root);
    INFO(help_form);
    CHECK(help.code == baseline.code);
    CHECK(help.out == baseline.out);
    CHECK(help.err == baseline.err);
    CHECK(help.out.find("usage:") == std::string::npos);
    CHECK(help.err.find("usage:") == std::string::npos);
    CHECK(help.out.find("--accept-url-divergence") == std::string::npos);
    CHECK(help.err.find("--accept-url-divergence") == std::string::npos);
  }
  std::filesystem::remove_all(root);
}
```

(The a6·14 case pins the FLAG spelling's inert observable only — it must not assert acceptance of arbitrary trailing tokens; the stub path is not this feature's contract. RECONCILE I2.)

- [ ] **Step 2: run, verify FAIL** — `cmake --build build/dev --target biv_tests biv && ./build/dev/biv_tests "Task 4 CLI help documents the strict agent binary pin syntax,a6-R3 pack and open accept --accept-url-divergence,a6.14 list/info accept the flag inert: full-stream equality with flagless,a6.18 inherited no-help boundary witnessed on pack/list/info"` — the help golden fails on the missing line; the parser cases fail on `unknown-flag`.
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

- [ ] **Step 4: run, verify PASS** — the same literal build + filtered `./build/dev/biv_tests` invocation as Step 2; all four named cases green (help golden byte-whole; parser cases; a6·14 full-stream equality; a6·18 no-help arms).
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

// Row-bound helpers for the two carriers (simdjson dom, the file's existing
// instrument — see the parser use at tests/test_envelope.cpp:115). Every value in
// every row is DISTINCT so a field omission, swap, or cross-row bleed cannot be
// satisfied by another row's identical value.
namespace {
void check_refusal_row(const simdjson::dom::element row,
                       const std::string& repo_id, const std::string& relpath,
                       const std::string& requested, const std::string& effective,
                       const std::string& op) {
  CHECK(std::string_view{row["kind"]} == "UrlDivergenceEntryRefused");
  CHECK(std::string_view{row["repo_id"]} == repo_id);
  CHECK(std::string_view{row["relpath"]} == relpath);
  CHECK(std::string_view{row["requested"]} == requested);
  CHECK(std::string_view{row["effective"]} == effective);
  CHECK(std::string_view{row["op"]} == op);
  CHECK(simdjson::dom::object(row).size() == 6);  // exact row shape, no extra members
}
void check_accepted_entry(const simdjson::dom::element entry,
                          const std::string& requested, const std::string& effective,
                          const std::string& op, const std::string& repo) {
  CHECK(std::string_view{entry["requested"]} == requested);
  CHECK(std::string_view{entry["effective"]} == effective);
  CHECK(std::string_view{entry["op"]} == op);
  CHECK(std::string_view{entry["repo"]} == repo);
  CHECK(simdjson::dom::object(entry).size() == 4);
}
// Returns the single url-divergence-accepted advisory object, asserting exactly one
// exists among the advisories and returning its entries array.
simdjson::dom::array single_accepted_entries(const simdjson::dom::element document) {
  size_t accepted_count = 0;
  simdjson::dom::array entries;
  for (const auto advisory : simdjson::dom::array(document["advisories"])) {
    if (std::string_view{advisory["kind"]} == "url-divergence-accepted") {
      ++accepted_count;
      entries = simdjson::dom::array(advisory["entries"]);
    }
  }
  REQUIRE(accepted_count == 1);  // ONE grouped outer object, never one-per-triple
  return entries;
}
}  // namespace

TEST_CASE("a6-R1 open carriers: exact rows, order, cardinality, grouped advisory, zero state") {
  biv::open::OpenReport report{.image_path = "img.bvpk", .output_dir = "out"};
  // zero state (a6.15 unit half): both carriers ABSENT on the open branch
  const auto zero = biv::report::envelope("open", std::nullopt, report, std::nullopt, 0);
  CHECK(zero.find("url_divergence_refusals") == std::string::npos);
  CHECK(zero.find("url-divergence-accepted") == std::string::npos);
  // populated — DISTINCT values everywhere:
  report.url_divergence_refusals = {
      {"repoA", "path/one", "https://req-1", "https://eff-1", "fetch"},
      {"repoB", "path/two", "https://req-2", "https://eff-2", "ls-remote"}};
  report.url_divergence_accepted = {{"https://acc-req", "https://acc-eff", "clone", "/hook/acc"}};
  const auto populated = biv::report::envelope("open", std::nullopt, report, std::nullopt, 2);
  simdjson::dom::parser parser;
  const simdjson::dom::element document = parser.parse(populated);
  const simdjson::dom::array rows{document["result"]["url_divergence_refusals"]};
  REQUIRE(rows.size() == 2);  // exact cardinality
  check_refusal_row(rows.at(0), "repoA", "path/one", "https://req-1", "https://eff-1", "fetch");
  check_refusal_row(rows.at(1), "repoB", "path/two", "https://req-2", "https://eff-2", "ls-remote");
  const auto entries = single_accepted_entries(document);
  REQUIRE(entries.size() == 1);
  check_accepted_entry(entries.at(0), "https://acc-req", "https://acc-eff", "clone", "/hook/acc");
}

TEST_CASE("a6-R1 pack carries the grouped advisory too: exact entries, order, zero state") {
  biv::pack::PackReport report{.image_path = "img.bvpk", .source_path = "src"};
  const auto zero = biv::report::envelope("pack", report, std::nullopt, std::nullopt, 0);
  CHECK(zero.find("url-divergence-accepted") == std::string::npos);
  CHECK(zero.find("url_divergence_refusals") == std::string::npos);
  // two entries, EVERY field distinct per entry, encounter order:
  report.url_divergence_accepted = {
      {"https://p1-req", "https://p1-eff", "ls-remote", "/pack/one"},
      {"https://p2-req", "https://p2-eff", "fetch", "/pack/two"}};
  const auto populated = biv::report::envelope("pack", report, std::nullopt, std::nullopt, 0);
  simdjson::dom::parser parser;
  const simdjson::dom::element document = parser.parse(populated);
  const auto entries = single_accepted_entries(document);
  REQUIRE(entries.size() == 2);
  check_accepted_entry(entries.at(0), "https://p1-req", "https://p1-eff", "ls-remote", "/pack/one");
  check_accepted_entry(entries.at(1), "https://p2-req", "https://p2-eff", "fetch", "/pack/two");
}

TEST_CASE("a6-R1 site 1: the preflight grain rides the top-level error carrier") {
  // kind/path/facts asserted; the A6-R4 detail BYTES are Task-4/STOP-1-gated and are
  // deliberately NOT asserted here (this unit proves the carrier, not the template):
  biv::BivError error{.kind = biv::ErrKind::UrlDivergenceRefused,
                      .path = "/hook/repo",
                      .detail = "placeholder-until-task-4",
                      .facts = {{"requested", "https://req"},
                                {"effective", "https://eff"},
                                {"op", "ls-remote"}}};
  const auto envelope = biv::report::envelope("pack", std::nullopt, std::nullopt, error, 3);
  CHECK(envelope.find("\"kind\": \"UrlDivergenceRefused\"") != std::string::npos);
  CHECK(envelope.find("\"path\": \"/hook/repo\"") != std::string::npos);
  CHECK(envelope.find("\"requested\": \"https://req\"") != std::string::npos);
  CHECK(envelope.find("\"effective\": \"https://eff\"") != std::string::npos);
  CHECK(envelope.find("\"op\": \"ls-remote\"") != std::string::npos);
  CHECK(envelope.find("\"exit_code\": 3") != std::string::npos);
  CHECK(envelope.find("\"result\": null") != std::string::npos);
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

- [ ] **Step 4: run, verify PASS** — `cmake --build build/dev --target biv_tests biv && ./build/dev/biv_tests "[envelope]" "schema artifacts reserve envelope and exit-map contracts,a6-R1 open carriers: exact rows, order, cardinality, grouped advisory, zero state,a6-R1 pack carries the grouped advisory too: exact entries, order, zero state,a6-R1 site 1: the preflight grain rides the top-level error carrier,a6-R1 exit composition: one typed aggregator over both sources"` (Catch2 name filters; drop "[envelope]" if no such tag exists on this tree — the comma-joined name list is the operative filter) and `python3 -m pytest harness/selftest/test_envelope.py -q` (pins + a6·17 + the existing scenario validations, the zero-state half of a6·16 now running against the widened schema).
- [ ] **Step 5: commit (the one-commit contract landing)** — `git add src/core/support/error.hpp src/core/support/error.cpp src/core/support/url_divergence.hpp src/core/open/open.hpp src/core/pack/pack.hpp src/core/report/envelope.hpp src/core/report/envelope.cpp src/cli/main.cpp schemas/biv-exit-map.v1.json schemas/biv-json-envelope.v1.schema.json tests/test_envelope.cpp harness/selftest/test_envelope.py && git commit -m "feat(contract): the two url-divergence ErrKinds land WITH both exit-map rows, all three envelope-schema sites, carrier structs/serialization, the widened open-exit aggregator, derived parity rows, and both recomputed selftest pins (sealed A6-R1; V-A6-3 one-commit rule)"`

### Task 3: E2 zero-state legs at verb scope (a6·15)

**Files:** Modify `tests/test_cli.cpp`.

- [ ] **Step 1: failing test** (fails only if Task 2 mis-emits; expected to pass immediately — it is the a6·15 landing instrument, keep it even when green on first run):

```cpp
TEST_CASE("a6.15 zero state: no divergence -> both carriers absent on real verb envelopes") {
  // the exact fixture sequence of "CLI pack/open round-trip emits JSON envelopes"
  // (tests/test_cli.cpp:891-916), reused verbatim:
  const auto root = make_tmp("a6-15-zero");
  const auto source = root / "sample";
  std::filesystem::create_directories(source / "dir");
  write_file(source / "a.txt", "alpha");
  write_file(source / "dir" / "b.txt", "beta");

  const auto packed = run_cmd("pack '" + source.string() + "' --json", root);
  REQUIRE(packed.code == 0);
  REQUIRE(std::filesystem::exists(root / "sample.bvpk"));
  CHECK(packed.out.find("url-divergence-accepted") == std::string::npos);
  CHECK(packed.out.find("url_divergence_refusals") == std::string::npos);
  CHECK(packed.out.find("UrlDivergence") == std::string::npos);

  const auto opened = run_cmd("open '" + (root / "sample.bvpk").string() + "' --dest '" +
                                  (root / "restore").string() + "' --json",
                              root);
  REQUIRE(opened.code == 0);
  CHECK(opened.out.find("url-divergence-accepted") == std::string::npos);
  CHECK(opened.out.find("url_divergence_refusals") == std::string::npos);
  CHECK(opened.out.find("UrlDivergence") == std::string::npos);
  std::filesystem::remove_all(root);
}
```

- [ ] **Step 2: run, verify PASS** — `cmake --build build/dev --target biv_tests biv && ./build/dev/biv_tests "a6.15 zero state: no divergence -> both carriers absent on real verb envelopes"`.
- [ ] **Step 3: commit** — `git add tests/test_cli.cpp && git commit -m "test: a6.15 zero-state landing leg — both url-divergence carriers absent on divergence-free pack/open envelopes"`

### Task 4: the PROMPT D renderer module (STOP-1 ANSWERED — un-blocked)

**GATE DISCHARGED:** STOP-1 is answered by the owner — m-3's ruling `intg-stop1-a6-golden-bytes/DESIGN-planner-20260827-235912.md` (pdc), carried down at master's `intg-substep1-master-answers/PLAN-master-planner-20260828-000750.md`; both cells are byte-level READINGS of the sealed text, no addendum. The resolved bytes, folded below: **(STOP-1a)** PROMPT D's golden final line is `  Contact the effective address? [y/N] ` — terminal bytes ONE SPACE then NOTHING (no newline), cursor stays on the line, answer read from stdin on the same line; the block keeps its two-space base indent and the nested `requested:`/`effective:` lines their four-space depth. **(STOP-1b)** the pack-refusal TEMPLATE's golden bytes begin at `pack refused:` — NO leading indent; `error.detail` carries EXACTLY the template bytes; the stream carries the template EMBEDDED by the standard typed-error machinery (`biv: <kind>: <detail>\n`, `src/cli/main.cpp:30-42`) — no separate stream renderer exists for it; a6·7's byte-identity ranges over the TEMPLATE bytes on both carriers. The single-carrier blocks (PROMPT D, per-entry refusal line, run-level guidance line) are golden AS WRITTEN including their leading indents.

**Files:** Create `src/cli/url_consent.hpp`, `src/cli/url_consent.cpp`; modify `tests/test_cli.cpp` (unit tests; include ONLY the header — `tests/test_cli.cpp:34` already compiles `../src/cli/args.cpp` by source-include, so do not source-include a second TU); modify root `CMakeLists.txt` UNCONDITIONALLY: line 97 becomes `add_executable(biv src/cli/main.cpp src/cli/args.cpp src/cli/url_consent.cpp)` and one new line `target_sources(biv_tests PRIVATE src/cli/url_consent.cpp)` joins the existing `target_sources(biv_tests …)` block.

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
        "  Contact the effective address? [y/N] ");  // STOP-1a: trailing space, NO newline (m-3 235912)
}
TEST_CASE("A6-R4 accepted notice bytes are golden") {
  const biv::cli::UrlDivergenceFacts facts{"fetch", "/w/repo", "https://req", "https://eff"};
  CHECK(biv::cli::render_accepted_notice(facts) ==
        "  fetch: contacting https://eff for /w/repo (requested: https://req — accepted for this run)\n");
}
TEST_CASE("A6-R4 refusal + guidance bytes are golden") {
  const biv::cli::UrlDivergenceFacts facts{"fetch", "/w/repo", "https://req", "https://eff"};
  CHECK(biv::cli::render_pack_refusal_detail(facts) ==
        "pack refused: fetch for /w/repo would contact https://eff instead of the requested https://req; approval was not given. Re-run interactively to review, or pass --accept-url-divergence to proceed.");
  // STOP-1b (m-3 235912): the template begins at "pack refused:" — no leading indent;
  // this string IS error.detail exactly; the stream renders it via the standard
  // typed-error machinery ("biv: <kind>: <detail>\n") — no separate stream renderer.
  CHECK(biv::cli::render_entry_refusal_line("a/b.txt", facts) ==
        "  a/b.txt: restore failed — fetch would contact https://eff instead of the requested https://req; approval was not given.\n");
  CHECK(biv::cli::render_run_guidance_line(2) ==
        "  open: 2 restore entry(ies) refused — the effective address was not approved. Re-run interactively to review, or pass --accept-url-divergence to proceed.\n");
}
TEST_CASE("A6-R2 default N: empty answer refuses; y proceeds; wrapper renders byte-whole to err") {
  const biv::cli::UrlDivergenceFacts facts{"fetch", "/r", "https://q", "https://e"};
  // EVERY branch also binds the wrapper's stderr bytes byte-whole to the golden
  // render — a wrapper emitting nothing, drifted bytes, or extra bytes REDs here:
  const auto golden = biv::cli::render_prompt_d(facts);
  { std::istringstream in{"\n"}; std::ostringstream err;
    CHECK_FALSE(biv::cli::prompt_url_divergence(facts, in, err));   // empty -> refuse (a6.1 default)
    CHECK(err.str() == golden); }
  { std::istringstream in{"y\n"}; std::ostringstream err;
    CHECK(biv::cli::prompt_url_divergence(facts, in, err));
    CHECK(err.str() == golden); }
  { std::istringstream in{"Y\n"}; std::ostringstream err;
    CHECK(biv::cli::prompt_url_divergence(facts, in, err));         // uppercase Y proceeds
    CHECK(err.str() == golden); }
  { std::istringstream in{"n\n"}; std::ostringstream err;
    CHECK_FALSE(biv::cli::prompt_url_divergence(facts, in, err));
    CHECK(err.str() == golden); }
  { std::istringstream in{""}; std::ostringstream err;              // EOF -> refuse
    CHECK_FALSE(biv::cli::prompt_url_divergence(facts, in, err));
    CHECK(err.str() == golden); }
  { std::istringstream in{"y\n"}; std::ostringstream err;
    err.setstate(std::ios::failbit);                                // stream failure -> refuse
    CHECK_FALSE(biv::cli::prompt_url_divergence(facts, in, err)); }
}
```

Addresses render VERBATIM — no elision, truncation, or normalization anywhere in the module (A6-R2). These are unit tests of the module's bytes; they claim NO FX-A6 behavioral leg (those need verb-reachable divergence, due 2b).

- [ ] **Step 2: run, verify FAIL** — `cmake --build build/dev --target biv_tests` fails to link (module absent) or the filtered run `./build/dev/biv_tests "A6-R2 PROMPT D bytes are golden"` fails.
- [ ] **Step 3: implement the module** — template literals exactly as the tests assert (STOP-1 cells per m-3's answer); the predicate; the prompt function reading one line, `y`/`Y` → true, anything else (including empty/EOF/stream-fail) → false. No file, env, or config read/write anywhere in the module (V-A6-1, A7-R1).
- [ ] **Step 4: run, verify PASS** — `cmake --build build/dev --target biv_tests biv && ./build/dev/biv_tests "A6-R2 PROMPT D bytes are golden,A6-R4 accepted notice bytes are golden,A6-R4 refusal + guidance bytes are golden,A6-R2 default N: empty answer refuses; y proceeds; wrapper renders byte-whole to err"`.
- [ ] **Step 5: commit** — `git add src/cli/url_consent.hpp src/cli/url_consent.cpp tests/test_cli.cpp CMakeLists.txt && git commit -m "feat(cli): PROMPT D renderer module — sealed A6-R2/R4 golden bytes (STOP-1 cells per m-3 ruling intg-stop1-a6-golden-bytes/DESIGN-planner-20260827-235912.md), A7-R1 stdin+stderr predicate, default-N prompt; consumer is sub-step 2b's wiring (V-A6-6)"`

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
# the A7-R1 predicate is EXACTLY the stdin+stderr isatty pair, with no json/env/config
# term anywhere in the module (acceptance criterion 6's source proof):
grep -c 'isatty' src/cli/url_consent.cpp        # expect exactly 2 (STDIN_FILENO, STDERR_FILENO)
grep -n 'isatty(STDIN_FILENO)' src/cli/url_consent.cpp
grep -n 'isatty(STDERR_FILENO)' src/cli/url_consent.cpp
grep -nE 'STDOUT_FILENO|json' src/cli/url_consent.cpp ; test $? -eq 1
# engine bytes untouched:
git diff --stat 02b51435..HEAD -- src/core/repo | wc -l   # must be 0
```

- [ ] **Step 2: full local suite** — configure + build + `ctest` on macOS (both test binaries; note R-3.37: the macOS allowlist is deny-by-default — these tests live in EXISTING binaries; verify the new cases actually RAN by name in the ctest/Catch2 output, not just that the suite is green).
- [ ] **Step 3: Linux parity leg** — Docker `ubuntu-24.04 --platform linux/amd64 --init` (R-4.40), raise `nofile` soft→hard inside the runuser context before the suite (R-4.31(a)), reproduce the s2-harness recipe; count-gate posture: R-4.38's pre-existing red stands disclosed and is NOT citable as merge-readiness (its repair is m-3's parallel gate).
- [ ] **Step 4: IMPL report** (file-first relay): claims with evidence levels; `ACTIONS_GIT_REF` branch@sha; the leg census (a6·14/15/17/18 + zero-half 16 — where each ran and its counts); the fence-grep outputs; the STOP-1 answer relay cited; explicit NOT-DONE list (all behavioral legs due 2b; no wiring; no merge claim).

## Acceptance criteria (the plan is met when ALL hold)

1. Branch `intg/consent-fabric` over base `02b51435`, commits exactly as tasked, every commit green.
2. The resulting `biv open --help` byte-equals the a6·18 golden (new line directly after `--consent`; `--agent-bin` line preserved); the `pack`/`list`/`info` no-help boundary is WITNESSED by the executed a6·18 arm, not assumed.
3. `--accept-url-divergence` parses on `pack` and `open` (state on `Command`); `list`/`info` inertness pinned by FULL code/out/err equality against the flagless invocation for EACH verb; no other new argv surface exists.
4. Both ErrKinds + exit rows + all three schema sites + parity rows + BOTH recomputed pins landed in ONE commit; the writer units prove the grouped advisory on BOTH verbs (all fields, encounter order, one outer object), the complete refusal-row field set, the top-level `UrlDivergenceRefused` carrier (kind/path/facts; detail bytes Task-4-gated), and zero-state absence on both branches; `pytest harness/selftest/test_envelope.py` green including the three a6·17 structural tests.
5. Zero-state absence proven at unit AND verb scope (a6·15; zero-half of a6·16 via the selftest validation over real envelopes).
6. The renderer module's bytes are sealed-verbatim (STOP-1 answer cited); default-N proven; predicate is exactly stdin+stderr TTY.
7. Every fence grep in Task 5 holds; engine diff from base is empty; the R-4.47 S3/V3-shadow constraints hold on every new text/predicate byte.
8. No claim of any 2b-due leg anywhere in the report.

## Out of scope (hard)

Engine wiring or any product→engine call/include; hook installation into engine runs; the format act (repos cell, N); `list`/`info` implementation (R-6.2); any unlanded design-table flag; PROMPT A/B/C or `build_preview`/`render_prompt_b` (R-4.24); summary-line or warning-row emission for this feature (SUPPRESS is the cut, A6-R7(2)); persistence of anything; FX-A6 behavioral legs a6·1–13 + divergence half of a6·16; all FX-A7 legs; any PTY-helper change (RECONCILE I5); merge/push/publication/release.

## Open gates (live at this revision; none is this plan's to discharge locally)

1. **STOP-1 — ANSWERED AND FOLDED** (owner ruling m-3 `intg-stop1-a6-golden-bytes/DESIGN-planner-20260827-235912.md`, carried down at master `000750`): both cells resolved as byte-level readings and folded into Task 4's literals; the renderer task is un-blocked. No undetermined golden byte remains.
2. **Commissioning-chain lint residue (rule-3d family, now rule 3a)** — adjudicated OUTSIDE W-3 by master `234934`; two directed transport repairs executed exactly as scripted (the grant, then the bounded four-member chain completion: T1 `142730`, charter rev0 `142832`, charter rev1 `144023`, approval `144253` — all byte-identical, sha-verified both sides at this seat, engine-reconciled hand-origin). The residue transformed each time rather than clearing; at the current sweep it reads: "latest authorization-universe member intg-commission-charter/DESIGN-master-planner-20260827-144023.md fails stage-(a) shape; marker-bearing malformed authorization shadows and fails (DD-v29-master-authority-20260809 cross-seat rule 3a)" — apparently because the charter's own face carries `COMMISSION_AUTHORIZATION: yes` and shadows T1 as the universe's latest member. Per the fallback the transport stopped there; the residue is reported UP verbatim and the adjudication sits at master. **No approval or implementation dispatch issues while this gate is open.**
3. **W-3 coverage**: appended for revision `233453`, updated to `000218` (master `000750`) and to `001327` (master `001956`); one entry throughout. Each successor revision re-measures per the current-revision rule with an archived full-root sweep under `results/` as the reproducible instrument (the root-mode linter sweeps ALL Markdown under the root; the plan-file verdict is the exact-path-filtered subset of the archived output). Archives of record so far: `results/lint-root-sweep-post-reconcile-20260827.txt` (grant carried), `results/lint-root-sweep-chain-complete-20260828.txt` (chain carried, measured at `000218`), `results/lint-root-sweep-successor2-20260828.txt` (`001327`); this revision's archive is named in its accompanying relay.

Every other byte is determined by the sealed texts.
