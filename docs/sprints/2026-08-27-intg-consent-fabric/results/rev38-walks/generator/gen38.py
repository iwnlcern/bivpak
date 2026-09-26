#!/usr/bin/env python3
# gen38.py <rev37.md> <hist38.md> <out rev38.md> — MUST-2B-52 folded; every edit exact and asserted once
import sys
src = open(sys.argv[1], encoding="utf-8").read()
def rep(old, new, n=1):
    global src
    k = src.count(old)
    if k != n: sys.exit("count %d != %d for: %s" % (k, n, old[:100]))
    src = src.replace(old, new)
# runner (task-9 RUN body; each string occurs once in the plan, inside it)
rep('for x in series H9; do [ ! -e "$EVID/$x" ] && [ ! -L "$EVID/$x" ] || STOP; done\n[ -d "$EVID/B" ] && [ ! -L "$EVID/B" ] && [ -d "$EVID/work" ] && [ ! -L "$EVID/work" ] || STOP\n',
    'for x in series H9 H.txt commits.c9.txt; do [ ! -e "$EVID/$x" ] && [ ! -L "$EVID/$x" ] || STOP; done\n[ -d "$EVID/B" ] && [ ! -L "$EVID/B" ] && [ -d "$EVID/work" ] && [ ! -L "$EVID/work" ] || STOP\n'
    '# rev38 (MUST-2B-52): CONFINEMENT before the first write — work/ and B/ physically the home\'s own, and no symlink directly under the home, work/ or B/, so no fixed name this runner writes with > can be redirected (H/, H9/ and series/ are made fresh)\n'
    'p=0; RH=$(cd "$EVID" && pwd -P) || p=$?; [ "$p" -eq 0 ] && [ -n "$RH" ] && [ "$(cd "$EVID/work" && pwd -P)" = "$RH/work" ] && [ "$(cd "$EVID/B" && pwd -P)" = "$RH/B" ] || STOP\n'
    'f=0; LNK=$(find "$EVID" "$EVID/work" "$EVID/B" -maxdepth 1 -type l) || f=$?; [ "$f" -eq 0 ] && [ -z "$LNK" ] || STOP\n')
rep('V37S=$EVID/work/series_verdict.rev37.stage; x=0; python3 "$RUNNERS/plan_blocks.py" extract "$PLANP" series_verdict.py > "$V37S" || x=$?; [ "$x" -eq 0 ] && [ -s "$V37S" ] || STOP\n',
    'V37S=$(mktemp "$EVID/work/series_verdict.rev37.XXXXXX") || STOP; [ -f "$V37S" ] && [ ! -L "$V37S" ] && [ ! -s "$V37S" ] || STOP; x=0; python3 "$RUNNERS/plan_blocks.py" extract "$PLANP" series_verdict.py > "$V37S" || x=$?; [ "$x" -eq 0 ] && [ -f "$V37S" ] && [ ! -L "$V37S" ] && [ -s "$V37S" ] || STOP\n')
rep("from THIS plan's block only when absent (staged in work/, digest-checked, then renamed into place), digest-pinned either way\n",
    "from THIS plan's block only when absent (rev38: a fresh `mktemp` stage in the confined work/ — never a fixed name, so an earlier failed stage is kept, not truncated — checked regular before and after the extract, digest-checked, then renamed into place), digest-pinned either way\n")
# prose
rep("the corrected block is produced at `$EVID/series_verdict.rev37.py` when absent and pinned by digest either way, and the series calls it);",
    "the corrected block is produced at `$EVID/series_verdict.rev37.py` when absent — rev38: through a fresh `mktemp` stage in the confined `work/`, regular before and after the extract — and pinned by digest either way, and the series calls it);")
rep("An earlier attempt's `series/` or `H9/` is a STOP too (none exists in this home).",
    "An earlier attempt's `series/`, `H9/`, `H.txt` or `commits.c9.txt` is a STOP too (rev38: the two names joined; none exists in this home). rev38 (MUST-2B-52): before the first write the runner proves `work/` and `B/` physically the home's own and finds NO symlink directly under the home, `work/` or `B/`, so no fixed name it writes with `>` can be redirected outside the home.")
rep("## Revision history\n\n", "## Revision history\n\n" + open(sys.argv[2], encoding="utf-8").read().rstrip("\n") + "\n")
open(sys.argv[3], "w", encoding="utf-8").write(src)
print("ok")
