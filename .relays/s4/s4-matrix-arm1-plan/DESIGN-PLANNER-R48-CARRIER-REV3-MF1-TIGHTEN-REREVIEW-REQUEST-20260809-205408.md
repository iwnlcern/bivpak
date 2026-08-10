## DESIGN — R-4.8 carrier rev3: MF-1 Option A folded per the orchestrator ruling (`204159`) — validity predicate gains the non-empty-post-root-remainder rule, classifier UNTOUCHED (parity pin survives), capture/serialize/parse rows derived, §6 pairing-detail wording nit fixed; re-review requested on the exact rev3 hash

ROLE: Planner
PHASE: DESIGN
AUTHORITY: design-only
DISPATCH_ID: s4-matrix-arm1-r48-design-rev3
PARENT_DISPATCH_ID: s4-matrix-arm1-r48-mf1-ruled
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-R48-MF1-RULED-OPTION-A-TIGHTEN-NOW-FOLDS-ENDORSED-20260809-204159.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no — MF-1's disposition is RULED (Option A, `204159`), the floor-contract wording is ruled a compatible narrowing there (floor CC'd on the ruling to object within its window), and every rev3 delta below is either the ruled rule verbatim or derived from it; this relay grants nothing — the fold dispatch waits on your approve; the release hold is ABSOLUTE
DESIGN_DOC_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-09-s4-matrix-arm1-r48-packer-home-carrier-design.md
DESIGN_RECORD_KIND: design-doc
GRILL_REQUIRED: yes
GRILL_LOCK_ID: s4-matrix-arm1-r48-carrier-grill-20260809
FROM: s4-matrix.planner
TO: s4-matrix.implementer
CC: s4.orchestrator-planner, operator, s4-floor.planner
SUBJECT: DESIGN-REVIEW request (rev3, unique lineage key) — verdict wanted: approve | must-revise | reject-narrow | human-decision-required

Rev3 is filed at the same DESIGN_DOC_ID with SHA-256
`06aeef6d33bcddecc14997ba14e969fa7ecbb6d28156f37490848b3846676983` (sealed after
authoring; your approve must cite THIS hash — design-doc lineage gate). The delta from
approved rev2 (`349ef6e1…`) rides this relay's commit, so `git diff HEAD^ HEAD -- <doc>`
at my commit shows exactly the amendment. This request carries a FRESH unique
DISPATCH_ID (the rev0-rev2 cycle reused `s4-matrix-arm1-r48-carrier` across stages — the
exact class the `141650` disposition retired; unique-ID-per-stage from here on).

FOLD MAP (ruling → rev3 bytes):

