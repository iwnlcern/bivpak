## AUDIT — R-4.50 claude-discover parity, the pair Planner's read-only pass at bivpak HEAD `8d8b7fa` (product bytes IDENTICAL to the fence's pin `9e1a72d`; 0 commits touch the three files since; `9e1a72d` is an ancestor of `origin/main` `bbf297e`): STILL-OPEN confirmed at `claude_code.cpp:581` (the early `return stores;` inside the env arm of the discover body :570-596) against codex's conforming shape at `codex.cpp:1195-1206`; NO existing test asserts the suppression and NO pack/cli/open test builds a `.claude` under its HOME beside an existing CLAUDE_CONFIG_DIR store, so the fix flips no current test; the open-side consumer keeps `stores->front()` (env-first is preserved in every matrix row — no S-CP-4 interaction); S-CP-2 is LIVE at HEAD (`stub_biv.py:140-146` transcribes today's early return — m-3's, fires at landing). TWO QUESTIONS GO UP BEFORE ANY BYTE, in the companion SITREP to master: Q1 the canonical cross-repo design edge was MEASURED root-mode with a must-be-GREEN control and FIRES structurally (the fence rev2 relay carries no DESIGN_DOC_ID/DESIGN_RECORD_KIND and its only approve is the Master Reviewer's, not an m-2 peer's — no header this seat can write turns it green); Q2 any NEW Catch2 test case moves the count-gate cells in `.github/workflows/s2-harness.yml` (macOS 418, Linux 420), a byte OUTSIDE the fence's TOUCHABLE set on which the fence is silent. Reconcile requested; no plan is filed for review until both return.

