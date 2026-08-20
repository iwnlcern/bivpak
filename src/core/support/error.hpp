#pragma once

#include <expected>
#include <map>
#include <string>

namespace biv {

enum class ErrKind {
  SourceUnreadableRoot,
  RepoDiscoveredUnsupported,
  OutputInsideSource,
  PartialPresent,
  ArchiveWriteFailed,
  NotABivpakImage,
  ImageUnreadable,
  FormatVersionUnsupported,
  UnknownRequiredCapability,
  IntegrityFailurePreApply,
  UnmanifestedMember,
  MemberPathUnsafe,
  CollisionRefused,
  OpenPartialPresent,
  IntegrityFailureMidApply,
  RestoreWriteFailed,
  ContainmentRefused,
  SessionInstallFailed,
  UnknownAgentSkipped,
  EntrySchemaSkipped,
  SessionsConsentSkipped,
  SessionsStaged,
  AgentNotValidatedFailed,
  InternalError,
  UsageError,
  ParseError
};

struct BivError {
  ErrKind kind;
  std::string path{};
  std::string detail{};
  int err_no{0};
  std::map<std::string, std::string> facts{};
};

template <class T>
using expected = std::expected<T, BivError>;

const char* to_string(ErrKind kind) noexcept;

}
