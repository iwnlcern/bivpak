## REVIEW-FOLD — Slice A team-of-5 panel at 798526c: MUST-FIX. One Critical (the rewrite-verify cohort gate destroys the version-refusal carrier on BOTH legs, reproduced by execution) + five Importants, all in-universe. No routed authority items — the below-MIN-at-open question is settled by spec (§A7.4). The amended head owes a targeted re-check.

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-floor-impl-2-a-review-fold-2
PARENT_DISPATCH_ID: s4-floor-impl-2-a-local-linux-ci
RUN_ID: s4
TASK_ID: A
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: yes — a must-fix panel result; you write FOLD_SCOPE before any edit; the amended head owes a targeted re-check + the merge-readiness confirmation the orchestrator is holding for; merge/release the operator's; the release hold is ABSOLUTE
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/SITREP-IMPLEMENTER-SLICE-A-LOCAL-LINUX-CI-20260806-160811.md
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: s4.orchestrator-planner, operator
SUBJECT: MUST-FIX — Slice A finally paneled at 798526c (it never was); one Critical reproduced on both legs by the correctness + security lenses, re-read at the bytes at this seat

Slice A had E1/E2 verification + one delta review + local-green but NEVER an adversarial
panel; the team-of-5 ran now, at exact `798526c`. Full record:
`docs/sprints/2026-08-04-s4-step4/reviews/2026-08-08-s4-floor-slice-a-panel-798526c.md`.
perf + idiom approve; security/tests/correctness must-fix. I byte-verified the Critical and
the by-design ruling; correctness and security built the SHA and reproduced the Critical.

## BLOCKERS

**A-BL1 [CRITICAL — correctness (executed both legs) + security I-2/I-3] — the rewrite-verify cohort gate destroys the version-refusal carrier on BOTH legs.**
Slice A's three cohort-failure gates were fixed inconsistently: the WRITE-BATCH gates were
taught to preserve pre-existing per-session refusals (codex `install.cpp:472` — the "No
clear(): capability-refusal rows never entered prepared_sessions or the batch, and clearing
here deleted them from the report" comment; claude `:588`/`:619`/`:634` guard on
`refusal_reason.has_value()`), but the REWRITE-VERIFY gate was not — the one gate the
version refusal must survive.
- **Codex DELETES the row:** version refusals are pushed straight into `result.sessions`
  (`install.cpp:347-355`); the verify-hits branch calls `result.sessions.clear()`
  (`:433`) before fanning cohort containment rows, and at that point `result.sessions`
  holds ONLY the refusal rows — the clear is purely destructive. Reproduced: cohort of
  {basis-unorderable refusal, admitted+verify-hit} → 1 row out, the refused session
  vanishes from `InstallResult`, and `run_session_leg` (`sessions.cpp:305`, no cross-check
  against `eligible`) emits no row for it. `biv open` reports one session for a two-session
  hostile image — silent per-session report loss on exactly the population this gate exists
  for.
- **Claude RELABELS the row:** the verify-hits branch (`install.cpp:574-579`) iterates ALL
  of `prepared` — including refusal-flagged sessions — and overwrites each with
  `containment_refused`/`rewrite_verify_failed`, missing the
  `if (session.refusal_reason.has_value()) continue;` its two siblings have. The typed
  version distinction ADDENDUM-7 §A7.7 requires to reach the m-3 boundary is lost.
FIX: add the `refusal_reason.has_value()` guard to the rewrite-verify gate on the claude
leg (`:574`), and on codex remove the `:433` clear() (or re-push the refusal rows after),
matching the write-batch gates. Add a cohort test — version-refusal + verify-hits sibling →
BOTH rows preserved with correct reasons (no test currently puts the two in one cohort;
that is why the suite is green).

**A-BL2 [Important — tests F1] — `readable-newer-than-survey` is never validated against the schema.**
The one wire spelling this slice introduced: `schemas/biv-json-envelope.v1.schema.json:110`
enumerates it, `adapter.hpp wire_verdict()` emits it, nothing crosses them. Both schema
ctests miss it (their fixtures carry only `readable`/`unreadable`/`absent`), so a real
`biv open --json` on a host running an above-survey agent (codex 0.300.0) emits an envelope
that VIOLATES the published v1 schema while every test stays green. FIX: add a third agent
row with `"capabilities_verdict": "readable-newer-than-survey"` to
`tests/fixtures/probe-envelope-v1.json`.

**A-BL3 [Important — tests F2] — dead `else` branch carrying a now-false assertion.**
`tests/test_sessions.cpp:626-643`: the table at `:560` was flipped so all five
`accepted` fields are `true`, so `if (version_case.accepted)`'s else never runs; its seven
CHECKs never execute, and `:636` asserts `row.reason == "not-validated"`, which shipped code
can no longer produce (`sessions.cpp:325-334` overwrites reason with the hyphenated
spellings). An assertion that cannot fail because it cannot run. FIX: give the table a real
REFUSING row (image version above the probed host) so the E2E real-adapter refusal path gets
an end-to-end case — which also exercises A-BL1 end-to-end. (Also delete the now-unreachable
`reason=="not-validated"` fallback at `sessions.cpp:75`.)

