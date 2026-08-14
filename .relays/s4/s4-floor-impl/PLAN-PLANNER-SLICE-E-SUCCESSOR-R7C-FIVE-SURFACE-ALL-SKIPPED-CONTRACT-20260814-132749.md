## PLAN (successor r7c, slice E) — **you found the mutant that survives my mutants, and that is the sharpest possible finding against a plan whose whole claim was falsifier coverage.** Widen the one shared `any_sessions()` predicate to `eligible > 0 || skipped > 0` and every r7b test goes green — the disclosure renders, the all-skipped outer mutant dies, the inner and placement legs pass — **while an inert consent prompt appears on a write that cannot occur and a trust warning fires about content that never reaches the host.** Sealed `A3.2(4)` excludes exactly that observable result, per surface, and I had carried two of its five. **Read at the bytes: `any_sessions()` has FIVE consumers, three of them m-3 UX, and the design says in its own voice that leaving the mechanism open "was not a deferral to m-1 — it was an undeclared m-3 ruling handed to whoever typed the fix."**

ROLE: Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-floor-slice-e-plan-successor-r7c
PARENT_DISPATCH_ID: s4-floor-slice-e-design-complete
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — the operator's consumer-scope assignment remains open and non-blocking to planning; every domain veto, the implementation token, publication and release keep their own gates. The release hold is ABSOLUTE.
DESIGN_DOC_ID: m2-addendum-12-transitive-collect-mono-gate-20260812
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m2-addendum12-29a5b3a3-lock-20260812
TARGET_DESIGN_SHA256: 29a5b3a3abb6777af70a1c959728f4f61731489a1735773e81713b5aa3ea3adb
TARGET_DESIGN_COMMIT: 6eeeb157be249792d61774016485d97c303e2c8f
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812
CONSUMER_DESIGN_LOCK_ID: m3-addendum-3-eeb4dd01-lock-20260814
CONSUMER_TARGET_DESIGN_SHA256: eeb4dd01cc907b5dc793a7a27892395a8af258f4967a38fd744f2b424013c7aa
CONSUMER_TARGET_DESIGN_COMMIT: a016f9532d6a4abff2d4e642062f8127efa0eae8
CONSUMER_POST_STAMP_SHA256: cefd3f799b571bea511b362583c97e1a856dbf07b97a4a948882d74705a6db67
PLAN_LOCK_ID: s4-floor-slice-e-plan-20260812
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-REVIEW-IMPLEMENTER-SLICE-E-SUCCESSOR-R7B-MUST-REVISE-FIVE-SURFACE-OUTER-CONTRACT-20260814-132540.md
RELATED_CONTEXT: .relays/s4/s4-floor-impl/PLAN-PLANNER-SLICE-E-SUCCESSOR-R7B-TWO-SUPPRESSION-PATHS-BOUND-20260814-131510.md (r7b — its inner-guard and pre-write mutants PASSED and carry); .relays/s4/s4-floor-impl/PLAN-PLANNER-SLICE-E-SUCCESSOR-R7-THREE-PINS-CONSUMER-NOTICE-BOUND-20260814-130641.md (r7, the amended base)
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: s4.orchestrator-planner, operator, s4.orchestrator-reviewer, master.orchestrator-planner
SUBJECT: PLAN (successor r7c) — the five-surface all-skipped contract carried with both outer mutant classes and the four split populations; behavioral split stated without choosing m-1's mechanism

## 1. Why my falsifier set was insufficient — the shape, not just the gap

**A mutant that passes every test in a plan built on mutants is the one finding that indicts the method
rather than the coverage.** Mine killed the *eligible-only* outer predicate. It could not see the *widened
shared* predicate, because both make the disclosure render — and I had only asked whether the disclosure
renders. **The two mechanisms are not observationally equivalent, and the design says so in its own voice:**

```text
"the mechanisms are not observationally equivalent: widening the shared predicate also makes an
 all-skipped image eligible for a consent prompt, a trust warning and a session summary, while
 adding separate gates for two surfaces leaves the other three suppressed."
"rev3 specified the disclosure and the JSON envelope and left the mechanism open. THAT WAS NOT A
 DEFERRAL TO m-1 — IT WAS AN UNDECLARED m-3 RULING HANDED TO WHOEVER TYPED THE FIX."
```

**I reproduced the same defect one level down:** by binding two surfaces and leaving the other three
unstated, my plan handed the same undeclared ruling to whoever typed the fix.

## 2. The five consumers and the ALL-SKIPPED contract, carried verbatim

```text
any_sessions() == (parent_count != 0 || child_count != 0)   [sessions.cpp, any agent]
M3-J-4: every over-schema entry contributes ZERO to BOTH counts
FIVE CONSUMERS at 0db8fdd, all reading the same predicate:
  disclosure      pre-write stderr notice
  consent prompt  render_prompt_b, interactive TTY only
  trust warning   kTrustWarning, the non-prompt paths
  json envelope   the sessions report inside the machine envelope
  text summary    render_summary, the final non-JSON report

THE ALL-SKIPPED CONTRACT — zero eligible entries, at least one skipped:
  disclosure      RENDER    the whole point; the user must learn entries were skipped
  json envelope   PRESENT   with entry_schema_skipped_count; a script must see the skip
  text summary    RENDER    carrying the A3.2(5) aggregate line — byte-exact, per agent
  consent prompt  SUPPRESS
  trust warning   SUPPRESS
```

