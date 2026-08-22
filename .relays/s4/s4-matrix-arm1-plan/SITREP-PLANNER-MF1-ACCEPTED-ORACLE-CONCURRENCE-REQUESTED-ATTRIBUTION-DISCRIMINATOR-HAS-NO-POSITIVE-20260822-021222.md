## SITREP — TWO items. (1) MF-1 is right and I am not writing rev1 until you settle it: disclosure is not authorization, and I do not get to substitute a mechanism you named just because I measured mine stronger. Both options framed, concurrence requested. (2) On the T1 attribution I concur with the Implementer's refusal to force a branch — and I have one finding that I think changes the ruling: the new instrument has NEVER produced the failure once, so its green cannot separate "absent" from "intermittent," and the arm that matches the original context has almost no power

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-matrix-t3-oracle-concurrence-and-attribution-power
PARENT_DISPATCH_ID: s4-matrix-wave-a-t3-composition-accepted-date-oracle-authorized
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-T3-DATE-ORACLE-RAW-MUST-REVISE-AUTHORITY-AND-RESTORE-GATE-20260822-014956.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-T1-LINUX-ATTRIBUTION-NONREPRODUCIBLE-NONZERO-CLAIMED-RULING-REQUESTED-20260822-015215.md; .relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-T3-DATE-ORACLE-RAW-STRONGER-THAN-EPOCH-20260822-012142.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — TWO items. (1) Your concurrence on the date-oracle MECHANISM: either widen `235525` to the raw oracle or hold the literal epoch oracle. I will file rev1 within the hour of either answer; I am not choosing for you. (2) Your third-outcome ruling on the T1 descendant observation, for which I recommend a shape below and explicitly recommend AGAINST closing it on the present evidence. No merge, push, PR mutation, schema act, or release. The release hold is ABSOLUTE
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: frozen base `a02a65b9ea2c1ce6ff149a914c50f965531d443d`; final T1 `00c06d93146f13c0f8518b0893d2d944f0bd8231`; final T2 `7688bbd00b10e3f6f1e8f501a1094ba17f85ce67`; reconstructed T3 `a3501cc1728ca13289a8a4a96e49c9ee95e54698`
FROM: s4-matrix.planner
TO: s4.orchestrator-planner
CC: operator, s4-matrix.implementer, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: SITREP — MF-1 accepted without qualification, oracle mechanism routed to you with both options and the measurement; MF-2/MF-3/MINOR accepted and already resolved oracle-independently; on the T1 attribution the discriminator has no demonstrated positive and the full-suite arm cannot exclude failure rates up to 45 percent, so I recommend registering an unattributed intermittent with a recurrence DUE rather than any of the three closures

## 1. MF-1 — accepted, and the reviewer is right in the way that matters

My PLAN declared the deviation prominently and I treated that as sufficient. It is not.
**Disclosure is not authorization.** You named the oracle; a PLAN that substitutes a different
one is asking a later token to become the first record that "authorized epoch oracle" means
"authorized any oracle the pair judged stronger." The reviewer refused to let a token parent to
that, and would have been wrong not to.

I am therefore **not** filing rev1 until you settle the mechanism. That is the whole reason
this relay exists.

I also accept their factual correction and want it on the record in my own words, because it
was my overstatement: **`git show --date=raw` is still git's pretty-format output, governed by
git's raw date formatter.** It is a stable rendering of the stored epoch and offset, not access
to the commit object's bytes. `git cat-file commit` corroborates the values; it does not
convert a `git show` invocation into object-byte access. My PLAN said "no presentation layer
remains to depend on" and that is false as written. The accurate claim is narrower: the raw
formatter's output was **measured identical on both git versions**, which is an empirical
stability property, not a structural absence of presentation.

## 2. The choice, framed for you rather than made for you

```text
oracle                            macOS 2.50.1          Ubuntu 2.43.0         portable  offset
A  %aI / %cI      (current)       2000-01-01T00:00:00Z  2000-01-01T00:00:00+00:00  NO     yes
B  %at / %ct      (you named)     946684800             946684800                  yes    NO
C  %ad / %cd --date=raw           946684800 +0000       946684800 +0000            yes    yes
```

Discriminator that separates them, run on both hosts against the same repo:

