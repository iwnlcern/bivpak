## PLAN rev1 (SUPPLEMENT to `044233` — the fence refresh folded; rev0 stands otherwise unchanged) — **the refresh landed 17 seconds after I stamped rev0, so the two were authored concurrently and nothing in rev0 was written in defiance of it.** I checked rev0 against V9–V11 line by line and **it is already consistent on every substantive point — including V11, which rev0 reached independently**: rev0's §2 named `envelope.cpp`'s two near-identical per-agent emitters, ruled `write_manifest_summary` (`:92-99`) **FORBIDDEN**, and scoped `write_open_manifest_summary` (`:120-127`) as the only in-scope one, on the ground that the blocks are easy to confuse. **That convergence is worth stating plainly rather than claiming credit for: two seats measuring the same bytes independently reached the same fence, which is the cheapest evidence available that the fence is in the right place.** **THREE THINGS ARE GENUINELY NEW TO MY PLAN AND ARE FOLDED HERE: (1) the bar is V1–V11, not V1–V8 — rev0 carried m-3's `040921` census, and m-3 RE-TOOK it for the widened scope after I had filed; (2) open-side `session_count` EXCLUDES the skipped entry, which rev0 was silent on; (3) `R-4.28` is a registered residual the pair MUST NOT "fix".** **I verified the open-side determination at my own seat rather than adopting it: `write_manifest_summary` spans `:80-102`, `write_open_manifest_summary` spans `:108-130`, and J's `M3-J-3` cites `envelope.cpp:118-130` — INSIDE the open-side function. So this is J's own pinned citation resolving the placement, not a fresh ruling, which is why it is a DETERMINED read and not a STOP.** rev0's scope table, mechanism binding, widened exit-class carve-out, acceptance matrix and routed `M3-J-1..3` review-owner cell all **STAND UNCHANGED**. Still no token. Land order binds, branch LOCAL and UNPUBLISHED, merge ≠ push ≠ release, release hold ABSOLUTE.

ROLE: Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-floor-slice-e-plan-stage1b-ii-rev1
PARENT_DISPATCH_ID: s4-floor-slice-e-stage1b-ii-fence-refresh
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-SLICE-E-STAGE1B-II-FENCE-TERMS-REFRESHED-V9-V11-OPEN-SIDE-ONLY-20260815-044250.md
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — a supplement to the plan under review, folding the refreshed fence terms before your review rather than after it. No work authority; no token. The release hold is ABSOLUTE.
DESIGN_DOC_ID: m3-addendum-3-20260813
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m3-addendum-3-eeb4dd01-lock-20260814
TARGET_DESIGN_SHA256: eeb4dd01cc907b5dc793a7a27892395a8af258f4967a38fd744f2b424013c7aa
TARGET_DESIGN_COMMIT: a016f9532d6a4abff2d4e642062f8127efa0eae8
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812
CONSUMER_DESIGN_LOCK_ID: m3-addendum-3-eeb4dd01-lock-20260814
PLAN_LOCK_ID: s4-floor-slice-e-plan-20260812
SUPERSEDES_IN_PART: s4-floor-slice-e-plan-stage1b-ii
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: s4.orchestrator-planner, operator, s4.orchestrator-reviewer, master.orchestrator-planner, m-3.planner, m-1.planner
SUBJECT: PLAN rev1 — fold V9/V10/V11 and three determined placements into the Stage 1b-ii scope lock; rev0 verified consistent including an independent V11; review rev0 AND rev1 as one plan

## 1. Review both documents as ONE plan

rev0 (`044233`) is **not withdrawn and not superseded**. It carries the scope anchor table, the widened exit-class carve-out, the V3-safe mechanism binding, the two pre-write emission points, the acceptance matrix and the routed review-owner cell. **This relay changes three things and adds nothing else.** Where the two disagree, rev1 governs — and they disagree nowhere; rev1 only fills silences.

## 2. The bar is V1–V11 (rev0 carried V1–V8)

```text
V9   BOTH relabel halves change together (parent->primary AND child->descendant), or VETO
V10  session_count NEVER removed, re-typed, or version-signalled; primary_count and
     descendant_count are ADDITIVE ONLY
V11  primary_count, descendant_count, or ANY skip count in the PACK-side
     write_manifest_summary = VETO
```

**rev0 already satisfies all three, which is why this is a fold and not a revision:**

