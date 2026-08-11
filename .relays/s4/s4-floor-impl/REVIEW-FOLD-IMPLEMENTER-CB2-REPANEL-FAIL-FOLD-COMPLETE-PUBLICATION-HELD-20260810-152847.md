## REVIEW-FOLD — CB2 targeted re-panel failure fold complete at local B2 `2b5675a`; fresh delta review CLEAR; publication held by the token's explicit push exclusion

ROLE: Implementer
PHASE: REVIEW-FOLD
AUTHORITY: fold-in-only
DISPATCH_ID: s4-floor-impl-2-cb2-repanel-fail-fold-complete
PARENT_DISPATCH_ID: s4-floor-impl-2-cb2-repanel-fold
RUN_ID: s4
TASK_ID: B2
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — the operative token names `push` in Hard OUT even though its ceremony paragraph also says republish; the local reviewed head is ready, but ref mutation requires an unambiguous publication grant
DESIGN_LOCK_ID: m2-addendum11-422d451b-lock-20260810
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/IMPL-PLANNER-CB2-REPANEL-FAIL-FOLD-DISPATCH-IMPL-TOKEN-20260810-090631.md
FROM: s4-floor.implementer
TO: s4-floor.planner
CC: s4.orchestrator-planner, operator, s4.orchestrator-reviewer
SUBJECT: DONE_WITH_CONCERNS — F-1..F-6 and the re-panel-discovered writer establishment gap are folded in one clean local B2 commit at `2b5675a`; host and Ubuntu amd64 evidence is complete; fresh review CLEAR; PR publication held pending resolution of the token's explicit push exclusion

DONE_WITH_CONCERNS / REVIEW-FOLD FILED

The implementation and verification are complete. The concern is authority-only: this
token's Hard OUT list explicitly includes `push`, while its later ceremony paragraph says
to republish PR #22/#23 with explicit leases. I did not silently resolve that contradiction
in favor of external mutation. C and both remote draft PR refs remain unchanged; B2 is
ready locally for a narrowly authorized guarded publication.

## Final local topology and scope

- C remains byte-identical at `b8083be8529a97d1d3d5931a2c7b308335bbd09c`.
- B2 is one commit directly atop exact C at
  `2b5675a49e9c7d990c36d904c5f6bc2de4a5f60b`.
- The preserved B2 subject is `feat(pack): collect torn tails and staged sidecars`.
- The cumulative C-to-B2 range is 17 tracked paths; `.github/**` is absent from the diff.
- The implementation worktree is clean; `git diff --check` passes; the one-commit law
  passes.

The scope was written before edits and contains every touched tracked path:

FOLD_SCOPE:
- src/adapters/claude_code/claude_code.cpp -> in
- src/adapters/codex/codex.cpp -> in
- src/adapters/claude_code/install.cpp -> in
- src/adapters/codex/install.cpp -> in
- harness/bivharness/e3.py -> in
- tests/test_pack.cpp -> in
- tests/test_adapter_claude_install.cpp -> in
- tests/test_adapter_codex_install.cpp -> in

FOLD_SCOPE_RESULT: all-in

The post-review writer establishment change remained inside
the already declared Claude install/test paths. Hard exclusions remain untouched:
`rewrite_common.cpp:982`, the ADDENDUM-11 PRESENT-membership formula, R-b destination
filenames, sealed A9 shape, `.github/**`, merge, and release.

## F-1 through F-6 disposition

- F-1: Claude `{}` subagent content survives consent-NO staging and repack. A legally
  absent body identity is accepted.
- F-2: id-less staged main transcripts round-trip in Claude and Codex; Codex child
  identity absence is aligned symmetrically.
- F-3: a staged row missing body-version evidence is skipped with a row-scoped warning;
  it does not kill its sibling or the other adapter.
- F-4: the Claude all-record union now harvests child aliases from a non-staged,
  version-refused row.
- F-5: the Codex all-record union now includes artifact-derived child identities from a
  staged, version-refused row.
- F-6: the round-trip and missing-version falsifiers prove the blast radius is confined;
  unrelated sessions and the other adapter survive.

Present-and-mismatched identities remain typed refusals in both staged readers.

The first targeted review correctly found one remaining writer-to-reader same-set hole:
Claude consent-NO could rewrite a child-origin `sessionId` to the minted child and stage
it even though the reader requires the minted parent. The writer now checks rewritten
main and `subagents/*.jsonl` content before publication: absence remains legal, but a
present non-parent identity refuses only that row as
`containment_refused` / `staged_identity_mismatch`, clears its outputs, and preserves a
clean sibling. No staged sidecar row or ID-map entry is emitted for the refused row.

## RED/GREEN and A3 receipts

- Initial five-case `F-*` RED: all five cases failed before the fold, 335 assertions.
- Initial fold GREEN: the same five cases passed, 335 assertions.
- Review regression RED: the hostile writer-establishment row produced four expected
  failures out of 14 assertions before the writer guard.
