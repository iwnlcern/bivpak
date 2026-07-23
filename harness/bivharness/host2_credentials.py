"""Typed, non-diagnostic credential materialization for host2 profiles."""

from __future__ import annotations

import enum
import errno
import hashlib
import json
import os
import re
import stat
import subprocess
import tempfile
from dataclasses import dataclass
from pathlib import Path
from typing import Callable


class CredentialStatus(enum.Enum):
    OK = "ok"
    SOURCE_MISSING = "source-missing"
    SOURCE_UNREADABLE = "source-unreadable"
    SOURCE_AMBIGUOUS = "source-ambiguous"
    SOURCE_EMPTY = "source-empty"
    SOURCE_OVERSIZE = "source-oversize"
    INVALID_SHAPE = "invalid-shape"
    DEST_UNSAFE = "dest-unsafe"


@dataclass(frozen=True)
class SourceIdentity:
    dev: int
    ino: int
    size: int
    digest: str


@dataclass(frozen=True)
class CredentialResult:
    status: CredentialStatus
    dest: Path | None = None
    identity: SourceIdentity | None = None


_ERRSEC_ITEM_NOT_FOUND = 44
_READ_CHUNK = 16 * 1024
_SNAPSHOT_MAX_BYTES = 64 * 1024


def claude_shape_ok(raw: bytes) -> bool:
    """Accept only the key structure Claude's credential source requires."""
    try:
        value = json.loads(raw)
    except (TypeError, UnicodeDecodeError, ValueError):
        return False
    oauth = value.get("claudeAiOauth") if isinstance(value, dict) else None
    return isinstance(oauth, dict) and "accessToken" in oauth and "refreshToken" in oauth


def codex_shape_ok(raw: bytes) -> bool:
    """Accept only the key structure Codex's credential source requires."""
    try:
        value = json.loads(raw)
    except (TypeError, UnicodeDecodeError, ValueError):
        return False
    if not isinstance(value, dict):
        return False
    tokens = value.get("tokens")
    return (isinstance(tokens, dict) and "access_token" in tokens) or "OPENAI_API_KEY" in value


def _has_symlink_component(path: Path) -> bool:
    """Reject a path whose existing components require following a symlink."""
    path = Path(path)
    parts = path.parts
    current = Path(path.anchor) if path.is_absolute() else Path()
    start = 1 if path.is_absolute() else 0
    for part in parts[start:]:
        current /= part
        try:
            mode = os.lstat(current).st_mode
        except FileNotFoundError:
            return False
        except OSError:
            return True
        if stat.S_ISLNK(mode):
            return True
    return False


def _read_via_nofollow_fd(
    src: Path, max_bytes: int
) -> tuple[CredentialStatus, bytes | None, SourceIdentity | None]:
    """Read a regular source once, proving bytes and identity came from one fd."""
    if _has_symlink_component(Path(src)):
        return CredentialStatus.SOURCE_UNREADABLE, None, None
    try:
        fd = os.open(src, os.O_RDONLY | os.O_NOFOLLOW)
    except OSError as exc:
        if exc.errno == errno.ENOENT:
            return CredentialStatus.SOURCE_MISSING, None, None
        return CredentialStatus.SOURCE_UNREADABLE, None, None

    try:
        first = os.fstat(fd)
        if not stat.S_ISREG(first.st_mode):
            return CredentialStatus.SOURCE_UNREADABLE, None, None

        raw = bytearray()
        oversized = max_bytes < 0
        while not oversized:
            # At the limit, one final byte distinguishes exact-size EOF from oversize.
            request_size = 1 if len(raw) >= max_bytes else min(_READ_CHUNK, max_bytes + 1 - len(raw))
            piece = os.read(fd, request_size)
            if not piece:
                break
            raw.extend(piece)
            oversized = len(raw) > max_bytes

        second = os.fstat(fd)
    except (OSError, TypeError, ValueError):
        return CredentialStatus.SOURCE_UNREADABLE, None, None
    finally:
        try:
            os.close(fd)
        except OSError:
            pass

    if (first.st_dev, first.st_ino, first.st_size) != (second.st_dev, second.st_ino, second.st_size):
        return CredentialStatus.SOURCE_UNREADABLE, None, None
    if oversized:
        return CredentialStatus.SOURCE_OVERSIZE, None, None
    if len(raw) != first.st_size:
        return CredentialStatus.SOURCE_UNREADABLE, None, None
    if not raw:
        return CredentialStatus.SOURCE_EMPTY, None, None

    captured = bytes(raw)
    identity = SourceIdentity(first.st_dev, first.st_ino, first.st_size, hashlib.sha256(captured).hexdigest())
    return CredentialStatus.OK, captured, identity


def snapshot_identity(src: Path) -> SourceIdentity | None:
    """Return an identity only when the source satisfies the same safe-read rules."""
    status, _raw, identity = _read_via_nofollow_fd(src, _SNAPSHOT_MAX_BYTES)
    return identity if status is CredentialStatus.OK else None


def _destination_exists(dest: Path) -> bool | None:
    try:
        os.lstat(dest)
    except FileNotFoundError:
        return False
    except OSError:
        return None
    return True


def _write_all(fd: int, data: bytes) -> None:
    offset = 0
    while offset < len(data):
        count = os.write(fd, data[offset:])
        if count <= 0:
            raise OSError(errno.EIO, "credential temporary-file write failed")
        offset += count


