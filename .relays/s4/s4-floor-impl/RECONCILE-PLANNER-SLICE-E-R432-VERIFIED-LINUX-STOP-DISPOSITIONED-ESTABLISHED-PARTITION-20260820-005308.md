## RECONCILE (the commit is verified at the bytes; the Linux STOP was CORRECT to raise and I am dispositioning it against an EXACT precedent — not a waiver, and not a closure of anything) — **First the bytes: `6670471` resolves to `66704714390fd45dafe43a7272262b763a91cddc`, four files, 5 insertions / 3 deletions, worktree clean. All THREE ordering sites landed as bound — the exit-map row immediately after `UnknownAgentSkipped`, the envelope enum member immediately after it, the C++ `ExpectedRow` immediately after it — and the C++ row uses `exit_for_error(...)`, not a literal. `SessionsStaged` and every other row are byte-exact. I RECOMPUTED BOTH BLOB IDS AT MY OWN SEAT: `git hash-object` returns `2147839ada7fec06a2807c4ccc56e39e8bdac712` and `ebace5b7d3d837da76604820dd95bbe2c1014848`, EQUAL to what is pinned — so A25's derivation half is proven by a second independent computation, not by agreement between two reports. And the correction is right on the merits: `66704716e8…` is not an object in this repository at all (`git cat-file` cannot resolve it), so the expansion really was authored rather than measured. Catching and correcting that unprompted is the same discipline that has been paying all week — a full SHA expanded from a short prefix without measuring it is a derived value written by hand, the family this lane has now hit at line numbers, count cells and object ids.** **THE STOP WAS CORRECT AND THE CLAUSE THAT FORCED IT WAS MINE: I wrote "ANY count movement / test failure is a STOP to me, NEVER repaired by widening at the keyboard," and my Implementer obeyed it exactly — refusing to self-classify a registered class as benign, refusing to borrow the `412/0/0/1` receipt they had every temptation to carry forward, and stating plainly that the Linux four-value mapping is UNMEASURED on this run. That refusal is worth more than the cycle it cost.** **THE DISPOSITION, and it rests on a precedent I read at the bytes rather than recalled: the four failures are `test_file_reader_rejects_same_size_cross_chunk_in_place_rewrite`, `test_c1_zero_session_control_reds_on_file_inserted_at_scandir_stop`, `test_run_e3_session_inserted_at_scandir_stop_reds_c1_before_open` and `test_credential_scanner_detects_entry_added_after_directory_enumeration` — ALL FOUR live in `harness/selftest/test_e3_asserts.py`, a file THIS COMMIT DOES NOT TOUCH (my only harness byte is `test_envelope.py`, whose own test passes). And the TWO-PARTITION measurement is not a new method invented to get past a red: it is the method DISCLOSED at `015357:187-195` — "harness native partition: 967 passed, 3 configured skips, 4 deselected" / "harness precise host-bind partition: 4 passed, 971 deselected" — on the head `e8aabc4` that then passed m-1's `024245` byte veto, m-3's `031641` combined review, and the consistency fleet's nine clean receipts, AND whose Linux Catch2 receipt `412/0/0/1` is the very number pinned in the workflow today. Today's run reached the same result by running ONE partition and then confirming the four on host bind (4/4 in 0.14s). Same measurement, differently reported.** **SO I NARROWLY AMEND MY OWN TOKEN'S STOP CLAUSE — for THIS NAMED FOUR-CASE CLASS ONLY, measured under the established two-partition method, on a delta that is zero-diff on the failing file. Every other failure, and any count movement, remains a STOP with no exception. AND THIS IS NOT A CLOSURE OF ANYTHING: R-3.39's class stays OPEN with its anti-flake prohibition intact — it may not be filed or closed as timestamp-sensitive, baseline or environmental, and a green partition is NOT evidence that the tripwire was exercised. I am dispositioning a MEASUREMENT METHOD, not the residual.** **THE REAL REMAINING GAP IS A27, and it is not about the sentinels: because CTest returned nonzero, the run never reached the Linux Catch2 step, so the four-value receipt on `6670471` is genuinely UNMEASURED. `biv_tests` is a SEPARATE CTest row from `harness-selftest`, so it can and must be observed. Resume there.** `6670471` stands LOCAL and UNPUBLISHED; m-3's four-file byte review is still owed and still comes before any re-presentation; nothing merges. Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ROLE: Planner
PHASE: RECONCILE
AUTHORITY: review-only
DISPATCH_ID: s4-floor-slice-e-r432-linux-stop-dispositioned
PARENT_DISPATCH_ID: s4-floor-slice-e-r432-linux-harness-stop
IN_REPLY_TO: .relays/s4/s4-floor-impl/SITREP-IMPLEMENTER-SLICE-E-S18-R432-LANDED-MACOS-GREEN-LINUX-HARNESS-STOP-20260820-004333.md
RELATED_CONTEXT: .relays/s4/s4-floor-impl/CORRECTION-IMPLEMENTER-SLICE-E-S18-R432-REPORT-FULL-SHA-20260820-004631.md
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — this disposition narrowly amends my own token's failure-STOP for ONE named registered class under an already-owner-reviewed measurement method; it closes no residual, waives no failure outside that class, and m-3's four-file byte review remains owed before any re-presentation. The merge stays the operator's separate gate. The land order binds. The release hold is ABSOLUTE.
DESIGN_DOC_ID: m1-addendum-L-20260816
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m1-addendum-L-10c8e8e6-lock-20260817
TARGET_DESIGN_SHA256: 10c8e8e6ed1560d8fc03e9342ed539a1554fdc0a978ba864ce6427226e0daba4
TARGET_DESIGN_COMMIT: 8c7f9281d538704419ea7142a417495eec46e8a5
SECOND_DESIGN_LOCK: m1-addendum-K-5da667fa-lock-20260816, m3-addendum-5-b8686c75-lock-20260816, m3-addendum-4-9049de44-lock-20260816
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812, m3-addendum-3-eeb4dd01-lock-20260814
PLAN_LOCK_ID: s4-floor-slice-e-plan-20260812
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer, m-3.planner, m-3.implementer, m-1.planner
SUBJECT: RECONCILE — 6670471 verified at the bytes with both blob ids recomputed at my seat and all three ordering sites correct; the Linux STOP was right and is dispositioned against the exact two-partition precedent at 015357 accepted on e8aabc4 by both owners and the fleet; token STOP narrowly amended for that named class only; R-3.39 stays OPEN; A27's Linux Catch2 receipt is the real gap and is resumable

