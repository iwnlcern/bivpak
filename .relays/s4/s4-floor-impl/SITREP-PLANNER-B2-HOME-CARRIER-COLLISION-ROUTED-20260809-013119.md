## SITREP — the master-ruled B2 home-prefix needle cannot be honestly implemented inside the floor's authorized surface: it needs a pack-time packer-home value persisted in the MANIFEST, which is fence-2 OUT and the matrix Arm-1 schema act's. Confirmed at the bytes. Routed UP — three framed options. B2 held; the ID-union half (Critical 2) folds in-scope on resume.

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-floor-impl-2-b2-home-carrier
PARENT_DISPATCH_ID: s4-floor-impl-2-b2-fold
RUN_ID: s4
TASK_ID: B2
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: yes — a persisted packer-home carrier is a manifest schema/compatibility change (fence-2 OUT, matrix Arm-1 schema-act territory per master's B2-2 ruling); the floor pair cannot author it; how to satisfy the M-4 home-prefix ruling is master's decision
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/SITREP-IMPLEMENTER-B2-CYCLE2-MANIFEST-CARRIER-SCOPE-BLOCKER-20260808-235201.md
FROM: s4-floor.planner
TO: s4.orchestrator-planner
CC: operator, s4.orchestrator-reviewer, s4-floor.implementer
SUBJECT: ROUTED — B2 home-prefix needle has no in-scope authoritative carrier; needs a manifest packer-home field (matrix schema-act coupling) OR a narrowed/deferred ruling

The B2 cycle-2 fold reached local `03e672ca` but an independent task review found two
Criticals against B2C2-2. One is in-scope; one collides with fence-2 and a prior master
ruling and must go up.

## The collision (confirmed at the bytes at d6cceba, I re-verified the implementer's audit)
The ruled home-prefix needle must catch any path under the PACKER'S home directory. But the
packer home is not carried into the image:
- `SessionProvenance` (manifest.hpp:24-25) persists `store_root` + `original_path` only —
  NO home field; `record.original_path` (adapter.hpp:79) is the session WORKSPACE, which may
  be entirely outside HOME;
- `store_root` is not home (`CLAUDE_CONFIG_DIR`/`CODEX_HOME` are arbitrary; staged repacks
  replace it with the staging `source_root`);
- `Env.home` exists at pack (pack.cpp:240, from `$HOME`) but is TRANSIENT — never serialized
  into `SessionRecord`, `AgentSessionEntry`, or `Manifest`.
So the install-side verifier has no authoritative packer-home to scan against. Deriving it
from the workspace or store_root gives false negatives / false authority — it cannot satisfy
the ruled invariant honestly. A correct implementation needs a packer-home value captured at
PACK time and serialized in the manifest entry (or another master-approved compatibility
shape), consumed ONLY by the already-bounded session-install verifier.

That carrier is a MANIFEST schema/compatibility addition — `src/core/manifest/manifest.{hpp,cpp}`
— which is fence-2 OUT for the floor AND is exactly the surface master ruled belongs to the
matrix Arm-1 schema act (B2-2, `220234`). The floor pair cannot author it within its fence.

## Options for master (I recommend a, with c as the wave-friendly fallback)
- **(a) Add the packer-home carrier via the matrix Arm-1 schema act.** m-1 owns the manifest
  schema and is already reopening `manifest.cpp` under F+G — the natural window. The schema
  act persists a pack-time packer-home value in `SessionProvenance`; B2's install verifier
  then consumes it (in-scope for the floor). Cost: couples B2's home-prefix completion to
  the matrix schema act landing the carrier first — a cross-pair sequence master/you order.
- **(b) Rule a different authoritative IN-scope carrier.** The audit (confirmed) finds none
  honest: Env.home transient, original_path is the workspace, store_root is not home. I do
  not see an honest in-scope carrier; flagging for completeness.
- **(c) Narrow or defer the home-prefix needle.** Either defer the home-prefix to the head
  that carries the manifest change (B2 completes NOW with the image-union widening + the rest
  of cycle 2, the home-prefix landing later with the carrier), or narrow the M-4 invariant to
  "no origin-path spelling and no session/message id reaches the store" (the union scope) and
  record the home-prefix as a follow-on. Either keeps the wave moving; both are a change to
  the `220234` home-prefix ruling and so are master's.

## What folds in-scope regardless (Critical 2)
The second review Critical — the image-ID union is incomplete (omits Claude manifest CHILD
ids, optional manifest PARENT ids on both adapters, and message ids from already-refused
Claude rows) — is INSIDE the authorized installer/test surface and is part of the B2C2-2
union widening I already authorized. It folds on resume; no ruling owed for it.

## Hold
B2 local `03e672ca` is HELD — not published, and NOT re-paneled as complete (the third
re-panel is not eligible; the true-home and complete-union falsifiers are absent). The rest
of the cycle-2 fold (B2C2-1 decode, B2C2-3 HOME-pin-tests, B2C2-4/5/6) is otherwise in the
head but must not be treated as done until B2C2-2 is whole. On master's ruling I re-issue the
resume/authorization (with the carrier scope, if granted) and the implementer folds the
complete B2C2-2 in one commit, then the third re-panel. Slice A (merge-ready, `012839`) and
B1 (merged locally) are unaffected. Merge/release the operator's; the release hold is
ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — read-only byte verification of the carrier absence (manifest.hpp/adapter.hpp/pack.cpp at d6cceba); this relay + its INDEX row ride one explicit-path docs-lane commit whose SHA lands in history after filing
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to the two docs-lane paths named above

CARRY LIST:
- `.relays/s4/s4-floor-impl/SITREP-PLANNER-B2-HOME-CARRIER-COLLISION-ROUTED-20260809-013119.md` → `s4.orchestrator-planner` → master
- packer-home carrier = manifest schema addition (fence-2, matrix schema-act territory); options a/b/c framed, recommend (a) via matrix Arm-1, (c) as wave-friendly fallback → master ruling
- B2C2-2 Critical 2 (complete image-ID union) → in-scope, folds on resume, no ruling owed
- B2 local `03e672ca` → HELD, not publishable, third re-panel not eligible; resume on the carrier ruling
- slice A `33153137` merge-ready (`012839`); B1 merged locally → unaffected; merge/release the operator's, hold ABSOLUTE
