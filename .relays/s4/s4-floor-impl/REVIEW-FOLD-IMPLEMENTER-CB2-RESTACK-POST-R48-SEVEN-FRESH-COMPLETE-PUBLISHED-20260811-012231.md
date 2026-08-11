## REVIEW-FOLD — C/B2 re-stack onto post-R-4.8 main complete; 27 CARRY / seven FRESH verified; independent review CLEAR; paired draft refs published

ROLE: Implementer
PHASE: REVIEW-FOLD
AUTHORITY: fold-in-only
DISPATCH_ID: s4-floor-impl-2-cb2-restack-post-r48-seven-fresh-complete
PARENT_DISPATCH_ID: s4-floor-impl-2-cb2-restack-carry-corrected
RUN_ID: s4
TASK_ID: B2
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — fresh paired hand-up, master's condition-3, operator's paired condition-4, merge, seal, and release remain separately gated; release hold ABSOLUTE
DESIGN_LOCK_ID: m2-addendum11-422d451b-lock-20260810
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/IMPL-PLANNER-CB2-RESTACK-CARRY-RULE-CORRECTED-SEVEN-FRESH-DISPATCH-IMPL-TOKEN-20260811-003533.md
RELATED_CONTEXT: .relays/s4/s4-floor-impl/REVIEW-FOLD-SCOPE-AMENDMENT-IMPLEMENTER-CB2-RESTACK-SEVEN-FRESH-20260811-004304.md; .relays/s4/s4-floor-impl/SITREP-IMPLEMENTER-CB2-RESTACK-SCOPE-STOP-TWO-UNLISTED-FRESH-20260811-002848.md; .relays/s4/s4-floor-impl/IMPL-PLANNER-CB2-RESTACK-ONTO-POST-R48-ORIGIN-MAIN-DISPATCH-IMPL-TOKEN-20260810-235910.md
FROM: s4-floor.implementer
TO: s4-floor.planner
CC: s4.orchestrator-planner, operator, s4.orchestrator-reviewer, m-2.planner
SUBJECT: DONE_WITH_CONCERNS — C f03ce70 / B2 fd857f1 re-stacked onto exact post-R-4.8 main, 27 CARRY / seven FRESH proven, full host and bounded Linux parity complete, independent review CLEAR, and both draft refs published under exact leases

DONE_WITH_CONCERNS / REVIEW-FOLD FILED

The corrected seven-FRESH re-stack is complete at the exact accepted candidates. C is
one commit directly on post-R-4.8 `origin/main`; B2 is one commit directly on C. The
five conflict files retain the required behavior from both sides, and the two added
FRESH files are the no-manual-resolution clean-merge unions ruled IN by `003533`.

Full macOS and bounded Ubuntu 24.04 `linux/amd64` validation were rerun at exact B2
`fd857f1`. Independent review returned APPROVE with zero Critical, Important, or Minor
findings. C and B2 were then force-with-lease published in the authorized order to the
two existing draft branches. Both PRs remain OPEN/DRAFT against `main`; no PR metadata
was changed.

The concerns are the standing, fully disclosed Docker Desktop/Rosetta process-lifecycle
and overlay mutation races plus the inherited stale 223-case workflow count gate. The
bounded exclusion controls are green. These are not relabeled as an all-green canonical
Linux aggregate.

No GitHub Actions run or check was invoked, rerun, cancelled, or inspected. No merge,
tag, deployment, seal, or release occurred. C never lands without B2; the release hold
is ABSOLUTE.

## Scope disposition

FOLD_SCOPE:
- src/core/open/sessions.cpp -> in
- tests/test_adapter_claude_install.cpp -> in
- tests/test_adapter_codex_install.cpp -> in
- tests/test_pack.cpp -> in
- tests/test_sessions.cpp -> in
- src/adapters/adapter.hpp -> in
- src/core/pack/pack.cpp -> in
- .git/refs/remotes/origin/s4-floor/c-consent-no-carrier -> in
- .git/refs/remotes/origin/s4-floor/b2-torn-tail -> in
FOLD_SCOPE_RESULT: all-in

