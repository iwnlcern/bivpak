import os
from pathlib import Path

import pytest

from bivharness.compare import assert_members, compare_trees, load_tolerance


def _write(path: Path, data: bytes):
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_bytes(data)


def _stamp(path: Path, ns: int):
    os.utime(path, ns=(ns, ns), follow_symlinks=False)


def _tree(root: Path):
    _write(root / "tools/run.sh", b"echo hi\n")
    os.chmod(root / "tools/run.sh", 0o751)
    (root / "empty").mkdir(parents=True)
    os.symlink("tools/run.sh", root / "link")
    _stamp(root / "tools", 1_700_000_000_000_000_100)
    _stamp(root / "tools/run.sh", 1_700_000_000_000_000_200)
    _stamp(root / "empty", 1_700_000_000_000_000_300)


def _matching_trees(tmp_path):
    src = tmp_path / "src"
    restored = tmp_path / "restored"
    _tree(src)
    _tree(restored)
    return src, restored


def test_identical_trees_with_modes_symlink_empty_dir_and_ns_mtimes_pass(tmp_path):
    src, restored = _matching_trees(tmp_path)

    assert compare_trees(src, restored, load_tolerance()) == []


def test_flipped_byte_reports_class_a_finding(tmp_path):
    src, restored = _matching_trees(tmp_path)
    (restored / "tools/run.sh").write_bytes(b"echo bye\n")

    assert any(item.startswith("A:") for item in compare_trees(src, restored, load_tolerance()))


def test_mode_difference_reports_class_b_finding(tmp_path):
    src, restored = _matching_trees(tmp_path)
    os.chmod(restored / "tools/run.sh", 0o644)

    assert any("mode" in item for item in compare_trees(src, restored, load_tolerance()))


def test_extra_and_missing_paths_report_class_c_findings(tmp_path):
    src, restored = _matching_trees(tmp_path)
    _write(restored / "extra.txt", b"x")
    os.unlink(restored / "tools/run.sh")

    findings = compare_trees(src, restored, load_tolerance())
    assert any("extra" in item for item in findings)
    assert any("missing" in item for item in findings)


def test_dir_mtime_skew_reports_class_b_finding(tmp_path):
    src, restored = _matching_trees(tmp_path)
    _stamp(restored / "empty", 1_700_000_000_000_000_301)

    assert any("dir-mtime" in item for item in compare_trees(src, restored, load_tolerance()))


def test_file_mtime_skew_reports_class_b_finding(tmp_path):
    src, restored = _matching_trees(tmp_path)
    _stamp(restored / "tools/run.sh", 1_700_000_000_000_000_201)

    assert any("file-mtime" in item for item in compare_trees(src, restored, load_tolerance()))


def test_unknown_tolerance_policy_is_invalid(tmp_path):
    src, restored = _matching_trees(tmp_path)
    tol = load_tolerance()
    tol["rows"][0]["policy"] = "surprise"

    with pytest.raises(ValueError, match="unknown tolerance policy"):
        compare_trees(src, restored, tol)


def test_ownership_is_ignored_by_tolerance(tmp_path):
    src, restored = _matching_trees(tmp_path)

    assert not any("ownership" in item for item in compare_trees(src, restored, load_tolerance()))


def test_member_absence_assertion_flags_forbidden_member():
    assert assert_members(["manifest.json", "payload/a.txt"], ["manifest.json"], ["payload/secret.log"]) == []
    assert assert_members(["payload/secret.log"], [], ["payload/secret.log"]) == [
        "member present but expected absent: payload/secret.log"
    ]
