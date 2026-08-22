## PLAN rev1 — MF-1 accepted, and it is a sharp one to have to own: two relays ago I refused to round a non-green Linux aggregate up to "green both platforms", and then wrote an O-1 that REQUIRED exactly that rounding. The Linux predicate is now split from the macOS one and pins node IDs plus the allowed residual family instead of an unstable count. The dual restore gate moves INTO O-2 so the PLAN stands alone. Design, widening, digests and all three discriminators carry unchanged

ROLE: Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-matrix-t3-ref-sha-guard-plan-r1
PARENT_DISPATCH_ID: s4-matrix-t3-ref-sha-guard-plan-review-r0
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-T3-REF-SHA-GUARD-MUST-REVISE-LINUX-AGGREGATE-CONTRACT-20260822-124939.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-T3-LINUX-AGGREGATE-RULED-ACCEPTABLE-PANEL-CONVENED-INDEX-REPAIR-AFFIRMED-20260822-060126.md; .relays/s4/s4-matrix-arm1-plan/SITREP-PLANNER-T3-COMPLETION-ADJUDICATED-ACCEPTED-FINAL-PANELABLE-INDEX-ROWS-REPAIRED-20260822-055131.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new operator gate — `060538` left the disposition of each panel finding to my discretion and authorized the finding-(3) closure as a bounded in-lane test. This relay carries NO token and authorizes NO keyboard; a successor Implementer PLAN-REVIEW approve is required and the bare token parents to THAT approval. Adding the test CHANGES T3's head, so a focused re-lens follows per `060538`. No merge, push, PR mutation, schema act, deployment, or release. The release hold is ABSOLUTE
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: accepted T3 head `d4068684e51f67d0a11fb6d2251178fb2a1a70ea` (panel PASS at `060538`)
SUPERSEDES: PLAN `s4-matrix-t3-ref-sha-guard-plan` at commit `721bc2e`, blob `5b460f211bcfd42cb945542d706a7020ad789593`, SHA-256 `de6cb12ea7f7155cc957f918c9a0d87039e7d2bf2923461cfb87450f818827c7` (MUST REVISE); all three values independently re-derived at this seat before superseding
FROM: s4-matrix.planner
TO: s4-matrix.implementer
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: PLAN rev1 — MF-1 accepted: O-1's Linux predicate split from macOS, pinning the three new node IDs and the allowed R-4.35 residual family rather than an aggregate count that rotating membership makes unstable; the dual restore gate on BOTH compare.py and test_compare.py moved into O-2 so the PLAN is self-contained; design, twin widening, target digest a9d0a49f and all three discriminators unchanged

## 0. MF-1 accepted, and it is mine in a shape I have no excuse for

At `055131` I refused to round a non-green Linux aggregate up to "green both platforms" and
said so as plainly as I could. Then I wrote an O-1 whose first clause demanded
`harness/selftest` GREEN **at 1000 on both platforms** — which for Linux is exactly the
rounding I had just refused. The obligation's own later sentence (report R-4.35 separately,
never claim whole-suite green) contradicts its opening. Both cannot govern one run.

The arithmetic makes it concrete: Linux at `d406868` is 3 failed / 990 passed / 3 skipped.
Adding three passing nodes gives 993 passed — never 1000, never green. An obligation that
cannot be satisfied is not a strict gate; it is a gate that forces whoever runs it to either
fail truthfully or report loosely, and the second is how a laundered green gets written.

Their second point is equally right and I had not seen it: **do not pin a Linux aggregate
count at all.** R-4.35 membership rotates — that is my own `215649` characterization — and
platform skips vary, so a pinned count is neither candidate-owned nor stable, and pinning it
would manufacture a red the candidate does not own. rev1 pins the three new node IDs and the
allowed residual family instead, which is what the candidate actually owns.

And the dual restore gate: the crossed note at `123504` said I adopted it, but the artifact
under review still left `test_compare.py` to a separate obligation. A reviewed PLAN must stand
alone — a proof obligation that depends on a report-only side amendment is not in the plan.
It is now in O-2 itself with both digests.

Nothing else changed: the two-test design, the `assert_repo_state` twin, the anchors, the
target digest, and all three discriminators carry exactly as reviewed and independently
reproduced at the Implementer's seat.

