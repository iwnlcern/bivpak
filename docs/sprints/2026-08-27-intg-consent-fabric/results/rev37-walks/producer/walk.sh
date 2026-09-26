#!/bin/bash
set -u
W=/private/tmp/claude-501/-Users-jack-Programming-bivpak/6fecc389-d499-4128-a827-a4138f47bce6/scratchpad/r37/vwalk; G=/private/tmp/claude-501/-Users-jack-Programming-bivpak/6fecc389-d499-4128-a827-a4138f47bce6/scratchpad/r37; E=/Users/jack/Programming/bivpak-evidence/s2b-intg-substep2b-impl-1-y3iCLB; RR=/Users/jack/Programming/bivpak-evidence/s2b-runners-aY2Suc; CASE=$1; SNIP=${SNIP:-$W/snip.sh}
[ "$(awk 'END{print NR}' "$SNIP")" -ge 9 ] || { echo WALK-INVALID; exit 9; }
R=$W/runs/$CASE; rm -rf "$R"; mkdir -p "$R/cnt" "$R/home/work" "$R/run"; M=$R/home; cp -p $E/series_verdict.py "$M/"; cp -p $RR/plan_blocks.py "$R/run/"; printf '%s\n' "$G/rev37.md" > "$R/run/plan-path.txt"
BD=09b6cb7612907972bb9cf340a8ffcbf406a71da1194d034ce45c85de6127d452
python3 $RR/plan_blocks.py extract $G/rev37.md series_verdict.py > "$R/good.py"
case "$CASE" in
  present-good) cp -p "$R/good.py" "$M/series_verdict.rev37.py";;
  present-old) cp -p $E/series_verdict.py "$M/series_verdict.rev37.py";;
  symlink) ln -s "$R/good.py" "$M/series_verdict.rev37.py";;
  dangling) ln -s "$R/nowhere" "$M/series_verdict.rev37.py";;
  plan-rev36|mut-plan-rev36) printf '%s\n' "$G/rev36.md" > "$R/run/plan-path.txt";;
  plan-missing) printf '%s\n' "$R/none.md" > "$R/run/plan-path.txt";;
esac
rc=$( cd "$M" && env PATH="$W/shim:$PATH" PWALK_CNT="$R/cnt" MV_FAIL_AT="${MV_FAIL_AT:-0}" PY_FAIL_AT="${PY_FAIL_AT:-0}" EVID="$M" RUNNERS="$R/run" bash -c 'set -u; set -o pipefail; STOP() { printf "STOP-task-9 line=%s\n" "${BASH_LINENO[0]}" >&2; exit 1; }; source "$1"; echo DONE' _ "$SNIP" > "$R/out" 2> "$R/err"; echo $? )
f=absent; if [ -L "$M/series_verdict.rev37.py" ]; then f=symlink; elif [ -f "$M/series_verdict.rev37.py" ]; then [ "$(shasum -a 256 "$M/series_verdict.rev37.py" | cut -d' ' -f1)" = $BD ] && f=pinned || f=OTHER-BYTES; fi
t0=$(cmp -s $E/series_verdict.py "$M/series_verdict.py" && echo intact || echo CHANGED)
printf 'case=%s rc=%s done=%s rev37_file=%s task0_copy=%s stage_left=%s stop="%s"\n' "$CASE" "$rc" "$(grep -c DONE "$R/out")" "$f" "$t0" "$([ -e "$M/work/series_verdict.rev37.stage" ] && echo yes || echo no)" "$(grep -m1 -o 'STOP-task-9.*' "$R/err")"
