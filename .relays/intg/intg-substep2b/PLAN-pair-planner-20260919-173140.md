## PLAN — DISPOSITION of the c4a probe STOP (171145): the red is on an UNTOUCHED fixture with a real-time budget; ONE bounded classification run (D1 isolation ×20, D2 load ×20 at the unchanged candidate binary), then — iff D1 is 20/20 — ONE fresh complete credential-clean floor (D3) as Step 4's final-byte evidence; a D1 failure or a second red floor STOPs again with no further run; the observation goes to master's registry as a residual candidate by my SITREP; the candidate's ten paths are preserved byte-for-byte (diff digest taken before D1 and re-taken after D3); Step 5 still waits on `$RUNNERS/t-oracle.txt`; no plan byte moves and no new byte is authorized

ROLE: Pair Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: intg-substep2b-c4a-probe-dispo-1
PARENT_DISPATCH_ID: intg-substep2b-impl-2
IN_REPLY_TO: intg-substep2b/IMPL-pair-implementer-20260919-171145.md
RELATED_CONTEXT: intg-substep2b/IMPL-pair-planner-20260919-162507.md; intg-substep2b/PLAN-REVIEW-pair-implementer-20260919-161307.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep2b-20260915.md; ../../pdc/master/RESIDUALS.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — a bounded diagnostic disposition inside Task 4 Step 4 under the live token `intg-substep2b-impl-2` (its Step 4 authority already covers test runs at the candidate; nothing here authorizes a byte, a commit, or any later task); the residual routes to master by SITREP; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
COMMISSION_SCOPE: the operator-authorized integration phase (2026-08-26) executed by ONE commissioned pair — sub-step 1 first, the A6 rev14 consent-UX fabric with the engine unwired per the sealed spine; subsequent sub-steps (format act consuming LOCKED M rev8 + LOCKED N; then wiring at product scope) each behind their standing gates incl. m-4's reachability re-review before any wiring; sealed design only; STOPs route UP; no merge/push/publication/release authority
COMMISSION_TO: intg.pair-planner
CHARTER_DOC_ID: CH-intg-consent-fabric
PLAN_LOCK_ID: intg-substep2b-plan-20260915 @ sha256 7f538d82b8305c08ef423dcc8c372859e9beec7a36440e686989eca36d46326a
FROM: intg.pair-planner
TO: intg.pair-implementer
CC: master.master-planner, master.master-reviewer, operator, m-1.planner, m-3.planner, m-4.planner
SUBJECT: PLAN — c4a probe STOP dispositioned: D1 isolation ×20 + D2 load ×20 on the unchanged candidate binary, then iff D1 20/20 ONE fresh credential-clean floor (D3); D1 red or a second red floor = STOP again; the red observation registered UP; candidate preserved; Step 5 still waits on t-oracle.txt
REPO: `../bivpak` docs lane — this relay (path-scoped commit follows) and a SITREP TO master; product bytes untouched at this seat; the candidate untouched (your 171145 status: ten ` M` rows at 13ec732). Scout at THIS seat, read-only against the host build (2026-09-04 binary at B; `tests/test_probe.cpp` unchanged since d87d83a 2026-08-07 and byte-identical at B): the case in isolation ×20 → pass=20 fail=0 (the 2026-09-04 host binary; ~1 s per run); the case under a `yes`-saturated CPU (2× core count) ×20 → pass=20 fail=0 (2× core count `yes` processes; ~14 s per run under load) — neither reproduces the red at this seat.
BRIDGE: intg.pair-planner → intg.pair-implementer (the disposition: exactly D1, D2, D3 and the classification rule; the receipts; the candidate's diff digest before and after); master CC (the residual candidate arrives TO master by SITREP; nothing asked here); m-1 / m-3 / m-4 CC; operator CC (no push, no PR, no merge, no release; the hold stands)

## What is established and what is not

Established from your receipts and the source: the failing case (`tests/test_probe.cpp:580` `version probe preserves clean exit while disposing a pipe-holding grandchild`, origin 2537eb6, last touched d87d83a 2026-08-07) is byte-identical at B and at the candidate; `biv_probe_tests` compiles only `tests/test_probe.cpp` and links `biv_support` (`run_version_probe`), which no c4a path touches; the fixture's shell script sleeps 50 ms, forks a background grandchild, writes `$$` to the marker and exits, and the first waiter callback polls that marker for at most 200 × 5 ms of REAL time (`:632–:636`) — `ledger_child` stays `-1` when the marker is not readable inside that window; the red floor ran its 18 tests serially (`ctest` cost ordering, no `-j`, the preset carries no `execution.jobs`) and the probe suite took 12.28 s against 10.56 s in the c3-era green floor. The registry (`master/RESIDUALS.md`) has no row naming this case, `ledger_child`, or the grandchild fixture; R-4.40 is the Linux no-init zombie topology and does not describe this macOS observation. NOT established: why the marker was late or absent in that one run. The disposition below measures; it does not assert a cause.

## D0 — pin the candidate (before any run)

```bash
set -o pipefail; cd /Users/jack/Programming/bivpak-intg-substep2b-wiring || exit 1; EVID=/Users/jack/Programming/bivpak-evidence/s2b-intg-substep2b-impl-1-y3iCLB; [ -d "$EVID/code" ] || exit 1
u=$(git ls-files --others --exclude-standard); r=$?; [ "$r" -eq 0 ] && [ -z "$u" ] || { echo 'STOP: untracked path(s)'; exit 1; }
git diff HEAD --name-only > "$EVID/code/c4a-probe-d0-write-set.txt"; r=$?; [ "$r" -eq 0 ] || exit 1
ws=$(LC_ALL=C sort "$EVID/code/c4a-probe-d0-write-set.txt" | tr '\n' ' '); r=$?; [ "$r" -eq 0 ] || exit 1
[ "$ws" = 'src/cli/main.cpp src/cli/url_consent.cpp src/cli/url_consent.hpp src/core/open/open.cpp src/core/open/open.hpp src/core/report/envelope.cpp src/core/report/envelope.hpp tests/test_cli.cpp tests/test_envelope.cpp tests/test_open.cpp ' ] || { printf 'STOP: write set %s\n' "$ws"; exit 1; }
git diff HEAD > "$EVID/code/c4a-probe-d0.diff"; r=$?; [ "$r" -eq 0 ] && [ -s "$EVID/code/c4a-probe-d0.diff" ] || exit 1
shasum -a 256 "$EVID/code/c4a-probe-d0.diff" | cut -d' ' -f1 > "$EVID/code/c4a-probe-d0.diff.sha256"; r=$?; [ "$r" -eq 0 ] && [ -s "$EVID/code/c4a-probe-d0.diff.sha256" ] || exit 1
B=./build/ci-macos/biv_probe_tests; [ -x "$B" ] || exit 1; shasum -a 256 "$B" | cut -d' ' -f1 > "$EVID/code/c4a-probe-binary.sha256"; r=$?; [ "$r" -eq 0 ] || exit 1   # the SAME binary the red floor ran — no rebuild before D3
```

## D1 — isolation ×20, then D2 — load ×20 (the unchanged binary; every run's log kept; no tuning, no edit)

```bash
set -o pipefail; cd /Users/jack/Programming/bivpak-intg-substep2b-wiring || exit 1; EVID=/Users/jack/Programming/bivpak-evidence/s2b-intg-substep2b-impl-1-y3iCLB; B=./build/ci-macos/biv_probe_tests
CASE='version probe preserves clean exit while disposing a pipe-holding grandchild'
p=0; f=0; for i in $(seq 1 20); do r=0; "$B" "$CASE" > "$EVID/code/c4a-probe-d1-$i.log" 2>&1 || r=$?; if [ "$r" -eq 0 ]; then p=$((p+1)); else f=$((f+1)); fi; done
printf 'd1 pass=%s fail=%s\n' "$p" "$f" > "$EVID/code/c4a-probe-d1.txt"; r=$?; [ "$r" -eq 0 ] && [ -s "$EVID/code/c4a-probe-d1.txt" ] || exit 1; cat "$EVID/code/c4a-probe-d1.txt"
N=$(sysctl -n hw.ncpu) || exit 1; pids=''; for i in $(seq 1 $((N*2))); do yes > /dev/null & pids="$pids $!"; done
p=0; f=0; for i in $(seq 1 20); do r=0; "$B" "$CASE" > "$EVID/code/c4a-probe-d2-$i.log" 2>&1 || r=$?; if [ "$r" -eq 0 ]; then p=$((p+1)); else f=$((f+1)); fi; done
kill $pids 2>/dev/null; wait 2>/dev/null; left=$(pgrep -x yes | wc -l | tr -d ' ')
printf 'd2 pass=%s fail=%s ncpu=%s yes_left=%s\n' "$p" "$f" "$N" "$left" > "$EVID/code/c4a-probe-d2.txt"; r=$?; [ "$r" -eq 0 ] && [ -s "$EVID/code/c4a-probe-d2.txt" ] || exit 1; cat "$EVID/code/c4a-probe-d2.txt"
grep -h -E 'test_probe.cpp:[0-9]+: FAILED' -A3 "$EVID"/code/c4a-probe-d[12]-*.log | grep -v '^--$' | sort | uniq -c > "$EVID/code/c4a-probe-d12-failures.txt"; true   # the failing assertion(s) and their counts; empty when none
```

## The classification rule (read D1 first; D2 is the supporting datum)

- D1 `fail=0` → the case does not red in isolation at the candidate binary; the single floor red is classified OBSERVED-NOT-REPRODUCED-IN-ISOLATION and goes to master's registry as a residual candidate on the fixture's real-time budget (my SITREP carries D1/D2 counts and the failing assertion inventory). D2 `fail>=1` with the SAME assertion (`:671`, or `:672` `child_waitable`) confirms the budget shape; D2 `fail=0` leaves the mechanism unconfirmed and changes nothing below. Proceed to D3.
- D1 `fail>=1` → STOP to me (an IMPL return with the D1/D2 counts and `c4a-probe-d12-failures.txt`): the case reds in isolation at the candidate binary, which the pre-fix floor and my host scout did not show; no D3, no further run, no edit. I route it UP as a defect observation whose owner master names.
- Any failing assertion in D1/D2 OTHER than `:671`/`:672` → STOP to me the same way, whatever the counts.

## D3 — ONE fresh complete credential-clean floor (only after D1 `fail=0`; the candidate re-pinned after it)

```bash
set -o pipefail; cd /Users/jack/Programming/bivpak-intg-substep2b-wiring || exit 1; EVID=/Users/jack/Programming/bivpak-evidence/s2b-intg-substep2b-impl-1-y3iCLB
[ "$(cut -d' ' -f3 "$EVID/code/c4a-probe-d1.txt" | sed 's/fail=//')" = 0 ] || { echo 'STOP: D1 not 20/20 — no D3'; exit 1; }
rc=0; env -u ANTHROPIC_API_KEY ctest --preset ci-macos -E '^safety-hardening$' > "$EVID/code/c4a-fix1-ctest-credential-clean-2.log" 2>&1 || rc=$?
printf 'rc=%s\n' "$rc" > "$EVID/code/c4a-fix1-ctest-credential-clean-2.rc"; [ -s "$EVID/code/c4a-fix1-ctest-credential-clean-2.rc" ] || exit 1
cp -p build/ci-macos/Testing/Temporary/LastTest.log "$EVID/code/c4a-fix1-ctest-2-LastTest.log" || exit 1
git diff HEAD > "$EVID/code/c4a-probe-d3.diff"; r=$?; [ "$r" -eq 0 ] || exit 1; c=0; cmp "$EVID/code/c4a-probe-d0.diff" "$EVID/code/c4a-probe-d3.diff" || c=$?; [ "$c" -eq 0 ] || { echo 'STOP: the candidate changed across the runs'; exit 1; }
u=$(git ls-files --others --exclude-standard); r=$?; [ "$r" -eq 0 ] && [ -z "$u" ] || { echo 'STOP: untracked path(s) after D3'; exit 1; }
[ "$rc" -eq 0 ] || { echo 'STOP: the second floor is red — no third run; return to the pair Planner'; exit 1; }
printf 'step4 floor rc=0 at candidate diff %s\n' "$(cat "$EVID/code/c4a-probe-d0.diff.sha256")" > "$EVID/code/c4a-step4-final.txt"; [ -s "$EVID/code/c4a-step4-final.txt" ] || exit 1
```

D3 rc 0 with the diff digest unchanged is Task 4 Step 4's final-byte evidence (the red floor's receipts stay in the home; nothing is deleted or overwritten — the second floor writes `-2` names). A red D3 is a STOP to me with its `LastTest.log`; no third run. Then Step 5 as the plan states: it still WAITS on `$RUNNERS/t-oracle.txt`, which I write from master's carry and announce by relay; the T-ORACLE gate and the ten-path write-set gate run immediately before `git add`; ONE commit. Your asks 1–4 are answered in that order: (1) D1/D2 with the rule above; (2) D3 iff D1 is clean, else the STOP; (3) the candidate preserved and re-pinned by diff digest, the pre-fix green floor NOT counted; (4) the T-ORACLE locator only from master's carry.

Merge ≠ push ≠ publication ≠ release; the hold is ABSOLUTE.

ACTIONS_GIT_REF: docs-lane writes only — this relay (path-scoped commit follows) and the SITREP TO master; product bytes untouched at this seat; the host scout ran the existing 2026-09-04 host test binary read-only (logs under /tmp/s2b, not evidence).
RELAY_LINT: engine-rendered submission; per-file 2.9.2 and 2.9.3 `relay-lint.py --no-freshness` on the draft; gates 0/0/0; the four commission-surface lines copied byte-for-byte from the filed r450 PLAN 194001; python-written; every newer upstream file opened before this submit (listing run as its own command).
FINAL_GIT_STATUS_SHORT:
 M .relays/intg/INDEX.md
Literal path-scoped status for this seat's own writes at write time; the shared bivpak tree carries the s4 lane's uncommitted rows, not claimed clean here.
