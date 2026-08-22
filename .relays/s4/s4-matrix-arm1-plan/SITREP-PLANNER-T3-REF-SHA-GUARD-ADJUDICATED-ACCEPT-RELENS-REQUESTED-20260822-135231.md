## SITREP — ref-SHA guard ADJUDICATED and ACCEPTED at `70601fc`. I re-ran O-1a myself, ran my own discriminator against the new candidate, and read R-4.35's membership out of master's registry rather than taking the classifier's word — the rotated-in fourth member IS registered, so O-1b's STOP correctly did not fire. Focused re-lens requested. One minor evidence-hygiene note, not a finding

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-matrix-t3-ref-sha-guard-adjudicated-relens-requested
PARENT_DISPATCH_ID: s4-matrix-t3-ref-sha-guard-complete
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-T3-REF-SHA-GUARD-COMPLETE-20260822-133735.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-T3-REF-SHA-GUARD-R1-LINUX-PREDICATE-SPLIT-DUAL-GATE-INLINED-20260822-125850.md; .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-T3-PANEL-PASS-3-NONBLOCKING-CLOSE-REF-SHA-TEST-GAP-BEFORE-STAGE5-20260822-060538.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — this is my word that the guard cycle is complete and correct, which releases the FOCUSED RE-LENS `060538` promised on the three new tests alone. T3's head has moved to `70601fc`, so it is not final again until that re-lens returns. No merge, push, PR mutation, schema act, deployment, or release. The release hold is ABSOLUTE
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: authorized pre-edit T3 `d4068684e51f67d0a11fb6d2251178fb2a1a70ea`; adjudicated candidate `70601fc201b3c41d2542d82399787b5febcbf03c`
FROM: s4-matrix.planner
TO: s4.orchestrator-planner
CC: operator, s4-matrix.implementer, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: ADJUDICATED ACCEPT at 70601fc — O-1a re-run by me (3 nodes, 31, 1000), my own discriminator fires against the new candidate, R-4.35 membership read directly from master's registry confirming all three Linux failures are registered and outside-family is genuinely zero; receipts 42 of 42; focused re-lens requested on the three new tests alone

## 1. What I re-ran, rather than read

```text
CANDIDATE IDENTITY, re-measured at my seat
  s4-matrix/arm1-t3   70601fc201b3c41d2542d82399787b5febcbf03c
  parent              d4068684e51f67d0a11fb6d2251178fb2a1a70ea   = authorized pre-edit head
  scope               harness/selftest/test_compare.py only, numstat 57/0
  digest              a9d0a49fce30623c12e9be5520da717f9f62abebde8cc2d9cca7e62569217566
  size / blob         13889 / 8eedaad7b55e619cea5c9ac715140329db0295c5
  compare.py          afda520510161b353ead3bb596e5b26bf249866bc593b6632a20f7436cfe1aa4  UNCHANGED

O-1a  RE-RUN BY ME from a git-archive export of 70601fc:
        three named nodes   3 passed
        test_compare.py     31 passed
        full harness/selftest  1000 passed

O-4   the target digest reproduces in my export

RECEIPTS  re-verified by me: 42 of 42, exit 0, manifest SHA-256
          5805748acb8f31d1054b238dead621a2a36d21652a14fbd5e133bca24d6b2b87 as filed
```

**And I ran my own discriminator against the shipped candidate**, because a regression guard
that has never been shown to fail is not a guard:

```text
compare.py:236 neutered, indentation preserved, import sanity confirmed FIRST
  -> test_ref_restored_to_a_divergent_sha_reports_a_ref_mismatch   1 failed
compare.py restored to
  afda520510161b353ead3bb596e5b26bf249866bc593b6632a20f7436cfe1aa4        CONFIRMED
```

That is the whole point of this cycle discharged at my seat, not inherited: the branch-restored-
to-the-wrong-commit contract now has a test that demonstrably fails when the code stops
enforcing it.

## 2. The classifier correction — verified against the registry, not the report

This is the one claim in the report that could have hidden a STOP condition, so I did not take
it. The Linux run rotated in a failure name that was not in the previous sample, and the
Implementer widened the allowlist after reading master's registry. **A cited registry is not a
read registry**, so I read it:

```text
master/RESIDUALS.md, the R-4.35 entry, every test_ name it contains:
  test_c1_zero_session_control_reds_on_file_inserted_at_scandir_stop
  test_credential_scanner_detects_entry_added_after_directory_enumeration
  test_file_reader_rejects_same_size_cross_chunk_in_place_rewrite
  test_run_e3_session_inserted_at_scandir_stop_reds_c1_before_open
  -> exactly FOUR registered members
```

The three observed Linux failures are all in that set, including the rotated-in
`test_run_e3_session_inserted_at_scandir_stop_reds_c1_before_open`. So `outside_r435_count=0` is
correct, O-1b's STOP condition genuinely did not fire, and the four-member-with-rotating-
membership reading is the registry's own, not a convenient widening.

