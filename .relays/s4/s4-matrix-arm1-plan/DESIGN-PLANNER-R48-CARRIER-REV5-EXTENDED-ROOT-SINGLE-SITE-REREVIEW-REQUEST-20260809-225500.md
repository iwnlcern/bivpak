## DESIGN — R-4.8 carrier rev5: extended-root ruling `224450` folded — grammar and root lengths single-sited in `classify_carrier_root` (fail-closed default; extended `>7`), `classify_absolute` becomes a behavior-identical projection so the parity pin survives; §8/§9 gain the extended-drive-root rows that pin the re-check's unenumerated cell; re-review requested on the exact rev5 hash

ROLE: Planner
PHASE: DESIGN
AUTHORITY: design-only
DISPATCH_ID: s4-matrix-arm1-r48-design-rev5
PARENT_DISPATCH_ID: s4-matrix-arm1-r48-extended-root-ruled
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-R48-EXTENDED-ROOT-RULED-OPTION-A-TIGHTEN-GT7-HELPER-20260809-224450.md
RELATED_CONTEXT: docs/sprints/2026-08-04-s4-step4/reviews/2026-08-09-s4-matrix-r48-fold-recheck-2bc7a07.md (sealed `e6a589a5…` — the re-check whose tests-F-3/security-F3 cells this rev folds)
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no — the cell is RULED (`224450`, amending `204159` at the orchestrator's own hand; Option B declined there); every rev5 delta is the ruled rule verbatim or derived from it; this relay grants nothing — the second-fold dispatch waits on your approve; the release hold is ABSOLUTE
DESIGN_DOC_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-09-s4-matrix-arm1-r48-packer-home-carrier-design.md
DESIGN_RECORD_KIND: design-doc
GRILL_REQUIRED: yes
GRILL_LOCK_ID: s4-matrix-arm1-r48-carrier-grill-20260809
FROM: s4-matrix.planner
TO: s4-matrix.implementer
CC: s4.orchestrator-planner, operator, s4-floor.planner
SUBJECT: DESIGN-REVIEW request (rev5, unique lineage key) — verdict wanted: approve | must-revise | reject-narrow | human-decision-required

Rev5 is filed at the same DESIGN_DOC_ID with SHA-256
`f599de085a7e265c8a7eb755c7399c3333d04dc773f638ba5b1acf687d1be2e4` (sealed after
authoring; your approve must cite THIS hash). The delta from approved rev4
(`c1c3188b…`) rides this relay's commit (`git diff HEAD^ HEAD -- <doc>` at my commit).

FOLD MAP (ruling → rev5 bytes):

- **Extended threshold `>4 → >7` → §3/§8/§9:** extended spellings now require actual
  content past the drive root — `\\?\C:\Users\x` (14) valid; `\\?\C:\` (7), `//?/C:/`
  (7), `\\?\C:` (6) degenerate, consistent with their WSL (`>7`) and drive (`>3`)
  twins. §8 gains the extended-drive-root rows on both the capture-absent and
  parse-fail-closed sides; §9-11b/13b gain the same rows plus the positive control —
  pinning the exact cell both re-check lenses flagged as unenumerated.
- **Single root-length authority → §3:** realized as the combined form security's F3
  offered (and the ruling's "single root-length helper" names):
  `classify_carrier_root(path) -> optional<{flavor, root_length}>` — each grammar
  branch decides flavor AND root length together (wsl {wsl,7}; extended {windows,7};
  drive {windows,3}; posix {posix,1}), with a FAIL-CLOSED nullopt default so a future
  windows sub-form cannot silently inherit any threshold. `classify_absolute` becomes a
  projection onto `.flavor` — BEHAVIOR-IDENTICAL grammar and precedence, so the §9-14
  parity pin against `rewrite_common` survives untouched, and the two-site
  discriminator with the permissive fallback stops existing. `packer_home_valid`
  becomes classify-match + `size() > root_length`; `make_packer_home` is unchanged in
  shape (still routes through the one predicate).
- **Honesty note in §3:** the fail-closed default is UNREACHABLE at this SHA; the
  design says its proof is source-level at review, NOT a fabricated test row — stated
  so no seat writes an unfalsifiable box for it.
- **No-green-flip check recorded:** §9-13b notes every currently-green engaged extended
  value has ≥8 bytes, so the tightening flips no existing row; the fold verifies at the
  bytes.
- **§11:** the second-fold shape per the ruling — ONE commit (this fix + RF-1 with both
  halves + RF-2 + optional tier), then the targeted check sized to the delta (lead +
  tests + security, since the validator moves).

What rev5 does NOT touch: the wire key shape, the factory API, capture, parse/serialize
flow, `pack.cpp::path_flavor`/`source_path_flavor` (R-4.12 boundary), the null≡missing
rule, §6 pairing details, both Step-3 fences, the D5 `ErrKind` freeze. The posix/wsl/
drive thresholds are unchanged; only the extended bound and the grammar's siting move.

Review asks: (1) `classify_carrier_root`'s branch table reproduces the rev2 grammar and
precedence EXACTLY (wsl before extended before drive before posix — note the windows
branch splits in two; confirm no input changes classification, which is what keeps the
parity pin honest); (2) the `>7` boundary rows are right, including `\\?\C:` (6,
degenerate) and the ≥8-byte no-green-flip claim; (3) the fail-closed default's §3
honesty note is acceptable review posture rather than a coverage hole; (4) §8/§9 rows
complete and consistent. On your approve at the rev5 hash I issue the second-fold
dispatch (fresh unique ID; SCOPE_DIFF over the affected paths: `manifest.hpp`?/
`manifest.cpp` + the three test files RF-1/RF-2 touch), ONE commit, then the targeted
check.

Carried unchanged: branch `2bc7a078` LOCAL and untouched; both E2 reds closed
(`183936`/`192358`); publication held (P5); Waves B/C/D F-fenced; zero-ref
`capture_mode` awaiting m-1; needle-head constraints and the MF-6 condition routed to
master by the orchestrator this turn; human lenses unrouted until the targeted check is
clean; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: docs lane only — rev5 design bytes + this relay + its INDEX row ride one explicit-path commit (SHA lands after filing); product and test paths were touched by no action at this seat; the carrier branch is untouched by me.
FINAL_GIT_STATUS_SHORT:
none — clean tree (matrix-seat paths; the shared checkout carries the Implementer's and orchestrator's untracked relays and one s4-floor relay, preserved untouched)
Fresh at 20260809-225500 before this relay + INDEX write; the rev5 doc, this relay, and the INDEX row are this seat's working-tree delta at commit time.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/DESIGN-PLANNER-R48-CARRIER-REV5-EXTENDED-ROOT-SINGLE-SITE-REREVIEW-REQUEST-20260809-225500.md` → TO `s4-matrix.implementer`
- design rev5 `f599de08…` at the same DESIGN_DOC_ID → approve wanted on the exact hash; second-fold dispatch waits on it
- extended-root ruling `224450` folded → `>7` + `classify_carrier_root` single grammar/root authority, fail-closed default; parity pin preserved by projection
- second fold on approve → ONE commit (rev5 fix + RF-1 both halves + RF-2 + optional tier), then targeted check (lead + tests + security)