**The suppressions are reasoned, not incidental, and the plan carries the reasons so nobody "fixes" them:**
the prompt asks permission for **a write that cannot occur** — both answers are identical, so it implies an
import that is not available, and an inert consent question teaches the user that these prompts are
formalities, degrading the one prompt in v1 that guards a host write. The trust warning **warns about content
that will reach the host**, and nothing reaches it — safe precisely because it is keyed to the write, not the
image, so an eligible entry brings it back. **The summary renders where the prompt does not** because the
JSON envelope publishes the skip, and a suppressed summary would leave the machine and human surfaces
disagreeing about the same run.

**`A3.2(5)` aggregate line — byte-exact, per agent, emitted only when that agent's skipped count is ≥ 1,
placed immediately after the per-row loop and before the activation lines:**

```text
  <agent>: <imported> session(s) imported; <skipped> session(s) skipped — recorded in a format this version of biv cannot read.
```

Not "count the rows yourself": `M3-J-6` exists because a shape that cannot say **how many** is not a
disclosure, and parity with a machine surface publishing an explicit count cannot be met with an inferable
one. **Per agent, never one global N** — a global figure would be a third framing of one fact on a third
surface.

## 3. Both outer mutant classes, and the four populations kept SEPARATE

```text
(h1) biv open <image> --json          disclosure PUBLISHED and envelope carries
                                      entry_schema_skipped_count — the one invocation where both
                                      machine-side surfaces are observable together
     MUTANT A  leave any_sessions() eligible-only with M3-J-4 in force  => BOTH vanish => RED
(h2) interactive TTY, no consent flag disclosure PUBLISHED; NO consent prompt; summary carries the
                                      A3.2(5) line byte-exact with <imported> = 0
     MUTANT B  satisfy (h1) by WIDENING THE SINGLE SHARED PREDICATE => the prompt appears => RED
               ** this is the leg that makes the mechanism choice OBSERVABLE rather than free **
(h3a) non-TTY, NO consent flag        reaches deny-default. disclosure PUBLISHED; NO trust warning;
                                      summary carries the A3.2(5) line with <imported> = 0
     MUTANT B  the same widening => the warning appears => RED
(h3b) interactive TTY, --consent yes  affirmative consent supplied, so prompt_requested is false for a
                                      DIFFERENT REASON than in (h3a). disclosure PUBLISHED; NO trust
                                      warning; summary carries the A3.2(5) line with <imported> = 0
     MUTANT B  the same widening => the warning appears => RED
```

**`h3a` and `h3b` do NOT collapse into one disjunctive leg.** The design split them precisely because they
are distinct control-flow populations and **a single fixture could satisfy the pair by half** — the same
defect class as an assertion nobody watched run. **Four legs, four fixtures.**

## 4. The behavioral split, stated WITHOUT choosing m-1's mechanism

```text
KEY ON eligible OR skipped   disclosure · json envelope · text summary
KEY ON eligible ALONE        consent prompt · trust warning
NOT OURS                     the count SOURCE and the PREDICATE MECHANISM are m-1's. Whether that is
                             separate gates, a second predicate, or something else is theirs to choose.
OURS TO BIND                 the OBSERVABLE m3 behavior above, which is locked and not open.
```

**This is the line r7b blurred:** I may not pick the mechanism, and I may not leave the observable outcome
unstated because the mechanism is someone else's. **Stating the outcome without the mechanism is exactly
what keeps the ruling declared instead of handed to a keyboard.**

## 5. Carried unchanged

r7b's **inner-guard** mutant (nest under `caps`/`probe`; unprobed agent, skipped ≥ 1 ⇒ RED) and **pre-write
placement** mutant (move past the first write or past `render_summary` ⇒ RED), both reviewed and passed, with
the carrier consumed unchanged at the `run_session_leg` leg. `A3.1`'s golden notice and `A3.2(1)`'s
zero-renders-nothing rule; `A3.3`'s `entry_schema_skipped_count` beside `primary_count`/`descendant_count`,
no removal and no re-type; `A3.4`/`A3.7`'s fact boundaries. The three pins and the full consumer identity.
The three-halves scope with the **consumer half NAMED-IF-GRANTED and `src/core/open/sessions.cpp` HARD-OUT**
until the operator assigns it. Stages 1a → 1b-i → 1b-ii; the **merge-gate predicate** with the
**1a-merges-early narrowing still REFUSED**. The manifest half under the (A) fence and m-1's byte-level veto
with the three STOPs and five VETOES; the J-capable reader transition and its three schema tests; the
**base-`0db8fdd`-binary** compatibility falsifier; `FX-A12-3`'s never-executed legs owed at 1b-i with the
least-of-component mutation falsifier; the cap carrier, the atomic-absence oracle and the three semantic
killing arms; A3's four checks on ONE `codex.cpp` head; sandbox guards and the credential decoy, **NEVER the
live `~/.claude`/`~/.codex`**; macOS plus **governing** local Ubuntu 24.04 `linux/amd64` Docker, **Actions
NOT invoked**; the base-container control; branch cut from `origin/main` never local `main`; publication
HELD; D-5.5(a) at hand-up; the token-time seven-element tuple with all three hashes re-derived at that act.
**Stage 0 ACCEPTED and unpublished at `dca6b7d`.** **Routing per `021028`: no cross-domain destination named.**

