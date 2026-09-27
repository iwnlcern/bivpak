import sys, hashlib, subprocess, re
P = 'docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep2b-20260915.md'
blob = subprocess.run(['git','show','12ee0f9e:'+P],capture_output=True,check=True).stdout
assert hashlib.sha256(blob).hexdigest().startswith('d5a868d3')
t = blob.decode('utf-8')
def rep(a, b, n=1):
    global t
    assert t.count(a) == n, (t.count(a), a[:100]); t = t.replace(a, b)
S = sys.argv[1]
# (1) the block
i = t.index('<!-- BLOCK: c10-mutants.sh -->\n```bash\n') + len('<!-- BLOCK: c10-mutants.sh -->\n```bash\n'); j = t.index('\n```\n', i)
old_block = t[i:j+1]; assert old_block.startswith('# Task 8c — the c10 mutant record (rev39;')
t = t[:i] + open(S + '/c10-mutants.sh').read() + t[j+1:]
# (2) the heading and the mutant prose
rep('### Task 8c — c10, MUST-H-1: a failed repository row renders its `kind` and `detail`, never null, and the envelope validates against the product\'s own schema (rev39;',
    '### Task 8c — c10, MUST-H-1: a failed repository row renders its `kind` and `detail`, never null, and the envelope validates against the product\'s own schema (rev40: Steps 0–4 EXECUTED under impl-13, c10 `2291a46`; Step 5 runs rev40\'s mutant record; rev39;')
rep('**THE MUTANT RECORD at the c10 head** (block `c10-mutants.sh`; each mutant applied to the working tree only, built, run, recorded in `$EVID/receipts/c10-mutants.txt` and reverted, the tree proved clean after each; a mutant that does not compile is a STOP). All three GATE:',
    '**THE MUTANT RECORD at the c10 head** (block `c10-mutants.sh`; each mutant applied to the working tree only, built, run, recorded in `$EVID/receipts/c10-mutants.rev40.txt` and reverted, the tree proved clean after each; a mutant that does not compile is a STOP; the record ends in ONE `verdict=ok` line written last, and Task 9b reads that line, never the file\'s mere presence). rev40 (impl-13\'s STOP `intg-substep2b/IMPL-pair-implementer-20260926-211822.md`): `divergence_envelope_conforms` REQUIRES the fixture `biv_tests` sets up, so when a mutant reddens `biv_tests` CTest reports the consumer `Not Run`, never `Failed`. rev39 demanded a conforms failure under M-H1-PRE that this topology makes impossible. Each mutant is therefore killed by the NAMED witness it reddens: the per-mutant record carries both CTest rows\' statuses and the failed Catch2 cases by name. impl-13\'s rev39 record (`receipts/c10-mutants.txt`, sha256 `4fe1c976…`) and work directory `code/c10-mutants/` stay where they are as the attempt\'s record. All three GATE:')
rep('- M-H1-PRE: `src/core/open/open.cpp` reverted to c9\'s bytes (the divergence row back to unset fields, the predicate never evaluated). (w1) goes red in `biv_tests`, and `divergence_envelope_conforms` goes red on the regenerated file.',
    '- M-H1-PRE: `src/core/open/open.cpp` reverted to c9\'s bytes (the divergence row back to unset fields, the predicate never evaluated). (w1) goes red in `biv_tests` — exactly ONE failed case, `open repos typed refusal continues in encounter order to a clean entry` — and `divergence_envelope_conforms` is `Not Run` by the fixture (recorded, never counted as a kill; under M-H1-PRE the case aborts on the null `kind` before it writes the envelope, so no conformance run could observe it).')
rep('- M-H1-SCHEMA: `schemas/biv-json-envelope.v1.schema.json` reverted to c9\'s bytes. `divergence_envelope_conforms` goes red, because the fixed row now carries two properties c9\'s schema forbids.',
    '- M-H1-SCHEMA: `schemas/biv-json-envelope.v1.schema.json` reverted to c9\'s bytes. Every case stays green (`biv_tests` `Passed`, zero failed cases), and `divergence_envelope_conforms` alone goes red (`Failed`), because the fixed row now carries two properties c9\'s schema forbids — the whole-envelope validation\'s independent kill.')
rep('- M-H1-F4: the predicate made constant `true`, as a one-hunk patch the implementer prepares at `$EVID/code/c10-M-H1-F4.patch` touching `src/core/report/envelope.cpp` only (the block refuses any other path). (w3) goes red.',
    '- M-H1-F4: the predicate made constant `true`, as a one-hunk patch the implementer prepares at `$EVID/code/c10-M-H1-F4.patch` touching `src/core/report/envelope.cpp` only (the block refuses any other path). (w3) goes red in `biv_tests` — exactly its TWO cases, `failed row completeness rejects a missing kind` and `failed row completeness rejects a missing detail and complete rows emit no null carriers` — with `divergence_envelope_conforms` `Not Run` by the fixture.')
