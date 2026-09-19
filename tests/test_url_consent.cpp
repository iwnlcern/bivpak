#include <array>
#include <cstddef>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include <catch2/catch_test_macros.hpp>

#include "cli/consent_display_table.hpp"
#include "cli/url_consent.hpp"

namespace {

struct MatrixRow {
  std::string input;
  std::string expected;
};

const std::vector<MatrixRow> kMatrix{
    {std::string{"\x0d"}, "\\r"},
    {std::string{"\x0a"}, "\\n"},
    {std::string{"\x1b"}, "\\u001b"},
    {std::string{"\x7f"}, "\\u007f"},
    {std::string{"\xc2\x9b"}, "\\u009b"},
    {std::string{"\x9b"}, "\xef\xbf\xbd"},
    {std::string{"\xe2\x80\xae"}, "\\u{202e}"},
    {std::string{"\xe2\x80\x8b"}, "\\u{200b}"},
    {std::string{"\xe2\x80\xa8"}, "\\u{2028}"},
    {std::string{"\xef\xb8\x8f"}, "\\u{fe0f}"},
    {std::string{"\xcd\x8f"}, "\\u{34f}"},
};

biv::cli::UrlDivergenceFacts base_facts() {
  return {.op = "clone",
          .repo = "r",
          .requested = "https://req.invalid/x.git",
          .effective = "https://eff.invalid/x.git"};
}

std::string& slot_value(biv::cli::UrlDivergenceFacts& facts, const int slot) {
  switch (slot) {
    case 0:
      return facts.requested;
    case 1:
      return facts.effective;
    case 2:
      return facts.repo;
    default:
      return facts.op;
  }
}

std::string expected_prompt_d(const biv::cli::UrlDivergenceFacts& facts) {
  return "  " + facts.op + ": the address git will contact for " + facts.repo +
         " differs from the requested address:\n"
         "    requested: " + facts.requested + "\n"
         "    effective: " + facts.effective + "\n"
         "  Contact the effective address? [y/N] ";
}

std::string expected_accepted_notice(
    const biv::cli::UrlDivergenceFacts& facts) {
  return "  " + facts.op + ": contacting " + facts.effective + " for " +
         facts.repo + " (requested: " + facts.requested +
         " — accepted for this run)\n";
}

std::string expected_pack_refusal_detail(
    const biv::cli::UrlDivergenceFacts& facts) {
  return "pack refused: " + facts.op + " for " + facts.repo +
         " would contact " + facts.effective + " instead of the requested " +
         facts.requested +
         "; approval was not given. Re-run interactively to review, or pass "
         "--accept-url-divergence to proceed.";
}

std::string expected_entry_refusal_line(
    const std::string_view relpath,
    const biv::cli::UrlDivergenceFacts& facts) {
  return "  " + std::string{relpath} + ": restore failed — " + facts.op +
         " would contact " + facts.effective + " instead of the requested " +
         facts.requested + "; approval was not given.\n";
}

bool decode_utf8_scalar(const std::string_view value, const std::size_t at,
                        char32_t& scalar, std::size_t& width) {
  const auto lead = static_cast<unsigned char>(value[at]);
  if (lead < 0x80U) {
    scalar = lead;
    width = 1;
    return true;
  }
  if (lead >= 0xc2U && lead <= 0xdfU) {
    width = 2;
  } else if (lead >= 0xe0U && lead <= 0xefU) {
    width = 3;
  } else if (lead >= 0xf0U && lead <= 0xf4U) {
    width = 4;
  } else {
    return false;
  }
  if (at + width > value.size()) {
    return false;
  }
  scalar = lead & (0x7fU >> width);
  for (std::size_t index = 1; index < width; ++index) {
    const auto byte = static_cast<unsigned char>(value[at + index]);
    if ((byte & 0xc0U) != 0x80U) {
      return false;
    }
    scalar = (scalar << 6U) | (byte & 0x3fU);
  }
  return true;
}

bool no_raw_control_or_format_scalar(const std::string_view value) {
  for (std::size_t offset = 0; offset < value.size();) {
    char32_t scalar{};
    std::size_t width{};
    if (!decode_utf8_scalar(value, offset, scalar, width)) {
      return false;
    }
    if (scalar <= 0x1fU || scalar == 0x7fU ||
        (scalar >= 0x80U && scalar <= 0x9fU) ||
        biv::cli::consent_display_active(scalar)) {
      return false;
    }
    offset += width;
  }
  return true;
}

}  // namespace

TEST_CASE(
    "a8-1 prompt-d hostile bytes: exact escapes, zero raw control bytes, "
    "template literals intact",
    "[a8]") {
  for (const auto& row : kMatrix) {
    for (int slot = 0; slot < 4; ++slot) {
      auto facts = base_facts();
      slot_value(facts, slot) += row.input;
      auto expected_facts = base_facts();
      slot_value(expected_facts, slot) += row.expected;

      INFO("slot=" << slot);
      CHECK(biv::cli::render_prompt_d(facts) ==
            expected_prompt_d(expected_facts));
      CHECK(no_raw_control_or_format_scalar(
          biv::cli::consent_display(slot_value(facts, slot))));
    }
  }
}

