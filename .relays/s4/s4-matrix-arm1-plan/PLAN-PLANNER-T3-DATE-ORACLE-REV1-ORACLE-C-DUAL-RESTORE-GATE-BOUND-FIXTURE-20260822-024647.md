## PLAN rev1 — oracle C concurred, so the mechanism question is closed and the three review findings are fixed. MF-2 was the serious one and it was mine: a restore gate that hashed a file the mutation never touches. I also ran every obligation in this plan against a scratch export before asking anyone else to, including the two must-be-NO discriminators nobody had executed yet — and the B-is-blind claim now has a test-level demonstration, not just a git-level one

ROLE: Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-matrix-t3-date-oracle-fix-plan-r1
PARENT_DISPATCH_ID: s4-matrix-t3-date-oracle-fix-plan-review
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-T3-DATE-ORACLE-RAW-MUST-REVISE-AUTHORITY-AND-RESTORE-GATE-20260822-014956.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-ORACLE-C-CONCURRED-T1-INTERMITTENT-SEEK-A-POSITIVE-DO-NOT-CLOSE-20260822-022336.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new operator gate — the oracle-C mechanism is authorized at `022336`, which widened `235525` to `%ad`/`%cd --date=raw`, scoped to `harness/selftest/test_fixtures.py`. This relay carries NO token and authorizes NO keyboard; a successor Implementer PLAN-REVIEW approve is required and the bare `DISPATCH IMPL` parents to THAT approval. No merge, push, PR mutation, `.github` edit, schema act, or release. The release hold is ABSOLUTE
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: final T2 `7688bbd00b10e3f6f1e8f501a1094ba17f85ce67`; reconstructed T3 under repair `a3501cc1728ca13289a8a4a96e49c9ee95e54698`
SUPERSEDES: PLAN `s4-matrix-t3-date-oracle-fix-plan` at blob `2b96b2fe798d0854d5d96e79e22567469bb5b744`, SHA-256 `18cdd420c0f9a0592a7e10bcea90003f4c6b2c1e2fab41a73c030289df0a7266` (MUST REVISE); both values independently re-derived at this seat before superseding
FROM: s4-matrix.planner
TO: s4-matrix.implementer
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: PLAN rev1 — MF-1 closed by the 022336 concurrence widening the authorization to oracle C; MF-2 fixed with a dual restore gate on both files; MF-3 fixed with an executable uniqueness-gated basetemp binding, validated by running it; MINOR fixed to six obligations; and all six obligations pre-validated at my seat in a scratch export without discharging any of yours

## 1. What changed, and the one finding that was mine

**MF-1 is closed, not argued.** `022336` verified the discriminator at the orchestrator's own
seat and widened `235525` to the `%ad`/`%cd --date=raw` oracle. The edit is therefore unchanged
from rev0 — what changed is that it is now authorized, which is the whole difference and the
reason I routed rather than filed.

**The corrected framing is carried into this plan's text, not just conceded in a relay.**
`--date=raw` is git's raw **formatter** output — a stable rendering of the stored epoch and
offset, **not** commit-object-byte access. `git cat-file commit` corroborates the values; it
does not turn a `git show` invocation into byte access. C's portability is therefore
**empirical** (measured identical on both git versions), not structural. Proof requirement (ii)
is satisfied on that empirical basis, which `022336` accepted explicitly.

**MF-2 was the serious finding and it was mine.** O-4 mutates `fixtures.py`, and I gated the
digest of `test_fixtures.py` — a file O-4 never touches. The gate would have stayed green with
the date-pin mutation still sitting in `fixtures.py`, poisoning every subsequent run in the
sequence. That is a restore gate blind to the only residue it exists to catch, which is the
same absence-blind shape this lane has paid for repeatedly. Their pinned digest is independently
verified at my seat.

MF-3 and the MINOR are accepted as written; both are fixed below.

## 2. The edit — unchanged from rev0, still pinned to an anchor and a target digest

