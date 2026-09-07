## SITREP — STOP UP on the R-4.50 act (implementer `201740`, under token 2 at Task 1 Step 5): S-CP-2 HAS FIRED AT THE CANDIDATE'S ACCEPTANCE GATE, NOT AT LANDING — and the surface that fired is a THIRD harness file the pre-stated follow-through does not name. The facts, re-derived at my bytes: the candidate's `claude_code.cpp` is EXACTLY the plan's Step 4 body (byte-equal; every byte outside :570-594 identical to `bbf297e`), the witness is RED-then-GREEN as the plan requires (ROW 1 + ROW 5 red at the base; all five green after; the existing case green), Task 0 is fully green under rev5 (the venv, the fresh cache, `rc1=8 rc2=0 iff=pass hygiene=pass`) — and the first workflow-equivalent macOS suite returns rc 8 because `harness-selftest` reports 53 failures. THE MECHANISM: `harness/bivharness/e3.py:72-81` `_ADAPTER_SOURCE_ANCHORS` pins the WHOLE-FILE sha256 of `src/adapters/claude_code/claude_code.cpp` (`cd1f8bc8…` == the file at `bbf297e`, verified) as the C1 drift tripwire; `_c1_drift_tripwire_failures` (`:2382-2395`) reds on ANY byte change, `test_drift_tripwire_is_green_at_pinned_source` (`test_e3_asserts.py:1883`) fails directly, and every E3 scenario is marked INVALID at `e3.py:3018-3020` — the 53 failures are one root. The candidate file hashes `4e105052a17b7e0d99bfeca28ac45cac1f6ed3c5ba0e9ba9ec62a34e530a3a51` (P's bytes; C's product bytes are identical by construction). THE GAP: m-3's S-CP-2 follow-through, as pre-stated (iso rev6 :193-196; RESIDUALS C-1 "shape (A)"), has the write set EXACTLY `harness/selftest/stub_biv.py` + `harness/selftest/test_store_isolation.py` — the `e3.py` pin is not in it, yet it is the byte that reds the suite. THE TIMING: the fence says S-CP-2 "fires AT LANDING" and m-3 ruled "no red window"; but `harness-selftest` is a row of the CI macOS AND Linux jobs and of the local parity leg, so the pair's own acceptance (rev5 Task 1 Step 5 and Task 4: the workflow-equivalent suite rc 0 at P and at C) cannot be green until the harness moves — and the harness may move only under m-3 (V-CP-5). The pair cannot resolve this; it is routed UP the fence's own path. The two in-scope unstaged paths and the evidence are PRESERVED at the implementer's worktree (no P, no Linux run, no transcription); token 2 is consumed at the STOP.

ROLE: Pair Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: intg-r450-discover-parity
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: intg-r450/SITREP-pair-implementer-20260906-201740.md
RELATED_CONTEXT: intg-r450/IMPL-pair-planner-20260906-194721.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/DESIGN-m2-planner-20260903-142000.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/DESIGN-m2-planner-20260903-144700.md; ../../pdc/master/domains/m-3-restore-cli/design/2026-09-01-e2-store-isolation-r437.md; ../../pdc/master/relays/intg-r450-discover-parity-act/PLAN-master-planner-20260906-004023.md; ../../pdc/master/relays/intg-r450-discover-parity-act/PLAN-master-planner-20260906-015102.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-r450-discover-parity-20260906.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — a cross-domain STOP (S-CP-2, owner m-3; the vehicle question is master's): the follow-through's write set must be corrected by its owner and the landing shape ruled before the pair can author rev6; no harness byte, no exclusion, no waiver in-lane; the release hold is ABSOLUTE.
COMMISSION_ID: intg-consent-fabric
COMMISSION_SCOPE: the operator-authorized integration phase (2026-08-26) executed by ONE commissioned pair — sub-step 1 first, the A6 rev14 consent-UX fabric with the engine unwired per the sealed spine; subsequent sub-steps (format act consuming LOCKED M rev8 + LOCKED N; then wiring at product scope) each behind their standing gates incl. m-4's reachability re-review before any wiring; sealed design only; STOPs route UP; no merge/push/publication/release authority
COMMISSION_TO: intg.pair-planner
CHARTER_DOC_ID: CH-intg-consent-fabric
FROM: intg.pair-planner
TO: master.master-planner
CC: operator, master.master-reviewer, m-3.planner, m-3.implementer, m-2.planner, m-2.implementer, intg.pair-implementer
SUBJECT: SITREP — STOP UP: S-CP-2 fired at the candidate's acceptance gate (harness-selftest 53 failures: the e3.py whole-file C1 drift pin on claude_code.cpp, cd1f8bc8 == bbf297e; candidate file 4e105052), a third harness surface outside m-3's pre-stated two-path follow-through; the pair's suite gate cannot be green until the harness moves and only m-3 may move it; arms framed (recommend ONE PR, two owners' commits C + H, acceptance at the PR head); candidate bytes verified == plan; token 2 consumed; worktree preserved
REPO: `../bivpak` docs lane; the implementer's worktree READ-ONLY at my seat (hashes and a byte comparison only): `claude_code.cpp` body == plan Step 4 block; outside-body bytes == `bbf297e`; numstat 12/13 + 183/0; SECTION labels ROW 1–5 (the ROW 5 label carries the implementer's plan-authorized one-token repair: the colon moved before the parenthetical so `witness.py`'s first-colon split reads `ROW 5` — a defect in MY synthetic validation, which used `ROW n: x` labels instead of the plan's own strings; folded in rev6). `../pdc` READ-ONLY.
BRIDGE: intg.pair-planner → master.master-planner (the STOP goes UP the fence's path; m-3 owns the harness surface and the follow-through's write set; you own the vehicle); m-3 seats CC (the pin `e3.py:72-81` is yours and is not in your pre-stated two-path set; the read-side mutant rows' anchor strings all survive in the candidate — `.path = root / "projects"`, `std::vector<Store> stores;`, the globs — so only the pin and the stub/isolation model need to move); m-2 seats CC (the product body is the reference shape byte-for-byte; nothing of yours is asked); operator CC (no gate of yours; the vehicle question is master's under R-4.51 clause (2)/R-4.52); intg.pair-implementer CC (hold: preserve the two unstaged paths and the evidence; nothing moves until the ruling)

