## SITREP — post-R-4.8 restack stopped before publication: the dispatched five-file FRESH premise is false; two clean-merge carrier overlaps are also FRESH

ROLE: Implementer
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-floor-impl-2-cb2-restack-post-r48-blocked-unlisted-fresh
PARENT_DISPATCH_ID: s4-floor-impl-2-cb2-restack-post-r48
RUN_ID: s4
TASK_ID: B2
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — planner must widen the fresh-review/scope premise to include the two inherited R-4.8 carrier overlaps or provide another explicit disposition; no suite, review, or publication proceeds under the contradictory five-file rule
DESIGN_LOCK_ID: m2-addendum11-422d451b-lock-20260810
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/IMPL-PLANNER-CB2-RESTACK-ONTO-POST-R48-ORIGIN-MAIN-DISPATCH-IMPL-TOKEN-20260810-235910.md
RELATED_CONTEXT: docs/sprints/2026-08-04-s4-step4/reviews/2026-08-10-s4-floor-cb2-endstate-baseline-3762f37-PANELED.md; .relays/s4/s4-floor-impl/REVIEW-FOLD-SCOPE-IMPLEMENTER-CB2-RESTACK-POST-R48-20260811-001434.md
FROM: s4-floor.implementer
TO: s4-floor.planner
CC: s4.orchestrator-planner, operator, s4.orchestrator-reviewer, m-2.planner
SUBJECT: BLOCKED AT CARRY GATE — local C f03ce70 and B2 fd857f1 are clean one-commit candidates, but the full baseline lookup is 27 CARRY / 7 FRESH, not 29/5; adapter.hpp and pack.cpp are unlisted, legitimate R-4.8+B2 clean-merge unions

BLOCKED / NO PUBLICATION

The sequential replay itself completed without a product-semantics choice:

- local C f03ce70ccb50e7b0946929653f7f9bafecc9cfac is one commit directly on
  38a4702bdc6c0fe82a102ebf58977ca7ad67623a, subject preserved as
  'feat(open): stage consent-no sessions with provenance sidecar';
- local B2 fd857f124b8e60d982fc341a563bab99317b0850 is one commit directly on
  the new C, subject preserved as
  'feat(pack): collect torn tails and staged sidecars';
- both linked worktrees are clean.

The required full 34-row hash lookup then triggered the dispatch's explicit stop
condition. It measured **27 CARRY / 7 FRESH**, not five FRESH. The named five conflict
files are fresh as expected, but two additional paneled-union files are fresh:

FOLD_SCOPE:
- src/core/open/sessions.cpp -> in
- tests/test_adapter_claude_install.cpp -> in
- tests/test_adapter_codex_install.cpp -> in
- tests/test_pack.cpp -> in
- tests/test_sessions.cpp -> in
- src/adapters/adapter.hpp -> OUT
- src/core/pack/pack.cpp -> OUT
- .git/refs/remotes/origin/s4-floor/c-consent-no-carrier -> in
- .git/refs/remotes/origin/s4-floor/b2-torn-tail -> in
FOLD_SCOPE_RESULT: deviation-present

The OUT rows were not manually resolved or amended. They are clean-merge overlaps:
both R-4.8 and the paneled pair touch these files, and Git combined their non-conflicting
hunks while replaying the authorized commits.

## Exact byte evidence

src/adapters/adapter.hpp:

- paneled B2 baseline: 1c96d3ac7b86b7836296475b2da3d6fd07b1806a70268a5a9981f237b713fcb4;
- new B2: 5516233907859e8915170ecea782f08074a355c230bf737d5a4359b6c1519f29;
- R-4.8 changed this file by 47 insertions / 4 deletions relative to its first
  parent; old-B2 to new-B2 adds the surviving InstallTarget::packer_home carrier line.

src/core/pack/pack.cpp:

- paneled B2 baseline: 0f5cabfd755eea473e76c047c4ad47d1b0f7127de1da3f95d550731b85a1ea33;
- new B2: 1a97083f6944718a86f90883959b4a969b1fbc082a22833fcb3bec7304d66779;
- R-4.8 changed this file by 67 insertions / 2 deletions relative to its first
  parent; old-B2 to new-B2 adds six carrier lines (packer_home_carrier() and the
  manifest .packer_home assignment).

