#!/usr/bin/env bash
# rev39 walk: regate.sh (rev39's BLOCK) on a scratch clone at c9 with a synthetic c10, against a mirror of the real home's inputs; ctest stubbed on PATH (the real harness-e2 is measured by the implementer), the head gate stubbed in a walk-only plan copy for the c11 branch
set -u
S=/private/tmp/claude-501/-Users-jack-Programming-bivpak/6fecc389-d499-4128-a827-a4138f47bce6/scratchpad/r39
W=$S/w/rg; RG=$S/b/regate.sh; RE=/Users/jack/Programming/bivpak-evidence/s2b-intg-substep2b-impl-1-y3iCLB; CAND=/Users/jack/Programming/bivpak-intg-substep2b-wiring
C9=2893bc53ad0f9d4f3e6f45f7990c86d49f868138
mkstub() { mkdir -p "$W/bin"; printf '#!/usr/bin/env bash\nexit ${CTEST_RC:-0}\n' > "$W/bin/ctest"; chmod +x "$W/bin/ctest"; }
setup() { local c=$1; local d=$W/$c; rm -rf "$d"; mkdir -p "$d"; git clone -q --no-hardlinks "$CAND" "$d/wt"; git -C "$d/wt" checkout -q "$C9"; git -C "$d/wt" checkout -q -b walk
  printf '\n// rev39 walk: synthetic c10\n' >> "$d/wt/tests/test_envelope.cpp"; git -C "$d/wt" -c user.name=w -c user.email=w@w commit -q -am "walk c10"; C10=$(git -C "$d/wt" rev-parse HEAD)
  E=$d/evid; mkdir -p "$E/runners" "$E/heads/c10/H" "$E/receipts" "$E/B" "$E/H" "$E/work"
  printf '%s\n' "$C9" > "$E/commits.c9.txt"; printf '%s\n' "$C10" > "$E/commits.c10.txt"; printf 'H=%s\n' "$C9" > "$E/H.txt"; printf 'rc=0\n' > "$E/runners/task-9.done"
  printf 'headgate label=c10 head=%s tidy_expected=none tidy_findings=0 coverage=37/37 macos_rc0=5 macos_failures=0 container_rc=0 linux_failures=0\n' "$C10" > "$E/heads/c10/headgate.txt"
  cp -p "$RE/H/tuples-macos.txt" "$RE/H/tuples-linux.txt" "$E/heads/c10/"; cp -p "$RE/H/selftest-H.kv" "$RE/H/selftest-H.names" "$E/heads/c10/"
  cp -p "$RE/H/biv_tests-linux.xml" "$RE/H/ctest-linux-H.junit.xml" "$RE/H/ctest-linux-H.rc" "$E/heads/c10/H/"
  { cat "$RE/heads/c8T/ctest-status.txt"; printf 'run divergence_envelope_conforms\n'; } > "$E/heads/c10/ctest-status.txt"
  printf 'walk\n' > "$E/receipts/c10-mutants.txt"; printf 'walk\n' > "$E/receipts/c10-red.txt"
  cp -p "$RE/B-cells.txt" "$RE/B-workflow.yml" "$RE/cells.py" "$RE/cellgate.py" "$RE/skipset.py" "$RE/cellpatch.py" "$RE/xmlcases.py" "$E/"; cp -p "$RE/B/tuples-linux.txt" "$E/B/"; cp -p "$RE/H/selftest-H.kv" "$RE/H/r435-family.txt" "$E/H/"
  R=$d/runners; mkdir -p "$R"; printf '%s\n' "$E" > "$R/evid.txt"; cp "$S/w/plan-walk.md" "$R/plan.md"; printf '%s\n' "$R/plan.md" > "$R/plan-path.txt"; shasum -a 256 "$R/plan.md" | cut -d' ' -f1 > "$R/plan-lock.txt"; cp -p /Users/jack/Programming/bivpak-evidence/s2b-runners-UG0MP0/plan_blocks.py "$R/"
  find "$E" -type f | sort > "$d/evid.before"; }
run() { local c=$1; local d=$W/$c; o=$(cd "$d/wt" && PATH="$W/bin:$PATH" EVID="$d/evid" RUNNERS="$d/runners" bash "$RG" 2>&1); rc=$?
  echo "case=$c rc=$rc out=$(echo "$o" | tail -1 | cut -c1-80) R=$([ -e "$d/evid/R" ] && echo present || echo absent) H=$(cat "$d/evid/R/H.txt" 2>/dev/null | cut -c1-12) c11=$([ -e "$d/evid/commits.c11.txt" ] && echo yes || echo no) head=$(git -C "$d/wt" log -1 --format=%s | cut -c1-30)"; }
