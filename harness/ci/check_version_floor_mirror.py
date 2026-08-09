#!/usr/bin/env python3
"""Fail when product, harness, and scenario version-floor rows drift."""

from __future__ import annotations

import argparse
import ast
import json
import re
import sys
from pathlib import Path


_PRODUCT_ROWS = {
    "kCodexFloor": "codex",
    "kClaudeCodeFloor": "claude-code",
}


def _product_rows(root: Path) -> dict[str, dict[str, str]]:
    source = (root / "src/adapters/version_floor.cpp").read_text(encoding="utf-8")
    matches = re.findall(
        r'constexpr\s+FloorRow\s+(k[A-Za-z]+Floor)\s*\{\s*"([^"]+)"\s*,\s*"([^"]+)"\s*\}',
        source,
    )
    rows = {
        _PRODUCT_ROWS[name]: {"min_line": minimum, "surveyed_through": surveyed}
        for name, minimum, surveyed in matches
        if name in _PRODUCT_ROWS
    }
    if set(rows) != set(_PRODUCT_ROWS.values()):
        raise ValueError("product version-floor rows are incomplete")
    return rows


def _harness_rows(root: Path) -> dict[str, dict[str, str]]:
    source = (root / "harness/bivharness/e3.py").read_text(encoding="utf-8")
    module = ast.parse(source)
    for statement in module.body:
        if (
            isinstance(statement, ast.Assign)
            and any(
                isinstance(target, ast.Name) and target.id == "VERSION_FLOOR_MIRROR"
                for target in statement.targets
            )
        ):
            value = ast.literal_eval(statement.value)
            if isinstance(value, dict):
                return value
    raise ValueError("VERSION_FLOOR_MIRROR is missing")


def _scenario_rows(root: Path) -> dict[str, dict[str, str]]:
    scenario = json.loads(
        (root / "harness/scenarios-e3/e3-dual-resume.json").read_text(
            encoding="utf-8"
        )
    )
    return {agent["id"]: agent["version_floor"] for agent in scenario["agents"]}


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--root",
        type=Path,
        default=Path(__file__).resolve().parents[2],
    )
    args = parser.parse_args()
    try:
        product = _product_rows(args.root)
        harness = _harness_rows(args.root)
        scenario = _scenario_rows(args.root)
    except (OSError, ValueError, SyntaxError, KeyError, TypeError, json.JSONDecodeError) as exc:
        print(f"version floor mirror drift: {exc}", file=sys.stderr)
        return 1
    if product != harness or product != scenario:
        print(
            "version floor mirror drift: "
            f"product={product!r} harness={harness!r} scenario={scenario!r}",
            file=sys.stderr,
        )
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
