# R-4.49 line-1 selection — Implementation Plan (revision 0 — DRAFT SKELETON, assembled 2026-09-13; NOT filed for review)

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:executing-plans to implement this plan task-by-task, IN DOCUMENT ORDER. Steps use checkbox (`- [ ]`) syntax for tracking. Nothing in this document is authority: the implementation token is a separate bare `DISPATCH IMPL` relay from the pair Planner after the exact-hash approve; the branch push and the PR are the R-4.51 clause (2) vehicle; the merge is the operator's condition-4 token; the landing is R-4.52; nothing here releases.

**Revision 0 (2026-09-13) — SKELETON.** Assembled the same day master routed the act (`intg-r449-line1-selection-act/PLAN-master-planner-20260913-164219.md`, `165605`), from the pair Planner's audit `intg-r449/AUDIT-pair-planner-20260913-165304.md` and the R-4.50 plan's per-task runner protocol (the same `plan_blocks.py` / `run-task.sh` bytes; the same acceptance shape). TWO PLACEHOLDERS wait on m-2's word (routed by master `165601`): **[C-1]** the claude head bound and governing text; **[C-2]** the codex head bound. The reconcile with the implementer's independent audit is pending. The RUN blocks are DRAFTED for Task 0 and the instrument tasks and MARKED where they will be materialized in rev1; the two adapter patchers are drafted against the base bytes and compile-checked in a scratch clone (rev1 records the receipt). This revision is committed as the lane's working skeleton per master `165605`; it is not the artifact of review.

**Goal:** execute sealed c1 §3 / §4 / §7 and locked A12's line-1 fact set in the two adapters' collect candidate paths: candidacy is decided from a HEAD-BOUNDED read of each store file (streamed, stopped at the first line that completes the head facts), and the FULL read happens only for selected sessions and their closure descendants — the act changes COST, never MEMBERSHIP (V-LS-2).

**Architecture:** in each adapter the per-line head-fact absorption becomes a function (`absorb_transcript_line` / `absorb_rollout_line`) with the SAME first-seen rule and the SAME completion condition the existing parsers use (claude: cwd + sessionId + version; codex: the first `session_meta` record); a streaming reader (`inspect_transcript_head` / `inspect_rollout_head_stream`) feeds it chunk by chunk over the existing `secure_io::ReadHandle::stream` and stops the stream at the end of the completing line by returning a sentinel error the reader consumes (a real stream error propagates); `collect` calls the streaming reader where it used to read the whole file, and the whole-file `source_text` moves BELOW the cwd filter (codex — its tail facts keep their full-text inputs) or disappears (claude — the artifact source and `apply_torn_tail_rule` already read the selected file in full). No `secure_io` byte, no discover byte, no shape change, no sqlite byte, no harness byte. Witness tests as `SECTION`s inside EXISTING `TEST_CASE`s so the Catch2 case census (`OverallResultsCases`) — the workflow's count-gate cells, OUTSIDE this fence — does not move.

**Tech stack:** C++20 (`std::filesystem`, `<expected>`), simdjson, Catch2 v3.7.1 (`-r xml`), CMake presets `ci-macos` (host) and `ci` (the Linux parity container: ubuntu-24.04 `linux/amd64` `--init`, nofile soft == hard, `strace` added for LEG 1), the pair's per-task runner protocol, `biv pack` + `bsdtar -xOf <image> manifest.json` for LEG 3, python3 helpers carried as BLOCKs.

**Spec (the law of this act, cited never retyped):** m-2 fence rev2 `pdc:master/relays/r437-pack-timeout-diagnosis/DESIGN-m2-planner-20260903-144700.md` @ sha256 `f2216ee606a03b0b5b0b7f4562fed52a7349219c28990e6ee3e89b0cc25e8c6f` — §4 preserves `142000` §2 BYTE-FOR-BYTE by reference (determining text, TOUCHABLE, V-LS-1..6, S-LS-1..4, the three-leg witness) and consumes m-3's C-2 five rules (`143638`); Master Reviewer approve with VP concurrence `151001`; the operator's grant `r437-operator-scope-ruling/PLAN-operator-20260903-152118.md` ("lets fix both please", grant 2 of 2). Determining sealed text: c1 `2026-07-02-adapter-contract-and-session-semantics.md` §3 :188 ("candidate selection reads `cwd` from line 1 of each transcript (cheap, structure-only)"), §4 :221 ("candidate rollouts by reading `session_meta.cwd` (line 1)"), §7 :344 ("newest `updated_at`/mtime wins"); locked A12 `2026-08-12-ADDENDUM-12-transitive-collect-and-mono-gate.md` (membership + edges are session_meta line-1 facts; full text owed only to selected sessions + closure descendants). **[C-1 PLACEHOLDER]** m-2's word on the claude governing text and bound — the audit's finding: m-2's own ADDENDUM 1 §A1 (`2026-07-04-ADDENDUM-1-adapter-remediation.md` @ `df523d97…`, SEAL-READY) superseded §3's "line 1" with STREAM-SCAN-TO-FIRST-CWD (stop at first hit; whole file when none → `no_cwd_record`) — the rule the code executes today and the real store requires (2/100 real transcripts carry cwd on line 1; first cwd at lines 3–9, worst 106); the draft below implements EXACTLY that rule with today's completion condition. **[C-2 PLACEHOLDER]** m-2's word on the codex bound — the draft implements "the first `session_meta` record, the whole file when none" (1,503/1,503 real rollouts on line 1; line-1 bytes max 22,552).

## Global constraints (each line binds every task)

