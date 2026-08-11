# Targeted re-check — C `b8083be` / B2 `8b12b25` (G-1..G-4 fold)

Convened by `s4-floor.planner` on the implementer's REVIEW-FOLD (`170608`). Three read-only lenses over
committed bytes, scoped to the fold delta `2b5675a → 8b12b25` (5 paths). Two E1 scouts run by the convener
against the real claude store (read-only, identity/version fields only).

| Lens | Verdict |
|---|---|
| Containment / injection scope | **FAIL** — 2 CRITICAL, 2 MAJOR, 2 MINOR |
| Content same-set / round-trip | **FAIL** — 1 HIGH, 3 MEDIUM, 2 LOW |
| Tests / falsifier power | PASS on its own bar — 2 MEDIUM, 5 LOW; G-1 genuinely closed |

**Panel verdict: FAIL — one bounded fold. No hand-up.**

## THE PATTERN THIS ROUND (state it before the findings)

This fold added THREE new guards. Each encodes an assumption about what real agent data looks like. The
convener measured all three against real stores:

| guard | premise | measured | verdict |
|---|---|---|---|
| claude identity (prior round) | subagent body `sessionId` is the PARENT's | 1657/1695 parent, 38 absent, 0 own | **TRUE — guard stands** |
| G-4 alias needle (this round) | an unattributed subagent alias should refuse | 1124/1124 nested aliases unattributed, all present | **FALSE — refuses real sessions** |
| G-2 codex identity (this round) | `payload.session_id` names THIS rollout | 633/930 real rollouts have `session_id != id`; 626 = parent_thread_id | **FALSE — refuses 68% of real rollouts** |

**The rule is not "guards are fine because one measured true."** Every new guard needs ITS OWN premise
measured before it ships. Last round's scout vindicating the identity guard is precisely what makes this
round's two unmeasured premises dangerous — a validated sibling is not evidence.

## R-1 [CRITICAL, BLOCKING] G-4 needles an alias it never rewrites, so real sessions become uninstallable

Convener-verified at the bytes and INDEPENDENTLY reproduced by the round-trip lens (its finding 1). Chain,
every link confirmed at `8b12b25`:

1. `collect_subtree_artifacts` (`claude_code.cpp:261-302`) uses a **recursive** iterator → nested
   `<id>/subagents/workflows/<wf>/agent-x.jsonl` IS collected into the image.
2. `child_ids_for` (`claude_code.cpp:304-321`) uses a **non-recursive** `directory_iterator` → only FLAT
   `subagents/*.jsonl` stems become child ids. `manifest_entry_for` (`pack.cpp:378-395`) only ever attributes
   artifacts to those child ids (the `ChildArtifactMatcher` fallback runs per existing child), so a nested
   file whose stem has no flat twin is **always unattributed in a live-collected image**.
3. The new `subagent_jsonl_artifact` (`install.cpp:361-369`) matches ANY `.jsonl` under `subagents/`,
   including nested → the alias IS inserted into `image_origin_id_set` (`:887-893`).
4. The rewrite pair (`session.child_alias_ids`) is appended only inside the child loop requiring
   `child.artifacts` membership (`:894-910`) → the unattributed alias gets **no pair**.
5. `rewrite_jsonl_bytes` therefore leaves the alias verbatim; `verify_scan` is then **guaranteed** to hit it
   (the needle was extracted from that very file); `:995-999` sets `verify-hits`/`origin_id` and clears
   outputs → **the whole session is refused**, at BOTH consent modes. Hit probability 1.0, not a race.

**E1 SCOUT (real store, convener):** 1699 real subagent transcripts — 1124 nested, and **all 1124 carry an
`agentId`**; **all 1124 nested stems are absent from the flat enumeration**, i.e. 100% unattributed. Those
transcripts concentrate in **6 sessions of ~135 (≈4.4%)** — so the honest weighting is *not* "the majority
session shape" (an overstatement the convener made mid-review and corrects here) but **every session that
uses subagent fan-out via workflows, all of which are refused outright.** At PRIOR they installed.

**It is a deliberate choice, not an oversight** — the fold's own test asserts the refusal
(`test_adapter_claude_install.cpp:3010`, origin refused, `id_map.empty()`, store empty). **The convener owns
the framing error:** the `160025` token's G-4 falsifier was worded "an unattributed subagent alias IS
needled", which is literally what was built. Needling without minting can only ever self-refuse.