## 1. Decision, and the widening declared first

`060538` recommended closing finding (3) and left it to me. **I am closing it**, because the
code is correct today and the value is a regression guard on the harness's single most
important guarantee: a branch restored to the *wrong commit* is the restore corruption this
harness exists to detect, and a future edit that compared ref NAMES only would pass every
current test while green-lighting it.

**The widening, stated before the plan rather than discovered in review.** The panel located
the gap in `compare_trees` → `_compare_repo_semantics`. Going to close it I measured the same
uncovered branch in the sibling surface:

```text
_compare_repo_semantics   compare.py:234       extra ref            NO test
                          compare.py:236-240   ref mismatch (SHA)   NO test
assert_repo_state         compare.py:285       extra ref            executed but NOT asserted
                          compare.py:287-291   ref mismatch (SHA)   NO test   <- the twin
```

The existing `test_repo_state_expectation_checks_head_branch_cleanliness_and_refs` asserts
`HEAD mismatch` and `missing ref` and stops; it never asserts a divergent SHA. So the panel's
finding is one instance of a two-instance class. I am covering both. Fixing one and leaving
its measured twin is precisely the "fixed one instance, never re-read for the class" defect I
would raise against another seat's work, and it stays in scope: same file, tests only, no
production byte.

`assert_repo_state`'s `extra ref` branch at `:285` I am deliberately NOT adding a test for —
it already *fires* inside the existing test (whose `wanted` omits `refs/heads/keep` and
`refs/heads/main`), it is simply unasserted. Executed-but-unasserted is a weaker gap than
never-executed, and one more test there earns less than it costs. Recorded, not silently
skipped.

## 2. The edit — pinned to anchors and a target digest

Three insertions in `harness/selftest/test_compare.py`, each anchor verified unique.

**(a) a `_git` helper, immediately before `def _matching_git_trees(tmp_path):`** — matching the
helper already in `test_fixtures.py`; the existing composed test open-codes `subprocess.run`
three times and a fourth open-coding would be worse than a helper:

```python
def _git(repo, *args):
    return subprocess.run(
        ["git", "-C", str(repo), *args], check=True, capture_output=True, text=True
    ).stdout.strip()
```

**(b) two tests, immediately before `def test_git_admin_bytes_are_excluded_from_byte_findings(tmp_path):`**

```python
def test_ref_restored_to_a_divergent_sha_reports_a_ref_mismatch(tmp_path):
    src, restored = _matching_git_trees(tmp_path)
    repo = restored / "repo"
    head = _git(repo, "rev-parse", "HEAD")
    keep = _git(repo, "rev-parse", "refs/heads/keep")
    assert head != keep
    _git(repo, "update-ref", "refs/heads/keep", head)

    findings = compare_trees(src, restored, load_tolerance())

    assert any(
        f"ref mismatch for refs/heads/keep: {keep} != {head}" in item
        for item in findings
    )


def test_extra_restored_ref_reports_a_repo_finding(tmp_path):
    src, restored = _matching_git_trees(tmp_path)
    repo = restored / "repo"
    _git(repo, "update-ref", "refs/heads/unexpected", _git(repo, "rev-parse", "HEAD"))

    findings = compare_trees(src, restored, load_tolerance())

    assert any("extra ref: refs/heads/unexpected" in item for item in findings)
```

**(c) one test, immediately before `def test_repo_state_expectation_accepts_unborn_head(tmp_path):`**

```python
def test_repo_state_expectation_reports_a_divergent_ref_sha(tmp_path):
    src, _ = _matching_git_trees(tmp_path)
    repo = src / "repo"
    head = _git(repo, "rev-parse", "HEAD")
    keep = _git(repo, "rev-parse", "refs/heads/keep")
    assert head != keep

    findings = assert_repo_state(
        src,
        {
            "repo": {
                "head_sha": head,
                "branch": "main",
                "porcelain_clean": True,
                "refs": {"refs/heads/keep": head, "refs/heads/main": head},
            }
        },
    )

    assert any(
        f"ref mismatch for refs/heads/keep: {keep} != {head}" in item
        for item in findings
    )
```

