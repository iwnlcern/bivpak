#!/usr/bin/env python3
"""Reject per-adapter references in generic core and CLI sources."""

from __future__ import annotations

import argparse
import re
import tempfile
from pathlib import Path


SOURCE_SUFFIXES = {".c", ".cc", ".cpp", ".cxx", ".h", ".hh", ".hpp", ".hxx"}
GENERIC_ID_COMPONENTS = {"adapter", "code"}


def adapter_identifiers(root: Path) -> set[str]:
    adapter_root = root / "src/adapters"
    identifiers: set[str] = set()
    if not adapter_root.is_dir():
        return identifiers
    for directory in sorted(adapter_root.iterdir()):
        if not directory.is_dir():
            continue
        identifiers.add(directory.name)
        identifiers.add(directory.name.replace("_", "-"))
        for component in re.split(r"[-_]", directory.name):
            if len(component) >= 5 and component not in GENERIC_ID_COMPONENTS:
                identifiers.add(component)
    id_method = re.compile(
        r'id\(\)\s+const\s+override\s*\{\s*return\s+"([a-z0-9][a-z0-9._-]*)"'
    )
    for path in sorted(adapter_root.rglob("*")):
        if path.is_file() and path.suffix in SOURCE_SUFFIXES:
            identifiers.update(id_method.findall(path.read_text(encoding="utf-8")))
    return {identifier for identifier in identifiers if identifier}


def violations(root: Path) -> list[str]:
    findings: list[str] = []
    identifiers = sorted(adapter_identifiers(root), key=lambda value: (-len(value), value))
    if not identifiers:
        return findings
    forbidden = re.compile(
        r"(?<![A-Za-z0-9])(?:" + "|".join(re.escape(value) for value in identifiers) +
        r")(?![A-Za-z0-9])",
        re.IGNORECASE,
    )
    for relative in (Path("src/core"), Path("src/cli")):
        directory = root / relative
        for path in sorted(directory.rglob("*")):
            if not path.is_file() or path.suffix not in SOURCE_SUFFIXES:
                continue
            for number, line in enumerate(path.read_text(encoding="utf-8").splitlines(), 1):
                if forbidden.search(line):
                    findings.append(f"{path.relative_to(root)}:{number}:{line.strip()}")
    return findings


def self_test() -> bool:
    with tempfile.TemporaryDirectory(prefix="biv-purity-") as temporary:
        root = Path(temporary)
        (root / "src/core").mkdir(parents=True)
        (root / "src/cli").mkdir(parents=True)
        adapter = root / "src/adapters/synthetic_future"
        adapter.mkdir(parents=True)
        (adapter / "synthetic_future.cpp").write_text(
            'std::string_view id() const override { return "synthetic-future"; }\n',
            encoding="utf-8",
        )
        (root / "src/core/generic.cpp").write_text(
            "void generic_registry_hook();\n", encoding="utf-8"
        )
        if violations(root):
            return False
        (root / "src/core/generic.cpp").write_text(
            'constexpr auto specialization = "synthetic-future";\n',
            encoding="utf-8",
        )
        findings = violations(root)
        return len(findings) == 1 and "synthetic-future" in findings[0]


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--self-test", action="store_true")
    parser.add_argument("root", nargs="?", type=Path, default=Path.cwd())
    args = parser.parse_args()
    if args.self_test:
        if self_test():
            print("core-adapter-purity-selftest: OK")
            return 0
        print("core-adapter-purity-selftest: FAILED")
        return 1
    findings = violations(args.root.resolve())
    if findings:
        print("generic core/CLI contains per-adapter references:")
        print("\n".join(findings))
        return 1
    print("core-adapter-purity: OK")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
