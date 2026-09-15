#!/usr/bin/env bash
# task-3.sh — materialized VERBATIM from the plan's BLOCK task-3 by plan_blocks.py extract; proved by plan_blocks.py check; invoked by run-task.sh 3
set -u
STOP() { printf 'STOP-task-3 line=%s\n' "${BASH_LINENO[0]}" >&2; exit 1; }
RUNNERS=${1-}; [ -n "$RUNNERS" ] && [ -d "$RUNNERS" ] || exit 1
[ "$0" = "$RUNNERS/task-3.sh" ] || { printf 'STOP-task-3-invoked-off-path %s\n' "$0" >&2; exit 1; }
t=0; tail -n 1 "$RUNNERS/proof-3.txt" > "$RUNNERS/task-3.proof-tail" 2>/dev/null || t=$?; [ "$t" -eq 0 ] && [ "$(cat "$RUNNERS/task-3.proof-tail")" = rc=0 ] || { printf 'STOP-task-3-unproved\n' >&2; exit 1; }
h=0; shasum -a 256 "$0" > "$RUNNERS/task-3.self.sha256" || h=$?; [ "$h" -eq 0 ] && [ -s "$RUNNERS/task-3.self.sha256" ] || exit 1
a=$(cut -d' ' -f1 "$RUNNERS/task-3.self.sha256") || exit 1; b=$(cut -d' ' -f1 "$RUNNERS/task-3.sha256") || exit 1; [ -n "$a" ] && [ "$a" = "$b" ] || { printf 'STOP-task-3-bytes-differ\n' >&2; exit 1; }
EVID=${2-}; [ -n "$EVID" ] && [ -d "$EVID" ] || exit 1; [ "$EVID" = "$(cat "$RUNNERS/evid.txt")" ] || exit 1
c=0; cp -p "$RUNNERS/task-3.sh" "$RUNNERS/proof-3.txt" "$RUNNERS/task-3.sha256" "$RUNNERS/task-3.invocation.txt" "$EVID/runners/" || c=$?; [ "$c" -eq 0 ] || exit 1
# Runner plumbing (Task 3)
WORKTREE=/Users/jack/Programming/bivpak-intg-r449-line1-selection
MAIN=/Users/jack/Programming/bivpak
B=4cf135ee97f57021c5fc5fd5343de6f655fb0d24
cd "$WORKTREE" || STOP
v=0; (cd "$EVID" && shasum -a 256 -c helpers.sha256 > helpers.verify-3.txt 2>&1) || v=$?; [ "$v" -eq 0 ] || STOP
[ -s "$EVID/observer-unset-names.txt" ] || STOP
OBS_ENV=(env); while read -r n; do OBS_ENV+=(-u "$n"); done < "$EVID/observer-unset-names.txt"
H=$(cat "$EVID/H.txt") || STOP; e=0; git cat-file -e "${H}^{commit}" || e=$?; [ "$e" -eq 0 ] || STOP; [ "$(git rev-parse HEAD)" = "$H" ] || STOP; s=0; git status --porcelain > "$EVID/H/status-pre-3.txt" || s=$?; [ "$s" -eq 0 ] && [ ! -s "$EVID/H/status-pre-3.txt" ] || STOP
# Step 1
b=0; cmake --build --preset ci-macos > "$EVID/H/build-H-3.log" 2>&1 || b=$?; [ "$b" -eq 0 ] || STOP
rc1=0; ctest --preset ci-macos -R '^harness-selftest$' > "$EVID/H/discriminator-as-is.log" 2>&1 || rc1=$?
rc2=0; "${OBS_ENV[@]}" ctest --preset ci-macos -R '^harness-selftest$' > "$EVID/H/discriminator-unset.log" 2>&1 || rc2=$?
present_count=$(cut -d= -f2 "$EVID/observer-present-count.txt")
iff=FAIL; hygiene=FAIL; [ "$rc2" -eq 0 ] && hygiene=PASS; if { [ "$present_count" -gt 0 ] && [ "$rc1" -ne 0 ]; } || { [ "$present_count" -eq 0 ] && [ "$rc1" -eq 0 ]; }; then iff=PASS; fi; printf 'rc1=%s rc2=%s present_count=%s iff=%s hygiene=%s\n' "$rc1" "$rc2" "$present_count" "$iff" "$hygiene" > "$EVID/H/discriminator-predicate.txt"; [ "$iff" = PASS ] && [ "$hygiene" = PASS ] || STOP
r=0; "${OBS_ENV[@]}" ctest --preset ci-macos -E '^safety-hardening$' --output-on-failure > "$EVID/H/ctest-macos-H.log" 2>&1 || r=$?; printf 'ctest_macos_H_rc=%s\n' "$r" > "$EVID/H/ctest-macos-H.rc"; [ "$r" -eq 0 ] || STOP
for binary in biv_subprocess_tests biv_repo_git_tests biv_repo_engine_tests biv_tests biv_probe_tests; do x=0; "${OBS_ENV[@]}" "./build/ci-macos/$binary" -r xml > "$EVID/H/$binary-macos.xml" 2> "$EVID/H/$binary-macos.stderr" || x=$?; printf '%s\n' "$x" > "$EVID/H/$binary-macos.rc"; [ -s "$EVID/H/$binary-macos.xml" ] || STOP; done
h=0; shasum -a 256 "$EVID"/H/*-macos.xml > "$EVID/H/xml-sha256-macos.txt" || h=$?; [ "$h" -eq 0 ] && [ -s "$EVID/H/xml-sha256-macos.txt" ] || STOP
u=0; python3 "$EVID/tuples.py" macos "$EVID"/H/biv_subprocess_tests-macos.xml "$EVID"/H/biv_repo_git_tests-macos.xml "$EVID"/H/biv_repo_engine_tests-macos.xml "$EVID"/H/biv_tests-macos.xml "$EVID"/H/biv_probe_tests-macos.xml > "$EVID/H/tuples-macos.txt" || u=$?; [ "$u" -eq 0 ] && [ -s "$EVID/H/tuples-macos.txt" ] || STOP
g=0; k=$(grep -c '<Section name="R-4.49' "$EVID/H/biv_tests-macos.xml") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 9 ] || STOP
r=0; "${OBS_ENV[@]}" ctest --preset ci-macos --output-on-failure > "$EVID/H/scout-macos.log" 2>&1 || r=$?; printf '%s\n' "$r" > "$EVID/H/scout-macos.rc"; [ "$r" -ne 0 ] && [ -s "$EVID/H/scout-macos.log" ] || STOP; f=0; grep -E '^[[:space:]]+[0-9]+ - .*\(Failed\)' "$EVID/H/scout-macos.log" > "$EVID/H/scout-macos.failed" || f=$?; [ "$f" -eq 0 ] && [ -s "$EVID/H/scout-macos.failed" ] || STOP; s=0; sed -E 's/^[[:space:]]*[0-9]+ - ([^ ]+) .*/\1/' "$EVID/H/scout-macos.failed" > "$EVID/H/scout-macos.failed-names" || s=$?; [ "$s" -eq 0 ] && [ -s "$EVID/H/scout-macos.failed-names" ] || STOP; printf 'safety-hardening\n' > "$EVID/H/scout-macos.expected"; d=0; diff "$EVID/H/scout-macos.expected" "$EVID/H/scout-macos.failed-names" > "$EVID/H/scout-macos.failed.delta" || d=$?; [ "$d" -eq 0 ] || STOP
c=0; cat -- "$EVID/H/ctest-macos-H.log" "$EVID/H/scout-macos.log" "$EVID/H/discriminator-as-is.log" "$EVID/H/discriminator-unset.log" "$EVID"/H/*-macos.stderr > "$EVID/H/all-logs-H-macos.txt" || c=$?; [ "$c" -eq 0 ] && [ -f "$EVID/H/all-logs-H-macos.txt" ] || STOP; g=0; secret_hits=$(grep -c -E 'sk-[A-Za-z0-9]{8,}|-----BEGIN [A-Z ]*PRIVATE KEY|AKIA[0-9A-Z]{16}|ghp_[A-Za-z0-9]{20,}|xox[abprs]-' "$EVID/H/all-logs-H-macos.txt") || g=$?; [ "$g" -le 1 ] || STOP; printf 'pattern=census-alternation cat_rc=%s grep_rc=%s hits=%s\n' "$c" "$g" "$secret_hits" > "$EVID/H/token-scan-macos.txt"; [ "$secret_hits" -eq 0 ] || STOP
i=0; { printf 'run_id=H-macos-%s\nplatform=macos\nH=%s\n' "$H" "$H" && sw_vers && uname -m && printf '%s\n' 'observer_unset_names:' && cat "$EVID/observer-unset-names.txt" && printf '%s\n' 'observer_host_presence_names_only:' && cat "$EVID/observer-host-presence.txt" "$EVID/observer-present-count.txt" "$EVID/H/discriminator-predicate.txt" "$EVID/H/tuples-macos.txt" "$EVID/H/xml-sha256-macos.txt" "$EVID/H/token-scan-macos.txt"; } > "$EVID/H/run-identity-macos.txt" || i=$?; [ "$i" -eq 0 ] && [ -s "$EVID/H/run-identity-macos.txt" ] || STOP
# Step 2
p=0; "${OBS_ENV[@]}" python3 "$EVID/pack_run.py" "$WORKTREE/build/ci-macos/biv" "$EVID/work" H "$EVID/H" > "$EVID/H/pack-run.log" 2>&1 || p=$?; [ "$p" -eq 0 ] && [ -s "$EVID/H/pack-H.json" ] && [ -s "$EVID/H/time-H.txt" ] && [ -s "$EVID/work/ws/proj-H.bvpk" ] || STOP
m=0; python3 "$EVID/membership.py" "$EVID/work/ws/proj-H.bvpk" "$EVID/H/membership-H.json" > "$EVID/H/membership-H.log" 2>&1 || m=$?; [ "$m" -eq 0 ] && [ -s "$EVID/H/membership-H.json" ] || STOP
g=0; k=$(grep -c -F -- ' "count": 6,' "$EVID/H/membership-H.json") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP
d=0; diff "$EVID/B/membership-B.json" "$EVID/H/membership-H.json" > "$EVID/H/membership.delta" || d=$?; [ "$d" -eq 0 ] || STOP
g=0; k=$(grep -c -F 'SessionNoCwdRecord' "$EVID/H/pack-H.json") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 5 ] || STOP; printf 'no_cwd_record_warnings=%s\n' "$k" > "$EVID/H/no-cwd-count.txt"; c=0; cmp "$EVID/B/no-cwd-count.txt" "$EVID/H/no-cwd-count.txt" || c=$?; [ "$c" -eq 0 ] || STOP
c=0; { printf 'LEG 3 cost receipt: biv pack over S (medians of three runs), macOS, B then H\n'; cat "$EVID/B/time-B.txt" "$EVID/H/time-H.txt"; printf 'membership_delta=empty no_cwd_record_warnings_equal=yes\n'; } > "$EVID/H/cost-receipt.txt" || c=$?; [ "$c" -eq 0 ] && [ -s "$EVID/H/cost-receipt.txt" ] || STOP
# Step 3
q=0; python3 "$EVID/cellgate.py" "$EVID/B-cells.txt" macos "$EVID/B/tuples-macos.txt" "$EVID/H/tuples-macos.txt" > "$EVID/H/count-gate-macos.txt" || q=$?; printf 'count_gate_macos_rc=%s\n' "$q" > "$EVID/H/count-gate-macos.rc"; [ "$q" -eq 0 ] && [ -s "$EVID/H/count-gate-macos.txt" ] || STOP
q=0; python3 "$EVID/skipset.py" "$EVID/B-cells.txt" "$EVID/H/tuples-macos.txt" macos > "$EVID/H/skipset-macos.txt" || q=$?; [ "$q" -eq 0 ] && [ -s "$EVID/H/skipset-macos.txt" ] || STOP
# Step 4
s=0; git status --porcelain > "$EVID/H/status-post-3.txt" || s=$?; [ "$s" -eq 0 ] && [ ! -s "$EVID/H/status-post-3.txt" ] || STOP; [ "$(git rev-parse HEAD)" = "$H" ] || STOP
s=0; git -C "$MAIN" status --porcelain -- . ':(exclude).relays' ':(exclude)docs/sprints' > "$EVID/status-main-post-3.txt" || s=$?; [ "$s" -eq 0 ] || STOP; d=0; diff "$EVID/status-initial.txt" "$EVID/status-main-post-3.txt" > "$EVID/status-main-post-3.delta" || d=$?; [ "$d" -eq 0 ] || STOP
exit 0
