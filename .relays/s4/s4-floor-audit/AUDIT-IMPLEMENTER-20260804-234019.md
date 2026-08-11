# S4 Floor Independent Audit — Implementer Seat

ROLE: Implementer
PHASE: AUDIT
AUTHORITY: read-only
DISPATCH_ID: s4-floor-audit-implementer-report
PARENT_DISPATCH_ID: s4-floor-audit
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: yes — resolve the two locked-A7 integration contradictions and issue an implementation dispatch before product changes
FROM: s4-floor.implementer
TO: s4.orchestrator-planner
CC: operator, s4.orchestrator-reviewer, s4-floor.planner
SUBJECT: Independent implementation-floor audit against pinned bivpak baseline 8981bfd

## Verdict

The implementation floor is not closed at `8981bfd0848039d533d9bb2a96301d4d81b564fa` (tree `2204d426`). The following work remains live:

- R-W.1 / C1: both adapter version checks remain prefix-membership predicates; neither includes total order or the required typed refusal conjunction.
- R-VF.1 / R-VF.2 / R-VF.3: denied consent still short-circuits before adapter staging, both adapters' `Consent::no` paths are metadata-only, and the staged result maps to failure if it ever reaches session-row mapping.
- R-3.25(a): Codex liveness is hardcoded false. The Claude leg and shared propagation exist, but neither adapter has the required torn-final-line four-branch behavior.
- Locked A7: no version-floor/archive-only marker implementation exists, list/info are not implemented, and two cross-boundary contradictions require orchestration before planning.
- All 18 required A5/A7 receipt keys are absent from the pinned tree and remain carrier-marked `MUTATION REQUIRED AT SEAL`.

No product source, test, harness, schema, fixture, branch, build, or commit was changed by this audit.

## Pinned evidence

- Bivpak baseline: `8981bfd0848039d533d9bb2a96301d4d81b564fa`; tree `2204d426`.
- Locked A7: `../pdc/master/domains/m-2-agent-adapters/design/2026-07-21-ADDENDUM-7-version-floor.md`.
- Locked A7 SHA-256: `2e4020571d464b6a61d7d7eba3e7966987932494bb355b10bff4a8fb4b6624da`; lock identifier `2e402057` matches.
- Receipt carrier was read from committed PDC blob `ce9ef8c:master/domains/m-2-agent-adapters/audit/2026-07-13-rclass2-fixture-evidence-map.md`, not from mutable worktree bytes.
- Carrier blob SHA-256: `c2bcdc129a3e42f5507bd87b4aa9b613866088a5d0da42896c811bf09c5110f0`.
- Checkout movement observed during the audit: `docs/r-3.21-readme-git-scope@c953788a939bf08812a6eecc763650055ef86116`, then a concurrent switch/commit to `main@c118d15edb53081500df15478aa8eca0587fc68e`, then back to `docs/r-3.21-readme-git-scope@c953788a` while the final transport was filed. This seat did not change branches or commits. `c118d15` has `8981bfd` as its direct parent, and every product search used the explicit `8981bfd` treeish, so the audited bytes did not drift.

## Four-bucket audit

### 1. R-W.1 / C1 — version admissibility and refusal

PRIMARY_BUCKET: still-open

- `still-open`: `src/adapters/codex/install.cpp:194-196` accepts only prefixes `0.142.*` and `0.144.*`; `src/adapters/claude_code/install.cpp:331` accepts only `2.1.*`. Neither helper expresses literal membership plus valid grammar plus total order, so the required typed refusal conjunction is absent on both legs.
- `already-closed`: host probing already feeds parsed versions through `semver_at` before these predicates (`codex/install.cpp:198-245,273-310`; `claude_code/install.cpp:333-380,408-444`). Adapter dispatch and both install/probe call paths already exist.
- `product-overlapped`: the E3 harness mirrors the current accepted prefixes, so changing product predicates without the mirror is invalid. The external RUNCARD pin is a separate-repository coordination surface.
- `recommended-next`: fold C1 into the locked-A7 implementation, reuse the existing parser/probe path, add a total-order result and typed refusal, and update the mirror and RUNCARD under an explicitly coordinated gate.