- DETERMINING TEXT: c1 §3, §4, §7 and locked A12's line-1 fact set as quoted above; **[C-1]** / **[C-2]** as m-2 rules them — until then this plan is not filed for review.
- TOUCHABLE (V-LS-1): `src/adapters/claude_code/claude_code.cpp` (the head-fact parser `inspect_transcript` :170-196 and the collect candidate path :654-668 at the base) + `src/adapters/codex/codex.cpp` (`inspect_rollout_head` :229-270 and the collect candidate path :1273-1301 at the base) + `tests/test_adapter_claude_collect.cpp` + `tests/test_adapter_codex_collect.cpp`. NO discover byte; NO `SessionRecord` / `CollectReport` shape change (`adapter.hpp` untouched); NO manifest / pack / open surface; NO `secure_io` byte; NO sqlite byte (V-LS-3 — `thread_updates` and `db_updated_at` untouched); NO harness byte (m-3's; S-LS-4); NO workflow byte (the count-gate cells `.github/workflows/s2-harness.yml:85` biv_tests `successes` 419 and `:326` 421 are OUTSIDE this fence — see COUNT-GATE below); NO new test FILE (a CMake byte); NO `.hpp` byte.
- VETOES V-LS-1..6 and STOPs S-LS-1..4 (`142000` §2), binding verbatim:

```text
V-LS-1  any byte outside the two collect candidate paths + tests
V-LS-2  THE LOAD-BEARING INVARIANT: any membership delta. The selected set (sessions, descendants, artifacts) is BYTE-IDENTICAL
        before/after on the ENTIRE fixture corpus. This act changes COST, never MEMBERSHIP. A delta on any fixture = red, no argument heard.
V-LS-3  any membership or narrowing use of the sqlite threads table (sealed §4: "NOT the source of truth for membership" — enrichment only, unchanged)
V-LS-4  tail facts (liveness terminal record, torn tails, newest timestamp) computed from anything less than the FULL read of each SELECTED
        session + descendant — the head-bounded read is for candidacy only
V-LS-5  warnings parity broken on the fixture corpus without a routed S-LS-3 ruling
V-LS-6  evidence not in the three-leg witness form below, or counts carried rather than derived at the candidate head
```

```text
S-LS-1  head-read mechanics the text does not fix: the byte bound for "line 1", and the disposition of a rollout whose first line is torn,
        overlong, or unparseable — owner m-2                      → C-1 / C-2 asked 2026-09-13 (`165305`, routed `165601`); PLACEHOLDERS below
S-LS-2  any fact discovered to be REQUIRED for membership or edges that does NOT live in line 1 — no in-lane semantic invention — owner m-2
S-LS-3  any user-visible warning today emitted from full-parse of NON-selected store files: disposition owner m-2, wording m-3
        → audited NONE (`165304`): no_cwd_record needs the whole file scanned and the streaming reader reads to EOF when no cwd appears;
          SessionIdWithoutId uses head facts; the enumeration / sqlite warnings are untouched — re-proven by the corpus suites at H
S-LS-4  CROSS-DOMAIN: any harness or witness expectation keyed to read counts or full-read behavior — owner m-3, routed, never patched in-lane
        → dormant by m-3's own C-2 rule 5 (oracles observe identities/provenance/paths/warnings, not read patterns); no harness byte in this act
```

- THE WITNESS, three legs (`142000` §2), executed as EVIDENCE by the runner (no witness leg is a product byte; the Catch2 `SECTION`s carry the membership cases of the corpus):

```text
LEG 1  bytes-read-per-candidate BEFORE/AFTER, instrumented at the candidate head: `strace -f -e trace=openat,read,pread64` around
       `biv pack` inside the Linux parity container at B and at H over the synthetic store S; `strace_bytes.py` reduces to
       path<TAB>bytes_read<TAB>file_size (no content) — non-selected store files: bytes_read < file_size at H (the head bound NAMED:
       the byte offset of the end of the completing line, per file); selected + descendants: bytes_read >= file_size at both
LEG 2  the cwd filter's POSITION proven ahead of any full read: at H every non-selected file's bytes_read equals the bytes to the end of
       its completing line (+ at most one 8 KiB stream chunk); the store-proportional term collapses — the per-store total bytes read
       at H is bounded by N × (head bytes) instead of the store's size; the R-4.49 registration's ~30 s cell re-measured as the pack
       wall time at B vs H on S (LEG 3's timing)
LEG 3  membership identity: `membership.py` over the manifest.json of `biv pack` images at B and at H — the fixture corpus (the on-disk
       stores under tests/fixtures/{claude,codex}_store mirrored into `work` with their cwd values re-rooted to a real work path, and
       the two collect suites' inline stores exercised by the suites themselves) PLUS the synthetic store S: the normalized session
       records EQUAL (not only ids: original_path, normalized_path_key, artifacts, children, live_at_pack, agent_version_at_pack,
       provenance); the wall-time delta on S recorded as the act's product-cost receipt
```

- COUNT-GATE (R-4.38 precedent; R-4.50's Q2 lesson): the workflow pins `OverallResultsCases successes` per binary; a NEW `TEST_CASE` moves the two `biv_tests` cells, which are OUTSIDE this fence → every new test is a `SECTION` inside an EXISTING `TEST_CASE` of the two touchable test files; Task 3 Step 3 PROVES the five binaries' `OverallResultsCases` at H EQUAL B's cells on both targets (a difference = STOP UP, V-LS-1 collision, never a transcription in this act).
- m-3's FIVE FIXTURE-ROOT RULES (`143638` §2; consumed by the fence rev2 §4) bind the instrument: (1) builders reusable by import, ids NEVER a `POISON_SESSION_IDS` value, the root NEVER the iso witness's poison root — `synth_store.py` mints its ids from a seed and writes under `$EVID/work/`; (2) FROZEN: the iso spec, `HERMETIC_LOCATORS`, `MANDATORY_PROCESS_LOCATORS`, `POISON_SESSION_IDS`, `POISON_SUBROOTS`, `_isolation_leaks`, `_rp_positive`, `test_store_isolation.py` — any byte a veto (this act touches no harness byte); (3) the synthetic store lives INSIDE `work` at a LOCATOR VALUE (`CODEX_HOME=$EVID/work/codex-home`, `CLAUDE_CONFIG_DIR=$EVID/work/claude-config`, `HOME=$EVID/work/home` with NO `.codex`/`.claude` under it), never a real host store; (4) any harness byte routed to m-3 — none needed; (5) S-LS-4 dormant by m-3's own reading.
- OWNER REVIEW: m-2's byte-level review and veto at the candidate sha (m-2.planner rules; m-2.implementer the byte seam), through master, after the IMPL return and before the vehicle's Task 6 (the plan's own Task 6 condition — the same shape as R-4.50's Task 8).
- THE VEHICLE AND THE LANDING, with the R-4.50 lessons as TERMS (master `164219` (1)–(6)): (1) Task 0 cuts a FRESH branch `intg/r449-line1-selection` and a FRESH worktree `../bivpak-intg-r449-line1-selection` from the PUBLISHED PIN `4cf135ee97f57021c5fc5fd5343de6f655fb0d24` (never from lane-local `main`) and DISPOSES the retained `-v2` worktree at H' with a receipt (`git worktree remove`; the branch refs stay); (2) before the branch push, the CENSUS OF RECORD at the BRANCH HEAD both arms — the population PRODUCED by the scan of the exact object (the branch head's tree carries the whole docs lane: at B the tree arm holds 69 locations = 3 product fixtures + 64 fixture copies + 2 English-word false positives, `results/intg-r450-main-head-census-20260913.txt`), reduced by the exact lines below, `LC_ALL=C sort -u`, CLASSIFIED by token identity against the one synthetic fixture token, names only; the synthetic store S is NOT committed and is DISCLOSED on the carrier face; (3) the branch pushed to `origin`, a PULL REQUEST against `main` — clause (2) authorizes it; (4) the PR is the VEHICLE, not the evidence — local suites GREEN both targets + the Docker parity leg + m-2's byte review + the merge bar + the operator's token are the evidence; red REMOTE CI cited nowhere; (5) the LANDING per R-4.52 in the merge packet's §7 shape: local `--no-ff` merge under the operator's token, NO trailer on any new commit, the census at the MERGE HEAD against a population file written FOR THAT OBJECT (population + reduction + collation pinned), ONE ff push of the pinned merge sha, receipts, PR observed merged at the remote; the docs commits above `4cf135ee` ride it; (6) R-4.53 arm (a): the raw/stripped census intermediates are written under `$EVID/census-raw/` and EXCLUDED from the evidence-of-record set by `finalize.py` (declared); `$EVID/work/` (the synthetic store, the pack images) likewise.
- EVIDENCE HOME (master `042340` ruling (2), STANDING) = `$HOME/Programming/bivpak-evidence/r449-<token DISPATCH_ID>-XXXXXX` (`mkdir -p` the root, `mktemp -d` the home, `pwd -P`, never the OS temp root, never inside the repository); evidence is never resumed, only bytes are; the runners directory `r449-runners-XXXXXX` under the same root.
- SHELL DISCIPLINE (standing corrective `164704`): every status captured as `rc=0; <cmd> || rc=$?` and RECORDED; never `set +e`; NO pipelines in any evidence-producing span — every producer writes a FILE and its status; every count is produced by a command over a file, never typed; the execution shell recorded.
- The GitHub token never enters a container or any evidence; credential VALUES never read, recorded or echoed (names only); the census alternation is applied to the branch head and to the merge head only through the runner's reductions (path:line; no matched text in the record — R-4.53); the host worktree byte-clean at product paths; inherited S4 state preserved, never cleaned; the MAIN checkout's product paths are NEVER mutated (no-mutation proofs as R-4.50).
- ONE commit (the grant: "ONE commissioned-lane commit"); its message carries NO `Co-Authored-By` trailer (the operator's rule); the commit message names the fence pin, the plan pin, B, and the two placeholders' rulings once they are words.
- Merge ≠ push ≠ release. The branch push and the PR are authorized by R-4.51 clause (2) via the route; the local merge waits on the four-condition bar + m-2's review + the operator's condition-4 token; the landing push is the merge packet's own step under R-4.52; the release hold is ABSOLUTE.

---

## Per-task runner protocol (rev12: master `164408` Q3 — PLAN TEXT, graded at the exact hash; rev14: the runner is the plan's own bytes; rev15: the executable text lives in RUN blocks under each Step, and the controller authenticates its instruments against the lock-verified plan before every use — F1a/F1b of `040614`; rev16: the runners directory and the evidence home live under the durable root `$HOME/Programming/bivpak-evidence/` — master `042340`)

Every task of this plan, Task 0 included, is entered ONLY through this protocol; a task entered by any other route (a controller shell call, an unproved runner, a copy at another path, a hand-typed line) is a STOP the CONTROLLER raises BEFORE the task — never a disclosure after it. The protocol has exactly two instruments, both carried in this document as fenced blocks: `plan_blocks.py` (extract / list / check) and `run-task.sh` (the controller). THE EXECUTABLE TEXT OF EVERY STEP IS A FENCED `RUN: task-N` BLOCK PLACED DIRECTLY UNDER THAT STEP'S PROSE; a task's runner is DERIVED as the fixed PROLOGUE(N) followed by the concatenation of Task N's RUN blocks in document order — there is no second copy of the runner to drift from, no manifest, no template, no glue: a line is executable if and only if it stands in a RUN block, and the prose around a RUN block explains it without being able to add to it. The trust root is the plan on disk, checked against the token's PLAN_LOCK digest (the ONE typed value) at bootstrap and again by the controller before every task; both instruments are re-derived from that lock-verified plan by a fixed one-line reader and compared byte-for-byte before they are used, so an instrument edited after bootstrap cannot extract, certify or run anything.

- **(0) The runners directory and the two instruments, ONCE, before Task 0, outside the repository and under the DURABLE evidence root (rev16; master `042340` ruling (2) — never the OS temp root)** — in the operator's shell (bash or zsh), every line status-gated: `mkdir -p "$HOME/Programming/bivpak-evidence" || exit 1; RUNNERS_RAW=$(mktemp -d "$HOME/Programming/bivpak-evidence/r449-runners-XXXXXX") || exit 1; RUNNERS=$(cd "$RUNNERS_RAW" && pwd -P) || exit 1; [ -d "$RUNNERS" ] && [ "$RUNNERS" = "$RUNNERS_RAW" ] || exit 1`; `PLAN=/Users/jack/Programming/bivpak/docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-r449-line1-selection-20260913.md; [ -s "$PLAN" ] || exit 1; printf '%s\n' "$PLAN" > "$RUNNERS/plan-path.txt" || exit 1`; the token's PLAN_LOCK digest, typed ONCE from the token relay and checked against the file on disk: `printf '%s\n' <the token's PLAN_LOCK sha256> > "$RUNNERS/plan-lock.txt" || exit 1; h=0; shasum -a 256 "$PLAN" > "$RUNNERS/plan-hash.txt" || h=$?; [ "$h" -eq 0 ] && [ -s "$RUNNERS/plan-hash.txt" ] || exit 1; d=$(cut -d' ' -f1 "$RUNNERS/plan-hash.txt") || exit 1; e=$(cat "$RUNNERS/plan-lock.txt") || exit 1; [ -n "$d" ] && [ "$d" = "$e" ] || exit 1` (the plan on disk IS the token's plan, or nothing starts); the token's DISPATCH_ID, typed ONCE — it names the evidence home and the tracked results directory (rev16): `printf '%s\n' <the token's DISPATCH_ID> > "$RUNNERS/token-id.txt" || exit 1; [ -s "$RUNNERS/token-id.txt" ] || exit 1`; THE FIXED READER — one python line that reads a named BLOCK straight from the plan's bytes, the same line the controller carries as `bx` — extracts BOTH instruments (rev15: the controller is no longer extracted by the extractor): `x=0; python3 -c 'import sys; t = open(sys.argv[1], encoding="utf-8").read(); m = "<!-- BLOCK: " + sys.argv[2] + " -->\n"; i = t.index(m) + len(m); j = t.index("\n", i) + 1; k = t.index("\n" + chr(96) * 3 + "\n", j); sys.stdout.write(t[j:k + 1])' "$PLAN" plan_blocks.py > "$RUNNERS/plan_blocks.py" || x=$?; [ "$x" -eq 0 ] && [ -s "$RUNNERS/plan_blocks.py" ] || exit 1; k=0; python3 -m py_compile "$RUNNERS/plan_blocks.py" || k=$?; [ "$k" -eq 0 ] || exit 1; x=0; python3 "$RUNNERS/plan_blocks.py" extract "$PLAN" plan_blocks.py > "$RUNNERS/plan_blocks.self.py" || x=$?; [ "$x" -eq 0 ] && [ -s "$RUNNERS/plan_blocks.self.py" ] || exit 1; c=0; cmp "$RUNNERS/plan_blocks.py" "$RUNNERS/plan_blocks.self.py" || c=$?; [ "$c" -eq 0 ] || exit 1; h=0; shasum -a 256 "$RUNNERS/plan_blocks.py" > "$RUNNERS/plan_blocks.sha256" || h=$?; [ "$h" -eq 0 ] && [ -s "$RUNNERS/plan_blocks.sha256" ] || exit 1`; `x=0; python3 -c 'import sys; t = open(sys.argv[1], encoding="utf-8").read(); m = "<!-- BLOCK: " + sys.argv[2] + " -->\n"; i = t.index(m) + len(m); j = t.index("\n", i) + 1; k = t.index("\n" + chr(96) * 3 + "\n", j); sys.stdout.write(t[j:k + 1])' "$PLAN" run-task.sh > "$RUNNERS/run-task.sh" || x=$?; [ "$x" -eq 0 ] && [ -s "$RUNNERS/run-task.sh" ] || exit 1; chmod 0500 "$RUNNERS/run-task.sh" || exit 1; [ -x "$RUNNERS/run-task.sh" ] || exit 1; h=0; shasum -a 256 "$RUNNERS/run-task.sh" > "$RUNNERS/run-task.sha256" || h=$?; [ "$h" -eq 0 ] && [ -s "$RUNNERS/run-task.sha256" ] || exit 1`; the block census of this artifact (every block, every derived runner — name, sha256, line count, RUN-block count; Task 0 re-derives it into the evidence home and compares): `x=0; python3 "$RUNNERS/plan_blocks.py" list "$PLAN" > "$RUNNERS/blocks.txt" || x=$?; [ "$x" -eq 0 ] && [ -s "$RUNNERS/blocks.txt" ] || exit 1`. From here the operator's ONLY act per task is `"$RUNNERS/run-task.sh" N` for N = 0, 1, …, 9 in order (rev17: Task 9 is the tracked-record FINALIZER — it runs through the same controller AFTER the controller has written Task 8's receipts); nothing else is typed.
- **(a) Authenticate, then materialize** — `run-task.sh N` first re-hashes the plan against `plan-lock.txt`, then re-reads its OWN block and the extractor's block from that plan with the fixed reader and `cmp`s them against `$0` and `$RUNNERS/plan_blocks.py` (`STOP-controller-task-N-not-the-plan-bytes` / `STOP-controller-task-N-extractor-not-the-plan-bytes` — an instrument edited after bootstrap stops the controller BEFORE any extraction; rev15, F1a of `040614`); only then it writes `$RUNNERS/task-N.sh` as `plan_blocks.py extract "$PLAN" task-N` — PROLOGUE(N) + Task N's RUN blocks in order, nothing added, nothing removed; the controller refuses to run if `task-N.sh`, `task-N.exit` or `task-N.done` already exists (a task is materialized and executed exactly once per token) and if `task-(N-1).done` does not read `rc=0` (document order).
- **(b) Prove** BEFORE the task's first command — `plan_blocks.py check "$PLAN" N "$RUNNERS/task-N.sh" > "$RUNNERS/proof-N.txt"`, exit 0 and a last line `rc=0` ONLY IF (i) the runner file equals the DERIVED task-N runner BYTE-FOR-BYTE — every executable Step record, in order, with its exact multiplicity, is in the runner because the runner IS their concatenation (an omitted, added, repeated, reordered or edited line — gate or not — is `BYTES-DIFFER`, exit 5; rev15, F1b of `040614`); (ii) every `RUN: task-N` block lies inside Task N's section and Task N's section holds no other task's RUN block (`RUN-BLOCK-OUTSIDE-SECTION` / `FOREIGN-RUN-BLOCK`, exit 5); (iii) the derived runner opens with PROLOGUE(N) exactly as `plan_blocks.py` defines it (`PROLOGUE`, plus `PROLOGUE_EVID` for N ≥ 1, `@N@` = N); (iv) the narrative stays bound to the executable text: every GATE span of Task N's prose (a backtick span carrying `|| STOP`, `|| exit`, `; exit 1;` or `exit 0; fi`) is a runner line and the gate spans occur in the runner in the prose's order (`OMITTED` / `OUT-OF-ORDER`, exit 5); then `bash -n` on the runner (a syntax error is a STOP before anything runs). Every violation is printed with its line; the proof's last line is `rc=<n>`.
- **(c) Mode and identity on the SAME path** — the controller `chmod 0500`s the proved file, checks `-x`, records `shasum -a 256` into `$RUNNERS/task-N.sha256`, writes the invocation string to `$RUNNERS/task-N.invocation.txt` and invokes BY THAT PATH STRING: `"$RUNNERS/task-N.sh" "$RUNNERS" "$EVID"` (`"$RUNNERS/task-0.sh" "$RUNNERS"` for Task 0, which CREATES the evidence home and records it in `$RUNNERS/evid.txt`). The exit status lands in `task-N.exit`; `task-N.done` (`rc=0`) is written only on exit 0, and Task N+1 cannot start without it; the extractor's digest at each task is recorded (`plan_blocks.sha256-N`) and copied to `$EVID/runners/` (tokens 8 and 10 died on a mode set on one copy and another copy invoked; token 11 on tasks entered outside a proof — both shapes are impossible here by construction).
- **(d) The runner's FIRST lines are the PROLOGUE** (byte-checked by (b)(iii)): `set -u`; the `STOP` function (prints the failing line number, exits 1); `RUNNERS` from `$1` and the path identity `[ "$0" = "$RUNNERS/task-N.sh" ]`; the proof-tail check (`proof-N.txt` must end `rc=0`); the self-digest — `shasum -a 256 "$0"` into `task-N.self.sha256`, its digest `cut` from that file and compared to the digest `cut` from `task-N.sha256` (staged producers, no pipeline — F4 of `010557`); for N ≥ 1 `EVID` from `$2`, equal to `$RUNNERS/evid.txt`, and the copy of the task's proof set (`task-N.sh`, `proof-N.txt`, `task-N.sha256`, `task-N.invocation.txt`) into `$EVID/runners/`. So a task cannot run off-path, unproved, or with bytes other than the proved ones even if the controller is bypassed.
- **(e) One runner per task, the whole task** — a task's runner is exactly one file executed exactly once; a task that the receipt routes to a skip still has a runner (the prologue, the receipt read, the skip receipt, `exit 0`); a STOP inside a runner ends the token (the plan's `|| STOP` gates are the stop instrument; `STOP` exits 1 naming the line); nothing of Task N executes outside `task-N.sh`, and nothing of Task N+1 executes before `task-N.done` exists. The Linux container scripts (`linux-container.sh`, `linux-suite.sh`) and the python helpers are single BLOCKs of this document: Task 0 Step 0b materializes them by `plan_blocks.py extract`, compiles/syntax-checks them and records `helpers.sha256`; every later runner re-verifies that digest file (`shasum -a 256 -c`) before it uses any helper — a helper, like a runner, is the plan's bytes or nothing.

**`plan_blocks.py`** (the protocol's own instrument; read from the plan by the fixed reader at (0) and re-verified by the controller before every use; never edited)

<!-- BLOCK: plan_blocks.py -->
```python
#!/usr/bin/env python3
# usage: plan_blocks.py extract <plan.md> <name>        — a single BLOCK (the fenced block after `<!-- BLOCK: <name> -->`) byte-for-byte; for <name> = task-N
#                                                          the DERIVED RUNNER: PROLOGUE(N) + the concatenation, in document order, of every fenced block that
#                                                          follows a `<!-- RUN: task-N -->` marker (exit 2: marker absent/duplicated/unterminated, or no RUN block)
#        plan_blocks.py list <plan.md>                  — every BLOCK and every derived task runner, in document order: <name> <sha256> <line-count> [run-blocks=<k>]
#        plan_blocks.py check <plan.md> <N> <runner.sh> — exit 0 iff (i) the runner file == the derived task-N runner BYTE-FOR-BYTE; (ii) every `RUN: task-N`
#                                                          marker lies inside Task N's section and that section holds no RUN marker of another task; (iii) the
#                                                          derived runner opens with PROLOGUE(N); (iv) every GATE span of Task N's prose (a backtick span carrying
#                                                          `|| STOP`, `|| exit`, `; exit 1;` or `exit 0; fi`) is a runner line and the gate spans occur in the runner
#                                                          in the prose's order — the narrative stays bound to the executable text; 5 = a violation (each
#                                                          printed); 2 = a missing input. The last line printed is always rc=<n>.
import hashlib, re, sys
GATE = ("|| STOP", "|| exit", "; exit 1;", "exit 0; fi")
PROLOGUE = """#!/usr/bin/env bash
# task-@N@.sh — materialized VERBATIM from the plan's BLOCK task-@N@ by plan_blocks.py extract; proved by plan_blocks.py check; invoked by run-task.sh @N@
set -u
STOP() { printf 'STOP-task-@N@ line=%s\\n' "${BASH_LINENO[0]}" >&2; exit 1; }
RUNNERS=${1-}; [ -n "$RUNNERS" ] && [ -d "$RUNNERS" ] || exit 1
[ "$0" = "$RUNNERS/task-@N@.sh" ] || { printf 'STOP-task-@N@-invoked-off-path %s\\n' "$0" >&2; exit 1; }
t=0; tail -n 1 "$RUNNERS/proof-@N@.txt" > "$RUNNERS/task-@N@.proof-tail" 2>/dev/null || t=$?; [ "$t" -eq 0 ] && [ "$(cat "$RUNNERS/task-@N@.proof-tail")" = rc=0 ] || { printf 'STOP-task-@N@-unproved\\n' >&2; exit 1; }
h=0; shasum -a 256 "$0" > "$RUNNERS/task-@N@.self.sha256" || h=$?; [ "$h" -eq 0 ] && [ -s "$RUNNERS/task-@N@.self.sha256" ] || exit 1
a=$(cut -d' ' -f1 "$RUNNERS/task-@N@.self.sha256") || exit 1; b=$(cut -d' ' -f1 "$RUNNERS/task-@N@.sha256") || exit 1; [ -n "$a" ] && [ "$a" = "$b" ] || { printf 'STOP-task-@N@-bytes-differ\\n' >&2; exit 1; }
"""
PROLOGUE_EVID = """EVID=${2-}; [ -n "$EVID" ] && [ -d "$EVID" ] || exit 1; [ "$EVID" = "$(cat "$RUNNERS/evid.txt")" ] || exit 1
c=0; cp -p "$RUNNERS/task-@N@.sh" "$RUNNERS/proof-@N@.txt" "$RUNNERS/task-@N@.sha256" "$RUNNERS/task-@N@.invocation.txt" "$EVID/runners/" || c=$?; [ "$c" -eq 0 ] || exit 1
"""
def prologue(n):
    p = PROLOGUE + ("" if n == "0" else PROLOGUE_EVID)
    return p.replace("@N@", n)
def read(plan):
    return open(plan, encoding="utf-8").read()
def fenced(lines, i):
    # lines[i] is a marker line; the fence opens on the next line and closes on a line that is exactly ```
    if i + 1 >= len(lines) or not lines[i + 1].startswith("```"):
        sys.exit(2)
    j = i + 2
    body = []
    while j < len(lines) and lines[j] != "```":
        body.append(lines[j])
        j += 1
    if j >= len(lines):
        sys.exit(2)
    return "\n".join(body) + "\n", j
def scan(text):
    """returns (blocks: name -> body, runs: list of (task, line_index, body)) in document order"""
    lines = text.split("\n")
    blocks, runs = {}, []
    i = 0
    while i < len(lines):
        m = re.match(r"^<!-- BLOCK: ([A-Za-z0-9_.-]+) -->$", lines[i])
        r = re.match(r"^<!-- RUN: task-([0-9]) -->$", lines[i])
        if m:
            name = m.group(1)
            if name in blocks or re.match(r"^task-[0-9]$", name):
                sys.exit(2)
            body, j = fenced(lines, i)
            blocks[name] = body
            i = j
        elif r:
            body, j = fenced(lines, i)
            runs.append((r.group(1), i, body))
            i = j
        i += 1
    return blocks, runs
def section_bounds(text, n):
    """(start_line, end_line) of Task N's section as line indexes, or None"""
    lines = text.split("\n")
    start = None
    for i, ln in enumerate(lines):
        if start is None and re.match(r"^### Task %s —" % re.escape(n), ln):
            start = i
        elif start is not None and (ln.startswith("### Task ") or ln.startswith("## ")):
            return start, i
    return (start, len(lines)) if start is not None else None
def derived(text, n, runs=None):
    if runs is None:
        runs = scan(text)[1]
    mine = [body for task, _, body in runs if task == n]
    if not mine:
        sys.exit(2)
    return prologue(n) + "".join(mine)
def spans(sec):
    return re.findall(r"`([^`\n]+)`", sec)
def extract(plan, name):
    text = read(plan)
    m = re.match(r"^task-([0-9])$", name)
    if m:
        sys.stdout.write(derived(text, m.group(1)))
        return 0
    blocks, _ = scan(text)
    if name not in blocks:
        sys.exit(2)
    sys.stdout.write(blocks[name])
    return 0
def listing(plan):
    text = read(plan)
    blocks, runs = scan(text)
    for name, body in blocks.items():
        print("%s %s %d" % (name, hashlib.sha256(body.encode("utf-8")).hexdigest(), body.count("\n")))
    for n in "0123456789":
        k = sum(1 for task, _, _ in runs if task == n)
        if k:
            body = derived(text, n, runs)
            print("task-%s %s %d run-blocks=%d" % (n, hashlib.sha256(body.encode("utf-8")).hexdigest(), body.count("\n"), k))
    return 0
def check(plan, n, runner):
    text = read(plan)
    blocks, runs = scan(text)
    b = section_bounds(text, n)
    if b is None or not any(task == n for task, _, _ in runs):
        sys.exit(2)
    try:
        run = open(runner, encoding="utf-8").read()
    except OSError:
        sys.exit(2)
    rc = 0
    blk = derived(text, n, runs)
    if run != blk:
        rl, bl = run.split("\n"), blk.split("\n")
        k = next((i for i in range(min(len(rl), len(bl))) if rl[i] != bl[i]), min(len(rl), len(bl)))
        print("BYTES-DIFFER at runner line %d (runner %d lines, derived %d lines)" % (k + 1, len(rl), len(bl)))
        rc = 5
    placed = 0
    for task, li, _ in runs:
        inside = b[0] <= li < b[1]
        if task == n and not inside:
            print("RUN-BLOCK-OUTSIDE-SECTION: RUN task-%s at line %d is outside Task %s's section" % (task, li + 1, n))
            rc = 5
        if task != n and inside:
            print("FOREIGN-RUN-BLOCK: RUN task-%s at line %d inside Task %s's section" % (task, li + 1, n))
            rc = 5
        if task == n and inside:
            placed += 1
    pro = prologue(n)
    if not blk.startswith(pro):
        print("PROLOGUE-MISMATCH")
        rc = 5
    sec_lines = text.split("\n")[b[0]:b[1]]
    sec = "\n".join(sec_lines)
    sp = spans(sec)
    gates = [s for s in sp if any(g in s for g in GATE)]
    lines = blk.split("\n")
    pos = {}
    for i, ln in enumerate(lines):
        pos.setdefault(ln, []).append(i)
    last = -1
    omitted = 0
    order = 0
    for s in gates:
        idx = [i for i in pos.get(s, []) if i >= last]
        if s not in pos:
            print("OMITTED gate span: %s" % s)
            omitted += 1
            rc = 5
        elif not idx:
            print("OUT-OF-ORDER gate span (runner lines %s, after %d): %s" % (",".join(str(i + 1) for i in pos[s]), last + 1, s))
            order += 1
            rc = 5
        else:
            last = idx[0]
    print("bytes=%s run_blocks=%d prologue=%s lines=%d spans=%d gates=%d omitted=%d out_of_order=%d" % (
        "equal" if run == blk else "differ", placed, "ok" if blk.startswith(pro) else "mismatch", len(lines) - 1, len(sp), len(gates), omitted, order))
    print("rc=%d" % rc)
    return rc
if __name__ == "__main__":
    if len(sys.argv) == 4 and sys.argv[1] == "extract":
        sys.exit(extract(sys.argv[2], sys.argv[3]))
    if len(sys.argv) == 3 and sys.argv[1] == "list":
        sys.exit(listing(sys.argv[2]))
    if len(sys.argv) == 5 and sys.argv[1] == "check":
        sys.exit(check(sys.argv[2], sys.argv[3], sys.argv[4]))
    sys.exit(2)
```

**`run-task.sh`** (the controller; read from the plan by the fixed reader at (0), self-verified against the plan before every task; the operator's only per-task act is `"$RUNNERS/run-task.sh" N`)

<!-- BLOCK: run-task.sh -->
```bash
#!/usr/bin/env bash
# run-task.sh N — the CONTROLLER (protocol (a)–(c)): authenticate itself and the extractor against the lock-verified plan, materialize task-N.sh from the plan's RUN blocks, prove it, fix its mode and digest, invoke it BY PATH, record the exit.
set -u
N=${1-}
case "$N" in 0|1|2|3|4|5|6|7|8|9) ;; *) printf 'usage: run-task.sh N (0..9)\n' >&2; exit 2;; esac
RUNNERS=$(cd "$(dirname "$0")" && pwd -P) || exit 1
[ "$0" = "$RUNNERS/run-task.sh" ] || { printf 'STOP-controller-invoked-off-path %s\n' "$0" >&2; exit 1; }
STOP() { printf 'STOP-controller-task-%s line=%s\n' "$N" "${BASH_LINENO[0]}" >&2; exit 1; }
PLAN=$(cat "$RUNNERS/plan-path.txt") || STOP; [ -s "$PLAN" ] || STOP
h=0; shasum -a 256 "$PLAN" > "$RUNNERS/plan-hash-$N.txt" || h=$?; [ "$h" -eq 0 ] && [ -s "$RUNNERS/plan-hash-$N.txt" ] || STOP
d=$(cut -d' ' -f1 "$RUNNERS/plan-hash-$N.txt") || STOP; e=$(cat "$RUNNERS/plan-lock.txt") || STOP; [ -n "$d" ] && [ "$d" = "$e" ] || STOP
bx() { python3 -c 'import sys; t = open(sys.argv[1], encoding="utf-8").read(); m = "<!-- BLOCK: " + sys.argv[2] + " -->\n"; i = t.index(m) + len(m); j = t.index("\n", i) + 1; k = t.index("\n" + chr(96) * 3 + "\n", j); sys.stdout.write(t[j:k + 1])' "$PLAN" "$1"; }
x=0; bx run-task.sh > "$RUNNERS/run-task.fresh-$N.sh" || x=$?; [ "$x" -eq 0 ] && [ -s "$RUNNERS/run-task.fresh-$N.sh" ] || STOP; c=0; cmp "$0" "$RUNNERS/run-task.fresh-$N.sh" || c=$?; [ "$c" -eq 0 ] || { printf 'STOP-controller-task-%s-not-the-plan-bytes\n' "$N" >&2; exit 1; }
x=0; bx plan_blocks.py > "$RUNNERS/plan_blocks.fresh-$N.py" || x=$?; [ "$x" -eq 0 ] && [ -s "$RUNNERS/plan_blocks.fresh-$N.py" ] || STOP; c=0; cmp "$RUNNERS/plan_blocks.py" "$RUNNERS/plan_blocks.fresh-$N.py" || c=$?; [ "$c" -eq 0 ] || { printf 'STOP-controller-task-%s-extractor-not-the-plan-bytes\n' "$N" >&2; exit 1; }
h=0; shasum -a 256 "$RUNNERS/plan_blocks.py" > "$RUNNERS/plan_blocks.sha256-$N" || h=$?; [ "$h" -eq 0 ] && [ -s "$RUNNERS/plan_blocks.sha256-$N" ] || STOP
if [ "$N" -gt 0 ]; then M=$((N - 1)); [ -s "$RUNNERS/task-$M.done" ] && [ "$(cat "$RUNNERS/task-$M.done")" = rc=0 ] || STOP; fi
[ ! -e "$RUNNERS/task-$N.done" ] && [ ! -e "$RUNNERS/task-$N.sh" ] && [ ! -e "$RUNNERS/task-$N.exit" ] || STOP
m=0; python3 "$RUNNERS/plan_blocks.py" extract "$PLAN" "task-$N" > "$RUNNERS/task-$N.sh" || m=$?; [ "$m" -eq 0 ] && [ -s "$RUNNERS/task-$N.sh" ] || STOP
c=0; python3 "$RUNNERS/plan_blocks.py" check "$PLAN" "$N" "$RUNNERS/task-$N.sh" > "$RUNNERS/proof-$N.txt" || c=$?; [ "$c" -eq 0 ] && [ -s "$RUNNERS/proof-$N.txt" ] || STOP
t=0; tail -n 1 "$RUNNERS/proof-$N.txt" > "$RUNNERS/proof-$N.tail" || t=$?; [ "$t" -eq 0 ] && [ "$(cat "$RUNNERS/proof-$N.tail")" = rc=0 ] || STOP
s=0; bash -n "$RUNNERS/task-$N.sh" || s=$?; [ "$s" -eq 0 ] || STOP
chmod 0500 "$RUNNERS/task-$N.sh" || STOP; [ -x "$RUNNERS/task-$N.sh" ] || STOP
h=0; shasum -a 256 "$RUNNERS/task-$N.sh" > "$RUNNERS/task-$N.sha256" || h=$?; [ "$h" -eq 0 ] && [ -s "$RUNNERS/task-$N.sha256" ] || STOP
if [ "$N" -eq 0 ]; then EVID=; printf '"%s/task-0.sh" "%s"\n' "$RUNNERS" "$RUNNERS" > "$RUNNERS/task-0.invocation.txt" || STOP; else EVID=$(cat "$RUNNERS/evid.txt") || STOP; [ -d "$EVID" ] || STOP; printf '"%s/task-%s.sh" "%s" "%s"\n' "$RUNNERS" "$N" "$RUNNERS" "$EVID" > "$RUNNERS/task-$N.invocation.txt" || STOP; fi
r=0; if [ "$N" -eq 0 ]; then "$RUNNERS/task-0.sh" "$RUNNERS" || r=$?; else "$RUNNERS/task-$N.sh" "$RUNNERS" "$EVID" || r=$?; fi
printf 'rc=%s\n' "$r" > "$RUNNERS/task-$N.exit" || exit 1
[ "$r" -eq 0 ] || { printf 'task-%s exited %s — STOP; the token ends here\n' "$N" "$r" >&2; exit 1; }
printf 'rc=0\n' > "$RUNNERS/task-$N.done" || exit 1
EVID=$(cat "$RUNNERS/evid.txt") || exit 1; c=0; cp -p "$RUNNERS/task-$N.done" "$RUNNERS/task-$N.exit" "$RUNNERS/proof-$N.tail" "$RUNNERS/plan_blocks.sha256-$N" "$EVID/runners/" || c=$?; [ "$c" -eq 0 ] || exit 1
printf 'task-%s done rc=0\n' "$N"
```


## B / H / S — roles, resolution, binding points (predeclared BEFORE any observation)

```text
B  the BASE = the published pin = origin/main = 4cf135ee97f57021c5fc5fd5343de6f655fb0d24 (the R-4.50 landing merge). RESOLVED at
   Task 0 Step 1 (the remote re-read must equal it; any other value = STOP UP, never a silent re-base) and RECORDED with B's workflow
   cells (the ten OverallResultsCases cells read from `git show 4cf135ee…:.github/workflows/s2-harness.yml`) → $EVID/B.txt, $EVID/B-cells.txt.
   B is the BEFORE side of every witness leg (built and observed in this token on both targets).
H  the CANDIDATE = B + EXACTLY ONE commit (the two adapter files + the two test files). H's identity is RECORDED at Task 2 Step 6 (after
   the commit exists, BEFORE Task 3 observes it) → $EVID/H.txt; H^ == B proven there. H is the PR HEAD; the acceptance suites of record
   run at H on both targets (Task 3, Task 4); the witness legs run at H against B (Task 4 for LEG 1/2; Task 3/Task 4 for LEG 3).
S  the LARGE SYNTHETIC STORE pair (codex-home + claude-config under $EVID/work/, cwd of exactly K sessions == $EVID/work/ws/proj) built
   ONCE at Task 1 Step 2 by `synth_store.py <work> <seed>` (seed recorded → $EVID/synth-seed.txt; the manifest → $EVID/synth-manifest.json,
   names/ids/counts only); S is the same bytes on both sides (built once, read by B's binary and by H's binary); S is EXCLUDED from the
   evidence-of-record set and never committed; S's cwd/ids never match any iso poison value (rule 1) and live at locator values (rule 3).
F  the FIXTURE CORPUS = tests/fixtures/{claude,codex}_store (on disk, committed at B; the claude fixture `aaaaaaaa…` has the REAL
   metadata-first head, first cwd on line 5; the `no-cwd-9999…` fixture has no cwd anywhere) + the two collect suites' inline stores.
   The suites at H are the membership oracle over F (every existing assertion; the new SECTIONs); LEG 3's manifest comparison covers S.
ANTI-RETROSPECTION  B.txt and H.txt are written at their binding steps and never rewritten; every later use re-reads them.
```

## File structure

- Modify: `src/adapters/claude_code/claude_code.cpp` — `inspect_transcript` refactored over `absorb_transcript_line` (same semantics); `inspect_transcript_head` (new, streaming); `collect` candidate path: the whole-file read before the cwd filter removed (patcher BLOCK `head_reader_claude.py`, anchors asserted once at B's bytes).
- Modify: `src/adapters/codex/codex.cpp` — `inspect_rollout_head` refactored over `absorb_rollout_line`; `inspect_rollout_head_stream` (new); `collect`: the head read first, the full `source_text` moved below the cwd filter (patcher BLOCK `head_reader_codex.py`).
- Modify: `tests/test_adapter_claude_collect.cpp` — `SECTION`s inside existing `TEST_CASE`s (rev1 names them): (a) first cwd on line 6 behind a multi-MiB body → selected, membership and every record field as before; (b) a no-cwd transcript with a multi-MiB body → `no_cwd_record`, not silence; (c) an unterminated last line carrying the completing facts → selected (getline parity).
- Modify: `tests/test_adapter_codex_collect.cpp` — `SECTION`s: (a) `session_meta` on line 2 after an unparseable line 1 → selected as today; (b) a rollout with a multi-MiB body after line 1 → selected; tail facts (live/terminal, newest timestamp) unchanged; (c) empty / lone-LF rollouts → not candidates (the tail-matrix fixtures already cover).
- Evidence (outside the repository): `$EVID` under the durable root; `$EVID/work/` (S, the pack images, the mirrored corpus) and `$EVID/census-raw/` EXCLUDED from the record (`finalize.py` SCRATCH); the tracked record `results/r449-<token>/` by Task 7.
- Instruments (BLOCKs of this document; materialized at Task 0 Step 0b; hashed; verified before every task): `linux-container.sh` (the parity container — the R-4.50 block with the branch name `intg/r449-line1-selection` and `strace` added to Phase R's package list), `linux-suite.sh` (unchanged from R-4.50 rev19), `selftest_summary.py` (unchanged), `finalize.py` (SCRATCH extended: `work`, `census-raw`), `synth_store.py`, `membership.py`, `strace_bytes.py`, `head_reader_claude.py`, `head_reader_codex.py`.

### Task 0 — bootstrap: evidence home, the `-v2` worktree DISPOSED with a receipt, the FRESH branch + worktree from the pin, B recorded, helpers materialized, venv/build at B

- [ ] **Step 0: the evidence home** — as R-4.50 Task 0 Step 0 with the `r449-` prefix: `TOKEN` from `$RUNNERS/token-id.txt`; `EVID` = `mktemp -d "$HOME/Programming/bivpak-evidence/r449-${TOKEN}-XXXXXX"` resolved with `pwd -P`; not inside the repository; `token.txt`; the MAIN checkout's product-path status snapshot (`status-initial.txt`, must be EMPTY over `src tests CMake* harness .github`).
- [ ] **Step 0b: helpers materialized** — every BLOCK named in File structure extracted by `plan_blocks.py extract` into `$EVID`, `py_compile`d, `shasum -a 256` into `helpers.sha256` (verified by every later task's plumbing).
- [ ] **Step 1: B resolved and recorded** — `git -C /Users/jack/Programming/bivpak fetch --no-tags origin refs/heads/main:refs/remotes/origin/main`; `origin/main` MUST equal `4cf135ee97f57021c5fc5fd5343de6f655fb0d24` or STOP; B's ten cells from `git show 4cf135ee…:.github/workflows/s2-harness.yml` → `B-cells.txt`; `B.txt`.
- [ ] **Step 2: the retained `-v2` worktree DISPOSED (master `164219` (1); ruled lane-local state)** — preconditions: `git -C ../bivpak-intg-r450-discover-parity rev-parse HEAD` == H' `e8a1128d75cd4693d21269c4d040095df570f116`, status EMPTY, both branch refs present locally and at origin (`ls-remote`); then `git worktree remove ../bivpak-intg-r450-discover-parity` (rc recorded; the path must be ABSENT after; `git worktree list` no longer names it; the refs `intg/r450-discover-parity` and `-v2` UNCHANGED before/after) → `worktree-dispose.txt`. A non-empty status or a missing ref = STOP UP.
- [ ] **Step 3: the FRESH branch and worktree from the pin** — `git show-ref --verify refs/heads/intg/r449-line1-selection` MUST fail (no such branch) and `git ls-remote --heads origin intg/r449-line1-selection` MUST be empty or STOP; `git worktree add -b intg/r449-line1-selection ../bivpak-intg-r449-line1-selection 4cf135ee97f57021c5fc5fd5343de6f655fb0d24`; `rev-parse HEAD` == B; status EMPTY; cut-point `git rev-list --count origin/main..HEAD` == 0 → `worktree-fresh.txt`.
- [ ] **Step 4: venv + build at B (ci-macos)** — the harness venv from `harness/requirements.lock` under `$EVID/venv` (R-4.50 shape); `cmake --preset ci-macos` + `cmake --build --preset ci-macos` in the fresh worktree; `build-B.log`; the observer environment names recorded (the three credential env NAMES unset for every suite run — names only).
- [ ] **Step 5: the runner's receipts** — `status-worktree-0.txt` (EMPTY over product paths; the build dir ignored), the MAIN checkout no-mutation proof (equal to `status-initial.txt`).

<!-- RUN: task-0 (rev0 DRAFT — materialized in rev1 from the R-4.50 task-0 runner with Steps 2–3 as written above) -->

### Task 1 — the BEFORE side at B: the synthetic store S, the mirrored corpus, LEG 3's B snapshot, LEG 1/2's B baseline on macOS (timing) — no product byte

- [ ] **Step 1: S's seed and locator layout** — `synth-seed.txt` (a fixed integer written here); `$EVID/work/{codex-home,claude-config,home,ws/proj}` created; the locator values recorded (`locators.txt`: names + paths, no host store).
- [ ] **Step 2: build S** — `python3 "$EVID/synth_store.py" "$EVID/work" "$(cat "$EVID/synth-seed.txt")"` → `synth-manifest.json`; counts proven (1,500 rollouts; 100 transcripts; K = 3 selected per agent); NO id equal to any `POISON_SESSION_IDS` value (grep of the harness constants' VALUES against the manifest ids = 0 — the harness file is READ, not touched).
- [ ] **Step 3: the corpus mirror** — `tests/fixtures/{claude,codex}_store` copied under `$EVID/work/corpus/` with their `/ws/proj` cwd values re-rooted to `$EVID/work/ws/proj` by a recorded `sed` over the copies (the on-disk fixtures untouched; the mirror is evidence scratch); the mirror's line-1 structure re-measured (the claude fixture's first cwd on line 5; the no-cwd fixture) → `corpus-shape.txt`.
- [ ] **Step 4: LEG 3 at B (macOS)** — with `HOME/CODEX_HOME/CLAUDE_CONFIG_DIR/TMPDIR` at the locator values: `biv pack "$EVID/work/ws/proj" --json` at B's binary → `pack-B.json` (the image beside the source under `work`), `membership.py` over `manifest.json` → `membership-B.json`; wall time → `time-B.txt` (three runs, the median); the same over the corpus mirror → `membership-corpus-B.json`.

<!-- RUN: task-1 (rev0 DRAFT — materialized in rev1) -->

### Task 2 — the CHANGE (one commit): the two patchers applied at B's bytes, the tests' SECTIONs, build, suites, H BOUND

- [ ] **Step 1: patch the adapters** — `python3 "$EVID/head_reader_claude.py" src/adapters/claude_code/claude_code.cpp` and `… head_reader_codex.py src/adapters/codex/codex.cpp` in the fresh worktree (each anchor asserted EXACTLY ONCE at B's bytes; an assertion failure = STOP — the base moved); `git diff --numstat` == exactly the two adapter paths.
- [ ] **Step 2: the tests' SECTIONs** — the two test-file patchers (rev1 BLOCKs `tests_claude_r449.py` / `tests_codex_r449.py`) insert the SECTIONs named in File structure inside existing `TEST_CASE`s; `grep -c '^TEST_CASE'` per file UNCHANGED (15 / 25) — the predictor of the count gate.
- [ ] **Step 3: build + the two collect suites** — `cmake --build --preset ci-macos`; `./build/ci-macos/biv_tests "[claude]"`… (rev1 names the exact Catch2 filters); every existing assertion of the two suites GREEN (the corpus's membership oracle).
- [ ] **Step 4: the whole `biv_tests` at H on macOS under the observer environment** — `-r xml` → `biv_tests-H-macos.xml`; `OverallResultsCases successes` == B's cell 419, skips 3 (the COUNT-GATE predictor; a difference = STOP UP).
- [ ] **Step 5: the commit** — `git add` EXACTLY the four paths; the message from the BLOCK template (no trailer); `git commit`; **Step 6: H BOUND** — `H.txt` := `git rev-parse HEAD`; `H^` == B; `git diff --numstat B H` == the four paths; `worktree status` EMPTY.

<!-- RUN: task-2 (rev0 DRAFT — materialized in rev1) -->

### Task 3 — observation and ACCEPTANCE OF RECORD at H on macOS; LEG 3 at H

- [ ] **Step 1: the acceptance (R-4.50 Task 6 Step 1 shape)** — `"${OBS_ENV[@]}" ctest --preset ci-macos -E '^safety-hardening$' --output-on-failure` REQUIRED rc 0; the unfiltered scout (rc 8 = exactly `safety-hardening`, the capability row) recorded; the five binaries' `-r xml` → tuples; the harness pytest selftest rc 0.
- [ ] **Step 2: LEG 3 at H** — `biv pack` at H's binary over S and over the corpus mirror → `membership-H.json`, `membership-corpus-H.json`; `diff membership-B.json membership-H.json` EMPTY (rc 0 or STOP — V-LS-2 red, no argument); `time-H.txt`; the delta → `cost-receipt.txt`.
- [ ] **Step 3: COUNT-GATE proof** — the five `OverallResultsCases` at H == B's ten cells (macOS here; Linux in Task 4) → `count-gate-H.txt`, a difference = STOP UP.

<!-- RUN: task-3 (rev0 DRAFT — materialized in rev1) -->

### Task 4 — the Linux parity leg at H and at B (the four-phase container; LEG 1 and LEG 2 by strace; the iso rev13 bar with the in-token base draw)

- [ ] **Step 1: the container at H** — `linux-container.sh "$H" H` (Phase R/T/S as R-4.50; the repo mounted read-only from the MAIN checkout — the fresh worktree is a LINKED worktree so H is in the shared object store; `strace` provisioned); Phase S adds LEG 1: inside the container `strace -f -e trace=openat,read,pread64 -o /work/out/strace-H.log ./build/ci/biv pack /evidence/work/ws/proj --json` with the locator env at `/evidence/work/…` (S mounted through `$EVID`); `strace_bytes.py` → `bytes-H.txt`.
- [ ] **Step 2: the container at B (the base draw of clause (f) AND LEG 1's before side)** — the same at B; `bytes-B.txt`.
- [ ] **Step 3: LEG 1 / LEG 2 reduction (host side)** — from `bytes-B.txt` / `bytes-H.txt` and `synth-manifest.json`: for every NON-selected store file at H `bytes_read < file_size` and `bytes_read <= head_end + 8192` where `head_end` is the byte offset of the end of its completing line (computed by a recorded python pass over S — structure only); for every SELECTED file `bytes_read >= file_size` at B and at H; the store total at H vs at B; → `leg1-verdict.txt`, `leg2-verdict.txt` (each a set of measured rows and one verdict line; a violation = STOP UP).
- [ ] **Step 4: the iso rev13 bar (a)–(h) at H with the in-token base draw at B** — EXACTLY the R-4.50 Task 6 Step 2 lines (the receipt `H/linux-selftest-bar.txt`; the two admitted outcomes `pass-green` | `pass-r435-disclosed-registered-red`; every other outcome STOP UP with the receipt); the Linux `OverallResultsCases` cells == B's (COUNT-GATE, Linux half).

<!-- RUN: task-4 (rev0 DRAFT — materialized in rev1 from the R-4.50 task-6 runner + the strace lines) -->

### Task 5 — fence proofs at H; the census of record at the BRANCH HEAD (population produced, classified, pinned); the IMPL return

- [ ] **Step 1: V-LS proofs** — `git diff --numstat B H` == the four paths (V-LS-1); `git diff B H -- src/adapters/adapter.hpp src/adapters/secure_io.* harness .github CMakeLists.txt CMakePresets.json` EMPTY; the sqlite lines (`thread_updates`, `db_updated_at`, `SELECT id, updated_at FROM threads`) byte-identical (V-LS-3); the discover bodies byte-identical; `has_terminal_tail_record` / `newest_rollout_timestamp` / `apply_torn_tail_rule` call sites still take the full text (V-LS-4 — grep-proven by line); the `no_cwd_record` / `SessionIdWithoutId` producers unchanged (S-LS-3).
- [ ] **Step 2: the census at the branch head** — the tree arm `git grep -n -E <alternation> "$H" -- .` reduced to `path:line` in `git grep`'s own order; the history arm `git rev-list "$H" | xargs git grep -l -E <alternation>` reduced with `LC_ALL=C sort -u`; the raw outputs under `$EVID/census-raw/` (EXCLUDED from the record); the reduced files CLASSIFIED by token identity against the one synthetic fixture token (class A product fixture / B fixture copy / C English-word false positive / anything else = STOP UP) → `census-tree-H.txt`, `census-history-H.txt`, `census-classes-H.txt` — the WRITTEN population for the vehicle and the seed of the merge packet's population file; the four new test SECTIONs must add NO location (the test bodies carry no credential-shaped string — proven by the scan).
- [ ] **Step 3: the IMPL return TO the pair Planner** — the receipts named; no push yet.

<!-- RUN: task-5 (rev0 DRAFT — materialized in rev1) -->

### Task 6 — the vehicle (ONLY after the pair Planner's verification of the Task 5 return + m-2's byte review at H through master with no red + the pair Planner's relay addressed to the implementer): push the branch, open the PR

- [ ] **Step 1: preconditions** — `HEAD` == H; `H^` == B; `remote-branch-before` EMPTY for `intg/r449-line1-selection`; `gh repo view` PRIVATE; no pre-push hook; the census deltas of Task 5 EMPTY against the written population; the shell recorded.
- [ ] **Step 2: ONE push** — `git push --dry-run --no-tags origin intg/r449-line1-selection` then the one attempt; class recorded; `remote-branch-after` == H or STOP.
- [ ] **Step 3: the PR** — `pr-body.md` from the record (the fence pin, the plan pin, B, H, the four-path numstat, LEG 1/2/3 receipts by name, the census population by class counts, m-2's review relay path, "the PR is the vehicle; the evidence of record is local" sentence, no red remote CI cited); `gh pr create --base main --head intg/r449-line1-selection`; no label, no reviewer request, no draft toggling, no comment.

<!-- RUN: task-6 (rev0 DRAFT — materialized in rev1 from the R-4.50 task-8 runner) -->

### Task 7 — FINALIZE the tracked record `results/r449-<token>/` (the evidence-of-record SET = the home MINUS the declared SCRATCH: `work/`, `census-raw/`, the finalizer's own receipts), manifest, the SITREP UP

- [ ] as R-4.50 Task 9 with `finalize.py`'s extended SCRATCH; the pair Planner commits the record path-scoped, no trailer.

<!-- RUN: task-7 (rev0 DRAFT — materialized in rev1 from the R-4.50 task-9 runner) -->

## Instruments (BLOCKs)

**`linux-container.sh`** (the parity container; the R-4.50 block with the branch name and `strace`):

<!-- BLOCK: linux-container.sh -->
```bash
#!/usr/bin/env bash
# linux-container.sh <expected-head> <label P|C|H> — Phases R / T / S inside ubuntu:24.04 (linux/amd64, --init); /llvm-mirror and /repo-ro read-only, /evidence writable.
# The container exits 0 ONLY IF Phase R, T and S all exited 0 AND the payload/copy-out receipts wrote and copied; the ctest rc is carried as DATA by Phase S.
set -u
WORK_ROOT=/work
REPO_ROOT=/work/repo
OUT=/work/out
LEDGER="$OUT/linux-ledger.txt"
EXPECTED=${1-}
LABEL=${2-}
STOP() { printf 'STOP-linux-container-%s line=%s\n' "$LABEL" "${BASH_LINENO[0]}" >&2; exit 1; }
finalize_container() {
  payload_rc=$?
  trap - EXIT
  payload_receipt_rc=0
  printf 'container_payload_rc=%s\n' "$payload_rc" > "$OUT/container-payload.rc" || payload_receipt_rc=$?
  copy_out_rc=0
  cp -p "$OUT"/* "/evidence/$LABEL/" || copy_out_rc=$?
  copy_receipt_rc=0
  printf 'copy_out_rc=%s payload_receipt_rc=%s\n' "$copy_out_rc" "$payload_receipt_rc" > "$OUT/container-copy-out.rc" || copy_receipt_rc=$?
  final_receipt_copy_rc=0
  cp -p "$OUT/container-copy-out.rc" "/evidence/$LABEL/container-copy-out.rc" || final_receipt_copy_rc=$?
  if [ "$payload_rc" -ne 0 ] || [ "$payload_receipt_rc" -ne 0 ] || [ "$copy_out_rc" -ne 0 ] || [ "$copy_receipt_rc" -ne 0 ] || [ "$final_receipt_copy_rc" -ne 0 ]; then
    exit 1
  fi
  exit 0
}
[ -n "$EXPECTED" ] || STOP
case "$LABEL" in P|C|H|B) ;; *) STOP;; esac
[ -d "/evidence/$LABEL" ] && [ -w "/evidence/$LABEL" ] || STOP
work_root_rc=0
mkdir -p "$OUT" || work_root_rc=$?
[ "$work_root_rc" -eq 0 ] && [ -d "$OUT" ] || STOP
ledger_create_rc=0
: > "$LEDGER" || ledger_create_rc=$?
[ "$ledger_create_rc" -eq 0 ] && [ -f "$LEDGER" ] || STOP
trap finalize_container EXIT
phase_r_base=0
apt-get update > "$OUT/phase-R-base.log" 2>&1 && apt-get install -y --no-install-recommends ca-certificates git g++ make cmake strace python3 python3-venv python3-pip libsqlite3-dev binutils zstd openssh-client >> "$OUT/phase-R-base.log" 2>&1 || phase_r_base=$?
phase_r_base_record_rc=0
printf 'phase_R_base_provision_rc=%s\n' "$phase_r_base" >> "$LEDGER" || phase_r_base_record_rc=$?
[ "$phase_r_base_record_rc" -eq 0 ] || STOP
[ "$phase_r_base" -eq 0 ] || STOP
phase_r_assets_fn() {
  LLVM_TIDY_VERSION='1:22.1.8~++20260613092238+e80beda6e255-1~exp1~20260613092253.78'
  while read -r _ expected_package asset; do
    packaged_name=$(dpkg-deb --field "/llvm-mirror/$asset" Package) || return 11
    packaged_version=$(dpkg-deb --field "/llvm-mirror/$asset" Version) || return 12
    packaged_arch=$(dpkg-deb --field "/llvm-mirror/$asset" Architecture) || return 13
    [ "$packaged_name" = "$expected_package" ] || return 14
    [ "$packaged_version" = "$LLVM_TIDY_VERSION" ] || return 15
    [ "$packaged_arch" = amd64 ] || return 16
  done < /llvm-mirror/MANIFEST
  set -- /llvm-mirror/*.deb
  [ "$#" -eq 8 ] || return 18
  apt-get install -y --no-install-recommends /llvm-mirror/*.deb || return 19
  while read -r _ package _; do
    installed_package_version=$(dpkg-query --show --showformat='${Version}' "$package") || return 20
    [ "$installed_package_version" = "$LLVM_TIDY_VERSION" ] || return 21
  done < /llvm-mirror/MANIFEST
  installed_version=$(dpkg-query --show --showformat='${Version}' clang-tidy-22) || return 22
  [ "$installed_version" = "$LLVM_TIDY_VERSION" ] || return 23
  clang-tidy-22 --version > "$OUT/clang-tidy-version.txt" || return 24
  [ -s "$OUT/clang-tidy-version.txt" ] || return 25
  observed_major=$(sed -nE 's/.*LLVM version ([0-9]+).*/\1/p' "$OUT/clang-tidy-version.txt") || return 26
  [ "$observed_major" = 22 ] || return 27
}
phase_r_assets=0
phase_r_assets_fn > "$OUT/phase-R-assets.log" 2>&1 || phase_r_assets=$?
phase_r_assets_record_rc=0
printf 'phase_R_asset_provision_rc=%s\n' "$phase_r_assets" >> "$LEDGER" || phase_r_assets_record_rc=$?
[ "$phase_r_assets_record_rc" -eq 0 ] || STOP
[ "$phase_r_assets" -eq 0 ] || STOP
phase_t_transition_fn() {
  groupadd -g 1001 suite || return 31
  useradd -m -u 1001 -g 1001 suite || return 32
  git config --global --add safe.directory /repo-ro || return 33
  git clone --no-hardlinks --branch intg/r449-line1-selection /repo-ro "$REPO_ROOT" || return 34
  git -C "$REPO_ROOT" checkout -q --detach "$EXPECTED" || return 35
  observed_head=$(git -C "$REPO_ROOT" rev-parse HEAD) || return 36
  printf 'expected=%s observed=%s\n' "$EXPECTED" "$observed_head" > "$OUT/linux-run-head-receipt.txt" || return 37
  [ -s "$OUT/linux-run-head-receipt.txt" ] || return 38
  [ "$observed_head" = "$EXPECTED" ] || return 39
  cp /evidence/linux-suite.sh "$REPO_ROOT/linux-suite.sh" || return 40
  cp /evidence/observer-unset-names.txt "$REPO_ROOT/observer-unset-names.txt" || return 41
  chown -R 1001:1001 "$REPO_ROOT" "$OUT" || return 42
  mkdir -p /mnt/c/tmp || return 43
  chown -R 1001:1001 /mnt/c || return 44
  runuser -u suite -- test -w /mnt/c/tmp || return 45
}
phase_t_transition=0
phase_t_transition_fn > "$OUT/phase-T-transition.log" 2>&1 || phase_t_transition=$?
phase_t_record_rc=0
printf 'phase_T_transition_fixture_rc=%s\n' "$phase_t_transition" >> "$LEDGER" || phase_t_record_rc=$?
[ "$phase_t_record_rc" -eq 0 ] || STOP
[ "$phase_t_transition" -eq 0 ] || STOP
phase_s_suite=0
runuser -u suite -- bash "$REPO_ROOT/linux-suite.sh" "$REPO_ROOT" "$OUT" "$LABEL" > "$OUT/phase-S-suite.log" 2>&1 || phase_s_suite=$?
phase_s_record_rc=0
printf 'phase_S_suite_rc=%s\n' "$phase_s_suite" >> "$LEDGER" || phase_s_record_rc=$?
[ "$phase_s_record_rc" -eq 0 ] || STOP
[ "$phase_s_suite" -eq 0 ] || STOP
printf 'LINUX_FOUR_PHASE_COMPLETE %s=%s\n' "$LABEL" "$EXPECTED"
exit 0
```

**`linux-suite.sh`** (unchanged from R-4.50 rev19):

<!-- BLOCK: linux-suite.sh -->
```bash
#!/usr/bin/env bash
# linux-suite.sh <repo-root> <out> <label P|C|H> — Phase S as the suite user: nofile raise, venv, configure, build, the name-free proof, the five -r xml
# producers, the workflow-equivalent ctest run. EVERY status is recorded in <out>/linux-suite-ledger.txt as <name>=<rc>; the 26 REQUIRED statuses
# decide suite_aggregate_rc (0 iff all 0); the ctest rc (ctest_<label>_producer_rc) is DATA — recorded, written bare to ctest-linux-<label>.rc, EXCLUDED
# from the aggregate. The script exits with the aggregate (a required red exits nonzero; a ctest red alone exits 0 and reaches the caller's bar).
set -u
REPO_ROOT=${1-}
OUT=${2-}
LABEL=${3-}
STOP() { printf 'STOP-linux-suite-%s line=%s\n' "$LABEL" "${BASH_LINENO[0]}" >&2; exit 1; }
[ "$REPO_ROOT" = /work/repo ] || STOP
[ "$OUT" = /work/out ] || STOP
case "$LABEL" in P|C|H|B) ;; *) STOP;; esac
cd "$REPO_ROOT" || STOP
[ -d "$OUT" ] && [ -w "$OUT" ] || STOP
SUITE_LEDGER="$OUT/linux-suite-ledger.txt"
ledger_create_rc=0
: > "$SUITE_LEDGER" || ledger_create_rc=$?
[ "$ledger_create_rc" -eq 0 ] && [ -f "$SUITE_LEDGER" ] || STOP
ledger_write_failed=0
record_status() {
  printf '%s=%s\n' "$1" "$2" >> "$SUITE_LEDGER" || ledger_write_failed=1
}
producers_red=0
run_binary() {
  binary=$1
  binary_rc=0
  "./build/ci/$binary" -r xml > "$OUT/$binary-linux.xml" 2> "$OUT/$binary-linux.stderr" || binary_rc=$?
  record_status "${binary}_producer_rc" "$binary_rc"
  binary_xml_nonempty_rc=1
  [ -s "$OUT/$binary-linux.xml" ] && binary_xml_nonempty_rc=0
  record_status "${binary}_xml_nonempty_rc" "$binary_xml_nonempty_rc"
  [ "$binary_rc" -eq 0 ] && [ "$binary_xml_nonempty_rc" -eq 0 ] || producers_red=1
}
hard_limit_rc=0
HARD_LIMIT=$(ulimit -Hn) || hard_limit_rc=$?
record_status nofile_hard_read_rc "$hard_limit_rc"
nofile_raise_rc=125
if [ "$hard_limit_rc" -eq 0 ] && [ -n "$HARD_LIMIT" ]; then
  nofile_raise_rc=0
  ulimit -Sn "$HARD_LIMIT" || nofile_raise_rc=$?
