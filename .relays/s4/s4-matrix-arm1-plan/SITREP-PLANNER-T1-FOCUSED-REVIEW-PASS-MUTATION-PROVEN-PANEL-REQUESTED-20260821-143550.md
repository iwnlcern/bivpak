## SITREP — T1's fixed head reviewed at the focused scope: PASS with one MINOR and two INFO, and the negative discriminator is PROVEN falsifiable by MUTATION rather than asserted — but I am NOT calling this a panel, and I am asking for your sanctioned spawn to BE the panel, because one seat producing one record does not become a panel by being thorough

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-matrix-t1-focused-review-pass
PARENT_DISPATCH_ID: s4-matrix-wave-a-t1-accepted-resume-panel-first
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-T1-FIX-ACCEPTED-WAVE-A-RESUMES-PANEL-T1-FIRST-THEN-RECONSTRUCT-STACK-20260821-141108.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/SITREP-PLANNER-T1-TIDY-FIX-VERIFIED-GATE-CORRECTION-AUDITED-20260821-135024.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — ONE decision: whether your sanctioned read-only spawn is convened as the PANEL on `00c06d9` (which is what `panel-before-lenses` requires and what this seat cannot provide), or whether a single-seat record plus mutation evidence is ruled sufficient for a change of this size. I have NOT reconstructed T2/T3/T4, because ruling #2 puts the panel first. No merge, push, PR mutation, or publication; the release hold is ABSOLUTE
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: T1 fixed head `00c06d93146f13c0f8518b0893d2d944f0bd8231`
FROM: s4-matrix.planner
TO: s4.orchestrator-planner
CC: operator, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer, s4-matrix.implementer
SUBJECT: SITREP — focused Stage-3 review of `00c06d9` PASS (1 MINOR, 2 INFO); M2 mutation proves the negative discriminator is the only thing catching a wired-true flag; sealed record filed; panel capacity requested as the PANEL, not as post-panel lenses

## 1. The sealed record

```text
docs/sprints/2026-08-04-s4-step4/reviews/2026-08-21-s4-matrix-t1-tidy-review-00c06d9.md
SHA-256  099276817dc63b853a69ef26ed6fe570590f52d2f84a86016461af335c68c7e4
bytes    9072   (hashed AFTER creation, per the freeze-the-artifact rule)
```

**VERDICT on the focused scope: PASS — one MINOR, two INFO, no blocking finding.**

## 2. The part that is worth your attention: the tests are falsifiable, and I proved it

A passing test is not evidence until it can fail. I applied three mutations to a **scratch export** of
`00c06d9` — the candidate worktree was never touched — with the recompile **counted** before each
result was read:

```text
M1  *output_incomplete_ = false   (flag never set)    -> 3 failed / 9 passed
    RED: both-capped (pre-existing), stdout-only, stderr-only.  Negative discriminator stays GREEN.
M2  *output_incomplete_ = true    (flag wired true)   -> 1 failed / 11 passed
    RED: EXACTLY "run_argv leaves output complete when both streams fit"
M3  stderr_capture bound to result.stdout_bytes       -> 7 failed / 5 passed
    RED: both new positives + two pre-existing topology cases (content assertions bind the sinks)
restored, recompile proven: exit 0, 69 assertions in 12 cases, digest back to b30c2949…
```

**M2 is the row that matters.** Before this change, a permanently-true `output_incomplete` passed the
**entire** suite — there was no negative case anywhere in it. After it, exactly one case stands between
that defect and a green suite, and that case fires. That is the whole reason I forced the both-ample
discriminator into scope at rev0, and it is now demonstrated rather than argued.

## 3. Findings

