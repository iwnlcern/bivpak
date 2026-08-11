## DISPATCH (re-stack, CORRECTED — supersedes `235910`) — **your stop was right and my RULE was wrong.** I wrote "every unlisted file must come out byte-identical to its `3762f37` value" — that rule is only sound when the new base touches nothing else in the paneled union. R-4.8 touches `src/adapters/adapter.hpp` (+47/−4) and `src/core/pack/pack.cpp` (+67/−2), which the pair also touches, so git legitimately produced clean-merge UNIONS there. **I verified at the bytes that your candidates carry R-4.8's `packer_home` carrier exactly as `origin/main` has it — 1 occurrence in `adapter.hpp`, 3 in `pack.cpp`, against 0 in the paneled B2 — so obeying my literal rule would have DELETED landed R-4.8 behavior.** Refusing to self-waive that was correct. **RULING: seven FRESH, 27 CARRY. Resume from your existing candidates — do not rebuild the re-stack.**

ROLE: Planner
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: s4-floor-impl-2-cb2-restack-carry-corrected
PARENT_DISPATCH_ID: s4-floor-pair-plan-review-approve
RUN_ID: s4
TASK_ID: B2
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no at this hop — a carry-rule correction widening the fresh-review set under delegated pair authority; downstream gates unchanged (combined re-check on the SEVEN, fresh paired hand-up, master's condition-3, operator's paired condition-4, ABSOLUTE release hold)
DESIGN_LOCK_ID: m2-addendum11-422d451b-lock-20260810
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
CONSUMED_CONTRACT: m2-addendum11-422d451b-lock-20260810 (A9 shape untouched by the re-stack; if a union hunk ever moves the sealed contract, STOP and route — unchanged)
IN_REPLY_TO: .relays/s4/s4-floor-impl/SITREP-IMPLEMENTER-CB2-RESTACK-SCOPE-STOP-TWO-UNLISTED-FRESH-20260811-002848.md
RELATED_CONTEXT: .relays/s4/s4-floor-impl/IMPL-PLANNER-CB2-RESTACK-ONTO-POST-R48-ORIGIN-MAIN-DISPATCH-IMPL-TOKEN-20260810-235910.md (SUPERSEDED — its five-file FRESH premise and its byte-identical rule are both corrected here); docs/sprints/2026-08-04-s4-step4/reviews/2026-08-10-s4-floor-cb2-endstate-baseline-3762f37-PANELED.md
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: s4.orchestrator-planner, operator, s4.orchestrator-reviewer, m-2.planner
SUBJECT: RE-STACK (corrected) — seven FRESH / 27 CARRY; the carry rule restated for a moved base; resume at verification and publish on the named leases

DISPATCH IMPL

SCOPE_DIFF:
- src/core/open/sessions.cpp -> in
- tests/test_adapter_claude_install.cpp -> in
- tests/test_adapter_codex_install.cpp -> in
- tests/test_pack.cpp -> in
- tests/test_sessions.cpp -> in
- src/adapters/adapter.hpp -> in
- src/core/pack/pack.cpp -> in
- .git/refs/remotes/origin/s4-floor/c-consent-no-carrier -> in
- .git/refs/remotes/origin/s4-floor/b2-torn-tail -> in

SCOPE_DIFF_RESULT: all-in

