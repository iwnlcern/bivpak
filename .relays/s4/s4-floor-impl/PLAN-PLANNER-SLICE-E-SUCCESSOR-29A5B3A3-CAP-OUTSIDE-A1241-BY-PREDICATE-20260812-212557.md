## PLAN (successor, slice E) at the CURRENT pin `29a5b3a3` — **every pin re-derived AT THIS FILING ACT, not carried**, which is the instrument I adopted after filing two plans against a dead lock. **The cap-carrier cell I routed is RESOLVED, and the basis matters more than the outcome: the cap refusal is outside `§A12.4.1` BY ITS OPERATIVE PREDICATE — a whole-entry refusal emits no entry for material to be omitted from — and `§A12.4.2` + J's typed loud fatal carry it. My recommended reasoning ("a typed error DISCHARGES the warnings clause") was REJECTED and is NOT encoded here**, because it would have licensed discharging the other `§A12.4.1` items the same way, and those are real drops on a surviving report. **One disclosure the carry-down did not contain: the locked document's own `STATUS:` block still says the VP `§A12.6` re-verification and the operator re-waiver "have NOT run" — both are STALE, and I show why at the bytes rather than leaving a future reader to read them as open gates.**

ROLE: Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-floor-slice-e-plan-successor
PARENT_DISPATCH_ID: s4-slice-e-cap-carrier-routeup-charter-act-review
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new operator gate — W-1 is concurred and effective, and Addendum-12 rev8 is locked and VP-re-approved at this pin. The remaining gates are mine and independent: this PLAN, its local PLAN-REVIEW approve, token-time tuple re-verification, then merge/seal/publication/release. The release hold is ABSOLUTE.
DESIGN_DOC_ID: m2-addendum-12-transitive-collect-mono-gate-20260812
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m2-addendum12-29a5b3a3-lock-20260812
TARGET_DESIGN_SHA256: 29a5b3a3abb6777af70a1c959728f4f61731489a1735773e81713b5aa3ea3adb
TARGET_DESIGN_COMMIT: 6eeeb157be249792d61774016485d97c303e2c8f
SUPERSEDED_DESIGN_LOCK_ID: m2-addendum12-154cd87e-lock-20260812
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812
PLAN_LOCK_ID: s4-floor-slice-e-plan-20260812
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-SLICE-E-BOTH-GATES-CLEAR-PIN-MOVED-SUCCESSOR-PLAN-29A5B3A3-20260812-211825.md
RELATED_CONTEXT: .relays/s4/s4-floor-impl/RECONCILE-IMPLEMENTER-SLICE-E-DESIGN-RECORD-ABSENT-REV6-PENDING-20260812-173115.md (the concur that held the line while the design moved); .relays/s4/s4-floor-impl/PLAN-PLANNER-SLICE-E-REV3B-EXACT-STAGE0-PATHS-KEY2-GREEN-CONTROL-20260812-170013.md (rev3b — must-revise at 171210, NOT revived; its two ACCEPTED corrections are carried here on their own merits); .relays/s4/s4-floor-impl/SITREP-PLANNER-SLICE-E-CAP-REFUSAL-CARRIER-SEAM-ROUTED-20260812-155122.md (the routed cell, now resolved)
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: s4.orchestrator-planner, operator, s4.orchestrator-reviewer, master.orchestrator-planner, m-2.planner, m-1.planner
SUBJECT: PLAN (successor) — slice E at 29a5b3a3 with the cap refusal outside A12.4.1 by predicate; two stages, eight keys, A3 same-head; plan review requested; m-1 receipt still absent

## 0. Every pin RE-DERIVED at this filing act (the instrument, not a citation)

```text
addendum-12 @ pdc 6eeeb157   sha256 29a5b3a3abb6777af70a1c959728f4f61731489a1735773e81713b5aa3ea3adb
                             == DESIGN_LOCK_ID's declared content.                            MATCH
addendum-12 @ pdc HEAD/disk  sha256 d0e2c6eb…  -- the LOCK POST-STAMP, and it CANNOT hash to the
                             locked value by construction (the stamp is applied on top).
J           @ pdc HEAD       sha256 94b6440c6ea5342a266ac16eb07b9eb4f1f52524f334e180483d2648d2049d18
                             UNMOVED through the entire m-2 rev3→rev8 churn.                  MATCH
lock commit  6f2de0d 18:57:37  "successor lock … over exact 29a5b3a3"  — the ONLY commit after 6eeeb157
VP re-approval 191415         DESIGN_REVIEW_VERDICT: approve, DESIGN_LOCK_ID / TARGET_DESIGN_SHA256 /
                             TARGET_DESIGN_COMMIT all naming this pin, FROM master.orchestrator-reviewer,
                             SUPERSEDED_DESIGN_LOCK_ID 154cd87e.                              VERIFIED
```

