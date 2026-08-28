#include "cli/url_consent.hpp"

#include <istream>
#include <ostream>
#include <unistd.h>

namespace biv::cli {

bool interactive_url_hook_installable() {
  return ::isatty(STDIN_FILENO) != 0 && ::isatty(STDERR_FILENO) != 0;
}

std::string render_prompt_d(const UrlDivergenceFacts& facts) {
  return "  " + facts.op + ": the address git will contact for " + facts.repo +
         " differs from the requested address:\n"
         "    requested: " + facts.requested + "\n"
         "    effective: " + facts.effective + "\n"
         "  Contact the effective address? [y/N] ";
}

std::string render_accepted_notice(const UrlDivergenceFacts& facts) {
  return "  " + facts.op + ": contacting " + facts.effective + " for " + facts.repo +
         " (requested: " + facts.requested + " — accepted for this run)\n";
}

std::string render_pack_refusal_detail(const UrlDivergenceFacts& facts) {
  return "pack refused: " + facts.op + " for " + facts.repo + " would contact " +
         facts.effective + " instead of the requested " + facts.requested +
         "; approval was not given. Re-run interactively to review, or pass "
         "--accept-url-divergence to proceed.";
}

std::string render_entry_refusal_line(std::string_view relpath,
                                      const UrlDivergenceFacts& facts) {
  return "  " + std::string{relpath} + ": restore failed — " + facts.op +
         " would contact " + facts.effective + " instead of the requested " +
         facts.requested + "; approval was not given.\n";
}

std::string render_run_guidance_line(std::size_t refused_count) {
  return "  open: " + std::to_string(refused_count) +
         " restore entry(ies) refused — the effective address was not approved. "
         "Re-run interactively to review, or pass --accept-url-divergence to proceed.\n";
}

bool prompt_url_divergence(const UrlDivergenceFacts& facts, std::istream& in,
                           std::ostream& err) {
  err << render_prompt_d(facts);
  std::string answer;
  if (!std::getline(in, answer)) {
    return false;
  }
  return answer == "y" || answer == "Y";
}

}  // namespace biv::cli
