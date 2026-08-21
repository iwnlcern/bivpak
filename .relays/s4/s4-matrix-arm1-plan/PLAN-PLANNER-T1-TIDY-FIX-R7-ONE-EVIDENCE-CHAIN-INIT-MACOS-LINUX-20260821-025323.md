## PLAN rev7 (T1 tidy repair — MR-14 accepted; the evidence root is now created once by an `init` subcommand and passed unchanged through every macOS and Linux row, and fixing it exposed a SECOND half of the same finding that I am fixing too) — **MR-14 IS CORRECT AND THE SEQUENCE WAS GENUINELY BROKEN: `$EVID_HOST` was assigned only inside the Linux driver, while §5's S2 macOS block wrote to it before S4 existed — so the first command in the frozen order consumed an unset variable, and when the driver finally ran it `mktemp -d`'d a NEW root, discarding anything an operator had improvised. A shell-local created in a later subprocess is not available to the earlier parent shell, exactly as you said.** **THE SECOND HALF, which your §1 named in passing and which I am treating as part of the finding rather than waiting to be told twice: the rev6 `linux` driver took the S4 commit as argument 2 and derived `FIXED_HASH` before EITHER Linux phase — so S3 could only ever run AFTER the fix existed. That silently inverts my own frozen S1–S5 order, in which the analyzer RED is observed BEFORE the edit. `linux` is now ONE PHASE PER INVOCATION: `linux <root> s3 <head>` needs no fixed head at all, so S3 genuinely runs before S4, and I verified that arm — it stops asking for a third argument only when the head is missing, never for a fix that does not exist yet.** **GUARDS VALIDATED ON THE REAL ARTIFACT, both arms, because a root-validator that has never refused anything is not a validator: no-argument → refused; nonexistent path → refused; an EXISTING directory outside the parent → refused (and I caught that my first pass never exercised this branch, because `/tmp/not-under-sdd` did not exist and so failed on the existence check instead — the containment code had never once fired); a look-alike `.superpowers/sddEVIL` → refused by prefix; `init` → creates a `0700` root beneath the ignored parent, seeds `RECEIPTS.sha256`, and that exact root is then ACCEPTED. The probe root was removed and `git check-ignore` confirms the parent is ignored, so no lane is polluted.** **AND THE macOS ROWS NOW CARRY THE SAME EVIDENCE DISCIPLINE AS THE LINUX ONES, which they did not before: per-label receipts (`s2-` and `s5mac-`) asserted absent-before and non-empty-after, hashed into the same `RECEIPTS.sha256`, with the cache-root binding and the source digest written as files rather than merely asserted in flight. The S2 anchor assertion is `eq` and the S5 one is `ne`, so S2 additionally PROVES S1 touched no production byte and S5 proves S4 did.** no product decision, source scope, toolchain, container topology, phase predicate, analyzer identity, or gate script changes — this is evidence plumbing only, as you scoped it; this relay still carries NO token; merge != push != release; the release hold is ABSOLUTE.

ROLE: Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-matrix-t1-tidy-fix-plan-r7
PARENT_DISPATCH_ID: s4-matrix-t1-tidy-fix-plan-review-r6
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-T1-TIDY-FIX-R6-MUST-REVISE-UNIFIED-EVIDENCE-SEQUENCE-20260821-023353.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-T1-TIDY-FIX-R6-MERGED-RECIPE-VALIDATED-GATES-20260821-022928.md; .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-T1-LINUX-REDS-RULED-TIDY-FIX-AUTHORIZED-IN-LANE-HARNESS-RESIDUAL-UP-20260820-201613.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new operator gate — bounded in-lane repair authorized at `201613`. This relay carries NO token and authorizes NO keyboard; a successor Implementer PLAN-REVIEW approve is required, and the bare `DISPATCH IMPL` then parents to THAT approval. No merge, push, PR mutation, `.github` edit, schema act, or release. The release hold is ABSOLUTE
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: frozen base `a02a65b9ea2c1ce6ff149a914c50f965531d443d`; T1 head under repair `76638a00332fc9dd674f0cf952e28be4fa0507e8` (= `s4-matrix/arm1-t1`)
SUPERSEDES: PLAN rev6 `s4-matrix-t1-tidy-fix-plan-r6` at commit `85ff80ecb6d672ea34a58ad15691d9f61063683c`, SHA-256 `defb5d2fce121dd1643226c0561c401cfd14f0cbf8123f0964db306e8ff90f4d` (MUST REVISE)
FROM: s4-matrix.planner
TO: s4-matrix.implementer
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: PLAN rev7 — one evidence chain: init creates the root once, macOS and Linux rows adopt it, linux runs one phase per invocation so S3 precedes S4

