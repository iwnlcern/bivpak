import hashlib
import io
import json
import multiprocessing
import os
import re
import shutil
import socket
import stat
import sys
import tarfile
import tempfile
import time
import unicodedata
from pathlib import Path
from types import SimpleNamespace

import pytest
import zstandard

from bivharness import cli, e3, host2_credentials
from bivharness.e3 import (
    CLAUDE_RESUME_MUTATION,
    CODEX_RESUME_SHAPE,
    CREDENTIAL_ENV_NAMES,
    assert_exact_install_delta,
    assert_resume_containment,
    capture_inventory,
    class_j_failures,
    classify_capture,
    format_cleanup_report,
    ordered_turns_present,
    plant_credential_decoys,
    rejected_credential_names,
    scan_secret_values,
    scan_image_secret_values,
    select_owned_rollout,
    snapshot_store,
    verify_credential_decoys,
    version_in_validated_range,
)
from bivharness.precheck import profile_root_failures
from bivharness.report import Report, ScenarioResult, Status, serialize_report


CLAUDE_ACCESS_LEAF = "claude-access-leaf-7f6d1a"
CLAUDE_REFRESH_LEAF = "claude-refresh-leaf-2c8b4e"
CODEX_ACCESS_LEAF = "codex-access-leaf-9a3e5d"
CODEX_REFRESH_LEAF = "codex-refresh-leaf-4b7c2f"
CODEX_API_KEY_LEAF = "codex-api-key-leaf-8d1f6a"
ESCAPED_CREDENTIAL_LEAF = 'quote" backslash\\ newline\n tab\t snowman-\u2603'
ESCAPED_CREDENTIAL_JSON = json.dumps(ESCAPED_CREDENTIAL_LEAF)[1:-1]
ESCAPED_CREDENTIAL_OUTPUT = json.dumps(
    {"credential": ESCAPED_CREDENTIAL_LEAF},
    separators=(",", ":"),
)
NESTED_CREDENTIAL_LEAF = 'nested quote" slash\\ line\n tab\t globe-\u2603'
NESTED_CREDENTIAL_JSON = json.dumps(NESTED_CREDENTIAL_LEAF)[1:-1]
NESTED_CREDENTIAL_OUTPUT = json.dumps(
    {"event": {"items": [{"credential": NESTED_CREDENTIAL_LEAF}]}},
    separators=(",", ":"),
)
CONTROLLED_RUNTIME_SENTINEL = "bive3-sentinel-" + "e" * 64
CONTROLLED_SLASH_SENTINEL = "bive3-sentinel-" + "f" * 63 + "/"


def _assert_report_refused(result):
    assert result == ScenarioResult(
        id="e3-report-refused",
        tier="E3",
        status=Status.INVALID,
        classes=[],
        held_asserts=[],
        detail="report refused: result could not be sanitized",
        warnings=[],
    )


@pytest.fixture
def repo_root() -> Path:
    root = Path(__file__).resolve().parents[2]
    assert (root / "src/adapters/codex/install.cpp").is_file(), (
        f"repo_root mis-resolved: {root}"
    )
    assert (root / "harness/scenarios-e3/e3-dual-resume.json").is_file(), (
        f"repo_root mis-resolved: {root}"
    )
    return root


@pytest.fixture(autouse=True)
def _fake_run_e3_credential_materialization(monkeypatch):
    """Keep E3 orchestration tests offline while preserving Task 2 result semantics."""

    claude_bytes = json.dumps(
        {
            "claudeAiOauth": {
                "accessToken": CLAUDE_ACCESS_LEAF,
                "refreshToken": CLAUDE_REFRESH_LEAF,
            }
        },
        separators=(",", ":"),
    ).encode()
    codex_bytes = json.dumps(
        {
            "OPENAI_API_KEY": CODEX_API_KEY_LEAF,
            "tokens": {
                "access_token": CODEX_ACCESS_LEAF,
                "refresh_token": CODEX_REFRESH_LEAF,
                "escaped_token": ESCAPED_CREDENTIAL_LEAF,
            },
            "metadata": {
                "history": [{"credential": NESTED_CREDENTIAL_LEAF}],
            },
        },
        separators=(",", ":"),
    ).encode()
    identity = e3.SourceIdentity(1, 2, len(codex_bytes), "fixture-digest")

    def fake_keychain(_service, _account, dest, **_kwargs):
        path = Path(dest)
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(claude_bytes)
        path.chmod(0o600)
        return e3.CredentialResult(e3.CredentialStatus.OK, path)

    def fake_file(_source, dest, **_kwargs):
        path = Path(dest)
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(codex_bytes)
        path.chmod(0o600)
        return e3.CredentialResult(e3.CredentialStatus.OK, path, identity)

    monkeypatch.setattr(e3, "materialize_keychain_credential", fake_keychain)
    monkeypatch.setattr(e3, "materialize_file_credential", fake_file)
    monkeypatch.setattr(e3, "snapshot_identity", lambda *_args, **_kwargs: identity)


@pytest.fixture
def stable_test_root(tmp_path):
    root = (
        Path.home()
        / ".cache"
        / "bivharness-selftest"
        / f"{os.getpid()}-{tmp_path.name}"
    )
    shutil.rmtree(root, ignore_errors=True)
    root.mkdir(parents=True)
    assert root.is_absolute()
    assert root.resolve() == root
    for live_store in (Path.home() / ".claude", Path.home() / ".codex"):
        assert root != live_store
        assert live_store not in root.parents
    try:
        yield root
    finally:
        shutil.rmtree(root, ignore_errors=True)


PRODUCT_PREDICATES = {
    "codex": ("src/adapters/codex/install.cpp", "validated_codex_version"),
    "claude-code": (
        "src/adapters/claude_code/install.cpp",
        "validated_claude_version",
    ),
}

TEST_AGENT_BINARIES = {
    "claude-code": "/opt/bivharness-test/bin/claude",
    "codex": "/opt/bivharness-test/bin/codex",
}


@pytest.fixture(autouse=True)
def deterministic_agent_path(monkeypatch):
    binaries_by_executable = {
        "claude": TEST_AGENT_BINARIES["claude-code"],
        "codex": TEST_AGENT_BINARIES["codex"],
    }
    monkeypatch.setattr(e3.shutil, "which", binaries_by_executable.get)


def _product_prefixes(repo_root: Path, agent_id: str) -> list[str]:
    rel, function = PRODUCT_PREDICATES[agent_id]
    source = (repo_root / rel).read_text(encoding="utf-8")
    match = re.search(
        rf"bool\s+{function}\s*\([^)]*\)\s*\{{(.*?)\n\}}",
        source,
        re.S,
    )
    assert match, f"predicate {function} not found in {rel}"
    prefixes = re.findall(r'starts_with\("([^"]*)"\)', match.group(1))
    assert prefixes, f"{function} is no longer a starts_with prefix set"
    return prefixes


def _product_accepts_single_version(repo_root: Path, agent_id: str, version: str) -> bool:
    return any(version.startswith(prefix) for prefix in _product_prefixes(repo_root, agent_id))


def test_scenario_version_sets_mirror_the_product_exactly(repo_root):
    spec = json.loads(
        (repo_root / "harness/scenarios-e3/e3-dual-resume.json").read_text(
            encoding="utf-8"
        )
    )
    for agent in spec["agents"]:
        product = _product_prefixes(repo_root, agent["id"])
        assert agent["validated_version_prefixes"] == product, (
            f"{agent['id']}: scenario {agent['validated_version_prefixes']} != product "
            f"{product}. Mirror the product exactly."
        )
        in_range = f"{product[0]}0"
        out_of_range = "999.999.999"
        for authoritative in (in_range, out_of_range):
            output = f"{agent['id']} {authoritative}\n"
            assert version_in_validated_range(output, product) is (
                _product_accepts_single_version(
                    repo_root,
                    agent["id"],
                    authoritative,
                )
            )
        for output in (
            f"{agent['id']} {in_range}\nancillary {out_of_range}\n",
            f"ancillary {in_range}\n{agent['id']} {out_of_range}\n",
        ):
            assert not version_in_validated_range(output, product)


def _valid_two_agent_spec():
    """Return a two-agent E3 spec that passes validation once lists are supported."""
    codex = {
        "id": "codex",
        "live_profile": "~/.codex",
        "env": {},
        "auth_status": ["codex", "login", "status"],
        "version_command": ["codex", "--version"],
        "validated_version_prefixes": ["0.142.", "0.144."],
        "cheapest_model": "cheap",
        "seed_start_command": ["codex", "seed", "{run_token}", "--model", "cheap"],
        "seed_retry_resume_command": ["codex", "retry", "{run_token}", "--model", "cheap"],
        "seed_continue_command": ["codex", "continue", "{run_token}", "--model", "cheap"],
        "ownership_glob": "*.jsonl",
        "run_token_prefix": "token",
        "resume_command": ["codex", "resume", "--model", "cheap"],
        "resume_shape": CODEX_RESUME_SHAPE,
    }
    claude = {
        **codex,
        "id": "claude-code",
        "live_profile": "~/.claude",
        "auth_status": ["claude", "auth", "status"],
        "version_command": ["claude", "--version"],
        "validated_version_prefixes": ["2.1."],
        "seed_start_command": ["claude", "seed", "{run_token}", "--model", "cheap"],
        "seed_retry_resume_command": ["claude", "retry", "{run_token}", "--model", "cheap"],
        "seed_continue_command": ["claude", "continue", "{run_token}", "--model", "cheap"],
        "resume_command": ["claude", "resume", "--model", "cheap"],
        "liveness_command": [
            "claude", "--model", "cheap", "--no-session-persistence", "-p",
            "Reply with one token: OK",
        ],
        "resume_mutation": CLAUDE_RESUME_MUTATION,
    }
    claude.pop("resume_shape", None)
    return {
        "id": "cx-range",
        "tier": "E3",
        "seed_turns": ["one", "two"],
        "resume_probe": "probe",
        "credential_scan_sentinel_count": 1,
        "agents": [codex, claude],
    }


def test_resolve_agent_binaries_is_once_per_agent_and_requires_absolute_paths(monkeypatch):
    spec = _valid_two_agent_spec()
    paths = {"codex": "/opt/agents/codex", "claude": "/opt/agents/claude"}
    calls = []

    def fake_which(executable):
        calls.append(executable)
        return paths[executable]

    monkeypatch.setattr(e3.shutil, "which", fake_which)
    assert e3._resolve_agent_binaries(spec) == {
        "codex": paths["codex"],
        "claude-code": paths["claude"],
    }
    assert calls == ["codex", "claude"]

    for invalid in (None, "relative/claude"):
        monkeypatch.setattr(
            e3.shutil,
            "which",
            lambda executable, invalid=invalid: invalid if executable == "claude" else paths[executable],
        )
        with pytest.raises(ValueError, match="absolute path"):
            e3._resolve_agent_binaries(spec)


def test_run_e3_has_no_input_callback_param():
    import inspect

    assert "input_callback" not in inspect.signature(e3.run_e3).parameters


def test_setup_host2_credentials_replaces_checkpoint_helper():
    assert hasattr(e3, "setup_host2_credentials")
    assert not hasattr(e3, "perform_oauth_checkpoint")
    assert not hasattr(e3, "assert_one_checkpoint")


def test_keychain_default_adapter_uses_absolute_security_and_remaining_timeout(
    monkeypatch, tmp_path
):
    calls = []

    def fake_run(command, *, capture_output, check, timeout):
        calls.append((list(command), capture_output, check, timeout))
        return SimpleNamespace(returncode=51, stdout=b"", stderr=b"ignored")

    monkeypatch.setattr(host2_credentials.subprocess, "run", fake_run)

    result = host2_credentials.materialize_keychain_credential(
        "service",
        "account",
        tmp_path / "dest",
        max_bytes=1024,
        shape_ok=lambda _raw: True,
    )

    assert result.status is host2_credentials.CredentialStatus.SOURCE_UNREADABLE
    assert len(calls) == 1
    command, capture_output, check, timeout = calls[0]
    assert command == [
        "/usr/bin/security",
        "list-keychains",
        "-d",
        "user",
    ]
    assert capture_output is True
    assert check is False
    assert 0 < timeout <= 5.0


def test_keychain_operation_uses_one_monotonic_deadline_across_commands(
    monkeypatch, tmp_path
):
    clock = [100.0]
    calls = []
    keychain = "/Users/test/Library/Keychains/login.keychain-db"

    monkeypatch.setattr(
        host2_credentials,
        "_KEYCHAIN_OPERATION_TIMEOUT_SECONDS",
        5.0,
        raising=False,
    )
    monkeypatch.setattr(time, "monotonic", lambda: clock[0])

    def runner(command):
        calls.append(list(command))
        clock[0] += 3.0
        if command[1] == "list-keychains":
            return SimpleNamespace(
                returncode=0,
                stdout=json.dumps(keychain).encode() + b"\n",
                stderr=b"",
            )
        if "-w" in command:
            pytest.fail("retrieval ran after the operation deadline")
        return SimpleNamespace(returncode=44, stdout=b"", stderr=b"")

    result = host2_credentials.materialize_keychain_credential(
        "service",
        "account",
        tmp_path / "dest",
        max_bytes=1024,
        shape_ok=lambda _raw: True,
        runner=runner,
    )

    assert result.status is host2_credentials.CredentialStatus.SOURCE_UNREADABLE
    assert calls == [
        ["security", "list-keychains", "-d", "user"],
        [
            "security",
            "find-generic-password",
            "-s",
            "service",
            "-a",
            "account",
            keychain,
        ],
    ]


@pytest.mark.parametrize(
    "listed",
    (
        b'prefix \"/a.keychain-db\"\n',
        b'\"/a.keychain-db\" trailing\n',
        b'\"/a.keychain-db\"\nresidue\n',
        b'\"/a.keychain-db\"\\x00\n',
        b'\"/a.keychain-db\"\n\\xff\n',
        b'\"/a.keychain-db\"\v\"/b.keychain-db\"\n',
        b'\"/a.keychain-db\"\f\"/b.keychain-db\"\n',
        b'\"/a.keychain-db\"\xc2\x85\"/b.keychain-db\"\n',
        b'\"/a\\u007f.keychain-db\"\n',
        b'\"/a\\u0085.keychain-db\"\n',
        b'\"/a\\u009f.keychain-db\"\n',
        b'42\n',
        b'\"/a.keychain-db\"\n\n\"/b.keychain-db\"\n',
    ),
)
def test_keychain_list_requires_complete_enumerated_json_string_lines(
    tmp_path, listed
):
    calls = []

    def runner(command):
        calls.append(list(command))
        return SimpleNamespace(returncode=0, stdout=listed, stderr=b"")

    result = host2_credentials.materialize_keychain_credential(
        "service",
        "account",
        tmp_path / "dest",
        max_bytes=1024,
        shape_ok=lambda _raw: True,
        runner=runner,
    )

    assert result.status is host2_credentials.CredentialStatus.SOURCE_UNREADABLE
    assert calls == [["security", "list-keychains", "-d", "user"]]


@pytest.mark.parametrize("malformed_phase", ("list", "retrieval"))
@pytest.mark.parametrize("string_behavior", ("raises", "coerces"))
def test_keychain_malformed_stdout_is_typed_and_not_echoed(
    tmp_path, malformed_phase, string_behavior
):
    marker = "dynamic-output-marker"
    keychain = "/a.keychain-db"

    class MalformedOutput:
        def __init__(self, text):
            self.text = text

        def __str__(self):
            if string_behavior == "raises":
                raise RuntimeError(marker)
            return self.text

    def runner(command):
        if command[1] == "list-keychains":
            stdout = (
                MalformedOutput(json.dumps(keychain) + "\n")
                if malformed_phase == "list"
                else json.dumps(keychain).encode() + b"\n"
            )
            return SimpleNamespace(returncode=0, stdout=stdout, stderr=b"")
        if "-w" in command:
            return SimpleNamespace(
                returncode=0,
                stdout=MalformedOutput('{"credential":"coerced"}'),
                stderr=b"",
            )
        return SimpleNamespace(returncode=0, stdout=b"", stderr=b"")

    result = host2_credentials.materialize_keychain_credential(
        "service",
        "account",
        tmp_path / "dest",
        max_bytes=1024,
        shape_ok=lambda _raw: True,
        runner=runner,
    )

    assert result.status is host2_credentials.CredentialStatus.SOURCE_UNREADABLE
    assert marker not in repr(result)


@pytest.mark.parametrize("malformed_phase", ("list", "retrieval"))
def test_keychain_bytes_subclass_stdout_is_typed_and_not_echoed(
    tmp_path, malformed_phase
):
    marker = "bytes-subclass-marker"
    keychain = "/a.keychain-db"

    class HostileBytes(bytes):
        def decode(self, *_args, **_kwargs):
            raise RuntimeError(marker)

        def endswith(self, *_args, **_kwargs):
            raise RuntimeError(marker)

    def runner(command):
        if command[1] == "list-keychains":
            stdout = (
                HostileBytes(json.dumps(keychain).encode() + b"\n")
                if malformed_phase == "list"
                else json.dumps(keychain).encode() + b"\n"
            )
            return SimpleNamespace(returncode=0, stdout=stdout, stderr=b"")
        if "-w" in command:
            return SimpleNamespace(
                returncode=0,
                stdout=HostileBytes(b'{"credential":"subclass"}'),
                stderr=b"",
            )
        return SimpleNamespace(returncode=0, stdout=b"", stderr=b"")

    result = host2_credentials.materialize_keychain_credential(
        "service",
        "account",
        tmp_path / "dest",
        max_bytes=1024,
        shape_ok=lambda _raw: True,
        runner=runner,
    )

    assert result.status is host2_credentials.CredentialStatus.SOURCE_UNREADABLE
    assert marker not in repr(result)


def test_file_reader_rejects_same_size_cross_chunk_in_place_rewrite(
    monkeypatch, tmp_path
):
    padding = "x" * (host2_credentials._READ_CHUNK * 2)
    raw = json.dumps(
        {"tokens": {"access_token": "fixture"}, "padding": padding},
        separators=(",", ":"),
    ).encode()
    src = tmp_path / "auth.json"
    dest = tmp_path / "dest" / "auth.json"
    src.write_bytes(raw)
    mutation_offset = host2_credentials._READ_CHUNK + 100
    assert raw[mutation_offset : mutation_offset + 1] == b"x"
    real_read = host2_credentials.os.read
    mutated = []

    def mutate_after_first_chunk(fd, size):
        piece = real_read(fd, size)
        if piece and not mutated:
            rewrite_fd = os.open(src, os.O_WRONLY)
            try:
                os.pwrite(rewrite_fd, b"y", mutation_offset)
            finally:
                os.close(rewrite_fd)
            mutated.append(True)
        return piece

    monkeypatch.setattr(host2_credentials.os, "read", mutate_after_first_chunk)

    result = host2_credentials.materialize_file_credential(
        src,
        dest,
        max_bytes=len(raw) + 1,
        shape_ok=host2_credentials.codex_shape_ok,
    )

    assert mutated == [True]
    assert result.status is host2_credentials.CredentialStatus.SOURCE_UNREADABLE
    assert not dest.exists()


@pytest.mark.parametrize(
    ("field", "value"),
    (
        ("checkpoint_count", 1),
        ("checkpoint_prompt", "x"),
        ("oauth_checkpoint", True),
        ("pause_text", "x"),
    ),
)
def test_validate_spec_rejects_stale_interactive_fields(field, value):
    spec = _valid_two_agent_spec()
    spec[field] = value
    assert (
        f"{field} must not be declared (run is non-interactive)"
        in e3._validate_spec(spec)
    )


def _live_override_spec():
    """Return a valid spec whose agents carry the shipped store overrides."""
    spec = _valid_two_agent_spec()
    overrides = {
        "claude-code": {"CLAUDE_CONFIG_DIR": "{profile}"},
        "codex": {"CODEX_HOME": "{profile}"},
    }
    for agent in spec["agents"]:
        agent["env"] = overrides[agent["id"]]
    return spec


def _envelope(verb, exit_code, *, ok, warnings=(), error=None, result=None):
    warning_rows = [
        {"kind": warning} if isinstance(warning, str) else warning
        for warning in warnings
    ]
    return json.dumps(
        {
            "envelope_version": 1,
            "app_version": "0.1.0",
            "ok": ok,
            "verb": verb,
            "exit_code": exit_code,
            "warnings": warning_rows,
            "advisories": [],
            "result": result,
            "error": error,
        }
    )


def _successful_pack(*, warnings=()):
    return SimpleNamespace(
        returncode=2 if warnings else 0,
        stdout=_envelope(
            "pack",
            2 if warnings else 0,
            ok=True,
            warnings=warnings,
            result={},
        ),
        stderr="",
    )


def _valid_sessions_payload():
    return {
        "agents": [
            {
                "agent": agent_id,
                "sessions": [
                    {
                        "outcome": "installed",
                        "installed_session_id": f"{agent_id}-session",
                    }
                ],
            }
            for agent_id in ("codex", "claude-code")
        ]
    }


def _open_process_result(
    restored_workspace,
    *,
    returncode=0,
    ok=True,
    warnings=(),
    error=None,
):
    restored_workspace.mkdir(exist_ok=True)
    return SimpleNamespace(
        returncode=returncode,
        stdout=_envelope(
            "open",
            returncode,
            ok=ok,
            warnings=warnings,
            error=error,
            result={
                "output_dir": str(restored_workspace),
                "sessions": _valid_sessions_payload(),
            },
        ),
        stderr="",
    )


def _run_exit_contract_case(
    monkeypatch,
    tmp_path,
    stable_test_root,
    *,
    pack_result,
    open_result=None,
    post_pack_exception=None,
):
    spec_path, seen = _configure_exit_contract_case(
        monkeypatch,
        tmp_path,
        pack_result=pack_result,
        open_result=open_result,
        post_pack_exception=post_pack_exception,
    )
    result = e3.run_e3(
        spec_path,
        Path("/fake/biv"),
        stable_test_root / "scratch",
    )
    return result, seen


def _materialize_test_credential_guards(spec, profile_root, credential_guards):
    destinations = {}
    for agent in spec["agents"]:
        profile = e3._agent_profile(agent, Path(profile_root), live=False)
        destination = (
            profile / ".credentials.json"
            if agent["id"] == "claude-code"
            else profile / "auth.json"
        )
        destination.parent.mkdir(parents=True, exist_ok=True)
        destination.write_bytes(b"test-credential-object")
        credential_guards[agent["id"]] = e3._credential_guard(destination)
        destinations[agent["id"]] = destination
    return destinations


def _configure_exit_contract_case(
    monkeypatch,
    tmp_path,
    *,
    pack_result,
    open_result=None,
    post_pack_exception=None,
):
    seen = []
    installed_root = tmp_path / "installed"

    def valid_open_result(restored_workspace):
        return _open_process_result(restored_workspace)

    def fake_spawn(command, cwd, env):
        if len(command) > 1 and command[1] == "pack":
            seen.append("pack")
            return pack_result
        if len(command) > 1 and command[1] == "open":
            seen.append("open")
            restored_workspace = Path(command[command.index("--dest") + 1])
            result = open_result or valid_open_result
            if callable(result):
                result = result(restored_workspace)
            return result
        if "--version" in command:
            version = "2.1.210" if _agent_basename(command) == "claude" else "0.144.1"
            return SimpleNamespace(returncode=0, stdout=version, stderr="")
        return SimpleNamespace(returncode=0, stdout="OK", stderr="")

    def fake_seed(
        agent,
        live_profile,
        seed_workspace,
        spec,
        env,
        spawn,
        capture_candidates,
        owned_paths,
        resolved_binary=None,
    ):
        transcript = seed_workspace.parent / f"{agent['id']}-seed.jsonl"
        transcript.write_text("{}\n", encoding="utf-8")
        capture_candidates.append(transcript)
        owned_paths.append(transcript)
        return transcript

    def fake_install_delta(agent_id, *args):
        installed_root.mkdir(exist_ok=True)
        path = installed_root / f"{agent_id}.jsonl"
        path.write_text('{"turn":"seed"}\n', encoding="utf-8")
        return [path]

    monkeypatch.setattr(e3, "_spawn", fake_spawn)
    monkeypatch.setattr(e3, "_seed_agent", fake_seed)
    monkeypatch.setattr(e3, "scan_image_secret_values", lambda *args: [])
    if post_pack_exception is not None:
        def raise_post_pack(*args):
            raise post_pack_exception

        monkeypatch.setattr(e3, "scan_image_secret_values", raise_post_pack)
    def fake_setup(
        spec,
        _host2,
        profile_root,
        _resolved_binaries,
        _spawn,
        _scanner,
        _child_outputs,
        _ambient_snapshots,
        credential_guards,
    ):
        _materialize_test_credential_guards(
            spec,
            profile_root,
            credential_guards,
        )
        return {agent["id"]: {} for agent in spec["agents"]}

    monkeypatch.setattr(e3, "setup_host2_credentials", fake_setup)
    monkeypatch.setattr(e3, "snapshot_store", lambda *args: {})
    monkeypatch.setattr(e3, "class_j_failures", lambda *args: [])
    monkeypatch.setattr(e3, "assert_exact_install_delta", fake_install_delta)
    monkeypatch.setattr(e3, "assert_resume_containment", lambda *args, **kwargs: None)

    spec_path = tmp_path / "e3-exit-contract.json"
    spec_path.write_text(json.dumps(_valid_two_agent_spec()), encoding="utf-8")
    return spec_path, seen


def test_e3_pack_exit2_with_warnings_reaches_pass_and_surfaces(
    monkeypatch, tmp_path, stable_test_root
):
    packed = SimpleNamespace(
        returncode=2,
        stdout=_envelope(
            "pack",
            2,
            ok=True,
            warnings=["CodexDbEnrichmentSkipped"],
            result={},
        ),
        stderr="",
    )

    result, seen = _run_exit_contract_case(
        monkeypatch,
        tmp_path,
        stable_test_root,
        pack_result=packed,
    )

    assert result.status is Status.PASS
    assert seen == ["pack", "open"]
    assert result.detail == "e3-post-materialization-pass"
    assert result.warnings == ["biv-warning-present"]
    row = Report([result]).to_json()["rows"][0]
    assert row["warnings"] == ["biv-warning-present"]


def test_e3_pack_ok_false_at_exit2_returns_report_refusal(
    monkeypatch, tmp_path, stable_test_root
):
    packed = SimpleNamespace(
        returncode=2,
        stdout=_envelope(
            "pack",
            2,
            ok=False,
            error={"kind": "ContainmentRefused", "message": "live-store divergence"},
        ),
        stderr="discarded stderr",
    )

    result, seen = _run_exit_contract_case(
        monkeypatch, tmp_path, stable_test_root, pack_result=packed
    )

    _assert_report_refused(result)
    assert seen == ["pack"]


def test_e3_pack_failure_detail_from_envelope(
    monkeypatch, tmp_path, stable_test_root
):
    packed = SimpleNamespace(
        returncode=3,
        stdout=_envelope(
            "pack",
            3,
            ok=False,
            error={"kind": "CollisionRefused", "message": "boom"},
        ),
        stderr="wrong source",
    )

    result, _ = _run_exit_contract_case(
        monkeypatch, tmp_path, stable_test_root, pack_result=packed
    )

    _assert_report_refused(result)


def test_e3_pack_exit_code_mismatch_fails(monkeypatch, tmp_path, stable_test_root):
    packed = SimpleNamespace(
        returncode=3,
        stdout=_envelope(
            "pack",
            2,
            ok=False,
            error={"kind": "CollisionRefused", "message": "boom"},
        ),
        stderr="",
    )

    result, _ = _run_exit_contract_case(
        monkeypatch, tmp_path, stable_test_root, pack_result=packed
    )

    _assert_report_refused(result)


def test_e3_pack_ok_true_bad_exit_is_violation(
    monkeypatch, tmp_path, stable_test_root
):
    packed = SimpleNamespace(
        returncode=3,
        stdout=_envelope("pack", 3, ok=True, result={}),
        stderr="",
    )

    result, _ = _run_exit_contract_case(
        monkeypatch, tmp_path, stable_test_root, pack_result=packed
    )

    _assert_report_refused(result)


def test_e3_pack_boolean_exit_code_fails(monkeypatch, tmp_path, stable_test_root):
    packed = SimpleNamespace(
        returncode=0,
        stdout=_envelope("pack", False, ok=True, result={}),
        stderr="",
    )

    result, _ = _run_exit_contract_case(
        monkeypatch, tmp_path, stable_test_root, pack_result=packed
    )

    _assert_report_refused(result)


def test_e3_pack_non_object_envelope_fails(
    monkeypatch, tmp_path, stable_test_root
):
    packed = SimpleNamespace(returncode=3, stdout="[1, 2, 3]", stderr="")

    result, _ = _run_exit_contract_case(
        monkeypatch, tmp_path, stable_test_root, pack_result=packed
    )

    _assert_report_refused(result)


def test_e3_pack_unparseable_envelope_fails(
    monkeypatch, tmp_path, stable_test_root
):
    packed = SimpleNamespace(returncode=3, stdout="", stderr="segfault")

    result, _ = _run_exit_contract_case(
        monkeypatch, tmp_path, stable_test_root, pack_result=packed
    )

    _assert_report_refused(result)


def test_e3_pack_non_bool_ok_fails(monkeypatch, tmp_path, stable_test_root):
    packed = SimpleNamespace(
        returncode=2,
        stdout=_envelope("pack", 2, ok="false", result={}),
        stderr="",
    )

    result, _ = _run_exit_contract_case(
        monkeypatch, tmp_path, stable_test_root, pack_result=packed
    )

    _assert_report_refused(result)


def test_e3_pack_malformed_warnings_fail_loud(
    monkeypatch, tmp_path, stable_test_root
):
    packed = SimpleNamespace(
        returncode=2,
        stdout=_envelope("pack", 2, ok=True, warnings=[{"note": "x"}], result={}),
        stderr="",
    )

    result, _ = _run_exit_contract_case(
        monkeypatch, tmp_path, stable_test_root, pack_result=packed
    )

    _assert_report_refused(result)


def test_e3_warned_pack_then_open_failure_retains_both(
    monkeypatch, tmp_path, stable_test_root
):
    opened = SimpleNamespace(
        returncode=3,
        stdout=_envelope(
            "open",
            3,
            ok=False,
            error={"kind": "SessionInstallFailed", "message": "install boom"},
        ),
        stderr="",
    )

    result, seen = _run_exit_contract_case(
        monkeypatch,
        tmp_path,
        stable_test_root,
        pack_result=_successful_pack(warnings=["CodexDbEnrichmentSkipped"]),
        open_result=opened,
    )

    assert result.status is Status.FAIL
    assert seen == ["pack", "open"]
    assert result.detail == "e3-post-materialization-fail"
    assert result.warnings == ["biv-warning-present"]
    assert Report([result]).to_json()["rows"][0]["warnings"] == [
        "biv-warning-present"
    ]


def test_e3_warned_pack_then_handled_exception_returns_report_refusal(
    monkeypatch, tmp_path, stable_test_root
):
    result, seen = _run_exit_contract_case(
        monkeypatch,
        tmp_path,
        stable_test_root,
        pack_result=_successful_pack(warnings=["CodexDbEnrichmentSkipped"]),
        post_pack_exception=ValueError("credential sentinel found in image"),
    )

    _assert_report_refused(result)
    assert seen == ["pack"]


def test_e3_open_exit2_with_warnings_proceeds(
    monkeypatch, tmp_path, stable_test_root
):
    def warned_open(restored_workspace):
        return _open_process_result(
            restored_workspace,
            returncode=2,
            warnings=[
                {
                    "kind": "UnknownAgentSkipped",
                    "path": "sessions/unknown.jsonl",
                }
            ],
        )

    result, seen = _run_exit_contract_case(
        monkeypatch,
        tmp_path,
        stable_test_root,
        pack_result=_successful_pack(),
        open_result=warned_open,
    )

    assert result.status is Status.PASS
    assert seen == ["pack", "open"]
    assert result.detail == "e3-post-materialization-pass"
    assert result.warnings == ["biv-warning-present"]


def test_e3_open_failure_detail_from_envelope(
    monkeypatch, tmp_path, stable_test_root
):
    opened = SimpleNamespace(
        returncode=3,
        stdout=_envelope(
            "open",
            3,
            ok=False,
            error={"kind": "SessionInstallFailed", "message": "open boom"},
        ),
        stderr="wrong source",
    )

    result, seen = _run_exit_contract_case(
        monkeypatch,
        tmp_path,
        stable_test_root,
        pack_result=_successful_pack(),
        open_result=opened,
    )

    assert result.status is Status.FAIL
    assert seen == ["pack", "open"]
    assert result.detail == "e3-post-materialization-fail"


@pytest.mark.parametrize(
    "result_payload",
    (None, "bad", []),
    ids=("null", "string", "list"),
)
def test_e3_open_non_object_result_fails_loudly(
    monkeypatch, tmp_path, stable_test_root, result_payload
):
    opened = SimpleNamespace(
        returncode=0,
        stdout=_envelope("open", 0, ok=True, result=result_payload),
        stderr="",
    )

    result, seen = _run_exit_contract_case(
        monkeypatch,
        tmp_path,
        stable_test_root,
        pack_result=_successful_pack(),
        open_result=opened,
    )

    assert result.status is Status.FAIL
    assert seen == ["pack", "open"]
    assert result.detail == "e3-post-materialization-fail"


@pytest.mark.parametrize(
    "result_payload",
    (
        {},
        {"sessions": _valid_sessions_payload()},
        {"output_dir": ""},
        {"output_dir": 42},
    ),
    ids=("empty-result", "missing", "empty", "non-string"),
)
def test_e3_open_invalid_output_dir_fails_before_path_resolution(
    monkeypatch, tmp_path, stable_test_root, result_payload
):
    opened = SimpleNamespace(
        returncode=0,
        stdout=_envelope("open", 0, ok=True, result=result_payload),
        stderr="",
    )

    result, _ = _run_exit_contract_case(
        monkeypatch,
        tmp_path,
        stable_test_root,
        pack_result=_successful_pack(),
        open_result=opened,
    )

    assert result.status is Status.FAIL
    assert result.detail == "e3-post-materialization-fail"


@pytest.mark.parametrize(
    "output_dir",
    (".", "..", "relative/path"),
    ids=("dot", "dotdot", "nested-relative"),
)
def test_e3_open_relative_output_dir_fails_before_workspace_binding(
    monkeypatch, tmp_path, stable_test_root, output_dir
):
    opened = SimpleNamespace(
        returncode=0,
        stdout=_envelope(
            "open",
            0,
            ok=True,
            result={
                "output_dir": output_dir,
                "sessions": _valid_sessions_payload(),
            },
        ),
        stderr="",
    )

    result, seen = _run_exit_contract_case(
        monkeypatch,
        tmp_path,
        stable_test_root,
        pack_result=_successful_pack(warnings=["CodexDbEnrichmentSkipped"]),
        open_result=opened,
    )

    assert result.status is Status.FAIL
    assert seen == ["pack", "open"]
    assert result.detail == "e3-post-materialization-fail"
    assert result.warnings == ["biv-warning-present"]


def test_e3_open_off_tree_absolute_output_dir_fails_before_workspace_binding(
    monkeypatch, tmp_path, stable_test_root
):
    off_tree = tmp_path / "off-tree"
    off_tree.mkdir()
    opened = SimpleNamespace(
        returncode=0,
        stdout=_envelope(
            "open",
            0,
            ok=True,
            result={
                "output_dir": str(off_tree),
                "sessions": _valid_sessions_payload(),
            },
        ),
        stderr="",
    )

    result, seen = _run_exit_contract_case(
        monkeypatch,
        tmp_path,
        stable_test_root,
        pack_result=_successful_pack(),
        open_result=opened,
    )

    assert result.status is Status.FAIL
    assert seen == ["pack", "open"]
    assert result.detail == "e3-post-materialization-fail"


def test_open_result_rejects_dotdot_alias_of_requested_destination(tmp_path):
    requested = tmp_path / "host2" / "work"
    alias = tmp_path / "host2" / "alias" / ".." / "work"
    envelope = {
        "result": {
            "output_dir": str(alias),
            "sessions": _valid_sessions_payload(),
        }
    }

    outcome = e3._open_result_outcome(envelope, requested)

    assert not outcome.ok
    assert "requested destination" in outcome.detail


@pytest.mark.parametrize(
    ("case", "sessions_payload", "detail_member"),
    (
        ("sessions-null", None, "sessions"),
        ("sessions-list", [], "sessions"),
        ("agents-null", {"agents": None}, "sessions.agents"),
        ("group-scalar", {"agents": [1]}, "sessions.agents[0]"),
        (
            "group-agent-missing",
            {"agents": [{"sessions": []}]},
            "sessions.agents[0].agent",
        ),
        (
            "group-sessions-null",
            {"agents": [{"agent": "codex", "sessions": None}]},
            "sessions.agents[0].sessions",
        ),
        (
            "session-scalar",
            {"agents": [{"agent": "codex", "sessions": [1]}]},
            "sessions.agents[0].sessions[0]",
        ),
        (
            "session-outcome-missing",
            {"agents": [{"agent": "codex", "sessions": [{}]}]},
            "sessions.agents[0].sessions[0].outcome",
        ),
        (
            "installed-id-non-string",
            {
                "agents": [
                    {
                        "agent": "codex",
                        "sessions": [
                            {"outcome": "installed", "installed_session_id": 42}
                        ],
                    },
                    {
                        "agent": "claude-code",
                        "sessions": [
                            {
                                "outcome": "installed",
                                "installed_session_id": "claude-code-session",
                            }
                        ],
                    },
                ]
            },
            "sessions.agents[0].sessions[0].installed_session_id",
        ),
    ),
    ids=(
        "sessions-null",
        "sessions-list",
        "agents-null",
        "group-scalar",
        "group-agent-missing",
        "group-sessions-null",
        "session-scalar",
        "session-outcome-missing",
        "installed-id-non-string",
    ),
)
def test_e3_open_malformed_sessions_fail_before_consumer_access(
    monkeypatch,
    tmp_path,
    stable_test_root,
    case,
    sessions_payload,
    detail_member,
):
    def malformed_open(restored_workspace):
        restored_workspace.mkdir(exist_ok=True)
        payload = {
            "output_dir": str(restored_workspace),
            "sessions": sessions_payload,
        }
        return SimpleNamespace(
            returncode=0,
            stdout=_envelope("open", 0, ok=True, result=payload),
            stderr="",
        )

    result, _ = _run_exit_contract_case(
        monkeypatch,
        tmp_path,
        stable_test_root,
        pack_result=_successful_pack(),
        open_result=malformed_open,
    )

    assert result.status is Status.FAIL, case
    assert result.detail == "e3-post-materialization-fail"


