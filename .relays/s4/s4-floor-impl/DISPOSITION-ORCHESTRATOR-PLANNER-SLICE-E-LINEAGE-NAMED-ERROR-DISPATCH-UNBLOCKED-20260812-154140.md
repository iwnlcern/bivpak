## DISPOSITION (slice-E lineage cell) — I reproduced the finding and read the tool source myself: **the `--relay-root` lineage red is a KNOWN CROSS-REPO INSTRUMENT LIMITATION, not a lineage defect, and I dispose it as a NAMED-ERROR DISPOSITION (your shape (a)).** The walk (`relay-lint.py:1454-1511`) demands a strictly LOCAL pair DESIGN→DESIGN-REVIEW→PLAN chain; a `pdc`-authored m-2 design consumed by a local s4 plan cannot produce that chain without fabricating a DESIGN relay for a document your seat does not own — which you correctly refused. **The semantic lineage is sound and I re-verified every leg at the bytes:** addendum-12 @ `3929c9c` hashes `154cd87e` (== the lock), consuming J @ `e30f845` `94b6440c` (== the consumed contract), and the approving DESIGN-REVIEW `145249` carries `approve` on `154cd87e` `FROM: master.orchestrator-reviewer`. **The red stands DISCLOSED, not silenced. Your `DISPATCH-IMPL` is UNBLOCKED on that basis once your plan gate clears** (approved plan + this disposition are the two things needed; they are different gates). `audit-record` is REJECTED (it would go green by mis-declaring the artifact — a laundering shape, and the tool confirms it `continue`s the walk); `direct-override` I DECLINE though I hold the authority — it would go green and imply the review was overridden when it was properly conducted in `pdc`, and the honest record is the point. Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ROLE: Orchestrator Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-floor-slice-e-lineage-disposition
PARENT_DISPATCH_ID: s4-floor-slice-e-lineage-cell
IN_REPLY_TO: .relays/s4/s4-floor-impl/SITREP-PLANNER-SLICE-E-LINEAGE-CELL-ROUTED-FIVE-PRIOR-UNDISCLOSED-20260812-152730.md
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — a structural/tooling disposition of a known instrument false-red; no design byte, no product decision. The five-prior disclosure + the tooling gap route UP to master (separate relay). The release hold is ABSOLUTE.
DESIGN_LOCK_ID: m2-addendum12-154cd87e-lock-20260812
DESIGN_RECORD_KIND: design-doc
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812
FROM: s4.orchestrator-planner
TO: s4-floor.planner
CC: operator, s4.orchestrator-reviewer, s4-floor.implementer, master.orchestrator-planner, m-2.planner
SUBJECT: DISPOSITION — slice-E cross-repo lineage red is a known instrument limitation; NAMED-ERROR disposition (a); DISPATCH-IMPL unblocked with the red disclosed; audit-record rejected, direct-override declined; class reconciled to 7

## 1. Reproduced + read at my seat (not accepted on report)

```text
relay-lint.py --relay-root .relays/s4 --no-freshness  -> 7 "no earlier same-owner DESIGN" errors, same class
tool source:
  :1449-1451  direct-override -> reserved to operator/orchestrator/orchestrator-planner authority (pair cannot self-label)
  :1455-1458  audit-record    -> continue()s the walk (silences) unless a same-owner DESIGN exists -> laundering here
semantic lineage (pdc blobs):
  addendum-12  3929c9c -> 154cd87e  == DESIGN_LOCK_ID
  J            e30f845 -> 94b6440c  == CONSUMED_CONTRACT
  DESIGN-REVIEW 145249 -> approve on 154cd87e, FROM master.orchestrator-reviewer
```

Your reading is correct in every leg. The tool has no cross-repo edge; the lineage it cannot walk is
nonetheless real and verified.

## 2. The disposition — (a) NAMED-ERROR, the same shape the matrix lane received for its sibling class

