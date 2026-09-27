import sys, re
src, dst = sys.argv[1:3]
S = '/private/tmp/claude-501/-Users-jack-Programming-bivpak/6fecc389-d499-4128-a827-a4138f47bce6/scratchpad/r39/'
t = open(src, encoding='utf-8').read()
def rep(a, b, n=1, within=None):
    global t
    if within is None:
        assert t.count(a) == n, (t.count(a), a[:100]); t = t.replace(a, b)
    else:
        i = t.index(within[0]); j = t.index(within[1], i + len(within[0]))
        seg = t[i:j]; assert seg.count(a) == n, (seg.count(a), a[:100]); t = t[:i] + seg.replace(a, b) + t[j:]
# 1. the two new sections
T8C = open(S + 'task8c.md', encoding='utf-8').read(); T9B = open(S + 'task9b.md', encoding='utf-8').read()
rep('### Task 9 — the gates at H0', T8C + '### Task 9 — the gates at H0')
rep('### Task 10 — the vehicle', T9B + '### Task 10 — the vehicle')
# 2. the head gate: a named BLOCK, the c10 / c11 labels
HG0 = "```bash\n# Task 8b — the per-head gate at ONE new head (rev33; master 215035 R3 as corrected by 224030, final form 003436): usage  bash <this block> <LABEL>  with LABEL in c8L c8Tr c8T, run at that commit's head before the next commit\n"
rep(HG0, "<!-- BLOCK: headgate.sh -->\n```bash\n# Task 8b — the per-head gate at ONE new head (rev33; master 215035 R3 as corrected by 224030, final form 003436): usage  bash <this block> <LABEL>  with LABEL in c8L c8Tr c8T (rev39: also c10, Task 8c, and c11, Task 9b), run at that commit's head before the next commit\n")
rep("  c8T) TL=none; TS=none; NT=0;;\n  *) STOP label;;", "  c8T) TL=none; TS=none; NT=0;;\n  c10|c11) TL=none; TS=none; NT=0;;\n  *) STOP label;;")
# 3. the commit topology
C9L = "c9  ci: count cells (IFF a case tuple moved at H0 on either platform) — committed INSIDE the       Task 9   .github/workflows/s2-harness.yml only\n         Task 9 runner by cellpatch.py after both platform observations\n"
rep(C9L, C9L +
"c10 open: MUST-H-1 — a failed row's kind and detail rendered, never null (m-3 160359 F1–F5;       Task 8c  src/core/open/open.cpp, src/core/report/envelope.{hpp,cpp}, src/cli/url_consent.{hpp,cpp},\n"
"         master 164725's F4 widening): the divergence row carries UrlDivergenceEntryRefused and A6           schemas/biv-json-envelope.v1.schema.json, harness/selftest/test_envelope.py (the pin),\n"
"         :537's sentence; the schema admits both iff failed; a failed row lacking either is a typed          tests/test_cli.cpp, tests/test_envelope.cpp, CMakeLists.txt\n"
"         InternalError; rev39, after Task 9 completed at c9\n"
"c11 ci: count cells re-pinned (IFF a case tuple at the c10 head differs from c9's cells) —            Task 9b  .github/workflows/s2-harness.yml only\n"
"         committed INSIDE the re-gate block by cellpatch.py\n")
rep("c8 after c7; rev33: c8L, c8Tr, c8T after c8 in that order (Task 8b; each head passes the per-head gate); c9 last.",
    "c8 after c7; rev33: c8L, c8Tr, c8T after c8 in that order (Task 8b; each head passes the per-head gate); c9 last of Task 9; rev39: c10 after c9 (Task 8c; its head passes the per-head gate), then c11 iff moved (Task 9b), last.")
rep("moved); the runner proves `git diff H0 H -- . ':!.github/workflows/s2-harness.yml'` EMPTY so every H0 receipt carries to H, and writes H.txt LAST.\n",
    "moved); the runner proves `git diff H0 H -- . ':!.github/workflows/s2-harness.yml'` EMPTY so every H0 receipt carries to H, and writes H.txt LAST.\n"
    "rev39: Task 9's H0 (`99136ca`, c8T) and H (`2893bc53`, c9) stand as EXECUTED under impl-12. The re-gate object is the c10 head (`R/H0.txt`), and the FINAL H is the head after c11 (== c10 iff no cell moved since c9), written LAST as `R/H.txt`; Task 9b proves `git diff c10 H -- . ':!.github/workflows/s2-harness.yml'` EMPTY. From rev39 the three owner byte reviews, the GO relay and the vehicle bind THAT H. c10 touches no src/core/repo path; c11 touches the workflow alone.\n")
