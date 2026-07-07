#include "adapters/codex/codex.hpp"

#include <algorithm>
#include <array>
#include <cerrno>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <limits>
#include <map>
#include <optional>
#include <random>
#include <span>
#include <string>
#include <string_view>
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

struct RolloutName {
  std::string id;
  std::string file_stamp;
  std::string year;
  std::string month;
  std::string day;
};

struct WritePlan {
  std::string artifact;
  fs::path path;
  std::string installed_id;
};

struct PreparedSession {
  manifest::AgentSessionEntry record;
  std::string installed_id;
  std::vector<std::pair<std::string, std::string>> child_ids;
  std::vector<WritePlan> writes;
  InstallVerify verify;
};

bool ascii_alpha(const char value) {
  return (value >= 'A' && value <= 'Z') || (value >= 'a' && value <= 'z');
}

manifest::PathFlavor path_flavor_for(const fs::path& path) {
  const std::string text = path.generic_string();
  if (text.size() >= 7 && text.starts_with("/mnt/") && text.at(6) == '/' && ascii_alpha(text.at(5))) {
    return manifest::PathFlavor::wsl;
  }
  return manifest::PathFlavor::posix;
}

uint64_t unix_ms_now() {
  const auto now = std::chrono::system_clock::now();
  return static_cast<uint64_t>(
      std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count());
}

std::tm gmtime_from_ms(const uint64_t ms) {
  const std::time_t seconds = static_cast<std::time_t>(ms / 1000U);
  std::tm tm {};
  gmtime_r(&seconds, &tm);
  return tm;
}

std::string strftime_utc(const std::tm& tm, std::string_view format) {
  std::array<char, 32> buffer {};
  const size_t written = std::strftime(buffer.data(), buffer.size(), std::string{format}.c_str(), &tm);
  if (written == 0U) {
    return {};
  }
  return buffer.data();
}

