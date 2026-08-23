## SITREP amendment — T4 rev4 completion A-1 closed: full 64-character digest restored; A-2 classified as a GCC-only guard-reach limitation

ROLE: Implementer
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-matrix-t4-nsdmi-fix-complete-r4-amend-a1
PARENT_DISPATCH_ID: s4-matrix-t4-nsdmi-r4-adjudication
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/SITREP-PLANNER-T4-NSDMI-R4-ACCEPTED-AT-BYTES-DIGEST-AMEND-GUARD-REACH-GCC-ONLY-20260822-200950.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-T4-NSDMI-R4-O1-O5-COMPLETE-GUARD-LINE-142-20260822-195729.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: `s4-matrix.planner` concurs and locks this A-1 amendment before the Stage-3 panel. `s4.orchestrator-planner` rules where A-2 is registered and convenes the panel only after A-1 is locked. This amendment grants no product, test, branch, push, PR, remote CI, merge, schema, publication, deployment, or release authority. The release hold is ABSOLUTE
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: authorized pre-edit T4 `29120d09891bfc46e80635c2212befa22a0e2604` on FINAL T3 `70601fc201b3c41d2542d82399787b5febcbf03c`
CANDIDATE: local T4 `6ba01ef92ef5052b317f6210fa202d5577e1e6c1` — byte-identical to the accepted candidate and unmoved by this amendment
SUPERSEDES: completion record `s4-matrix-t4-nsdmi-fix-complete-r4` at docs commit `b2bfd01f685722bbe823a6a4240f7467b878ffe1`; the original immutable relay is preserved, and this successor corrects its A-1 digest transcription while carrying its implementation evidence unchanged
FROM: s4-matrix.implementer
TO: s4-matrix.planner, s4.orchestrator-planner
CC: operator, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: Record-only amendment — A-1 closed with full git_exec.hpp SHA-256 ending f0a; A-2 disclosed as GCC-only guard reach; candidate 6ba01ef and every implementation result unchanged
FILING_STAMP: 20260822-212942

## 1. A-1 amended and classified

The original completion report truncated one trailing hexadecimal character from the
`src/core/repo/git_exec.hpp` fixed digest. It recorded a 63-character string ending `f0`; the
candidate object measures as the following 64-character SHA-256 ending `f0a`:

```text
src/core/repo/git_exec.hpp
  2500 bytes
  SHA-256 523e13186cb4bc7d9e6eb12b0a64ea0f56c8c6819068b30f3fc54c4052d87f0a
  blob    94f674fba2d466ad1d218ae2d1d0c5e7ae2963b4

src/core/repo/types.hpp
  6253 bytes
  SHA-256 744ba6c694b984a8f88a04828e293900e5a8b7ef6e0bdcc8ab90cc25db180f18
  blob    816ec6d4b315c44fcc9b3271e574cc17c6a52b6b

tests/test_repo_engine.cpp
  54027 bytes
  SHA-256 1dd44d5ce09b682f97b991b7edcef10eda4688e9ddc07ea4add0b319f5aee98c
  blob    ff8aad022b1068fdc3f524843d3043ce22e5e082
```

All three digests above were freshly re-derived from `git show 6ba01ef:<path>` and are exactly
64 characters. The candidate worktree remains clean at `6ba01ef`.

**Classification:** A-1 is a completion-record transcription defect only. It is not a product,
test, source-commit, evidence, or validation defect. No source or evidence byte is amended. The
original relay stays immutable; this successor supplies the producible reference value that
O-4d binds. With the corrected value, O-4d's restored `git_exec.hpp` digest equals the candidate
object exactly.

## 2. A-2 guard reach disclosed and classified

The class guard is proven under the planned GCC 13 environment and is carried by the Linux leg.
It is not active under the project's present macOS compile flags:

- GCC 13 with the project target's `-Wall -Wextra -Werror` promotes the designated aggregate
  omission and made the test-first guard RED before the NSDMIs.
- Apple clang 17 with the project's current `-Wall -Wextra` emits no diagnostic for that
  omission. The separate `-Wmissing-designated-field-initializers` flag is required for the
  must-be-RED arm on that compiler, and the project does not presently pass it.
- GCC's nineteen-row per-member multiplicity is compiler-specific. A Clang oracle must be
  re-derived from Clang output and must not translate the GCC row count.

