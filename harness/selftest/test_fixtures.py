import base64
import os

import pytest

from bivharness.fixtures import SpecError, materialize


def test_materializes_file_bytes_mode_empty_dir_and_relative_symlink(tmp_path):
    materialize(
        {
            "entries": [
                {
                    "type": "file",
                    "path": "bin/tool",
                    "bytes_b64": base64.b64encode(b"\x00abc").decode("ascii"),
                    "mode": "0751",
                },
                {"type": "dir", "path": "empty"},
                {"type": "symlink", "path": "link", "target": "bin/tool"},
            ]
        },
        tmp_path,
    )

    assert (tmp_path / "bin/tool").read_bytes() == b"\x00abc"
    assert (tmp_path / "bin/tool").stat().st_mode & 0o777 == 0o751
    assert (tmp_path / "empty").is_dir()
    assert os.readlink(tmp_path / "link") == "bin/tool"


def test_crlf_bytes_survive_verbatim(tmp_path):
    materialize(
        {"entries": [{"type": "file", "path": "crlf.txt", "text": "a\r\nb\r\n"}]},
        tmp_path,
    )

    assert (tmp_path / "crlf.txt").read_bytes() == b"a\r\nb\r\n"


def test_hardlink_type_is_rejected(tmp_path):
    with pytest.raises(SpecError, match="unsupported fixture entry type"):
        materialize(
            {"entries": [{"type": "hardlink", "path": "x", "target": "y"}]},
            tmp_path,
        )


def test_paths_escaping_root_are_rejected(tmp_path):
    with pytest.raises(SpecError, match="escapes fixture root"):
        materialize(
            {"entries": [{"type": "file", "path": "../x", "text": "bad"}]},
            tmp_path,
        )
