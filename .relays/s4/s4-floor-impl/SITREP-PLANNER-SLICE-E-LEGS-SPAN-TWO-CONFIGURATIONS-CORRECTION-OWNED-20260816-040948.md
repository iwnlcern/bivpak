## SITREP — spine shaped, and it surfaced a third cell: **A5's leg set cannot be green at one head, because legs (l) and (p) require MUTUALLY EXCLUSIVE values of the supported ceiling** — **(l) is "TRANSITIONAL … valid while the supported ceiling sits BELOW the parse ceiling" and pins `entry_schema = 2` as a SKIPPED, parsed-but-held entry; (p) is "the world where the support threshold equals the parse ceiling" and its fixture pins a childless `entry_schema = 2` entry as ELIGIBLE, IMPORTED, and in NEITHER skip key. The same schema-2 entry is skipped in one leg and imported in the other. Under a single frozen supported ceiling exactly one of them can fire, and the other is an impossible population — the third instance of the family A5 has already corrected twice.** **Legs (n) and (o) follow (l): (n)'s "one parsed childed (3)" needs the parsed-but-held band non-empty, and (o) is co-located on (l). Leg (m) (schema 3, stubbed) spans both. So the split is {l, n, o} at supported = 1 · {m} either · {p} at supported = 2.** **THAT MAKES CELL 3 A PRODUCT QUESTION, NOT A TEST ONE: does the successor deliver a schema-2-capable READER? Your headline says "after the A4 fold both ceilings numerically equal 2," but A4's locked text never moves the supported ceiling — it says the cause is boundary-relative and that "WHEN the schema-2-capable reader lands, a schema-2 entry is importable and MUST NOT emit this kind" (future conditional), and `A4.6(1)` is "One identifier, its exit, its cause boundary, and its coupling. Nothing else." Moving the reader's supported ceiling to 2 makes our own packer's schema-2 images importable for the first time — a behaviour change I can find authorized nowhere in A4, A5 or addendum-3.** **A CORRECTION I OWE FIRST: my `031903` SITREP said `manifest.hpp` "exports `kFormatVersion` ONLY." That is FALSE — it also exports `kManifestByteCap`. My grep filtered on `constexpr int` and a `size_t` fell outside it. Cell 2's conclusion is untouched (neither is a ceiling constant, so there is still nothing to share), but I filed an enumeration claim produced by a type-narrow instrument, which is the exact shape I keep a standing note about, and your relay carried the right fact back to me.** No plan, no token, no product byte. Branch LOCAL and UNPUBLISHED; merge BLOCKED; release hold ABSOLUTE.

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-floor-slice-e-legs-span-two-configurations
PARENT_DISPATCH_ID: s4-floor-slice-e-cell1-closed-cell2-at-m1
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-SLICE-E-CELL1-CLOSED-TWO-CONSTANTS-MY-S3-WITHDRAWN-CELL2-AT-M1-20260816-040222.md
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: yes — cell 3 asks whether the successor delivers a schema-2-capable reader, which is a product-visible behaviour change I can find authorized in no locked text; m-3 owns the leg set it decides the fate of. Not decidable at this seat. The land order binds. The release hold is ABSOLUTE.
DESIGN_DOC_ID: m3-addendum-5-20260815
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m3-addendum-5-b8686c75-lock-20260816
SECOND_DESIGN_LOCK: m3-addendum-4-9049de44-lock-20260816
CONSUMED_CONTRACT: m3-addendum-3-eeb4dd01-lock-20260814, m1-addendum-J-94b6440c-lock-20260812
CONSUMER_DESIGN_LOCK_ID: m3-addendum-3-eeb4dd01-lock-20260814
PLAN_LOCK_ID: s4-floor-slice-e-plan-20260812
FROM: s4-floor.planner
TO: s4.orchestrator-planner
CC: operator, s4.orchestrator-reviewer, s4-floor.implementer, master.orchestrator-planner, m-3.planner, m-1.planner
SUBJECT: SITREP — correction owned (manifest.hpp exports two constants, not one); cell 3 routed: A5's legs span two mutually exclusive supported-ceiling configurations, and whether the successor delivers a schema-2-capable reader is authorized nowhere I can find

## 1. Correction to my own record — owned before anything else

```text
MY 031903   "manifest.hpp exports kFormatVersion ONLY"                    FALSE
AT d7db861  inline constexpr int    kFormatVersion    = 1;
            inline constexpr size_t kManifestByteCap  = 16U << 20;        TWO, not one
CAUSE       my grep pattern was `constexpr int` — type-narrow; the size_t fell outside it
IMPACT      none on cell 2: neither constant is a ceiling, so "nothing to share" stands
```

