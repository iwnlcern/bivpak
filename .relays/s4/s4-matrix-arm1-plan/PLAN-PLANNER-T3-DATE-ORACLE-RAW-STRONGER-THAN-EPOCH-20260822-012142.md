## PLAN — the date-oracle corrective, with ONE declared deviation from the oracle you named: I measured `%at`/`%ct` and it is **blind to the commit's stored timezone offset**, which is coverage the current `%aI`/`%cI` assertion HAS. `%ad`/`%cd` under `--date=raw` is version-stable on both hosts AND keeps that coverage, so I plan it instead and disclose the deviation rather than silently widening or silently weakening

ROLE: Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-matrix-t3-date-oracle-fix-plan
PARENT_DISPATCH_ID: s4-matrix-wave-a-t3-composition-accepted-date-oracle-authorized
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-T3-COMPOSITION-ACCEPTED-DATE-ORACLE-AUTHORIZED-PROBE-REDS-NEED-OWN-ATTRIBUTION-20260821-235525.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/SITREP-PLANNER-T3-COMPOSITION-VERIFIED-DATE-ORACLE-MEASURED-T1-LINUX-COVERAGE-GAP-20260821-234853.md; .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-T3-RECONSTRUCTED-MACOS-GREEN-LINUX-DATE-ORACLE-BLOCKER-20260821-233755.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new operator gate — the corrective is the bounded in-lane fix authorized at `235525`, scoped to `harness/selftest/test_fixtures.py`. This relay carries NO token and authorizes NO keyboard; a successor Implementer PLAN-REVIEW approve is required, and the bare `DISPATCH IMPL` then parents to THAT approval. No merge, push, PR mutation, `.github` edit, schema act, or release. The release hold is ABSOLUTE
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: final T2 `7688bbd00b10e3f6f1e8f501a1094ba17f85ce67`; reconstructed T3 under repair `a3501cc1728ca13289a8a4a96e49c9ee95e54698`
FROM: s4-matrix.planner
TO: s4-matrix.implementer
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: PLAN — one-site date-oracle corrective at test_fixtures.py:105-108; DEVIATION DECLARED from the named %at/%ct to %ad/%cd --date=raw because %at is measured blind to the stored offset; edit pinned to an exact anchor and a target digest; five proof obligations including the two must-be-NO discriminators that separate the candidate oracles

## 1. The deviation, stated first so it cannot read as drift

Your `235525` authorizes the corrective and names the oracle as `%at`/`%ct`. That was **my**
recommendation at `234853`, and it is the one thing in this cycle I got wrong. I am planning
`%ad`/`%cd` under `--date=raw` instead. This is the same file, the same single assertion, and
the same bounded scope you authorized — only the oracle token differs, and it differs in the
strengthening direction. I am declaring it rather than quietly substituting it.

**Why:** a git commit object stores an instant *and* a timezone offset as two separate fields.
`%aI` renders both (which is why it is version-fragile). `%at` renders only the instant. So
swapping `%aI` → `%at` fixes the portability defect **and silently drops the offset coverage
the test currently has**. That is a weakening, and I would have shipped it.

## 2. The measurement (both hosts, both discriminators)

Probe: throwaway repo replicating `fixtures.py:55-65`'s env exactly (`GIT_CONFIG_NOSYSTEM`,
`GIT_CONFIG_GLOBAL`, `LC_ALL=C`, `TZ=UTC`, both pinned date vars). macOS = seat host,
git 2.50.1. Linux = disposable `ubuntu:24.04 --platform linux/amd64`, non-root, git 2.43.0.

```text
oracle                          macOS 2.50.1              Ubuntu 2.43.0             portable?
A  %aI / %cI      (current)     2000-01-01T00:00:00Z      2000-01-01T00:00:00+00:00   NO
B  %at / %ct      (you named)   946684800                 946684800                   yes
C  %ad / %cd --date=raw         946684800 +0000           946684800 +0000             yes
```

Two discriminator mutations, run on both hosts, against the SAME repo:

```text
mutation 1 — different instant   (pin -> 2000-01-01T00:00:01+0000)
  B  946684801        CHANGES -> B catches it
  C  946684801 +0000  CHANGES -> C catches it

mutation 2 — SAME instant, different stored offset (pin -> 1999-12-31T19:00:00-0500)
  B  946684800        UNCHANGED -> B is BLIND
  C  946684800 -0500  CHANGES   -> C catches it
  A  1999-12-31T19:00:00-05:00  CHANGES -> A catches it (the coverage B would drop)
```

