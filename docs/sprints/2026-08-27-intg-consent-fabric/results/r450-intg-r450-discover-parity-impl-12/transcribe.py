#!/usr/bin/env python3
# usage: transcribe.py <workflow> <macos-biv_tests.xml> <linux-biv_tests.xml>
# Writes the observed biv_tests "successes" cells into lines 85 and 326 of the workflow.
# No arithmetic: the value written IS the XML's OverallResultsCases successes attribute.
import sys, re, xml.etree.ElementTree as ET
workflow, macos_xml, linux_xml = sys.argv[1], sys.argv[2], sys.argv[3]
def observed(path):
    cases = ET.parse(path).getroot().find("OverallResultsCases")
    if cases is None or cases.get("successes") is None:
        sys.exit(2)
    return cases.get("successes")
targets = {85: observed(macos_xml), 326: observed(linux_xml)}
lines = open(workflow, encoding="utf-8").read().split("\n")
for lineno in targets:
    if lines[lineno - 2].strip() != '"biv_tests": {':
        sys.exit(3)  # the anchor line above each cell must be the biv_tests block opener
    m = re.fullmatch(r'(\s+"successes": )(\d+)(,)', lines[lineno - 1])
    if m is None:
        sys.exit(3)
    lines[lineno - 1] = f"{m.group(1)}{targets[lineno]}{m.group(3)}"
open(workflow, "w", encoding="utf-8").write("\n".join(lines))
print("transcribed", targets)
