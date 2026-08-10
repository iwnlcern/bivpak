## SITREP — R-4.8 carrier rigorous review panel COMPLETE at `29796bb`: four lenses in, verdict MUST-FIX (REVIEW-FOLD required); product bytes clean on three independent reads; five test-delta must-fixes fold on pair authority; ONE cross-lens conflict (degenerate-root validator) ROUTED UP with both options framed — fold dispatch held so the ruled outcome and the test set ride ONE commit

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-matrix-arm1-r48-panel-verdict
PARENT_DISPATCH_ID: s4-matrix-arm1-r48-impl-r1-complete
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-CARRIER-COMPLETE-20260809-192358.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: yes — MF-1's disposition may amend the grammar of the floor-ratified consumer contract (`…050728`), which is above the pair; the pair self-rules nothing on it; the five test-delta must-fixes are pair-scope and wait only so the fold is one commit; publication remains a separate token; the release hold is ABSOLUTE
DESIGN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-09-s4-matrix-arm1-r48-packer-home-carrier-design.md
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/plans/2026-08-09-s4-matrix-arm1-r48-carrier-plan.md
FROM: s4-matrix.planner
TO: s4.orchestrator-planner
CC: operator, s4.orchestrator-reviewer, s4-matrix.implementer, master.orchestrator-planner
SUBJECT: SITREP — panel verdict must-fix (test delta only, plus one routed contract-grammar cell); record sealed in reviews/; fold plan stated; three candidate RESIDUALS rows for master

## Panel result

Full record (four verbatim lens reports + lead verification + synthesis):
`docs/sprints/2026-08-04-s4-step4/reviews/2026-08-09-s4-matrix-r48-carrier-panel-29796bb.md`
(SHA-256 `006144b2d1cb827b4f0b28c4c97c92978674c811e4391781dd5ccbbecb216443`, sealed after
creation). Team-of-4 (correctness, security, test-coverage, perf+idiom merged), all cold
read-only, pinned to the sealed blobs at `29796bbe`. 4 spawns = 4 finding-sets + 0 stalls.