def test_e3_open_installed_agent_ids_must_match_spec_and_retain_warning(
    monkeypatch, tmp_path, stable_test_root
):
    def mismatched_open(restored_workspace):
        restored_workspace.mkdir(exist_ok=True)
        sessions = _valid_sessions_payload()
        sessions["agents"][1]["agent"] = "bogus-agent"
        return SimpleNamespace(
            returncode=0,
            stdout=_envelope(
                "open",
                0,
                ok=True,
                result={
                    "output_dir": str(restored_workspace),
                    "sessions": sessions,
                },
            ),
            stderr="",
        )

    result, seen = _run_exit_contract_case(
        monkeypatch,
        tmp_path,
        stable_test_root,
        pack_result=_successful_pack(warnings=["CodexDbEnrichmentSkipped"]),
        open_result=mismatched_open,
    )

    assert result.status is Status.FAIL
    assert seen == ["pack", "open"]
    assert result.detail == "e3-post-materialization-fail"
    assert Report([result]).to_json()["rows"][0]["warnings"] == [
        "biv-warning-present"
    ]


@pytest.mark.parametrize(
    ("case", "actual_agents"),
    (
        ("duplicate", ["claude-code", "codex", "codex"]),
        ("missing", ["codex"]),
        ("extra", ["claude-code", "codex", "extra-agent"]),
    ),
)
def test_e3_open_installed_agent_multiset_must_match_spec(
    monkeypatch, tmp_path, stable_test_root, case, actual_agents
):
    def malformed_open(restored_workspace):
        restored_workspace.mkdir(exist_ok=True)
        sessions = _valid_sessions_payload()
        if case == "duplicate":
            sessions["agents"].append(
                {
                    "agent": "codex",
                    "sessions": [
                        {
                            "outcome": "installed",
                            "installed_session_id": "codex-duplicate-session",
                        }
                    ],
                }
            )
        elif case == "missing":
            sessions["agents"].pop()
        else:
            sessions["agents"].append(
                {
                    "agent": "extra-agent",
                    "sessions": [
                        {
                            "outcome": "installed",
                            "installed_session_id": "extra-agent-session",
                        }
                    ],
                }
            )
        return SimpleNamespace(
            returncode=0,
            stdout=_envelope(
                "open",
                0,
                ok=True,
                result={
                    "output_dir": str(restored_workspace),
                    "sessions": sessions,
                },
            ),
            stderr="",
        )

    result, seen = _run_exit_contract_case(
        monkeypatch,
        tmp_path,
        stable_test_root,
        pack_result=_successful_pack(warnings=["CodexDbEnrichmentSkipped"]),
        open_result=malformed_open,
    )

    assert result.status is Status.FAIL
    assert seen == ["pack", "open"]
    assert result.detail == "e3-post-materialization-fail"
    assert Report([result]).to_json()["rows"][0]["warnings"] == [
        "biv-warning-present"
    ]


@pytest.mark.parametrize(
    ("case", "installed_count"),
    (
        ("mixed-over", 2),
        ("mixed-under", 0),
        ("sole-over", 2),
        ("sole-under", 0),
    ),
)
def test_e3_open_each_raw_group_requires_exactly_one_installed_row(
    monkeypatch, tmp_path, stable_test_root, case, installed_count
):
    def malformed_open(restored_workspace):
        restored_workspace.mkdir(exist_ok=True)
        sessions = _valid_sessions_payload()
        codex_group = sessions["agents"][0]
        original_row = codex_group["sessions"][0]
        if installed_count == 2:
            codex_group["sessions"].append(
                {
                    "outcome": "installed",
                    "installed_session_id": "codex-second-session",
                }
            )
        else:
            codex_group["sessions"] = [{"outcome": "skipped"}]
        if case.startswith("mixed"):
            sessions["agents"].append(
                {
                    "agent": "codex",
                    "sessions": [original_row],
                }
            )
        return SimpleNamespace(
            returncode=0,
            stdout=_envelope(
                "open",
                0,
                ok=True,
                result={
                    "output_dir": str(restored_workspace),
                    "sessions": sessions,
                },
            ),
            stderr="",
        )

    result, seen = _run_exit_contract_case(
        monkeypatch,
        tmp_path,
        stable_test_root,
        pack_result=_successful_pack(warnings=["CodexDbEnrichmentSkipped"]),
        open_result=malformed_open,
    )

    assert result.status is Status.FAIL
    assert seen == ["pack", "open"]
    assert result.detail == "e3-post-materialization-fail"
    assert Report([result]).to_json()["rows"][0]["warnings"] == [
        "biv-warning-present"
    ]


def test_e3_warned_pack_then_malformed_open_result_retains_warning(
    monkeypatch, tmp_path, stable_test_root
):
    opened = SimpleNamespace(
        returncode=0,
        stdout=_envelope("open", 0, ok=True, result=None),
        stderr="",
    )

    result, _ = _run_exit_contract_case(
        monkeypatch,
        tmp_path,
        stable_test_root,
        pack_result=_successful_pack(warnings=["CodexDbEnrichmentSkipped"]),
        open_result=opened,
    )

    assert result.status is Status.FAIL
    assert result.detail == "e3-post-materialization-fail"
    assert Report([result]).to_json()["rows"][0]["warnings"] == [
        "biv-warning-present"
    ]


def test_cli_persists_failed_e3_report_for_malformed_open_result(
    monkeypatch, tmp_path, stable_test_root
):
    opened = SimpleNamespace(
        returncode=0,
        stdout=_envelope("open", 0, ok=True, result=None),
        stderr="",
    )
    spec_path, seen = _configure_exit_contract_case(
        monkeypatch,
        tmp_path,
        pack_result=_successful_pack(warnings=["CodexDbEnrichmentSkipped"]),
        open_result=opened,
    )
    report_path = stable_test_root / "report.json"

    exit_code = cli.main(
        [
            "--biv",
            str(tmp_path / "biv"),
            "--e3",
            str(spec_path),
            "--report",
            str(report_path),
        ]
    )

    assert exit_code != 0
    assert seen == ["pack", "open"]
    assert report_path.is_file()
    report = json.loads(report_path.read_text(encoding="utf-8"))
    assert report["failed"] == ["cx-range"]
    assert len(report["rows"]) == 1
    row = report["rows"][0]
    assert row["status"] == "fail"
    assert row["detail"] == "e3-post-materialization-fail"
    assert row["warnings"] == ["biv-warning-present"]
    assert list(stable_test_root.glob(".bivharness-scratch-*")) == []


def _selector_spec(env_mode):
    spec = _valid_two_agent_spec()
    if env_mode == "absent":
        for agent in spec["agents"]:
            agent.pop("env", None)
    return spec


def test_shared_fixture_is_valid_as_authored():
    assert e3._validate_spec(_valid_two_agent_spec()) == []


def test_live_override_spec_is_valid():
    assert e3._validate_spec(_live_override_spec()) == []


def test_validator_requires_no_session_persistence():
    spec = _valid_two_agent_spec()
    claude = next(agent for agent in spec["agents"] if agent["id"] == "claude-code")
    claude["liveness_command"].remove("--no-session-persistence")

    assert any("no-session-persistence" in failure for failure in e3._validate_spec(spec))


def test_c1_zero_session_control_accepts_absent_and_empty_locations(tmp_path):
    profile_root = tmp_path / "host2" / "profiles"
    for agent in _valid_two_agent_spec()["agents"]:
        store = profile_root / agent["id"]
        store.mkdir(parents=True)
        if agent["id"] == "claude-code":
            (store / "projects").mkdir()
        else:
            (store / "sessions").mkdir()
            (store / "archived_sessions").mkdir()
            (store / "session_index.jsonl").write_bytes(b"")

    assert e3._c1_zero_session_failures(profile_root, _valid_two_agent_spec()) == []


def _insert_session_when_scandir_stops(monkeypatch, directory):
    real_scandir = e3.os.scandir
    state = {"inserted": False}

    class InsertOnStop:
        def __init__(self, entries):
            self._entries = entries

        def __enter__(self):
            self._entries.__enter__()
            return self

        def __exit__(self, *args):
            return self._entries.__exit__(*args)

        def __iter__(self):
            return self

        def __next__(self):
            try:
                return next(self._entries)
            except StopIteration:
                if not state["inserted"]:
                    (directory / "late-session.jsonl").write_bytes(b"{}")
                    state["inserted"] = True
                raise

    def scandir_with_insertion(path):
        entries = real_scandir(path)
        if isinstance(path, int):
            try:
                target = os.stat(directory, follow_symlinks=False)
                if e3._same_entry(os.fstat(path), target):
                    return InsertOnStop(entries)
            except FileNotFoundError:
                pass
        return entries

    monkeypatch.setattr(e3.os, "scandir", scandir_with_insertion)
    return state


def test_c1_zero_session_control_reds_on_file_inserted_at_scandir_stop(
    monkeypatch, tmp_path
):
    profile_root = tmp_path / "profiles"
    sessions = profile_root / "codex" / "sessions"
    sessions.mkdir(parents=True)
    (profile_root / "claude-code").mkdir(parents=True)
    mutation = _insert_session_when_scandir_stops(monkeypatch, sessions)

    failures = e3._c1_zero_session_failures(
        profile_root,
        _valid_two_agent_spec(),
    )

    assert mutation["inserted"]
    assert any("changed during enumeration" in failure for failure in failures)


@pytest.mark.parametrize(
    ("agent_id", "location", "kind"),
    (
        ("claude-code", "projects", "regular"),
        ("codex", "sessions", "regular"),
        ("codex", "session_index.jsonl", "regular"),
        ("codex", "archived_sessions", "regular"),
        ("claude-code", "projects", "symlink"),
        ("codex", "sessions", "fifo"),
    ),
)
def test_c1_zero_session_control_reds_on_recorded_or_nonregular_entries(
    tmp_path, agent_id, location, kind
):
    profile_root = tmp_path / "profiles"
    store = profile_root / agent_id
    store.mkdir(parents=True)
    target = store / location
    if kind == "regular":
        if location.endswith(".jsonl"):
            target.write_bytes(b"recorded")
        else:
            (target / "recorded.jsonl").parent.mkdir(parents=True)
            (target / "recorded.jsonl").write_bytes(b"{}")
    elif kind == "symlink":
        outside = tmp_path / "outside"
        outside.mkdir()
        (outside / "recorded.jsonl").write_bytes(b"{}")
        target.symlink_to(outside, target_is_directory=True)
    else:
        os.mkfifo(target)

    failures = e3._c1_zero_session_failures(profile_root, _valid_two_agent_spec())

    assert failures
    assert agent_id in "\n".join(failures)


def test_c1_zero_session_control_reds_when_profile_isolation_is_dropped(tmp_path):
    profile_root = tmp_path / "profiles"
    origin = tmp_path / "origin"
    (origin / "projects" / "origin").mkdir(parents=True)
    (origin / "projects" / "origin" / "session.jsonl").write_bytes(b"{}")
    profile_root.mkdir()
    (profile_root / "claude-code").symlink_to(origin, target_is_directory=True)
    (profile_root / "codex").mkdir()

    failures = e3._c1_zero_session_failures(profile_root, _valid_two_agent_spec())

    assert failures
    assert any("claude-code" in failure for failure in failures)


def test_c1_zero_session_control_reds_on_unreadable_empty_index_and_continues(
    monkeypatch, tmp_path
):
    profile_root = tmp_path / "profiles"
    codex = profile_root / "codex"
    codex.mkdir(parents=True)
    (codex / "sessions").mkdir()
    (codex / "archived_sessions").mkdir()
    index = codex / "session_index.jsonl"
    index.write_bytes(b"")
    real_open = e3.os.open

    def deny_index(path, flags, mode=0o777, *, dir_fd=None):
        if Path(path) == index or (path == index.name and dir_fd is not None):
            raise PermissionError("denied")
        return real_open(path, flags, mode, dir_fd=dir_fd)

    monkeypatch.setattr(e3.os, "open", deny_index)

    failures = e3._c1_zero_session_failures(profile_root, _valid_two_agent_spec())

    assert any("session_index.jsonl" in failure for failure in failures)


def test_c1_zero_session_control_rejects_directory_swap_before_scan(
    monkeypatch, tmp_path
):
    profile_root = tmp_path / "profiles"
    projects = profile_root / "claude-code" / "projects"
    projects.mkdir(parents=True)
    (profile_root / "codex").mkdir()
    outside = tmp_path / "outside"
    outside.mkdir()
    real_scandir = e3.os.scandir
    swapped = False

    def swap_to_symlink(path):
        nonlocal swapped
        if not swapped:
            projects.rmdir()
            projects.symlink_to(outside, target_is_directory=True)
            swapped = True
        return real_scandir(path)

    monkeypatch.setattr(e3.os, "scandir", swap_to_symlink)

    failures = e3._c1_zero_session_failures(profile_root, _valid_two_agent_spec())

    assert swapped
    assert failures
    assert any("projects" in failure for failure in failures)


def test_c1_zero_session_control_rejects_profile_ancestor_swap(
    monkeypatch, tmp_path
):
    profile_root = tmp_path / "profiles"
    store = profile_root / "claude-code"
    projects = store / "projects"
    projects.mkdir(parents=True)
    (profile_root / "codex").mkdir()
    outside = tmp_path / "outside"
    outside.mkdir()
    moved = tmp_path / "detached-claude-profile"
    real_scandir = e3.os.scandir
    swapped = False

    def swap_profile_to_symlink(path):
        nonlocal swapped
        if not swapped:
            store.rename(moved)
            store.symlink_to(outside, target_is_directory=True)
            swapped = True
        return real_scandir(path)

    monkeypatch.setattr(e3.os, "scandir", swap_profile_to_symlink)

    failures = e3._c1_zero_session_failures(profile_root, _valid_two_agent_spec())

    assert swapped
    assert failures
    assert any("changed during nofollow inspection" in failure for failure in failures)


@pytest.mark.parametrize("kind", ("symlink", "fifo"))
def test_snapshot_store_rejects_nonregular_entries_without_reading(tmp_path, kind):
    root = tmp_path / "store"
    root.mkdir()
    target = root / "entry"
    if kind == "symlink":
        outside = tmp_path / "outside"
        outside.write_bytes(b"must-not-be-read")
        target.symlink_to(outside)
    else:
        os.mkfifo(target)

    with pytest.raises(ValueError, match="snapshot store"):
        snapshot_store(root)


def test_drift_tripwire_is_green_at_pinned_source():
    assert e3._c1_drift_tripwire_failures() == []


@pytest.mark.parametrize(
    ("rel", "anchor_old", "anchor_new", "key"),
    (
        pytest.param(
            "src/adapters/claude_code/claude_code.cpp",
            '.globs = {"projects/*/*.jsonl"}',
            '.globs = {"projects/*/*.jsonl", "x/**"}',
            "claude_adapter_file",
            id="claude-inventory",
        ),
        pytest.param(
            "src/adapters/codex/codex.cpp",
            '.globs = {"sessions/**/rollout-*.jsonl"}',
            '.globs = {"sessions/**/rollout-*.jsonl", "x/**"}',
            "codex_adapter_file",
            id="codex-inventory",
        ),
        pytest.param(
            "src/adapters/claude_code/claude_code.cpp",
            '.path = root / "projects"',
            '.path = root / "projects_moved"',
            "claude_adapter_file",
            id="claude-discover-primary",
        ),
        pytest.param(
            "src/adapters/codex/codex.cpp",
            '.path = root / "sessions"',
            '.path = root / "sessions_moved"',
            "codex_adapter_file",
            id="codex-discover-primary",
        ),
        pytest.param(
            "src/adapters/codex/codex.cpp",
            'root / "archived_sessions"}}',
            'root / "archived_sessions2"}}',
            "codex_adapter_file",
            id="codex-discover-archived",
        ),
        pytest.param(
            "src/adapters/claude_code/claude_code.cpp",
            "    std::vector<Store> stores;\n",
            (
                "    std::vector<Store> stores;\n"
                "    stores.push_back(Store{\n"
                '        .root = env.home / ".claude",\n'
                '        .locators = {StoreLocator{.kind = "sessions_root",\n'
                '                                  .path = env.home / "legacy_sessions"}},\n'
                "        .tier = DiscoveryTier::defaults,\n"
                "        .archived = false});\n"
            ),
            "claude_adapter_file",
            id="claude-discover-novel-location",
        ),
        pytest.param(
            "src/adapters/codex/codex.cpp",
            "    std::vector<Store> stores;\n",
            (
                "    std::vector<Store> stores;\n"
                "    stores.push_back(Store{\n"
                '        .root = env.home / ".codex",\n'
                '        .locators = {StoreLocator{.kind = "sessions_root",\n'
                '                                  .path = env.home / "legacy_sessions"}},\n'
                "        .tier = DiscoveryTier::defaults,\n"
                "        .archived = false});\n"
            ),
            "codex_adapter_file",
            id="codex-discover-novel-location",
        ),
    ),
)
def test_drift_tripwire_reds_each_adapter_read_side_change(
    tmp_path, rel, anchor_old, anchor_new, key
):
    repo = tmp_path / "repo"
    shutil.copytree(Path(__file__).resolve().parents[2] / "src", repo / "src")
    assert e3._c1_drift_tripwire_failures(repo) == []

    source = repo / rel
    text = source.read_text(encoding="utf-8")
    assert anchor_old in text
    source.write_text(
        text.replace(anchor_old, anchor_new, 1),
        encoding="utf-8",
    )

    failures = e3._c1_drift_tripwire_failures(repo)
    assert any(f"({key})" in failure for failure in failures)


def test_drift_tripwire_reds_on_unrelated_anchored_file_edit(tmp_path):
    repo = tmp_path / "repo"
    shutil.copytree(Path(__file__).resolve().parents[2] / "src", repo / "src")
    source = repo / "src/adapters/codex/codex.cpp"
    text = source.read_text(encoding="utf-8")
    anchor = "std::string discovery_tier_string(const DiscoveryTier tier) {\n"
    assert anchor in text
    source.write_text(
        text.replace(anchor, anchor + "  // unrelated control edit\n", 1),
        encoding="utf-8",
    )

    failures = e3._c1_drift_tripwire_failures(repo)
    assert any("(codex_adapter_file)" in failure for failure in failures)


def test_drift_tripwire_ignores_write_side_install_change(tmp_path):
    repo = tmp_path / "repo"
    shutil.copytree(Path(__file__).resolve().parents[2] / "src", repo / "src")
    source = repo / "src/adapters/claude_code/install.cpp"
    text = source.read_text(encoding="utf-8")
    old = 'target.target_store.root / "projects" / project_key'
    assert old in text
    source.write_text(
        text.replace(
            old,
            'target.target_store.root / "projects_moved" / project_key',
            1,
        ),
        encoding="utf-8",
    )

    assert e3._c1_drift_tripwire_failures(repo) == []


@pytest.mark.parametrize(
    ("rel", "function", "key"),
    (
        (
            "src/adapters/claude_code/claude_code.cpp",
            "const Inventory& claude_inventory()",
            "claude_adapter_file",
        ),
        (
            "src/adapters/codex/codex.cpp",
            "const Inventory& codex_inventory()",
            "codex_adapter_file",
        ),
    ),
    ids=("claude", "codex"),
)
def test_drift_tripwire_reds_on_post_initializer_collect_push_back(
    tmp_path, rel, function, key
):
    repo = tmp_path / "repo"
    shutil.copytree(Path(__file__).resolve().parents[2] / "src", repo / "src")
    source = repo / rel
    text = source.read_text(encoding="utf-8")
    function_start = text.index(function)
    insertion = text.index("    return value;", function_start)
    mutation = (
        '    value.collect.push_back(ArtifactClass{.name = "late-sessions",\n'
        '                                          .globs = {"late-sessions/**"}});\n'
    )
    source.write_text(
        text[:insertion] + mutation + text[insertion:],
        encoding="utf-8",
    )

    failures = e3._c1_drift_tripwire_failures(repo)
    assert any(key in failure for failure in failures)


def test_run_e3_liveness_without_persistence_flag_reds_c1_before_open(
    monkeypatch, tmp_path, stable_test_root
):
    spec = _valid_two_agent_spec()
    spec["agents"][0]["env"] = {"CODEX_HOME": "{profile}"}
    spec["agents"][1]["env"] = {"CLAUDE_CONFIG_DIR": "{profile}"}
    spec["host2_profile_root"] = "host2/profiles"
    spec_path = tmp_path / "e3.json"
    spec_path.write_text(json.dumps(spec), encoding="utf-8")
    open_calls = []

    real_materialize = e3.materialize_run_tokens

    def mutate_after_validation(value):
        materialized = real_materialize(value)
        claude = next(agent for agent in materialized["agents"] if agent["id"] == "claude-code")
        claude["liveness_command"].remove("--no-session-persistence")
        return materialized

    def fake_seed(*args, **kwargs):
        return None

    def fake_spawn(command, cwd, env):
        command = list(command)
        if len(command) > 1 and command[1] == "pack":
            return _successful_pack()
        if len(command) > 1 and command[1] == "open":
            open_calls.append(command)
            raise AssertionError("biv open must not run after C1 RED")
        if command[1:] == ["--version"]:
            version = "2.1.210" if _agent_basename(command) == "claude" else "0.144.1"
            return SimpleNamespace(returncode=0, stdout=version, stderr="")
        if command[1:] in (["auth", "status"], ["login", "status"]):
            return SimpleNamespace(returncode=0, stdout="authenticated", stderr="")
        if "-p" in command:
            projects = Path(env["CLAUDE_CONFIG_DIR"]) / "projects" / "liveness"
            projects.mkdir(parents=True, exist_ok=True)
            (projects / "transcript.jsonl").write_bytes(b"liveness")
            return SimpleNamespace(returncode=0, stdout="OK", stderr="")
        return SimpleNamespace(returncode=0, stdout="OK", stderr="")

    monkeypatch.setattr(e3, "materialize_run_tokens", mutate_after_validation)
    monkeypatch.setattr(e3, "_seed_agent", fake_seed)
    monkeypatch.setattr(e3, "_spawn", fake_spawn)
    monkeypatch.setattr(e3, "scan_image_secret_values", lambda *args: [])

    result = e3.run_e3(spec_path, Path("biv"), stable_test_root / "scratch")

    assert result.status is Status.INVALID
    assert result.detail == "e3-post-materialization-invalid"
    assert open_calls == []


def test_run_e3_origin_session_isolation_mutation_stops_before_open(
    monkeypatch, tmp_path, stable_test_root
):
    real_snapshot_store = e3.snapshot_store
    spec_path, seen = _configure_exit_contract_case(
        monkeypatch,
        tmp_path,
        pack_result=_successful_pack(),
    )
    spec = json.loads(spec_path.read_text(encoding="utf-8"))
    spec["host2_profile_root"] = "host2/profiles"
    spec_path.write_text(json.dumps(spec), encoding="utf-8")
    origin = tmp_path / "origin-session.jsonl"
    origin.write_bytes(b"origin-session")

    def expose_origin_session(value, host2, profile_root, resolved_binaries, spawn, *_args):
        claude_project = profile_root / "claude-code" / "projects" / "origin"
        claude_project.mkdir(parents=True)
        os.link(origin, claude_project / "session.jsonl")
        (profile_root / "codex").mkdir()
        return {agent["id"]: {} for agent in value["agents"]}

    monkeypatch.setattr(e3, "snapshot_store", real_snapshot_store)
    monkeypatch.setattr(e3, "setup_host2_credentials", expose_origin_session)

    result = e3.run_e3(spec_path, Path("biv"), stable_test_root / "scratch")

    assert result.status is Status.INVALID
    assert result.detail == "e3-post-materialization-invalid"
    assert seen == ["pack"]


def test_run_e3_session_inserted_at_scandir_stop_reds_c1_before_open(
    monkeypatch, tmp_path, stable_test_root
):
    spec_path, seen = _configure_exit_contract_case(
        monkeypatch,
        tmp_path,
        pack_result=_successful_pack(),
    )
    spec = json.loads(spec_path.read_text(encoding="utf-8"))
    spec["host2_profile_root"] = "host2/profiles"
    spec_path.write_text(json.dumps(spec), encoding="utf-8")
    profile_root = stable_test_root / "scratch" / "host2/profiles"
    sessions = profile_root / "codex" / "sessions"
    mutation = _insert_session_when_scandir_stops(monkeypatch, sessions)

    def create_isolated_session_directories(value, *_args):
        for agent in value["agents"]:
            store = profile_root / agent["id"]
            store.mkdir(parents=True)
            for location in e3.SESSION_LOCATIONS[agent["id"]]:
                path = store / location
                if location == "session_index.jsonl":
                    path.write_bytes(b"")
                else:
                    path.mkdir()
        return {agent["id"]: {} for agent in value["agents"]}

    monkeypatch.setattr(
        e3,
        "setup_host2_credentials",
        create_isolated_session_directories,
    )

    result = e3.run_e3(
        spec_path,
        Path("biv"),
        stable_test_root / "scratch",
    )

    assert mutation["inserted"]
    assert result.status is Status.INVALID
    assert result.detail == "e3-post-materialization-invalid"
    assert seen == ["pack"]


def test_run_e3_tripwire_red_stops_before_open(
    monkeypatch, tmp_path, stable_test_root
):
    repo = tmp_path / "repo"
    shutil.copytree(Path(__file__).resolve().parents[2] / "src", repo / "src")
    source = repo / "src/adapters/claude_code/claude_code.cpp"
    text = source.read_text(encoding="utf-8")
    old = '.globs = {"projects/*/*.jsonl"}'
    new = '.globs = {"projects/*/*.jsonl", "drift/**"}'
    assert text.count(old) == 1
    source.write_text(text.replace(old, new, 1), encoding="utf-8")

    spec_path, seen = _configure_exit_contract_case(
        monkeypatch,
        tmp_path,
        pack_result=_successful_pack(),
    )
    monkeypatch.setattr(e3, "_c1_default_repo_root", lambda: repo)

    result = e3.run_e3(spec_path, Path("biv"), stable_test_root / "scratch")

    assert result.status is Status.INVALID
    assert result.detail == "e3-post-materialization-invalid"
    assert seen == ["pack"]


def test_run_e3_c1_is_final_operation_immediately_before_open(
    monkeypatch, tmp_path, stable_test_root
):
    spec_path, _ = _configure_exit_contract_case(
        monkeypatch,
        tmp_path,
        pack_result=_successful_pack(),
    )
    events = []
    configured_spawn = e3._spawn

    def record_snapshot(*args):
        events.append("snapshot")
        return {}

    def record_tripwire():
        events.append("tripwire")
        return []

    def record_zero_session(*args):
        events.append("zero-session")
        return []

    def record_spawn(command, cwd, env):
        if len(command) > 1 and command[1] == "open":
            events.append("open")
        return configured_spawn(command, cwd, env)

    monkeypatch.setattr(e3, "snapshot_store", record_snapshot)
    monkeypatch.setattr(e3, "_c1_drift_tripwire_failures", record_tripwire)
    monkeypatch.setattr(e3, "_c1_zero_session_failures", record_zero_session)
    monkeypatch.setattr(e3, "_spawn", record_spawn)

    result = e3.run_e3(spec_path, Path("biv"), stable_test_root / "scratch")

    assert result.status is Status.PASS
    zero_index = events.index("zero-session")
    assert events[zero_index - 1 : zero_index + 2] == [
        "tripwire",
        "zero-session",
        "open",
    ]


@pytest.mark.parametrize("env_mode", ("empty", "absent"))
def test_e3_rejects_divergent_ambient_store_selector_pre_spend(
    monkeypatch, tmp_path, stable_test_root, env_mode
):
    monkeypatch.setenv("CLAUDE_CONFIG_DIR", str(tmp_path / "ambient-claude"))
    monkeypatch.setenv("CODEX_HOME", str(tmp_path / "ambient-codex"))
    calls = []

    def fake_spawn(command, cwd, env):
        calls.append(list(command))
        return SimpleNamespace(returncode=0, stdout="", stderr="")

    monkeypatch.setattr(e3, "_spawn", fake_spawn)
    spec_path = tmp_path / "e3.json"
    spec_path.write_text(json.dumps(_selector_spec(env_mode)), encoding="utf-8")

    result = e3.run_e3(spec_path, Path("biv"), stable_test_root / "scratch")

    assert calls == []
    assert result.status is Status.INVALID
    assert "CLAUDE_CONFIG_DIR" in result.detail
    assert "CODEX_HOME" in result.detail


def test_e3_dry_run_rejects_divergent_ambient_store_selector(
    monkeypatch, tmp_path, stable_test_root
):
    monkeypatch.setenv("CLAUDE_CONFIG_DIR", str(tmp_path / "ambient-claude"))
    monkeypatch.setenv("CODEX_HOME", str(tmp_path / "ambient-codex"))
    calls = []

    def fake_spawn(command, cwd, env):
        calls.append(list(command))
        return SimpleNamespace(returncode=0, stdout="", stderr="")

    monkeypatch.setattr(e3, "_spawn", fake_spawn)
    spec_path = tmp_path / "e3.json"
    spec_path.write_text(json.dumps(_valid_two_agent_spec()), encoding="utf-8")

    result = e3.run_e3(
        spec_path,
        Path("biv"),
        stable_test_root / "scratch",
        dry_run=True,
    )

    assert calls == []
    assert result.status is Status.INVALID
    assert "CLAUDE_CONFIG_DIR" in result.detail
    assert "CODEX_HOME" in result.detail


def test_live_codex_auth_probe_runs_ambient_no_store_override(
    monkeypatch, tmp_path, stable_test_root
):
    seen = {}
    calls = []

    def fake_spawn(command, cwd, env):
        calls.append(list(command))
        seen[tuple(command)] = dict(env)
        if command[1:] == ["--version"]:
            version = "2.1.210" if _agent_basename(command) == "claude" else "0.144.1"
            return SimpleNamespace(returncode=0, stdout=version, stderr="")
        if command[1:] == ["login", "status"] and _agent_basename(command) == "codex":
            return SimpleNamespace(returncode=1, stdout="", stderr="not logged in")
        return SimpleNamespace(returncode=0, stdout="", stderr="")

    monkeypatch.setattr(e3, "_spawn", fake_spawn)
    spec_path = tmp_path / "e3.json"
    spec_path.write_text(json.dumps(_live_override_spec()), encoding="utf-8")

    result = e3.run_e3(spec_path, Path("biv"), stable_test_root / "scratch")

    _assert_report_refused(result)
    assert "CODEX_HOME" not in seen[tuple(_resolved_agent_command("codex", "login", "status"))]
    assert calls == [
        _resolved_agent_command("codex", "--version"),
        _resolved_agent_command("claude-code", "--version"),
        _resolved_agent_command("codex", "login", "status"),
    ]


def test_live_claude_auth_probe_runs_ambient_no_store_override(
    monkeypatch, tmp_path, stable_test_root
):
    seen = {}
    calls = []

    def fake_spawn(command, cwd, env):
        calls.append(list(command))
        seen[tuple(command)] = dict(env)
        if command[1:] == ["--version"]:
            version = "2.1.210" if _agent_basename(command) == "claude" else "0.144.1"
            return SimpleNamespace(returncode=0, stdout=version, stderr="")
        if command[1:] == ["auth", "status"] and _agent_basename(command) == "claude":
            return SimpleNamespace(returncode=1, stdout="", stderr="not logged in")
        return SimpleNamespace(returncode=0, stdout="", stderr="")

    monkeypatch.setattr(e3, "_spawn", fake_spawn)
    spec_path = tmp_path / "e3.json"
    spec_path.write_text(json.dumps(_live_override_spec()), encoding="utf-8")

    result = e3.run_e3(spec_path, Path("biv"), stable_test_root / "scratch")

    _assert_report_refused(result)
    assert "CODEX_HOME" not in seen[tuple(_resolved_agent_command("codex", "--version"))]
    assert "CLAUDE_CONFIG_DIR" not in seen[tuple(_resolved_agent_command("claude-code", "auth", "status"))]
    assert calls == [
        _resolved_agent_command("codex", "--version"),
        _resolved_agent_command("claude-code", "--version"),
        _resolved_agent_command("codex", "login", "status"),
        _resolved_agent_command("claude-code", "auth", "status"),
    ]


def test_ordered_turns_require_all_sentinels_and_probe_in_order():
    turns = ["seed-one", "seed-two", "resume-probe"]

    assert ordered_turns_present("prefix seed-one middle seed-two tail resume-probe", turns)
    assert not ordered_turns_present("seed-two seed-one resume-probe", turns)
    assert not ordered_turns_present("seed-one seed-two", turns)


def test_owned_rollout_rejects_foreign_and_ambiguous_candidates(tmp_path):
    owned = tmp_path / "rollout-2026-07-11-owned-id.jsonl"
    owned.write_text('{"run_token":"mine"}\n', encoding="utf-8")

    assert select_owned_rollout(tmp_path, "owned-id", "mine") == owned

    duplicate = tmp_path / "nested" / owned.name
    duplicate.parent.mkdir()
    duplicate.write_text('{"run_token":"mine"}\n', encoding="utf-8")
    with pytest.raises(ValueError, match="exactly one"):
        select_owned_rollout(tmp_path, "owned-id", "mine")


def _host2_agents():
    return [
        {
            "id": "claude-code",
            "host2_profile": "claude",
            "env": {"CLAUDE_CONFIG_DIR": "{profile}"},
            "auth_status": ["claude", "auth", "status"],
            "version_command": ["claude", "--version"],
            "validated_version_prefixes": ["2.1."],
            "liveness_command": [
                "claude",
                "--model",
                "haiku",
                "--no-session-persistence",
                "-p",
                "Reply with one token: OK",
            ],
        },
        {
            "id": "codex",
            "host2_profile": "codex",
            "env": {"CODEX_HOME": "{profile}"},
            "auth_status": ["codex", "login", "status"],
            "version_command": ["codex", "--version"],
            "validated_version_prefixes": ["0.142.", "0.144."],
        },
    ]


def _by_id(agents):
    return {agent["id"]: agent for agent in agents}


def _agent_basename(command):
    return Path(command[0]).name


def _resolved_agent_command(agent_id, *args):
    return [TEST_AGENT_BINARIES[agent_id], *args]


def test_live_leg_env_construction_has_no_store_override():
    for agent in _host2_agents():
        assert e3._agent_env(agent, Path("/anything"), live=True) == {}


def test_host2_leg_env_construction_keeps_store_override():
    agents = _by_id(_host2_agents())
    root = Path("/tmp/e3-host2-profiles")

    assert e3._agent_env(agents["claude-code"], root / "claude", live=False) == {
        "CLAUDE_CONFIG_DIR": str(root / "claude")
    }
    assert e3._agent_env(agents["codex"], root / "codex", live=False) == {
        "CODEX_HOME": str(root / "codex")
    }


def test_live_login_instruction_is_ambient():
    agents = _by_id(_host2_agents())

    assert (
        e3._login_instruction(
            agents["claude-code"], Path("/x"), live=True,
            resolved_binary="/opt/agents/claude-real",
        )
        == "/opt/agents/claude-real auth login"
    )
    assert (
        e3._login_instruction(
            agents["codex"], Path("/x"), live=True,
            resolved_binary="/opt/agents/codex-real",
        )
        == "/opt/agents/codex-real login"
    )


def test_live_seed_boundary_receives_ambient_env_for_both_agents(
    monkeypatch, tmp_path, stable_test_root
):
    seen = {}
    version_envs = {}

    def fake_seed(
        agent, live_profile, seed_ws, spec, env, spawn, candidates, owned,
        resolved_binary=None,
    ):
        seen[agent["id"]] = dict(env)
        if len(seen) == 2:
            raise ValueError("stop-after-seed-loop")
        return tmp_path / "dummy.jsonl"

    def fake_spawn(command, cwd, env):
        if command[-1] == "--version":
            version_envs[_agent_basename(command)] = dict(env)
            version = "2.1.210" if _agent_basename(command) == "claude" else "0.144.1"
            return SimpleNamespace(returncode=0, stdout=version, stderr="")
        return SimpleNamespace(returncode=0, stdout="", stderr="")

    monkeypatch.setattr(e3, "_seed_agent", fake_seed)
    monkeypatch.setattr(e3, "_spawn", fake_spawn)
    spec_path = tmp_path / "e3.json"
    spec_path.write_text(json.dumps(_live_override_spec()), encoding="utf-8")

    result = e3.run_e3(spec_path, Path("biv"), stable_test_root / "scratch")

    _assert_report_refused(result)
    assert set(seen) == {"codex", "claude-code"}
    assert version_envs == {"codex": {}, "claude": {}}
    for env in seen.values():
        assert "CLAUDE_CONFIG_DIR" not in env
        assert "CODEX_HOME" not in env


