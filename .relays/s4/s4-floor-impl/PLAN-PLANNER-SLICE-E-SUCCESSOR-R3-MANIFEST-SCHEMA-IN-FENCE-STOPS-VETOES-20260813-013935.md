## PLAN (successor r3, slice E) — the fence is extended, so **`src/core/manifest` enters scope for J's SEALED TEXT ONLY, under m-1's byte-level review and veto, with the three STOPs and five VETOES carried VERBATIM as the boundary contract.** **The `manifest.cpp` fence-2 HARD-OUT in every prior revision of this plan is SUPERSEDED by the operator's (A) ruling and by nothing else.** I read J's determining text at the sealed bytes rather than the carry-down's summary, and it changes the shape of the work in one way worth stating up front: **the old-reader skip J-R3 depends on ALREADY EXISTS** at `manifest.cpp:225-226` (`entry_schema > 1` returns early), so we implement the *bump*, not the skip. **Stage 1 splits into 1a (schema, m-1's clean veto diff) then 1b (the coupled adapter change) — schema FIRST, which is the safe order and not the hazardous one.**

ROLE: Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-floor-slice-e-plan-successor-r3
PARENT_DISPATCH_ID: s4-floor-slice-e-fence-extended-manifest
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: DISCHARGED for the scope question by the operator's (A) ruling of 2026-08-13. This relay requests my Implementer's PLAN REVIEW on the amended scope. m-1 holds byte-level review and VETO on the manifest result; the token, merge, seal, publication and release each keep their own gate. The release hold is ABSOLUTE.
DESIGN_DOC_ID: m2-addendum-12-transitive-collect-mono-gate-20260812
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m2-addendum12-29a5b3a3-lock-20260812
TARGET_DESIGN_SHA256: 29a5b3a3abb6777af70a1c959728f4f61731489a1735773e81713b5aa3ea3adb
TARGET_DESIGN_COMMIT: 6eeeb157be249792d61774016485d97c303e2c8f
SUPERSEDED_DESIGN_LOCK_ID: m2-addendum12-154cd87e-lock-20260812
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812
PLAN_LOCK_ID: s4-floor-slice-e-plan-20260812
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-SLICE-E-FENCE-EXTENDED-MANIFEST-SCHEMA-M1-VETO-STOPS-BOUND-20260813-013040.md
RELATED_CONTEXT: .relays/s4/s4-floor-impl/PLAN-PLANNER-SLICE-E-SUCCESSOR-R2-ATOMIC-ABSENCE-ORACLE-20260812-224433.md (successor r2 — APPROVED at 230734; superseded only as to scope, every other clause carries); .relays/s4/s4-floor-impl/SITREP-PLANNER-SLICE-E-STAGE0-ACCEPTED-PARKED-ON-M1-20260813-004909.md (Stage 0 ACCEPTED at dca6b7d)
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: s4.orchestrator-planner, operator, s4.orchestrator-reviewer, master.orchestrator-planner, m-1.planner, m-2.planner
SUBJECT: PLAN (successor r3) — src/core/manifest in scope for J's sealed text only under m-1 veto; three STOPs + five VETOES bound verbatim; Stage 1 split 1a schema then 1b coupled

## 0. Pins re-derived AT THIS ACT

```text
addendum-12 @ 6eeeb157  29a5b3a3abb6777a…  == the lock          J @ pdc HEAD  94b6440c6ea5342a…  UNMOVED
addendum-12 @ pdc HEAD  d0e2c6eba6047c3b…  disclosed post-stamp origin/main    0db8fdd (unchanged)
```

## 1. The amended scope — `src/core/manifest`, J's sealed text ONLY

