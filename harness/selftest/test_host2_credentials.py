import errno
import hashlib
import json
import multiprocessing
import os
import socket
import stat
import tempfile
from pathlib import Path
from types import SimpleNamespace

import pytest

from bivharness import host2_credentials as credentials
from bivharness.host2_credentials import (
    CredentialStatus,
    claude_shape_ok,
    codex_shape_ok,
    materialize_file_credential,
    materialize_keychain_credential,
    snapshot_identity,
)


CLAUDE_OK = json.dumps(
    {"claudeAiOauth": {"accessToken": "CLAUDE_TEST_VALUE", "refreshToken": "REFRESH_TEST_VALUE"}}
).encode()
CODEX_OK = json.dumps(
    {"tokens": {"access_token": "CODEX_TEST_VALUE"}, "OPENAI_API_KEY": "API_TEST_VALUE"}
).encode()


def _fifo_source_worker(operation, src, dest, connection):
    try:
        if operation == "materialize":
            result = materialize_file_credential(
                Path(src),
                Path(dest),
                max_bytes=1_000_000,
                shape_ok=codex_shape_ok,
            )
            connection.send(("status", result.status.value))
        else:
            identity = snapshot_identity(Path(src), max_bytes=1_000_000)
            connection.send(("identity", identity is None))
    except BaseException as exc:
        connection.send(("error", type(exc).__name__))
    finally:
        connection.close()


def test_file_copies_bytes_0600_and_sets_identity(tmp_path):
    src = tmp_path / "auth.json"
    src.write_bytes(CODEX_OK)
    dest = tmp_path / "store" / "auth.json"

    result = materialize_file_credential(src, dest, max_bytes=1_000_000, shape_ok=codex_shape_ok)

    assert result.status is CredentialStatus.OK
    assert dest.read_bytes() == CODEX_OK
    assert dest.stat().st_mode & 0o777 == 0o600
    assert result.identity is not None
    assert result.identity.digest == snapshot_identity(src, max_bytes=1_000_000).digest
    assert result.identity.size == len(CODEX_OK)


@pytest.mark.skipif(not hasattr(os, "mkfifo"), reason="FIFO sources are unavailable")
@pytest.mark.parametrize("operation", ("materialize", "snapshot"))
def test_fifo_source_is_rejected_without_blocking(tmp_path, operation):
    src = tmp_path / "credential-fifo"
    os.mkfifo(src)
    dest = tmp_path / "dest" / "auth.json"
    context = multiprocessing.get_context("spawn")
    receive, send = context.Pipe(duplex=False)
    process = context.Process(
        target=_fifo_source_worker,
        args=(operation, str(src), str(dest), send),
    )
    process.start()
    send.close()
    process.join(timeout=5)
    if process.is_alive():
        process.kill()
        process.join()
        receive.close()
        pytest.fail(f"{operation} blocked while opening a FIFO credential source")

    assert process.exitcode == 0
    assert receive.poll(timeout=1)
    outcome = receive.recv()
    receive.close()
    if operation == "materialize":
        assert outcome == ("status", CredentialStatus.SOURCE_UNREADABLE.value)
        assert not dest.exists()
    else:
        assert outcome == ("identity", True)


@pytest.mark.parametrize("source_kind", ("device", "socket"))
def test_shared_reader_rejects_portable_nonregular_sources(tmp_path, source_kind):
    opened_socket = None
    socket_parent = None
    if source_kind == "device":
        src = Path(os.devnull)
        if not stat.S_ISCHR(src.stat().st_mode):
            pytest.skip("os.devnull is not a character device")
    else:
        if not hasattr(socket, "AF_UNIX"):
            pytest.skip("Unix-domain sockets are unavailable")
        socket_parent = tempfile.TemporaryDirectory(
            prefix="biv-h2-sock-",
            dir=Path(tempfile.gettempdir()).resolve(),
        )
        src = Path(socket_parent.name) / "credential.sock"
        opened_socket = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
        opened_socket.bind(str(src))

    try:
        dest = tmp_path / source_kind / "auth.json"
        result = materialize_file_credential(
            src,
            dest,
            max_bytes=1_000_000,
            shape_ok=codex_shape_ok,
        )

        assert result.status is CredentialStatus.SOURCE_UNREADABLE
        assert snapshot_identity(src, max_bytes=1_000_000) is None
        assert not dest.exists()
    finally:
        if opened_socket is not None:
            opened_socket.close()
        if socket_parent is not None:
            socket_parent.cleanup()


