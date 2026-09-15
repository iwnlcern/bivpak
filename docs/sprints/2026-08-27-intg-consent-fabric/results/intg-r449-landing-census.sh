#!/bin/bash
# intg-r449-landing-census.sh — the R-4.49 landing's CENSUS OF RECORD (merge packet §7 step (3)), the one declared instrument. bash 3.2 compatible (the macOS system bash).
# usage: intg-r449-landing-census.sh <TREE_REF> <POPULATION_FILE> <OUT_DIR> <HISTORY_REF> [<HISTORY_REF>...]
#   TREE_REF      the object whose WHOLE TREE is scanned (the merge commit at landing; the predicted tree from `git merge-tree --write-tree main H` before it)
#   HISTORY_REFS  the commits whose WHOLE REACHABLE HISTORY is scanned (the merge commit at landing; `main H` before it)
# Exit 0 and a last stdout line ending `result=PASS` ONLY IF every predicate holds; otherwise exit 1 with ONE stderr line `STOP-landing-census line=<N> reason=<token>` and NO push may follow.
# Retained output under OUT_DIR is paths and line numbers only (expected/actual/delta files, class/ok rows, digests); matched text is held in shell memory and never written; values are compared by sha256 digest against the ACCEPTED VALUE DIGESTS line of the population file.
# Negative-control hook (rehearsal only; never set at a landing): CENSUS_MUTANT_ROW=<n> replaces, IN MEMORY, the matched value on actual tree row n with a different synthetic value that still matches the same detector branch — the value guard must STOP.
set -u
ALT='sk-[A-Za-z0-9]{8,}|-----BEGIN [A-Z ]*PRIVATE KEY|AKIA[0-9A-Z]{16}|ghp_[A-Za-z0-9]{20,}|xox[abprs]-'
STOP() { printf 'STOP-landing-census line=%s reason=%s\n' "${BASH_LINENO[0]}" "$1" >&2; exit 1; }
[ $# -ge 4 ] || STOP usage
TREE_REF=$1; POP=$2; OUT=$3; shift 3
export LC_ALL=C
[ "$(printf 'a\nB\n' | LC_ALL=C sort | head -n 1)" = B ] || STOP collation-not-C
[ -s "$POP" ] || STOP population-missing
mkdir -p "$OUT" || STOP outdir
TREE=$(git rev-parse --verify --quiet "${TREE_REF}^{tree}") || STOP tree-ref-unresolvable
[ "${#TREE}" -eq 40 ] || STOP tree-sha-shape
# ---- expectations from the population file (sections bounded by their header line and the next blank line)
a=0; awk '/^== TREE ARM \(path:line \| class\)/ { f = 1; next } f && /^$/ { exit } f { print }' "$POP" > "$OUT/expected-tree.rows" || a=$?; [ "$a" -eq 0 ] && [ -s "$OUT/expected-tree.rows" ] || STOP expected-tree-section
g=0; bad=$(grep -c -v -E '^[A-Za-z0-9_./-]+:[0-9]+ \| [ABC] [a-z-]+$' "$OUT/expected-tree.rows") || g=$?; [ "$g" -le 1 ] && [ "$bad" -eq 0 ] || STOP expected-tree-row-shape
s=0; sed -E 's/ \| .*$//' "$OUT/expected-tree.rows" > "$OUT/expected-tree.pl" || s=$?; [ "$s" -eq 0 ] || STOP expected-tree-projection
s=0; sed -E 's/^.* \| ([ABC]) .*$/\1/' "$OUT/expected-tree.rows" > "$OUT/expected-tree.class" || s=$?; [ "$s" -eq 0 ] || STOP expected-tree-class
a=0; awk '/^== HISTORY ARM/ { f = 1; next } f && /^$/ { exit } f { print }' "$POP" > "$OUT/expected-history.p" || a=$?; [ "$a" -eq 0 ] && [ -s "$OUT/expected-history.p" ] || STOP expected-history-section
g=0; bad=$(grep -c -v -E '^[A-Za-z0-9_./-]+$' "$OUT/expected-history.p") || g=$?; [ "$g" -le 1 ] && [ "$bad" -eq 0 ] || STOP expected-history-row-shape
FIX=$(sed -n -E 's/^== ACCEPTED VALUE DIGESTS: fixture=([0-9a-f]{64}) english=([0-9a-f]{64})$/\1/p' "$POP"); ENG=$(sed -n -E 's/^== ACCEPTED VALUE DIGESTS: fixture=([0-9a-f]{64}) english=([0-9a-f]{64})$/\2/p' "$POP")
[ "${#FIX}" -eq 64 ] && [ "${#ENG}" -eq 64 ] && [ "$FIX" != "$ENG" ] || STOP accepted-digests-line
# ---- the TREE ARM (producer: git grep -n over the whole tree, rows in git grep's own order; the ref prefix stripped by its literal resolved sha; then the path:line projection). The raw rows live in memory only.
r=0; RAW=$(git grep -n -E "$ALT" "$TREE" -- .) || r=$?; [ "$r" -eq 0 ] || STOP tree-producer-rc-"$r"
[ -n "$RAW" ] || STOP tree-zero-rows
: > "$OUT/actual-tree.pl"; TEXT=(); i=0
while IFS= read -r line; do case "$line" in "$TREE:"*) ;; *) STOP tree-row-prefix;; esac; rest=${line#"$TREE:"}; pl=$(printf '%s' "$rest" | sed -E 's/^([^:]+:[0-9]+):.*$/\1/'); [ -n "$pl" ] && [ "$pl" != "$rest" ] || STOP tree-row-projection; printf '%s\n' "$pl" >> "$OUT/actual-tree.pl"; TEXT[$i]=${rest#"$pl":}; i=$((i + 1)); done <<< "$RAW"
unset RAW
d=0; diff "$OUT/expected-tree.pl" "$OUT/actual-tree.pl" > "$OUT/tree.delta" || d=$?; [ "$d" -eq 0 ] || STOP tree-delta
# ---- the VALUE GUARD on every tree row (the first detector match on the row, digested in memory; class A and B must be the fixture digest, class C the English digest)
CLS=(); j=0; while IFS= read -r c; do CLS[$j]=$c; j=$((j + 1)); done < "$OUT/expected-tree.class"; [ "${#CLS[@]}" -eq "${#TEXT[@]}" ] || STOP class-count
: > "$OUT/tree-value-check.txt"; nA=0; nB=0; nC=0; SEEN=" "; nseen=0
i=0; while [ "$i" -lt "${#TEXT[@]}" ]; do t=${TEXT[$i]}; if [ -n "${CENSUS_MUTANT_ROW:-}" ] && [ "$((i + 1))" -eq "$CENSUS_MUTANT_ROW" ]; then t="mutant $(printf 'sk-%040d' 7) in memory only"; fi; v=$(printf '%s' "$t" | grep -o -E "$ALT" | head -n 1); [ -n "$v" ] || STOP tree-row-no-match; dg=$(printf '%s' "$v" | shasum -a 256 | cut -d' ' -f1); case "$SEEN" in *" $dg "*) ;; *) SEEN="$SEEN$dg "; nseen=$((nseen + 1));; esac; pl=$(sed -n "$((i + 1))p" "$OUT/actual-tree.pl"); case "${CLS[$i]}" in A) want=$FIX; nA=$((nA + 1));; B) want=$FIX; nB=$((nB + 1));; C) want=$ENG; nC=$((nC + 1));; *) STOP class-token;; esac; if [ "$dg" != "$want" ]; then printf '%s class=%s digest=%s expected=%s MISMATCH\n' "$pl" "${CLS[$i]}" "${dg:0:16}" "${want:0:16}" >> "$OUT/tree-value-check.txt"; STOP value-guard-"$pl"; fi; printf '%s class=%s ok\n' "$pl" "${CLS[$i]}" >> "$OUT/tree-value-check.txt"; i=$((i + 1)); done
unset TEXT
[ "$nseen" -eq 2 ] || STOP distinct-current-values-"$nseen"
# ---- the PRODUCT-SCOPED VIEW of the tree (exactly the class-A locations, in order; no other product path)
g=0; grep -E '^(src|tests|harness|\.github|CMake)' "$OUT/actual-tree.pl" > "$OUT/actual-tree-product.pl" || g=$?; [ "$g" -le 1 ] || STOP product-view-grep
: > "$OUT/expected-tree-product.pl"; i=0; while [ "$i" -lt "${#CLS[@]}" ]; do if [ "${CLS[$i]}" = A ]; then sed -n "$((i + 1))p" "$OUT/expected-tree.pl" >> "$OUT/expected-tree-product.pl"; fi; i=$((i + 1)); done
d=0; diff "$OUT/expected-tree-product.pl" "$OUT/actual-tree-product.pl" > "$OUT/tree-product.delta" || d=$?; [ "$d" -eq 0 ] || STOP product-view-delta
# ---- the HISTORY ARM (producer: rev-list over the given refs, then ONE `git grep -l` over every listed commit — no xargs, so the producer's exit status is git grep's own: 0 = rows, 1 = no row at all = STOP, other = STOP; rows stripped of their 40-hex commit prefix; unique paths in BYTE ORDER)
HREFS=$*; r=0; git rev-list "$@" > "$OUT/revs.txt" || r=$?; [ "$r" -eq 0 ] && [ -s "$OUT/revs.txt" ] || STOP rev-list
g=0; bad=$(grep -c -v -E '^[0-9a-f]{40}$' "$OUT/revs.txt") || g=$?; [ "$g" -le 1 ] && [ "$bad" -eq 0 ] || STOP rev-list-shape
set -- $(cat "$OUT/revs.txt")
x=0; git grep -l -E "$ALT" "$@" -- . > "$OUT/history.raw" || x=$?; [ "$x" -eq 0 ] || STOP history-producer-rc-"$x"
g=0; bad=$(grep -c -v -E '^[0-9a-f]{40}:' "$OUT/history.raw") || g=$?; [ "$g" -le 1 ] && [ "$bad" -eq 0 ] || STOP history-row-prefix
s=0; sed -E 's/^[0-9a-f]{40}://' "$OUT/history.raw" > "$OUT/history.paths" || s=$?; [ "$s" -eq 0 ] || STOP history-strip; o=0; LC_ALL=C sort -u "$OUT/history.paths" > "$OUT/actual-history.p" || o=$?; [ "$o" -eq 0 ] && [ -s "$OUT/actual-history.p" ] || STOP history-reduction; rm -f "$OUT/history.raw" "$OUT/history.paths"
d=0; diff "$OUT/expected-history.p" "$OUT/actual-history.p" > "$OUT/history.delta" || d=$?; [ "$d" -eq 0 ] || STOP history-delta
# ---- the HISTORICAL VALUE SET (every matched value over the whole reachable history, digested in memory; must be a subset of the two accepted digests)
x=0; HV=$(git grep -h -o -E "$ALT" "$@" -- . | LC_ALL=C sort | uniq -c) || x=$?; [ "$x" -eq 0 ] && [ -n "$HV" ] || STOP history-values-producer; nhv=0; : > "$OUT/history-value-digests.txt"
while IFS= read -r e; do n=$(printf '%s' "$e" | awk '{ print $1 }'); v=$(printf '%s' "$e" | sed -E 's/^ *[0-9]+ //'); dg=$(printf '%s' "$v" | shasum -a 256 | cut -d' ' -f1); [ "$dg" = "$FIX" ] || [ "$dg" = "$ENG" ] || STOP undeclared-historical-value-"${dg:0:16}"; printf '%s occurrences=%s\n' "$dg" "$n" >> "$OUT/history-value-digests.txt"; nhv=$((nhv + 1)); done <<< "$HV"
unset HV
[ "$nhv" -ge 1 ] || STOP history-values-empty
# ---- the PRODUCT-SCOPED VIEW of the history (exactly the unique paths of the class-A rows)
g=0; grep -E '^(src|tests|harness|\.github|CMake)' "$OUT/actual-history.p" > "$OUT/actual-history-product.p" || g=$?; [ "$g" -le 1 ] || STOP product-history-grep
s=0; sed -E 's/:[0-9]+$//' "$OUT/expected-tree-product.pl" | LC_ALL=C sort -u > "$OUT/expected-history-product.p" || s=$?; [ "$s" -eq 0 ] || STOP product-history-expected
d=0; diff "$OUT/expected-history-product.p" "$OUT/actual-history-product.p" > "$OUT/history-product.delta" || d=$?; [ "$d" -eq 0 ] || STOP product-history-delta
nt=$(awk 'END { print NR }' "$OUT/actual-tree.pl"); nh=$(awk 'END { print NR }' "$OUT/actual-history.p"); nr=$(awk 'END { print NR }' "$OUT/revs.txt"); npt=$(awk 'END { print NR }' "$OUT/actual-tree-product.pl"); nph=$(awk 'END { print NR }' "$OUT/actual-history-product.p")
printf 'landing_census tree=%s tree_rows=%s history_refs=%s commits=%s history_paths=%s classes A=%s B=%s C=%s distinct_current_digests=%s distinct_historical_digests=%s product_tree_rows=%s product_history_paths=%s result=PASS\n' "$TREE" "$nt" "$HREFS" "$nr" "$nh" "$nA" "$nB" "$nC" "$nseen" "$nhv" "$npt" "$nph" | tee "$OUT/summary.txt"
exit 0