Anchor verified **unique** (`count == 1`). Remove exactly:

```python
    assert _git(first_repo, "show", "-s", "--format=%an|%ae|%aI|%cn|%ce|%cI", "HEAD") == (
        "Biv Harness|biv-harness@example.invalid|2000-01-01T00:00:00Z|"
        "Biv Harness|biv-harness@example.invalid|2000-01-01T00:00:00Z"
    )
```

Insert exactly:

```python
    assert _git(
        first_repo, "show", "-s", "--date=raw",
        "--format=%an|%ae|%ad|%cn|%ce|%cd", "HEAD"
    ) == (
        "Biv Harness|biv-harness@example.invalid|946684800 +0000|"
        "Biv Harness|biv-harness@example.invalid|946684800 +0000"
    )
```

```text
TARGET   harness/selftest/test_fixtures.py
  before sha256 b09f735297de49db08798bceed6cf4258d86bc16c39666496f9f6186192fd3df   7842 bytes
  AFTER  sha256 ca9f04e1ad06856d3c5d093ee2c6ba5d76e034d020c1cb482d65fc2868c68aaf   7868 bytes

MUTATION SURFACE (O-4 only, scratch copies, never the candidate)
  harness/bivharness/fixtures.py
         sha256 6776756f8f50ea9f9c4a46d2cb9804586da4e628fa5698041ec00356a4b81303   9980 bytes
```

Both digests independently re-derived at this seat; sizes taken with `git cat-file -s`, which
is immune to the trailing-newline stripping that made three of my byte counts one low in the
preceding relay. `_git(repo, *args)` forwards positionally, so `--date=raw` needs no helper
change; longest line 95 before and 95 after. No ruff/black/flake8 config, no python linter in
`.github/workflows/`.

## 3. Proof obligations — SIX (MINOR fixed; the SUBJECT now says six)

```text
O-1  MUST-BE-YES, macOS.  At the fixed head: python3 -m pytest harness/selftest -q GREEN,
     still 997 passed.  Record the node id of
     test_git_repo_builder_is_deterministic_and_host_config_isolated as PASSED explicitly --
     a suite total cannot show that one row ran.

O-2  MUST-BE-YES, Linux = proof requirement (iii).  Same suite in the disposable
     ubuntu:24.04 --platform linux/amd64 container, non-root, nofile SOFT raised back to the
     inherited HARD limit before the run (CLAUDE.md / R-4.31 arm (a)).  The previously-failing
     node id must be PASSED.

O-3  CROSS-VERSION IDENTITY = proof requirement (ii), BOUND TO THE REAL FIXTURE (MF-3).
     The queried repository must be the one the test itself materialized.  Executable recipe,
     identical on both hosts, validated by running it (section 4):

       EVID=$(mktemp -d)                       # fresh per attempt; never mkdir -p
       python3 -m pytest harness/selftest/test_fixtures.py \
         -k test_git_repo_builder_is_deterministic_and_host_config_isolated \
         --basetemp="$EVID/tmp" -q
       MATCHES=$(find "$EVID/tmp" -type d -path '*/first/source/project' -print)
       N=$(printf '%s\n' "$MATCHES" | grep -c .)
       [ "$N" -eq 1 ] || { echo "STOP: expected exactly one repo, got $N"; exit 1; }
       REPO="$MATCHES"
       git -C "$REPO" show -s --date=raw --format='%an|%ae|%ad|%cn|%ce|%cd' HEAD

     Both hosts must print BYTE-IDENTICAL output, equal to:
       Biv Harness|biv-harness@example.invalid|946684800 +0000|Biv Harness|biv-harness@example.invalid|946684800 +0000

     DELIBERATELY NOT PINNED: the basetemp subdirectory name.  I observed pytest 9.0.2 produce
     test_git_repo_builder_is_deter0 (a 30-character truncation plus index), but that
     truncation is a pytest implementation detail and pinning it would make the recipe
     version-fragile in exactly the way this whole corrective exists to remove.  The
     uniqueness-gated find is version-independent; the N==1 check is what makes it falsifiable.

O-4  MUST-BE-NO x2, THE DISCRIMINATORS, WITH A DUAL RESTORE GATE (MF-2 fixed).
     In a scratch COPY of the worktree -- never the candidate -- mutate the fixtures.py date
     pin and confirm the test FAILS:
       (a) 2000-01-01T00:00:01+0000   different instant                      MUST FAIL
       (b) 1999-12-31T19:00:00-0500   same instant, different stored offset  MUST FAIL
     (b) is the coverage C retains and %at/%ct drops; section 4 demonstrates that at the test
     level, not merely at the git level.
     AFTER EACH mutation, gate on BOTH digests before continuing -- they prove different things:
       harness/bivharness/fixtures.py   == 6776756f8f50ea9f9c4a46d2cb9804586da4e628fa5698041ec00356a4b81303
       harness/selftest/test_fixtures.py == ca9f04e1ad06856d3c5d093ee2c6ba5d76e034d020c1cb482d65fc2868c68aaf
     The first is the mutation surface and is the gate rev0 was missing; the second proves the
     edit under test is still the planned edit.  A residue left in either invalidates every
     run after it.

O-5  CENSUS AT THE FIXED HEAD.  Tree-wide over harness/src/tests/schemas: zero %aI and zero
     %cI must remain.  VALIDATE THE INSTRUMENT FIRST on a must-be-YES and a must-be-NO file
     and show both.  Do not inherit my word, do not use \b inside git grep -E (POSIX ERE
     ignores it and returns a silent zero), and quote refspecs as "${sha}:path" -- bare
     "$sha:path" fires zsh's :t history modifier and returns a confident wrong 0.

O-6  SCOPE.  Exactly ONE changed file in git status/diff.  Anything else moved: stop and
     disclose before proceeding.
```

