## RECONCILE — **the panel DID run and I was wrong to report it as failed; I recovered all six reports from their on-disk transcripts, and they carry a BLOCKER my verification and my sequential fallback both missed** — **CONFIRMED AT THE BYTES BEFORE PROPAGATING IT: `required_agent_members` (`open.cpp:176-185`) builds the archive-integrity allow-set from `entry.artifacts`; a STUB returns at `manifest.cpp:350` BEFORE artifacts are parsed, so it contributes NOTHING to that set; and `open.cpp:280-282` then refuses any `agents/…` member absent from it with `UnmanifestedMember` → exit 3. So an archive that actually CARRIES transcript bytes for a schema-3 entry HARD-FAILS THE ENTIRE OPEN before preview, skip, disclosure or exit 0 is ever reached. The whole stub → skip → disclose → exit-0 contract A5 and K exist to deliver is reachable ONLY for archives whose over-parse-ceiling entries carry ZERO members — a shape no real packer emits.** **AND THE SUITE STRUCTURALLY CANNOT SEE IT: `tests/test_cli.cpp:141` guards payload emission with `if (entry_schemas[index] <= kEntrySchemaParseCeiling)`, so every over-ceiling fixture is built in precisely the one shape that avoids the gate. The tests are not wrong; they encode an unreal population, which is why every leg is green.** **MY `171122` VERDICT OF "QUICK-CHECK ONLY, NO BLOCKER, NO MUST-FIX" IS SUPERSEDED. The corrected verdict is REVIEW-FOLD REQUIRED, and the blocker is not a build fix — it asks whether the locked forward-compat contract is reachable in production at all, which is m-1's and m-3's to answer.** **THE PANEL EARNED ITS KEEP TWICE OVER: two independent lenses converged on the unreachability (security by the member gate, correctness-2 by flagging that the fixture "deliberately carries no payload members" and that reaching exit 0 could not be proven statically); two converged on the missing ceiling `static_assert`; two on the ungated `known_adapter` notice; and the test-coverage lens found a SECOND must-fix I had no line of sight to — the CI count/skip-identity gates in `.github/workflows/s2-harness.yml` are not updated for the three new cases, so BOTH CI rows go red, and `.github/**` is OUT of scope by my own dispatch.** **AND ONE OF THEM CAUGHT ME: the performance lens flagged that my panel briefing framed the render correlation as NEW ("the summary path NOW … does a find_if") when it is byte-identical at `d7db861`. I mis-stated provenance in the very prompt I wrote to hunt for it. That is my error, it is the discipline I have been applying to everyone else all session, and it is on the record here.** Nothing folded; `9729191` unchanged; merge BLOCKED; release hold ABSOLUTE.

ROLE: Planner
PHASE: RECONCILE
AUTHORITY: review-only
DISPATCH_ID: s4-floor-slice-e-successor-panel-recovered
PARENT_DISPATCH_ID: s4-floor-slice-e-successor-panel
IN_REPLY_TO: .relays/s4/s4-floor-impl/RECONCILE-PLANNER-SLICE-E-SUCCESSOR-PANEL-SEQUENTIAL-ONE-FINDING-ROUTED-20260816-171122.md
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: yes — the blocker asks whether the locked A5/K forward-compat contract is reachable in production at all. That is a DESIGN cell for m-1 and m-3, not a build fix. My prior quick-check-only verdict is SUPERSEDED. The land order binds. The release hold is ABSOLUTE.
DESIGN_DOC_ID: m1-addendum-K-20260816
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m1-addendum-K-5da667fa-lock-20260816
SECOND_DESIGN_LOCK: m3-addendum-4-9049de44-lock-20260816, m3-addendum-5-b8686c75-lock-20260816
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812, m3-addendum-3-eeb4dd01-lock-20260814
PLAN_LOCK_ID: s4-floor-slice-e-plan-20260812
FROM: s4-floor.planner
TO: s4.orchestrator-planner
CC: operator, s4.orchestrator-reviewer, s4-floor.implementer, master.orchestrator-planner, m-1.planner, m-3.planner
SUBJECT: RECONCILE — the panel DID run; all six reports recovered from disk. Verdict corrected to REVIEW-FOLD REQUIRED: one confirmed blocker (forward-compat path unreachable for any archive carrying real bytes), two must-fix, my 171122 verdict superseded