**I checked the post-stamp rather than accepting its self-certification** — a document certifying its own
edit is the shape that has bitten this team before. `git diff 6eeeb157 6f2de0d` on that file is **ONE hunk,
`@@ -1,15 +1,52 @@`, 49 insertions / 12 deletions**, entirely the title marker, the `STATUS:` block and the
lock record. **No normative clause, fixture, arm, or seam statement is inside the changed region** — checkable
in a single hunk, which is why the stamp was deliberately confined to one. The VP independently confirmed
both hashes at `191415`.

## 0a. A disclosure the carry-down did not carry: the locked document's own STATUS is STALE

The rev8 `STATUS:` block, written into the file at lock time (`18:57:37`), says:

```text
"VP re-verification against the NEW red/green fixtures in §A12.6 is the gate AFTER this lock and has NOT
 run; the operator re-waiver at this pin has NOT run."
```

**Both clauses were true when written and are false now**, and a reader checking gates against the document
would conclude two upstream gates are open. Measured:

- **The `§A12.6` VP re-verification RAN at `191415`** (`19:14:15`, 17 minutes after the stamp). Its "MONO and
  fixture review" section walks the identity gate's oracle and **all eight literal keys by name** — `1` kills
  direct-child-only collection, `2` is the two-level compatibility control, `3` uses the off-cycle
  lexicographically-smaller descendant to kill least-node-of-component, `4` requires observable warning
  carriage, `4a` requires a present inconsistent edge to refuse so MONO cannot erase legitimate narrowing,
  `5` requires both variants to accept on membership, `6` proves pack carriage alone is insufficient, `7`
  keeps claude's flat path unchanged — and it confirms eight keys present with no mutation arm claimed.
- **The operator re-waiver clause is superseded by the W-1 chain** (`193019` → `200713` → `204925` →
  `210434` → `210540` concur-approve → `211308` chain closed), which re-scoped the waiver so it survives a
  pin change instead of dying with one.

**I am not editing anyone's document and I am not treating the stale lines as gates. I am recording, in the
artifact that consumes it, why they no longer bind** — so the next reader does not stop on them.

## 1. The cap-carrier cell — RESOLVED, and the BASIS is the load-bearing part

```text
§A12.4.1 (narrowed):  "Any material OMITTED FROM, OR ALTERED WITHIN, AN ENTRY OR REPORT THAT IS
                       NEVERTHELESS EMITTED MUST produce a line on CollectReport.warnings."
§A12.4.2 (added):     the cap case. A LOUD WHOLE-ENTRY REFUSAL EMITS NO SUCH RESULT — there is nothing
                       for material to be omitted FROM — so it falls outside §A12.4.1 BY THE OPERATIVE
                       PREDICATE ITSELF, not by an argument laid over it. J's LOCKED TYPED WHOLE-ENTRY
                       REFUSAL, naming THE CAP and THE ENTRY, carries it. NO warnings line is owed.
```

**The outcome is the one I recommended; the reasoning I recommended was rejected, and rightly.** I proposed
that the typed error *discharges* the clause. m-2 ruled that this would license discharging the **other**
`§A12.4.1` items through errors — and those are **partial successes**, real drops inside a report that
survives to carry the line. **The correct statement is that the clause never covered the cap case.**
**Do not encode "the error discharges the requirement" anywhere.** m-2 also named the concrete harm rev2's
mis-listing would have caused, and it is the same one I flagged when routing: an implementer appending a
warning on a path where the report is discarded — **a dead line that reads as compliance in a diff and would
survive review looking like the remedy.**

**The killing arms, updated to the resolved reading:**

```text
a cap refusal that does NOT name BOTH the entry and the cap        -> FAILS
an over-cap entry that is EMITTED AT ALL (truncated or whole)      -> FAILS
a genuine drop/alteration WITHIN AN EMITTED entry with no
  §A12.4.1 CollectReport.warnings line                             -> FAILS
```

The third arm is what stops the ruling from being over-read into "warnings are optional." **`§A12.4.1` still
binds everything it always bound.** All four caps are unchanged: **1024 nodes / 64 depth / 256 artifacts per
declared node / 4096 total, per entry, whole-entry refusal, never truncation**, with at-cap ACCEPT and cap+1
REFUSE arms for each and **zero partial emission** asserted on every cap+1 arm.

## 2. Two stages — the coupling, and what is still blocked

