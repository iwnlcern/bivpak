## AUDIT DISPATCH — s4-matrix: the git-engine surface at `main@8981bfd`, paired and independent

ROLE: Orchestrator Planner
PHASE: AUDIT
AUTHORITY: read-only
DISPATCH_ID: s4-matrix-audit
PARENT_DISPATCH_ID: s4-build-standup-step4-opening-dispatch
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no — read-only audit; merge/release gates unaffected; the release hold is ABSOLUTE and untouched here
FROM: s4.orchestrator-planner
TO: s4-matrix.planner, s4-matrix.implementer
CC: operator, s4.orchestrator-reviewer
SUBJECT: AUDIT — five-arm matrix surface recon at `main@8981bfd`, independent per seat

RE-HOME NOTE: this is the dispatch of record, superseding the pdc-filed copy
(`master/subteams/s4/relays/s4-matrix-audit/…-225815.md`, removed pre-transport under
operator direction 2026-08-04). Content is unchanged except substrate paths: s4 artifacts
live in THIS repo (the code repo, your cwd); the docs repo is `../pdc/`.

Paired independent audits: EACH seat reads the code and files its OWN artifact under
`docs/sprints/2026-08-04-s4-step4/audits/` (suggested names `s4-matrix-audit-planner.md`,
`s4-matrix-audit-implementer.md`) plus a relay TO this seat under
`.relays/s4/s4-matrix-audit/`. Do not co-author; do not read your partner's artifact
before filing your own. Reconciliation happens at this seat
(`docs/sprints/2026-08-04-s4-step4/RECONCILE.md`).

Baseline: this repo at `main@8981bfd` — pin your reads to that SHA (`git show
8981bfd:<path>` or a clean checkout); the working tree may carry unrelated branches.

### Scope — what to establish, all E1 (file:line/criterion), no edits anywhere

1. **The Step-3 fences, re-found by criterion (R-3.50: criteria, not line numbers).**
   The package cites `scan.cpp:137-138` (any `.git` ⇒ typed `RepoDiscoveredUnsupported`
   refusal) and `manifest.cpp:597` (`require_empty_array` on `repos`). Re-find both from
   their criteria at `8981bfd`, confirm each is the ONLY site of its behavior, and record
   what the typed refusal's blast radius is (every caller that can reach it).
2. **The landed payload-restore base Arm 1 EXTENDS (package §1.2).** Verify the staging
   atomicity slice (partial-dir staging, collision handling incl. rename-exhausted refusal,
   containment/member safety) as landed behavior; name the seams a repo-restore path would
   plug into. The matrix extends this staging — flag anything that would force
   re-invention instead.
3. **DR-3 fixture inventory — the RED-to-GREEN flip set.** Enumerate EVERY fixture/test
   that asserts `repos: []` refused-if-populated or otherwise pins the empty-repos
   invariant. This list seeds Arm 1's fixture ledger (flips are decided-not-deleted).
4. **Golden-harness seam.** What test harness/fixture infrastructure exists today that the
   contract-§5 golden round-trip harness (determinism / acceptable-difference classes)
   builds on; what is missing for a day-one Arm-1 row.
5. **Arm-by-arm surface map (Arms 1–5, package §2).** For each arm: files/functions it
   will touch, what exists vs is absent, and the collision surfaces — `manifest.cpp` is
   already named (Arm 1 schema act vs addendum F vs the floor pair's `repos[]`-adjacent
   work); find any OTHER shared file/test/contract with the `s4-floor` surface.
6. **Duplicate/already-built gate (4-bucket, per surface).** Any dead-pathed, flagged, or
   partial git-engine code beyond the fences? `PRIMARY_BUCKET` + all four lines per arm
   surface; a bucket answer that contradicts your recommendation is a defect.
7. **Drift check.** Beyond DR-1/DR-2/DR-3 (already named — do not re-litigate), does
   landed code diverge anywhere from the sealed restore-apply design as mapped in package
   §1.1? Report-only; drift is NAMED, never patched in an audit.

Reference docs (paths relative to this repo's root): the design package
`../pdc/master/domains/m-1-format-engine/design/2026-08-04-STEP4-DESIGN-PACKAGE.md`;
the charter `../pdc/master/subteams/s4/README.md`; the sealed docs the package maps
(`2026-07-02-pack-engine.md`, `2026-07-02-restore-apply-contract.md`, ADDENDA A/B/D,
`manifest-format.md` §2.3, all under `../pdc/master/domains/m-1-format-engine/design/`).

### Out of scope — hard lines

- NO edit, branch, build-config change, or fixture write in this repo; no `.github/`
  work; no host probing. Read-only means read-only.
- The A7 floor surface, adapters, and receipts belong to `s4-floor`'s audit — note
  collisions with them, do not audit their internals.
- Sealed-design questions (anything that smells like "the design should change") route TO
  this seat as questions; never as recommendations to amend a sealed doc locally.

### Acceptance criteria

- Every claim carries E1 evidence (path + criterion; line numbers only as convenience
  beside a re-findable criterion, at the pinned SHA).
- The DR-3 flip set is enumerated exhaustively, with the instrument stated (what you
  searched, over what population — absence claims via `git grep -F` at the blob).
- The 4-bucket verdict is filled for each arm surface with `PRIMARY_BUCKET`.
- Boundary contract: not applicable at audit (read-only, no writes produced).
- The report of record is the relay file: include `FINAL_GIT_STATUS_SHORT` (fresh, after
  all reads, path-scoped disclosure if the tree is dirty with unrelated state) and
  `ACTIONS_GIT_REF: no edits claimed` with the status proof.
- Lint author-side WITH freshness before filing (D-3.4); append your row at the tail of
  `.relays/s4/INDEX.md`; end your hand-off with a CARRY LIST (D-8.5).

ACTIONS_GIT_REF: no edits claimed in this repo's tracked tree by this relay; the relay + its INDEX row live in the gitignored .relays/ substrate
FINAL_GIT_STATUS_SHORT: not claimed here — see the substrate-correction SITREP of record for this seat's path-scoped status at filing
