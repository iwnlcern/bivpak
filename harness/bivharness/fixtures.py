import base64
import os
from pathlib import Path
from typing import Any


class SpecError(ValueError):
    pass


def _safe_path(root: Path, relpath: str) -> Path:
    root_real = root.resolve()
    candidate = root.joinpath(relpath).resolve(strict=False)
    if not candidate.is_relative_to(root_real):
        raise SpecError(f"path escapes fixture root: {relpath}")
    return candidate


def _entry_bytes(entry: dict[str, Any]) -> bytes:
    has_text = "text" in entry
    has_b64 = "bytes_b64" in entry
    if has_text == has_b64:
        raise SpecError("file entry requires exactly one of text or bytes_b64")
    if has_text:
        return str(entry["text"]).encode("utf-8")
    try:
        return base64.b64decode(str(entry["bytes_b64"]), validate=True)
    except Exception as exc:
        raise SpecError("invalid bytes_b64") from exc


def materialize(spec: dict[str, Any], root: Path) -> None:
    root.mkdir(parents=True, exist_ok=True)
    for entry in spec.get("entries", []):
        entry_type = entry.get("type")
        path = _safe_path(root, str(entry.get("path", "")))

        if entry_type == "dir":
            path.mkdir(parents=True, exist_ok=True)
            if "mode" in entry:
                os.chmod(path, int(str(entry["mode"]), 8))
            continue

        if entry_type == "file":
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_bytes(_entry_bytes(entry))
            if "mode" in entry:
                os.chmod(path, int(str(entry["mode"]), 8))
            continue

        if entry_type == "symlink":
            path.parent.mkdir(parents=True, exist_ok=True)
            try:
                path.unlink()
            except FileNotFoundError:
                pass
            os.symlink(str(entry["target"]), path)
            continue

        raise SpecError(f"unsupported fixture entry type: {entry_type}")