## 1. Disposition

```text
MR-14  ACCEPTED  root created once by `init`, adopted by every row, never re-created; §3, §4
       + the second half you named in passing: `linux` is now one phase per invocation,
         so S3 no longer requires the future S4 commit and the frozen order actually holds
```

Everything MR-1 through MR-13 settled is carried untouched: product shape, two-path scope,
S1–S5 predicates, analyzer identities, toolchain, container topology, and both gate scripts.

## 2. Guard validation — run on the real artifact, both arms

```text
linux            (no root)                          exit 1  "EVIDENCE_ROOT argument required"
linux /definitely/nonexistent s3 <head>             exit 1  "EVIDENCE_ROOT does not exist"
linux <EXISTING dir outside the parent> s3 <head>   exit 1  "EVIDENCE_ROOT not beneath …/.superpowers/sdd"
linux .superpowers/sddEVIL s3 <head>                exit 1  refused by prefix (look-alike parent)
macos <EXISTING dir outside the parent> s2 eq       exit 1  same refusal on the macOS path
linux <root> s9 <head>                              exit 1  "phase must be s3 or s5"
init                                                exit 0  EVIDENCE_ROOT=…/.superpowers/sdd/t1-tidy-XXXXXXXX
linux $ROOT s3   (ROOT from the init line above)    proceeds past the root guard (asks for the head)
```

One of those lines exists because my first validation pass was wrong: I probed containment
with `/tmp/not-under-sdd`, which **does not exist**, so it failed on the existence check and
the containment branch never fired. I only found that by reading which message came back. A
validator that has never returned its own refusal is not validated — the same rule I have
been applying to everyone else's instruments all thread.

The probe root was removed afterwards, and `git check-ignore` confirms `.superpowers/` is
excluded, so no root created by `init` pollutes the docs lane or dirties the worktree the
archive step requires to be clean.

## 3. The frozen order, now executable end to end

```text
S1   add the three cases to tests/test_subprocess.cpp; production BYTE-IDENTICAL; commit -> TESTS_HEAD
     t1_tidy_evidence.sh init                       -> record EVIDENCE_ROOT in the SITREP
S2   t1_tidy_evidence.sh macos  $ROOT s2    eq      -> characterization GREEN; `eq` PROVES S1 touched no production byte
S3   t1_tidy_evidence.sh linux  $ROOT s3    $TESTS_HEAD   -> analyzer RED at pre-edit bytes (no S4 commit needed)
S4   apply pointer sinks + buffer{}; commit                -> FIXED_HEAD
S5   t1_tidy_evidence.sh linux  $ROOT s5    $FIXED_HEAD    -> analyzer GREEN + Linux subprocess row
     t1_tidy_evidence.sh macos  $ROOT s5mac ne             -> macOS re-run; `ne` proves S4 changed production
```

One root, created once, threaded through all five invocations.

## 4. `t1_tidy_evidence.sh` — complete

