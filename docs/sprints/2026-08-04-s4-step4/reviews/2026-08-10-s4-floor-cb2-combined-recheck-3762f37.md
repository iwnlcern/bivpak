# COMBINED re-check — C `b8083be` / B2 `3762f37` (option (a) Branch B)

Three read-only lenses over committed bytes. **Combined scope**: the union of the `e0d6c19` partial delta and
the option-(a) delta, adjudicated per-file against the end-state baseline captured before the fold.

| Lens | Verdict |
|---|---|
| Containment (ratified value-class scope) | **PASS** — 1 LOW, 1 INFO |
| Round-trip / functional acceptance | **PASS** — 1 MEDIUM (instrument), 3 LOW, 1 INFO |
| Tests / re-targeting honesty | **PASS** — 2 MEDIUM, 3 LOW, 1 INFO |

**PANEL VERDICT: PASS. The pair is bar-ready.** No Critical or Major survives; nothing found is a
regression against the pre-fold state; the acceptance instrument is genuine.

## Per-file carry adjudication (independently reproduced by the convener)
Of the 17 cumulative C→B2 paths, **12 hash-match the `e0d6c19` baseline and carry mechanically**; **5 are
FRESH and were reviewed at `3762f37`**. My determination matched the implementer's file-for-file — the value
of capturing the baseline BEFORE the fold is that the disposition was a lookup on both sides rather than an
argument. FRESH: `src/adapters/claude_code/install.cpp`, `tests/test_adapter_claude_install.cpp`,
`tests/test_adapter_claude_collect.cpp`, `tests/test_pack.cpp`, `tests/test_sessions.cpp`.

## The acceptance instrument — GENUINE (the finding that matters most)
`test_pack.cpp:1568` drives THREE REAL production legs — `run_session_leg` (consent-NO staged install) →
`biv::pack::pack` (real archive writer AND real staged re-collector) → `install(Consent::yes)` — with the
packed manifest's `children[]` **re-derived by production code**, not carried from the fixture. It is
falsifiable in BOTH directions: reintroduce the mint and the `senderTaskId`/id_map assertions fail; rename
the child file instead and the filename-located lookup fails. Parameterized over all three real classes
(flat bare-hex, flat slug-hex, nested bare-hex under `subagents/<wf>/`), closing the flat-only 34% gap.
**This is the first instrument in this band that measures whether a restored session WORKS rather than that
we merely failed to corrupt it.**

## Containment — the contained side did NOT relax (verified line-for-line)
`image_origin_path_set` construction, the per-session pair set, all four `verify_*` call sites and the
`origin_path` refusal gate are unchanged from PRIOR. Union membership lost EXACTLY the two ratified classes
(child origin ids, `agentId` aliases); primary, parent, artifact-derived session identities, message-uuid
origins and every path origin remain — the last two are now *over*-contained relative to the ratification,
which is safe. Dead-code removal is clean (zero repo-wide occurrences; no function lost a needed caller).
**The strongest argument, which the fold did not make:** the child origin id was NEVER contained — the
destination is `<installed_session_id>/subagents/<child.original_id>.jsonl` verbatim, so the union was
claiming to scrub from content an id already written into the recipient's filesystem as a filename. The fold
aligns the id-map claim with what the bytes always did.

## CONVENER ERROR, owned: the `staged_path_caveats` "proof" is unfalsifiable
My corrected token (`220856` §1) told the implementer to assert, as a bonus, that the caveat lookup "can now
find the real child path — today it is a uuid nothing is named, so the lookup cannot succeed." **That premise
is FALSE and the round-trip lens refuted it.** `installed_ids` is seeded with the PARENT's
`installed_session_id` (`sessions.cpp:175`) and every child path is `<installed_session_id>/subagents/…`
(`install.cpp:205`), so the parent id alone satisfies the substring match — the caveat row is emitted
identically under minting or identity. `staged_path_caveats` was never broken. The implementer duly asserted
what I told them to, so their report's "sessions consumer proof" claim is not evidence and must be corrected
in the hand-up. **This is the second lens refutation of an inference of mine this run** (the first: a
severity-upgrading claim to the tests lens). The rule I keep re-learning: a planner's causal story is a
hypothesis until an instrument grades it, and mine rode into a dispatch as an instruction.

