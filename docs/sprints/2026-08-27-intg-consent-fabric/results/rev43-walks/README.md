# rev43 walk records (plan 2b, MUST-2B-55 and MUST-2B-56)

- `gen43.py` produces rev43 (`096e47b4…`) from the rev42 blob at 78e87b3 (`37ca6530…`).
Only the `task-10` block moves, as `plan_blocks.py list` shows, and `plan_blocks.py check` passes for tasks 0, 9, 10 and 11.
- `walk43.sh` extracts Task 10 lines from the generated rev43 and runs them; `walk43.out` is one recorded run.
- `producer-gate-rev43.out`: `orphans=0 classified=54 stale=0` against the unchanged rev41 baseline.

## MUST-2B-55 (destination binding)

- YES on the real candidate at H `cb19326a`: fetch URL, push URL and visibility bind to `https://github.com/iwnlcern/bivpak.git` / `iwnlcern/bivpak`; `url-rewrite.txt` is empty; `gh repo view "$REPO"` returns PUBLIC.
- YES with `GH_REPO` set to a non-existent repository: the explicit `$REPO` form is unaffected.
The paired control (rev42's unqualified `gh repo view` under the same `GH_REPO`) also returned PUBLIC, so this run does not show that the unqualified form was steerable through `GH_REPO`; rev43 names the repository explicitly regardless.
- NO cases, each in a disposable `--shared` clone at H, each stopping before any remote read and writing zero remote-read or push receipts: split fetch/push URL (STOP at the fetch-url line), `url.<bare>.insteadOf` (fetch-url line, since `get-url` applies the rewrite), `url.<bare>.pushInsteadOf` (url-rewrite line), and an environment-injected `GIT_CONFIG_COUNT` insteadOf (fetch-url line).
- Static: no `ls-remote`, `git push` or `gh repo|pr` line in Task 10 omits `"$URL"` / `"$REPO"` (count 0; the `ls-remote --get-url` probe is the rewrite check itself).

## MUST-2B-56 (prior-attempt pyc retention)

- Every case runs on a full APFS clone (`cp -cRp`) of the real `$EVID`.
An earlier run on a hand-picked subset stopped at the `helpers.sha256` verify line before reaching the compile; that run proved nothing about the compile and is superseded.
- Retention (YES): Step 0 moves `__pycache__/finalize.rev41.cpython-312.pyc` byte-equal into `attempts/task10-1/__pycache__/`; MANIFEST.pre has 9 rows, all 9 verify OK.
`finalize.rev41.py` stays in place with sha and mtime unchanged at `a9eec925…`.
The in-memory `compile()` then passes and the home `__pycache__` goes from 13 to 12 entries, with no `finalize.rev41.*` entry written.
- Negative control: the same Step 0 followed by rev42's `python3 -m py_compile` writes `finalize.rev41.cpython-314.pyc` into the home `__pycache__` (1 entry).
This isolates the compile line as the writer.
- Step 0 NO cases: a symlinked prior pyc STOPs at the pyc loop (t10 line 30); a pre-existing `push-rc.txt` STOPs at the receipt fence (t10 line 27).
Neither creates an `attempts/task10-*` directory or moves any file.
