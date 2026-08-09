# R-4.8 Packer-Home Carrier Implementation Plan (rev0)

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Serialize the packer's absolute `$HOME` (+ its own path flavor) into the manifest at pack time and transport it opaquely to the adapter session-install verifiers, per the approved rev2 design.

**Architecture:** One optional `PackerHome{path, flavor}` struct on `Manifest` (two co-occurring wire keys), captured via a core-local total `classify_absolute` classifier, validated by one lexical predicate at both wire boundaries, and passed once through a new `InstallTarget` field by `run_session_leg`. Core never interprets the value; only adapters read it.

**Tech Stack:** C++23, simdjson (parse), in-repo JSON writer, Catch2 (`biv_tests`), CMake preset `dev`.

DESIGN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-09-s4-matrix-arm1-r48-packer-home-carrier-design.md (rev2, SHA-256 `349ef6e1f503be8a05660053111d5a4de634f0c0eba7512cccabfc38cc75841a`, APPROVED at `…REV2-APPROVE-20260809-053253`)
GRILL_LOCK_ID: s4-matrix-arm1-r48-carrier-grill-20260809
FLOOR_CONTRACT: RATIFIED at `…RATIFIED-20260809-050728` — the WIRE SHAPE IS SEALED by that ratification; any wire change is a design revision routed back to the floor, not a plan-level choice.

## Global Constraints

- `format_version` stays 1; NO `required_capabilities` entry; NO new `ErrKind` member (D5 nine-member freeze).
- Wire: keys `"packer_home"` + `"packer_home_flavor"`, top-level, emitted together right after `"source_path_flavor"`, or both omitted. Present ⇒ non-empty absolute in its declared-and-verified flavor.
- Emittable states = {absent, valid}: the writer never emits `""`, a lone key, a relative path, or a mismatched pair; an invalid engaged in-memory value collapses to omitted.
- JSON `null` ≡ missing key, for BOTH keys.
- Core performs NO interpretation of the value (no prefix logic, no username derivation, no path ops) — capture, serialize, parse, transport only.
- DO NOT touch: `pack.cpp::path_flavor()` / any `source_path_flavor` behavior, `src/adapters/rewrite_common.*`, `SessionProvenance`, the repo engine, `scan.cpp:138` fence, `manifest.cpp:597` fence (`require_empty_array(object, "repos")` — additions in manifest.cpp must not disturb it).
- No CI trigger, no merge, no publication, no release action (release hold ABSOLUTE; R-4.8 is hard-gated before any release).
- Full local gate per task-final steps: `git diff --check && cmake --build --preset dev -j8 && ctest --preset dev -E '^safety-hardening$' --output-on-failure`.

## Branch mechanics

One branch `s4-matrix/r48-carrier` off current `main` (`f0179e0` or later). One commit per task. On completion: ONE draft PR into `main`; no merge — the pair review/panel path and merge conditions are downstream and operator-owned.

## File structure

- Modify: `src/core/manifest/manifest.hpp` — `PackerHome` struct, `Manifest::packer_home` field, `classify_absolute` + `packer_home_valid` declarations.
- Modify: `src/core/manifest/manifest.cpp` — classifier + predicate + serialize emit + parse/validate/remap.
- Modify: `src/core/pack/pack.cpp` — capture helper + one designated-init field.
- Modify: `src/adapters/adapter.hpp` — `InstallTarget::packer_home` field.
- Modify: `src/core/open/sessions.cpp` — populate the field at the single construction site.
- Test: `tests/test_manifest.cpp`, `tests/test_pack.cpp`, `tests/test_sessions.cpp`, `tests/test_adapter_claude_install.cpp`, `tests/test_adapter_codex_install.cpp`.

---

### Task 1: Schema — struct, classifier, validator, serialize, parse (design §3/§5/§6; tests 1–14)

**Files:**
- Modify: `src/core/manifest/manifest.hpp` (struct cluster near `SessionProvenance`, `manifest.hpp:18-70`)
- Modify: `src/core/manifest/manifest.cpp` (helpers near `optional_string` :99; serialize cluster :481-484; parse cluster :553-557; `parse_path_flavor` :451-462 UNTOUCHED)
- Test: `tests/test_manifest.cpp`

