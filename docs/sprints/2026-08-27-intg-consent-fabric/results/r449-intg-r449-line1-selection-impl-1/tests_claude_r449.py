#!/usr/bin/env python3
# tests_claude_r449.py <tests/test_adapter_claude_collect.cpp> — R-4.49 witness SECTIONs inside the EXISTING TEST_CASE "Claude adapter keys
# membership on the first cwd record" (the Catch2 case census — the workflow's count-gate cells — does not move). Anchor asserted EXACTLY ONCE.
import sys
p = sys.argv[1]; t = open(p, encoding="utf-8").read()
OLD = '''  REQUIRE(report.has_value());
  CHECK(report->sessions.empty());
  fs::remove_all(root);
}

TEST_CASE("Claude adapter matches Windows cwd to its WSL workspace") {'''
NEW = '''  REQUIRE(report.has_value());
  CHECK(report->sessions.empty());

  // R-4.49 (A1 §A1: the FIRST cwd-bearing record keys the session; fence 142000 §2 V-LS-2): membership and every record field
  // are the same whatever lies behind the first cwd-bearing record and however large the transcript is. These SECTIONs are the
  // corpus oracle for the head-bounded candidacy read; the read-cost witness (bytes read per file) is evidence, not a test.
  const auto r449_stores = [](const fs::path& r449_store) {
    return std::vector<biv::adapters::Store>{biv::adapters::Store{
        .root = r449_store,
        .locators = {biv::adapters::StoreLocator{.kind = "sessions_root",
                                                 .path = r449_store / "projects"}},
        .tier = biv::adapters::DiscoveryTier::defaults,
        .archived = false}};
  };
  const auto r449_body = [](const std::size_t bytes) {
    const std::string line = "{\\"type\\":\\"assistant\\",\\"message\\":{\\"role\\":\\"assistant\\",\\"content\\":\\"" +
                             std::string(1000, 'y') + "\\"}}\\n";
    std::string body;
    while (body.size() < bytes) {
      body += line;
    }
    return body;
  };
  constexpr std::size_t kR449Large = 3u * 1024u * 1024u;

  SECTION("R-4.49: enrichment fields behind the first cwd record still key the selected session") {
    const auto r449_store = root / "r449-enrichment-later";
    const std::string id{"aaaaaaaa-1111-4000-8000-000000004901"};
    write_file(r449_store / "projects" / "-ws-proj" / (id + ".jsonl"),
               "{\\"type\\":\\"user\\",\\"cwd\\":\\"/ws/proj\\"}\\n"
               "{\\"type\\":\\"assistant\\",\\"cwd\\":\\"/ws/proj\\",\\"sessionId\\":\\"" +
                   id + "\\",\\"version\\":\\"2.1.202\\"}\\n" + r449_body(kR449Large));
    const auto r449 = biv::adapters::claude_code_adapter().collect("/ws/proj", r449_stores(r449_store));
    REQUIRE(r449.has_value());
    REQUIRE(r449->sessions.size() == 1);
    CHECK(r449->sessions.front().original_session_id == id);
    CHECK(r449->sessions.front().original_path == "/ws/proj");
    CHECK(r449->sessions.front().agent_version_at_pack == "2.1.202");
    REQUIRE(r449->sessions.front().artifacts.size() == 1);
    CHECK(r449->no_cwd_record.empty());
  }

  SECTION("R-4.49: an out-of-root first cwd record without enrichment fields is excluded silently however large the file") {
    const auto r449_store = root / "r449-out-of-root-no-enrichment";
    const std::string id{"aaaaaaaa-1111-4000-8000-000000004902"};
    write_file(r449_store / "projects" / "-other-proj" / (id + ".jsonl"),
               "{\\"type\\":\\"user\\",\\"cwd\\":\\"/other/proj\\"}\\n" + r449_body(kR449Large));
    const auto r449 = biv::adapters::claude_code_adapter().collect("/ws/proj", r449_stores(r449_store));
    REQUIRE(r449.has_value());
    CHECK(r449->sessions.empty());
    CHECK(r449->no_cwd_record.empty());
  }

  SECTION("R-4.49: a large transcript with no cwd record anywhere is excluded and reported") {
    const auto r449_store = root / "r449-no-cwd";
    const std::string id{"aaaaaaaa-1111-4000-8000-000000004903"};
    write_file(r449_store / "projects" / "-ws-proj" / (id + ".jsonl"),
               "{\\"type\\":\\"summary\\",\\"sessionId\\":\\"" + id + "\\",\\"version\\":\\"2.1.202\\"}\\n" +
                   r449_body(kR449Large));
    const auto r449 = biv::adapters::claude_code_adapter().collect("/ws/proj", r449_stores(r449_store));
    REQUIRE(r449.has_value());
    CHECK(r449->sessions.empty());
    REQUIRE(r449->no_cwd_record.size() == 1);
    CHECK(r449->no_cwd_record.front().find(id) != std::string::npos);
  }

  SECTION("R-4.49: metadata-first head with the first cwd on line 5 and a large body is selected with today's fields") {
    const auto r449_store = root / "r449-metadata-first";
    const std::string id{"aaaaaaaa-1111-4000-8000-000000004904"};
    write_file(r449_store / "projects" / "-ws-proj" / (id + ".jsonl"),
               "{\\"type\\":\\"last-prompt\\",\\"sessionId\\":\\"" + id + "\\"}\\n"
               "{\\"type\\":\\"mode\\",\\"sessionId\\":\\"" + id + "\\"}\\n"
               "{\\"type\\":\\"permission-mode\\",\\"sessionId\\":\\"" + id + "\\"}\\n"
               "not json\\n"
               "{\\"type\\":\\"user\\",\\"cwd\\":\\"/ws/proj\\",\\"sessionId\\":\\"" + id +
                   "\\",\\"version\\":\\"2.1.202\\"}\\n" + r449_body(kR449Large));
    const auto r449 = biv::adapters::claude_code_adapter().collect("/ws/proj", r449_stores(r449_store));
    REQUIRE(r449.has_value());
    REQUIRE(r449->sessions.size() == 1);
    CHECK(r449->sessions.front().original_session_id == id);
    CHECK(r449->sessions.front().agent_version_at_pack == "2.1.202");
    CHECK(r449->no_cwd_record.empty());
  }

  SECTION("R-4.49: the first cwd on an unterminated final line still keys the session") {
    const auto r449_store = root / "r449-unterminated";
    const std::string id{"aaaaaaaa-1111-4000-8000-000000004905"};
    write_file(r449_store / "projects" / "-ws-proj" / (id + ".jsonl"),
               "{\\"type\\":\\"user\\",\\"cwd\\":\\"/ws/proj\\",\\"sessionId\\":\\"" + id +
                   "\\",\\"version\\":\\"2.1.202\\"}");
    const auto r449 = biv::adapters::claude_code_adapter().collect("/ws/proj", r449_stores(r449_store));
    REQUIRE(r449.has_value());
    REQUIRE(r449->sessions.size() == 1);
    CHECK(r449->sessions.front().original_session_id == id);
  }
  fs::remove_all(root);
}

TEST_CASE("Claude adapter matches Windows cwd to its WSL workspace") {'''
assert t.count(OLD) == 1, t.count(OLD)
t = t.replace(OLD, NEW)
open(p, "w", encoding="utf-8").write(t)
print("test_adapter_claude_collect.cpp patched (rev1: 5 SECTIONs)")
