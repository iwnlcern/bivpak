# Task 8c — the c10 mutant record (rev40; impl-13's rev39 attempt preserved; m-3 160359 F5, master 164725): run ONCE at the c10 head, before its head gate; usage  bash <this block>  from the worktree with EVID exported
set -o pipefail
STOP() { printf 'STOP-c10-mutants %s line=%s\n' "$1" "${BASH_LINENO[0]}" >&2; exit 1; }
[ -n "${EVID-}" ] && [ -d "$EVID/receipts" ] && [ -d "$EVID/code" ] || STOP env
z=0; C10=$(cat "$EVID/commits.c10.txt") || z=$?; [ "$z" -eq 0 ] && [ -n "$C10" ] && [ "$(git rev-parse HEAD)" = "$C10" ] || STOP not-at-c10
z=0; C9=$(cat "$EVID/commits.c9.txt") || z=$?; [ "$z" -eq 0 ] && [ -n "$C9" ] && [ "$(git rev-parse HEAD~1)" = "$C9" ] || STOP parent-not-c9
git diff --cached --quiet && git diff HEAD --quiet || STOP dirty
# impl-13's rev39 attempt stays exactly where it is: its record (the M-H1-PRE assertion rev39 could not meet) and its work directory
Q=$EVID/receipts/c10-mutants.txt; [ -f "$Q" ] && [ ! -L "$Q" ] || STOP rev39-record-absent
h=0; s=$(shasum -a 256 "$Q" | cut -d' ' -f1) || h=$?; [ "$h" -eq 0 ] && [ "$s" = 4fe1c9768bc4e6305611cf371c3259ca6d2efcfc16990f2339fee60724145afc ] || STOP rev39-record-moved
[ -d "$EVID/code/c10-mutants" ] && [ ! -L "$EVID/code/c10-mutants" ] || STOP rev39-work-absent
O=$EVID/receipts/c10-mutants.rev40.txt; [ ! -e "$O" ] && [ ! -L "$O" ] || STOP record-exists
P=$EVID/code/c10-M-H1-F4.patch; [ -f "$P" ] && [ -s "$P" ] && [ ! -L "$P" ] || STOP f4-patch-absent
g=0; k=$(grep -c -E '^\+\+\+ ' "$P") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP f4-patch-files; g=0; k=$(grep -c -x -F '+++ b/src/core/report/envelope.cpp' "$P") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP f4-patch-path
g=0; k=$(grep -c -E '^@@ ' "$P") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP f4-patch-hunks
a=0; git apply --check "$P" || a=$?; [ "$a" -eq 0 ] || STOP f4-patch-applies
M=$EVID/code/c10-mutants.rev40; [ ! -e "$M" ] && [ ! -L "$M" ] || STOP work-exists; m=0; mkdir "$M" || m=$?; [ "$m" -eq 0 ] || STOP work-mkdir
# the named witnesses at c10 (w1, w3), by their TEST_CASE names; divergence_envelope_conforms REQUIRES the fixture biv_tests sets up, so CTest runs it only when biv_tests passes
W1='open repos typed refusal continues in encounter order to a clean entry'
W3A='failed row completeness rejects a missing kind'
W3B='failed row completeness rejects a missing detail and complete rows emit no null carriers'
status() { local log=$1 name=$2 n p f r; g=0; p=$(grep -c -E "Test +#[0-9]+: $name \.+ +Passed " "$log") || g=$?; [ "$g" -le 1 ] || STOP "status-grep-$name"
  g=0; f=$(grep -c -E "Test +#[0-9]+: $name \.+\*\*\*Failed " "$log") || g=$?; [ "$g" -le 1 ] || STOP "status-grep-$name"
  g=0; r=$(grep -c -E "Test +#[0-9]+: $name \.+\*\*\*Not Run " "$log") || g=$?; [ "$g" -le 1 ] || STOP "status-grep-$name"
  n=$((p + f + r)); [ "$n" -eq 1 ] || STOP "status-count-$name-$n"
  if [ "$p" -eq 1 ]; then printf passed; elif [ "$f" -eq 1 ]; then printf failed; else printf notrun; fi; }
