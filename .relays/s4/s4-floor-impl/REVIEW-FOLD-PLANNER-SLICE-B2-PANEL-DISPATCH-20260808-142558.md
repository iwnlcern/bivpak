## REVIEW-FOLD — Slice B2 team-of-5 panel at 54a6c54: verdict MUST-FIX with TWO confirmed Criticals (origin bytes reach the recipient's host store un-scanned, two independent vectors). Five actionable blockers folded (BL2-1..BL2-3, BL2-6, BL2-7) + one authority item HELD (BL2-4); BL2-5 REGRADED to non-blocking hardening by the correctness lens's execution trace; one fence-2 caveat routed to the orchestrator; efficiency/idiom items at discretion.

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-floor-impl-2-b2-review-fold
PARENT_DISPATCH_ID: s4-floor-impl-2-b2-complete
RUN_ID: s4
TASK_ID: B2
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: yes — a must-fix panel result with two Criticals; you write FOLD_SCOPE before any edit; any byte change preserves the one-commit law and refreshes exact-head evidence; merge and release remain the operator's alone and the release hold is ABSOLUTE
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/SITREP-IMPLEMENTER-SLICE-B2-COMPLETE-20260808-065636.md
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: s4.orchestrator-planner, operator
SUBJECT: MUST-FIX — panel-at-SHA on PR #23 head 54a6c54f9d12874123bb520b2598f1086931f70f; two Criticals reproduced by running the code and re-confirmed at the bytes at this seat

Five cold SHA-bound lenses reviewed the committed blobs at exact `54a6c54`. I re-ran the
load-bearing claims at this seat: both Criticals confirmed by direct read of the bytes
(the `never_rewrite` arm has no verify call; `verify_raw_text_bytes` reuses the rewriter's
own `boundary_ok`), topology/scope/fences clean, and the A3 anchor recapture verified by
recomputed SHA-256 (claude `046527fd…`, codex `da32ace6…`, matching `e3.py`). Verdicts:
security must-fix (1 Critical, upgraded from Important on cross-lens verification),
correctness must-fix (2 Critical, both reproduced by COMPILING AND RUNNING the committed
functions), tests must-fix (2 Critical), idiom must-fix (6 Important), performance approve
(3 Important, efficiency). Consolidated, deduplicated, ranked below.

## BLOCKERS — must fix before this slice can be recommended for merge

**BL2-1 [CRITICAL] — `never_rewrite` artifacts are written to the recipient's host store neither rewritten NOR verify-scanned; the origin-leak guard over that whole class was deleted, and a new test SEALS the leak.**
Confirmed by tests C2, security C-1 (Critical), correctness C1 (ran it), and my own read
at `src/adapters/claude_code/install.cpp:684-703`: the loop verifies only the `jsonl`
(:688-696) and `raw_text` (:697-701) arms, then `session.outputs.push_back(output)`
(:703) with NO branch for `never_rewrite`. At base (`ec9a2db:…:590-593`) the
`merge_verify(verify_scan(...))` sat OUTSIDE the rewrite guard and scanned EVERY
destination. The exemption is NOT gated to `.meta.json`: `never_rewrite` is the DEFAULT
ternary arm (`install.cpp:177-183`), reached by ANY subtree artifact not ending
`.jsonl`/`.txt` (`.json`, `.md`, `.log`, `.env`, extension-less…), and normal collect
(`collect_subtree_artifacts`) admits every regular file with no extension filter. Under
`--consent yes` the destination is the recipient's PERSISTENT Claude store. Scenario: a
packer's session subtree carries `notes.md` (or a `.json` sidecar) embedding
`/Users/packer/clients/acme-acquisition` and the original session id; the recipient's
install writes it byte-identical into `~/.claude/projects/<key>/<minted-id>/` and reports
`installed`, `origin_path_hits: 0`. The new test `tests/test_adapter_claude_install.cpp:1982-2035`
pins exactly this (and the `artifacts_checked` 3→2 edits at :565/:~640 are the lost
coverage on the wire).
FIX (correctness's refined shape — do NOT simply restore the old call; base was
over-strict, a pretty-printed multi-line `.meta.json` hit the `decoded=false` auto-refuse
arm): add a third arm that leaves `output` untouched but runs a WHOLE-DOCUMENT origin
scan (`rewrite::count_hits_bytes` over the member, fail-closed, no line-structure
assumption) and restores `artifacts_checked` to the destination count. Additionally key
the exemption off the DECLARED inventory (`claude_code.cpp:321 never_rewrite={".meta.json"}`)
rather than the suffix fallthrough, so declared and enforced policy stop diverging. Fix
the sealing test to assert refusal.

