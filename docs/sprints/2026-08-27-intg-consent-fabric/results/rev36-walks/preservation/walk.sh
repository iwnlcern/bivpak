#!/bin/bash
# rev36 preservation walk on real-home mirrors: walk.sh <case> ; prints one verdict line
set -u
REAL=/Users/jack/Programming/bivpak-evidence/s2b-intg-substep2b-impl-1-y3iCLB
W=$(cd "$(dirname "$0")" && pwd -P); CASE=$1; SNIP=${SNIP:-$W/snippet.sh}
[ -s "$SNIP" ] && [ "$(awk 'END{print NR}' "$SNIP")" -ge 60 ] || { echo "case=$CASE WALK-INVALID snippet"; exit 9; }
R=$W/runs/$CASE; rm -rf "$R"; mkdir -p "$R/cnt"; M=$R/home; mkdir "$M"; for x in B H attempts work H0.txt helpers.verify-9.txt; do cp -Rp "$REAL/$x" "$M/$x"; done
REF=$W/ref; [ -d "$REF" ] || { mkdir -p "$REF/B"; cp -Rp "$REAL/H" "$REAL/H0.txt" "$REAL/helpers.verify-9.txt" "$REF/"; cp -Rp "$REAL/B" "$REF/Ball"; }
export PWALK_CNT=$R/cnt
PN=task9-H0-99136ca
setup() { case "$CASE" in
  pt-file) : > "$M/attempts/$PN";;
  pt-dir) mkdir "$M/attempts/$PN";;
  pt-symlink) mkdir "$R/elsewhere"; ln -s "$R/elsewhere" "$M/attempts/$PN";;
  pt-dangling) ln -s "$R/nowhere" "$M/attempts/$PN";;
  attempts-symlink) /bin/mv "$M/attempts" "$R/out"; ln -s "$R/out" "$M/attempts";;
  attempts-file) /bin/mv "$M/attempts" "$R/out"; : > "$M/attempts";;
  attempts-absent) /bin/mv "$M/attempts" "$R/out";;
  h-symlink) /bin/mv "$M/H" "$R/Hreal"; ln -s "$R/Hreal" "$M/H";;
  h0-two-lines) printf 'H0=99136ca635cd4c59b456606aed7d448e1c25a509\nextra\n' > "$M/H0.txt";;
  h0-bad-hex) printf 'H0=99136ca635cd\n' > "$M/H0.txt";;
  h0-symlink) /bin/mv "$M/H0.txt" "$R/H0real"; ln -s "$R/H0real" "$M/H0.txt";;
  helpers-absent) /bin/mv "$M/helpers.verify-9.txt" "$R/";;
  series-present) mkdir "$M/series";;
  h9-present) mkdir "$M/H9";;
  b-symlink) /bin/mv "$M/B" "$R/Breal"; ln -s "$R/Breal" "$M/B";;
  work-absent) /bin/mv "$M/work" "$R/";;
  t0-missing) /bin/mv "$M/B/tuples-macos.txt" "$R/";;
  t0-symlink) /bin/mv "$M/B/tuples-macos.txt" "$R/"; ln -s "$R/tuples-macos.txt" "$M/B/tuples-macos.txt";;
  t0-dir) /bin/mv "$M/B/tuples-macos.txt" "$R/"; mkdir "$M/B/tuples-macos.txt";;
  bleg-symlink) ln -s /nonexistent "$M/B/zz-dangling-leg";;
  bleg-dir) mkdir "$M/B/zz-leg-dir"; : > "$M/B/zz-leg-dir/f";;
  fresh-with-bleg) /bin/mv "$M/H" "$M/H0.txt" "$M/helpers.verify-9.txt" "$R/";;
  fresh-clean) /bin/mv "$M/H" "$M/H0.txt" "$M/helpers.verify-9.txt" "$R/"; mkdir "$R/bleg"; (cd "$M/B" && ls | grep -v -E -- '-macos\.(stderr|xml|txt)$|^(build|configure)-B\.log$|^run-rcs-macos\.txt$' | while read -r f; do /bin/mv "$f" "$R/bleg/"; done);;
  fresh-clean-empty-H) /bin/mv "$M/H" "$M/H0.txt" "$M/helpers.verify-9.txt" "$R/"; mkdir "$M/H"; mkdir "$R/bleg"; (cd "$M/B" && ls | grep -v -E -- '-macos\.(stderr|xml|txt)$|^(build|configure)-B\.log$|^run-rcs-macos\.txt$' | while read -r f; do /bin/mv "$f" "$R/bleg/"; done);;
  no-bleg-with-h0) mkdir "$R/bleg"; (cd "$M/B" && ls | grep -v -E -- '-macos\.(stderr|xml|txt)$|^(build|configure)-B\.log$|^run-rcs-macos\.txt$' | while read -r f; do /bin/mv "$f" "$R/bleg/"; done);;
  retry-after-success|yes|mv*|py*) :;;
