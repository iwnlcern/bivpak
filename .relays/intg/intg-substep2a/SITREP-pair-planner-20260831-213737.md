## SITREP — the combined evidence set UP, and m-2's STORE SIGNATURE is CONFIRMED AT THE STACK: the 25-second sample attributes the window to full-text store reads — 21502 samples in pack_impl (pack.cpp:620), 18852 of them in CodexAdapter::collect → source_text (codex.cpp:1273→:172) and 2291 in ClaudeCodeAdapter::collect → source_text (claude_code.cpp:655→:113) — and ACT 1 shows WHY the fixture's override cannot prevent it: codex.cpp:1193-1206 ADDS $HOME/.codex even when CODEX_HOME is set, CLAUDE_CONFIG_DIR-unset resolves the real ~/.claude, so every measured AND every harness run on this host parses the REAL stores (1330 codex session files + 9.2MB state_5.sqlite; 2210 claude files, 762 JSONL) against a fixture that stages ONE rollout and nothing claude-side — deterministic, worktree-invariant, result-invisible, store-size-proportional: the whole R-4.37 family in one mechanism; the H-A/H-D cut is m-3's on these receipts; the pair HOLDS

ROLE: Pair Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: intg-substep2a-audit
PARENT_DISPATCH_ID: intg-substep2a-format-act
IN_REPLY_TO: intg-substep2a/IMPL-pair-implementer-20260831-210948.md
RELATED_CONTEXT: ../../pdc/master/relays/intg-substep2a-format-act/PLAN-master-planner-20260831-194614.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/DESIGN-m2-planner-20260831-192500.md; intg-substep2a/SITREP-pair-planner-20260831-171137.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — the H-A/H-D cut and every disposition it implies (harness isolation vs product-side treatment; any budget byte; the 2a baseline ruling; Task 1's restart) are m-3's and yours on these receipts; the pair holds fail-closed with nothing proposed; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
FROM: intg.pair-planner
TO: master.master-planner
CC: master.master-reviewer, intg.pair-implementer, m-3.planner, m-3.implementer, m-2.planner
SUBJECT: SITREP — Acts 1-3 complete at exactly the directed budget (one new run, one 25s sample, metadata-only census; fences honored; snapshot equality proven at both worktrees; receipts at the implementer's 210948 with artifacts hashed): ACT 1 — all seven runs AND the harness contexts inherited HOME=/Users/jack with only CODEX_HOME overridden (source_env sets CODEX_HOME iff codex named, CLAUDE_CONFIG_DIR iff claude-code named — scenario.py:262-319 cited; this scenario names codex only), and the RESOLVED roots are three: the scratch profile, the real /Users/jack/.codex (added by codex.cpp:1193-1206 EVEN WITH CODEX_HOME SET), and the real /Users/jack/.claude (claude_code.cpp:570-594 default) — census: .codex 1330 session files/1326 rollouts + state_5.sqlite 9,228,288 bytes; .claude 2210 files/762 JSONL; the scratch roots 1 rollout each; ACT 2 — one 30.372974s run, sample verbatim (291 lines, sha c8b118c1…): the top frames put the window in source_text under BOTH adapters' collect; ACT 3 — the fixture stages source-codex (1 rollout) + an empty target-codex config and NO claude profile; the mechanism explains determinism, worktree-invariance, result-invisibility, AND the store-size proportionality (a growing real store slowly crossed the fixed 30s budget — why 152108 passed and later runs straddle); the cut is m-3's; asks unchanged (the 2a baseline ruling after the cut); HOLD

## What the receipts establish (synthesis of filed numbers; the disposition is not mine)

```text
resolution   the fixture CANNOT isolate the host stores on these bytes: overriding
             CODEX_HOME still gets $HOME/.codex APPENDED as a second store
             (codex.cpp:1193-1206), and nothing in a codex-only scenario touches
             CLAUDE_CONFIG_DIR, so the real ~/.claude default rides too
             (claude_code.cpp:570-594) — three roots resolved in every measured
             and every harness context on this host
where-time   the sample (25s of a 30.37s run): pack_impl 21502 samples at
             pack.cpp:620 → CodexAdapter::collect 18852 → source_text codex.cpp:172;
             ClaudeCodeAdapter::collect 2291 → source_text claude_code.cpp:113 —
             the window IS full-text artifact reads of the resolved stores
proportion   codex real store: 1330 session files (1326 rollout JSONL) + 9.2MB
             sqlite → 18852 samples; claude real store: 2210 files (762 JSONL) →
             2291 samples; the staged fixture: ONE rollout → invisible — the
             duration scales with the HOST's store size, which explains every
             historical observation: 152108 passed when the stores were smaller /
             load lighter; the R-4.37 sightings straddled as the stores grew into
             the fixed 30s budget; CI runners (store-less HOME) never see it
contexts     bare runs ≡ harness runs on every governing variable (ACT 1a/1b,
             file:line cites on the face) — the bare reproduction was faithful
fences       exactly acts 1-3, one run, one sample, metadata-only census (no store
             content, no names carried), C4 snapshot equality at both worktrees,
             zero candidate bytes, Task 1 CLOSED, token live-held
```

## Standing state and asks (unchanged)

The H-A/H-D cut executes at m-3's seat on these receipts — harness-side store isolation vs any product-side disposition, and any budget byte, are the owner's alone. After the cut: the 2a baseline ruling (the pair still holds fail-closed at the C3 gate; option (c) remains refused everywhere). The countgate lane stands as sequenced. The pair proposes nothing and moves nothing.

ACTIONS_GIT_REF: report-only — the implementer's receipts consumed as filed; this relay via the engine; no byte moved at any pair seat; both worktrees snapshot-proven unchanged
RELAY_LINT: engine-rendered submission; per-file v2.9.2 lint rides the daemon gate
FINAL_GIT_STATUS_SHORT:
 ?? .relays/intg/.engine/drafts/intg.pair-planner/SITREP-STORE-SIGNATURE-CONFIRMED-UP.md
Literal path-scoped status for this seat's own writes at authoring time; the shared bivpak tree additionally carries sibling-authored state not claimed clean here.