fi
record_status nofile_raise_rc "$nofile_raise_rc"
soft_limit_rc=0
SOFT_LIMIT=$(ulimit -Sn) || soft_limit_rc=$?
record_status nofile_soft_read_rc "$soft_limit_rc"
nofile_equal_rc=1
if [ "$hard_limit_rc" -eq 0 ] && [ "$soft_limit_rc" -eq 0 ] && [ -n "$HARD_LIMIT" ] && [ "$SOFT_LIMIT" = "$HARD_LIMIT" ]; then
  nofile_equal_rc=0
fi
record_status nofile_soft_equals_hard_rc "$nofile_equal_rc"
nofile_receipt_rc=0
printf 'soft=%s hard=%s\n' "${SOFT_LIMIT-UNREADABLE}" "${HARD_LIMIT-UNREADABLE}" > "$OUT/linux-nofile.txt" || nofile_receipt_rc=$?
record_status nofile_receipt_write_rc "$nofile_receipt_rc"
venv_rc=0
python3 -m venv .venv-harness > "$OUT/linux-venv.log" 2>&1 || venv_rc=$?
record_status venv_rc "$venv_rc"
requirements_rc=0
.venv-harness/bin/python -m pip install -r harness/requirements.lock > "$OUT/linux-requirements.log" 2>&1 || requirements_rc=$?
record_status requirements_rc "$requirements_rc"
configure_rc=0
cmake --preset ci -DBIVHARNESS_REQUIRE_CLANG_TIDY=ON > "$OUT/linux-configure.log" 2>&1 || configure_rc=$?
record_status configure_rc "$configure_rc"
build_rc=0
cmake --build --preset ci > "$OUT/linux-build.log" 2>&1 || build_rc=$?
record_status build_rc "$build_rc"
name_proof_create_rc=0
: > "$OUT/linux-observer-name-proof.txt" || name_proof_create_rc=$?
record_status observer_name_proof_create_rc "$name_proof_create_rc"
observer_input_rc=0
[ -s "$REPO_ROOT/observer-unset-names.txt" ] || observer_input_rc=1
record_status observer_name_input_nonempty_rc "$observer_input_rc"
observer_name_present_rc=0
observer_name_proof_write_rc=0
if [ "$name_proof_create_rc" -eq 0 ] && [ "$observer_input_rc" -eq 0 ]; then
  while read -r observer_name; do
    if [ -z "$observer_name" ]; then
      observer_name_present_rc=1
      continue
    fi
    if printenv "$observer_name" > /dev/null; then
      printf '%s present\n' "$observer_name" >> "$OUT/linux-observer-name-proof.txt" || observer_name_proof_write_rc=$?
      observer_name_present_rc=1
    else
      printf '%s absent\n' "$observer_name" >> "$OUT/linux-observer-name-proof.txt" || observer_name_proof_write_rc=$?
    fi
  done < "$REPO_ROOT/observer-unset-names.txt"
