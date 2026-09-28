# rev45 walk records (plan 2b: Task 11's census producer)

- `gen45.py` produces rev45 (`bd2d21f5…`) from the rev44 blob at 2c795a2 (`7d55f0b8…`).
Only the `census_population.sh` block and the `task-11` runner move, as `plan_blocks.py list` shows, and `plan_blocks.py check` passes for tasks 0, 9, 10 and 11.
- `rev44-to-rev45.diff`: the plan file diff.
- `producer-gate-rev45.out`: `orphans=0 classified=56 stale=0` against `producer-gate/baseline-substep2b-rev45.txt`, which is rev41's baseline plus two rows for the new beside-copy (the rev37/rev41 variable-write pattern); rev44 against that baseline reports exactly those two rows stale.

## The finding (pre-token walk of Task 11, after impl-16's Task 10 returned rc 0)

- `w11-rev44-control.sh` / `.out`: rev44's Task 11 body on a full APFS clone of the real `$EVID` (MAIN re-pointed at a scratch dir holding the pinned instrument) STOPs at the census rehearsal: `STOP-landing-census line=38 reason=tree-delta`, `census_rehearsal_rc=1`.
- `rev44-control-tree.delta`: the expected list (sealed producer, `git grep -n -o`, one row per match) carries 85 rows; the instrument (`git grep -n`, one row per line) finds 81; as sets they are identical, and the 4 extra rows are 3 lines holding two matches.
- `census_population.rev45.candidate.sh` / `cp45-vs-instrument.out`: the fix (one row per line, classified by its first match, the instrument's own rule) against the pinned instrument: PASS at H0 `b3039506` and at H `cb19326a` (81 rows, A=3 B=76 C=2).
- `w11b.sh` / `.out`: the whole rev44 Task 11 body with the candidate producer substituted: rc 0, `finalize_check_rc=0`, 2,329 files in the final set (the results directory would hold 2,330 files, 23M).

## rev45 walked (`w45.sh` / `w45.out`, the DERIVED rev45 Task 11 body, RUNNERS = scratch with `plan-path.txt` -> rev45)

- YES: `census_population.rev45.sh` produced from the block (`0c7124d7…`), no stage left in `work/`, the sealed `census_population.sh` unchanged (`1917222c…`); population rc 0; instrument PASS; the declaration names `census_population.rev45.sh` with producer sha256 `0c7124d7…`; `finalize_check_rc=0`; the rev45 producer is in the final set.
- NO: a pre-existing tampered `census_population.rev45.sh` STOPs at the pin line (runner line 42); a symlinked one STOPs at the regular-file line (runner line 41); neither produces a population.
