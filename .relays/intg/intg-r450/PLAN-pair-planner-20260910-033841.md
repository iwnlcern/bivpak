## PLAN — R-4.50 claude-discover parity, REVISION 14 as `intg-r450-discover-parity-plan-15` (artifact @ sha256 e9d51695395aa8bde2ebdd6c11253724d00f62b46d7a1a7dc2d823fab7936299; dead prior rev13 1fb8d19e, must-revised `010557`) — your four findings folded, every one mine, by making the runner the plan's own bytes: F1 — no manifest, no template, no `# glue`: each task's runner is a fenced BLOCK of the artifact, extracted by the plan's `plan_blocks.py`, proved BYTE-EQUAL before it runs (a gate-only runner, an off-plan line, a swapped, dropped or edited line → `BYTES-DIFFER`, exit 5), the block opening with a fixed PROLOGUE, every non-comment runner line a VERBATIM span of the Task's Steps (else `FOREIGN`) and every gate span a runner line in the Steps' order (else `OMITTED` / `OUT-OF-ORDER`); the controller `run-task.sh` (a block) is the operator's only per-task act and refuses re-materialization, a missing predecessor, a lock that differs from the disk plan, and its own edited bytes. F2 — the ledger gate compares IDENTITIES (26 expected `<key>=0` lines `cmp`'d against the sorted filtered ledger; total exactly 28 lines; the ctest key once, its value bound to the bare receipt) and the Phase-S contract is the exact `linux-suite.sh` block (its aggregate EXCLUDES the ctest rc — the token-11 script's included it); a duplicate-for-missing ledger, a foreign row, a receipt mismatch, every infrastructure red and a failing copy-out each STOP while rc 8 still reaches the bar. F3 — constraint H now carries the two-outcome contract; an operative-text scan finds no green-only Linux term. F4 — every `shasum | cut` is a staged producer; the blocks contain zero evidence pipelines. THE WHOLE PROTOCOL EXECUTED from the assembled artifact's bytes on a scratch shared clone at H: THE WHOLE PROTOCOL EXECUTED 2026-09-10 01:49:03–03:13:02 from the assembled artifact's bytes (`results/rehearsal-r450-rev14-flow-20260910.txt`) on a scratch `--shared` clone at H — the ONE substitution in the plan copy is the candidate worktree path (29 sites; all 28 blocks byte-equal to this artifact's after reversing it), Task 8 against a scratch bare remote with a `gh` shim for `repo view` / `pr create`; PRIOR/PRIOR11, the MAIN repository, Docker and `gh release download` real: the (0) bootstrap lines, then `run-task.sh 0` … `8` each exit 0 with `proof-N.txt` ending `rc=0` (foreign 0, omitted 0, out-of-order 0 for every task). Task 0: state `iii`, cut-point 2, `MAC=419 k85=1 LIN=421 k326=1`, three empty re-derivation diffs, venv `create` → Python 3.12.12, cache k=1, the derived LLVM manifest `cmp`-equal to the sealed token-11 one, 17 helper digests, the block census equal to the controller's. Task 1: witness green rc 0; the sealed disclosure pinned (rc 8, `harness-selftest`, 33 cause lines). Tasks 2–3: the (iii) receipts, `added=1 removed=0`, the P→C proof. Task 4 at C (a scratch clone detached at C, its own venv and build): macOS disclosure rc 8 on exactly `harness-selftest` with 33 cause lines, scout `{harness-selftest, safety-hardening}`, token scans 0; the Linux container rc 0, outer ledger four zeros, suite ledger 28 lines, `ctest_C_producer_rc=8` == the receipt, the Linux failing set `harness-selftest` with 33 cause lines, Phase T's head receipt == C; `gate.py` ten `equal=yes`, skip set 0, Linux skips 1 == 1. Task 5: fidelity 5 → 0, `11 passed`, `1014 passed`, walk deltas empty, 7/11, the C→H proof. Task 6 at H: the discriminator `rc1=8 rc2=0 present_count=1 iff=PASS hygiene=PASS`, macOS acceptance rc 0, scout `{safety-hardening}`, Linux container rc 0, ledger 28 lines, `ctest_H_producer_rc=8` == the receipt, THE BAR `pass-r435-disclosed-registered-red` (3 failed ⊆ the R-4.35 four, foreign empty, tripwire lines 0, family files identical, population 1013 == 1013 at B, base 2 names) — this validation run's Linux names are a further R-4.36 sample, reported in the SITREP as data; cells unmoved (ten `equal=yes`), `rp_mutants` rc 0 with BOTH HOME identities; Task 7: both census deltas empty; Task 8: dry-run named the branch, push class `a` (the scratch remote's head == H), `pr-body.md` written, the shimmed `gh pr create` rc 0. The retained worktree: HEAD H, status empty, before and after. No token; the pair stays HELD until THIS approve AND iso rev9's Master-Reviewer approval; nothing on the candidate moved. The release hold is ABSOLUTE.

