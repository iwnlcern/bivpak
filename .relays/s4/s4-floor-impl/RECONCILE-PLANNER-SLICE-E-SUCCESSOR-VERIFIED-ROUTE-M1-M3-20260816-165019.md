## RECONCILE — successor VERIFIED at the bytes at `9729191`; every K veto, STOP and fence holds — **and the most useful thing I can report is a defect in MY OWN verification that I caught and fixed before it became a false green: my first K-R4(1) scan (`entry_schema … \s*[0-9]`) returned CLEAN on the candidate, and I ran it against `d7db861` as a control before believing it — where `entry.entry_schema > 2` demonstrably exists — AND IT RETURNED CLEAN THERE TOO. The `\s` escape is not honoured by this grep. I had a veto check that COULD NOT FAIL and it was about to certify the single most important rule in K. Re-run with a validated pattern (`entry_schema *[<>=!]+ *[0-9]`, confirmed firing on all FOUR sites at `d7db861`), the candidate has exactly ONE hit — `manifest.cpp:347`'s `< 1` validity floor, which K-R3(1) preserves BY NAME. Zero surviving ceiling literals, now on evidence rather than on a blind instrument.** **THE TWO CONSTANTS ARE STRUCTURALLY SEPARATE, WHICH IS K-R2's WHOLE POINT: `manifest.hpp:15` `inline constexpr int kEntrySchemaParseCeiling = 2` and `sessions.hpp:17` `inline constexpr int kEntrySchemaSupportedCeiling = 1` — different names, different namespaces, different values, and the parse ceiling is CONSUMED at `sessions.cpp:354` by QUALIFIED REFERENCE (`manifest::kEntrySchemaParseCeiling`), never copied. K-R4(2) and K-R4(3) both hold structurally rather than by inspection.** **A5.2's UNIFORM EXPRESSION IS CORRECT AND I VERIFIED ITS PREMISE RATHER THAN ASSUMING IT: the skipped count is `1U + entry.children.size()` for every skipped entry, with no branch — which is exactly what `A5.4` mandates ("uniformly `entry.children.size()` … by the biconditional rather than by a branch") and is only true if a STUB carries no children. It does: `entry.children` is assigned at `manifest.cpp:435`, eighty-five lines BELOW the stub early-return at `:350`, so a stub contributes exactly 1 — `A5.4`'s "each unparsed entry contributes exactly 1 to `entry_schema_skipped_count`." The elegance is load-bearing and it rests on a fact I checked.** **All three within-file fences hold by whole-function hashing: `any_sessions()` `0d51b5b0…` and pack-side `write_manifest_summary` `4e1ff402…` are BYTE-IDENTICAL across the delta.** Hand-up still BLOCKED on m-1's manifest veto and m-3's combined re-review. Branch LOCAL and UNPUBLISHED; merge BLOCKED; release hold ABSOLUTE.

ROLE: Planner
PHASE: RECONCILE
AUTHORITY: review-only
DISPATCH_ID: s4-floor-slice-e-successor-verified-routeup
PARENT_DISPATCH_ID: s4-floor-slice-e-successor-implemented-verified-stop-byte-reviews
IN_REPLY_TO: .relays/s4/s4-floor-impl/SITREP-IMPLEMENTER-SLICE-E-SUCCESSOR-IMPLEMENTED-VERIFIED-STOP-BYTE-REVIEWS-20260816-163751.md
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — hand-up is blocked on m-1's byte-level MANIFEST veto and m-3's COMBINED successor re-review, neither of which this verification discharges. Merge, seal, publication, deployment and release retain separate gates. The land order binds. The release hold is ABSOLUTE.
DESIGN_DOC_ID: m1-addendum-K-20260816
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m1-addendum-K-5da667fa-lock-20260816
TARGET_DESIGN_SHA256: 5da667fa507f7d8687bb0ffaa2dfa919220e4939172207269f25f55c89f94667
TARGET_DESIGN_COMMIT: 0e455ef5bf9b48870f6d061146a0dbd80dd2de96
SECOND_DESIGN_LOCK: m3-addendum-4-9049de44-lock-20260816, m3-addendum-5-b8686c75-lock-20260816
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812, m3-addendum-3-eeb4dd01-lock-20260814
CONSUMER_DESIGN_LOCK_ID: m3-addendum-3-eeb4dd01-lock-20260814
PLAN_LOCK_ID: s4-floor-slice-e-plan-20260812
FROM: s4-floor.planner
TO: s4.orchestrator-planner
CC: operator, s4.orchestrator-reviewer, s4-floor.implementer, master.orchestrator-planner, master.orchestrator-reviewer, m-1.planner, m-1.implementer, m-3.planner, m-3.implementer
SUBJECT: RECONCILE — successor verified at 9729191: K-R4(1) re-established on a VALIDATED pattern after my first scan proved blind; two constants structurally separate; A5.2's uniform expression premise checked; three fences hash-identical; routing for m-1 and m-3 byte reviews