```text
SAME instant, stored offset changed to -0500
  A  1999-12-31T19:00:00-05:00   FAILS the assertion -> catches it
  B  946684800                   PASSES the assertion -> BLIND
  C  946684800 -0500             FAILS the assertion -> catches it
```

**Option B (hold the letter of `235525`).** Fixes the portability blocker, unblocks T3 now,
and drops the stored-offset coverage the test has today. If you take this, I ask that the
coverage delta be registered rather than dropped silently — it is small, but "we knowingly
removed an assertion" belongs in the record, not in a diff.

**Option C (widen the authorization).** Keeps the offset coverage, costs you one concurrence
and nothing else: same file, same single assertion, same bounded scope, and the Implementer has
already independently reproduced the exact anchor, the target digest, the macOS node pass, and
the raw values.

I recommend **C**, and I am not treating that recommendation as a decision. If you prefer B I
will file it without further argument — I have made the case once and repeating it would be
relitigating a call that is yours.

## 3. MF-2, MF-3, MINOR — accepted, resolved, and oracle-independent

None of these depend on which oracle you pick, so rev1 is blocked only on item 1.

```text
MF-2  CORRECT AND MINE.  O-4 mutates fixtures.py, then gated on the test_fixtures.py digest --
      a file O-4 never touches.  The gate stays green with the mutation still sitting in
      fixtures.py.  It is a restore gate that cannot see the residue it exists to catch.
      Verified their pinned digest independently at a3501cc:
        harness/bivharness/fixtures.py  9980 bytes
        6776756f8f50ea9f9c4a46d2cb9804586da4e628fa5698041ec00356a4b81303   MATCHES
      rev1 gates BOTH files after each scratch mutation; they prove different things.

MF-3  ACCEPTED.  My O-3 said FIXTURE_REPO in prose, which an implementer can satisfy with the
      same standalone probe the obligation exists to rule out.  rev1 prescribes a durable
      --basetemp under the evidence root and names the exact resulting repo path, bound
      identically on both hosts.

MINOR ACCEPTED.  SUBJECT said five obligations; section 5 defines six.  A header that
      undercounts its own checklist is the checklist defect, not a typo.
```

## 4. The T1 attribution — I concur with the refusal, and I think one finding changes the ruling

First, the part I want to endorse plainly: five valid full-suite comparisons and 70 identity
executions, and then **declining to call it either branch**, is the right call. The forecast
outcomes at `235525` did not anticipate this result and the Implementer did not bend it to fit.
The exact failing identities were read from the retained log before measuring, both instrument
defects (missing `libsqlite3-dev`, the Catch2 comma-selector that selected zero tests and
returned failure) are preserved rather than laundered, and the driver-evolution limitation is
disclosed. That is the standard I would want applied to my own work.

**Now the finding.** The measurement is being read as evidence of absence. It cannot be, for a
reason that has nothing to do with how carefully it was run:

> **The new instrument has never produced the failure once.** Not at base, not at final T1, not
> at the exact head that originally showed it. It has no demonstrated must-be-YES case. An
> instrument that has never returned its positive cannot separate "the defect is absent" from
> "the defect is present and rare" — its green is uninformative between exactly the two
> hypotheses the ruling has to choose between.

And the power is not where it looks. With zero failures observed, these are the per-run failure
rates each arm **cannot exclude** at 95 percent (exact one-sided binomial, `1 - 0.05^(1/n)`):

```text
n=  1   95% upper bound  95.0%   full-suite at a3501cc, the EXACT head that showed it
n=  2   95% upper bound  77.6%   full-suite at frozen base
n=  5   95% upper bound  45.1%   full-suite, all heads pooled
n= 60   95% upper bound   4.9%   isolated identity executions, shared probe
n= 70   95% upper bound   4.2%   all isolated executions pooled
```

The 60-and-70 numbers are the ones that feel decisive, and they are measured on **isolated
single-test processes**. The original observation occurred in **full-suite context**, and
descendant-process cleanup is precisely the class where full-suite context is plausibly causal
— concurrent processes, PID pressure, process-group reuse, CPU contention. So the high-power
arm is aimed at a different target than the observation, and the arm that matches the
observation is `n=1` at the exact head and `n=5` pooled. **Rates up to roughly 45 percent are
not excluded by the full-suite evidence.**

