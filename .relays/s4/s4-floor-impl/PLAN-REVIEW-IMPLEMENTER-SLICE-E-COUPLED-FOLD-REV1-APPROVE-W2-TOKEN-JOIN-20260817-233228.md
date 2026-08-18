## PLAN-REVIEW — APPROVE rev1: S-16 is executable under the one-case fence; the invalid-ELF candidate is measurement-only, the directory shape is structurally refuted, and W-2 remains a Planner-owned pre-token stop

ROLE: Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
DISPATCH_ID: s4-floor-slice-e-coupled-fold-plan-review-rev1
PARENT_DISPATCH_ID: s4-floor-slice-e-coupled-fold-plan-rev1
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-PLANNER-SLICE-E-COUPLED-FOLD-REV1-S16-R340-13-BOUNDED-FIX-20260817-230254.md
RELATED_CONTEXT: .relays/s4/s4-floor-impl/SITREP-PLANNER-SLICE-E-REV1-LINT-DISCLOSURE-CORRECTED-W2-JOIN-DUE-20260817-230604.md
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — master already granted the bounded one-test fix; this review clears only the pair PLAN-REVIEW gate, while the Planner-owned W-2 registry join and a fresh implementation token remain mandatory before any keyboard act
DESIGN_DOC_ID: m1-addendum-L-20260816
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m1-addendum-L-10c8e8e6-lock-20260817
TARGET_DESIGN_SHA256: 10c8e8e6ed1560d8fc03e9342ed539a1554fdc0a978ba864ce6427226e0daba4
TARGET_DESIGN_COMMIT: 8c7f9281d538704419ea7142a417495eec46e8a5
SECOND_DESIGN_LOCK: m1-addendum-K-5da667fa-lock-20260816, m3-addendum-5-b8686c75-lock-20260816, m3-addendum-4-9049de44-lock-20260816
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812, m3-addendum-3-eeb4dd01-lock-20260814
CONSUMER_DESIGN_LOCK_ID: m3-addendum-3-eeb4dd01-lock-20260814
PLAN_LOCK_ID: s4-floor-slice-e-plan-20260812
FROM: s4-floor.implementer
TO: s4-floor.planner
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, m-1.planner, m-3.planner, m-2.planner
SUBJECT: APPROVE — rev1 adds one executable S-16 bind and one test path; exact invalid-ELF measurement candidate answered, directory refutation confirmed, fix-first ordering sound, and W-2 registry join remains a hard pre-token Planner obligation

PLAN_REVIEW_VERDICT: approve

## Review basis

I reviewed the exact rev1 file at coordination head `bfc7a84118ba60a80705e8f60cbfcaa1a79df599`;
its SHA-256 is `6057acc081bdf87a385b632eba1784ab135a0f55c4e2eb378a399a4d42b54556` and exact-file
relay lint passes with historical freshness disabled. I also consumed the Planner's correcting SITREP at the same
head; its SHA-256 is `31625d0125bee74cc3aaa3a365896c577734d41c40b70ba8e330bb3152fac0bf` and exact-file
lint passes. The correction is substantive evidence for gate handling: rev1's root-arm DESIGN-lineage red is real,
but it is the standing cross-repo class and W-2 makes its per-listed-identity registry join a Planner-owned
precondition to token issuance. It does not move S-16's bytes, scope, ordering, or acceptance criteria.

I independently re-hashed the locked Addendum L object at pdc commit
`8c7f9281d538704419ea7142a417495eec46e8a5`; it remains
`10c8e8e6ed1560d8fc03e9342ed539a1554fdc0a978ba864ce6427226e0daba4`, equal to the declared lock.
The carried rev0 plan re-hashes to
`1b9c6930e35ded4bffd5e34002d3101786190fc7b1dde104a2265c163aa11ec5`, equal to rev1's declared
carry-forward identity and the plan approved at `192103`.

At committed base `972919137203cb2ecb1d9f4bba8d8cd31e27befc`, the decisive byte claims are correct:

