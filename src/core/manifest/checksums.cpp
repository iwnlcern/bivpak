#include "core/manifest/checksums.hpp"

#include <string_view>

#if defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-literal-operator"
#endif
#include <simdjson.h>
#if defined(__clang__)
#pragma GCC diagnostic pop
#endif

#include "core/json/writer.hpp"

namespace biv::manifest {

namespace {

expected<std::string> parse_string(simdjson::dom::element element, std::string_view detail) {
  std::string_view value;
  if (const auto error = element.get(value); error) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, std::string{detail}});
  }
  return std::string{value};
}

bool starts_with_json_object(std::string_view text) {
  const auto pos = text.find_first_not_of(" \t\r\n");
  return pos != std::string_view::npos && text.at(pos) == '{';
}

}  // namespace

bool is_sha256_hex(const std::string_view value) {
  if (value.size() != 64U) {
    return false;
  }
  for (const char ch : value) {
    const bool digit = ch >= '0' && ch <= '9';
    const bool lower = ch >= 'a' && ch <= 'f';
    const bool upper = ch >= 'A' && ch <= 'F';
    if (!digit && !lower && !upper) {
      return false;
    }
  }
  return true;
}

std::string serialize(const Checksums& checksums) {
  json::Writer writer;
  writer.begin_object();
  writer.key("algo");
  writer.value_string("sha256");
  writer.key("entries");
  writer.begin_object();
  for (const auto& [path, digest] : checksums.entries) {
    writer.key(path);
    writer.value_string(digest);
  }
  writer.end_object();
  writer.end_object();
  return writer.take();
}

expected<Checksums> parse_checksums(const std::span<const std::byte> bytes) {
  if (bytes.empty() || bytes.size() > kChecksumsByteCap) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, "checksums-size"});
  }

  try {
    std::string text;
    text.reserve(bytes.size());
    for (const std::byte byte : bytes) {
      text.push_back(static_cast<char>(byte));
    }
    if (!starts_with_json_object(text)) {
      return std::unexpected(BivError{ErrKind::ParseError, {}, "root"});
    }

    simdjson::padded_string padded{text.data(), text.size()};
    if (padded.data() == nullptr) {
      return std::unexpected(BivError{ErrKind::InternalError, {}, "checksums-alloc"});
    }
    simdjson::dom::parser parser;
    simdjson::dom::element root;
    if (const auto error = parser.parse(padded).get(root); error) {
      return std::unexpected(BivError{ErrKind::ParseError, {}, error_message(error)});
    }
    simdjson::dom::object object;
    if (const auto error = root.get(object); error) {
      return std::unexpected(BivError{ErrKind::ParseError, {}, "root"});
    }

    auto algo = parse_string(object.at_key("algo"), "algo");
    if (!algo || *algo != "sha256") {
      return std::unexpected(BivError{ErrKind::ParseError, {}, "algo"});
    }

    simdjson::dom::object entries_object;
    if (const auto error = object.at_key("entries").get(entries_object); error) {
      return std::unexpected(BivError{ErrKind::ParseError, {}, "entries"});
    }

    Checksums checksums;
    for (auto field : entries_object) {
      auto digest = parse_string(field.value, "digest");
      if (!digest || !is_sha256_hex(*digest)) {
        return std::unexpected(BivError{ErrKind::ParseError, {}, "digest"});
      }
      checksums.entries.emplace(std::string{field.key}, std::move(*digest));
    }
    return checksums;
  } catch (const simdjson::simdjson_error& error) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, error.what()});
  } catch (...) {
    return std::unexpected(BivError{ErrKind::InternalError, {}, "checksums-parse"});
  }
}

}  // namespace biv::manifest