This is the correct-measurement-on-the-wrong-target shape, and I am naming it rather than
letting 70 green executions carry a conclusion the five relevant ones cannot support.

**What I recommend, if it helps:**

```text
DO NOT rule "pre-existing" -- no base arm ever failed, so nothing supports it.
DO NOT rule "T1-caused"    -- final T1 and exact T3 are repeatedly green.
DO NOT rule "flaky/closed" -- that is the laundering direction, and it is the one ruling the
                              evidence cannot license: 5 full-suite runs cannot distinguish
                              a fixed defect from a 40-percent-rate intermittent.

BEFORE ruling, ask for ONE of:
  (a) reproduce the observation ONCE in the new topology -- this validates the discriminator
      and converts every later green into real evidence; or
  (b) identify the specific topology delta between the ORIGINAL failing run (evidence root
      t3-reverify-MNIpkPxh) and the five green runs -- CTest parallelism / -j, container CPU
      and memory allocation, concurrent load, PID namespace, ulimit -- then re-run at high
      repetition under the ORIGINAL topology, which is the only configuration ever observed
      to produce it.

IF neither yields a positive: register an UNATTRIBUTED INTERMITTENT carrying the five exact
identities, the topology of the one observing run, and the power bounds above, with a DUE at
FIRST RECURRENCE anywhere -- explicitly NOT pre-existing, NOT T1-owned, NOT closed.
```

That last shape is not invented for this: it is **exactly how R-3.40's original registration
handled a non-reproducing observation** — "so a second sighting is recognized as a second
sighting, not a first." That item then sat until it recurred, was diagnosed properly, and
closed unconditionally. The pattern works, and it is already in the registry.

## 5. The `nonzero_exit` claim — sound, but on ONE witness, not two, and it is worth more than claimed

I checked this at the source rather than concurring, because it touches a registry item.

**The claim holds.** But of the two cases offered, only one can witness a *Linux-specific*
contract:

```text
test_probe.cpp:246-268  "does not fall back to PATH when a pinned executable cannot spawn"
    #if defined(__APPLE__)  -> spawn_error
    #else                   -> nonzero_exit        <- LINUX-DISCRIMINATING. The witness.

test_probe.cpp:316-328  "reports a nonzero child exit"
    asserts nonzero_exit with NO platform conditional (verified: zero __APPLE__ occurrences
    in the case body) -> passes identically on macOS, so it cannot evidence a Linux contract.
```

One witness is still a witness and the contract is claimable. I am flagging it so the record
does not credit two independent witnesses where the evidence supplies one.

**And it is worth more than the SITREP claims.** That `#else` arm *is* the landed R-3.40 item
(13) fix `d22d474` — "assert the platform-correct outcome, `spawn_error` under `__APPLE__`,
`nonzero_exit` otherwise." I verified `d22d474` is an ancestor of the frozen base and that the
assertion-level platform split is present at all three heads:

```text
a02a65b  38963 bytes   __APPLE__ assertion splits 1 (plus 1 fixture-helper split at :103)
00c06d9  39234 bytes   same
a3501cc  39234 bytes   same
```

R-3.40(13) closed on green **at `e8aabc4`**. These runs re-confirm it at three heads it was
never measured at — which is the decay problem this lane has paid for before: a signed verdict
is a statement about a tree, and the tree moved. Worth recording as a re-verification, not just
a contract claim.

## 6. My own instrument defect, disclosed

Writing section 5 I ran a three-head census that returned **zero** `nonzero_exit` hits at
`a3501cc` — a file I had already read the assertion out of. The cause is a zsh-specific trap:
`"$sha:tests/test_probe.cpp"` applies zsh's **`:t` history modifier** to the variable, yielding
`a3501cc` + `ests/test_probe.cpp`. `git show` failed, the pipeline swallowed it, and `grep -c`
reported `0` — a clean, confident, wrong number. `${sha}` fixes it.

This is the second instrument in two relays that returned a false zero on a must-be-YES case
(the first was `\b` inside `git grep -E`). Both were caught only because I had an independent
positive to check against. I am not treating that as luck to be repeated: every census in this
relay was run against a known-YES case before its result was used, and rev1's O-5 already
requires the Implementer to do the same rather than inherit my word.

## 7. State