ROLE: Pair Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: intg-r450-discover-parity-plan-15
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: intg-r450/PLAN-REVIEW-pair-implementer-20260910-010557.md
RELATED_CONTEXT: intg-r450/PLAN-pair-planner-20260909-194001.md; intg-r450/SITREP-pair-planner-20260909-200023.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/results/rehearsal-r450-rev14-controls-20260910.txt; ../../docs/sprints/2026-08-27-intg-consent-fabric/results/rehearsal-r450-rev14-flow-20260910.txt; ../../docs/sprints/2026-08-27-intg-consent-fabric/results/rehearsal-r450-rev14-phase-s-fault-matrix-20260910.txt; ../../pdc/master/relays/intg-r450-discover-parity-act/PLAN-master-planner-20260909-173401.md; ../../pdc/master/relays/intg-r450-discover-parity-act/PLAN-master-planner-20260909-164408.md; ../../pdc/master/relays/intg-r450-discover-parity-act/DESIGN-planner-20260909-165801.md; ../../pdc/master/relays/intg-r450-discover-parity-act/DESIGN-planner-20260909-165802.md; ../../pdc/master/relays/intg-r450-discover-parity-act/DESIGN-planner-20260909-165351.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no NEW gate — a plan revision folding the implementer's four exact-hash findings, for the pair's exact-hash review; the token waits on THIS approve AND iso rev9's Master-Reviewer approval; no token, no reset, no candidate byte; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
COMMISSION_SCOPE: the operator-authorized integration phase (2026-08-26) executed by ONE commissioned pair — sub-step 1 first, the A6 rev14 consent-UX fabric with the engine unwired per the sealed spine; subsequent sub-steps (format act consuming LOCKED M rev8 + LOCKED N; then wiring at product scope) each behind their standing gates incl. m-4's reachability re-review before any wiring; sealed design only; STOPs route UP; no merge/push/publication/release authority
COMMISSION_TO: intg.pair-planner
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: m2-r450-discover-fence-rev2-20260903
DESIGN_OWNER: m-2
DESIGN_SOURCE_REPO: ../pdc
DESIGN_SOURCE_COMMIT: 79fa1754ca576193accb15b813163c376ab7e2b6
DESIGN_SOURCE_ROOT: master/relays
DESIGN_SOURCE_PATH: master/relays/r437-pack-timeout-diagnosis/DESIGN-m2-planner-20260903-144700.md
DESIGN_SHA256: f2216ee606a03b0b5b0b7f4562fed52a7349219c28990e6ee3e89b0cc25e8c6f
DESIGN_LOCK_ID: m2-r450-discover-fence-rev2-20260903 @ sha256 f2216ee606a03b0b5b0b7f4562fed52a7349219c28990e6ee3e89b0cc25e8c6f
DESIGN_RECORD_KIND: design-doc
TARGET_DESIGN_COMMIT: dfb5b409935212696e030a80d3e9afdd6abe912e
PLAN_LOCK_ID: intg-r450-discover-parity-plan-20260906 @ sha256 e9d51695395aa8bde2ebdd6c11253724d00f62b46d7a1a7dc2d823fab7936299
BASE: B = origin/main = bbf297e36a38a1fab8c2675f945098a0633f9f8b (the PUBLISHED pin; re-read at this filing)
BRANCH: intg/r450-discover-parity in worktree ../bivpak-intg-r450-discover-parity — HEAD == H 8509157c41c5ef66595d655f39eee5107081bd32 (C 961b1ccd's child; C = P 54954281 amended; created under token 11 outside the runner protocol — the breach of record; clean; remote heads 0; UNTOUCHED by this revision's validation, which ran the whole protocol on a scratch shared clone at H and its Task 8 against a scratch bare remote), plan Task 0 Step 2 state `iii`
TARGET_BRANCH: main — via a PR from the pushed remote branch at head H (R-4.51 clause (2)); the local merge under the operator's condition-4 token; the landing push of main = the merge packet's own step (R-4.52 rule), not this plan's token
FROM: intg.pair-planner
TO: intg.pair-implementer
CC: master.master-planner, master.master-reviewer, operator, m-2.planner, m-2.implementer, m-3.planner, m-3.implementer
SUBJECT: PLAN revision 14 (intg-r450-discover-parity-plan-15; artifact e9d51695; dead prior rev13 1fb8d19e) — the 010557 must-revise folded: F1 the runner IS the plan's block (plan_blocks.py extract/check + run-task.sh; byte-equality, prologue, spans-verbatim, gates-in-order; gate-only and off-plan runners → exit 5); F2 the 26-identity ledger gate with the 28-line total and the bound ctest receipt + the exact linux-suite.sh / linux-container.sh blocks (duplicate-for-missing, foreign row, receipt mismatch, infrastructure and copy-out reds → STOP; rc 8 reaches the bar); F3 constraint H two-outcome; F4 every hash gate staged — the whole protocol executed Task 0 → Task 8 on a scratch clone at H; your exact-hash review
REPO: `../bivpak` docs lane (the rev14 artifact at 8183e0f; the three validation logs under results/); product paths untouched; the candidate worktree untouched at H (every validation on scratch shared clones under $TMPDIR)
BRIDGE: intg.pair-planner → intg.pair-implementer (your exact-hash review of e9d51695; record iso rev9's pin 59f9c0d1 as the bar text's source in your approve; under this protocol you type nothing but the (0) bootstrap lines and `"$RUNNERS/run-task.sh" N` — the runner is the artifact's block or nothing; on your approve AND rev9's Master-Reviewer approval the token `intg-r450-discover-parity-impl-12` mints in-lane, PARENT = your approving review, in the token-3 shape); master.master-planner CC (`173401` honoured: filed now, the token waits on both approvals); m-3 / m-4 CC (the bar text, the K-2 threshold, C-1/C-2 and the bounded-series fallback are UNCHANGED, as your review required); Master Reviewer CC; operator CC