def _atomic_write_0600(dest: Path, data: bytes) -> CredentialResult:
    """Write a new regular destination, refusing unsafe paths and cleaning temp files."""
    dest = Path(dest)
    parent = dest.parent
    fd: int | None = None
    temporary: str | None = None
    replaced = False
    succeeded = False

    try:
        if _has_symlink_component(dest):
            return CredentialResult(CredentialStatus.DEST_UNSAFE)
        parent.mkdir(parents=True, exist_ok=True)
        if _has_symlink_component(dest) or _destination_exists(dest) is not False:
            return CredentialResult(CredentialStatus.DEST_UNSAFE)

        fd, temporary = tempfile.mkstemp(prefix=".host2-credential-", dir=parent)
        os.fchmod(fd, 0o600)
        _write_all(fd, data)
        os.close(fd)
        fd = None

        # Check again just before replacing: rename does not follow a destination symlink.
        if _has_symlink_component(dest) or _destination_exists(dest) is not False:
            return CredentialResult(CredentialStatus.DEST_UNSAFE)
        os.replace(temporary, dest)
        temporary = None
        replaced = True
        os.chmod(dest, 0o600)
        succeeded = True
        return CredentialResult(CredentialStatus.OK, dest)
    except (OSError, TypeError, ValueError):
        return CredentialResult(CredentialStatus.DEST_UNSAFE)
    finally:
        if fd is not None:
            try:
                os.close(fd)
            except OSError:
                pass
        if temporary is not None:
            try:
                os.unlink(temporary)
            except OSError:
                pass
        if replaced and not succeeded:
            # A failed final chmod must not leave a partially-confirmed credential behind.
            try:
                os.unlink(dest)
            except OSError:
                pass


def materialize_file_credential(
    src: Path, dest: Path, *, max_bytes: int, shape_ok: Callable[[bytes], bool]
) -> CredentialResult:
    """Copy a validated ambient credential file without exposing its bytes."""
    status, raw, identity = _read_via_nofollow_fd(Path(src), max_bytes)
    if status is not CredentialStatus.OK:
        return CredentialResult(status)
    try:
        valid_shape = shape_ok(raw)
    except Exception:
        return CredentialResult(CredentialStatus.INVALID_SHAPE)
    if not valid_shape:
        return CredentialResult(CredentialStatus.INVALID_SHAPE)

    written = _atomic_write_0600(Path(dest), raw)
    if written.status is not CredentialStatus.OK:
        return written
    return CredentialResult(CredentialStatus.OK, written.dest, identity)


def _result_output(value: object) -> str:
    if isinstance(value, bytes):
        return value.decode(errors="ignore")
    if isinstance(value, bytearray):
        return bytes(value).decode(errors="ignore")
    return str(value or "")


def _run_keychain(runner: Callable[[list[str]], object], command: list[str]) -> object | None:
    try:
        result = runner(command)
        int(getattr(result, "returncode"))
        getattr(result, "stdout")
    except Exception:
        return None
    return result


def _keychain_bytes(value: object) -> bytes:
    if isinstance(value, bytes):
        return value
    if isinstance(value, bytearray):
        return bytes(value)
    return str(value or "").encode()


def materialize_keychain_credential(
    service: str,
    account: str,
    dest: Path,
    *,
    max_bytes: int,
    shape_ok: Callable[[bytes], bool],
    runner: Callable[[list[str]], object] | None = None,
) -> CredentialResult:
    """Read one exact Keychain item only after fail-closed user-list cardinality proof."""
    run = runner or (lambda command: subprocess.run(command, capture_output=True, check=False))
    listed = _run_keychain(run, ["security", "list-keychains", "-d", "user"])
    if listed is None or getattr(listed, "returncode") != 0:
        return CredentialResult(CredentialStatus.SOURCE_UNREADABLE)

    keychains = re.findall(r'"([^\"]+)"', _result_output(getattr(listed, "stdout")))
    matches: list[str] = []
    probe_error = False
    for keychain in keychains:
        probe = _run_keychain(
            run, ["security", "find-generic-password", "-s", service, "-a", account, keychain]
        )
        if probe is None:
            probe_error = True
            continue
        if probe.returncode == 0:
            matches.append(keychain)
        elif probe.returncode != _ERRSEC_ITEM_NOT_FOUND:
            probe_error = True

    # Any uncertain list or probe makes the match count untrustworthy.
    if probe_error:
        return CredentialResult(CredentialStatus.SOURCE_UNREADABLE)
    if not matches:
        return CredentialResult(CredentialStatus.SOURCE_MISSING)
    if len(matches) != 1:
        return CredentialResult(CredentialStatus.SOURCE_AMBIGUOUS)

    retrieved = _run_keychain(
        run,
        ["security", "find-generic-password", "-s", service, "-a", account, "-w", matches[0]],
    )
    if retrieved is None or retrieved.returncode != 0:
        return CredentialResult(CredentialStatus.SOURCE_UNREADABLE)

    raw = _keychain_bytes(retrieved.stdout)
    if raw.endswith(b"\n"):
        raw = raw[:-1]
    if not raw:
        return CredentialResult(CredentialStatus.SOURCE_EMPTY)
    if len(raw) > max_bytes:
        return CredentialResult(CredentialStatus.SOURCE_OVERSIZE)
    try:
        valid_shape = shape_ok(raw)
    except Exception:
        return CredentialResult(CredentialStatus.INVALID_SHAPE)
    if not valid_shape:
        return CredentialResult(CredentialStatus.INVALID_SHAPE)
    return _atomic_write_0600(Path(dest), raw)
