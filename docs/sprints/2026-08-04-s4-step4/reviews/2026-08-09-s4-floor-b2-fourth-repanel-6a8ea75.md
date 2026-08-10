# B2 fourth targeted re-panel — head `6a8ea75`, cumulative window `ec9a2db..6a8ea75`

Convened by s4.orchestrator-planner (3 cold read-only lenses: security, correctness, tests) after the
I-3 + F2 + F3 + TIMEOUT-600 amend. M-4 under UNION-SCOPE acceptance (bare home/username-prefix deferred
to R-4.8, out of scope). **Verdict: PASSES — M-4 holds FULLY; B2 bar-ready on its merits.** All
load-bearing claims byte-verified by the orchestrator at `6a8ea75`.

## Amend byte-verification (orchestrator)
Scope exactly the four authorized paths (rewrite_common.cpp, codex/install.cpp, both test files); one
commit over `ec9a2db`; no `.github`/`manifest.`. I-3 symmetric closure CONFIRMED: all three
`JsonValueRewriter` sites pass `decode_keys=true` (:841 jsonl-rewrite, :923 whole-doc, :1051 verify_scan —
the previously key-blind arm). B2 stacked on slice C (`ec9a2db`); merges AFTER C per the operator's
C→B2-immediate election (C not yet in main).

## Lens results — all PASS

### Security — PASS
M-4 HOLDS FULLY (excluding deferred R-4.8). I-3 CONFIRMED CLOSED on all three arms: `key_string`
decodes keys, pushes the decoded form for scanning, rewrites under the pair-set, re-encodes — escaped/
`\uXXXX`/doubled-backslash key spellings normalized before match; no production `decode_keys=false` path;
fail-closed intact. No new leak; no weakened mechanism; amend net-positive. One Minor/theoretical
(substring `replace_all`, not reachable — UUIDs equal-length, none a substring of a distinct one).

### Correctness — PASS (amend correct, strict improvement)
I-3 key rewrite deterministic/boundary-safe (inherits the sound value path); F2 parent id-map correct
(maps child's stored parent to the parent's installed primary; self-parent/empty/collision cases safe;
forward-reference safe); no regression to precedence/decode/torn-tail/union/store_root. F3 test-only.

### Tests — PASS
Lock-in inversion GENUINE with kill power at unit + install level (escaped-key fixture only yields the
rewritten key via decode→match→rewrite→re-encode; verify-side twin confirms decoded-key detection in
`verify_scan`); `key-must-not-change` survives only as a value. F3 falsifier GENUINE (child id reaches
the union only via the manifest-wide loop over all records incl. the version-refused origin; removal →
RED). F2 de-masked fixture GENUINE (real `parent_thread_id`, exercises in-image→rewrite, double-anchored
RED). No vacuous/source-text assertions introduced.

## The graded cell — not-in-image Codex parent refusal (converged across all three lenses)
An admitted Codex session whose own `parent_thread_id` references a NOT-in-image (uncollected) parent:
the union inserts the parent id (codex/install.cpp:485-486) but the F2 rewrite loop (:463-471) only maps
in-image parents, so the id is un-rewritten in the session's own bytes → `verify_scan` hit → the session
refuses (`verify-hits`/`origin_id`).
- **Reachability: YES** (subset-pack a child whose parent file was cleaned up / not a winner — traced
  collect→pack→install).
- **Provenance (byte-grounded vs the third panel):** at `ec9a2db` the parent id was NOT in the union →
  the orphan session silently **LEAKED** the parent id (pre-B2 M-4 breach). B2's union-widening added it,
  turning the leak into a fail-closed **REFUSE**. So B2 converts a leak into a safe refusal — a strict
  M-4 improvement — at a usability cost (orphan sessions refuse). NOT introduced by the fourth amend
  (byte-identical orphan behavior at f9675ea); a consequence of B2's leak-closure.
- **Security: refuse is CORRECT** — the parent id is a genuine origin id in the needle set; fail-open
  would re-leak it. **Correctness: MEDIUM** real reachable drop of legitimate orphan data, fail-closed.
  **Tests: untested by design (LOW), fail-closed-safe.**
- **Not a security or amend defect. Does NOT block B2.** It is a usability limitation that is the cost of
  closing the leak; admitting orphans would require prepare-time scrubbing of the dangling parent
  reference (a separate design change). The DEFINITION (accept refuse-by-default + track residual, or
  elect prepare-time scrubbing) is the family-invariant owner's (master's) call — routed up.

## Disposition
- B2 fourth re-panel PASSES → bar-ready on merits (condition 1). Handed up for condition-3 (merges after C).
- The orphan-parent refusal → routed UP to master: register as a RESIDUAL (usability: orphan sessions
  refuse) + rule the definition. Recommend accept refuse-by-default (fail-closed, strict improvement over
  the pre-B2 leak) + track; elect prepare-time scrubbing only as separate work if orphan usability is
  wanted. Does not block B2.
- Tests LOW residual (untested orphan installed-session path) folded into the same residual note.
