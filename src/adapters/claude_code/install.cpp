#include "adapters/claude_code/claude_code.hpp"

#include <algorithm>
#include <array>
#include <cerrno>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <limits>
#include <optional>
#include <random>
#include <span>
#include <string>
#include <string_view>
#include <system_error>
#include <vector>

#include <fcntl.h>
#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-literal-operator"
#endif
#include <simdjson.h>
#if defined(__GNUC__)
#pragma GCC diagnostic pop
#endif
#include <sys/random.h>
#include <unistd.h>

#include "adapters/rewrite_common.hpp"

namespace biv::adapters {

namespace {

namespace fs = std::filesystem;

constexpr size_t kUnpinnedProjectKeyCap = 255;

struct DestinationPlan {
  std::string artifact;
  fs::path path;
  bool rewrite_content{true};
};

struct PreparedSession {
  manifest::AgentSessionEntry record;
  std::string installed_session_id;
  std::vector<DestinationPlan> destinations;
  InstallVerify verify;
  std::optional<std::string> refusal_reason;
};

struct ProjectRoot {
  fs::path value;
};

struct CandidatePath {
  fs::path value;
};

struct SessionImageId {
  std::string_view value;
};

bool ascii_alpha(const char value) {
  return (value >= 'A' && value <= 'Z') || (value >= 'a' && value <= 'z');
}

bool ascii_alnum(const char value) {
  return (value >= '0' && value <= '9') || (value >= 'A' && value <= 'Z') || (value >= 'a' && value <= 'z');
}

std::string project_key_for_path(const fs::path& path) {
  std::string key = path.generic_string();
  for (char& value : key) {
    if (!ascii_alnum(value)) {
      value = '-';
    }
  }
  return key;
}

manifest::PathFlavor path_flavor_for(const fs::path& path) {
  const std::string text = path.generic_string();
  if (text.size() >= 7 && text.starts_with("/mnt/") && text.at(6) == '/' && ascii_alpha(text.at(5))) {
    return manifest::PathFlavor::wsl;
  }
  return manifest::PathFlavor::posix;
}

std::string uuid4() {
  std::array<unsigned char, 16> bytes {};
  if (::getrandom(bytes.data(), bytes.size(), 0) != static_cast<ssize_t>(bytes.size())) {
    std::random_device rd;
    for (auto& byte : bytes) {
      byte = static_cast<unsigned char>(rd());
    }
  }
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

bool path_inside(const CandidatePath candidate, const ProjectRoot root) {
  const auto rel = candidate.value.lexically_normal().lexically_relative(root.value.lexically_normal());
  if (rel.empty()) {
    return false;
  }
  const auto begin = rel.begin();
  return begin != rel.end() && *begin != "..";
}

bool safe_relative_path(const std::string_view path) {
  if (path.empty() || path.front() == '/' || path.find('\\') != std::string_view::npos) {
    return false;
  }
  fs::path rel{std::string{path}};
  for (const auto& part : rel) {
    if (part.empty() || part == "." || part == "..") {
      return false;
    }
  }
  return true;
}

std::optional<DestinationPlan> destination_for_artifact(const std::string& artifact,
                                                        const SessionImageId original_session_id,
                                                        std::string_view installed_session_id,
                                                        const ProjectRoot project_root) {
  const std::string prefix = "agents/claude-code/";
  if (!artifact.starts_with(prefix)) {
    return std::nullopt;
  }
  const std::string_view rest = std::string_view{artifact}.substr(prefix.size());
  const std::string main_name = std::string{original_session_id.value} + ".jsonl";
  if (rest == main_name) {
    const auto path = project_root.value / (std::string{installed_session_id} + ".jsonl");
    if (!path_inside(CandidatePath{path}, project_root)) {
      return std::nullopt;
    }
    return DestinationPlan{.artifact = artifact, .path = path, .rewrite_content = true};
  }

  const std::string subtree_prefix = std::string{original_session_id.value} + "/";
  if (!rest.starts_with(subtree_prefix)) {
    return std::nullopt;
  }
  const std::string_view subtree_rel = rest.substr(subtree_prefix.size());
  if (!safe_relative_path(subtree_rel)) {
    return std::nullopt;
  }
  const auto path = project_root.value / std::string{installed_session_id} / fs::path{std::string{subtree_rel}};
  if (!path_inside(CandidatePath{path}, project_root)) {
    return std::nullopt;
  }
  return DestinationPlan{.artifact = artifact, .path = path, .rewrite_content = !artifact.ends_with(".meta.json")};
}

std::vector<std::string> all_artifacts(const manifest::AgentSessionEntry& record) {
  std::vector<std::string> artifacts = record.artifacts;
  for (const auto& child : record.children) {
    artifacts.insert(artifacts.end(), child.artifacts.begin(), child.artifacts.end());
  }
  return artifacts;
}

std::vector<std::pair<std::string, std::string>> id_pairs_for(const manifest::AgentSessionEntry& record,
                                                              std::string_view installed_session_id) {
  return {{record.original_session_ids.primary, std::string{installed_session_id}}};
}

std::vector<std::string> origin_ids_for(const manifest::AgentSessionEntry& record) {
  return {record.original_session_ids.primary};
}

std::vector<std::byte> as_bytes(std::string_view text) {
  std::vector<std::byte> out;
  out.reserve(text.size());
  for (const char value : text) {
    out.push_back(static_cast<std::byte>(value));
  }
  return out;
}

std::string as_string(std::span<const std::byte> bytes) {
  std::string out;
  out.reserve(bytes.size());
  for (const std::byte value : bytes) {
    out.push_back(static_cast<char>(value));
  }
  return out;
}

std::vector<std::byte> rewrite_jsonl_bytes(std::span<const std::byte> bytes,
                                           rewrite::PathPairsView pair_set,
                                           rewrite::IdPairsView id_map,
                                           size_t& skipped_non_utf8) {
  const std::string input = as_string(bytes);
  std::string output;
  output.reserve(input.size());
  size_t start = 0;
  while (start < input.size()) {
    const size_t newline = input.find('\n', start);
    const size_t end = newline == std::string::npos ? input.size() : newline;
    const std::string_view line = std::string_view{input}.substr(start, end - start);
    auto rewritten = rewrite::rewrite_jsonl_line(line, pair_set, id_map);
    if (rewritten.skipped_non_utf8) {
      ++skipped_non_utf8;
    }
    output += rewritten.line;
    if (newline == std::string::npos) {
      break;
    }
    output.push_back('\n');
    start = newline + 1;
  }
  if (input.empty()) {
    return {};
  }
  return as_bytes(output);
}

expected<void> write_all(const int fd, std::span<const std::byte> bytes) {
  while (!bytes.empty()) {
    const auto written = ::write(fd, bytes.data(), bytes.size());
    if (written < 0) {
      return std::unexpected(BivError{ErrKind::ArchiveWriteFailed, {}, {}, errno});
    }
    bytes = bytes.subspan(static_cast<size_t>(written));
  }
  return {};
}

expected<void> write_no_replace(const fs::path& final_path, std::span<const std::byte> bytes) {
  std::error_code ec;
  fs::create_directories(final_path.parent_path(), ec);
  if (ec) {
    return std::unexpected(BivError{ErrKind::ArchiveWriteFailed, final_path.generic_string(), ec.message(),
                                    static_cast<int>(ec.value())});
  }
  const auto tmp_path = final_path.parent_path() / (".bivpak-install-" + uuid4() + ".tmp");
  const int fd = ::open(tmp_path.c_str(), O_WRONLY | O_CREAT | O_EXCL | O_NOFOLLOW | O_CLOEXEC, 0600);
  if (fd < 0) {
    return std::unexpected(BivError{ErrKind::ArchiveWriteFailed, tmp_path.generic_string(), {}, errno});
  }
  auto cleanup_fd = [&] {
    const int saved_errno = errno;
    ::close(fd);
    std::error_code remove_ec;
    fs::remove(tmp_path, remove_ec);
    errno = saved_errno;
  };
  if (auto ok = write_all(fd, bytes); !ok) {
    cleanup_fd();
    return ok;
  }
  if (::fsync(fd) != 0) {
    cleanup_fd();
    return std::unexpected(BivError{ErrKind::ArchiveWriteFailed, tmp_path.generic_string(), {}, errno});
  }
  if (::close(fd) != 0) {
    std::error_code remove_ec;
    fs::remove(tmp_path, remove_ec);
    return std::unexpected(BivError{ErrKind::ArchiveWriteFailed, tmp_path.generic_string(), {}, errno});
  }
  if (::link(tmp_path.c_str(), final_path.c_str()) != 0) {
    std::error_code remove_ec;
    fs::remove(tmp_path, remove_ec);
    return std::unexpected(BivError{ErrKind::ArchiveWriteFailed, final_path.generic_string(), {}, errno});
  }
  fs::remove(tmp_path, ec);
  return {};
}

void merge_verify(InstallVerify& total, const InstallVerify& next) {
  total.origin_path_hits += next.origin_path_hits;
  total.origin_id_hits += next.origin_id_hits;
  total.artifacts_checked += next.artifacts_checked;
}

InstallSessionOutcome failed_outcome(const manifest::AgentSessionEntry& record, std::string reason) {
  return InstallSessionOutcome{.image_session_id = record.original_session_ids.primary,
                               .outcome = InstallSessionOutcome::Outcome::failed,
                               .reason = std::move(reason),
                               .content_rewrite = std::nullopt,
                               .host_version_unverified = false,
                               .verify = {},
                               .detail = std::nullopt};
}

std::optional<std::string> string_field_from_json_file(const fs::path& path, std::string_view key) {
  std::ifstream input{path, std::ios::binary};
  if (!input) {
    return std::nullopt;
  }
  std::string json{std::istreambuf_iterator<char>{input}, std::istreambuf_iterator<char>{}};
  simdjson::padded_string padded{json};
  simdjson::dom::parser parser;
  simdjson::dom::element root;
  if (parser.parse(padded).get(root)) {
    return std::nullopt;
  }
  simdjson::dom::object object;
  if (root.get(object)) {
    return std::nullopt;
  }
  std::string_view value;
  if (object.at_key(key).get(value)) {
    return std::nullopt;
  }
  return std::string{value};
}

std::optional<std::string> claude_version_from_store(const fs::path& root) {
  if (auto version = string_field_from_json_file(root / ".last-update-result.json", "version"); version.has_value()) {
    return version;
  }
  const auto sessions = root / "sessions";
  if (!fs::exists(sessions)) {
    return std::nullopt;
  }
  for (const auto& entry : fs::directory_iterator(sessions)) {
    if (!entry.is_regular_file() || entry.path().extension() != ".json") {
      continue;
    }
    if (auto version = string_field_from_json_file(entry.path(), "version"); version.has_value()) {
      return version;
    }
  }
  return std::nullopt;
}

fs::path claude_root_for_host(const Host& host) {
  if (host.env.getenv) {
    auto configured = host.env.getenv("CLAUDE_CONFIG_DIR");
    if (configured.has_value()) {
      return fs::path{*configured};
    }
  }
  if (!host.env.home.empty()) {
    return host.env.home / ".claude";
  }
  return host.home / ".claude";
}

bool validated_claude_version(const std::string_view version) {
  return version.starts_with("2.1.");
}

Capabilities capabilities_for_root(const fs::path& root) {
  Capabilities caps{.agent_version = "unknown",
                    .validated_range = "2.1.x",
                    .verdict = Capabilities::Verdict::absent,
                    .long_path_keys_pinned = false,
                    .per_verb = {.collect = false, .install = false, .rewrite = false}};
  if (!fs::exists(root)) {
    return caps;
  }
  caps.per_verb = {.collect = true, .install = true, .rewrite = true};
  auto version = claude_version_from_store(root);
  if (!version.has_value()) {
    caps.verdict = Capabilities::Verdict::unvalidated_host;
    return caps;
  }
  caps.agent_version = *version;
  caps.verdict = validated_claude_version(*version) ? Capabilities::Verdict::validated
                                                    : Capabilities::Verdict::unvalidated;
  return caps;
}

}  // namespace

expected<InstallResult> claude_code_install(const InstallTarget& target,
                                            const Consent consent,
                                            const std::span<const manifest::AgentSessionEntry> records) {
  InstallResult result;
  result.mode = consent == Consent::yes ? InstallResult::Mode::host_installed : InstallResult::Mode::staged;
  const auto project_key = project_key_for_path(target.workspace_root);
  if (project_key.size() > kUnpinnedProjectKeyCap) {
    for (const auto& record : records) {
      result.sessions.push_back(failed_outcome(record, "long_path_key_unpinned"));
    }
    return result;
  }

  const auto project_root = ProjectRoot{target.target_store.root / "projects" / project_key};
  std::vector<PreparedSession> prepared;
  prepared.reserve(records.size());
  bool containment_refused = false;
  for (const auto& record : records) {
    PreparedSession session{.record = record,
                            .installed_session_id = uuid4(),
                            .destinations = {},
                            .verify = {},
                            .refusal_reason = std::nullopt};
    for (const auto& artifact : all_artifacts(record)) {
      auto destination = destination_for_artifact(artifact,
                                                 SessionImageId{record.original_session_ids.primary},
                                                 session.installed_session_id,
                                                 project_root);
      if (!destination.has_value()) {
        session.refusal_reason = "containment_refused";
        containment_refused = true;
        break;
      }
      if (fs::exists(destination->path)) {
        session.refusal_reason = "collision_refused";
        break;
      }
      session.destinations.push_back(std::move(*destination));
    }
    prepared.push_back(std::move(session));
  }

  if (containment_refused) {
    for (const auto& record : records) {
      result.sessions.push_back(failed_outcome(record, "containment_refused"));
    }
    return result;
  }

  const auto caps = capabilities_for_root(target.target_store.root);
  for (auto& session : prepared) {
    if (session.refusal_reason.has_value()) {
      result.sessions.push_back(failed_outcome(session.record, *session.refusal_reason));
      continue;
    }
    result.id_map.push_back(IdMapEntry{.agent = "claude-code",
                                       .image_session_id = session.record.original_session_ids.primary,
                                       .installed_session_id = session.installed_session_id,
                                       .children = {}});
    if (consent == Consent::no) {
      result.sessions.push_back(InstallSessionOutcome{.image_session_id = session.record.original_session_ids.primary,
                                                      .outcome = InstallSessionOutcome::Outcome::staged,
                                                      .reason = std::nullopt,
                                                      .content_rewrite = std::nullopt,
                                                      .host_version_unverified = false,
                                                      .verify = {},
                                                      .detail = std::nullopt});
      continue;
    }

    const auto pair_set = rewrite::derive_pair_set(session.record.original_path,
                                                   session.record.path_flavor,
                                                   target.workspace_root.generic_string(),
                                                   path_flavor_for(target.workspace_root));
    const auto origins = rewrite::origins_from_pairs(pair_set);
    const auto ids = id_pairs_for(session.record, session.installed_session_id);
    const auto origin_ids = origin_ids_for(session.record);
    size_t skipped_non_utf8 = 0;
    for (const auto& destination : session.destinations) {
      auto data = target.member_read(destination.artifact);
      if (!data) {
        return std::unexpected(data.error());
      }
      std::vector<std::byte> output = *data;
      if (destination.rewrite_content) {
        output = rewrite_jsonl_bytes(*data, rewrite::PathPairsView{pair_set}, rewrite::IdPairsView{ids}, skipped_non_utf8);
      }
      auto verify = rewrite::verify_scan(output, rewrite::OriginPathsView{origins}, rewrite::OriginIdsView{origin_ids});
      merge_verify(session.verify, verify);
      if (auto ok = write_no_replace(destination.path, output); !ok) {
        return std::unexpected(ok.error());
      }
    }
    result.sessions.push_back(InstallSessionOutcome{.image_session_id = session.record.original_session_ids.primary,
                                                    .outcome = InstallSessionOutcome::Outcome::installed,
                                                    .reason = std::nullopt,
                                                    .content_rewrite = skipped_non_utf8 == 0
                                                                           ? std::optional<std::string>{"jsonl"}
                                                                           : std::optional<std::string>{"partial"},
                                                    .host_version_unverified =
                                                        caps.verdict != Capabilities::Verdict::validated,
                                                    .verify = session.verify,
                                                    .detail = std::nullopt});
  }
  if (std::ranges::any_of(result.sessions, [](const InstallSessionOutcome& session) {
        return session.outcome == InstallSessionOutcome::Outcome::installed;
      })) {
    result.activation.push_back(Activation{.agent = "claude-code", .command = "claude"});
  }
  return result;
}

expected<RewriteReport> claude_code_rewrite(const std::span<const SessionRecord> records,
                                            const InstallTarget& target) {
  RewriteReport report;
  const auto target_flavor = path_flavor_for(target.workspace_root);
  for (const auto& record : records) {
    const auto pair_set = rewrite::derive_pair_set(record.original_path,
                                                   record.path_flavor,
                                                   target.workspace_root.generic_string(),
                                                   target_flavor);
    const auto origins = rewrite::origins_from_pairs(pair_set);
    const auto origin_ids = std::vector<std::string>{record.original_session_id};
    for (const auto& artifact : record.artifacts) {
      auto data = target.member_read(artifact);
      if (!data) {
        return std::unexpected(data.error());
      }
      auto verify = rewrite::verify_scan(*data, rewrite::OriginPathsView{origins}, rewrite::OriginIdsView{origin_ids});
      report.per_artifact_hits.push_back({artifact, verify});
      merge_verify(report.verify, verify);
    }
  }
  return report;
}

Capabilities claude_code_capabilities(const Host& host) {
  return capabilities_for_root(claude_root_for_host(host));
}

}  // namespace biv::adapters
