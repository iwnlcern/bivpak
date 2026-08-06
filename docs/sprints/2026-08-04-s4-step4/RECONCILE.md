# s4 — reconciliation ledger (RUN_ID `s4`)

Audit/sitrep reconciliation at the `s4.orchestrator-planner` seat. Incoming claims are E0
until checked against repo/PR/task/runtime evidence; resolve toward file:line/runtime/test
evidence. Rows append as reconciliations happen.

## s4-matrix-audit — paired reconcile (2026-08-04, both artifacts at `main@8981bfd`)

Artifacts: `audits/s4-matrix-audit-planner.md` · `audits/s4-matrix-audit-implementer.md`.
Both seats E1, blob-pinned, independent (each attests non-reading of the other).

**AGREEMENT (dual-evidenced, adopted as the reconciled base):**
- Fence 1 (`scan.cpp:137-138`, basename-`.git` test, prune-beats-refusal ordering, sole
  construction site, blast radius = pack verb only) and fence 2 (`require_empty_array`
  helper `:81-97`, sole call `:597`, wrap at open into `IntegrityFailurePreApply`).
- The payload-restore substrate is EXTEND-not-rebuild: staging/rename/partial semantics,
  containment via created-ancestry, collision refuse/rename-exhausted, checksummed member
  accounting, plan/apply split — same sites both artifacts.
- NO hidden/dead-pathed git engine exists (two independent instrument sets, both empty).
- Golden harness: substrate reusable (scenario/compare/tolerance), but no git fixture
  builder, repo-aware comparison, semantic git oracle, or activated `d-git-restore` row.
- All five arms: PRIMARY_BUCKET still-open; no bucket/recommendation contradictions.
- The `repos/` member-namespace gate (`open.cpp:275-279` → `UnmanifestedMember`) is a
  THIRD surface Arm 1's schema act must open (planner named it a finding; implementer's
  §2 states the same behavior) — with the envelope summaries (`envelope.cpp:79-81/:107-109`
  + frozen oracle) the schema act scopes FOUR surfaces, not the package's two. **ADOPTED.**

**DIFFERENT COVERAGE (complementary, both folded into the reconciled base):**
- Planner: F1–F7 flip set with the frozen-oracle recapture DECISION (F7), the exit-map
  row-count pin (F4), C1–C9 carriers, green-side seams. Implementer: the ten
  `manifest_variant` scenario retentions, schema `maxItems`/`minItems` gap, selftest
  positive/negative coverage gaps. The DR-3 ledger at PLAN merges BOTH lists.
- Implementer only: the `probe.cpp` subprocess machinery question — extract a generic
  argv runner vs a separately-owned git runner (`probe.cpp:669-880` hardcodes
  `--version`). **Routed to the matrix DESIGN phase as a named decision** (two process-
  safety implementations is the failure to avoid).

**DISAGREEMENT (one, ruled):**
- The two payload-contract gaps (partial lifecycle `detect_partial`/`clean_partial`
  absent from `open.hpp`; plan-time representability — case-collision/path-length/
  `rename_map`/no-probe absent). Implementer: "payload-contract gaps" needing
  disposition; planner: "absent, not divergent — Step-4 work."
  **RULED at this seat: both readings are compatible and the planner's classification
  stands — these are unimplemented features of the restore-apply contract Step 4 exists
  to implement, NOT prior-step drift (nothing landed contradicts the contract).**
  Homes: partial lifecycle → Arm 1/Arm 5 plan rows; representability → Arm 1 plan-time
  checks. The scope READING (contract features beyond the git slice are in-gate) is
  routed UP for master's concurrence — see the reconcile relay.
  **CONCURRED by master (`001031`, 2026-08-05) on STRONGER ground: both features are
  NAMED in the sealed contract itself — `detect_partial`/`clean_partial` at
  `2026-07-02-restore-apply-contract.md:39-40,66-70` (E-17 primitives), representability
  at `:121-126` (§2.5 E-13, `PathUnrepresentable`). One fence restated: contract
  SEMANTICS beyond the sealed text (e.g. the `:218` rename-map mechanism, m-3 input
  flagged) is an m-1 ADDENDUM routed UP, never a local amendment. Q1/Q2/Q3 are
  dispatched to m-2 with master-side verification; the floor holds stand.**
  *Hygiene rule adopted at this seat (master `001031` §2): citations in bridge relays
  carry FULL repo-relative paths (`src/core/open/sessions.hpp`, never `sessions.hpp`) —
  a cite must resolve verbatim at the receiving seat.*