@pytest.mark.parametrize(
    "start_ok,expected_verbs",
    [
        (True, ["seed", "continue"]),
        (False, ["seed", "retry", "continue", "continue"]),
    ],
)
def test_seed_agent_forwards_received_env_to_every_model_spawn(
    monkeypatch, tmp_path, start_ok, expected_verbs
):
    spec = e3.materialize_run_tokens(_live_override_spec())
    agent = _by_id(spec["agents"])["claude-code"]
    transcript = tmp_path / "s.jsonl"
    transcript.write_text("\n".join(spec["seed_turns"]) + "\n", encoding="utf-8")
    recorded = []

    def rec_spawn(command, cwd, env):
        recorded.append((list(command), dict(env)))
        return SimpleNamespace(returncode=0 if start_ok else 1, stdout="", stderr="")

    def fake_capture_attempt(root, pattern, run_token, command, path_proof=None):
        command()
        result = SimpleNamespace(returncode=0 if start_ok else 1)
        return result, None, [transcript], [transcript]

    def fake_capture_seed_leg(root, pattern, run_token, command, path_proof=None):
        command()
        return SimpleNamespace(returncode=0), transcript, []

    monkeypatch.setattr(e3, "_capture_attempt", fake_capture_attempt)
    monkeypatch.setattr(e3, "_capture_seed_leg", fake_capture_seed_leg)
    monkeypatch.setattr(
        e3, "_session_id_from_path", lambda agent_id, path: "fixed-id"
    )
    sentinel = {"AMBIENT_MARKER": "1"}

    result = e3._seed_agent(
        agent,
        tmp_path / "profile",
        tmp_path / "ws",
        spec,
        sentinel,
        rec_spawn,
        [],
        [],
    )

    assert result == transcript
    assert [command[1] for command, _ in recorded] == expected_verbs
    for _, env in recorded:
        assert env == sentinel


def _host2_agent_id(command):
    matches = [
        agent_id
        for agent_id, binary in TEST_AGENT_BINARIES.items()
        if command[0] == binary
    ]
    assert len(matches) == 1, f"unexpected host2 agent binary: {command[0]}"
    return matches[0]


def _assert_host2_binary_ledger(commands, expected_agents):
    assert [command[0] for command in commands] == [
        TEST_AGENT_BINARIES[agent_id] for agent_id in expected_agents
    ]


def _host2_binaries():
    return dict(TEST_AGENT_BINARIES)


def _host2_version_output(command):
    return "2.1.202" if _host2_agent_id(command) == "claude-code" else "0.142.5"


def test_host2_binary_fixtures_are_explicit_absolute_and_path_independent(monkeypatch):
    def unexpected_which(executable):
        raise AssertionError(f"host2 fixture consulted PATH for {executable}")

    monkeypatch.setattr(e3.shutil, "which", unexpected_which)

    assert _host2_binaries() == TEST_AGENT_BINARIES
    assert all(Path(binary).is_absolute() for binary in _host2_binaries().values())


@pytest.mark.parametrize("profile_topology", ("sibling", "nested"))
def test_setup_host2_credentials_constructs_profiles_and_runs_liveness(
    tmp_path, profile_topology
):
    host2 = tmp_path / "host two"
    profile_root = (
        tmp_path / "host2-profile"
        if profile_topology == "sibling"
        else host2 / "profiles"
    )
    calls = []

    def fake_spawn(command, cwd, env):
        _host2_agent_id(command)
        calls.append(command)
        return SimpleNamespace(
            returncode=0,
            stdout=_host2_version_output(command),
            stderr="",
        )

    envs = e3.setup_host2_credentials(
        {"agents": _host2_agents()},
        host2,
        profile_root,
        _host2_binaries(),
        fake_spawn,
        e3._CredentialScanner(),
        [],
        {},
    )

    assert (host2 / "home").is_dir()
    assert (profile_root / "claude").is_dir()
    assert (profile_root / "codex").is_dir()
    assert set(envs) == {"claude-code", "codex"}
    _assert_host2_binary_ledger(
        calls,
        ["claude-code", "codex", "claude-code", "codex", "claude-code"],
    )
    assert _agent_basename(calls[-1]) == "claude"
    assert "--no-session-persistence" in calls[-1]
    assert "-p" in calls[-1]


@pytest.mark.parametrize("symlink_case", ("leaf", "ancestor"))
def test_setup_host2_credentials_refuses_symlinked_profile_topology_before_spawn(
    monkeypatch, tmp_path, symlink_case
):
    host2 = tmp_path / "host2"
    outside = tmp_path / "outside-profile"
    outside.mkdir()
    canary = outside / "canary"
    canary.write_text("outside-unchanged", encoding="utf-8")
    if symlink_case == "leaf":
        profile_root = tmp_path / "host2-profile"
        profile_root.symlink_to(outside, target_is_directory=True)
    else:
        ancestor = tmp_path / "profile-parent"
        ancestor.symlink_to(outside, target_is_directory=True)
        profile_root = ancestor / "profiles"
    spawn_calls = []
    materializer_calls = []

    def unavailable_materializer(*args, **kwargs):
        materializer_calls.append((args, kwargs))
        return e3.CredentialResult(e3.CredentialStatus.SOURCE_MISSING)

    monkeypatch.setattr(e3, "materialize_keychain_credential", unavailable_materializer)
    monkeypatch.setattr(e3, "materialize_file_credential", unavailable_materializer)

    with pytest.raises(ValueError, match="host2 profile topology unavailable"):
        e3.setup_host2_credentials(
            {"agents": _host2_agents()},
            host2,
            profile_root,
            _host2_binaries(),
            lambda command, *_args: (
                spawn_calls.append(list(command))
                or SimpleNamespace(
                    returncode=0,
                    stdout=_host2_version_output(command),
                    stderr="",
                )
            ),
            e3._CredentialScanner(),
            [],
            {},
        )

    assert spawn_calls == []
    assert materializer_calls == []
    assert canary.read_text(encoding="utf-8") == "outside-unchanged"
    assert list(outside.iterdir()) == [canary]


def test_runtime_credential_sentinels_are_fresh_prefixed_and_cardinality_only(
    monkeypatch,
):
    configured = [
        "bive3-sentinel-" + "a" * 64,
        "documented-durable-sentinel",
    ]
    generated = iter(("1" * 64, "2" * 64, "3" * 64, "4" * 64))
    monkeypatch.setattr(e3.secrets, "token_hex", lambda size: next(generated))

    first = e3._runtime_credential_sentinels(len(configured))
    second = e3._runtime_credential_sentinels(len(configured))

    assert first == [
        "bive3-sentinel-" + "1" * 64,
        "bive3-sentinel-" + "2" * 64,
    ]
    assert second == [
        "bive3-sentinel-" + "3" * 64,
        "bive3-sentinel-" + "4" * 64,
    ]
    assert first != second
    assert not set(first + second).intersection(configured)


def test_credential_scanner_adds_only_bounded_sentinel_representations():
    scanner = e3._CredentialScanner()
    sentinel = "bive3-sentinel-" + "a" * 64 + "/"

    scanner.add_sentinel(sentinel)

    representations = e3._sentinel_representations(sentinel)
    canonical, solidus, ascii_u = representations[:3]
    assert canonical != solidus
    assert canonical != ascii_u
    assert solidus != ascii_u
    assert all(scanner.scan_bytes(value) for value in representations)
    assert len(scanner._values) == len(representations)


def test_setup_host2_credentials_materializes_both_credentials_without_seeding_scanner(
    monkeypatch, tmp_path
):
    host2 = tmp_path / "host2"
    profile_root = host2 / "profiles"
    claude_access = "setup-claude-access-leaf"
    claude_refresh = "setup-claude-refresh-leaf"
    codex_api_key = "setup-codex-api-key-leaf"
    codex_access = "setup-codex-access-leaf"
    codex_refresh = "setup-codex-refresh-leaf"
    codex_id = "setup-codex-id-leaf"
    claude_nested = 'setup-claude nested "value"'
    codex_nested = "setup-codex nested\\value\n"
    claude_bytes = json.dumps(
        {
            "claudeAiOauth": {
                "accessToken": claude_access,
                "refreshToken": claude_refresh,
            },
            "metadata": {"history": [{"credential": claude_nested}]},
        },
        separators=(",", ":"),
    ).encode()
    codex_bytes = json.dumps(
        {
            "OPENAI_API_KEY": codex_api_key,
            "tokens": {
                "access_token": codex_access,
                "refresh_token": codex_refresh,
                "id_token": codex_id,
                "expires_at": 123,
                "nullable": None,
                "empty": "",
            },
            "metadata": {"history": [[{"credential": codex_nested}]]},
        },
        separators=(",", ":"),
    ).encode()
    scanner = e3._CredentialScanner()
    scanner.add_sentinel("bive3-sentinel-" + "f" * 64)
    scanner_values = [bytes(value) for value in scanner._values]
    child_outputs = []
    ambient_snapshots = {}
    calls = []

    def fake_keychain(service, account, dest, **kwargs):
        assert service == "Claude Code-credentials"
        assert account == "host2-test-user"
        Path(dest).parent.mkdir(parents=True, exist_ok=True)
        Path(dest).write_bytes(claude_bytes)
        Path(dest).chmod(0o600)
        return e3.CredentialResult(e3.CredentialStatus.OK, Path(dest))

    def fake_file(source, dest, **kwargs):
        assert source == Path("~/.codex/auth.json").expanduser()
        Path(dest).parent.mkdir(parents=True, exist_ok=True)
        Path(dest).write_bytes(codex_bytes)
        Path(dest).chmod(0o600)
        return e3.CredentialResult(
            e3.CredentialStatus.OK,
            Path(dest),
            e3.SourceIdentity(1, 2, len(codex_bytes), "digest"),
        )

    def fake_spawn(command, cwd, env):
        calls.append(list(command))
        if command[1:] == ["--version"]:
            return SimpleNamespace(
                returncode=0, stdout=_host2_version_output(command), stderr=""
            )
        if "-p" in command:
            return SimpleNamespace(returncode=0, stdout="OK", stderr="")
        return SimpleNamespace(returncode=0, stdout="authenticated", stderr="")

    monkeypatch.setattr(e3.getpass, "getuser", lambda: "host2-test-user")
    monkeypatch.setattr(e3, "materialize_keychain_credential", fake_keychain)
    monkeypatch.setattr(e3, "materialize_file_credential", fake_file)

    envs = e3.setup_host2_credentials(
        {"agents": _host2_agents()},
        host2,
        profile_root,
        _host2_binaries(),
        fake_spawn,
        scanner,
        child_outputs,
        ambient_snapshots,
    )

    claude_dest = profile_root / "claude" / ".credentials.json"
    codex_dest = profile_root / "codex" / "auth.json"
    assert set(envs) == {"claude-code", "codex"}
    assert claude_dest.read_bytes() == claude_bytes
    assert codex_dest.read_bytes() == codex_bytes
    assert claude_dest.stat().st_mode & 0o777 == 0o600
    assert codex_dest.stat().st_mode & 0o777 == 0o600
    assert not (profile_root / "codex" / "config.toml").exists()
    assert [bytes(value) for value in scanner._values] == scanner_values
    assert not scanner.scan_bytes(claude_bytes)
    assert not scanner.scan_bytes(codex_bytes)
    for leaf in (
        claude_access,
        claude_refresh,
        codex_api_key,
        codex_access,
        codex_refresh,
        codex_id,
        claude_nested,
        codex_nested,
    ):
        assert not scanner.scan_text(leaf)
        assert not scanner.scan_bytes(json.dumps(leaf)[1:-1].encode("ascii"))
    assert ambient_snapshots["codex-auth.json"] == e3.SourceIdentity(
        1, 2, len(codex_bytes), "digest"
    )
    assert child_outputs == [b"authenticated", b"authenticated", b"OK"]
    assert all(command[0].startswith("/") for command in calls)
    owned_values = list(scanner._values)
    scanner.drop()
    assert scanner._values == []
    assert all(value == bytearray(len(value)) for value in owned_values)


def test_setup_host2_credentials_guards_each_materialized_destination_without_reread(
    monkeypatch, tmp_path
):
    host2 = tmp_path / "host2"
    profile_root = host2 / "profiles"
    claude_raw = b'{"claudeAiOauth":{"accessToken":"real-claude-value"}}'
    codex_raw = b'{"tokens":{"access_token":"real-codex-value"}}'
    identity = e3.SourceIdentity(1, 2, len(codex_raw), "source-digest")
    lifecycle = []
    scanner = e3._CredentialScanner()
    scanner.add_sentinel("bive3-sentinel-" + "a" * 64)
    scanner_values = [bytes(value) for value in scanner._values]
    guards = {}
    destinations = {
        profile_root / "claude" / ".credentials.json",
        profile_root / "codex" / "auth.json",
    }

    def materialize(raw, credential_id, dest, source_identity=None):
        lifecycle.append(("materialize", credential_id))
        path = Path(dest)
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(raw)
        return e3.CredentialResult(
            e3.CredentialStatus.OK,
            path,
            source_identity,
        )

    monkeypatch.setattr(
        e3,
        "materialize_keychain_credential",
        lambda _service, _account, dest, **_kwargs: materialize(
            claude_raw,
            "claude-code",
            dest,
        ),
    )
    monkeypatch.setattr(
        e3,
        "materialize_file_credential",
        lambda _source, dest, **_kwargs: materialize(
            codex_raw,
            "codex",
            dest,
            identity,
        ),
    )
    real_guard = e3._credential_guard

    def recording_guard(path):
        credential_id = (
            "claude-code" if Path(path).name == ".credentials.json" else "codex"
        )
        lifecycle.append(("guard", credential_id))
        return real_guard(path)

    monkeypatch.setattr(e3, "_credential_guard", recording_guard)
    monkeypatch.setattr(
        e3,
        "_read_regular_file_nofollow",
        lambda *_args, **_kwargs: pytest.fail("credential destination reread"),
    )
    real_path_open = e3.Path.open

    def refuse_destination_read(path, mode="r", *args, **kwargs):
        if Path(path) in destinations and "r" in mode:
            pytest.fail("credential destination reread")
        return real_path_open(path, mode, *args, **kwargs)

    monkeypatch.setattr(e3.Path, "open", refuse_destination_read)

    envs = e3.setup_host2_credentials(
        {"agents": _host2_agents()},
        host2,
        profile_root,
        _host2_binaries(),
        lambda command, *_args: SimpleNamespace(
            returncode=0,
            stdout=_host2_version_output(command)
            if command[1:] == ["--version"]
            else "OK",
            stderr="",
        ),
        scanner,
        [],
        {},
        guards,
    )

    assert set(envs) == {"claude-code", "codex"}
    assert lifecycle == [
        ("materialize", "claude-code"),
        ("guard", "claude-code"),
        ("materialize", "codex"),
        ("guard", "codex"),
    ]
    assert set(guards) == {"claude-code", "codex"}
    assert [bytes(value) for value in scanner._values] == scanner_values
    assert not scanner.scan_bytes(claude_raw)
    assert not scanner.scan_bytes(codex_raw)


def test_real_credential_scanner_seed_helpers_are_retired():
    assert not hasattr(e3, "_read_credential_destination_nofollow")
    assert not hasattr(e3, "_seed_credential_scanner")


def test_setup_host2_credentials_refuses_codex_config_toml(monkeypatch, tmp_path):
    codex_bytes = b'{"tokens":{"access_token":"fixture"}}'
    identity = e3.SourceIdentity(1, 2, len(codex_bytes), "fixture")
    scanner = e3._CredentialScanner()
    ambient_snapshots = {}

    def fake_file(_source, dest, **_kwargs):
        path = Path(dest)
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(codex_bytes)
        (path.parent / "config.toml").write_text("unexpected", encoding="utf-8")
        return e3.CredentialResult(
            e3.CredentialStatus.OK,
            path,
            identity,
        )

    monkeypatch.setattr(e3, "materialize_file_credential", fake_file)
    with pytest.raises(ValueError, match="host2 credential unavailable: codex"):
        e3.setup_host2_credentials(
            {"agents": _host2_agents()},
            tmp_path / "host2",
            tmp_path / "profiles",
            _host2_binaries(),
            lambda command, *_args: SimpleNamespace(
                returncode=0, stdout=_host2_version_output(command), stderr=""
            ),
            scanner,
            [],
            ambient_snapshots,
        )

    assert not scanner.scan_bytes(codex_bytes)
    assert ambient_snapshots["codex-auth.json"] == identity


@pytest.mark.parametrize(
    ("failed", "expected_error"),
    (
        (
            {"claude-code", "codex"},
            "host2 credential unavailable: claude-code, codex",
        ),
        ({"claude-code"}, "host2 credential unavailable: claude-code"),
        ({"codex"}, "host2 credential unavailable: codex"),
    ),
)
def test_setup_host2_credentials_probes_all_agents_before_rejecting(
    tmp_path, failed, expected_error
):
    auth_seen = []
    calls = []

    def fake_spawn(command, cwd, env):
        calls.append(list(command))
        agent = _host2_agent_id(command)
        if command[-1] == "status":
            auth_seen.append(agent)
            return SimpleNamespace(
                returncode=1 if agent in failed else 0,
                stdout="sensitive-auth-stdout",
                stderr="sensitive-auth-stderr",
            )
        return SimpleNamespace(returncode=0, stdout=_host2_version_output(command), stderr="")

    with pytest.raises(ValueError) as exc_info:
        e3.setup_host2_credentials(
            {"agents": _host2_agents()},
            tmp_path / "host2",
            tmp_path / "profiles",
            _host2_binaries(),
            fake_spawn,
            e3._CredentialScanner(),
            [],
            {},
        )
    assert str(exc_info.value) == expected_error
    assert auth_seen == ["claude-code", "codex"]
    assert [command[1:] for command in calls[:2]] == [["--version"], ["--version"]]
    assert [command[1:] for command in calls[2:]] == [
        ["auth", "status"], ["login", "status"],
    ]
    _assert_host2_binary_ledger(
        calls,
        ["claude-code", "codex", "claude-code", "codex"],
    )


def test_setup_host2_credentials_auth_exception_still_probes_all_agents(tmp_path):
    auth_seen = []
    child_outputs = []
    leaked = b'{"tokens":{"access_token":"fixture"}}'

    def fake_spawn(command, cwd, env):
        agent = _host2_agent_id(command)
        if command[-1] == "status":
            auth_seen.append(agent)
            if agent == "claude-code":
                raise e3.subprocess.TimeoutExpired(
                    command,
                    120,
                    output=leaked,
                    stderr=b"exceptional-auth-stderr",
                )
            return SimpleNamespace(
                returncode=0,
                stdout="codex-auth-stdout",
                stderr="codex-auth-stderr",
            )
        return SimpleNamespace(
            returncode=0,
            stdout=_host2_version_output(command),
            stderr="",
        )

    with pytest.raises(
        ValueError,
        match=r"^host2 credential unavailable: claude-code$",
    ):
        e3.setup_host2_credentials(
            {"agents": _host2_agents()},
            tmp_path / "host2",
            tmp_path / "profiles",
            _host2_binaries(),
            fake_spawn,
            e3._CredentialScanner(),
            child_outputs,
            {},
        )

    assert auth_seen == ["claude-code", "codex"]
    assert child_outputs == [
        leaked + b"exceptional-auth-stderr",
        b"codex-auth-stdoutcodex-auth-stderr",
    ]


def test_spawn_retry_captures_exception_and_retry_outputs_in_order(tmp_path):
    command = ["/fake/agent", "resume"]
    child_outputs = []
    calls = 0

    def fake_spawn(command, cwd, env):
        nonlocal calls
        calls += 1
        if calls == 1:
            raise e3.subprocess.TimeoutExpired(
                command,
                120,
                output=b"first-attempt-stdout",
                stderr=b"first-attempt-stderr",
            )
        return SimpleNamespace(
            returncode=0,
            stdout="retry-stdout",
            stderr="retry-stderr",
        )

    captured = e3._spawn_with_capture(fake_spawn, child_outputs)
    result = e3._spawn_retry_with(command, tmp_path, {}, captured)

    assert result.returncode == 0
    assert child_outputs == [
        b"first-attempt-stdoutfirst-attempt-stderr",
        b"retry-stdoutretry-stderr",
    ]


def test_setup_host2_credentials_rejects_failed_claude_liveness(tmp_path):
    calls = []

    def fake_spawn(command, cwd, env):
        calls.append(list(command))
        agent = _host2_agent_id(command)
        if agent == "claude-code" and "-p" in command:
            return SimpleNamespace(returncode=1, stdout="", stderr="offline")
        return SimpleNamespace(
            returncode=0,
            stdout=_host2_version_output(command),
            stderr="",
        )

    with pytest.raises(ValueError, match="liveness"):
        e3.setup_host2_credentials(
            {"agents": _host2_agents()}, tmp_path / "host2", tmp_path / "profiles",
            _host2_binaries(), fake_spawn, e3._CredentialScanner(), [], {}
        )
    _assert_host2_binary_ledger(
        calls,
        [
            "claude-code", "codex", "claude-code", "codex",
            "claude-code", "claude-code",
        ],
    )


def test_setup_host2_credentials_rejects_multi_token_claude_liveness(tmp_path):
    calls = []

    def fake_spawn(command, cwd, env):
        calls.append(list(command))
        agent = _host2_agent_id(command)
        output = (
            "too many tokens"
            if agent == "claude-code" and "-p" in command
            else _host2_version_output(command)
        )
        return SimpleNamespace(returncode=0, stdout=output, stderr="")

    with pytest.raises(ValueError, match="one token"):
        e3.setup_host2_credentials(
            {"agents": _host2_agents()}, tmp_path / "host2", tmp_path / "profiles",
            _host2_binaries(), fake_spawn, e3._CredentialScanner(), [], {}
        )
    _assert_host2_binary_ledger(
        calls,
        [
            "claude-code", "codex", "claude-code", "codex",
            "claude-code", "claude-code",
        ],
    )


def test_setup_host2_credentials_retries_claude_liveness_once(tmp_path):
    liveness_calls = 0
    calls = []

    def fake_spawn(command, cwd, env):
        nonlocal liveness_calls
        calls.append(list(command))
        agent = _host2_agent_id(command)
        if agent == "claude-code" and "-p" in command:
            liveness_calls += 1
            return SimpleNamespace(
                returncode=1 if liveness_calls == 1 else 0,
                stdout="" if liveness_calls == 1 else "OK",
                stderr="transient" if liveness_calls == 1 else "",
            )
        return SimpleNamespace(
            returncode=0,
            stdout=_host2_version_output(command),
            stderr="",
        )

    e3.setup_host2_credentials(
        {"agents": _host2_agents()}, tmp_path / "host2", tmp_path / "profiles",
        _host2_binaries(), fake_spawn, e3._CredentialScanner(), [], {}
    )
    assert liveness_calls == 2
    _assert_host2_binary_ledger(
        calls,
        [
            "claude-code", "codex", "claude-code", "codex",
            "claude-code", "claude-code",
        ],
    )


@pytest.mark.parametrize("first_failure", ["multi-token", "timeout", "oserror"])
def test_setup_host2_credentials_retries_invalid_or_exceptional_liveness_once(tmp_path, first_failure):
    liveness_calls = 0
    calls = []

    def fake_spawn(command, cwd, env):
        nonlocal liveness_calls
        calls.append(list(command))
        agent = _host2_agent_id(command)
        if agent == "claude-code" and "-p" in command:
            liveness_calls += 1
            if liveness_calls == 1 and first_failure == "timeout":
                raise e3.subprocess.TimeoutExpired(command, 120)
            if liveness_calls == 1 and first_failure == "oserror":
                raise OSError("spawn failed")
            output = "too many tokens" if liveness_calls == 1 else "OK"
            return SimpleNamespace(returncode=0, stdout=output, stderr="")
        return SimpleNamespace(
            returncode=0,
            stdout=_host2_version_output(command),
            stderr="",
        )

    e3.setup_host2_credentials(
        {"agents": _host2_agents()}, tmp_path / "host2", tmp_path / "profiles",
        _host2_binaries(), fake_spawn, e3._CredentialScanner(), [], {}
    )
    assert liveness_calls == 2
    _assert_host2_binary_ledger(
        calls,
        [
            "claude-code", "codex", "claude-code", "codex",
            "claude-code", "claude-code",
        ],
    )


@pytest.mark.parametrize("first_failure", ["empty", "timeout", "oserror"])
def test_model_reply_retry_covers_semantic_and_exceptional_failure(tmp_path, first_failure):
    calls = 0

    def fake_spawn(command, cwd, env):
        nonlocal calls
        calls += 1
        if calls == 1 and first_failure == "timeout":
            raise e3.subprocess.TimeoutExpired(command, 120)
        if calls == 1 and first_failure == "oserror":
            raise OSError("spawn failed")
        return SimpleNamespace(returncode=0, stdout="" if calls == 1 else "reply", stderr="")

    result = e3._spawn_retry_with(
        ["agent", "resume"], tmp_path, {}, fake_spawn,
        lambda value: value.returncode == 0 and bool(value.stdout.strip()),
    )
    assert result.stdout == "reply"
    assert calls == 2


@pytest.mark.parametrize("pattern", ["*.jsonl", "rollout-*.jsonl"])
@pytest.mark.parametrize("case", ["clean", "foreign-new", "foreign-modified", "duplicate-owned"])
def test_capture_window_requires_one_owned_and_zero_foreign_candidates(tmp_path, pattern, case):
    root = tmp_path / "store"
    root.mkdir()
    foreign = root / ("rollout-foreign.jsonl" if pattern.startswith("rollout") else "foreign.jsonl")
    if case == "foreign-modified":
        foreign.write_text("old", encoding="utf-8")
    before = capture_inventory(root, pattern)
    owned = root / ("rollout-owned.jsonl" if pattern.startswith("rollout") else "owned.jsonl")
    owned.write_text("TOKEN", encoding="utf-8")
    if case == "foreign-new":
        foreign.write_text("foreign", encoding="utf-8")
    elif case == "foreign-modified":
        foreign.write_text("changed", encoding="utf-8")
    elif case == "duplicate-owned":
        duplicate = root / "nested" / owned.name
        duplicate.parent.mkdir()
        duplicate.write_text("TOKEN", encoding="utf-8")
    after = capture_inventory(root, pattern)

    if case == "clean":
        selected, candidates = classify_capture(before, after, "TOKEN")
        assert selected == owned
        assert candidates == [owned]
    else:
        with pytest.raises(ValueError, match="capture ambiguity"):
            classify_capture(before, after, "TOKEN")


def test_cleanup_report_discloses_foreign_but_never_suggests_it_for_cleanup(tmp_path):
    owned = tmp_path / "owned.jsonl"
    foreign = tmp_path / "foreign.jsonl"
    report = format_cleanup_report([owned, foreign], [owned])
    disclosure, cleanup = report.split("Ownership-proven cleanup candidates (not deleted):\n")
    assert str(foreign) in disclosure
    assert str(foreign) not in cleanup
    assert str(owned) in cleanup


def test_failed_seed_leg_still_classifies_every_changed_candidate(tmp_path):
    root = tmp_path / "store"
    root.mkdir()
    owned = root / "owned.jsonl"
    foreign = root / "foreign.jsonl"

    def failed_command():
        owned.write_text("TOKEN", encoding="utf-8")
        foreign.write_text("other", encoding="utf-8")
        return SimpleNamespace(returncode=1, stdout="", stderr="failed")

    with pytest.raises(e3.CaptureAmbiguity) as caught:
        e3._capture_seed_leg(root, "*.jsonl", "TOKEN", failed_command)
    assert caught.value.candidates == [foreign, owned]


@pytest.mark.parametrize("foreign_write", [False, True])
def test_exceptional_seed_leg_still_classifies_every_changed_candidate(tmp_path, foreign_write):
    root = tmp_path / "store"
    root.mkdir()
    owned = root / "owned.jsonl"
    foreign = root / "foreign.jsonl"

    def timed_out_command():
        owned.write_text("TOKEN", encoding="utf-8")
        if foreign_write:
            foreign.write_text("other", encoding="utf-8")
        raise e3.subprocess.TimeoutExpired(["agent", "seed"], 120)

    expected = e3.CaptureAmbiguity if foreign_write else e3.CaptureCommandError
    with pytest.raises(expected) as caught:
        e3._capture_seed_leg(root, "*.jsonl", "TOKEN", timed_out_command)
    assert caught.value.candidates == ([foreign, owned] if foreign_write else [owned])


@pytest.mark.parametrize("failure", ["nonzero", "timeout", "oserror", "foreign"])
def test_first_leg_owned_path_survives_every_continuation_failure(tmp_path, failure):
    root = tmp_path / "store"
    root.mkdir()
    workspace = tmp_path / "workspace"
    workspace.mkdir()
    session_id = "aaaaaaaa-1111-4111-8111-111111111111"
    transcript = _scoped_claude_transcript(root, workspace, session_id)
    foreign = root / "foreign.jsonl"
    calls = 0

    def fake_spawn(command, cwd, env):
        nonlocal calls
        calls += 1
        if calls == 1:
            transcript.write_text("TOKEN\nseed-one\n", encoding="utf-8")
            return SimpleNamespace(returncode=0, stdout="", stderr="")
        transcript.write_text("TOKEN\nseed-one\nseed-two\n", encoding="utf-8")
        if failure == "nonzero":
            return SimpleNamespace(returncode=1, stdout="", stderr="failed")
        if failure == "timeout":
            raise e3.subprocess.TimeoutExpired(command, 120)
        if failure == "oserror":
            raise OSError("spawn failed")
        foreign.write_text("other", encoding="utf-8")
        return SimpleNamespace(returncode=0, stdout="", stderr="")

    agent = {
        "id": "claude-code",
        "ownership_glob": "*.jsonl",
        "run_token": "TOKEN",
        "seed_start_command": ["agent", "start"],
        "seed_retry_resume_command": ["agent", "retry-resume", "{id}"],
        "seed_continue_command": ["agent", "continue", "{id}"],
    }
    spec = {"seed_turns": ["seed-one", "seed-two"]}
    candidates = []
    owned = []

    with pytest.raises(ValueError):
        e3._seed_agent(agent, root, workspace, spec, {}, fake_spawn, candidates, owned)

    report = format_cleanup_report(candidates, owned)
    disclosure, cleanup = report.split("Ownership-proven cleanup candidates (not deleted):\n")
    assert str(transcript) in cleanup
    if failure == "foreign":
        assert str(foreign) in disclosure
        assert str(foreign) not in cleanup


def _retry_seed_agent():
    return {
        "id": "claude-code",
        "ownership_glob": "*.jsonl",
        "run_token": "TOKEN",
        "seed_start_command": ["agent", "start"],
        "seed_retry_resume_command": ["agent", "retry-resume", "{id}"],
        "seed_continue_command": ["agent", "continue", "{id}"],
    }


def _scoped_claude_transcript(root, workspace, session_id):
    project = root / "projects" / e3._project_key(workspace)
    project.mkdir(parents=True, exist_ok=True)
    return project / f"{session_id}.jsonl"


def test_runtime_tokens_are_distinct_between_invocations():
    spec = {
        "agents": [
            {"id": "claude-code", "run_token_prefix": "BIV_E3_CLAUDE_RUN_TOKEN"},
            {"id": "codex", "run_token_prefix": "BIV_E3_CODEX_RUN_TOKEN"},
        ]
    }

    first = e3.materialize_run_tokens(spec)
    second = e3.materialize_run_tokens(spec)

    assert [agent["run_token"] for agent in first["agents"]] != [
        agent["run_token"] for agent in second["agents"]
    ]
    assert all("run_token" not in agent for agent in spec["agents"])


@pytest.mark.parametrize(
    "foreign_token",
    [
        "BIV_E3_CLAUDE_RUN_TOKEN",
        "THIS_INVOCATION_TOKEN"[:-1],
        "THIS_INVOCATION_TOKEN_SUFFIX",
        "OTHER_INVOCATION_TOKEN",
    ],
)
def test_failed_empty_start_never_adopts_non_exact_invocation_token(tmp_path, foreign_token):
    root = tmp_path / "store"
    root.mkdir()
    workspace = tmp_path / "workspace"
    workspace.mkdir()
    session_id = "aaaaaaaa-1111-4111-8111-111111111111"
    transcript = _scoped_claude_transcript(root, workspace, session_id)
    commands = []

    def fake_spawn(command, cwd, env):
        commands.append(command)
        transcript.write_text(f"{foreign_token}\nseed-one\n", encoding="utf-8")
        return SimpleNamespace(returncode=1, stdout="", stderr="transient")

    agent = {
        **_retry_seed_agent(),
        "run_token_prefix": "BIV_E3_CLAUDE_RUN_TOKEN",
        "run_token": "THIS_INVOCATION_TOKEN",
    }
    candidates = []
    owned = []
    with pytest.raises(ValueError, match="capture ambiguity"):
        e3._seed_agent(
            agent, root, workspace, {"seed_turns": ["seed-one", "seed-two"]},
            {}, fake_spawn, candidates, owned,
        )

    assert len(commands) == 1
    assert candidates == [transcript]
    assert owned == []


def test_failed_start_resumes_candidate_with_this_invocations_exact_token(tmp_path):
    root = tmp_path / "store"
    root.mkdir()
    workspace = tmp_path / "workspace"
    workspace.mkdir()
    session_id = "aaaaaaaa-1111-4111-8111-111111111111"
    transcript = _scoped_claude_transcript(root, workspace, session_id)
    commands = []

    def fake_spawn(command, cwd, env):
        commands.append(command)
        if len(commands) == 1:
            transcript.write_text("THIS_INVOCATION_TOKEN\nseed-one\n", encoding="utf-8")
            return SimpleNamespace(returncode=1, stdout="", stderr="transient")
        if len(commands) == 2:
            transcript.write_text("THIS_INVOCATION_TOKEN\nseed-one\nretry-reply\n", encoding="utf-8")
            return SimpleNamespace(returncode=0, stdout="reply", stderr="")
        transcript.write_text("THIS_INVOCATION_TOKEN\nseed-one\nseed-two\n", encoding="utf-8")
        return SimpleNamespace(returncode=0, stdout="reply", stderr="")

    agent = {
        **_retry_seed_agent(),
        "run_token_prefix": "BIV_E3_CLAUDE_RUN_TOKEN",
        "run_token": "THIS_INVOCATION_TOKEN",
        "seed_start_command": ["agent", "start", "{run_token}"],
        "seed_retry_resume_command": ["agent", "retry-resume", "{id}", "{run_token}"],
        "seed_continue_command": ["agent", "continue", "{id}", "{run_token}"],
    }
    selected = e3._seed_agent(
        agent, root, workspace,
        {"id": "scenario-id", "seed_turns": ["seed-one", "seed-two"]},
        {}, fake_spawn, [], [],
    )

    assert selected == transcript
    assert commands[1] == ["agent", "retry-resume", session_id, "THIS_INVOCATION_TOKEN"]
    assert commands[2] == ["agent", "continue", session_id, "THIS_INVOCATION_TOKEN"]


def test_claude_token_outside_seed_workspace_project_is_foreign(tmp_path):
    root = tmp_path / "store"
    root.mkdir()
    workspace = tmp_path / "workspace"
    workspace.mkdir()
    foreign_project = root / "projects" / "foreign-workspace"
    foreign_project.mkdir(parents=True)
    transcript = foreign_project / "aaaaaaaa-1111-4111-8111-111111111111.jsonl"
    calls = 0

    def fake_spawn(command, cwd, env):
        nonlocal calls
        calls += 1
        transcript.write_text("THIS_INVOCATION_TOKEN\nseed-one\n", encoding="utf-8")
        return SimpleNamespace(returncode=1, stdout="", stderr="transient")

    agent = {
        **_retry_seed_agent(),
        "run_token": "THIS_INVOCATION_TOKEN",
    }
    candidates = []
    owned = []
    with pytest.raises(ValueError, match="capture ambiguity"):
        e3._seed_agent(
            agent, root, workspace, {"seed_turns": ["seed-one", "seed-two"]},
            {}, fake_spawn, candidates, owned,
        )

    assert calls == 1
    assert candidates == [transcript]
    assert owned == []


@pytest.mark.parametrize("agent_id", ["claude-code", "codex"])
def test_capture_path_proof_rejects_malformed_session_uuid(tmp_path, agent_id):
    root = tmp_path / "store"
    workspace = tmp_path / "workspace"
    malformed = "xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx"
    if agent_id == "claude-code":
        path = root / "projects" / e3._project_key(workspace) / f"{malformed}.jsonl"
    else:
        path = root / "sessions" / f"rollout-2026-07-11-{malformed}.jsonl"

    assert not e3._capture_path_proof(agent_id, path, root, workspace)


@pytest.mark.parametrize("first_shape", ["wrote-owned", "wrote-nothing"])
def test_first_seed_retry_resumes_owned_or_restarts_empty_window(tmp_path, first_shape):
    root = tmp_path / "store"
    root.mkdir()
    workspace = tmp_path / "workspace"
    workspace.mkdir()
    session_id = "aaaaaaaa-1111-4111-8111-111111111111"
    transcript = _scoped_claude_transcript(root, workspace, session_id)
    commands = []

    def fake_spawn(command, cwd, env):
        commands.append(command)
        if len(commands) == 1:
            if first_shape == "wrote-owned":
                transcript.write_text("TOKEN\nseed-one\n", encoding="utf-8")
            return SimpleNamespace(returncode=1, stdout="", stderr="transient")
        if len(commands) == 2:
            transcript.write_text("TOKEN\nseed-one\nretry-reply\n", encoding="utf-8")
            return SimpleNamespace(returncode=0, stdout="reply", stderr="")
        transcript.write_text("TOKEN\nseed-one\nseed-two\n", encoding="utf-8")
        return SimpleNamespace(returncode=0, stdout="reply", stderr="")

    candidates = []
    owned = []
    selected = e3._seed_agent(
        _retry_seed_agent(), root, workspace, {"seed_turns": ["seed-one", "seed-two"]},
        {}, fake_spawn, candidates, owned,
    )

    assert selected == transcript
    assert owned == [transcript]
    expected_retry = ["agent", "retry-resume", session_id] if first_shape == "wrote-owned" else ["agent", "start"]
    assert commands[1] == expected_retry


