## PLAN (successor r5, slice E) — **narrow, as requested: ONE Stage-1b start rule, stated everywhere.** My r4 said in §2 that the adapter/manifest-layer 1b work was `NOT GATED` and in §4 that no Stage-1b byte starts before the receipt. Both mine, contradicting each other at exactly the boundary the revision existed to settle. **I take option 2 — the split — because the boundary turns out to be MEASURABLE rather than a matter of taste: `tests/test_adapter_codex_install.cpp` includes `adapters/codex/codex.hpp` and NOT `core/open/sessions.hpp`, and has ZERO references to the open-side session flow, so keys `4a`/`5`/`6` never touch the consumer. `tests/test_cli.cpp` drives `BIV_BINARY_PATH` — the shipped binary — and therefore does.** **Seven of the eight keys are receipt-independent; exactly one instrument crosses the line.**

ROLE: Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-floor-slice-e-plan-successor-r5
PARENT_DISPATCH_ID: s4-floor-slice-e-fence-extended-manifest
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — the consumer disposition (routed UP at `020326`, onward path master's) gates Stage 1b-ii. Stage 1a needs this plan's review plus m-1's byte-level approval; Stage 1b-i needs that approval and nothing from the consumer. The release hold is ABSOLUTE.
DESIGN_DOC_ID: m2-addendum-12-transitive-collect-mono-gate-20260812
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m2-addendum12-29a5b3a3-lock-20260812
TARGET_DESIGN_SHA256: 29a5b3a3abb6777af70a1c959728f4f61731489a1735773e81713b5aa3ea3adb
TARGET_DESIGN_COMMIT: 6eeeb157be249792d61774016485d97c303e2c8f
SUPERSEDED_DESIGN_LOCK_ID: m2-addendum12-154cd87e-lock-20260812
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812
PLAN_LOCK_ID: s4-floor-slice-e-plan-20260812
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-REVIEW-IMPLEMENTER-SLICE-E-SUCCESSOR-R4-MUST-REVISE-STAGE1B-GATE-CONTRADICTION-20260813-021601.md
RELATED_CONTEXT: .relays/s4/s4-floor-impl/PLAN-PLANNER-SLICE-E-SUCCESSOR-R4-JCAPABLE-READER-M3-GATED-E2E-20260813-020509.md (r4 — superseded ONLY as to the Stage-1b start rule; its reader transition, tests, falsifier and narrowed 1a claim PASSED review and carry); .relays/s4/s4-floor-impl/CORRECTION-PLANNER-M3-CELL-ROUTES-VIA-MASTER-NOT-DIRECT-20260813-021028.md (operative routing correction)
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: s4.orchestrator-planner, operator, s4.orchestrator-reviewer, master.orchestrator-planner
SUBJECT: PLAN (successor r5) — Stage 1b split into 1b-i (receipt-independent) and 1b-ii (receipt-gated) on a measured include-boundary; one start rule stated everywhere

## 0. Pins re-derived AT THIS ACT

```text
addendum-12 @ 6eeeb157  29a5b3a3abb6777a…  == the lock    J @ pdc HEAD  94b6440c6ea5342a…  UNMOVED
origin/main             0db8fdd            unchanged -> the consumer surface is as measured at 020326
```

## 1. The contradiction, owned

```text
r4 §2  "NOT GATED … Stage 1b's collector/gate/cap work whose falsifiers live at the adapter and
        manifest layers rather than through `biv open`"
r4 §4  "STAGE 1b DOES NOT START until the m-3 receipt is present AND its dependency-integrity
        controls pass"
```

**Both are mine and they authorize opposite execution orders.** §2 was a true observation about which
falsifiers exercise the consumer; §4 was a rule. **I let an observation sit where a rule belonged**, and at
the one boundary this revision existed to settle. A reader could have started 1b bytes or been forbidden
them, citing the same document.

## 2. The rule, chosen ONCE — option 2, on a boundary I measured rather than judged

```text
tests/test_adapter_codex_install.cpp   includes adapters/codex/codex.hpp, rewrite_common.hpp,
                                       version_floor.hpp, core/support/probe.hpp
                                       — NOT core/open/sessions.hpp, and ZERO references to the
                                       open-side session flow (build_preview / install_sessions / rows)
tests/test_cli.cpp                     drives BIV_BINARY_PATH — the SHIPPED BINARY — so it runs the real
                                       `biv open` path and therefore `sessions.cpp:345` / `:410`
```

**THE LINE, stated so it can be applied without me:** an assertion is **receipt-dependent iff it requires a
`entry_schema = 2` entry to survive the shipped `biv open` session-install path.** Nothing else is. That is
a property of the instrument, checkable by reading its includes and whether it invokes the binary — not a
judgement about how "integration-y" a test feels.

```text
STAGE 1b-i   RECEIPT-INDEPENDENT. Starts on m-1's approval of Stage 1a. NOT gated by the consumer.
  production  src/adapters/adapter.hpp            child_parent_map carrier
              src/adapters/codex/codex.cpp        closure · rootless disposition · staged-reader gate ·
                                                  warning producers            (ANCHORED — A3 fires)
              src/adapters/codex/install.cpp      writer gate · mapped node set
              src/core/pack/pack.cpp              edge emission under J's absence license · the four caps
  tests       tests/test_adapter_codex_collect.cpp   greens 1a, 3, 4
              tests/test_adapter_codex_install.cpp   4a, 5 (atomic), 6
              tests/test_pack.cpp                    1b, key 2 BOTH arms, the eight cap arms
  => SEVEN of the eight keys (1a, 1b, 2, 3, 4, 4a, 5, 6 minus none; 7 is a Stage-0 claude control)
     complete here, with the cap carrier and the atomic-absence oracle.

STAGE 1b-ii  RECEIPT-GATED. Starts only when the consumer disposition has landed AND names a SHA.
  tests       tests/test_cli.cpp   the three-level shipped-binary R<-P<-C E2E, and EVERY assertion that a
                                   transitive session INSTALLS through the real CLI
  => ONE instrument crosses the line. The claude reference-resolution controls already in test_cli.cpp
     from Stage 0 are NOT gated — they involve no schema-2 entry and already pass.
```

**§2's `NOT GATED` phrasing is DELETED and replaced by this table.** There is no longer a sentence anywhere
in this plan that describes gating without saying whether bytes may start.

## 3. The start rule, restated identically everywhere it appears

```text
STAGE 1a     starts on THIS plan's review approve.  Lands as its OWN EXACT COMMIT and STOPS for m-1's
             byte-level approval/veto — SHA reported, verdict awaited, no 1b byte before it.
STAGE 1b-i   starts on m-1's APPROVAL of 1a, and on nothing else. The consumer disposition does NOT gate it.
             Additional precondition: key 2 arm 2 GREEN after 1a — a RED there means OUR 1a broke J's
             absence license and is a STOP, not a 1b-i task.
STAGE 1b-ii  starts only when the consumer disposition has landed and names a SHA. Until then
             tests/test_cli.cpp gains NO schema-2 assertion, and the E2E is reported as OWED, not as
             deferred coverage that quietly never returns.
ANY pre-named silence (multi-cap breach; a J-R6/J-R7 question; the cap-carrier seam) HALTS AND ROUTES
             UP to me, with no answer chosen locally.
```

**The honest consequence, stated rather than buried:** if the disposition never lands, slice E completes
with **seven of eight keys green and the acceptance instrument OWED**. That is a real gap in the operator's
own criterion — "installed and working without recollection issues" — and it must be reported in those
words at hand-up, not softened into "covered at the adapter layer." **Seven keys at the adapter and manifest
layers do not add up to one shipped round trip.**

## 4. Carried unchanged (all PASSED at `021601`)

The J-capable reader transition — schema 2 recognized and fully parsed/validated, only above the supported
maximum on the disclosed-skip path, the maximum being 2 because J-R3 determines it; the three killing tests
separating a moved threshold from a deleted branch (schema 2 in full, 3 skipped, 99 skipped); the
compatibility falsifier run with the **base `0db8fdd` binary** because the new head cannot impersonate the
pre-J reader; the narrowed Stage-1a claim stated in both halves (producer-side inert, reader-side changed —
both go in the report); `src/core/open/sessions.cpp` **HARD-OUT** with no widening; the three STOPs and five
VETOES verbatim under m-1's byte-level veto; the manifest-only fence with `.github`, sealed docs and every
unnamed path out; J's determining text as read at the sealed bytes; the `parse_session_children`
primary-threading fact to be NAMED in the report; the `ArchiveWriteFailed` cap carrier at exit 4 with both
names in `detail`; the atomic-absence cap+1 oracle on the three source-derived paths with its at-cap
positive arm; the three semantic killing arms; key 5 atomic and **`FX-A12-3`'s never-executed legs owed at
1b-i** (shown executing and passing, and shown failing against a least-of-component implementation); A3's
four checks on ONE `codex.cpp` head with its ONE pin; sandbox guards and the credential decoy, **NEVER the
live `~/.claude`/`~/.codex`**; macOS plus **governing** local Ubuntu 24.04 `linux/amd64` Docker with
**Actions NOT invoked**; the base-container control; branch cut from `origin/main` never local `main`;
publication HELD; D-5.5(a) at hand-up; the token-time seven-element tuple with both hashes re-derived at
that act. **Stage 0 remains ACCEPTED and unpublished at `dca6b7d`.**

**Routing, per the operative `021028` correction:** cells leaving this pair go UP to
`s4.orchestrator-planner` and the onward path is theirs and master's to name. **This plan names no
cross-domain destination and no onward sequence**, and where earlier revisions did, `021028` governs.

## 5. What I am asking of you

**A plan review of the start rule only** — is there now exactly one answer, in every place the question
arises, to "may this byte start"; is the receipt-dependence test (does the assertion need a schema-2 entry
to survive the shipped `biv open` path) applicable without me; and does the 1b-i / 1b-ii split leave any
instrument ambiguously placed? Reply with `PLAN_REVIEW_VERDICT: approve` or `must-revise` (verdict line BARE
— no bold, no backticks; remarks via em-dash only, per the matcher's recorded grammar). **On approve,
Stage 1a is dispatchable.** Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — at this act: re-hashed addendum-12 at `6eeeb157` and J at pdc HEAD, re-measured `origin/main`; and measured the receipt-dependence boundary by reading `tests/test_adapter_codex_install.cpp`'s include set (no `core/open/sessions.hpp`; zero open-side session-flow references) against `tests/test_cli.cpp`'s use of `BIV_BINARY_PATH`; this relay + its INDEX row ride one explicit-path docs-lane commit whose SHA lands after filing
RELAY_LINT: per D-3.4 — per-file WITH freshness before filing; INDEX tail re-read immediately before appending; `--index`; `&&`-gated append→lint→commit. Disclosed reds: INDEX line 222 (inherited) and the `013935`/`014004` tail inversion I caused and disclosed at `014257`, which stays deliberately unindexed to avoid a second inversion and is named in the `020326` row
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to this relay and `.relays/s4/INDEX.md`

CARRY LIST:
- `.relays/s4/s4-floor-impl/PLAN-PLANNER-SLICE-E-SUCCESSOR-R5-STAGE1B-SPLIT-ON-MEASURED-BOUNDARY-20260813-023240.md` → `s4-floor.implementer`; r4 `020509` superseded ONLY as to the Stage-1b start rule
- **the contradiction owned:** r4 §2 called the adapter/manifest 1b work `NOT GATED` while §4 forbade any 1b byte before the receipt. **I let an OBSERVATION sit where a RULE belonged**, at the one boundary the revision existed to settle
- **option 2 taken, on a MEASURED boundary:** `test_adapter_codex_install.cpp` includes `adapters/codex/codex.hpp` and NOT `core/open/sessions.hpp`, with zero open-side session-flow references, so keys `4a`/`5`/`6` never touch the consumer; `test_cli.cpp` drives `BIV_BINARY_PATH` and does. **The test: an assertion is receipt-dependent IFF it requires a schema-2 entry to survive the shipped `biv open` session-install path** — a property of the instrument, not a judgement about how integration-y it feels
- **1b-i (receipt-INDEPENDENT, starts on m-1's approval of 1a):** `adapter.hpp`, `codex.cpp` (anchored), `codex/install.cpp`, `pack.cpp` + `test_adapter_codex_collect.cpp`, `test_adapter_codex_install.cpp`, `test_pack.cpp` — **seven of eight keys, the cap carrier and the atomic-absence oracle**. **1b-ii (receipt-GATED):** `test_cli.cpp` only — the shipped-binary E2E and every real-CLI transitive-install assertion. Stage-0's claude controls in that file are NOT gated
- **`NOT GATED` phrasing DELETED**; one start rule restated identically for 1a, 1b-i, 1b-ii and the STOPs
- **honest consequence stated, not buried:** if the disposition never lands, slice E completes with seven of eight keys green and **the acceptance instrument OWED** — reported in those words at hand-up, never softened into "covered at the adapter layer," because seven keys at the adapter and manifest layers do not add up to one shipped round trip
- everything that PASSED at `021601` carries: the reader transition and its three tests, the base-binary compatibility falsifier, the two-halves Stage-1a claim, `sessions.cpp` hard-out, STOPs/VETOES, J's determining text, the cap carrier and oracle, `FX-A12-3`'s owed legs, A3, sandbox/decoy, Docker governing with Actions untouched, branch mechanics, token-time tuple; Stage 0 ACCEPTED at `dca6b7d`
- **routing per `021028`: this plan names no cross-domain destination and no onward sequence** — cells go UP and the onward path is the orchestrator's and master's; release hold ABSOLUTE
