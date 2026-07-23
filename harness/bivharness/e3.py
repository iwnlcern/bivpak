import errno
import getpass
import hashlib
import json
import os
import posixpath
import re
import secrets
import shlex
import shutil
import stat
import subprocess
import unicodedata
import uuid
from pathlib import Path
from typing import Any, Callable, NamedTuple

from bivharness.artifact import extract_member, list_members
from bivharness.host2_credentials import (
    CredentialResult,
    CredentialStatus,
    SourceIdentity,
    claude_shape_ok,
    codex_shape_ok,
    materialize_file_credential,
    materialize_keychain_credential,
    snapshot_identity,
)
from bivharness.precheck import pin_env, probe, profile_root_failures
from bivharness.report import ScenarioResult, Status, serialize_report


CREDENTIAL_ENV_NAMES = (
    "ANTHROPIC_API_KEY",
    "OPENAI_API_KEY",
    "CODEX_ACCESS_TOKEN",
)
CREDENTIAL_DECOY_NAMES = (".credentials.json", "auth.json", ".env")
CREDENTIAL_DECOY_ROOT = ".biv-e3-credential-decoys"
CLAUDE_KEYCHAIN_SERVICE = "Claude Code-credentials"
CREDENTIAL_MAX_BYTES = 64 * 1024
DOTENV_SAFE_SENTINEL = re.compile(r"[A-Za-z0-9_.:@/+\-=]+")
CLAUDE_RESUME_MUTATION = "appends-same-file"
CODEX_RESUME_SHAPE = "appends-same-rollout"
E3_CLASS = "E3 (real CLI resume in isolated profile)"
COMMAND_TIMEOUT_S = 120
_CLOEXEC = getattr(os, "O_CLOEXEC", 0)
_DIRECTORY_NOFOLLOW_FLAGS = os.O_RDONLY | os.O_DIRECTORY | os.O_NOFOLLOW | _CLOEXEC
_REGULAR_NOFOLLOW_FLAGS = os.O_RDONLY | os.O_NOFOLLOW | os.O_NONBLOCK | _CLOEXEC
_CREDENTIAL_SCAN_CHUNK_SIZE = 64 * 1024
_SANITIZED_REPORT_ID = "e3-report-sanitized"
_SANITIZED_REPORT_TIER = "E3"
_SANITIZED_REPORT_DETAIL = "credential value detected; report invalidated"
LIVE_STORE_SELECTORS: dict[str, tuple[str, ...]] = {
    "claude-code": ("CLAUDE_CONFIG_DIR",),
    "codex": ("CODEX_HOME",),
}
SESSION_LOCATIONS: dict[str, tuple[str, ...]] = {
    "claude-code": ("projects",),
    "codex": ("sessions", "session_index.jsonl", "archived_sessions"),
}
_ADAPTER_SOURCE_ANCHORS = {
    "claude_inventory": (
        "src/adapters/claude_code/claude_code.cpp",
        '.collect = {ArtifactClass{.name = "project-transcripts"',
        "b63ee9afd60b27ac5eccb557c551fd7e71b0028c1d40629be4727ba92fc70b62",
    ),
    "codex_inventory": (
        "src/adapters/codex/codex.cpp",
        '.collect = {ArtifactClass{.name = "rollouts"',
        "313f9d70fc3baa5110271c418dc13ffd7fcb83829f732f0a0dd5b0851a1bacc8",
    ),
    "codex_discover_archived": (
        "src/adapters/codex/codex.cpp",
        'if (fs::exists(root / "archived_sessions", ec))',
        "98eb3f362d23dcb4dd39881cc7add622155505a802b697f404417c8b0fc51b72",
    ),
}


class _BivOutcome(NamedTuple):
    ok: bool
    warnings: list[str]
    detail: str
    envelope: dict[str, Any] | None


class _OpenResultOutcome(NamedTuple):
    ok: bool
    output_dir: str
    groups: list[dict[str, Any]]
    detail: str


class _ScenarioExit(Exception):
    def __init__(self, result: ScenarioResult) -> None:
        super().__init__()
        self.result = result


class _NofollowParent(NamedTuple):
    descriptor: int
    name: str
    checks: tuple[tuple[int, str, os.stat_result], ...]
    descriptors: tuple[int, ...]


class _CredentialScanner:
    """Fail closed while searching private credential values in untrusted trees."""

    __slots__ = ("_values",)

    def __init__(self) -> None:
        self._values: list[bytearray] = []

    def __repr__(self) -> str:
        return "_CredentialScanner()"

    @property
    def active(self) -> bool:
        return bool(self._values)

    def add_value(self, value: str | bytes | bytearray) -> None:
        if isinstance(value, str):
            encoded = value.encode("utf-8")
            if encoded:
                self._values.append(bytearray(encoded))
            return
        if isinstance(value, bytearray):
            if value:
                self._values.append(bytearray(value))
            return
        if isinstance(value, bytes):
            if value:
                self._values.append(bytearray(value))
            return
        raise TypeError("credential value must be text or bytes")

    def scan_bytes(self, blob: bytes | bytearray) -> bool:
        return any(value in blob for value in self._values)

    def scan_text(self, text: str) -> bool:
        return self.scan_bytes(text.encode("utf-8"))

    def _open_root(self, root: Path) -> tuple[int, tuple[int, ...], tuple[tuple[int, str, os.stat_result], ...]]:
        descriptor = os.open(root.anchor, _DIRECTORY_NOFOLLOW_FLAGS)
        descriptors = [descriptor]
        checks: list[tuple[int, str, os.stat_result]] = []
        try:
            for name in root.parts[1:]:
                expected = os.stat(name, dir_fd=descriptor, follow_symlinks=False)
                if not stat.S_ISDIR(expected.st_mode):
                    raise ValueError("scan root is not a directory")
                child = os.open(name, _DIRECTORY_NOFOLLOW_FLAGS, dir_fd=descriptor)
                opened = os.fstat(child)
                if not stat.S_ISDIR(opened.st_mode) or not _same_entry(expected, opened):
                    os.close(child)
                    raise ValueError("scan root changed during inspection")
                checks.append((descriptor, name, expected))
                descriptors.append(child)
                descriptor = child
            return descriptor, tuple(descriptors), tuple(checks)
        except BaseException:
            for opened in reversed(descriptors):
                os.close(opened)
            raise

    @staticmethod
    def _entry_matches(
        parent_descriptor: int,
        name: str,
        expected: os.stat_result,
    ) -> bool:
        current = os.stat(name, dir_fd=parent_descriptor, follow_symlinks=False)
        return _same_entry(expected, current)

    @staticmethod
    def _directory_snapshot_matches(
        before: os.stat_result,
        after: os.stat_result,
    ) -> bool:
        return (
            before.st_dev,
            before.st_ino,
            stat.S_IFMT(before.st_mode),
            before.st_nlink,
            before.st_size,
            before.st_mtime_ns,
            before.st_ctime_ns,
        ) == (
            after.st_dev,
            after.st_ino,
            stat.S_IFMT(after.st_mode),
            after.st_nlink,
            after.st_size,
            after.st_mtime_ns,
            after.st_ctime_ns,
        )

    @staticmethod
    def _regular_snapshot_matches(
        before: os.stat_result,
        after: os.stat_result,
    ) -> bool:
        return _same_entry(before, after) and (
            before.st_size,
            before.st_mtime_ns,
            before.st_ctime_ns,
        ) == (
            after.st_size,
            after.st_mtime_ns,
            after.st_ctime_ns,
        )

    def _scan_regular(
        self,
        parent_descriptor: int,
        name: str,
        expected: os.stat_result,
        *,
        read_contents: bool,
        require_single_link: bool = False,
    ) -> bool:
        if require_single_link and expected.st_nlink != 1:
            return True
        descriptor = os.open(name, _REGULAR_NOFOLLOW_FLAGS, dir_fd=parent_descriptor)
        try:
            opened = os.fstat(descriptor)
            if (
                not stat.S_ISREG(opened.st_mode)
                or not self._regular_snapshot_matches(expected, opened)
                or (require_single_link and opened.st_nlink != 1)
            ):
                return True
            if read_contents:
                tail = b""
                tail_size = max((len(value) - 1 for value in self._values), default=0)
                while True:
                    chunk = os.read(descriptor, _CREDENTIAL_SCAN_CHUNK_SIZE)
                    if not chunk:
                        break
                    window = tail + chunk
                    if self.scan_bytes(window):
                        return True
                    tail = window[-tail_size:] if tail_size else b""
            final = os.fstat(descriptor)
            if (
                not stat.S_ISREG(final.st_mode)
                or not self._regular_snapshot_matches(opened, final)
                or (require_single_link and final.st_nlink != 1)
            ):
                return True
        finally:
            os.close(descriptor)
        current = os.stat(name, dir_fd=parent_descriptor, follow_symlinks=False)
        return (
            not self._regular_snapshot_matches(final, current)
            or (require_single_link and current.st_nlink != 1)
        )

    def _scan_directory(
        self,
        descriptor: int,
        lexical_path: Path,
        excluded: set[Path],
        unseen_exclusions: set[Path],
    ) -> bool:
        try:
            before = os.fstat(descriptor)
            if not stat.S_ISDIR(before.st_mode):
                return True
            with os.scandir(descriptor) as entries:
                for entry in entries:
                    name = entry.name
                    path = lexical_path / name
                    expected = os.stat(
                        name,
                        dir_fd=descriptor,
                        follow_symlinks=False,
                    )
                    if path in excluded:
                        unseen_exclusions.discard(path)
                        if not stat.S_ISREG(expected.st_mode):
                            return True
                        if self._scan_regular(
                            descriptor,
                            name,
                            expected,
                            read_contents=False,
                            require_single_link=True,
                        ):
                            return True
                        continue
                    if stat.S_ISREG(expected.st_mode):
                        if self._scan_regular(
                            descriptor,
                            name,
                            expected,
                            read_contents=True,
                        ):
                            return True
                        continue
                    if not stat.S_ISDIR(expected.st_mode):
                        return True
                    child = os.open(name, _DIRECTORY_NOFOLLOW_FLAGS, dir_fd=descriptor)
                    try:
                        opened = os.fstat(child)
                        if not stat.S_ISDIR(opened.st_mode) or not _same_entry(expected, opened):
                            return True
                        if self._scan_directory(child, path, excluded, unseen_exclusions):
                            return True
                    finally:
                        os.close(child)
                    if not self._entry_matches(descriptor, name, expected):
                        return True
            after = os.fstat(descriptor)
            if (
                not stat.S_ISDIR(after.st_mode)
                or not self._directory_snapshot_matches(before, after)
            ):
                return True
        except (OSError, ValueError, RuntimeError):
            return True
        return False

    def scan_tree(self, root: Path, exclude: set[Path]) -> bool:
        """Return True for a secret or any unsafe traversal condition."""
        try:
            lexical_root = Path(root)
            excluded = {Path(path) for path in exclude}
            if not lexical_root.is_absolute() or any(not path.is_absolute() for path in excluded):
                return True
            descriptor, descriptors, checks = self._open_root(lexical_root)
            try:
                unseen_exclusions = set(excluded)
                if self._scan_directory(
                    descriptor,
                    lexical_root,
                    excluded,
                    unseen_exclusions,
                ):
                    return True
                for parent_descriptor, name, expected in reversed(checks):
                    if not self._entry_matches(parent_descriptor, name, expected):
                        return True
                return bool(unseen_exclusions)
            finally:
                for opened in reversed(descriptors):
                    os.close(opened)
        except (OSError, ValueError, RuntimeError, TypeError):
            return True

    def drop(self) -> None:
        try:
            for value in self._values:
                value[:] = b"\0" * len(value)
        finally:
            self._values.clear()


