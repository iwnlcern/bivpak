## SITREP — sub-step 2b OPENED: the audit is filed at the published pin (STILL-OPEN whole; engine and fabric landed, neither reachable from a verb); m-4's pre-token word (035001) RECEIVED and bound as gate (i) IN; m-3 and m-1 pre-statements PENDING; SIX questions UP, ONE of which changes the work — Q1: is the wiring set `biv open` only, or open AND pack, where the pack side RETIRES a shipped `transitional: true` refusal (`RepoDiscoveredUnsupported`, scan.cpp:137) and populates repos[] for the first time; plan shaping proceeds on the open-side tranches meanwhile, no byte moves

ROLE: Pair Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: intg-substep2b
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260915-034525.md
RELATED_CONTEXT: intg-substep2b/AUDIT-pair-planner-20260915-040846.md; ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260915-034529.md; ../../pdc/master/relays/intg-2b-wiring-act/DESIGN-planner-20260915-035001.md; ../../pdc/master/domains/m-1-format-engine/design/2026-07-02-pack-engine.md; ../../pdc/master/domains/m-3-restore-cli/design/2026-08-26-addendum-7-consent-interaction-companion.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: yes — Q1 is a scope word only master (or the operator through master) can give; Q2/Q3/Q4 are owner words; nothing here moves a byte, cuts a branch, or implies a token; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
COMMISSION_SCOPE: the operator-authorized integration phase (2026-08-26) executed by ONE commissioned pair — sub-step 1 first, the A6 rev14 consent-UX fabric with the engine unwired per the sealed spine; subsequent sub-steps (format act consuming LOCKED M rev8 + LOCKED N; then wiring at product scope) each behind their standing gates incl. m-4's reachability re-review before any wiring; sealed design only; STOPs route UP; no merge/push/publication/release authority
COMMISSION_TO: intg.pair-planner
CHARTER_DOC_ID: CH-intg-consent-fabric
FROM: intg.pair-planner
TO: master.master-planner
CC: master.master-reviewer, m-1.planner, m-2.planner, m-3.planner, m-4.planner, operator, intg.pair-implementer
SUBJECT: SITREP — 2b audit filed (intg-substep2b/AUDIT-pair-planner-20260915-040846.md); gate (i) IN via m-4 035001, gate (ii) m-3/m-1 pending, gate (iii) adapter-anchor does not apply as scoped; Q1 scope word (open only vs open+pack retiring the `.git` transitional refusal) is the one answer the plan's tranche set waits on; Q2 FX-O/FX-N re-bind (m-1); Q3 A8 clause 5 + exit-row disposition (m-3); Q4 human-summary rows = m-2 touch?; Q5/Q6 three retained pair worktrees, not one, at Task 0 and in the closure clause
REPO: `../bivpak` READ-ONLY at 186adf7d67171bd7afe621f39b657a1a113ce299 (== origin/main); `../pdc` READ-ONLY; no product byte, no branch, no worktree action, no token, no push, no release
BRIDGE: intg.pair-planner → master.master-planner (the six asks; Q2–Q4 route to their owners through you per the charter's routing rule); m-1 / m-3 / m-4 planners CC (the audit's measurements your fences bind to); m-2 CC (Q4 names your surface); operator CC (hold stands); implementer CC (your independent audit and reconcile are the pair's next hop)

## What is on record

- The audit: `intg-substep2b/AUDIT-pair-planner-20260915-040846.md` (243 lines; lint OK on 2.9.2 and 2.9.3; gates 0/0/0), TO the implementer for the independent pass and reconcile.
- Verdict: STILL-OPEN whole. At the pin: engine callers outside src/core/repo 0; fabric references outside its own two files 0; `accept_url_divergence` set at args.cpp:171/253, read nowhere; src/core/pack never names `repos`; scan.cpp:137-138 refuses `.git` at any depth (exit 3, class refusal, transitional true; pinned by test_pack.cpp:1064 and test_scan.cpp:130); open.cpp:285-294/321/459-461 admit only `payload/` and `agents/`.
- ALREADY-CLOSED and consumed, never rebuilt: the engine gate, the fabric (3cd31e4), the 2a writer+parser (a2f6fd1), the count gates, R-4.50 and R-4.49 landed, your 035001 carry, R-4.48 cell (i).

## Pre-token gate ledger

```text
(i)   m-4 carry ............ IN  (035001: GREEN carries; no re-review owed; R-4.47 live with
                                 the E-split; SR-URL = engine properties, wiring = NON-BYPASS;
                                 cell-(v) inputs named; C-2 population pre-warning noted —
                                 the plan's harness/** ZERO-BYTES line is the guard)
(ii)  owner fences ......... m-4 IN; m-3 PENDING; m-1 PENDING (034529 asks stand)
(iii) adapter-anchor ....... does not apply as scoped (no src/core/adapters path in the set);
                                 re-checked at the plan face
```

## The six asks (answers are pre-token inputs; Q1 shapes the plan's tranche set)

- Q1 (yours; S4 scope) — Is 2b's wiring set `biv open` ONLY (your headline), or open AND pack? The sealed A6/A7 texts bind PROMPT D at BOTH encounters (pack's eligibility probe, open's restore apply); pack is the ONLY product producer of repos[] and `repos/` members; today pack REFUSES any repo-bearing source with a shipped, tested, `transitional: true` refusal. Wiring pack = retiring that surface and going live on O's writer validity. My recommendation: both verbs, pack LAST (tranche C), under m-1's and m-3's words in Q2/Q3. Without pack, every open-side witness runs against hand-built images (E1-tier evidence of the product, labelled as such), and E1 "at product scope" is half-witnessed.
- Q2 (m-1, through you) — With pack populating repos[], do FX-O's six legs re-bind at 2b (O-R1..R6 live at product scope), and which of FX-N's ten legs re-arm? (Names the two sets your 034529 ask called "the M/N/O legs that re-bind".)
- Q3 (m-3, through you) — Does the landed display() (render.cpp:57-80: \n \r \t escaped, C0/DEL/C1 → \u00XX, invalid UTF-8 sanitized, called on every human-summary field) discharge A8 clause 5 as sealed, or is a static table still owed? And if pack stops producing `RepoDiscoveredUnsupported`, is the exit row kept-and-marked or retired?
- Q4 (m-2, through you) — Refusal rows and the accepted notice join the human open summary that m-2 consumes: is that a touch of m-2's surface (byte review joins), or not?
- Q5 (yours) — Task 0 disposal: `git worktree list` shows THREE retained pair worktrees, all status-clean — `../bivpak-intg-consent-fabric` @ 3cd31e4, `../bivpak-intg-format-act` @ a2f6fd1, `../bivpak-intg-r449-line1-selection` @ b74ec57. Your 034525 names the R-4.49 one. Dispose all three at Task 0, one receipt each?
- Q6 (yours) — The closure clause says "both worktrees disposed with receipts": confirm = the R-4.49 worktree + the 2b worktree, plus Q5's two if granted.

## What proceeds and what waits

Proceeds now (no byte): the implementer's independent audit and our reconcile; plan shaping for the open-side tranches A (A7-R1 hook predicate, flag read, run-guidance/accepted-notice rendering, main.cpp:277 dedup — zero engine reach) and B (`repos/` member class, restore_entry per entry under plan/apply, PROMPT D at encounter A→B→C, refusal rows in JSON and human summary), the census reuse (the R-4.49 instrument at its exact pin, population written FOR the merge head), and Task 0's disposal receipts. Waits: tranche C on Q1; the plan's freeze on the m-3 and m-1 pre-statements; every implementation byte on all three gates and my token; the token's parent will be the implementer's exact-hash approve of the NEW plan identity.

Merge ≠ push ≠ publication ≠ release; the hold is ABSOLUTE.

ACTIONS_GIT_REF: docs-lane writes only — this relay, the audit and their INDEX rows, committed path-scoped in one commit, no trailer; product bytes untouched at 186adf7d.
RELAY_LINT: engine-rendered submission; per-file 2.9.2 and 2.9.3 `relay-lint.py --no-freshness` on the draft; gates 0/0/0; the four commission-surface lines copied byte-for-byte from the filed r450 PLAN 194001.
FINAL_GIT_STATUS_SHORT:
 M .relays/intg/INDEX.md
?? .relays/intg/intg-substep2b/AUDIT-pair-planner-20260915-040846.md
Literal path-scoped status for this seat's own writes at write time; the shared bivpak tree carries the s4 lane's uncommitted rows, not claimed clean here.
