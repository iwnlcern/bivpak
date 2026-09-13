#!/usr/bin/env python3
# usage: plan_blocks.py extract <plan.md> <name>        — a single BLOCK (the fenced block after `<!-- BLOCK: <name> -->`) byte-for-byte; for <name> = task-N
#                                                          the DERIVED RUNNER: PROLOGUE(N) + the concatenation, in document order, of every fenced block that
#                                                          follows a `<!-- RUN: task-N -->` marker (exit 2: marker absent/duplicated/unterminated, or no RUN block)
#        plan_blocks.py list <plan.md>                  — every BLOCK and every derived task runner, in document order: <name> <sha256> <line-count> [run-blocks=<k>]
#        plan_blocks.py check <plan.md> <N> <runner.sh> — exit 0 iff (i) the runner file == the derived task-N runner BYTE-FOR-BYTE; (ii) every `RUN: task-N`
#                                                          marker lies inside Task N's section and that section holds no RUN marker of another task; (iii) the
#                                                          derived runner opens with PROLOGUE(N); (iv) every GATE span of Task N's prose (a backtick span carrying
#                                                          `|| STOP`, `|| exit`, `; exit 1;` or `exit 0; fi`) is a runner line and the gate spans occur in the runner
#                                                          in the prose's order — the narrative stays bound to the executable text; 5 = a violation (each
#                                                          printed); 2 = a missing input. The last line printed is always rc=<n>.
import hashlib, re, sys
GATE = ("|| STOP", "|| exit", "; exit 1;", "exit 0; fi")
PROLOGUE = """#!/usr/bin/env bash
# task-@N@.sh — materialized VERBATIM from the plan's BLOCK task-@N@ by plan_blocks.py extract; proved by plan_blocks.py check; invoked by run-task.sh @N@
set -u
STOP() { printf 'STOP-task-@N@ line=%s\\n' "${BASH_LINENO[0]}" >&2; exit 1; }
RUNNERS=${1-}; [ -n "$RUNNERS" ] && [ -d "$RUNNERS" ] || exit 1
[ "$0" = "$RUNNERS/task-@N@.sh" ] || { printf 'STOP-task-@N@-invoked-off-path %s\\n' "$0" >&2; exit 1; }
t=0; tail -n 1 "$RUNNERS/proof-@N@.txt" > "$RUNNERS/task-@N@.proof-tail" 2>/dev/null || t=$?; [ "$t" -eq 0 ] && [ "$(cat "$RUNNERS/task-@N@.proof-tail")" = rc=0 ] || { printf 'STOP-task-@N@-unproved\\n' >&2; exit 1; }
h=0; shasum -a 256 "$0" > "$RUNNERS/task-@N@.self.sha256" || h=$?; [ "$h" -eq 0 ] && [ -s "$RUNNERS/task-@N@.self.sha256" ] || exit 1
a=$(cut -d' ' -f1 "$RUNNERS/task-@N@.self.sha256") || exit 1; b=$(cut -d' ' -f1 "$RUNNERS/task-@N@.sha256") || exit 1; [ -n "$a" ] && [ "$a" = "$b" ] || { printf 'STOP-task-@N@-bytes-differ\\n' >&2; exit 1; }
"""
PROLOGUE_EVID = """EVID=${2-}; [ -n "$EVID" ] && [ -d "$EVID" ] || exit 1; [ "$EVID" = "$(cat "$RUNNERS/evid.txt")" ] || exit 1
c=0; cp -p "$RUNNERS/task-@N@.sh" "$RUNNERS/proof-@N@.txt" "$RUNNERS/task-@N@.sha256" "$RUNNERS/task-@N@.invocation.txt" "$EVID/runners/" || c=$?; [ "$c" -eq 0 ] || exit 1
"""
def prologue(n):
    p = PROLOGUE + ("" if n == "0" else PROLOGUE_EVID)
    return p.replace("@N@", n)
def read(plan):
    return open(plan, encoding="utf-8").read()
def fenced(lines, i):
    # lines[i] is a marker line; the fence opens on the next line and closes on a line that is exactly ```
    if i + 1 >= len(lines) or not lines[i + 1].startswith("```"):
        sys.exit(2)
    j = i + 2
    body = []
    while j < len(lines) and lines[j] != "```":
        body.append(lines[j])
        j += 1
    if j >= len(lines):
        sys.exit(2)
    return "\n".join(body) + "\n", j
def scan(text):
    """returns (blocks: name -> body, runs: list of (task, line_index, body)) in document order"""
    lines = text.split("\n")
    blocks, runs = {}, []
    i = 0
    while i < len(lines):
        m = re.match(r"^<!-- BLOCK: ([A-Za-z0-9_.-]+) -->$", lines[i])
        r = re.match(r"^<!-- RUN: task-([0-9]) -->$", lines[i])
        if m:
            name = m.group(1)
            if name in blocks or re.match(r"^task-[0-9]$", name):
                sys.exit(2)
            body, j = fenced(lines, i)
            blocks[name] = body
            i = j
        elif r:
            body, j = fenced(lines, i)
            runs.append((r.group(1), i, body))
            i = j
        i += 1
    return blocks, runs
