#!/bin/bash
cd "$(dirname "$0")"; : > results.txt
for c in yes pt-file pt-dir pt-symlink pt-dangling attempts-symlink attempts-file attempts-absent h-symlink h0-two-lines h0-bad-hex h0-symlink helpers-absent series-present h9-present b-symlink work-absent t0-missing t0-symlink t0-dir bleg-symlink bleg-dir fresh-with-bleg fresh-clean fresh-clean-empty-H no-bleg-with-h0 retry-after-success root-dangling work-stage-symlink work-stage-dangling work-stage-regular work-bleg-dangling htxt-present c9-present; do ./walk.sh $c >> results.txt; done
for n in 1 2 3 4 20 39 40; do MV_FAIL_AT=$n ./walk.sh mvfail-$n | sed "s/^/MV_FAIL_AT=$n /" >> results.txt; done
MV_FAIL_AT=39,40 ./walk.sh mvfail-39-rb | sed 's/^/MV_FAIL_AT=39,40 /' >> results.txt
MV_FAIL_AT=10,14 ./walk.sh mvfail-10-rbB | sed 's/^/MV_FAIL_AT=10,14 /' >> results.txt
for n in 1 3 10 39; do MV_CORRUPT_AT=$n ./walk.sh mvcorrupt-$n | sed "s/^/MV_CORRUPT_AT=$n /" >> results.txt; done
for n in 1 2 3 4 5; do PY_FAIL_AT=$n ./walk.sh pyfail-$n | sed "s/^/PY_FAIL_AT=$n /" >> results.txt; done
for m in nobmove nobleg-at-all nobleg-nopost; do SNIP=$PWD/mut-$m.sh ./walk.sh yes | sed "s/^/MUT-$m /" >> results.txt; done
SNIP=$PWD/mut-nolinkguard.sh ./walk.sh work-bleg-dangling | sed 's/^/MUT-nolinkguard /' >> results.txt
echo ALL-DONE >> results.txt
