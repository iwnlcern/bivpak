#pragma once

#include "adapters/adapter.hpp"

namespace biv::adapters {

const AgentAdapter& claude_code_adapter();
expected<InstallResult> claude_code_install(const InstallTarget& target,
                                            Consent consent,
                                            std::span<const manifest::AgentSessionEntry> records);
expected<RewriteReport> claude_code_rewrite(std::span<const SessionRecord> records, const InstallTarget& target);
Capabilities claude_code_capabilities(const Host& host);

}  // namespace biv::adapters
