#!/usr/bin/env bash
set -euo pipefail

if [[ ! -d src/core/open ]]; then
  echo "src/core/open missing" >&2
  exit 1
fi

if grep -RIn --include='*.cpp' --include='*.hpp' 'rewrite' src/core/open; then
  echo "src/core/open must not reference rewrite" >&2
  exit 1
fi
