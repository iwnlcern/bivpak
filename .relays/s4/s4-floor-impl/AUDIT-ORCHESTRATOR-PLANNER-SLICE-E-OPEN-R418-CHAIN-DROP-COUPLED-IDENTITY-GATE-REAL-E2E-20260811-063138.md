## AUDIT dispatch (slice E OPEN) — master opened slice E and I independently VERIFIED its rescope at the bytes at `0db8fdd`: R-4.15 is **LANDED, not owed** (`child_alias_ids` gone — 0 hits; `claude_code/install.cpp:722` = `session.child_ids.push_back({child.original_id, child.original_id})`, the identity map), and codex is **genuinely clean** (`codex/install.cpp:457` mints a rollout name that IS the destination filename, so reference and file move together — R-4.15's second fork, not the claude mismatch). So slice E does NOT own R-4.15. **This is a READ-ONLY AUDIT to scope what slice E DOES own against `0db8fdd`: (1) R-4.18 — the three-level codex chain drop; (2) the identity-gate coupling that makes the drop unfixable alone; (3) a REAL end-user E2E of the restore round trip.** Map the surface, the collisions, and the corpus basis — no code, no PR, no design decisions. R-4.18's DESIGN half is m-2's (dispatched in parallel); you are NOT blocked on it to audit. `manifest.cpp` fence-2 and the `agent_sessions[]` joint-lock stay HARD-OUT for this seat — if scoping shows the work needs them, name it and it routes UP. Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ROLE: Orchestrator Planner
PHASE: AUDIT
AUTHORITY: read-only
DISPATCH_ID: s4-slice-e-audit
PARENT_DISPATCH_ID: s4-slice-e-open
IN_REPLY_TO: ../../../../pdc/master/relays/s4-build-standup/PLAN-ORCHESTRATOR-PLANNER-R415-REPAIR-CONFIRMED-LANDED-MY-RECEIPT-WAS-STALE-SLICE-E-SCOPED-TO-R418-20260811-062724.md
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no — a read-only audit dispatch inside Step 4's existing operator gate; slice E sits within it. A new operator gate is needed only if the design later requires a sealed-design-of-record change beyond a scoped addendum, or scope reaches outside Step 4. The release hold is ABSOLUTE.
DESIGN_LOCK_ID: pending — R-4.18 design predicate is m-2's, in flight (master 062353); this audit precedes and informs it
DESIGN_RECORD_KIND: design-doc
FROM: s4.orchestrator-planner
TO: s4-floor.planner, s4-floor.implementer
CC: operator, s4.orchestrator-reviewer, master.orchestrator-planner, m-2.planner
SUBJECT: AUDIT — slice E open at 0db8fdd: R-4.18 chain drop + coupled identity gate + a real restore E2E; R-4.15 confirmed LANDED (not owned); read-only scoping, m-2 design in parallel

## 1. The rescope, independently confirmed at my seat (so no one re-opens R-4.15)

```text
at 0db8fdd:
  git grep -c child_alias_ids -- src tests                 -> 0 files            (minting machinery GONE)
  src/adapters/claude_code/install.cpp:722                 -> session.child_ids.push_back(
                                                               {child.original_id, child.original_id})   (option (a))
  src/adapters/codex/install.cpp:457                       -> rollouts.emplace(child_identity, mint_rollout_name());
                                                               child_ids.push_back({child.original_id, installed_child})
                                                             ^ minted name IS the destination; ref+file move together
```

R-4.15's functional repair landed in the C/B2 merge. Master's `061312` receipt named it still-owed from the
residual register; master caught and corrected that (`D-6`: a true-then line carried as now) and is fixing the
`RESIDUALS.md` R-4.15 row itself. **I confirm the correction at the bytes.** Do NOT re-open R-4.15, and do not
let its stale residual row route work here. The one survivor is m-2's, not ours: under (a) `IdMapEntry.children`
is an identity map (shape unchanged, semantics changed) and whether `children` is still emitted is the
install-result-shape owner's contract question.

## 2. What slice E OWNS — audit these three against 0db8fdd

**(1) R-4.18 — the three-level codex chain drop.** `src/adapters/codex/codex.cpp:452` `session_for(candidate,
children)` builds `child_ids` from the DIRECT `children` only (`:457 child_ids.push_back(child.id)`, no
recursion), and the emit loop skips children — so for `R←P←C` the grandchild's rollout is never packed and
there is NO warning channel: a silent loss. This is the X-1 your pair surfaced during C/B2. Master's basis to
confirm, not inherit: **145 self / 635 two-level / 7 three-level of 940** rollouts. Audit deliverable: the real
recursion behavior, the emit/skip path, and whether any warning channel exists — measured, not read.

**(2) The coupling — why it was never a bounded fold.** The landed identity gates are written to exactly ONE
level (`installed_thread_id` is the immediate parent on both sides; there is no mapped-ROOT concept). **Fix the
drop alone and every three-level leaf raises `staged_identity_mismatch` — a silent loss becomes a WHOLE-PACK
ABORT.** So the chain drop, the manifest child cardinality, and a root-mapped identity gate move together or
not at all. Audit deliverable: locate the identity gate(s), confirm the one-level assumption, and map exactly
which files the coupled change would touch — flagging any that are hard-OUT (see §4).

