#!/usr/bin/env bash
# Gate for errno_symbol's table.
#
# ONE property, checked exactly: the ACTIVE switch must EQUAL the mapping
# derived from the target itself --
#
#     singleton group   -> its sole member
#     multi-name group  -> the canonical member in tests/errno_pins.txt
#     unpinned group    -> FAIL (m-3 032747 rule 3; do not guess)
#
# Exact equality subsumes what earlier revisions checked separately and closes
# what they missed:
#   MISSING value            expected has it, switch does not
#   EXTRA value              switch has it, target does not define it -- which
#                            would engage errno_symbol OUTSIDE the namespace,
#                            contradicting the presence rule
#   WRONG name on a GROUP    caught by the pin comparison
#   WRONG name on a SINGLETON  caught too -- a one-way numeric subset check
#                            could not see this at all
#   INVALID PIN              a pin whose canonical is NOT a member of the
#                            target's group, or a signature pinned twice.
#                            Without this the EXPECTED side is not
#                            target-derived: a malformed pin plus a matching
#                            return literal satisfies equality while naming a
#                            symbol from outside the group.
#
# The fixtures run FIRST on every invocation; they are inline rather than a
# second ctest entry because CMakeLists authority is bounded to one add_test.
set -euo pipefail

PINS="${PINS:-tests/errno_pins.txt}"
SRC="${SRC:-src/adapters/secure_io.cpp}"
CXX_BIN="${CXX:-c++}"
CXXSTD="${CXXSTD:--std=c++23}"

# Group signature: member names, sorted, comma-joined. TARGET-STABLE -- integer
# keys are dead (032747 §1). tr|sort|paste, not gawk asort, so this runs under
# the macOS job's BSD awk.
signature() { tr ' ' '\n' <<<"$1" | grep -v '^$' | sort | paste -sd, -; }

expected_mapping() {
  # Unused cross-target pins are intentional: one canonical file covers all
  # supported targets while the active mapping remains strictly per-target.
  local platform="$1" fail=0 value names sig pin hits count
  while read -r value names; do
    [ -z "$value" ] && continue
    if [ "$(wc -w <<<"$names")" -le 1 ]; then
      echo "$value $names"; continue
    fi
    sig="$(signature "$names")"
    hits="$(awk -v k="$sig" '$1==k {print $2}' "$PINS" || true)"
    count="$(printf '%s' "$hits" | grep -c . || true)"
    if [ "$count" -eq 0 ]; then
      echo "FAIL rule 3: value $value has multi-name group {$sig} with NO owner pin." >&2
      echo "  An unpinned group cannot ship. Route it to m-3; do not choose locally." >&2
      fail=1; continue
    fi
    if [ "$count" -gt 1 ]; then
      echo "FAIL invalid pin: signature {$sig} has $count entries in $PINS; exactly one is required." >&2
      fail=1; continue
    fi
    pin="$hits"
    # The pin's canonical token MUST be a member of the target's own group.
    # Without this the expected side is not target-derived at all: a malformed
    # pin plus a matching return literal would satisfy exact equality while
    # naming a symbol from outside the group.
    if ! tr ' ' '\n' <<<"$names" | grep -Fxq "$pin"; then
      echo "FAIL invalid pin: {$sig} names canonical '$pin', which is NOT a member of the target's value-$value group." >&2
      fail=1; continue
    fi
    echo "$value $pin"
  done <<<"$platform"
  return "$fail"
}

check_exact() {
  local platform="$1" table="$2" w fail=0
  w="$(mktemp -d)"
  if ! expected_mapping "$platform" | sort > "$w/expected"; then rm -rf "$w"; return 1; fi
  sort <<<"$table" | grep -v '^$' > "$w/actual" || true
  if ! diff -q "$w/expected" "$w/actual" >/dev/null 2>&1; then
    comm -23 "$w/expected" "$w/actual" | while read -r l; do
      [ -n "$l" ] && echo "FAIL missing-or-misspelled: target requires '$l', the switch does not have it" >&2
    done
    comm -13 "$w/expected" "$w/actual" | while read -r l; do
      [ -n "$l" ] && echo "FAIL extra-or-misspelled: switch has '$l', which is not what the target defines" >&2
    done
    fail=1
  fi
  rm -rf "$w"
  return "$fail"
}

