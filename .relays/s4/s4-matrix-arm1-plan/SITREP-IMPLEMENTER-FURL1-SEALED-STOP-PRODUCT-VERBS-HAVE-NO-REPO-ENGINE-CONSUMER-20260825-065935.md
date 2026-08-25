## SITREP — F-URL-1 implementation STOP: the sealed A6 E2 CLI legs require product repo-engine consumers that do not exist at base and cannot be added inside the fifteen-path fence

ROLE: Implementer
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-matrix-furl1-product-consumer-gap-stop
PARENT_DISPATCH_ID: s4-matrix-furl1-corrective-impl-token
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/IMPL-PLANNER-FURL1-CORRECTIVE-TOKEN-SEALED-M-A6-FIFTEEN-PATHS-20260825-063107.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-FURL1-CORRECTIVE-R2-FOOTER-MEASURED-CARRY-SELF-ROUTED-20260825-061535.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
DESIGN_DOC_ID: m3-addendum-6-20260824
DESIGN_RECORD_KIND: audit-record
DESIGN_LOCK_ID: m3-addendum-6-ae7ca0b2-lock-20260825
LOCKED_DESIGN_SHA256: ae7ca0b24a85d296e12ade58219dc651e95f10191684c421c3f2a5a87473c883
POST_STAMP_SHA256: 9d2a915c874ce5fa90902868610ae98bdf64f7b1b3607447a77f366b0733f295
CONSUMED_CONTRACT: m1-addendum-M-20260823 (4a61da224cce34a6084a4a6a39b231c98c325b5bdc671d28d70add52a43913e9)
SECOND_CONSUMED_CONTRACT: m4-sr-url-family-20260823 (a2f777c2311ab04283992b24f5fba766c6ba8c66ef8bcf6bc88f7b48f88f7798)
HUMAN_GATE_REQUIRED: yes — the owning planners must rule the missing product-integration seam or issue a widened, reviewed fence before implementation resumes; this relay grants no edit, commit, test continuation, merge, push, PR mutation, remote CI, publication, deployment, or release act
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: T4 `6ba01ef92ef5052b317f6210fa202d5577e1e6c1` on FINAL T3 `70601fc201b3c41d2542d82399787b5febcbf03c`
FROM: s4-matrix.implementer
TO: s4-matrix.planner, s4.orchestrator-planner
CC: operator, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer, m-1.planner, m-3.planner, m-4.planner
SUBJECT: The sealed A6 E2 legs require real biv pack/open divergence behavior, but at the exact authorized base neither product verb consumes run_eligibility, repo capture, or restore_entry and manifest parsing requires repos to be empty; all consumers are test-only, while the integration paths needed to create real CLI divergence are outside the fifteen-path fence, so execution-not-amendment STOPs before A6 implementation and requests an owning-seat ruling

The token, its approving review, all three sealed documents, and every one of the fifteen
candidate preimages were independently verified before editing. The token is uniquely addressed
to this seat and carries exactly one live `DISPATCH IMPL`. The macOS baseline built and passed the
six canonical named rows at the untouched base: `biv_tests`, `errno_table_gate`,
`generated_envelope_conforms`, `harness-selftest`, `harness-e2`, and the remaining selected
canonical row, 6/6 in 629.81 seconds.

## The sealed STOP

M's engine seam is implementable inside the fence. A6's required E2 surface is not. A6 legs
`a6.1` through `a6.13` and `a6.16` require actual `biv pack` and `biv open` invocations to reach
network-class repository operations so the CLI hook, prompts/notices/refusals, envelope carriers,
exit composition, and cross-run non-persistence are observed end to end.

At base `6ba01ef`, exact-source searches establish:

1. `run_eligibility` has a declaration and definition under `src/core/repo`, but no production
   caller. Every call is in `tests/test_repo_engine.cpp`.
2. `restore_entry` has a declaration and definition under `src/core/repo`, but no production
   caller. Every call is in `tests/test_repo_engine.cpp`.
3. No production `pack`, `open`, CLI, or manifest path calls `repo::capture` or otherwise
   orchestrates the repository engine.
4. `src/core/manifest/manifest.cpp` at the base still parses `repos` through
   `require_empty_array(object, "repos")`; the live product format cannot carry the repository
   population needed by the open-side A6 fixtures.

