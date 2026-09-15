#!/usr/bin/env python3
# e3pin_r449.py <harness/bivharness/e3.py> <claude_code.cpp> <codex.cpp> — m-3's ONE harness byte for this act (C-2 rule 4, `143638`; R-4.50 arm A
# precedent: the pin moved in m-3's commit H under m-3 byte review): re-pins BOTH `_ADAPTER_SOURCE_ANCHORS` sha256 literals (the S-CP-2 C1 drift
# tripwire, whole-file digests of the two adapter sources) to the digests of the given files — the lane commit C's bytes. Each anchor's
# path line + literal line must occur exactly once (else exit 3, no write); an unchanged digest is refused (exit 4, no write); nothing else is
# touched (the caller proves numstat 2/2 on e3.py). Prints key old= new= for the evidence.
import hashlib, re, sys
from pathlib import Path
e3 = Path(sys.argv[1]); files = {"src/adapters/claude_code/claude_code.cpp": Path(sys.argv[2]), "src/adapters/codex/codex.cpp": Path(sys.argv[3])}
text = e3.read_text(encoding="utf-8"); out = []
for rel, cpp in files.items():
    new = hashlib.sha256(cpp.read_bytes()).hexdigest()
    pat = re.compile(r'(        "' + re.escape(rel) + r'",\n        ")([0-9a-f]{64})(",\n)')
    hits = pat.findall(text)
    if len(hits) != 1:
        print(f"REFUSED: anchor for {rel} found {len(hits)} times (expected 1); no write", file=sys.stderr); sys.exit(3)
    old = hits[0][1]
    if old == new:
        print(f"REFUSED: digest unchanged for {rel}; no write", file=sys.stderr); sys.exit(4)
    text = pat.sub(lambda m: m.group(1) + new + m.group(3), text, count=1)
    out.append(f"{rel} old={old} new={new}")
e3.write_text(text, encoding="utf-8")
print("\n".join(out))
