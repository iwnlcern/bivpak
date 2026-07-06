#!/usr/bin/env python3
import hashlib
import io
import json
import os
import shutil
import sys
import tarfile
import uuid
from pathlib import Path

import zstandard

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from bivharness.artifact import payload_extent_digests_from_bytes  # noqa: E402


BUILTIN_BIVIGNORE_SHA256 = "e271561320eecb76b6736a4b85bfc98069e1259b8fc9609ebea926e8aa5bb1d3"


def _mode():
    return os.environ.get("STUB_BIV_MODE", "ok")


def _emit(verb, exit_code, result=None, error=None, advisories=None):
    payload = json.dumps(
        {
            "envelope_version": 1,
            "app_version": "0.1.0",
            "ok": exit_code in (0, 2),
            "verb": verb,
            "exit_code": exit_code,
            "warnings": [],
            "advisories": advisories or [],
            "result": result,
            "error": error,
        }
    )
    if _mode() == "malformed-stdout":
        print("{not-json")
        return exit_code
    if _mode() == "noisy-stdout":
        print(payload)
        print("extra stdout")
        return exit_code
    print(payload)
    return exit_code


def _manifest(source: Path):
    has_file_ignore = (source / ".bivignore").exists()
    if has_file_ignore:
        ignore_sha = hashlib.sha256((source / ".bivignore").read_bytes()).hexdigest()
    else:
        ignore_sha = BUILTIN_BIVIGNORE_SHA256
    if _mode() == "bad-manifest":
        ignore_sha = "0" * 64
    return {
        "format_version": 1,
        "required_capabilities": [],
        "image_id": str(uuid.UUID("00000000-0000-4000-8000-000000000000")),
        "app_version": "0.1.0",
        "created_at": "2026-07-05T00:00:00Z",
        "source_path": source.as_posix(),
        "source_path_flavor": "posix",
        "bivignore": {
            "source": "file" if has_file_ignore else "builtin",
            "builtin_id": None if has_file_ignore else "builtin-v1",
            "sha256": ignore_sha,
        },
        "repos": [],
        "agent_sessions": [],
    }


def _ignore_rules(source: Path):
    ignore_file = source / ".bivignore"
    if not ignore_file.exists():
        return [("node_modules", "builtin-v1")]
    rules = []
    for line_number, line in enumerate(ignore_file.read_text(encoding="utf-8").splitlines(), start=1):
        rule = line.strip()
        if not rule or rule.startswith("#"):
            continue
        rules.append((rule.rstrip("/"), f".bivignore:{line_number}"))
    return rules


def _ignored(source: Path):
    return {rule for rule, _source in _ignore_rules(source)}


def _prune_entries(source: Path):
    entries = []
    for rule, source_text in _ignore_rules(source):
        if (source / rule).exists():
            entries.append({"path": rule, "source": source_text})
    return entries


def _is_ignored(rel: str, ignored: set[str]):
    return any(rel == rule or rel.startswith(rule + "/") for rule in ignored)


def _pax_mtime(ns: int):
    sec, nsec = divmod(ns, 1_000_000_000)
    return f"{sec}.{nsec:09d}"


def _member_mtime_ns(member: tarfile.TarInfo):
    raw = member.pax_headers.get("mtime")
    if raw and "." in raw:
        sec, frac = raw.split(".", 1)
        return int(sec) * 1_000_000_000 + int(frac[:9].ljust(9, "0"))
    return int(member.mtime * 1_000_000_000)


def _add_payload(tf: tarfile.TarFile, source: Path):
    ignored = set() if _mode() == "leak-member" else _ignored(source)
    for path in sorted(source.rglob("*"), key=lambda p: p.relative_to(source).as_posix()):
        rel = path.relative_to(source).as_posix()
        if _is_ignored(rel, ignored):
            continue
        arc = "payload/" + rel
        info = tf.gettarinfo(path, arcname=arc)
        info.pax_headers["mtime"] = _pax_mtime(path.lstat().st_mtime_ns)
        if path.is_file() and not path.is_symlink():
            with path.open("rb") as fh:
                tf.addfile(info, fh)
        else:
            tf.addfile(info)


