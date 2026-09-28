STOP(){ echo "STOP $1"; exit 1; }
REC=docs/sprints/2026-08-27-intg-consent-fabric/results/s2b-intg-substep2b-impl-1; n=$(git ls-files -- "$REC" | wc -l | tr -d ' '); [ "$n" -eq 0 ] || STOP record-tracked-"$n"
echo PASS tracked=$n