def _sanitized_report_result() -> ScenarioResult:
    return ScenarioResult(
        id=_SANITIZED_REPORT_ID,
        tier=_SANITIZED_REPORT_TIER,
        status=Status.INVALID,
        classes=[],
        held_asserts=[],
        detail=_SANITIZED_REPORT_DETAIL,
        warnings=[],
    )


def _minimal_sanitized_report_result() -> ScenarioResult:
    return ScenarioResult(
        id="",
        tier="",
        status=Status.INVALID,
        classes=[],
        held_asserts=[],
        detail="",
        warnings=[],
    )


def _finalize_report(
    result: ScenarioResult,
    scanner: _CredentialScanner,
) -> ScenarioResult:
    try:
        if not scanner.scan_bytes(serialize_report([result]).encode("utf-8")):
            return result
    except Exception:
        pass
    sanitized = _sanitized_report_result()
    try:
        if not scanner.scan_bytes(serialize_report([sanitized]).encode("utf-8")):
            return sanitized
    except Exception:
        pass
    minimal = _minimal_sanitized_report_result()
    try:
        scanner.scan_bytes(serialize_report([minimal]).encode("utf-8"))
    except Exception:
        pass
    return minimal


def _scan_and_teardown(
    primary: ScenarioResult,
    scanner: _CredentialScanner,
    scratch: Path,
    *,
    child_outputs: list[bytes],
    ambient_snapshots: dict[str, SourceIdentity],
    claude_dest: Path,
    codex_dest: Path,
    profile_root: Path,
    host2: Path,
    seed_parent: Path,
    remove_targets: bool = True,
) -> ScenarioResult:
    """Settle one result, scan all captured state, then remove every private target."""

    notes: list[str] = []

    def note(value: str) -> None:
        if value not in notes:
            notes.append(value)

    def remove_file(path: Path) -> None:
        try:
            os.lstat(path)
        except FileNotFoundError:
            return
        except BaseException:
            note("cleanup-stat-failed")
            return
        try:
            path.unlink()
        except BaseException:
            note("cleanup-unlink-failed")

    def remove_tree(path: Path) -> None:
        try:
            os.lstat(path)
        except FileNotFoundError:
            return
        except BaseException:
            note("cleanup-stat-failed")
            return

        def onerror(_function: Callable[..., Any], _path: str, _exc: Any) -> None:
            note("cleanup-rmtree-failed")

        try:
            shutil.rmtree(path, onerror=onerror)
        except BaseException:
            note("cleanup-rmtree-failed")

    def exact_exclusion(path: Path) -> Path | None:
        opened: _NofollowParent | None = None
        try:
            opened = _open_parent_directory_nofollow(path)
            if opened is None:
                return None
            expected = _entry_status(opened.descriptor, opened.name)
            if (
                expected is None
                or not stat.S_ISREG(expected.st_mode)
                or expected.st_nlink != 1
            ):
                return None
            _verify_parent_unchanged(opened, "credential exclusion")
            return path
        except BaseException:
            return None
        finally:
            if opened is not None:
                try:
                    _close_nofollow_parent(opened)
                except BaseException:
                    note("credential-scan-failed")

    def scanned_constant() -> ScenarioResult:
        candidates = (
            _sanitized_report_result(),
            _minimal_sanitized_report_result(),
        )
        for candidate in candidates:
            try:
                serialized = serialize_report([candidate]).encode("utf-8")
                if not scanner.scan_bytes(serialized):
                    return candidate
            except BaseException:
                continue
        return candidates[-1]

    final: ScenarioResult | None = None
    try:
        active = False
        try:
            active = scanner.active
        except BaseException:
            note("credential-scan-failed")
        if active:
            try:
                exclusions = {
                    path
                    for path in (exact_exclusion(claude_dest), exact_exclusion(codex_dest))
                    if path is not None
                }
                if scanner.scan_tree(scratch.resolve(strict=False), exclusions):
                    note("credential-scan-detected")
            except BaseException:
                note("credential-scan-failed")
            for output in child_outputs:
                try:
                    if scanner.scan_bytes(output):
                        note("credential-child-output-detected")
                except BaseException:
                    note("credential-child-output-scan-failed")
            expected = ambient_snapshots.get("codex-auth.json")
            if expected is not None:
                try:
                    current = snapshot_identity(
                        Path("~/.codex/auth.json").expanduser(),
                        max_bytes=CREDENTIAL_MAX_BYTES,
                    )
                    if current != expected:
                        note("codex-ambient-credential-drift")
                except BaseException:
                    note("codex-ambient-credential-drift")

        if remove_targets:
            remove_file(claude_dest)
            remove_file(codex_dest)
            for target in (profile_root, host2, seed_parent):
                remove_tree(target)
        for target in (claude_dest, codex_dest, profile_root, host2, seed_parent):
            try:
                os.lstat(target)
            except FileNotFoundError:
                continue
            except BaseException:
                note("cleanup-absence-stat-failed")
            else:
                note("cleanup-target-present")

        settled = primary
        if notes:
            if primary.status is Status.PASS:
                settled = ScenarioResult(
                    primary.id,
                    primary.tier,
                    Status.INVALID,
                    [],
                    [],
                    detail="post-materialization verification failed",
                    warnings=[*primary.warnings, *notes],
                )
            else:
                settled = ScenarioResult(
                    primary.id,
                    primary.tier,
                    primary.status,
                    list(primary.classes),
                    list(primary.held_asserts),
                    detail=primary.detail,
                    warnings=[*primary.warnings, *notes],
                )
        try:
            final = _finalize_report(settled, scanner)
        except BaseException:
            final = scanned_constant()
    except BaseException:
        final = scanned_constant()
    finally:
        try:
            scanner.drop()
        except BaseException:
            final = scanned_constant()
    return final if final is not None else scanned_constant()


def rejected_credential_names(env: dict[str, str]) -> list[str]:
    return sorted(name for name in CREDENTIAL_ENV_NAMES if name in env)


def ordered_turns_present(transcript: str, turns: list[str]) -> bool:
    cursor = 0
    for turn in turns:
        found = transcript.find(turn, cursor)
        if found < 0:
            return False
        cursor = found + len(turn)
    return True


def _project_key(path: Path) -> str:
    return "".join(ch if ch.isascii() and ch.isalnum() else "-" for ch in path.as_posix())


def scan_secret_values(blob: bytes, secret_values: list[str]) -> list[str]:
    return [f"secret[{index}]" for index, value in enumerate(secret_values) if value and value.encode() in blob]


def scan_image_secret_values(image: Path, secret_values: list[str]) -> list[str]:
    hits: list[str] = []
    for member in list_members(image):
        for hit in scan_secret_values(extract_member(image, member), secret_values):
            hits.append(f"{member}:{hit}")
    return hits


def _is_prefix_list(value: object) -> bool:
    return (
        isinstance(value, list)
        and bool(value)
        and all(isinstance(prefix, str) and prefix for prefix in value)
    )


def version_in_validated_range(version_output: str, validated_prefixes: list[str]) -> bool:
    if not _is_prefix_list(validated_prefixes):
        raise TypeError(
            "validated_version_prefixes must be a non-empty list of non-empty strings; "
            f"got {validated_prefixes!r} (a bare string character-iterates and fails open)"
        )
    versions = re.findall(
        r"(?<![0-9])([0-9]+\.[0-9]+\.[0-9]+)(?![0-9])",
        version_output,
    )
    return len(versions) == 1 and any(
        versions[0].startswith(prefix) for prefix in validated_prefixes
    )


def class_j_failures(seed_workspace: Path, restored_workspace: Path, app_state_paths: list[Path]) -> list[str]:
    failures: list[str] = []
    if seed_workspace.resolve(strict=False) == restored_workspace.resolve(strict=False):
        failures.append("workspace-paths-not-distinct")
    if any(path.exists() for path in app_state_paths):
        failures.append("bivpak-state-present")
    return failures


def assert_resume_containment(
    agent_id: str,
    profile: Path,
    restored_workspace: Path,
    session_id: str,
    turns: list[str],
    probe: str,
    pinned_shape: str,
    *,
    expected_transcript: Path | None = None,
    pre_resume_content: bytes | None = None,
) -> Path:
    if agent_id == "claude-code":
        if pinned_shape != CLAUDE_RESUME_MUTATION:
            raise ValueError("Claude resume mutation does not match pinned shape")
        transcript = profile / "projects" / _project_key(restored_workspace) / f"{session_id}.jsonl"
        probe_hits = []
        for candidate in profile.rglob("*.jsonl"):
            try:
                content = candidate.read_bytes()
            except OSError as exc:
                raise ValueError("unable to inspect Claude transcript") from exc
            try:
                content.decode("utf-8")
            except UnicodeError as exc:
                raise ValueError("invalid UTF-8 Claude transcript") from exc
            if probe.encode() in content:
                probe_hits.append(candidate)
        if probe_hits != [transcript]:
            raise ValueError("Claude resume containment requires the exact installed transcript")
    elif agent_id == "codex":
        if pinned_shape != CODEX_RESUME_SHAPE:
            raise ValueError("Codex resume shape does not match pinned shape")
        if expected_transcript is None:
            raise ValueError("Codex resume containment requires the exact installed transcript")
        transcript = select_owned_rollout(
            profile, session_id, probe, expected_transcript=expected_transcript
        )
    else:
        raise ValueError(f"unsupported E3 agent: {agent_id}")
    if pre_resume_content is not None and not transcript.read_bytes().startswith(pre_resume_content):
        raise ValueError(f"{agent_id} resume did not append to the installed transcript")
    if not transcript.is_file() or not ordered_turns_present(transcript.read_text(encoding="utf-8"), turns):
        raise ValueError(f"{agent_id} transcript containment failed")
    return transcript


def select_owned_rollout(
    root: Path,
    session_id: str,
    run_token: str,
    *,
    expected_transcript: Path | None = None,
) -> Path:
    matches: list[Path] = []
    for path in root.rglob("rollout-*.jsonl"):
        if session_id not in path.name:
            continue
        try:
            content = path.read_bytes()
        except OSError as exc:
            raise ValueError("unable to inspect same-session rollout") from exc
        if run_token.encode() in content:
            matches.append(path)
    if expected_transcript is not None and matches != [expected_transcript]:
        raise ValueError("Codex resume containment requires the exact installed transcript")
    if len(matches) != 1:
        raise ValueError(f"expected exactly one owned rollout, got {len(matches)}")
    return matches[0]


StoreSnapshot = dict[Path, bytes]


class CaptureAmbiguity(ValueError):
    def __init__(self, candidates: list[Path]) -> None:
        super().__init__(f"capture ambiguity: expected one owned and zero foreign candidates, got {len(candidates)}")
        self.candidates = candidates


class CaptureCommandError(ValueError):
    def __init__(self, candidates: list[Path], error: Exception) -> None:
        super().__init__(f"seed command failed after capture: {error}")
        self.candidates = candidates


def capture_inventory(root: Path, pattern: str) -> StoreSnapshot:
    inventory: StoreSnapshot = {}
    for path in root.rglob(pattern):
        if path.is_file():
            inventory[path] = path.read_bytes()
    return inventory


def _inventory_changes(before: StoreSnapshot, after: StoreSnapshot) -> list[Path]:
    return sorted(path for path in before.keys() | after.keys() if before.get(path) != after.get(path))


def _contains_exact_token(content: bytes, run_token: str) -> bool:
    token = re.escape(run_token.encode())
    return re.search(rb"(?<![A-Za-z0-9_-])" + token + rb"(?![A-Za-z0-9_-])", content) is not None


def classify_capture(
    before: StoreSnapshot,
    after: StoreSnapshot,
    run_token: str,
    path_proof: Callable[[Path], bool] | None = None,
) -> tuple[Path, list[Path]]:
    candidates = _inventory_changes(before, after)
    proof = path_proof or (lambda path: True)
    owned = [
        path for path in candidates
        if proof(path) and _contains_exact_token(after.get(path, b""), run_token)
    ]
    if len(candidates) != 1 or len(owned) != 1:
        raise CaptureAmbiguity(candidates)
    return owned[0], candidates


