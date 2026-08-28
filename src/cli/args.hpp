#pragma once

#include <filesystem>
#include <map>
#include <span>
#include <string>
#include <string_view>

#include "core/open/consent.hpp"
#include "core/open/open.hpp"
#include "core/support/error.hpp"

namespace biv::cli {

enum class Verb { pack, open, list, info };

struct Command {
  Verb verb{Verb::pack};
  bool json{false};
  bool help{false};
  bool accept_url_divergence{false};
  std::filesystem::path pack_dir;
  biv::open::OpenOptions open_options;
  core_sessions::ConsentSpec consent;
  std::map<std::string, std::filesystem::path> agent_bins;
};

bool contains_json(std::span<char* const> args);
expected<Command> parse_args(std::span<char* const> args);
const char* verb_name(Verb verb) noexcept;
std::string help_text(Verb verb);

}  // namespace biv::cli
