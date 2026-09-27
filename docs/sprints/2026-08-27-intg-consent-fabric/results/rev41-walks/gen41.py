import hashlib, re, subprocess, sys
P = 'docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep2b-20260915.md'
src = subprocess.run(['git', 'show', 'e86c891:' + P], capture_output=True, check=True).stdout.decode('utf-8')
assert hashlib.sha256(src.encode()).hexdigest() == '682ceb885cf06f53270a6b3558f54a48f124ce3b36a63409c3ef9469db1aa607'
t = src
def rep(a, b, n=1):
    global t
    c = t.count(a); assert c == n, (c, a[:100]); t = t.replace(a, b)
CR = 'dbea9b75bcbe0c7ee3f2b9096ef21af1678b5746'; RP = 'docs/sprints/2026-08-27-intg-consent-fabric/results/c10t-scout-20260926/repair-13-c10t-initializers.patch'
RS = hashlib.sha256(subprocess.run(['git', 'show', CR + ':' + RP], capture_output=True, check=True).stdout).hexdigest(); assert RS.startswith('0508c70f')
LS = '6b0c66e5f2882bd7eaf20b6a2dbce194b804c190bc573297d5edabd037e74404'; TREE = '36331eb01cc53efcf8dfafd803948a2cc0f765af'
R40 = '725ee7fd1bc7ea13a99aa457713a899e5f5cb7df71e83fb7ed5c29d59b2c67bf'
# ---- topology table, order rule, H paragraph
rep("c11 ci: count cells re-pinned (IFF a case tuple at the c10 head differs from c9's cells) —            Task 9b  .github/workflows/s2-harness.yml only",
    "c10t test: the two c10 failed-row initializers name every RepoOutcomeRow member (Linux GCC         Task 8d  tests/test_envelope.cpp only\n         -Werror=missing-field-initializers; impl-14 231301; repair-13); rev41, after c10's head gate STOPped\n"
    "c11 ci: count cells re-pinned (IFF a case tuple at the c10t head differs from c9's cells) —           Task 9b  .github/workflows/s2-harness.yml only")
rep("rev39: c10 after c9 (Task 8c; its head passes the per-head gate), then c11 iff moved (Task 9b), last.",
    "rev39: c10 after c9 (Task 8c); rev41: c10t after c10 (Task 8d; ITS head passes the per-head gate — c10's head gate STOPped under impl-14 and `heads/c10/` stays as that record), then c11 iff moved (Task 9b), last.")
rep("c10 touches no src/core/repo path; c11 touches the workflow alone.",
    "c10 touches no src/core/repo path; c11 touches the workflow alone. rev41: the re-gate object is the c10t head (Task 8d) — `R/H0.txt` names c10t, the FINAL H is c10t iff no cell moved since c9, and Task 9b proves `git diff c10t H -- . ':!.github/workflows/s2-harness.yml'` EMPTY; c10t touches `tests/test_envelope.cpp` alone.")
# ---- headgate.sh label
rep("(rev39: also c10, Task 8c, and c11, Task 9b)", "(rev39: also c10, Task 8c, and c11, Task 9b; rev41: c10t, Task 8d)")
rep("  c10|c11) TL=none; TS=none; NT=0;;", "  c10|c10t|c11) TL=none; TS=none; NT=0;;")
# ---- Task 8c heading + Step 6
rep("(rev40: Steps 0–4 EXECUTED under impl-13, c10 `2291a46`; Step 5 runs rev40's mutant record;",
    "(rev41: Step 5 EXECUTED under impl-14 — `receipts/c10-mutants.rev40.txt`, `verdict=ok` — and Step 6 STOPPED on the canonical Linux build, repaired by Task 8d as c10t; rev40: Steps 0–4 EXECUTED under impl-13, c10 `2291a46`; Step 5 runs rev40's mutant record;")
rep("every ctest row but harness-selftest passed): `heads/c10/headgate.txt`.\n- [ ] **Step 7: record** — the IMPL return enumerates c10's paths against the Files line (master 042625 (1)).",
    "every ctest row but harness-selftest passed): `heads/c10/headgate.txt`. rev41: EXECUTED under impl-14 and STOPPED (`STOP-headgate container`: GCC 13 `-Werror=missing-field-initializers` at `tests/test_envelope.cpp:75` and `:85`, the retained `heads/c10/H/linux-build.log` `6b0c66e5…`); `heads/c10/` is that STOP's record, never modified, and the head gate is taken at c10t (Task 8d).\n- [ ] **Step 7: record** — the IMPL return enumerates c10's paths against the Files line (master 042625 (1)). rev41: EXECUTED under impl-14 (its return 231301).")
