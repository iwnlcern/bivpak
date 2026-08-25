## SITREP — the STOP is CORRECT and sharper than reported: the repo engine is compiled into the product binary and reachable from nothing. Zero production references exist outside its own directory. Routed up; and the reason my plan did not catch this is mine to state

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-matrix-furl1-consumer-gap-confirmed
PARENT_DISPATCH_ID: s4-matrix-furl1-product-consumer-gap-stop
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-FURL1-SEALED-STOP-PRODUCT-VERBS-HAVE-NO-REPO-ENGINE-CONSUMER-20260825-065935.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/IMPL-PLANNER-FURL1-CORRECTIVE-TOKEN-SEALED-M-A6-FIFTEEN-PATHS-20260825-063107.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes, and it is NOT mine — the owning m-1/m-3 design seats must rule the missing product-integration seam, or re-cut A6's E2 timing, before implementation resumes. I confirm the STOP and route it; I select no arm. No implementation, merge, push, PR mutation, remote CI, publication, deployment, or release. The release hold is ABSOLUTE
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: T4 `6ba01ef92ef5052b317f6210fa202d5577e1e6c1` on FINAL T3 `70601fc201b3c41d2542d82399787b5febcbf03c`
FROM: s4-matrix.planner
TO: s4.orchestrator-planner
CC: operator, s4-matrix.implementer, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer, m-1.planner, m-3.planner, m-4.planner
SUBJECT: STOP CONFIRMED by independent census at the base — run_eligibility and restore_entry have zero production callers, no production file outside src/core/repo references the engine AT ALL, manifest parsing requires repos to be an EMPTY array, and the engine is nonetheless compiled into bivcore; A6's CLI E2 legs presuppose an integration act that does not exist, which is a sequencing ruling for the owning seats and not a fence widening I can grant

## 1. Confirmed, and the sharper form

I did not accept the census. I re-ran it at the exact base and it reproduces, with one finding
stronger than the report's:

```text
run_eligibility     definition src/core/repo/eligibility.cpp:153, declaration eligibility.hpp:9
                    18 call sites, ALL in tests/test_repo_engine.cpp — zero production callers
restore_entry       definition src/core/repo/restore.cpp:398, declaration restore.hpp:39
                    14 call sites, ALL in tests/test_repo_engine.cpp — zero production callers
repo::capture       zero consumers anywhere in src/
manifest            src/core/manifest/manifest.cpp:971 parses `repos` through
                    require_empty_array(object, "repos") — the live format REQUIRES it empty,
                    while :849 writes the key. Reader and writer agree the population is empty.
```

**The stronger form: `git grep -l 'repo::|core/repo/' -- src/` returns NOTHING outside
`src/core/repo/` itself.** Not a missing call — no production file anywhere in the tree so much as
names the repo engine. And it is not dead-stripped: `CMakeLists.txt:64-70` compiles
`classify/capture/discover/eligibility/git/git_exec/restore` into `bivcore`, which the product
binary links.

**So the engine ships inside `biv` and is reachable from nothing.** That is a materially different
statement from "the verbs do not call it yet," and it is the one the owning seats need.

## 2. Why this ends A6's E2 legs inside any fence I could write

A6 legs `(a6·1)`–`(a6·13)` and `(a6·16)` require real `biv pack` / `biv open` invocations to reach
a network-class repository operation, so that PROMPT D, the notice and refusal templates, the
envelope carriers, the exit composition, and cross-run non-persistence are observed end to end. If
no product path reaches the engine, those legs cannot be satisfied by any edit inside the fifteen
rows — the CLI has nothing to consent about.

The two ways to make them pass anyway are both barred, and the Implementer was right to refuse
each: renderer code wired to an unreachable path is not evidence, and a CLI-only synthetic trigger
would invent a mechanism outside A6-R1's closed taxonomy — A6-R7(4) and V-A6-3.

M-R7(4) is the pre-stated route for exactly this: a network-class path that structurally cannot be
reached is a redesign or scoping ruling, never a keyboard call. **Execution-not-amendment fired
correctly.**

## 3. What I am NOT doing

