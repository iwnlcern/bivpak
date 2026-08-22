import os
import shutil
import subprocess
from pathlib import Path

import pytest

from bivharness.compare import assert_members, assert_repo_state, compare_trees, load_tolerance
from bivharness.fixtures import materialize


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


def test_declared_additive_root_is_the_only_restored_tree_tolerance(tmp_path):
    src, restored = _matching_trees(tmp_path)
    _write(restored / ".biv/agents/manifest.json", b"sealed\n")
    _write(restored / ".biv/agents/claude-code/session.jsonl", b"staged\n")
    _write(restored / ".biv/foreign.txt", b"not allowed\n")

    findings = compare_trees(src, restored, load_tolerance(), [".biv/agents"])

    assert not any(".biv/agents" in item for item in findings)
    assert findings == ["C: extra path: .biv/foreign.txt"]


@pytest.mark.parametrize("root", ["", ".", "../agents", "/tmp/agents", ".biv/../agents"])
def test_additive_root_must_be_a_normalized_relative_path(tmp_path, root):
    src, restored = _matching_trees(tmp_path)

    with pytest.raises(ValueError, match="invalid additive root"):
        compare_trees(src, restored, load_tolerance(), [root])


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


def _git(repo, *args):
    return subprocess.run(
        ["git", "-C", str(repo), *args], check=True, capture_output=True, text=True
    ).stdout.strip()


def _matching_git_trees(tmp_path):
    src = tmp_path / "src"
    restored = tmp_path / "restored"
    materialize(
        {
            "entries": [
                {
                    "type": "git-repo",
                    "path": "repo",
                    "commits": [
                        {"files": {"a.txt": "one\n"}, "message": "first"},
                        {"files": {"a.txt": "two\n"}, "message": "second"},
                    ],
                    "branches": {"keep": 0},
                }
            ]
        },
        src,
    )
    shutil.copytree(src, restored, symlinks=True, copy_function=shutil.copy2)
    return src, restored


def test_compare_trees_composes_additive_roots_with_repo_semantics(tmp_path):
    src, restored = _matching_git_trees(tmp_path)
    _write(restored / ".biv/agents/session.json", b"staged\n")
    subprocess.run(
        ["git", "-C", str(restored / "repo"), "branch", "-D", "keep"],
        check=True,
        capture_output=True,
        text=True,
    )

    findings = compare_trees(src, restored, load_tolerance(), [".biv/agents"])

    assert not any(".biv/agents" in finding for finding in findings)
    assert any("missing ref: refs/heads/keep" in finding for finding in findings)


def test_ref_restored_to_a_divergent_sha_reports_a_ref_mismatch(tmp_path):
    src, restored = _matching_git_trees(tmp_path)
    repo = restored / "repo"
    head = _git(repo, "rev-parse", "HEAD")
    keep = _git(repo, "rev-parse", "refs/heads/keep")
    assert head != keep
    _git(repo, "update-ref", "refs/heads/keep", head)

    findings = compare_trees(src, restored, load_tolerance())

    assert any(
        f"ref mismatch for refs/heads/keep: {keep} != {head}" in item
        for item in findings
    )


def test_extra_restored_ref_reports_a_repo_finding(tmp_path):
    src, restored = _matching_git_trees(tmp_path)
    repo = restored / "repo"
    _git(repo, "update-ref", "refs/heads/unexpected", _git(repo, "rev-parse", "HEAD"))

    findings = compare_trees(src, restored, load_tolerance())

    assert any("extra ref: refs/heads/unexpected" in item for item in findings)


def test_git_admin_bytes_are_excluded_from_byte_findings(tmp_path):
    src, restored = _matching_git_trees(tmp_path)
    (restored / "repo/.git/untracked-admin-byte").write_bytes(b"different")

    assert compare_trees(src, restored, load_tolerance()) == []


def test_git_admin_exclusion_is_controlled_by_declared_tolerance(tmp_path):
    src, restored = _matching_git_trees(tmp_path)
    (restored / "repo/.git/untracked-admin-byte").write_bytes(b"different")
    tol = load_tolerance()
    tol["rows"] = [row for row in tol["rows"] if row["name"] != "git-administration"]

    assert any(
        "extra path: repo/.git/untracked-admin-byte" in item
        for item in compare_trees(src, restored, tol)
    )


def test_git_worktree_mtime_drift_is_semantically_ignored(tmp_path):
    src, restored = _matching_git_trees(tmp_path)
    os.utime(restored / "repo/a.txt", ns=(1_700_000_000_000_000_000,) * 2)

    assert compare_trees(src, restored, load_tolerance()) == []


def test_git_worktree_mtime_exemption_is_controlled_by_declared_tolerance(tmp_path):
    src, restored = _matching_git_trees(tmp_path)
    os.utime(restored / "repo/a.txt", ns=(1_700_000_000_000_000_000,) * 2)
    tol = load_tolerance()
    tol["rows"] = [
        row for row in tol["rows"] if row["name"] != "git-tracked-file-mtime"
    ]

    assert any(
        "file-mtime mismatch for repo/a.txt" in item
        for item in compare_trees(src, restored, tol)
    )