def test_source_leaf_open_retains_nofollow_cloexec_and_nonblock(tmp_path, monkeypatch):
    src = tmp_path / "auth.json"
    src.write_bytes(CODEX_OK)
    real_open = os.open
    leaf_flags = []

    def tracking_open(path, flags, mode=0o777, *, dir_fd=None):
        if path == src.name and dir_fd is not None:
            leaf_flags.append(flags)
        return real_open(path, flags, mode, dir_fd=dir_fd)

    monkeypatch.setattr(credentials.os, "open", tracking_open)

    assert snapshot_identity(src, max_bytes=1_000_000) is not None
    assert len(leaf_flags) == 1
    for flag_name in ("O_NOFOLLOW", "O_CLOEXEC", "O_NONBLOCK"):
        flag = getattr(os, flag_name, 0)
        if flag:
            assert leaf_flags[0] & flag


def test_file_refuses_symlink_nonregular_missing_empty_oversize_and_wrong_shape(tmp_path):
    real = tmp_path / "real"
    real.write_bytes(CODEX_OK)
    link = tmp_path / "link"
    link.symlink_to(real)
    assert materialize_file_credential(
        link, tmp_path / "a" / "auth.json", max_bytes=1_000_000, shape_ok=codex_shape_ok
    ).status is CredentialStatus.SOURCE_UNREADABLE

    source_parent = tmp_path / "source-parent"
    source_parent.mkdir()
    (source_parent / "auth.json").write_bytes(CODEX_OK)
    linked_parent = tmp_path / "linked-parent"
    linked_parent.symlink_to(source_parent, target_is_directory=True)
    assert materialize_file_credential(
        linked_parent / "auth.json", tmp_path / "a" / "parent-link.json", max_bytes=1_000_000, shape_ok=codex_shape_ok
    ).status is CredentialStatus.SOURCE_UNREADABLE

    assert materialize_file_credential(
        tmp_path, tmp_path / "directory-copy", max_bytes=1_000_000, shape_ok=codex_shape_ok
    ).status is CredentialStatus.SOURCE_UNREADABLE
    assert materialize_file_credential(
        tmp_path / "nope", tmp_path / "b", max_bytes=10, shape_ok=codex_shape_ok
    ).status is CredentialStatus.SOURCE_MISSING

    empty = tmp_path / "empty"
    empty.write_bytes(b"")
    assert materialize_file_credential(
        empty, tmp_path / "c", max_bytes=10, shape_ok=codex_shape_ok
    ).status is CredentialStatus.SOURCE_EMPTY

    big = tmp_path / "big"
    big.write_bytes(b"x" * 100)
    assert materialize_file_credential(
        big, tmp_path / "d", max_bytes=10, shape_ok=codex_shape_ok
    ).status is CredentialStatus.SOURCE_OVERSIZE

    invalid = tmp_path / "invalid"
    invalid.write_bytes(b'{"nope": 1}')
    assert materialize_file_credential(
        invalid, tmp_path / "e", max_bytes=1_000_000, shape_ok=codex_shape_ok
    ).status is CredentialStatus.INVALID_SHAPE


def test_file_refuses_symlink_destination(tmp_path):
    src = tmp_path / "auth.json"
    src.write_bytes(CODEX_OK)
    target = tmp_path / "target"
    target.write_bytes(b"unchanged")
    dest = tmp_path / "dest"
    dest.symlink_to(target)

    result = materialize_file_credential(src, dest, max_bytes=1_000_000, shape_ok=codex_shape_ok)

    assert result.status is CredentialStatus.DEST_UNSAFE
    assert target.read_bytes() == b"unchanged"


