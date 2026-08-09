#include "core/json/writer.hpp"

#include <stdexcept>
#include <utility>

namespace biv::json {

namespace {

constexpr int kIndentWidth = 2;

char hex_digit(const unsigned char value) {
  return static_cast<char>(value < 10U ? ('0' + value) : ('A' + (value - 10U)));
}

}  // namespace

void Writer::begin_object() {
  begin_value();
  out_.push_back('{');
  stack_.push_back(Frame{Kind::object});
}

void Writer::end_object() {
  if (stack_.empty() || stack_.back().kind != Kind::object || stack_.back().pending_key) {
    throw std::logic_error("json object imbalance");
  }
  const bool was_empty = stack_.back().first;
  stack_.pop_back();
  if (!was_empty) {
    out_.push_back('\n');
    write_indent();
  }
  out_.push_back('}');
  end_value();
}

void Writer::begin_array() {
  begin_value();
  out_.push_back('[');
  stack_.push_back(Frame{Kind::array});
}

void Writer::end_array() {
  if (stack_.empty() || stack_.back().kind != Kind::array) {
    throw std::logic_error("json array imbalance");
  }
  const bool was_empty = stack_.back().first;
  stack_.pop_back();
  if (!was_empty) {
    out_.push_back('\n');
    write_indent();
  }
  out_.push_back(']');
  end_value();
}

void Writer::key(const std::string_view key_name) {
  if (stack_.empty() || stack_.back().kind != Kind::object || stack_.back().pending_key) {
    throw std::logic_error("json key outside object");
  }
  before_value();
  write_escaped(key_name);
  out_ += ": ";
  stack_.back().pending_key = true;
}

void Writer::value_string(const std::string_view value) {
  begin_value();
  write_escaped(value);
  end_value();
}

void Writer::value_int(const std::int64_t value) {
  begin_value();
  out_ += std::to_string(value);
  end_value();
}

void Writer::value_uint(const std::uint64_t value) {
  begin_value();
  out_ += std::to_string(value);
  end_value();
}

void Writer::value_bool(const bool value) {
  begin_value();
  out_ += value ? "true" : "false";
  end_value();
}

void Writer::value_null() {
  begin_value();
  out_ += "null";
  end_value();
}

std::string Writer::take() {
  if (!stack_.empty()) {
    throw std::logic_error("json document incomplete");
  }
  if (out_.empty() || out_.back() != '\n') {
    out_.push_back('\n');
  }
  return std::exchange(out_, {});
}

void Writer::before_value() {
  auto& frame = stack_.back();
  if (!frame.first) {
    out_.push_back(',');
  }
  out_.push_back('\n');
  write_indent();
  frame.first = false;
}

void Writer::begin_value() {
  if (stack_.empty()) {
    return;
  }
  auto& frame = stack_.back();
  if (frame.kind == Kind::object) {
    if (!frame.pending_key) {
      throw std::logic_error("json object value without key");
    }
    return;
  }
  before_value();
}

void Writer::end_value() {
  if (!stack_.empty() && stack_.back().kind == Kind::object && stack_.back().pending_key) {
    stack_.back().pending_key = false;
  }
}

void Writer::write_indent() {
  out_.append(stack_.size() * kIndentWidth, ' ');
}

void Writer::write_escaped(const std::string_view value) {
  out_.push_back('"');
  for (const unsigned char ch : value) {
    switch (ch) {
      case '"':
        out_ += "\\\"";
        break;
      case '\\':
        out_ += "\\\\";
        break;
      default:
        if (ch < 0x20U) {
          out_ += "\\u00";
          out_.push_back(hex_digit((ch >> 4U) & 0x0FU));
          out_.push_back(hex_digit(ch & 0x0FU));
        } else {
          out_.push_back(static_cast<char>(ch));
        }
        break;
    }
  }
  out_.push_back('"');
}

}  // namespace biv::json
