#!/usr/bin/env python3
# head_reader_codex.py <codex.cpp> — R-4.49 codex side (rev0 DRAFT patcher; anchors asserted EXACTLY ONCE at the base 4cf135ee bytes).
# (1) inspect_rollout_head's per-line body becomes absorb_rollout_line (the FIRST session_meta record completes the head; every other
# line is skipped — the same rule); inspect_rollout_head keeps its signature and semantics. (2) a streaming head reader over
# ArtifactSource::stream (same sentinel shape as the claude side). (3) collect reads the head first; the FULL read (source_text) moves
# BELOW the cwd filter so it happens only for in-root candidates, whose tail facts (has_terminal_tail_record, newest_rollout_timestamp)
# keep their full-text inputs — V-LS-4.
import sys
p = sys.argv[1]; t = open(p, encoding="utf-8").read()
def rep(old, new):
    global t
    assert t.count(old) == 1, ("anchor count %d: %s" % (t.count(old), old[:80]))
    t = t.replace(old, new)
OLD_HEAD = '''RolloutFacts inspect_rollout_head(const std::string_view rollout) {
  RolloutFacts facts;
  std::istringstream input{std::string{rollout}};
  std::string line;
  while (std::getline(input, line)) {
    simdjson::padded_string padded{line};
    simdjson::dom::parser parser;
    auto object = parse_json_object(parser, padded);
    if (!object) {
      continue;
    }
    auto type = object_string(*object, "type");
    if (!type || *type != "session_meta") {
      continue;
    }
    auto payload = object_object(*object, "payload");
    if (!payload) {
      continue;
    }
    if (!facts.id.has_value()) {
      facts.id = object_string(*payload, "id");
    }
    if (!facts.session_id.has_value()) facts.session_id = object_string(*payload, "session_id");
    if (!facts.cwd.has_value()) {
      facts.cwd = object_string(*payload, "cwd");
    }
    if (!facts.cli_version.has_value()) {
      facts.cli_version = object_string(*payload, "cli_version");
    }
    if (const auto direct = object_string(*payload, "parent_thread_id");
        direct.has_value()) {
      facts.parent_ids.push_back(*direct);
    }
    if (const auto nested = nested_parent_id(*payload); nested.has_value()) {
      facts.parent_ids.push_back(*nested);
    }
    if (!facts.parent_ids.empty()) {
      facts.parent_id = facts.parent_ids.front();
    }
    return facts;
  }
  return facts;
}
'''
NEW_HEAD = '''// R-4.49 (sealed c1 §4; fence 142000 §2): ONE rollout line absorbed into the head facts — the FIRST session_meta record
// completes the head (exactly the rule inspect_rollout_head has always applied); any other line is skipped.
bool absorb_rollout_line(RolloutFacts& facts, const std::string_view line) {
  simdjson::padded_string padded{line};
  simdjson::dom::parser parser;
  auto object = parse_json_object(parser, padded);
  if (!object) {
    return false;
  }
  auto type = object_string(*object, "type");
  if (!type || *type != "session_meta") {
    return false;
  }
  auto payload = object_object(*object, "payload");
  if (!payload) {
    return false;
  }
  if (!facts.id.has_value()) {
    facts.id = object_string(*payload, "id");
  }
  if (!facts.session_id.has_value()) facts.session_id = object_string(*payload, "session_id");
  if (!facts.cwd.has_value()) {
    facts.cwd = object_string(*payload, "cwd");
  }
  if (!facts.cli_version.has_value()) {
    facts.cli_version = object_string(*payload, "cli_version");
  }
  if (const auto direct = object_string(*payload, "parent_thread_id");
      direct.has_value()) {
    facts.parent_ids.push_back(*direct);
  }
  if (const auto nested = nested_parent_id(*payload); nested.has_value()) {
    facts.parent_ids.push_back(*nested);
  }
  if (!facts.parent_ids.empty()) {
    facts.parent_id = facts.parent_ids.front();
  }
  return true;
}

RolloutFacts inspect_rollout_head(const std::string_view rollout) {
  RolloutFacts facts;
  std::istringstream input{std::string{rollout}};
  std::string line;
  while (std::getline(input, line)) {
    if (absorb_rollout_line(facts, line)) {
      return facts;
    }
  }
  return facts;
}

// R-4.49: the HEAD-BOUNDED read for candidacy — streamed, stopped at the end of the first session_meta line (observed on the
// evidence host: line 1 of 1,503/1,503 rollouts; at most 22,552 bytes); a rollout with no session_meta record is read to EOF and
// is not a candidate, as today. Sentinel-stop over secure_io::ReadHandle::stream; a real stream error propagates.
constexpr std::string_view kHeadCompleteSentinel = "r449-head-complete";

expected<RolloutFacts> inspect_rollout_head_stream(const SessionRecord::ArtifactSource& source) {
  RolloutFacts facts;
  std::string carry;
  bool complete = false;
  auto read = source.stream([&](const std::span<const std::byte> chunk) -> expected<void> {
    for (const auto byte : chunk) {
      carry.push_back(static_cast<char>(byte));
    }
    std::size_t start = 0;
    for (auto newline = carry.find('\\n', start); newline != std::string::npos;
         newline = carry.find('\\n', start)) {
      const std::string_view line = std::string_view{carry}.substr(start, newline - start);
      start = newline + 1;
      if (absorb_rollout_line(facts, line)) {
        complete = true;
        break;
      }
    }
    carry.erase(0, start);
    if (complete) {
      return std::unexpected(BivError{ErrKind::InternalError, {}, std::string{kHeadCompleteSentinel}});
    }
    return {};
  });
  if (!read) {
    if (complete && read.error().detail == kHeadCompleteSentinel) {
      return facts;
    }
    return std::unexpected(read.error());
  }
  if (!carry.empty()) {
    absorb_rollout_line(facts, carry);
  }
  return facts;
}
'''
rep(OLD_HEAD, NEW_HEAD)
OLD_COLLECT = '''            auto source = open_artifact_source(path);
            if (!source) {
              return std::unexpected(source.error());
            }
            auto text = source_text(*source);
            if (!text) {
              return std::unexpected(text.error());
            }
            auto facts = inspect_rollout_head(*text);
            const bool in_source_root ='''
NEW_COLLECT = '''            auto source = open_artifact_source(path);
            if (!source) {
              return std::unexpected(source.error());
            }
            // R-4.49: candidacy from the HEAD only; the full read moves below the cwd filter (in-root candidates only).
            auto head = inspect_rollout_head_stream(*source);
            if (!head) {
              return std::unexpected(head.error());
            }
            auto facts = std::move(*head);
            const bool in_source_root ='''
rep(OLD_COLLECT, NEW_COLLECT)
OLD_AFTER = '''            if (!facts.id || !in_source_root) {
              continue;
            }
            const auto mtime = fs::last_write_time(path, ec);'''
NEW_AFTER = '''            if (!facts.id || !in_source_root) {
              continue;
            }
            // R-4.49: the FULL read — for an in-root candidate only (V-LS-4: tail facts from the whole text).
            auto text = source_text(*source);
            if (!text) {
              return std::unexpected(text.error());
            }
            const auto mtime = fs::last_write_time(path, ec);'''
rep(OLD_AFTER, NEW_AFTER)
open(p, "w", encoding="utf-8").write(t)
print("codex.cpp patched (rev0 draft)")
