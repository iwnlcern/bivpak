#include "cli/args.hpp"

#include <optional>
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

}  // namespace

bool contains_json(int argc, char* argv[]) {
  for (int i = 1; i < argc; ++i) {
    if (std::string_view{argv[i]} == "--json") {
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

expected<Command> parse_args(int argc, char* argv[]) {
  Command command;
  command.json = contains_json(argc, argv);

  std::vector<std::string_view> tokens;
  for (int i = 1; i < argc; ++i) {
    const std::string_view arg{argv[i]};
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
      if (is_flag(tokens[i])) {
        return std::unexpected(usage("unknown-flag"));
      }
      if (dir.has_value()) {
        return std::unexpected(usage("too-many-args"));
      }
      dir = std::filesystem::path{tokens[i]};
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
      const auto arg = tokens[i];
      if (arg == "--dest") {
        if (i + 1U >= tokens.size()) {
          return std::unexpected(usage("missing-dest"));
        }
        command.open_options.dest = std::filesystem::path{tokens[++i]};
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