# ---- Task 8d (inserted before Task 9)
C10T = r'''# Task 8d — c10t (rev41; impl-14's STOP 231301): the two c10 failed-row test initializers name every RepoOutcomeRow member (repair-13, pinned); run ONCE at the c10 head; usage  bash <this block>  from the worktree with EVID exported
set -o pipefail
STOP() { printf 'STOP-c10t %s line=%s\n' "$1" "${BASH_LINENO[0]}" >&2; exit 1; }
MAIN=/Users/jack/Programming/bivpak; CR=@CR@; RP=@RP@
RS=@RS@; LS=@LS@; TREE=@TREE@
[ -n "${EVID-}" ] && [ -d "$EVID" ] && [ ! -L "$EVID" ] && [ -d "$EVID/receipts" ] && [ -d "$EVID/work" ] || STOP env
z=0; C10=$(cat "$EVID/commits.c10.txt") || z=$?; [ "$z" -eq 0 ] && [ -n "$C10" ] && [ "$(git rev-parse HEAD)" = "$C10" ] || STOP not-at-c10
z=0; C9=$(cat "$EVID/commits.c9.txt") || z=$?; [ "$z" -eq 0 ] && [ -n "$C9" ] && [ "$(git rev-parse HEAD~1)" = "$C9" ] || STOP parent-not-c9
git diff --cached --quiet && git diff HEAD --quiet || STOP dirty
u=$(git ls-files --others --exclude-standard); r=$?; [ "$r" -eq 0 ] && [ -z "$u" ] || STOP untracked
# Task 8c's standing record: the rev40 mutant verdict, and the c10 head gate's STOP kept exactly as impl-14 left it (container rc 1, no headgate.txt, the build log by digest)
g=0; k=$(grep -c -x -F 'verdict=ok' "$EVID/receipts/c10-mutants.rev40.txt") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP c10-mutants-verdict
[ -d "$EVID/heads/c10" ] && [ ! -L "$EVID/heads/c10" ] && [ "$(cat "$EVID/heads/c10/linux-container.rc")" = 1 ] && [ ! -e "$EVID/heads/c10/headgate.txt" ] && [ ! -L "$EVID/heads/c10/headgate.txt" ] || STOP c10-stop-record
L=$EVID/heads/c10/H/linux-build.log; [ -f "$L" ] && [ ! -L "$L" ] || STOP c10-build-log
h=0; s=$(shasum -a 256 "$L" | cut -d' ' -f1) || h=$?; [ "$h" -eq 0 ] && [ "$s" = "$LS" ] || STOP c10-build-log-sha
for x in commits.c10t.txt receipts/c10t-red.txt heads/c10t receipts/c10t-mutants.txt code/c10t-mutants work/c10t-red.errors work/c10t-repair-13.patch; do [ ! -e "$EVID/$x" ] && [ ! -L "$EVID/$x" ] || STOP "exists-$x"; done
# (1) the RED is the canonical build's own: every error line of the retained log is one of the 18 — tests/test_envelope.cpp:75 and :85, the nine trailing RepoOutcomeRow members at each — and none is foreign
g=0; grep -E ': error: ' "$L" > "$EVID/work/c10t-red.errors" || g=$?; [ "$g" -eq 0 ] || STOP red-grep
MEM='sha|branch|capture_mode|remotes|bundle_path|reconstruct|local_refs|advisories|shallow_boundary'
g=0; k=$(grep -c -x -E "/work/repo/tests/test_envelope\.cpp:(75|85):25: error: missing initializer for member 'biv::open::RepoOutcomeRow::($MEM)' \[-Werror=missing-field-initializers\]" "$EVID/work/c10t-red.errors") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 18 ] || STOP red-shape
a=0; n=$(awk 'END { print NR }' "$EVID/work/c10t-red.errors") || a=$?; [ "$a" -eq 0 ] && [ "$n" -eq 18 ] || STOP red-foreign
s=0; d=$(sed -E 's/^[^:]+:([0-9]+):25: .*::([a-z_]+).*$/\1 \2/' "$EVID/work/c10t-red.errors" | LC_ALL=C sort -u | awk 'END { print NR }') || s=$?; [ "$s" -eq 0 ] && [ "$d" -eq 18 ] || STOP red-distinct
w=0; printf 'log=heads/c10/H/linux-build.log sha256=%s\nerrors=18 at=tests/test_envelope.cpp:75,85 members=9-each distinct=18 foreign=0\n' "$LS" > "$EVID/receipts/c10t-red.txt" || w=$?; [ "$w" -eq 0 ] && [ -s "$EVID/receipts/c10t-red.txt" ] || STOP red-receipt
# (2) repair-13, the pinned patch, applied to the working tree: exactly tests/test_envelope.cpp, +8/-2
PT=$EVID/work/c10t-repair-13.patch
g=0; git -C "$MAIN" show "${CR}:${RP}" > "$PT" || g=$?; [ "$g" -eq 0 ] && [ -s "$PT" ] || STOP patch-read
h=0; s=$(shasum -a 256 "$PT" | cut -d' ' -f1) || h=$?; [ "$h" -eq 0 ] && [ "$s" = "$RS" ] || STOP patch-sha
a=0; git apply --check "$PT" || a=$?; [ "$a" -eq 0 ] || STOP patch-check
a=0; git apply "$PT" || a=$?; [ "$a" -eq 0 ] || { git checkout -q HEAD -- .; STOP patch-apply; }
n=0; ns=$(git diff --numstat) || n=$?; [ "$n" -eq 0 ] && [ "$ns" = "$(printf '8\t2\ttests/test_envelope.cpp')" ] || { git checkout -q HEAD -- .; STOP patch-numstat; }
# (3) green on macOS: the build; biv_tests whole, with (w3)'s two cases passed; the envelope rows passed
b=0; cmake --build --preset ci-macos > "$EVID/work/c10t-build-macos.log" 2>&1 || b=$?; [ "$b" -eq 0 ] || { git checkout -q HEAD -- .; STOP build; }
x=0; ./build/ci-macos/biv_tests -r xml > "$EVID/work/c10t-biv_tests.xml" 2> "$EVID/work/c10t-biv_tests.stderr" || x=$?; [ "$x" -eq 0 ] || { git checkout -q HEAD -- .; STOP biv-tests; }
f=0; python3 - "$EVID/work/c10t-biv_tests.xml" > "$EVID/work/c10t-w3.txt" <<'PY' || f=$?
import sys, xml.etree.ElementTree as E
want = {"failed row completeness rejects a missing kind", "failed row completeness rejects a missing detail and complete rows emit no null carriers"}
seen = {}
for t in E.parse(sys.argv[1]).getroot().iter("TestCase"):
    if t.get("name") in want:
        o = t.find("OverallResult")
        seen[t.get("name")] = None if o is None else o.get("success")
for n in sorted(want):
    print("case=%r success=%s" % (n, seen.get(n)))
sys.exit(0 if all(seen.get(n) == "true" for n in want) else 5)
PY
[ "$f" -eq 0 ] || { git checkout -q HEAD -- .; STOP w3-cases; }
y=0; ctest --preset ci-macos -R '^(generated_envelope_reset|divergence_envelope_reset|biv_tests|generated_envelope_conforms|divergence_envelope_conforms)$' > "$EVID/work/c10t-ctest.log" 2>&1 || y=$?; [ "$y" -eq 0 ] || { git checkout -q HEAD -- .; STOP envelope-rows; }
for row in biv_tests generated_envelope_conforms divergence_envelope_conforms; do g=0; k=$(grep -c -E "Test +#[0-9]+: $row \.+ +Passed " "$EVID/work/c10t-ctest.log") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || { git checkout -q HEAD -- .; STOP "row-$row"; }; done
# (4) the commit: the one path staged, its tree the scout's BEFORE the commit (git write-tree), the exact message; its parent c10; the tree clean after
g=0; git add -- tests/test_envelope.cpp || g=$?; [ "$g" -eq 0 ] || { git reset -q; git checkout -q HEAD -- .; STOP stage; }
g=0; IT=$(git write-tree) || g=$?; [ "$g" -eq 0 ] && [ "$IT" = "$TREE" ] || { git reset -q; git checkout -q HEAD -- .; STOP index-tree; }
g=0; git commit -q -m "test: name every RepoOutcomeRow member in c10's two failed-row initializers (Linux GCC -Werror=missing-field-initializers) -- c10t, test-only (impl-14 231301; repair-13)" || g=$?; [ "$g" -eq 0 ] || STOP commit
[ "$(git rev-parse HEAD~1)" = "$C10" ] || STOP commit-parent
[ "$(git rev-parse 'HEAD^{tree}')" = "$TREE" ] || STOP commit-tree
g=0; P1=$(git diff-tree --no-commit-id --name-only -r HEAD) || g=$?; [ "$g" -eq 0 ] && [ "$P1" = tests/test_envelope.cpp ] || STOP commit-paths
git diff --cached --quiet && git diff HEAD --quiet || STOP dirty-after
u=$(git ls-files --others --exclude-standard); r=$?; [ "$r" -eq 0 ] && [ -z "$u" ] || STOP untracked-after
w=0; git rev-parse HEAD > "$EVID/commits.c10t.txt" || w=$?; [ "$w" -eq 0 ] && [ -s "$EVID/commits.c10t.txt" ] || STOP w-commit
printf 'c10t OK %s\n' "$(cat "$EVID/commits.c10t.txt")"
'''.replace('@CR@', CR).replace('@RP@', RP).replace('@RS@', RS).replace('@LS@', LS).replace('@TREE@', TREE)
# c10t-mutants.sh from rev40's c10-mutants.sh, each changed line named
i = t.index('<!-- BLOCK: c10-mutants.sh -->\n```bash\n') + len('<!-- BLOCK: c10-mutants.sh -->\n```bash\n'); j = t.index('```\n', i)
M40 = t[i:j]
m = M40
def mrep(a, b):
    global m
    assert m.count(a) == 1, a[:80]; m = m.replace(a, b)