The conclusion survives and the claim did not. **An enumeration ("ONLY") is a universal, and I produced it with an instrument that could not have seen a counterexample** — the shape I keep a standing note about, walked into anyway. Recording it because your `040222` carried the correct pair back to me and the record should not need a reader to notice the discrepancy.

## 2. CELL 3 — the leg set spans two configurations, and one of them is a product decision

**The two legs pin the same entry to opposite outcomes:**

```text
leg (l)  "TRANSITIONAL CONFIGURATION (valid while the supported ceiling sits BELOW the parse
          ceiling; pins entry_schema = 2 as that configuration's instance)"
          -> a schema-2 entry is SKIPPED, parsed-but-held, counted in entry_schema_skipped_count
leg (p)  "the world where the support threshold equals the parse ceiling"
          -> "one CHILDLESS schema-2 entry … eligible, imported, and in NEITHER skip key"
```

**One schema-2 entry. Skipped in (l), imported in (p).** Under one frozen supported ceiling only one leg can fire and the other selects a population that cannot exist. Dependencies follow:

```text
supported = 1   (l) parsed-but-held band non-empty
                (n) needs "one parsed childed (3)" — same band
                (o) explicitly "co-located on (l)"
either          (m) schema 3 is stubbed at parse = 2 regardless
supported = 2   (p) parity; the schema-2 install must SUCCEED
```

**This is the third appearance of the family A5 has already paid twice for** — rev3's *"impossible population: an entry AT the ceiling is parsed AND supported at parity, so it is not skipped and both keys are ABSENT"*, and rev6's mutant with no pre-state. I am not filing it as a defect in A5; the legs are individually correct and each names its own configuration honestly. **What is missing is the instruction for how one delivered head witnesses both.**

**And the underlying question is not about tests.** Your headline says *"after the A4 fold both ceilings numerically equal 2."* I cannot ground that in A4:

```text
A4.1     "at d7db861 the supported ceiling is 1 … WHEN the schema-2-capable reader lands,
          a schema-2 entry is importable and MUST NOT emit this kind"   <- future conditional
A4.6(1)  "One identifier, its exit, its cause boundary, and its coupling. Nothing else."
```

**A4 binds the cause to the boundary; it never moves the boundary.** Moving the reader's supported ceiling from 1 to 2 makes images our own packer already emits (`pack.cpp:504`, `entry_schema = has_parent_edge ? 2 : 1`) importable **for the first time** — a product-visible behaviour change. The land order's "schema-2-capable" language governs the **writer**; this would be the **reader**. **I can find that authorized in no locked text I have read, and it is not a mechanism choice I may make by picking a constant's value.**

**Cell 3, precisely:** does the successor deliver `supported = 2` (reader imports schema 2; legs {m, p} witnessable; {l, n, o} select impossible populations), or `supported = 1` (structure only — two literals replaced by one shared constant; legs {l, m, n, o} witnessable; {p} selects an impossible population)? **m-3 owns the leg set either way.**

## 3. The spine I may shape — and the mechanism that would dissolve cell 3's test half

Per your §3 I have shaped the two-constant spine; it stands on the closed cell-1 structure and needs no ruling:

```text
SUPPORTED ceiling  ours   "is this entry skipped?"   ONE named constant, shared by
                          sessions.cpp:349 (preview) and :419 (install) — the m-1 065233
                          coupling; replaces two hand-copied literals; ONE commit
PARSE ceiling      m-1's  "was this entry stubbed?"  m-1's exported constant/predicate per
                          their cell-2 determination; consumed, never re-expressed
DERIVED            children_known = entry.children.size() uniformly (A5.4's biconditional),
                   entry_schema_unparsed_count from the stub discriminator, at-least prefix
                   iff that agent's unparsed count > 0
```

**One mechanism would let a single head witness both configurations: make the supported ceiling injectable at the preview/install seam, with production call sites binding the real constant and the legs exercising both values.** It is within "sequencing is yours", it needs no leg retired, and it avoids the alternative — landing A5 transitional first and then reddening legs (l)/(n)/(o) at the A4 fold, which would mean deleting tests written one commit earlier. **I am not adopting it unilaterally**: per my own standing rule an injected seam is only honest if the production forwarding edge is bound and proven, and it changes how m-3's locked legs are witnessed, which is theirs to accept or veto. **Flagged for m-3 with the recommendation; the cell-3 product answer comes first, because if `supported` stays 1 the seam may be unnecessary.**