- Final `F-*` GREEN: six cases, 349 assertions passed.
- Final writer-establishment regression: 14 assertions passed; hostile row refused,
  clean sibling staged alone.
- Fresh adversarial delta review at exact `2b5675a` returned CLEAR with no findings. It
  independently reran the six-case F cohort, the new regression, the empty-subagent
  round trip, and ordinary consent-NO staging.

A3 recaptured both anchored collectors at their final bytes:

- Claude: `a68f0276e1bcf72f82d9daf421f227a700c71ce0aa52a710860c7f55d615f009`
- Codex: `b3c2c42a8c9ce8c758d45bd0d7b2988cbdefbb7e138fef4972cf76e8ec399e44`

Both hashes match `harness/bivharness/e3.py`. The anchor-side diff is exactly two
replacements. Eleven final-head controls passed: nine read-side mutation arms, the
pinned-source control, and the unchanged write-side exclusion control.

## Final host verification

At exact `2b5675a` on macOS:

- configure and build passed;
- `biv_tests` passed in 319.18 seconds;
- open-no-rewrite, adapter purity, version-floor mirror, errno, probe schema, generated
  envelope, harness-selftest, harness-E2, and Werror passed;
- harness-E2 passed in 179.23 seconds;
- ASan/UBSan, tidy/analyzer, and fuzz smoke were preset-configured skips;
- the sole selected failure was the disclosed platform prerequisite
  `readelf unavailable` in `safety-hardening`; the Linux run below passes that gate.

## Final Ubuntu 24.04 linux/amd64 Docker parity

A fresh detached clone of exact `2b5675a` ran in disposable `ubuntu:24.04` under
`--platform linux/amd64`. It verified x86_64, Python 3.12.3, GNU 13.3.0, and all eight
immutable LLVM 22.1.8 amd64 package hashes, package names, versions, and architectures.
No GitHub Actions run or check inspection was used.

Canonical results:

- configure/build and core-adapter purity: PASS;
- product: 340/341 cases and 9,358/9,359 assertions passed; the only failure was the
  registered Rosetta invalid-executable spawn-semantic case;
- harness: 968 passed, three registered Docker filesystem-mutation sentinels failed,
  four skipped;
- E2: PASS;
- Werror: PASS;
- LLVM 22 tidy: PASS in 44.88 seconds;
- hardening: PASS;
- schema/probe gates: PASS;
- generated-envelope CTest row was dependency-blocked by the registered product
  exception; direct schema validation passed.

Bounded controls passed:

- product excluding only the registered Rosetta case: 340/340;
- harness excluding exactly the four registered Docker filesystem sentinels: 967 passed,
  four skipped, four deselected;
- generated-envelope direct schema validation: PASS.

Configured Linux skips remained ASan/UBSan and fuzz smoke. No unrelated Docker resource
was pruned or removed.

## Merge-tree, remote, and publication hold

- Current remote `main`: `8981bfd0848039d533d9bb2a96301d4d81b564fa`.
- `origin/main` to exact C merge tree: `64d77cdeade243f7da001402a19212ef5d5d73d1`.
- Exact C to local B2 merge tree: `86058893045a2eb0c085cb136aaac953eea63ec4`.
- PR #22 remains OPEN/DRAFT at exact C `b8083be`.
- PR #23 remains OPEN/DRAFT at remote B2 `20e56bc`.
- No branch push, PR-body mutation, GitHub Actions invocation/inspection, undraft, merge,
  deployment, seal, or release occurred.

Requested next action: issue an unambiguous guarded-publication token for B2 (expected
lease `20e56bc4053d4a27c4b47b6dbff0fc02af1dcc13`) or explicitly rule that this token's
ceremony sentence overrides its Hard OUT `push` entry. C needs no ref update.

C must never land without B2 (the A10.3 stacking observation).

The release hold is ABSOLUTE.

ACTIONS_GIT_REF: local product head `2b5675a49e9c7d990c36d904c5f6bc2de4a5f60b`; remote B2 intentionally held at `20e56bc4053d4a27c4b47b6dbff0fc02af1dcc13`; this report and its append-only INDEX row are the only docs-lane writes from this filing
FINAL_GIT_STATUS_SHORT: product worktree clean; shared docs checkout retains pre-existing sibling INDEX/untracked state, preserved; this filing adds only the named report and its INDEX row

CARRY LIST:
- `.relays/s4/s4-floor-impl/REVIEW-FOLD-IMPLEMENTER-CB2-REPANEL-FAIL-FOLD-COMPLETE-PUBLICATION-HELD-20260810-152847.md` -> `s4-floor.planner`
- local B2 `2b5675a` over byte-identical C `b8083be`; F-1..F-6 plus writer establishment closed; fresh review CLEAR
- publication held solely on explicit push-authority contradiction; guarded B2 lease named; PR #22/#23 remain draft/open; Actions untouched
- C must never land without B2 (the A10.3 stacking observation); release hold ABSOLUTE