**Classification:** A-2 is a verified guard-reach limitation and evidence-scope disclosure, not
a defect in the authorized implementation and not authority for a code or build-system edit.
The Linux GCC leg provides the regression protection proved by O-4. A macOS-only run does not.
Registration ownership remains with the Orchestrator and master registry; this amendment
records the limit for the panel without choosing a registry row or widening the candidate.
While this successor was being filed, the Orchestrator independently ruled A-2 accepted,
carried it to Stage 5 as an attributed limitation, and routed registration upward in commit
`ffb906fb2985d2777ca337fbf90c70a8385aecd5`. That later disposition is preserved and is not
authority for this seat to edit the registry.

## 3. Unchanged completion evidence and disposition

Everything else in the completion remains unchanged and was accepted at the bytes by
`s4-matrix.planner`: exact three-file candidate scope; literal nineteen-row GCC reproduction
and closure; focused Linux product 2/2 green with the separate harness aggregate classified only
inside R-4.35; macOS interaction 14/14 green; `GUARD_LINE = 142`; the O-4 exact positive tuple,
guard-removal negative control, and restored green; and O-5's byte-identical removal proof.

The honest weight of O-1b is reproducibility and closure against a same-base retained manifest,
not independent discovery. The stable population and the no-outside-struct closure result stand.

Candidate `6ba01ef` remains implemented, local, clean, unpublished, and not panelable until the
Planner concurs and locks A-1. The Orchestrator has staged and held the panel on that lock; it
has not run the three lenses. Neither A-1 nor A-2 moves the candidate. No remote CI, push,
force-push, PR mutation, merge, schema act, publication, deployment, or release occurred. The
release hold is ABSOLUTE.

## 4. Concurrent docs-lane reconciliation

The live docs `HEAD` advanced from `6ce08bf` to Orchestrator commit `ffb906f` during this filing.
That foreign commit absorbed the already-appended `20260822-212942` INDEX row for this successor,
then appended its own `20260822-212923` row, while leaving this successor relay untracked. The
foreign commit and both append-only rows are preserved exactly. This Implementer commit therefore
claims only this successor relay file; it does not claim, rewrite, or recommit the INDEX byte.

Relative to pre-concurrency `6ce08bf`, the INDEX now has one additional monotonicity diagnostic:
the later-appended Orchestrator row carries an earlier timestamp than the preceding Implementer
row. The current INDEX and `ffb906f` INDEX have the identical eleven-error lint set. This relay
does not repair or hide that foreign append-order defect.

ACTIONS_GIT_REF: record-only successor filing after read-only re-measurement of the three candidate objects; candidate 6ba01ef, branch s4-matrix/arm1-t4, source, tests, evidence, refs, worktrees, remotes and Docker state all unchanged. The successor row was appended at the then-live EOF and was concurrently absorbed by foreign Orchestrator commit ffb906f; this Implementer commit claims only this successor relay file
FINAL_GIT_STATUS_SHORT: candidate worktree clean at 6ba01ef; shared docs checkout preserves sibling-authored tracked and untracked state unchanged and unclaimed; only this successor relay remains as the owned uncommitted path after the concurrent ffb906f INDEX absorption
RELAY_LINT: exact-file freshness passed on the authored bytes before concurrent lane reconciliation; live INDEX EOF re-read; current INDEX error set path-normalized and identical to ffb906f with the one post-6ce08bf ordering diagnostic disclosed above; root mode required to name no error against this successor; cached diff check and explicit one-path docs commit; post-commit exact-file no-freshness verification

CARRY LIST:
- A-1 CLOSED by correct-forward record amendment: `git_exec.hpp` SHA-256 is the full 64-character `523e13186cb4bc7d9e6eb12b0a64ea0f56c8c6819068b30f3fc54c4052d87f0a`; original report preserved immutable
- A-1 classified as transcription-only, not product, test, source, evidence, or validation; O-4d now binds a producible digest that equals the candidate object
- A-2 disclosed and classified as a GCC-only guard-reach limitation: Linux carries the proven guard; current macOS flags do not; any Clang oracle must be re-derived rather than translated
- candidate `6ba01ef` and all accepted O-1 through O-5 results unchanged; no product or evidence byte moved
- Planner concur+lock is next; the Orchestrator has ruled A-2 and holds the Stage-3 panel pending that lock; no remote, integration, schema, publication, deployment, or release authority or act
