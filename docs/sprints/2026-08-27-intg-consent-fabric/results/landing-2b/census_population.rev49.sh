#!/bin/bash
# census_population.rev49.sh <TREE_REF> <OUT_POP> — PRODUCES the PINNED product population the rev49 landing census consumes (R-4.92 operator arm (a), master 212748;
# the accepted-value SET, master 211118). bash 3.2; set -o pipefail; every producer's rc bound before its output is read; no matched text written.
# One `git grep -n` over the WHOLE tree at TREE_REF; each row classified by its FIRST match's sha256 against the accepted-value SET below:
#   kind fixture -> class A at a product path (src/ tests/ harness/ .github/ CMake*), class B elsewhere; kind english -> class C.
# ANY row whose digest is not in the SET is a STOP naming path:line only (a new value is a pair-Planner classification routed to master, never automatic).
# OUT_POP holds ONLY the SET header and the PRODUCT rows (path:line | class), so its bytes are stable while docs/ and .relays/ grow; the whole-tree
# counts are printed to stdout as DATA, never written into OUT_POP.
set -u
set -o pipefail
ALT='sk-[A-Za-z0-9]{8,}|-----BEGIN [A-Z ]*PRIVATE KEY|AKIA[0-9A-Z]{16}|ghp_[A-Za-z0-9]{20,}|xox[abprs]-'
# the accepted-value SET (kind=sha256), in this order: the R-4.49 fixture; the rev42 synthetic control (211118: class B); the R-4.49 English value; the 2b English value (211118: class C)
SET='fixture=2b3d813effb1ac2021683332d9bc74477e9d7bf5a9bc47a95a8c725de0562150 fixture=f419886e26c74511ac3a28b1f9f8a7dff3ad6196518b8445d5b441c565b917e2 english=5d64f445c82a86cf123096105cd0d3a763abce9db9d67f366b5694c3b483f380 english=6b5faf3733f8e6f844543b9b1886fd780a0333658081240dfa1c55e7fce655df'
STOP() { printf 'STOP-census-population line=%s reason=%s\n' "${BASH_LINENO[0]}" "$1" >&2; exit 1; }
PIPEOK() { local st=("${PIPESTATUS[@]}"); local k; for k in "${st[@]}"; do [ "$k" -eq 0 ] || STOP "$1-stage-status-${st[*]// /-}"; done; }
kind_of() { local p; for p in $SET; do [ "${p#*=}" = "$1" ] && { printf '%s' "${p%%=*}"; return 0; }; done; return 1; }
[ $# -eq 2 ] || STOP usage
TREE_REF=$1; OUTP=$2
export LC_ALL=C
[ ! -e "$OUTP" ] && [ ! -L "$OUTP" ] || STOP out-exists
TREE=$(git rev-parse --verify --quiet "${TREE_REF}^{tree}") || STOP tree-ref-unresolvable
[ "${#TREE}" -eq 40 ] || STOP tree-sha-shape
r=0; RAW=$(git grep -n -E "$ALT" "$TREE" -- .) || r=$?; [ "$r" -eq 0 ] || STOP tree-producer-rc-"$r"
[ -n "$RAW" ] || STOP tree-zero-rows
ROWS=""; nA=0; nB=0; nC=0; nt=0; np=0
while IFS= read -r line; do
  case "$line" in "$TREE:"*) ;; *) STOP tree-row-prefix;; esac
  rest=${line#"$TREE:"}; pl=${rest%%:*}; rest2=${rest#*:}; ln=${rest2%%:*}; txt=${rest2#*:}
  case "$ln" in ''|*[!0-9]*) STOP "tree-row-line-number-at-$pl";; esac
  m=0; val=$(printf '%s' "$txt" | grep -o -E "$ALT") || m=$?; [ "$m" -eq 0 ] && [ -n "$val" ] || STOP "tree-row-no-match-at-$pl:$ln"; val=${val%%$'\n'*}
  dg=$(printf '%s' "$val" | shasum -a 256 | cut -d' ' -f1); PIPEOK value-digest; [ "${#dg}" -eq 64 ] || STOP value-digest-shape
  k=$(kind_of "$dg") || STOP "unclassified-value-at-$pl:$ln"
  case "$k" in
    fixture) case "$pl" in src/*|tests/*|harness/*|.github/*|CMake*) c=A; nA=$((nA+1));; *) c=B; nB=$((nB+1));; esac;;
    english) c=C; nC=$((nC+1));;
    *) STOP kind-token;;
  esac
  case "$pl" in src/*|tests/*|harness/*|.github/*|CMake*) ROWS="$ROWS$pl:$ln | $c"$'\n'; np=$((np+1));; esac
  nt=$((nt+1))
done <<EOF_ROWS
$RAW
EOF_ROWS
unset RAW
[ "$np" -ge 1 ] || STOP product-rows-empty
{
  printf '# sub-step 2b PINNED product census population (rev49; R-4.92 arm (a)): the accepted-value SET and the PRODUCT rows only; paths and line numbers ONLY, no matched text.\n'
  printf '== ACCEPTED VALUE SET: %s\n' "$SET"
  printf '\n== PRODUCT TREE ARM (path:line | class)\n'
  printf '%s' "$ROWS"
  printf '\n'
} > "$OUTP" || STOP population-write
[ -s "$OUTP" ] || STOP population-empty
printf 'census_population_rev49 tree=%s tree_rows=%s A=%s B=%s C=%s product_rows=%s (tree_rows and the class counts are DATA; only the SET and the product rows are written)\n' "$TREE" "$nt" "$nA" "$nB" "$nC" "$np"
exit 0