Production call graph evidence:

- Probe leg: `src/cli/main.cpp` → `build_preview` → `find_adapter` → `adapter.capabilities` → adapter `probe_capabilities` → the predicate.
- Install leg: `src/cli/main.cpp` → `run_session_leg` → `adapter.install` → adapter `host_version_unverified_for_install` → the predicate.
- An exact production search found only these two predicate call sites per adapter. The host-probe basis is grammar-parsed; the image-manifest basis reaches the prefix predicate directly. Total ordering is absent on both paths.
- Exact searches at the pinned tree found no implementation vocabulary for `basis_newer_than_host`, `basis_unorderable`, `surveyed_through`, or `archive_only`.

### 2. R-VF.1 / R-VF.2 / R-VF.3 — consent-denied staging

PRIMARY_BUCKET: still-open

- `still-open`: `src/core/open/sessions.cpp:213-225` emits `sessions_consent_skipped` and continues before any adapter call, member read, identifier rewrite, or staging. `src/cli/main.cpp:339-388` contains no compensating staging operation.
- `still-open`: Codex `install.cpp:406-508` and Claude `install.cpp:533-659` perform byte reads, rewrites, and writes only within `Consent::yes`; their `Consent::no` branches return staged metadata and ID maps without staged carrier bytes or the required `.biv/agents/manifest.json` A9 sidecar.
- `still-open`: `src/core/open/sessions.cpp:297-327` maps an adapter `staged` outcome to `session_install_failed` at lines 323-325. That defect is latent only because orchestration currently calls adapters with `Consent::yes` exclusively (`sessions.cpp:260-265`).
- `already-closed`: consent is already modeled, both adapters have install and ID-remap machinery, the chosen skip row exits zero (`src/core/report/envelope.cpp:381-428`), and the yes-consent installation path already performs the sensitive transforms.
- `product-overlapped`: existing harness scenarios `open-consent-no.json` and `open-deny-default.json` encode the superseded short-circuit/target-unchanged behavior.
- `recommended-next`: preserve the current yes path, implement an install-ready staged carrier and A9 sidecar on denial, route the adapter call under `Consent::no`, and map the staged result to the locked chosen row/guidance with exit zero.

There is no `.biv/agents/manifest.json` occurrence in the pinned tree and no direct adapter `Consent::no` test.

### 3. R-3.25(a) — liveness and torn final lines

PRIMARY_BUCKET: still-open

- `still-open`: the only Codex assignment to `.live_at_pack` is the constant false at `src/adapters/codex/codex.cpp:391`. No Codex terminal-tail classifier or the disposed terminal-type vocabulary exists in production or tests.
- `already-closed`: Claude derives liveness from terminal status (`src/adapters/claude_code/claude_code.cpp:37-40,152-186,430`). Shared transport is already pure: `SessionRecord.live_at_pack` reaches the manifest in `src/core/pack/pack.cpp:386-405`, drives the default-visible pack warning at `pack.cpp:563-566`, is serialized/deserialized in `src/core/manifest/manifest.cpp:284-301,428-433`, and is copied into open/session rows.
- `still-open`: neither adapter implements the A3.3 four-branch torn-final-line behavior. Both stream raw source files into `artifact_sources`; pack then writes the raw bytes (`src/core/pack/pack.cpp:611-620`). Exact searches found no `torn_tail_dropped` implementation.
- `product-overlapped`: Codex torn-tail branch 3 depends on real Codex liveness first; implementing it independently would encode the wrong dependency order.
- `recommended-next`: land Codex terminal-tail derivation first, preserving pure shared propagation, then implement all four torn-tail branches per leg with branch-specific fixtures and exact raw-member assertions.

The disposed Codex rule is fail-closed: only the terminal tail types `task_complete`, `turn_aborted`, and `thread_rolled_back` are non-live; every other, missing, malformed, or truncated tail remains live, with one default-visible warning whose wording does not assert certainty.

### 4. Locked A7 — floor, watermark, archive-only compatibility

PRIMARY_BUCKET: still-open

