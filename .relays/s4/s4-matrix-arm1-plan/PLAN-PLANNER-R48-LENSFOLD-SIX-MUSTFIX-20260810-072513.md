## PLAN — R-4.8 lens fold rev0 (Edge-1 lineage: parented to the approving rev6 DESIGN-REVIEW per the `071834` discipline note): the six lens must-fixes as ONE bounded cycle, my two discretion calls decided at the bytes (B-Q1 brackets FOLDED; A-obs-2 private-ctor REGISTERED — it would break the aggregate property the locked rev6 §3 explicitly guarantees), and the §4 operator cell carried as a wired conditional slot; PLAN-REVIEW requested

ROLE: Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-matrix-arm1-r48-lensfold-plan
PARENT_DISPATCH_ID: s4-matrix-arm1-r48-design-rev6-review
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-R48-LENS-SIX-MUSTFIX-FOLD-CARRIED-DOWN-20260810-071834.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no at this relay — plan-only, grants nothing; the fold `DISPATCH IMPL` waits on your approving PLAN-REVIEW (Edge 2); §4 remains the OPERATOR's open cell (this plan only wires the slot); the merge hand-up and the ABSOLUTE release hold stand entirely ahead
DESIGN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-09-s4-matrix-arm1-r48-packer-home-carrier-design.md
DESIGN_RECORD_KIND: design-doc
GRILL_LOCK_ID: s4-matrix-arm1-r48-carrier-grill-20260809
PLAN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/plans/2026-08-09-s4-matrix-arm1-r48-carrier-plan.md
FROM: s4-matrix.planner
TO: s4-matrix.implementer
CC: s4.orchestrator-planner, operator, master.orchestrator-planner
SUBJECT: PLAN — lens-fold (six must-fixes + folded brackets + conditional §4 slot), four test files + conditional pack.cpp/design line, ONE commit; verdict wanted: approve | must-revise

Authority basis: the orchestrator's carry-down `071834` (master's six must-fixes intact;
§2 fold-or-register delegated with two cells at pair discretion; §5 lineage discipline —
THIS plan is Edge 1, your approving review is Edge 2). Both load-bearing lens findings
were re-verified at MY seat before this plan (third independent byte-check after master
and the orchestrator): codex.cpp:770-775 appends `env.home / ".codex"` with no early
return from the env branch; test_pack.cpp :461/:525/:551/:576/:660 pin only
`CLAUDE_CONFIG_DIR` and :705/:747/:774 only `CODEX_HOME` — eight pack tests with NO HOME
pin on a machine where `pack()` walks the real `~/.codex`; and `/Users/packer` appears
in the test tree ONLY as receipt/transport assignments, never in fixture CONTENT bytes.
Both lenses' central claims hold exactly as carried.

BASE (re-pinned at dispatch time): `234166722ef44f51db5740c2ac4e01301b5dc0c1` (the
published PR #24 head; the fold commit lands ON TOP — the draft PR gates on nothing and
is not republished by this fold without a separate instruction).

## Steps (ONE commit)

**H1 (must-fix 1a + 4 — hermetic env fixture) `tests/test_pack.cpp`:** one RAII fixture
(extending the existing `ScopedEnv` idiom) that pins ALL FOUR discovery variables —
`HOME`, `CLAUDE_CONFIG_DIR`, `CODEX_HOME`, and `CODEX_SQLITE_HOME` (B-3.1; read at
codex.cpp:726-738) — to paths under the test temp root, applied to EVERY test that
calls `pack()`: the eight unpinned sites above AND uniformly at the already-pinned
sites (the :606-607 two-tier test keeps its intentional env-vs-home split, expressed
THROUGH the fixture's knobs, not around it). No pack test may run with any discovery
variable inherited from the process environment.

**H2 (must-fix 1b — real store guard) `tests/test_pack.cpp`:** wherever a pack test
inspects report/manifest session rows, assert every discovered provenance
`store_root` lies UNDER the test temp root; where zero rows are expected, the existing
`agent_sessions.empty()` stays (it cannot detect an escape — the guard is the
complement, per the lens). Falsifier property to demonstrate (mechanism yours, state
it): a decoy store at a path OUTSIDE the pinned temp universe must be unreachable by
construction — e.g. show the fixture pins `env.home` under temp and assert
`getenv("HOME")` differs from the fixture-recorded original during the pinned scope.

**V1 (must-fix 2 — carrier-divergence-visible receipts) `tests/test_adapter_claude_install.cpp` + `tests/test_adapter_codex_install.cpp`:**
make the engaged arm's carrier a PREFIX of paths present in the fixture member CONTENT
— point `packer_home` at the fixture workspace's PARENT (the member bytes already carry
`/ws/proj` spellings; carrier `"/ws"` posix puts carrier-prefixed bytes in the compared
content). Expected result TODAY is unchanged (arms byte-identical — the adapters do not
read the field), but a future carrier-conditional scrub/rewrite now DIVERGES the arms
instead of landing green. Keep `/Users/packer` out or in as you judge — the property
that matters is carrier-bytes-visible-in-content, stated in the test comment.

**V2 (must-fix 3) both receipt files:** wrap the contents-map insert as
`REQUIRE(receipt.contents.emplace(...).second)` — a duplicate normalized name fails
loudly instead of silently dropping the shadowed file.

**V3 (must-fix 6) both receipt files:** state the minted-id carve-out in the receipt
claim (comment on the byte-identity REQUIREs: minted ids are normalized across arms by
construction, so id-only divergence is out of the claim) AND compare id_map SHAPE
across arms: entry count and the stable members (`agent`, `image_session_id`,
`children.first` sequence) equal; minted members excluded.

