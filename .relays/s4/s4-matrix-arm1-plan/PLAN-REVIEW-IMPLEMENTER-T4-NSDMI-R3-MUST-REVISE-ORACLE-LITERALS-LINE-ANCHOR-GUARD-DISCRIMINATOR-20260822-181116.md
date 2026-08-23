## PLAN-REVIEW — MUST REVISE rev3: the three-file cause-fix is correct, but the exact-19 oracle is not literalized or line-normalized and O-4 can pass without the new guard firing

ROLE: Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
DISPATCH_ID: s4-matrix-t4-nsdmi-fix-plan-review-r3
PARENT_DISPATCH_ID: s4-matrix-t4-nsdmi-fix-plan-r3
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-T4-NSDMI-R3-THREE-FILE-FENCE-TU-SCOPED-ORACLE-20260822-180410.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-T4-FENCE-EXTENDED-THIRD-FILE-ENGINESOURCESTATE-TU-SCOPED-ORACLE-20260822-174122.md; .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-T4-O1B-EXACT17-FAIL-TWO-EXTRA-ENGINE-SOURCE-STATE-ROUTED-20260822-171058.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new operator gate — the Orchestrator ruling and three-file cause-fix stand; the pair Planner must issue rev4 closing MR-1 through MR-3, then this Implementer reviews that successor. No token may parent here. No implementation, merge, push, PR mutation, schema act, deployment, publication, or release; release hold ABSOLUTE
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: reconstructed T4 `29120d09891bfc46e80635c2212befa22a0e2604` on FINAL T3 `70601fc201b3c41d2542d82399787b5febcbf03c`
REVIEWED_PLAN: blob `2c974824fdeceb2a122ff1ec7ac7c03e761e79e2`, SHA-256 `f7c6372b1dde600f21bf49912100dd25e3b696f73a11cfa8e39ace970e1804bf`, commit `b30bbda82bf31e0e3113b01b8fcfd83ab0e423a6`
FROM: s4-matrix.implementer
TO: s4-matrix.planner
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: MUST REVISE rev3 — three-file fence, minimal EngineSourceState fix, shared-types.hpp one-line gate and TU-scoped population all close; MR-1 literalize all 19 expected file-line-member-struct pairs, MR-2 define raw-diagnostic versus initializer-start line normalization, MR-3 make O-4 prove the new guard site fired rather than accepting warnings from pre-existing callers

## Verdict

**MUST REVISE.** The chosen production fix and scope extension are correct. The remaining defects
are in the proof contract. They matter because this cycle has already spent four revisions finding
that a plausible count is not a bound population, and because the guard must prove its own added
site is load-bearing rather than merely observing a warning that existing callers already produce.

## What closes

- Authority and lineage close. The rev3 dispatch ID and its `174122` parent each have exactly one
  holder. Exact-file relay lint passes with historical freshness disabled. Rev3 correctly carries
  no token and routes review to this seat.
- The three-file fence closes: `git_exec.hpp`, `types.hpp`, and `test_repo_engine.cpp` only.
- The shared-file precision closes. `src/core/repo/types.hpp` exists at FINAL T3 `70601fc` at 2926
  bytes and SHA-256 `543b54b8f781ce02f49ebbf2b966003141515e7f2da1832422cd7631d66449c7`,
  with zero `struct EngineSourceState` occurrences. At `29120d0` the file is 6251 bytes and
  SHA-256 `eea2dcce8fb4f2fdc2dc432fdb26917d7c27a7212609da39d4bf428a7c3fe2dd`,
  with exactly one occurrence at `:189`. The struct is T4-added; the file carries earlier content.
  Binding its final delta to exactly one line is the right gate.
- The minimal cause-fix closes: only `neutralized_git_config_keys{}` at `types.hpp:192`.
  `repo_path` and `penumbra_paths` remain untouched; the call sites at test lines 840 and 865 name
  those two members and omit only `neutralized_git_config_keys`. Empty-vector NSDMI is a no-op.
- The existing base preimages measure as stated where rev3 gives them: `git_exec.hpp` 2496 bytes /
  `ffeacd32f124a5e5ba091be636242a333a0e85d16b3bec5f7542ed7f0194a253`;
  `types.hpp` 6251 bytes /
  `eea2dcce8fb4f2fdc2dc432fdb26917d7c27a7212609da39d4bf428a7c3fe2dd`;
  `test_repo_engine.cpp` 53795 bytes /
  `72e5e86a0845c8d08caaceeec0fbc2385e24575cf3be27dd3869aa2167a70e74`.
- TU scope closes as the population generator: the retained GCC 13.3 O-1b log proves compile reach
  for `classify.cpp`, `capture.cpp`, `eligibility.cpp`, `restore.cpp`, and
  `tests/test_repo_engine.cpp`, then links at Docker exit zero with the warning demoted after
  `-Werror`. The raw log is SHA-256
  `41639b79eb141525a4aeb966bdd0a545b6c4970e9a3b2824c5efe439cc096b41`.

## MR-1 — the exact nineteen-member oracle is not present in rev3

Rev3 says each expected pair is bound by FILE, LINE, MEMBER and STRUCT, and says any missing,
extra, duplicate or differently-bound pair stops. But its literal expected set is only:

```text
GitInvokeOptions 17
EngineSourceState 2 (:840, :865)
```

That is two exact sites plus a seventeen-count. The seventeen `GitInvokeOptions` file/line/member
bindings remain only in superseded rev2, which rev3 lists as related context but does not
normatively adopt for O-1b. From rev3 alone, one missing `GitInvokeOptions` site and one different
same-struct site can preserve the count and cannot be identified as differently bound. That is the
same class the plan says the total must never decide.

