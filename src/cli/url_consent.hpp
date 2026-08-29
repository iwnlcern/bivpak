#pragma once

#include <cstddef>
#include <iosfwd>
#include <string>
#include <string_view>

namespace biv::cli {

struct UrlDivergenceFacts {
  std::string op;
  std::string repo;
  std::string requested;
  std::string effective;
};

bool interactive_url_hook_installable();

std::string render_prompt_d(const UrlDivergenceFacts& facts);
std::string render_accepted_notice(const UrlDivergenceFacts& facts);
std::string render_pack_refusal_detail(const UrlDivergenceFacts& facts);
std::string render_entry_refusal_line(std::string_view relpath,
                                      const UrlDivergenceFacts& facts);
std::string render_run_guidance_line(std::size_t refused_count);
bool prompt_url_divergence(const UrlDivergenceFacts& facts, std::istream& in,
                           std::ostream& err);

}  // namespace biv::cli