**O1 (must-fix 5) `tests/test_manifest.cpp`:** the `ORACLE RULE — never regenerate from
the serializer` comment on the carrier-engaged exact-bytes golden (:93-111), wording
matched to `test_envelope.cpp:566-567`.

**BR1 (§2 discretion — FOLDED, cheap) `tests/test_manifest.cpp`:** minimal-accept
bracket rows in the factory table: `"/x"` → engaged posix, `"/mnt/c/x"` → engaged wsl,
`"C:/x"` → engaged windows — pins the lower accept boundary of every flavor (the
extended pair already carries its 8-byte controls).

**G1 (§4 — WIRED CONDITIONAL SLOT, executes only on the operator's ruling):** if the
operator rules (a) sessions-gated capture: gate the capture at pack.cpp:676 on
non-empty `report.agent_sessions` (zero-session image ⇒ no carrier ⇒ no home/username
disclosure where the needle never runs); add the two matrix rows (sessionless pack ⇒
keys ABSENT; with-sessions pack ⇒ carrier present); and record the operator's ruling as
a one-line design §4 note citing the ruling relay (authority = the operator's ruling,
disclosed to your review — object if you want a fuller amendment cycle instead). If (b)
unconditional stands: G1 is a no-op and the slot closes with the ruling reference. The
fold does NOT wait on §4 — if the ruling lands before the dispatch, G1 rides the one
commit; if after, G1 becomes its own micro-cycle per the orchestrator's window.

## Decided at this seat (§2 discretion cells, with reasons for your review)

- **B-Q1 brackets → FOLDED** (BR1): purely additive boundary rows, minutes of work,
  catches non-uniform tightenings the extended controls cannot.
- **A-obs-2 private-ctor + factory-sole-builder → REGISTERED, not folded.** At the
  bytes this is NOT the mechanical visibility tweak it looks like: locked rev6 §3
  explicitly guarantees "`PackerHome` stays an aggregate (fixtures/designated-init
  untouched)" — a private constructor destroys aggregate-ness, breaks every
  designated/positional init site in the fixtures, and moves sealed design text. Per
  the carry-down's own guard ("if it grows beyond a mechanical ctor/visibility change,
  register") and the fences-over-sealed-behavior rule, this is a design-lane item:
  registered with this reason for master's registry / a future design micro-amendment.
- (Per the ruling, not mine to decide: extended-grammar/UNC and oracle-2 REGISTER at
  the needle head; no pure in-design tightening is attempted in this fold — any
  drive-spec check touches `classify_carrier_root` semantics, which is exactly the
  stop-and-route line.)

## Acceptance criteria

1. No pack test runs with ANY of the four discovery variables inherited from the
   process env; the eight formerly-unpinned sites are pinned; the two-tier test's
   intent preserved. 2. Store-root-under-temp guard present wherever rows exist; the
   hermeticity falsifier property demonstrated and stated. 3. Engaged-arm receipts
   carry carrier-prefixed bytes IN CONTENT; arms still byte-identical at this head; the
   claim comment + id_map shape compare landed. 4. Duplicate-key inserts fail loudly.
5. ORACLE comment + bracket rows landed. 6. G1 only per the operator's ruling, with the
   design note. 7. ONE commit on top of `2341667`; strict TDD where a RED is
   constructible (the eight unpinned sites: a decoy-visibility RED is constructible on
   any machine by pointing the decoy inside the CWD-reachable universe — your call,
   disclose); declines disclosed. 8. Focused carrier + pack suites; full macOS row;
   Docker NOT re-run for a test-only delta — but if G1(a) rides (a `pack.cpp` product
   change), the Docker carrier leg and a security seat in the re-check are ADDED. 9. No
   push/PR-republish/CI/merge/release; the PR is not updated by this fold absent a
   separate instruction; the release hold is ABSOLUTE.

Downstream: your approve (Edge 2) → the fold `DISPATCH IMPL` (fresh unique key,
parented to your approve, BASE re-pinned, SCOPE_DIFF: the four test files + conditional
`pack.cpp` + conditional design line) → the work → targeted re-check sized to the delta
(lead + tests; + security iff G1(a) rode) → the fresh MERGE hand-up (§1 six-fold proof
+ the standing end-state-bytes condition-3 at the eventual merge base + condition-4).

ACTIONS_GIT_REF: docs lane only — this PLAN + its INDEX row ride one explicit-path commit (SHA lands after filing); product and test paths were touched by no action at this seat; the published branch/PR are untouched by this relay.
FINAL_GIT_STATUS_SHORT:
none — clean tree (matrix-seat paths; the shared checkout carries sibling seats' untracked relays, preserved untouched)
Fresh at 20260810-072513 before this relay + INDEX write; this relay and the INDEX row are this seat's working-tree delta at commit time.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-R48-LENSFOLD-SIX-MUSTFIX-20260810-072513.md` → TO `s4-matrix.implementer`
- six must-fixes → H1/H2/V1/V2/V3/O1 as one bounded cycle; BR1 folded; A-obs-2 REGISTERED (breaks the locked rev6 aggregate guarantee — reason routed for the registry)
- §4 → wired conditional slot G1; operator's cell; fold does not wait on it
- Edge 1 = this PLAN → rev6 DESIGN-REVIEW (`231944`); Edge 2 = the fold token → YOUR approving PLAN-REVIEW; then targeted re-check → merge hand-up (end-state-bytes condition-3 ahead)
- PR #24 stays as-is; publication ≠ merge ≠ release; release hold ABSOLUTE