## 1. The verification defect I caught in myself — reported first because it is the transferable part

```text
MY FIRST PATTERN   entry_schema[^_a-zA-Z]*(>|<|>=|<=|==|!=)\s*[0-9]
ON THE CANDIDATE   0 hits   -> looked like K-R4(1) PASS
CONTROL RUN        the SAME pattern on d7db861, where `entry.entry_schema > 2` EXISTS
                   0 hits   -> THE PATTERN WAS BLIND. `\s` is not honoured here.
VALIDATED PATTERN  entry_schema *[<>=!]+ *[0-9]
  on d7db861       4 hits — manifest.cpp:347, :350, sessions.cpp:349, :419   (fires correctly)
  on 9729191       1 hit  — manifest.cpp:347  `if (entry.entry_schema < 1)`   ONLY
```

**A veto check that cannot fail certifies nothing**, and this one was about to certify K-R4(1) — the rule the whole export exists to enforce. The single remaining hit is the `< 1` validity floor that `K-R3(1)` **explicitly preserves BY NAME** and calls out as *not* a STOP. **Zero surviving parse-ceiling or supported-ceiling literals at any site, `manifest.cpp`'s own gate included.**

## 2. K's vetoes and STOPs, each at its anchor

```text
K-R4(1)  no surviving literal ceiling comparison        PASS (validated scan above)
K-R4(2)  ONE definition, no copy in the preview         PASS  manifest.hpp:15 defines it;
                                                        manifest.cpp:350 and sessions.cpp:354
                                                        CONSUME it, the latter by qualified
                                                        reference manifest::kEntrySchemaParseCeiling
K-R4(3)  never one identifier for both ceilings         PASS  two names, two namespaces,
                                                        two values (2 and 1)
K-R4(4)  no cast at any comparison site                 PASS  both constants `int`;
                                                        manifest.hpp:63 `int entry_schema{1}`
K-R3(1)  no NEW upper-boundary/discriminator class      PASS  the `< 1` floor preserved verbatim
K-R3(2)  no THIRD adjacent discriminator                PASS  exactly two at sessions.cpp:352/:354
K-R3(3)  no other export-surface change                 PASS  manifest delta is TWO lines total —
                                                        one gate rewritten, one constant added
```

## 3. The three WITHIN-FILE fences — whole-function hashing, not inspection

```text
any_sessions()            0d51b5b086a9b147   BEFORE == AFTER   byte-identical
write_manifest_summary    4e1ff402cca55896   BEFORE == AFTER   byte-identical (V11)
exit composition          exit_for_error gains EXACTLY ONE row:
                          case ErrKind::EntrySchemaSkipped: return 0;   (authorized this stage)
```

## 4. A5.2's uniform expression — correct, and its premise verified rather than assumed

```text
sessions.cpp:352-356   if (entry.entry_schema > kEntrySchemaSupportedCeiling) {
                         found->entry_schema_skipped_count += 1U + entry.children.size();
                         if (entry.entry_schema > manifest::kEntrySchemaParseCeiling) {
                           ++found->entry_schema_unparsed_count;
                         }
                       } else { ++primary_count; descendant_count += children.size(); }
```

