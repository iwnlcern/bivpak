# Merge packet — sub-step 1 consent-UX fabric (assembled 2026-08-28, held at completion)

Assembled by `intg.pair-planner` under master's ASK-1 ruling (`master/relays/intg-substep1-master-answers/PLAN-master-planner-20260828-190918.md`):
the packet assembles in parallel with the m-3 count-gate repair; it does not queue behind it.
This document is the packet of record.
It carries NO merge authority; the token is the operator's alone.

## 1. Candidate identity

- Branch: `intg/consent-fabric@3cd31e4823d40c1c9ea020fcb51917618368533b`
- Base: `main@02b51435a5b50363df7f595dd827af107424b0c3` (= the merge-base, measured; no hidden lineage)
- Series: exactly 4 commits, all authored `intg.pair-implementer`:
  `0734f03` (flag + help golden) → `11e3b3b` (the ONE-COMMIT contract landing, V-A6-3) → `4ce1a1f` (a6.15 zero-state leg) → `3cd31e4` (PROMPT D renderer module).
- Changed paths: exactly 18, byte-equal to the plan fence; engine diff from base EMPTY (`git diff 02b51435..HEAD -- src/core/repo` = 0 bytes).
- Sealed sources implemented: `m3-addendum-6-c41d015f-lock-20260825` (rev14 fabric), `m3-addendum-7-4c40fe37-lock-20260827` (S5-S7 TTY rules), STOP-1 golden-byte ruling `intg-stop1-a6-golden-bytes/DESIGN-planner-20260827-235912.md`.
- Plan of record: `plans/PL-intg-substep1-20260827.md` @ sha256 `403b3c95bdce875be5a0111a82b47d91168b2aa53964364166309c0403e4b9b4` (revision 12; approved exact-hash at `intg-substep1-plan-review-11`).
- Engine: UNWIRED throughout (the renderer has zero production callers — verified by grep and by the panel; the consumer is sub-step 2b behind m-4's reachability gate).

## 2. Evidence chain (all at the exact SHA)

- Implementation: `intg-substep1/SITREP-pair-implementer-20260828-045956.md` (implementation-complete, accepted).
- Task-5 battery: `IMPL-pair-implementer-20260828-152108.md` (first run, blocker → rev12) and `IMPL-pair-implementer-20260828-184407.md` (rev12 rerun): fence aggregate rc=0; `[a6-fabric] --success` 127 assertions / 12 cases green on macOS AND Linux; selftest 6 passed; four-phase Linux parity receipts green (exact-tree clone receipt `rev-parse == 3cd31e4`, suite uid 1001, R-4.31(a) nofile raise, harness venv before configure); `repo_engine` green under the rev12 frozen command.
- Plan-review lineage: eleven reviews, final APPROVE at exact `403b3c95` (`intg-substep1-plan-review-11`).
- The panel record: §5 below (condition 1 of the bar).

## 3. Registered residual reds — disclosed verbatim, with row attributions

**The count gate is NOT cited as merge-readiness evidence anywhere in this packet.**
Both reds ride disclosed under their registered rows; neither is converted to green; neither is waived.

1. **R-4.35** (registered pre-existing flaky mutation-adversary family; attributed to NO candidate; correctness half = R-4.36, m-4's row). Linux `harness-selftest` rc nonzero: `3 failed, 996 passed, 3 skipped` — members `test_file_reader_rejects_same_size_cross_chunk_in_place_rewrite`, `test_c1_zero_session_control_reds_on_file_inserted_at_scandir_stop`, `test_credential_scanner_detects_entry_added_after_directory_enumeration`. Membership churn from the first run's `4 failed, 995 passed` is recorded on the row (fourth+fifth samples, master 2026-08-28).
2. **R-4.38** (the single-binary count gate; owner m-3; repair designed D1-D4; re-anchored due point 2026-08-26: binds before any PUSH/PUBLICATION and before the gate is CITED). Linux count-read rc 1: `observed 399/0/0/1 vs want 412/0/0/1` (`s2-harness.yml:272`) — reconciled on the row: `412 − 25 (registered probe split) + 12 (this candidate's new a6-fabric cases) = 399`; skips 1 = 1. Ordering synergy recorded by master: intg merging BEFORE the (D3) observed-runs transcription is the repair-friendly order.

macOS raw-CTest observations (host-environment-keyed, mechanism files outside the candidate census, byte-identical at base): the credential-env tripwire firing on real host env vars (controlled clean rerun: 1003 passed), and `readelf` absent on macOS. Recorded, not candidate-attributed.

## 4. Blast radius (measured, not assumed)

- `git merge-base main intg/consent-fabric` = `02b51435` (the declared base).
- Branch delta: `git rev-list --count main..intg/consent-fabric` = 4.
- Local main has advanced 44 docs/relay-lane commits since the base; conflict surface `git merge-tree` = **0 overlapping paths** (product paths vs relay/docs paths disjoint) — a clean true-merge.
- **The merge publishes nothing.** The eventual push would carry local main's unpublished lineage (683 commits at assembly time; cut-point cell `rev-list --count origin/main..intg/consent-fabric^` = 642) and remains behind R-4.46 AND the re-anchored R-4.38 due point regardless of this merge.

## 5. Condition 1 — the adversarial panel record (run 2026-08-28 at exact `3cd31e4`)

```text
PANEL_CHOSEN: team-of-5
DEFAULT_ROLES_CHANGED: no
WHY_THIS_PANEL: C++/systems baseline (ARCHITECTURE.md merge bar); production-risk
  consent surface; FIRST full panel of this branch, sized against the whole
  cumulative diff from base (panel-at-SHA rule 2)
ROLES:
- security — consent-bypass/TTY-stream/injection surfaces on a consent-critical renderer
- performance — envelope writer hot paths, zero-divergence cost
- test-coverage — golden byte-wholeness, row-bound carriers, false-green audit
- correctness — sealed-text conformance, one-commit contract, exit composition
- idiomaticity — C++ RAII/lifetimes/headers vs project idiom (tidy-22 blind spots)
```

Verdicts: security **must-fix** (1 Major + 2 nits) · performance **approve** (1 nit) · test-coverage **optional** (3 Minors, test-file-only) · correctness **approve** (0 findings; independent E2 re-runs at the SHA: `[a6-fabric]` 127/12, `od -c` golden bytes vs STOP-1, one-commit `git show --stat`, schema parity, blob pins) · idiomaticity **approve** (5 nits).

### Consolidated findings

**SEC-1 (Major, must-fix; VERIFIED at the pair-planner's own bytes; disposition OWNER-ROUTED — sealed text):**
`src/cli/url_consent.cpp:13-45` — all five renderers substitute `facts.op/repo/requested/effective` and `relpath` into terminal output with NO control-character escaping, while the landed consent surface escapes C0/DEL/C1 via `display()` (`src/core/open/render.cpp:57-77`, `sanitize_utf8` + `\u00XX`).
Once wired, `effective` derives from repo git config (the registered F-URL-1 attacker surface), so hostile CR/ESC bytes could visually rewrite the consent prompt a user then ratifies.
**No live exposure at these bytes** — the renderer is unwired by design and every production caller is absent (verified).
The renderer literals are SEALED m-3 bytes: the pair cannot fold this unilaterally.
Required disposition (the panel's words): before sub-step 2b wiring, the design owner rules — escape the substituted VALUES inside the renderers (golden tests use clean fixtures; template bytes unchanged), or seal a documented, test-pinned caller-sanitizes precondition. An undocumented precondition on a consent-critical surface must not be the resting state.
**Routed with this packet into the m-3 byte-review lane at this same SHA; whether it conditions THIS merge (vs binding at 2b wiring) is the owner's and master's call — the pair neither blocks on it unilaterally nor launders it to a non-blocker.**

**Minors (test-coverage; test-file-only, ~6 lines total, no sealed-byte contact; folding any produces a new SHA and owes a targeted fresh panel per the panel-at-SHA rules):**
- TC-1 `tests/test_envelope.cpp:237,245` — parity find-after-position idiom leaves a one-direction false-green if `UrlDivergenceRefused` regressed 3→2; landed bytes verified correct; fold-in: two literal exit pins.
- TC-2 `tests/test_envelope.cpp:830,838` — one-grouped-object claim mutant-distinguishing only on pack (2 entries); fold-in: second accepted entry on the open arm.
- TC-3 `tests/test_envelope.cpp:879-885` — `exit_for_open` max-composition cell (both sources nonzero) unwitnessed; today mutant-equivalent (sessions codomain caps at 2, verified); fold-in: one nonzero-sessions arm.

**Nits (non-blocking, recorded):** the `exit_for_open` per-row loop that is semantically an emptiness check (flagged independently by three lenses; `envelope.cpp:498-506`); declaration-home drift (`exit_for_open` declared in `envelope.hpp` while siblings live in `exit_map.hpp`); positional-init fragility of the four-string `UrlDivergenceFacts` aggregate (prefer designated initializers at the 2b wiring site); test formatting; redundant `{}` member initializers; CRLF `y\r` refuses (fail-closed; a WSL-terminal question for 2b); two correctness nits (assignment-style test init; exit-map alignment padding).

**2b-due obligations surfaced by the panel (for the wiring gate's record):** SEC-1's disposition + a hostile-bytes-in-facts verification leg; confirm the human (non-JSON) open summary surfaces refusal rows; replace `main.cpp:277`'s inline isatty conjunction with the new predicate (dedup).

### Synthesis verdict

No `block`. The one `must-fix` (SEC-1) is sealed-byte-bound and owner-routed; every other finding is optional/nit.
**Packet: structurally merge-gate ready; SEC-1's disposition = owner/master decision, pending in the m-3 byte-review lane.**
Recommended handling of fold-ins: hold this SHA; defer the test-only Minors to a directed fold or to 2b (any fold = new SHA = fresh targeted panel + re-run owner predicate).

## 6. The condition census (the four-condition bar, R-4.30 commissioned-pair recast, + the owner predicate)

```text
condition 1  adversarial panel at the exact SHA — DONE (§5; record complete)
condition 2  visibility CC — master.master-reviewer + m-3.planner + m-3.implementer
             CC'd on the packet relay (visibility, not approval)
condition 3  VERIFIED at master's own bytes (record: master/relays/
             intg-substep1-master-answers/PLAN-master-planner-20260828-212827.md —
             head/base/merge-tree/delta/packet-face all independently re-derived,
             not the pair's report re-trusted)
condition 4  the operator's DISPATCH MERGE, PHASE: MERGE-GATE, issued directly —
             PENDING; sought only after the owner predicate returns; nothing in
             this packet is or substitutes for it
owner gate   SATISFIED — m-3 byte review at exact 3cd31e4 returned
             BYTE_REVIEW_VERDICT: green-no-veto (master/relays/
             intg-m3-byte-review-3cd31e4/DESIGN-REVIEW-implementer-20260828-220220.md,
             SEC1_FENCE_RULING: fenced-raw-substitution), and the A6/A7 authoring
             seat CONCURRED WHOLE (intg-sec1-m3-owner-concurrence/
             DESIGN-planner-20260828-225500.md — the seal's omission owned at that
             pen; SEC-1-2B-PRECONDITION adopted as a standing m-3 veto, registered
             R-4.48); both relays verified at the pair-planner's own read; no other
             domain's fence was routed by master
```

The release hold is ABSOLUTE and untouched by any of the above. Merged is not pushed, not published, not released.

## 7. Hold

Assembled and HELD. Condition 3 verified (master `212827`). Owner predicate SATISFIED (m-3 `220220` green-no-veto + authoring-seat concurrence `225500`; census complete recorded at master `021404`). **The ONLY remaining gate is condition 4 — the operator's merge token, issued directly; master surfaced the decision to the operator.**

SEC-1 disposition of record: fence-not-silence; renderer-owned escaping selected (caller-sanitizes rejected); a HARD 2b PRECONDITION registered as **R-4.48** — no production caller or engine-hook wiring of the raw renderer API before its five cells discharge (the joint m-3+m-4 re-cut is dispatched); SEC-1 binds NOTHING at this candidate. The three test-only Minors DEFER to the 2b lane (the green-no-veto arm of master's `212827` contingent rule). The eventual push stays behind the R-4.38 repair + R-4.46 regardless of the merge.

If the token issues: the merge is a LANE-LOCAL act (merge ≠ push ≠ release) executed per §4's recorded topology, reported UP with post-merge receipts. The release hold is ABSOLUTE.

## 8. Landed (2026-08-29)

Condition 4 issued: the operator's authorization of record `MERGE-GATE-operator-20260829-044640.md` ("Ok, merge it" quoted on the face) + the grammar-compliant token carrier `MERGE-GATE-operator-20260829-045944.md` (FROM operator, TO intg.pair-implementer, bare token; sha256 `37d0a67a…`; re-issued after the pair-planner's transport-grammar STOP `045104` — relay-lint.py:1170's grantor set excludes the pair-planner, measured at source).

Merge executed by `intg.pair-implementer` (claim `SITREP-pair-implementer-20260829-052523.md`), every cell independently re-verified by the pair-planner:

```text
merge        81066effff52ee97a7dcaf77ae45d06547f26f1c  (local non-ff true-merge)
parent 1     1696b9eb85b8021bdc12bb571fa6e4fabcfd3499  (main-before)
parent 2     3cd31e4823d40c1c9ea020fcb51917618368533b  (the candidate, exact)
tree         24c6189eab9c2a2f48e068ef4f80a3e5f2754d2f  (= the pre-merge merge-tree
             prediction; conflict-free)
identity     product-root diff candidate..merge EMPTY — the landed bytes are the
             battery-verified bytes
landed E2    build PASS; [a6-fabric] 127/12 PASS; schema contract 101/1 PASS;
             a6.17 pytest 3 PASS (implementer's fresh serial run on the landed tree)
reds         R-4.35 (3f/996p/3s) and R-4.38 (399/412) RETAINED, disclosed, uncited
remote       origin/main untouched at 0db8fdd; no push/PR/remote CI/publication/
             deployment/seal/release
```

MERGED IS NOT PUSHED, NOT PUBLISHED, NOT RELEASED. Push stays behind the R-4.38 repair + R-4.46 (operator-gated). R-4.48 fences sub-step 2b. The three test-only Minors remain deferred to the 2b lane. The release hold is ABSOLUTE.

Landing RECORDED at the registry (master `intg-substep1-master-answers/PLAN-master-planner-20260829-053801.md` — all four landed cells re-derived at master's own bytes, equal; both token-grammar drafting defects owned at master on the filed successors; the R-4.38 transcription-ordering carried to m-3.planner). **Sub-step 1 COMPLETE.** 2a and 2b open only on routed-UP acts and fresh master answers; a second plan would terminate W-3.