# 4. resume.sh: carry Task 9's receipts once Task 9 is done
rep("# resume.sh — protocol step 0': bind a NEW runners directory to a LATER token (new PLAN_LOCK digest, new DISPATCH_ID, the SAME evidence home) while carrying Task 0's receipts and every gate file;",
    "# resume.sh — protocol step 0': bind a NEW runners directory to a LATER token (new PLAN_LOCK digest, new DISPATCH_ID, the SAME evidence home) while carrying Task 0's receipts, Task 9's once Task 9 is done (rev39), and every gate file;")
R0 = 'for f in proof-0.txt task-0.sha256 task-0.invocation.txt task-0.exit task-0.proof-tail task-0.self.sha256 plan-hash-0.txt plan_blocks.sha256-0; do [ -s "$OLD/$f" ] || STOP "receipt-absent-$f"; done\n'
rep(R0, R0 +
'# rev39: once Task 9 is done in the previous directory its receipts are carried (Task 10\'s controller requires task-9.done in the directory it runs from); each bound to the controller\'s copies in $EVID/runners/ and to the prologue records of the token that ran it\n'
'T9=0; if [ -e "$OLD/task-9.done" ] || [ -L "$OLD/task-9.done" ]; then T9=1; [ -f "$OLD/task-9.done" ] && [ ! -L "$OLD/task-9.done" ] && [ "$(cat "$OLD/task-9.done")" = rc=0 ] || STOP task-9-not-done\n'
'  for f in task-9.done task-9.exit proof-9.tail plan_blocks.sha256-9; do c=0; cmp "$OLD/$f" "$EVID/runners/$f" >&2 || c=$?; [ "$c" -eq 0 ] || STOP "task-9-copy-mismatch-$f"; done\n'
'  h=0; s=$(shasum -a 256 "$OLD/task-9.sh" | cut -d\' \' -f1) || h=$?; r=$(cut -d\' \' -f1 "$OLD/task-9.sha256") || STOP task-9-sha-read; [ "$h" -eq 0 ] && [ -n "$r" ] && [ "$s" = "$r" ] || STOP task-9-sh-altered\n'
'  OT=$(cat "$OLD/token-id.txt") || STOP old-token; printf \'%s\' "$OT" | grep -q -E \'^intg-substep2b-impl-[0-9]+$\' || STOP old-token-form\n'
'  for f in task-9.sh proof-9.txt task-9.sha256 task-9.invocation.txt; do c=0; cmp "$OLD/$f" "$EVID/runners/$OT/task-9/$f" >&2 || c=$?; [ "$c" -eq 0 ] || STOP "task-9-record-mismatch-$f"; done\n'
'  for f in task-9.proof-tail task-9.self.sha256 plan-hash-9.txt; do [ -s "$OLD/$f" ] || STOP "receipt-absent-$f"; done\n'
'fi\n')
C0 = 'for f in task-0.sh proof-0.txt task-0.sha256 task-0.invocation.txt task-0.exit task-0.done task-0.proof-tail task-0.self.sha256 plan-hash-0.txt plan_blocks.sha256-0; do c=0; cp -p "$OLD/$f" "$NEW/$f" || c=$?; [ "$c" -eq 0 ] && [ -s "$NEW/$f" ] || STOP "carry-$f"; c=0; cmp "$OLD/$f" "$NEW/$f" || c=$?; [ "$c" -eq 0 ] || STOP "carry-cmp-$f"; CARRIED="$CARRIED $f"; done\n'
rep(C0, C0 + 'if [ "$T9" -eq 1 ]; then for f in task-9.sh proof-9.txt task-9.sha256 task-9.invocation.txt task-9.exit task-9.done task-9.proof-tail task-9.self.sha256 plan-hash-9.txt plan_blocks.sha256-9 proof-9.tail; do c=0; cp -p "$OLD/$f" "$NEW/$f" || c=$?; [ "$c" -eq 0 ] && [ -s "$NEW/$f" ] || STOP "carry-$f"; c=0; cmp "$OLD/$f" "$NEW/$f" || c=$?; [ "$c" -eq 0 ] || STOP "carry-cmp-$f"; CARRIED="$CARRIED $f"; done; fi\n')
# 5. Task 10's runner binds Task 9b's receipts
W10 = ('<!-- RUN: task-10 -->', '### Task 11 —')
rep('H=$(sed \'s/^H=//\' "$EVID/H.txt") || STOP; [ -n "$H" ] || STOP\n', 'H=$(sed \'s/^H=//\' "$EVID/R/H.txt") || STOP; [ -n "$H" ] || STOP   # rev39: the FINAL H is Task 9b\'s\n', within=W10)
rep('[ "$(cat "$EVID/H/count-gate-final-macos.rc")" = count_gate_final_macos_rc=0 ] && [ "$(cat "$EVID/H/count-gate-final-linux.rc")" = count_gate_final_linux_rc=0 ] || STOP\n',
    '[ "$(cat "$EVID/R/count-gate-final-macos.rc")" = count_gate_final_macos_rc=0 ] && [ "$(cat "$EVID/R/count-gate-final-linux.rc")" = count_gate_final_linux_rc=0 ] || STOP\n', within=W10)
