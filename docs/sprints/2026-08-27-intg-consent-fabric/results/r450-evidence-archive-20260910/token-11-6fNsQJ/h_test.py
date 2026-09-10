# usage: h_test.py <harness/selftest/test_store_isolation.py>  — the HOME mutant test renamed and
# its claude-canary assertion inverted from ABSENCE to PRESENCE (each edit exactly once, else exit 3, no write).
import sys
from pathlib import Path
target = Path(sys.argv[1])
EDITS = [
    (
        "def test_home_restore_exposes_only_the_reachable_codex_canary(\n",
        "def test_home_restore_exposes_both_home_default_canaries(\n",
    ),
    (
        '    assert scenario.POISON_SESSION_IDS["HOME:claude"] not in "\\n".join(\n'
        "        path for _, _, path in entries\n"
        "    )\n",
        '    assert scenario.POISON_SESSION_IDS["HOME:claude"] in "\\n".join(\n'
        "        path for _, _, path in entries\n"
        "    )\n",
    ),
]
text = target.read_text(encoding="utf-8")
for old, new in EDITS:
    n = text.count(old)
    if n != 1:
        print(f"REFUSED: edit anchor found {n} times (expected 1); no write: {old.splitlines()[0]!r}", file=sys.stderr)
        sys.exit(3)
for old, new in EDITS:
    text = text.replace(old, new, 1)
target.write_text(text, encoding="utf-8")
print("test_store_isolation.py: HOME mutant renamed; claude HOME canary asserted PRESENT")
