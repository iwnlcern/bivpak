# R-4.49 line-1 selection — Implementation Plan (revision 1 — assembled 2026-09-13; the RUN blocks materialized; C-1/C-2 RESOLVED; not yet filed: the root-mode edge measurement precedes the filing per master `164219`)

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:executing-plans to implement this plan task-by-task, IN DOCUMENT ORDER, through the per-task runner protocol below and nothing else. Steps use checkbox (`- [ ]`) syntax for tracking. Nothing in this document is authority: the implementation token is a separate bare `DISPATCH IMPL` relay from the pair Planner after the exact-hash approve; the branch push and the PR are the R-4.51 clause (2) vehicle; the merge is the operator's condition-4 token; the landing is R-4.52; nothing here releases.

**Revision 1 (2026-09-13).** rev0 (b07125a, the same day) was the skeleton with two placeholders. This revision: (1) **C-1 and C-2 are RULED** by m-2 (`intg-r449-line1-selection-act/DESIGN-m2-planner-20260913-170000.md`, carried down by master `171709`) — THE BOUNDS below bind verbatim; (2) the **reconcile** with the implementer's independent audit `intg-r449/AUDIT-pair-implementer-20260913-165828.md` is recorded (six dispositions, all agree; O-1 FOLDED as a design change: the claude head reader stops at the FIRST cwd-bearing record and the selected transcript's other fields come from today's whole-text parse, so the enrichment fields can never extend a non-selected read; the witness states the two sealed whole-file classes instead of asserting every non-selected file is head-bounded); (3) the four patchers are FINAL and **compile-checked at B's bytes in a disposed scratch clone**: `cmake --preset ci-macos` + build rc 0, `biv_tests -r xml` rc 0 with `OverallResultsCases successes=419 skips=3` (B's macOS cell) and the nine R-4.49 `SECTION`s observed run (receipt `/tmp/r449/scratch-build-receipt-rev1.txt` at the pair Planner's seat; patched digests claude `0e820ab8…`, codex `895d87d4…`, tests `c561e3cd…` / `0f8f3b67…`); (4) the eight RUN blocks are materialized (Tasks 0–7) with the R-4.50 rev22 runners as templates; (5) the fixture-corpus mirror of rev0 Task 1 Step 3 is dropped — the corpus oracle is the two collect suites themselves at B and at H (V-LS-2 over F is what every existing assertion asserts, measured in-token on both targets), and LEG 3's manifest comparison covers S. This artifact is committed on the docs lane; the PLAN relay files after the root-mode measurement of the canonical cross-repo edge is read (structural green ⇒ no waiver; a fired set returns to the operator through master before any byte).

**Goal:** execute the sealed head predicates in the two adapters' collect candidate paths: candidacy is decided from a HEAD-BOUNDED read of each store file (streamed, stopped at the line that completes the predicate — the first cwd-bearing record for claude, the first session_meta record for codex), and the FULL read happens only for selected sessions and their closure descendants — the act changes COST, never MEMBERSHIP (V-LS-2; m-2: selection identity by construction).

**Architecture:** claude — a streaming reader `first_transcript_cwd(source)` over the existing `ArtifactSource::stream` (8 KiB `pread` chunks) frames lines on `'\n'` exactly as `std::getline` does, parses each line with the same `parse_json_object`/`object_string` calls `inspect_transcript` uses, and stops the stream at the end of the first line whose record carries `cwd` by returning a sentinel error the reader consumes (a real stream error propagates); `collect` decides no-cwd / out-of-root from that head cwd and, for an in-root transcript only, runs the whole-file `source_text` + the UNCHANGED `inspect_transcript` (so sessionId/version are today's; the cwd is the head's first-seen value, which `inspect_transcript` reproduces over the same bytes by the same first-seen rule). codex — `inspect_rollout_head`'s per-line body becomes `absorb_rollout_line` (the first `session_meta` completes; every other line skipped; the whole-text parser keeps its signature and semantics), a streaming `inspect_rollout_head_stream` feeds it chunk by chunk with the same sentinel stop, and `collect` reads the head first, keeps the `SessionIdWithoutId` warning on head facts, and moves the whole-file `source_text` BELOW the cwd filter so the tail facts (`has_terminal_tail_record(*text)`, `newest_rollout_timestamp(*text)`) keep their full-text inputs for in-root candidates only. No `secure_io`, discover, shape, sqlite, manifest or harness byte. Witness tests as nine `SECTION`s inside two EXISTING `TEST_CASE`s so the Catch2 case census (`OverallResultsCases`) — the workflow's count-gate cells, OUTSIDE this fence — does not move.

**Tech stack:** C++20, simdjson, Catch2 v3.7.1 (`-r xml`), CMake presets `ci-macos` (host) and `ci` (the Linux parity container: ubuntu-24.04 `linux/amd64` `--init`, nofile soft == hard, `strace` provisioned for LEG 1), the pair's per-task runner protocol, `biv pack <dir> --json` (no consent prompt under `--json`; exit 0 or 2 with `"ok": true`) + `tar -xOf <image> manifest.json` for LEG 3, python3 helpers carried as BLOCKs.

**Spec (the law of this act, cited never retyped):** m-2 fence rev2 `pdc:master/relays/r437-pack-timeout-diagnosis/DESIGN-m2-planner-20260903-144700.md` @ sha256 `f2216ee606a03b0b5b0b7f4562fed52a7349219c28990e6ee3e89b0cc25e8c6f` — §4 preserves `142000` §2 BYTE-FOR-BYTE by reference (TOUCHABLE, V-LS-1..6, S-LS-1..4, the three-leg witness) and consumes m-3's C-2 five rules (`143638`); Master Reviewer approve with VP concurrence `151001`; the operator's grant `r437-operator-scope-ruling/PLAN-operator-20260903-152118.md` ("lets fix both please", grant 2 of 2); **the S-LS-1/S-LS-2 rulings** `intg-r449-line1-selection-act/DESIGN-m2-planner-20260913-170000.md` (m-2.planner; lint OK; bound to the fence pin) carried by master `171709`. Determining sealed text: ADDENDUM-1 §A1/M06 `2026-07-04-ADDENDUM-1-adapter-remediation.md` @ `df523d97f3a54b2311e6f3af93160499cf73021746a347396ee25cb0d8298956` (:29-50 — the claude stream-scan rule; the superseded c1 §3 sentence named; FX-M06's RED leg); c1 `2026-07-02-adapter-contract-and-session-semantics.md` §4 :221 ("candidate rollouts by reading `session_meta.cwd` (line 1)" — the normative object is the session_meta RECORD; the parenthetical records where it sits), §7 :344 ("newest `updated_at`/mtime wins", untouched); locked A12 `2026-08-12-ADDENDUM-12-transitive-collect-and-mono-gate.md` (membership + edges are session_meta facts; full text owed only to selected sessions + closure descendants).

## Global constraints (each line binds every task)

- THE BOUNDS, as RULED (binding verbatim):

```text
C-1 CLAUDE (m-2 `170000`, CONFIRMED): ADDENDUM-1 §A1 governs — stream-scan from the top; the FIRST record carrying a `cwd` field keys the
    session; the scan stops at first hit; a transcript with NO cwd-bearing record anywhere is EXCLUDED and reported per file (`no_cwd_record`,
    warned never silent — the worst case remains a whole-file read, sealed); unparseable lines skipped as today; NEVER a line number, NEVER a
    byte cap. c1 §3:188 "line 1" is A1's named superseded ancestor (the fence's citation defect is m-2's, owned; A1's own FX-M06 RED leg
    refutes line-1 verbatim); NO fence rev, NO addendum.
C-2 CODEX (m-2 `170000`, CONFIRMED): the bound is the FIRST `session_meta` record — identity with today's parser (`inspect_rollout_head`);
    a fixed byte cap is DECLINED as an invented normative constant (S-LS-1's class); the lane's 1,503/1,503 line-1 observation is
    confirmation of shape, not a license to hard-code a position; absence disposition unchanged (no session_meta → not a candidate, silent).
JOINT CONSEQUENCE (m-2's words the plan binds to): both bounds are the predicates today's parsers implement, so SELECTION IDENTITY IS
    PRESERVED BY CONSTRUCTION and the act stays READ-BOUNDING ONLY — whole-file `source_text` reads replaced by reads bounded at the predicate
    hit; FULL reads retained for selected sessions + closure descendants (V-LS-4); sqlite untouched (V-LS-3); V-LS-2's witness anchored to
    bounds that cannot move membership.
```

- TOUCHABLE (V-LS-1): `src/adapters/claude_code/claude_code.cpp` (the collect candidate path :654-671 at B and a new head reader inserted after `inspect_transcript` at :197; `inspect_transcript` itself UNCHANGED) + `src/adapters/codex/codex.cpp` (`inspect_rollout_head` :229-270 refactored over `absorb_rollout_line`, the streaming reader, and the collect candidate path :1273-1290 at B) + `tests/test_adapter_claude_collect.cpp` + `tests/test_adapter_codex_collect.cpp` (SECTIONs only). NO discover byte (the `discover` bodies at claude :570 / codex :1155 lie outside every hunk window Task 5 proves); NO `SessionRecord` / `CollectReport` shape change (`adapter.hpp` untouched); NO `.hpp` byte; NO manifest / pack / open surface (`src/core`, `src/cli` untouched); NO `secure_io` byte; NO sqlite byte (V-LS-3 — the `sqlite3_` / `threads` occurrence counts equal at B and H); NO harness byte (m-3's; S-LS-4); NO workflow byte (the count-gate cells `.github/workflows/s2-harness.yml` are OUTSIDE this fence — see COUNT-GATE); NO new test FILE (a CMake byte); NO fixture byte (`tests/fixtures` untouched).
- VETOES V-LS-1..6 and STOPs S-LS-1..4 (`142000` §2), binding verbatim, with their 2026-09-13 dispositions:

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
        overlong, or unparseable — owner m-2                      → RULED 2026-09-13 (m-2 `170000`, carried by master `171709`): see THE BOUNDS below
S-LS-2  any fact discovered to be REQUIRED for membership or edges that does NOT live in line 1 — no in-lane semantic invention — owner m-2
        → RULED with S-LS-1: the claude membership fact is the FIRST cwd-bearing RECORD (A1 §A1), not line 1 — m-2 owns the fence's citation defect
S-LS-3  any user-visible warning today emitted from full-parse of NON-selected store files: disposition owner m-2, wording m-3
        → audited NONE (`165304`, corroborated `165828`): no_cwd_record needs the whole file scanned and the head reader reads to EOF when no cwd
          appears (sealed); SessionIdWithoutId uses head facts; the enumeration / sqlite warnings are untouched — re-proven by the suites at H
S-LS-4  CROSS-DOMAIN: any harness or witness expectation keyed to read counts or full-read behavior — owner m-3, routed, never patched in-lane
        → dormant by m-3's own C-2 rule 5 (oracles observe identities/provenance/paths/warnings, not read patterns); no harness byte in this act
```

- THE WITNESS, three legs (`142000` §2), executed as EVIDENCE by the runner (no witness leg is a product byte; the Catch2 `SECTION`s carry the corpus-shaped membership cases):

```text
LEG 1  bytes-read-per-store-file BEFORE (B) and AFTER (H), instrumented at the candidate head: `strace -f -s 0 -e trace=open,openat,openat2,read,pread64`
       around `biv pack` inside the Linux parity container (Phase L) at B and at H over the synthetic store S (six classes, per-file manifest
       with each file's predicate-completing byte offset `head_end`); `strace_bytes.py` reduces the trace to path<TAB>bytes_read (no content:
       `-s 0`); `leg12_verdict.py` grades every file of S by its class with the bound NAMED per file:
         selected (K per agent)                          bytes_B >= size AND bytes_H >= size                (full reads retained — V-LS-4)
         non-selected with a completing line             bytes_B >= size AND bytes_H <= ceil(head_end / 8192) * 8192 AND bytes_H < size
         the SEALED whole-file classes                   bytes_B >= size AND bytes_H >= size — claude-no-cwd (A1 §A1: no cwd anywhere → EOF +
                                                         no_cwd_record) and codex-no-meta (no session_meta → EOF, not a candidate); the
                                                         implementer's audit correction (`165828`): the witness must NOT assert that EVERY
                                                         non-selected file is head-bounded — these two classes are read whole by sealed rule
LEG 2  the cwd filter's POSITION ahead of any full read: the class `claude-cwd-no-enrichment` (an out-of-root first cwd record with NO
       sessionId/version, a 4 MiB body that never carries them — the O-1 counterexample) is head-bounded at H exactly like `claude-bulk`; a
       reader that waited for the enrichment fields would read it to EOF (bytes_H == size → VIOLATION). The store-proportional term
       collapses: the TOTAL bytes read over S at H vs at B is printed (ratio) — the registration's ~30 s cell re-measured as LEG 3's timing
LEG 3  membership identity as WHOLE RECORDS: `membership.py` over the manifest.json of the `biv pack` images at B and at H over S — macOS
       (Task 1 / Task 3) and Linux (Phase L, both containers): the normalized agent_sessions records (agent, original_session_ids,
       original_path, normalized_path_key, normalization_scheme, path_flavor, artifacts, children, live_at_pack, agent_version_at_pack,
       provenance) EQUAL — an empty diff or STOP; the no_cwd mention count in the pack JSON equal at B and H; the FIXTURE CORPUS F is the
       membership oracle through the two collect suites (every existing assertion green at B and at H — measured in-token on both targets —
       plus the nine R-4.49 SECTIONs); the pack wall time over S at B vs at H (medians of three) recorded as the act's cost receipt
```

- COUNT-GATE (R-4.38 precedent; R-4.50's Q2 lesson): the workflow pins `OverallResultsCases successes` per binary (biv_tests 419 macOS / 421 Linux at B, read from the bytes by `cells.py`, never typed); a NEW `TEST_CASE` moves the two `biv_tests` cells, which are OUTSIDE this fence → every new test is a `SECTION` inside an EXISTING `TEST_CASE` (claude: "Claude adapter keys membership on the first cwd record"; codex: "X-2 Codex suppresses session_id warnings outside the source root"); Task 2 proves the `TEST_CASE` count per file unchanged (15 / 25); Task 3 (macOS) and Task 4 (Linux) prove by `cellgate.py` that the five binaries' cells at H EQUAL B's literal cells AND B's observed tuples (a difference = STOP UP, V-LS-1 collision, never a transcription in this act); `skipset.py` proves the skip SET unchanged.
- m-3's FIVE FIXTURE-ROOT RULES (`143638` §2; consumed by the fence rev2 §4) bind the instrument: (1) builders reusable by import; ids NEVER a `POISON_SESSION_IDS` value — Task 1 greps every uuid literal of B's `harness/bivharness/scenario.py` against the synthetic manifest (0 hits or STOP); the root is `$EVID/work`, never the iso witness's poison root; (2) FROZEN: the iso spec, `HERMETIC_LOCATORS`, `MANDATORY_PROCESS_LOCATORS`, `POISON_SESSION_IDS`, `POISON_SUBROOTS`, `_isolation_leaks`, `_rp_positive`, `test_store_isolation.py` — any byte a veto (this act touches no harness byte: Task 5's diff over `harness` is EMPTY); (3) the synthetic store lives INSIDE `work` at LOCATOR VALUES (`CODEX_HOME=$EVID/work/codex-home`, `CLAUDE_CONFIG_DIR=$EVID/work/claude-config`, `HOME=$EVID/work/home` with NO `.codex`/`.claude` under it, `TMPDIR=$EVID/work/tmp`), never a real host store; (4) any harness byte routed to m-3 — none needed; (5) S-LS-4 dormant by m-3's own reading.
- OWNER REVIEW: m-2's byte-level V-LS-1..6 review and veto at the candidate sha (m-2.planner rules; m-2.implementer the byte seam), through master, after the Task 5 IMPL return and before the vehicle's Task 6 — Task 6 runs only on the pair Planner's relay addressed to the implementer after that review returns with no red.
- THE VEHICLE AND THE LANDING, with the R-4.50 lessons as TERMS (master `164219` (1)–(6)): (1) Task 0 cuts a FRESH branch `intg/r449-line1-selection` and a FRESH worktree `../bivpak-intg-r449-line1-selection` from the PUBLISHED PIN `4cf135ee97f57021c5fc5fd5343de6f655fb0d24` (re-read from `origin/main` at Task 0; never from lane-local `main`; cut-point count 0 proven) and DISPOSES the retained `-v2` worktree at H' `e8a1128d…` with a receipt (`git worktree remove` after a clean-status check; both branch refs proven unchanged before and after; the remote heads untouched); (2) the CENSUS OF RECORD at the BRANCH HEAD both arms (Task 5): the population PRODUCED by the scan of the exact objects — B's tree/history and H's tree/history in the same token, reduced by the same lines, `LC_ALL=C sort -u` — H's census must EQUAL B's (the act adds no location), and B's census must EQUAL the record of `4cf135ee` (`results/intg-r450-main-head-census-20260913.txt`: 69 tree locations = 3 product fixtures + 64 fixture copies + 2 English-word false positives; 34 history paths — the classification is inherited by equality); paths and line numbers only, the raw matches under `$EVID/census-raw/` EXCLUDED from the record; the synthetic store S is NOT committed and is DISCLOSED on the carrier face; (3) the branch pushed to `origin`, a PULL REQUEST against `main` — clause (2) authorizes it; (4) the PR is the VEHICLE, not the evidence — local suites GREEN both targets + the Docker parity leg + the three-leg witness + m-2's byte review + the merge bar + the operator's token are the evidence; red REMOTE CI cited nowhere; (5) the LANDING per R-4.52 in the merge packet's §7 shape: local `--no-ff` merge under the operator's token, NO trailer on any new commit, the census at the MERGE HEAD against a population file written FOR THAT OBJECT (population + reduction + collation pinned), ONE ff push of the pinned merge sha, receipts, PR observed merged at the remote; the docs commits above `4cf135ee` ride it; (6) R-4.53 arm (a): the raw/stripped census intermediates live under `$EVID/census-raw/` and the strace traces under `$EVID/{B,H}/strace-*.log`, both EXCLUDED from the evidence-of-record set by `finalize.py` (declared SCRATCH); `$EVID/work/` (S, the pack images) likewise.
- EVIDENCE HOME (master `042340` ruling (2), STANDING) = `$HOME/Programming/bivpak-evidence/r449-<token DISPATCH_ID>-XXXXXX` (`mkdir -p` the root, `mktemp -d` the home, `pwd -P`, never the OS temp root, never inside the repository); evidence is never resumed, only bytes are; the runners directory `r449-runners-XXXXXX` under the same root. S is about 850 MB under `$EVID/work` (1,540 rollouts × 256 KiB + 110 transcripts × 4 MiB + 5 × 1 MiB): disk is checked by the operator before Task 1.
- SHELL DISCIPLINE (standing corrective `164704`): every status captured as `rc=0; <cmd> || rc=$?` and RECORDED; never `set +e`; NO pipelines in any evidence-producing span — every producer writes a FILE and its status; every count is produced by a command over a file, never typed; the execution shell recorded.
- The GitHub token never enters a container or any evidence (the containers mount `/repo-ro` read-only, `/llvm-mirror` read-only and `$EVID` writable — no credential file, no env var); credential VALUES never read, recorded or echoed (the observer unsets the harness's credential env NAMES for every suite run and every pack run; names only in the record); the census alternation is applied to the branch head only through the runner's reductions (path:line; no matched text in the record — R-4.53); every log aggregate is token-scanned with the full alternation (0 hits or STOP); the host worktree byte-clean at product paths; inherited S4 state preserved, never cleaned; the MAIN checkout's product paths NEVER mutated (no-mutation proofs at every task).
- ONE commit (the grant: "ONE commissioned-lane commit"); its message = the `commit-message.txt` BLOCK + the pins (fence, rulings, plan lock, B) — NO `Co-Authored-By` trailer (the operator's rule; proven on the message file AND on the committed object).
- Merge ≠ push ≠ release. The branch push and the PR are authorized by R-4.51 clause (2) via the route; the local merge waits on the four-condition bar + m-2's review + the operator's condition-4 token; the landing push is the merge packet's own step under R-4.52; the release hold is ABSOLUTE.

## Reconcile (pair lifecycle step 3) — the implementer's `165828` against the planner's `165304`

| # | Implementer `165828` | Planner `165304` | Verdict | Where it lands |
|---|---|---|---|---|
| C-1 | claude governing text/bound = m-2 confirmation (A1 §A1 supersedes c1 §3) | same finding, routed `165305` | agree — RULED `170000` | THE BOUNDS; head reader = first cwd-bearing record |
| C-2 | codex bound = m-2 confirmation; no fixed cap from the host | same | agree — RULED `170000` | THE BOUNDS; head reader = first session_meta |
| O-1 | the rev0 reader inherited the all-three (cwd+sessionId+version) exit — NOT a valid bound for a non-selected transcript whose first cwd record lacks the enrichment fields; decide first-cwd BEFORE the full read, take sessionId/version from the selected file's full parse; witness must not assert every non-selected file is head-bounded (no-cwd = EOF) | rev0 carried the all-three reader | **agree — FOLDED**: `first_transcript_cwd` stops at the first cwd; the in-root path runs today's `inspect_transcript` over the full text; class `claude-cwd-no-enrichment` in S (LEG 2) + SECTION "enrichment fields behind the first cwd record"; LEG 1's sealed whole-file classes stated | patcher, S, SECTIONs, LEG 1/2 |
| O-2 | closure/tail full reads unchanged (static boundary) | same | agree | Task 5 V-LS-4 greps + hunk windows |
| O-3 | canonical cross-repo edge measured root-mode (master's gate) | same | agree | the pair Planner's root-mode measurement precedes the PLAN filing |
| O-4 | landing/fixture-root terms (fresh branch at the pin; m-3 rules; census; R-4.53 arm (a)) | same | agree | Global constraints; Task 0 / Task 1 / Task 5 |
| — | host structure check: 1,503/1,503 codex line-1 (max line 22,553 B incl. newline); claude 97/100 have cwd and all 97 have cwd+sessionId+version by the first cwd-bearing record; 3 no-cwd files (756 B total) | 2/100 line-1 cwd; first cwd lines 3–9, worst 106; up to 15.5 MB | different coverage (both structure-only; live store drift acknowledged) — neither is the witness | informative only |

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


## B / H / S / F — roles, resolution, binding points (predeclared BEFORE any observation)

```text
B  the BASE = the published pin = origin/main = 4cf135ee97f57021c5fc5fd5343de6f655fb0d24 (the R-4.50 landing merge). RESOLVED at
   Task 0 Step 1 (the remote re-read must equal it; any other value = STOP UP, never a silent re-base) and RECORDED with B's workflow
   cells (the ten OverallResultsCases cells read from the workflow bytes by cells.py) → $EVID/B.txt, $EVID/B-cells.txt. B is the BEFORE
   side of every witness leg: built and observed in this token on both targets (Task 0 Step 6 macOS tuples; Task 1 LEG 3 macOS; Task 4 the
   B container: suites + Phase L).
H  the CANDIDATE = B + EXACTLY ONE commit (the two adapter files + the two test files). H's identity is RECORDED at Task 2 Step 5 (after
   the commit exists, BEFORE Task 3 observes it) → $EVID/H.txt; H^ == B proven there and at every later task. H is the PR HEAD; the
   acceptance suites of record run at H on both targets (Task 3, Task 4); the witness legs run at H against B (Task 4 LEG 1/2; Task 3 +
   Task 4 LEG 3).
