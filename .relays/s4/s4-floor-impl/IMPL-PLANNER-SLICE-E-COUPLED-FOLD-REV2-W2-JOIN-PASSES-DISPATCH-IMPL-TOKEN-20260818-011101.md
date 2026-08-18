## IMPL — the W-2 token-time join PASSES on every element, and the coupled fold + R-3.40(13) fix is DISPATCHED

ROLE: Planner
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: s4-floor-slice-e-coupled-fold-impl-rev2
PARENT_DISPATCH_ID: s4-floor-slice-e-coupled-fold-plan-review-rev2
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-REVIEW-IMPLEMENTER-SLICE-E-COUPLED-FOLD-REV2-APPROVE-W2-L-ONLY-20260818-000126.md
RELATED_CONTEXT: .relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-SLICE-E-W2-ROW-CORRECTED-REFUSAL-AFFIRMED-REV2-PATH-CLEAR-NON-RETROACTIVITY-DOWN-20260818-004111.md
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — the successor returns for m-1's byte review and veto AND m-3's COMBINED successor re-review, and the R-3.40(13) fix carries m-3's and m-2's named objection path to master. None of those is discharged here. Merge, push, publication, deployment and release retain separate gates. The land order binds. The release hold is ABSOLUTE.
DESIGN_DOC_ID: m1-addendum-L-20260816
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m1-addendum-L-10c8e8e6-lock-20260817
TARGET_DESIGN_SHA256: 10c8e8e6ed1560d8fc03e9342ed539a1554fdc0a978ba864ce6427226e0daba4
TARGET_DESIGN_COMMIT: 8c7f9281d538704419ea7142a417495eec46e8a5
SECOND_DESIGN_LOCK: m1-addendum-K-5da667fa-lock-20260816, m3-addendum-5-b8686c75-lock-20260816, m3-addendum-4-9049de44-lock-20260816
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812, m3-addendum-3-eeb4dd01-lock-20260814
CONSUMER_DESIGN_LOCK_ID: m3-addendum-3-eeb4dd01-lock-20260814
PLAN_LOCK_ID: s4-floor-slice-e-plan-20260812
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer, m-1.planner, m-1.implementer, m-3.planner, m-3.implementer, m-2.planner
SUBJECT: IMPL — W-2 join run at the registry and locked bytes and PASSING on all eleven elements; coupled fold + the bounded R-3.40(13) fix dispatched on the rev2 approve; nine IN paths all-in; fix commit FIRST, both platforms observed on the final head

DISPATCH IMPL

## 1. The W-2 token-time join — run at my seat, at the registry and locked bytes, never from a summary

**Listed identity: ONE.** `m1-addendum-L-20260816 -> m1-addendum-L-10c8e8e6-lock-20260817` (rev2 §1).

### 1.1 The selector — all five must hold

```text
REPO             ../bivpak                                                              PASS
RELAY_ROOT       .relays/s4/s4-floor-impl                                               PASS
PLAN_LOCK_ID     s4-floor-slice-e-plan-20260812                                         PASS
DESIGN_BINDINGS  rev2's literal list — ONE item, the L pair above. rev2 (`235116`)
                 PASSED my Implementer's local plan-review at `000126`
                 (`PLAN_REVIEW_VERDICT: approve`, FROM s4-floor.implementer, TO me,
                 PARENT s4-floor-slice-e-coupled-fold-plan-rev2, sha256
                 3b4cc8b7d4a2d03817ef5b2a14f1d287ffc0f4a373de499a762375a6e26715e5 —
                 re-derived by me and EQUAL to their declared value), so rev2 IS the
                 latest revision under this PLAN_LOCK_ID to pass local plan-review and
                 its list IS the current coverage                                       PASS
ERROR_CLASS      the cross-repo foreign-lock / no-earlier-same-owner-DESIGN lineage red,
                 measured firing on rev2 and naming this lock alone                      PASS
```

### 1.2 The join, per listed identity — every element, measured

