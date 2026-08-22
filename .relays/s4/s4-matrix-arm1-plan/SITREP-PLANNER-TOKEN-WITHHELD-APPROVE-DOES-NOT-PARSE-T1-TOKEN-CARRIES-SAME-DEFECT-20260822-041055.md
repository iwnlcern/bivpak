## SITREP — I am NOT issuing the T3 token, and the reason is a measurement, not a reading: your rev1 approve does not parse. `plan_review_approved` returns False on it, the lineage gate at `relay-lint.py:3348` fires, and a token parented there would be clean per-file and broken in the lineage record. Worse — I checked the class and found the SAME defect already landed on T1's token, which I issued

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-matrix-t3-token-withheld-approve-does-not-parse
PARENT_DISPATCH_ID: s4-matrix-wave-a-t1-resolved-preexisting-topology-use-init
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-T1-RESOLVED-PREEXISTING-TOPOLOGY-ARTIFACT-USE-INIT-DATE-ORACLE-PROCEEDS-20260822-035347.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-T3-DATE-ORACLE-REV1-APPROVE-20260822-025839.md; .relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-T3-DATE-ORACLE-REV1-ORACLE-C-DUAL-RESTORE-GATE-BOUND-FIXTURE-20260822-024647.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — TWO items. (1) The Implementer must file a corrected successor PLAN-REVIEW carrying a PARSING approve line, with a FRESH `DISPATCH_ID`; my token then parents to that, and T3 proceeds exactly as `035347` sequenced it. (2) A disposition for the T1 lineage defect, which is already landed and which I do not think can be repaired in an append-only record. No merge, push, PR mutation, schema act, or release. The release hold is ABSOLUTE
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: reconstructed T3 `a3501cc1728ca13289a8a4a96e49c9ee95e54698`; accepted T1 `00c06d93146f13c0f8518b0893d2d944f0bd8231`
FROM: s4-matrix.planner
TO: s4-matrix.implementer
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: TOKEN WITHHELD — rev1's approve returns False from plan_review_approved (bolded verdict, trailing period, trailing prose); the root-mode gate fires; class census of all 27 lane PLAN-REVIEWs finds exactly two failing approves, the second being T1's R8, whose token I already issued and whose lineage error is live today; corrected successor approve requested with an exact tested line

## 1. What I did instead of issuing the token

`035347` says the approve at `713e790` is in hand and to proceed. I went to parent my bare
`DISPATCH IMPL` to it and checked the approval the way this lane has learned to check
instruments — by calling the matcher rather than reading the prose.

```text
plan_review_approved(PLAN-REVIEW-IMPLEMENTER-T3-DATE-ORACLE-REV1-APPROVE-20260822-025839.md)
  -> False
```

Matcher validated first, so this is a separation and not a bare reading:

```text
  True   'VERDICT: approve'
  True   'VERDICT: APPROVE'
  False  'VERDICT: MUST REVISE'
  False  '**VERDICT: APPROVE.**'        <- the form in your relay
```

**And the gate is real, not theoretical.** `relay-lint.py:3348`:

```text
if rph != "PLAN-REVIEW" or not plan_review_approved(rtext):
    result.error("DISPATCH IMPL parent must be an earlier PLAN-REVIEW relay with verdict approve")
```

Your approve is substantively complete — you pressure-tested the anchor, the AFTER digest, the
named node, the `N == 1` binding, the exact raw output, and the locator's zero-match control.
None of that is in question. The defect is that the verdict LINE confers nothing on the
instrument, which is the looks-delivered-but-isn't shape: it reads as an approve to every human
and returns False to the gate.

## 2. The exact grammar, so the correction lands in one pass

I probed the matcher rather than describing it:

```text
  True   VERDICT: approve
  True   VERDICT: APPROVE
  True   PLAN_REVIEW_VERDICT: approve
  True   VERDICT: approve — remark            (em-dash remark OK)
  True   VERDICT: approve - remark            (hyphen remark OK)
  False  VERDICT: APPROVE.                    (trailing period)
  False  **VERDICT: APPROVE**                 (bold)
  False  **VERDICT: APPROVE.**                (bold + period)  <- yours
  False  VERDICT: APPROVE. The findings close. (trailing prose) <- also yours
  False  VERDICT: approve, with notes         (comma remark)
  False  `VERDICT: approve`                   (backticks)
```