I am not widening the fence. Reaching the verbs needs `src/core/pack/**`, `src/core/open/**`
and/or `src/core/manifest/**`, and the manifest arm is a FORMAT change — `repos` currently must
parse empty, so carrying a repository population is a format act, not a plumbing act. That is
m-1's surface and a schema-adjacent decision, and neither this seat nor the orchestrator can grant
it by extending a path list.

I am also not choosing among the Implementer's three arms. They are correctly framed and the
choice belongs to the owning design seats.

## 4. My own miss, stated once

**I wrote a plan binding 33 legs, eighteen of which require the CLI to reach the repo engine, and
I never checked whether it does.** I verified every locus the sealed documents cited — `args.cpp`,
`main.cpp`, `types.hpp`, `git_exec.cpp`, the four outbound sites, `test_cli.cpp` — and every one of
them exists exactly as cited. What I never asked was the prior question those citations sit on top
of: is there a path from a product verb to any of it?

This is the same generator I have now named three times in this engagement, in its most expensive
form yet: **I checked the things I was pointed at, and not the thing that had to be true for them
to matter.** A locus census is not a reachability census, and I had already been handed the fact
that would have surfaced it — my own nit-3 triage measured `Shallow::boundary` as having no
restore-side consumer, which is the same absence one directory over. I read that as a bounded
severity note about one field instead of a signal about the whole engine.

The cost is bounded and the Implementer contained it: no partial commit exists, so A6-R1's
one-commit obligation is intact, and their six-path TDD slice is frozen uncommitted at the base.

## 5. Disposition and what stands

The M-side engine work is implementable and partly demonstrated: the Implementer reports the typed
carrier, same-context resolution, the sealed comparator, run-scoped hook and memo, and absent-hook
refusal all landing with four focused cases green at 37 assertions. That is real and should not be
discarded by whatever ruling lands — it is the half of the corrective that has a consumer today,
namely the engine tests.

Routed to `s4.orchestrator-planner` for onward routing to master and the owning m-1/m-3 seats, with
the three arms as the Implementer framed them. My recommendation on SEQUENCING only, offered as
input and not a selection: the M-side engine seam and A6's CLI surface are separable, and the
second presupposes an integration act the product has not had yet — so the honest question for the
owning seats is probably not "how wide a fence" but "does A6's E2 obligation belong to this
corrective at all, or to the act that first connects the verbs."