## Findings — all non-gating, all routed
**REGISTER → slice E (the caveat surface is a loud-install surface, and its file is C's, unchanged since C —
B2 must not touch it without breaking C's byte-identity):**
- **E-1 [MEDIUM, newly reachable]** A crafted manifest child `original_id` of one character becomes the
  identity pair `{"e","e"}` and floods `staged_path_caveats`, whose matcher is an UNANCHORED substring test
  (`sessions.cpp:186`) while `session_id_ok` (`agent_member.hpp:17-23`) accepts any non-empty slash-free
  string. Consequence is over-disclosure noise on the local user's own caveat list, not a leak — with
  `from == to` the rewrite is a provable no-op. Convener-measured: of **1705 real child stems, ZERO** carry a
  username, home directory, machine name or path shape, so the class does not occur in real data. Fix:
  anchor the matcher to path segments.
- **E-2 [MEDIUM, pre-existing, uncovered before AND after]** `ChildArtifactMatcher` (`pack.cpp:357-376`)
  matches a child id against ANY path segment, so a nested file whose stem equals a flat child's id is
  silently attributed to the flat child. Now load-bearing because the id is verbatim and it decides what the
  caveat surface discloses. Recommend a same-stem fixture.
- **E-3 [LOW]** `child_ids_for` is non-recursive, so the live collector never registers a nested subagent as
  a child — 1124/1702 files (66%) pack with no child row. Pre-existing; resolution does not depend on it
  (proved by the R-1 nested round-trip with `children` empty), but the nested arm of the acceptance test
  therefore models a staged-repack-shaped record rather than a live-collected one.

**RESIDUAL row (product, non-gating):**
- **R-a [LOW]** Duplicate-needle precedence disagrees between the two rewriters: if a child stem is also a
  message-uuid origin, `apply_replacements` (vector order) lets the MINT win in `.jsonl` while
  `rewrite_raw_text_bytes` (length-descending stable sort) lets IDENTITY win in `.txt` — so `.txt` fails
  closed via `verify-hits` and `.jsonl` re-dangles silently, on the same input. Implausible for
  `agent-`-prefixed stems; less so for the 25 nested-only `other`-shaped ones. No guard, no test.

**Test hygiene (implementer discretion, disclosed — NOT re-folded, to avoid breeding new bytes for zero
product risk):** the unfalsifiable caveat assertion (`test_sessions.cpp:1254-1259`) and the
`!= "child_identity_conflict"` check against a string that no longer exists (`test_adapter_claude_install.cpp:3435`)
should be deleted or repointed; no two-cycle test carries a child; install-side unit fixtures remain
flat-only and UUID-shaped (the reality-shaped coverage lives at the pack seam).

**Recorded decisions (not defects):** the leak gate no longer covers child origin ids, and four tests were
inverted from "refuses" to "installs", now asserting the scan's SILENCE as a positive property. The removed
`child_identity_shape` guard was the last value-class check; its class is measured absent from real data.
The claude/codex asymmetry is principled — codex derives the child rollout FILENAME from the minted id, so
renaming file and reference together stays consistent there; claude names the file with the child's own stem,
so identity is the only way to keep the index intact.

## Mechanical verification (convener)
One commit atop byte-identical C (tree `64d77cd`, as paneled); subject preserved; 17-path cumulative range;
option-(a) delta exactly the 5 declared paths; `child_ids` identity at `:722`; alias arm zero occurrences;
**stack merges CLEAN at every hop including onto LOCAL main** (which carries the B1 and slice-A merges the
implementer's remote-only trees do not cover); blast radius independently recomputed to **27**.

## Disposition
PASS → fresh paired hand-up, C-first / B2-immediate, carrying A10.3 (C never lands without B2), the measured
blast-radius line, the convener-error correction above, and the four routed items. Nothing seals; merge ≠
push ≠ release; the release hold is ABSOLUTE.
