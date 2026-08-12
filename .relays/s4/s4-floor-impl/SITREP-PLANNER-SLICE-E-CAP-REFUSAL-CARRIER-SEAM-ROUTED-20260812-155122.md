## SITREP — routing ONE inexpressible cell UP: **the two locked documents jointly demand something the existing API cannot deliver.** J requires a cap violation to make `pack` **fail typed and loud**; `A12.4.1` requires that same refused entry to produce a line on **`CollectReport.warnings`**. At the bytes, a typed fatal returns `expected`'s error and **DESTROYS the `PackReport` the warning would have ridden out on** — so the two requirements cannot both be observed through any path that exists today. **This is not a plan defect I can fix by writing more plan.** My Implementer found it; I reproduced it at the source, derived everything derivable, and route the one cell that needs authority — with three options framed and a recommendation I do not act on.

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-floor-slice-e-cap-carrier-seam
PARENT_DISPATCH_ID: s4-floor-slice-e-plan-rev1
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new operator gate to ROUTE this. The RESOLUTION is a normative call on locked design text or an API/result-carrier decision — m-2's or yours, not a pair Planner's and never an implementer's to invent mid-build. The release hold is ABSOLUTE.
DESIGN_DOC_ID: m2-addendum-12-transitive-collect-mono-gate-20260812
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m2-addendum12-154cd87e-lock-20260812
TARGET_DESIGN_SHA256: 154cd87ebdc0619cdf3a7172da9b46d5753888da68f03a10ed6c18c481ff4c77
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-REVIEW-IMPLEMENTER-SLICE-E-REV1-MUST-REVISE-COSEQUENCE-CARRIER-A3-20260812-154600.md
RELATED_CONTEXT: .relays/s4/s4-floor-impl/DISPOSITION-ORCHESTRATOR-PLANNER-SLICE-E-LINEAGE-NAMED-ERROR-DISPATCH-UNBLOCKED-20260812-154140.md (the lineage cell, disposed; this is a DIFFERENT and NEW cell)
FROM: s4-floor.planner
TO: s4.orchestrator-planner
CC: operator, s4.orchestrator-reviewer, s4-floor.implementer, master.orchestrator-planner, m-2.planner, m-1.planner
SUBJECT: SITREP — cap refusal must be a typed pack fatal AND a CollectReport.warnings line; the fatal discards the carrier. One cell routed with three options and a recommendation; no implementation authority exists to invent it

## 1. The two requirements, quoted from the locked bytes

```text
J (pdc e30f845, "Producer closure", :226-231 + Calibration :245-249)
  "the pack side refuses rather than emitting what J's own parser refuses. If an operator's real
   store presents a session tree exceeding any cap, pack FAILS TYPED AND LOUD; it never truncates
   and never emits an over-cap entry."
  "The refusal must be loud, typed, and NAME BOTH THE CAP AND THE OFFENDING ENTRY."

ADDENDUM-12 (pdc 3929c9c, A12.4.1 covered list)
  "Anything the closure cannot carry or cannot represent MUST produce a line on
   CollectReport.warnings … Covered: … ANY ENTRY REFUSED FOR EXCEEDING J'S CAPS."
```

## 2. Why they cannot both be observed today — measured at `0db8fdd`, not reasoned about

```text
src/core/pack/pack.cpp
  :469  expected<PackReport> pack_impl(...)         and :771 expected<PackReport> pack(...)
  :498  auto cleanup_error = [&](BivError error)    -> returns the ERROR; `report` is discarded
  :553-559  collected->no_cwd_record and collected->warnings are DRAINED into report.warnings
            IMMEDIATELY after collect() returns
  :560+     the per-session loop runs AFTER that drain, and every invalid path returns
            cleanup_error(BivError{...}) — including where manifest_entry_for is reached
src/adapters/adapter.hpp:281  virtual expected<CollectReport> collect(...)
```

**The carrier and the fatal are mutually destructive.** A cap detected pack-side fires
`cleanup_error`, `pack()` yields an error, and **there is no `PackReport` for the CLI or a test to read
the warning out of.** Appending to `collected->warnings` after `:559` writes to a vector nothing ever
drains again — an unreachable line, which is worse than no line because it looks like compliance in a
diff. And pushing the detection down into `collect()` does not escape it: `collect()` also returns
`expected<CollectReport>`, so a typed error there discards the very `CollectReport` whose `warnings`
member the clause names. **The seam is the same one layer down.**

## 3. What I derived rather than routed (so the routed cell is as small as it can be)

Everything else about the caps is settled and stays in the plan: **all four** per-entry caps
(1024 nodes / 64 depth / 256 artifacts per node / 4096 total), **whole-entry refusal, never truncation**,
at-cap and cap+1 arms for each, and the requirement that the refusal **name both the entry and the cap**.
The producer side is ours; the parser side is m-1's; if m-1 ships a shared validator we call it and name
its receipt. **None of that needs authority. Exactly one thing does: WHICH SURFACE carries the
disclosure when the refusal fires.**

## 4. The three options, framed honestly — including what each COSTS

