## AUDIT REPORT — s4-matrix.implementer / Step 4 matrix

ROLE: Implementer
PHASE: AUDIT
AUTHORITY: read-only
DISPATCH_ID: s4-matrix-audit
PARENT_DISPATCH_ID: s4-build-standup-step4-opening-dispatch
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no
FROM: s4-matrix.implementer
TO: s4.orchestrator-planner
CC: operator
IN_REPLY_TO: .relays/s4/s4-matrix-audit/AUDIT-ORCHESTRATOR-PLANNER-20260804-231720.md
RELAY_PATH: .relays/s4/s4-matrix-audit/AUDIT-IMPLEMENTER-20260804-233619.md
AUDIT_ARTIFACT: docs/sprints/2026-08-04-s4-step4/audits/s4-matrix-audit-implementer.md
BASE: 8981bfd0848039d533d9bb2a96301d4d81b564fa
BOUNDARY_CONTRACT: not applicable — read-only audit; no implementation boundary edits

Verdict: MUST-REVISE before implementation routing.

The Step 3 package identifies the two immediate code fences and the landed payload restore substrate, but it is not implementation-ready. It lacks an exhaustive DR-3 flip/retain/add ledger in the plan, an executable git golden contract, and collision-free ownership across the five matrix arms and A7 floor. Two further sealed-contract-to-payload gaps require orchestrator disposition: partial lifecycle inspection/cleanup and plan-time path representability.

Independence:
- This seat did not read the s4-matrix.planner audit artifact.
- All code claims below are pinned-blob reads from 8981bfd, not working-tree inference.
- The complete evidence ledger is filed in AUDIT_ARTIFACT; this relay is the routed report of record.

1. Step 3 fences:
- Fence 1 is `src/core/scan/scan.cpp:137-138`. After `.bivignore` pruning at lines 129-135 and before kind dispatch, basename equality with `.git` emits `RepoDiscoveredUnsupported`; file, directory, and symlink forms are covered when not ignored.
- An exact symbol search found one production construction site. The only production direct caller of `scan::scan` is `src/core/pack/pack.cpp:477`; failure returns at 478-480. The public pack boundary is 688-695 and the CLI pack call is `src/cli/main.cpp:207-220`. Production blast radius is library/CLI pack, not open/list/info; direct scanner tests are also affected.
- Fence 2 is `src/core/manifest/manifest.cpp:81-97`, called only at 597-600. Missing or empty `repos` passes; non-array fails parsing; populated array is refused as `step2-plain-dir-only`. Serialization hard-codes empty at 498-500 and `manifest.hpp:59-69` has no repository model.
- Adjacent Fence 2 population includes `open.cpp:220-240`, `harness/bivharness/manifest.py:69-83`, `tests/test_manifest.cpp:63-81,143-168`, envelope production/oracles, the manifest schema, fuzz corpora, stub, self-test, probe fixture, and every scenario artifact validated through `scenario.py:655-659`.
- The Addendum F then Arm 1 `manifest.cpp` then floor repos-adjacent ordering is a mandatory edit fence. It must be expanded to the shared header, tests, harness validator/schema, pack, report, and build registration surfaces.

2. Landed restore substrate and seams:
- `src/core/open/open.cpp:220-319` already owns manifest/checksum parsing, member accounting, and currently admits only `payload/` and `agents/`; `repos/` is unmanifested today.
- `open.cpp:443-602` owns contained paths, created-directory ancestry, file/dir/symlink apply, and agent separation.
- `open.cpp:604-675` owns collision refuse/rename, the one `<destination>.bvpk-open.partial` tree, residue semantics, reverse directory mtimes, fsync, and atomic rename.
- `src/core/archive/tar_reader.cpp:202-230,470-488` owns lexical archive-path safety. Existing `test_open.cpp` cases cover payload round-trip, collisions, partials, symlink-parent escape, and mid-apply residue.
- Arm 1 should extend the archive plan with validated repository members, admit only manifest-accounted checksummed `repos/<id>/...` members, materialize repository state inside the existing partial tree before its existing commit point, generalize artifact reads without agent assumptions, and extend OpenReport/envelopes. A second staging/finalization path would duplicate landed safety behavior.
- `support/probe.cpp:669-880` contains robust process-spawn/timeout/group-cleanup machinery but hard-codes `--version` at 715-721; `probe.hpp:73-83` sanctions only that probe. The plan must assign extraction of a generic argv runner or ownership of a separate git runner.
- Exact vocabulary probes found no production bundle/remote/ref/porcelain/submodule/quarantine/offline/repo-artifact engine. This is payload substrate plus future harness scaffolding, not a dormant git implementation.

