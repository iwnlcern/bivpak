#!/bin/bash
# one series draw exactly as Task 9's loop line runs it, on a scratch home
EVID=/private/tmp/claude-501/-Users-jack-Programming-bivpak/6fecc389-d499-4128-a827-a4138f47bce6/scratchpad/r36/swalk/evid; LLVM_DIR=/Users/jack/Programming/bivpak-evidence/s2b-intg-substep2b-impl-1-y3iCLB/llvm22-assets-H.1vOscg; MAIN=/Users/jack/Programming/bivpak; LABEL=B-1; EXP=186adf7d67171bd7afe621f39b657a1a113ce299
date
o=0; docker run --rm --platform linux/amd64 --init -v "${LLVM_DIR}:/llvm-mirror:ro" -v "${MAIN}:/repo-ro:ro" -v "${EVID}/series:/evidence" -v "${EVID}/linux-container.sh:/evidence/linux-container.sh:ro" -v "${EVID}/linux-suite.sh:/evidence/linux-suite.sh:ro" -v "${EVID}/observer-unset-names.txt:/evidence/observer-unset-names.txt:ro" ubuntu:24.04 bash /evidence/linux-container.sh "$EXP" "$LABEL" > "$EVID/series/$LABEL/linux-container.log" 2>&1 || o=$?; printf '%s\n' "$o" > "$EVID/series/$LABEL/linux-container.rc"; echo "container rc=$o"
x=0; python3 "$EVID/selftest_summary.py" "$EVID/series/$LABEL/ctest-linux-$LABEL.junit.xml" "$EVID/series/$LABEL/selftest-$LABEL" > "$EVID/series/$LABEL/selftest-$LABEL.out" || x=$?; echo "summary rc=$x"; cat "$EVID/series/$LABEL/selftest-$LABEL.kv" 2>/dev/null
ls -la "$EVID/series"
date
