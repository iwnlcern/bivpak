# S4 Step 4 matrix audit — Implementer seat

## Audit identity

- Seat: `s4-matrix.implementer`
- Phase / authority: AUDIT / read-only
- Dispatch: `.relays/s4/s4-matrix-audit/AUDIT-ORCHESTRATOR-PLANNER-20260804-231720.md`
- Dispatch SHA-256: `a89383b2821e286f110014626c721b0364b64bb3230c77d457719560e92001f8`
- Pinned source baseline: `8981bfd0848039d533d9bb2a96301d4d81b564fa` (`main`, `origin/main`)
- Independence: this audit did not read the `s4-matrix.planner` audit artifact.
- Boundary contract: not applicable; this was a read-only audit and made no implementation boundary edits.

## Verdict

**MUST-REVISE before implementation routing.** The Step 3 package correctly identifies the two immediate code fences and the landed payload-restore substrate, but it does not yet provide an implementation-ready exhaustive fixture ledger, a usable git golden harness, or collision-free ownership across the five matrix arms and the A7 floor. Two additional sealed-contract-to-payload gaps also need an explicit disposition: partial-lifecycle inspection/cleanup and plan-time path representability.

This verdict does not reopen DR-1, DR-2, or DR-3. It narrows the remaining work and records the exact E1 evidence needed for the next design/plan pass.

## 1. Step 3 fences

### Fence 1 — scanner rejection

The operative rejection is `src/core/scan/scan.cpp:137-138`: after `.bivignore` pruning at lines 129-135 and before file-kind dispatch, any directory entry whose basename is exactly `.git` emits `RepoDiscoveredUnsupported`. The criterion is basename equality, so it covers file, directory, and symlink forms that survive ignore pruning.

`git grep -n -F RepoDiscoveredUnsupported 8981bfd -- src tests schemas README.md .bivignore` found one production construction site, `src/core/scan/scan.cpp:138`. The other matches are the enum/string/report mapping, schema/docs, and tests. The only production direct caller of `scan::scan` is `src/core/pack/pack.cpp:477`; scan failure is returned at lines 478-480. The public pack entry is `src/core/pack/pack.cpp:688-695`, and the CLI invokes it at `src/cli/main.cpp:207-220`. Therefore the production blast radius is every library/CLI pack traversal that encounters an unignored `.git`; open/list/info are not on this call path. Direct scanner tests are also affected.

The error maps through `src/core/report/envelope.cpp:381-411` to the refusal class recorded in `schemas/exit-map-v1.json:5`. Arm 1 must replace this single rejection point with repo discovery/classification while retaining the existing ignore-order semantics.

### Fence 2 — manifest `repos` rejection

The operative parser gate is `src/core/manifest/manifest.cpp:81-97`, called only at lines 597-600. A missing field or empty array is accepted; a non-array is a parse error; a non-empty array is refused with detail `step2-plain-dir-only`. `git grep -n -F require_empty_array 8981bfd` found only the definition and that call.

The adjacent blast radius is larger than that one function:

- `src/core/manifest/manifest.hpp:59-69` has no repository model member.
- `src/core/manifest/manifest.cpp:498-500` serializes `repos` unconditionally as empty.
- `src/core/open/open.cpp:220-240` parses the manifest before planning archive members.
- `harness/bivharness/manifest.py:69-83` independently rejects populated `repos` at lines 81-82.
- `tests/test_manifest.cpp:143-168` deliberately mutates `repos` to `[1]` and pins the refusal detail at lines 163-167.
- `tests/test_manifest.cpp:63-81`, `tests/test_envelope.cpp:448-471`, `src/core/report/envelope.cpp:72-121`, and `harness/fixtures/probe-only/archive/manifest.json:64-67` pin empty repository summaries or arrays.

Arm 1 and the A7 floor both touch this schema neighborhood. The prescribed sequencing—Addendum F before Arm 1 enters `manifest.cpp`, then the floor repos-adjacent act after the Arm 1 schema act—is a real collision fence, not merely scheduling advice.

## 2. Landed payload-restore substrate and exact seams

The payload restore base is substantial and should be extended rather than replaced:

- `src/core/open/open.cpp:220-319` parses the manifest/checksums, enforces archive-member accounting, and currently admits only `payload/` and `agents/`; a `repos/` member is therefore `UnmanifestedMember` today.
- `src/core/open/open.cpp:443-477` enforces contained payload paths and created-directory ancestry, preventing traversal through a created symlink.
- `src/core/open/open.cpp:479-602` applies directories/files/symlinks and separates agent replay.
- `src/core/open/open.cpp:604-675` owns destination collision handling, the single `<destination>.bvpk-open.partial` staging tree, reverse directory mtimes, fsync, and atomic final rename.
- `src/core/archive/tar_reader.cpp:202-230,470-488` rejects unsafe archive paths before application.
- `tests/test_open.cpp:263-338,379-426,476-520` already cover payload round-trip, collision refusal/rename, occupied/pre-existing partials, created-symlink parent escape, and mid-apply residue.