No product or test edit was made after the corrected token. The held candidates were
resumed as ordered. `adapter.hpp` and `pack.cpp` were not manually resolved: their
FRESH classification is the inherited clean-merge union of paneled B2 and R-4.8.

Hard OUT remained untouched: `.github/**`, every other ref, PR metadata, slice E/X-1,
WSL/A11, R-4.16, the sealed A9 member shape, merge, tag, deploy, seal, and release.

## Exact topology and publication receipts

| layer | exact SHA | parent | subject |
|---|---|---|---|
| post-R-4.8 main | `38a4702bdc6c0fe82a102ebf58977ca7ad67623a` | — | merge target |
| C | `f03ce70ccb50e7b0946929653f7f9bafecc9cfac` | `38a4702bdc6c0fe82a102ebf58977ca7ad67623a` | `feat(open): stage consent-no sessions with provenance sidecar` |
| B2 | `fd857f124b8e60d982fc341a563bab99317b0850` | `f03ce70ccb50e7b0946929653f7f9bafecc9cfac` | `feat(pack): collect torn tails and staged sidecars` |

Final topology checks:

- `git merge-tree --write-tree --name-only origin/main f03ce70...` exit 0,
  result tree `8e1eb0cfe03595ddf980dca36e751f7d82d3c352`;
- `git merge-tree --write-tree --name-only origin/main fd857f1...` exit 0,
  result tree `2d47080877eaf9366e416c39b298905cd051aa9e`;
- baseline-to-C ancestry exit 0;
- C-to-B2 ancestry exit 0;
- `git rev-list --count origin/main..fd857f1^` = **1**.

The blast radius therefore fell from 27 to 1: the sole prior commit published by B2 is
C itself. The old docs-lane ancestry is no longer a side effect of the product stack.

Guarded publication succeeded:

- C: lease `b8083be8529a97d1d3d5931a2c7b308335bbd09c` → published
  `f03ce70ccb50e7b0946929653f7f9bafecc9cfac` to
  `s4-floor/c-consent-no-carrier`;
- B2: lease `3762f3722a1fcebfbaa25921c31ca2f10df4ddf4` → published
  `fd857f124b8e60d982fc341a563bab99317b0850` to
  `s4-floor/b2-torn-tail`.

Post-publication verification found `main` still exact `38a4702`, PR #22 OPEN/DRAFT at
exact `f03ce70`, and PR #23 OPEN/DRAFT at exact `fd857f1`. No ready/undraft, title,
body, base, label, merge, auto-merge, or check action was performed.

## Five manually reconciled files

1. `src/core/open/sessions.cpp` retains R-4.8's capability and `packer_home` target
   shape together with C's per-agent consent call and staged sidecar result.
2. `tests/test_adapter_codex_install.cpp` retains the R-4.8 packer-home byte-identity
   case together with C's consent-NO staging and unwritable-workspace cases.
3. `tests/test_sessions.cpp` retains both R-4.8 packer-home transport cases together
   with C's staged outcome and provenance-sidecar cases; its fixture records both
   packer homes and consent/install targets.
4. `tests/test_adapter_claude_install.cpp` retains R-4.8 packer-home byte identity
   together with B2's escaped value, origin-path key, and child-identity assertions.
5. `tests/test_pack.cpp` retains R-4.8 isolated pack-discovery helpers together with
   B2 staging helpers and the table-driven flat bare-hex, flat slug-hex, and nested
   bare-hex stage-pack-open acceptance case.

No side was accepted wholesale in a conflict. `.pending-r415`, `child_alias_ids`, and
`child_identity_shape` are absent. The alias-ABSENT arm was not resurrected; the struck
`staged_path_caveats` convener-error claim stays struck. The sealed A9 pair-list member
shape is unchanged.

## 34-row paneled-byte carry adjudication

`old SHA-256` is the file byte hash at paneled B2 `3762f37`; `new SHA-256` is the file
byte hash at re-stacked B2 `fd857f1`.

