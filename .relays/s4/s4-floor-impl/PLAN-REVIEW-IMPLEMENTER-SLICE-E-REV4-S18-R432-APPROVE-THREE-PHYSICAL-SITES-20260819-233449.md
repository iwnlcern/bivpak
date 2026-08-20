## PLAN-REVIEW — APPROVE rev4 S-18 with independently verified totality, single enum site and one three-site ordering bind

ROLE: Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
DISPATCH_ID: s4-floor-slice-e-r432-plan-review-rev4
PARENT_DISPATCH_ID: s4-floor-slice-e-r432-plan-rev4
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-PLANNER-SLICE-E-REV4-S18-R432-FOUR-FILE-COMMIT-DERIVATIONS-PINNED-20260819-223918.md
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new operator gate — this review clears only the local pair PLAN-REVIEW gate; a fresh floor-Planner implementation token parented to this review remains mandatory, both platform suites are owed after implementation, and the landed four-file commit returns to m-3 for byte review before any merge-gate re-presentation
DESIGN_DOC_ID: m1-addendum-L-20260816
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m1-addendum-L-10c8e8e6-lock-20260817
SECOND_DESIGN_LOCK: m1-addendum-K-5da667fa-lock-20260816, m3-addendum-5-b8686c75-lock-20260816, m3-addendum-4-9049de44-lock-20260816
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812, m3-addendum-3-eeb4dd01-lock-20260814
CONSUMER_DESIGN_LOCK_ID: m3-addendum-3-eeb4dd01-lock-20260814
PLAN_LOCK_ID: s4-floor-slice-e-plan-20260812
FROM: s4-floor.implementer
TO: s4-floor.planner
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, m-3.planner, m-3.implementer, m-1.planner
SUBJECT: APPROVE — rev4 S-18 at exact plan hash 8be6217e; exit-to-class totality and the single enumerated session-row kind site independently confirmed; bind after-UnknownAgentSkipped placement across all three physical insertion sites

PLAN_REVIEW_VERDICT: approve

## Exact review basis

The committed rev4 plan at docs-lane commit `276099f` and the worktree file both hash
`8be6217e10bfb020467e15498d875655093a3830fa84f1e41aefa1f3721b9574`. Exact-file relay lint passes.
Its parent, four-row `SCOPE_DIFF`, owner sources, no-token authority, one-commit form, re-run rule, m-3 return
gate, R-4.34 exclusion, merge hold and release hold are internally executable.

I re-read the A4 owner document at pdc object `40bd88a6`. Its bytes independently establish the exact
`EntrySchemaSkipped` spelling, exit 0, distinct cause boundary from `UnknownAgentSkipped`, and purely additive
one-row shape. The implementation worktree is clean at exact candidate
`4427bb30e23309af92432a06dc66d89463480d0c`.

## Answers to the four review questions

### 1. Exit-to-class correspondence is total

Yes. I parsed all 26 current exit-map rows and independently obtained:

```text
exit 0 -> advisory
exit 2 -> divergence
exit 3 -> refusal
exit 4 -> mid-fail
exit 5 -> usage
```

Every observed exit value maps to exactly one class and there are no exceptions. A4's exit 0 therefore derives
`class: advisory` without an authored semantic choice. The two current exit-0 rows are
`SessionsConsentSkipped` and `SessionsStaged`, both with that class and the approved byte shape.

### 2. Exactly one enumerated session-row kind site exists

Yes. I recursively enumerated all ten `enum` nodes in the envelope schema. Exactly one is a `kind` enum: the
six-member session-row kind at the §4.2 JSON pointer. The other `kind` properties are two free-form strings
(`warnings` and `error`) and two advisory `const` discriminators; none is a second enum site for this value.
Adding one member at the measured session-row site is complete and no other schema site is owed.

### 3. Ordering accepted with one token bind

I accept immediate placement after `UnknownAgentSkipped`. Section 4.5's singular “rows order” must be carried
into the token as one coordinated ordering policy across **both** physical row lists. The complete physical bind
is therefore:

1. exit-map JSON row immediately after the `UnknownAgentSkipped` row;
2. envelope session-row enum member immediately after `UnknownAgentSkipped`;
3. C++ `ExpectedRow` element immediately after the `UnknownAgentSkipped` element.

This does not add a path or semantic choice; it makes the plan's stated split-relative ordering deterministic at
all three insertion sites. A token that applies §4.5 to only one of the two row lists is ambiguous and invalid.

### 4. S-18 and A22-A27

No refutation. The four-file fence is complete for the observed dependency surface, the schema hash constants
are mechanically derived only after both schema files reach final bytes, the C++ row uses
`exit_for_error(biv::ErrKind::EntrySchemaSkipped)`, and the existing cardinality check becomes 27 against 27.
R-4.34 remains explicitly outside this commit.

A22-A27 are accepted with two execution readings already present in the plan:

- “unchanged counts” is evidenced by job and mapping key, never by living source position;
- any unexpected fifth path, extra changed byte, second enum site, test failure or count movement is a STOP to
  the floor Planner and is never repaired by widening at the keyboard.

## Scope and gate verdict

Approved IN scope is exactly:

```text
schemas/biv-exit-map.v1.json
schemas/biv-json-envelope.v1.schema.json
harness/selftest/test_envelope.py
tests/test_envelope.cpp
```

The landed delta is one exit-map row, one envelope enum member, two recomputed blob-ID values and one C++
expected-row element, with the three-site ordering bind above. Every other byte, every fifth path, every product
path, every `.github` byte and count cell, and the R-4.34 derive-from-enum repair remain OUT.

This approval grants no implementation authority. The next lawful act is a fresh floor-Planner token parented to
this review, carrying the three-site ordering bind and a fresh W-2 join. After the one local commit naming R-4.32,
both platform suites re-observe and the four job/key count values must remain unchanged. The landed commit then
returns to m-3 for byte review over all four files. Merge remains a separate operator gate and the release hold
remains absolute.

No Docker run, local test, GitHub Actions, remote CI, push, PR, merge, publication, deployment or release
occurred during this review.

ACTIONS_GIT_REF: review-only at docs-lane HEAD 276099f; incoming plan SHA-256 8be6217e10bfb020467e15498d875655093a3830fa84f1e41aefa1f3721b9574; A4 owner object 40bd88a6 re-read; independent 26-row exit-class enumeration and 10-enum schema enumeration at clean implementation head 4427bb30e23309af92432a06dc66d89463480d0c; this review plus one live-EOF INDEX row are the only intended coordination writes
RELAY_LINT: incoming exact-file no-freshness PASS and outgoing exact-file freshness PASS; live INDEX lint reports only inherited malformed-cell rows 132, 222, 324, 362, 384, 388, 408 and 435 plus inherited time inversions 222 and 393; this appended row is 10-cell clean, filename-matched and live-EOF at lint time
FINAL_GIT_STATUS_SHORT: path-scoped pre-commit status is `M .relays/s4/INDEX.md` plus `?? .relays/s4/s4-floor-impl/PLAN-REVIEW-IMPLEMENTER-SLICE-E-REV4-S18-R432-APPROVE-THREE-PHYSICAL-SITES-20260819-233449.md`; all other untracked paths are pre-existing foreign artifacts, preserved and excluded

CARRY LIST:
- `.relays/s4/s4-floor-impl/PLAN-REVIEW-IMPLEMENTER-SLICE-E-REV4-S18-R432-APPROVE-THREE-PHYSICAL-SITES-20260819-233449.md` -> `s4-floor.planner`
- `PLAN_REVIEW_VERDICT: approve`; no implementation authority inferred
- exit-to-class totality -> independently confirmed over all 26 rows with no exception
- envelope enum inventory -> independently confirmed ten enums and one session-row kind enum target
- ordering bind -> immediately after `UnknownAgentSkipped` at exit-map row, envelope enum and C++ expected row
- scope -> exactly four files; R-4.34, count cells, `.github` and every other path OUT
- next -> fresh token parented here with fresh W-2 join; one local R-4.32 commit; both suites; m-3 four-file byte review
