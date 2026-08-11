## SITREP — option-(a) dispatch is structurally live but blocked before edit by a child-map contract contradiction

ROLE: Implementer
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-floor-impl-2-cb2-option-a-contract-blocker
PARENT_DISPATCH_ID: s4-floor-impl-2-cb2-option-a
RUN_ID: s4
TASK_ID: B2
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: yes — the pair Planner must reconcile the dispatch's mutually exclusive child-ID minting and IdMapEntry.children requirements before implementation; release hold remains ABSOLUTE
DESIGN_LOCK_ID: m2-addendum11-422d451b-lock-20260810
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/IMPL-PLANNER-CB2-OPTION-A-DISPATCH-IMPL-TOKEN-20260810-215715.md
FROM: s4-floor.implementer
TO: s4-floor.planner
CC: s4.orchestrator-planner, operator, s4.orchestrator-reviewer, m-2.planner
SUBJECT: BLOCKED BEFORE EDIT — current bytes prove child_ids minting STAYS and IdMapEntry.children becomes IDENTITY cannot both hold; clarify L-3 surviving surface

BLOCKED BEFORE FOLD_SCOPE / TEST / PRODUCT EDIT

The dispatch is structurally live: its exact relay passes relay lint, contains one bare
own-line implementation token, and addresses only this Implementer in TO. The existing
linked product worktree is clean on `s4-floor/b2-torn-tail` at exact B2
`e0d6c1994e286291cc7ab3439228edbb65f048a4` over exact C
`b8083be8529a97d1d3d5931a2c7b308335bbd09c`.

Critical plan review found one contract contradiction in the current bytes. I stopped
before authoring FOLD_SCOPE, changing tests, or changing production code rather than
choosing one side implicitly.

## Contradiction — child minting versus identity map

The dispatch states all three of the following:

1. `child_ids` minting STAYS;
2. exactly one removal is authorized, the child-alias arm;
3. under option (a), `IdMapEntry.children` becomes an IDENTITY map.

The implementation makes (1) and (3) mutually exclusive:

- `src/adapters/claude_code/install.cpp:810-812` appends
  `{child.original_id, uuid4()}` to `session.child_ids`;
- `src/adapters/claude_code/install.cpp:1099-1102` writes
  `IdMapEntry.children = session.child_ids` without another transform;
- `src/core/open/sessions.cpp:170-177` consumes each pair's second value as an installed
  child identifier when forming staged-path caveats, so the value is observable
  downstream rather than inert report prose.

Therefore, if `child_ids` minting stays, `IdMapEntry.children` remains an
`origin -> minted UUID` map and is not identity. Making it identity requires changing
the mint or substituting a different result map, contradicting the exact-one-removal
guardrail and changing the downstream contract.

## Required ruling

Please amend the dispatch with one coherent branch:

- Branch A: `child_ids` minting stays and `IdMapEntry.children` remains non-identity;
  withdraw the rider-2 identity-map statement. Option (a) then removes only the
  content-derived `child_alias_ids` arm and its `agentId` needles.
- Branch B: `IdMapEntry.children` must become identity; explicitly authorize the
  necessary child-ID/result-map change, its downstream consumer proof, and any expanded
  scope. This supersedes the current instruction that `child_ids` minting stays and
  exactly one removal is authorized.

## Secondary L-3 surface clarification

The Claude-specific `child_identity_shape` check is reached only through the `agentId`
alias harvest in `install.cpp:906-951`. Fully stopping `agentId` needling makes that
scanner and shape check dead. The shared token-boundary rewrite guard in
`src/adapters/rewrite_common.cpp` remains active for session/message/declared-child ID
pairs without any edit.

Please confirm that “L-3 stays” means the shared boundary-aware rewrite plus strict
verification remain unchanged while the now-unused Claude alias scanner/shape check
folds away. If the Claude-specific shape check must remain operational, name the
authorized non-`agentId` input that should feed it; inventing one would broaden scope.

## Tests and scope observations

The conditional Codex inspection found no symmetric content-derived `agentId` alias
needle in `src/adapters/codex/install.cpp`; no Codex production or test edit is
currently justified.

Several active tests, not only the hidden pending tests, encode the old alias-rewrite
contract, including the M-1 attribution test and the staged-pack unattributed-alias
round trip. They can be retargeted within the dispatched Claude test paths after the
contract ruling. No test was changed or run because the plan review blocker precedes
the TDD and baseline-execution steps.

Hard OUT remains untouched: X-1/slice E, R-4.16, A9 member shape, WSL/A11 formula,
`.github/**`, merge, tag, deploy, seal, and release.

Requested next action: issue a corrected direct carry-down selecting Branch A or B and
answering the L-3 surviving-surface question. On a coherent ruling I will author the
pre-edit FOLD_SCOPE, run the retargeted falsifiers RED, implement minimally, and run the
required host and local Ubuntu amd64 evidence.

C never lands without B2 (A10.3).

The release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/test/branch/PR mutations; product worktree read-only verified clean at e0d6c1994e286291cc7ab3439228edbb65f048a4; this blocker SITREP and one append-only INDEX row are the only docs-lane writes
FINAL_GIT_STATUS_SHORT: product worktree none — clean; shared docs checkout retains pre-existing sibling untracked state, preserved; this filing adds only the named blocker and its INDEX row

CARRY LIST:
- `.relays/s4/s4-floor-impl/SITREP-IMPLEMENTER-CB2-OPTION-A-CONTRACT-CONTRADICTION-BLOCKER-20260810-220519.md` -> `s4-floor.planner`
- BLOCKER: child_ids are `{origin, uuid4()}` and directly become `IdMapEntry.children`; minting STAYS and identity-map consequence cannot both hold
- choose Branch A (mint stays, map remains non-identity) or Branch B (authorize map/mint contract change and expanded proof)
- clarify L-3 as shared boundary guard surviving versus an operational Claude alias-shape check after agentId de-needling
- no product/test/PR/Actions action; release hold ABSOLUTE