fi
record_status observer_name_present_rc "$observer_name_present_rc"
record_status observer_name_proof_write_rc "$observer_name_proof_write_rc"
observer_name_proof_nonempty_rc=1
[ -s "$OUT/linux-observer-name-proof.txt" ] && observer_name_proof_nonempty_rc=0
record_status observer_name_proof_nonempty_rc "$observer_name_proof_nonempty_rc"
measurement_missing=0
ctest_rc=125
ctest_log_nonempty_rc=1
ctest_receipt_rc=125
if [ "$name_proof_create_rc" -eq 0 ] && [ "$observer_input_rc" -eq 0 ] && [ "$observer_name_present_rc" -eq 0 ] && [ "$observer_name_proof_write_rc" -eq 0 ] && [ "$observer_name_proof_nonempty_rc" -eq 0 ] && [ "$configure_rc" -eq 0 ] && [ "$build_rc" -eq 0 ]; then
  run_binary biv_subprocess_tests
  run_binary biv_repo_git_tests
  run_binary biv_repo_engine_tests
  run_binary biv_tests
  run_binary biv_probe_tests
  ctest_rc=0
  ctest --preset ci --output-junit "$OUT/ctest-linux-$LABEL.junit.xml" --output-on-failure --test-output-size-passed 50000000 --test-output-size-failed 50000000 > "$OUT/ctest-linux-$LABEL.log" 2>&1 || ctest_rc=$?
  record_status "ctest_${LABEL}_producer_rc" "$ctest_rc"
  ctest_log_nonempty_rc=1
  [ -s "$OUT/ctest-linux-$LABEL.log" ] && ctest_log_nonempty_rc=0
  record_status "ctest_${LABEL}_log_nonempty_rc" "$ctest_log_nonempty_rc"
  ctest_receipt_rc=0
  printf '%s\n' "$ctest_rc" > "$OUT/ctest-linux-$LABEL.rc" || ctest_receipt_rc=$?
  record_status "ctest_${LABEL}_receipt_write_rc" "$ctest_receipt_rc"
