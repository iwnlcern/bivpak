## PROCEED-TO-PLAN (slice E RELEASED) — the last DESIGN gate is passed: ADDENDUM-12 is VP-APPROVED at `154cd87e` (commit `3929c9c`), consuming J's lock `m1-addendum-J-94b6440c…`, and I verified both pins + the J-consumption at the bytes. **Slice E is released to its PLAN gate and to NOTHING beyond it — this authorizes no implementation, product-code write, schema act, merge, seal, publication, deployment or release, and is VOID IF EITHER LOCKED DESIGN CHANGES.** s4-floor.planner: emit the gated `PHASE: PLAN` for the coupled slice, addressing your plan-review request to your Implementer, with `DESIGN_LOCK_ID: m2-addendum12-154cd87e-lock-20260812` (CONSUMED_CONTRACT `m1-addendum-J-94b6440c-lock-20260812`) and `PARENT_DISPATCH_ID` pointing to the approving DESIGN-REVIEW `145249`. Scope, boundary, and the binding constraints are below — build against them, do not rediscover them. Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ROLE: Orchestrator Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-slice-e-proceed-to-plan
PARENT_DISPATCH_ID: s4-slice-e-design-m-2
IN_REPLY_TO: ../../../../pdc/master/relays/s4-slice-e-design-m-2/PLAN-ORCHESTRATOR-PLANNER-ADDENDUM12-APPROVED-SLICE-E-RELEASED-TO-PLAN-D58-OWNED-20260812-145954.md
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no NEW operator gate to reach PLAN — the VP's exact-pin Addendum-12 design gate PASSED (consuming J). Slice E's PLAN gate is your Implementer's plan review; implementation, merge, seal and release each retain their own gate. The release hold is ABSOLUTE.
DESIGN_DOC_ID: m2-addendum-12-transitive-collect-mono-gate-20260812
DESIGN_RECORD_KIND: design-doc
DESIGN_REVIEW_VERDICT: approve
DESIGN_LOCK_ID: m2-addendum12-154cd87e-lock-20260812
TARGET_DESIGN_SHA256: 154cd87ebdc0619cdf3a7172da9b46d5753888da68f03a10ed6c18c481ff4c77
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812
FROM: s4.orchestrator-planner
TO: s4-floor.planner
CC: operator, s4.orchestrator-reviewer, s4-floor.implementer, master.orchestrator-planner, m-2.planner
SUBJECT: PROCEED-TO-PLAN — slice E released at addendum-12 154cd87e (consuming J 94b6440c); emit the gated coupled PLAN; scope + R-4.20/MONO/producer-closure constraints + fence-2 dependency carried; R-4.24 is m-3/m-1's not yours

## 1. The design of record (verified at my seat, bind these bytes)

```text
addendum-12  commit 3929c9c944ba2bdc576cbe3ee2ceceae8a0cfe8b  SHA-256 154cd87e…  VP APPROVE (145249)
             CONSUMED_CONTRACT m1-addendum-J-94b6440c-lock-20260812  (SHA 94b6440c…) — verified in the file
J (sealed)   commit e30f845                                    SHA-256 94b6440c…  VP APPROVE (052536)
```

Both pins re-derived at my seat. This is sequencing only — I do NOT carry the gated lock; your `PHASE: PLAN`
relay emits it (`FROM: s4-floor.planner`, `DESIGN_LOCK_ID` above, `PARENT_DISPATCH_ID` → `145249`).

## 2. Scope slice E OWNS — the s4-side coupled slice (from the reconciled audit, 145820)

One coupled slice, not separable:
1. **Collector recursion fix** — `codex.cpp:452 session_for` + the `1294+` grouping/emit so transitive
   descendants (`R←P←C`) are carried, not dropped; `children_by_parent[P]` consumed.
2. **Both identity gates made ROOT-MAPPED** — writer `codex/install.cpp` and staged reader `codex.cpp:700-818`,
   so installed-root and installed-immediate-parent are distinct identities (kills the whole-pack abort on a
   three-level leaf).
3. **Killing tests** — a RED `R←P←C` collector case at `0db8fdd`; write/read cases where mapped root ≠ mapped
   immediate parent; a chain-drop warning producer over the EXISTING transport (`pack.cpp:334/558` → cli).
4. **A disposable-store CLI `biv pack`/`biv open` E2E** with a reference-resolution read assertion, reusing
   R-4.8's landed isolation (`ScopedPackDiscoveryEnv` + `require_store_roots_under`) and `test_cli.cpp`'s
   actual-binary harness; NEVER touch live `~/.claude`/`~/.codex`; NO credential collection; state covered axes
   (both layouts, bare-hex majority) and non-coverage.

## 3. The manifest schema half is m-1's, HARD-OUT for you — name it as a dependency, do not write it

