import hashlib, subprocess, sys
P = 'docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep2b-20260915.md'
src = subprocess.run(['git', 'show', '78e87b3:' + P], capture_output=True, check=True).stdout.decode('utf-8')
assert hashlib.sha256(src.encode()).hexdigest() == '37ca6530ad575a828c9d85070fb7bd2bab5fcec73945502e36afb7f9c7e4ca27'
t = src
def rep(a, b, n=1):
    global t
    c = t.count(a); assert c == n, (c, a[:100]); t = t.replace(a, b)
# ---- MUST-2B-56 (a): Step 0 also preserves the prior attempt's finalize bytecode; the new receipts join the preserved set
rep('PRE=\'\'; for f in helpers.verify-10.txt task-10-go.txt push-url.txt remote-branch-before.txt visibility.txt exposure-remote-main.txt exposure-count.txt exposure-authors.txt exposure-secret.txt work/exposure-patches.txt work/owner-lines.txt work/owner-paths.txt work/owner-paths.uniq; do if [ -e "$EVID/$f" ] || [ -L "$EVID/$f" ]; then [ -f "$EVID/$f" ] && [ ! -L "$EVID/$f" ] || STOP; PRE="$PRE $f"; fi; done',
    'PRE=\'\'; for f in helpers.verify-10.txt task-10-go.txt push-url.txt fetch-url.txt url-rewrite.txt remote-branch-before.txt visibility.txt exposure-remote-main.txt exposure-count.txt exposure-authors.txt exposure-secret.txt work/exposure-patches.txt work/owner-lines.txt work/owner-paths.txt work/owner-paths.uniq; do if [ -e "$EVID/$f" ] || [ -L "$EVID/$f" ]; then [ -f "$EVID/$f" ] && [ ! -L "$EVID/$f" ] || STOP; PRE="$PRE $f"; fi; done\n'
    '# rev43 (MUST-2B-56): the prior attempt\'s finalize bytecode (`python3 -m py_compile` under rev41/rev42 wrote it) is part of its byte set and is preserved too; this runner\'s own syntax check writes no bytecode (below)\n'
    'for f in "$EVID"/__pycache__/finalize.rev41.*.pyc; do if [ -e "$f" ] || [ -L "$f" ]; then [ -f "$f" ] && [ ! -L "$f" ] || STOP; PRE="$PRE __pycache__/${f##*/}"; fi; done')
rep('  m=0; mkdir "$AD" || m=$?; [ "$m" -eq 0 ] || STOP; m=0; mkdir "$AD/work" || m=$?; [ "$m" -eq 0 ] || STOP',
    '  m=0; mkdir "$AD" || m=$?; [ "$m" -eq 0 ] || STOP; m=0; mkdir "$AD/work" || m=$?; [ "$m" -eq 0 ] || STOP; m=0; mkdir "$AD/__pycache__" || m=$?; [ "$m" -eq 0 ] || STOP')
# ---- MUST-2B-56 (b): the syntax check compiles in memory, writing no bytecode into the evidence home
rep('p=0; python3 -m py_compile "$F41" || p=$?; [ "$p" -eq 0 ] || STOP',
    'p=0; python3 -c \'import sys; compile(open(sys.argv[1], encoding="utf-8").read(), sys.argv[1], "exec")\' "$F41" || p=$?; [ "$p" -eq 0 ] || STOP   # rev43 (MUST-2B-56): compiled in memory, no `__pycache__` write')