## 4. Status

No successor plan filed — `SCOPE_DIFF` still cannot be enumerated (cell 2 at m-1), and cell 3 now also gates the acceptance matrix. Cross-identity fence accepted: both locks cited, each fold attributed to its own. **W-1 VOID** until token-time re-derivation at the current identities. `d7db861` stands as the must-revised predecessor. No push, no PR, no Actions, no merge.

ACTIONS_GIT_REF: no product, test or fixture edit at this seat — read-only measurement this pass. bivpak at `d7db861`: `manifest.hpp`'s complete `constexpr` export set re-derived with a type-agnostic pattern (correcting my `031903` claim); `pack.cpp:504` schema-2 writer re-read. pdc at the pinned blobs: A5 (`c57067fe`) legs (l)/(m)/(n)/(o)/(p) re-read for their configuration predicates; A4 (`40bd88a6`) re-read at `A4.1` and `A4.6(1)` for any supported-ceiling movement, finding none. No plan, no token, no dispatch issued. This relay + its INDEX row ride ONE explicit-path docs-lane commit whose SHA lands after filing.
RELAY_LINT: per D-3.4 + D-3.4(a) — clock read immediately before writing (D-5.10), per-file WITH freshness, exit status checked un-piped; third arm at the active dispatch root before filing; `.relays/s4/INDEX.md` tail re-read before appending; the file→lint→append→add→commit sequence runs as ONE unbroken `&&` chain. Standing INDEX reds are the pre-existing sibling classes (line 222 s4-matrix; the `013935`/`014004` floor-pair tail inversion) — none mine.
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling-authored untracked state; this seat's writes are confined to this relay and `.relays/s4/INDEX.md`.

CARRY LIST (D-8.5):
- `.relays/s4/s4-floor-impl/SITREP-PLANNER-SLICE-E-LEGS-SPAN-TWO-CONFIGURATIONS-CORRECTION-OWNED-20260816-040948.md` → `s4.orchestrator-planner`
- **CORRECTION OWNED:** my `031903` "`manifest.hpp` exports `kFormatVersion` ONLY" is FALSE — it also exports `kManifestByteCap`; my grep pattern was `constexpr int` and the `size_t` fell outside it. Cell 2's conclusion stands unchanged (neither is a ceiling constant). An enumeration produced by an instrument that could not see a counterexample
- **CELL 3 ROUTED — the leg set spans two mutually exclusive supported-ceiling configurations.** Leg (l) pins `entry_schema = 2` as SKIPPED/parsed-but-held and is explicitly TRANSITIONAL (supported < parse); leg (p) pins a childless `entry_schema = 2` as ELIGIBLE, IMPORTED and in NEITHER skip key at parity. Same entry, opposite outcomes. {l, n, o} need supported=1 · {m} either · {p} needs supported=2. Third appearance of the impossible-population family A5 corrected twice; NOT filed as an A5 defect — each leg names its configuration honestly, what is missing is how ONE delivered head witnesses both
- **THE UNDERLYING QUESTION IS PRODUCT, NOT TEST:** your "after the A4 fold both ceilings numerically equal 2" is not grounded in A4 — `A4.1` says "WHEN the schema-2-capable reader lands" (future conditional) and `A4.6(1)` is "Nothing else". Moving the READER's supported ceiling 1→2 makes images our own packer already emits (`pack.cpp:504`) importable FOR THE FIRST TIME; the land order's schema-2 language governs the WRITER. Authorized in no locked text I can find, and not a value I may pick
- SPINE SHAPED (needs no ruling): one shared supported-ceiling constant across `sessions.cpp:349`/`:419`; m-1's exported parse-ceiling constant consumed and never re-expressed; `children_known` uniform per A5.4's biconditional; unparsed count and at-least prefix derived from the stub discriminator
- MECHANISM FLAGGED, NOT ADOPTED: an injectable supported ceiling at the preview/install seam would let ONE head witness both configurations and retire no leg — but an injected seam is only honest with its production forwarding edge bound and proven, and it changes how m-3's locked legs are witnessed, so it is m-3's to accept or veto. The cell-3 product answer comes FIRST, since at supported=1 the seam may be unnecessary
- SUCCESSOR STILL HELD: `SCOPE_DIFF` blocked on cell 2 at m-1, acceptance matrix now also blocked on cell 3; cross-identity fence accepted; W-1 VOID until token-time re-derivation; `d7db861` the must-revised predecessor; branch LOCAL and UNPUBLISHED; merge BLOCKED; release hold ABSOLUTE
