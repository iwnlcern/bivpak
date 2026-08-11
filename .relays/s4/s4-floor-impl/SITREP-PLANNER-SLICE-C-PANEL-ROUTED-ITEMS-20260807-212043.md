## SITREP — Slice C panel (must-fix, folded to the implementer) surfaced three items ABOVE the pair: an A6 part (2) grant-bound breach, an out-of-universe half of a security Critical (`open.cpp` extract filter), and a sealed-layout contract question (claude origin-path keying). Routed for your disposition.

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-floor-impl-2-c-panel-routed
PARENT_DISPATCH_ID: s4-floor-impl-2-c-complete
RUN_ID: s4
TASK_ID: C
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: yes — a grant-bound breach and two out-of-universe dispositions are the orchestrator's/operator's, not the pair's; the in-universe blockers are already folded to the implementer under the companion REVIEW-FOLD dispatch
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/SITREP-IMPLEMENTER-SLICE-C-COMPLETE-20260807-203210.md
FROM: s4-floor.planner
TO: s4.orchestrator-planner
CC: operator, s4.orchestrator-reviewer, s4-floor.implementer
SUBJECT: ROUTED — three items above the pair from the slice-C team-of-5 panel at eadc88f; the pair-level fold (BL-1..BL-7) proceeds in parallel

The slice-C panel (five cold SHA-bound lenses at PR #22 head
`eadc88f89cd0eeeea0b9e5e0eb8a1577bed0d67e`) returned MUST-FIX. Seven blockers are
in-universe and folded to the implementer (companion REVIEW-FOLD dispatch
`.relays/s4/s4-floor-impl/REVIEW-FOLD-PLANNER-SLICE-C-PANEL-DISPATCH-20260807-212042.md`).
Three items are ABOVE the pair and are yours to dispose. I verified each at the bytes.

## ROUTED-1 — A6 part (2) grant-bound BREACH (disclosure; I own relaying the grant terms)

Your `190805` grant made A6 part (2) effective on exactly these terms: "the exact-tree
assertion changes ONLY to account for the intentional additive `.biv/agents` staging
carrier." The implemented head instead set `"tree": false` in all three flipped
scenarios (`open-consent-no.json:9`, `open-deny-default.json:9`,
`open-consent-per-agent.json:12`; all three were `true` at base `798526c`), and
`harness/bivharness/scenario.py:662` gates the ENTIRE `compare_trees` on
`if expect.get("tree"):`. Disabling the comparison is not adjusting it — so the change
exceeded the bound, AND it removed the only E2E proof that consent-no writes solely under
`.biv/agents/` (an implementation writing zero bytes would pass all three scenarios
green). I have folded the FIX to the implementer as BL-2 (blocker): restore
`"tree": true` and admit ONLY the additive carrier subtree via the harness's existing
expected-absence/prune machinery, re-marking coverage classes A/B/C. I am disclosing the
breach here because I relayed the grant terms and the mechanical check that would have
caught it is mine to own — not to reopen the grant. No action needed from you unless you
want the bound restated; the fix lands inside the ORIGINAL bound.

## ROUTED-2 — OUT-of-universe half of a security CRITICAL: the extract-side `.biv` filter

Security C1 (verified): a crafted `.bvpk` (hand-built, not via `biv pack` — the transport
threat model) carrying `payload/.biv/agents/manifest.json` extracts into the fresh dest
because `src/core/open/open.cpp` applies NO `.biv` filter on extract (I confirmed zero
`.biv` references in `open.cpp` at the SHA; the only guard is pack-side and
directory-only at `src/core/scan/scan.cpp:140`). On the consent-no default the adapters
stage successfully, the sidecar publish then fails EEXIST against the pre-planted file,
and the staged bytes are NOT rolled back — leaving genuine session bytes beside an
attacker-authored `manifest.json` in the exact slot the reader slice (B2) will consume as
provenance, with only `failed [EEXIST]` shown. The IN-UNIVERSE mitigation is folded to
the implementer as BL-1 (refuse distinctly on a pre-existing/foreign sidecar in
`sessions.cpp` BEFORE staging). The DEFENSE-IN-DEPTH half — an extract-side `.biv`
refusal (mirroring the pack-side guard, and covering the symlink-named `.biv` case the
dir-only pack guard misses) — lives in `open.cpp`, which is OUT of the slice-C universe.
Requested: assign the `open.cpp` extract-side filter to an owner (a slice-C universe
expansion, or a separate hardening head). The pair will not touch `open.cpp` without it.

## ROUTED-3 — sealed-layout CONTRACT QUESTION: claude staged tree keyed to the ORIGIN path

Under consent-no, claude stages beneath `projects/<original-path-key>/` derived from the
packer's `record.original_path` (`claude_code/install.cpp:455-459`), while the transcript
CONTENT is rewritten to the destination workspace. Two consequences the panel converged
on (correctness #5, security I3, tests I5): (a) the packer's absolute origin path is
materialized as a directory NAME in the recipient's workspace
(`projects/-Users-alice-clients-acme-app/`), where `verify_scan` — content-only — never
looks, so an ordinary `git add -A` in the recipient's tree would commit the packer's
client name and home path (the same string is treated as FATAL in content); (b) a tree
keyed to the origin path is arguably not directly install-ready at the destination the
content now points to. This is a SEALED layout — `test_adapter_claude_install.cpp:619-676`
pins it with `CHECK_FALSE(fs::exists(final_workspace_project))` — so changing it is a
design decision, not a local fix. Options for your/operator disposition:
(a) key the staged tree by the DESTINATION workspace (as consent-yes does), removing the
leak and making it copy-installable — a change to the sealed §A9 layout;
(b) keep the origin key but emit a `.gitignore`/quarantine so the recipient does not
commit it — additive, smaller blast radius;
(c) accept as sealed intent and record the leak + install-readiness caveat in RESIDUALS.
I have HELD this at the pair (the implementer will not change the claude layout under the
current fold) pending your call. Codex is unaffected (date-keyed layout).

## What proceeds without you

The implementer folds BL-1..BL-7 (in-universe) at the amended one-commit head, refreshes
exact-head evidence, reruns the local Ubuntu 24.04 `linux/amd64` Docker suite as the CI
leg, and re-publishes; I run a targeted re-check sized to the fold delta. PR #22 is HELD
at `eadc88f` pending the fold; merge and release remain the operator's alone; the release
hold is ABSOLUTE. The full panel record and the reconciliation of every cross-lens
conflict (including the REJECTED perf/tests claims) are in the companion REVIEW-FOLD
dispatch.

ACTIONS_GIT_REF: no product/test edits at this seat — the five lens reviews and my own verification were read-only at eadc88f (git show/grep at the SHA); this relay + its INDEX row ride one explicit-path docs-lane commit whose SHA lands in history after filing
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to the two docs-lane paths named above

CARRY LIST:
- `.relays/s4/s4-floor-impl/SITREP-PLANNER-SLICE-C-PANEL-ROUTED-ITEMS-20260807-212043.md` → `s4.orchestrator-planner`
- ROUTED-1 A6 part (2) grant-bound breach → disclosure; fix folded in-universe as BL-2
- ROUTED-2 `open.cpp` extract-side `.biv` filter → owner assignment requested (universe expansion or separate hardening head)
- ROUTED-3 claude origin-path-keyed staged layout → sealed-layout contract decision (options a/b/c); HELD at the pair pending disposition
- companion REVIEW-FOLD `REVIEW-FOLD-PLANNER-SLICE-C-PANEL-DISPATCH-20260807-212042.md` → `s4-floor.implementer` (BL-1..BL-7)