```text
1  OWNER PLANNER'S LOCK DECLARATION — the complete three-field tuple
   pdc master/relays/s4-build-standup/DESIGN-PLANNER-M1-ADDENDUM-L-NEW-LOCK-DECLARED-REV7-
     FENCES-RESTAMPED-AT-PIN-20260817-184619.md · FROM m-1.planner (the owning Planner)
     DESIGN_LOCK_ID        m1-addendum-L-10c8e8e6-lock-20260817
     LOCKED_DESIGN_SHA256  10c8e8e6ed1560d8fc03e9342ed539a1554fdc0a978ba864ce6427226e0daba4
     LOCKED_DESIGN_COMMIT  8c7f9281d538704419ea7142a417495eec46e8a5
     post-stamp declared   b3599511d8802adc12b2f4dda131374f03d33bc33dfad78e22e826b435fde1e1   PASS

2  VP'S EXACT-PIN APPROVAL — the same three-field identity
   .../DESIGN-REVIEW-ORCHESTRATOR-REVIEWER-L-REV7-APPROVE-M4-REACH-DEFERRAL-BOUNDED-20260817-154000.md
     FROM master.orchestrator-reviewer · DESIGN_REVIEW_VERDICT approve
     DESIGN_DOC_ID         m1-addendum-L-20260816
     TARGET_DESIGN_SHA256  10c8e8e6ed…   EQUAL   TARGET_DESIGN_COMMIT 8c7f9281d5…   EQUAL   PASS
     (it names NO DESIGN_LOCK_ID — CORRECT and expected: a PRE-LOCK approval cannot name a
      later lock, the identical role W-2 assigns `053722` in the K join provenance)

3  THE DESIGN'S OWN GATE DISPOSITIONS, as its lock records them
   the stamp records: implementer APPROVE `144843` · VP APPROVE `154000` · CTO carry `154351`
   .../DESIGN-REVIEW-IMPLEMENTER-M1-ADDENDUM-L-REV7-APPROVE-LEG-Q-LOCUS-EXACT-20260817-144843.md
     FROM m-1.implementer · DESIGN_REVIEW_VERDICT approve · same SHA-256 and commit          PASS
   `154351` present as the CTO carry; `154000` is element 2                                  PASS

4  EVERY ARTIFACT PRECEDES THE CONSUMING TOKEN
   144843 < 154000 < 154351 < 184619 (08-17) < rev2 235116 (08-17) < rev2 approve 000126
   (08-18) < this token                                                                      PASS

5  NO LATER SUPERSESSION
   exactly ONE live L lock. master/ARCHITECTURE.md's L row is RE-PINNED to
   `m1-addendum-L-10c8e8e6-lock-20260817` @ 8c7f9281 / 10c8e8e6…, and names 61d3e443 ONLY in
   its SUPERSEDES clause and dead-pin list. (My first grep surfaced 61d3e443 from that
   supersession text and I read the row before treating it as a finding — it is not one.)     PASS

6  NO LATER UNLOCKED NORMATIVE EDIT — re-verified AT TOKEN TIME, not carried
   live file hashes b3599511… — EQUAL to the declared post-stamp
   diff locked(8c7f9281) -> live = ONE hunk, `14,18c14,47`, entirely inside the Status block
   last commit touching the doc = 437520e, the lock declaration itself                       PASS
```

**Eleven elements, zero mismatches. The join holds, W-2's coverage attaches to the listed identity, and
the token issues.** Had any element mismatched, none would have.

## 2. Delegation preconditions

```text
1 DELEGATION GRANTED   190217 §3 and re-confirmed at 004111 ("Proceed on your own gates; nothing waits
                       on master or me"); the extension rule needed no new grant at any level
2 PLAN-REVIEW APPROVE  000126 on rev2, addressed to me, parented to rev2, on the exact filed bytes
3 SCOPE_DIFF           all-in, nine rows — §3
4 NO HARD TRIGGER      no new operator gate; the two owner-surface acts (M-a's four count lines, the
                       ONE ruled transcription) and the bounded R-3.40(13) grant are all pre-granted
```

## 3. Scope — rev2's nine rows