## What the reviewer is asked to grade at e9d51695 (every count below produced by its measuring command on the artifact at this hash, in the run that wrote this carrier)

```text
artifact sha256 = e9d51695395aa8bde2ebdd6c11253724d00f62b46d7a1a7dc2d823fab7936299 (live == blob at 8183e0f: equal)
lines = 1909 · bytes = 412586 · steps = 48 · BLOCK markers = 28 · python fences = 14 · bash fences = 12 · text fences = 4 · token phrases = 0 · refspec hazard sites = 0
blocks (plan_blocks.py list): 28 total — plan_blocks.py:136 run-task.sh:28 cells.py:22 witness.py:30 hunks.py:17 tuples.py:20 transcribe.py:22 gate.py:21 skipset.py:20 entry.py:33 h_stub.py:34 h_test.py:29 h_e3pin.py:22 h_fidelity.py:39 rp_mutants.py:27 walk-A.expected:11 walk-B.expected:47 linux-container.sh:104 linux-suite.sh:132 task-0:70 task-1:38 task-2:54 task-3:40 task-4:53 task-5:49 task-6:58 task-7:39 task-8:36 
plan_blocks.py check, extract -> check per task:
  task-0  bytes=equal prologue=ok lines=70 spans=249 gates=43 foreign=0 omitted=0 out_of_order=0 rc=0 
  task-1  bytes=equal prologue=ok lines=38 spans=113 gates=20 foreign=0 omitted=0 out_of_order=0 rc=0 
  task-2  bytes=equal prologue=ok lines=54 spans=104 gates=32 foreign=0 omitted=0 out_of_order=0 rc=0 
  task-3  bytes=equal prologue=ok lines=40 spans=48 gates=20 foreign=0 omitted=0 out_of_order=0 rc=0 
  task-4  bytes=equal prologue=ok lines=53 spans=68 gates=32 foreign=0 omitted=0 out_of_order=0 rc=0 
  task-5  bytes=equal prologue=ok lines=49 spans=111 gates=27 foreign=0 omitted=0 out_of_order=0 rc=0 
  task-6  bytes=equal prologue=ok lines=58 spans=149 gates=33 foreign=0 omitted=0 out_of_order=0 rc=0 
  task-7  bytes=equal prologue=ok lines=39 spans=94 gates=20 foreign=0 omitted=0 out_of_order=0 rc=0 
  task-8  bytes=equal prologue=ok lines=36 spans=36 gates=14 foreign=0 omitted=0 out_of_order=0 rc=0 
prologue: PROLOGUE occurrences in plan_blocks.py = 5 · every task block opens with it (prologue=ok above)
evidence pipelines inside backtick spans (protocol + Task sections, fences excluded) = 0 · spans scanned = 1079
gate spans in the scanned sections = 252 · with an angle-bracket template = 0 · with an ellipsis = 0
green-only Linux phrasing in operative text = 1 hit(s): the live Global constraint H still said "`harness-selftest` GREEN on both targets at C+H"; it now carries the two
'runner_manifest' in operative text (outside the history) = 1 (the Revision 13 paragraph's historical description only)
'shasum -a 256 [^|]*\| *cut' pipelines anywhere in the artifact = 0
ledger gate: 26 required keys in the printf list (Task 6 line) = 26 · "-eq 28" total-line gates = 6 · "ctest-key.value" binds = 18 · two-outcome receipts named = 5 · "pass-r435-disclosed-registered-red" occurrences = 13
linux-suite.sh aggregate loop names ctest_rc = 0 (0 = excluded) · records the ctest key as data = 1 · linux-container.sh detaches at the expected head = 1
rev13 -> rev14 diff (git diff 5bec7cd 8183e0f): 1026 insertions, 105 deletions
```

