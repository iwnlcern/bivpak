#include <algorithm>
#include <exception>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <optional>
#include <span>

#include <unistd.h>

#include "cli/args.hpp"
#include "core/pack/pack.hpp"
#include "core/open/render.hpp"
#include "core/open/sessions.hpp"
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

biv::adapters::Env current_env() {
  const char* home = std::getenv("HOME");
  return biv::adapters::Env{
      .getenv = [](const std::string_view name) -> std::optional<std::string> {
        const std::string key{name};
        const char* value = std::getenv(key.c_str());
        return value == nullptr ? std::nullopt : std::optional<std::string>{value};
      },
      .home = home == nullptr ? std::filesystem::path{} : std::filesystem::path{home}};
}

bool consent_specified(const biv::core_sessions::ConsentSpec& consent) {
  return consent.global != biv::core_sessions::ConsentValue::unset || !consent.per_agent.empty();
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
        auto plan = biv::open::plan_open(parsed->open_options);
        if (!plan) {
          return emit_error("open", plan.error(), parsed->json);
        }
        auto preview = biv::core_sessions::build_preview(plan->manifest(), current_env());
        if (!preview) {
          return emit_error("open", preview.error(), parsed->json);
        }
        auto reader = plan->make_reader();
        auto manifest = plan->manifest();
        maybe_prompt_collision(parsed->open_options, parsed->json);
        bool prompt_shown = false;
        std::optional<bool> prompt_answer;
        if (preview->any_sessions() && !consent_specified(parsed->consent) && !parsed->json &&
            ::isatty(STDIN_FILENO) != 0 && ::isatty(STDERR_FILENO) != 0) {
          prompt_shown = true;
          std::cerr << biv::open_render::render_prompt_b(*preview, manifest) << std::flush;
          char choice = '\0';
          if (!(std::cin >> choice)) {
            return 130;
          }
          prompt_answer = choice == 'y' || choice == 'Y';
        }
        const bool warning_shown = preview->any_sessions();
        if (warning_shown && !prompt_shown) {
          std::cerr << biv::open_render::kTrustWarning << '\n';
        }
        auto consent = biv::core_sessions::resolve_consent(parsed->consent, *preview, prompt_answer);
        auto report = biv::open::execute_open(std::move(*plan),
                                              biv::open::OpenDecisions{.collision = parsed->open_options.collision});
        if (!report) {
          return emit_error("open", report.error(), parsed->json);
        }
        auto sessions = biv::core_sessions::run_session_leg(*preview, consent, manifest,
                                                             std::filesystem::path{report->output_dir}, reader);
        if (!sessions) {
          return emit_error("open", sessions.error(), parsed->json);
        }
        sessions->warning_shown = warning_shown;
        const int exit_code = biv::report::exit_for_sessions(*sessions);
        biv::report::OpenSessionsReport sessions_report{.prompt_shown = prompt_shown,
                                                         .warning_shown = warning_shown,
                                                         .consent = consent,
                                                         .preview = *preview,
                                                         .outcome = *sessions};
        if (parsed->json) {
          if (preview->any_sessions()) {
            std::cout << biv::report::envelope("open", std::nullopt, *report, std::nullopt,
                                               exit_code, sessions_report);
          } else {
            std::cout << biv::report::envelope("open", std::nullopt, *report, std::nullopt, exit_code);
          }
        } else if (preview->any_sessions()) {
          const bool all_denied = std::ranges::all_of(consent.per_agent, [](const auto& decision) {
            return !decision.second;
          });
          std::cout << biv::open_render::render_summary(*sessions, all_denied);
        }
        return exit_code;
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
