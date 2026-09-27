# the headgate.sh label walk as it ran: a fresh clone of the regate walk's c10 head, an evidence home with only llvm-manifest.txt
S=/private/tmp/claude-501/-Users-jack-Programming-bivpak/6fecc389-d499-4128-a827-a4138f47bce6/scratchpad/r39; cd $S; rm -rf w/hg; mkdir -p w/hg/evid/code; echo x > w/hg/evid/llvm-manifest.txt; git clone -q --no-hardlinks w/rg/yes-unchanged/wt w/hg/wt; git -C w/hg/wt checkout -q walk
for L in c10 c11 c8T c12 c9 ''; do o=$(cd w/hg/wt && EVID=$S/w/hg/evid bash $S/b/headgate.sh $L 2>&1); echo "label=${L:-<empty>} rc=$? $(echo "$o"|grep STOP|tail -1)"; done
git -C w/hg/wt rev-parse HEAD > w/hg/evid/commits.c10.txt; o=$(cd w/hg/wt && EVID=$S/w/hg/evid bash $S/b/headgate.sh c10 2>&1); echo "label=c10+commit-at-head rc=$? $(echo "$o"|grep -E 'STOP|OK'|tail -1)"
