#!/usr/bin/env bash
set -u

STOP() {
  printf 'STOP-task-1\n' >&2
  exit 1
}

PLAN_ARTIFACT=${1-}
EVID_ARG=${2-}
[ -n "$PLAN_ARTIFACT" ] || STOP
[ -n "$EVID_ARG" ] || STOP
plan_hash_rc=0
plan_hash_line=$(shasum -a 256 "$PLAN_ARTIFACT") || plan_hash_rc=$?
[ "$plan_hash_rc" -eq 0 ] || STOP
plan_hash=${plan_hash_line%% *}
[ "$plan_hash" = 97bef383a22771fc4855f87caa4ec6865d3f596af57860165e903f7f712d7747 ] || STOP
EVID=$(cd "$EVID_ARG" && pwd -P) || STOP
[ "$EVID" = /private/var/folders/hq/f0qq8v_103q9y8prfn20rzx80000gn/T/r450-evidence-6fNsQJ ] || STOP
WORKTREE=/Users/jack/Programming/bivpak-intg-r450-discover-parity
cd "$WORKTREE" || STOP

bind_rc=0
(cd "$EVID" && shasum -a 256 -c task-1-preexec-binding-sha256.txt > task-1-binding-verify.txt 2>&1) || bind_rc=$?
[ "$bind_rc" -eq 0 ] && [ -s "$EVID/task-1-binding-verify.txt" ] || STOP

q=0
python3 "$EVID/task-1-candidate-check.py"   "$WORKTREE/tests/test_adapter_claude_collect.cpp"   "$WORKTREE/src/adapters/claude_code/claude_code.cpp"   "$EVID/task-1-cpp-block-1.txt"   "$EVID/task-1-cpp-block-2.txt"   "$EVID/task-1-cpp-block-3.txt"   > "$EVID/task-1-candidate-check.txt" 2>&1 || q=$?
[ "$q" -eq 0 ] && [ -s "$EVID/task-1-candidate-check.txt" ] || STOP

[ -s "$EVID/observer-unset-names.txt" ] || STOP
observer_read_rc=0
{ OBS_ENV=(env); while read -r n; do OBS_ENV+=(-u "$n"); done < "$EVID/observer-unset-names.txt"; } || observer_read_rc=$?
printf 'observer_env_read_rc=%s\n' "$observer_read_rc" > "$EVID/observer-env-read.rc"
[ "$observer_read_rc" -eq 0 ] || STOP

