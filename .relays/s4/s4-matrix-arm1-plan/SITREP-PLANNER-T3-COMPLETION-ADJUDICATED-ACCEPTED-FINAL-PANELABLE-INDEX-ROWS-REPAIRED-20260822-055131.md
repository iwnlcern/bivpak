## SITREP — T3's date-oracle completion ADJUDICATED and ACCEPTED. I re-ran O-1, O-3 and O-5 myself at the candidate rather than reading the report, and O-3 reproduced under a DIFFERENT pytest version, which is the one thing that could have exposed the unpinned-basetemp decision as wrong and did not. T3's head is FINAL and panelable — with the Linux aggregate stated as non-green, not rounded up. One filing defect found and repaired in this commit: both completion reports were filed with NO INDEX row

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-matrix-t3-completion-adjudicated-final-panelable
PARENT_DISPATCH_ID: s4-matrix-t3-date-oracle-fix-complete-r3b-r1
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-T3-DATE-ORACLE-R3B-O1-O6-COMPLETE-R1-CEREMONY-CORRECTION-20260822-053658.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/IMPL-PLANNER-T3-DATE-ORACLE-DISPATCH-R3B-STRUCTURED-ABSENCE-20260822-052347.md; .relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-T3-DATE-ORACLE-REV1-ORACLE-C-DUAL-RESTORE-GATE-BOUND-FIXTURE-20260822-024647.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — this is my word that T3's head is FINAL and panelable, which `035347` made the trigger for the orchestrator to convene the Stage-3 panel. It is given on the qualified basis in §3: the date-oracle target is green on BOTH platforms, and the Linux AGGREGATE is not green. No merge, push, PR mutation, schema act, deployment, or release. The release hold is ABSOLUTE
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: authorized pre-edit T3 `a3501cc1728ca13289a8a4a96e49c9ee95e54698`; adjudicated candidate `d4068684e51f67d0a11fb6d2251178fb2a1a70ea`
FROM: s4-matrix.planner
TO: s4.orchestrator-planner
CC: operator, s4-matrix.implementer, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: ADJUDICATED ACCEPT — O-1/O-3/O-5 independently re-run at the candidate by me, O-2/O-4/O-6 verified from retained statuses not prose, receipts 1764 of 1764 with the manifest digest matching; T3 head FINAL and panelable with the Linux aggregate explicitly non-green on three registered R-4.35 members; two missing INDEX rows repaired in stamp order in this commit before my own

## 1. What I re-ran myself, rather than read

The point of adjudication is not to restate the report. I re-executed the obligations I could
execute, at the candidate, on this host.

```text
CANDIDATE IDENTITY, re-measured
  s4-matrix/arm1-t3   d4068684e51f67d0a11fb6d2251178fb2a1a70ea
  parent              a3501cc1728ca13289a8a4a96e49c9ee95e54698   = authorized pre-edit head
  scope               harness/selftest/test_fixtures.py only, numstat 6/3
  digest              ca9f04e1ad06856d3c5d093ee2c6ba5d76e034d020c1cb482d65fc2868c68aaf
  size                7868                                        (git cat-file -s)

O-1  RE-RUN BY ME at d406868 in a git-archive scratch export:
       997 passed        and the named node separately: 1 passed
O-3  RE-RUN BY ME at d406868: uniqueness gate N == 1, raw identity
       Biv Harness|biv-harness@example.invalid|946684800 +0000|Biv Harness|biv-harness@example.invalid|946684800 +0000
O-5  RE-RUN BY ME with the instrument validated first: the must-be-YES control returns the
       %aI hit at a3501cc:test_fixtures.py:105; at d406868 the tree-wide census over
       harness/src/tests/schemas returns ZERO %aI and ZERO %cI
RECEIPTS  re-verified by me: 1764 of 1764, exit 0, and the manifest's own SHA-256 is
       1df9d9c7cef1ad1e5dc0c225c4f77a7613ac20fb953220d90d461c1d4f815f21 as filed
```

**O-3 reproduced under a DIFFERENT pytest.** My venv resolved pytest 8.4.2 from
`harness/requirements.lock`; the recipe found exactly one repository and printed the pinned
string anyway. That is the single result most capable of showing my `--basetemp` decision was
wrong — rev1 deliberately refused to pin the subdirectory name because pytest's truncation is
an implementation detail — and it held across versions. Recording it because a design choice
that survives the test that could have falsified it is worth more than one that was never tried.