```text
probe.cpp:652-656       non-regular or no-exec-bit pin returns not_executable
probe.cpp:657           executed is assigned only after that gate
probe.cpp:720-723       plain ::posix_spawn; a nonzero spawn result maps to spawn_error
test_probe.cpp:244-257  directory control expects not_executable and no executed value
test_probe.cpp:260-278  target case plants PATH and requires executed == absolute(pinned)
test_probe.cpp:57-65    write_invalid_executable is used only by the target case
```

The implementation worktree remains at `9729191` with exactly the seven held rev0 paths modified and no
`tests/test_probe.cpp` edit yet. This review made no product, test, fixture, workflow, branch, or container act.

## Answers to the three requested questions

### 1. Exact invalid-ELF measurement candidate

Use this exact 16-byte sequence, written in binary rather than through formatted text output:

```text
7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00
```

It is the ELF magic plus an ELF64/little-endian/current-version identification record, truncated immediately
after `e_ident`. It is not a valid executable: an ELF64 header requires the remaining header fields and this file
has no type, machine, entry point, program-header table, or loadable segment. It is not intentionally valid shell
source: there is no `#!`, no text command, and the payload begins with the binary ELF marker and contains NUL
bytes rather than a leading shell word.

That static description is deliberately not promoted into a claim about what glibc or a shell will do after an
`ENOEXEC`. The plan's measurement is the authority. Run the one case in the Ubuntu 24.04 `linux/amd64` container
after the fresh token:

```text
spawn_error   -> keep the binary fixture and the common expectation
nonzero_exit  -> retain the measurement in the report, then use shape (a)'s platform-correct expectation
anything else -> STOP and route; do not invent a third shape
```

On either accepted branch, `pinned`, `requested == absolute(pinned)`, `executed == absolute(pinned)`, the planted
PATH candidate, and `raw.empty()` remain byte-present and passing. The invalid-ELF trial is a bounded measurement,
not an unmeasured mechanism assertion.

### 2. Directory refutation

I agree with the refutation. A directory fails `S_ISREG` and returns at `probe.cpp:655`, before `executed` is set
and before the spawn call. The standing directory control then confirms the consequence at
`test_probe.cpp:256`: `executed` is absent. Substituting a directory would therefore violate master's explicit
SURVIVES bar and duplicate the earlier non-executable-pin coverage while silently retiring the spawn-attempt
coverage. It is not a lawful S-16 shape.

### 3. Refutations of S-16 or A11-A15/G8-G9

None. The one-file scope extension is the exact bounded grant; the helper is sole-use by the target case; the
forbidden lines `:269/:270`, every other case, `probe.cpp`, and unrelated workflow bytes are mechanically
checkable. Fix-first is the sound order because the isolated S-16 commit repairs the already-existing Linux-red
case before the fold commit adds the held product delta. A11's preliminary container case run chooses the shape;
A15 then requires both complete platform observations and all four target-local counts at the final two-commit
head. The named fold mutants remain valid because S-16 is zero-diff on every mutant surface.

## Scope, boundary, and gate verdict

Rev1's scope is complete: rev0's eight carried rows plus `tests/test_probe.cpp`, fenced to the sole helper/case
surface. The S-16 delta has no new product boundary contract: it changes only the test oracle/fixture for the
existing probe boundary, while rev0's Addendum L producer/consumer contract and all sixteen live legs remain
unchanged. A discovered need for `src/core/support/probe.cpp`, another probe case, another path, or a third shape
is a STOP back to the Planner.

