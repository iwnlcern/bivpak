## REVIEW-FOLD — CB2 G-1..G-4 re-check fold complete at B2 `8b12b25`; fresh review CLEAR; guarded draft-branch publication complete

ROLE: Implementer
PHASE: REVIEW-FOLD
AUTHORITY: fold-in-only
DISPATCH_ID: s4-floor-impl-2-cb2-recheck-g1-g4-complete
PARENT_DISPATCH_ID: s4-floor-impl-2-cb2-recheck-fold
RUN_ID: s4
TASK_ID: B2
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — targeted re-check of this exact fold delta, fresh paired hand-up, master's condition-3, and operator's paired condition-4 remain downstream gates; release hold remains ABSOLUTE
DESIGN_LOCK_ID: m2-addendum11-422d451b-lock-20260810
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/IMPL-PLANNER-CB2-RECHECK-FOLD-G1-G4-DISPATCH-IMPL-TOKEN-20260810-160025.md
RELATED_CONTEXT: .relays/s4/s4-floor-impl/IMPL-PLANNER-B2-GUARDED-PUBLICATION-DISPATCH-IMPL-TOKEN-20260810-154400.md
FROM: s4-floor.implementer
TO: s4-floor.planner
CC: s4.orchestrator-planner, operator, s4.orchestrator-reviewer
SUBJECT: DONE_WITH_CONCERNS — G-1..G-4 closed in one B2 commit at `8b12b25`; host and Ubuntu amd64 evidence complete; independent review CLEAR; guarded publication moved only the PR #23 draft branch

DONE_WITH_CONCERNS / REVIEW-FOLD FILED

Implementation, independent review, local verification, and the separately authorized
guarded draft-branch publication are complete. The concerns are limited to registered
platform-specific test exceptions and one stale workflow count gate described below;
the bounded product and harness controls are green. No GitHub Actions run or check was
invoked or inspected.

## Final topology and actual fold scope

- C remains byte-identical at `b8083be8529a97d1d3d5931a2c7b308335bbd09c`.
- B2 is one commit directly atop exact C at
  `8b12b25f38bbf0f8a400e1a9141ff9cea071f874`.
- The preserved B2 subject is `feat(pack): collect torn tails and staged sidecars`.
- The cumulative C-to-B2 range is 17 tracked paths; `.github/**` is absent from the diff.
- The implementation worktree is clean.

FOLD_SCOPE:
- src/adapters/claude_code/install.cpp -> in
- src/adapters/codex/install.cpp -> in
- tests/test_pack.cpp -> in
- tests/test_adapter_claude_install.cpp -> in
- tests/test_adapter_codex_install.cpp -> in

FOLD_SCOPE_RESULT: all-in

The authorization permitted ten paths, but this fold changed only the five above. Neither
collector nor `harness/bivharness/e3.py` changed, so the token's conditional A3 anchor
re-fire was not triggered. Hard OUT remains untouched: WSL/m-2, R-4.15/slice E, R-4.16,
sealed A9 member shape, `.github/**`, merge, tag, deployment, seal, and release.

## G-1 through G-4 disposition and falsifier receipts

- G-1 — same-adapter sibling control: the missing-version pack fixture now includes a
  second version-complete row in the same Claude adapter plus an unrelated Codex row and
  asserts that both survivors remain. Mutating the production staged-reader
  `continue` to `break` made the strengthened case RED: expected two sessions, observed
  one. Restoring `continue` returned the 12-assertion case to GREEN. This was tests-only;
  collector bytes remain unchanged.
- G-2 — Codex writer/reader symmetry: before staging, the writer parses the rewritten
  first `session_meta.payload` and requires every present `id` and `session_id` to equal
  that artifact's `WritePlan.installed_id`; either key may be absent. A mismatch refuses
  only that row as `containment_refused` / `staged_identity_mismatch`, clears its outputs,
  and preserves a clean sibling. Direct-install and stage/repack falsifiers cover the
  previously reachable `id:A` / `session_id:B` shape.
- G-3 — Claude writer/reader version same-set: the writer now establishes body version
  evidence. If the main body has no `version`, it injects manifest
  `agent_version_at_pack` into the first JSON object. If present, the value must be a
  string, parseable, and at or above the same minimum major/minor line used by the pack
  reader; malformed, non-string, or below-floor values refuse only that row as
  `containment_refused` / `staged_version_unestablished`. Valid patch-level differences
  remain legal and are preserved. A reality-shaped nested
  `subagents/workflows/wf-a/...` round trip proves the admitted session reappears.
- G-4 — Claude unattributed alias union: alias harvest now includes JSONL anywhere below
  `subagents/` as well as child-attributed artifacts, and the image union receives every
  subagent alias even when no manifest child attributes it. Child mapping remains
  attribution-only. The unattributed nested-subagent falsifier proves the alias is
  needled; the existing attributed-history falsifier proves that path did not regress.

The operative E1 ruling was preserved: the Claude identity guard was not weakened.

## RED/GREEN and independent review

- The first pre-implementation G cohort made G-2, G-3, and G-4 RED while the original
  G-1 fixture still passed, reproducing the four dispatched gaps.
- After the initial fold, the G cohort passed: 159 assertions across five cases.
- The first independent review found two Major gaps: G-3 accepted stale/ill-typed existing
  versions, and G-4 regressed child-attributed history alias harvesting. New regressions
  were demonstrated RED before their fixes.
- Exact equality for G-3 was rejected after Linux exposed it as too strict for the legal
  patch-level mismatch already accepted by pack semantics; the final check uses the same
  parse-and-minimum-line rule as the reader.
