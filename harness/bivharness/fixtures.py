import base64
import os
import shutil
import subprocess
from pathlib import Path
from typing import Any


class SpecError(ValueError):
    pass


def _safe_path(root: Path, relpath: str) -> Path:
    root_real = root.resolve()
    candidate = root.joinpath(relpath).resolve(strict=False)
    if not candidate.is_relative_to(root_real):
        raise SpecError(f"path escapes fixture root: {relpath}")
    return candidate


def _entry_bytes(entry: dict[str, Any]) -> bytes:
    has_text = "text" in entry
    has_b64 = "bytes_b64" in entry
    if has_text == has_b64:
        raise SpecError("file entry requires exactly one of text or bytes_b64")
    if has_text:
        return str(entry["text"]).encode("utf-8")
    try:
        return base64.b64decode(str(entry["bytes_b64"]), validate=True)
    except Exception as exc:
        raise SpecError("invalid bytes_b64") from exc


def _git_binary() -> str:
    resolved = shutil.which("git")
    if resolved is None:
        raise SpecError("git fixture requires git on PATH")
    return str(Path(resolved).resolve())


def _git_env(root: Path) -> dict[str, str]:
    home = root.parent / ".bivharness-git-home"
    home.mkdir(parents=True, exist_ok=True)
    global_config = home / "gitconfig"
    global_config.touch(exist_ok=True)
    env = {key: value for key, value in os.environ.items() if not key.startswith("GIT_")}
    env.update(
        {
            "HOME": str(home),
            "GIT_CONFIG_GLOBAL": str(global_config),
            "GIT_CONFIG_NOSYSTEM": "1",
            "GIT_TERMINAL_PROMPT": "0",
            "LC_ALL": "C",
            "TZ": "UTC",
            "GIT_AUTHOR_NAME": "Biv Harness",
            "GIT_AUTHOR_EMAIL": "biv-harness@example.invalid",
            "GIT_COMMITTER_NAME": "Biv Harness",
            "GIT_COMMITTER_EMAIL": "biv-harness@example.invalid",
            "GIT_AUTHOR_DATE": "2000-01-01T00:00:00+0000",
            "GIT_COMMITTER_DATE": "2000-01-01T00:00:00+0000",
        }
    )
    return env


def _run_git(
    binary: str,
    args: list[str],
    env: dict[str, str],
    *,
    cwd: Path | None = None,
) -> str:
    run = subprocess.run(
        [binary, "-c", "commit.gpgsign=false", *args],
        cwd=cwd,
        env=env,
        check=False,
        text=True,
        capture_output=True,
    )
    if run.returncode != 0:
        detail = run.stderr.strip() or run.stdout.strip() or f"exit {run.returncode}"
        raise SpecError(f"git fixture command failed: {detail}")
    return run.stdout.strip()


def _commit_index(shas: list[str], value: Any, label: str) -> str:
    if not isinstance(value, int) or isinstance(value, bool) or value < 0 or value >= len(shas):
        raise SpecError(f"{label} commit index out of range: {value}")
    return shas[value]


def _materialize_commit_files(repo: Path, files: Any) -> None:
    if not isinstance(files, dict):
        raise SpecError("git commit files must be an object")
    for relpath, content in files.items():
        rel = str(relpath)
        if any(part.casefold() == ".git" for part in Path(rel).parts):
            raise SpecError("git commit file may not target .git")
        path = _safe_path(repo, rel)
        canonical_rel = path.relative_to(repo.resolve())
        if any(part.casefold() == ".git" for part in canonical_rel.parts):
            raise SpecError("git commit file may not target .git")
        if content is None:
            if path.is_dir() and not path.is_symlink():
                shutil.rmtree(path)
            else:
                try:
                    path.unlink()
                except FileNotFoundError:
                    pass
            continue
        path.parent.mkdir(parents=True, exist_ok=True)
        if isinstance(content, dict):
            path.write_bytes(_entry_bytes(content))
        elif isinstance(content, str):
            path.write_text(content, encoding="utf-8")
        else:
            raise SpecError(f"unsupported git commit file value for {rel}")


def _bare_id(value: Any) -> str:
    bare_id = str(value)
    if not bare_id or bare_id in {".", ".."} or "/" in bare_id or "\\" in bare_id:
        raise SpecError(f"invalid git-bare id: {bare_id}")
    return bare_id


def _reject_declared_repo_admin_target(
    root: Path,
    path: Path,
    declared_repo_paths: list[str],
) -> None:
    for relpath in declared_repo_paths:
        if not relpath:
            continue
        repo = _safe_path(root, relpath)
        if not path.is_relative_to(repo):
            continue
        within_repo = path.relative_to(repo)
        if any(part.casefold() == ".git" for part in within_repo.parts):
            raise SpecError("fixture entry may not target .git")


