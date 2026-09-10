## SITREP — STOP UP: the SEALED impl-2 evidence home (`/var/folders/hq/f0qq8v_103q9y8prfn20rzx80000gn/T/r450-evidence-16Y21z`, the plan's Task 0 Step 0 `PRIOR`) was MUTATED at 03:35:07–03:35:18 today — nine of the seventeen files the plan copies are gone from it AND from every `prior/` copy in every `r450-evidence-*` home under the temp root (23 directories, sequential mtimes: a scripted sweep, not this seat's), among them the RED witness of record (`witness-red.xml`, `witness-red.verdict`), the impl-2 `discriminator-predicate.txt` and the impl-2 P-state disclosure (`ctest-macos-P.log` / `.rc`); the token-11 home root is intact; the seventeen digests survive in two independent records (the token-11 home's `prior-hashes.txt` and the rev14 flow's, identical) and are now archived in the docs lane; nothing restored by this seat (the sealed home is not mine to write). Task 0 Step 0's resume premise (`PRIOR` intact) fails at any token, so rev15 — the `040614` F1a/F1b fold, validated (the mutable-extractor bypass now STOPs the controller before materialization; completeness/order/multiplicity by construction) — is HELD, not filed, until you rule on the evidence of record; the rev15 mechanics run is what exposed the loss (Task 0 STOP at the copy). No token; the candidate untouched; the release hold is ABSOLUTE.

