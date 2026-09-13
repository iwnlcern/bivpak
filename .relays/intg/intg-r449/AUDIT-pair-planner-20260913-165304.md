## AUDIT — R-4.49 line-1 selection, the pair Planner's read-only pass at bivpak `origin/main` 4cf135e (the new published pin `4cf135ee`; local HEAD 26f94e3 carries docs only — product delta origin/main..HEAD = 0 lines): STILL-OPEN in BOTH adapters at the same shape — every store file is read WHOLE by `source_text` BEFORE its head facts are inspected (`claude_code.cpp:654-658`, `codex.cpp:1273-1276`), so the cwd filter's position is after a full read and the read cost is the whole resolved store (measured today on this host: `~/.codex/sessions` 1,503 rollouts / 7.66 GB, `~/.claude/projects` 100 transcripts / 1.81 GB). The head-fact parsers already stop at the first hit — `inspect_rollout_head` returns at the first `session_meta` record (`codex.cpp:229-269`), `inspect_transcript` breaks once cwd+sessionId+version are found (`claude_code.cpp:170-196`) — so the act is a READ-BOUNDING change, not a selection change: stream each file through the existing `secure_io::ReadHandle::stream` (which aborts when the sink returns an error and re-reads from offset 0 on every call — `secure_io.cpp`, the `pread` loop) and stop at the head facts; full reads only for in-root candidates (codex: `has_terminal_tail_record`, `newest_rollout_timestamp`, the artifact source; claude: the artifact source and `apply_torn_tail_rule`) and their descendants — exactly V-LS-4's line. THE SEALED PREMISE SPLITS BY ADAPTER, MEASURED (structure only, no value read into any record): CODEX — 1,503/1,503 real rollouts open with a `session_meta` record carrying `cwd` on LINE 1 (payload keys id/cwd/cli_version always; parent_thread_id on 1,166; session_id on 1,350); line-1 length p50 18,957 B, p90 22,445 B, max 22,552 B; the on-disk fixture rollouts likewise (25 files; the two empty/lone-LF tail-matrix fixtures have no line 1 and are not candidates today either). CLAUDE — only 2/100 real transcripts carry `cwd` on line 1; line-1 record types are `custom-title` 50, `last-prompt` 25, `ai-title` 16, `mode` 4, `user` 2, `bridge-session` 2; the FIRST cwd-bearing record sits at line 3–9 for 76 files (1:2, 3:3, 4:22, 5:10, 6:26, 7:8, 8:2, 9:5), at line 106 at worst; bytes to the end of that record p50 4,709, p90 62,716, max 15,504,275; 3 transcripts carry no cwd anywhere (today's `no_cwd_record` path). The on-disk claude fixture `aaaaaaaa…` has the real shape (metadata records on lines 1–4, first cwd on line 5); the tests' inline transcripts put cwd on line 1. THE GOVERNING TEXT FOR CLAUDE IS NOT c1 §3's SENTENCE BUT m-2's OWN SUPERSESSION OF IT: ADDENDUM 1 §A1/M06 (`../../pdc/master/domains/m-2-agent-adapters/design/2026-07-04-ADDENDUM-1-adapter-remediation.md` @ df523d97…, SEAL-READY rev1) — "candidate selection STREAM-SCANS each transcript from the top and takes the FIRST record carrying a `cwd` field … The scan stops at first hit. A transcript with NO cwd-bearing record in the entire file … is EXCLUDED … and REPORTED per-file (`no_cwd_record`)" — which is what the code does today and what the real shape requires; the fence's DETERMINING TEXT (`142000` §2) quotes §3's "line 1" and does not name A1, and a literal line-1 or fixed-byte head bound on claude would DROP sessions (a V-LS-2 membership delta: 98/100 real transcripts, and the fixture `aaaaaaaa…`). That is S-LS-1/S-LS-2 territory by the fence's own words and is routed UP in the companion SITREP as a CONFIRMATION ask to m-2 (A1's rule governs; the bound is the first cwd-bearing record, the whole file when none), not an in-lane choice. RECOMMENDED SHAPE: ONE commit on a fresh branch cut from `4cf135ee`: (1) claude — a streaming head reader in `claude_code.cpp` (a line-framed sink over `ReadHandle::stream` that stops at the SAME condition `inspect_transcript` uses today, cwd+sessionId+version, so every SessionRecord field stays byte-identical, not only membership) replacing the whole-file `source_text` at `:654`; the full read for selected sessions + descendants unchanged; (2) codex — the same reader stopping at the first `session_meta` record replacing `:1273-1276`; the full read for in-root candidates unchanged; `SessionIdWithoutId` keeps its head-only inputs; (3) tests — the three-leg witness as tests + a membership-identity snapshot before/after over the whole corpus (on-disk fixtures + the tests' inline builders), a bytes-read counter as a product-side seam INSIDE the two candidate paths (m-3 C-2 rule 4: product-side counters are m-2's under V-LS-1), the large synthetic store inside `work` at a locator value under m-3's five rules; (4) no discover, shape, sqlite, manifest/pack/open byte. Blocked on the two confirmations below and on m-3's settle word (the pre-token gate master named).