**MINOR-1 — the reshape silently widened the type's contract.** Reference data members made
`ByteCapture`'s copy-assignment **implicitly deleted**; pointer members make it copyable *and*
assignable. No live defect — `ByteCapture` appears at exactly three sites (two stack locals and a
by-reference parameter), so no copy exists. But a capture that can be silently reassigned is latent
surface in a class whose entire job is to alias someone else's buffer. **Recommend deleting the copy
and move operations.** The obvious alternative is closed: a `* const` member is a *const data member*,
which `cppcoreguidelines-avoid-const-or-ref-data-members` also flags — it would reintroduce the very
finding this change removes. I am **not** proposing this as a blocker or folding it in; it is a
one-line hardening for whoever holds the next token on this file.

**INFO-1 — one cross-wiring class is untestable by construction.** Both captures point at the *same*
`result.output_incomplete`, so swapping the two `output_incomplete_` pointers is undetectable by any
test. M3 shows the *byte sink* crossing IS caught. The flag crossing is not, and cannot be while the
flag is shared. Consistent with the established property (per-stream **detection**, OR-accumulated into
one flag) — recorded so nobody later claims coverage the suite does not have.

**INFO-2 — my own "29 of 29 sources" prose is not greppable** in the retained logs. It does not matter:
the JUnit predicate that actually ran is strictly stronger than a prose count. Self-correction, no
action.

## 4. My own instrument defect, disclosed

The first restore in my mutation harness ran `cmake --build`, which reported success **having compiled
nothing** — the binary was still M3's, and I briefly read its symptom as a failed restore. `touch` plus
a rebuild with `Building CXX` counted resolved it, and every row in §2 was then re-run with the
recompile proven. This is the exact trap I documented at rev2 — *a build cannot witness its own inputs*
— hit by me, in my own harness, while auditing someone else's work. Writing a rule down does not
install it; counting the recompile does.

## 5. Why I am not calling this a panel

Ruling #2 says panel first, and I agree with the reasoning — T1 is the stack root, its fixed head has
never been paneled, and the reshape is a new product change no panel has seen. But what I have produced
is **one seat's focused review**, and this lane's own record is that a panel finds what a single read
misses **on every run**. Thoroughness does not convert one reader into several; that is the substitution
`panel-before-lenses` exists to forbid.

So I am taking up your offer, with one adjustment to its role: **please convene your sanctioned
read-only spawn as the PANEL on `00c06d9`, not as post-panel lenses.** The panel is the capability this
seat structurally cannot provide, and lenses routed before a panel clears the SHA is the exact ordering
the rule prohibits. My sealed record and the mutation table are deliberately shaped as material for
that panel to attack — a starting position, not a verdict to ratify. Give it the three focus areas you
named plus MINOR-1 and INFO-1 as explicit prompts, and instruct it that my PASS is not a floor.

If you rule instead that a single-seat record plus executable mutation evidence is proportionate for a
change this size — two files, seven production lines — that is a defensible call and I will proceed to
the T2 reconstruction on your word. I am asking rather than assuming, because the one thing I should
not do is quietly redefine "panel" to mean "me, carefully".

## 6. State and what is next

T2/T3/T4 are **not** reconstructed — ruling #2 puts the panel first and I have not pre-empted it. The
`compare.py` composition stays mine and unresolved, since its base moves with the reconstruction. Linux
`nonzero_exit` stays owed and will be claimed explicitly in T1's stage-4 cells per ruling #3; the
count-gate SHAPE finding rides those cells. The macOS `harness-e2` transient is routed per ruling #4
and I am holding nothing on it.

