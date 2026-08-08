import functools
import json
import os
import shutil
import stat
import subprocess
from pathlib import Path, PurePosixPath
from typing import Any


TOLERANCE_PATH = Path(__file__).resolve().parents[1] / "tolerance" / "tolerance-v1.json"
GIT_TIMEOUT_SECONDS = 30
ALLOWED_POLICIES = {
    "file-bytes": {"exact"},
    "file-mode": {"exact"},
    "dir-mode": {"exact"},
    "symlink-target": {"exact"},
    "file-mtime": {"exact-ns", "ignore"},
    "dir-mtime": {"exact-ns", "ignore"},
    "ownership": {"ignore"},
    "git-object-id": {"head-and-refs"},
    "git-index": {"semantic-only"},
    "git-remote-config": {"recorded-remote"},
    "git-tracked-file-mtime": {"ignore-checkout"},
    "git-administration": {"semantic-only"},
}


def load_tolerance(path: Path | None = None) -> dict[str, Any]:
    return json.loads((path or TOLERANCE_PATH).read_text(encoding="utf-8"))


def _kind(path: Path) -> str:
    mode = path.lstat().st_mode
    if stat.S_ISLNK(mode):
        return "symlink"
    if stat.S_ISDIR(mode):
        return "dir"
    if stat.S_ISREG(mode):
        return "file"
    return "other"


def _entries(root: Path, *, exclude_git_administration: bool) -> dict[str, str]:
    return {
        path.relative_to(root).as_posix(): _kind(path)
        for path in root.rglob("*")
        if not (
            exclude_git_administration
            and ".git" in path.relative_to(root).parts
        )
    }


def _same_bytes(left: Path, right: Path) -> bool:
    with left.open("rb") as lf, right.open("rb") as rf:
        while True:
            lb = lf.read(1024 * 1024)
            rb = rf.read(1024 * 1024)
            if lb != rb:
                return False
            if not lb:
                return True


def _mode(path: Path) -> int:
    return stat.S_IMODE(path.lstat().st_mode)


def _row_policy(tolerance: dict[str, Any], name: str) -> str:
    for row in tolerance.get("rows", []):
        if row.get("name") == name:
            return str(row.get("policy", ""))
    return ""


def _validate_tolerance(tolerance: dict[str, Any]) -> None:
    for row in tolerance.get("rows", []):
        name = str(row.get("name", ""))
        policy = str(row.get("policy", ""))
        if policy not in ALLOWED_POLICIES.get(name, set()):
            raise ValueError(f"unknown tolerance policy for {name}: {policy}")


def _validated_additive_roots(roots: list[str]) -> tuple[str, ...]:
    result: list[str] = []
    for root in roots:
        path = PurePosixPath(root)
        if (
            not root
            or root == "."
            or path.is_absolute()
            or path.as_posix() != root
            or any(part in {".", ".."} for part in path.parts)
        ):
            raise ValueError(f"invalid additive root: {root}")
        result.append(root)
    return tuple(result)


def _allowed_extra(rel: str, kind: str, roots: tuple[str, ...]) -> bool:
    if any(rel == root or rel.startswith(root + "/") for root in roots):
        return True
    return kind == "dir" and any(root.startswith(rel + "/") for root in roots)


def _row_reachable(tolerance: dict[str, Any], name: str) -> bool:
    for row in tolerance.get("rows", []):
        if row.get("name") == name:
            return row.get("reachable") is True
    return False


def _git_env() -> dict[str, str]:
    env = {key: value for key, value in os.environ.items() if not key.startswith("GIT_")}
    env.update(
        {
            "GIT_CONFIG_NOSYSTEM": "1",
            "GIT_CONFIG_GLOBAL": "/dev/null",
            "GIT_TERMINAL_PROMPT": "0",
            "LC_ALL": "C",
        }
    )
    return env


@functools.cache
def _git_binary() -> str:
    binary = shutil.which("git")
    if binary is None:
        raise ValueError("git semantic comparison requires git on PATH")
    return str(Path(binary).resolve())


def _run_git(repo: Path, args: list[str], *, allow_failure: bool = False) -> subprocess.CompletedProcess[str]:
    try:
        run = subprocess.run(
            [_git_binary(), "-C", str(repo), *args],
            env=_git_env(),
            check=False,
            text=True,
            capture_output=True,
            timeout=GIT_TIMEOUT_SECONDS,
        )
    except subprocess.TimeoutExpired as exc:
        raise ValueError(f"git semantic comparison timed out for {repo}") from exc
    if run.returncode != 0 and not allow_failure:
        detail = run.stderr.strip() or run.stdout.strip() or f"exit {run.returncode}"
        raise ValueError(f"git semantic comparison failed for {repo}: {detail}")
    return run