- `still-open`: the locked minimum floors are Codex `0.142` and Claude `2.1`; the disclosure watermarks are Codex `0.144` and Claude `2.1`. The pinned product implements neither concept and must not conflate them.
- `still-open`: known versions at or above the minimum remain schema 1; below-floor sessions are omitted loudly; unknown-but-parseable versions require schema 2 with `agent_version_at_pack: "unknown"` plus `archive_only.reason: "unknown_version"`. The current `AgentSessionEntry` has no archive-only marker (`src/core/manifest/manifest.hpp:42-57`), and the writer always emits schema 1 (`manifest.cpp:375-434`).
- `already-closed`: manifest parsing already skips future entry schemas (`manifest.cpp:206-227`), member containment checks exist, adapter host probes exist, and the format has existing extension points without a top-level format-version bump.
- `product-overlapped`: `src/core/manifest/manifest.cpp` directly owns the `repos[]`-adjacent wire layout, so it is the explicit collision file. List/info rendering crosses the CLI/open/report boundary and is currently rejected as `NotYetImplemented` (`src/cli/main.cpp:390-394`).
- `recommended-next`: resolve the two contradictions below, then sequence pack classification, manifest marker/compatibility, open gating, render/exit-map changes, and same-revision harness evidence. Do not invent compatibility or commit semantics inside an implementation pair.

Locked-A7 integration contradictions requiring orchestration:

1. **Old-reader compatibility versus current containment.** A7 says an old reader safely reaches a generic `unknown_agent_skipped` row for a schema-2 archive-only entry. The current schema parser returns early for entry schema greater than 1, leaving no artifact members in the parsed entry (`manifest.cpp:206-227`). `src/core/open/open.cpp:176-184,261-284` then rejects the actual `agents/...` member as `UnmanifestedMember` before the session-layer generic skip. This is safe against installation, but it is not the claimed graceful-degradation path.
2. **“Same commit” versus two Git repositories.** Product predicates and the E3 scenario/selftest live in bivpak (`harness/scenarios-e3/e3-dual-resume.json:24,42`; `harness/selftest/test_e3_asserts.py:196-248`; `harness/bivharness/e3.py:766-778`). The paired RUNCARD pins live in PDC (`../pdc/master/subteams/s3/RUNCARD-E3.md:306-307`). `git rev-parse --show-toplevel` confirms separate Git roots. One literal commit cannot atomically contain both sides; orchestration must define the cross-repository lock/receipt.

### 5. Existing pure propagation — preserve, do not rebuild

PRIMARY_BUCKET: already-closed

- `already-closed`: `live_at_pack` transport from adapter record through pack, manifest, open rows, and warning selection is implemented.
- `still-open`: only the Codex producer and torn-tail normalization feeding that transport are missing.
- `product-overlapped`: none beyond the liveness/torn-tail sequencing already identified.
- `recommended-next`: keep shared propagation behavior unchanged unless a failing acceptance test proves a narrow adjustment is required.

### 6. Required receipt population

PRIMARY_BUCKET: still-open

- `still-open`: all 18 exact receipt keys are absent from tree `8981bfd`, and every corresponding carrier row is marked `MUTATION REQUIRED AT SEAL`.
- `already-closed`: generic harness, scenario, and mutation-test infrastructure exists, but it does not constitute any of the named receipts.
- `product-overlapped`: A7 receipt execution depends on the product floor/watermark paths; C1 and silent-promotion receipts also share the E3 mirror/RUNCARD surface.
- `recommended-next`: name all 18 receipts in the implementation plan, require pre-mutation green, isolate and revert exactly one mutation per receipt, retain run-trace evidence, and keep the sibling leg green where the carrier requires it.

## Minimum direct-touch file set

This is the minimum currently compelled by the pinned call graph and lock. A later plan may add new fixture files, but it may not omit these existing surfaces without evidence that the obligation moved.

Production and schemas:

- `src/adapters/adapter.hpp`
- `src/adapters/codex/codex.cpp`
- `src/adapters/codex/install.cpp`
- `src/adapters/claude_code/claude_code.cpp`
- `src/adapters/claude_code/install.cpp`
- `src/core/manifest/manifest.hpp`
- `src/core/manifest/manifest.cpp` — direct `repos[]`-adjacent wire-format collision: **YES**
- `src/core/pack/pack.hpp`
- `src/core/pack/pack.cpp`
- `src/core/open/open.cpp`
- `src/core/open/sessions.hpp`
- `src/core/open/sessions.cpp`
- `src/core/open/render.hpp`
- `src/core/open/render.cpp`
- `src/core/report/envelope.cpp`
- `src/core/support/error.hpp`
- `src/core/support/error.cpp`
- `src/cli/main.cpp`
- `schemas/biv-exit-map.v1.json`
- `schemas/biv-json-envelope.v1.schema.json`

Owner tests:

- `tests/test_adapter_codex_collect.cpp`
- `tests/test_adapter_claude_collect.cpp`
- `tests/test_adapter_codex_install.cpp`
- `tests/test_adapter_claude_install.cpp`
- `tests/test_pack.cpp`
- `tests/test_manifest.cpp`
- `tests/test_open.cpp`
- `tests/test_sessions.cpp`
- `tests/test_render.cpp`
- `tests/test_envelope.cpp`
- `tests/test_cli.cpp`

Harness and mirrors:

- `harness/scenarios/open-consent-no.json`
- `harness/scenarios/open-deny-default.json`
- `harness/scenarios/open-consent-yes.json`
- `harness/scenarios-e3/e3-dual-resume.json`
- `harness/bivharness/e3.py`
- `harness/selftest/test_e3_asserts.py`
- `harness/schemas/manifest-plaindir-v1.schema.json`
- `harness/bivharness/manifest.py`
- `harness/selftest/test_manifest.py`
- `harness/selftest/test_scenario.py`

External coordinated surface, not pair-owned and not atomically committable with bivpak:

- `../pdc/master/subteams/s3/RUNCARD-E3.md`

The exact new receipt fixture filenames do not exist in the pinned tree and therefore cannot be truthfully enumerated from current bytes. The implementation plan must assign their final paths before editing begins; all 18 exact keys below are mandatory.

## 18-receipt inventory

Every `Tree key` result below is `ABSENT` from `8981bfd`; every `Carrier arm` is `MUTATION REQUIRED AT SEAL` in committed carrier `ce9ef8c`.

| # | Required receipt key | Carrier line | Current substrate | Missing execution prerequisite |
|---:|---|---:|---|---|
| 1 | `FX-MG-1R/recovery-visibility` | 55 | Generic recovery/harness machinery only | Named default-visible recovery fixture, green assertion, isolated mutation and revert |
| 2 | `FX-MG-3a/recovery-visibility` | 60 | Generic recovery/harness machinery only | Named recovery visibility fixture, green assertion, isolated mutation and revert |
| 3 | `FX-MG-6/default-visibility` | 70 | Generic rendering checks only | Named default-visibility fixture, green assertion, isolated mutation and revert |
| 4 | `FX-MG-7/codex/full-grammar-red` | 85 | Prefix predicate and partial host grammar parser | Full-grammar Codex hostile-basis fixture; sibling Claude leg green; isolated mutation |
| 5 | `FX-MG-7/claude/full-grammar-red` | 86 | Prefix predicate and partial host grammar parser | Full-grammar Claude hostile-basis fixture; sibling Codex leg green; isolated mutation |
| 6 | `FX-MG-9/evaluability-red` | 93 | No evaluability receipt | Evaluability-based abstention fixture/assertion and isolated mutation |
| 7 | `A5.8/tier2-announcement/default-visibility` | 104 | No exact key | Post-A7 readable-newer announcement path, default-visible assertion and mutation |
| 8 | `A5.8/tier2-createdpaths/default-visibility` | 108 | No exact key | Created-path disclosure fixture/assertion, sibling leg green and mutation |
| 9 | `A5.8/tier2-recovery/identify-visibility` | 110 | No exact key | Recovery-identification disclosure fixture/assertion and mutation |
| 10 | `A5.8/tier2-recovery/removes-ours-visibility` | 112 | No exact key | Own-path removal disclosure fixture/assertion and mutation |
| 11 | `A5.8/tier2-recovery/vendor-warning-visibility` | 114 | No exact key | Vendor-warning visibility fixture/assertion and mutation |
| 12 | `A5.8/silent-promotion` | 115 | E3 prefix mirror exists; no floor/watermark distinction | Product `surveyed_through` constants, frozen O7 at/above inputs, watermark-only mutation, and exactly the bound O7 reds |
| 13 | `FX-VF-O3/codex/disclosure-default-visible` | 522 | No readable-newer Codex floor path | Codex O3 readable-newer install/disclosure fixture and mutation |
| 14 | `FX-VF-O3/claude/disclosure-default-visible` | 526 | No readable-newer Claude floor path | Claude O3 readable-newer install/disclosure fixture and mutation |
| 15 | `FX-VF-O6/codex/no-image-field-in-derivation` | 572 | No A7 decision vector | Fixed-host Codex image-version sweep proving derivation purity and mutation |
| 16 | `FX-VF-O6/claude/no-image-field-in-derivation` | 574 | No A7 decision vector | Fixed-host Claude image-version sweep proving derivation purity and mutation |
| 17 | `FX-VF-O4/codex/basis-nul-bearing/refuses-before-comparison` | 538 | No NUL-bearing basis receipt | Real NUL-bearing Codex basis fixture, grammar-before-order assertion, sibling observation and mutation |
| 18 | `FX-VF-O4/claude/basis-nul-bearing/refuses-before-comparison` | 554 | No NUL-bearing basis receipt | Real NUL-bearing Claude basis fixture, grammar-before-order assertion, sibling observation and mutation |

