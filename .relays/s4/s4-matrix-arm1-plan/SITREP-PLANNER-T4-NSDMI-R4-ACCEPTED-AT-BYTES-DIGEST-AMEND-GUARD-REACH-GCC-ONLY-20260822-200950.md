## ADJUDICATION — T4 rev4 ACCEPTED at the bytes: every obligation re-verified independently at my seat; two things the report does not say, one a truncated digest and one a guard-reach limit I measured myself

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-matrix-t4-nsdmi-r4-adjudication
PARENT_DISPATCH_ID: s4-matrix-t4-nsdmi-fix-complete-r4
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-T4-NSDMI-R4-O1-O5-COMPLETE-GUARD-LINE-142-20260822-195729.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/IMPL-PLANNER-T4-NSDMI-R4-GUARD-DISPATCH-NINETEEN-ROW-ORACLE-20260822-190215.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: two asks, to two addressees. `s4-matrix.implementer` files a wording/record-only amendment closing A-1 (D-2 cadence: amend+classify, then my concur+lock). `s4.orchestrator-planner` convenes the T4 Stage-3 panel on candidate `6ba01ef92ef5052b317f6210fa202d5577e1e6c1` once A-1 lands, and rules where A-2 is registered. Neither ask moves the candidate. No merge, push, PR mutation, remote CI, schema act, publication, deployment, or release. The release hold is ABSOLUTE
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: authorized pre-edit T4 `29120d09891bfc46e80635c2212befa22a0e2604` on FINAL T3 `70601fc201b3c41d2542d82399787b5febcbf03c`
CANDIDATE: local T4 `6ba01ef92ef5052b317f6210fa202d5577e1e6c1` — verified, unpublished, unchanged by this relay
FROM: s4-matrix.planner
TO: s4-matrix.implementer, s4.orchestrator-planner
CC: operator, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: T4 rev4 ACCEPTED — candidate 6ba01ef re-verified at the bytes at my seat including the exact O-5 removal proof; A-1 the git_exec.hpp digest in report section 1 is 63 hex characters and can never match, record-only amendment required before panel; A-2 I measured the guard silent under the project's actual macOS flags, so its reach is GCC-only and must be disclosed rather than inferred

## 1. Accepted, and re-measured rather than read

I did not adjudicate this from the report's numbers. Every load-bearing claim below was
re-derived at my seat against the candidate and base objects.

```text
candidate parent            29120d0…  EXACT, direct, single parent
changed paths               3  (git_exec.hpp, types.hpp, test_repo_engine.cpp) and nothing else
numstat                     2/2 + 1/1 + 7/0  = 10 insertions, 3 deletions  MATCHES the report
types.hpp delta             exactly one line — the O-5 one-line gate holds
four repo callers           byte-identical by BLOB identity, not by digest transcription
                            classify 49c2bdaa…, capture 01d3b365…, eligibility b9773f59…,
                            restore c0583b57…
publication                 no remote ref contains 6ba01ef; local branch s4-matrix/arm1-t4 only
```

**The O-5 removal proof is the strongest thing in this candidate and it reproduces exactly.**
Deleting candidate lines 141–147 from `tests/test_repo_engine.cpp` yields SHA-256
`72e5e86a0845c8d08caaceeec0fbc2385e24575cf3be27dd3869aa2167a70e74`, which is the base file
byte-for-byte. That single measurement proves in one stroke that all thirteen pre-existing
`GitInvokeOptions` initializers and both `EngineSourceState` sites at base `:840`/`:865` are
untouched — a stronger statement than any per-site enumeration, because it admits no gap.

The fix is the minimal one that was authorized and is visibly a no-op: `budget_override{}`,
`empty_config_keys{}`, `neutralized_git_config_keys{}`, with `repo_path` and `penumbra_paths`
untouched and belonging to m-1's enlarged R-4.41.

`GUARD_LINE = 142` is confirmed: the guard's initializer is a single-line aggregate at candidate
line 142, so opening and closing coincide there and the raw-diagnostic coordinate is unambiguous
at that site. The guard was written test-first and failed on both members before any production
byte moved, which is the right order.

**R-4.35 is a read registry, not a cited one.** I checked rather than accepting the label: the
rows are real at `pdc/master/RESIDUALS.md:2303`, and both
`test_c1_zero_session_control_reds_on_file_inserted_at_scandir_stop` and
`test_credential_scanner_detects_entry_added_after_directory_enumeration` are named in them.
The classification holds and the Linux harness aggregate is correctly NOT claimed green.

## 2. A-1 — the `git_exec.hpp` digest in section 1 is not a SHA-256

```text
report section 1   523e13186cb4bc7d9e6eb12b0a64ea0f56c8c6819068b30f3fc54c4052d87f0    63 chars
measured           523e13186cb4bc7d9e6eb12b0a64ea0f56c8c6819068b30f3fc54c4052d87f0a   64 chars
```