T3 is NOT final, NOT panelable; T4 HELD. No token exists for the date-oracle fix and none will
until you settle item 1 and a corrected PLAN-REVIEW approves rev1. No product, test, harness,
workflow, ref, or worktree byte was edited at my seat; the T3 branch is unmoved at `a3501cc`.
T2 head FINAL at `7688bbd`. R-4.38's binary inventory stays my stage-5 obligation. Schema
F+G-fenced. Merge is not push is not release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: read-only. `git show` of `tests/test_probe.cpp` at `a02a65b`/`00c06d9`/`a3501cc` and of `harness/bivharness/fixtures.py` at `a3501cc` for the digest re-verification; `git cat-file -t d22d474` and `git merge-base --is-ancestor d22d474 a02a65b`; a validated `git grep` census; and a local binomial computation for the power table. NO edit, NO ref created or moved, NO container run at this seat for this relay, NO merge, push, PR mutation, or remote CI. Docs lane: this relay + its INDEX row ride ONE explicit-path commit.
FINAL_GIT_STATUS_SHORT: this relay and its INDEX row are this seat's only working-tree delta at commit time; the shared checkout carries sibling-authored untracked paths, preserved and unclaimed
RELAY_LINT: exact-file WITH freshness immediately before commit; INDEX tail re-read before appending; `--index` run and diffed against the same lint on the pre-append blob to prove no new error is mine; commit gated on lint by logical AND; post-commit exact-file re-verify without freshness.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/SITREP-PLANNER-MF1-ACCEPTED-ORACLE-CONCURRENCE-REQUESTED-ATTRIBUTION-DISCRIMINATOR-HAS-NO-POSITIVE-20260822-021222.md` → TO `s4.orchestrator-planner`
- MF-1 ACCEPTED WITHOUT QUALIFICATION: disclosure is NOT authorization. I declared the deviation prominently and treated that as sufficient; it is not. A PLAN that substitutes a mechanism you named asks a later token to become the first record that "authorized epoch oracle" means "authorized any oracle the pair judged stronger." NO rev1 until you settle the mechanism
- MY OVERSTATEMENT CORRECTED IN MY OWN WORDS: `git show --date=raw` IS still git pretty-format output governed by git's raw date formatter — a stable RENDERING of the stored epoch and offset, NOT commit-object-byte access; `git cat-file commit` corroborates the values but does not convert a `git show` invocation into byte access. My PLAN's "no presentation layer remains to depend on" is FALSE as written; the accurate claim is the narrower empirical one: the raw formatter's output was MEASURED IDENTICAL on both git versions
- CHOICE FRAMED NOT MADE: B (hold `235525`'s letter) fixes portability, unblocks T3 now, drops the stored-offset coverage the test has today — and if you take it I ask the coverage delta be REGISTERED, not dropped silently. C (widen) keeps the coverage for one concurrence and nothing else; same file, same assertion, same scope, and the Implementer already independently reproduced the anchor, target digest, macOS node pass, and raw values. I recommend C and will file B without further argument — the call is yours and repeating the case would be relitigating it
- MF-2 CORRECT AND MINE: O-4 mutates `fixtures.py` but gated the `test_fixtures.py` digest, a file O-4 never touches — a restore gate that cannot see the residue it exists to catch. Their pinned digest independently VERIFIED at `a3501cc`: `harness/bivharness/fixtures.py` 9980 bytes, `6776756f8f50ea9f9c4a46d2cb9804586da4e628fa5698041ec00356a4b81303`. rev1 gates BOTH files after each scratch mutation
- MF-3 ACCEPTED (prose `FIXTURE_REPO` is satisfiable by the very standalone probe the obligation exists to rule out; rev1 prescribes a durable `--basetemp` under the evidence root and names the exact resulting repo path, bound identically on both hosts) and MINOR ACCEPTED (five versus six is the checklist defect, not a typo). NONE of MF-2/MF-3/MINOR depends on the oracle choice, so rev1 is blocked ONLY on item 1
- T1 ATTRIBUTION — I CONCUR WITH THE REFUSAL: declining to force either forecast branch is right, the exact identities were read from the retained log BEFORE measuring, and both instrument defects (missing `libsqlite3-dev`; the Catch2 comma-selector that selected zero tests and returned failure) are preserved rather than laundered
- THE FINDING THAT SHOULD CHANGE THE RULING: **the new instrument has NEVER produced the failure once** — not at base, not at final T1, not at the exact head that showed it. It has NO demonstrated must-be-YES, and an instrument that has never returned its positive cannot separate "absent" from "present and rare" — precisely the two hypotheses the ruling must choose between
- POWER IS NOT WHERE IT LOOKS (exact one-sided binomial, zero failures, `1 - 0.05^(1/n)`): n=1 at the EXACT observing head cannot exclude 95.0%; n=2 at base 77.6%; n=5 full-suite pooled 45.1%; n=60 isolated 4.9%; n=70 pooled 4.2%. The decisive-feeling 60/70 are measured on ISOLATED single-test processes while the original observation is FULL-SUITE, and descendant cleanup is exactly the class where full-suite context (concurrent processes, PID pressure, process-group reuse, CPU contention) is plausibly causal. High-power arm, wrong target; right-target arm, almost no power. **Rates up to ~45% are NOT excluded**
- RECOMMENDED RULING SHAPE: do NOT rule pre-existing (no base arm ever failed), do NOT rule T1-caused (T1 and T3 repeatedly green), and do NOT rule flaky/closed (the laundering direction, and the one ruling the evidence cannot license). BEFORE ruling ask for (a) reproduce ONCE in the new topology, validating the discriminator, or (b) identify the topology delta between the ORIGINAL failing run (`t3-reverify-MNIpkPxh`) and the five green runs — CTest parallelism/`-j`, container CPU/memory, concurrent load, PID namespace, ulimit — then re-run at high repetition under the ORIGINAL topology, the only configuration ever observed to produce it. If neither yields a positive, register an UNATTRIBUTED INTERMITTENT with the five identities, the observing topology, and the power bounds, DUE at FIRST RECURRENCE — explicitly NOT pre-existing, NOT T1-owned, NOT closed. This is exactly R-3.40's original-registration pattern ("a second sighting is recognized as a second sighting, not a first"), which then recurred, was diagnosed, and closed unconditionally
- `nonzero_exit` CLAIM SOUND BUT ON ONE WITNESS, NOT TWO: `test_probe.cpp:246-268` is Linux-discriminating via its `#else` arm and IS the witness; `test_probe.cpp:316-328` asserts `nonzero_exit` with NO platform conditional (verified zero `__APPLE__` occurrences in the case body) so it passes identically on macOS and cannot evidence a Linux contract. Claimable on one witness; flagged so the record does not credit two
- AND IT IS WORTH MORE THAN CLAIMED: that `#else` arm IS the landed R-3.40 item (13) fix `d22d474`, whose closure was green at `e8aabc4`. VERIFIED `d22d474` is an ancestor of the frozen base and the assertion-level split is present at all three heads (`a02a65b` 38963 bytes, `00c06d9` and `a3501cc` 39234 bytes; one assertion split each plus one fixture-helper split at `:103`). These runs RE-VERIFY a closed registry item at three heads it was never measured at — the verdict-decay problem this lane has already paid for
- MY OWN INSTRUMENT DEFECT: a three-head census returned ZERO `nonzero_exit` hits at `a3501cc`, a file I had already read the assertion out of. Cause is zsh-specific — `"$sha:tests/test_probe.cpp"` applies zsh's `:t` HISTORY MODIFIER, yielding `a3501cc` + `ests/test_probe.cpp`; `git show` failed, the pipeline swallowed it, `grep -c` reported a clean confident wrong `0`. `${sha}` fixes it. SECOND false-zero instrument in two relays (the first was `\b` inside `git grep -E`), both caught only by having an independent positive — so every census here was run against a known-YES case before its result was used, and rev1's O-5 makes the Implementer do the same rather than inherit my word
- STATE: T3 NOT final, NOT panelable; T4 HELD; no date-oracle token exists and none will until item 1 is settled and a corrected PLAN-REVIEW approves rev1; no byte edited at my seat and the T3 branch is unmoved at `a3501cc`; T2 head FINAL at `7688bbd`; R-4.38 binary inventory my stage-5 obligation; schema F+G-fenced; no remote CI, push, PR mutation, merge, publication, deployment or release; release hold ABSOLUTE
