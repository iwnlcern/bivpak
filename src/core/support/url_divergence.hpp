#pragma once

#include <string>

namespace biv {

struct UrlDivergenceEntryRefusal {
  std::string repo_id;
  std::string relpath;
  std::string requested;
  std::string effective;
  std::string op;
};

struct UrlDivergenceAcceptedEntry {
  std::string requested;
  std::string effective;
  std::string op;
  std::string repo;
};

}  // namespace biv