| result | path | old SHA-256 | new SHA-256 |
|---|---|---|---|
| CARRY | `harness/CMakeLists.txt` | `21d348285d54d2d1cb1f17b8d9d9f388816de719258f5eac0d4fa5475ff49505` | `21d348285d54d2d1cb1f17b8d9d9f388816de719258f5eac0d4fa5475ff49505` |
| CARRY | `harness/bivharness/compare.py` | `8ac47d21356824ca61783e6fce06699bd2c9a8666a2688a5942e43ab897a428c` | `8ac47d21356824ca61783e6fce06699bd2c9a8666a2688a5942e43ab897a428c` |
| CARRY | `harness/bivharness/e3.py` | `2fb295a67ab2dd95388579e05513b1901b5db528e73faa4ad6e2ba097d3df6ec` | `2fb295a67ab2dd95388579e05513b1901b5db528e73faa4ad6e2ba097d3df6ec` |
| CARRY | `harness/bivharness/scenario.py` | `2ee49d6e457a5bb618ad50d09fa75eb9e9c754085d35299c5672f921106879a9` | `2ee49d6e457a5bb618ad50d09fa75eb9e9c754085d35299c5672f921106879a9` |
| CARRY | `harness/scenarios/open-consent-no.json` | `73f438c4e492f6ee54ef9b4b1a57480f1fe1052409ff64a15a78230284e58100` | `73f438c4e492f6ee54ef9b4b1a57480f1fe1052409ff64a15a78230284e58100` |
| CARRY | `harness/scenarios/open-consent-per-agent.json` | `0fdaecb1c117b32d90f7d8b500c5134acbdc9f10403e89b09e2e9a3b29a9734f` | `0fdaecb1c117b32d90f7d8b500c5134acbdc9f10403e89b09e2e9a3b29a9734f` |
| CARRY | `harness/scenarios/open-deny-default.json` | `3b1c659c838ab1ba820c44a1f842d862f777f20a87a8671c88034c543e80a602` | `3b1c659c838ab1ba820c44a1f842d862f777f20a87a8671c88034c543e80a602` |
| CARRY | `harness/selftest/test_compare.py` | `b2d66c81c5caf3b20d13e23b4e7f077deed72e629ae6f553e12e9ca7d72f2da5` | `b2d66c81c5caf3b20d13e23b4e7f077deed72e629ae6f553e12e9ca7d72f2da5` |
| CARRY | `harness/selftest/test_e3_asserts.py` | `2c864581b7b63e81b390ab0fbfec129288179871988fc275041c5b14ae0a734d` | `2c864581b7b63e81b390ab0fbfec129288179871988fc275041c5b14ae0a734d` |
| CARRY | `harness/selftest/test_envelope.py` | `0291fb3e0b2ab43ebb14a97a3c5a1d5125312765110cbd97e660647c57ec92c3` | `0291fb3e0b2ab43ebb14a97a3c5a1d5125312765110cbd97e660647c57ec92c3` |
| CARRY | `schemas/biv-exit-map.v1.json` | `b3f3262a2362bb857fd0d8d50ad68ff73795f63eba5c88c574be350d0a69df0a` | `b3f3262a2362bb857fd0d8d50ad68ff73795f63eba5c88c574be350d0a69df0a` |
| CARRY | `schemas/biv-json-envelope.v1.schema.json` | `4b4412c3dddca0cabbe9ed615af75cf05a388f1ec33f53811d0643e7cc7765dd` | `4b4412c3dddca0cabbe9ed615af75cf05a388f1ec33f53811d0643e7cc7765dd` |
| FRESH | `src/adapters/adapter.hpp` | `1c96d3ac7b86b7836296475b2da3d6fd07b1806a70268a5a9981f237b713fcb4` | `5516233907859e8915170ecea782f08074a355c230bf737d5a4359b6c1519f29` |
| CARRY | `src/adapters/claude_code/claude_code.cpp` | `cd1f8bc8f7ab87cf15251d84ad7e59c618a22f3c19b9633ff193350782800851` | `cd1f8bc8f7ab87cf15251d84ad7e59c618a22f3c19b9633ff193350782800851` |
| CARRY | `src/adapters/claude_code/install.cpp` | `5802406ee272ed496d005a8c8010fe08e21d336dd2e5e562c5177aedf27a2c11` | `5802406ee272ed496d005a8c8010fe08e21d336dd2e5e562c5177aedf27a2c11` |
| CARRY | `src/adapters/codex/codex.cpp` | `2fd24c84bc7f114268b4e3d5f2d5fc98075130c61aa90c4df548f0fa13b5406d` | `2fd24c84bc7f114268b4e3d5f2d5fc98075130c61aa90c4df548f0fa13b5406d` |
| CARRY | `src/adapters/codex/install.cpp` | `5e829ff7b391f8a06ff637f902a4a33cb1b7b56db3a363b31f12be7ba4b783b7` | `5e829ff7b391f8a06ff637f902a4a33cb1b7b56db3a363b31f12be7ba4b783b7` |
| CARRY | `src/adapters/rewrite_common.cpp` | `cfcd49111ff9a4c9deabcd249d10ed9996d7c4adf597c86fb864309a41f60c96` | `cfcd49111ff9a4c9deabcd249d10ed9996d7c4adf597c86fb864309a41f60c96` |
| CARRY | `src/adapters/rewrite_common.hpp` | `4a0e77b7d7331f7419e87cf7746ce31428d17af3e1351500139a4d93a7ab48f3` | `4a0e77b7d7331f7419e87cf7746ce31428d17af3e1351500139a4d93a7ab48f3` |
| CARRY | `src/core/open/render.cpp` | `af1045fc68cc8b3cc0272795f5ec8324733297c8fd9e3405046c9e6e660ffd82` | `af1045fc68cc8b3cc0272795f5ec8324733297c8fd9e3405046c9e6e660ffd82` |
| FRESH | `src/core/open/sessions.cpp` | `bd64bb5b8229f204975e1477232715014a78b223042105917981116d432fd46f` | `685c9fbd1c01fdfce11e552955210d0ff471add5aa22cd5431f69afd9be34704` |
| CARRY | `src/core/open/sessions.hpp` | `deac5a31bb2e23121ab370665698a03b987f940a8f0a2ae3f83bb6e1528fbb9f` | `deac5a31bb2e23121ab370665698a03b987f940a8f0a2ae3f83bb6e1528fbb9f` |
| FRESH | `src/core/pack/pack.cpp` | `0f5cabfd755eea473e76c047c4ad47d1b0f7127de1da3f95d550731b85a1ea33` | `1a97083f6944718a86f90883959b4a969b1fbc082a22833fcb3bec7304d66779` |
| CARRY | `src/core/report/envelope.cpp` | `3d0830ceddbb9ea1faae30b1d6ccee728648fc915f8a8208424071ddb54eaef6` | `3d0830ceddbb9ea1faae30b1d6ccee728648fc915f8a8208424071ddb54eaef6` |
| CARRY | `src/core/support/error.cpp` | `f3447560dd505542f10b26f46d5fb61942405f5928d9040161dad5dd57f5fd18` | `f3447560dd505542f10b26f46d5fb61942405f5928d9040161dad5dd57f5fd18` |
| CARRY | `src/core/support/error.hpp` | `4f7172709ff497eff744e52dd09ab2db2e3854b11b1f3fffe5e423641f407514` | `4f7172709ff497eff744e52dd09ab2db2e3854b11b1f3fffe5e423641f407514` |
| CARRY | `tests/test_adapter_claude_collect.cpp` | `2131cc80a628d8a2a6de67a8e10c29ba00389a08b42c32daa4bfa1eb473b3a64` | `2131cc80a628d8a2a6de67a8e10c29ba00389a08b42c32daa4bfa1eb473b3a64` |
| FRESH | `tests/test_adapter_claude_install.cpp` | `152b82df86da61e55c7410f94d55251c0080e60deb4025a9869c9b7fd8b45b2a` | `c7cee6264b5fe24729dc8c61a138aebaae4087ce19f9356b08c12b603f1e2720` |
| CARRY | `tests/test_adapter_codex_collect.cpp` | `6b52a282387d12eff55d5718767d176e7c45b923faed4455f92609eff08b4d6e` | `6b52a282387d12eff55d5718767d176e7c45b923faed4455f92609eff08b4d6e` |
| FRESH | `tests/test_adapter_codex_install.cpp` | `35506db97b7af78b49b770301a3f027dc40a5a7b5463e15fad1dc3b01e1bd0f5` | `261a7cabd9efd51c3c30bffb288f7dec710f3029c4539860e56db183f811364a` |
| CARRY | `tests/test_cli.cpp` | `1c74fd06693577039d91d87c4a69dc42386888baa27ae3288dc7bb573453f8ae` | `1c74fd06693577039d91d87c4a69dc42386888baa27ae3288dc7bb573453f8ae` |
| CARRY | `tests/test_envelope.cpp` | `8326536990f366bf46b2ba3272a2858d5784af7f4b830cd85b4646b3f040cf3d` | `8326536990f366bf46b2ba3272a2858d5784af7f4b830cd85b4646b3f040cf3d` |
| FRESH | `tests/test_pack.cpp` | `38d790c1b185e7757d03d1b17e13592cebf46065b7c9ed84218d12a16c8b57ff` | `50881bd28bf94509ff64589484ca384e78971e5b93fecf19c2f86bca49266ff5` |
| FRESH | `tests/test_sessions.cpp` | `cbb4cdf17775fe8c51687d2a5c8efb26f0d51fdc8d523db21c930cb9c58e0883` | `54781af36add6e66599145e7a595c539e383580907638fe1fd65266d20db3570` |