**Measured at this act:** `origin/main` is still `0db8fdd`; `SessionChild` is `{original_id, artifacts}`;
`git grep -c parent_id origin/main -- src/core/manifest` → **0 hits**. **m-1's receipt has NOT landed, so
Stage 1 remains blocked** — the one gate neither the lock nor W-1 touches.

```text
STAGE 0 — cut from origin/main = 0db8fdd. NO PRODUCTION BYTE. src/** untouched entirely.
  PERMITTED PATHS, EXHAUSTIVE:
    tests/test_adapter_codex_collect.cpp    REDs 1a, 3, 4
    tests/test_adapter_codex_install.cpp    RED  6
    tests/test_adapter_claude_collect.cpp   CONTROL 7
    tests/test_pack.cpp                     CONTROL 2 (byte-identical two-level arm)
    tests/test_cli.cpp                      the three claude reference-resolution controls
    tests/fixtures/slice-e/**               fixture trees, incl. DATA ONLY for 1b / 4a / 5
  FORBIDDEN: src/**, harness/**, .github/**, and every path not named. Any other test, helper or
  fixture path ROUTES through the scope-diff/deviation gate BEFORE dispatch.

STAGE 1 — opens on the m-1 receipt. ONE coupled behavior change, nothing split out of it:
  transitive closure · child_parent_map DECLARED+POPULATED+CONSUMED · rootless-component disposition ·
  both identity gates root-mapped AND monotone · warning producers · manifest_entry_for edge emission ·
  all four producer caps.
  IN (production): adapter.hpp · codex/codex.cpp (ANCHORED) · codex/install.cpp · core/pack/pack.cpp
  HARD-OUT: manifest.hpp / manifest.cpp (fence-2) · .github/** · sealed docs · m-3's sessions.cpp:344,
    render.cpp:244-245, report/envelope.cpp:125 · harness/selftest/test_e3_asserts.py
  CONDITIONAL-OUT, each requiring a STOP-and-route: any src/core/open/* file · rewrite_common.cpp ·
    every claude production file (key 7 asserts claude is UNCHANGED)
  harness/bivharness/e3.py enters ONLY inside Stage 1's single anchored head, for the codex pin.
```

**Why the coupling is not negotiable:** `manifest_entry_for` loops `child_ids` and builds flat
`SessionChild{original_id, artifacts}` with no parent position, and under J's absence license absence means
*the parent IS the entry primary* — so transitive `child_ids` on the flat writer emits **C as a DIRECT CHILD
of R. False data, not missing data.** A publication hold does not make a lying producer a valid checkpoint.

**The combined-tree checkpoint:** the branch rebases onto the m-1 receipt SHA, and **that tree is the first
point at which keys `1a`, `1b`, `2`'s absence arm, `4a`, `5` and the E2E are creditable.** `0db8fdd` stays
named as the AUDIT cut — the rebase target and the audit cut are different things and the report says both.

**The m-1 stop gate:** the receipt must name a commit on `origin/main` where `manifest::SessionChild` carries
an optional `parent_id`, the writer emits it, the parser validates it, and the parser enforces J's four caps
with the typed whole-entry refusal.

## 3. Eight keys — placement, RED classification, ordering

**An assertion-level RED requires a test that COMPILES, SELECTS, RUNS and FAILS on an assertion. A compile
failure earns no behavioral-RED credit.**

```text
KEY  FILE / CASE NAME                        EXPECTED FAILING ASSERTION            GREENED BY   WHERE
1a   codex_collect  "FX-A12-1 … carried"     C ∉ R's carried descendants           closure      STAGE 0
3    codex_collect  "FX-A12-3 … cycle"       no primary exists for the component   rootless     STAGE 0
                                             (+ primary IS a CYCLE MEMBER, omitted   pass
                                             edge NAMED, artifacts exactly once)
4    codex_collect  "FX-A12-4 … warns"       no warnings line for an unreadable    warning      STAGE 0
                                             descendant                             producers
6    codex_install  "FX-A12-6 … own parent"  staged_identity_mismatch refuses the  the gates    STAGE 0
                                             grandchild
2    test_pack      "FX-A12-2 … unchanged"   CONTROL, GREEN at 0db8fdd (arm 1) and GREEN again after the
                                             m-1 rebase (arm 2: no parent_id emitted for a two-level entry)
7    claude_collect "FX-A12-7 … unchanged"   CONTROL, GREEN at 0db8fdd and after
1b   test_pack      "FX-A12-1 … parent edge" children[] for C carries no parent_id  emission    POST-REBASE
4a   codex_install  "FX-A12-4a … refuses"    a PRESENT disagreeing edge is not      gates +     POST-REBASE
                                             refused                                emission
5    codex_install  "FX-A12-5 … never grants" ATOMIC: ONE artifact, TWO EXECUTED    gates +     POST-REBASE
                                             variants, BOTH outcomes asserted —     emission
                                             v0 (edge ABSENT, bytes name P) ACCEPT,
                                             vE (edge = P) ACCEPT. BOTH-REFUSED FAILS
```

