## SITREP — routing the slice-E dispatch-lineage cell UP, with a disclosure that makes it worse than my Implementer found it. The error reproduces at my seat, and it is **NOT NEW: five of my own prior CB2 plans carry the IDENTICAL class under the addendum-11 lock, and NOT ONE of them was ever disclosed** — the class went unmeasured in this lane because nobody ran the relay-ROOT lint here, only the exact-file lint. My Implementer ran the root lint and found it. **No delegated dispatch issues from my seat until this is dispositioned.**

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-floor-slice-e-lineage-cell
PARENT_DISPATCH_ID: s4-floor-slice-e-plan
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new operator gate — this routes a STRUCTURAL/TOOLING cell above my pair. It changes no design byte and asks for no product decision. The release hold is ABSOLUTE.
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-REVIEW-IMPLEMENTER-SLICE-E-COUPLED-TRANSITIVE-COLLECT-MUST-REVISE-20260812-151658.md
FROM: s4-floor.planner
TO: s4.orchestrator-planner
CC: operator, s4.orchestrator-reviewer, s4-floor.implementer, master.orchestrator-planner, m-2.planner
SUBJECT: SITREP — cross-repo design lineage is not mechanically resolvable in the local relay root; reproduced, class measured (6 instances, 5 prior and undisclosed), three candidate shapes, no self-grant

## 1. The finding, reproduced at my seat rather than accepted on report

```
python3 ~/.claude/skills/tools/relay-lint.py --relay-root .relays/s4 --no-freshness

ERROR .relays/s4: s4-floor-impl/PLAN-PLANNER-SLICE-E-…-20260812-150913.md:
  DESIGN_LOCK_ID 'm2-addendum12-154cd87e-lock-20260812' has no earlier same-owner
  DESIGN relay carrying matching DESIGN_DOC_ID
```

## 2. What the instrument actually demands (read at the tool source, not inferred)

`relay-lint.py:1454-1511` walks a **strictly local pair chain** for any `PHASE: PLAN` from a pair Planner
carrying `DESIGN_LOCK_ID` with `DESIGN_RECORD_KIND: design-doc`:

```text
1. an EARLIER PHASE: DESIGN relay  FROM s4-floor.planner       with DESIGN_DOC_ID == the lock id
2. a  PHASE: DESIGN-REVIEW relay   FROM s4-floor.implementer   with DESIGN_REVIEW_VERDICT: approve,
                                   DESIGN_DOC_ID == the lock, PARENT_DISPATCH_ID -> (1)
3. the PLAN's PARENT_DISPATCH_ID -> (2)
```

**No shape of that chain can exist for slice E without my seat FABRICATING a DESIGN relay for a document it
does not own and did not author.** The design is m-2's, authored and approved in the `pdc` repo; the local
`.relays/s4` root contains no m-2 DESIGN relay and correctly cannot. **The tool has no cross-repo edge.**
The semantic lineage is nonetheless sound and I re-derived every leg of it: addendum-12 at pdc `3929c9c`
hashes `154cd87e…` (matches the lock), J at `e30f845` hashes `94b6440c…` (matches the consumed contract),
and the approving DESIGN-REVIEW `145249` carries `approve` on the identical target hash.

## 3. The disclosure I owe — the class is SIX instances, and five are mine and were never surfaced

```
s4-floor-impl/PLAN-PLANNER-B2-SIDECAR-LEG-RESUME-UNDER-STANDING-TOKEN-20260810-063656.md      addendum-11
s4-floor-impl/PLAN-PLANNER-CB2-FOLD-ONE-LEVEL-CONSISTENT-CONSTRAINT-20260810-193623.md        addendum-11
s4-floor-impl/PLAN-PLANNER-CB2-HOLD-L1-ALIAS-ARM-PENDING-R415-DESIGN-20260810-203310.md       addendum-11
s4-floor-impl/PLAN-PLANNER-CB2-PARTIAL-FOLD-VERIFIED-L3-PREMISE-MEASURED-20260810-214246.md   addendum-11
s4-floor-impl/PLAN-PLANNER-CB2-BASE-CONTAINER-CONTROL-OWED-BEFORE-HANDUP-20260811-013353.md   addendum-11
s4-floor-impl/PLAN-PLANNER-SLICE-E-…-20260812-150913.md                                       addendum-12
```

All six are the **same error string**, same mechanism, same cause: a pdc-authored m-2 design consumed by a
local pair plan. **`grep -rl 'no earlier same-owner DESIGN' .relays/s4/` returns NOTHING** — the class was
never named in a single relay of this lane. The five addendum-11 instances rode the C/B2 chain that reached
delegated dispatch, merge hand-up and landing **with this red standing and unmentioned.** I am not asking for
that to be waived retroactively; I am reporting it because it is true and because the lane's record currently
implies a cleanliness it did not have.

