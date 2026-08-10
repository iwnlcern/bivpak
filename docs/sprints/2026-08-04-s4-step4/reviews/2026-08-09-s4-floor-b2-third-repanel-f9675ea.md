# B2 third targeted re-panel — head `f9675ea`, cumulative window `ec9a2db..f9675ea`

Convened by s4.orchestrator-planner (3 cold read-only lenses: security, correctness, tests),
M-4 re-confirmed under UNION-SCOPE acceptance (the bare home/username-prefix needle is deferred to
R-4.8 and out of scope here). Verdict: **M-4 does NOT hold — B2 is NOT bar-ready.** All load-bearing
findings byte-verified by the orchestrator at `f9675ea`.

## Findings (material)

### F1 — Security, CRITICAL (CONFIRMED) — the I-3 jsonl key-arm origin-path leak
`verify_scan` (rewrite_common.cpp:1026-1080, JsonValueRewriter at :1044 with `decode_keys` defaulting
false at :501) collects only value strings; JSON object **keys** are neither decode-scanned nor
raw-scanned (the raw floor at :1060-1074 is skipped when the line decodes). Rewrite likewise leaves
keys verbatim (`raw_string` with `decode_keys_==false`, the default in `rewrite_jsonl_*`). So an
origin **path** at a JSON key survives verbatim into the installed session — a literal origin-path
spelling in a published session, which M-4 forbids. Locked in by a **passing** test
(`test_adapter_claude_install.cpp:534-569`: key `/ws/proj` asserted to remain, `outcome==installed`).
This is the previously-carried inherited **I-3** ("master's I-3 call"). Pre-existing at `ec9a2db`, but
B2's own new `verify_whole_document_bytes` (:903-929) uses `decode_keys=true` — B2 closed this class for
the never_rewrite/whole-document arm while leaving the dominant jsonl arm blind; the two must be
symmetric. **Fully fixable in-scope (mirror the key-decode into `verify_scan` + `rewrite_jsonl`); NO
carrier blocker — NOT deferrable like R-4.8.** Origin-disclosure family → master's call (144700).

### F2 — Correctness, IMPORTANT→must-fix (CONFIRMED) — B2-introduced Codex parent self-refusal
B2 ADDED (diff `+`) `image_origin_id_set.insert(*record.original_session_ids.parent)`
(codex/install.cpp:473-474, the verify/refusal set) but the Codex rewrite id-map (`rewrite_ids`,
:404-431) has primary/primary_identity/child ids and **no parent**. A genuinely-collected Codex session
whose rollout head carries `parent_thread_id` (= the parent id; that is how `parent` is populated,
codex.cpp:258-262) will have that id in the verify set, un-rewritten → `origin_id_hits>0` → `verify-hits`
→ the session **refuses itself**. B2 thus converts a pre-existing silent leak into a hard refusal of a
legitimate session — neither is correct; the parent id should be MAPPED (to the parent's installed id
when in image) and the session installed. The covering test (`test_adapter_codex_install.cpp:1659-1717`)
**masks** this — it sets `parent` but crafts the origin body WITHOUT `parent_thread_id` (an input real
`collect` cannot produce), so it never exercises the self-refusal. Codex-only (Claude sets
`parent_id=nullopt`). In-universe (B2's own union widening) → pair fold.

### F3 — Tests, IMPORTANT (CONFIRMED) — Codex child-id union member unverified
Production inserts Codex child ids into the union (codex/install.cpp:476-478) and Claude has a
cross-session falsifier (`test_adapter_claude_install.cpp:2210`), but Codex has none — every Codex union
test clears children or uses same-session children, so deleting the Codex child-id insert fails zero
tests. Coverage gap (production correct), asymmetric with Claude → pair fold (add a Codex cross-session
child-id falsifier mirroring the Claude one).

## Minors (noted; pair discretion / residual)
- Security: raw-text literal-only verify (sound under the model); union scoped to the eligible batch not
  the whole image (low realism); non-staged refused rows omit artifact-derived alias ids (low realism).
- Correctness: two divergent `valid_utf8` defs (adapter.hpp strict-but-NUL-accepting vs
  rewrite_common.cpp:650-683 lenient-but-NUL-rejecting) — fail-closed, latent, worth unifying; JSONL
  `apply_replacements` cross-pair re-scan vs raw single-pass (rare double-rewrite); blank-interior-line
  refusal; live single-partial-record → empty artifact (edge, non-corrupting).
- Tests: `e3.py` `_ADAPTER_SOURCE_ANCHORS` SHA pins (pre-existing source-text seal, correct maintenance);
  `harness-e2 TIMEOUT 600` headroom could mask a perf regression (not flakiness).

## Checked and SOUND
Value-arm encoding coverage (`\/`, `\uXXXX`, doubled-backslash spellings all needled); union assembly
within the batch (primary + parent-in-verify + children + image id + message-uuid origins incl. refused
rows + agentId alias prepass), no double-count, ordering before verify correct; store_root rewrite/verify;
refusal fail-safe wiring; the **precedence fix** (longest-source-first `stable_sort`, non-owning view is
lifetime-safe and deterministic); decode logic (surrogate bounds guarded, fail-closed); the precedence
falsifier RED→GREEN is real and keyed to the defect (the origin-hit verifier is provably blind to the
mis-rewrite, so the falsifier is necessary); torn-tail triggers/warnings; PARENT-id needled tests on both
adapters; union recipient tests non-vacuous.

## Disposition
- F1 (I-3, Critical) → routed UP to master (open origin-disclosure-family call); recommend fold into B2
  (symmetric `verify_scan`/`rewrite_jsonl` key-decode), not deferred.
- F2 + F3 (Important) → folded DOWN to the pair (in-universe).
- The amended head owes a FOURTH targeted re-panel (verify/rewrite semantics change again). Land F2+F3
  (+F1 if master concurs) in ONE commit, then the fourth re-panel.
