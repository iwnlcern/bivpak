## MERGE-GATE — packet revision 3 for your RE-VERIFICATION: `docs/sprints/2026-08-27-intg-consent-fabric/results/intg-substep2b-merge-gate.md` (sha256 `07418d95aa8637bee7b6c8846132e26aa692ffefb34f2928b44d7f5a8eb22ea8`, commit d1552ff). It folds F-2B-VP-2 in full. It is HELD at H `cb19326a`: cells 1–3 are unchanged and DONE, and cell 4 is PENDING.

ROLE: Pair Planner
PHASE: MERGE-GATE
AUTHORITY: report-only
DISPATCH_ID: intg-substep2b-merge-packet
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: ../../pdc/master/relays/intg-2b-wiring-act/MERGE-GATE-master-reviewer-20260930-021153.md
RELATED_CONTEXT: intg-substep2b/MERGE-GATE-pair-planner-20260930-020200.md; ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260930-012837.md; ../../pdc/master/relays/intg-2b-wiring-act/MERGE-GATE-master-reviewer-20260929-041058.md; ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260929-163054.md; intg-substep2b/PLAN-REVIEW-pair-implementer-20260930-001212.md; intg-substep2b/MERGE-GATE-pair-planner-20260929-025641.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/results/intg-substep2b-merge-gate.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — cell 4, the operator's condition-4 merge token on H (a BARE `DISPATCH MERGE` TO intg.pair-implementer filed under ../bivpak/.relays/intg/), presented by master only after your re-verification, and preceded by the operator's undraft of PR #28; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
COMMISSION_SCOPE: the operator-authorized integration phase (2026-08-26) executed by ONE commissioned pair — sub-step 1 first, the A6 rev14 consent-UX fabric with the engine unwired per the sealed spine; subsequent sub-steps (format act consuming LOCKED M rev8 + LOCKED N; then wiring at product scope) each behind their standing gates incl. m-4's reachability re-review before any wiring; sealed design only; STOPs route UP; no merge/push/publication/release authority
COMMISSION_TO: intg.pair-planner
CHARTER_DOC_ID: CH-intg-consent-fabric
PLAN_LOCK_ID: intg-substep2b-plan-20260915 @ sha256 4832b147e9fb0980dbf3896d704113fbb0c196a2f5ef32017f165d97fd8443f1
BRANCH: intg/substep2b-wiring at H cb19326a5596bf30eab2ec2b9baeda0bc77be895 (remote == H by ls-remote at this filing; PR #28 OPEN, draft, MERGEABLE, head H)
TARGET_BRANCH: main — the TRUE local merge under the operator's token, M derived once, the census and both record clauses on M BEFORE the ONE push of M (R-4.52)
BASE: B = origin/main = 186adf7d67171bd7afe621f39b657a1a113ce299 (ls-remote at this filing)
FROM: intg.pair-planner
TO: master.master-reviewer
CC: master.master-planner, operator, intg.pair-implementer, m-1.planner, m-3.planner, m-4.planner
SUBJECT: MERGE-GATE — packet revision 3 (07418d95 @ d1552ff) for your re-verification. It folds F-2B-VP-2: every §7 receipt goes through REC (write, read back, exit on failure), and step (5) holds the push output in memory, with its one post-push receipt through PREC ending in `STOP post-push … SPENT … NO retry`. Walked at the real filesystem boundary with push invocations COUNTED: the record-index, record-history, step1 and step2 sinks STOP with 0 push invocations and the remote at B. The push-dry-run and push-attempt sinks STOP with 1 invocation (the dry run) and the remote at B. The push-result sink lands and then STOPs rc 1. YES gives landing-pushed-ok. The pins, the census and every gate predicate are byte-unchanged; §7 run.zsh 666e2e9b.
REPO: `../bivpak` docs lane — packet revision 3 and the walk drivers and records committed d1552ff (revision 2 at 9aac28b); this relay (a path-scoped commit follows), no trailer; the candidate, the evidence home and the runners read only except the governed `t-oracle.txt` rewrite (predecessor preserved); walks in scratch clones against local bare repos; no remote write; `../pdc` read-only
BRIDGE: intg.pair-planner → master.master-reviewer (the object to re-verify); master CC (your presentation follows only a clean re-verification); implementer CC (§7 is your landing act, as runnable blocks); operator CC (after the re-verification and the presentation: your undraft, then your bare token)

## F-2B-VP-2, as folded

Your finding is accepted with no dispute: `| tee` receipts were unchecked, and a failed write could reach the push with a final rc 0.
- **The writer, defined once in block (0).** `REC <file> <text>` writes, reads the file back and compares, and `exit`s the landing shell on either failure (`STOP receipt-write <name>` or `STOP receipt-readback <name>`). Nothing relies on `pipefail`.
- **Every receipt goes through `REC`:** `step1.txt`, `step2.txt`, `record-index.txt`, `record-history.txt`, `push-dry-run.txt` and `push-attempt.txt`.
  - The pin files are read back against their digests in the step (0) python.
  - The substituted scripts and the census output keep their `||` STOPs; a truncated script cannot print the exact pass line, and the census receipt must end `result=PASS`.
  - A scan of every write in the six blocks is clean of `tee`.
- **Step (5), restructured.**
  - The dry run's output is captured in memory and kept by `REC`.
  - `push-attempt.txt` (`REC`) is the LAST pre-push write.
  - The ONE push's output is held in memory, so no file write can block or mask it. Then comes `ls-remote`, with its rc bound.
  - The one post-push receipt, `push-result.txt`, uses the non-exiting `PREC` (write plus read-back), because nothing can undo a spent attempt.
  - The step ends `landing-pushed-ok M=<M>` only if the push rc is 0, the ls-remote rc is 0, the remote equals M and the receipt was kept. Otherwise it ends `STOP post-push … the attempt is SPENT; report UP as failed/unverified; NO retry` at rc 1.
- **Unchanged:** the three pins (327/`2df745ff…`, 221/`af8c1927…`, 1150/`bcbb5c97…`), the census contract, every gate predicate, master's two 012837 asks, and the history pre-check on both parents.

## The walks, at the real command boundary (both extract §7's six blocks from this packet; the final §7 digests to the walked `666e2e9b…`)

`results/landing-2b/landing-walk-7r3.txt` (driver `landing-walk-7r3.sh`):
- A sink arm inserts ONE line after block 0, `mkdir "$LD/<receipt>"`, so that receipt's write fails at the real filesystem boundary. No packet command is edited.
- A pass-through git wrapper logs every `push` invocation, dry runs included.
- Each arm runs in its own clone with its own local bare remote, which starts at B.

```text
arm                        result                                                     push invocations   remote
yes                        landing-pushed-ok, zsh rc 0                                2                  M
sink step1.txt             STOP receipt-write step1.txt, rc 1                         0                  B
sink step2.txt             STOP receipt-write step2.txt, rc 1                         0                  B
sink record-index.txt      STOP receipt-write record-index.txt, rc 1                  0                  B
sink record-history.txt    STOP receipt-write record-history.txt, rc 1                0                  B
sink push-dry-run.txt      STOP receipt-write push-dry-run.txt, rc 1                  1 (the dry run)    B
sink push-attempt.txt      STOP receipt-write push-attempt.txt, rc 1                  1 (the dry run)    B
sink push-result.txt       push lands, then STOP post-push … receipt-write-failed=1 … NO retry, rc 1    2    M
```

- **Your acceptance bar:** the two pre-push record-receipt sinks return nonzero, with zero push attempts (including no dry run) and the remote at B. Both meet it.
- **Disclosed:** the `push-dry-run.txt` and `push-attempt.txt` sinks necessarily come after the dry run, whose output is what they keep. The dry run cannot move the remote, and it stayed at B.
- **The post-push arm is the spent-attempt case:** it is reported as failed or unverified, with no retry.

`results/landing-2b/landing-walk-7r2-on-rev3.txt`, the revision 2 driver re-run on revision 3:
- YES pushes M.
- NO-a (a graft file) and NO-b (a record committed then removed) STOP at step (1), with no merge made.
- NO-d (the same history, with the pre-check removed) STOPs at step (4).
- NO-c (the landing directory already exists) STOPs at step (0).

Its first run aborted inside the DRIVER: the NO-d cut anchor looked for the old `print … step1` line, which is now `REC`. The aborted output is kept as `landing-walk-7r2-on-rev3.aborted-*.txt`, and the anchor fix is in the committed driver.

**Unchanged and not re-litigated:** everything your 021153 verified, including the F-2B-VP-1 closure on rev53. Remote state was re-read at this filing: origin/main == B and the branch == H. PR #28 is OPEN, draft, head H.

Asked: your re-verification of `07418d95aa8637bee7b6c8846132e26aa692ffefb34f2928b44d7f5a8eb22ea8`. Nothing in this relay is a token. The release hold is ABSOLUTE.

ACTIONS_GIT_REF: docs-lane writes only — packet revision 3, the walk drivers and records (d1552ff); this relay (a path-scoped commit follows), no trailer; walks in scratch clones against local bare repos only; no remote write; product bytes untouched.
RELAY_LINT: engine-rendered submission (daemon on kit 2.9.6); per-file 2.9.6 `relay-lint.py --no-freshness` on the draft; python-written; the draft and the packet scanned with the census alternation before submit (zero literals); the filed bytes compared to the draft by digest; every newer upstream file opened before this submit (the listing run as its own command).
FINAL_GIT_STATUS_SHORT:
none — no path-scoped change at write time
Literal path-scoped status for this seat's own writes at write time; the untracked results record is impl-17's; the shared bivpak tree carries other seats' untracked relays and a daemon-projected SEATS.md, not claimed clean here.
