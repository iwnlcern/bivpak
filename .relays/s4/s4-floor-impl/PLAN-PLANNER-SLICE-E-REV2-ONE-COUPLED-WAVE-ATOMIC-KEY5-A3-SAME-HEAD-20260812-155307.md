## PLAN rev2 (slice E) — **R1 is the finding of this cycle and it is a defect I introduced, not merely an under-specification.** My wave split would have shipped a commit whose product binary emits a **semantically FALSE manifest**: once wave 1 makes `child_ids` transitive, `manifest_entry_for` serializes C under R with no edge, and J's absence license reads absence as *"parent IS the entry primary"* — so the image would assert C is a direct child of R. **A publication hold does not make a lying producer a valid checkpoint.** Collapsed to ONE coupled post-m-1 implementation stage. R2 (`FX-A12-5` atomic) and R4 (A3's four checks on the SAME head) fixed with it. **R3 is routed UP at `155122` — I will not let a carrier decision be authored inside an implementation.**

ROLE: Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-floor-slice-e-plan-rev2
PARENT_DISPATCH_ID: s4-slice-e-design-m-2
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new operator gate to reach the plan gate. TWO cells gate the token, not this review: the cap-disclosure carrier (`155122`, OPEN) and the m-1 schema receipt (not yet landed). The lineage cell is NAMED-ERROR disposed at `154140`. The release hold is ABSOLUTE.
DESIGN_DOC_ID: m2-addendum-12-transitive-collect-mono-gate-20260812
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m2-addendum12-154cd87e-lock-20260812
TARGET_DESIGN_SHA256: 154cd87ebdc0619cdf3a7172da9b46d5753888da68f03a10ed6c18c481ff4c77
TARGET_DESIGN_COMMIT: 3929c9c944ba2bdc576cbe3ee2ceceae8a0cfe8b
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812
PLAN_LOCK_ID: s4-floor-slice-e-plan-20260812
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-REVIEW-IMPLEMENTER-SLICE-E-REV1-MUST-REVISE-COSEQUENCE-CARRIER-A3-20260812-154600.md
RELATED_CONTEXT: .relays/s4/s4-floor-impl/SITREP-PLANNER-SLICE-E-CAP-REFUSAL-CARRIER-SEAM-ROUTED-20260812-155122.md (R3 routed, OPEN); .relays/s4/s4-floor-impl/DISPOSITION-ORCHESTRATOR-PLANNER-SLICE-E-LINEAGE-NAMED-ERROR-DISPATCH-UNBLOCKED-20260812-154140.md (lineage disposed); .relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-C1-RECAPTURE-GRANTED-B1-RELEASES-FOUR-CHECKS-20260806-002730.md (the A3 four-check grant); .relays/s4/s4-floor-impl/PLAN-PLANNER-SLICE-E-REV1-EXACT-SCOPE-FOUR-CAPS-EIGHT-KEYS-WAVED-20260812-153157.md (rev1, superseded)
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: s4.orchestrator-planner, operator, s4.orchestrator-reviewer, master.orchestrator-planner, m-2.planner
SUBJECT: PLAN rev2 — one coupled post-m-1 implementation stage (no false intermediate producer); FX-A12-5 atomic; A3's four checks on the same reviewed head with the codex literal classes named; cap-disclosure carrier routed OPEN

## 0. Your four findings, re-derived at the bytes before acceptance

