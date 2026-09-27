### Task 9b — the re-gate at the c10 head: the count cells re-pinned INSIDE the block iff a case tuple moved since c9 (c11), the FINAL H written last into `R/` (rev39; the operator's "lighter regate pls", 2026-09-26; m-3 R-4.83 and master R-4.82 folded for this block)

**Why a lighter re-gate and not Task 9 again.** Task 9 ran once to rc 0 under impl-12 and stands as EXECUTED: its receipts under `H/`, `H9/`, `series/` and `B/` are the record for H0 `99136ca` and its H `2893bc53`, and nothing here moves or rewrites them. c10 changes only the failed-row rendering, its schema and its witnesses. Task 8c's head gate already observes the c10 head on both platforms: the five macOS producers and the canonical Linux container, tidy clean at 37/37, E3 inside `biv_tests`, every ctest row but harness-selftest passed (R-4.83's property, taken from the whole row census rather than inside a population branch), and the selftest summary. This block adds only what the head gate does not carry: c10's path set and the censuses c10 could move; the count gate against c9's cells; both skip sets; the macOS `harness-e2` row; the selftest population, which must EQUAL Task 9's (a moved population needs the series and is a STOP routed up, never a lighter pass); the count-cell companion c11 iff c10 moved a tuple; and the FINAL H.

**Outputs:** everything under a fresh `$EVID/R/` (created by plain `mkdir`, so an existing directory or a symlink STOPs — R-4.82's form), `$EVID/commits.c11.txt` iff c11 lands, and `heads/c11/` from the head gate iff c11 lands. `R/H.txt` is written LAST and is the object the three owner byte reviews, the GO and Task 10 bind.

- [ ] **Step 1: run the block** — `bash` the block `regate.sh` (extracted from this plan by `plan_blocks.py extract`) ONCE from the worktree, with `EVID` and `RUNNERS` exported as the token names them. A STOP ends the token: report it with its line and receipts, never retry, never weaken a predicate.
- [ ] **Step 2: record** — the IMPL return enumerates c10's paths (and c11's, iff it landed) against their Files lines and quotes `R/H.txt`.

