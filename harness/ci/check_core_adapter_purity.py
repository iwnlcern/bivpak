#!/usr/bin/env python3
"""Reject per-adapter references in generic core and CLI sources."""

from __future__ import annotations

import argparse
import re
from pathlib import Path


FORBIDDEN = re.compile(r"(?:claude|codex)", re.IGNORECASE)
SOURCE_SUFFIXES = {".c", ".cc", ".cpp", ".cxx", ".h", ".hh", ".hpp", ".hxx"}


def violations(root: Path) -> list[str]:
    findings: list[str] = []
    for relative in (Path("src/core"), Path("src/cli")):
        directory = root / relative
        for path in sorted(directory.rglob("*")):
            if not path.is_file() or path.suffix not in SOURCE_SUFFIXES:
                continue
            for number, line in enumerate(path.read_text(encoding="utf-8").splitlines(), 1):
                if FORBIDDEN.search(line):
                    findings.append(f"{path.relative_to(root)}:{number}:{line.strip()}")
    return findings


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("root", nargs="?", type=Path, default=Path.cwd())
    args = parser.parse_args()
    findings = violations(args.root.resolve())
    if findings:
        print("generic core/CLI contains per-adapter references:")
        print("\n".join(findings))
        return 1
    print("core-adapter-purity: OK")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
