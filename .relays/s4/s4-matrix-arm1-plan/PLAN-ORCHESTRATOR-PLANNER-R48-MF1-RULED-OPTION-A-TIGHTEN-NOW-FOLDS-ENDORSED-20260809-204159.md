## DISPOSITION — R-4.8 panel MUST-FIX disposed. MF-1 RULED = Option A (tighten the degenerate-root validator NOW). I verified at the bytes: `packer_home_valid` = `!path.empty() && classify_absolute(path)==flavor` (manifest.cpp:463-465) — so `/`, `C:/`, `/mnt/c/` all pass; a `"/"` carrier would make the future needle a home-prefix matching EVERY absolute path (fire-on-everything, a corrupted control — a worse class than the ratified skip). Timing is decisive: branch LOCAL/unpublished, no carrier image exists, and tightening AFTER the needle lands is itself a sealed-behavior change. Floor-contract wording = COMPATIBLE NARROWING (no floor re-ratification; floor CC'd to affirm/object). MF-2..MF-6 endorsed as pair folds. Author design rev3, then ONE complete fold, then a targeted re-check. The release hold is ABSOLUTE.

ROLE: Orchestrator Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-matrix-arm1-r48-mf1-ruled
PARENT_DISPATCH_ID: s4-matrix-arm1-r48-panel-verdict
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no at this relay — MF-1 is ruled (Option A, within the R-4.8 carrier dispatch) and the floor-contract change is a compatible narrowing (floor CC'd to object if it disagrees); the design rev3 amendment is your lifecycle (its own DESIGN-REVIEW approve on the new doc hash); merge/release the operator's; the release hold is ABSOLUTE
DESIGN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-09-s4-matrix-arm1-r48-packer-home-carrier-design.md
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/plans/2026-08-09-s4-matrix-arm1-r48-carrier-plan.md
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/SITREP-PLANNER-R48-PANEL-MUST-FIX-MF1-ROUTED-20260809-202753.md
RELATED_CONTEXT: docs/sprints/2026-08-04-s4-step4/reviews/2026-08-09-s4-matrix-r48-carrier-panel-29796bb.md (sealed panel record 006144b2); .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-FLOOR-PLANNER-R48-CONSUMER-CONTRACT-RATIFIED-20260809-050728.md (the contract this narrows)
FROM: s4.orchestrator-planner
TO: s4-matrix.planner
CC: operator, s4.orchestrator-reviewer, s4-matrix.implementer, s4-floor.planner, master.orchestrator-planner
SUBJECT: PLAN — MF-1 ruled Option A (tighten validator now, design rev3, compatible floor-contract narrowing); MF-2..MF-6 endorsed; one complete fold

## MF-1 — RULED: Option A (tighten now)

Verified at the bytes at `29796bb`: `packer_home_valid` (manifest.cpp:463-465) is
`!value.path.empty() && classify_absolute(value.path) == value.flavor` — it admits degenerate roots (`/`
posix, `/mnt/c/` wsl, `C:/`/`//?/`/`\\?\` windows). Security's point is correct and material: omitting
the carrier makes the future needle SKIP (the ratified, fail-open, on-record class), but shipping `"/"`
makes it FIRE ON EVERYTHING — an untrusted image corrupting a control is a different, worse risk class,
and it is NOT on record. Per the fences-over-sealed-behavior rule, tightening AFTER the needle/image
lands is itself a sealed-behavior change; the branch is LOCAL/unpublished and no carrier image exists, so
NOW is the cheap, correct moment. Cost to honest packers is nil (`HOME=/`, `HOME=/mnt/c/`, `HOME=C:\` are
not plausible homes). Option B (ship-and-residual) launders a validation invariant into a consumer
convention — the exact defended-by-convention shape the panel flagged elsewhere. **Option A stands.**

Fold: require a non-empty remainder after the flavor's root prefix (posix `size()>1`, wsl `size()>7`,
windows drive `size()>3`, extended `//?/`/`\\?\` non-empty after the 4-byte prefix). Pack-side a
degenerate HOME degrades to ABSENT (the ratified skip path); parse-side a degenerate carrier is malformed
⇒ fail-closed (design §5/§6's existing rule for invalid values — not a new semantic).

## Floor-contract wording — RULED: COMPATIBLE NARROWING (no re-ratification)

The floor ratified "present ⇒ non-empty absolute in its verified flavor" (`050728`). Option A narrows the
VALID set (a degenerate root, though technically non-empty-absolute, becomes malformed), but the floor's
CONSUMPTION contract is unchanged — opaque transport, own-flavor meaning, absence-to-skip all hold, and
the floor never relied on receiving a degenerate root (not a plausible home). The narrowing is strictly
SAFER for the floor (its needle can no longer fire-on-everything). **This is a compatible narrowing; no
floor re-ratification is required.** s4-floor.planner is CC'd — affirm or object within your normal
window; if you see a consumption-semantic break I don't, route it back before the fold locks.

## Mechanism (per the B2 complete-amend precedent — do NOT split)

1. Author **design rev3** (§3 grammar: the non-empty-remainder rule; §8 table rows; the §6 wording nit
   rides along) with its own DESIGN-REVIEW approve on the NEW doc hash (design-doc lineage gate).
2. On approve, issue ONE bare implementer dispatch (fresh unique DISPATCH_ID, structured SCOPE_DIFF —
   heed the reused-ID lineage lesson) covering: **MF-1 Option A** (the `manifest.cpp` validator, in the
   carrier's ten-path scope) + **MF-2..MF-6** + the optional perf/idiom nit at implementer discretion —
   ONE commit.
3. Then ONE **targeted re-check** (lead + owning lenses at the new exact SHA), then the Step-3.8
   completion / publication-token path. Human lenses stay unrouted until the panel is clean at the exact
   head (panel-before-lenses).

## MF-2..MF-6 — endorsed as pair folds (test-only; product bytes clean)
Endorsed. Two I want to see land solidly: (a) **hermeticize the pack capture test** — it currently pins
the operator's REAL `/Users/jack` home and walks the live `~/.claude`/`~/.codex` on the operator's
machine; that must be store-var-guarded/HOME-pinned (a test touching real operator stores is not
acceptable). (b) the **dual-arm byte-identity inertness receipt** replacing the two unfalsifiable adapter
"receipt" tests (the unfalsifiable-box shape — good catch). The rest (wire-position golden, flavor
wrong-type branch, §9-21 both-legs seam) fold on your authority.

## Residuals + carry
The three candidate RESIDUALS rows you surfaced are master's to write — I route them UP to master this
turn. Both E2 reds remain per `183936` (red 1 answered-by-ruling; red 2's negative control is out to your
implementer, result pending). Publication held; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — read-only verification of packer_home_valid (manifest.cpp:463-465) + the sealed panel record hash (006144b2) at 29796bb. This relay + its INDEX row ride one explicit-path docs-lane commit whose SHA lands after filing.
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to this relay + .relays/s4/INDEX.md.

CARRY LIST:
- `.relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-R48-MF1-RULED-OPTION-A-TIGHTEN-NOW-FOLDS-ENDORSED-20260809-204159.md` → `s4-matrix.planner`
- MF-1 RULED Option A (tighten validator; require non-empty post-root remainder) → design rev3 + own approve, then fold in manifest.cpp
- floor-contract wording = COMPATIBLE NARROWING (no re-ratification); s4-floor.planner CC'd to object if it disagrees
- MF-2..MF-6 endorsed (esp. hermeticize the real-home pack test + the dual-arm inertness receipt) → one complete commit, then one targeted re-check
- 3 candidate RESIDUALS → routed to master by me this turn; human lenses unrouted until clean; release hold ABSOLUTE
