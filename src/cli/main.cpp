#include <exception>
#include <iostream>
#include <optional>

#include "cli/args.hpp"
#include "core/pack/pack.hpp"
#include "core/report/envelope.hpp"
#include "core/report/exit_map.hpp"

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

}  // namespace

int main(int argc, char* argv[]) {
  const bool json_requested = biv::cli::contains_json(argc, argv);
  try {
    auto parsed = biv::cli::parse_args(argc, argv);
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
    return emit_error("pack", biv::BivError{biv::ErrKind::InternalError, {}, error.what()}, json_requested);
  } catch (...) {
    return emit_error("pack", biv::BivError{biv::ErrKind::InternalError, {}, "main"}, json_requested);
  }
  return 4;
}
