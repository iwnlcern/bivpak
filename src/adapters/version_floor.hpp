#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <string>
#include <string_view>

namespace biv::adapters::version_floor {

struct FloorRow {
  std::string_view min_line;
  std::string_view surveyed_through;
};

FloorRow row_for(std::string_view agent);

struct Parsed {
  std::array<std::uint32_t, 4> components{};
  std::size_t component_count{0};
};

struct Admission {
  bool admitted{false};
  bool host_version_unverified{false};
  std::string_view detail;
};

struct AdmissionInput {
  std::string_view agent;
  std::string_view host_version;
  std::string_view image_version;
};

std::optional<Parsed> parse_grammar(std::string_view version);
std::optional<std::string> extract_single_version(std::string_view raw);

enum class Order { less, equal, greater };

Order compare_line(const Parsed& a, const Parsed& b);

Admission admit(const AdmissionInput& input);

inline constexpr std::string_view kBasisNewerThanHost =
    "basis_newer_than_host";
inline constexpr std::string_view kBasisUnorderable = "basis_unorderable";

}  // namespace biv::adapters::version_floor