ROLE: Pair Planner
PHASE: AUDIT
AUTHORITY: read-only
DISPATCH_ID: intg-r449-line1-selection
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: ../../pdc/master/relays/intg-r449-line1-selection-act/PLAN-master-planner-20260913-164219.md
RELATED_CONTEXT: ../../pdc/master/relays/intg-r449-line1-selection-act/PLAN-master-planner-20260913-164219.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/DESIGN-m2-planner-20260903-142000.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/DESIGN-m2-planner-20260903-144700.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/DESIGN-REVIEW-master-reviewer-20260903-151001.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/DESIGN-planner-20260903-143638.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/DESIGN-m2-planner-20260901-005900.md; ../../pdc/master/relays/r437-operator-scope-ruling/PLAN-operator-20260903-152118.md; ../../pdc/master/domains/m-2-agent-adapters/design/2026-07-02-adapter-contract-and-session-semantics.md; ../../pdc/master/domains/m-2-agent-adapters/design/2026-07-04-ADDENDUM-1-adapter-remediation.md; ../../pdc/master/domains/m-2-agent-adapters/design/2026-07-12-ADDENDUM-5-codex-tiered-verdict.md; ../../pdc/master/domains/m-2-agent-adapters/design/2026-08-12-ADDENDUM-12-transitive-collect-and-mono-gate.md; ../../pdc/master/RESIDUALS.md; intg-r450/AUDIT-pair-planner-20260905-215317.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: yes — two confirmations go UP to m-2 through master in the companion SITREP (the claude governing text and bound; the codex head bound), and m-3's settle word is the pre-token gate; no plan is filed for review, no branch cut, no token; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
COMMISSION_SCOPE: the operator-authorized integration phase (2026-08-26) executed by ONE commissioned pair — sub-step 1 first, the A6 rev14 consent-UX fabric with the engine unwired per the sealed spine; subsequent sub-steps (format act consuming LOCKED M rev8 + LOCKED N; then wiring at product scope) each behind their standing gates incl. m-4's reachability re-review before any wiring; sealed design only; STOPs route UP; no merge/push/publication/release authority
COMMISSION_TO: intg.pair-planner
CHARTER_DOC_ID: CH-intg-consent-fabric
FROM: intg.pair-planner
TO: intg.pair-implementer
CC: master.master-planner, master.master-reviewer, m-2.planner, m-2.implementer, m-3.planner, m-3.implementer, m-4.planner, operator
SUBJECT: AUDIT — R-4.49 still-open in both adapters at one shape (whole-file source_text before the head facts: claude_code.cpp:654-658, codex.cpp:1273-1276; the head parsers already stop at first hit) — a read-bounding act, membership untouched; MEASURED: codex line 1 = session_meta+cwd 1503/1503 (max 22,552 B); claude cwd on line 1 only 2/100, first cwd at lines 3-9 (max 106; up to 15.5 MB in) — the governing claude text is m-2's ADDENDUM 1 stream-scan-to-first-cwd, not §3's "line 1"; a literal/fixed head bound would be a V-LS-2 delta → S-LS-1/S-LS-2 confirmation to m-2 UP; codex bound = first session_meta record; secure_io stream aborts on sink error and re-reads from 0 → in-fence streaming reader; S-LS-3 none (no_cwd_record and SessionIdWithoutId keep their inputs); your independent pass + reconcile
REPO: `../bivpak` READ-ONLY at 26f94e3 (product bytes == origin/main 4cf135ee); `../pdc` READ-ONLY (fence rev2 blob re-hashed f2216ee6… == f2216ee6; A1 df523d97…); the REAL host stores `~/.codex/sessions` and `~/.claude/projects` READ-ONLY for STRUCTURE (record types, key presence, byte lengths, line indices) — no value read into any output; no draft, no scout, no product byte
BRIDGE: intg.pair-planner → intg.pair-implementer (your independent pass and reconcile; the plan follows m-2's two confirmations and m-3's settle); master CC (the companion SITREP carries the two asks UP; this relay is the evidence behind them); m-2 seats CC (your fence is the law; your A1 §A1 is what the claude side executes — say if you read your own texts otherwise); m-3 seats CC (your five rules bind the instrument; your settle word is the token gate; S-LS-4 stays yours); m-4 CC (the read set is unchanged; the act only reads LESS); operator CC (visibility; nothing asked)

