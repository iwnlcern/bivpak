## PLAN (the operator's consistency fleet found ONE real product defect the whole gate chain missed — mine included — and it routes to your floor as a bounded fix: R-4.32, `EntrySchemaSkipped` emitted on the wire but ABSENT from both published schemas; the merge-gate presentation is SUPERSEDED-PENDING and NOTHING merges until this lands and re-presents) — **the operator ordered a global consistency fleet (seventeen read-only adversarial-verified agents); it confirmed ten findings, refuted zero, and returned nine clean receipts — the candidate is SOUND, the decision document was not. TWO findings touch this lane, and I verified BOTH at the bytes before carrying: (1) R-4.32 is a REAL product defect — `EntrySchemaSkipped` is emitted on the wire (exit 0, advisory; produced by `src/core/open/sessions.cpp`, `src/core/report/envelope.cpp`, `src/core/support/error.cpp/.hpp` at `4427bb3`) but is ABSENT from BOTH published contract files — I confirmed zero occurrences of `EntrySchemaSkipped` in `schemas/biv-json-envelope.v1.schema.json` AND `schemas/biv-exit-map.v1.json` at `4427bb3` (each carries `SessionsStaged` but not this kind). So a VALID envelope from biv's own round-trip of a transitive codex graph FAILS biv's own published envelope schema and the exit-map lookup; the A4 lock's "one exit-map row" clause for this kind is UNIMPLEMENTED at the contract files. The whole gate chain missed it — including my own two verifications — because `schemas/` sat OUTSIDE EVERY STATED FENCE: the fence lists were surface-complete for CODE, not for the CONTRACT FILES that publish the wire. (2) I OWN A FOOTPRINT ERROR, registered as D-5.13 instance 4 (my half): my close-out `160741` stated the "complete slice-E footprint is NINE files, product bytes only in manifest/open" — that was the `9729191..4427bb3` range (arithmetically correct) measured against the SUPERSEDED prior fold head as if it were the base; the TRUE slice-E footprint is 10 commits / 59 files / 3102+ vs `origin/main` (15 src files), and the MERGE ACT into local `main` is 23 commits / 75 files (merge-base `6047ab0`, verified at my seat) — subset-as-whole, the same measure-against-the-wrong-base failure the D-5.5 blast-radius defect was. The fleet verified the mitigations that make this CORRECTABLE-FORWARD, not a re-review: every out-of-fence byte traces to a RECORDED, REVIEWED dispatch grant, and the C/B2/R-4.8 content is the IDENTICAL published commits by sha. I correct it FORWARD in the close-out record; the immutable `160741` stands with its supersession declared.** **THE R-4.32 BOUNDED FIX GRANT to your floor (m-3's error surface — they byte-review it): add `EntrySchemaSkipped` to BOTH `schemas/biv-json-envelope.v1.schema.json` and `schemas/biv-exit-map.v1.json` EXACTLY as the A4 lock specifies — bind to the A4 lock bytes (`m3-addendum-4-9049de44-lock-20260816` @ `40bd88a6`), NOT to this paraphrase: the wire string is `"EntrySchemaSkipped"` (PascalCase per `support/error.cpp` convention), one exit-map row, the envelope-schema kind, the row-mapping split — EXECUTION, not amendment. ANYTHING THE A4 LOCK TEXT DOES NOT DETERMINE IS A STOP ROUTED UP — do not invent schema structure, do not touch `SessionsStaged` or any other kind, do not restructure either file. Its OWN commit NAMING R-4.32. MEASURE whether any test consumes `schemas/` at runtime: if CONSUMED, both platform suites re-observe on the fixed tree and the count cells are expected UNCHANGED (any movement is a STOP routed up); if NOT consumed, state the no-re-run GROUND WITH the measurement (the reason it is safe, not just the permission — your own discipline). FORBIDDEN: any other byte in either schema file, any product byte, any test byte, any count cell, any `.github` byte.** **THE SEQUENCE: fold a SCOPE_DIFF adding the two schema files to IN (fenced to the `EntrySchemaSkipped` addition per the A4 lock) — take your Implementer's PLAN-REVIEW, issue your fresh token parented to it, land the ONE commit naming R-4.32, route it to m-3 for the byte review; on m-3's PASS, my spine check, THEN master re-presents the merge gate (against the NAMED TARGET this time — 23 commits/75 files vs local main, 59 vs origin/main, per-commit grant attribution, D-5.5 radius 0, the reconcile-the-split topology). I issue NO token here.** The `165410` merge-gate presentation is SUPERSEDED-PENDING — the operator was asked NOT to rule on it and NOTHING merges on it; the candidate head `4427bb3` is unchanged and sound (nine clean fleet receipts: design-vs-impl on all six locked claims, DNA clean across the full 75-file delta, C/B2/R-4.8 identical by sha, test integrity sound, leg-(p) by-design, CI/charter/mirror byte-consistent, both registry closures exact, post-merge `main` strictly contains `origin/main`). Also registered: R-4.33 (the Linux count gate is name-blind — m-3's, non-gating). Branch LOCAL and UNPUBLISHED; the land order binds. Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ROLE: Orchestrator Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-floor-slice-e-r432-schema-gap-fix-granted
PARENT_DISPATCH_ID: s4-slice-e-fleet-findings-r432-fix
IN_REPLY_TO: ../../../../pdc/master/relays/s4-build-standup/PLAN-ORCHESTRATOR-PLANNER-FLEET-FINDINGS-PRESENTATION-SUPERSEDED-PENDING-R432-FIX-ROUTED-20260818-172346.md
RELATED_CONTEXT: ../../../../pdc/master/relays/s4-build-standup/PLAN-ORCHESTRATOR-PLANNER-SLICE-E-CLOSEOUT-COMPLETE-FINISHED-HEAD-4427BB3-PRESENTED-UP-FOR-OPERATOR-MERGE-GATE-20260818-160741.md
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — the operator ordered the fleet and holds the merge gate; the 165410 presentation is SUPERSEDED-PENDING and must not be ruled on; R-4.32 is a bounded fix at the floor under m-3 byte review, and the re-presentation (master's) follows it. No merge, push, publication, deployment, or release. The land order binds. The release hold is ABSOLUTE.
DESIGN_DOC_ID: m1-addendum-L-20260816
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m1-addendum-L-10c8e8e6-lock-20260817
SECOND_DESIGN_LOCK: m1-addendum-K-5da667fa-lock-20260816, m3-addendum-5-b8686c75-lock-20260816, m3-addendum-4-9049de44-lock-20260816
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812, m3-addendum-3-eeb4dd01-lock-20260814
CONSUMER_DESIGN_LOCK_ID: m3-addendum-3-eeb4dd01-lock-20260814
PLAN_LOCK_ID: s4-floor-slice-e-plan-20260812
FROM: s4.orchestrator-planner
TO: s4-floor.planner, s4-floor.implementer
CC: operator, s4.orchestrator-reviewer, master.orchestrator-planner, m-3.planner, m-3.implementer, m-1.planner
SUBJECT: PLAN — consistency fleet: R-4.32 (EntrySchemaSkipped emitted on the wire but absent from both published schemas; A4's exit-map row unimplemented at the contract files; schemas/ outside every fence) routed as a bounded fix to your floor under m-3 byte review, bound to the A4 lock bytes; I own my close-out footprint error (nine-files subset-as-whole vs the true 59/merge-act 75) and correct it forward; the 165410 merge presentation is superseded-pending; re-presentation follows the fix

## 1. R-4.32 verified at my seat

```text
emitted    EntrySchemaSkipped produced by sessions.cpp / envelope.cpp / error.cpp/.hpp at 4427bb3
absent     zero occurrences in schemas/biv-json-envelope.v1.schema.json AND schemas/biv-exit-map.v1.json
           (each carries SessionsStaged, not this kind)
defect     a valid envelope from biv's own round-trip FAILS biv's own published schema + exit-map lookup;
           the A4 lock's one-exit-map-row clause is UNIMPLEMENTED at the contract files
why missed schemas/ sat OUTSIDE every stated fence — surface-complete for CODE, not the CONTRACT FILES
A4 lock    m3-addendum-4-9049de44-lock-20260816 @ 40bd88a6: enum member, wire string "EntrySchemaSkipped"
           (PascalCase), one exit-map row, one row-mapping split — the floor binds HERE, not to my words
```

## 2. The bounded fix — fenced

```text
scope      EntrySchemaSkipped added to BOTH schema files per the A4 lock text; EXECUTION not amendment
STOP       anything the A4 lock does not determine -> route UP; do not invent schema structure
measure    does any test consume schemas/ at runtime?  consumed -> re-observe both suites, counts
           expected UNCHANGED (movement = STOP);  not consumed -> state the no-re-run GROUND with the measurement
commit     its OWN commit naming R-4.32
review     m-3 byte review (their error surface) -> my spine check -> master re-presents the merge gate
forbidden  any other byte in either schema, any SessionsStaged/other-kind touch, any product/test/.github/count byte
```

## 3. I own my footprint error (D-5.13 instance 4, my half)

```text
stated     close-out 160741: "complete slice-E footprint is NINE files, product bytes only in manifest/open"
was        the 9729191..4427bb3 range — the SUPERSEDED prior fold head as a false base
true       slice E vs origin/main: 10 commits / 59 files / 3102+ (15 src files)
merge act  23 commits / 75 files into local main (merge-base 6047ab0) — verified at my seat
family     subset-as-whole; measure against the TRUE base/named target, not the superseded head (the D-5.5 shape)
mitigations (fleet-verified) every out-of-fence byte traces to a RECORDED reviewed grant; C/B2/R-4.8 identical
           published commits by sha -> CORRECTABLE-FORWARD, not a re-review; I correct it in the close-out record
```

## 4. Your local path

```text
1  fold SCOPE_DIFF: the two schemas/ files -> in (fenced to the EntrySchemaSkipped addition per the A4 lock)
   -> Implementer PLAN-REVIEW -> your token
2  land the ONE commit naming R-4.32 -> route to m-3 for byte review
3  m-3 PASS -> my spine check -> master re-presents the merge gate against the NAMED TARGET; nothing merges before
```

Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/test/.github/schema byte at this seat — read-only verification this pass in `../bivpak`: `EntrySchemaSkipped` grepped in both `schemas/*.json` at `4427bb3` (zero each; `SessionsStaged` present) and `git grep`'d in `src/**` (present in sessions/envelope/error); the slice-E footprint measured vs `origin/main` (10 commits/59 files) and vs local `main` (23 commits, merge-base `6047ab0`); and in `../pdc`: the A4 lock's `EntrySchemaSkipped` clause (enum/wire/exit-map-row) confirmed at object `40bd88a6`. The fix spec lives in the A4 lock — the floor binds to those bytes, not this relay. This relay + its INDEX row ride ONE explicit-path docs-lane commit whose SHA lands after filing. No DISPATCH-IMPL issued — the R-4.32 token is your pair Planner's after your local plan-review.
RELAY_LINT: per D-3.4 (v2.9 linter landed) — per-file WITH freshness (clock read at 183517 immediately before writing, per D-5.10 instance 4); `.relays/s4/INDEX.md` tail re-read before appending; `--index`; add and commit path-scoped. Standing INDEX reds: pre-existing sibling inversions (line 222) + the v2.9 historical embedded-pipe cell-count class (R-4.27) — none mine; my appended row is 10-cell clean, status prose pipe-free.
FINAL_GIT_STATUS_SHORT: literal path-scoped status for this seat's two writes captured at commit; the shared checkout carries sibling-authored state, excluded/unclaimed.

CARRY LIST (D-8.5):
- `.relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-SLICE-E-R432-SCHEMA-GAP-BOUNDED-FIX-GRANTED-DOWN-I-OWN-MY-FOOTPRINT-ERROR-20260818-183517.md` → `s4-floor.planner`, `s4-floor.implementer`
- OPERATOR CONSISTENCY FLEET (17 adversarial-verified agents, 10 confirmed / 0 refuted / 9 clean receipts): the candidate head 4427bb3 is SOUND, the decision document was not. R-4.32 is a REAL product defect routed to your floor; the 165410 merge-gate presentation is SUPERSEDED-PENDING and NOTHING merges until the fix lands and re-presents
- R-4.32 VERIFIED AT MY SEAT: EntrySchemaSkipped is emitted on the wire (sessions.cpp/envelope.cpp/error.cpp at 4427bb3) but ABSENT from BOTH published schemas (zero occurrences in biv-json-envelope.v1.schema.json AND biv-exit-map.v1.json; each carries SessionsStaged not this kind), so a valid envelope from biv's own round-trip FAILS biv's own published schema + exit-map lookup; the A4 lock's one-exit-map-row clause is UNIMPLEMENTED at the contract files; the whole chain (my two verifications included) missed it because schemas/ sat OUTSIDE every stated fence (surface-complete for code, not the contract files)
- BOUNDED FIX GRANT: add EntrySchemaSkipped to BOTH schema files EXACTLY as the A4 lock (m3-addendum-4-9049de44 @ 40bd88a6) specifies — wire string "EntrySchemaSkipped" PascalCase, one exit-map row, envelope-schema kind, row-mapping split; EXECUTION not amendment; ANYTHING the lock does not determine is a STOP routed up; bind to the A4 lock bytes NOT my paraphrase; its OWN commit naming R-4.32; MEASURE whether any test consumes schemas/ at runtime (consumed -> both suites re-observe, counts expected UNCHANGED, movement = STOP; not consumed -> state the no-re-run GROUND with the measurement); FORBIDDEN any other byte in either schema, any SessionsStaged/other-kind touch, any product/test/.github/count byte
- I OWN A FOOTPRINT ERROR (D-5.13 instance 4, my half): my close-out 160741 stated the complete slice-E footprint as NINE files product-bytes-only-in-manifest/open, which was the 9729191..4427bb3 range against the SUPERSEDED prior fold head as a false base; the TRUE slice-E footprint is 10 commits / 59 files / 3102+ vs origin/main (15 src files) and the MERGE ACT is 23 commits / 75 files into local main (merge-base 6047ab0), verified at my seat — subset-as-whole, the same measure-against-the-wrong-base failure as the D-5.5 blast-radius defect. Mitigations fleet-verified (every out-of-fence byte traces to a recorded reviewed grant; C/B2/R-4.8 identical published by sha) make it CORRECTABLE-FORWARD not a re-review; I correct it forward in the close-out record, the immutable 160741 standing with its supersession declared
- SEQUENCE: fold a SCOPE_DIFF (two schemas/ files -> in, fenced) -> Implementer PLAN-REVIEW -> your token -> land the ONE R-4.32 commit -> route to m-3 -> m-3 PASS -> my spine check -> master re-presents the merge gate against the NAMED TARGET (23/75 vs local main, 59 vs origin/main, per-commit grant attribution, D-5.5 radius 0, reconcile-the-split topology); NO token issued here; R-4.33 (name-blind Linux skip gate) registered non-gating m-3's; branch LOCAL and UNPUBLISHED; merge != push != release; release hold ABSOLUTE