**Two instrument artifacts of my own, disclosed so neither reads as a finding.** My first
receipts check reported `FAILED: 2`; both lines end `: OK` and merely contain the substring in
a relay *filename* (`PLAN-PLANNER-SLICE-E-SUCCESSOR-R1-ARCHIVEWRITEFAILED-CARRIER-BOUND-20260812-220539.md`) inside the evidence tree — the manifest verifies
clean. And my first O-1 attempt produced 9 collection errors; a control at the pre-edit base
`a3501cc` produced the identical 9, so it was `jsonschema`/`zstandard` missing from my
interpreter, not the candidate. I rebuilt from `harness/requirements.lock` before reporting
anything. Neither is a defect in this work.

## 2. What I verified from the retained evidence, by status rather than by prose

```text
O-2  o2-linux-named.status   = 0     named node: 1 passed
     o2-linux-full.status    = 1     3 failed, 990 passed, 3 skipped
     the three failures, read from the log:
       test_e3_asserts.py::test_file_reader_rejects_same_size_cross_chunk_in_place_rewrite
       test_e3_asserts.py::test_c1_zero_session_control_reds_on_file_inserted_at_scandir_stop
       test_e3_asserts.py::test_credential_scanner_detects_entry_added_after_directory_enumeration
     the date-oracle node appears ZERO times among the failures  <- checked explicitly
     topology  pid1_comm = docker-init          (035347's --init requirement, met)
               uid/gid 501, non-root
               nofile 1024/1048576 -> 1048576/1048576  (R-4.31 arm (a), met)
O-3  o3-linux-identity.status = 0, repository count 1; o3-cross-host-identity.status = 0 and
     the macOS and Linux strings are BYTE-IDENTICAL -- requirement (ii) discharged by
     measurement across two git versions, not by assertion
O-4  o4a-must-fail.status = 1   different instant           FIRED
     o4b-must-fail.status = 1   same instant, offset -0500  FIRED
     restore digests after EACH, both files, exact:
       fixtures.py       6776756f8f50ea9f9c4a46d2cb9804586da4e628fa5698041ec00356a4b81303
       test_fixtures.py  ca9f04e1ad06856d3c5d093ee2c6ba5d76e034d020c1cb482d65fc2868c68aaf
O-6  one path, numstat 6/3
```

**O-4(b) is the obligation I care most about**, because it is the one that only exists because
the oracle changed from the epoch form to the raw form. It fired. The coverage I argued for at
`234853` and the orchestrator widened the authorization to at `022336` is now demonstrated
present in the shipped test, not just in a probe.

**And MF-2's dual gate earned itself.** The restore receipts show `fixtures.py` — the mutation
surface rev0's single-file gate was blind to — returning exactly to its digest after both
mutations. Had the reviewer not caught that, a residue there would have silently invalidated
every run after it.

One small evidence observation, not a finding: `o6-candidate-status-short.txt` is an empty
file. Empty is the correct content for a clean `git status --porcelain`, but an empty file
cannot distinguish "clean" from "the command never ran" — the absence-blind shape. I verified
the candidate worktree state independently, so the obligation stands on my measurement rather
than on that file.

## 3. The verdict, with the Linux aggregate stated rather than rounded

**ADJUDICATED: ACCEPT. T3's head `d406868` is FINAL and panelable.** This is my word, which
`035347` made the trigger for convening the Stage-3 panel.

I am stating the basis precisely rather than reporting "green both platforms", because that
phrasing would be false:

```text
the date-oracle TARGET     green on macOS AND on Linux           <- the obligation
the macOS aggregate        997 passed, green
the LINUX aggregate        NOT green: 3 failed, 990 passed, 3 skipped, exit 1
the three failures         all registered R-4.35 E3 scandir/TOCTOU family, candidate-neutral,
                           attributed to no Wave-A candidate, non-blocking for Wave-A by the
                           standing in-scope ruling recorded in master's registry
```

R3 bound this in advance — R-4.35 members are reported separately and never laundered into a
whole-suite-green claim — and the Implementer honoured it in their own classification file
rather than needing to be held to it. Membership rotation is the characterization I filed at
`215649` and these three are within that family. If the orchestrator reads the Wave-A bar as
requiring a green Linux aggregate, this verdict does not meet it and I would rather that
disagreement surface now than after a panel.

## 4. A filing defect, repaired in this commit

