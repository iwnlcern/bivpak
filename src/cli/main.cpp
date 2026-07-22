#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <exception>
#include <filesystem>
#include <iostream>
#include <map>
#include <optional>
#include <span>
#include <string>
#include <system_error>

#include <pthread.h>
#include <signal.h>
#include <unistd.h>

#include "cli/args.hpp"
#include "core/pack/pack.hpp"
#include "core/open/render.hpp"
#include "core/open/sessions.hpp"
#include "core/report/envelope.hpp"
#include "core/report/exit_map.hpp"
#include "core/support/probe.hpp"
#include "core/support/version.hpp"

namespace {

namespace fs = std::filesystem;

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

std::optional<std::string> render_collision_prompt(
    const biv::open::OpenOptions& options, bool json) {
  if (json || options.collision != biv::open::Collision::refuse ||
      ::isatty(STDIN_FILENO) == 0 || ::isatty(STDERR_FILENO) == 0) {
    return std::nullopt;
  }
  const auto dest = options.dest.value_or(default_dest_for(options.image)).lexically_normal();
  std::error_code ec;
  if (!std::filesystem::exists(dest, ec)) {
    return std::nullopt;
  }
  return "destination exists: " + dest.generic_string() + "\n[r]ename/[a]bort? ";
}

void read_collision_choice(biv::open::OpenOptions& options) {
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

biv::adapters::Host current_host(
    const biv::adapters::Env& env,
    std::map<std::string, std::filesystem::path> pinned_bins) {
  return biv::adapters::Host{
      .home = env.home,
      .env = env,
      .version_probe =
          [getenv = env.getenv](
              const std::string_view executable,
              const std::optional<std::filesystem::path>& pin)
          -> biv::expected<biv::support::ProbeEvidence> {
        auto budgets = biv::support::ProbeBudgets{};
        budgets.probe_wall = biv::support::kProbeTimeout;
        return biv::support::run_version_probe(
            std::string{executable}, pin, getenv, budgets);
      },
      .pinned_bins = std::move(pinned_bins)};
}

bool consent_specified(const biv::core_sessions::ConsentSpec& consent) {
  return consent.global != biv::core_sessions::ConsentValue::unset || !consent.per_agent.empty();
}

class SigpipeBlockGuard {
 public:
  // Construction blocks SIGPIPE; every exit except the explicit success
  // restore leaves it blocked by design.
  SigpipeBlockGuard() noexcept {
    if (sigemptyset(&sigpipe_set_) != 0 || sigaddset(&sigpipe_set_, SIGPIPE) != 0 ||
        ::pthread_sigmask(SIG_BLOCK, &sigpipe_set_, &previous_mask_) != 0) {
      return;
    }
    sigset_t pending{};
    if (::sigpending(&pending) != 0) {
      return;
    }
    const int pending_member = sigismember(&pending, SIGPIPE);
    if (pending_member < 0) {
      return;
    }
    sigpipe_pending_before_ = pending_member == 1;
    ready_ = true;
  }

  ~SigpipeBlockGuard() = default;

  SigpipeBlockGuard(const SigpipeBlockGuard&) = delete;
  SigpipeBlockGuard& operator=(const SigpipeBlockGuard&) = delete;
  SigpipeBlockGuard(SigpipeBlockGuard&&) = delete;
  SigpipeBlockGuard& operator=(SigpipeBlockGuard&&) = delete;

  bool ready() const noexcept { return ready_; }

  bool drain_if_ours_and_restore_for_success() noexcept {
    sigset_t pending{};
    if (::sigpending(&pending) != 0) {
      return false;
    }
    const int pending_member = sigismember(&pending, SIGPIPE);
    if (pending_member < 0) {
      return false;
    }
    if (!sigpipe_pending_before_ && pending_member == 1) {
      int received = 0;
      if (::sigwait(&sigpipe_set_, &received) != 0 || received != SIGPIPE) {
        return false;
      }
    }
    if (::pthread_sigmask(SIG_SETMASK, &previous_mask_, nullptr) != 0) {
      return false;
    }
    return true;
  }

 private:
  sigset_t sigpipe_set_{};
  sigset_t previous_mask_{};
  bool sigpipe_pending_before_{false};
  bool ready_{false};
};

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
    if (parsed->help) {
      std::cout << biv::cli::help_text(parsed->verb);
      return 0;
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
        const auto dest_or_default = parsed->open_options.dest.value_or(
            default_dest_for(parsed->open_options.image));
        auto dest_candidate =
            fs::absolute(dest_or_default).lexically_normal();
        while (dest_candidate.filename().empty() &&
               dest_candidate != dest_candidate.root_path()) {
          dest_candidate = dest_candidate.parent_path();
        }
        if (dest_candidate.filename().empty()) {
          return emit_error(
              "open",
              biv::BivError{biv::ErrKind::UsageError, {},
                            "dest-root-like"},
              parsed->json);
        }
        std::error_code dest_error;
        const auto resolved_parent =
            fs::weakly_canonical(dest_candidate.parent_path(), dest_error);
        if (dest_error || resolved_parent.empty()) {
          return emit_error(
              "open",
              biv::BivError{biv::ErrKind::UsageError,
                            dest_candidate.parent_path(),
                            "dest-parent-unresolvable",
                            dest_error.value()},
              parsed->json);
        }
        parsed->open_options.dest =
            resolved_parent / dest_candidate.filename();
        const auto env = current_env();
        const auto host = current_host(env, parsed->agent_bins);
        auto plan = biv::open::plan_open(parsed->open_options);
        if (!plan) {
          return emit_error("open", plan.error(), parsed->json);
        }
        auto preview =
            biv::core_sessions::build_preview(plan->manifest(), host);
        if (!preview) {
          return emit_error("open", preview.error(), parsed->json);
        }
        auto reader = plan->make_reader();
        auto manifest = plan->manifest();
        const auto disclosure =
            preview->any_sessions()
                ? std::optional<std::string>{biv::open_render::render_probe_disclosure(*preview)}
                : std::nullopt;
        const auto collision_prompt = render_collision_prompt(parsed->open_options, parsed->json);
        const bool prompt_requested = preview->any_sessions() &&
                                      !consent_specified(parsed->consent) && !parsed->json &&
                                      ::isatty(STDIN_FILENO) != 0 && ::isatty(STDERR_FILENO) != 0;
        const auto consent_prompt =
            prompt_requested
                ? std::optional<std::string>{biv::open_render::render_prompt_b(*preview, manifest)}
                : std::nullopt;
        const auto trust_warning =
            preview->any_sessions() && !prompt_requested
                ? std::optional<std::string>{std::string{biv::open_render::kTrustWarning} + '\n'}
                : std::nullopt;

        SigpipeBlockGuard sigpipe_guard;
        if (!sigpipe_guard.ready()) {
          return emit_error("open",
                            biv::BivError{.kind = biv::ErrKind::InternalError,
                                          .detail = disclosure.has_value()
                                                        ? "probe-disclosure-write-failed"
                                                        : "consent-surface-write-failed"},
                            parsed->json);
        }
        if (disclosure.has_value()) {
          std::cerr << *disclosure << std::flush;
          if (!std::cerr.good()) {
            return emit_error("open",
                              biv::BivError{.kind = biv::ErrKind::InternalError,
                                            .detail = "probe-disclosure-write-failed"},
                              parsed->json);
          }
        }
        if (collision_prompt.has_value()) {
          std::cerr << *collision_prompt << std::flush;
          if (!std::cerr.good()) {
            return emit_error("open",
                              biv::BivError{.kind = biv::ErrKind::InternalError,
                                            .detail = "consent-surface-write-failed"},
                              parsed->json);
          }
          read_collision_choice(parsed->open_options);
        }
        bool prompt_shown = false;
        bool warning_shown = false;
        std::optional<bool> prompt_answer;
        if (consent_prompt.has_value()) {
          std::cerr << *consent_prompt << std::flush;
          if (!std::cerr.good()) {
            return emit_error("open",
                              biv::BivError{.kind = biv::ErrKind::InternalError,
                                            .detail = "consent-surface-write-failed"},
                              parsed->json);
          }
          prompt_shown = true;
          // render_prompt_b embeds kTrustWarning, so verified prompt
          // publication verifies the warning too.
          warning_shown = true;
          char choice = '\0';
          if (!(std::cin >> choice)) {
            return 130;
          }
          prompt_answer = choice == 'y' || choice == 'Y';
        } else if (trust_warning.has_value()) {
          std::cerr << *trust_warning << std::flush;
          if (!std::cerr.good()) {
            return emit_error("open",
                              biv::BivError{.kind = biv::ErrKind::InternalError,
                                            .detail = "consent-surface-write-failed"},
                              parsed->json);
          }
          warning_shown = true;
        }
        auto consent =
            biv::core_sessions::resolve_consent(parsed->consent, *preview, prompt_answer);
        if (!std::cerr.good()) {
          return emit_error("open",
                            biv::BivError{.kind = biv::ErrKind::InternalError,
                                          .detail = "consent-surface-write-failed"},
                            parsed->json);
        }
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
        const int exit_code = biv::report::exit_for_sessions(*sessions);
        biv::report::OpenSessionsReport sessions_report{.prompt_shown = prompt_shown,
                                                         .warning_shown = warning_shown,
                                                         .consent = consent,
                                                         .preview = *preview,
                                                         .outcome = *sessions};
        std::optional<std::string> final_success_output;
        if (parsed->json) {
          if (preview->any_sessions()) {
            final_success_output = biv::report::envelope(
                "open", std::nullopt, *report, std::nullopt, exit_code, sessions_report);
          } else {
            final_success_output =
                biv::report::envelope("open", std::nullopt, *report, std::nullopt, exit_code);
          }
        } else if (preview->any_sessions()) {
          const bool all_denied = std::ranges::all_of(consent.per_agent, [](const auto& decision) {
            return !decision.second;
          });
          final_success_output = biv::open_render::render_summary(
              *sessions, all_denied, std::filesystem::path{report->output_dir});
        }
        if (!sigpipe_guard.drain_if_ours_and_restore_for_success()) {
          return emit_error("open",
                            biv::BivError{.kind = biv::ErrKind::InternalError,
                                          .detail = "consent-surface-write-failed"},
                            parsed->json);
        }
        if (final_success_output.has_value()) {
          std::cout << *final_success_output;
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
