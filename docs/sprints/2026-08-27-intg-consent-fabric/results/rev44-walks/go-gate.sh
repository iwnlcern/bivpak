set -u
STOP() { printf 'STOP-task-10 line=%s\n' "${BASH_LINENO[0]}" >&2; exit 1; }
PIPEOK() { local st=("${PIPESTATUS[@]}"); local k; for k in "${st[@]}"; do [ "$k" -eq 0 ] || { printf 'STOP-task-10 pipe=%s stage-status=%s line=%s\n' "$1" "${st[*]}" "${BASH_LINENO[0]}" >&2; exit 1; }; done; }
H=cb19326a5596bf30eab2ec2b9baeda0bc77be895; MAIN=/Users/jack/Programming/bivpak
# Step 1 — the GO relay and the owner set
[ -s "$RUNNERS/task-10-go.txt" ] || STOP; a=0; ng=$(awk 'END { print NR }' "$RUNNERS/task-10-go.txt") || a=$?; [ "$a" -eq 0 ] && [ "$ng" -eq 1 ] || STOP; GO=$(sed -n '1p' "$RUNNERS/task-10-go.txt") || STOP; [ -s "$GO" ] || STOP
GOD=$(cd "$(dirname "$GO")" && pwd -P) || STOP; RR=$(cd "$MAIN/.relays/intg/intg-substep2b" && pwd -P) || STOP; [ "$GOD" = "$RR" ] || STOP
GOB=$(basename "$GO") || STOP; case "$GOB" in SITREP-pair-planner-[0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9]-[0-9][0-9][0-9][0-9][0-9][0-9].md) :;; *) STOP;; esac
g=0; k=$(grep -c -F -- "intg-substep2b/$GOB" "$MAIN/.relays/intg/INDEX.md") || g=$?; [ "$g" -eq 0 ] && [ "$k" -ge 1 ] || STOP
for pat in '^FROM: intg\.pair-planner$' '^TO: intg\.pair-implementer$' '^PHASE: SITREP$' '^TASK10_GO: yes$'; do g=0; k=$(grep -c -E "$pat" "$GO") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP; done
g=0; k=$(grep -c -x -F -- "TASK10_H: $H" "$GO") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP
g=0; grep -E '^OWNER_REVIEW_H: [^ |]+ \| FROM=m-(1|3|4)\.(planner|implementer) \| VERDICT=no-red$' "$GO" > "$EVID/work/owner-lines.txt" || g=$?; [ "$g" -eq 0 ] || STOP
a=0; nl=$(awk 'END { print NR }' "$EVID/work/owner-lines.txt") || a=$?; [ "$a" -eq 0 ] && [ "$nl" -eq 3 ] || STOP
g=0; n1=$(grep -c -F ' | FROM=m-1.' "$EVID/work/owner-lines.txt") || g=$?; [ "$g" -le 1 ] || STOP; g=0; n3=$(grep -c -F ' | FROM=m-3.' "$EVID/work/owner-lines.txt") || g=$?; [ "$g" -le 1 ] || STOP; g=0; n4=$(grep -c -F ' | FROM=m-4.' "$EVID/work/owner-lines.txt") || g=$?; [ "$g" -le 1 ] || STOP
[ "$n1" -eq 1 ] && [ "$n3" -eq 1 ] && [ "$n4" -eq 1 ] || STOP
s=0; sed -E 's/^OWNER_REVIEW_H: ([^ |]+) \| .*$/\1/' "$EVID/work/owner-lines.txt" > "$EVID/work/owner-paths.txt" || s=$?; [ "$s" -eq 0 ] || STOP; s=0; LC_ALL=C sort -u "$EVID/work/owner-paths.txt" > "$EVID/work/owner-paths.uniq" || s=$?; [ "$s" -eq 0 ] || STOP
a=0; nu=$(awk 'END { print NR }' "$EVID/work/owner-paths.uniq") || a=$?; [ "$a" -eq 0 ] || STOP
[ "$nu" -eq 3 ] || STOP
PDC=$(cd "$MAIN/../pdc/master/relays" && pwd -P) || STOP
: > "$EVID/task-10-go.txt"
while IFS= read -r line; do
  RP=$(printf '%s\n' "$line" | sed -n -E 's/^OWNER_REVIEW_H: ([^ |]+) \| FROM=([^ |]+) \| VERDICT=no-red$/\1/p'); PIPEOK owner-path; RF=$(printf '%s\n' "$line" | sed -n -E 's/^OWNER_REVIEW_H: [^ |]+ \| FROM=([^ |]+) \| VERDICT=no-red$/\1/p'); PIPEOK owner-from; [ -n "$RP" ] && [ -n "$RF" ] || STOP
  case "$RP" in /*) R=$RP;; *) R=$MAIN/$RP;; esac; [ -s "$R" ] || STOP; RD=$(cd "$(dirname "$R")" && pwd -P) || STOP; case "$RD" in "$PDC"/*) :;; *) STOP;; esac
  g=0; k=$(grep -c -x -F -- "FROM: $RF" "$R") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP
  g=0; k=$(grep -c -E '^PHASE: [A-Z-]+$' "$R") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP
  g=0; k=$(grep -c -x -F -- "S2B_REVIEW_OBJECT: H=$H" "$R") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP
  g=0; k=$(grep -c -E '^S2B_REVIEW_SCOPE: .+$' "$R") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP
  g=0; k=$(grep -c -x -F -- 'S2B_REVIEW_VERDICT: no-red' "$R") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP
  g=0; k=$(grep -c -i -E '^([A-Z0-9_]*VERDICT|STATUS): *(must-revise|reject|reject-narrow|red|blocked|pending|hold|human-decision-required)' "$R") || g=$?; [ "$g" -eq 1 ] && [ "$k" -eq 0 ] || STOP
  printf 'owner_review=%s FROM=%s\n' "$R" "$RF" >> "$EVID/task-10-go.txt" || STOP
done < "$EVID/work/owner-lines.txt"
echo GO-GATE-OK
