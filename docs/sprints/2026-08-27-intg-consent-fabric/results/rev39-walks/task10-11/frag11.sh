set -u; STOP() { printf "STOP-frag line=%s
" "${BASH_LINENO[0]}" >&2; exit 1; }
H0=$(sed 's/^H0=//' "$EVID/R/H0.txt") || STOP; [ -n "$H0" ] || STOP; H=$(sed 's/^H=//' "$EVID/R/H.txt") || STOP; [ -n "$H" ] || STOP
echo "frag11 OK H0=$H0 H=$H"