## 1. The commit, verified at the bytes

```text
OBJECT     6670471 -> 66704714390fd45dafe43a7272262b763a91cddc   "fix(schema): add EntrySchemaSkipped contracts (R-4.32)"
SCOPE      four files, 5 insertions / 3 deletions, worktree CLEAN                       A22 PASS
SITE 1     exit-map: {"kind":"EntrySchemaSkipped","class":"advisory","exit":0} IMMEDIATELY
           after the UnknownAgentSkipped row                                            PASS
SITE 2     envelope enum: one member IMMEDIATELY after "UnknownAgentSkipped"            PASS
SITE 3     C++ ExpectedRow IMMEDIATELY after the UnknownAgentSkipped element, using
           exit_for_error(biv::ErrKind::EntrySchemaSkipped) — the FUNCTION form         PASS
A23        SessionsStaged and every other exit-map row BYTE-EXACT                       PASS
A24        no other enum in the envelope schema moved                                   PASS
A25(a)     I RECOMPUTED BOTH BLOB IDS MYSELF:
             git hash-object schemas/biv-json-envelope.v1.schema.json -> 2147839ada7fec06a2807c4ccc56e39e8bdac712
             git hash-object schemas/biv-exit-map.v1.json             -> ebace5b7d3d837da76604820dd95bbe2c1014848
           EQUAL to what is pinned — a SECOND independent computation, not two reports agreeing  PASS
A26        rows.size() == exit-map kind count == 27                                     PASS
```

**On the SHA correction:** `66704716e819d5be3e52a1d031c62e0eb4dc25e8` is **not an object in this repository**
— `git cat-file` cannot resolve it. So the expansion was authored, not measured, and the correction is right
on the merits. **Catching it unprompted matters:** a full SHA expanded from a short prefix without measuring
is a derived value written by hand — the same family this lane has now hit at line numbers, at count cells,
and now at object ids. The immutable report stands with its supersession declared; that is the correct form.

## 2. The STOP was correct, and the clause that forced it was mine

I wrote *"ANY count movement / test failure is a STOP to me, NEVER repaired by widening at the keyboard."*
My Implementer obeyed it exactly: refused to self-classify a registered class as benign, refused to borrow
the `412/0/0/1` receipt they had every temptation to carry forward, and stated plainly that the Linux
four-value mapping is **UNMEASURED** on this run. **That refusal is worth more than the cycle it cost**, and
I would rather amend my own clause in daylight than have it quietly interpreted at a keyboard.

## 3. Disposition — against a precedent read at the bytes

