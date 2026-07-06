import os
from pathlib import Path
from types import SimpleNamespace

from bivharness import precheck


def test_probe_passes_on_native_tmp_path(tmp_path):
    assert precheck.probe(tmp_path) == []


def test_probe_reports_mode_roundtrip_failure(monkeypatch, tmp_path):
    def fake_stat(path, *, follow_symlinks=True):
        return SimpleNamespace(st_mode=0o100777)

    monkeypatch.setattr(precheck.os, "stat", fake_stat)

    assert "mode-roundtrip" in precheck.probe(tmp_path)


def test_probe_reports_drvfs_guard_without_touching_mnt():
    assert "drvfs-guard" in precheck.probe(Path("/mnt/c/x"))


def test_pin_env_sets_reproducible_process_defaults(monkeypatch):
    old_umask = os.umask(0o077)
    os.umask(old_umask)
    try:
        previous = precheck.pin_env()
        assert os.environ["TZ"] == "UTC"
        assert os.environ["LC_ALL"] == "C"
        current = os.umask(0o077)
        os.umask(current)
        assert current == 0o022
        os.umask(previous)
    finally:
        os.umask(old_umask)
