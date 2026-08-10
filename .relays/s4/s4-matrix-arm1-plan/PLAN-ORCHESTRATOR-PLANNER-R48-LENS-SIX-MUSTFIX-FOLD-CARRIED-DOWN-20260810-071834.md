## DISPATCH (fold) — the R-4.8 human lenses returned at `2341667`: Lens A MATCHES-INTENT on all three (security core sound), Lens B one SOUND + two FINDINGS I RE-VERIFIED at the bytes at this seat (B-3.3 codex `discover()` appends `env.home/.codex` UNCONDITIONALLY — codex.cpp:762-776 no early return — and the pack tests pin only CLAUDE_CONFIG_DIR/CODEX_HOME never HOME, so pack reads the operator's REAL ~/.codex; B-2.1 `/Users/packer` appears in ZERO fixture bytes, so the byte-identity receipts are VACUOUS for the carrier — a buggy scrub lands green). SIX MUST-FIX items (all pair-scope, small) gate the R-4.8 MERGE HAND-UP; the published DRAFT PR #24 gates on NOTHING and stays as-is. My §2 fold-or-register rulings below. §3 convergent items (R-4.10/R-4.11) are cited not re-registered — no action. §4 is the operator's cell (unconditional vs sessions-gated capture) — routed, master + I recommend (a); either answer folds into this same window. Run the fold as ONE bounded cycle under a FRESH lineage chain (both edges — see the discipline note), targeted re-check sized to the delta, then the merge hand-up (condition-3 end-state-bytes + condition-4). Nothing seals; the release hold is ABSOLUTE.

ROLE: Orchestrator Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-matrix-r48-lens-mustfix-fold
PARENT_DISPATCH_ID: s4-matrix-r48-published-verified
IN_REPLY_TO: ../../../../pdc/master/relays/s4-build-standup/MERGE-GATE-ORCHESTRATOR-PLANNER-LENS-VERDICTS-SIX-MUST-FIX-CONVERGENT-ROWS-CITED-ONE-OPERATOR-CELL-20260810-070844.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — §4 is one OPERATOR policy cell (unconditional vs sessions-gated capture); the six must-fix items are pair-scope and gate only the R-4.8 merge hand-up; the fold's own IMPL token is the pair-Planner's to issue after the Implementer PLAN-REVIEW; the release hold is ABSOLUTE.
DESIGN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-09-s4-matrix-arm1-r48-packer-home-carrier-design.md
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/plans/2026-08-09-s4-matrix-arm1-r48-carrier-plan.md
FROM: s4.orchestrator-planner
TO: s4-matrix.planner
CC: operator, s4.orchestrator-reviewer, s4-matrix.implementer, master.orchestrator-planner, m-2.planner
SUBJECT: PLAN — carry the six R-4.8 lens must-fixes as one bounded fold (gating the merge hand-up); §2 rulings; §4 operator cell surfaced; lineage discipline restated

## 1. MUST-FIX (six, pair-scope, gate the R-4.8 MERGE hand-up — NOT the published draft)

Re-verified B-3.3 and B-2.1 at the bytes at `2341667` at this seat; all six are master's, carried intact:
1. **(B-3.3) Hermeticity — LIVE (the historic B2C2-3 class recurring):** hoist HOME-pinning into an RAII
   fixture used by EVERY pack test (the eight unpinned: `:461/:525/:551/:576/:660` claude-only-pinned;
   `:705/:747/:774` codex-only-pinned) AND add a REAL store guard — assert every discovered `store.root`
   lies under the test temp root (`agent_sessions.empty()` cannot detect an escape; verified). `:606-607`
   shows the authors knew the two-tier hazard — make it uniform. Falsifier: a test with a real `~/.codex`
   present must not read it.
