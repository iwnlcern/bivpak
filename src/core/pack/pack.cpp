#include "core/pack/pack.hpp"

#include <algorithm>
#include <array>
#include <chrono>
#include <cstdlib>
#include <cstddef>
#include <ctime>
#include <exception>
#include <fstream>
#include <map>
#include <optional>
#include <set>
#include <span>
#include <sstream>
#include <string_view>
#include <system_error>
#include <vector>

#include <fcntl.h>
#include <unistd.h>

#include "adapters/registry.hpp"
#include "adapters/version_floor.hpp"
#include "core/container/tar_writer.hpp"
#include "core/container/zstd_stream.hpp"
#include "core/manifest/checksums.hpp"
#include "core/manifest/agent_member.hpp"
#include "core/repo/capture.hpp"
#include "core/repo/classify.hpp"
#include "core/repo/discover.hpp"
#include "core/repo/eligibility.hpp"
#include "core/repo/git.hpp"
#include "core/repo/restore.hpp"
#include "core/scan/scan.hpp"
#include "core/support/portability.hpp"
#include "core/support/version.hpp"

namespace biv::pack {

namespace {

struct ClockStamp {
  int64_t seconds;
  std::string rfc3339;
};

std::filesystem::path existing_canonical(const std::filesystem::path& path, std::error_code& ec) {
  auto canonical = std::filesystem::weakly_canonical(path, ec);
  if (ec) {
    return {};
  }
  return canonical;
}

bool lexically_inside(const std::filesystem::path& candidate, const std::filesystem::path& root) {
  const auto rel = candidate.lexically_normal().lexically_relative(root.lexically_normal());
  if (rel.empty()) {
    return false;
  }
  const auto begin = rel.begin();
  if (begin == rel.end()) {
    return false;
  }
  return *begin != "..";
}

BivError with_temp_facts(BivError error,
                         const std::filesystem::path& partial_path,
                         const std::filesystem::path& spool_path) {
  error.facts.try_emplace("partial_path", partial_path.generic_string());
  error.facts.try_emplace("spool_path", spool_path.generic_string());
  return error;
}

expected<void> write_bytes(std::ofstream& out, std::span<const std::byte> bytes, const std::filesystem::path& path) {
  std::string chunk;
  chunk.reserve(bytes.size());
  for (const auto byte : bytes) {
    chunk.push_back(static_cast<char>(byte));
  }
  out.write(chunk.data(), static_cast<std::streamsize>(chunk.size()));
  if (!out) {
    return std::unexpected(BivError{ErrKind::ArchiveWriteFailed, path.generic_string()});
  }
  return {};
}

expected<void> fsync_path(const std::filesystem::path& path, bool directory) {
  const int flags = O_RDONLY | O_CLOEXEC | (directory ? O_DIRECTORY : 0);
  const int fd = ::open(path.c_str(), flags);
  if (fd < 0) {
    return std::unexpected(BivError{ErrKind::ArchiveWriteFailed, path.generic_string(), {}, errno});
  }
  const int rc = ::fsync(fd);
  const int saved_errno = errno;
  ::close(fd);
  if (rc != 0) {
    return std::unexpected(BivError{ErrKind::ArchiveWriteFailed, path.generic_string(), {}, saved_errno});
  }
  return {};
}

std::string uuid4() {
  std::array<unsigned char, 16> bytes {};
  support::secure_random_bytes(bytes.data(), bytes.size());
  bytes.at(6) = static_cast<unsigned char>((bytes.at(6) & 0x0fU) | 0x40U);
  bytes.at(8) = static_cast<unsigned char>((bytes.at(8) & 0x3fU) | 0x80U);

  constexpr std::array<char, 16> hex{'0', '1', '2', '3', '4', '5', '6', '7',
                                     '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
  std::string out;
  out.reserve(36);
  for (size_t i = 0; i < bytes.size(); ++i) {
    if (i == 4U || i == 6U || i == 8U || i == 10U) {
      out.push_back('-');
    }
    out.push_back(hex.at((bytes.at(i) >> 4U) & 0x0fU));
    out.push_back(hex.at(bytes.at(i) & 0x0fU));
  }
  return out;
}

ClockStamp now_stamp() {
  const auto now = std::chrono::system_clock::now();
  const auto seconds = std::chrono::time_point_cast<std::chrono::seconds>(now);
  const std::time_t time = std::chrono::system_clock::to_time_t(seconds);
  std::tm tm {};
  gmtime_r(&time, &tm);
  std::array<char, 32> buffer {};
  const size_t written = std::strftime(buffer.data(), buffer.size(), "%FT%TZ", &tm);
  if (written == 0U) {
    return ClockStamp{.seconds = static_cast<int64_t>(time), .rfc3339 = {}};
  }
  return ClockStamp{.seconds = static_cast<int64_t>(time), .rfc3339 = buffer.data()};
}

manifest::PathFlavor path_flavor(const std::filesystem::path& path) {
  const auto text = path.generic_string();
  if (text.size() >= 7U && text.starts_with("/mnt/") && text.at(6) == '/') {
    const char drive = text.at(5);
    if ((drive >= 'a' && drive <= 'z') || (drive >= 'A' && drive <= 'Z')) {
      return manifest::PathFlavor::wsl;
    }
  }
  return manifest::PathFlavor::posix;
}

std::optional<manifest::PackerHome> packer_home_carrier(
    const std::filesystem::path& home) {
  return manifest::make_packer_home(home.generic_string());
}

expected<void> copy_file_to_sink(const std::filesystem::path& path, container::TarWriter::Sink sink);

expected<std::string> write_payload_member(container::TarWriter& writer,
                                           const std::filesystem::path& source_root,
                                           const scan::Node& node) {
  const std::string archive_path = "payload/" + node.relpath;
  const auto abs = source_root / std::filesystem::path{node.relpath};
  const container::MemberMeta meta{
      .path = archive_path,
      .kind = node.kind,
      .mode = node.mode,
      .mtime_s = node.mtime_s,
      .mtime_ns = node.mtime_ns,
      .size = node.size,
      .symlink_target = node.symlink_target,
  };
  if (auto ok = writer.begin_member(meta); !ok) {
    return std::unexpected(ok.error());
  }
  if (node.kind == scan::NodeKind::file) {
    auto ok = copy_file_to_sink(abs, [&](std::span<const std::byte> chunk) -> expected<void> {
      return writer.write_data(chunk);
    });
    if (!ok) {
      return std::unexpected(ok.error());
    }
  }
  auto extent = writer.end_member();
  if (!extent) {
    return std::unexpected(extent.error());
  }
  return *extent;
}

expected<std::string> write_file_member(container::TarWriter& writer,
                                        const adapters::SessionRecord::ArtifactSource& source,
                                        const std::string_view archive_path,
                                        const int64_t mtime_s) {
  const container::MemberMeta meta{
      .path = std::string{archive_path},
      .kind = scan::NodeKind::file,
      .mode = 0644,
      .mtime_s = mtime_s,
      .mtime_ns = 0,
      .size = source.size,
      .symlink_target = {},
  };
  if (auto ok = writer.begin_member(meta); !ok) {
    return std::unexpected(ok.error());
  }
  auto copied = source.stream([&](std::span<const std::byte> chunk) -> expected<void> {
    return writer.write_data(chunk);
  });
  if (!copied) {
    return std::unexpected(copied.error());
  }
  auto extent = writer.end_member();
  if (!extent) {
    return std::unexpected(extent.error());
  }
  return *extent;
}

expected<std::string> write_file_member(
    container::TarWriter& writer, const std::filesystem::path& source,
    const std::string_view archive_path, const int64_t mtime_s) {
  std::error_code ec;
  const auto size = std::filesystem::file_size(source, ec);
  if (ec) {
    return std::unexpected(BivError{ErrKind::ArchiveWriteFailed,
                                    source.generic_string(), ec.message(),
                                    ec.value()});
  }
  const container::MemberMeta meta{
      .path = std::string{archive_path},
      .kind = scan::NodeKind::file,
      .mode = 0644,
      .mtime_s = mtime_s,
      .mtime_ns = 0,
      .size = size,
      .symlink_target = {},
  };
  if (auto ok = writer.begin_member(meta); !ok) {
    return std::unexpected(ok.error());
  }
  if (auto copied = copy_file_to_sink(
          source, [&](std::span<const std::byte> chunk) -> expected<void> {
            return writer.write_data(chunk);
          });
      !copied) {
    return std::unexpected(copied.error());
  }
  auto extent = writer.end_member();
  if (!extent) {
    return std::unexpected(extent.error());
  }
  return *extent;
}

expected<void> write_string_member(container::TarWriter& writer,
                                   std::string_view path,
                                   std::string_view bytes,
                                   int64_t mtime_s) {
  const container::MemberMeta meta{
      .path = std::string{path},
      .kind = scan::NodeKind::file,
      .mode = 0644,
      .mtime_s = mtime_s,
      .mtime_ns = 0,
      .size = bytes.size(),
      .symlink_target = {},
  };
  if (auto ok = writer.begin_member(meta); !ok) {
    return ok;
  }
  if (auto ok = writer.write_data(std::as_bytes(std::span<const char>{bytes.data(), bytes.size()})); !ok) {
    return ok;
  }
  auto extent = writer.end_member();
  if (!extent) {
    return std::unexpected(extent.error());
  }
  return {};
}

adapters::Env process_env() {
  return adapters::Env{
      .getenv = [](const std::string_view name) -> std::optional<std::string> {
        const std::string key{name};
        if (const char* value = std::getenv(key.c_str()); value != nullptr) {
          return std::string{value};
        }
        return std::nullopt;
      },
      .home = [] {
        if (const char* value = std::getenv("HOME"); value != nullptr) {
          return std::filesystem::path{value};
        }
        return std::filesystem::path{};
      }()};
}

std::vector<std::string> path_segments(std::string text,
                                       const manifest::PathFlavor flavor) {
  if (flavor == manifest::PathFlavor::windows) {
    if (text.starts_with("\\\\?\\") || text.starts_with("//?/")) {
      text.erase(0, 4);
    }
    std::ranges::replace(text, '\\', '/');
  } else if (flavor == manifest::PathFlavor::wsl && text.size() >= 7U &&
             text.starts_with("/mnt/") && text.at(6) == '/') {
    text = text.substr(5, 1) + ":/" + text.substr(7);
  }
  std::vector<std::string> segments;
  size_t start = 0;
  while (start <= text.size()) {
    const auto slash = text.find('/', start);
    const auto end = slash == std::string::npos ? text.size() : slash;
    auto segment = text.substr(start, end - start);
    if (!segment.empty() && segment != ".") {
      if (flavor != manifest::PathFlavor::posix) {
        std::ranges::transform(segment, segment.begin(), [](const char value) {
          return value >= 'A' && value <= 'Z'
                     ? static_cast<char>(value - 'A' + 'a')
                     : value;
        });
      }
      if (segment == "..") {
        if (!segments.empty()) {
          segments.pop_back();
        }
      } else {
        segments.push_back(std::move(segment));
      }
    }
    if (slash == std::string::npos) {
      break;
    }
    start = slash + 1U;
  }
  return segments;
}

std::string relpath_key_for(const std::filesystem::path& source,
                            const adapters::SessionRecord& session) {
  const auto source_flavor = path_flavor(source);
  const auto source_segments = path_segments(source.generic_string(), source_flavor);
  const auto original_segments =
      path_segments(session.original_path, session.path_flavor);
  if (original_segments.size() < source_segments.size() ||
      !std::equal(source_segments.begin(), source_segments.end(),
                  original_segments.begin())) {
    return ".";
  }
  if (original_segments.size() == source_segments.size()) {
    return ".";
  }
  std::string relative;
  for (size_t i = source_segments.size(); i < original_segments.size(); ++i) {
    if (!relative.empty()) {
      relative.push_back('/');
    }
    relative += original_segments.at(i);
  }
  return relative;
}

bool agent_id_ok(const std::string_view value) {
  if (value.empty() || !((value.front() >= 'a' && value.front() <= 'z') ||
                         (value.front() >= '0' && value.front() <= '9'))) {
    return false;
  }
  return std::ranges::all_of(value.substr(1), [](const char character) {
    return (character >= 'a' && character <= 'z') ||
           (character >= '0' && character <= '9') || character == '.' ||
           character == '_' || character == '-';
  });
}

bool session_id_ok(const std::string_view value) {
  return manifest::grammar::session_id_ok(value);
}

Warning adapter_warning(const std::string_view encoded) {
  const auto colon = encoded.find(':');
  if (colon == std::string_view::npos) {
    return Warning{.kind = std::string{encoded}, .path = {}};
  }
  return Warning{.kind = std::string{encoded.substr(0, colon)},
                 .path = std::string{encoded.substr(colon + 1U)}};
}

std::string terminal_safe(const std::string_view text) {
  constexpr std::string_view hex = "0123456789ABCDEF";
  std::string safe;
  safe.reserve(text.size());
  for (const unsigned char byte : text) {
    if (byte < 0x20U || byte == 0x7FU) {
      safe += "\\x";
      safe.push_back(hex.at(byte >> 4U));
      safe.push_back(hex.at(byte & 0x0FU));
    } else {
      safe.push_back(static_cast<char>(byte));
    }
  }
  return safe;
}

struct ChildArtifactMatcher {
  std::string_view child_id;

  bool matches(std::string_view artifact) const {
    const std::string child_jsonl = std::string{child_id} + ".jsonl";
    size_t start = 0;
    while (start <= artifact.size()) {
      const size_t slash = artifact.find('/', start);
      const size_t end =
          slash == std::string_view::npos ? artifact.size() : slash;
      const std::string_view segment = artifact.substr(start, end - start);
      if (segment == child_id || segment == child_jsonl ||
          (segment.starts_with(child_id) && segment.size() > child_id.size() &&
           segment.at(child_id.size()) == '.')) {
        return true;
      }
      if (slash == std::string_view::npos) {
        break;
      }
      start = slash + 1U;
    }
    return false;
  }
};

expected<manifest::AgentSessionEntry> manifest_entry_for(
    const adapters::SessionRecord& session,
    const std::filesystem::path& source,
    const std::string& imported_at) {
  constexpr std::size_t kChildrenNodeCap = 1024U;
  constexpr std::size_t kChildrenDepthCap = 64U;
  constexpr std::size_t kChildArtifactsPerNodeCap = 256U;
  constexpr std::size_t kEntryArtifactsTotalCap = 4096U;
  const auto cap_error = [&](const std::string_view cap) {
    return BivError{ErrKind::ArchiveWriteFailed, session.original_session_id,
                    std::string{cap} + " entry=" +
                        session.original_session_id};
  };

  std::map<std::string, std::string> parent_by_child;
  for (const auto& [child, parent] : session.child_parent_map) {
    parent_by_child.insert_or_assign(child, parent);
  }
  for (const auto& child_id : session.child_ids) {
    std::size_t depth = 1U;
    std::string cursor = child_id;
    std::set<std::string> visited;
    auto edge = parent_by_child.find(cursor);
    while (edge != parent_by_child.end() &&
           edge->second != session.original_session_id) {
      if (!visited.insert(cursor).second || depth == kChildrenDepthCap) {
        return std::unexpected(cap_error("children-depth-cap"));
      }
      ++depth;
      cursor = edge->second;
      edge = parent_by_child.find(cursor);
    }
  }

  std::vector<manifest::SessionChild> children;
  std::vector<std::string> parent_artifacts;
  std::size_t total_artifacts = 0U;
  for (const auto& child_id : session.child_ids) {
    if (children.size() == kChildrenNodeCap) {
      return std::unexpected(cap_error("children-node-cap"));
    }
    std::vector<std::string> child_artifacts;
    const auto append_child_artifact = [&](const std::string& artifact)
        -> expected<void> {
      if (child_artifacts.size() == kChildArtifactsPerNodeCap) {
        return std::unexpected(
            cap_error("children-artifacts-per-node-cap"));
      }
      if (total_artifacts == kEntryArtifactsTotalCap) {
        return std::unexpected(cap_error("entry-artifacts-total-cap"));
      }
      child_artifacts.push_back(artifact);
      ++total_artifacts;
      return {};
    };
    for (const auto& [mapped_child, artifact] : session.child_artifact_map) {
      if (mapped_child == child_id) {
        if (auto appended = append_child_artifact(artifact); !appended) {
          return std::unexpected(appended.error());
        }
      }
    }
    if (child_artifacts.empty()) {
      const ChildArtifactMatcher child_matcher{.child_id = child_id};
      for (const auto& artifact : session.artifacts) {
        if (child_matcher.matches(artifact)) {
          if (auto appended = append_child_artifact(artifact); !appended) {
            return std::unexpected(appended.error());
          }
        }
      }
    }
    std::optional<std::string> parent_id;
    if (const auto parent = parent_by_child.find(child_id);
        parent != parent_by_child.end() &&
        parent->second != session.original_session_id) {
      parent_id = parent->second;
    }
    children.push_back(manifest::SessionChild{
        .original_id = child_id,
        .artifacts = std::move(child_artifacts),
        .parent_id = std::move(parent_id)});
  }
  for (const auto& artifact : session.artifacts) {
    const bool explicitly_mapped = std::ranges::any_of(session.child_artifact_map, [&](const auto& mapping) {
      return mapping.second == artifact;
    });
    const bool belongs_to_child = explicitly_mapped || std::ranges::any_of(session.child_ids, [&](const std::string& child_id) {
      return ChildArtifactMatcher{.child_id = child_id}.matches(artifact);
    });
    if (!belongs_to_child) {
      if (total_artifacts == kEntryArtifactsTotalCap) {
        return std::unexpected(cap_error("entry-artifacts-total-cap"));
      }
      ++total_artifacts;
      parent_artifacts.push_back(artifact);
    }
  }

  const bool has_parent_edge = std::ranges::any_of(
      children, [](const auto& child) { return child.parent_id.has_value(); });
  return manifest::AgentSessionEntry{
      .agent = session.agent,
      .agent_version_at_pack = session.agent_version_at_pack,
      .relpath_key = relpath_key_for(source, session),
      .original_path = session.original_path,
      .normalized_path_key = session.normalized_path_key,
      .normalization_scheme = session.normalization_scheme,
      .path_flavor = session.path_flavor,
      .provenance = session.provenance,
      .original_session_ids = {.primary = session.original_session_id,
                               .parent = session.parent_id,
                               .parent_in_image =
                                   session.parent_id.has_value()
                                       ? std::optional<bool>{false}
                                       : std::nullopt},
      .children = std::move(children),
      .artifacts = std::move(parent_artifacts),
      .live_at_pack = session.live_at_pack,
      .imported_at = imported_at,
      .entry_schema = has_parent_edge ? 2 : 1};
}

void add_summary(PackReport& report, std::string_view agent) {
  auto found = std::ranges::find_if(report.agent_sessions_summary, [&](const AgentSessionsSummary& summary) {
    return summary.agent == agent;
  });
  if (found == report.agent_sessions_summary.end()) {
    report.agent_sessions_summary.push_back(AgentSessionsSummary{.agent = std::string{agent}, .session_count = 1});
  } else {
    ++found->session_count;
  }
}

BivError engine_to_pack_error(BivError error,
                              const std::optional<std::string_view> repo_relpath = std::nullopt,
                              const bool offline = false) {
  const auto engine_kind = repo::engine_error_kind(error);
  if (!engine_kind) return error;
  if (*engine_kind == repo::EngineErrorKind::url_divergence_refused) {
    BivError mapped{ErrKind::UrlDivergenceRefused, error.path};
    for (const auto field : {"requested", "effective", "op"}) {
      if (const auto value = error.facts.find(field); value != error.facts.end()) {
        mapped.facts.emplace(field, value->second);
      }
    }
    return mapped;
  }
  std::optional<ErrKind> kind;
  switch (*engine_kind) {
    case repo::EngineErrorKind::repo_dirty_unsupported: kind = ErrKind::RepoDirtyUnsupported; break;
    case repo::EngineErrorKind::repo_nested_unsupported: kind = ErrKind::RepoNestedUnsupported; break;
    case repo::EngineErrorKind::repo_submodule_unsupported: kind = ErrKind::RepoSubmoduleUnsupported; break;
    case repo::EngineErrorKind::unmerged_index_unrepresentable: kind = ErrKind::UnmergedIndexUnrepresentable; break;
    case repo::EngineErrorKind::ref_uncapturable: kind = ErrKind::RefUncapturable; break;
    case repo::EngineErrorKind::promisor_objects_unavailable: kind = ErrKind::PromisorObjectsUnavailable; break;
    case repo::EngineErrorKind::git_invocation_failed: kind = ErrKind::GitInvocationFailed; break;
    case repo::EngineErrorKind::git_budget_expired: kind = ErrKind::GitBudgetExpired; break;
    case repo::EngineErrorKind::repo_restore_failed: kind = ErrKind::RepoRestoreFailed; break;
    case repo::EngineErrorKind::url_divergence_refused: break;
  }
  if (!kind) return error;
  error.kind = *kind;
  if (repo_relpath) error.facts["repo_relpath"] = std::string{*repo_relpath};
  else if (!error.facts.contains("repo_relpath")) error.facts["repo_relpath"] = error.path;
  if (*kind != ErrKind::RepoNestedUnsupported &&
      *kind != ErrKind::RepoSubmoduleUnsupported) {
    error.path = error.facts.at("repo_relpath");
  }
  error.facts["verb"] = "pack";
  if (*kind == ErrKind::PromisorObjectsUnavailable) {
    error.facts["offline"] = offline ? "true" : "false";
  }
  if (*kind == ErrKind::GitInvocationFailed || *kind == ErrKind::RepoRestoreFailed) {
    error.facts["engine_detail"] = error.detail;
  }
  return error;
}

BivError fence_error(const repo::RepoBoundary& boundary,
                     const repo::EngineIssue& issue) {
  const auto path = issue.paths.empty() ? boundary.relpath : issue.paths.front();
  auto error = repo::make_engine_error(issue.kind, path, issue.detail);
  error.facts.emplace("repo_relpath", boundary.relpath.generic_string());
  if (!issue.paths.empty()) {
    std::string joined;
    for (const auto& issue_path : issue.paths) {
      if (!joined.empty()) joined.push_back('\n');
      joined += issue_path.generic_string();
    }
    error.facts.emplace("unmerged_count", std::to_string(issue.paths.size()));
    error.facts.emplace("unmerged_paths", std::move(joined));
    if (issue.kind == repo::EngineErrorKind::repo_nested_unsupported) {
      error.facts.emplace("child", issue.paths.front().generic_string());
    } else if (issue.kind == repo::EngineErrorKind::repo_submodule_unsupported) {
      error.facts.emplace("gitlink", issue.paths.front().generic_string());
    }
  }
  return error;
}

std::vector<std::size_t> leaves_first(
    const std::vector<repo::RepoEntry>& entries) {
  std::vector<std::size_t> order(entries.size());
  for (std::size_t index = 0; index < entries.size(); ++index) {
    order[index] = index;
  }
  const auto depth = [&](const std::size_t index) {
    std::size_t value = 0;
    auto parent = entries[index].parent_id;
    while (parent && value < entries.size()) {
      const auto found = std::ranges::find(entries, *parent,
                                           &repo::RepoEntry::id);
      if (found == entries.end()) break;
      ++value;
      parent = found->parent_id;
    }
    return value;
  };
  std::stable_sort(order.begin(), order.end(), [&](const auto lhs, const auto rhs) {
    return depth(lhs) > depth(rhs);
  });
  return order;
}

bool path_has_segment(const std::string_view path,
                      const std::string_view segment) {
  size_t start = 0;
  while (start <= path.size()) {
    const auto end = path.find('/', start);
    const auto part = path.substr(
        start, end == std::string_view::npos ? path.size() - start
                                             : end - start);
    if (part == segment) return true;
    if (end == std::string_view::npos) break;
    start = end + 1U;
  }
  return false;
}

bool path_is_below(const std::string_view path,
                   const std::string_view directory) {
  if (directory.empty()) return !path.empty();
  return path.size() > directory.size() &&
         path.starts_with(directory) && path.at(directory.size()) == '/';
}

std::vector<std::string> directory_prefixes(const std::string_view path) {
  std::vector<std::string> prefixes;
  size_t slash = path.find('/');
  while (slash != std::string_view::npos) {
    prefixes.emplace_back(path.substr(0, slash));
    slash = path.find('/', slash + 1U);
  }
  return prefixes;
}

expected<bool> directory_is_all_penumbra(
    const std::filesystem::path& repo_root,
    const std::filesystem::path& directory,
    const std::set<std::string>& penumbra) {
  std::error_code ec;
  std::filesystem::recursive_directory_iterator iterator{
      directory, std::filesystem::directory_options::none, ec};
  if (ec) {
    return std::unexpected(BivError{ErrKind::SourceUnreadableRoot,
                                    directory.generic_string(), ec.message(),
                                    static_cast<int>(ec.value())});
  }
  for (auto end = std::filesystem::recursive_directory_iterator{};
       iterator != end; iterator.increment(ec)) {
    if (ec) {
      return std::unexpected(BivError{ErrKind::SourceUnreadableRoot,
                                      iterator->path().generic_string(),
                                      ec.message(),
                                      static_cast<int>(ec.value())});
    }
    const auto status = iterator->symlink_status(ec);
    if (ec) {
      return std::unexpected(BivError{ErrKind::SourceUnreadableRoot,
                                      iterator->path().generic_string(),
                                      ec.message(),
                                      static_cast<int>(ec.value())});
    }
    if (std::filesystem::is_directory(status)) continue;
    const auto relative =
        iterator->path().lexically_relative(repo_root).generic_string();
    if (!penumbra.contains(relative)) return false;
  }
  if (ec) {
    return std::unexpected(BivError{ErrKind::SourceUnreadableRoot,
                                    directory.generic_string(), ec.message(),
                                    static_cast<int>(ec.value())});
  }
  return true;
}

expected<std::vector<scan::Node>> penumbra_nodes(
    const std::filesystem::path& source,
    const std::vector<repo::RepoEntry>& entries,
    const ignore::Matcher& matcher,
    scan::ScanResult& diagnostics) {
  std::map<std::string, scan::Node> emitted;
  std::set<std::string> recorded_prunes;
  for (const auto& prune : diagnostics.pruned) {
    recorded_prunes.insert(prune.relpath);
  }

  for (size_t entry_index = 0; entry_index < entries.size(); ++entry_index) {
    const auto& entry = entries.at(entry_index);
    if (!entry.engine_source || !repo::restore_invokes_git(entry)) continue;
    const std::string row =
        scan::ScanExclusions::canonical(entry.relpath);
    const auto repo_root = source / std::filesystem::path{row};
    std::set<std::string> penumbra;
    for (const auto& path : entry.engine_source->penumbra_paths) {
      penumbra.insert(scan::ScanExclusions::canonical(path));
    }

    std::vector<std::string> paths{penumbra.begin(), penumbra.end()};
    std::ranges::sort(paths);
    for (const auto& relative : paths) {
      if (relative.empty()) continue;
      const std::string full =
          row.empty() ? relative : row + "/" + relative;
      if (path_has_segment(full, ".biv")) continue;

      bool in_deeper_row = false;
      for (size_t other_index = 0; other_index < entries.size();
           ++other_index) {
        if (other_index == entry_index) continue;
        const auto deeper = scan::ScanExclusions::canonical(
            entries.at(other_index).relpath);
        if (!deeper.empty() && path_is_below(deeper, row) &&
            (full == deeper || path_is_below(full, deeper))) {
          in_deeper_row = true;
          break;
        }
      }
      if (in_deeper_row) continue;

      std::optional<ignore::Verdict> pruned;
      for (const auto& prefix : directory_prefixes(full)) {
        const auto verdict = matcher.match(prefix, true);
        if (verdict.ignored) {
          pruned = verdict;
          if (recorded_prunes.insert(prefix).second) {
            diagnostics.pruned.push_back(
                scan::PruneEntry{.relpath = prefix,
                                 .source = verdict.source});
          }
          break;
        }
      }
      if (!pruned) {
        const auto verdict = matcher.match(full, false);
        if (verdict.ignored) {
          pruned = verdict;
          if (recorded_prunes.insert(full).second) {
            diagnostics.pruned.push_back(
                scan::PruneEntry{.relpath = full,
                                 .source = verdict.source});
          }
        }
      }
      if (pruned) continue;

      auto node = scan::stat_node(source, full);
      if (!node) {
        diagnostics.unreadable.push_back(full);
        continue;
      }
      if (!*node) {
        diagnostics.skipped_unsupported.push_back(full);
        continue;
      }
      emitted.try_emplace(full, std::move(node->value()));
    }

    std::set<std::string> ancestors;
    for (const auto& [full, node] : emitted) {
      (void)node;
      if (!path_is_below(full, row)) continue;
      auto parent = std::filesystem::path{full}.parent_path();
      while (!parent.empty()) {
        const auto ancestor = parent.generic_string();
        if (ancestor == row || !path_is_below(ancestor, row)) break;
        ancestors.insert(ancestor);
        parent = parent.parent_path();
      }
    }
    for (const auto& ancestor : ancestors) {
      if (emitted.contains(ancestor)) continue;
      const auto verdict = matcher.match(ancestor, true);
      if (verdict.ignored) continue;
      auto qualifies = directory_is_all_penumbra(
          repo_root, source / std::filesystem::path{ancestor}, penumbra);
      if (!qualifies) {
        diagnostics.unreadable.push_back(ancestor);
        continue;
      }
      if (!*qualifies) continue;
      auto node = scan::stat_node(source, ancestor);
      if (!node) {
        diagnostics.unreadable.push_back(ancestor);
        continue;
      }
      if (!*node || node->value().kind != scan::NodeKind::dir) continue;
      emitted.try_emplace(ancestor, std::move(node->value()));
    }
  }

  std::vector<scan::Node> nodes;
  nodes.reserve(emitted.size());
  for (auto& [path, node] : emitted) {
    (void)path;
    nodes.push_back(std::move(node));
  }
  return nodes;
}

expected<void> copy_file_to_sink(const std::filesystem::path& path, container::TarWriter::Sink sink) {
  std::ifstream in{path, std::ios::binary};
  if (!in) {
    return std::unexpected(BivError{ErrKind::ArchiveWriteFailed, path.generic_string()});
  }
  std::array<char, 8192> buffer {};
  while (in) {
    in.read(buffer.data(), static_cast<std::streamsize>(buffer.size()));
    const auto count = in.gcount();
    if (count > 0) {
      auto ok = sink(std::as_bytes(std::span<const char>{buffer.data(), static_cast<size_t>(count)}));
      if (!ok) {
        return ok;
      }
    }
  }
  if (in.bad()) {
    return std::unexpected(BivError{ErrKind::ArchiveWriteFailed, path.generic_string()});
  }
  return {};
}

expected<PackReport> pack_impl(const std::filesystem::path& source_dir,
                               const PackOptions& options) {
  std::error_code ec;
  const auto source = existing_canonical(source_dir, ec);
  if (ec || !std::filesystem::is_directory(source, ec)) {
    return std::unexpected(BivError{ErrKind::SourceUnreadableRoot, source_dir.generic_string(),
                                    ec ? ec.message() : "not-directory", static_cast<int>(ec.value())});
  }

  const auto name = source.filename().generic_string();
  const auto image_path = (source.parent_path() / (name + ".bvpk")).lexically_normal();
  const auto partial_path = (source.parent_path() / (name + ".bvpk.partial")).lexically_normal();
  const auto spool_path = (source.parent_path() / (name + ".bvpk.spool")).lexically_normal();
  const auto scratch_path = (source.parent_path() / (name + ".bvpk.scratch")).lexically_normal();
  if (lexically_inside(image_path, source) || lexically_inside(partial_path, source) ||
      lexically_inside(spool_path, source)) {
    return std::unexpected(with_temp_facts(BivError{ErrKind::OutputInsideSource, image_path.generic_string()},
                                           partial_path,
                                           spool_path));
  }
  if (std::filesystem::exists(partial_path, ec) ||
      std::filesystem::exists(spool_path, ec) ||
      std::filesystem::exists(scratch_path, ec)) {
    BivError error{ErrKind::PartialPresent};
    if (std::filesystem::exists(partial_path)) {
      error.facts["partial_path"] = partial_path.generic_string();
    }
    if (std::filesystem::exists(spool_path)) {
      error.facts["spool_path"] = spool_path.generic_string();
    }
    if (std::filesystem::exists(scratch_path)) {
      error.facts["scratch_path"] = scratch_path.generic_string();
    }
    return std::unexpected(error);
  }

  auto cleanup_error = [&](BivError error) {
    std::error_code cleanup_ec;
    std::filesystem::remove(partial_path, cleanup_ec);
    std::filesystem::remove(spool_path, cleanup_ec);
    std::filesystem::remove_all(scratch_path, cleanup_ec);
    return std::unexpected(with_temp_facts(std::move(error), partial_path, spool_path));
  };

  const auto env = process_env();
  auto matcher = scan::prepare_matcher(source);
  if (!matcher) {
    return cleanup_error(matcher.error());
  }
  auto discovery = repo::discover(source, matcher->matcher);
  if (!discovery) {
    return cleanup_error(engine_to_pack_error(discovery.error()));
  }
  scan::ScanExclusions exclusions;
  for (const auto& boundary : discovery->repos) {
    exclusions.repo_subtrees.push_back(
        scan::ScanExclusions::canonical(boundary.relpath));
  }
  auto scan_result = scan::scan(source, matcher->matcher, exclusions);
  if (!scan_result) {
    return cleanup_error(scan_result.error());
  }
  scan_result->bivignore = matcher->bivignore;

  std::vector<repo::RepoEntry> entries;
  std::vector<repo::CaptureResult> captures;
  if (!discovery->repos.empty()) {
    auto git = repo::Git::resolve(env.getenv);
    if (!git) {
      return cleanup_error(engine_to_pack_error(git.error()));
    }
    entries.reserve(discovery->repos.size());
    for (const auto& boundary : discovery->repos) {
      auto classified = repo::classify(
          *git, (source / boundary.relpath).lexically_normal(),
          *discovery);
      if (!classified) {
        return cleanup_error(engine_to_pack_error(
            classified.error(), boundary.relpath.generic_string(), options.offline));
      }
      if (classified->fence != repo::Classification::Fence::none) {
        if (!classified->issue) {
          return cleanup_error(BivError{ErrKind::InternalError,
                                        boundary.relpath.generic_string(),
                                        "repo fence without issue"});
        }
        return cleanup_error(
            engine_to_pack_error(fence_error(boundary, *classified->issue),
                                 boundary.relpath.generic_string(), options.offline));
      }
      entries.push_back(std::move(classified->entry));
    }
    const auto mode = options.offline ? repo::EligibilityMode::offline
                                      : repo::EligibilityMode::network;
    for (auto& entry : entries) {
      if (auto ok = repo::run_eligibility(*git, entry, mode); !ok) {
        return cleanup_error(engine_to_pack_error(
            ok.error(), entry.relpath.generic_string(), options.offline));
      }
    }
    std::filesystem::create_directory(scratch_path, ec);
    if (ec) {
      return cleanup_error(BivError{ErrKind::ArchiveWriteFailed,
                                    scratch_path.generic_string(),
                                    ec.message(), ec.value()});
    }
    captures.reserve(entries.size());
    for (const auto index : leaves_first(entries)) {
      auto captured = repo::capture(*git, entries.at(index), scratch_path);
      if (!captured) {
        return cleanup_error(engine_to_pack_error(
            captured.error(), entries.at(index).relpath.generic_string(), options.offline));
      }
      captures.push_back(std::move(*captured));
    }
  }

  scan::ScanExclusions payload_only_exclusions;
  for (const auto& entry : entries) {
    const auto rel = scan::ScanExclusions::canonical(entry.relpath);
    if (repo::restore_invokes_git(entry)) {
      payload_only_exclusions.repo_subtrees.push_back(rel);
    } else {
      payload_only_exclusions.claimed_markers.push_back(rel);
    }
  }
  for (const auto& entry : entries) {
    if (repo::restore_invokes_git(entry)) {
      continue;
    }
    auto scanned = scan::scan_subtree(
        source, matcher->matcher, payload_only_exclusions,
        scan::ScanExclusions::canonical(entry.relpath), *scan_result);
    if (!scanned) {
      return cleanup_error(scanned.error());
    }
  }
  auto penumbra =
      penumbra_nodes(source, entries, matcher->matcher, *scan_result);
  if (!penumbra) {
    return cleanup_error(penumbra.error());
  }
  scan_result->payload.insert(scan_result->payload.end(), penumbra->begin(),
                              penumbra->end());

  manifest::Checksums checksums;
  PackReport report;
  report.image_path = image_path.generic_string();
  report.source_path = source.generic_string();
  report.flavor = path_flavor(source);
  report.image_id = uuid4();
  report.repos = entries;
  for (const auto& path : scan_result->skipped_unsupported) {
    report.warnings.push_back(
        Warning{.kind = std::string{kWarningUnsupportedFileTypeSkipped},
                .path = path});
  }
  for (const auto& path : scan_result->unreadable) {
    report.warnings.push_back(Warning{.kind = "SourceUnreadableSubpath", .path = path});
  }
  if (!scan_result->pruned.empty()) {
    report.advisories.push_back(Advisory{.kind = "prune-summary", .entries = scan_result->pruned, .paths = {}});
  }
  if (!scan_result->nested_bivignore.empty()) {
    report.advisories.push_back(
        Advisory{.kind = "nested-bivignore-ignored", .entries = {}, .paths = scan_result->nested_bivignore});
  }

  const auto created = now_stamp();
  std::vector<adapters::SessionRecord> collected_sessions;
  std::set<std::pair<std::string, std::string>> emitted_agent_sessions;
  std::set<std::string> emitted_members{"manifest.json", "checksums.json"};
  for (const auto& node : scan_result->payload) {
    emitted_members.insert("payload/" + node.relpath);
  }
  for (const auto* adapter : adapters::all_adapters()) {
    if (!agent_id_ok(adapter->id())) {
      return cleanup_error(BivError{ErrKind::ArchiveWriteFailed, {},
                                    "adapter-id-grammar"});
    }
    auto stores = adapter->discover(env);
    if (!stores) {
      return cleanup_error(stores.error());
    }
    auto collected = adapter->collect(source, *stores);
    if (!collected) {
      return cleanup_error(collected.error());
    }
    for (const auto& path : collected->no_cwd_record) {
      report.warnings.push_back(
          Warning{.kind = "SessionNoCwdRecord", .path = path});
    }
    for (const auto& warning : collected->warnings) {
      report.warnings.push_back(adapter_warning(warning));
    }
    for (auto& session : collected->sessions) {
      if (session.agent != adapter->id() || !agent_id_ok(session.agent) ||
          !session_id_ok(session.original_session_id) ||
          session.artifacts.empty() ||
          session.artifacts.size() != session.artifact_sources.size() ||
          !emitted_agent_sessions
               .insert({session.agent, session.original_session_id})
               .second) {
        return cleanup_error(BivError{ErrKind::ArchiveWriteFailed, {},
                                      "adapter-session-invalid"});
      }
      for (const auto& child_id : session.child_ids) {
        if (!session_id_ok(child_id)) {
          return cleanup_error(BivError{ErrKind::ArchiveWriteFailed, {},
                                        "adapter-session-id"});
        }
      }
      if (session.parent_id.has_value() && !session_id_ok(*session.parent_id)) {
        return cleanup_error(BivError{ErrKind::ArchiveWriteFailed, {},
                                      "adapter-parent-session-id"});
      }
      const auto floor = adapters::version_floor::row_for(session.agent);
      const auto version =
          adapters::version_floor::parse_grammar(session.agent_version_at_pack);
      const auto minimum =
          adapters::version_floor::parse_grammar(floor.min_line);
      if (version.has_value() && minimum.has_value() &&
          adapters::version_floor::compare_line(*version, *minimum) ==
              adapters::version_floor::Order::less) {
        report.warnings.push_back(Warning{
            .kind = "SessionBelowMinimumOmitted",
            .path = session.original_session_id,
            .artifact = session.agent + " version " +
                        session.agent_version_at_pack +
                        " is below minimum " + std::string{floor.min_line} +
                        " (reason: below-minimum)"});
        continue;
      }
      for (const auto& artifact : session.artifacts) {
        if (!manifest::grammar::agent_member_ok(
                manifest::grammar::AgentId{session.agent},
                manifest::grammar::MemberPath{artifact}) ||
            !emitted_members.insert(artifact).second) {
          return cleanup_error(BivError{ErrKind::ArchiveWriteFailed, artifact,
                                        "adapter-member-invalid"});
        }
      }
      if (session.live_at_pack) {
        report.warnings.push_back(Warning{.kind = std::string{kWarningSessionLiveAtPack},
                                          .path = session.original_session_id});
      }
      for (const auto& torn_tail : session.torn_tails) {
        report.warnings.push_back(Warning{.kind = torn_tail.retained
                                                     ? "TornTailRetained"
                                                     : std::string{kWarningTornTailDropped},
                                          .path = session.original_session_id,
                                          .artifact = torn_tail.artifact,
                                          .bytes = torn_tail.bytes});
      }
      auto entry = manifest_entry_for(session, source, created.rfc3339);
      if (!entry) {
        return cleanup_error(entry.error());
      }
      if (entry->artifacts.empty()) {
        return cleanup_error(BivError{ErrKind::ArchiveWriteFailed, {},
                                      "adapter-parent-artifacts-empty"});
      }
      report.agent_sessions.push_back(std::move(*entry));
      add_summary(report, session.agent);
      collected_sessions.push_back(std::move(session));
    }
  }

  std::set<std::pair<std::string, std::string>> image_session_ids;
  for (const auto& entry : report.agent_sessions) {
    image_session_ids.insert({entry.agent, entry.original_session_ids.primary});
  }
  for (auto& entry : report.agent_sessions) {
    if (entry.original_session_ids.parent.has_value() &&
        image_session_ids.contains(
            {entry.agent, *entry.original_session_ids.parent})) {
      entry.original_session_ids.parent_in_image = std::nullopt;
    }
  }

  {
    std::ofstream spool{spool_path, std::ios::binary};
    if (!spool) {
      return cleanup_error(BivError{ErrKind::ArchiveWriteFailed, spool_path.generic_string()});
    }
    container::TarWriter spool_writer{
        [&](std::span<const std::byte> chunk) -> expected<void> {
          return write_bytes(spool, chunk, spool_path);
        }};
    for (const auto& node : scan_result->payload) {
      auto extent = write_payload_member(spool_writer, source, node);
      if (!extent) {
        return cleanup_error(extent.error());
      }
      const std::string archive_path = "payload/" + node.relpath;
      checksums.entries[archive_path] = std::move(*extent);
      ++report.member_count;
      if (node.kind == scan::NodeKind::file) {
        report.payload_bytes += node.size;
      }
    }
    for (const auto& capture : captures) {
      for (const auto& artifact : capture.artifacts) {
        const auto archive_path = artifact.archive_path.generic_string();
        if (!emitted_members.insert(archive_path).second) {
          return cleanup_error(BivError{ErrKind::ArchiveWriteFailed,
                                        archive_path,
                                        "repo-member-duplicate"});
        }
        auto extent = write_file_member(spool_writer, artifact.disk_path,
                                        archive_path, created.seconds);
        if (!extent) {
          return cleanup_error(extent.error());
        }
        checksums.entries[archive_path] = std::move(*extent);
        ++report.member_count;
      }
    }
    for (const auto& session : collected_sessions) {
      for (size_t i = 0; i < session.artifacts.size(); ++i) {
        auto extent = write_file_member(spool_writer, session.artifact_sources.at(i), session.artifacts.at(i),
                                        created.seconds);
        if (!extent) {
          return cleanup_error(extent.error());
        }
        checksums.entries[session.artifacts.at(i)] = std::move(*extent);
        ++report.member_count;
      }
    }
    if (auto ok = spool_writer.finish(); !ok) {
      return cleanup_error(ok.error());
    }
  }

  const manifest::Manifest manifest_model{
      .format_version = manifest::kFormatVersion,
      .required_capabilities = {},
      .image_id = report.image_id,
      .app_version = app_version(),
      .created_at = created.rfc3339,
      .source_path = source.generic_string(),
      .source_path_flavor = report.flavor,
      .packer_home = packer_home_carrier(env.home),
      .repos = entries,
      .agent_sessions = report.agent_sessions,
      .bivignore = scan_result->bivignore,
  };
  auto manifest_json = manifest::serialize(manifest_model);
  if (!manifest_json) {
    return cleanup_error(manifest_json.error());
  }
  const std::string checksums_json = manifest::serialize(checksums);

  {
    std::ofstream partial{partial_path, std::ios::binary};
    if (!partial) {
      return cleanup_error(BivError{ErrKind::ArchiveWriteFailed, partial_path.generic_string()});
    }
    container::ZstdCompressSink zstd{[&](std::span<const std::byte> chunk) -> expected<void> {
      return write_bytes(partial, chunk, partial_path);
    }};
    auto zstd_sink = zstd.as_sink();
    container::TarWriter archive{zstd_sink};
    if (auto ok = write_string_member(archive, "manifest.json", *manifest_json, created.seconds); !ok) {
      return cleanup_error(ok.error());
    }
    if (auto ok = write_string_member(archive, "checksums.json", checksums_json, created.seconds); !ok) {
      return cleanup_error(ok.error());
    }
    if (auto ok = copy_file_to_sink(spool_path, zstd_sink); !ok) {
      return cleanup_error(ok.error());
    }
    if (auto ok = archive.finish(); !ok) {
      return cleanup_error(ok.error());
    }
    if (auto ok = zstd.finish(); !ok) {
      return cleanup_error(ok.error());
    }
  }

  if (auto ok = fsync_path(partial_path, false); !ok) {
    return cleanup_error(ok.error());
  }
  if (auto ok = fsync_path(partial_path.parent_path(), true); !ok) {
    return cleanup_error(ok.error());
  }
  std::filesystem::rename(partial_path, image_path, ec);
  if (ec) {
    return cleanup_error(BivError{ErrKind::ArchiveWriteFailed, image_path.generic_string(), ec.message(),
                                  static_cast<int>(ec.value())});
  }
  if (auto ok = fsync_path(image_path.parent_path(), true); !ok) {
    return cleanup_error(ok.error());
  }
  std::filesystem::remove(spool_path, ec);
  std::filesystem::remove_all(scratch_path, ec);
  return report;
}

}  // namespace

std::string warning_text(const Warning& warning) {
  if (warning.kind == "SessionBelowMinimumOmitted" &&
      warning.artifact.has_value()) {
    return "warning: omitted agent session " + terminal_safe(warning.path) +
           ": " + terminal_safe(*warning.artifact);
  }
  if (warning.kind == kWarningSessionLiveAtPack) {
    return "warning: session " + terminal_safe(warning.path) +
           " may have been live at pack time";
  }
  if (warning.kind == kWarningTornTailDropped &&
      warning.artifact.has_value() && warning.bytes.has_value()) {
    return "warning: torn tail dropped from " +
           terminal_safe(*warning.artifact) + ": " +
           std::to_string(*warning.bytes) + " bytes";
  }
  if (warning.kind == "TornTailRetained" &&
      warning.artifact.has_value() && warning.bytes.has_value()) {
    return "warning: torn tail retained in " +
           terminal_safe(*warning.artifact) + ": " +
           std::to_string(*warning.bytes) +
           " bytes; install will refuse this session";
  }
  auto rendered = "warning: " + terminal_safe(warning.kind);
  if (!warning.path.empty()) {
    rendered += ": " + terminal_safe(warning.path);
  }
  return rendered;
}

expected<PackReport> pack(const std::filesystem::path& source_dir,
                          const PackOptions& options) {
  try {
    return pack_impl(source_dir, options);
  } catch (const std::exception& error) {
    return std::unexpected(BivError{ErrKind::InternalError, source_dir.generic_string(), error.what()});
  } catch (...) {
    return std::unexpected(BivError{ErrKind::InternalError, source_dir.generic_string(), "pack"});
  }
}

expected<PackReport> pack(const std::filesystem::path& source_dir) {
  return pack(source_dir, {});
}

}  // namespace biv::pack