S  the LARGE SYNTHETIC STORE pair (codex-home + claude-config under $EVID/work/, cwd of exactly K=3 sessions per agent == $EVID/work/ws/proj)
   built ONCE at Task 1 Step 2 by synth_store.py from the recorded seed (20260913) → $EVID/synth-manifest.json (paths relative to work,
   class, selected, size, head_end — names/ids/counts only, never content); six classes (see synth_store.py's header); S is the same bytes
   on both sides (read by B's binary and by H's binary, on macOS from $EVID/work and in each container from a copy at /work/synth);
   S is EXCLUDED from the evidence-of-record set and never committed; its ids never match any poison value (rule 1) and its stores live at
   locator values (rule 3).
F  the FIXTURE CORPUS = tests/fixtures/{claude,codex}_store (committed at B; the claude fixture aaaaaaaa… has the REAL metadata-first
   head with the first cwd on line 5; no-cwd-9999… has no cwd anywhere) + the two collect suites' inline stores. The suites are the
   membership oracle over F: every existing assertion green at B (Task 0 Step 6) and at H (Task 2 Step 3, Task 3, Task 4) on both targets,
   plus the nine R-4.49 SECTIONs at H.
ANTI-RETROSPECTION  B.txt and H.txt are written at their binding steps and never rewritten; every later use re-reads them.
```

## File structure

- Modify: `src/adapters/claude_code/claude_code.cpp` — `first_transcript_cwd` (new streaming head reader, inserted after `inspect_transcript`); `collect` candidate path: head decision, then the whole-file read + `inspect_transcript` for an in-root transcript only (patcher BLOCK `head_reader_claude.py`; every anchor asserted EXACTLY ONCE at B's bytes).
- Modify: `src/adapters/codex/codex.cpp` — `absorb_rollout_line` + `inspect_rollout_head` refactored over it (same semantics); `inspect_rollout_head_stream` (new); `collect`: the head read first, the full `source_text` moved below the cwd filter (patcher BLOCK `head_reader_codex.py`).
- Modify: `tests/test_adapter_claude_collect.cpp` — five `SECTION`s appended inside `TEST_CASE("Claude adapter keys membership on the first cwd record")` (patcher BLOCK `tests_claude_r449.py`): enrichment fields behind the first cwd record still key the selected session (sessionId/version from the full parse); an out-of-root first cwd record without enrichment fields is excluded silently however large the file; a large transcript with no cwd record anywhere is excluded and reported; metadata-first head (first cwd on line 5) with a large body is selected with today's fields; the first cwd on an unterminated final line still keys the session.
- Modify: `tests/test_adapter_codex_collect.cpp` — four `SECTION`s appended inside `TEST_CASE("X-2 Codex suppresses session_id warnings outside the source root")` (patcher BLOCK `tests_codex_r449.py`): an unparseable first line ahead of session_meta still keys the rollout; the tail facts of a large selected rollout come from its full text (a terminal `task_complete` after 3 MiB → `live_at_pack` false); an out-of-root session_meta with a large body is excluded without a warning; the in-root `SessionIdWithoutId` warning still fires from the head facts of a large rollout.
- Evidence (outside the repository): `$EVID` under the durable root; `$EVID/work/` (S, the pack images), `$EVID/census-raw/` and `$EVID/{B,H}/strace-*.log` EXCLUDED from the record (`finalize.py` SCRATCH); the tracked record `results/r449-<token>/` by Task 7.
- Instruments (BLOCKs of this document; materialized at Task 0 Step 0b; hashed into `helpers.sha256`; verified before every task): `cells.py`, `tuples.py`, `cellgate.py`, `skipset.py`, `selftest_summary.py`, `finalize.py`, `synth_store.py`, `membership.py`, `strace_bytes.py`, `leg12_verdict.py`, `pack_run.py`, `hunkwin.py`, `head_reader_claude.py`, `head_reader_codex.py`, `tests_claude_r449.py`, `tests_codex_r449.py`, `linux-container.sh` (the R-4.50 container with the branch name, `strace` in Phase R's package list and a new Phase L), `linux-suite.sh` (unchanged from R-4.50 rev19), `commit-message.txt`.

### Task 0 — bootstrap: evidence home; helpers; B resolved and recorded; the `-v2` worktree DISPOSED with a receipt; the FRESH branch + worktree from the pin; venv + build at B; the observer; B's macOS tuples

- [ ] **Step 0: the evidence home** — the token id from the runners dir; `mktemp -d` under the durable root with the `r449-` prefix, resolved with `pwd -P`; not the OS temp root; not inside the repository; the sub-directories `runners`, `B`, `H`, `work`, `census-raw`; the proof set copied; `token.txt`; the MAIN checkout's product-path status snapshot (`status-initial.txt`).
- [ ] **Step 0b: helpers materialized** — the sixteen python BLOCKs extracted and `py_compile`d, the two shell BLOCKs extracted and `bash -n`'d, the commit-message BLOCK extracted; `helpers.sha256` over all nineteen; the block listing compared with the bootstrap's.
- [ ] **Step 1: B resolved and recorded** — fetch `origin/main`; it MUST equal `4cf135ee97f57021c5fc5fd5343de6f655fb0d24` or STOP; the workflow bytes at B → `cells.py` → `B-cells.txt`; `B.txt`; the eight-line LLVM mirror manifest cut from the workflow (lines 167–174, shape-checked); the four base files and their digests (`base-hashes.txt`).
- [ ] **Step 2: the retained `-v2` worktree DISPOSED (master `164219` (1))** — preconditions: its HEAD is H' `e8a1128d75cd4693d21269c4d040095df570f116` on branch `intg/r450-discover-parity-v2`, status EMPTY, both local refs at their recorded values (`8509157c…`, `e8a1128d…`), two remote heads present; then `git worktree remove`; the path ABSENT after; both refs UNCHANGED after; the worktree list no longer names it → `worktree-dispose.txt`.
- [ ] **Step 3: the FRESH branch and worktree from the pin** — no local branch `intg/r449-line1-selection`, no remote head of that name, the worktree path absent; `git worktree add -b intg/r449-line1-selection ../bivpak-intg-r449-line1-selection <B>`; HEAD == B on the new branch; status EMPTY; cut-point `origin/main..HEAD` == 0 → `cutpoint.txt`; the ignore proof for `.venv-harness/` and `build/`.
- [ ] **Step 4: venv + build at B** — the harness venv from `harness/requirements.lock` (python3.12); the import proof; the configure with the `BIVHARNESS_PYTHON` cache proof; the build; `build/ci-macos/biv` present.
- [ ] **Step 5: the observer** — the credential env NAMES from the harness (`CREDENTIAL_ENV_NAMES`), shape-checked; host presence names-only; the `OBS_ENV` unset vector.
- [ ] **Step 6: B observed on macOS** — the five binaries `-r xml` under the observer → `B/tuples-macos.txt` (`tuples.py`), the skip set vs B's cells (`skipset.py`); status EMPTY after.

<!-- RUN: task-0 -->
```bash
# Runner plumbing (Task 0)
WORKTREE=/Users/jack/Programming/bivpak-intg-r449-line1-selection
OLDWT=/Users/jack/Programming/bivpak-intg-r450-discover-parity
MAIN=/Users/jack/Programming/bivpak
B=4cf135ee97f57021c5fc5fd5343de6f655fb0d24
PLAN=$(cat "$RUNNERS/plan-path.txt") || STOP; [ -s "$PLAN" ] || STOP
cd "$MAIN" || STOP
# Step 0
TOKEN=$(cat "$RUNNERS/token-id.txt") || STOP; [ -n "$TOKEN" ] || STOP
m=0; mkdir -p "$HOME/Programming/bivpak-evidence" || m=$?; [ "$m" -eq 0 ] && [ -d "$HOME/Programming/bivpak-evidence" ] || STOP
EVID_RAW=$(mktemp -d "$HOME/Programming/bivpak-evidence/r449-${TOKEN}-XXXXXX") || STOP
EVID=$(cd "$EVID_RAW" && pwd -P) || STOP
[ -d "$EVID" ] && [ "$EVID" = "$EVID_RAW" ] || STOP
case "$EVID/" in /var/folders/*|/private/var/folders/*|/tmp/*|/private/tmp/*) echo STOP-evid-in-temp-root; exit 1;; esac
case "$EVID/" in "$(git rev-parse --show-toplevel)/"*) echo STOP-evid-inside-repo; exit 1;; esac
m=0; mkdir "$EVID/runners" "$EVID/B" "$EVID/H" "$EVID/work" "$EVID/census-raw" || m=$?; [ "$m" -eq 0 ] && [ -d "$EVID/runners" ] && [ -d "$EVID/work" ] || STOP
w=0; printf '%s\n' "$EVID" > "$RUNNERS/evid.txt" || w=$?; [ "$w" -eq 0 ] && [ -s "$RUNNERS/evid.txt" ] || STOP; w=0; printf '%s\n' "$RUNNERS" > "$EVID/runners-dir.txt" || w=$?; [ "$w" -eq 0 ] && [ -s "$EVID/runners-dir.txt" ] || STOP
c=0; cp -p "$RUNNERS/task-0.sh" "$RUNNERS/proof-0.txt" "$RUNNERS/task-0.sha256" "$RUNNERS/task-0.invocation.txt" "$RUNNERS/plan_blocks.py" "$RUNNERS/run-task.sh" "$RUNNERS/run-task.sha256" "$RUNNERS/blocks.txt" "$RUNNERS/plan-lock.txt" "$RUNNERS/plan-path.txt" "$RUNNERS/plan-hash-0.txt" "$EVID/runners/" || c=$?; [ "$c" -eq 0 ] || STOP
w=0; printf 'token=%s\nevid=%s\n' "$TOKEN" "$EVID" > "$EVID/token.txt" || w=$?; [ "$w" -eq 0 ] && [ -s "$EVID/token.txt" ] || STOP
s0=0; git -C "$MAIN" status --porcelain -- . ':(exclude).relays' ':(exclude)docs/sprints' > "$EVID/status-initial.txt" || s0=$?; [ "$s0" -eq 0 ] || STOP
# Step 0b
for name in cells tuples cellgate skipset selftest_summary finalize synth_store membership strace_bytes leg12_verdict pack_run hunkwin head_reader_claude head_reader_codex tests_claude_r449 tests_codex_r449; do x=0; python3 "$RUNNERS/plan_blocks.py" extract "$PLAN" "$name.py" > "$EVID/$name.py" || x=$?; [ "$x" -eq 0 ] && [ -s "$EVID/$name.py" ] || STOP; k=0; python3 -m py_compile "$EVID/$name.py" || k=$?; [ "$k" -eq 0 ] || STOP; done
for name in linux-container.sh linux-suite.sh; do x=0; python3 "$RUNNERS/plan_blocks.py" extract "$PLAN" "$name" > "$EVID/$name" || x=$?; [ "$x" -eq 0 ] && [ -s "$EVID/$name" ] || STOP; s=0; bash -n "$EVID/$name" || s=$?; [ "$s" -eq 0 ] || STOP; done
x=0; python3 "$RUNNERS/plan_blocks.py" extract "$PLAN" commit-message.txt > "$EVID/commit-message.txt" || x=$?; [ "$x" -eq 0 ] && [ -s "$EVID/commit-message.txt" ] || STOP
h=0; (cd "$EVID" && shasum -a 256 cells.py tuples.py cellgate.py skipset.py selftest_summary.py finalize.py synth_store.py membership.py strace_bytes.py leg12_verdict.py pack_run.py hunkwin.py head_reader_claude.py head_reader_codex.py tests_claude_r449.py tests_codex_r449.py linux-container.sh linux-suite.sh commit-message.txt > helpers.sha256) || h=$?; [ "$h" -eq 0 ] && [ -s "$EVID/helpers.sha256" ] || STOP
x=0; python3 "$RUNNERS/plan_blocks.py" list "$PLAN" > "$EVID/blocks.txt" || x=$?; [ "$x" -eq 0 ] && [ -s "$EVID/blocks.txt" ] || STOP; c=0; cmp "$EVID/blocks.txt" "$RUNNERS/blocks.txt" || c=$?; [ "$c" -eq 0 ] || STOP
# Step 1
f=0; git -C "$MAIN" fetch --no-tags origin refs/heads/main:refs/remotes/origin/main || f=$?; [ "$f" -eq 0 ] || STOP
BASE=$(git -C "$MAIN" rev-parse origin/main) || STOP; [ "$BASE" = "$B" ] || STOP
w=0; git -C "$MAIN" show "${B}:.github/workflows/s2-harness.yml" > "$EVID/B-workflow.yml" || w=$?; [ "$w" -eq 0 ] && [ -s "$EVID/B-workflow.yml" ] || STOP
c=0; python3 "$EVID/cells.py" "$EVID/B-workflow.yml" > "$EVID/B-cells.txt" || c=$?; printf 'cells_B_rc=%s\n' "$c" > "$EVID/B-cells.rc"; [ "$c" -eq 0 ] && [ -s "$EVID/B-cells.txt" ] || STOP
printf 'B=%s\n' "$BASE" > "$EVID/B.txt"
s=0; sed -n '167,174p' "$EVID/B-workflow.yml" > "$EVID/llvm-manifest-source.txt" || s=$?; [ "$s" -eq 0 ] && [ -s "$EVID/llvm-manifest-source.txt" ] || STOP; s=0; sed 's/^          //' "$EVID/llvm-manifest-source.txt" > "$EVID/llvm-manifest.txt" || s=$?; [ "$s" -eq 0 ] && [ -s "$EVID/llvm-manifest.txt" ] || STOP; a=0; n=$(awk 'END { print NR }' "$EVID/llvm-manifest.txt") || a=$?; [ "$a" -eq 0 ] && [ "$n" -eq 8 ] || STOP; g=0; k=$(grep -c -E '^[0-9a-f]{64} [a-z0-9-]+ [A-Za-z0-9._+~-]+\.deb$' "$EVID/llvm-manifest.txt") || g=$?; [ "$g" -le 1 ] && [ "$k" -eq 8 ] || STOP
for p in src/adapters/claude_code/claude_code.cpp src/adapters/codex/codex.cpp tests/test_adapter_claude_collect.cpp tests/test_adapter_codex_collect.cpp; do w=0; git -C "$MAIN" show "${B}:${p}" > "$EVID/base-$(basename "$p")" || w=$?; [ "$w" -eq 0 ] && [ -s "$EVID/base-$(basename "$p")" ] || STOP; done; h=0; (cd "$EVID" && shasum -a 256 base-claude_code.cpp base-codex.cpp base-test_adapter_claude_collect.cpp base-test_adapter_codex_collect.cpp > base-hashes.txt) || h=$?; [ "$h" -eq 0 ] && [ -s "$EVID/base-hashes.txt" ] || STOP
# Step 2
[ -d "$OLDWT" ] || STOP; [ "$(git -C "$OLDWT" rev-parse HEAD)" = e8a1128d75cd4693d21269c4d040095df570f116 ] || STOP; [ "$(git -C "$OLDWT" rev-parse --abbrev-ref HEAD)" = intg/r450-discover-parity-v2 ] || STOP
s=0; git -C "$OLDWT" status --porcelain > "$EVID/oldwt-status.txt" || s=$?; [ "$s" -eq 0 ] && [ ! -s "$EVID/oldwt-status.txt" ] || STOP
[ "$(git -C "$MAIN" rev-parse refs/heads/intg/r450-discover-parity)" = 8509157c41c5ef66595d655f39eee5107081bd32 ] && [ "$(git -C "$MAIN" rev-parse refs/heads/intg/r450-discover-parity-v2)" = e8a1128d75cd4693d21269c4d040095df570f116 ] || STOP
l=0; git -C "$MAIN" ls-remote --heads origin intg/r450-discover-parity intg/r450-discover-parity-v2 > "$EVID/oldwt-remote-refs.txt" || l=$?; [ "$l" -eq 0 ] || STOP; a=0; n=$(awk 'END { print NR }' "$EVID/oldwt-remote-refs.txt") || a=$?; [ "$a" -eq 0 ] && [ "$n" -eq 2 ] || STOP
w=0; git -C "$MAIN" worktree remove "$OLDWT" > "$EVID/worktree-remove.log" 2>&1 || w=$?; [ "$w" -eq 0 ] && [ ! -e "$OLDWT" ] || STOP
[ "$(git -C "$MAIN" rev-parse refs/heads/intg/r450-discover-parity)" = 8509157c41c5ef66595d655f39eee5107081bd32 ] && [ "$(git -C "$MAIN" rev-parse refs/heads/intg/r450-discover-parity-v2)" = e8a1128d75cd4693d21269c4d040095df570f116 ] || STOP
l=0; git -C "$MAIN" worktree list > "$EVID/worktree-list-after.txt" || l=$?; [ "$l" -eq 0 ] && [ -s "$EVID/worktree-list-after.txt" ] || STOP; g=0; k=$(grep -c -F -- "$OLDWT" "$EVID/worktree-list-after.txt") || g=$?; [ "$g" -eq 1 ] && [ "$k" -eq 0 ] || STOP
w=0; printf 'disposed=%s head_was=e8a1128d75cd4693d21269c4d040095df570f116 branch_was=intg/r450-discover-parity-v2 remove_rc=0 refs_unchanged=yes remote_heads=%s\n' "$OLDWT" "$n" > "$EVID/worktree-dispose.txt" || w=$?; [ "$w" -eq 0 ] && [ -s "$EVID/worktree-dispose.txt" ] || STOP
# Step 3
e=0; git -C "$MAIN" show-ref --verify -q refs/heads/intg/r449-line1-selection || e=$?; [ "$e" -ne 0 ] || STOP
l=0; git -C "$MAIN" ls-remote --heads origin intg/r449-line1-selection > "$EVID/remote-branch-initial.txt" || l=$?; [ "$l" -eq 0 ] && [ ! -s "$EVID/remote-branch-initial.txt" ] || STOP
[ ! -e "$WORKTREE" ] || STOP
a=0; git -C "$MAIN" worktree add -b intg/r449-line1-selection "$WORKTREE" "$B" > "$EVID/worktree-add.log" 2>&1 || a=$?; [ "$a" -eq 0 ] && [ -d "$WORKTREE" ] || STOP
cd "$WORKTREE" || STOP
[ "$(git rev-parse HEAD)" = "$B" ] && [ "$(git rev-parse --abbrev-ref HEAD)" = intg/r449-line1-selection ] || STOP
s=0; git status --porcelain > "$EVID/status-worktree-0.txt" || s=$?; [ "$s" -eq 0 ] && [ ! -s "$EVID/status-worktree-0.txt" ] || STOP
c=0; n=$(git rev-list --count origin/main..HEAD) || c=$?; [ "$c" -eq 0 ] && [ "$n" -eq 0 ] || STOP; w=0; printf 'unpublished_commits_in_lineage=%s expected=0 cut_point=%s\n' "$n" "$B" > "$EVID/cutpoint.txt" || w=$?; [ "$w" -eq 0 ] && [ -s "$EVID/cutpoint.txt" ] || STOP
g=0; git check-ignore -q .venv-harness/ || g=$?; g2=0; git check-ignore -q build/ || g2=$?; printf 'venv_ignored_rc=%s build_ignored_rc=%s\n' "$g" "$g2" > "$EVID/ignore-proof.txt"; [ "$g" -eq 0 ] && [ "$g2" -eq 0 ] || STOP
# Step 4
v=0; /opt/homebrew/bin/python3.12 -m venv .venv-harness || v=$?; [ "$v" -eq 0 ] && [ -x .venv-harness/bin/python ] || STOP; i=0; .venv-harness/bin/python -m pip install -q -r harness/requirements.lock > "$EVID/venv-pip.log" 2>&1 || i=$?; [ "$i" -eq 0 ] || STOP
m=0; .venv-harness/bin/python -c 'import pytest, jsonschema, zstandard; print("imported", pytest.__name__, jsonschema.__name__, zstandard.__name__)' > "$EVID/venv-imports.txt" 2>&1 || m=$?; [ "$m" -eq 0 ] && [ -s "$EVID/venv-imports.txt" ] || STOP
p=0; .venv-harness/bin/python --version > "$EVID/venv-python.txt" 2>&1 || p=$?; [ "$p" -eq 0 ] && [ -s "$EVID/venv-python.txt" ] || STOP
s=0; git status --porcelain > "$EVID/status-post-venv.txt" || s=$?; [ "$s" -eq 0 ] && [ ! -s "$EVID/status-post-venv.txt" ] || STOP
b=0; cmake --preset ci-macos > "$EVID/B/configure-B.log" 2>&1 || b=$?; [ "$b" -eq 0 ] || STOP
g=0; k=$(grep -c -E '^BIVHARNESS_PYTHON:FILEPATH=.*/\.venv-harness/bin/python3$' build/ci-macos/CMakeCache.txt) || g=$?; [ "$g" -le 1 ] && [ "$k" -eq 1 ] || STOP; printf 'cache_k=%s\n' "$k" > "$EVID/B/cache-proof.txt"
b=0; cmake --build --preset ci-macos > "$EVID/B/build-B.log" 2>&1 || b=$?; [ "$b" -eq 0 ] && [ -x build/ci-macos/biv ] || STOP
# Step 5
n=0; (cd harness && ../.venv-harness/bin/python -c 'from bivharness.e3 import CREDENTIAL_ENV_NAMES as n; print("\n".join(n))') > "$EVID/observer-unset-names.txt" || n=$?; [ "$n" -eq 0 ] && [ -s "$EVID/observer-unset-names.txt" ] || STOP
g=0; k=$(grep -c -E '^[A-Z][A-Z0-9_]+$' "$EVID/observer-unset-names.txt") || g=$?; [ "$g" -eq 0 ] && [ "$k" -ge 1 ] || STOP; a=0; n=$(awk 'END { print NR }' "$EVID/observer-unset-names.txt") || a=$?; [ "$a" -eq 0 ] && [ "$n" -eq "$k" ] || STOP
while read -r n; do if printenv "$n" > /dev/null; then echo "$n present"; else echo "$n absent"; fi; done < "$EVID/observer-unset-names.txt" > "$EVID/observer-host-presence.txt"; [ -s "$EVID/observer-host-presence.txt" ] || STOP
g=0; present_count=$(grep -c present "$EVID/observer-host-presence.txt") || g=$?; [ "$g" -le 1 ] || STOP; printf 'present_count=%s\n' "$present_count" > "$EVID/observer-present-count.txt"
OBS_ENV=(env); while read -r n; do OBS_ENV+=(-u "$n"); done < "$EVID/observer-unset-names.txt"
# Step 6
for binary in biv_subprocess_tests biv_repo_git_tests biv_repo_engine_tests biv_tests biv_probe_tests; do x=0; "${OBS_ENV[@]}" "./build/ci-macos/$binary" -r xml > "$EVID/B/$binary-macos.xml" 2> "$EVID/B/$binary-macos.stderr" || x=$?; printf '%s\n' "$x" > "$EVID/B/$binary-macos.rc"; [ -s "$EVID/B/$binary-macos.xml" ] || STOP; done
u=0; python3 "$EVID/tuples.py" macos "$EVID"/B/biv_subprocess_tests-macos.xml "$EVID"/B/biv_repo_git_tests-macos.xml "$EVID"/B/biv_repo_engine_tests-macos.xml "$EVID"/B/biv_tests-macos.xml "$EVID"/B/biv_probe_tests-macos.xml > "$EVID/B/tuples-macos.txt" || u=$?; [ "$u" -eq 0 ] && [ -s "$EVID/B/tuples-macos.txt" ] || STOP
q=0; python3 "$EVID/skipset.py" "$EVID/B-cells.txt" "$EVID/B/tuples-macos.txt" macos > "$EVID/B/skipset-macos.txt" || q=$?; [ "$q" -eq 0 ] && [ -s "$EVID/B/skipset-macos.txt" ] || STOP
s=0; git status --porcelain > "$EVID/status-post-B.txt" || s=$?; [ "$s" -eq 0 ] && [ ! -s "$EVID/status-post-B.txt" ] || STOP
exit 0
```

### Task 1 — the BEFORE side at B (macOS): the synthetic store S built and proven, LEG 3's B snapshot and timing

- [ ] **Step 1: the seed** — `synth-seed.txt` = 20260913 (recorded; S is deterministic from it).
- [ ] **Step 2: build S** — `synth_store.py "$EVID/work" <seed>` → `synth-manifest.json` copied beside the record; the class counts proven (codex-bulk 1500, codex-garbage-line1 20, codex-no-meta 10, claude-bulk 100, claude-cwd-no-enrichment 10, claude-no-cwd 5; K = 3 selected per agent); the poison check (every uuid literal of B's `harness/bivharness/scenario.py` grepped against the manifest: 0 hits); `locators.txt` (names + paths).
- [ ] **Step 3: LEG 3 at B** — `pack_run.py` with B's binary over S (three runs, medians; the observer unset vector) → `B/pack-B.json`, `B/time-B.txt`, the image `work/ws/proj-B.bvpk`; `membership.py` → `B/membership-B.json` with count 6; the `no_cwd` mention count of the pack JSON recorded; worktree status EMPTY; the MAIN checkout unchanged.

<!-- RUN: task-1 -->
```bash
# Runner plumbing (Task 1)
WORKTREE=/Users/jack/Programming/bivpak-intg-r449-line1-selection
MAIN=/Users/jack/Programming/bivpak
B=4cf135ee97f57021c5fc5fd5343de6f655fb0d24
cd "$WORKTREE" || STOP
v=0; (cd "$EVID" && shasum -a 256 -c helpers.sha256 > helpers.verify-1.txt 2>&1) || v=$?; [ "$v" -eq 0 ] || STOP
[ -s "$EVID/observer-unset-names.txt" ] || STOP
OBS_ENV=(env); while read -r n; do OBS_ENV+=(-u "$n"); done < "$EVID/observer-unset-names.txt"
[ "$(git rev-parse HEAD)" = "$B" ] && [ -x build/ci-macos/biv ] || STOP
# Step 1
w=0; printf '20260913\n' > "$EVID/synth-seed.txt" || w=$?; [ "$w" -eq 0 ] && [ -d "$EVID/work" ] || STOP
# Step 2
x=0; python3 "$EVID/synth_store.py" "$EVID/work" "$(cat "$EVID/synth-seed.txt")" > "$EVID/synth-build.log" 2>&1 || x=$?; [ "$x" -eq 0 ] && [ -s "$EVID/work/synth-manifest.json" ] || STOP
c=0; cp -p "$EVID/work/synth-manifest.json" "$EVID/synth-manifest.json" || c=$?; [ "$c" -eq 0 ] && [ -s "$EVID/synth-manifest.json" ] || STOP
k=0; python3 -c 'import json, sys; m = json.load(open(sys.argv[1])); c = m["counts"]; want = {"codex-bulk": 1500, "codex-garbage-line1": 20, "codex-no-meta": 10, "claude-bulk": 100, "claude-cwd-no-enrichment": 10, "claude-no-cwd": 5}; assert c == want, c; assert len(m["selected"]["codex"]) == 3 and len(m["selected"]["claude"]) == 3, m["selected"]; print("classes ok total_bytes=%d files=%d" % (m["total_bytes"], len(m["files"])))' "$EVID/synth-manifest.json" > "$EVID/synth-classes.txt" || k=$?; [ "$k" -eq 0 ] && [ -s "$EVID/synth-classes.txt" ] || STOP
w=0; git show "${B}:harness/bivharness/scenario.py" > "$EVID/scenario-B.py" || w=$?; [ "$w" -eq 0 ] && [ -s "$EVID/scenario-B.py" ] || STOP; o=0; grep -o -E '[0-9a-f]{8}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{12}' "$EVID/scenario-B.py" > "$EVID/poison-ids.txt" || o=$?; [ "$o" -eq 0 ] && [ -s "$EVID/poison-ids.txt" ] || STOP; g=0; k=$(grep -c -F -f "$EVID/poison-ids.txt" "$EVID/synth-manifest.json") || g=$?; [ "$g" -eq 1 ] && [ "$k" -eq 0 ] || STOP
w=0; printf 'HOME=%s/work/home\nCODEX_HOME=%s/work/codex-home\nCLAUDE_CONFIG_DIR=%s/work/claude-config\nTMPDIR=%s/work/tmp\nsource=%s/work/ws/proj\n' "$EVID" "$EVID" "$EVID" "$EVID" "$EVID" > "$EVID/locators.txt" || w=$?; [ "$w" -eq 0 ] && [ -s "$EVID/locators.txt" ] || STOP
# Step 3
p=0; "${OBS_ENV[@]}" python3 "$EVID/pack_run.py" "$WORKTREE/build/ci-macos/biv" "$EVID/work" B "$EVID/B" > "$EVID/B/pack-run.log" 2>&1 || p=$?; [ "$p" -eq 0 ] && [ -s "$EVID/B/pack-B.json" ] && [ -s "$EVID/B/time-B.txt" ] && [ -s "$EVID/work/ws/proj-B.bvpk" ] || STOP
m=0; python3 "$EVID/membership.py" "$EVID/work/ws/proj-B.bvpk" "$EVID/B/membership-B.json" > "$EVID/B/membership-B.log" 2>&1 || m=$?; [ "$m" -eq 0 ] && [ -s "$EVID/B/membership-B.json" ] || STOP
g=0; k=$(grep -c -F -- ' "count": 6,' "$EVID/B/membership-B.json") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP
g=0; k=$(grep -c -F 'no_cwd' "$EVID/B/pack-B.json") || g=$?; [ "$g" -le 1 ] || STOP; printf 'no_cwd_mentions=%s\n' "$k" > "$EVID/B/no-cwd-count.txt"
s=0; git status --porcelain > "$EVID/status-post-1.txt" || s=$?; [ "$s" -eq 0 ] && [ ! -s "$EVID/status-post-1.txt" ] || STOP
s=0; git -C "$MAIN" status --porcelain -- . ':(exclude).relays' ':(exclude)docs/sprints' > "$EVID/status-main-post-1.txt" || s=$?; [ "$s" -eq 0 ] || STOP; d=0; diff "$EVID/status-initial.txt" "$EVID/status-main-post-1.txt" > "$EVID/status-main-post-1.delta" || d=$?; [ "$d" -eq 0 ] || STOP
exit 0
```

### Task 2 — the CHANGE (one commit): the four patchers at B's bytes, the TEST_CASE census, build + whole suite pre-commit, the commit, H BOUND

- [ ] **Step 1: patch** — the two adapter patchers and the two test patchers (each anchor asserted EXACTLY ONCE at B's bytes; an assertion failure = STOP: the base moved); the working-tree numstat paths == exactly the four touchable paths.
- [ ] **Step 2: the TEST_CASE census** — `grep -c '^TEST_CASE'` per test file UNCHANGED: 15 (claude) / 25 (codex) — the predictor of the count gate.
- [ ] **Step 3: build + the whole `biv_tests` pre-commit** — `-r xml` under the observer, rc 0; exactly nine `<Section name="R-4.49…">` elements observed.
- [ ] **Step 4: the commit** — the message = the `commit-message.txt` BLOCK + the pins (fence sha, the rulings relay path, the plan lock from the runners dir, B); no `Co-Authored-By` in the message file; `git add` EXACTLY the four paths; `git commit -F`.
- [ ] **Step 5: H BOUND** — `H.txt` := HEAD; `H^` == B; the committed message re-read from the object carries no trailer; the numstat B→H paths == the four; status EMPTY.

<!-- RUN: task-2 -->
```bash
# Runner plumbing (Task 2)
WORKTREE=/Users/jack/Programming/bivpak-intg-r449-line1-selection
MAIN=/Users/jack/Programming/bivpak
B=4cf135ee97f57021c5fc5fd5343de6f655fb0d24
cd "$WORKTREE" || STOP
v=0; (cd "$EVID" && shasum -a 256 -c helpers.sha256 > helpers.verify-2.txt 2>&1) || v=$?; [ "$v" -eq 0 ] || STOP
[ -s "$EVID/observer-unset-names.txt" ] || STOP
OBS_ENV=(env); while read -r n; do OBS_ENV+=(-u "$n"); done < "$EVID/observer-unset-names.txt"
[ "$(git rev-parse HEAD)" = "$B" ] || STOP; s=0; git status --porcelain > "$EVID/H/status-pre-patch.txt" || s=$?; [ "$s" -eq 0 ] && [ ! -s "$EVID/H/status-pre-patch.txt" ] || STOP
# Step 1
x=0; python3 "$EVID/head_reader_claude.py" src/adapters/claude_code/claude_code.cpp > "$EVID/H/patch-claude.log" 2>&1 || x=$?; [ "$x" -eq 0 ] || STOP
x=0; python3 "$EVID/head_reader_codex.py" src/adapters/codex/codex.cpp > "$EVID/H/patch-codex.log" 2>&1 || x=$?; [ "$x" -eq 0 ] || STOP
x=0; python3 "$EVID/tests_claude_r449.py" tests/test_adapter_claude_collect.cpp > "$EVID/H/patch-tests-claude.log" 2>&1 || x=$?; [ "$x" -eq 0 ] || STOP
x=0; python3 "$EVID/tests_codex_r449.py" tests/test_adapter_codex_collect.cpp > "$EVID/H/patch-tests-codex.log" 2>&1 || x=$?; [ "$x" -eq 0 ] || STOP
r=0; git diff --numstat > "$EVID/H/touched-wt.numstat" || r=$?; [ "$r" -eq 0 ] && [ -s "$EVID/H/touched-wt.numstat" ] || STOP; s=0; awk '{print $3}' "$EVID/H/touched-wt.numstat" > "$EVID/H/touched-wt.paths" || s=$?; [ "$s" -eq 0 ] || STOP; o=0; LC_ALL=C sort "$EVID/H/touched-wt.paths" > "$EVID/H/touched-wt.sorted" || o=$?; [ "$o" -eq 0 ] || STOP; printf 'src/adapters/claude_code/claude_code.cpp\nsrc/adapters/codex/codex.cpp\ntests/test_adapter_claude_collect.cpp\ntests/test_adapter_codex_collect.cpp\n' > "$EVID/touched.expected"; d=0; diff "$EVID/touched.expected" "$EVID/H/touched-wt.sorted" > "$EVID/H/touched-wt.delta" || d=$?; [ "$d" -eq 0 ] || STOP
# Step 2
g=0; k=$(grep -c '^TEST_CASE' tests/test_adapter_claude_collect.cpp) || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 15 ] || STOP; g=0; k2=$(grep -c '^TEST_CASE' tests/test_adapter_codex_collect.cpp) || g=$?; [ "$g" -eq 0 ] && [ "$k2" -eq 25 ] || STOP; printf 'claude_test_cases=%s codex_test_cases=%s\n' "$k" "$k2" > "$EVID/H/test-case-census.txt"
# Step 3
b=0; cmake --build --preset ci-macos > "$EVID/H/build-H.log" 2>&1 || b=$?; [ "$b" -eq 0 ] || STOP
t=0; "${OBS_ENV[@]}" ./build/ci-macos/biv_tests -r xml > "$EVID/H/biv_tests-pre-commit.xml" 2> "$EVID/H/biv_tests-pre-commit.stderr" || t=$?; printf '%s\n' "$t" > "$EVID/H/biv_tests-pre-commit.rc"; [ "$t" -eq 0 ] && [ -s "$EVID/H/biv_tests-pre-commit.xml" ] || STOP
g=0; k=$(grep -c '<Section name="R-4.49' "$EVID/H/biv_tests-pre-commit.xml") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 9 ] || STOP; printf 'r449_sections_run=%s\n' "$k" > "$EVID/H/sections-run.txt"
# Step 4
w=0; { cat "$EVID/commit-message.txt" && printf '\nDesign pin: m2-r450-discover-fence-rev2-20260903 sha256 f2216ee606a03b0b5b0b7f4562fed52a7349219c28990e6ee3e89b0cc25e8c6f (142000 section 2 preserved by reference); C-1/C-2 rulings: pdc master/relays/intg-r449-line1-selection-act/DESIGN-m2-planner-20260913-170000.md\nPlan pin: intg-r449-line1-selection-plan-20260913 sha256 %s\nBase: %s\n' "$(cat "$RUNNERS/plan-lock.txt")" "$B"; } > "$EVID/H/message-H.txt" || w=$?; [ "$w" -eq 0 ] && [ -s "$EVID/H/message-H.txt" ] || STOP
g=0; k=$(grep -c -F 'Co-Authored-By' "$EVID/H/message-H.txt") || g=$?; [ "$g" -eq 1 ] && [ "$k" -eq 0 ] || STOP
a=0; git add src/adapters/claude_code/claude_code.cpp src/adapters/codex/codex.cpp tests/test_adapter_claude_collect.cpp tests/test_adapter_codex_collect.cpp || a=$?; [ "$a" -eq 0 ] || STOP; c=0; git commit -q -F "$EVID/H/message-H.txt" || c=$?; [ "$c" -eq 0 ] || STOP
# Step 5
H=$(git rev-parse HEAD) || STOP; [ -n "$H" ] && [ "$(git rev-parse "HEAD^")" = "$B" ] || STOP; w=0; printf '%s\n' "$H" > "$EVID/H.txt" || w=$?; [ "$w" -eq 0 ] && [ -s "$EVID/H.txt" ] || STOP
m=0; git log -1 --format=%B "$H" > "$EVID/H/message-H.committed" || m=$?; [ "$m" -eq 0 ] && [ -s "$EVID/H/message-H.committed" ] || STOP; g=0; k=$(grep -c -F 'Co-Authored-By' "$EVID/H/message-H.committed") || g=$?; [ "$g" -eq 1 ] && [ "$k" -eq 0 ] || STOP
r=0; git diff --numstat "$B" "$H" > "$EVID/H/touched.numstat" || r=$?; [ "$r" -eq 0 ] && [ -s "$EVID/H/touched.numstat" ] || STOP; s=0; awk '{print $3}' "$EVID/H/touched.numstat" > "$EVID/H/touched.paths" || s=$?; [ "$s" -eq 0 ] || STOP; o=0; LC_ALL=C sort "$EVID/H/touched.paths" > "$EVID/H/touched.sorted" || o=$?; [ "$o" -eq 0 ] || STOP; d=0; diff "$EVID/touched.expected" "$EVID/H/touched.sorted" > "$EVID/H/touched.delta" || d=$?; [ "$d" -eq 0 ] || STOP
s=0; git status --porcelain > "$EVID/H/status-post-commit.txt" || s=$?; [ "$s" -eq 0 ] && [ ! -s "$EVID/H/status-post-commit.txt" ] || STOP
exit 0
```

### Task 3 — observation and ACCEPTANCE OF RECORD at H on macOS; LEG 3 at H; the count gate (macOS half)

- [ ] **Step 1: the acceptance** — the discriminator pair on `harness-selftest` (as-is vs unset; the iff/hygiene predicate); `ctest --preset ci-macos -E '^safety-hardening$'` REQUIRED rc 0; the five binaries `-r xml` → `H/tuples-macos.txt`; the nine SECTIONs observed again; the unfiltered scout (nonzero; exactly `safety-hardening`, the capability row); the aggregate log token-scanned with the FULL census alternation (0 hits); `run-identity-macos.txt`.
- [ ] **Step 2: LEG 3 at H** — `pack_run.py` with H's binary over S → `H/membership-H.json` (count 6); `diff B/membership-B.json H/membership-H.json` EMPTY or STOP (V-LS-2 red, no argument heard); the `no_cwd` mention counts equal; `H/cost-receipt.txt` (B and H medians).
- [ ] **Step 3: the count gate, macOS** — `cellgate.py` (B literal == B observed == H observed for the five binaries) rc 0 or STOP UP; `skipset.py` at H.
- [ ] **Step 4: no-mutation proofs** — worktree status EMPTY at H; the MAIN checkout unchanged.

<!-- RUN: task-3 -->
```bash
# Runner plumbing (Task 3)
WORKTREE=/Users/jack/Programming/bivpak-intg-r449-line1-selection
MAIN=/Users/jack/Programming/bivpak
B=4cf135ee97f57021c5fc5fd5343de6f655fb0d24
cd "$WORKTREE" || STOP
v=0; (cd "$EVID" && shasum -a 256 -c helpers.sha256 > helpers.verify-3.txt 2>&1) || v=$?; [ "$v" -eq 0 ] || STOP
[ -s "$EVID/observer-unset-names.txt" ] || STOP
OBS_ENV=(env); while read -r n; do OBS_ENV+=(-u "$n"); done < "$EVID/observer-unset-names.txt"
H=$(cat "$EVID/H.txt") || STOP; e=0; git cat-file -e "${H}^{commit}" || e=$?; [ "$e" -eq 0 ] || STOP; [ "$(git rev-parse HEAD)" = "$H" ] || STOP; s=0; git status --porcelain > "$EVID/H/status-pre-3.txt" || s=$?; [ "$s" -eq 0 ] && [ ! -s "$EVID/H/status-pre-3.txt" ] || STOP
# Step 1
b=0; cmake --build --preset ci-macos > "$EVID/H/build-H-3.log" 2>&1 || b=$?; [ "$b" -eq 0 ] || STOP
rc1=0; ctest --preset ci-macos -R '^harness-selftest$' > "$EVID/H/discriminator-as-is.log" 2>&1 || rc1=$?
rc2=0; "${OBS_ENV[@]}" ctest --preset ci-macos -R '^harness-selftest$' > "$EVID/H/discriminator-unset.log" 2>&1 || rc2=$?
present_count=$(cut -d= -f2 "$EVID/observer-present-count.txt")
iff=FAIL; hygiene=FAIL; [ "$rc2" -eq 0 ] && hygiene=PASS; if { [ "$present_count" -gt 0 ] && [ "$rc1" -ne 0 ]; } || { [ "$present_count" -eq 0 ] && [ "$rc1" -eq 0 ]; }; then iff=PASS; fi; printf 'rc1=%s rc2=%s present_count=%s iff=%s hygiene=%s\n' "$rc1" "$rc2" "$present_count" "$iff" "$hygiene" > "$EVID/H/discriminator-predicate.txt"; [ "$iff" = PASS ] && [ "$hygiene" = PASS ] || STOP
r=0; "${OBS_ENV[@]}" ctest --preset ci-macos -E '^safety-hardening$' --output-on-failure > "$EVID/H/ctest-macos-H.log" 2>&1 || r=$?; printf 'ctest_macos_H_rc=%s\n' "$r" > "$EVID/H/ctest-macos-H.rc"; [ "$r" -eq 0 ] || STOP
for binary in biv_subprocess_tests biv_repo_git_tests biv_repo_engine_tests biv_tests biv_probe_tests; do x=0; "${OBS_ENV[@]}" "./build/ci-macos/$binary" -r xml > "$EVID/H/$binary-macos.xml" 2> "$EVID/H/$binary-macos.stderr" || x=$?; printf '%s\n' "$x" > "$EVID/H/$binary-macos.rc"; [ -s "$EVID/H/$binary-macos.xml" ] || STOP; done
h=0; shasum -a 256 "$EVID"/H/*-macos.xml > "$EVID/H/xml-sha256-macos.txt" || h=$?; [ "$h" -eq 0 ] && [ -s "$EVID/H/xml-sha256-macos.txt" ] || STOP
u=0; python3 "$EVID/tuples.py" macos "$EVID"/H/biv_subprocess_tests-macos.xml "$EVID"/H/biv_repo_git_tests-macos.xml "$EVID"/H/biv_repo_engine_tests-macos.xml "$EVID"/H/biv_tests-macos.xml "$EVID"/H/biv_probe_tests-macos.xml > "$EVID/H/tuples-macos.txt" || u=$?; [ "$u" -eq 0 ] && [ -s "$EVID/H/tuples-macos.txt" ] || STOP
g=0; k=$(grep -c '<Section name="R-4.49' "$EVID/H/biv_tests-macos.xml") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 9 ] || STOP
r=0; "${OBS_ENV[@]}" ctest --preset ci-macos --output-on-failure > "$EVID/H/scout-macos.log" 2>&1 || r=$?; printf '%s\n' "$r" > "$EVID/H/scout-macos.rc"; [ "$r" -ne 0 ] && [ -s "$EVID/H/scout-macos.log" ] || STOP; f=0; grep -E '^[[:space:]]+[0-9]+ - .*\(Failed\)' "$EVID/H/scout-macos.log" > "$EVID/H/scout-macos.failed" || f=$?; [ "$f" -eq 0 ] && [ -s "$EVID/H/scout-macos.failed" ] || STOP; s=0; sed -E 's/^[[:space:]]*[0-9]+ - ([^ ]+) .*/\1/' "$EVID/H/scout-macos.failed" > "$EVID/H/scout-macos.failed-names" || s=$?; [ "$s" -eq 0 ] && [ -s "$EVID/H/scout-macos.failed-names" ] || STOP; printf 'safety-hardening\n' > "$EVID/H/scout-macos.expected"; d=0; diff "$EVID/H/scout-macos.expected" "$EVID/H/scout-macos.failed-names" > "$EVID/H/scout-macos.failed.delta" || d=$?; [ "$d" -eq 0 ] || STOP
c=0; cat -- "$EVID/H/ctest-macos-H.log" "$EVID/H/scout-macos.log" "$EVID/H/discriminator-as-is.log" "$EVID/H/discriminator-unset.log" "$EVID"/H/*-macos.stderr > "$EVID/H/all-logs-H-macos.txt" || c=$?; [ "$c" -eq 0 ] && [ -f "$EVID/H/all-logs-H-macos.txt" ] || STOP; g=0; secret_hits=$(grep -c -E 'sk-[A-Za-z0-9]{8,}|-----BEGIN [A-Z ]*PRIVATE KEY|AKIA[0-9A-Z]{16}|ghp_[A-Za-z0-9]{20,}|xox[abprs]-' "$EVID/H/all-logs-H-macos.txt") || g=$?; [ "$g" -le 1 ] || STOP; printf 'pattern=census-alternation cat_rc=%s grep_rc=%s hits=%s\n' "$c" "$g" "$secret_hits" > "$EVID/H/token-scan-macos.txt"; [ "$secret_hits" -eq 0 ] || STOP
i=0; { printf 'run_id=H-macos-%s\nplatform=macos\nH=%s\n' "$H" "$H" && sw_vers && uname -m && printf '%s\n' 'observer_unset_names:' && cat "$EVID/observer-unset-names.txt" && printf '%s\n' 'observer_host_presence_names_only:' && cat "$EVID/observer-host-presence.txt" "$EVID/observer-present-count.txt" "$EVID/H/discriminator-predicate.txt" "$EVID/H/tuples-macos.txt" "$EVID/H/xml-sha256-macos.txt" "$EVID/H/token-scan-macos.txt"; } > "$EVID/H/run-identity-macos.txt" || i=$?; [ "$i" -eq 0 ] && [ -s "$EVID/H/run-identity-macos.txt" ] || STOP
# Step 2
p=0; "${OBS_ENV[@]}" python3 "$EVID/pack_run.py" "$WORKTREE/build/ci-macos/biv" "$EVID/work" H "$EVID/H" > "$EVID/H/pack-run.log" 2>&1 || p=$?; [ "$p" -eq 0 ] && [ -s "$EVID/H/pack-H.json" ] && [ -s "$EVID/H/time-H.txt" ] && [ -s "$EVID/work/ws/proj-H.bvpk" ] || STOP
m=0; python3 "$EVID/membership.py" "$EVID/work/ws/proj-H.bvpk" "$EVID/H/membership-H.json" > "$EVID/H/membership-H.log" 2>&1 || m=$?; [ "$m" -eq 0 ] && [ -s "$EVID/H/membership-H.json" ] || STOP
g=0; k=$(grep -c -F -- ' "count": 6,' "$EVID/H/membership-H.json") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP
d=0; diff "$EVID/B/membership-B.json" "$EVID/H/membership-H.json" > "$EVID/H/membership.delta" || d=$?; [ "$d" -eq 0 ] || STOP
g=0; k=$(grep -c -F 'no_cwd' "$EVID/H/pack-H.json") || g=$?; [ "$g" -le 1 ] || STOP; printf 'no_cwd_mentions=%s\n' "$k" > "$EVID/H/no-cwd-count.txt"; c=0; cmp "$EVID/B/no-cwd-count.txt" "$EVID/H/no-cwd-count.txt" || c=$?; [ "$c" -eq 0 ] || STOP
c=0; { printf 'LEG 3 cost receipt: biv pack over S (medians of three runs), macOS, B then H\n'; cat "$EVID/B/time-B.txt" "$EVID/H/time-H.txt"; printf 'membership_delta=empty no_cwd_mentions_equal=yes\n'; } > "$EVID/H/cost-receipt.txt" || c=$?; [ "$c" -eq 0 ] && [ -s "$EVID/H/cost-receipt.txt" ] || STOP
# Step 3
q=0; python3 "$EVID/cellgate.py" "$EVID/B-cells.txt" macos "$EVID/B/tuples-macos.txt" "$EVID/H/tuples-macos.txt" > "$EVID/H/count-gate-macos.txt" || q=$?; printf 'count_gate_macos_rc=%s\n' "$q" > "$EVID/H/count-gate-macos.rc"; [ "$q" -eq 0 ] && [ -s "$EVID/H/count-gate-macos.txt" ] || STOP
q=0; python3 "$EVID/skipset.py" "$EVID/B-cells.txt" "$EVID/H/tuples-macos.txt" macos > "$EVID/H/skipset-macos.txt" || q=$?; [ "$q" -eq 0 ] && [ -s "$EVID/H/skipset-macos.txt" ] || STOP
# Step 4
s=0; git status --porcelain > "$EVID/H/status-post-3.txt" || s=$?; [ "$s" -eq 0 ] && [ ! -s "$EVID/H/status-post-3.txt" ] || STOP; [ "$(git rev-parse HEAD)" = "$H" ] || STOP
s=0; git -C "$MAIN" status --porcelain -- . ':(exclude).relays' ':(exclude)docs/sprints' > "$EVID/status-main-post-3.txt" || s=$?; [ "$s" -eq 0 ] || STOP; d=0; diff "$EVID/status-initial.txt" "$EVID/status-main-post-3.txt" > "$EVID/status-main-post-3.delta" || d=$?; [ "$d" -eq 0 ] || STOP
exit 0
```

### Task 4 — the Linux parity leg at H and at B (Phases R/T/S/L); LEG 1 and LEG 2 by strace; LEG 3 Linux; the iso rev13 bar with the in-token base draw; the count gate (Linux half)

- [ ] **Step 1: the container at H** — the LLVM mirror assets downloaded and digest-verified; the stale macOS image removed from `work/ws`; `docker run --rm --platform linux/amd64 --init` with `/repo-ro` (the MAIN checkout, read-only — the fresh worktree is a linked worktree so H's objects are in the shared store and the branch ref is cloneable), `/llvm-mirror` (read-only) and `$EVID` at `/evidence`; Phase L copies `/evidence/work` to `/work/synth`, chowns it to the suite user and runs `strace -f -s 0` around `biv pack /work/synth/ws/proj --json` with the locator env, reduces the trace (`strace_bytes.py`) and extracts the image's membership (`membership.py`); the required files present (suite XMLs, ctest log/rc/junit, `bytes-H.tsv`, `pack-linux-H.json/.rc/.ok`, `membership-linux-H.json`, `strace-H.size`); the container ledger's five phase keys = 0; the 26 required suite-ledger keys = 0 (28 rows); pack rc 0 or 2 with ok; membership count 6; the aggregate log token-scanned; the observer names absent in the container; `H/tuples-linux.txt`.
- [ ] **Step 2: the container at B** — the same at B (the base draw of the bar AND LEG 1's before side) → `B/…`.
- [ ] **Step 3: LEG 1 / LEG 2 / LEG 3 Linux** — `leg12_verdict.py B/bytes-B.tsv H/bytes-H.tsv synth-manifest.json` → `H/leg12-verdict.txt` (one row per file of S with its rule and verdict; per-class totals; the store totals and the H/B ratio; `VERDICT PASS violations=0` or STOP UP); `H/leg12-summary.txt`; `diff B/membership-linux-B.json H/membership-linux-H.json` EMPTY.
- [ ] **Step 4: the iso rev13 bar (a)–(h) at H with the in-token base draw at B** — EXACTLY the R-4.50 Task 6 Step 2 lines re-based on B (the receipt `H/linux-selftest-bar.txt`; the two admitted outcomes `pass-green` | `pass-r435-disclosed-registered-red`; every other outcome STOP UP with the receipt).
- [ ] **Step 5: the count gate, Linux** — `cellgate.py` linux rc 0 or STOP UP; `skipset.py` linux; `run-identity-linux.txt`; no-mutation proofs.

<!-- RUN: task-4 -->
```bash
# Runner plumbing (Task 4)
WORKTREE=/Users/jack/Programming/bivpak-intg-r449-line1-selection
MAIN=/Users/jack/Programming/bivpak
B=4cf135ee97f57021c5fc5fd5343de6f655fb0d24
cd "$WORKTREE" || STOP
v=0; (cd "$EVID" && shasum -a 256 -c helpers.sha256 > helpers.verify-4.txt 2>&1) || v=$?; [ "$v" -eq 0 ] || STOP
[ -s "$EVID/observer-unset-names.txt" ] && [ -s "$EVID/synth-manifest.json" ] && [ -d "$EVID/work/ws/proj" ] || STOP
H=$(cat "$EVID/H.txt") || STOP; e=0; git cat-file -e "${H}^{commit}" || e=$?; [ "$e" -eq 0 ] || STOP; [ "$(git rev-parse HEAD)" = "$H" ] || STOP
[ "$(sed -n 's/^B=//p' "$EVID/B.txt")" = "$B" ] || STOP
# Step 1
LLVM_RAW=$(mktemp -d "$EVID/llvm22-assets-H.XXXXXX") || STOP; LLVM_DIR=$(cd "$LLVM_RAW" && pwd -P) || STOP; c=0; cp "$EVID/llvm-manifest.txt" "$LLVM_DIR/MANIFEST" || c=$?; [ "$c" -eq 0 ] || STOP; h=0; while read -r _ package asset; do gh release download toolchain-mirror-clang-tidy-22-immutable-v1 --repo iwnlcern/bivpak --pattern "$asset" --dir "$LLVM_DIR" || h=$?; done < "$LLVM_DIR/MANIFEST" > "$EVID/H/phase-H.log" 2>&1; a=0; awk '{ print $1 "  " $3 }' "$LLVM_DIR/MANIFEST" > "$LLVM_DIR/SHA256SUMS" || a=$?; [ "$a" -eq 0 ] && [ -s "$LLVM_DIR/SHA256SUMS" ] || STOP; v=0; (cd "$LLVM_DIR" && shasum -a 256 -c SHA256SUMS) > "$EVID/H/phase-H-verify.txt" 2>&1 || v=$?; printf 'phase_H_transport_rc=%s verify_rc=%s\n' "$h" "$v" > "$EVID/H/phase-H.rc"; [ "$h" -eq 0 ] && [ "$v" -eq 0 ] || STOP
rm -f "$EVID"/work/ws/proj.bvpk "$EVID"/work/ws/proj.bvpk.partial "$EVID"/work/ws/proj.bvpk.spool
o=0; docker run --rm --platform linux/amd64 --init -v "${LLVM_DIR}:/llvm-mirror:ro" -v "${MAIN}:/repo-ro:ro" -v "${EVID}:/evidence" ubuntu:24.04 bash /evidence/linux-container.sh "$H" H > "$EVID/H/linux-container.log" 2>&1 || o=$?; printf '%s\n' "$o" > "$EVID/H/linux-container.rc"; [ "$o" -eq 0 ] && [ -s "$EVID/H/linux-container.log" ] || STOP
for f in linux-ledger.txt linux-suite-ledger.txt linux-observer-name-proof.txt linux-nofile.txt linux-run-head-receipt.txt container-payload.rc container-copy-out.rc ctest-linux-H.log ctest-linux-H.rc ctest-linux-H.junit.xml biv_subprocess_tests-linux.xml biv_repo_git_tests-linux.xml biv_repo_engine_tests-linux.xml biv_tests-linux.xml biv_probe_tests-linux.xml bytes-H.tsv pack-linux-H.json pack-linux-H.rc pack-linux-H.ok membership-linux-H.json strace-H.size; do [ -s "$EVID/H/$f" ] || STOP; done; [ "$(cat "$EVID/H/container-payload.rc")" = container_payload_rc=0 ] || STOP; [ "$(cat "$EVID/H/container-copy-out.rc")" = 'copy_out_rc=0 payload_receipt_rc=0' ] || STOP; for x in phase_R_base_provision_rc=0 phase_R_asset_provision_rc=0 phase_T_transition_fixture_rc=0 phase_S_suite_rc=0 phase_L_leg_rc=0; do g=0; k=$(grep -c -x -F -- "$x" "$EVID/H/linux-ledger.txt") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP; done
w=0; printf '%s=0\n' nofile_hard_read_rc nofile_raise_rc nofile_soft_read_rc nofile_soft_equals_hard_rc nofile_receipt_write_rc venv_rc requirements_rc configure_rc build_rc observer_name_proof_create_rc observer_name_input_nonempty_rc observer_name_present_rc observer_name_proof_write_rc observer_name_proof_nonempty_rc biv_subprocess_tests_producer_rc biv_subprocess_tests_xml_nonempty_rc biv_repo_git_tests_producer_rc biv_repo_git_tests_xml_nonempty_rc biv_repo_engine_tests_producer_rc biv_repo_engine_tests_xml_nonempty_rc biv_tests_producer_rc biv_tests_xml_nonempty_rc biv_probe_tests_producer_rc biv_probe_tests_xml_nonempty_rc ctest_H_log_nonempty_rc ctest_H_receipt_write_rc > "$EVID/H/ledger-required.raw" || w=$?; [ "$w" -eq 0 ] || STOP; o=0; LC_ALL=C sort "$EVID/H/ledger-required.raw" > "$EVID/H/ledger-required.expected" || o=$?; [ "$o" -eq 0 ] && [ -s "$EVID/H/ledger-required.expected" ] || STOP; g=0; grep -E '^(nofile_hard_read_rc|nofile_raise_rc|nofile_soft_read_rc|nofile_soft_equals_hard_rc|nofile_receipt_write_rc|venv_rc|requirements_rc|configure_rc|build_rc|observer_name_proof_create_rc|observer_name_input_nonempty_rc|observer_name_present_rc|observer_name_proof_write_rc|observer_name_proof_nonempty_rc|biv_subprocess_tests_producer_rc|biv_subprocess_tests_xml_nonempty_rc|biv_repo_git_tests_producer_rc|biv_repo_git_tests_xml_nonempty_rc|biv_repo_engine_tests_producer_rc|biv_repo_engine_tests_xml_nonempty_rc|biv_tests_producer_rc|biv_tests_xml_nonempty_rc|biv_probe_tests_producer_rc|biv_probe_tests_xml_nonempty_rc|ctest_H_log_nonempty_rc|ctest_H_receipt_write_rc)=' "$EVID/H/linux-suite-ledger.txt" > "$EVID/H/ledger-required.txt" || g=$?; [ "$g" -eq 0 ] || STOP; o=0; LC_ALL=C sort "$EVID/H/ledger-required.txt" > "$EVID/H/ledger-required.sorted" || o=$?; [ "$o" -eq 0 ] || STOP; c=0; cmp "$EVID/H/ledger-required.sorted" "$EVID/H/ledger-required.expected" || c=$?; [ "$c" -eq 0 ] || STOP; a=0; ntot=$(awk 'END { print NR }' "$EVID/H/linux-suite-ledger.txt") || a=$?; [ "$a" -eq 0 ] && [ "$ntot" -eq 28 ] || STOP; g=0; grep -E '^ctest_H_producer_rc=[0-9]+$' "$EVID/H/linux-suite-ledger.txt" > "$EVID/H/ctest-key.txt" || g=$?; [ "$g" -eq 0 ] || STOP; a=0; k=$(awk 'END { print NR }' "$EVID/H/ctest-key.txt") || a=$?; [ "$a" -eq 0 ] && [ "$k" -eq 1 ] || STOP; s=0; sed 's/^ctest_H_producer_rc=//' "$EVID/H/ctest-key.txt" > "$EVID/H/ctest-key.value" || s=$?; [ "$s" -eq 0 ] && [ -s "$EVID/H/ctest-key.value" ] || STOP; [ "$(cat "$EVID/H/ctest-linux-H.rc")" = "$(cat "$EVID/H/ctest-key.value")" ] || STOP; g=0; k=$(grep -c -x -F 'suite_aggregate_rc=0 ledger_write_failed=0' "$EVID/H/linux-suite-ledger.txt") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP
[ "$(cat "$EVID/H/pack-linux-H.ok")" = 1 ] || STOP; case "$(cat "$EVID/H/pack-linux-H.rc")" in 0|2) ;; *) STOP;; esac; g=0; k=$(grep -c -F -- ' "count": 6,' "$EVID/H/membership-linux-H.json") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP
c=0; cat -- "$EVID/H/linux-container.log" "$EVID/H/phase-R-base.log" "$EVID/H/phase-R-assets.log" "$EVID/H/phase-T-transition.log" "$EVID/H/phase-S-suite.log" "$EVID/H/phase-L-leg.log" "$EVID/H/linux-venv.log" "$EVID/H/linux-requirements.log" "$EVID/H/linux-configure.log" "$EVID/H/linux-build.log" "$EVID/H/ctest-linux-H.log" "$EVID/H/pack-linux-H.stderr" "$EVID"/H/*-linux.stderr > "$EVID/H/all-logs-H-linux.txt" || c=$?; [ "$c" -eq 0 ] && [ -f "$EVID/H/all-logs-H-linux.txt" ] || STOP; g=0; secret_hits=$(grep -c -E 'sk-[A-Za-z0-9]{8,}|-----BEGIN [A-Z ]*PRIVATE KEY|AKIA[0-9A-Z]{16}|ghp_[A-Za-z0-9]{20,}|xox[abprs]-' "$EVID/H/all-logs-H-linux.txt") || g=$?; [ "$g" -le 1 ] || STOP; printf 'pattern=census-alternation cat_rc=%s grep_rc=%s hits=%s\n' "$c" "$g" "$secret_hits" > "$EVID/H/token-scan-linux.txt"; [ "$secret_hits" -eq 0 ] || STOP; s=0; sed 's/$/ absent/' "$EVID/observer-unset-names.txt" > "$EVID/H/linux-observer-name-proof.expected" || s=$?; [ "$s" -eq 0 ] && [ -s "$EVID/H/linux-observer-name-proof.expected" ] || STOP; d=0; diff "$EVID/H/linux-observer-name-proof.expected" "$EVID/H/linux-observer-name-proof.txt" > "$EVID/H/linux-observer-name-proof.delta" || d=$?; [ "$d" -eq 0 ] || STOP
h=0; shasum -a 256 "$EVID"/H/*-linux.xml > "$EVID/H/xml-sha256-linux.txt" || h=$?; [ "$h" -eq 0 ] && [ -s "$EVID/H/xml-sha256-linux.txt" ] || STOP
u=0; python3 "$EVID/tuples.py" linux "$EVID"/H/biv_subprocess_tests-linux.xml "$EVID"/H/biv_repo_git_tests-linux.xml "$EVID"/H/biv_repo_engine_tests-linux.xml "$EVID"/H/biv_tests-linux.xml "$EVID"/H/biv_probe_tests-linux.xml > "$EVID/H/tuples-linux.txt" || u=$?; [ "$u" -eq 0 ] && [ -s "$EVID/H/tuples-linux.txt" ] || STOP
# Step 2
o=0; docker run --rm --platform linux/amd64 --init -v "${LLVM_DIR}:/llvm-mirror:ro" -v "${MAIN}:/repo-ro:ro" -v "${EVID}:/evidence" ubuntu:24.04 bash /evidence/linux-container.sh "$B" B > "$EVID/B/linux-container.log" 2>&1 || o=$?; printf '%s\n' "$o" > "$EVID/B/linux-container.rc"; [ "$o" -eq 0 ] && [ -s "$EVID/B/linux-container.log" ] || STOP
for f in linux-ledger.txt linux-suite-ledger.txt linux-observer-name-proof.txt linux-nofile.txt linux-run-head-receipt.txt container-payload.rc container-copy-out.rc ctest-linux-B.log ctest-linux-B.rc ctest-linux-B.junit.xml biv_subprocess_tests-linux.xml biv_repo_git_tests-linux.xml biv_repo_engine_tests-linux.xml biv_tests-linux.xml biv_probe_tests-linux.xml bytes-B.tsv pack-linux-B.json pack-linux-B.rc pack-linux-B.ok membership-linux-B.json strace-B.size; do [ -s "$EVID/B/$f" ] || STOP; done; [ "$(cat "$EVID/B/container-payload.rc")" = container_payload_rc=0 ] || STOP; [ "$(cat "$EVID/B/container-copy-out.rc")" = 'copy_out_rc=0 payload_receipt_rc=0' ] || STOP; for x in phase_R_base_provision_rc=0 phase_R_asset_provision_rc=0 phase_T_transition_fixture_rc=0 phase_S_suite_rc=0 phase_L_leg_rc=0; do g=0; k=$(grep -c -x -F -- "$x" "$EVID/B/linux-ledger.txt") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP; done
w=0; printf '%s=0\n' nofile_hard_read_rc nofile_raise_rc nofile_soft_read_rc nofile_soft_equals_hard_rc nofile_receipt_write_rc venv_rc requirements_rc configure_rc build_rc observer_name_proof_create_rc observer_name_input_nonempty_rc observer_name_present_rc observer_name_proof_write_rc observer_name_proof_nonempty_rc biv_subprocess_tests_producer_rc biv_subprocess_tests_xml_nonempty_rc biv_repo_git_tests_producer_rc biv_repo_git_tests_xml_nonempty_rc biv_repo_engine_tests_producer_rc biv_repo_engine_tests_xml_nonempty_rc biv_tests_producer_rc biv_tests_xml_nonempty_rc biv_probe_tests_producer_rc biv_probe_tests_xml_nonempty_rc ctest_B_log_nonempty_rc ctest_B_receipt_write_rc > "$EVID/B/ledger-required.raw" || w=$?; [ "$w" -eq 0 ] || STOP; o=0; LC_ALL=C sort "$EVID/B/ledger-required.raw" > "$EVID/B/ledger-required.expected" || o=$?; [ "$o" -eq 0 ] && [ -s "$EVID/B/ledger-required.expected" ] || STOP; g=0; grep -E '^(nofile_hard_read_rc|nofile_raise_rc|nofile_soft_read_rc|nofile_soft_equals_hard_rc|nofile_receipt_write_rc|venv_rc|requirements_rc|configure_rc|build_rc|observer_name_proof_create_rc|observer_name_input_nonempty_rc|observer_name_present_rc|observer_name_proof_write_rc|observer_name_proof_nonempty_rc|biv_subprocess_tests_producer_rc|biv_subprocess_tests_xml_nonempty_rc|biv_repo_git_tests_producer_rc|biv_repo_git_tests_xml_nonempty_rc|biv_repo_engine_tests_producer_rc|biv_repo_engine_tests_xml_nonempty_rc|biv_tests_producer_rc|biv_tests_xml_nonempty_rc|biv_probe_tests_producer_rc|biv_probe_tests_xml_nonempty_rc|ctest_B_log_nonempty_rc|ctest_B_receipt_write_rc)=' "$EVID/B/linux-suite-ledger.txt" > "$EVID/B/ledger-required.txt" || g=$?; [ "$g" -eq 0 ] || STOP; o=0; LC_ALL=C sort "$EVID/B/ledger-required.txt" > "$EVID/B/ledger-required.sorted" || o=$?; [ "$o" -eq 0 ] || STOP; c=0; cmp "$EVID/B/ledger-required.sorted" "$EVID/B/ledger-required.expected" || c=$?; [ "$c" -eq 0 ] || STOP; a=0; ntot=$(awk 'END { print NR }' "$EVID/B/linux-suite-ledger.txt") || a=$?; [ "$a" -eq 0 ] && [ "$ntot" -eq 28 ] || STOP; g=0; grep -E '^ctest_B_producer_rc=[0-9]+$' "$EVID/B/linux-suite-ledger.txt" > "$EVID/B/ctest-key.txt" || g=$?; [ "$g" -eq 0 ] || STOP; a=0; k=$(awk 'END { print NR }' "$EVID/B/ctest-key.txt") || a=$?; [ "$a" -eq 0 ] && [ "$k" -eq 1 ] || STOP; s=0; sed 's/^ctest_B_producer_rc=//' "$EVID/B/ctest-key.txt" > "$EVID/B/ctest-key.value" || s=$?; [ "$s" -eq 0 ] && [ -s "$EVID/B/ctest-key.value" ] || STOP; [ "$(cat "$EVID/B/ctest-linux-B.rc")" = "$(cat "$EVID/B/ctest-key.value")" ] || STOP; g=0; k=$(grep -c -x -F 'suite_aggregate_rc=0 ledger_write_failed=0' "$EVID/B/linux-suite-ledger.txt") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP
[ "$(cat "$EVID/B/pack-linux-B.ok")" = 1 ] || STOP; case "$(cat "$EVID/B/pack-linux-B.rc")" in 0|2) ;; *) STOP;; esac; g=0; k=$(grep -c -F -- ' "count": 6,' "$EVID/B/membership-linux-B.json") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP
c=0; cat -- "$EVID/B/linux-container.log" "$EVID/B/phase-R-base.log" "$EVID/B/phase-R-assets.log" "$EVID/B/phase-T-transition.log" "$EVID/B/phase-S-suite.log" "$EVID/B/phase-L-leg.log" "$EVID/B/linux-venv.log" "$EVID/B/linux-requirements.log" "$EVID/B/linux-configure.log" "$EVID/B/linux-build.log" "$EVID/B/ctest-linux-B.log" "$EVID/B/pack-linux-B.stderr" "$EVID"/B/*-linux.stderr > "$EVID/B/all-logs-B-linux.txt" || c=$?; [ "$c" -eq 0 ] && [ -f "$EVID/B/all-logs-B-linux.txt" ] || STOP; g=0; secret_hits=$(grep -c -E 'sk-[A-Za-z0-9]{8,}|-----BEGIN [A-Z ]*PRIVATE KEY|AKIA[0-9A-Z]{16}|ghp_[A-Za-z0-9]{20,}|xox[abprs]-' "$EVID/B/all-logs-B-linux.txt") || g=$?; [ "$g" -le 1 ] || STOP; printf 'pattern=census-alternation cat_rc=%s grep_rc=%s hits=%s\n' "$c" "$g" "$secret_hits" > "$EVID/B/token-scan-linux.txt"; [ "$secret_hits" -eq 0 ] || STOP; s=0; sed 's/$/ absent/' "$EVID/observer-unset-names.txt" > "$EVID/B/linux-observer-name-proof.expected" || s=$?; [ "$s" -eq 0 ] && [ -s "$EVID/B/linux-observer-name-proof.expected" ] || STOP; d=0; diff "$EVID/B/linux-observer-name-proof.expected" "$EVID/B/linux-observer-name-proof.txt" > "$EVID/B/linux-observer-name-proof.delta" || d=$?; [ "$d" -eq 0 ] || STOP
h=0; shasum -a 256 "$EVID"/B/*-linux.xml > "$EVID/B/xml-sha256-linux.txt" || h=$?; [ "$h" -eq 0 ] && [ -s "$EVID/B/xml-sha256-linux.txt" ] || STOP
u=0; python3 "$EVID/tuples.py" linux "$EVID"/B/biv_subprocess_tests-linux.xml "$EVID"/B/biv_repo_git_tests-linux.xml "$EVID"/B/biv_repo_engine_tests-linux.xml "$EVID"/B/biv_tests-linux.xml "$EVID"/B/biv_probe_tests-linux.xml > "$EVID/B/tuples-linux.txt" || u=$?; [ "$u" -eq 0 ] && [ -s "$EVID/B/tuples-linux.txt" ] || STOP
# Step 3
v=0; python3 "$EVID/leg12_verdict.py" "$EVID/B/bytes-B.tsv" "$EVID/H/bytes-H.tsv" "$EVID/synth-manifest.json" > "$EVID/H/leg12-verdict.txt" || v=$?; printf 'leg12_rc=%s\n' "$v" > "$EVID/H/leg12-verdict.rc"; [ "$v" -eq 0 ] && [ -s "$EVID/H/leg12-verdict.txt" ] || STOP
g=0; k=$(grep -c -x -F 'VERDICT PASS violations=0' "$EVID/H/leg12-verdict.txt") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP; g=0; grep -E '^(CLASS |TOTAL |VERDICT )' "$EVID/H/leg12-verdict.txt" > "$EVID/H/leg12-summary.txt" || g=$?; [ "$g" -eq 0 ] && [ -s "$EVID/H/leg12-summary.txt" ] || STOP
d=0; diff "$EVID/B/membership-linux-B.json" "$EVID/H/membership-linux-H.json" > "$EVID/H/membership-linux.delta" || d=$?; [ "$d" -eq 0 ] || STOP
# Step 4
rcL=$(cat "$EVID/H/ctest-linux-H.rc"); [ -n "$rcL" ] || STOP; f=0; grep -E '^[[:space:]]+[0-9]+ - .*\(Failed\)' "$EVID/H/ctest-linux-H.log" > "$EVID/H/ctest-linux-H.failed" || f=$?; [ "$f" -le 1 ] || STOP; s=0; sed -E 's/^[[:space:]]*[0-9]+ - ([^ ]+) .*/\1/' "$EVID/H/ctest-linux-H.failed" > "$EVID/H/ctest-linux-H.failed-names" || s=$?; [ "$s" -eq 0 ] || STOP; printf 'harness-selftest\n' > "$EVID/ctest-failed.expected"; d=0; diff "$EVID/ctest-failed.expected" "$EVID/H/ctest-linux-H.failed-names" > "$EVID/H/ctest-linux-H.failed.delta" || d=$?; [ "$d" -le 1 ] || STOP; printf 'selftest/test_e3_asserts.py::test_file_reader_rejects_same_size_cross_chunk_in_place_rewrite\nselftest/test_e3_asserts.py::test_c1_zero_session_control_reds_on_file_inserted_at_scandir_stop\nselftest/test_e3_asserts.py::test_credential_scanner_detects_entry_added_after_directory_enumeration\nselftest/test_e3_asserts.py::test_run_e3_session_inserted_at_scandir_stop_reds_c1_before_open\n' > "$EVID/H/r435-family.txt"
x=0; python3 "$EVID/selftest_summary.py" "$EVID/H/ctest-linux-H.junit.xml" "$EVID/H/selftest-H" > "$EVID/H/selftest-H.out" || x=$?; [ "$x" -eq 0 ] && [ -s "$EVID/H/selftest-H.kv" ] || STOP; hsum=$(sed -n 's/^summary=//p' "$EVID/H/selftest-H.kv"); nfail=$(sed -n 's/^failed=//p' "$EVID/H/selftest-H.kv"); nf=$(sed -n 's/^names_count=//p' "$EVID/H/selftest-H.kv"); pop=$(sed -n 's/^population=//p' "$EVID/H/selftest-H.kv"); [ -n "$hsum" ] && [ -n "$nfail" ] && [ -n "$nf" ] && [ -n "$pop" ] || STOP; c=0; cp -p "$EVID/H/selftest-H.names" "$EVID/H/linux-selftest-failed.names" || c=$?; [ "$c" -eq 0 ] || STOP; o=0; grep -v -x -F -f "$EVID/H/r435-family.txt" "$EVID/H/selftest-H.names" > "$EVID/H/linux-selftest-foreign.names" || o=$?; [ "$o" -le 1 ] || STOP
g=0; trip=$(grep -c 'claude_adapter_file' "$EVID/H/ctest-linux-H.log") || g=$?; [ "$g" -le 1 ] || STOP; q=0; git diff --quiet "$B" "$H" -- harness/selftest/test_e3_asserts.py harness/bivharness/host2_credentials.py || q=$?; [ "$q" -le 1 ] || STOP
rcB=$(cat "$EVID/B/ctest-linux-B.rc"); [ -n "$rcB" ] || STOP; f=0; grep -E '^[[:space:]]+[0-9]+ - .*\(Failed\)' "$EVID/B/ctest-linux-B.log" > "$EVID/B/ctest-linux-B.failed" || f=$?; [ "$f" -le 1 ] || STOP; s=0; sed -E 's/^[[:space:]]*[0-9]+ - ([^ ]+) .*/\1/' "$EVID/B/ctest-linux-B.failed" > "$EVID/B/ctest-linux-B.failed-names" || s=$?; [ "$s" -eq 0 ] || STOP; a=0; nrowsb=$(awk 'END { print NR }' "$EVID/B/ctest-linux-B.failed-names") || a=$?; [ "$a" -eq 0 ] || STOP; db=0; diff "$EVID/ctest-failed.expected" "$EVID/B/ctest-linux-B.failed-names" > "$EVID/B/ctest-linux-B.failed.delta" || db=$?; [ "$db" -le 1 ] || STOP; x=0; python3 "$EVID/selftest_summary.py" "$EVID/B/ctest-linux-B.junit.xml" "$EVID/B/selftest-B" > "$EVID/B/selftest-B.out" || x=$?; [ "$x" -eq 0 ] && [ -s "$EVID/B/selftest-B.kv" ] || STOP; bsum=$(sed -n 's/^summary=//p' "$EVID/B/selftest-B.kv"); nbfail=$(sed -n 's/^failed=//p' "$EVID/B/selftest-B.kv"); nb=$(sed -n 's/^names_count=//p' "$EVID/B/selftest-B.kv"); popb=$(sed -n 's/^population=//p' "$EVID/B/selftest-B.kv"); [ -n "$bsum" ] && [ -n "$nbfail" ] && [ -n "$nb" ] && [ -n "$popb" ] || STOP; o=0; grep -v -x -F -f "$EVID/H/r435-family.txt" "$EVID/B/selftest-B.names" > "$EVID/B/base-foreign.names" || o=$?; [ "$o" -le 1 ] || STOP
bar=fail; if [ "$rcL" -eq 0 ]; then bar=pass-green; elif [ "$rcL" -ne 8 ] || [ "$d" -ne 0 ]; then bar=fail-not-the-one-row; elif [ "$hsum" != parsed ] || [ "$nf" -lt 1 ] || [ "$nf" -ne "$nfail" ]; then bar=stop-invalid-candidate-result; elif [ "$nf" -ge 5 ] || [ -s "$EVID/H/linux-selftest-foreign.names" ]; then bar=stop-fresh-finding-K1-K2-up-to-m3-m4; elif { [ "$rcB" -ne 0 ] && [ "$rcB" -ne 8 ]; } || { [ "$nrowsb" -ne 0 ] && [ "$db" -ne 0 ]; } || [ "$bsum" != parsed ] || [ "$nb" -ne "$nbfail" ]; then bar=stop-invalid-base-draw; elif [ "$q" -ne 0 ] || [ "$trip" -ne 0 ] || [ "$pop" -lt 1 ] || [ "$pop" -ne "$popb" ]; then bar=stop-single-draw-inadmissible-arm-ii-required; elif [ "$nb" -eq 0 ]; then bar=stop-inconclusive-base-green-arm-ii-required; elif [ "$nb" -ge 5 ] || [ -s "$EVID/B/base-foreign.names" ]; then bar=stop-fresh-finding-base-outside-family; else bar=pass-r435-disclosed-registered-red; fi
s=0; tr '\n' ',' < "$EVID/H/selftest-H.names" > "$EVID/H/selftest-H.csv" || s=$?; [ "$s" -eq 0 ] || STOP; s=0; tr '\n' ',' < "$EVID/H/linux-selftest-foreign.names" > "$EVID/H/linux-selftest-foreign.csv" || s=$?; [ "$s" -eq 0 ] || STOP; s=0; tr '\n' ',' < "$EVID/B/selftest-B.names" > "$EVID/B/selftest-B.csv" || s=$?; [ "$s" -eq 0 ] || STOP; s=0; tr '\n' ',' < "$EVID/B/base-foreign.names" > "$EVID/B/base-foreign.csv" || s=$?; [ "$s" -eq 0 ] || STOP; printf 'rcL=%s a_rows_rc=%s summary_H=%s failed_H=%s names_H=%s foreign_H=%s d_tripwire_lines=%s d_family_files_rc=%s population_H=%s rcB=%s base_rows=%s base_rows_rc=%s summary_B=%s failed_B=%s names_B=%s foreign_B=%s population_B=%s bar=%s\n' "$rcL" "$d" "$hsum" "$nfail" "$(cat "$EVID/H/selftest-H.csv")" "$(cat "$EVID/H/linux-selftest-foreign.csv")" "$trip" "$q" "$pop" "$rcB" "$nrowsb" "$db" "$bsum" "$nbfail" "$(cat "$EVID/B/selftest-B.csv")" "$(cat "$EVID/B/base-foreign.csv")" "$popb" "$bar" > "$EVID/H/linux-selftest-bar.txt"; case "$bar" in pass-green|pass-r435-disclosed-registered-red) ;; *) STOP;; esac
# Step 5
q=0; python3 "$EVID/cellgate.py" "$EVID/B-cells.txt" linux "$EVID/B/tuples-linux.txt" "$EVID/H/tuples-linux.txt" > "$EVID/H/count-gate-linux.txt" || q=$?; printf 'count_gate_linux_rc=%s\n' "$q" > "$EVID/H/count-gate-linux.rc"; [ "$q" -eq 0 ] && [ -s "$EVID/H/count-gate-linux.txt" ] || STOP
q=0; python3 "$EVID/skipset.py" "$EVID/B-cells.txt" "$EVID/H/tuples-linux.txt" linux > "$EVID/H/skipset-linux.txt" || q=$?; [ "$q" -eq 0 ] && [ -s "$EVID/H/skipset-linux.txt" ] || STOP
i=0; { printf 'run_id=H-linux-%s\nplatform=ubuntu:24.04 linux/amd64 --init\nH=%s\n' "$H" "$H" && cat "$EVID/H/linux-run-head-receipt.txt" "$EVID/H/linux-ledger.txt" "$EVID/H/linux-suite-ledger.txt" "$EVID/H/linux-nofile.txt" "$EVID/H/linux-observer-name-proof.txt" "$EVID/H/tuples-linux.txt" "$EVID/H/xml-sha256-linux.txt" "$EVID/H/token-scan-linux.txt" "$EVID/H/linux-selftest-bar.txt" "$EVID/H/count-gate-linux.txt" "$EVID/H/leg12-summary.txt"; } > "$EVID/H/run-identity-linux.txt" || i=$?; [ "$i" -eq 0 ] && [ -s "$EVID/H/run-identity-linux.txt" ] || STOP
s=0; git status --porcelain > "$EVID/H/status-post-4.txt" || s=$?; [ "$s" -eq 0 ] && [ ! -s "$EVID/H/status-post-4.txt" ] || STOP; [ "$(git rev-parse HEAD)" = "$H" ] || STOP
s=0; git -C "$MAIN" status --porcelain -- . ':(exclude).relays' ':(exclude)docs/sprints' > "$EVID/status-main-post-4.txt" || s=$?; [ "$s" -eq 0 ] || STOP; d=0; diff "$EVID/status-initial.txt" "$EVID/status-main-post-4.txt" > "$EVID/status-main-post-4.delta" || d=$?; [ "$d" -eq 0 ] || STOP
exit 0
```

### Task 5 — fence proofs at H; the census of record at the BRANCH HEAD (B and H produced in-token, equal to each other and to the record of the pin); the IMPL return

- [ ] **Step 1: V-LS proofs** — numstat B→H == the four paths (V-LS-1); the diff over `adapter.hpp`, `secure_io.*`, the two adapter `.hpp`s, `src/core`, `src/cli`, `harness`, `.github`, the CMake files, `tests/fixtures` EMPTY; `hunkwin.py`: every claude hunk inside old-side windows 197–198 (the head reader insertion) and 654–672 (the collect candidate path), every codex hunk inside 228–270 (`inspect_rollout_head`) and 1273–1291 (the collect candidate path) — the discover bodies (claude :570, codex :1155), the sqlite enrichment (codex :1117) and the install side are outside every window; occurrence counts equal at B and H for `sqlite3_` and `threads` (V-LS-3), `SessionIdWithoutId:` (S-LS-3), `has_terminal_tail_record(*text)` / `newest_rollout_timestamp(*text)` / `auto text = source_text(*source);` (V-LS-4 — the tail facts keep their full-text inputs), `no_cwd_record.push_back`, `auto main_text = source_text(*main_source);`, `apply_torn_tail_rule(…)`, the `inspect_transcript` signature (unchanged install-side parser); the two head readers present exactly once each → `fence-greps.txt`.
- [ ] **Step 2: the census at B and at H** — for each: the tree arm `git grep -n -E <alternation> <sha> -- .` reduced to `path:line` in `git grep`'s own order; the history arm `git rev-list <sha> | xargs git grep -l -E <alternation>` (two producers, a file between them) reduced with `LC_ALL=C sort -u`; the raw outputs under `census-raw/` (EXCLUDED from the record); `diff` tree B vs H EMPTY and history B vs H EMPTY (the act adds no location; the nine SECTIONs carry no credential-shaped string); B's tree rows == the record's `path:line` rows and B's history paths == the record's history paths (the classification A=3 / B=64 / C=2 inherited by equality) → `census-summary.txt`.
- [ ] **Step 3: the IMPL return** — the receipts listed (`receipts-root.txt`, `receipts-B.txt`, `receipts-H.txt`); no-mutation proofs; the implementer files the IMPL return TO the pair Planner; no push.

<!-- RUN: task-5 -->
```bash
# Runner plumbing (Task 5)
WORKTREE=/Users/jack/Programming/bivpak-intg-r449-line1-selection
MAIN=/Users/jack/Programming/bivpak
B=4cf135ee97f57021c5fc5fd5343de6f655fb0d24
cd "$WORKTREE" || STOP
v=0; (cd "$EVID" && shasum -a 256 -c helpers.sha256 > helpers.verify-5.txt 2>&1) || v=$?; [ "$v" -eq 0 ] || STOP
H=$(cat "$EVID/H.txt") || STOP; e=0; git cat-file -e "${H}^{commit}" || e=$?; [ "$e" -eq 0 ] || STOP; [ "$(git rev-parse HEAD)" = "$H" ] && [ "$(git rev-parse "${H}^")" = "$B" ] || STOP
# Step 1
r=0; git diff --numstat "$B" "$H" > "$EVID/fence-touched.numstat" || r=$?; [ "$r" -eq 0 ] && [ -s "$EVID/fence-touched.numstat" ] || STOP; s=0; awk '{print $3}' "$EVID/fence-touched.numstat" > "$EVID/fence-touched.paths" || s=$?; [ "$s" -eq 0 ] || STOP; o=0; LC_ALL=C sort "$EVID/fence-touched.paths" > "$EVID/fence-touched.sorted" || o=$?; [ "$o" -eq 0 ] || STOP; d=0; diff "$EVID/touched.expected" "$EVID/fence-touched.sorted" > "$EVID/fence-touched.delta" || d=$?; [ "$d" -eq 0 ] || STOP
d=0; git diff --quiet "$B" "$H" -- src/adapters/adapter.hpp src/adapters/secure_io.cpp src/adapters/secure_io.hpp src/adapters/claude_code/claude_code.hpp src/adapters/codex/codex.hpp src/core src/cli harness .github CMakeLists.txt CMakePresets.json tests/fixtures tests/CMakeLists.txt || d=$?; [ "$d" -eq 0 ] || STOP
for q in src/adapters/claude_code/claude_code.cpp src/adapters/codex/codex.cpp; do w=0; git show "${H}:${q}" > "$EVID/H-$(basename "$q")" || w=$?; [ "$w" -eq 0 ] && [ -s "$EVID/H-$(basename "$q")" ] || STOP; done
r=0; git diff -U0 "$B" "$H" -- src/adapters/claude_code/claude_code.cpp > "$EVID/claude-H.diff" || r=$?; [ "$r" -eq 0 ] && [ -s "$EVID/claude-H.diff" ] || STOP; h=0; python3 "$EVID/hunkwin.py" "$EVID/claude-H.diff" 197-198,654-672 > "$EVID/claude-H.hunks.txt" || h=$?; [ "$h" -eq 0 ] && [ -s "$EVID/claude-H.hunks.txt" ] || STOP
r=0; git diff -U0 "$B" "$H" -- src/adapters/codex/codex.cpp > "$EVID/codex-H.diff" || r=$?; [ "$r" -eq 0 ] && [ -s "$EVID/codex-H.diff" ] || STOP; h=0; python3 "$EVID/hunkwin.py" "$EVID/codex-H.diff" 228-270,1273-1291 > "$EVID/codex-H.hunks.txt" || h=$?; [ "$h" -eq 0 ] && [ -s "$EVID/codex-H.hunks.txt" ] || STOP
: > "$EVID/fence-greps.txt"; for pat in 'sqlite3_' 'threads' 'SessionIdWithoutId:' 'has_terminal_tail_record(*text)' 'newest_rollout_timestamp(*text)' 'auto text = source_text(*source);'; do g=0; kb=$(grep -c -F -- "$pat" "$EVID/base-codex.cpp") || g=$?; [ "$g" -eq 0 ] || STOP; g=0; kh=$(grep -c -F -- "$pat" "$EVID/H-codex.cpp") || g=$?; [ "$g" -eq 0 ] || STOP; printf 'codex %s base=%s H=%s\n' "$pat" "$kb" "$kh" >> "$EVID/fence-greps.txt"; [ "$kb" -eq "$kh" ] || STOP; done
for pat in 'no_cwd_record.push_back' 'auto main_text = source_text(*main_source);' 'apply_torn_tail_rule(artifacts, artifact_sources, live.live, torn_tails);' 'TranscriptFacts inspect_transcript(const std::string_view transcript) {'; do g=0; kb=$(grep -c -F -- "$pat" "$EVID/base-claude_code.cpp") || g=$?; [ "$g" -eq 0 ] || STOP; g=0; kh=$(grep -c -F -- "$pat" "$EVID/H-claude_code.cpp") || g=$?; [ "$g" -eq 0 ] || STOP; printf 'claude %s base=%s H=%s\n' "$pat" "$kb" "$kh" >> "$EVID/fence-greps.txt"; [ "$kb" -eq "$kh" ] || STOP; done
g=0; k=$(grep -c -F -- 'first_transcript_cwd(*main_source)' "$EVID/H-claude_code.cpp") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP; g=0; k=$(grep -c -F -- 'inspect_rollout_head_stream(*source)' "$EVID/H-codex.cpp") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP; g=0; k=$(grep -c -F -- 'has_terminal_tail_record(*text)' "$EVID/H-codex.cpp") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP; printf 'head_readers_present=2 tail_fact_full_text_site=1\n' >> "$EVID/fence-greps.txt"
# Step 2
ALT='sk-[A-Za-z0-9]{8,}|-----BEGIN [A-Z ]*PRIVATE KEY|AKIA[0-9A-Z]{16}|ghp_[A-Za-z0-9]{20,}|xox[abprs]-'
for L in B H; do if [ "$L" = B ]; then X=$B; else X=$H; fi; r=0; git grep -n -E "$ALT" "$X" -- . > "$EVID/census-raw/tree-$L.raw" || r=$?; [ "$r" -le 1 ] || STOP; s=0; sed -E 's/^[0-9a-f]{40}://' "$EVID/census-raw/tree-$L.raw" > "$EVID/census-raw/tree-$L.stripped" || s=$?; [ "$s" -eq 0 ] || STOP; s=0; sed -E 's/^([^:]+:[0-9]+):.*$/\1/' "$EVID/census-raw/tree-$L.stripped" > "$EVID/census-tree-$L.txt" || s=$?; [ "$s" -eq 0 ] || STOP; r=0; git rev-list "$X" > "$EVID/census-raw/rl-$L.txt" || r=$?; [ "$r" -eq 0 ] && [ -s "$EVID/census-raw/rl-$L.txt" ] || STOP; x=0; xargs git grep -l -E "$ALT" < "$EVID/census-raw/rl-$L.txt" > "$EVID/census-raw/hist-$L.raw" || x=$?; [ "$x" -le 1 ] || STOP; s=0; sed -E 's/^[0-9a-f]{40}://' "$EVID/census-raw/hist-$L.raw" > "$EVID/census-raw/hist-$L.paths" || s=$?; [ "$s" -eq 0 ] || STOP; o=0; LC_ALL=C sort -u "$EVID/census-raw/hist-$L.paths" > "$EVID/census-history-$L.txt" || o=$?; [ "$o" -eq 0 ] || STOP; done
d=0; diff "$EVID/census-tree-B.txt" "$EVID/census-tree-H.txt" > "$EVID/census-tree.delta" || d=$?; [ "$d" -eq 0 ] || STOP
d=0; diff "$EVID/census-history-B.txt" "$EVID/census-history-H.txt" > "$EVID/census-history.delta" || d=$?; [ "$d" -eq 0 ] || STOP
REC=$MAIN/docs/sprints/2026-08-27-intg-consent-fabric/results/intg-r450-main-head-census-20260913.txt; [ -s "$REC" ] || STOP
g=0; grep -E '^[A-Za-z0-9_./-]+:[0-9]+ \| [ABC]' "$REC" > "$EVID/census-raw/record-tree.rows" || g=$?; [ "$g" -eq 0 ] || STOP; s=0; sed -E 's/ \| .*$//' "$EVID/census-raw/record-tree.rows" > "$EVID/census-record-tree.txt" || s=$?; [ "$s" -eq 0 ] && [ -s "$EVID/census-record-tree.txt" ] || STOP
d=0; diff "$EVID/census-record-tree.txt" "$EVID/census-tree-B.txt" > "$EVID/census-record-tree.delta" || d=$?; [ "$d" -eq 0 ] || STOP
a=0; awk '/^== HISTORY ARM/ { f = 1; next } /^== PRODUCT-SCOPED/ { f = 0 } f && /^[A-Za-z0-9_./-]+$/ { print }' "$REC" > "$EVID/census-record-history.txt" || a=$?; [ "$a" -eq 0 ] && [ -s "$EVID/census-record-history.txt" ] || STOP; d=0; diff "$EVID/census-record-history.txt" "$EVID/census-history-B.txt" > "$EVID/census-record-history.delta" || d=$?; [ "$d" -eq 0 ] || STOP
a=0; nt=$(awk 'END { print NR }' "$EVID/census-tree-H.txt") || a=$?; nh=$(awk 'END { print NR }' "$EVID/census-history-H.txt") || a=$?; [ "$a" -eq 0 ] || STOP; w=0; printf 'census_at=%s tree_rows=%s history_paths=%s delta_vs_B=empty delta_B_vs_record_of_4cf135ee=empty classes=inherited_from_record(A=3,B=64,C=2) matched_text_in_record=none collation=LC_ALL=C\n' "$H" "$nt" "$nh" > "$EVID/census-summary.txt" || w=$?; [ "$w" -eq 0 ] && [ -s "$EVID/census-summary.txt" ] || STOP
# Step 3
l=0; ls -1 "$EVID" > "$EVID/receipts-root.txt" || l=$?; [ "$l" -eq 0 ] || STOP; l=0; ls -1 "$EVID/B" > "$EVID/receipts-B.txt" || l=$?; [ "$l" -eq 0 ] || STOP; l=0; ls -1 "$EVID/H" > "$EVID/receipts-H.txt" || l=$?; [ "$l" -eq 0 ] || STOP
s=0; git status --porcelain > "$EVID/H/status-post-5.txt" || s=$?; [ "$s" -eq 0 ] && [ ! -s "$EVID/H/status-post-5.txt" ] || STOP; [ "$(git rev-parse HEAD)" = "$H" ] || STOP
s=0; git -C "$MAIN" status --porcelain -- . ':(exclude).relays' ':(exclude)docs/sprints' > "$EVID/status-main-post-5.txt" || s=$?; [ "$s" -eq 0 ] || STOP; d=0; diff "$EVID/status-initial.txt" "$EVID/status-main-post-5.txt" > "$EVID/status-main-post-5.delta" || d=$?; [ "$d" -eq 0 ] || STOP
exit 0
```

### Task 6 — the vehicle (ONLY after the pair Planner's verification of the Task 5 return + m-2's byte review at H through master with no red + the pair Planner's relay addressed to the implementer): push the branch, open the PR

- [ ] **Step 1: preconditions** — HEAD == H; `H^` == B; one push URL; no remote head `intg/r449-line1-selection`; the repository PRIVATE; no executable pre-push hook; the six deltas EMPTY (census tree/history B-vs-H, census B-vs-record tree/history, membership macOS, membership Linux); the LEG 1/2 verdict rc 0; both count-gate rc files 0; the macOS ctest rc 0; the Linux bar in an admitted outcome; the shell recorded.
- [ ] **Step 2: ONE push** — `git push --dry-run --no-tags origin intg/r449-line1-selection` (the refspec line present exactly once) then the one attempt; the class recorded; class a (remote head == H) or STOP.
- [ ] **Step 3: the PR** — `pr-body.md` from the record files (the fence pin, the rulings relay, the plan lock, B, H, the numstat, the count-gate rows, the LEG 1/2 summary, the LEG 3 cost receipt, the Linux bar line, the census summary, the owner-review-pending sentence, the vehicle sentence; no red remote CI cited), token-scanned; `gh pr create --base main --head intg/r449-line1-selection`; no label, no reviewer request, no draft toggling, no comment.

<!-- RUN: task-6 -->
```bash
# Runner plumbing (Task 6)
WORKTREE=/Users/jack/Programming/bivpak-intg-r449-line1-selection
MAIN=/Users/jack/Programming/bivpak
B=4cf135ee97f57021c5fc5fd5343de6f655fb0d24
cd "$WORKTREE" || STOP
v=0; (cd "$EVID" && shasum -a 256 -c helpers.sha256 > helpers.verify-6.txt 2>&1) || v=$?; [ "$v" -eq 0 ] || STOP
# Step 1
H=$(cat "$EVID/H.txt") || STOP; [ "$(git rev-parse HEAD)" = "$H" ] && [ "$(git rev-parse "${H}^")" = "$B" ] || STOP
u=0; git remote get-url --push --all origin > "$EVID/push-url.txt" || u=$?; [ "$u" -eq 0 ] && [ -s "$EVID/push-url.txt" ] || STOP; a=0; n=$(awk 'END { print NR }' "$EVID/push-url.txt") || a=$?; [ "$a" -eq 0 ] && [ "$n" -eq 1 ] || STOP
l=0; git ls-remote --heads origin intg/r449-line1-selection > "$EVID/remote-branch-before.txt" || l=$?; [ "$l" -eq 0 ] && [ ! -s "$EVID/remote-branch-before.txt" ] || STOP
v=0; gh repo view --json visibility -q .visibility > "$EVID/visibility.txt" || v=$?; [ "$v" -eq 0 ] && [ "$(cat "$EVID/visibility.txt")" = PRIVATE ] || STOP
[ ! -x "$(git rev-parse --git-path hooks/pre-push)" ] || STOP
for f in census-tree.delta census-history.delta census-record-tree.delta census-record-history.delta H/membership.delta H/membership-linux.delta; do [ -f "$EVID/$f" ] && [ ! -s "$EVID/$f" ] || STOP; done
[ "$(cat "$EVID/H/leg12-verdict.rc")" = leg12_rc=0 ] && [ "$(cat "$EVID/H/count-gate-macos.rc")" = count_gate_macos_rc=0 ] && [ "$(cat "$EVID/H/count-gate-linux.rc")" = count_gate_linux_rc=0 ] && [ "$(cat "$EVID/H/ctest-macos-H.rc")" = ctest_macos_H_rc=0 ] || STOP
g=0; k=$(grep -c -E ' bar=(pass-green|pass-r435-disclosed-registered-red)$' "$EVID/H/linux-selftest-bar.txt") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP
printf '%s %s\n' "$0" "${ZSH_VERSION:-${BASH_VERSION:-unknown}}" > "$EVID/shell.txt"
# Step 2
y=0; git push --dry-run --no-tags origin intg/r449-line1-selection > "$EVID/push-dry.txt" 2>&1 || y=$?; [ "$y" -eq 0 ] || STOP
g=0; k=$(grep -c -F 'intg/r449-line1-selection -> intg/r449-line1-selection' "$EVID/push-dry.txt") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP
p=0; git push --no-tags origin intg/r449-line1-selection > "$EVID/push-stdout.txt" 2> "$EVID/push-stderr.txt" || p=$?; printf 'push_rc=%s\n' "$p" > "$EVID/push-rc.txt"
o=0; git ls-remote --heads origin intg/r449-line1-selection > "$EVID/remote-branch-after.txt" || o=$?; remote_after=$(cut -f1 "$EVID/remote-branch-after.txt")
if [ "$o" -ne 0 ]; then class=d; elif [ "$p" -eq 0 ] && [ "$remote_after" = "$H" ]; then class=a; elif [ "$p" -eq 0 ]; then class=e; elif [ "$remote_after" = "$H" ]; then class=c; elif [ -z "$remote_after" ]; then class=b; else class=e; fi; printf 'class=%s\n' "$class" > "$EVID/push-class.txt"
[ "$class" = a ] || STOP
# Step 3
w=0; { printf '%s\n\n' 'R-4.49 line-1 selection (m-2 fence 142000 §2 / rev2 144700; the operator grant 152118 "lets fix both please", 2 of 2): candidacy in both collect paths is decided from a HEAD-BOUNDED streamed read that stops at the predicate today'"'"'s parsers already implement — the FIRST cwd-bearing record for claude (sealed ADDENDUM-1 §A1; no cwd anywhere = whole file + no_cwd_record, sealed) and the FIRST session_meta record for codex (sealed c1 §4) — and the whole-file read + the unchanged whole-text parsers run only for an in-root candidate. m-2 C-1/C-2 rulings (DESIGN-m2-planner-20260913-170000): selection identity by construction; the act is read-bounding only. ONE commit; SECTIONs inside existing TEST_CASEs (case census unchanged).'; printf 'Design pin: m2-r450-discover-fence-rev2-20260903 sha256 f2216ee606a03b0b5b0b7f4562fed52a7349219c28990e6ee3e89b0cc25e8c6f\nPlan pin: intg-r449-line1-selection-plan-20260913 sha256 %s\n\n' "$(cat "$RUNNERS/plan-lock.txt")"; printf 'B=%s (origin/main, the R-4.50 landing merge)\nH=%s (H^ = B)\n\n' "$B" "$H"; printf 'H touched (numstat):\n'; cat "$EVID/H/touched.numstat"; printf '\nCOUNT-GATE (the ten OverallResultsCases cells: literal at B == observed at B == observed at H):\n'; cat "$EVID/H/count-gate-macos.txt" "$EVID/H/count-gate-linux.txt"; printf '\nLEG 1 / LEG 2 (bytes read per store file, strace in the Linux parity container, B vs H over the synthetic store S):\n'; cat "$EVID/H/leg12-summary.txt"; printf '\nLEG 3 (whole-record membership identity over S at B and at H, macOS and Linux: deltas empty) and the cost receipt:\n'; cat "$EVID/H/cost-receipt.txt"; printf '\nLinux acceptance at H (two-outcome bar):\n'; cat "$EVID/H/linux-selftest-bar.txt"; printf '\nCensus at the branch head (both arms; paths only):\n'; cat "$EVID/census-summary.txt"; printf '\nOwner review: m-2 V-LS-1..6 byte review at H returns through master BEFORE any merge packet; the four-condition merge bar and the operator'"'"'s condition-4 token follow.\n\nThis PR is the vehicle under R-4.51 clause (2); the evidence of record is the local suites on both targets, the Docker parity leg, the three-leg witness, the owner byte review and the operator'"'"'s token — a red remote CI is cited nowhere. Merge is local under the operator'"'"'s token; the landing push of main follows under the R-4.52 landing rule as the merge packet'"'"'s own step.\n'; } > "$EVID/pr-body.md" || w=$?; [ "$w" -eq 0 ] && [ -s "$EVID/pr-body.md" ] || STOP
g=0; k=$(grep -c -E 'sk-[A-Za-z0-9]{8,}|-----BEGIN [A-Z ]*PRIVATE KEY|AKIA[0-9A-Z]{16}|ghp_[A-Za-z0-9]{20,}|xox[abprs]-' "$EVID/pr-body.md") || g=$?; [ "$g" -eq 1 ] && [ "$k" -eq 0 ] || STOP
q=0; gh pr create --base main --head intg/r449-line1-selection --title "adapters(claude, codex): decide candidacy from a head-bounded read; full reads only for selected sessions (R-4.49)" --body-file "$EVID/pr-body.md" > "$EVID/pr.txt" 2>&1 || q=$?; printf 'pr_rc=%s\n' "$q" > "$EVID/pr.rc"; [ "$q" -eq 0 ] && [ -s "$EVID/pr.txt" ] || STOP
exit 0
```

### Task 7 — FINALIZE the tracked record `results/r449-<token>/` (the evidence-of-record SET = the home MINUS the declared SCRATCH: `work/`, `census-raw/`, the strace traces, the finalizer's own receipts), manifest, the SITREP UP

- [ ] **Step 1: preconditions** — Task 6 done/exit/proof receipts present; push class a; PR created; the results dir absent.
- [ ] **Step 2: the set** — `finalize.py list` → `final-set.txt` (no `work/`, `census-raw/` or strace path in it — proven).
- [ ] **Step 3: the copy** — the set copied path-for-path under `results/r449-<token>/`.
- [ ] **Step 4: manifest + verdict** — `SHA256SUMS` (`LC_ALL=C sort -k2`), `finalize.py check` rc 0, `shasum -c` rc 0, the record token-scanned with the full alternation (0 hits) → `final-record.txt`; the pair Planner commits the record path-scoped, no trailer.

<!-- RUN: task-7 -->
```bash
# Runner plumbing (Task 7)
WORKTREE=/Users/jack/Programming/bivpak-intg-r449-line1-selection
MAIN=/Users/jack/Programming/bivpak
cd "$WORKTREE" || STOP
v=0; (cd "$EVID" && shasum -a 256 -c helpers.sha256 > helpers.verify-7.txt 2>&1) || v=$?; [ "$v" -eq 0 ] || STOP
# Step 1
[ -s "$EVID/runners/task-6.done" ] && [ "$(cat "$EVID/runners/task-6.done")" = rc=0 ] || STOP; [ -s "$EVID/runners/task-6.exit" ] && [ "$(cat "$EVID/runners/task-6.exit")" = rc=0 ] || STOP; [ -s "$EVID/runners/proof-6.tail" ] && [ -s "$EVID/runners/plan_blocks.sha256-6" ] || STOP
[ -s "$EVID/push-class.txt" ] && [ "$(cat "$EVID/push-class.txt")" = class=a ] || STOP; [ -s "$EVID/pr.rc" ] && [ "$(cat "$EVID/pr.rc")" = pr_rc=0 ] || STOP
TOKEN=$(sed -n 's/^token=//p' "$EVID/token.txt"); [ -n "$TOKEN" ] || STOP; RESDIR=$MAIN/docs/sprints/2026-08-27-intg-consent-fabric/results/r449-${TOKEN}; [ ! -e "$RESDIR" ] || STOP
# Step 2
x=0; python3 "$EVID/finalize.py" list "$EVID" > "$RUNNERS/final-set.txt" || x=$?; [ "$x" -eq 0 ] && [ -s "$RUNNERS/final-set.txt" ] || STOP; a=0; n=$(awk 'END { print NR }' "$RUNNERS/final-set.txt") || a=$?; [ "$a" -eq 0 ] && [ "$n" -ge 1 ] || STOP
g=0; k=$(grep -c -E '^(work/|census-raw/|B/strace-B\.log$|H/strace-H\.log$)' "$RUNNERS/final-set.txt") || g=$?; [ "$g" -eq 1 ] && [ "$k" -eq 0 ] || STOP
# Step 3
m=0; mkdir -p "$RESDIR" || m=$?; [ "$m" -eq 0 ] && [ -d "$RESDIR" ] || STOP
c=0; while IFS= read -r f; do d=$(dirname "$f") && mkdir -p "$RESDIR/$d" && cp -p "$EVID/$f" "$RESDIR/$f" || { c=1; break; }; done < "$RUNNERS/final-set.txt"; [ "$c" -eq 0 ] || STOP
# Step 4
h=0; (cd "$RESDIR" && find . -type f ! -name SHA256SUMS -exec shasum -a 256 {} + > "$RUNNERS/final-manifest.unsorted") || h=$?; [ "$h" -eq 0 ] && [ -s "$RUNNERS/final-manifest.unsorted" ] || STOP; o=0; LC_ALL=C sort -k2 "$RUNNERS/final-manifest.unsorted" > "$RESDIR/SHA256SUMS" || o=$?; [ "$o" -eq 0 ] && [ -s "$RESDIR/SHA256SUMS" ] || STOP
k=0; python3 "$EVID/finalize.py" check "$EVID" "$RESDIR" "$RESDIR/SHA256SUMS" > "$RUNNERS/final-verdict.txt" 2>&1 || k=$?; printf 'finalize_check_rc=%s\n' "$k" > "$RUNNERS/final-verdict.rc"; [ "$k" -eq 0 ] && [ -s "$RUNNERS/final-verdict.txt" ] || STOP
v=0; (cd "$RESDIR" && shasum -a 256 -c --quiet SHA256SUMS) > "$RUNNERS/final-shasum-c.txt" 2>&1 || v=$?; printf 'shasum_c_rc=%s\n' "$v" > "$RUNNERS/final-shasum-c.rc"; [ "$v" -eq 0 ] || STOP
g=0; k=$(grep -r -l -E 'sk-[A-Za-z0-9]{8,}|-----BEGIN [A-Z ]*PRIVATE KEY|AKIA[0-9A-Z]{16}|ghp_[A-Za-z0-9]{20,}|xox[abprs]-' "$RESDIR" > "$RUNNERS/final-token-scan.txt") || g=$?; [ "$g" -eq 1 ] && [ ! -s "$RUNNERS/final-token-scan.txt" ] || STOP
w=0; printf 'results_dir=%s set=%s finalize_check_rc=0 shasum_c_rc=0 token_scan_hits=0\n' "$RESDIR" "$n" > "$RUNNERS/final-record.txt" || w=$?; [ "$w" -eq 0 ] && [ -s "$RUNNERS/final-record.txt" ] || STOP
exit 0
```

## Instruments (BLOCKs)

**`cells.py`** (unchanged from R-4.50):

<!-- BLOCK: cells.py -->
```python
#!/usr/bin/env python3
# usage: cells.py <s2-harness.yml>   — prints the ten count-gate cells (+ the macOS expected_skips names), read from the bytes
import re, sys
text = open(sys.argv[1], encoding="utf-8").read()
starts = [m.start() for m in re.finditer(r"checks = \{", text)]
if len(starts) != 2:
    sys.exit(2)  # exactly one macOS block and one Linux block
