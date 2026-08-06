#pragma once

#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

namespace biv::json {

class Writer {
 public:
  void begin_object();
  void end_object();
  void begin_array();
  void end_array();
  void key(std::string_view key);
  void value_string(std::string_view value);
  void value_int(std::int64_t value);
  void value_uint(std::uint64_t value);
  void value_bool(bool value);
  void value_null();
  std::string take();

 private:
  enum class Kind { object, array };
  struct Frame {
    Kind kind{Kind::object};
    bool first{true};
    bool pending_key{false};
  };

  void before_value();
  void begin_value();
  void end_value();
  void write_indent();
  void write_escaped(std::string_view value);

  std::string out_;
  std::vector<Frame> stack_;
};

}