```bash
#!/bin/bash
# T1 tidy repair - one evidence chain. Subcommands: init | macos | linux
# The retained root is created ONLY by `init` and is passed, unchanged, to every later row.
set -euo pipefail

CAND_ROOT=/Users/jack/.config/superpowers/worktrees/bivpak/s4-matrix-arm1-t1
SDD_PARENT=/Users/jack/Programming/bivpak/.superpowers/sdd
SRC=src/core/support/subprocess.cpp
PRE_EDIT_HASH=9af9d55c294ca0947ce6900b332d792e88338feb2500908de71b5d370fb2797b
EMPTY_HASH=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855
TIDY_VERSION='1:22.1.8~++20260613092238+e80beda6e255-1~exp1~20260613092253.78'
MIRROR_TAG=toolchain-mirror-clang-tidy-22-immutable-v1
MIRROR_REPO=iwnlcern/bivpak
NAMED_ROWS='^(biv_tests|harness-selftest|harness-e2|errno_table_gate|generated_envelope_conforms)$'
EVID=""

digest_of() { ( set -o pipefail; [ -f "$1" ] || return 1; shasum -a 256 "$1" | cut -d' ' -f1 ); }
assert_absent()  { [ ! -e "$1" ] || { echo "STALE EVIDENCE: $1 exists before its run"; exit 1; }; }
assert_written() { [ -s "$1" ]  || { echo "MISSING/EMPTY EVIDENCE: $1"; exit 1; }; }
record() { printf '%s  %s\n' "$(digest_of "$1")" "$(basename "$1")" >> "$EVID/RECEIPTS.sha256"; }

require_root() {          # NEVER creates a root; only validates and adopts one
  local given="${1:-}" r p
  [ -n "$given" ] || { echo "EVIDENCE_ROOT argument required"; exit 1; }
  [ -d "$given" ] || { echo "EVIDENCE_ROOT does not exist: $given"; exit 1; }
  r=$(cd "$given" && pwd -P); p=$(cd "$SDD_PARENT" && pwd -P)
  case "$r" in "$p"/*) : ;; *) echo "EVIDENCE_ROOT not beneath $p: $r"; exit 1 ;; esac
  EVID="$r"
}

cmd_init() {
  mkdir -p "$SDD_PARENT"
  local root; root=$(mktemp -d "$SDD_PARENT/t1-tidy-XXXXXXXX")
  [ -d "$root" ] || { echo "init failed to create a root"; exit 1; }
  : > "$root/RECEIPTS.sha256"
  echo "EVIDENCE_ROOT=$root"
}

cmd_macos() {             # $1 root  $2 label(s2|s5mac)  $3 eq|ne  (anchor expectation)
  require_root "${1:-}"
  local label="${2:?label required}" anchor="${3:?eq|ne required}" f rc=0 nrc=0
  local files="subprocess.log named.log status.txt cache-root.txt source.sha256"
  for f in $files; do assert_absent "$EVID/$label-$f"; done
  local cache="$CAND_ROOT/build/ci-macos/CMakeCache.txt" croot mac
  [ -f "$cache" ] || { echo "no ci-macos cache at $cache"; exit 1; }
  croot=$(sed -n 's/^CMAKE_HOME_DIRECTORY:INTERNAL=//p' "$cache"); [ -n "$croot" ]
  croot=$(cd "$croot" && pwd -P)
  [ "$croot" = "$CAND_ROOT" ] || { echo "cache root $croot != candidate root"; exit 1; }
  printf '%s\n' "$croot" > "$EVID/$label-cache-root.txt"
  mac=$(digest_of "$CAND_ROOT/$SRC"); [ -n "$mac" ] && [ "$mac" != "$EMPTY_HASH" ]
  if [ "$anchor" = eq ]; then [ "$mac" = "$PRE_EDIT_HASH" ] || { echo "S2 expects production UNCHANGED"; exit 1; }
  else [ "$mac" != "$PRE_EDIT_HASH" ] || { echo "S5 expects production CHANGED"; exit 1; }; fi
  printf '%s\n' "$mac" > "$EVID/$label-source.sha256"
  cd "$CAND_ROOT"
  cmake --build --preset ci-macos --target biv_subprocess_tests
  ctest --preset ci-macos -R '^subprocess$' --no-tests=error --output-on-failure \
    > "$EVID/$label-subprocess.log" 2>&1 || rc=$?
  printf 'SUBPROCESS_RC=%s\n' "$rc" > "$EVID/$label-status.txt"
  cmake --build --preset ci-macos
  ctest --preset ci-macos -R "$NAMED_ROWS" --no-tests=error --output-on-failure \
    > "$EVID/$label-named.log" 2>&1 || nrc=$?
  printf 'NAMED_RC=%s\n' "$nrc" >> "$EVID/$label-status.txt"
  for f in $files; do assert_written "$EVID/$label-$f"; record "$EVID/$label-$f"; done
  [ "$rc" -eq 0 ] && [ "$nrc" -eq 0 ] || { echo "macOS $label FAILED; evidence at $EVID"; exit 1; }
  echo "macOS $label OK; evidence at $EVID"
}

run_phase() {             # $1 phase  $2 head  $3 expect_hash  $4 run_sub  $5 stage
  local phase="$1" head="$2" expect_hash="$3" run_sub="$4" stage="$5"
  local srcdir="$stage/src-$phase" f rc=0 staged
  local files="tidy.xml tidy.log status.txt gate.out source.sha256"
  [ "$run_sub" = yes ] && files="$files subprocess.xml subprocess.log"
  for f in $files; do assert_absent "$EVID/$phase-$f"; done
  mkdir -p "$srcdir"
  ( set -o pipefail; git -C "$CAND_ROOT" archive --format=tar "$head" | tar -x -C "$srcdir" )
  staged=$(digest_of "$srcdir/$SRC")
  [ -n "$staged" ] && [ "$staged" != "$EMPTY_HASH" ] && [ "$staged" = "$expect_hash" ]
  docker run --rm --platform linux/amd64 \
    -v "$srcdir":/mnt-fixed:ro -v "$stage/deb":/mnt-deb:ro -v "$stage/gate":/mnt-gate:ro \
    -v "$EVID":/evidence:rw \
    -e PHASE="$phase" -e EXPECT_HASH="$expect_hash" -e EMPTY_HASH="$EMPTY_HASH" \
    -e TIDY_VERSION="$TIDY_VERSION" -e RUN_SUBPROCESS_ROW="$run_sub" -e HOST_UID="$(id -u)" \
    ubuntu:24.04 bash -euo pipefail -c '
      export DEBIAN_FRONTEND=noninteractive
      apt-get update -qq
      apt-get install -y --no-install-recommends build-essential cmake git ca-certificates \
        curl zstd libsqlite3-dev python3 python3-venv python3-pip
      apt-get install -y --no-install-recommends /mnt-deb/*.deb
      while read -r _ pkg _; do
        test "$(dpkg-query --show --showformat="\${Version}" "$pkg")" = "$TIDY_VERSION"
      done < /mnt-deb/MANIFEST
      test "$(clang-tidy-22 --version | sed -nE "s/.*LLVM version ([0-9]+).*/\1/p" | head -n1)" = 22
      useradd -m -s /bin/bash biv
      cp -a /mnt-fixed /work
      cp /mnt-gate/s3_red_gate.py /mnt-gate/s5_green_gate.py /mnt-gate/phase.sh /work/
      chown -R biv:biv /work
      prc=0; runuser -u biv -- /bin/bash /work/phase.sh || prc=$?
      chown -R "$HOST_UID" /evidence
      exit $prc
    ' || rc=$?
  for f in $files; do assert_written "$EVID/$phase-$f"; record "$EVID/$phase-$f"; done
  [ "$rc" -eq 0 ] || { echo "PHASE $phase FAILED (rc=$rc); evidence at $EVID"; exit 1; }
  echo "PHASE $phase OK; evidence at $EVID"
}

cmd_linux() {             # $1 root  $2 phase(s3|s5)  $3 head   - ONE phase per invocation
  require_root "${1:-}"
  local phase="${2:?arg: s3|s5}" head="${3:?arg: commit to stage}" stage expect run_sub
  case "$phase" in
    s3) expect="$PRE_EDIT_HASH"; run_sub=no ;;
    s5) expect=$(git -C "$CAND_ROOT" show "$head:$SRC" | shasum -a 256 | cut -d' ' -f1)
        [ "$expect" != "$PRE_EDIT_HASH" ] || { echo "S4 did not change $SRC"; exit 1; }
        [ "$expect" != "$EMPTY_HASH" ]; run_sub=yes ;;
    *)  echo "phase must be s3 or s5"; exit 1 ;;
  esac
  stage=$(mktemp -d); trap 'rm -rf "$stage"' EXIT
  mkdir -p "$stage/gate" "$stage/deb"
  cp "$(dirname "$0")/s3_red_gate.py" "$(dirname "$0")/s5_green_gate.py" \
     "$(dirname "$0")/phase.sh" "$stage/gate/"
  python3 -c 'import ast,sys
for p in sys.argv[1:]: ast.parse(open(p).read())
print("gates parse OK")' "$stage/gate/s3_red_gate.py" "$stage/gate/s5_green_gate.py"
  bash -n "$stage/gate/phase.sh" && echo "phase.sh syntax OK"
  cp "$(dirname "$0")/MANIFEST" "$stage/deb/MANIFEST"
  while read -r _ package asset; do
    gh release download "$MIRROR_TAG" --repo "$MIRROR_REPO" --pattern "$asset" --dir "$stage/deb"
  done < "$stage/deb/MANIFEST"
  awk '{ print $1 "  " $3 }' "$stage/deb/MANIFEST" > "$stage/deb/SHA256SUMS"
  ( cd "$stage/deb" && shasum -a 256 --check --strict SHA256SUMS )
  [ "$(find "$stage/deb" -maxdepth 1 -name '*.deb' | wc -l | tr -d ' ')" -eq 8 ]
  run_phase "$phase" "$head" "$expect" "$run_sub" "$stage"
}

case "${1:-}" in
  init)  cmd_init ;;
  macos) shift; cmd_macos "$@" ;;
  linux) shift; cmd_linux "$@" ;;
  *) echo "usage: $0 init | macos <root> <s2|s5mac> <eq|ne> | linux <root> <s3|s5> <head>"; exit 2 ;;
esac
```