The Arm 1 seams are correspondingly narrow:

1. Extend the internal archive plan with validated repository descriptors and members.
2. Admit checksummed `repos/<repo-id>/...` members only when the manifest accounts for them.
3. Materialize repository state inside the existing partial tree before its existing fsync/rename boundary. A second staging or finalization mechanism would duplicate landed safety semantics.
4. Generalize the artifact-reader seam used for archive members so bundle and patch artifacts do not inherit agent-specific assumptions.
5. Extend `OpenReport` and the envelope with repository outcomes.

One implementation dependency is unresolved. `src/core/support/probe.hpp:73-83` sanctions only a pinned, shell-free `<binary> --version` probe. `src/core/support/probe.cpp:669-880` contains reusable `posix_spawn`, pipe, timeout, and process-group cleanup machinery but hardcodes `--version` at lines 715-721. The design/plan must decide whether to extract and test a generic argv runner or introduce a separately owned git runner; silently duplicating this machinery would create two process-safety implementations.

Pinned vocabulary searches over `src/`, `tests/`, `harness/`, and `schemas/` found no production implementation of `git bundle`, `ls-remote`, `merge-base`, porcelain capture, submodule restore, quarantine, `GIT_NO_LAZY_FETCH`, repo bundles, repo patches, `capture_mode`, `local_refs`, or `repos/`. The landed state is therefore payload substrate plus future harness scaffolding—not a hidden, flagged, or partially active git engine.

## 3. DR-3 fixture and oracle ledger

### Population and instrument

The population was enumerated from the pinned blob with `git ls-tree -r --name-only 8981bfd -- tests harness fuzz schemas`, followed by exact `git grep -n -F` probes for `"repos"`, `"repos": []`, `"repos":[]`, `step2-plain-dir-only`, `maxItems`, `minItems`, and manifest indexing/call sites. This is the denominator for the ledger; it is not inferred from token counts or the working tree.

### Must flip or expand for populated repositories

- `src/core/manifest/manifest.cpp:81-97,498-500,597-600`: replace empty-only parsing/serialization with the Arm 1 repository schema.
- `src/core/manifest/manifest.hpp:59-69`: add the repository model.
- `tests/test_manifest.cpp:143-168`: replace the populated-array refusal oracle with positive parsing plus malformed-item rejection. Retain an explicit negative-schema case.
- `harness/bivharness/manifest.py:69-83`: replace the empty-array assertion with repository item validation.
- `harness/selftest/test_manifest.py:1-27`: add explicit populated positive and malformed negative coverage; current tests exercise only empty arrays.
- `schemas/manifest-v1.schema.json:14,34`: its array type is already compatible, but it needs the sealed item shape and constraints; there is no current `maxItems`/`minItems` rule.
- `src/core/report/envelope.cpp:72-121` and `tests/test_envelope.cpp:448-471`: expand the hard-coded empty repository summary and its exact oracle when repository outcomes become reportable.

### Retain as valid empty-repository fixtures unless their surrounding shape changes

- `fuzz/corpora/manifest/seed1.json:14`.
- The three compact harness fuzz corpora containing `"repos":[]`.
- `harness/stub_biv.py:71`, the current empty-repository self-test golden, and `harness/fixtures/probe-only/archive/manifest.json:64-67`.
- The ten scenario specifications using `manifest_variant`: `open-collision-rename-projectkey`, `open-consent-no`, `open-consent-per-agent`, `open-consent-yes`, `open-deny-default`, `open-no-sessions-regression`, `open-store-locked`, `open-unknown-agent`, `plain-dir-v1`, and `plain-dir-v2`. They all pass through `harness/bivharness/scenario.py:655-659`; their payload-only manifests remain legitimate empty-repository cases.

The ledger must be carried into the implementation plan as explicit flip/retain/add rows. Deleting the old empty fixtures would lose payload-only coverage; leaving the populated-refusal oracle unchanged would preserve DR-3.

## 4. Golden harness readiness

The generic harness is reusable, but no executable git golden contract exists yet.

Existing pieces:

- `harness/scenarios/shells/d-git-restore.json:1-8` is an `xfail` pointer with no steps.
- `harness/tolerance/tolerance-v1.json:4-13` has future-step rows for git object IDs, index internals, and remote configuration; they are not reachable policy behavior.
- `harness/bivharness/compare.py:27-40,72-110` recursively byte-compares the whole tree, including `.git`, and does not interpret the git tolerance rows.
- `harness/bivharness/fixtures.py:32-60` can materialize only directories, files, and symlinks.
- `harness/bivharness/scenario.py:441-590,645-666` provides scenario setup, pack/open execution, and manifest/checksum/member/tree assertions.
- `harness/CMakeLists.txt:30-52` executes self-tests and scenarios; `plain-dir-v1/v2` are working end-to-end templates.

Missing for Arm 1 day-one proof:

1. Fixture grammar/setup that initializes a repository, commits content, and creates stable reachable remote/tip evidence under a controlled git environment.
2. Populated repository-manifest item validation and explicit repository-member assertions.
3. A semantic git oracle for `HEAD`, branch/refs, porcelain state, worktree bytes/modes/symlink targets, plus explicit acceptable-difference exclusions for volatile `.git` internals.
4. Repeated-pack/determinism and pack-open-round-trip checks.
5. Activation of the `d-git-restore` scenario and only the tolerance rows actually consumed by comparison.

`tests/test_open.cpp:263-278` is useful unit-level payload round-trip evidence, but it is not the required git golden contract.

## 5. Arm-by-arm four-bucket matrix

### Arm 1 — single clean repository

- `PRIMARY_BUCKET: still-open`
- `still-open:` discovery/classification, repository manifest model, capture, archive membership, restore, remote/tip proof, reporting, errors, fixtures, and semantic golden contract are absent at E1. Likely target surfaces are `src/core/scan/scan.{hpp,cpp}`, `src/core/pack/pack.{hpp,cpp}`, `src/core/manifest/manifest.{hpp,cpp}`, `src/core/open/open.{hpp,cpp}`, support/error/report layers, CLI option plumbing, schemas, tests, harness, and build registration.
- `already-closed:` payload staging, collision refuse/rename, tar/path containment, checksum/member accounting, fsync/rename finalization, and generic scenario execution are landed and tested. They are substrate, not proof of git behavior.
- `product-overlapped:` Arm 1 extends the landed payload pipeline and collides with the A7 floor in the manifest model/parser/serializer/tests/harness schema, pack metadata, envelope/report schema, and build registration.
- `recommended-next:` land Addendum F, choose the generic git-command runner boundary, freeze the DR-3 ledger, then write a sequenced Arm 1 plan that uses the existing partial-tree commit point.

### Arm 2 — dirty state

- `PRIMARY_BUCKET: still-open`
- `still-open:` staged/unstaged/untracked capture and apply, attribute/filter/encoding/ident behavior, unmerged-index refusal, gitlink dirt accounting, archive artifacts, and tests are absent.
- `already-closed:` no dirty-repository behavior is closed. Existing byte/mode/symlink payload comparison can be reused only for worktree portions of the oracle.
- `product-overlapped:` depends on Arm 1 classifier, runner, repository schema, capture/apply pipeline, and semantic harness. No existing feature closes the Arm 2 contract.
- `recommended-next:` plan only after Arm 1’s engine and golden contract are stable; enumerate Addendum B cases as explicit positive/refusal fixtures rather than a single “dirty repo” test.

### Arm 3 — nested repositories

- `PRIMARY_BUCKET: still-open`
- `still-open:` nested-repository discovery, parent/child IDs and kinds, parent capture exclusions, deterministic ordering, nested restore placement, outcomes, and fixtures are absent.
- `already-closed:` the scanner recursively traverses payload entries, but it currently rejects `.git`; this is traversal substrate, not nested-repository support.
- `product-overlapped:` shares the Arm 1 manifest/engine and the Arm 2 worktree exclusion model. It will collide with those arms if parent exclusions and ordering are added independently.
- `recommended-next:` sequence after Arm 2 and specify the discovery population, exclusion boundary, parent linkage, and deterministic ordering as one contract.

### Arm 4 — submodules and offline behavior

- `PRIMARY_BUCKET: still-open`
- `still-open:` gitlink/`.gitmodules` discovery, submodule capture/restore, bundle and remote proof, promisor/offline refusal, shallow/full-image modes, zero-git restore, and fixtures are absent.
- `already-closed:` no submodule/offline git behavior is closed at E1.
- `product-overlapped:` depends on Arm 3 hierarchy and Arm 1’s command/artifact/restore boundaries; offline restore also cuts across the entire repository pipeline.
- `recommended-next:` sequence after Arm 3 and convert Addenda A/D cases into separate online-capture, offline-restore, shallow, promisor, and refusal fixtures with explicit tool-availability assumptions.

### Arm 5 — quarantine and full closure