3. DR-3 exhaustive fixture inventory:
- Population instrument: `git ls-tree -r --name-only 8981bfd -- tests harness fuzz schemas`, then exact searches for `"repos"`, both empty-array spellings, `step2-plain-dir-only`, item-limit vocabulary, indexing, and call sites.
- Must flip/expand: manifest model/parser/serializer; `tests/test_manifest.cpp:143-168` populated refusal; `harness/bivharness/manifest.py:81-82`; harness manifest self-tests; manifest item schema; envelope repository summaries and exact oracle when outcomes become reportable.
- Retain as valid empty-repository cases unless surrounding shape changes: `fuzz/corpora/manifest/seed1.json`, three compact harness fuzz corpora, stub, empty self-test golden, probe fixture, and the ten `manifest_variant` scenarios: open-collision-rename-projectkey, open-consent-no, open-consent-per-agent, open-consent-yes, open-deny-default, open-no-sessions-regression, open-store-locked, open-unknown-agent, plain-dir-v1, plain-dir-v2.
- Add: populated positive parse/serialize/schema tests, malformed-item negatives, repository member/accounting checks, and executable repository scenarios. Old empty fixtures must not be deleted; the populated-refusal oracle must not survive unchanged.

4. Golden harness:
- Existing: `harness/scenarios/shells/d-git-restore.json` is xfail with no steps; tolerance rows are marked future-step; the comparator recursively byte-compares all content including `.git`; fixture materialization supports only dir/file/symlink; scenario execution and archive/tree assertions are otherwise reusable.
- Missing: controlled git repository/remote fixture setup, populated repository-manifest validation, repository-member assertions, a semantic oracle for HEAD/branch/refs/porcelain/worktree plus explicit volatile-internal exclusions, repeat-pack determinism, round-trip comparison, and activation of the git shell/tolerance rows.
- `tests/test_open.cpp:263-278` is payload unit round-trip evidence, not a git golden contract.

5. Four-bucket arm matrix:

Arm 1 — single clean repository
- PRIMARY_BUCKET: still-open
- still-open: discovery/classification, repository schema, capture, membership, restore, remote/tip proof, reporting/errors, fixtures, and semantic golden evidence are absent.
- already-closed: payload staging, collision refuse/rename, tar/path safety, accounting, fsync/rename, and generic scenario execution are reusable substrate only.
- product-overlapped: landed payload pipeline and floor schema/pack/report/build surfaces.
- recommended-next: land Addendum F, decide runner ownership, freeze the DR-3 ledger, and plan Arm 1 around the existing partial-tree commit point.

Arm 2 — dirty state
- PRIMARY_BUCKET: still-open
- still-open: staged/unstaged/untracked capture/apply, attributes/filters/encoding/ident, unmerged refusal, gitlink dirt, artifacts, and tests are absent.
- already-closed: no dirty-repository behavior; byte/mode/symlink payload comparison is only reusable oracle substrate.
- product-overlapped: depends on Arm 1 classifier, runner, schema, pipeline, and semantic harness.
- recommended-next: sequence after Arm 1 and enumerate each Addendum B positive/refusal case.

Arm 3 — nested repositories
- PRIMARY_BUCKET: still-open
- still-open: nested discovery, IDs/kinds/parent links, parent exclusions, ordering, placement, outcomes, and fixtures are absent.
- already-closed: recursive payload traversal exists but rejects `.git`; it is not nested-repository support.
- product-overlapped: shares Arm 1 schema/engine and Arm 2 worktree exclusion semantics.
- recommended-next: sequence after Arm 2 with discovery population, exclusion boundary, parent linkage, and ordering in one contract.

