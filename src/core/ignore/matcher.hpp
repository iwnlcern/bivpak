#pragma once

#include <regex>
#include <string>
#include <string_view>
#include <vector>

#include "core/support/error.hpp"

namespace biv::ignore {

struct Verdict {
  bool ignored;
  std::string source;
};

class Matcher {
 public:
  static expected<Matcher> compile(std::string_view pattern_bytes, bool is_builtin);
  Verdict match(std::string_view relpath, bool is_dir) const;

 private:
  struct Rule {
    std::regex regex;
    bool negated;
    bool dir_only;
    bool has_slash;
    bool anchored;
    std::string source;
  };

  std::vector<Rule> rules_;
};

}