- `PRIMARY_BUCKET: still-open`
- `still-open:` repository quarantine, exclusion writing, failure outcomes, cross-arm invariants, full matrix golden closure, and release evidence are absent.
- `already-closed:` `src/core/scan/scan.cpp:140-141` excludes `.biv` from payload scanning, and the payload restore base already has contained staging/residue behavior. The tolerance file is scaffolding only.
- `product-overlapped:` integrates all prior arms and shares report/error/harness surfaces; implementing quarantine earlier would risk creating a second staging/finalization path.
- `recommended-next:` keep as the closure arm after Arms 1-4, reuse the single payload partial tree, and require a complete positive/refusal matrix before lifting any release hold.

## 6. Matrix/floor collision ledger

The design’s named `manifest.cpp` fence is necessary but not exhaustive. The following shared surfaces require one owner and a serial landing order:

- `src/core/manifest/manifest.hpp`, `src/core/manifest/manifest.cpp`, `tests/test_manifest.cpp`, `harness/bivharness/manifest.py`, `harness/selftest/test_manifest.py`, and `schemas/manifest-v1.schema.json`: matrix repository records versus floor `entry_schema` / `archive_only` evolution.
- `src/core/pack/pack.cpp`: matrix repository capture versus floor live-at-pack/session-entry metadata. Current session construction is around lines 403-405 and warning/report behavior around line 563.
- `src/adapters/codex/codex.cpp:391`: currently hard-codes `live_at_pack=false`, so the floor’s classification change is adjacent to matrix pack orchestration.
- `src/core/report/envelope.cpp`, `tests/test_envelope.cpp`, and the envelope schema: both tracks add outcomes/fields.
- Root `CMakeLists.txt:49-66,99-123`: both tracks may register sources/tests.
- `src/cli/main.cpp` and `tests/test_cli.cpp:637-686`: repository orchestration/options and session installation can alter the same command flow and source-order oracle.

The collision-safe route is: Addendum F; Arm 1 repository schema act; floor repos-adjacent schema act; then separately owned pack/report/build integration acts with rebases between them. Equality of intent is not authority to edit the same file concurrently.

## 7. Drift beyond DR-1/DR-2/DR-3

Two additional gaps are visible between the sealed restore contract and the pinned payload implementation:

1. **Partial lifecycle gap.** The restore contract names `detect_partial` and `clean_partial`; `src/core/open/open.hpp:19-78` exposes collision/options/report/plan/open operations but no inspection or cleanup primitive. `open.cpp` can refuse a pre-existing partial and leave failed residue, and tests pin those behaviors, but callers cannot inspect or clean it through the sealed interface. Exact symbol searches over the pinned source/tests/harness are empty.
2. **Plan-time representability gap.** The contract requires plan-time case-collision and path-length/unrepresentable checks plus rename mapping without probing. The pinned code has strong lexical tar-path and created-parent containment, but exact searches found no `PathUnrepresentable`, case-insensitive collision, path-length, `rename_map`, or `no_probe` implementation/tests.

These are payload-contract gaps, unlike the absent repository engine, which is expected still-open Step 4 work. No additional contradictory landed behavior was found in staging, checksum/member accounting, collision refuse/rename, lexical containment, or atomic finalization.

**Question for `s4.orchestrator-planner`:** should these two gaps be incorporated into Step 4 ownership, routed as pre-existing payload residuals, or explicitly accepted as prior-step deviations? This audit does not amend a sealed design.

## 8. Required gates before implementation

1. Orchestrator disposition of the two additional payload gaps.
2. Addendum F landed before Arm 1 edits `manifest.cpp`.
3. An explicit Arm 1/floor serial ownership map covering every collision above, not just `manifest.cpp`.
4. A DR-3 fixture ledger with flip/retain/add rows and exact instruments.
5. A real git golden scenario and semantic comparator contract.
6. A generic git command-runner ownership decision.
7. Arm-by-arm plans that preserve the four-bucket findings and the absolute release hold.

No source, test, build, configuration, branch, scratch, or host-probing action was taken by this audit seat.

## Verification and workspace attribution

- Exact relay lint: `OK .relays/s4/s4-matrix-audit/AUDIT-IMPLEMENTER-20260804-233619.md`.
- Shared INDEX lint: failed because the sibling row timestamp `20260804-231954` follows this seat's earlier `20260804-232033` boot row. The append-only historical defect was preserved; this audit's `20260804-233619` row was appended at the then-visible tail, and later sibling rows may follow it.
- Path-scoped status: `?? docs/sprints/2026-08-04-s4-step4/audits/s4-matrix-audit-implementer.md`.
- Root status: pre-existing ` M .gitignore` and aggregate `?? docs/`; this seat claims only the path-scoped audit file within that aggregate. Relay and INDEX paths are ignored by `.gitignore:2`.
