import json
import uuid
from datetime import datetime
from pathlib import Path
from typing import Any

from jsonschema import Draft202012Validator


SCHEMA_PATH = Path(__file__).resolve().parents[1] / "schemas" / "manifest-plaindir-v1.schema.json"


def _schema() -> dict[str, Any]:
    return json.loads(SCHEMA_PATH.read_text(encoding="utf-8"))


def _is_uuid4(value: str) -> bool:
    try:
        parsed = uuid.UUID(value)
    except ValueError:
        return False
    return parsed.version == 4


def _is_iso8601_utc(value: str) -> bool:
    if not value.endswith("Z"):
        return False
    try:
        datetime.fromisoformat(value[:-1] + "+00:00")
    except ValueError:
        return False
    return True


def _path(error: Any) -> str:
    return ".".join(str(part) for part in error.path) or "<root>"


def validate_manifest(manifest: dict[str, Any], variant: str) -> list[str]:
    errors = [
        f"{_path(error)}: {error.message}"
        for error in Draft202012Validator(_schema()).iter_errors(manifest)
    ]
    if errors:
        return sorted(errors)

    if manifest["format_version"] != 1:
        errors.append("format_version must be 1")
    if manifest["required_capabilities"] != []:
        errors.append("required_capabilities must be []")
    if manifest["repos"] != []:
        errors.append("repos must be [] for Step-2 plain-dir")
    if manifest["agent_sessions"] != []:
        errors.append("agent_sessions must be []")
    for forbidden in ("agent_memory", "memory"):
        if forbidden in manifest:
            errors.append(f"{forbidden} must be absent")
    if not _is_uuid4(manifest["image_id"]):
        errors.append("image_id must be uuid4")
    if not _is_iso8601_utc(manifest["created_at"]):
        errors.append("created_at must be ISO-8601 UTC")

    bivignore = manifest["bivignore"]
    if variant == "file":
        if bivignore.get("source") != "file":
            errors.append("bivignore.source must be file")
        if bivignore.get("builtin_id") is not None:
            errors.append("bivignore.builtin_id must be null for file variant")
    elif variant == "builtin":
        if bivignore.get("source") != "builtin":
            errors.append("bivignore.source must be builtin")
        if bivignore.get("builtin_id") != "builtin-v1":
            errors.append("bivignore.builtin_id must be builtin-v1")
    else:
        errors.append(f"unknown manifest variant: {variant}")

    return sorted(errors)