mrep("# Task 8c — the c10 mutant record (rev40; impl-13's rev39 attempt preserved; m-3 160359 F5, master 164725): run ONCE at the c10 head, before its head gate;",
     "# Task 8d — the c10t mutant record (rev41; Task 8c's rev40 record preserved; m-3 160359 F5 and its F5_M_H1_PRE accept 222938, master 164725): run ONCE at the c10t head, before its head gate;")
mrep("STOP() { printf 'STOP-c10-mutants %s", "STOP() { printf 'STOP-c10t-mutants %s")
mrep('''z=0; C10=$(cat "$EVID/commits.c10.txt") || z=$?; [ "$z" -eq 0 ] && [ -n "$C10" ] && [ "$(git rev-parse HEAD)" = "$C10" ] || STOP not-at-c10
z=0; C9=$(cat "$EVID/commits.c9.txt") || z=$?; [ "$z" -eq 0 ] && [ -n "$C9" ] && [ "$(git rev-parse HEAD~1)" = "$C9" ] || STOP parent-not-c9
''', '''z=0; C10T=$(cat "$EVID/commits.c10t.txt") || z=$?; [ "$z" -eq 0 ] && [ -n "$C10T" ] && [ "$(git rev-parse HEAD)" = "$C10T" ] || STOP not-at-c10t
z=0; C10=$(cat "$EVID/commits.c10.txt") || z=$?; [ "$z" -eq 0 ] && [ -n "$C10" ] && [ "$(git rev-parse HEAD~1)" = "$C10" ] || STOP parent-not-c10
z=0; C9=$(cat "$EVID/commits.c9.txt") || z=$?; [ "$z" -eq 0 ] && [ -n "$C9" ] && [ "$(git rev-parse HEAD~2)" = "$C9" ] || STOP grandparent-not-c9
''')
mrep('''# impl-13's rev39 attempt stays exactly where it is: its record (the M-H1-PRE assertion rev39 could not meet) and its work directory
Q=$EVID/receipts/c10-mutants.txt; [ -f "$Q" ] && [ ! -L "$Q" ] || STOP rev39-record-absent
h=0; s=$(shasum -a 256 "$Q" | cut -d' ' -f1) || h=$?; [ "$h" -eq 0 ] && [ "$s" = 4fe1c9768bc4e6305611cf371c3259ca6d2efcfc16990f2339fee60724145afc ] || STOP rev39-record-moved
[ -d "$EVID/code/c10-mutants" ] && [ ! -L "$EVID/code/c10-mutants" ] || STOP rev39-work-absent
O=$EVID/receipts/c10-mutants.rev40.txt; [ ! -e "$O" ] && [ ! -L "$O" ] || STOP record-exists
''', '''# Task 8c's rev40 record (verdict=ok at c10, impl-14) stays exactly where it is, with its work directory
Q=$EVID/receipts/c10-mutants.rev40.txt; [ -f "$Q" ] && [ ! -L "$Q" ] || STOP rev40-record-absent
h=0; s=$(shasum -a 256 "$Q" | cut -d' ' -f1) || h=$?; [ "$h" -eq 0 ] && [ "$s" = @R40@ ] || STOP rev40-record-moved
[ -d "$EVID/code/c10-mutants.rev40" ] && [ ! -L "$EVID/code/c10-mutants.rev40" ] || STOP rev40-work-absent
O=$EVID/receipts/c10t-mutants.txt; [ ! -e "$O" ] && [ ! -L "$O" ] || STOP record-exists
'''.replace('@R40@', R40))
mrep('M=$EVID/code/c10-mutants.rev40; [ ! -e "$M" ]', 'M=$EVID/code/c10t-mutants; [ ! -e "$M" ]')
mrep("# the named witnesses at c10 (w1, w3)", "# the named witnesses at c10t (w1, w3)")
mrep("printf 'c10 mutants OK (%s)\\n' \"$O\"", "printf 'c10t mutants OK (%s)\\n' \"$O\"")
MT = m
T8D = '''### Task 8d — c10t: the two c10 failed-row test initializers name every `RepoOutcomeRow` member, so the canonical Linux GCC build compiles (rev41; impl-14's STOP `intg-substep2b/IMPL-pair-implementer-20260926-231301.md`)

**Why this task exists.** impl-14 ran Task 8c Step 5 green (`receipts/c10-mutants.rev40.txt`, `verdict=ok`); Step 6's one head gate at c10 then STOPped in the canonical Linux container. GCC 13 rejects c10's two new `report.repos.push_back({...})` rows in `tests/test_envelope.cpp` (`:75`, `:85`) under `-Wall -Wextra -Werror` as `-Werror=missing-field-initializers`: each names five of `RepoOutcomeRow`'s fourteen members, and Apple clang accepts that. It is the class c8L (`c47eb32`) already repaired for the 2b structs, re-introduced by c10's new rows: Task 8c checked c10 green on macOS only (Step 3) and met the canonical Linux toolchain first at its head gate. The census is complete, not a stopped build's first page: the retained log's error lines are exactly those 18 (the nine trailing members at each row), and a scout at c10 plus the repair built and passed the WHOLE canonical container — tidy clean at 37/37, only harness-selftest red, the selftest population EQUAL to Task 9's — with macOS tuples equal to c10's and the mutant record reproducing impl-14's three rows (`results/c10t-scout-20260926/scout-summary.txt` at `dbea9b75`).

**Files:** `tests/test_envelope.cpp` only (inside c10's Files line and the 53-path allowlist). ONE new commit, c10t, on top of c10; c10 is not amended; no product byte moves; nothing under `src/core/repo`, so veto 9 is untouched.

**The repair (repair-13, pinned).** Each of the two rows names the nine trailing members explicitly, as the rows at `tests/test_envelope.cpp:979` already do: `.sha = std::nullopt, .branch = std::nullopt, .capture_mode = std::nullopt, .remotes = {}, .bundle_path = std::nullopt, .reconstruct = std::nullopt, .local_refs = {}, .advisories = {}, .shallow_boundary = std::nullopt` — the values the omitted members already took, so neither case's meaning moves. The patch is `results/c10t-scout-20260926/repair-13-c10t-initializers.patch` at `dbea9b75` (sha256 `''' + RS[:8] + '''…`, +8/−2); the block applies it verbatim and pins the commit's TREE to the scout's (`36331eb0…`).

**Outputs:** `receipts/c10t-red.txt` (the canonical RED, from impl-14's retained build log), `commits.c10t.txt`, `receipts/c10t-mutants.txt` with `code/c10t-mutants/` (the mutant record re-taken at c10t, ending in ONE `verdict=ok`), and `heads/c10t/` (the head gate). `heads/c10/` stays exactly as impl-14 left it: the STOP's record.

- [ ] **Steps 0–4: the block `c10t.sh`** — `bash` it ONCE from the worktree at the c10 head with `EVID` exported. It checks the preconditions: HEAD c10, parent c9, the tree clean, Task 8c's rev40 `verdict=ok`, and `heads/c10/` holding the STOP by content (container rc 1, no `headgate.txt`, the retained build log `6b0c66e5…`). It writes the RED receipt from that log: exactly the 18 lines, nothing foreign. It applies repair-13 (sha-checked; +8/−2 on the one path) and proves it green on macOS: the build, `biv_tests` whole with (w3)'s two cases passed, and the rows `generated_envelope_conforms` and `divergence_envelope_conforms` passed. It then commits with the exact message, pins the commit's tree to the scout's, and writes `commits.c10t.txt`. Any STOP before the commit restores the working tree.
- [ ] **Step 5: the mutant record at c10t** — `bash` the block `c10t-mutants.sh`: Task 8c's three gating mutants with the same named witnesses and verdict lines (M-H1-PRE and M-H1-SCHEMA restore their files from c9; M-H1-F4 applies `code/c10-M-H1-F4.patch`), recorded in `receipts/c10t-mutants.txt` and ending in ONE `verdict=ok`. Task 8c's rev40 record and work directory stay where they are, the record pinned by digest.
- [ ] **Step 6: the head gate** — `bash` the block `headgate.sh` with `c10t` (tidy list EMPTY, coverage 37/37, macOS failures 0, the canonical container rc 0, every ctest row but harness-selftest passed): `heads/c10t/headgate.txt`.
- [ ] **Step 7: record** — the IMPL return enumerates c10t's one path against this Files line (master 042625 (1)).

<!-- BLOCK: c10t.sh -->
```bash
''' + C10T + '''```

<!-- BLOCK: c10t-mutants.sh -->
```bash
''' + MT + '''```

'''
rep("### Task 9 — (EXECUTED under impl-12 at H `2893bc53`;", T8D + "### Task 9 — (EXECUTED under impl-12 at H `2893bc53`;")
# ---- Task 9b prose
rep("### Task 9b — the re-gate at the c10 head: the count cells re-pinned INSIDE the block iff a case tuple moved since c9 (c11),",
    "### Task 9b — the re-gate at the c10t head (rev41; c10 + Task 8d's c10t): the count cells re-pinned INSIDE the block iff a case tuple moved since c9 (c11),")