def _repo_paths(root: Path) -> set[str]:
    repos: set[str] = set()
    for marker in root.rglob(".git"):
        if marker.is_dir() or marker.is_file():
            rel = marker.parent.relative_to(root).as_posix()
            repos.add("." if rel == "." else rel)
    return repos


def _repo_state(repo: Path) -> dict[str, Any]:
    head_run = _run_git(repo, ["rev-parse", "--verify", "HEAD"], allow_failure=True)
    head = head_run.stdout.strip() if head_run.returncode == 0 else None
    branch_run = _run_git(repo, ["symbolic-ref", "--quiet", "--short", "HEAD"], allow_failure=True)
    branch = branch_run.stdout.strip() if branch_run.returncode == 0 else None
    porcelain = _run_git(repo, ["status", "--porcelain=v2"]).stdout
    refs: dict[str, str] = {}
    for line in _run_git(
        repo,
        ["for-each-ref", "--format=%(refname) %(objectname)"],
    ).stdout.splitlines():
        ref, sha = line.split(" ", 1)
        if not ref.startswith("refs/remotes/"):
            refs[ref] = sha
    remotes: dict[str, list[str]] = {}
    for name in _run_git(repo, ["remote"]).stdout.splitlines():
        remotes[name] = _run_git(repo, ["remote", "get-url", "--all", name]).stdout.splitlines()
    return {
        "head": head,
        "branch": branch,
        "porcelain_clean": not porcelain.strip(),
        "refs": refs,
        "remotes": remotes,
    }


def _repo_at(root: Path, rel: str) -> Path:
    return root if rel == "." else root / rel


def _carried_refs(refs: dict[str, str]) -> dict[str, str]:
    return {
        ref: sha
        for ref, sha in refs.items()
        if ref.startswith("refs/heads/") or ref.startswith("refs/tags/")
    }


def _tracked_paths(root: Path) -> set[str]:
    tracked: set[str] = set()
    for rel in _repo_paths(root):
        repo = _repo_at(root, rel)
        for repo_rel in _run_git(repo, ["ls-files", "-z"]).stdout.split("\0"):
            if not repo_rel:
                continue
            tracked.add(repo_rel if rel == "." else f"{rel}/{repo_rel}")
    return tracked


def _compare_repo_semantics(src: Path, restored: Path, tol: dict[str, Any]) -> list[str]:
    findings: list[str] = []
    src_repos = _repo_paths(src)
    restored_repos = _repo_paths(restored)
    for rel in sorted(src_repos - restored_repos):
        findings.append(f"D: missing repo: {rel}")
    for rel in sorted(restored_repos - src_repos):
        findings.append(f"D: extra repo: {rel}")
    for rel in sorted(src_repos & restored_repos):
        left = _repo_state(_repo_at(src, rel))
        right = _repo_state(_repo_at(restored, rel))
        if _row_reachable(tol, "git-object-id"):
            left_refs = _carried_refs(left["refs"])
            right_refs = _carried_refs(right["refs"])
            if left["head"] != right["head"]:
                findings.append(f"D: repo {rel} HEAD mismatch: {left['head']} != {right['head']}")
            if left["branch"] != right["branch"]:
                findings.append(
                    f"D: repo {rel} branch mismatch: {left['branch']} != {right['branch']}"
                )
            for ref in sorted(left_refs.keys() - right_refs.keys()):
                findings.append(f"D: repo {rel} missing ref: {ref}")
            for ref in sorted(right_refs.keys() - left_refs.keys()):
                findings.append(f"D: repo {rel} extra ref: {ref}")
            for ref in sorted(left_refs.keys() & right_refs.keys()):
                if left_refs[ref] != right_refs[ref]:
                    findings.append(
                        f"D: repo {rel} ref mismatch for {ref}: "
                        f"{left_refs[ref]} != {right_refs[ref]}"
                    )
        if _row_reachable(tol, "git-index"):
            if not left["porcelain_clean"]:
                findings.append(f"D: source repo {rel} porcelain-v2 is not clean")
            if not right["porcelain_clean"]:
                findings.append(f"D: restored repo {rel} porcelain-v2 is not clean")
        if _row_reachable(tol, "git-remote-config") and left["remotes"] != right["remotes"]:
            findings.append(
                f"D: repo {rel} remote config mismatch: {left['remotes']} != {right['remotes']}"
            )
    return findings