TEST_CASE("a8-2 accepted notice applies the eleven-row matrix to every slot",
          "[a8]") {
  for (const auto& row : kMatrix) {
    for (int slot = 0; slot < 4; ++slot) {
      auto facts = base_facts();
      slot_value(facts, slot) += row.input;
      auto expected_facts = base_facts();
      slot_value(expected_facts, slot) += row.expected;

      INFO("slot=" << slot);
      CHECK(biv::cli::render_accepted_notice(facts) ==
            expected_accepted_notice(expected_facts));
      CHECK(no_raw_control_or_format_scalar(
          biv::cli::consent_display(slot_value(facts, slot))));
    }
  }
}

TEST_CASE("a8-3 pack refusal detail applies the eleven-row matrix to both carriers",
          "[a8]") {
  for (const auto& row : kMatrix) {
    for (int slot = 0; slot < 4; ++slot) {
      auto facts = base_facts();
      slot_value(facts, slot) += row.input;
      auto expected_facts = base_facts();
      slot_value(expected_facts, slot) += row.expected;

      INFO("slot=" << slot);
      CHECK(biv::cli::render_pack_refusal_detail(facts) ==
            expected_pack_refusal_detail(expected_facts));
      CHECK(no_raw_control_or_format_scalar(
          biv::cli::consent_display(slot_value(facts, slot))));
    }
  }
}

TEST_CASE("a8-4 entry refusal line encodes relpath and effective",
          "[a8]") {
  for (const auto& row : kMatrix) {
    auto facts = base_facts();
    facts.effective += row.input;
    auto expected_facts = base_facts();
    expected_facts.effective += row.expected;
    CHECK(biv::cli::render_entry_refusal_line("p", facts) ==
          expected_entry_refusal_line("p", expected_facts));
    CHECK(no_raw_control_or_format_scalar(
        biv::cli::consent_display(facts.effective)));

    facts = base_facts();
    const auto relpath = std::string{"p"} + row.input;
    const auto expected_relpath = std::string{"p"} + row.expected;
    CHECK(biv::cli::render_entry_refusal_line(relpath, facts) ==
          expected_entry_refusal_line(expected_relpath, facts));
    CHECK(no_raw_control_or_format_scalar(
        biv::cli::consent_display(relpath)));
  }
}

TEST_CASE("consent_display clauses 1-4 agree with the landed policy on control rows",
          "[a8]") {
  CHECK(biv::cli::consent_display("\r\n\t") == "\\r\\n\\t");
  CHECK(biv::cli::consent_display(std::string{"\x00", 1}) == "\\u0000");
  CHECK(biv::cli::consent_display("\x1b") == "\\u001b");
  CHECK(biv::cli::consent_display("\x7f") == "\\u007f");
  CHECK(biv::cli::consent_display("\xc2\x9b") == "\\u009b");
  CHECK(biv::cli::consent_display("\x9b") == "\xef\xbf\xbd");
  CHECK(biv::cli::consent_display("ordinary ASCII") == "ordinary ASCII");
}

TEST_CASE("consent_display clause 5 membership: display-active in, ordinary scalars out",
          "[a8]") {
  const std::array<std::pair<char32_t, std::string_view>, 8> active{{
      {0x202e, "\xe2\x80\xae"},
      {0x200b, "\xe2\x80\x8b"},
      {0x2028, "\xe2\x80\xa8"},
      {0x2029, "\xe2\x80\xa9"},
      {0xfe0f, "\xef\xb8\x8f"},
      {0x034f, "\xcd\x8f"},
      {0x00ad, "\xc2\xad"},
      {0x200d, "\xe2\x80\x8d"},
  }};
  const std::array<std::string_view, 8> active_expected{{
      "\\u{202e}", "\\u{200b}", "\\u{2028}", "\\u{2029}",
      "\\u{fe0f}", "\\u{34f}", "\\u{ad}", "\\u{200d}",
  }};
  for (std::size_t index = 0; index < active.size(); ++index) {
    CHECK(biv::cli::consent_display_active(active[index].first));
    CHECK(biv::cli::consent_display(active[index].second) ==
          active_expected[index]);
  }

  const std::array<std::pair<char32_t, std::string_view>, 4> ordinary{{
      {0x0041, "A"},
      {0x00e9, "\xc3\xa9"},
      {0x4e2d, "\xe4\xb8\xad"},
      {0x1f600, "\xf0\x9f\x98\x80"},
  }};
  for (const auto& [scalar, encoded] : ordinary) {
    CHECK_FALSE(biv::cli::consent_display_active(scalar));
    CHECK(biv::cli::consent_display(encoded) == encoded);
  }
}
