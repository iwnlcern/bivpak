set -u; STOP() { printf "STOP-frag line=%s
" "${BASH_LINENO[0]}" >&2; exit 1; }
H=$(sed 's/^H=//' "$EVID/R/H.txt") || STOP; [ -n "$H" ] || STOP   # rev39: the FINAL H is Task 9b's
[ "$(cat "$EVID/R/count-gate-final-macos.rc")" = count_gate_final_macos_rc=0 ] && [ "$(cat "$EVID/R/count-gate-final-linux.rc")" = count_gate_final_linux_rc=0 ] || STOP
[ "$(cat "$EVID/heads/c10/linux-container.rc")" = 0 ] && [ "$(cat "$EVID/B/linux-container.rc")" = 0 ] && [ "$(cat "$EVID/R/E3-linux.rc")" = e3_linux_rc=0 ] && [ "$(cat "$EVID/R/harness-e2-macos.rc")" = harness_e2_macos_rc=0 ] && [ "$(cat "$EVID/R/harness-e2-linux.rc")" = harness_e2_linux_rc=0 ] || STOP
[ "$(cat "$EVID/R/selftest-population.rc")" = population_equal_rc=0 ] || STOP; g=0; k=$(grep -c -E ' bar=(pass-green|pass-r435-disclosed-registered-red)$' "$EVID/R/linux-selftest-bar.txt") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP   # rev39: the lighter re-gate admits only an EQUAL population
echo "frag10 OK H=$H"