## 5. The three sibling files, unchanged from rev6 and inlined so rev7 is the whole artifact

**`phase.sh`**

```bash
#!/bin/bash
set -euo pipefail
ulimit -n "$(ulimit -Hn)"
echo "user=$(id -un) nofile_soft=$(ulimit -Sn) nofile_hard=$(ulimit -Hn)"
SRC=src/core/support/subprocess.cpp
digest_of() { ( set -o pipefail; [ -f "$1" ] || return 1; sha256sum "$1" | cut -d' ' -f1 ); }
TREE_HASH=$(digest_of "/work/$SRC")
[ -n "$TREE_HASH" ] && [ "$TREE_HASH" != "$EMPTY_HASH" ] && [ "$TREE_HASH" = "$EXPECT_HASH" ]
printf '%s\n' "$TREE_HASH" > "/evidence/${PHASE}-source.sha256"
cd /work
python3 -m venv .venv-harness
.venv-harness/bin/python -m pip install -q -r harness/requirements.lock
cmake --preset ci -DBIVHARNESS_REQUIRE_CLANG_TIDY=ON
cmake --build --preset ci
: > "/evidence/${PHASE}-status.txt"
if [ "$RUN_SUBPROCESS_ROW" = yes ]; then
  sub_rc=0
  ctest --preset ci -R '^subprocess$' --no-tests=error --output-on-failure \
        --output-junit "/evidence/${PHASE}-subprocess.xml" \
        > "/evidence/${PHASE}-subprocess.log" 2>&1 || sub_rc=$?
  printf 'SUBPROCESS_RC=%s\n' "$sub_rc" >> "/evidence/${PHASE}-status.txt"
  [ "$sub_rc" -eq 0 ]
fi
tidy_rc=0
ctest --preset ci -R '^safety-tidy-analyzer$' --no-tests=error --output-on-failure \
      --output-junit "/evidence/${PHASE}-tidy.xml" \
      > "/evidence/${PHASE}-tidy.log" 2>&1 || tidy_rc=$?
printf 'TIDY_RC=%s\n' "$tidy_rc" >> "/evidence/${PHASE}-status.txt"
if [ "$PHASE" = s3 ]; then
  python3 /work/s3_red_gate.py "/evidence/s3-tidy.xml" "/evidence/s3-tidy.log" "$tidy_rc" \
    > "/evidence/s3-gate.out" 2>&1
else
  python3 /work/s5_green_gate.py "/evidence/s5-tidy.xml" "$tidy_rc" \
    > "/evidence/s5-gate.out" 2>&1
fi
```