**No branch on `children_known`** — exactly `A5.4`'s *"uniformly `entry.children.size()` … by the biconditional rather than by a branch."* That is only correct if a STUB carries no children, so I checked: **`entry.children` is assigned at `manifest.cpp:435`, below the stub early-return at `:350`.** A stub therefore contributes exactly `1 + 0` = 1, which is `A5.4`'s *"each unparsed entry contributes exactly 1 to `entry_schema_skipped_count`."* **The premise holds and the elegance is load-bearing rather than incidental.**

## 5. A4, A5.3, A5.4, and leg (p)

```text
A4      error.hpp   ErrKind::EntrySchemaSkipped added beside UnknownAgentSkipped
        error.cpp   case -> "EntrySchemaSkipped"        byte-exact wire spelling
        envelope    exit_for_error :411-412 -> return 0
        split       kind_for_row:268 reason == "entry-schema" ? EntrySchemaSkipped
                                                              : UnknownAgentSkipped
                    — `reason` was already a parameter, so no signature moved
A5.3    BOTH golden lines gain (unparsed != 0U ? "at least " : "") immediately before the
        numeral. When the ternary is empty the line is BYTE-IDENTICAL to the eeb4dd01 form
        I reconstructed and hash-compared at Stage 1b-ii — so the exact variant cannot have
        drifted, and the at-least variant inserts exactly `at least ` at the specified position
A5.4    the open-side key is emitted only under `!= 0U` — suppressed at zero, FX-J-1(p)
LEG (p) a real TEST_CASE ("threshold-parity per-agent distribution self-activates at R-4.29",
        tags [slice-e][pending-R-4.29]) whose guard is
          if (kEntrySchemaSupportedCeiling < manifest::kEntrySchemaParseCeiling) SKIP(...)
        — keyed to the TWO EXPORTED CONSTANTS exactly as dispatched, not a hidden tag and not
        an unconditional skip. It RAN and was COUNTED as a skip in both batteries (macOS 3 skips,
        Linux selection 17 cases = 16 + deferred), which is the property that stops a deferred
        leg from reporting success while asserting nothing. Reported as CONFIGURED-DEFERRED.
```

## 6. Scope and topology

One commit `9729191` over the dispatched base `d7db861`; **fourteen authorized paths, 316 insertions / 39 deletions, and the out-of-scope filter over the granted set returns NOTHING.** `src/cli/main.cpp`, `src/core/open/render.hpp`, `src/core/pack/**`, `.github/**`, harness and sealed bytes are all absent from the changed set — the OUT rows held structurally rather than by inspection.

## 7. What I did NOT verify — stated as a boundary

**The macOS and Linux batteries are theirs and I did not re-run them**, nor the twelve mutation receipts. I note that their Linux run exposed **three** of the four known overlay sentinels where the previous run exposed a different subset, they fired the exact-base control at `d7db861`, and the base reproduced the same top-level JUnit result, the same sole product failure and three sentinel failures — with the base selecting a *different* sentinel member than the head, which demonstrates the membership is environment-sensitive rather than delta-induced. **That is the shape that exonerates the delta rather than excusing it.** Removing the full four-sentinel set made head and base independently green. The stale workflow count pins remain inherited and disclosed; `.github/**` was out of scope and untouched.

## 8. Routing

**Hand-up remains BLOCKED and neither remaining gate is mine.** Routed via the orchestrator: **m-1** owns the byte-level veto over every `src/core/manifest/**` byte (the delta there is two lines: the gate rewritten to the constant, and the constant added beside `kFormatVersion`/`kManifestByteCap`); **m-3** owns the COMBINED re-review — the supported-ceiling sites, the stub discriminator, the per-agent counts and the deferred-leg disposition **TOGETHER**, per the non-ceremonial clause carried verbatim in K's lock stamp. `9729191` is local and unpublished; nothing merges; the land order binds and the early-merge narrowing stays REFUSED.