def test_source_parent_substitution_cannot_change_opened_bytes(tmp_path, monkeypatch):
    source_parent = tmp_path / "source"
    source_parent.mkdir()
    src = source_parent / "auth.json"
    src.write_bytes(CODEX_OK)
    original_identity = src.stat()

    attacker_parent = tmp_path / "attacker"
    attacker_parent.mkdir()
    attacker_bytes = json.dumps({"tokens": {"access_token": "ATTACKER_VALUE"}}).encode()
    (attacker_parent / "auth.json").write_bytes(attacker_bytes)
    moved_parent = tmp_path / "source-original"
    dest = tmp_path / "dest" / "auth.json"
    real_open = os.open
    swapped = False

    def racing_open(path, flags, mode=0o777, *, dir_fd=None):
        nonlocal swapped
        is_old_leaf_open = Path(path) == src and dir_fd is None
        is_secure_leaf_open = path == src.name and dir_fd is not None
        if not swapped and (is_old_leaf_open or is_secure_leaf_open):
            source_parent.rename(moved_parent)
            source_parent.symlink_to(attacker_parent, target_is_directory=True)
            swapped = True
        return real_open(path, flags, mode, dir_fd=dir_fd)

    monkeypatch.setattr(credentials.os, "open", racing_open)
    result = materialize_file_credential(src, dest, max_bytes=1_000_000, shape_ok=codex_shape_ok)

    assert swapped
    assert result.status is CredentialStatus.OK
    assert dest.read_bytes() == CODEX_OK
    assert result.identity.dev == original_identity.st_dev
    assert result.identity.ino == original_identity.st_ino
    assert result.identity.digest == hashlib.sha256(CODEX_OK).hexdigest()


def test_destination_parent_substitution_is_typed_and_cleans_original_dir(tmp_path, monkeypatch):
    src = tmp_path / "auth.json"
    src.write_bytes(CODEX_OK)
    dest_parent = tmp_path / "dest"
    dest_parent.mkdir()
    dest = dest_parent / "auth.json"

    attacker_parent = tmp_path / "attacker"
    attacker_parent.mkdir()
    attacker_dest = attacker_parent / "auth.json"
    attacker_dest.write_bytes(b"attacker-file-unchanged")
    moved_parent = tmp_path / "dest-original"
    real_mkstemp_at = getattr(credentials, "_mkstemp_at", None)
    swapped = False

    def racing_mkstemp_at(dir_fd):
        nonlocal swapped
        dest_parent.rename(moved_parent)
        dest_parent.symlink_to(attacker_parent, target_is_directory=True)
        swapped = True
        return real_mkstemp_at(dir_fd)

    monkeypatch.setattr(credentials, "_mkstemp_at", racing_mkstemp_at, raising=False)
    result = materialize_file_credential(src, dest, max_bytes=1_000_000, shape_ok=codex_shape_ok)

    assert swapped
    assert result.status is CredentialStatus.DEST_UNSAFE
    assert attacker_dest.read_bytes() == b"attacker-file-unchanged"
    assert not (moved_parent / "auth.json").exists()
    assert not list(moved_parent.glob(".host2-credential-*"))


def test_destination_leaf_created_after_preflight_is_preserved(tmp_path, monkeypatch):
    src = tmp_path / "auth.json"
    src.write_bytes(CODEX_OK)
    dest = tmp_path / "dest" / "auth.json"
    competing_bytes = b"competing-leaf-must-survive"
    real_replace_at = credentials._replace_at
    raced = False

    def racing_replace_at(parent_fd, temporary, destination):
        nonlocal raced
        competing_fd = os.open(
            destination,
            os.O_WRONLY | os.O_CREAT | os.O_EXCL | os.O_NOFOLLOW,
            0o600,
            dir_fd=parent_fd,
        )
        try:
            os.write(competing_fd, competing_bytes)
        finally:
            os.close(competing_fd)
        raced = True
        return real_replace_at(parent_fd, temporary, destination)

    monkeypatch.setattr(credentials, "_replace_at", racing_replace_at)
    result = materialize_file_credential(src, dest, max_bytes=1_000_000, shape_ok=codex_shape_ok)

    assert raced
    assert result.status is CredentialStatus.DEST_UNSAFE
    assert dest.read_bytes() == competing_bytes
    assert not list(dest.parent.glob(".host2-credential-*"))


