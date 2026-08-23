## SITREP — I closed my own open caveat: main measures 413 exactly, so your structural settlement is now MEASURED, not inferred. Also retiring a wrong number I produced, and narrowing the Linux gate from "unmeasured" to one specific unknown

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-matrix-r438-main-consistency-measured
PARENT_DISPATCH_ID: s4-matrix-wave-a-furl1-arm-b-receipted-nits-r438-routed
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-FURL1-ARM-B-RECEIPTED-NITS-RECEIVED-R438-VERIFIED-ROUTED-COSIGN-SURFACED-20260823-033511.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/SITREP-PLANNER-R438-INVENTORY-PLUS-COUNT-GATE-WOULD-RED-AT-MERGE-NOT-GREEN-ROUTED-UP-20260823-011248.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new gate. This closes the one caveat I left open in `011248` and hardens a claim already routed to master, so master and m-3 act on a measurement rather than an inference. The F-URL-1 operator co-sign remains the operator's and I do not touch it. No merge, push, PR mutation, remote CI, schema act, publication, deployment, or release. The release hold is ABSOLUTE
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: authorized pre-edit T4 `29120d09891bfc46e80635c2212befa22a0e2604` on FINAL T3 `70601fc201b3c41d2542d82399787b5febcbf03c`
CANDIDATE: local T4 `6ba01ef92ef5052b317f6210fa202d5577e1e6c1` — unchanged by this relay
FROM: s4-matrix.planner
TO: s4.orchestrator-planner
CC: operator, s4-matrix.implementer, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: Main measures 413 TEST_CASEs across 22 biv_tests files versus the candidate's 388 across 21, differing by exactly test_probe.cpp and nothing else — the introduced-not-inherited settlement is confirmed by measurement; my earlier 359 was an extractor artifact and is formally retired; and the Linux gate narrows to one unknown, its successes/skips split, since total registration is platform-independent

## 1. Why I measured a settlement you had already made

You settled my open fork structurally and routed it up. The structure was sound, and I could have
left it. I did not, because the inference has a load-bearing premise that nobody had checked:
that main's `biv_tests` source set equals the candidate's **plus** `test_probe.cpp` and differs in
no other way. If Wave-A had also added or moved any other file into or out of `biv_tests`, main's
total would not be 413 and the ownership conclusion — already travelling upward to master — would
invert.

My own earlier reading pointed that way: 14 files at main against 21 at the candidate. I had
discarded it as an extractor artifact rather than report it, but a discarded number is not a
resolved one.

## 2. Measured

Parsed with a balanced-parenthesis scan of the `add_executable(biv_tests …)` block plus every
`target_sources(biv_tests …)` block, rather than the non-greedy regex that failed me twice.

```text
main       biv_tests   22 files   413 TEST_CASEs
candidate  biv_tests   21 files   388 TEST_CASEs      (binary --list-tests: 388)
only in main            tests/test_probe.cpp
only in candidate       (none)
```

**Main measures 413. The macOS want total is 410 + 3 = 413. Main is consistent and green.**

The parser validates itself two ways: the candidate figure it produces, 388, equals the binary's
own listing exactly, and every file it names exists at both refs (asserted, not assumed). My
earlier **359 across 14 files was an extractor artifact and is formally RETIRED** — it should not
resurface in any downstream record. The non-greedy `\n\)` terminator truncated the source block;
the same class of failure as the `awk` range that overran, in the opposite direction.

So your settlement holds, and it is now a measurement:

```text
main       consistent at 413, GREEN
candidate  388 -> the gate's 410-vs-385 red is INTRODUCED AT MERGE by T1's split
Wave-A     does NOT inherit a pre-existing red
```

## 3. The Linux gate, narrowed

`011248` listed Linux as flatly unmeasured. I can tighten that without a Linux run.

`TEST_CASE` registration is compile-time and I checked all 21 candidate `biv_tests` sources for a
`TEST_CASE` reachable inside a preprocessor conditional: **zero**. So the 413/388 totals are
platform-independent, and the Linux gate — `want` 412 successes + 1 skip = **413**, the same
pre-split total, running the same single binary — reds at merge by the same mechanism.

What still needs a Linux run is only the **successes/skips split** at 388, since which cases skip
is a runtime property and differs between the legs (macOS 3, Linux 1). The failure is inferable;
the exact numbers are not, and I will not state them.

## 4. What this changes and does not change

It changes nothing about the disposition — the repair is still m-3's `.github` gate-design act and
this lane still touches no workflow byte. It changes the evidence tier under a claim that is
already in front of master and the operator: introduced-not-inherited is now measured on both
sides of the merge, so nobody has to take the structural argument on faith.

R-4.43 and the F-URL-1 operator co-sign are untouched by this relay, T4 FINAL remains held on that
co-sign, and no human lens is routed. All three nits stand at the severities you accepted.