Restoring either file to its 3762f37 hash would delete landed R-4.8 carrier behavior.
Keeping the correct union violates the token's literal rule that every unlisted file
must remain byte-identical to 3762f37. That is a scope/acceptance contradiction and
cannot be self-waived by this seat.

## What did complete before the stop

The five true conflicts were separable without product judgment:

- src/core/open/sessions.cpp: R-4.8 capability/packer-home target shape and C's
  per-agent consent flow both survive;
- tests/test_adapter_codex_install.cpp: R-4.8 packer-home byte-identity and C
  consent-NO staging/unwritable-workspace cases survive;
- tests/test_sessions.cpp: R-4.8 packer-home transport cases and C staged
  outcome/sidecar cases survive;
- tests/test_adapter_claude_install.cpp: R-4.8 packer-home byte-identity and
  B2 escaped-value/origin-key plus child identity-map cases survive;
- tests/test_pack.cpp: R-4.8 isolated pack-discovery helpers and B2 staging
  helpers plus the full three-shape stage-pack-open acceptance case survive.

The implementation agent's focused build/run completed before the controller's carry
stop: build succeeded and 1,089 assertions in 11 cases passed. This is supporting E2,
not the owed full-suite proof. The controller independently verified:

- git merge-tree --write-tree --name-only origin/main f03ce70... exit 0;
- git merge-tree --write-tree --name-only origin/main fd857f1... exit 0;
- git merge-base --is-ancestor 38a4702 f03ce70... exit 0;
- cut-point blast radius git rev-list --count origin/main..fd857f1^ = 1;
- both commit-range git diff --check invocations pass;
- .pending-r415, child_alias_ids, and child_identity_shape are absent.

A3 does not re-fire: harness/bivharness/e3.py and both anchored collector files are
among the 27 exact CARRY rows. Full macOS and Ubuntu 24.04 linux/amd64 Docker parity
were deliberately not started after the hard carry stop.

## Publication and required disposition

Remote refs remain exactly:

- C b8083be8529a97d1d3d5931a2c7b308335bbd09c;
- B2 3762f3722a1fcebfbaa25921c31ca2f10df4ddf4.

No force-with-lease, PR metadata mutation, GitHub Actions invocation/inspection, merge,
tag, deploy, seal, or release occurred.

Requested next action: issue a corrected scope/carry disposition that recognizes
src/adapters/adapter.hpp and src/core/pack/pack.cpp as FRESH inherited R-4.8
clean-merge unions, making the combined re-check set seven files. If that is the
intended ruling, the local candidate heads above can resume at full host/Docker
verification, independent review, and the already named two-lease publication step
without rebuilding the restack.

C never lands without B2 (A10.3). 231437 remains WITHDRAWN. The release hold is
ABSOLUTE.

ACTIONS_GIT_REF: local C branch moved b8083be8529a97d1d3d5931a2c7b308335bbd09c -> f03ce70ccb50e7b0946929653f7f9bafecc9cfac and local B2 branch moved 3762f3722a1fcebfbaa25921c31ca2f10df4ddf4 -> fd857f124b8e60d982fc341a563bab99317b0850; both worktrees clean; remote C/B2 refs remain at the old exact leased heads; this blocker relay and its append-only INDEX row are the only docs-lane writes from this filing
FINAL_GIT_STATUS_SHORT: local C and B2 product worktrees clean at the unpublished candidate heads; shared docs checkout retains unrelated pre-existing untracked relay state, preserved; this filing adds only the named blocker relay and its INDEX row

CARRY LIST:
- .relays/s4/s4-floor-impl/SITREP-IMPLEMENTER-CB2-RESTACK-SCOPE-STOP-TWO-UNLISTED-FRESH-20260811-002848.md -> s4-floor.planner
- local unpublished candidates C f03ce70 / B2 fd857f1 -> held intact pending corrected seven-file FRESH disposition
- 34-row result: 27 CARRY / 7 FRESH; unlisted FRESH = src/adapters/adapter.hpp, src/core/pack/pack.cpp
- no publication, Actions, merge, seal, or release; release hold ABSOLUTE
