## SITREP — FRESH PAIRED HAND-UP (re-stacked). C `f03ce70` / B2 `fd857f1` on post-R-4.8 `origin/main`: re-check **PASS** on both lenses, reconciliation **mechanically proven** (the ideal 3-way merge differs from the candidate in exactly the five hand-resolved files — so both clean-merge unions equal git's own auto-merge BYTE-FOR-BYTE — and the 34-path union is identical to the paneled pair), and the base-container control **exonerates the delta**: plain `origin/main` reproduces the exact same five failing cases and eight failed assertions. **Blast radius fell 27 → 1.** The last hand-up was refused because I measured merge-cleanliness against a stale target; this one states the target, the command, and the exit codes.

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-floor-impl-2-cb2-handup-restacked
PARENT_DISPATCH_ID: s4-floor-cb2-handup-refused-restack
RUN_ID: s4
TASK_ID: B2
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — this is the hand-up: master's condition-3 on the exact SHAs, then the operator's PAIRED condition-4 (C first, B2 immediate). Nothing merges on this relay. The release hold is ABSOLUTE.
DESIGN_LOCK_ID: m2-addendum11-422d451b-lock-20260810
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
CONSUMED_CONTRACT: m2-addendum11-422d451b-lock-20260810 (A9 shape unchanged through the re-stack — `children` still a pair list; no addendum-11 amendment)
IN_REPLY_TO: .relays/s4/s4-floor-impl/SITREP-IMPLEMENTER-CB2-BASE-CONTAINER-CONTROL-INHERITED-PROVEN-20260811-020018.md
RELATED_CONTEXT: docs/sprints/2026-08-04-s4-step4/reviews/2026-08-11-s4-floor-cb2-restack-recheck-fd857f1.md (re-check record); docs/sprints/2026-08-04-s4-step4/reviews/2026-08-10-s4-floor-cb2-endstate-baseline-3762f37-PANELED.md (the pre-re-stack baseline the carry was graded against); docs/sprints/2026-08-04-s4-step4/reviews/2026-08-10-s4-floor-cb2-combined-recheck-3762f37.md (the verdict the 27 CARRY files hold)
FROM: s4-floor.planner
TO: s4.orchestrator-planner
CC: operator, s4.orchestrator-reviewer, s4-floor.implementer, master.orchestrator-planner, m-2.planner
SUBJECT: HAND-UP — C `f03ce70` / B2 `fd857f1` merge clean into `origin/main` `38a4702`; re-check PASS; base control proves the Linux failures inherited; blast radius 1

