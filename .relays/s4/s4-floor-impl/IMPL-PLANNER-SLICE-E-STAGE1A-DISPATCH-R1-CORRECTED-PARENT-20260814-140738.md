## IMPL DISPATCH R1 (slice E, STAGE 1a) — **corrected canonical parent, and the blocker is right at the bytes: `135512` carried `PARENT_DISPATCH_ID: s4-floor-slice-e-plan-successor-r7d` — the PLAN — when the approving PLAN-REVIEW `s4-floor-slice-e-plan-review-successor-r7d` is the edge that makes a delegated grant live at all.** I pointed the token at the thing that was reviewed instead of at the review, and **`IN_REPLY_TO` naming the review does not repair it — that field is threading, not a gate input.** **The `135512` token is WITHDRAWN and INERT; this relay carries the only live one.** Scope, the three-pin tuple, the STOP, the STOPs/VETOES and every prohibition are byte-identical to `135512` — **nothing about the work changed, only the edge that authorizes it.**

ROLE: Planner
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: s4-floor-slice-e-stage1a-impl-r1
PARENT_DISPATCH_ID: s4-floor-slice-e-plan-review-successor-r7d
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — m-1 holds byte-level review and VETO on this result, and 1a STOPS for that verdict. The operator's consumer-scope assignment stays open and does not gate 1a. Merge, seal, publication and release each retain their own gate. The release hold is ABSOLUTE.
DESIGN_DOC_ID: m2-addendum-12-transitive-collect-mono-gate-20260812
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m2-addendum12-29a5b3a3-lock-20260812
TARGET_DESIGN_SHA256: 29a5b3a3abb6777af70a1c959728f4f61731489a1735773e81713b5aa3ea3adb
TARGET_DESIGN_COMMIT: 6eeeb157be249792d61774016485d97c303e2c8f
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812
CONSUMER_DESIGN_LOCK_ID: m3-addendum-3-eeb4dd01-lock-20260814
CONSUMER_TARGET_DESIGN_SHA256: eeb4dd01cc907b5dc793a7a27892395a8af258f4967a38fd744f2b424013c7aa
CONSUMER_TARGET_DESIGN_COMMIT: a016f9532d6a4abff2d4e642062f8127efa0eae8
CONSUMER_POST_STAMP_SHA256: cefd3f799b571bea511b362583c97e1a856dbf07b97a4a948882d74705a6db67
PLAN_LOCK_ID: s4-floor-slice-e-plan-20260812
IN_REPLY_TO: .relays/s4/s4-floor-impl/SITREP-IMPLEMENTER-SLICE-E-STAGE1A-DISPATCH-LINEAGE-BLOCKER-20260814-140210.md
RELATED_CONTEXT: .relays/s4/s4-floor-impl/IMPL-PLANNER-SLICE-E-STAGE1A-DISPATCH-IMPL-TOKEN-20260814-135512.md (WITHDRAWN — its token is INERT and must not be acted on); .relays/s4/s4-floor-impl/PLAN-REVIEW-IMPLEMENTER-SLICE-E-SUCCESSOR-R7D-APPROVE-COMPLETE-A36-MATRIX-20260814-134528.md (the approving review, now the canonical parent)
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: s4.orchestrator-planner, operator, s4.orchestrator-reviewer, master.orchestrator-planner
SUBJECT: IMPL DISPATCH R1 — canonical parent corrected to the approving PLAN-REVIEW; 135512 withdrawn; scope, tuple, STOP and prohibitions unchanged

## 1. The defect, verified at the bytes before correcting it

```text
135512 (WITHDRAWN)   DISPATCH_ID: s4-floor-slice-e-stage1a-impl
                     PARENT_DISPATCH_ID: s4-floor-slice-e-plan-successor-r7d      <- the PLAN
approving review     DISPATCH_ID: s4-floor-slice-e-plan-review-successor-r7d
                     PARENT_DISPATCH_ID: s4-floor-slice-e-plan-successor-r7d
                     PLAN_REVIEW_VERDICT: approve
approved plan        DISPATCH_ID: s4-floor-slice-e-plan-successor-r7d
REQUIRED CHAIN       IMPL -> approving PLAN-REVIEW -> pair-Planner PLAN
THIS RELAY           PARENT_DISPATCH_ID: s4-floor-slice-e-plan-review-successor-r7d   CORRECT
```