else
  for binary in biv_subprocess_tests biv_repo_git_tests biv_repo_engine_tests biv_tests biv_probe_tests; do
    record_status "${binary}_producer_rc" 125
    record_status "${binary}_xml_nonempty_rc" 1
  done
  record_status "ctest_${LABEL}_producer_rc" 125
  record_status "ctest_${LABEL}_log_nonempty_rc" 1
  record_status "ctest_${LABEL}_receipt_write_rc" 125
  measurement_missing=1
fi
suite_aggregate_rc=0
for required_rc in "$hard_limit_rc" "$nofile_raise_rc" "$soft_limit_rc" "$nofile_equal_rc" "$nofile_receipt_rc" "$venv_rc" "$requirements_rc" "$configure_rc" "$build_rc" "$name_proof_create_rc" "$observer_input_rc" "$observer_name_present_rc" "$observer_name_proof_write_rc" "$observer_name_proof_nonempty_rc" "$measurement_missing" "$producers_red" "$ctest_log_nonempty_rc" "$ctest_receipt_rc"; do
  [ "$required_rc" -eq 0 ] || suite_aggregate_rc=1
done
[ "$producers_red" -eq 0 ] || suite_aggregate_rc=1
[ "$ledger_write_failed" -eq 0 ] || suite_aggregate_rc=1
aggregate_record_rc=0
printf 'suite_aggregate_rc=%s ledger_write_failed=%s\n' "$suite_aggregate_rc" "$ledger_write_failed" >> "$SUITE_LEDGER" || aggregate_record_rc=$?
[ "$aggregate_record_rc" -eq 0 ] || exit 1
exit "$suite_aggregate_rc"
```

**`selftest_summary.py`** (unchanged):

<!-- BLOCK: selftest_summary.py -->
```python
#!/usr/bin/env python3
# selftest_summary.py — the pytest facts of the `harness-selftest` ctest row, read from CTest's JUnit output (rev18; iso rev13 bar).
#   usage: selftest_summary.py <ctest junit xml> <out prefix>
#   writes <prefix>.kv    one `key=value` per line: status=<run|fail|notrun|absent> summary=<parsed|absent> failed=<n> passed=<m>
#                         skipped=<k> population=<n+m+k> names_count=<c>
#          <prefix>.names one failing test per line as `<path>::<name>` (pytest's `FAILED <path>::<name>` short-summary lines, every file), sorted, unique
#   The summary line is pytest's final `==== N failed, M passed, K skipped in T s ====` line (the LAST such line in the testcase's
#   system-out); `summary=parsed` iff that line exists and carries a `passed` count; `failed`/`skipped` default to 0 when absent from it.
#   exit 0 when the XML parsed and the testcase exists (the bar decides on the fields); 2 on a missing/unparseable file or an absent testcase.
import re, sys, xml.etree.ElementTree as ET
def main(argv):
    if len(argv) != 3:
        print("usage: selftest_summary.py <junit.xml> <out-prefix>")
        return 2
    try:
        root = ET.parse(argv[1]).getroot()
    except Exception as e:
        print("BAD-JUNIT: %s" % e)
        return 2
    tc = next((t for t in root.iter("testcase") if t.get("name") == "harness-selftest"), None)
    if tc is None:
        print("TESTCASE-ABSENT: harness-selftest")
        return 2
    so = tc.find("system-out")
    txt = (so.text or "") if so is not None else ""
    status = tc.get("status") or "absent"
    if tc.find("failure") is not None:
        status = "fail"
    lines = [ln for ln in txt.split("\n") if re.match(r"^=+ .* in [0-9.]+s( \([0-9:]+\))? =+\s*$", ln)]
    summary = lines[-1] if lines else ""
    def count(word):
        m = re.search(r"(\d+) " + word + r"\b", summary)
        return int(m.group(1)) if m else 0
    parsed = bool(summary) and re.search(r"\d+ passed\b", summary) is not None
    failed, passed, skipped = (count("failed"), count("passed"), count("skipped")) if parsed else (0, 0, 0)
    names = sorted(set(re.findall(r"^FAILED (\S+::[A-Za-z0-9_\[\]\-]+)", txt, re.M)))  # QUALIFIED path::name, every file — a failure outside test_e3_asserts.py is a name the bar must see
    kv = "status=%s\nsummary=%s\nfailed=%d\npassed=%d\nskipped=%d\npopulation=%d\nnames_count=%d\n" % (
        status, "parsed" if parsed else "absent", failed, passed, skipped, failed + passed + skipped, len(names))
    with open(argv[2] + ".kv", "w", encoding="utf-8") as f:
        f.write(kv)
    with open(argv[2] + ".names", "w", encoding="utf-8") as f:
        f.write("".join(n + "\n" for n in names))
    sys.stdout.write(kv.replace("\n", " ").strip() + "\n")
    return 0
