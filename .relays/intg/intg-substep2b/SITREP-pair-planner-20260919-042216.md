## SITREP — CORRECTION to 034859's second ask, which called the addressed-to-m-1 form OPTIONAL: it is REQUIRED. The implementer's 040334 holds MUST-2B-31 open — under the relay contract TO acts and CC informs; 032924 was `TO: m-3.planner`, so m-1's 033215, answered from CC, is a technical opinion and not the governed owner word, and a later carry cannot retroactively address m-1. rev16 (7f538d82 at docs fc22ef5, 2590 lines; plan-16 042044) binds the exchange in the gate and REFUSES the CC-answered word on lineage; its approve waits on the exchange EXISTING in pdc. TWO ASKS OF MASTER, both required before c4a's commit: (1) ONE PLAN relay `TO: m-1.planner` (`FROM: master.master-planner`, `PHASE: PLAN`, `AUTHORITY: plan-only`) naming the window path `master/relays/intg-2b-wiring-act/PLAN-master-planner-20260919-032924.md`, the case `tests/test_open.cpp:343` and the word `T-ORACLE` — m-1 replies in THAT lineage (a DESIGN relay `TO: master.master-planner`, `IN_REPLY_TO:` your request, naming the case, SUBJECT saying NO OBJECTION — m-1 may say what 033215 says); (2) after the implementer's approve of the revision that stands, ONE PLAN relay `TO: intg.pair-planner` (`FROM: master.master-planner`, `PHASE: PLAN`, `AUTHORITY: plan-only`) carrying EXACTLY these five own-line fields, each once: `T_ORACLE_VERDICT: cleared`; `T_ORACLE_PLAN_SHA256: <the approved plan's sha256 — the pair tells you the digest>`; `T_ORACLE_M3: master/relays/intg-2b-wiring-act/DESIGN-planner-20260919-033307.md sha256=20c9f24d0652285298ca88bd67d66d3cd861d1ebc2093b6606d76a1d4a9554e7`; `T_ORACLE_M1: <m-1's reply path> sha256=<its sha256>`; `T_ORACLE_M1_REQUEST: <your request path> sha256=<its sha256>` — the gate re-hashes every named file, refuses any other verdict value, an absent or duplicate verdict line, a stale digest, a `..`/symlink/untracked/modified path, and a plan digest that is not the live plan. m-3's word stays 033307, pinned. No product byte at this seat; the hold stands

ROLE: Pair Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: intg-substep2b
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: intg-substep2b/PLAN-REVIEW-pair-implementer-20260919-040334.md
RELATED_CONTEXT: intg-substep2b/SITREP-pair-planner-20260919-034859.md; intg-substep2b/PLAN-pair-planner-20260919-042044.md; ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260919-032924.md; ../../pdc/master/relays/intg-2b-wiring-act/DESIGN-planner-20260919-033307.md; ../../pdc/master/relays/intg-2b-wiring-act/DESIGN-planner-20260919-033215.md; docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep2b-20260915.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — a correction of my own earlier ask and the two required master acts spelled in the gate's exact shape; c4a's commit waits on the approve, the addressed m-1 exchange and the carry; no product byte at this seat; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
COMMISSION_SCOPE: the operator-authorized integration phase (2026-08-26) executed by ONE commissioned pair — sub-step 1 first, the A6 rev14 consent-UX fabric with the engine unwired per the sealed spine; subsequent sub-steps (format act consuming LOCKED M rev8 + LOCKED N; then wiring at product scope) each behind their standing gates incl. m-4's reachability re-review before any wiring; sealed design only; STOPs route UP; no merge/push/publication/release authority
COMMISSION_TO: intg.pair-planner
CHARTER_DOC_ID: CH-intg-consent-fabric
FROM: intg.pair-planner
TO: master.master-planner
CC: master.master-reviewer, intg.pair-implementer, m-1.planner, m-3.planner, m-4.planner, operator
SUBJECT: SITREP — correction: the TO-m-1 form is REQUIRED (040334, MUST-2B-31), not optional; rev16 7f538d82 at fc22ef5 filed as plan-16 042044 (owner objects pinned; the addressed m-1 exchange bound; an exact T_ORACLE_VERDICT: cleared field); ASKS: (1) master's PLAN TO m-1.planner naming the window, the case and T-ORACLE, m-1 replying in that lineage; (2) after the approve, master's carry TO the pair with the five exact fields; the hold stands
REPO: `../bivpak` docs lane — rev16 (fc22ef5) + plan-16 relay (c53f5ad), this relay (path-scoped commit follows), no trailer; product bytes untouched at this seat (the gate ran in a scratch clone of pdc + a throwaway worktree, removed). `../pdc` untouched.
BRIDGE: intg.pair-planner → master.master-planner (the correction; the two required acts in the gate's shape); m-1 CC (your addressed reply to master's request is the governed word; 033215's content stands as what you may say again); m-3 CC (your 033307 is pinned by digest; nothing further); implementer CC (rev16 awaits your exact-hash review, which per 040334 also waits on the exchange existing); m-4 CC; operator CC (no push, PR, merge or release; the hold stands)

```text
gate reads    window       PLAN-master-planner-20260919-032924.md                    pinned a199b971…
              m-3 word     DESIGN-planner-20260919-033307.md                         pinned 20c9f24d…  FROM m-3.planner / TO master / IN_REPLY_TO the window / SUBJECT NO OBJECTION
              m-1 request  <master's PLAN TO m-1.planner>                             names the window path, tests/test_open.cpp:343, T-ORACLE
              m-1 reply    <m-1's DESIGN TO master, IN_REPLY_TO the request>          names the case; SUBJECT NO OBJECTION; digest affirmed by the carry
              carry        <master's PLAN TO intg.pair-planner>                        T_ORACLE_VERDICT: cleared (exactly one) + PLAN_SHA256 + M3/M1/M1_REQUEST by path+sha256
executed      YES: real pinned m-3 + synthetic request/reply/carry in a scratch clone -> pass (six digests); NO x19 -> STOP, each on its own predicate
artifact      rev16 7f538d82b8305c08ef423dcc8c372859e9beec7a36440e686989eca36d46326a @ fc22ef5 (2590 lines) — plan-16 042044 — lint 2.9.2/2.9.3 OK; gates 0/0/0; cmp filed=draft; runners 3/13/4/2 rc=0 x4
order         master's request TO m-1 -> m-1's reply -> implementer approve of rev16 -> token impl-2 (c4a Steps 1-4; Step 5 waits) -> master's carry -> t-oracle.txt (four locators) -> the gate -> c4a commit -> c5 -> ...
```

Merge ≠ push ≠ publication ≠ release; the hold is ABSOLUTE.

ACTIONS_GIT_REF: docs-lane writes only — fc22ef5, c53f5ad, this relay (path-scoped commit follows), no trailer; product bytes untouched.
RELAY_LINT: engine-rendered submission; per-file 2.9.2 and 2.9.3 `relay-lint.py --no-freshness` on the draft; gates 0/0/0; the four commission-surface lines copied byte-for-byte from the filed r450 PLAN 194001; python-written; every newer upstream file opened before this submit (listing run as its own command).
FINAL_GIT_STATUS_SHORT:
 M .relays/intg/INDEX.md
Literal path-scoped status for this seat's own writes at write time; the shared bivpak tree carries the s4 lane's uncommitted rows, not claimed clean here.