## Four-bucket verdict

```text
still-open        BOTH adapters read each store file WHOLE before inspecting its head facts:
                  claude_code.cpp:654 `source_text(*main_source)` then :658 `inspect_transcript(*main_text)`;
                  codex.cpp:1273 `source_text(*source)` then :1276 `inspect_rollout_head(*text)`. The cwd filter
                  (:661-668 / :1277-1285) therefore sits AFTER a full read of every file in every resolved store —
                  the R-4.49 registration's store-proportional term. The parsers themselves already stop at the
                  first hit (claude: cwd+sessionId+version found, :190-193; codex: the first session_meta record,
                  :269). Bytes at origin/main 4cf135ee (the fence's read at 9e1a72d predates the R-4.50 discover
                  change; the collect bodies are byte-identical to the pin on these lines — diff 9e1a72d..4cf135ee
                  on codex.cpp = 0 lines; on claude_code.cpp only the discover body 570-596).
already-closed    nothing of the act. Adjacent and landed: R-4.50 (claude discover union) at 4cf135ee; m-3's stub
                  follow-through INSIDE H' (the settle word is the pre-token gate, not an audit question).
product-overlapped (i) the shared head parsers `inspect_transcript` (also used by append_staged_session :434/:493)
                  and `inspect_rollout_head` are NOT changed — a NEW streaming reader feeds them the head text;
                  (ii) `secure_io::ReadHandle::stream` (outside the fence) needs NO change: it aborts when the sink
                  returns an error and every call re-reads from offset 0 (`pread` loop) — the in-adapter sink stops
                  the stream at the head facts; the selected candidates' later full reads reuse the same source;
                  (iii) pack.cpp:624-629 surfaces `no_cwd_record` as SessionNoCwdRecord and the adapter warnings
                  verbatim — S-LS-3: NONE fires: no_cwd_record needs the WHOLE file scanned (A1: no cwd in the
                  entire file) and the streaming reader reads to EOF when no cwd appears; SessionIdWithoutId uses
                  head facts only; CompressedRolloutSkipped / SessionDescendantUncarryable / CodexDbEnrichmentSkipped
                  come from enumeration and the sqlite copy, untouched; (iv) sqlite threads stays enrichment
                  (db_updated_at in better_candidate tie-break, :437) — V-LS-3 untouched; (v) m-3's harness reads
                  identities/provenance/paths/warnings, not read patterns (C-2 rule 5) — S-LS-4 dormant.
recommended-next  ONE commit on branch intg/r449-line1-selection cut from origin/main 4cf135ee (cut-point count
                  rev-list --count origin/main..<branch>^ = 0): a streaming head reader in each adapter file
                  (line-framed sink over ReadHandle::stream; stop condition IDENTICAL to today's parser exit —
                  claude cwd+sessionId+version, codex first session_meta — so every SessionRecord field, not only
                  membership, stays byte-identical); full reads only for selected sessions + descendants (V-LS-4);
                  the three-leg witness as tests with a product-side bytes-read seam inside the two candidate
                  paths; the large synthetic store under m-3's five rules. Blocked on the two m-2 confirmations
                  and m-3's settle word.
```

## Measurements (this seat, 2026-09-13 16:51; structure only; the commands are the plan's LEG-2 instrument's ancestors)