# ---- MUST-2B-55: ONE destination for every remote read and write
rep('u=0; git remote get-url --push --all origin > "$EVID/push-url.txt" || u=$?;',
    '# rev43 (MUST-2B-55): the ONE destination, named literally in every remote read and write; origin\'s fetch AND push URLs must each be exactly it, and no url.* rewrite may exist in any git config scope (insteadOf / pushInsteadOf would re-route even a literal URL)\n'
    'URL=https://github.com/iwnlcern/bivpak.git; REPO=iwnlcern/bivpak\n'
    'u=0; git remote get-url --all origin > "$EVID/fetch-url.txt" || u=$?; [ "$u" -eq 0 ] && [ -s "$EVID/fetch-url.txt" ] || STOP; a=0; nf=$(awk \'END { print NR }\' "$EVID/fetch-url.txt") || a=$?; [ "$a" -eq 0 ] && [ "$nf" -eq 1 ] && [ "$(cat "$EVID/fetch-url.txt")" = "$URL" ] || STOP\n'
    'r=0; git config --get-regexp \'^url\\.\' > "$EVID/url-rewrite.txt" || r=$?; [ "$r" -eq 1 ] && [ ! -s "$EVID/url-rewrite.txt" ] || STOP; [ "$(git ls-remote --get-url "$URL")" = "$URL" ] || STOP\n'
    'u=0; git remote get-url --push --all origin > "$EVID/push-url.txt" || u=$?;')
rep('[ "$(cat "$EVID/push-url.txt")" = https://github.com/iwnlcern/bivpak.git ] || STOP\nl=0; git ls-remote --heads origin intg/substep2b-wiring > "$EVID/remote-branch-before.txt"', '[ "$(cat "$EVID/push-url.txt")" = "$URL" ] || STOP\nl=0; git ls-remote --heads "$URL" intg/substep2b-wiring > "$EVID/remote-branch-before.txt"')
rep('v=0; gh repo view --json visibility -q .visibility > "$EVID/visibility.txt"', 'v=0; gh repo view "$REPO" --json visibility -q .visibility > "$EVID/visibility.txt"')
rep('l=0; git ls-remote origin refs/heads/main > "$EVID/exposure-remote-main.txt"', 'l=0; git ls-remote "$URL" refs/heads/main > "$EVID/exposure-remote-main.txt"')
rep('y=0; git push --dry-run --no-tags origin intg/substep2b-wiring > "$EVID/push-dry.txt"', 'y=0; git push --dry-run --no-tags "$URL" intg/substep2b-wiring > "$EVID/push-dry.txt"')
rep('p=0; git push --no-tags origin intg/substep2b-wiring > "$EVID/push-stdout.txt"', 'p=0; git push --no-tags "$URL" intg/substep2b-wiring > "$EVID/push-stdout.txt"')
rep('o=0; git ls-remote --heads origin intg/substep2b-wiring > "$EVID/remote-branch-after.txt"', 'o=0; git ls-remote --heads "$URL" intg/substep2b-wiring > "$EVID/remote-branch-after.txt"')
rep('q=0; gh pr create --base main --head intg/substep2b-wiring', 'q=0; gh pr create --repo "$REPO" --base main --head intg/substep2b-wiring')
# ---- prose
rep("- [ ] **Step 0 (rev42): preserve a prior attempt** — before any `$EVID` write:",
    "- [ ] **Step 0 (rev42; rev43 MUST-2B-56): preserve a prior attempt** — before any receipt the body writes (the generated prologue first publishes the NEW token's own four runner records under `runners/<token>/task-10/`; those are this run's records, never a prior attempt's):")
rep("is renamed into a fresh `attempts/task10-<k>/` with `MANIFEST.pre` and a passing `MANIFEST.verify`.\n",
    "is renamed into a fresh `attempts/task10-<k>/` with `MANIFEST.pre` and a passing `MANIFEST.verify`, INCLUDING the prior attempt's `__pycache__/finalize.rev41.*.pyc` (rev43). `finalize.rev41.py` itself is NOT renamed: it is the digest-pinned shared helper (`a9eec925…`, verified every run) and stays in place. This runner's syntax check compiles it in memory and writes no bytecode, so no prior byte is rewritten.\n")
rep("`git ls-remote --heads origin intg/substep2b-wiring` EMPTY; `gh repo view --json visibility` ∈ {PRIVATE, PUBLIC}",
    "rev43 (MUST-2B-55) ONE destination: `URL=https://github.com/iwnlcern/bivpak.git`, `REPO=iwnlcern/bivpak`; `git remote get-url --all origin` (fetch) is EXACTLY one line equal to `URL`, as is the push URL; `git config --get-regexp '^url\\.'` finds nothing in any scope and `git ls-remote --get-url \"$URL\"` is `URL` (no insteadOf / pushInsteadOf re-routing); every `ls-remote`, the dry-run and the push name `\"$URL\"`, and `gh repo view` / `gh pr create` name `--repo`/`\"$REPO\"`; `git ls-remote --heads \"$URL\" intg/substep2b-wiring` EMPTY; `gh repo view \"$REPO\" --json visibility` ∈ {PRIVATE, PUBLIC}")