def test_exclusive_move_uses_renameat2_noreplace_when_available(tmp_path, monkeypatch):
    calls = []

    def renameat2(src_fd, src, dest_fd, dest, flags):
        calls.append((src_fd, src, dest_fd, dest, flags))
        return 0

    monkeypatch.setattr(credentials, "_RENAMEATX_NP", None)
    monkeypatch.setattr(credentials, "_RENAMEAT2", renameat2)
    parent_fd = os.open(tmp_path, os.O_RDONLY | os.O_DIRECTORY)
    try:
        credentials._replace_at(parent_fd, "temporary", "credential")
    finally:
        os.close(parent_fd)

    assert calls == [
        (
            parent_fd,
            b"temporary",
            parent_fd,
            b"credential",
            credentials._RENAME_NOREPLACE,
        )
    ]


def test_no_destination_target_after_atomic_commit(tmp_path, monkeypatch):
    src = tmp_path / "auth.json"
    src.write_bytes(CODEX_OK)
    dest = tmp_path / "dest" / "auth.json"
    dest.parent.mkdir()
    competing_bytes = b"post-install-competitor-must-survive"
    competitor = dest.parent / ".post-install-competitor"
    competitor.write_bytes(competing_bytes)
    real_replace_at = credentials._replace_at
    real_directory_identity_matches = credentials._directory_identity_matches
    real_stat = os.stat
    committed = False
    race_attempted = False

    def tracking_replace_at(parent_fd, temporary, destination):
        nonlocal committed
        real_replace_at(parent_fd, temporary, destination)
        committed = True

    def phase_sensitive_identity(path, parent_fd):
        if committed:
            return False
        return real_directory_identity_matches(path, parent_fd)

    def racing_stat(path, *args, dir_fd=None, follow_symlinks=True, **kwargs):
        nonlocal race_attempted
        if committed and path == dest.name and dir_fd is not None and follow_symlinks is False:
            installed = real_stat(
                path,
                *args,
                dir_fd=dir_fd,
                follow_symlinks=follow_symlinks,
                **kwargs,
            )
            os.rename(
                competitor.name,
                dest.name,
                src_dir_fd=dir_fd,
                dst_dir_fd=dir_fd,
            )
            race_attempted = True
            return installed
        return real_stat(
            path,
            *args,
            dir_fd=dir_fd,
            follow_symlinks=follow_symlinks,
            **kwargs,
        )

    monkeypatch.setattr(credentials, "_replace_at", tracking_replace_at)
    monkeypatch.setattr(credentials, "_directory_identity_matches", phase_sensitive_identity)
    monkeypatch.setattr(credentials.os, "stat", racing_stat)
    result = materialize_file_credential(src, dest, max_bytes=1_000_000, shape_ok=codex_shape_ok)

    assert result.status is CredentialStatus.OK
    assert committed
    assert not race_attempted
    assert dest.read_bytes() == CODEX_OK
    assert competitor.read_bytes() == competing_bytes
    assert not list(dest.parent.glob(".host2-credential-*"))