bounds = starts + [len(text)]
for target, (lo, hi) in zip(("macos", "linux"), zip(starts, bounds[1:])):
    region = text[lo:hi]
    end = re.search(r"\n {10}\}\n", region)  # the block closer at the workflow's indentation
    if end is None:
        sys.exit(2)
    checks = region[:end.start()]
    cells = re.findall(r'"(biv_[a-z_]+)": \{\s*"successes": (\d+),\s*"failures": (\d+),\s*"expectedFailures": (\d+),\s*"skips": (\d+),', checks)
    if len(cells) != 5:
        sys.exit(3)
    for binary, s, f, e, k in cells:
        print(f"{binary} {target} successes={s} failures={f} expectedFailures={e} skips={k}")
    skips = re.search(r"expected_skips = \{(.*?)\}", region[end.end():], re.S)
    names = re.findall(r'"([^"]+)"', skips.group(1)) if skips else []
    print(f"expected_skips {target} {'n=' + str(len(names)) if skips else 'absent'} " + " | ".join(names))
```

**`tuples.py`** (unchanged):

<!-- BLOCK: tuples.py -->
```python
#!/usr/bin/env python3
# usage: tuples.py <target> <xml>...  — one line per XML: binary target successes failures expectedFailures skips xml_sha256; then the biv_tests skip set
import hashlib, os, sys, xml.etree.ElementTree as ET
target = sys.argv[1]
skips = None
for xml_path in sys.argv[2:]:
    binary = os.path.basename(xml_path).split("-")[0]
    data = open(xml_path, "rb").read()
    if not data:
        sys.exit(2)
    cases = ET.fromstring(data).find("OverallResultsCases")
    if cases is None:
        sys.exit(3)
    tuple_ = " ".join(f"{k}={cases.get(k, '0')}" for k in ("successes", "failures", "expectedFailures", "skips"))
    print(f"{binary} {target} {tuple_} xml_sha256={hashlib.sha256(data).hexdigest()}")
    if binary == "biv_tests":
        skips = sorted(tc.get("name") for tc in ET.fromstring(data).iter("TestCase") if tc.find("Skip") is not None)