@pytest.mark.parametrize("first_shape", ["two-owned", "foreign"])
def test_first_seed_retry_rejects_ambiguous_or_foreign_window(tmp_path, first_shape):
    root = tmp_path / "store"
    root.mkdir()
    workspace = tmp_path / "workspace"
    workspace.mkdir()
    first = _scoped_claude_transcript(root, workspace, "aaaaaaaa-1111-4111-8111-111111111111")
    second = first.parent / "bbbbbbbb-1111-4111-8111-111111111111.jsonl"
    foreign = root / "foreign.jsonl"
    calls = 0

    def fake_spawn(command, cwd, env):
        nonlocal calls
        calls += 1
        first.write_text("TOKEN\nseed-one\n", encoding="utf-8")
        if first_shape == "two-owned":
            second.write_text("TOKEN\nseed-one\n", encoding="utf-8")
        else:
            foreign.write_text("other", encoding="utf-8")
        return SimpleNamespace(returncode=1, stdout="", stderr="transient")

    candidates = []
    owned = []
    with pytest.raises(ValueError, match="capture ambiguity"):
        e3._seed_agent(
            _retry_seed_agent(), root, workspace, {"seed_turns": ["seed-one", "seed-two"]},
            {}, fake_spawn, candidates, owned,
        )
    assert calls == 1
    assert owned == []


def test_first_seed_retry_rejects_resume_after_midfail_rejection(tmp_path):
    root = tmp_path / "store"
    root.mkdir()
    workspace = tmp_path / "workspace"
    workspace.mkdir()
    session_id = "aaaaaaaa-1111-4111-8111-111111111111"
    transcript = _scoped_claude_transcript(root, workspace, session_id)
    commands = []

    def fake_spawn(command, cwd, env):
        commands.append(command)
        transcript.write_text(f"TOKEN\nseed-one\nattempt-{len(commands)}\n", encoding="utf-8")
        return SimpleNamespace(returncode=1, stdout="", stderr="resume rejected")

    candidates = []
    owned = []
    with pytest.raises(ValueError, match="retry failed"):
        e3._seed_agent(
            _retry_seed_agent(), root, workspace, {"seed_turns": ["seed-one", "seed-two"]},
            {}, fake_spawn, candidates, owned,
        )
    assert commands == [["agent", "start"], ["agent", "retry-resume", session_id]]
    assert owned == [transcript]


def test_second_seed_turn_retries_same_resume_command_once(tmp_path):
    root = tmp_path / "store"
    root.mkdir()
    workspace = tmp_path / "workspace"
    workspace.mkdir()
    session_id = "aaaaaaaa-1111-4111-8111-111111111111"
    transcript = _scoped_claude_transcript(root, workspace, session_id)
    commands = []

    def fake_spawn(command, cwd, env):
        commands.append(command)
        if len(commands) == 1:
            transcript.write_text("TOKEN\nseed-one\n", encoding="utf-8")
            return SimpleNamespace(returncode=0, stdout="reply", stderr="")
        transcript.write_text(f"TOKEN\nseed-one\nseed-two\nattempt-{len(commands)}\n", encoding="utf-8")
        return SimpleNamespace(returncode=1 if len(commands) == 2 else 0, stdout="reply", stderr="")

    e3._seed_agent(
        _retry_seed_agent(), root, workspace, {"seed_turns": ["seed-one", "seed-two"]},
        {}, fake_spawn, [], [],
    )
    assert commands[1] == commands[2] == ["agent", "continue", session_id]


def test_e3_scenario_pins_cheapest_model_on_every_model_call_leg():
    scenario = Path(__file__).parents[1] / "scenarios-e3" / "e3-dual-resume.json"
    spec = json.loads(scenario.read_text(encoding="utf-8"))
    expected = {"claude-code": "haiku", "codex": "gpt-5.4-mini"}
    assert spec["model_call_baseline"] == {"claude-code": 4, "codex": 3}

    for agent in spec["agents"]:
        model = expected[agent["id"]]
        assert agent["cheapest_model"] == model
        fields = ["seed_start_command", "seed_retry_resume_command", "seed_continue_command", "resume_command"]
        if agent["id"] == "claude-code":
            fields.append("liveness_command")
        for field in fields:
            command = agent[field]
            index = command.index("--model")
            assert command[index + 1] == model


def test_e3_scenario_keeps_only_token_prefix_and_injects_runtime_token_into_seed_commands():
    scenario = Path(__file__).parents[1] / "scenarios-e3" / "e3-dual-resume.json"
    spec = json.loads(scenario.read_text(encoding="utf-8"))

    for agent in spec["agents"]:
        assert agent["run_token_prefix"]
        assert "run_token" not in agent
        for field in ("seed_start_command", "seed_retry_resume_command", "seed_continue_command"):
            assert any("{run_token}" in part for part in agent[field])


def test_workspace_credential_decoys_are_exact_and_format_valid(tmp_path):
    sentinels = ["synthetic-secret-one", "synthetic-secret-two"]
    paths = plant_credential_decoys(tmp_path, sentinels)
    assert {path.name for path in paths} == {".credentials.json", "auth.json", ".env"}
    verify_credential_decoys(tmp_path, paths, sentinels)


def test_workspace_credential_decoys_are_removed_and_absence_proven(tmp_path):
    paths = plant_credential_decoys(tmp_path, ["synthetic-secret"])
    root = paths[0].parent

    e3._remove_credential_decoys(tmp_path, paths)

    assert not root.exists()
    assert all(not path.exists() for path in paths)


@pytest.mark.parametrize("failure_mode", ("no-op", "missing-error"))
def test_workspace_credential_decoy_removal_fails_closed_when_absence_is_unproven(
    monkeypatch, tmp_path, failure_mode
):
    paths = plant_credential_decoys(tmp_path, ["synthetic-secret"])

    def failed_remove(*_args, **_kwargs):
        if failure_mode == "missing-error":
            raise FileNotFoundError("injected deletion failure")

    monkeypatch.setattr(e3.shutil, "rmtree", failed_remove)

    with pytest.raises(ValueError, match="decoy cleanup failed"):
        e3._remove_credential_decoys(tmp_path, paths)


@pytest.mark.parametrize("removed_count", [1, 2])
def test_workspace_credential_decoys_reject_missing_required_paths(tmp_path, removed_count):
    sentinels = ["synthetic-secret"]
    paths = plant_credential_decoys(tmp_path, sentinels)
    for path in paths[-removed_count:]:
        path.unlink()
    with pytest.raises(ValueError, match="exact controlled credential-shaped decoy set"):
        verify_credential_decoys(tmp_path, paths, sentinels)


@pytest.mark.parametrize(
    ("name", "content"),
    [
        (".credentials.json", "synthetic-secret"),
        ("auth.json", '{"apiKey":"synthetic-secret"}'),
        (".env", "OPENAI_API_KEY=synthetic-secret\n"),
    ],
)
def test_workspace_credential_decoys_reject_wrong_format_or_content(tmp_path, name, content):
    sentinels = ["synthetic-secret"]
    paths = plant_credential_decoys(tmp_path, sentinels)
    next(path for path in paths if path.name == name).write_text(content, encoding="utf-8")
    with pytest.raises(ValueError, match="format invalid"):
        verify_credential_decoys(tmp_path, paths, sentinels)


@pytest.mark.parametrize("kind", ["directory", "symlink"])
def test_workspace_credential_decoys_require_regular_files(tmp_path, kind):
    sentinels = ["synthetic-secret"]
    paths = plant_credential_decoys(tmp_path, sentinels)
    target = paths[0]
    target.unlink()
    if kind == "directory":
        target.mkdir()
    else:
        target.symlink_to(paths[1])
    with pytest.raises(ValueError, match="regular file"):
        verify_credential_decoys(tmp_path, paths, sentinels)


def test_workspace_credential_decoys_reject_extra_path(tmp_path):
    sentinels = ["synthetic-secret"]
    paths = plant_credential_decoys(tmp_path, sentinels)
    extra = paths[0].parent / "extra.env"
    extra.write_text("ANTHROPIC_API_KEY=synthetic-secret\n", encoding="utf-8")
    with pytest.raises(ValueError, match="exact controlled credential-shaped decoy set"):
        verify_credential_decoys(tmp_path, [*paths, extra], sentinels)


def test_workspace_credential_decoys_reject_unreported_physical_extra(tmp_path):
    sentinels = ["synthetic-secret"]
    paths = plant_credential_decoys(tmp_path, sentinels)
    (paths[0].parent / "unreported.env").write_text(
        "ANTHROPIC_API_KEY=synthetic-secret\n", encoding="utf-8"
    )
    with pytest.raises(ValueError, match="exact controlled credential-shaped decoy set"):
        verify_credential_decoys(tmp_path, paths, sentinels)


def test_workspace_credential_decoy_plant_rejects_symlinked_root(tmp_path):
    workspace = tmp_path / "workspace"
    outside = tmp_path / "outside"
    workspace.mkdir()
    outside.mkdir()
    (workspace / ".biv-e3-credential-decoys").symlink_to(outside, target_is_directory=True)

    with pytest.raises(ValueError, match="regular directory inside workspace"):
        plant_credential_decoys(workspace, ["synthetic-secret"])
    assert list(outside.iterdir()) == []


def test_workspace_credential_decoy_plant_rejects_symlinked_leaf_before_write(tmp_path):
    workspace = tmp_path / "workspace"
    outside = tmp_path / "outside.json"
    root = workspace / ".biv-e3-credential-decoys"
    workspace.mkdir()
    root.mkdir()
    outside.write_text("do-not-overwrite", encoding="utf-8")
    (root / ".credentials.json").symlink_to(outside)

    with pytest.raises(ValueError, match="exact controlled credential-shaped decoy set"):
        plant_credential_decoys(workspace, ["synthetic-secret"])
    assert outside.read_text(encoding="utf-8") == "do-not-overwrite"
    assert {path.name for path in root.iterdir()} == {".credentials.json"}


def test_workspace_credential_decoy_plant_rejects_symlinked_ignore_before_write(tmp_path):
    workspace = tmp_path / "workspace"
    outside = tmp_path / "outside.ignore"
    workspace.mkdir()
    outside.write_text("do-not-overwrite", encoding="utf-8")
    (workspace / ".bivignore").symlink_to(outside)

    with pytest.raises(ValueError, match="regular file inside workspace"):
        plant_credential_decoys(workspace, ["synthetic-secret"])
    assert outside.read_text(encoding="utf-8") == "do-not-overwrite"
    assert not (workspace / ".biv-e3-credential-decoys").exists()


def test_workspace_credential_decoy_plant_rejects_symlinked_workspace(tmp_path):
    outside = tmp_path / "outside"
    workspace = tmp_path / "workspace"
    outside.mkdir()
    workspace.symlink_to(outside, target_is_directory=True)

    with pytest.raises(ValueError, match="workspace must be a regular directory"):
        plant_credential_decoys(workspace, ["synthetic-secret"])
    assert list(outside.iterdir()) == []


def test_workspace_credential_decoy_verify_rejects_root_outside_workspace(tmp_path):
    workspace = tmp_path / "workspace"
    outside = tmp_path / "outside"
    workspace.mkdir()
    outside.mkdir()
    paths = plant_credential_decoys(outside, ["synthetic-secret"])

    with pytest.raises(ValueError, match="regular directory inside workspace"):
        verify_credential_decoys(workspace, paths, ["synthetic-secret"])


def test_e3_spec_requires_positive_int_sentinel_count():
    scenario = Path(__file__).parents[1] / "scenarios-e3" / "e3-dual-resume.json"
    spec = json.loads(scenario.read_text(encoding="utf-8"))
    spec["credential_scan_sentinel_count"] = 1
    assert not any("credential_scan_sentinel_count" in f for f in e3._validate_spec(spec))
    for bad in [None, 0, -1, "1", 1.0, True, False]:
        s = dict(spec)
        s["credential_scan_sentinel_count"] = bad
        assert any(
            "credential_scan_sentinel_count must be a positive integer" in f
            for f in e3._validate_spec(s)
        ), bad
    s = dict(spec)
    s.pop("credential_scan_sentinel_count", None)
    assert any("credential_scan_sentinel_count" in f for f in e3._validate_spec(s))


def _credential_order_fake_spawn(seen):
    def fake_spawn(command, cwd, env):
        seen.append(tuple(command))
        if command[1:] in (["auth", "status"], ["login", "status"]):
            return SimpleNamespace(returncode=0, stdout="", stderr="")
        if command[1:] == ["--version"] and _agent_basename(command) == "claude":
            return SimpleNamespace(returncode=0, stdout="2.1.0", stderr="")
        if command[1:] == ["--version"] and _agent_basename(command) == "codex":
            return SimpleNamespace(returncode=0, stdout="0.144.1", stderr="")
        raise AssertionError(f"unexpected spawn command: {command}")

    return fake_spawn


def test_e3_converts_decoy_plant_failure_to_invalid_and_cleans_up(monkeypatch):
    scenario = Path(__file__).parents[1] / "scenarios-e3" / "e3-dual-resume.json"
    scratch = Path.home() / ".cache" / f"biv-e3-decoy-plant-failure-{os.getpid()}"
    shutil.rmtree(scratch, ignore_errors=True)
    seen = []
    seeded = []

    def reject_plant(workspace, sentinels):
        raise ValueError("decoy root rejected")

    monkeypatch.setattr(e3, "_spawn", _credential_order_fake_spawn(seen))
    monkeypatch.setattr(
        e3,
        "_seed_agent",
        lambda agent, *args, **kwargs: seeded.append(agent["id"]),
    )
    monkeypatch.setattr(e3, "plant_credential_decoys", reject_plant)
    try:
        result = e3.run_e3(scenario, Path("biv"), scratch)
        _assert_report_refused(result)
        assert seeded == ["claude-code", "codex"]
        assert all(_agent_basename(command) in {"claude", "codex"} for command in seen)
        assert not (scratch / "seed-ws").exists()
        assert not (scratch / "host2").exists()
    finally:
        shutil.rmtree(scratch, ignore_errors=True)


def test_e3_decoys_planted_after_seed_are_absent_from_session_and_excluded_from_image(
    monkeypatch, tmp_path, stable_test_root, capsys
):
    configured = "BIV_E3_CREDENTIAL_SENTINEL_MUST_NOT_APPEAR"
    sentinel = "bive3-sentinel-" + "d" * 64
    source_scenario = (
        Path(__file__).parents[1] / "scenarios-e3" / "e3-dual-resume.json"
    )
    spec = json.loads(source_scenario.read_text(encoding="utf-8"))
    spec["credential_scan_sentinel_count"] = 1
    scenario = tmp_path / "credential-fixture-order.json"
    scenario.write_text(json.dumps(spec), encoding="utf-8")
    scratch = stable_test_root / "scratch"
    stub_biv = Path(__file__).with_name("stub_biv.py")

    reached = []
    seen = []
    captured_reads = []
    captured_members = []
    captured_hits = []
    pack_time = {}
    generated_counts = []

    def fake_seed(
        agent,
        live_profile,
        seed_workspace,
        spec,
        env,
        spawn,
        capture_candidates,
        owned_paths,
        resolved_binary=None,
    ):
        reached.append(f"seed:{agent['id']}")
        blob = "".join(
            path.read_text(errors="ignore")
            for path in sorted(seed_workspace.rglob("*"))
            if path.is_file()
        )
        captured_reads.append(blob)
        transcript = seed_workspace / f"seen-{agent['id']}.jsonl"
        transcript.write_text(json.dumps({"content": blob}), encoding="utf-8")
        owned_paths.append(transcript)

    real_scan = e3.scan_image_secret_values

    def capturing_scan(image, secret_values):
        reached.append("scan")
        captured_members[:] = e3.list_members(image)
        captured_hits[:] = real_scan(image, secret_values)
        return captured_hits

    real_spawn = e3._spawn
    fake_agent_spawn = _credential_order_fake_spawn(seen)

    def fake_spawn(command, cwd, env):
        if len(command) > 1 and command[0] == str(stub_biv) and command[1] == "pack":
            seen.append(tuple(command))
            seed_workspace = Path(command[2])
            decoy_root = seed_workspace / e3.CREDENTIAL_DECOY_ROOT
            pack_time["decoys"] = decoy_root.is_dir() and {
                path.name for path in decoy_root.iterdir()
            } == set(e3.CREDENTIAL_DECOY_NAMES)
            pack_time["bivignore"] = e3.CREDENTIAL_DECOY_ROOT + "/" in (
                seed_workspace / ".bivignore"
            ).read_text(encoding="utf-8").splitlines()
            reached.append("pack")
            return real_spawn([sys.executable, *command], cwd, env)
        return fake_agent_spawn(command, cwd, env)

    def stop_after_scan(*args):
        reached.append("terminal")
        scanner = args[5]
        assert scanner.scan_text(sentinel)
        assert not scanner.scan_text(configured)
        assert not (
            scratch
            / "seed-ws"
            / spec["workspace_name"]
            / e3.CREDENTIAL_DECOY_ROOT
        ).exists()
        raise ValueError("stop after credential scan")

    monkeypatch.setenv("STUB_BIV_MODE", "ok")

    def controlled_runtime_sentinels(count):
        generated_counts.append(count)
        return [sentinel] if count == 1 else pytest.fail(count)

    monkeypatch.setattr(
        e3,
        "_runtime_credential_sentinels",
        controlled_runtime_sentinels,
    )
    monkeypatch.setattr(e3, "_spawn", fake_spawn)
    monkeypatch.setattr(e3, "_seed_agent", fake_seed)
    monkeypatch.setattr(e3, "scan_image_secret_values", capturing_scan)
    monkeypatch.setattr(e3, "setup_host2_credentials", stop_after_scan)

    result = e3.run_e3(
        scenario,
        stub_biv,
        scratch,
    )
    captured_console = capsys.readouterr()

    assert result.status is Status.INVALID
    assert result.detail == "e3-post-materialization-invalid"
    assert generated_counts == [1]
    assert sentinel not in captured_console.out
    assert sentinel not in captured_console.err
    assert len(captured_reads) == 2
    assert all(sentinel not in blob for blob in captured_reads)
    assert all(configured not in blob for blob in captured_reads)
    assert not any(
        member.startswith(f"payload/{e3.CREDENTIAL_DECOY_ROOT}/")
        for member in captured_members
    )
    assert captured_hits == []
    assert pack_time == {"decoys": True, "bivignore": True}
    assert reached == [
        "seed:claude-code",
        "seed:codex",
        "pack",
        "scan",
        "terminal",
    ]
    assert all(
        _agent_basename(command) in {"claude", "codex"} or command[0] == str(stub_biv)
        for command in seen
    )
    assert not (scratch / "seed-ws").exists()
    assert not (scratch / "host2").exists()


def test_e3_controlled_sentinel_image_hit_stops_before_credential_materialization(
    monkeypatch, tmp_path, stable_test_root
):
    sentinel = "bive3-sentinel-" + "f" * 64
    spec_path, seen = _configure_exit_contract_case(
        monkeypatch,
        tmp_path,
        pack_result=_successful_pack(),
    )
    scanned = []

    monkeypatch.setattr(
        e3,
        "_runtime_credential_sentinels",
        lambda count: [sentinel] if count == 1 else pytest.fail(count),
    )

    def controlled_hit(_image, values):
        scanned.append(list(values))
        return ["payload/auth.json:secret[0]"]

    monkeypatch.setattr(e3, "scan_image_secret_values", controlled_hit)
    monkeypatch.setattr(
        e3,
        "setup_host2_credentials",
        lambda *_args: pytest.fail("credential materialization followed image hit"),
    )

    result = e3.run_e3(
        spec_path,
        Path("/fake/biv"),
        stable_test_root / "scratch",
    )

    _assert_report_refused(result)
    assert sentinel not in serialize_report([result])
    assert scanned == [[sentinel]]
    assert seen == ["pack"]


def test_e3_pack_warning_before_sentinel_population_is_not_written(
    monkeypatch, tmp_path, stable_test_root
):
    secret = "REFRESHED_REAL_CREDENTIAL_VALUE_pack_window"
    result, seen = _run_exit_contract_case(
        monkeypatch,
        tmp_path,
        stable_test_root,
        pack_result=_successful_pack(warnings=[secret]),
        post_pack_exception=ValueError("controlled image scan failure"),
    )

    _assert_report_refused(result)
    assert secret not in serialize_report([result])
    assert seen == ["pack"]


def test_e3_decoy_removal_error_stops_before_scanner_activation_and_setup(
    monkeypatch, tmp_path, stable_test_root
):
    spec_path, seen = _configure_exit_contract_case(
        monkeypatch,
        tmp_path,
        pack_result=_successful_pack(),
    )
    real_rmtree = e3.shutil.rmtree
    setup_calls = []

    def fail_decoy_remove(path, *args, **kwargs):
        if Path(path).name == e3.CREDENTIAL_DECOY_ROOT:
            raise FileNotFoundError("injected deletion failure")
        return real_rmtree(path, *args, **kwargs)

    monkeypatch.setattr(e3.shutil, "rmtree", fail_decoy_remove)
    monkeypatch.setattr(
        e3,
        "setup_host2_credentials",
        lambda *_args: setup_calls.append(True),
    )

    result = e3.run_e3(
        spec_path,
        Path("/fake/biv"),
        stable_test_root / "scratch",
    )

    _assert_report_refused(result)
    assert setup_calls == []
    assert seen == ["pack"]


def test_e3_open_uses_fresh_work_directory_below_host2_state_root(monkeypatch):
    scenario = Path(__file__).parents[1] / "scenarios-e3" / "e3-dual-resume.json"
    scratch = Path.home() / ".cache" / f"biv-e3-open-dest-{os.getpid()}"
    shutil.rmtree(scratch, ignore_errors=True)
    opened = []
    restored_workspaces = []

    monkeypatch.setattr(e3, "_seed_agent", lambda *args, **kwargs: None)
    monkeypatch.setattr(e3, "scan_image_secret_values", lambda *args: [])
    real_class_j_failures = e3.class_j_failures

    def capture_class_j(seed_workspace, restored_workspace, app_state_paths):
        restored_workspaces.append(restored_workspace)
        return real_class_j_failures(seed_workspace, restored_workspace, app_state_paths)

    monkeypatch.setattr(e3, "class_j_failures", capture_class_j)

    def fake_spawn(command, cwd, env):
        if command[1:] == ["--version"]:
            version = "2.1.207" if _agent_basename(command) == "claude" else "0.142.5"
            return SimpleNamespace(returncode=0, stdout=version, stderr="")
        if _agent_basename(command) == "claude" and command[1] == "--model":
            return SimpleNamespace(returncode=0, stdout="OK", stderr="")
        if len(command) > 1 and command[1] == "pack":
            return _successful_pack()
        if len(command) > 1 and command[1] == "open":
            dest = Path(command[command.index("--dest") + 1])
            host2 = scratch / "host2"
            assert dest == host2 / "work"
            assert not dest.exists()
            assert (host2 / "home").is_dir()
            assert (host2 / "profiles" / "claude").is_dir()
            assert (host2 / "profiles" / "codex").is_dir()
            assert dest != scratch / "seed-ws" / "biv-e3-dual-resume"
            assert cwd == host2
            assert env["HOME"] == str(host2 / "home")
            assert env["CLAUDE_CONFIG_DIR"] == str(host2 / "profiles" / "claude")
            assert env["CODEX_HOME"] == str(host2 / "profiles" / "codex")
            dest.mkdir()
            assert dest.is_dir()
            opened.append(dest)
            result = {
                "output_dir": str(dest),
                "sessions": {"agents": []},
            }
            return SimpleNamespace(
                returncode=0,
                stdout=_envelope("open", 0, ok=True, result=result),
                stderr="",
            )
        return SimpleNamespace(returncode=0, stdout="", stderr="")

    monkeypatch.setattr(e3, "_spawn", fake_spawn)
    try:
        result = e3.run_e3(scenario, Path("biv"), scratch)
        expected = scratch / "host2" / "work"
        assert result.status is Status.FAIL
        assert result.detail == "e3-post-materialization-fail"
        assert opened == [expected]
        assert restored_workspaces == [expected]
        assert e3._project_key(restored_workspaces[0]) != e3._project_key(scratch / "host2")
        assert not (scratch / "host2").exists()
    finally:
        shutil.rmtree(scratch, ignore_errors=True)


def test_e3_rejects_symlinked_scratch_before_probe_writes(tmp_path):
    scenario = Path(__file__).parents[1] / "scenarios-e3" / "e3-dual-resume.json"
    outside = tmp_path / "outside"
    scratch = tmp_path / "scratch-link"
    outside.mkdir()
    scratch.symlink_to(outside, target_is_directory=True)

    result = e3.run_e3(scenario, Path("biv"), scratch, dry_run=True)
    assert result.status is Status.INVALID
    assert "scratch must not be a symlink" in result.detail
    assert list(outside.iterdir()) == []


@pytest.mark.parametrize("stale_target", ["seed-parent", "seed-workspace", "host2"])
def test_e3_rejects_preexisting_run_trees_without_deleting_them(monkeypatch, stale_target):
    scenario = Path(__file__).parents[1] / "scenarios-e3" / "e3-dual-resume.json"
    scratch = Path.home() / ".cache" / f"biv-e3-stale-{stale_target}-{os.getpid()}"
    targets = {
        "seed-parent": scratch / "seed-ws",
        "seed-workspace": scratch / "seed-ws" / "biv-e3-dual-resume",
        "host2": scratch / "host2",
    }
    stale = targets[stale_target]
    shutil.rmtree(scratch, ignore_errors=True)
    stale.mkdir(parents=True)
    marker = stale / "stale"
    marker.write_text("stale", encoding="utf-8")
    calls = []
    monkeypatch.setattr(e3, "_spawn", lambda *args: calls.append(args))
    try:
        result = e3.run_e3(scenario, Path("biv"), scratch)
        _assert_report_refused(result)
        assert calls == []
        assert marker.read_text(encoding="utf-8") == "stale"
    finally:
        shutil.rmtree(scratch, ignore_errors=True)


def test_e3_dry_run_rejects_missing_credential_sentinel_inventory(tmp_path):
    scenario = Path(__file__).parents[1] / "scenarios-e3" / "e3-dual-resume.json"
    spec = json.loads(scenario.read_text(encoding="utf-8"))
    spec.pop("credential_scan_sentinel_count")
    spec_path = tmp_path / "missing-sentinels.json"
    spec_path.write_text(json.dumps(spec), encoding="utf-8")
    scratch = Path.home() / ".cache" / f"biv-e3-missing-sentinels-{os.getpid()}"
    shutil.rmtree(scratch, ignore_errors=True)
    try:
        result = e3.run_e3(spec_path, Path("biv"), scratch, dry_run=True)
    finally:
        shutil.rmtree(scratch, ignore_errors=True)

    assert result.status is Status.INVALID
    assert "credential_scan_sentinel_count" in result.detail


def test_secret_scan_reads_decompressed_archive_members(tmp_path):
    sentinel = "compressed-secret-value"
    raw = io.BytesIO()
    with tarfile.open(fileobj=raw, mode="w") as archive:
        content = f"OPENAI_API_KEY={sentinel}\n".encode()
        member = tarfile.TarInfo("payload/leak.env")
        member.size = len(content)
        archive.addfile(member, io.BytesIO(content))
    image = tmp_path / "leak.bvpk"
    image.write_bytes(zstandard.ZstdCompressor().compress(raw.getvalue()))

    assert scan_secret_values(image.read_bytes(), [sentinel]) == []
    assert scan_image_secret_values(image, [sentinel]) == ["payload/leak.env:secret[0]"]


@pytest.mark.parametrize("agent_id", ["claude-code", "codex"])
def test_exact_install_delta_rejects_extra_or_mutated_files(tmp_path, agent_id):
    profile = tmp_path / agent_id
    profile.mkdir()
    baseline = profile / "config"
    baseline.write_text("before", encoding="utf-8")
    before = snapshot_store(profile)
    session_id = "aaaaaaaa-1111-4111-8111-111111111111"
    restored = tmp_path / "restored"
    if agent_id == "claude-code":
        project_key = "".join(ch if ch.isascii() and ch.isalnum() else "-" for ch in restored.as_posix())
        installed = profile / "projects" / project_key / f"{session_id}.jsonl"
    else:
        installed = profile / "sessions" / f"rollout-now-{session_id}.jsonl"
    installed.parent.mkdir(parents=True)
    installed.write_text(f'{{"sessionId":"{session_id}","turn":"seed-one seed-two"}}', encoding="utf-8")
    rows = [{"image_session_id": "old-id", "installed_session_id": session_id}]
    after = snapshot_store(profile)
    paths = assert_exact_install_delta(
        agent_id, profile, restored, rows, before, after, ["seed-one", "seed-two"]
    )
    assert paths == [installed]

    extra = profile / "stray-auth.json"
    extra.write_text("unexpected", encoding="utf-8")
    with pytest.raises(ValueError, match="exact install delta"):
        assert_exact_install_delta(
            agent_id, profile, restored, rows, before, snapshot_store(profile), ["seed-one", "seed-two"]
        )
    extra.unlink()
    baseline.write_text("mutated", encoding="utf-8")
    with pytest.raises(ValueError, match="exact install delta"):
        assert_exact_install_delta(
            agent_id, profile, restored, rows, before, snapshot_store(profile), ["seed-one", "seed-two"]
        )


@pytest.mark.parametrize("agent_id", ["claude-code", "codex"])
def test_exact_install_delta_rejects_transcript_without_seeded_history(tmp_path, agent_id):
    profile = tmp_path / agent_id
    profile.mkdir()
    before = snapshot_store(profile)
    session_id = "aaaaaaaa-1111-4111-8111-111111111111"
    restored = tmp_path / "restored"
    if agent_id == "claude-code":
        installed = profile / "projects" / e3._project_key(restored) / f"{session_id}.jsonl"
    else:
        installed = profile / "sessions" / f"rollout-now-{session_id}.jsonl"
    installed.parent.mkdir(parents=True)
    installed.write_text(f'{{"sessionId":"{session_id}"}}', encoding="utf-8")
    rows = [{"image_session_id": "old-id", "installed_session_id": session_id}]

    with pytest.raises(ValueError, match="seeded history"):
        assert_exact_install_delta(
            agent_id, profile, restored, rows, before, snapshot_store(profile),
            ["seed-one", "seed-two"],
        )


def test_claude_resume_requires_exact_restored_workspace_project_file(tmp_path):
    profile = tmp_path / "claude"
    restored = tmp_path / "host2" / "work" / "restored"
    session_id = "aaaaaaaa-1111-4111-8111-111111111111"
    project_key = "".join(ch if ch.isascii() and ch.isalnum() else "-" for ch in restored.as_posix())
    expected = profile / "projects" / project_key / f"{session_id}.jsonl"
    expected.parent.mkdir(parents=True)
    expected.write_text("seed-one\nseed-two\n", encoding="utf-8")
    fork = profile / "projects" / "fork" / "bbbbbbbb-1111-4111-8111-111111111111.jsonl"
    fork.parent.mkdir(parents=True)
    fork.write_text("seed-one\nseed-two\nresume-probe\n", encoding="utf-8")

    with pytest.raises(ValueError, match="containment"):
        assert_resume_containment(
            "claude-code", profile, restored, session_id,
            ["seed-one", "seed-two", "resume-probe"], "resume-probe",
            CLAUDE_RESUME_MUTATION,
        )

    fork.unlink()
    expected.write_text("seed-one\nseed-two\nresume-probe\n", encoding="utf-8")
    assert_resume_containment(
        "claude-code", profile, restored, session_id,
        ["seed-one", "seed-two", "resume-probe"], "resume-probe",
        CLAUDE_RESUME_MUTATION,
    )


def _assert_claude_resume(profile, restored, session_id, installed, before):
    return assert_resume_containment(
        "claude-code", profile, restored, session_id,
        ["seed-one", "seed-two", "resume-probe"], "resume-probe",
        CLAUDE_RESUME_MUTATION,
        expected_transcript=installed,
        pre_resume_content=before,
    )


def _claude_installed(profile, restored, session_id):
    return profile / "projects" / e3._project_key(restored) / f"{session_id}.jsonl"


def test_claude_resume_accepts_exact_installed_transcript_append(tmp_path):
    profile = tmp_path / "claude"
    restored = tmp_path / "restored"
    session_id = "aaaaaaaa-1111-4111-8111-111111111111"
    installed = _claude_installed(profile, restored, session_id)
    installed.parent.mkdir(parents=True)
    before = b"seed-one\nseed-two\n"
    installed.write_bytes(before + b"resume-probe\n")

    assert _assert_claude_resume(
        profile, restored, session_id, installed, before,
    ) == installed


@pytest.mark.parametrize("installed_appended", [False, True])
def test_claude_resume_rejects_same_id_probe_fork(tmp_path, installed_appended):
    profile = tmp_path / "claude"
    restored = tmp_path / "restored"
    session_id = "aaaaaaaa-1111-4111-8111-111111111111"
    installed = _claude_installed(profile, restored, session_id)
    installed.parent.mkdir(parents=True)
    before = b"seed-one\nseed-two\n"
    installed.write_bytes(before + (b"resume-probe\n" if installed_appended else b""))
    fork = profile / "projects" / "sibling" / f"fork-alternate-{session_id}.jsonl"
    fork.parent.mkdir(parents=True)
    fork.write_bytes(before + b"resume-probe\n")

    with pytest.raises(ValueError, match="exact installed transcript"):
        _assert_claude_resume(profile, restored, session_id, installed, before)


def test_claude_resume_rejects_nested_same_id_probe_fork_with_invalid_utf8(tmp_path):
    profile = tmp_path / "claude"
    restored = tmp_path / "restored"
    session_id = "aaaaaaaa-1111-4111-8111-111111111111"
    installed = _claude_installed(profile, restored, session_id)
    installed.parent.mkdir(parents=True)
    before = b"seed-one\nseed-two\n"
    installed.write_bytes(before + b"resume-probe\n")
    fork = profile / "projects" / "nested" / "deeper" / f"alternate-{session_id}.jsonl"
    fork.parent.mkdir(parents=True)
    fork.write_bytes(before + b"resume-probe\n\xff")

    with pytest.raises(ValueError, match="invalid UTF-8 Claude transcript"):
        _assert_claude_resume(profile, restored, session_id, installed, before)


def test_claude_resume_rejects_same_id_invalid_utf8_candidate_without_probe(tmp_path):
    profile = tmp_path / "claude"
    restored = tmp_path / "restored"
    session_id = "aaaaaaaa-1111-4111-8111-111111111111"
    installed = _claude_installed(profile, restored, session_id)
    installed.parent.mkdir(parents=True)
    before = b"seed-one\nseed-two\n"
    installed.write_bytes(before + b"resume-probe\n")
    fork = profile / "projects" / "nested" / f"alternate-{session_id}.jsonl"
    fork.parent.mkdir(parents=True)
    fork.write_bytes(before + b"fork-without-probe\n\xff")

    with pytest.raises(ValueError, match="invalid UTF-8 Claude transcript"):
        _assert_claude_resume(profile, restored, session_id, installed, before)


def test_claude_resume_rejects_unreadable_same_id_candidate(tmp_path):
    profile = tmp_path / "claude"
    restored = tmp_path / "restored"
    session_id = "aaaaaaaa-1111-4111-8111-111111111111"
    installed = _claude_installed(profile, restored, session_id)
    installed.parent.mkdir(parents=True)
    before = b"seed-one\nseed-two\n"
    installed.write_bytes(before + b"resume-probe\n")
    fork = profile / "projects" / "nested" / f"alternate-{session_id}.jsonl"
    fork.parent.mkdir(parents=True)
    fork.write_bytes(before + b"resume-probe\n")
    fork.chmod(0)
    try:
        with pytest.raises(ValueError, match="inspect Claude transcript"):
            _assert_claude_resume(profile, restored, session_id, installed, before)
    finally:
        fork.chmod(0o600)


def test_claude_resume_rejects_non_prefix_replacement_at_installed_path(tmp_path):
    profile = tmp_path / "claude"
    restored = tmp_path / "restored"
    session_id = "aaaaaaaa-1111-4111-8111-111111111111"
    installed = _claude_installed(profile, restored, session_id)
    installed.parent.mkdir(parents=True)
    before = b"header-original\nseed-one\nseed-two\n"
    installed.write_bytes(b"header-rewritten\nseed-one\nseed-two\nresume-probe\n")

    with pytest.raises(ValueError, match="append"):
        _assert_claude_resume(profile, restored, session_id, installed, before)


def test_claude_resume_rejects_unreadable_exact_installed_file(tmp_path):
    profile = tmp_path / "claude"
    restored = tmp_path / "restored"
    session_id = "aaaaaaaa-1111-4111-8111-111111111111"
    installed = _claude_installed(profile, restored, session_id)
    installed.parent.mkdir(parents=True)
    before = b"seed-one\nseed-two\n"
    installed.write_bytes(before + b"resume-probe\n")
    installed.chmod(0)
    try:
        with pytest.raises(ValueError):
            _assert_claude_resume(profile, restored, session_id, installed, before)
    finally:
        installed.chmod(0o600)


def _assert_codex_resume(profile, restored, session_id, installed, before):
    return assert_resume_containment(
        "codex", profile, restored, session_id,
        ["seed-one", "seed-two", "resume-probe"], "resume-probe", CODEX_RESUME_SHAPE,
        expected_transcript=installed,
        pre_resume_content=before,
    )


def test_codex_resume_accepts_exact_installed_rollout_append(tmp_path):
    profile = tmp_path / "codex"
    session_id = "019faaaa-bbbb-7ccc-8ddd-eeeeeeee0001"
    installed = profile / "sessions" / f"rollout-original-{session_id}.jsonl"
    installed.parent.mkdir(parents=True)
    before = b"seed-one\nseed-two\n"
    installed.write_bytes(before + b"resume-probe\n")

    assert _assert_codex_resume(
        profile, tmp_path / "restored", session_id, installed, before,
    ) == installed


