#!/usr/bin/env python3
import hashlib, sys
from pathlib import Path
test_path, source_path, b1_path, b2_path, b3_path = map(Path, sys.argv[1:])
test = test_path.read_text(encoding='utf-8')
source = source_path.read_text(encoding='utf-8')
blocks = [Path(p).read_text(encoding='utf-8') for p in (b1_path, b2_path, b3_path)]
checks = [test.count(blocks[0]), test.count(blocks[1]), source.count(blocks[2])]
includes = [
    '#include "adapters/codex/codex.hpp"',
    '#include "core/pack/pack.hpp"',
    '#include "core/support/error.hpp"',
]
include_counts = [test.count(line) for line in includes]
for i, (block, count) in enumerate(zip(blocks, checks), 1):
    print(f'block_{i}_count={count} sha256={hashlib.sha256(block.encode()).hexdigest()}')
for line, count in zip(includes, include_counts):
    print(f'include_count={count} literal={line}')
print(f'test_sha256={hashlib.sha256(test.encode()).hexdigest()}')
print(f'source_sha256={hashlib.sha256(source.encode()).hexdigest()}')
sys.exit(0 if checks == [1, 1, 1] and include_counts == [1, 1, 1] else 5)