One trailing character is missing. The other two digests are correct at 64 characters and match
the objects exactly, and the file CONTENT is right — this is transcription, not product.

It still has to be fixed before the panel, because O-4d discharges by asserting the three files
"returned to the fixed digests in section 1," and a 63-character string can never match the
output of any hash function. A gate whose reference value cannot be produced does not pass; it
fails to run. The panel will bind these digests, so the record must be exact first.

**A-1 is record-only and does not move `6ba01ef`.** D-2 cadence: amend and classify, then I
concur and lock.

## 3. A-2 — I measured the guard's reach, and it is GCC-only

This is not in the report and it is not a criticism of the implementation: the plan pinned GCC 13
as the oracle environment and the implementer met that exactly. But a reader meeting the words
"class guard" beside "macOS 14/14 green" will infer protection on both platforms, and that
inference is wrong.

I compiled the real `git_exec.hpp` — base and candidate — against the guard's own initializer
shape on this host:

```text
Apple clang 17.0.0, -Wall -Wextra, BASE header (no NSDMIs)        0 diagnostics
Apple clang 17.0.0, -Wall -Wextra, CANDIDATE header               0 diagnostics
```

My first run was exactly that pair, and I discarded it: a must-be-RED case that comes back green
is a dead instrument, and reporting a product conclusion from it would have been the defect this
lane has spent the cycle naming. Diagnosing it gave the real finding. Apple clang does not fold
this class into `-Wextra` for designated initializers; it needs a separate flag:

```text
+ -Wmissing-designated-field-initializers, BASE header       warning: missing field
                                                             'budget_override' initializer
+ -Wmissing-designated-field-initializers, CANDIDATE header  0 diagnostics
```

Now the instrument separates, and it independently confirms the fix on a second compiler and a
second platform. It also establishes the limit: **the project passes that flag nowhere** — no
occurrence in `CMakeLists.txt`, `cmake/`, or `.github/workflows/`. So on the macOS leg the guard
is silent. A future NSDMI-less member added to `GitInvokeOptions` would be caught by the Linux
GCC leg and would sail through a macOS-only run.

Two consequences worth carrying:

- The guard is real protection, correctly scoped to where it was proven, and it is **the Linux
  leg that carries it**. This is another instance of the standing rule that a leg is not
  redundant because its headline count duplicates another's.
- Clang emitted **one** diagnostic where GCC 13 emits **two** at the same site. The per-member
  multiplicity in the nineteen-row oracle is therefore a GCC 13 property, not a portable one.
  Anyone porting that oracle to another compiler must re-derive it, not translate it.

A-2 needs no code change and I am not folding it into this candidate. It needs disclosure to the
panel and a ruling on where it is registered — RESIDUALS is master's to write, so I route the
registration question up rather than asserting a row.

## 4. Honest weight of O-1b

O-1b matched the nineteen rows exactly. Stated precisely: that oracle was transcribed FROM the
retained manifest of the earlier binding run at the same base, so the match is a
**reproducibility and closure** result, not an independent discovery. Its value is real and it is
specifically this — the population is stable across containers, and the closure STOP on any
struct outside the two did not fire, which is the arm that could have surprised us. I would
rather say that plainly than let a re-derivation read as a second witness.

## 5. Disposition

T4 is IMPLEMENTED at `6ba01ef` and is **not yet panelable** — A-1 lands first so the panel binds
a correct record. The candidate does not move for either finding.

T1 `00c06d9`, T2 `7688bbd`, T3 `70601fc` remain FINAL. R-4.38 binary inventory and the stage-5
merge-readiness report remain my obligations. Merge is not push and neither is release; the
release hold is ABSOLUTE.

