## SITREP — T1 tidy repair VERIFIED at my seat at `00c06d9`: the RED→GREEN transition is proven from the RAW analyzer evidence, not from my own gate's summary; and the mid-flight gate correction is AUDITED and confirmed narrowing-preserving, because a granted "correct the parser" is exactly how a gate gets disabled

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-matrix-t1-tidy-fix-verified
PARENT_DISPATCH_ID: s4-matrix-t1-tidy-fix-impl
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-T1-TIDY-FIX-COMPLETE-20260821-052056.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/IMPL-PLANNER-T1-TIDY-FIX-DISPATCH-20260821-035403.md; .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-T1-LINUX-REDS-RULED-TIDY-FIX-AUTHORIZED-IN-LANE-HARNESS-RESIDUAL-UP-20260820-201613.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — one ruling: whether Wave-A resumes at the fixed head (T2/T3/T4 + the `compare.py` composition) and whether a Stage-3 panel is convened on T1 first. `201613`'s exit condition (Linux tidy leg GREEN at the fixed head) is MET. Nothing merged, pushed, published, or PR-mutated; the fixed head is LOCAL and UNPUBLISHED; the release hold is ABSOLUTE
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: frozen base `a02a65b9ea2c1ce6ff149a914c50f965531d443d`; pre-repair T1 `76638a00332fc9dd674f0cf952e28be4fa0507e8`; tests-only `b61e761f530ed86e4f54b65a5b3259b5a5d03e3b`; FIXED HEAD `00c06d93146f13c0f8518b0893d2d944f0bd8231`
FROM: s4-matrix.planner
TO: s4.orchestrator-planner
CC: operator, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer, s4-matrix.implementer
SUBJECT: SITREP — T1 tidy fix verified independently at `00c06d9`; gate correction audited on 7 arms and confirmed not a disable; `201613` exit condition met; resumption ruling requested

## 1. Verdict

**VERIFIED.** Every load-bearing claim in `052056` re-derived at my seat rather than
accepted on report. The defect that blocked T1 is gone, and it is gone for the reason
claimed.

## 2. Scope and product bytes

```text
git diff --name-status 76638a0..00c06d9    ->  M src/core/support/subprocess.cpp
                                               M tests/test_subprocess.cpp        (exactly the two dispatched paths)
git diff --quiet 76638a0 b61e761 -- src/   ->  exit 0   S1 is PROVABLY tests-only
subprocess.cpp @76638a0                    ->  9af9d55c…  (the approved pre-edit anchor)
subprocess.cpp @00c06d9                    ->  b30c2949…  (differs; matches the SITREP)
worktree clean at 00c06d9, HEAD unchanged
```

The **entire** production diff is the approved edit and nothing else: three
`bytes_{&bytes}` / `output_incomplete_{&output_incomplete}` initializations, the three
dereference sites in `write()`, the two member declarations, and `buffer{}` at `:220`.
Every arithmetic and control expression is otherwise character-identical. `reserve` appears
only at `:521`/`:529` for `argv`/`env` — both pre-existing and outside `ByteCapture::write`,
so `76638a0`'s geometric-growth repair stands.

The three test cases match the frozen vectors exactly, including
`CHECK_FALSE(result->output_incomplete)` on the both-ample **negative discriminator**; the
pre-existing both-capped case is untouched.

## 3. The RED→GREEN transition, read from the RAW evidence

I did not take this from the gate's own printed verdict — the gate is my instrument, so its
summary is not independent of me. From `s3-tidy.log` and the JUnit directly:

```text
S3  subprocess.cpp:136:27: error: member 'bytes_' … is a reference [cppcoreguidelines-avoid-const-or-ref-data-members,-warnings-as-errors]
    subprocess.cpp:138:9:  error: member 'output_incomplete_' … is a reference [cppcoreguidelines-avoid-const-or-ref-data-members,-warnings-as-errors]
    subprocess.cpp:220:3:  error: uninitialized record type: 'buffer'          [cppcoreguidelines-pro-type-member-init,-warnings-as-errors]
    JUnit: cases=1  status='fail'  children=['failure','properties','system-out']

S5  subprocess.cpp findings in the log: 0
    JUnit: cases=1  status='run'   children=['properties','system-out']   (no failure/error)
```

Per-phase source anchors bind each half to the right bytes: S2/S3 = `9af9d55c…`
(pre-edit), S5/S5mac = `b30c2949…` (fixed). `RECEIPTS.sha256` self-hashes to `b69a72ba…`
and `shasum -c` re-verifies **22/22 OK** at my seat.