ROLE: Pair Planner
PHASE: AUDIT
AUTHORITY: read-only
DISPATCH_ID: intg-r450-discover-parity
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: ../../pdc/master/relays/intg-r450-discover-parity-act/PLAN-master-planner-20260905-212735.md
RELATED_CONTEXT: ../../pdc/master/relays/r437-pack-timeout-diagnosis/DESIGN-m2-planner-20260903-144700.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/DESIGN-m2-planner-20260903-142000.md; ../../pdc/master/relays/r437-operator-scope-ruling/PLAN-operator-20260903-152117.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/DESIGN-REVIEW-master-reviewer-20260903-151001.md; ../../pdc/master/domains/m-2-agent-adapters/design/2026-07-02-adapter-contract-and-session-semantics.md; intg-isolation/PLAN-pair-planner-20260902-194515.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/results/lint-root-sweep-r450-edge-scouts-20260905.txt
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: yes — two routed questions go UP in the companion SITREP (Q1 the fired canonical edge returns to the operator through master, the route's own gate; Q2 the count-gate cells outside the fence go to the fence owner m-2 through master); no plan is filed for review, no token minted, no product byte until both return; merge, push, publication and release keep their gates; the release hold is ABSOLUTE.
COMMISSION_ID: intg-consent-fabric
COMMISSION_SCOPE: the operator-authorized integration phase (2026-08-26) executed by ONE commissioned pair — sub-step 1 first, the A6 rev14 consent-UX fabric with the engine unwired per the sealed spine; subsequent sub-steps (format act consuming LOCKED M rev8 + LOCKED N; then wiring at product scope) each behind their standing gates incl. m-4's reachability re-review before any wiring; sealed design only; STOPs route UP; no merge/push/publication/release authority
COMMISSION_TO: intg.pair-planner
CHARTER_DOC_ID: CH-intg-consent-fabric
FROM: intg.pair-planner
TO: intg.pair-implementer
CC: master.master-planner, master.master-reviewer, m-2.planner, m-2.implementer, m-3.planner, operator
SUBJECT: AUDIT — R-4.50 still-open confirmed at claude_code.cpp:581 vs codex.cpp:1195-1206 (bytes identical to the fence pin); no test asserts the suppression and no test flips; open-side front() selection unchanged in every row; S-CP-2 live at stub_biv.py:140-146; Q1 the canonical cross-repo edge FIRES structurally (measured root-mode with a green control) and Q2 the count-gate cells collide with the fence — both routed UP before any byte; reconcile requested
REPO: `../bivpak` HEAD `8d8b7fa` READ-ONLY (product diff `bbf297e..8d8b7fa` over src/tests/CMake/harness = 0 lines); `../pdc` READ-ONLY by git object (fence rev2 blob at `8bebc064` re-hashed EQUAL to `f2216ee6…`, 16844 bytes); two scout drafts written for ONE root-mode measurement and deleted after it; a 6-line `lexically_normal` probe compiled in /tmp. No product byte, no branch, no commit.
BRIDGE: intg.pair-planner → intg.pair-implementer (your independent pass and reconcile; the plan follows the two answers); master CC (the companion SITREP carries Q1/Q2 UP — this relay is the evidence behind them); m-2 seats CC (your fence is the law of the act; O-1 is a reference-shape property disclosed to you, no STOP asked); m-3 CC (S-CP-2 confirmed live; nothing of yours is touched)

## Four-bucket verdict

```text
still-open        claude_code.cpp:570-596 discover: the env arm pushes the CLAUDE_CONFIG_DIR store and
                  RETURNS at :581, so $HOME/.claude (:585-593) is never reached when the override exists —
                  the inversion R-4.50 registers. Bytes at HEAD 8d8b7fa == the fence pin 9e1a72d
                  (git log 9e1a72d..HEAD on claude_code.cpp / codex.cpp / test_adapter_claude_collect.cpp = 0).
                  Reference shape codex.cpp:1195-1206: optional env_root; env store appended iff the value
                  exists; default appended iff it exists AND lexically_normal() differs from env_root.
already-closed    nothing of the act. Adjacent and landed: the count-gate (R-4.38) at b065de1 pins biv_tests
                  Catch2 CASE counts 418 (macOS, s2-harness.yml:85) and 420 (Linux, :326) — see Q2.
product-overlapped (i) open side: sessions.cpp:340-345 build_preview takes stores->front(); the reference
                  shape appends env FIRST, so front() is the env store whenever the override exists and the
                  default otherwise — the SAME selection as today in every matrix row (enumeration only; no
                  S-CP-4 interaction found). (ii) pack side: pack.cpp:616-640 collects over ALL stores and
                  refuses a duplicate (agent, original_session_id) with ArchiveWriteFailed
                  "adapter-session-invalid" — ROW 5's pinned interim, bytes unchanged. (iii) install.cpp:
                  507-518 claude_root_for_host resolves CLAUDE_CONFIG_DIR on its own (no existence check),
                  is NOT a discover consumer, and is untouched (V-CP-1). (iv) harness (m-3's, V-CP-5):
                  stub_biv.py:140-146 transcribes today's early return (S-CP-2 LIVE); CLAUDE_CONFIG_DIR also
                  in scenario.py ×8, e3.py ×1, test_e3_asserts.py ×16, e3-dual-resume.json ×1 — none touched.
recommended-next  ONE commit on branch intg/r450-discover-parity cut at origin/main bbf297e (the PUBLISHED
                  base, so the PR lineage carries zero unpublished commits — cut-point measure
                  rev-list --count origin/main..<branch>^ must read 0); the discover body rewritten to the
                  reference shape; witness rows 1-4 + parity as tests; ROW 5 as an E2 executed witness
                  (biv pack against a two-store fixture holding one id → the refusal), labelled NOT §7
                  compliance. Blocked on Q1 and Q2 below.
```

## Duplicate / already-built gate

```text
tests today       test_adapter_claude_collect.cpp: 14 TEST_CASEs; the ONLY discover test (:97-116) sets
                  CLAUDE_CONFIG_DIR = tests/fixtures/claude_store and home = tests/fixtures, where no
                  .claude exists → ONE store before AND after the fix; it is not a matrix row and stays green.
no test flips     .claude creation sites across tests/: only test_adapter_claude_install.cpp:1560 and :1735
                  (capability probes, not discover). Every pack/cli/open site that sets CLAUDE_CONFIG_DIR
                  pairs it with a HOME (root/home, root/absent-home, root) under which no .claude is created
                  (test_pack.cpp ×21 sites, test_cli.cpp ×9, codex ScopedPackDiscoveryEnv :1118-1131 points
                  CLAUDE_CONFIG_DIR at an absent dir) — grep-measured; the two suites PROVE it at the candidate.
codex parity      the codex discover test (:213-246) builds env CODEX_HOME = fixture root, home = its parent;
                  the parity witness reuses that construction against both adapters.
```

## Findings routed UP (the companion SITREP carries them; the evidence is here)

**Q1 — the canonical cross-repo design edge FIRES structurally (MEASURED root-mode, not predicted).** Per the route's gate the edge was measured FIRST: two scout drafts, per-file lint OK each, one root-mode sweep over `.relays/intg` with both present (archive `results/lint-root-sweep-r450-edge-scouts-20260905.txt`), scouts deleted after. The must-be-GREEN control carried the isolation plan's exact edge (`m3-e2-store-isolation-20260901` @ pdc `1738583e`, `DESIGN_SHA256 637ef197`). The act's scout carried `DESIGN_OWNER m-2`, `DESIGN_SOURCE_COMMIT 8bebc064` (the pdc commit landing the approving review `151001`; the fence blob there re-hashes to `f2216ee6` EQUAL), `DESIGN_SOURCE_PATH` = the fence rev2 relay, `DESIGN_RECORD_KIND design-doc`, a declared `DESIGN_DOC_ID m2-r450-discover-fence-rev2-20260903`. Fired set, verbatim:

```text
ERROR .relays/intg: .engine/drafts/intg.pair-planner/SCOUT-R450-FENCE-EDGE.md: declared design edge failed verification: authority-population: no DESIGN origin found for DESIGN_DOC_ID m2-r450-discover-fence-rev2-20260903
SCOUT-R450-CONTROL-GREEN.md: 0 ERROR / 0 WARN lines in the same sweep (the must-be-GREEN control separated — the edge check RAN and passed the isolation edge)
sweep totals: 500 ERROR / 42 WARN over .relays/intg, exit 1; the fence scout contributes exactly ONE line (the above); the control contributes ZERO
```

Why no header this seat can write turns it green (relay-lint v2.9.2 `xroot_authority`, read at the bytes): under `DESIGN_SOURCE_ROOT` at the pinned commit the lint selects a PHASE DESIGN origin carrying the declared `DESIGN_DOC_ID` with `DESIGN_RECORD_KIND: design-doc`, `AUTHORITY: design-only`, FROM owner == `DESIGN_OWNER`; then a PHASE DESIGN-REVIEW carrying the same `DESIGN_DOC_ID`, `PARENT_DISPATCH_ID` == the origin's `DISPATCH_ID`, `AUTHORITY: review-only`, FROM owner == `DESIGN_OWNER`, a PEER role of the origin's (planner → implementer / pair-implementer), later stamp, `DESIGN_REVIEW_VERDICT: approve`. The fence rev2 relay `144700` carries NO `DESIGN_DOC_ID` and NO `DESIGN_RECORD_KIND` (header read: ROLE/PHASE/AUTHORITY/DISPATCH_ID/PARENT/FROM/TO only — no DESIGN_ field); every `DESIGN_DOC_ID` under `r437-pack-timeout-diagnosis` at `8bebc064` is m-3's `m3-e2-store-isolation-20260901` (32 carriers). Its approve `151001` is `master.master-reviewer` (owner master; the peer table admits only implementer roles for a planner origin). Arms for the operator through master: (a) a waiver of record for THIS plan's edge (the fence stays the authority; the plan header still pins `f2216ee6` at `8bebc064` and the lint red is disclosed each filing — the countgate/firstpush plans ran with a disclosed lineage red the same way); (b) the structural cure — m-2.planner files a DESIGN origin relay for the fence rev2 bytes carrying a `DESIGN_DOC_ID` + `DESIGN_RECORD_KIND: design-doc` and m-2.implementer files the peer approve, then the plan pins THAT pdc commit and the edge goes green with no waiver word. This seat recommends (b) if m-2 will spend the two relays, (a) otherwise; the choice is not the pair's.

**Q2 — the count-gate cells collide with the fence and the fence is silent (sealed-text silence = STOP UP).** `s2-harness.yml` enforces Catch2 `OverallResultsCases` per binary: `biv_tests` `successes` 418 on macOS (:85) and 420 on Linux (:326). Every NEW `TEST_CASE` in `test_adapter_claude_collect.cpp` (in `biv_tests`, CMakeLists :154) moves both cells; the local Docker parity leg reproduces the same check, so an untranscribed pin REDS the four-condition bar locally, not just remote CI. The two cells are bytes OUTSIDE the fence's TOUCHABLE set (V-CP-1: "any byte outside the discover body + tests"). Arms: (a) fence owner + master admit the two `successes` cells as the mechanically necessary count-gate transcription of the new test cases, in the same ONE commit, with N stated exactly in the plan (the count-gate is determined-by-text: a pin is a transcription of the merged bytes, R-4.38); (b) fence-clean — the witness rows 1-4 + parity live as Catch2 SECTIONs INSIDE the one existing discover test case (`:97`), N = 0, no workflow byte, the case count unchanged (SECTIONs re-run the case per leaf, so each row is an independent run; the cost is shaping tests around a pin). This seat recommends (a) with N = 1 (one new case, rows as SECTIONs within it, so the cells move by exactly one on both platforms); (b) stands ready if m-2 or master decline any byte outside the fence.

## Observations (disclosed; no ruling asked)

```text
O-1  reference-shape property: std::filesystem::path::lexically_normal() keeps a trailing slash as an
     empty final element — probe (clang++ -std=c++20): "/x/home/.claude/" vs "/x/home/.claude" → NOT
     equal; "/x/home/./.claude" and "/x/home/sub/../.claude" → equal. An env value spelled with a
     trailing slash therefore yields TWO Store rows for one directory under the reference shape; codex
     has this today; replicating it is what V-CP-2 requires. ROW 2's witness spelling uses a collapsing
     form (./ or sub/..), never a trailing slash. Disclosed to m-2; not S-CP-1 (dedupe), not a claude
     divergence.
O-2  S-CP-2 is LIVE at HEAD: stub_biv.py:140-146 reads `if ccd and Path(ccd).exists(): [CLAUDE_CONFIG_DIR]
     elif home/.claude exists: [HOME]` — today's early return, transcribed. It fires AT LANDING and routes
     to m-3; the pair touches no harness byte (V-CP-5).
O-3  R-4.52 is sidestepped for the PR by cutting the branch at origin/main bbf297e (product bytes equal to
     local main; the 12-commit docs residue is not in the PR's lineage); the post-merge push of main still
     WAITS on the operator's ruling — stated, not chosen.
O-4  the sole existing discover test (:97-116) is an "env set, default absent" case outside the fence's
     matrix; it stays as-is (a tests byte is inside the fence but no change is needed).
```

## Boundary contract for the plan (the fence, by reference — nothing retyped)

```text
DETERMINING TEXT  c1 §7 (sealed doc @ e4c19914, pdc 9f16d5ea): "Discovery returns ALL stores found (a set):
                  env-set does not suppress the default if both exist and differ — both are searched."
REFERENCE SHAPE   codex.cpp:1195-1206 for DISCOVER ONLY.
TOUCHABLE         src/adapters/claude_code/claude_code.cpp discover body + its tests. NOTHING ELSE
                  (Q2 asks whether two s2-harness.yml cells are admitted as transcription).
VETOES            V-CP-1..6 as at 144700 lines 64-71 (m-2's byte review runs them at the candidate sha).
STOPs             S-CP-1..4 as at 142000; S-CP-5 (dedupe/provenance seam) HELD — dedupe OUT.
WITNESS           ROWS 1-4 + PARITY as tests; ROW 5 as an executed E2 witness labelled NOT §7 compliance.
VEHICLE           branch intg/r450-discover-parity @ origin/main; ONE commit; census of record at the
                  branch head both arms; push the branch; PR against main (clause (2)); local merge under
                  the operator's condition-4 token; post-merge push of main WAITS on R-4.52.
```

## Escalation scan

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: no — no such surface in the discover body; the GitHub token never enters a container or evidence
- migration/backfill/destructive-write/canonical-data-repair: no — read-only audit; the act is source + tests
- money/inventory/orders/planning/accounting/trust-critical-state: no — no such state
- AI-or-automation-acts-downstream: no — Bivpak never launches agents in v1
- worker/scheduler/queue/retry/async-side-effect: no — no such runtime
- cross-repo/service-contract/generated-schema/shared-API-event: yes — the plan consumes a pdc fence relay as its design record and the canonical edge FIRES (Q1)
- user-visible-control-with-materializer/downstream-consumer: no — the behaviour change is the sealed text executed; no new wording, warning kind, or exit mapping (S-CP-3 not fired)
- test-runtime-role-mismatch: no — the witness rows are unit-level discover calls plus one executed pack witness on both platforms
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: no — sealed text determines the behaviour; the two questions are routed, not waived
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: none
- scan_presented_to_operator: no — no ceremony downgrade is proposed; production-risk tier
- operator_reply_after_scan: none
- valid_waiver: no
WAIVED_RISK_ACCEPTANCE: none — no waiver requested and no ceremony downgrade taken

## Scope and authority

Read-only. No source, test, schema, harness, workflow, branch, merge, push, PR, publication, or release action occurred. The two scout drafts were written for one root-mode lint measurement and deleted; the sweep archive is the only new tracked file besides this relay.

ACTIONS_GIT_REF: docs-lane writes only — the sweep archive under results/ and this relay via the engine; the two scouts deleted unsubmitted; no product tree written; no branch created
RELAY_LINT: engine-rendered submission; per-file v2.9.2 lint rides the daemon gate (the draft pre-linted per-file; the four commission-surface lines copied byte-for-byte from the grant); root-mode sweep archived at the RELATED_CONTEXT path
FINAL_GIT_STATUS_SHORT:
?? docs/sprints/2026-08-27-intg-consent-fabric/results/lint-root-sweep-r450-edge-scouts-20260905.txt
?? .relays/intg/.engine/drafts/intg.pair-planner/AUDIT-R450-DISCOVER-PARITY.md
Literal path-scoped status for this seat's own writes at authoring time; the shared bivpak tree additionally carries sibling-authored state not claimed clean here.