Totals: **27 CARRY / seven FRESH**. No eighth FRESH row and no path outside the
34-row union exists in the re-stacked delta.

The two clean-merge union rows retain the landed R-4.8 carrier exactly at the new head:
one `packer_home` occurrence in `src/adapters/adapter.hpp` and three in
`src/core/pack/pack.cpp`, versus zero in paneled B2. No manual resolution touched either
file.

## A3 determination

A3 does **not** re-fire. All three named anchor surfaces are exact byte-identical CARRY
rows:

- `harness/bivharness/e3.py` → `2fb295a6...`;
- `tests/test_adapter_claude_collect.cpp` → `2131cc80...`;
- `tests/test_adapter_codex_collect.cpp` → `6b52a282...`.

The restack therefore does not move either anchored collector or the harness code that
binds their hashes. No new A3 execution or anchor edit was required.

## macOS validation at exact `fd857f1`

The host command was:

```text
cmake --preset ci-macos && cmake --build --preset ci-macos && ctest --preset ci-macos -E '^safety-hardening$' --output-on-failure
```

Configure and build passed. CTest exited 0 with no failures among 14 selected rows in
486.56 seconds. Product, open-no-rewrite, core-adapter-purity, version mirror, errno,
probe envelope, generated envelope, harness selftest, harness E2, and Werror rows all
passed. ASan/UBSan, clang-tidy, and fuzz smoke took their configured macOS skip arms;
the explicitly excluded hardening row was exercised in Linux below.

