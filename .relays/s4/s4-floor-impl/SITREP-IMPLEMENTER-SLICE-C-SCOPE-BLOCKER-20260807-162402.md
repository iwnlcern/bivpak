## SITREP — Slice C producer implementation focused-green; mandatory staged wire is blocked by envelope-schema scope, CANON-2.6 consumer remains outside the locked file set

ROLE: Implementer
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-floor-impl-2-c-scope-blocker
PARENT_DISPATCH_ID: s4-floor-impl-2
RUN_ID: s4
TASK_ID: C
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — the locked Task 7–8 file set requires a new serialized `staged` / `SessionsStaged` row but omits `schemas/biv-json-envelope.v1.schema.json`; the existing envelope-schema lock also cannot be recaptured under the exit-map-only A2 grant. A separate disposition is also required for CANON-2.6's collect-side consumer proof.
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/IMPL-PLANNER-PUBLICATION-GO-LOCAL-DOCKER-CI-20260807-154413.md
FROM: s4-floor.implementer
TO: s4-floor.planner
CC: s4.orchestrator-planner, operator
SUBJECT: BLOCKED / DONE_WITH_CONCERNS — Slice A published exactly at 798526c; Slice C Tasks 7–8 producer is focused-green but uncommitted because the mandatory staged envelope is schema-invalid under the locked scope

BLOCKED / DONE_WITH_CONCERNS

## Slice A publication completed first

- `s4-floor/a-floor-core` was force-updated under the exact immutable lease from remote `26e6eb1fbe57401e9ed3c931a57f0d8863d96fd6` to `798526c5c68c4251cc088bcf922fbee798ed8b79`.
- PR #21 now resolves to exact head `798526c5c68c4251cc088bcf922fbee798ed8b79`.
- Its body points to `SITREP-IMPLEMENTER-SLICE-A-LOCAL-LINUX-CI-20260806-160811.md` and discloses the Docker Desktop/Rosetta limitations, narrow exclusion controls, stale `.github` count gate, and absence of native GitHub x86_64 proof.
- No GitHub Actions run was invoked or managed. Merge and release remain held.

## Slice C checkpoint state

Slice C was seeded in an isolated worktree and branch `s4-floor/c-consent-no-carrier` from exact `798526c`. Task 7 reached its required uncommitted checkpoint and received an independent clean spec/quality review with no Critical, Important, or Minor findings.

Task 8 then implemented, test-first, the authorized producer side:

- consent-no Codex stages install-ready bytes under the sealed dated `<WS>/.biv/agents/codex/sessions/YYYY/MM/DD/…` layout;
- consent-no Claude stages beneath `<WS>/.biv/agents/claude-code/projects/<original-path-key>/…`, while transcript contents rewrite the packed path to the final workspace;
- both legs use the shared mint, read, pair-set rewrite, verify, and secure no-replace pipeline;
- a read-only host store does not block consent-no, while consent-yes retains `store_locked`;
- one orchestration writer aggregates successful staged sessions across agents into `<WS>/.biv/agents/manifest.json` with only `id_map`, original provenance-chain, and applied pair-set content;
- per-agent failure isolation is retained;
- sidecar publication failure converts otherwise staged rows to existing `session_install_failed` divergence, preserves/discloses already-published staged byte paths, and does not delete them;
- the two consent-no harness scenarios were flipped in place from `skipped` / `consent-denied` to `staged` / `SessionsStaged` while retaining host-store-unchanged controls;
- only the exit-map locked blob was mechanically recaptured, to Git blob `7ac7de89c1a60016ed24e17e6205c4a9acb7a538`.

The implementation worktree remains intentionally uncommitted at base/HEAD `798526c5c68c4251cc088bcf922fbee798ed8b79`: zero commits since base, empty index, 17 tracked modified paths. No push, PR, Docker suite, remote CI, merge, release, or deployment followed the blocker.

## Focused GREEN evidence

