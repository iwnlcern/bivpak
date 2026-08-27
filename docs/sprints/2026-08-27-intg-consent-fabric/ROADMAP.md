# intg — consent-fabric integration sprint (commissioned pair)

RUN_ID: intg
Commission: `CH-intg-consent-fabric` (pdc `master/relays/intg-commission-charter/DESIGN-master-planner-20260827-144023.md`, rev1 @ sha256 `82d02a57aad96151eb707c8ca708e47c130626a58ab9fccb287fa537e3b70c13`).
Grant: pdc `master/relays/intg-commission-grant/PLAN-master-planner-20260827-144459.md` (H27 stage (d), delegated dispatch to `intg.pair-planner`).
Seats: `intg.pair-planner` (adt-master:pair-planner) and `intg.pair-implementer` (adt-master:pair-implementer, subsumes adversarial review; no third seat).
Bridge: the ONE cross-team edge is `intg.pair-planner` -> `master.master-planner`; bridge relays live in pdc `master/relays/`.

## Relay substrate

The relay root is `.relays/intg/` at the bivpak repo root, engine-managed from birth (commissioned daemon; `INDEX.md`/`SEATS.md` are daemon projections).
The relay root is git-tracked per charter LAYOUT; `.relays/intg/.engine/` is engine-gitignored machine state.
This sprint root carries no `.relays/` subtree of its own; the charter fixes the run-level root at `.relays/intg/`, and that divergence from the skill default is recorded here.

## Spine (charter order, each behind its standing gate)

1. Sub-step 1 — the A6 rev14 consent-UX fabric, ENGINE UNWIRED (consumes LOCKED A6 `m3-addendum-6-c41d015f-lock-20260825`).
2. The format act consuming LOCKED M rev8 (`2966b839`) + LOCKED N (`82293732`) under V-M-INT-1..5 + V-N-1/V-N-2, with the (i)/(j) censuses at m-1's byte review.
3. Verb-to-engine wiring at product scope, ONLY after m-4's mandatory reachability re-review; M-R8 veto 9 ordering holds.

Not granted at any step: design-of-record amendment, merge, push, publication, deployment, release.
The release hold is ABSOLUTE.

## Standing dispositions from master (answer relay `intg-substep1-master-answers/PLAN-master-planner-20260827-155221.md`)

- Branch base CONFIRMED: `intg/consent-fabric` cuts from local `main@02b51435` (the phase-design pin); no rebase without a routed STOP.
- A7 (`m3-addendum-7`, S5–S7) rides the renewed VP verification; on the pass it seals at m-3 and JOINS the spec-of-record set — the S5–S7 surfaces stay un-PLANNED until the seal carries down.
- Bridge transport: up-facing relays file in this root and ride the operator's hand-carry; answers file in the pdc root and ride the carry back; no master-root intg seat.
- W-3 (cross-repo plan-lineage waiver) PROPOSED, not effective: no gated PLAN files before the operator's grant and the Master Reviewer's concurrence both land.

## Additional top-level files (declared per sprint-doc-setup)

- `DEVIATIONS.md` — the pair-local deviations ledger (Stock -> Ours -> Why -> Status), required by charter LAYOUT.
- `OBLIGATIONS.md` — the boot-read register of master/RESIDUALS.md rows binding this commission (charter rule 5 projection; the registry wins on conflict).