**Why this is a real gate and not bookkeeping.** A pair Planner's implementation grant is **inert without
its approving PLAN-REVIEW parent** — that edge is the whole evidence that a second seat looked at the plan
before authority issued. Pointing at the PLAN says "I wrote a plan and then authorized myself"; pointing at
the REVIEW says "a reviewer approved it and the grant hangs from that approval." **I skipped the seat whose
sign-off the token exists to inherit.**

**And the near-miss worth naming:** the exact-file lint passed on `135512`. **The shape was clean and the
lineage was wrong**, which is exactly the class this lane keeps paying for — an instrument that cannot see
the thing you needed checked. Your manual header-chain walk found it; no automated arm I ran would have.

## 2. Withdrawal, stated so no ambiguity survives

**The bare token in `135512` is WITHDRAWN and INERT.** It authorizes nothing, and no act may cite it.
**This relay carries the only live implementation token for Stage 1a.** `135512` is not rewritten and stays
in the record as filed, per the lane's append-only discipline.

## 3. Everything below is byte-identical in substance to `135512` — the tuple, the scope, the stop

**Seven-element tuple, as re-verified at the `135512` act and unchanged since** (all three targets hash to
their locks — `29a5b3a3` @ `6eeeb157`, `94b6440c` @ `e30f845`, `eeb4dd01` @ `a016f953`; each live file
carries exactly ONE later commit and each of those is that document's own lock or lock-stamp, so three
expected post-stamps and zero unlocked normative edits; approvals and pre-lock dispositions all precede the
plan, its approve and this token). `origin/main` = `0db8fdd`, `parent_id` under `src/core/manifest` = 0,
Stage-0 head `dca6b7d` reachable and unpublished. **W-1 APPLICABLE.**

SCOPE_DIFF:
- src/core/manifest/manifest.hpp -> in
- src/core/manifest/manifest.cpp -> in
- tests/test_manifest.cpp -> in
SCOPE_DIFF_RESULT: all-in

SCOPE_ROW_EVIDENCE:
- src/core/manifest/manifest.hpp — EXISTS at `0db8fdd`; `SessionChild` gains **exactly one** member, `std::optional<std::string> parent_id`, determined by J's sealed text. Named IN by the approved plan's manifest half.
- src/core/manifest/manifest.cpp — EXISTS at `0db8fdd`; `parse_session_children` gains J-R1's wire-shape validation (absent ⇒ the parent IS the entry primary; present ⇒ equals another member's `original_id` and NEVER the primary, REFUSED), J-R5's present-`null` refusal, M4-CG-0..5 in full with the CG-4 node cap **short-circuiting DURING iteration**, and the other three caps; the children writer emits `parent_id` **only** when the parent is not the primary; `entry_schema` gains J-R3's conditional bump; the reader's supported maximum moves to 2 with schemas above it staying on the disclosed-skip path. Named IN by the approved plan.
- tests/test_manifest.cpp — EXISTS at `0db8fdd`; carries the manifest-layer arms: the three schema tests (2 accepted in full, 3 and 99 still skipped), the four cap at-cap/cap+1 arms with typed whole-entry refusal naming entry AND cap, the explicit-primary and present-`null` refusals, and the absence-license round trip. Named IN by the approved plan.

**FORBIDDEN — a byte in any of these is a scope breach: STOP and route.** `src/adapters/**`,
`src/core/pack/**`, `src/core/open/**` (m-3's, hard-out until the operator assigns it), `src/cli/**`,
`harness/**`, `.github/**`, sealed docs, and every path not listed. **`codex.cpp` is NOT in this stage, so no
anchor moves and no A3 ceremony fires.**

**Build against J's SEALED BYTES at `e30f845`** — not its reasoning, not my summary. Determining clauses:
J-R1, J-R5, J-R3, M4-CG-6's validation order (**iterative with a visited set**; a count cap alone still
stack-overflows a recursive walk on a degenerate chain), M4-CG-4's four caps. **RED-first**, each arm RUN and
observed failing with its receipt recorded; **a compile failure is NOT a credited behavioral RED** — report
it instead.

**THE THREE STOPS — halt and route to me, do NOT decide:** (1) a **MULTI-CAP BREACH**, since J requires the
error to name *"the cap"* — singular — and m-1 has not stated which is named when two are breached;
(2) **J-R6 / J-R7 originate on m-3's surface** — implement what is written and **never re-derive them from
J's reasoning**; (3) **the cap-carrier seam (`§A12.4.2`)** — J's fatal must be consistent with **the ruling**,
never an inferred carrier, and **a warning appended where the failure path discards it is DEAD CODE THAT
READS AS COMPLIANCE IN A DIFF.**

