## SITREP — the tranche-2 implementation STOPPED at my implementer's seat (`063445`, before any staging or commit) on a contradiction between the plan's census and the executable parser, and the contradiction is a PLANNER CENSUS ERROR OF MINE, resolved in-lane at revision 11 with the grounds on the face and ONE observation for m-1 (no ask): the rev5–rev10 plan listed "non-empty `remote`/`url`" as a `remotes[]` parser predicate; VERIFIED at my bytes it never was — `required_string` (:41-47) checks presence and string type only, `parse_remotes` (9e6ebe8 :1183-1203; the frozen tree alike) rejects only a failed expected, so empty `name`/`url` strings are ACCEPTED; sealed §2.3 imposes no such constraint ("`remote`/`remotes`: recorded from the repo's EFFECTIVE config", manifest-format.md:259) and O leg (f) treats URL fields as recorded data; by the plan's own rule (a table-A row exists only where the parser REJECTS the state) the row was never eligible — I had inferred it from ParseError sites that reject absence/type alone; rev11 STRIKES it, corrects the member names (`name`/`url`), records a binding corollary (a row is admitted only on a cited rejection site executed at the bytes), moves NO parser byte, and restores O-R4 by removal (the writer accepts what the parser accepts); the implementer's option 1 (keep the writer clause) and option 3 (change the parser) are both rejected on the face; the `055109` token is CONSUMED at the STOP; rev11 (`intg-substep2a/PLAN-pair-planner-20260902-064236.md`, artifact 0929edb3) goes to exact-hash review, then a fresh token; the frozen six-file patch (fbf77f3d) stays unstaged as evidence; the W-5 re-measurement runs on the rev11 filing and is reported here verbatim

ROLE: Pair Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: intg-substep2a-audit
PARENT_DISPATCH_ID: intg-substep2a-format-act
IN_REPLY_TO: intg-substep2a/IMPL-pair-implementer-20260902-063445.md
RELATED_CONTEXT: ../../pdc/master/domains/m-1-format-engine/design/2026-07-02-manifest-format.md; ../../pdc/master/domains/m-1-format-engine/design/2026-09-01-ADDENDUM-O-writer-validity-contract.md; ../../pdc/master/relays/intg-substep2a-format-act/DESIGN-planner-20260902-034802.md; intg-substep2a/IMPL-pair-planner-20260902-055109.md; ../../pdc/master/RESIDUALS.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no NEW gate — a plan correction inside the sealed text (nothing filled, an inference removed); the observation rides to m-1 with no ask and m-1 may overrule by opening its own row; the standing gates (exact-hash re-review → fresh token → m-1/m-3 byte reviews → merge behind the operator's token; push behind R-4.38 + R-4.46) all survive; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: intg-format-act-plan
DESIGN_LOCK_ID: m1-addendum-O-63c46631-lock-20260901
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: intg-substep2a-plan-20260830 @ sha256 0929edb3d48afee54c6f95a96ee1a09dca11deabdda7e383edcd8754d97f7a16
FROM: intg.pair-planner
TO: master.master-planner
CC: operator, master.master-reviewer, intg.pair-implementer, m-1.planner, m-1.implementer, m-3.planner, m-3.implementer
SUBJECT: SITREP — tranche-2 STOP (063445: the plan required writer refusal of empty remotes[] name/url; the retained parser accepts them) resolved in-lane as MY census error — the row struck at rev11 (0929edb3) with the grounds (required_string :41-47; parse_remotes 9e6ebe8 :1183-1203; manifest-format.md:259; O leg (f)) and a binding corollary; no parser byte; O-R4 by removal; observation for m-1, no ask; token 055109 consumed; fresh review → fresh token; the W-5 re-measurement of rev11 below

## The finding at the bytes (verified at my seat before resolving)

```text
required_string   manifest.cpp:41-47 (both trees): at_key(key).get(string_view) → error ⇒ ParseError{key};
                  else return the string UNCHANGED — presence + type only, no emptiness test
parse_remotes     9e6ebe8 :1183-1203 (the frozen tree byte-equal here): name = required_string("name"),
                  url = required_string("url"); `if (!name || !url) → ParseError{"remotes"}`; nothing else
                  — an empty "" for either is ACCEPTED
the plan's row    rev5 §2.3 list: "the remotes[] row constraints (:1198-1209: non-empty `remote`/`url`)" —
                  the cited lines are the absence/type rejections; "non-empty" was my inference; the member
                  is `name`, not `remote`
sealed §2.3       manifest-format.md:259 "`remote`/`remotes`: recorded from the repo's EFFECTIVE config
                  (audit caveat: never `.gitmodules` alone for submodules). `remote` = the eligibility-proven
                  one." — no non-emptiness constraint; none in G/H/N; O-R2 carves URL fields OUT as recorded
                  data (leg (f))
the plan's rule   a table-A row exists ONLY where the parser REJECTS the state (O-R1 "§2.3+G+H+N+O-R2/O-R3"
                  + O-R4's by-construction clause, 034802 §2) → the row was never eligible
```

## The resolution and why it is in-lane

The implementer framed three options: (1) keep the writer clause — narrows the O-R1-accepted projection below the parser language, O-R4 violated; (3) change the parser — an acceptance change, 034802 §2 violated; (2) remove the clause. Option 2 is not an "omission of a required row": the row was admitted by an inference the sealed text never made and the parser never executed, so removing it CONFORMS the plan to the sealed text and the retained bytes. Nothing is filled in-lane; nothing sealed is silent on this point (§2.3 speaks: recorded verbatim from config). Rev11 therefore strikes the row, records the grounds, and adds the corollary that binds the Step-0 tables: a row is admitted only on a cited parser rejection site executed at the bytes — never from a field name, an exemplar, or a ParseError site that rejects absence/type alone.

**Observation for m-1 (no ask):** if m-1 reads §2.3 as REQUIRING non-empty remote names or URLs, the retained parser under-enforces it — that would be m-1's own row (an acceptance change, outside arm (a)'s propagation-only fence and outside O), not this act's. This act keeps the parser's acceptance language exactly as it stands.

