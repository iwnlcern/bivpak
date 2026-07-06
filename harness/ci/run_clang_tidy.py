import argparse
import json
import subprocess
from pathlib import Path


CHECKS = (
    "cppcoreguidelines-*,bugprone-*,cert-*,clang-analyzer-*,"
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

    failures = []
    for source in sources:
        run = subprocess.run(
            [
                args.clang_tidy,
                "--quiet",
                f"-checks={CHECKS}",
                "--warnings-as-errors=*",
                "-p",
                str(args.compile_commands.parent),
                str(source),
            ],
            check=False,
            text=True,
            capture_output=True,
        )
        if run.returncode != 0:
            failures.append(f"{source} exited {run.returncode}\n{run.stdout}\n{run.stderr}")

    if failures:
        print("\n".join(failures))
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