**BL2-2 [CRITICAL] — the new `.txt` raw-text verifier is tautological: it shares the rewriter's `boundary_ok`, so it cannot flag any origin the rewriter declined.**
Confirmed by security I-2, correctness C2 (COMPILED + RAN, four concrete leaks), and my
read at `src/adapters/adapter.hpp:315-338`: `verify_raw_text_bytes` matches with
`matches_at(...) && boundary_ok(...)` — the identical predicate `rewrite_raw_text_bytes`
uses, unlike `rewrite::verify_scan` which counts unanchored substrings and fails closed on
an undecodable line. Correctness ran the committed functions with pair `/ws/proj →
/host/ws`: `"Working directory is /ws/proj.\n"`, `"/ws/proj:12: match here\n"` (ripgrep
output — the most likely `.txt` content), `"backup at /ws/proj-old\n"`, and an escaped
form all pass through UNCHANGED with `origin_path_hits == 0`. The source-host absolute path
is published into the store, install reports clean. New surface this commit.
FIX: the verifier must count bare `matches_at` occurrences WITHOUT `boundary_ok` (a
declined-because-ambiguous match is exactly what a leak guard must catch), matching
`verify_scan`'s fail-closed posture.

**BL2-3 [Important] — a zero-byte `.jsonl` artifact makes its whole session un-installable, and A3.3 can MANUFACTURE that state.**
security I-3 + correctness I3. `strict_jsonl_decodable` (`adapter.hpp:377`) excludes the
empty file from the trailing-newline exemption (`start != 0U`), so `parse_json("")` errors
⇒ `undecodable_line` ⇒ session refused. Reachable via (a) an empty `subagents/*.jsonl` in
the source subtree (collected with no size filter), and (b) A3.3 branch-3 itself: a live
session whose JSONL has no LF and one invalid segment gets `resize(tail_start==0)` → a
0-byte member + a `TornTailDropped` warning → then refused at install. A3.3's stated
purpose is to make live sessions installable; here it produces an un-installable image.
FIX: drop the `start != 0U` clause so an empty JSONL decodes (zero records), and
reconsider branch-3 emitting a 0-byte member.

**BL2-4 [Important — AUTHORITY, routed to orchestrator; do not resolve locally] — the origin-leak refusal radius silently narrowed from whole-set to per-session.**
correctness I4. Base refused the ENTIRE record set on origin hits; now a session with real
origin hits refuses alone and clean siblings publish (`codex/install.cpp:494-504`,
`claude_code/install.cpp:705-720`), and a new test seals it. The dispatch authorized
per-session scope ONLY for `undecodable_line`; extending it to the leak class weakens a
containment guarantee. The row CLASS still forces `containment_refused` (sessions.cpp:485-489),
so this is radius + detail (`rewrite_verify_failed`→`origin_path`/`origin_id`), not
classification. I have routed the authority question to the orchestrator (companion SITREP);
HOLD this one pending that ruling — do not change the radius under the current fold until
it lands.

