#!/usr/bin/env bash
# task-8.sh — materialized VERBATIM from the plan's BLOCK task-8 by plan_blocks.py extract; proved by plan_blocks.py check; invoked by run-task.sh 8
set -u
STOP() { printf 'STOP-task-8 line=%s\n' "${BASH_LINENO[0]}" >&2; exit 1; }
RUNNERS=${1-}; [ -n "$RUNNERS" ] && [ -d "$RUNNERS" ] || exit 1
[ "$0" = "$RUNNERS/task-8.sh" ] || { printf 'STOP-task-8-invoked-off-path %s\n' "$0" >&2; exit 1; }
t=0; tail -n 1 "$RUNNERS/proof-8.txt" > "$RUNNERS/task-8.proof-tail" 2>/dev/null || t=$?; [ "$t" -eq 0 ] && [ "$(cat "$RUNNERS/task-8.proof-tail")" = rc=0 ] || { printf 'STOP-task-8-unproved\n' >&2; exit 1; }
h=0; shasum -a 256 "$0" > "$RUNNERS/task-8.self.sha256" || h=$?; [ "$h" -eq 0 ] && [ -s "$RUNNERS/task-8.self.sha256" ] || exit 1
a=$(cut -d' ' -f1 "$RUNNERS/task-8.self.sha256") || exit 1; b=$(cut -d' ' -f1 "$RUNNERS/task-8.sha256") || exit 1; [ -n "$a" ] && [ "$a" = "$b" ] || { printf 'STOP-task-8-bytes-differ\n' >&2; exit 1; }
EVID=${2-}; [ -n "$EVID" ] && [ -d "$EVID" ] || exit 1; [ "$EVID" = "$(cat "$RUNNERS/evid.txt")" ] || exit 1
c=0; cp -p "$RUNNERS/task-8.sh" "$RUNNERS/proof-8.txt" "$RUNNERS/task-8.sha256" "$RUNNERS/task-8.invocation.txt" "$EVID/runners/" || c=$?; [ "$c" -eq 0 ] || exit 1
# Runner plumbing (Task 8)
WORKTREE=/Users/jack/Programming/bivpak-intg-r450-discover-parity
cd "$WORKTREE" || STOP
v=0; (cd "$EVID" && shasum -a 256 -c helpers.sha256 > helpers.verify-8.txt 2>&1) || v=$?; [ "$v" -eq 0 ] || STOP
# Step 1
H=$(cat "$EVID/H.txt")
[ "$(git rev-parse HEAD)" = "$H" ] || STOP
[ "$(git rev-parse "${H}^")" = "$(cat "$EVID/C.txt")" ] || STOP
u=0; git remote get-url --push --all origin > "$EVID/push-url.txt" || u=$?; [ "$u" -eq 0 ] && [ -s "$EVID/push-url.txt" ] || STOP; a=0; n=$(awk 'END { print NR }' "$EVID/push-url.txt") || a=$?; [ "$a" -eq 0 ] && [ "$n" -eq 1 ] || STOP
l=0; git ls-remote --heads origin intg/r450-discover-parity-v2 > "$EVID/remote-branch-before.txt" || l=$?; [ "$l" -eq 0 ] && [ ! -s "$EVID/remote-branch-before.txt" ] || STOP
v=0; gh repo view --json visibility -q .visibility > "$EVID/visibility.txt" || v=$?; [ "$v" -eq 0 ] && [ "$(cat "$EVID/visibility.txt")" = PRIVATE ] || STOP
[ ! -x "$(git rev-parse --git-path hooks/pre-push)" ] || STOP
[ -f "$EVID/census-tree.delta" ] && [ ! -s "$EVID/census-tree.delta" ] && [ -f "$EVID/census-history.delta" ] && [ ! -s "$EVID/census-history.delta" ] || STOP
printf '%s %s\n' "$0" "${ZSH_VERSION:-${BASH_VERSION:-unknown}}" > "$EVID/shell.txt"
# Step 2
y=0; git push --dry-run --no-tags origin intg/r450-discover-parity-v2 > "$EVID/push-dry.txt" 2>&1 || y=$?; [ "$y" -eq 0 ] || STOP
g=0; k=$(grep -c -F 'intg/r450-discover-parity-v2 -> intg/r450-discover-parity-v2' "$EVID/push-dry.txt") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP
p=0; git push --no-tags origin intg/r450-discover-parity-v2 > "$EVID/push-stdout.txt" 2> "$EVID/push-stderr.txt" || p=$?; printf 'push_rc=%s\n' "$p" > "$EVID/push-rc.txt"
o=0; git ls-remote --heads origin intg/r450-discover-parity-v2 > "$EVID/remote-branch-after.txt" || o=$?; remote_after=$(cut -f1 "$EVID/remote-branch-after.txt")
if [ "$o" -ne 0 ]; then class=d; elif [ "$p" -eq 0 ] && [ "$remote_after" = "$H" ]; then class=a; elif [ "$p" -eq 0 ]; then class=e; elif [ "$remote_after" = "$H" ]; then class=c; elif [ -z "$remote_after" ]; then class=b; else class=e; fi; printf 'class=%s\n' "$class" > "$EVID/push-class.txt"
[ "$class" = a ] || STOP
# Step 3
w=0; { printf '%s\n\n' 'R-4.50 claude-discover parity — ONE PR, TWO COMMITS, TWO OWNERS (arm A of master 041131). SUPERSEDES PR #25: C 961b1ccd and H 8509157c were REWRITTEN as C-prime and H-prime (commit MESSAGES only — the Co-Authored-By trailer line removed per the operator ruling 164309; trees 1efd9ce2 / 4a6075c9 byte-identical; author and committer identity and dates preserved); PR #25 is to be closed UNMERGED by this runner'"'"'s next step, with a comment naming this PR (receipt pr25-close.rc); the old branch intg/r450-discover-parity is left in place.'; printf 'Rewrite: C_orig=%s C_new=%s H_orig=%s H_new=%s\n\n' "$(cat "$EVID/C-orig.txt")" "$(cat "$EVID/C.txt")" "$(cat "$EVID/H-orig.txt")" "$(cat "$EVID/H.txt")"; printf 'Design pins: m-2 fence rev2 m2-r450-discover-fence-rev2-20260903 sha256 f2216ee606a03b0b5b0b7f4562fed52a7349219c28990e6ee3e89b0cc25e8c6f; iso rev8 sha256 00046a657abd6c5792e3c6222c8690b39f1a773ecbc2473ca9af2845a95813af (live: iso rev13 sha256 f72919d984860684450d8394d74191a423f525fd5be787f64fe681dc7a13f9ce).\nPlan pin: intg-r450-discover-parity-plan-20260906 sha256 %s\n\n' "$(cat "$RUNNERS/plan-lock.txt")"; printf 'B=%s\nP=%s\nC=%s\nH=%s (H^ = C)\n\n' "$(sed -n 's/^B=//p' "$EVID/B.txt")" "$(cat "$EVID/P.txt")" "$(cat "$EVID/C.txt")" "$H"; printf 'C touched (numstat):\n'; cat "$EVID/touched.numstat"; printf '\nH touched (numstat):\n'; cat "$EVID/c-to-h.numstat.final"; printf '\nC tuples (macOS, Linux):\n'; cat "$EVID/C/tuples-macos.txt" "$EVID/C/tuples-linux.txt"; printf '\nH cell equality (gate.py):\n'; cat "$EVID/H/gate-equality-H.txt"; printf '\nLinux acceptance at H (two-outcome bar):\n'; cat "$EVID/H/linux-selftest-bar.txt"; printf '\nOwner reviews: of the ORIGINAL C 961b1ccd and H 8509157c — m-2 on C (V-CP-1..6; 053700) and m-3 on C'"'"'s two workflow lines (CG-R7.5) and on H (V-FT-1..8; 053914) — returned through master before PR #25 was opened; the REWRITTEN C-prime and H-prime this PR carries (the same trees) are PENDING their own owner re-reviews through master, which precede any merge packet or merge token.\n\nThis PR is the vehicle under R-4.51 clause (2); the evidence of record is the local suites, the Docker parity leg, the owner byte reviews (PENDING for C-prime and H-prime at this PR'"'"'s creation), and the operator'"'"'s condition-4 token — a red remote CI is cited nowhere. Merge is local under the operator'"'"'s token; the landing push of main follows the merge under the R-4.52 landing rule as the merge packet'"'"'s own step.\n'; } > "$EVID/pr-body.md" || w=$?; [ "$w" -eq 0 ] && [ -s "$EVID/pr-body.md" ] || STOP
q=0; gh pr create --base main --head intg/r450-discover-parity-v2 --title "adapters(claude): discover returns every store found (env + default), codex parity; count-gate cells transcribed" --body-file "$EVID/pr-body.md" > "$EVID/pr.txt" 2>&1 || q=$?; printf 'pr_rc=%s\n' "$q" > "$EVID/pr.rc"; [ "$q" -eq 0 ] && [ -s "$EVID/pr.txt" ] || STOP; new_url=$(tail -n 1 "$EVID/pr.txt"); [ -n "$new_url" ] || STOP; z=0; gh pr close 25 --comment "Superseded by $new_url. C 961b1ccd and H 8509157c were rewritten as $(cat "$EVID/C.txt") and $(cat "$EVID/H.txt") (commit messages only: the Co-Authored-By trailer line removed per the operator ruling 164309; trees byte-identical). Closed UNMERGED; the branch intg/r450-discover-parity is left in place at 8509157c (no force update, no deletion)." > "$EVID/pr25-close.txt" 2>&1 || z=$?; printf 'pr25_close_rc=%s\n' "$z" > "$EVID/pr25-close.rc"; [ "$z" -eq 0 ] && [ -s "$EVID/pr25-close.txt" ] || STOP
exit 0