def _capture_seed_leg(
    root: Path,
    pattern: str,
    run_token: str,
    command: Callable[[], Any],
    path_proof: Callable[[Path], bool] | None = None,
) -> tuple[Any, Path, list[Path]]:
    before = capture_inventory(root, pattern)
    try:
        result = command()
    except (OSError, subprocess.TimeoutExpired) as exc:
        after = capture_inventory(root, pattern)
        try:
            _, candidates = classify_capture(before, after, run_token, path_proof)
        except CaptureAmbiguity as ambiguity:
            raise ambiguity from exc
        raise CaptureCommandError(candidates, exc) from exc
    after = capture_inventory(root, pattern)
    owned, candidates = classify_capture(before, after, run_token, path_proof)
    return result, owned, candidates


def _capture_attempt(
    root: Path,
    pattern: str,
    run_token: str,
    command: Callable[[], Any],
    path_proof: Callable[[Path], bool] | None = None,
) -> tuple[Any | None, Exception | None, list[Path], list[Path]]:
    before = capture_inventory(root, pattern)
    result: Any | None = None
    error: Exception | None = None
    try:
        result = command()
    except (OSError, subprocess.TimeoutExpired) as exc:
        error = exc
    after = capture_inventory(root, pattern)
    candidates = _inventory_changes(before, after)
    proof = path_proof or (lambda path: True)
    owned = [
        path for path in candidates
        if proof(path) and _contains_exact_token(after.get(path, b""), run_token)
    ]
    return result, error, candidates, owned


def _require_retryable_capture(candidates: list[Path], owned: list[Path]) -> None:
    if len(owned) > 1 or len(candidates) != len(owned):
        raise CaptureAmbiguity(candidates)


def _rewrite_agent_command(command: list[str], resolved_binary: str | None) -> list[str]:
    rewritten = list(command)
    if resolved_binary is not None:
        rewritten[0] = resolved_binary
    return rewritten