2. **(B-2.1) Receipt vacuity:** add an engaged-arm fixture whose session bytes lie UNDER the carrier path
   (or point the carrier at the fixture workspace's parent) so a scrub divergence is VISIBLE; today both
   arms are byte-identical regardless of carrier behavior (`/Users/packer` in zero fixture bytes — verified).
3. **(B-2.2) Silent-drop masking:** `receipt.contents.emplace(...)` is a no-op on a duplicate normalized
   name — wrap as `REQUIRE(….second)`, both receipts (one line each).
4. **(B-3.1) Var-complete pinning:** pin `CODEX_SQLITE_HOME` in the capture matrix (read at
   codex.cpp:726-738; latent, fires for any operator who exports it).
5. **(B-oracle-1) Regeneration pin:** add the `ORACLE RULE — never regenerate from the serializer` comment
   to the exact-bytes golden (`test_manifest.cpp:93-111`), matching `test_envelope.cpp:566-567`.
6. **(B-2.3) Claim carve-out:** state the id_map carve-out in the receipt claim (minted-id identity
   normalized across arms by construction) — or compare id_map shape across arms.

## 2. FOLD-OR-REGISTER — my rulings (master delegated §2 to s4)

- **(A-Q2 + B-Q1 extended-grammar gap + UNC) → REGISTER at the needle head with a UNC-disposition note.**
  The rev6 extended-root boundary (`>7`, single `classify_carrier_root` authority) is LOCKED; adding a
  positions-4-6 `<alpha>:<sep>` drive-spec grammar check is a design-SEMANTICS change, not a fold. Register
  the gap (`\\?\abcd` validates as a windows home; `\\?\UNC\…` under-floors; bare UNC silently drops the
  carrier) at the needle head. **You MAY fold ONLY a pure drive-spec/UNC tightening that is expressible
  within the locked rev6 classifier WITHOUT changing its sealed semantics; if it needs a semantics change,
  STOP and route up for a design micro-amendment — do not silently move locked design.** Confidentiality-
  inert (mislabel/silent-drop, not a leak), so registering is safe.
- **(B-oracle-2 "appears nowhere else in the image" confidentiality receipt) → REGISTER at the needle head**
  beside R-4.10's observability (the confidentiality property currently has no test).
- **(B-Q1 brackets — minimal-accept posix/wsl/drive `/x`, `/mnt/c/x`, `C:/x`) → FOLD into the must-fix test
  window if cheap** (additive boundary coverage; the extended pair alone catches only uniform tightenings),
  else register — your call, lean fold.
- **(A-obs-2 `PackerHome` publicly constructible) → FOLD** the private-ctor + factory-sole-builder hardening
  if small (prevents a future direct writer bypassing `make_packer_home` and silently losing the field),
  else register — your call, lean fold. NOTE: this is a src/ change; if it grows beyond a mechanical
  ctor/visibility change, register instead.

## 3. CONVERGENT — cited, not re-registered (no action; good signal)

Lens A independently re-derived two registered rows: A-obs-1 (silent fail-open at the producer — unset/
relative `$HOME` ⇒ no carrier, no diagnostic) IS **R-4.10** (carrier-emission opacity, due at the needle
head); A-obs-3 (the `/mnt/<alpha>/` wsl mislabel driving a confidentiality control) IS **R-4.11** (derive
from the PATH; the recorded flavor is a hint never authority). Confirmations of the registry, not news.

## 4. THE OPERATOR CELL (surfaced; the operator decides — master + I recommend (a))

Capture is UNCONDITIONAL (`pack.cpp:676`): a ZERO-session image now carries the packer's home (hence
username) where the needle never runs and where it previously did not. **Options:** (a) gate capture on
`!agent_sessions.empty()` — no sessions ⇒ no carrier ⇒ no disclosure, nothing lost (the scrub has no
material); (b) keep unconditional. **I concur with master's (a):** it is the origin-disclosure family's
standing minimal-disclosure posture (packer identity must not reach the recipient store), a sessionless
disclosure of home/username is exactly what the family minimizes, and the gate is one condition. The
operator decides; either answer folds into THIS same must-fix window — proceed on §1 meanwhile; wire the
capture-gating cell once the operator's answer lands.

## 5. Lineage discipline (so this fold does NOT cycle like fold-3)

Run the fold as ONE bounded cycle. The fold PLAN carries the R-4.8 design lock (design-doc kind), so BOTH
lineage edges must hold: **Edge 1** — the PLAN parents to the approving **rev6 DESIGN-REVIEW**
(`s4-matrix-arm1-r48-design-rev6-review`, approve `231944`), NOT a check/SITREP; **Edge 2** — the fold
`DISPATCH-IMPL` token parents to the Implementer's approving PLAN-REVIEW of that PLAN. Then a targeted
re-check sized to the delta (tests-hermeticity + the src hardening if folded; a round-trip/real-store
falsifier for B-3.3 and a carrier-divergence-visible fixture for B-2.1), then the fresh merge hand-up. The
merge hand-up gates on §1 + the standing end-state-bytes condition-3 at the eventual merge base (the branch
predates C/B2 at `6047ab03`).

Nothing seals; the published DRAFT PR #24 stays as-is (it gates on nothing); merge ≠ release; the release
hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — read-only re-verification at `2341667` (codex.cpp:758-778 unconditional home append; test_pack.cpp:461/705 pin CLAUDE_CONFIG_DIR/CODEX_HOME not HOME; /Users/packer absent from all fixtures) + this dispatch relay + its INDEX row on one explicit-path docs-lane commit whose SHA lands after filing. No fold executed at this seat; the branch is the pair's.
RELAY_LINT: per D-3.4 — per-file WITH freshness at this seat before filing; `.relays/s4/INDEX.md` tail re-read for sibling rows before appending; `--index`; commit GATED on both exits, path-scoped add AND commit. Expected `--index` reds: the R-4.8 design/plan path-style-lock false-reds (relay-lint.py:1639, referents exist at repo-root) + the line-222 sibling inversion — none mine.
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to this relay and `.relays/s4/INDEX.md`.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-R48-LENS-SIX-MUSTFIX-FOLD-CARRIED-DOWN-20260810-071834.md` → `s4-matrix.planner`
- SIX must-fixes (B-3.3 hermeticity RAII+store-guard; B-2.1 carrier-divergence-visible fixture; B-2.2 REQUIRE(.second); B-3.1 pin CODEX_SQLITE_HOME; B-oracle-1 golden ORACLE comment; B-2.3 id_map carve-out) gate the R-4.8 MERGE hand-up; published DRAFT gates on nothing; B-3.3+B-2.1 re-verified at bytes at my seat
- §2 rulings: extended-grammar/UNC → REGISTER at needle head (locked rev6 semantics; pure in-design tightening may fold ELSE stop-and-route); oracle-2 → REGISTER at needle head; B-Q1 brackets + A-obs-2 private-ctor → FOLD if small else register (pair discretion)
- §3 R-4.10/R-4.11 convergent, cited not re-registered (no action); §4 operator cell (unconditional vs sessions-gated capture) → operator decides, master+I recommend (a), folds into this window
- lineage: BOTH edges (PLAN→rev6 DESIGN-REVIEW; DISPATCH-IMPL→Implementer PLAN-REVIEW); targeted re-check → merge hand-up (§1 + end-state-bytes condition-3); nothing seals; release hold ABSOLUTE
