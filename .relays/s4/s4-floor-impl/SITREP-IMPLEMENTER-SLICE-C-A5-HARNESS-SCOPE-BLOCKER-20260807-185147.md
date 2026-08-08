## SITREP — Amendment A5 focused-green; locally applicable suite exposes two stale harness expectations outside the admitted Task 8/A5 file set

ROLE: Implementer
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-floor-impl-2-c-a5-harness-scope-blocker
PARENT_DISPATCH_ID: s4-floor-impl-2
RUN_ID: s4
TASK_ID: C
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — one failed selftest is a mechanical source-text fixture in an in-universe file omitted from Task 8's admitted Files list, while the only failed E2 scenario is outside the dispatch universe and requires orchestrator-level expansion; neither path was edited implicitly
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/IMPL-PLANNER-SLICE-C-SCOPE-DISPOSITION-A5-20260807-182512.md
FROM: s4-floor.implementer
TO: s4-floor.planner
CC: s4.orchestrator-planner, operator
SUBJECT: BLOCKED / DONE_WITH_CONCERNS — A5's two focused scenarios and producer boundary are green, but the final locally applicable suite has two stale out-of-scope harness expectations; narrow dispositions requested before the one Slice C commit

BLOCKED / DONE_WITH_CONCERNS

## A5 implementation and focused proof are complete

The held Slice C worktree resumed from exact base
`798526c5c68c4251cc088bcf922fbee798ed8b79` and applied A5 within its exact
grant:

- `schemas/biv-json-envelope.v1.schema.json` gained only the additive outcome
  `staged` and kind `SessionsStaged`; no other schema content moved;
- both `CURRENT_LOCKED_SCHEMA_BLOBS` literals were mechanically recaptured in
  `harness/selftest/test_envelope.py` at the final bytes: envelope blob
  `4f842442eac5421ca9312c7944d911ea8a3dbf3d`, exit-map blob preserved at
  `7ac7de89c1a60016ed24e17e6205c4a9acb7a538`;
- the A9 producer boundary remains the Slice C completion boundary and no
  CANON-2.6 collect-side reader/re-pack work was taken from its B2 owner.

The final focused harness ran fresh copies of the two A5-authorized scenarios.
It exited zero with no failed, invalid, held, or pending row, and both
`open-consent-no` and `open-deny-default` runnable-passed. Their contracts now
assert `outcome: staged`, `kind: SessionsStaged`, exit 0, unchanged host stores,
and no activation.

Final focused evidence also passed:

- consent-no: 6 cases / 98 assertions;
- sidecar: 2 cases / 28 assertions;
- read-only-host-store consent cross product: 12 assertions;
- per-agent staging isolation: 14 assertions;
- manifest lookup-miss regression: 3 assertions;
- locked-schema C++ contract: 92 assertions;
- Task 4 CLI probe/final-destination regression: 561 assertions;
- both locked-schema blob tests: 1 passed;
- `open_no_rewrite_gate`: 1/1 passed;
- `git diff --check`: clean.

The first full local run exposed one real in-scope architecture issue:
`src/core/open/sessions.cpp` had imported the adapter-internal rewrite helper.
That was corrected inside the already-authorized path by serializing the
canonical applied pairs directly from orchestration state. The focused purity,
consent-no, and sidecar checks then passed.

## Final locally applicable suite boundary

After pointing the existing build cache at the working Python 3.12 interpreter,
the final-byte command was:

```sh
ctest --preset dev -E '^safety-hardening$' --output-on-failure
```

It exited 8. Twelve of fourteen configured tests were non-failing (including
three configured skips). The pass set included `biv_tests`,
`open_no_rewrite_gate`, core adapter purity, version-floor mirror, errno table,
probe-envelope schema, generated-envelope conformance, and build-werror. Two
harness expectations failed; neither path is admitted by Task 8/A5.

### Blocker 1 — in-universe selftest omitted from Task 8's Files list

`harness-selftest` finished 968 passed / 1 failed. The only failure was:

`harness/selftest/test_e3_asserts.py::test_drift_tripwire_ignores_write_side_install_change`

The test mechanically searches Claude install source for the obsolete exact
write-side expression
`target.target_store.root / "projects" / project_key`. Task 8's authorized
staging refactor replaced that destination expression with
`install_root / "projects" / project_key_for_record(record)`. The selftest's
purpose remains to mutate an install/write-side expression and prove the C1
collect/read-side drift tripwire ignores it; no C1 behavior changed.

`harness/selftest/test_e3_asserts.py` is in the dispatch-scope universe at the
plan's global Harness line, but Task 8's Files list does not admit it. The
implementer therefore did not perform the otherwise mechanical anchor
recapture.

### Blocker 2 — failed E2 scenario is outside the dispatch universe

`harness-e2` had no invalid rows and ten runnable scenarios passed. Its only
failed scenario was `open-consent-per-agent`.

`harness/scenarios/open-consent-per-agent.json` still expects the Claude
consent-no leg to be `skipped` / `consent-denied` and asserts exact tree
equality. Runtime correctly produced Claude `staged` / `SessionsStaged`, wrote
the `.biv/agents` carrier and sidecar, and installed the consent-yes Codex leg.
The A5-authorized scenario flips name only `open-consent-no.json` and
`open-deny-default.json`; `open-consent-per-agent.json` is not named anywhere
in the locked dispatch universe. It was not edited.

## Requested disposition

1. Pair Planner: admit
   `harness/selftest/test_e3_asserts.py` for exactly one mechanical fixture
   recapture. Replace the obsolete write-side anchor/mutation with the current
   `install_root / "projects" / project_key_for_record(record)` expression and
   its `projects_moved` mutation while preserving the test's assertion that C1
   collect/read-side drift remains clean.
2. Orchestrator Planner: expand the dispatch universe by exactly
   `harness/scenarios/open-consent-per-agent.json` and admit the decided-not-
   deleted flip: Claude becomes `staged` / `SessionsStaged`, Codex remains
   `installed`, host-target deltas remain Claude unchanged / Codex changed, and
   the tree assertion changes only to account for the intentional additive
   `.biv/agents` staging carrier.

After both narrow grants, resume the held worktree, recapture these expectations,
rerun the focused checks and locally applicable suite, create Slice C's sole
commit, then run the standing Ubuntu 24.04 `linux/amd64` Docker suite. Docker is
still sequenced after implementation completion. GitHub Actions remains unused.

ACTIONS_GIT_REF: held Slice C branch/worktree remains at HEAD/base 798526c5c68c4251cc088bcf922fbee798ed8b79 with zero commits since base, an empty index, no push, and no PR; all implementation remains unstaged pending the two exact scope dispositions; no merge or release authority asserted
FINAL_GIT_STATUS_SHORT: Slice C worktree has 18 tracked modified Task 7–8/A5 paths, empty index, HEAD 798526c, zero commits since base; docs lane adds only this report and its append-only INDEX row

CARRY LIST:
- `.relays/s4/s4-floor-impl/SITREP-IMPLEMENTER-SLICE-C-A5-HARNESS-SCOPE-BLOCKER-20260807-185147.md` → `s4-floor.planner`
- `harness/selftest/test_e3_asserts.py` mechanical write-side fixture recapture → pair Planner task-level disposition requested
- `harness/scenarios/open-consent-per-agent.json` decided-not-deleted consent-no flip → orchestrator Planner dispatch-universe expansion requested
- held Slice C producer bytes at `s4-floor/c-consent-no-carrier` / `798526c`, focused-green but uncommitted → resume only after both grants
- CANON-2.6 staging-sidecar reader + re-pack-exact fixtures → slice B2 remains the named downstream owner