Requirement (i) — *pins the exact instant `946684800`* — is discharged by the AFTER bytes in
section 2 plus O-4(a).

## 4. What I already ran, and what it does NOT discharge

rev0 disclosed that my expected string came from a standalone env-replicating probe rather than
the fixture end-to-end. Since I am the seat mandating these measurements, I validated them.
Method: `git archive a3501cc` exported to a scratch directory (read-only, **no ref created, no
worktree added**), the planned edit applied there, nothing in the candidate touched.

```text
target digest reproduces in the scratch export
    ca9f04e1ad06856d3c5d093ee2c6ba5d76e034d020c1cb482d65fc2868c68aaf           CONFIRMED
O-3 recipe runs, uniqueness gate returns N == 1                                CONFIRMED
O-3 expected string, measured on the REAL pytest-materialized fixture (macOS):
    Biv Harness|biv-harness@example.invalid|946684800 +0000|Biv Harness|biv-harness@example.invalid|946684800 +0000
    -> identical to the probe-derived string rev0 predicted.  rev0's disclosed gap is closed
       on the macOS arm; the LINUX arm remains genuinely open and is yours.
O-1 unmutated, oracle C                               1 passed                 CONFIRMED
O-4(a) instant mutation, oracle C                     1 failed                 FIRES
O-4(b) offset mutation, oracle C                      1 failed                 FIRES
dual restore gate returns both files to
    6776756f8f50ea9f9c4a46d2cb9804586da4e628fa5698041ec00356a4b81303 and
    ca9f04e1ad06856d3c5d093ee2c6ba5d76e034d020c1cb482d65fc2868c68aaf           CONFIRMED

AND THE CLAIM THAT DECIDED THE ORACLE, NOW SHOWN AT THE TEST LEVEL:
  same test, oracle B (%at/%ct) installed instead of C
    unmutated                                         1 passed
    O-4(b) same instant, offset -0500                 1 PASSED  <- BLIND
  Under C that mutation fails; under B it passes.  Until now that was a git-level measurement
  and an inference about the test; it is now the test's own behaviour.
```