## 6. What I am asking of you

**A plan review.** Are the five surfaces bound tightly enough that neither mechanism can be chosen by
accident; do MUTANT A and MUTANT B genuinely separate the eligible-only implementation from the
shared-widened one; are the four populations stated so no fixture can satisfy two of them by half; and does
§4 state the observable without straying into m-1's mechanism? Reply with `PLAN_REVIEW_VERDICT: approve` or
`must-revise` (verdict line BARE — no bold, no backticks; remarks via em-dash only, per the matcher's
recorded grammar). **On approve, Stages 1a and 1b-i are dispatchable to BUILD; nothing merges.** Merge ≠
push ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — read `A3.2(4)`'s five-consumer census, the all-skipped per-surface contract and both suppression rationales, `A3.2(5)`'s byte-exact aggregate line and its placement, and legs `h1`/`h2`/`h3a`/`h3b` with their mutants, all at m3-addendum-3's sealed bytes `a016f953`; the three pin hashes were re-derived at r7's act and are not re-claimed fresh; this relay + its INDEX row ride ONE explicit-path docs-lane commit filed under a single unbroken `&&` chain
RELAY_LINT: per D-3.4 — per-file WITH freshness, INDEX tail re-read, append, `--index`, add and commit in ONE `&&` chain with no semicolon. Disclosed reds: INDEX line 222 (inherited) and the `013935`/`014004` tail inversion from the first sweep; two relays remain deliberately unindexed and are named in the `130923` row
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to this relay and `.relays/s4/INDEX.md`

CARRY LIST:
- `.relays/s4/s4-floor-impl/PLAN-PLANNER-SLICE-E-SUCCESSOR-R7C-FIVE-SURFACE-ALL-SKIPPED-CONTRACT-20260814-132749.md` → `s4-floor.implementer`; amends r7/r7b, everything not named here stands
- **you found the mutant that survives my mutants** — widening the single shared `any_sessions()` predicate greens EVERY r7b test while producing an inert consent prompt on a write that cannot occur and a trust warning about content that never reaches the host. **A mutant that passes a mutation-based plan indicts the method, not the coverage**
- **I reproduced the design's own recorded defect one level down:** it says leaving the mechanism open "was NOT a deferral to m-1 — it was an UNDECLARED m-3 RULING HANDED TO WHOEVER TYPED THE FIX," and by binding two of five surfaces I handed the same ruling to the same keyboard
- **five consumers, all reading one predicate** (disclosure · consent prompt · trust warning · json envelope · text summary) with the **ALL-SKIPPED contract carried verbatim**: RENDER / PRESENT-with-`entry_schema_skipped_count` / RENDER-with-the-`A3.2(5)`-aggregate / SUPPRESS / SUPPRESS — **with the suppression REASONS carried so nobody "fixes" them** (a prompt for a write that cannot occur teaches users these prompts are formalities; the warning is keyed to the WRITE not the image; the summary renders because a machine surface publishing the skip and a silent human surface would disagree about one run)
- **`A3.2(5)` byte-exact aggregate**, per agent, only when skipped ≥ 1, immediately after the per-row loop and before the activation lines — **not "count the rows yourself,"** since `M3-J-6` exists because a shape that cannot say HOW MANY is not a disclosure
- **two mutant classes:** MUTANT A (eligible-only predicate with `M3-J-4` in force ⇒ disclosure AND envelope vanish) and MUTANT B (**widen the single shared predicate ⇒ prompt/warning appear**) — B is the leg that makes the mechanism choice OBSERVABLE rather than free. **Four populations kept SEPARATE — `h1`, `h2`, `h3a`, `h3b` — because `h3a`/`h3b` are distinct control-flow paths and a single fixture could satisfy the pair BY HALF**
- **behavioral split stated WITHOUT choosing m-1's mechanism:** disclosure/envelope/summary key on eligible-or-skipped, prompt/warning key on eligible alone; the count source and predicate mechanism stay m-1's, the observable m3 behavior is locked and ours to bind
- r7b's inner-guard and pre-write mutants carry, as does everything else incl. the merge gate, the refused narrowing, `sessions.cpp` HARD-OUT and Stage 0 ACCEPTED at `dca6b7d`; release hold ABSOLUTE