```text
codex  ~/.codex/sessions       files 1,503 · bytes 7,656,072,880 · line 1 == session_meta with cwd: 1,503 (100%)
                               payload keys: {id,cwd,cli_version,parent_thread_id,session_id} 1,158 · {id,cwd,cli_version,session_id} 192 · {id,cwd,cli_version} 145 · {id,cwd,cli_version,parent_thread_id} 8
                               line-1 bytes p50 18,957 · p90 22,445 · p99 22,538 · max 22,552
claude ~/.claude/projects      files 100 · bytes 1,808,487,942 · cwd on line 1: 2 · no cwd anywhere: 3
                               line-1 record types: custom-title 50 · last-prompt 25 · ai-title 16 · mode 4 · user 2 · bridge-session 2
                               first cwd-bearing line: {1:2, 3:3, 4:22, 5:10, 6:26, 7:8, 8:2, 9:5, …} max 106
                               bytes to the end of the first cwd record: p50 4,709 · p90 62,716 · p99 15,504,275 · max 15,504,275
fixtures on disk               tests/fixtures/codex_store: 23 rollouts with line 1 == session_meta+cwd (line-1 bytes 207-597) + 2 empty/lone-LF;
                               tests/fixtures/claude_store: aaaaaaaa… = last-prompt, mode, permission-mode, bridge-session, then cwd on line 5 (real shape, A1's FX-M06);
                               no-cwd-9999… = 3 lines, no cwd (the no_cwd_record fixture, test :342); cccc-2222… cwd on line 1; subagents/agent-a01 cwd on line 1
tests                          test_adapter_claude_collect.cpp 15 TEST_CASEs (inline transcripts put cwd on line 1, :357/:410); test_adapter_codex_collect.cpp 25 TEST_CASEs (write_rollout :125 puts session_meta on line 1)
stream contract                secure_io.cpp ReadHandle::stream: 8 KiB pread loop from offset 0; `if (!ok) return ok;` — a sink error aborts the stream; re-entrant (offset local)
```

## Findings routed UP (the companion SITREP carries them to m-2 through master)

**C-1 — the claude governing text and bound (S-LS-1 + S-LS-2).** The fence's DETERMINING TEXT quotes c1 §3 "reads `cwd` from line 1"; m-2's ADDENDUM 1 §A1 (M06, SEAL-READY) SUPERSEDES that sentence with STREAM-SCAN-TO-FIRST-CWD, stop at first hit, whole file when none (→ `no_cwd_record`). The real store shape (2/100 on line 1; first cwd at lines 3–9, worst 106; up to 15.5 MB in) and the on-disk fixture make a literal line-1 or fixed-byte bound a MEMBERSHIP DELTA (V-LS-2). Asked of m-2: CONFIRM that A1 §A1 is the governing selection semantics for the claude side of this act and that the head bound is therefore "the first cwd-bearing record, the whole file when none" (no fixed byte bound; the malformed/unparseable line skipped as today, :178-181). Any other answer is m-2's ruling to give, never the lane's.

**C-2 — the codex head bound (S-LS-1).** c1 §4 and A5 §A5.4-CX say line 1 == `session_meta`; the code's rule is "the first `session_meta` record" (skipping unparseable lines). Asked of m-2: CONFIRM the bound as "the first `session_meta` record, the whole file when none" (identity with today's parser; observed max line-1 22,552 B, so the head read is one or two 8 KiB chunks in practice) rather than a fixed byte cap.

## Observations (disclosed; no ruling asked)