Receipt denominator: **18 required / 0 exact keys present / 18 still open**. No receipt was executed during this read-only audit.

## Required sequencing and gates

1. Orchestrator resolves the old-reader containment contradiction and defines a cross-repository replacement for literal same-commit RUNCARD synchronization.
2. Planner produces a file- and test-specific plan naming the new fixture paths and all 18 exact receipt keys.
3. Orchestrator issues literal implementation authority. This audit does not grant it.
4. Implement Codex liveness before Codex torn-tail branch 3; preserve existing shared propagation.
5. Land A7 floor/watermark/archive-only behavior together with C1 ordering/refusal and E3 mirror coordination.
6. Land denied-consent staging end to end, including A9 sidecar and chosen-row exit-zero behavior.
7. Execute each carrier receipt with pre-mutation green, one isolated mutation, expected red, revert, and post-revert green evidence.

The boundary-contract requirement is not applicable to this audit phase: the audit produced no product output or runtime-write boundary. The implementation plan must identify every such boundary before code work.

## Actions and status proof

ACTIONS_GIT_REF: no product/code edits claimed; repository writes by this seat were this required tracked audit artifact, its timestamped audit transports, the earlier boot acknowledgment, and this seat's append-only INDEX rows. Concurrent branch switches and a docs-lane commit repeatedly changed whether those paths were tracked or untracked during final capture. One transient `/tmp/s4-key-hit.<pid>` search file was created and removed; no temporary file remains.

FINAL_GIT_STATUS_SHORT: unavailable — the shared checkout switched between `docs/r-3.21-readme-git-scope@c953788a` and `main@c118d15` during repeated final captures, changing tracked/untracked classification; no single stable final snapshot can be bound without interfering with concurrent sibling work.

PDC_ACTIONS_GIT_REF: no PDC writes by this seat; PDC sources were read only, with the receipt carrier bound to committed blob `ce9ef8c`.

PDC_FINAL_PATH_SCOPED_GIT_STATUS_SHORT: no output for the five cited PDC authority/carrier/RUNCARD paths.

## Carry list

- `s4.orchestrator-planner`: resolve the two locked-A7 contradictions, preserve the distinct minimum-floor and surveyed-through concepts, and dispatch a plan pass that names every new fixture path and all 18 receipt keys.
- `s4-floor.planner`: independently reconcile this artifact only after filing its own audit; do not treat overlap or an existing helper as closure.
- Future implementation pair: touch no product path until separately addressed implementation authority arrives; preserve unrelated `.gitignore`, roadmap, reconcile, and sibling relay state.