if __name__ == "__main__":
    sys.exit(main(sys.argv))
```

**`finalize.py`** (SCRATCH extended — R-4.53 arm (a)):

<!-- BLOCK: finalize.py -->
```python
#!/usr/bin/env python3
# finalize.py — THE EVIDENCE-OF-RECORD SET and its proof (rev17; master 042340 ruling (2); F5 of 212145)
#   list  <evid>                      print the SET: every regular file under the evidence home, path relative to the home,
#                                     sorted bytewise, EXCLUDING any path whose components include one of the four declared
#                                     scratch classes (rederive-*, llvm22-assets-{P,C,H}.*, __pycache__, stale-ci-macos) and the
#                                     four finalizer controller receipts (runners/task-9.done|.exit, proof-9.tail, plan_blocks.sha256-9)
#   check <evid> <resdir> <manifest>  exit 0 iff SET == TRACKED TREE (every regular file under <resdir> except SHA256SUMS)
#                                     == MANIFEST PATHS, in order and multiplicity; every manifest digest equals the tracked
#                                     file's sha256 recomputed here (hashlib); every tracked file's digest equals its home
#                                     twin's. 5 = a difference (the first ones printed); 2 = usage or an unreadable input.
import hashlib, os, re, sys
SCRATCH = (re.compile(r"^work$"), re.compile(r"^census-raw$"), re.compile(r"^llvm22-assets-[HB]\.[A-Za-z0-9]+$"),
           re.compile(r"^__pycache__$"), re.compile(r"^stale-ci-macos$"))
# the FINALIZER's own controller receipts: written by run-task.sh into the home AFTER the Task 9 runner exits, so they can never
# be in the tree the finalizer proves; excluded here (declared), so a re-check after the run reproduces the same set
FINALIZER_RECEIPTS = frozenset(("runners/task-9.done", "runners/task-9.exit", "runners/proof-9.tail", "runners/plan_blocks.sha256-9"))
def excluded(rel):
    return rel in FINALIZER_RECEIPTS or any(p.match(c) for c in rel.split("/") for p in SCRATCH)
def files(root, skip=()):
    out = []
    for d, _dirs, names in os.walk(root):
        for n in names:
            full = os.path.join(d, n)
            if os.path.islink(full) or not os.path.isfile(full):
                continue
            rel = os.path.relpath(full, root)
            if rel in skip:
                continue
            out.append(rel)
    return sorted(out)
def evidence_set(evid):
    return [r for r in files(evid) if not excluded(r)]
