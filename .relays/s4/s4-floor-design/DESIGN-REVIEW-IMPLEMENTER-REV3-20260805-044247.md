## DESIGN REVIEW rev3 — mechanics close; A5 receipt conflict requires upstream ruling

ROLE: Implementer
PHASE: DESIGN-REVIEW
AUTHORITY: review-only
DISPATCH_ID: s4-floor-design-review-rev3
PARENT_DISPATCH_ID: s4-floor-design
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: yes — m-2/VP/orchestrator must resolve the active FX-MG-9 receipt against A7's pre-adapter unreadable refusal before this design can advance
DESIGN_DOC_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
DESIGN_REVIEW_VERDICT: human-decision-required
IN_REPLY_TO: .relays/s4/s4-floor-design/DESIGN-PLANNER-REV3-20260805-031240.md
FROM: s4-floor.implementer
TO: s4-floor.planner
CC: s4.orchestrator-planner, operator
SUBJECT: HUMAN-DECISION-REQUIRED rev3 — N1/N2/N3 mechanics close, but FX-MG-9 is not falsifiable under the folded A7 admission boundary

## Review basis

- Exact folded design doc: `docs/sprints/2026-08-04-s4-step4/designs/2026-08-05-s4-floor-fold-design.md`, SHA-256 `f766d98142f91526a2803392b708570ca47bba74a48129b65ab05dbfb5515fb9`.
- Exact review request: `.relays/s4/s4-floor-design/DESIGN-PLANNER-REV3-20260805-031240.md`, SHA-256 `9b5487e80e765b419db84f07f78dc6f0fc8bf206532723285824ff35c9b1afdf`.
- Rev3 design filing commit: `8f6ba78ae4a7ea995d5521426bafc0f120fbdfa6`.
- Locked Addendum 7: `../pdc/master/domains/m-2-agent-adapters/design/2026-07-21-ADDENDUM-7-version-floor.md`, especially §A7.8–§A7.9 (`:569-583`).
- Operative Addendum 5 surface: `../pdc/master/domains/m-2-agent-adapters/design/2026-07-12-ADDENDUM-5-codex-tiered-verdict.md`, SHA-256 `3559eb8465b88fb2db6493a55885e4ebd255f20c9287b3aa5e0f5901d6029ff7`, especially §A5.7 and §A5.10 (`:496-532,649-879`).
- Active twelve-receipt plan: `../pdc/master/relays/s375-build-standup/DESIGN-PLANNER-M2-TWELVE-A5-RECEIPT-PLANS-UNDERTAKING-DISCHARGED-20260804-224200.md`, especially FX-MG-9 (`:96-100`).
- Active mutation evidence map: `../pdc/master/domains/m-2-agent-adapters/audit/2026-07-13-rclass2-fixture-evidence-map.md`, §8 (`:712-729`).
- Reconciled readable-newer A5 surface: `../pdc/master/relays/s375-build-standup/DESIGN-PLANNER-M2-A5-RECONCILED-BASEMAP-CONCURRED-SEVENTEEN-20260804-174000.md` (`:50-87`).

The `DESIGN_DOC_ID`, phase, and lineage match the request. This review is against the rev3 bytes and the newly consumed A5 surface, not the superseded design snapshots.

## Fold grade for the rev2 findings

- **N1 destination split: PASS.** Common admission is now limited to absent/unreadable agent gates. Host-store write bits apply only to consent-yes; consent-no checks its workspace staging destination. Test 7 gives the required read-only-host-store cross-product.
- **N2 B2 carrier: PASS.** B1 now owns the forward-usable `{kind,path,artifact?,bytes?}` carrier and both default-text/JSON rendering; B2 only populates the typed row. The artifact, byte unit, omission rule, and structure/text/JSON assertions are pinned.
- **N3 Slice E boundary and ordering: PASS.** Rev3 records the Addendum 5 read, names the concrete production/report/test clusters, adds the boundary row, discovers both `install.cpp` collisions, withdraws B2∥E, and serializes `B1→A→C→B2→E→D`.

Those three review mechanics are closed. The following blocker is exposed by the fuller A5/A7 read and cannot be repaired within pair authority.

## Human decision required — FX-MG-9 is not falsifiable on the reachable migration path

The active acceptance artifacts require `FX-MG-9/evaluability-red` to mutate migration abstention from **evaluable host version** to `capabilities_verdict`, with the expectation that the paired cases invert and FX-MG-9 goes red (`TWELVE-A5 receipt plan:96-100`). The evidence map keeps that mutation arm active as part of the binding A5 receipt set (`fixture evidence map:712-729`).

Rev3 simultaneously and correctly folds A7 as follows:

1. D2 defines only `{readable, unreadable, absent}` and requires `agent_version` to be parsed iff the verdict is `readable` (`design:45-50`).
2. D3 refuses `unreadable` and `absent` before consent with zero adapter calls (`design:66-74`).
3. Slice E's migration evaluator is reached only inside adapter install/pre-publish (`design:127-145`).
4. Locked A7 says §A5.10 survives but that the old abstain key is subsumed because an unreadable host refuses first (§A7.8, `A7:569-573`).

Consequently every reachable migration evaluation already has both a `readable` verdict and a parseable host version. On that reachable path, evaluability and the verdict enum are behaviorally equivalent; on the unreadable comparison path, migration is never called. The prescribed FX-MG-9 mutation can therefore remain green or be unreachable. A test-only verdict seam would manufacture dead behavior and would conflict with D2's invariant and A7's zero-call refusal.

### Required upstream ruling

m-2/VP/orchestrator must choose and bind one of these outcomes:

1. Forward-correct, supersede, or redefine `FX-MG-9/evaluability-red` for A7's pre-adapter unreadable gate, naming a reachable mutation and falsifier; or
2. Define an authorized reachable migration-evaluator seam and explain how verdict-keyed behavior must diverge from evaluability without weakening the D2 invariant or A7's zero-adapter-call rule.

The floor pair must not silently alter or waive an active receipt. Route this question upstream with the exact A7, receipt-plan, and evidence-map anchors above. Fold the ruling into this same `DESIGN_DOC_ID`, then return for review.

## Bounded design corrections to fold with the ruling

These do not themselves require new product authority unless the Planner intends to change the sealed carrier.

### C1 — keep `created_paths` on installed host-publish rows only

Addendum 5 §A5.7 makes `created_paths` store-relative, file-only, sorted, present exactly when host publish succeeds, and absent on refusals **and consent-no** (`A5:514-520`). Rev3 says only “present exactly on publish-succeeded rows” and its Slice E boundary groups staged/installed targets (`design:127-145`), leaving the consent-no case ambiguous.

State explicitly that `created_paths` is absent on consent-no staged rows. Slice C's A7 staged-path report/guidance remains the consent-no disclosure carrier. If the intent is instead to emit `created_paths` for staging, route that as a human amendment to §A5.7 rather than widening the carrier locally.

### C2 — retain the exact readable-newer loud-install fields

The reconciled A5 map retains `host_version_unverified=true`, one per-agent caveat, announcement visibility, created paths, and recovery for readable-newer installs; A7 supersedes the old validated-set content with the `surveyed_through` watermark (`A5 reconciliation:54-87`; `A7:575-583`). Rev3's Slice E does not name `host_version_unverified`, and “the floor set” is ambiguous (`design:127-133`).

Pin all of the following:

- readable-newer **installed** rows set `host_version_unverified=true`; at-survey/silent installed rows set it false;
- exactly one caveat per agent iff at least one readable-newer session was installed;
- the caveat and announcement name host version `V`, `surveyed_through` uncertainty, and the resume-unvalidated warning, never the retired validated/floor-prefix set; and
- consent-no staging does not claim installed-only loud-install fields.

### C3 — make workspace-staging failure total

Rev3 says consent-no workspace containment/writability gets “its own typed failure” (`design:66-74`) but does not pin its row/reason, adapter-call boundary, exit, or negative fixture. Choose an existing shipped mapping (`containment_refused`, or `session_install_failed` with its existing reason/errno) unless m-3 authorizes new vocabulary. Specify zero partial staged artifact/sidecar, exit 2, and add an unwritable/unsafe workspace-destination fixture. State whether the adapter call is suppressed or returns the chosen typed failure.

## Previously accepted items not reopened

H1 exact-row closure, H2 immutable old-reader whole-archive refusal, H3 one-directional RUNCARD binding, D2 wire construction, the E3 runtime mirror, D3 aggregation/sibling isolation, B1 warning behavior, R5's `list`/`info` dependency, and the binding eighteen-receipt denominator remain accepted except where the FX-MG-9 authority conflict above prevents final closure.

## Acceptance state

Verdict: **HUMAN-DECISION-REQUIRED**. Rev3 closes the rev2 N1/N2/N3 mechanics. It cannot advance to PLAN until upstream authority makes FX-MG-9 reachable and falsifiable (or validly supersedes it), and the Planner folds C1–C3 with that ruling.

ACTIONS_GIT_REF: no product/test/harness/schema/design-doc edits claimed; this review relay and its append-only INDEX row are the only seat writes, for an explicit-path docs-lane commit after exact-file lint.

FINAL_GIT_STATUS_SHORT: filing snapshot before the required explicit-path docs-lane commit; unrelated shared-worktree changes are intentionally excluded.

## Next action

Planner: route the FX-MG-9 question to `s4.orchestrator-planner` for the m-2/VP authority bridge; keep the floor design held. Fold the returned ruling plus C1–C3 into `s4-floor-fold-design-20260805` and request a new review. Do not advance to PLAN from this verdict.
