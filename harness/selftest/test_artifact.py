import io
import tarfile

import pytest
import zstandard

from bivharness.artifact import extract_member, list_members, mutate_in_stream


def _tar_zstd(path, manifest=b'{"format_version": 1}', payload=b"hello"):
    tar_buf = io.BytesIO()
    with tarfile.open(fileobj=tar_buf, mode="w", format=tarfile.PAX_FORMAT) as tf:
        for name, data in (
            ("manifest.json", manifest),
            ("checksums.json", b"{}"),
            ("payload/a.txt", payload),
        ):
            info = tarfile.TarInfo(name)
            info.size = len(data)
            tf.addfile(info, io.BytesIO(data))
    path.write_bytes(zstandard.ZstdCompressor().compress(tar_buf.getvalue()))


def _decompressed(path):
    return zstandard.ZstdDecompressor().decompress(path.read_bytes())


def test_lists_members_in_streaming_order(tmp_path):
    img = tmp_path / "x.bvpk"
    _tar_zstd(img)

    assert list_members(img)[:2] == ["manifest.json", "checksums.json"]
    assert list_members(img)[2] == "payload/a.txt"


def test_extract_member_returns_exact_bytes(tmp_path):
    img = tmp_path / "x.bvpk"
    _tar_zstd(img, payload=b"\x00a\r\n")

    assert extract_member(img, "payload/a.txt") == b"\x00a\r\n"


def test_mutate_in_stream_replaces_same_length_once(tmp_path):
    img = tmp_path / "x.bvpk"
    out = tmp_path / "mutated.bvpk"
    old = b'"format_version": 1'
    new = b'"format_version": 9'
    _tar_zstd(img, manifest=b'{"format_version": 1}')

    before = _decompressed(img)
    mutate_in_stream(img, out, old, new)
    after = _decompressed(out)

    assert old in before
    assert new in after
    assert after.replace(new, old, 1) == before


def test_mutate_in_stream_rejects_length_mismatch(tmp_path):
    img = tmp_path / "x.bvpk"
    _tar_zstd(img)

    with pytest.raises(ValueError, match="same length"):
        mutate_in_stream(img, tmp_path / "out.bvpk", b"abc", b"abcd")