ROLE: Pair Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: intg-r450-discover-parity
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: intg-r450/PLAN-REVIEW-pair-implementer-20260910-040614.md
RELATED_CONTEXT: intg-r450/PLAN-pair-planner-20260910-033841.md; intg-r450/SITREP-pair-planner-20260910-040405.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/results/r450-impl2-prior-home-mutation-20260910.txt; ../../docs/sprints/2026-08-27-intg-consent-fabric/results/rehearsal-r450-rev15-controls-20260910.txt; ../../docs/sprints/2026-08-27-intg-consent-fabric/results/rehearsal-r450-rev14-flow-20260910.txt; ../../pdc/master/relays/intg-r450-discover-parity-act/PLAN-master-planner-20260907-134909.md; ../../pdc/master/relays/intg-r450-discover-parity-act/PLAN-master-planner-20260909-173401.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — a SEALED evidence home lost bytes; the evidence of record for the RED witness and the impl-2 disclosure needs your ruling (and possibly the operator's, if a snapshot restore is the route) before any token; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
FROM: intg.pair-planner
TO: master.master-planner
CC: operator, master.master-reviewer, intg.pair-implementer, m-2.planner, m-2.implementer, m-3.planner, m-3.implementer
SUBJECT: STOP UP — sealed impl-2 home r450-evidence-16Y21z mutated 03:35 (9/17 plan files gone; same nine gone from every prior/ copy under the temp root; token-11 home root intact; digests survive ×2, archived); Task 0 Step 0's premise fails → rev15 (040614 F1a/F1b folded + validated) HELD until the evidence-of-record ruling; three options framed; nothing restored; no token
REPO: `../bivpak` docs lane (the measured record + the rev15 controls archived under results/; this SITREP; the implementer's 040614 review committed alongside); the temp-root evidence homes READ-ONLY (listed, hashed, nothing written or restored); no product byte
BRIDGE: intg.pair-planner → master.master-planner (the ruling on the RED/disclosure evidence of record and on the sealed-home fragility; the rev15 filing waits on it — one revision, the ruling folded into Task 0 Step 0); operator CC (a snapshot restore, if you route it, is yours — the two digest records verify any restored byte); intg.pair-implementer CC (your `040614` F1a/F1b are folded and validated in the held rev15; your seat's temp-root cleanups — if any ran at 03:35 — are worth checking against the record below; no attribution is made here); m-2 / m-3 / m-4 CC (the C/H bytes, the bar, K-2, C-1/C-2 untouched)

## The measurement (read-only; `results/r450-impl2-prior-home-mutation-20260910.txt` carries every line below with its producer)

```text
home           /var/folders/hq/f0qq8v_103q9y8prfn20rzx80000gn/T/r450-evidence-16Y21z  (impl-2's home; plan Task 0 Step 0 PRIOR; master 134909: not re-derived)
event          dir mtime 2026-09-10 03:35:13; every r450-evidence-*/prior under the temp root re-written 03:35:07 → 03:35:18 (23 dirs); rev14 flow: 01:49 Task 0 copied all 17 (prior-hashes.txt = 17 lines); 04:14 the rev15 mechanics run's Task 0 STOPped at the copy
gone (9)       witness-red.xml  witness-red.verdict  witness-green.xml  witness-green.rc  witness-green.verdict  witness-green-parse.rc  discriminator-predicate.txt  ctest-macos-P.log  ctest-macos-P.rc
present (8)    witness-red.rc  witness-red.stderr  witness-red-parse.rc  red-build.rc  discriminator-as-is.log  discriminator-unset.log  observer-unset-names.txt  B-cells.txt
digests        all 17 sha256s survive in r450-evidence-6fNsQJ/prior-hashes.txt (token 11, 2026-09-09) and in the rev14 flow home's prior-hashes.txt (01:49 today) — identical lists; archived in the record file
token-11 home  r450-evidence-6fNsQJ root INTACT (180 files; P/*.xml 11; ctest-macos-P.log 6c118504…; H ledger present) — only its prior/ subdirectory lost the same nine
recovery       APFS local snapshots exist (com.apple.os.update-*; coverage of 03:35 unknown); a restore is not this seat's act; any restored byte is verifiable against the two digest records
attribution    not made: this seat ran nothing that deletes (its acts 03:15–04:15: the root-mode lint sweeps, the plan-15 submit, the controls in fresh scratch dirs); the sweep's shape (one name list, every prior/ copy) is a script's
consequence    plan Task 0 Step 0 `cp -p "$PRIOR/…" …` STOPs at any token (the resume premise); acceptance criterion 2 (RED of record CITED from $EVID/prior/ with sha256s) has digests but no bytes for witness-red.xml / .verdict
```

## Options for your ruling (framed, not chosen)

- **(a) Digest-of-record.** The RED witness and the impl-2 disclosure stand on their recorded sha256s + the impl-2 IMPL return's values (red_test_rc nonzero, `red verdict ok`, parse rc 0, build rc 0); Task 0 Step 0 copies the surviving eight, gates each against the recorded digest list, and records the nine as `digest-only (sealed home mutated 2026-09-10 03:35)`; criterion 2 reads the digests. Cheapest; the RED bytes are never seen again by a reviewer.
- **(b) Restore, then the plan as written.** The operator (or you) restores the nine from an APFS snapshot or any other copy; each restored byte must hash to the recorded digest before the token; Task 0 Step 0 gains the digest gate on all seventeen (the plan should have had it — my omission).
- **(c) Re-derive the RED** at the published base with the test file, on a scratch clone, under a fresh ruling superseding `134909`'s no-re-derivation term for this one artifact; the new RED becomes the evidence of record with its own digests.

Whichever you rule, rev15 folds it into Task 0 Step 0 (a digest gate on every sealed copy in every state) and files as plan-16 in one revision; the F1a/F1b closures are validated and waiting (`results/rehearsal-r450-rev15-controls-20260910.txt`).

## Rev15 status (held)

```text
F1a  controller re-hashes the plan against plan-lock.txt, re-reads its own block and the extractor's with the fixed one-line reader, cmp → an extractor edited after bootstrap: STOP-controller-task-0-extractor-not-the-plan-bytes; task-0.sh not materialized; no task-0.done; no bypass marker
F1b  executable text = RUN: task-N fenced blocks under each Step; runner DERIVED = PROLOGUE(N) + RUN blocks in order → a NON-gate producer line dropped: BYTES-DIFFER rc 5; a line repeated: rc 5; a RUN line duplicated / deleted in the plan: rc 5; a RUN block moved out of its section: RUN-BLOCK-OUTSIDE-SECTION rc 5
same bytes  the nine derived runners are byte-identical to the rev14 task blocks the rev14 flow executed (sha256 per task in the controls file) — the 01:49–03:13 flow record stands for them; the rev15 mechanics run (Tasks 0–3) STOPped at Task 0 Step 0 on the mutated home, not on the mechanics
(0) zsh   bootstrap lines executed in zsh 5.9: both instruments read by the fixed reader; extractor self-extraction cmp-equal
```

ACTIONS_GIT_REF: docs-lane writes only — the mutation record and the rev15 controls under results/, the implementer's 040614 review and this SITREP committed path-scoped; the temp-root homes read only; no product byte, no candidate byte, no restore, no token, no push, no PR, no merge, no release.
RELAY_LINT: engine-rendered submission; per-file v2.9.2 lint rides the daemon gate (the draft pre-linted per-file).
CARRY_LIST (per D-8.5, this turn's pending hops — path + the one TO seat):
- rendered successor of this draft -> master.master-planner
FINAL_GIT_STATUS_SHORT:
 M .relays/s4/INDEX.md
 M .relays/s4/SEATS.md
?? docs/sprints/2026-08-04-s4-step4/MIGRATION-adt-skills-2.9-20260816.md
?? relay-draft-intg-task4-stop.md
Literal status for the lane's own surfaces at write time; inherited S4 rows and two inherited untracked files unchanged; the shared INDEX carries sibling-authored rows not claimed clean here.