## 1. The correction I owe first

**My `171122` relay reported the panel as having failed.** That was wrong in its conclusion. **The panel ran.** All six lenses did full reviews — 6.4 KB to 10.5 KB of final report each — and every one is on disk under this session's `subagents/` directory. **What failed was delivery, not review.** The operator pointed me at the transcripts; I had treated an idle notification as evidence of no work, which is the same absence-blind error I have been naming in other people's instruments all session.

**Verdict change, stated plainly:**

```text
171122 (mine, sequential self-review)   quick-check only · no blocker · no must-fix
171641 (this, the real panel)           REVIEW-FOLD REQUIRED · 1 blocker · 2 must-fix
```

`171122` stands in the record unrewritten and is **superseded by this relay**.

## 2. BLOCKER — the forward-compat path is unreachable for any archive carrying real bytes

**Lens: security. Independently corroborated by correctness-2. Verified at the bytes at my seat before propagating — E1.**

```text
open.cpp:176-185   required_agent_members() builds the allow-set from entry.artifacts
                   and child.artifacts — nothing else
manifest.cpp:350   a STUB returns BEFORE artifacts are parsed  -> contributes NOTHING
open.cpp:280-282   if (agent && !required_agents.contains(member.meta.path))
                       -> UnmanifestedMember  -> exit 3
```

**Consequence.** A `.bvpk` whose schema-3 entry actually carries its `agents/…` transcript members is refused wholesale with `UnmanifestedMember` **before** `build_preview` runs. The skip is never counted, the notice never prints, `entry_schema_unparsed_count` is never emitted, and exit 0 is never reached. **The stub → skip → disclose → exit-0 behaviour that A5 and K were locked to deliver is reachable only for an archive whose over-ceiling entries carry no members at all.**

**Why no test sees it — and this is the part that matters most.** `tests/test_cli.cpp:141` gates payload emission on `entry_schemas[index] <= kEntrySchemaParseCeiling`. **Every over-ceiling fixture in the suite is therefore built in exactly the one shape that cannot trip the member gate.** The legs are not wrong and they are not fitted; they encode a population that a real packer does not produce. This is the impossible-population family A5 corrected twice in its own legs, now appearing one layer out in the fixtures.

**Direction is fail-closed** — no unaccounted member is ever accepted — so this is a reachability and honesty defect, not a safety hole. But the notice tells the user *"a newer version of biv may be able to import them"* about entries whose archive the current version refuses outright.

**This is not a build fix and I am not dispatching one.** It asks whether the locked contract reaches production, and the remedy is a design choice among at least three: parse `artifacts`/`children[].artifacts` before the stub return (m-1's parser surface); or lock "over-parse-ceiling entry carrying members = exit-3 refusal" and correct the A3.1 notice text (m-3's surface); or something else the owners see. **Routed to m-1 and m-3 via the orchestrator.**

**Live verification owed:** build a `.bvpk` with a schema-3 entry whose `agents/…` members are present in both the tar and `checksums`, run `biv open --json`, record the exit. The E1 reading predicts exit 3 / `UnmanifestedMember`. **No seat has run this; the prediction is static.**

## 3. MUST-FIX — the CI count and skip-identity gates are not updated, and the fix is out of my fence

**Lens: test-coverage. E1.**

```text
.github/workflows/s2-harness.yml:68-76    successes: 221 · skips: 2 · expected_skips = exactly 2 names
.github/workflows/s2-harness.yml:268-271  successes: 223 · skips: 0
```

The commit adds three `TEST_CASE`s, one of them an **unconditional** SKIP at today's ceilings. macOS `skips` becomes 3 and `set(skipped) != expected_skips` fires because `"threshold-parity per-agent distribution self-activates at R-4.29"` is not in the set; Linux `skips` becomes 1. **Both CI rows go red.**

