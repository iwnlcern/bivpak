#pragma once

#include <filesystem>
#include <string>
#include <string_view>

#include "core/manifest/manifest.hpp"
#include "core/open/sessions.hpp"

namespace biv::open_render {

inline constexpr std::string_view kTrustWarning =
    "WARNING: Only import sessions from a .bvpk image you trust. Imported sessions were\n"
    "authored elsewhere and may be attacker-controlled; once installed, your agent will\n"
    "read them as trusted prior history and may act on instructions or false context they\n"
    "contain when you resume.";

std::string render_probe_disclosure(
    const core_sessions::SessionPreview& preview);
std::string render_prompt_b(const core_sessions::SessionPreview& preview,
                            const manifest::Manifest& manifest);
std::string render_summary(
    const core_sessions::SessionPreview& preview,
    const core_sessions::SessionsOutcome& outcome,
    bool consent_no_all,
    const std::filesystem::path& output_dir);

}  // namespace biv::open_render
