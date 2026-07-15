import json
import sys
from pathlib import Path
from types import SimpleNamespace

from ci import run_clang_tidy


def _write_compile_commands(tmp_path: Path, names: tuple[str, ...]) -> tuple[Path, list[Path]]:
    source_dir = tmp_path / "src"
    source_dir.mkdir()
    sources = []
    rows = []
    for name in names:
        source = source_dir / name
        source.write_text("int main() { return 0; }\n", encoding="utf-8")
        sources.append(source.resolve())
        rows.append({"file": str(source)})

    compile_commands = tmp_path / "compile_commands.json"
    compile_commands.write_text(json.dumps(rows), encoding="utf-8")
    return compile_commands, sources


def _set_main_args(monkeypatch, compile_commands: Path, source_root: Path) -> None:
    monkeypatch.setattr(
        sys,
        "argv",
        [
            "run_clang_tidy.py",
            "--clang-tidy",
            "clang-tidy",
            "--compile-commands",
            str(compile_commands),
            "--source-root",
            str(source_root),
        ],
    )


def test_analyze_converts_spawn_failure_to_red_result(monkeypatch, tmp_path):
    source = tmp_path / "source.cpp"

    def fail_to_spawn(*_args, **_kwargs):
        raise OSError("clang-tidy is unavailable")

    monkeypatch.setattr(run_clang_tidy.subprocess, "run", fail_to_spawn)

    result = run_clang_tidy._analyze(source, "clang-tidy", tmp_path)

    assert result[:3] == (source, 97, "")
    assert "clang-tidy is unavailable" in result[3]


def test_main_rejects_missing_source_result(monkeypatch, tmp_path, capsys):
    compile_commands, sources = _write_compile_commands(tmp_path, ("a.cpp", "b.cpp"))
    _set_main_args(monkeypatch, compile_commands, tmp_path)
    monkeypatch.setattr(
        run_clang_tidy,
        "_run_parallel",
        lambda *_args: [(sources[0], 0, "", "")],
    )

    assert run_clang_tidy.main() == 1
    assert "COVERAGE FAILURE: 1 results vs 2 sources - a TU was DROPPED" in capsys.readouterr().out


def test_main_reports_failures_in_source_order(monkeypatch, tmp_path, capsys):
    compile_commands, sources = _write_compile_commands(tmp_path, ("a.cpp", "b.cpp"))
    _set_main_args(monkeypatch, compile_commands, tmp_path)
    monkeypatch.setattr(
        run_clang_tidy,
        "_run_parallel",
        lambda *_args: [
            (sources[1], 1, "b stdout", "b stderr"),
            (sources[0], 2, "a stdout", "a stderr"),
        ],
    )

    assert run_clang_tidy.main() == 1
    output = capsys.readouterr().out
    assert "clang-tidy coverage: 2 results == 2 sources" in output
    assert output.index(str(sources[0])) < output.index(str(sources[1]))


def test_parallel_results_match_serial_results(monkeypatch, tmp_path):
    sources = [tmp_path / "b.cpp", tmp_path / "a.cpp"]

    def fake_run(command, **_kwargs):
        source = Path(command[-1])
        return SimpleNamespace(
            returncode=1 if source.name == "b.cpp" else 0,
            stdout=f"stdout:{source.name}",
            stderr=f"stderr:{source.name}",
        )

    monkeypatch.setattr(run_clang_tidy.subprocess, "run", fake_run)
    serial = [run_clang_tidy._analyze(source, "clang-tidy", tmp_path) for source in sources]

    parallel = run_clang_tidy._run_parallel(sources, "clang-tidy", tmp_path)

    assert sorted(parallel) == sorted(serial)
