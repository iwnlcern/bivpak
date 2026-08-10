## REVIEW-FOLD — four-fold C/B2 implementation complete with ADDENDUM-11: exact heads host/Docker verified, fresh review CLEAR, merge trees clean, and draft PRs republished

ROLE: Implementer
PHASE: REVIEW-FOLD
AUTHORITY: fold-in-only
DISPATCH_ID: s4-floor-impl-2-cb2-four-folds-addendum11-review-fold
PARENT_DISPATCH_ID: s4-floor-impl-2-b2-leg-resume
RUN_ID: s4
TASK_ID: B2
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new gate at this seat — this filing requests the already-required targeted M-4 and round-trip re-panel; merge, condition-4, seal, and release remain held
DESIGN_LOCK_ID: m2-addendum11-422d451b-lock-20260810
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
CONSUMED_CONTRACT: m2-addendum11-422d451b-lock-20260810 (certified pdc rev11 blob `858d1ca5f4af66ddb2f186466d2ee1d2b77aa7e7`, SHA-256 `422d451b0c613a44f30bf8a93739a691ee410e178ffea7942ec1c31b728d4fcb`)
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-PLANNER-B2-SIDECAR-LEG-RESUME-UNDER-STANDING-TOKEN-20260810-063656.md
FROM: s4-floor.implementer
TO: s4-floor.planner
CC: s4.orchestrator-planner, operator, s4.orchestrator-reviewer
SUBJECT: DONE_WITH_CONCERNS — A1/A2/B1/B2 and ADDENDUM-11 are folded at C b8083be and B2 20e56bc; exact host and classified Ubuntu amd64 suites are complete; fresh review is CLEAR; PR #22/#23 are draft and exact; targeted re-panel requested; release hold ABSOLUTE

DONE_WITH_CONCERNS / REVIEW-FOLD FILED

The implementation concern is limited to environment classification: macOS lacks the
Linux hardening/tidy prerequisites, and Docker Desktop reproduces the standing
Rosetta-spawn classification plus nondeterministic overlay mutation-sentinel behavior.
The exact controlled suites and every substantive Linux gate are green. No unresolved
product or test finding remains from this fold.

## Certified design and final topology

The ADDENDUM-11 design was read at the certified pdc rev11 blob, not from the stamped
working file. Its content hash was independently re-derived as
`422d451b0c613a44f30bf8a93739a691ee410e178ffea7942ec1c31b728d4fcb`.

Final C:

- branch `s4-floor/c-consent-no-carrier`;
- head `b8083be8529a97d1d3d5931a2c7b308335bbd09c`;
- parent `721eeaefd168c917e4ee4cadf7cd0366baa43514`;
- exactly one commit, subject preserved as `feat(open): stage consent-no sessions with provenance sidecar`;
- ADDENDUM-11 amendment confined to `src/core/open/sessions.cpp` and `tests/test_sessions.cpp`.

Final B2:

- branch `s4-floor/b2-torn-tail`;
- head `20e56bc4053d4a27c4b47b6dbff0fc02af1dcc13`;
- parent exact C `b8083be8529a97d1d3d5931a2c7b308335bbd09c`;
- exactly one commit, subject preserved as `feat(pack): collect torn tails and staged sidecars`;
- direct parent-to-head range remains 17 paths; this fold's changed paths are all in the authorized scope below.

Both isolated worktrees were clean immediately before publication and are clean against
their published remote branches afterward.

FOLD_SCOPE:
- src/adapters/claude_code/install.cpp -> in
- src/adapters/codex/install.cpp -> in
- src/adapters/claude_code/claude_code.cpp -> in
- src/adapters/codex/codex.cpp -> in
- src/core/open/sessions.cpp -> in
- src/adapters/rewrite_common.cpp -> in
- src/adapters/rewrite_common.hpp -> in
- harness/bivharness/e3.py -> in
- tests/test_adapter_claude_install.cpp -> in
- tests/test_adapter_codex_install.cpp -> in
- tests/test_adapter_claude_collect.cpp -> in
- tests/test_adapter_codex_collect.cpp -> in
- tests/test_pack.cpp -> in
- tests/test_sessions.cpp -> in

FOLD_SCOPE_RESULT: all-in

No path outside this scope was edited. C's writer remains on C and both staged readers
remain on B2.

## Implemented contract

Fold A is closed for both adapters: the image-ID union is derived from all records before
version-floor decisions and includes each record's artifact-derived primary identity.
Claude collection is collect-then-decide: an undecodable artifact sets refusal but no
longer truncates harvesting of later origin UUIDs. Version-refused siblings and
refused-mid-collection sessions therefore cannot under-seed the rewrite needle.

Fold B1 is closed structurally. Writer and staged reader consume the shared safe-relative,
suffix-constrained Claude subtree predicate. A legal consent-NO subtree such as
`<id>/notes.txt` survives open-to-pack round-trip, while foreign and unsafe members still
fail closed.

Fold B2 and ADDENDUM-11 are closed at their owning heads:

- C always emits one `original_path` per `id_map` row, joining to exactly one record by
  `(agent, image_session_id)`, never order, and fails on missing or duplicate join;
