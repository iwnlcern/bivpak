#include "core/ignore/matcher.hpp"

#include <sstream>

namespace biv::ignore {

namespace {

bool regex_special(const char ch) {
  switch (ch) {
    case '.':
    case '+':
    case '(':
    case ')':
    case '{':
    case '}':
    case '[':
    case ']':
    case '^':
    case '$':
    case '|':
    case '\\':
      return true;
    default:
      return false;
  }
}

std::string glob_to_regex(std::string_view pattern) {
  std::string out;
  out.reserve(pattern.size() * 2U);
  for (size_t i = 0; i < pattern.size(); ++i) {
    const char ch = pattern[i];
    if (ch == '*') {
      if ((i + 1U) < pattern.size() && pattern[i + 1U] == '*') {
        out += ".*";
        ++i;
      } else {
        out += "[^/]*";
      }
    } else if (ch == '?') {
      out += "[^/]";
    } else {
      if (regex_special(ch)) {
        out.push_back('\\');
      }
      out.push_back(ch);
    }
  }
  return out;
}

std::string trim_cr(std::string line) {
  if (!line.empty() && line.back() == '\r') {
    line.pop_back();
  }
  return line;
}

}  // namespace

expected<Matcher> Matcher::compile(const std::string_view pattern_bytes, const bool is_builtin) {
  Matcher matcher;
  std::istringstream stream{std::string{pattern_bytes}};
  std::string line;
  size_t line_number = 0;
  try {
    while (std::getline(stream, line)) {
      ++line_number;
      line = trim_cr(std::move(line));
      if (line.empty() || line.starts_with('#')) {
        continue;
      }

      bool negated = false;
      if (line.starts_with('!')) {
        negated = true;
        line.erase(line.begin());
      }

      bool anchored = false;
      if (line.starts_with('/')) {
        anchored = true;
        line.erase(line.begin());
      }

      bool dir_only = false;
      if (line.ends_with('/')) {
        dir_only = true;
        line.pop_back();
      }

      const bool has_slash = line.find('/') != std::string::npos;
      const std::string source = is_builtin ? "builtin-v1" : ".bivignore:" + std::to_string(line_number);

      std::string regex_text;
      if (anchored || has_slash) {
        regex_text = "^" + glob_to_regex(line) + "$";
      } else {
        regex_text = "(^|.*/)" + glob_to_regex(line) + "$";
      }

      matcher.rules_.push_back(Rule{
          .regex = std::regex{regex_text, std::regex::ECMAScript},
          .negated = negated,
          .dir_only = dir_only,
          .has_slash = has_slash,
          .anchored = anchored,
          .source = source});
    }
  } catch (const std::regex_error& error) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, error.what()});
  }
  return matcher;
}

Verdict Matcher::match(const std::string_view relpath, const bool is_dir) const {
  bool ignored = false;
  std::string source;
  const std::string path{relpath};
  for (const auto& rule : rules_) {
    if (rule.dir_only && !is_dir) {
      continue;
    }
    if (std::regex_match(path, rule.regex)) {
      ignored = !rule.negated;
      source = rule.source;
    }
  }
  return Verdict{.ignored = ignored, .source = ignored ? source : std::string{}};
}

}  // namespace biv::ignore