@pytest.mark.parametrize("installed_appended", [False, True])
@pytest.mark.parametrize(
    "fork_parent_name",
    [
        ("sibling", "rollout-fork"),
        ("sessions/nested/deeper", "rollout-copy"),
        ("archive", "rollout-alternate-name-shape"),
    ],
)
def test_codex_resume_rejects_same_id_probe_fork(
    tmp_path, installed_appended, fork_parent_name,
):
    profile = tmp_path / "codex"
    session_id = "019faaaa-bbbb-7ccc-8ddd-eeeeeeee0001"
    installed = profile / "sessions" / f"rollout-original-{session_id}.jsonl"
    installed.parent.mkdir(parents=True)
    before = b"seed-one\nseed-two\n"
    installed.write_bytes(before + (b"resume-probe\n" if installed_appended else b""))
    parent, name = fork_parent_name
    fork = profile / parent / f"{name}-{session_id}.jsonl"
    fork.parent.mkdir(parents=True)
    fork.write_bytes(before + b"resume-probe\n")

    with pytest.raises(ValueError, match="exact installed transcript"):
        _assert_codex_resume(
            profile, tmp_path / "restored", session_id, installed, before,
        )


def test_codex_resume_rejects_delete_and_recreate_at_installed_path(tmp_path):
    profile = tmp_path / "codex"
    session_id = "019faaaa-bbbb-7ccc-8ddd-eeeeeeee0001"
    installed = profile / "sessions" / f"rollout-original-{session_id}.jsonl"
    installed.parent.mkdir(parents=True)
    before = b"header-original\nseed-one\nseed-two\n"
    installed.write_bytes(b"header-rewritten\nseed-one\nseed-two\nresume-probe\n")

    with pytest.raises(ValueError, match="append"):
        _assert_codex_resume(
            profile, tmp_path / "restored", session_id, installed, before,
        )


def test_codex_resume_rejects_two_probe_bearing_same_id_rollouts(tmp_path):
    profile = tmp_path / "codex"
    session_id = "019faaaa-bbbb-7ccc-8ddd-eeeeeeee0001"
    installed = profile / "sessions" / f"rollout-original-{session_id}.jsonl"
    installed.parent.mkdir(parents=True)
    before = b"seed-one\nseed-two\n"
    installed.write_bytes(before + b"resume-probe\n")
    second = profile / "nested" / f"rollout-b-{session_id}.jsonl"
    second.parent.mkdir()
    second.write_text("resume-probe\n", encoding="utf-8")

    with pytest.raises(ValueError, match="exact installed transcript"):
        _assert_codex_resume(
            profile, tmp_path / "restored", session_id, installed, before,
        )


def test_codex_resume_rejects_same_id_probe_fork_with_invalid_utf8(tmp_path):
    profile = tmp_path / "codex"
    session_id = "019faaaa-bbbb-7ccc-8ddd-eeeeeeee0001"
    installed = profile / "sessions" / f"rollout-original-{session_id}.jsonl"
    installed.parent.mkdir(parents=True)
    before = b"seed-one\nseed-two\n"
    installed.write_bytes(before + b"resume-probe\n")
    fork = profile / "nested" / f"rollout-invalid-{session_id}.jsonl"
    fork.parent.mkdir()
    fork.write_bytes(before + b"resume-probe\n\xff")

    with pytest.raises(ValueError, match="exact installed transcript"):
        _assert_codex_resume(
            profile, tmp_path / "restored", session_id, installed, before,
        )


def test_codex_resume_rejects_unreadable_same_id_fork(tmp_path):
    profile = tmp_path / "codex"
    session_id = "019faaaa-bbbb-7ccc-8ddd-eeeeeeee0001"
    installed = profile / "sessions" / f"rollout-original-{session_id}.jsonl"
    installed.parent.mkdir(parents=True)
    before = b"seed-one\nseed-two\n"
    installed.write_bytes(before + b"resume-probe\n")
    fork = profile / "nested" / f"rollout-unreadable-{session_id}.jsonl"
    fork.parent.mkdir()
    fork.write_bytes(before + b"resume-probe\n")
    fork.chmod(0)
    try:
        with pytest.raises(ValueError, match="inspect same-session rollout"):
            _assert_codex_resume(
                profile, tmp_path / "restored", session_id, installed, before,
            )
    finally:
        fork.chmod(0o600)


def test_value_aware_secret_scan_has_red_and_green_controls():
    assert scan_secret_values(b"prefix planted-secret suffix", ["planted-secret"]) == ["secret[0]"]
    assert scan_secret_values(b"ANTHROPIC_API_KEY is only a variable name", ["planted-secret"]) == []


def test_credential_scanner_excludes_only_the_exact_regular_path(tmp_path):
    secret = b"scanner-owner-secret"
    scanner = e3._CredentialScanner()
    scanner.add_value(secret)
    excluded = tmp_path / "credential"
    excluded.write_bytes(secret)
    (tmp_path / "unexpected-copy").write_bytes(secret)

    assert scanner.scan_tree(tmp_path, {excluded})

    (tmp_path / "unexpected-copy").unlink()
    assert not scanner.scan_tree(tmp_path, {excluded})


def test_credential_scanner_rejects_multiply_linked_exclusion_without_values(
    tmp_path,
):
    scanner = e3._CredentialScanner()
    excluded = tmp_path / "credential"
    excluded.write_bytes(b"ordinary")
    os.link(excluded, tmp_path / "hardlink-alias")

    assert scanner.scan_tree(tmp_path, {excluded})


def test_credential_scanner_ignores_empty_values():
    scanner = e3._CredentialScanner()
    scanner.add_value(b"")
    scanner.add_value("")
    scanner.add_value(bytearray())

    assert not scanner.scan_bytes(b"ordinary content")


def test_credential_scanner_rejects_symlink_and_hardlink_aliases(tmp_path):
    secret = b"scanner-alias-secret"
    scanner = e3._CredentialScanner()
    scanner.add_value(secret)
    excluded = tmp_path / "credential"
    excluded.write_bytes(secret)
    (tmp_path / "symlink-alias").symlink_to(excluded)
    os.link(excluded, tmp_path / "hardlink-alias")

    assert scanner.scan_tree(tmp_path, {excluded})


@pytest.mark.parametrize("kind", ["file", "directory"])
def test_credential_scanner_fails_closed_on_unreadable_entries(tmp_path, kind):
    scanner = e3._CredentialScanner()
    scanner.add_value(b"scanner-unreadable-secret")
    blocked = tmp_path / "blocked"
    if kind == "file":
        blocked.write_bytes(b"ordinary")
    else:
        blocked.mkdir()
        (blocked / "inside").write_bytes(b"ordinary")
    blocked.chmod(0)
    try:
        assert scanner.scan_tree(tmp_path, set())
    finally:
        blocked.chmod(0o700)


@pytest.mark.parametrize("kind", ["fifo", "device", "socket"])
def test_credential_scanner_rejects_special_entries_without_blocking(
    monkeypatch, kind
):
    scanner = e3._CredentialScanner()
    scanner.add_value(b"scanner-special-secret")
    short_temp_root = (
        "/private/tmp" if Path("/private/tmp").is_dir() else tempfile.gettempdir()
    )
    root = Path(tempfile.mkdtemp(prefix="e3s-", dir=short_temp_root))
    try:
        if kind == "fifo":
            os.mkfifo(root / "fifo")
        elif kind == "socket":
            server = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
            server.bind(str(root / "socket"))
        else:
            (root / "device").write_bytes(b"ordinary")
            real_stat = e3.os.stat

            def special_stat(path, *args, **kwargs):
                status = real_stat(path, *args, **kwargs)
                if path == "device" and kwargs.get("dir_fd") is not None:
                    return os.stat_result((stat.S_IFCHR | 0o600, *status[1:]))
                return status

            monkeypatch.setattr(e3.os, "stat", special_stat)
        started = time.monotonic()
        assert scanner.scan_tree(root, set())
        assert time.monotonic() - started < 1
    finally:
        if "server" in locals():
            server.close()
        shutil.rmtree(root, ignore_errors=True)


def test_credential_scanner_detects_values_split_across_read_chunks(tmp_path):
    scanner = e3._CredentialScanner()
    secret = b"scanner-boundary-secret"
    scanner.add_value(secret)
    (tmp_path / "boundary").write_bytes(
        b"x" * (e3._CREDENTIAL_SCAN_CHUNK_SIZE - 3) + secret
    )

    assert scanner.scan_tree(tmp_path, set())


def test_credential_scanner_rejects_in_place_overwrite_after_final_read(
    monkeypatch, tmp_path
):
    scanner = e3._CredentialScanner()
    secret = b"credential-secret"
    original = b"ordinary-content!"
    assert len(secret) == len(original)
    scanner.add_value(secret)
    candidate = tmp_path / "candidate"
    candidate.write_bytes(original)
    os.utime(candidate, ns=(1_000_000_000, 1_000_000_000))
    before = candidate.stat()
    real_read = e3.os.read
    mutated = False

    def overwrite_after_eof(descriptor, size):
        nonlocal mutated
        chunk = real_read(descriptor, size)
        if not chunk and not mutated:
            candidate.write_bytes(secret)
            mutated = True
        return chunk

    monkeypatch.setattr(e3.os, "read", overwrite_after_eof)

    assert scanner.scan_tree(tmp_path, set())
    assert mutated
    assert candidate.read_bytes() == secret
    after = candidate.stat()
    assert (after.st_dev, after.st_ino, after.st_size) == (
        before.st_dev,
        before.st_ino,
        before.st_size,
    )
    assert after.st_mtime_ns != before.st_mtime_ns


def test_credential_scanner_copies_caller_bytearray():
    scanner = e3._CredentialScanner()
    caller = bytearray(b"scanner-owned-secret")
    scanner.add_value(caller)

    caller[:] = b"x" * len(caller)

    assert scanner.scan_bytes(b"scanner-owned-secret")
    assert not scanner.scan_bytes(caller)


def test_credential_scanner_drop_zeroes_and_clears_private_owned_buffer():
    scanner = e3._CredentialScanner()
    scanner.add_value(bytearray(b"scanner-drop-secret"))
    owned = scanner._values[0]

    scanner.drop()

    assert owned == bytearray(len(owned))
    assert scanner._values == []
    assert "scanner-drop-secret" not in repr(scanner)


def test_credential_scanner_detects_entry_added_after_directory_enumeration(
    monkeypatch, tmp_path
):
    scanner = e3._CredentialScanner()
    (tmp_path / "existing").write_bytes(b"ordinary")
    real_scandir = e3.os.scandir
    mutated = False

    class MutatingScandir:
        def __init__(self, descriptor):
            self._entries = real_scandir(descriptor)

        def __enter__(self):
            return self

        def __exit__(self, *args):
            self._entries.close()

        def __iter__(self):
            return self

        def __next__(self):
            nonlocal mutated
            try:
                return next(self._entries)
            except StopIteration:
                if not mutated:
                    (tmp_path / "late-addition").write_bytes(b"ordinary")
                    mutated = True
                raise

    monkeypatch.setattr(e3.os, "scandir", MutatingScandir)

    assert scanner.scan_tree(tmp_path, set())
    assert mutated


def test_finalize_report_replaces_all_secret_bearing_fields(tmp_path):
    secret = "scanner-report-secret"
    scanner = e3._CredentialScanner()
    scanner.add_value(secret)
    result = ScenarioResult(
        id=secret,
        tier=secret,
        status=Status.FAIL,
        classes=[secret],
        held_asserts=[secret],
        detail=secret,
        warnings=[secret],
    )

    final = e3._finalize_report(result, scanner)

    assert final.status is Status.INVALID
    assert final.classes == []
    assert final.held_asserts == []
    assert final.warnings == []
    assert secret not in serialize_report([final])


def _current_credential_guards(claude_dest, codex_dest):
    return {
        "claude-code": e3._credential_guard(claude_dest),
        "codex": e3._credential_guard(codex_dest),
    }


def _same_entry_changed_metadata(status):
    return SimpleNamespace(
        st_dev=status.st_dev,
        st_ino=status.st_ino,
        st_mode=status.st_mode,
        st_nlink=status.st_nlink,
        st_size=status.st_size + 1,
        st_mtime_ns=status.st_mtime_ns + 1,
        st_ctime_ns=status.st_ctime_ns + 1,
    )


def _guarded_teardown_paths(tmp_path):
    scratch = tmp_path / "scratch"
    seed_parent = scratch / "seed-ws"
    host2 = scratch / "host2"
    profile_root = scratch / "host2-profile"
    claude_dest = profile_root / "claude" / ".credentials.json"
    codex_dest = profile_root / "codex" / "auth.json"
    for path in (claude_dest, codex_dest):
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(b"guarded-teardown-secret")
    host2.mkdir(parents=True)
    seed_parent.mkdir(parents=True)
    guards = _current_credential_guards(claude_dest, codex_dest)
    return (
        scratch,
        seed_parent,
        host2,
        profile_root,
        claude_dest,
        codex_dest,
        guards,
    )


def test_scan_and_teardown_builds_typed_post_materialization_result(tmp_path):
    (
        scratch,
        seed_parent,
        host2,
        profile_root,
        claude_dest,
        codex_dest,
        guards,
    ) = _guarded_teardown_paths(tmp_path)
    dynamic = "RAW_REFRESHED_CREDENTIAL_OR_ENVELOPE_TEXT"
    scanner = e3._CredentialScanner()
    scanner.add_sentinel("bive3-sentinel-" + "a" * 64)

    final = e3._scan_and_teardown(
        ScenarioResult(
            "e3",
            "untrusted-tier",
            Status.FAIL,
            [dynamic],
            [dynamic],
            detail=dynamic,
            warnings=[dynamic],
        ),
        scanner,
        scratch,
        child_outputs=[dynamic.encode()],
        ambient_snapshots={},
        credential_guards=guards,
        claude_dest=claude_dest,
        codex_dest=codex_dest,
        profile_root=profile_root,
        host2=host2,
        seed_parent=seed_parent,
    )

    serialized = serialize_report([final])
    assert final == ScenarioResult(
        id="e3",
        tier="E3",
        status=Status.FAIL,
        classes=[],
        held_asserts=[],
        detail="e3-post-materialization-fail",
        warnings=["biv-warning-present"],
    )
    assert dynamic not in serialized


@pytest.mark.parametrize("representation_index", (0, 1, 2))
@pytest.mark.parametrize("surface", ("child", "scratch"))
def test_controlled_sentinel_forms_in_capture_surfaces_invalidate_cleanly(
    tmp_path,
    representation_index,
    surface,
):
    (
        scratch,
        seed_parent,
        host2,
        profile_root,
        claude_dest,
        codex_dest,
        guards,
    ) = _guarded_teardown_paths(tmp_path)
    sentinel = "bive3-sentinel-" + "b" * 63 + "/"
    representation = (
        sentinel.encode("ascii"),
        sentinel.replace("/", r"\/").encode("ascii"),
        "".join(f"\\u{ord(character):04x}" for character in sentinel).encode(
            "ascii"
        ),
    )[representation_index]
    child_outputs = []
    if surface == "child":
        child_outputs.append(representation)
    else:
        (seed_parent / "sentinel-copy").write_bytes(representation)
    scanner = e3._CredentialScanner()
    scanner.add_sentinel(sentinel)

    final = e3._scan_and_teardown(
        ScenarioResult("e3", "E3", Status.PASS, [e3.E3_CLASS], detail="passed"),
        scanner,
        scratch,
        child_outputs=child_outputs,
        ambient_snapshots={},
        credential_guards=guards,
        claude_dest=claude_dest,
        codex_dest=codex_dest,
        profile_root=profile_root,
        host2=host2,
        seed_parent=seed_parent,
    )

    serialized = serialize_report([final]).encode()
    expected_warning = (
        "credential-child-output-detected"
        if surface == "child"
        else "credential-scan-detected"
    )
    assert final.status is Status.INVALID
    assert expected_warning in final.warnings
    assert representation not in serialized


@pytest.mark.parametrize("representation_index", (0, 1, 2))
def test_controlled_sentinel_forms_in_final_candidate_are_discarded(
    representation_index,
):
    sentinel = "bive3-sentinel-" + "c" * 63 + "/"
    representation = (
        sentinel.encode("ascii"),
        sentinel.replace("/", r"\/").encode("ascii"),
        "".join(f"\\u{ord(character):04x}" for character in sentinel).encode(
            "ascii"
        ),
    )[representation_index]
    scanner = e3._CredentialScanner()
    scanner.add_sentinel(sentinel)

    final = e3._finalize_report(
        ScenarioResult(
            "e3",
            "E3",
            Status.FAIL,
            [],
            detail=representation.decode("ascii"),
        ),
        scanner,
    )

    serialized = serialize_report([final]).encode()
    assert final.status is Status.INVALID
    assert representation not in serialized
    assert not scanner.scan_bytes(serialized)


@pytest.mark.parametrize("credential_id", ("claude-code", "codex"))
@pytest.mark.parametrize("mutation", ("missing", "replaced"))
def test_scan_and_teardown_rejects_each_changed_credential_guard_during_tree_scan(
    tmp_path, credential_id, mutation
):
    (
        scratch,
        seed_parent,
        host2,
        profile_root,
        claude_dest,
        codex_dest,
        guards,
    ) = _guarded_teardown_paths(tmp_path)
    target = claude_dest if credential_id == "claude-code" else codex_dest
    target.unlink()
    if mutation == "replaced":
        target.write_bytes(b"replacement-object")

    class RecordingScanner(e3._CredentialScanner):
        def scan_tree_guarded(self, *args):
            scan_calls.append(args)
            return e3._CredentialScanOutcome(False, False)

    scan_calls = []
    scanner = RecordingScanner()
    scanner.add_value(b"guarded-teardown-secret")

    final = e3._scan_and_teardown(
        ScenarioResult("e3", "E3", Status.FAIL, [], detail="primary failure"),
        scanner,
        scratch,
        child_outputs=[],
        ambient_snapshots={},
        credential_guards=guards,
        claude_dest=claude_dest,
        codex_dest=codex_dest,
        profile_root=profile_root,
        host2=host2,
        seed_parent=seed_parent,
    )

    assert final.status is Status.INVALID
    assert "credential-exclusion-integrity-failed" in final.warnings
    assert scan_calls == []
    for cleanup_target in (
        claude_dest,
        codex_dest,
        profile_root,
        host2,
        seed_parent,
    ):
        with pytest.raises(FileNotFoundError):
            os.lstat(cleanup_target)


@pytest.mark.parametrize("mutation", ("nonregular", "multiply-linked", "colliding"))
def test_scan_and_teardown_rejects_unsafe_or_colliding_credential_guards(
    tmp_path, mutation
):
    (
        scratch,
        seed_parent,
        host2,
        profile_root,
        claude_dest,
        codex_dest,
        guards,
    ) = _guarded_teardown_paths(tmp_path)
    if mutation == "nonregular":
        codex_dest.unlink()
        codex_dest.mkdir()
    elif mutation == "multiply-linked":
        os.link(codex_dest, profile_root / "codex-auth-alias")
    else:
        guards["codex"] = guards["claude-code"]

    scanner = e3._CredentialScanner()
    scanner.add_value(b"guarded-teardown-secret")

    final = e3._scan_and_teardown(
        ScenarioResult("e3", "E3", Status.PASS, [], detail="passed"),
        scanner,
        scratch,
        child_outputs=[],
        ambient_snapshots={},
        credential_guards=guards,
        claude_dest=claude_dest,
        codex_dest=codex_dest,
        profile_root=profile_root,
        host2=host2,
        seed_parent=seed_parent,
    )

    assert final.status is Status.INVALID
    assert "credential-exclusion-integrity-failed" in final.warnings


def test_scan_and_teardown_binds_guard_identity_inside_exclusion_traversal(
    tmp_path,
):
    (
        scratch,
        seed_parent,
        host2,
        profile_root,
        claude_dest,
        codex_dest,
        guards,
    ) = _guarded_teardown_paths(tmp_path)

    class ReplacingScanner(e3._CredentialScanner):
        def scan_tree_guarded(self, root, exclusion_guards):
            codex_dest.unlink()
            codex_dest.write_bytes(b"replacement-object")
            return super().scan_tree_guarded(root, exclusion_guards)

    scanner = ReplacingScanner()
    scanner.add_value(b"guarded-teardown-secret")
    final = e3._scan_and_teardown(
        ScenarioResult("e3", "E3", Status.PASS, [], detail="passed"),
        scanner,
        scratch,
        child_outputs=[],
        ambient_snapshots={},
        credential_guards=guards,
        claude_dest=claude_dest,
        codex_dest=codex_dest,
        profile_root=profile_root,
        host2=host2,
        seed_parent=seed_parent,
    )

    assert final.status is Status.INVALID
    assert "credential-exclusion-integrity-failed" in final.warnings


def test_scan_and_teardown_rejects_changed_guard_metadata_before_scan(
    monkeypatch,
    tmp_path,
):
    (
        scratch,
        seed_parent,
        host2,
        profile_root,
        claude_dest,
        codex_dest,
        guards,
    ) = _guarded_teardown_paths(tmp_path)
    real_entry_status = e3._entry_status

    def changed_entry_status(parent_descriptor, name):
        current = real_entry_status(parent_descriptor, name)
        if current is not None and name == codex_dest.name:
            return _same_entry_changed_metadata(current)
        return current

    class RecordingScanner(e3._CredentialScanner):
        def scan_tree_guarded(self, *args):
            scan_calls.append(args)
            return e3._CredentialScanOutcome(False, False)

    monkeypatch.setattr(e3, "_entry_status", changed_entry_status)
    scan_calls = []
    scanner = RecordingScanner()
    scanner.add_value(b"guarded-teardown-secret")

    final = e3._scan_and_teardown(
        ScenarioResult("e3", "E3", Status.PASS, [], detail="passed"),
        scanner,
        scratch,
        child_outputs=[],
        ambient_snapshots={},
        credential_guards=guards,
        claude_dest=claude_dest,
        codex_dest=codex_dest,
        profile_root=profile_root,
        host2=host2,
        seed_parent=seed_parent,
    )

    assert final.status is Status.INVALID
    assert "credential-exclusion-integrity-failed" in final.warnings
    assert scan_calls == []


def test_scan_and_teardown_rejects_changed_guard_metadata_during_traversal(
    tmp_path,
):
    (
        scratch,
        seed_parent,
        host2,
        profile_root,
        claude_dest,
        codex_dest,
        guards,
    ) = _guarded_teardown_paths(tmp_path)

    class MetadataDriftScanner(e3._CredentialScanner):
        def scan_tree_guarded(self, root, exclusion_guards):
            changed = dict(exclusion_guards)
            changed[codex_dest] = _same_entry_changed_metadata(changed[codex_dest])
            return super().scan_tree_guarded(root, changed)

    scanner = MetadataDriftScanner()
    scanner.add_value(b"guarded-teardown-secret")
    final = e3._scan_and_teardown(
        ScenarioResult("e3", "E3", Status.PASS, [], detail="passed"),
        scanner,
        scratch,
        child_outputs=[],
        ambient_snapshots={},
        credential_guards=guards,
        claude_dest=claude_dest,
        codex_dest=codex_dest,
        profile_root=profile_root,
        host2=host2,
        seed_parent=seed_parent,
    )

    assert final.status is Status.INVALID
    assert "credential-exclusion-integrity-failed" in final.warnings


def test_scan_and_teardown_attempts_every_cleanup_after_guard_failure(
    monkeypatch,
    tmp_path,
):
    (
        scratch,
        seed_parent,
        host2,
        profile_root,
        claude_dest,
        codex_dest,
        guards,
    ) = _guarded_teardown_paths(tmp_path)
    guards.pop("codex")
    unlink_calls = []
    rmtree_calls = []
    real_unlink = e3.Path.unlink
    real_rmtree = e3.shutil.rmtree

    def recording_unlink(path, *args, **kwargs):
        unlink_calls.append(Path(path))
        if Path(path) == claude_dest:
            raise RuntimeError("injected unlink failure")
        return real_unlink(path, *args, **kwargs)

    def recording_rmtree(path, *args, **kwargs):
        rmtree_calls.append(Path(path))
        if Path(path) == profile_root:
            raise RuntimeError("injected rmtree failure")
        return real_rmtree(path, *args, **kwargs)

    monkeypatch.setattr(e3.Path, "unlink", recording_unlink)
    monkeypatch.setattr(e3.shutil, "rmtree", recording_rmtree)
    scanner = e3._CredentialScanner()
    scanner.add_value(b"guarded-teardown-secret")
    final = e3._scan_and_teardown(
        ScenarioResult("e3", "E3", Status.FAIL, [], detail="primary failure"),
        scanner,
        scratch,
        child_outputs=[],
        ambient_snapshots={},
        credential_guards=guards,
        claude_dest=claude_dest,
        codex_dest=codex_dest,
        profile_root=profile_root,
        host2=host2,
        seed_parent=seed_parent,
    )

    assert final.status is Status.INVALID
    assert "credential-exclusion-integrity-failed" in final.warnings
    assert unlink_calls == [claude_dest, codex_dest]
    assert rmtree_calls == [profile_root, host2, seed_parent]


def test_scan_and_teardown_tree_hit_invalidates_preexisting_fail_and_stays_clean(
    tmp_path,
):
    (
        scratch,
        seed_parent,
        host2,
        profile_root,
        claude_dest,
        codex_dest,
        guards,
    ) = _guarded_teardown_paths(tmp_path)
    (seed_parent / "credential-copy").write_bytes(b"guarded-teardown-secret")
    scanner = e3._CredentialScanner()
    scanner.add_value(b"guarded-teardown-secret")

    final = e3._scan_and_teardown(
        ScenarioResult("e3", "E3", Status.FAIL, ["failed"], detail="primary failure"),
        scanner,
        scratch,
        child_outputs=[],
        ambient_snapshots={},
        credential_guards=guards,
        claude_dest=claude_dest,
        codex_dest=codex_dest,
        profile_root=profile_root,
        host2=host2,
        seed_parent=seed_parent,
    )

    report_scanner = e3._CredentialScanner()
    report_scanner.add_value(b"guarded-teardown-secret")
    serialized = serialize_report([final]).encode()
    assert final.status is Status.INVALID
    assert final.classes == []
    assert final.held_asserts == []
    assert "credential-scan-detected" in final.warnings
    assert not report_scanner.scan_bytes(serialized)


def test_scan_and_teardown_child_hit_keeps_preexisting_invalid_and_stays_clean(
    tmp_path,
):
    (
        scratch,
        seed_parent,
        host2,
        profile_root,
        claude_dest,
        codex_dest,
        guards,
    ) = _guarded_teardown_paths(tmp_path)
    scanner = e3._CredentialScanner()
    scanner.add_value(b"guarded-teardown-secret")

    final = e3._scan_and_teardown(
        ScenarioResult("e3", "E3", Status.INVALID, [], detail="primary invalid"),
        scanner,
        scratch,
        child_outputs=[b"guarded-teardown-secret"],
        ambient_snapshots={},
        credential_guards=guards,
        claude_dest=claude_dest,
        codex_dest=codex_dest,
        profile_root=profile_root,
        host2=host2,
        seed_parent=seed_parent,
    )

    report_scanner = e3._CredentialScanner()
    report_scanner.add_value(b"guarded-teardown-secret")
    serialized = serialize_report([final]).encode()
    assert final.status is Status.INVALID
    assert "credential-child-output-detected" in final.warnings
    assert not report_scanner.scan_bytes(serialized)


def test_scan_and_teardown_scans_seed_tree_before_removing_all_targets(tmp_path):
    scratch = tmp_path / "scratch"
    seed_parent = scratch / "seed-ws"
    host2 = scratch / "host2"
    profile_root = scratch / "host2-profile"
    claude_dest = profile_root / "claude" / ".credentials.json"
    codex_dest = profile_root / "codex" / "auth.json"
    secret = b"teardown-seed-copy-secret"
    for path in (claude_dest, codex_dest):
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(secret)
    (seed_parent / "image-era-copy").parent.mkdir(parents=True)
    (seed_parent / "image-era-copy").write_bytes(secret)
    host2.mkdir(parents=True)
    scanner = e3._CredentialScanner()
    scanner.add_value(secret)
    primary = ScenarioResult("e3", "E3", Status.PASS, [], detail="passed")

    final = e3._scan_and_teardown(
        primary,
        scanner,
        scratch,
        child_outputs=[],
        ambient_snapshots={},
        credential_guards=_current_credential_guards(claude_dest, codex_dest),
        claude_dest=claude_dest,
        codex_dest=codex_dest,
        profile_root=profile_root,
        host2=host2,
        seed_parent=seed_parent,
    )

    assert final.status is Status.INVALID
    assert secret.decode() not in serialize_report([final])
    assert not any(path.exists() for path in (claude_dest, codex_dest, profile_root, host2, seed_parent))


def test_scan_and_teardown_clears_pass_evidence_and_continues_after_cleanup_error(
    monkeypatch, tmp_path
):
    scratch = tmp_path / "scratch"
    seed_parent = scratch / "seed-ws"
    host2 = scratch / "host2"
    profile_root = scratch / "host2-profile"
    claude_dest = profile_root / "claude" / ".credentials.json"
    codex_dest = profile_root / "codex" / "auth.json"
    for path in (claude_dest, codex_dest):
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(b"teardown-helper-secret")
    host2.mkdir(parents=True)
    seed_parent.mkdir(parents=True)
    scanner = e3._CredentialScanner()
    scanner.add_value(b"teardown-helper-secret")
    rmtree_calls = []
    real_rmtree = e3.shutil.rmtree

    def broken_first_rmtree(path, *args, **kwargs):
        rmtree_calls.append(Path(path))
        if Path(path) == profile_root:
            raise RuntimeError("unexpected cleanup failure")
        return real_rmtree(path, *args, **kwargs)

    monkeypatch.setattr(e3.shutil, "rmtree", broken_first_rmtree)
    final = e3._scan_and_teardown(
        ScenarioResult("e3", "E3", Status.PASS, ["held-class"], ["held-assert"], detail="passed"),
        scanner,
        scratch,
        child_outputs=[b"teardown-helper-secret"],
        ambient_snapshots={},
        credential_guards=_current_credential_guards(claude_dest, codex_dest),
        claude_dest=claude_dest,
        codex_dest=codex_dest,
        profile_root=profile_root,
        host2=host2,
        seed_parent=seed_parent,
    )

    assert final.status is Status.INVALID
    assert final.classes == []
    assert final.held_asserts == []
    assert rmtree_calls == [profile_root, host2, seed_parent]
    assert not host2.exists()
    assert not seed_parent.exists()
    assert "cleanup-rmtree-failed" in final.warnings


def test_scan_and_teardown_drop_failure_returns_a_fresh_scanned_constant(tmp_path):
    class BrokenDropScanner:
        active = False

        def __init__(self):
            self.scanned = []

        def scan_bytes(self, value):
            self.scanned.append(bytes(value))
            return False

        def drop(self):
            raise RuntimeError("drop failed")

    scanner = BrokenDropScanner()
    scratch = tmp_path / "scratch"
    final = e3._scan_and_teardown(
        ScenarioResult("e3", "E3", Status.PASS, [], detail="passed"),
        scanner,
        scratch,
        child_outputs=[],
        ambient_snapshots={},
        credential_guards={},
        claude_dest=scratch / "profile" / ".credentials.json",
        codex_dest=scratch / "profile" / "auth.json",
        profile_root=scratch / "profile",
        host2=scratch / "host2",
        seed_parent=scratch / "seed-ws",
    )

    assert final.status is Status.INVALID
    assert final.detail == e3._SANITIZED_REPORT_DETAIL
    assert serialize_report([final]).encode("utf-8") in scanner.scanned


def test_scan_and_teardown_activation_failure_returns_only_typed_constant_invalid(
    tmp_path,
):
    class BrokenActiveScanner(e3._CredentialScanner):
        @property
        def active(self):
            raise RuntimeError("active unavailable")

    secret = "REFRESHED_REAL_CREDENTIAL_VALUE_7f1a"
    scratch = tmp_path / "scratch"
    scanner = BrokenActiveScanner()
    scanner.add_value(b"CONTROLLED_RUNTIME_SENTINEL_activation_failure")
    final = e3._scan_and_teardown(
        ScenarioResult(
            "unsafe-primary",
            "E3",
            Status.FAIL,
            ["unsafe-class"],
            ["unsafe-assert"],
            detail="unsafe-primary-detail",
            warnings=[secret],
        ),
        scanner,
        scratch,
        child_outputs=[],
        ambient_snapshots={},
        credential_guards={},
        claude_dest=scratch / "profile" / ".credentials.json",
        codex_dest=scratch / "profile" / "auth.json",
        profile_root=scratch / "profile",
        host2=scratch / "host2",
        seed_parent=scratch / "seed-ws",
        remove_targets=False,
    )

    assert final == ScenarioResult(
        id="e3-report-refused",
        tier="E3",
        status=Status.INVALID,
        classes=[],
        held_asserts=[],
        detail="report refused: result could not be sanitized",
        warnings=[],
    )
    assert secret not in serialize_report([final])


def test_scan_and_teardown_empty_scanner_returns_only_typed_constant_invalid(
    tmp_path,
):
    secret = "REFRESHED_REAL_CREDENTIAL_VALUE_empty_scanner"
    scratch = tmp_path / "scratch"
    scanner = e3._CredentialScanner()
    assert scanner.active is False
    final = e3._scan_and_teardown(
        ScenarioResult(
            "unsafe-empty-primary",
            "E3",
            Status.FAIL,
            ["unsafe-class"],
            ["unsafe-assert"],
            detail="unsafe-empty-primary-detail",
            warnings=[secret],
        ),
        scanner,
        scratch,
        child_outputs=[],
        ambient_snapshots={},
        credential_guards={},
        claude_dest=scratch / "profile" / ".credentials.json",
        codex_dest=scratch / "profile" / "auth.json",
        profile_root=scratch / "profile",
        host2=scratch / "host2",
        seed_parent=scratch / "seed-ws",
        remove_targets=False,
    )

    assert final == ScenarioResult(
        id="e3-report-refused",
        tier="E3",
        status=Status.INVALID,
        classes=[],
        held_asserts=[],
        detail="report refused: result could not be sanitized",
        warnings=[],
    )
    assert secret not in serialize_report([final])


def test_scan_and_teardown_drop_failure_honors_positive_constant_rescan(tmp_path):
    class BrokenDropScanner:
        active = False

        def __init__(self):
            self.calls = 0

        def scan_bytes(self, value):
            self.calls += 1
            return self.calls >= 2

        def drop(self):
            raise RuntimeError("drop failed")

    scanner = BrokenDropScanner()
    scratch = tmp_path / "scratch"
    final = e3._scan_and_teardown(
        ScenarioResult("e3", "E3", Status.PASS, [], detail="passed"),
        scanner,
        scratch,
        child_outputs=[],
        ambient_snapshots={},
        credential_guards={},
        claude_dest=scratch / "profile" / ".credentials.json",
        codex_dest=scratch / "profile" / "auth.json",
        profile_root=scratch / "profile",
        host2=scratch / "host2",
        seed_parent=scratch / "seed-ws",
    )

    assert scanner.calls == 3
    assert final == e3._nonwritable_sanitized_report_result()
    assert json.loads(serialize_report([final]))["invalid"] == ["e3-report-refused"]


def test_scan_and_teardown_internal_finalizer_failure_rescans_constant_ladder(
    monkeypatch, tmp_path
):
    class ConstantScanner:
        active = False

        def __init__(self):
            self.calls = 0

        def scan_bytes(self, value):
            self.calls += 1
            return self.calls == 1

        def drop(self):
            return None

    monkeypatch.setattr(
        e3,
        "_finalize_report",
        lambda *_args: (_ for _ in ()).throw(RuntimeError("finalizer failed")),
    )
    scanner = ConstantScanner()
    scratch = tmp_path / "scratch"
    final = e3._scan_and_teardown(
        ScenarioResult("e3", "E3", Status.PASS, [], detail="passed"),
        scanner,
        scratch,
        child_outputs=[],
        ambient_snapshots={},
        credential_guards={},
        claude_dest=scratch / "profile" / ".credentials.json",
        codex_dest=scratch / "profile" / "auth.json",
        profile_root=scratch / "profile",
        host2=scratch / "host2",
        seed_parent=scratch / "seed-ws",
    )

    assert scanner.calls == 2
    assert final == e3._minimal_sanitized_report_result()


@pytest.mark.parametrize(
    "snapshot_outcome",
    (
        e3.SourceIdentity(9, 9, 9, "drifted"),
        None,
        RuntimeError("ambient unreadable"),
    ),
    ids=("drifted", "short-or-missing", "unreadable"),
)
def test_scan_and_teardown_invalidates_each_codex_ambient_drift(
    monkeypatch, tmp_path, snapshot_outcome
):
    scanner = e3._CredentialScanner()
    scanner.add_value(b"credential-secret")
    expected = e3.SourceIdentity(1, 2, 3, "expected")

    def fake_snapshot(*args, **kwargs):
        if isinstance(snapshot_outcome, Exception):
            raise snapshot_outcome
        return snapshot_outcome

    monkeypatch.setattr(e3, "snapshot_identity", fake_snapshot)
    scratch = tmp_path / "scratch"
    final = e3._scan_and_teardown(
        ScenarioResult("e3", "E3", Status.PASS, ["pass"], ["held"], detail="passed"),
        scanner,
        scratch,
        child_outputs=[],
        ambient_snapshots={"codex-auth.json": expected},
        credential_guards={},
        claude_dest=scratch / "profile" / ".credentials.json",
        codex_dest=scratch / "profile" / "auth.json",
        profile_root=scratch / "profile",
        host2=scratch / "host2",
        seed_parent=scratch / "seed-ws",
        remove_targets=False,
    )

    assert final.status is Status.INVALID
    assert final.classes == []
    assert final.held_asserts == []
    assert "codex-ambient-credential-drift" in final.warnings


