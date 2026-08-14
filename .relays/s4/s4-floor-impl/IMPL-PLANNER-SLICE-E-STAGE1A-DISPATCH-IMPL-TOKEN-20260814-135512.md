## IMPL DISPATCH (slice E, STAGE 1a ONLY — J's sealed manifest schema) — the plan gate cleared at `134528`, and **the seven-element tuple is re-verified AT THIS ACT across all THREE pins.** Each target hashes to its lock; each live file carries exactly ONE later commit and that commit is its own lock/stamp; **three expected post-stamps, zero drift.** **This token authorizes STAGE 1a ONLY: three paths, J's sealed text, under m-1's byte-level veto.** **It ends at a STOP, not a continuation — 1a lands as its own commit and waits for m-1's verdict, and 1b-i needs a FRESH token from me.** **Nothing merges: the land order binds and the schema-2 stamp does not land ahead of M3-J-4..7.** Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ROLE: Planner
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: s4-floor-slice-e-stage1a-impl
PARENT_DISPATCH_ID: s4-floor-slice-e-plan-successor-r7d
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
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-REVIEW-IMPLEMENTER-SLICE-E-SUCCESSOR-R7D-APPROVE-COMPLETE-A36-MATRIX-20260814-134528.md
RELATED_CONTEXT: .relays/s4/s4-floor-impl/PLAN-PLANNER-SLICE-E-SUCCESSOR-R7D-SECOND-VALUE-AND-ALL-A36-LEGS-20260814-134034.md (the approved plan)
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: s4.orchestrator-planner, operator, s4.orchestrator-reviewer, master.orchestrator-planner
SUBJECT: IMPL DISPATCH — Stage 1a only (manifest.hpp/manifest.cpp/test_manifest.cpp), three-pin tuple re-verified at this act, stops for m-1's veto, nothing merges

## 1. The seven-element tuple, RE-VERIFIED AT THIS ACT — three pins

```text
TARGETS (each hashes to its declared lock)
  addendum-12    @ 6eeeb157   29a5b3a3abb6777a…   == DESIGN_LOCK_ID
  J              @ e30f845    94b6440c6ea5342a…   == CONSUMED_CONTRACT
  m3-addendum-3  @ a016f953   eeb4dd01cc907b5d…   == CONSUMER_DESIGN_LOCK_ID
LIVE (all three carry disclosed lock stamps and CANNOT hash to their locked values by construction)
  addendum-12    d0e2c6eb…      J   79d8dde5…      m3-addendum-3   cefd3f79…
NO LATER SUPERSESSION / NO LATER UNLOCKED NORMATIVE EDIT
  commits after the target, per document: 1, 1, 1 — and EACH of those three is that document's own
  lock or lock-stamp commit. Zero unlocked normative edits across all three.
APPROVALS  addendum-12 VP re-approval 191415 naming lock + full SHA + full commit; pre-lock content
           dispositions 181509 (m-2.implementer APPROVE) / 183734 (m-4 BOUNDED CONFIRM) / 184943
           (master link-1 discharge), each naming DESIGN_DOC_ID + the full target hash.
           J sealed + VP-approved at its pin. m3-addendum-3 LOCKED at a016f953.
ORDERING   every element precedes this successor plan (134034), its approve (134528) and this token.
TUPLE RESULT: COMPLETE. W-1 APPLICABLE.
```

**Re-measured at this act:** `origin/main` = `0db8fdd8424d27aad2c547614e9ebb95621a2794`; `git grep -c
parent_id origin/main -- src/core/manifest` → **0**; Stage-0 head `dca6b7d` reachable and unpublished.

## 2. Scope — Stage 1a only

SCOPE_DIFF:
- src/core/manifest/manifest.hpp -> in
- src/core/manifest/manifest.cpp -> in
- tests/test_manifest.cpp -> in
SCOPE_DIFF_RESULT: all-in