Arm 4 — submodules/offline
- PRIMARY_BUCKET: still-open
- still-open: gitlink/`.gitmodules`, submodule capture/restore, bundle/remote proof, promisor/offline refusal, shallow/full-image modes, zero-git restore, and fixtures are absent.
- already-closed: none of the submodule/offline git behavior.
- product-overlapped: depends on Arm 3 hierarchy and Arm 1 command/artifact/restore boundaries; offline behavior is cross-cutting.
- recommended-next: sequence after Arm 3 and translate Addenda A/D into separate online, offline, shallow, promisor, and refusal fixtures.

Arm 5 — quarantine/closure
- PRIMARY_BUCKET: still-open
- still-open: quarantine, exclusion writing, failure outcomes, cross-arm invariants, full golden closure, and release evidence are absent.
- already-closed: `.biv` payload exclusion at `scan.cpp:140-141`, contained payload staging/residue, and unused tolerance scaffolding.
- product-overlapped: integrates every prior arm and shares report/error/harness surfaces.
- recommended-next: close after Arms 1-4, reuse the single partial tree, and keep the release hold absolute until the positive/refusal matrix is complete.

6. Matrix/floor collision ledger:
- Shared manifest ownership: `manifest.hpp`, `manifest.cpp`, `test_manifest.cpp`, harness manifest validator/self-test, and manifest schema.
- Shared pack ownership: `pack.cpp` repository capture versus floor live-at-pack/session-entry metadata; `src/adapters/codex/codex.cpp:391` currently hard-codes `live_at_pack=false`.
- Shared report/build/flow ownership: envelope implementation/test/schema, root CMake source/test registration, CLI orchestration, and `tests/test_cli.cpp:637-686` source-order oracle.
- Required sequence: Addendum F; Arm 1 repository schema act; floor repos-adjacent schema act; separately owned pack/report/build integration acts with rebases. Intent agreement does not authorize concurrent edits to the same file.

7. Drift beyond DR-1/DR-2/DR-3:
- Partial lifecycle gap: the sealed restore contract names partial detection and cleanup operations. `open.hpp:19-78` exposes no such operations. Existing code can refuse or leave residue, but callers cannot inspect/clean it through that interface; exact symbol probes are empty.
- Plan-time representability gap: the sealed contract requires case-collision/path-length/unrepresentable planning and rename mapping without probing. Pinned code has lexical tar/path containment, but exact probes found no implementation or tests for those plan-time classes.
- These are payload-contract gaps, unlike the absent repository engine, which is expected Step 4 work. No additional contradictory behavior was found in staging, member/checksum accounting, collision refuse/rename, containment, or atomic finalization.

Question to s4.orchestrator-planner:
- Should the two additional payload gaps be incorporated into Step 4 ownership, routed as pre-existing payload residuals, or explicitly accepted as prior-step deviations? This read-only audit does not amend sealed design.

Required gates before implementation:
- Orchestrator disposition of the two payload gaps.
- Addendum F before Arm 1 manifest implementation.
- Serial matrix/floor ownership for the complete collision ledger.
- DR-3 flip/retain/add fixture ledger.
- Executable git golden scenario and semantic comparator contract.
- Generic git command-runner ownership decision.
- Arm-by-arm plans retaining these four-bucket findings and the absolute release hold.

Actions:
- Filed only the authorized durable audit artifact, this gitignored report relay, and its append-only INDEX row.
- No source, test, build, configuration, branch, scratch, host-probing, commit, PR, or merge action was taken.

ACTIONS_GIT_REF: no code-baseline edits claimed; audit-only writes are docs/sprints/2026-08-04-s4-step4/audits/s4-matrix-audit-implementer.md plus this gitignored relay and its INDEX row
FINAL_GIT_STATUS_SHORT:
 M .gitignore
?? docs/

PATH_SCOPED_AUDIT_STATUS:
?? docs/sprints/2026-08-04-s4-step4/audits/s4-matrix-audit-implementer.md

RELAY_LINT: OK — exact-file author-side freshness lint
INDEX_LINT: ERROR — sibling timestamp 20260804-231954 follows this seat's 20260804-232033 boot row; preserved as append-only shared history; this audit row was appended at the then-visible tail

CARRY LIST:
- docs/sprints/2026-08-04-s4-step4/audits/s4-matrix-audit-implementer.md -> s4.orchestrator-planner