def _materialize_git_repo(
    entry: dict[str, Any],
    root: Path,
    remotes: dict[str, Path],
    binary: str,
    env: dict[str, str],
) -> None:
    relpath = str(entry.get("path", ""))
    if not relpath:
        raise SpecError("git-repo path is required")
    repo = _safe_path(root, relpath)
    repo.parent.mkdir(parents=True, exist_ok=True)
    if repo.is_dir() and any(child.name.casefold() == ".git" for child in repo.iterdir()):
        raise SpecError("git-repo path has preexisting .git administration")
    _run_git(binary, ["init", str(repo)], env)
    _run_git(binary, ["symbolic-ref", "HEAD", "refs/heads/main"], env, cwd=repo)

    shas: list[str] = []
    commits = entry.get("commits", [])
    if not isinstance(commits, list):
        raise SpecError("git-repo commits must be an array")
    for commit in commits:
        if not isinstance(commit, dict):
            raise SpecError("git-repo commit must be an object")
        _materialize_commit_files(repo, commit.get("files", {}))
        _run_git(binary, ["add", "-A", "--"], env, cwd=repo)
        _run_git(
            binary,
            ["commit", "--allow-empty", "--no-gpg-sign", "-m", str(commit.get("message", "fixture"))],
            env,
            cwd=repo,
        )
        shas.append(_run_git(binary, ["rev-parse", "HEAD"], env, cwd=repo))

    branches = entry.get("branches", {})
    if not isinstance(branches, dict):
        raise SpecError("git-repo branches must be an object")
    for name, index in branches.items():
        sha = _commit_index(shas, index, f"branch {name}")
        branch = str(name)
        if branch == "main":
            _run_git(binary, ["reset", "--hard", sha], env, cwd=repo)
        else:
            _run_git(binary, ["branch", "-f", branch, sha], env, cwd=repo)

    tags = entry.get("tags", {})
    if not isinstance(tags, dict):
        raise SpecError("git-repo tags must be an object")
    for name, index in tags.items():
        sha = _commit_index(shas, index, f"tag {name}")
        _run_git(binary, ["tag", str(name), sha], env, cwd=repo)

    if "remote" in entry:
        remote_id = _bare_id(entry["remote"])
        if remote_id not in remotes:
            raise SpecError(f"unknown git-bare remote: {remote_id}")
        _run_git(binary, ["remote", "add", "origin", str(remotes[remote_id])], env, cwd=repo)
        pushes = entry.get("push", [])
        if not isinstance(pushes, list) or not all(isinstance(item, str) for item in pushes):
            raise SpecError("git-repo push must be an array of refspec strings")
        for refspec in pushes:
            _run_git(binary, ["push", "origin", "--", refspec], env, cwd=repo)
    elif entry.get("push"):
        raise SpecError("git-repo push requires remote")


def materialize(spec: dict[str, Any], root: Path) -> None:
    root.mkdir(parents=True, exist_ok=True)
    entries = spec.get("entries", [])
    declared_repo_paths = [
        str(entry.get("path", ""))
        for entry in entries
        if entry.get("type") == "git-repo"
    ]
    binary = _git_binary() if any(entry.get("type") in {"git-bare", "git-repo"} for entry in entries) else ""
    env = _git_env(root) if binary else {}
    remote_root = root.parent / ".bivharness-git-remotes"
    remotes: dict[str, Path] = {}
    for entry in entries:
        if entry.get("type") != "git-bare":
            continue
        bare_id = _bare_id(entry.get("id", ""))
        if bare_id in remotes:
            raise SpecError(f"duplicate git-bare id: {bare_id}")
        remote = remote_root / f"{bare_id}.git"
        remote.parent.mkdir(parents=True, exist_ok=True)
        _run_git(binary, ["init", "--bare", str(remote)], env)
        _run_git(binary, ["symbolic-ref", "HEAD", "refs/heads/main"], env, cwd=remote)
        remotes[bare_id] = remote.resolve()

    for entry in entries:
        entry_type = entry.get("type")
        if entry_type == "git-bare":
            continue
        if entry_type == "git-repo":
            _materialize_git_repo(entry, root, remotes, binary, env)
            continue
        path = _safe_path(root, str(entry.get("path", "")))
        _reject_declared_repo_admin_target(root, path, declared_repo_paths)

        if entry_type == "dir":
            path.mkdir(parents=True, exist_ok=True)
            if "mode" in entry:
                os.chmod(path, int(str(entry["mode"]), 8))
            continue

        if entry_type == "file":
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_bytes(_entry_bytes(entry))
            if "mode" in entry:
                os.chmod(path, int(str(entry["mode"]), 8))
            continue

        if entry_type == "symlink":
            path.parent.mkdir(parents=True, exist_ok=True)
            try:
                path.unlink()
            except FileNotFoundError:
                pass
            os.symlink(str(entry["target"]), path)
            continue

        raise SpecError(f"unsupported fixture entry type: {entry_type}")