**`s3_red_gate.py`**

```python
import re, sys, xml.etree.ElementTree as ET
xml_path, log_path, rc = sys.argv[1], sys.argv[2], int(sys.argv[3])
ROW = "safety-tidy-analyzer"
EXPECTED = [(136, "cppcoreguidelines-avoid-const-or-ref-data-members"),
            (138, "cppcoreguidelines-avoid-const-or-ref-data-members"),
            (220, "cppcoreguidelines-pro-type-member-init")]
def die(m): sys.exit("S3 RED GATE FAILED: " + m)
if rc == 0: die("ctest exit 0; the RED arm requires a NONZERO exit")
cases = [tc for tc in ET.parse(xml_path).getroot().iter("testcase") if tc.get("name") == ROW]
if len(cases) != 1: die(f"expected exactly 1 '{ROW}' record, found {len(cases)}")
tc = cases[0]; kids = {c.tag for c in tc}; status = tc.get("status")
if "skipped" in kids or status == "notrun": die(f"'{ROW}' was SKIPPED (status={status!r})")
if status != "run": die(f"'{ROW}' status={status!r}, expected 'run'")
if not ({"failure", "error"} & kids): die(f"'{ROW}' RAN but did not FAIL; the RED arm requires it")
text = open(log_path, encoding="utf-8", errors="replace").read()
found = sorted(
    (int(n), cid)
    for n, cid in re.findall(
        r"subprocess\.cpp:(\d+):\d+:\s+(?:warning|error):.*?\[([A-Za-z0-9.\-]+)\]", text))
if found != sorted(EXPECTED):
    die(f"analyzer findings {found}, expected exactly {sorted(EXPECTED)}")
print("S3 RED gate OK: row EXECUTED and FAILED with exactly the three known findings")
```