@pytest.mark.parametrize("primitive_state", ["unsupported", "failure"])
def test_exclusive_move_failure_is_typed_and_cleans_temp(tmp_path, monkeypatch, primitive_state):
    src = tmp_path / "auth.json"
    src.write_bytes(CODEX_OK)
    dest = tmp_path / "dest" / "auth.json"

    if primitive_state == "unsupported":
        primitive = None
    else:
        def primitive(*_args):
            import ctypes

            ctypes.set_errno(errno.EIO)
            return -1

    monkeypatch.setattr(credentials, "_RENAMEATX_NP", primitive, raising=False)
    monkeypatch.setattr(credentials, "_RENAMEAT2", None, raising=False)
    result = materialize_file_credential(src, dest, max_bytes=1_000_000, shape_ok=codex_shape_ok)

    assert result.status is CredentialStatus.DEST_UNSAFE
    assert not dest.exists()
    assert not list(dest.parent.glob(".host2-credential-*"))


def test_file_reads_to_eof_when_reads_are_short(tmp_path, monkeypatch):
    src = tmp_path / "auth.json"
    src.write_bytes(CODEX_OK)
    dest = tmp_path / "dest"
    real_read = os.read

    def short_read(fd, size):
        return real_read(fd, min(size, 3))

    monkeypatch.setattr(credentials.os, "read", short_read)
    result = materialize_file_credential(src, dest, max_bytes=1_000_000, shape_ok=codex_shape_ok)

    assert result.status is CredentialStatus.OK
    assert dest.read_bytes() == CODEX_OK
    assert result.identity.digest == hashlib.sha256(CODEX_OK).hexdigest()


def test_file_rejects_short_read_before_fstat_size(tmp_path, monkeypatch):
    src = tmp_path / "auth.json"
    src.write_bytes(CODEX_OK)
    real_read = os.read
    calls = 0

    def early_eof(fd, size):
        nonlocal calls
        calls += 1
        return real_read(fd, min(size, 3)) if calls == 1 else b""

    monkeypatch.setattr(credentials.os, "read", early_eof)
    result = materialize_file_credential(src, tmp_path / "dest", max_bytes=1_000_000, shape_ok=codex_shape_ok)

    assert result.status is CredentialStatus.SOURCE_UNREADABLE


def test_shape_validators_only_require_source_specific_keys():
    assert claude_shape_ok(CLAUDE_OK)
    assert not claude_shape_ok(CODEX_OK)
    assert codex_shape_ok(CODEX_OK)
    assert not codex_shape_ok(CLAUDE_OK)
    assert claude_shape_ok(b'{"claudeAiOauth": {"accessToken": null, "refreshToken": null}}')
    assert codex_shape_ok(b'{"tokens": {"access_token": null}}')
    assert codex_shape_ok(b'{"OPENAI_API_KEY": null}')
    assert not claude_shape_ok(b"not json")


def test_snapshot_identity_uses_safe_reader_and_detects_change(tmp_path):
    path = tmp_path / "auth.json"
    path.write_bytes(CODEX_OK)
    original = snapshot_identity(path, max_bytes=1_000_000)

    assert snapshot_identity(path, max_bytes=1_000_000) == original
    assert snapshot_identity(tmp_path / "missing", max_bytes=1_000_000) is None
    path.write_bytes(CODEX_OK + b" ")
    assert snapshot_identity(path, max_bytes=1_000_000) != original


def test_snapshot_identity_accepts_source_over_64k_under_explicit_limit(tmp_path):
    raw = json.dumps({"tokens": {"access_token": "A"}, "padding": "x" * (70 * 1024)}).encode()
    src = tmp_path / "large-auth.json"
    src.write_bytes(raw)
    max_bytes = len(raw) + 1

    result = materialize_file_credential(
        src, tmp_path / "dest" / "auth.json", max_bytes=max_bytes, shape_ok=codex_shape_ok
    )
    identity = snapshot_identity(src, max_bytes=max_bytes)

    assert result.status is CredentialStatus.OK
    assert identity is not None
    assert identity == result.identity