if skips is None:
    sys.exit(4)
print(f"expected_skips_observed {target} n={len(skips)} " + " | ".join(skips))
```

**`cellgate.py`** (the count-gate proof on one target):

<!-- BLOCK: cellgate.py -->
```python
#!/usr/bin/env python3
# usage: cellgate.py <B-cells.txt> <target> <tuples-B-<target>.txt> <tuples-H-<target>.txt>  — the COUNT-GATE proof on one target: exit 0 iff for
# each of the five binaries the literal cell at B (the workflow's bytes), the tuple OBSERVED at B and the tuple OBSERVED at H are all EQUAL
# (successes, failures, expectedFailures, skips). A difference = exit 5 (each row printed) — a STOP UP in this act, never a transcription.
import sys
def rows(path, target):
    out = {}
    for line in open(path, encoding="utf-8"):
        p = line.split()
        if len(p) >= 6 and p[0].startswith("biv_") and p[1] == target and p[2].startswith("successes="):
            out[p[0]] = tuple(x.split("=", 1)[1] for x in p[2:6])
    return out
target = sys.argv[2]
lit, ob, oh = rows(sys.argv[1], target), rows(sys.argv[3], target), rows(sys.argv[4], target)
if len(lit) != 5 or set(lit) != set(ob) or set(lit) != set(oh):
    print("MALFORMED literal=%d observed_B=%d observed_H=%d" % (len(lit), len(ob), len(oh))); sys.exit(2)
