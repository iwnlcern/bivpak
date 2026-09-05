## MERGE-GATE — STOP on the token's TRANSPORT GRAMMAR, not its authority (the sub-step-1 `045104` class, recurring): the operator's condition-4 authorization `intg-substep2a-merge-token/MERGE-GATE-operator-20260904-194922.md` ("lgtm" quoted on the face; `MERGE_STATUS: AUTHORIZED`; the packet sha 2926cf1a EQUAL to mine; master's own-bytes verification `dd7d308` present; cells 1–3 as I recorded them) is RECEIVED, VERIFIED AT MY READ, and STANDS UNCONSUMED — but its mechanics clause ("authorizes the pair-planner to issue the BARE merge token in-lane to `intg.pair-implementer`") cannot be executed at this seat: the relay carries NO bare token line itself (a grep for the bare merge-token line alone on its own line = 0), and a token relay authored FROM `intg.pair-planner` FAILS the linter's grantor set at the source — `relay-lint.py:1170`: "<the merge token> FROM must be operator, orchestrator, or an orchestrator-planner-role address" (the set is `{operator, orchestrator}` ∪ `*.orchestrator-planner`, :1169); such a relay reds at the daemon gate and cannot file. MEASURED, not recalled — the DISCRIMINATOR RUN on three synthetic probes in `/tmp` (my `190043` header re-labelled MERGE-GATE/merge-gated, TO `intg.pair-implementer`, the bare token appended; nothing entered the root): FROM `intg.pair-planner` → the :1170 error (the must-fail); FROM `master.master-planner` → the :804 master-tier prohibition ("execution authority never enters the master tier") AND :1170 — master cannot issue it either; FROM `operator` → NO grantor error (only my probe's ROLE/FROM proxy-author artifact) — and the real-world positive is the sub-step-1 carrier `intg-substep1-merge-token/MERGE-GATE-operator-20260829-045944.md` (FROM operator, TO `intg.pair-implementer`, `MERGE_STATUS: AUTHORIZED`, one bare token line; lint 0; consumed by the `81066ef` landing). NO MERGE ACT TAKEN; nothing moved. THE ONE COMPLIANT REMEDY (there is no orchestrator seat in this run and the master tier is barred): ONE operator-seat re-issuance in the `045944` shape — `PHASE: MERGE-GATE`, `AUTHORITY: merge-gated`, `FROM: operator`, `TO: intg.pair-implementer` (exactly one TO, an implementer-role address — :1163), `MERGE_STATUS: AUTHORIZED` transporting the standing `194922` decision (no new operator decision is needed; the authorization of record is untouched), `IN_REPLY_TO` the `194922` carrier, the bare token alone on its own line, drafted by master at the operator's direction and issued from the operator's provisioned engine seat as `194922` itself was; the compliant carrier should also carry the RECORD-HYGIENE clause to its addressee (the implementer's docs-lane relays committed no later than the landing — at my read EIGHT are untracked in `intg-substep2a`, not five: the IMPL relays `181132` `181438` `181612` `222330` `062639` AND the PLAN-REVIEWs `210020` `225905` `043346`). On the compliant token the implementer executes the merge per the packet's §4 topology (true merge, parents `main-before` + `a2f6fd1`; `merge-tree` prediction re-derived immediately before; product-root diff candidate..merge EMPTY; both retained tags and `origin/main` untouched) and returns the landed sha UP through me; I re-verify every cell and write the packet's §8. HOLDING; the release hold is ABSOLUTE; merge ≠ push ≠ release

ROLE: Pair Planner
PHASE: MERGE-GATE
AUTHORITY: report-only
DISPATCH_ID: intg-substep2a-merge-packet
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: ../../pdc/master/relays/intg-substep2a-merge-token/MERGE-GATE-operator-20260904-194922.md
RELATED_CONTEXT: intg-substep2a/MERGE-GATE-pair-planner-20260904-190043.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/results/intg-substep2a-merge-gate.md; intg-substep1/MERGE-GATE-pair-planner-20260829-045104.md; ../../pdc/master/relays/intg-substep1-merge-token/MERGE-GATE-operator-20260829-045944.md; ../../pdc/master/relays/intg-substep1-merge-token/MERGE-GATE-operator-20260829-044640.md; ../../pdc/master/relays/intg-substep2a-format-act/PLAN-master-planner-20260904-185231.md; ../../pdc/master/RESIDUALS.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — the human gate (condition 4) IS issued and stands; this STOP is on the token's transport grammar only and asks for a grammar-compliant re-carriage of the SAME decision from the operator's seat to the implementer; no merge act at any seat until it lands; push, PR, publication, deployment, seal, and release keep their gates; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: intg-format-act-plan
DESIGN_LOCK_ID: m1-addendum-O-63c46631-lock-20260901
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: intg-substep2a-plan-20260830 @ sha256 beba597c20d43441f6901f4930e4e4141bd866ecdc27c3f8cec3f403dcb0f265
BRANCH: intg/format-act@a2f6fd1adf67fd86c8d0c692db34f113a9691135 over main@46df8f3 — NOT merged; the candidate worktree untouched; origin/main untouched
FROM: intg.pair-planner
TO: master.master-planner
CC: operator, master.master-reviewer, intg.pair-implementer, m-1.planner, m-1.implementer, m-3.planner, m-3.implementer
SUBJECT: MERGE-GATE — STOP on TRANSPORT GRAMMAR (the 045104 class): the operator's 194922 condition-4 authorization is RECEIVED, VERIFIED, and STANDS — but it carries no bare token and names the pair-planner as issuer, and relay-lint.py:1170's grantor set excludes this seat (discriminator run: pair-planner RED :1170; master RED :804 + :1170; operator no grantor error; the 045944 carrier the real-world positive); NO merge act; the one remedy = the operator re-issues in the 045944 shape FROM operator TO intg.pair-implementer, bare token, MERGE_STATUS AUTHORIZED transporting 194922; record hygiene: EIGHT implementer relays untracked, not five; HOLDING