```text
R1  pack.cpp at 0db8fdd: manifest_entry_for loops session.child_ids and builds flat
      SessionChild{original_id, artifacts} with NO parent position (:387-400).
    A12.2.5 + J-R1: parent_id ABSENT means "the parent IS the entry primary" — and an explicit
      parent_id naming the primary is REFUSED as a second spelling of that same state.
    => transitive child_ids on the flat writer emits "C is a DIRECT CHILD OF R". FALSE DATA,
       not missing data. Your R1 is correct and it is the most serious defect in rev1.   CONFIRMED
R2  A12.6 key 5: "ONE concrete artifact, TWO EXECUTED variants, BOTH expected outcomes
      asserted … BOTH-REFUSED also FAILS." Splitting v0/vE across dependency states makes the
      key creditable before the variant that discriminates the implementations has ever run.
      That is my own "validate the discriminator" rule, broken by me.                    CONFIRMED
R3  J e30f845:226-231 + :245-249 (pack FAILS TYPED AND LOUD, naming cap AND entry) vs
      A12.4.1 (that entry MUST produce a CollectReport.warnings line), against
      pack.cpp:498 cleanup_error discarding `report` and :553-559 draining collected->warnings
      BEFORE the loop that can fail; adapter.hpp:281 collect() is expected<CollectReport> so
      the seam repeats one layer down.                          CONFIRMED — ROUTED UP at 155122
R4  002730, the grant's operational text: per recapture head H changing anchored file F —
      FOUR checks, ONE review, THE SAME HEAD; "PER-HEAD, never batched." My E6 anchor-only
      commit cannot satisfy check 1, and I named neither check 3 nor check 4.             CONFIRMED
```

**One clarification, not a challenge.** You cite `pack.cpp:379-423` and I measured `manifest_entry_for`
opening at `:384` with the `children` loop at `:387-400` and the return running to `:433`. Different spans,
same function, same finding — the mechanism you identified is exactly right and the emission edit lands in
that loop.

## 1. R1 — ONE coupled implementation stage. The intermediate producer is deleted, not deferred.

**Deleted from rev1: the claim that wave 1 is "UNBLOCKED TODAY."** It was true only of the *edits* and false
of the *product*, and a plan that says a stage is unblocked when its output would misrepresent the operator's
data is a plan that has smuggled a defect past its own gate. The proceed-to-plan called this **"one coupled
slice, not separable"** and I split it anyway.

```text
STAGE 0 — PREPARATION. Provably inert. Cut from origin/main = 0db8fdd.
  INVARIANT (the thing that makes it legal): NO commit in stage 0 may change ANY byte that
  `biv pack` or `biv open` emits, or any value `collect()` returns. Specifically:
    - `child_ids` semantics UNCHANGED. No closure, no traversal change, no emit change.
    - `src/adapters/codex/codex.cpp` IS NOT TOUCHED AT ALL in stage 0 — which also means no
      anchor moves and no A3 ceremony fires here.
  PERMITTED: the eight RED fixtures (they fail, that is the point); fixture trees; the
    `child_parent_map` member DECLARED on SessionRecord and populated by nothing.
  PROOF the invariant held: the full suite is green apart from the intended REDs, and keys 2
    and 7 run here as BASELINE CONTROLS establishing the pre-change value.

STAGE 1 — THE COUPLED IMPLEMENTATION. Opens ONLY on the m-1 receipt. One behavior change.
  transitive closure + child_parent_map population + rootless disposition + both identity gates
  (root-mapped AND monotone) + warning producers + manifest_entry_for edge emission + the four
  producer caps — TOGETHER, on the combined tree, because the manifest carrying the edge and the
  adapter producing transitive descendants are one fact expressed in two files.
```

**THE COMBINED-TREE CHECKPOINT, named as you asked.** The branch is rebased onto the m-1 receipt SHA, and
**that tree is the first point at which keys `1a`, `1b`, `2` (its `parent_id`-absence arm), `4a`, `5` (both
variants) and the E2E are MEANINGFUL AND CREDITABLE.** Nothing before it may be reported as a key.
`0db8fdd` remains named as the AUDIT cut point; the rebase target is a different thing and the report must
say both.

**The stop gate, unchanged and checkable:** wave... **stage** 1 opens when an m-1 implementation receipt
names a commit on `origin/main` where (i) `manifest::SessionChild` carries an optional `parent_id`,
(ii) the writer emits it and the parser validates it, (iii) the parser enforces J's four per-entry caps with
the typed whole-entry refusal. **Measured today: `SessionChild` is `{original_id, artifacts}` and
`git grep -c parent_id 0db8fdd -- src/core/manifest` returns 0. The receipt does not exist.** Stage 1 is
BLOCKED — not flagged, not stubbed, not simulated behind anything.

## 2. R2 — `FX-A12-5` is ONE artifact with TWO EXECUTED variants, credited once

Authored as a single test artifact over **one** `R←P←C` artifact, with **both** variants executed and **both**
outcomes asserted in the same case:

```text
variant 0   C's parent_id ABSENT,   C's bytes name P   -> EXPECT ACCEPT   (mapped-node membership)
variant E   identical bytes/nodes,  C's parent_id = P  -> EXPECT ACCEPT   (membership + edge consistency)
BOTH-REFUSED FAILS the key.   rev0's edge-derived-expected-parent predicate FAILS variant 0.
```

**It runs and is credited ONLY at the combined-tree checkpoint.** No partial-key receipt exists and none may
be reported. If an absent-edge helper is useful earlier it is named **preparation**, never a key-5 result.
**`FX-A12-4a` stays the separate edge-narrowing refusal arm** — that independence is what keeps edge
narrowing alive while key 5 kills the grant direction, and collapsing them was rev0's error.

## 3. R3 — the cap-disclosure carrier is OPEN, routed, and gates the token

All four caps stand exactly as rev1 bound them: **1024 nodes / 64 depth / 256 artifacts per declared node /
4096 total, per entry, whole-entry refusal, never truncation, at-cap ACCEPT and cap+1 REFUSE arms for each,
the refusal naming BOTH the entry and the cap.** What is OPEN is only **which surface carries the disclosure**
— J requires a typed loud `pack` failure and `A12.4.1` requires a `CollectReport.warnings` line, and at
`0db8fdd` the fatal discards the carrier (`pack.cpp:498` vs the `:553-559` drain; `collect()` is itself
`expected<CollectReport>`). **Routed UP at `155122` with three options and a recommendation I do not act on.**

**Whichever way it lands, BOTH killing arms are required and neither is optional:**

```text
a typed failure WITHOUT the required disclosure  -> the test FAILS
the required disclosure WITHOUT a typed failure  -> the test FAILS
```

**Do not choose a carrier during implementation.** If the answer has not arrived when stage 1 otherwise
opens, the cap arms wait; the rest of stage 1 does not depend on them.

## 4. R4 — A3, per the `002730` grant's operational text, on the SAME reviewed head

```text
Per recapture head H changing anchored file F — FOUR checks, ONE review, THE SAME HEAD:
 1. H's diff shows F's change + the ONE corresponding anchor-literal update and nothing else anchor-side
 2. the review RE-DERIVES F's whole-file hash at H and matches the new literal
 3. for F's leg, each 153958 §4 read-side session literal is MUTATION-CHECKED — a disposable local
    mutation goes RED under the harness, is REVERTED, and is recorded as mutation diff + failing assertion
 4. the review states that H's own diff touches none of those literals — CLASS-SCOPED: NAME the classes,
    never assert the bare negative
Scope: "every Step-4 slice head that changes an anchored file; PER-HEAD, never batched."
```

**The structural fix: all `codex.cpp` changes land in ONE head, so exactly one ceremony fires.** RED fixtures
land first (test-only, no anchor moves, stage 0), then stage 1's `codex.cpp` implementation lands **together
with its single `_ADAPTER_SOURCE_ANCHORS` codex-pin update in the same commit** — which is the only shape
that can satisfy check 1. **rev1's separate E6 anchor-only commit is deleted.**

**`codex/install.cpp` moves NO pin.** The `153958` mechanism excludes `install.cpp` normatively — it is
write/restore-side, cannot desync `SESSION_LOCATIONS`, and is policed by the restore round-trip. Do not run
the ceremony for it, and do not let its presence in scope suggest a second anchor.

**Check 3's literal classes for F = `codex.cpp`, located at `0db8fdd` and to be RE-LOCATED at the head
(these line numbers WILL move under our own edits — re-derive them, do not carry them):**

```text
sessions-root locator          codex.cpp:1136   StoreLocator{"sessions_root", root / "sessions"}
archived-sessions locator      codex.cpp:1145-1149  root / "archived_sessions"
sqlite selection               codex.cpp:1191-1198  locator.path / "state_5.sqlite", store.root fallback
sqlite_home configuration      codex.cpp:1123   config_string(root / "config.toml", "sqlite_home")
rollout path construction      codex.cpp:625    root / "sessions" / year / month / day
```

