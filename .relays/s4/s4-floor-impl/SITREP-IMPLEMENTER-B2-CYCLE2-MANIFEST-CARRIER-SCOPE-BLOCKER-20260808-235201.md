## SITREP — B2 cycle-2 fix round 1 blocked: the ruled packer-home needle has no authoritative persisted carrier inside the authorized surface; review also found the image-ID union incomplete; manifest carrier compatibility scope is required before any fix

ROLE: Implementer
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-floor-impl-2-b2-fold
PARENT_DISPATCH_ID: s4-floor-impl-2-b2-fold
RUN_ID: s4
TASK_ID: B2
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: yes — authorize or redesign the authoritative packer-home carrier across the manifest compatibility surface; the current amended head has two Critical review findings and must not be published or re-paneled as complete
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/IMPL-PLANNER-B2-CYCLE2-FOLD-DISPATCH-IMPL-TOKEN-20260808-222434.md
FROM: s4-floor.implementer
TO: s4-floor.planner
CC: s4.orchestrator-planner, operator
SUBJECT: BLOCKED after independent B2 cycle-2 review — true packer HOME is not persisted; manifest carrier paths are outside FOLD_SCOPE; do not publish 03e672ca

The authorized cycle-2 implementation completed at local amended head
`03e672ca839ae0832f69c3b480620ffafb252a68`, but the mandatory independent task review
returned two Critical findings against B2C2-2:

1. the implementation derives the home-prefix needle from each session's
   `record.original_path`, which is a workspace path, not authoritative packer-home
   evidence; a workspace outside the packer's home leaves the real home unscanned;
2. the image-wide ID union omits manifest child IDs on Claude, optional manifest parent
   IDs on both adapters, and message IDs from already-refused Claude rows.

The second Critical can be corrected inside the current installer/test scope. The first
cannot be corrected honestly inside it.

## Carrier audit

The pre-fix audit found:

- `Env.home` exists while discovery/pack runs but is not persisted into `SessionRecord`,
  `manifest::AgentSessionEntry`, or `Manifest`;
- `record.original_path` is the session workspace and may be completely outside HOME;
- `provenance.store_root` is not a home value: `CLAUDE_CONFIG_DIR` and `CODEX_HOME` may be
  arbitrary, and staged repacks replace it with staging `source_root`;
- therefore neither workspace-parent inference nor store-root inference can satisfy the
  ruled "packer home-dir prefix" invariant without false negatives or false authority.

A correct implementation needs an authoritative packed-home carrier written at pack time,
serialized in the manifest entry (or another master-approved compatibility shape), parsed
at open, and consumed only by the already-bounded session-install verifier. The minimal
currently visible compatibility surface is:

FOLD_SCOPE:
- `src/adapters/adapter.hpp` -> in (existing authorized carrier input, if selected)
- `src/core/pack/pack.cpp` -> in (existing authorized pack producer)
- `src/adapters/claude_code/install.cpp` -> in
- `src/adapters/codex/install.cpp` -> in
- existing authorized adapter/pack tests -> in
- `src/core/manifest/manifest.hpp` -> OUT (hard-excluded by the current fold scope)
- `src/core/manifest/manifest.cpp` -> OUT (hard-excluded by the current fold scope)
- `tests/test_manifest.cpp` -> OUT (not listed in the live token's SCOPE_DIFF)

FOLD_SCOPE_RESULT: deviation-present

If the approved carrier requires another schema/version/compatibility path, that path is
also a deviation and must be named by the grant before edit. No manifest, schema, producer,
installer, test, harness, or report-source edit was made during fix round 1 after the
review finding surfaced.

## State and earlier evidence

The local `03e672ca` amend remains exactly one commit over `ec9a2db`, with the original
subject preserved. Before review it passed the fresh `/tmp` host suite 14/14 selected rows
and the A3 11-check ceremony. Those tests do not overrule the review findings: the true-home
falsifier and complete parent/child/refused-row ID-union falsifiers were absent.

Do not publish `03e672ca`, do not convene the third re-panel as if the fold were complete,
and do not merge/release. Resume only after the manifest-carrier compatibility surface is
explicitly granted or a different authoritative in-scope carrier is ruled.

ACTIONS_GIT_REF: B2 worktree remains clean at local `s4-floor/b2-torn-tail@03e672ca839ae0832f69c3b480620ffafb252a68`; fix round 1 made no tracked edit or amend; origin branch and PR #23 remain at the prior published head pending verification; this blocker relay and its append-only INDEX row ride one explicit-path docs-lane commit
FINAL_GIT_STATUS_SHORT: B2 implementation worktree clean at unchanged reviewed head; main docs lane was clean before this relay and INDEX append

CARRY LIST:
- manifest carrier compatibility scope/ruling → `s4-floor.planner` + `s4.orchestrator-planner`
- Critical 2 complete image-ID union → implementer fix round after scope unblocks
- local B2 head `03e672ca` → HELD, not publishable
- third B2 re-panel → not yet eligible
- PR #23, merge, and release → held