**Their handling of their own defect is the standard I want to name.** The r0 classifier
allowlisted only the three names from the *previous* sample — an allowlist built from an
observation rather than from the registry, which is the same family as the census whose reach I
got wrong on T2. They stopped on it, read the registry, corrected forward, and **preserved r0's
output and its non-zero status** instead of overwriting it. The retained Linux log is unchanged
and the aggregate is still reported non-green.

## 3. O-1b read by status, and the aggregate stated as it is

```text
linux-three-new-nodes.status   0     three named nodes PASSED explicitly
linux-full-selftest.status     1     3 failed, 993 passed, 3 skipped
failures (from the log, not the summary):
  test_file_reader_rejects_same_size_cross_chunk_in_place_rewrite
  test_c1_zero_session_control_reds_on_file_inserted_at_scandir_stop
  test_run_e3_session_inserted_at_scandir_stop_reds_c1_before_open
topology  pid1 docker-init (035347/R-4.40), non-root uid/gid 501,
          nofile 1024/1048576 -> 1048576/1048576 (R-4.31 arm (a))
classifier r0.status 1 (preserved defect)   r1.status 0 (corrected)
```

The aggregate landed exactly on the shape rev1 gave for orientation — 3 failed / 993 passed /
3 skipped — and rev1 was right not to make that a gate: had membership rotated to a *different*
count the run would still have been correct, and a pinned number would have manufactured a red
the candidate does not own.

O-2's three controls are recorded with the two traps rev1 named handled properly: the exact
source-line token asserted before each mutation, original indentation preserved, and
`bivharness.compare` imported successfully **before** any verdict was read. Dual restore gate
passed on both files after every arm.

## 4. One evidence-hygiene note, not a finding

```text
linux-r435-classification.txt      status 1   <- byte-identical to r0, i.e. SUPERSEDED
  95379e6d545b820654141d53a358ca17dec7278c443be0eb9ad1047546354da1
linux-r435-classification-r0.txt   status 1
  95379e6d545b820654141d53a358ca17dec7278c443be0eb9ad1047546354da1
linux-r435-classification-r1.txt   status 0   <- the corrected, authoritative result
  3005479e46d9e466ac5907f2cfdf892809e6a6c68a8055d543837e742b89f601
```

The **unsuffixed** artifact — the one a reader reaches for by its natural name — carries the
*superseded* r0 content and its failing status. Nothing is wrong with the work: r0 was correctly
preserved and r1 is correctly authoritative. But a future seat opening
`linux-r435-classification.status`, which looks like the canonical name, gets `1` and would
reasonably conclude the classification failed. That is the looks-authoritative-name-carries-the-
stale-result shape. Cheap remedy for next time: leave no unsuffixed twin, or make the unsuffixed
name a pointer to the authoritative revision. Raising it because evidence roots outlive the
cycle that wrote them.

## 5. Verdict and what I am asking for

**ADJUDICATED: ACCEPT.** The guard cycle is complete and correct at `70601fc`. All of rev1's
obligations are discharged: O-1a green at 1000 with the three nodes explicit, O-1b's three nodes
green with the aggregate recorded verbatim and every failure inside the registered family, O-2's
three controls firing with dual restore gates, O-3's one-file scope, O-4's digest.

**T3's head has moved**, so it is NOT final again until the focused re-lens returns. I am
requesting it now, scoped as `060538` framed it — **the three new tests alone**; the rest of T3
is panel-cleared at `d406868` and the delta from that head is one test file with zero deletions
and no production byte, so there is nothing else in the delta to re-audit.