rep("the count-cell companion c11 iff c10 moved a tuple; and the FINAL H.\n",
    "the count-cell companion c11 iff c10 moved a tuple; and the FINAL H.\n\n**rev41 (impl-14's STOP).** The re-gate object is the c10t head — c10 plus Task 8d's test-only c10t — because c10's head gate STOPped on the canonical Linux build. Wherever this task says \"the c10 head\" or \"Task 8c's head gate\", read the c10t head and Task 8d's head gate at `heads/c10t/`. The block checks c10's path set against Task 8c's Files line AND c10t's against Task 8d's (exactly `tests/test_envelope.cpp`); it requires both mutant records' `verdict=ok`; it compares the censuses between c9 and c10t; and it proves `git diff c10t H` outside the workflow EMPTY.\n")
rep("- [ ] **Step 2: record** — the IMPL return enumerates c10's paths (and c11's, iff it landed) against",
    "- [ ] **Step 2: record** — the IMPL return enumerates c10's and c10t's paths (and c11's, iff it landed) against")
# ---- regate.sh
RG = [
("# Task 9b — the re-gate at the c10 head (rev39): usage  bash <this block>  from the worktree with EVID and RUNNERS exported; run ONCE after Task 8c's head gate",
 "# Task 9b — the re-gate at the c10t head (rev39; rev41: c10 + c10t, impl-14's STOP 231301): usage  bash <this block>  from the worktree with EVID and RUNNERS exported; run ONCE after Task 8d's head gate"),
("# the preconditions: HEAD is c10; its parent is c9, Task 9's FINAL H; Task 9 done; Task 8c's receipts; the tree clean\n"
 "z=0; C10=$(cat \"$EVID/commits.c10.txt\") || z=$?; [ \"$z\" -eq 0 ] && [ -n \"$C10\" ] && [ \"$(git rev-parse HEAD)\" = \"$C10\" ] || STOP not-at-c10\n"
 "z=0; C9=$(cat \"$EVID/commits.c9.txt\") || z=$?; [ \"$z\" -eq 0 ] && [ -n \"$C9\" ] && [ \"$(git rev-parse HEAD~1)\" = \"$C9\" ] || STOP parent-not-c9\n",
 "# the preconditions: HEAD is c10t; its parent is c10; c10's parent is c9, Task 9's FINAL H; Task 9 done; Task 8c's and Task 8d's receipts; the tree clean\n"
 "z=0; C10T=$(cat \"$EVID/commits.c10t.txt\") || z=$?; [ \"$z\" -eq 0 ] && [ -n \"$C10T\" ] && [ \"$(git rev-parse HEAD)\" = \"$C10T\" ] || STOP not-at-c10t\n"
 "z=0; C10=$(cat \"$EVID/commits.c10.txt\") || z=$?; [ \"$z\" -eq 0 ] && [ -n \"$C10\" ] && [ \"$(git rev-parse HEAD~1)\" = \"$C10\" ] || STOP parent-not-c10\n"
 "z=0; C9=$(cat \"$EVID/commits.c9.txt\") || z=$?; [ \"$z\" -eq 0 ] && [ -n \"$C9\" ] && [ \"$(git rev-parse HEAD~2)\" = \"$C9\" ] || STOP grandparent-not-c9\n"),
("G=$EVID/heads/c10\n[ -s \"$G/headgate.txt\" ] && [ -s \"$EVID/receipts/c10-red.txt\" ] || STOP task8c-receipts\n",
 "G=$EVID/heads/c10t\n[ -s \"$G/headgate.txt\" ] && [ -s \"$EVID/receipts/c10-red.txt\" ] && [ -s \"$EVID/receipts/c10t-red.txt\" ] || STOP task8c-8d-receipts\n"),
("|| STOP task8c-mutants-verdict\n",
 "|| STOP task8c-mutants-verdict\ng=0; k=$(grep -c -x -F 'verdict=ok' \"$EVID/receipts/c10t-mutants.txt\") || g=$?; [ \"$g\" -eq 0 ] && [ \"$k\" -eq 1 ] || STOP task8d-mutants-verdict\n"),
("g=0; k=$(grep -c -E \"^headgate label=c10 head=$C10 tidy_expected=none tidy_findings=0 \" \"$G/headgate.txt\") || g=$?; [ \"$g\" -eq 0 ] && [ \"$k\" -eq 1 ] || STOP headgate-c10\n",
 "g=0; k=$(grep -c -E \"^headgate label=c10t head=$C10T tidy_expected=none tidy_findings=0 \" \"$G/headgate.txt\") || g=$?; [ \"$g\" -eq 0 ] && [ \"$k\" -eq 1 ] || STOP headgate-c10t\n"),
("w=0; printf 'H0=%s\\n' \"$C10\" > \"$EVID/R/H0.txt\"", "w=0; printf 'H0=%s\\n' \"$C10T\" > \"$EVID/R/H0.txt\""),
("# (1) c10's path set inside Task 8c's Files line, none under src/core/repo; the censuses c10 could move, compared by CONTENT between c9 and c10\n",
 "# (1) c10's path set inside Task 8c's Files line and c10t's EXACTLY tests/test_envelope.cpp, none under src/core/repo; the censuses c10 and c10t could move, compared by CONTENT between c9 and c10t\n"),
("|| STOP c10-foreign-path\n",
 "|| STOP c10-foreign-path\ng=0; git diff-tree --no-commit-id --name-only -r \"$C10T\" > \"$EVID/R/c10t-paths.txt\" || g=$?; [ \"$g\" -eq 0 ] && [ \"$(cat \"$EVID/R/c10t-paths.txt\")\" = tests/test_envelope.cpp ] || STOP c10t-paths\n"),
("for T in \"$C9\" \"$C10\"; do local g=0;", "for T in \"$C9\" \"$C10T\"; do local g=0;"),
("diff \"$EVID/work/regate-$tag-$C9.txt\" \"$EVID/work/regate-$tag-$C10.txt\"", "diff \"$EVID/work/regate-$tag-$C9.txt\" \"$EVID/work/regate-$tag-$C10T.txt\""),
("for T in B c10; do if [ \"$T\" = B ];", "for T in B c10t; do if [ \"$T\" = B ];"),
("cmp \"$EVID/R/skipset-linux-B.txt\" \"$EVID/R/skipset-linux-c10.txt\"", "cmp \"$EVID/R/skipset-linux-B.txt\" \"$EVID/R/skipset-linux-c10t.txt\""),
("# (3) E3 Linux, harness-e2 on both platforms, and the ctest row census at c10 (", "# (3) E3 Linux, harness-e2 on both platforms, and the ctest row census at c10t ("),
("grep -E '^fail ' \"$G/ctest-status.txt\" > \"$EVID/R/ctest-failed-c10.txt\"", "grep -E '^fail ' \"$G/ctest-status.txt\" > \"$EVID/R/ctest-failed-c10t.txt\""),
("grep -v -x -F 'fail harness-selftest' \"$EVID/R/ctest-failed-c10.txt\" > \"$EVID/R/ctest-failed-c10.foreign\" || o=$?; [ \"$o\" -eq 1 ] && [ ! -s \"$EVID/R/ctest-failed-c10.foreign\" ]",
 "grep -v -x -F 'fail harness-selftest' \"$EVID/R/ctest-failed-c10t.txt\" > \"$EVID/R/ctest-failed-c10t.foreign\" || o=$?; [ \"$o\" -eq 1 ] && [ ! -s \"$EVID/R/ctest-failed-c10t.foreign\" ]"),
("> \"$EVID/R/selftest-population-c10.txt\" || s=$?; [ \"$s\" -eq 0 ] && [ -s \"$EVID/R/selftest-population-c10.txt\" ] || STOP population-c10",
 "> \"$EVID/R/selftest-population-c10t.txt\" || s=$?; [ \"$s\" -eq 0 ] && [ -s \"$EVID/R/selftest-population-c10t.txt\" ] || STOP population-c10t"),
("cmp \"$EVID/R/selftest-population-task9.txt\" \"$EVID/R/selftest-population-c10.txt\"", "cmp \"$EVID/R/selftest-population-task9.txt\" \"$EVID/R/selftest-population-c10t.txt\""),
("# (5) the companion count-cell commit c11 INSIDE the block iff c10's tuples differ from c9's cells;", "# (5) the companion count-cell commit c11 INSIDE the block iff c10t's tuples differ from c9's cells;"),
("git commit -q -m \"ci: re-pin case counts at the c10 head (macOS/Linux) -- m-3 count-cell companion\"", "git commit -q -m \"ci: re-pin case counts at the c10t head (macOS/Linux) -- m-3 count-cell companion\""),
("# (6) the FINAL H: nothing but the workflow's cells between c10 and H,", "# (6) the FINAL H: nothing but the workflow's cells between c10t and H,"),
("d=0; git diff --stat \"$C10\" \"$H\" -- . ':!.github/workflows/s2-harness.yml' > \"$EVID/R/c10-H.delta\" || d=$?; [ \"$d\" -eq 0 ] && [ ! -s \"$EVID/R/c10-H.delta\" ] || STOP c10-H-delta",
 "d=0; git diff --stat \"$C10T\" \"$H\" -- . ':!.github/workflows/s2-harness.yml' > \"$EVID/R/c10t-H.delta\" || d=$?; [ \"$d\" -eq 0 ] && [ ! -s \"$EVID/R/c10t-H.delta\" ] || STOP c10t-H-delta"),
]
for a, b in RG: rep(a, b)
# ---- finalize.py block
rep("import hashlib, os, re, sys\n", "import hashlib, os, re, subprocess, sys\n")
rep('''        commits = "\\n".join("- c%s = %s" % (k, rd("commits.c%s.txt" % k)) for k in range(1, 12) if os.path.isfile(os.path.join(evid, "commits.c%s.txt" % k)))
''', '''        labels = [f[len("commits."):-len(".txt")] for f in os.listdir(evid) if re.fullmatch(r"commits\\.(c[0-9]+[A-Za-z]*|r462)\\.txt", f)]
        order = subprocess.run(["git", "rev-list", "--reverse", base + ".." + head], capture_output=True, text=True, check=True).stdout.split()
        pos = {c: i for i, c in enumerate(order)}
        commits = "\\n".join("- %s = %s%s" % (l, rd("commits.%s.txt" % l), "" if rd("commits.%s.txt" % l) in pos else " (NOT in B..H)") for _, l in sorted((pos.get(rd("commits.%s.txt" % l), len(order)), l) for l in labels))
''')
rep('"Re-gate at c10 (Task 9b, rev39): object %s;', '"Re-gate at the c10t head (Task 9b, rev39; rev41): object %s;')
rep("- `finalize.py` — verbatim except the finalizer receipts name Task 11, and the `prbody` subcommand (the PR body from the record files).",
    "- `finalize.py` — verbatim except the finalizer receipts name Task 11, and the `prbody` subcommand (the PR body from the record files). rev41: Task 0 sealed its copy in `helpers.sha256` before rev39 changed the block, so Task 10 runs `$EVID/finalize.rev41.py`, produced from THIS block beside the sealed copy (never overwritten) and digest-pinned — the rev37 `series_verdict.rev37.py` pattern; `prbody` lists every `commits.<label>.txt` in `B..H` order (the rev1–rev40 form listed only the numeric labels c1–c11, omitting c1a–c1e, c3h, c4a/c4b, c6a/c6b/c6m/c6p/c6q, c8L/c8Tr/c8T, c10t and r462). Task 11's `list` and `check` are byte-identical in both copies and keep the sealed one.")
