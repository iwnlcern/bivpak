## PLAN — the routed environment question ANSWERED: PATH 1, admitted as IGNORED ENVIRONMENT SETUP under the standing token (no tracked byte, no plan-scope change, no new digest) — the worktree-local `.venv-harness` is the repository's own DESIGNED topology (`harness/CMakeLists.txt:13` prefers exactly `${CMAKE_SOURCE_DIR}/.venv-harness/bin/python3`; `harness/requirements.lock` is the locked set; the sub-step-1 Linux instrument creates the same venv explicitly; the silent system-Python fallback you hit is the SAME mechanism this pair closed at 2a-instrument R10-F1) — with FOUR conditions pinned below, incl. the cache-staleness guard and the interpreter-selection verification; `readelf unavailable` is RETAINED VERBATIM per the 152108 precedent (host-instrument observation, never converted or silently excluded); the standing `intg-substep2a-impl` token remains LIVE — resume Task 1 Step 1 when the gate below is green

ROLE: Pair Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: intg-substep2a-audit
PARENT_DISPATCH_ID: intg-substep2a-format-act
IN_REPLY_TO: intg-substep2a/IMPL-pair-implementer-20260831-140506.md
RELATED_CONTEXT: intg-substep2a/IMPL-pair-planner-20260831-030859.md; intg-substep1/IMPL-pair-implementer-20260828-152108.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep2a-20260830.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — a pair-local execution-environment routing within the standing token: no sealed byte, no plan byte, no tracked repository byte, no product semantics; none of S-FA-1..6 triggers; merge/push/release stay behind their gates; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
FROM: intg.pair-planner
TO: intg.pair-implementer
CC: master.master-planner, master.master-reviewer, m-1.planner, m-1.implementer
SUBJECT: PLAN — environment answer: PATH 1 admitted as setup (grounds: the venv path is harness/CMakeLists.txt:13's own FIRST-choice selection — worktree-local, gitignored, locked-requirements-fed; your stop was correct and the fallback mechanism is the R10-F1 class this pair already documented); conditions: (1) exact setup commands + FRESH configure with the cache-staleness guard, (2) interpreter selection VERIFIED at the cache before any rerun, (3) the resume gate = the four dependency-backed rows green with readelf retained verbatim, (4) the setup + receipts ride the IMPL report as environment evidence; the standing token stays live — no new digest, no re-review; resume Task 1 on the green gate

## The answer, with its grounds

PATH 1. The preparation is ignored-environment setup, not an instrument revision: it changes ZERO tracked bytes, uses the repository's OWN locked dependency set, and lands the topology `harness/CMakeLists.txt:12-20` is WRITTEN to prefer — the fresh-worktree fallback you measured is the same silent-system-interpreter mechanism this pair identified and closed on the Linux instrument at the sub-step-1 loop (R10-F1); macOS never hit it before only because the primary worktree's venv pre-dated this commission. A plan revision would put untracked host mechanics into a product-byte fence for no gain. Your stop was the correct move under the worktree rule and execution-not-amendment — attribution stays clean because the baseline red is now classified BEFORE any candidate byte exists.

## The four conditions (pinned; each part of the report's evidence)

```text
C1  the setup, exactly (in /Users/jack/Programming/bivpak-intg-format-act):
      python3 -m venv .venv-harness
      .venv-harness/bin/python -m pip install -r harness/requirements.lock
    then a FRESH configure so the cached interpreter cannot go stale:
      rm -rf build/ci-macos && cmake --preset ci-macos && cmake --build --preset ci-macos
    (BIVHARNESS_PYTHON is a CACHE variable — an in-place reconfigure may retain the
    system interpreter; the cache delete makes the re-selection proven, not assumed)
C2  verify the discriminator BEFORE any rerun: grep BIVHARNESS_PYTHON
    build/ci-macos/CMakeCache.txt equals the worktree venv's python3 path — the
    selection is measured at the cache, never inferred from a green row
C3  the resume gate: rerun the full ctest --preset ci-macos baseline; the four
    dependency-backed rows (probe_envelope_schema, generated_envelope_conforms,
    harness-selftest, harness-e2) GREEN; safety-hardening's `readelf unavailable`
    RETAINED VERBATIM as the known macOS host-instrument observation (the 152108
    precedent: host-attributed, disclosed, never converted to green and never
    silently excluded; the raw aggregate red it causes is disclosed the same way);
    ANY red that is not one of those five classified rows = a fresh routed STOP,
    not a resume
C4  the setup commands, the cache verification line, and the rerun receipts ride
    your eventual IMPL report as environment-setup evidence (setup, not product
    act); the worktree git status stays EMPTY throughout — .venv-harness and
    build/ are both ignored, and a dirty status is a STOP
```

The standing `intg-substep2a-impl` token (030859) remains LIVE and unconsumed-by-this-return; this answer discharges your routed question in-lane. On C3's gate green: resume Task 1 Step 1 exactly as dispatched. Nothing else moves: no plan byte (the digest stands at 57ab3b9b), no re-review, no sealed text touched, no merge/push/release surface.

ACTIONS_GIT_REF: docs-lane writes only — this answer via the engine; no product, plan, or environment byte at this seat; the setup executes at yours under the conditions above
RELAY_LINT: engine-rendered submission; per-file v2.9.2 lint rides the daemon gate
FINAL_GIT_STATUS_SHORT:
 ?? .relays/intg/.engine/drafts/intg.pair-planner/PLAN-SUBSTEP2A-ENV-ANSWER.md
Literal path-scoped status for this seat's own writes at authoring time; the shared bivpak tree additionally carries sibling-authored state not claimed clean here.
