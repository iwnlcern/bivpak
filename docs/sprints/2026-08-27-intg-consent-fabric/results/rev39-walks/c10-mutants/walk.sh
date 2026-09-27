# the c10-mutants.sh precondition walk as it ran (zsh, scratch paths as run); B0 is the regate walk's yes-unchanged home (a clone whose `walk` branch head plays c10)
S=/private/tmp/claude-501/-Users-jack-Programming-bivpak/6fecc389-d499-4128-a827-a4138f47bce6/scratchpad/r39; B0=$S/w/rg/yes-unchanged
mm() { local c=$1; rm -rf $S/w/m/$c; mkdir -p $S/w/m/$c; git clone -q --no-hardlinks $B0/wt $S/w/m/$c/wt; git -C $S/w/m/$c/wt checkout -q walk; E=$S/w/m/$c/evid; mkdir -p $E/receipts $E/code; cp -p $B0/evid/commits.c9.txt $B0/evid/commits.c10.txt $E/
  (cd $S/w/m/$c/wt && python3 -c "p='src/core/report/envelope.cpp'; s=open(p).read().split('\n'); s[0]='// walk mutant'; open(p,'w').write('\n'.join(s))" && git diff > $E/code/c10-M-H1-F4.patch && git checkout -q HEAD -- .); }
rm_() { local c=$1; o=$(cd $S/w/m/$c/wt && EVID=$S/w/m/$c/evid bash $S/b/c10-mutants.sh 2>&1); echo "case=$c rc=$? $(echo "$o" | grep -E 'STOP|OK' | tail -1) tree=$(git -C $S/w/m/$c/wt status --short | wc -l | tr -d ' ') workdir=$([ -e $S/w/m/$c/evid/code/c10-mutants ] && echo made || echo none)"; }
mm reaches-build; rm_ reaches-build
mm patch-stale; printf -- '--- a/src/core/report/envelope.cpp\n+++ b/src/core/report/envelope.cpp\n@@ -1,1 +1,1 @@\n-not the line\n+// walk mutant\n' > $S/w/m/patch-stale/evid/code/c10-M-H1-F4.patch; rm_ patch-stale
mm patch-path; sed -i '' 's#b/src/core/report/envelope.cpp#b/src/core/open/open.cpp#' $S/w/m/patch-path/evid/code/c10-M-H1-F4.patch; rm_ patch-path
mm not-at-c10; git -C $S/w/m/not-at-c10/wt checkout -q HEAD~1; rm_ not-at-c10
mm record-exists; : > $S/w/m/record-exists/evid/receipts/c10-mutants.txt; rm_ record-exists
mm patch-absent; rm $S/w/m/patch-absent/evid/code/c10-M-H1-F4.patch; rm_ patch-absent
mm patch-hunks; P=$S/w/m/patch-hunks/evid/code/c10-M-H1-F4.patch; grep -E '^@@ ' $P > $S/chk/h; cat $S/chk/h >> $P; rm_ patch-hunks
mm dirty; echo x >> $S/w/m/dirty/wt/README.md; rm_ dirty
mm work-exists; mkdir $S/w/m/work-exists/evid/code/c10-mutants; rm_ work-exists
mm work-dangling; ln -s /nonexistent $S/w/m/work-dangling/evid/code/c10-mutants; rm_ work-dangling