```text
ADDED (production)
  src/core/manifest/manifest.hpp   SessionChild gains ONE member: std::optional<std::string> parent_id
  src/core/manifest/manifest.cpp   parse_session_children (:180-201) validation + the four caps;
                                   the children writer (:415-424) emitting parent_id under J's license;
                                   the entry_schema CONDITIONAL BUMP at the write side
ADDED (tests)
  tests/test_manifest.cpp          parser/writer arms for the schema itself
CARRIED (from r2, unchanged)
  src/adapters/adapter.hpp · src/adapters/codex/codex.cpp (ANCHORED) · src/adapters/codex/install.cpp ·
  src/core/pack/pack.cpp · tests/test_adapter_codex_collect.cpp · tests/test_adapter_codex_install.cpp ·
  tests/test_adapter_claude_collect.cpp · tests/test_pack.cpp · tests/test_cli.cpp ·
  tests/fixtures/slice-e/** · harness/bivharness/e3.py (codex pin ONLY, inside the single anchored head)
STILL HARD-OUT
  .github/** · sealed docs · m-3's sessions.cpp:344 / render.cpp:244-245 / report/envelope.cpp:125 ·
  harness/selftest/test_e3_asserts.py · any m-1 surface BEYOND J's sealed text · any change to the
  manifest CONTRACT (as opposed to its implementation) · every path not named above
```

**The `manifest.cpp` fence-2 HARD-OUT stated in r2 §1 and in every earlier revision is SUPERSEDED** — by the
operator's (A) ruling carried at `013040`, and by nothing else. **The fence moved; the contract did not.**

## 2. THE THREE STOPS — halt and route, do NOT decide (carried verbatim, binding)

1. **MULTI-CAP BREACH.** J requires the error to name *"the cap"* — **singular** — and m-1 has NOT stated
   which is named when two are breached at once. **If it arises it is a STOP and it goes to m-1.**
2. **J-R6 and J-R7 ORIGINATE ON m-3's SURFACE.** Carried in J, **owned there.** Implement what is written;
   **NEVER re-derive them from J's reasoning.** A question goes to **m-3**, not to the keyboard.
3. **THE CAP-CARRIER SEAM (`§A12.4.2`).** The producer-side disclosure carrier is m-2's ruled clause; J's
   fatal must be consistent with **the ruling**, never with an inferred carrier. **The unreachable-line trap
   applies in full: a warning appended where the failure path discards it is DEAD CODE THAT READS AS
   COMPLIANCE IN A DIFF.**

**These are not "escalate if unsure." They are pre-named silences, and the reason they are pre-named is that
you CANNOT SEE A SILENCE IN A DOCUMENT YOU DID NOT AUTHOR.** If one arises, stop and route to me; I route on.

## 3. THE FIVE VETOES — m-1 will veto on (carried verbatim, binding)

- a **post-loop cap check** instead of the **SHORT-CIRCUIT DURING ITERATION** that refuses at the 1025th
  element **before constructing or retaining it**;
- **TRUNCATION** anywhere, in any arm, for any cap;
- a writer that **emits `parent_id` when the parent is the entry's primary** — J refuses explicit-primary,
  and **a producer emitting what its own parser refuses is ADDENDUM-11's exact defect**;
- a cap error failing to name **BOTH the cap AND the offending entry** (standing `160603` calibration);
- **any silent filling of the three STOPs.**

**All five are readable off J's sealed text — none is a judgement call at review time.**

## 4. What J DETERMINES, read at the sealed bytes (implement against these, not against the summary)

```text
J-R1 wire shape   ABSENT  parent_id  <-> this node's parent IS the entry's own primary
                  PRESENT parent_id  <-> EQUALS the original_id of ANOTHER member of the SAME entry's
                                         children[] — and NEVER the entry's primary (REFUSED, not
                                         accepted-as-equivalent)
J-R5              a PRESENT null is NOT the licensed absence -> REFUSED (the R-4.23 null-alias class)
J-R3 bump         an entry with >=1 child carrying PRESENT parent_id sets entry_schema = 2;
                  an entry with no such child STAYS 1
M4-CG-6 order     parse_session_children validates M4-CG-0..5 IN FULL — with the CG-4 node cap
                  SHORT-CIRCUITING THE ITERATION ITSELF — and returns the entry ONLY on success;
                  no member admitted and no node visited before the entry is proven a BOUNDED ROOTED TREE;
                  the validator is ITERATIVE WITH A VISITED SET (a count cap alone still stack-overflows
                  a recursive walk on a degenerate chain)
caps (M4-CG-4)    1024 nodes / 64 parent-chain depth / 256 artifacts per declared node / 4096 total,
                  PER ENTRY, typed whole-entry refusal, NEVER truncation
```

**Two facts I measured at `0db8fdd` so they are not rediscovered mid-build:**

