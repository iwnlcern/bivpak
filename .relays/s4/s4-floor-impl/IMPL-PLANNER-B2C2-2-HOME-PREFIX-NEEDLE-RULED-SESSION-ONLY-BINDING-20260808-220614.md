## IMPL — B2C2-2's held cell is RULED: fold the packer home-dir-prefix needle in PATH CONTEXT (all flavors), NOT a bare-substring scan; AND a BINDING guardrail on ALL needle work — scan/rewrite stays on session artifacts only, a needle-hit in non-session payload is NOT a refusal. Supplements the cycle-2 fold authorization; the rest of B2C2-1..B2C2-6 proceeds as authorized.

ROLE: Planner
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: s4-floor-impl-2
PARENT_DISPATCH_ID: s4-floor-pair-plan-review-approve
RUN_ID: s4
TASK_ID: B2
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — the operator ratified the scope (master `215811`, carried by the orchestrator `220234`); the mechanism is the pair's to fold within the ruling; the third re-panel, condition-3, per-candidate operator authorization, and the ABSOLUTE release hold are unchanged downstream gates
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-B2-M4-SCOPE-RULED-SESSION-ONLY-BINDING-I3-FALLBACK-C-THEN-B2-20260808-220234.md
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: s4.orchestrator-planner, operator
SUBJECT: B2C2-2 fully specified — home-dir-prefix path-context needle + the session-only-rewrite BINDING line; folds under the standing cycle-2 authority (`214345`)

The one part of B2C2-2 I held pending a ruling is now discharged. This IMPL relay
supplements the cycle-2 fold authorization
(`IMPL-PLANNER-B2-CYCLE2-FOLD-AUTHORIZE-20260808-214345`); everything else there stands
unchanged.

## B2C2-2 needle set — fold to EXACTLY this
- the image-UNION of all origin-path spellings + all origin/message ids across the manifest
  (as already authorized), PLUS
- **the packer home-dir prefix in PATH CONTEXT** — all `path_flavor` spellings — catching any
  path UNDER the packer's home directory.
- **NO bare-substring content scan** of the home/username token (low-entropy; would
  over-refuse on innocent transcript content — the operator adopted the path-context
  scoping).

## BINDING structural constraint — applies to ALL needle work, not just this cell
Operator's hard line, verbatim in substance:
> The tool edits/scrubs ONLY agent-session-history artifacts. The whole needle set
> (paths, ids, home-prefix) — rewrite AND scan — applies ONLY to session artifacts at
> install. Every other payload class (repo payloads, overlays, dirty-state, non-agent
> files) restores BYTE-VERBATIM; editing them would forge new git state and break the
> pack/open inverse invariant. A needle-hit in a NON-session file is NOT a refusal — that
> is the user's own packed data, governed by consent/`.bivignore`.

**What this means mechanically (master byte-verified at `d6cceba`, and so did I):** the scan
DOMAIN is already correct — `verify_scan` / `verify_raw_text_bytes` /
`verify_whole_document_bytes` are called ONLY from `claude_code/install.cpp` and
`codex/install.cpp` (per-session install), with ZERO `src/core/**` (pack/open/scan/repo)
callers. So the union + home-prefix change is to the **needle SET**, NOT the **scan
domain**. Keep the domain where it is: add the home-prefix needle in path context inside the
session-install verify surface; do NOT extend any needle scan to non-session payload, and do
NOT let a union/home-prefix hit on repo or overlay bytes become a refusal. If satisfying the
needle set appears to require reaching outside the session-install surface, STOP and route
up — that would be a new deviation.

## Unchanged from the cycle-2 authorization
B2C2-1 (decode keys AND values + raw floor), B2C2-3 (pin HOME ×9), and the three Importants
(B2C2-4 collector class-set, B2C2-5 retained-torn pack warning, B2C2-6 falsifiers) proceed
as authorized. `rewrite_common.{hpp,cpp}` in-universe; `manifest.cpp` fence-2 OUT; BL2-4
per-session radius as master ruled; any third file a NEW deviation before an edit. Write
FOLD_SCOPE `all-in` before any edit.

## Downstream (situational — no change to the fold itself)
The amended one-commit head owes the THIRD targeted security+correctness+tests re-panel
(M-4 re-confirmed) before B2 is bar-ready — I convene it after your report. I-3: the
operator DECLINED unit-land and elected **C then B2 back-to-back** — B2 is the immediate
next merge after C, nothing between, nothing released in the window, m-4 the confidentiality
lens; B2 still owes the third re-panel first. Wave: B1 (in flight) → slice A (post-panel) →
C → B2 immediately. Merge and release remain the operator's alone; the release hold is
ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — this authorization supplement + its INDEX row ride one explicit-path docs-lane commit whose SHA lands in history after filing; the implementation branch is unchanged at d6cceba pending your fold
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state (incl. the orchestrator's untracked B1 merge-token relay); this seat's writes are confined to the two docs-lane paths named above

CARRY LIST:
- `.relays/s4/s4-floor-impl/IMPL-PLANNER-B2C2-2-HOME-PREFIX-NEEDLE-RULED-SESSION-ONLY-BINDING-20260808-220614.md` → `s4-floor.implementer`
- B2C2-2 = image-union + home-dir-prefix path-context needle (all flavors), NO bare-substring scan → fold
- BINDING: needle set + rewrite confined to session-install artifacts; non-session restores byte-verbatim; non-session needle-hit ≠ refusal; keep the scan domain, change the needle set → guardrail on the whole fold
- third re-panel owed; I-3 = C-then-B2 back-to-back (B2 immediate-next); merge/release the operator's, hold ABSOLUTE
