#!/usr/bin/env bash
S=/private/tmp/claude-501/-Users-jack-Programming-bivpak/6fecc389-d499-4128-a827-a4138f47bce6/scratchpad/r42; T=$S/t10.sh; RE=/Users/jack/Programming/bivpak-evidence/s2b-intg-substep2b-impl-1-y3iCLB; W=$S/w; rm -rf "$W"; mkdir -p "$W"
HDR='set -o pipefail; STOP() { printf "STOP-task-10 line=%s\n" "${BASH_LINENO[0]}" >&2; exit 1; }'
{ printf '%s\n' "$HDR"; sed -n '26,36p' "$T"; echo 'echo STEP0-OK "${AD-none}"'; } > "$W/step0.sh"
{ printf '%s\n' "$HDR"; echo 'gh() { cat "$FAKEVIS"; }'; sed -n '84p' "$T"; echo 'echo VIS-OK'; } > "$W/vis.sh"
{ printf '%s\n' "$HDR"; echo 'B=186adf7d67171bd7afe621f39b657a1a113ce299; H=${WH:-cb19326a5596bf30eab2ec2b9baeda0bc77be895}; B=${WB:-$B}'; echo 'git() { case "$1 $2" in "${HOOKARGS-}") command git "$@" | eval "$HOOKCMD";; *) command git "$@";; esac; }'; sed -n '85,89p' "$T"; echo 'echo EXPOSURE-OK; cat "$EVID"/exposure-*.txt'; } > "$W/exp.sh"
echo "exposure script map (block 85..89 -> lines 4..8):"; awk 'NR>=4 && NR<=8 {print "  " NR ": " substr($0,1,60)}' "$W/exp.sh"
mk() { local e=$W/$1/E; mkdir -p "$e/work" "$e/attempts/task9-H0-99136ca"; for f in helpers.verify-10.txt task-10-go.txt push-url.txt remote-branch-before.txt visibility.txt work/owner-lines.txt work/owner-paths.txt work/owner-paths.uniq; do cp -p "$RE/$f" "$e/$f"; done; }
r0() { (EVID=$W/$1/E bash "$W/step0.sh") > "$W/$1.out" 2>&1; echo "$1 rc=$? $(tail -1 "$W/$1.out")"; }
echo "== Step 0 (preservation)"
mk yes; r0 yes; (cd "$W/yes/E/attempts/task10-1" && find . -type f | sort | tr '\n' ' '); echo; ls "$W/yes/E" | tr '\n' ' '; echo
for f in helpers.verify-10.txt task-10-go.txt push-url.txt remote-branch-before.txt visibility.txt work/owner-lines.txt work/owner-paths.txt work/owner-paths.uniq; do cmp -s "$RE/$f" "$W/yes/E/attempts/task10-1/$f" || echo "DIFF $f"; done; echo "moved bytes equal to the real files: checked"
r0 yes; echo "(second run on the emptied home: no-op expected)"
mk second; mkdir -p "$W/second/E/attempts/task10-1"; r0 second
mk push-receipt; echo push_rc=0 > "$W/push-receipt/E/push-rc.txt"; r0 push-receipt
mk pr-receipt; : > "$W/pr-receipt/E/pr.rc"; r0 pr-receipt
mk linked; rm "$W/linked/E/visibility.txt"; ln -s "$RE/visibility.txt" "$W/linked/E/visibility.txt"; r0 linked
mk attempts-link; rm -rf "$W/attempts-link/E/attempts"; mkdir -p "$W/elsewhere"; ln -s "$W/elsewhere" "$W/attempts-link/E/attempts"; r0 attempts-link
echo "== visibility"
for v in PUBLIC PRIVATE INTERNAL public ''; do printf '%s\n' "$v" > "$W/fv"; mkdir -p "$W/v/E"; (FAKEVIS=$W/fv EVID=$W/v/E bash "$W/vis.sh") > "$W/v.out" 2>&1; echo "vis='$v' rc=$? $(tail -1 "$W/v.out")"; done
echo "== exposure census (real candidate; ls-remote is a read)"
re() { local c=$1; shift; mkdir -p "$W/x-$c/work"; (cd /Users/jack/Programming/bivpak-intg-substep2b-wiring && env "$@" EVID=$W/x-$c bash "$W/exp.sh") > "$W/x-$c.out" 2>&1; echo "$c rc=$? $(grep -m1 -E 'EXPOSURE-OK|STOP' "$W/x-$c.out")"; }
re yes X=1; sed -n '2,5p' "$W/x-yes.out"
re wrong-B WB=2893bc53ad0f9d4f3e6f45f7990c86d49f868138
re count-25 WH=b3039506d0df856930dba21f5dc47a3d23baab56
re foreign-author "HOOKARGS=log --format=%ae%n%ce" "HOOKCMD={ cat; echo someone@example.com; }"
re secret-in-patch "HOOKARGS=log -p" "HOOKCMD={ cat; echo '+token ghp_abcdefghijklmnopqrstuvwxyz0123'; }"
re control-noop-hook "HOOKARGS=log -p" "HOOKCMD=cat"