**A-BL4 [Important — tests F3/F4] — untested fail-open + untested defensive branch.**
pack.cpp:578's gate packs (does not omit) an image version that fails `parse_grammar`
(reachable: `agent_version_at_pack="unknown"`); no pack test exercises it. And
`version_admission`'s host-unparseable branch (codex `:256-259` / claude `:388-391`) has no
test in either adapter (every `from_probe` in the tree passes a grammatical version). FIX:
add a pack `Case` with `version="unknown"` (keep-test at `:238`) and a host-unparseable
admission case driven through the `InstallTarget` seam.

**A-BL5 [Important — correctness] — pre-consent disclosure says "readable" for an agent that will be refused.**
`render.cpp:182-196` prints `(readable; minimum X; surveyed through Y)` whenever
`probe.outcome == ok && probe.parsed`, ignoring `caps.verdict()`. But `probe_capabilities`
sets `Verdict::absent` when the store is missing despite a good probe, so a host with codex
on PATH but no `~/.codex` is disclosed "readable; minimum 0.142" and then consent-yes
returns `agent_not_validated_failed`/`store-absent`/exit 2. Regressed from a warning to a
reassurance. FIX: gate the disclosure on `caps.verdict()`, not just probe outcome.

**A-BL6 [Important — idiom I-2 / tests F4] — the admission conjunction is duplicated byte-for-byte at both legs.**
`version_admission` + `struct VersionAdmission` are 24 identical lines in both `install.cpp`
files; only the PRIMITIVES moved to `version_floor`. The conjunction — grammar-before-
ordering, which reason wins, the `host_version_unverified` coupling — is the thing whose
divergence would produce two different products, and it was copied. FIX: move the whole
conjunction into `version_floor::admit(agent_id, host, image)` returning the
admitted/unverified/reason triple; both legs call it with their own id (as `row_for` already
parameterizes). This also makes A-BL1's fix land ONCE instead of twice and lets coverage
transfer between adapters.

## BY-DESIGN — settled by spec, NOT folded, NOT routed
Security I-1 (the floor's `min_line` never gates install; below-MIN host/crafted-archive
admitted at open) is CORRECT by design. Plan line 158 ("diff NOT widened into below-MIN
refusals") + Task 6 (pack-side MIN omit), and the correctness lens cites ADDENDUM-7 §A7.4
M4-VF-N1: "the pack-MIN is an honest-packer disposition, never an open-side admission
invariant." `min_line` appears only at `pack.cpp:586` and `render.cpp:190`. No action.

## Minors / residuals (discretion)
- Mirror gate blind to the agent→row binding (idiom I-1, tests M1, correctness M-1 — three
  confirmations; `test_render.cpp:282-284` mitigates by asserting per-agent floor values, so
  latent-only, reachable via a deliberate new-adapter change). Recommend binding the checker
  to `row_for` or dropping the `if name in _PRODUCT_ROWS` filter.
- Grammar-drift residual: the C++ `parse_grammar` and Python `_VERSION_GRAMMAR` are two
  implementations of one spec that AGREE today (correctness brute-forced 79,712 inputs, 0
  mismatches) with nothing holding them there; the mirror compares floor values, not grammar
  behavior. Standing exposure — record in RESIDUALS, not a slice-A blocker.
- `Warning.artifact` carries a prose sentence (schema `detail` is the right field, unused);
  mapper fixture uses `reason=nullopt` where adapters ship `not-validated`; host-side parse
  failure labeled a basis fault (latent); two `valid_utf8` under one name; idiom M-1..M-8.

## Fold discipline + gate
Write FOLD_SCOPE `all-in` before any edit; one-commit law + subject preserved; A3 re-fires
only if an anchored file changes (slice A touches none). Host + local Ubuntu 24.04 amd64
Docker suite (Actions unused, per CI-leg (a) — remote red is not a blocker); republish PR
#21. A-BL1 changes report behavior on the failure path, so the amended head owes a TARGETED
RE-CHECK from me (not a full re-panel unless blast radius grows); on that, I give the
orchestrator the merge-ready confirmation it is holding slice A's condition-3 for.
Merge/release the operator's.

ACTIONS_GIT_REF: no product/test edits at this seat — review relay; the five lens reviews were read-only/execution at 798526c and my verification read-only git plumbing; this relay + its INDEX row ride one explicit-path docs-lane commit whose SHA lands in history after filing
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to the two docs-lane paths named above

CARRY LIST:
- `.relays/s4/s4-floor-impl/REVIEW-FOLD-PLANNER-SLICE-A-PANEL-DISPATCH-20260808-210909.md` → `s4-floor.implementer`
- A-BL1..A-BL6 (all in-universe) → implementer fold at the amended one-commit head; A-BL1 is the Critical
- security I-1 below-MIN-at-open → by-design per §A7.4, recorded not folded
- amended head → targeted re-check by me, then slice-A merge-ready confirmation to the orchestrator (condition-3 held); PR #21 at 798526c meanwhile; merge/release the operator's, hold ABSOLUTE
