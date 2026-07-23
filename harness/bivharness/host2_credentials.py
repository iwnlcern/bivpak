"""Typed, non-diagnostic credential materialization for host2 profiles."""

from __future__ import annotations

import ctypes
import enum
import errno
import hashlib
import json
import os
import re
import secrets
import stat
import subprocess
import sys
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
_CLOEXEC = getattr(os, "O_CLOEXEC", 0)
_DIRECTORY_FLAGS = os.O_RDONLY | os.O_DIRECTORY | os.O_NOFOLLOW | _CLOEXEC
_RENAME_EXCL = 0x00000004


def _load_renameatx_np():
    if sys.platform != "darwin":
        return None
    try:
        primitive = ctypes.CDLL(None, use_errno=True).renameatx_np
    except (AttributeError, OSError):
        return None
    primitive.argtypes = [
        ctypes.c_int,
        ctypes.c_char_p,
        ctypes.c_int,
        ctypes.c_char_p,
        ctypes.c_uint,
    ]
    primitive.restype = ctypes.c_int
    return primitive


_RENAMEATX_NP = _load_renameatx_np()


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


def _close_fd(fd: int | None) -> None:
    if fd is None:
        return
    try:
        os.close(fd)
    except OSError:
        pass


def _open_directory(path: Path, *, create: bool) -> int:
    """Open a directory by walking each component without following symlinks."""
    path = Path(path)
    current = os.open(path.anchor if path.is_absolute() else ".", _DIRECTORY_FLAGS)
    start = 1 if path.is_absolute() else 0
    try:
        for component in path.parts[start:]:
            if component in ("", "."):
                continue
            if component == "..":
                raise OSError(errno.EINVAL, "parent traversal is not allowed")
            try:
                next_fd = os.open(component, _DIRECTORY_FLAGS, dir_fd=current)
            except OSError as exc:
                if not create or exc.errno != errno.ENOENT:
                    raise
                try:
                    os.mkdir(component, mode=0o700, dir_fd=current)
                except OSError as mkdir_exc:
                    if mkdir_exc.errno != errno.EEXIST:
                        raise
                next_fd = os.open(component, _DIRECTORY_FLAGS, dir_fd=current)
            _close_fd(current)
            current = next_fd
        return current
    except BaseException:
        _close_fd(current)
        raise


def _open_file_nofollow(src: Path) -> int:
    src = Path(src)
    if src.name in ("", ".", ".."):
        raise OSError(errno.EINVAL, "invalid source leaf")
    parent_fd = _open_directory(src.parent, create=False)
    try:
        return os.open(src.name, os.O_RDONLY | os.O_NOFOLLOW | _CLOEXEC, dir_fd=parent_fd)
    finally:
        _close_fd(parent_fd)


def _read_via_nofollow_fd(
    src: Path, max_bytes: int
) -> tuple[CredentialStatus, bytes | None, SourceIdentity | None]:
    """Read a regular source once, proving bytes and identity came from one fd."""
    try:
        fd = _open_file_nofollow(Path(src))
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
        _close_fd(fd)

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


def snapshot_identity(src: Path, *, max_bytes: int) -> SourceIdentity | None:
    """Return an identity only when the source satisfies the same safe-read rules."""
    status, _raw, identity = _read_via_nofollow_fd(src, max_bytes)
    return identity if status is CredentialStatus.OK else None


def _entry_exists_at(parent_fd: int, name: str) -> bool:
    try:
        os.stat(name, dir_fd=parent_fd, follow_symlinks=False)
    except FileNotFoundError:
        return False
    return True


def _write_all(fd: int, data: bytes) -> None:
    offset = 0
    while offset < len(data):
        count = os.write(fd, data[offset:])
        if count <= 0:
            raise OSError(errno.EIO, "credential temporary-file write failed")
        offset += count


def _mkstemp_at(parent_fd: int) -> tuple[int, str]:
    for _attempt in range(100):
        name = f".host2-credential-{secrets.token_hex(8)}"
        try:
            fd = os.open(
                name,
                os.O_WRONLY | os.O_CREAT | os.O_EXCL | os.O_NOFOLLOW | _CLOEXEC,
                0o600,
                dir_fd=parent_fd,
            )
        except FileExistsError:
            continue
        return fd, name
    raise FileExistsError(errno.EEXIST, "unable to allocate credential temporary file")


def _replace_at(parent_fd: int, temporary: str, destination: str) -> None:
    """Make the final install an atomic, exclusive, descriptor-relative move."""
    primitive = _RENAMEATX_NP
    if primitive is None:
        raise OSError(errno.ENOTSUP, "exclusive credential install is unsupported")
    ctypes.set_errno(0)
    result = primitive(
        parent_fd,
        os.fsencode(temporary),
        parent_fd,
        os.fsencode(destination),
        _RENAME_EXCL,
    )
    if result != 0:
        error = ctypes.get_errno() or errno.EIO
        raise OSError(error, "exclusive credential install failed")


def _directory_identity_matches(path: Path, expected_fd: int) -> bool:
    verification_fd = _open_directory(path, create=False)
    try:
        expected = os.fstat(expected_fd)
        verification = os.fstat(verification_fd)
        return (expected.st_dev, expected.st_ino) == (verification.st_dev, verification.st_ino)
    finally:
        _close_fd(verification_fd)


def _atomic_write_0600(dest: Path, data: bytes) -> CredentialResult:
    """Write a new regular destination, refusing unsafe paths and cleaning temp files."""
    dest = Path(dest)
    parent_fd: int | None = None
    temporary_fd: int | None = None
    temporary: str | None = None

    try:
        if dest.name in ("", ".", ".."):
            return CredentialResult(CredentialStatus.DEST_UNSAFE)
        parent_fd = _open_directory(dest.parent, create=True)
        if _entry_exists_at(parent_fd, dest.name):
            return CredentialResult(CredentialStatus.DEST_UNSAFE)

        temporary_fd, temporary = _mkstemp_at(parent_fd)
        os.fchmod(temporary_fd, 0o600)
        _write_all(temporary_fd, data)
        _close_fd(temporary_fd)
        temporary_fd = None

        if not _directory_identity_matches(dest.parent, parent_fd):
            return CredentialResult(CredentialStatus.DEST_UNSAFE)
        _replace_at(parent_fd, temporary, dest.name)
        temporary = None
        return CredentialResult(CredentialStatus.OK, dest)
    except (OSError, TypeError, ValueError):
        return CredentialResult(CredentialStatus.DEST_UNSAFE)
    finally:
        _close_fd(temporary_fd)
        if temporary is not None and parent_fd is not None:
            try:
                os.unlink(temporary, dir_fd=parent_fd)
            except OSError:
                pass
        _close_fd(parent_fd)


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