@pytest.mark.parametrize("profile_topology", ("sibling", "nested"))
def test_scan_and_teardown_removes_all_targets_in_both_profile_topologies(
    tmp_path, profile_topology
):
    scratch = tmp_path / "scratch"
    host2 = scratch / "host2"
    profile_root = (
        scratch / "host2-profile"
        if profile_topology == "sibling"
        else host2 / "profiles"
    )
    seed_parent = scratch / "seed-ws"
    claude_dest = profile_root / "claude" / ".credentials.json"
    codex_dest = profile_root / "codex" / "auth.json"
    for path in (claude_dest, codex_dest):
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(b"credential-secret")
    seed_parent.mkdir(parents=True)
    scanner = e3._CredentialScanner()
    scanner.add_value(b"credential-secret")

    final = e3._scan_and_teardown(
        ScenarioResult("e3", "E3", Status.FAIL, [], detail="primary failure"),
        scanner,
        scratch,
        child_outputs=[],
        ambient_snapshots={},
        credential_guards=_current_credential_guards(claude_dest, codex_dest),
        claude_dest=claude_dest,
        codex_dest=codex_dest,
        profile_root=profile_root,
        host2=host2,
        seed_parent=seed_parent,
    )

    assert final.status is Status.FAIL
    assert final.detail == "e3-post-materialization-fail"
    for target in (claude_dest, codex_dest, profile_root, host2, seed_parent):
        with pytest.raises(FileNotFoundError):
            os.lstat(target)


def test_scan_and_teardown_attempts_all_targets_after_non_oserror_stat_failure(
    monkeypatch, tmp_path
):
    scratch = tmp_path / "scratch"
    profile_root = scratch / "host2-profile"
    host2 = scratch / "host2"
    seed_parent = scratch / "seed-ws"
    claude_dest = profile_root / "claude" / ".credentials.json"
    codex_dest = profile_root / "codex" / "auth.json"
    for path in (claude_dest, codex_dest):
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(b"credential-secret")
    host2.mkdir(parents=True)
    seed_parent.mkdir(parents=True)
    targets = (claude_dest, codex_dest, profile_root, host2, seed_parent)
    target_calls = {target: 0 for target in targets}
    real_lstat = e3.os.lstat

    def flaky_lstat(path, *args, **kwargs):
        candidate = Path(path)
        if candidate in target_calls:
            target_calls[candidate] += 1
            if candidate == claude_dest and target_calls[candidate] == 1:
                raise RuntimeError("non-oserror stat failure")
        return real_lstat(path, *args, **kwargs)

    monkeypatch.setattr(e3.os, "lstat", flaky_lstat)
    scanner = e3._CredentialScanner()
    scanner.add_value(b"credential-secret")
    final = e3._scan_and_teardown(
        ScenarioResult("e3", "E3", Status.FAIL, [], detail="primary failure"),
        scanner,
        scratch,
        child_outputs=[],
        ambient_snapshots={},
        credential_guards=_current_credential_guards(claude_dest, codex_dest),
        claude_dest=claude_dest,
        codex_dest=codex_dest,
        profile_root=profile_root,
        host2=host2,
        seed_parent=seed_parent,
    )

    assert final.status is Status.FAIL
    assert final.detail == "e3-post-materialization-fail"
    assert "cleanup-stat-failed" in final.warnings
    assert all(count >= 1 for count in target_calls.values())
    assert all(count >= 2 for count in target_calls.values())


def test_scan_and_teardown_folds_unlink_failure_and_preserves_primary(
    monkeypatch, tmp_path
):
    scratch = tmp_path / "scratch"
    profile_root = scratch / "host2-profile"
    host2 = scratch / "host2"
    seed_parent = scratch / "seed-ws"
    claude_dest = profile_root / "claude" / ".credentials.json"
    codex_dest = profile_root / "codex" / "auth.json"
    for path in (claude_dest, codex_dest):
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(b"credential-secret")
    host2.mkdir(parents=True)
    seed_parent.mkdir(parents=True)
    real_unlink = e3.Path.unlink

    def flaky_unlink(path, *args, **kwargs):
        if Path(path) == claude_dest:
            raise RuntimeError("non-oserror unlink failure")
        return real_unlink(path, *args, **kwargs)

    monkeypatch.setattr(e3.Path, "unlink", flaky_unlink)
    scanner = e3._CredentialScanner()
    scanner.add_value(b"credential-secret")
    final = e3._scan_and_teardown(
        ScenarioResult("e3", "E3", Status.FAIL, [], detail="primary failure"),
        scanner,
        scratch,
        child_outputs=[],
        ambient_snapshots={},
        credential_guards=_current_credential_guards(claude_dest, codex_dest),
        claude_dest=claude_dest,
        codex_dest=codex_dest,
        profile_root=profile_root,
        host2=host2,
        seed_parent=seed_parent,
    )

    assert final.status is Status.FAIL
    assert final.detail == "e3-post-materialization-fail"
    assert "cleanup-unlink-failed" in final.warnings
    assert not any(
        target.exists()
        for target in (claude_dest, codex_dest, profile_root, host2, seed_parent)
    )


def test_scan_and_teardown_folds_absence_stat_failure_after_all_removals(
    monkeypatch, tmp_path
):
    scratch = tmp_path / "scratch"
    profile_root = scratch / "host2-profile"
    host2 = scratch / "host2"
    seed_parent = scratch / "seed-ws"
    claude_dest = profile_root / "claude" / ".credentials.json"
    codex_dest = profile_root / "codex" / "auth.json"
    for path in (claude_dest, codex_dest):
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(b"credential-secret")
    host2.mkdir(parents=True)
    seed_parent.mkdir(parents=True)
    targets = (claude_dest, codex_dest, profile_root, host2, seed_parent)
    calls = {target: 0 for target in targets}
    real_lstat = e3.os.lstat

    def flaky_lstat(path, *args, **kwargs):
        candidate = Path(path)
        if candidate in calls:
            calls[candidate] += 1
            if candidate == claude_dest and calls[candidate] == 2:
                raise RuntimeError("absence stat failure")
        return real_lstat(path, *args, **kwargs)

    monkeypatch.setattr(e3.os, "lstat", flaky_lstat)
    scanner = e3._CredentialScanner()
    scanner.add_value(b"credential-secret")
    final = e3._scan_and_teardown(
        ScenarioResult("e3", "E3", Status.FAIL, [], detail="primary failure"),
        scanner,
        scratch,
        child_outputs=[],
        ambient_snapshots={},
        credential_guards=_current_credential_guards(claude_dest, codex_dest),
        claude_dest=claude_dest,
        codex_dest=codex_dest,
        profile_root=profile_root,
        host2=host2,
        seed_parent=seed_parent,
    )

    assert final.status is Status.FAIL
    assert final.detail == "e3-post-materialization-fail"
    assert "cleanup-absence-stat-failed" in final.warnings
    assert all(count >= 2 for count in calls.values())


def test_finalize_report_handles_serializer_failure_without_raising(monkeypatch):
    scanner = e3._CredentialScanner()
    scanner.add_value(b"scanner-finalize-secret")
    monkeypatch.setattr(
        e3,
        "serialize_report",
        lambda results: (_ for _ in ()).throw(RuntimeError("broken serializer")),
    )

    final = e3._finalize_report(
        ScenarioResult("id", "E3", Status.FAIL, [], detail="scanner-finalize-secret"),
        scanner,
    )

    assert final == e3._nonwritable_sanitized_report_result()
    assert json.loads(serialize_report([final]))["invalid"] == ["e3-report-refused"]


def test_finalize_report_swallows_a_rescan_failure_after_sanitizing():
    class BrokenRescan:
        def __init__(self):
            self.calls = 0

        def scan_bytes(self, blob):
            self.calls += 1
            if self.calls == 1:
                return True
            if self.calls == 2:
                raise RuntimeError("rescan failed")
            return False

    scanner = BrokenRescan()
    final = e3._finalize_report(
        ScenarioResult("id", "E3", Status.FAIL, [], detail="unsafe"),
        scanner,
    )

    assert scanner.calls == 2
    assert final == e3._nonwritable_sanitized_report_result()
    assert json.loads(serialize_report([final]))["invalid"] == ["e3-report-refused"]


def test_finalize_report_uses_minimal_fallback_on_positive_sanitized_rescan():
    scanner = e3._CredentialScanner()
    scanner.add_value(b"E3")

    final = e3._finalize_report(
        ScenarioResult("id", "E3", Status.FAIL, [], detail="unsafe"),
        scanner,
    )

    assert b"E3" not in serialize_report([final]).encode("utf-8")
    assert final.status is Status.INVALID
    assert final.id == ""
    assert final.tier == ""
    assert final.detail == ""
    assert final.classes == []
    assert final.held_asserts == []
    assert final.warnings == []


@pytest.mark.parametrize("fallback_outcome", ["hit", "error"])
def test_finalize_report_returns_minimal_fallback_when_its_scan_fails(
    fallback_outcome,
):
    class FallbackScanner:
        def __init__(self):
            self.calls = 0

        def scan_bytes(self, blob):
            self.calls += 1
            if self.calls < 3 or fallback_outcome == "hit":
                return True
            raise RuntimeError("fallback scan failed")

    scanner = FallbackScanner()
    final = e3._finalize_report(
        ScenarioResult("id", "E3", Status.FAIL, [], detail="unsafe"),
        scanner,
    )

    assert scanner.calls == 3
    assert final == e3._nonwritable_sanitized_report_result()
    assert json.loads(serialize_report([final]))["invalid"] == ["e3-report-refused"]


def test_finalize_report_returns_serializable_constant_after_positive_terminal_scan():
    scanner = e3._CredentialScanner()
    scanner.add_value(b'"classes": []')

    final = e3._finalize_report(
        ScenarioResult("id", "E3", Status.FAIL, [], detail="unsafe"),
        scanner,
    )

    assert final == e3._nonwritable_sanitized_report_result()
    assert json.loads(serialize_report([final]))["invalid"] == ["e3-report-refused"]


def test_class_j_workspace_memoryless_and_version_predicates(tmp_path):
    seed = tmp_path / "seed"
    restored = tmp_path / "restored"
    seed.mkdir()
    restored.mkdir()

    assert class_j_failures(seed, restored, [tmp_path / "biv-owned"]) == []
    assert "workspace-paths-not-distinct" in class_j_failures(seed, seed, [])
    app_state = tmp_path / "biv-owned"
    app_state.mkdir()
    assert "bivpak-state-present" in class_j_failures(seed, restored, [app_state])
    assert version_in_validated_range("claude 2.1.202", ["2.1."])
    assert not version_in_validated_range("claude 2.2.0", ["2.1."])
    assert not version_in_validated_range("claude 12.1.202", ["2.1."])


CX = ["0.142.", "0.144."]
STALE_VERSION_PREFIX_KEY = "validated_version_" + "prefix"


@pytest.mark.parametrize("version,accepted", [
    ("codex-cli 0.142.5", True),
    ("codex-cli 0.144.1", True),
    ("codex-cli 0.143.0", False),
    ("codex-cli 0.145.0", False),
    ("codex-cli 0.61.0", False),
])
def test_codex_enumerated_set_is_not_an_inequality(version, accepted):
    assert version_in_validated_range(version, CX) is accepted


@pytest.mark.parametrize("output", (
    "codex-cli 0.145.0\nsandbox-runtime 0.142.9\n",
    "sandbox-runtime 0.142.9\ncodex-cli 0.145.0\n",
))
def test_version_gate_rejects_ambiguous_multi_token_output(output):
    assert not version_in_validated_range(output, CX)


@pytest.mark.parametrize("version,accepted", [
    ("claude 2.1.202", True),
    ("claude 2.2.0", False),
    ("claude 12.1.202", False),
])
def test_claude_single_element_list(version, accepted):
    assert version_in_validated_range(version, ["2.1."]) is accepted


@pytest.mark.parametrize("bad", ["0.142.", "", [], ["0.142.", ""], [None], ("0.142.",)])
def test_helper_raises_rather_than_character_iterating(bad):
    with pytest.raises(TypeError):
        version_in_validated_range("codex-cli 0.61.0", bad)


@pytest.mark.parametrize("bad", ["0.142.", [], ["0.142.", ""], [None]])
def test_validate_spec_rejects_malformed_prefix_shapes(bad):
    spec = _valid_two_agent_spec()
    spec["agents"][0]["validated_version_prefixes"] = bad
    failures = e3._validate_spec(spec)
    assert any("validated_version_prefixes" in failure for failure in failures)


def test_validate_spec_rejects_a_stale_scalar_only_scenario():
    spec = _valid_two_agent_spec()
    agent = spec["agents"][0]
    del agent["validated_version_prefixes"]
    agent[STALE_VERSION_PREFIX_KEY] = "0.142."
    failures = e3._validate_spec(spec)
    assert any("validated_version_prefixes" in failure for failure in failures)


def test_stale_scenario_is_invalid_before_any_spawn(monkeypatch, tmp_path):
    calls = []

    def fake_spawn(command, cwd, env):
        calls.append(command)
        return SimpleNamespace(returncode=0, stdout="codex-cli 0.61.0", stderr="")

    monkeypatch.setattr(e3, "_spawn", fake_spawn)
    spec = _valid_two_agent_spec()
    agent = spec["agents"][0]
    del agent["validated_version_prefixes"]
    agent[STALE_VERSION_PREFIX_KEY] = "0.142."
    spec_path = tmp_path / "e3.json"
    spec_path.write_text(json.dumps(spec), encoding="utf-8")

    result = e3.run_e3(spec_path, Path("biv"), tmp_path / "scratch", dry_run=True)

    assert result.status is Status.INVALID
    assert "validated_version_prefixes" in result.detail
    assert calls == []


CX_MATRIX = [
    ("0.142.5", True),
    ("0.144.1", True),
    ("0.143.0", False),
    ("0.145.0", False),
    ("0.61.0", False),
]


def _run_prerun_with_codex_version(monkeypatch, tmp_path, stable_test_root, version):
    calls = []

    def fake_spawn(command, cwd, env):
        calls.append(command)
        if command[1:] == ["--version"]:
            output = version if _agent_basename(command) == "codex" else "2.1.210"
            return SimpleNamespace(returncode=0, stdout=output, stderr="")
        if command[1:] == ["auth", "status"] and _agent_basename(command) == "claude":
            return SimpleNamespace(returncode=1, stdout="", stderr="not logged in")
        return SimpleNamespace(returncode=0, stdout="", stderr="")

    monkeypatch.setattr(e3, "_spawn", fake_spawn)
    spec_path = tmp_path / "e3.json"
    spec_path.write_text(json.dumps(_valid_two_agent_spec()), encoding="utf-8")
    result = e3.run_e3(spec_path, Path("biv"), stable_test_root / "scratch")
    return result, calls


@pytest.mark.parametrize("version,accepted", CX_MATRIX)
def test_prerun_version_gate_enforces_the_enumerated_set(
    monkeypatch, tmp_path, stable_test_root, version, accepted
):
    result, calls = _run_prerun_with_codex_version(
        monkeypatch, tmp_path, stable_test_root, version
    )
    _assert_report_refused(result)
    assert _resolved_agent_command("codex", "--version") in calls
    if accepted:
        assert calls == [
            _resolved_agent_command("codex", "--version"),
            _resolved_agent_command("claude-code", "--version"),
            _resolved_agent_command("codex", "login", "status"),
            _resolved_agent_command("claude-code", "auth", "status"),
        ]
    else:
        assert calls == [
            _resolved_agent_command("codex", "--version"),
            _resolved_agent_command("claude-code", "--version"),
        ]


@pytest.mark.parametrize("version", (
    "codex-cli 0.145.0\nsandbox-runtime 0.142.9\n",
    "sandbox-runtime 0.142.9\ncodex-cli 0.145.0\n",
))
def test_prerun_version_gate_rejects_ambiguous_multi_token_output(
    monkeypatch, tmp_path, stable_test_root, version
):
    result, calls = _run_prerun_with_codex_version(
        monkeypatch,
        tmp_path,
        stable_test_root,
        version,
    )

    _assert_report_refused(result)
    assert calls == [
        _resolved_agent_command("codex", "--version"),
        _resolved_agent_command("claude-code", "--version"),
    ]


@pytest.mark.parametrize("version,accepted", CX_MATRIX)
def test_host2_version_gate_enforces_the_enumerated_set(tmp_path, version, accepted):
    calls = []

    def fake_spawn(command, cwd, env):
        calls.append(list(command))
        agent = _host2_agent_id(command)
        if agent == "claude-code":
            if "-p" in command:
                return SimpleNamespace(returncode=0, stdout="OK", stderr="")
            return SimpleNamespace(returncode=0, stdout="2.1.202", stderr="")
        return SimpleNamespace(returncode=0, stdout=version, stderr="")

    host2 = tmp_path / "host two"
    args = (
        {"agents": _host2_agents()},
        host2,
        host2 / "profiles",
        _host2_binaries(),
        fake_spawn,
        e3._CredentialScanner(),
        [],
        {},
    )
    if accepted:
        e3.setup_host2_credentials(*args)
        expected_agents = [
            "claude-code", "codex", "claude-code", "codex", "claude-code",
        ]
    else:
        with pytest.raises(ValueError, match="host2 version is outside the validated range"):
            e3.setup_host2_credentials(*args)
        expected_agents = ["claude-code", "codex"]
    _assert_host2_binary_ledger(calls, expected_agents)


def _symlinked_ancestor(tmp_path):
    real = tmp_path / "real"
    real.mkdir()
    link = tmp_path / "link"
    link.symlink_to(real, target_is_directory=True)
    shadowed = link / "child"
    assert not shadowed.is_symlink()
    return shadowed


def _run_dry(tmp_path, spec, scratch):
    spec_path = tmp_path / "e3.json"
    spec_path.write_text(json.dumps(spec), encoding="utf-8")
    return e3.run_e3(spec_path, Path("biv"), scratch, dry_run=True)


def _tree_snapshot(root):
    snapshot = {}
    paths = [root]
    if root.is_dir():
        for directory, dirnames, filenames in os.walk(root, followlinks=False):
            paths.extend(Path(directory) / name for name in dirnames + filenames)
    for path in sorted(paths):
        metadata = path.lstat()
        relative = "." if path == root else str(path.relative_to(root))
        mode = stat.S_IMODE(metadata.st_mode)
        if stat.S_ISLNK(metadata.st_mode):
            kind = "symlink"
            digest = None
            link_target = os.readlink(path)
        elif stat.S_ISREG(metadata.st_mode):
            kind = "file"
            digest = hashlib.sha256(path.read_bytes()).hexdigest()
            link_target = None
        elif stat.S_ISDIR(metadata.st_mode):
            kind = "directory"
            digest = None
            link_target = None
        else:
            kind = "other"
            digest = None
            link_target = None
        snapshot[relative] = (
            kind,
            mode,
            metadata.st_size,
            metadata.st_mtime_ns,
            digest,
            link_target,
        )
    return snapshot


def _run_refusal_without_side_effects(
    monkeypatch, tmp_path, spec, scratch, *, watched_roots=()
):
    spec_path = tmp_path / "e3.json"
    spec_path.write_text(json.dumps(spec), encoding="utf-8")
    roots = [tmp_path, *watched_roots]
    before = {root: _tree_snapshot(root) for root in roots}
    spawn_calls = []

    def refused_spawn(*args):
        spawn_calls.append(args)
        raise AssertionError("INVALID scenario must not spawn")

    monkeypatch.setattr(e3, "_spawn", refused_spawn)
    result = e3.run_e3(spec_path, Path("biv"), scratch, dry_run=True)

    assert spawn_calls == []
    assert {root: _tree_snapshot(root) for root in roots} == before
    return result


@pytest.mark.parametrize(
    "failing_check",
    ("scratch_overlap", "probe", "profile_root_failures"),
)
def test_e3_preflight_filesystem_errors_are_invalid(
    monkeypatch, tmp_path, stable_test_root, failing_check
):
    def raise_filesystem_error(*args):
        raise OSError("injected preflight filesystem error")

    if failing_check == "scratch_overlap":
        monkeypatch.setattr(e3, "_scratch_overlap_failures", raise_filesystem_error)
    elif failing_check == "probe":
        monkeypatch.setattr(e3, "probe", raise_filesystem_error)
    else:
        monkeypatch.setattr(e3, "probe", lambda scratch: [])
        monkeypatch.setattr(e3, "profile_root_failures", raise_filesystem_error)
    scenario = tmp_path / "e3.json"
    scenario.write_text(json.dumps(_valid_two_agent_spec()), encoding="utf-8")

    result = e3.run_e3(
        scenario,
        tmp_path / "biv",
        stable_test_root / "scratch",
        dry_run=True,
    )

    assert result.status is Status.INVALID
    assert "pre-run filesystem check failed" in result.detail
    assert "injected preflight filesystem error" in result.detail


def test_e3_poison_mode_probe_directory_is_invalid(
    tmp_path, stable_test_root
):
    scratch = stable_test_root / "scratch"
    poison = scratch / ".bivharness-mode-probe"
    poison.mkdir(parents=True)
    scenario = tmp_path / "e3.json"
    scenario.write_text(json.dumps(_valid_two_agent_spec()), encoding="utf-8")

    result = e3.run_e3(scenario, tmp_path / "biv", scratch, dry_run=True)

    assert result.status is Status.INVALID
    assert "pre-run filesystem check failed" in result.detail
    assert poison.is_dir()
    assert not (scratch / ".bivharness-link-probe").exists()


@pytest.mark.parametrize("field", ("live_profile", "live_store_roots"))
@pytest.mark.parametrize("relation", ("same", "scratch-inside-live", "live-inside-scratch"))
def test_e3_refuses_scratch_overlap_with_live_roots_before_probe(
    monkeypatch, tmp_path, stable_test_root, field, relation
):
    if relation == "same":
        scratch = stable_test_root / "scratch"
        live_root = scratch
    elif relation == "scratch-inside-live":
        live_root = stable_test_root / "live-root"
        scratch = live_root / "scratch"
    else:
        scratch = stable_test_root / "scratch"
        live_root = scratch / "live-root"
    spec = _valid_two_agent_spec()
    if field == "live_profile":
        spec["agents"][0][field] = str(live_root)
    else:
        spec[field] = [str(live_root)]

    result = _run_refusal_without_side_effects(
        monkeypatch,
        tmp_path,
        spec,
        scratch,
        watched_roots=(stable_test_root,),
    )

    assert result.status is Status.INVALID
    assert "scratch overlaps" in result.detail
    assert field in result.detail


ROOT_RELATIVE_FIELDS = (
    "host2_profile_root",
    "workspace_name",
    "host2_profile",
    "forbidden_bivpak_state",
)


def _set_root_relative_field(spec, field, value):
    if field == "host2_profile":
        spec["agents"][0][field] = value
    elif field == "forbidden_bivpak_state":
        spec[field] = [value]
    else:
        spec[field] = value


def _root_relative_root(scratch, field):
    if field == "workspace_name":
        return scratch / "seed-ws"
    if field == "host2_profile":
        return scratch / "host2-profile"
    return scratch


def _root_relative_case(stable_test_root, root, field, case, tmp_path):
    root.mkdir(parents=True, exist_ok=True)
    suffix = f"{field}-{os.getpid()}-{tmp_path.name}"
    if case == "A-abs-safe":
        target = stable_test_root / f"absolute-safe-{suffix}"
        return str(target), (target,), ()
    if case == "B-absolute-name":
        target = Path("/tmp").resolve() / f"bivharness-task7-child-{suffix}"
        return str(target), (target,), ()
    if case == "C-abs-unstable":
        physical = stable_test_root / f"physical-{suffix}"
        physical.mkdir()
        alias = stable_test_root / f"alias-{suffix}"
        alias.symlink_to(physical, target_is_directory=True)
        lexical = alias / "child"
        return str(lexical), (lexical, physical / "child"), ()
    if case == "D-cycle":
        loop_a = root / "loop-a"
        loop_b = root / "loop-b"
        loop_a.symlink_to("loop-b", target_is_directory=True)
        loop_b.symlink_to("loop-a", target_is_directory=True)
        return "loop-a/child", (), (loop_a, loop_b)
    if case == "F-dotdot":
        lexical = root / "../../escaped"
        return "../../escaped", (lexical, lexical.resolve()), ()
    if case == "G-contained-symlink":
        physical = root / "contained-physical"
        physical.mkdir()
        link = root / "contained"
        link.symlink_to(physical, target_is_directory=True)
        lexical = link / "child"
        return "contained/child", (lexical, physical / "child"), ()
    if case == "H-escaping-symlink":
        physical = stable_test_root / f"outside-{suffix}"
        physical.mkdir()
        link = root / "jump"
        link.symlink_to(physical, target_is_directory=True)
        lexical = link / "escaped"
        return "jump/escaped", (lexical, physical / "escaped"), ()
    if case == "J-dot":
        return ".", (), ()
    if case == "J-empty":
        return "", (), ()
    raise AssertionError(f"unknown root-relative case: {case}")


def _inject_identity_resolve_for(monkeypatch, cycle_path):
    real_resolve = Path.resolve

    def resolve_with_cycle_identity(self, *args, **kwargs):
        if self == cycle_path:
            return self
        return real_resolve(self, *args, **kwargs)

    monkeypatch.setattr(Path, "resolve", resolve_with_cycle_identity)


@pytest.mark.parametrize("field", ROOT_RELATIVE_FIELDS)
@pytest.mark.parametrize("case", (
    "A-abs-safe",
    "B-absolute-name",
    "C-abs-unstable",
    "D-cycle",
    "F-dotdot",
    "G-contained-symlink",
    "H-escaping-symlink",
    "J-dot",
    "J-empty",
))
def test_root_relative_path_matrix_refuses_without_side_effects(
    monkeypatch, tmp_path, stable_test_root, field, case
):
    scratch = stable_test_root / "sandbox" / "scratch"
    root = _root_relative_root(scratch, field)
    value, absent_targets, cycle_links = _root_relative_case(
        stable_test_root, root, field, case, tmp_path
    )
    if cycle_links:
        _inject_identity_resolve_for(monkeypatch, root / value)
    spec = _valid_two_agent_spec()
    _set_root_relative_field(spec, field, value)

    result = _run_refusal_without_side_effects(
        monkeypatch,
        tmp_path,
        spec,
        scratch,
        watched_roots=(stable_test_root,),
    )

    assert result.status is Status.INVALID, (field, case, result.detail)
    assert field in result.detail
    for target in absent_targets:
        assert not target.exists(), (field, case, target)
    for link in cycle_links:
        assert link.is_symlink()
    if cycle_links:
        assert list(stable_test_root.rglob(".bivharness-mode-probe")) == []
        assert list(stable_test_root.rglob(".bivharness-link-probe")) == []


@pytest.mark.parametrize("field", ("live_profile", "live_store_roots"))
def test_external_roots_refuse_relative_spellings_without_side_effects(
    monkeypatch, tmp_path, stable_test_root, field
):
    spec = _valid_two_agent_spec()
    if field == "live_profile":
        spec["agents"][0][field] = "relative/live-profile"
    else:
        spec[field] = ["relative/live-store"]

    result = _run_refusal_without_side_effects(
        monkeypatch,
        tmp_path,
        spec,
        stable_test_root / "scratch",
        watched_roots=(stable_test_root,),
    )

    assert result.status is Status.INVALID
    assert field in result.detail
    assert "realpath-stable" in result.detail


PATH_MATRIX_COLUMNS = (
    "A",
    "B",
    "C",
    "D",
    "E",
    "F",
    "G",
    "H",
    "I",
    "J",
    "K",
    "L",
    "M1",
    "M2",
)
PATH_POLICY_MATRIX = {
    "scratch": (
        "accept", "refuse", "refuse", "refuse", "refuse", "refuse", "n/a",
        "n/a", "refuse", "refuse", "n/a", "refuse", "refuse", "refuse",
    ),
    "host2_profile_root": (
        "refuse", "refuse", "refuse", "refuse", "accept", "refuse", "refuse",
        "refuse", "n/a", "refuse", "n/a", "refuse", "refuse", "refuse",
    ),
    "workspace_name": (
        "refuse", "refuse", "refuse", "refuse", "accept", "refuse", "refuse",
        "refuse", "n/a", "refuse", "n/a", "refuse", "refuse", "refuse",
    ),
    "host2_profile": (
        "refuse", "refuse", "refuse", "refuse", "accept", "refuse", "refuse",
        "refuse", "n/a", "refuse", "n/a", "refuse", "refuse", "refuse",
    ),
    "forbidden_bivpak_state": (
        "refuse", "refuse", "refuse", "refuse", "accept", "refuse", "refuse",
        "refuse", "n/a", "refuse", "refuse", "refuse", "refuse", "refuse",
    ),
    "live_profile": (
        "accept", "refuse", "refuse", "refuse", "n/a", "refuse", "n/a", "n/a",
        "refuse", "refuse", "n/a", "refuse", "refuse", "refuse",
    ),
    "live_store_roots": (
        "accept", "refuse", "refuse", "refuse", "n/a", "refuse", "n/a", "n/a",
        "refuse", "refuse", "refuse", "refuse", "refuse", "refuse",
    ),
}
PATH_POLICY_COLUMN_B_OWNERS = {
    "scratch": "temp-root",
    "host2_profile_root": "absolute-name",
    "workspace_name": "absolute-name",
    "host2_profile": "absolute-name",
    "forbidden_bivpak_state": "absolute-name",
    "live_profile": "temp-root",
    "live_store_roots": "temp-root",
}


def _path_matrix_cases():
    return [
        (field, column, verdict)
        for field, verdicts in PATH_POLICY_MATRIX.items()
        for column, verdict in zip(PATH_MATRIX_COLUMNS, verdicts, strict=True)
    ]


def test_path_policy_matrix_is_seven_by_fourteen():
    assert len(PATH_POLICY_MATRIX) == 7
    assert len(PATH_MATRIX_COLUMNS) == 14
    assert all(len(verdicts) == 14 for verdicts in PATH_POLICY_MATRIX.values())
    assert len(_path_matrix_cases()) == 98


def test_path_policy_column_b_guard_ownership_is_explicit():
    assert PATH_POLICY_COLUMN_B_OWNERS == {
        "scratch": "temp-root",
        "host2_profile_root": "absolute-name",
        "workspace_name": "absolute-name",
        "host2_profile": "absolute-name",
        "forbidden_bivpak_state": "absolute-name",
        "live_profile": "temp-root",
        "live_store_roots": "temp-root",
    }


def _set_matrix_path_value(spec, field, value, column):
    if field in ("live_profile", "live_store_roots") and isinstance(value, Path):
        value = str(value)
    if field == "host2_profile":
        spec["agents"][0][field] = value
    elif field == "forbidden_bivpak_state":
        spec[field] = value if column == "K" else [value]
    elif field == "live_profile":
        spec["agents"][0][field] = value
    elif field == "live_store_roots":
        spec[field] = value if column == "K" else [value]
    else:
        spec[field] = value


def _matrix_root_case(stable_test_root, tmp_path, field, column):
    spec = _valid_two_agent_spec()
    scratch = stable_test_root / "matrix" / "scratch"
    suffix = f"{field}-{column}-{os.getpid()}-{tmp_path.name}"
    absent_targets = []
    cycle_links = []
    cycle_path = None
    cleanup_targets = []

    if field in ROOT_RELATIVE_FIELDS:
        root = _root_relative_root(scratch, field)
        if not (field == "host2_profile" and column == "E"):
            root.mkdir(parents=True, exist_ok=True)
        if column == "E":
            value = f"safe-{suffix}"
        elif column == "K":
            value = {}
        elif column == "L":
            value = None
        elif column == "M1":
            value = "path\0segment"
        elif column == "M2":
            value = "~nosuchuser/e3"
        else:
            case = {
                "A": "A-abs-safe",
                "B": "B-absolute-name",
                "C": "C-abs-unstable",
                "D": "D-cycle",
                "F": "F-dotdot",
                "G": "G-contained-symlink",
                "H": "H-escaping-symlink",
                "J": "J-dot",
            }[column]
            value, absent_targets, cycle_links = _root_relative_case(
                stable_test_root, root, field, case, tmp_path
            )
            if column == "B":
                cleanup_targets.extend(absent_targets)
            if cycle_links:
                cycle_path = root / value
        _set_matrix_path_value(spec, field, value, column)
        return (
            spec,
            scratch,
            tuple(absent_targets),
            tuple(cycle_links),
            cycle_path,
            tuple(cleanup_targets),
        )

    if column == "A":
        value = stable_test_root / f"absolute-safe-{suffix}"
    elif column == "B":
        value = Path("/tmp").resolve() / f"bivharness-task9-{suffix}"
        absent_targets.append(value)
        cleanup_targets.append(value)
    elif column == "C":
        physical = stable_test_root / f"physical-{suffix}"
        physical.mkdir(parents=True)
        alias = stable_test_root / f"alias-{suffix}"
        alias.symlink_to(physical, target_is_directory=True)
        value = alias / "child"
        absent_targets.extend((value, physical / "child"))
    elif column == "D":
        loop_a = stable_test_root / f"loop-a-{suffix}"
        loop_b = stable_test_root / f"loop-b-{suffix}"
        loop_a.symlink_to(loop_b.name, target_is_directory=True)
        loop_b.symlink_to(loop_a.name, target_is_directory=True)
        value = loop_a / "child"
        cycle_links.extend((loop_a, loop_b))
        cycle_path = value
    elif column == "E":
        value = "relative-safe"
    elif column == "F":
        value = f"traversal-{suffix}/../escaped-{suffix}"
        absent_targets.append((stable_test_root / value).resolve())
    elif column == "I":
        value = "./cwd-relative"
        absent_targets.append(stable_test_root / "cwd-relative")
    elif column == "J":
        value = "."
    elif column == "K":
        value = {}
    elif column == "L":
        value = None
    elif column == "M1":
        value = (
            Path("scratch\0path")
            if field == "scratch"
            else str(stable_test_root / "path\0segment")
        )
    elif column == "M2":
        value = Path("~nosuchuser/e3") if field == "scratch" else "~nosuchuser/e3"
    else:
        raise AssertionError(f"unsupported matrix cell: {field}/{column}")

    if field == "scratch":
        scratch = value
    else:
        _set_matrix_path_value(spec, field, value, column)
    return (
        spec,
        scratch,
        tuple(absent_targets),
        tuple(cycle_links),
        cycle_path,
        tuple(cleanup_targets),
    )


@pytest.mark.parametrize(
    ("field", "column", "verdict"),
    _path_matrix_cases(),
    ids=lambda value: str(value),
)
def test_path_policy_matrix_at_runner_boundary(
    monkeypatch, tmp_path, stable_test_root, field, column, verdict
):
    if verdict == "n/a":
        return

    monkeypatch.chdir(stable_test_root)
    spec, scratch, absent_targets, cycle_links, cycle_path, cleanup_targets = (
        _matrix_root_case(stable_test_root, tmp_path, field, column)
    )
    for target in absent_targets:
        assert target.is_relative_to(stable_test_root) or target in cleanup_targets, (
            field,
            column,
            target,
        )
    if cycle_path is not None:
        _inject_identity_resolve_for(monkeypatch, cycle_path)

    try:
        if verdict == "accept":
            result = _run_dry(tmp_path, spec, scratch)
            assert result.status is Status.PASS, (field, column, result.detail)
            return

        result = _run_refusal_without_side_effects(
            monkeypatch,
            tmp_path,
            spec,
            scratch,
            watched_roots=(stable_test_root,),
        )

        assert result.status is Status.INVALID, (field, column, result.detail)
        assert field in result.detail, (field, column, result.detail)
        for target in absent_targets:
            assert not target.exists(), (field, column, target)
        for link in cycle_links:
            assert link.is_symlink(), (field, column, link)
        if cycle_links:
            assert list(stable_test_root.rglob(".bivharness-mode-probe")) == []
            assert list(stable_test_root.rglob(".bivharness-link-probe")) == []
    finally:
        for target in cleanup_targets:
            shutil.rmtree(target, ignore_errors=True)


@pytest.mark.parametrize("field", ROOT_RELATIVE_FIELDS)
@pytest.mark.parametrize(
    "case",
    (
        "A-abs-safe",
        "B-absolute-name",
        "C-abs-unstable",
        "D-cycle",
        "E-rel-safe",
        "F-dotdot",
        "G-contained-symlink",
        "H-escaping-symlink",
    ),
)
def test_child_path_policy_subsumes_runtime_containment(
    monkeypatch, tmp_path, stable_test_root, field, case
):
    scratch = stable_test_root / "subsumption" / "scratch"
    root = _root_relative_root(scratch, field)
    root.mkdir(parents=True, exist_ok=True)
    if case == "E-rel-safe":
        value = "safe-child"
    else:
        value, _, cycle_links = _root_relative_case(
            stable_test_root, root, field, case, tmp_path
        )
        if cycle_links:
            _inject_identity_resolve_for(monkeypatch, root / value)

    child = root / value
    containment_refuses = not child.resolve().is_relative_to(root.resolve())
    failure = e3._child_failure(field, root, value)

    if containment_refuses:
        assert failure is not None, (field, case, child)
    if case == "E-rel-safe":
        assert failure is None


@pytest.mark.parametrize("field", ("scratch", "live_profile", "live_store_roots"))
def test_resolved_temp_roots_are_refused_without_side_effects(
    monkeypatch, tmp_path, stable_test_root, field
):
    temp_parent = (
        Path("/tmp").resolve()
        / f"bivharness-task7-root-{field}-{os.getpid()}-{tmp_path.name}"
    )
    shutil.rmtree(temp_parent, ignore_errors=True)
    spec = _valid_two_agent_spec()
    scratch = stable_test_root / "scratch"
    if field == "scratch":
        scratch = temp_parent / "scratch"
        target = scratch
    elif field == "live_profile":
        target = temp_parent / "live-profile"
        spec["agents"][0][field] = str(target)
    else:
        target = temp_parent / "live-store"
        spec[field] = [str(target)]

    try:
        result = _run_refusal_without_side_effects(
            monkeypatch,
            tmp_path,
            spec,
            scratch,
            watched_roots=(stable_test_root,),
        )
        assert result.status is Status.INVALID
        assert field in result.detail
        assert not target.exists()
    finally:
        shutil.rmtree(temp_parent, ignore_errors=True)


