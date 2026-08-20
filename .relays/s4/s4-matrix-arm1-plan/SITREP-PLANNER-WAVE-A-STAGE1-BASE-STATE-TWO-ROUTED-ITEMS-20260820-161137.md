## SITREP (STAGE 1) — Wave-A base state MEASURED at the new base: the four candidates are a STACK (#16→#17→#19→#20) sharing one merge base and sitting **530 commits behind** main; the scouted probe overlap is measured and its residual risk NAMED (auto-merges textually, production undrifted, but #16 restructures the very `spawn_error`/`nonzero_exit` classification slice E's new platform-split assertion depends on — resolvable only by stage 2, not by reading); and TWO items route UP under the STOP rule before any keyboard: (A) a REAL semantic conflict in `harness/bivharness/compare.py` on #19/#20, and (B) a mechanic question that gates the WHOLE re-verification — every candidate conflicts on the append-only `.relays/s4/INDEX.md`, so no re-based head can exist without reconciling a conflict I am told not to reconcile

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-matrix-wave-a-reverify-stage1
PARENT_DISPATCH_ID: s4-matrix-wave-a-reverify-dispatched-down
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-WAVE-A-REVERIFICATION-DISPATCHED-NEW-BASE-A2EEDC9-NOTHING-TRANSCRIBES-20260820-145356.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no new operator gate — this is stage-1 measurement, read-only; but TWO cells need YOUR word before stages 2-4 can run (the `compare.py` conflict and the INDEX-reconciliation mechanic), per the STOP rule's "do not reconcile a conflict at the keyboard on your own authority"; no merge, no push, no PR state change occurred; the release hold is ABSOLUTE
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
FROM: s4-matrix.planner
TO: s4.orchestrator-planner
CC: operator, s4.orchestrator-reviewer, master.orchestrator-planner, s4-matrix.implementer
SUBJECT: SITREP — stage-1 base state for #16/#17/#19/#20; probe overlap measured with its residual named; two routed items (compare.py semantic conflict; INDEX reconciliation gates every re-base)

## 1. The stack, and the size of the drift

```text
#16  s4-matrix/arm1-t1  tip d691f9be8  →  main       6 commits
#17  s4-matrix/arm1-t2  tip 92a70c9cd  →  arm1-t1   11 commits (includes #16)
#19  s4-matrix/arm1-t3  tip d7d32f94c  →  arm1-t2   14 commits
#20  s4-matrix/arm1-t4  tip cb1f6254e  →  arm1-t3   32 commits
merge base (all four)   285cfc475      behind current main: 530 commits
```

They are a dependent STACK, not four independents — #17 bases on #16, #19 on #17, #20
on #19. Your "in your stack order" therefore also fixes the only order in which they can
be re-based: a change to #16's re-based head re-parents everything above it.

## 2. Conflict state — measured by trial merge only, nothing written

```text
#16 arm1-t1   CONFLICT: .relays/s4/INDEX.md
#17 arm1-t2   CONFLICT: .relays/s4/INDEX.md
#19 arm1-t3   CONFLICT: .relays/s4/INDEX.md  +  harness/bivharness/compare.py
#20 arm1-t4   CONFLICT: .relays/s4/INDEX.md  +  harness/bivharness/compare.py
```

No product-source (`src/`) conflict on any candidate. The two distinct classes are
routed separately below because they are not the same kind of thing.

## 3. The scouted probe overlap — MEASURED, and its residual named honestly

You asked me to measure #16's `probe.cpp` refactor against slice E's `test_probe.cpp`
assertions and not to assume consistency. Measured:

```text
main-side drift among #16's touched files:  tests/test_probe.cpp  ONLY
  src/core/support/probe.cpp      UNCHANGED in main since the merge base
  src/core/support/subprocess.cpp UNCHANGED in main
  probe.hpp / subprocess.hpp      UNCHANGED in main
```

**Textually the two sides do not collide.** Slice E's hunks are `write_invalid_executable`
(now a 16-byte binary ELF header instead of the old text line) and the platform-split
outcome assertion (`spawn_error` on `__APPLE__`, `nonzero_exit` elsewhere). #16's hunks
are elsewhere in the file: it replaces the local `TempDir` with the shared
`biv::test_support::TempDir`, and it re-points a source-text seal. Git auto-merges them,
which is why `test_probe.cpp` does not appear in the conflict list.

**Semantically the risk is real and I will not call it clean by reading.** Slice E's new
assertion is a platform split on the *outcome classification* for an invalid-ELF pinned
executable. #16 restructures exactly that classification — the diff moves and rewrites
where `ProbeOutcome::spawn_error` and `ProbeOutcome::nonzero_exit` are assigned (five
assignment sites removed from the old path, re-established in the new one). Slice E also
changed the *input* to that path from a text file (ENOEXEC-shaped) to a valid-magic
truncated ELF (kernel-accepts-then-fails-shaped) — which is why it needed a platform
split at all. So the question "does the auto-merged combination still yield `spawn_error`
on macOS and `nonzero_exit` on Linux" is decidable only by running it on both platforms.
**That is precisely stage 2, and it is the specific thing to watch there.** No assumption
is recorded either way.

One further item for the eventual panel, flagged now so it is not discovered late: #16's
other change to this file re-points a test that `ifstream`s **production source text**
(the "one traced readiness primitive" seal) from `probe.cpp` to `subprocess.cpp`. That is
the known source-text-sealing shape — such a test freezes file layout invisibly to
call-graph and symbol instruments. It is #16's own pre-existing design, not drift, but it
interacts with a refactor that moves machinery between exactly those two files, so it
belongs on the panel's list rather than in a footnote.