**Key 2 is GREEN on both arms, and its failure is a DEPENDENCY-INTEGRITY STOP, not our RED.** Both production
`SessionChild` sites (`pack.cpp:400`, `manifest.cpp:201`) use designated initializers, so an added optional
`parent_id` is value-initialized to `nullopt` and the absence assertion passes the moment the member exists.
**If arm 2 is RED at the receipt, m-1's writer is breaking J's absence license — STAGE 1 STOPS and ROUTES.**
Same stop if the member lands **required** rather than optional and our site will not compile.

**Ordering — three RED points, not two:** Stage-0 REDs `1a/3/4/6` + controls at `0db8fdd` → rebase onto the
m-1 receipt → key-2 arm 2 GREEN plus REDs `1b/4a/5` → Stage 1 → all green with the controls still green.
**No implementation byte lands before every key it greens has been observed failing.**

## 4. A3 — four checks, ONE reviewed head (`002730`'s operational text)

All `codex.cpp` changes land in **one** head carrying its **one** `_ADAPTER_SOURCE_ANCHORS` codex-pin update
**in the same commit** — the only shape that satisfies check 1. No separate anchor-only commit.

```text
1. H's diff = F's change + the ONE anchor-literal update, nothing else anchor-side
2. the review RE-DERIVES F's whole-file hash at H and matches the new literal
3. each 153958 §4 read-side session literal MUTATION-CHECKED: mutate → RED under the harness → revert →
   record mutation diff + failing assertion
4. the review states H's diff touches none of them — CLASS-SCOPED, naming the classes, never a bare negative
```

**Check-3 classes for `codex.cpp`, located at `0db8fdd` and TO BE RE-LOCATED at the head** (our own edits move
these lines — re-derive, do not carry): `:1136` `sessions_root` locator · `:1145-1149` `archived_sessions` ·
`:1191-1198` `state_5.sqlite` selection and the store-root fallback · `:1123` `config.toml` `sqlite_home` ·
`:625` rollout path construction. **`codex/install.cpp` moves NO pin** — `153958` excludes `install.cpp`
normatively as write/restore-side. **`claude_code.cpp`'s pin must NOT move.** Burden reported per the grant's
own R-3.40(11) trigger rather than absorbed.

## 5. Evidence

Three-level actual-binary E2E: all three rollouts installed, mapped-root and immediate-parent **distinct
identities both resolving**, and the leaf's marker bytes **READ BACK**. Three sanitized claude
reference-resolution controls (flat bare-hex, flat slug-hex, nested `subagents/<wf>/`) with unprefixed
reference ids and prefixed child filenames. **Coverage stated as AXES, never a distribution** — basis
`309` bare-hex + `269` slug-hex of `578`, the withdrawn "578/578 slug-hex" reaching no fixture, the `1702`
figure cited nowhere. `ScopedPackDiscoveryEnv` + `require_store_roots_under` with a **credential-shaped decoy
asserted never opened, packed or copied**; **NEVER the live `~/.claude`/`~/.codex`**. Full macOS presets +
`git diff --check`; **local Ubuntu 24.04 `linux/amd64` Docker parity as the GOVERNING Linux signal**, Actions
NOT invoked, with the three disclosed divergences (clang-tidy mirror fetch, `/mnt/c` provisioning, quota
hold). **Base-container control on ANY change in the Linux failure-set count.** The `.github` Catch2 count
gates (221/223 vs the 385-case landed B2 head) named as an **inherited already-stale pin**, hard-out, routed
not folded.

**Branch:** cut from `origin/main` (= `0db8fdd`), **never local `main`** (169 behind). Publication HELD.
**D-5.5(a) measured AT HAND-UP** as `git rev-list --count origin/main..<branch-cut-point>`.

**Constraints carried:** R-4.20 — the edge produces refusals only; mint sites `codex/install.cpp:122-143`,
`:430`, `:455`, writes `:483-489`; **`:507-513` is NOT minting proof.** MONO `A(E) ⊆ A(0)`. Producer closure.
Typed refusal, never silent truncation. M4-CG-0. **R-4.24 is m-3/m-1's and we do not gate on it.**

## 6. Token-time obligations, recorded now

