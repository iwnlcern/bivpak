import hashlib, subprocess, sys
P = 'docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep2b-20260915.md'
src = subprocess.run(['git', 'show', 'df0b928:' + P], capture_output=True, check=True).stdout.decode('utf-8')
assert hashlib.sha256(src.encode()).hexdigest() == '0140f69eeebbf4102d29f5799b3f8c46f5de76d5bf4419197b08c7a376be9122'
t = src
def rep(a, b, n=1):
    global t
    c = t.count(a); assert c == n, (c, a[:100]); t = t.replace(a, b)
ALT = 'sk-[A-Za-z0-9]{8,}|-----BEGIN [A-Z ]*PRIVATE KEY|AKIA[0-9A-Z]{16}|ghp_[A-Za-z0-9]{20,}|xox[abprs]-'
# ---- (1) Step 0: preserve a prior attempt, before any $EVID write
PRES = r'''cd "$WORKTREE" || STOP
# rev42 Step 0: a PRIOR Task 10 attempt's evidence is preserved by rename, never overwritten (impl-15's successor attempt STOPped at the visibility preflight, return 045007); a push or PR receipt from ANY prior attempt is a STOP — a remote act may have happened, and this runner never repeats one
for f in push-dry.txt push-stdout.txt push-stderr.txt push-rc.txt remote-branch-after.txt push-class.txt pr-body.md pr-create.txt pr.rc; do [ ! -e "$EVID/$f" ] && [ ! -L "$EVID/$f" ] || STOP; done
PRE=''; for f in helpers.verify-10.txt task-10-go.txt push-url.txt remote-branch-before.txt visibility.txt exposure-remote-main.txt exposure-count.txt exposure-authors.txt exposure-secret.txt work/exposure-patches.txt work/owner-lines.txt work/owner-paths.txt work/owner-paths.uniq; do if [ -e "$EVID/$f" ] || [ -L "$EVID/$f" ]; then [ -f "$EVID/$f" ] && [ ! -L "$EVID/$f" ] || STOP; PRE="$PRE $f"; fi; done
if [ -n "$PRE" ]; then
  m=0; mkdir -p "$EVID/attempts" || m=$?; [ "$m" -eq 0 ] && [ -d "$EVID/attempts" ] && [ ! -L "$EVID/attempts" ] || STOP
  k=1; while [ -e "$EVID/attempts/task10-$k" ] || [ -L "$EVID/attempts/task10-$k" ]; do k=$((k + 1)); done; AD=$EVID/attempts/task10-$k
  m=0; mkdir "$AD" || m=$?; [ "$m" -eq 0 ] || STOP; m=0; mkdir "$AD/work" || m=$?; [ "$m" -eq 0 ] || STOP
  h=0; (cd "$EVID" && shasum -a 256 $PRE) > "$AD/MANIFEST.pre" || h=$?; [ "$h" -eq 0 ] && [ -s "$AD/MANIFEST.pre" ] || STOP
  for f in $PRE; do v=0; mv "$EVID/$f" "$AD/$f" || v=$?; [ "$v" -eq 0 ] && [ ! -e "$EVID/$f" ] && [ -f "$AD/$f" ] || STOP; done
  h=0; (cd "$AD" && shasum -a 256 -c MANIFEST.pre) > "$AD/MANIFEST.verify" 2>&1 || h=$?; [ "$h" -eq 0 ] || STOP
fi'''
rep('cd "$WORKTREE" || STOP\nv=0; (cd "$EVID" && shasum -a 256 -c helpers.sha256 > helpers.verify-10.txt 2>&1)', PRES + '\nv=0; (cd "$EVID" && shasum -a 256 -c helpers.sha256 > helpers.verify-10.txt 2>&1)')
# ---- (2) visibility: PUBLIC accepted on the operator's word; (3) the exposure census
rep('v=0; gh repo view --json visibility -q .visibility > "$EVID/visibility.txt" || v=$?; [ "$v" -eq 0 ] && [ "$(cat "$EVID/visibility.txt")" = PRIVATE ] || STOP\n',
    'v=0; gh repo view --json visibility -q .visibility > "$EVID/visibility.txt" || v=$?; [ "$v" -eq 0 ] || STOP; case "$(cat "$EVID/visibility.txt")" in PRIVATE|PUBLIC) ;; *) STOP;; esac   # rev42: PUBLIC accepted on the operator\'s word "2" (2026-09-27) — the branch is published to the public repository\n'
    '# rev42: the exposure census — what the push publishes, measured before it: the remote main IS B (so exactly B..H is new), exactly 26 commits, every author and committer a placeholder @local identity, zero secret-pattern hits in the B..H patches\n'
    'l=0; git ls-remote origin refs/heads/main > "$EVID/exposure-remote-main.txt" || l=$?; [ "$l" -eq 0 ] && [ "$(cat "$EVID/exposure-remote-main.txt")" = "$(printf \'%s\\trefs/heads/main\' "$B")" ] || STOP\n'
    'c=0; n=$(git rev-list --count "$B..$H") || c=$?; [ "$c" -eq 0 ] && [ "$n" -eq 26 ] || STOP; w=0; printf \'commits=%s\\n\' "$n" > "$EVID/exposure-count.txt" || w=$?; [ "$w" -eq 0 ] || STOP\n'
    'g=0; git log --format=\'%ae%n%ce\' "$B..$H" > "$EVID/exposure-authors.txt" || g=$?; [ "$g" -eq 0 ] && [ -s "$EVID/exposure-authors.txt" ] || STOP; g=0; k=$(grep -c -v -E \'^[a-z0-9.-]+@local$\' "$EVID/exposure-authors.txt") || g=$?; [ "$g" -eq 1 ] && [ "$k" -eq 0 ] || STOP\n'
    'g=0; git log -p "$B..$H" > "$EVID/work/exposure-patches.txt" || g=$?; [ "$g" -eq 0 ] && [ -s "$EVID/work/exposure-patches.txt" ] || STOP; g=0; k=$(grep -c -E \'' + ALT + '\' "$EVID/work/exposure-patches.txt") || g=$?; [ "$g" -eq 1 ] && [ "$k" -eq 0 ] || STOP; w=0; printf \'secret_hits=0\\n\' > "$EVID/exposure-secret.txt" || w=$?; [ "$w" -eq 0 ] || STOP\n')
