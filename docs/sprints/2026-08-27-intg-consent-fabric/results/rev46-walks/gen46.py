import hashlib, subprocess, sys
P = 'docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep2b-20260915.md'
src = subprocess.run(['git', 'show', '31a6123:' + P], capture_output=True, check=True).stdout.decode('utf-8')
assert hashlib.sha256(src.encode()).hexdigest() == 'bd2d21f5c2e5681b2608414139c754bd3b8933889518d0223424c9e46c85bfe6'
t = src
def rep(a, b, n=1):
    global t
    c = t.count(a); assert c == n, (c, a[:100]); t = t.replace(a, b)
# ---- resume.sh: Task 10's receipts carried once Task 10 is done (Task 11's controller requires task-10.done in the directory it runs from)
rep("# resume.sh — protocol step 0': bind a NEW runners directory to a LATER token (new PLAN_LOCK digest, new DISPATCH_ID, the SAME evidence home) while carrying Task 0's receipts, Task 9's once Task 9 is done (rev39), and every gate file;",
    "# resume.sh — protocol step 0': bind a NEW runners directory to a LATER token (new PLAN_LOCK digest, new DISPATCH_ID, the SAME evidence home) while carrying Task 0's receipts, Task 9's once Task 9 is done (rev39), Task 10's once Task 10 is done (rev46), and every gate file;")
rep('  for f in task-9.proof-tail task-9.self.sha256 plan-hash-9.txt; do [ -s "$OLD/$f" ] || STOP "receipt-absent-$f"; done\nfi\n',
    '  for f in task-9.proof-tail task-9.self.sha256 plan-hash-9.txt; do [ -s "$OLD/$f" ] || STOP "receipt-absent-$f"; done\nfi\n'
    '# rev46: once Task 10 is done in the previous directory its receipts are carried too (Task 11\'s controller requires task-10.done in the directory it runs from; without them a resumed directory STOPs at the controller\'s predecessor check); bound exactly as Task 9\'s: the controller\'s copies in $EVID/runners/, the runner\'s own digest, and the prologue records of the ONE token that ran it, found by content\n'
    'T10=0; if [ -e "$OLD/task-10.done" ] || [ -L "$OLD/task-10.done" ]; then T10=1; [ "$T9" -eq 1 ] || STOP task-10-without-task-9; [ -f "$OLD/task-10.done" ] && [ ! -L "$OLD/task-10.done" ] && [ "$(cat "$OLD/task-10.done")" = rc=0 ] || STOP task-10-not-done\n'
    '  for f in task-10.done task-10.exit proof-10.tail plan_blocks.sha256-10; do c=0; cmp "$OLD/$f" "$EVID/runners/$f" >&2 || c=$?; [ "$c" -eq 0 ] || STOP "task-10-copy-mismatch-$f"; done\n'
    '  h=0; s=$(shasum -a 256 "$OLD/task-10.sh" | cut -d\' \' -f1) || h=$?; r=$(cut -d\' \' -f1 "$OLD/task-10.sha256") || STOP task-10-sha-read; [ "$h" -eq 0 ] && [ -n "$r" ] && [ "$s" = "$r" ] || STOP task-10-sh-altered\n'
    '  n=0; for td in "$EVID"/runners/intg-substep2b-impl-*/task-10; do [ -d "$td" ] && [ ! -L "$td" ] || continue; m=1; for f in task-10.sh proof-10.txt task-10.sha256 task-10.invocation.txt; do cmp -s "$OLD/$f" "$td/$f" || m=0; done; [ "$m" -eq 0 ] || n=$((n + 1)); done\n'
    '  [ "$n" -eq 1 ] || STOP "task-10-record-owner-$n"\n'
    '  for f in task-10.proof-tail task-10.self.sha256 plan-hash-10.txt; do [ -s "$OLD/$f" ] || STOP "receipt-absent-$f"; done\n'
    'fi\n')
rep('proof-9.tail; do c=0; cp -p "$OLD/$f" "$NEW/$f" || c=$?; [ "$c" -eq 0 ] && [ -s "$NEW/$f" ] || STOP "carry-$f"; c=0; cmp "$OLD/$f" "$NEW/$f" || c=$?; [ "$c" -eq 0 ] || STOP "carry-cmp-$f"; CARRIED="$CARRIED $f"; done; fi\n',
    'proof-9.tail; do c=0; cp -p "$OLD/$f" "$NEW/$f" || c=$?; [ "$c" -eq 0 ] && [ -s "$NEW/$f" ] || STOP "carry-$f"; c=0; cmp "$OLD/$f" "$NEW/$f" || c=$?; [ "$c" -eq 0 ] || STOP "carry-cmp-$f"; CARRIED="$CARRIED $f"; done; fi\n'
    'if [ "$T10" -eq 1 ]; then for f in task-10.sh proof-10.txt task-10.sha256 task-10.invocation.txt task-10.exit task-10.done task-10.proof-tail task-10.self.sha256 plan-hash-10.txt plan_blocks.sha256-10 proof-10.tail; do c=0; cp -p "$OLD/$f" "$NEW/$f" || c=$?; [ "$c" -eq 0 ] && [ -s "$NEW/$f" ] || STOP "carry-$f"; c=0; cmp "$OLD/$f" "$NEW/$f" || c=$?; [ "$c" -eq 0 ] || STOP "carry-cmp-$f"; CARRIED="$CARRIED $f"; done; fi\n')
# ---- prose
rep("the fold accepted by master 175324; rev39: Task 9's receipts carried once Task 9 is done).**",
    "the fold accepted by master 175324; rev39: Task 9's receipts carried once Task 9 is done; rev46: Task 10's likewise).**")
rep("and all eleven Task 9 receipts are carried, so Task 10's controller finds `task-9.done` and Task 9 can never re-run under a later token.",
    "and all eleven Task 9 receipts are carried, so Task 10's controller finds `task-9.done` and Task 9 can never re-run under a later token. rev46: the same, for Task 10, once `task-10.done` is present (and only beside a carried Task 9): it must read `rc=0`; `task-10.done`, `task-10.exit`, `proof-10.tail` and `plan_blocks.sha256-10` must equal the controller's copies in `$EVID/runners/`; `task-10.sh` must re-hash to `task-10.sha256`; the runner, its proof, digest and invocation must equal the prologue records of exactly ONE token (`$EVID/runners/<that token>/task-10/`; impl-15's failed attempt's records differ and do not count); and all eleven Task 10 receipts are carried, so Task 11's controller finds `task-10.done` (its predecessor check, controller line 16) and Task 10 can never re-run under a later token.")
H46 = ("- rev46 (2026-09-28): `resume.sh` and the Step 0′ prose only. The pair Planner's walk of the NEXT token's handoff (Step 0′ from a mirror of the real `s2b-runners-V1jS1t` on the rev45 lock, then the sealed controller `run-task.sh 11` from the new directory) STOPped `STOP-controller-task-11 line=16`: the controller requires `task-10.done` rc=0 in the directory it runs from, and `resume.sh` carried Task 0's and Task 9's receipts but never Task 10's, so every resumed directory orphaned Task 11. "
       "rev45 walked Step 0′ and the Task 11 body separately and never the controller between them. `resume.sh` now binds and carries Task 10's eleven receipts exactly as rev39 did Task 9's (the controller's copies, the runner's digest, the one owning token's prologue records by content), only beside a carried Task 9.\n")
rep("- rev45 (2026-09-27): Task 11 and the `census_population.sh` BLOCK only.", H46 + "- rev45 (2026-09-27): Task 11 and the `census_population.sh` BLOCK only.")
sys.stdout.write(t)