- At exact final head `8b12b25`, `G-*` passes 182 assertions across seven host cases.
  Adding the two existing legal patch-mismatch controls passes 202 assertions across
  nine cases. Linux `G-*` passes 173 assertions across seven cases (the assertion-count
  difference is platform conditional, not a skip).
- The independent reviewer returned CLEAR at exact `8b12b25`: the 15-assertion
  stale/ill-typed G-3 control, 46-assertion existing host-mismatch control, and
  29-assertion consent-NO mismatch control all pass; no findings remain.

## Final macOS verification

At exact `8b12b25`, configure/build passed and the selected local suite produced:

- `biv_tests`: PASS in 336.35 seconds;
- open-no-rewrite, adapter purity, version-floor mirror, errno, probe-schema,
  generated-envelope, harness-selftest, and Werror: PASS;
- `harness-E2` CTest wrapper: the sole selected failure, ending at 190.04 seconds with no
  output at its timing boundary;
- the exact underlying E2 command, rerun from the required `harness/` working directory
  with the same final binary and schema/scenario inputs: exit 0, all 11 runnable scenarios
  PASS and six xfail-pending rows, with no failed or invalid row;
- ASan/UBSan, tidy/analyzer, and fuzz smoke: preset-configured skips.

The first direct-E2 attempt was invoked one directory too high and immediately failed
with `No module named bivharness`; it is not counted as test evidence. The corrected
working-directory run above is the recorded E2 result.

## Final Ubuntu 24.04 linux/amd64 Docker parity

A fresh detached exact-head checkout ran in an explicitly named disposable container
under Docker `--init --platform linux/amd64`. It verified Ubuntu 24.04, x86_64, Python
3.12.3, GCC 13.3, and all eight pinned LLVM 22 packages at exact version
`1:22.1.8~++20260613092238+e80beda6e255-1~exp1~20260613092253.78` on amd64.
Configuration required clang-tidy and selected `/usr/bin/clang-tidy-22`; build passed.

Canonical results:

- product: 346/347 cases and 9,494/9,495 assertions passed; the sole failure is the
  registered Docker/Rosetta invalid-executable spawn-semantic case
  `version probe does not fall back to PATH when a pinned executable cannot spawn`;
- harness: 969 passed, two registered Docker filesystem-mutation sentinels failed, three
  skipped;
- E2: PASS in 1.14 seconds;
- Werror: PASS in 1.58 seconds;
- LLVM 22 tidy: PASS in 42.33 seconds;
- hardening: PASS in 0.16 seconds;
- ASan/UBSan and fuzz smoke: configured skips;
- canonical selected total: 70.67 seconds; generated-envelope was dependency-blocked by
  the registered product exception.

Bounded controls passed:

- product excluding exactly the registered Rosetta case: 346/346 cases, 9,494
  assertions;
- harness excluding exactly the four established filesystem-mutation sentinels: 967
  passed, three skipped, four deselected;
- direct generated-envelope schema validation: PASS.

The full Linux product XML records 346 successes, one failure, zero expected failures,
and zero skips. The workflow's historical exact-count gate still expects 223/0 and is
stale against the current registered suite. `.github/**` is Hard OUT, so it was neither
edited nor invoked. No unrelated Docker resource was pruned or removed.

## Guarded publication receipt and remaining gates

Under the separate `154400` publication authority, preflight established remote B2
`20e56bc4053d4a27c4b47b6dbff0fc02af1dcc13`, PR #23 OPEN/DRAFT/base `main`, and PR #22
OPEN/DRAFT at exact C. The only external mutation was:

`git push --force-with-lease=s4-floor/b2-torn-tail:20e56bc4053d4a27c4b47b6dbff0fc02af1dcc13 origin HEAD:s4-floor/b2-torn-tail`

The lease succeeded. Postflight established:

- remote B2 and PR #23 head equal exact `8b12b25f38bbf0f8a400e1a9141ff9cea071f874`;
- PR #23 remains OPEN, DRAFT, and based on `main`;
- remote C and PR #22 remain exact `b8083be8529a97d1d3d5931a2c7b308335bbd09c`,
  OPEN, DRAFT, and based on `main`.

No PR title/body/base/label/reviewer mutation, undraft, GitHub Actions invocation or
inspection, merge, tag, deployment, seal, or release occurred.

Requested next action: convene the token-required targeted re-check on this exact fold
delta. On a clean disposition, issue the fresh paired hand-up; condition-3 and the
operator's paired condition-4 remain separate gates.

C never lands without B2 (A10.3).

The release hold is ABSOLUTE.

ACTIONS_GIT_REF: local and remote B2 `8b12b25f38bbf0f8a400e1a9141ff9cea071f874` atop exact C `b8083be8529a97d1d3d5931a2c7b308335bbd09c`; guarded force-with-lease updated only `origin/s4-floor/b2-torn-tail`; this report and its append-only INDEX row are the only docs-lane writes from this filing
FINAL_GIT_STATUS_SHORT: product worktree clean; shared docs checkout retains pre-existing sibling untracked state, preserved; this filing adds only the named report and its INDEX row

CARRY LIST:
- `.relays/s4/s4-floor-impl/REVIEW-FOLD-IMPLEMENTER-CB2-RECHECK-G1-G4-COMPLETE-PUBLISHED-20260810-170608.md` -> `s4-floor.planner`
- B2 `8b12b25` over byte-identical C `b8083be`; actual five-path fold; G-1..G-4 closed; independent review CLEAR
- host and Ubuntu amd64 evidence complete with registered exceptions and bounded controls disclosed; GitHub Actions untouched
- PR #23 remains OPEN/DRAFT at exact B2; PR #22 remains OPEN/DRAFT at exact C; no merge/seal/release
- C never lands without B2 (A10.3); release hold ABSOLUTE
