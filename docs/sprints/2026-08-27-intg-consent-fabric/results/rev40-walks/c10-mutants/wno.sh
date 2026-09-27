#!/usr/bin/env bash
# rev40 NO walk of c10-mutants.sh: cmake/ctest stubbed on PATH and build/ci-macos/biv_tests a stub, each serving the REAL artifacts of the rev40 YES run for the mutant MAP names
set -u
S=/private/tmp/claude-501/-Users-jack-Programming-bivpak/6fecc389-d499-4128-a827-a4138f47bce6/scratchpad/r40; A=$S/mev/code/c10-mutants.rev40; RE=/Users/jack/Programming/bivpak-evidence/s2b-intg-substep2b-impl-1-y3iCLB; CAND=/Users/jack/Programming/bivpak-intg-substep2b-wiring; C10=2291a46e7ff70c4c06055c8d0aab9e6709cb134d
case_rc() { case $1 in M-H1-SCHEMA) echo 0;; *) echo 42;; esac; }
walk() { local c=$1 map=$2 d=$S/no/$1; rm -rf "$d"; mkdir -p "$d/bin" "$d/evid/receipts" "$d/evid/code" "$d/art"
  git clone -q --no-hardlinks "$CAND" "$d/wt"; git -C "$d/wt" checkout -q "$C10"; mkdir -p "$d/wt/build/ci-macos"
  cp -p $RE/commits.c9.txt $RE/commits.c10.txt "$d/evid/"; cp -p $RE/receipts/c10-mutants.txt "$d/evid/receipts/"; cp -Rp $RE/code/c10-mutants "$d/evid/code/"; cp -p $RE/code/c10-M-H1-F4.patch "$d/evid/code/"
  cp -p $A/*.xml $A/*.ctest.log "$d/art/"; [ -n "${3-}" ] && eval "$3"
  printf '#!/usr/bin/env bash\nexit 0\n' > "$d/bin/cmake"
  printf '#!/usr/bin/env bash\nn=$(cat "%s/n"); set -- %s; shift $((n-1)); cat "%s/art/$1.ctest.log"; exit 8\n' "$d" "$map" "$d" > "$d/bin/ctest"
  printf '#!/usr/bin/env bash\nn=$(( $(cat "%s/n" 2>/dev/null || echo 0) + 1 )); echo $n > "%s/n"; set -- %s; shift $((n-1)); cat "%s/art/$1.xml"; case $1 in M-H1-SCHEMA) exit 0;; *) exit 42;; esac\n' "$d" "$d" "$map" "$d" > "$d/wt/build/ci-macos/biv_tests"
  chmod +x "$d/bin/cmake" "$d/bin/ctest" "$d/wt/build/ci-macos/biv_tests"
  o=$(cd "$d/wt" && PATH="$d/bin:$PATH" EVID="$d/evid" bash $S/c10-mutants.sh 2>&1); rc=$?
  echo "case=$c rc=$rc out=$(echo "$o" | tail -1 | cut -c1-70) verdict=$(grep -c -x 'verdict=ok' "$d/evid/receipts/c10-mutants.rev40.txt" 2>/dev/null) tree=$(git -C "$d/wt" status --short --untracked-files=no | wc -l | tr -d ' ')"; }
walk yes-stubbed 'M-H1-PRE M-H1-SCHEMA M-H1-F4'
walk pre-gets-schema 'M-H1-SCHEMA M-H1-SCHEMA M-H1-F4'
walk pre-gets-f4 'M-H1-F4 M-H1-SCHEMA M-H1-F4'
walk pre-other-case 'M-H1-PRE M-H1-SCHEMA M-H1-F4' 'sed -i "" "s/open repos typed refusal continues in encounter order to a clean entry/some other case/" "$d/art/M-H1-PRE.xml"'
walk schema-gets-pre 'M-H1-PRE M-H1-PRE M-H1-F4'
walk f4-gets-pre 'M-H1-PRE M-H1-SCHEMA M-H1-PRE'
walk f4-one-w3-renamed 'M-H1-PRE M-H1-SCHEMA M-H1-F4' 'sed -i "" "s/failed row completeness rejects a missing kind/some other case/" "$d/art/M-H1-F4.xml"'
walk conforms-row-absent 'M-H1-PRE M-H1-SCHEMA M-H1-F4' 'grep -v "divergence_envelope_conforms" "$d/art/M-H1-PRE.ctest.log" > "$d/art/x" && mv "$d/art/x" "$d/art/M-H1-PRE.ctest.log"'
walk rev39-record-moved 'M-H1-PRE M-H1-SCHEMA M-H1-F4' 'printf x >> "$d/evid/receipts/c10-mutants.txt"'
walk rev39-work-absent 'M-H1-PRE M-H1-SCHEMA M-H1-F4' 'rm -rf "$d/evid/code/c10-mutants"'
walk record-exists 'M-H1-PRE M-H1-SCHEMA M-H1-F4' ': > "$d/evid/receipts/c10-mutants.rev40.txt"'