T1 `00c06d9`, T2 `7688bbd`, T3 `70601fc` FINAL; T4 IMPLEMENTED at `6ba01ef`, panel-adjudicated,
FINAL held. Merge is not push and neither is release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: none — no edits made at this seat; no product, test, workflow, branch, ref or worktree moved, and `6ba01ef` is untouched by this relay. Read-only at my seat: a balanced-parenthesis parse of the `add_executable(biv_tests …)` and `target_sources(biv_tests …)` blocks at main and at the candidate, with existence of every named file asserted at both refs; `TEST_CASE` counts over both source sets; a preprocessor-conditional scan across all 21 candidate sources; and a cross-check of the parser's candidate total against the previously measured binary listing. No build was created or run, no workflow byte touched, no merge, push, PR mutation, or remote CI. Docs lane: this relay and its INDEX row ride ONE explicit-path commit.
FINAL_GIT_STATUS_SHORT: this relay and its INDEX row are this seat's only working-tree delta at commit time; `git status --porcelain` over `harness/`, `src/`, `tests/`, `CMakeLists.txt`, `.github/` is empty; the shared checkout carries sibling-authored untracked paths, preserved and unclaimed
RELAY_LINT: all three arms before commit — exact-file WITH freshness; `--index` error set path-normalized and diffed against the pre-append blob; `--relay-root` run with this relay present AND moved aside, requiring identical error sets. `substantive_actions_ref` and `implementation_work_claimed` measured False; `operational_token_text` carries no bare token. INDEX tail re-read for NEW INBOUND addressed to this seat, not only for monotonicity.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/SITREP-PLANNER-MAIN-CONSISTENT-413-MEASURED-SETTLEMENT-CONFIRMED-MY-359-RETIRED-LINUX-NARROWED-20260823-040534.md` → TO `s4.orchestrator-planner`
- WHY I MEASURED A SETTLEMENT ALREADY MADE AND ROUTED: the structural argument was sound but rested on an UNCHECKED premise — that main's `biv_tests` source set equals the candidate's PLUS `test_probe.cpp` and differs in NO other way. Had Wave-A moved any other file into or out of `biv_tests`, main's total would not be 413 and the ownership conclusion ALREADY TRAVELLING UP TO MASTER would INVERT. My own earlier reading pointed that way (14 files at main vs 21 at the candidate); I had discarded it as an artifact, but A DISCARDED NUMBER IS NOT A RESOLVED ONE
- MEASURED WITH A BALANCED-PAREN PARSER (not the non-greedy regex that failed me twice): main `biv_tests` = 22 files / **413 TEST_CASEs**; candidate = 21 files / **388**; the ONLY difference is `tests/test_probe.cpp`, with NOTHING only-in-candidate. macOS want total = 410 + 3 = 413, so **MAIN IS CONSISTENT AND GREEN**
- PARSER SELF-VALIDATED TWO WAYS: its candidate figure 388 equals the binary's own `--list-tests` exactly, and every file it names was ASSERTED to exist at both refs rather than assumed
- MY EARLIER 359 ACROSS 14 FILES IS FORMALLY RETIRED as an extractor artifact and must not resurface in any downstream record — the non-greedy `\n\)` terminator TRUNCATED the source block, the same class of failure as the `awk` range that OVERRAN, in the opposite direction. Two failures of the same parser family in opposite directions, both caught only by cross-checking against an independent measurement
- YOUR SETTLEMENT HOLDS AND IS NOW A MEASUREMENT: main consistent at 413 GREEN; candidate 388; the gate's 410-vs-385 red is INTRODUCED AT MERGE by T1's split; Wave-A does NOT inherit a pre-existing red. Master and m-3 now act on a measurement on BOTH sides of the merge rather than on faith in a structural argument
- LINUX GATE NARROWED WITHOUT A LINUX RUN: `TEST_CASE` registration is compile-time and I scanned all 21 candidate sources for a `TEST_CASE` reachable inside a preprocessor conditional — **ZERO** — so the 413/388 totals are PLATFORM-INDEPENDENT and the Linux gate (`want` 412 + 1 skip = **413**, same pre-split total, same single binary) REDS AT MERGE by the same mechanism. What still requires a Linux run is ONLY the successes/skips split at 388, since which cases skip is a RUNTIME property differing per leg (macOS 3, Linux 1) — the failure is inferable, the exact numbers are NOT, and I do not state them
- CHANGES NOTHING ABOUT DISPOSITION: the repair remains m-3's `.github` gate-design act and this lane still touches no workflow byte. It raises the EVIDENCE TIER under a claim already before master and the operator. R-4.43 and the F-URL-1 operator co-sign are UNTOUCHED by this relay, T4 FINAL remains HELD on that co-sign, no human lens routed, and all three nits stand at the accepted severities. T1 `00c06d9` / T2 `7688bbd` / T3 `70601fc` FINAL; T4 `6ba01ef` panel-adjudicated, FINAL held; no remote CI, push, PR mutation, merge, publication, deployment or release; release hold ABSOLUTE
