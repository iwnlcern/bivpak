#!/usr/bin/env python3
# selftest_summary.py — the pytest facts of the `harness-selftest` ctest row, read from CTest's JUnit output (rev18; iso rev13 bar).
#   usage: selftest_summary.py <ctest junit xml> <out prefix>
#   writes <prefix>.kv    one `key=value` per line: status=<run|fail|notrun|absent> summary=<parsed|absent> failed=<n> passed=<m>
#                         skipped=<k> population=<n+m+k> names_count=<c>
#          <prefix>.names one failing test per line as `<path>::<name>` (pytest's `FAILED <path>::<name>` short-summary lines, every file), sorted, unique
#   The summary line is pytest's final `==== N failed, M passed, K skipped in T s ====` line (the LAST such line in the testcase's
#   system-out); `summary=parsed` iff that line exists and carries a `passed` count; `failed`/`skipped` default to 0 when absent from it.
#   exit 0 when the XML parsed and the testcase exists (the bar decides on the fields); 2 on a missing/unparseable file or an absent testcase.
import re, sys, xml.etree.ElementTree as ET
def main(argv):
    if len(argv) != 3:
        print("usage: selftest_summary.py <junit.xml> <out-prefix>")
        return 2
    try:
        root = ET.parse(argv[1]).getroot()
    except Exception as e:
        print("BAD-JUNIT: %s" % e)
        return 2
    tc = next((t for t in root.iter("testcase") if t.get("name") == "harness-selftest"), None)
    if tc is None:
        print("TESTCASE-ABSENT: harness-selftest")
        return 2
    so = tc.find("system-out")
    txt = (so.text or "") if so is not None else ""
    status = tc.get("status") or "absent"
    if tc.find("failure") is not None:
        status = "fail"
    lines = [ln for ln in txt.split("\n") if re.match(r"^=+ .* in [0-9.]+s( \([0-9:]+\))? =+\s*$", ln)]
    summary = lines[-1] if lines else ""
    def count(word):
        m = re.search(r"(\d+) " + word + r"\b", summary)
        return int(m.group(1)) if m else 0
    parsed = bool(summary) and re.search(r"\d+ passed\b", summary) is not None
    failed, passed, skipped = (count("failed"), count("passed"), count("skipped")) if parsed else (0, 0, 0)
    names = sorted(set(re.findall(r"^FAILED (\S+::[A-Za-z0-9_\[\]\-]+)", txt, re.M)))  # QUALIFIED path::name, every file — a failure outside test_e3_asserts.py is a name the bar must see
    kv = "status=%s\nsummary=%s\nfailed=%d\npassed=%d\nskipped=%d\npopulation=%d\nnames_count=%d\n" % (
        status, "parsed" if parsed else "absent", failed, passed, skipped, failed + passed + skipped, len(names))
    with open(argv[2] + ".kv", "w", encoding="utf-8") as f:
        f.write(kv)
    with open(argv[2] + ".names", "w", encoding="utf-8") as f:
        f.write("".join(n + "\n" for n in names))
    sys.stdout.write(kv.replace("\n", " ").strip() + "\n")
    return 0
if __name__ == "__main__":
    sys.exit(main(sys.argv))