FB = t[t.index('<!-- BLOCK: finalize.py -->\n```python\n') + len('<!-- BLOCK: finalize.py -->\n```python\n'):]
FB = FB[:FB.index('```\n')]
FS = hashlib.sha256(FB.encode()).hexdigest()
# ---- Task 10 prose + block
rep("and the container receipts from `heads/c10/` and `B/`.",
    "and the container receipts from `heads/c10t/` (rev41) and `B/`. rev41: Step 3's PR body is built by `$EVID/finalize.rev41.py`, produced at the START of the runner — before any gate, push or PR — from THIS plan's `finalize.py` block only when absent (a fresh `mktemp` stage in the confined `work/`, checked regular before and after the extract, digest-checked, then renamed into place) and digest-pinned either way, beside Task 0's sealed `finalize.py`, which is never overwritten. Task 0 sealed its helpers in `helpers.sha256` before rev39 changed the block, so rev39's `finalize.py` edits could never reach the sealed copy; this is the rev37 `series_verdict.rev37.py` pattern.")
rep('''v=0; (cd "$EVID" && shasum -a 256 -c helpers.sha256 > helpers.verify-10.txt 2>&1) || v=$?; [ "$v" -eq 0 ] || STOP
H=$(sed 's/^H=//' "$EVID/R/H.txt") || STOP; [ -n "$H" ] || STOP   # rev39: the FINAL H is Task 9b's
''', '''v=0; (cd "$EVID" && shasum -a 256 -c helpers.sha256 > helpers.verify-10.txt 2>&1) || v=$?; [ "$v" -eq 0 ] || STOP
# rev41: the PR-body finalizer, produced beside Task 0's sealed `finalize.py` (never overwritten) from THIS plan's block only when absent (a fresh mktemp stage in the confined work/, checked regular before and after the extract, digest-checked, then renamed into place), digest-pinned either way — before any gate, push or PR
F41=$EVID/finalize.rev41.py
if [ ! -e "$F41" ] && [ ! -L "$F41" ]; then
PLANP=$(cat "$RUNNERS/plan-path.txt") || STOP; [ -s "$PLANP" ] || STOP; F41S=$(mktemp "$EVID/work/finalize.rev41.XXXXXX") || STOP; [ -f "$F41S" ] && [ ! -L "$F41S" ] && [ ! -s "$F41S" ] || STOP; x=0; python3 "$RUNNERS/plan_blocks.py" extract "$PLANP" finalize.py > "$F41S" || x=$?; [ "$x" -eq 0 ] && [ -f "$F41S" ] && [ ! -L "$F41S" ] && [ -s "$F41S" ] || STOP
m=0; fs=$(shasum -a 256 "$F41S" | cut -d' ' -f1) || m=$?; [ "$m" -eq 0 ] && [ "$fs" = @FS@ ] || STOP
[ ! -e "$F41" ] && [ ! -L "$F41" ] || STOP; v=0; mv "$F41S" "$F41" || v=$?; [ "$v" -eq 0 ] || STOP
fi
[ -f "$F41" ] && [ ! -L "$F41" ] || STOP
m=0; fs=$(shasum -a 256 "$F41" | cut -d' ' -f1) || m=$?; [ "$m" -eq 0 ] && [ "$fs" = @FS@ ] || STOP
p=0; python3 -m py_compile "$F41" || p=$?; [ "$p" -eq 0 ] || STOP
H=$(sed 's/^H=//' "$EVID/R/H.txt") || STOP; [ -n "$H" ] || STOP   # rev39: the FINAL H is Task 9b's
'''.replace('@FS@', FS))
rep('[ "$(cat "$EVID/heads/c10/linux-container.rc")" = 0 ] && [ "$(cat "$EVID/B/linux-container.rc")" = 0 ]',
    '[ "$(cat "$EVID/heads/c10t/linux-container.rc")" = 0 ] && [ "$(cat "$EVID/B/linux-container.rc")" = 0 ]')