SCOPE_DIFF:
- src/core/manifest/manifest.hpp -> in
- src/core/manifest/manifest.cpp -> in
- src/core/open/open.cpp -> in
- tests/test_manifest.cpp -> in
- tests/test_cli.cpp -> in
- tests/test_sessions.cpp -> in
- tests/fixtures/slice-e/** -> in
- .github/workflows/s2-harness.yml -> in
- tests/test_probe.cpp -> in
SCOPE_DIFF_RESULT: all-in

SCOPE_ROW_EVIDENCE:
- unchanged from rev2 §3 and the `193748` token's per-row evidence; no path added, none removed. `tests/test_probe.cpp` is fenced to the SINGLE case at `:260-278` (its helper at `:57-65` and/or its expected outcome) under the `221915` grant. `.github/workflows/s2-harness.yml` is fenced to `:73-76`'s one transcribed line and the four count cells `:68`/`:71`/`:268`/`:271`.

**OUT — a discovered need is a STOP to me, never a licence:** `src/core/support/probe.cpp` and every other `test_probe.cpp` case; `src/core/open/sessions.cpp`, `render.cpp`, `report/envelope.cpp` (S-9, zero diff); `src/cli/main.cpp` and the `list`/`info` verbs (R-6.2 / Step 6); `src/core/pack/**` and `serialize`; `:269`/`:270`; every other `.github` byte; sealed design bytes; the harness.

## 4. What implements — rev2 governs; this relay is not the spec

**Implement to the LOCKED L bytes (`10c8e8e6…` @ `8c7f9281`) and to rev2, not to this paraphrase.**
S-1…S-15 (rev0, approved `192103`) · S-16 and its one-case fence (rev1, approved `233228`) · rev2 §1's
binding list. The four adopted binds from `192103` (S-12a off-by-default payload control, S-3a's three
equality-asserted duplicate details, S-7a's separate allow-only set, S-Ea's in-test 1,025-child fixture)
and the three placements I ruled (S-1 the new opaque field, S-7 allow-only at `:280`, S-8 the
identity-free cap detail) all stand.

```text
ORDERING     1  the FIX commit — S-16 only, message NAMES "R-3.40 item (13)"
             2  the FOLD commit — S-1..S-15, the seven held paths
             fix-first leaves NO red interval at any intermediate head
SHAPE        measure the invalid-ELF fixture in-container FIRST — your `7f 45 4c 46 02 01 01 00 …`
             candidate, regular file, mode 0700. Linux `spawn_error` => keep it, no platform
             conditional. Linux `nonzero_exit` => report it, then shape (a). ANY THIRD OUTCOME => STOP.
STRUCTURAL   the replacement fixture stays a REGULAR FILE WITH EXEC BITS, or it returns at
             probe.cpp:655 and never reaches the spawn — G8, with A12 as the detector
EVIDENCE     BOTH platforms re-observed on the FINAL head; the earlier macOS 6/6 PREDATES the fix and
             DOES NOT transcribe; four counts from GREEN runs of that head, run ids cited, no
             arithmetic, no cross-target borrowing; the four named fold mutants STAND — do NOT re-run
TRANSCRIBE   m-3's line RE-READ at transcription time from 224751; the pin
             9e3639f07d46437095d1478328d5dfd6871aeb87a6b207243a991c1624d39481 is how you CHECK what
             you landed, never what you type. Any deviation is an m-3 VETO.
```

## 5. The fences carried

**L's six vetoes and three STOPs** (graph reads · count feeds · post-loop cap check · truncation ·
un-cut stub annotation · silent STOP-filling; reads beyond `{agent, entry_schema, footprint}` → m-1,
listing annotation → m-3, count machinery from the footprint → m-3). **All three route through me, then
UP through the orchestrator — never sideways to an m-x seat.** **K's one-identifier rule, A5's
biconditional and at-least floor, A3.1's notice, and m-3's V1–V11 continue to bind.** **Leg (h) is NOT
written; the vacuous listing halves of (m)/(o) and L-R2(0) are NOT asserted; no stub-class annotation
text anywhere (L-V5, unconditional).**

**Standing operator constraints, unchanged:** live `~/.claude` / `~/.codex` are never read-for-mutation
or written — fixture trees or explicit disposable copies only; **no credential collection**; GitHub
Actions NOT invoked; branch stays **LOCAL and UNPUBLISHED** — no push, no PR, no merge, no seal, no
publication.

**The token ends at a STOP covering the fix commit and the coupled fold only.** Return for my byte
verification, then m-1's byte veto and m-3's combined successor re-review — both gate the hand-up, and
the fix additionally carries m-3's and m-2's named objection path to master. **Any gap rev0–rev2 does
not decide is a STOP to me**, never a keyboard call (L-R7).

Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product, test, fixture, workflow, branch, Docker, push, PR, Actions, merge, publication, deployment, or release act at this seat — this relay delegates. Read-only this pass: the `000126` rev2 approve read in full and re-hashed (`3b4cc8b7…`, EQUAL to its declared value); the W-2 join run at the bytes — `184619` (owner lock declaration, three-field tuple + post-stamp), `154000` (VP exact-pin approval, verdict + SHA + commit + doc id), `144843` (m-1.implementer gate disposition), `154351` (CTO carry) all opened and their identity fields read; `pdc master/ARCHITECTURE.md`'s L row read in full for supersession; the live L doc re-hashed (`b3599511…`) and re-diffed against `8c7f9281` at token time (one Status-block hunk, `14,18c14,47`); `git log -1` on the L doc (`437520e`); and, in the prior pass, `pdc 47b70f8`'s W-2 row edit verified committed and ancestor-reachable with the `:3249-3252` pointer independently validated against the live linter sha `eef1d2be8294b67e5478c37f9c0bbae99a3c980bbcded4c2cc6c5f5aca87dfa3`. This relay + its INDEX row ride ONE explicit-path docs-lane commit whose SHA lands after filing.
RELAY_LINT: per D-3.4 + D-3.4(a) — clock read immediately before filing (D-5.10), per-file WITH freshness and the exit status checked un-piped and READ before committing; `--relay-root` run against this file and its output READ IN FULL, not grepped past. Standing reds disclosed: the cross-repo DESIGN-lineage class, of which this thread's plan revisions are members — that red is the very one rev2 §1 brings under W-2 and the §1.2 join is the evidence entitling it, disclosed rather than claimed absent; INDEX cell-count (R-4.27) at 132, 222, 324, 362, 384, 388, 408, 435; INDEX time inversions at 222 and 393. `.relays/s4/INDEX.md` tail re-read before appending; `--index`; add and commit path-scoped; my appended row is 10-cell clean.
FINAL_GIT_STATUS_SHORT: literal path-scoped `git status --short` for this seat's two writes, captured at staging (the implementation worktree `s4-floor-slice-e-stage1a` at `9729191` carries the seven authorized unstaged fold paths, held and about to be committed under this token; the shared main checkout carries sibling-authored untracked state, excluded and unclaimed):
  M  .relays/s4/INDEX.md
  A  .relays/s4/s4-floor-impl/IMPL-PLANNER-SLICE-E-COUPLED-FOLD-REV2-W2-JOIN-PASSES-DISPATCH-IMPL-TOKEN-20260818-011101.md

CARRY LIST (D-8.5):
- `.relays/s4/s4-floor-impl/IMPL-PLANNER-SLICE-E-COUPLED-FOLD-REV2-W2-JOIN-PASSES-DISPATCH-IMPL-TOKEN-20260818-011101.md` → `s4-floor.implementer` — LIVE bare implementation token, parented to the `000126` rev2 plan-review approve
- THE W-2 TOKEN-TIME JOIN PASSES ON ALL ELEVEN ELEMENTS, run at the registry and locked bytes and never from a summary. SELECTOR: REPO ../bivpak, RELAY_ROOT .relays/s4/s4-floor-impl, PLAN_LOCK_ID s4-floor-slice-e-plan-20260812, DESIGN_BINDINGS rev2's one-item literal list with rev2 having passed local plan-review at 000126 so it IS the current approved revision and its list IS the coverage, ERROR_CLASS the cross-repo foreign-lock lineage red measured firing on rev2 and naming this lock alone. JOIN: (1) owner Planner lock declaration 184619 FROM m-1.planner carrying the complete tuple m1-addendum-L-10c8e8e6-lock-20260817 / 10c8e8e6ed1560d8fc03e9342ed539a1554fdc0a978ba864ce6427226e0daba4 / 8c7f9281d538704419ea7142a417495eec46e8a5 plus post-stamp b3599511; (2) VP exact-pin approval 154000 FROM master.orchestrator-reviewer, approve, same SHA and commit and doc id, naming NO lock id which is CORRECT for a pre-lock review and the identical role W-2 assigns 053722 in the K join; (3) gate dispositions as the lock records them — implementer approve 144843 at the same pin, VP 154000, CTO carry 154351; (4) every artifact precedes this token by chronology 144843 < 154000 < 154351 < 184619 < 235116 < 000126 < now; (5) no later supersession, exactly one live L lock with ARCHITECTURE.md's row RE-PINNED to 10c8e8e6 and naming 61d3e443 only as superseded and dead — my first grep surfaced the dead pin from that supersession text and I read the row before treating it as a finding, which it is not; (6) no later unlocked normative edit, re-verified AT TOKEN TIME with the live file hashing b3599511 equal to the declared post-stamp, the locked-to-live diff ONE hunk 14,18c14,47 entirely inside the Status block, and the last commit touching the doc being 437520e the lock declaration itself. Zero mismatches; had any element mismatched, no token would have issued
- DELEGATION PRECONDITIONS: delegation granted at 190217 and re-confirmed at 004111; the 000126 approve addressed to me, parented to rev2, on the exact filed bytes with its declared sha 3b4cc8b7 re-derived by me and EQUAL; SCOPE_DIFF all-in over nine rows; no hard trigger
- IMPLEMENT TO THE LOCKED L BYTES AND TO rev2, NOT to this relay: S-1 through S-15 from rev0 approved 192103, S-16 and its one-case fence from rev1 approved 233228, rev2's binding list; the four adopted binds S-12a, S-3a, S-7a and S-Ea stand, as do the three ruled placements S-1, S-7 and S-8
- ORDERING fix commit FIRST naming R-3.40 item (13), then the fold commit, so no red interval exists at any intermediate head. SHAPE measured in-container first with the invalid-ELF candidate as a regular file at mode 0700: Linux spawn_error keeps it with no platform conditional, Linux nonzero_exit is reported and then shape (a) is used, ANY THIRD OUTCOME is a STOP. STRUCTURAL the fixture stays a regular file with exec bits or it returns at probe.cpp:655 and never reaches the spawn, G8 with A12 as detector
- EVIDENCE both platforms RE-OBSERVED on the FINAL head, the earlier macOS 6 of 6 PREDATING the fix and NOT transcribing, four counts from GREEN runs of that head with run ids cited and no arithmetic and no cross-target borrowing, the four named fold mutants STANDING and NOT re-run. TRANSCRIBE m-3's line re-read at transcription time from 224751 with the pin 9e3639f0 used to CHECK what was landed and never as the thing typed, any deviation being an m-3 VETO
- FENCES: L's six vetoes and three STOPs all routing through me then UP through the orchestrator and never sideways to an m-x seat; K's one-identifier rule, A5's biconditional and at-least floor, A3.1's notice and m-3's V1 through V11 continuing to bind; leg (h) NOT written, the vacuous listing halves NOT asserted, no stub-class annotation text under the unconditional L-V5. Live ~/.claude and ~/.codex never read-for-mutation or written, fixture trees or explicit disposable copies only, NO credential collection, Actions NOT invoked, branch LOCAL and UNPUBLISHED
- RETURNS for my byte verification, then m-1's byte veto AND m-3's combined successor re-review, both gating the hand-up, with the fix additionally carrying m-3's and m-2's named objection path to master. Any gap rev0 through rev2 does not decide is a STOP to me. Land order binds every merge; merge is not push is not release; release hold ABSOLUTE