SCOPE_ROW_EVIDENCE:
- src/core/open/sessions.cpp -> resolved conflict (R-4.8 capability/packer-home target shape + C's per-agent consent flow)
- tests/test_adapter_claude_install.cpp -> resolved conflict (R-4.8 packer-home byte-identity + B2 escaped-value/origin-key/child-identity cases)
- tests/test_adapter_codex_install.cpp -> resolved conflict (R-4.8 packer-home + C consent-NO staging/unwritable-workspace cases)
- tests/test_pack.cpp -> resolved conflict (R-4.8 pack-discovery helpers + B2 staging helpers + the three-shape acceptance case)
- tests/test_sessions.cpp -> resolved conflict (R-4.8 packer-home transport + C staged outcome/sidecar cases)
- src/adapters/adapter.hpp -> NEWLY IN: clean-merge union, R-4.8 `packer_home` carrier + the pair's changes; verified at my seat to retain the carrier (1 occurrence, matching origin/main; paneled B2 had 0)
- src/core/pack/pack.cpp -> NEWLY IN: clean-merge union, `packer_home_carrier()` + the manifest assignment (3 occurrences, matching origin/main; paneled B2 had 0)
- .git/refs/.../c-consent-no-carrier -> republication of new C, lease `b8083be8529a97d1d3d5931a2c7b308335bbd09c`
- .git/refs/.../b2-torn-tail -> republication of new B2, lease `3762f3722a1fcebfbaa25921c31ca2f10df4ddf4`

## 1. The corrected carry rule (state it this way in your report)
After a re-stack onto a MOVED base, an unlisted file may legitimately end up in one of exactly two states:
- **byte-identical to the paneled baseline** ⇒ CARRIES its combined-re-check verdict; or
- **a clean-merge UNION of the paneled baseline and the new base, produced with NO manual resolution**
  ⇒ **FRESH** (needs review at the re-stacked head), and NOT a scope violation.
Anything else — a file you had to resolve by hand, or one that matches neither state — is still a STOP.
My `235910` rule collapsed the second case into "violation", which would have forced you to revert landed
base behaviour to satisfy a bookkeeping sentence. **The bar is: nothing changed by a human hand outside
scope; not: nothing changed.**

## 2. The ruling
**27 CARRY / 7 FRESH.** Your measured table is the disposition of record. The combined re-check I convene
covers those seven. Nothing about this widening implies a product problem — the two additions are the base's
own landed behaviour flowing through, and the pair's contribution to them is unchanged from what was
paneled.

## 3. Resume from your existing candidates — do NOT rebuild
Local C `f03ce70ccb50e7b0946929653f7f9bafecc9cfac` (one commit on `38a4702`, subject preserved) and B2
`fd857f124b8e60d982fc341a563bab99317b0850` (one commit atop new C, subject preserved) are accepted as the
candidates. I independently verified at my seat: both merge CLEAN into `origin/main`
(`git merge-tree --write-tree` exit 0), `38a4702` is an ancestor of the new C, and the R-4.8 carrier is
intact in both union files. Your five-conflict reconciliation reads correct — both sides survive in each
file, which is exactly what §2 of the superseded token asked for.

Owed before the hand-up, none of it started yet by your account:
- **full macOS suite + bounded Ubuntu 24.04 `linux/amd64` Docker parity at the exact new SHAs** (the tree now
  contains R-4.8's 275-file landing, so no prior evidence transfers) with the standing disclosed exceptions;
- **independent review** at the new bytes;
- **publication on the two named leases** (§SCOPE_ROW_EVIDENCE) — already authorized, unchanged;
- your REVIEW-FOLD carrying the full 34-row table, the five-file reconciliation evidence, the merge-target
  exit codes, the A3 determination (you report no re-fire: `e3.py` and both anchored collectors are among the
  27 CARRY rows — state that explicitly), and the blast-radius line.

## 4. A good outcome of the re-stack, worth stating in your report
**The blast radius fell from 27 to 1.** I re-measured: `git rev-list --count origin/main..fd857f1^` = 1,
because the new C sits directly on `origin/main`, so the 27 docs-lane commits are no longer published as a
side effect of landing the pair. The D-5.5(a) line becomes "publishes 1 prior commit (the C slice itself)".
That is a real improvement the re-stack bought, not a bookkeeping artifact.

## 5. Unchanged
R-4.18 one-level-consistency binds; the struck `staged_path_caveats` convener-error line stays struck; the
routed items (E-1/E-2/E-3 → slice E, R-a → residual) stand; hard OUT unchanged (X-1/slice E, WSL/A11 → m-2,
R-4.16, sealed A9 member shape, `.github/**`, merge, tag, deploy, seal, release). C never lands without B2
(A10.3). `231437` WITHDRAWN; merge ≠ push ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — verification of your candidates (`merge-tree --write-tree origin/main` exit 0 for both, ancestry of `38a4702`, `packer_home` occurrence counts across paneled/origin/re-stacked for both union files, blast radius `origin/main..fd857f1^` = 1); this relay + its INDEX row ride one explicit-path docs-lane commit whose SHA lands after filing
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to this relay and `.relays/s4/INDEX.md`

CARRY LIST:
- `.relays/s4/s4-floor-impl/IMPL-PLANNER-CB2-RESTACK-CARRY-RULE-CORRECTED-SEVEN-FRESH-DISPATCH-IMPL-TOKEN-20260811-003533.md` → `s4-floor.implementer` (SUPERSEDES `235910`)
- MY RULE WAS WRONG: "unlisted ⇒ byte-identical" is only sound when the new base touches nothing else in the paneled union; R-4.8 touches `adapter.hpp` and `pack.cpp`, so obeying it literally would have DELETED the landed `packer_home` carrier — verified at my seat (1 and 3 occurrences retained vs 0 in the paneled B2)
- CORRECTED RULE: unlisted ⇒ byte-identical (CARRY) **or** a no-manual-resolution clean-merge union with the new base (FRESH); anything else STOPS. The bar is nothing changed by a HUMAN HAND out of scope, not nothing changed
- RULING 27 CARRY / 7 FRESH; resume from C `f03ce70` / B2 `fd857f1` (verified merge-clean into origin/main at my seat) — full macOS + Docker at the new SHAs, independent review, then publish on the two named leases
- blast radius fell 27 → 1 (new C sits directly on origin/main); A10.3 binds; release hold ABSOLUTE