rep("`git ls-remote origin refs/heads/main` is exactly B", "`git ls-remote \"$URL\" refs/heads/main` is exactly B")
rep("- [ ] **Step 2: ONE push** — `git push --dry-run --no-tags origin intg/substep2b-wiring`",
    "- [ ] **Step 2: ONE push** — `git push --dry-run --no-tags \"$URL\" intg/substep2b-wiring` (rev43: the literal destination, and the post-push classifier reads the same `\"$URL\"`)")
rep("The operator chose to keep the repository public and publish the branch (\"2\", 2026-09-27). Three changes, and nothing else in this task moves:",
    "The operator chose to keep the repository public and publish the branch (\"2\", 2026-09-27). rev43 folds the implementer's exact-hash MUST-REVISE of rev42 (`intg-substep2b/PLAN-REVIEW-pair-implementer-20260927-151814.md`). MUST-2B-55: every remote read and write now names the one destination, origin's fetch and push URLs must both equal it, and no url.* rewrite may exist. MUST-2B-56: Step 0 also preserves the prior attempt's finalize bytecode, the syntax check writes none, and the Step 0 boundary is stated as the body's first receipt. rev42's three changes, and nothing else in this task moves:")
rep("(`[ \"$(cat \"$EVID/push-url.txt\")\" = https://github.com/iwnlcern/bivpak.git ] || STOP`)", "(`[ \"$(cat \"$EVID/push-url.txt\")\" = \"$URL\" ] || STOP`, rev43)")
# ---- acceptance 18 and history
rep("18. (rev42) Task 10: a prior attempt's files preserved under `attempts/task10-<k>/` (manifest verified),",
    "18. (rev42; rev43) Task 10: a prior attempt's files — its `__pycache__/finalize.rev41.*.pyc` included — preserved under `attempts/task10-<k>/` (manifest verified), `finalize.rev41.py` unchanged in place at `a9eec925…`, no bytecode written by this run; `fetch-url.txt` and `push-url.txt` each exactly `https://github.com/iwnlcern/bivpak.git`, `url-rewrite.txt` empty, every remote read and write naming that URL or `iwnlcern/bivpak`;")
H43 = ("- rev43 (2026-09-27): folds the implementer's exact-hash MUST-REVISE of rev42 (`intg-substep2b/PLAN-REVIEW-pair-implementer-20260927-151814.md`), Task 10 only. "
       "MUST-2B-55: rev42's census read origin's FETCH side and an unqualified `gh repo view` while the push used origin's PUSH URL — split remotes (proved by the implementer's control) would let the census certify one repository and the push mutate another, and the post-push classifier read the wrong one. Now `URL`/`REPO` are pinned; origin's fetch and push URLs must each be exactly `URL`; no `url.*` rewrite (insteadOf / pushInsteadOf, which re-route even a literal URL) may exist in any scope; every ls-remote, the dry-run, the push and the classifier name `\"$URL\"`; `gh repo view` and `gh pr create` name the repo. "
       "MUST-2B-56: rev42's Step 0 missed the prior attempt's `__pycache__/finalize.rev41.cpython-312.pyc`, which the rerun's `py_compile` would rewrite, and claimed \"before any `$EVID` write\" although the generated prologue writes the new token's runner records first. Now the pyc is preserved, the syntax check compiles in memory, `finalize.rev41.py` is stated as the in-place digest-pinned helper, and the boundary reads \"before any receipt the body writes\".\n")
rep("- rev42 (2026-09-27): folds impl-15's Task 10 STOP", H43 + "- rev42 (2026-09-27): folds impl-15's Task 10 STOP")
sys.stdout.write(t)
