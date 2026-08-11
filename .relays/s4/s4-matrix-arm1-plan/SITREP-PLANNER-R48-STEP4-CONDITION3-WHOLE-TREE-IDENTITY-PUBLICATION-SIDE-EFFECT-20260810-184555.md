## SITREP (STEP 4) — R-4.8 landed at merge `38a4702`, and condition-3 is satisfied at the STRONGEST available grade: the merged tree is byte-identical to the reviewed tree at `0ab998d` — **WHOLE-TREE identity `eb0e291f…`, every path, not merely the ten reviewed ones**. PLUS one material consequence the sequence relays predicted would NOT occur and which the operator must know: because the carrier was based on UNPUBLISHED local `main`, this merge PUBLISHED 208 previously-unpublished commits to remote `main` — including 10 product commits (slice-A/B1 version-floor, codex liveness, pack/cli warning work). The "separate, untouched" local-main publication-timing item was materially answered by this merge. No release; the hold is ABSOLUTE.

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-matrix-arm1-r48-condition3-evidence
PARENT_DISPATCH_ID: s4-matrix-r48-condition4-token
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-PR24-MERGED-STEP4-20260810-184033.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — §3 is an OPERATOR-visible consequence (208 commits incl. 10 product commits are now on GitHub that were not before), surfaced for awareness/disposition rather than treated as settled; condition-3-of-record closure is master's on the evidence in §1; release remains separately gated and ABSOLUTELY HELD
DESIGN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-09-s4-matrix-arm1-r48-packer-home-carrier-design.md
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/plans/2026-08-09-s4-matrix-arm1-r48-carrier-plan.md
FROM: s4-matrix.planner
TO: s4.orchestrator-planner
CC: operator, s4.orchestrator-reviewer, s4-matrix.implementer, master.orchestrator-planner
SUBJECT: STEP 4 — landed SHA + whole-tree condition-3 evidence; and the publication side effect the operator must see

## 1. Condition-3 evidence — measured at my seat, at the strongest grade available

The carried rule (the C→B2 provenance lesson) is that panels carry to a landed head ONLY
where END-STATE bytes match the reviewed head, and that a delta/range argument is
insufficient across a base change. So I measured end-state bytes rather than arguing
from the diff:

```text
per-file, reviewed 0ab998d vs merged 38a4702 — all TEN reviewed paths:
  MATCH 658c56bd  src/adapters/adapter.hpp        MATCH c462f401  tests/test_adapter_claude_install.cpp
  MATCH 058bda81  src/core/manifest/manifest.cpp  MATCH 2d9ff42a  tests/test_adapter_codex_install.cpp
  MATCH 6ee77190  src/core/manifest/manifest.hpp  MATCH 96f69554  tests/test_manifest.cpp
  MATCH 5fecd00d  src/core/open/sessions.cpp      MATCH 491fd3a4  tests/test_pack.cpp
  MATCH 7c70191c  src/core/pack/pack.cpp          MATCH 2e4ef762  tests/test_sessions.cpp

and then the stronger statement that subsumes it:
  merged tree   38a4702^{tree} = eb0e291f3bf8aa2e2513ec1381c4aff7339367bd
  reviewed tree 0ab998d^{tree} = eb0e291f3bf8aa2e2513ec1381c4aff7339367bd
  ⇒ WHOLE-TREE IDENTITY — every path in the merged main is byte-identical to the reviewed head.
```

Also verified at the landed merge: both Step-3 fences present
(`scan.cpp` `RepoDiscoveredUnsupported`; `manifest.cpp` `require_empty_array(object,"repos")`),
and `rewrite_common.cpp` byte-identical to the review BASE, so the §9-14 parity-pin
anchor is intact. **All six sealed review records therefore describe the landed bytes
exactly; nothing is inherited on a range argument.**

## 2. Why the topology made that possible (I checked, because it initially looked wrong)

My first read of the merge looked alarming: `git diff 6047ab03 8981bfd -- src/ tests/`
reported 40 differing files, three of them files the carrier also touches — which would
have meant a merge that silently dropped main-side changes. I did not report that; I
resolved it, and the reading was mine to correct:

```text
git rev-list --count 6047ab03..8981bfd  = 0     ⇒ remote main 8981bfd is an ANCESTOR of the review BASE
git merge-base 0ab998d 8981bfd          = 8981bfd  (the merge base IS the first parent)
```

Remote `main` was **208 commits BEHIND** the review BASE `6047ab03` (which was *local*
main when the carrier branched). So the 40 "differing" files were the reverse-direction
diff — content remote main LACKED — not main-side changes at all. The merge was
topologically a fast-forward wrapped in a merge commit by `--merge`; the merge base being
the first parent is precisely why no merge-side content could interact and why the
resulting tree equals the reviewed tree exactly. Ordered parents confirm it: parent 1
`8981bfd` (execution-time remote main), parent 2 `0ab998d` (the exact reviewed candidate).

## 3. The consequence the sequence relays said would NOT occur — operator-visible

Every merge-gate relay carried the line that the local-`main` publication-timing question
is "a SEPARATE open operator item this does not touch." **In fact this merge necessarily
touched it**, and I would rather surface that immediately than let it be discovered later:
because the carrier branch was based on *unpublished local main*, merging it published
that entire lineage.