ACTIONS_GIT_REF: no product, test or fixture edit at this seat — read-only verification at `9729191` and `d7db861` via `git show`/`git diff`/`git grep`, plus whole-function SHA-256 comparison of `any_sessions()` and `write_manifest_summary`, and a control run of my own literal-scan pattern against the prior head to establish it could fire before I believed its clean result. pdc not re-read this pass; the three lock identities were re-derived at the token act `152630` and no design byte has moved since. This relay + its INDEX row ride ONE explicit-path docs-lane commit whose SHA lands after filing.
RELAY_LINT: per D-3.4 + D-3.4(a) — clock read immediately before writing (D-5.10), per-file WITH freshness, exit status checked un-piped; third arm at the active dispatch root before filing. Standing INDEX reds are the pre-existing sibling classes (line 222 s4-matrix; the `013935`/`014004` floor-pair tail inversion) — not mine.
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling-authored untracked state; this seat's writes are confined to this relay and `.relays/s4/INDEX.md`.

CARRY LIST (D-8.5):
- `.relays/s4/s4-floor-impl/RECONCILE-PLANNER-SLICE-E-SUCCESSOR-VERIFIED-ROUTE-M1-M3-20260816-165019.md` → `s4.orchestrator-planner`
- **SUCCESSOR VERIFIED at `9729191`** — one commit over `d7db861`, fourteen authorized paths, 316/39, out-of-scope filter returns NOTHING
- **A DEFECT IN MY OWN VERIFICATION, CAUGHT BY A CONTROL RUN:** my first K-R4(1) scan used `\s*[0-9]`, returned CLEAN on the candidate, and returned CLEAN on `d7db861` too — where `entry.entry_schema > 2` demonstrably exists. **A veto check that could not fail, about to certify K's central rule.** Re-run on a validated pattern (4 hits at `d7db861`, so it fires): the candidate has exactly ONE hit, `manifest.cpp:347`'s `< 1` floor, which K-R3(1) preserves BY NAME. Zero surviving ceiling literals
- K-R4(2)/(3) hold STRUCTURALLY: `kEntrySchemaParseCeiling` defined once at `manifest.hpp:15`, consumed at `manifest.cpp:350` and at `sessions.cpp:354` by QUALIFIED REFERENCE; `kEntrySchemaSupportedCeiling` separately at `sessions.hpp:17` — two names, two namespaces, values 2 and 1, never aliased. K-R4(4) no cast (both `int`). K-R3(2) exactly two discriminators. K-R3(3) manifest delta is TWO lines
- THREE FENCES by whole-function hashing: `any_sessions()` `0d51b5b0…` and pack-side `write_manifest_summary` `4e1ff402…` BYTE-IDENTICAL; `exit_for_error` gains exactly one row returning 0
- **A5.2's UNIFORM EXPRESSION VERIFIED AT ITS PREMISE, not assumed:** `1U + entry.children.size()` with no branch is only right if a stub carries no children — and `entry.children` is assigned at `manifest.cpp:435`, below the stub return at `:350`, so a stub contributes exactly 1, which is A5.4's own rule
- A4 kind/wire/exit-0/reason-split verified; A5.3's at-least prefix conditional on `unparsed != 0` in BOTH lines with the exact variant byte-identical by construction; A5.4 suppressed at zero
- LEG (p) is a real TEST_CASE guarded on the TWO EXPORTED CONSTANTS, **RAN and was COUNTED as a skip in both batteries** — the property that stops a deferred leg reporting success while asserting nothing; reported CONFIGURED-DEFERRED, never witnessed
- NOT MINE and not restated as mine: the macOS/Linux batteries and the twelve mutation receipts. Their Linux run exposed a DIFFERENT three of the four known sentinels than the base did, and the exact-base control at `d7db861` reproduced the same top-level result and sole product failure — environment-sensitive membership, which EXONERATES the delta rather than excusing it
- **ROUTED: hand-up BLOCKED on m-1's manifest veto (two-line delta) and m-3's COMBINED re-review (supported sites + stub discriminator + per-agent counts + deferred-leg disposition TOGETHER, per K's non-ceremonial clause)** — neither is mine; branch LOCAL and UNPUBLISHED; merge BLOCKED; release hold ABSOLUTE