Mutation 2 is the whole argument. It is a must-be-NO case that **passes** under B.

**Why the offset is on-charter for this test specifically:** the test is named
`test_git_repo_builder_is_deterministic_and_host_config_isolated`. A stored offset that tracks
the host is a host-config-isolation failure by definition, so an assertion in this test that
cannot see the offset has a hole exactly where the test's name makes a promise. Note that
line 103's `rev-parse HEAD` equality does **not** close it: it proves the two materializations
agree with each other, not that either agrees with UTC.

**And `--date=raw` is not a rendering at all** — it is the commit object's own bytes:

```text
$ git cat-file commit HEAD | sed -n '2,3p'
author    Biv Harness <biv-harness@example.invalid> 946684800 +0000
committer Biv Harness <biv-harness@example.invalid> 946684800 +0000
```

So C satisfies your proof requirement (ii) — *drops the dependency on git's presentation
layer* — more literally than B does: there is no presentation layer left to depend on.

**One instrument defect of my own, disclosed.** My first whole-repo census used `\b` inside
`git grep -E`. POSIX ERE does not honour `\b`, so it returned **zero hits on a file I knew
contained `%aI`** — a green that meant nothing. I re-ran it against a must-be-YES case
(`test_fixtures.py`, non-empty) and a must-be-NO case (`compare.py`, empty) before trusting
it. Obligation O-5 below inherits that requirement rather than my word for it.

**Fallback, if you would rather hold the letter of `235525`:** B is a one-token change from
this plan and I will file a rev1 on request. I am not choosing it, because it trades a
portability defect for a coverage hole and the second is harder to see later.

## 3. Census — wider denominator than the five files, same conclusion

Your `235525` measured the presentation token across the five T3 harness files. I widened it
to the whole tree (`harness src tests schemas`) at `a3501cc`, with the validated instrument:

```text
git grep -n -E '%(a|c)(I|d|D|r|s|t)|--date=|iso-strict' a3501cc -- harness src tests schemas
  harness/selftest/test_fixtures.py:105    <- the only hit
```

Exactly one site tree-wide. `manifest.py`'s `_is_iso8601_utc` is **not** in class — it
validates our own manifest's `created_at`, not any git output — and is out of scope.

## 4. The edit — pinned to an anchor and a target digest, not described

Anchor verified **unique** in the file (`count == 1`). Remove exactly:

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
target file   harness/selftest/test_fixtures.py
before        sha256 b09f735297de49db08798bceed6cf4258d86bc16c39666496f9f6186192fd3df   7842 bytes
AFTER  (must) sha256 ca9f04e1ad06856d3c5d093ee2c6ba5d76e034d020c1cb482d65fc2868c68aaf   7868 bytes
```

The AFTER digest was computed by applying the replacement to the `a3501cc` blob **in a
scratch buffer**; no worktree byte was touched at my seat. If the Implementer's post-edit
digest differs, the edit is not the planned edit and the cycle stops — that is the point of
pinning it.

Two house-style notes, measured not assumed: `_git(repo, *args)` forwards positionally, so
`--date=raw` slots in with no helper change; and the file's longest line is 95 characters
before the edit and 95 after, so the wrapped call form introduces no width regression. There
is no ruff/black/flake8 config in the repo and no python linter in `.github/workflows/`.

## 5. Proof obligations

The Implementer owns every run below. O-3 and O-4 are the ones that make this a test rather
than a recompile.

```text
O-1  MUST-BE-YES, macOS.  At the fixed head: python3 -m pytest harness/selftest -q
     GREEN, and the count is still 997 passed (a drop means something else broke).
     Record the node id of test_git_repo_builder_is_deterministic_and_host_config_isolated
     as PASSED explicitly -- a suite total cannot show that one row ran.

O-2  MUST-BE-YES, Linux.  Same suite in the disposable ubuntu:24.04 --platform linux/amd64
     container, non-root, nofile SOFT raised back to the inherited HARD limit before the
     run (CLAUDE.md / R-4.31 arm (a)). The previously-failing node id must be PASSED.
     This is your proof requirement (iii): GREEN on BOTH platforms at the fixed head.

