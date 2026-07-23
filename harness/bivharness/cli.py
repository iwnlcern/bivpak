import argparse
import os
import tempfile
from pathlib import Path

from bivharness.e3 import run_e3
from bivharness.report import Report, ScenarioResult, serialize_report
from bivharness.scenario import run_scenario


def _write_report_atomic(
    report_path: Path,
    results: list[ScenarioResult],
) -> None:
    serialized = serialize_report(results)
    temporary: Path | None = None
    try:
        with tempfile.NamedTemporaryFile(
            mode="w",
            encoding="utf-8",
            prefix=f".{report_path.name}.",
            suffix=".tmp",
            dir=report_path.parent,
            delete=False,
        ) as stream:
            temporary = Path(stream.name)
            stream.write(serialized)
        os.replace(temporary, report_path)
    finally:
        if temporary is not None:
            temporary.unlink(missing_ok=True)


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(prog="bivharness")
    parser.add_argument("--biv", required=True, type=Path)
    mode = parser.add_mutually_exclusive_group(required=True)
    mode.add_argument("--scenarios", type=Path)
    mode.add_argument("--e3", type=Path)
    parser.add_argument("--dry-run", action="store_true")
    parser.add_argument("--report", required=True, type=Path)
    args = parser.parse_args(argv)

    biv = args.biv.resolve()
    report_path = args.report.resolve()
    report_path.parent.mkdir(parents=True, exist_ok=True)

    with tempfile.TemporaryDirectory(prefix=".bivharness-scratch-", dir=report_path.parent) as scratch_dir:
        scratch = Path(scratch_dir)
        if args.e3:
            e3 = args.e3.resolve()
            results = [run_e3(e3, biv, scratch / e3.stem, dry_run=args.dry_run)]
        else:
            scenarios = args.scenarios.resolve()
            results = [
                run_scenario(path, biv, scratch / path.stem)
                for path in sorted(scenarios.rglob("*.json"))
            ]
    _write_report_atomic(report_path, results)
    return Report(results).exit_code()


if __name__ == "__main__":
    raise SystemExit(main())
