### Task 8c — c10, MUST-H-1: a failed repository row renders its `kind` and `detail`, never null, and the envelope validates against the product's own schema (rev39; m-3 `../pdc/master/relays/intg-2b-wiring-act/DESIGN-planner-20260926-160359.md` MUST-H-1 with F1–F5; master `PLAN-master-planner-20260926-164725.md`, F4 widened to both doors; the operator's "lighter regate pls", 2026-09-26)

**Why this task exists.** Task 9 completed at H `2893bc53` (impl-12), and m-3's owner byte review of that H returned MUST-REVISE. A url-divergence-refused row is pushed as `repo_row(*entry)` with `kind` and `detail` unset (`open.cpp:1148` at H). `write_open_result` then writes both keys on every `failed` row, as null when unset (`envelope.cpp:414-420`). The schema's `result.anyOf[1].properties.repos.items` is `additionalProperties: false` over twelve properties, neither of them `kind` nor `detail`. So the envelope fails the product's own schema exactly when the consent fail-safe fires. m-3 reproduced it with the harness validator. Master confirmed it at its own bytes and found a second door: the two-argument `repo_row` maps `RepoRestoreOutcome::failed` to `"failed"` without setting either field (`open.cpp:1069-1088`, pushed at `:1143`), and `restore_entry` initializes its row as `failed` (`restore.cpp:491`). Hence F4, the writer-side invariant, is the load-bearing arm. The fix moves H, so m-1's and m-4's no-reds at `2893bc53` go stale: all three owner reviews are retaken at the FINAL head Task 9b writes.

**Files:** `src/core/open/open.cpp`, `src/core/report/envelope.hpp`, `src/core/report/envelope.cpp`, `src/cli/url_consent.hpp`, `src/cli/url_consent.cpp`, `schemas/biv-json-envelope.v1.schema.json`, `harness/selftest/test_envelope.py` (the schema pin only), `tests/test_cli.cpp`, `tests/test_envelope.cpp`, `CMakeLists.txt`. Each is inside the 53-path allowlist; none is under `src/core/repo`, so veto 9 is untouched. ONE new commit, c10, on top of c9; no landed commit is rewritten.

**The behaviour (each cell has a witness below):**
- F1 — the url-divergence-refused row carries `outcome: "failed"` and `kind: "UrlDivergenceEntryRefused"`, A6's sealed wire kind (`to_string(ErrKind::UrlDivergenceEntryRefused)`; A11.4 item 2 leaves it as A6 sealed it).
- F2 — its `detail` is A6 `:537`'s per-entry sentence with the RAW values, exactly `<relpath>: restore failed — <op> would contact <effective> instead of the requested <requested>; approval was not given.` (no leading spaces, no trailing newline; m-3's owner fill of A10.1's silence, moving no normative byte). It reaches the wire through the writer's existing `machine_text` (A8-R2). ONE sentence function serves both carriers: `render_entry_refusal_line` becomes two spaces, that function over `consent_display(...)` values, then `\n`, and the machine detail is the same function over the raw facts, composed in `open.cpp`. Every `facts.(op|repo|requested|effective)` line in `src/cli/url_consent.cpp` still passes through `consent_display(` (Task 9's A8 census, re-run by Task 9b).
- F3 — the schema's row object gains `kind` (string) and `detail` (string), REQUIRED when `outcome` is `"failed"` and absent otherwise (an `allOf` member: `if {properties: {outcome: {const: "failed"}}}` then `required: [kind, detail]` else `not: {anyOf: [{required: [kind]}, {required: [detail]}]}`); `additionalProperties` stays `false`. Same commit as the rendering (A10.1's schema line; R-4.32). `harness/selftest/test_envelope.py`'s pin for the schema moves to c10's blob (`git hash-object`), nothing else in that file.
- F4 — the writer never emits a null `kind` or `detail`: the two `value_null()` branches go, and the two keys are written only from present values. A public predicate `bool failed_rows_complete(const biv::open::OpenReport&)`, declared in `src/core/report/envelope.hpp`, is true iff every `failed` row carries both. Open's result path evaluates it before a report is returned; when it is false, open returns a top-level typed `ErrKind::InternalError` (the exit map's `mid-fail`, exit 4; result null, A11.2's invariant) instead of a report. That closes both doors — the divergence push and the two-argument overload's `failed` mapping — without a reachability argument. `record_open_engine_failure` (which sets both) is untouched.
- Unchanged: the divergence exit (2), `url_divergence_refusals`, the human carrier's bytes, and every other row shape.