- **MF-1 Option A → §3 validity predicate:** `valid(p)` gains `non_degenerate(path,
  flavor)` — non-empty remainder after the flavor's root prefix: posix `size()>1`, wsl
  `size()>7`, windows drive `size()>3`, windows extended `size()>4`. The ruled thresholds
  verbatim. The `!path.empty()` conjunct is dropped as subsumed (empty classifies
  `nullopt`, failing the flavor match — stated in the doc). **The CLASSIFIER is
  untouched**: the grammar stays parity-pinned to `rewrite_common` (§9 test 14 survives
  unchanged), so the tightening lives entirely in the one validity authority both
  boundaries already share (grill D8's own structure — one predicate, two call sites).
- **Capture → §4:** capture now gates on the FULL predicate; `HOME=/`, `HOME=/mnt/c/`,
  `HOME=C:\` degrade to ABSENT — the ratified skip path, per the ruling's pack-side arm.
- **Serialize → §5:** the stated-collapse class now names degenerate roots explicitly.
- **Parse → §6:** degenerate roots fail-closed as `ParseError{"packer_home"}` under the
  EXISTING invalid-value rule (the ruling's parse-side arm: malformed, not a new
  semantic). §6's pairing sentence also fixed (correctness #7 nit, ruled to ride along):
  presence-XOR detail is ALWAYS `packer_home_flavor` in both directions, matching §8 and
  the code — rev2's "naming the lone key" implied two details it never had.
- **Contract → §7:** the contract row now states the narrowing and cites the ruling's
  compatible-narrowing verdict (floor CC'd there; no re-ratification per the ruling).
- **Cases → §8:** three new rows — degenerate `$HOME` at capture ⇒ absent; each
  degenerate spelling with its own matching flavor ⇒ `ParseError{"packer_home"}`;
  positive control `\\?\C:\Users\x` ⇒ valid (the rule bans only the bare 4-byte prefix).
- **Tests → §9:** 11b (degenerate-root parse matrix + positive control + serialize
  collapse extension) and 18b (`HOME=/` ⇒ absent capture row). Numbered as sub-letters so
  every existing §9 cross-reference in the locked plan and the panel record stays valid.
  §9-21/23 wording is deliberately UNTOUCHED — the panel graded the implementation
  against that wording and its fixes (MF-4/MF-6) implement it, not amend it.
- **Header/§11:** rev3 lineage block (rev2 approve, panel record `006144b2…`, the
  ruling); design locks on YOUR approve at the rev3 hash; §11 states the fold shape
  (ONE commit with MF-2..MF-6, then one targeted re-check).

What rev3 does NOT touch, stated for your falsification pass: the wire key shape,
`classify_absolute`'s grammar, `pack.cpp::path_flavor`/`source_path_flavor`, the
null≡missing rule, the D5 nine-member `ErrKind` freeze, both Step-3 fences, §10's hard
lines. The doc diff is confined to §§3-9 + header/§11 as mapped above.

Review asks: (1) the ruled thresholds transcribed correctly (each spelling's boundary
value — off-by-one here is the whole game); (2) the positive-control row is right
(`\\?\C:\Users\x` MUST stay valid); (3) no §9 renumbering broke a plan cross-reference;
(4) the §6 wording fix matches §8's table exactly. On your approve at the rev3 hash, I
issue the ONE complete fold dispatch (fresh unique ID, SCOPE_DIFF: the carrier's
existing ten paths — MF-1 touches `manifest.cpp` only within them) per the ruling's
mechanism; then the targeted re-check.

Reconcile note for the record: the ruling's carry list marks red 2's negative control
"result pending," but your `192358` completion already reported it (BASE reproduced the
same 5+3; both E2 reds closed under `183936`). Stale row, no action riding on it —
flagged so the record does not carry it forward.

Carried unchanged: branch `29796bb` LOCAL and untouched; publication held (P5); Waves
B/C/D F-fenced; zero-ref `capture_mode` awaiting m-1; human lenses unrouted until the
panel is clean at the exact head; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: docs lane only — rev3 design bytes + this relay + its INDEX row ride one explicit-path commit (SHA lands after filing); product and test paths were touched by no action at this seat; the carrier branch is untouched by me.
FINAL_GIT_STATUS_SHORT:
none — clean tree (matrix-seat paths; the shared checkout carries the Implementer's untracked relays and one s4-floor relay, preserved untouched)
Fresh at 20260809-205408 before this relay + INDEX write; the rev3 doc, this relay, and the INDEX row are this seat's working-tree delta at commit time.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/DESIGN-PLANNER-R48-CARRIER-REV3-MF1-TIGHTEN-REREVIEW-REQUEST-20260809-205408.md` → TO `s4-matrix.implementer`
- design rev3 `06aeef6d…` at the same DESIGN_DOC_ID → approve wanted on the exact hash; fold dispatch waits on it
- MF-1 ruled Option A (`204159`) → folded as §3 non_degenerate + derived rows; classifier untouched; floor narrowing ruled compatible (floor's objection window per the ruling)
- fold downstream → ONE commit (MF-1 + MF-2..MF-6 + optional tier at your discretion), then one targeted re-check; human lenses after clean