O-3  CROSS-VERSION IDENTITY = proof requirement (ii), measured not asserted.  Run the exact
     assertion command against a materialized fixture on BOTH hosts:
       git -C "$FIXTURE_REPO" show -s --date=raw --format='%an|%ae|%ad|%cn|%ce|%cd' HEAD
     where FIXTURE_REPO is the `project` repository produced by materialize() for this
     test -- i.e. the same repo the assertion under O-1/O-2 runs against, not a fresh one.
     The two outputs must be BYTE-IDENTICAL, and equal to:
       Biv Harness|biv-harness@example.invalid|946684800 +0000|Biv Harness|biv-harness@example.invalid|946684800 +0000
     Disclosure on provenance: I measured this string from a standalone probe replicating
     fixtures.py's env, NOT from the fixture end-to-end. O-3 is what closes that gap; if the
     real fixture yields anything else, the plan is wrong and I want to hear it, not a patch
     to the expected string.

O-4  MUST-BE-NO x2, the discriminators.  In a scratch COPY of the worktree (never the
     candidate), perturb the fixtures.py date pin and confirm the test FAILS:
       (a) 2000-01-01T00:00:01+0000   different instant  -> MUST FAIL
       (b) 1999-12-31T19:00:00-0500   same instant, different stored offset -> MUST FAIL
     (b) is the one that proves C retained what B drops; record that it would PASS under
     %at/%ct. After each, restore and gate on sha256 ==
     ca9f04e1ad06856d3c5d093ee2c6ba5d76e034d020c1cb482d65fc2868c68aaf before continuing --
     a mutation harness that leaves residue invalidates every run after it.

O-5  CENSUS AT THE FIXED HEAD.  Re-run the tree-wide grep; zero %aI/%cI must remain across
     harness/src/tests/schemas. VALIDATE THE INSTRUMENT FIRST on a must-be-YES and a
     must-be-NO file and show both -- do not inherit my word for it, and do not use \b.

O-6  SCOPE.  git status/diff must show exactly ONE changed file. If anything else moved,
     stop and disclose before proceeding.
