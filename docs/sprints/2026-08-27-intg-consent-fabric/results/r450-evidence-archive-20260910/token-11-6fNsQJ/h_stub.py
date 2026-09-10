# usage: h_stub.py <harness/selftest/stub_biv.py>  — replaces the claude branch of _discover_model
# with the codex-shaped append (exactly ONE occurrence of the old block, else no write; exit 3).
import sys
from pathlib import Path
target = Path(sys.argv[1])
OLD = (
    '    ccd = env.get("CLAUDE_CONFIG_DIR")\n'
    '    if ccd and Path(ccd).exists():\n'
    '        claude_roots = [("CLAUDE_CONFIG_DIR", Path(ccd))]\n'
    '    elif home and (home / ".claude").exists():\n'
    '        claude_roots = [("HOME", home / ".claude")]\n'
    '    else:\n'
    '        claude_roots = []\n'
)
NEW = (
    '    claude_roots = []\n'
    '    claude_env_root = None\n'
    '    ccd = env.get("CLAUDE_CONFIG_DIR")\n'
    '    if ccd and Path(ccd).exists():\n'
    '        claude_env_root = Path(ccd)\n'
    '        claude_roots.append(("CLAUDE_CONFIG_DIR", claude_env_root))\n'
    '    if home and (home / ".claude").exists() and (\n'
    '        claude_env_root is None\n'
    '        or os.path.normpath(home / ".claude") != os.path.normpath(claude_env_root)\n'
    '    ):\n'
    '        claude_roots.append(("HOME", home / ".claude"))\n'
)
text = target.read_text(encoding="utf-8")
n = text.count(OLD)
if n != 1:
    print(f"REFUSED: old claude branch found {n} times (expected 1); no write", file=sys.stderr)
    sys.exit(3)
target.write_text(text.replace(OLD, NEW, 1), encoding="utf-8")
print(f"stub claude branch replaced: old_lines={OLD.count(chr(10))} new_lines={NEW.count(chr(10))}")