Findings (1), (2) and (4) remain disposed as stage-4 notes and must ride the stage-5
merge-readiness report alongside R-4.35, R-4.38, R-4.40, and the three permanent root-mode
lineage record-defects. T4 stays HELD. T2 head FINAL at `7688bbd`. Both T3 heads LOCAL and
UNPUBLISHED. R-4.38's binary inventory stays my stage-5 obligation. Schema F+G-fenced. Merge is
not push is not release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: none — no edits made at this seat to any tracked byte; the candidate branch is unmoved at `70601fc` as its author left it. Read-only verification plus one disposable `git archive 70601fc` scratch export outside every tracked worktree, where the full selftest, the three named nodes, and one independent mutation discriminator (with import sanity first and restore afterwards) were executed against a venv built from `harness/requirements.lock`; `git cat-file -s`, `git rev-parse`, `git diff --numstat`, `shasum -a 256 -c` over the retained receipts, reads of the retained `.status`/`.log`/classification artifacts, and a direct read of the R-4.35 entry in master's `RESIDUALS.md`. No merge, push, PR mutation, or remote CI. Docs lane: this relay + its INDEX row ride ONE explicit-path commit.
FINAL_GIT_STATUS_SHORT: this relay and its INDEX row are this seat's only working-tree delta at commit time; `git status --porcelain` over `harness/`, `src/`, `tests/`, `CMakeLists.txt` is empty; the shared checkout carries sibling-authored untracked paths, preserved and unclaimed
RELAY_LINT: exact-file WITH freshness immediately before commit; INDEX tail re-read before appending; `--index` diffed against the same lint on the pre-append blob; `--relay-root` run before commit required to name no error against this relay; `substantive_actions_ref` and `implementation_work_claimed` both measured FALSE on the finished bytes. Commit gated by logical AND.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/SITREP-PLANNER-T3-REF-SHA-GUARD-ADJUDICATED-ACCEPT-RELENS-REQUESTED-20260822-135231.md` → TO `s4.orchestrator-planner`
- ADJUDICATED ACCEPT at `70601fc`: parent `d406868`, ONE file at numstat 57/0, digest `a9d0a49fce30623c12e9be5520da717f9f62abebde8cc2d9cca7e62569217566`, size 13889, blob `8eedaad7b55e619cea5c9ac715140329db0295c5`, and `compare.py` UNCHANGED at `afda520510161b353ead3bb596e5b26bf249866bc593b6632a20f7436cfe1aa4` — all re-measured at my seat
- RE-RAN RATHER THAN READ: O-1a from a `git archive` export gives three named nodes 3 passed, `test_compare.py` 31 passed, full selftest 1000 passed; the target digest reproduces; receipts re-verified 42 of 42 exit 0 with manifest `5805748acb8f31d1054b238dead621a2a36d21652a14fbd5e133bca24d6b2b87` as filed
- I RAN MY OWN DISCRIMINATOR against the SHIPPED candidate, because a regression guard never shown to fail is not a guard: neutering `compare.py:236` with indentation preserved and import sanity confirmed FIRST makes `test_ref_restored_to_a_divergent_sha_reports_a_ref_mismatch` fail, and `compare.py` restored exactly. The wrong-commit contract now has a test that demonstrably fails when the code stops enforcing it
- CLASSIFIER CORRECTION VERIFIED AGAINST THE REGISTRY, NOT THE REPORT, because it was the one claim that could have hidden a STOP: master's `RESIDUALS.md` R-4.35 entry names EXACTLY FOUR members and the rotated-in `test_run_e3_session_inserted_at_scandir_stop_reds_c1_before_open` IS one of them, so `outside_r435_count=0` is correct and O-1b's STOP genuinely did not fire. A cited registry is not a read registry
- THEIR HANDLING OF THEIR OWN DEFECT IS THE STANDARD: r0 allowlisted only the three names from the PREVIOUS sample — an allowlist built from an OBSERVATION rather than the registry, the same family as the census reach I got wrong on T2 — and they stopped on it, read the registry, corrected forward, and PRESERVED r0's output and non-zero status rather than overwriting it; the retained log is unchanged and the aggregate still reported non-green
- O-1b BY STATUS: three-new-nodes 0 (PASSED explicitly), full 1 at 3 failed / 993 passed / 3 skipped with the failures read from the LOG; topology pid1 `docker-init` (035347/R-4.40), non-root uid/gid 501, `nofile` 1024 to 1048576 (R-4.31 arm (a)); classifier r0 status 1 preserved and r1 status 0 corrected. The aggregate landed exactly on rev1's ORIENTATION shape, and rev1 was RIGHT not to gate it — a different rotation would still have been correct and a pinned number would have manufactured a red the candidate does not own
- O-2's THREE CONTROLS handled both traps rev1 named: exact source-line token asserted before each mutation, original indentation preserved, `bivharness.compare` imported successfully BEFORE any verdict was read; dual restore gate passed on both files after every arm
- EVIDENCE-HYGIENE NOTE, NOT A FINDING: the UNSUFFIXED `linux-r435-classification.txt`/`.status` is byte-identical to the SUPERSEDED r0 (digest `95379e6d`, status 1) while the corrected r1 (digest `3005479e`, status 0) carries the authoritative result — so a future seat opening the canonical-looking name gets `1` and would reasonably conclude the classification failed. Nothing is wrong with the work; the shape is looks-authoritative-name-carries-the-stale-result. Cheap remedy next time: no unsuffixed twin, or make the unsuffixed name point at the authoritative revision. Raised because evidence roots outlive the cycle that wrote them
- FOCUSED RE-LENS REQUESTED, scoped as `060538` framed it — THE THREE NEW TESTS ALONE. The rest of T3 is panel-cleared at `d406868` and the delta from that head is one test file with ZERO deletions and no production byte, so nothing else is in the delta to re-audit. T3's head MOVED, so it is NOT final again until that re-lens returns
- STATE: findings (1), (2), (4) remain disposed as stage-4 notes and must ride the stage-5 merge-readiness report alongside R-4.35, R-4.38, R-4.40 and the three permanent root-mode lineage record-defects; T4 HELD; T2 head FINAL at `7688bbd`; both T3 heads LOCAL and UNPUBLISHED; R-4.38 binary inventory my stage-5 obligation; schema F+G-fenced; no remote CI, push, PR mutation, merge, publication, deployment or release; release hold ABSOLUTE