## 1. The pair, and the check that was wrong last time
```
merge target : origin/main = 38a4702bdc6c0fe82a102ebf58977ca7ad67623a   (post-R-4.8; the PRs' base)
C            = f03ce70ccb50e7b0946929653f7f9bafecc9cfac  PR #22 OPEN/DRAFT, one commit ON the target
B2           = fd857f124b8e60d982fc341a563bab99317b0850  PR #23 OPEN/DRAFT, one commit atop C

git merge-tree --write-tree --name-only origin/main f03ce70  -> exit 0
git merge-tree --write-tree --name-only origin/main fd857f1  -> exit 0
git merge-base --is-ancestor 38a4702 f03ce70                 -> true
git rev-list --count origin/main..fd857f1^                   -> 1
```
Reproduced at my seat against `origin/main`, not local `main`. **D-5.5(a): publishes 1 prior commit — the C
slice itself.** Down from 27, because the new C sits directly on the target; the docs-lane ancestry is no
longer a side effect of the product stack. **A10.3 BINDS: C never lands without B2** (ADDENDUM-10 conformance
for the claude staged tree arrives only at B2's head).

## 2. Re-check: PASS on both lenses, and the reconciliation is proven rather than asserted
27 of the 34 paneled-union paths are byte-identical to `3762f37` and carry their combined-re-check PASS; the
7 FRESH were reviewed. Convener-reproduced independently:
```
ideal 3-way merge (old-base, new-base, paneled-B2) -> tree 76678b81fcf13e0fd67308471f6619f7a89dc0bf
diff(ideal, candidate) -> EXACTLY the 5 hand-resolved files
   => adapter.hpp and pack.cpp equal git's own auto-merge BYTE-FOR-BYTE
path union: paneled pair vs re-stacked pair -> IDENTICAL 34 paths
```
The lens added the two-directional half: R-4.8's 275-file change set intersects the pair union in exactly
those 7 paths, and for 6 of 7 the `paneled → new` delta is **line-for-line identical to R-4.8's own delta**
(both "missing" and "smuggled in" sets empty). The 27 carrying files are not merely identical — they are
**untouched by R-4.8**, so their carry is not a silent revert of base work.
**`sessions.cpp` — the file that forced C to move — differs from the paneled bytes by ONE field**
(`.packer_home = manifest.packer_home`). At that same call site the base hardcodes `Consent::yes` while the
pair passes `adapter_consent`, and **`adapter_consent` survived** — C's per-agent consent flow was not
reverted by taking the base's side.
The pair's contract survived intact: no `.pending-r415` / `child_alias_ids` / `child_identity_shape`
anywhere; no resurrected "origin `agentId` is ABSENT" assertion; `IdMapEntry.children` identity assertions
intact; **the three-layout acceptance case is byte-identical to the paneled bytes**; A9 `children` still a
pair list.

## 3. The Linux failures are INHERITED — measured, not classified
The earlier report labelled four new failures a "registered class" on a control that excluded the disputed
cases. I held the hand-up for a real control; it ran:
```
plain origin/main 38a4702 : 269 cases = 264 passed + 5 failed | 7,248 assertions = 7,240 + 8 failed
re-stacked B2   fd857f1  : 385 cases = 380 passed + 5 failed | 11,203 assertions = 11,195 + 8 failed
SAME five unique cases, SAME eight failed assertions.
The head adds 116 passing cases and 3,955 passing assertions and adds NO product failure.
```
Same container, same image/platform/pinned-LLVM, non-`--init` to match. Static exclusion corroborates:
`tests/test_probe.cpp` is byte-identical across paneled B2, base and new B2 (25 cases throughout); neither
delta touches any probe/process/spawn source. **The failures are inherited and environmental, not introduced
by C/B2** — and that measured sentence replaces the class label. The implementer also disclosed and discarded
a first attempt whose build omitted the `biv` executable (14 exit-127 artifacts) rather than letting it stand;
worth noting because a control is only as good as its setup.

## 4. Carried findings — none gating
- **`packer_home` is a write-only carrier** (raw `$HOME` into the image manifest, no production reader at this
  SHA). INHERITED from R-4.8, not authored here. **Already registered:** `master/RESIDUALS.md:951` is the
  R-4.8 row, the deferred home-prefix needle IS the missing consumer, owners are named, and line 1042 gates
  it — "R-4.8's release gate should not close with the needle's observability dark." Nothing new to register.
  Noted for master: the pair transported this; it did not create it.
- Malformed `packer_home`/`packer_home_flavor` fails the whole manifest parse — inherited, open/parse-side,
  fail-closed, consistent with every other manifest field.
- **LOW cosmetic:** one leading space lost on `install_calls` in `tests/test_sessions.cpp` — the only byte in
  all seven files belonging to neither side's delta. No semantic effect, no `.clang-format` in the repo, tidy
  does not check indentation. Restore on any follow-up touch; it does not warrant a cycle.
- Standing routed items unchanged: **E-1/E-2/E-3 → slice E** (caveat surface + attribution), **R-a → residual**
  (duplicate-needle precedence). **The struck `staged_path_caveats` convener-error line stays struck** — my
  premise was false and it is not evidence.

## 5. What I am asking for
Master's condition-3 at the exact SHAs in §1, then the operator's PAIRED condition-4 (C first, B2 immediate).
`231437` stays WITHDRAWN. Nothing seals here; merge ≠ push ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — two lenses at `fd857f1`; independent reproduction of the ideal-3-way-merge equivalence, the 34-path union identity, merge-cleanliness into `origin/main` for both heads, ancestry, blast radius 1, `packer_home` retention in both union files, the `sessions.cpp` one-field delta and surviving `adapter_consent`, the probe-subsystem exclusion chain, and the control's arithmetic; plus verification that the R-4.8 residual row and its release gate already exist. This relay + its INDEX row ride one explicit-path docs-lane commit whose SHA lands after filing
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to this relay and `.relays/s4/INDEX.md`

CARRY LIST:
- `.relays/s4/s4-floor-impl/SITREP-PLANNER-CB2-PAIRED-HANDUP-RESTACKED-VERIFIED-20260811-022546.md` → `s4.orchestrator-planner` → master (condition-3) → operator (paired condition-4)
- PAIR: C `f03ce70` (PR #22) + B2 `fd857f1` (PR #23), both merge-tree exit 0 into `origin/main` `38a4702`; A10.3 BINDS; **blast radius 1** (was 27)
- re-check PASS ×2 lenses; reconciliation MECHANICALLY PROVEN (ideal 3-way merge equals the candidate except the five hand-resolved files; unions byte-identical to git's auto-merge; 34-path union identical); `sessions.cpp` is a ONE-FIELD delta and `adapter_consent` survived
- base control: plain `origin/main` reproduces the SAME five cases / eight assertions ⇒ Linux failures INHERITED + environmental; the head adds 116 passing cases and no failure
- non-gating: `packer_home` inert carrier (inherited; already gated at RESIDUALS R-4.8), one cosmetic indent byte, E-1/E-2/E-3 → slice E, R-a → residual; struck line stays struck; release hold ABSOLUTE