- `*consent-no*`: 6 cases / 98 assertions passed.
- `*sidecar*`: 2 cases / 28 assertions passed.
- read-only-host-store consent cross-product: 12 assertions passed.
- per-agent failure isolation: 14 assertions passed.
- Task 7 fail-closed lookup-miss regression: 3 assertions passed.
- exit-schema reserved-token test: 92 assertions passed.
- CLI probe/final-destination regression: 561 assertions passed.
- `test_vendored_schema_artifacts_match_current_locked_bytes`: 1 passed after the exit-map-only recapture.
- `git diff --check`: clean.

The Task 8 TDD record includes expected RED then GREEN for both adapters' real staged bytes, persisted minted identities, path-pair rewrite/verify, the one sidecar publication, and sidecar-failure path disclosure.

## Blocking scope conflict 1 — mandatory staged row is invalid under the held envelope schema

Focused harness execution reaches the required runtime result in both flipped scenarios:

- `outcome = staged`;
- `kind = SessionsStaged`;
- exit 0;
- host stores unchanged;
- no activation.

Both scenarios are nevertheless `INVALID`, not runnable-green, because `schemas/biv-json-envelope.v1.schema.json` admits only the old outcome/kind vocabulary. The mandatory Task 7 wire change therefore cannot satisfy its consumer without modifying that schema.

The locked Task 7 `Files:` list names `envelope.cpp`, the exit-map schema, and the exit-map A2 recapture, but does not admit the envelope schema or its locked-blob recapture. The implementation correctly stopped before either OUT edit and before the one Slice C commit.

## Blocking scope conflict 2 — CANON-2.6 actual re-pack consumption is collect-side

CANON-2.6 requires re-packing the staged workspace to consume the A9 sidecar and emit `locator: staging`, `tier: staged`, the original identity, and the minted staged identity. The current tree has no staging-sidecar reader. The real consumers would live in collect-side production files outside Task 8's authorized `install.cpp` + `sessions.cpp` set, and those files are assigned to later Slice B2/A3 ownership.

Task 8 therefore proves the exact A9 producer inputs only and does not claim actual re-pack consumption green. Widening into collect now would violate the slice file boundary, collide with the later owner, and trigger a separate A3 source-anchor act.

## Requested disposition

1. Admit `schemas/biv-json-envelope.v1.schema.json` for exactly the two additive enum values required by the already-locked row (`staged`, `SessionsStaged`), and admit the matching mechanical envelope-schema blob recapture in `harness/selftest/test_envelope.py` at the final same head. The existing exit-map-only recapture remains exact.
2. For CANON-2.6, choose one explicitly:
   - recommended: declare Slice C complete at the sealed A9 producer boundary and route actual collect/re-pack consumption to its named downstream owner; or
   - widen Slice C with the exact collect/test/A3-anchor file set and resolve the collision with Slice B2 before any such edit.

On the narrow schema grant plus a CANON-2.6 disposition, resume the held worktree, run the now-valid focused harness, complete the one Slice C commit, then run the standing local Ubuntu 24.04 `linux/amd64` Docker suite. GitHub Actions remains unused while quota is exhausted.

ACTIONS_GIT_REF: Slice A published at PR #21 exact 798526c5c68c4251cc088bcf922fbee798ed8b79; Slice C branch/worktree seeded from that exact head but still has zero commits and no remote branch; focused-green Task 7–8 producer edits remain unstaged and uncommitted pending the two scope dispositions; no merge/release authority asserted
FINAL_GIT_STATUS_SHORT: Slice C worktree has 17 tracked modified Task 7–8 paths, empty index, HEAD 798526c, zero commits since base; docs lane adds only this report and its append-only INDEX row

CARRY LIST:
- `.relays/s4/s4-floor-impl/SITREP-IMPLEMENTER-SLICE-C-SCOPE-BLOCKER-20260807-162402.md` → s4-floor.planner
- held Slice C worktree at `s4-floor/c-consent-no-carrier` / `798526c` with focused-green producer edits → resume only after schema + CANON-2.6 disposition
- envelope-schema additive values + matching one-literal blob recapture → exact narrow scope request
- CANON-2.6 collect-side consumer proof → downstream-owner declaration recommended; no implicit collect-file authority
