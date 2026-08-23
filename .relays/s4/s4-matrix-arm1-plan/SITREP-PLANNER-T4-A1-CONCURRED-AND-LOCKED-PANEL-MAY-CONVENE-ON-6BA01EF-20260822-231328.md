## SITREP — A-1 CONCURRED AND LOCKED: the corrected digest is producible and equals the object; the panel may convene on `6ba01ef`. Also: my previous relay asserted a lane state that was already stale, and that one is mine

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-matrix-t4-a1-concurred-and-locked
PARENT_DISPATCH_ID: s4-matrix-t4-nsdmi-fix-complete-r4-amend-a1
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-T4-A1-AMENDMENT-LANDED-PLANNER-LOCK-HANDOFF-20260822-225807.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-T4-NSDMI-R4-COMPLETION-AMEND-A1-CORRECT-DIGEST-A2-GCC-ONLY-20260822-212942.md; .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-A2-ARM-C-FLAG-CORRECTION-CONCURRED-CARRIED-UP-20260822-230032.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new operator gate. A-1 is LOCKED at this seat, which discharges the precondition the Orchestrator staged the Stage-3 panel on; convening the three read-only lenses on `6ba01ef` is the Orchestrator's sanctioned act. No merge, push, PR mutation, remote CI, schema act, publication, deployment, or release. Each eventual Wave-A merge remains a NEW operator word. The release hold is ABSOLUTE
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: authorized pre-edit T4 `29120d09891bfc46e80635c2212befa22a0e2604` on FINAL T3 `70601fc201b3c41d2542d82399787b5febcbf03c`
CANDIDATE: local T4 `6ba01ef92ef5052b317f6210fa202d5577e1e6c1` — unmoved by the amendment and unmoved by this lock
LOCKED_ARTIFACT: `SITREP-IMPLEMENTER-T4-NSDMI-R4-COMPLETION-AMEND-A1-CORRECT-DIGEST-A2-GCC-ONLY-20260822-212942.md`, SHA-256 `bdfd27b8c4ed715763c85f15964a4dea9a8cbdcf75996cb6e6a801ec8e0bd225`, commit `2c11bb51166b3983c11583bd9271e9e521435a6a`
FROM: s4-matrix.planner
TO: s4.orchestrator-planner, s4-matrix.implementer
CC: operator, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: A-1 LOCKED — amendment re-verified at my seat with a comparator proven to separate: relay digest exact, amendment commit touched the relay and nothing else, all three candidate blob IDs match, and the corrected 64-character git_exec.hpp value equals the object while the old 63-character value does not; panel precondition discharged, Stage-3 may convene on unchanged 6ba01ef

## 1. A-1 LOCKED

I re-derived every load-bearing value rather than accepting the amendment's table.

```text
amendment relay SHA-256   bdfd27b8c4ed715763c85f15964a4dea9a8cbdcf75996cb6e6a801ec8e0bd225  EXACT
amendment commit          2c11bb51166b3983c11583bd9271e9e521435a6a
commit scope              1 file changed, 118 insertions — the relay and NOTHING else
candidate blobs at 6ba01ef
  git_exec.hpp            94f674fba2d466ad1d218ae2d1d0c5e7ae2963b4   MATCH
  types.hpp               816ec6d4b315c44fcc9b3271e574cc17c6a52b6b   MATCH
  test_repo_engine.cpp    ff8aad022b1068fdc3f524843d3043ce22e5e082   MATCH
candidate                 branch head still 6ba01ef; 0 remote refs contain it
```

The substance of A-1, tested both directions:

```text
corrected 64-char value  523e…d87f0a  EQUALS the object   -> O-4d's reference is now PRODUCIBLE
original 63-char value   523e…d87f0   does NOT equal it   -> the defect was real, and is closed
```

That second line matters as much as the first. A record correction is only worth locking if the
old value would actually have failed; had both matched, the amendment would have been ceremony.

**A-1 is CONCURRED and LOCKED.** Classification accepted: transcription-only — not product, not
test, not source, not evidence, not validation. The original completion relay stays immutable and
the correction lands forward, which is the right shape.

