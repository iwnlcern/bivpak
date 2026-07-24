import json
import os
import stat
from collections.abc import Iterable, Mapping
from contextlib import ExitStack
from pathlib import Path, PurePath
from typing import Any, Callable


_READ_SIZE = 65536
_DIRECTORY_FLAGS = os.O_RDONLY | os.O_DIRECTORY | os.O_NOFOLLOW


def read_bounded_roots(
    roots: Iterable[Path],
    *,
    per_file_bytes: int = 65536,
    total_bytes: int = 1 << 20,
) -> tuple[str, list[str]]:
    content = []
    notes = []
    remaining = max(0, total_bytes)

    for supplied_root in roots:
        root = Path(supplied_root)
        try:
            root_stat = os.lstat(root)
        except OSError:
            notes.append("traversal-error")
            continue
        if stat.S_ISLNK(root_stat.st_mode):
            notes.append("skip-symlink-root")
            continue

        try:
            root_fd = os.open(root, _DIRECTORY_FLAGS)
        except OSError:
            notes.append("traversal-error")
            continue

        def traversal_error(_error):
            notes.append("traversal-error")

        try:
            try:
                opened_root_stat = os.fstat(root_fd)
            except OSError:
                notes.append("traversal-error")
                continue
            validated_identity = (root_stat.st_dev, root_stat.st_ino)
            opened_identity = (opened_root_stat.st_dev, opened_root_stat.st_ino)
            if opened_identity != validated_identity:
                notes.append("traversal-error")
                continue

            for _dirpath, dirnames, filenames, dirfd in os.fwalk(
                ".",
                topdown=True,
                onerror=traversal_error,
                follow_symlinks=False,
                dir_fd=root_fd,
            ):
                dirnames.sort()
                filenames.sort()
                for name in filenames:
                    if remaining == 0:
                        notes.append("budget-exhausted")
                        return "".join(content), notes

                    flags = os.O_RDONLY | os.O_NOFOLLOW
                    if hasattr(os, "O_NONBLOCK"):
                        flags |= os.O_NONBLOCK
                    try:
                        fd = os.open(name, flags, dir_fd=dirfd)
                    except OSError:
                        notes.append("skip-open-error")
                        continue

                    try:
                        try:
                            file_stat = os.fstat(fd)
                        except OSError:
                            notes.append("skip-open-error")
                            continue
                        if not stat.S_ISREG(file_stat.st_mode):
                            notes.append("skip-nonregular")
                            continue

                        chunks = []
                        file_remaining = min(max(0, per_file_bytes), remaining)
                        while file_remaining:
                            try:
                                chunk = os.read(
                                    fd,
                                    min(_READ_SIZE, file_remaining),
                                )
                            except OSError:
                                notes.append("skip-read-error")
                                chunks.clear()
                                break
                            if not chunk:
                                break
                            chunks.append(chunk)
                            size = len(chunk)
                            file_remaining -= size
                            remaining -= size
                        content.append(b"".join(chunks).decode("utf-8", "replace"))
                        if remaining == 0:
                            notes.append("budget-exhausted")
                            return "".join(content), notes
                    finally:
                        os.close(fd)
        finally:
            os.close(root_fd)

    return "".join(content), notes


def _validated_parts(name: str) -> tuple[str, ...]:
    path = PurePath(name)
    if path.is_absolute() or not path.parts or ".." in path.parts:
        raise ValueError(f"unsafe corpus name: {name!r}")
    return path.parts


def _write_all(fd: int, data: bytes) -> None:
    pending = memoryview(data)
    while pending:
        written = os.write(fd, pending)
        if written <= 0:
            raise OSError("short corpus write")
        pending = pending[written:]


def build_durable_corpus(
    root: Path,
    contents: Mapping[str, str | bytes],
) -> Path:
    root = Path(root)
    entries = [
        (_validated_parts(name), value)
        for name, value in sorted(contents.items())
    ]

    try:
        root_stat = os.lstat(root)
    except FileNotFoundError:
        root.mkdir(parents=True)
        root_stat = os.lstat(root)
    if stat.S_ISLNK(root_stat.st_mode):
        raise ValueError("corpus root must not be a symlink")

    with ExitStack() as root_descriptors:
        root_fd = os.open(root, _DIRECTORY_FLAGS)
        root_descriptors.callback(os.close, root_fd)
        for parts, value in entries:
            with ExitStack() as entry_descriptors:
                parent_fd = os.dup(root_fd)
                entry_descriptors.callback(os.close, parent_fd)
                for component in parts[:-1]:
                    try:
                        os.mkdir(component, dir_fd=parent_fd)
                    except FileExistsError:
                        pass
                    next_fd = os.open(
                        component,
                        _DIRECTORY_FLAGS,
                        dir_fd=parent_fd,
                    )
                    parent_fd = next_fd
                    entry_descriptors.callback(os.close, parent_fd)

                data = value.encode("utf-8") if isinstance(value, str) else bytes(value)
                file_fd = os.open(
                    parts[-1],
                    os.O_WRONLY | os.O_CREAT | os.O_EXCL | os.O_NOFOLLOW,
                    0o600,
                    dir_fd=parent_fd,
                )
                entry_descriptors.callback(os.close, file_fd)
                _write_all(file_fd, data)
                os.fsync(file_fd)

    return root


def adversarial_seed_fake(
    *,
    extra_roots: Iterable[Path] | None = None,
    per_file_bytes: int = 65536,
    total_bytes: int = 1 << 20,
):
    captured_extra_roots = tuple(Path(root) for root in (extra_roots or ()))

    def seed_agent(
        agent: dict[str, Any],
        live_profile: Path,
        seed_workspace: Path,
        spec: dict[str, Any],
        env: dict[str, str],
        spawn: Callable[[list[str], Path, dict[str, str]], Any],
        capture_candidates: list[Path],
        owned_paths: list[Path],
        resolved_binary: str | None = None,
    ) -> Path:
        del live_profile, spec, env, spawn, capture_candidates, resolved_binary
        content, notes = read_bounded_roots(
            [seed_workspace, *captured_extra_roots],
            per_file_bytes=per_file_bytes,
            total_bytes=total_bytes,
        )
        transcript = seed_workspace / f"seen-{agent['id']}.jsonl"
        transcript.write_text(
            json.dumps(
                {"content": content, "notes": notes},
                sort_keys=True,
                separators=(",", ":"),
            ),
            encoding="utf-8",
        )
        owned_paths.append(transcript)
        return transcript

    return seed_agent