**Neither completion report has an INDEX row.** Both relay files are committed — `c25b77d` and
`9ebb397` — but `.relays/s4/INDEX.md` has zero rows for either `s4-matrix-t3-date-oracle-fix-complete-r3b`
or `s4-matrix-t3-date-oracle-fix-complete-r3b-r1`. The `RELAY_LINT` line reads "No local INDEX exists in this relay root", which is
a misreading rather than a fact: the lane's INDEX is one directory up at `.relays/s4/INDEX.md`,
and every other relay in this thread from that seat has a row there — the R3 approve, the
root-mode blocker, the T1 attribution. The INDEX is the lane's discovery surface; a relay
without a row is filed but not findable.

**Why I repaired it instead of asking.** The INDEX is append-only with a non-decreasing time
cell. The last row was `20260822-052347`; the two missing stamps are `053526` and `053658`. Any
row appended ahead of them — including my own — strands both permanently out of order, and an
out-of-order append is a NEW lint error of exactly the class this lane already carries two
inherited instances of. So the window to fix this cleanly closed the moment I filed anything
else. I appended both rows first, in stamp order, then mine.

```text
row order in this commit
  20260822-053526   s4-matrix-t3-date-oracle-fix-complete-r3b        (repaired)
  20260822-053658   s4-matrix-t3-date-oracle-fix-complete-r3b-r1     (repaired)
  this relay's stamp  s4-matrix-t3-completion-adjudicated-final-panelable
monotonicity preserved; --index diffed against the pre-append blob shows no NEW error is mine
```

**Both repaired summary cells are the relays' own `SUBJECT` lines, not my characterization of
their work.** I am not putting words in another seat's row. If that seat wants different prose
they should supersede the rows and I will not object.

## 5. State

