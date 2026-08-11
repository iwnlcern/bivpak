## REVIEW-FOLD (cycle 2) — B2 targeted re-panel at d6cceba: MUST-FIX, M-4 DOES NOT HOLD. The first fold closed the two Criticals but left/created a THIRD encoding-blind leak. Three Criticals + three Importants folded (in-universe); one M-4 invariant-scope item routed to the orchestrator. The head owes ANOTHER re-panel.

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-floor-impl-2-b2-review-fold-2
PARENT_DISPATCH_ID: s4-floor-impl-2-b2-review-fold-complete
RUN_ID: s4
TASK_ID: B2
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: yes — a must-fix re-panel with M-4 unmet; you write FOLD_SCOPE before any edit; the amended head owes a THIRD targeted re-panel (verify semantics change again); merge/release the operator's; the release hold is ABSOLUTE
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/SITREP-IMPLEMENTER-SLICE-B2-REVIEW-FOLD-COMPLETE-20260808-162316.md
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: s4.orchestrator-planner, operator
SUBJECT: MUST-FIX (cycle 2) — B2 re-panel at d6cceba; three Criticals confirmed by execution (twice) and re-read at the bytes; M-4 (containment invariant under per-session) does not hold

The master-endorsed targeted re-panel (security + correctness + tests, cold, m-4) ran on
the fold head `d6cceba`. BL2-2 is genuinely closed and the checked-clean set is strong (see
the record). But the first fold's BL2-1 was NARROWED, not closed, and the m-4 review found
the stated containment invariant was never actually met. Full record:
`docs/sprints/2026-08-04-s4-step4/reviews/2026-08-08-s4-floor-slice-b2-repanel-d6cceba.md`.
I byte-verified all three Criticals at this seat; two were also reproduced by the lenses
executing the built binary.

## BLOCKERS (second fold cycle)

**B2C2-1 [CRITICAL — 3 lenses, 2 by execution] — the `never_rewrite` scan is raw-byte, blind to the JSON encoding of the one class it guards.**
`verify_whole_document_bytes` (rewrite_common.cpp:864) → `verify_bare_bytes` (:712) →
`count_hits_bytes` (:676) is a plain byte substring count, no decode. It is the ONLY
verification on the `never_rewrite` arm (claude install.cpp:720), whose bytes are published
verbatim. The declared `never_rewrite` inventory is exactly `{".meta.json"}`
(claude_code.cpp:321) — a JSON document. So a JSON-escaped origin defeats the scan:
reproduced by execution — posix `{"cwd":"\/ws\/proj"}` → installed, origin_path_hits=0,
origin published; wsl `{"cwd":"C:\\Users\\dev\\proj"}` → installed, hits=0 (a JSON
serializer MUST double the backslash, so the `windows_backslash` origin spelling can never
match the file bytes — every wsl/windows image leaks). The jsonl arm already refuses this
class because `verify_scan` scans DECODED values; the never_rewrite arm does not. The
existing positive test (test_adapter_claude_install.cpp:2008) uses only the unescaped
`/ws/proj`, so it proves nothing about the escaped class.
**FIX (binding):** a bare byte scan cannot be the containment floor for a member that
encodes its strings. Decode the whole document's string tokens — **KEYS AND VALUES, not
values only** — and scan the decoded forms, summed with the raw byte floor for the
undecodable case. Decoding values only would reintroduce the inherited object-KEY blindness
(I-3). Add escaped + wsl/windows-flavored `.meta.json` falsifiers that go RED on a raw-only
scan.

**B2C2-2 [CRITICAL, split] — the origin-scan needle set is the session's OWN origins/ids only; M-4 as stated does not hold, and radius-widening cannot fix it.**
`origins` come from `session.record.original_path` alone (claude install.cpp:651-656) and
`origin_ids` from this session's own image id + its own message uuids + its own primary
(:689-693). A sibling session's path, another session's id, and the bare packer
username/home are never needles. So "a published session provably carries no packer
identity" is false, and — the security lens's key point — widening the refusal radius can't
fix it, because "clean" is measured against each session's own needles only.
**IN-UNIVERSE FIX (fold now):** widen the needle set to the IMAGE UNION of all origin
spellings and all origin ids across the manifest, so every session's output is scanned
against every session's origins/ids.
**AUTHORITY (routed to the orchestrator, do NOT resolve locally):** whether the invariant
additionally requires needling the bare packer home/username prefix, or is explicitly
narrowed to the origin-path/id union, is master's call — companion SITREP carries it with
the security lens's narrowest-provable statement. Fold the union; hold the home/username
scope pending the ruling.