## 4. TWO items routed UP — the STOP rule, applied before any keyboard

**(A) `harness/bivharness/compare.py` — a REAL semantic conflict on #19/#20.** Both sides
extend the same comparator:

```text
main side (slice C, f03ce70)  +32/-3   adds _validated_additive_roots() and _allowed_extra()
                                       — additive-roots validation for consent-no staging
#19 side                      +219/-8  git fixture builders, repo-aware compare, tolerance git rows
```

Resolving this is not a mechanical merge: it decides how repo-aware comparison and
additive-roots validation **compose** inside `compare_trees` — a semantic design question
about the harness comparator, owned by whoever owns that contract. Per your STOP rule I
have not reconciled it and have written nothing. Routing for a ruling on who resolves it
and under what authority.

**(B) The INDEX-reconciliation mechanic — this one gates the ENTIRE re-verification, so
it needs your word first.** Every candidate conflicts on `.relays/s4/INDEX.md`, the
append-only relay index (both lanes appended rows; the known structural shared-INDEX
class with no per-seat isolation). Stages 2-4 all require *re-based heads* — suites green
"at each candidate's re-based head", panel "at the ACTUAL SHAs that would merge". But
producing any re-based head requires reconciling that INDEX conflict, which is exactly
the act your STOP rule reserves. I am not going to treat "it's only the docs lane" as
self-granted permission to reconcile a conflict, so:

- **(B1)** rule the mechanical INDEX resolution in-scope (both sides' rows retained,
  append-only preserved, no row rewritten or reordered) and I proceed; or
- **(B2)** direct a different mechanic that avoids the question — e.g. evaluate each
  candidate at a `merge-tree`-produced tree without committing a re-based head, or merge
  current `main` INTO each candidate branch rather than re-basing; or
- **(B3)** hand the re-base to the seat that owns the INDEX shard convention.
My recommendation is **(B1)** with the resolution rule stated explicitly in your reply so
it is a grant and not a drift — the conflict is genuinely mechanical (two append-only
tails), and (B2)'s no-commit variants make stage-3's "panel at the ACTUAL merge SHA"
hard to satisfy honestly.

## 5. What I have NOT done, and what I propose

Not done: no merge, no push, no re-base, no conflict resolution, no PR state change, no
schema-act contact (the Arm-1 schema act stays F+G-fenced and untouched), no product or
test edit. All measurement above is trial-merge and diff arithmetic; nothing was written
to any branch.

Proposed on your word: **(i)** on (B), begin stage 2 with #16 alone — it is the stack
root, has no product conflict, and carries the probe question that stage 2 exists to
answer; run both platforms per the chartered recipe including the `nofile` soft→hard
condition now in `CLAUDE.md` "Local Linux CI". **(ii)** #17 follows #16 (no product
conflict either). **(iii)** #19/#20 stay HELD pending (A) — re-basing them means
resolving `compare.py`, and their stack position means nothing above #19 can be measured
honestly until it is settled. **(iv)** stages 3-4 and the merge-readiness report follow
per your five stages; each merge remains a new operator word, which I am not
anticipating.

`origin` untouched; both refs LOCAL and UNPUBLISHED; merge ≠ push ≠ release; the release
hold is ABSOLUTE.

ACTIONS_GIT_REF: read-only measurement only — `git merge-tree` trial merges (discarded), `git diff`/`rev-list` arithmetic across `285cfc475`, the four candidate tips, and local `main`. NO re-base, NO conflict resolution, NO merge, NO push, NO branch or PR mutation, NO product/test edit. Docs lane: this relay + its INDEX row ride one explicit-path commit (SHA lands after filing).
FINAL_GIT_STATUS_SHORT:
none — clean tree (matrix-seat paths; the shared checkout carries sibling-authored state, excluded/unclaimed)
Fresh at 20260820-161137 before this relay + INDEX write; this relay and the INDEX row are this seat's working-tree delta at commit time.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/SITREP-PLANNER-WAVE-A-STAGE1-BASE-STATE-TWO-ROUTED-ITEMS-20260820-161137.md` → TO `s4.orchestrator-planner`
- STAGE 1 MEASURED: dependent stack #16→#17→#19→#20, one merge base `285cfc475`, all 530 commits behind main; no `src/` conflict anywhere
- SCOUTED OVERLAP measured: textually disjoint (auto-merges), production probe/subprocess UNDRIFTED in main, BUT #16 rewrites the `spawn_error`/`nonzero_exit` classification that slice E's new platform-split assertion depends on, over a fixture slice E also changed (text → valid-magic truncated ELF) ⇒ decidable ONLY at stage 2 on both platforms; no assumption recorded. Panel note: #16 re-points a production-source-text seal between the two files the refactor moves machinery across
- ROUTED (A): `harness/bivharness/compare.py` REAL semantic conflict on #19/#20 (main +32/-3 additive-roots validation from slice C `f03ce70` vs #19 +219/-8 repo-aware compare) — composition question, NOT reconciled, ruling requested
- ROUTED (B): every candidate conflicts on append-only `.relays/s4/INDEX.md`, so NO re-based head exists without reconciling a conflict the STOP rule reserves — this gates stages 2-4 for the whole stack; options (B1) rule it in-scope with the resolution rule stated [RECOMMENDED], (B2) alternate mechanic, (B3) hand to the INDEX-shard owner
- schema act untouched and F+G-fenced; nothing merged/pushed/re-based; release hold ABSOLUTE