def test_scratch_rejects_null_without_raising_or_side_effects(
    monkeypatch, tmp_path, stable_test_root
):
    result = _run_refusal_without_side_effects(
        monkeypatch,
        tmp_path,
        _valid_two_agent_spec(),
        None,
        watched_roots=(stable_test_root,),
    )

    assert result.status is Status.INVALID
    assert "scratch" in result.detail


def test_path_field_failures_does_not_recoerce_normalized_scratch(
    monkeypatch, stable_test_root
):
    coerced_labels = []
    real_root_failure = e3._root_failure

    def record_root_coercion(label, value, **kwargs):
        coerced_labels.append(label)
        return real_root_failure(label, value, **kwargs)

    monkeypatch.setattr(e3, "_root_failure", record_root_coercion)

    failures = e3._path_field_failures(
        _valid_two_agent_spec(), stable_test_root / "scratch"
    )

    assert failures == []
    assert "scratch" not in coerced_labels


def _schema_shape_cases():
    """Malformed values for every JSON shape consumed by the E3 runner."""
    scalar = ("none", None), ("scalar", 42), ("container", []), ("bad-element", [None])
    list_of_strings = ("none", None), ("scalar", "value"), ("container", {}), ("bad-element", [None])
    mapping = ("none", None), ("scalar", "value"), ("container", []), ("bad-element", {"KEY": None})
    sentinel_counts = (
        ("none", None),
        ("zero", 0),
        ("negative", -1),
        ("string", "1"),
        ("float", 1.0),
        ("true", True),
        ("false", False),
    )
    cases = []

    def add(label, values, mutate):
        cases.extend((f"{label}-{kind}", value, mutate) for kind, value in values)

    add("id", scalar, lambda spec, value: spec.__setitem__("id", value))
    add("workspace_name", scalar, lambda spec, value: spec.__setitem__("workspace_name", value))
    add("host2_profile_root", scalar, lambda spec, value: spec.__setitem__("host2_profile_root", value))
    add("resume_probe", scalar, lambda spec, value: spec.__setitem__("resume_probe", value))
    add("seed_turns", list_of_strings, lambda spec, value: spec.__setitem__("seed_turns", value))
    add("live_store_roots", list_of_strings, lambda spec, value: spec.__setitem__("live_store_roots", value))
    add("forbidden_bivpak_state", list_of_strings, lambda spec, value: spec.__setitem__("forbidden_bivpak_state", value))
    add(
        "credential_scan_sentinel_count",
        sentinel_counts,
        lambda spec, value: spec.__setitem__("credential_scan_sentinel_count", value),
    )
    add("agents", list_of_strings, lambda spec, value: spec.__setitem__("agents", value))

    def mutate_agent(field):
        return lambda spec, value: spec["agents"][0].__setitem__(field, value)

    for field in (
        "id", "live_profile", "host2_profile", "ownership_glob", "run_token_prefix",
        "cheapest_model", "resume_shape",
    ):
        add(f"agent-{field}", scalar, mutate_agent(field))
    add("agent-resume_mutation", scalar, lambda spec, value: spec["agents"][1].__setitem__("resume_mutation", value))
    for field in (
        "auth_status", "version_command", "seed_start_command", "seed_retry_resume_command",
        "seed_continue_command", "resume_command", "validated_version_prefixes",
    ):
        add(f"agent-{field}", list_of_strings, mutate_agent(field))
    add("agent-liveness_command", list_of_strings, lambda spec, value: spec["agents"][1].__setitem__("liveness_command", value))
    add("agent-env", mapping, mutate_agent("env"))
    return cases


@pytest.mark.parametrize(("label", "value", "mutate"), _schema_shape_cases())
def test_e3_consumed_schema_is_total_over_arbitrary_json(monkeypatch, tmp_path, label, value, mutate):
    spec = _valid_two_agent_spec()
    mutate(spec, value)
    scratch = tmp_path.resolve() / "scratch"

    assert isinstance(e3._path_field_failures(spec, scratch), list)
    result = _run_refusal_without_side_effects(monkeypatch, tmp_path, spec, scratch)

    assert result.status is Status.INVALID, label
    assert result.detail, label


@pytest.mark.parametrize("label, mutate", [
    ("scratch", lambda spec, stable_root: None),
    ("host2_profile_root", lambda spec, stable_root: spec.__setitem__("host2_profile_root", "path\0segment")),
    ("live_store_roots", lambda spec, stable_root: spec.__setitem__("live_store_roots", [str(stable_root / "path\0segment")])),
    ("live_profile", lambda spec, stable_root: spec["agents"][0].__setitem__("live_profile", str(stable_root / "path\0segment"))),
    ("host2_profile", lambda spec, stable_root: spec["agents"][0].__setitem__("host2_profile", "path\0segment")),
    ("workspace_name", lambda spec, stable_root: spec.__setitem__("workspace_name", "path\0segment")),
    ("forbidden_bivpak_state", lambda spec, stable_root: spec.__setitem__("forbidden_bivpak_state", ["path\0segment"])),
])
def test_e3_path_fields_reject_nul_without_raising(monkeypatch, tmp_path, label, mutate):
    spec = _valid_two_agent_spec()
    stable_root = tmp_path.resolve()
    mutate(spec, stable_root)
    scratch = Path("scratch\0path") if label == "scratch" else stable_root / "scratch"

    assert isinstance(e3._path_field_failures(spec, scratch), list)
    result = _run_refusal_without_side_effects(monkeypatch, tmp_path, spec, scratch)

    assert result.status is Status.INVALID, label


@pytest.mark.parametrize("label, mutate", [
    ("live_store_roots", lambda spec: spec.__setitem__("live_store_roots", ["~nosuchuser/e3"])),
    ("live_profile", lambda spec: spec["agents"][0].__setitem__("live_profile", "~nosuchuser/e3")),
    ("host2_profile", lambda spec: spec["agents"][0].__setitem__("host2_profile", "~nosuchuser/e3")),
    ("workspace_name", lambda spec: spec.__setitem__("workspace_name", "~nosuchuser/e3")),
    ("forbidden_bivpak_state", lambda spec: spec.__setitem__("forbidden_bivpak_state", ["~nosuchuser/e3"])),
])
def test_e3_path_fields_reject_ambiguous_tilde_spellings(monkeypatch, tmp_path, label, mutate):
    spec = _valid_two_agent_spec()
    mutate(spec)

    result = _run_refusal_without_side_effects(
        monkeypatch, tmp_path, spec, tmp_path.resolve() / "scratch"
    )

    assert result.status is Status.INVALID, label
    assert label in result.detail


@pytest.mark.parametrize("spec", [[], "s", 42, None])
def test_e3_consumed_schema_rejects_non_object_top_levels(monkeypatch, tmp_path, spec):
    scratch = tmp_path.resolve() / "scratch"

    assert isinstance(e3._path_field_failures(spec, scratch), list)
    result = _run_refusal_without_side_effects(monkeypatch, tmp_path, spec, scratch)

    assert result.status is Status.INVALID
    assert result.id == "e3-invalid-spec"
    assert result.detail


def test_cli_persists_invalid_e3_report_for_malformed_json(tmp_path):
    scenario = tmp_path / "malformed-e3.json"
    report_path = tmp_path / "report.json"
    scenario.write_text("[]", encoding="utf-8")

    exit_code = cli.main([
        "--biv", str(tmp_path / "biv"),
        "--e3", str(scenario),
        "--dry-run",
        "--report", str(report_path),
    ])

    assert exit_code != 0
    assert report_path.is_file()
    report = json.loads(report_path.read_text(encoding="utf-8"))
    assert report["invalid"] == ["e3-invalid-spec"]
    assert len(report["rows"]) == 1
    row = report["rows"][0]
    assert row["id"] == "e3-invalid-spec"
    assert row["tier"] == "E3"
    assert row["status"] == "invalid"
    assert row["classes"] == []
    assert row["detail"]


def _deeply_nested_json_container(depth=300):
    value = {}
    for _ in range(depth):
        value = {"nested": value}
    return value


MALFORMED_REPORT_IDS = (
    ("null", None),
    ("empty", ""),
    ("list", []),
    ("object", {"untrusted": "payload"}),
    ("deep-container", _deeply_nested_json_container()),
)


@pytest.mark.parametrize(
    ("case", "bad_id"),
    MALFORMED_REPORT_IDS,
    ids=[case for case, _ in MALFORMED_REPORT_IDS],
)
def test_cli_bounds_rejected_scenario_ids_in_persisted_report(
    monkeypatch, tmp_path, case, bad_id
):
    scenario = tmp_path / f"invalid-id-{case}.json"
    report_path = tmp_path / "report.json"
    runner_target = tmp_path / "biv"
    spec = _valid_two_agent_spec()
    spec["id"] = bad_id
    scenario.write_text(json.dumps(spec), encoding="utf-8")
    spawn_calls = []

    def refused_spawn(*args):
        spawn_calls.append(args)
        raise AssertionError("rejected scenario id must not spawn")

    monkeypatch.setattr(e3, "_spawn", refused_spawn)
    exit_code = cli.main([
        "--biv", str(runner_target),
        "--e3", str(scenario),
        "--dry-run",
        "--report", str(report_path),
    ])

    assert exit_code != 0
    assert report_path.is_file()
    report_text = report_path.read_text(encoding="utf-8")
    assert len(report_text.encode()) < 2048
    report = json.loads(report_text)
    assert report["invalid"] == ["e3-invalid-spec"]
    assert all(isinstance(result_id, str) for result_id in report["invalid"])
    assert len(report["rows"]) == 1
    assert report["rows"][0]["id"] == "e3-invalid-spec"
    assert isinstance(report["rows"][0]["id"], str)
    assert spawn_calls == []
    assert not runner_target.exists()
    assert list(tmp_path.glob(".bivharness-scratch-*")) == []


@pytest.mark.parametrize(
    ("case", "bad_id"),
    MALFORMED_REPORT_IDS,
    ids=[case for case, _ in MALFORMED_REPORT_IDS],
)
def test_cli_bounds_rejected_agent_ids_in_diagnostics(
    monkeypatch, tmp_path, case, bad_id
):
    scenario = tmp_path / f"invalid-agent-id-{case}.json"
    report_path = tmp_path / "report.json"
    runner_target = tmp_path / "biv"
    spec = _valid_two_agent_spec()
    spec["agents"][0]["id"] = bad_id
    spec["agents"][0]["validated_version_prefixes"] = []
    scenario.write_text(json.dumps(spec), encoding="utf-8")
    spawn_calls = []

    def refused_spawn(*args):
        spawn_calls.append(args)
        raise AssertionError("rejected agent id must not spawn")

    monkeypatch.setattr(e3, "_spawn", refused_spawn)
    exit_code = cli.main([
        "--biv", str(runner_target),
        "--e3", str(scenario),
        "--dry-run",
        "--report", str(report_path),
    ])

    assert exit_code != 0
    assert report_path.is_file()
    report_text = report_path.read_text(encoding="utf-8")
    assert len(report_text.encode()) < 2048
    report = json.loads(report_text)
    assert report["invalid"] == ["cx-range"]
    assert report["rows"][0]["id"] == "cx-range"
    detail = report["rows"][0]["detail"]
    assert "agent validated_version_prefixes" in detail
    unsafe_line = (
        f"{bad_id} validated_version_prefixes must be a non-empty list of "
        "non-empty strings"
    )
    assert unsafe_line not in detail.splitlines()
    assert spawn_calls == []
    assert not runner_target.exists()
    assert list(tmp_path.glob(".bivharness-scratch-*")) == []


def test_e3_non_utf8_scenario_is_invalid_instead_of_raising(tmp_path):
    scenario = tmp_path / "non-utf8-e3.json"
    scenario.write_bytes(b"\xff\xfe")

    result = e3.run_e3(
        scenario,
        tmp_path / "biv",
        tmp_path.resolve() / "scratch",
        dry_run=True,
    )

    assert result.status is Status.INVALID
    assert result.id == "e3-invalid-spec"
    assert "scenario unreadable" in result.detail


def test_cli_persists_invalid_e3_report_for_non_utf8_scenario(tmp_path):
    scenario = tmp_path / "non-utf8-e3.json"
    report_path = tmp_path / "report.json"
    scenario.write_bytes(b"\xff\xfe")

    exit_code = cli.main([
        "--biv", str(tmp_path / "biv"),
        "--e3", str(scenario),
        "--dry-run",
        "--report", str(report_path),
    ])

    assert exit_code != 0
    assert report_path.is_file()
    report = json.loads(report_path.read_text(encoding="utf-8"))
    assert report["invalid"] == ["e3-invalid-spec"]
    assert report["rows"][0]["status"] == "invalid"
    assert "scenario unreadable" in report["rows"][0]["detail"]


def test_scratch_under_a_symlinked_ancestor_is_refused_without_writing(tmp_path):
    shadowed = _symlinked_ancestor(tmp_path)
    real = tmp_path / "real"

    result = _run_dry(tmp_path, _valid_two_agent_spec(), shadowed)

    assert result.status is Status.INVALID
    assert "realpath-stable" in result.detail
    assert "scratch" in result.detail
    assert not shadowed.exists()
    assert list(real.iterdir()) == []


@pytest.mark.parametrize("spelling", ["relative-scratch", ".", "", "~nosuchuser/e3"])
def test_scratch_relative_spellings_are_refused_by_realpath_stability(
    monkeypatch, tmp_path, spelling
):
    stable = tmp_path.resolve()
    monkeypatch.chdir(stable)

    scratch = Path(spelling)
    assert isinstance(e3._path_field_failures(_valid_two_agent_spec(), scratch), list)
    result = _run_refusal_without_side_effects(
        monkeypatch, tmp_path, _valid_two_agent_spec(), scratch
    )

    assert result.status is Status.INVALID
    assert "scratch must be realpath-stable" in result.detail


def test_absolute_realpath_unstable_host2_profile_root_is_refused(tmp_path):
    spec = _valid_two_agent_spec()
    spec["host2_profile_root"] = str(_symlinked_ancestor(tmp_path) / "profiles")
    result = _run_dry(tmp_path, spec, tmp_path.resolve() / "scratch")
    assert result.status is Status.INVALID
    assert "host2_profile_root" in result.detail


def test_realpath_unstable_live_store_root_is_refused(tmp_path):
    spec = _valid_two_agent_spec()
    spec["live_store_roots"] = [str(_symlinked_ancestor(tmp_path) / "store")]
    result = _run_dry(tmp_path, spec, tmp_path.resolve() / "scratch")
    assert result.status is Status.INVALID
    assert "live_store_roots" in result.detail


def test_realpath_unstable_live_profile_is_refused(tmp_path):
    spec = _valid_two_agent_spec()
    spec["agents"][0]["live_profile"] = str(_symlinked_ancestor(tmp_path) / ".codex")
    result = _run_dry(tmp_path, spec, tmp_path.resolve() / "scratch")
    assert result.status is Status.INVALID
    assert "live_profile" in result.detail


@pytest.mark.parametrize(
    "field",
    ("scratch", "live_profile", "live_store_roots"),
)
@pytest.mark.parametrize("spelling", ("svd", "nfd"))
def test_noncanonical_external_roots_are_refused_before_probe_or_spawn(
    monkeypatch, tmp_path, stable_test_root, field, spelling
):
    if spelling == "svd":
        suffix = {
            "scratch": "e3-run/bivharness-scratch-x",
            "live_profile": ".codex",
            "live_store_roots": ".claude",
        }[field]
        canonical = Path("/Users/jack") / suffix
        refused = Path("/System/Volumes/Data") / str(canonical).lstrip("/")
    else:
        canonical = stable_test_root / f"{field}-\u00e9"
        refused = Path(unicodedata.normalize("NFD", str(canonical)))
    spec = _valid_two_agent_spec()
    scratch = stable_test_root / "scratch"
    if field == "scratch":
        scratch = refused
    elif field == "live_profile":
        spec["agents"][0]["live_profile"] = str(refused)
    else:
        spec["live_store_roots"] = [str(refused)]
    probe_calls = []
    monkeypatch.setattr(
        e3,
        "probe",
        lambda root: probe_calls.append(root) or [],
    )

    result = _run_refusal_without_side_effects(
        monkeypatch,
        tmp_path,
        spec,
        scratch,
        watched_roots=(stable_test_root,),
    )

    assert result.status is Status.INVALID
    assert probe_calls == []
    assert (
        f"{field} must use its canonical spelling ({canonical}); "
        f"firmlink-aliased or non-NFC spellings are refused ({refused})"
    ) in result.detail


# Case-variant APFS identity containment is deliberately outside this fold and
# remains an orchestrator-owned residual for the next negctl or E4 hardening pass.
@pytest.mark.parametrize(
    "field",
    ("scratch", "live_profile", "live_store_roots"),
)
@pytest.mark.parametrize(
    "canonical",
    (
        Path("/Users/jack/e3-run/bivharness-scratch-x"),
        Path("/private/var/e3-run/bivharness-scratch-x"),
    ),
    ids=("users", "private-var"),
)
def test_path_field_failures_accept_canonical_external_root_spellings(
    stable_test_root, field, canonical
):
    spec = _valid_two_agent_spec()
    scratch = stable_test_root / "scratch"
    if field == "scratch":
        scratch = canonical
    elif field == "live_profile":
        spec["agents"][0]["live_profile"] = str(canonical)
    else:
        spec["live_store_roots"] = [str(canonical)]

    assert e3._path_field_failures(spec, scratch) == []


@pytest.mark.parametrize(
    "field",
    ("scratch", "live_profile", "live_store_roots"),
)
def test_path_field_failures_accept_nfc_non_ascii_external_root_spellings(
    stable_test_root, field
):
    canonical = stable_test_root / "canonical-\u00e9"
    assert unicodedata.normalize("NFC", str(canonical)) == str(canonical)
    spec = _valid_two_agent_spec()
    scratch = stable_test_root / "scratch"
    if field == "scratch":
        scratch = canonical
    elif field == "live_profile":
        spec["agents"][0]["live_profile"] = str(canonical)
    else:
        spec["live_store_roots"] = [str(canonical)]

    assert e3._path_field_failures(spec, scratch) == []


@pytest.mark.parametrize("field", ["host2_profile", "workspace_name"])
def test_absolute_value_that_would_escape_its_root_is_refused(tmp_path, field):
    spec = _valid_two_agent_spec()
    if field == "workspace_name":
        spec["workspace_name"] = "/etc"
    else:
        spec["agents"][0]["host2_profile"] = "/etc"
    result = _run_dry(tmp_path, spec, tmp_path.resolve() / "scratch")
    assert result.status is Status.INVALID
    assert field in result.detail


def test_absolute_forbidden_bivpak_state_entry_is_refused(tmp_path):
    spec = _valid_two_agent_spec()
    spec["forbidden_bivpak_state"] = ["/etc"]
    result = _run_dry(tmp_path, spec, tmp_path.resolve() / "scratch")
    assert result.status is Status.INVALID
    assert "forbidden_bivpak_state" in result.detail


def test_realpath_stable_paths_are_accepted(tmp_path, stable_test_root):
    result = _run_dry(
        tmp_path, _valid_two_agent_spec(), stable_test_root / "scratch"
    )
    assert result.status is Status.PASS


def test_temp_rooted_host2_profile_is_refused_before_any_spawn(
    monkeypatch, tmp_path, stable_test_root
):
    calls = []

    def fake_spawn(command, cwd, env):
        calls.append(command)
        return SimpleNamespace(returncode=0, stdout="", stderr="")

    monkeypatch.setattr(e3, "_spawn", fake_spawn)
    spec = _valid_two_agent_spec()
    spec["host2_profile_root"] = "/tmp/bivharness-selftest-host2"

    result = _run_dry(tmp_path, spec, stable_test_root / "scratch")

    assert result.status is Status.INVALID
    assert calls == []


def test_shipped_scenario_has_no_realpath_unstable_or_absolute_paths(repo_root):
    spec = json.loads(
        (repo_root / "harness/scenarios-e3/e3-dual-resume.json").read_text(encoding="utf-8")
    )
    assert e3._path_field_failures(spec, Path.home()) == []


def test_runner_proceeds_past_tempdir_noise_to_pack(
    monkeypatch, tmp_path, stable_test_root
):
    calls = []

    def fake_spawn(command, cwd, env):
        calls.append(command)
        if "--version" in command:
            version = "claude 2.1.202" if _agent_basename(command) == "claude" else "codex-cli 0.144.1"
            return SimpleNamespace(returncode=0, stdout=version, stderr="")
        if command[:2] == ["biv", "pack"]:
            return SimpleNamespace(returncode=1, stdout="", stderr="stop after negative control")
        return SimpleNamespace(returncode=0, stdout="", stderr="")

    def fake_seed_agent(
        agent,
        live_profile,
        seed_workspace,
        spec,
        env,
        spawn,
        capture_candidates,
        owned_paths,
        resolved_binary=None,
    ):
        payload = (
            b'{"output":"FileNotFoundError: No usable temporary directory found in '
            b"['/var/folders/hq/x/T/', '/tmp', '/var/tmp', '/usr/tmp']\\n"
            b'also /var/folders/hq/x/T/ws and /private/var/folders/hq/x/T/ws"}\n'
            if agent["id"] == "codex"
            else b'{"cwd":"/Users/jack/biv-e3/ws"}\n'
        )
        transcript = seed_workspace.parent / f"{agent['id']}-seed.jsonl"
        transcript.write_bytes(payload)
        owned_paths.append(transcript)
        return transcript

    monkeypatch.setattr(e3, "_spawn", fake_spawn)
    monkeypatch.setattr(e3, "_seed_agent", fake_seed_agent)
    spec_path = tmp_path / "e3.json"
    spec_path.write_text(json.dumps(_valid_two_agent_spec()), encoding="utf-8")

    result = e3.run_e3(spec_path, Path("biv"), stable_test_root / "scratch")

    assert "negative-control" not in (result.detail or "")
    assert any(command[:2] == ["biv", "pack"] for command in calls)


def test_runner_voids_pre_pack_when_a_run_root_alias_spelling_appears(
    monkeypatch, tmp_path, stable_test_root
):
    calls = []

    def fake_spawn(command, cwd, env):
        calls.append(command)
        if "--version" in command:
            version = "claude 2.1.202" if _agent_basename(command) == "claude" else "codex-cli 0.144.1"
            return SimpleNamespace(returncode=0, stdout=version, stderr="")
        return SimpleNamespace(returncode=0, stdout="", stderr="")

    def fake_seed_agent(
        agent,
        live_profile,
        seed_workspace,
        spec,
        env,
        spawn,
        capture_candidates,
        owned_paths,
        resolved_binary=None,
    ):
        transcript = seed_workspace.parent / f"{agent['id']}-seed.jsonl"
        transcript.write_bytes(b'{"cwd":"E3-ALIAS-CANARY/seed-ws"}\n')
        owned_paths.append(transcript)
        return transcript

    monkeypatch.setattr(e3, "_spawn", fake_spawn)
    monkeypatch.setattr(e3, "_seed_agent", fake_seed_agent)
    monkeypatch.setattr(e3, "_alias_spellings", lambda root: ["E3-ALIAS-CANARY"])
    spec_path = tmp_path / "e3.json"
    spec_path.write_text(json.dumps(_valid_two_agent_spec()), encoding="utf-8")

    result = e3.run_e3(spec_path, Path("biv"), stable_test_root / "scratch")

    _assert_report_refused(result)
    assert not any(command[:2] == ["biv", "pack"] for command in calls)


@pytest.mark.parametrize(
    "agent_order",
    (
        ("codex", "claude-code"),
        ("claude-code", "codex"),
    ),
    ids=("codex-first", "claude-first"),
)
@pytest.mark.parametrize(
    "hit_index",
    (0, 1),
    ids=("first-transcript", "second-transcript"),
)
def test_runner_checks_each_agent_transcript_for_double_slash_alias_before_pack(
    monkeypatch, tmp_path, stable_test_root, agent_order, hit_index
):
    calls = []
    hit_agent = agent_order[hit_index]
    alias_root = "/tmp/E3-ALIAS-CANARY"

    def fake_spawn(command, cwd, env):
        calls.append(command)
        if "--version" in command:
            version = (
                "claude 2.1.202"
                if _agent_basename(command) == "claude"
                else "codex-cli 0.144.1"
            )
            return SimpleNamespace(returncode=0, stdout=version, stderr="")
        if command[:2] == ["biv", "pack"]:
            return SimpleNamespace(
                returncode=1,
                stdout="",
                stderr="negative control was bypassed",
            )
        return SimpleNamespace(returncode=0, stdout="", stderr="")

    def fake_seed_agent(
        agent,
        live_profile,
        seed_workspace,
        spec,
        env,
        spawn,
        capture_candidates,
        owned_paths,
        resolved_binary=None,
    ):
        transcript = seed_workspace.parent / f"{agent['id']}-seed.jsonl"
        cwd = (
            "//tmp/E3-ALIAS-CANARY/seed-ws"
            if agent["id"] == hit_agent
            else "/opt/benign-workspace"
        )
        transcript.write_text(
            json.dumps({"cwd": cwd}) + "\n",
            encoding="utf-8",
        )
        owned_paths.append(transcript)
        return transcript

    spec = _valid_two_agent_spec()
    agents_by_id = {agent["id"]: agent for agent in spec["agents"]}
    spec["agents"] = [agents_by_id[agent_id] for agent_id in agent_order]
    monkeypatch.setattr(e3, "_spawn", fake_spawn)
    monkeypatch.setattr(e3, "_seed_agent", fake_seed_agent)
    monkeypatch.setattr(
        e3,
        "_alias_spellings",
        lambda root: [alias_root],
    )
    spec_path = tmp_path / "e3.json"
    spec_path.write_text(json.dumps(spec), encoding="utf-8")

    result = e3.run_e3(
        spec_path,
        Path("biv"),
        stable_test_root / "scratch",
    )

    _assert_report_refused(result)
    assert not any(command[:2] == ["biv", "pack"] for command in calls)


def test_negative_control_flags_the_alias_spelling_of_the_run_root(tmp_path):
    scratch = Path("/private/var/e3-run/bivharness-scratch-x")
    transcript = tmp_path / "seed.jsonl"
    transcript.write_bytes(b'{"cwd":"/var/e3-run/bivharness-scratch-x/seed-ws"}\n')
    failures = e3._negative_control_failures([transcript], scratch)
    assert failures and "negative-control" in failures[0]


def test_negative_control_flags_the_reverse_direction_too(tmp_path):
    scratch = Path("/var/e3-run/bivharness-scratch-x")
    transcript = tmp_path / "seed.jsonl"
    transcript.write_bytes(
        b'{"cwd":"/private/var/e3-run/bivharness-scratch-x/seed-ws"}\n'
    )
    assert e3._negative_control_failures([transcript], scratch)


def test_negative_control_is_silent_on_runtime_tempdir_noise(tmp_path):
    scratch = Path("/private/var/e3-run/bivharness-scratch-x")
    transcript = tmp_path / "rollout.jsonl"
    transcript.write_bytes(
        b'{"output":"FileNotFoundError: No usable temporary directory found in '
        b"['/var/folders/hq/x/T/', '/tmp', '/var/tmp', '/usr/tmp']\\n"
        b'also /var/folders/hq/x/T/ws and /private/var/folders/hq/x/T/ws"}\n'
    )
    assert e3._negative_control_failures([transcript], scratch) == []


def test_negative_control_is_silent_on_the_canonical_spelling(tmp_path):
    scratch = Path("/private/var/e3-run/bivharness-scratch-x")
    transcript = tmp_path / "seed.jsonl"
    transcript.write_bytes(
        b'{"cwd":"/private/var/e3-run/bivharness-scratch-x/seed-ws"}\n'
    )
    assert e3._negative_control_failures([transcript], scratch) == []


def test_negative_control_is_silent_on_a_realpath_stable_transcript(tmp_path):
    transcript = tmp_path / "seed.jsonl"
    transcript.write_bytes(b'{"cwd":"/Users/jack/biv-e3/seed-ws"}\n')
    assert e3._negative_control_failures(
        [transcript], Path("/Users/jack/biv-e3-scratch")
    ) == []


@pytest.mark.parametrize(
    "scratch,sibling",
    [
        (
            Path("/private/var/e3-run/bivharness-scratch-x"),
            b'{"path":"/var/e3-run/bivharness-scratch-x-old/output"}\n',
        ),
        (
            Path("/var/e3-run/bivharness-scratch-x"),
            b'{"path":"/private/var/e3-run/bivharness-scratch-x-old/output"}\n',
        ),
    ],
)
def test_negative_control_is_silent_on_a_sibling_prefix_path(
    tmp_path, scratch, sibling
):
    transcript = tmp_path / "seed.jsonl"
    transcript.write_bytes(sibling)
    assert e3._negative_control_failures([transcript], scratch) == []


@pytest.mark.parametrize(
    "scratch,blob",
    [
        (
            Path("/private/var/e3-run/bivharness-scratch-x"),
            b'{"p":"/opt/private/var/e3-run/bivharness-scratch-x/y"}\n',
        ),
        (
            Path("/private/var/e3-run/bivharness-scratch-x"),
            b'{"p":"/foo1/var/e3-run/bivharness-scratch-x/y"}\n',
        ),
        (
            Path("/private/var/e3-run/bivharness-scratch-x"),
            b'{"p":"/scope@/var/e3-run/bivharness-scratch-x/y"}\n',
        ),
        (
            Path("/private/var/e3-run/bivharness-scratch-x"),
            b'{"p":"/scope%/var/e3-run/bivharness-scratch-x/y"}\n',
        ),
        (
            Path("/private/var/e3-run/bivharness-scratch-x"),
            b'{"p":"/opt//var/e3-run/bivharness-scratch-x/y"}\n',
        ),
        (
            Path("/private/var/e3-run/bivharness-scratch-x"),
            b'{"p":"/scope=/var/e3-run/bivharness-scratch-x/y"}\n',
        ),
        (
            Path("/private/var/e3-run/bivharness-scratch-x"),
            b'{"p":"/scope:/var/e3-run/bivharness-scratch-x/y"}\n',
        ),
        (
            Path("/private/var/e3-run/bivharness-scratch-x"),
            b'{"p":"/scope,/var/e3-run/bivharness-scratch-x/y"}\n',
        ),
        (
            Path("/private/var/e3-run/bivharness-scratch-x"),
            b'{"p":"/scope /var/e3-run/bivharness-scratch-x/y"}\n',
        ),
        (
            Path("/var/e3-run/bivharness-scratch-x"),
            b'{"p":"/x@/private/var/e3-run/bivharness-scratch-x/y"}\n',
        ),
        (
            Path("/var/e3-run/bivharness-scratch-x"),
            b'{"p":"/scope=/private/var/e3-run/bivharness-scratch-x/y"}\n',
        ),
    ],
)
def test_negative_control_is_silent_on_an_embedded_longer_path(
    tmp_path, scratch, blob
):
    transcript = tmp_path / "seed.jsonl"
    transcript.write_bytes(blob)
    assert e3._negative_control_failures([transcript], scratch) == []


def test_negative_control_flags_the_exact_alias_root_as_a_complete_value(tmp_path):
    scratch = Path("/private/var/e3-run/bivharness-scratch-x")
    transcript = tmp_path / "seed.jsonl"
    transcript.write_bytes(b'{"root":"/var/e3-run/bivharness-scratch-x"}\n')
    assert e3._negative_control_failures([transcript], scratch)


def test_negative_control_flags_a_nested_container_value(tmp_path):
    scratch = Path("/private/var/e3-run/bivharness-scratch-x")
    transcript = tmp_path / "seed.jsonl"
    transcript.write_bytes(
        b'{"a":[{"p":"/var/e3-run/bivharness-scratch-x/y"}]}\n'
    )
    assert e3._negative_control_failures([transcript], scratch)


@pytest.mark.parametrize("separator", ("\u2028", "\u2029", "\u0085"))
def test_negative_control_preserves_raw_unicode_separators_inside_json_records(
    tmp_path, separator
):
    scratch = Path("/private/var/e3-run/bivharness-scratch-x")
    transcript = tmp_path / "seed.jsonl"
    transcript.write_text(
        '{"msg":"mask'
        + separator
        + 'text","cwd":"/var/e3-run/bivharness-scratch-x/seed"}\n',
        encoding="utf-8",
    )

    assert e3._negative_control_failures([transcript], scratch)


def test_negative_control_skips_json_parser_recursion_errors(
    monkeypatch, tmp_path
):
    scratch = Path("/private/var/e3-run/bivharness-scratch-x")
    transcript = tmp_path / "seed.jsonl"
    transcript.write_text(
        'too-deep\n{"cwd":"/var/e3-run/bivharness-scratch-x/seed"}\n',
        encoding="utf-8",
    )
    real_loads = e3.json.loads

    def loads_with_deep_record(line):
        if line == "too-deep":
            raise RecursionError("injected parser depth")
        return real_loads(line)

    monkeypatch.setattr(e3.json, "loads", loads_with_deep_record)

    assert e3._negative_control_failures([transcript], scratch)


def test_structural_alias_walk_handles_nesting_beyond_python_recursion_limit():
    root = "/var/e3-run/bivharness-scratch-x"
    record = root + "/seed"
    for _ in range(1200):
        record = [record]

    assert e3._structural_alias_hit(record, [root]) == root


def test_structural_alias_walk_preserves_document_order():
    first = "/alias/first"
    second = "/alias/second"
    record = {
        "first": {"cwd": first + "/seed"},
        "second": [second + "/seed"],
    }

    assert e3._structural_alias_hit(record, [first, second]) == first


@pytest.mark.parametrize(
    ("scratch", "alias"),
    (
        (
            Path("/private/var/e3-run/bivharness-scratch-x"),
            "/var/e3-run/bivharness-scratch-x",
        ),
        (
            Path("/var/e3-run/bivharness-scratch-x"),
            "/private/var/e3-run/bivharness-scratch-x",
        ),
        (
            Path("/private/tmp/e3-run/bivharness-scratch-x"),
            "/tmp/e3-run/bivharness-scratch-x",
        ),
        (
            Path("/tmp/e3-run/bivharness-scratch-x"),
            "/private/tmp/e3-run/bivharness-scratch-x",
        ),
        (
            Path("/private/etc/e3-run/bivharness-scratch-x"),
            "/etc/e3-run/bivharness-scratch-x",
        ),
        (
            Path("/etc/e3-run/bivharness-scratch-x"),
            "/private/etc/e3-run/bivharness-scratch-x",
        ),
        (
            Path("/Users/jack/e3-run/bivharness-scratch-x"),
            "/System/Volumes/Data/Users/jack/e3-run/bivharness-scratch-x",
        ),
    ),
)
def test_structural_alias_hit_uses_lexical_path_identity(scratch, alias):
    roots = e3._alias_spellings(scratch)
    assert alias in roots
    assert all(root.startswith("/") and not root.startswith("//") for root in roots)

    for root in roots:
        assert e3._structural_alias_hit(
            {"cwd": root + "/../outside-the-run"},
            roots,
        ) is None
        assert e3._structural_alias_hit(
            {"cwd": root + "/a/../seed-ws"},
            roots,
        ) == root
        assert e3._structural_alias_hit(
            {"cwd": root + "/./seed-ws"},
            roots,
        ) == root
        assert e3._structural_alias_hit({"cwd": root + "/"}, roots) == root
        assert e3._structural_alias_hit({"cwd": "/" + root}, roots) == root
        assert (
            e3._structural_alias_hit({"cwd": "/" + root + "/seed-ws"}, roots)
            == root
        )
        assert e3._structural_alias_hit({"cwd": "//" + root}, roots) == root
        assert e3._structural_alias_hit(
            {"cwd": "/" + root + "/../outside-the-run"},
            roots,
        ) is None
        assert e3._structural_alias_hit(
            {"cwd": "/" + root + "-outside"},
            roots,
        ) is None

    assert e3._structural_alias_hit(
        {"cwd": "//opt/unrelated/e3-run"},
        roots,
    ) is None


def test_negative_control_flags_the_darwin_data_firmlink_for_users_scratch(
    tmp_path
):
    scratch = Path("/Users/jack/e3-run/bivharness-scratch-x")
    transcript = tmp_path / "seed.jsonl"
    transcript.write_text(
        '{"cwd":"/System/Volumes/Data/Users/jack/e3-run/'
        'bivharness-scratch-x/seed"}\n',
        encoding="utf-8",
    )

    assert e3._negative_control_failures([transcript], scratch)


def test_negative_control_is_silent_on_canonical_users_scratch_spelling(tmp_path):
    scratch = Path("/Users/jack/e3-run/bivharness-scratch-x")
    transcript = tmp_path / "seed.jsonl"
    transcript.write_text(
        '{"cwd":"/Users/jack/e3-run/bivharness-scratch-x/seed"}\n',
        encoding="utf-8",
    )

    assert e3._negative_control_failures([transcript], scratch) == []


def test_alias_spellings_return_text_without_a_byte_round_trip():
    spellings = e3._alias_spellings(
        Path("/private/var/e3-run/bivharness-scratch-x")
    )

    assert "/var/e3-run/bivharness-scratch-x" in spellings
    assert all(isinstance(spelling, str) for spelling in spellings)
    for root, alias in (
        ("/private/var", "/var"),
        ("/var", "/private/var"),
        ("/private/tmp", "/tmp"),
        ("/tmp", "/private/tmp"),
        ("/private/etc", "/etc"),
        ("/etc", "/private/etc"),
        ("/", "/System/Volumes/Data"),
    ):
        assert alias in e3._alias_spellings(Path(root))
    assert e3._alias_spellings(Path("/System/Volumes/Data")) == [
        "/System/Volumes/Data"
    ]


@pytest.mark.parametrize("data_prefix_count", (1, 2))
def test_alias_spellings_canonicalize_darwin_data_prefixes_to_a_fixed_point(
    data_prefix_count,
):
    prefix = "/System/Volumes/Data" * data_prefix_count
    scratch = Path(prefix + "/private/tmp/e3-scratch")

    spellings = e3._alias_spellings(scratch)

    assert "/tmp/e3-scratch" in spellings


