#include "core/manifest/manifest.hpp"

#include <cstdint>
#include <string_view>

#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-literal-operator"
#endif
#include <simdjson.h>
#if defined(__GNUC__)
#pragma GCC diagnostic pop
#endif

#include "core/json/writer.hpp"
#include "core/support/version.hpp"

namespace biv::manifest {

namespace {

expected<std::string> required_string(simdjson::dom::object object, std::string_view key) {
  std::string_view value;
  const auto error = object[key].get(value);
  if (error) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, std::string{key}});
  }
  return std::string{value};
}

expected<int> required_int(simdjson::dom::object object, std::string_view key) {
  int64_t value = 0;
  const auto error = object[key].get(value);
  if (error) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, std::string{key}});
  }
  return static_cast<int>(value);
}

expected<std::vector<std::string>> required_string_array(simdjson::dom::object object,
                                                         std::string_view key) {
  simdjson::dom::array array;
  if (const auto error = object[key].get(array); error) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, std::string{key}});
  }
  std::vector<std::string> out;
  for (auto element : array) {
    std::string_view value;
    if (const auto error = element.get(value); error) {
      return std::unexpected(BivError{ErrKind::ParseError, {}, std::string{key}});
    }
    out.emplace_back(value);
  }
  return out;
}

expected<void> require_empty_array(simdjson::dom::object object, std::string_view key) {
  simdjson::dom::element element;
  if (const auto error = object[key].get(element); error == simdjson::NO_SUCH_FIELD) {
    return {};
  } else if (error) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, std::string{key}});
  }

  simdjson::dom::array array;
  if (const auto error = element.get(array); error) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, std::string{key}});
  }
  if (array.size() != 0U) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, "step2-plain-dir-only"});
  }
  return {};
}

}  // namespace

std::string to_string(const PathFlavor flavor) {
  switch (flavor) {
    case PathFlavor::posix:
      return "posix";
    case PathFlavor::windows:
      return "windows";
    case PathFlavor::wsl:
      return "wsl";
  }
  return "posix";
}

expected<PathFlavor> parse_path_flavor(const std::string_view value) {
  if (value == "posix") {
    return PathFlavor::posix;
  }
  if (value == "windows") {
    return PathFlavor::windows;
  }
  if (value == "wsl") {
    return PathFlavor::wsl;
  }
  return std::unexpected(BivError{ErrKind::ParseError, {}, "source_path_flavor"});
}

std::string serialize(const Manifest& manifest) {
  json::Writer writer;
  writer.begin_object();
  writer.key("format_version");
  writer.value_int(manifest.format_version);
  writer.key("required_capabilities");
  writer.begin_array();
  for (const auto& capability : manifest.required_capabilities) {
    writer.value_string(capability);
  }
  writer.end_array();
  writer.key("image_id");
  writer.value_string(manifest.image_id);
  writer.key("app_version");
  writer.value_string(manifest.app_version.empty() ? app_version() : manifest.app_version);
  writer.key("created_at");
  writer.value_string(manifest.created_at);
  writer.key("source_path");
  writer.value_string(manifest.source_path);
  writer.key("source_path_flavor");
  writer.value_string(to_string(manifest.source_path_flavor));
  writer.key("bivignore");
  writer.begin_object();
  writer.key("source");
  writer.value_string(manifest.bivignore.source);
  writer.key("builtin_id");
  if (manifest.bivignore.builtin_id.has_value()) {
    writer.value_string(*manifest.bivignore.builtin_id);
  } else {
    writer.value_null();
  }
  writer.key("sha256");
  writer.value_string(manifest.bivignore.sha256_hex);
  writer.end_object();
  writer.key("repos");
  writer.begin_array();
  writer.end_array();
  writer.key("agent_sessions");
  writer.begin_array();
  writer.end_array();
  writer.end_object();
  return writer.take();
}

expected<Manifest> parse(const std::span<const std::byte> bytes) {
  if (bytes.empty() || bytes.size() > kManifestByteCap) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, "manifest-size"});
  }

  try {
    std::string text;
    text.resize(bytes.size());
    for (size_t i = 0; i < bytes.size(); ++i) {
      text[i] = static_cast<char>(bytes[i]);
    }

    simdjson::dom::parser parser;
    simdjson::dom::element root;
    if (const auto error = parser.parse(text).get(root); error) {
      return std::unexpected(BivError{ErrKind::ParseError, {}, error_message(error)});
    }
    simdjson::dom::object object;
    if (const auto error = root.get(object); error) {
      return std::unexpected(BivError{ErrKind::ParseError, {}, "root"});
    }

    Manifest manifest;
    auto version = required_int(object, "format_version");
    if (!version) {
      return std::unexpected(version.error());
    }
    manifest.format_version = *version;

    auto capabilities = required_string_array(object, "required_capabilities");
    if (!capabilities) {
      return std::unexpected(capabilities.error());
    }
    manifest.required_capabilities = std::move(*capabilities);

    auto image_id = required_string(object, "image_id");
    auto app_version_value = required_string(object, "app_version");
    auto created_at = required_string(object, "created_at");
    auto source_path = required_string(object, "source_path");
    auto source_flavor = required_string(object, "source_path_flavor");
    if (!image_id || !app_version_value || !created_at || !source_path || !source_flavor) {
      return std::unexpected(BivError{ErrKind::ParseError, {}, "manifest-field"});
    }
    manifest.image_id = std::move(*image_id);
    manifest.app_version = std::move(*app_version_value);
    manifest.created_at = std::move(*created_at);
    manifest.source_path = std::move(*source_path);
    auto flavor = parse_path_flavor(*source_flavor);
    if (!flavor) {
      return std::unexpected(flavor.error());
    }
    manifest.source_path_flavor = *flavor;

    simdjson::dom::object bivignore;
    if (const auto error = object["bivignore"].get(bivignore); error) {
      return std::unexpected(BivError{ErrKind::ParseError, {}, "bivignore"});
    }
    auto bivignore_source = required_string(bivignore, "source");
    auto bivignore_sha = required_string(bivignore, "sha256");
    if (!bivignore_source || !bivignore_sha) {
      return std::unexpected(BivError{ErrKind::ParseError, {}, "bivignore-field"});
    }
    manifest.bivignore.source = std::move(*bivignore_source);
    manifest.bivignore.sha256_hex = std::move(*bivignore_sha);
    simdjson::dom::element builtin_id;
    if (const auto error = bivignore["builtin_id"].get(builtin_id); !error) {
      if (builtin_id.is_null()) {
        manifest.bivignore.builtin_id = std::nullopt;
      } else {
        std::string_view value;
        if (const auto string_error = builtin_id.get(value); string_error) {
          return std::unexpected(BivError{ErrKind::ParseError, {}, "builtin_id"});
        }
        manifest.bivignore.builtin_id = std::string{value};
      }
    } else if (error != simdjson::NO_SUCH_FIELD) {
      return std::unexpected(BivError{ErrKind::ParseError, {}, "builtin_id"});
    }

    auto repos = require_empty_array(object, "repos");
    if (!repos) {
      return std::unexpected(repos.error());
    }
    auto sessions = require_empty_array(object, "agent_sessions");
    if (!sessions) {
      return std::unexpected(sessions.error());
    }

    return manifest;
  } catch (const simdjson::simdjson_error& error) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, error.what()});
  } catch (...) {
    return std::unexpected(BivError{ErrKind::InternalError, {}, "manifest-parse"});
  }
}

}  // namespace biv::manifest
