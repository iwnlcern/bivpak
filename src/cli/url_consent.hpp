#pragma once

#include <cstddef>
#include <iosfwd>
#include <string>
#include <string_view>
#include <optional>
#include <vector>

#include "core/repo/types.hpp"
#include "core/support/error.hpp"

namespace biv::cli {

struct UrlDivergenceFacts {
  std::string op;
  std::string repo;
  std::string requested;
  std::string effective;
};

bool interactive_url_hook_installable();

std::string consent_display(std::string_view raw);
std::string render_prompt_d(const UrlDivergenceFacts& facts);
std::string render_accepted_notice(const UrlDivergenceFacts& facts);
std::string render_pack_refusal_detail(const UrlDivergenceFacts& facts);
std::string render_unclaimed_git_entry_detail(std::string_view path,
                                              std::string_view reason);
std::string render_engine_refusal_detail(
    ErrKind kind, const std::map<std::string, std::string>& facts);
std::string render_entry_refusal_line(std::string_view relpath,
                                      const UrlDivergenceFacts& facts);
std::string render_run_guidance_line(std::size_t refused_count);
std::string render_offline_header();
std::string render_offline_row(std::string_view relpath,
                                const std::optional<std::string>& branch,
                                std::string_view sha,
                                const std::vector<std::string>& remotes);
std::string render_network_consent(const std::vector<repo::RepoEntry>& entries,
                                   bool include_prompt);
std::string render_offline_bundle_row(
    std::string_view relpath, std::string_view absolute_bundle_path,
    const std::optional<std::string>& reconstruct);
bool prompt_url_divergence(const UrlDivergenceFacts& facts, std::istream& in,
                           std::ostream& err);

}  // namespace biv::cli
