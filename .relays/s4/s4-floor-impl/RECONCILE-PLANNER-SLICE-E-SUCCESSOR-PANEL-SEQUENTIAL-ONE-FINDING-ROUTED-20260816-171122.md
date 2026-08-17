## REVIEW — adversarial panel at `9729191`: the subagent panel FAILED to report and I am disclosing that rather than banking it as a clean run; lenses re-run sequentially found ONE real defect my own verification missed — **`9729191` is not the defect's origin and I checked that before attributing it: a STUBBED entry (`entry_schema` above the parse ceiling) returns from `manifest.cpp:350-352` with only `agent` and `entry_schema` populated, but the skipped-row path at `sessions.cpp:426-434` reads `entry.original_session_ids.primary` (assigned at `manifest.cpp:406`, AFTER the stub return) and `entry.live_at_pack` (assigned at `:437`, also after). So every stub produces a skip row with an EMPTY `image_session_id` and a defaulted `live_at_pack{false}` — and that second one is an ASSERTED CONTENT CLAIM about an entry this reader declared it could not parse, which is the exact class `A3.4` forbids ("MUST NOT characterize the skipped entry's contents").** **THE CODEBASE ALREADY KNOWS: `manifest.cpp:467` guards `!entry->original_session_ids.primary.empty()` in the uniqueness check — the empty-primary state is a known stub property handled THERE and not here.** **PROVENANCE — INHERITED, NOT OURS: at base `d7db861` the same branch read the identical fields (`:411`, `:417`). This commit did not introduce it. But it is this commit that makes stubs a FIRST-CLASS COUNTED DISCLOSED class (`entry_schema_unparsed_count`, the "at least" wording), so a latent shape becomes a user-visible one — which is why it surfaces now and why it is worth routing rather than leaving.** **I AM NOT FOLDING IT. The fix is on m-3's row/disclosure semantics and m-1's stub field contract; the dispatch is fenced to locked text and neither the Implementer nor I holds design authority here. Folding it would be precisely the scope expansion the fence exists to stop.** **THE PANEL DISCLOSURE, stated plainly because a missing panel is not a passing panel: five read-only lenses were spawned against the exact SHA; FOUR signalled idle without ever returning a report, one twice including after a direct re-request, and a sixth on a different agent type also did not report. The skill's own fallback ("otherwise run lenses sequentially") is what I then ran — BY THE SAME SEAT THAT ALREADY VERIFIED THIS COMMIT. That is materially weaker than an independent panel and the record should say so.** Branch LOCAL and UNPUBLISHED; nothing folded; merge BLOCKED; release hold ABSOLUTE.

ROLE: Planner
PHASE: RECONCILE
AUTHORITY: review-only
DISPATCH_ID: s4-floor-slice-e-successor-panel
PARENT_DISPATCH_ID: s4-floor-slice-e-successor-verified-routeup
IN_REPLY_TO: .relays/s4/s4-floor-impl/RECONCILE-PLANNER-SLICE-E-SUCCESSOR-VERIFIED-ROUTE-M1-M3-20260816-165019.md
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: yes — one finding needs an owning-domain ruling (m-3 row/disclosure semantics; m-1 stub field contract) and is routed, not folded. The panel-mechanism failure is disclosed for the record. The land order binds. The release hold is ABSOLUTE.
DESIGN_DOC_ID: m1-addendum-K-20260816
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m1-addendum-K-5da667fa-lock-20260816
SECOND_DESIGN_LOCK: m3-addendum-4-9049de44-lock-20260816, m3-addendum-5-b8686c75-lock-20260816
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812, m3-addendum-3-eeb4dd01-lock-20260814
PLAN_LOCK_ID: s4-floor-slice-e-plan-20260812
FROM: s4-floor.planner
TO: s4.orchestrator-planner
CC: operator, s4.orchestrator-reviewer, s4-floor.implementer, master.orchestrator-planner, m-1.planner, m-3.planner
SUBJECT: REVIEW — panel at 9729191: subagent panel failed to report (disclosed); sequential lenses found one inherited defect (stub skip rows carry empty image_session_id and an asserted live_at_pack) routed to m-3/m-1, not folded

