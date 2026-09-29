#!/bin/bash
# intg-2b-landing-census.sh — the sub-step 2b landing's CENSUS OF RECORD (rev49). Derived from intg-r449-landing-census.sh rev3 (9c9391d5…, unchanged as the R-4.49 record)
# under master 211118 (the accepted-value SET) and R-4.92 operator arm (a) carried by master 212748: the value guard is GLOBAL over the whole tree and the whole
# reachable history, and a row's class is a function of its value's DIGEST (kind fixture -> A at a product path, B elsewhere; kind english -> C); the path:line
# expectation is pinned EXACTLY over the product prefixes only; docs/ and .relays/ carry value-membership only, their counts recorded as DATA.
# REMOVED from rev3 (exactly): the global tree location diff and the global history location diff, with the index walk (CLS[]/class-count) and the two hardcoded
# distinct-value counts that depended on them. UNCHANGED from rev3: set -o pipefail; PIPEOK after every pipeline; each single-stage producer's own rc bound
# before its output is read; partial output with a nonzero status is a STOP; every retained write checked; the summary written and checked before the PASS
# line; no retries; OUT_DIR retains paths, line numbers, classes and digests only — matched text is held in shell memory and never written. bash 3.2.
# usage: intg-2b-landing-census.sh <TREE_REF> <POPULATION_FILE> <OUT_DIR> <HISTORY_REF> [<HISTORY_REF>...]
# Exit 0 with a last stdout line ending `result=PASS` ONLY IF every predicate holds; otherwise exit 1 with ONE stderr line `STOP-landing-census line=<N> reason=<token>`, and NO push may follow.
# Negative-control hook (rehearsal only; never set at a landing): CENSUS_MUTANT_ROW=<n> replaces, IN MEMORY, the matched value on actual tree row n with a synthetic value on the same detector branch — the value guard must STOP.
set -u
set -o pipefail
ALT='sk-[A-Za-z0-9]{8,}|-----BEGIN [A-Z ]*PRIVATE KEY|AKIA[0-9A-Z]{16}|ghp_[A-Za-z0-9]{20,}|xox[abprs]-'
PROD='^(src|tests|harness|\.github|CMake)'
STOP() { printf 'STOP-landing-census line=%s reason=%s\n' "${BASH_LINENO[0]}" "$1" >&2; exit 1; }
PIPEOK() { local st=("${PIPESTATUS[@]}"); local k; for k in "${st[@]}"; do [ "$k" -eq 0 ] || { printf 'STOP-landing-census line=%s reason=%s\n' "${BASH_LINENO[0]}" "$1-stage-status-${st[*]// /,}" >&2; exit 1; }; done; }
[ $# -ge 4 ] || STOP usage
TREE_REF=$1; POP=$2; OUT=$3; shift 3
export LC_ALL=C
cs=$(printf 'a\nB\n' | LC_ALL=C sort | head -n 1); PIPEOK collation-probe; [ "$cs" = B ] || STOP collation-not-C
[ -s "$POP" ] || STOP population-missing
mkdir -p "$OUT" || STOP outdir
TREE=$(git rev-parse --verify --quiet "${TREE_REF}^{tree}") || STOP tree-ref-unresolvable
[ "${#TREE}" -eq 40 ] || STOP tree-sha-shape
# ---- the accepted-value SET: exactly ONE header line of kind=sha256 tokens; kinds fixture|english; at least one fixture; no digest twice
g=0; nset=$(grep -c -E '^== ACCEPTED VALUE SET: ' "$POP") || g=$?; [ "$g" -le 1 ] && [ "$nset" -eq 1 ] || STOP accepted-set-line-count
SETL=$(sed -n -E 's/^== ACCEPTED VALUE SET: (.*)$/\1/p' "$POP") || STOP accepted-set-read; [ -n "$SETL" ] || STOP accepted-set-empty
SET=" "; nfix=0; nsetv=0
for tok in $SETL; do case "$tok" in fixture=*|english=*) ;; *) STOP accepted-set-token-kind;; esac; h=${tok#*=}; case "$h" in *[!0-9a-f]*) STOP accepted-set-token-hex;; esac; [ "${#h}" -eq 64 ] || STOP accepted-set-token-length; case "$SET" in *"=$h "*) STOP accepted-set-duplicate;; esac; SET="$SET$tok "; nsetv=$((nsetv + 1)); case "$tok" in fixture=*) nfix=$((nfix + 1));; esac; done
[ "$nfix" -ge 1 ] || STOP accepted-set-no-fixture
kind_of() { case "$SET" in *" fixture=$1 "*) printf fixture;; *" english=$1 "*) printf english;; *) return 1;; esac; }
# ---- the PINNED product expectation (the section bounded by its header and the next blank line); every row a product path
awk '/^== PRODUCT TREE ARM \(path:line \| class\)/ { f = 1; next } f && /^$/ { exit } f { print }' "$POP" > "$OUT/expected-product.rows" || STOP expected-product-section; [ -s "$OUT/expected-product.rows" ] || STOP expected-product-empty
g=0; bad=$(grep -c -v -E '^[A-Za-z0-9_./-]+:[0-9]+ \| [AC]$' "$OUT/expected-product.rows") || g=$?; [ "$g" -le 1 ] && [ "$bad" -eq 0 ] || STOP expected-product-row-shape
g=0; bad=$(grep -c -v -E "$PROD" "$OUT/expected-product.rows") || g=$?; [ "$g" -le 1 ] && [ "$bad" -eq 0 ] || STOP expected-product-non-product-row
# ---- the TREE ARM (producer: ONE `git grep -n` over the whole tree, its own rc — 0 = rows; 1 = no row = STOP; other = STOP). Raw rows live in memory only.
r=0; RAW=$(git grep -n -E "$ALT" "$TREE" -- .) || r=$?; [ "$r" -eq 0 ] || STOP tree-producer-rc-"$r"
[ -n "$RAW" ] || STOP tree-zero-rows
# ---- the VALUE GUARD on every tree row, GLOBAL: the row's first detector match digested in memory; its class from the SET and the path; an undeclared digest STOPs
: > "$OUT/tree-classes.txt" || STOP tree-classes-write; nA=0; nB=0; nC=0; SEEN=" "; nseen=0; i=0
while IFS= read -r line; do
  case "$line" in "$TREE:"*) ;; *) STOP tree-row-prefix;; esac
  rest=${line#"$TREE:"}; pl=$(printf '%s' "$rest" | sed -E 's/^([^:]+:[0-9]+):.*$/\1/'); PIPEOK tree-row-projection; [ -n "$pl" ] && [ "$pl" != "$rest" ] || STOP tree-row-projection
  t=${rest#"$pl":}; i=$((i + 1)); if [ -n "${CENSUS_MUTANT_ROW:-}" ] && [ "$i" -eq "$CENSUS_MUTANT_ROW" ]; then t="mutant $(printf 'sk-%040d' 7) in memory only"; fi
  m=0; v=$(printf '%s' "$t" | grep -o -E "$ALT") || m=$?; [ "$m" -eq 0 ] && [ -n "$v" ] || STOP tree-row-no-match; v=${v%%$'\n'*}
  dg=$(printf '%s' "$v" | shasum -a 256 | cut -d' ' -f1); PIPEOK row-digest; [ "${#dg}" -eq 64 ] || STOP row-digest-shape
  k=$(kind_of "$dg") || STOP undeclared-value-at-"$pl"
  case "$k" in fixture) case "$pl" in src/*|tests/*|harness/*|.github/*|CMake*) c=A; nA=$((nA + 1));; *) c=B; nB=$((nB + 1));; esac;; english) c=C; nC=$((nC + 1));; *) STOP kind-token;; esac
  case "$SEEN" in *" $dg "*) ;; *) SEEN="$SEEN$dg "; nseen=$((nseen + 1));; esac
  printf '%s | %s\n' "$pl" "$c" >> "$OUT/tree-classes.txt" || STOP tree-classes-write
done <<< "$RAW"
unset RAW
# ---- the PRODUCT-SCOPED VIEW of the tree: the actual product-prefix rows WITH their class == the pinned product rows, exactly and in order
g=0; grep -E "$PROD" "$OUT/tree-classes.txt" > "$OUT/actual-product.rows" || g=$?; [ "$g" -le 1 ] || STOP product-view-grep
d=0; diff "$OUT/expected-product.rows" "$OUT/actual-product.rows" > "$OUT/tree-product.delta" || d=$?; [ "$d" -eq 0 ] || STOP product-view-delta
# ---- the HISTORY ARM (producer: `git rev-list` over the given refs, then ONE `git grep -l` over every listed commit; each stage checked; paths recorded as DATA)
HREFS=$*; git rev-list "$@" > "$OUT/revs.txt" || STOP rev-list; [ -s "$OUT/revs.txt" ] || STOP rev-list-empty
g=0; bad=$(grep -c -v -E '^[0-9a-f]{40}$' "$OUT/revs.txt") || g=$?; [ "$g" -le 1 ] && [ "$bad" -eq 0 ] || STOP rev-list-shape
REVS=$(cat "$OUT/revs.txt") || STOP rev-list-read; set -- $REVS; [ $# -ge 1 ] || STOP rev-list-args
x=0; git grep -l -E "$ALT" "$@" -- . > "$OUT/history.raw" || x=$?; [ "$x" -eq 0 ] || STOP history-producer-rc-"$x"
g=0; bad=$(grep -c -v -E '^[0-9a-f]{40}:' "$OUT/history.raw") || g=$?; [ "$g" -le 1 ] && [ "$bad" -eq 0 ] || STOP history-row-prefix
sed -E 's/^[0-9a-f]{40}://' "$OUT/history.raw" > "$OUT/history.paths" || STOP history-strip
LC_ALL=C sort -u "$OUT/history.paths" > "$OUT/actual-history.p" || STOP history-reduction; [ -s "$OUT/actual-history.p" ] || STOP history-reduction-empty; rm -f "$OUT/history.raw" "$OUT/history.paths" || STOP history-cleanup
# ---- the HISTORICAL VALUE GUARD, GLOBAL (ONE `git grep -h -o`, its own rc checked BEFORE its output is used; the reduction a separately checked pipeline; every digest in the SET)
x=0; HV1=$(git grep -h -o -E "$ALT" "$@" -- .) || x=$?; [ "$x" -eq 0 ] || STOP history-values-producer-rc-"$x"; [ -n "$HV1" ] || STOP history-values-empty-output
HV=$(printf '%s\n' "$HV1" | LC_ALL=C sort | uniq -c); PIPEOK history-values-reduction; unset HV1; [ -n "$HV" ] || STOP history-values-reduction-empty
nhv=0; : > "$OUT/history-value-digests.txt" || STOP history-digests-write
while IFS= read -r e; do n=$(printf '%s' "$e" | awk '{ print $1 }'); PIPEOK history-value-count; v=$(printf '%s' "$e" | sed -E 's/^ *[0-9]+ //'); PIPEOK history-value-field; dg=$(printf '%s' "$v" | shasum -a 256 | cut -d' ' -f1); PIPEOK history-value-digest; [ "${#dg}" -eq 64 ] || STOP history-value-digest-shape; kind_of "$dg" > /dev/null || STOP undeclared-historical-value-"${dg:0:16}"; printf '%s occurrences=%s\n' "$dg" "$n" >> "$OUT/history-value-digests.txt" || STOP history-digests-write; nhv=$((nhv + 1)); done <<< "$HV"
unset HV
# ---- the PRODUCT-SCOPED VIEW of the history: the unique product paths in history == the unique paths of the pinned product rows
g=0; grep -E "$PROD" "$OUT/actual-history.p" > "$OUT/actual-history-product.p" || g=$?; [ "$g" -le 1 ] || STOP product-history-grep
sed -E 's/:[0-9]+ \| [AC]$//' "$OUT/expected-product.rows" > "$OUT/expected-history-product.unsorted" || STOP product-history-expected; LC_ALL=C sort -u "$OUT/expected-history-product.unsorted" > "$OUT/expected-history-product.p" || STOP product-history-expected-sort; rm -f "$OUT/expected-history-product.unsorted" || STOP product-history-cleanup
d=0; diff "$OUT/expected-history-product.p" "$OUT/actual-history-product.p" > "$OUT/history-product.delta" || d=$?; [ "$d" -eq 0 ] || STOP product-history-delta
# ---- the SUMMARY is written and checked BEFORE it is printed; exit 0 only after both (tree_rows, history_paths and the distinct counts are DATA)
nt=$(awk 'END { print NR }' "$OUT/tree-classes.txt") || STOP count; nh=$(awk 'END { print NR }' "$OUT/actual-history.p") || STOP count; nr=$(awk 'END { print NR }' "$OUT/revs.txt") || STOP count; npt=$(awk 'END { print NR }' "$OUT/actual-product.rows") || STOP count; nph=$(awk 'END { print NR }' "$OUT/actual-history-product.p") || STOP count
printf 'landing_census_2b tree=%s tree_rows=%s history_refs=%s commits=%s history_paths=%s classes A=%s B=%s C=%s accepted_set=%s distinct_current_digests=%s distinct_historical_digests=%s product_tree_rows=%s product_history_paths=%s result=PASS\n' "$TREE" "$nt" "$HREFS" "$nr" "$nh" "$nA" "$nB" "$nC" "$nsetv" "$nseen" "$nhv" "$npt" "$nph" > "$OUT/summary.txt" || STOP summary-write
[ -s "$OUT/summary.txt" ] || STOP summary-empty
cat "$OUT/summary.txt" || STOP summary-print
exit 0
