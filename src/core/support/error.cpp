#include "core/support/error.hpp"

namespace biv {

const char* to_string(const ErrKind kind) noexcept {
  switch (kind) {
    case ErrKind::SourceUnreadableRoot:
      return "SourceUnreadableRoot";
    case ErrKind::RepoDiscoveredUnsupported:
      return "RepoDiscoveredUnsupported";
    case ErrKind::OutputInsideSource:
      return "OutputInsideSource";
    case ErrKind::PartialPresent:
      return "PartialPresent";
    case ErrKind::ArchiveWriteFailed:
      return "ArchiveWriteFailed";
    case ErrKind::NotABivpakImage:
      return "NotABivpakImage";
    case ErrKind::ImageUnreadable:
      return "ImageUnreadable";
    case ErrKind::FormatVersionUnsupported:
      return "FormatVersionUnsupported";
    case ErrKind::UnknownRequiredCapability:
      return "UnknownRequiredCapability";
    case ErrKind::IntegrityFailurePreApply:
      return "IntegrityFailurePreApply";
    case ErrKind::UnmanifestedMember:
      return "UnmanifestedMember";
    case ErrKind::MemberPathUnsafe:
      return "MemberPathUnsafe";
    case ErrKind::CollisionRefused:
      return "CollisionRefused";
    case ErrKind::OpenPartialPresent:
      return "OpenPartialPresent";
    case ErrKind::IntegrityFailureMidApply:
      return "IntegrityFailureMidApply";
    case ErrKind::RestoreWriteFailed:
      return "RestoreWriteFailed";
    case ErrKind::ContainmentRefused:
      return "ContainmentRefused";
    case ErrKind::SessionInstallFailed:
      return "SessionInstallFailed";
    case ErrKind::UnknownAgentSkipped:
      return "UnknownAgentSkipped";
    case ErrKind::SessionsConsentSkipped:
      return "SessionsConsentSkipped";
    case ErrKind::SessionsStaged:
      return "SessionsStaged";
    case ErrKind::AgentNotValidatedFailed:
      return "AgentNotValidatedFailed";
    case ErrKind::InternalError:
      return "InternalError";
    case ErrKind::UsageError:
      return "UsageError";
    case ErrKind::ParseError:
      return "ParseError";
  }
  return "InternalError";
}

}
