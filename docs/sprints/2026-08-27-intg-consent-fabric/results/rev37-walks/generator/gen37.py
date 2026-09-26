#!/usr/bin/env python3
# gen37.py <rev36.md> <plan_blocks.py> <hist37.md> <out rev37.md> — m-4's K3_TIE strict (151817, carried by master 154632) folded; every edit exact and asserted once
import sys, hashlib, subprocess
src = open(sys.argv[1], encoding="utf-8").read(); PB = sys.argv[2]
def rep(old, new, n=1):
    global src
    k = src.count(old)
    if k != n: sys.exit("count %d != %d for: %s" % (k, n, old[:100]))
    src = src.replace(old, new)
def extract(text, name):
    tmp = sys.argv[4] + ".tmp"; open(tmp, "w", encoding="utf-8").write(text)
    return subprocess.run([sys.executable, PB, "extract", tmp, name], capture_output=True, check=True, text=True).stdout
t9_old = extract(src, "task-9")
# 1. the block: code and its K-3 comment
rep("shifted = (hmean - bmean) >= 1.0 or min(hc) >= max(bc)", "shifted = (hmean - bmean) >= 1.0 or min(hc) > max(bc)")
rep("SHIFTED iff (landed mean - base mean) >= 1.0 OR landed min >= base max (complete separation);", "SHIFTED iff (landed mean - base mean) >= 1.0 OR landed min > base max (complete separation);")
blk = extract(src, "series_verdict.py"); BD = hashlib.sha256(blk.encode("utf-8")).hexdigest()
# 2. the description line
rep("K-3 — SHIFTED iff (landed mean − base mean) ≥ 1.0 OR landed min ≥ base max;", "K-3 — SHIFTED iff (landed mean − base mean) ≥ 1.0 OR landed min > base max (rev37: strict — m-4's `K3_TIE: strict`, `master/relays/intg-2b-wiring-act/DESIGN-planner-20260925-151817.md`, carried by master's `…/PLAN-master-planner-20260925-154632.md`; on integer counts the strict arm implies delta ≥ 1.0; Task 9 runs the corrected block from `$EVID/series_verdict.rev37.py`, produced beside Task 0's copy, which stays byte-unchanged as Task 0's record);")
# 3. the runner: produce the corrected reducer beside Task 0's copy, pinned; the series calls it
cut = "# Runner plumbing (Task 9)\n"
body_old = t9_old[t9_old.index(cut):]
anchor = "o=0; of=$(shasum -a 256 \"$EVID/observer-unset-names.txt\" | cut -d' ' -f1) || o=$?; [ \"$o\" -eq 0 ] && [ \"$of\" = e12d5d0af265ea8faf41dadc1e3af02610365ac25c40a228714b0e72f2a612f3 ] || STOP\n"
assert body_old.count(anchor) == 1
prod = ("# rev37 (m-4 151817 K3_TIE strict; master 154632): the corrected series reducer, produced beside Task 0's `series_verdict.py` (never overwritten) from THIS plan's block only when absent (staged in work/, digest-checked, then renamed into place), digest-pinned either way\n"
 "V37=$EVID/series_verdict.rev37.py\n"
 "if [ ! -e \"$V37\" ] && [ ! -L \"$V37\" ]; then\n"
 "PLANP=$(cat \"$RUNNERS/plan-path.txt\") || STOP; [ -s \"$PLANP\" ] || STOP; V37S=$EVID/work/series_verdict.rev37.stage; x=0; python3 \"$RUNNERS/plan_blocks.py\" extract \"$PLANP\" series_verdict.py > \"$V37S\" || x=$?; [ \"$x\" -eq 0 ] && [ -s \"$V37S\" ] || STOP\n"
 "m=0; vs=$(shasum -a 256 \"$V37S\" | cut -d' ' -f1) || m=$?; [ \"$m\" -eq 0 ] && [ \"$vs\" = " + BD + " ] || STOP\n"
 "[ ! -e \"$V37\" ] && [ ! -L \"$V37\" ] || STOP; v=0; mv \"$V37S\" \"$V37\" || v=$?; [ \"$v\" -eq 0 ] || STOP\n"
 "fi\n"
 "[ -f \"$V37\" ] && [ ! -L \"$V37\" ] || STOP\n"
 "m=0; vs=$(shasum -a 256 \"$V37\" | cut -d' ' -f1) || m=$?; [ \"$m\" -eq 0 ] && [ \"$vs\" = " + BD + " ] || STOP\n"
 "p=0; python3 -m py_compile \"$V37\" || p=$?; [ \"$p\" -eq 0 ] || STOP\n")
body_new = body_old.replace(anchor, anchor + prod, 1)
old_call = "  s=0; python3 \"$EVID/series_verdict.py\" \"$EVID/series\" \"$EVID/H/r435-family.txt\" 10 > \"$EVID/H/selftest-series.txt\" 2>&1 || s=$?;"
assert body_new.count(old_call) == 1
body_new = body_new.replace(old_call, "  s=0; python3 \"$V37\" \"$EVID/series\" \"$EVID/H/r435-family.txt\" 10 > \"$EVID/H/selftest-series.txt\" 2>&1 || s=$?;", 1)
rep("<!-- RUN: task-9 -->\n```bash\n" + body_old, "<!-- RUN: task-9 -->\n```bash\n" + body_new)
# 4. Task 9 Step 4 prose and the instruments line
rep("K-3 shift = mean delta ≥ 1.0 OR complete separation;", "K-3 shift = mean delta ≥ 1.0 OR complete separation, strictly `landed min > base max` (rev37, m-4's `K3_TIE: strict`; the corrected block is produced at `$EVID/series_verdict.rev37.py` when absent and pinned by digest either way, and the series calls it);")
open(sys.argv[4], "w", encoding="utf-8").write(src)
src2 = src
rep("## Revision history\n\n", "## Revision history\n\n" + open(sys.argv[3], encoding="utf-8").read().replace("@BD@", BD).rstrip("\n") + "\n")
open(sys.argv[4], "w", encoding="utf-8").write(src)
import os; os.remove(sys.argv[4] + ".tmp")
print("block", BD)