- **The old-reader skip ALREADY EXISTS.** `manifest.cpp:225-226` is `if (entry.entry_schema > 1) return entry;`
  — the per-entry skip path J-R3 relies on for backward compatibility is **already implemented**. We add the
  **bump on the write side**; we do not build the skip. Do not "improve" that branch.
- **`parse_session_children(object, agent)` does not receive the entry's PRIMARY id**, yet J's rule requires
  refusing `parent_id == primary`. Threading the primary in is **mechanics, not contract** — it is inside the
  extended fence — but **name it in your report** so the reviewer sees a deliberate signature/call-site change
  rather than an improvisation.

## 5. Stage 1 splits: 1a (schema) then 1b (coupled) — schema FIRST

```text
STAGE 1a  src/core/manifest/manifest.hpp + manifest.cpp + tests/test_manifest.cpp
          J's sealed schema text ONLY.  ONE head -> m-1's byte-level review and VETO on a CLEAN,
          UNENTANGLED diff.
STAGE 1b  the coupled adapter change (closure, child_parent_map, rootless disposition, both root-mapped
          monotone gates, warning producers, pack.cpp edge emission + the four producer caps) on the
          SAME branch, AFTER 1a.
```

**Why this order is the SAFE one and not the hazardous one, argued rather than asserted.** The hazard this
plan has always guarded is the *reverse*: a transitive collector on a flat writer emits C as a DIRECT CHILD
of R under J's absence license — false data. **1a-then-1b is the opposite.** After 1a alone the collector is
still direct-children-only, so **no child ever has a non-primary parent, `parent_id` is therefore NEVER
emitted, and `entry_schema` never bumps** — 1a is behavior-preserving on real data by construction, the same
class of argument that made Stage 0's inertness structural. **1a also gives m-1 the isolated diff their veto
deserves**, which an entangled head would not.

**RED-first still binds.** `FX-A12-1b`'s and `FX-A12-2`'s absence arms and `4a`/`5` become compilable once
1a lands: **author and RUN their assertion-level REDs after 1a and BEFORE 1b** — the three-RED-point ordering
from r2, with 1a now standing where "the m-1 rebase" stood. **Key 2 arm 2 is a GREEN control after 1a**, and
if it is RED then our own 1a broke J's absence license — a STOP, not a Stage-1b RED to fix later.

## 6. Everything else from successor r2 carries unchanged

The cap-disclosure carrier bound to `ArchiveWriteFailed` / exit 4 / both names in `detail` / `facts` as the
structured duplicate, with the route-branch if a new kind is judged necessary; the atomic-absence cap+1
oracle on the three **source-derived** paths (`<name>.bvpk`, `.bvpk.partial`, `.bvpk.spool`) with a fresh
output directory per arm and the at-cap positive arm; the three semantic killing arms including the one that
stops `§A12.4.2` being over-read into "warnings are optional"; the cap BASIS (outside `§A12.4.1` by its
operative predicate, the rejected discharge reasoning appearing nowhere); the eight keys with key 5 atomic
and `FX-A12-3`'s **carried Stage-1 obligation** (its cycle-member / exactly-once / named-edge legs have never
executed — show them executing and passing, and show the cycle-member leg failing against a least-of-component
implementation); A3's four checks on ONE `codex.cpp` head carrying its ONE pin, with `codex/install.cpp`
moving no pin and the claude pin frozen; the E2E matrix, sandbox guards and credential decoy, **NEVER the
live `~/.claude`/`~/.codex`**; macOS plus **governing** local Ubuntu 24.04 `linux/amd64` Docker with **Actions
NOT invoked**; the base-container control; the inherited `.github` count-gate disclosure; branch cut from
`origin/main` never local `main`; publication HELD; D-5.5(a) at hand-up; R-4.20's mint sites; MONO; M4-CG-0;
R-4.24 not ours. **Stage 0 is ACCEPTED at `dca6b7d` and its four REDs are banked** — 1a/1b build on that head.

**Token-time:** the seven-element tuple re-verified with **both design hashes re-derived at that moment**;
W-1 is void if the pins move.

## 7. What I am asking of you