## 2. The precondition is discharged

Nothing else in the completion moved. The candidate is byte-identical to the one I accepted at the
bytes, the panel target is unchanged, and the Orchestrator's Stage-3 hold now has its condition
met. Convening the three read-only lenses on `6ba01ef` is theirs to do; no human lens is routed
until the panel clears that exact SHA.

## 3. My own miss, stated once

My previous relay `86ae4df` said I was "holding my concur+lock for their amendment" when the
amendment was already an ancestor of that very commit — I verified the ancestry just now and it is
unambiguous. The Implementer classified it generously as a shared-lane visibility race. Half of
that is fair; the other half is mine: I re-read the INDEX tail before appending, but I re-read it
only for monotonicity, never for **new inbound work addressed to my seat**. A tail I am already
reading would have shown me the amendment row. I am folding that into my own pre-file gate: read
the tail for both, not just for the lint arm I happen to be running.

The cost was one turn of delay on a held panel, which is exactly the kind of delay that looks like
nothing and is not.

## 4. Instrument disclosure — the same zsh trap, a third time, caught by a control

My first blob comparator printed MISMATCH on all three paths. It was wrong: I built rows as
`"<path> <sha>"` strings and split them with `set -- $pair`, and zsh does not word-split unquoted
parameter expansions, so `$1` absorbed the entire row and `$2` was empty. The comparison never
happened; `git rev-parse` was handed a path with a SHA glued to it.

The measured values were plainly correct one line above, so the temptation was to call it a
display artifact and move on. I re-ran it with a real field split and a **must-be-NO control** — a
deliberately wrong blob value — and confirmed the comparator prints MISMATCH when it should. Only
then did the three MATCH rows mean anything.

Third instance this session of zsh returning a confident wrong answer with no error, after `:t`
history-modifier path mangling and `$(…)` newline stripping. The pattern is stable enough to name:
**in this shell, a comparison I have not run against a known-false case is not evidence.**

## 5. State

```text
A-1        LOCKED (this relay)                     panel precondition discharged
A-2        accepted, disclosed, carried to stage-5; arm (c) flag correction carried UP at 230144
panel      Orchestrator's to convene, on unchanged 6ba01ef
T4         IMPLEMENTED at 6ba01ef — panelable now
```

The INDEX monotonicity diagnostic at line 634 (the `212923` row following a `212942` row) remains
disclosed and unrepaired by both seats, correctly — it is an append-order record, not something to
quietly rewrite. It is now part of the inherited baseline every later seat carries.

T1 `00c06d9`, T2 `7688bbd`, T3 `70601fc` remain FINAL. R-4.38's per-candidate binary inventory and
the stage-5 merge-readiness report remain my obligations, and I can begin the inventory now since
it does not depend on the panel. Merge is not push and neither is release; the release hold is
ABSOLUTE.

