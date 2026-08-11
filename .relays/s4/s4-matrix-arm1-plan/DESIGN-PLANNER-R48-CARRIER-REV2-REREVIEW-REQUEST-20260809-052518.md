## DESIGN — R-4.8 carrier rev2: R1-R3 folded (each byte-verified first) — single optional PackerHome struct, core-local total classifier with rewrite-parity pin, one lexical validator at every wire boundary, null≡missing rule, local detail remap; wire shape UNCHANGED so the floor ratification stands; re-review requested

ROLE: Planner
PHASE: DESIGN
AUTHORITY: design-only
DISPATCH_ID: s4-matrix-arm1-r48-carrier
PARENT_DISPATCH_ID: s4-build-standup-step4-opening-dispatch
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV1-20260809-050934.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no — all three revisions are code-derived (layering forces the core-local classifier; the model fix is forced by the design's own tests; null≡missing is the only rule the named helpers implement without raw-key tracking); no operator cell arose; the placement and Q1 rulings are unchanged
DESIGN_DOC_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-09-s4-matrix-arm1-r48-packer-home-carrier-design.md
DESIGN_RECORD_KIND: design-doc
GRILL_REQUIRED: yes
GRILL_LOCK_ID: s4-matrix-arm1-r48-carrier-grill-20260809
FROM: s4-matrix.planner
TO: s4-matrix.implementer
CC: s4.orchestrator-planner, operator, s4-floor.planner, m-4.planner
SUBJECT: DESIGN-REVIEW request (rev2) — verdict wanted: approve | must-revise | reject-narrow | human-decision-required

Rev2 is filed at the same DESIGN_DOC_ID; the grill lock carries a rev2 appendix (D6-D8,
all code-derived — no operator cell this round). I verified all three findings at the
bytes before folding: pack's `path_flavor` indeed has no `windows` branch; my §6 indeed
let `"relative/home"` and mismatched pairs through to the needle; the non-optional flavor
indeed could not represent my own §9 "both nullopt" tests; and `parse_path_flavor`'s
detail is indeed hardcoded `source_path_flavor` (manifest.cpp:462).

FOLD MAP (finding → rev2 bytes):

- **R1 → §3 (grill D7):** a core-local TOTAL classifier `classify_absolute(path) ->
  optional<PathFlavor>` beside the manifest schema, grammar mirroring
  `rewrite::path_flavor_for` + its three helpers EXACTLY (wsl mount; windows drive both
  separators; windows extended `\\?\`//`//?/`; posix leading-slash; else nullopt), with
  the parity PINNED by a spelling-table test including both layers (§9 test 14). Your
  suggested direct reuse was rejected for a reason you'll want to check: the PARSER needs
  the classifier too (R2), and `manifest` cannot include `rewrite_common` — which itself
  includes `manifest` for `PathFlavor` — so reuse is circular from the parse side.
  Extending pack's `path_flavor` was rejected per your own warning (source-path callers).
  `source_path_flavor` behavior untouched. Windows rows added to capture matrix (§9
  test 20 — lexical capture is host-independent, so it runs on any CI host).
- **R2 → §3/§5/§6 (grill D8):** ONE host-independent lexical validator
  `valid(p) := !path.empty() && classify_absolute(path) == flavor`, applied at BOTH
  boundaries: parse rejects (`ParseError{"packer_home"}` — subsumes "", relative, and
  every path/flavor mismatch), serialize gates (emittable states = {absent, valid};
  a manually constructed invalid engaged value COLLAPSES to omitted — the stated-collapse
  rule extended from empty to the whole invalid class, so the design no longer claims
  capture makes invalid impossible). Native `is_absolute()` used NOWHERE at wire
  boundaries. Falsifiers: §9 tests 2, 10, 11.
- **R3 → §3/§6/§8 (grill D6/D8):** the model is now ONE
  `std::optional<PackerHome{path, flavor}>` — co-absence by construction, lone flavor
  unrepresentable in memory, "both nullopt" becomes `== std::nullopt`, round-trip is a
  single `==`; `InstallTarget` transport becomes the single field
  `optional<manifest::PackerHome>`. Null rule DEFINED: JSON `null` ≡ missing key for
  BOTH keys (adopting `optional_string`'s collapse as the rule — no raw-key tracking
  exists or is needed); the §6/§8 lone-null contradiction is resolved and tested (§9
  test 6). The flavor parse failure is REMAPPED locally to detail `packer_home_flavor`
  (helper and its callers untouched), with an exact-detail falsifier (§9 test 12).

FLOOR RATIFICATION — STANDS, per your own criterion: rev2 preserves the exact two-key
wire shape, own-flavor meaning, and absence semantics ratified at `050728`; only the
producer-side in-memory model changed. No re-route owed; any future WIRE change routes
back to the floor explicitly (§7).

Unchanged: operator placement + Q1 rulings, `format_version` 1, no capability, no new
`ErrKind`, Step-3 fences, B1/B4's passed shape (transport seam, 7-part boundary, test
surfaces — §9 now 23 numbered cases across the four real surfaces incl. your
`CountingAdapter` seam citation).

Return `DESIGN_REVIEW_VERDICT` parented to this relay, same DESIGN_DOC_ID. On approve the
lock condition is complete (floor already on record) and I file the design-completion
SITREP, then hold for PROCEED-TO-PLAN.

ACTIONS_GIT_REF: docs lane only — rev2 design + grill-lock appendix + this relay + INDEX row, one explicit-path commit (SHA in the commit record); no product/test edit.
FINAL_GIT_STATUS_SHORT:
none — clean tree (matrix-seat paths; the shared checkout carries the Implementer's two untracked review relays, preserved untouched)
Fresh at 20260809-052518 before this relay + INDEX write; the named docs-lane paths are this seat's working-tree delta at commit time.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/DESIGN-PLANNER-R48-CARRIER-REV2-REREVIEW-REQUEST-20260809-052518.md` → TO `s4-matrix.implementer`
- `docs/sprints/2026-08-04-s4-step4/designs/2026-08-09-s4-matrix-arm1-r48-packer-home-carrier-design.md` (rev2) + grill-lock appendix D6-D8 → under re-review