```text
TARGET  harness/selftest/test_compare.py
  before  sha256 5da5bd335f5b401676b54c24ff591b1ce4eb007ab9d2327218cade8a0c04ba43   12163 bytes
  AFTER   sha256 a9d0a49fce30623c12e9be5520da717f9f62abebde8cc2d9cca7e62569217566   13889 bytes
```

Design notes, measured not assumed: the fixture already yields two distinct SHAs
(`refs/heads/keep` at commit 0, HEAD/`main` at commit 1), so a divergent case needs only
`update-ref` and **no new commit** — which matters because committing would move the current
branch and manufacture a second, incidental finding. `update-ref` on a non-checked-out branch
leaves the worktree untouched, so these tests isolate the repo-semantic layer. The file's
longest line is 110 before and 110 after — no width regression.

## 3. Proof obligations

```text
O-1a MACOS.  python3 -m pytest harness/selftest -q GREEN at exactly 1000 passed (997 + 3).
     All three new node ids recorded PASSED explicitly -- a suite total cannot show a row ran.

O-1b LINUX, a SEPARATE predicate because the aggregate is not green and must not be made to
     look green.  Full harness/selftest under the bound topology: disposable ubuntu:24.04
     --platform linux/amd64, non-root, Docker --init or a reaping PID 1 (035347/R-4.40), and
     nofile SOFT raised to the inherited HARD limit (R-4.31 arm (a)).
       PASS CONDITION   all three new node ids PASS explicitly
       RECORD           the exact aggregate exit status and counts, verbatim
       CLASSIFY         every failure against the registered R-4.35 E3 scandir/TOCTOU family
       STOP AND ROUTE   if any new node fails, OR any Linux failure falls OUTSIDE that family
     DO NOT pin a Linux aggregate pass count.  R-4.35 membership rotates and platform skips
     vary, so a pinned count is neither candidate-owned nor a stable contract -- pinning it
     would manufacture a red the candidate does not own.  For orientation only, NOT a gate:
     d406868 Linux is 3 failed / 990 passed / 3 skipped, so the expected shape afterwards is
     3 failed / 993 passed / 3 skipped, exit 1.  Never "green both platforms".

O-2  MUST-BE-NO x3 -- the point of a regression guard is that it can fail.  In a scratch COPY,
     neuter each production branch in turn and confirm the matching test FAILS:
       compare.py:236  `if left_refs[ref] != right_refs[ref]:`  -> the divergent-SHA test
       compare.py:234  the `extra ref` append                   -> the extra-ref test
       compare.py:287  `if wanted_refs[ref] != actual["refs"][ref]:` -> the assert_repo_state test
     TWO TRAPS I HIT AND YOU MUST NOT INHERIT:
       (i) the `extra ref` append text occurs TWICE (:234 and :285).  A string replace asserts
           count==1 and DIES; mutate by LINE NUMBER, and assert the line you are about to
           replace still contains the expected token.
       (ii) preserve the ORIGINAL INDENTATION.  My first attempt at :287 used 12 spaces where
           the file has 16 and produced an IndentationError -- pytest then reported "1 error",
           NOT "1 failed", and an error means the test never ran and proves nothing.  Import
           the module (or assert collection succeeded) BEFORE reading any mutation verdict.
     After EACH mutation, DUAL RESTORE GATE -- both files, in this obligation, because they
     prove different things and a proof obligation must not depend on a side relay:
       harness/bivharness/compare.py   == afda520510161b353ead3bb596e5b26bf249866bc593b6632a20f7436cfe1aa4
       harness/selftest/test_compare.py == a9d0a49fce30623c12e9be5520da717f9f62abebde8cc2d9cca7e62569217566
     The first catches mutation residue; the second proves the edit under test never drifted.

O-3  SCOPE: exactly ONE changed file vs d406868.  compare.py, fixtures.py, test_fixtures.py
     and scenario.py must each be byte-identical to d406868 at the fixed head.

O-4  DIGEST GATE: the edited file must hash to a9d0a49fce30623c12e9be5520da717f9f62abebde8cc2d9cca7e62569217566.
     A different digest means the edit is not the planned edit and the cycle stops.
```

## 4. What I already ran, and what it does not discharge

Method: `git archive d406868` to a scratch export (no ref created, no worktree added, candidate
untouched), a venv from `harness/requirements.lock`.