def section_bounds(text, n):
    """(start_line, end_line) of Task N's section as line indexes, or None"""
    lines = text.split("\n")
    start = None
    for i, ln in enumerate(lines):
        if start is None and re.match(r"^### Task %s —" % re.escape(n), ln):
            start = i
        elif start is not None and (ln.startswith("### Task ") or ln.startswith("## ")):
            return start, i
    return (start, len(lines)) if start is not None else None
def derived(text, n, runs=None):
    if runs is None:
        runs = scan(text)[1]
    mine = [body for task, _, body in runs if task == n]
    if not mine:
        sys.exit(2)
    return prologue(n) + "".join(mine)
def spans(sec):
    return re.findall(r"`([^`\n]+)`", sec)
def extract(plan, name):
    text = read(plan)
    m = re.match(r"^task-([0-9])$", name)
    if m:
        sys.stdout.write(derived(text, m.group(1)))
        return 0
    blocks, _ = scan(text)
    if name not in blocks:
        sys.exit(2)
    sys.stdout.write(blocks[name])
    return 0
def listing(plan):
    text = read(plan)
    blocks, runs = scan(text)
    for name, body in blocks.items():
        print("%s %s %d" % (name, hashlib.sha256(body.encode("utf-8")).hexdigest(), body.count("\n")))
    for n in "0123456789":
        k = sum(1 for task, _, _ in runs if task == n)
        if k:
            body = derived(text, n, runs)
            print("task-%s %s %d run-blocks=%d" % (n, hashlib.sha256(body.encode("utf-8")).hexdigest(), body.count("\n"), k))
    return 0
def check(plan, n, runner):
    text = read(plan)
    blocks, runs = scan(text)
    b = section_bounds(text, n)
    if b is None or not any(task == n for task, _, _ in runs):
        sys.exit(2)
    try:
        run = open(runner, encoding="utf-8").read()
    except OSError:
        sys.exit(2)
    rc = 0
    blk = derived(text, n, runs)
    if run != blk:
        rl, bl = run.split("\n"), blk.split("\n")
        k = next((i for i in range(min(len(rl), len(bl))) if rl[i] != bl[i]), min(len(rl), len(bl)))
        print("BYTES-DIFFER at runner line %d (runner %d lines, derived %d lines)" % (k + 1, len(rl), len(bl)))
        rc = 5
    placed = 0
    for task, li, _ in runs:
        inside = b[0] <= li < b[1]
        if task == n and not inside:
            print("RUN-BLOCK-OUTSIDE-SECTION: RUN task-%s at line %d is outside Task %s's section" % (task, li + 1, n))
            rc = 5
        if task != n and inside:
            print("FOREIGN-RUN-BLOCK: RUN task-%s at line %d inside Task %s's section" % (task, li + 1, n))
            rc = 5
        if task == n and inside:
            placed += 1
    pro = prologue(n)
    if not blk.startswith(pro):
        print("PROLOGUE-MISMATCH")
        rc = 5
    sec_lines = text.split("\n")[b[0]:b[1]]
    sec = "\n".join(sec_lines)
    sp = spans(sec)
    gates = [s for s in sp if any(g in s for g in GATE)]
    lines = blk.split("\n")
    pos = {}
    for i, ln in enumerate(lines):
        pos.setdefault(ln, []).append(i)
    last = -1
    omitted = 0
    order = 0
    for s in gates:
        idx = [i for i in pos.get(s, []) if i >= last]
        if s not in pos:
            print("OMITTED gate span: %s" % s)
            omitted += 1
            rc = 5
        elif not idx:
            print("OUT-OF-ORDER gate span (runner lines %s, after %d): %s" % (",".join(str(i + 1) for i in pos[s]), last + 1, s))
            order += 1
            rc = 5
        else:
            last = idx[0]
    print("bytes=%s run_blocks=%d prologue=%s lines=%d spans=%d gates=%d omitted=%d out_of_order=%d" % (
        "equal" if run == blk else "differ", placed, "ok" if blk.startswith(pro) else "mismatch", len(lines) - 1, len(sp), len(gates), omitted, order))
    print("rc=%d" % rc)
    return rc
if __name__ == "__main__":
    if len(sys.argv) == 4 and sys.argv[1] == "extract":
        sys.exit(extract(sys.argv[2], sys.argv[3]))
    if len(sys.argv) == 3 and sys.argv[1] == "list":
        sys.exit(listing(sys.argv[2]))
    if len(sys.argv) == 5 and sys.argv[1] == "check":
        sys.exit(check(sys.argv[2], sys.argv[3], sys.argv[4]))
    sys.exit(2)