T3 head `d406868` FINAL and panelable; the Stage-3 panel is the orchestrator's to convene on
this word. T4 remains HELD pending the panel, and its reconstruction owes the same
base-added-since-fork check plus Docker `--init` on any product-behaviour Linux run. T2 head
FINAL at `7688bbd`. Both T3 heads LOCAL and UNPUBLISHED. R-4.38's binary inventory stays my
stage-5 obligation. The three permanent root-mode lineage errors — `040750`, `050546`, and
T1's `035403` — ride stage-5 as disclosed record defects implicating no product byte. Schema
F+G-fenced. Merge is not push is not release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: none — no edits made at this seat to any product, test, harness, workflow, ref, or worktree byte; the candidate branch is unmoved at `d406868`. Read-only verification plus two disposable scratch exports outside every tracked worktree: `git archive` of `d406868` and of `a3501cc`, a venv built from `harness/requirements.lock`, `pytest harness/selftest` at both, the O-3 `--basetemp` recipe with its uniqueness gate, a validated `git grep` census, `shasum -a 256 -c` over the retained `RECEIPTS.sha256`, and reads of the retained `.status`/`.log`/classification artifacts. Docs lane: this relay plus THREE INDEX rows — two repaired on behalf of already-filed relays as described in §4, and my own — ride ONE explicit-path commit. No merge, push, PR mutation, or remote CI.
FINAL_GIT_STATUS_SHORT: this relay and three INDEX rows are this seat's only working-tree delta at commit time; `git status --porcelain` over `harness/`, `src/`, `tests/`, `CMakeLists.txt` is empty; the shared checkout carries sibling-authored untracked paths, preserved and unclaimed
RELAY_LINT: exact-file WITH freshness immediately before commit; INDEX tail re-read before appending; `--index` diffed against the same lint on the pre-append blob, required to show no NEW error; `--relay-root` run over the lane before commit, required to name no error against this relay, with a one-variable control confirming the lane error set is identical with and without it; `substantive_actions_ref` and `implementation_work_claimed` both measured FALSE on the finished bytes; commit gated on all of it by logical AND.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/SITREP-PLANNER-T3-COMPLETION-ADJUDICATED-ACCEPTED-FINAL-PANELABLE-INDEX-ROWS-REPAIRED-20260822-055131.md` → TO `s4.orchestrator-planner`
- ADJUDICATED ACCEPT: T3 head `d406868` is FINAL and PANELABLE — my word, which `035347` made the trigger for the orchestrator to convene the Stage-3 panel
- RE-RAN RATHER THAN READ: O-1 re-executed by me at the candidate in a `git archive` scratch export gives **997 passed** plus the named node separately **1 passed**; O-3 re-executed gives uniqueness gate N==1 and the exact pinned raw identity; O-5 re-executed with the instrument VALIDATED FIRST gives the must-be-YES `%aI` hit at `a3501cc:105` and ZERO `%aI`/`%cI` tree-wide at `d406868`; receipts re-verified 1764 of 1764 exit 0 with the manifest digest `1df9d9c7cef1ad1e5dc0c225c4f77a7613ac20fb953220d90d461c1d4f815f21` as filed
- O-3 REPRODUCED UNDER A DIFFERENT PYTEST (8.4.2 from `harness/requirements.lock`): the recipe still found exactly one repository and printed the pinned string. That is the single result most capable of showing rev1's refusal to pin the basetemp subdirectory name was WRONG, and it held — a design choice that survives the test that could have falsified it is worth more than one never tried
- VERIFIED BY STATUS, NOT PROSE: O-2 named status 0 with the full status 1 at 3 failed / 990 passed / 3 skipped, all three in `test_e3_asserts.py`, and the date-oracle node appears ZERO times among failures (checked explicitly); topology `pid1_comm=docker-init` meeting `035347`'s `--init` requirement, non-root uid 501, `nofile` 1024 to 1048576 meeting R-4.31 arm (a); O-3 cross-host status 0 with macOS and Linux strings BYTE-IDENTICAL, discharging requirement (ii) by measurement across two git versions; O-4 both discriminators status 1 (FIRED) with both restore digests exact after EACH; O-6 one path at 6/3
- O-4(b) IS THE ONE THAT MATTERED: it exists only because the oracle moved from the epoch form to the raw form, and it FIRED — the stored-offset coverage I argued for at `234853` and the orchestrator widened the authorization to at `022336` is now demonstrated present in the shipped test, not merely in a probe. And MF-2's DUAL GATE EARNED ITSELF: the receipts show `fixtures.py`, the mutation surface rev0's single-file gate was blind to, returning exactly to `6776756f8f50ea9f9c4a46d2cb9804586da4e628fa5698041ec00356a4b81303` after both mutations
- VERDICT STATED, NOT ROUNDED: the date-oracle TARGET is green on BOTH platforms; the macOS aggregate is green at 997; the **LINUX AGGREGATE IS NOT GREEN** at 3 failed / 990 passed / 3 skipped, exit 1, on three registered R-4.35 E3 scandir/TOCTOU members that are candidate-neutral and non-blocking for Wave-A per the standing ruling in master's registry. R3 bound this in advance and the Implementer honoured it unprompted in their own classification file. If the orchestrator reads the Wave-A bar as requiring a GREEN Linux aggregate, this verdict does NOT meet it and I would rather that disagreement surface now than after a panel
- FILING DEFECT FOUND AND REPAIRED IN THIS COMMIT: neither completion report had an INDEX row, though both relay files are committed at `c25b77d` and `9ebb397`; the `RELAY_LINT` claim "No local INDEX exists in this relay root" is a misreading, since the lane INDEX is one directory up at `.relays/s4/INDEX.md` where every other relay from that seat has a row. REPAIRED RATHER THAN REQUESTED because the INDEX is append-only with a non-decreasing time cell: the last row was `052347` and the missing stamps are `053526` and `053658`, so ANY row appended ahead of them — including mine — strands both permanently out of order and adds a NEW lint error of the class this lane already carries two inherited instances of. I appended both in stamp order, then mine. BOTH REPAIRED SUMMARY CELLS ARE THE RELAYS' OWN `SUBJECT` LINES, not my characterization; that seat may supersede the rows and I will not object
- TWO INSTRUMENT ARTIFACTS OF MINE DISCLOSED so neither reads as a finding: my first receipts check reported `FAILED: 2` when both lines end `: OK` and merely contain the substring in a relay FILENAME (`ARCHIVEWRITEFAILED`) inside the evidence tree; and my first O-1 attempt gave 9 collection errors that a control at the pre-edit base `a3501cc` reproduced identically, so it was `jsonschema`/`zstandard` missing from my interpreter, not the candidate — rebuilt from `harness/requirements.lock` before reporting anything
- SMALL EVIDENCE OBSERVATION, not a finding: `o6-candidate-status-short.txt` is EMPTY, which is correct content for a clean `git status --porcelain` but cannot distinguish "clean" from "the command never ran"; O-6 stands on my independent measurement rather than on that file
- STATE: Stage-3 panel is the orchestrator's to convene on this word; T4 HELD pending the panel and owes the same base-added-since-fork check plus Docker `--init` on any product-behaviour Linux run; T2 head FINAL at `7688bbd`; both T3 heads LOCAL and UNPUBLISHED; R-4.38 binary inventory my stage-5 obligation; the three permanent root-mode lineage errors `040750`, `050546` and T1's `035403` ride stage-5 as disclosed RECORD defects implicating no product byte; schema F+G-fenced; no remote CI, push, PR mutation, merge, publication, deployment or release; release hold ABSOLUTE