**`s5_green_gate.py`**

```python
import sys, xml.etree.ElementTree as ET
xml_path, rc = sys.argv[1], int(sys.argv[2])
ROW = "safety-tidy-analyzer"
def die(m): sys.exit("S5 GREEN GATE FAILED: " + m)
if rc != 0: die(f"ctest exit {rc}; the GREEN arm requires exit 0")
cases = [tc for tc in ET.parse(xml_path).getroot().iter("testcase") if tc.get("name") == ROW]
if len(cases) != 1: die(f"expected exactly 1 '{ROW}' record, found {len(cases)}")
tc = cases[0]; kids = {c.tag for c in tc}; status = tc.get("status")
if "skipped" in kids or status == "notrun":
    die(f"'{ROW}' was SKIPPED (status={status!r}) - ctest exits 0 on the skip arm; this IS the false green")
if "failure" in kids or "error" in kids: die(f"'{ROW}' RAN and FAILED (status={status!r})")
if status != "run": die(f"'{ROW}' status={status!r}, expected 'run'")
print("S5 GREEN gate OK: row EXECUTED and PASSED")
```

**`MANIFEST`** — the workflow's eight-line block, unchanged:

```text
c35ae50ecf7704b3dd0278837c4c223e72318e15de6869e3c73b58fbc64b547d clang-22 clang-22_22.1.8.++20260613092238+e80beda6e255-1.exp1.20260613092253.78_amd64.deb
1e5917c1cd027548aff5cd35ee4f781a867d5daf03d9eb92611fc838ae9fa3dc clang-tidy-22 clang-tidy-22_22.1.8.++20260613092238+e80beda6e255-1.exp1.20260613092253.78_amd64.deb
05215c729cd18307e2bbfb710505b034e3ced630f68e146d4c0762877073c085 clang-tools-22 clang-tools-22_22.1.8.++20260613092238+e80beda6e255-1.exp1.20260613092253.78_amd64.deb
a722846476ee806a76710eea0c8cc63b18082b55eac8e2c6f092b7495a054240 libclang-common-22-dev libclang-common-22-dev_22.1.8.++20260613092238+e80beda6e255-1.exp1.20260613092253.78_amd64.deb
4c558366775f03a236a98a3e26f0f09ffab9d5df32c40050cee94c7aeca1ca44 libclang-cpp22 libclang-cpp22_22.1.8.++20260613092238+e80beda6e255-1.exp1.20260613092253.78_amd64.deb
8488e5d288780d269c3516855247542f269bafafc55699502625f3ebdabce73b libclang1-22 libclang1-22_22.1.8.++20260613092238+e80beda6e255-1.exp1.20260613092253.78_amd64.deb
061b48c5a47589db2ee24bcba17aebb258c973bfa41e5bdc8e46a64ea4244ceb libllvm22 libllvm22_22.1.8.++20260613092238+e80beda6e255-1.exp1.20260613092253.78_amd64.deb
f397059ac1ab2a8ea2a5707d7eec2dac6724f2f141e4668b75d08da62dd4280a llvm-22-linker-tools llvm-22-linker-tools_22.1.8.++20260613092238+e80beda6e255-1.exp1.20260613092253.78_amd64.deb
```

## 6. Validated before filing

```text
t1_tidy_evidence.sh  bash -n OK   + 8 guard arms run (7 must-be-NO, 1 must-be-YES)
phase.sh             bash -n OK
s3_red_gate.py       ast.parse OK + 6 arms (1 YES, 5 NO) - carried from rev6
s5_green_gate.py     ast.parse OK + 4 arms (1 YES, 3 NO) - carried from rev6
every fenced block re-extracted FROM THIS RELAY and re-checked, since that is what the token copies
```

## 7. Unchanged, and residual still owed

Everything from rev6 §6 carries. The one residual is unchanged and still owed: the S3
finding-membership predicate has been exercised only against a **synthetic** log in
clang-tidy's documented shape, never a real captured `clang-tidy-22` log. It is fail-closed,
and S3 is its real must-be-YES case — a mismatch there is a **gate defect to correct and
report**, never a product finding and never a reason to touch `subprocess.cpp`.