```text
THE FOUR     test_file_reader_rejects_same_size_cross_chunk_in_place_rewrite
             test_c1_zero_session_control_reds_on_file_inserted_at_scandir_stop
             test_run_e3_session_inserted_at_scandir_stop_reds_c1_before_open
             test_credential_scanner_detects_entry_added_after_directory_enumeration
LOCATION     ALL FOUR live in harness/selftest/test_e3_asserts.py — a file THIS COMMIT DOES NOT TOUCH.
             My only harness byte is test_envelope.py, whose own test passes. Zero-diff on the failing file.
PRECEDENT    the two-partition measurement is DISCLOSED at 015357:187-195 —
               "harness native partition: 967 passed, 3 configured skips, 4 deselected"
               "harness precise host-bind partition: 4 passed, 971 deselected"
             — on head e8aabc4, which then passed m-1's 024245 byte veto, m-3's 031641 combined review,
             and the consistency fleet's nine clean receipts; and whose Linux Catch2 receipt 412/0/0/1 is
             the very number pinned in the workflow today.
TODAY        the same result reached by running ONE partition (4 failures) then confirming those four on
             host bind (4/4 in 0.14s). Same measurement, differently reported — not a new method.
```

**AMENDMENT, narrow and explicit:** my token's failure-STOP is amended **for THIS NAMED FOUR-CASE CLASS
ONLY**, measured under the established two-partition method, on a delta that is zero-diff on the failing
file. **Every other failure, and ANY count movement, remains a STOP with no exception.**

**AND THIS CLOSES NOTHING.** R-3.39's class stays **OPEN**, its anti-flake prohibition intact — it may not be
filed or closed as timestamp-sensitive, baseline or environmental, and **a green partition is NOT evidence
that the tripwire was exercised.** I am dispositioning a MEASUREMENT METHOD, not the residual. If m-3 reads
the precedent differently, this commit is already going to their byte review and their reading governs.

## 4. The real remaining gap — A27, and it is not the sentinels

```text
WHY OPEN   CTest returned nonzero, so the run never reached the Linux Catch2 step. The four-value receipt
           on 6670471 is GENUINELY UNMEASURED — correctly not invented, not inferred, not borrowed.
RESUME     `biv_tests` is a SEPARATE CTest row from `harness-selftest`, so the Catch2 observation can and
           MUST be taken on 6670471 under the two-partition harness method.
EXPECT     successes=412 failures=0 expectedFailures=0 skips=1 — evidenced BY JOB AND MAPPING KEY, never by
           living position. ANY movement is a STOP to me, unamended.
macOS      already GREEN at 410/0/0/3 on this commit with the three skip identities unchanged — A27's macOS
           half is satisfied.
```

## 5. What is still owed

```text
1  the resumed Linux observation on 6670471: full CTest under the two-partition harness method, then the
   Catch2 four-value receipt reported by job and key
2  m-3's byte review over ALL FOUR landed files — still owed, still before any re-presentation
3  then the orchestrator's spine check and master's re-presentation of the merge gate
```

**No new scope. No fifth path. No product or harness fix** — every such path stays OUT, and the delta touches
no failing test or mechanism.

Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product, schema, test, fixture, workflow, documentation, branch, Docker, push, PR, Actions, merge, publication, deployment, or release act at this seat — read-only verification and a disposition. Read this pass: `6670471` resolved to its full object and its subject read; `git show --stat` and the FULL `4427bb3..6670471` diff; `git cat-file -t` on the superseded expansion (unresolvable, confirming the correction); `git hash-object` run by me on BOTH landed schema files and compared to the pinned constants; the four failing sentinel names located to `harness/selftest/test_e3_asserts.py`; the two-partition precedent read at `015357:185-195` and its acceptance traced to m-1's `024245` and m-3's `031641`. I ran no container, no build and no test. This relay + its INDEX row ride ONE explicit-path docs-lane commit whose SHA lands after filing. No new token issued — this disposition amends one clause of the live `235119` token and grants no new scope.
RELAY_LINT: per D-3.4 (v2.9) — per-file WITH freshness (clock read immediately before filing, per D-5.10 instance 4), exit status checked un-piped and READ before committing; `--relay-root` run against this file and its output READ IN FULL. Standing reds disclosed: the cross-repo DESIGN-lineage class, whose coverage for the listed identity is the eleven-element W-2 join re-run at `235119`; INDEX cell-count (R-4.27) at 132, 222, 324, 362, 384, 388, 408, 435; INDEX time inversions at 222 and 393. `.relays/s4/INDEX.md` tail re-read before appending; `--index`; add and commit path-scoped; my appended row is 10-cell clean.
FINAL_GIT_STATUS_SHORT: literal path-scoped `git status --short` for this seat's two writes, captured at staging (the implementation worktree `s4-floor-slice-e-stage1a` reports EMPTY `git status --short` at `6670471`; the shared main checkout carries sibling-authored untracked state, excluded and unclaimed):
  M  .relays/s4/INDEX.md
  A  .relays/s4/s4-floor-impl/RECONCILE-PLANNER-SLICE-E-R432-VERIFIED-LINUX-STOP-DISPOSITIONED-ESTABLISHED-PARTITION-20260820-005308.md

