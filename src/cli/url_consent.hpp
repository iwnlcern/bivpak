#pragma once

#include <cstddef>
#include <iosfwd>
#include <string>
#include <string_view>
#include <optional>
#include <vector>

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
std::string render_entry_refusal_line(std::string_view relpath,
                                      const UrlDivergenceFacts& facts);
std::string render_run_guidance_line(std::size_t refused_count);
std::string render_offline_header();
std::string render_offline_row(std::string_view relpath,
                                const std::optional<std::string>& branch,
                                std::string_view sha,
                                const std::vector<std::string>& remotes);
bool prompt_url_divergence(const UrlDivergenceFacts& facts, std::istream& in,
                           std::ostream& err);

}  // namespace biv::cli