**BL2-5 [REGRADED → Minor / hardening — NOT a blocker] — a codex-leg invariant is carried by `assert()` (stripped under the shipped `-DNDEBUG`) and a sibling `rollouts.find` deref is unchecked.**
Raised by idiom X-1/X-4; the correctness lens then REFUTED both as live defects by tracing
the bytes, and security concurred (M-4/M-5 Minor). The `assert` deref at
`codex/install.cpp:397,423` is unreachable: the pre-pass at :347-375 visits every record
with no early skip and refuses-all on `!valid`, so reaching :381 proves every parent/child
identity is engaged; `identity_for_artifacts` is a pure function fed byte-identical spans
in both loops. The `rollouts.find(*original_id)` at :452-453 cannot miss for the same
reason (keys are exactly the per-group identities; `id_from_artifact` nullopt is caught
first with a whole-set refusal). So this is latent fragility, not a shipped bug — do NOT
merge-block on it. RECOMMENDED hardening (your discretion): use `.value()` / `rollouts.at()`
so a future divergence throws instead of corrupting, or better, carry the identity forward
on the prepared session as the claude leg already does (`PreparedSession::image_session_id`).

**BL2-6 [Important — test strength] — the falsifiers below are missing or vacuous; add them (some must exercise the NEW verify behavior from BL2-1/BL2-2):**
- the two "interior segments never inspected" controls are VACUOUS (both run `live==false`,
  and the drop path is gated on `live`, so the assertion is true by construction — tests
  C1). Add controls with `live==true` (claude `status:"running"`; codex a valid
  non-terminal final record) asserting streamed bytes + `torn_tails.empty()`.
- whole-file torn tail (`split==npos`, single-line invalid live → 0 bytes) untested
  (tests I3) — pin the intended outcome (ties to BL2-3).
- the escaped-origin refusal tests now short-circuit at the decodability gate, so the
  decodable well-formed escaped-origin class is uncovered (tests I4) — add a well-formed
  `{"cwd":"/ws/proj",…}` fixture that must be caught by the corrected scan.
- single-artifact-only torn-tail tests miss parent/child artifact mispairing and the
  non-live-child-under-live-parent behavior (tests I5).
- the non-staged identity-mismatch refusal and the two unfalsifiable verify boxes
  (tests I6/I7) — add kill-power.

**BL2-7 [Important — idiom, maintainability with a silent-failure edge] — the 96-line staging-sidecar PARSER is byte-identical in both adapters for a document core/open owns; and 208 lines of a competing rewrite API landed in the root header past the swap guard.**
idiom I-1, I-2, X-2. `struct StagedMapRow`/`StagedSidecar`/`parse_staged_sidecar` are 96
byte-identical lines in `claude_code.cpp:335-430` and `codex.cpp:481-576`; the writer is
`sessions.cpp:35-96`. Rename a key there and BOTH readers fall into the
`invalid_staged_sidecar` early-return — silent loss of staged sessions at pack time, not a
compile error (the adapter↔core format is coupled with no shared owner). FIX: move the
sidecar schema parser to the reserved shared module (`rewrite_common.{hpp,cpp}`) or a
core-owned shared header so the schema has ONE spelling. Also move the 208-line raw-text
rewrite API out of the root `adapter.hpp` (it bypasses the `bugprone-*` swap guard the
codebase relies on, since clang-tidy's default empty HeaderFilterRegex doesn't diagnose
header bodies) and give the bare-span twins wrapper structs like their `rewrite_common`
siblings.

## ROUTED TO THE ORCHESTRATOR (companion SITREP `…-142558`), not yours to act on
- BL2-4 authority: per-session vs whole-set refusal radius for the origin-leak class.
- fence-2 caveat: the `staged` rekey privilege derives from image-controlled
  `locator`/`discovery_tier` read without enum validation in `manifest.cpp` (fence-2 OUT) —
  a crafted `.bvpk` declares its own rekey privilege (security C-6 / correctness). Not
  B2's to fix; routed as hardening.
- note: BL2-1/BL2-2 are the SAME origin-disclosure family as slice C's master-held
  ROUTED-3; I flagged the linkage so the resolutions stay consistent.