**This discharges none of your obligations.** Mine ran on a scratch export on one platform with
no durable evidence root; yours run at the candidate head, on both platforms, with receipts.
What it buys is that no obligation here is one I have merely reasoned would work — and if any
of them behaves differently at the candidate head, the plan is wrong and I want that reported
rather than reconciled.

## 5. Fence

In scope: `harness/selftest/test_fixtures.py`, one assertion, per `235525` as widened by
`022336`.

**Not** in scope and not authorized by this plan: `harness/bivharness/fixtures.py` (its pin is
correct; O-4's mutations are scratch-copy only and gated back), any other harness file, any
C++/CMake byte, `.github/`, the schema, T4, and — named explicitly because `022336` runs it in
parallel — the T1 intermittent positive-seek, the `nonzero_exit` claim, and the R-3.40(13)
re-verification. None of those ride this fix.

This relay carries **no** token. Ceremony: rev1 → Implementer PLAN-REVIEW → my bare
`DISPATCH IMPL` parented to the approving review. Then T3's head is FINAL and panelable.

Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no candidate edit, no ref created or moved, no worktree added. Read-only `git show`/`git cat-file -s` at `a3501cc` for both digests and sizes; `git hash-object`/`git show f8fe8d5:` to re-derive rev0's blob and SHA-256 before superseding; one `git archive a3501cc` export to a scratch directory outside every tracked worktree, where the planned edit, the O-3 recipe, both O-4 discriminators, the dual restore gate, and the oracle-B blindness demonstration were executed. NO merge, push, PR mutation, or remote CI; no container run at this seat for this relay. Docs lane: this relay + its INDEX row ride ONE explicit-path commit.
FINAL_GIT_STATUS_SHORT: this relay and its INDEX row are this seat's only working-tree delta at commit time; `git status --porcelain` over `harness/`, `src/`, `tests/`, `CMakeLists.txt` is empty and the T3 branch is unmoved at `a3501cc`; the shared checkout carries sibling-authored untracked paths, preserved and unclaimed
RELAY_LINT: exact-file WITH freshness immediately before commit; INDEX tail re-read before appending; `--index` run and diffed against the same lint on the pre-append blob to prove no new error is mine; commit gated on lint by logical AND; post-commit exact-file re-verify without freshness.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-T3-DATE-ORACLE-REV1-ORACLE-C-DUAL-RESTORE-GATE-BOUND-FIXTURE-20260822-024647.md` → TO `s4-matrix.implementer`
- MF-1 CLOSED BY AUTHORIZATION, NOT BY ARGUMENT: `022336` verified the discriminator at the orchestrator's own seat and WIDENED `235525` to the `%ad`/`%cd --date=raw` oracle. The edit is UNCHANGED from rev0; what changed is that it is now authorized, which is the entire difference and the reason routing beat filing. SUPERSEDES rev0 at blob `2b96b2fe798d0854d5d96e79e22567469bb5b744`, SHA-256 `18cdd420c0f9a0592a7e10bcea90003f4c6b2c1e2fab41a73c030289df0a7266`, both re-derived here before superseding
- CORRECTED FRAMING CARRIED INTO THE PLAN TEXT, not merely conceded in a relay: `--date=raw` is git's raw FORMATTER output, a stable RENDERING of the stored epoch and offset, NOT commit-object-byte access; `git cat-file commit` corroborates but does not convert a `git show` invocation into byte access. C's portability is EMPIRICAL (measured identical on both git versions), not structural, and requirement (ii) is satisfied on that basis per `022336`
- MF-2 WAS THE SERIOUS FINDING AND IT WAS MINE: O-4 mutates `fixtures.py` while rev0 gated the `test_fixtures.py` digest, a file O-4 never touches — the gate stays green with the mutation still resident, poisoning every later run. rev1 gates BOTH after each mutation: `fixtures.py` == `6776756f8f50ea9f9c4a46d2cb9804586da4e628fa5698041ec00356a4b81303` (9980 bytes, the mutation surface, the gate rev0 lacked) and `test_fixtures.py` == `ca9f04e1ad06856d3c5d093ee2c6ba5d76e034d020c1cb482d65fc2868c68aaf` (7868 bytes, proving the edit under test is still the planned edit)
- MF-3 FIXED WITH AN EXECUTABLE BINDING, VALIDATED BY RUNNING IT: fresh `mktemp -d` per attempt, `--basetemp="$EVID/tmp"`, then a uniqueness-gated `find "$EVID/tmp" -type d -path '*/first/source/project' -print` with an `N == 1` STOP, then the exact git command against `$REPO`. DELIBERATELY NOT PINNED: the basetemp subdirectory name — I OBSERVED pytest 9.0.2 produce `test_git_repo_builder_is_deter0` (30-char truncation plus index) but pinning it would make the recipe version-fragile in precisely the way this corrective exists to remove; the uniqueness gate is version-independent and is what makes it falsifiable
- MINOR FIXED: SUBJECT and section now both say SIX obligations
- PRE-VALIDATED AT MY SEAT via `git archive a3501cc` to a scratch export (NO ref created, NO worktree added, candidate untouched): target digest reproduces; O-3 recipe runs with N==1; **the O-3 expected string is now MEASURED ON THE REAL pytest-materialized FIXTURE on macOS and is identical to rev0's probe-derived prediction, closing rev0's disclosed gap on the macOS arm while the LINUX arm stays genuinely open and yours**; O-1 passes; O-4(a) FIRES; O-4(b) FIRES; the dual restore gate returns both files to their pinned digests
- THE ORACLE-DECIDING CLAIM NOW SHOWN AT THE TEST LEVEL, not inferred: with oracle B (`%at`/`%ct`) installed in the same test, the O-4(b) same-instant/offset-`-0500` mutation **PASSES** (1 passed) where under C it FAILS. Until now B-is-blind was a git-level measurement plus an inference about the test; it is now the test's own behaviour
- THIS DISCHARGES NONE OF THE IMPLEMENTER'S OBLIGATIONS: mine ran on a scratch export, one platform, no durable evidence root; theirs run at the candidate head, both platforms, with receipts. If any obligation behaves differently at the candidate head, the PLAN is wrong and I want it reported rather than reconciled
- O-5 CARRIES BOTH OF MY INSTRUMENT DEFECTS FORWARD AS REQUIREMENTS: validate the census on a must-be-YES AND a must-be-NO file and show both; no `\b` inside `git grep -E` (POSIX ERE ignores it, silent zero); quote refspecs as `"${sha}:path"` because bare `"$sha:path"` fires zsh's `:t` history modifier and returns a confident wrong `0`. Sizes taken with `git cat-file -s`, immune to the trailing-newline stripping that made three byte counts one low in the preceding relay
- FENCE: `fixtures.py` NOT in scope (pin correct; O-4 mutations are scratch-copy only and gated back), no other harness file, no C++/CMake byte, no `.github/`, no schema, no T4, and — named explicitly because `022336` runs them in parallel — the T1 intermittent positive-seek, the `nonzero_exit` claim, and the R-3.40(13) re-verification do NOT ride this fix
- NO TOKEN IN THIS RELAY: rev1 → Implementer PLAN-REVIEW → my bare `DISPATCH IMPL` parented to THAT approval; then T3 head FINAL and panelable. T2 head FINAL at `7688bbd`; T3 branch unmoved at `a3501cc`; both T3 heads LOCAL and UNPUBLISHED; R-4.38 binary inventory my stage-5 obligation; schema F+G-fenced; no remote CI, push, PR mutation, merge, publication, deployment or release; release hold ABSOLUTE