def test_ignored_repo_payload_mtime_remains_exact(tmp_path):
    src = tmp_path / "src"
    restored = tmp_path / "restored"
    materialize(
        {
            "entries": [
                {
                    "type": "git-repo",
                    "path": "repo",
                    "commits": [
                        {
                            "files": {".gitignore": "*.cache\n", "a.txt": "tracked\n"},
                            "message": "tracked",
                        }
                    ],
                },
                {"type": "file", "path": "repo/state.cache", "text": "payload\n"},
            ]
        },
        src,
    )
    shutil.copytree(src, restored, symlinks=True, copy_function=shutil.copy2)
    os.utime(restored / "repo/state.cache", ns=(1_700_000_000_000_000_000,) * 2)

    findings = compare_trees(src, restored, load_tolerance())
    assert any("file-mtime mismatch for repo/state.cache" in item for item in findings)


def test_noncarried_git_refs_are_semantically_ignored(tmp_path):
    src, restored = _matching_git_trees(tmp_path)
    subprocess.run(
        [
            "git",
            "-C",
            str(src / "repo"),
            "update-ref",
            "refs/notes/commits",
            "HEAD",
        ],
        check=True,
        capture_output=True,
        text=True,
    )

    assert compare_trees(src, restored, load_tolerance()) == []


def test_repo_semantic_oracle_flags_head_mismatch_and_missing_ref(tmp_path):
    src, restored = _matching_git_trees(tmp_path)
    subprocess.run(
        ["git", "-C", str(restored / "repo"), "checkout", "--detach", "HEAD^"],
        check=True,
        capture_output=True,
        text=True,
    )
    subprocess.run(
        ["git", "-C", str(restored / "repo"), "branch", "-D", "keep"],
        check=True,
        capture_output=True,
        text=True,
    )

    findings = compare_trees(src, restored, load_tolerance())
    assert any("HEAD mismatch" in item for item in findings)
    assert any("branch mismatch" in item for item in findings)
    assert any("missing ref: refs/heads/keep" in item for item in findings)


def test_repo_semantic_oracle_ignores_ambient_git_directory(monkeypatch, tmp_path):
    src, restored = _matching_git_trees(tmp_path)
    subprocess.run(
        ["git", "-C", str(restored / "repo"), "branch", "-D", "keep"],
        check=True,
        capture_output=True,
        text=True,
    )
    monkeypatch.setenv("GIT_DIR", str(src / "repo/.git"))
    monkeypatch.setenv("GIT_WORK_TREE", str(src / "repo"))

    findings = compare_trees(src, restored, load_tolerance())
    assert any("missing ref: refs/heads/keep" in item for item in findings)


def test_repo_state_expectation_checks_head_branch_cleanliness_and_refs(tmp_path):
    src, _ = _matching_git_trees(tmp_path)
    repo = src / "repo"
    head = subprocess.run(
        ["git", "-C", str(repo), "rev-parse", "HEAD"],
        check=True,
        capture_output=True,
        text=True,
    ).stdout.strip()
    keep = subprocess.run(
        ["git", "-C", str(repo), "rev-parse", "refs/heads/keep"],
        check=True,
        capture_output=True,
        text=True,
    ).stdout.strip()

    assert assert_repo_state(
        src,
        {
            "repo": {
                "head_sha": head,
                "branch": "main",
                "porcelain_clean": True,
                "refs": {"refs/heads/keep": keep, "refs/heads/main": head},
            }
        },
    ) == []
    findings = assert_repo_state(
        src,
        {"repo": {"head_sha": "0" * 40, "refs": {"refs/heads/missing": head}}},
    )
    assert any("HEAD mismatch" in item for item in findings)
    assert any("missing ref: refs/heads/missing" in item for item in findings)


def test_repo_state_expectation_reports_a_divergent_ref_sha(tmp_path):
    src, _ = _matching_git_trees(tmp_path)
    repo = src / "repo"
    head = _git(repo, "rev-parse", "HEAD")
    keep = _git(repo, "rev-parse", "refs/heads/keep")
    assert head != keep

    findings = assert_repo_state(
        src,
        {
            "repo": {
                "head_sha": head,
                "branch": "main",
                "porcelain_clean": True,
                "refs": {"refs/heads/keep": head, "refs/heads/main": head},
            }
        },
    )

    assert any(
        f"ref mismatch for refs/heads/keep: {keep} != {head}" in item
        for item in findings
    )


def test_repo_state_expectation_accepts_unborn_head(tmp_path):
    root = tmp_path / "root"
    materialize(
        {"entries": [{"type": "git-repo", "path": "unborn", "commits": []}]},
        root,
    )

    assert assert_repo_state(
        root,
        {
            "unborn": {
                "head_unborn": True,
                "branch": "main",
                "porcelain_clean": True,
                "refs": {},
            }
        },
    ) == []


def test_repo_semantic_oracle_consumes_index_and_remote_policies(tmp_path):
    src, restored = _matching_git_trees(tmp_path)
    (restored / "repo/untracked.txt").write_text("dirty\n", encoding="utf-8")
    subprocess.run(
        ["git", "-C", str(src / "repo"), "remote", "add", "origin", "https://example.invalid/repo.git"],
        check=True,
        capture_output=True,
        text=True,
    )

    findings = compare_trees(src, restored, load_tolerance())
    assert any("porcelain-v2 is not clean" in item for item in findings)
    assert any("remote config mismatch" in item for item in findings)


def test_unknown_git_tolerance_policy_is_invalid(tmp_path):
    src, restored = _matching_git_trees(tmp_path)
    tol = load_tolerance()
    next(row for row in tol["rows"] if row["name"] == "git-object-id")["policy"] = "surprise"

    with pytest.raises(ValueError, match="unknown tolerance policy"):
        compare_trees(src, restored, tol)
