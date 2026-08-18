## PLAN-REVIEW — coupled fold L rev7 APPROVE: fifteen binds and sixteen live legs are executable; five questions closed at the pinned bytes

ROLE: Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
DISPATCH_ID: s4-floor-slice-e-coupled-fold-plan-review-rev7
PARENT_DISPATCH_ID: s4-floor-slice-e-coupled-fold-plan-rev7
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new operator gate — this approval clears only the floor pair's plan-review gate; the floor Planner still owes a separately filed implementation token parented to this review, and the m-1 and m-3 successor byte reviews, land order, merge gate, publication gate and absolute release hold remain unchanged
DESIGN_DOC_ID: m1-addendum-L-20260816
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m1-addendum-L-10c8e8e6-lock-20260817
TARGET_DESIGN_SHA256: 10c8e8e6ed1560d8fc03e9342ed539a1554fdc0a978ba864ce6427226e0daba4
TARGET_DESIGN_COMMIT: 8c7f9281d538704419ea7142a417495eec46e8a5
SECOND_DESIGN_LOCK: m1-addendum-K-5da667fa-lock-20260816, m3-addendum-5-b8686c75-lock-20260816, m3-addendum-4-9049de44-lock-20260816
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812, m3-addendum-3-eeb4dd01-lock-20260814
CONSUMER_DESIGN_LOCK_ID: m3-addendum-3-eeb4dd01-lock-20260814
PLAN_LOCK_ID: s4-floor-slice-e-plan-20260812
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-PLANNER-SLICE-E-COUPLED-FOLD-L-REV7-SIXTEEN-LIVE-LEGS-SCOPE-LOCKED-20260817-191450.md
RELATED_CONTEXT: .relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-SLICE-E-B-L5-RULED-COUPLED-FOLD-RESUMED-NEW-L-LOCK-LEG-Q-LISTING-DEFERRED-20260817-190217.md; .relays/s4/s4-floor-impl/SITREP-IMPLEMENTER-SLICE-E-B-L5-RESUME-RECEIVED-NEW-LOCK-LOCAL-TOKEN-OWED-20260817-191105.md
FROM: s4-floor.implementer
TO: s4-floor.planner
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, m-1.planner, m-1.implementer, m-3.planner, m-3.implementer
SUBJECT: APPROVE — L rev7 plan is executable at clean unpublished 9729191; parameterize the consumer-image helper with an off-by-default stub-payload switch, use three exact stub-footprint duplicate details, build a separate allow-only set, generate leg e in-test, and carry two non-semantic editorial corrections in the implementation token

PLAN_REVIEW_VERDICT: approve

## Review basis

I reviewed the exact `191450` plan committed at coordination head
`1b1b855c185ff5ed1c21fdf445a39c6b9f5d0277`; its file SHA-256 is
`1b9c6930e35ded4bffd5e34002d3101786190fc7b1dde104a2265c163aa11ec5` and isolated relay lint passes.
The implementation worktree is clean at local unpublished head
`972919137203cb2ecb1d9f4bba8d8cd31e27befc`.

I independently extracted the L document from pdc object
`8c7f9281d538704419ea7142a417495eec46e8a5`; it hashes
`10c8e8e6ed1560d8fc03e9342ed539a1554fdc0a978ba864ce6427226e0daba4`, EQUAL to the new lock. The live
post-stamp file hashes `b3599511d8802adc12b2f4dda131374f03d33bc33dfad78e22e826b435fde1e1`, EQUAL to the
released live identity. The old `61d3e443` lock remains superseded.

At `9729191`, the plan's three decisive placements are correct:

```text
manifest.hpp:50-65       AgentSessionEntry has no existing safe carrier; a new opaque vector is required
manifest.cpp:350-351     the over-parse-ceiling return occurs before identity/graph parsing
open.cpp:176-185         required_agent_members constructs the presence-requiring set
open.cpp:280-281         the archive-member admission check is the only allow-only widening point
open.cpp:311-315         missing required members are enforced separately and must remain untouched
sessions.cpp:352-359     entry.children is the skipped cardinal source and cannot carry the footprint
```

The exact helper and caller sweep also confirms that `make_slice_e_consumer_image` has only the three plan-named
call sites at `tests/test_cli.cpp:655`, `:656`, and `:789`; no fourth caller was found. The far-future parser
control is exactly `tests/test_manifest.cpp:589-597`. The m-3 identity source at `224751:46` byte-matches the
live test name at `tests/test_sessions.cpp:1745`; it remains a transcription-time re-read, not a byte copied from
this review.

## Answers to the five requested questions

### 1. S-12 — parameterize; do not lift globally

Add one off-by-default helper control equivalent to `include_stub_payload = false` to
`make_slice_e_consumer_image`. Change the existing condition only to admit payload when the entry is within the
parse ceiling OR that explicit control is true. The three existing callers at `:655`, `:656`, and `:789` omit the
argument and retain today's suppression and oracle meaning. Legs (a) and (b) opt in; leg (q) deliberately stays
off so a declared footprint can be absent without creating an archive presence requirement.

A10 is demonstrated in two ways: source-level, the default preserves the old branch for every existing caller;
behaviorally, run the pre-existing Stage 1b-ii and successor CLI cases unchanged and show their prior notices,
summaries, counts and exits still pass. The new opt-in cases then prove the previously unreachable member-bearing
stub path. A global lift is rejected because it would silently reshape all three existing fixtures and make A10
harder to distinguish from incidental green output.

### 2. S-3 — three exact details, asserted by equality

Use these exact `ParseError.detail` values:

```text
stub-footprint-entry-artifacts-duplicate-key
stub-footprint-entry-children-duplicate-key
stub-footprint-child-artifacts-duplicate-key
```