rep('[ "$(cat "$EVID/H/linux-container.rc")" = 0 ] && [ "$(cat "$EVID/B/linux-container.rc")" = 0 ] && [ "$(cat "$EVID/H/E3-linux.rc")" = e3_linux_rc=0 ] && [ "$(cat "$EVID/H/harness-e2-macos.rc")" = harness_e2_macos_rc=0 ] && [ "$(cat "$EVID/H/harness-e2-linux.rc")" = harness_e2_linux_rc=0 ] || STOP\n',
    '[ "$(cat "$EVID/heads/c10/linux-container.rc")" = 0 ] && [ "$(cat "$EVID/B/linux-container.rc")" = 0 ] && [ "$(cat "$EVID/R/E3-linux.rc")" = e3_linux_rc=0 ] && [ "$(cat "$EVID/R/harness-e2-macos.rc")" = harness_e2_macos_rc=0 ] && [ "$(cat "$EVID/R/harness-e2-linux.rc")" = harness_e2_linux_rc=0 ] || STOP\n', within=W10)
i = t.index('<!-- RUN: task-10 -->'); j = t.index('### Task 11 —', i); seg = t[i:j]
pl = [l for l in seg.split('\n') if l.startswith('if [ "$(cat "$EVID/H/selftest-population.rc")" = population_equal_rc=0 ]; then')]
assert len(pl) == 1
rep(pl[0] + '\n', '[ "$(cat "$EVID/R/selftest-population.rc")" = population_equal_rc=0 ] || STOP; g=0; k=$(grep -c -E \' bar=(pass-green|pass-r435-disclosed-registered-red)$\' "$EVID/R/linux-selftest-bar.txt") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP   # rev39: the lighter re-gate admits only an EQUAL population\n', within=W10)
# 6. Task 11's runner: H0 and H from R/
W11 = ('<!-- RUN: task-11 -->', '### Task 12 —')
rep('H0=$(sed \'s/^H0=//\' "$EVID/H0.txt") || STOP; [ -n "$H0" ] || STOP; H=$(sed \'s/^H=//\' "$EVID/H.txt") || STOP; [ -n "$H" ] || STOP',
    'H0=$(sed \'s/^H0=//\' "$EVID/R/H0.txt") || STOP; [ -n "$H0" ] || STOP; H=$(sed \'s/^H=//\' "$EVID/R/H.txt") || STOP; [ -n "$H" ] || STOP', within=W11)
# 7. finalize.py prbody: c10/c11 in the commit list; the re-gate's receipts beside Task 9's
rep('commits = "\\n".join("- c%s = %s" % (k, rd("commits.c%s.txt" % k)) for k in range(1, 10) if os.path.isfile(os.path.join(evid, "commits.c%s.txt" % k)))',
    'commits = "\\n".join("- c%s = %s" % (k, rd("commits.c%s.txt" % k)) for k in range(1, 12) if os.path.isfile(os.path.join(evid, "commits.c%s.txt" % k)))')
rep('                "Leg receipts (%d): %s" % (len(legs), ", ".join(legs)), "Registered (S-6): %s" % rd("legs/registered.txt"),\n',
    '                "Re-gate at c10 (Task 9b, rev39): object %s; count gate %s; final macOS %s / linux %s; E3 linux %s; harness-e2 macOS %s / linux %s; population %s; bar %s" % (rd("R/H0.txt"), rd("R/count-gate.txt"), rd("R/count-gate-final-macos.rc"), rd("R/count-gate-final-linux.rc"), rd("R/E3-linux.rc"), rd("R/harness-e2-macos.rc"), rd("R/harness-e2-linux.rc"), rd("R/selftest-population.rc"), rd("R/linux-selftest-bar.txt")),\n'
    '                "Leg receipts (%d): %s" % (len(legs), ", ".join(legs)), "Registered (S-6): %s" % rd("legs/registered.txt"),\n')
# 8. prose: Step 0′, Task 9 (executed), Task 10 and Task 11 notes
rep('**Step 0′ — resumption under a LATER token (rev17; rev18 folds MUST-2B-36/37; rev19 folds MUST-2B-38/39/40; the gap disclosed on the token 162507 and in 162750, the fold accepted by master 175324).**',
    '**Step 0′ — resumption under a LATER token (rev17; rev18 folds MUST-2B-36/37; rev19 folds MUST-2B-38/39/40; the gap disclosed on the token 162507 and in 162750, the fold accepted by master 175324; rev39: Task 9\'s receipts carried once Task 9 is done).** rev39: when the previous directory holds `task-9.done`, it must read `rc=0`; `task-9.done`, `task-9.exit`, `proof-9.tail` and `plan_blocks.sha256-9` must equal the controller\'s copies in `$EVID/runners/`; `task-9.sh` must re-hash to `task-9.sha256`; the runner, its proof, digest and invocation must equal the prologue records of the token that ran it (`$EVID/runners/<that token>/task-9/`); and all eleven Task 9 receipts are carried, so Task 10\'s controller finds `task-9.done` and Task 9 can never re-run under a later token.')
