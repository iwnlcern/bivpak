#!/usr/bin/env bash
# rev41 walk: regate.sh (rev41's BLOCK, retargeted to c10t) on scratch clones at c9 with a synthetic c10 and c10t, against a mirror of the real home's inputs; ctest stubbed on PATH, the head gate stubbed in a walk-only plan copy for the c11 branch
set -u
S=/private/tmp/claude-501/-Users-jack-Programming-bivpak/6fecc389-d499-4128-a827-a4138f47bce6/scratchpad
W=$S/r41/rg; RG=$S/r41/bl/regate.sh; RE=/Users/jack/Programming/bivpak-evidence/s2b-intg-substep2b-impl-1-y3iCLB; CAND=/Users/jack/Programming/bivpak-intg-substep2b-wiring
C9=2893bc53ad0f9d4f3e6f45f7990c86d49f868138
mkdir -p $W/bin; printf '#!/usr/bin/env bash\nexit ${CTEST_RC:-0}\n' > "$W/bin/ctest"; chmod +x "$W/bin/ctest"
ci() { git -c user.name=w -c user.email=w@w commit -q -m "$1"; }
# setup <case> [extra-c10 cmd] [c10t cmd]
setup() { local c=$1 x10=${2-} x10t=${3-}; local d=$W/$c; rm -rf "$d"; mkdir -p "$d"; git clone -q --no-hardlinks "$CAND" "$d/wt"; git -C "$d/wt" checkout -q "$C9"; git -C "$d/wt" checkout -q -b walk
  (cd "$d/wt" && printf '\n// walk: synthetic c10\n' >> src/core/open/open.cpp && { [ -z "$x10" ] || bash -c "$x10"; } && git add -A && ci "walk c10"); C10=$(git -C "$d/wt" rev-parse HEAD)
  (cd "$d/wt" && printf '\n// walk: synthetic c10t\n' >> tests/test_envelope.cpp && { [ -z "$x10t" ] || bash -c "$x10t"; } && git add -A && ci "walk c10t"); C10T=$(git -C "$d/wt" rev-parse HEAD)
  E=$d/evid; mkdir -p "$E/runners" "$E/heads/c10t/H" "$E/receipts" "$E/B" "$E/H" "$E/work"
  printf '%s\n' "$C9" > "$E/commits.c9.txt"; printf '%s\n' "$C10" > "$E/commits.c10.txt"; printf '%s\n' "$C10T" > "$E/commits.c10t.txt"; printf 'H=%s\n' "$C9" > "$E/H.txt"; printf 'rc=0\n' > "$E/runners/task-9.done"
  printf 'headgate label=c10t head=%s tidy_expected=none tidy_findings=0 coverage=37/37 macos_rc0=5 macos_failures=0 container_rc=0 linux_failures=0\n' "$C10T" > "$E/heads/c10t/headgate.txt"
  cp -p "$RE/H/tuples-macos.txt" "$RE/H/tuples-linux.txt" "$E/heads/c10t/"; cp -p "$RE/H/selftest-H.kv" "$RE/H/selftest-H.names" "$E/heads/c10t/"
  cp -p "$RE/H/biv_tests-linux.xml" "$RE/H/ctest-linux-H.junit.xml" "$RE/H/ctest-linux-H.rc" "$E/heads/c10t/H/"
  { cat "$RE/heads/c8T/ctest-status.txt"; printf 'run divergence_envelope_conforms\n'; } > "$E/heads/c10t/ctest-status.txt"
  printf 'mutant=walk\nverdict=ok\n' > "$E/receipts/c10-mutants.rev40.txt"; printf 'walk\n' > "$E/receipts/c10-red.txt"; printf 'walk\n' > "$E/receipts/c10t-red.txt"; printf 'mutant=walk\nverdict=ok\n' > "$E/receipts/c10t-mutants.txt"
  cp -p "$RE/B-cells.txt" "$RE/B-workflow.yml" "$RE/cells.py" "$RE/cellgate.py" "$RE/skipset.py" "$RE/cellpatch.py" "$RE/xmlcases.py" "$E/"; cp -p "$RE/B/tuples-linux.txt" "$E/B/"; cp -p "$RE/H/selftest-H.kv" "$RE/H/r435-family.txt" "$E/H/"
  R=$d/runners; mkdir -p "$R"; printf '%s\n' "$E" > "$R/evid.txt"; cp "$S/r41/plan-walk.md" "$R/plan.md"; printf '%s\n' "$R/plan.md" > "$R/plan-path.txt"; shasum -a 256 "$R/plan.md" | cut -d' ' -f1 > "$R/plan-lock.txt"; cp -p /Users/jack/Programming/bivpak-evidence/s2b-runners-r9Akl6/plan_blocks.py "$R/"; }
run() { local c=$1; local d=$W/$c; o=$(cd "$d/wt" && PATH="$W/bin:$PATH" EVID="$d/evid" RUNNERS="$d/runners" bash "$RG" 2>&1); rc=$?
  echo "case=$c rc=$rc out=$(echo "$o" | tail -1 | cut -c1-80) R=$([ -e "$d/evid/R" ] && echo present || echo absent) H0=$(sed -n 's/^H0=//p' "$d/evid/R/H0.txt" 2>/dev/null | cut -c1-7) H=$(cat "$d/evid/R/H.txt" 2>/dev/null | cut -c1-12) c11=$([ -e "$d/evid/commits.c11.txt" ] && echo yes || echo no) head=$(git -C "$d/wt" log -1 --format=%s | cut -c1-40)"; }