rep('- [ ] **Step 5: the mutant record** — prepare `$EVID/code/c10-M-H1-F4.patch`, then `bash` the block `c10-mutants.sh` (extracted from this plan by `plan_blocks.py extract`) from the worktree.',
    '- [ ] **Step 5: the mutant record** — prepare `$EVID/code/c10-M-H1-F4.patch`, then `bash` the block `c10-mutants.sh` (extracted from this plan by `plan_blocks.py extract`) from the worktree. rev40 (resumption): Steps 0–4 are EXECUTED under impl-13 — c10 `2291a46e7ff70c4c06055c8d0aab9e6709cb134d` at its ten Files-line paths, `receipts/c10-red.txt` (`801bc78e…`) and the patch `code/c10-M-H1-F4.patch` (one file, one hunk) all in place; under the successor token Task 8c RESUMES HERE, with HEAD at c10 and the tree clean, and nothing of Steps 0–4 is re-run or re-written.')
# (3) the consumer: regate.sh reads the verdict, never the file's presence
rep('[ -s "$G/headgate.txt" ] && [ -s "$EVID/receipts/c10-mutants.txt" ] && [ -s "$EVID/receipts/c10-red.txt" ] || STOP task8c-receipts\n',
    '[ -s "$G/headgate.txt" ] && [ -s "$EVID/receipts/c10-red.txt" ] || STOP task8c-receipts\ng=0; k=$(grep -c -x -F \'verdict=ok\' "$EVID/receipts/c10-mutants.rev40.txt") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP task8c-mutants-verdict\n')
# (4) acceptance 15
rep('`receipts/c10-mutants.txt` shows M-H1-PRE, M-H1-SCHEMA and M-H1-F4 each RED;',
    '`receipts/c10-mutants.rev40.txt` ends in ONE `verdict=ok` line: M-H1-PRE killed by (w1)\'s one case with the conforms row `Not Run` by the fixture, M-H1-SCHEMA killed by the conforms row alone with every case green, M-H1-F4 killed by (w3)\'s two cases (rev40); impl-13\'s rev39 record preserved unchanged;')
# (4b) resume.sh: Task 9's records are bound by CONTENT to the one token that ran Task 9, not to the previous directory's token (a second successor resumes from a directory whose token did not run Task 9)
rep("""  OT=$(cat "$OLD/token-id.txt") || STOP old-token; printf '%s' "$OT" | grep -q -E '^intg-substep2b-impl-[0-9]+$' || STOP old-token-form
  for f in task-9.sh proof-9.txt task-9.sha256 task-9.invocation.txt; do c=0; cmp "$OLD/$f" "$EVID/runners/$OT/task-9/$f" >&2 || c=$?; [ "$c" -eq 0 ] || STOP "task-9-record-mismatch-$f"; done
""", """  # rev40: the records of the ONE token whose Task 9 run these are, found by content (impl-12 ran Task 9; impl-13's directory carried it; impl-14 resumes from impl-13's)
  n=0; for td in "$EVID"/runners/intg-substep2b-impl-*/task-9; do [ -d "$td" ] && [ ! -L "$td" ] || continue; m=1; for f in task-9.sh proof-9.txt task-9.sha256 task-9.invocation.txt; do cmp -s "$OLD/$f" "$td/$f" || m=0; done; [ "$m" -eq 0 ] || n=$((n + 1)); done
  [ "$n" -eq 1 ] || STOP "task-9-record-owner-$n"
""")
# (5) history
h = t.index('- rev39 (2026-09-26): folds m-3')
hist = ("- rev40 (2026-09-26): folds impl-13's STOP (`intg-substep2b/IMPL-pair-implementer-20260926-211822.md`, `STOP-c10-mutants survived-M-H1-PRE`). c10 `2291a46` LANDED green at its ten paths, and every mutant was killed by a named witness (M-H1-PRE by (w1), M-H1-SCHEMA by the conforms row, M-H1-F4 by (w3)). "
        "But rev39's block demanded a `divergence_envelope_conforms` FAILURE under M-H1-PRE, and CTest reports that consumer `Not Run` whenever the `biv_tests` fixture it requires fails — an assertion rev39's own topology made impossible, in the one arm rev39 disclosed as unwalked. "
        "`c10-mutants.sh` rev40: each mutant is killed by the witness it NAMES — the per-mutant record carries both CTest rows' statuses and the failed Catch2 cases by name (exactly (w1)'s one case under M-H1-PRE; zero cases with the conforms row alone `Failed` under M-H1-SCHEMA; exactly (w3)'s two under M-H1-F4). The record is `receipts/c10-mutants.rev40.txt`, ending in ONE `verdict=ok` line written last; impl-13's rev39 record and work directory stay in place, the record pinned by digest. "
        "The same STOP exposed a second defect: `regate.sh` gated Task 8c on `[ -s receipts/c10-mutants.txt ]`, which impl-13's FAILED record satisfies. Task 9b now reads the rev40 record's `verdict=ok`. "
        "A third defect, found by walking Step 0′ for the NEXT token from a mirror of impl-13's runners directory: rev39's `resume.sh` bound Task 9's records to `$EVID/runners/<the previous directory's token>/task-9/`, which holds only for the FIRST successor after Task 9; from impl-13's directory it STOPs `task-9-record-mismatch`. rev40 binds them by CONTENT to exactly one token's `task-9/` record set. "
        "Task 8c resumes at Step 5 (Steps 0–4 EXECUTED under impl-13). Every other block is unchanged, `regate.sh` apart from that one line.\n")
t = t[:h] + hist + t[h:]
open(sys.argv[2], 'w', encoding='utf-8').write(t)
print('ok', t.count('\n'), hashlib.sha256(t.encode()).hexdigest())