- Windows-drive rows emit the `windows_backslash` representative from
  `origin_spellings`; other rows emit the `literal` representative;
- `pair_set_applied` shape, sort, uniqueness, and meaning are unchanged;
- B2's generic parser accepts only two global states across every agent and row:
  all-absent runs old inference; all-present validates and uses every row value;
- mixed presence, wrong type, empty or duplicate member, missing pair, target mismatch,
  or well-formed value outside the audited set refuses at parse as
  `invalid_staged_sidecar`;
- Codex uses per-row provenance in present state and the unchanged global resolver only
  in absent state; Claude uses validated provenance while staged location remains
  destination-project-keyed;
- membership is integrity-only and is not claimed as hostile-image containment.

Required disclosed behavior change, verbatim:

a Windows drive origin containing any / normalizes to the canonical spelling on round-trip

The 1+N obligation is explicit: the global pair collection is one site and every staged
row is another occurrence, including rows sharing one origin. The producer falsifier uses
two rows with the same mixed-separator Windows origin, proving two per-row occurrences
while the global pair set remains deduplicated.

## RED to GREEN receipts

- A1/A2/B1 pre-fix receipt: four intended assertions failed in the 22-assertion focused
  cohort; after the fold the same cohort passed 22/22 and the expanded four-fold set
  passed 429/429.
- The first six-case ADDENDUM-11 reader wave produced five intended failures: FX-A11-1
  could not repack two Codex paths; FX-A11-3 accepted three malformed forms; FX-A11-4 and
  FX-A11-5 accepted invalid state; FX-A11-6a recovered legacy rather than row provenance.
  Independent FX-A11-6b destination-location control already passed.
- The producer initially lacked `original_path`; the 1+N two-row producer check was RED
  at both per-row members, then passed 31 assertions.
- Final coverage includes FX-A11-1 through FX-A11-8b, with malformed and outside-audit
  cases separate, old all-absent compatibility including ambiguous typed refusal, mixed
  presence, both consumers, mixed separators, and byte-identical second repack.
- Final exact-head `FX-A11-*`: 721 assertions in 10 cases passed; wider
  Addendum/long-origin cohort: 766 assertions in 12 cases passed; standing A1/A2/B1
  cohort: 125 assertions in four cases passed; legacy all-absent composite: 16 passed.

Review found and closed one critical issue before publication: Claude consent-NO staging
was still origin-project-keyed. The corrected test was RED at 12/14 and GREEN at 29/29
after restoring the locked destination project key. A stale long-origin fixture exposed
the same superseded assumption in the full suite; it was rewritten to assert the
destination-keyed six-artifact result, with production bytes unchanged.

Linux verification found and closed two portability defects before publication. GNU 13
Werror rejected three new `SessionIds` fixtures with implicit optional defaults; all now
state both null optionals. LLVM 22 rejected an unchecked optional dereference in the Codex
absent-state resolver; definite string storage now preserves both closed states. That
production-byte change intentionally tripped A3, so the Codex anchor was recaptured.

## A3 ceremony and final review

- Claude collector SHA-256: `2f6da068e2f2c5f0297419664621717df9fd30ce786a8ed790783d317fc16092`.
- Codex collector SHA-256: `83684ecfc8eeeea4b4a4ee64291fb9f545e0e1ba07a911ae8d11afd789f1b5b2`.
- Both match the two literals in `harness/bivharness/e3.py`.
- A3 drift-tripwire cohort: 12 passed, 844 deselected.

A fresh independent read-only review at exact B2 `20e56bc` over C `b8083be` returned
CLEAR / PASS with no findings. It verified the final portability delta, unchanged
all-absent/all-present semantics, both exact anchors, and clean `git diff --check`.

## macOS host verification

At exact C `b8083be`:

- full product passed in 267.74 seconds;
- open-no-rewrite, purity, version, errno, schema, envelope, harness-selftest, and Werror passed;
- the configured 180-second E2 row timed out, while its exact underlying command exited 0
  with 17 rows: 11 pass, six `xfail-pending`, no failed or invalid rows;
- hardening reports the environmental prerequisite `readelf unavailable`.

At exact B2 `20e56bc`:

- full product: 337 cases, 335 passed, two WSL-only skips, 9,222/9,222 assertions passed;
- eight selected gates passed: open-no-rewrite, purity, version, errno, probe-schema,
  harness-selftest, E2, and Werror;
- E2 passed in 182.95 seconds; direct generated-envelope validation passed;
- macOS tidy is configured as a skip and hardening requires Linux `readelf`; both passed
  in the Linux gate below.

## Local Ubuntu 24.04 linux/amd64 Docker parity

No GitHub Actions test was used as a Linux substitute. Each exact head was cloned clean
and detached into a disposable `ubuntu:24.04` container with `--platform linux/amd64`.
Each run verified eight immutable LLVM package hashes, names, exact version
`1:22.1.8~++20260613092238+e80beda6e255-1~exp1~20260613092253.78`, and amd64 architecture.
Observed: Python 3.12.3, GNU 13.3.0, LLVM/clang-tidy 22.1.8.

At C `b8083be`:

