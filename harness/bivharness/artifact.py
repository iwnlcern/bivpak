from contextlib import contextmanager, closing
import hashlib
import io
import tarfile
from pathlib import Path

import zstandard


BLOCK_SIZE = 512


@contextmanager
def _tar_stream(img: Path):
    with img.open("rb") as compressed:
        with closing(zstandard.ZstdDecompressor().stream_reader(compressed)) as reader:
            with tarfile.open(fileobj=reader, mode="r|") as tf:
                yield tf


def list_members(img: Path) -> list[str]:
    members: list[str] = []
    with _tar_stream(img) as tf:
        for member in tf:
            members.append(member.name)
    return members


def extract_member(img: Path, name: str) -> bytes:
    with _tar_stream(img) as tf:
        for member in tf:
            if member.name != name:
                continue
            extracted = tf.extractfile(member)
            if extracted is None:
                return b""
            return extracted.read()
    raise KeyError(name)


def _decompress(img: Path) -> bytes:
    with img.open("rb") as fh:
        with closing(zstandard.ZstdDecompressor().stream_reader(fh)) as reader:
            chunks = []
            while True:
                chunk = reader.read(1024 * 1024)
                if not chunk:
                    break
                chunks.append(chunk)
            return b"".join(chunks)


def mutate_in_stream(img: Path, out: Path, old: bytes, new: bytes) -> None:
    if len(old) != len(new):
        raise ValueError("old and new substitutions must have the same length")
    raw = _decompress(img)
    if raw.count(old) != 1:
        raise ValueError("old byte sequence must occur exactly once")
    mutated = raw.replace(old, new, 1)
    out.write_bytes(zstandard.ZstdCompressor().compress(mutated))


def _padded(size: int) -> int:
    remainder = size % BLOCK_SIZE
    return size if remainder == 0 else size + BLOCK_SIZE - remainder


def _octal(block: bytes, start: int, size: int) -> int:
    raw = block[start:start + size].split(b"\0", 1)[0].strip()
    return int(raw or b"0", 8)


def _header_name(block: bytes) -> str:
    name = block[0:100].split(b"\0", 1)[0].decode("utf-8")
    prefix = block[345:500].split(b"\0", 1)[0].decode("utf-8")
    return f"{prefix}/{name}" if prefix else name


def _pax_records(data: bytes) -> dict[str, str]:
    records: dict[str, str] = {}
    offset = 0
    while offset < len(data):
        space = data.find(b" ", offset)
        if space == -1:
            break
        length = int(data[offset:space])
        record = data[space + 1:offset + length]
        if record.endswith(b"\n"):
            record = record[:-1]
        if b"=" in record:
            key, value = record.split(b"=", 1)
            records[key.decode("utf-8")] = value.decode("utf-8")
        offset += length
    return records


def payload_extent_digests_from_bytes(raw: bytes) -> dict[str, str]:
    digests: dict[str, str] = {}
    offset = 0
    while offset + BLOCK_SIZE <= len(raw):
        first = raw[offset:offset + BLOCK_SIZE]
        offset += BLOCK_SIZE
        if first == b"\0" * BLOCK_SIZE:
            break

        extent = bytearray(first)
        block = first
        typeflag = block[156:157]
        pax: dict[str, str] = {}

        if typeflag == b"x":
            pax_size = _octal(block, 124, 12)
            pax_total = _padded(pax_size)
            pax_bytes = raw[offset:offset + pax_size]
            extent.extend(raw[offset:offset + pax_total])
            offset += pax_total
            pax = _pax_records(pax_bytes)

            block = raw[offset:offset + BLOCK_SIZE]
            offset += BLOCK_SIZE
            if block == b"\0" * BLOCK_SIZE:
                break
            extent.extend(block)
            typeflag = block[156:157]

        name = pax.get("path", _header_name(block))
        size = _octal(block, 124, 12) if typeflag in (b"0", b"\0") else 0
        total = _padded(size)
        extent.extend(raw[offset:offset + total])
        offset += total

        if name.startswith("payload/"):
            digests[name] = hashlib.sha256(bytes(extent)).hexdigest()
    return digests


def payload_extent_digests(img: Path) -> dict[str, str]:
    return payload_extent_digests_from_bytes(_decompress(img))
