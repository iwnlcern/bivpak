## MERGE-GATE — STOP on the token's TRANSPORT GRAMMAR, not its authority: the operator's condition-4 authorization (044640, "Ok, merge it" quoted on the face) is RECEIVED, VERIFIED AT MY READ, and STANDS UNCONSUMED — but the ruled mechanics ("the PAIR-PLANNER issues the bare token in-lane to its implementer") FAILS the linter's grantor set at the source: relay-lint.py:1170 restricts a bare DISPATCH MERGE's FROM to {operator, orchestrator, *.orchestrator-planner}; a pair-planner-FROM token relay reds at the daemon gate and cannot file — the same gate family that redded the 044604 predecessor's TO-half (:1163, re-derived at my read: FROM operator / TO intg.pair-planner / bare token). NO MERGE ACT TAKEN; the compliant remedy is ONE operator-seat re-issuance TO intg.pair-implementer; HOLDING

ROLE: Pair Planner
PHASE: MERGE-GATE
AUTHORITY: report-only
DISPATCH_ID: intg-substep1-merge-packet
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: ../../pdc/master/relays/intg-substep1-merge-token/MERGE-GATE-operator-20260829-044640.md
RELATED_CONTEXT: ../../pdc/master/relays/intg-substep1-merge-token/MERGE-GATE-operator-20260829-044604.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/results/intg-substep1-merge-gate.md; intg-substep1/MERGE-GATE-pair-planner-20260828-194800.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — the one open cell is the token's grammar-compliant transport: the operator's authorization is issued and standing, but the bare DISPATCH MERGE must be FROM a grantor the linter accepts ({operator, orchestrator, *.orchestrator-planner} — relay-lint.py:1170) and TO exactly one implementer-role address (:1163); the recommended remedy is one re-issuance from the operator's provisioned engine seat TO intg.pair-implementer; no merge occurs until a compliant token lands; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
FROM: intg.pair-planner
TO: master.master-planner
CC: operator, master.master-reviewer, intg.pair-implementer, m-3.planner, m-3.implementer
SUBJECT: MERGE-GATE — STOP routed UP per the standing fallback: the 044640 authorization verified at my read (dispatch intg-substep1-merge-token, MERGE_STATUS AUTHORIZED, lock hashes c41d015f/7ce2251d + 4c40fe37/e4a6b982 match my records, predecessor 044604 disclosed and its red re-derived) and STANDS UNCONSUMED; the in-lane issuance it directs is mechanically unfilable — relay-lint.py:1164-1170 (verified at the source, matching my registered note "grantor set orchestrator-planner-and-above, stricter than DISPATCH IMPL"): FROM must be operator/orchestrator/orchestrator-planner (pair-planner is NOT in the set; master-tier is token-barred at :804), TO exactly one implementer-role (:583 canonical-role check — intg.pair-implementer QUALIFIES); pre-merge state re-verified and GREEN (candidate clean at 3cd31e4; merge-tree at CURRENT main 73180d7 still 0-conflict); remedies framed below, R1 recommended; NO self-served workaround taken

## The conflict, measured (all at my own read)

```text
authorization  044640: FROM operator, TO intg.pair-planner, PHASE MERGE-GATE,
               AUTHORITY merge-gated, MERGE_STATUS: AUTHORIZED, the operator's
               typed words quoted on the face — VERIFIED; carries NO bare token
               (correct for its shape: TO is not an implementer)
directed       its face: "under the settled pair gate the PAIR-PLANNER issues the
mechanics      bare token in-lane to its implementer"
the gate       relay-lint.py:1164-1170 — a bare DISPATCH MERGE requires PHASE
               MERGE-GATE, exactly one TO that is implementer-role (:1163, :583),
               and FROM in {operator, orchestrator} or address_role ==
               orchestrator-planner (:1170). intg.pair-planner FAILS :1170.
               relay-lint.py:804: master-tier seats may not carry the token.
               => NO seat inside this commission's lanes can file the bare token;
               the daemon gate refuses the directed form before it ever lands.
predecessor    044604 re-derived: FROM operator (grantor VALID), TO
               intg.pair-planner + bare token => the :1163 red the successor
               disclosed — the TO-half of the same grammar; the FROM-half (:1170)
               went untested at the successor because it carries no token.
state          candidate CLEAN at exact 3cd31e4 (re-verified this turn);
               merge-tree vs CURRENT main (73180d7) still 0 conflicting paths;
               origin untouched; NO merge act, NO token relay attempted (a red
               submission would be self-served instrument noise); the
               authorization is UNCONSUMED at this seat.
```

## Remedies (the choice is the operator's/yours; both leave the authorization-of-record untouched)

```text
R1 (recommended, grammar-clean, one act): re-issue the bare token from the
    operator's provisioned engine seat exactly as 044640 was filed, changed only
    in shape: TO: intg.pair-implementer (exactly one implementer-role addressee),
    bare DISPATCH MERGE alone on its own line, PHASE MERGE-GATE, FROM operator —
    passes :1157/:1163/:1170 by construction; the 044640 authorization stands as
    the decision of record and the new carrier cites it. The implementer then
    executes the lane-local merge per the packet §4 topology and reports the
    landed receipts; I verify and route them UP.
R2 (ruling-shaped): master + operator explicitly rule alternative mechanics —
    e.g., the pair-planner executes the lane-local merge itself under 044640
    with NO bare token relay (requires an explicit reassignment ruling: my seat's
    role contract excludes running merges, and the token grammar would simply be
    bypassed rather than satisfied — flagged, not endorsed).
R3 (kit-shaped, out of this lane): widen the linter's grantor set — named only
    for completeness; every prior adjudication in this run found the linter
    correct and the authoring at fault, and nothing here needs the kit to move.
```

HOLDING: no merge act, no token attempt, the packet unchanged at census-complete-except-condition-4-transport. On R1's token landing at the implementer, my next acts are the post-merge verification and the landed report UP.

ACTIONS_GIT_REF: docs-lane writes only — this report via the engine; the candidate untouched at 3cd31e4; main untouched at 73180d7; no merge, push, PR, remote CI, publication, deployment, seal, or release act
RELAY_LINT: engine-rendered submission; per-file v2.9.2 lint rides the daemon gate
FINAL_GIT_STATUS_SHORT:
 ?? .relays/intg/.engine/drafts/intg.pair-planner/MERGE-GATE-TOKEN-GRAMMAR-STOP.md
Literal path-scoped status for this seat's own writes at authoring time; the shared bivpak tree additionally carries sibling-authored state not claimed clean here.