def pack(args):
    source = Path(args[0]).resolve()
    if _mode() == "pack-fail":
        return _emit(
            "pack",
            4,
            result=None,
            error={"kind": "InternalError", "path": "", "detail": "pack-fail", "errno": 0, "facts": {}},
        )
    image = source.parent / f"{source.name}.bvpk"
    manifest = json.dumps(_manifest(source), sort_keys=True).encode("utf-8")

    placeholder = io.BytesIO()
    with tarfile.open(fileobj=placeholder, mode="w", format=tarfile.PAX_FORMAT) as tf:
        for name, data in (("manifest.json", manifest), ("checksums.json", b'{"algo":"sha256","entries":{}}')):
            info = tarfile.TarInfo(name)
            info.size = len(data)
            tf.addfile(info, io.BytesIO(data))
        _add_payload(tf, source)
    checksum_entries = payload_extent_digests_from_bytes(placeholder.getvalue())
    if _mode() == "bad-checksums" and checksum_entries:
        first = sorted(checksum_entries)[0]
        checksum_entries[first] = "0" * 64
    checksums = json.dumps(
        {"algo": "sha256", "entries": checksum_entries},
        indent=2,
        sort_keys=True,
    ).encode("utf-8") + b"\n"

    tar_buf = io.BytesIO()
    with tarfile.open(fileobj=tar_buf, mode="w", format=tarfile.PAX_FORMAT) as tf:
        for name, data in (("manifest.json", manifest), ("checksums.json", checksums)):
            info = tarfile.TarInfo(name)
            info.size = len(data)
            tf.addfile(info, io.BytesIO(data))
        _add_payload(tf, source)
    image.write_bytes(zstandard.ZstdCompressor().compress(tar_buf.getvalue()))
    pruned = _prune_entries(source)
    advisories = [{"kind": "prune-summary", "entries": pruned}] if pruned else []
    return _emit(
        "pack",
        0,
        result={
            "image_path": image.as_posix(),
            "source_path": source.as_posix(),
            "image_id": hashlib.sha256(manifest).hexdigest(),
            "member_count": 0,
            "payload_bytes": 0,
            "manifest": json.loads(manifest),
        },
        advisories=advisories,
    )


def open_image(args):
    image = Path(args[0]).resolve()
    if "--dest" in args:
        if _mode() == "reject-dest":
            return _emit(
                "open",
                5,
                result=None,
                error={"kind": "UsageError", "path": "", "detail": "--dest rejected", "errno": 0, "facts": {}},
            )
        dest = Path(args[args.index("--dest") + 1]).resolve()
    else:
        dest = (Path.cwd() / image.with_suffix("").name).resolve()
    if _mode() == "refuse":
        return _emit(
            "open",
            3,
            result=None,
            error={"kind": "FormatVersionUnsupported", "path": "", "detail": "", "errno": 0, "facts": {}},
        )
    raw = zstandard.ZstdDecompressor().decompress(image.read_bytes())
    with tarfile.open(fileobj=io.BytesIO(raw), mode="r:") as tf:
        manifest_member = tf.extractfile("manifest.json")
        manifest = json.loads(manifest_member.read() if manifest_member else b"{}")
        if manifest.get("format_version") != 1:
            return _emit(
                "open",
                3,
                result=None,
                error={"kind": "FormatVersionUnsupported", "path": "", "detail": "", "errno": 0, "facts": {}},
            )
    dest.mkdir(parents=True, exist_ok=True)
    dir_mtimes = []
    with tarfile.open(fileobj=io.BytesIO(raw), mode="r:") as tf:
        for member in tf.getmembers():
            if not member.name.startswith("payload/"):
                continue
            rel = member.name.removeprefix("payload/")
            target = dest / rel
            if member.isdir():
                target.mkdir(parents=True, exist_ok=True)
                os.chmod(target, member.mode)
                dir_mtimes.append((target, _member_mtime_ns(member)))
            elif member.issym():
                target.parent.mkdir(parents=True, exist_ok=True)
                os.symlink(member.linkname, target)
            elif member.isfile():
                target.parent.mkdir(parents=True, exist_ok=True)
                extracted = tf.extractfile(member)
                target.write_bytes(extracted.read() if extracted else b"")
                os.chmod(target, member.mode)
                ns = _member_mtime_ns(member)
                os.utime(target, ns=(ns, ns))
    for target, ns in sorted(dir_mtimes, key=lambda item: len(item[0].parts), reverse=True):
        os.utime(target, ns=(ns, ns))
    if _mode() == "badtree":
        (dest / "stray.txt").write_text("stray", encoding="utf-8")
    return _emit("open", 0, result={"output_dir": dest.as_posix()})


def main():
    args = [arg for arg in sys.argv[1:] if arg != "--json"]
    if not args:
        return 5
    if args[0] == "pack":
        return pack(args[1:])
    if args[0] == "open":
        return open_image(args[1:])
    return _emit(
        args[0],
        5,
        error={"kind": "UsageError", "path": "", "detail": "", "errno": 0, "facts": {}},
    )


if __name__ == "__main__":
    raise SystemExit(main())
