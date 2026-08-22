## IMPL — token issued, parented to R3's parsing approve. The explicit disposition R3 asked for: I ADOPT `d406868` on measured byte-identity rather than ordering a redo that would change no byte, and I disclose plainly that it was made under a lineage-invalid token and is not retroactively authorized by anything. The six obligations are entirely unrun and all six are owed

ROLE: Planner
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: s4-matrix-t3-date-oracle-fix-impl-r3
PARENT_DISPATCH_ID: s4-matrix-t3-date-oracle-fix-plan-review-r3
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-T3-DATE-ORACLE-REV1-APPROVE-R3-FRESH-PARSING-SUCCESSOR-20260822-041652.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-T3-DATE-ORACLE-REV1-ORACLE-C-DUAL-RESTORE-GATE-BOUND-FIXTURE-20260822-024647.md; .relays/s4/s4-matrix-arm1-plan/SITREP-PLANNER-TOKEN-WITHHELD-APPROVE-DOES-NOT-PARSE-T1-TOKEN-CARRIES-SAME-DEFECT-20260822-041055.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new operator gate — the oracle-C corrective is authorized at `235525` as widened by `022336`, the plan approved at R3, and this token is the pair Planner ceremony that approval releases. It authorizes ONE thing: the single-assertion date-oracle correction in `harness/selftest/test_fixtures.py` and its six proof obligations. No merge, push, PR mutation, `.github` edit, schema act, deployment, or release. The release hold is ABSOLUTE
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: authorized pre-edit T3 `a3501cc1728ca13289a8a4a96e49c9ee95e54698`; current `s4-matrix/arm1-t3` head `d4068684e51f67d0a11fb6d2251178fb2a1a70ea`
SUPERSEDES: token `s4-matrix-t3-date-oracle-fix-impl` at `IMPL-PLANNER-T3-DATE-ORACLE-DISPATCH-20260822-040750.md` — VOID, it parents `s4-matrix-t3-date-oracle-fix-plan-review-r1` whose approve does not parse; preserved as filed, corrected forward, never rewritten
FROM: s4-matrix.planner
TO: s4-matrix.implementer
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: IMPL token parented to R3 — d406868 ADOPTED on measured byte-identity (ca9f04e1 target, parent a3501cc, one file, 6+/3-), explicitly NOT retroactively authorized; the void 040750 token and T1's dispatch both remain permanent root-mode lineage errors; O-1 through O-6 all owed with Docker --init binding on O-2

DISPATCH IMPL

## 1. Scope

SCOPE_DIFF:
- harness/selftest/test_fixtures.py -> in

SCOPE_DIFF_RESULT: all-in

SCOPE_ROW_EVIDENCE:
- `harness/selftest/test_fixtures.py` — the single authorized path. At the authorized pre-edit head `a3501cc` it is 7842 bytes, SHA-256 `b09f735297de49db08798bceed6cf4258d86bc16c39666496f9f6186192fd3df`. At `d406868` it is 7868 bytes, SHA-256 `ca9f04e1ad06856d3c5d093ee2c6ba5d76e034d020c1cb482d65fc2868c68aaf`, exactly the target digest pinned in rev1 §2. `git diff --name-only a3501cc d406868` returns this path and nothing else; `git diff --numstat` returns `6 3` — the one assertion, rewrapped. Measured at this seat, not transcribed.

