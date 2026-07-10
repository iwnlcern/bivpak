import json
import re
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
    if not _is_uuid4(manifest["image_id"]):
        errors.append("image_id must be uuid4")
    if not _is_iso8601_utc(manifest["created_at"]):
        errors.append("created_at must be ISO-8601 UTC")

    seen_sessions: set[tuple[str, str]] = set()
    seen_artifacts: set[str] = set()
    agent_pattern = re.compile(r"^[a-z0-9][a-z0-9._-]*$")
    session_id_pattern = re.compile(r"^[^/\\\x00-\x1f\x7f]+$")
    for index, entry in enumerate(manifest["agent_sessions"]):
        agent = entry["agent"]
        if not agent_pattern.fullmatch(agent):
            errors.append(f"agent_sessions.{index}.agent grammar invalid")
        if entry["entry_schema"] > 1:
            continue
        primary = entry["original_session_ids"]["primary"]
        if primary in (".", "..") or not session_id_pattern.fullmatch(primary):
            errors.append(f"agent_sessions.{index} primary id grammar invalid")
        session_key = (agent, primary)
        if session_key in seen_sessions:
            errors.append(f"agent_sessions.{index} session must be unique")
        seen_sessions.add(session_key)

        ids = entry["original_session_ids"]
        parent = ids.get("parent")
        if parent is not None and (
            parent in (".", "..") or not session_id_pattern.fullmatch(parent)
        ):
            errors.append(f"agent_sessions.{index} parent id grammar invalid")
        if "parent_in_image" in ids and (
            parent is None or ids["parent_in_image"] is not False
        ):
            errors.append(f"agent_sessions.{index} dangling parent invalid")

        prefix = f"agents/{agent}/"
        artifacts = list(entry["artifacts"])
        for child in entry["children"]:
            child_id = child["original_id"]
            if child_id in (".", "..") or not session_id_pattern.fullmatch(child_id):
                errors.append(f"agent_sessions.{index} child id grammar invalid")
            artifacts.extend(child["artifacts"])
        for artifact in artifacts:
            segments = artifact.split("/")
            rest = artifact[len(prefix):] if artifact.startswith(prefix) else ""
            first_rest = rest.split("/", 1)[0]
            if (
                not artifact.startswith(prefix)
                or "\\" in artifact
                or artifact.startswith("/")
                or any(segment in ("", ".", "..") for segment in segments)
                or ":" in first_rest
            ):
                errors.append(
                    f"agent_sessions.{index} artifact containment invalid"
                )
            if artifact in seen_artifacts:
                errors.append(f"agent_sessions.{index} artifact must be unique")
            seen_artifacts.add(artifact)
    for index, entry in enumerate(manifest["agent_sessions"]):
        if entry["entry_schema"] > 1:
            continue
        ids = entry["original_session_ids"]
        parent = ids.get("parent")
        if parent is None:
            continue
        parent_in_set = (entry["agent"], parent) in seen_sessions
        if (parent_in_set and "parent_in_image" in ids) or (
            not parent_in_set and ids.get("parent_in_image") is not False
        ):
            errors.append(f"agent_sessions.{index} parent relationship invalid")

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
