import json
import os
import stat
from pathlib import Path
from typing import Any


TOLERANCE_PATH = Path(__file__).resolve().parents[1] / "tolerance" / "tolerance-v1.json"
ALLOWED_POLICIES = {
    "file-bytes": {"exact"},
    "file-mode": {"exact"},
    "dir-mode": {"exact"},
    "symlink-target": {"exact"},
    "file-mtime": {"exact-ns", "ignore"},
    "dir-mtime": {"exact-ns", "ignore"},
    "ownership": {"ignore"},
    "git-object-id": {"future-step"},
    "git-index": {"future-step"},
    "git-remote-config": {"future-step"},
}


def load_tolerance(path: Path | None = None) -> dict[str, Any]:
    return json.loads((path or TOLERANCE_PATH).read_text(encoding="utf-8"))


def _kind(path: Path) -> str:
    mode = path.lstat().st_mode
    if stat.S_ISLNK(mode):
        return "symlink"
    if stat.S_ISDIR(mode):
        return "dir"
    if stat.S_ISREG(mode):
        return "file"
    return "other"


def _entries(root: Path) -> dict[str, str]:
    return {path.relative_to(root).as_posix(): _kind(path) for path in root.rglob("*")}


def _same_bytes(left: Path, right: Path) -> bool:
    with left.open("rb") as lf, right.open("rb") as rf:
        while True:
            lb = lf.read(1024 * 1024)
            rb = rf.read(1024 * 1024)
            if lb != rb:
                return False
            if not lb:
                return True


def _mode(path: Path) -> int:
    return stat.S_IMODE(path.lstat().st_mode)


def _row_policy(tolerance: dict[str, Any], name: str) -> str:
    for row in tolerance.get("rows", []):
        if row.get("name") == name:
            return str(row.get("policy", ""))
    return ""


def _validate_tolerance(tolerance: dict[str, Any]) -> None:
    for row in tolerance.get("rows", []):
        name = str(row.get("name", ""))
        policy = str(row.get("policy", ""))
        if policy not in ALLOWED_POLICIES.get(name, set()):
            raise ValueError(f"unknown tolerance policy for {name}: {policy}")


def compare_trees(src: Path, restored: Path, tol: dict[str, Any]) -> list[str]:
    _validate_tolerance(tol)
    findings: list[str] = []
    src_entries = _entries(src)
    restored_entries = _entries(restored)

    for rel in sorted(src_entries.keys() - restored_entries.keys()):
        findings.append(f"C: missing path: {rel}")
    for rel in sorted(restored_entries.keys() - src_entries.keys()):
        findings.append(f"C: extra path: {rel}")

    for rel in sorted(src_entries.keys() & restored_entries.keys()):
        src_kind = src_entries[rel]
        restored_kind = restored_entries[rel]
        left = src / rel
        right = restored / rel
        if src_kind != restored_kind:
            findings.append(f"C: kind mismatch for {rel}: {src_kind} != {restored_kind}")
            continue

        if src_kind == "file":
            if not _same_bytes(left, right):
                findings.append(f"A: byte mismatch for {rel}")
            if _mode(left) != _mode(right):
                findings.append(f"B: mode mismatch for {rel}: {oct(_mode(left))} != {oct(_mode(right))}")
            if _row_policy(tol, "file-mtime") == "exact-ns":
                if left.stat().st_mtime_ns != right.stat().st_mtime_ns:
                    findings.append(f"B: file-mtime mismatch for {rel}")
        elif src_kind == "dir":
            if _mode(left) != _mode(right):
                findings.append(f"B: mode mismatch for {rel}: {oct(_mode(left))} != {oct(_mode(right))}")
            if _row_policy(tol, "dir-mtime") == "exact-ns":
                if left.stat().st_mtime_ns != right.stat().st_mtime_ns:
                    findings.append(f"B: dir-mtime mismatch for {rel}")
        elif src_kind == "symlink":
            if os.readlink(left) != os.readlink(right):
                findings.append(f"B: symlink target mismatch for {rel}")

    return findings


def assert_members(members: list[str], present: list[str], absent: list[str]) -> list[str]:
    member_set = set(members)
    findings = [f"member missing: {name}" for name in present if name not in member_set]
    findings.extend(f"member present but expected absent: {name}" for name in absent if name in member_set)
    return findings