```text
the three insertions applied -> target digest
  a9d0a49fce30623c12e9be5520da717f9f62abebde8cc2d9cca7e62569217566   REPRODUCES
harness/selftest full suite at the proposed head                     1000 passed
test_compare.py alone                                                31 passed
MUST-BE-NO  compare.py:236 neutered -> divergent-SHA test            1 failed   FIRES
MUST-BE-NO  compare.py:234 neutered -> extra-ref test                1 failed   FIRES
MUST-BE-NO  compare.py:287 neutered -> assert_repo_state test        1 failed   FIRES
            (after an import-sanity check, because my first attempt errored on indentation)
compare.py restored to its d406868 digest after every mutation       CONFIRMED
scope: compare.py / fixtures.py / test_fixtures.py / scenario.py     all unchanged
```

**This discharges none of your obligations** — mine ran on one platform in a scratch export with
no durable evidence root. If anything behaves differently at the candidate head, the plan is
wrong and I want that reported rather than reconciled.

## 5. The other three findings — disposed, not carried

**(1) `compare.py:349`, `_compare_repo_semantics` called without `allowed_roots` — REGISTER as
a stage-4 note. I am deliberately NOT hardening it.** Verified: the call takes only
`(src, restored, tol)` while the worktree loop passes `allowed_roots` to `_allowed_extra`. The
asymmetry is real. But the proposed fix *softens a detector*, and softening is the direction
that manufactures false-greens — the one defect class the panel confirmed absent. Over-strict
fails visibly; under-strict corrupts silently. And it is unreachable: the only declared
additive root anywhere is `.biv/agents` (three scenarios), which is biv's staging area and will
not contain a nested `.git`. Registering beats hardening here, and I would rather say why than
quietly do the tidier-looking thing.

**(2) `test_fixtures.py:112` — informational, REGISTER.** Concur: env identity overrides config
regardless, so the `Hostile User` assertion does not discriminate config isolation, which is
discriminatingly covered by the two sibling hook tests.

**(4) `compare.py:156` gitlink — REGISTER, and it is SHARPER than "latent trust boundary". I
measured it rather than reasoning about it:**

```text
a directory whose .git is a FILE containing the line `gitdir: /tmp/probe/real/.git`:
  git -C fake rev-parse HEAD  ->  ab0e55e67f21ed6005a36f774f52da9d647fe5da
  git -C real rev-parse HEAD  ->  ab0e55e67f21ed6005a36f774f52da9d647fe5da   IDENTICAL
```

`_repo_paths` accepts it (`marker.is_dir() or marker.is_file()`), so `_repo_state` would read
an **external** repository. The consequence is sharper than untested-trust-boundary: if src and
restored both carry the same gitlink, both sides resolve to the *same* external repo and match
trivially — the repo-semantic comparison becomes **vacuous**, an unfalsifiable check rather
than a passing one. File-content comparison stays sound, so it is not a total false-green, and
no fixture exercises a gitlink today, so it stays non-blocking. But "what counts as a repo
root" is a policy decision on a trust boundary, outside T3's authorized scope, so I route it
UP rather than deciding it in-lane.

## 6. Fence

In scope: `harness/selftest/test_compare.py`, tests only. **Not** in scope: `compare.py` or any
production byte (findings (1) and (4) are registered, not fixed), `fixtures.py`,
`test_fixtures.py`, any C++/CMake byte, `.github/`, the schema, T4.

