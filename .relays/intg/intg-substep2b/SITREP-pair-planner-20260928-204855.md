## SITREP — 203750 received, and packet assembly has started. Before the packet is presented, a scout of the landing's census on the PREDICTED merge (local `main` + H) shows that the landing act as declared would STOP at its census step. The pinned producer STOPs on an unclassified value. The pinned instrument (9c9391d5) cannot express the fix, because it reads exactly two accepted value digests (`fixture=` and `english=`) and the merge tree carries two more values, in both tree and history. The H0 rehearsal passed because H0 is the candidate tree WITHOUT the docs lane; the landing scans the merge head, which carries it. A ruling is needed before the packet's §7 can be written.

ROLE: Pair Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: intg-substep2b
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260928-203750.md
RELATED_CONTEXT: ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260928-181421.md; intg-substep2b/SITREP-pair-planner-20260928-175741.md; intg-substep2b/IMPL-pair-implementer-20260928-021324.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — the census instrument is master-pinned and its accepted-value format must change (see options); the packet, the Master Reviewer's verification, PR #28's undraft and the bare merge token all wait on that ruling; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
COMMISSION_TO: intg.pair-planner
CHARTER_DOC_ID: CH-intg-consent-fabric
PLAN_LOCK_ID: intg-substep2b-plan-20260915 @ sha256 acb2ac80569857a86628a0c8ee2e50387c872038c9f4fff514491af620a03048
FROM: intg.pair-planner
TO: master.master-planner
CC: master.master-reviewer, intg.pair-implementer, operator
SUBJECT: SITREP — landing census blocked at the merge head. The pinned producer STOPs `unclassified-value-at-…/OBLIGATIONS.md:112` on the predicted merge (tree 30cecdaa == merge-tree main H). Two values fall outside the instrument's two accepted digests: `sk-changing` (English, "task-changing"; 1 tree line, 290 history blobs) and a SYNTHETIC `ghp_` string from my rev42 walk's secret-in-patch control (1 tree line, 47 history blobs). Nothing else is outside. The instrument's two-slot header cannot classify them. Options with a recommendation below; the packet is HELD, unassembled, until you rule.
REPO: `../bivpak` docs lane — the scout record `results/landing-scout-2b/` committed at f5af6a6 (values masked except all-lowercase English); this relay (a path-scoped commit follows), no trailer; the candidate and the evidence home read only; the scout ran in a scratch clone; `../pdc` read-only
BRIDGE: intg.pair-planner → master.master-planner (the blocker, the options, the ask); Master Reviewer CC (what the packet will have to carry); implementer CC (the landing act's census step changes); operator CC (the merge token cannot be meaningful before this closes)

## What was measured (`results/landing-scout-2b/`, f5af6a6)

Method: a scratch clone of bivpak; local `main` (59d6fc0 at scout time) merged with H `cb19326a…` using `--no-ff`. The resulting tree is `30cecdaae27fccf5ac77c182e5e743a163b236c0`, identical to `git merge-tree --write-tree main H`. The tracked producer twin `results/rev45-walks/census_population.rev45.candidate.sh` (0c7124d7, byte-equal to the record copy) was run as the declaration runs it, with the merge as tree ref and history ref.

- The producer gives rc 1: `STOP-census-population line=32 reason=unclassified-value-at-docs/sprints/2026-08-27-intg-consent-fabric/OBLIGATIONS.md:112`.
- Survey of the tree arm (first match per line, the producer's rule), 94 lines:
  - fixture `sk-complete`: 90 lines, 45 paths;
  - english `sk-structured`: 2 lines;
  - UNCLASSIFIED `sk-changing`, sha256 `6b5faf37…`: 1 line (OBLIGATIONS.md:112, prose "task-changing");
  - UNCLASSIFIED `ghp_` (34 chars), sha256 `f419886e…`: 1 line (`results/rev42-walks/walk42.sh:27`).
- Survey of the history arm (`git grep -h -o` over all 1,853 commits reachable from the predicted merge): the same four values and no others.
  - `sk-changing` appears in 290 blobs and the `ghp_` string in 47.
  - Neither is reachable from B, so both entered with the docs lane after the R-4.49 landing.
- The `ghp_` string is SYNTHETIC. I wrote it on 2026-09-27 (78e87b3) as the injected secret in rev42's `secret-in-patch` negative control. Its body is 30 distinct characters in ascending order, with no run longer than 1. It is not a credential. It is, however, a GitHub-token-SHAPED string in a commit the landing would publish.
- Why it can't be fixed downstream: the instrument's line 30 reads ONE header line, `== ACCEPTED VALUE DIGESTS: fixture=<64> english=<64>`, which has room for two values. Rewording either line would not help, because the history arm still sees 290 and 47 blobs. Rewriting history is ruled out by charter rule 4 and the pinned shas. Narrowing the scan to leave out the docs lane is the R-4.50 anti-pattern.

## Options

- **(A) — recommended.** Revise both artifacts to carry an accepted-value SET: the producer's in-memory classification and the instrument's header each become a list of `(class, sha256)` pairs.
  - Classification of the two new values:
    - `sk-changing` → class C (English, like `sk-structured`);
    - the synthetic `ghp_` control → class B (a non-product fixture copy, like `sk-complete` outside product paths).
  - The cost is two new pinned digests. Each artifact is re-exercised with the r449 rev3 discipline: pipefail, per-stage status, and a must-be-YES/must-be-NO pair, including a mutant value that must STOP.
  - Rehearsal on the predicted merge head, not on H0.
  - Authorship follows r449: the pair writes it and the Master Reviewer verifies it.
  - The plan needs a Task 11/12 wording change (rev49) that names the new producer and instrument pins and makes the rehearsal object the predicted merge.
- **(B)** Keep the instrument, and have the landing act run the census with an override for the two known values. This is a narrower scan in disguise, and I do not recommend it.
- **(C)** Rule that the landing census scans the product tree only. That is a bar change, and it is yours and the operator's to make, not mine.

Separately, whatever the option: the `ghp_` string may interest GitHub push protection on the landing push of `main` to a public repo. Real `ghp_` tokens carry a checksum, which a synthetic ascending string will almost certainly fail, so I expect no block. It cannot be tested without pushing, so I am naming it rather than assuming it.

## The producer path (your §3)

Under any option, the packet pins the TRACKED path. Under (A) that is the revised producer; under (B) or (C) it is `results/rev45-walks/census_population.rev45.candidate.sh` at `0c7124d7` (tracked, `cmp` equal to the record copy, and location-independent: no `$0`, `dirname` or `cd`; it reads the repository at its working directory). The untracked record copy stays uncited as a path.

## Also measured for the packet (unchanged by this finding)

- **Identity:** H `cb19326a…`; B `186adf7d…`; `merge-base main H` == B; 26 commits in B..H with zero trailer lines; PR #28 OPEN, draft, head H, MERGEABLE.
- **Cells 1–2 at H (head gate `c11`):** tidy 0, coverage 37/37, the five macOS producers rc 0 with 0 failures, container rc 0 with 0 Linux failures.
  - Tuples: biv_tests macOS 486/0/0/3 and Linux 488/0/0/1; engine 82, git 6, subprocess 12, probe 25, all 0 failures.
  - Final count gates rc 0 on both targets.
  - Only `harness-selftest` failed, with 3 failed of 1,055 and every name inside the R-4.35 family (foreign empty); the bar is `pass-r435-disclosed-registered-red`.
- **Cell 3:** m-1 033430, m-3 033409 and m-4 033613, re-hashed equal to your pins.
- **Blast radius:** 336 docs-lane commits above the pin (`.relays` and `docs` only; no non-docs delta), all with placeholder `@local` identities and zero trailers; merge-tree clean; overlap 0.

Asked of you: an option word, and under (A) a word on the two classifications. I then write the revised artifacts and rev49 for the implementer's exact-hash review, rehearse on the predicted merge head, and assemble the packet with a §7 that PASSes on the object the landing scans.

ACTIONS_GIT_REF: docs-lane writes only: the scout record (f5af6a6); this relay (a path-scoped commit follows), no trailer; the plan artifact at b127a02 untouched; product bytes untouched; the scout in a scratch clone only.
RELAY_LINT: engine-rendered submission (daemon on kit 2.9.6); per-file 2.9.6 `relay-lint.py --no-freshness` on the draft; python-written; the draft scanned with the census alternation before submit (no value outside the four above); the filed bytes compared to the draft by digest; every newer upstream file opened before this submit (the listing run as its own command).
FINAL_GIT_STATUS_SHORT:
none — no path-scoped change at write time
Literal path-scoped status for this seat's own writes at write time; the untracked results record is impl-17's; the shared bivpak tree carries other seats' untracked relays and a daemon-projected SEATS.md, not claimed clean here.
