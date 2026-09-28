import hashlib, subprocess, sys
P = 'docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep2b-20260915.md'
src = subprocess.run(['git', 'show', '2c795a2:' + P], capture_output=True, check=True).stdout.decode('utf-8')
assert hashlib.sha256(src.encode()).hexdigest() == '7d55f0b86a3ccf4078c9da2cbf2c8c8364e441e4b87bf26f68efa8ed28e1f500'
t = src
D45 = '0c7124d75aab4fdb34341bb1027e55f2606c7c5ac28bf3868fbf6536c3a23b19'
def rep(a, b, n=1):
    global t
    c = t.count(a); assert c == n, (c, a[:100]); t = t.replace(a, b)
# ---- the producer BLOCK: one tree row per LINE, classified by its FIRST match (the pinned instrument's rule)
rep('r=0; RAW=$(git grep -n -o -E "$ALT" "$TREE" -- .) || r=$?; [ "$r" -eq 0 ] || STOP tree-producer-rc-"$r"',
    'r=0; RAW=$(git grep -n -E "$ALT" "$TREE" -- .) || r=$?; [ "$r" -eq 0 ] || STOP tree-producer-rc-"$r"')
rep('  rest=${line#"$TREE:"}; pl=${rest%%:*}:; rest2=${rest#*:}; ln=${rest2%%:*}; val=${rest2#*:}; pl=${pl%:}\n',
    '  rest=${line#"$TREE:"}; pl=${rest%%:*}:; rest2=${rest#*:}; ln=${rest2%%:*}; txt=${rest2#*:}; pl=${pl%:}\n'
    '  m=0; val=$(printf \'%s\' "$txt" | grep -o -E "$ALT") || m=$?; [ "$m" -eq 0 ] && [ -n "$val" ] || STOP "tree-row-no-match-at-$pl:$ln"; val=${val%%$\'\\n\'*}   # one row per LINE, classified by its FIRST match: the instrument\'s own rule (its `git grep -n` + `${v%%$\'\\n\'*}`)\n')
# ---- Task 11: produce the fixed producer beside the sealed one, pinned; use it for the population and in the declaration
rep('# Step 2 — the population PRODUCED on H0, then the rehearsal\n',
    '# rev45: the population producer, produced beside Task 0\'s sealed `census_population.sh` (never overwritten: its tree arm emitted one row per MATCH where the pinned instrument reads one row per LINE, so a line holding two matches drew `STOP-landing-census reason=tree-delta`) from THIS plan\'s block only when absent (a fresh mktemp stage in the confined work/, checked regular before and after the extract, digest-checked, then renamed into place), digest-pinned either way — before the population is produced\n'
    'CP45=$EVID/census_population.rev45.sh\n'
    'if [ ! -e "$CP45" ] && [ ! -L "$CP45" ]; then\n'
    'PLANP=$(cat "$RUNNERS/plan-path.txt") || STOP; [ -s "$PLANP" ] || STOP; CPS=$(mktemp "$EVID/work/census_population.rev45.XXXXXX") || STOP; [ -f "$CPS" ] && [ ! -L "$CPS" ] && [ ! -s "$CPS" ] || STOP; x=0; python3 "$RUNNERS/plan_blocks.py" extract "$PLANP" census_population.sh > "$CPS" || x=$?; [ "$x" -eq 0 ] && [ -f "$CPS" ] && [ ! -L "$CPS" ] && [ -s "$CPS" ] || STOP\n'
    f'm=0; cs=$(shasum -a 256 "$CPS" | cut -d\' \' -f1) || m=$?; [ "$m" -eq 0 ] && [ "$cs" = {D45} ] || STOP\n'
    '[ ! -e "$CP45" ] && [ ! -L "$CP45" ] || STOP; v=0; mv "$CPS" "$CP45" || v=$?; [ "$v" -eq 0 ] || STOP\n'
    'fi\n'
    '[ -f "$CP45" ] && [ ! -L "$CP45" ] || STOP\n'
    f'm=0; cs=$(shasum -a 256 "$CP45" | cut -d\' \' -f1) || m=$?; [ "$m" -eq 0 ] && [ "$cs" = {D45} ] || STOP\n'
    '# Step 2 — the population PRODUCED on H0, then the rehearsal\n')