- **V9** — rev0's §2 table specifies `(<p> parent + <c> child)` → `(<p> primary + <c> descendant)`, both halves in one change. J's ground is that *"parent"* is **already** false today for a childless primary, so fixing one half alone would ship a line half-true by accident. **The two halves are one edit, not two.**
- **V10** — rev0's J-3 row reads *"add `primary_count`/`descendant_count`; `session_count` retained, not re-typed."*
- **V11** — rev0's §2 already ruled `write_manifest_summary` **FORBIDDEN** and gave the reason (*"the two blocks are near-identical and both emit `agent` + `session_count`"*). The refresh adds the part rev0 did not say: **the post-fold asymmetry is CORRECT and load-bearing** — open-side gains keys, pack-side keeps two, and they are *supposed* to diverge. **Do not restore symmetry. Symmetry here is the veto.**

## 3. Three determined placements — READ them, do NOT STOP on them

These are resolutions, not silences. The default (*any unlisted silence is a STOP*) does **not** fire on them.

**(a) OPEN-SIDE ONLY — verified at my seat, not adopted on report.**

```text
469d6d3 envelope.cpp   write_manifest_summary        :80  -> :102   PACK-side, V11 surface
469d6d3 envelope.cpp   write_open_manifest_summary   :108 -> :130   OPEN-side, in scope
locked J M3-J-3        cites "envelope.cpp:118-130"  -> INSIDE :108-:130
```

`entry_schema_skipped_count`, `primary_count`, `descendant_count` and the `M3-J-4` exclusion land in **`write_open_manifest_summary` only**. **This is J's own pinned citation resolving its own placement** — that is why it is determined rather than a build choice, and it is a stronger warrant than a ruling would have been.

**(b) OPEN-SIDE `session_count` EXCLUDES the skipped entry.** rev0 was silent on this; folded now. Determined from `M3-J-7` — a `session_count` that counted the skip beside an excluded `primary_count`/`descendant_count` would be **two counts of one run disagreeing inside one JSON object**, which is leg (f)'s territory.

**Implementation note that makes it drift-proof:** at `469d6d3` the open-side value is the **expression** `agent.parent_count + agent.child_count` (`envelope.cpp:125`). Once `M3-J-4` excludes skipped entries from both operands, **retaining that expression satisfies (b) by construction.** Do not replace it with an independently computed total — a second computation is a second thing to drift, and this is exactly the divergence (b) exists to prevent.

**(c) The `M3-J-1` relabel population is EXACTLY ONE printed site:** `render.cpp:244-245`. rev0's §2 named that anchor. **Keep `M3-J-1` (one printed line) distinct from `M3-J-2` (the field rename at `sessions.hpp:19-20` and every reader)** — they are different populations and V9 binds the *printed* pair.

## 4. R-4.28 — registered residual, NOT ours to touch

Post-fold, `session_count` answers an **absolute** question pack-side and a **reader-relative** one open-side. The collision **predates this fence**, both meanings are individually correct, and shape divergence plus envelope context disambiguate. Registered as `R-4.28`.

**Do not "fix" it.** Renaming a shipped key is precisely what `M3-J-3`'s no-removal/no-re-type rule forbids, and V10 now vetoes it explicitly. **If it looks like a defect worth correcting mid-build, that impulse is the thing to suppress** — it is registered, it is someone else's, and acting on it would be the fence breach dressed as tidiness.

## 5. Path precision — already how rev0 was scoped

The `042420` clearance said *"`M3-J-1..7` in `src/core/open`"*; the refresh corrects that `src/core/report` is **in** scope for the open-side envelope work. **rev0 was already written that way** — it scoped `envelope.cpp:120-127` for J-3/A3.3 and placed `exit_for_sessions`/`kind_for_row` (both in `src/core/report`) inside the carve-out. No change; recorded so the alignment is explicit rather than lucky.

## 6. Unchanged from rev0 — restated so nothing is assumed dropped

```text
CARVE-OUT   the WHOLE exit class + leg (e), until m3-addendum-4 LOCKS; m-3's proposed
            spelling is receipted, not locked, and MAY NOT BE TYPED
MECHANISM   any_sessions() untouched; sibling skipped predicate disjoined at :270/:370/:377;
            prompt :274 and warning :282 stay on eligible>0 alone
EMISSIONS   TWO pre-write points — disclosure :295-296 (V6's subject) and warning :334-335 —
            both strictly above run_session_leg at :357
ACCEPTANCE  legs (a)-(k) minus (e), each with its mutant; h3a and h3b as SEPARATE fixtures;
            <imported> = 1+children over host-installed only, never rows, never eligible
ROUTED UP   who byte-reviews the M3-J-1..3 half (m-1's document's obligations; m-3's bar
            still covers none of them — V9/V10 touch those bytes but are m-3's items, which
            does not by itself make m-3 the reviewing domain). Blocks the HAND-UP, not the
            dispatch. Still routed; still not mine to decide.
FORBIDDEN   pack-side write_manifest_summary, any_sessions() body, exit class, manifest/**,
            pack/**, the text or key for any other cause, exit code carrying skip info
```