**Process disclosures accepted:** the shared-INDEX ordering wobble (one boot-ack append
race, grandfathered by marker at `232323`); the matrix implementer's shared-checkout
observations.

## s4-floor-audit — paired reconcile (2026-08-04, both artifacts at `main@8981bfd`)

Artifacts: `audits/s4-floor-audit-planner.md` · `audits/s4-floor-audit-implementer.md`
(implementer relay of record: `234019`, third revision). Both E1, blob-pinned,
independent; both verified the A7 lock hash `2e402057…` and read the carrier at blob
`ce9ef8c` (implementer hashed it: `c2bcdc12…`).

**AGREEMENT (dual-evidenced):**
- R-W.1/C1: bare `starts_with` both legs (`codex/install.cpp:194-196`,
  `claude_code/install.cpp:331`); grammar/total-order/typed-refuse conjuncts absent; the
  two production call paths (probe leg, install leg) identical in both artifacts.
- R-VF.1/2/3: all three present exactly as A7 names them — consent-denied bare skip
  before any adapter call; consent-no branches metadata-only both legs; A9 sidecar
  absent tree-wide; the dead `staged`→`session_install_failed` mapper; zero tests on
  `Outcome::staged`.
- R-3.25(a): codex `.live_at_pack=false` at `codex.cpp:391` is the only assignment
  (planner's whole-dir `live` grep is the stronger only-ness instrument); claude leg
  computed; propagation pure (planner enumerated all 21 `live_at_pack` hits). Torn-tail:
  0 hits — unimplemented BOTH legs; (b)-inoperative-until-(a) restated by both.
- A7 floor wholly unlanded: `surveyed_through` 0 hits, `archive_only` 0 hits, no MIN
  constants, no dispositions, writer hardcodes `entry_schema: 1`. MIN vs
  `surveyed_through` kept distinct in every sentence of both artifacts (dispatch
  acceptance criterion met).
- EIGHTEEN receipts: 18 required / 0 keys in tree / 18 still open, all carrier arms
  MUTATION-required; per-receipt prerequisite rows compatible; `A5.8/silent-promotion`
  §8-operative (not §1) in both.

**DIFFERENT COVERAGE (each significant, all routed rather than absorbed):**
- Planner only — **the nine-member drift:** `SessionRowReport` gained `detail`
  post-lock (`sessions.hpp:46-62`) while A7's CANON closed-row rule closes exact rows
  over "ALL EIGHT members." Lock intact; the TREE moved. Every `…-exact` receipt row
  needs a ruling (close over ninth with ∅, or CANON amendment). **m-2 seam → routed UP.**
- Implementer only — **the old-reader containment contradiction:** A7 claims an old
  reader degrades gracefully to a generic skip row on a schema-2 archive-only entry,
  but the shipped parser early-returns at `manifest.cpp:206-227` leaving the entry's
  members unaccounted, so `open.cpp:261-284` refuses the archive's `agents/…` member as
  `UnmanifestedMember` BEFORE the session-layer skip — refusal, not degradation.
  **m-2 seam (it tests A7's own compatibility claim) → routed UP.**
- Both, converging — **the cross-repo same-commit law:** §A7.10's mirror spans two git
  repos (product + harness mirror in bivpak; RUNCARD in pdc) — one literal commit
  cannot hold both. **The cross-repo lock/receipt definition → routed UP.**
- Planner only, plan-level (kept local): `sessions.cpp:308-314` fail-open
  `live_at_pack=false` default on manifest-lookup miss — hardening row for the floor
  plan. `main.cpp:390-394` `NotYetImplemented` list/info (implementer) — render-surface
  note for the floor design.

**DISAGREEMENT:** none of substance found — the artifacts differ only in coverage.

**THE THREE ROUTED QUESTIONS — ANSWERED (m-2 `001600` via master `013331`, 2026-08-05;
holds released to the floor pair at `013542`):**
- Q1: `…-exact` rows close over every member AS IT EXISTS at the reviewed tree
  (criterion, not count); the executor asserts `detail` as read; a populated `detail` on
  an installed row is a finding returned UP. No CANON rewrite.
  **CORRECTED FORWARD (master `044101`, 2026-08-05): the read-and-assert execution shape
  is WITHDRAWN — VP-rejected as self-referential. `detail` semantics arrive PINNED via
  m-2's scoped addendum before the A7 seal; exact-row fixtures take the expected value as
  INPUT, never derive it from the observed row. Criterion-not-count closure stands;
  receipt plans unchanged; carried down at `044329`.**
- Q2, WITH master's correction to m-2's answer: the old reader refuses the WHOLE ARCHIVE
  (`UnmanifestedMember`, **exit 3** — m-2 said exit 2, falsified at master's seat at both
  `cd61ac6` and `8981bfd`, and re-verified at this seat: `src/core/report/envelope.cpp:407`
  `return 3` group; `schemas/biv-exit-map.v1.json:16`). Marker slice binds to
  whole-archive refusal / exit 3 / zero install; A7's contrary text rode an unreachable
  path and is corrected forward at m-2's seat. Stricter than claimed; no arm narrows.
- Q3: F-1's RUNCARD leg = ONE-DIRECTIONAL SHA BINDING (one bivpak commit; the pdc RUNCARD
  row names that SHA; no run consumes unpinned constants). Accepted limitation, carried
  verbatim in the F-1 ledger: drift goes RED at the next run gate, not at change time.
- P5 register disposition: VP-side, meets the A7 seal at s4's exit; the eighteen-receipt
  obligation is unchanged.

**FX-MG-9 (found at floor design rev3, routed `051705`, ruled 2026-08-05):** DISSOLVED —
§A7.5's allowlist deletion made the verdict a pure function of the parsed line; the
discriminating A5 input class is EXTINCT (unconstructible, not unreachable). Burden:
`FX-VF-O5` (12 keys) + `CANON-3`, own CIM, strictly stronger. Map entry:
DISSOLVED-PENDING-RATIFICATION with burden pointer. **Count discipline: EIGHTEEN stays
operative in every s4 artifact until the VP's one master-side re-ratification pass lands
(seventeen only as marked candidate); carried down at `141338`.** Pattern refinement
adopted: a dead-world receipt test asks whether the DISCRIMINATING INPUT CLASS still
exists, not whether one case died.

**Sequencing ruled at this seat (binding on both pairs' plans):**
Addendum F → Arm-1 schema act (all FOUR surfaces) → floor `repos[]`-adjacent
`manifest.cpp` act → separately-owned integration acts with rebases between them.
Beyond the charter fences, three shared clusters get ONE owner per act window:
(1) `src/cli/main.cpp` orchestration; (2) the error-enum/exit-map/envelope cluster
(`error.hpp/cpp`, `envelope.cpp`, `schemas/biv-exit-map.v1.json`, `test_envelope.cpp`
row-count pin); (3) the frozen open-envelope oracle — recapture is ONE decision per act
window, matrix-first at Arm 1, floor after its act lands. `CMakeLists.txt` and shared
open/cli tests: explicit-path, rebase-before-land discipline.

## In-flight dispositions (implementation phase)

**Task-1 uint64 boundary (floor, 2026-08-05, disposed at this seat `182217`):** the JSON
writer lacked any unsigned emitter (verified: `src/core/json/writer.hpp:17-20`;
`value_uint` 0 hits in `src/` at `8981bfd`), so the locked plan's
`std::optional<std::uint64_t> bytes` narrowed via cast above `INT64_MAX`. Scope
expansion GRANTED additive-only on exactly `src/core/json/writer.{hpp,cpp}` +
`tests/test_json_writer.cpp`; delta plan-review approve required; fresh token not
required. **Shared-infra note: the JSON writer is repo-shared leaf infrastructure — the
addition rides the floor's act window (single-owner rule); the matrix pair REBASES over
it before touching writer surfaces.** The implementer's stop-without-editing was the
standing conditions working — second live catch by the pair's own gates this run.

**Locked-schema blob-lock discipline (RULING OF RECORD, both pairs — disposed `200505`):**
`harness/selftest/test_envelope.py`'s `CURRENT_LOCKED_SCHEMA_BLOBS` recaptures
MECHANICALLY, literal-for-literal, in the SAME reviewed head that changes the
corresponding locked schema (envelope schema / exit map) — the recapture rides the
review that approved the schema change, so lock-green is always a reviewed decision.
Recapturing a literal whose schema the head did not change, or any other edit to the
file, is a deviation. Binds the floor slices (B1/A/C) and the matrix Arm-1 schema act
identically, inside whichever act window owns the schema file. DISTINCT from the frozen
open-envelope ORACLE's once-per-window recapture rule, which stands unchanged —
different instrument, different discipline.