Your line fails on three counts at once: bold, trailing period, trailing sentence.

**The working precedent is in this very lane** — `PLAN-REVIEW-IMPLEMENTER-T2-NSDMI-R1-APPROVE`
carries `VERDICT: approve` bare on its own line at line 6, and parses True. Please use exactly
that form.

**Ask:** file a corrected successor PLAN-REVIEW with a **fresh** `DISPATCH_ID` — do NOT reuse
`s4-matrix-t3-date-oracle-fix-plan-review-r1`. Reusing it would create a two-holder id, and the
impl-dispatch parent walk resolves shared ids by `one_by_id`, which R-3.40 records as
*guessing* earliest-first with no ambiguity diagnostic. Fixing a lineage defect by creating an
id collision would trade a loud error for a silent one. My token then parents to the new id and
T3 proceeds exactly as `035347` sequenced it.

## 3. The class census — and the part that is mine

I did not stop at the blocking instance. I ran `plan_review_approved` over **all 27**
PLAN-REVIEW relays in this lane. Every MUST-REVISE returning False is correct and expected;
the question is only which **approves** fail. Exactly two:

```text
APPROVES THAT PARSE (8)
  R48-CARRIER-REV2, R48-CARRIER-REV2B, R48-FOLD3-R1, R48-LENSFOLD,
  R48-MICROFOLD-R2, REV2, REV3-AMENDMENT, T2-NSDMI-R1

APPROVES THAT DO NOT PARSE (2)
  PLAN-REVIEW-IMPLEMENTER-T3-DATE-ORACLE-REV1-APPROVE-20260822-025839   <- blocking, not landed
  PLAN-REVIEW-IMPLEMENTER-T1-TIDY-FIX-R8-APPROVE-MACOS-PHASE-IDENTITY-20260821-033716
                                                                        <- LANDED, token issued
```

T1's R8 has **no `VERDICT:` key line at all** — the verdict is `**APPROVE.**` in prose beneath
a `## 1. Verdict` heading. So the token I issued at
`IMPL-PLANNER-T1-TIDY-FIX-DISPATCH-20260821-035403.md` parents to an approval the gate reads as
not-approved. That is live today:

```text
$ relay-lint.py --relay-root .relays/s4/s4-matrix-arm1-plan --no-freshness
ERROR .relays/s4/s4-matrix-arm1-plan: IMPL-PLANNER-T1-TIDY-FIX-DISPATCH-20260821-035403.md:
      DISPATCH IMPL parent must be an earlier PLAN-REVIEW relay with verdict approve
```

**I checked whether that red is genuine before reporting it**, because the walk uses the
`one_by_id` resolver R-3.40 records as guessing, and findings from the guessing path are
indicative in both directions:

```text
T1 token PARENT_DISPATCH_ID   s4-matrix-t1-tidy-fix-plan-review-r8
holders of that id            1        <- no collision; resolution is trustworthy
direct plan_review_approved   False    <- instrument-independent, agrees with the walk
```

Unique holder, and two independent methods agree. It is a genuine defect, not an R-3.40
artifact. **I issued that token and I did not check the approval then.** I am not routing this
as someone else's finding.

**Why it went unnoticed, which matters for whether it recurs:** the gate lives only in
`--relay-root` mode. Per-file lint — which every seat here runs before every commit, including
me — never evaluates it. So a token with this defect passes every check the filing ceremony
performs and is only visible to a lineage walk nobody runs routinely.

## 4. What I do not think can be fixed, and what I am therefore asking

For **T3** the fix is clean: nothing has landed, a corrected successor approve with a fresh id
restores the chain.

For **T1** I do not believe the record can be repaired, and I would rather say so than propose
a remedy that quietly makes it worse:

```text
the walk resolves the token's parent BY ID, and reads that relay's committed text
  -> a successor restatement with a NEW id is not what the token points at   (no effect)
  -> a successor reusing the OLD id creates a two-holder collision resolved by guessing
     (R-3.40's one_by_id, earliest-first, no diagnostic) -> trades a loud error for a silent one
  -> the relay record is append-only, so the R8 text cannot be edited
```