**Interfaces:**
- Produces: `biv::manifest::PackerHome{std::string path; PathFlavor flavor}` (defaulted `operator==`); `std::optional<PathFlavor> biv::manifest::classify_absolute(std::string_view)`; `bool biv::manifest::packer_home_valid(const PackerHome&)`; `Manifest::packer_home` (`std::optional<PackerHome>`, declared AFTER `source_path_flavor`, BEFORE `agent_sessions` — designated-init order depends on it).
- Consumes: existing `optional_string`, `parse_path_flavor`, `to_string(PathFlavor)`, JSON writer.

- [ ] **Step 1.1: Write the failing tests** — append to `tests/test_manifest.cpp`. First add the hostile-JSON helper to the file's anonymous namespace (mirror the existing `"Manifest parser ignores unknown fields"` fixture exactly, including its `"sha256"` bivignore key):

```cpp
std::string carrier_json(const std::string& injected) {
  return "{"
         "\"format_version\":1,"
         "\"required_capabilities\":[],"
         "\"image_id\":\"id\","
         "\"app_version\":\"0.1.0\","
         "\"created_at\":\"2026-07-05T00:00:00Z\","
         "\"source_path\":\"/tmp/plain\","
         "\"source_path_flavor\":\"posix\"," +
         injected +
         "\"bivignore\":{\"source\":\"file\",\"builtin_id\":null,\"sha256\":\"def\"},"
         "\"repos\":[],\"agent_sessions\":[]"
         "}";
}
```

Then the test cases (design §9 tests 1–14):