**The sting: that skip-identity gate is precisely the instrument that stops a deferred test from silently masking its neighbours — and this commit adds a deferred test without registering it there.** `.github/**` is OUT of scope by my own dispatch, so the fix cannot be folded under the current token. **Routed as a scope cell**, with the counts to be re-derived from real `biv_tests -r xml` runs on both platforms rather than from anyone's arithmetic.

## 4. MUST-FIX — per-agent attribution of the new counter is unwitnessed

**Lens: test-coverage. E1.** Every head-active assertion on `entry_schema_unparsed_count` sits on a single-agent population or a hand-built `AgentPreview` that bypasses `build_preview`; the only two-agent witness is inside the deferred SKIP. **A mutant writing `preview.agents.front().entry_schema_unparsed_count++` instead of `found->` survives the entire active suite.** And the deferral is over-broad: `codex@3 + claude-code@3` yields unparsed = 1 on each *today*, so only the parity-dependent half needs the R-4.29 guard. Foldable inside the fence.

## 5. Convergence — where two lenses independently agreed

```text
unreachable forward-compat path   security #1  +  correctness-2 "live verification required"
missing ceiling static_assert     security #5  +  idiomaticity #1   (one line; include present)
notice not gated on known_adapter security #4  +  correctness-2 open question
empty image_session_id on stubs   security #2  +  test-coverage question  (also my own 171122 finding)
Row::skipped entry-schema arm is  correctness #2 + test-coverage #4 + correctness-2 fold-in #1
production-dead
```

**Convergence is the panel's real product.** Four of these five I did not have; the fifth (empty `image_session_id`) I found, and the panel rated it higher than I did.

## 6. Where the panel disagreed with ME

**The performance lens caught an error in my own briefing.** I wrote that the summary path *"now"* does an `id_map` `find_if` per installed row. **It is byte-identical at `d7db861`** — `git show d7db861:src/core/open/render.cpp` lines 309-329 hold the same loop, guard, filter and `find_if`; this commit adds one ternary. I mis-stated provenance in the very prompt I wrote to hunt for provenance errors. **Recorded because I have spent this whole slice insisting that inherited work not be misfiled as branch-created, and I did it myself.**

The performance verdict is `approve` with no findings, bounded rather than waved: the true cost is `A_skip × R + (Σ I_a) × M`, not `A × R × M`, and the hostile maximum requires ~50,000 successful installs to disk first. **It cannot become the bottleneck at any reachable N.**

## 7. Verdicts as returned

```text
security        must-fix   (1 Major blocker-class, 1 Major, 1 Moderate, 2 Minor, 1 observation)
test-coverage   must-fix   (2 Major, 3 Minor, 1 pre-existing question)
correctness     approve    (2 Minor)
correctness-2   approve    (no findings; both golden lines reconstructed and byte-compared TRUE)
idiomaticity    approve    (5 optional; no iterator invalidation, no sign-compare, header hygiene clean)
performance     approve    (no findings; bound given)
```

**Both correctness lenses independently reconstructed the A3 golden templates from the `<<` operands and byte-compared them against the sealed doc — both TRUE.** The conformance core of this commit is sound. What the panel found is that the contract it conforms to may not be reachable, and that the suite cannot observe the difference.

## 8. PANEL_CHOSEN record

```text
PANEL_CHOSEN: team-of-5 (+1 probe on a second agent type)
DEFAULT_ROLES_CHANGED: no
WHY_THIS_PANEL: C++/systems + production-risk; three coupled locked contracts across two
                domains on the untrusted-archive restore path
DELIVERY: all six returned full reports; none reached the lead seat. Recovered from the
          session's on-disk subagent transcripts at the operator's direction.
```

## 9. What I am NOT doing

**Not folding anything.** The blocker is a design cell; the CI gate is outside my fence; the two foldable items (per-agent witness, `static_assert`) should ride one dispatch with whatever the owners rule, not a separate churn. **No token, no product byte, no fixture change.** `9729191` stands exactly as verified.

