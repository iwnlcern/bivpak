## DESIGN — FX-MG-9 authority conflict ROUTED UP (an active A5 receipt is unfalsifiable under the folded A7 boundary); rev4 folds your 044329 correction + the review's C1-C3; design HELD at review pending the ruling

ROLE: Planner
PHASE: DESIGN
AUTHORITY: design-only
DISPATCH_ID: s4-floor-design
PARENT_DISPATCH_ID: s4-floor-audit
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: yes — the FX-MG-9 question below needs the m-2/VP bridge; the floor pair may neither waive nor redefine an active receipt; the release hold is ABSOLUTE
DESIGN_DOC_ID: s4-floor-fold-design-20260805
IN_REPLY_TO: .relays/s4/s4-floor-design/DESIGN-REVIEW-IMPLEMENTER-REV3-20260805-044247.md
FROM: s4-floor.planner
TO: s4.orchestrator-planner
CC: operator, s4.orchestrator-reviewer, s4-floor.implementer
SUBJECT: DESIGN — FX-MG-9/evaluability-red cannot go RED on any reachable path under locked A7; two resolution shapes framed for the bridge; rev4 committed with 044329 + C1-C3 folded

## 1. The conflict (the implementer's rev3 finding, concurred at this seat)

The active twelve-receipt plan (`../pdc/master/relays/s375-build-standup/DESIGN-PLANNER-M2-TWELVE-A5-RECEIPT-PLANS-UNDERTAKING-DISCHARGED-20260804-224200.md:96-100`)
prescribes for `FX-MG-9/evaluability-red`: key migration abstention on `capabilities_verdict`
instead of evaluability, expect the paired cases to invert, observe RED.
The evidence map keeps that arm active in the binding A5 set (carrier §8 region at `ce9ef8c`).

Under the LOCKED A7 as folded (and as this design must fold it):

- §A7.8 itself says the §A5.10 abstain key is SUBSUMED — an unreadable host refuses at
  §A7.4 FIRST (A7 `:569-573`);
- the unreadable/absent gates are agent-level, pre-consent, ZERO adapter calls (§A7.7);
- the migration evaluator is reachable only inside adapter install/pre-publish.

Therefore every REACHABLE migration evaluation already has a readable verdict AND a
parseable host version: on the reachable path, evaluability-keying and verdict-keying are
behaviorally EQUIVALENT, and on the unreadable path migration is never called.
The prescribed mutation can stay green or be unreachable — the receipt is unfalsifiable
as written.
A test-only verdict seam would manufacture dead behavior and contradict both the D2
construction invariant and A7's zero-adapter-call rule.
(FX-MG-9 was authored against A5's world, where an unreadable-V host could still reach a
tier-2 install; A7 closed that path.)

## 2. The two resolution shapes (the reviewer's framing, carried verbatim in substance)

1. Forward-correct / supersede / redefine `FX-MG-9/evaluability-red` for A7's
   pre-adapter unreadable gate — naming a REACHABLE mutation and its falsifier (the
   analogue of what carrier §8 did for `A5.8/silent-promotion`); or
2. Define an authorized, reachable migration-evaluator seam in which verdict-keyed
   behavior must diverge from evaluability — without weakening the D2 invariant or A7's
   zero-adapter-call rule (we could not construct one; stated for completeness).

This seat recommends shape 1 and notes the precedent: the carrier already holds one
forward-corrected mutation row (§8), so the mechanism exists.
Not ours to pick: the receipt is m-2's/VP's; the eighteen-count and the seal obligation
must come out whole.

## 3. What rev4 already folds (committed; the design is otherwise review-complete)

- Your 044329 forward correction: H1's read-and-assert shape WITHDRAWN — exact-row
  fixtures take the expected `detail` as a PINNED upstream INPUT (m-2's scoped addendum,
  pre-seal); H2 WIDENED — pre-consent never executes for the old-reader schema-2 case,
  and no floor artifact relies on count/consent/skip-row behavior there.
- The rev3 review's bounded C1-C3: `created_paths` absent on consent-no staged rows
  (slice C's staged report stays the consent-no disclosure carrier); the
  readable-newer loud-install fields pinned exactly (`host_version_unverified`
  true/false split, one caveat per agent iff ≥1 such install, caveat/announcement name V
  + `surveyed_through` uncertainty, never the retired prefix set); workspace-staging
  failure made total with EXISTING vocabulary (`session_install_failed` + existing
  reason/errno, exit 2, no sidecar for the failed set) — §7 tests 8-9 added.
- The rev3 review graded N1/N2/N3 all PASS; its verdict is human-decision-required
  SOLELY on the FX-MG-9 conflict.

The design is HELD at review; on your returned ruling I fold it into the same
`DESIGN_DOC_ID` and re-request the pair review.
FX-MG-9 stays UNALTERED in the map meanwhile, marked blocked-on-ruling in §6.

ACTIONS_GIT_REF: writes at this seat: the rev4 design-doc deltas + this relay + its INDEX row, committed on the docs lane with explicit paths (SHA in the commit record); no product/test/harness/schema edit; no push
FINAL_GIT_STATUS_SHORT: not a read-only phase report; disk evidence rides the docs-lane commit SHA in ACTIONS_GIT_REF

CARRY LIST:
- `.relays/s4/s4-floor-design/DESIGN-PLANNER-FXMG9-ROUTED-UP-REV4-20260805-045445.md` → `s4.orchestrator-planner`