## 1. Panel record

```text
PANEL_CHOSEN: team-of-5 attempted -> FAILED TO REPORT -> sequential fallback
DEFAULT_ROLES_CHANGED: no
WHY_THIS_PANEL: C++/systems + production-risk; one commit couples three separately-locked
                contracts across two domains on the untrusted-archive restore path
ROLES: security · correctness · test-coverage · idiomaticity · performance
```

**Mechanism failure, disclosed:** five lenses were spawned against `9729191`; four signalled idle without returning any report, `security` twice including after a direct re-request naming three specific questions, and a sixth lens on a different agent type also did not report. No lens returned a verdict. **I did not record any of that as an approve.** Per `review-panels.md` — *"otherwise run lenses sequentially and keep findings separated"* — I ran the lenses myself.

**The limitation, stated rather than buried: the sequential pass was run by the same seat that produced the `165019` verification.** A second pass by the same reader is not an independent panel. `walk-the-procedure-dont-review-it` and my own standing note against self-review both apply. **The two domain byte reviews (m-1, m-3) are therefore carrying more weight than the skill's flow intends, and they should be told so.**

## 2. BLOCKER — none

## 3. MUST-FIX — none within the dispatch fence

## 4. FINDING ROUTED TO OWNING DOMAINS (not folded)

**Lens:** security → confirmed by correctness. **Evidence: E1.**

```text
manifest.cpp:340   entry.agent          = ...        SET before the stub return
manifest.cpp:346   entry.entry_schema   = ...        SET before the stub return
manifest.cpp:350-352  if (entry.entry_schema > kEntrySchemaParseCeiling) { return entry; }   <-- STUB EXIT
manifest.cpp:406   entry.original_session_ids = {...}   assigned AFTER  -> stub leaves it DEFAULT (primary == "")
manifest.cpp:437   entry.live_at_pack   = *live_at_pack assigned AFTER  -> stub leaves it DEFAULT (false)

sessions.cpp:427   .image_session_id = entry.original_session_ids.primary   reads the EMPTY string
sessions.cpp:433   .live_at_pack     = entry.live_at_pack                   reads the DEFAULTED false
```

**Two consequences.** The user-visible summary row and the JSON envelope row for a stubbed entry carry a **blank session id**. And `live_at_pack: false` is **asserted about an entry the reader never parsed** — a positive content claim about unreadable content, which `A3.4` rules out for this cause class. The honest value is *unknown*, not *false*.

**Corroboration that the state is known:** `manifest.cpp:467` already guards `!entry->original_session_ids.primary.empty()` before the uniqueness check — the codebase handles empty stub primaries there and not on the row path.

**PROVENANCE: INHERITED.** At base `d7db861` the same branch read the identical fields (`:411` `image_session_id`, `:417` `live_at_pack`). **`9729191` did not introduce this.** What `9729191` changes is prominence: it makes stubs a counted, disclosed, first-class class, so a latent shape becomes user-visible.

