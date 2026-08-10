# VERIFICATION RECORD — R-4.8 micro-fold at `0ab998d` (CLOSES THE HUMAN-LENS WINDOW)

DISPATCH_ID: s4-matrix-arm1-r48-microfold-verify
PARENT_DISPATCH_ID: s4-matrix-arm1-r48-microfold-impl-complete
CANDIDATE_SHA: 0ab998d8431a20de80b8d769fb82c1350ed0728d (branch `s4-matrix/r48-carrier`, ONE test-only commit over `d234314`)
FOLD_DELTA: `git diff d234314..0ab998d` = exactly the 3 dispatched test files, +31/-12; ZERO production bytes
PLAN: micro-fold PLAN rev2 (`f5f71432…`, approved `152645` with five binding conditions)
PRIOR_RECORDS: panel `006144b2…`; re-check `e6a589a5…`; check `c1e7eb8d…`; verification `4f90641f…`; lens-fold check `eb187d09…`
LEAD: s4-matrix.planner (non-lens; synthesis only)
DATE: 2026-08-10

PANEL_CHOSEN: single owning lens per the approved sizing (lead + tests) — the two gating findings were the tests lens's own; zero production bytes move. PANEL_COMPOSITION: one independent cold read-only subagent (r48-microfold-verify), pinned to `0ab998d`, committed blobs only (the working tree is on main and does not contain this branch — the lens stated this and read blobs throughout). Both pair seats excluded; no re-spawn.

## Spawn-count reconciliation

| lens seat | spawns | stalls | finding-sets |
|---|---|---|---|
| test-coverage | 1 | 0 | 1 |

1 spawn = 1 finding-set + 0 stalls. Report delivered via the agent mailbox, reproduced below unaltered.

## LEAD PRE-PANEL VERIFICATION (E1, at `0ab998d`, before spawning)

- One commit over `d234314`; delta exactly the three dispatched test files (+31/-12).
- `kEngagedCarrier` defined once per TU with exactly three uses — prefix CHECK, needle
  loop, engaged `PackerHome` construction; the escaped needle genuinely COMPUTED by the
  `/`→`\/` transform, not literal; both predicates non-fatal and at fixture-input
  position before the installs; the output-side `find("/ws")` guard absent from both
  files (zero occurrences); `CHECK(report->agent_sessions.empty())` present in the
  decoy block after `require_store_roots_under`.
- The pasted four-site RED evidence matches the demanded shape (two CHECKs per receipt
  test, four total, before any install; `/ws` restored for the committed GREEN).
- **PR STALENESS (load-bearing for the hand-up):** `git ls-remote` shows the published
  PR #24 head is `2341667`; the reviewed head `0ab998d` is TWO commits ahead
  (`d234314` lens-fold, `0ab998d` micro-fold). The published PR does NOT contain the
  reviewed bytes.

## VERBATIM REPORT — test-coverage lens

