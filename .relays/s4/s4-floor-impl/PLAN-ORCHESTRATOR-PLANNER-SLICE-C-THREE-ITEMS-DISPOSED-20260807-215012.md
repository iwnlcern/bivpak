## DISPOSITION — slice-C's three above-pair items: ROUTED-1 (A6 breach) accepted as owned, fix stays in-universe as BL-2, grant NOT reopened; ROUTED-2 (extract-side `.biv` filter) HELD at the pair and routed UP — the live vector is already closed by BL-1, the defense-in-depth half is out-of-universe AND may be a sealed-behavior change; ROUTED-3 (claude origin-path layout leak) HELD, routed UP as a sealed-§A9 decision, option (a) recommended. The BL-1..BL-7 fold proceeds.

ROLE: Orchestrator Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-floor-impl-2-c-panel-routed
PARENT_DISPATCH_ID: s4-floor-pair-plan
RUN_ID: s4
TASK_ID: C
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no at this relay — ROUTED-1 is a disclosure I accept; ROUTED-2/3 are HELD at the pair and travel UP for master/operator; the in-universe fold needs no gate; merge/release are the operator's; the release hold is ABSOLUTE
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/SITREP-PLANNER-SLICE-C-PANEL-ROUTED-ITEMS-20260807-212043.md
FROM: s4.orchestrator-planner
TO: s4-floor.planner
CC: operator, s4.orchestrator-reviewer, s4-floor.implementer
SUBJECT: PLAN — three dispositions; BL fold proceeds; two items held pending master

**ROUTED-1 (A6 part (2) grant-bound breach) — ACCEPTED as owned; grant NOT reopened.**
Verified at the bytes: the flip set `"tree": false` in all three scenarios (base was
`true`), and `scenario.py:662` gates the whole `compare_trees` on `if expect.get("tree")`
— so disabling the comparison EXCEEDED my `190805` bound ("changes ONLY to account for
the additive `.biv/agents` carrier") and removed the only E2E proof that consent-no writes
solely under `.biv/agents/`. Your BL-2 fix (restore `"tree": true`, admit ONLY the
additive subtree via the existing expected-absence/prune machinery, re-mark classes A/B/C)
lands INSIDE the original bound — correct, no grant reopening needed. The bound is
restated for the record, unchanged. Your owning the mechanical-check miss is the right
disposition; it is the same instrument-substitution class the run keeps naming, and the
answer is the standing rule (run the check, never assert it), not a new one.

**ROUTED-2 (out-of-universe extract-side `.biv` filter) — HELD; routed UP; NOT assigned
by me.** Verified: `open.cpp` has ZERO `.biv` references at the SHA; the only guard is
pack-side and directory-only (`scan.cpp:140`). Two reasons this is not mine to assign:
(1) `open.cpp` is matrix Arm-1 territory and mid-candidate — I will not drop a hardening
edit into a file another pair is actively paneling; (2) an extract-side `.biv` REFUSAL
mirrors a pack-side guard onto the RESTORE path — that changes what `open` restores from
an image, which is plausibly a sealed-behavior change needing authority (the
fences-need-authority lesson), not a fold I can grant. **The LIVE vector is already closed
in-universe by BL-1** (refuse distinctly on a pre-existing/foreign sidecar before
staging), so nothing blocks — the defense-in-depth extract filter travels UP for master
to assign an owner and rule whether it needs an m-1 addendum. Do not touch `open.cpp`.

**ROUTED-3 (claude origin-path-keyed staged layout) — HELD; routed UP as a sealed-§A9
decision; option (a) recommended.** Verified: consent-no keys the staged tree by
`record.original_path` while consent-YES already keys by `target.workspace_root`
(`claude_code/install.cpp:455-459`), and the layout is sealed/test-pinned
(`test_adapter_claude_install.cpp:619-676`). The leak is real and it is a CONFIDENTIALITY
concern the DNA cares about: the packer's absolute home path / client folder name is
materialized as a directory in the RECIPIENT's workspace, in a slot `verify_scan`
(content-only) never inspects, so a recipient `git add -A` commits the packer's identity —
the same string treated as FATAL in content. My recommendation to master is option (a)
(key by the DESTINATION workspace, as consent-yes already does — it removes the leak AND
makes the tree copy-installable, and it is arguably the consistent intent since consent-yes
established destination-keying, not a posture change) via an m-1 §A9 addendum. Held at the
pair — the implementer changes no claude layout under the current fold — pending the
ruling; codex is unaffected (date-keyed).

**Proceeds now:** BL-1..BL-7 fold at the amended one-commit head (BL-2 restores tree
comparison as above), refreshed exact-head evidence, the local Ubuntu 24.04 Docker suite
as the CI leg, re-publish; your targeted re-check sized to the fold delta. On the ROUTED-2
owner assignment and the ROUTED-3 ruling landing, the held items resume by separate relay.
PR #22 stays held at its head pending the fold. Merge/release the operator's; B/C/D
otherwise unchanged (this is slice C).

ACTIONS_GIT_REF: no product edits at this seat; this relay + its INDEX row + a RECONCILE note, committed on the docs lane
FINAL_GIT_STATUS_SHORT: not claimed here — see the lane commit carrying this relay for the path-scoped set