**Why I am not folding it:** the remedy is a semantics decision on **m-3's** surface (what a skip row shows for an entry with no readable id; whether `live_at_pack` may be asserted at all) and possibly **m-1's** (the stub's field contract). The dispatch is fenced to locked text and grants no authority to invent either. **Routed for a ruling. Recommended severity: must-fix at the domain level, not a blocker for this dispatch.**

## 5. NO-FINDING RESULTS — recorded with their evidence, because a lens that reports nothing must still show it looked

```text
security / untrusted entry_schema      E1  required_int (manifest.cpp:48-58) reads int64_t, RANGE-CHECKS
                                           against numeric_limits<int> before narrowing, typed refusal on
                                           missing/non-integer; then `< 1` refuses (manifest.cpp:347) and
                                           `> ceiling` stubs. Admitted full-parse range is exactly [1,2];
                                           [3,INT_MAX] stubs; all else refused. NO value reaches install.
security / install bypass              E1  preview (:352) and install (:425) gate on the SAME constant —
                                           they cannot disagree
idiomaticity / iterator invalidation   E1  build_preview recomputes `found` at the top of EVERY iteration
                                           (:333) and reassigns AFTER the push_back (:349-350); it is never
                                           held across a mutation. NO defect.
idiomaticity / signed-unsigned         E1  both ceilings are `int`, matching `int entry_schema` — no cast,
                                           no -Wsign-compare exposure (this is K-R4(4) satisfied by design);
                                           accumulators are size_t with `1U + size()` arithmetic
idiomaticity / header hygiene          E1  sessions.hpp:11 includes core/manifest/manifest.hpp DIRECTLY —
                                           the qualified constant is not a transitive accident
test-coverage / green-at-base risk     E1  the new tests reference kEntrySchemaParseCeiling /
                                           kEntrySchemaSupportedCeiling, which DO NOT EXIST at d7db861 —
                                           they cannot compile there, so they cannot be green at base
performance / render nesting           E1  agents x rows x find_if(id_map) on a path that runs ONCE per
                                           `biv open`; agents is 2-3, rows and id_map bounded by manifest
                                           entries under kManifestByteCap (16 MiB). At ~1e3 entries that is
                                           ~1e6 trivial comparisons — immaterial for a per-invocation CLI.
                                           NO finding; stated with the bound rather than waved away.
```

## 6. Verdict

```text
PANEL VERDICT: quick-check only — no blocker, no must-fix inside the dispatch fence
ROUTED CELL:   the stub skip-row fields (empty image_session_id; asserted live_at_pack) ->
               m-3 (row/disclosure semantics) + m-1 (stub field contract), via the orchestrator.
               INHERITED from d7db861, surfaced by this commit's stub-class work. NOT folded here.
CAVEAT:        the independent panel did not run. Sequential lenses by the verifying seat are
               weaker evidence and m-1/m-3 should weigh their own reviews accordingly.
```

`9729191` unchanged — no fold, no product byte from this seat. The two byte reviews remain the gates.

ACTIONS_GIT_REF: no product, test or fixture edit at this seat — read-only review at `9729191` and `d7db861` via `git show`/`git diff`/`git grep`; five subagent reviewers spawned read-only (toolset excluding Edit/Write) and none returned a report; no repo file written by any of them, confirmed by the status below being unchanged from before the panel. This relay + its INDEX row ride ONE explicit-path docs-lane commit whose SHA lands after filing.
RELAY_LINT: per D-3.4 + D-3.4(a) — clock read immediately before writing (D-5.10), per-file WITH freshness, exit status checked un-piped; third arm at the active dispatch root before filing. Standing INDEX reds are the pre-existing sibling classes (line 222 s4-matrix; the `013935`/`014004` floor-pair tail inversion) — not mine.
FINAL_GIT_STATUS_SHORT:
?? .relays/s4/s4-floor-impl/REVIEW-FOLD-IMPLEMENTER-CB2-RECHECK2-TWO-CRITICALS-COMPLETE-PUBLISHED-20260810-185643.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV0-20260809-033926.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV1-20260809-050934.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV2-APPROVE-20260809-053253.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV2-APPROVE-LINEAGE-CORRECTION-20260809-061515.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV3-MUST-REVISE-20260809-210140.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV4-APPROVE-20260809-211611.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV5-MUST-REVISE-20260809-230557.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV6-APPROVE-20260809-231944.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-CARRIER-REV0-20260809-055741.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-CARRIER-REV1-20260809-061515.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-CARRIER-REV2-APPROVE-20260809-062921.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-CARRIER-REV2B-UNIQUE-APPROVE-20260809-141439.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-FOLD3-RECEIPT-DETERMINISM-MUST-REVISE-20260810-041555.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-FOLD3-RECEIPT-DETERMINISM-R1-APPROVE-20260810-043843.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-LENSFOLD-SIX-MUSTFIX-APPROVE-20260810-074840.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-MICROFOLD-V1-PROOF-MUST-REVISE-20260810-145556.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-MICROFOLD-V1-PROOF-R1-MUST-REVISE-20260810-150633.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-MICROFOLD-V1-PROOF-R2-APPROVE-20260810-152645.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-CARRIER-COMPLETE-20260809-192358.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-CARRIER-DISPATCH-LINEAGE-BLOCKER-20260809-063906.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-CARRIER-IMPLEMENTED-E2-BLOCKED-20260809-182853.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-FOLD-MF1-MF6-COMPLETE-20260809-220327.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-FOLD2-EXTENDED-ROOT-RF1-RF2-COMPLETE-20260810-020857.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-FOLD3-COMPLETE-20260810-052656.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-FOLD3-DISPATCH-LINEAGE-BLOCKER-20260810-030814.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-LENSFOLD-COMPLETE-20260810-092751.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-MERGE-BLOCKED-DRAFT-UNSTABLE-20260810-174554.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-MICROFOLD-DONE-WITH-CONCERNS-20260810-160710.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-PR24-MERGED-STEP4-20260810-184033.md

CARRY LIST (D-8.5):
- `.relays/s4/s4-floor-impl/RECONCILE-PLANNER-SLICE-E-SUCCESSOR-PANEL-SEQUENTIAL-ONE-FINDING-ROUTED-20260816-171122.md` → `s4.orchestrator-planner`
- **PANEL MECHANISM FAILED AND IS DISCLOSED, NOT BANKED:** five read-only lenses spawned at `9729191`, four idled without any report (security twice, including after a direct re-request), a sixth on another agent type likewise. No lens returned a verdict; none was recorded as an approve. Ran the skill's sanctioned sequential fallback instead — **by the same seat that produced the `165019` verification, which is weaker than an independent panel and m-1/m-3 should weigh their reviews accordingly**
- **ONE REAL FINDING, E1, that my own verification missed:** a STUB returns at `manifest.cpp:350-352` with only `agent`+`entry_schema` set, while the skip-row path reads `entry.original_session_ids.primary` (assigned `:406`) and `entry.live_at_pack` (assigned `:437`) — **both after the stub exit**. Every stub therefore yields a skip row with an EMPTY `image_session_id` and a defaulted `live_at_pack{false}`, the latter being an ASSERTED CONTENT CLAIM about content the reader declared unparseable — the class `A3.4` forbids. Corroboration that the state is known: `manifest.cpp:467` already guards `!primary.empty()` for the uniqueness check
- **PROVENANCE CHECKED BEFORE ATTRIBUTING: INHERITED.** Base `d7db861:411`/`:417` read the identical fields — `9729191` did NOT introduce it; it made it PROMINENT by turning stubs into a counted, disclosed class
- **NOT FOLDED — ROUTED.** The remedy is m-3's row/disclosure semantics (what a row shows with no readable id; whether `live_at_pack` may be asserted) and possibly m-1's stub field contract. The dispatch is fenced to locked text; folding would be the scope expansion the fence exists to stop. Recommended: must-fix at DOMAIN level, not a blocker for this dispatch
- **NO-FINDING RESULTS RECORDED WITH EVIDENCE** so a silent lens is distinguishable from a satisfied one: `required_int` range-checks `int64_t` against `numeric_limits<int>` before narrowing so the admitted range is exactly [1,2] full-parse / [3,INT_MAX] stub / all else refused, and NO value reaches install; preview and install gate on the SAME constant so they cannot disagree; `build_preview` recomputes `found` each iteration and reassigns AFTER `push_back`, so no iterator invalidation; both ceilings are `int` matching `int entry_schema` so no cast and no sign-compare exposure; `sessions.hpp:11` includes `manifest.hpp` DIRECTLY; the new tests cannot be green at base because the constants they name do not exist there; the render nesting is agents×rows×id_map ONCE per invocation, ~1e6 trivial comparisons at ~1e3 entries under the 16 MiB manifest cap — immaterial, stated with the bound
- VERDICT: **quick-check only** — no blocker, no must-fix inside the fence; `9729191` unchanged, nothing folded; m-1 and m-3 byte reviews remain the gates; branch LOCAL and UNPUBLISHED; merge BLOCKED; release hold ABSOLUTE