## Ubuntu 24.04 `linux/amd64` Docker parity at exact `fd857f1`

The disposable container used `ubuntu:24.04` with `--platform linux/amd64`, Python
3.12.3, CMake 3.28.3, GCC 13.3.0, and the exact eight pinned LLVM mirror packages from
the canonical workflow. All package SHA-256 values matched; all package versions
matched `1:22.1.8~++20260613092238+e80beda6e255-1~exp1~20260613092253.78`;
`clang-tidy-22 --version` reported LLVM 22.1.8. The writable `/mnt/c/tmp` workflow
fixture was provisioned before the parity rerun. Configure selected
`/usr/bin/clang-tidy-22`; the hardened build completed.

The canonical CTest aggregate returned **8**, disclosed rather than normalized:

- raw product: 385 cases = 380 passed + 5 failed; 11,203 assertions = 11,195 passed
  + 8 failed;
- the five unique product cases are the registered emulated process-lifecycle class:
  invalid pinned executable classification; timeout/process-group grandchild reap;
  detached-descendant acknowledgement; clean-exit pipe-holding grandchild disposal;
  and post-KILL handoff fallback (two generated sections);
- raw harness parity run: 974 cases = 969 passed + 2 failed + 3 skipped. The observed
  failures were two members of the registered four-case overlay metadata/enumeration
  race class; an earlier same-container run exposed all four, confirming the known
  variable subset;