**THE FIVE VETOES:** a post-loop cap check instead of the **short-circuit during iteration** refusing at the
1025th element **before constructing or retaining it**; **truncation** anywhere, any arm, any cap; a writer
that **emits `parent_id` when the parent IS the primary** (ADDENDUM-11's exact defect — a producer emitting
what its own parser refuses); a cap error failing to name **BOTH the cap AND the offending entry**; and
**any silent filling of the three STOPs.**

**Two facts pre-supplied:** the old-reader skip J-R3 relies on **already exists** at `manifest.cpp:225-226`
— move the supported maximum, do not build the skip; and `parse_session_children(object, agent)` **does not
receive the entry's primary id** that J's refusal rule needs, so **NAME that signature/call-site change in
your report.**

DISPATCH IMPL

## 4. Where this token ENDS

**Stage 1a lands as its OWN EXACT COMMIT and STOPS.** Report the SHA and **wait for m-1's byte-level
approval or veto.** **No Stage-1b byte follows on this token** — 1b-i requires m-1's approval **and a fresh
dispatch from me.** No adapter, pack, CLI, open, harness or `.github` edit; no branch publication, no PR, no
GitHub Actions, no merge, no seal, no deployment, no release.

**Nothing merges regardless:** the land order binds — **no head that can produce a schema-2 image lands
ahead of M3-J-4..7 being in force at a named receipt SHA** — and the narrower 1a-merges-early reading
**stays refused** pending the orchestrator's answer. Build on `dca6b7d` (cut from `origin/main` = `0db8fdd`),
keep it unpublished; macOS locally, with the local Ubuntu 24.04 `linux/amd64` Docker suite governing Linux
if run; **Actions NOT invoked**; **never read or mutate the live `~/.claude` / `~/.codex`**; no credential
collection. Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — compared the `135512` header against the approving review's `DISPATCH_ID` and the approved plan's, confirming the skipped edge; the three-pin tuple and scope-row evidence were measured at the `135512` act and are carried unchanged, with `origin/main`, the `parent_id` count and `dca6b7d`'s reachability re-confirmed there. This relay + its INDEX row ride ONE explicit-path docs-lane commit filed under a single unbroken `&&` chain
RELAY_LINT: per D-3.4 — per-file WITH freshness, INDEX tail re-read, append, `--index`, add and commit in ONE `&&` chain with no semicolon. **Note for the record: exact-file lint passed on the DEFECTIVE `135512` — the shape was clean and the lineage was wrong, so the header-chain walk is the arm that matters here and no automated arm I ran would have caught it.** Disclosed reds: INDEX line 222 (inherited) and the `013935`/`014004` tail inversion; two relays remain deliberately unindexed and are named in the `130923` row
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to this relay and `.relays/s4/INDEX.md`

CARRY LIST:
- `.relays/s4/s4-floor-impl/IMPL-PLANNER-SLICE-E-STAGE1A-DISPATCH-R1-CORRECTED-PARENT-20260814-140738.md` → `s4-floor.implementer`
- **THE BLOCKER IS RIGHT AT THE BYTES:** `135512` carried `PARENT_DISPATCH_ID: s4-floor-slice-e-plan-successor-r7d` (the PLAN) when the approving review `s4-floor-slice-e-plan-review-successor-r7d` is the edge that makes a delegated grant live. **`IN_REPLY_TO` naming the review does NOT repair it — that field is threading, not a gate input**
- **why it is a real gate:** a pair Planner's grant is INERT without its approving PLAN-REVIEW parent, because that edge is the evidence a second seat looked before authority issued. Pointing at the PLAN says "I wrote a plan and then authorized myself"; **I skipped the seat whose sign-off the token exists to inherit**
- **near-miss named: exact-file lint PASSED on `135512` — clean shape, wrong lineage.** The manual header-chain walk found it and no automated arm I ran would have
- **`135512`'s token is WITHDRAWN and INERT — it authorizes nothing and no act may cite it.** This relay carries the ONLY live Stage-1a token. `135512` is not rewritten and stays in the record as filed
- scope, three-pin tuple, `SCOPE_DIFF_RESULT: all-in` with per-row evidence, the three STOPs, the five VETOES, the two pre-supplied facts, the RED-first rule and every prohibition are **carried unchanged** — nothing about the work moved, only the edge that authorizes it
- **the token ENDS AT A STOP:** 1a lands as its own commit, reports its SHA, waits for m-1's verdict; **1b-i needs m-1's approval AND a fresh token from me**; nothing merges regardless, the land order binds and the early-merge narrowing stays REFUSED; release hold ABSOLUTE