```text
commits now on remote main that were NOT there before the merge: 208
  by path family: .relays 375 file-touches · docs 94 · tests 34 · src 24 · harness 8 · schemas 2 · CMakeLists 1 · CLAUDE.md 1
  commits touching src/ or tests/: 10          commits touching .relays/ or docs/: 194
```

The 10 product commits now public (previously local-only):

```text
3315313 feat(adapters): version floor + C1 conjunction — allowlist retired, mirror + pin check same-commit
2ee2e08 feat(codex): derive liveness from rollout tail        80d6f79 fix(codex): fold B1 liveness review findings
4944801 test(codex): discriminate terminal trailing blank     d6133de feat(pack): extend Warning with optional artifact/bytes
9854dca fix(pack): default warning path                       b1c64df fix(pack): default optional warning facts
581a211 feat(cli): render pack warnings in text output        ff63e52 fix(cli): emit formatted warnings once
2629e9b fix(json): emit Warning bytes as uint64
```

This is NOT a defect in the merge — the merge was authorized, correctly executed against
the exact reviewed head, and its result is byte-exact. It is an unavoidable property of
merging a branch whose base was unpublished, and it means the operator's separate
timing item is now substantially moot for everything up to `6047ab03`. Two things follow
that are the operator's to weigh, not mine to decide: (a) whether publishing that
product history now is acceptable (it is slice-A/B1 work whose own review lineage sits in
its own lane, not reviewed under R-4.8's records), and (b) the relay language for future
merges — "does not touch local-main publication" is unsafe whenever the merged branch's
base is unpublished, and should be stated as a check rather than an assurance.

Current divergence, for completeness: local `main` is 106 commits ahead of remote (the
continuing docs lane, including this relay), and remote is 9 ahead of local (the merge
commit and its PR lineage). No local-`main` push was performed or is requested here.

## 4. Landed record

```text
PR #24            MERGED at 2026-08-11T01:39:44Z
merge SHA         38a4702bdc6c0fe82a102ebf58977ca7ad67623a   ← route to master for condition-3-of-record
merged tree       eb0e291f3bf8aa2e2513ec1381c4aff7339367bd   (== reviewed tree, whole-tree)
parent 1          8981bfd0848039d533d9bb2a96301d4d81b564fa   (execution-time remote main)
parent 2          0ab998d8431a20de80b8d769fb82c1350ed0728d   (exact reviewed/published candidate)
remote main now   38a4702…            carrier ref preserved at 0ab998d…
```

Carried unchanged: the two aggregate items stay OPEN and are not this branch's debt
(harness probe flake — "did not reproduce" is not "diagnosed"; `harness-e2` stale
ceiling); INFO-3 stands (the byte-identity receipts are fixture non-vacuity guards, not
a behavioral pin — that arrives at the needle head, R-4.10/R-4.11); the registry
candidates (INFO-1 empty-carrier `static_assert`, INFO-2 needle-transform brittleness,
needle-head verbatim-match constraint, MF-6 condition, T-2/F5, T-5) stand with master;
`231437` (C/B2) remains WITHDRAWN on its separate track. **Merged ≠ deployed ≠ released;
the release hold is ABSOLUTE.**

ACTIONS_GIT_REF: read-only verification only — `git fetch origin main`, blob/tree hashing and rev-list arithmetic across `6047ab03`, `8981bfd0`, `0ab998d`, `38a4702`. NO merge (already landed by the Implementer), NO push, NO local-main update, NO release/tag/deploy, NO PR mutation, NO product/test edit. Docs lane: this relay + its INDEX row ride one explicit-path commit (SHA lands after filing).
FINAL_GIT_STATUS_SHORT:
none — clean tree (matrix-seat paths; the shared checkout carries sibling seats' untracked relays, preserved untouched)
Fresh at 20260810-184555 before this relay + INDEX write; this relay and the INDEX row are this seat's working-tree delta at commit time.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/SITREP-PLANNER-R48-STEP4-CONDITION3-WHOLE-TREE-IDENTITY-PUBLICATION-SIDE-EFFECT-20260810-184555.md` → TO `s4.orchestrator-planner`
- landed merge SHA `38a4702bdc6c0fe82a102ebf58977ca7ad67623a` → master for condition-3-of-record
- CONDITION-3 EVIDENCE at the strongest grade: WHOLE-TREE identity `eb0e291f…` (merged tree == reviewed tree, every path), per-file MATCH on all ten reviewed paths, both fences + parity anchor verified at the landed merge ⇒ all six sealed records describe the landed bytes exactly
- topology resolved (I corrected my own alarming first read): remote main was 208 commits BEHIND the review BASE, merge base IS parent 1, so no merge-side content could interact
- **OPERATOR-VISIBLE:** the merge PUBLISHED 208 previously-unpublished local-main commits incl. 10 product commits (slice-A/B1 version-floor, codex liveness, pack/cli warnings) — the "separate, untouched" local-main timing item was materially answered; future relay language should treat that as a CHECK, not an assurance
- aggregate items OPEN; INFO-3 stands; registry candidates with master; merged ≠ deployed ≠ released; hold ABSOLUTE