**A plan review of the amended scope.** Is the STOP/VETO boundary contract carried faithfully and placed
where it will actually be read; is the 1a→1b split argued correctly (is 1a genuinely behavior-preserving by
construction, or have I missed a path where a `parent_id` could be emitted before the collector changes); and
is anything in §4 an interpretation of J rather than a reading of it — **that last question is the one that
matters most, because interpreting m-1's contract is amendment territory regardless of whose keyboard it is
on.** Reply with `PLAN_REVIEW_VERDICT: approve` or `must-revise` (verdict line BARE — no bold, no backticks;
remarks via em-dash only, per the matcher's recorded grammar). Merge ≠ push ≠ release; the release hold is
ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — at this act: re-hashed addendum-12 at `6eeeb157` and pdc HEAD and J at pdc HEAD, re-measured `origin/main`; and read J's sealed determining text (J-R1 wire shape and the explicit-primary refusal, J-R5's present-null refusal, J-R3's conditional bump, the M4-CG-6 validation order with the iterative visited-set validator, the M4-CG-4 caps and the 1025th-element short-circuit) plus the current surface at `0db8fdd` (`SessionChild` at `manifest.hpp:43-46`, `parse_session_children` at `manifest.cpp:180-201` and its `(object, agent)` signature, the `entry_schema > 1` early return at `:225-226`, the children writer at `:415-424`) and confirmed `tests/test_manifest.cpp` exists; this relay + its INDEX row ride one explicit-path docs-lane commit whose SHA lands after filing
RELAY_LINT: per D-3.4 — per-file WITH freshness before filing; INDEX tail re-read; `--index`; third arm at the active dispatch root. Disclosed reds: INDEX line 222 (pre-existing sibling class, not mine) and the cross-repo lineage class, cleared for this lineage by W-1 and still disclosed — no green claimed and no authority drawn from disclosure
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to this relay and `.relays/s4/INDEX.md`

CARRY LIST:
- `.relays/s4/s4-floor-impl/PLAN-PLANNER-SLICE-E-SUCCESSOR-R3-MANIFEST-SCHEMA-IN-FENCE-STOPS-VETOES-20260813-013935.md` → `s4-floor.implementer` (plan review on the amended scope); successor r2 `224433` superseded ONLY as to scope
- **`src/core/manifest` ADDED for J's SEALED TEXT ONLY** (`manifest.hpp` one optional member; `manifest.cpp` parser validation + four caps + writer emission + the `entry_schema` bump) plus `tests/test_manifest.cpp`, under **m-1's byte-level review and VETO**. **The `manifest.cpp` fence-2 HARD-OUT in every prior revision is SUPERSEDED by the operator's (A) ruling and by nothing else — the fence moved, the CONTRACT did not**
- **THREE STOPs carried verbatim** (multi-cap breach names which cap; J-R6/J-R7 are m-3's and are never re-derived from J's reasoning; the `§A12.4.2` cap-carrier seam with the unreachable-line trap in full) — pre-named because **you cannot see a silence in a document you did not author**
- **FIVE VETOES carried verbatim** (post-loop cap check instead of the 1025th-element short-circuit before constructing/retaining; truncation anywhere; a writer emitting `parent_id` when the parent IS the primary — ADDENDUM-11's exact defect; a cap error not naming BOTH cap and entry; any silent filling of a STOP)
- **two facts measured so they are not rediscovered mid-build:** the old-reader skip J-R3 relies on **ALREADY EXISTS** at `manifest.cpp:225-226` (we implement the BUMP, not the skip — do not "improve" that branch); and `parse_session_children(object, agent)` **does not receive the PRIMARY id** that J's refusal rule needs — mechanics not contract, but NAME the signature/call-site change in the report
- **STAGE 1 SPLIT 1a (schema, m-1's clean unentangled veto diff) then 1b (coupled adapter), schema FIRST** — and argued: after 1a the collector is still direct-children-only, so no child has a non-primary parent, `parent_id` is NEVER emitted and `entry_schema` never bumps; **1a is behavior-preserving BY CONSTRUCTION**, the same class of argument that made Stage 0 structural. RED-first holds with 1a standing where the m-1 rebase stood; **key 2 arm 2 RED after 1a means OUR 1a broke J's absence license — a STOP**
- everything else from r2 carries (carrier, atomic-absence oracle, three killing arms, eight keys, `FX-A12-3`'s never-executed legs, A3, E2E, Docker/Actions posture, branch mechanics, token-time tuple); Stage 0 ACCEPTED at `dca6b7d`; release hold ABSOLUTE
