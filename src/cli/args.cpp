#include "cli/args.hpp"

#include <optional>
#include <set>
#include <string>
#include <string_view>
#include <vector>

namespace biv::cli {

namespace {

bool is_flag(std::string_view arg) {
  return arg.starts_with("--");
}

BivError usage(std::string_view detail) {
  return BivError{ErrKind::UsageError, {}, std::string{detail}};
}

bool valid_agent_id(const std::string_view value) {
  if (value.empty() || value.front() < 'a' || value.front() > 'z') {
    if (value.empty() || value.front() < '0' || value.front() > '9') {
      return false;
    }
  }
  for (const char ch : value) {
    const bool lower = ch >= 'a' && ch <= 'z';
    const bool digit = ch >= '0' && ch <= '9';
    if (!lower && !digit && ch != '.' && ch != '_' && ch != '-') {
      return false;
    }
  }
  return true;
}

expected<core_sessions::ConsentSpec> parse_consent(const std::string_view value) {
  core_sessions::ConsentSpec spec;
  if (value == "yes") {
    spec.global = core_sessions::ConsentValue::yes;
    return spec;
  }
  if (value == "no") {
    spec.global = core_sessions::ConsentValue::no;
    return spec;
  }

  std::set<std::string> seen;
  size_t start = 0;
  while (start <= value.size()) {
    const size_t comma = value.find(',', start);
    const auto item = value.substr(start, comma == std::string_view::npos ? value.size() - start : comma - start);
    const size_t equals = item.find('=');
    if (equals == std::string_view::npos || item.find('=', equals + 1U) != std::string_view::npos) {
      return std::unexpected(usage("consent-value-invalid"));
    }
    const auto agent = item.substr(0, equals);
    const auto decision = item.substr(equals + 1U);
    if (!valid_agent_id(agent)) {
      return std::unexpected(usage("consent-agent-grammar"));
    }
    if (!seen.insert(std::string{agent}).second) {
      return std::unexpected(usage("consent-duplicate-agent"));
    }
    core_sessions::ConsentValue parsed = core_sessions::ConsentValue::unset;
    if (decision == "yes") {
      parsed = core_sessions::ConsentValue::yes;
    } else if (decision == "no") {
      parsed = core_sessions::ConsentValue::no;
    } else {
      return std::unexpected(usage("consent-value-invalid"));
    }
    spec.per_agent.emplace_back(agent, parsed);
    if (comma == std::string_view::npos) {
      break;
    }
    start = comma + 1U;
  }
  if (spec.per_agent.empty()) {
    return std::unexpected(usage("consent-value-invalid"));
  }
  return spec;
}

}  // namespace

bool contains_json(std::span<char* const> args) {
  for (char* arg : args.subspan(1)) {
    if (std::string_view{arg} == "--json") {
      return true;
    }
  }
  return false;
}

const char* verb_name(const Verb verb) noexcept {
  switch (verb) {
    case Verb::pack:
      return "pack";
    case Verb::open:
      return "open";
    case Verb::list:
      return "list";
    case Verb::info:
      return "info";
  }
  return "pack";
}

expected<Command> parse_args(std::span<char* const> args) {
  Command command;
  command.json = contains_json(args);

  std::vector<std::string_view> tokens;
  for (char* raw_arg : args.subspan(1)) {
    const std::string_view arg{raw_arg};
    if (arg != "--json") {
      tokens.push_back(arg);
    }
  }
  if (tokens.empty()) {
    return std::unexpected(usage("missing-verb"));
  }

  const auto verb = tokens.front();
  if (verb == "pack") {
    command.verb = Verb::pack;
    std::optional<std::filesystem::path> dir;
    for (size_t i = 1; i < tokens.size(); ++i) {
      if (is_flag(tokens.at(i))) {
        return std::unexpected(usage("unknown-flag"));
      }
      if (dir.has_value()) {
        return std::unexpected(usage("too-many-args"));
      }
      dir = std::filesystem::path{tokens.at(i)};
    }
    if (!dir.has_value()) {
      return std::unexpected(usage("missing-dir"));
    }
    command.pack_dir = *dir;
    return command;
  }

  if (verb == "open") {
    command.verb = Verb::open;
    std::optional<std::filesystem::path> image;
    bool saw_rename = false;
    bool saw_abort = false;
    for (size_t i = 1; i < tokens.size(); ++i) {
      const auto arg = tokens.at(i);
      if (arg == "--dest") {
        if (i + 1U >= tokens.size()) {
          return std::unexpected(usage("missing-dest"));
        }
        ++i;
        command.open_options.dest = std::filesystem::path{tokens.at(i)};
      } else if (arg == "--consent") {
        if (i + 1U >= tokens.size()) {
          return std::unexpected(usage("consent-value-invalid"));
        }
        ++i;
        auto consent = parse_consent(tokens.at(i));
        if (!consent) {
          return std::unexpected(consent.error());
        }
        command.consent = std::move(*consent);
      } else if (arg == "--rename") {
        saw_rename = true;
        command.open_options.collision = biv::open::Collision::rename;
      } else if (arg == "--abort-on-collision") {
        saw_abort = true;
        command.open_options.collision = biv::open::Collision::abort_preset;
      } else if (arg == "--verify") {
        command.open_options.verify = true;
      } else if (is_flag(arg)) {
        return std::unexpected(usage("unknown-flag"));
      } else if (!image.has_value()) {
        image = std::filesystem::path{arg};
      } else {
        return std::unexpected(usage("too-many-args"));
      }
    }
    if (saw_rename && saw_abort) {
      return std::unexpected(usage("collision-mode-conflict"));
    }
    if (!image.has_value()) {
      return std::unexpected(usage("missing-image"));
    }
    command.open_options.image = *image;
    return command;
  }

  if (verb == "list") {
    command.verb = Verb::list;
    return command;
  }
  if (verb == "info") {
    command.verb = Verb::info;
    return command;
  }

  return std::unexpected(usage("unknown-verb"));
}

}  // namespace biv::cli