def test_alias_spellings_normalize_the_scratch_text_to_nfc():
    scratch = Path(
        unicodedata.normalize("NFD", "/Users/jack/e3-run/bivharness-scratch-\u00e9")
    )
    alias = "/System/Volumes/Data/Users/jack/e3-run/bivharness-scratch-\u00e9"

    assert alias in e3._alias_spellings(scratch)


def test_negative_control_normalizes_transcript_path_values_to_nfc(tmp_path):
    scratch = Path("/Users/jack/e3-run/bivharness-scratch-\u00e9")
    alias = unicodedata.normalize(
        "NFD",
        "/System/Volumes/Data/Users/jack/e3-run/bivharness-scratch-\u00e9/seed",
    )
    transcript = tmp_path / "seed.jsonl"
    transcript.write_text(
        json.dumps({"cwd": alias}, ensure_ascii=False) + "\n",
        encoding="utf-8",
    )

    assert e3._negative_control_failures([transcript], scratch)


def test_negative_control_failure_binds_detail_cardinality_and_non_ascii_root(
    tmp_path
):
    scratch = Path("/Users/jack/e3-run/bivharness-scratch-\u00e9")
    alias = "/System/Volumes/Data/Users/jack/e3-run/bivharness-scratch-\u00e9"
    transcript = tmp_path / "seed.jsonl"
    transcript.write_text(
        f'{{"cwd":"{alias}/first"}}\n{{"cwd":"{alias}/second"}}\n',
        encoding="utf-8",
    )

    failures = e3._negative_control_failures([transcript], scratch)

    assert len(failures) == 1
    assert failures[0].startswith(
        f"negative-control: {transcript} renders {alias} - "
    )


def test_negative_control_replaces_invalid_utf8_in_benign_noise(tmp_path):
    scratch = Path("/private/var/e3-run/bivharness-scratch-x")
    transcript = tmp_path / "seed.jsonl"
    transcript.write_bytes(b'\xff\n{"cwd":"/opt/workspace"}\n')

    assert e3._negative_control_failures([transcript], scratch) == []


def test_negative_control_replaces_invalid_utf8_and_still_finds_alias(tmp_path):
    scratch = Path("/private/var/e3-run/bivharness-scratch-x")
    transcript = tmp_path / "seed.jsonl"
    transcript.write_bytes(
        b'\xff\n{"cwd":"/var/e3-run/bivharness-scratch-x/seed"}\n'
    )

    assert e3._negative_control_failures([transcript], scratch)


def test_negative_control_replacement_does_not_join_an_alias_across_invalid_utf8(
    tmp_path,
):
    scratch = Path("/private/var/e3-run/bivharness-scratch-x")
    transcript = tmp_path / "seed.jsonl"
    transcript.write_bytes(
        b'{"cwd":"/var/e3-run/bivharness-scratch-\xffx/seed"}\n'
    )

    assert e3._negative_control_failures([transcript], scratch) == []


@pytest.mark.parametrize("delimiter", (b"\r\n", b"\r"), ids=("crlf", "lone-cr"))
def test_negative_control_accepts_platform_newlines_as_jsonl_record_delimiters(
    tmp_path, delimiter
):
    scratch = Path("/private/var/e3-run/bivharness-scratch-x")
    transcript = tmp_path / "seed.jsonl"
    transcript.write_bytes(
        b'{"cwd":"/opt/workspace"}'
        + delimiter
        + b'{"cwd":"/var/e3-run/bivharness-scratch-x/seed"}'
        + delimiter
    )

    assert e3._negative_control_failures([transcript], scratch)


def test_negative_control_reads_a_bom_prefixed_first_record(tmp_path):
    scratch = Path("/private/var/e3-run/bivharness-scratch-x")
    transcript = tmp_path / "seed.jsonl"
    transcript.write_text(
        '\ufeff{"cwd":"/var/e3-run/bivharness-scratch-x/seed"}\n',
        encoding="utf-8",
    )

    assert e3._negative_control_failures([transcript], scratch)


@pytest.mark.parametrize(
    ("path", "refused"),
    (
        (Path("/System/Volumes/Data/private/tmp/e3-scratch"), True),
        (Path("/private/tmp/e3-scratch"), False),
    ),
    ids=("darwin-data-firmlink", "distinct-linux-private-tmp"),
)
def test_temp_root_guard_handles_darwin_firmlink_without_linux_false_positive(
    monkeypatch, path, refused
):
    real_resolve = Path.resolve

    def linux_style_tmp_resolve(path, *args, **kwargs):
        if path == Path("/tmp"):
            return Path("/tmp")
        return real_resolve(path, *args, **kwargs)

    monkeypatch.setattr(Path, "resolve", linux_style_tmp_resolve)
    failure = e3._temp_root_failure("scratch", path)

    assert (failure is not None) is refused
    if refused:
        assert "under" in failure


def test_temp_overlap_guard_canonicalizes_the_darwin_data_firmlink(
    monkeypatch, stable_test_root
):
    monkeypatch.setenv("TMPDIR", str(stable_test_root / "unrelated-temp"))

    failures = e3._scratch_temp_root_overlap_failures(
        Path("/System/Volumes/Data/private/var")
    )

    assert failures
    assert "/private/var/tmp" in failures[0]


def test_temp_overlap_guard_normalizes_paths_to_nfc(
    monkeypatch, stable_test_root
):
    scratch = stable_test_root / "scratch-\u00e9"
    temp_root = Path(
        unicodedata.normalize("NFD", str(scratch / "ambient-temp"))
    )
    monkeypatch.setenv("TMPDIR", str(temp_root))

    failures = e3._scratch_temp_root_overlap_failures(scratch)

    assert failures


def test_e3_empty_tmpdir_falls_back_to_tmp(
    monkeypatch, tmp_path, stable_test_root
):
    calls = []
    scratch = stable_test_root / "scratch"
    cwd = scratch / "cwd"
    cwd.mkdir(parents=True)
    monkeypatch.chdir(cwd)
    monkeypatch.setenv("TMPDIR", "")
    for name in (*CREDENTIAL_ENV_NAMES, "CLAUDE_CONFIG_DIR", "CODEX_HOME"):
        monkeypatch.delenv(name, raising=False)
    monkeypatch.setattr(e3, "probe", lambda root: calls.append(root) or [])

    result = _run_dry(tmp_path, _valid_two_agent_spec(), scratch)

    assert result.status is Status.PASS
    assert calls == [scratch]


def test_e3_absolutizes_a_relative_tmpdir_before_overlap_check(
    monkeypatch, tmp_path, stable_test_root
):
    calls = []
    scratch = stable_test_root / "scratch"
    scratch.mkdir()
    monkeypatch.chdir(scratch)
    monkeypatch.setenv("TMPDIR", "ambient-temp")
    for name in (*CREDENTIAL_ENV_NAMES, "CLAUDE_CONFIG_DIR", "CODEX_HOME"):
        monkeypatch.delenv(name, raising=False)
    monkeypatch.setattr(e3, "probe", lambda root: calls.append(root) or [])

    result = _run_dry(tmp_path, _valid_two_agent_spec(), scratch)

    assert result.status is Status.INVALID
    assert calls == []
    assert "temporary root" in result.detail


def test_e3_allows_scratch_strictly_inside_ambient_tmpdir(
    monkeypatch, tmp_path, stable_test_root
):
    calls = []
    ambient_temp_root = stable_test_root / "ambient-temp"
    scratch = ambient_temp_root / "e3-scratch"
    scratch.mkdir(parents=True)
    monkeypatch.setenv("TMPDIR", str(ambient_temp_root))
    for name in (*CREDENTIAL_ENV_NAMES, "CLAUDE_CONFIG_DIR", "CODEX_HOME"):
        monkeypatch.delenv(name, raising=False)
    monkeypatch.setattr(e3, "probe", lambda root: calls.append(root) or [])

    result = _run_dry(tmp_path, _valid_two_agent_spec(), scratch)

    assert result.status is Status.PASS
    assert calls == [scratch]


@pytest.mark.parametrize("temp_root_kind", ("ambient", "private-var-tmp"))
def test_e3_refuses_scratch_equal_to_or_above_temp_roots_before_probe(
    monkeypatch, tmp_path, stable_test_root, temp_root_kind
):
    calls = []
    scratch = stable_test_root / "scratch"
    scratch.mkdir()
    if temp_root_kind == "ambient":
        ambient_temp_root = scratch / "ambient-temp"
        ambient_temp_root.mkdir()
        monkeypatch.setenv("TMPDIR", str(ambient_temp_root))
    else:
        scratch = Path("/private/var/tmp")
        monkeypatch.setenv("TMPDIR", str(stable_test_root / "unrelated-temp"))
    for name in (*CREDENTIAL_ENV_NAMES, "CLAUDE_CONFIG_DIR", "CODEX_HOME"):
        monkeypatch.delenv(name, raising=False)
    monkeypatch.setattr(e3, "probe", lambda root: calls.append(root) or [])
    spec_path = tmp_path / "e3.json"
    spec_path.write_text(json.dumps(_valid_two_agent_spec()), encoding="utf-8")

    result = e3.run_e3(
        spec_path,
        Path("biv"),
        scratch,
        dry_run=True,
    )

    assert calls == []
    assert result.status is Status.INVALID
    assert "temporary root" in result.detail


def test_negative_control_is_silent_on_a_prose_embedded_mention(tmp_path):
    scratch = Path("/private/var/e3-run/bivharness-scratch-x")
    transcript = tmp_path / "seed.jsonl"
    transcript.write_bytes(
        b'{"msg":"I ran in /var/e3-run/bivharness-scratch-x/seed today"}\n'
    )
    assert e3._negative_control_failures([transcript], scratch) == []


def test_negative_control_skips_malformed_lines_without_voiding(tmp_path):
    scratch = Path("/private/var/e3-run/bivharness-scratch-x")
    transcript = tmp_path / "seed.jsonl"
    transcript.write_bytes(b'not json /var/e3-run/bivharness-scratch-x/seed\n')
    assert e3._negative_control_failures([transcript], scratch) == []
    transcript.write_bytes(
        b'not json\n{"cwd":"/var/e3-run/bivharness-scratch-x/s"}\n'
    )
    assert e3._negative_control_failures([transcript], scratch)


def test_all_host1_auth_and_version_gates_run_before_any_seed(monkeypatch, tmp_path):
    calls = []
    binaries = {"first": "/opt/first", "second": "/opt/second"}
    monkeypatch.setattr(e3.shutil, "which", binaries.get)

    def fake_spawn(command, cwd, env):
        calls.append(command)
        if command[1] == "auth" and command[0] == binaries["second"]:
            return SimpleNamespace(returncode=1, stdout="", stderr="not logged in")
        return SimpleNamespace(returncode=0, stdout="tool 1.0.0", stderr="")

    spec = _valid_two_agent_spec()
    spec["id"] = "auth-order"
    for agent, command in zip(spec["agents"], ("first", "second")):
        agent["auth_status"] = [command, "auth"]
        agent["version_command"] = [command, "version"]
        agent["validated_version_prefixes"] = ["1.0."]
    spec_path = tmp_path / "e3.json"
    spec_path.write_text(json.dumps(spec), encoding="utf-8")
    scratch = Path.home() / ".cache" / f"biv-e3-auth-order-{os.getpid()}"
    shutil.rmtree(scratch, ignore_errors=True)
    monkeypatch.setattr(e3, "_spawn", fake_spawn)
    try:
        result = e3.run_e3(spec_path, Path("biv"), scratch)
    finally:
        shutil.rmtree(scratch, ignore_errors=True)

    assert result.status is Status.INVALID
    assert calls == [
        [binaries["first"], "version"],
        [binaries["second"], "version"],
        [binaries["first"], "auth"],
        [binaries["second"], "auth"],
    ]


def _argv_barrier_spec(stable_test_root):
    spec = _valid_two_agent_spec()
    spec["live_store_roots"] = []
    for agent in spec["agents"]:
        live_root = stable_test_root / f"live-{agent['id']}"
        agent["live_profile"] = str(live_root)
        spec["live_store_roots"].append(str(live_root))
    spec["host2_profile_root"] = "host2/profiles"
    spec["workspace_name"] = "argv-barrier"
    return spec


def _run_argv_barrier_flow(
    monkeypatch,
    tmp_path,
    stable_test_root,
    *,
    wrong_version=None,
    wrong_host2_version=None,
    leak_phase=None,
    exception_leak_phase=None,
    restored_symlink=False,
    unexpected_phase=None,
    post_materialization_base_exception=None,
    leak_payload=None,
    exception_leak_payload=None,
    scratch_leak_payload=None,
    credential_guard_mutation=None,
    profile_topology="nested",
    preexisting_profile_symlink=None,
    controlled_sentinel=CONTROLLED_RUNTIME_SENTINEL,
):
    spec = _argv_barrier_spec(stable_test_root)
    if profile_topology == "sibling":
        spec.pop("host2_profile_root")
    elif profile_topology != "nested":
        raise AssertionError(f"unsupported profile topology: {profile_topology}")
    leak_payload = controlled_sentinel if leak_payload is None else leak_payload
    exception_leak_payload = (
        controlled_sentinel
        if exception_leak_payload is None
        else exception_leak_payload
    )
    binaries = {
        "codex": "/opt/agents/codex-real",
        "claude": "/opt/agents/claude-real",
    }
    monkeypatch.setattr(e3.shutil, "which", lambda name: binaries.get(name))
    spec_path = tmp_path / "argv-barrier.json"
    spec_path.write_text(json.dumps(spec), encoding="utf-8")
    biv = tmp_path / "fake-biv"
    scratch = stable_test_root / "scratch"
    if preexisting_profile_symlink is not None:
        outside = stable_test_root / "outside-profile-topology"
        outside.mkdir()
        (outside / "canary").write_text("outside-unchanged", encoding="utf-8")
        if profile_topology == "sibling" and preexisting_profile_symlink == "leaf":
            scratch.mkdir()
            (scratch / "host2-profile").symlink_to(
                outside,
                target_is_directory=True,
            )
        elif (
            profile_topology == "sibling"
            and preexisting_profile_symlink == "ancestor"
        ):
            scratch.symlink_to(outside, target_is_directory=True)
        elif profile_topology == "nested" and preexisting_profile_symlink == "leaf":
            (scratch / "host2").mkdir(parents=True)
            (scratch / "host2" / "profiles").symlink_to(
                outside,
                target_is_directory=True,
            )
        elif (
            profile_topology == "nested"
            and preexisting_profile_symlink == "ancestor"
        ):
            scratch.mkdir()
            (scratch / "host2").symlink_to(outside, target_is_directory=True)
        else:
            raise AssertionError(
                (profile_topology, preexisting_profile_symlink)
            )
    ledger = []
    lifecycle_events = []
    exceptional_phases = set()
    seed_attempts = {agent["id"]: 0 for agent in spec["agents"]}
    resume_attempts = {agent["id"]: 0 for agent in spec["agents"]}

    def write_seed_transcript(agent, command, cwd, attempt):
        token = next(
            part for part in command
            if part.startswith(agent["run_token_prefix"] + "_")
        )
        session_id = "aaaaaaaa-1111-4111-8111-111111111111" if agent["id"] == "codex" else "bbbbbbbb-2222-4222-8222-222222222222"
        if agent["id"] == "codex":
            transcript = Path(agent["live_profile"]) / f"rollout-2026-07-22-{session_id}.jsonl"
        else:
            transcript = (
                Path(agent["live_profile"])
                / "projects"
                / e3._project_key(cwd)
                / f"{session_id}.jsonl"
            )
        transcript.parent.mkdir(parents=True, exist_ok=True)
        is_continue = command[1] == "continue" or "resume" in command
        turns = ["one"] if not is_continue else ["one", "two"]
        transcript.write_text(
            "\n".join([token, *turns, f"attempt-{attempt}"]) + "\n",
            encoding="utf-8",
        )

    def base_spawn(command, cwd, env):
        command = list(command)
        ledger.append((command, Path(cwd), dict(env)))
        if command[0] == str(biv):
            if command[1] == "pack":
                return _successful_pack()
            if command[1] == "open":
                destination = Path(command[command.index("--dest") + 1])
                result = _open_process_result(destination)
                if restored_symlink:
                    shutil.rmtree(destination)
                    outside = stable_test_root / "outside-restored"
                    outside.mkdir()
                    destination.symlink_to(outside, target_is_directory=True)
                return result
        agent = next(
            agent for agent in spec["agents"]
            if command[0] in (agent["auth_status"][0], binaries[agent["auth_status"][0]])
        )
        agent_name = agent["id"]
        if command[1:] == ["--version"]:
            if Path(cwd) == scratch / "host2":
                lifecycle_events.append(
                    ("version", agent_name, tuple(command), None)
                )
            version = {
                "codex": "0.144.1",
                "claude-code": "2.1.210",
            }[agent_name]
            if wrong_version == agent_name or (
                wrong_host2_version == agent_name
                and Path(cwd) == scratch / "host2"
            ):
                version = "9.9.9"
            return SimpleNamespace(returncode=0, stdout=version, stderr="")
        if command[1:] in (["login", "status"], ["auth", "status"]):
            return SimpleNamespace(returncode=0, stdout="authenticated", stderr="")
        if "-p" in command:
            attempt = sum(
                1 for item, _, _ in ledger
                if item[0] == command[0] and "-p" in item
            )
            return SimpleNamespace(
                returncode=1 if attempt == 1 else 0,
                stdout="" if attempt == 1 else "OK",
                stderr="transient" if attempt == 1 else "",
            )
        if cwd == scratch / "seed-ws" / spec["workspace_name"]:
            if command[1] == "continue" or "resume" in command:
                seed_attempts[agent_name] += 1
                write_seed_transcript(agent, command, cwd, seed_attempts[agent_name])
                return SimpleNamespace(
                    returncode=1 if seed_attempts[agent_name] == 2 else 0,
                    stdout="" if seed_attempts[agent_name] == 2 else "reply",
                    stderr="transient" if seed_attempts[agent_name] == 2 else "",
                )
            seed_attempts[agent_name] += 1
            write_seed_transcript(agent, command, cwd, seed_attempts[agent_name])
            return SimpleNamespace(returncode=0, stdout="reply", stderr="")
        resume_attempts[agent_name] += 1
        return SimpleNamespace(
            returncode=1 if resume_attempts[agent_name] == 1 else 0,
            stdout="" if resume_attempts[agent_name] == 1 else "reply",
            stderr="transient" if resume_attempts[agent_name] == 1 else "",
        )

    def fake_spawn(command, cwd, env):
        result = base_spawn(command, cwd, env)
        phase = None
        if command[0] == str(biv) and len(command) > 1 and command[1] == "open":
            phase = "open"
        elif command[1:] in (["login", "status"], ["auth", "status"]):
            phase = "auth"
        elif "-p" in command:
            phase = "liveness"
        elif Path(cwd) == scratch / "host2" / "work":
            phase = "resume"
        post_materialization = Path(cwd) != scratch / "seed-ws" / spec["workspace_name"]
        if scratch_leak_payload is not None and phase == "open":
            leaked = scratch / "seed-ws" / "post-materialization-leaf"
            leaked.write_text(scratch_leak_payload, encoding="utf-8")
        if (
            post_materialization_base_exception is not None
            and phase == "open"
        ):
            raise post_materialization_base_exception
        if unexpected_phase is not None and phase == unexpected_phase:
            raise RuntimeError("unexpected synthetic execution failure")
        if (
            exception_leak_phase is not None
            and phase == exception_leak_phase
            and post_materialization
            and phase not in exceptional_phases
        ):
            exceptional_phases.add(phase)
            raise e3.subprocess.TimeoutExpired(
                command,
                120,
                output=exception_leak_payload.encode(),
                stderr=b"exceptional-attempt-stderr",
            )
        if phase == leak_phase:
            return SimpleNamespace(
                returncode=result.returncode,
                stdout=result.stdout,
                stderr=(result.stderr or "") + leak_payload,
            )
        return result

    def fake_install_delta(agent_id, profile, *args):
        path = Path(profile) / f"{agent_id}-installed.jsonl"
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text("one\ntwo\n", encoding="utf-8")
        return [path]

    setup_calls = []
    real_setup = e3.setup_host2_credentials
    real_keychain_materializer = e3.materialize_keychain_credential
    real_file_materializer = e3.materialize_file_credential

    def recording_keychain_materializer(service, account, dest, **kwargs):
        lifecycle_events.append(
            ("materializer", "claude-code", None, Path(dest))
        )
        return real_keychain_materializer(service, account, dest, **kwargs)

    def recording_file_materializer(source, dest, **kwargs):
        lifecycle_events.append(("materializer", "codex", None, Path(dest)))
        return real_file_materializer(source, dest, **kwargs)

    def recording_setup(*args):
        setup_calls.append(args)
        envs = real_setup(*args)
        if credential_guard_mutation is not None:
            credential_id, mutation = credential_guard_mutation
            profile_root = Path(args[2])
            agent = next(
                item for item in args[0]["agents"] if item["id"] == credential_id
            )
            profile = e3._agent_profile(agent, profile_root, live=False)
            target = (
                profile / ".credentials.json"
                if credential_id == "claude-code"
                else profile / "auth.json"
            )
            target.unlink()
            if mutation == "replaced":
                target.write_bytes(b"replacement-object")
        return envs

    monkeypatch.setattr(e3, "_spawn", fake_spawn)
    monkeypatch.setattr(
        e3,
        "_runtime_credential_sentinels",
        lambda count: [controlled_sentinel] if count == 1 else pytest.fail(count),
    )
    monkeypatch.setattr(e3, "scan_image_secret_values", lambda *args: [])
    monkeypatch.setattr(e3, "assert_exact_install_delta", fake_install_delta)
    monkeypatch.setattr(e3, "assert_resume_containment", lambda *args, **kwargs: None)
    monkeypatch.setattr(
        e3,
        "materialize_keychain_credential",
        recording_keychain_materializer,
    )
    monkeypatch.setattr(
        e3,
        "materialize_file_credential",
        recording_file_materializer,
    )
    monkeypatch.setattr(e3, "setup_host2_credentials", recording_setup)
    result = e3.run_e3(spec_path, biv, scratch)
    return result, spec, binaries, ledger, setup_calls, scratch, lifecycle_events


def _agent_ledger(ledger, binaries):
    result = []
    for command, cwd, _ in ledger:
        raw_name = next(
            (agent_id for agent_id, binary in binaries.items()
             if binary == command[0] or agent_id == command[0]),
            None,
        )
        if raw_name is None:
            continue
        result.append(("claude-code" if raw_name == "claude" else raw_name, command, cwd))
    return result


def test_run_e3_uses_one_absolute_binary_for_full_agent_argv_ledger_and_global_barrier(
    monkeypatch, tmp_path, stable_test_root
):
    (
        result,
        spec,
        binaries,
        ledger,
        setup_calls,
        scratch,
        lifecycle_events,
    ) = _run_argv_barrier_flow(
        monkeypatch, tmp_path, stable_test_root
    )

    assert result.status is Status.PASS
    assert setup_calls
    agent_ledger = _agent_ledger(ledger, binaries)
    assert all(
        command[0] == binaries["claude" if agent_id == "claude-code" else agent_id]
        for agent_id, command, _ in agent_ledger
    )
    events = []
    seed_workspace = scratch / "seed-ws" / spec["workspace_name"]
    restored_workspace = scratch / "host2" / "work"
    for agent_id, command, cwd in agent_ledger:
        if command[1:] == ["--version"]:
            event = "version"
        elif command[1:] in (["login", "status"], ["auth", "status"]):
            event = "auth"
        elif "-p" in command:
            event = "liveness"
        elif cwd == seed_workspace:
            event = "seed-continue" if command[1] == "continue" or "resume" in command else "seed-start"
        elif cwd == restored_workspace:
            event = "resume"
        else:
            raise AssertionError((agent_id, command, cwd))
        events.append((agent_id, event))
    assert events == [
        ("codex", "version"), ("claude-code", "version"),
        ("codex", "auth"), ("claude-code", "auth"),
        ("codex", "seed-start"), ("codex", "seed-continue"),
        ("codex", "seed-continue"), ("claude-code", "seed-start"),
        ("claude-code", "seed-continue"), ("claude-code", "seed-continue"),
        ("codex", "version"), ("claude-code", "version"),
        ("codex", "auth"), ("claude-code", "auth"),
        ("claude-code", "liveness"), ("claude-code", "liveness"),
        ("codex", "resume"), ("codex", "resume"),
        ("claude-code", "resume"), ("claude-code", "resume"),
    ]
    first_auth = events.index(("codex", "auth"))
    assert all(event == "version" for _, event in events[:first_auth])
    assert [event[:2] for event in lifecycle_events] == [
        ("version", "codex"),
        ("version", "claude-code"),
        ("materializer", "claude-code"),
        ("materializer", "codex"),
    ]
    version_events = [
        event for event in lifecycle_events if event[0] == "version"
    ]
    materializer_events = [
        event for event in lifecycle_events if event[0] == "materializer"
    ]
    expected_versions = [
        (
            agent["id"],
            tuple(
                e3._rewrite_agent_command(
                    agent["version_command"],
                    binaries[agent["auth_status"][0]],
                )
            ),
        )
        for agent in spec["agents"]
    ]
    assert [(event[1], event[2]) for event in version_events] == expected_versions
    assert all(Path(command[0]).is_absolute() for _, command in expected_versions)
    profile_root = scratch / "host2" / "profiles"
    expected_destinations = [
        (
            "claude-code",
            e3._agent_profile(
                next(
                    agent
                    for agent in spec["agents"]
                    if agent["id"] == "claude-code"
                ),
                profile_root,
                live=False,
            )
            / ".credentials.json",
        ),
        (
            "codex",
            e3._agent_profile(
                next(agent for agent in spec["agents"] if agent["id"] == "codex"),
                profile_root,
                live=False,
            )
            / "auth.json",
        ),
    ]
    assert [(event[1], event[3]) for event in materializer_events] == (
        expected_destinations
    )
    assert max(lifecycle_events.index(event) for event in version_events) < min(
        lifecycle_events.index(event) for event in materializer_events
    )
    assert agent_ledger[5][1] == agent_ledger[6][1]
    assert agent_ledger[8][1] == agent_ledger[9][1]
    assert agent_ledger[14][1] == agent_ledger[15][1]
    assert agent_ledger[16][1] == agent_ledger[17][1]
    assert agent_ledger[18][1] == agent_ledger[19][1]


@pytest.mark.parametrize("leak_phase", ("auth", "liveness", "open", "resume"))
def test_run_e3_invalidates_each_post_materialization_output_leak(
    monkeypatch, tmp_path, stable_test_root, leak_phase
):
    result, *_ = _run_argv_barrier_flow(
        monkeypatch,
        tmp_path,
        stable_test_root,
        leak_phase=leak_phase,
    )

    assert result.status is Status.INVALID
    assert "credential-child-output-detected" in result.warnings
    assert CONTROLLED_RUNTIME_SENTINEL not in serialize_report([result])


@pytest.mark.parametrize(
    "exception_leak_phase",
    ("auth", "liveness", "open", "resume"),
)
def test_run_e3_invalidates_each_exceptional_post_materialization_output_leak(
    monkeypatch, tmp_path, stable_test_root, exception_leak_phase
):
    result, _, _, ledger, _, _, _ = _run_argv_barrier_flow(
        monkeypatch,
        tmp_path,
        stable_test_root,
        exception_leak_phase=exception_leak_phase,
    )

    assert result.status is Status.INVALID
    assert "credential-child-output-detected" in result.warnings
    assert CONTROLLED_RUNTIME_SENTINEL not in serialize_report([result])
    if exception_leak_phase == "auth":
        auth_calls = [
            command
            for command, _, _ in ledger
            if command[1:] in (["login", "status"], ["auth", "status"])
        ]
        assert len(auth_calls) == 4


def test_run_e3_invalidates_token_leaf_copied_into_scratch_after_materialization(
    monkeypatch, tmp_path, stable_test_root
):
    result, *_ = _run_argv_barrier_flow(
        monkeypatch,
        tmp_path,
        stable_test_root,
        scratch_leak_payload=CONTROLLED_RUNTIME_SENTINEL,
    )

    assert result.status is Status.INVALID
    assert "credential-scan-detected" in result.warnings
    assert CONTROLLED_RUNTIME_SENTINEL not in serialize_report([result])


@pytest.mark.parametrize("mutation", ("missing", "replaced"))
def test_run_e3_invalidates_changed_credential_guard_after_materialization(
    monkeypatch, tmp_path, stable_test_root, mutation
):
    result, *_ = _run_argv_barrier_flow(
        monkeypatch,
        tmp_path,
        stable_test_root,
        credential_guard_mutation=("codex", mutation),
    )

    serialized = serialize_report([result])
    assert result.status is Status.INVALID
    assert "credential-exclusion-integrity-failed" in result.warnings
    assert CODEX_ACCESS_LEAF not in serialized


def test_run_e3_rejects_restored_workspace_symlink_before_any_resume_spawn(
    monkeypatch, tmp_path, stable_test_root
):
    result, _, binaries, ledger, _, scratch, _ = _run_argv_barrier_flow(
        monkeypatch,
        tmp_path,
        stable_test_root,
        restored_symlink=True,
    )

    assert result.status is Status.INVALID
    restored_workspace = scratch / "host2" / "work"
    resume_calls = [
        command
        for _, command, cwd in _agent_ledger(ledger, binaries)
        if cwd == restored_workspace
    ]
    assert resume_calls == []


@pytest.mark.parametrize("outcome", ("pass", "resume-invalid", "runtime"))
def test_run_e3_finalizes_exactly_once_for_each_execution_outcome(
    monkeypatch, tmp_path, stable_test_root, outcome
):
    calls = 0
    real_finalize = e3._finalize_report

    def recording_finalize(result, scanner):
        nonlocal calls
        calls += 1
        return real_finalize(result, scanner)

    monkeypatch.setattr(e3, "_finalize_report", recording_finalize)
    kwargs = {}
    if outcome == "resume-invalid":
        kwargs["leak_phase"] = "resume"
    elif outcome == "runtime":
        kwargs["unexpected_phase"] = "open"
    result, *_ = _run_argv_barrier_flow(
        monkeypatch,
        tmp_path,
        stable_test_root,
        **kwargs,
    )

    assert result.status is (Status.PASS if outcome == "pass" else Status.INVALID)
    assert calls == 1


def test_run_e3_token_materialization_exception_is_finalized_and_dropped_once(
    monkeypatch, tmp_path, stable_test_root
):
    spec_path, _ = _configure_exit_contract_case(
        monkeypatch,
        tmp_path,
        pack_result=_successful_pack(),
    )
    scanners = []

    class RecordingScanner(e3._CredentialScanner):
        def __init__(self):
            super().__init__()
            self.drop_calls = 0
            scanners.append(self)

        def drop(self):
            self.drop_calls += 1
            return super().drop()

    finalize_calls = 0
    real_finalize = e3._finalize_report

    def recording_finalize(result, scanner):
        nonlocal finalize_calls
        finalize_calls += 1
        return real_finalize(result, scanner)

    monkeypatch.setattr(e3, "_CredentialScanner", RecordingScanner)
    monkeypatch.setattr(
        e3,
        "materialize_run_tokens",
        lambda _spec: (_ for _ in ()).throw(RuntimeError("token setup failed")),
    )
    monkeypatch.setattr(e3, "_finalize_report", recording_finalize)

    result = e3.run_e3(spec_path, Path("/fake/biv"), stable_test_root / "scratch")

    assert result.status is Status.INVALID
    assert finalize_calls == 1
    assert len(scanners) == 1
    assert scanners[0].drop_calls == 1


def test_run_e3_post_materialization_baseexception_finalizes_and_removes_all_targets(
    monkeypatch, tmp_path, stable_test_root
):
    class SyntheticAbort(BaseException):
        pass

    scanners = []

    class RecordingScanner(e3._CredentialScanner):
        def __init__(self):
            super().__init__()
            self.drop_calls = 0
            scanners.append(self)

        def drop(self):
            self.drop_calls += 1
            return super().drop()

    finalize_calls = 0
    real_finalize = e3._finalize_report

    def recording_finalize(result, scanner):
        nonlocal finalize_calls
        finalize_calls += 1
        return real_finalize(result, scanner)

    monkeypatch.setattr(e3, "_CredentialScanner", RecordingScanner)
    monkeypatch.setattr(e3, "_finalize_report", recording_finalize)
    result, spec, _, _, _, scratch, _ = _run_argv_barrier_flow(
        monkeypatch,
        tmp_path,
        stable_test_root,
        post_materialization_base_exception=SyntheticAbort(
            "synthetic post-materialization abort"
        ),
    )

    profile_root = scratch / "host2" / "profiles"
    claude = next(agent for agent in spec["agents"] if agent["id"] == "claude-code")
    codex = next(agent for agent in spec["agents"] if agent["id"] == "codex")
    claude_dest = e3._agent_profile(claude, profile_root, live=False) / ".credentials.json"
    codex_dest = e3._agent_profile(codex, profile_root, live=False) / "auth.json"
    targets = (
        claude_dest,
        codex_dest,
        profile_root,
        scratch / "host2",
        scratch / "seed-ws",
    )
    assert result.status is Status.INVALID
    assert finalize_calls == 1
    assert len(scanners) == 1
    assert scanners[0].drop_calls == 1
    for target in targets:
        with pytest.raises(FileNotFoundError):
            os.lstat(target)


@pytest.mark.parametrize("wrong_version", ["claude-code", "codex"])
def test_run_e3_wrong_agent_version_is_invalid_before_any_auth_or_setup(
    monkeypatch, tmp_path, stable_test_root, wrong_version
):
    result, _, _, ledger, setup_calls, _, lifecycle_events = _run_argv_barrier_flow(
        monkeypatch, tmp_path, stable_test_root, wrong_version=wrong_version
    )

    _assert_report_refused(result)
    assert setup_calls == []
    assert lifecycle_events == []
    assert not any(command[1:] in (["login", "status"], ["auth", "status"]) for command, _, _ in ledger)


@pytest.mark.parametrize("wrong_host2_version", ["claude-code", "codex"])
def test_run_e3_wrong_host2_version_materializes_no_credentials(
    monkeypatch, tmp_path, stable_test_root, wrong_host2_version
):
    result, spec, _, _, setup_calls, scratch, lifecycle_events = _run_argv_barrier_flow(
        monkeypatch,
        tmp_path,
        stable_test_root,
        wrong_host2_version=wrong_host2_version,
    )

    assert result.status is Status.INVALID
    assert result.detail == "e3-post-materialization-invalid"
    assert len(setup_calls) == 1
    assert [event[0] for event in lifecycle_events] == ["version", "version"]
    assert not any(event[0] == "materializer" for event in lifecycle_events)
    profile_root = scratch / "host2" / "profiles"
    for agent in spec["agents"]:
        profile = e3._agent_profile(agent, profile_root, live=False)
        destination = (
            profile / ".credentials.json"
            if agent["id"] == "claude-code"
            else profile / "auth.json"
        )
        with pytest.raises(FileNotFoundError):
            os.lstat(destination)


@pytest.mark.parametrize("profile_topology", ("sibling", "nested"))
@pytest.mark.parametrize("symlink_case", ("leaf", "ancestor"))
def test_run_e3_refuses_preexisting_profile_symlink_before_host2_credential_work(
    monkeypatch,
    tmp_path,
    stable_test_root,
    profile_topology,
    symlink_case,
):
    result, _, _, ledger, _, _, lifecycle_events = _run_argv_barrier_flow(
        monkeypatch,
        tmp_path,
        stable_test_root,
        profile_topology=profile_topology,
        preexisting_profile_symlink=symlink_case,
    )

    outside = stable_test_root / "outside-profile-topology"
    canary = outside / "canary"
    host2 = stable_test_root / "scratch" / "host2"
    assert result.status is Status.INVALID
    assert lifecycle_events == []
    assert not any(
        Path(cwd) == host2
        and command[1:] in (
            ["--version"],
            ["login", "status"],
            ["auth", "status"],
        )
        for command, cwd, _ in ledger
    )
    assert canary.read_text(encoding="utf-8") == "outside-unchanged"
    assert list(outside.iterdir()) == [canary]


def test_e3_spec_validation_rejects_dead_or_wrong_resume_shape():
    base = {
        "id": "agent",
        "live_profile": "~/.agent",
        "auth_status": ["agent", "auth"],
        "version_command": ["agent", "version"],
        "validated_version_prefixes": ["1.0."],
        "seed_start_command": ["agent", "seed"],
        "seed_continue_command": ["agent", "continue"],
        "ownership_glob": "*.jsonl",
        "run_token": "token",
        "resume_command": ["agent", "resume"],
    }
    spec = {
        "tier": "E3",
        "seed_turns": ["one", "two"],
        "resume_probe": "probe",
        "agents": [
            {**base, "id": "claude-code", "resume_mutation": "forks-new-file"},
            {**base, "id": "codex", "resume_shape": CODEX_RESUME_SHAPE},
        ],
    }
    assert "Claude resume mutation must match the pinned shape" in e3._validate_spec(spec)


@pytest.mark.parametrize("name", CREDENTIAL_ENV_NAMES)
def test_credential_inventory_rejects_each_named_variable(name):
    assert rejected_credential_names({name: "secret"}) == [name]


def test_profile_root_guards_tmp_mnt_and_live_store(tmp_path):
    live = tmp_path / "live-store"
    live.mkdir()

    assert "profile-root-tmp" in profile_root_failures(Path("/tmp/host2"), [])
    assert "profile-root-mnt" in profile_root_failures(Path("/mnt/c/host2"), [])
    assert "profile-root-live-store" in profile_root_failures(live / "nested", [live])


def test_profile_root_accepts_isolated_native_path(tmp_path):
    root = Path.home() / ".cache" / "bivharness-e3-test-profile"
    live = tmp_path / "live-store"

    assert profile_root_failures(root, [live]) == []