b=0; cmake --build --preset ci-macos > "$EVID/green-build.log" 2>&1 || b=$?; [ "$b" -eq 0 ] || STOP
t=0; "${OBS_ENV[@]}" ./build/ci-macos/biv_tests -w UnmatchedTestSpec "Claude adapter discovery returns every store found: env and default both searched with codex parity (c1 §7)" -r xml > "$EVID/witness-green.xml" 2> "$EVID/witness-green.stderr" || t=$?; printf 'green_test_rc=%s\n' "$t" > "$EVID/witness-green.rc"; [ "$t" -eq 0 ] && [ -s "$EVID/witness-green.xml" ] || STOP; p=0; python3 "$EVID/witness.py" "$EVID/witness-green.xml" green > "$EVID/witness-green.verdict" || p=$?; [ "$p" -eq 0 ] || STOP
t=0; "${OBS_ENV[@]}" ./build/ci-macos/biv_tests -w UnmatchedTestSpec "Claude adapter discovers CLAUDE_CONFIG_DIR as an env-tier store" > "$EVID/existing-discover-1.log" 2>&1 || t=$?; [ "$t" -eq 0 ] || STOP
r=0; "${OBS_ENV[@]}" ctest --preset ci-macos -E '^safety-hardening$' --output-on-failure > "$EVID/ctest-macos-P.log" 2>&1 || r=$?; printf 'ctest_macos_P_rc=%s\n' "$r" > "$EVID/ctest-macos-P.rc"
[ -s "$EVID/ctest-macos-P.log" ] || STOP
f=0; grep -E '^[[:space:]]+[0-9]+ - .*\(Failed\)' "$EVID/ctest-macos-P.log" > "$EVID/ctest-macos-P.failed" || f=$?; [ "$f" -le 1 ] || STOP
[ -s "$EVID/ctest-macos-P.failed" ] || STOP
s=0; sed -E 's/^[[:space:]]*[0-9]+ - ([^ ]+) .*/\1/' "$EVID/ctest-macos-P.failed" > "$EVID/ctest-macos-P.failed-names" || s=$?; [ "$s" -eq 0 ] || STOP
[ -s "$EVID/ctest-macos-P.failed-names" ] || STOP
printf 'harness-selftest\n' > "$EVID/ctest-failed.expected"; d=0; diff "$EVID/ctest-failed.expected" "$EVID/ctest-macos-P.failed-names" > "$EVID/ctest-macos-P.failed.delta" || d=$?; [ "$d" -eq 0 ] || STOP
g=0; k=$(grep -c -F 'claude_adapter_file' "$EVID/ctest-macos-P.log") || g=$?; [ "$g" -le 1 ] || STOP; [ "$k" -ge 1 ] || STOP
resume_state=$(sed -n 's/^resume_state=//p' "$EVID/resume-state.txt"); [ "$resume_state" = i ] || [ "$resume_state" = ii ] || STOP
if [ "$resume_state" = i ]; then s=0; git status --porcelain > "$EVID/status-pre-P.txt" || s=$?; [ "$s" -eq 0 ] && [ -s "$EVID/status-pre-P.txt" ] || STOP; printf ' M src/adapters/claude_code/claude_code.cpp\n M tests/test_adapter_claude_collect.cpp\n' > "$EVID/status-pre-P.expected"; d=0; diff "$EVID/status-pre-P.expected" "$EVID/status-pre-P.txt" > "$EVID/status-pre-P.delta" || d=$?; [ "$d" -eq 0 ] || STOP; r=0; git diff -U0 -- src/adapters/claude_code/claude_code.cpp > "$EVID/claude-P.diff" || r=$?; [ "$r" -eq 0 ] && [ -s "$EVID/claude-P.diff" ] || STOP; g=0; grep -E '^@@' "$EVID/claude-P.diff" > "$EVID/claude-P.hunks" || g=$?; [ "$g" -eq 0 ] && [ -s "$EVID/claude-P.hunks" ] || STOP; h=0; python3 "$EVID/hunks.py" "$EVID/claude-P.hunks" 570 596 > "$EVID/claude-P.hunks.verdict" || h=$?; [ "$h" -eq 0 ] || STOP; r=0; git diff --numstat -- src/adapters/codex/ > "$EVID/codex-P.numstat" || r=$?; [ "$r" -eq 0 ] && [ ! -s "$EVID/codex-P.numstat" ] || STOP; fi
if [ "$resume_state" = ii ]; then s=0; git status --porcelain > "$EVID/status-pre-P.txt" || s=$?; [ "$s" -eq 0 ] && [ ! -s "$EVID/status-pre-P.txt" ] || STOP; r=0; git diff -U0 bbf297e36a38a1fab8c2675f945098a0633f9f8b HEAD -- src/adapters/claude_code/claude_code.cpp > "$EVID/claude-P.diff" || r=$?; [ "$r" -eq 0 ] && [ -s "$EVID/claude-P.diff" ] || STOP; g=0; grep -E '^@@' "$EVID/claude-P.diff" > "$EVID/claude-P.hunks" || g=$?; [ "$g" -eq 0 ] && [ -s "$EVID/claude-P.hunks" ] || STOP; h=0; python3 "$EVID/hunks.py" "$EVID/claude-P.hunks" 570 596 > "$EVID/claude-P.hunks.verdict" || h=$?; [ "$h" -eq 0 ] || STOP; r=0; git diff --numstat bbf297e36a38a1fab8c2675f945098a0633f9f8b HEAD -- src/adapters/codex/ > "$EVID/codex-P.numstat" || r=$?; [ "$r" -eq 0 ] && [ ! -s "$EVID/codex-P.numstat" ] || STOP; fi
resume_state=$(sed -n 's/^resume_state=//p' "$EVID/resume-state.txt"); [ "$resume_state" = i ] || [ "$resume_state" = ii ] || STOP
if [ "$resume_state" = i ]; then git add src/adapters/claude_code/claude_code.cpp tests/test_adapter_claude_collect.cpp && git commit -q -F "$EVID/message-P.txt" || STOP; fi
if [ "$resume_state" = ii ]; then [ "$(git rev-parse HEAD)" = 54954281b30cae113f399055fff106963a37a443 ] || STOP; fi
P=$(git rev-parse HEAD); [ -n "$P" ] || STOP; w=0; printf '%s\n' "$P" > "$EVID/P.txt" || w=$?; [ "$w" -eq 0 ] && [ -s "$EVID/P.txt" ] || STOP; e=0; git cat-file -e "${P}^{commit}" || e=$?; [ "$e" -eq 0 ] || STOP; [ "$(git rev-parse "${P}^")" = bbf297e36a38a1fab8c2675f945098a0633f9f8b ] || STOP; t=0; tree=$(git rev-parse "${P}^{tree}") || t=$?; [ "$t" -eq 0 ] && [ -n "$tree" ] || STOP; w=0; printf '%s\n' "$tree" > "$EVID/P.tree" || w=$?; [ "$w" -eq 0 ] && [ -s "$EVID/P.tree" ] || STOP; s=0; git status --porcelain > "$EVID/status-post-P.txt" || s=$?; [ "$s" -eq 0 ] && [ ! -s "$EVID/status-post-P.txt" ] || STOP