- configure/build, purity, open-no-rewrite, version, errno, schema, E2, Werror, executed
  clang-tidy, hardening, and direct envelope validation passed;
- canonical product: 269 passed, one standing failure out of 270, 7,110/7,111 assertions;
  only `version probe does not fall back to PATH when a pinned executable cannot spawn` failed;
- controlled product excluding only that registered Rosetta-on-Docker case passed 269;
- canonical harness reproduced three or four registered overlay sentinels depending on
  run, with four platform skips; controlled harness passed 967, skipped four, deselected four.

At B2 `20e56bc`:

- configure/build, purity, open-no-rewrite, version, errno, schema, E2, Werror, executed
  clang-tidy, hardening, and direct envelope validation passed;
- canonical product: 336 passed, one standing failure out of 337, 9,050/9,051 assertions;
  only the same registered probe case failed;
- controlled product excluding only that case passed 336;
- canonical harness observed one registered overlay sentinel, 970 passed, four skipped;
  controlled harness passed 967, skipped four, deselected four.

Configured CTest safety skips were `safety-asan-ubsan` and `safety-fuzz-smoke`. No
unrelated Docker resource was pruned or removed.

## Non-gating dispositions

- Fresh-`InstallResult` report integrity remains unreachable under today's preparation
  flow; registered, not claimed closed.
- Slice-E Claude parent mapping and refused-parent/clean-child coherence remain
  fail-closed cosmetic items for their owning slice; no expansion taken.
- Unsupported-subtree intent is clarified by the shared B1 predicate; unsafe/foreign
  members remain fail-closed.
- Consent-NO clean-skip drift is master-confirmed intended; no action taken.
- Membership is recorded only as sidecar integrity, never hostile containment.

## Merge-tree and publication receipts

Current remote `main`: `8981bfd0848039d533d9bb2a96301d4d81b564fa`.

- main -> C `b8083be`: conflict-free tree `64d77cdeade243f7da001402a19212ef5d5d73d1`;
- C `b8083be` -> B2 `20e56bc`: conflict-free tree `7addb73c35eafd3583d162f50d9fe0a9dca981ff`.

After implementation, both platform suites, and fresh review completed, explicit leases
moved only the authorized branches:

- PR #22: `d6e44d9e5ec4ff48e5121a9674ef7788eca9e881` -> exact C `b8083be8529a97d1d3d5931a2c7b308335bbd09c`;
- PR #23: `0653fea400e83a59f4c3a9d7983510222e9159ec` -> exact B2 `20e56bc4053d4a27c4b47b6dbff0fc02af1dcc13`.

Remote refs and PR queries agree. Both PRs remain OPEN, DRAFT, and based on `main`.
GitHub Actions was not manually invoked, rerun, cancelled, or inspected; no result is claimed.

## Boundaries and requested handoff

Nothing seals. `231437` stays withdrawn. No merge, release, deployment, or live-behavior
claim is made; the release hold remains ABSOLUTE.

Next act: targeted M-4 plus both round-trip lenses at exact C `b8083be` and B2 `20e56bc`.
Only after that pass may the fresh paired hand-up and new condition-4 sequence occur in
C-first/B2-immediate order.

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: no
- migration/backfill/destructive-write/canonical-data-repair: no
- money/inventory/orders/planning/accounting/trust-critical-state: no
- AI-or-automation-acts-downstream: no
- worker/scheduler/queue/retry/async-side-effect: no
- cross-repo/service-contract/generated-schema/shared-API-event: yes, resolved by certified ADDENDUM-11 at exact `422d451b`; no unruled choice remains
- user-visible-control-with-materializer/downstream-consumer: yes, resolved at locked bytes; targeted re-panel remains required
- test-runtime-role-mismatch: no — exact host and detached Ubuntu amd64 rows exercised final bytes
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: no — scope exact; platform exceptions and registrations disclosed
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER: none
WAIVED_RISK_ACCEPTANCE: none

ACTIONS_GIT_REF: C `b8083be8529a97d1d3d5931a2c7b308335bbd09c` and B2 `20e56bc4053d4a27c4b47b6dbff0fc02af1dcc13` published with explicit leases to existing PR #22/#23 branches and verified exact; this report and append-only INDEX row are this seat's only shared-checkout writes; no PR metadata edit, manual Actions operation, merge, release, deployment, or unrelated cleanup
FINAL_GIT_STATUS_SHORT: C and B2 worktrees clean and equal remote; shared main retains pre-existing sibling untracked relays, preserved; this seat adds only this report and its INDEX append

CARRY LIST:
- `.relays/s4/s4-floor-impl/REVIEW-FOLD-IMPLEMENTER-CB2-FOUR-FOLDS-ADDENDUM11-FILED-20260810-083626.md` -> `s4-floor.planner`
- exact C `b8083be` / draft PR #22 and exact B2 `20e56bc` / draft PR #23 -> targeted M-4 plus round-trip re-panel
- ADDENDUM-11 -> writer/reader two-state row edge, 1+N N>1 falsifier, A3 both anchors green
- GitHub Actions -> unmanaged; no result claimed
- merge, seal, release, deployment -> untouched; release hold ABSOLUTE
