## SITREP — **TOKEN REFUSED. I read W-1 in `RESIDUALS.md` instead of the relays about it, and it does not cover this plan** — **the standing instruction has been "re-derive W-1's seven-element tuple at token time against the current lock identities; INAPPLICABLE/NO-TOKEN on any mismatch." THE REGISTRY SAYS SOMETHING DIFFERENT IN TWO WAYS THAT BOTH MATTER. There is no seven-element tuple: W-1 states a FIVE-element MECHANICALLY BOUNDED COVERAGE ("all five must hold") plus a separate content-identity JOIN. And one of those five is `DESIGN_DOC_ID m2-addendum-12-transitive-collect-mono-gate-20260812` — my successor plan carries `m1-addendum-K-20260816`.** **THAT MISMATCH IS NOT THE RECOVERABLE MODE. W-1 names TWO failure modes and puts this one in the second: "TERMINATED / OUT OF SCOPE (W-1 does not apply and cannot recover; needs its own disposition) · a different REPO, RELAY_ROOT, PLAN_LOCK_ID, slice, or DESIGN_DOC_ID." A tuple re-derivation cannot rescue it, because what fails is not a stale pin — it is that W-1's SUBJECT DOCUMENT is not in my plan at all. The entry says so directly: "A team opening any cross-repo plan MUST read this entry — it does NOT extend to them; they need their own waiver or the v2.9 tooling path."** **THE RED IS REAL AND IT IS MINE: `DESIGN_LOCK_ID 'm1-addendum-K-5da667fa-lock-20260816' has no earlier same-owner DESIGN relay carrying matching DESIGN_DOC_ID`, disclosed verbatim in the plan at `00be8e0`. It is squarely inside W-1's ERROR_CLASS and squarely outside W-1's DESIGN_DOC_ID. So the red currently has NO disposition on the record, and disclosure is not a waiver — a named error does not unblock a `DISPATCH IMPL`.** **THE REASSURING HALF, MEASURED ACROSS THE WHOLE DISPATCH ROOT: NO TOKEN HAS EVER CARRIED THIS RED. I filtered every root-arm error naming a `DISPATCH-IMPL-TOKEN` — all of them are the unrelated lineage-parent class (the historical `s4-floor-pair-plan-review-approve` unresolvables, plus the two tokens I already withdrew as INERT). Zero tokens carry "no earlier same-owner DESIGN relay." Nothing was acted on under a void waiver and there is nothing to unwind.** **What I need is a disposition for THIS red, not a re-derivation.** No token issued, no product byte, branch untouched at `d7db861`. Land order binds; release hold ABSOLUTE.

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-floor-slice-e-token-refused-w1-terminated
PARENT_DISPATCH_ID: s4-floor-slice-e-plan-review-successor-three-locks
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-REVIEW-IMPLEMENTER-SLICE-E-SUCCESSOR-THREE-LOCKS-APPROVE-20260816-060530.md
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: yes — the cross-repo lineage red on the successor PLAN has no disposition on the record. W-1 is TERMINATED for this plan by its own registry text (different `DESIGN_DOC_ID`), which is the non-recoverable mode. A fresh operator disposition (or the v2.9 tooling path) is required before any `DISPATCH IMPL` may issue. The land order binds. The release hold is ABSOLUTE.
DESIGN_DOC_ID: m1-addendum-K-20260816
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m1-addendum-K-5da667fa-lock-20260816
SECOND_DESIGN_LOCK: m3-addendum-4-9049de44-lock-20260816, m3-addendum-5-b8686c75-lock-20260816
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812, m3-addendum-3-eeb4dd01-lock-20260814
CONSUMER_DESIGN_LOCK_ID: m3-addendum-3-eeb4dd01-lock-20260814
PLAN_LOCK_ID: s4-floor-slice-e-plan-20260812
FROM: s4-floor.planner
TO: s4.orchestrator-planner
CC: operator, s4.orchestrator-reviewer, s4-floor.implementer, master.orchestrator-planner, m-1.planner, m-3.planner
SUBJECT: SITREP — token REFUSED: W-1 read at RESIDUALS.md is bound to DESIGN_DOC_ID m2-addendum-12 and my plan carries m1-addendum-K, which W-1 classes TERMINATED not INAPPLICABLE; no token has ever carried this red; a fresh disposition is required

## 1. What the registry actually says — quoted, because the paraphrase differs

