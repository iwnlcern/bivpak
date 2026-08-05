## AUDIT DISPATCH — s4-floor: the A7 floor + adapter-leg surface at `main@8981bfd`, paired and independent

ROLE: Orchestrator Planner
PHASE: AUDIT
AUTHORITY: read-only
DISPATCH_ID: s4-floor-audit
PARENT_DISPATCH_ID: s4-build-standup-step4-opening-dispatch
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no — read-only audit; merge/release gates unaffected; the release hold is ABSOLUTE and untouched here
FROM: s4.orchestrator-planner
TO: s4-floor.planner, s4-floor.implementer
CC: operator, s4.orchestrator-reviewer
SUBJECT: AUDIT — A7 floor + adapter legs recon at `main@8981bfd`, independent per seat

RE-HOME NOTE: this is the dispatch of record, superseding the pdc-filed copy
(`master/subteams/s4/relays/s4-floor-audit/…-225816.md`, removed pre-transport under
operator direction 2026-08-04). Content is unchanged except substrate paths: s4 artifacts
live in THIS repo (the code repo, your cwd); the docs repo is `../pdc/`.

Paired independent audits: EACH seat reads the code and files its OWN artifact under
`docs/sprints/2026-08-04-s4-step4/audits/` (suggested names `s4-floor-audit-planner.md`,
`s4-floor-audit-implementer.md`) plus a relay TO this seat under
`.relays/s4/s4-floor-audit/`. Do not co-author; do not read your partner's artifact
before filing your own. Reconciliation happens at this seat
(`docs/sprints/2026-08-04-s4-step4/RECONCILE.md`).

Baseline: this repo at `main@8981bfd` — pin your reads to that SHA. The LOCKED A7 you
consume is `../pdc/master/domains/m-2-agent-adapters/design/2026-07-21-ADDENDUM-7-version-floor.md`
(full-cycle lock `2e402057`); verify the lock id before relying on any clause.

### Scope — what to establish, all E1, no edits anywhere

1. **R-W.1 / C1 both-legs head, verified still unlanded.** The package cites
   `codex/install.cpp:195` and `claude_code/install.cpp:331` as bare `starts_with`.
   Re-find both by criterion (the three-step conjunction — literal membership AND full
   grammar AND total order ⇒ else typed REFUSE — absent on each leg), confirm at
   `8981bfd`, and name every call path that reaches each site.
2. **The R-VF.1/2/3 implementing-head debt (fence F-2), current behavior per site.**
   (1) the consent path's end-to-end vs bare-skip-exit-0 behavior; (2) what
   `install(…, Consent::no)` writes today vs the required install-ready staged bytes +
   A9 sidecar; (3) the `staged`→`session_install_failed` mapper. Establish present
   behavior with file:criterion evidence for all three, on BOTH legs where applicable.
3. **R-3.25(a) sites, verified.** The codex `live_at_pack` assignment (cited
   `codex.cpp:391`, hardcoded `false`, claimed the ONLY codex assignment — verify the
   ONLY-ness with a stated instrument), the computed claude path (`claude_code.cpp:430`
   from `LiveFacts`), and the pure-propagation claim for `pack.cpp`/`manifest.cpp`/
   `sessions.cpp`. Map where m-2's disposition (`170500` §4: terminal tail-record set
   `{task_complete, turn_aborted, thread_rolled_back}`, fail-closed on any other tail,
   one default-visible warning, attestation-bound MAY-wording) would land — surfaces
   only, no design of your own.
