# Slice B2 fold — targeted re-panel record of record

**Target:** PR #23 amended head `d6cceba9321d693d8e302e89b796ca159a0f8f66` (fold of the
first B2 panel), one commit over `ec9a2db`, 15 paths (13 + granted
`src/adapters/rewrite_common.{hpp,cpp}`).
**Scope:** master-endorsed targeted re-panel on the rewrite/verify surface — security,
correctness, tests — cold lenses, with **m-4** on the containment invariant under the
per-session refusal radius (master's B2-1 ruling gated the per-session radius on this
re-panel confirming scan soundness).
**Method:** all three lenses executed code (security compiled+ran the verifiers;
correctness built the binary and ran the suite; tests ran the mirror/verifier probes);
planner byte-verified all three Criticals independently.
**Aggregate verdict:** MUST-FIX — **M-4 DOES NOT HOLD.** A second fold cycle is owed, and
the resulting head owes ANOTHER targeted re-panel (verify semantics change again).

## Confirmed blockers (second fold cycle)

| ID | Sev | Lenses | Site @ SHA | One-line |
|---|---|---|---|---|
| B2C2-1 | Critical | security C1 + tests C-1 + correctness C-1 (all executed) | rewrite_common.cpp:864→712→676; claude install.cpp:720; inventory claude_code.cpp:321 | never_rewrite scan is raw-byte, blind to JSON escaping; the only never_rewrite class is `.meta.json` (JSON), so posix `\/`, `\uXXXX`, and unavoidable wsl/windows `C:\\` origins publish to the store with origin_path_hits=0 |
| B2C2-2 | Critical (split) | security C2 | claude install.cpp:651-656/689-693 | needle set is the session's OWN origins/ids only — not the image union, no username/home; M-4 as stated fails and radius-widening can't fix it |
| B2C2-3 | Critical (test-integrity) | tests C-2 | tests/test_pack.cpp nine staged sites | HOME unpinned → tests read the operator's real ~/.claude, ~/.codex → the guard-deletion falsifier is dead everywhere but a bare container, and they scan the operator's live sessions |
| B2C2-4 | Important | correctness I-1 | claude_code.cpp:253 collect vs install.cpp:180-192 | collector packs every file, installer admits only 3 suffixes → cohort-wide `containment_refused` with no detail; staged path already enforces the 3 classes |
| B2C2-5 | Important | correctness I-2 | claude_code.cpp:157 / codex.cpp:215 branch 4; pack.cpp:606 | torn-tail branch 4 (retain invalid non-live tail) is silently un-installable — pack emits no fact, install refuses `undecodable_line`; claude DEFAULTS to this branch (live=false), codex to branch 3 |
| B2C2-6 | Important | tests I-1 + I-2 | test_adapter_claude_install.cpp:2108; codex_collect:535 twin | raw-text rewrite engine has no output-observing test (passes under `return input`); whole-file torn-tail branch untested on the claude copy |

## Routed above the pair
- **B2C2-2 authority (M-4 invariant scope):** the in-universe fix (widen the needle set to
  the IMAGE UNION of all origin spellings + all origin ids) folds; the question of whether
  the invariant requires needling the bare packer home/username, or is explicitly narrowed
  to the origin-path/id union, is master's — routed with security's narrowest-provable
  statement of what the code actually guarantees.
- **Inherited I-3 (JSON object-key leak):** pre-existing at base; `JsonValueRewriter`
  copies object keys verbatim and never scans them, so `verify_scan` is key-blind by
  construction. Already routed to master (the orchestrator's I-3 merge-sequencing relay).
  NOTE: B2C2-1's fix must decode BOTH keys and values (not values only) or it reintroduces
  the same key-blindness in the new never_rewrite arm.

## Fix-shape (binding, from correctness + security)
B2C2-1: a bare byte scan cannot be the containment floor for a member format that encodes
its strings. The never_rewrite arm needs a DECODED projection (decode the whole document's
string tokens — keys AND values — and scan the decoded forms) summed with the raw byte
floor (for the undecodable case). Do NOT decode values only.

## Checked-clean (execution-verified across lenses)
BL2-2 raw_text arm correct (deliberate fail-closed asymmetry — verifier counts what the
rewriter declines); BL2-3 empty-JSONL correct on both adapters (0 bytes = 0 records,
installed); BL2-5 codex identity derefs both guarded (`.value()`/`.at()` cannot throw —
loop-1 invariant); BL2-7 shared sidecar parser fail-closed, one definition, both callers;
rekey-restricted-to-staged correct both legs; re-pack identity handling correct;
`missing_staged_version` fail-closed both; claude refusal-radius plumbing correct
(per-session refusal preserves clean siblings). Every member IS scanned — the two problems
are the scan's weakness for the JSON member class (B2C2-1) and the collector feeding
inventory-rejected members (B2C2-4).

## Method caveat (correctness, recorded honestly)
The "relocation into rewrite_common is byte-for-byte equivalent" charge is NOT gradable at
these bytes: all six moved symbols are NEW at d6cceba (zero hits at ec9a2db), so the move
happened inside the slice's own pre-fold revisions, unreachable from a one-commit-over-base
branch. What was verified: exactly one definition of each survives (no divergent twin).

## Gate
Second fold cycle folds B2C2-1..B2C2-6 (in-universe) at the one-commit head; the M-4
invariant-scope and the inherited I-3 route up. Because B2C2-1/B2C2-2 again change
install-time verify semantics, the third head owes another targeted security+correctness+
tests re-panel (m-4 re-confirmed). Master's per-session B2-1 ruling stays gated on that
confirmation. Merge/release the operator's; release hold ABSOLUTE.