rep('p=0; bash "$EVID/census_population.sh" "$H0" "$EVID/census-raw/H0/population-H0.txt" "$H0"', 'p=0; bash "$CP45" "$H0" "$EVID/census-raw/H0/population-H0.txt" "$H0"')
rep('PD=$(shasum -a 256 "$EVID/census_population.sh" | cut -d\' \' -f1); PIPEOK producer-digest;', 'PD=$(shasum -a 256 "$CP45" | cut -d\' \' -f1); PIPEOK producer-digest;')
rep('\\n  bash census_population.sh <merge> <out>/population-merge.txt <merge>   # producer sha256 %s', '\\n  bash census_population.rev45.sh <merge> <out>/population-merge.txt <merge>   # producer sha256 %s')
# ---- prose
rep('— `census_population.sh "$H0" "$EVID/census-raw/H0/population-H0.txt" "$H0"` (BLOCK;',
    f'— `census_population.sh "$H0" "$EVID/census-raw/H0/population-H0.txt" "$H0"` (rev45: run as `census_population.rev45.sh`, produced from this BLOCK beside Task 0\'s sealed copy only when absent and digest-pinned `{D45[:8]}…` either way; one tree row per LINE classified by its FIRST match, the pinned instrument\'s own rule — the sealed copy emitted one row per MATCH; BLOCK;')
rep('— `census_population.sh <merge> <pop-merge> <merge>` then `<INST> <merge> <pop-merge> <out> <merge>`',
    '— `census_population.rev45.sh <merge> <pop-merge> <merge>` (rev45) then `<INST> <merge> <pop-merge> <out> <merge>`')
rep("Task 11's `census_population.sh` re-run ON THE MERGE HEAD", "Task 11's `census_population.rev45.sh` (rev45) re-run ON THE MERGE HEAD")
rep('11. The census rehearsal at H0: the population PRODUCED on H0 by `census_population.sh` (every',
    f'11. The census rehearsal at H0: the population PRODUCED on H0 by `census_population.rev45.sh` (rev45: from the plan\'s BLOCK, beside the sealed copy, pinned `{D45}`; one tree row per line; every')
rep('- `census_population.sh` — PRODUCES the landing-census population', '- `census_population.sh` (rev45: run as `census_population.rev45.sh`, produced by Task 11 beside Task 0\'s sealed copy) — PRODUCES the landing-census population')
H45 = ("- rev45 (2026-09-27): Task 11 and the `census_population.sh` BLOCK only. The pair Planner's pre-token walk of Task 11 on a full clone of the real evidence home (after impl-16's Task 10 returned rc 0: branch pushed at H, draft PR #28) STOPped at the census rehearsal: `STOP-landing-census line=38 reason=tree-delta` at H0 `b3039506`. "
       "Root cause: the sealed Task 0 producer's tree arm ran `git grep -n -o` (one row per MATCH) while the pinned instrument runs `git grep -n` (one row per LINE) and classifies each line by its first match; the two sets were identical (81 locations) and the expected list carried 4 extra rows for 3 lines holding two matches. "
       f"The BLOCK now emits one row per line classified by its first match; Task 11 produces `census_population.rev45.sh` from it beside the sealed copy (never overwritten) only when absent, digest-pinned `{D45}` either way (the rev41 `finalize.rev41.py` pattern), and uses it for the population and in the landing declaration. "
       "With it the pinned instrument PASSes at H0 and at H, and the whole Task 11 body runs rc 0 on the clone (finalize check rc 0).\n")
rep("- rev44 (2026-09-27): folds the implementer's exact-hash MUST-REVISE of rev43", H45 + "- rev44 (2026-09-27): folds the implementer's exact-hash MUST-REVISE of rev43")
sys.stdout.write(t)