selftest() {
  local w saved="$PINS" got
  w="$(mktemp -d)"; PINS="$w/pins"; printf 'EAGAIN,EWOULDBLOCK EAGAIN\n' > "$PINS"
  _f() { if check_exact "$2" "$3" 2>/dev/null; then got=pass; else got=fail; fi
         [ "$got" = "$1" ] && return 0
         echo "SELFTEST FAIL: $4 wanted $1, got $got" >&2; return 1; }
  _f pass "5 EIO
11 EAGAIN EWOULDBLOCK" "5 EIO
11 EAGAIN" POSITIVE            || { rm -rf "$w"; return 1; }
  _f fail "5 EIO ENEWALIAS" "5 EIO" UNPINNED_GROUP           || { rm -rf "$w"; return 1; }
  _f fail "11 EAGAIN EWOULDBLOCK" "11 EWOULDBLOCK" WRONG_GROUP_MEMBER || { rm -rf "$w"; return 1; }
  _f fail "5 EIO" "5 ENOENT" WRONG_SINGLETON                 || { rm -rf "$w"; return 1; }
  _f fail "5 EIO" "5 EIO
999 EEXTRA" EXTRA_VALUE                                      || { rm -rf "$w"; return 1; }
  _f fail "5 EIO
11 EAGAIN EWOULDBLOCK" "5 EIO" MISSING_VALUE                 || { rm -rf "$w"; return 1; }
  printf 'EAGAIN,EWOULDBLOCK ENOENT\n' > "$PINS"
  _f fail "11 EAGAIN EWOULDBLOCK" "11 ENOENT" INVALID_PIN_NONMEMBER || { rm -rf "$w"; return 1; }
  printf 'EAGAIN,EWOULDBLOCK EAGAIN\nEAGAIN,EWOULDBLOCK EWOULDBLOCK\n' > "$PINS"
  _f fail "11 EAGAIN EWOULDBLOCK" "11 EAGAIN" DUPLICATE_PIN  || { rm -rf "$w"; return 1; }
  rm -rf "$w"; PINS="$saved"
  echo "errno gate selftest: all eight fixtures behaved as specified"
}

selftest

work="$(mktemp -d)"; trap 'rm -rf "$work"' EXIT

# 1. the target's own name->value enumeration, grouped by value. Macros are not
#    enumerable from C directly, so the names drive a generated probe.
echo '#include <cerrno>' | "$CXX_BIN" $CXXSTD -dM -E -x c++ - \
  | grep -E '^#define E[A-Z0-9]+ ' | awk '{print $2}' | sort -u > "$work/names"
{ echo '#include <cerrno>'; echo '#include <cstdio>'; echo 'int main(){'
  while read -r n; do printf '  std::printf("%%d %s\\n", %s);\n' "$n" "$n"; done < "$work/names"
  echo '  return 0; }'; } > "$work/probe.cpp"
"$CXX_BIN" $CXXSTD -o "$work/probe" "$work/probe.cpp"
"$work/probe" | sort -n | awk '{g[$1]=g[$1]" "$2} END {for (v in g) print v g[v]}' \
  | sort -u > "$work/platform_groups"

# 2. the ACTIVE table: value -> chosen name, from the preprocessed TU. The
#    return string literal carries the NAME through preprocessing, so one
#    extraction yields both and no raw-source parse is needed -- an entry
#    inside an inactive #ifdef is correctly absent.
#    THE FLATTENING IS REQUIRED: the compiler brackets every system-header
#    macro expansion with line markers, so `case EIO: return "EIO";` arrives
#    split across four physical lines and a line-oriented grep finds NOTHING.
"$CXX_BIN" $CXXSTD -E -I src "$SRC" > "$work/pp.txt"
awk '/^# [0-9]+ "/ { f = $3; gsub(/"/, "", f); next }
     f ~ /secure_io\.cpp$/ { print }' "$work/pp.txt" \
  | tr '\n' ' ' \
  | grep -oE 'case +[0-9]+ *: *return *"E[A-Z0-9]+"' \
  | sed -E 's/case +([0-9]+) *: *return *"(E[A-Z0-9]+)"/\1 \2/' \
  | sort -u > "$work/table" || true

# 3. POSITIVE CONTROL. An empty extraction must FAIL WITH A DIAGNOSTIC. The
#    `|| true` above is REQUIRED -- a no-match grep exits 1 under `pipefail`
#    and would kill the script before this check could report anything.
if [ ! -s "$work/table" ]; then
  echo "errno gate: no active case labels extracted from $SRC." >&2
  echo "  The switch moved, the extraction broke, or preprocessing failed." >&2
  exit 1
fi

# 4. EXACT equality against the target-derived mapping.
check_exact "$(cat "$work/platform_groups")" "$(cat "$work/table")"

echo "errno gate: switch matches the target-derived mapping exactly ($(wc -l < "$work/table") entries)"