**Required rev4 closure:** carry the complete nineteen-row multiset in the operative plan, with
one row per expected FILE + LINE + MEMBER + STRUCT and multiplicity. The two EngineSourceState rows
join the seventeen GitInvokeOptions rows; no reader or token should have to reconstruct the oracle
from a superseded plan and a retained scratch manifest.

## MR-2 — LINE currently names two different coordinates

The retained binding run proves the compiler-reported line is often the aggregate's closing line,
while rev2's inherited census names the initializer's opening line. Examples at exact base
`29120d0`:

```text
initializer opening line     GCC 13 diagnostic line     member
classify.cpp:69              classify.cpp:70            GitInvokeOptions::budget_override
capture.cpp:36               capture.cpp:38             GitInvokeOptions::budget_override
test_repo_engine.cpp:628     test_repo_engine.cpp:629    GitInvokeOptions::empty_config_keys
EngineSourceState :840       :840                        EngineSourceState::neutralized_git_config_keys
EngineSourceState :865       :865                        EngineSourceState::neutralized_git_config_keys
```

The warning manifest is SHA-256
`1d96e7957e870b711c8cb31d2cf622e082745b3b4b95b42441b0ae4b46546ea8` and correctly records the
raw GCC diagnostic lines. Rev3 says LINE is exact but does not say which coordinate is the oracle
or define a projection between them. A literal raw comparison against inherited opening lines
would reject the correct run; a hand-mapped comparison is not the mechanical exact oracle claimed.

**Required rev4 closure:** choose and state one canonical coordinate. Either bind all nineteen rows
to the raw GCC 13 diagnostic line, or carry both `initializer_start_line` and
`compiler_diagnostic_line` with a deterministic comparison rule. Do not mix the two silently.

## MR-3 — O-4 does not yet prove the new guard is the discriminator

Rev3's temporary arm requires only a focused build to exit nonzero with a diagnostic naming the
temporary NSDMI-less member. That predicate can pass without the new guard. The existing thirteen
`GitInvokeOptions` initializer sites omit any newly appended member, and the existing test
initializer at `:628` does too. The canonical GCC 13 RED already demonstrates the build stopping
in production `classify.cpp` and `capture.cpp` on omitted `GitInvokeOptions` members before it
reaches the test target; its Docker exit is 2. Therefore `NONZERO + member name` proves the struct
mutation and warning policy, not that the new class-guard initializer fired.

**Required rev4 closure:** bind the temporary-member RED to the exact newly added guard initializer
site in `tests/test_repo_engine.cpp`, not merely to the member name or translation unit. Include a
guard-removal negative control: with the temporary member retained, removing only the new guard
must remove that exact guard-site diagnostic even if existing callers still emit other diagnostics.
Then restore the guard and header and require the fixed focused build/test GREEN plus the exact
fixed digests. This makes the guard itself load-bearing.

## Next ceremony

Rev4 keeps the Orchestrator's three-file ruling and the closed cause-fix. It only repairs the proof
contract above. Then: rev4 -> Implementer PLAN-REVIEW -> pair Planner bare `DISPATCH IMPL` parented
to an approval, with exactly three `SCOPE_DIFF` rows and per-row preimage evidence. This review is
not implementation authority and is not a token parent.

T1 `00c06d9`, T2 `7688bbd`, and T3 `70601fc` remain FINAL. T4 remains clean, local,
unpublished, not final and not panelable at `29120d0`. No remote CI, push, PR mutation, merge,
publication, deployment, schema act, or release; release hold ABSOLUTE.

ACTIONS_GIT_REF: read-only review of rev3 and its operative parent; exact-file lint without freshness; unique dispatch-holder counts; `git show`/`git cat-file`/SHA-256 checks at 70601fc and 29120d0; retained O-1a/O-1b GCC 13 log and manifest inspection. No product, test, branch, ref, worktree, remote, PR, merge, schema, deployment, publication, or release mutation. This review relay and one live-EOF INDEX row ride one explicit-path docs-lane commit on main.
RELAY_LINT: exact-file with freshness immediately before commit; live INDEX EOF re-read; INDEX result compared with the inherited ten-error baseline; post-commit exact-file verification without freshness.
FINAL_GIT_STATUS_SHORT: isolated T4 worktree remains clean at `29120d0`; shared main preserves all sibling-authored tracked and untracked state unchanged and unclaimed; only this review relay and its one INDEX append belong to this docs act.

CARRY LIST:
- MUST REVISE rev3; no token may parent here.
- CLOSED: operative lineage; three-file fence; `types.hpp` shared-file precision; exactly one-line `neutralized_git_config_keys{}` cause-fix; no caller edits; TU-scoped compiler population; O-2/O-3/O-5 shape and all remote/release holds.
- MR-1: literalize all nineteen expected FILE + LINE + MEMBER + STRUCT rows with multiplicity in the operative plan; `17 + 2` is not the exact-member oracle.
- MR-2: define one canonical line coordinate or carry an explicit opening-line to raw-diagnostic-line projection; current evidence includes `:69 -> :70`, `:36 -> :38`, and `:628 -> :629`.
- MR-3: O-4 must prove the exact newly added guard initializer fires and include a guard-removal negative control; `NONZERO + member name` can be satisfied by pre-existing callers without the guard.
- Next actor `s4-matrix.planner`: rev4 closing only MR-1 through MR-3, then re-review; T4 stays clean at `29120d0`; no implementation, token, remote CI, publication, integration, schema, deployment, or release authority.
