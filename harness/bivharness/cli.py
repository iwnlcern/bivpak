import argparse
import json
import tempfile
from pathlib import Path

from bivharness.report import Report
from bivharness.scenario import run_scenario


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(prog="bivharness")
    parser.add_argument("--biv", required=True, type=Path)
    parser.add_argument("--scenarios", required=True, type=Path)
    parser.add_argument("--report", required=True, type=Path)
    args = parser.parse_args(argv)

    biv = args.biv.resolve()
    scenarios = args.scenarios.resolve()
    report_path = args.report.resolve()
    report_path.parent.mkdir(parents=True, exist_ok=True)

    with tempfile.TemporaryDirectory(prefix=".bivharness-scratch-", dir=report_path.parent) as scratch_dir:
        scratch = Path(scratch_dir)
        results = [
            run_scenario(path, biv, scratch / path.stem)
            for path in sorted(scenarios.rglob("*.json"))
        ]
    report = Report(results)
    report_path.write_text(json.dumps(report.to_json(), indent=2, sort_keys=True) + "\n", encoding="utf-8")
    return report.exit_code()


if __name__ == "__main__":
    raise SystemExit(main())