- **(A) Detect at COLLECT, warn, and omit the entry; `pack` SUCCEEDS.** The `CollectReport.warnings` line
  is real and observable exactly as `A12.4.1` describes. **Cost: it contradicts J's "pack fails typed and
  loud" outright** — the entry is dropped, disclosed but dropped, and J's paragraph exists specifically to
  forbid a producer that quietly declines to carry the operator's data. **I do not recommend it.**
- **(B) Detect at PACK; the TYPED ERROR IS the disclosure.** `BivError` already carries kind + path +
  detail, so "loud, typed, names both the cap and the offending entry" is fully satisfiable through the
  existing failure path, and J's calibration — *a producer refusal in the field means the CAP IS
  MIS-PRICED* — is served by an error the operator actually sees. **Cost: it needs m-2 to say, in one
  sentence, that `A12.4.1`'s cap case is discharged by the typed error rather than by a
  `CollectReport.warnings` line.** The clause as written names the warnings channel, and **a plan may not
  re-read a normative clause into a different carrier.** **This is my recommendation** — smallest change,
  no new API, both J requirements kept intact.
- **(C) Widen the result carrier** so `pack()` can return warnings alongside a failure. **Cost: an API
  change to a sealed-adjacent surface, touching every caller, to serve one warning class.** Correct in the
  abstract, disproportionate here, and squarely a design decision.

## 5. What I am NOT doing, stated so nobody has to wonder

I am not choosing (B) and building it. I am not letting my Implementer pick a carrier mid-build — **that
is the exact shape where an implementation quietly authors a normative decision**, and my seat has spent
this run insisting the reverse. I am not moving the caps into the adapters to make the warning fit, and I
am not adding a result member. **The plan's rev2 states the cell as OPEN, names both killing arms it will
need whichever way it lands (a fatal with NO disclosure must fail; a disclosure with NO fatal must fail),
and gates the token on the answer.**

## 6. Status

Rev2 of the PLAN — fixing my Implementer's R1 (the wave split activated transitive producer semantics on a
flat writer, which would emit a **semantically false manifest**: with `child_ids` transitive and no edge,
J's absence license reads C as a DIRECT child of R), R2 (`FX-A12-5` is one atomic two-variant oracle and
must not be split across dependency states) and R4 (A3's four checks bind the SAME reviewed head; a later
anchor-only commit cannot satisfy check 1) — files immediately after this and is addressed to my
Implementer. **The lineage cell you disposed at `154140` is closed and I am not re-opening it; this is a
new and different cell.** No product byte, no branch, no PR. **No `DISPATCH IMPL` token issues from my seat
until this cell is answered.** Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — J's producer-closure and calibration paragraphs re-read at pdc `e30f845`, `A12.4.1`'s covered list at `3929c9c`, and the seam measured at `0db8fdd` (`pack.cpp:469/:498/:553-559/:560+`, `adapter.hpp:281`); this relay + its INDEX row ride one explicit-path docs-lane commit whose SHA lands after filing
RELAY_LINT: per D-3.4 — per-file WITH freshness before filing; INDEX tail re-read; `--index`. Standing disclosed reds: INDEX line 222 (pre-existing sibling class, not mine) and the `--relay-root` cross-repo lineage red, NAMED-ERROR disposed at `154140` and carried disclosed per that disposition
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to this relay and `.relays/s4/INDEX.md`

CARRY LIST:
- `.relays/s4/s4-floor-impl/SITREP-PLANNER-SLICE-E-CAP-REFUSAL-CARRIER-SEAM-ROUTED-20260812-155122.md` → `s4.orchestrator-planner` → m-2 (the `A12.4.1` cap-case reading) and m-1 (parser-side symmetry) if you route it on
- J: a cap violation makes `pack` FAIL TYPED AND LOUD naming cap + entry; `A12.4.1`: that same refused entry MUST produce a `CollectReport.warnings` line. **At `0db8fdd` the fatal DESTROYS the carrier** (`cleanup_error` discards `report`; warnings are drained at `:553-559` BEFORE the loop that can fail; `collect()` is `expected<CollectReport>`, so the seam repeats one layer down)
- everything else about the caps is DERIVED and stays in the plan (all four caps, whole-entry refusal never truncation, at-cap/+1 arms, name entry AND cap, producer ours / parser m-1's)
- options: **(A)** collect-side warn-and-omit — contradicts J's loud typed fail, NOT recommended; **(B)** pack-side typed error IS the disclosure — RECOMMENDED, needs one sentence from m-2 that `A12.4.1`'s cap case is discharged by the error, since a plan may not re-read a normative clause into a different carrier; **(C)** widen the result carrier — an API change to serve one warning class, disproportionate and a design decision
- both killing arms are required whichever way it lands: a fatal with NO disclosure FAILS; a disclosure with NO fatal FAILS
- rev2 PLAN (R1 false-manifest wave split / R2 key-5 atomicity / R4 A3 same-head ceremony) files next to my Implementer; **no `DISPATCH IMPL` token until this cell is answered**; release hold ABSOLUTE
