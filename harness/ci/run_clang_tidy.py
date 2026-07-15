import argparse
import json
import os
import subprocess
from concurrent.futures import ThreadPoolExecutor
from functools import partial
from pathlib import Path


CHECKS = (
    "cppcoreguidelines-*,bugprone-*,cert-*,clang-analyzer-*,"
    # Policy ruling 175152: excluded for v1 Step 3; R-6.5 owes an audited sys::open wrapper and re-enablement.
    "-cppcoreguidelines-pro-type-vararg,"
    "-cppcoreguidelines-avoid-magic-numbers,"
    "-cppcoreguidelines-pro-bounds-array-to-pointer-decay"
)


def _project_sources(compile_commands: Path, source_root: Path) -> list[Path]:
    rows = json.loads(compile_commands.read_text(encoding="utf-8"))
    sources: list[Path] = []
    for row in rows:
        file_path = Path(row["file"]).resolve()
        try:
            rel = file_path.relative_to(source_root)
        except ValueError:
            continue
        if rel.parts and rel.parts[0] == "src":
            sources.append(file_path)
    return sorted(set(sources))


def _analyze(
    source: Path, clang_tidy: str, compile_commands: Path
) -> tuple[Path, int, str, str]:
    try:
        run = subprocess.run(
            [
                clang_tidy,
                "--quiet",
                f"-checks={CHECKS}",
                "--warnings-as-errors=*",
                "-p",
                str(compile_commands.parent),
                str(source),
            ],
            check=False,
            text=True,
            capture_output=True,
        )
        return source, run.returncode, run.stdout, run.stderr
    except Exception as error:
        return source, 97, "", f"analyzer failed to run on {source}: {error}"


def _run_parallel(
    sources: list[Path], clang_tidy: str, compile_commands: Path
) -> list[tuple[Path, int, str, str]]:
    analyze = partial(
        _analyze, clang_tidy=clang_tidy, compile_commands=compile_commands
    )
    with ThreadPoolExecutor(max_workers=os.cpu_count() or 4) as executor:
        return list(executor.map(analyze, sources))


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--clang-tidy", required=True)
    parser.add_argument("--compile-commands", required=True, type=Path)
    parser.add_argument("--source-root", required=True, type=Path)
    args = parser.parse_args()

    if not args.compile_commands.exists():
        print(f"compile_commands.json missing: {args.compile_commands}")
        return 1

    sources = _project_sources(args.compile_commands, args.source_root.resolve())
    if not sources:
        print("compile_commands.json contains no project sources")
        return 1

    results = _run_parallel(sources, args.clang_tidy, args.compile_commands)
    if len(results) != len(sources):
        print(
            f"COVERAGE FAILURE: {len(results)} results vs {len(sources)} sources"
            " - a TU was DROPPED"
        )
        return 1

    print(f"clang-tidy coverage: {len(results)} results == {len(sources)} sources")
    failures = []
    for source, returncode, stdout, stderr in sorted(results):
        if returncode != 0:
            failures.append(f"{source} exited {returncode}\n{stdout}\n{stderr}")

    if failures:
        print("\n".join(failures))
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
