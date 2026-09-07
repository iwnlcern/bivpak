STOP(){ echo "STOP-REACHED"; exit 99; }
EVID_RAW=$(mktemp -d "${TMPDIR:-/tmp}/r450-evidence-XXXXXX")
EVID=$(cd "$EVID_RAW" && pwd -P)
[ -d "$EVID" ] || STOP
echo "EVID=$EVID"
for n in cells witness hunks tuples transcribe gate; do cp /tmp/r450-plan-$n.py "$EVID/$n.py" 2>/dev/null || true; done
for n in h_stub h_test h_e3pin h_fidelity rp_mutants; do cp "/tmp/r450-ex-$n.py" "$EVID/$n.py"; done
cp /tmp/r450-ex-walk-A "$EVID/walk-A.expected"; cp /tmp/r450-ex-walk-B "$EVID/walk-B.expected"
cp /tmp/r450-plan-gate.py "$EVID/gate.py"
for n in cells witness hunks tuples transcribe gate h_stub h_test h_e3pin h_fidelity rp_mutants; do [ -s "$EVID/$n.py" ] || STOP; k=0; python3 -m py_compile "$EVID/$n.py" || k=$?; [ "$k" -eq 0 ] || STOP; done; echo helpers-compiled
S=$(mktemp -d "${TMPDIR:-/tmp}/r450-rehearse-XXXXXX"); S=$(cd "$S" && pwd -P); git clone -q --shared --no-checkout /Users/jack/Programming/bivpak "$S/wt"; cd "$S/wt"; git checkout -q -b intg/r450-discover-parity bbf297e36a38a1fab8c2675f945098a0633f9f8b; git update-ref refs/remotes/origin/main bbf297e36a38a1fab8c2675f945098a0633f9f8b; cp /Users/jack/Programming/bivpak-intg-r450-discover-parity/src/adapters/claude_code/claude_code.cpp src/adapters/claude_code/claude_code.cpp; cp /Users/jack/Programming/bivpak-intg-r450-discover-parity/tests/test_adapter_claude_collect.cpp tests/test_adapter_claude_collect.cpp; git -c user.name=r -c user.email=r@x commit -q -am "scratch C"; printf "%s\n" "$(git rev-parse HEAD)" > "$EVID/C.txt"; ln -s /tmp/r450-venvtest/.venv-harness .venv-harness; printf "__pycache__/\n.pytest_cache/\n.venv-harness\n" >> .git/info/exclude; echo scratch-ready
cp /tmp/r450-unset-names.txt "$EVID/observer-unset-names.txt"
OBS_ENV=(env); while read -r n; do OBS_ENV+=(-u "$n"); done < "$EVID/observer-unset-names.txt"
for p in src/adapters/claude_code/claude_code.cpp src/adapters/codex/codex.cpp tests/test_adapter_claude_collect.cpp; do w=0; git show "bbf297e36a38a1fab8c2675f945098a0633f9f8b:${p}" > "$EVID/base-$(basename "$p")" || w=$?; [ "$w" -eq 0 ] && [ -s "$EVID/base-$(basename "$p")" ] || STOP; done; h=0; shasum -a 256 "$EVID"/base-*.cpp > "$EVID/base-hashes.txt" || h=$?; [ "$h" -eq 0 ] && [ -s "$EVID/base-hashes.txt" ] || STOP
cp /var/folders/hq/f0qq8v_103q9y8prfn20rzx80000gn/T/r450-evidence-16Y21z/ctest-macos-P.log "$EVID/ctest-macos-P.log"
f=0; grep -E '^[[:space:]]+[0-9]+ - .*\(Failed\)' "$EVID/ctest-macos-P.log" > "$EVID/ctest-macos-P.failed" || f=$?; [ "$f" -le 1 ] || STOP; s=0; sed -E 's/^[[:space:]]*[0-9]+ - ([^ ]+) .*/\1/' "$EVID/ctest-macos-P.failed" > "$EVID/ctest-macos-P.failed-names" || s=$?; [ "$s" -eq 0 ] || STOP; printf 'harness-selftest\n' > "$EVID/ctest-failed.expected"; d=0; diff "$EVID/ctest-failed.expected" "$EVID/ctest-macos-P.failed-names" > "$EVID/ctest-macos-P.failed.delta" || d=$?; [ "$d" -eq 0 ] || STOP
g=0; k=$(grep -c -F 'claude_adapter_file' "$EVID/ctest-macos-P.log") || g=$?; [ "$g" -le 1 ] || STOP; [ "$k" -ge 1 ] || STOP
echo "task1-iv-ok $(cat "$EVID/ctest-macos-P.failed-names")"
C=$(cat "$EVID/C.txt"); e=0; git cat-file -e "${C}^{commit}" || e=$?; [ "$e" -eq 0 ] || STOP; [ "$(git rev-parse HEAD)" = "$C" ] || STOP; s=0; git status --porcelain > "$EVID/status-pre-H.txt" || s=$?; [ "$s" -eq 0 ] && [ ! -s "$EVID/status-pre-H.txt" ] || STOP
q=0; git diff --quiet bbf297e36a38a1fab8c2675f945098a0633f9f8b "$C" -- harness || q=$?; [ "$q" -eq 0 ] || STOP
w=0; grep -rn -E 'claude_code\.cpp|claude_adapter_file' harness/ --include='*.py' > "$EVID/walk-A.txt" || w=$?; [ "$w" -eq 0 ] && [ -s "$EVID/walk-A.txt" ] || STOP; s=0; sed -E 's/^([^:]+:[0-9]+):.*$/\1/' "$EVID/walk-A.txt" > "$EVID/walk-A.inv" || s=$?; [ "$s" -eq 0 ] || STOP; o=0; sort "$EVID/walk-A.inv" > "$EVID/walk-A.sorted" || o=$?; [ "$o" -eq 0 ] || STOP; d=0; diff "$EVID/walk-A.expected" "$EVID/walk-A.sorted" > "$EVID/walk-A.delta" || d=$?; [ "$d" -eq 0 ] || STOP
w=0; grep -rn -E 'CLAUDE_CONFIG_DIR|/\.claude|"\.claude"|SESSION_LOCATIONS|LIVE_STORE_SELECTORS' harness/ --include='*.py' --include='*.json' > "$EVID/walk-B.txt" || w=$?; [ "$w" -eq 0 ] && [ -s "$EVID/walk-B.txt" ] || STOP; s=0; sed -E 's/^([^:]+:[0-9]+):.*$/\1/' "$EVID/walk-B.txt" > "$EVID/walk-B.inv" || s=$?; [ "$s" -eq 0 ] || STOP; o=0; sort "$EVID/walk-B.inv" > "$EVID/walk-B.sorted" || o=$?; [ "$o" -eq 0 ] || STOP; d=0; diff "$EVID/walk-B.expected" "$EVID/walk-B.sorted" > "$EVID/walk-B.delta" || d=$?; [ "$d" -eq 0 ] || STOP
for a in '.globs = {"projects/*/*.jsonl"}' '.path = root / "projects"' '    std::vector<Store> stores;' 'const Inventory& claude_inventory()'; do g=0; k=$(grep -c -F -- "$a" src/adapters/claude_code/claude_code.cpp) || g=$?; [ "$g" -le 1 ] && [ "$k" -eq 1 ] || STOP; printf '%s -> %s\n' "$a" "$k"; done > "$EVID/anchors-at-C.txt"; [ -s "$EVID/anchors-at-C.txt" ] || STOP
g=0; k=$(grep -c -F '    "claude-code": ("CLAUDE_CONFIG_DIR",),' harness/bivharness/e3.py) || g=$?; [ "$g" -le 1 ] && [ "$k" -eq 1 ] || STOP; g=0; k=$(grep -c -F '    "claude-code": ("projects",),' harness/bivharness/e3.py) || g=$?; [ "$g" -le 1 ] && [ "$k" -eq 1 ] || STOP
g=0; k=$(grep -c -F '08480a19a7194f79078d01091f2f24d7d23abb8483c7a2bff0138d6de52e6d5d' harness/bivharness/e3.py) || g=$?; [ "$g" -le 1 ] && [ "$k" -eq 1 ] || STOP; h=0; shasum -a 256 src/adapters/codex/codex.cpp > "$EVID/codex-at-C.sha" || h=$?; [ "$h" -eq 0 ] || STOP; g=0; k=$(grep -c -F "$(cut -d' ' -f1 "$EVID/codex-at-C.sha")" "$EVID/base-hashes.txt") || g=$?; [ "$g" -le 1 ] && [ "$k" -eq 1 ] || STOP
n=0; .venv-harness/bin/python "$EVID/h_fidelity.py" harness/selftest > "$EVID/fidelity-pre-H.txt" 2>&1 || n=$?; printf 'fidelity_pre_rc=%s\n' "$n" > "$EVID/fidelity-pre-H.rc"; [ "$n" -eq 5 ] || STOP
echo "done: Step 0: preconditions, the WALK "
a=0; python3 "$EVID/h_stub.py" harness/selftest/stub_biv.py > "$EVID/h-stub.out" 2>&1 || a=$?; [ "$a" -eq 0 ] && [ -s "$EVID/h-stub.out" ] || STOP
b=0; python3 "$EVID/h_test.py" harness/selftest/test_store_isolation.py > "$EVID/h-test.out" 2>&1 || b=$?; [ "$b" -eq 0 ] && [ -s "$EVID/h-test.out" ] || STOP
c=0; python3 "$EVID/h_e3pin.py" harness/bivharness/e3.py src/adapters/claude_code/claude_code.cpp > "$EVID/h-e3pin.out" 2>&1 || c=$?; [ "$c" -eq 0 ] && [ -s "$EVID/h-e3pin.out" ] || STOP
g=0; k=$(grep -c -F 'new=4e105052a17b7e0d99bfeca28ac45cac1f6ed3c5ba0e9ba9ec62a34e530a3a51' "$EVID/h-e3pin.out") || g=$?; [ "$g" -le 1 ] && [ "$k" -eq 1 ] || STOP
echo "done: Step 1: the three edits"
n=0; .venv-harness/bin/python "$EVID/h_fidelity.py" harness/selftest > "$EVID/fidelity-H.txt" 2>&1 || n=$?; printf 'fidelity_rc=%s\n' "$n" > "$EVID/fidelity-H.rc"; [ "$n" -eq 0 ] && [ -s "$EVID/fidelity-H.txt" ] || STOP
echo "done: Step 2: L1 fidelity at the H stu"
s=0; git status --porcelain > "$EVID/status-pre-H-commit.txt" || s=$?; [ "$s" -eq 0 ] && [ -s "$EVID/status-pre-H-commit.txt" ] || STOP; printf ' M harness/bivharness/e3.py\n M harness/selftest/stub_biv.py\n M harness/selftest/test_store_isolation.py\n' > "$EVID/status-pre-H-commit.expected"; d=0; diff "$EVID/status-pre-H-commit.expected" "$EVID/status-pre-H-commit.txt" > "$EVID/status-pre-H-commit.delta" || d=$?; [ "$d" -eq 0 ] || STOP
r=0; git diff --numstat > "$EVID/H.numstat" || r=$?; [ "$r" -eq 0 ] && [ -s "$EVID/H.numstat" ] || STOP; printf '1\t1\tharness/bivharness/e3.py\n9\t5\tharness/selftest/stub_biv.py\n2\t2\tharness/selftest/test_store_isolation.py\n' > "$EVID/H.numstat.expected"; d=0; diff "$EVID/H.numstat.expected" "$EVID/H.numstat" > "$EVID/H.numstat.delta" || d=$?; [ "$d" -eq 0 ] || STOP
r=0; git diff -U0 -- harness/bivharness/e3.py > "$EVID/e3-H.diff" || r=$?; [ "$r" -eq 0 ] && [ -s "$EVID/e3-H.diff" ] || STOP; g=0; n=$(grep -c -E '^[-+][^-+]' "$EVID/e3-H.diff") || g=$?; [ "$g" -eq 0 ] && [ "$n" -eq 2 ] || STOP; g=0; m=$(grep -c -E '^[-+]        "[0-9a-f]{64}",$' "$EVID/e3-H.diff") || g=$?; [ "$g" -eq 0 ] && [ "$m" -eq 2 ] || STOP; g=0; k=$(grep -c -F '@@ -75 +75 @@' "$EVID/e3-H.diff") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP
g=0; k=$(grep -c 'NAMED MUTANT' harness/selftest/test_store_isolation.py) || g=$?; [ "$g" -le 1 ] && [ "$k" -eq 7 ] || STOP; g=0; k=$(grep -c '^def test_' harness/selftest/test_store_isolation.py) || g=$?; [ "$g" -le 1 ] && [ "$k" -eq 11 ] || STOP; printf 'markers=7 tests=11\n' > "$EVID/inventory-H.txt"
g=0; k=$(grep -c -F '08480a19a7194f79078d01091f2f24d7d23abb8483c7a2bff0138d6de52e6d5d' harness/bivharness/e3.py) || g=$?; [ "$g" -le 1 ] && [ "$k" -eq 1 ] || STOP
echo "done: Step 3: fence proofs on the work"
t=0; (cd harness && "${OBS_ENV[@]}" ../.venv-harness/bin/python -m pytest selftest/test_store_isolation.py -q -p no:cacheprovider) > "$EVID/pytest-store-isolation-H.log" 2>&1 || t=$?; printf 'pytest_si_rc=%s\n' "$t" > "$EVID/pytest-store-isolation-H.rc"; [ "$t" -eq 0 ] || STOP; g=0; k=$(grep -c -E '^11 passed' "$EVID/pytest-store-isolation-H.log") || g=$?; [ "$g" -le 1 ] && [ "$k" -eq 1 ] || STOP
t=0; (cd harness && "${OBS_ENV[@]}" ../.venv-harness/bin/python -m pytest selftest -q -p no:cacheprovider) > "$EVID/pytest-selftest-H.log" 2>&1 || t=$?; printf 'pytest_selftest_rc=%s\n' "$t" > "$EVID/pytest-selftest-H.rc"; [ "$t" -eq 0 ] || STOP
echo "done: Step 4: the targeted selftest at"
printf "harness: scratch H\n\nCo-Authored-By: Claude Fable 5.1 <noreply@anthropic.com>\n" > "$EVID/message-H.txt"
git add harness/bivharness/e3.py harness/selftest/stub_biv.py harness/selftest/test_store_isolation.py && git commit -q -F "$EVID/message-H.txt"
H=$(git rev-parse HEAD); printf '%s\n' "$H" > "$EVID/H.txt"; [ -s "$EVID/H.txt" ] || STOP; e=0; git cat-file -e "${H}^{commit}" || e=$?; [ "$e" -eq 0 ] || STOP; [ "$(git rev-parse "${H}^")" = "$C" ] || STOP
echo "done: step5 H=$(cat "$EVID/H.txt")"
r=0; git diff --numstat "$C" "$H" > "$EVID/c-to-h.numstat" || r=$?; [ "$r" -eq 0 ] && [ -s "$EVID/c-to-h.numstat" ] || STOP; d=0; diff "$EVID/H.numstat.expected" "$EVID/c-to-h.numstat" > "$EVID/c-to-h.numstat.delta" || d=$?; [ "$d" -eq 0 ] || STOP
q=0; git diff --quiet "$C" "$H" -- . ':(exclude)harness/' || q=$?; [ "$q" -eq 0 ] || STOP
[ "$(git rev-parse "${H}^^")" = bbf297e36a38a1fab8c2675f945098a0633f9f8b ] || STOP; c=0; n=$(git rev-list --count "origin/main..${H}") || c=$?; [ "$c" -eq 0 ] && [ "$n" -eq 2 ] || STOP
s=0; git status --porcelain > "$EVID/status-post-H.txt" || s=$?; [ "$s" -eq 0 ] && [ ! -s "$EVID/status-post-H.txt" ] || STOP
echo "done: step6"
mkdir -p "$EVID/C" "$EVID/H/rp"
cp /var/folders/hq/f0qq8v_103q9y8prfn20rzx80000gn/T/r450-evidence-16Y21z/B-cells.txt "$EVID/C-cells.txt"
sed -E "s/\$/ xml_sha256=deadbeef/" "$EVID/C-cells.txt" > "$EVID/C/tuples-macos.txt"; cp "$EVID/C/tuples-macos.txt" "$EVID/C/tuples-linux.txt"; cp "$EVID/C/tuples-macos.txt" "$EVID/H/tuples-macos.txt"; cp "$EVID/C/tuples-macos.txt" "$EVID/H/tuples-linux.txt"
q=0; python3 "$EVID/gate.py" "$EVID/C-cells.txt" "$EVID/C/tuples-macos.txt" "$EVID/C/tuples-linux.txt" "$EVID/H/tuples-macos.txt" "$EVID/H/tuples-linux.txt" > "$EVID/H/gate-equality-H.txt" || q=$?; printf 'gate_H_rc=%s\n' "$q" > "$EVID/H/gate-H.rc"; [ "$q" -eq 0 ] && [ -s "$EVID/H/gate-equality-H.txt" ] || STOP
echo "done: task6 step3 $(awk "END{print NR}" "$EVID/H/gate-equality-H.txt") lines"
cp "$(cat /tmp/r450-rp-resolved-dir.txt)/rp-mutants.log" "$EVID/H/rp/rp-mutants.log"
g=0; k=$(grep -c -F 'ALL FOUR MUTANTS RED ON EXACTLY THEIR OWN LOCATOR' "$EVID/H/rp/rp-mutants.log") || g=$?; [ "$g" -le 1 ] && [ "$k" -eq 1 ] || STOP; g=0; k=$(grep -c -F "MUTANT HOME: status=fail leak_tags=['HOME']" "$EVID/H/rp/rp-mutants.log") || g=$?; [ "$g" -le 1 ] && [ "$k" -eq 1 ] || STOP; g=0; k=$(grep -c -E '^isolation-leak HOME: .*0d15ea5e-0002-4000-8000-0000000c1a0d' "$EVID/H/rp/rp-mutants.log") || g=$?; [ "$g" -le 1 ] && [ "$k" -ge 1 ] || STOP; g=0; k=$(grep -c -E '^isolation-leak HOME: .*0d15ea5e-0001-4000-8000-00000000c0de' "$EVID/H/rp/rp-mutants.log") || g=$?; [ "$g" -le 1 ] && [ "$k" -ge 1 ] || STOP
echo "done: task6 step4 greps"
echo "REHEARSAL-COMPLETE shell=$0 EVID=$EVID S=$S"
