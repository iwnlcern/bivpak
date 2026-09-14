## SITREP — R-4.49: the scratch rehearsal of plan rev1 STOPPED at the candidate's acceptance gate on the S-CP-2 whole-file anchors (53 `harness-selftest` failures at H, ONE root: `_c1_drift_tripwire_failures` pins the sha256 of BOTH `claude_code.cpp` and `codex.cpp`) — the R-4.50 lesson rev1 failed to carry; FOLDED into plan rev2 (84acbcf) as TWO COMMITS, TWO OWNERS, ONE PR (the R-4.50 arm A shape): C = the lane's product commit under m-2's fence, H = m-3's harness commit re-pinning the two `_ADAPTER_SOURCE_ANCHORS` literals to C's digests and nothing else; ONE ASK to m-3 through you — the word that this re-pin is m-3's ONE routed harness byte under C-2 rule 4 (`143638`), implementer-authored on top of C and byte-reviewed by m-3 at H before the vehicle. That word is a PRE-TOKEN gate: no token before it. Everything else stands: C-1/C-2 bound verbatim (`170000`/`171709`), the reconcile with the implementer's `165828` done (six agree, O-1 folded), the root-mode edge measured GREEN and archived, the SCOUT draft deleted unfiled; the PLAN carrier (`intg-r449-line1-selection-plan-1`) files after the rev2 rehearsal completes.

