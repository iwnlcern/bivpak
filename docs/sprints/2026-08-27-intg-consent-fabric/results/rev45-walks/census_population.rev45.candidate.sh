#!/bin/bash
# census_population.sh <TREE_REF> <OUT_POP> <HISTORY_REF>... — PRODUCES the population file the pinned landing-census instrument consumes, ON THE
# OBJECT SCANNED (never carried). Same alternation; the TREE ARM rows (path:line | class) from ONE `git grep -n` over the whole tree, every matched
# value classified IN MEMORY by its sha256 against the two ACCEPTED VALUE DIGESTS of the R-4.49 record (fixture / english); class A = the fixture
# digest at a product path (src|tests|harness|.github|CMake), B = the fixture digest elsewhere, C = the english digest; ANY other value ⇒
# STOP naming path:line only (a new class is the pair Planner's classification, never automatic). HISTORY ARM: `git rev-list` over the refs, ONE
# `git grep -l`, paths sorted -u under LC_ALL=C. bash 3.2; set -o pipefail; every producer's rc before its output is read; no matched text written.
set -u
set -o pipefail
ALT='sk-[A-Za-z0-9]{8,}|-----BEGIN [A-Z ]*PRIVATE KEY|AKIA[0-9A-Z]{16}|ghp_[A-Za-z0-9]{20,}|xox[abprs]-'
FIX=2b3d813effb1ac2021683332d9bc74477e9d7bf5a9bc47a95a8c725de0562150
ENG=5d64f445c82a86cf123096105cd0d3a763abce9db9d67f366b5694c3b483f380
STOP() { printf 'STOP-census-population line=%s reason=%s\n' "${BASH_LINENO[0]}" "$1" >&2; exit 1; }
PIPEOK() { local st=("${PIPESTATUS[@]}"); local k; for k in "${st[@]}"; do [ "$k" -eq 0 ] || STOP "$1-stage-status-${st[*]// /-}"; done; }
[ $# -ge 3 ] || STOP usage
TREE_REF=$1; OUTP=$2; shift 2
export LC_ALL=C
TREE=$(git rev-parse --verify --quiet "${TREE_REF}^{tree}") || STOP tree-ref-unresolvable
[ "${#TREE}" -eq 40 ] || STOP tree-sha-shape
r=0; RAW=$(git grep -n -E "$ALT" "$TREE" -- .) || r=$?; [ "$r" -eq 0 ] || STOP tree-producer-rc-"$r"
[ -n "$RAW" ] || STOP tree-zero-rows
TMP=$(mktemp) || STOP tmp; : > "$TMP" || STOP tmp-write
nA=0; nB=0; nC=0
while IFS= read -r line; do
  case "$line" in "$TREE:"*) ;; *) STOP tree-row-prefix;; esac
  rest=${line#"$TREE:"}; pl=${rest%%:*}:; rest2=${rest#*:}; ln=${rest2%%:*}; txt=${rest2#*:}; pl=${pl%:}
  m=0; val=$(printf '%s' "$txt" | grep -o -E "$ALT") || m=$?; [ "$m" -eq 0 ] && [ -n "$val" ] || STOP "tree-row-no-match-at-$pl:$ln"; val=${val%%$'\n'*}   # one row per LINE, classified by its FIRST match: the instrument's own rule (its `git grep -n` + `${v%%$'\n'*}`)
  dg=$(printf '%s' "$val" | shasum -a 256 | cut -d' ' -f1); PIPEOK value-digest
  cls=""
  if [ "$dg" = "$FIX" ]; then case "$pl" in src/*|tests/*|harness/*|.github/*|CMake*) cls="A fixture-product";; *) cls="B fixture-copy";; esac
  elif [ "$dg" = "$ENG" ]; then cls="C english-word-false-positive"
  else STOP "unclassified-value-at-$pl:$ln"; fi
  case "$cls" in A*) nA=$((nA+1));; B*) nB=$((nB+1));; C*) nC=$((nC+1));; esac
  printf '%s:%s | %s\n' "$pl" "$ln" "$cls" >> "$TMP" || STOP row-write
done <<EOF_ROWS
$RAW
EOF_ROWS
unset RAW
nt=$(awk 'END { print NR }' "$TMP") || STOP count
HTMP=$(mktemp) || STOP tmp2
git rev-list "$@" > "$HTMP.revs" || STOP rev-list; [ -s "$HTMP.revs" ] || STOP rev-list-empty
REVS=$(cat "$HTMP.revs") || STOP rev-list-read; set -- $REVS; [ $# -ge 1 ] || STOP rev-list-args
x=0; git grep -l -E "$ALT" "$@" -- . > "$HTMP.raw" || x=$?; [ "$x" -eq 0 ] || STOP history-producer-rc-"$x"
sed -E 's/^[0-9a-f]{40}://' "$HTMP.raw" > "$HTMP.paths" || STOP history-strip
LC_ALL=C sort -u "$HTMP.paths" > "$HTMP.p" || STOP history-reduction; [ -s "$HTMP.p" ] || STOP history-empty
nh=$(awk 'END { print NR }' "$HTMP.p") || STOP count2; nr=$(awk 'END { print NR }' "$HTMP.revs") || STOP count3
{
  printf '# sub-step 2b census population PRODUCED on %s (tree %s) by census_population.sh — paths and line numbers ONLY; no matched text.\n' "$TREE_REF" "$TREE"
  printf '# Classes by value digest against the R-4.49 record: A fixture-product (%s) B fixture-copy (%s) C english (%s); history refs: %s (%s commits)\n' "$nA" "$nB" "$nC" "$*" "$nr"
  printf '== ACCEPTED VALUE DIGESTS: fixture=%s english=%s\n' "$FIX" "$ENG"
  printf '\n== TREE ARM (path:line | class) — %s locations\n' "$nt"
  cat "$TMP"
  printf '\n== HISTORY ARM — %s paths\n' "$nh"
  cat "$HTMP.p"
  printf '\n'
} > "$OUTP" || STOP population-write
rm -f "$TMP" "$HTMP" "$HTMP.revs" "$HTMP.raw" "$HTMP.paths" "$HTMP.p"
[ -s "$OUTP" ] || STOP population-empty
printf 'census_population tree=%s rows=%s A=%s B=%s C=%s history_paths=%s commits=%s\n' "$TREE" "$nt" "$nA" "$nB" "$nC" "$nh" "$nr"
exit 0
