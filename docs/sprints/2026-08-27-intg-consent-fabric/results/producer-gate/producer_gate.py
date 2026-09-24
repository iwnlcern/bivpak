# usage: producer_gate2.py <plan.md> <plan_blocks.py> — every literal "$EVID/<p>" / "$RUNNERS/<p>" READ in the RUN tasks
# (0, 9, 10, 11 in execution order) must have an EARLIER write of <p> or of a parent directory created and populated
# earlier (never counted: a read needs the file itself). A WRITE occurrence is a target of > / >> / tee / --output-junit /
# mkdir / mktemp, or the LAST path operand of cp / mv. Everything else is a READ. Absence tests ([ ! -e ]) read nothing.
# Named exceptions (ALLOW) are printed on every run. Exit 0 = no orphan; 1 = orphans printed.
import re, subprocess, sys
plan, pb = sys.argv[1], sys.argv[2]
def ext(name):
    return subprocess.run([sys.executable, pb, 'extract', plan, name], capture_output=True, check=True, text=True).stdout
runtask = ext('run-task.sh')
OCC = re.compile(r'"?\$\{?(EVID|RUNNERS)\}?/([A-Za-z0-9_.\-/]+)"?')
ALLOW = {
    ('EVID', 'helpers.sha256'): 'task-0 writes it relative inside cd "$EVID"',
    ('RUNNERS', 'task-10-go.txt'): 'the pair Planner GO relay — an external input the controller requires by design',
    ('EVID', 'runners/task-10.done'): 'run-task.sh copies task-N.done into "$EVID/runners/" after rc 0',
    ('EVID', 'census-raw/H0/population-H0.txt'): 'census_population.sh writes its OUT_POP argument',
}
def classify(ln, m):
    pre = ln[:m.start()].rstrip()
    if re.search(r'(>>?|tee(?: -a)?|--output-junit|mkdir(?: -p)?|mktemp -d|--dir|worktree add(?: --detach)?|clone[^;|&]*)$', pre):
        return 'W'
    if re.search(r'\[ ! -e$', pre):
        return 'N'
    # cp / mv: the last path operand of the command segment is the target
    seg_start = max(pre.rfind(';'), pre.rfind('&&'), pre.rfind('||'), pre.rfind('('), pre.rfind('{'))
    seg = ln[seg_start + 1:]
    cm = re.match(r'\s*(?:[a-z]=0;\s*)?(cp|mv)\b', seg)
    if cm:
        end = re.search(r'\|\||&&|;|\)|$', seg[cm.end():])
        body = seg[cm.end():cm.end() + end.start()]
        ops = OCC.findall(body)
        if ops and ops[-1] == (m.group(1), m.group(2)) and body.rstrip().endswith(m.group(0).rstrip()):
            return 'W'
    return 'R'
written = set()
LOOPVARS = {'LABEL': ['H', 'B'], 'N': ['0', '9', '10', '11'], 'T': ['H', 'B']}
def expand(p, ln):
    # expand $var / ${var} using a same-line `for var in a b c; do` or the fixed LOOPVARS
    out = [p]
    for var in re.findall(r'\$\{?([A-Za-z_]+)\}?', p):
        m = re.search(r'for ' + var + r' in ([^;]+); do', ln)
        vals = m.group(1).split() if m else LOOPVARS.get(var)
        if not vals:
            return []
        out = [re.sub(r'\$\{?' + var + r'\}?', v, q) for q in out for v in vals]
    return out
def harvest(text, roots_map):
    # every write occurrence in `text`, with loop/label expansion; roots_map maps a foreign root to (EVID, prefix)
    for ln in text.split('\n'):
        if ln.lstrip().startswith('#'):
            continue
        for m in re.finditer(r'"?\$\{?(EVID|RUNNERS|OUT)\}?/([A-Za-z0-9_.\-/${}]+)"?', ln):
            if classify(ln, m) != 'W':
                continue
            root, p = m.group(1), m.group(2).rstrip('/')
            for q in expand(p, ln):
                if root == 'OUT':
                    for lab in ('H', 'B'):
                        written.add(('EVID', lab + '/' + q))
                else:
                    written.add((root, q))
for (r, p) in re.findall(r'\$(EVID|RUNNERS)/([A-Za-z0-9_.\-/]+)', ''):
    pass
import itertools
text = open(plan, encoding='utf-8').read()
harvest(runtask, None)
harvest(ext('linux-suite.sh') + ext('linux-container.sh'), None)
t9 = text.index('### Task 9')
t1 = text.index('### Task 1')
harvest(text[t1:t9], None)   # the code tasks' steps, executed before Task 9
BASE = {}
for bl in open(sys.argv[3], encoding='utf-8'):
    if bl.strip():
        key, why = bl.rstrip('\n').split('\t', 1); r, q = key.split(' ', 1); BASE[(r, q)] = why
classified = set()
orph = 0
seen_allow = set()
for n in ('0', '9', '10', '11'):
    lines = ext('task-' + n).split('\n')
    for i, ln in enumerate(lines):
        if ln.lstrip().startswith('#'):
            continue
        harvest(ln, None)
        for m in OCC.finditer(ln):
            root, p = m.group(1), m.group(2).rstrip('/')
            if '$' in p or not p or ln[m.end(2):m.end(2) + 1] == '$':
                continue  # templated: the name continues with a variable
            k = classify(ln, m)
            if k == 'W':
                continue
            if k == 'N':
                continue
            if (root, p) in written:
                continue
            if (root, p) in ALLOW:
                if (root, p) not in seen_allow:
                    print('ALLOWED $%s/%s <- %s' % (root, p, ALLOW[(root, p)])); seen_allow.add((root, p))
                continue
            if (root, p) in BASE:
                classified.add((root, p)); written.add((root, p)); continue
            print('ORPHAN task-%s line %d: $%s/%s' % (n, i + 1, root, p)); orph += 1
            written.add((root, p))  # report each path once
stale = sorted(set(BASE) - classified)
for r, q in stale:
    print('STALE-BASELINE $%s/%s (classified but no longer read without a writer)' % (r, q))
print('orphans=%d classified=%d stale=%d' % (orph, len(classified), len(stale)))
orph += len(stale)
sys.exit(1 if orph else 0)