```cpp
TEST_CASE("packer_home serializes after source_path_flavor and round-trips") {
  auto manifest = fixed_manifest();
  manifest.packer_home = biv::manifest::PackerHome{
      .path = "/Users/jack", .flavor = biv::manifest::PathFlavor::posix};

  const auto json = biv::manifest::serialize(manifest);
  REQUIRE(json.find("\"packer_home\":\"/Users/jack\"") != std::string::npos);
  REQUIRE(json.find("\"packer_home_flavor\":\"posix\"") != std::string::npos);
  REQUIRE(json.find("\"source_path_flavor\"") < json.find("\"packer_home\""));

  const auto parsed = biv::manifest::parse(bytes_of(json));
  REQUIRE(parsed.has_value());
  REQUIRE(parsed->packer_home == manifest.packer_home);
}

TEST_CASE("packer_home round-trips every flavor spelling") {
  struct Row {
    std::string path;
    biv::manifest::PathFlavor flavor;
  };
  for (const auto& row : std::array{
           Row{"/home/user", biv::manifest::PathFlavor::posix},
           Row{"/mnt/c/Users/x", biv::manifest::PathFlavor::wsl},
           Row{"C:/Users/x", biv::manifest::PathFlavor::windows},
           Row{"C:\\Users\\x", biv::manifest::PathFlavor::windows},
           Row{"\\\\?\\C:\\Users\\x", biv::manifest::PathFlavor::windows},
       }) {
    CAPTURE(row.path);
    auto manifest = fixed_manifest();
    manifest.packer_home = biv::manifest::PackerHome{row.path, row.flavor};
    const auto parsed =
        biv::manifest::parse(bytes_of(biv::manifest::serialize(manifest)));
    REQUIRE(parsed.has_value());
    REQUIRE(parsed->packer_home == manifest.packer_home);
  }
}

TEST_CASE("packer_home absent round-trips and pre-carrier fixtures stay clean") {
  auto manifest = fixed_manifest();
  manifest.packer_home = std::nullopt;
  const auto json = biv::manifest::serialize(manifest);
  REQUIRE(json.find("packer_home") == std::string::npos);
  const auto parsed = biv::manifest::parse(bytes_of(json));
  REQUIRE(parsed.has_value());
  REQUIRE(parsed->packer_home == std::nullopt);

  const auto pre_carrier = biv::manifest::parse(bytes_of(carrier_json("")));
  REQUIRE(pre_carrier.has_value());
  REQUIRE(pre_carrier->packer_home == std::nullopt);
}

TEST_CASE("packer_home invalid engaged values collapse to absent on serialize") {
  for (const auto& bad : std::array{
           biv::manifest::PackerHome{"", biv::manifest::PathFlavor::posix},
           biv::manifest::PackerHome{"relative/home",
                                     biv::manifest::PathFlavor::posix},
           biv::manifest::PackerHome{"/home/user",
                                     biv::manifest::PathFlavor::windows},
       }) {
    CAPTURE(bad.path);
    auto manifest = fixed_manifest();
    manifest.packer_home = bad;
    REQUIRE(biv::manifest::serialize(manifest).find("packer_home") ==
            std::string::npos);
  }
}

TEST_CASE("packer_home JSON null is missing for both keys") {
  const auto lone_null =
      biv::manifest::parse(bytes_of(carrier_json("\"packer_home\":null,")));
  REQUIRE(lone_null.has_value());
  REQUIRE(lone_null->packer_home == std::nullopt);

  const auto null_with_flavor = biv::manifest::parse(bytes_of(carrier_json(
      "\"packer_home\":null,\"packer_home_flavor\":\"posix\",")));
  REQUIRE_FALSE(null_with_flavor.has_value());
  REQUIRE(null_with_flavor.error().detail == "packer_home_flavor");
}

TEST_CASE("packer_home lone keys fail closed naming the flavor key") {
  const auto lone_home =
      biv::manifest::parse(bytes_of(carrier_json("\"packer_home\":\"/x\",")));
  REQUIRE_FALSE(lone_home.has_value());
  REQUIRE(lone_home.error().detail == "packer_home_flavor");

  const auto lone_flavor = biv::manifest::parse(
      bytes_of(carrier_json("\"packer_home_flavor\":\"posix\",")));
  REQUIRE_FALSE(lone_flavor.has_value());
  REQUIRE(lone_flavor.error().detail == "packer_home_flavor");
}

TEST_CASE("packer_home malformed values fail closed naming the home key") {
  for (const auto& injected : std::array<std::string, 5>{
           "\"packer_home\":42,\"packer_home_flavor\":\"posix\",",
           "\"packer_home\":\"\",\"packer_home_flavor\":\"posix\",",
           "\"packer_home\":\"relative/home\",\"packer_home_flavor\":\"posix\",",
           "\"packer_home\":\"/home/user\",\"packer_home_flavor\":\"windows\",",
           "\"packer_home\":\"/mnt/c/Users/x\",\"packer_home_flavor\":\"posix\",",
       }) {
    CAPTURE(injected);
    const auto parsed = biv::manifest::parse(bytes_of(carrier_json(injected)));
    REQUIRE_FALSE(parsed.has_value());
    REQUIRE(parsed.error().detail == "packer_home");
  }
}

TEST_CASE("packer_home unknown flavor names the flavor key not source_path_flavor") {
  const auto parsed = biv::manifest::parse(bytes_of(carrier_json(
      "\"packer_home\":\"/x\",\"packer_home_flavor\":\"vms\",")));
  REQUIRE_FALSE(parsed.has_value());
  REQUIRE(parsed.error().detail == "packer_home_flavor");
}

TEST_CASE("classify_absolute covers every grammar branch") {
  using biv::manifest::PathFlavor;
  const auto classify = biv::manifest::classify_absolute;
  REQUIRE(classify("/home/user") == PathFlavor::posix);
  REQUIRE(classify("/mnt/c/Users/x") == PathFlavor::wsl);
  REQUIRE(classify("/mnt/C/Users/x") == PathFlavor::wsl);
  REQUIRE(classify("/mnt/cc/x") == PathFlavor::posix);  // not a drive mount
  REQUIRE(classify("C:/Users/x") == PathFlavor::windows);
  REQUIRE(classify("C:\\Users\\x") == PathFlavor::windows);
  REQUIRE(classify("\\\\?\\C:\\Users\\x") == PathFlavor::windows);
  REQUIRE(classify("//?/C:/Users/x") == PathFlavor::windows);
  REQUIRE(classify("") == std::nullopt);
  REQUIRE(classify("relative/home") == std::nullopt);
  REQUIRE(classify("mnt/c/x") == std::nullopt);
  REQUIRE(classify("C:") == std::nullopt);
  REQUIRE(classify("C:x") == std::nullopt);
}

TEST_CASE("classify_absolute agrees with the adapter spelling classifier") {
  // Parity pin (design §3/D7): absolute spellings only — the adapter
  // classifier is total (posix fallback), classify_absolute is not.
  for (const auto spelling : std::array{
           "/home/user", "/mnt/c/Users/x", "/mnt/C/Users/x", "/mnt/cc/x",
           "C:/Users/x", "C:\\Users\\x", "\\\\?\\C:\\Users\\x", "//?/C:/Users/x",
       }) {
    CAPTURE(spelling);
    REQUIRE(biv::manifest::classify_absolute(spelling) ==
            biv::adapters::rewrite::path_flavor_for(spelling));
  }
}
```