**The witnesses (F5).** (w1) The A10 divergence shim test in `tests/test_cli.cpp` (`url_divergence_refusals` at about `:2027`) additionally asserts each refused row's `kind` and `detail` bytes for the fixture's `op`, `effective` and `requested`, and writes its `--json` stdout to `BIV_DIVERGENCE_ENVELOPE_PATH`. That compile definition is set beside `BIV_GENERATED_ENVELOPE_PATH` in `CMakeLists.txt`, with a reset row `divergence_envelope_reset` and a new ctest row `divergence_envelope_conforms` that validates the file with the same `Draft202012Validator` command as `generated_envelope_conforms` (`FIXTURES_REQUIRED` on `biv_tests`'s setup, `RESOURCE_LOCK` on the artifact). (w2) For display-inert values the human line equals two spaces, the machine `detail`, then `\n`. (w3) `tests/test_envelope.cpp`: `failed_rows_complete` is false for a report with a `failed` row lacking `kind`, false for one lacking `detail`, true for a complete one, and the complete report's envelope carries no `null` for either key.

**THE MUTANT RECORD at the c10 head** (block `c10-mutants.sh`; each mutant applied to the working tree only, built, run, recorded in `$EVID/receipts/c10-mutants.txt` and reverted, the tree proved clean after each; a mutant that does not compile is a STOP). All three GATE:
- M-H1-PRE: `src/core/open/open.cpp` reverted to c9's bytes (the divergence row back to unset fields, the predicate never evaluated). (w1) goes red in `biv_tests`, and `divergence_envelope_conforms` goes red on the regenerated file.
- M-H1-SCHEMA: `schemas/biv-json-envelope.v1.schema.json` reverted to c9's bytes. `divergence_envelope_conforms` goes red, because the fixed row now carries two properties c9's schema forbids.
- M-H1-F4: the predicate made constant `true`, as a one-hunk patch the implementer prepares at `$EVID/code/c10-M-H1-F4.patch` touching `src/core/report/envelope.cpp` only (the block refuses any other path). (w3) goes red.

- [ ] **Step 0: the precondition** — HEAD is c9 (`commits.c9.txt`), which is Task 9's FINAL H (`H.txt`); the tree clean; `commits.c10.txt`, `heads/c10`, `receipts/c10-red.txt`, `receipts/c10-mutants.txt` and `code/c10-mutants` all absent.
- [ ] **Step 1: the failing tests first** — write (w1)–(w3) and the CMake rows; build; run the three named cases and the `divergence_envelope_conforms` row; record each as RED at c9's product bytes in `$EVID/receipts/c10-red.txt` (one `case=<name> rc=<n>` line each, `rc` non-zero for all four).
- [ ] **Step 2: F1–F4** — the minimal product change above; nothing outside the Files line.
- [ ] **Step 3: green** — the three cases, `biv_tests` whole, `generated_envelope_conforms`, `divergence_envelope_conforms` and harness-selftest's `test_envelope.py` all green on macOS.
- [ ] **Step 4: the commit** — `git add` the Files line's paths only; `git commit -m "open: MUST-H-1 -- the failed row's kind and detail rendered, never null; the schema admits both iff failed (m-3 160359 F1-F5; master 164725)"`; `git rev-parse HEAD > "$EVID/commits.c10.txt"`; the tree clean.
- [ ] **Step 5: the mutant record** — prepare `$EVID/code/c10-M-H1-F4.patch`, then `bash` the block `c10-mutants.sh` (extracted from this plan by `plan_blocks.py extract`) from the worktree.
- [ ] **Step 6: the head gate** — `bash` the block `headgate.sh` with `c10` (tidy list EMPTY, coverage 37/37, macOS failures 0, the canonical container rc 0, every ctest row but harness-selftest passed): `heads/c10/headgate.txt`.
- [ ] **Step 7: record** — the IMPL return enumerates c10's paths against the Files line (master 042625 (1)).

<!-- BLOCK: c10-mutants.sh -->
```bash
# Task 8c — the c10 mutant record (rev39; m-3 160359 F5, master 164725): run ONCE at the c10 head, before its head gate; usage  bash <this block>  from the worktree with EVID exported
set -o pipefail
STOP() { printf 'STOP-c10-mutants %s line=%s\n' "$1" "${BASH_LINENO[0]}" >&2; exit 1; }
[ -n "${EVID-}" ] && [ -d "$EVID/receipts" ] && [ -d "$EVID/code" ] || STOP env
z=0; C10=$(cat "$EVID/commits.c10.txt") || z=$?; [ "$z" -eq 0 ] && [ -n "$C10" ] && [ "$(git rev-parse HEAD)" = "$C10" ] || STOP not-at-c10
z=0; C9=$(cat "$EVID/commits.c9.txt") || z=$?; [ "$z" -eq 0 ] && [ -n "$C9" ] && [ "$(git rev-parse HEAD~1)" = "$C9" ] || STOP parent-not-c9
git diff --cached --quiet && git diff HEAD --quiet || STOP dirty
O=$EVID/receipts/c10-mutants.txt; [ ! -e "$O" ] && [ ! -L "$O" ] || STOP record-exists
P=$EVID/code/c10-M-H1-F4.patch; [ -s "$P" ] && [ ! -L "$P" ] || STOP f4-patch-absent
g=0; k=$(grep -c -E '^\+\+\+ ' "$P") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP f4-patch-files; g=0; k=$(grep -c -x -F '+++ b/src/core/report/envelope.cpp' "$P") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP f4-patch-path
g=0; k=$(grep -c -E '^@@ ' "$P") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP f4-patch-hunks
a=0; git apply --check "$P" || a=$?; [ "$a" -eq 0 ] || STOP f4-patch-applies
M=$EVID/code/c10-mutants; [ ! -e "$M" ] && [ ! -L "$M" ] || STOP work-exists; m=0; mkdir "$M" || m=$?; [ "$m" -eq 0 ] || STOP work-mkdir
DW=divergence_envelope_conforms
run() { local name=$1; shift
  b=0; cmake --build --preset ci-macos > "$M/$name.build.log" 2>&1 || b=$?; [ "$b" -eq 0 ] || { git checkout -q HEAD -- .; STOP "build-$name"; }
  x=0; ./build/ci-macos/biv_tests "$@" -r xml > "$M/$name.xml" 2> "$M/$name.stderr" || x=$?
  y=0; ctest --preset ci-macos -R '^(generated_envelope_reset|divergence_envelope_reset|biv_tests|divergence_envelope_conforms)$' > "$M/$name.ctest.log" 2>&1 || y=$?
  g=0; w=$(grep -c -E "[0-9]+ - $DW \(Failed\)" "$M/$name.ctest.log") || g=$?; [ "$g" -le 1 ] || STOP "ctest-grep-$name"
  c=0; git checkout -q HEAD -- . || c=$?; [ "$c" -eq 0 ] || STOP "revert-$name"; git diff --cached --quiet && git diff HEAD --quiet || STOP "not-clean-after-$name"
  printf 'mutant=%s gating=yes case_rc=%s ctest_rc=%s conforms_failed=%s\n' "$name" "$x" "$y" "$w" >> "$O" || STOP record-write; }
g=0; git checkout -q "$C9" -- src/core/open/open.cpp || g=$?; [ "$g" -eq 0 ] || STOP apply-M-H1-PRE
run M-H1-PRE
g=0; git checkout -q "$C9" -- schemas/biv-json-envelope.v1.schema.json || g=$?; [ "$g" -eq 0 ] || STOP apply-M-H1-SCHEMA
run M-H1-SCHEMA
a=0; git apply "$P" || a=$?; [ "$a" -eq 0 ] || STOP apply-M-H1-F4
run M-H1-F4
b=0; cmake --build --preset ci-macos > "$M/rebuild.log" 2>&1 || b=$?; [ "$b" -eq 0 ] || STOP rebuild
git diff --cached --quiet && git diff HEAD --quiet || STOP dirty-after
g=0; k=$(grep -c -E '^mutant=M-H1-(PRE|SCHEMA|F4) gating=yes ' "$O") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 3 ] || STOP record-rows
g=0; k=$(grep -c -E '^mutant=M-H1-PRE gating=yes case_rc=[1-9][0-9]* ctest_rc=[1-9][0-9]* conforms_failed=1$' "$O") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP survived-M-H1-PRE
g=0; k=$(grep -c -E '^mutant=M-H1-SCHEMA gating=yes case_rc=[0-9]+ ctest_rc=[1-9][0-9]* conforms_failed=1$' "$O") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP survived-M-H1-SCHEMA
g=0; k=$(grep -c -E '^mutant=M-H1-F4 gating=yes case_rc=[1-9][0-9]* ' "$O") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP survived-M-H1-F4
printf 'c10 mutants OK (%s)\n' "$O"
```