def sha(path):
    h = hashlib.sha256()
    with open(path, "rb") as f:
        for chunk in iter(lambda: f.read(1 << 20), b""):
            h.update(chunk)
    return h.hexdigest()
def main(argv):
    if len(argv) == 3 and argv[1] == "list":
        s = evidence_set(argv[2])
        sys.stdout.write("".join(x + "\n" for x in s))
        return 0 if s else 5
    if len(argv) == 5 and argv[1] == "check":
        evid, res, man = argv[2], argv[3], argv[4]
        s = evidence_set(evid)
        tree = files(res, skip=("SHA256SUMS",))
        rows = []
        for ln in open(man, encoding="utf-8").read().split("\n"):
            if not ln:
                continue
            m = re.match(r"^([0-9a-f]{64})  (?:\./)?(.+)$", ln)
            if not m:
                print("BAD-MANIFEST-ROW: " + ln)
                return 5
            rows.append((m.group(2), m.group(1)))
        mpaths = [p for p, _ in rows]
        bad = 0
        def diff(name, first, second):
            nonlocal bad
            if first != second:
                bad = 1
                sa, sb = set(first), set(second)
                for x in sorted(sa - sb)[:5]:
                    print("%s: only in first: %s" % (name, x))
                for x in sorted(sb - sa)[:5]:
                    print("%s: only in second: %s" % (name, x))
                if sa == sb:
                    print("%s: same members, order or multiplicity differs" % name)
        diff("set-vs-tree", s, tree)
        diff("set-vs-manifest", s, mpaths)
        digests_bad = 0
        for p, dgst in rows:
            full = os.path.join(res, p)
            if not os.path.isfile(full):
                digests_bad += 1
                print("digest: missing in tree " + p)
                continue
            if sha(full) != dgst:
                digests_bad += 1
                print("digest: MISMATCH manifest-vs-tree " + p)
        copies_bad = 0
        for p in s:
            home, tracked = os.path.join(evid, p), os.path.join(res, p)
            if not os.path.isfile(tracked) or sha(home) != sha(tracked):
                copies_bad += 1
                print("copy: home-vs-tree differs or missing " + p)
        print("set=%d tree=%d manifest=%d equal=%s digests=%s copies=%s" % (
            len(s), len(tree), len(rows), "no" if bad else "yes", "ok" if digests_bad == 0 else "bad", "ok" if copies_bad == 0 else "bad"))
        return 0 if (bad == 0 and digests_bad == 0 and copies_bad == 0) else 5
    print("usage: finalize.py list <evid> | check <evid> <resdir> <manifest>")
    return 2
if __name__ == "__main__":
    sys.exit(main(sys.argv))
