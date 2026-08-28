## **H27 STAGE (b) — THE COMMISSION CHARTER `CH-intg-consent-fabric`: the local charter of the integration-phase build pair, restating parent law from the tier's charter-template; authored by `master.master-planner` under the operator's T1 (`142730`, the operator's typed "authorized" quoted on its face) and routed to `master.master-reviewer` for the stage-(c) same-owner parented approval — THE PAIR DOES NOT EXIST until the approval and the stage-(d) grant land; this relay commissions nothing by itself.** **DISCLOSED ON THE FACE: this is the first relay authored from the adopted `master.master-planner` seat (operator-ruled in-place adoption, 2026-08-27 — the sitting legacy CTO session read its boot pointer `135336`, loaded the tier skill, and continues as this seat; occupant `2dae5bed…`; the legacy address is retired from new authorship, its filed relays immutable).** **THE CHARTER IS THE BODY BELOW, verbatim-restated parent law: cardinal rules the pair preserves without reinterpretation; org chart and addressing; the domain owns/consumes edges the work touches; the substrate layout per the s4 precedent; the commission identity carried byte-equal from T1.** Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ROLE: Master Planner
PHASE: DESIGN
AUTHORITY: design-only
DISPATCH_ID: intg-commission-charter
PARENT_DISPATCH_ID: intg-t1-authz
IN_REPLY_TO: master/relays/intg-t1-authz/PLAN-operator-20260827-142730.md
RELATED_CONTEXT: CLAUDE.md; master/RESIDUALS.md; master/ARCHITECTURE.md
RUN_ID: master
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no — the operator's stage-(a) authorization is consumed (`142730`, quoted verbatim there); this charter binds nothing until the Master Reviewer's stage-(c) parented approval and the stage-(d) grant; every build gate named below remains separately governed; the release hold is ABSOLUTE
DESIGN_DOC_ID: CH-intg-consent-fabric
DESIGN_RECORD_KIND: design-doc
COMMISSION_AUTHORIZATION: yes
COMMISSION_ID: intg-consent-fabric
COMMISSION_SCOPE: the operator-authorized integration phase (2026-08-26) executed by ONE commissioned pair — sub-step 1 first, the A6 rev14 consent-UX fabric with the engine unwired per the sealed spine; subsequent sub-steps (format act consuming LOCKED M rev8 + LOCKED N; then wiring at product scope) each behind their standing gates incl. m-4's reachability re-review before any wiring; sealed design only; STOPs route UP; no merge/push/publication/release authority
COMMISSION_TO: intg.pair-planner
CHARTER_DOC_ID: CH-intg-consent-fabric
FROM: master.master-planner
TO: master.master-reviewer
CC: operator, m-1.planner, m-1.implementer, m-2.planner, m-2.implementer, m-3.planner, m-3.implementer, m-4.planner, m-4.implementer
SUBJECT: DESIGN — H27 stage (b): commission charter CH-intg-consent-fabric for the intg pair (T1 142730 consumed; commission identity byte-equal), restating parent law — cardinal rules, addressing, owns/consumes edges, s4-precedent substrate in ../bivpak, sub-step-1-first scope with every standing gate named; routed to master.master-reviewer for the stage-(c) parented approval; the pair does not exist before approval + grant; first relay from the adopted master.master-planner seat, disclosed
REPO: `../bivpak` not read this turn — a governance charter in the pdc docs tree; the pair's substrate paths are declared below and created by the pair at its boot, not here.
BRIDGE: master.master-planner → master.master-reviewer; H27 stage (b) → (c); operator CC (your T1 consumed exactly); domain seats CC (your fences are restated as this charter's cardinal rules)

## CARDINAL_RULES (parent law, preserved without reinterpretation)

```text
- SEALED DESIGN ONLY: implement VP-approved sealed text exactly — no addition, removal,
  or reinterpretation of any normative element (generalized fence rule). Where sealed
  text DETERMINES the implementation, execute; where it defers or is silent, STOP and
  route UP: intg.pair-planner -> master.master-planner -> the owning domain planner ->
  back down the same path. The pair NEVER amends the design-of-record.
- OWNER BYTE GATE: every deliverable rides under the owning domains' BYTE-LEVEL REVIEW
  AND VETO at the exact candidate SHA; a commissioned-pair merge additionally requires,
  as a packet predicate, green byte-review/no-veto evidence from EVERY fenced owning
  domain — evidence, never merge authority.
- SPINE + GATES, in order: sub-step 1 = A6 rev14 consent-UX fabric, ENGINE UNWIRED
  (consumes LOCKED A6 c41d015f); the format act consumes LOCKED M rev8 (2966b839) +
  LOCKED N (82293732) under V-M-INT-1..5 + V-N-1/V-N-2 with the (i)/(j) censuses at
  m-1's byte review; m-4's MANDATORY reachability re-review precedes ANY verb-to-engine
  wiring; M-R8 veto 9 (no product-call-site diff before the gate-bearing engine diff);
  the reduced real-git E2 set at the resume; all-green regression before any merge claim.
- PRODUCT DNA: read host state freely, write only with consent; the sole host write is
  the consent-yes session import at biv open; no agent launches; credentials/user config
  never collected, packed, or rewritten; .bvpk is an archive, not an app-owned store.
- CI/MERGE LAW: remote GitHub Actions is UNFUNDED and produces NO SIGNAL — never gate on
  it; merge evidence = local suites GREEN + Docker Linux parity (ubuntu-24.04
  --platform linux/amd64, nofile soft==hard raised per R-4.31(a), --init for product
  behaviour per R-4.40). Merge needs the four-condition bar + the owner predicate;
  DISPATCH MERGE issues from the OPERATOR directly. Merge != push != release; the
  trunk push is a separately operator-gated publication act (R-4.46); the release hold
  is ABSOLUTE.
- RECORDS: relative paths king (payload/worked-example carve-out exempt); filed relays
  immutable; deferrals register in master/RESIDUALS.md, never only in a relay; relay
  discipline per v2.9.2 (engine-rendered, per-file lint, path-scoped commits).
```

## ORG_CHART + ADDRESSING

```text
ORG_CHART:
- pair planner:      intg.pair-planner   (adt-master:pair-planner; RUN_ID intg)
- pair implementer:  intg.pair-implementer (adt-master:pair-implementer; subsumes
                     adversarial review; NO third seat)
ADDRESSING:
- FROM: intg.pair-planner | intg.pair-implementer (each its own FROM, never proxied)
- TO (cross-team): master.master-planner ONLY — the single bridge edge; the
  pair-implementer never addresses master or a domain seat
- CC: master.master-reviewer + the owning domain reviewers on authority-bearing and
  merge-visibility relays; CC is visibility, never routing
```

## DOMAIN TABLE (owns/consumes edges this commission touches)

```text
| Domain | The pair consumes | The pair NEVER |
|---|---|---|
| m-3 (restore/CLI) | LOCKED A6 rev14 consent-UX surface: PROMPT D fabric, golden text, V-A6-1..6 incl. zero-m-3-surface-bytes bar + structural wiring veto | cuts golden wording (m-3 seat only) |
| m-1 (format/engine) | LOCKED M rev8 (M-R1..R8, veto 9) + LOCKED N (repos[].shallow cell) + sealed §2.3+G+H for the format act | relaxes require_empty_array("repos") outside the fenced format act |
| m-4 (security) | SR-URL rev2 (a2f777c2) requirements; m-4's consolidated triggers | wires verb-to-engine before m-4's reachability re-review |
| m-2 (adapters) | no edge in sub-step 1; adapter contracts consumed read-only if later sub-steps touch them | opens adapter work without a routed STOP |
```

## LAYOUT (s4-precedent substrate — sub-team artifacts live in the CODE repo)

```text
LAYOUT:
- relay root:      ../bivpak/.relays/intg/          (git-tracked; own engine root)
- sprint docs:     ../bivpak/docs/sprints/2026-08-27-intg-consent-fabric/
- bridge relays:   master/relays/ (pdc) — ONLY the master <-> intg.pair-planner edge
- spec of record:  the SEALED pdc design tree (read-only to the pair): LOCKED A6/M/N,
                   sealed §2.3+G+H, SR-URL rev2 — cited by lock id + pin, never copied
- ledgers:         pair-local reconcile + deviations (Stock -> Ours -> Why -> Status)
                   under the sprint docs dir; deferrals surface UP to master/RESIDUALS.md
- docs lane:       commits path-scoped to docs/sprints/** + .relays/** land outside the
                   product merge bar; anything else is bar-governed by definition
```

## COMMISSION_ID

```text
COMMISSION_ID: intg-consent-fabric
COMMISSION_TO: intg.pair-planner
CHARTER_DOC_ID: CH-intg-consent-fabric
AUTHORIZATION: intg-t1-authz/PLAN-operator-20260827-142730.md (operator, "authorized",
               verbatim on its face)
```

## Sequenced after stage (c)

Master Reviewer approve (parented to THIS relay, commission identity byte-equal) →
stage-(d) delegated-dispatch grant to `intg.pair-planner` → `relay commission` exports the
child-run record → the pair boots LAST on `pair-planner`/`pair-implementer`, creates its
substrate, and opens with the sub-step-1 audit. Must-revise → successor charter at this pen.

ACTIONS_GIT_REF: pdc docs-tree writes only — this charter via the engine and its engine-owned projection. No pair exists yet; no product act, no merge, no release.
RELAY_LINT: per D-3.4 — engine-rendered, per-file v2.9.2 lint, un-piped exit to the gate; commit path-scoped.
CARRY_LIST (per D-8.5, this turn's pending hops — path + the one TO seat):
- rendered successor of this draft -> master.master-reviewer
FINAL_GIT_STATUS_SHORT:
 ?? master/relays/intg-commission-charter/
Literal path-scoped status for this seat's own writes at write time; the shared pdc tree carries sibling-authored state not claimed clean here.