4. **A7 floor surface enumeration (fences F-1..F-6).** From the locked A7: the survey
   constants, MIN vs `surveyed_through` (they are DIFFERENT things — the pack floor vs
   the disclosure watermark), the same-commit mirror/RUNCARD law (§A7.10), the
   `entry_schema: 2` archive-only marker under joint-seam pins P1–P5. Enumerate every
   file the floor implementation must touch, and mark which are `repos[]`-adjacent in
   `manifest.cpp` (the named collision with `s4-matrix`'s Arm-1 schema act).
5. **Receipt-plan cross-check — the exit obligation's ground truth.** Against m-2's
   `170500` §3 (six A7 receipts row-by-row) and the cold-start package (`222800` §3,
   twelve A5 arms) with the carrier at `ce9ef8c` (§8 silent-promotion frozen-oracle
   mutation spec): for each of the EIGHTEEN, record whether its fixture keys exist in
   tree today, their arm state (BOUND / MUTATION-required), and what the receipt's
   execution will need that does not yet exist. No receipt is executed at audit — this
   is the inventory that lets the plan produce them as arms land.
6. **Duplicate/already-built gate (4-bucket, per surface).** Any partial floor/version
   plumbing already landed? `PRIMARY_BUCKET` + all four lines per surface.

Reference docs (paths relative to this repo's root): the design package
`../pdc/master/domains/m-1-format-engine/design/2026-08-04-STEP4-DESIGN-PACKAGE.md`;
the charter `../pdc/master/subteams/s4/README.md`; m-2's receipt plans
`../pdc/master/relays/s375-build-standup/DESIGN-PLANNER-M2-GATE3-MEASURED-TWELVE-RECEIPTS-CIRCULARITY-G5-DISPOSED-20260804-170500.md`;
the cold-start package inside
`../pdc/master/relays/s375-build-standup/DESIGN-PLANNER-M2-FORWARD-CORRECTION-CONCURRED-COLDSTART-PACKAGE-20260804-222800.md` §3;
**the twelve A5 receipt plans (LANDED 2026-08-04, relayed across the bridge at `230800`):**
`../pdc/master/relays/s375-build-standup/DESIGN-PLANNER-M2-TWELVE-A5-RECEIPT-PLANS-UNDERTAKING-DISCHARGED-20260804-224200.md`
— note m-2's operative flags there and verify them at the artifact, not from this pointer:
the `A5.8/silent-promotion` mutation runs per the carrier's §8, NOT its byte-verbatim §1
row; sibling-stays-green is PART of the receipt content for the visibility arms; every
fixture must be GREEN before its mutation; one mutation per receipt, applied in isolation,
reverted after;
the carrier `../pdc/master/domains/m-2-agent-adapters/audit/2026-07-13-rclass2-fixture-evidence-map.md`
at `ce9ef8c` (a pdc commit — read it as the committed blob, not the working copy).

### Out of scope — hard lines

- NO edit, branch, build-config change, or fixture write in this repo; no `.github/`
  work; no host probing; no host-store surface of any kind.
- The five matrix arms belong to `s4-matrix`'s audit — note collisions, do not audit
  their internals.
- The m-2 seam may-not-move list (charter §2) is CONSUMED, not questioned: seam
  questions route TO this seat for the bridge; never sideways, never designed around.
- R-4.1 promisor arm (ii) and R-4.2 sparse implementation are traps — out, per charter.

### Acceptance criteria

- Every claim carries E1 evidence at the pinned SHA; criteria over line numbers;
  absence claims via `git grep -F` at the blob with the population stated; ONLY-ness
  claims name their instrument and its scope.
- MIN vs `surveyed_through` are never conflated in any sentence of the artifact.
- The receipt inventory covers all EIGHTEEN with per-receipt tree-state rows.
- The 4-bucket verdict is filled per surface with `PRIMARY_BUCKET`.
- Boundary contract: not applicable at audit (read-only, no writes produced).
- The report of record is the relay file: include `FINAL_GIT_STATUS_SHORT` (fresh, after
  all reads, path-scoped disclosure if the tree is dirty with unrelated state) and
  `ACTIONS_GIT_REF: no edits claimed` with the status proof.
- Lint author-side WITH freshness before filing (D-3.4); append your row at the tail of
  `.relays/s4/INDEX.md`; end your hand-off with a CARRY LIST (D-8.5).

ACTIONS_GIT_REF: no edits claimed in this repo's tracked tree by this relay; the relay + its INDEX row live in the gitignored .relays/ substrate
FINAL_GIT_STATUS_SHORT: not claimed here — see the substrate-correction SITREP of record for this seat's path-scoped status at filing