# the walk-only plan: rev39 with the headgate.sh block body replaced by a stub that records its label and exits 0
python3 - "$S/rev39.md" "$S/w/plan-walk.md" <<'PY'
import sys
t=open(sys.argv[1]).read(); m="<!-- BLOCK: headgate.sh -->\n```bash\n"; i=t.index(m)+len(m); k=t.index("\n```\n",i)
t=t[:i]+'printf "stub-headgate %s\\n" "$1"; exit ${HG_RC:-0}'+t[k:]; open(sys.argv[2],'w').write(t)
PY
mkstub
setup yes-unchanged; run yes-unchanged
setup yes-moved; sed -i '' -E 's/^(biv_tests macos successes=)484 /\1486 /' "$W/yes-moved/evid/heads/c10/tuples-macos.txt"; run yes-moved
setup not-at-c10; git -C "$W/not-at-c10/wt" checkout -q "$C9"; run not-at-c10
setup h-mismatch; printf 'H=%040d\n' 0 > "$W/h-mismatch/evid/H.txt"; run h-mismatch
setup no-receipts; rm "$W/no-receipts/evid/receipts/c10-red.txt"; run no-receipts
setup hg-label; sed -i '' 's/label=c10/label=c8T/' "$W/hg-label/evid/heads/c10/headgate.txt"; run hg-label
setup dirty; printf 'x\n' >> "$W/dirty/wt/README.md"; run dirty
setup r-exists; mkdir "$W/r-exists/evid/R"; run r-exists
setup r-dangling; ln -s "$W/r-dangling/nowhere" "$W/r-dangling/evid/R"; run r-dangling
setup c11-exists; printf 'x\n' > "$W/c11-exists/evid/commits.c11.txt"; run c11-exists
setup home-symlink; ln -s /tmp "$W/home-symlink/evid/zz"; run home-symlink
setup foreign-path; (cd "$W/foreign-path/wt" && git reset -q --soft HEAD~1 && printf '\n' >> src/cli/main.cpp && git add -A && git -c user.name=w -c user.email=w@w commit -q -m "walk c10" && git rev-parse HEAD > "$W/foreign-path/evid/commits.c10.txt"); C=$(cat "$W/foreign-path/evid/commits.c10.txt"); sed -i '' -E "s/head=[0-9a-f]{40}/head=$C/" "$W/foreign-path/evid/heads/c10/headgate.txt"; run foreign-path
setup census-moved; (cd "$W/census-moved/wt" && git reset -q --soft HEAD~1 && printf '\n// repo::restore_entry(x);\n' >> src/core/open/open.cpp && git add -A && git -c user.name=w -c user.email=w@w commit -q -m "walk c10" && git rev-parse HEAD > "$W/census-moved/evid/commits.c10.txt"); C=$(cat "$W/census-moved/evid/commits.c10.txt"); sed -i '' -E "s/head=[0-9a-f]{40}/head=$C/" "$W/census-moved/evid/heads/c10/headgate.txt"; run census-moved
setup a8-raw; (cd "$W/a8-raw/wt" && git reset -q --soft HEAD~1 && printf '\n// facts.requested\n' >> src/cli/url_consent.cpp && git add -A && git -c user.name=w -c user.email=w@w commit -q -m "walk c10" && git rev-parse HEAD > "$W/a8-raw/evid/commits.c10.txt"); C=$(cat "$W/a8-raw/evid/commits.c10.txt"); sed -i '' -E "s/head=[0-9a-f]{40}/head=$C/" "$W/a8-raw/evid/heads/c10/headgate.txt"; run a8-raw
setup failures; sed -i '' -E 's/^(biv_tests macos successes=[0-9]+ failures=)0 /\11 /' "$W/failures/evid/heads/c10/tuples-macos.txt"; run failures
setup skip-linux; sed -i '' -E 's/^(expected_skips_observed linux n=)1 /\12 /' "$W/skip-linux/evid/heads/c10/tuples-linux.txt"; run skip-linux
setup e3-red; python3 - "$W/e3-red/evid/heads/c10/H/biv_tests-linux.xml" <<'PY'
import sys,re
p=sys.argv[1]; s=open(p).read(); i=s.index('[E3]'); j=s.index('<OverallResult success="true"', i); s=s[:j]+'<OverallResult success="false"'+s[j+len('<OverallResult success="true"'):]; open(p,'w').write(s)
PY
run e3-red
setup e2-mac; CTEST_RC=1 run e2-mac
setup foreign-red; sed -i '' 's/^run divergence_envelope_conforms$/fail divergence_envelope_conforms/' "$W/foreign-red/evid/heads/c10/ctest-status.txt"; run foreign-red
setup witness-absent; sed -i '' '/^run divergence_envelope_conforms$/d' "$W/witness-absent/evid/heads/c10/ctest-status.txt"; run witness-absent
setup pop-moved; sed -i '' -E 's/^population=.*/population=9999/' "$W/pop-moved/evid/heads/c10/selftest-H.kv"; run pop-moved
setup bar-red; printf '1\n' > "$W/bar-red/evid/heads/c10/H/ctest-linux-H.rc"; run bar-red
setup hg-c11-red; sed -i '' -E 's/^(biv_tests macos successes=)484 /\1486 /' "$W/hg-c11-red/evid/heads/c10/tuples-macos.txt"; HG_RC=1 run hg-c11-red