## 4. The gate correction — audited, because this is where a gate gets quietly disabled

The Implementer changed a gate mid-flight. That is the single highest-risk act in this
SITREP: a granted "correct the parser" is precisely the shape by which an assertion becomes
a no-op. So I re-ran the negatives myself against the **corrected** gate, with the real
comma suffix applied to every fixture — a control that only matters if you assume the fix
might have opened an evasion:

```text
MUST-BE-YES  status=fail + ',-warnings-as-errors' suffix, rc=8      exit 0  gate OK
MUST-BE-YES  status=run  + suffix                                   exit 0  gate OK
MUST-BE-NO   1. ctest exit 0                                        exit 1  refused
MUST-BE-NO   2. green row (no failure child)                        exit 1  refused
MUST-BE-NO   3. skipped row (status notrun)                         exit 1  refused
MUST-BE-NO   4. FOURTH finding, comma-suffixed                      exit 1  refused
MUST-BE-NO   5. SWAPPED check-id, comma-suffixed                    exit 1  refused
MUST-BE-NO   6. status=fail but NO failure child   (my arm)         exit 1  refused
MUST-BE-NO   7. unexpected status 'disabled'       (my arm)         exit 1  refused
```

Arms 6 and 7 are mine, aimed at exactly what widening `status` could have opened. Both
hold. **The S5 GREEN gate is byte-identical to the version I approved** — it was not
touched, so the green half was never loosened. The correction is narrowing-preserving.

**And both gate defects were MINE, not theirs.** My rev6 predicate required
`status == 'run'`, but CTest records an executed *failed* row as `status="fail"`; and my
synthetic fixture used a bare `[check-id]`, while clang-22 under `WarningsAsErrors` emits
`[check-id,-warnings-as-errors]`. That is the residual I disclosed in rev5–rev8, and it
behaved exactly as designed: **fail-closed**, caught at S3, corrected on the gate side, with
the product bytes untouched and the raw first-attempt evidence retained at
`.superpowers/sdd/t1-tidy-BnRABAzv`. The Implementer triaged it correctly and did not waive
a finding to make it pass. The disclosure was worth writing; the fixture being synthetic was
the cost of my not having a real log, and that cost was one cycle.

One small correction to my own plan text, no action needed: rev4's prose asked the analyzer
row be observed covering "29 of 29 sources". That count is not printed in any greppable
form in the retained logs. It does not matter — the JUnit predicate (row present exactly
once, not skipped/notrun, failure-child present at S3 and absent at S5) is strictly stronger
than a prose count, and it is what actually ran.

## 5. Two flakiness observations now stand in this lane

```text
harness-selftest (Linux)  pre-existing at the frozen base, candidate-neutral by byte-identity,
                          membership nondeterministic (0-3 of the same three tests) - ruled a
                          residual at 201613, registration owed by master
harness-e2 (macOS)        NEW, transient: two scenarios (open-consent-yes, open-store-locked)
                          timed out at the pinned Codex stand-in's 2000ms version-probe budget,
                          on the identical pre-edit binary that had just passed; each passed
                          when rerun alone, and both canonical macOS selections passed in full
```

The Implementer handled the second correctly — retained the failing root
(`.superpowers/sdd/t1-tidy-ufKPP5z5`) rather than erasing it, changed no code and no timeout,
and did not fold it into the accepted receipts. I am **not** treating it as a T1 finding:
it reproduced on pre-edit bytes. But two independently flaky rows is a pattern, and a
2000ms budget that fails under load is a thin margin. **Recommend both be registered as
residuals** — that registry is master's to write, so I am routing rather than filing.

## 6. State, owed, and the ruling I need

`201613`'s exit condition — *"re-run the Linux tidy leg to GREEN at the fixed head"* — is
**MET**, and the Linux subprocess row also passes at the fixed head.

```text
OWED   Linux `nonzero_exit` contract, still unclaimed on the fixed head (the aggregate
       subprocess CTest receipt does NOT claim it, correctly)
ROUTED count-gate SHAPE finding, unchanged since 174238 (#16 splits the suite into three
       binaries while the gate reads one)
HELD   T2, T3, T4, and the `compare.py` composition with its test obligation
LOCAL  both commits and the branch are LOCAL and UNPUBLISHED; PR #16 remains superseded
       per the operator's arm-(ii) disposition
```

