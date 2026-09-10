#!/usr/bin/env python3
import pathlib
import re
import sys


def parse_cells(path: pathlib.Path, observed: bool):
    rows = {}
    for raw in path.read_text(encoding="utf-8").splitlines():
        if raw.startswith("expected_skips"):
            continue
        parts = raw.split()
        if len(parts) < 6:
            raise SystemExit(f"malformed cells row: {raw!r}")
        binary, target = parts[0], parts[1]
        values = {}
        for field in parts[2:]:
            if "=" not in field:
                raise SystemExit(f"malformed field: {field!r}")
            key, value = field.split("=", 1)
            if key == "xml_sha256":
                if not observed or not re.fullmatch(r"[0-9a-f]{64}", value):
                    raise SystemExit(f"bad xml hash: {value!r}")
                continue
            if key not in {"successes", "failures", "expectedFailures", "skips"}:
                raise SystemExit(f"unexpected key: {key!r}")
            values[key] = int(value)
        if set(values) != {"successes", "failures", "expectedFailures", "skips"}:
            raise SystemExit(f"incomplete tuple: {raw!r}")
        key = (binary, target)
        if key in rows:
            raise SystemExit(f"duplicate tuple: {key!r}")
        rows[key] = values
    return rows


def main() -> int:
    if len(sys.argv) != 6:
        return 64
    b_path, mac_path, linux_path, predictor_path, table_path = map(pathlib.Path, sys.argv[1:])
    baseline = parse_cells(b_path, observed=False)
    observed = {}
    observed.update(parse_cells(mac_path, observed=True))
    observed.update(parse_cells(linux_path, observed=True))
    binaries = [
        "biv_subprocess_tests",
        "biv_repo_git_tests",
        "biv_repo_engine_tests",
        "biv_tests",
        "biv_probe_tests",
    ]
    expected_keys = {(binary, target) for target in ("macos", "linux") for binary in binaries}
    if set(baseline) != expected_keys or set(observed) != expected_keys:
        raise SystemExit("baseline/observed key set is not the exact ten-cell set")
    match = re.fullmatch(r"added=(\d+) removed=(\d+)\n?", predictor_path.read_text(encoding="utf-8"))
    if match is None:
        raise SystemExit("malformed predictor")
    added, removed = map(int, match.groups())
    if (added, removed) != (1, 0):
        raise SystemExit(f"predictor mismatch: added={added} removed={removed}")
    predicted_delta = added - removed
    lines = ["binary target old_B_successes observed_P_successes delta new_C_successes"]
    for target in ("macos", "linux"):
        for binary in binaries:
            old = baseline[(binary, target)]
            new = observed[(binary, target)]
            if binary == "biv_tests":
                if new["failures"] != 0 or new["expectedFailures"] != 0:
                    raise SystemExit(f"{target} biv_tests nonzero failure field")
                if new["skips"] != old["skips"]:
                    raise SystemExit(f"{target} biv_tests skip drift")
                delta = new["successes"] - old["successes"]
                if delta == 0:
                    raise SystemExit(f"{target} biv_tests zero successes delta")
                if delta != predicted_delta:
                    raise SystemExit(
                        f"{target} observed successes delta {delta} != predictor {predicted_delta}"
                    )
            else:
                if new != old:
                    raise SystemExit(f"{binary} {target} drift: old={old} observed={new}")
                delta = 0
            lines.append(
                f"{binary} {target} {old['successes']} {new['successes']} {delta} PENDING"
            )
    table_path.write_text("\n".join(lines) + "\n", encoding="utf-8")
    print(f"entry=PASS predictor=PASS added={added} removed={removed}")
    print("observed_delta_macos=1 observed_delta_linux=1")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