# ---- prose
rep("`git ls-remote --heads origin intg/substep2b-wiring` EMPTY; `gh repo view --json visibility` == PRIVATE; no executable `pre-push` hook.",
    "`git ls-remote --heads origin intg/substep2b-wiring` EMPTY; `gh repo view --json visibility` ∈ {PRIVATE, PUBLIC} (rev42: PUBLIC accepted on the operator's word \"2\", 2026-09-27 — the branch is published to the public repository); rev42's EXPOSURE CENSUS: `git ls-remote origin refs/heads/main` is exactly B (so the push publishes exactly B..H), `git rev-list --count B..H` is 26, every author and committer e-mail in B..H matches `^[a-z0-9.-]+@local$`, and the census alternation over `git log -p B..H` has 0 hits (receipts `exposure-*.txt`); no executable `pre-push` hook.")
rep("Protocol (e): before `run-task.sh 10` the operator's ONE typed act is the GO relay's path into `$RUNNERS/task-10-go.txt`;",
    "Protocol (e): before `run-task.sh 10` the GO relay's ABSOLUTE path is written into `$RUNNERS/task-10-go.txt` (rev42: by the pair Planner on the operator's word \"just cite it, you dont need my typed ack\", 2026-09-27; the controller is invoked by its ABSOLUTE path, `\"$RUNNERS\"/run-task.sh 10` — its line 7 refuses any other `$0`);")