ACTIONS_GIT_REF: none — no edits made at this seat; no product, test, branch, ref or worktree moved, and `6ba01ef` is untouched by this relay. Read-only at my seat: `git log`/`git diff --numstat`/`--name-status`/`--name-only` across base and candidate; blob-identity comparison of the four repo callers; `git cat-file -s` and `git show | shasum -a 256` digests; the O-5 line-141-to-147 strip reproducing the base file digest; `git branch -r --contains` for publication state; a grep of `pdc/master/RESIDUALS.md` confirming the R-4.35 rows and both named tests; and syntax-only Apple clang 17 compiles of the base and candidate headers in a scratch directory outside the worktree, run in both directions until the instrument separated. No merge, push, PR mutation, or remote CI. Docs lane: this relay and its INDEX row ride ONE explicit-path commit.
FINAL_GIT_STATUS_SHORT: this relay and its INDEX row are this seat's only working-tree delta at commit time; `git status --porcelain` over `harness/`, `src/`, `tests/`, `CMakeLists.txt` is empty; the shared checkout carries sibling-authored untracked paths, preserved and unclaimed
RELAY_LINT: all three arms before commit — exact-file WITH freshness; `--index` error set path-normalized and diffed against the pre-append blob; `--relay-root` run with this relay present AND moved aside, requiring identical error sets. `substantive_actions_ref` and `implementation_work_claimed` measured False on the finished bytes with a positive control; `operational_token_text` carries no bare token.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/SITREP-PLANNER-T4-NSDMI-R4-ACCEPTED-AT-BYTES-DIGEST-AMEND-GUARD-REACH-GCC-ONLY-20260822-200950.md` → TO `s4-matrix.implementer`, `s4.orchestrator-planner`
- T4 rev4 ACCEPTED at candidate `6ba01ef92ef5052b317f6210fa202d5577e1e6c1`, re-measured at my seat and not adjudicated from the report's numbers: direct single parent `29120d0`, exactly three changed paths and nothing else, numstat 2/2 + 1/1 + 7/0 matching the claimed 10 insertions and 3 deletions, the `types.hpp` delta EXACTLY ONE LINE, the four repo callers byte-identical BY BLOB IDENTITY (classify `49c2bdaa`, capture `01d3b365`, eligibility `b9773f59`, restore `c0583b57`), and no remote ref containing the candidate
- THE O-5 REMOVAL PROOF REPRODUCES EXACTLY and is the strongest artifact here: stripping candidate lines 141–147 yields SHA-256 `72e5e86a0845c8d08caaceeec0fbc2385e24575cf3be27dd3869aa2167a70e74`, the base file byte-for-byte, proving in ONE measurement that all thirteen pre-existing `GitInvokeOptions` initializers and both `EngineSourceState` sites are untouched — stronger than a per-site enumeration because it admits no gap. `GUARD_LINE = 142` confirmed as a single-line aggregate where opening and closing coincide; guard written test-first, failing on both members before any production byte moved
- R-4.35 IS A READ REGISTRY, NOT A CITED ONE: rows verified real at `pdc/master/RESIDUALS.md:2303` with both `test_c1_zero_session_control_reds_on_file_inserted_at_scandir_stop` and `test_credential_scanner_detects_entry_added_after_directory_enumeration` named; classification holds and the Linux harness aggregate is correctly NOT claimed green
- A-1 RECORD DEFECT, AMENDMENT REQUIRED BEFORE PANEL: report section 1's `git_exec.hpp` digest is `523e13186cb4bc7d9e6eb12b0a64ea0f56c8c6819068b30f3fc54c4052d87f0` at 63 hex characters; measured is `523e13186cb4bc7d9e6eb12b0a64ea0f56c8c6819068b30f3fc54c4052d87f0a` at 64. Content is correct and this is transcription, NOT product — but O-4d discharges by asserting the files "returned to the fixed digests in section 1", and a 63-character string can never be the output of any hash function, so that gate does not pass, it fails to RUN. Record-only, does not move `6ba01ef`; D-2 cadence amend+classify then my concur+lock
- A-2 GUARD REACH IS GCC-ONLY, MEASURED AT MY SEAT AND ABSENT FROM THE REPORT: under Apple clang 17 with `-Wall -Wextra` BOTH base and candidate headers give ZERO diagnostics. **I discarded that first run** — a must-be-RED case returning green is a dead instrument, and a product conclusion drawn from it would be this cycle's own named defect. Diagnosing it produced the finding: clang needs the separate `-Wmissing-designated-field-initializers`, under which BASE warns and CANDIDATE is silent, independently confirming the fix on a second compiler AND platform. **The project passes that flag NOWHERE** (`CMakeLists.txt`, `cmake/`, `.github/workflows/`), so the guard is silent on the macOS leg and a future NSDMI-less member would sail through a macOS-only run. THE LINUX LEG CARRIES THIS GUARD — another instance of a leg not being redundant because its headline count duplicates another's. Also: clang emits ONE diagnostic where GCC 13 emits TWO at the same site, so the nineteen-row per-member multiplicity is a GCC 13 property and must be RE-DERIVED, never translated, if ported. No code change; disclosure to the panel plus an orchestrator ruling on registration, since RESIDUALS is master's to write
- HONEST WEIGHT OF O-1b: the oracle was transcribed FROM the retained manifest of the earlier run at the same base, so an exact match is REPRODUCIBILITY AND CLOSURE, not independent discovery. Its real value is that the population is stable across containers and the closure STOP on any struct outside the two did not fire — the arm that could have surprised us. A re-derivation must not be allowed to read as a second witness
- DISPOSITION: T4 IMPLEMENTED at `6ba01ef` and NOT YET PANELABLE — A-1 lands first so the panel binds a correct record; the candidate moves for neither finding. `s4-matrix.implementer` files the A-1 amendment; `s4.orchestrator-planner` convenes the Stage-3 panel on `6ba01ef` after it lands and rules where A-2 registers. T1 `00c06d9` / T2 `7688bbd` / T3 `70601fc` FINAL; R-4.38 inventory and the stage-5 merge-readiness report remain mine; no remote CI, push, PR mutation, merge, publication, deployment or release; release hold ABSOLUTE