J changes `agent_sessions[].children[]` (gains the child→parent edge; meaning direct children → TRANSITIVE
DESCENDANTS). That schema change lives in `manifest.hpp`/`manifest.cpp` — **`manifest.cpp` is fence-2, HARD-OUT
for this seat.** The manifest schema IMPLEMENTATION is m-1's format-engine work, not yours. **Your PLAN scopes
the s4-side (codex adapter + collector + gates + E2E, plus any `core/open`/`core/pack` READER changes that are
NOT fence-2) and NAMES the m-1 manifest-schema dependency + the co-sequencing** (the adapter cannot emit
transitive descendants before the manifest carries them). Route any need to touch `manifest.cpp` UP to me — do
not plan to author it. Your audit's minimum-surface map already flagged this conditional/route-UP branch; it is
now the confirmed path.

## 4. Binding constraints — build against these (from J + addendum-12, verified)

- **R-4.20 — well-formedness, not truth.** The declared parent edge may **only ever produce REFUSALS, never
  GRANTS**: no destination path, host write, or consent decision derives from it. Containment rests on
  **locally-minted destinations** — I opened the file per `D-5.8`: the real mint sites are
  `codex/install.cpp:122-143 uuidv7_from_ms`, `:430` and `:455 mint_rollout_name()`, writes `:483-489`
  (NOT `:507-513`, which calls `derive_install_pair_set` and mints nothing — do not cite it as minting proof).
  Image-derived identifiers are lookup/rewrite keys only, never destination identities or path components.
- **MONO direction `A(E) ⊆ A(0)`** (edge-consistency is a conjunct on ACCEPT — an edge can remove an
  acceptance, never create one; `R-4.26` carries the durable statement). The reversed form is rejected history.
- **Producer closure** (pack refuses loudly rather than emit a tree its own parser would reject);
  **per-entry caps with typed refusal, never silent truncation**; **M4-CG-0** duplicate-known-key refusal
  (`at_key` first-wins).

## 5. Correction I owe — R-4.24 is NOT slice E's

My `061048` receipt registered R-4.24 (pre-consent prompt says N, install produces N−1) as "slice E owns." **That
was my over-attribution.** Master's addendum-12 relay is explicit: **R-4.24 is owned by m-3 (surface) with m-1
(count source), is independent, and is NOT gated by or cleared by addendum-12.** It is adjacent to your
count/consent surface, so coordinate/stay aware — but you do NOT own its fix and must not gate on it.

## 6. Route to build

Emit the gated `PHASE: PLAN` → your Implementer's plan review (the plan gate) → on approve you issue exactly
one `DISPATCH-IMPL` to your Implementer, provided the locked plan stays in this scope/boundary and hits no
hard trigger; deviations re-engage me. Then build → review-fold → merge-gate (four-condition bar, operator
token). Cut against `0db8fdd`; state the cut-point blast radius against `origin/main` per D-5.5(a). Act against
no design bytes but `154cd87e`/`94b6440c`. Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — read-only verification (addendum-12 design @ 3929c9c == 154cd87e + CONSUMED_CONTRACT J 94b6440c; codex/install.cpp mint sites :122/:430/:455 and the mints-nothing :507-513 at 0db8fdd) + this PROCEED-TO-PLAN. This relay + its INDEX row ride one explicit-path docs-lane commit whose SHA lands after filing.
RELAY_LINT: per D-3.4 — per-file WITH freshness at this seat before filing; `.relays/s4/INDEX.md` tail re-read for sibling rows before appending; `--index`; commit GATED on both exits, path-scoped add AND commit. Other index reds are the pre-existing sibling classes — none mine.
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to this relay and `.relays/s4/INDEX.md`.

CARRY LIST (D-8.5):
- `.relays/s4/s4-floor-impl/PROCEED-TO-PLAN-ORCHESTRATOR-PLANNER-SLICE-E-RELEASED-R418-COUPLED-DESIGN-LOCKED-20260812-150245.md` → `s4-floor.planner`, `s4-floor.implementer`
- SLICE E RELEASED to its PLAN gate: addendum-12 VP-APPROVED 154cd87e (commit 3929c9c) consuming J 94b6440c — both pins verified at my seat. PLAN only; no impl/schema/merge/seal/release; void if either locked design changes
- emit the gated PHASE: PLAN (DESIGN_LOCK_ID m2-addendum12-154cd87e, CONSUMED_CONTRACT J, PARENT → 145249); plan-review to your Implementer is the plan gate; then one DISPATCH-IMPL
- OWNS: collector recursion (session_for/1294+) + both root-mapped identity gates + killing tests (RED R←P←C, root≠parent, chain-drop warning on the existing pack→cli transport) + disposable-store CLI pack/open E2E (reuse ScopedPackDiscoveryEnv/test_cli; no live store; no creds; state coverage)
- manifest schema half (children[]→transitive descendants + parent edge in manifest.hpp/cpp) is m-1's; manifest.cpp is fence-2 HARD-OUT — scope the s4-side, NAME the m-1 dependency + co-sequencing, route manifest.cpp UP
- constraints: R-4.20 edge-only-refuses (mint sites :122/:430/:455 not :507-513); MONO A(E)⊆A(0); producer closure; typed refusal never silent truncation; M4-CG-0
- R-4.24 is m-3(surface)/m-1(count) owned, independent, NOT yours (I own the earlier mis-attribution); release hold ABSOLUTE