Per-lens: correctness must-fix (tests only — "the five product files are clean … NO
divergence between the committed product bytes and the locked design"); security must-fix
(one Medium, all four assigned probes otherwise CLEAN, both fences verified LIVE);
test-coverage must-fix (2 Major; §9 matrix 19/23 fully mapped, non-vacuousness PASS,
receipt-honesty PASS, env-hygiene PASS); perf+idiom approve (one cold-path nit).

**PANEL VERDICT: must-fix — REVIEW-FOLD required.** Product bytes untouched by every
in-pair fix: the entire pair-scope must-fix set (MF-2..MF-6, deduplicated across lenses in
the record) lives in the five test files — pinning the sealed wire POSITION with a
carrier-engaged golden; covering the unreached `packer_home_flavor` wrong-type fail-closed
branch; replacing both unfalsifiable adapter "receipt" tests with a dual-arm byte-identity
inertness receipt (§9-23's missing nullopt arm — graded HIGH by correctness, the known
unfalsifiable-box shape); hermeticizing the pack capture test (it currently pins the
operator's REAL `/Users/jack` home with no store-var guards, so it walks the live
`~/.claude`/`~/.codex` on the operator's machine); and proving §9-21 on both adapter legs
with a per-call seam. The correctness lens is explicit that these touch no sealed wire
shape and owe no floor re-route. Disclosure carried in the record: most of the Minor-tier
test debt traces to MY plan's literal code blocks, reproduced faithfully by the
Implementer — plan-authored, not implementer drift.

## MF-1 — the routed cell (security Medium ⟷ correctness "conformant"; adjudicated at the bytes)

`packer_home_valid` admits degenerate root-only spellings — `/` (posix), `/mnt/c/` (wsl),
`C:/`, `//?/`, `\\?\` (windows) all clear parse into the carrier (lead re-verified at the
blob). Both lenses agree on the facts; the conflict is disposition, and it is not mine:
the implementation CONFORMS to design §3's grammar (deliberately mirroring
`rewrite_common`), so the defect — if graded one — is in the ratified contract's grammar
itself. Security's material point: omitting the pair makes the future needle SKIP
(ratified, fail-open, silent); shipping `"/"` makes it FIRE ON EVERYTHING — an untrusted
image corrupting a control is a different risk class from disabling it, and only the
disabling class is on record.

**Option A (security's recommendation, and mine as lead):** tighten the validator NOW —
require a non-empty remainder after the flavor's root prefix (posix `size()>1`, wsl
`size()>7`, windows drive `size()>3`, extended non-empty remainder after the 4-byte
prefix). Pack-side, a degenerate HOME degrades to ABSENT (the already-ratified skip path
— strictly safer); parse-side, a degenerate carrier is malformed ⇒ fail-closed, which is
design §5/§6's existing rule for invalid values, not a new semantic. Cost to honest
packers is nil (`HOME=/`, `HOME=/mnt/c/`, `HOME=C:\` are not plausible homes). Timing is
the argument: the branch is LOCAL and unpublished, no image with the carrier exists, and
per the fences-over-sealed-behavior rule, tightening AFTER the needle lands is itself a
sealed-behavior change — now is the cheap moment. Needs: design rev3 amendment (§3
grammar + §8 table rows; §6 wording nit rides along) with its own approve on the doc
hash, your ruling on whether the floor contract's "non-empty absolute in its verified
flavor" wording needs floor re-ratification or is a compatible narrowing, then the fold.

**Option B:** ship the validator as-is; register a residual binding the needle ("a cleared
carrier must not be treated as a bounded prefix; degenerate roots handled needle-side").
Framed honestly: this moves a validation invariant into a consumer convention — the exact
defended-by-convention shape security flagged elsewhere in the same report.

## Plan on your ruling (per the B2 complete-amend precedent)

I hold the fold dispatch until MF-1 is ruled, then issue ONE bare `DISPATCH IMPL` token
(fresh ID, structured SCOPE_DIFF) covering MF-2..MF-6 + the optional tier at Implementer
discretion + the ruled MF-1 arm (option A adds `src/core/manifest/manifest.cpp` + the
design rev3 lineage; option B keeps the fold test-only) — one commit, then ONE targeted
re-check (lead + owning lenses), then the Step-3.8 completion/publication-token path. The
two human lenses stay unrouted until the panel verdict is clean at the exact head
(panel-before-lenses). If you prefer the test-only fold proceeds immediately in parallel
with the MF-1 ruling, say so and I split the dispatch — the sequencing is yours.

## Candidate RESIDUALS rows (master CC'd — master's to write, none registered by me)

1. No pack-report surface discloses whether the carrier was emitted ("needle found
   nothing" vs "needle never ran" indistinguishable) — belongs to the needle work.
2. `packer_home_flavor` is fully redundant with the path, and a legitimate non-WSL Linux
   HOME under `/mnt/<alpha>/` is recorded `wsl` — the needle's flavor-driven spelling
   derivation must tolerate the mislabel.
3. `pack.cpp::path_flavor` is a fourth, weaker copy of the flavor grammar (no windows
   branch): `source_path_flavor` can never be `windows` while `packer_home_flavor` can.
   Pre-existing; consolidating changes sealed `source_path_flavor` behavior and needs its
   own authority.

## Process disclosure

The lead seat crossed a context-window boundary after all four lens reports were delivered
but before the record was written; the four reports were recovered VERBATIM from the
session's on-disk transcript (not reconstructed), every must-fix's central claim was
RE-VERIFIED at the sealed blobs post-recovery, and the record carries the same disclosure
inline. No lens was re-spawned; no finding was re-graded.

Carried unchanged: branch `29796bb` LOCAL and untouched by me; both E2 reds closed per
your disposition `…183936` (red 1 answered-by-existing-ruling, red 2 measured by the BASE
negative control); publication held (P5); Waves B/C/D F-fenced; zero-ref `capture_mode`
awaiting m-1; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: docs lane only — this relay + its INDEX row + the sealed panel record ride one explicit-path commit (SHA lands after filing); product and test paths were touched by no action at this seat; the carrier branch is untouched by me.
FINAL_GIT_STATUS_SHORT:
none — clean tree (matrix-seat paths; the shared checkout carries the Implementer's untracked review/blocker/completion relays and one s4-floor relay, preserved untouched — their INDEX rows are already committed)
Fresh at 20260809-202753 before this relay + INDEX write; this relay, the INDEX row, and the panel record are this seat's working-tree delta at commit time.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/SITREP-PLANNER-R48-PANEL-MUST-FIX-MF1-ROUTED-20260809-202753.md` → TO `s4.orchestrator-planner`
- panel record `006144b2…` at `29796bbe` → verdict must-fix; MF-2..MF-6 pair-scope test-only; fold held for one complete commit
- MF-1 (degenerate-root validator) → ROUTED UP, option A (tighten now, design rev3 + your call on floor wording) recommended over option B (needle-side residual)
- three candidate RESIDUALS rows → master.orchestrator-planner
- human lenses → unrouted until the panel is clean at the exact head
