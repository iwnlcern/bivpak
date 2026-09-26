#!/bin/bash
set -u
W=/private/tmp/claude-501/-Users-jack-Programming-bivpak/6fecc389-d499-4128-a827-a4138f47bce6/scratchpad/r38/vwalk; G=/private/tmp/claude-501/-Users-jack-Programming-bivpak/6fecc389-d499-4128-a827-a4138f47bce6/scratchpad/r38; E=/Users/jack/Programming/bivpak-evidence/s2b-intg-substep2b-impl-1-y3iCLB; RR=/Users/jack/Programming/bivpak-evidence/s2b-runners-aY2Suc; CASE=$1; SNIP=${SNIP:-$W/snip.sh}; PLANF=${PLANF:-$G/rev38.md}
[ "$(awk 'END{print NR}' "$SNIP")" -ge 9 ] || { echo WALK-INVALID; exit 9; }
R=$W/runs/$CASE; rm -rf "$R"; mkdir -p "$R/cnt" "$R/home/work" "$R/run"; M=$R/home; cp -p $E/series_verdict.py "$M/"; cp -p $RR/plan_blocks.py "$R/run/"; printf '%s\n' "$PLANF" > "$R/run/plan-path.txt"
BD=09b6cb7612907972bb9cf340a8ffcbf406a71da1194d034ce45c85de6127d452
python3 $RR/plan_blocks.py extract $G/rev38.md series_verdict.py > "$R/good.py"
case "$CASE" in
  present-good) cp -p "$R/good.py" "$M/series_verdict.rev37.py";;
  present-old) cp -p $E/series_verdict.py "$M/series_verdict.rev37.py";;
  symlink) ln -s "$R/good.py" "$M/series_verdict.rev37.py";;
  dangling) ln -s "$R/nowhere" "$M/series_verdict.rev37.py";;
  plan-rev36) printf '%s\n' "$G/../r37/rev36.md" > "$R/run/plan-path.txt";;
  plan-missing) printf '%s\n' "$R/none.md" > "$R/run/plan-path.txt";;
  stale-unique-stage) printf 'stale\n' > "$M/work/series_verdict.rev37.AbC123";;
  fixed-stage-regular) printf 'stale fixed\n' > "$M/work/series_verdict.rev37.stage";;
  fixed-stage-symlink|ctl-rev37-fixed-stage-symlink) printf 'outside-sentinel\n' > "$R/sentinel"; ln -s "$R/sentinel" "$M/work/series_verdict.rev37.stage";;
esac
snap() { (cd "$M/work" && ls -A | LC_ALL=C sort | while read -r n; do if [ -L "$n" ]; then echo "l $n"; else echo "f $n $(shasum -a 256 "$n" | cut -c1-12)"; fi; done); }
snap > "$R/work.pre"
run() { ( cd "$M" && env PATH="$W/shim:$PATH" PWALK_CNT="$R/cnt" MV_FAIL_AT="${MV_FAIL_AT:-0}" PY_FAIL_AT="${PY_FAIL_AT:-0}" EVID="$M" RUNNERS="$R/run" bash -c 'set -u; set -o pipefail; STOP() { printf "STOP-task-9 line=%s\n" "${BASH_LINENO[0]}" >&2; exit 1; }; source "$1"; echo DONE' _ "$SNIP" > "$R/out" 2> "$R/err"; echo $? ); }
rc=$(run)
if [ "$CASE" = pyfail-then-rerun ]; then rm -f "$R/cnt/"*; rc2=$(PY_FAIL_AT=0 run); rc="$rc,then=$rc2"; fi
snap > "$R/work.post"
f=absent; if [ -L "$M/series_verdict.rev37.py" ]; then f=symlink; elif [ -f "$M/series_verdict.rev37.py" ]; then [ "$(shasum -a 256 "$M/series_verdict.rev37.py" | cut -d' ' -f1)" = $BD ] && f=pinned || f=OTHER-BYTES; fi
t0=$(cmp -s $E/series_verdict.py "$M/series_verdict.py" && echo intact || echo CHANGED)
pre_kept=$(comm -23 "$R/work.pre" "$R/work.post" | wc -l | tr -d ' '); new=$(comm -13 "$R/work.pre" "$R/work.post" | wc -l | tr -d ' ')
sent=na; [ -f "$R/sentinel" ] && sent=$(tr -d '\n' < "$R/sentinel" | cut -c1-20)
printf 'case=%s rc=%s done=%s rev37_file=%s task0_copy=%s work_entries_lost=%s work_entries_new=%s sentinel=%s stop="%s"\n' "$CASE" "$rc" "$(grep -c DONE "$R/out")" "$f" "$t0" "$pre_kept" "$new" "$sent" "$(grep -m1 -o 'STOP-task-9.*' "$R/err")"
