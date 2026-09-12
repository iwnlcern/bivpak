#!/usr/bin/env python3
# usage: witness.py <catch2-xml> red|green   — exit 0 iff the five ROW leaves have exactly the expected outcome
import sys, xml.etree.ElementTree as ET
xml_path, mode = sys.argv[1], sys.argv[2]
NAME = "Claude adapter discovery returns every store found: env and default both searched with codex parity (c1 §7)"
RED_ROWS = {"ROW 1", "ROW 5"} if mode == "red" else set()
root = ET.parse(xml_path).getroot()
cases = [tc for tc in root.iter("TestCase") if tc.get("name") == NAME]
if len(cases) != 1:
    sys.exit(2)  # the named case must appear exactly once
seen = {}
for section in cases[0].findall("Section"):
    label = section.get("name", "").split(":")[0].strip()  # "ROW n"
    if not label.startswith("ROW "):
        continue
    results = section.find("OverallResults")
    if results is None or label in seen:
        sys.exit(3)  # every leaf carries one OverallResults; a leaf appears once
    seen[label] = int(results.get("failures", "-1"))
if set(seen) != {"ROW 1", "ROW 2", "ROW 3", "ROW 4", "ROW 5"}:
    sys.exit(4)  # all five leaves present
for label, failures in sorted(seen.items()):
    expected_red = label in RED_ROWS
    if failures < 0 or (failures > 0) != expected_red:
        sys.exit(5)  # a leaf's outcome differs from the mode's expectation
    print(f"{label} failures={failures} expected={'red' if expected_red else 'green'} ok")
overall = cases[0].find("OverallResult")
if overall is None or (overall.get("success") == "true") != (mode == "green"):
    sys.exit(6)  # the case verdict must agree with the mode
print(f"{mode} verdict ok")