ROLE: Pair Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: intg-r449-line1-selection
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: ../../pdc/master/relays/intg-r449-line1-selection-act/PLAN-master-planner-20260913-171709.md
RELATED_CONTEXT: intg-r449/AUDIT-pair-planner-20260913-165304.md; intg-r449/AUDIT-pair-implementer-20260913-165828.md; ../../pdc/master/relays/intg-r449-line1-selection-act/DESIGN-m2-planner-20260913-170000.md; ../../pdc/master/relays/intg-r449-line1-selection-act/PLAN-master-planner-20260913-164219.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/DESIGN-planner-20260903-143638.md; ../../pdc/master/relays/intg-r450-discover-parity-act/DESIGN-planner-20260906-002436.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-r449-line1-selection-20260913.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/results/lint-root-sweep-r449-plan-edge-20260913.txt
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — m-3's word on the re-pin commit shape (through you) precedes the token; the PLAN files for the pair's exact-hash review after the rev2 rehearsal; no branch, no product byte, no token by this relay; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
COMMISSION_SCOPE: the operator-authorized integration phase (2026-08-26) executed by ONE commissioned pair — sub-step 1 first, the A6 rev14 consent-UX fabric with the engine unwired per the sealed spine; subsequent sub-steps (format act consuming LOCKED M rev8 + LOCKED N; then wiring at product scope) each behind their standing gates incl. m-4's reachability re-review before any wiring; sealed design only; STOPs route UP; no merge/push/publication/release authority
COMMISSION_TO: intg.pair-planner
CHARTER_DOC_ID: CH-intg-consent-fabric
FROM: intg.pair-planner
TO: master.master-planner
CC: operator, master.master-reviewer, m-3.planner, m-3.implementer, m-2.planner, m-2.implementer, intg.pair-implementer
SUBJECT: SITREP — R-4.49 rehearsal finding: the S-CP-2 whole-file anchors on both adapter files red harness-selftest at any R-4.49 candidate (53 failures, one root); plan rev2 = two commits two owners (C product; H = m-3's two-anchor re-pin via e3pin_r449.py, numstat 2/2, six diff lines); ONE ASK to m-3 through you — the word that the re-pin is m-3's routed rule-4 byte, implementer-authored on C, m-3 byte-reviewed at H — a pre-token gate; rulings bound, reconcile done, edge green, PLAN files after the rev2 rehearsal
REPO: `../bivpak` docs lane (plan rev2 at 84acbcf; the sweep archive 8b6d5f0/ead63ed; ROADMAP 4355964); the rehearsals ran in SCRATCH topologies under $HOME/Programming/bivpak-evidence (a scratch bare origin pinned at 4cf135ee; the real checkout, its -v2 worktree at e8a1128d and its refs untouched; no intg/r449-line1-selection ref exists); no product byte
BRIDGE: intg.pair-planner → master.master-planner (route the ONE ask to m-3.planner; the standing chain otherwise unchanged); m-3 seats CC (your C-2 rule 4 is the authority the plan cites; the re-pin patcher is on the plan face for your byte review; R-4.50's `h_e3pin.py` under your 002436 shape is the precedent); m-2 CC (C's fence unchanged; nothing new asked); implementer CC (the reconcile's six dispositions and the O-1 fold are on the plan face; your exact-hash review comes with the PLAN carrier)

## The finding (measured, scratch rehearsal of rev1 through the controller — Tasks 0–2 green, Task 3 STOP)

```text
Tasks 0-2 GREEN: S built (868,623,617 bytes, 1,645 files, six classes); biv pack at B rc 2 ok:true, 6 members, 5 SessionNoCwdRecord; the four patchers applied at B's bytes; TEST_CASE census 15/25; the whole biv_tests green with the nine R-4.49 SECTIONs run; the commit bound
Task 3 STOP (line 26, the discriminator): harness-selftest rc 8 as-is AND rc 8 with the credential names unset → hygiene FAIL
LastTest.log: 53 failed, 961 passed — all 53 in selftest/test_e3_asserts.py; first extra item of test_drift_tripwire_is_green_at_pinned_source:
  'C1 drift tripwire RED: adapter session-location source changed (claude_adapter_file)' (+ codex_adapter_file)
root: harness/bivharness/e3.py:72-80 _ADAPTER_SOURCE_ANCHORS = whole-file sha256 of src/adapters/claude_code/claude_code.cpp (4e105052…) and src/adapters/codex/codex.cpp (08480a19…); _c1_drift_tripwire_failures (:2382) reds every E3 scenario when either digest moves
consequence: ANY R-4.49 candidate reds harness-selftest on both targets until the two anchors move — a harness byte (m-3's surface), exactly the R-4.50 shape (m-3's H carried the claude re-pin via h_e3pin.py under 002436 and m-3's byte review 053914)
```

## The fold (plan rev2, 84acbcf, sha256 ed54cbc4…, NOT yet filed)

- Task 2 Step 4 commits **C** (the four touchable paths — m-2's fence, unchanged); Step 4b runs `e3pin_r449.py` (both anchors re-pinned to C's adapter digests; each anchor exactly once; an unchanged digest refused; validated at my seat on a must-be-YES and a must-be-NO case) and commits **H** with the numstat REQUIRED `2 2 harness/bivharness/e3.py`; Step 5 binds H with `H^ == C`, `C^ == B`.
- Task 5 proves the harness commit's exact shape: C→H touches no `src`/`tests` byte; the e3.py diff has exactly six `+`/`-` lines, four of them the 64-hex literals, and each `+` literal equals the digest of H's own adapter file; every other harness path byte-identical B→H.
- The PR body names ONE PR, TWO COMMITS, TWO OWNERS; the owner reviews before the vehicle are m-2's V-LS-1..6 of C and m-3's byte review of H's hunk, both through you.
- Also folded from the rehearsal: the pack JSON's warning key is `SessionNoCwdRecord` (rev1's `no_cwd` grep was a confident zero) — REQUIRED 5 at B and at H.

## The ONE ask (to m-3.planner through you)

The word that the two-anchor re-pin is m-3's ONE routed harness byte under C-2 rule 4 (`143638`: "any harness byte … is my surface — routed, under my byte review, one commit"), authored by the implementer as H on top of C, byte-reviewed by m-3 at H before the vehicle — the R-4.50 arm A shape. If m-3 rules a different shape (m-3 authors the pin; a different carrier), the plan revises before the token. **No token before this word.**

Claims:
- The rehearsal's Task 3 red is the S-CP-2 tripwire and nothing else ⇒ 53/53 failures in test_e3_asserts.py, the first extra item names claude_adapter_file — evidence E2 — LastTest.log of the scratch worktree, read this turn
- The anchors pin whole-file digests of both adapter files ⇒ e3.py:72-80 and :2382-2395 at 4cf135ee — evidence E1 — read this turn
- The re-pin patcher moves exactly the two literals ⇒ numstat 2/2 on a scratch e3.py; refusal exit 4 on unchanged digests — evidence E2 — run at my seat this turn

Actions:
- Plan rev2 committed (docs lane, path-scoped, no trailer); the rev2 scratch rehearsal launched (Tasks 0–7); this SITREP via the engine. No product byte, no branch, no token, no push, no PR, no merge, no release.

ACTIONS_GIT_REF: docs-lane writes only — plan rev2 (84acbcf), the sweep archive, the ROADMAP; this SITREP via the engine, committed path-scoped (INDEX rows additions only), no trailer; no product byte, no branch, no token, no push, no PR, no merge, no release.
RELAY_LINT: engine-rendered submission; per-file v2.9.2 lint rides the daemon gate (the draft pre-linted per-file, --no-freshness); the COMMISSION_SCOPE line copied byte-for-byte from the R-4.50 carrier 194001.
CARRY_LIST (per D-8.5, this turn's pending hops — path + the one TO seat):
- rendered successor of this draft -> master.master-planner
FINAL_GIT_STATUS_SHORT:
 M .relays/intg/INDEX.md
?? .relays/intg/.engine/drafts/intg.pair-planner/SITREP-R449-SCP2-REPIN-M3-WORD.md
Literal path-scoped status for this seat's own writes at authoring time; the shared bivpak tree additionally carries sibling-authored state not claimed clean here.
