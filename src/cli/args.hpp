#pragma once

#include <filesystem>

#include "core/open/open.hpp"
#include "core/support/error.hpp"

namespace biv::cli {

enum class Verb { pack, open, list, info };

struct Command {
  Verb verb{Verb::pack};
  bool json{false};
  std::filesystem::path pack_dir;
  biv::open::OpenOptions open_options;
};

bool contains_json(int argc, char* argv[]);
expected<Command> parse_args(int argc, char* argv[]);
const char* verb_name(Verb verb) noexcept;

}  // namespace biv::cli