bad = 0
for b in sorted(lit):
    ok = lit[b] == ob[b] == oh[b]; bad += 0 if ok else 1
    print("%s %s literal_B=%s observed_B=%s observed_H=%s equal=%s" % (b, target, lit[b], ob[b], oh[b], "yes" if ok else "NO"))
sys.exit(0 if bad == 0 else 5)
```

**`skipset.py`** (unchanged):

<!-- BLOCK: skipset.py -->
```python
#!/usr/bin/env python3
# usage: skipset.py <B-cells.txt> <tuples-<target>.txt> <target>  — exit 0 iff the biv_tests skipped-name SET (and count)
# observed on <target> equals B's expected_skips names for <target>; membership only — the two producers order names differently
# by construction (cells.py: the workflow's listing order; tuples.py: sorted). exit 5 = a set/count difference; exit 2 = a line missing.
import sys
def names(path, prefix):
    for line in open(path, encoding="utf-8"):
        parts = line.rstrip("\n").split(" ", 3)
        if len(parts) >= 3 and parts[0] == prefix and parts[1] == sys.argv[3]:
            n = int(parts[2].split("=", 1)[1])
            rest = parts[3] if len(parts) == 4 else ""
            return n, frozenset(x.strip() for x in rest.split("|") if x.strip())
    return None