def _seed_agent(
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
    path_proof = lambda path: _capture_path_proof(
        agent["id"], path, live_profile, seed_workspace
    )
    format_values = {**spec, "workspace": str(seed_workspace), "run_token": agent["run_token"]}
    start_command = _rewrite_agent_command([
        part.format(**format_values)
        for part in agent["seed_start_command"]
    ], resolved_binary)
    seeded, start_error, candidates, owned = _capture_attempt(
        live_profile, agent["ownership_glob"], agent["run_token"],
        lambda: spawn(start_command, seed_workspace, env),
        path_proof,
    )
    capture_candidates.extend(candidates)
    start_failed = start_error is not None or seeded is None or seeded.returncode != 0
    if not start_failed:
        if len(candidates) != 1 or len(owned) != 1:
            raise CaptureAmbiguity(candidates)
        first = owned[0]
    else:
        _require_retryable_capture(candidates, owned)
        first = owned[0] if owned else None
        if first is not None:
            owned_paths.append(first)
            retry_id = _session_id_from_path(agent["id"], first)
            retry_command = _rewrite_agent_command([
                part.format(**{**format_values, "id": retry_id})
                for part in agent["seed_retry_resume_command"]
            ], resolved_binary)
        else:
            retry_command = start_command
        try:
            retried, retry_owned, retry_candidates = _capture_seed_leg(
                live_profile, agent["ownership_glob"], agent["run_token"],
                lambda: spawn(retry_command, seed_workspace, env),
                path_proof,
            )
            capture_candidates.extend(retry_candidates)
        except (CaptureAmbiguity, CaptureCommandError) as exc:
            capture_candidates.extend(exc.candidates)
            raise
        if retried.returncode != 0:
            raise ValueError(f"{agent['id']} first-seed retry failed: {retried.stderr.strip()}")
        if first is not None and retry_owned != first:
            raise CaptureAmbiguity([first, retry_owned])
        first = retry_owned

    if first not in owned_paths:
        owned_paths.append(first)
    seed_id = _session_id_from_path(agent["id"], first)
    continue_command = _rewrite_agent_command([
        part.format(**{**format_values, "id": seed_id})
        for part in agent["seed_continue_command"]
    ], resolved_binary)
    continued, continue_error, candidates, continued_owned = _capture_attempt(
        live_profile, agent["ownership_glob"], agent["run_token"],
        lambda: spawn(continue_command, seed_workspace, env),
        path_proof,
    )
    capture_candidates.extend(candidates)
    continue_failed = continue_error is not None or continued is None or continued.returncode != 0
    if continue_failed:
        _require_retryable_capture(candidates, continued_owned)
        if continued_owned and continued_owned != [first]:
            raise CaptureAmbiguity(candidates)
        try:
            continued, retry_owned, retry_candidates = _capture_seed_leg(
                live_profile, agent["ownership_glob"], agent["run_token"],
                lambda: spawn(continue_command, seed_workspace, env),
                path_proof,
            )
            capture_candidates.extend(retry_candidates)
        except (CaptureAmbiguity, CaptureCommandError) as exc:
            capture_candidates.extend(exc.candidates)
            raise
        if continued.returncode != 0:
            raise ValueError(f"{agent['id']} continuation retry failed: {continued.stderr.strip()}")
        continued_owned = [retry_owned]
    elif len(candidates) != 1 or continued_owned != [first]:
        raise CaptureAmbiguity(candidates)
    if continued_owned != [first] or not ordered_turns_present(
        first.read_text(encoding="utf-8"), spec["seed_turns"]
    ):
        raise ValueError(f"{agent['id']} seed turns were not in one transcript")
    return first


def format_cleanup_report(candidates: list[Path], owned: list[Path]) -> str:
    disclosure = "\n".join(str(path) for path in sorted(set(candidates)))
    cleanup = "\n".join(str(path) for path in sorted(set(owned)))
    return (
        "Capture-window candidate diff (disclosure only):\n"
        f"{disclosure}\n"
        "Ownership-proven cleanup candidates (not deleted):\n"
        f"{cleanup}"
    )


def _same_entry(left: os.stat_result, right: os.stat_result) -> bool:
    return (
        left.st_dev,
        left.st_ino,
        stat.S_IFMT(left.st_mode),
    ) == (
        right.st_dev,
        right.st_ino,
        stat.S_IFMT(right.st_mode),
    )


def _close_nofollow_parent(opened: _NofollowParent) -> None:
    for descriptor in reversed(opened.descriptors):
        os.close(descriptor)


def _open_parent_directory_nofollow(path: Path) -> _NofollowParent | None:
    path = Path(path)
    if not path.is_absolute():
        path = Path.cwd() / path
    parts = path.parts
    current = os.open(path.anchor, _DIRECTORY_NOFOLLOW_FLAGS)
    descriptors = [current]
    checks: list[tuple[int, str, os.stat_result]] = []
    try:
        for component in parts[1:-1]:
            status = _entry_status(current, component)
            if status is None:
                for descriptor in reversed(descriptors):
                    os.close(descriptor)
                return None
            if not stat.S_ISDIR(status.st_mode):
                raise ValueError(
                    f"nofollow parent component {component!r} is nonregular"
                )
            next_descriptor = _open_verified_directory(
                current,
                component,
                status,
                f"nofollow parent component {component!r}",
            )
            checks.append((current, component, status))
            descriptors.append(next_descriptor)
            current = next_descriptor
    except BaseException:
        for descriptor in reversed(descriptors):
            os.close(descriptor)
        raise
    return _NofollowParent(
        current,
        parts[-1] if len(parts) > 1 else ".",
        tuple(checks),
        tuple(descriptors),
    )


def _entry_status(parent_descriptor: int, name: str) -> os.stat_result | None:
    try:
        return os.stat(name, dir_fd=parent_descriptor, follow_symlinks=False)
    except FileNotFoundError:
        return None


def _open_verified_directory(
    parent_descriptor: int,
    name: str,
    expected: os.stat_result,
    label: str,
) -> int:
    descriptor = os.open(
        name,
        _DIRECTORY_NOFOLLOW_FLAGS,
        dir_fd=parent_descriptor,
    )
    try:
        opened = os.fstat(descriptor)
        if not stat.S_ISDIR(opened.st_mode) or not _same_entry(expected, opened):
            raise ValueError(f"{label} changed during nofollow inspection")
    except BaseException:
        os.close(descriptor)
        raise
    return descriptor


def _directory_topology_is_nofollow(path: Path) -> bool:
    """Prove that every lexical component and the target are stable directories."""
    opened = None
    descriptor = None
    valid = False
    try:
        opened = _open_parent_directory_nofollow(path)
        if opened is None:
            return False
        expected = _entry_status(opened.descriptor, opened.name)
        if expected is None or not stat.S_ISDIR(expected.st_mode):
            return False
        descriptor = _open_verified_directory(
            opened.descriptor,
            opened.name,
            expected,
            "restored workspace",
        )
        _verify_entry_unchanged(
            opened.descriptor,
            opened.name,
            expected,
            "restored workspace",
        )
        _verify_parent_unchanged(opened, "restored workspace")
        valid = _same_entry(expected, os.fstat(descriptor))
    except BaseException:
        valid = False
    finally:
        if descriptor is not None:
            try:
                os.close(descriptor)
            except BaseException:
                valid = False
        if opened is not None:
            try:
                _close_nofollow_parent(opened)
            except BaseException:
                valid = False
    return valid


def _verify_entry_unchanged(
    parent_descriptor: int,
    name: str,
    expected: os.stat_result,
    label: str,
) -> os.stat_result:
    current = _entry_status(parent_descriptor, name)
    if current is None or not _same_entry(expected, current):
        raise ValueError(f"{label} changed during nofollow inspection")
    return current


def _verify_parent_unchanged(opened: _NofollowParent, label: str) -> None:
    for parent_descriptor, name, expected in reversed(opened.checks):
        _verify_entry_unchanged(parent_descriptor, name, expected, label)


def _read_regular_file_nofollow(
    parent_descriptor: int,
    name: str,
    expected: os.stat_result,
    label: str,
) -> bytes:
    descriptor = os.open(
        name,
        _REGULAR_NOFOLLOW_FLAGS,
        dir_fd=parent_descriptor,
    )
    try:
        opened = os.fstat(descriptor)
        if not stat.S_ISREG(opened.st_mode) or not _same_entry(expected, opened):
            raise ValueError(f"{label} changed during nofollow inspection")
        chunks: list[bytes] = []
        while True:
            chunk = os.read(descriptor, 1024 * 1024)
            if not chunk:
                break
            chunks.append(chunk)
        final = os.fstat(descriptor)
        if not stat.S_ISREG(final.st_mode) or not _same_entry(opened, final):
            raise ValueError(f"{label} changed during nofollow inspection")
    finally:
        os.close(descriptor)
    _verify_entry_unchanged(parent_descriptor, name, expected, label)
    return b"".join(chunks)


def _read_credential_destination_nofollow(path: Path) -> bytes:
    """Read one private credential destination without following a path component."""
    opened = _open_parent_directory_nofollow(path)
    if opened is None:
        raise ValueError("credential destination unavailable")
    try:
        expected = _entry_status(opened.descriptor, opened.name)
        if (
            expected is None
            or not stat.S_ISREG(expected.st_mode)
            or expected.st_nlink != 1
            or expected.st_size > CREDENTIAL_MAX_BYTES
        ):
            raise ValueError("credential destination unavailable")
        data = _read_regular_file_nofollow(
            opened.descriptor,
            opened.name,
            expected,
            "credential destination",
        )
        if not data or len(data) > CREDENTIAL_MAX_BYTES:
            raise ValueError("credential destination unavailable")
        _verify_parent_unchanged(opened, "credential destination")
        return data
    finally:
        _close_nofollow_parent(opened)


def _seed_credential_scanner(
    scanner: _CredentialScanner,
    raw: bytes,
    credential_id: str,
) -> None:
    scanner.add_value(raw)
    if credential_id == "claude-code":
        if not claude_shape_ok(raw):
            raise ValueError("credential destination unavailable")
        parsed = json.loads(raw)
        oauth = parsed["claudeAiOauth"]
        candidates = (oauth["accessToken"], oauth["refreshToken"])
    elif credential_id == "codex":
        if not codex_shape_ok(raw):
            raise ValueError("credential destination unavailable")
        parsed = json.loads(raw)
        candidates = [parsed.get("OPENAI_API_KEY")]
        tokens = parsed.get("tokens")
        if isinstance(tokens, dict):
            candidates.extend(tokens.values())
    else:
        raise ValueError("credential destination unavailable")
    for value in candidates:
        if isinstance(value, str) and value:
            try:
                encoded = json.dumps(value, ensure_ascii=True)
                if (
                    len(encoded) < 2
                    or encoded[0] != '"'
                    or encoded[-1] != '"'
                ):
                    raise ValueError("credential destination unavailable")
                escaped = encoded[1:-1].encode("ascii")
                scanner.add_value(value)
                scanner.add_value(escaped)
            except (TypeError, UnicodeError, ValueError):
                raise ValueError("credential destination unavailable") from None


def _credential_path_exists_nofollow(path: Path) -> bool:
    opened = _open_parent_directory_nofollow(path)
    if opened is None:
        return False
    try:
        return _entry_status(opened.descriptor, opened.name) is not None
    finally:
        _close_nofollow_parent(opened)


def _snapshot_directory_nofollow(
    descriptor: int,
    relative: Path,
    snapshot: StoreSnapshot,
) -> None:
    with os.scandir(descriptor) as entries:
        for entry in entries:
            path = relative / entry.name
            label = f"snapshot store entry {path}"
            status = entry.stat(follow_symlinks=False)
            if stat.S_ISREG(status.st_mode):
                snapshot[path] = _read_regular_file_nofollow(
                    descriptor, entry.name, status, label
                )
                continue
            if not stat.S_ISDIR(status.st_mode):
                raise ValueError(f"{label} is nonregular")
            child = _open_verified_directory(
                descriptor, entry.name, status, label
            )
            try:
                _snapshot_directory_nofollow(child, path, snapshot)
            finally:
                os.close(child)
            _verify_entry_unchanged(descriptor, entry.name, status, label)


def snapshot_store(root: Path) -> StoreSnapshot:
    opened_parent = _open_parent_directory_nofollow(root)
    if opened_parent is None:
        return {}
    parent_descriptor = opened_parent.descriptor
    name = opened_parent.name
    try:
        status = _entry_status(parent_descriptor, name)
        if status is None:
            _verify_parent_unchanged(opened_parent, f"snapshot store root {root}")
            return {}
        if not stat.S_ISDIR(status.st_mode):
            raise ValueError(f"snapshot store root {root} is nonregular")
        descriptor = _open_verified_directory(
            parent_descriptor,
            name,
            status,
            f"snapshot store root {root}",
        )
        try:
            snapshot: StoreSnapshot = {}
            _snapshot_directory_nofollow(descriptor, Path(), snapshot)
        finally:
            os.close(descriptor)
        _verify_entry_unchanged(
            parent_descriptor,
            name,
            status,
            f"snapshot store root {root}",
        )
        _verify_parent_unchanged(opened_parent, f"snapshot store root {root}")
        return snapshot
    finally:
        _close_nofollow_parent(opened_parent)


def assert_exact_install_delta(
    agent_id: str,
    profile: Path,
    restored_workspace: Path,
    rows: list[dict[str, Any]],
    before: StoreSnapshot,
    after: StoreSnapshot,
    expected_turns: list[str],
) -> list[Path]:
    expected: dict[Path, dict[str, Any]] = {}
    for row in rows:
        installed_id = row.get("installed_session_id")
        if not installed_id:
            raise ValueError("exact install delta: installed id missing")
        if agent_id == "claude-code":
            relative = Path("projects") / _project_key(restored_workspace) / f"{installed_id}.jsonl"
        elif agent_id == "codex":
            matches = [path for path in after if path.name.startswith("rollout-") and installed_id in path.name]
            if len(matches) != 1:
                raise ValueError("exact install delta: Codex installed rollout is not unique")
            relative = matches[0]
        else:
            raise ValueError(f"unsupported E3 agent: {agent_id}")
        expected[relative] = row

    changed = {path for path in before.keys() | after.keys() if before.get(path) != after.get(path)}
    if changed != set(expected):
        raise ValueError("exact install delta: store changes do not match installed rows")
    for relative, row in expected.items():
        content = after.get(relative, b"")
        installed_id = str(row["installed_session_id"])
        image_id = str(row.get("image_session_id", ""))
        if installed_id.encode() not in content or (image_id and image_id.encode() in content):
            raise ValueError("exact install delta: installed transcript identity mismatch")
        try:
            transcript = content.decode("utf-8")
        except UnicodeDecodeError as exc:
            raise ValueError("exact install delta: installed transcript is not UTF-8") from exc
        if not ordered_turns_present(transcript, expected_turns):
            raise ValueError("exact install delta: installed transcript lacks seeded history")
    return sorted(profile / path for path in expected)


def plant_credential_decoys(workspace: Path, sentinels: list[str]) -> list[Path]:
    if not sentinels:
        return []
    if workspace.is_symlink() or not workspace.is_dir():
        raise ValueError("controlled credential-shaped workspace must be a regular directory")
    ignore = workspace / ".bivignore"
    if ignore.is_symlink() or (ignore.exists() and not ignore.is_file()):
        raise ValueError("controlled .bivignore must be a regular file inside workspace")
    decoy_root = workspace / CREDENTIAL_DECOY_ROOT
    if decoy_root.is_symlink() or (decoy_root.exists() and not decoy_root.is_dir()):
        raise ValueError("controlled credential-shaped decoy root must be a regular directory inside workspace")
    decoy_root.mkdir(parents=True, exist_ok=True)
    if decoy_root.resolve().parent != workspace.resolve():
        raise ValueError("controlled credential-shaped decoy root must be a regular directory inside workspace")
    if any(decoy_root.iterdir()):
        raise ValueError("exact controlled credential-shaped decoy set not planted")
    value = ",".join(sentinels)
    paths = [decoy_root / name for name in CREDENTIAL_DECOY_NAMES]
    paths[0].write_text(json.dumps({"apiKey": value}), encoding="utf-8")
    paths[1].write_text(json.dumps({"tokens": {"access_token": value}}), encoding="utf-8")
    paths[2].write_text(f"ANTHROPIC_API_KEY={value}\n", encoding="utf-8")
    existing = ignore.read_text(encoding="utf-8") if ignore.exists() else ""
    ignore_entry = f"{CREDENTIAL_DECOY_ROOT}/"
    if ignore_entry not in existing.splitlines():
        ignore.write_text(existing + ignore_entry + "\n", encoding="utf-8")
    return paths


def verify_credential_decoys(workspace: Path, paths: list[Path], sentinels: list[str]) -> None:
    expected_names = set(CREDENTIAL_DECOY_NAMES)
    if (
        len(paths) != len(expected_names)
        or {path.name for path in paths} != expected_names
        or len({path.parent for path in paths}) != 1
    ):
        raise ValueError("exact controlled credential-shaped decoy set not planted")
    root = paths[0].parent
    if (
        root != workspace / CREDENTIAL_DECOY_ROOT
        or root.is_symlink()
        or not root.is_dir()
        or root.resolve().parent != workspace.resolve()
    ):
        raise ValueError("controlled credential-shaped decoy root must be a regular directory inside workspace")
    if set(root.iterdir()) != set(paths):
        raise ValueError("exact controlled credential-shaped decoy set not planted")
    for path in paths:
        if path.is_symlink() or not path.is_file():
            raise ValueError(f"controlled credential-shaped decoy is not a regular file: {path.name}")

    value = ",".join(sentinels)
    try:
        credentials = json.loads((root / ".credentials.json").read_text(encoding="utf-8"))
        auth = json.loads((root / "auth.json").read_text(encoding="utf-8"))
        dotenv = (root / ".env").read_text(encoding="utf-8")
    except (OSError, UnicodeError, json.JSONDecodeError) as exc:
        raise ValueError("controlled credential-shaped decoy format invalid") from exc
    if (
        credentials != {"apiKey": value}
        or auth != {"tokens": {"access_token": value}}
        or dotenv != f"ANTHROPIC_API_KEY={value}\n"
        or any(sentinel not in value for sentinel in sentinels)
    ):
        raise ValueError("controlled credential-shaped decoy format invalid")


def _hash(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def _clean_env(overrides: dict[str, str] | None = None) -> dict[str, str]:
    env = os.environ.copy()
    for name in CREDENTIAL_ENV_NAMES:
        env.pop(name, None)
    if overrides:
        env.update(overrides)
    rejected = rejected_credential_names(env)
    if rejected:
        raise ValueError("credential environment names present: " + ", ".join(rejected))
    return env


def _spawn(command: list[str], cwd: Path, env: dict[str, str]) -> subprocess.CompletedProcess[str]:
    clean = _clean_env(env)
    return subprocess.run(
        command,
        cwd=cwd,
        env=clean,
        text=True,
        capture_output=True,
        check=False,
        timeout=COMMAND_TIMEOUT_S,
    )


def _spawn_retry(
    command: list[str],
    cwd: Path,
    env: dict[str, str],
    is_success: Callable[[Any], bool] | None = None,
) -> subprocess.CompletedProcess[str]:
    return _spawn_retry_with(command, cwd, env, _spawn, is_success)


def _spawn_retry_with(
    command: list[str],
    cwd: Path,
    env: dict[str, str],
    spawn: Callable[[list[str], Path, dict[str, str]], Any],
    is_success: Callable[[Any], bool] | None = None,
) -> Any:
    predicate = is_success or (lambda result: result.returncode == 0)
    result: Any | None = None
    for attempt in range(2):
        try:
            result = spawn(command, cwd, env)
        except (OSError, subprocess.TimeoutExpired):
            if attempt == 0:
                continue
            raise
        if predicate(result) or attempt == 1:
            return result
    raise ValueError("model-call retry produced no result")


def _spawn_with_capture(
    spawn: Callable[[list[str], Path, dict[str, str]], Any],
    child_outputs: list[bytes],
) -> Callable[[list[str], Path, dict[str, str]], Any]:
    """Preserve every post-materialization child output for final secret scanning."""

    def output_bytes(value: Any) -> bytes:
        if isinstance(value, bytes):
            return value
        return str(value or "").encode("utf-8", errors="replace")

    def capture(command: list[str], cwd: Path, env: dict[str, str]) -> Any:
        try:
            result = spawn(command, cwd, env)
        except BaseException as exc:
            stdout = getattr(exc, "stdout", None)
            if stdout is None:
                stdout = getattr(exc, "output", "")
            child_outputs.append(
                output_bytes(stdout) + output_bytes(getattr(exc, "stderr", ""))
            )
            raise
        child_outputs.append(
            output_bytes(getattr(result, "stdout", ""))
            + output_bytes(getattr(result, "stderr", ""))
        )
        return result

    return capture


def _resolve_agent_binaries(spec: dict[str, Any]) -> dict[str, str]:
    resolved: dict[str, str] = {}
    for agent in spec["agents"]:
        executable = agent["auth_status"][0]
        path = shutil.which(executable)
        if not isinstance(path, str) or not Path(path).is_absolute():
            raise ValueError(
                f"{agent['id']} executable could not be resolved to an absolute path"
            )
        resolved[agent["id"]] = path
    return resolved


def _version_gate_agents(
    contexts: list[tuple[dict[str, Any], Path, dict[str, str]]],
    resolved_binaries: dict[str, str],
    cwd: Path,
    spawn: Callable[[list[str], Path, dict[str, str]], Any],
    scope: str = "",
) -> None:
    failures: list[str] = []
    for agent, _, env in contexts:
        command = _rewrite_agent_command(
            agent["version_command"], resolved_binaries[agent["id"]]
        )
        try:
            version = spawn(command, cwd, env)
            valid = version.returncode == 0 and version_in_validated_range(
                version.stdout + version.stderr,
                agent["validated_version_prefixes"],
            )
        except (OSError, subprocess.TimeoutExpired, TypeError, ValueError):
            valid = False
        if not valid:
            failures.append(agent["id"])
    if failures:
        label = f"{failures[0]} " if failures else ""
        if scope:
            label += f"{scope} "
        raise ValueError(f"{label}version is outside the validated range")


def _agent_profile(agent: dict[str, Any], profile_root: Path, *, live: bool) -> Path:
    if live:
        return Path(agent["live_profile"]).expanduser().resolve(strict=False)
    suffix = agent.get("host2_profile", agent["id"])
    return (profile_root / suffix).resolve(strict=False)


def _agent_env(agent: dict[str, Any], profile: Path, *, live: bool) -> dict[str, str]:
    if live:
        return {}
    return {key: str(value).format(profile=str(profile)) for key, value in agent.get("env", {}).items()}


def _login_instruction(
    agent: dict[str, Any],
    profile: Path,
    *,
    live: bool,
    resolved_binary: str | None = None,
) -> str:
    binary = resolved_binary or agent["auth_status"][0]
    command = [binary, "auth", "login"]
    if agent["id"] == "codex":
        command = [binary, "login"]
    assignments = " ".join(
        f"{key}={shlex.quote(value)}"
        for key, value in _agent_env(agent, profile, live=live).items()
    )
    return " ".join(part for part in (assignments, shlex.join(command)) if part)


def setup_host2_credentials(
    spec: dict[str, Any],
    host2: Path,
    profile_root: Path,
    resolved_binaries: dict[str, str],
    spawn: Callable[[list[str], Path, dict[str, str]], Any],
    scanner: _CredentialScanner,
    child_outputs: list[bytes],
    ambient_snapshots: dict[str, SourceIdentity],
) -> dict[str, dict[str, str]]:
    home = host2 / "home"
    home.mkdir(parents=True, exist_ok=True)
    contexts: list[tuple[dict[str, Any], Path, dict[str, str]]] = []
    for agent in spec["agents"]:
        profile = _agent_profile(agent, profile_root, live=False)
        profile.mkdir(parents=True, exist_ok=True)
        env = _agent_env(agent, profile, live=False)
        env["HOME"] = str(home)
        contexts.append((agent, profile, env))

    _version_gate_agents(contexts, resolved_binaries, host2, spawn, "host2")

    claude = next((item for item in contexts if item[0]["id"] == "claude-code"), None)
    codex = next((item for item in contexts if item[0]["id"] == "codex"), None)
    if claude is None or codex is None:
        raise ValueError("host2 credential unavailable: claude-code")

    claude_result = materialize_keychain_credential(
        CLAUDE_KEYCHAIN_SERVICE,
        getpass.getuser(),
        claude[1] / ".credentials.json",
        max_bytes=CREDENTIAL_MAX_BYTES,
        shape_ok=claude_shape_ok,
    )
    if claude_result.status is not CredentialStatus.OK or claude_result.dest is None:
        raise ValueError("host2 credential unavailable: claude-code")
    try:
        raw = _read_credential_destination_nofollow(claude_result.dest)
        _seed_credential_scanner(scanner, raw, "claude-code")
    except (OSError, ValueError, TypeError):
        raise ValueError("host2 credential unavailable: claude-code") from None

    codex_result = materialize_file_credential(
        Path("~/.codex/auth.json").expanduser(),
        codex[1] / "auth.json",
        max_bytes=CREDENTIAL_MAX_BYTES,
        shape_ok=codex_shape_ok,
    )
    if (
        codex_result.status is not CredentialStatus.OK
        or codex_result.dest is None
        or codex_result.identity is None
    ):
        raise ValueError("host2 credential unavailable: codex")
    try:
        raw = _read_credential_destination_nofollow(codex_result.dest)
        _seed_credential_scanner(scanner, raw, "codex")
    except (OSError, ValueError, TypeError):
        raise ValueError("host2 credential unavailable: codex") from None
    ambient_snapshots["codex-auth.json"] = codex_result.identity
    try:
        if _credential_path_exists_nofollow(codex[1] / "config.toml"):
            raise ValueError("credential destination unavailable")
    except (OSError, ValueError, TypeError):
        raise ValueError("host2 credential unavailable: codex") from None
    capture_spawn = _spawn_with_capture(spawn, child_outputs)

    auth_failures: list[str] = []
    for agent, _, env in contexts:
        command = _rewrite_agent_command(
            agent["auth_status"], resolved_binaries[agent["id"]]
        )
        try:
            auth_ok = capture_spawn(command, host2, env).returncode == 0
        except Exception:
            auth_ok = False
        if not auth_ok:
            auth_failures.append(agent["id"])
    if auth_failures:
        raise ValueError("host2 credential unavailable: " + ", ".join(auth_failures))

    claude = next((item for item in contexts if item[0]["id"] == "claude-code"), None)
    if claude is None:
        raise ValueError("Claude liveness ping requires a claude-code agent")
    liveness = _spawn_retry_with(
        _rewrite_agent_command(
            claude[0]["liveness_command"], resolved_binaries[claude[0]["id"]]
        ),
        host2, claude[2], capture_spawn,
        lambda result: result.returncode == 0 and len(result.stdout.split()) == 1,
    )
    if liveness.returncode != 0 or len(liveness.stdout.split()) != 1:
        raise ValueError("Claude liveness ping did not return exactly one token")
    return {agent["id"]: env for agent, _, env in contexts}


def _session_id_from_path(agent_id: str, path: Path) -> str:
    if agent_id == "codex":
        candidate = path.stem[-36:]
    else:
        candidate = path.stem
    try:
        canonical = str(uuid.UUID(candidate))
    except ValueError as exc:
        raise ValueError("owned transcript filename did not contain a session UUID") from exc
    if canonical != candidate:
        raise ValueError("owned transcript filename did not contain a session UUID")
    return candidate


def _capture_path_proof(
    agent_id: str,
    path: Path,
    live_profile: Path,
    seed_workspace: Path,
) -> bool:
    try:
        _session_id_from_path(agent_id, path)
    except ValueError:
        return False
    if agent_id == "claude-code":
        expected = live_profile / "projects" / _project_key(seed_workspace)
        return path.parent == expected
    if agent_id == "codex":
        return path.name.startswith("rollout-")
    return False


def materialize_run_tokens(spec: dict[str, Any]) -> dict[str, Any]:
    agents = [
        {
            **agent,
            "run_token": f"{agent['run_token_prefix']}_{secrets.token_hex(32)}",
        }
        for agent in spec["agents"]
    ]
    return {**spec, "agents": agents}


def _bounded_string(value: object, fallback: str) -> str:
    return value if isinstance(value, str) and value else fallback


def _result(
    spec: object,
    status: Status,
    detail: str,
    warnings: list[str] | None = None,
) -> ScenarioResult:
    raw_id = spec.get("id") if isinstance(spec, dict) else None
    spec_id = _bounded_string(raw_id, "e3-invalid-spec")
    return ScenarioResult(
        id=spec_id,
        tier="E3",
        status=status,
        classes=[E3_CLASS] if status is Status.PASS else [],
        detail=detail,
        warnings=list(warnings or []),
    )


def _biv_envelope_outcome(result: object, verb: str) -> _BivOutcome:
    rc = result.returncode
    excerpt = (result.stdout or "").strip()[:500] or (result.stderr or "").strip()
    try:
        envelope = json.loads(result.stdout)
    except (json.JSONDecodeError, TypeError):
        return _BivOutcome(
            False,
            [],
            f"{verb} failed (exit {rc}, unparseable envelope): {excerpt}",
            None,
        )
    if not isinstance(envelope, dict):
        return _BivOutcome(
            False,
            [],
            f"{verb} failed (exit {rc}, envelope not an object): {excerpt}",
            None,
        )
    ok = envelope.get("ok")
    if not isinstance(ok, bool):
        return _BivOutcome(
            False,
            [],
            f"{verb} failed (envelope 'ok' not a bool: {ok!r})",
            envelope,
        )
    envelope_exit = envelope.get("exit_code")
    if type(envelope_exit) is not int or envelope_exit != rc:
        return _BivOutcome(
            False,
            [],
            f"{verb} failed (envelope exit_code {envelope_exit!r} "
            f"not int==process exit {rc})",
            envelope,
        )
    if ok:
        if rc not in (0, 2) or envelope.get("error") is not None:
            return _BivOutcome(
                False,
                [],
                f"{verb} exit-contract violation: ok:true but exit={rc} or error present",
                envelope,
            )
        raw_warnings = envelope.get("warnings")
        if not isinstance(raw_warnings, list):
            return _BivOutcome(
                False,
                [],
                f"{verb} failed (warnings not a list: {raw_warnings!r})",
                envelope,
            )
        warnings: list[str] = []
        for warning in raw_warnings:
            kind = warning.get("kind") if isinstance(warning, dict) else None
            if not isinstance(kind, str) or not kind:
                return _BivOutcome(
                    False,
                    [],
                    f"{verb} failed (malformed warning row: {warning!r})",
                    envelope,
                )
            path = warning.get("path")
            if path is not None and not isinstance(path, str):
                return _BivOutcome(
                    False,
                    [],
                    f"{verb} failed (malformed warning path: {path!r})",
                    envelope,
                )
            warnings.append(f"{kind} ({path})" if path else kind)
        return _BivOutcome(True, warnings, "", envelope)
    error = envelope.get("error")
    detail = json.dumps(error, sort_keys=True) if error is not None else excerpt
    return _BivOutcome(False, [], f"{verb} failed: {detail}", envelope)


def _open_result_outcome(
    envelope: dict[str, Any], requested_output_dir: Path
) -> _OpenResultOutcome:
    result = envelope.get("result")
    if not isinstance(result, dict):
        return _OpenResultOutcome(
            False,
            "",
            [],
            "open result malformed: result is not an object",
        )
    output_dir = result.get("output_dir")
    if not isinstance(output_dir, str) or not output_dir:
        return _OpenResultOutcome(
            False,
            "",
            [],
            "open result malformed: output_dir must be a non-empty string",
        )
    output_path = Path(output_dir)
    if not output_path.is_absolute():
        return _OpenResultOutcome(
            False,
            "",
            [],
            "open result malformed: output_dir must be an absolute path",
        )
    matches_requested = output_path == requested_output_dir
    if not matches_requested:
        return _OpenResultOutcome(
            False,
            "",
            [],
            "open result malformed: output_dir does not match requested destination",
        )
    sessions = result.get("sessions")
    if not isinstance(sessions, dict):
        return _OpenResultOutcome(
            False,
            "",
            [],
            "open result malformed: sessions is not an object",
        )
    groups = sessions.get("agents")
    if not isinstance(groups, list):
        return _OpenResultOutcome(
            False,
            "",
            [],
            "open result malformed: sessions.agents is not a list",
        )
    for group_index, group in enumerate(groups):
        group_member = f"sessions.agents[{group_index}]"
        if not isinstance(group, dict):
            return _OpenResultOutcome(
                False,
                "",
                [],
                f"open result malformed: {group_member} is not an object",
            )
        agent_id = group.get("agent")
        if not isinstance(agent_id, str) or not agent_id:
            return _OpenResultOutcome(
                False,
                "",
                [],
                f"open result malformed: {group_member}.agent must be a non-empty string",
            )
        rows = group.get("sessions")
        if not isinstance(rows, list):
            return _OpenResultOutcome(
                False,
                "",
                [],
                f"open result malformed: {group_member}.sessions is not a list",
            )
        for row_index, row in enumerate(rows):
            row_member = f"{group_member}.sessions[{row_index}]"
            if not isinstance(row, dict):
                return _OpenResultOutcome(
                    False,
                    "",
                    [],
                    f"open result malformed: {row_member} is not an object",
                )
            outcome = row.get("outcome")
            if not isinstance(outcome, str) or not outcome:
                return _OpenResultOutcome(
                    False,
                    "",
                    [],
                    f"open result malformed: {row_member}.outcome must be a non-empty string",
                )
            if outcome == "installed":
                installed_id = row.get("installed_session_id")
                if not isinstance(installed_id, str) or not installed_id:
                    return _OpenResultOutcome(
                        False,
                        "",
                        [],
                        f"open result malformed: {row_member}.installed_session_id "
                        "must be a non-empty string",
                    )
    return _OpenResultOutcome(True, output_dir, groups, "")


def _is_string_list(value: object, *, non_empty: bool = True) -> bool:
    return (
        isinstance(value, list)
        and (bool(value) or not non_empty)
        and all(isinstance(item, str) and item for item in value)
    )


def _c1_scan_directory(
    descriptor: int,
    label: str,
) -> list[str]:
    failures: list[str] = []
    try:
        with os.scandir(descriptor) as entries:
            for entry in entries:
                entry_label = f"{label}/{entry.name}"
                try:
                    status = entry.stat(follow_symlinks=False)
                except (OSError, ValueError, RuntimeError) as exc:
                    failures.append(f"{entry_label}: cannot stat: {exc}")
                    continue
                if stat.S_ISREG(status.st_mode):
                    failures.append(f"{entry_label}: recorded regular file")
                    continue
                if not stat.S_ISDIR(status.st_mode):
                    failures.append(f"{entry_label}: nonregular session entry")
                    continue
                try:
                    child = _open_verified_directory(
                        descriptor,
                        entry.name,
                        status,
                        entry_label,
                    )
                except (OSError, ValueError, RuntimeError) as exc:
                    failures.append(f"{entry_label}: {exc}")
                    continue
                try:
                    failures.extend(_c1_scan_directory(child, entry_label))
                finally:
                    os.close(child)
                try:
                    _verify_entry_unchanged(
                        descriptor,
                        entry.name,
                        status,
                        entry_label,
                    )
                except (OSError, ValueError, RuntimeError) as exc:
                    failures.append(f"{entry_label}: {exc}")
    except (OSError, ValueError, RuntimeError) as exc:
        failures.append(f"{label}: cannot traverse: {exc}")
    return failures


def _c1_scan_session_path(
    path: Path,
    label: str,
    *,
    allow_empty_file: bool,
) -> list[str]:
    try:
        opened_parent = _open_parent_directory_nofollow(path)
    except (OSError, ValueError, RuntimeError) as exc:
        return [f"{label}: cannot traverse: {exc}"]
    if opened_parent is None:
        return []
    parent_descriptor = opened_parent.descriptor
    name = opened_parent.name

    def parent_failures() -> list[str]:
        try:
            _verify_parent_unchanged(opened_parent, label)
        except (OSError, ValueError, RuntimeError) as exc:
            return [f"{label}: {exc}"]
        return []

    try:
        try:
            status = _entry_status(parent_descriptor, name)
        except (OSError, ValueError, RuntimeError) as exc:
            return [f"{label}: cannot stat: {exc}"]
        if status is None:
            return parent_failures()
        if stat.S_ISREG(status.st_mode):
            if not allow_empty_file or status.st_size != 0:
                return [
                    f"{label}: recorded regular file at {path}",
                    *parent_failures(),
                ]
            try:
                content = _read_regular_file_nofollow(
                    parent_descriptor,
                    name,
                    status,
                    label,
                )
            except (OSError, ValueError, RuntimeError) as exc:
                return [f"{label}: {exc}"]
            if content:
                return [
                    f"{label}: session index non-empty at {path}",
                    *parent_failures(),
                ]
            return parent_failures()
        if not stat.S_ISDIR(status.st_mode):
            return [
                f"{label}: nonregular session entry at {path}",
                *parent_failures(),
            ]
        try:
            descriptor = _open_verified_directory(
                parent_descriptor,
                name,
                status,
                label,
            )
        except (OSError, ValueError, RuntimeError) as exc:
            return [f"{label}: {exc}"]
        try:
            failures = _c1_scan_directory(descriptor, label)
        finally:
            os.close(descriptor)
        try:
            _verify_entry_unchanged(parent_descriptor, name, status, label)
        except (OSError, ValueError, RuntimeError) as exc:
            failures.append(f"{label}: {exc}")
        failures.extend(parent_failures())
        return failures
    finally:
        _close_nofollow_parent(opened_parent)


def _c1_zero_session_failures(profile_root: Path, spec: dict[str, Any]) -> list[str]:
    failures: list[str] = []
    for agent in spec.get("agents", []):
        agent_id = agent.get("id", "agent")
        suffix = agent.get("host2_profile", agent_id)
        store = Path(profile_root) / suffix
        for location in SESSION_LOCATIONS.get(agent_id, ()):
            failures.extend(
                _c1_scan_session_path(
                    store / location,
                    f"{agent_id} host2 session path {location}",
                    allow_empty_file=location == "session_index.jsonl",
                )
            )
    return failures


def _extract_source_region(path: Path, anchor: str) -> str:
    text = path.read_text(encoding="utf-8")
    first = text.find(anchor)
    if first < 0:
        raise ValueError(f"drift anchor missing: {anchor!r} in {path.name}")
    if text.find(anchor, first + 1) >= 0:
        raise ValueError(f"drift anchor not unique: {anchor!r} in {path.name}")
    try:
        brace = text.index("{", first)
    except ValueError as exc:
        raise ValueError(f"drift anchor unbalanced: {anchor!r} in {path.name}") from exc
    depth = 0
    for index in range(brace, len(text)):
        if text[index] == "{":
            depth += 1
        elif text[index] == "}":
            depth -= 1
            if depth == 0:
                return text[first : index + 1]
            if depth < 0:
                break
    raise ValueError(f"drift anchor unbalanced: {anchor!r} in {path.name}")


def _c1_default_repo_root() -> Path:
    return Path(__file__).resolve().parents[2]


def _c1_drift_tripwire_failures(repo_root: Path | None = None) -> list[str]:
    root = Path(repo_root) if repo_root is not None else _c1_default_repo_root()
    failures: list[str] = []
    for key, (relative, anchor, pinned) in _ADAPTER_SOURCE_ANCHORS.items():
        try:
            region = _extract_source_region(root / relative, anchor)
            digest = hashlib.sha256(region.encode("utf-8")).hexdigest()
        except (OSError, UnicodeError, ValueError, RuntimeError) as exc:
            failures.append(f"C1 drift tripwire RED: {key}: {exc}")
            continue
        if digest != pinned:
            failures.append(
                f"C1 drift tripwire RED: adapter session-location source changed ({key})"
            )
    return failures


def _validate_spec(spec: object) -> list[str]:
    failures: list[str] = []
    if not isinstance(spec, dict):
        return ["scenario must be a JSON object"]

    def require_string(mapping: dict[str, Any], field: str, label: str) -> bool:
        value = mapping.get(field)
        if not isinstance(value, str) or not value:
            failures.append(f"{label} must be a non-empty string")
            return False
        return True

    def optional_string(mapping: dict[str, Any], field: str, label: str) -> bool:
        if field not in mapping:
            return True
        return require_string(mapping, field, label)

    def optional_string_list(mapping: dict[str, Any], field: str, label: str) -> bool:
        if field not in mapping:
            return True
        value = mapping[field]
        if not _is_string_list(value):
            failures.append(f"{label} must be a non-empty list of non-empty strings")
            return False
        return True

    require_string(spec, "id", "scenario id")
    if spec.get("tier") != "E3":
        failures.append("scenario tier must be E3")
    for field in (
        "checkpoint_count",
        "checkpoint_prompt",
        "oauth_checkpoint",
        "pause_text",
    ):
        if field in spec:
            failures.append(f"{field} must not be declared (run is non-interactive)")
    optional_string(spec, "workspace_name", "workspace_name")
    optional_string(spec, "host2_profile_root", "host2_profile_root")
    optional_string_list(spec, "live_store_roots", "live_store_roots")
    optional_string_list(spec, "forbidden_bivpak_state", "forbidden_bivpak_state")
    if not _is_string_list(spec.get("seed_turns")):
        failures.append("seed_turns must be a non-empty list of non-empty strings")
    require_string(spec, "resume_probe", "resume_probe")

    agents = spec.get("agents")
    if (
        not isinstance(agents, list)
        or len(agents) != 2
        or not all(isinstance(agent, dict) for agent in agents)
    ):
        failures.append("scenario must declare two agents")
    else:
        required_agent_fields = (
            "id", "live_profile", "auth_status", "version_command",
            "validated_version_prefixes", "seed_start_command", "seed_continue_command",
            "seed_retry_resume_command", "ownership_glob", "run_token_prefix", "resume_command",
            "cheapest_model",
        )
        for agent in agents:
            agent_id = _bounded_string(agent.get("id"), "agent")
            for field in required_agent_fields:
                if field in (
                    "id", "live_profile", "ownership_glob", "run_token_prefix", "cheapest_model",
                ):
                    require_string(agent, field, f"agent {field}")
                elif not _is_string_list(agent.get(field)):
                    failures.append(f"agent {field} must be a non-empty list of non-empty strings")
            if not _is_prefix_list(agent.get("validated_version_prefixes")):
                failures.append(
                    f"{agent_id} validated_version_prefixes must be "
                    "a non-empty list of non-empty strings"
                )
            optional_string(agent, "host2_profile", "agent host2_profile")
            if "env" in agent and (
                not isinstance(agent["env"], dict)
                or not all(isinstance(key, str) and isinstance(value, str) for key, value in agent["env"].items())
            ):
                failures.append("agent env must be a mapping of strings to strings")
            if "run_token" in agent:
                failures.append("scenario must not contain a static run_token")
            for field in ("seed_start_command", "seed_retry_resume_command", "seed_continue_command"):
                command = agent.get(field)
                if _is_string_list(command) and not any("{run_token}" in part for part in command):
                    failures.append(f"{agent_id} {field} missing runtime run-token placeholder")
            if agent.get("id") == "claude-code":
                if not _is_string_list(agent.get("liveness_command")):
                    failures.append("agent liveness_command must be a non-empty list of non-empty strings")
                elif "--no-session-persistence" not in agent["liveness_command"]:
                    failures.append(
                        "claude liveness_command must include --no-session-persistence"
                    )
                if agent.get("resume_mutation") != CLAUDE_RESUME_MUTATION:
                    failures.append("Claude resume mutation must match the pinned shape")
            if agent.get("id") == "codex" and agent.get("resume_shape") != CODEX_RESUME_SHAPE:
                failures.append("Codex resume shape must match the pinned shape")
            model_fields = [
                "seed_start_command", "seed_retry_resume_command",
                "seed_continue_command", "resume_command",
            ]
            if agent.get("id") == "claude-code":
                model_fields.append("liveness_command")
            model = agent.get("cheapest_model")
            for field in model_fields:
                command = agent.get(field)
                if not _is_string_list(command):
                    continue
                if "--model" not in command:
                    failures.append(f"{agent_id} {field} missing cheapest-model flag")
                    continue
                index = command.index("--model")
                if index + 1 >= len(command) or command[index + 1] != model:
                    failures.append(f"{agent_id} {field} cheapest-model mismatch")
    sentinels = spec.get("credential_scan_sentinels")
    if not _is_string_list(sentinels):
        failures.append("scenario missing non-empty credential_scan_sentinels")
    elif any(DOTENV_SAFE_SENTINEL.fullmatch(value) is None for value in sentinels):
        failures.append("credential_scan_sentinels values must be dotenv-safe")
    return failures


def _stability_failure(label: str, path: Path) -> str | None:
    for ancestor in [path, *path.parents]:
        try:
            os.stat(ancestor)
        except FileNotFoundError:
            continue
        except OSError as exc:
            if exc.errno == errno.ELOOP:
                return f"{label}: symlink cycle at {ancestor}"
            return f"{label}: unstatable ({exc.strerror}) at {ancestor}"
    resolved = path.resolve()
    if resolved != path:
        return f"{label} must be realpath-stable; {path} resolves to {resolved}"
    return None


def _canonical_path_text(path: Path) -> str:
    text = unicodedata.normalize("NFC", str(path))
    data_prefix = "/System/Volumes/Data"
    while text == data_prefix or text.startswith(data_prefix + "/"):
        text = text[len(data_prefix):] or "/"
    return text


def _canonical_spelling_failure(label: str, path: Path) -> str | None:
    canonical = _canonical_path_text(path)
    if str(path) == canonical:
        return None
    return (
        f"{label} must use its canonical spelling ({canonical}); "
        f"firmlink-aliased or non-NFC spellings are refused ({path})"
    )


def _temp_root_failure(label: str, path: Path) -> str | None:
    path_text = str(path)
    data_prefix = "/System/Volumes/Data"
    has_data_prefix = (
        path_text == data_prefix or path_text.startswith(data_prefix + "/")
    )
    resolved = Path(_canonical_path_text(path.resolve()))
    host_temp_root = Path(_canonical_path_text(Path("/tmp").resolve()))
    temp_roots = {host_temp_root}
    if has_data_prefix or host_temp_root == Path("/private/tmp"):
        temp_roots.add(Path("/private/tmp"))
    for temp_root in sorted(temp_roots, key=str):
        try:
            resolved.relative_to(temp_root)
        except ValueError:
            continue
        return f"{label}: resolved path must not be under {temp_root} ({resolved})"
    return None


def _root_failure(
    label: str,
    value: object,
) -> str | None:
    if not isinstance(value, (str, Path)):
        return f"{label} must be a path string; got {value!r}"
    try:
        path = Path(value).expanduser()
        failure = _stability_failure(label, path)
        if failure is not None:
            return failure
        failure = _canonical_spelling_failure(label, path)
        if failure is not None:
            return failure
        return _temp_root_failure(label, path)
    except (OSError, ValueError, RuntimeError) as exc:
        return f"{label} is not a usable path: {type(exc).__name__}: {exc}"


def _child_failure(label: str, root: Path, value: object) -> str | None:
    """P-CHILD. Containment is proved by requiring resolve(child) == child."""
    if (
        not isinstance(value, str)
        or not value
        or value in (".", "..")
        or Path(value).is_absolute()
    ):
        return f"{label} must be a non-empty relative name; got {value!r}"
    if value.startswith("~"):
        return f"{label}: tilde spellings are refused ({value})"
    try:
        child = root / value
        return _stability_failure(label, child)
    except (OSError, ValueError, RuntimeError) as exc:
        return f"{label} is not a usable path: {type(exc).__name__}: {exc}"


def _path_field_failures(spec: object, scratch: Path) -> list[str]:
    """Refuse unstable roots and children before probe or any runner write."""
    failures: list[str] = []
    try:
        failure = _stability_failure("scratch", scratch)
        if failure is None:
            failure = _canonical_spelling_failure("scratch", scratch)
        if failure is None:
            failure = _temp_root_failure("scratch", scratch)
    except (OSError, ValueError, RuntimeError) as exc:
        failure = f"scratch is not a usable path: {type(exc).__name__}: {exc}"
    if failure is not None:
        failures.append(failure)
    if not isinstance(spec, dict):
        return failures
    profile_root = scratch / "host2-profile"
    if "host2_profile_root" in spec:
        value = spec["host2_profile_root"]
        failure = _child_failure("host2_profile_root", scratch, value)
        if failure is not None:
            failures.append(failure)
        elif isinstance(value, str):
            profile_root = scratch / value
    values = spec.get("live_store_roots", [])
    if isinstance(values, list):
        for value in values:
            failure = _root_failure("live_store_roots", value)
            if failure is not None:
                failures.append(failure)
    else:
        failures.append("live_store_roots must be a list")
    agents = spec.get("agents", [])
    if isinstance(agents, list):
        for agent in agents:
            if not isinstance(agent, dict):
                failures.append("agents entries must be objects")
                continue
            failure = _root_failure(
                "live_profile",
                agent.get("live_profile", ""),
            )
            if failure is not None:
                failures.append(failure)
            if "host2_profile" in agent:
                failure = _child_failure("host2_profile", profile_root, agent["host2_profile"])
                if failure is not None:
                    failures.append(failure)
    else:
        failures.append("agents must be a list")
    if "workspace_name" in spec:
        failure = _child_failure("workspace_name", scratch / "seed-ws", spec["workspace_name"])
        if failure is not None:
            failures.append(failure)
    values = spec.get("forbidden_bivpak_state", [])
    if isinstance(values, list):
        for value in values:
            failure = _child_failure("forbidden_bivpak_state", scratch, value)
            if failure is not None:
                failures.append(failure)
    else:
        failures.append("forbidden_bivpak_state must be a list")
    return failures


def _scratch_overlap_failures(spec: dict[str, Any], scratch: Path) -> list[str]:
    scratch = scratch.resolve()
    live_roots = [
        ("live_store_roots", Path(value).expanduser().resolve())
        for value in spec.get("live_store_roots", [])
    ]
    live_roots.extend(
        ("live_profile", Path(agent["live_profile"]).expanduser().resolve())
        for agent in spec["agents"]
    )
    return [
        f"scratch overlaps {label}: {scratch} and {live_root}"
        for label, live_root in live_roots
        if (
            scratch == live_root
            or scratch in live_root.parents
            or live_root in scratch.parents
        )
    ]


def _scratch_temp_root_overlap_failures(scratch: Path) -> list[str]:
    scratch = Path(_canonical_path_text(scratch.resolve()))
    ambient_temp_root = os.environ.get("TMPDIR") or "/tmp"
    temp_roots = {
        Path(_canonical_path_text(Path(ambient_temp_root).resolve())),
        Path(_canonical_path_text(Path("/private/var/tmp").resolve())),
    }
    return [
        f"scratch overlaps temporary root: {scratch} contains {temp_root}"
        for temp_root in sorted(temp_roots, key=str)
        if scratch == temp_root or scratch in temp_root.parents
    ]


_ALIAS_PREFIX_PAIRS = (
    ("/private/var/", "/var/"),
    ("/private/tmp/", "/tmp/"),
    ("/private/etc/", "/etc/"),
    ("/System/Volumes/Data/", "/"),
)


def _alias_spellings(root: Path) -> list[str]:
    """Return alternate spellings of a run root under Darwin aliases."""
    text = _canonical_path_text(root)
    spellings: list[str] = []
    for real, alias in _ALIAS_PREFIX_PAIRS:
        real_root = real.rstrip("/")
        alias_root = alias.rstrip("/") or "/"
        if text == real_root:
            spellings.append(alias_root)
        elif text.startswith(real):
            spellings.append(alias + text[len(real):])
        elif text == alias_root:
            spellings.append(real_root)
        elif text.startswith(alias):
            spellings.append(real + text[len(alias):])
    return spellings


def _structural_alias_hit(record: Any, roots: list[str]) -> str | None:
    stack = [record]
    while stack:
        value = stack.pop()
        if isinstance(value, str):
            candidate = posixpath.normpath(unicodedata.normalize("NFC", value))
            if candidate.startswith("//"):
                candidate = candidate[1:]
            hit = next(
                (
                    root
                    for root in roots
                    if candidate == root or candidate.startswith(root + "/")
                ),
                None,
            )
            if hit is not None:
                return hit
        elif isinstance(value, dict):
            stack.extend(reversed(tuple(value.values())))
        elif isinstance(value, list):
            stack.extend(reversed(value))
    return None


def _negative_control_failures(
    owned_paths: list[Path], scratch: Path
) -> list[str]:
    """Reject aliased root values and descendants in owned JSONL transcripts."""
    roots = _alias_spellings(scratch)
    failures: list[str] = []
    for path in owned_paths:
        text = path.read_text(encoding="utf-8-sig", errors="replace")
        for line in text.split("\n"):
            try:
                record = json.loads(line)
            except (ValueError, RecursionError):
                continue
            hit = _structural_alias_hit(record, roots)
            if hit is not None:
                failures.append(
                    f"negative-control: {path} renders {hit} - an aliased "
                    "spelling of this run's scratch tree; the scratch guard did not hold "
                    "and this run's evidence is void"
                )
                break
    return failures


def ambient_store_selector_failures(spec: dict[str, Any]) -> list[str]:
    failures: list[str] = []
    for agent in spec.get("agents", []):
        agent_id = agent.get("id")
        selectors = LIVE_STORE_SELECTORS.get(agent_id)
        if selectors is None:
            failures.append(
                f"no live store-selector policy for agent {agent_id!r}; "
                "the E3 live leg cannot certify its effective store"
            )
            continue
        for key in selectors:
            if os.environ.get(key):
                failures.append(
                    f"ambient store selector {key} is set for {agent_id}; the E3 live leg "
                    f"must run under the sealed default store - unset {key} before the run"
                )
    return failures


def _clear_precheck_probe_artifacts(scratch: Path) -> None:
    for name in (".bivharness-link-probe", ".bivharness-mode-probe"):
        try:
            (scratch / name).unlink()
        except FileNotFoundError:
            continue
        except OSError as exc:
            raise ValueError("pre-run probe cleanup failed") from exc


def run_e3(
    spec_path: Path,
    biv: Path,
    scratch: Path,
    *,
    dry_run: bool = False,
) -> ScenarioResult:
    try:
        spec = json.loads(spec_path.read_text(encoding="utf-8"))
    except (OSError, UnicodeDecodeError, json.JSONDecodeError) as exc:
        return _result({}, Status.INVALID, f"scenario unreadable: {exc}")

    failures = _validate_spec(spec)
    if failures:
        return _result(spec, Status.INVALID, "\n".join(failures))
    try:
        if not isinstance(scratch, (str, Path)):
            return _result(spec, Status.INVALID, "scratch must be a str or Path")
        scratch = Path(scratch)
        if scratch.is_symlink():
            return _result(spec, Status.INVALID, "scratch must not be a symlink")
    except (OSError, ValueError, RuntimeError) as exc:
        return _result(spec, Status.INVALID, f"scratch is unusable: {exc}")
    failures = _path_field_failures(spec, scratch)
    failures.extend(f"credential-env:{name}" for name in rejected_credential_names(os.environ))
    failures.extend(ambient_store_selector_failures(spec))
    if failures:
        return _result(spec, Status.INVALID, "\n".join(failures))

    try:
        failures.extend(_scratch_temp_root_overlap_failures(scratch))
        failures.extend(_scratch_overlap_failures(spec, scratch))
        if failures:
            return _result(spec, Status.INVALID, "\n".join(failures))
        profile_root = Path(spec.get("host2_profile_root", scratch / "host2-profile"))
        if not profile_root.is_absolute():
            profile_root = scratch / profile_root
        live_stores = [Path(value).expanduser() for value in spec.get("live_store_roots", [])]
        failures.extend(probe(scratch))
        failures.extend(profile_root_failures(profile_root, live_stores))
    except (OSError, ValueError, RuntimeError) as exc:
        return _result(
            spec,
            Status.INVALID,
            f"pre-run filesystem check failed: {type(exc).__name__}: {exc}",
        )
    if failures:
        return _result(spec, Status.INVALID, "\n".join(failures))
    try:
        _clear_precheck_probe_artifacts(scratch)
    except (OSError, ValueError, RuntimeError) as exc:
        return _result(spec, Status.INVALID, f"pre-run filesystem check failed: {exc}")

    pin_env()
    if dry_run:
        return _result(spec, Status.PASS, "dry-run: structural, isolation, and credential guards passed")

    run_warnings: list[str] = []

    def _run_result(status: Status, detail: str) -> ScenarioResult:
        return _result(spec, status, detail, warnings=list(run_warnings))

    owned_paths: list[Path] = []
    capture_candidates: list[Path] = []
    scanner: _CredentialScanner | None = None
    child_outputs: list[bytes] = []
    ambient_snapshots: dict[str, SourceIdentity] = {}
    seed_parent: Path | None = None
    host2: Path | None = None
    claude_dest: Path | None = None
    codex_dest: Path | None = None
    primary: ScenarioResult | None = None
    remove_targets = False

    # Live execution is intentionally explicit: this path owns real API calls. The
    # scenario supplies commands so CLI surface changes cannot silently alter the
    # safety predicates in this runner.
    try:
        seed_parent = scratch / "seed-ws"
        host2 = scratch / "host2"
        restored_dest = host2 / "work"
        claude_dest = profile_root / "claude-code" / ".credentials.json"
        codex_dest = profile_root / "codex" / "auth.json"
        host2_env: dict[str, str] = {}
        host2_agent_envs: dict[str, dict[str, str]] = {}
        scanner = _CredentialScanner()
        claude_dest = _agent_profile(
            next(agent for agent in spec["agents"] if agent["id"] == "claude-code"),
            profile_root,
            live=False,
        ) / ".credentials.json"
        codex_dest = _agent_profile(
            next(agent for agent in spec["agents"] if agent["id"] == "codex"),
            profile_root,
            live=False,
        ) / "auth.json"
        spec = materialize_run_tokens(spec)
        seed_ws = seed_parent / spec.get("workspace_name", "resume-e3")
        credential_sentinels = spec.get("credential_scan_sentinels", [])
        resolved_binaries = _resolve_agent_binaries(spec)
        if seed_parent.is_symlink() or seed_parent.exists() or seed_ws.is_symlink() or seed_ws.exists():
            raise ValueError("seed workspace must be fresh and contained by scratch")
        if host2.is_symlink() or host2.exists():
            raise ValueError("host2 workspace must be fresh and contained by scratch")
        remove_targets = True
        scratch.mkdir(parents=True, exist_ok=True)
        seed_parent.mkdir()
        seed_ws.mkdir()
        host2.mkdir()
        live_contexts: list[tuple[dict[str, Any], Path, dict[str, str]]] = []
        for agent in spec["agents"]:
            live_profile = _agent_profile(agent, profile_root, live=True)
            env = _agent_env(agent, live_profile, live=True)
            live_contexts.append((agent, live_profile, env))

        _version_gate_agents(live_contexts, resolved_binaries, seed_ws, _spawn)
        for agent, live_profile, env in live_contexts:
            auth = _spawn(
                _rewrite_agent_command(
                    agent["auth_status"], resolved_binaries[agent["id"]]
                ),
                seed_ws,
                env,
            )
            if auth.returncode != 0:
                instruction = _login_instruction(
                    agent,
                    live_profile,
                    live=True,
                    resolved_binary=resolved_binaries[agent["id"]],
                )
                raise _ScenarioExit(_run_result(
                    Status.INVALID,
                    f"{agent['id']} is not authenticated; run: {instruction}",
                ))
        for agent, live_profile, env in live_contexts:
            _seed_agent(
                agent, live_profile, seed_ws, spec, env, _spawn,
                capture_candidates, owned_paths,
                resolved_binary=resolved_binaries[agent["id"]],
            )

        negative_control = _negative_control_failures(owned_paths, scratch)
        if negative_control:
            raise _ScenarioExit(_run_result(Status.INVALID, "\n".join(negative_control)))

        credential_decoys = plant_credential_decoys(seed_ws, credential_sentinels)
        verify_credential_decoys(seed_ws, credential_decoys, credential_sentinels)
        before = {path: _hash(path) for path in owned_paths}
        packed = _spawn([str(biv), "pack", str(seed_ws), "--json"], scratch, {})
        pack_outcome = _biv_envelope_outcome(packed, "pack")
        if not pack_outcome.ok:
            raise _ScenarioExit(_run_result(Status.FAIL, pack_outcome.detail))
        run_warnings.extend(pack_outcome.warnings)
        if any(_hash(path) != digest for path, digest in before.items()):
            raise _ScenarioExit(_run_result(
                Status.INVALID,
                "pack mutated an owned live-store transcript",
            ))
        image = seed_ws.parent / f"{seed_ws.name}.bvpk"
        image_secret_hits = scan_image_secret_values(image, credential_sentinels)
        if image_secret_hits:
            raise ValueError("credential sentinel found in image: " + ", ".join(image_secret_hits))

        host2_agent_envs = setup_host2_credentials(
            spec,
            host2,
            profile_root,
            resolved_binaries,
            _spawn,
            scanner,
            child_outputs,
            ambient_snapshots,
        )
        capture_spawn = _spawn_with_capture(_spawn, child_outputs)
        for env in host2_agent_envs.values():
            host2_env.update(env)
        pre_open_stores = {
            agent["id"]: snapshot_store(_agent_profile(agent, profile_root, live=False))
            for agent in spec["agents"]
        }
        drift_failures = _c1_drift_tripwire_failures()
        if drift_failures:
            raise _ScenarioExit(_run_result(Status.INVALID, "\n".join(drift_failures)))
        zero_session_failures = _c1_zero_session_failures(profile_root, spec)
        if zero_session_failures:
            raise _ScenarioExit(_run_result(Status.INVALID, "\n".join(zero_session_failures)))

        # The remaining open/resume commands are deliberately data-driven and still
        # pass through _spawn, preserving the no-credential and isolated-profile gates.
        opened = capture_spawn([str(biv), "open", str(image), "--dest", str(restored_dest),
                                "--consent", "yes", "--json"], host2, host2_env)
        open_outcome = _biv_envelope_outcome(opened, "open")
        if not open_outcome.ok:
            raise _ScenarioExit(_run_result(Status.FAIL, open_outcome.detail))
        run_warnings.extend(open_outcome.warnings)
        envelope = open_outcome.envelope or {}
        result_outcome = _open_result_outcome(envelope, restored_dest)
        if not result_outcome.ok:
            raise _ScenarioExit(_run_result(Status.FAIL, result_outcome.detail))
        restored_workspace = Path(result_outcome.output_dir)
        if not _directory_topology_is_nofollow(restored_workspace):
            raise _ScenarioExit(_run_result(Status.FAIL, "open output workspace missing"))
        class_j = class_j_failures(
            seed_ws,
            restored_workspace,
            [restored_workspace / ".biv" / "agents",
             *[scratch / path for path in spec.get("forbidden_bivpak_state", [])]],
        )
        if class_j:
            raise _ScenarioExit(_run_result(Status.INVALID, ",".join(class_j)))
        groups = result_outcome.groups
        installed_rows: list[tuple[str, dict[str, Any]]] = []
        for group in groups:
            sessions = [row for row in group.get("sessions", []) if row.get("outcome") == "installed"]
            if len(sessions) != 1:
                raise _ScenarioExit(_run_result(
                    Status.FAIL,
                    f"open result malformed: agent {group['agent']!r} reported "
                    f"{len(sessions)} installed session rows, expected exactly 1",
                ))
            installed_rows.append((group["agent"], sessions[0]))
        installed_agents = sorted(group["agent"] for group in groups)
        expected_agents = sorted(agent["id"] for agent in spec["agents"])
        if installed_agents != expected_agents:
            raise _ScenarioExit(_run_result(
                Status.FAIL,
                "open result malformed: installed agents "
                f"{installed_agents!r} do not match spec {expected_agents!r}",
            ))
        installed = dict(installed_rows)

        installed_paths: dict[str, Path] = {}
        for agent in spec["agents"]:
            profile = _agent_profile(agent, profile_root, live=False)
            paths = assert_exact_install_delta(
                agent["id"], profile, restored_workspace, [installed[agent["id"]]],
                pre_open_stores[agent["id"]], snapshot_store(profile), spec["seed_turns"],
            )
            installed_paths[agent["id"]] = paths[0]
        installed_contents = {
            agent_id: path.read_bytes() for agent_id, path in installed_paths.items()
        }
        installed_hashes = {agent_id: _hash(path) for agent_id, path in installed_paths.items()}

        for agent in spec["agents"]:
            if _hash(installed_paths[agent["id"]]) != installed_hashes[agent["id"]]:
                raise _ScenarioExit(_run_result(
                    Status.INVALID,
                    f"{agent['id']} installed transcript changed before resume",
                ))
            row = installed[agent["id"]]
            session_id = row.get("installed_session_id")
            if not session_id:
                raise _ScenarioExit(_run_result(
                    Status.FAIL,
                    f"{agent['id']} installed id missing",
                ))
            command = _rewrite_agent_command(
                [part.format(id=session_id, probe=spec["resume_probe"])
                 for part in agent["resume_command"]],
                resolved_binaries[agent["id"]],
            )
            profile = _agent_profile(agent, profile_root, live=False)
            env = host2_agent_envs[agent["id"]]
            resumed = _spawn_retry_with(
                command, restored_workspace, env, capture_spawn,
                lambda result: result.returncode == 0 and bool(result.stdout.strip()),
            )
            if resumed.returncode != 0 or not resumed.stdout.strip():
                raise _ScenarioExit(_run_result(
                    Status.INVALID,
                    f"{agent['id']} resume did not return a reply",
                ))
            turns = [*spec["seed_turns"], spec["resume_probe"]]
            shape = agent["resume_mutation"] if agent["id"] == "claude-code" else agent["resume_shape"]
            assert_resume_containment(
                agent["id"], profile, restored_workspace, session_id,
                turns, spec["resume_probe"], shape,
                expected_transcript=installed_paths[agent["id"]],
                pre_resume_content=installed_contents[agent["id"]],
            )
        raise _ScenarioExit(_run_result(
            Status.PASS,
            "dual-agent resume and store containment passed",
        ))
    except _ScenarioExit as exit_result:
        primary = exit_result.result
    except BaseException as exc:
        try:
            scanner_active = scanner is not None and scanner.active
        except BaseException:
            scanner_active = True
        if scanner_active:
            detail = "post-materialization execution failed"
        else:
            try:
                detail = str(exc)
            except BaseException:
                detail = "post-dry-run execution failed"
        primary = _run_result(Status.INVALID, detail)
    finally:
        try:
            print(format_cleanup_report(capture_candidates, owned_paths))
        except BaseException:
            pass
    if (
        scanner is None
        or seed_parent is None
        or host2 is None
        or claude_dest is None
        or codex_dest is None
    ):
        return _minimal_sanitized_report_result()
    if primary is None:
        primary = _run_result(Status.INVALID, "post-materialization execution failed")
    return _scan_and_teardown(
        primary,
        scanner,
        scratch,
        child_outputs=child_outputs,
        ambient_snapshots=ambient_snapshots,
        claude_dest=claude_dest,
        codex_dest=codex_dest,
        profile_root=profile_root,
        host2=host2,
        seed_parent=seed_parent,
        remove_targets=remove_targets,
    )