def _keychain_runner(list_out, per_keychain, value=CLAUDE_OK, *, list_returncode=0, read_returncode=0):
    def run(command):
        if command[:2] == ["security", "list-keychains"]:
            return SimpleNamespace(returncode=list_returncode, stdout=list_out, stderr=b"")
        if "-w" in command:
            return SimpleNamespace(returncode=read_returncode, stdout=value + b"\n", stderr=b"")
        keychain = command[-1]
        return SimpleNamespace(returncode=per_keychain.get(keychain, 44), stdout=b"", stderr=b"")

    return run


def test_keychain_single_match_ok(tmp_path):
    dest = tmp_path / "cfg" / ".credentials.json"
    runner = _keychain_runner(
        b'"/Users/jack/Library/Keychains/login.keychain-db"\n',
        {"/Users/jack/Library/Keychains/login.keychain-db": 0},
    )

    result = materialize_keychain_credential(
        "Claude Code-credentials", "jack", dest, max_bytes=1_000_000, shape_ok=claude_shape_ok, runner=runner
    )

    assert result.status is CredentialStatus.OK
    assert result.identity is None
    assert dest.read_bytes() == CLAUDE_OK
    assert dest.stat().st_mode & 0o777 == 0o600


def test_keychain_list_failure_is_unreadable_before_cardinality(tmp_path):
    calls = []

    def runner(command):
        calls.append(command)
        return SimpleNamespace(returncode=51, stdout=b'"/a.keychain-db"\n', stderr=b"unavailable")

    result = materialize_keychain_credential(
        "S", "jack", tmp_path / "dest", max_bytes=10, shape_ok=claude_shape_ok, runner=runner
    )

    assert result.status is CredentialStatus.SOURCE_UNREADABLE
    assert calls == [["security", "list-keychains", "-d", "user"]]


def test_keychain_runner_exception_is_typed_without_value_in_error(tmp_path):
    secret = "RUNNER_EXCEPTION_CREDENTIAL_VALUE"

    def runner(_command):
        raise RuntimeError(secret)

    result = materialize_keychain_credential(
        "S", "jack", tmp_path / "dest", max_bytes=10, shape_ok=claude_shape_ok, runner=runner
    )

    assert result.status is CredentialStatus.SOURCE_UNREADABLE
    assert secret not in repr(result)


def test_keychain_probe_error_overrides_one_match(tmp_path):
    calls = []
    runner = _keychain_runner(b'"/a.keychain-db"\n"/b.keychain-db"\n', {"/a.keychain-db": 0, "/b.keychain-db": 51})

    def recording_runner(command):
        calls.append(command)
        return runner(command)

    result = materialize_keychain_credential(
        "S", "jack", tmp_path / "dest", max_bytes=1_000_000, shape_ok=claude_shape_ok, runner=recording_runner
    )

    assert result.status is CredentialStatus.SOURCE_UNREADABLE
    assert not any("-w" in command for command in calls)


def test_keychain_zero_multiple_read_failure_and_invalid_values(tmp_path):
    two = b'"/a.keychain-db"\n"/b.keychain-db"\n'
    missing = materialize_keychain_credential(
        "S", "jack", tmp_path / "missing", max_bytes=1_000_000, shape_ok=claude_shape_ok,
        runner=_keychain_runner(two, {}),
    )
    ambiguous = materialize_keychain_credential(
        "S", "jack", tmp_path / "ambiguous", max_bytes=1_000_000, shape_ok=claude_shape_ok,
        runner=_keychain_runner(two, {"/a.keychain-db": 0, "/b.keychain-db": 0}),
    )
    read_failure = materialize_keychain_credential(
        "S", "jack", tmp_path / "read-failure", max_bytes=1_000_000, shape_ok=claude_shape_ok,
        runner=_keychain_runner(b'"/a.keychain-db"\n', {"/a.keychain-db": 0}, read_returncode=51),
    )
    empty = materialize_keychain_credential(
        "S", "jack", tmp_path / "empty", max_bytes=1_000_000, shape_ok=claude_shape_ok,
        runner=_keychain_runner(b'"/a.keychain-db"\n', {"/a.keychain-db": 0}, value=b""),
    )
    oversized = materialize_keychain_credential(
        "S", "jack", tmp_path / "oversized", max_bytes=4, shape_ok=claude_shape_ok,
        runner=_keychain_runner(b'"/a.keychain-db"\n', {"/a.keychain-db": 0}),
    )
    invalid = materialize_keychain_credential(
        "S", "jack", tmp_path / "invalid", max_bytes=1_000_000, shape_ok=claude_shape_ok,
        runner=_keychain_runner(b'"/a.keychain-db"\n', {"/a.keychain-db": 0}, value=b'{"nope": 1}'),
    )

    assert missing.status is CredentialStatus.SOURCE_MISSING
    assert ambiguous.status is CredentialStatus.SOURCE_AMBIGUOUS
    assert read_failure.status is CredentialStatus.SOURCE_UNREADABLE
    assert empty.status is CredentialStatus.SOURCE_EMPTY
    assert oversized.status is CredentialStatus.SOURCE_OVERSIZE
    assert invalid.status is CredentialStatus.INVALID_SHAPE