rep("this is the rev37 `series_verdict.rev37.py` pattern.\n",
    "this is the rev37 `series_verdict.rev37.py` pattern.\n\nrev42 (impl-15's Task 10 return `intg-substep2b/IMPL-pair-implementer-20260927-045007.md`: `STOP-task-10 line=73`, the live visibility `PUBLIC` against the required `PRIVATE`, before the hook check, the dry-run, the push and the PR — none of their receipts exists). The operator chose to keep the repository public and publish the branch (\"2\", 2026-09-27). Three changes, and nothing else in this task moves: Step 0 preserves a prior attempt's `$EVID` files by rename into `attempts/task10-<k>/` with a verified manifest, and STOPs if any push or PR receipt exists; the visibility predicate accepts `PRIVATE` or `PUBLIC`; the EXPOSURE CENSUS runs before the dry-run (Step 1). Measured at the pair Planner's seat before this revision: GitHub's `main` is B, so the push adds exactly the 26 B..H commits; all 26 carry `@local` placeholder identities; the B..H patches have 0 census hits (the H tree's 40 hit files are byte-identical at B, all the `sk-complete`/`sk-structured` false positive, already public on `main`); the real PR body from `finalize.rev41.py` has 0 hits and no local path. The runner re-runs from a NEW runners directory (Step 0′ under the next token, on this revision's lock): the controller's one-shot fence refuses a second run in `s2b-runners-j6w4EX`, whose `task-10.exit` (rc=1) is impl-15's record.\n")
rep("- [ ] **Step 1: the owner-set gate, then preconditions** —",
    "- [ ] **Step 0 (rev42): preserve a prior attempt** — before any `$EVID` write: every push/PR receipt (`push-dry.txt`, `push-stdout.txt`, `push-stderr.txt`, `push-rc.txt`, `remote-branch-after.txt`, `push-class.txt`, `pr-body.md`, `pr-create.txt`, `pr.rc`) ABSENT or STOP; every earlier-stage file this runner writes that exists (regular, not a link) is renamed into a fresh `attempts/task10-<k>/` with `MANIFEST.pre` and a passing `MANIFEST.verify`.\n- [ ] **Step 1: the owner-set gate, then preconditions** —")
# ---- acceptance 18
rep("\n\n## Out of scope (an act here is a STOP, not a judgement)",
    "\n\n18. (rev42) Task 10: a prior attempt's files preserved under `attempts/task10-<k>/` (manifest verified), no push or PR receipt from any earlier attempt; visibility `PRIVATE` or `PUBLIC`; the exposure receipts (`exposure-remote-main.txt` == B on `refs/heads/main`, `exposure-count.txt` `commits=26`, `exposure-authors.txt` all `@local`, `exposure-secret.txt` `secret_hits=0`) written before the dry-run; then ONE push (class a) and ONE draft PR.\n\n## Out of scope (an act here is a STOP, not a judgement)")
# ---- history
H42 = ("- rev42 (2026-09-27): folds impl-15's Task 10 STOP (`intg-substep2b/IMPL-pair-implementer-20260927-045007.md`, `STOP-task-10 line=73`: `gh repo view` returned `PUBLIC`, the gate required `PRIVATE`; nothing pushed). The operator chose to keep the repository public and publish the branch (\"2\", 2026-09-27). "
       "Task 10 only: Step 0 preserves a prior attempt's `$EVID` files by rename (manifest verified) and STOPs on any push/PR receipt; the visibility predicate accepts `PRIVATE` or `PUBLIC`; the exposure census (remote `main` == B, 26 commits, `@local` identities, 0 census hits in the B..H patches) runs before the dry-run. Protocol (e)'s prose records the operator's waiver of the typed act and the controller's absolute invocation (impl-15's first attempt STOPped `controller-invoked-off-path` on `./run-task.sh`, return 044136). "
       "Every measurement the census encodes was taken at the pair Planner's seat before this revision. Task 10 re-runs from a new runners directory under the next token (`s2b-runners-j6w4EX` keeps impl-15's `task-10.exit`).\n")
rep("- rev41 (2026-09-26): folds impl-14's STOP", H42 + "- rev41 (2026-09-26): folds impl-14's STOP")
sys.stdout.write(t)