## The collision, precisely

```text
fence      S-CP-2 (142000 :60): CROSS-DOMAIN, "fires AT LANDING": m-3's L1 stub transcribes today's early-return … the
           pair NEVER fixes the stub or harness in-lane; the landing relay routes the follow-through to m-3. V-CP-5: any
           harness/stub/witness byte = red.
m-3        C-1 ruling (RESIDUALS): shape (A) — a two-path harness act (stub_biv.py + test_store_isolation.py) under m-3's
           byte review at R-4.50's landed sha; "no red window". iso rev6 :193-196: write set EXACTLY those two files.
reality    e3.py:72-81 _ADAPTER_SOURCE_ANCHORS pins sha256(claude_code.cpp) == cd1f8bc8… (== the file at bbf297e, verified);
           _c1_drift_tripwire_failures (:2382) reds on ANY change; test_drift_tripwire_is_green_at_pinned_source fails and
           every E3 scenario returns INVALID (:3018-3020) → harness-selftest 53 failed / 961 passed → ctest rc 8.
           harness-selftest is a row of BOTH CI jobs and of the local parity leg (the workflow-equivalent suite).
plan       rev5 Task 1 Step 5 / Task 4 Step 1: the workflow-equivalent macOS suite under OBS_ENV rc 0 at P and at C; a red
           = FINDING UP, never an exclusion (CG-R3: -E is platform-instrument-only) — the implementer stopped correctly.
gap        (1) the pin is a THIRD harness file outside m-3's write set; (2) "at landing" cannot hold: the candidate is red
           before it lands, on both targets, until the pin moves; (3) the pin's new value is knowable NOW —
           4e105052a17b7e0d99bfeca28ac45cac1f6ed3c5ba0e9ba9ec62a34e530a3a51 (P's claude_code.cpp; C's product bytes are
           identical, only the two workflow literals differ P→C).
```

## Arms for the owner and for master (the pair recommends A; it decides none)

```text
A  ONE PR, TWO OWNERS, TWO COMMITS: the pair's C (product body + test + the two count cells) and m-3's H (stub_biv.py +
   test_store_isolation.py + the e3.py pin = sha256 of C's claude_code.cpp), H authored against P's product bytes on the
   same branch; the acceptance gate (the workflow-equivalent suite, both targets) runs at the PR HEAD (C+H) and is the gate
   of record; m-2 reviews C's fenced bytes, m-3 reviews H and the C→cells hunk; the landing pushes both; no red window
   anywhere. Cost: rev6 re-sequences Task 1 Step 5 / Task 4 to the PR head and the count-gate observation stays at P/C
   (Catch2 binaries — harness-selftest is not a census binary, the cells do not move with H).
B  m-3 lands H FIRST on main (pin = the future bytes): main's harness-selftest is RED from H until C lands — a red window
   the C-1 ruling forbids. Rejected on the record unless m-3 says otherwise.
C  the pair's local acceptance excludes harness-selftest for this act (-E) and H follows C: the PR's CI and main are red
   between C and H; CG-R3 admits -E for platform-instrument ABSENCE only. Rejected on the record unless ruled.
D  m-3 folds the pin into the pair's commit C (a harness byte in a fenced product commit): V-CP-5 red; the pair will not.
```

## What the pair holds and will fold regardless of the arm (rev6, filed only after the ruling)

```text
- the implementer's worktree: the two in-scope unstaged paths (verified == the plan), the venv, the fresh cache, the
  evidence home 16Y21z; no P, no Linux observation, no transcription, no push; token 2 CONSUMED at the STOP
- rev6 folds: (i) the ROW 5 SECTION label spelled so the parser's first-colon split reads "ROW 5" (the implementer's
  repair, now the plan's text) and witness.py validated against the plan's OWN labels; (ii) the deletion form admits a
  status-captured `mv` into the evidence home as the equivalent when the executing wrapper refuses `rm -rf` (the absence
  postcondition is what matters); (iii) whatever the ruling says about the acceptance gate's head and H's presence
- nothing else moves: helpers, product body, witness rows, B/P/C, the vehicle, the landing rule
```

ACTIONS_GIT_REF: docs-lane writes only — this relay via the engine (committed path-scoped with the implementer's STOP relay); no product byte at this seat; the implementer's worktree read only (two hashes, one byte comparison, one label grep)
RELAY_LINT: engine-rendered submission; per-file v2.9.2 lint rides the daemon gate (pre-linted per-file; the four commission-surface lines copied byte-for-byte from the grant)
FINAL_GIT_STATUS_SHORT:
?? .relays/intg/.engine/drafts/intg.pair-planner/SITREP-R450-STOP-UP-HARNESS-TRIPWIRE-SCP2-EARLY.md
?? .relays/intg/intg-r450/SITREP-pair-implementer-20260906-201740.md
Literal path-scoped status for this seat's own writes at authoring time (the STOP relay is the implementer's, uncommitted at their seat; it commits with this filing); the shared bivpak tree additionally carries sibling-authored state not claimed clean here.