python3 - "$S/r41/rev41.md" "$S/r41/plan-walk.md" <<'PY'
import sys
t=open(sys.argv[1]).read(); m="<!-- BLOCK: headgate.sh -->\n```bash\n"; i=t.index(m)+len(m); k=t.index("\n```\n",i)
t=t[:i]+'printf "stub-headgate %s\\n" "$1"; exit ${HG_RC:-0}'+t[k:]; open(sys.argv[2],'w').write(t)
PY
HGT=heads/c10t
setup yes-unchanged; run yes-unchanged; echo "  H0-is-c10t=$([ "$(sed -n 's/^H0=//p' $W/yes-unchanged/evid/R/H0.txt)" = "$(cat $W/yes-unchanged/evid/commits.c10t.txt)" ] && echo yes || echo no) c10t-paths=$(cat $W/yes-unchanged/evid/R/c10t-paths.txt)"
setup yes-moved; sed -i '' -E 's/^(biv_tests macos successes=)484 /\1486 /' "$W/yes-moved/evid/$HGT/tuples-macos.txt"; run yes-moved; echo "  c11-parent-is-c10t=$([ "$(git -C $W/yes-moved/wt rev-parse HEAD~1)" = "$(cat $W/yes-moved/evid/commits.c10t.txt)" ] && echo yes || echo no)"
setup not-at-c10t; git -C "$W/not-at-c10t/wt" checkout -q HEAD~1; run not-at-c10t
setup parent-not-c10; printf '%040d\n' 0 > "$W/parent-not-c10/evid/commits.c10.txt"; run parent-not-c10
setup grandparent; printf '%s\n' 99136ca635cd4c59b456606aed7d448e1c25a509 > "$W/grandparent/evid/commits.c9.txt"; run grandparent
setup h-mismatch; printf 'H=%040d\n' 0 > "$W/h-mismatch/evid/H.txt"; run h-mismatch
setup no-c10-red; rm "$W/no-c10-red/evid/receipts/c10-red.txt"; run no-c10-red
setup no-c10t-red; rm "$W/no-c10t-red/evid/receipts/c10t-red.txt"; run no-c10t-red
setup c10-verdict-absent; printf 'mutant=walk\n' > "$W/c10-verdict-absent/evid/receipts/c10-mutants.rev40.txt"; run c10-verdict-absent
setup c10t-verdict-absent; printf 'mutant=walk\n' > "$W/c10t-verdict-absent/evid/receipts/c10t-mutants.txt"; run c10t-verdict-absent
setup c10t-verdict-twice; printf 'verdict=ok\n' >> "$W/c10t-verdict-twice/evid/receipts/c10t-mutants.txt"; run c10t-verdict-twice
setup c10t-record-absent; rm "$W/c10t-record-absent/evid/receipts/c10t-mutants.txt"; run c10t-record-absent
setup hg-label-c10; sed -i '' 's/label=c10t/label=c10/' "$W/hg-label-c10/evid/$HGT/headgate.txt"; run hg-label-c10
setup hg-absent; rm "$W/hg-absent/evid/$HGT/headgate.txt"; run hg-absent
setup dirty; printf 'x\n' >> "$W/dirty/wt/README.md"; run dirty
setup r-exists; mkdir "$W/r-exists/evid/R"; run r-exists
setup r-dangling; ln -s "$W/r-dangling/nowhere" "$W/r-dangling/evid/R"; run r-dangling
setup c11-exists; printf 'x\n' > "$W/c11-exists/evid/commits.c11.txt"; run c11-exists
setup home-symlink; ln -s /tmp "$W/home-symlink/evid/zz"; run home-symlink
setup c10-foreign-path 'printf "\n" >> src/cli/main.cpp'; run c10-foreign-path
setup c10t-second-path "" 'printf "\n" >> tests/test_cli.cpp'; run c10t-second-path
setup c10t-product-path "" 'printf "\n" >> src/core/open/open.cpp'; run c10t-product-path
setup census-moved 'printf "\n// repo::restore_entry(x);\n" >> src/core/open/open.cpp'; run census-moved
setup a8-raw 'printf "\n// facts.requested\n" >> src/cli/url_consent.cpp'; run a8-raw
setup failures; sed -i '' -E 's/^(biv_tests macos successes=[0-9]+ failures=)0 /\11 /' "$W/failures/evid/$HGT/tuples-macos.txt"; run failures
setup skip-linux; sed -i '' -E 's/^(expected_skips_observed linux n=)1 /\12 /' "$W/skip-linux/evid/$HGT/tuples-linux.txt"; run skip-linux
setup e3-red; python3 - "$W/e3-red/evid/$HGT/H/biv_tests-linux.xml" <<'PY'
import sys
p=sys.argv[1]; s=open(p).read(); i=s.index('[E3]'); j=s.index('<OverallResult success="true"', i); s=s[:j]+'<OverallResult success="false"'+s[j+len('<OverallResult success="true"'):]; open(p,'w').write(s)
PY
run e3-red
setup e2-mac; CTEST_RC=1 run e2-mac
setup foreign-red; sed -i '' 's/^run divergence_envelope_conforms$/fail divergence_envelope_conforms/' "$W/foreign-red/evid/$HGT/ctest-status.txt"; run foreign-red
setup witness-absent; sed -i '' '/^run divergence_envelope_conforms$/d' "$W/witness-absent/evid/$HGT/ctest-status.txt"; run witness-absent
setup pop-moved; sed -i '' -E 's/^population=.*/population=9999/' "$W/pop-moved/evid/$HGT/selftest-H.kv"; run pop-moved
setup bar-red; printf '1\n' > "$W/bar-red/evid/$HGT/H/ctest-linux-H.rc"; run bar-red
setup hg-c11-red; sed -i '' -E 's/^(biv_tests macos successes=)484 /\1486 /' "$W/hg-c11-red/evid/$HGT/tuples-macos.txt"; HG_RC=1 run hg-c11-red