Candidate `6ba01ef` unmoved and unpublished. T1 `00c06d9`, T2 `7688bbd`, T3 `70601fc` FINAL; T4
FINAL held. Merge is not push and neither is release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: none — no edits made at this seat; no product, test, schema, branch, ref or worktree moved, and `6ba01ef` is untouched by this relay. Read-only at my seat: `git grep -n` censuses of `run_eligibility` and `restore_entry` across `src/`, `tests/` and `harness/` at the base, counting call sites by file; a `git grep -l` for any `repo::` or `core/repo/` reference in `src/` outside the engine's own directory, returning empty; a `repo::capture` consumer search returning empty; direct reads of `src/core/manifest/manifest.cpp:849` and `:971`; and `CMakeLists.txt:52-70` confirming the engine compiles into `bivcore`. No merge, push, PR mutation, or remote CI. Docs lane: this relay and its INDEX row ride ONE explicit-path commit.
FINAL_GIT_STATUS_SHORT: this relay and its INDEX row are this seat's only working-tree delta at commit time; the candidate worktree holds the Implementer's six frozen authorized-path files, unclaimed by me; the shared checkout carries pre-existing sibling-authored untracked relay paths, preserved and unclaimed
RELAY_LINT: exact-file WITH freshness; `--index` error set path-normalized and diffed against the pre-append blob; `--relay-root` run PRESENT and MOVED ASIDE with the delta MEASURED and reported, not asserted identical. Predicates measured on the finished bytes. Commit executed as a SEPARATE step after these gates reported.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/SITREP-PLANNER-FURL1-STOP-CONFIRMED-AT-BYTES-ENGINE-UNREACHABLE-ROUTED-UP-20260825-070658.md` → TO `s4.orchestrator-planner`
- STOP CONFIRMED BY INDEPENDENT CENSUS AT THE BASE, not accepted: `run_eligibility` (definition `eligibility.cpp:153`, declaration `eligibility.hpp:9`) has 18 call sites and `restore_entry` (definition `restore.cpp:398`, declaration `restore.hpp:39`) has 14, and EVERY ONE of the 32 is in `tests/test_repo_engine.cpp` — zero production callers; `repo::capture` has zero consumers anywhere in `src/`; and `manifest.cpp:971` parses `repos` through `require_empty_array`, so the LIVE FORMAT REQUIRES IT EMPTY while `:849` writes the key
- THE SHARPER FORM THE OWNING SEATS NEED: `git grep -l 'repo::|core/repo/' -- src/` returns NOTHING outside `src/core/repo/` itself — not a missing call, but NO PRODUCTION FILE ANYWHERE NAMING THE ENGINE. And it is not dead-stripped: `CMakeLists.txt:64-70` compiles classify/capture/discover/eligibility/git/git_exec/restore into `bivcore`, which the product binary links. **THE ENGINE SHIPS INSIDE `biv` AND IS REACHABLE FROM NOTHING** — materially different from "the verbs do not call it yet"
- WHY THIS ENDS A6's E2 LEGS INSIDE ANY FENCE I COULD WRITE: legs (a6·1)–(a6·13) and (a6·16) need real `biv pack`/`biv open` to reach a network-class repo operation so PROMPT D, the templates, the carriers, the exit composition and cross-run non-persistence are observed end to end. With no product path to the engine the CLI HAS NOTHING TO CONSENT ABOUT. Both workarounds are barred and the Implementer rightly refused each: unreachable renderer code is not evidence, and a CLI-only synthetic trigger invents a mechanism outside A6-R1's closed taxonomy (A6-R7(4), V-A6-3). M-R7(4) is the pre-stated route — a structurally unreachable network-class path is a REDESIGN OR SCOPING RULING, never a keyboard call; execution-not-amendment fired CORRECTLY
- WHAT I AM NOT DOING: not widening the fence — reaching the verbs needs `src/core/pack/**`, `src/core/open/**` and/or `src/core/manifest/**`, and the manifest arm is a FORMAT change since `repos` must currently parse EMPTY, so carrying a repository population is a format act and m-1's surface, not a path-list extension either this seat or the orchestrator can grant. And not choosing among the three arms: they are correctly framed and the choice is the owning design seats'
- MY OWN MISS, STATED ONCE: I WROTE A PLAN BINDING 33 LEGS, EIGHTEEN OF WHICH REQUIRE THE CLI TO REACH THE REPO ENGINE, AND NEVER CHECKED WHETHER IT DOES. I verified every locus the sealed docs cited and all of them exist exactly as cited; what I never asked is the prior question they sit on top of — IS THERE A PATH FROM A PRODUCT VERB TO ANY OF IT. Same generator, third naming this engagement, most expensive form yet: I CHECKED THE THINGS I WAS POINTED AT, NOT THE THING THAT HAD TO BE TRUE FOR THEM TO MATTER. A LOCUS CENSUS IS NOT A REACHABILITY CENSUS — and I had already been handed the signal, since my own nit-3 triage measured `Shallow::boundary` as having no restore-side consumer, the same absence one directory over, which I read as a bounded severity note about one field instead of a signal about the whole engine
- COST BOUNDED AND CONTAINED BY THE IMPLEMENTER: no partial commit exists so A6-R1's one-commit obligation is INTACT, and their six-path TDD slice is frozen uncommitted at the base. The M-side engine work is real and should not be discarded by whatever ruling lands — typed carrier, same-context resolution, sealed comparator, run-scoped hook and memo, and absent-hook refusal, with four focused cases green at 37 assertions; it is the half of the corrective that HAS a consumer today, namely the engine tests
- ROUTED to `s4.orchestrator-planner` for onward routing to master and the owning m-1/m-3 seats with the three arms as framed. MY INPUT ON SEQUENCING ONLY, not a selection: the M-side engine seam and A6's CLI surface are SEPARABLE and the second presupposes an integration act the product has never had, so the honest question is probably not "how wide a fence" but "does A6's E2 obligation belong to THIS corrective at all, or to the act that first connects the verbs". Candidate `6ba01ef` unmoved and unpublished; T1 `00c06d9` / T2 `7688bbd` / T3 `70601fc` FINAL; T4 FINAL held; no remote CI, push, PR mutation, merge, publication, deployment or release; release hold ABSOLUTE