Nothing else is in scope. Explicitly out: `harness/bivharness/fixtures.py` (its pin is correct; O-4's mutations are scratch-copy only and gated back), every other harness file, every C++ and CMake byte, `.github/`, the schema, T4, and the separately-running T1 items — the intermittent's registration, the `nonzero_exit` claim, and the R-3.40(13) re-verification.

## 2. The disposition R3 required — `d406868` is ADOPTED, and why that is not laundering

R3 requires this token to "explicitly choose how that inert artifact is handled." I choose to
**adopt it**, and I want the reasoning checkable rather than asserted.

**What I measured myself, three independent properties:**

```text
digest   d406868:harness/selftest/test_fixtures.py
         = ca9f04e1ad06856d3c5d093ee2c6ba5d76e034d020c1cb482d65fc2868c68aaf
         = the target digest rev1 pinned BEFORE any edit existed          EXACT MATCH
parent   d406868^ = a3501cc = the authorized pre-edit head                EXACT MATCH
scope    git diff --name-only a3501cc d406868 -> one path, 6+/3-          ONE FILE
```

**Why adopt rather than order a redo.** rev1 pinned the AFTER digest precisely so the outcome
would be determinate independently of who typed it — that was the point of the gate, and the
gate now discharges its function. A redo produces a byte-identical tree under a different
commit SHA: it changes no product byte, adds no evidence, and would rewrite local history to
improve the appearance of the record rather than its content. This lane has consistently
corrected forward instead — R2 to R3 an hour ago on exactly that principle.

**What adoption does NOT mean, stated so it cannot be read broadly later:**

```text
NOT retroactive authorization.  d406868 was created under the VOID 040750 token, which
  parents an approve that does not parse.  Nothing here makes that act authorized when it
  happened, and R3 says the same.  What this token authorizes is the edit going forward;
  what it adopts is a set of bytes proven identical to the edit it authorizes.
NOT a precedent.  Adoption rests on a digest pinned BEFORE the artifact existed.  An edit
  with no pre-pinned target has nothing to be measured against and would not qualify.
NOT evidence.  O-1 through O-6 are entirely unrun.  Correct bytes are not a passing test.
```

## 3. The six obligations — all owed, none discharged

Binding exactly as approved in rev1 §3. The digests below are unchanged by adoption because
`d406868` **is** the target state.

```text
O-1  macOS: python3 -m pytest harness/selftest -q GREEN, still 997 passed, and the node id
     test_git_repo_builder_is_deterministic_and_host_config_isolated recorded PASSED
     explicitly -- a suite total cannot show that one row ran.

O-2  Linux = requirement (iii): the same suite in a disposable ubuntu:24.04
     --platform linux/amd64 container, non-root, nofile SOFT raised back to the inherited
     HARD limit (R-4.31 arm (a)), and -- NEW, binding, per 035347 -- WITH Docker --init, or
     otherwise a reaping PID 1.  The previously-failing node id must be PASSED.  Separately
     owned R-4.35 harness-selftest members are reported SEPARATELY and must not be laundered
     into a claim that the whole Linux suite was green (R3's binding clarification, adopted).

O-3  Cross-version identity = requirement (ii), bound to the real fixture: fresh mktemp -d,
     --basetemp, uniqueness-gated locate with an N == 1 STOP, then the exact command.  Both
     hosts must print BYTE-IDENTICAL output equal to:
       Biv Harness|biv-harness@example.invalid|946684800 +0000|Biv Harness|biv-harness@example.invalid|946684800 +0000
     The basetemp subdirectory name stays UNPINNED -- pytest's truncation is version-fragile
     in exactly the way this corrective exists to remove.

O-4  Two must-be-NO discriminators in a scratch COPY, never the candidate:
       (a) 2000-01-01T00:00:01+0000  different instant                      MUST FAIL
       (b) 1999-12-31T19:00:00-0500  same instant, different stored offset  MUST FAIL
     DUAL restore gate after EACH, both digests, because they prove different things:
       harness/bivharness/fixtures.py    == 6776756f8f50ea9f9c4a46d2cb9804586da4e628fa5698041ec00356a4b81303
       harness/selftest/test_fixtures.py == ca9f04e1ad06856d3c5d093ee2c6ba5d76e034d020c1cb482d65fc2868c68aaf

O-5  Census at the fixed head: zero %aI and zero %cI tree-wide over harness/src/tests/schemas.
     VALIDATE THE INSTRUMENT on a must-be-YES and a must-be-NO file and show both.  No \b
     inside git grep -E (POSIX ERE ignores it, silent zero).  Quote refspecs "${sha}:path" --
     bare "$sha:path" fires zsh's :t history modifier and returns a confident wrong 0.

O-6  Scope: exactly ONE changed file relative to a3501cc.  Anything else: stop and disclose.
```

Any obligation that fails STOPS the cycle and routes; none may be reconciled into a pass.

## 4. Two permanent lineage errors, disclosed rather than quietly carried

```text
IMPL-PLANNER-T3-DATE-ORACLE-DISPATCH-20260822-040750.md   VOID (parents the non-parsing r1)
IMPL-PLANNER-T1-TIDY-FIX-DISPATCH-20260821-035403.md      parents T1's non-parsing R8 approve
```

Both will keep erroring in `--relay-root` forever. The record is append-only, the walk resolves
parents by id and reads committed text, and root mode has no void concept — R-3.40 item (8).
Marking 040750 VOID in this relay's `SUPERSEDES` is an honest label for humans; it does not and
cannot silence the walk, and I am not pretending otherwise. Both ride T1's and T3's stage-5
merge-readiness as disclosed record defects. Neither implicates a product byte.

This lane has now produced **three** live instances of R-3.40 item (7) — T1's R8, T3's R1, and
the R2 near-miss — plus one of the same family from the freshness gate. The registry says
routing to the harness team is evidence-triggered.

## 5. State

T3 is NOT final and NOT panelable until O-1 through O-6 complete; T4 HELD. T2 head FINAL at
`7688bbd`. Both T3 heads remain LOCAL and UNPUBLISHED. R-4.38's binary inventory stays my
stage-5 obligation. Schema F+G-fenced. Merge is not push is not release; the release hold is
ABSOLUTE.

ACTIONS_GIT_REF: no product, test, harness, ref, or worktree byte edited at my seat. Read-only verification: `git cat-file -s` and `git show | shasum` on `harness/selftest/test_fixtures.py` at `a3501cc` and `d406868`; `git rev-parse d406868^`; `git diff --name-only` and `--numstat` between them; `git rev-parse s4-matrix/arm1-t3`; a `DISPATCH_ID` holder count confirming `s4-matrix-t3-date-oracle-fix-impl-r3` is fresh and collision-free while `s4-matrix-t3-date-oracle-fix-impl` is already held; and a re-validated `plan_review_approved` call confirming R3 parses True. NO merge, push, PR mutation, or remote CI. Docs lane: this relay + its INDEX row ride ONE explicit-path commit.
FINAL_GIT_STATUS_SHORT: this relay and its INDEX row are this seat's only working-tree delta at commit time; `git status --porcelain` over `harness/`, `src/`, `tests/`, `CMakeLists.txt` is empty; the shared checkout carries sibling-authored untracked paths, preserved and unclaimed
RELAY_LINT: exact-file WITH freshness immediately before commit; INDEX tail re-read before appending; `--index` diffed against the same lint on the pre-append blob to prove no new error is mine; commit gated on lint by logical AND; post-commit exact-file re-verify without freshness; the bare token verified present exactly once outside any fence via the linter's own `operational_token_text`, with the detector validated on a must-be-YES and a must-be-NO first.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/IMPL-PLANNER-T3-DATE-ORACLE-DISPATCH-R3-ADOPTS-D406868-20260822-050546.md` → TO `s4-matrix.implementer`
- TOKEN ISSUED, parented to `s4-matrix-t3-date-oracle-fix-plan-review-r3`, whose approve I re-verified parses True with the matcher re-validated on a must-be-YES and must-be-NO first. Fresh `DISPATCH_ID` `s4-matrix-t3-date-oracle-fix-impl-r3` confirmed ZERO holders; the old `s4-matrix-t3-date-oracle-fix-impl` is already held by the void 040750 relay, so reusing it would have created exactly the guess-resolved collision I warned against
- `d406868` ADOPTED on THREE independently measured properties: digest `ca9f04e1ad06856d3c5d093ee2c6ba5d76e034d020c1cb482d65fc2868c68aaf` equals the target rev1 pinned BEFORE any edit existed; parent `d406868^` equals the authorized pre-edit head `a3501cc`; scope is ONE path at `6+/3-`. Adopted rather than redone because rev1 pinned the AFTER digest precisely so the outcome would be determinate independent of who typed it — a redo yields a byte-identical tree under a new SHA, changing no product byte, adding no evidence, and rewriting local history to improve the record's appearance rather than its content; this lane corrected forward from R2 to R3 on the same principle an hour earlier
- WHAT ADOPTION IS NOT, stated so it cannot be read broadly later: NOT retroactive authorization (d406868 was made under the VOID 040750 token parenting a non-parsing approve; this token authorizes the edit GOING FORWARD and adopts bytes proven identical to it); NOT a precedent (adoption rests on a digest pinned BEFORE the artifact existed — an edit with no pre-pinned target has nothing to measure against and would not qualify); NOT evidence (O-1 through O-6 are entirely unrun, and correct bytes are not a passing test)
- ALL SIX OBLIGATIONS OWED, none discharged, digests unchanged by adoption because `d406868` IS the target state. O-2 now BINDS Docker `--init` (or a reaping PID 1) per `035347` in ADDITION to the chartered `nofile` soft-to-hard recipe, and adopts R3's clarification that separately-owned R-4.35 members are reported SEPARATELY and never laundered into a whole-suite-green claim. O-4 keeps the DUAL restore gate on both `fixtures.py` `6776756f8f50ea9f9c4a46d2cb9804586da4e628fa5698041ec00356a4b81303` and `test_fixtures.py` `ca9f04e1ad06856d3c5d093ee2c6ba5d76e034d020c1cb482d65fc2868c68aaf`. O-5 carries both of my instrument defects forward as requirements. Any failure STOPS and routes; none may be reconciled into a pass
- TWO PERMANENT ROOT-MODE LINEAGE ERRORS DISCLOSED, not quietly carried: the void `040750` dispatch and T1's `035403` dispatch will error in `--relay-root` forever, because the record is append-only, the walk resolves parents by id and reads committed text, and root mode has no void concept (R-3.40 item 8). The `SUPERSEDES` VOID label is honest for humans and CANNOT silence the walk; I am not pretending otherwise. Both ride stage-5 merge-readiness as disclosed RECORD defects implicating no product byte
- THREE live instances of R-3.40 item (7) in this lane now (T1 R8, T3 R1, the R2 near-miss) plus one freshness-gate sibling; the registry says harness-team routing is EVIDENCE-TRIGGERED
- CORRECTION TO MY OWN EARLIER READING: git authorship cannot distinguish seats in this checkout — every commit including all of mine carries the same identity — so the `040750` token's provenance is NOT determinable from authorship, and I do not claim it. What is measured is only that it parents the non-parsing r1 and is therefore lineage-invalid
- STATE: T3 NOT final and NOT panelable until O-1 through O-6 complete; T4 HELD; T2 head FINAL at `7688bbd`; both T3 heads LOCAL and UNPUBLISHED; `s4-matrix/arm1-t3` now at `d406868`; R-4.38 binary inventory my stage-5 obligation; schema F+G-fenced; no remote CI, push, PR mutation, merge, publication, deployment or release; release hold ABSOLUTE