Mutation-check each: mutate, observe RED under the harness, revert, record the mutation diff and the failing
assertion. **Check 4 is CLASS-SCOPED** — name those five classes and show our diff touches none of them.
Our edits sit in `session_for` (`:452`), the grouping/emit block (`:1294-1300`) and the staged reader
(`:700-818`); **note that the staged-reader region carries image-internal path literals (`:707`
`.biv/agents/codex`) which are NOT the C1 host-store class — say which class you checked and why that one is
not it, rather than a bare "touches none."**

**`claude_code.cpp`'s pin must NOT move.** If it does, a claude production file changed — a scope breach, not
a recapture, since key 7 asserts claude is unchanged.

**Burden report, per the grant's own trigger.** `002730` registers R-3.40 item (11) upstream and says its
trigger is *the four-check ceremony proving burdensome across the slices* — *"if it does, SAY SO in your
sitreps rather than absorbing the cost."* Single-head consolidation is my attempt to keep it proportionate;
**if it still proves burdensome, report it rather than absorbing it.**

## 5. Unchanged from rev1 and still binding (do not re-litigate; do re-read)

**Scope** (§1 of rev1) — IN: `adapter.hpp`, `codex.cpp` (ANCHORED), `codex/install.cpp`, `pack.cpp`,
`tests/test_adapter_codex_collect.cpp`, `tests/test_adapter_codex_install.cpp`,
`tests/test_adapter_claude_collect.cpp` (key 7's home), `tests/test_pack.cpp`, `tests/test_cli.cpp`,
`tests/fixtures/slice-e/**`, and `harness/bivharness/e3.py` for the codex pin ONLY — now inside stage 1's
single anchored head per §4. HARD-OUT: `manifest.hpp`/`manifest.cpp` (fence-2), `.github`, sealed docs,
m-3's `sessions.cpp:344` / `render.cpp:244-245` / `report/envelope.cpp:125`,
`harness/selftest/test_e3_asserts.py`. CONDITIONAL-OUT, individually named and each requiring a STOP-and-route:
any `src/core/open/*` file, `rewrite_common.cpp`, every claude production file.

**Semantics** (§3 of rev1) — traversal unbounded with a visited set / emission J-capped with typed
whole-entry refusal; `child_ids` stays a flat SET answering WHICH while `child_parent_map` answers WHOSE and
`child_artifact_map` is NOT reused; rootless detection with the **lexicographically least CYCLE MEMBER** as
synthetic primary and that member's outgoing edge omitted, artifacts carried exactly once, the omitted edge
NAMED; the gate accepting on mapped-node membership with the edge NOT consulted and refusing additionally on
a present disagreeing edge, so `A(E) ⊆ A(0)` by construction; warnings on `CollectReport.warnings`, no
warnings member added anywhere.

**Evidence** (§6 of rev1) — the three-level actual-binary E2E asserting three installed rollouts, distinct
mapped-root and immediate-parent identities both resolving, and the leaf's marker bytes READ BACK; three
sanitized claude reference-resolution controls (flat bare-hex, flat slug-hex, nested `subagents/<wf>/`);
coverage stated as AXES, never a distribution; `ScopedPackDiscoveryEnv` + `require_store_roots_under` with a
credential-shaped decoy asserted never opened, packed or copied; **NEVER the live `~/.claude`/`~/.codex`**;
full macOS presets + `git diff --check`; local Ubuntu 24.04 `linux/amd64` Docker parity as the GOVERNING
Linux signal with its three disclosed divergences; **Actions NOT invoked**; the base-container control on any
change in the Linux failure-set count; the `.github` Catch2 count gates named as an inherited already-stale
pin (221/223 vs the 385-case landed B2 head), hard-out, routed not folded.

**Branch** (§7 of rev1) — cut from `origin/main` (= `0db8fdd`), NEVER local `main` (169 behind); publication
HELD; D-5.5(a) measured AT HAND-UP as `git rev-list --count origin/main..<branch-cut-point>`.

**Constraints** (§8 of rev1) — R-4.20 edge-refuses-only with mint sites `:122/:430/:455` and NOT `:507-513`;
MONO; producer closure; typed refusal never silent truncation; M4-CG-0; R-4.24 is m-3/m-1's.

## 6. Gate state, stated once and precisely

```text
lineage cell        DISPOSED   named-error at 154140; red carried DISCLOSED, not silenced
cap carrier (R3)    OPEN       routed 155122 — gates the token
m-1 schema receipt  ABSENT     measured; gates stage 1
plan gate           THIS RELAY
```

**No `DISPATCH IMPL` token issues from my seat until the plan gate returns approve AND the `155122` cell is
answered.** Stage 1 additionally waits on the m-1 receipt; stage 0 is dispatchable the moment the first two
clear, since it touches no behavior and no anchor.

## 7. What I am asking of you

**A plan review.** Grade the plan: is the stage-0 inertness invariant actually sufficient to guarantee no
behavior byte moves, is the combined-tree checkpoint named precisely enough to be checkable, does the single
anchored head satisfy all four A3 checks as the grant words them, and is anything here still a design
decision I had no authority to make? Reply with `PLAN_REVIEW_VERDICT: approve` or `must-revise` (verdict line
BARE — no bold, no backticks; remarks via em-dash only, per the matcher's recorded grammar). Merge ≠ push ≠
release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — each finding re-derived at the bytes (`manifest_entry_for`'s flat `SessionChild` construction and J's absence-license meaning; A12.6's key-5 atomicity clause; the `pack.cpp:498` / `:553-559` / `adapter.hpp:281` disclosure seam; the `002730` four-check operational text and the `153958` two-arm mutation mechanism; the five codex read-side literal classes at `0db8fdd`; `SessionChild` and the 0 `parent_id` hits under `src/core/manifest`); this relay + its INDEX row ride one explicit-path docs-lane commit whose SHA lands after filing
RELAY_LINT: per D-3.4 — per-file WITH freshness before filing; INDEX tail re-read; `--index`; and the `--relay-root` arm run per the orchestrator's standing instruction. Disclosed reds: INDEX line 222 (pre-existing sibling class, not mine) and the cross-repo lineage red, NAMED-ERROR disposed at `154140` and carried disclosed per that disposition
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to this relay and `.relays/s4/INDEX.md`

CARRY LIST:
- `.relays/s4/s4-floor-impl/PLAN-PLANNER-SLICE-E-REV2-ONE-COUPLED-WAVE-ATOMIC-KEY5-A3-SAME-HEAD-20260812-155307.md` → `s4-floor.implementer`; rev1 `153157` SUPERSEDED
- **R1 accepted in full and it was mine:** transitive `child_ids` on the flat writer emits C as a DIRECT CHILD OF R under J's absence license — FALSE DATA, not missing data; a publication hold does not make a lying producer a valid checkpoint. Collapsed to STAGE 0 (provably inert: no behavior byte, `codex.cpp` untouched, no anchor moves) + STAGE 1 (one coupled post-m-1 change), with the combined-tree checkpoint NAMED as the first creditable point for keys 1a/1b/2-absence/4a/5/E2E
- **R2:** `FX-A12-5` is ONE artifact, TWO EXECUTED variants, BOTH outcomes asserted, credited once at the combined tree; both-refused fails; `FX-A12-4a` stays independent
- **R3 ROUTED at `155122` and OPEN** — J's typed loud `pack` failure vs `A12.4.1`'s `CollectReport.warnings` line, with the fatal discarding the carrier; all four caps otherwise unchanged; both killing arms (fatal-without-disclosure, disclosure-without-fatal) required whichever way it lands; **no carrier is chosen during implementation**
- **R4:** all `codex.cpp` changes in ONE head carrying its ONE pin update (the only shape satisfying check 1); the separate anchor-only commit DELETED; four checks listed verbatim; the five codex read-side literal classes named for mutation-checking with a re-derive-at-head warning; check 4 CLASS-SCOPED incl. why the staged-reader's image-internal literals are not the C1 class; `codex/install.cpp` moves no pin (`153958` excludes it normatively); the claude pin must NOT move; burden reported per the grant's own R-3.40(11) trigger rather than absorbed
- gates: lineage DISPOSED (`154140`), cap carrier OPEN (`155122`), m-1 receipt ABSENT (measured), plan gate = this relay; **no token until approve AND `155122` are both in hand**; release hold ABSOLUTE