SCOPE_ROW_EVIDENCE:
- src/core/manifest/manifest.hpp — EXISTS at `0db8fdd`; `SessionChild` gains **exactly one** member, `std::optional<std::string> parent_id`. Named IN by the approved plan's manifest half; J's sealed text determines the member and its optionality.
- src/core/manifest/manifest.cpp — EXISTS at `0db8fdd`; `parse_session_children` gains J-R1's wire-shape validation (absent ⇒ parent IS the entry primary; present ⇒ equals another member's `original_id` and NEVER the primary, which is REFUSED), J-R5's present-`null` refusal, M4-CG-0..5 in full with the CG-4 node cap **short-circuiting DURING iteration**, and the other three caps; the children writer emits `parent_id` **only** when the parent is not the primary; `entry_schema` gains J-R3's conditional bump; and the reader's supported maximum moves to 2 with schemas above it staying on the disclosed-skip path. Named IN by the approved plan.
- tests/test_manifest.cpp — EXISTS at `0db8fdd`; carries the manifest-layer arms: the three schema tests (schema 2 accepted in full, 3 and 99 still skipped), the four cap at-cap/cap+1 arms with typed whole-entry refusal naming entry and cap, the explicit-primary and present-`null` refusals, and the absence-license round trip. Named IN by the approved plan.