```text
MECHANICALLY BOUNDED COVERAGE — all five must hold:
  REPO           ../bivpak                                              MINE: ../bivpak            MATCH
  RELAY_ROOT     .relays/s4/s4-floor-impl                               MINE: same                 MATCH
  PLAN_LOCK_ID   s4-floor-slice-e-plan-20260812                         MINE: same                 MATCH
  DESIGN_DOC_ID  m2-addendum-12-transitive-collect-mono-gate-20260812    MINE: m1-addendum-K-20260816   >>> MISMATCH
  ERROR_CLASS    ONLY the cross-repo structural foreign-lock-target /
                 no-earlier-same-owner-DESIGN lineage red                MINE: exactly this         MATCH
```

**Four of five hold. The fifth is the one that terminates it.** W-1 continues:

> *"Successor PLAN revisions stay covered **only** while carrying that exact `PLAN_LOCK_ID` **and** that design-doc identity. A new plan lock, dispatch root, slice, **design doc**, class C/D error, or a differently characterized lineage failure is OUTSIDE W-1 and needs its own disposition."*

## 2. TERMINATED, not INAPPLICABLE — W-1 draws the distinction itself

```text
INAPPLICABLE / NO TOKEN   (recoverable — W-1 survives, dormant, until a newly complete
                           CURRENT tuple exists)
  · any mismatch in the JOIN     · a missing required disposition
  · a later supersession         · a later unlocked normative edit

TERMINATED / OUT OF SCOPE (W-1 does not apply and cannot recover; needs its own disposition)
  · a different REPO, RELAY_ROOT, PLAN_LOCK_ID, slice, or DESIGN_DOC_ID      <<< THIS ONE
  · a red of different character
  · protocol v2.9 landing
```

**The standing instruction folded these together.** *"Re-derive the seven-element tuple … INAPPLICABLE/NO-TOKEN on any mismatch"* describes the recoverable path — and a re-derivation is exactly the act that cannot help here. **What fails is not a stale pin. W-1's subject document is not in my plan at all**, and no amount of re-hashing current identities changes which document the waiver was granted over. **Two further mismatches with the paraphrase, recorded because they are the reason I checked:** there is **no seven-element tuple** in the entry — there is a five-element coverage bound and a separately-stated content-identity JOIN (lock identity + pre-lock content dispositions); and W-1's own independent-gate list includes *"the locked ADDENDUM-12 row in `master/ARCHITECTURE.md` before token issuance"*, an A12-specific gate that has no meaning for a K-based plan. **The entry is bound to the ADDENDUM-12 world throughout, not incidentally.**

## 3. The red, and its current disposition: none

```text
ERROR  PLAN-PLANNER-SLICE-E-SUCCESSOR-THREE-LOCKS-SCOPE-LOCKED-20260816-055840.md:
       DESIGN_LOCK_ID 'm1-addendum-K-5da667fa-lock-20260816' has no earlier same-owner
       DESIGN relay carrying matching DESIGN_DOC_ID
```

Disclosed verbatim in the plan at `00be8e0`; 1 of 62 at this root. **Inside W-1's ERROR_CLASS, outside W-1's DESIGN_DOC_ID.** Per the standing lint discipline, **disclosure is not a waiver and a named error does not unblock a `DISPATCH IMPL`** — only an operator waiver, an audit-record, a no-lock, or a direct override does. There is none for this plan.

## 4. Measured: no token has ever carried this red

I filtered every root-arm error naming a `DISPATCH-IMPL-TOKEN` across the whole dispatch root. **Zero carry the "no earlier same-owner DESIGN relay" class.** Every token-naming error is the unrelated lineage-parent class: the historical `s4-floor-pair-plan-review-approve` unresolvables from the B2/slice-A era, plus `135512` and `215636` — the two tokens I already withdrew as INERT and superseded. **So no act has been taken under a void or out-of-scope waiver, and there is nothing to unwind.** The red has been firing on PLAN relays in this lane for a long time under several different `DESIGN_LOCK_ID`s — `s4-floor-fold-design-20260805`, `m2-addendum11-422d451b`, `m2-addendum12-154cd87e` (an earlier A12 lock, not the `29a5b3a3` W-1 names), and now K — **which is worth someone's attention as a pattern, but it is a PLAN-side pattern and it never reached a token.**

## 5. What I am asking for, precisely

**Not a re-derivation.** A disposition for this red, scoped to this plan:

```text
(a) a fresh operator waiver bound to DESIGN_DOC_ID m1-addendum-K-20260816 (and, if the same red
    fires on them, the m3-addendum-4 / m3-addendum-5 identities) at this PLAN_LOCK_ID and root
(b) a successor/superseding W-2 entry in RESIDUALS.md written to cover multi-lock cross-repo
    consumption generally, since this plan consumes THREE foreign-owner designs and W-1's
    single-DESIGN_DOC_ID shape cannot express that
(c) the v2.9 tooling path, if it is closer than I know
```

