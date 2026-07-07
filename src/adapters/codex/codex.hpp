#pragma once

#include "adapters/adapter.hpp"

namespace biv::adapters {

const AgentAdapter& codex_adapter();
expected<InstallResult> codex_install(const InstallTarget& target,
                                      Consent consent,
                                      std::span<const manifest::AgentSessionEntry> records);
expected<RewriteReport> codex_rewrite(std::span<const SessionRecord> records, const InstallTarget& target);
Capabilities codex_capabilities(const Host& host);

}  // namespace biv::adapters
