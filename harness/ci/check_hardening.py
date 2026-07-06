import os
import shutil
import subprocess
import sys
from pathlib import Path


def _run(args):
    return subprocess.run(args, check=False, text=True, capture_output=True)


def main(argv):
    if len(argv) != 2:
        print("usage: check_hardening.py <binary>", file=sys.stderr)
        return 2
    binary = Path(argv[1])
    readelf = shutil.which("readelf")
    if readelf is None:
        print("readelf unavailable", file=sys.stderr)
        return 1
    if not binary.exists():
        print(f"binary missing: {binary}", file=sys.stderr)
        return 1

    header = _run([readelf, "-h", str(binary)])
    program = _run([readelf, "-l", str(binary)])
    dynamic = _run([readelf, "-d", str(binary)])
    symbols = _run([readelf, "-Ws", str(binary)])
    hardening_flags = os.environ.get("BIVHARNESS_HARDENING_FLAGS", "")
    text = "\n".join([header.stdout, program.stdout, dynamic.stdout, symbols.stdout, hardening_flags])

    failures = []
    if "Type:                              DYN" not in header.stdout:
        failures.append("PIE/DYN")
    if "GNU_RELRO" not in program.stdout:
        failures.append("RELRO")
    if "BIND_NOW" not in dynamic.stdout:
        failures.append("BIND_NOW")
    if "__stack_chk_fail" not in symbols.stdout:
        failures.append("__stack_chk_fail")
    if "_FORTIFY_SOURCE" not in hardening_flags and "_chk" not in symbols.stdout:
        failures.append("_FORTIFY_SOURCE")
    if "-fstack-clash-protection" not in hardening_flags:
        failures.append("-fstack-clash-protection")
    if failures:
        print("hardening check failed: " + ", ".join(failures), file=sys.stderr)
        print(text, file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv))
