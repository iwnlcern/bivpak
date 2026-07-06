#include <exception>
#include <filesystem>
#include <iostream>
#include <optional>
#include <span>

#include <unistd.h>

#include "cli/args.hpp"
#include "core/pack/pack.hpp"
#include "core/report/envelope.hpp"
#include "core/report/exit_map.hpp"
#include "core/support/version.hpp"

namespace {

int emit_error(std::string_view verb, const biv::BivError& error, bool json) {
  const int exit_code = biv::report::exit_for_error(error.kind);
  if (json) {
    std::cout << biv::report::envelope(verb, std::nullopt, std::nullopt, error, exit_code);
  } else {
    std::cerr << "biv: " << biv::to_string(error.kind);
    if (!error.detail.empty()) {
      std::cerr << ": " << error.detail;
    }
    std::cerr << '\n';
  }
  return exit_code;
}

void emit_pack_text(const biv::pack::PackReport& report) {
  for (const auto& advisory : report.advisories) {
    if (advisory.kind == "prune-summary") {
      std::cout << "pruned " << advisory.entries.size() << " path(s)\n";
    }
  }
}

std::filesystem::path default_dest_for(const std::filesystem::path& image) {
  auto name = image.filename().generic_string();
  if (name.ends_with(".bvpk")) {
    name.resize(name.size() - 5U);
  }
  return std::filesystem::current_path() / name;
}

void maybe_prompt_collision(biv::open::OpenOptions& options, bool json) {
  if (json || options.collision != biv::open::Collision::refuse ||
      ::isatty(STDIN_FILENO) == 0 || ::isatty(STDERR_FILENO) == 0) {
    return;
  }
  const auto dest = options.dest.value_or(default_dest_for(options.image)).lexically_normal();
  std::error_code ec;
  if (!std::filesystem::exists(dest, ec)) {
    return;
  }

  std::cerr << "destination exists: " << dest.generic_string() << "\n[r]ename/[a]bort? " << std::flush;
  char choice = '\0';
  if (!(std::cin >> choice)) {
    options.collision = biv::open::Collision::abort_preset;
    return;
  }
  if (choice == 'r' || choice == 'R') {
    options.collision = biv::open::Collision::rename;
  } else {
    options.collision = biv::open::Collision::abort_preset;
  }
}

int emit_internal_fallback(bool json) noexcept {
  if (json) {
    std::cout << "{\"envelope_version\":1,\"app_version\":\"" << biv::app_version()
              << "\",\"ok\":false,\"verb\":\"pack\",\"exit_code\":4,"
                 "\"warnings\":[],\"advisories\":[],\"result\":null,"
                 "\"error\":{\"kind\":\"InternalError\",\"path\":\"\",\"detail\":\"main\","
                 "\"errno\":0,\"facts\":{}}}";
  } else {
    std::cerr << "biv: InternalError\n";
  }
  return 4;
}

}  // namespace

int main(int argc, char** argv) {
  std::span<char*> args{argv, static_cast<size_t>(argc)};
  const bool json_requested = biv::cli::contains_json(args);
  try {
    auto parsed = biv::cli::parse_args(args);
    if (!parsed) {
      return emit_error("pack", parsed.error(), json_requested);
    }

    switch (parsed->verb) {
      case biv::cli::Verb::pack: {
        auto report = biv::pack::pack(parsed->pack_dir);
        if (!report) {
          return emit_error("pack", report.error(), parsed->json);
        }
        const int exit_code = biv::report::exit_for_warnings(!report->warnings.empty());
        if (parsed->json) {
          std::cout << biv::report::envelope("pack", *report, std::nullopt, std::nullopt, exit_code);
        } else {
          emit_pack_text(*report);
        }
        return exit_code;
      }
      case biv::cli::Verb::open: {
        maybe_prompt_collision(parsed->open_options, parsed->json);
        auto report = biv::open::open(parsed->open_options);
        if (!report) {
          return emit_error("open", report.error(), parsed->json);
        }
        if (parsed->json) {
          std::cout << biv::report::envelope("open", std::nullopt, *report, std::nullopt, 0);
        }
        return 0;
      }
      case biv::cli::Verb::list:
      case biv::cli::Verb::info:
        return emit_error(biv::cli::verb_name(parsed->verb),
                          biv::BivError{biv::ErrKind::UsageError, {}, "NotYetImplemented"},
                          parsed->json);
    }
  } catch (const std::exception& error) {
    (void)error;
    return emit_internal_fallback(json_requested);
  } catch (...) {
    return emit_internal_fallback(json_requested);
  }
  return 4;
}
