# usage: h_e3pin.py <harness/bivharness/e3.py> <src/adapters/claude_code/claude_code.cpp>
# Re-pins ONLY the _ADAPTER_SOURCE_ANCHORS["claude_adapter_file"] sha256 literal to the sha256 of the
# given claude_code.cpp bytes. The old literal line must occur exactly once (else exit 3, no write);
# an unchanged digest is refused (exit 4, no write). Prints old= new= for the evidence.
import hashlib
import sys
from pathlib import Path
e3 = Path(sys.argv[1])
cpp = Path(sys.argv[2])
OLD_LINE = '        "cd1f8bc8f7ab87cf15251d84ad7e59c618a22f3c19b9633ff193350782800851",\n'
new_digest = hashlib.sha256(cpp.read_bytes()).hexdigest()
NEW_LINE = f'        "{new_digest}",\n'
text = e3.read_text(encoding="utf-8")
n = text.count(OLD_LINE)
if n != 1:
    print(f"REFUSED: old anchor literal line found {n} times (expected 1); no write", file=sys.stderr)
    sys.exit(3)
if NEW_LINE == OLD_LINE:
    print("REFUSED: digest unchanged — nothing to re-pin; no write", file=sys.stderr)
    sys.exit(4)
e3.write_text(text.replace(OLD_LINE, NEW_LINE, 1), encoding="utf-8")
print(f"old={OLD_LINE.strip().strip(',').strip(chr(34))} new={new_digest}")