rep('### Task 9 — the gates at H0, both platforms;', '### Task 9 — (EXECUTED under impl-12 at H `2893bc53`; rev39 re-gates the c10 head in Task 9b) the gates at H0, both platforms;')
rep('### Task 10 — the vehicle (ONLY after the pair Planner\'s GO relay carrying EXACTLY ONE no-red byte review of H from EACH of m-1, m-3 and m-4 through master): ONE push to ONE pinned destination, ONE draft PR\n',
    '### Task 10 — the vehicle (ONLY after the pair Planner\'s GO relay carrying EXACTLY ONE no-red byte review of H from EACH of m-1, m-3 and m-4 through master): ONE push to ONE pinned destination, ONE draft PR\n\nrev39: H is Task 9b\'s FINAL H (`R/H.txt`); the final count gates, E3 Linux, both `harness-e2` rows and the population rule are read from `R/` (the population EQUAL, the bar passed), and the container receipts from `heads/c10/` and `B/`.\n')
# 9. the acceptance criteria
A14 = [l for l in t.split('\n') if l.startswith('14. (rev33) Task 8b: each of c8L, c8Tr, c8T applied VERBATIM')]
assert len(A14) == 1
rep(A14[0] + '\n', A14[0] + '\n\n15. (rev39, MUST-H-1) Task 8c: c10 at its Files line only, on top of c9; `receipts/c10-red.txt` shows the three named cases and `divergence_envelope_conforms` RED at c9\'s product bytes; the same four green at c10; `receipts/c10-mutants.txt` shows M-H1-PRE, M-H1-SCHEMA and M-H1-F4 each RED; `heads/c10/headgate.txt` (tidy EMPTY, coverage 37/37, macOS failures 0, container rc 0, only harness-selftest red, `divergence_envelope_conforms` run and passed).\n\n16. (rev39) Task 9b: `R/` complete — c10\'s path set inside its Files line and the E2 / closure / network censuses unmoved from c9; the A8 facts census, the no-spawn and zero-byte fences; the count gate against c9\'s cells as data; both skip sets unchanged; E3 Linux and `harness-e2` on both platforms rc 0; the selftest population EQUAL to Task 9\'s and the bar passed; c11 iff moved, its head gated; both final count gates rc 0; `git diff c10 H` outside the workflow EMPTY; `R/H.txt` written LAST.\n')
# 10. the revision history (newest first)
rep('\n- rev38 (2026-09-25): folds MUST-2B-52', '\n- rev39 (2026-09-26): folds m-3\'s MUST-H-1 (owner byte review of H `2893bc53`, `../pdc/master/relays/intg-2b-wiring-act/DESIGN-planner-20260926-160359.md`, F1–F5) as carried and widened by master (`PLAN-master-planner-20260926-164725.md`, F4 the load-bearing arm across both doors), under the operator\'s "lighter regate pls" (2026-09-26). NEW Task 8c: c10, the failed row\'s `kind` and `detail` rendered and never null, the schema admitting both iff failed, a failed row lacking either a typed `InternalError`; tests first; three gating mutants (block `c10-mutants.sh`); the per-head gate, now the named block `headgate.sh`, with the `c10` / `c11` labels. NEW Task 9b: the re-gate at the c10 head (block `regate.sh`) — the censuses c10 could move, the count gate against c9\'s cells, both skip sets, E3 and `harness-e2`, the selftest population EQUAL to Task 9\'s (a moved population is a STOP routed up), the companion c11 iff moved, the FINAL H into `R/H.txt` LAST; R-4.83\'s whole-census form and R-4.82\'s plain-`mkdir` form carried for this block. Task 9 stands as EXECUTED (impl-12); nothing in its outputs moves. `resume.sh` carries Task 9\'s eleven receipts once Task 9 is done (Task 10\'s controller requires `task-9.done`; the gap would have stopped Task 10 under any later token). Task 10, Task 11 and `finalize.py` read the FINAL H and the re-gate receipts from `R/`. The topology gains c10 and c11; acceptance gains 15 and 16.\n- rev38 (2026-09-25): folds MUST-2B-52')
open(dst, 'w', encoding='utf-8').write(t)
print('ok', t.count('\n'))
