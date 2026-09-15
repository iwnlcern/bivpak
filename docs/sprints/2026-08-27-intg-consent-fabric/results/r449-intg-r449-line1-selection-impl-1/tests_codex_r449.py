#!/usr/bin/env python3
# tests_codex_r449.py <tests/test_adapter_codex_collect.cpp> — R-4.49 witness SECTIONs inside the EXISTING TEST_CASE "X-2 Codex suppresses
# session_id warnings outside the source root" (case census unchanged). Anchor asserted EXACTLY ONCE.
import sys
p = sys.argv[1]; t = open(p, encoding="utf-8").read()
OLD = '''  CHECK_FALSE(std::ranges::any_of(
      report->warnings, [&](const std::string& warning) {
        return warning == "SessionIdWithoutId:" + rollout.generic_string();
      }));
  fs::remove_all(root);
}

TEST_CASE("Codex duplicate-store E-3 warns and picks by declared freshness") {'''
NEW = '''  CHECK_FALSE(std::ranges::any_of(
      report->warnings, [&](const std::string& warning) {
        return warning == "SessionIdWithoutId:" + rollout.generic_string();
      }));

  // R-4.49 (c1 §4: the FIRST session_meta record keys the rollout — m-2 C-2 ruling; fence 142000 §2 V-LS-2/V-LS-4): membership,
  // the head-fact warning and the tail facts are the same however large the rollout is and whatever precedes session_meta.
  const auto r449_stores = [](const fs::path& r449_store) {
    return std::vector<biv::adapters::Store>{biv::adapters::Store{
        .root = r449_store,
        .locators = {biv::adapters::StoreLocator{.kind = "sessions_root",
                                                 .path = r449_store / "sessions"}},
        .tier = biv::adapters::DiscoveryTier::defaults,
        .archived = false}};
  };
  const auto r449_body = [](const std::size_t bytes) {
    const std::string line =
        "{\\"timestamp\\":\\"2026-07-06T11:00:01Z\\",\\"type\\":\\"response_item\\",\\"payload\\":{\\"type\\":\\"message\\","
        "\\"role\\":\\"assistant\\",\\"content\\":[{\\"type\\":\\"output_text\\",\\"text\\":\\"" +
        std::string(1000, 'y') + "\\"}]}}\\n";
    std::string body;
    while (body.size() < bytes) {
      body += line;
    }
    return body;
  };
  const auto r449_meta = [](const std::string& id, const std::string& cwd, const bool with_id) {
    return std::string{"{\\"timestamp\\":\\"2026-07-06T11:00:00Z\\",\\"type\\":\\"session_meta\\",\\"payload\\":{"} +
           (with_id ? "\\"id\\":\\"" + id + "\\"," : std::string{}) + "\\"session_id\\":\\"" + id +
           "\\",\\"cwd\\":\\"" + cwd + "\\",\\"cli_version\\":\\"0.144.0\\"}}\\n";
  };
  const auto r449_path = [](const fs::path& r449_store, const std::string& id) {
    return r449_store / "sessions" / "2026" / "07" / "06" / ("rollout-2026-07-06T11-00-00-" + id + ".jsonl");
  };
  constexpr std::size_t kR449Large = 3u * 1024u * 1024u;

  SECTION("R-4.49: an unparseable first line ahead of session_meta still keys the rollout") {
    const auto r449_store = root / "r449-garbage-first-line";
    const std::string id{"019faaaa-bbbb-7ccc-8ddd-eeeeeeee4901"};
    write_file(r449_path(r449_store, id), "not json\\n" + r449_meta(id, "/ws/proj", true) + r449_body(kR449Large));
    const auto r449 = biv::adapters::codex_adapter().collect("/ws/proj", r449_stores(r449_store));
    REQUIRE(r449.has_value());
    REQUIRE(r449->sessions.size() == 1);
    CHECK(r449->sessions.front().original_session_id == id);
    CHECK(r449->sessions.front().original_path == "/ws/proj");
    CHECK(r449->sessions.front().agent_version_at_pack == "0.144.0");
    CHECK(r449->sessions.front().live_at_pack);
  }

  SECTION("R-4.49: the tail facts of a large selected rollout come from its full text") {
    const auto r449_store = root / "r449-terminal-tail";
    const std::string id{"019faaaa-bbbb-7ccc-8ddd-eeeeeeee4902"};
    write_file(r449_path(r449_store, id),
               r449_meta(id, "/ws/proj", true) + r449_body(kR449Large) +
                   "{\\"timestamp\\":\\"2026-07-06T11:59:00Z\\",\\"type\\":\\"task_complete\\",\\"payload\\":{}}\\n");
    const auto r449 = biv::adapters::codex_adapter().collect("/ws/proj", r449_stores(r449_store));
    REQUIRE(r449.has_value());
    REQUIRE(r449->sessions.size() == 1);
    CHECK(r449->sessions.front().original_session_id == id);
    CHECK_FALSE(r449->sessions.front().live_at_pack);
  }

  SECTION("R-4.49: an out-of-root session_meta with a large body is excluded without a warning") {
    const auto r449_store = root / "r449-out-of-root-large";
    const std::string id{"019faaaa-bbbb-7ccc-8ddd-eeeeeeee4903"};
    write_file(r449_path(r449_store, id), r449_meta(id, "/other/project", false) + r449_body(kR449Large));
    const auto r449 = biv::adapters::codex_adapter().collect("/ws/proj", r449_stores(r449_store));
    REQUIRE(r449.has_value());
    CHECK(r449->sessions.empty());
    CHECK_FALSE(std::ranges::any_of(r449->warnings, [&](const std::string& warning) {
      return warning == "SessionIdWithoutId:" + r449_path(r449_store, id).generic_string();
    }));
  }

  SECTION("R-4.49: the in-root SessionIdWithoutId warning still fires from the head facts of a large rollout") {
    const auto r449_store = root / "r449-in-root-no-id-large";
    const std::string id{"019faaaa-bbbb-7ccc-8ddd-eeeeeeee4904"};
    write_file(r449_path(r449_store, id), r449_meta(id, "/ws/proj", false) + r449_body(kR449Large));
    const auto r449 = biv::adapters::codex_adapter().collect("/ws/proj", r449_stores(r449_store));
    REQUIRE(r449.has_value());
    CHECK(r449->sessions.empty());
    CHECK(std::ranges::any_of(r449->warnings, [&](const std::string& warning) {
      return warning == "SessionIdWithoutId:" + r449_path(r449_store, id).generic_string();
    }));
  }
  fs::remove_all(root);
}

TEST_CASE("Codex duplicate-store E-3 warns and picks by declared freshness") {'''
assert t.count(OLD) == 1, t.count(OLD)
t = t.replace(OLD, NEW)
open(p, "w", encoding="utf-8").write(t)
print("test_adapter_codex_collect.cpp patched (rev1: 4 SECTIONs)")