```
TEST-COVERAGE LENS — R-4.8 micro-fold verification at s4-matrix/r48-carrier@0ab998d8431a20de80b8d769fb82c1350ed0728d (one commit over d2343147243b9cc65ce94c853b49f5ecac1227ae). Read-only; every reading below is from committed blobs via `git show <sha>:<path>` and `git diff d234314..0ab998d`. I did not build or run.

## VERDICT: pass

Both of my prior findings close. MFX-1 closes properly — the two new predicates are immune to both false witnesses I originally exercised, and they are genuinely coupled to the carrier constant. MFX-2 closes. The pasted four-site RED evidence reconciles with the source, including the exit code and the line attribution. I found no Critical, Important, or Minor defects introduced by the fold. I am recording three informational items below; none of them is a fix condition and none blocks the merge hand-up.

---

## Findings

**INFO-1 — empty-carrier vacuity remains theoretically open.** `tests/test_adapter_claude_install.cpp:571,581-583` and `tests/test_adapter_codex_install.cpp:542,552-554`.

If `kEngagedCarrier` were ever emptied rather than changed, both predicates would pass vacuously: an empty needle makes `std::search` return `first`, which compares unequal to `end()` for any non-empty member, and `"/ws/proj".starts_with("")` is trivially true. This is the same *class* as MFX-1 (a guard that cannot fail), reached by a different edit. I am not treating it as a fix condition, because the constant is a source literal, the canonical mutation the plan specified is a value change rather than an emptying, and no realistic edit path produces an empty carrier. If a future pass wants the last hole shut, one line does it: `static_assert(kEngagedCarrier.size() > 1U && kEngagedCarrier.front() == '/');` next to the constant. I would take that, but I am not asking for it now — re-opening a hash-bound cycle for it is not proportionate.

**INFO-2 — the escaped-needle transform models solidus escaping only.** `tests/test_adapter_claude_install.cpp:572-578`, `tests/test_adapter_codex_install.cpp:543-549`.

The loop escapes `/` as `\/` and passes every other byte through. That is exactly right for the current constant, because the fixture spells the carrier segment as `\/ws` — but the fixture deliberately spells the *next* segment with a `p` for the `p` (`"cwd":"\/ws\/proj"`). So if anyone ever widens `kEngagedCarrier` to `/ws/proj`, the computed needle `\/ws\/proj` will not be found, and the CHECK will go red for an encoding reason rather than a coverage reason. This fails loud, not silent, so it is a brittleness note rather than a defect — but a future widener will lose time to it if it is not written down somewhere.

**INFO-3 — what these guards do and do not prove; worth recording so nobody over-reads them later.** `src/adapters/adapter.hpp:161`, `src/core/open/sessions.cpp:271`.

`packer_home` is presently write-only on the install path. It is declared as an `InstallTarget` field at `src/adapters/adapter.hpp:161` and populated from the manifest at `src/core/open/sessions.cpp:271`, and `git grep -n packer_home 0ab998d -- src/adapters` returns that declaration and nothing else — no adapter reads it. So the four byte-identity `REQUIRE`s in these two cases are true by construction today, and would remain true if the carrier were any string at all. The two new predicates do not change that, and they are not meant to: they are fixture non-vacuity guards asserting that the record's origin lies strictly under the carrier and that the input bytes carry the carrier in a rewrite-eligible encoded spelling — i.e. that the byte-identity claim is being made over a fixture in which carrier-conditional rewriting *could* manifest if it were ever introduced. That is the correct and intended scope, and it is what the plan prescribed. It is not a proof that the product observes the carrier, and the test should not be cited as one.

---

## MFX-1 closure, with the false-witness analysis

**Mechanical checks, all confirmed at 0ab998d.**

One constant per TU, at function-block scope inside the TEST_CASE: `kEngagedCarrier` at `tests/test_adapter_claude_install.cpp:560` and `tests/test_adapter_codex_install.cpp:528`, both `constexpr std::string_view = "/ws"`.

The engaged `PackerHome` is constructed from it, not from a literal: `tests/test_adapter_claude_install.cpp:636-638` and `tests/test_adapter_codex_install.cpp:608-610` both pass `std::string{kEngagedCarrier}` with `PathFlavor::posix`. Each constant has exactly three uses per TU — the prefix CHECK, the escaping loop, and this construction — so the literal-decoupling defect I raised is closed.

Strict prefix, not substring: `record.original_path.starts_with(std::string{kEngagedCarrier} + "/")` at claude:571 and codex:542. It is `starts_with`, anchored at position 0, and the trailing `/` is appended so the match is at a path-component boundary. `record.original_path` is `"/ws/proj"` in both fixtures (`claude_entry` default parameter at claude:212; `codex_entry` at codex:171), so the predicate holds today and is a real assertion about the record's origin lying strictly beneath the carrier.

The needle is computed, not written: claude:572-578 / codex:543-549 build `escaped_member_needle` by walking `kEngagedCarrier` and emitting a `\` before each `/`. For `"/ws"` this yields the four bytes `\/ws`. There is no literal spelling of the escaped form anywhere, and no comment-only coupling.

The search is over raw input member bytes, pre-install: `const auto& raw_member = members.at(main_artifact())` at claude:580 (`members.at(parent_artifact())` at codex:551), bound after the fixture assignment at claude:563-568 / codex:531-539 and before any install. Both CHECKs sit at claude:571 and 581-583 / codex:542 and 552-554, while the two `install_receipt` calls are at claude:635-639 / codex:607-611 — so both predicates evaluate before the first install, as the plan required.

Both are non-fatal `CHECK`, not `REQUIRE`, so a single mutated run evaluates all four. This is load-bearing for the evidence and I return to it below.

The output-side guard is gone outright in both files. `git grep -n "engaged.contents\|any_of(engaged" 0ab998d -- tests/` returns only `REQUIRE(engaged.contents == absent.contents)` at claude:643 and codex:618. The `REQUIRE(std::ranges::any_of(engaged.contents, ... find("/ws") ...))` block is deleted in both, along with its comment.

**The decisive question: are both new predicates immune to my two original false witnesses?**

*False witness A — the restore workspace directory literally named `workspace`, which contains the substring `/ws`.* Immune to both predicates, and for independent reasons.

The prefix CHECK never touches a filesystem path. It reads `record.original_path`, a manifest field whose value is the string `"/ws/proj"`. The workspace path is `<tmpdir>/biv-claude-install-packer-home-receipt-<pid>/workspace`, and it is not that field. Even if one substituted it in adversarially, the predicate is `starts_with("/ws/")` anchored at position 0, and the workspace path begins with the temp-directory root, not with `/ws/`. The old guard fell to this witness precisely because `find` is position-free; `starts_with` is not.

The member CHECK searches the raw *input* fixture bytes, which are constructed literally at claude:563-568 / codex:531-539 and never contain any filesystem path — the workspace path only ever appears in *output*, injected by the rewrite. So the witness is not in the searched buffer at all. And even if it were, the needle is `\/ws` with a leading backslash; the directory name `workspace` contains no backslash and cannot supply one. Doubly immune. Adversarial construction: rename the workspace directory to `/ws` itself and the predicates are still unaffected, because neither reads it — this is the structural fix, not a fixture accident.

*False witness B — the sealed, never-rewritten JSON key `"/ws/proj"`.* Immune to both.

The prefix CHECK does not read member bytes, so the key cannot reach it.

The member CHECK is the interesting one, and it is immune by encoding. The key is spelled with a bare solidus — `{"/ws/proj":"key-must-not-change"` — while the computed needle is `\/ws`, four bytes beginning with a backslash. A bare `/ws` cannot satisfy a search for `\/ws`. I walked both fixture lines byte by byte for other occurrences: in the claude fixture the only `\/ws` is inside `"cwd":"\/ws\/proj"`, and in the codex fixture likewise the only one is inside the `payload.cwd` value. So the single site that satisfies the predicate is exactly the escaped *string value* — the one the rewriter decodes and rewrites, per the sibling coverage at claude:526-551 which pins that `\/` and `p` decode and that values rewrite while keys do not. That is the right site: the guard now asserts the fixture carries the carrier in a form the rewrite path would actually act on, which is what makes the byte-identity comparison meaningful rather than decorative.

*Third defect from the original finding — a `/zz` carrier left the guard green.* Closed. Both predicates now derive from `kEngagedCarrier`, and the same constant builds the engaged `PackerHome`. The `/zz` edit turns both red in both TUs, which is the four-site evidence.

**One honest limitation, stated so it is on the record rather than discovered later:** these are self-consistency assertions over the fixture and the record, not observations of product behavior — see INFO-3. They are the correct instrument for the non-vacuity job and they close what I raised, but they are not a behavioral pin on the carrier.

---

## Grading the pasted four-site RED evidence

I checked whether the source at 0ab998d can produce exactly the pasted output — no more failures, no fewer — and it can.

**Line attribution: all four exact.** The report quotes claude:571, claude:583, codex:542, codex:554. At 0ab998d, claude:571 and codex:542 are the single-line prefix CHECKs. The member CHECKs are three-line macro invocations spanning claude:581-583 and codex:552-554, and Catch2 takes `__LINE__` at the end of the macro invocation, so 583 and 554 are the correct attributions. Worth noting because a report written from memory rather than from a run would most plausibly have quoted the macro-name lines 581 and 552; these are the closing-paren lines.

**Failure count is forced to be exactly four.** `kEngagedCarrier` is a case-local constant in each TU with exactly three uses. Two of them are the CHECKs, which both go false under `/zz` with the fixture unchanged: `"/ws/proj".starts_with("/zz/")` is false, and the needle becomes `\/zz`, which is absent from fixture bytes that still spell `\/ws`. The third use feeds `target.packer_home` — and since no adapter reads that field (INFO-3), the engaged arm's installed files, contents, and id-map shape are bit-identical whether the carrier says `/ws` or `/zz`. So the mutation cannot perturb the four `install_receipt` validity REQUIREs, the per-file emplace REQUIREs, `REQUIRE_FALSE(files.empty())`, codex's rollout-filename REQUIRE, or any of the four cross-arm equality REQUIREs at claude:640-644 / codex:615-619. Nothing else in either TU references the constant, and the constant is not visible outside its own TEST_CASE, so no other case in the binary can be disturbed. Exactly four, in exactly those two cases. `test cases: 2 | 0 passed | 2 failed` follows, since each case carries two of the four.

**The assertion arithmetic reconciles, and it reconciles in the way that matters.** The RED run reports 62 assertions with 58 passed and 4 failed. The report's separate GREEN run of the same filter reports "62 assertions in 2 cases", all passing. That the *total* is identical across both runs is the proof, and it is a proof specifically that the plan's non-fatal requirement was honored: because both predicates are `CHECK`, a failure does not abort the case, so every downstream assertion still executes and the total is invariant under the mutation. Had either predicate been `REQUIRE`, each case would have aborted at its first failure, the RED total would have collapsed far below 62, and a run reporting a full 62 with 4 failures and 2 failed cases would be impossible to produce. 58 + 4 = 62 closes it.

I will be straight about the limit of this: I did not independently derive the absolute number 62 from the source. Doing so requires knowing how many files each install writes at runtime, and the count also folds in assertions inside the helpers rather than the case bodies — `read_text` carries a `REQUIRE(input)` (claude:139-143, codex:94-98), `replace_all` carries a `REQUIRE_FALSE(token.empty())` reached twice per file through `normalize_minted_ids`, and codex's `normalize_rollout_clock` adds five REQUIREs per `sessions/`-rooted path (codex:57-70). I am read-only and did not build, so the file counts are not available to me statically. What I did verify — invariance of the total across RED and GREEN, and that the source forces exactly four failures and forbids any fifth — is the part that actually discriminates a real run from a constructed one, and both hold.

**Exit code 42 checks out, and I want to correct an assumption I nearly filed as a finding.** My first reading was that Catch2 returns the failed-assertion count clamped to 255, which would have made 4 the expected status and 42 a discrepancy. That is Catch2 v2 behavior. This repo pins Catch2 v3.7.1 (`CMakeLists.txt:27-30`), and v3.7.1 returns a fixed `TestFailureExitCode = 42` for any nonzero failed-assertion count — `_deps/catch2-src/src/catch2/catch_session.cpp:37` defines the constant and `:356` returns it. So 42 is exactly right for this binary. It also means the exit status carries no count information: it corroborates "something failed" and nothing more, and the failure count rests entirely on the printed summary. That is fine here, but it is the same shape as the STOP-text/exit-status lesson, pointed the other way — worth keeping in mind before anyone reads a Catch2 exit code as a magnitude.

**No collateral breakage.** I checked the one plausible route: `PackerHome{"/zz", posix}` is constructed directly by the test, bypassing `make_packer_home`, and `packer_home_valid` is only consulted on the manifest write and parse paths (`src/core/manifest/manifest.cpp:475,537,646`), never during install. So the mutation cannot flip an install outcome and cannot reach the manifest tests.

---

## MFX-2

Closed as prescribed. `tests/test_pack.cpp:267` now reads `CHECK(report->agent_sessions.empty());`, placed immediately after `require_store_roots_under(*report, root)` at :266 and before the pre-existing `none_of` at :268-271, which is retained. Both are fine to keep.

The placement matters and it is right. `require_store_roots_under` (test_pack.cpp:206-219) is a bare `for` loop over `report.agent_sessions` with its four REQUIREs inside the loop body — it contributes exactly zero assertions when the vector is empty, which was the original defect. The `none_of` immediately below is likewise a universal quantifier over the same empty vector and is vacuously true. So before this fold the decoy block's entire post-state was two quantifiers that could not fail. The new CHECK is the only assertion in that block that actually pins the outcome, and it is now stated positively: the ambient-HOME decoy store at `decoy_home/".codex"` must not be discovered at all, not merely "must not appear among whatever was discovered." Correct expectation, correctly placed, non-fatal so the two surviving quantifiers still evaluate.

---

## Fold-introduced defect hunt

**The escaped-needle loop.** Correct for `"/ws"`: leading `/` is escaped, yielding `\/ws`, and the `\` is appended before the `/` in the right order (claude:574-577). Leading-slash handling is correct — the loop does not special-case position, and JSON `\/` is a valid escape for solidus in any position, which is exactly how the fixture spells it. Empty-needle production is possible only from an empty constant, which is INFO-1. No other carrier shape produces a silently-passing needle: `"/w"` and `"ws"` both leave the prefix CHECK red, and `"/ws/proj"` leaves both red (INFO-2).

**`std::search` usage and types.** `raw_member` is `const std::vector<std::byte>&` bound to a mapped value of the non-const `members` map, so `.begin()/.end()` yield `const_iterator`. `escaped_member_bytes` is `const std::vector<std::byte>`, same iterator category and same value type. `std::byte` is a scoped enum with a defined `operator==`, so the default binary predicate is well-formed. Both TUs include `<algorithm>` (claude:1, codex:1) and `<string>`/`<string_view>`, so `std::search` and `starts_with` are declared. The comparison against `raw_member.end()` uses the same range's end, not the needle's — a classic slip that is not present here. Under the project's `-Wall -Wextra -Werror` (`CMakeLists.txt:125`) I see no new warning: the loop variable is `const char` over a `string_view`, which yields `char` exactly, and there is no shadowing of an enclosing `value`.

**`bytes(...)` conversion.** `bytes` takes `std::string_view` and returns `std::vector<std::byte>` (claude:122-129, codex:86-93), each `char` widened by `static_cast<std::byte>`. Passing the `std::string` needle converts implicitly. This is the same function that built the fixture bytes being searched, so needle and haystack are produced by identical byte semantics — no signedness or encoding mismatch between the two sides. That is the right choice; a `std::string`-side search against a `std::byte` buffer would have needed a reinterpret and would have been the place a bug hid.

**New vacuity.** None beyond INFO-1. I specifically checked whether either CHECK could pass for a reason unrelated to the carrier: the prefix CHECK is anchored and boundary-terminated, so only a genuine strict-prefix relationship satisfies it; the member CHECK has exactly one satisfying site in each fixture and that site is the rewrite-eligible encoded value.

**Did removing the output-side guard lose coverage that mattered?** No. The removed `REQUIRE` asserted that some retained output still contained `/ws`. Its only witness that was not the workspace directory name was the immutable JSON key — and that key's survival through install is separately and directly pinned elsewhere, at `tests/test_adapter_claude_install.cpp:677` and `tests/test_adapter_codex_install.cpp:658` (`CHECK(installed.find("\"/ws/proj\":\"key-must-not-change\"") != npos)` in the "rewrites escaped values without changing keys or numbers" cases), and at the rewrite-unit level at claude:538. So every genuine behavior the old guard could have observed is still pinned by an assertion that can actually fail. Removing it lost only its two false witnesses.

**Scope creep.** None. `git diff --name-only d234314..0ab998d` returns exactly the three test files, +31/-12. No production source, no fixture, no manifest test, no workflow, no build-system, design, plan, parity, or fence file. Consistent with the completion report.

---

## Grading the two disclosed aggregate concerns

Neither changes my verdict, and both should be tracked rather than closed.

**(a) The pinned-executable probe failure that did not reproduce in isolation.** This does not affect the verdict on this diff. The affected TU is outside the three changed files and the patch touches nothing it depends on — no production code changed, so the probe's subject is byte-identical to baseline. But I want to be explicit that "passed when run alone" is not a disposition. My prior guidance stands unchanged: *did not reproduce is not diagnosed*. A failure that appears in the aggregate run and vanishes in isolation is the signature of cross-case state leakage — shared temp roots, environment variables restored out of order, or ordering dependence on a pinned executable path — and the isolated re-run is precisely the instrument that cannot see any of those, because it removes the conditions that produced the failure. Passing it is therefore consistent with both "flake" and "real order-dependent defect," and it discriminates between them not at all. This belongs in the harness lineage as an open, undiagnosed item with the aggregate run's ordering recorded, not marked resolved by the isolated pass. It is not this branch's debt and it is not a reason to hold this branch.

**(b) The inherited harness-e2 180s wrapper timeout.** Already-ruled stale-ceiling class, and the disclosure carries the right evidence: the underlying harness command exits 0 past the wrapper budget, and the baseline *before* the patch reproduces the same timeout. Since the commit is test-only and changes neither the `biv` binary nor any harness or timeout configuration, this cannot have been introduced here. Correctly disclosed rather than suppressed. It should remain tracked in the harness lineage against the stale-ceiling residual until the ceiling is raised or the harness is made faster; it does not gate this micro-fold.

I note approvingly that the completion report declines to call the full gate green while these are open, and holds push, PR update, remote CI, merge, publication, and release. That is the correct posture and I am not asking it to change. My pass verdict is scoped to the three-file diff and to the two findings I gated it on; the aggregate gate remains the lead's call.

---

## Summary of confirmations

- MFX-1 (CRITICAL): CLOSED. Both new predicates are coupled to `kEngagedCarrier`, which also builds the engaged `PackerHome`; both are immune to the workspace-directory-name witness and to the immutable-JSON-key witness, by anchoring and by encoding respectively; both sit before the installs; the output-side `find("/ws")` guard is deleted in both TUs.
- MFX-2 (MEDIUM): CLOSED. `CHECK(report->agent_sessions.empty())` at test_pack.cpp:267, after `require_store_roots_under`, with the pre-existing `none_of` retained.
- Mutation evidence: RECONCILES. Four line numbers exact including closing-paren attribution; exactly four failures forced by the source with no fifth possible; totals invariant at 62 between RED and GREEN, which independently confirms the predicates are non-fatal; exit 42 is Catch2 3.7.1's `TestFailureExitCode`.
- Defect hunt: no Critical, Important, or Minor findings. Three informational items recorded above; none is a fix condition.
- Scope: exactly the three authorized test files.
- Aggregate concerns: correctly disclosed, do not affect this verdict, and should be TRACKED in the harness lineage rather than closed — "did not reproduce" is still not "diagnosed."

Files reviewed at 0ab998d: tests/test_adapter_claude_install.cpp, tests/test_adapter_codex_install.cpp, tests/test_pack.cpp. Supporting reads: src/adapters/adapter.hpp, src/core/open/sessions.cpp, src/core/manifest/manifest.cpp, CMakeLists.txt.
```

---

## LEAD SYNTHESIS

Lens verdict (bare): **pass** — "No further byte is requested"; zero Critical/Important/
Minor findings; three informational items, none a fix condition.

**VERIFICATION VERDICT: PASS — the human-lens six-must-fix window is CLOSED at
`0ab998d`.** MFX-1 closes with an explicit false-witness immunity analysis rather than
an assertion of closure: the prefix predicate is immune to the workspace-directory
witness by ANCHORING (`starts_with` at position 0 with a component-boundary `/`, versus
the position-free `find` that fell), and the member predicate is immune to the
immutable-JSON-key witness by ENCODING (the computed needle `\/ws` leads with a
backslash the bare key `"/ws/proj"` cannot supply) — and immune to the workspace
witness twice over, since it searches raw INPUT bytes that contain no filesystem path
at all. The lens constructed the adversarial cases (including renaming the workspace
directory to `/ws`) and showed the predicates unaffected, which is what makes this a
structural fix rather than a fixture accident. The single satisfying site is exactly
the escaped string VALUE the rewriter would act on — so the byte-identity claim is now
made over a fixture where carrier-conditional rewriting could actually manifest.

**The mutation evidence reconciles, and the lens proved the non-fatal requirement from
the arithmetic:** all four quoted line numbers are exact including the closing-paren
attribution of the three-line macros (the tell of a real run rather than a report
written from memory); the source FORCES exactly four failures and forbids a fifth
(the constant's third use feeds a write-only field no adapter reads, so nothing else
can move); and the assertion TOTAL is invariant at 62 between the RED and GREEN runs —
which is only possible if both predicates are non-fatal, since a `REQUIRE` would have
aborted each case at its first failure and collapsed the total. The lens also caught
and CORRECTED its own near-finding: it nearly filed exit-42 as a discrepancy on Catch2
v2 semantics before verifying this repo pins v3.7.1, where 42 is the fixed
`TestFailureExitCode` — and noted the corollary (a Catch2 exit code carries no
magnitude, the inverse face of the STOP-text lesson). It was equally straight about
what it could NOT do read-only: it did not derive the absolute 62 from source, and said
so, resting the verdict on the invariance and the forced-four instead.

**MFX-2 closes** with the right diagnosis: the block's two surviving quantifiers
contribute zero assertions over an empty vector, so the new CHECK is the only assertion
that pins the outcome — and it states the expectation positively (the decoy must not be
discovered AT ALL, not merely "must not appear among what was discovered").

### Informational items (recorded; none a fix condition)

- **INFO-1:** empty-carrier vacuity remains theoretically open (an EMPTIED constant
  makes both predicates trivially true) — same class as MFX-1 by a different edit,
  unreachable by any realistic edit path; a one-line `static_assert` would shut it.
  **Registry candidate; deliberately NOT re-opening a hash-bound cycle for it.**
- **INFO-2:** the needle transform models solidus escaping only, so widening the
  constant to `/ws/proj` would fail for an ENCODING reason (the fixture spells `p` as
  `p`) — fails loud, not silent; recorded so a future widener does not lose time.
- **INFO-3 (the honest scope statement):** `packer_home` is write-only on the install
  path — no adapter reads it — so the byte-identity REQUIREs are true by construction
  today. These predicates are FIXTURE NON-VACUITY guards, not a behavioral pin on the
  carrier, and must not be cited as one. This is the correct and intended scope.

### Aggregate concerns — graded, tracked not closed

Both sit outside the diff (three test TUs feeding neither the `biv` binary nor the
harness). (a) The pinned-executable probe failure that vanished in isolation: the lens
restates its standing guidance — **"did not reproduce" is not "diagnosed"** — with the
sharpest statement of it yet: a failure present in the aggregate and absent alone is the
signature of cross-case state leakage, and the isolated re-run is precisely the
instrument that CANNOT discriminate flake from order-dependent defect, because it
removes the conditions that produced it. Tracked in the harness lineage as OPEN and
undiagnosed with the aggregate ordering recorded; not this branch's debt. (b) The
inherited `harness-e2` 180s wrapper timeout: the already-ruled stale-ceiling class,
reproduced at the pre-patch baseline, underlying harness exits 0 past the budget;
tracked against the stale-ceiling residual. Neither gates this fold. The lens noted
approvingly that the completion declined to call the full gate green while these are
open — the lead concurs and preserves that posture in the hand-up.

### Disposition

The six human-lens must-fixes are now ALL proven closed (five at `d234314`, the two
gating repairs at `0ab998d`). The merge hand-up follows this record, carrying: the
six-fold proof, the four sealed record hashes plus this one, the three informational
items, the two tracked aggregate concerns, the standing end-state-bytes condition-3 at
the eventual merge base (this branch predates C/B2 at `6047ab03`), and one item the
hand-up must not omit — **the published PR #24 is STALE at `2341667`, two commits
behind the reviewed head; republication of `0ab998d` is owed under a separate P5 token
BEFORE any merge can act on reviewed bytes.** The branch stays local-plus-stale-published;
the release hold is ABSOLUTE.