**B2C2-3 [CRITICAL — test integrity] — the nine staged pack tests leave HOME unpinned, so they measure the operator's real stores, not the guard deletion.**
`tests/test_pack.cpp` staged sites (772, 889, 951, 1007, 1047, 1076, 1147, 1202, 1284) set
`CODEX_HOME`/`CLAUDE_CONFIG_DIR` to absent paths but never pin `HOME`; both `discover()`
bodies fall through to `env.home/.claude` resp. `.codex`, and `~/.claude` + `~/.codex`
exist on real machines (I confirmed at this host). So the `pack.cpp:541-544`
`if (stores->empty()) continue;` deletion — whose falsifier is "no stores discovered but a
staged sidecar exists" — stays GREEN on every dev machine and E3 host2, RED only in a bare
container; and the nine tests recursively scan the operator's live sessions on every run.
**FIX:** add `const ScopedEnv home{"HOME", (root/"home").string()};` to all nine (sibling
tests at :216/:278/:538 already do this).

**B2C2-4 [Important, correctness I-1] — collector/installer class-set disagreement → cohort-wide refusal with no detail.**
`collect_subtree_artifacts` (claude_code.cpp:253) packs every regular file; install
(install.cpp:180-192) admits only `.jsonl`/`.txt`/`.meta.json`, and an unclassified member
becomes a cohort-wide `containment_refused` with `detail=<none>` — both sibling sessions
refuse, no indication which file. The STAGED collector already enforces the three classes
(`staged_subtree_class`). **FIX:** enforce the same three classes in
`collect_subtree_artifacts` (pack names the offending file) and scope the install refusal
to the owning record with a detail carrying the artifact path.

**B2C2-5 [Important, correctness I-2] — torn-tail branch 4 is silently un-installable.**
Branch 4 (`!live && !valid_json(tail)`, claude_code.cpp:157 / codex.cpp:215) retains the
invalid tail and pushes NO `TornTail`, so pack warns nothing (pack.cpp:606) — but install's
new floor refuses those bytes `undecodable_line`. Claude DEFAULTS to live=false (no status
record → branch 4); codex defaults live=true → branch 3 (drop). So the two adapters land on
opposite branches for identical corruption, and claude's default path produces an image
that silently cannot install. **FIX:** emit a DISTINCT pack warning for retained-torn (not
`TornTailDropped`) so the un-installability is visible at pack time.

**B2C2-6 [Important, tests I-1/I-2] — add the missing falsifiers.**
The ~90-line raw-text rewrite engine has NO output-observing test — the integration test
(test_adapter_claude_install.cpp:2108) asserts only refusal and passes under
`return input`. Add a clean-install `.txt` case where the rewrite happens and INSTALLS
(verify hits 0, published bytes contain the workspace and not the origin). Add the claude
twin of the codex whole-file torn-tail test (codex_collect:535), or dedup the torn-tail
rule (it is still duplicated across the two adapters).

## Minors (discretion)
security M-1/M-2 (two `valid_utf8` under one name diverging on lone surrogates; symlink AT
the sidecar aborts pack vs skip); correctness M-1/M-2/M-3 (the two `valid_utf8`;
never_rewrite literal-suffix vs never_collect globs; `count_hits_bytes` non-overlapping
count — sound verdict, don't build a rule on its magnitude); tests M2/M3/M4.

## What does NOT change
BL2-4 per-session radius stays as master ruled (no radius change); `manifest.cpp` stays
fence-2 OUT (B2-2 is the matrix schema act's); the granted `rewrite_common.{hpp,cpp}` stay
in-universe; any third file is a NEW deviation to the orchestrator before an edit.

## Fold discipline + the gate this head owes
Re-write FOLD_SCOPE `all-in` before any edit; one-commit law + subject preserved; if either
anchored collect file changes, the A3 four-check ceremony re-fires at the new head. Host +
local Ubuntu 24.04 amd64 Docker suite (Actions unused); republish PR #23. Because
B2C2-1/B2C2-2 again change install-time verify semantics, the amended head owes a THIRD
targeted security+correctness+tests re-panel (m-4 re-confirmed on the containment invariant)
— master-endorsed; I run it after your report. Merge/release the operator's.

ACTIONS_GIT_REF: no product/test edits at this seat — review relay; the three re-panel lenses were read-only/execution at d6cceba and my verification read-only git plumbing; this relay + its INDEX row ride one explicit-path docs-lane commit whose SHA lands in history after filing
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to the two docs-lane paths named above

CARRY LIST:
- `.relays/s4/s4-floor-impl/REVIEW-FOLD-PLANNER-B2-CYCLE2-PANEL-DISPATCH-20260808-210909.md` → `s4-floor.implementer`
- B2C2-1..B2C2-6 (in-universe) → implementer second fold at the amended one-commit head
- B2C2-2 M-4 invariant-scope (home/username needles?) → orchestrator (companion SITREP `20260808-210909`)
- inherited I-3 object-key leak → already master-routed; B2C2-1 must decode keys+values so B2 does not reintroduce it in the new arm
- PR #23 at `d6cceba` → HELD pending the second fold + third re-panel; merge/release the operator's
