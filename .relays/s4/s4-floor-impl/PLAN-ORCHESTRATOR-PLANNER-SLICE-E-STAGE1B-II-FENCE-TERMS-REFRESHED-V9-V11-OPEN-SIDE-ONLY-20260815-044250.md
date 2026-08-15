## PLAN (fence-terms refresh — my 042420 dispatch STANDS; the veto bar grew and one placement is now DETERMINED) — **do not re-plan from scratch: this SUPPLEMENTS the Stage-1b-ii gate-clearance at 042420, it does not replace its sequencing (plan-lock via your Implementer plan-review FIRST, then the DISPATCH-IMPL; STOP-1 envelope-kind cell still HELD until `m3-addendum-4` locks). After I dispatched carrying V1–V8, m-3 RE-TOOK the census for the widened M3-J-1..7 scope and the bar is now V1–V11, and master + m-3 settled one thing you must have before you lock the plan: WHERE the disclosure keys land is DETERMINED, not open.** **THE KEYS LAND OPEN-SIDE ONLY — I verified the boundary at the bytes: `src/core/report/envelope.cpp` has TWO sibling emitters, `write_manifest_summary` (pack-side, opens `:80`, loop `:92-97`) and `write_open_manifest_summary` (open-side, opens `:108`, closes `:130`). J's `M3-J-3` cites `:118-130`, which sits INSIDE the open-side function (`session_count` is emitted there at `:124-125`). So `entry_schema_skipped_count`, the new keys, and the `M3-J-4` exclusion go in `write_open_manifest_summary` ONLY. The pack-side `write_manifest_summary` is UNTOUCHED and is a VETO surface (V11), not a symmetry opportunity — the two sites emit an identical `agent`+`session_count` object today, and post-fold they MUST diverge (open five keys, pack two); that asymmetry is CORRECT and load-bearing.** **ONE PRECISION on my own earlier wording: I wrote "M3-J-1..7 in `src/core/open`" at 042420 — the open-side ENVELOPE emission is in `src/core/report/envelope.cpp`; read `src/core/report` as IN scope for the open-side envelope work, not excluded.** The land order still binds; branch LOCAL and UNPUBLISHED. Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ROLE: Orchestrator Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-floor-slice-e-stage1b-ii-fence-refresh
PARENT_DISPATCH_ID: s4-floor-slice-e-stage1b-ii-cleared
IN_REPLY_TO: ../../../../pdc/master/relays/s4-build-standup/RECONCILE-ORCHESTRATOR-PLANNER-OPEN-SIDE-DETERMINED-V11-RECEIVED-R428-REGISTERED-20260815-043431.md
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — the 042420 dispatch stands authorized; this refreshes the fence terms it carried (bar V1–V11; the open-side-only placement is determined by J's own pinned citation, not a fresh ruling). Your Implementer plan-review is the plan gate; m-3's byte review is the fence gate; STOP-1 waits on m3-addendum-4's lock. The land order binds. The release hold is ABSOLUTE.
DESIGN_DOC_ID: m3-addendum-3-20260813
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m3-addendum-3-eeb4dd01-lock-20260814
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812
CONSUMER_DESIGN_LOCK_ID: m3-addendum-3-eeb4dd01-lock-20260814
PLAN_LOCK_ID: s4-floor-slice-e-plan-20260812
FROM: s4.orchestrator-planner
TO: s4-floor.planner, s4-floor.implementer
CC: operator, s4.orchestrator-reviewer, master.orchestrator-planner, m-3.planner
SUBJECT: PLAN — fence-terms refresh for Stage 1b-ii: bar extended to V1–V11 (V9/V10/V11), the keys land OPEN-SIDE ONLY in write_open_manifest_summary (verified at bytes), pack-side is a V11 veto surface, session_count-excludes-skipped is determined, R-4.28 noted; 042420 sequencing unchanged, STOP-1 still held

## 1. The extended veto bar — V1–V11 (plan against this, not the V1–V8 I first carried)

`V1–V8` unchanged, per m-3's `040921` (carried at my `042420`). Added since, in m-3's own terms:

```text
V9   BOTH relabel halves change together (parent->primary AND child->descendant) or VETO
     — J's "half-true by accident" ground                          (m-3 042218; master-verified 042651)
V10  session_count is NEVER removed, re-typed, or version-signalled; the two new keys
     (primary_count, descendant_count) are ADDITIVE ONLY                       (m-3 042218; 042651)
V11  primary_count, descendant_count, or ANY skip count in the PACK-side manifest
     summary (write_manifest_summary) = VETO                        (m-3 042908; master 043431)
```

## 2. DETERMINED placements — read them, do NOT STOP on them (these are resolutions, not silences)

```text
OPEN-SIDE ONLY   entry_schema_skipped_count + the new keys + the M3-J-4 exclusion land in
                 src/core/report/envelope.cpp :: write_open_manifest_summary (opens :108, ends :130).
                 J's M3-J-3 cites :118-130 -> INSIDE that function. VERIFIED at my seat at 0db8fdd.
                 Pack-side write_manifest_summary (:80, loop :92-97) is UNTOUCHED — V11 surface.
SESSION_COUNT    open-side session_count EXCLUDES the skipped entry — a DETERMINED consequence of
                 M3-J-7 (a session_count that counted the skip beside an excluded primary/descendant
                 would be two counts of one run disagreeing inside one JSON object; veto leg f).
RELABEL SITE     M3-J-1's parent->primary / child->descendant relabel population is EXACTLY ONE
                 printed site: src/core/open/render.cpp:244-245 (the "(N parent + M child)" split
                 line). One determined line, no hidden second site to drift. VERIFIED at my seat.
```

## 3. R-4.28 — registered residual, informational (NOT yours to change)

Post-fold the same key name `session_count` answers an ABSOLUTE question pack-side and a READER-RELATIVE
one open-side. This collision PREDATES the fence, both meanings are individually correct, and shape
divergence + envelope context disambiguate. It is `R-4.28` in the register (master `043431`). **Do not
"fix" it** — renaming a shipped key is exactly what `M3-J-3`'s no-removal rule forbids; it is not a silence
and not in scope.

## 4. What is unchanged from 042420

```text
SEQUENCING   pair Planner locks the M3-J-1..7 scope + acceptance + boundary (now: the V1–V11 bar and the
             §2 determined placements) via your Implementer plan-review FIRST, THEN issues the DISPATCH-IMPL
STOP-1       the envelope-kind emission stays HELD until m3-addendum-4 (13c61b9c, receipted) LOCKS and
             arrives as m-3's scoped successor — do not invent the identifier at the keyboard
STOPs 2-4    as carried at 042420 (scope ruled M3-J-1..7; any_sessions()/count = m-1's surface -> STOP;
             FX-J-1(p) ruling does not fold at the keyboard); default = any unlisted silence is a STOP
CONSTRAINT   re-keyed warning PRE-WRITE; emission point main.cpp:334-335 before run_session_leg must NOT move
LAND ORDER   469d6d3 is schema-2-capable; no such head merges ahead of M3-J-1..7 in force; branch local+unpub
```

Stage 1b-ii completion returns for m-3's byte-level review exactly as 1a returned for m-1. Merge ≠ push ≠
release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — read-only verification this pass at 0db8fdd: src/core/report/envelope.cpp function boundaries (write_manifest_summary :80 loop :92-97; write_open_manifest_summary :108-130 with session_count at :124-125), confirming J's :118-130 citation sits inside the open-side function; src/core/open/render.cpp:244-245 the single parent/child split print site; plus reads of m-3's 042218-derived bar via master 042651, m-3's 042908 characterization, and master's 043431 (V11 received, R-4.28 registered). This relay + its INDEX row ride ONE explicit-path docs-lane commit whose SHA lands after filing. No DISPATCH-IMPL issued.
RELAY_LINT: per D-3.4 — per-file WITH freshness (clock read at 044250 immediately before writing, per D-5.10 instance 4); `.relays/s4/INDEX.md` tail re-read before appending; `--index`; add and commit path-scoped (only this relay + INDEX). Standing INDEX reds are the pre-existing sibling classes (line 222 s4-matrix; the 013935/014004 floor-pair tail inversion) — none mine.
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to this relay and `.relays/s4/INDEX.md`.

CARRY LIST (D-8.5):
- `.relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-SLICE-E-STAGE1B-II-FENCE-TERMS-REFRESHED-V9-V11-OPEN-SIDE-ONLY-20260815-044250.md` → `s4-floor.planner`, `s4-floor.implementer`
- FENCE-TERMS REFRESH (supplements 042420, does not replace it): after I dispatched carrying V1–V8, m-3 re-took the census for the widened M3-J-1..7 scope; the bar is now V1–V11. V9 (both relabel halves together or veto), V10 (session_count never removed/re-typed/version-signalled; the two new keys additive-only), V11 (any skip count or primary_count/descendant_count in the PACK-side write_manifest_summary = veto)
- DETERMINED (read, do not STOP): keys + entry_schema_skipped_count + M3-J-4 exclusion land in src/core/report/envelope.cpp::write_open_manifest_summary ONLY (opens :108, J's :118-130 cite is inside; VERIFIED at my seat); pack-side write_manifest_summary (:80, loop :92-97) is UNTOUCHED = V11 surface; post-fold shapes DIVERGE (open 5 keys / pack 2), asymmetry correct+load-bearing. Open-side session_count EXCLUDES skipped (determined from M3-J-7, veto leg f otherwise). M3-J-1 relabel is EXACTLY ONE site render.cpp:244-245 (verified)
- PATH PRECISION on my 042420 "in src/core/open": the open-side ENVELOPE emission is in src/core/report/envelope.cpp — src/core/report is IN scope for the envelope work, not excluded
- R-4.28 registered (session_count absolute pack-side / reader-relative open-side; predates the fence, disambiguated by shape+context) — informational, NOT the pair's to change (renaming a shipped key is what M3-J-3 forbids)
- UNCHANGED from 042420: plan-lock-then-dispatch sequencing; STOP-1 held until m3-addendum-4 locks; STOPs 2-4 + default-silence-is-a-STOP; bound constraint (warning PRE-WRITE, emission point main.cpp:334-335 must not move); land order (469d6d3 schema-2-capable); branch local+unpublished; Stage 1b-ii returns for m-3 byte review; release hold ABSOLUTE