run() { local name=$1 bs ds
  b=0; cmake --build --preset ci-macos > "$M/$name.build.log" 2>&1 || b=$?; [ "$b" -eq 0 ] || { git checkout -q HEAD -- .; STOP "build-$name"; }
  x=0; ./build/ci-macos/biv_tests -r xml > "$M/$name.xml" 2> "$M/$name.stderr" || x=$?
  f=0; python3 -c 'import sys, xml.etree.ElementTree as E
r = E.parse(sys.argv[1]).getroot()
for t in r.iter("TestCase"):
    o = t.find("OverallResult")
    if o is not None and o.get("success") == "false":
        print(t.get("name"))' "$M/$name.xml" > "$M/$name.failed-cases.txt" || f=$?
  [ "$f" -eq 0 ] || { git checkout -q HEAD -- .; STOP "cases-$name"; }
  y=0; ctest --preset ci-macos -R '^(generated_envelope_reset|divergence_envelope_reset|biv_tests|divergence_envelope_conforms)$' > "$M/$name.ctest.log" 2>&1 || y=$?
  bs=$(status "$M/$name.ctest.log" biv_tests) || { git checkout -q HEAD -- .; exit 1; }
  ds=$(status "$M/$name.ctest.log" divergence_envelope_conforms) || { git checkout -q HEAD -- .; exit 1; }
  g=0; nf=$(grep -c . "$M/$name.failed-cases.txt") || g=$?; [ "$g" -le 1 ] || { git checkout -q HEAD -- .; STOP "cases-count-$name"; }
  c=0; git checkout -q HEAD -- . || c=$?; [ "$c" -eq 0 ] || STOP "revert-$name"; git diff --cached --quiet && git diff HEAD --quiet || STOP "not-clean-after-$name"
  printf 'mutant=%s gating=yes case_rc=%s ctest_rc=%s biv_tests=%s conforms=%s failed_cases=%s\n' "$name" "$x" "$y" "$bs" "$ds" "$nf" >> "$O" || STOP record-write; }
has() { g=0; k=$(grep -c -x -F -- "$2" "$M/$1.failed-cases.txt") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP "$3"; }
g=0; git checkout -q "$C9" -- src/core/open/open.cpp || g=$?; [ "$g" -eq 0 ] || STOP apply-M-H1-PRE
run M-H1-PRE
g=0; git checkout -q "$C9" -- schemas/biv-json-envelope.v1.schema.json || g=$?; [ "$g" -eq 0 ] || STOP apply-M-H1-SCHEMA
run M-H1-SCHEMA
a=0; git apply "$P" || a=$?; [ "$a" -eq 0 ] || STOP apply-M-H1-F4
run M-H1-F4
b=0; cmake --build --preset ci-macos > "$M/rebuild.log" 2>&1 || b=$?; [ "$b" -eq 0 ] || STOP rebuild
git diff --cached --quiet && git diff HEAD --quiet || STOP dirty-after
g=0; k=$(grep -c -E '^mutant=M-H1-(PRE|SCHEMA|F4) gating=yes ' "$O") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 3 ] || STOP record-rows
# M-H1-PRE: killed by (w1) alone inside biv_tests; the conforms consumer is NOT RUN by the fixture, never counted as a kill
g=0; k=$(grep -c -E '^mutant=M-H1-PRE gating=yes case_rc=[1-9][0-9]* ctest_rc=[1-9][0-9]* biv_tests=failed conforms=notrun failed_cases=1$' "$O") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP survived-M-H1-PRE
has M-H1-PRE "$W1" M-H1-PRE-not-w1
# M-H1-SCHEMA: every case green, and the whole-envelope validation (the conforms row) alone red
g=0; k=$(grep -c -E '^mutant=M-H1-SCHEMA gating=yes case_rc=0 ctest_rc=[1-9][0-9]* biv_tests=passed conforms=failed failed_cases=0$' "$O") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP survived-M-H1-SCHEMA
# M-H1-F4: killed by (w3)'s two cases alone inside biv_tests; the conforms consumer NOT RUN
g=0; k=$(grep -c -E '^mutant=M-H1-F4 gating=yes case_rc=[1-9][0-9]* ctest_rc=[1-9][0-9]* biv_tests=failed conforms=notrun failed_cases=2$' "$O") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP survived-M-H1-F4
has M-H1-F4 "$W3A" M-H1-F4-not-w3a; has M-H1-F4 "$W3B" M-H1-F4-not-w3b
printf 'verdict=ok\n' >> "$O" || STOP verdict-write
g=0; k=$(grep -c -x -F 'verdict=ok' "$O") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP verdict-read
printf 'c10 mutants OK (%s)\n' "$O"