Add `#include "adapters/rewrite_common.hpp"` at the top of `tests/test_manifest.cpp` (match the file's existing include-path style; `biv_tests` links `bivcore` → `biv_adapters` PUBLIC, so this links).

- [ ] **Step 1.2: Run to verify failure.** `cmake --build --preset dev -j8` — expected: COMPILE FAILURE (`PackerHome`, `classify_absolute`, `packer_home` member do not exist). A compile-time RED is the intended first failure.

- [ ] **Step 1.3: Implement the schema.** In `src/core/manifest/manifest.hpp`, after `struct BivignoreProvenance` (:22) add:

```cpp
struct PackerHome {
  std::string path;
  PathFlavor flavor{PathFlavor::posix};
  friend bool operator==(const PackerHome&, const PackerHome&) = default;
};
```

In `struct Manifest`, immediately after `PathFlavor source_path_flavor{PathFlavor::posix};` add:

```cpp
std::optional<PackerHome> packer_home;
```

Next to the existing `parse_path_flavor`/`to_string` declarations add:

```cpp
std::optional<PathFlavor> classify_absolute(std::string_view path);
bool packer_home_valid(const PackerHome& value);
```

In `src/core/manifest/manifest.cpp` (file scope, near `parse_path_flavor` :451):

```cpp
namespace {
bool carrier_ascii_alpha(const char value) {
  return (value >= 'a' && value <= 'z') || (value >= 'A' && value <= 'Z');
}
}  // namespace

std::optional<PathFlavor> classify_absolute(const std::string_view path) {
  if (path.size() >= 7U && path.starts_with("/mnt/") &&
      carrier_ascii_alpha(path.at(5)) && path.at(6) == '/') {
    return PathFlavor::wsl;
  }
  if ((path.size() >= 3U && carrier_ascii_alpha(path.at(0)) &&
       path.at(1) == ':' && (path.at(2) == '\\' || path.at(2) == '/')) ||
      path.starts_with(R"(\\?\)") || path.starts_with("//?/")) {
    return PathFlavor::windows;
  }
  if (path.starts_with('/')) {
    return PathFlavor::posix;
  }
  return std::nullopt;
}

bool packer_home_valid(const PackerHome& value) {
  return !value.path.empty() && classify_absolute(value.path) == value.flavor;
}
```

(WSL before POSIX is load-bearing: a mount spelling is POSIX-lexical. If the file has an existing `ascii_alpha`-style helper, reuse it instead of adding `carrier_ascii_alpha`.)

In `serialize(Manifest)` immediately after the `source_path_flavor` pair (:483-484):

```cpp
if (manifest.packer_home && packer_home_valid(*manifest.packer_home)) {
  writer.key("packer_home");
  writer.value_string(manifest.packer_home->path);
  writer.key("packer_home_flavor");
  writer.value_string(to_string(manifest.packer_home->flavor));
}
```

In `parse`, immediately after `source_path_flavor` is parsed and assigned (:557 area), before `agent_sessions`:

```cpp
auto packer_home_text = optional_string(object, "packer_home");
if (!packer_home_text) {
  return std::unexpected(packer_home_text.error());
}
auto packer_home_flavor_text = optional_string(object, "packer_home_flavor");
if (!packer_home_flavor_text) {
  return std::unexpected(packer_home_flavor_text.error());
}
if (packer_home_text->has_value() != packer_home_flavor_text->has_value()) {
  return std::unexpected(
      BivError{ErrKind::ParseError, {}, "packer_home_flavor"});
}
if (packer_home_text->has_value()) {
  auto flavor = parse_path_flavor(**packer_home_flavor_text);
  if (!flavor) {
    return std::unexpected(
        BivError{ErrKind::ParseError, {}, "packer_home_flavor"});
  }
  PackerHome value{.path = std::move(**packer_home_text), .flavor = *flavor};
  if (!packer_home_valid(value)) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, "packer_home"});
  }
  manifest.packer_home = std::move(value);
}
```

(`optional_string` already yields `ParseError{"packer_home"}` / `ParseError{"packer_home_flavor"}` on wrong-type — key-named — and collapses `null` to disengaged, which IS the null≡missing rule. The `parse_path_flavor` failure is remapped locally; the helper and its `source_path_flavor` callers are untouched.)

- [ ] **Step 1.4: Run to verify pass.** `cmake --build --preset dev -j8 && ./build/dev/biv_tests "*packer_home*" "*classify_absolute*"` — expected: ALL PASS. Then run the FULL manifest suite `./build/dev/biv_tests "Manifest*"` — expected: no regression (esp. `"Manifest parser ignores unknown fields"` and the `repos` fence cases).

- [ ] **Step 1.5: Commit.** `git add src/core/manifest/manifest.hpp src/core/manifest/manifest.cpp tests/test_manifest.cpp && git commit -m "manifest: add optional packer_home carrier with total classifier and wire validation"`

---

### Task 2: Pack-time capture (design §4; tests 15–20)

**Files:**
- Modify: `src/core/pack/pack.cpp` (helper near `path_flavor` :131-140; designated-init at :663-673)
- Test: `tests/test_pack.cpp`

**Interfaces:**
- Consumes: Task 1's `manifest::PackerHome`, `manifest::classify_absolute`; existing `process_env()` (:230) and `manifest_model` designated-init (:663).
- Produces: packed images whose manifest carries `packer_home` iff `$HOME` is absolute.

- [ ] **Step 2.1: Write the failing tests** — append to `tests/test_pack.cpp`, using the file's existing `make_tmp`/`write_file`/`ScopedEnv`/`read_archive`/`as_span` helpers (idiom of the Task-6 cases at :194-249):

```cpp
TEST_CASE("pack captures packer_home per HOME shape") {
  struct Row {
    std::string_view label;
    std::optional<std::string> home;  // nullopt = unset HOME
    std::optional<biv::manifest::PackerHome> expected;
  };
  const auto rows = std::array{
      Row{"absolute-posix", "/Users/jack",
          biv::manifest::PackerHome{"/Users/jack",
                                    biv::manifest::PathFlavor::posix}},
      Row{"unset", std::nullopt, std::nullopt},
      Row{"empty", "", std::nullopt},
      Row{"relative", "relative/home", std::nullopt},
      Row{"wsl-mount", "/mnt/c/Users/jack",
          biv::manifest::PackerHome{"/mnt/c/Users/jack",
                                    biv::manifest::PathFlavor::wsl}},
      Row{"windows-drive", "C:/Users/jack",
          biv::manifest::PackerHome{"C:/Users/jack",
                                    biv::manifest::PathFlavor::windows}},
  };
  for (const auto& row : rows) {
    CAPTURE(row.label);
    const auto root = make_tmp("packer-home-" + std::string{row.label});
    const auto source = root / "proj";
    std::filesystem::create_directories(source);
    write_file(source / "work.txt", "workspace");
    std::optional<ScopedEnv> home;
    if (row.home.has_value()) {
      home.emplace("HOME", *row.home);
    } else {
      unsetenv("HOME");
    }

    const auto report = biv::pack::pack(source);

    REQUIRE(report.has_value());
    const auto members = read_archive(root / "proj.bvpk");
    auto manifest = biv::manifest::parse(as_span(members.at(0).data));
    REQUIRE(manifest.has_value());
    REQUIRE(manifest->packer_home == row.expected);
    if (row.label == std::string_view{"wsl-mount"}) {
      // Independence (design §8): posix source, wsl home.
      REQUIRE(manifest->source_path_flavor == biv::manifest::PathFlavor::posix);
    }
    std::filesystem::remove_all(root);
  }
}
```

(If `ScopedEnv` lacks a two-arg emplace-friendly constructor for this pattern, restore the prior `HOME` with an outer `ScopedEnv` per the file's existing unset-restore idiom — keep the assertion table identical. The `unsetenv` branch must restore `HOME` after the case; wrap the loop body's env handling exactly like the file's existing `ScopedEnv` save/restore semantics.)

- [ ] **Step 2.2: Run to verify failure.** `cmake --build --preset dev -j8 && ./build/dev/biv_tests "pack captures packer_home per HOME shape"` — expected: FAIL — `manifest->packer_home` is `nullopt` for the three present-rows (capture not implemented).

- [ ] **Step 2.3: Implement capture.** In `src/core/pack/pack.cpp`, next to `path_flavor` (:140, anonymous namespace) add:

```cpp
std::optional<manifest::PackerHome> packer_home_carrier(
    const std::filesystem::path& home) {
  const auto text = home.generic_string();
  const auto flavor = manifest::classify_absolute(text);
  if (!flavor) {
    return std::nullopt;
  }
  return manifest::PackerHome{.path = text, .flavor = *flavor};
}
```

In the `manifest_model` designated-init (:663-673), between `.source_path_flavor` and `.agent_sessions` (order must match the struct):

```cpp
.packer_home = packer_home_carrier(process_env().home),
```

- [ ] **Step 2.4: Run to verify pass.** Same command — expected: PASS, all six rows. Then `./build/dev/biv_tests` for the pack suite (no regression; existing cases set `HOME` via `ScopedEnv` so their manifests now carry `packer_home` — they assert other fields and must stay green; if any asserts full-manifest equality, update it to include the carrier and note it in the task commit).

- [ ] **Step 2.5: Commit.** `git add src/core/pack/pack.cpp tests/test_pack.cpp && git commit -m "pack: capture packer_home carrier from HOME at pack time"`

---

### Task 3: Transport — InstallTarget + run_session_leg + adapter receipt (design §7; tests 21–23)

**Files:**
- Modify: `src/adapters/adapter.hpp` (`InstallTarget` :156-161)
- Modify: `src/core/open/sessions.cpp` (single `InstallTarget` construction :266-271)
- Test: `tests/test_sessions.cpp` (CountingAdapter :173), `tests/test_adapter_claude_install.cpp`, `tests/test_adapter_codex_install.cpp`

**Interfaces:**
- Consumes: Task 1's `manifest::PackerHome`; `run_session_leg`'s `manifest` parameter (`sessions.cpp:175-179`).
- Produces: `adapters::InstallTarget::packer_home` (`std::optional<manifest::PackerHome>`) — the field the floor's needle will read; ONE population site.

- [ ] **Step 3.1: Write the failing tests.** In `tests/test_sessions.cpp`, extend `CountingAdapter` (:173) to record the received field — add a member `std::optional<biv::manifest::PackerHome> seen_packer_home;` and in its `install` override capture `seen_packer_home = target.packer_home;`. Then add:

```cpp
TEST_CASE("run_session_leg transports packer_home to the adapter once per image") {
  // Present: build the leg's manifest with a carrier and run the existing
  // eligible-entry fixture path (mirror the adjacent CountingAdapter case
  // setup at :225 exactly, then set:)
  //   manifest.packer_home = biv::manifest::PackerHome{
  //       "/Users/packer", biv::manifest::PathFlavor::posix};
  // After the leg runs:
  REQUIRE(adapter.seen_packer_home ==
          biv::manifest::PackerHome{"/Users/packer",
                                    biv::manifest::PathFlavor::posix});
}

TEST_CASE("run_session_leg passes absent packer_home through unchanged") {
  // Same fixture, manifest.packer_home left nullopt:
  REQUIRE(adapter.seen_packer_home == std::nullopt);
}
```

(The comment lines describe fixture reuse of the EXISTING CountingAdapter case at :225 — copy that case's setup verbatim; the only new lines are the manifest field set and the two REQUIREs. Both tests are complete once that setup is pasted; no other scenario changes.)

In `tests/test_adapter_claude_install.cpp` and `tests/test_adapter_codex_install.cpp`, add one receipt case each (identical shape; RECEIPT only — needle semantics are floor-owned and out of scope):

```cpp
TEST_CASE("claude install accepts a transported packer_home as inert metadata") {
  // Take the file's smallest existing green install case; construct its
  // InstallTarget with the additional field:
  //   .packer_home = biv::manifest::PackerHome{
  //       "/Users/packer", biv::manifest::PathFlavor::posix},
  // Re-run the identical assertions of that case: outcomes/rows unchanged.
}
```

(For codex, same with the codex case. These prove the field is receivable and INERT — compile-time receipt + zero behavior change. Copy each file's smallest green install case wholesale and add only the field; every existing assertion stays.)

- [ ] **Step 3.2: Run to verify failure.** `cmake --build --preset dev -j8` — expected: COMPILE FAILURE (`InstallTarget` has no `packer_home`).

- [ ] **Step 3.3: Implement transport.** In `src/adapters/adapter.hpp`, `struct InstallTarget` (:156-161), after `Capabilities capabilities;`:

```cpp
std::optional<manifest::PackerHome> packer_home;
```

In `src/core/open/sessions.cpp`, the single construction (:267-270), after `.capabilities = caps`:

```cpp
, .packer_home = manifest.packer_home
```

NO other read, branch, or interpretation of the value anywhere in core — transport only.

- [ ] **Step 3.4: Run to verify pass.** `cmake --build --preset dev -j8 && ./build/dev/biv_tests "*packer_home*"` — expected: ALL PASS (schema + capture + transport + receipt). Then the sessions and both adapter-install suites in full — no regression.

- [ ] **Step 3.5: Full local gate.** `git diff --check && cmake --build --preset dev -j8 && ctest --preset dev -E '^safety-hardening$' --output-on-failure` — expected: all locally applicable rows pass (macOS skips per preset are expected and not failures).

- [ ] **Step 3.6: Commit.** `git add src/adapters/adapter.hpp src/core/open/sessions.cpp tests/test_sessions.cpp tests/test_adapter_claude_install.cpp tests/test_adapter_codex_install.cpp && git commit -m "open: transport packer_home opaquely to adapter install targets"`

- [ ] **Step 3.7: Open ONE draft PR** from `s4-matrix/r48-carrier` into `main` (no merge; no CI re-runs beyond the single push's automatic checks; observe once).

---

## Acceptance criteria (the plan is done when)

1. All Task 1–3 tests green + the full local gate green at the branch head.
2. Wire proof: a packed image under an absolute `$HOME` carries both keys after `source_path_flavor`; under unset/empty/relative `$HOME` carries neither (Q1).
3. Fail-closed proof: every §8 malformed row is a `ParseError` naming the exact key (incl. the `packer_home_flavor` remap falsifier).
4. Parity proof: `classify_absolute` agrees with `biv::adapters::rewrite::path_flavor_for` on the spelling table.
5. Transport proof: `CountingAdapter` observes the same image-level value (present and absent); both adapter legs receive it as INERT metadata (zero behavior change).
6. Fences proof: `scan.cpp:138` and `manifest.cpp:597` byte-identical to `main`'s.
7. NO change to: `pack.cpp::path_flavor()`, `rewrite_common.*`, `SessionProvenance`, any `ErrKind`, `format_version`, any restore/eligibility/classification behavior.

## Out of scope (anti-half-fix guards)

- The floor's home-prefix needle (lands with this carrier under R-4.8, floor-owned; receipt tests here must NOT assert needle semantics).
- Username derivation, normalization, prefix logic, any core interpretation.
- Honest-packer hardening: a hostile image omitting the pair evades the needle BY DESIGN (floor-acknowledged limitation; the origin-path/id union scan is the adversarial floor) — do not add carrier-side countermeasures.
- Merge, publication, release (hold ABSOLUTE); R-4.8 gate is master's.

## Verification target

E2 (local command proof: build + full test gate at the branch head). Panel/merge evidence is downstream of this plan.