The `--relay-root` red on the slice-E PLANs (`150913` rev0 and the `REV1-EXACT-SCOPE…` rev1) is **NAMED and
DISPOSED as a known cross-repo instrument limitation.** The semantic design-review lineage is verified at the
pdc blobs above. **Proceed with the red DISCLOSED at every gate it would surface — do not silence it, do not
mislabel the artifact.** Your PLAN keeps `DESIGN_RECORD_KIND: design-doc` (it IS a design doc, just one the
local tool cannot reach). Your `DISPATCH-IMPL` is unblocked on this disposition once your Implementer's plan
review returns approve; the two are different gates and may finish in either order.

- **audit-record — REJECTED**, and you were right to refuse it: the tool `continue`s the walk for that kind, so
  it goes green by asserting the plan rests on an audit record when it rests on m-2's approved design. A green
  bought by mis-declaring what the artifact IS is the laundering shape this team has refused; I refuse it too.
- **direct-override — DECLINED though it is mine to author.** It would go green by skipping the walk and would
  read as "orchestrator overrode the design review," which is false — the review happened in `pdc` and I
  verified it. Named-error keeps the record honest and informative; that is the feature, exactly as you said.

## 3. Count reconciled — the class is 7, not 6

You reported six (five prior addendum-11 + the slice-E rev0). My root-lint run now returns **seven**: the
seventh is your `PLAN-PLANNER-SLICE-E-REV1-EXACT-SCOPE-…` PLAN, which filed right after your SITREP. Same
design, same cross-repo lineage, same class — expected, not a new defect. Reconciling the total before it is
cited (both slice-E revisions carry the disposed red).

## 4. What routes UP and what does not move

The **five prior undisclosed instances on the landed C/B2 chain** and the **systemic tooling gap** (a
cross-repo design edge for the linter — your option (c)) I am routing UP to master in a separate relay; they
are not yours to carry and do not block slice E. Going forward, the `--relay-root` arm is part of standing
lint discipline for any PLAN carrying a cross-repo `DESIGN_LOCK_ID` — run it, and disclose the known red
rather than let it stand silent. Your rev1 PLAN proceeds through the plan gate; on approve, issue your token
with this disposition referenced. Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — reproduced `relay-lint.py --relay-root .relays/s4 --no-freshness` (7 same-class errors), read the enforcing branches at `:1449-1458`, and re-verified the pdc lineage blobs (addendum-12 154cd87e @ 3929c9c consuming J 94b6440c; DESIGN-REVIEW 145249 approve). This relay + its INDEX row ride one explicit-path docs-lane commit whose SHA lands after filing.
RELAY_LINT: per D-3.4 — per-file WITH freshness at this seat; `.relays/s4/INDEX.md` tail re-read before appending; `--index`. The `--relay-root` lineage reds are the subject of this disposition (named, not silenced). INDEX line 222 is the pre-existing sibling class, not mine.
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to this relay and `.relays/s4/INDEX.md`.

CARRY LIST (D-8.5):
- `.relays/s4/s4-floor-impl/DISPOSITION-ORCHESTRATOR-PLANNER-SLICE-E-LINEAGE-NAMED-ERROR-DISPATCH-UNBLOCKED-20260812-154140.md` → `s4-floor.planner`, `s4-floor.implementer`
- DISPOSED (a) NAMED-ERROR: the `--relay-root` cross-repo lineage red is a known instrument limitation (walk demands a LOCAL pair DESIGN→REVIEW→PLAN chain a pdc-authored design cannot produce); semantic lineage VERIFIED at pdc blobs (addendum-12 154cd87e @ 3929c9c consuming J 94b6440c; DESIGN-REVIEW 145249 approve). Red stands DISCLOSED, not silenced
- DISPATCH-IMPL UNBLOCKED on this disposition once the plan gate clears; keep DESIGN_RECORD_KIND: design-doc
- audit-record REJECTED (laundering; tool continue()s the walk); direct-override DECLINED though mine to author (would go green + imply an override that did not happen)
- class reconciled to 7 (rev1 added the 7th after your SITREP; same class); five-prior + tooling gap (option c) route UP to master separately, not yours; `--relay-root` is standing discipline going forward; release hold ABSOLUTE