- `generated_envelope_conforms` was dependency-not-run because `biv_tests` failed;
  direct schema validation of the generated artifact passed;
- harness E2, Werror, clang-tidy analyzer, and hardening passed;
- the JUnit tidy-row gate independently reported status `run` and PASS;
- ASan/UBSan and fuzz smoke took their configured workflow skip arms.

The fresh `--init` diagnostic excluded exactly the five registered product cases and
passed **380/380 cases, 11,086/11,086 assertions**. The harness diagnostic excluded
exactly the four registered overlay cases and passed **967**, with 3 configured skips
and 4 deselections. No implementation-owned regression remained after those bounded
environment substitutions.

The workflow's exact Catch2 XML count was 380 successes / 5 failures / 0 expected
failures / 0 skips. Its hard-coded 223/0/0/0 count gate is inherited and stale. No
`.github/**` edit was authorized or made.

The task-scoped canonical container, fresh diagnostic container, temporary diagnostic
image, and exact pinned-package staging directory were removed. No unrelated Docker
resource was pruned or removed.

## Independent review

Independent final review returned **APPROVE** with:

- Critical: none;
- Important: none;
- Minor: none.

The reviewer independently reproduced the clean B2 worktree, baseline→C→B2 ancestry,
the exact 34-path scope, 27 CARRY / seven FRESH classification, both R-4.8 union patch
identities and `packer_home` retention, absence of forbidden alias/pending markers,
and blast radius 1. A fresh focused run covering the seven FRESH rows passed **1,227
assertions in 20 cases**, including `packer_home`, torn tails, staged sidecars,
consent-NO staging, escaped origins, and all three child-stem shapes.

The reviewer explicitly did not rerun the controller's full host/Docker aggregates;
those receipts remain controller evidence above, not falsely attributed as independent
reproduction.

## Final state and downstream boundary

Both product worktrees are clean at their exact published heads. `git diff --check`
passes for `38a4702..fd857f1`. The final forbidden-marker scan is clean.

This report completes implementation, local validation, independent review, and the
two authorized draft-branch publications. It does not provide fresh paired hand-up,
condition-3, condition-4, merge, seal, release, or live-deployment proof. Those remain
downstream. A10.3 binds: C never lands without B2. The release hold is ABSOLUTE.

ACTIONS_GIT_REF: guarded publication only — `s4-floor/c-consent-no-carrier` b8083be8529a97d1d3d5931a2c7b308335bbd09c -> f03ce70ccb50e7b0946929653f7f9bafecc9cfac, then `s4-floor/b2-torn-tail` 3762f3722a1fcebfbaa25921c31ca2f10df4ddf4 -> fd857f124b8e60d982fc341a563bab99317b0850; this relay and its append-only INDEX row ride one explicit-path docs-lane commit whose SHA lands after filing
FINAL_GIT_STATUS_SHORT: C and B2 product worktrees clean; shared docs checkout retains unrelated pre-existing untracked relay files, preserved; this seat writes only this report and its one INDEX row

CARRY LIST:
- `.relays/s4/s4-floor-impl/REVIEW-FOLD-IMPLEMENTER-CB2-RESTACK-POST-R48-SEVEN-FRESH-COMPLETE-PUBLISHED-20260811-012231.md` -> `s4-floor.planner`
- C `f03ce70` / B2 `fd857f1` published on exact leases; both PRs remain OPEN/DRAFT
- 27 CARRY / seven FRESH; five manual reconciliations plus two clean-merge R-4.8 unions; A3 does not re-fire; blast radius 1
- macOS no selected-row failures; bounded Linux exceptions disclosed with exact green controls; independent review APPROVE with zero findings
- no Actions inspection or invocation; no PR metadata change, merge, tag, deploy, seal, or release; A10.3 and release hold ABSOLUTE
