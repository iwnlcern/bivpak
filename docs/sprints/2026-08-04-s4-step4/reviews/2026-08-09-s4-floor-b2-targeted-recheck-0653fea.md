# B2 targeted re-check — re-stacked head `0653fea` (six differing files)

Convened by s4.orchestrator-planner after master refused B2's condition-3 on provenance (the re-stack
changed B2's base old-A→rebuilt-A, so 6 of 17 files landed at end-state bytes no panel saw). Scoped
per master's `225536`: **security** over the two `install.cpp` seams; **tests** over the four test files.
The other 11 files are byte-identical to the sealed fourth-panel head `6a8ea75` and carry mechanically.
Two cold read-only lenses. **Verdict: PASS — the composition is verified at `0653fea`.**

## Security — PASS (M-4 holds FULLY at the composed install.cpp bytes, excl. deferred R-4.8)
The entire `6a8ea75→0653fea` delta in both `install.cpp` is a single swap: delete the local
`version_admission(caps, image_version)` helper, call `version_floor::admit(...)` at the same call site.
That guard is **refusal-equivalent** for both agents (same refusal set; `admit`'s extra
unparseable-`surveyed_through` branch is dead for the hard-coded agent rows, both of which parse; host
input byte-identical). The only behavioral change is the `host_version_unverified` REPORT field, which
never gates refusal/union/verify/publish → M-4-irrelevant. Refusal-equivalent guard ⇒ unchanged union ⇒
unchanged verify gating. All sub-questions clean: no token reaches an installed session, no needle
dropped, per-session verify-hits vs per-row version-refusal seam clean (no clean-sibling over-refusal),
union over ALL records incl. refused, no scan skipped, no new verify-bypass fall-through.
- **Pre-existing caveat (Minor/PLAUSIBLE, NOT composition-introduced):** in codex, a *staged +
  version-refused* sibling's artifact-derived ALIAS id enters the union only via the `prepared_sessions`
  loop, which excludes version-refused rows — so its alias id is not needled (its manifest primary/parent/
  children.original_id still are). Byte-identical at `6a8ea75` (the diff touches only the admit call), so
  it is base behavior the fourth panel already sealed, not a defect this composition creates. Routed as a
  candidate residual to master; does not gate B2.

## Tests — PASS (all four files retain falsifying power; the "un-granted change" is additive)
- **Framing correction (CONFIRMED):** no existing `/ws/proj` fixture was rewritten. The
  `/capability-origin` count rose 1→3 because a NEW composition-cohort test ("Claude rewrite verification
  preserves a sibling capability refusal", `test_adapter_claude_install.cpp:1238`) was APPENDED — verified
  new (0→1 occurrences of the title) in a B2-scope file. An additive test cannot weaken existing
  guarantees; the "un-granted re-expression" concern was a raw-count misread.
- **I-3 lock-in inversion / escaped-key kill-power INTACT** — the KEY-rewrite tests (`:502`, `:543`) are
  content-identical and still use `/ws/proj` (escaped `proj` fixture present); untouched by the
  composition.
- **Per-session verify-hits surface INTACT** (byte-identical mixed-verify test); **version-refusal
  survival PRESERVED and STRENGTHENED** (new cohort tests with genuine kill-power); the granted
  `test_sessions.cpp` re-expression is a NET GAIN (it made a previously-dead refusal branch reachable).
  F2/F3 falsifiers intact (line-shift only). The new codex admission-table test rides the production
  `version_floor::admit` seam (not a stub). Vacuity sweep cleared. `test_pack.cpp` HOME/env hermeticity
  engages (ScopedEnv overrides, not CWD-dependent).

## Disposition
Both lenses PASS. B2 `0653fea` composed bytes verified: 11 files carry mechanically (byte-identical to
`6a8ea75`) + 6 re-checked (security PASS on the 2 install.cpp, tests PASS on the 4 test files). Condition-1
provenance for the composed head is now complete. B2 handed up FRESH for condition-3; both C (met) + B2
route to the operator paired. Pre-existing codex alias caveat → candidate residual to master (not a
blocker).