printf 'TASK_1_COMPLETE P=%s\n' "$P"
exit 0

: <<'TASK1_PLAN_INLINE_SPANS'
tests/test_adapter_claude_collect.cpp
src/adapters/claude_code/claude_code.cpp:570-596
biv::adapters::Env{getenv, home}
Store{root, locators, tier, archived}
DiscoveryTier{env, defaults, …}
src/adapters/adapter.hpp:23-49
biv::adapters::claude_code_adapter()
biv::adapters::codex_adapter()
biv::pack::pack(const fs::path&) -> expected<PackReport>
src/core/pack/pack.hpp:59
BivError{kind, path, detail}
src/core/support/error.hpp:40-46
biv
ErrKind::ArchiveWriteFailed
$EVID/resume-state.txt
i
ROW 5: (…)
$EVID/prior/
witness-red.rc
red_test_rc=
witness-red.verdict
red verdict ok
witness-red-parse.rc
red-build.rc
134909
i
i
ii
231512
i
ii
ii
write_file
#include "adapters/codex/codex.hpp"
#include "core/pack/pack.hpp"
#include "core/support/error.hpp"
impl-2
$EVID/prior/
b=0; cmake --build --preset ci-macos > "$EVID/red-build.log" 2>&1 || b=$?; printf 'red_build_rc=%s\n' "$b" > "$EVID/red-build.rc"; [ "$b" -eq 0 ] || STOP
-w UnmatchedTestSpec
NoTests
t=0; "${OBS_ENV[@]}" ./build/ci-macos/biv_tests -w UnmatchedTestSpec "Claude adapter discovery returns every store found: env and default both searched with codex parity (c1 §7)" -r xml > "$EVID/witness-red.xml" 2> "$EVID/witness-red.stderr" || t=$?; printf 'red_test_rc=%s\n' "$t" > "$EVID/witness-red.rc"; [ "$t" -ne 0 ] || STOP; [ -s "$EVID/witness-red.xml" ] || STOP
p=0; python3 "$EVID/witness.py" "$EVID/witness-red.xml" red > "$EVID/witness-red.verdict" || p=$?; [ "$p" -eq 0 ] && [ -s "$EVID/witness-red.verdict" ] || STOP
stores->size() == 2
REQUIRE_FALSE(refused.has_value())
claude_code.cpp:570-596
<optional>
codex.cpp:1193-1206
projects
b=0; cmake --build --preset ci-macos > "$EVID/green-build.log" 2>&1 || b=$?; [ "$b" -eq 0 ] || STOP
t=0; "${OBS_ENV[@]}" ./build/ci-macos/biv_tests -w UnmatchedTestSpec "Claude adapter discovery returns every store found: env and default both searched with codex parity (c1 §7)" -r xml > "$EVID/witness-green.xml" 2> "$EVID/witness-green.stderr" || t=$?; printf 'green_test_rc=%s\n' "$t" > "$EVID/witness-green.rc"; [ "$t" -eq 0 ] && [ -s "$EVID/witness-green.xml" ] || STOP; p=0; python3 "$EVID/witness.py" "$EVID/witness-green.xml" green > "$EVID/witness-green.verdict" || p=$?; [ "$p" -eq 0 ] || STOP
t=0; "${OBS_ENV[@]}" ./build/ci-macos/biv_tests -w UnmatchedTestSpec "Claude adapter discovers CLAUDE_CONFIG_DIR as an env-tier store" > "$EVID/existing-discover-1.log" 2>&1 || t=$?; [ "$t" -eq 0 ] || STOP
harness-selftest
r=0; "${OBS_ENV[@]}" ctest --preset ci-macos -E '^safety-hardening$' --output-on-failure > "$EVID/ctest-macos-P.log" 2>&1 || r=$?; printf 'ctest_macos_P_rc=%s\n' "$r" > "$EVID/ctest-macos-P.rc"
harness-selftest
f=0; grep -E '^[[:space:]]+[0-9]+ - .*\(Failed\)' "$EVID/ctest-macos-P.log" > "$EVID/ctest-macos-P.failed" || f=$?; [ "$f" -le 1 ] || STOP; s=0; sed -E 's/^[[:space:]]*[0-9]+ - ([^ ]+) .*/\1/' "$EVID/ctest-macos-P.failed" > "$EVID/ctest-macos-P.failed-names" || s=$?; [ "$s" -eq 0 ] || STOP; printf 'harness-selftest\n' > "$EVID/ctest-failed.expected"; d=0; diff "$EVID/ctest-failed.expected" "$EVID/ctest-macos-P.failed-names" > "$EVID/ctest-macos-P.failed.delta" || d=$?; [ "$d" -eq 0 ] || STOP
ctest-macos-P.log
harness-selftest
g=0; k=$(grep -c -F 'claude_adapter_file' "$EVID/ctest-macos-P.log") || g=$?; [ "$g" -le 1 ] || STOP; [ "$k" -ge 1 ] || STOP
harness-selftest
d
env -u
001126
resume_state=$(sed -n 's/^resume_state=//p' "$EVID/resume-state.txt"); [ "$resume_state" = i ] || [ "$resume_state" = ii ] || STOP
i
if [ "$resume_state" = i ]; then s=0; git status --porcelain > "$EVID/status-pre-P.txt" || s=$?; [ "$s" -eq 0 ] && [ -s "$EVID/status-pre-P.txt" ] || STOP; printf ' M src/adapters/claude_code/claude_code.cpp\n M tests/test_adapter_claude_collect.cpp\n' > "$EVID/status-pre-P.expected"; d=0; diff "$EVID/status-pre-P.expected" "$EVID/status-pre-P.txt" > "$EVID/status-pre-P.delta" || d=$?; [ "$d" -eq 0 ] || STOP; r=0; git diff -U0 -- src/adapters/claude_code/claude_code.cpp > "$EVID/claude-P.diff" || r=$?; [ "$r" -eq 0 ] && [ -s "$EVID/claude-P.diff" ] || STOP; g=0; grep -E '^@@' "$EVID/claude-P.diff" > "$EVID/claude-P.hunks" || g=$?; [ "$g" -eq 0 ] && [ -s "$EVID/claude-P.hunks" ] || STOP; h=0; python3 "$EVID/hunks.py" "$EVID/claude-P.hunks" 570 596 > "$EVID/claude-P.hunks.verdict" || h=$?; [ "$h" -eq 0 ] || STOP; r=0; git diff --numstat -- src/adapters/codex/ > "$EVID/codex-P.numstat" || r=$?; [ "$r" -eq 0 ] && [ ! -s "$EVID/codex-P.numstat" ] || STOP; fi
ii
if [ "$resume_state" = ii ]; then s=0; git status --porcelain > "$EVID/status-pre-P.txt" || s=$?; [ "$s" -eq 0 ] && [ ! -s "$EVID/status-pre-P.txt" ] || STOP; r=0; git diff -U0 bbf297e36a38a1fab8c2675f945098a0633f9f8b HEAD -- src/adapters/claude_code/claude_code.cpp > "$EVID/claude-P.diff" || r=$?; [ "$r" -eq 0 ] && [ -s "$EVID/claude-P.diff" ] || STOP; g=0; grep -E '^@@' "$EVID/claude-P.diff" > "$EVID/claude-P.hunks" || g=$?; [ "$g" -eq 0 ] && [ -s "$EVID/claude-P.hunks" ] || STOP; h=0; python3 "$EVID/hunks.py" "$EVID/claude-P.hunks" 570 596 > "$EVID/claude-P.hunks.verdict" || h=$?; [ "$h" -eq 0 ] || STOP; r=0; git diff --numstat bbf297e36a38a1fab8c2675f945098a0633f9f8b HEAD -- src/adapters/codex/ > "$EVID/codex-P.numstat" || r=$?; [ "$r" -eq 0 ] && [ ! -s "$EVID/codex-P.numstat" ] || STOP; fi
i
ii
001126
resume_state=$(sed -n 's/^resume_state=//p' "$EVID/resume-state.txt"); [ "$resume_state" = i ] || [ "$resume_state" = ii ] || STOP
i
if [ "$resume_state" = i ]; then git add src/adapters/claude_code/claude_code.cpp tests/test_adapter_claude_collect.cpp && git commit -q -F "$EVID/message-P.txt" || STOP; fi
message-P.txt
adapters(claude): discover returns every store found (env + default), codex parity — PROVISIONAL, cells not yet transcribed
ii
if [ "$resume_state" = ii ]; then [ "$(git rev-parse HEAD)" = 54954281b30cae113f399055fff106963a37a443 ] || STOP; fi
P=$(git rev-parse HEAD); [ -n "$P" ] || STOP; w=0; printf '%s\n' "$P" > "$EVID/P.txt" || w=$?; [ "$w" -eq 0 ] && [ -s "$EVID/P.txt" ] || STOP; e=0; git cat-file -e "${P}^{commit}" || e=$?; [ "$e" -eq 0 ] || STOP; [ "$(git rev-parse "${P}^")" = bbf297e36a38a1fab8c2675f945098a0633f9f8b ] || STOP; t=0; tree=$(git rev-parse "${P}^{tree}") || t=$?; [ "$t" -eq 0 ] && [ -n "$tree" ] || STOP; w=0; printf '%s\n' "$tree" > "$EVID/P.tree" || w=$?; [ "$w" -eq 0 ] && [ -s "$EVID/P.tree" ] || STOP; s=0; git status --porcelain > "$EVID/status-post-P.txt" || s=$?; [ "$s" -eq 0 ] && [ ! -s "$EVID/status-post-P.txt" ] || STOP
git reflog show intg/r450-discover-parity
$EVID/P.txt
git cat-file -e "${P}^{commit}"
git cat-file -e "${sha}^{commit}"
:
"${P}^{commit}"
ii
TASK1_PLAN_INLINE_SPANS

: <<'TASK1_CPP_BLOCK_1'
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
TASK1_CPP_BLOCK_1

: <<'TASK1_CPP_BLOCK_2'
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
TASK1_CPP_BLOCK_2

: <<'TASK1_CPP_BLOCK_3'
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
TASK1_CPP_BLOCK_3