So T1's lineage error looks **permanent** until either the matcher is made tolerant or a
void/supersession concept lands — and both are already registered as R-3.40 items (7) *make
the refusal LOUD* and (8) *root mode has no VOID/supersession concept*. I am not proposing to
invent a fourth option in-lane; the disposition is yours and master's.

My recommendation: record T1's lineage defect as a **disclosed known-defect riding T1's stage-5
merge-readiness**, with the measurement above, so the operator's merge word rides full
information — the same treatment `035347` gave the topology artifact. It is a record defect,
not a product defect: the approval was substantively real, the review genuinely pressure-tested
rev8, and no product byte is implicated.

**And this lane has now produced two fresh live instances of R-3.40 item (7)**, whose registry
text says the routing to the harness team is evidence-triggered. Two instances in two days,
from seats that know the rule, is that evidence. The registry already names the remedy: a
`VERDICT`+`approve` line that fails the matcher deserves a WARN whatever grammar they admit.

## 5. State

No token issued. T3 is NOT final, NOT panelable; T4 HELD. rev1(C) itself is unaffected — the
plan is approved in substance and `035347` confirms it is in scope; only the approval's
machine-readability blocks the token. No product, test, harness, workflow, ref, or worktree
byte was edited at my seat; the T3 branch is unmoved at `a3501cc`. I concur with the T1
attribution disposition at `035347` and with adopting Docker `--init` for product-behaviour
Linux runs; O-2 in rev1 inherits that and I will carry it into the token when I issue it.
T2 head FINAL at `7688bbd`. R-4.38's binary inventory stays my stage-5 obligation. Schema
F+G-fenced. Merge is not push is not release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: read-only. Imported `relay-lint.py` and CALLED `plan_review_approved` on eleven synthetic grammar probes and on all 27 lane PLAN-REVIEW relays; ran `relay-lint.py --relay-root .relays/s4/s4-matrix-arm1-plan --no-freshness`; read `PARENT_DISPATCH_ID` from the T1 dispatch relay and counted `DISPATCH_ID` holders. NO edit, NO ref created or moved, NO token issued, NO merge, push, PR mutation, or remote CI. Docs lane: this relay + its INDEX row ride ONE explicit-path commit.
FINAL_GIT_STATUS_SHORT: this relay and its INDEX row are this seat's only working-tree delta at commit time; `git status --porcelain` over `harness/`, `src/`, `tests/`, `CMakeLists.txt` is empty and the T3 branch is unmoved at `a3501cc`; the shared checkout carries sibling-authored untracked paths, preserved and unclaimed
RELAY_LINT: exact-file WITH freshness immediately before commit; INDEX tail re-read before appending; `--index` diffed against the same lint on the pre-append blob to prove no new error is mine; commit gated on lint by logical AND; post-commit exact-file re-verify without freshness.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/SITREP-PLANNER-TOKEN-WITHHELD-APPROVE-DOES-NOT-PARSE-T1-TOKEN-CARRIES-SAME-DEFECT-20260822-041055.md` → TO `s4-matrix.implementer`
- TOKEN WITHHELD ON A MEASUREMENT, NOT A READING: `plan_review_approved` returns **False** on the rev1 approve at `713e790`. Matcher VALIDATED first (`VERDICT: approve` True, `VERDICT: APPROVE` True, `VERDICT: MUST REVISE` False, `**VERDICT: APPROVE.**` False), so this is a separation, not a bare reading. The gate is REAL at `relay-lint.py:3348` — a `DISPATCH IMPL` whose parent fails the matcher errors
- THE APPROVE IS SUBSTANTIVELY COMPLETE and not in question: the Implementer pressure-tested the anchor, AFTER digest, named node, `N == 1` binding, exact raw output, and the locator zero-match control. The defect is that the verdict LINE confers nothing on the instrument — looks-delivered-but-isn't
- EXACT GRAMMAR PROBED, so the correction lands in one pass: PASS = `VERDICT: approve` / `VERDICT: APPROVE` / `PLAN_REVIEW_VERDICT: approve` / `VERDICT: approve — remark` / `VERDICT: approve - remark`. FAIL = trailing period, bold, trailing prose, comma remark, backticks. Your line fails on THREE counts at once (bold + trailing period + trailing sentence). WORKING PRECEDENT IN THIS LANE: `PLAN-REVIEW-IMPLEMENTER-T2-NSDMI-R1-APPROVE` carries `VERDICT: approve` bare at line 6 and parses True — use exactly that
- ASK: corrected successor PLAN-REVIEW with a FRESH `DISPATCH_ID`; do NOT reuse `s4-matrix-t3-date-oracle-fix-plan-review-r1`, because a two-holder id is resolved by `one_by_id` (R-3.40: guesses earliest-first, NO ambiguity diagnostic) and fixing a lineage defect by creating an id collision trades a loud error for a silent one. My token then parents to the new id and T3 proceeds exactly as `035347` sequenced it
- CLASS CENSUS over ALL 27 lane PLAN-REVIEWs (every MUST-REVISE returning False is correct; the question is which APPROVES fail): 8 approves PARSE (R48-CARRIER-REV2, REV2B, R48-FOLD3-R1, R48-LENSFOLD, R48-MICROFOLD-R2, REV2, REV3-AMENDMENT, T2-NSDMI-R1); exactly TWO do NOT — the blocking T3 rev1, and **T1's R8 approve, which is LANDED and which I already issued a token against**
- THE PART THAT IS MINE: T1's R8 has NO `VERDICT:` key line at all (the verdict is `**APPROVE.**` in prose under a `## 1. Verdict` heading), so `IMPL-PLANNER-T1-TIDY-FIX-DISPATCH-20260821-035403.md` parents to an approval the gate reads as not-approved, and `--relay-root` ERRORS on it TODAY. I issued that token and did not check the approval then; I am not routing this as someone else's finding
- RED VERIFIED GENUINE BEFORE REPORTING, because the walk uses the `one_by_id` resolver R-3.40 records as GUESSING and whose findings are indicative in BOTH directions: `PARENT_DISPATCH_ID` = `s4-matrix-t1-tidy-fix-plan-review-r8`, holder count **1** (no collision, resolution trustworthy), and a direct instrument-independent `plan_review_approved` call also returns False. Two methods agree — genuine, not an R-3.40 artifact
- WHY IT WENT UNNOTICED, which decides whether it recurs: the gate lives ONLY in `--relay-root` mode. Per-file lint — which every seat runs before every commit, including me — never evaluates it, so a token with this defect passes the entire filing ceremony and is visible only to a lineage walk nobody runs routinely
- T1 LOOKS UNREPAIRABLE and I would rather say so than propose a remedy that quietly worsens it: the walk resolves the parent BY ID and reads that relay's COMMITTED text, so a successor with a NEW id is not what the token points at (no effect), a successor REUSING the old id creates a guess-resolved collision (loud error traded for silent one), and the record is append-only so the R8 text cannot be edited. Permanent until the matcher is made tolerant or a void/supersession concept lands — both ALREADY registered as R-3.40 items (7) and (8). RECOMMEND: record it as a DISCLOSED KNOWN-DEFECT riding T1's stage-5 merge-readiness with the measurement, the same treatment `035347` gave the topology artifact. It is a RECORD defect, not a product defect — the approval was substantively real and no product byte is implicated
- TWO FRESH LIVE INSTANCES OF R-3.40 ITEM (7) in two days, from seats that know the rule; the registry says routing to the harness team is EVIDENCE-TRIGGERED and names the remedy already — a `VERDICT`+`approve` line failing the matcher deserves a WARN whatever grammar they admit
- CONCUR with the `035347` T1 attribution disposition (pre-existing harness-topology artifact, T1 does not reopen and is not closed) and with adopting Docker `--init` for product-behaviour Linux runs; rev1's O-2 inherits it and I will carry it into the token when I issue it
- STATE: NO token issued; rev1(C) itself unaffected — approved in substance and confirmed in scope by `035347`, only the approval's machine-readability blocks the token; T3 NOT final, NOT panelable, T4 HELD; no byte edited at my seat and the T3 branch unmoved at `a3501cc`; T2 head FINAL at `7688bbd`; R-4.38 binary inventory my stage-5 obligation; schema F+G-fenced; no remote CI, push, PR mutation, merge, publication, deployment or release; release hold ABSOLUTE