**(3) A REAL end-user E2E of the restore round trip.** The acceptance criterion today is discharged by a
FIXTURE test (`tests/test_pack.cpp:1748`, "B2 standing Claude stage pack open keeps parent references equal
to …") — byte-verified and passing, but NOT an end-user E2E. The operator's requirement, in their words:
sessions "installed and working without recollection issues from having referenced files with the wrong path
causing the agent to seek a few extra turns." Audit deliverable: scope an E2E that packs a genuine
subagent-bearing session → opens into a clean target → shows the restored parent's references resolving to
files that exist and the harness reading them. Two non-negotiable constraints, both from standing rules:
- **(i) NEVER read or mutate the operator's live `~/.claude` / `~/.codex`.** A prior global check already found
  pack tests touching real `~/.codex`. Product DNA is read-freely / **write-only-with-consent**, and **NO
  credential collection**. Build the source store as a fixture tree or an explicit disposable copy.
- **(ii) It is an acceptance instrument — it states what it covers and what it does not.** One shape is not a
  corpus claim; the distribution is **309 bare-hex + 269 slug-hex of 578** (bare-hex the majority), and both
  LAYOUTS (flat + nested `subagents/<wf>/`) must be represented or the omission stated.

## 3. What slice E does NOT own

**R-4.15 (landed).** Also unchanged and non-gating this audit: the 1702-stem corpus provenance (still owed;
cite no absolute figure as a live-store measurement until it lands); `R-4.19`'s unpinned control container;
`R-3.40` item 13 (glibc ENOEXEC fall-back to `/bin/sh` at `test_probe.cpp:273` — the test's fix, take it if
you touch that file); `packer_home` already gated at `RESIDUALS` R-4.8.

## 4. Boundaries, dependency, and mechanics

- **HARD-OUT for this seat:** `.github`, `manifest.cpp` fence-2, and sealed-doc amendments. The manifest child
  cardinality sits on the `agent_sessions[]` joint-lock (m-1's seam). If the audit shows the coupled fix needs
  a `manifest.cpp` fence-2 change, **name it and route UP — do not plan to self-author it.**
- **Design dependency:** R-4.18's design half is m-2's, dispatched in parallel (master `062353`): recursion
  semantics, manifest child cardinality, whether a root-mapped identity concept enters the contract, m-1
  consulted if cardinality moves. You are NOT blocked on it to audit — the drop, the corpus, and the E2E are
  measurable/buildable today. Plan the fold against the design when it lands.
- **Against `0db8fdd`.** Any future candidate re-bases on it and states its cut-point blast radius against
  `origin/main` per D-5.5(a) (the 4-vs-217 on C/B2 was worth the re-stack).
- **This is AUDIT — read-only.** Address the paired audit back to me (`TO: s4.orchestrator-planner`); I
  reconcile the two, then the DESIGN phase folds m-2's predicate, then PLAN, then build. No code, no PR, no
  design decisions in the audit.

ACTIONS_GIT_REF: no product/test edits at this seat — read-only verification of master's rescope at 0db8fdd (child_alias_ids 0 hits; claude install.cpp:722 identity; codex install.cpp:457 mint-is-destination; codex.cpp:452 session_for non-recursion; agent_sessions[] schema locations) and this AUDIT dispatch. This relay + its INDEX row ride one explicit-path docs-lane commit whose SHA lands after filing.
RELAY_LINT: per D-3.4 — per-file WITH freshness at this seat before filing; `.relays/s4/INDEX.md` tail re-read for sibling rows before appending; `--index`; commit GATED on both exits, path-scoped add AND commit. Other index reds are the pre-existing sibling classes — none mine.
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to this relay and `.relays/s4/INDEX.md`.

CARRY LIST (D-8.5):
- `.relays/s4/s4-floor-impl/AUDIT-ORCHESTRATOR-PLANNER-SLICE-E-OPEN-R418-CHAIN-DROP-COUPLED-IDENTITY-GATE-REAL-E2E-20260811-063138.md` → `s4-floor.planner`, `s4-floor.implementer`
- SLICE E OPEN at 0db8fdd (read-only audit). R-4.15 CONFIRMED LANDED at my seat (child_alias_ids gone; install.cpp:722 identity; codex clean) — NOT owned, do not re-open
- OWNS: (1) R-4.18 three-level codex chain drop (codex.cpp:452 session_for non-recursive, emit skips children, no warning; basis 145/635/7 of 940); (2) the identity-gate coupling (one-level installed_thread_id; fixing the drop alone turns silent loss into a staged_identity_mismatch WHOLE-PACK ABORT; drop + manifest cardinality + root-mapped gate move together); (3) a REAL end-user E2E restore round trip
- E2E constraints: (i) NEVER touch live ~/.claude/~/.codex — fixture tree / disposable copy, write-only-with-consent, NO credential collection; (ii) acceptance instrument states coverage (309 bare-hex + 269 slug-hex of 578, both layouts)
- HARD-OUT: .github, manifest.cpp fence-2, sealed-doc amendments; manifest child cardinality = m-1 agent_sessions[] joint-lock, route UP if the fix needs it. Design half is m-2's (062353), not blocking the audit. Address the paired audit back to me; merge ≠ push ≠ release; release hold ABSOLUTE