ACTIONS_GIT_REF: no product, test or fixture edit at this seat — read-only. Recovered six subagent final reports from `~/.claude/projects/-Users-jack-Programming-bivpak/56e71dc2-.../subagents/*.jsonl` (read-only, at operator direction; no agent store written). Independently re-verified the blocker at `9729191`: `open.cpp:176-185` allow-set construction, `open.cpp:274-286` member gate, `tests/test_cli.cpp:141` payload guard. This relay + its INDEX row ride ONE explicit-path docs-lane commit whose SHA lands after filing.
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
- `.relays/s4/s4-floor-impl/RECONCILE-PLANNER-SLICE-E-SUCCESSOR-PANEL-RECOVERED-BLOCKER-20260816-171847.md` → `s4.orchestrator-planner`
- **CORRECTION: THE PANEL RAN.** My `171122` "panel failed" was wrong in conclusion — all six lenses produced full reports (6.4-10.5 KB each) and DELIVERY failed, not review. Recovered from the session's on-disk subagent transcripts at the operator's direction. I had treated an idle notification as evidence of no work — the same absence-blind error I spent the session naming in other instruments
- **VERDICT SUPERSEDED: `171122` quick-check-only → REVIEW-FOLD REQUIRED.** `171122` stands unrewritten in the record
- **BLOCKER, verified at MY seat before propagating (E1):** `required_agent_members` (`open.cpp:176-185`) builds the archive allow-set from `entry.artifacts`; a stub returns at `manifest.cpp:350` BEFORE artifacts parse, contributing nothing; `open.cpp:280-282` then refuses any unlisted `agents/…` member with `UnmanifestedMember` → exit 3. **An archive carrying real bytes for a schema-3 entry hard-fails the whole open before skip/disclosure/exit-0.** The locked A5/K forward-compat contract is reachable ONLY for archives whose over-ceiling entries carry ZERO members — a shape no real packer emits
- **AND THE SUITE CANNOT SEE IT:** `tests/test_cli.cpp:141` gates payload emission on `<= kEntrySchemaParseCeiling`, so every over-ceiling fixture is built in the one shape that avoids the gate. Impossible-population, one layer out from the legs A5 already corrected twice
- **NOT A BUILD FIX — DESIGN CELL routed to m-1 and m-3:** parse artifacts before the stub return (m-1 parser), or lock "over-ceiling entry with members = exit-3 refusal" and correct the A3.1 notice (m-3 surface), or owners' alternative. **Live falsifier owed and unrun:** schema-3 entry WITH members → `biv open --json` → predicted exit 3
- **MUST-FIX (out of my fence):** `.github/workflows/s2-harness.yml:68-76`/`:268-271` count and skip-identity gates unamended for 3 new cases — both CI rows go red, and the skip-identity gate is exactly the instrument that stops a deferred test masking neighbours. Counts to be re-derived from real runs, not arithmetic
- **MUST-FIX (foldable):** per-agent attribution of `entry_schema_unparsed_count` is witnessed only on single-agent or hand-built populations — a mutant writing to `agents.front()` survives the whole active suite; and the R-4.29 deferral is over-broad since two-agent unparsed attribution is testable TODAY
- **CONVERGENCE (the panel's real product):** two lenses each on the unreachable path, the missing ceiling `static_assert`, the `known_adapter`-ungated notice, the empty `image_session_id`, and the production-dead `Row::skipped` arm. Four of five I did not have
- **A LENS CAUGHT ME:** my panel briefing called the render `find_if` correlation NEW; it is byte-identical at `d7db861`. I mis-stated provenance in the prompt I wrote to hunt provenance errors. On the record
- **CONFORMANCE CORE IS SOUND:** both correctness lenses independently reconstructed the A3 golden templates from the `<<` operands and byte-compared them against the sealed doc — both TRUE. What is in doubt is the reachability of the contract, not the conformance to it
- NOTHING FOLDED; no token, no product byte; `9729191` unchanged; m-1 and m-3 byte reviews now carry the blocker too; branch LOCAL and UNPUBLISHED; merge BLOCKED; release hold ABSOLUTE
