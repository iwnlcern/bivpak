#!/usr/bin/env python3
# head_reader_claude.py <claude_code.cpp> — R-4.49 claude side (rev1 patcher; every anchor asserted EXACTLY ONCE at the base 4cf135ee bytes;
# any other count = STOP: the base moved). The bound is m-2's C-1 ruling (`170000`): A1 §A1 — stream-scan from the top, the FIRST record
# carrying a `cwd` field keys the session, stop at first hit; no cwd anywhere → whole file, excluded, no_cwd_record. (1) a streaming
# first-cwd reader over ArtifactSource::stream (the sink returns a sentinel error to stop the stream at the end of the first cwd-bearing
# line — the sink contract of secure_io::ReadHandle::stream — consumed here; a real stream error propagates). (2) collect decides
# candidacy from that head cwd; the whole-file source_text + the UNCHANGED inspect_transcript run only for an in-root transcript, so a
# selected session's every field (sessionId, version, cwd) comes from exactly today's parse over exactly today's bytes.
# inspect_transcript itself is NOT touched (its install-side callers unchanged).
import sys
p = sys.argv[1]; t = open(p, encoding="utf-8").read()
def rep(old, new):
    global t
    assert t.count(old) == 1, ("anchor count %d: %s" % (t.count(old), old[:80]))
    t = t.replace(old, new)
OLD_ANCHOR = '''bool terminal_status(const std::string_view status) {'''
NEW_HEAD = '''// R-4.49 (sealed A1 §A1, m-2 C-1 ruling 2026-09-13; fence 142000 §2): the HEAD-BOUNDED read that decides candidacy — the
// source is STREAMED (secure_io::ReadHandle::stream, 8 KiB chunks) and the stream is STOPPED at the end of the FIRST line whose
// record carries a `cwd` field; bytes after that line are never read for a transcript that is not selected. A transcript with no
// cwd-bearing record anywhere is read to EOF (the sealed worst case: excluded and reported as no_cwd_record by the caller).
// Unparseable lines are skipped, as inspect_transcript skips them. The stop is signalled to the stream as a sentinel error and
// consumed here; a real stream error propagates. Line framing is std::getline's: '\\n'-terminated lines, a trailing unterminated
// line counted once. The value returned is exactly the `cwd` inspect_transcript would report for the same bytes (first seen).
constexpr std::string_view kHeadCompleteSentinel = "r449-head-complete";

expected<std::optional<std::string>> first_transcript_cwd(const SessionRecord::ArtifactSource& source) {
  std::optional<std::string> cwd;
  std::string carry;
  const auto absorb = [&](const std::string_view line) {
    simdjson::padded_string padded{line};
    simdjson::dom::parser parser;
    auto object = parse_json_object(parser, padded);
    if (!object.has_value()) {
      return false;
    }
    cwd = object_string(*object, "cwd");
    return cwd.has_value();
  };
  auto read = source.stream([&](const std::span<const std::byte> chunk) -> expected<void> {
    for (const auto byte : chunk) {
      carry.push_back(static_cast<char>(byte));
    }
    std::size_t start = 0;
    for (auto newline = carry.find('\\n', start); newline != std::string::npos;
         newline = carry.find('\\n', start)) {
      const std::string_view line = std::string_view{carry}.substr(start, newline - start);
      start = newline + 1;
      if (absorb(line)) {
        break;
      }
    }
    carry.erase(0, start);
    if (cwd.has_value()) {
      return std::unexpected(BivError{ErrKind::InternalError, {}, std::string{kHeadCompleteSentinel}});
    }
    return {};
  });
  if (!read) {
    if (cwd.has_value() && read.error().detail == kHeadCompleteSentinel) {
      return cwd;
    }
    return std::unexpected(read.error());
  }
  if (!carry.empty()) {
    absorb(carry);
  }
  return cwd;
}

bool terminal_status(const std::string_view status) {'''
rep(OLD_ANCHOR, NEW_HEAD)
OLD_COLLECT = '''            auto main_text = source_text(*main_source);
            if (!main_text) {
              return std::unexpected(main_text.error());
            }
            auto facts = inspect_transcript(*main_text);
            if (!facts.cwd.has_value()) {
              if (project_key_matches_source) {
                report.no_cwd_record.push_back(entry.path().generic_string());
              }
              continue;
            }
            if (!rewrite::path_is_same_or_descendant(rewrite::PathMembership{
                    .candidate = *facts.cwd,
                    .root = source_root.generic_string()})) {
              continue;
            }
'''
NEW_COLLECT = '''            // R-4.49: candidacy from the HEAD only — the first cwd-bearing record (A1 §A1), streamed and stopped there; a
            // transcript with no cwd anywhere is read to EOF and reported (sealed); a transcript whose first cwd is outside the
            // source root is never read past that line. The FULL read and the unchanged whole-text parse below run only for an
            // in-root transcript, so every selected field (sessionId, version) is today's; its cwd IS the head's first-seen cwd —
            // inspect_transcript applies the same first-seen rule over the same bytes (the SECTIONs and LEG 3 measure this).
            auto head_cwd = first_transcript_cwd(*main_source);
            if (!head_cwd) {
              return std::unexpected(head_cwd.error());
            }
            if (!head_cwd->has_value()) {
              if (project_key_matches_source) {
                report.no_cwd_record.push_back(entry.path().generic_string());
              }
              continue;
            }
            if (!rewrite::path_is_same_or_descendant(rewrite::PathMembership{
                    .candidate = **head_cwd,
                    .root = source_root.generic_string()})) {
              continue;
            }
            auto main_text = source_text(*main_source);
            if (!main_text) {
              return std::unexpected(main_text.error());
            }
            auto facts = inspect_transcript(*main_text);
            facts.cwd = *head_cwd;
'''
rep(OLD_COLLECT, NEW_COLLECT)
open(p, "w", encoding="utf-8").write(t)
print("claude_code.cpp patched (rev1)")