```

**`synth_store.py`** (rev0 draft):

<!-- BLOCK: synth_store.py -->
```python
#!/usr/bin/env python3
# synth_store.py <work> <seed> — builds the LARGE SYNTHETIC STORE pair for LEG 3 (real-store SCALE, synthetic CONTENT), deterministic
# from <seed>: <work>/codex-home/sessions/YYYY/MM/DD/rollout-*.jsonl (N_CODEX rollouts, line 1 = session_meta with cwd; bodies of
# BODY_CODEX bytes of turn records) and <work>/claude-config/projects/<key>/<uuid>.jsonl (N_CLAUDE transcripts, lines 1-4 = metadata
# records without cwd, line 5 the first cwd-bearing record — the REAL shape, A1 FX-M06; bodies of BODY_CLAUDE bytes). Exactly K of each
# carry cwd == <work>/ws/proj (the SELECTED set); the rest carry an unrelated cwd. Ids are minted from the seed and are NEVER any value of
# the iso witness's POISON_SESSION_IDS (m-3 C-2 rule 1); the store lives INSIDE <work> at a locator value (rule 3); no real host store.
# No credential-shaped string is ever written (the census at the branch head and at the merge head scans this store's tree if committed —
# it is NOT committed: it lives under $EVID/work, excluded from the evidence-of-record set by finalize.py).
import json, os, random, sys, uuid
N_CODEX, N_CLAUDE, K = 1500, 100, 3
BODY_CODEX, BODY_CLAUDE = 256 * 1024, 4 * 1024 * 1024
def main(work, seed):
    rnd = random.Random(seed)
    def uid():
        return str(uuid.UUID(int=rnd.getrandbits(128), version=4))
    ws = os.path.join(work, "ws", "proj"); os.makedirs(ws, exist_ok=True)
    other = os.path.join(work, "elsewhere", "proj")
    selected = {"codex": [], "claude": []}
    codex_days = os.path.join(work, "codex-home", "sessions", "2026", "09", "13"); os.makedirs(codex_days, exist_ok=True)
    for i in range(N_CODEX):
        sid = uid(); cwd = ws if i < K else other
        if i < K: selected["codex"].append(sid)
        meta = {"timestamp": "2026-09-13T00:%02d:%02dZ" % (i // 60 % 60, i % 60), "type": "session_meta",
                "payload": {"id": sid, "session_id": sid, "cwd": cwd, "cli_version": "0.142.5"}}
        turn = {"timestamp": "2026-09-13T00:00:00Z", "type": "response_item", "payload": {"type": "message", "role": "assistant", "content": [{"type": "output_text", "text": "x" * 1000}]}}
        with open(os.path.join(codex_days, "rollout-2026-09-13T00-00-00-%s.jsonl" % sid), "w", encoding="utf-8") as f:
            f.write(json.dumps(meta) + "\n"); line = json.dumps(turn) + "\n"; n = BODY_CODEX // len(line)
            for _ in range(n): f.write(line)
    key = "-" + ws.strip("/").replace("/", "-"); proj = os.path.join(work, "claude-config", "projects", key); os.makedirs(proj, exist_ok=True)
    otherkey = "-" + other.strip("/").replace("/", "-"); oproj = os.path.join(work, "claude-config", "projects", otherkey); os.makedirs(oproj, exist_ok=True)
    for i in range(N_CLAUDE):
        sid = uid(); cwd = ws if i < K else other; pdir = proj if i < K else oproj
        if i < K: selected["claude"].append(sid)
        head = [{"type": "last-prompt", "sessionId": sid, "lastPrompt": "p"}, {"type": "mode", "sessionId": sid, "mode": "default"},
                {"type": "permission-mode", "sessionId": sid, "permissionMode": "default"}, {"type": "bridge-session", "sessionId": sid, "bridgeSessionId": uid()},
                {"type": "user", "cwd": cwd, "sessionId": sid, "version": "2.1.202", "uuid": uid(), "parentUuid": None, "message": {"role": "user", "content": "hi"}}]
        body = {"type": "assistant", "cwd": cwd, "sessionId": sid, "uuid": "u", "parentUuid": "p", "message": {"role": "assistant", "content": [{"type": "text", "text": "y" * 1000}]}}
        with open(os.path.join(pdir, sid + ".jsonl"), "w", encoding="utf-8") as f:
            for r in head: f.write(json.dumps(r) + "\n")
            line = json.dumps(body) + "\n"; n = BODY_CLAUDE // len(line)
            for _ in range(n): f.write(line)
    with open(os.path.join(work, "synth-manifest.json"), "w", encoding="utf-8") as f:
        json.dump({"seed": seed, "n_codex": N_CODEX, "n_claude": N_CLAUDE, "k": K, "body_codex": BODY_CODEX, "body_claude": BODY_CLAUDE, "selected": selected, "ws": ws}, f, indent=1, sort_keys=True)
    print("synth ok")
if __name__ == "__main__":
    main(sys.argv[1], int(sys.argv[2]))
```

**`membership.py`** (rev0 draft):

<!-- BLOCK: membership.py -->
```python
#!/usr/bin/env python3
# membership.py <image.bvpk> <out.json> — extracts manifest.json from a biv image (a zstd frame around a ustar/PAX tar; bsdtar reads zstd
# in-process on macOS; on Linux the zstd binary is required) and writes the NORMALIZED selected set: per agent the sorted list of
# (original_session_ids, original_path, normalized_path_key, artifacts, children, live_at_pack, agent_version_at_pack, provenance) —
# every field of the manifest's agent_sessions entries, so LEG 3 compares WHOLE RECORDS, not only membership. Sorted by (agent, ids).
import json, subprocess, sys
def main(image, out):
    raw = subprocess.run(["bsdtar", "-xOf", image, "manifest.json"], capture_output=True, check=True).stdout
    m = json.loads(raw)
    rows = sorted(m.get("agent_sessions", []), key=lambda e: (e.get("agent", ""), json.dumps(e.get("original_session_ids", {}), sort_keys=True)))
    keep = ("agent", "original_session_ids", "original_path", "normalized_path_key", "normalization_scheme", "path_flavor", "artifacts", "children", "live_at_pack", "agent_version_at_pack", "provenance")
    norm = [{k: e.get(k) for k in keep} for e in rows]
    with open(out, "w", encoding="utf-8") as f:
        json.dump({"count": len(norm), "sessions": norm}, f, indent=1, sort_keys=True)
    print("membership rows=%d" % len(norm))
if __name__ == "__main__":
    main(sys.argv[1], sys.argv[2])
```

**`strace_bytes.py`** (rev0 draft):

<!-- BLOCK: strace_bytes.py -->
```python
#!/usr/bin/env python3
# strace_bytes.py <strace.log> <store-root-prefix> <out.txt> — LEG 1 reducer: from `strace -f -e trace=openat,read,pread64 -o <log>`
# output, maps fds to paths (openat return values, per pid) and sums the bytes returned by read/pread64 per PATH under <store-root-prefix>.
# Writes `path<TAB>bytes_read<TAB>file_size` sorted by path (LC_ALL=C order), no content. A non-selected store file must show
# bytes_read < file_size (the head-bounded read); a selected one bytes_read >= file_size (the full read; a source may be streamed twice).
import os, re, sys
OPEN = re.compile(r'^(?:(\d+)\s+)?openat\(.*?"([^"]+)".*\)\s*=\s*(\d+)')
READ = re.compile(r'^(?:(\d+)\s+)?p?read6?4?\((\d+),.*\)\s*=\s*(\d+)')
CLOSE = re.compile(r'^(?:(\d+)\s+)?close\((\d+)\)')
def main(log, prefix, out):
    fds = {}; total = {}
    for line in open(log, encoding="utf-8", errors="replace"):
        m = OPEN.match(line)
        if m:
            fds[(m.group(1), m.group(3))] = m.group(2); continue
        m = READ.match(line)
        if m:
            path = fds.get((m.group(1), m.group(2)))
            if path and path.startswith(prefix):
                total[path] = total.get(path, 0) + int(m.group(3))
            continue
        m = CLOSE.match(line)
        if m:
            fds.pop((m.group(1), m.group(2)), None)
    with open(out, "w", encoding="utf-8") as f:
        for path in sorted(total, key=lambda p: p.encode()):
            size = os.path.getsize(path) if os.path.exists(path) else -1
            f.write("%s\t%d\t%d\n" % (path, total[path], size))
    print("files=%d" % len(total))
if __name__ == "__main__":
    main(sys.argv[1], sys.argv[2], sys.argv[3])
```

**`head_reader_claude.py`** (rev0 draft — compile-checked in a scratch clone at B; the receipt in rev1):

<!-- BLOCK: head_reader_claude.py -->
```python
#!/usr/bin/env python3
# head_reader_claude.py <claude_code.cpp> — R-4.49 claude side (rev0 DRAFT patcher; every anchor asserted EXACTLY ONCE at the base 4cf135ee bytes;
# any other count = STOP). (1) inspect_transcript's per-line body becomes absorb_transcript_line (same fields, same first-seen rule, same exit
# condition cwd+sessionId+version); inspect_transcript keeps its signature and semantics for the install-side callers. (2) a STREAMING head
# reader over ArtifactSource::stream that stops at the end of the first completing line (a sentinel error aborts the stream — the sink
# contract of secure_io::ReadHandle::stream — and is consumed here; a real stream error propagates). (3) collect uses the streaming reader;
# the whole-file source_text before the cwd filter is REMOVED; the full reads for selected sessions (artifact source; apply_torn_tail_rule) stay.
import sys
p = sys.argv[1]; t = open(p, encoding="utf-8").read()
def rep(old, new):
    global t
    assert t.count(old) == 1, ("anchor count %d: %s" % (t.count(old), old[:80]))
    t = t.replace(old, new)
OLD_INSPECT = '''TranscriptFacts inspect_transcript(const std::string_view transcript) {
  TranscriptFacts facts;
  std::istringstream input{std::string{transcript}};
  std::string line;
  while (std::getline(input, line)) {
    simdjson::padded_string padded{line};
    simdjson::dom::parser parser;
    auto object = parse_json_object(parser, padded);
    if (!object.has_value()) {
      continue;
    }
    if (!facts.session_id.has_value()) {
      facts.session_id = object_string(*object, "sessionId");
    }
    if (!facts.version.has_value()) {
      facts.version = object_string(*object, "version");
    }
    if (!facts.cwd.has_value()) {
      facts.cwd = object_string(*object, "cwd");
    }
    if (facts.cwd.has_value() && facts.session_id.has_value() &&
        facts.version.has_value()) {
      break;
    }
  }
  return facts;
}
'''
NEW_INSPECT = '''// R-4.49 (sealed A1 §A1 over c1 §3; fence 142000 §2): ONE line of a transcript absorbed into the head facts — the same
// first-seen rule and the same completion condition inspect_transcript has always used (cwd + sessionId + version).
// Returns true when the head facts are complete after this line.
bool absorb_transcript_line(TranscriptFacts& facts, const std::string_view line) {
  simdjson::padded_string padded{line};
  simdjson::dom::parser parser;
  auto object = parse_json_object(parser, padded);
  if (!object.has_value()) {
    return false;
  }
  if (!facts.session_id.has_value()) {
    facts.session_id = object_string(*object, "sessionId");
  }
  if (!facts.version.has_value()) {
    facts.version = object_string(*object, "version");
  }
  if (!facts.cwd.has_value()) {
    facts.cwd = object_string(*object, "cwd");
  }
  return facts.cwd.has_value() && facts.session_id.has_value() && facts.version.has_value();
}

TranscriptFacts inspect_transcript(const std::string_view transcript) {
  TranscriptFacts facts;
  std::istringstream input{std::string{transcript}};
  std::string line;
  while (std::getline(input, line)) {
    if (absorb_transcript_line(facts, line)) {
      break;
    }
  }
  return facts;
}

// R-4.49: the HEAD-BOUNDED read for candidacy — the source is STREAMED (secure_io::ReadHandle::stream, 8 KiB chunks) and the
// stream is STOPPED at the end of the first line that completes the head facts; bytes after that line are never read for a
// transcript that is not selected. A transcript with no completing line is read to EOF (the whole file — A1 §A1: no cwd
// anywhere → excluded and reported). The stop is signalled to the stream as a sentinel error and consumed here; a real
// stream error propagates. Line framing is std::getline's: '\\n'-terminated lines, a trailing unterminated line counted once.
constexpr std::string_view kHeadCompleteSentinel = "r449-head-complete";

expected<TranscriptFacts> inspect_transcript_head(const SessionRecord::ArtifactSource& source) {
  TranscriptFacts facts;
  std::string carry;
  bool complete = false;
  auto read = source.stream([&](const std::span<const std::byte> chunk) -> expected<void> {
    carry.append(reinterpret_cast<const char*>(chunk.data()), chunk.size());
    std::size_t start = 0;
    for (auto newline = carry.find('\\n', start); newline != std::string::npos;
         newline = carry.find('\\n', start)) {
      const std::string_view line{carry.data() + start, newline - start};
      start = newline + 1;
      if (absorb_transcript_line(facts, line)) {
        complete = true;
        break;
      }
    }
    carry.erase(0, start);
    if (complete) {
      return std::unexpected(BivError{ErrKind::InternalError, {}, std::string{kHeadCompleteSentinel}});
    }
    return {};
  });
  if (!read) {
    if (complete && read.error().detail == kHeadCompleteSentinel) {
      return facts;
    }
    return std::unexpected(read.error());
  }
  if (!carry.empty()) {
    absorb_transcript_line(facts, carry);
  }
  return facts;
}
'''
rep(OLD_INSPECT, NEW_INSPECT)
OLD_COLLECT = '''            auto main_source = open_artifact_source(entry.path());
            if (!main_source) {
              return std::unexpected(main_source.error());
            }
            auto main_text = source_text(*main_source);
            if (!main_text) {
              return std::unexpected(main_text.error());
            }
            auto facts = inspect_transcript(*main_text);
            if (!facts.cwd.has_value()) {'''
NEW_COLLECT = '''            auto main_source = open_artifact_source(entry.path());
            if (!main_source) {
              return std::unexpected(main_source.error());
            }
            // R-4.49: candidacy from the HEAD only (streamed, stopped at the completing line); the full read of a
            // SELECTED transcript happens where it always did (the artifact source; apply_torn_tail_rule).
            auto head = inspect_transcript_head(*main_source);
            if (!head) {
              return std::unexpected(head.error());
            }
            auto facts = std::move(*head);
            if (!facts.cwd.has_value()) {'''
rep(OLD_COLLECT, NEW_COLLECT)
open(p, "w", encoding="utf-8").write(t)
print("claude_code.cpp patched (rev0 draft)")
```

**`head_reader_codex.py`** (rev0 draft — compile-checked in a scratch clone at B; the receipt in rev1):

<!-- BLOCK: head_reader_codex.py -->
```python
#!/usr/bin/env python3
# head_reader_codex.py <codex.cpp> — R-4.49 codex side (rev0 DRAFT patcher; anchors asserted EXACTLY ONCE at the base 4cf135ee bytes).
# (1) inspect_rollout_head's per-line body becomes absorb_rollout_line (the FIRST session_meta record completes the head; every other
# line is skipped — the same rule); inspect_rollout_head keeps its signature and semantics. (2) a streaming head reader over
# ArtifactSource::stream (same sentinel shape as the claude side). (3) collect reads the head first; the FULL read (source_text) moves
# BELOW the cwd filter so it happens only for in-root candidates, whose tail facts (has_terminal_tail_record, newest_rollout_timestamp)
# keep their full-text inputs — V-LS-4.
import sys
p = sys.argv[1]; t = open(p, encoding="utf-8").read()
def rep(old, new):
    global t
    assert t.count(old) == 1, ("anchor count %d: %s" % (t.count(old), old[:80]))
    t = t.replace(old, new)
OLD_HEAD = '''RolloutFacts inspect_rollout_head(const std::string_view rollout) {
  RolloutFacts facts;
  std::istringstream input{std::string{rollout}};
  std::string line;
  while (std::getline(input, line)) {
    simdjson::padded_string padded{line};
    simdjson::dom::parser parser;
    auto object = parse_json_object(parser, padded);
    if (!object) {
      continue;
    }
    auto type = object_string(*object, "type");
    if (!type || *type != "session_meta") {
      continue;
    }
    auto payload = object_object(*object, "payload");
    if (!payload) {
      continue;
    }
    if (!facts.id.has_value()) {
      facts.id = object_string(*payload, "id");
    }
    if (!facts.session_id.has_value()) facts.session_id = object_string(*payload, "session_id");
    if (!facts.cwd.has_value()) {
      facts.cwd = object_string(*payload, "cwd");
    }
    if (!facts.cli_version.has_value()) {
      facts.cli_version = object_string(*payload, "cli_version");
    }
    if (const auto direct = object_string(*payload, "parent_thread_id");
        direct.has_value()) {
      facts.parent_ids.push_back(*direct);
    }
    if (const auto nested = nested_parent_id(*payload); nested.has_value()) {
      facts.parent_ids.push_back(*nested);
    }
    if (!facts.parent_ids.empty()) {
      facts.parent_id = facts.parent_ids.front();
    }
    return facts;
  }
  return facts;
}
'''
NEW_HEAD = '''// R-4.49 (sealed c1 §4; fence 142000 §2): ONE rollout line absorbed into the head facts — the FIRST session_meta record
// completes the head (exactly the rule inspect_rollout_head has always applied); any other line is skipped.
bool absorb_rollout_line(RolloutFacts& facts, const std::string_view line) {
  simdjson::padded_string padded{line};
  simdjson::dom::parser parser;
  auto object = parse_json_object(parser, padded);
  if (!object) {
    return false;
  }
  auto type = object_string(*object, "type");
  if (!type || *type != "session_meta") {
    return false;
  }
  auto payload = object_object(*object, "payload");
  if (!payload) {
    return false;
  }
  if (!facts.id.has_value()) {
    facts.id = object_string(*payload, "id");
  }
  if (!facts.session_id.has_value()) facts.session_id = object_string(*payload, "session_id");
  if (!facts.cwd.has_value()) {
    facts.cwd = object_string(*payload, "cwd");
  }
  if (!facts.cli_version.has_value()) {
    facts.cli_version = object_string(*payload, "cli_version");
  }
  if (const auto direct = object_string(*payload, "parent_thread_id");
      direct.has_value()) {
    facts.parent_ids.push_back(*direct);
  }
  if (const auto nested = nested_parent_id(*payload); nested.has_value()) {
    facts.parent_ids.push_back(*nested);
  }
  if (!facts.parent_ids.empty()) {
    facts.parent_id = facts.parent_ids.front();
  }
  return true;
}

RolloutFacts inspect_rollout_head(const std::string_view rollout) {
  RolloutFacts facts;
  std::istringstream input{std::string{rollout}};
  std::string line;
  while (std::getline(input, line)) {
    if (absorb_rollout_line(facts, line)) {
      return facts;
    }
  }
  return facts;
}

// R-4.49: the HEAD-BOUNDED read for candidacy — streamed, stopped at the end of the first session_meta line (observed on the
// evidence host: line 1 of 1,503/1,503 rollouts; at most 22,552 bytes); a rollout with no session_meta record is read to EOF and
// is not a candidate, as today. Sentinel-stop over secure_io::ReadHandle::stream; a real stream error propagates.
constexpr std::string_view kHeadCompleteSentinel = "r449-head-complete";

expected<RolloutFacts> inspect_rollout_head_stream(const SessionRecord::ArtifactSource& source) {
  RolloutFacts facts;
  std::string carry;
  bool complete = false;
  auto read = source.stream([&](const std::span<const std::byte> chunk) -> expected<void> {
    carry.append(reinterpret_cast<const char*>(chunk.data()), chunk.size());
    std::size_t start = 0;
    for (auto newline = carry.find('\\n', start); newline != std::string::npos;
         newline = carry.find('\\n', start)) {
      const std::string_view line{carry.data() + start, newline - start};
      start = newline + 1;
      if (absorb_rollout_line(facts, line)) {
        complete = true;
        break;
      }
    }
    carry.erase(0, start);
    if (complete) {
      return std::unexpected(BivError{ErrKind::InternalError, {}, std::string{kHeadCompleteSentinel}});
    }
    return {};
  });
  if (!read) {
    if (complete && read.error().detail == kHeadCompleteSentinel) {
      return facts;
    }
    return std::unexpected(read.error());
  }
  if (!carry.empty()) {
    absorb_rollout_line(facts, carry);
  }
  return facts;
}
'''
rep(OLD_HEAD, NEW_HEAD)
OLD_COLLECT = '''            auto source = open_artifact_source(path);
            if (!source) {
              return std::unexpected(source.error());
            }
            auto text = source_text(*source);
            if (!text) {
              return std::unexpected(text.error());
            }
            auto facts = inspect_rollout_head(*text);
            const bool in_source_root ='''
NEW_COLLECT = '''            auto source = open_artifact_source(path);
            if (!source) {
              return std::unexpected(source.error());
            }
            // R-4.49: candidacy from the HEAD only; the full read moves below the cwd filter (in-root candidates only).
            auto head = inspect_rollout_head_stream(*source);
            if (!head) {
              return std::unexpected(head.error());
            }
            auto facts = std::move(*head);
            const bool in_source_root ='''
rep(OLD_COLLECT, NEW_COLLECT)
OLD_AFTER = '''            if (!facts.id || !in_source_root) {
              continue;
            }
            const auto mtime = fs::last_write_time(path, ec);'''
NEW_AFTER = '''            if (!facts.id || !in_source_root) {
              continue;
            }
            // R-4.49: the FULL read — for an in-root candidate only (V-LS-4: tail facts from the whole text).
            auto text = source_text(*source);
            if (!text) {
              return std::unexpected(text.error());
            }
            const auto mtime = fs::last_write_time(path, ec);'''
rep(OLD_AFTER, NEW_AFTER)
open(p, "w", encoding="utf-8").write(t)
print("codex.cpp patched (rev0 draft)")
```

## Acceptance criteria (each measured, none inferred)

1. At H: `git diff --numstat B H` == exactly the four touchable paths; every V-LS-1/3/4 grep proof rc 0; no `.hpp`, `secure_io`, discover, workflow, harness, CMake or fixture byte.
2. V-LS-2: `membership-B.json` == `membership-H.json` and `membership-corpus-B.json` == `membership-corpus-H.json` (whole normalized records, rc 0 `diff`); the two collect suites' every existing assertion green at H; the new SECTIONs green.
3. LEG 1 / LEG 2: at H every non-selected file of S read head-only (`bytes_read < file_size`, within one chunk of its completing line's end); every selected file read in full at B and at H; the store total collapsed (the receipt names both totals).
4. LEG 3's cost receipt: the pack wall time on S at B and at H (medians of three), the delta named.
5. COUNT-GATE: the ten `OverallResultsCases` cells at H == B's on both targets.
6. Acceptance of record at H: macOS `ctest --preset ci-macos -E '^safety-hardening$'` rc 0; Linux rc 0 or the iso rev13 (a)–(h) admitted red with the in-token base draw at B; the four container ledgers aggregate 0.
7. The census at the branch head: produced on H's tree and history, classified, no class beyond A/B/C, the four SECTIONs adding no location; the population file written for the vehicle.
8. Cut-point `origin/main..H^` = 0; `H^` == B; the branch pushed with class a; the PR open against `main` with head H; `main` NOT pushed by this plan.
9. m-2's byte review at H returns through master with no red before the vehicle; the four-condition bar, the operator's token and the R-4.52 landing follow in the merge packet.

## Out of scope (an act here is a STOP, not a judgement)

Any discover byte (R-4.50 landed it); any `SessionRecord` / `CollectReport` / `adapter.hpp` byte; any `secure_io` byte; any sqlite use beyond enrichment; any harness / stub / iso-witness byte (m-3's); any workflow byte (the count-gate cells — a `TEST_CASE` count change routes UP); any manifest / pack / open surface; any new head SEMANTICS (the bound and the malformed-head disposition are m-2's — C-1 / C-2); dedupe semantics (c1 §7's mtime clause is executed as today's `better_candidate`, untouched); any release act.

## Anti-half-fix guards

- The head reader's completion condition is IDENTICAL to today's parser exit (claude cwd+sessionId+version; codex the first `session_meta`) — a reader that stops earlier changes record fields, a reader that stops later is not the act; both are red under LEG 3's whole-record comparison.
- A full read that survives ABOVE the cwd filter on either adapter is the act not done (LEG 1 shows it: non-selected `bytes_read == file_size`).
- A tail fact computed from the head text is V-LS-4 red (the grep proofs name the three call sites and their full-text arguments).
- The synthetic store's cwd values, ids and roots are proven against the frozen harness constants (values read, never written); a hit is a STOP, not a rename.
- No evidence-producing pipeline anywhere; every producer's status recorded; every count from a file.
- The census population is PRODUCED on the object scanned, reduced by the exact lines, `LC_ALL=C` — never carried from a previous head; the raw intermediates never enter the record.

## Revision history

- **rev0** — this SKELETON (2026-09-13): the audit's findings as the plan's architecture; the fence verbatim by reference; placeholders [C-1] / [C-2]; the runner protocol and the R-4.50 instruments carried; the two patchers drafted at B's bytes; the RUN blocks to be materialized in rev1 after the reconcile and m-2's words.
