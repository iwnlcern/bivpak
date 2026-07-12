from pathlib import Path
from types import SimpleNamespace

from bivharness import scenario


def test_run_json_merges_environment_overrides(monkeypatch, tmp_path):
    captured = {}

    def fake_run(*args, **kwargs):
        captured.update(kwargs["env"])
        return SimpleNamespace(
            returncode=0,
            stdout='{"ok":true}',
            stderr="",
        )

    monkeypatch.setenv("BIVHARNESS_PARENT", "kept")
    monkeypatch.setattr(scenario.subprocess, "run", fake_run)

    scenario._run_json(
        Path("biv"),
        ["open", "image.bvpk"],
        tmp_path,
        {"BIVHARNESS_CHILD": "added", "BIVHARNESS_PARENT": "overridden"},
    )

    assert captured["BIVHARNESS_CHILD"] == "added"
    assert captured["BIVHARNESS_PARENT"] == "overridden"


def test_run_json_default_preserves_parent_environment(monkeypatch, tmp_path):
    captured = {}

    def fake_run(*args, **kwargs):
        captured.update(kwargs["env"])
        return SimpleNamespace(returncode=0, stdout='{"ok":true}', stderr="")

    monkeypatch.setenv("BIVHARNESS_PARENT", "kept")
    monkeypatch.setattr(scenario.subprocess, "run", fake_run)

    scenario._run_json(Path("biv"), ["pack", "source"], tmp_path)

    assert captured["BIVHARNESS_PARENT"] == "kept"
