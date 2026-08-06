import base64
import os
import subprocess

import pytest

from bivharness.fixtures import SpecError, materialize


def _git(repo, *args):
    return subprocess.run(
        ["git", "-C", str(repo), *args],
        check=True,
        text=True,
        capture_output=True,
    ).stdout.strip()


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


def test_git_repo_builder_is_deterministic_and_host_config_isolated(monkeypatch, tmp_path):
    hostile_home = tmp_path / "hostile-home"
    hostile_home.mkdir()
    (hostile_home / ".gitconfig").write_text(
        "[user]\n\tname = Hostile User\n\temail = hostile@example.test\n"
        "[commit]\n\tgpgsign = true\n",
        encoding="utf-8",
    )
    monkeypatch.setenv("HOME", str(hostile_home))
    monkeypatch.setenv("GIT_CONFIG_GLOBAL", str(hostile_home / ".gitconfig"))

    fixture = {
        "entries": [
            {"type": "git-bare", "id": "origin"},
            {
                "type": "git-repo",
                "path": "project",
                "commits": [
                    {"files": {"README.md": "one\n"}, "message": "first"},
                    {"files": {"README.md": "two\n", "src/a.txt": "a\n"}, "message": "second"},
                ],
                "branches": {"feature": 0},
                "tags": {"v1": 0},
                "remote": "origin",
                "push": ["main", "feature", "refs/tags/v1"],
            },
        ]
    }
    first = tmp_path / "first" / "source"
    second = tmp_path / "second" / "source"

    materialize(fixture, first)
    materialize(fixture, second)

    first_repo = first / "project"
    second_repo = second / "project"
    assert _git(first_repo, "rev-parse", "HEAD") == _git(second_repo, "rev-parse", "HEAD")
    assert _git(first_repo, "status", "--porcelain=v2") == ""
    assert _git(first_repo, "show", "-s", "--format=%an|%ae|%aI|%cn|%ce|%cI", "HEAD") == (
        "Biv Harness|biv-harness@example.invalid|2000-01-01T00:00:00Z|"
        "Biv Harness|biv-harness@example.invalid|2000-01-01T00:00:00Z"
    )
    assert "Hostile User" not in _git(first_repo, "log", "--format=%an", "-2")
    advertised = _git(first_repo, "ls-remote", "origin")
    assert "refs/heads/main" in advertised
    assert "refs/heads/feature" in advertised
    assert "refs/tags/v1" in advertised


def test_git_repo_builder_ignores_ambient_config_parameters(monkeypatch, tmp_path):
    hooks = tmp_path / "host-hooks"
    hooks.mkdir()
    marker = tmp_path / "host-hook-ran"
    pre_commit = hooks / "pre-commit"
    pre_commit.write_text(f"#!/bin/sh\ntouch {marker}\nexit 23\n", encoding="utf-8")
    pre_commit.chmod(0o755)
    monkeypatch.setenv("GIT_CONFIG_PARAMETERS", f"'core.hooksPath={hooks}'")

    materialize(
        {
            "entries": [
                {
                    "type": "git-repo",
                    "path": "project",
                    "commits": [{"files": {"a.txt": "safe\n"}, "message": "safe"}],
                }
            ]
        },
        tmp_path / "source",
    )

    assert not marker.exists()


def test_git_repo_builder_ignores_ambient_template_dir(monkeypatch, tmp_path):
    template = tmp_path / "host-template"
    hooks = template / "hooks"
    hooks.mkdir(parents=True)
    marker = tmp_path / "template-hook-ran"
    pre_commit = hooks / "pre-commit"
    pre_commit.write_text(f"#!/bin/sh\ntouch {marker}\nexit 23\n", encoding="utf-8")
    pre_commit.chmod(0o755)
    monkeypatch.setenv("GIT_TEMPLATE_DIR", str(template))

    materialize(
        {
            "entries": [
                {
                    "type": "git-repo",
                    "path": "project",
                    "commits": [{"files": {"a.txt": "safe\n"}, "message": "safe"}],
                }
            ]
        },
        tmp_path / "source",
    )

    assert not marker.exists()


def test_git_repo_builder_rejects_casefolded_git_admin_path(tmp_path):
    with pytest.raises(SpecError, match="may not target .git"):
        materialize(
            {
                "entries": [
                    {
                        "type": "git-repo",
                        "path": "project",
                        "commits": [
                            {"files": {".GIT/config": "hostile\n"}, "message": "hostile"}
                        ],
                    }
                ]
            },
            tmp_path / "source",
        )


def test_git_repo_builder_rejects_symlink_into_git_admin_path(tmp_path):
    with pytest.raises(SpecError, match="may not target .git"):
        materialize(
            {
                "entries": [
                    {"type": "symlink", "path": "project/admin", "target": ".git"},
                    {
                        "type": "git-repo",
                        "path": "project",
                        "commits": [
                            {"files": {"admin/config": "hostile\n"}, "message": "hostile"}
                        ],
                    },
                ]
            },
            tmp_path / "source",
        )


def test_git_repo_builder_rejects_preexisting_git_admin_symlink(tmp_path):
    outside = tmp_path / "outside-admin"
    outside.mkdir()

    with pytest.raises(SpecError, match=".git"):
        materialize(
            {
                "entries": [
                    {
                        "type": "symlink",
                        "path": "project/.git",
                        "target": "../../outside-admin",
                    },
                    {"type": "git-repo", "path": "project", "commits": []},
                ]
            },
            tmp_path / "source",
        )

    assert list(outside.iterdir()) == []


@pytest.mark.parametrize(
    "entries",
    [
        [
            {"type": "git-repo", "path": "project", "commits": []},
            {"type": "file", "path": "project/.git/config", "text": "owned-direct\n"},
        ],
        [
            {"type": "git-repo", "path": "project", "commits": []},
            {"type": "symlink", "path": "project/admin", "target": ".git"},
            {"type": "file", "path": "project/admin/config", "text": "owned-alias\n"},
        ],
    ],
)
def test_generic_entries_cannot_mutate_declared_repo_admin(entries, tmp_path):
    with pytest.raises(SpecError, match="may not target .git"):
        materialize({"entries": entries}, tmp_path / "source")