esac; }
setup
snap() { ( cd "$M" && find . \( -type f -o -type l -o -type d \) -print | LC_ALL=C sort | while read -r p; do if [ -L "$p" ]; then echo "l $p $(readlink "$p")"; elif [ -f "$p" ]; then echo "f $p $(shasum -a 256 "$p" | cut -c1-64)"; else echo "d $p"; fi; done ); }
snap > "$R/snap.pre"
run() { ( cd "$M" && env PATH="$W/shim:$PATH" MV_FAIL_AT="${MV_FAIL_AT:-0}" MV_CORRUPT_AT="${MV_CORRUPT_AT:-0}" PY_FAIL_AT="${PY_FAIL_AT:-0}" EVID="$M" bash -c 'set -u; set -o pipefail; STOP() { printf "STOP-task-9 line=%s\n" "${BASH_LINENO[0]}" >&2; exit 1; }; source "$1"; echo SNIPPET-DONE' _ "$SNIP" ) > "$R/out.txt" 2> "$R/err.txt"; echo $?; }
rc=$(run)
if [ "$CASE" = retry-after-success ] && [ "$rc" -eq 0 ]; then rm -f "$R/cnt/"*; rc=$(run); fi
t0ok() { local d=$1; for f in $(cd "$REF/Ball" && ls | grep -E -- '-macos\.(stderr|xml|txt)$|^(build|configure)-B\.log$|^run-rcs-macos\.txt$'); do cmp -s "$REF/Ball/$f" "$d/$f" || { echo no; return; }; done; echo yes; }
same() { diff -r "$REF/H" "$1/H" >/dev/null 2>&1 && cmp -s "$REF/H0.txt" "$1/H0.txt" && cmp -s "$REF/helpers.verify-9.txt" "$1/helpers.verify-9.txt" && echo yes || echo no; }
blegcount() { if [ -d "$1" ]; then ls -A "$1" | grep -c -v -E -- '-macos\.(stderr|xml|txt)$|^(build|configure)-B\.log$|^run-rcs-macos\.txt$'; else echo na; fi; return 0; }
blegsame() { [ -d "$1" ] || { echo na; return; }; for f in $(cd "$REF/Ball" && ls | grep -v -E -- '-macos\.(stderr|xml|txt)$|^(build|configure)-B\.log$|^run-rcs-macos\.txt$'); do cmp -s "$REF/Ball/$f" "$1/$f" || { echo no; return; }; done; echo yes; }
PT=$M/attempts/$PN
orig=$(same "$M"); pub=no; [ -d "$PT" ] && [ ! -L "$PT" ] && pub=$(same "$PT")
man=na; [ -f "$PT/MANIFEST.pre" ] && { cmp -s "$PT/MANIFEST.pre" "$PT/MANIFEST.post" && man=pre==post || man=differ; }
stages=$(ls -d "$M"/attempts/stage-* 2>/dev/null | wc -l | tr -d ' ')
newH=na; [ -d "$M/H" ] && [ ! -L "$M/H" ] && newH="$(ls -A "$M/H" | wc -l | tr -d ' ')"; snap > "$R/snap.post"; unchanged=no; cmp -s "$R/snap.pre" "$R/snap.post" && unchanged=yes
bl=$(blegcount "$M/B"); pbl=$(blegcount "$PT/B"); t0=$(t0ok "$M/B"); bsame_pub=$(blegsame "$PT/B"); bsame_home=$(blegsame "$M/B")
rec=$(cat "$M/H/preserved-attempt.txt" 2>/dev/null | sed 's/manifest_sha256=[0-9a-f]*/manifest_sha256=<h>/')
done=$(grep -c SNIPPET-DONE "$R/out.txt"); printf 'done=%s case=%s rc=%s home_unchanged=%s originals_in_place=%s published=%s manifest=%s stages=%s newH=%s B_leg_home=%s B_leg_pub=%s t0_intact=%s bleg_bytes_pub=%s bleg_bytes_home=%s rec="%s" stop="%s"\n' "$done" "$CASE" "$rc" "$unchanged" "$orig" "$pub" "$man" "$stages" "$newH" "$bl" "$pbl" "$t0" "$bsame_pub" "$bsame_home" "$rec" "$(grep -m1 -o 'STOP-task-9.*' "$R/err.txt" | head -1)"