rep('w=0; python3 "$EVID/finalize.py" prbody "$EVID" "$B" "$H" > "$EVID/pr-body.md"', 'w=0; python3 "$F41" prbody "$EVID" "$B" "$H" > "$EVID/pr-body.md"')
# ---- acceptance
rep("; `heads/c10/headgate.txt` (tidy EMPTY, coverage 37/37, macOS failures 0, container rc 0, only harness-selftest red, `divergence_envelope_conforms` run and passed).",
    "; rev41: `heads/c10/` holds impl-14's head-gate STOP (container rc 1, no `headgate.txt`), unchanged — the head gate passes at c10t (item 17).")
rep("16. (rev39) Task 9b: `R/` complete — c10's path set inside its Files line and the E2 / closure / network censuses unmoved from c9;",
    "16. (rev39) Task 9b: `R/` complete — c10's path set inside its Files line and c10t's exactly `tests/test_envelope.cpp` (rev41), the E2 / closure / network censuses unmoved from c9 at c10t;")
rep("`git diff c10 H` outside the workflow EMPTY; `R/H.txt` written LAST.",
    "`git diff c10t H` outside the workflow EMPTY; `R/H.txt` written LAST.\n\n17. (rev41) Task 8d: c10t on top of c10, `tests/test_envelope.cpp` only, +8/−2, its tree the scout's; `receipts/c10t-red.txt` records the canonical RED from impl-14's retained build log (the 18 missing-initializer errors, nothing foreign); (w3)'s two cases, `biv_tests`, `generated_envelope_conforms` and `divergence_envelope_conforms` green on macOS at c10t; `receipts/c10t-mutants.txt` ends in ONE `verdict=ok` with item 15's three named kills; `heads/c10t/headgate.txt` (tidy EMPTY, coverage 37/37, macOS failures 0, container rc 0, only harness-selftest red, `divergence_envelope_conforms` run and passed). Task 10's PR body comes from `finalize.rev41.py`, produced from this plan's block beside Task 0's sealed `finalize.py` and digest-pinned, and lists every `commits.<label>.txt` in `B..H` order.")