```text
O-1  the claude parser keeps scanning past the first cwd until sessionId and version are also found (:190-193); these are
     enrichment fields (session_id falls back to the filename stem; version → agent_version_at_pack). The recommended reader
     keeps the SAME stop condition so every record field stays byte-identical — a cost of a few more head records, never
     a semantic choice; if m-2 prefers cwd-only stopping, that is a field-identity question for m-2, not membership.
O-2  A12's closure for claude is directory-based (child_ids_for :304 reads <sid>/subagents/; collect_subtree_artifacts
     opens the subtree) — no line-1 edge fact; the full read of descendants stays (V-LS-4). Codex parent_id IS a line-1
     session_meta fact (:257-268) — unchanged.
O-3  the canonical cross-repo design edge: the plan carrier will reuse the R-4.50 design block (fence rev2 @ f2216ee6 at
     its pdc commit) that measured GREEN root-mode through plan-19; master's gate asks it MEASURED FIRST for this act —
     ONE root-mode measurement of the plan draft will be run at plan time and archived (the operator's no-sweeps rule
     otherwise stands).
O-4  the landing lessons are plan terms this time: fresh branch + worktree from 4cf135ee (never lane-local main); the
     retained -v2 worktree DISPOSED at Task 0 with a receipt (master ruled it lane-local state); census at the branch
     head AND at the merge head with population + reduction + LC_ALL=C pinned and the synthetic store disclosed; R-4.53
     arm (a) — no raw/stripped census intermediates in the evidence set.
```

ACTIONS_GIT_REF: docs-lane writes only — this relay and its INDEX row, committed path-scoped with the companion SITREP, no trailer; the host stores were READ for structure only; no product byte, no branch, no worktree, no token, no push, no PR, no merge, no release.
RELAY_LINT: engine-rendered submission; per-file v2.9.2 lint rides the daemon gate (the draft pre-linted per-file; the four commission-surface lines copied byte-for-byte from the filed plan-14 carrier).
CARRY_LIST (per D-8.5, this turn's pending hops — path + the one TO seat):
- rendered successor of this draft -> intg.pair-implementer
FINAL_GIT_STATUS_SHORT:
 M .relays/s4/INDEX.md
 M .relays/s4/SEATS.md
?? .relays/s4/s4-floor-impl/REVIEW-FOLD-IMPLEMENTER-CB2-RECHECK2-TWO-CRITICALS-COMPLETE-PUBLISHED-20260810-185643.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV0-20260809-033926.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV1-20260809-050934.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV2-APPROVE-20260809-053253.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV2-APPROVE-LINEAGE-CORRECTION-20260809-061515.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV3-MUST-REVISE-20260809-210140.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV4-APPROVE-20260809-211611.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV5-MUST-REVISE-20260809-230557.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV6-APPROVE-20260809-231944.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-CARRIER-REV0-20260809-055741.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-CARRIER-REV1-20260809-061515.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-CARRIER-REV2-APPROVE-20260809-062921.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-CARRIER-REV2B-UNIQUE-APPROVE-20260809-141439.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-FOLD3-RECEIPT-DETERMINISM-MUST-REVISE-20260810-041555.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-FOLD3-RECEIPT-DETERMINISM-R1-APPROVE-20260810-043843.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-LENSFOLD-SIX-MUSTFIX-APPROVE-20260810-074840.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-MICROFOLD-V1-PROOF-MUST-REVISE-20260810-145556.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-MICROFOLD-V1-PROOF-R1-MUST-REVISE-20260810-150633.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-MICROFOLD-V1-PROOF-R2-APPROVE-20260810-152645.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-CARRIER-COMPLETE-20260809-192358.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-CARRIER-DISPATCH-LINEAGE-BLOCKER-20260809-063906.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-CARRIER-IMPLEMENTED-E2-BLOCKED-20260809-182853.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-FOLD-MF1-MF6-COMPLETE-20260809-220327.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-FOLD2-EXTENDED-ROOT-RF1-RF2-COMPLETE-20260810-020857.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-FOLD3-COMPLETE-20260810-052656.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-FOLD3-DISPATCH-LINEAGE-BLOCKER-20260810-030814.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-LENSFOLD-COMPLETE-20260810-092751.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-MERGE-BLOCKED-DRAFT-UNSTABLE-20260810-174554.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-MICROFOLD-DONE-WITH-CONCERNS-20260810-160710.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-PR24-MERGED-STEP4-20260810-184033.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-WAVE-A-REVERIFY-STAGE1-INDEPENDENT-STOP-CORROBORATION-20260820-161626.md
?? .relays/s4/s4-matrix/SITREP-implementer-20260825-220111.md
?? docs/sprints/2026-08-04-s4-step4/MIGRATION-adt-skills-2.9-20260816.md
?? relay-draft-intg-task4-stop.md
Literal `git status --short` of the docs lane at write time (inherited S4 rows and inherited untracked files included as printed); the shared INDEX carries sibling-authored rows not claimed clean here.