**FORBIDDEN in Stage 1a — a byte in any of these is a scope breach: STOP and route.** `src/adapters/**`,
`src/core/pack/**`, `src/core/open/**` (m-3's, and hard-out until the operator assigns it), `src/cli/**`,
`harness/**`, `.github/**`, sealed docs, and every path not listed above. **`codex.cpp` is NOT in this stage,
so no anchor moves and no A3 ceremony fires.**

## 3. What to build — J's sealed text, and nothing adjacent to it

Implement against **J's sealed bytes at `e30f845`**, not against its reasoning and not against my summary.
The determining clauses are J-R1 (wire shape + explicit-primary refusal), J-R5 (present-`null` refused),
J-R3 (the conditional bump), M4-CG-6 (validation order; **iterative with a visited set** — a count cap alone
still stack-overflows a recursive walk on a degenerate chain), and M4-CG-4 (the four caps).

**RED-first.** Author and RUN each manifest-layer arm, observe it failing, record the receipt, then fix.
**A compile failure is NOT a credited behavioral RED** — if an arm cannot compile at `0db8fdd`, report it.

**THE THREE STOPS — halt and route to me, do NOT decide:**
1. **MULTI-CAP BREACH.** J requires the error to name *"the cap"* — singular — and m-1 has NOT stated which
   is named when two are breached at once.
2. **J-R6 / J-R7 originate on m-3's surface.** Implement what is written; **never re-derive them from J's
   reasoning.**
3. **THE CAP-CARRIER SEAM (`§A12.4.2`).** J's fatal must be consistent with **the ruling**, never with an
   inferred carrier. **A warning appended where the failure path discards it is DEAD CODE THAT READS AS
   COMPLIANCE IN A DIFF.**

**THE FIVE VETOES — m-1 will veto on:** a post-loop cap check instead of the **short-circuit during
iteration** refusing at the 1025th element **before constructing or retaining it**; **truncation** anywhere,
in any arm, for any cap; a writer that **emits `parent_id` when the parent IS the entry's primary**
(ADDENDUM-11's exact defect: a producer emitting what its own parser refuses); a cap error failing to name
**BOTH the cap AND the offending entry**; and **any silent filling of the three STOPs.**

**Two facts to save you rediscovering them:** the old-reader skip J-R3 relies on **already exists** at
`manifest.cpp:225-226` — we move the supported maximum, we do not build the skip; and
`parse_session_children(object, agent)` **does not receive the entry's primary id** that J's refusal rule
needs, so **NAME the signature/call-site change in your report** rather than letting it read as an
improvisation.

DISPATCH IMPL

## 4. Where this token ENDS

**Stage 1a lands as its OWN EXACT COMMIT and STOPS.** Report the SHA and **wait for m-1's byte-level
approval or veto.** **No Stage-1b byte follows on this token** — 1b-i requires m-1's approval **and a fresh
dispatch from me.** This token authorizes no adapter, pack, CLI, open, harness or `.github` edit, no branch
publication, no PR, no GitHub Actions, no merge, no seal, no deployment and no release.

**And nothing merges regardless:** the land order binds — **no head that can produce a schema-2 image lands
ahead of M3-J-4..7 being in force at a named receipt SHA**, and the narrower reading that 1a alone might
merge early **stays refused** pending the orchestrator's answer. Build on the Stage-0 head `dca6b7d`
(itself cut from `origin/main` = `0db8fdd`), keep it unpublished, and run macOS locally; the local Ubuntu
24.04 `linux/amd64` Docker suite governs Linux if you run it. **Actions are NOT invoked.** Never read or
mutate the live `~/.claude` / `~/.codex`; no credential collection. Merge ≠ push ≠ release; the release hold
is ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — at this act: re-hashed all three targets (`6eeeb157`→`29a5b3a3`, `e30f845`→`94b6440c`, `a016f953`→`eeb4dd01`) and all three live files (`d0e2c6eb`, `79d8dde5`, `cefd3f79`), counted the later commits per document (1/1/1, each being that document's own lock or lock-stamp), and re-measured `origin/main` with the `parent_id` hit count and the reachability of `dca6b7d`; plus `git cat-file -e` on each Stage-1a path for the SCOPE_ROW_EVIDENCE. This relay + its INDEX row ride ONE explicit-path docs-lane commit filed under a single unbroken `&&` chain
RELAY_LINT: per D-3.4 — per-file WITH freshness, INDEX tail re-read, append, `--index`, add and commit in ONE `&&` chain with no semicolon. Disclosed reds: INDEX line 222 (inherited) and the `013935`/`014004` tail inversion from the first sweep; two relays remain deliberately unindexed and are named in the `130923` row
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to this relay and `.relays/s4/INDEX.md`

CARRY LIST:
- `.relays/s4/s4-floor-impl/IMPL-PLANNER-SLICE-E-STAGE1A-DISPATCH-IMPL-TOKEN-20260814-135512.md` → `s4-floor.implementer`
- **SEVEN-ELEMENT TUPLE RE-VERIFIED AT THIS ACT ACROSS THREE PINS:** each target hashes to its lock (`29a5b3a3`/`94b6440c`/`eeb4dd01`); each live file carries **exactly ONE later commit and that commit is its own lock or lock-stamp** — three expected post-stamps, **zero unlocked normative edits**; approvals and pre-lock dispositions all precede the plan, its approve and this token. **W-1 APPLICABLE**
- **STAGE 1a ONLY** — `manifest.hpp` (one optional member), `manifest.cpp` (parser validation + four caps + absence-licensed writer + the bump + supported max → 2), `tests/test_manifest.cpp`; `SCOPE_DIFF_RESULT: all-in` with per-row evidence. **`src/adapters/**`, `src/core/pack/**`, `src/core/open/**`, `src/cli/**`, `harness/**`, `.github/**` all FORBIDDEN** — `codex.cpp` is not in this stage so **no anchor moves and no A3 fires**
- build against **J's SEALED BYTES at `e30f845`**, RED-first with observed failures; **a compile failure earns no behavioral-RED credit.** THREE STOPS (multi-cap breach; J-R6/J-R7 are m-3's and never re-derived; the cap-carrier seam with the dead-line trap) and FIVE VETOES (post-loop cap check; truncation; emitting `parent_id` = primary; a cap error missing cap or entry; silent STOP-filling) carried
- **two facts pre-supplied:** the old-reader skip ALREADY EXISTS at `manifest.cpp:225-226` (move the maximum, do not build the skip), and `parse_session_children(object, agent)` lacks the PRIMARY id J's refusal needs — **NAME that signature/call-site change in the report**
- **THIS TOKEN ENDS AT A STOP:** 1a lands as its own commit, reports its SHA and **waits for m-1's verdict**; **1b-i needs m-1's approval AND a fresh token from me.** No publication, PR, Actions, merge, seal or release
- **nothing merges regardless** — the land order binds and the 1a-merges-early narrowing stays REFUSED; build on `dca6b7d`, unpublished; Actions NOT invoked; live stores never touched; release hold ABSOLUTE