The lint correction is accepted rather than erased. Root lint still reports the standing cross-repo
DESIGN-lineage class, including rev0 and rev1; exact-file lint proves each incoming artifact's structure, not the
truth or local visibility of the pdc lock. The independently matched pdc object supplies the byte evidence here.
The Planner must perform the W-2 join per every listed identity at the registry/locked bytes and report each
element in the fresh token relay. Any mismatch means no token. This approval neither performs nor waives that
join.

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: no — one test case and carried fold scope only
- migration/backfill/destructive-write/canonical-data-repair: no — no data or migration act
- money/inventory/orders/planning/accounting/trust-critical-state: no — not present
- AI-or-automation-acts-downstream: no — no downstream automation act
- worker/scheduler/queue/retry/async-side-effect: no — no such runtime surface changes
- cross-repo/service-contract/generated-schema/shared-API-event: yes — carried pdc design locks govern the fold; the lock object was independently matched
- user-visible-control-with-materializer/downstream-consumer: no — S-16 is test-only and rev0's boundary is unchanged
- test-runtime-role-mismatch: yes — the defect is a macOS/Linux outcome divergence, so both final-head targets remain mandatory
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: no — master bounded the extension to one case; no evidence gate is skipped
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: none
- scan_presented_to_operator: no — production-risk ceremony is retained and no downgrade is proposed
- operator_reply_after_scan: none
- valid_waiver: no
WAIVED_RISK_ACCEPTANCE: none

This approval clears PLAN-REVIEW only. It grants no implementation authority. The next lawful act is the floor
Planner's W-2 join followed, only if every element matches, by a fresh pair implementation relay parented to this
review and containing the live literal token. Local macOS validation and Ubuntu 24.04 `linux/amd64` Docker remain
the two required final-head targets. GitHub Actions are not invoked. No push, PR, merge, publication, deployment,
or release is authorized; the land order, owner reviews, named objection path, and absolute release hold remain.

ACTIONS_GIT_REF: review/transport only at coordination head bfc7a84118ba60a80705e8f60cbfcaa1a79df599; locked pdc object, exact relays, committed base source, and held implementation-worktree status read; no product, test, fixture, workflow, branch, Docker, remote CI, push, PR, merge, publication, deployment, or release act; this review plus one live-EOF INDEX row ride one explicit-path docs-lane commit
RELAY_LINT: exact incoming rev1 and correction pass with --no-freshness; exact review passes with freshness before commit and will be re-verified with --no-freshness after commit; root lint's standing cross-repo DESIGN-lineage class and INDEX historical errors are preserved and disclosed, not rewritten
FINAL_GIT_STATUS_SHORT:
  M  .relays/s4/INDEX.md
  A  .relays/s4/s4-floor-impl/PLAN-REVIEW-IMPLEMENTER-SLICE-E-COUPLED-FOLD-REV1-APPROVE-W2-TOKEN-JOIN-20260817-233228.md

CARRY LIST (D-8.5):
- `.relays/s4/s4-floor-impl/PLAN-REVIEW-IMPLEMENTER-SLICE-E-COUPLED-FOLD-REV1-APPROVE-W2-TOKEN-JOIN-20260817-233228.md` -> `s4-floor.planner`
- `PLAN_REVIEW_VERDICT: approve` clears only rev1's pair PLAN-REVIEW gate; it is not an implementation token
- exact invalid-ELF measurement candidate -> `7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00`, binary, mode 0700; runtime outcome decides, not a shell-mechanism inference
- accepted branches -> `spawn_error` keeps one common expectation; `nonzero_exit` is reported then shape (a) uses the platform-correct expectation; any third outcome stops and routes
- directory shape -> structurally refuted because it returns before `executed` and spawn, violates the SURVIVES bar, and duplicates the standing directory control
- S-16 scope -> only `tests/test_probe.cpp` helper/case surface; no `probe.cpp`, other case, forbidden `:269/:270`, or unrelated workflow byte
- ordering/evidence -> separate fix commit first naming R-3.40 item (13), fold commit second; both platforms and all four target-local counts re-observed on the final head; carried mutants stand
- W-2 -> Planner must join every listed identity at registry/locked bytes before issuing the token; any mismatch means no token
- no remote Actions, push, PR, merge, publication, deployment, or release; land order, owner gates, named objection path, and absolute release hold remain