At token time I re-verify the **seven-element tuple** and say so in the token relay: lock declaration + VP
approval each naming `DESIGN_LOCK_ID` + full SHA-256 + full commit; the pre-lock content dispositions naming
`DESIGN_DOC_ID` + full target SHA-256 (+ commit); all preceding this successor and the token; **no later
supersession and no later unlocked normative edit** — with the live `d0e2c6eb` shown to be the disclosed
one-hunk status-only post-stamp (proved in §0, to be re-proved then). **A miss makes W-1 INAPPLICABLE / NO
TOKEN.** And I re-derive both design hashes at that moment rather than citing §0 — **§0 is a measurement with
a timestamp, not a property of this plan.**

## 7. What I am asking of you

**A plan review** — this is slice E's plan gate at the successor pin. Is the cap-carrier basis encoded
correctly (outside `§A12.4.1` by predicate, `§A12.4.2` + J carrying it, with the rejected reasoning absent
and `§A12.4.1` still binding everything it always bound), is the stage split and RED classification honest,
and is anything here a design decision I had no authority to make? Reply with `PLAN_REVIEW_VERDICT: approve`
or `must-revise` (verdict line BARE — no bold, no backticks; remarks via em-dash only, per the matcher's
recorded grammar). **On approve the token still waits on m-1's receipt for Stage 1**; Stage 0 is dispatchable
on approve alone. Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — at this filing act: re-hashed addendum-12 at `6eeeb157` (`29a5b3a3`) and at pdc HEAD (`d0e2c6eb`), re-hashed J (`94b6440c`, unmoved), enumerated the single lock commit `6f2de0d` after `6eeeb157`, proved the post-stamp is ONE hunk (49/12, head region only), read the `191415` VP re-approval's header pins and its `§A12.6` eight-key fixture review, walked the W-1 chain `193019`→`211308`, and re-measured the m-1 dependency at `origin/main` (`0db8fdd`; `SessionChild` unchanged; 0 `parent_id` hits); this relay + its INDEX row ride one explicit-path docs-lane commit whose SHA lands after filing
RELAY_LINT: per D-3.4 — per-file WITH freshness before filing; INDEX tail re-read; `--index`; third arm at the active dispatch root. Disclosed reds: INDEX line 222 (pre-existing sibling class, not mine) and the cross-repo lineage class, cleared for this lineage by W-1 (concurred/effective, property-scoped) and still disclosed — no green claimed and no authority drawn from disclosure
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to this relay and `.relays/s4/INDEX.md`

CARRY LIST:
- `.relays/s4/s4-floor-impl/PLAN-PLANNER-SLICE-E-SUCCESSOR-29A5B3A3-CAP-OUTSIDE-A1241-BY-PREDICATE-20260812-212557.md` → `s4-floor.implementer` (plan review = slice E's plan gate); rev3b `170013` stays must-revise and is NOT revived — its two ACCEPTED corrections are carried here on their own merits
- **all pins RE-DERIVED AT THIS ACT:** `29a5b3a3` @ `6eeeb157` MATCHES the lock; J `94b6440c` UNMOVED; VP re-approval `191415` names lock + SHA + commit; the live `d0e2c6eb` is the lock POST-STAMP, proved ONE hunk / 49+12 / head region only — I checked it rather than accepting the document's self-certification
- **STALE-STATUS DISCLOSURE:** the locked doc still says the VP `§A12.6` re-verification and the operator re-waiver "have NOT run" — the former RAN at `191415` (its fixture review walks all eight keys by name), the latter is superseded by the W-1 chain. Recorded in the consuming artifact; nobody's document edited
- **cap carrier RESOLVED with the CORRECT BASIS:** outside `§A12.4.1` by its operative predicate (a whole-entry refusal emits no entry for material to be omitted from); `§A12.4.2` + J's typed loud fatal naming CAP and ENTRY carry it; **my recommended "typed error discharges the clause" reasoning is REJECTED and absent here**; three killing arms incl. one that stops the ruling being over-read into "warnings are optional"
- two stages with an exhaustive six-path Stage 0 (no production byte) and ONE coupled Stage 1; **m-1's receipt measured ABSENT at this act (`origin/main` = `0db8fdd`, 0 `parent_id` hits), so Stage 1 stays blocked**; eight keys with key 2 GREEN on both arms and a dependency-integrity stop; key 5 atomic; three RED points
- A3's four checks on ONE `codex.cpp` head with the five literal classes to be RE-LOCATED at the head; `codex/install.cpp` moves no pin; the claude pin frozen
- token-time: seven-element tuple re-verified and **both design hashes re-derived at that moment** — §0 is a measurement with a timestamp, not a property of this plan; release hold ABSOLUTE
