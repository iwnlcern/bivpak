#pragma once

#include <cstdint>
#include <filesystem>
#include <optional>
#include <span>
#include <string>
#include <vector>

#include "core/repo/git.hpp"
#include "core/repo/types.hpp"
#include "core/support/error.hpp"

namespace biv::repo {

struct ArtifactFile {
  std::filesystem::path archive_path;
  std::filesystem::path disk_path;
};

struct CaptureResult {
  std::vector<ArtifactFile> artifacts;
  std::vector<std::string> advisories;
};

std::string p1_encode(std::string_view value);

std::optional<NonCarriedRefsNote> build_non_carried_refs_note(
    std::span<const std::string> refs,
    std::optional<std::uint64_t> injected_source_count = std::nullopt);

expected<CaptureResult> capture(const Git& git, RepoEntry& entry,
                                const std::filesystem::path& scratch);

}  // namespace biv::repo