**The ruling I need:** whether Wave-A resumes now at `00c06d9` — and whether a Stage-3
panel is convened on T1's fixed head before T2/T3/T4 restart, or after the stack is
reconstructed. I have not started either, because the `compare.py` composition is mine and
its base moves with whatever you rule.

Nothing merged, pushed, re-based onto a published ref, PR-mutated, or published; no remote
CI; no `.github` edit; the schema act remains F+G-fenced. Merge != push != release; the
release hold is ABSOLUTE.

ACTIONS_GIT_REF: read-only verification at my seat — `git log`/`diff --name-status`/`diff --quiet`/`show` over `76638a0..00c06d9` in the candidate worktree; `shasum -a 256` of both source revisions; `shasum -a 256 -c RECEIPTS.sha256` (22/22 OK) in the canonical evidence root; direct reads of `s3-tidy.log`, `s5-tidy.log`, and both JUnit XMLs; and nine re-runs of the corrected S3 gate against fixtures I built in the session scratchpad. NO ref created or moved, NO source/test/workflow edit, NO container started, NO merge, push, PR mutation, or remote CI. Docs lane: this relay + its INDEX row ride ONE explicit-path commit.
FINAL_GIT_STATUS_SHORT: this relay and its INDEX row are this seat's only working-tree delta at commit time; the shared checkout carries sibling-authored untracked paths, preserved and unclaimed

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/SITREP-PLANNER-T1-TIDY-FIX-VERIFIED-GATE-CORRECTION-AUDITED-20260821-135024.md` → TO `s4.orchestrator-planner`
- T1 TIDY FIX VERIFIED at `00c06d9`: scope exactly the two dispatched paths; S1 PROVABLY tests-only (`git diff --quiet -- src/` exit 0); the entire production diff is the approved edit and nothing else; no `reserve` in `ByteCapture::write`; the three test vectors exact including the both-ample NEGATIVE discriminator; source `9af9d55c…` → `b30c2949…`
- RED→GREEN read from the RAW evidence, not the gate's own verdict: S3 log carries exactly the three findings and its JUnit row is `status='fail'` with a failure child; S5 log carries ZERO `subprocess.cpp` findings and its row is `status='run'` with none. Per-phase source anchors bind each half; `RECEIPTS.sha256` re-verified 22/22 OK at my seat
- GATE CORRECTION AUDITED on 9 arms with the real comma suffix applied — all five original negatives still refused, plus two arms of MINE aimed at what widening `status` could open (fail-without-failure-child, unexpected status); the S5 GREEN gate is BYTE-IDENTICAL to the approved version. The correction is narrowing-preserving, NOT a disable
- BOTH GATE DEFECTS WERE MINE: my rev6 required `status == 'run'` but CTest records an executed FAILED row as `status="fail"`; and my synthetic fixture used a bare `[check-id]` while clang-22 under `WarningsAsErrors` emits `[check-id,-warnings-as-errors]`. The disclosed residual fired exactly as designed — fail-closed, corrected gate-side, product untouched, raw first attempt retained at `t1-tidy-BnRABAzv`. Cost: one cycle, and it was the price of a synthetic fixture
- SELF-CORRECTION, no action needed: rev4's prose "29 of 29 sources" is not printed in greppable form; the JUnit predicate that actually ran is strictly stronger than that count
- TWO FLAKY ROWS now stand: `harness-selftest` (Linux, pre-existing, ruled a residual at `201613`) and a NEW transient macOS `harness-e2` — two scenarios timing out at the pinned Codex stand-in's 2000ms version-probe budget on PRE-EDIT bytes, each passing when rerun alone. NOT a T1 finding; failing root retained, no code or timeout changed. RECOMMEND both registered as residuals — master's registry, so ROUTED not filed
- `201613` EXIT CONDITION MET (Linux tidy leg GREEN at the fixed head; Linux subprocess row also green). OWED: Linux `nonzero_exit`, correctly NOT claimed by the aggregate subprocess receipt. ROUTED: the count-gate SHAPE finding, unchanged. HELD: T2/T3/T4 and the `compare.py` composition
- RULING REQUESTED: resume Wave-A at `00c06d9`, and whether a Stage-3 panel convenes on T1's fixed head before or after the stack is reconstructed. Both commits LOCAL and UNPUBLISHED; schema F+G-fenced; merge != push != release; release hold ABSOLUTE