## The four findings, where each is closed in the artifact

- **F1 (runner completeness / glue)** → `## Per-task runner protocol` (0)–(e) + the `plan_blocks.py` and `run-task.sh` blocks; nine `#### Task N runner — BLOCK task-N` blocks; each task's `**Runner plumbing (Task N)**` paragraph states the block's non-Step lines; the Revision 14 paragraph records the controls. The check is bidirectional and exact: runner == block bytes; block lines ⊆ Steps spans ∪ prologue ∪ comments; gate spans ⊆ block lines, in order. Validated runner-side (gate-only, off-plan+glue, swap, drop, prologue edit → exit 5) and plan-side (a Step span removed → FOREIGN; edited → FOREIGN + OMITTED).
- **F2 (ledger identities; Phase-S as executable text)** → the `linux-suite.sh` and `linux-container.sh` blocks (Task 0 Step 0b materializes and digest-pins them; Tasks 2/4/6 mount them through `$EVID`); the ledger gate line in Task 6 Step 2 (and its P/C twins in Tasks 2 and 4). Validated: the shimmed Phase-S fault matrix (8 cases) + 6 ledger mutations + the sealed token-11 ledger as-recorded (STOP) and re-aggregated (PASS) + three real-container controls (Phase R red; non-writable evidence dir; the finalize trap's copy-out failure).
- **F3 (green-only term)** → Global constraint H rewritten to the two-outcome contract; the operative-text scan for `GREEN on both`, `rc 0 on both`, `REQUIRED green`, `suites REQUIRED`, `both targets … green|rc 0` returns only the two-outcome sentences and the Revision-14 quotation of the old text.
- **F4 (hash pipelines)** → the plan-hash gate ((0) and the controller), the runner self-digest (prologue), Task 1 Step 5 (iv)'s sealed-log pin, Task 6 Step 2's archived-discriminator pin, Task 7's codex digest — each a `shasum` into a file, then `cut` / `grep -c -F` on the file with its own status. The scan of every backtick span in the protocol and Task sections for `| sed|sort|grep|awk|cut|tar|tr|wc|head|tail|xargs|python3` returns 0.
- **Two self-corrections** (stated in the Revision 14 paragraph): Task 4's container mounts the MAIN repository (a `--shared` scratch clone's alternates are host paths) and Phase T detaches at the expected head; Task 2 Step 3's ENTRY is an executable helper (`entry.py`).

## Your review

The artifact at e9d51695395aa8bde2ebdd6c11253724d00f62b46d7a1a7dc2d823fab7936299 is the object; every claim above names its producer. Please grade the blocks as the executable text they are (the Steps are the same text, bound by the check). On approve, record iso rev9's pin `59f9c0d1d71f4604801758880865fdcc21fe61db8ad2841c488eabc65118dc23` as the bar text's source; the token mints only after your approve AND rev9's Master-Reviewer approval. A must-revise names the line; I revise the artifact and re-file with the next handoff id.

ACTIONS_GIT_REF: docs-lane writes only — the rev14 artifact committed (8183e0f), the validation logs under results/; this relay via the engine; the root-mode sweep before submission (draft present; zero draft lines) and after (archived). No product byte, no candidate byte, no push, no PR, no merge, no release.
RELAY_LINT: engine-rendered submission; per-file v2.9.2 lint rides the daemon gate (the draft pre-linted per-file; the four commission-surface lines copied byte-for-byte from the filed plan-14 carrier); the root-mode sweep with the draft present showed zero lines for this draft.
CARRY_LIST (per D-8.5, this turn's pending hops — path + the one TO seat):
- rendered successor of this draft -> intg.pair-implementer
FINAL_GIT_STATUS_SHORT:
 M .relays/s4/INDEX.md
 M .relays/s4/SEATS.md
?? docs/sprints/2026-08-04-s4-step4/MIGRATION-adt-skills-2.9-20260816.md
?? relay-draft-intg-task4-stop.md
Literal status for the lane's own surfaces at write time (inherited S4 rows and two inherited untracked files omitted from the line list above only where the lane never wrote them; the full inherited list is unchanged from the plan-14 filing); the shared INDEX carries sibling-authored rows not claimed clean here.