Therefore adding the hook and renderers only in `src/cli/main.cpp` would produce unreachable
surfaces, not the sealed E2 behavior. Manufacturing a CLI-only synthetic trigger would invent an
unenumerated mechanism and violate A6-R7(4), V-A6-3, and the E2 fixture contract. Connecting the
real verbs requires product orchestration and format paths outside the token's fifteen IN rows,
including at minimum currently out-of-fence `src/core/pack/**`, `src/core/open/**`, and/or
`src/core/manifest/**` loci. M-R7(4) and the generalized execution-not-amendment rule therefore
fire: a structurally absent path is a redesign/scope ruling, never permission to keyboard around
the gap.

## Work performed before discovery, frozen uncommitted

The first TDD slice was created only within six authorized paths:

```text
src/core/repo/git_exec.hpp
src/core/repo/git_exec.cpp
src/core/repo/types.hpp
src/core/repo/eligibility.cpp
src/core/repo/restore.cpp
tests/test_repo_engine.cpp
```

It adds the typed endpoint carrier, central same-context resolution/check, the sealed narrow
comparator, run-scoped hook/memo, absent-hook refusal, and carrier population at the four known
network sites. The initial focused build RED exactly on the absent carrier/comparator/hook/kind
API. After implementation, four focused engine cases pass independently: 7 assertions for
zero/many carrier fail-closed, 11 for the comparator boundary, 8 for absent-hook refusal before
network spawn, and 11 for one-decision-per-triple memo behavior. `git diff --check` is clean.

No completion is claimed. The broader repo-engine binary correctly exposed that legacy local-path
fixtures are unparseable endpoints and now require explicit test-hook consent; that test adaptation
was not continued after the product-consumer STOP was identified. No partial commit exists, which
preserves A6-R1's one-commit obligation if the owning seats authorize a successor path.

## Ruling requested

Please route this to the owning m-1/m-3 design seats and return one reviewed, explicit disposition:

- identify an existing in-fence production consumer at `6ba01ef` that the evidence above missed;
- authorize and design the missing product repository-engine integration with an explicit widened
  path fence and sequencing; or
- re-cut the E2 obligation if the sealed A6 CLI fixtures were intended for a later integration act.

The lower-level Implementer cannot select among those arms. Candidate work is frozen at the base
plus the six-path uncommitted TDD slice. No schema, exit-map, CLI, help, or selftest-pin edit was
made; no one-commit candidate was formed; Linux was not started because the pre-stated STOP fired
before the next obligation. No remote CI, push, merge, PR mutation, publication, deployment, or
release occurred. The release hold is ABSOLUTE.

ACTIONS_GIT_REF: no ref moved; candidate branch remains at `6ba01ef92ef5052b317f6210fa202d5577e1e6c1` with six authorized-path uncommitted files frozen; read-only base consumer census plus focused local macOS build/tests only; no Linux continuation, remote CI, push, merge, PR mutation, publication, deployment, or release. Docs lane: this report-only relay and one live-EOF INDEX row only, explicit-path commit after lint.
FINAL_GIT_STATUS_SHORT: candidate has exactly six modified authorized paths and no untracked files; shared main retains all pre-existing sibling-authored untracked artifacts unchanged, with only this relay and its INDEX row attributable to this filing
RELAY_LINT: initial exact-file lint passed before INDEX append; its first final rerun caught the draft filename outside the two-minute freshness window, so the unfiled draft was restamped to the real current time; final exact-file freshness OK after that correction. The full INDEX arm reports 222 inherited non-monotonic-history errors and no error at the new EOF row; inherited history disclosed and not repaired. Separate explicit-path docs commit follows these gates

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-FURL1-SEALED-STOP-PRODUCT-VERBS-HAVE-NO-REPO-ENGINE-CONSUMER-20260825-065935.md` -> `s4-matrix.planner`, `s4.orchestrator-planner`
- token, approving review, all three sealed hashes, and all fifteen base preimages independently MATCH before edits; macOS base canonical selection 6/6 green
- exact base gap: production defines but never calls `run_eligibility` or `restore_entry`, has no product `repo::capture` consumer, and manifest parsing requires an empty `repos` array; every engine consumer is test-only
- sealed consequence: real pack/open A6 E2 divergence cannot be produced inside the fifteen-path fence; unreachable renderer code or a synthetic CLI trigger is not acceptable evidence and would violate the closed taxonomy
- six-path engine TDD slice frozen uncommitted at base; four focused cases green with 37 assertions; broader fixture adaptation and every later obligation stopped; no partial commit, preserving the one-commit rule
- requested ruling: identify a missed in-fence consumer, widen and design the product integration, or re-cut the E2 timing; no merge, push, PR mutation, remote CI, publication, deployment, or release; release hold ABSOLUTE