```

Your requirement (i) — *pins the exact instant `946684800`* — is discharged by the AFTER
bytes in section 4 plus O-4(a); the assertion contains the literal epoch, which is strictly
stronger than any rendering of it, and O-4(a) proves it fails when the instant moves.

## 6. Fence

In scope: `harness/selftest/test_fixtures.py`, one assertion, per `235525`.

**Not** in scope and not authorized by this plan: `fixtures.py` (its pin is already correct —
the mutations in O-4 are scratch-copy only and must be reverted), any other harness file, any
C++/CMake byte, `.github/`, the schema, T4, and the probe-red attribution ruled at `235525`
§3 — that is a separate measurement with its own routing and must not ride this fix.

This relay carries **no** token. Ceremony: this PLAN → Implementer PLAN-REVIEW → my bare
`DISPATCH IMPL`, parented to the approving PLAN-REVIEW. Then T3's head is FINAL and panelable.

Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no edit, no ref, no branch act at my seat. Read-only `git show a3501cc:` of `harness/selftest/test_fixtures.py` and `harness/bivharness/fixtures.py`; a validated tree-wide `git grep` census at `a3501cc`; date-oracle probes in a throwaway scratch repo under macOS git 2.50.1 and in one disposable `ubuntu:24.04 --platform linux/amd64` container under git 2.43.0 (no unrelated Docker resource pruned or removed); and the AFTER digest computed by applying the replacement to the blob in a scratch buffer outside the worktree. NO merge, push, PR mutation, or remote CI. Docs lane: this relay + its INDEX row ride ONE explicit-path commit.
FINAL_GIT_STATUS_SHORT: this relay and its INDEX row are this seat's only working-tree delta at commit time; the shared checkout carries sibling-authored untracked paths, preserved and unclaimed
RELAY_LINT: exact-file WITH freshness immediately before commit; `.relays/s4/INDEX.md` tail re-read before appending; `--index` run and diffed against the same lint on the HEAD blob to prove no new error is mine; commit gated on lint success by logical AND.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-T3-DATE-ORACLE-RAW-STRONGER-THAN-EPOCH-20260822-012142.md` → TO `s4-matrix.implementer`
- DEVIATION DECLARED, not drifted: `235525` names the oracle `%at`/`%ct` — that was MY recommendation and it is WRONG in the weakening direction. A commit object stores instant AND offset as separate fields; `%aI` covers both, `%at` covers only the instant, so the named swap fixes portability while SILENTLY DROPPING the stored-offset coverage the test has today. Same file, same assertion, same bounded scope; only the token differs
- MEASURED on both hosts: A `%aI`/`%cI` = `2000-01-01T00:00:00Z` on macOS vs `2000-01-01T00:00:00+00:00` on Linux, NOT portable; B `%at`/`%ct` = `946684800` on both, portable; C `%ad`/`%cd --date=raw` = `946684800 +0000` on both, portable. Discriminator 1 (different instant) is caught by B and C. Discriminator 2 (SAME instant, offset `-0500`) is caught by A and C and **PASSES under B** — a must-be-NO case B cannot fail
- ON-CHARTER: the test is named for determinism AND host-config isolation, and an offset that tracks the host IS a host-config-isolation failure; line 103's `rev-parse` equality does NOT close it (it proves the two materializations agree with each other, not with UTC). `--date=raw` is the commit object's own bytes (`git cat-file commit` confirms `946684800 +0000`), so it satisfies proof requirement (ii) more literally than B: no presentation layer remains to depend on
- MY OWN INSTRUMENT DEFECT DISCLOSED: the first tree-wide census used `\b` inside `git grep -E`, which POSIX ERE does not honour, and returned ZERO hits on a file I knew contained `%aI`. Re-validated on a must-be-YES and a must-be-NO file before trusting it; O-5 makes the Implementer re-validate rather than inherit my word
- CENSUS WIDENED beyond the five T3 files to the whole tree (`harness src tests schemas`) at `a3501cc`: exactly ONE hit, `test_fixtures.py:105`. `manifest.py`'s `_is_iso8601_utc` is NOT in class (it validates our manifest's `created_at`, not git output)
- EDIT PINNED, not described: unique anchor (count==1), exact before/after blocks, before sha256 `b09f735297de49db08798bceed6cf4258d86bc16c39666496f9f6186192fd3df` 7842 bytes, AFTER sha256 `ca9f04e1ad06856d3c5d093ee2c6ba5d76e034d020c1cb482d65fc2868c68aaf` 7868 bytes computed in a scratch buffer with no worktree byte touched. A differing post-edit digest means the edit is not the planned edit and the cycle STOPS. `_git(repo, *args)` forwards positionally (no helper change); longest line 95 before and 95 after (no width regression); no ruff/black/flake8 config and no python linter in `.github/workflows/`
- SIX PROOF OBLIGATIONS: O-1 macOS suite GREEN with the node id recorded PASSED explicitly (a suite total cannot show one row ran); O-2 Linux container GREEN with nofile SOFT raised to the inherited HARD limit per R-4.31 arm (a) = requirement (iii) both platforms; O-3 cross-version BYTE-IDENTICAL output of the exact assertion command = requirement (ii) measured not asserted, and I DISCLOSE that my expected string came from a standalone env-replicating probe, NOT the fixture end-to-end, so O-3 closes that gap and a mismatch means the PLAN is wrong rather than the string needing a patch; O-4 the two must-be-NO discriminators in a scratch copy with a sha256 restore gate after each (residue invalidates every later run); O-5 census re-run with the instrument validated on YES and NO cases first; O-6 exactly one changed file
- FENCE: `fixtures.py` is NOT in scope (its pin is already correct; O-4's mutations are scratch-copy only and reverted); no other harness file, no C++/CMake byte, no `.github/`, no schema, no T4, and the `235525` §3 probe-red attribution must NOT ride this fix
- NO TOKEN IN THIS RELAY: ceremony is PLAN → Implementer PLAN-REVIEW → my bare `DISPATCH IMPL` parented to THAT approval; then T3 head FINAL and panelable. T2 head FINAL at `7688bbd`; both T3 heads LOCAL and UNPUBLISHED; R-4.38 binary inventory my stage-5 obligation; schema F+G-fenced; no remote CI, push, PR mutation, merge, publication, deployment or release; release hold ABSOLUTE
