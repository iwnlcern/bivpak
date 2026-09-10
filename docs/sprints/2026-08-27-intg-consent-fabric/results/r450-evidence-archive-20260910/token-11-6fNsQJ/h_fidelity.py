# usage: <venv python> h_fidelity.py <harness/selftest dir>  — L1 fidelity: the stub's _discover_model
# claude branch reproduces C's discover on the five witness rows (store TAG sets, env first).
# exit 0 iff every row matches; each row printed as `ROW n: observed=[...] expected=[...] ok|MISMATCH`.
import os
import sys
import tempfile
from pathlib import Path
sys.path.insert(0, sys.argv[1])
import stub_biv  # noqa: E402

def plant(root):
    (root / "projects" / "p").mkdir(parents=True)
    (root / "projects" / "p" / "s.jsonl").write_text("{}\n", encoding="utf-8")

def tags(env):
    seen = []
    for tag, _ in stub_biv._discover_model(env):
        if tag not in seen:
            seen.append(tag)
    return seen

rows = []
with tempfile.TemporaryDirectory() as tmp:
    t = Path(tmp)
    home = t / "home"; env_store = t / "env-store"
    plant(home / ".claude"); plant(env_store)
    rows.append(("ROW 1 env set, exists, differs; default exists", {"HOME": str(home), "CLAUDE_CONFIG_DIR": str(env_store)}, ["CLAUDE_CONFIG_DIR", "HOME"]))
    rows.append(("ROW 2 env set and equal to the default", {"HOME": str(home), "CLAUDE_CONFIG_DIR": str(home / ".claude")}, ["CLAUDE_CONFIG_DIR"]))
    rows.append(("ROW 3 env unset, default exists", {"HOME": str(home)}, ["HOME"]))
    home2 = t / "home2"; home2.mkdir()
    rows.append(("ROW 4 neither", {"HOME": str(home2)}, []))
    rows.append(("ROW 5 env set, default exists, both hold sessions (enumeration only)", {"HOME": str(home), "CLAUDE_CONFIG_DIR": str(env_store)}, ["CLAUDE_CONFIG_DIR", "HOME"]))
    bad = 0
    for name, env, expected in rows:
        observed = tags(env)
        ok = observed == expected
        bad += 0 if ok else 1
        print(f"{name}: observed={observed} expected={expected} {'ok' if ok else 'MISMATCH'}")
sys.exit(0 if bad == 0 else 5)