## The conflict, measured (all at my own read, 2026-09-04 ~20:05)

```text
194922 face      MERGE_STATUS: AUTHORIZED · TO: intg.pair-planner · FROM: operator · "lgtm" quoted · packet sha 2926cf1a51b73bef… == results/intg-substep2a-merge-gate.md at my seat
                 grep -c for the bare merge-token line alone on its own line → 0   (no operative token line; the relay is an AUTHORIZATION, not a token)
                 mechanics clause: "authorizes the pair-planner to issue the BARE merge token in-lane to intg.pair-implementer"
the rule         relay-lint.py:1163  <the merge token> requires TO to be exactly one implementer-role address
                 relay-lint.py:1169-1170  if from_low not in {"operator","orchestrator"} and address_role(from_addr) != "orchestrator-planner":
                                            error "<the merge token> FROM must be operator, orchestrator, or an orchestrator-planner-role address"
                 relay-lint.py:804  master-tier seat may not carry <the merge token>: execution authority never enters the master tier
the probes       (synthetic, /tmp only, never in the root; my 190043 header → PHASE MERGE-GATE / AUTHORITY merge-gated / TO intg.pair-implementer / bare token line)
                 FROM intg.pair-planner      → ERROR :1170   (must-fail: CONFIRMED)
                 FROM master.master-planner  → ERROR :804 + ERROR :1170
                 FROM operator               → no :1170 / :804 error (the only error = my probe's ROLE/FROM proxy-author artifact)
the positive     intg-substep1-merge-token/MERGE-GATE-operator-20260829-045944.md — FROM operator · TO intg.pair-implementer · MERGE_STATUS AUTHORIZED · 1 bare token line · consumed by 81066ef
consequence      a pair-planner-FROM token cannot file (daemon gate); a master-FROM token cannot file; no orchestrator seat exists in this run → the operator's seat is the only compliant issuer
```

## Remedy (the choice is the operator's/yours; the authorization of record is untouched)

```text
R1 (the 045944 shape, the only compliant one)  ONE operator-seat re-issuance: PHASE MERGE-GATE · AUTHORITY merge-gated · FROM operator · TO intg.pair-implementer (exactly one) ·
    MERGE_STATUS: AUTHORIZED — transporting the standing 194922 decision · IN_REPLY_TO the 194922 carrier · the bare token alone on its own line ·
    carrying the record-hygiene clause to its addressee (the EIGHT untracked implementer relays committed no later than the landing:
    IMPL 181132 181438 181612 222330 062639 · PLAN-REVIEW 210020 225905 043346)
then  the implementer merges per packet §4 (true merge; parents main-before + a2f6fd1; merge-tree re-derived immediately before; product-root diff candidate..merge EMPTY;
      tags + origin/main untouched) → landed sha + receipts UP through me → I re-verify every cell → packet §8 → the count-gate token issues
```

ACTIONS_GIT_REF: docs-lane writes only — this STOP via the engine; ROADMAP's cell-4 entry; commit path-scoped follows; the three probe files lived in /tmp and are removed; no merge, no product byte, no ref move, no push, no PR, no release act at any seat
RELAY_LINT: engine-rendered submission; per-file v2.9.2 lint rides the daemon gate; the draft pre-linted per-file; the grantor rule measured at the linter's source and by the three-probe discriminator; every upstream route directory and every pair cycle directory re-listed immediately before submit
FINAL_GIT_STATUS_SHORT:
 M .relays/intg/INDEX.md
 M docs/sprints/2026-08-27-intg-consent-fabric/ROADMAP.md
 ?? .relays/intg/.engine/drafts/intg.pair-planner/MERGE-GATE-STOP-TRANSPORT-GRAMMAR-2A-TOKEN.md
Literal path-scoped status for this seat's own writes at authoring time; the shared bivpak tree additionally carries sibling-authored state not claimed clean here.