std::string hex_uuid(const std::array<unsigned char, 16>& bytes) {
  constexpr std::array<char, 16> hex{'0', '1', '2', '3', '4', '5', '6', '7',
                                     '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
  std::string out;
  out.reserve(36);
  for (size_t i = 0; i < bytes.size(); ++i) {
    if (i == 4U || i == 6U || i == 8U || i == 10U) {
      out.push_back('-');
    }
    out.push_back(hex.at((bytes.at(i) >> 4U) & 0x0FU));
    out.push_back(hex.at(bytes.at(i) & 0x0FU));
  }
  return out;
}

std::string uuidv7_from_ms(const uint64_t ms) {
  std::array<unsigned char, 16> bytes {};
  if (::getrandom(bytes.data(), bytes.size(), 0) != static_cast<ssize_t>(bytes.size())) {
    std::random_device rd;
    for (auto& byte : bytes) {
      byte = static_cast<unsigned char>(rd());
    }
  }
  bytes.at(0) = static_cast<unsigned char>((ms >> 40U) & 0xffU);
  bytes.at(1) = static_cast<unsigned char>((ms >> 32U) & 0xffU);
  bytes.at(2) = static_cast<unsigned char>((ms >> 24U) & 0xffU);
  bytes.at(3) = static_cast<unsigned char>((ms >> 16U) & 0xffU);
  bytes.at(4) = static_cast<unsigned char>((ms >> 8U) & 0xffU);
  bytes.at(5) = static_cast<unsigned char>(ms & 0xffU);
  bytes.at(6) = static_cast<unsigned char>((bytes.at(6) & 0x0fU) | 0x70U);
  bytes.at(8) = static_cast<unsigned char>((bytes.at(8) & 0x3fU) | 0x80U);
  return hex_uuid(bytes);
}

RolloutName mint_rollout_name() {
  const uint64_t ms = unix_ms_now();
  const auto tm = gmtime_from_ms(ms);
  return RolloutName{.id = uuidv7_from_ms(ms),
                     .file_stamp = strftime_utc(tm, "%Y-%m-%dT%H-%M-%S"),
                     .year = strftime_utc(tm, "%Y"),
                     .month = strftime_utc(tm, "%m"),
                     .day = strftime_utc(tm, "%d")};
}

std::vector<std::string> all_artifacts(const manifest::AgentSessionEntry& record) {
  std::vector<std::string> artifacts = record.artifacts;
  for (const auto& child : record.children) {
    artifacts.insert(artifacts.end(), child.artifacts.begin(), child.artifacts.end());
  }
  return artifacts;
}

std::optional<std::string> id_from_artifact(const std::string& artifact) {
  const std::string prefix = "agents/codex/";
  if (!artifact.starts_with(prefix) || !artifact.ends_with(".jsonl")) {
    return std::nullopt;
  }
  return artifact.substr(prefix.size(), artifact.size() - prefix.size() - 6U);
}

std::vector<std::pair<std::string, std::string>> id_pairs_for(const manifest::AgentSessionEntry& record,
                                                              std::string_view installed_id,
                                                              const std::vector<std::pair<std::string, std::string>>&
                                                                  child_ids) {
  std::vector<std::pair<std::string, std::string>> ids{{record.original_session_ids.primary, std::string{installed_id}}};
  ids.insert(ids.end(), child_ids.begin(), child_ids.end());
  return ids;
}

std::vector<std::string> origin_ids_for(const manifest::AgentSessionEntry& record) {
  std::vector<std::string> ids{record.original_session_ids.primary};
  for (const auto& child : record.children) {
    ids.push_back(child.original_id);
  }
  return ids;
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
  const int fd = ::open(final_path.c_str(), O_WRONLY | O_CREAT | O_EXCL | O_NOFOLLOW | O_CLOEXEC, 0600);
  if (fd < 0) {
    return std::unexpected(BivError{ErrKind::ArchiveWriteFailed, final_path.generic_string(), {}, errno});
  }
  if (auto ok = write_all(fd, bytes); !ok) {
    ::close(fd);
    fs::remove(final_path, ec);
    return ok;
  }
  if (::fsync(fd) != 0) {
    const int saved_errno = errno;
    ::close(fd);
    fs::remove(final_path, ec);
    return std::unexpected(BivError{ErrKind::ArchiveWriteFailed, final_path.generic_string(), {}, saved_errno});
  }
  if (::close(fd) != 0) {
    return std::unexpected(BivError{ErrKind::ArchiveWriteFailed, final_path.generic_string(), {}, errno});
  }
  return {};
}

void merge_verify(InstallVerify& total, const InstallVerify& next) {
  total.origin_path_hits += next.origin_path_hits;
  total.origin_id_hits += next.origin_id_hits;
  total.artifacts_checked += next.artifacts_checked;
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

std::optional<std::string> rollout_cli_version(const fs::path& path) {
  std::ifstream input{path};
  std::string line;
  while (std::getline(input, line)) {
    simdjson::padded_string padded{line};
    simdjson::dom::parser parser;
    simdjson::dom::element root;
    if (parser.parse(padded).get(root)) {
      continue;
    }
    simdjson::dom::object object;
    if (root.get(object)) {
      continue;
    }
    simdjson::dom::object payload;
    if (object.at_key("payload").get(payload)) {
      continue;
    }
    std::string_view version;
    if (!payload.at_key("cli_version").get(version)) {
      return std::string{version};
    }
  }
  return std::nullopt;
}

std::optional<std::string> codex_version_from_store(const fs::path& root) {
  if (auto version = string_field_from_json_file(root / "version.json", "version"); version.has_value()) {
    return version;
  }
  const auto sessions = root / "sessions";
  if (!fs::exists(sessions)) {
    return std::nullopt;
  }
  for (const auto& entry : fs::recursive_directory_iterator(sessions)) {
    if (entry.is_regular_file() && entry.path().filename().generic_string().starts_with("rollout-")) {
      if (auto version = rollout_cli_version(entry.path()); version.has_value()) {
        return version;
      }
    }
  }
  return std::nullopt;
}

fs::path codex_root_for_host(const Host& host) {
  if (host.env.getenv) {
    auto configured = host.env.getenv("CODEX_HOME");
    if (configured.has_value()) {
      return fs::path{*configured};
    }
  }
  if (!host.env.home.empty()) {
    return host.env.home / ".codex";
  }
  return host.home / ".codex";
}

bool validated_codex_version(std::string_view version) {
  return version.starts_with("0.142.");
}

Capabilities capabilities_for_root(const fs::path& root) {
  Capabilities caps{.agent_version = "unknown",
                    .validated_range = "0.142.x",
                    .verdict = Capabilities::Verdict::absent,
                    .long_path_keys_pinned = true,
                    .per_verb = {.collect = false, .install = false, .rewrite = false}};
  if (!fs::exists(root)) {
    return caps;
  }
  caps.per_verb = {.collect = true, .install = true, .rewrite = true};
  auto version = codex_version_from_store(root);
  if (!version) {
    caps.verdict = Capabilities::Verdict::unvalidated_host;
    return caps;
  }
  caps.agent_version = *version;
  caps.verdict = validated_codex_version(*version) ? Capabilities::Verdict::validated
                                                   : Capabilities::Verdict::unvalidated;
  return caps;
}

}  // namespace

expected<InstallResult> codex_install(const InstallTarget& target,
                                      const Consent consent,
                                      const std::span<const manifest::AgentSessionEntry> records) {
  InstallResult result;
  result.mode = consent == Consent::yes ? InstallResult::Mode::host_installed : InstallResult::Mode::staged;
  const auto host_caps = capabilities_for_root(target.target_store.root);
  for (const auto& record : records) {
    std::map<std::string, RolloutName> rollouts;
    rollouts.emplace(record.original_session_ids.primary, mint_rollout_name());
    PreparedSession prepared{.record = record,
                             .installed_id = rollouts.at(record.original_session_ids.primary).id,
                             .child_ids = {},
                             .writes = {},
                             .verify = {}};
    for (const auto& child : record.children) {
      rollouts.emplace(child.original_id, mint_rollout_name());
      prepared.child_ids.push_back({child.original_id, rollouts.at(child.original_id).id});
    }
    for (const auto& artifact : all_artifacts(record)) {
      auto original_id = id_from_artifact(artifact);
      if (!original_id) {
        result.sessions.push_back(InstallSessionOutcome{.image_session_id = record.original_session_ids.primary,
                                                        .outcome = InstallSessionOutcome::Outcome::failed,
                                                        .reason = "containment_refused",
                                                        .content_rewrite = std::nullopt,
                                                        .host_version_unverified = false,
                                                        .verify = {},
                                                        .detail = std::nullopt});
        continue;
      }
      const auto rollout = rollouts.at(*original_id);
      const auto path = target.target_store.root / "sessions" / rollout.year / rollout.month / rollout.day /
                        ("rollout-" + rollout.file_stamp + "-" + rollout.id + ".jsonl");
      prepared.writes.push_back(WritePlan{.artifact = artifact, .path = path, .installed_id = rollout.id});
    }

    result.id_map.push_back(IdMapEntry{.agent = "codex",
                                       .image_session_id = record.original_session_ids.primary,
                                       .installed_session_id = prepared.installed_id,
                                       .children = prepared.child_ids});
    if (consent == Consent::no) {
      result.sessions.push_back(InstallSessionOutcome{.image_session_id = record.original_session_ids.primary,
                                                      .outcome = InstallSessionOutcome::Outcome::staged,
                                                      .reason = std::nullopt,
                                                      .content_rewrite = std::nullopt,
                                                      .host_version_unverified = false,
                                                      .verify = {},
                                                      .detail = std::nullopt});
      continue;
    }

    const auto pair_set = rewrite::derive_pair_set(record.original_path,
                                                   record.path_flavor,
                                                   target.workspace_root.generic_string(),
                                                   path_flavor_for(target.workspace_root));
    const auto origins = rewrite::origins_from_pairs(pair_set);
    const auto id_map = id_pairs_for(record, prepared.installed_id, prepared.child_ids);
    const auto origin_ids = origin_ids_for(record);
    size_t skipped_non_utf8 = 0;
    for (const auto& write : prepared.writes) {
      auto data = target.member_read(write.artifact);
      if (!data) {
        return std::unexpected(data.error());
      }
      auto output = rewrite_jsonl_bytes(*data, rewrite::PathPairsView{pair_set}, rewrite::IdPairsView{id_map},
                                        skipped_non_utf8);
      auto verify = rewrite::verify_scan(output, rewrite::OriginPathsView{origins}, rewrite::OriginIdsView{origin_ids});
      merge_verify(prepared.verify, verify);
      if (auto ok = write_no_replace(write.path, output); !ok) {
        return std::unexpected(ok.error());
      }
    }
    result.sessions.push_back(InstallSessionOutcome{.image_session_id = record.original_session_ids.primary,
                                                    .outcome = InstallSessionOutcome::Outcome::installed,
                                                    .reason = std::nullopt,
                                                    .content_rewrite = skipped_non_utf8 == 0
                                                                           ? std::optional<std::string>{"jsonl"}
                                                                           : std::optional<std::string>{"partial"},
                                                    .host_version_unverified =
                                                        host_caps.verdict != Capabilities::Verdict::validated,
                                                    .verify = prepared.verify,
                                                    .detail = std::nullopt});
    result.activation.push_back(Activation{.agent = "codex", .command = "codex resume " + prepared.installed_id});
  }
  return result;
}

expected<RewriteReport> codex_rewrite(const std::span<const SessionRecord> records, const InstallTarget& target) {
  RewriteReport report;
  for (const auto& record : records) {
    const auto pair_set = rewrite::derive_pair_set(record.original_path,
                                                   record.path_flavor,
                                                   target.workspace_root.generic_string(),
                                                   path_flavor_for(target.workspace_root));
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

Capabilities codex_capabilities(const Host& host) {
  return capabilities_for_root(codex_root_for_host(host));
}

}  // namespace biv::adapters
