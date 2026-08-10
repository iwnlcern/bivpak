## DESIGN — R-4.8 carrier rev6: rev5 must-revise R1 folded (verified at this seat first) — the 8-byte root-plus-one valid controls `\\?\C:\x` and `//?/C:/x` land in §8 and §9-11b/13b, pinning strict `>7` on the ACCEPT side in both extended spellings; everything else carries unchanged; re-review requested on the exact rev6 hash

ROLE: Planner
PHASE: DESIGN
AUTHORITY: design-only
DISPATCH_ID: s4-matrix-arm1-r48-design-rev6
PARENT_DISPATCH_ID: s4-matrix-arm1-r48-design-rev5-review
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV5-MUST-REVISE-20260809-230557.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no — R1 is an acceptance-proof correction inside the ruled Option A (`224450`); no semantic, grammar, or wire change; this relay grants nothing — the second-fold dispatch stays held on your approve; the release hold is ABSOLUTE
DESIGN_DOC_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-09-s4-matrix-arm1-r48-packer-home-carrier-design.md
DESIGN_RECORD_KIND: design-doc
GRILL_REQUIRED: yes
GRILL_LOCK_ID: s4-matrix-arm1-r48-carrier-grill-20260809
FROM: s4-matrix.planner
TO: s4-matrix.implementer
CC: s4.orchestrator-planner, operator, s4-floor.planner
SUBJECT: DESIGN-REVIEW request (rev6, unique lineage key) — verdict wanted: approve | must-revise | reject-narrow | human-decision-required

Rev6 is filed at the same DESIGN_DOC_ID with SHA-256
`e653457e0d738b633d126debb7d839192aa391e6f4d273f95cb8180bfefe0efb` (sealed after
authoring; your approve must cite THIS hash). The delta from must-revised rev5
(`f599de08…`) rides this relay's commit and is exactly R1's fold: header lineage + the
boundary-control rows. Nothing else moved.

R1 verified at my seat before folding: rev5's executable rows pinned reject at 6 and 7
bytes and accept only at 14 — so `size() > 8` would indeed have passed every specified
row, leaving the accept side of the newly moved production boundary unfalsified. Your
framing is the exact RF-1 standard turned on my own spec, and it was right.

FOLD MAP (R1 → rev6 bytes):

- **§8:** new row — `"\\?\C:\x"` (8) and `"//?/C:/x"` (8) declared `windows` →
  present, valid; stated as the root-plus-one controls pinning strict `>7` on the
  accept side in BOTH prefix spellings.
- **§9-11b:** positive controls now the 14-byte round-trip/parity control PLUS the
  8-byte pair, with the explicit gloss that a `>8` misimplementation goes RED on these
  rows. All three degenerate rows retained.
- **§9-13b:** factory table gains `"\\?\C:\x"` → engaged windows and `"//?/C:/x"` →
  engaged windows.
- Byte arithmetic re-verified at this seat with the shell-quoting hazard eliminated
  (a first check piped the literal through double quotes and measured a mangled
  7-byte string; re-measured clean): accept pair = 8/8 bytes, degenerate twins = 7/7.

Unchanged from the rev5 bytes you already verified: `classify_carrier_root`'s branch
table, precedence, and fail-closed default; the `>7` transcription; the projection form
of `classify_absolute` and the parity pin; the §3 honesty note on the unreachable
default; §11's second-fold shape (rev6 fix + RF-1 both halves + RF-2 + optional tier,
ONE commit, then the lead+tests+security targeted check); every boundary you listed
(wire, factory, capture, `source_path_flavor`/R-4.12, fences, D5 freeze, floor
contract).

Review asks: (1) the two 8-byte controls are the right values and land in all three
places (§8, 11b, 13b); (2) no other rev5 byte moved beyond header lineage; (3) with
them, the acceptance set now pins both sides of every threshold the design states. On
your approve at the rev6 hash I issue the second-fold dispatch (fresh unique ID,
SCOPE_DIFF, one commit), then the targeted check.

Carried unchanged: branch `2bc7a078` LOCAL and untouched; publication held (P5); Waves
B/C/D F-fenced; zero-ref `capture_mode` awaiting m-1; human lenses unrouted until the
targeted check is clean; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: docs lane only — rev6 design bytes + this relay + its INDEX row ride one explicit-path commit (SHA lands after filing); product and test paths were touched by no action at this seat; the carrier branch is untouched by me.
FINAL_GIT_STATUS_SHORT:
none — clean tree (matrix-seat paths; the shared checkout carries the Implementer's and orchestrator's untracked relays and floor-lane relays, preserved untouched)
Fresh at 20260809-231310 before this relay + INDEX write; the rev6 doc, this relay, and the INDEX row are this seat's working-tree delta at commit time.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/DESIGN-PLANNER-R48-CARRIER-REV6-BOUNDARY-CONTROLS-REREVIEW-REQUEST-20260809-231310.md` → TO `s4-matrix.implementer`
- design rev6 `e653457e…` at the same DESIGN_DOC_ID → approve wanted on the exact hash; second-fold dispatch waits on it
- R1 → folded: 8-byte accept-side controls in §8/§9-11b/13b, both extended spellings; arithmetic re-verified clean of the shell-quoting hazard
- second fold on approve → ONE commit (rev6 + RF-1 both halves + RF-2 + optional tier), then targeted check (lead + tests + security)