No token here. Ceremony: this PLAN → Implementer PLAN-REVIEW → my bare token parented to that
approval → the focused re-lens `060538` promised on the new tests.

Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: none — no edits made at this seat to any tracked byte; the candidate branch is unmoved at `d406868`. Read-only verification plus one disposable `git archive d406868` scratch export outside every tracked worktree, where the three insertions, the full suite, the three mutation discriminators and the restore gates were executed; a venv built from `harness/requirements.lock`; a throwaway gitlink probe repo for finding (4); and `git show`/`git cat-file -s`/validated `git grep` reads at `d406868`. No merge, push, PR mutation, or remote CI. Docs lane: this relay + its INDEX row ride ONE explicit-path commit.
FINAL_GIT_STATUS_SHORT: this relay and its INDEX row are this seat's only working-tree delta at commit time; `git status --porcelain` over `harness/`, `src/`, `tests/`, `CMakeLists.txt` is empty and the T3 branch is unmoved at `d406868`; the shared checkout carries sibling-authored untracked paths, preserved and unclaimed
RELAY_LINT: exact-file WITH freshness immediately before commit; INDEX tail re-read before appending; `--index` diffed against the same lint on the pre-append blob; `--relay-root` run over the lane before commit, required to name no error against this relay, with a one-variable control; `substantive_actions_ref` and `implementation_work_claimed` both measured FALSE on the finished bytes. Commit gated on all of it by logical AND.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-T3-REF-SHA-GUARD-R1-LINUX-PREDICATE-SPLIT-DUAL-GATE-INLINED-20260822-125850.md` → TO `s4-matrix.implementer`
- CLOSING FINDING (3): the code is correct today and the value is a REGRESSION GUARD on the harness's single most important guarantee — a branch restored to the WRONG COMMIT is the corruption this harness exists to detect, and a future edit comparing ref NAMES only would pass every current test while green-lighting it
- WIDENING DECLARED UP FRONT, not discovered in review: the panel located the gap in `compare_trees`, and closing it I MEASURED the same uncovered branch in the twin `assert_repo_state` (`compare.py:287-291`) — the existing repo-state test asserts `HEAD mismatch` and `missing ref` and stops, never a divergent SHA. The panel's finding is ONE instance of a TWO-instance class and I cover both; fixing one while knowingly leaving its measured twin is the defect I would raise against another seat's work. Same file, tests only, no production byte
- DELIBERATELY NOT COVERED and recorded rather than silently skipped: `assert_repo_state`'s `extra ref` branch at `compare.py:285` already FIRES inside the existing test (whose `wanted` omits both refs), it is merely unasserted; executed-but-unasserted is a weaker gap than never-executed and one more test there earns less than it costs
- EDIT PINNED: three insertions at three unique anchors; before `5da5bd335f5b401676b54c24ff591b1ce4eb007ab9d2327218cade8a0c04ba43` 12163 bytes, AFTER `a9d0a49fce30623c12e9be5520da717f9f62abebde8cc2d9cca7e62569217566` 13889 bytes. MEASURED design notes: the fixture already yields two distinct SHAs (`keep` at commit 0, HEAD/`main` at commit 1) so a divergent case needs only `update-ref` and NO new commit — committing would move the current branch and manufacture a second incidental finding — and `update-ref` on a non-checked-out branch leaves the worktree untouched, isolating the repo-semantic layer; longest line 110 before and 110 after
- PRE-VALIDATED AT MY SEAT in a `git archive` scratch export: target digest REPRODUCES; full selftest **1000 passed** (997 + 3); `test_compare.py` 31 passed; and ALL THREE must-be-NO discriminators FIRE (neutering `compare.py:236`, `:234`, `:287` each makes the matching test fail), with `compare.py` restored to its `d406868` digest after every mutation and scope confirmed unchanged across `compare.py`/`fixtures.py`/`test_fixtures.py`/`scenario.py`. Discharges NONE of the Implementer's obligations — one platform, scratch export, no durable evidence root
- TWO TRAPS I HIT, WRITTEN INTO O-2 SO THEY ARE NOT INHERITED: (i) the `extra ref` append text occurs TWICE (`:234` and `:285`) so a string replace asserting count==1 DIES and the mutation never applies — mutate by LINE NUMBER and assert the token is present first; (ii) my first `:287` mutation used 12 spaces where the file has 16, producing an IndentationError, and pytest then reported "1 error" NOT "1 failed" — an error means the test never ran and proves nothing, so import-sanity must precede any mutation verdict
- FINDING (1) REGISTERED, NOT HARDENED, with the reason stated: the asymmetry is real (`_compare_repo_semantics` takes only `(src, restored, tol)`) but the proposed fix SOFTENS a detector, and softening is the direction that manufactures false-greens — the one class the panel confirmed absent; over-strict fails visibly, under-strict corrupts silently. Unreachable besides: the only declared additive root anywhere is `.biv/agents` in three scenarios, biv's staging area, which will not contain a nested `.git`
- FINDING (2) informational, concurred and registered: env identity overrides config regardless, so the `Hostile User` assertion does not discriminate config isolation, which the two sibling hook tests cover discriminatingly
- FINDING (4) REGISTERED and SHARPENED BY MEASUREMENT, not reasoning: a `.git` FILE containing a `gitdir:` line pointing at another repository resolves `git -C` to that EXTERNAL repo (probe: both `rev-parse HEAD` returned the identical SHA), and `_repo_paths` accepts it via `marker.is_dir() or marker.is_file()`. The consequence is sharper than "latent trust boundary" — if src and restored both carry the same gitlink, both resolve to the SAME external repo and match trivially, making the repo-semantic comparison **VACUOUS**, an unfalsifiable check rather than a passing one. File-content comparison stays sound so it is not a total false-green, and no fixture exercises a gitlink, so non-blocking — but "what counts as a repo root" is a trust-boundary POLICY decision outside T3's scope, so I route it UP rather than decide it in-lane
- MF-1 ACCEPTED AND IT IS MINE WITH NO EXCUSE: at `055131` I refused to round a non-green Linux aggregate up to "green both platforms", then wrote an O-1 demanding `harness/selftest` GREEN at 1000 on BOTH platforms — exactly that rounding — while the same obligation's later sentence said report R-4.35 separately and never claim whole-suite green. Both cannot govern one run. The arithmetic is concrete: Linux at `d406868` is 3 failed / 990 passed / 3 skipped, so three new passing nodes give 993, never 1000 and never green. An unsatisfiable obligation is not a strict gate — it forces the runner to fail truthfully or report loosely, and the second is how a laundered green gets written
- THEIR SECOND POINT I HAD NOT SEEN AND IT IS RIGHT: do NOT pin a Linux aggregate count at all. R-4.35 membership ROTATES (my own `215649` characterization) and platform skips vary, so a pinned count is neither candidate-owned nor stable and pinning it would MANUFACTURE a red the candidate does not own. rev1 pins the three new node IDs and the allowed residual family instead — what the candidate actually owns
- O-1 SPLIT INTO TWO PREDICATES: O-1a macOS full selftest GREEN at exactly 1000 with all three node ids PASSED explicitly; O-1b Linux under the bound topology (`--init`/R-4.40 + `nofile` R-4.31) where the PASS CONDITION is the three new node ids passing explicitly, the aggregate exit/counts are RECORDED verbatim, every failure is CLASSIFIED against the registered R-4.35 family, and it STOPS AND ROUTES if a new node fails or any failure falls OUTSIDE that family. The `3 failed / 993 passed / 3 skipped` shape is given for ORIENTATION ONLY and explicitly NOT a gate
- DUAL RESTORE GATE MOVED INTO O-2 ITSELF: `compare.py` at `afda520510161b353ead3bb596e5b26bf249866bc593b6632a20f7436cfe1aa4` and `test_compare.py` at `a9d0a49fce30623c12e9be5520da717f9f62abebde8cc2d9cca7e62569217566` after EACH mutation. The `123504` crossed note said I adopted it but the reviewed artifact still deferred the test target to a separate obligation — a reviewed PLAN must stand alone, and a proof obligation depending on a report-only side amendment is not in the plan
- NOTHING ELSE CHANGED and the review independently reproduced it: two isolated `compare_trees` tests, the `assert_repo_state` twin widening, the exact anchors, before `5da5bd33` / after `a9d0a49f`, macOS 31 and 1000 passed, and all three must-fail controls each yielding exactly one failed node with no collection or import error
- FENCE: `test_compare.py` tests only; NOT `compare.py` or any production byte (findings (1) and (4) are registered, not fixed), not `fixtures.py`, not `test_fixtures.py`, no C++/CMake byte, no `.github/`, no schema, no T4. NO TOKEN here: PLAN → Implementer PLAN-REVIEW → my bare token parented to THAT approval → the focused re-lens `060538` promised. Adding the test CHANGES T3's head. T2 head FINAL at `7688bbd`; both T3 heads LOCAL and UNPUBLISHED; R-4.38 binary inventory my stage-5 obligation; schema F+G-fenced; no remote CI, push, PR mutation, merge, publication, deployment or release; release hold ABSOLUTE
