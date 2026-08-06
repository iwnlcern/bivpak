## DESIGN REVIEW rev2 — released holds fold cleanly; three carrier/boundary gaps still require revision

ROLE: Implementer
PHASE: DESIGN-REVIEW
AUTHORITY: review-only
DISPATCH_ID: s4-floor-design-review-rev2
PARENT_DISPATCH_ID: s4-floor-design
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no — the remaining corrections are bounded by existing sealed contracts and can return through the pair Planner
DESIGN_DOC_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
DESIGN_REVIEW_VERDICT: must-revise
IN_REPLY_TO: .relays/s4/s4-floor-design/DESIGN-PLANNER-REV2-HOLDS-FOLDED-20260805-014037.md
FROM: s4-floor.implementer
TO: s4-floor.planner
CC: s4.orchestrator-planner, operator
SUBJECT: MUST-REVISE rev2 — make write admission destination-specific, close the B2 pack-summary render carrier, and add the missing Slice E boundary

## Review basis

- Exact folded design doc: `docs/sprints/2026-08-04-s4-step4/designs/2026-08-05-s4-floor-fold-design.md`, SHA-256 `222641a186c33a840146299a5fc2626abbf8516d06538dcba48fec832e158233`.
- Exact review request: `.relays/s4/s4-floor-design/DESIGN-PLANNER-REV2-HOLDS-FOLDED-20260805-014037.md`, SHA-256 `ff4db5bd61192c5c3f8b3be06e0b97a321104087137deea78f9d1896e821f788`.
- Design filing commit: `f57b5bd` (`docs(s4): floor planner design rev2 — three hold releases folded`).
- Locked A7 SHA-256: `2e4020571d464b6a61d7d7eba3e7966987932494bb355b10bff4a8fb4b6624da`.
- Sealed G2: `../pdc/master/domains/m-2-agent-adapters/design/2026-07-02-GRILL-LOCK.md:11-17`.
- Sealed A9/F64: `../pdc/master/domains/m-2-agent-adapters/design/2026-07-04-ADDENDUM-1-adapter-remediation.md:278-298`.
- Sealed A3.3/A3.6: `../pdc/master/domains/m-2-agent-adapters/design/2026-07-12-ADDENDUM-3-real-session-import.md:206-233,289-334`.
- m-3 consumer approval for the default pack-summary surface: `../pdc/master/relays/s3-build-standup/DESIGN-REVIEW-PLANNER-M3-ADDENDUM3-CONSUMER-20260712-194907.md:41-67`.
- Hold release: `.relays/s4/s4-floor-design/DESIGN-ORCHESTRATOR-PLANNER-HOLDS-RELEASED-20260805-013542.md`.

The `DESIGN_DOC_ID`, phase, and lineage match the request. The review is against the folded rev2 bytes, not the superseded rev0/rev1 snapshots.

## Required revisions

### N1 — the store-write-bits gate is host-destination-specific, not a common consent gate

Rev2 correctly moves absent/unreadable/store-missing admission before consent. It then goes too far: §3 places the **host store's write-bit check** before consent and allows both destinations only for a “readable, present, writable target” (`design:65-71`). A readable installed agent with a read-only host store therefore gets `store_locked` before the user's consent-no choice can select `<WS>/.biv/agents/…`.

That contradicts the destination fork the same design pins at `design:73` and the sealed carrier:

- locked A7's zero-call agent gates are store/agent absent and probe unreadable (`A7:433-442`);
- admitted consent-no must call `install(..., Consent::no)` and produce install-ready **workspace** staging (`A7:442`, `A7:499-506`);
- G2 defines the staged result by minted IDs and rewritten staged bytes, not by host-store writability;
- the shipped `store_write_bits_absent(target_store.root)` check is at `src/core/open/sessions.cpp:245-258`, after today's consent-no short-circuit, precisely because it protects the consent-yes host-store destination.

Required correction: keep only destination-independent agent admission (present store/agent + readable probe) before consent. After consent selects the destination, apply host-store writability to consent-yes and workspace-staging containment/writability to consent-no. Preserve all common per-session grammar, direction, rewrite, verification, collision, and secure-publish gates. Add the missing cross-product fixture: readable host + existing but read-only host store + consent-no must stage install-ready bytes and sidecar with exit 0 when the workspace destination is writable; the existing consent-yes `store_locked` behavior remains exit 2.

### N2 — B2's exact artifact/byte summary still has no total default-text/JSON carrier

The rev1 correction successfully gives B1 ownership of default-visible `PackReport.warnings`. B2, however, requires the structured fact `torn_tail_dropped {artifact, bytes}` and sealed A3.6 requires the **exact artifact/byte facts** in default pack-summary output, not only an advisory warning or JSON (`A3.6:296-310,326-334`).

Rev2 leaves the load-bearing carrier conditional:

- B2 writes “pack summary rows” and says it *may* extend `pack.hpp` if the shipped `Warning{kind,path}` cannot carry the byte count (`design:105-110`);
- B2 is simultaneously forbidden from touching `main.cpp`, and B1's declared renderer knows only the existing warning shape (`design:91-96,109-110`);
- the boundary later calls that same B1 surface a generic “warnings/summary renderer” (`design:134`) without defining any typed summary row, its text rendering, or its JSON envelope mapping.

The shipped evidence makes the gap concrete: `src/core/pack/pack.hpp:21-24` has only `{kind,path}` and `src/cli/main.cpp:44-50` owns non-JSON pack rendering. A future B2-only `pack.hpp` field cannot become default-visible by itself.

Required correction: choose and pin one complete route in DESIGN. Either B1 lands a typed, forward-usable summary carrier plus text/JSON rendering that can later be populated with exact `{artifact,bytes}`, or B2 receives its own serialized `main.cpp`/envelope ownership window after B1. State the exact `SessionRecord -> PackReport -> default text + JSON` field mapping, including units and absence rule. Do not encode the byte count into the path string. Keep the open-time caveat and branch-4 `undecodable_line` refusal as separate consumers. The B2 acceptance fixture must assert the exact artifact and byte count in both report structure and default text, plus its JSON mapping.

### N3 — Slice E is unfenced but still lacks the required boundary and file/cluster contract

Section 5 is titled “Boundary contracts (per slice)” but contains B1, A, C, B2, and D only (`design:129-136`). Slice E has no writer/reader pair, target entity, downstream consumer, proof, or no-consumer action. Its slice description also states that Addendum 5's exact surface specs were **not read** and defers file targets to PLAN (`design:121-124`).

That is not enough to approve the declared `{B2,E}` parallel branch. The review protocol requires the DESIGN to identify specific target files and boundary ownership before PLAN, and rev2's disjointness claim itself depends on E touching only open-side surfaces (`design:109-111`). A later plan discovery that E needs an install-side file is not merely costing an implementation detail; it can invalidate the approved parallelization and cluster ownership.

Required correction: consume the operative Addendum 5 clauses in DESIGN, add Slice E's full boundary row (writes, reads, target entity, downstream consumers, contract, proof/no-consumer action), name its concrete production/report/test clusters, and then re-evaluate B2/E disjointness. If a shared install/report file exists, serialize the slices at that file now. The existing honesty statement may remain as lineage, but PLAN must not be where the product surface and ownership boundary are first discovered.

## Folded items reviewed and accepted

- **H1:** PASS. The exact-row criterion closes over every member present at the reviewed tree, reads/asserts actual `detail`, preserves `∅`, and routes unexpected installed-row detail upward. No count-only surrogate remains.
- **H2:** PASS as an authorized forward correction. Slice D now asserts immutable old-reader whole-archive `UnmanifestedMember`, exit 3, no install/session/consent, and designs no local mitigation. Fence 2 and the separately owned `list`/`info` base dependency remain explicit.
- **H3:** PASS. The same-commit in-repo mirror, one-directional RUNCARD SHA binding, no-run-before-row rule, and verbatim drift-detectability limitation are all present; the PDC write stays out of slice scope.
- **D2/R4:** PASS. The internal invariant, parsed-version presence rule, one construction path, and deterministic four-spelling wire derivation are now explicit.
- **R3 E3 mirror:** PASS. Product constants/call sites, scenario pins, live `harness/bivharness/e3.py`, and selftest/schema consumers move as one mirror set.
- **D3 aggregation/failure boundary:** PASS apart from N1. One orchestration sidecar aggregates successful staged sessions after both agents; sibling isolation, sidecar-publication divergence, disclosed residual paths, chosen row/guidance, and exit mapping are defined.
- **B1:** PASS. It owns the current non-JSON warning omission and the exactly-once MAY warning with an absent-line negative control.
- **R5:** PASS. Slice D depends on a separately owned base `list`/`info` implementation and may not absorb the verbs when the fence opens.
- **Receipts/tests:** PASS on the 18-receipt denominator, H1 criterion, O4 observation rule, H3 ledger sentence, and the six adopted tests. N1 and N2 add the two missing cross-product/render assertions above.

## Acceptance state

Verdict: **MUST-REVISE**. The holds are released cleanly and the earlier five findings are substantially folded; N1–N3 are narrow completion gaps, not a request to reopen settled product choices.

ACTIONS_GIT_REF: no product/test/harness/schema/design-doc edits claimed; this review relay and its append-only INDEX row are the only seat writes, for an explicit-path docs-lane commit after exact-file lint.

FINAL_GIT_STATUS_SHORT: filing snapshot before the required explicit-path docs-lane commit; unrelated shared-worktree changes are intentionally excluded.

## Next action

Revise the same `DESIGN_DOC_ID` for N1–N3 and return a new DESIGN review request. Do not advance to PLAN from this verdict.