**Fix shape (round-trip lens, endorsed):** the product already mints replacements for message UUIDs found
anywhere in a body and pushes the pairs (`minted_message_uuid_pairs`). Mint a replacement per unattributed
subagent alias and push the pair — closes the leak AND preserves the round trip. This follows the
message-UUID precedent, creates no sidecar `id_map` row, and is therefore **pair scope, not an A9 shape
change**. The approving test must be re-targeted in the same pass.

## R-1b [CRITICAL, BLOCKING] G-2's codex guard has a FALSE PREMISE — it refuses ~2/3 of real rollouts

Found by the containment lens; **convener-verified against the real codex store**. The guard
(`codex/install.cpp:545-554`) requires a PRESENT `session_meta.payload.session_id` to equal **this
artifact's** `write.installed_id`. But `session_id` names the **parent/root thread**, not this rollout:

```
930 real codex rollouts (~/.codex/sessions):
  both id + session_id present ......... 777
    session_id != id  (guard REFUSES) .. 633   (68% of all rollouts)
      of which == parent_thread_id ..... 626
  id only .............................. 153
```

Trace: codex folds children into the parent's `SessionRecord` (`codex.cpp:1249-1263`) and mints a separate
rollout per child (`install.cpp:437-449`), so on a child artifact the rewriter **correctly** maps
`payload.session_id` (the parent's origin id) to the PARENT's installed id — which by construction differs
from the child's `write.installed_id`. **The guard refuses precisely the bytes the rewriter got right.**
Because codex folds children into the parent record, the refused "row" is the entire parent+children
family. Any packed codex multi-agent group hits this.

Fix direction (lens, endorsed): compare `payload.id` to `write.installed_id`, and validate
`session_id`/`parent_thread_id` against the installed id of the session they legitimately reference — the
parent's — not this artifact's. Also close R-6 (the `id` arm is untested) and F6 (the guard returns a
default `{}` when no `session_meta` line or neither key exists, so it silently passes exactly the artifacts
where identity evidence is missing — the recorded absence-blind shape; give absence its own disposition).

## R-2 [MEDIUM] Writer/reader version predicates diverge on a NON-STRING `version`
Reader (`inspect_transcript` via `object_string`) SKIPS an ill-typed value and keeps scanning later lines;
the writer (`install.cpp:324`) decides on the first line carrying the KEY and hard-refuses
`staged_version_unestablished`. A transcript with `"version": 7` on line 3 and a valid string on line 40 is
accepted by the reader and refused by the writer. The same file's `transcript_session_id` (`:281-302`)
treats a non-string as ABSENT and continues — the version path is the sole outlier. Align it.

## R-3 [MEDIUM] The injection branch skips the floor check its own present-branch enforces
`establish_transcript_version` refuses a PRESENT below-floor version but injects
`agent_version_at_pack` with NO floor comparison (`:337-352` vs `:324-330`) — the writer can produce a
workspace it would itself refuse on the next hop. A fence must apply one standard to both branches.
Checked and CLEAR: no JSON-escaping hole — `admit` runs first and `parse_grammar` restricts the value to
`[0-9A-Za-z.+-]`, so no quote or backslash can reach the insert.

## R-4 [MEDIUM] The injection is not consent-gated — it mutates the recipient's REAL store
`publish_root` is `target.target_store.root` under consent=YES (`install.cpp:682`); the injection at `:953`
consults no consent. So `biv open --consent yes` writes a synthesized `version` into the user's real
`~/.claude` transcript while the row still reports `content_rewrite = "pair"`. G-3 was a consent-NO
round-trip fix; this is broader than the defect required. Gate on `Consent::no`, or report the body mutation
honestly. **Realism, E1 SCOUT (convener, answering the lens's direct question):** of 135 real main
transcripts, 127 carry a `version` somewhere (119 on a LATER line — untouched by the fold) and 8 carry none;
**none of those 8 has a live `sessions/<id>.json` sidecar**, so `value_or("unknown")` → `admit` refuses them
as `basis_unorderable` before the writer runs. **The injection branch is not reachable from any observed
real session on the reference store** — it survives for foreign/older images only. Evidence from one store,
not a proof of impossibility; weight R-3/R-4 as correctness+hygiene, not live product breaks.

## R-4b [MAJOR] The injected value is the PACKER's version — wrong source, and it propagates
The injection passes `record.agent_version_at_pack` (`install.cpp:953-954`), so the recipient's transcript
is made to assert a version the session will not run under; the next pack reads it back
(`claude_code.cpp:708`) and freezes it into the manifest, hop after hop. Harm beyond misstatement:
`pack.cpp:576-590` OMITS below-floor sessions, so a frozen old version silently deletes the session from
future archives once the floor rises — whereas WITHOUT injection the next pack yields `"unknown"` and
refuses LOUDLY (`basis_unorderable`). Injection replaces a loud failure with a confidently wrong value.
Defensible source (lens, endorsed): the recipient's own `caps.agent_version()`, already in hand at
`:725`/`:750` — the version the session will actually resume under, which also keeps `admit`'s image ≤ host
comparison stable across hops.

## R-4c [MAJOR, pre-existing gap this fold would write into the store] `admit` never floor-checks
`version_floor::admit` (`version_floor.cpp:166-186`) checks parseability and image ≤ host but never consults
`min_line`, so install accepts below-floor images; combined with R-3 the writer can inject a below-floor
value into the recipient's REAL store, after which every future pack omits that session. The admit gap is
pre-existing (register it), but this fold is what turns it into a write.

**Scope ruling recorded (lens, and the convener agrees — do not stretch M-4):** a version string is NOT
packer identity. The governing origin-invariant ruling names path/id/key-shaped artifacts (derived paths,
session/message ids, object keys). R-3/R-4/R-4b/R-4c are **provenance-integrity** defects and must not be
filed as M-4 containment rows.

## Also fold (cheap, both lenses)
- R-5 [LOW] The typed refusal (`staged_version_unestablished` / `staged_identity_mismatch`) is overwritten
  by the post-loop verify relabel (`:995-999`); guard so the operator reads the cause that fired.
- R-6 [tests F1, MEDIUM] The `identities.id` arm of the new codex refusal is UNTESTED — both fixtures put
  the divergence only in `session_id`; deleting the `id` clause leaves the suite green.
- R-7 [tests F3, MEDIUM] The empty-first-object branch of the injection is unexercised: inverting the
  `empty ?` ternary would emit `{,"version":"…"}` — invalid JSON — with the whole suite green.
- R-8 [tests F2, MEDIUM] The nested round-trip test asserts byte carriage but not child attribution, and is
  green only because the fixture names the child to match the basename — the very coincidence R-1 shows real
  images never supply. Assert `children` explicitly.
- R-9 [LOW] No test locks the version-dimension idempotence (the lens traced it STABLE, converging after one
  hop, byte-identical on cycle 2 — but nothing would catch a regression).

## ROUTE / REGISTER (beyond this fold)
- **R-a [pre-existing, reachable from a LEGAL workspace]** The staged re-collector does not apply
  `never_collect_path` (the live branch does), and `claude_staged_subtree_artifact` admits only
  `.jsonl`/`.txt`/`.meta.json`, so ANY other regular file under the staged subtree — a `.DS_Store` from a
  Finder visit on the operator's own macOS host, an editor swapfile — turns a legal workspace into a TOTAL
  `biv pack` failure (`claude_code.cpp:471-480` → `pack.cpp:544-547`). Largest remaining whole-pack refusal
  reachable from a legal consent-NO workspace. Folding it as skip-and-warn is inside the pair's standing B1
  grant ("same-set OR skip-and-warn") and strictly widens reader acceptance with no containment cost —
  elected into this fold, disclosed here.
- **R-b [scope note]** G-3 is claude-only and correctly so: codex's `agent_version_at_pack` derives ONLY
  from the body, so a version-less codex head yields "unknown" and dies at `admit` before staging. Do not
  read G-3 as asymmetric neglect.

## What HOLDS (verified; carries)
- **G-1 genuinely closed** (the item that failed last round): the fixture now carries THREE rows — two on
  the SAME adapter — and `continue`→`break` produces exactly "expected two sessions, observed one". Both
  adapters covered symmetrically. Convener-confirmed at the bytes.
- **G-2 VERIFIED** by a full same-set enumeration (neither key / `id` only / `session_id` only / both
  divergent — writer and reader accept exactly the same set); the previously-reachable `id:A`+`session_id:B`
  case is now refused ROW-SCOPED instead of aborting the pack, proven end-to-end through the production
  installer then `pack`.
- **Idempotence STABLE**: injection converges after one hop, cycle-2 byte-identical, no oscillation.
- **Nothing was weakened**: the only removed test lines are inside the renamed G-1 case and were replaced by
  strictly stronger assertions; the min-line relaxation is honestly bound by the pre-existing `FX-VF-O1`.
- Topology: one commit atop byte-identical C, subject preserved, 17-path cumulative range, fold delta == the
  5 declared FOLD_SCOPE paths; no collector or `e3.py` change, so the A3 re-fire was correctly not triggered.

## Disposition
FAIL → one bounded fold: R-1 (blocking, with its test re-targeted), R-2..R-5, R-6..R-9, plus elected R-a.
Then a re-check scoped to that delta, then the fresh paired hand-up carrying A10.3.
