# FOCUSED Stage-3 review — T1 tidy repair at `00c06d93146f13c0f8518b0893d2d944f0bd8231`

Scope of this record, per the Orchestrator's `141108` ruling #2: the `ByteCapture` pointer reshape,
the both-ample negative discriminator, and the gate correction. T1's unchanged bytes are not re-audited.

**WHAT THIS RECORD IS, AND IS NOT.** This is a **single-seat** focused review carrying executable
mutation evidence. It is **NOT a panel.** This lane's own history is that a panel finds what a single
read misses on every run, and one seat producing one record does not become a panel by being thorough.
The independent adversarial capacity the Orchestrator offered at `141108` is requested in the
accompanying relay, and it is requested **as the panel** — the thing this seat structurally cannot
provide — not as post-panel lenses. Read this record as material for that panel to attack, not as a
substitute for it.

## Verdict

**PASS on the focused scope, with one MINOR and two INFO.** No blocking finding. The product change
does what it claims, and — established by mutation, not by reading — the tests that guard it can fail.

## 1. The change, at the bytes

```text
scope    git diff --name-status 76638a0..00c06d9 -> M src/core/support/subprocess.cpp
                                                    M tests/test_subprocess.cpp   (nothing else)
split    git diff --quiet 76638a0 b61e761 -- src/  -> exit 0   S1 is PROVABLY tests-only
source   9af9d55c294ca0947ce6900b332d792e88338feb2500908de71b5d370fb2797b  (pre-edit)
      -> b30c2949121ca645e70922c3a80f641079120829828beb6f0c806b16f8165695  (fixed)
```

The entire production diff: `bytes_{&bytes}` / `output_incomplete_{&output_incomplete}` in the ctor
init list, three dereference sites in `write()`, two member declarations, and `buffer{}` at `:220`.
Every other arithmetic and control expression is character-identical. `reserve` occurs only at
`:521`/`:529` for `argv`/`env` — outside `ByteCapture::write`, so `76638a0`'s geometric-growth repair
stands.

**Lifetime and aliasing.** `SpawnResult result;` is declared immediately before both captures in the
same scope, so it outlives them. Both members are initialized from references, so neither pointer can
be null by construction. No pointer arithmetic is performed. `ByteCapture` appears at exactly three
sites — the two stack locals and a by-reference parameter of `drain_once` — so no copy, move, store, or
return of the type exists anywhere.

## 2. Mutation evidence — the tests are falsifiable, proven by execution

A passing test is not evidence until it can fail. Three mutations were applied to a **scratch export**
of `00c06d9` (the candidate worktree was never touched), each with the recompile **proven** (`Building
CXX` observed) before its result was read:

| Mutation | Expected | Observed |
|---|---|---|
| **M1** `*output_incomplete_ = false` (flag never set) | the three TRUE-asserting cases go red; the negative stays green | **3 failed / 9 passed** — `…both captured streams incomplete at their caps`, `…only stdout reaches its cap`, `…only stderr reaches its cap`. Negative discriminator green. |
| **M2** `*output_incomplete_ = true` (flag wired true) | **only** the negative discriminator goes red | **1 failed / 11 passed** — exactly `run_argv leaves output complete when both streams fit` |
| **M3** `stderr_capture` bound to `result.stdout_bytes` (sinks crossed) | content assertions go red | **7 failed / 5 passed**, including both new positives and two pre-existing topology cases |

Restored to pristine with the recompile proven: **exit 0, 69 assertions in 12 test cases**, digest back
to `b30c2949…`.

**M2 is the load-bearing row.** Before this change a permanently-true `output_incomplete` passed the
entire suite — there was no negative case anywhere. After it, exactly one case stands between that
defect and a green suite, and it fires. That is the property the negative discriminator was required
for, now demonstrated rather than asserted.

**M3** additionally proves the two sinks are bound to the correct streams: crossing them is caught by
the exact-content assertions.

## 3. The mid-flight gate correction — audited for a disable

The S3 gate was changed during execution. A granted "correct the parser" is precisely how an assertion
becomes a no-op, so the corrected gate was re-run against every original negative **with the real
comma suffix applied**, plus two arms aimed at what widening `status` could open:

```text
MUST-BE-YES  status=fail + ',-warnings-as-errors', rc=8   exit 0   gate OK
MUST-BE-YES  status=run  + ',-warnings-as-errors', rc=8   exit 0   gate OK
MUST-BE-NO   ctest exit 0                                  exit 1   refused
MUST-BE-NO   green row (no failure child)                  exit 1   refused
MUST-BE-NO   skipped row (status notrun)                   exit 1   refused
MUST-BE-NO   FOURTH finding, comma-suffixed                exit 1   refused
MUST-BE-NO   SWAPPED check-id, comma-suffixed              exit 1   refused
MUST-BE-NO   status=fail with NO failure child             exit 1   refused
MUST-BE-NO   unexpected status 'disabled'                  exit 1   refused
```

The **S5 GREEN gate is byte-identical** to the approved version — the green half was never loosened.
The correction is narrowing-preserving.

Both gate defects originated in the plan, not the implementation: the predicate required
`status == 'run'` while CTest records an executed-and-failed row as `status="fail"`, and the fixture
used a bare `[check-id]` while clang-22 under `WarningsAsErrors` emits `[check-id,-warnings-as-errors]`.
The disclosed residual fired fail-closed at S3, was corrected gate-side with product bytes untouched,
and the raw first attempt is retained at `.superpowers/sdd/t1-tidy-BnRABAzv`.

## 4. Findings

**MINOR-1 — the reshape silently widened the type's contract.** With reference data members,
`ByteCapture`'s copy-assignment operator was implicitly **deleted** (a reference cannot be rebound).
With pointer members the type is now copyable *and* copy-assignable. There is no live defect — no copy
of `ByteCapture` exists anywhere — but a capture that can be silently reassigned is latent surface in a
class whose whole job is to alias someone else's buffer. Recommend deleting the copy and move
operations. Note the obvious alternative is **not** available: a `* const` member would be a const data
member, which `cppcoreguidelines-avoid-const-or-ref-data-members` also flags, reintroducing the very
finding this change removes.

**INFO-1 — one cross-wiring class remains untestable, by construction.** Both captures point at the
*same* `result.output_incomplete`, so swapping the two `output_incomplete_` pointers is undetectable by
any test. M3 shows the *byte sink* cross-wiring is caught; the flag cross-wiring is not, and cannot be
while the flag is shared. This is consistent with the established property (per-stream **detection**,
OR-accumulated into one flag) and is not a defect — it is a limit of what the suite can prove, recorded
so nobody later claims coverage it does not have.

**INFO-2 — analyzer source-coverage count.** The plan's prose asked the analyzer row be observed
covering "29 of 29 sources". No such count is printed in greppable form in the retained logs. It does
not matter: the JUnit predicate that actually ran (row present exactly once, not skipped/notrun,
failure-child present at S3 and absent at S5) is strictly stronger than a prose count.

## 5. Convener's own instrument defect, disclosed

The first restore in the mutation harness ran `cmake --build`, which reported success **having
compiled nothing** — the binary under test was still M3's, and its symptom (empty `stderr_bytes`,
stdout carrying both streams) was briefly misread as a failed restore. `touch` plus a rebuild with the
recompile counted resolved it. This is the exact trap this plan documented at rev2 — *a build cannot
witness its own inputs* — hit by the convener, in the convener's own harness, while auditing someone
else's work. Every mutation row above was subsequently re-run with `Building CXX` counted before its
result was read; the table reflects only those runs.

## 6. Evidence

```text
canonical evidence root   .superpowers/sdd/t1-tidy-QTViwhrG   RECEIPTS.sha256 = b69a72ba…, 22/22 OK re-verified
first-attempt (gate defect) .superpowers/sdd/t1-tidy-BnRABAzv
transient macOS harness-e2  .superpowers/sdd/t1-tidy-ufKPP5z5
S3  log carries exactly the three findings; JUnit cases=1 status='fail' with a failure child
S5  log carries ZERO subprocess.cpp findings; JUnit cases=1 status='run' with none
independent re-run at the fixed head: subprocess row PASS, 69 assertions in 12 cases, exit 0
```

## 7. Owed, unchanged by this review

Linux `nonzero_exit` remains owed on the fixed head and is correctly not claimed by the aggregate
subprocess receipt. The count-gate SHAPE finding stays routed and rides T1's stage-4 cells. Both
commits are LOCAL and UNPUBLISHED. The release hold is ABSOLUTE.