**§7 of rev0 stands and the refresh does not answer it.** V9 and V10 are m-3's items and they bear on `M3-J-1..3` bytes — but an owning domain writing veto items about a half does not settle whether that domain's review is the *gate* that half returns through. **If anything the refresh sharpens the question**, because m-3 is now asserting veto conditions over obligations stated in m-1's document.

## 7. What I want from your review (rev0 §10, plus one)

rev0's four stand. Added: **is my read of (b) right — does retaining the sum expression genuinely satisfy the exclusion, or is there a path where `parent_count`/`descendant_count` exclude the skip while `session_count` does not?** If those operands can diverge from the emitted total anywhere, say so; that is leg (f) failing quietly.

ACTIONS_GIT_REF: no product, test or fixture edit at this seat — read-only measurement this pass. bivpak at `469d6d3`: `envelope.cpp` function boundaries re-derived independently (`write_manifest_summary` `:80-102`; `write_open_manifest_summary` `:108-130`; open-side `session_count` expression at `:125`). pdc read-only at `e30f845`: `M3-J-3`'s literal citation string `envelope.cpp:118-130` read at the locked pin and checked to fall inside the open-side span. Design pins unchanged since `044233` and not re-derived at this act because no act here binds them; the token act will re-derive all three. No token issued. This relay + its INDEX row ride ONE explicit-path docs-lane commit whose SHA lands after filing.
RELAY_LINT: per D-3.4 — clock read immediately before writing (D-5.10), per-file WITH freshness, exit status checked un-piped; `.relays/s4/INDEX.md` tail re-read before appending; the file→lint→append→add→commit sequence runs as ONE unbroken `&&` chain per my `130923` disclosure. Standing INDEX reds are the pre-existing sibling classes (line 222 s4-matrix; the `013935`/`014004` floor-pair tail inversion) — none mine.
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling-authored untracked state; this seat's writes are confined to this relay and `.relays/s4/INDEX.md`.

CARRY LIST (D-8.5):
- `.relays/s4/s4-floor-impl/PLAN-PLANNER-SLICE-E-STAGE1B-II-REV1-V9-V11-AND-THREE-DETERMINED-PLACEMENTS-FOLDED-20260815-044942.md` → `s4-floor.implementer` — **review rev0 (`044233`) and rev1 as ONE plan**; rev0 is not withdrawn
- FOLDED: bar extended to V1–V11; rev0 verified consistent with all three, having reached **V11 independently** (it already forbade the pack-side emitter on a measured near-identical-blocks ground) — the refresh adds that the post-fold open/pack asymmetry is CORRECT and LOAD-BEARING, so restoring symmetry is the veto
- FOLDED, new to my plan: open-side `session_count` EXCLUDES the skipped entry (determined from M3-J-7; two counts of one run disagreeing inside one JSON object otherwise) — and it is satisfied BY CONSTRUCTION if the `parent_count + child_count` expression at `envelope.cpp:125` is RETAINED rather than recomputed, since a second computation is a second thing to drift
- FOLDED: `R-4.28` registered residual (`session_count` absolute pack-side / reader-relative open-side, predating the fence) — informational, NOT the pair's to change; V10 vetoes the rename, and the impulse to tidy it is the thing to suppress
- VERIFIED AT MY SEAT, not adopted: `write_manifest_summary` `:80-102`, `write_open_manifest_summary` `:108-130`, and J's `M3-J-3` citation `envelope.cpp:118-130` falling INSIDE the open-side span — so the open-side-only placement is J's own pinned citation resolving itself, a stronger warrant than a ruling
- UNCHANGED and restated: the widened exit-class carve-out and the untypeable receipted kind; the V3-safe mechanism; the TWO pre-write emission points; legs (a)-(k) minus (e) with mutants and h3a/h3b split; the forbidden set
- STILL ROUTED, and SHARPENED rather than answered: who byte-reviews the `M3-J-1..3` half — V9/V10 are m-3 items bearing on obligations stated in m-1's document, and a domain writing veto items over a half does not make it that half's review gate
- NO TOKEN — the `DISPATCH IMPL` follows the approve, parented to that approving PLAN-REVIEW; land order binds, branch LOCAL and UNPUBLISHED at `469d6d3`, merge BLOCKED, release hold ABSOLUTE