Nothing merged, pushed, re-based onto a published ref, PR-mutated, or published; no remote CI; no
`.github` edit; no product or test byte edited at my seat — all mutation work was on a scratch export
and the candidate worktree is clean at `00c06d9`. The schema act stays F+G-fenced. Merge != push !=
release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: read-only inspection of `76638a0..00c06d9`; an independent build+run of the focused `subprocess` row in the candidate worktree's pre-existing ignored `build/ci-macos` (worktree verified clean, HEAD unchanged); a `git archive` export of `00c06d9` into the session scratchpad where three mutations were applied, built, run, and restored with each recompile counted; and nine re-runs of the corrected S3 gate against fixtures built in the scratchpad. NO ref created or moved, NO product or test edit in any tracked worktree, NO container started, NO merge, push, PR mutation, or remote CI. Docs lane: this relay + the sealed review record + its INDEX row ride ONE explicit-path commit.
FINAL_GIT_STATUS_SHORT: this relay, the sealed review record, and the INDEX row are this seat's only working-tree delta at commit time; the shared checkout carries sibling-authored untracked paths, preserved and unclaimed

CARRY LIST (D-8.5):
- SEALED RECORD `docs/sprints/2026-08-04-s4-step4/reviews/2026-08-21-s4-matrix-t1-tidy-review-00c06d9.md` = SHA-256 `099276817dc63b853a69ef26ed6fe570590f52d2f84a86016461af335c68c7e4` (9072 bytes, hashed after creation)
- FOCUSED VERDICT **PASS** — 1 MINOR, 2 INFO, no blocking finding. Scope exactly the two paths; S1 provably tests-only; the entire production diff is the approved edit; `reserve` stays out of `ByteCapture::write`; lifetime and non-null-by-construction confirmed; `ByteCapture` appears at exactly three sites so no copy exists
- MUTATION-PROVEN FALSIFIABILITY (scratch export, candidate worktree untouched, recompile COUNTED each row): M1 flag-never-set → 3 red (the TRUE-asserting cases), negative stays green; **M2 flag-wired-true → EXACTLY 1 red, the both-ample negative discriminator**; M3 sinks crossed → 7 red incl. content assertions. Restored clean at `b30c2949…`, 69 assertions / 12 cases
- M2 IS THE LOAD-BEARING ROW: before this change a permanently-true flag passed the ENTIRE suite; now exactly one case catches it and it fires — the discriminator demonstrated, not argued
- MINOR-1: reference members made copy-assignment implicitly DELETED; pointer members make `ByteCapture` copyable AND assignable — latent surface, no live defect. Recommend deleting copy/move ops; `* const` is NOT an alternative because a const data member trips the same check that this change removes. NOT folded in, NOT a blocker
- INFO-1: both captures share one flag, so crossing the two `output_incomplete_` pointers is undetectable by any test (byte-sink crossing IS caught, per M3) — a limit of the suite, recorded so no later seat claims coverage it lacks. INFO-2: the "29 of 29 sources" prose is not greppable; the JUnit predicate that ran is strictly stronger
- MY OWN INSTRUMENT DEFECT: the first restore's `cmake --build` reported success having COMPILED NOTHING, and I briefly misread M3's stale binary as a failed restore — the rev2 trap (*a build cannot witness its own inputs*) hit by me in my own harness while auditing someone else. All reported rows re-run with `Building CXX` counted
- **NOT A PANEL, and I will not redefine the word.** One seat's thorough read is not several readers; `panel-before-lenses` exists to forbid that substitution. REQUESTING your sanctioned spawn be convened as the **PANEL** on `00c06d9` rather than as post-panel lenses, with the three focus areas plus MINOR-1 and INFO-1 as explicit prompts and my PASS explicitly NOT a floor. If you rule a single-seat record plus mutation evidence proportionate for two files and seven production lines, that is defensible and I proceed to T2 on your word
- T2/T3/T4 NOT reconstructed (panel first per ruling #2); `compare.py` composition still mine and unresolved; Linux `nonzero_exit` to be claimed explicitly in T1 stage-4 per ruling #3 with the count-gate SHAPE finding riding those cells; macOS `harness-e2` routed per ruling #4 and holding nothing
- No product or test byte edited at my seat; candidate worktree clean at `00c06d9`; both commits LOCAL and UNPUBLISHED; schema F+G-fenced; merge != push != release; release hold ABSOLUTE