# ---- history
H41 = ("- rev41 (2026-09-26): folds impl-14's STOP (`intg-substep2b/IMPL-pair-implementer-20260926-231301.md`, `STOP-headgate container` at c10). Step 0′ and Task 8c Step 5 passed: `receipts/c10-mutants.rev40.txt` ends in `verdict=ok`, each mutant killed by its named witness. Step 6's one head gate then STOPped in the canonical Linux container on GCC 13 `-Werror=missing-field-initializers` at c10's two new failed-row initializers in `tests/test_envelope.cpp` (`:75`, `:85`), each naming five of `RepoOutcomeRow`'s fourteen members — c8L's class, re-introduced; Task 8c had proved c10 green on macOS only. "
       "NEW Task 8d: c10t, `tests/test_envelope.cpp` only (repair-13, pinned at `dbea9b75`, the commit's tree pinned to the scout's), its RED taken from impl-14's retained build log (exactly the 18 errors, nothing foreign), green on macOS, the mutant record re-taken at c10t (block `c10t-mutants.sh`, rev40's block with its head, parent, record and work names moved), and the head gate at c10t (`headgate.sh` gains the `c10t` label). The census was measured before this revision, not inferred from a stopped build: a scout at c10 plus repair-13 passed the whole canonical container (tidy 0 at 37/37, only harness-selftest red, the selftest population EQUAL to Task 9's 1055), macOS tuples equal to c10's, and the mutant record reproduced impl-14's three rows (`results/c10t-scout-20260926/`). "
       "Task 9b re-gates the c10t head: `regate.sh` binds HEAD c10t → c10 → c9, both mutant verdicts, `heads/c10t/`, c10t's one path, and the censuses and final delta against c10t. Task 10 reads `heads/c10t/`. "
       "A latent rev39 defect, found while tracing Task 10's inputs: Task 0 sealed `finalize.py` in `helpers.sha256` (verified by Tasks 9, 10 and 11) before rev39 edited the block, so rev39's re-gate line and its c10/c11 commit list could never run — the class rev37 met with `series_verdict.py`. Task 10 now produces `finalize.rev41.py` beside the sealed copy (the rev37 pattern) before any gate, push or PR, and its `prbody` lists every `commits.<label>.txt` in `B..H` order; the rev1–rev40 form listed only numeric labels, omitting the veto-9 engine commits c1a–c1e among others. `heads/c10/` stays as impl-14's STOP record. Every other block is unchanged.\n")
rep("- rev40 (2026-09-26): folds impl-13's STOP", H41 + "- rev40 (2026-09-26): folds impl-13's STOP")
sys.stdout.write(t)
print('FS=' + FS, file=sys.stderr); print('C10T lines=%d MT lines=%d' % (C10T.count('\n'), MT.count('\n')), file=sys.stderr)