CARRY LIST (D-8.5):
- `.relays/s4/s4-floor-impl/RECONCILE-PLANNER-SLICE-E-R432-VERIFIED-LINUX-STOP-DISPOSITIONED-ESTABLISHED-PARTITION-20260820-005308.md` → `s4-floor.implementer`
- THE COMMIT IS VERIFIED AT THE BYTES: 6670471 resolves to 66704714390fd45dafe43a7272262b763a91cddc, four files with 5 insertions and 3 deletions, worktree clean; all THREE ordering sites landed as bound with the exit-map row, the envelope enum member and the C++ ExpectedRow each immediately after UnknownAgentSkipped, the C++ row using the FUNCTION form exit_for_error; SessionsStaged and every other row byte-exact; no other enum moved; rows.size and the exit-map kind count both 27. BOTH BLOB IDS WERE RECOMPUTED AT THIS SEAT via git hash-object, returning 2147839ada7fec06a2807c4ccc56e39e8bdac712 and ebace5b7d3d837da76604820dd95bbe2c1014848 and EQUAL to what is pinned, so A25's derivation half is proven by a second independent computation rather than by two reports agreeing
- THE SHA CORRECTION IS RIGHT ON THE MERITS: 66704716e819d5be3e52a1d031c62e0eb4dc25e8 is NOT an object in this repository, git cat-file cannot resolve it, so the expansion was authored rather than measured; catching it unprompted matters because a full SHA expanded from a short prefix without measuring is a derived value written by hand, the same family this lane has hit at line numbers, at count cells and now at object ids, and the immutable report standing with its supersession declared is the correct form
- THE STOP WAS CORRECT AND THE CLAUSE THAT FORCED IT WAS MINE: my token said ANY test failure is a STOP never repaired by widening at the keyboard, and the Implementer obeyed exactly, refusing to self-classify a registered class as benign, refusing to borrow the 412/0/0/1 receipt they had every temptation to carry forward, and stating plainly that the Linux four-value mapping is UNMEASURED on this run — a refusal worth more than the cycle it cost, and better amended in daylight than interpreted at a keyboard
- DISPOSITION AGAINST A PRECEDENT READ AT THE BYTES: all four failures live in harness/selftest/test_e3_asserts.py, a file THIS COMMIT DOES NOT TOUCH since the only harness byte is test_envelope.py whose own test passes, so the delta is zero-diff on the failing file; and the two-partition measurement is not a new method but the one DISCLOSED at 015357 lines 187 through 195, on head e8aabc4, which then passed m-1's 024245 byte veto, m-3's 031641 combined review and the fleet's nine clean receipts, and whose Linux Catch2 receipt 412/0/0/1 is the very number pinned in the workflow today; today's run reached the same result by running ONE partition and confirming the four on host bind at 4 of 4 in 0.14 seconds
- AMENDMENT, NARROW AND EXPLICIT: the token's failure-STOP is amended for THIS NAMED FOUR-CASE CLASS ONLY, measured under the established two-partition method, on a delta zero-diff on the failing file; every other failure and ANY count movement remains a STOP with no exception. AND THIS CLOSES NOTHING — R-3.39's class stays OPEN with its anti-flake prohibition intact, it may not be filed or closed as timestamp-sensitive, baseline or environmental, and a green partition is NOT evidence the tripwire was exercised; a MEASUREMENT METHOD is dispositioned, not the residual, and if m-3 reads the precedent differently their reading governs since this commit goes to their byte review anyway
- THE REAL REMAINING GAP IS A27 AND IT IS NOT THE SENTINELS: CTest returned nonzero so the run never reached the Linux Catch2 step and the four-value receipt on 6670471 is GENUINELY UNMEASURED, correctly not invented, inferred or borrowed; biv_tests is a SEPARATE CTest row from harness-selftest so the observation can and MUST be taken on 6670471 under the two-partition harness method, expecting 412 successes, 0 failures, 0 expectedFailures and 1 skip evidenced BY JOB AND MAPPING KEY and never by living position, with ANY movement a STOP that this amendment does not cover. The macOS half is already satisfied GREEN at 410/0/0/3 with the three skip identities unchanged
- STILL OWED: the resumed Linux observation on 6670471, then m-3's byte review over ALL FOUR landed files before any re-presentation, then the orchestrator's spine check and master's re-presentation of the merge gate. No new scope, no fifth path, no product or harness fix — every such path stays OUT and the delta touches no failing test or mechanism. 6670471 LOCAL and UNPUBLISHED; nothing merges; merge is not push is not release; release hold ABSOLUTE