Legs (i), (j), and (k) each assert equality with its corresponding detail, not substring presence. All three are
therefore distinct from J's existing `children-duplicate-key`, and the child-arm test cannot accidentally pass on
the parsed-graph helper. Duplicate non-footprint keys remain first-wins as S-3 requires.

### 3. S-7 — a separate function and a separate set

Add a separate file-local function beside `required_agent_members`, equivalent to
`allowed_stub_agent_members(const manifest::Manifest&)`, returning only the new opaque footprint paths. Build its
set beside `required_agents` in `read_archive_plan`, then widen only the `open.cpp:280` admission predicate to
accept membership in either set. Do not change `required_agent_members` or the `:311-315` loop.

The separate function is preferred because semantic separation is visible in the code and diff: one set controls
presence, the other only admission. A paired return from `required_agent_members` would couple those policies at
the function boundary and make leg (q)'s forbidden union easier to reintroduce during maintenance.

### 4. Leg (e) — generate in-test

Generate the 1,025-child JSON in `tests/test_manifest.cpp`. Put valid, minimal children in positions 1 through
1,024 and the invalid-path sentinel only in child 1,025. This keeps the mutant leg readable, avoids a large opaque
fixture blob, and makes the ordering proof explicit: the expected detail is the identity-free node-cap detail, not
`artifact-prefix`. The generated string remains ordinary test input; no production generator or fixture schema is
introduced.

### 5. Byte refutation — none substantive; two editorial corrections are carried

I found no semantic refutation of S-1 through S-15. Two plan prose defects are bounded and non-authorizing:

- the scope row `tests/test_manifest.cpp parse-level legs (S-16 map)` references a nonexistent S-16; it means the
  section 4 leg map;
- leg (a)'s `at-least disclosure, exit 0` line appears twice; it is one oracle, not two executions or a seventeenth
  live leg.

The implementation token must record those two corrections explicitly so no keyboard act depends on resolving a
nonexistent bind or double-counting an oracle. They do not change a path, mechanism, leg population, acceptance
criterion, lock, or owner disposition, so a plan rewrite is not required.

## Scope and acceptance verdict

The seven product/test/fixture path rows and the narrowly fenced workflow row are complete for the described
mechanism. The OUT rows are enforceable: writer/serialize and pack stay unchanged; list/info remain deferred;
`sessions.cpp`, `render.cpp`, and `report/envelope.cpp` remain zero-diff; every other workflow byte stays hard-OUT.
A discovered need for an OUT path is a stop to the floor Planner.

The sixteen live legs `(a)-(g)+(i)-(q)` are sufficiently discriminating when implemented as mapped. Leg (h) is
absent, not green. The listing halves remain unasserted. The named `(m)/(n)/(o)/(q)` mutants must be executed and
reverted; reasoning about them does not satisfy A2. Legs (a)/(b) retain the already-observed RED at `9729191` and
must report GREEN at the successor. Leg (q) specifically distinguishes admission from presence and makes the
separate-set placement executable rather than stylistic.

This approval clears PLAN-REVIEW only. It grants no implementation authority. The next lawful act is the floor
Planner's separately filed implementation token parented to this review and carrying the two editorial
corrections above. After that token, implementation and tests remain local: macOS locally, then Ubuntu 24.04
`linux/amd64` in disposable Docker after the implementation is complete. GitHub Actions are not invoked. The four
workflow counts come only from each target's own final XML run, and failures/expectedFailures are observe-and-route.
No push, PR, merge, deployment, publication or release is authorized; the land order and absolute release hold bind.

ACTIONS_GIT_REF: read-only plan review at coordination head 1b1b855c185ff5ed1c21fdf445a39c6b9f5d0277 and clean local unpublished implementation head 972919137203cb2ecb1d9f4bba8d8cd31e27befc; exact L object and live post-stamp re-hashed in ../pdc; exact source/caller/locus sweeps only; no product, test, fixture, workflow, branch, Docker, remote, PR, Actions, merge, publication, deployment or release act; this review and one live-EOF INDEX row ride one explicit-path docs-lane commit
RELAY_LINT: exact incoming plan passes with --no-freshness; exact review will pass with freshness before filing and with --no-freshness after commit; INDEX retains only disclosed standing historical cell-count errors at lines 132, 222, 324, 362, 384, 388, 408 and 435 plus time inversions at 222 and 393; append-only history is not rewritten
FINAL_GIT_STATUS_SHORT: implementation worktree clean at 9729191; coordination checkout contains unrelated pre-existing untracked relay files, and this seat stages and commits only this review plus its one INDEX row

CARRY LIST:
- `.relays/s4/s4-floor-impl/PLAN-REVIEW-IMPLEMENTER-SLICE-E-COUPLED-FOLD-L-REV7-APPROVE-20260817-192103.md` -> `s4-floor.planner`
- `PLAN_REVIEW_VERDICT: approve` -> clears only the pair plan-review gate
- S-12 -> off-by-default helper parameter; existing callers `:655`, `:656`, `:789` retain suppression; legs (a)/(b) opt in and leg (q) stays off
- S-3 -> three exact stub-footprint duplicate details, each equality-asserted and distinct from `children-duplicate-key`
- S-7 -> separate allow-only helper/set at `:280`; required-set construction and `:311-315` remain untouched
- leg (e) -> generated in-test with the invalid sentinel only in child 1,025
- editorial carry -> `S-16 map` means section 4; duplicated leg-(a) line counts once
- local macOS plus Ubuntu 24.04 `linux/amd64` Docker -> only after implementation; GitHub Actions not invoked
- m-1 and m-3 successor byte reviews, land order, push/PR/merge/publication/deployment/release gates -> unchanged and held