def assert_repo_state(root: Path, expected: dict[str, Any]) -> list[str]:
    findings: list[str] = []
    root_real = root.resolve()
    for rel, wanted in sorted(expected.items()):
        repo = _repo_at(root, str(rel))
        if not repo.resolve(strict=False).is_relative_to(root_real):
            findings.append(f"D: repo expectation escapes root: {rel}")
            continue
        if not (repo / ".git").exists():
            findings.append(f"D: expected repo missing: {rel}")
            continue
        actual = _repo_state(repo)
        if "head_sha" in wanted and actual["head"] != wanted["head_sha"]:
            findings.append(
                f"D: repo {rel} HEAD mismatch: {actual['head']} != {wanted['head_sha']}"
            )
        if wanted.get("head_unborn") is True and actual["head"] is not None:
            findings.append(f"D: repo {rel} HEAD expected unborn, got {actual['head']}")
        if "branch" in wanted and actual["branch"] != wanted["branch"]:
            findings.append(
                f"D: repo {rel} branch mismatch: {actual['branch']} != {wanted['branch']}"
            )
        if "porcelain_clean" in wanted and actual["porcelain_clean"] != wanted["porcelain_clean"]:
            findings.append(
                f"D: repo {rel} porcelain cleanliness mismatch: "
                f"{actual['porcelain_clean']} != {wanted['porcelain_clean']}"
            )
        if "refs" in wanted:
            wanted_refs = wanted["refs"]
            for ref in sorted(wanted_refs.keys() - actual["refs"].keys()):
                findings.append(f"D: repo {rel} missing ref: {ref}")
            for ref in sorted(actual["refs"].keys() - wanted_refs.keys()):
                findings.append(f"D: repo {rel} extra ref: {ref}")
            for ref in sorted(wanted_refs.keys() & actual["refs"].keys()):
                if wanted_refs[ref] != actual["refs"][ref]:
                    findings.append(
                        f"D: repo {rel} ref mismatch for {ref}: "
                        f"{actual['refs'][ref]} != {wanted_refs[ref]}"
                    )
    return findings


def compare_trees(
    src: Path,
    restored: Path,
    tol: dict[str, Any],
    additive_roots: list[str] | None = None,
) -> list[str]:
    _validate_tolerance(tol)
    allowed_roots = _validated_additive_roots(additive_roots or [])
    findings: list[str] = []
    exclude_git_administration = _row_policy(tol, "git-administration") == "semantic-only"
    src_entries = _entries(src, exclude_git_administration=exclude_git_administration)
    restored_entries = _entries(
        restored,
        exclude_git_administration=exclude_git_administration,
    )
    tracked_paths = (
        _tracked_paths(src)
        if _row_policy(tol, "git-tracked-file-mtime") == "ignore-checkout"
        else set()
    )

    for rel in sorted(src_entries.keys() - restored_entries.keys()):
        findings.append(f"C: missing path: {rel}")
    for rel in sorted(restored_entries.keys() - src_entries.keys()):
        if not _allowed_extra(rel, restored_entries[rel], allowed_roots):
            findings.append(f"C: extra path: {rel}")

    for rel in sorted(src_entries.keys() & restored_entries.keys()):
        src_kind = src_entries[rel]
        restored_kind = restored_entries[rel]
        left = src / rel
        right = restored / rel
        if src_kind != restored_kind:
            findings.append(f"C: kind mismatch for {rel}: {src_kind} != {restored_kind}")
            continue

        if src_kind == "file":
            if not _same_bytes(left, right):
                findings.append(f"A: byte mismatch for {rel}")
            if _mode(left) != _mode(right):
                findings.append(f"B: mode mismatch for {rel}: {oct(_mode(left))} != {oct(_mode(right))}")
            if rel not in tracked_paths and _row_policy(tol, "file-mtime") == "exact-ns":
                if left.stat().st_mtime_ns != right.stat().st_mtime_ns:
                    findings.append(f"B: file-mtime mismatch for {rel}")
        elif src_kind == "dir":
            if _mode(left) != _mode(right):
                findings.append(f"B: mode mismatch for {rel}: {oct(_mode(left))} != {oct(_mode(right))}")
            if _row_policy(tol, "dir-mtime") == "exact-ns":
                if left.stat().st_mtime_ns != right.stat().st_mtime_ns:
                    findings.append(f"B: dir-mtime mismatch for {rel}")
        elif src_kind == "symlink":
            if os.readlink(left) != os.readlink(right):
                findings.append(f"B: symlink target mismatch for {rel}")

    findings.extend(_compare_repo_semantics(src, restored, tol))
    return findings


def assert_members(members: list[str], present: list[str], absent: list[str]) -> list[str]:
    member_set = set(members)
    findings = [f"member missing: {name}" for name in present if name not in member_set]
    findings.extend(f"member present but expected absent: {name}" for name in absent if name in member_set)
    return findings
