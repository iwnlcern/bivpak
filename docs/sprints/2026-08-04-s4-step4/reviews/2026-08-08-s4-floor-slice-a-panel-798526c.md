# Slice A team-of-5 adversarial panel — record of record

**Target:** PR #21, branch `s4-floor/a-floor-core`, exact head
`798526c5c68c4251cc088bcf922fbee798ed8b79`, parent `ff63e521d8ae5229a831aab8718a3fa58205f40f`
(one commit, 24 paths). The Addendum-7 VERSION FLOOR slice.
**Why now:** slice A had E1/E2 verification + one independent delta review + local-green,
but NEVER an adversarial panel (the `091452` "panel requested" was overtaken by the
publication question and the C/B2 work). Convened before any merge hand-up.
**Method:** five cold read-only lenses over committed bytes; correctness and security built
the SHA and reproduced findings by execution; planner byte-verified the Critical and the
I-1 by-design ruling.
**Aggregate verdict:** MUST-FIX (one Critical, both legs).

## Per-lens verdicts
- performance: approve (1 Minor)
- idiom: approve (2 Important, 7 Minor)
- security: must-fix (I-2/I-3 real; I-1 by-design)
- tests: must-fix (F1/F2, 2 more Important, minors)
- correctness: must-fix (1 Critical, 1 Important, 5 Minor) — executed both legs

## Confirmed blockers

| ID | Sev | Lenses | Site @ SHA | One-line |
|---|---|---|---|---|
| A-BL1 | Critical | correctness C (executed both legs) + security I-2/I-3 | codex install.cpp:433 `result.sessions.clear()`; claude install.cpp:574-579 | the rewrite-verify cohort gate destroys the version-refusal carrier — codex DELETES the refused row, claude RELABELS it `containment_refused`; the write-batch gates were taught to preserve it (the "No clear()" comment), the verify-hits gate was not |
| A-BL2 | Important | tests F1 | schemas + adapter.hpp wire_verdict + fixtures | `readable-newer-than-survey` never schema-validated → a real `biv open --json` on a newer-than-survey host emits an envelope violating the published v1 schema, all tests green |
| A-BL3 | Important | tests F2 | tests/test_sessions.cpp:626-643 | dead `else` branch (table flipped all-accepted) carrying `reason=="not-validated"`, which shipped code can no longer produce — assertion that can't fail because it can't run |
| A-BL4 | Important | tests F3/F4 | pack.cpp:578; version_admission both legs | pack fail-open (unknown version → packed) and the host-unparseable admission branch are both untested |
| A-BL5 | Important | correctness | render.cpp:182-196 | pre-consent disclosure prints "readable; minimum…" for a store-absent agent whose sessions end exit 2 — keys on probe.outcome, not caps.verdict; regressed from a warning to a reassurance |
| A-BL6 | Important | idiom I-2 / tests F4 | claude install.cpp:382-399 ≡ codex install.cpp:250-267 | the admission conjunction is duplicated byte-for-byte at both legs (only the primitives moved to version_floor); coverage doesn't transfer and A-BL1's fix must land twice — move the conjunction into `version_floor::admit` |

## By-design, NOT a defect (settled by spec — no route-up)
Security I-1 (the floor's `min_line` never gates install; a below-MIN host or a crafted
below-MIN archive is admitted at open) is CORRECT by design. Plan line 158 ("diff NOT
widened into below-MIN/non-version refusals") + Task 6 (pack-side MIN omit), and the
correctness lens cites the exact clause: ADDENDUM-7 §A7.4 M4-VF-N1 — "the pack-MIN is an
honest-packer disposition, never an open-side admission invariant." `min_line` appears only
at `pack.cpp:586` (omit) and `render.cpp:190` (display); no install site reads it. Recorded
so it is not re-raised.

## Minor / residual
Mirror gate blind to the agent→row binding (idiom I-1, tests M1, correctness M-1 — THREE
confirmations, all note `test_render.cpp:282-284` mitigates by asserting per-agent floor
values; tests lens proved the swap reds 4 suite cases, so it's latent-only, reachable via a
deliberate new-adapter change; the coverage is incidental to far-apart floor values).
Recommend binding the checker to `row_for` or dropping the `if name in _PRODUCT_ROWS`
filter. Plus: harness mirror arm decorative; `Warning.artifact` carries prose; mapper
fixture uses `reason=nullopt` where adapters ship `not-validated`; host-side parse failure
labeled a basis fault (latent); two `valid_utf8` under one name.

## Checked-clean (execution-verified across lenses)
Grammar strictly before ordering (both legs, byte-identical); untrusted version parsing safe
(30+ adversarial inputs under ASan/UBSan — overflow/NUL/injection all fail-closed, 9-digit
+ 4-component caps); gate fails closed on unreadable host at both layers; allowlist deletion
introduces no accept-where-refused path and REMOVED a prior untrusted-manifest fail-open;
exit mapping correct (new reasons ride AgentNotValidatedFailed → exit 2); A2 blob recapture
hash-matches (both schemas); C++/Python grammars match exactly (bounds, suffix, boundary —
no differential); pack MIN omit-loud excludes from every collection (no member collision);
whole-output single-token parse deliberate per §A7.6.

## Gate
Slice-A fold folds A-BL1..A-BL6 (all in-universe) at the one-commit head; A-BL1 gets a
cohort test (version-refusal + verify-hits sibling → both rows preserved). No routed
authority items. The amended head owes a targeted re-check (A-BL1 changes report behavior on
the failure path; not a full re-panel unless blast radius grows). Merge/release the
operator's; release hold ABSOLUTE.