## MINORS / EFFICIENCY — your discretion unless the operator/orchestrator directs
performance (approve; efficiency, felt only at store scale): torn-tail reads the whole
artifact to inspect only the last segment (`claude_code.cpp:148`/`codex.cpp:206`; O(1)
rolling buffer instead); claude double-reads the main transcript at `claude_code.cpp:760`;
staged locators run a full directory walk per row on re-pack (`claude_code.cpp:449`,
`codex.cpp:741`). Performance's OUT-OF-DIFF note: inherited `verify_scan` cost dominates
install at transcript scale — route as a separate residual, not a B2 fold. idiom minors
(M-1..M-7, incl. the stale `test_sessions.cpp:159` comment referencing the removed
`rewrite_verify_failed`; `Handling` enum mixing format+policy axes; `"verify-hits"` raw
literal in four sites). security M-1/M-2 (symlink AT the sidecar path aborts the whole pack
vs skip; staged walk roots lack the `validate_directory_no_follow` gate) and M-6 (torn-tail
buffers uncapped at collect; `if(!bytes) continue` is a fail-open fifth branch). correctness
M5-M8 (claude staged reader drops child rows; same-workspace round-trip aborts pack).

## REJECTED / regraded (recorded so you don't chase them)
The two Criticals held up under execution and re-read. Two idiom-raised correctness
suspicions (X-1 assert-stripped deref; X-4 unchecked `find`) were REFUTED as live defects
by the correctness lens tracing the establishing invariant at the bytes — both regraded to
non-blocking hardening (BL2-5 above). Performance explicitly did NOT repeat the prior
slice's unreachable-Critical error (it probed the real store). The re-pack identity Critical + the two Importants your
own review closed reproduce as GENUINELY closed (correctness traced the loops); the A3
ceremony, `missing_staged_version` fail-closed, the rekey-restricted-to-staged guard, the
CANON-2.6 symlink/TOCTOU posture, and `.txt`-excluded-from-JSONL-rule are all
checked-clean with evidence across security + correctness.

## Fold discipline and the re-review this fold owes
Write FOLD_SCOPE (every touched file vs the findings scope) BEFORE any edit; every row
inside the B2 universe; a row outside it (incl. any `manifest.*` reach) is a deviation to
the orchestrator BEFORE the edit. Preserve the one-commit law and the subject; refresh
exact-head evidence (focused RED→GREEN for every new/changed falsifier; the corrected
sealing tests for BL2-1/BL2-2 must now assert REFUSAL); if you touch either anchored
collect file again, the A3 four-check ceremony re-fires at the new head. Rerun the host
suite + the standing local Ubuntu 24.04 `linux/amd64` Docker suite (Actions unused); re-
publish under the standing disposition. Because BL2-1/BL2-2 change install-time VERIFY
semantics (production, security-bearing), the replacement head owes a TARGETED re-panel on
the rewrite/verify surface — at minimum security + correctness + tests re-run on the fold
delta — not merely my targeted re-check. Merge and release remain the operator's alone.

ACTIONS_GIT_REF: no product/test edits at this seat — this is a review relay; the five lens reviews were read-only at 54a6c54 and my verification was read-only git plumbing (git show/shasum at the SHA); this relay + its INDEX row ride one explicit-path docs-lane commit whose SHA lands in history after filing
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to the two docs-lane paths named above

CARRY LIST:
- `.relays/s4/s4-floor-impl/REVIEW-FOLD-PLANNER-SLICE-B2-PANEL-DISPATCH-20260808-142558.md` → `s4-floor.implementer`
- BL2-1..BL2-3, BL2-6, BL2-7 (in-universe) → implementer fold at the amended one-commit head; BL2-5 = recommended hardening at discretion
- BL2-4 authority (refusal radius) + manifest.cpp enum caveat + ROUTED-3 family linkage → orchestrator (companion SITREP `20260808-142558`)
- PR #23 at `54a6c54f9d12874123bb520b2598f1086931f70f` → HELD pending fold; merge/release the operator's