expected = names(sys.argv[1], "expected_skips")
observed = names(sys.argv[2], "expected_skips_observed")
if expected is None or observed is None:
    sys.exit(2)
(n_e, s_e), (n_o, s_o) = expected, observed
print(f"expected n={n_e} observed n={n_o} same_set={'yes' if s_e == s_o else 'no'} only_in_B={sorted(s_e - s_o)} only_in_observed={sorted(s_o - s_e)}")
sys.exit(0 if (n_e == n_o == len(s_e) and s_e == s_o) else 5)
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

**`finalize.py`** (SCRATCH extended — R-4.53 arm (a): `work`, `census-raw`, `strace-*.log`):

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
SCRATCH = (re.compile(r"^work$"), re.compile(r"^census-raw$"), re.compile(r"^strace-[HB]\.log$"), re.compile(r"^llvm22-assets-[HB]\.[A-Za-z0-9]+$"),
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

**`synth_store.py`** (six classes; per-file manifest with `head_end`):

<!-- BLOCK: synth_store.py -->
```python
#!/usr/bin/env python3
# synth_store.py <work> <seed> — builds the LARGE SYNTHETIC STORE pair S for LEG 1/2/3 (real-store SCALE, synthetic CONTENT), deterministic
# from <seed>, INSIDE <work> at locator values (m-3 C-2 rule 3): <work>/codex-home/sessions/2026/09/13/rollout-*.jsonl and
# <work>/claude-config/projects/<key>/<uuid>.jsonl. Exactly K of each agent carry cwd == <work>/ws/proj (the SELECTED set); every other file
# is out of the source root or carries no cwd. Ids are minted from the seed (never a POISON_SESSION_IDS value — proven by the runner, rule 1).
# CLASSES (per-file manifest row: path relative to <work>, agent, class, selected, size, head_end = byte offset just past the '\n' of the
# line that COMPLETES the head predicate — first cwd-bearing record (claude, A1 §A1) / first session_meta record (codex, c1 §4) — or null
# when no line completes it, i.e. the sealed whole-file case):
#   codex-bulk                 N_CODEX rollouts, line 1 = session_meta (+cwd); body BODY_CODEX bytes; K in root, the rest out of root
#   codex-garbage-line1        N_CODEX_GARBAGE out-of-root rollouts, line 1 unparseable, line 2 = session_meta        (head_end = end of line 2)
#   codex-no-meta              N_CODEX_NOMETA rollouts with NO session_meta anywhere                                   (head_end = null; not a candidate, silent — today's disposition)
#   claude-bulk                N_CLAUDE transcripts, lines 1-4 metadata without cwd, line 5 the first cwd-bearing record (the REAL shape,
#                              A1 FX-M06) with sessionId+version; body BODY_CLAUDE bytes; K in root, the rest out of root  (head_end = end of line 5)
#   claude-cwd-no-enrichment   N_CLAUDE_NOENRICH out-of-root transcripts whose FIRST cwd-bearing record (line 1) carries NO sessionId/version
#                              and whose body never carries them either — the implementer's O-1 counterexample: a reader that waits for the
#                              enrichment fields reads these to EOF; the first-cwd reader stops at line 1              (head_end = end of line 1)
#   claude-no-cwd              N_CLAUDE_NOCWD transcripts IN the source project directory with no cwd anywhere        (head_end = null; whole file, no_cwd_record — sealed)
# No credential-shaped string is ever written. S is NOT committed: it lives under $EVID/work, excluded from the evidence-of-record set.
import json, os, random, sys, uuid
N_CODEX, N_CODEX_GARBAGE, N_CODEX_NOMETA = 1500, 20, 10
N_CLAUDE, N_CLAUDE_NOENRICH, N_CLAUDE_NOCWD = 100, 10, 5
K = 3
BODY_CODEX, BODY_CLAUDE, BODY_NOCWD = 256 * 1024, 4 * 1024 * 1024, 1024 * 1024
def project_key(path):
    return "-" + path.strip("/").replace("/", "-")
def write_lines(path, head_lines, body_line, body_bytes, complete_index):
    """writes head_lines then body_line repeated to >= body_bytes; returns (size, head_end) where head_end is the offset just past head_lines[complete_index] (None if complete_index is None)"""
    os.makedirs(os.path.dirname(path), exist_ok=True)
    head_end = None
    with open(path, "w", encoding="utf-8") as f:
        off = 0
        for i, line in enumerate(head_lines):
            f.write(line); off += len(line.encode("utf-8"))
            if complete_index is not None and i == complete_index:
                head_end = off
        n = body_bytes // len(body_line.encode("utf-8")) + 1
        for _ in range(n):
            f.write(body_line)
    return os.path.getsize(path), head_end
def main(work, seed):
    rnd = random.Random(seed)
    def uid():
        return str(uuid.UUID(int=rnd.getrandbits(128), version=4))
    ws = os.path.join(work, "ws", "proj"); os.makedirs(ws, exist_ok=True)
    other = os.path.join(work, "elsewhere", "proj")
    rows = []; selected = {"codex": [], "claude": []}
    def row(path, agent, cls, sel, size, head_end):
        rows.append({"path": os.path.relpath(path, work), "agent": agent, "class": cls, "selected": sel, "size": size, "head_end": head_end})
    codex_dir = os.path.join(work, "codex-home", "sessions", "2026", "09", "13")
    def meta(sid, cwd, i):
        return json.dumps({"timestamp": "2026-09-13T00:%02d:%02dZ" % (i // 60 % 60, i % 60), "type": "session_meta",
                           "payload": {"id": sid, "session_id": sid, "cwd": cwd, "cli_version": "0.142.5"}}) + "\n"
    turn = json.dumps({"timestamp": "2026-09-13T00:00:00Z", "type": "response_item", "payload": {"type": "message", "role": "assistant", "content": [{"type": "output_text", "text": "x" * 1000}]}}) + "\n"
    for i in range(N_CODEX):
        sid = uid(); sel = i < K; cwd = ws if sel else other
        if sel: selected["codex"].append(sid)
        p = os.path.join(codex_dir, "rollout-2026-09-13T00-00-00-%s.jsonl" % sid)
        size, he = write_lines(p, [meta(sid, cwd, i)], turn, BODY_CODEX, 0); row(p, "codex", "codex-bulk", sel, size, he)
    for i in range(N_CODEX_GARBAGE):
        sid = uid(); p = os.path.join(codex_dir, "rollout-2026-09-13T00-01-00-%s.jsonl" % sid)
        size, he = write_lines(p, ["not json at all\n", meta(sid, other, i)], turn, BODY_CODEX, 1); row(p, "codex", "codex-garbage-line1", False, size, he)
    for i in range(N_CODEX_NOMETA):
        sid = uid(); p = os.path.join(codex_dir, "rollout-2026-09-13T00-02-00-%s.jsonl" % sid)
        size, he = write_lines(p, [], turn, BODY_CODEX, None); row(p, "codex", "codex-no-meta", False, size, he)
    proj = os.path.join(work, "claude-config", "projects", project_key(ws))
    oproj = os.path.join(work, "claude-config", "projects", project_key(other))
    def cl(obj):
        return json.dumps(obj) + "\n"
    body_full = cl({"type": "assistant", "cwd": other, "sessionId": "body", "uuid": "u", "parentUuid": "p", "message": {"role": "assistant", "content": [{"type": "text", "text": "y" * 1000}]}})
    body_bare = cl({"type": "assistant", "uuid": "u", "parentUuid": "p", "message": {"role": "assistant", "content": [{"type": "text", "text": "y" * 1000}]}})
    for i in range(N_CLAUDE):
        sid = uid(); sel = i < K; cwd = ws if sel else other; pdir = proj if sel else oproj
        if sel: selected["claude"].append(sid)
        head = [cl({"type": "last-prompt", "sessionId": sid, "lastPrompt": "p"}), cl({"type": "mode", "sessionId": sid, "mode": "default"}),
                cl({"type": "permission-mode", "sessionId": sid, "permissionMode": "default"}), cl({"type": "bridge-session", "sessionId": sid, "bridgeSessionId": uid()}),
                cl({"type": "user", "cwd": cwd, "sessionId": sid, "version": "2.1.202", "uuid": uid(), "parentUuid": None, "message": {"role": "user", "content": "hi"}})]
        body = cl({"type": "assistant", "cwd": cwd, "sessionId": sid, "uuid": "u", "parentUuid": "p", "message": {"role": "assistant", "content": [{"type": "text", "text": "y" * 1000}]}})
        p = os.path.join(pdir, sid + ".jsonl"); size, he = write_lines(p, head, body, BODY_CLAUDE, 4); row(p, "claude", "claude-bulk", sel, size, he)
    for i in range(N_CLAUDE_NOENRICH):
        sid = uid(); p = os.path.join(oproj, sid + ".jsonl")
        size, he = write_lines(p, [cl({"type": "user", "cwd": other, "uuid": uid(), "message": {"role": "user", "content": "hi"}})], body_bare, BODY_CLAUDE, 0)
        row(p, "claude", "claude-cwd-no-enrichment", False, size, he)
    for i in range(N_CLAUDE_NOCWD):
        sid = uid(); p = os.path.join(proj, sid + ".jsonl")
        size, he = write_lines(p, [cl({"type": "summary", "sessionId": sid, "version": "2.1.202", "summary": "s"})], body_bare, BODY_NOCWD, None)
        row(p, "claude", "claude-no-cwd", False, size, he)
    os.makedirs(os.path.join(work, "home"), exist_ok=True)
    counts = {}
    for r in rows: counts[r["class"]] = counts.get(r["class"], 0) + 1
    with open(os.path.join(work, "synth-manifest.json"), "w", encoding="utf-8") as f:
        json.dump({"seed": seed, "k": K, "counts": counts, "selected": selected, "ws": ws, "files": rows,
                   "total_bytes": sum(r["size"] for r in rows)}, f, indent=1, sort_keys=True)
    print("synth ok files=%d bytes=%d" % (len(rows), sum(r["size"] for r in rows)))
if __name__ == "__main__":
    main(sys.argv[1], int(sys.argv[2]))
```

**`membership.py`** (whole-record normalization; GNU tar `--zstd` then bsdtar):

<!-- BLOCK: membership.py -->
```python
#!/usr/bin/env python3
# membership.py <image.bvpk> <out.json> — extracts manifest.json from a biv image (a zstd frame around a ustar/PAX tar) and writes the NORMALIZED
# selected set: per agent_sessions entry every membership-bearing field (agent, original_session_ids, original_path, normalized_path_key,
# normalization_scheme, path_flavor, artifacts, children, live_at_pack, agent_version_at_pack, provenance), sorted by (agent, ids) — LEG 3 compares
# WHOLE RECORDS, not only ids. Extraction: `tar --zstd -xOf` (GNU tar, Linux) first, then `tar -xOf` (macOS bsdtar reads zstd in-process).
import json, subprocess, sys
def extract(image):
    for cmd in (["tar", "--zstd", "-xOf", image, "manifest.json"], ["tar", "-xOf", image, "manifest.json"]):
        r = subprocess.run(cmd, capture_output=True)
        if r.returncode == 0 and r.stdout.strip():
            return r.stdout
    sys.exit(3)
def main(image, out):
    m = json.loads(extract(image))
    rows = sorted(m.get("agent_sessions", []), key=lambda e: (e.get("agent", ""), json.dumps(e.get("original_session_ids", {}), sort_keys=True)))
    keep = ("agent", "original_session_ids", "original_path", "normalized_path_key", "normalization_scheme", "path_flavor", "artifacts", "children", "live_at_pack", "agent_version_at_pack", "provenance")
    norm = [{k: e.get(k) for k in keep} for e in rows]
    with open(out, "w", encoding="utf-8") as f:
        json.dump({"count": len(norm), "sessions": norm}, f, indent=1, sort_keys=True)
    print("membership rows=%d" % len(norm))
if __name__ == "__main__":
    main(sys.argv[1], sys.argv[2])
```

**`strace_bytes.py`** (trace → bytes read per file, no content):

<!-- BLOCK: strace_bytes.py -->
```python
#!/usr/bin/env python3
# strace_bytes.py <strace.log> <prefix> — reduces an `strace -f -e trace=openat,read,pread64 -o <log>` trace of one `biv pack` run to
# bytes READ per file under <prefix> (structure only: no file content is ever in the trace — read/pread64 payloads are elided by strace's
# default string cut and are NOT parsed here; only the return value = byte count). Output: path-relative-to-prefix<TAB>bytes_read, sorted by
# path, one row per file opened under <prefix>. Handles -f traces (pid-prefixed lines) and unfinished/resumed syscall pairs.
import re, sys
log, prefix = sys.argv[1], sys.argv[2].rstrip("/") + "/"
fd_path = {}      # (pid, fd) -> path
unfinished = {}   # pid -> partial line
bytes_read = {}
op = re.compile(r'^(?:(\d+)\s+)?(\S+?)\((.*)\)\s+=\s+(-?\d+|\?)')
for raw in open(log, encoding="utf-8", errors="replace"):
    line = raw.rstrip("\n")
    m = re.match(r'^(\d+)\s+(.*)$', line); pid, rest = (m.group(1), m.group(2)) if m else ("0", line)
    if rest.endswith("<unfinished ...>"):
        unfinished[pid] = rest[: -len("<unfinished ...>")]; continue
    if rest.startswith("<... ") and " resumed>" in rest:
        rest = unfinished.pop(pid, "") + rest.split(" resumed>", 1)[1]
    m = op.match(pid + " " + rest) if False else re.match(r'^(\S+?)\((.*)\)\s+=\s+(-?\d+|\?)', rest)
    if not m: continue
    call, args, ret = m.group(1), m.group(2), m.group(3)
    if call == "openat":
        pm = re.search(r'"((?:[^"\\]|\\.)*)"', args)
        if pm and ret.lstrip("-").isdigit() and int(ret) >= 0:
            path = pm.group(1)
            if path.startswith(prefix): fd_path[(pid, ret)] = path[len(prefix):]
    elif call in ("read", "pread64"):
        fd = args.split(",", 1)[0].strip()
        p = fd_path.get((pid, fd))
        if p is not None and ret.isdigit(): bytes_read[p] = bytes_read.get(p, 0) + int(ret)
for p in sorted(bytes_read): print("%s\t%d" % (p, bytes_read[p]))
```

**`leg12_verdict.py`** (LEG 1 / LEG 2 grading by class):

<!-- BLOCK: leg12_verdict.py -->
```python
#!/usr/bin/env python3
# leg12_verdict.py <bytes-B.tsv> <bytes-H.tsv> <synth-manifest.json> — LEG 1 (bytes read per candidate BEFORE/AFTER with the bound NAMED per
# file) and LEG 2 (the filter's position: every non-selected file's read at H ends within one 8 KiB stream chunk of the end of the line that
# completes the head predicate; the store-proportional term collapses). Rules, per manifest class:
#   selected                      bytes_B >= size AND bytes_H >= size          (full reads retained — V-LS-4)
#   head_end != null, not selected  bytes_B >= size AND bytes_H <= ceil(head_end / 8192) * 8192 AND bytes_H < size   (the bound, per file)
#   head_end == null              bytes_B >= size AND bytes_H >= size          (the SEALED whole-file cases: claude-no-cwd, codex-no-meta)
# A file of S absent from a trace = a violation (it was never opened). Prints one row per file (path class selected size head_end bytes_B
# bytes_H rule verdict), the per-class totals, the store totals at B and at H, then VERDICT PASS|FAIL; exit 0 iff PASS.
import json, math, sys
def load(tsv):
    d = {}
    for line in open(tsv, encoding="utf-8"):
        p, b = line.rstrip("\n").split("\t"); d[p] = int(b)
    return d
B, H, man = load(sys.argv[1]), load(sys.argv[2]), json.load(open(sys.argv[3], encoding="utf-8"))
CHUNK = 8192; fails = 0; tot = {}; totB = totH = 0
print("path\tclass\tselected\tsize\thead_end\tbytes_B\tbytes_H\trule\tverdict")
for r in man["files"]:
    p, size, he, sel = r["path"], r["size"], r["head_end"], r["selected"]
    b, h = B.get(p), H.get(p)
    if b is None or h is None:
        rule, ok = "opened-at-both", False; b = -1 if b is None else b; h = -1 if h is None else h
    elif sel:
        rule, ok = "full-both", (b >= size and h >= size)
    elif he is None:
        rule, ok = "sealed-whole-file", (b >= size and h >= size)
    else:
        bound = int(math.ceil(he / CHUNK)) * CHUNK
        rule, ok = "head<=%d" % bound, (b >= size and h <= bound and h < size)
    fails += 0 if ok else 1
    t = tot.setdefault(r["class"], [0, 0, 0]); t[0] += 1; t[1] += max(b, 0); t[2] += max(h, 0); totB += max(b, 0); totH += max(h, 0)
    print("%s\t%s\t%s\t%d\t%s\t%d\t%d\t%s\t%s" % (p, r["class"], sel, size, he, b, h, rule, "ok" if ok else "VIOLATION"))
for c in sorted(tot): print("CLASS %s files=%d bytes_B=%d bytes_H=%d" % (c, *tot[c]))
print("TOTAL files=%d bytes_B=%d bytes_H=%d ratio_H_over_B=%.4f" % (len(man["files"]), totB, totH, (totH / totB) if totB else 0.0))
print("VERDICT %s violations=%d" % ("PASS" if fails == 0 else "FAIL", fails))
sys.exit(0 if fails == 0 else 1)
```

**`pack_run.py`** (LEG 3 producer: three timed packs under the locator env):

<!-- BLOCK: pack_run.py -->
```python
#!/usr/bin/env python3
# usage: pack_run.py <biv> <work> <label B|H> <outdir>  — LEG 3's producer on one side: runs `biv pack <work>/ws/proj --json` THREE times with the
# locator environment pinned to S (HOME=<work>/home, CODEX_HOME=<work>/codex-home, CLAUDE_CONFIG_DIR=<work>/claude-config, TMPDIR=<work>/tmp; every
# other variable of the caller's environment passed through — the caller unsets the credential names), removing the previous image before each run;
# records each run's wall time and exit status, keeps the LAST run's stdout as <outdir>/pack-<label>.json (stderr beside it), renames the last image
# to <work>/ws/proj-<label>.bvpk and writes <outdir>/time-<label>.txt (three times, the median, the statuses). Exit 0 iff every run returned 0 or 2
# (2 = warned; biv's documented conflation) with `"ok": true` in its JSON and the image exists; the three statuses must be equal.
import json, os, shutil, subprocess, sys, time
biv, work, label, outdir = sys.argv[1:5]
src = os.path.join(work, "ws", "proj"); image = os.path.join(work, "ws", "proj.bvpk")
env = dict(os.environ); env.update({"HOME": os.path.join(work, "home"), "CODEX_HOME": os.path.join(work, "codex-home"),
                                    "CLAUDE_CONFIG_DIR": os.path.join(work, "claude-config"), "TMPDIR": os.path.join(work, "tmp")})
os.makedirs(env["TMPDIR"], exist_ok=True); os.makedirs(outdir, exist_ok=True)
times, rcs, oks = [], [], []
for i in range(3):
    for stale in (image, image + ".partial", image + ".spool"):
        if os.path.exists(stale): os.remove(stale)
    t0 = time.monotonic(); r = subprocess.run([biv, "pack", src, "--json"], env=env, capture_output=True, text=True); t1 = time.monotonic()
    times.append(t1 - t0); rcs.append(r.returncode)
    try: oks.append(bool(json.loads(r.stdout).get("ok")))
    except Exception: oks.append(False)
    open(os.path.join(outdir, "pack-%s.json" % label), "w").write(r.stdout); open(os.path.join(outdir, "pack-%s.stderr" % label), "w").write(r.stderr)
final = os.path.join(work, "ws", "proj-%s.bvpk" % label)
if os.path.exists(image): shutil.move(image, final)
med = sorted(times)[1]
with open(os.path.join(outdir, "time-%s.txt" % label), "w") as f:
    f.write("label=%s runs=3 times_s=%.3f,%.3f,%.3f median_s=%.3f rcs=%s oks=%s image=%s\n" % (label, times[0], times[1], times[2], med, ",".join(map(str, rcs)), ",".join(map(str, oks)), final))
print(open(os.path.join(outdir, "time-%s.txt" % label)).read().strip())
sys.exit(0 if (all(rc in (0, 2) for rc in rcs) and len(set(rcs)) == 1 and all(oks) and os.path.exists(final)) else 1)
```

**`hunkwin.py`** (every hunk inside the touchable windows):

<!-- BLOCK: hunkwin.py -->
```python
#!/usr/bin/env python3
# usage: hunkwin.py <unified-diff-U0> <lo1>-<hi1>[,<lo2>-<hi2>...]  — exit 0 iff EVERY hunk's OLD-side span (`@@ -a[,n]`) lies inside one of the
# windows (base-file line numbers); prints each hunk with its verdict. A hunk outside every window = exit 5: a byte landed outside the TOUCHABLE
# functions (the discover bodies, the sqlite enrichment, the install side stay byte-identical because no hunk reaches them).
import re, sys
wins = [tuple(int(x) for x in w.split("-")) for w in sys.argv[2].split(",")]
bad = 0; n = 0
for line in open(sys.argv[1], encoding="utf-8"):
    m = re.match(r"^@@ -(\d+)(?:,(\d+))? \+", line)
    if not m: continue
    n += 1; a = int(m.group(1)); cnt = int(m.group(2)) if m.group(2) is not None else 1; b = a + max(cnt, 1) - 1
    ok = any(lo <= a and b <= hi for lo, hi in wins); bad += 0 if ok else 1
    print("hunk old=%d..%d %s" % (a, b, "ok" if ok else "OUTSIDE"))
print("hunks=%d outside=%d" % (n, bad))
sys.exit(0 if (n >= 1 and bad == 0) else 5)
```

**`head_reader_claude.py`** (FINAL — compile-checked at B's bytes; the C-1 predicate):

<!-- BLOCK: head_reader_claude.py -->
```python
#!/usr/bin/env python3
# head_reader_claude.py <claude_code.cpp> — R-4.49 claude side (rev1 patcher; every anchor asserted EXACTLY ONCE at the base 4cf135ee bytes;
# any other count = STOP: the base moved). The bound is m-2's C-1 ruling (`170000`): A1 §A1 — stream-scan from the top, the FIRST record
# carrying a `cwd` field keys the session, stop at first hit; no cwd anywhere → whole file, excluded, no_cwd_record. (1) a streaming
# first-cwd reader over ArtifactSource::stream (the sink returns a sentinel error to stop the stream at the end of the first cwd-bearing
# line — the sink contract of secure_io::ReadHandle::stream — consumed here; a real stream error propagates). (2) collect decides
# candidacy from that head cwd; the whole-file source_text + the UNCHANGED inspect_transcript run only for an in-root transcript, so a
# selected session's every field (sessionId, version, cwd) comes from exactly today's parse over exactly today's bytes.
# inspect_transcript itself is NOT touched (its install-side callers unchanged).
import sys
p = sys.argv[1]; t = open(p, encoding="utf-8").read()
def rep(old, new):
    global t
    assert t.count(old) == 1, ("anchor count %d: %s" % (t.count(old), old[:80]))
    t = t.replace(old, new)
OLD_ANCHOR = '''bool terminal_status(const std::string_view status) {'''
NEW_HEAD = '''// R-4.49 (sealed A1 §A1, m-2 C-1 ruling 2026-09-13; fence 142000 §2): the HEAD-BOUNDED read that decides candidacy — the
// source is STREAMED (secure_io::ReadHandle::stream, 8 KiB chunks) and the stream is STOPPED at the end of the FIRST line whose
// record carries a `cwd` field; bytes after that line are never read for a transcript that is not selected. A transcript with no
// cwd-bearing record anywhere is read to EOF (the sealed worst case: excluded and reported as no_cwd_record by the caller).
// Unparseable lines are skipped, as inspect_transcript skips them. The stop is signalled to the stream as a sentinel error and
// consumed here; a real stream error propagates. Line framing is std::getline's: '\\n'-terminated lines, a trailing unterminated
// line counted once. The value returned is exactly the `cwd` inspect_transcript would report for the same bytes (first seen).
constexpr std::string_view kHeadCompleteSentinel = "r449-head-complete";

expected<std::optional<std::string>> first_transcript_cwd(const SessionRecord::ArtifactSource& source) {
  std::optional<std::string> cwd;
  std::string carry;
  const auto absorb = [&](const std::string_view line) {
    simdjson::padded_string padded{line};
    simdjson::dom::parser parser;
    auto object = parse_json_object(parser, padded);
    if (!object.has_value()) {
      return false;
    }
    cwd = object_string(*object, "cwd");
    return cwd.has_value();
  };
  auto read = source.stream([&](const std::span<const std::byte> chunk) -> expected<void> {
    carry.append(reinterpret_cast<const char*>(chunk.data()), chunk.size());
    std::size_t start = 0;
    for (auto newline = carry.find('\\n', start); newline != std::string::npos;
         newline = carry.find('\\n', start)) {
      const std::string_view line{carry.data() + start, newline - start};
      start = newline + 1;
      if (absorb(line)) {
        break;
      }
    }
    carry.erase(0, start);
    if (cwd.has_value()) {
      return std::unexpected(BivError{ErrKind::InternalError, {}, std::string{kHeadCompleteSentinel}});
    }
    return {};
  });
  if (!read) {
    if (cwd.has_value() && read.error().detail == kHeadCompleteSentinel) {
      return cwd;
    }
    return std::unexpected(read.error());
  }
  if (!carry.empty()) {
    absorb(carry);
  }
  return cwd;
}

bool terminal_status(const std::string_view status) {'''
rep(OLD_ANCHOR, NEW_HEAD)
OLD_COLLECT = '''            auto main_text = source_text(*main_source);
            if (!main_text) {
              return std::unexpected(main_text.error());
            }
            auto facts = inspect_transcript(*main_text);
            if (!facts.cwd.has_value()) {
              if (project_key_matches_source) {
                report.no_cwd_record.push_back(entry.path().generic_string());
              }
              continue;
            }
            if (!rewrite::path_is_same_or_descendant(rewrite::PathMembership{
                    .candidate = *facts.cwd,
                    .root = source_root.generic_string()})) {
              continue;
            }
'''
NEW_COLLECT = '''            // R-4.49: candidacy from the HEAD only — the first cwd-bearing record (A1 §A1), streamed and stopped there; a
            // transcript with no cwd anywhere is read to EOF and reported (sealed); a transcript whose first cwd is outside the
            // source root is never read past that line. The FULL read and the unchanged whole-text parse below run only for an
            // in-root transcript, so every selected field (sessionId, version) is today's; its cwd IS the head's first-seen cwd —
            // inspect_transcript applies the same first-seen rule over the same bytes (the SECTIONs and LEG 3 measure this).
            auto head_cwd = first_transcript_cwd(*main_source);
            if (!head_cwd) {
              return std::unexpected(head_cwd.error());
            }
            if (!head_cwd->has_value()) {
              if (project_key_matches_source) {
                report.no_cwd_record.push_back(entry.path().generic_string());
              }
              continue;
            }
            if (!rewrite::path_is_same_or_descendant(rewrite::PathMembership{
                    .candidate = **head_cwd,
                    .root = source_root.generic_string()})) {
              continue;
            }
            auto main_text = source_text(*main_source);
            if (!main_text) {
              return std::unexpected(main_text.error());
            }
            auto facts = inspect_transcript(*main_text);
            facts.cwd = *head_cwd;
'''
rep(OLD_COLLECT, NEW_COLLECT)
open(p, "w", encoding="utf-8").write(t)
print("claude_code.cpp patched (rev1)")
```

**`head_reader_codex.py`** (FINAL — compile-checked at B's bytes; the C-2 predicate):

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

**`tests_claude_r449.py`** (five SECTIONs):

<!-- BLOCK: tests_claude_r449.py -->
```python
#!/usr/bin/env python3
# tests_claude_r449.py <tests/test_adapter_claude_collect.cpp> — R-4.49 witness SECTIONs inside the EXISTING TEST_CASE "Claude adapter keys
# membership on the first cwd record" (the Catch2 case census — the workflow's count-gate cells — does not move). Anchor asserted EXACTLY ONCE.
import sys
p = sys.argv[1]; t = open(p, encoding="utf-8").read()
OLD = '''  REQUIRE(report.has_value());
  CHECK(report->sessions.empty());
  fs::remove_all(root);
}

TEST_CASE("Claude adapter matches Windows cwd to its WSL workspace") {'''
NEW = '''  REQUIRE(report.has_value());
  CHECK(report->sessions.empty());

  // R-4.49 (A1 §A1: the FIRST cwd-bearing record keys the session; fence 142000 §2 V-LS-2): membership and every record field
  // are the same whatever lies behind the first cwd-bearing record and however large the transcript is. These SECTIONs are the
  // corpus oracle for the head-bounded candidacy read; the read-cost witness (bytes read per file) is evidence, not a test.
  const auto r449_stores = [](const fs::path& r449_store) {
    return std::vector<biv::adapters::Store>{biv::adapters::Store{
        .root = r449_store,
        .locators = {biv::adapters::StoreLocator{.kind = "sessions_root",
                                                 .path = r449_store / "projects"}},
        .tier = biv::adapters::DiscoveryTier::defaults,
        .archived = false}};
  };
  const auto r449_body = [](const std::size_t bytes) {
    const std::string line = "{\\"type\\":\\"assistant\\",\\"message\\":{\\"role\\":\\"assistant\\",\\"content\\":\\"" +
                             std::string(1000, 'y') + "\\"}}\\n";
    std::string body;
    while (body.size() < bytes) {
      body += line;
    }
    return body;
  };
  constexpr std::size_t kR449Large = 3u * 1024u * 1024u;

  SECTION("R-4.49: enrichment fields behind the first cwd record still key the selected session") {
    const auto r449_store = root / "r449-enrichment-later";
    const std::string id{"aaaaaaaa-1111-4000-8000-000000004901"};
    write_file(r449_store / "projects" / "-ws-proj" / (id + ".jsonl"),
               "{\\"type\\":\\"user\\",\\"cwd\\":\\"/ws/proj\\"}\\n"
               "{\\"type\\":\\"assistant\\",\\"cwd\\":\\"/ws/proj\\",\\"sessionId\\":\\"" +
                   id + "\\",\\"version\\":\\"2.1.202\\"}\\n" + r449_body(kR449Large));
    const auto r449 = biv::adapters::claude_code_adapter().collect("/ws/proj", r449_stores(r449_store));
    REQUIRE(r449.has_value());
    REQUIRE(r449->sessions.size() == 1);
    CHECK(r449->sessions.front().original_session_id == id);
    CHECK(r449->sessions.front().original_path == "/ws/proj");
    CHECK(r449->sessions.front().agent_version_at_pack == "2.1.202");
    REQUIRE(r449->sessions.front().artifacts.size() == 1);
    CHECK(r449->no_cwd_record.empty());
  }

  SECTION("R-4.49: an out-of-root first cwd record without enrichment fields is excluded silently however large the file") {
    const auto r449_store = root / "r449-out-of-root-no-enrichment";
    const std::string id{"aaaaaaaa-1111-4000-8000-000000004902"};
    write_file(r449_store / "projects" / "-other-proj" / (id + ".jsonl"),
               "{\\"type\\":\\"user\\",\\"cwd\\":\\"/other/proj\\"}\\n" + r449_body(kR449Large));
    const auto r449 = biv::adapters::claude_code_adapter().collect("/ws/proj", r449_stores(r449_store));
    REQUIRE(r449.has_value());
    CHECK(r449->sessions.empty());
    CHECK(r449->no_cwd_record.empty());
  }

  SECTION("R-4.49: a large transcript with no cwd record anywhere is excluded and reported") {
    const auto r449_store = root / "r449-no-cwd";
    const std::string id{"aaaaaaaa-1111-4000-8000-000000004903"};
    write_file(r449_store / "projects" / "-ws-proj" / (id + ".jsonl"),
               "{\\"type\\":\\"summary\\",\\"sessionId\\":\\"" + id + "\\",\\"version\\":\\"2.1.202\\"}\\n" +
                   r449_body(kR449Large));
    const auto r449 = biv::adapters::claude_code_adapter().collect("/ws/proj", r449_stores(r449_store));
    REQUIRE(r449.has_value());
    CHECK(r449->sessions.empty());
    REQUIRE(r449->no_cwd_record.size() == 1);
    CHECK(r449->no_cwd_record.front().find(id) != std::string::npos);
  }

  SECTION("R-4.49: metadata-first head with the first cwd on line 5 and a large body is selected with today's fields") {
    const auto r449_store = root / "r449-metadata-first";
    const std::string id{"aaaaaaaa-1111-4000-8000-000000004904"};
    write_file(r449_store / "projects" / "-ws-proj" / (id + ".jsonl"),
               "{\\"type\\":\\"last-prompt\\",\\"sessionId\\":\\"" + id + "\\"}\\n"
               "{\\"type\\":\\"mode\\",\\"sessionId\\":\\"" + id + "\\"}\\n"
               "{\\"type\\":\\"permission-mode\\",\\"sessionId\\":\\"" + id + "\\"}\\n"
               "not json\\n"
               "{\\"type\\":\\"user\\",\\"cwd\\":\\"/ws/proj\\",\\"sessionId\\":\\"" + id +
                   "\\",\\"version\\":\\"2.1.202\\"}\\n" + r449_body(kR449Large));
    const auto r449 = biv::adapters::claude_code_adapter().collect("/ws/proj", r449_stores(r449_store));
    REQUIRE(r449.has_value());
    REQUIRE(r449->sessions.size() == 1);
    CHECK(r449->sessions.front().original_session_id == id);
    CHECK(r449->sessions.front().agent_version_at_pack == "2.1.202");
    CHECK(r449->no_cwd_record.empty());
  }

  SECTION("R-4.49: the first cwd on an unterminated final line still keys the session") {
    const auto r449_store = root / "r449-unterminated";
    const std::string id{"aaaaaaaa-1111-4000-8000-000000004905"};
    write_file(r449_store / "projects" / "-ws-proj" / (id + ".jsonl"),
               "{\\"type\\":\\"user\\",\\"cwd\\":\\"/ws/proj\\",\\"sessionId\\":\\"" + id +
                   "\\",\\"version\\":\\"2.1.202\\"}");
    const auto r449 = biv::adapters::claude_code_adapter().collect("/ws/proj", r449_stores(r449_store));
    REQUIRE(r449.has_value());
    REQUIRE(r449->sessions.size() == 1);
    CHECK(r449->sessions.front().original_session_id == id);
  }
  fs::remove_all(root);
}

TEST_CASE("Claude adapter matches Windows cwd to its WSL workspace") {'''
assert t.count(OLD) == 1, t.count(OLD)
t = t.replace(OLD, NEW)
open(p, "w", encoding="utf-8").write(t)
print("test_adapter_claude_collect.cpp patched (rev1: 5 SECTIONs)")
```

**`tests_codex_r449.py`** (four SECTIONs):

<!-- BLOCK: tests_codex_r449.py -->
```python
#!/usr/bin/env python3
# tests_codex_r449.py <tests/test_adapter_codex_collect.cpp> — R-4.49 witness SECTIONs inside the EXISTING TEST_CASE "X-2 Codex suppresses
# session_id warnings outside the source root" (case census unchanged). Anchor asserted EXACTLY ONCE.
import sys
p = sys.argv[1]; t = open(p, encoding="utf-8").read()
OLD = '''  CHECK_FALSE(std::ranges::any_of(
      report->warnings, [&](const std::string& warning) {
        return warning == "SessionIdWithoutId:" + rollout.generic_string();
      }));
  fs::remove_all(root);
}

TEST_CASE("Codex duplicate-store E-3 warns and picks by declared freshness") {'''
NEW = '''  CHECK_FALSE(std::ranges::any_of(
      report->warnings, [&](const std::string& warning) {
        return warning == "SessionIdWithoutId:" + rollout.generic_string();
      }));

  // R-4.49 (c1 §4: the FIRST session_meta record keys the rollout — m-2 C-2 ruling; fence 142000 §2 V-LS-2/V-LS-4): membership,
  // the head-fact warning and the tail facts are the same however large the rollout is and whatever precedes session_meta.
  const auto r449_stores = [](const fs::path& r449_store) {
    return std::vector<biv::adapters::Store>{biv::adapters::Store{
        .root = r449_store,
        .locators = {biv::adapters::StoreLocator{.kind = "sessions_root",
                                                 .path = r449_store / "sessions"}},
        .tier = biv::adapters::DiscoveryTier::defaults,
        .archived = false}};
  };
  const auto r449_body = [](const std::size_t bytes) {
    const std::string line =
        "{\\"timestamp\\":\\"2026-07-06T11:00:01Z\\",\\"type\\":\\"response_item\\",\\"payload\\":{\\"type\\":\\"message\\","
        "\\"role\\":\\"assistant\\",\\"content\\":[{\\"type\\":\\"output_text\\",\\"text\\":\\"" +
        std::string(1000, 'y') + "\\"}]}}\\n";
    std::string body;
    while (body.size() < bytes) {
      body += line;
    }
    return body;
  };
  const auto r449_meta = [](const std::string& id, const std::string& cwd, const bool with_id) {
    return std::string{"{\\"timestamp\\":\\"2026-07-06T11:00:00Z\\",\\"type\\":\\"session_meta\\",\\"payload\\":{"} +
           (with_id ? "\\"id\\":\\"" + id + "\\"," : std::string{}) + "\\"session_id\\":\\"" + id +
           "\\",\\"cwd\\":\\"" + cwd + "\\",\\"cli_version\\":\\"0.144.0\\"}}\\n";
  };
  const auto r449_path = [](const fs::path& r449_store, const std::string& id) {
    return r449_store / "sessions" / "2026" / "07" / "06" / ("rollout-2026-07-06T11-00-00-" + id + ".jsonl");
  };
  constexpr std::size_t kR449Large = 3u * 1024u * 1024u;

  SECTION("R-4.49: an unparseable first line ahead of session_meta still keys the rollout") {
    const auto r449_store = root / "r449-garbage-first-line";
    const std::string id{"019faaaa-bbbb-7ccc-8ddd-eeeeeeee4901"};
    write_file(r449_path(r449_store, id), "not json\\n" + r449_meta(id, "/ws/proj", true) + r449_body(kR449Large));
    const auto r449 = biv::adapters::codex_adapter().collect("/ws/proj", r449_stores(r449_store));
    REQUIRE(r449.has_value());
    REQUIRE(r449->sessions.size() == 1);
    CHECK(r449->sessions.front().original_session_id == id);
    CHECK(r449->sessions.front().original_path == "/ws/proj");
    CHECK(r449->sessions.front().agent_version_at_pack == "0.144.0");
    CHECK(r449->sessions.front().live_at_pack);
  }

  SECTION("R-4.49: the tail facts of a large selected rollout come from its full text") {
    const auto r449_store = root / "r449-terminal-tail";
    const std::string id{"019faaaa-bbbb-7ccc-8ddd-eeeeeeee4902"};
    write_file(r449_path(r449_store, id),
               r449_meta(id, "/ws/proj", true) + r449_body(kR449Large) +
                   "{\\"timestamp\\":\\"2026-07-06T11:59:00Z\\",\\"type\\":\\"task_complete\\",\\"payload\\":{}}\\n");
    const auto r449 = biv::adapters::codex_adapter().collect("/ws/proj", r449_stores(r449_store));
    REQUIRE(r449.has_value());
    REQUIRE(r449->sessions.size() == 1);
    CHECK(r449->sessions.front().original_session_id == id);
    CHECK_FALSE(r449->sessions.front().live_at_pack);
  }

  SECTION("R-4.49: an out-of-root session_meta with a large body is excluded without a warning") {
    const auto r449_store = root / "r449-out-of-root-large";
    const std::string id{"019faaaa-bbbb-7ccc-8ddd-eeeeeeee4903"};
    write_file(r449_path(r449_store, id), r449_meta(id, "/other/project", false) + r449_body(kR449Large));
    const auto r449 = biv::adapters::codex_adapter().collect("/ws/proj", r449_stores(r449_store));
    REQUIRE(r449.has_value());
    CHECK(r449->sessions.empty());
    CHECK_FALSE(std::ranges::any_of(r449->warnings, [&](const std::string& warning) {
      return warning == "SessionIdWithoutId:" + r449_path(r449_store, id).generic_string();
    }));
  }

  SECTION("R-4.49: the in-root SessionIdWithoutId warning still fires from the head facts of a large rollout") {
    const auto r449_store = root / "r449-in-root-no-id-large";
    const std::string id{"019faaaa-bbbb-7ccc-8ddd-eeeeeeee4904"};
    write_file(r449_path(r449_store, id), r449_meta(id, "/ws/proj", false) + r449_body(kR449Large));
    const auto r449 = biv::adapters::codex_adapter().collect("/ws/proj", r449_stores(r449_store));
    REQUIRE(r449.has_value());
    CHECK(r449->sessions.empty());
    CHECK(std::ranges::any_of(r449->warnings, [&](const std::string& warning) {
      return warning == "SessionIdWithoutId:" + r449_path(r449_store, id).generic_string();
    }));
  }
  fs::remove_all(root);
}

TEST_CASE("Codex duplicate-store E-3 warns and picks by declared freshness") {'''
assert t.count(OLD) == 1, t.count(OLD)
t = t.replace(OLD, NEW)
open(p, "w", encoding="utf-8").write(t)
print("test_adapter_codex_collect.cpp patched (rev1: 4 SECTIONs)")
```

**`linux-container.sh`** (Phases R / T / S / L):

<!-- BLOCK: linux-container.sh -->
```bash
#!/usr/bin/env bash
# linux-container.sh <expected-head> <label B|H> — Phases R / T / S / L inside ubuntu:24.04 (linux/amd64, --init); /llvm-mirror and /repo-ro read-only, /evidence writable.
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
phase_l_leg_fn() {
  [ -d /evidence/work/ws/proj ] && [ -s /evidence/synth-manifest.json ] || return 51
  cp -a /evidence/work "$WORK_ROOT/synth" || return 52
  rm -f "$WORK_ROOT"/synth/ws/proj.bvpk "$WORK_ROOT"/synth/ws/proj-*.bvpk || return 53
  mkdir -p "$WORK_ROOT/synth/tmp" || return 54
  chown -R 1001:1001 "$WORK_ROOT/synth" || return 55
  runuser -u suite -- env HOME=/work/synth/home CODEX_HOME=/work/synth/codex-home CLAUDE_CONFIG_DIR=/work/synth/claude-config TMPDIR=/work/synth/tmp strace -f -s 0 -e trace=open,openat,openat2,read,pread64 -o "$OUT/strace-$LABEL.log" "$REPO_ROOT/build/ci/biv" pack /work/synth/ws/proj --json > "$OUT/pack-linux-$LABEL.json" 2> "$OUT/pack-linux-$LABEL.stderr" || pack_rc=$?
  printf '%s\n' "${pack_rc-0}" > "$OUT/pack-linux-$LABEL.rc" || return 56
  case "${pack_rc-0}" in 0|2) ;; *) return 57;; esac
  grep -c -F '"ok": true' "$OUT/pack-linux-$LABEL.json" > "$OUT/pack-linux-$LABEL.ok" || return 58
  [ -s "$OUT/strace-$LABEL.log" ] || return 59
  python3 /evidence/strace_bytes.py "$OUT/strace-$LABEL.log" /work/synth > "$OUT/bytes-$LABEL.tsv" || return 60
  [ -s "$OUT/bytes-$LABEL.tsv" ] || return 61
  python3 /evidence/membership.py /work/synth/ws/proj.bvpk "$OUT/membership-linux-$LABEL.json" > "$OUT/membership-linux-$LABEL.log" 2>&1 || return 62
  [ -s "$OUT/membership-linux-$LABEL.json" ] || return 63
  wc -c < "$OUT/strace-$LABEL.log" > "$OUT/strace-$LABEL.size" || return 64
}
phase_l_leg=0
pack_rc=0
phase_l_leg_fn > "$OUT/phase-L-leg.log" 2>&1 || phase_l_leg=$?
phase_l_record_rc=0
printf 'phase_L_leg_rc=%s\n' "$phase_l_leg" >> "$LEDGER" || phase_l_record_rc=$?
[ "$phase_l_record_rc" -eq 0 ] || STOP
[ "$phase_l_leg" -eq 0 ] || STOP
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

**`commit-message.txt`** (the one commit's message body; the runner appends the pins):

<!-- BLOCK: commit-message.txt -->
```text
adapters(claude, codex): decide candidacy from a head-bounded read; full reads only for selected sessions (R-4.49)

Both collect paths read every store file in full before the cwd filter. Now each candidate is streamed and the stream stops at
the line that completes the head predicate today's parsers already implement: the FIRST cwd-bearing record for a claude
transcript (sealed ADDENDUM-1 §A1; a transcript with no cwd anywhere is still read to EOF and reported as no_cwd_record) and the
FIRST session_meta record for a codex rollout (sealed c1 §4). The whole-file read and the unchanged whole-text parsers run only
for an in-root candidate, so membership, edges, record fields, warnings and tail facts are byte-identical (m-2 C-1/C-2 rulings
2026-09-13: selection identity by construction; the act is read-bounding only). No discover, secure_io, schema, sqlite, manifest
or harness byte. Witness SECTIONs inside existing TEST_CASEs (the Catch2 case census is unchanged).
```

## Acceptance criteria (each measured, none inferred)

1. At H: numstat B→H == exactly the four touchable paths; the diff over every non-touchable path set EMPTY; every hunk inside the declared windows; every V-LS-3 / V-LS-4 / S-LS-3 occurrence count equal at B and H; the two head readers present.
2. V-LS-2: `B/membership-B.json` == `H/membership-H.json` (macOS) and `B/membership-linux-B.json` == `H/membership-linux-H.json` (Linux), whole normalized records, `diff` rc 0; the `no_cwd` mention counts equal; every existing assertion of the two collect suites green at B and at H on both targets; the nine SECTIONs green (observed run: 9).
3. LEG 1 / LEG 2: `VERDICT PASS violations=0` — every non-selected file of S with a completing line read within one 8 KiB chunk of that line's end at H and in full at B; the class `claude-cwd-no-enrichment` head-bounded at H (the O-1 discriminator); the two sealed whole-file classes read in full at both sides; every selected file read in full at both sides; the store totals and the H/B ratio printed.
4. LEG 3's cost receipt: the pack wall time over S at B and at H (medians of three), both recorded.
5. COUNT-GATE: the ten `OverallResultsCases` cells at H == B's literal cells == B's observed cells on both targets (`cellgate.py` rc 0 twice); the skip sets unchanged; the `TEST_CASE` counts 15 / 25 unchanged.
6. Acceptance of record at H: macOS `ctest --preset ci-macos -E '^safety-hardening$'` rc 0; the Linux bar in `pass-green` or `pass-r435-disclosed-registered-red` with the in-token base draw at B; the four container ledgers aggregate 0 (five phase keys each).
7. The census at the branch head: produced on B and on H in-token, both arms, `LC_ALL=C`; H == B; B == the record of `4cf135ee` (69 / 34); no matched text in the record; the raw intermediates excluded.
8. Cut-point `origin/main..B` = 0 at Task 0; `H^` == B; the branch pushed with class a; the PR open against `main` with head H; `main` NOT pushed by this plan; the `-v2` worktree disposed with its receipt and both R-4.50 branch refs unchanged.
9. m-2's byte review at H returns through master with no red before Task 6; the four-condition bar, the operator's token and the R-4.52 landing follow in the merge packet.

## Out of scope (an act here is a STOP, not a judgement)

Any discover byte (R-4.50 landed it); any `SessionRecord` / `CollectReport` / `adapter.hpp` byte; any `.hpp` byte; any `secure_io` byte; any sqlite use beyond enrichment; any harness / stub / iso-witness byte (m-3's); any workflow byte (the count-gate cells — a `TEST_CASE` count change routes UP); any manifest / pack / open surface; any new head SEMANTICS (the bound is the sealed predicate as ruled; a byte cap or a line number is m-2's declined class); dedupe semantics (c1 §7's mtime clause is executed as today's `better_candidate`, untouched); any release act.

## Anti-half-fix guards

- The head readers' predicates are IDENTICAL to today's parsers' membership facts (claude: the first cwd-bearing parseable record; codex: the first `session_meta` record) — a reader that stops earlier or later than the predicate changes membership and is red under LEG 3's whole-record comparison and the SECTIONs; a reader that waits for enrichment fields is red under LEG 2 (class `claude-cwd-no-enrichment` read to EOF).
- A full read that survives ABOVE the cwd filter on either adapter is the act not done (LEG 1: non-selected `bytes_H == size` outside the two sealed classes → VIOLATION).
- A tail fact computed from the head text is V-LS-4 red (the codex SECTION "tail facts … from its full text" reds; the grep proofs name the full-text call sites).
- The synthetic store's ids are proven against the frozen harness constants (values read, never written); a hit is a STOP, not a rename.
- No evidence-producing pipeline anywhere (the history census's two producers write a file between them); every producer's status recorded; every count from a file.
- The census population is PRODUCED on the objects scanned (B and H, in-token), reduced by the exact lines, `LC_ALL=C` — never carried from a previous head; H must equal B and B must equal the record; the raw intermediates never enter the record.
- The `-v2` worktree disposal is a receipted act with both refs proven unchanged before and after — a branch deletion or a force update is outside this plan.

## Revision history

- **rev0** (b07125a, 2026-09-13) — the SKELETON: the audit's architecture; the fence by reference; placeholders [C-1] / [C-2]; the runner protocol and the R-4.50 instruments carried; the two patchers drafted at B's bytes.
- **rev1** (2026-09-13) — C-1/C-2 RESOLVED per m-2 `170000` (master `171709`); the reconcile with `165828` (O-1 FOLDED: first-cwd head reader + today's full parse for the selected transcript; the sealed whole-file classes stated in LEG 1; class `claude-cwd-no-enrichment` in S); nine SECTIONs; the final patchers compile-checked at B (419/3; 9 sections run); the eight RUN blocks materialized; the corpus mirror dropped in favour of the suites as F's oracle; instruments `cellgate.py`, `pack_run.py`, `hunkwin.py`, `leg12_verdict.py`, Phase L in the container, `finalize.py` SCRATCH for the strace traces.