<!-- BLOCK: regate.sh -->
```bash
# Task 9b — the re-gate at the c10 head (rev39): usage  bash <this block>  from the worktree with EVID and RUNNERS exported; run ONCE after Task 8c's head gate
set -o pipefail
STOP() { printf 'STOP-regate %s line=%s\n' "$1" "${BASH_LINENO[0]}" >&2; exit 1; }
MAIN=/Users/jack/Programming/bivpak; B=186adf7d67171bd7afe621f39b657a1a113ce299
[ -n "${EVID-}" ] && [ -d "$EVID" ] && [ ! -L "$EVID" ] && [ -n "${RUNNERS-}" ] && [ -d "$RUNNERS" ] || STOP env
[ "$(cat "$RUNNERS/evid.txt")" = "$EVID" ] || STOP evid-pointer
PLAN=$(cat "$RUNNERS/plan-path.txt") || STOP plan-pointer; [ -s "$PLAN" ] || STOP plan-absent
h=0; d=$(shasum -a 256 "$PLAN" | cut -d' ' -f1) || h=$?; [ "$h" -eq 0 ] && [ "$d" = "$(cat "$RUNNERS/plan-lock.txt")" ] || STOP plan-not-the-lock
# the preconditions: HEAD is c10; its parent is c9, Task 9's FINAL H; Task 9 done; Task 8c's receipts; the tree clean
z=0; C10=$(cat "$EVID/commits.c10.txt") || z=$?; [ "$z" -eq 0 ] && [ -n "$C10" ] && [ "$(git rev-parse HEAD)" = "$C10" ] || STOP not-at-c10
z=0; C9=$(cat "$EVID/commits.c9.txt") || z=$?; [ "$z" -eq 0 ] && [ -n "$C9" ] && [ "$(git rev-parse HEAD~1)" = "$C9" ] || STOP parent-not-c9
[ "$(cat "$EVID/H.txt")" = "H=$C9" ] || STOP task9-H-not-c9
[ "$(cat "$EVID/runners/task-9.done")" = rc=0 ] || STOP task9-not-done
G=$EVID/heads/c10
[ -s "$G/headgate.txt" ] && [ -s "$EVID/receipts/c10-mutants.txt" ] && [ -s "$EVID/receipts/c10-red.txt" ] || STOP task8c-receipts
g=0; k=$(grep -c -E "^headgate label=c10 head=$C10 tidy_expected=none tidy_findings=0 " "$G/headgate.txt") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP headgate-c10
git diff --cached --quiet && git diff HEAD --quiet || STOP dirty
u=$(git ls-files --others --exclude-standard); r=$?; [ "$r" -eq 0 ] && [ -z "$u" ] || STOP untracked
# confinement before the first write (rev38's form): R/ and commits.c11.txt absent, no symlink directly under the home, R/ made by a plain mkdir and physically the home's own
for x in R commits.c11.txt; do [ ! -e "$EVID/$x" ] && [ ! -L "$EVID/$x" ] || STOP "exists-$x"; done
f=0; LNK=$(find "$EVID" -maxdepth 1 -type l) || f=$?; [ "$f" -eq 0 ] && [ -z "$LNK" ] || STOP home-symlink
m=0; mkdir "$EVID/R" || m=$?; [ "$m" -eq 0 ] || STOP R-mkdir
p=0; RH=$(cd "$EVID" && pwd -P) || p=$?; [ "$p" -eq 0 ] && [ -d "$EVID/R" ] && [ ! -L "$EVID/R" ] && [ "$(cd "$EVID/R" && pwd -P)" = "$RH/R" ] || STOP R-confined
w=0; printf 'H0=%s\n' "$C10" > "$EVID/R/H0.txt" || w=$?; [ "$w" -eq 0 ] || STOP w-H0
# (1) c10's path set inside Task 8c's Files line, none under src/core/repo; the censuses c10 could move, compared by CONTENT between c9 and c10
g=0; git diff-tree --no-commit-id --name-only -r "$C10" > "$EVID/R/c10-paths.txt" || g=$?; [ "$g" -eq 0 ] && [ -s "$EVID/R/c10-paths.txt" ] || STOP c10-paths
o=0; grep -v -x -E 'src/core/open/open\.cpp|src/core/report/envelope\.(hpp|cpp)|src/cli/url_consent\.(hpp|cpp)|schemas/biv-json-envelope\.v1\.schema\.json|harness/selftest/test_envelope\.py|tests/test_cli\.cpp|tests/test_envelope\.cpp|CMakeLists\.txt' "$EVID/R/c10-paths.txt" > "$EVID/R/c10-paths.foreign" || o=$?; [ "$o" -eq 1 ] && [ ! -s "$EVID/R/c10-paths.foreign" ] || STOP c10-foreign-path
CEN() { local tag=$1 pat=$2 T; for T in "$C9" "$C10"; do local g=0; git grep -n -E "$pat" "$T" -- src ':!src/core/repo' > "$EVID/work/regate-$tag-$T.raw" || g=$?; [ "$g" -le 1 ] || STOP "census-$tag"; local s=0; sed -E "s/^${T}:([^:]+):[0-9]+:/\1: /" "$EVID/work/regate-$tag-$T.raw" > "$EVID/work/regate-$tag-$T.txt" || s=$?; [ "$s" -eq 0 ] || STOP "census-strip-$tag"; done
  local d=0; diff "$EVID/work/regate-$tag-$C9.txt" "$EVID/work/regate-$tag-$C10.txt" > "$EVID/R/census-$tag.delta" || d=$?; [ "$d" -eq 0 ] || STOP "census-moved-$tag"; }
CEN E2 'repo::(discover|classify|run_eligibility|capture|restore_entry)\('
CEN closure 'invoke_git\('
CEN network 'GitCallClass::network'
g=0; git grep -n -E 'posix_spawn|execv|popen|std::system|fork\(' HEAD -- src ':!src/core/repo' ':!src/core/support' > "$EVID/R/S1-nospawn.txt" || g=$?; [ "$g" -eq 1 ] && [ ! -s "$EVID/R/S1-nospawn.txt" ] || STOP S1-nospawn
g=0; grep -n -E 'facts\.(op|repo|requested|effective)' src/cli/url_consent.cpp > "$EVID/R/a8-facts-lines.txt" || g=$?; [ "$g" -eq 0 ] && [ -s "$EVID/R/a8-facts-lines.txt" ] || STOP a8-facts
g=0; k=$(grep -c -v 'consent_display(' "$EVID/R/a8-facts-lines.txt") || g=$?; [ "$g" -le 1 ] && [ "$k" -eq 0 ] || STOP a8-raw-fact
z=0; git diff --stat "$B" HEAD -- src/core/manifest src/adapters harness/bivharness/e3.py src/core/open/render.cpp > "$EVID/R/zero-byte-fences.txt" || z=$?; [ "$z" -eq 0 ] && [ ! -s "$EVID/R/zero-byte-fences.txt" ] || STOP zero-byte-fences
# (2) every tuple failures=0 on both platforms (a failure count is never a move), the count gate against c9's cells (MOVED rows are data), and both skip sets UNCHANGED
for T in macos linux; do g=0; k=$(grep -c -x -E "biv_[a-z_]+ $T successes=[0-9]+ failures=0 expectedFailures=0 skips=[0-9]+ xml_sha256=[0-9a-f]{64}" "$G/tuples-$T.txt") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 5 ] || STOP "tuples-failures-$T"; g=0; k=$(grep -c -E '^biv_' "$G/tuples-$T.txt") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 5 ] || STOP "tuples-rows-$T"; done
c=0; python3 "$EVID/cells.py" .github/workflows/s2-harness.yml > "$EVID/R/c9-cells.txt" || c=$?; [ "$c" -eq 0 ] && [ -s "$EVID/R/c9-cells.txt" ] || STOP c9-cells
for T in macos linux; do c=0; python3 "$EVID/cellgate.py" "$EVID/R/c9-cells.txt" "$T" "$G/tuples-$T.txt" > "$EVID/R/count-gate-$T.txt" 2>&1 || c=$?; printf 'count_gate_%s_rc=%s\n' "$T" "$c" > "$EVID/R/count-gate-$T.rc" || STOP "w-count-gate-$T"; [ "$c" -eq 0 ] || [ "$c" -eq 5 ] || STOP "count-gate-$T"; done
q=0; python3 "$EVID/skipset.py" "$EVID/B-cells.txt" "$G/tuples-macos.txt" macos > "$EVID/R/skipset-macos.txt" || q=$?; [ "$q" -eq 0 ] || STOP skipset-macos
for T in B c10; do if [ "$T" = B ]; then TF=$EVID/B/tuples-linux.txt; else TF=$G/tuples-linux.txt; fi; g=0; grep -E '^expected_skips_observed linux n=[0-9]+ ' "$TF" > "$EVID/R/skipset-linux-$T.txt" || g=$?; [ "$g" -eq 0 ] || STOP "skipset-linux-$T"; a=0; n=$(awk 'END { print NR }' "$EVID/R/skipset-linux-$T.txt") || a=$?; [ "$a" -eq 0 ] && [ "$n" -eq 1 ] || STOP "skipset-linux-rows-$T"; done
q=0; cmp "$EVID/R/skipset-linux-B.txt" "$EVID/R/skipset-linux-c10.txt" > "$EVID/R/skipset-linux.cmp" 2>&1 || q=$?; printf 'skipset_linux_rc=%s\n' "$q" > "$EVID/R/skipset-linux.rc"; [ "$q" -eq 0 ] || STOP skipset-linux
# (3) E3 Linux, harness-e2 on both platforms, and the ctest row census at c10 (only harness-selftest may fail; the new witness row ran and passed)
x=0; python3 - "$G/H/biv_tests-linux.xml" > "$EVID/R/E3-linux.txt" <<'PY' || x=$?
import sys, xml.etree.ElementTree as ET
rows = []
for tc in ET.fromstring(open(sys.argv[1], "rb").read()).iter("TestCase"):
    if "[E3]" in (tc.get("tags") or ""):
        o = tc.find("OverallResult")
        rows.append((tc.get("name"), None if o is None else o.get("success")))
if not rows:
    print("E3 cases=0"); sys.exit(3)
for name, ok in rows:
    print("E3 case=%r success=%s" % (name, ok))
sys.exit(0 if all(ok == "true" for _, ok in rows) else 5)
PY
printf 'e3_linux_rc=%s\n' "$x" > "$EVID/R/E3-linux.rc"; [ "$x" -eq 0 ] || STOP E3-linux
x=0; python3 "$EVID/xmlcases.py" ctest-row harness-e2 "$G/H/ctest-linux-H.junit.xml" > "$EVID/R/harness-e2-linux.txt" || x=$?; printf 'harness_e2_linux_rc=%s\n' "$x" > "$EVID/R/harness-e2-linux.rc"; [ "$x" -eq 0 ] || STOP harness-e2-linux
e=0; ctest --preset ci-macos -R '^harness-e2$' --output-on-failure > "$EVID/R/harness-e2-macos.log" 2>&1 || e=$?; printf 'harness_e2_macos_rc=%s\n' "$e" > "$EVID/R/harness-e2-macos.rc"; [ "$e" -eq 0 ] || STOP harness-e2-macos
o=0; grep -E '^fail ' "$G/ctest-status.txt" > "$EVID/R/ctest-failed-c10.txt" || o=$?; [ "$o" -le 1 ] || STOP ctest-failed-grep
o=0; grep -v -x -F 'fail harness-selftest' "$EVID/R/ctest-failed-c10.txt" > "$EVID/R/ctest-failed-c10.foreign" || o=$?; [ "$o" -eq 1 ] && [ ! -s "$EVID/R/ctest-failed-c10.foreign" ] || STOP ctest-foreign-red
g=0; k=$(grep -c -x -F 'run divergence_envelope_conforms' "$G/ctest-status.txt") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP witness-row-linux
# (4) the selftest population EQUAL to Task 9's, and the bar (a moved population needs the series: a STOP routed up, never a lighter pass)
s=0; sed -n 's/^population=//p' "$EVID/H/selftest-H.kv" > "$EVID/R/selftest-population-task9.txt" || s=$?; [ "$s" -eq 0 ] && [ -s "$EVID/R/selftest-population-task9.txt" ] || STOP population-task9
s=0; sed -n 's/^population=//p' "$G/selftest-H.kv" > "$EVID/R/selftest-population-c10.txt" || s=$?; [ "$s" -eq 0 ] && [ -s "$EVID/R/selftest-population-c10.txt" ] || STOP population-c10
p=0; cmp "$EVID/R/selftest-population-task9.txt" "$EVID/R/selftest-population-c10.txt" > "$EVID/R/selftest-population.cmp" 2>&1 || p=$?; printf 'population_equal_rc=%s\n' "$p" > "$EVID/R/selftest-population.rc"; [ "$p" -eq 0 ] || STOP population-moved
rcL=$(cat "$G/H/ctest-linux-H.rc") || STOP rcL; [ -n "$rcL" ] || STOP rcL-empty
hsum=$(sed -n 's/^summary=//p' "$G/selftest-H.kv"); nfail=$(sed -n 's/^failed=//p' "$G/selftest-H.kv"); nf=$(sed -n 's/^names_count=//p' "$G/selftest-H.kv"); [ -n "$hsum" ] && [ -n "$nfail" ] && [ -n "$nf" ] || STOP selftest-kv
o=0; grep -v -x -F -f "$EVID/H/r435-family.txt" "$G/selftest-H.names" > "$EVID/R/linux-selftest-foreign.names" || o=$?; [ "$o" -le 1 ] || STOP foreign-names
bar=fail; if [ "$rcL" -eq 0 ]; then bar=pass-green; elif [ "$rcL" -ne 8 ]; then bar=fail-not-the-one-row; elif [ "$hsum" != parsed ] || [ "$nf" -lt 1 ] || [ "$nf" -ne "$nfail" ]; then bar=stop-invalid-candidate-result; elif [ -s "$EVID/R/linux-selftest-foreign.names" ]; then bar=fail-foreign-selftest-red; else bar=pass-r435-disclosed-registered-red; fi
printf 'rcL=%s summary=%s failed=%s names=%s bar=%s\n' "$rcL" "$hsum" "$nfail" "$nf" "$bar" > "$EVID/R/linux-selftest-bar.txt" || STOP w-bar
case "$bar" in pass-green|pass-r435-disclosed-registered-red) :;; *) STOP "bar-$bar";; esac
# (5) the companion count-cell commit c11 INSIDE the block iff c10's tuples differ from c9's cells; its head gated by headgate.sh; then the FINAL gates against HEAD's own cells
p=0; python3 "$EVID/cellpatch.py" "$EVID/B-workflow.yml" "$G/tuples-macos.txt" "$G/tuples-linux.txt" > "$EVID/work/s2-harness.regate.yml" || p=$?; [ "$p" -eq 0 ] && [ -s "$EVID/work/s2-harness.regate.yml" ] || STOP cellpatch
c=0; cmp -s "$EVID/work/s2-harness.regate.yml" .github/workflows/s2-harness.yml || c=$?
if [ "$c" -eq 0 ]; then
  printf 'unchanged-since-c9\n' > "$EVID/R/count-gate.txt" || STOP w-count-gate
elif [ "$c" -eq 1 ]; then
  c=0; cp "$EVID/work/s2-harness.regate.yml" .github/workflows/s2-harness.yml || c=$?; [ "$c" -eq 0 ] || STOP cellpatch-copy
  g=0; git add .github/workflows/s2-harness.yml && git commit -q -m "ci: re-pin case counts at the c10 head (macOS/Linux) -- m-3 count-cell companion" || g=$?; [ "$g" -eq 0 ] || STOP c11-commit
  w=0; git rev-parse HEAD > "$EVID/commits.c11.txt" || w=$?; [ "$w" -eq 0 ] && [ -s "$EVID/commits.c11.txt" ] || STOP w-c11
  g=0; git diff-tree --no-commit-id --name-only -r HEAD > "$EVID/R/c11-paths.txt" || g=$?; [ "$g" -eq 0 ] && [ "$(cat "$EVID/R/c11-paths.txt")" = .github/workflows/s2-harness.yml ] || STOP c11-paths
  HG=$(mktemp "$EVID/work/headgate.regate.XXXXXX") || STOP hg-mktemp; x=0; python3 "$RUNNERS/plan_blocks.py" extract "$PLAN" headgate.sh > "$HG" || x=$?; [ "$x" -eq 0 ] && [ -s "$HG" ] || STOP hg-extract
  x=0; bash "$HG" c11 > "$EVID/R/headgate-c11.out" 2>&1 || x=$?; [ "$x" -eq 0 ] || STOP headgate-c11
  printf 'count-cells-moved: c11 committed\n' > "$EVID/R/count-gate.txt" || STOP w-count-gate
else STOP cellpatch-cmp; fi
c=0; python3 "$EVID/cells.py" .github/workflows/s2-harness.yml > "$EVID/R/H-cells.txt" || c=$?; [ "$c" -eq 0 ] && [ -s "$EVID/R/H-cells.txt" ] || STOP H-cells
for T in macos linux; do c=0; python3 "$EVID/cellgate.py" "$EVID/R/H-cells.txt" "$T" "$G/tuples-$T.txt" > "$EVID/R/count-gate-final-$T.txt" 2>&1 || c=$?; printf 'count_gate_final_%s_rc=%s\n' "$T" "$c" > "$EVID/R/count-gate-final-$T.rc" || STOP "w-final-$T"; [ "$c" -eq 0 ] || STOP "count-gate-final-$T"; done
# (6) the FINAL H: nothing but the workflow's cells between c10 and H, the tree clean, R/H.txt LAST
H=$(git rev-parse HEAD) || STOP head
d=0; git diff --stat "$C10" "$H" -- . ':!.github/workflows/s2-harness.yml' > "$EVID/R/c10-H.delta" || d=$?; [ "$d" -eq 0 ] && [ ! -s "$EVID/R/c10-H.delta" ] || STOP c10-H-delta
s=0; git status --porcelain > "$EVID/R/status-post.txt" || s=$?; [ "$s" -eq 0 ] && [ ! -s "$EVID/R/status-post.txt" ] || STOP status-post
w=0; printf 'H=%s\n' "$H" > "$EVID/R/H.txt" || w=$?; [ "$w" -eq 0 ] && [ -s "$EVID/R/H.txt" ] || STOP w-H
printf 'regate OK H=%s\n' "$H"
```