**My error, classed:** a census row asserted from a rejection site's NEIGHBOURHOOD rather than its executed predicate — the same inspect-not-walk class m-1 owned on C-4, at my pen; the implementer's Step-0 walk caught it before any commit. Credited.

## The W-5 replacement re-measurement of rev11, VERBATIM (the instrument of record)

```text
command   python3 <kit 2.9.2>/tools/relay-lint.py --relay-root .relays/intg --no-freshness
archive   docs/sprints/2026-08-27-intg-consent-fabric/results/lint-root-sweep-2a-rev11-remotes-row-struck-20260902.txt
          sha256 ff6834dfd7db145aed2e3c62df33e4360f2b223cb858f16e13bb6fe160e1f88d ; 303 lines ; rc 1
          (277 ERROR / 26 WARN root-wide; design-lineage class 52 = 50 prior + the rev11 carrier + its draft
          echo; design-edge class 0; the isolation carrier 033604 silent)

FIRED SET ON THE CITING CARRIER (exactly one ERROR line):
ERROR .relays/intg: intg-substep2a/PLAN-pair-planner-20260902-064236.md: DESIGN_LOCK_ID 'm1-addendum-O-63c46631-lock-20260901' has no earlier same-owner DESIGN relay carrying matching DESIGN_DOC_ID

per-file contrast (NOT closure): relay-lint.py --no-freshness intg-substep2a/PLAN-pair-planner-20260902-064236.md → OK, rc 0

DISCLOSED, so the +15 root-wide delta since the rev10 sweep is accounted for: every one of the 15 new lines is
either (i) the rev11 carrier / its draft echo (the design-lineage class above), or (ii) the standing class
"commission machine engaged but relay is not consumed by any Task 9.5a stage (DD-v29 cross-seat rule 3)" firing
once on each NEW engaged non-PLAN relay or draft (the 053812/055211/055242 SITREPs, the 054431 review, the
055109 token, the 063445 STOP, and the seats' drafts) — that class has fired on every such relay in this root
since the first 2a sweep (80 lines on 2026-08-30 → 164 now; the oldest firing relay is the countgate review
221938) because CHARTER_DOC_ID is a commission carrier and a non-stage relay carrying it is "engaged"; it is
the inherited population, not a new finding, and not the W-5 gate. Plus one informational WARN on the consumed
055109 token naming 053636 as its selected PLAN parent among the eleven same-id holders (the standing
supersession shape).
```

## Standing state (both lanes)

- 2a: rev11 @ `0929edb3` to the implementer for exact-hash review; on approve a fresh token (handoff `intg-substep2a-impl-3`, parented to that review); the frozen six-file patch (`fbf77f3d`) unstaged at `9e6ebe8`, index clean, tranche 1 preserved (`72fd3dc6`); the resume is mechanical (two clauses + two arms dropped; |A| re-derived; Steps 4→6; Task 4).
- Isolation: plan `033604` @ `46e47a0a` awaiting the implementer's exact-hash review.
- No merge, no push (R-4.38 due point + R-4.46), no PR, no remote CI, no publication, no seal, no release. The release hold is ABSOLUTE.

ACTIONS_GIT_REF: docs-lane writes only — the rev11 artifact, its relay, and this SITREP via the engine; commit path-scoped follows; no product byte at this seat; the implementer's frozen patch untouched
RELAY_LINT: engine-rendered submissions; per-file v2.9.2 lint rides the daemon gate; drafts pre-linted per-file
FINAL_GIT_STATUS_SHORT:
 M docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep2a-20260830.md
 ?? .relays/intg/.engine/drafts/intg.pair-planner/PLAN-SUBSTEP2A-REVISION11-REMOTES-ROW-STRUCK.md
 ?? .relays/intg/.engine/drafts/intg.pair-planner/SITREP-TRANCHE2-STOP-REMOTES-RESOLVED.md
Literal path-scoped status for this seat's own writes at authoring time; the shared bivpak tree additionally carries sibling-authored state not claimed clean here.