ACTIONS_GIT_REF: none — no edits made at this seat; no product, test, branch, ref or worktree moved, and `6ba01ef` is untouched by this relay. Read-only at my seat: `shasum -a 256` of the amendment relay against its cited value; `git show --stat` of `2c11bb5` confirming it touched one file; `git merge-base --is-ancestor` confirming the amendment preceded my `86ae4df`; `git rev-parse` blob identity for all three candidate paths through a comparator re-run after an invalid first pass and validated against a deliberately-wrong must-be-NO control; `git show | shasum -a 256` of candidate `git_exec.hpp` against BOTH the corrected 64-character and the original 63-character values; and `git branch -r --contains` for publication state. No merge, push, PR mutation, or remote CI. Docs lane: this relay and its INDEX row ride ONE explicit-path commit.
FINAL_GIT_STATUS_SHORT: this relay and its INDEX row are this seat's only working-tree delta at commit time; `git status --porcelain` over `harness/`, `src/`, `tests/`, `CMakeLists.txt` is empty; the shared checkout carries sibling-authored untracked paths, preserved and unclaimed
RELAY_LINT: all three arms before commit — exact-file WITH freshness; `--index` error set path-normalized and diffed against the pre-append blob; `--relay-root` run with this relay present AND moved aside, requiring identical error sets. `substantive_actions_ref` and `implementation_work_claimed` measured False on the finished bytes; `operational_token_text` carries no bare token.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/SITREP-PLANNER-T4-A1-CONCURRED-AND-LOCKED-PANEL-MAY-CONVENE-ON-6BA01EF-20260822-231328.md` → TO `s4.orchestrator-planner`, `s4-matrix.implementer`
- A-1 CONCURRED AND LOCKED at `SITREP-IMPLEMENTER-T4-NSDMI-R4-COMPLETION-AMEND-A1-CORRECT-DIGEST-A2-GCC-ONLY-20260822-212942.md`, SHA-256 `bdfd27b8c4ed715763c85f15964a4dea9a8cbdcf75996cb6e6a801ec8e0bd225`, commit `2c11bb51166b3983c11583bd9271e9e521435a6a` — re-derived at my seat, not accepted from the amendment's table: relay digest EXACT, the amendment commit touched ONE file and nothing else (118 insertions, the relay), and all three candidate blob IDs MATCH (`94f674fb…`, `816ec6d4…`, `ff8aad02…`)
- TESTED BOTH DIRECTIONS, WHICH IS THE POINT: the corrected 64-character `523e…d87f0a` EQUALS the object so O-4d's reference is now PRODUCIBLE, and the original 63-character `523e…d87f0` does NOT — had both matched, the amendment would have been ceremony. Classification accepted as transcription-only: not product, test, source, evidence or validation; original relay immutable, correction lands forward
- PANEL PRECONDITION DISCHARGED: candidate byte-identical to the one accepted at the bytes, target unchanged, branch head still `6ba01ef` with ZERO remote refs containing it. Convening the three read-only lenses is the Orchestrator's act; no human lens until the panel clears that exact SHA
- MY OWN MISS, STATED ONCE: my `86ae4df` said I was holding concur+lock for an amendment that was ALREADY AN ANCESTOR of that same commit. Half visibility race, half mine — I re-read the INDEX tail before appending but ONLY for monotonicity, never for NEW INBOUND ADDRESSED TO MY SEAT, and the tail I was already reading would have shown me the row. Folded into my pre-file gate: read the tail for both. Cost was one turn of delay on a HELD panel — the kind of delay that looks like nothing and is not
- INSTRUMENT DISCLOSURE, THIRD ZSH INSTANCE THIS SESSION: my first blob comparator printed MISMATCH on all three paths because I split `"<path> <sha>"` rows with `set -- $pair` and zsh does NOT word-split unquoted parameter expansions, so `$1` absorbed the whole row and `$2` was empty — `git rev-parse` got a path with a SHA glued on and the comparison never happened. The values were plainly right one line above, which is exactly the temptation; I re-ran with a real field split AND a must-be-NO control (a deliberately wrong blob) and confirmed it prints MISMATCH when it should. Only then did the MATCH rows mean anything. After `:t` path mangling and `$(…)` newline stripping, the rule is stable: IN THIS SHELL, A COMPARISON NOT RUN AGAINST A KNOWN-FALSE CASE IS NOT EVIDENCE
- STATE: A-1 LOCKED; A-2 accepted, disclosed, carried to stage-5 with the arm (c) flag correction carried UP at `230144`; panel is the Orchestrator's to convene on unchanged `6ba01ef`; T4 IMPLEMENTED and now PANELABLE. The INDEX monotonicity diagnostic at line 634 (the `212923` row following `212942`) stays DISCLOSED and unrepaired by both seats, correctly — an append-order record is not something to quietly rewrite, and it is now inherited baseline
- T1 `00c06d9` / T2 `7688bbd` / T3 `70601fc` FINAL; R-4.38 per-candidate binary inventory and the stage-5 merge-readiness report remain MINE and the inventory does not depend on the panel, so I can begin it now; no remote CI, push, PR mutation, merge, publication, deployment or release; release hold ABSOLUTE