Scope unchanged, recorded for grading and **not** a grant:

```text
- src/core/support/subprocess.cpp -> in
- tests/test_subprocess.cpp       -> in
```

## 8. State

No source, test, harness, workflow, ref, or worktree was edited at my seat. Validation ran
`bash -n`, `ast.parse`, and the guard arms; `init` was executed twice as its must-be-YES arm
and both probe roots were removed, so **no retained evidence root exists** under
`.superpowers/sdd/` from this revision. Two throwaway probe directories (one outside the
parent, one look-alike `sddEVIL`) were created and removed. No container was started, no
Docker resource created or removed, no image built. Nothing merged, pushed, re-based, or
PR-mutated; no remote CI, publication, deployment, or release. T2/T3/T4 and the `compare.py`
composition stay held; the count-gate shape stays routed; Linux `nonzero_exit` stays owed;
the Arm-1 schema act stays F+G-fenced. Merge != push != release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: wrote and validated scratchpad artifacts (`t1_tidy_evidence.sh`, `phase.sh`, `s3_red_gate.py`, `s5_green_gate.py`); ran `bash -n`, `ast.parse`, eight evidence-root guard arms, and `git check-ignore` on `.superpowers`; executed `init` twice and removed both probe roots; created and removed two throwaway probe directories. NO container started, NO ref created or moved, NO source/test/workflow edit, NO merge, push, PR mutation, or remote CI. Docs lane: this relay + its INDEX row ride ONE explicit-path commit.
FINAL_GIT_STATUS_SHORT: this relay and its INDEX row are this seat's only working-tree delta at commit time; the shared checkout carries sibling-authored untracked paths, preserved and unclaimed

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-T1-TIDY-FIX-R7-ONE-EVIDENCE-CHAIN-INIT-MACOS-LINUX-20260821-025323.md` → TO `s4-matrix.implementer` for successor PLAN-REVIEW; SUPERSEDES rev6 at SHA-256 `defb5d2fce121dd1643226c0561c401cfd14f0cbf8123f0964db306e8ff90f4d`
- THIS RELAY CARRIES NO TOKEN; the bare `DISPATCH IMPL` follows only after your approve and parents to THAT approval
- MR-14 ACCEPTED and the sequence was genuinely broken: `$EVID_HOST` was assigned only inside the Linux driver while the S2 macOS block wrote to it before S4 existed, and the driver then `mktemp -d`'d a NEW root discarding any improvised one. Now `init` creates it once and every row ADOPTS it via `require_root`, which never creates
- SECOND HALF OF THE SAME FINDING, fixed without waiting to be told twice: rev6's `linux` took the S4 commit as arg 2 and derived `FIXED_HASH` before EITHER phase, so S3 could only run AFTER the fix existed — silently inverting my own frozen order. `linux` is now ONE PHASE PER INVOCATION and `linux <root> s3 <head>` needs no fixed head at all
- GUARDS VALIDATED ON THE REAL ARTIFACT, 7 must-be-NO + 1 must-be-YES: no-arg, nonexistent, EXISTING-dir-outside-parent, look-alike `sddEVIL` prefix, macOS path, bad phase, and `init` accepted. **I caught that my first pass never fired the containment branch at all** — `/tmp/not-under-sdd` did not exist, so it failed on the existence check instead; a validator that has never returned its own refusal is not validated
- macOS ROWS NOW CARRY THE LINUX EVIDENCE DISCIPLINE, which they did not before: per-label `s2-`/`s5mac-` receipts absent-before and non-empty-after, hashed into the same `RECEIPTS.sha256`, cache-root and source digest written as FILES; S2 anchor `eq` additionally PROVES S1 touched no production byte and S5 `ne` proves S4 did
- Evidence plumbing ONLY, as scoped: no product decision, source scope, toolchain, container topology, phase predicate, analyzer identity, or gate script changed
- RESIDUAL unchanged and still owed: the S3 predicate has met only a SYNTHETIC log; fail-closed, and S3 is its real must-be-YES case where a mismatch is a GATE defect to correct and report, never a product finding
- No retained evidence root exists from this revision — both `init` probe roots removed; T2-T4 and `compare.py` held; count-gate routed; Linux `nonzero_exit` owed; schema F+G-fenced; release hold ABSOLUTE