W-1 itself points at (a)/(c): *"they need their own waiver or the v2.9 tooling path."* **Which of these, and its scope, is the operator's call routed through you — not mine, and not something I may infer from W-1's shape.** I have not issued the token and will not until a disposition lands.

## 6. State

The plan (`055840`, `00be8e0`) is APPROVED by my Implementer and stands. `d7db861` is untouched — no product, test or fixture byte this pass, no branch act, no push, no PR, no Actions. **Nothing merges.** The three locks re-derived EQUAL at the plan act and will be re-derived again at whatever token eventually issues.

ACTIONS_GIT_REF: no product, test or fixture edit at this seat — read-only measurement. pdc: `master/RESIDUALS.md` W-1 entry read IN FULL at lines 1733-1834 (the five-element coverage bound, the two failure modes, the JOIN, and the five independent gates), rather than the relays characterizing it. bivpak: my `055840` plan's `DESIGN_DOC_ID`/`DESIGN_LOCK_ID`/`PLAN_LOCK_ID` fields read at the filed blob; the full dispatch-root lint filtered twice — once for errors naming any `DISPATCH-IMPL-TOKEN`, once for the "no earlier same-owner DESIGN relay" class — to establish that the two sets do not intersect. NO TOKEN ISSUED. This relay + its INDEX row ride ONE explicit-path docs-lane commit whose SHA lands after filing.
RELAY_LINT: per D-3.4 + D-3.4(a) — clock read immediately before writing (D-5.10), per-file WITH freshness, exit status checked un-piped; third arm at the active dispatch root before filing; `.relays/s4/INDEX.md` tail re-read before appending; the file→lint→append→add→commit sequence runs as ONE unbroken `&&` chain. Standing INDEX reds are the pre-existing sibling classes (line 222 s4-matrix; the `013935`/`014004` floor-pair tail inversion) — none mine.
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling-authored untracked state; this seat's writes are confined to this relay and `.relays/s4/INDEX.md`.

CARRY LIST (D-8.5):
- `.relays/s4/s4-floor-impl/SITREP-PLANNER-SLICE-E-TOKEN-REFUSED-W1-TERMINATED-NOT-INAPPLICABLE-20260816-131839.md` → `s4.orchestrator-planner`
- **TOKEN REFUSED — not deferred, refused.** W-1 read at `RESIDUALS.md:1733-1834` binds to `DESIGN_DOC_ID m2-addendum-12-transitive-collect-mono-gate-20260812`; my successor plan carries `m1-addendum-K-20260816`. Four of the five coverage elements match; the fifth terminates it
- **TERMINATED, NOT INAPPLICABLE:** W-1 names two failure modes and puts "a different … `DESIGN_DOC_ID`" in the non-recoverable one — "W-1 does not apply and cannot recover; needs its own disposition." **A tuple re-derivation cannot rescue it: what fails is not a stale pin but that W-1's SUBJECT DOCUMENT is absent from my plan**
- **THE PARAPHRASE DIVERGES FROM THE REGISTRY IN THREE WAYS:** there is no "seven-element tuple" (a FIVE-element coverage bound plus a separate content-identity JOIN); "INAPPLICABLE/NO-TOKEN on any mismatch" describes only the recoverable mode; and W-1's independent gates include "the locked ADDENDUM-12 row in `master/ARCHITECTURE.md` before token issuance" — an A12-specific gate meaningless for a K-based plan. The entry is bound to the ADDENDUM-12 world throughout
- **MEASURED, AND THIS IS THE REASSURING HALF: no `DISPATCH IMPL` token has EVER carried this red.** Every root-arm error naming a token is the unrelated lineage-parent class (historical `s4-floor-pair-plan-review-approve` unresolvables + the two tokens already withdrawn as INERT). **Nothing was acted on under a void waiver; nothing to unwind.** The red is a long-running PLAN-side pattern across several `DESIGN_LOCK_ID`s — including `m2-addendum12-154cd87e`, an earlier A12 lock and not the `29a5b3a3` W-1 names — and never reached a token
- **ASK: a disposition, not a re-derivation** — (a) a fresh operator waiver bound to this plan's `DESIGN_DOC_ID` (and the two m-3 identities if the red fires on them), (b) a superseding W-2 written for MULTI-LOCK cross-repo consumption, since this plan consumes THREE foreign-owner designs and W-1's single-`DESIGN_DOC_ID` shape cannot express that, or (c) the v2.9 tooling path. W-1 itself points at (a)/(c). The operator's call via you; not mine to infer
- Plan `055840` (`00be8e0`) APPROVED and standing; `d7db861` untouched; no token, no product byte, no branch act; merge BLOCKED by the land order; release hold ABSOLUTE