@pytest.mark.parametrize("operation", ["mkdir", "mkstemp", "write", "replace", "chmod"])
def test_destination_operation_failures_are_typed_and_clean_temp(tmp_path, monkeypatch, operation):
    src = tmp_path / "auth.json"
    src.write_bytes(CODEX_OK)
    dest = tmp_path / "dest" / "auth.json"

    def fail(*_args, **_kwargs):
        raise OSError(errno.EIO, operation)

    if operation == "mkdir":
        monkeypatch.setattr(credentials.os, "mkdir", fail)
    elif operation == "mkstemp":
        monkeypatch.setattr(credentials, "_mkstemp_at", fail, raising=False)
    elif operation == "write":
        monkeypatch.setattr(credentials.os, "write", fail)
    elif operation == "replace":
        monkeypatch.setattr(credentials, "_replace_at", fail, raising=False)
    else:
        monkeypatch.setattr(credentials.os, "fchmod", fail)

    result = materialize_file_credential(src, dest, max_bytes=1_000_000, shape_ok=codex_shape_ok)

    assert result.status is CredentialStatus.DEST_UNSAFE
    if dest.parent.exists():
        assert not list(dest.parent.glob(".host2-credential-*"))


def test_descriptor_fds_are_closed_after_materialization(tmp_path, monkeypatch):
    src = tmp_path / "auth.json"
    src.write_bytes(CODEX_OK)
    opened = []
    closed = []
    real_open = os.open
    real_close = os.close

    def tracking_open(path, flags, mode=0o777, *, dir_fd=None):
        fd = real_open(path, flags, mode, dir_fd=dir_fd)
        opened.append(fd)
        return fd

    def tracking_close(fd):
        closed.append(fd)
        return real_close(fd)

    monkeypatch.setattr(credentials.os, "open", tracking_open)
    monkeypatch.setattr(credentials.os, "close", tracking_close)
    result = materialize_file_credential(
        src, tmp_path / "dest" / "auth.json", max_bytes=1_000_000, shape_ok=codex_shape_ok
    )

    assert result.status is CredentialStatus.OK
    assert opened
    assert set(opened) <= set(closed)


def test_secret_never_escapes_result_owners_or_error_text(tmp_path):
    secret = "DO_NOT_EXPOSE_CREDENTIAL_VALUE"
    raw = json.dumps({"tokens": {"access_token": secret}}).encode()
    src = tmp_path / "auth.json"
    src.write_bytes(raw)

    result = materialize_file_credential(src, tmp_path / "dest", max_bytes=1_000_000, shape_ok=codex_shape_ok)
    invalid = materialize_file_credential(src, tmp_path / "invalid", max_bytes=1_000_000, shape_ok=lambda _raw: False)

    assert result.status is CredentialStatus.OK
    assert invalid.status is CredentialStatus.INVALID_SHAPE
    assert secret not in repr(result)
    assert secret not in repr(invalid)
    assert secret not in repr(vars(result))
    assert secret not in repr(vars(invalid))