**The cause is mine and it is exactly the shape this team keeps re-learning: I ran the instrument that could
not return the finding.** My standing lint discipline was per-file plus `--index`. The `--relay-root` arm is
the only one that walks lineage, and I never ran it. A check that cannot fire is not a check — my Implementer
ran the arm I did not and got a result I had six chances to get first.

**Not the same class, for the record:** the `s4-matrix-arm1-plan` / `s4-matrix-wave-a-panel` rows in the same
lint output are `DESIGN_LOCK_ID references missing file …` — a different predicate (local design path), the
one that produced that lane's two named-error dispositions. Precedent for the *mechanism* of disposition
exists there; precedent for **this** predicate does not.

## 4. Candidate shapes — yours to pick, and two of the three are NOT mine to take

- **(a) A NAMED-ERROR DISPOSITION** on this exact predicate, as the matrix lane received twice for its
  sibling class: the error is named, the semantic lineage is recorded as independently verified at the pdc
  blobs, and dispatch proceeds with the red disclosed rather than silenced. **Cheapest, and it leaves the
  record honest.** It does not make the lint green, which I regard as a feature.
- **(b) `DESIGN_RECORD_KIND: direct-override`**, authored by operator/orchestrator authority. The tool skips
  the lineage walk for that kind (`:1449`) **and errors if a pair Planner uses it** (`:1451`). **I will not
  self-label it** — my Implementer flagged that and is right; the enum reserves it to your authority, not
  mine.
- **(c) A TOOLING FIX** giving the linter a cross-repo design edge (e.g. a `DESIGN_DOC_REPO`/commit+hash
  field it can verify directly, which would be strictly better evidence than a same-repo relay chain).
  **Not my seat's file and not this slice's scope**; it also does not have to block slice E if (a) issues.

**A shape I considered and reject, stated so nobody adopts it later:** `DESIGN_RECORD_KIND: audit-record`
mechanically silences this error — the walk `continue`s at `:1455-1458` when no same-owner DESIGN relay
exists, which is precisely my situation. **It would go green and it would be a lie.** This plan does not rest
on an audit record; it rests on m-2's approved design doc. Making an instrument green by mis-declaring what
the artifact IS is the laundering shape this team has refused before, and I refuse it here.

**My recommendation is (a) now and (c) on someone's backlog.**

## 5. Status and what does not move

The rev1 PLAN answering my Implementer's R1-R5 files immediately after this relay and is addressed to them;
the plan gate can proceed in parallel because **an approved plan and a clean delegated-dispatch path are
different gates.** What is BLOCKED is the token: **no `DISPATCH IMPL`-bearing relay issues from my seat until
this cell is dispositioned.** No product byte, no branch, no PR. Merge ≠ push ≠ release; the release hold is
ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — reproduced the root-lint lineage error at `.relays/s4`, read the enforcing walk at `relay-lint.py:1449-1511` and `:1110-1148`, enumerated the six same-class instances, and confirmed by grep that the class appears in no relay of this lane; this relay + its INDEX row ride one explicit-path docs-lane commit whose SHA lands after filing
RELAY_LINT: per D-3.4 — per-file WITH freshness before filing; `.relays/s4/INDEX.md` tail re-read before appending; `--index`. Standing disclosed reds: INDEX line 222 (`20260809-142630` after `20260809-142708`) is the pre-existing sibling class, present in `HEAD~1` and not mine; the root-lint lineage error on the rev0 PLAN is the subject of this relay and is NOT claimed cleared
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to this relay and `.relays/s4/INDEX.md`

CARRY LIST:
- `.relays/s4/s4-floor-impl/SITREP-PLANNER-SLICE-E-LINEAGE-CELL-ROUTED-FIVE-PRIOR-UNDISCLOSED-20260812-152730.md` → `s4.orchestrator-planner`
- the cross-repo design-lineage error REPRODUCED at my seat; the tool's walk demands a strictly LOCAL pair DESIGN → DESIGN-REVIEW → PLAN chain that cannot exist for a pdc-authored m-2 design without fabricating a DESIGN relay
- CLASS IS SIX, FIVE PRIOR AND UNDISCLOSED (addendum-11, across the landed C/B2 chain) — cause: I ran per-file + `--index` and never the `--relay-root` arm that walks lineage; my Implementer ran it and found what I had six chances to find
- distinct from the matrix lane's `references missing file` predicate (which holds the two named-error-disposition precedents)
- shapes: (a) named-error disposition RECOMMENDED, (b) `direct-override` — YOURS to author, I will not self-label, (c) linter cross-repo edge; `audit-record` REJECTED as a laundering shape that would go green by mis-declaring the artifact
- rev1 PLAN files next to my Implementer; **no `DISPATCH IMPL` token issues from my seat until this cell is dispositioned**; release hold ABSOLUTE
